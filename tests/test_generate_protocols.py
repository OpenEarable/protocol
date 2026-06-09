"""Tests for the protocol generator."""

from __future__ import annotations

import dataclasses
import pathlib
import tempfile
import unittest

from protocol_generator import (
    EmitterRegistry,
    GeneratedFile,
    LanguageEmitter,
    Protocol,
    ProtocolGenerator,
    ProtocolSchemaRepository,
    generate,
    load_protocol,
)
from protocol_generator.errors import SchemaError


@dataclasses.dataclass(frozen=True)
class FakeEmitter(LanguageEmitter):
    """Small test emitter used to verify the strategy registry."""

    def emit_runtime_files(self) -> tuple[GeneratedFile, ...]:
        """Emit one runtime marker file."""

        return (GeneratedFile(pathlib.Path("fake/runtime.txt"), "runtime"),)

    def emit_protocol_files(
        self,
        protocol: Protocol,
        schema_path: pathlib.Path,
    ) -> tuple[GeneratedFile, ...]:
        """Emit a marker file containing the protocol name."""

        return (GeneratedFile(pathlib.Path("fake") / f"{protocol.name}.txt", protocol.name),)


class GenerateProtocolsTest(unittest.TestCase):
    """Validate schema loading and generated output for the bundled schemas."""

    def test_loads_audio_response_schema(self) -> None:
        """The audio response schema should load into four ordered messages."""

        protocol = load_protocol(pathlib.Path("schemas/audio-response/protocol.yml"))

        self.assertEqual(protocol.name, "audio-response")
        self.assertEqual(protocol.version, 1)
        self.assertEqual(
            [message.name for message in protocol.messages],
            ["buffer", "tone", "audio_response", "sound"],
        )

    def test_generates_dart_and_c_outputs(self) -> None:
        """The generator should emit Dart, C header, and C source files."""

        with tempfile.TemporaryDirectory() as temp_dir:
            output_dir = pathlib.Path(temp_dir)
            written = generate(pathlib.Path("schemas"), output_dir)
            schema_count = len(tuple(pathlib.Path("schemas").glob("*/protocol.yml")))

            self.assertEqual(len(written), 6 + schema_count * 3)
            self.assertTrue((output_dir / "dart/lib/open_earable_protocols.dart").is_file())
            self.assertTrue((output_dir / "dart/lib/src/protocol_runtime.dart").is_file())
            self.assertTrue((output_dir / "c/protocol_runtime.h").is_file())
            self.assertTrue((output_dir / "c/protocol_runtime.c").is_file())
            self.assertTrue((output_dir / "c/protocol_sources.cmake").is_file())
            self.assertTrue((output_dir / "c/protocol_sources.mk").is_file())
            self.assertTrue((output_dir / "dart/lib/src/audio_response_protocol.dart").is_file())
            self.assertTrue((output_dir / "c/audio_response_protocol.h").is_file())
            self.assertTrue((output_dir / "c/audio_response_protocol.c").is_file())

            dart_library = (output_dir / "dart/lib/open_earable_protocols.dart").read_text()
            dart_output = (output_dir / "dart/lib/src/audio_response_protocol.dart").read_text()
            c_header = (output_dir / "c/audio_response_protocol.h").read_text()
            c_source = (output_dir / "c/audio_response_protocol.c").read_text()
            dart_runtime = (output_dir / "dart/lib/src/protocol_runtime.dart").read_text()
            c_runtime = (output_dir / "c/protocol_runtime.c").read_text()
            c_cmake_sources = (output_dir / "c/protocol_sources.cmake").read_text()
            c_make_sources = (output_dir / "c/protocol_sources.mk").read_text()

            self.assertIn(
                "export 'src/protocol_runtime.dart' show ProtocolFormatException;",
                dart_library,
            )
            self.assertIn("export 'src/audio_response_protocol.dart';", dart_library)
            self.assertIn("class AudioResponseSound", dart_output)
            self.assertIn("import 'protocol_runtime.dart';", dart_output)
            self.assertNotIn("class ProtocolWriter", dart_output)
            self.assertIn("class ProtocolWriter", dart_runtime)
            self.assertIn("audio_response_sound_encode", c_header)
            self.assertIn('#include "protocol_runtime.h"', c_header)
            self.assertNotIn("protocol_status_t protocol_write_uint16(", c_source)
            self.assertIn("protocol_status_t protocol_write_uint16(", c_runtime)
            self.assertIn("audio_response_protocol.c", c_cmake_sources)
            self.assertIn("audio_response_protocol.c", c_make_sources)

    def test_can_select_language_strategy(self) -> None:
        """The generator should only run selected language strategies."""

        with tempfile.TemporaryDirectory() as temp_dir:
            output_dir = pathlib.Path(temp_dir)
            registry = EmitterRegistry()
            registry.register("fake", FakeEmitter)
            generator = ProtocolGenerator(
                ProtocolSchemaRepository(pathlib.Path("schemas")),
                registry,
            )

            written = generator.generate(output_dir, languages=["fake"])

            expected_protocol_paths = [
                output_dir / "fake" / f"{schema_path.parent.name}.txt"
                for schema_path in sorted(pathlib.Path("schemas").glob("*/protocol.yml"))
            ]
            self.assertEqual(written, [output_dir / "fake/runtime.txt", *expected_protocol_paths])
            self.assertEqual((output_dir / "fake/runtime.txt").read_text(), "runtime")
            self.assertEqual((output_dir / "fake/audio-response.txt").read_text(), "audio-response")

    def test_generates_float_and_double_fields_and_arrays(self) -> None:
        """Floating-point fields should map to native Dart and C types."""

        schema = """\
protocol: measurements
version: 1
messages:
  sample:
    fields:
      - name: count
        type: uint8
      - name: value
        type: float
      - name: precise_value
        type: double
      - name: values
        type: float[count]
"""
        with tempfile.TemporaryDirectory() as temp_dir:
            root = pathlib.Path(temp_dir)
            schema_path = root / "schemas/measurements/protocol.yml"
            schema_path.parent.mkdir(parents=True)
            schema_path.write_text(schema)

            generate(root / "schemas", root / "generated")

            dart_output = (root / "generated/dart/lib/src/measurements_protocol.dart").read_text()
            c_header = (root / "generated/c/measurements_protocol.h").read_text()
            c_source = (root / "generated/c/measurements_protocol.c").read_text()

            self.assertIn("final double value;", dart_output)
            self.assertIn("final List<double> values;", dart_output)
            self.assertIn("reader.float32()", dart_output)
            self.assertIn("reader.float64()", dart_output)
            self.assertIn("float value;", c_header)
            self.assertIn("double precise_value;", c_header)
            self.assertIn("protocol_write_float", c_source)
            self.assertIn("protocol_write_double", c_source)

    def test_rejects_float_as_array_length(self) -> None:
        """Floating-point fields cannot control variable-length data."""

        schema = """\
protocol: invalid
version: 1
messages:
  sample:
    fields:
      - name: count
        type: float
      - name: values
        type: uint8[count]
"""
        with tempfile.TemporaryDirectory() as temp_dir:
            schema_path = pathlib.Path(temp_dir) / "protocol.yml"
            schema_path.write_text(schema)

            with self.assertRaisesRegex(SchemaError, "references length field 'count'"):
                load_protocol(schema_path)


if __name__ == "__main__":
    unittest.main()

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
from protocol_generator.model import ArrayType, BleCharacteristicProperty, UnionType


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
        """The audio response schema should retain ordered messages and descriptions."""

        protocol = load_protocol(pathlib.Path("schemas/audio-response/protocol.yml"))

        self.assertEqual(protocol.name, "audio-response")
        self.assertEqual(protocol.version, 1)
        self.assertIsNotNone(protocol.ble)
        assert protocol.ble is not None
        self.assertEqual(protocol.ble.service_uuid, "7467b395-9043-4453-bc5c-2d8e8b10680a")
        self.assertEqual(protocol.ble.characteristics[0].name, "transfer_control")
        self.assertEqual(
            protocol.ble.characteristics[0].properties,
            (BleCharacteristicProperty.WRITE,),
        )
        self.assertEqual(
            protocol.ble.characteristics[0].uuid,
            "7467b398-9043-4453-bc5c-2d8e8b10680a",
        )
        self.assertEqual(
            protocol.ble.characteristics[1].properties,
            (BleCharacteristicProperty.WRITE_WITHOUT_RESPONSE,),
        )
        self.assertEqual(
            protocol.ble.characteristics[2].properties,
            (BleCharacteristicProperty.NOTIFY,),
        )
        self.assertEqual(
            [characteristic.uuid for characteristic in protocol.ble.characteristics],
            [
                "7467b398-9043-4453-bc5c-2d8e8b10680a",
                "7467b399-9043-4453-bc5c-2d8e8b10680a",
                "7467b39a-9043-4453-bc5c-2d8e8b10680a",
                "7467b39b-9043-4453-bc5c-2d8e8b10680a",
                "7467b39c-9043-4453-bc5c-2d8e8b10680a",
            ],
        )
        self.assertEqual(
            [message.name for message in protocol.messages],
            [
                "transfer_start",
                "transfer_commit",
                "transfer_abort",
                "transfer_control",
                "transfer_chunk",
                "transfer_status",
                "config",
                "result",
            ],
        )
        self.assertEqual(
            protocol.messages[0].description,
            "Starts uploading an audio sample buffer. The checksum is CRC-32/ISO-HDLC "
            "over all little-endian encoded samples.",
        )
        transfer_control = protocol.messages[3]
        self.assertEqual(len(transfer_control.fields), 1)
        command_type = transfer_control.fields[0].type
        self.assertIsInstance(command_type, UnionType)
        assert isinstance(command_type, UnionType)
        self.assertEqual(command_type.tag_type.name, "uint8")
        self.assertEqual(
            [(variant.tag, variant.message.name) for variant in command_type.variants],
            [(0, "transfer_start"), (1, "transfer_commit"), (2, "transfer_abort")],
        )
        config = protocol.messages[6]
        self.assertEqual(
            [field.name for field in config.fields],
            ["id", "transfer_id", "volume", "points", "frequencies"],
        )
        frequencies_type = config.fields[4].type
        self.assertIsInstance(frequencies_type, ArrayType)
        assert isinstance(frequencies_type, ArrayType)
        self.assertEqual(frequencies_type.length_field, "points")
        self.assertEqual(frequencies_type.item_type.name, "uint16")

    def test_generates_dart_and_c_outputs(self) -> None:
        """The generator should emit Dart, C header, and C source files."""

        with tempfile.TemporaryDirectory() as temp_dir:
            output_dir = pathlib.Path(temp_dir)
            written = generate(pathlib.Path("schemas"), output_dir)
            schema_count = len(tuple(pathlib.Path("schemas").glob("*/protocol.yml")))
            ble_schema_count = sum(
                load_protocol(schema_path).ble is not None
                for schema_path in pathlib.Path("schemas").glob("*/protocol.yml")
            )

            self.assertEqual(len(written), 5 + schema_count * 3 + ble_schema_count)
            self.assertTrue((output_dir / "dart/lib/open_earable_protocols.dart").is_file())
            self.assertTrue((output_dir / "dart/lib/src/protocol_runtime.dart").is_file())
            self.assertTrue((output_dir / "c/include/protocol_runtime.h").is_file())
            self.assertTrue((output_dir / "c/src/protocol_runtime.c").is_file())
            self.assertTrue((output_dir / "c/CMakeLists.txt").is_file())
            self.assertFalse((output_dir / "c/Makefile").exists())
            self.assertFalse((output_dir / "c/protocol_sources.cmake").exists())
            self.assertFalse((output_dir / "c/protocol_sources.mk").exists())
            self.assertTrue((output_dir / "dart/lib/src/audio_response_protocol.dart").is_file())
            self.assertTrue((output_dir / "c/include/audio_response_protocol.h").is_file())
            self.assertTrue((output_dir / "c/src/audio_response_protocol.c").is_file())
            self.assertTrue((output_dir / "c/include/zephyr/audio_response_ble.h").is_file())

            dart_library = (output_dir / "dart/lib/open_earable_protocols.dart").read_text()
            dart_output = (output_dir / "dart/lib/src/audio_response_protocol.dart").read_text()
            c_header = (output_dir / "c/include/audio_response_protocol.h").read_text()
            c_source = (output_dir / "c/src/audio_response_protocol.c").read_text()
            dart_runtime = (output_dir / "dart/lib/src/protocol_runtime.dart").read_text()
            c_runtime = (output_dir / "c/src/protocol_runtime.c").read_text()
            c_cmake = (output_dir / "c/CMakeLists.txt").read_text()
            zephyr_header = (output_dir / "c/include/zephyr/audio_response_ble.h").read_text()

            self.assertIn("export 'src/protocol_runtime.dart'", dart_library)
            self.assertIn("ProtocolBleCharacteristicDefinition", dart_library)
            self.assertIn("ProtocolBleCharacteristicProperty", dart_library)
            self.assertIn("export 'src/audio_response_protocol.dart';", dart_library)
            self.assertIn("class AudioResponseTransferControl", dart_output)
            self.assertIn("sealed class AudioResponseTransferControlCommand", dart_output)
            self.assertIn(
                "class AudioResponseTransferStart implements AudioResponseTransferControlCommand",
                dart_output,
            )
            self.assertIn(
                "factory AudioResponseTransferControl.start(AudioResponseTransferStart command)",
                dart_output,
            )
            self.assertNotIn("required this.type", dart_output)
            self.assertIn("class AudioResponseTransferChunk", dart_output)
            self.assertIn("class AudioResponseTransferStatus", dart_output)
            self.assertIn(
                "AudioResponseConfig({required this.id, required this.transfer_id, "
                "required this.volume, required this.points, required this.frequencies});",
                dart_output,
            )
            self.assertIn("final List<int> frequencies;", dart_output)
            self.assertIn("writer.uint8(points);", dart_output)
            self.assertIn("frequencies length does not match points", dart_output)
            self.assertIn(
                "/// Starts uploading an audio sample buffer.",
                dart_output,
            )
            self.assertIn("abstract final class AudioResponseBleUuids", dart_output)
            self.assertIn(
                "static const String serviceUuid = '7467b395-9043-4453-bc5c-2d8e8b10680a';",
                dart_output,
            )
            self.assertIn(
                "static const String transferControlCharacteristicUuid = "
                "'7467b398-9043-4453-bc5c-2d8e8b10680a';",
                dart_output,
            )
            self.assertIn("ProtocolBleCharacteristicProperty.write", dart_output)
            self.assertIn("ProtocolBleCharacteristicProperty.writeWithoutResponse", dart_output)
            self.assertIn("ProtocolBleCharacteristicProperty.notify", dart_output)
            self.assertIn("static const ProtocolBleServiceDefinition service", dart_output)
            self.assertIn("mapPropertiesByName", dart_runtime)
            self.assertIn("bool get isReadable", dart_runtime)
            self.assertIn("bool get isWritable", dart_runtime)
            self.assertIn("import 'protocol_runtime.dart';", dart_output)
            self.assertNotIn("class ProtocolWriter", dart_output)
            self.assertIn("class ProtocolWriter", dart_runtime)
            self.assertIn("audio_response_transfer_control_encode", c_header)
            self.assertIn("AUDIO_RESPONSE_TRANSFER_CONTROL_START = 0", c_header)
            self.assertIn("audio_response_transfer_control_from_start", c_header)
            self.assertIn("audio_response_transfer_control_set_command_start", c_header)
            self.assertIn("audio_response_transfer_control_dispatch", c_header)
            self.assertIn("audio_response_transfer_control_handler_t", c_header)
            self.assertIn("audio_response_transfer_chunk_encode", c_header)
            self.assertIn("audio_response_transfer_status_encode", c_header)
            self.assertIn("uint8_t points;", c_header)
            self.assertIn("uint16_t *frequencies;", c_header)
            self.assertIn("protocol_write_uint8(writer, message->points)", c_source)
            self.assertIn("message->frequencies[index]", c_source)
            self.assertIn('#include "protocol_runtime.h"', c_header)
            self.assertIn(
                "/** Uploads a contiguous section of an audio sample buffer. */",
                c_header,
            )
            self.assertIn("Encode a binary representation of this message.", c_header)
            self.assertIn(
                '#define AUDIO_RESPONSE_BLE_SERVICE_UUID "7467b395-9043-4453-bc5c-2d8e8b10680a"',
                c_header,
            )
            self.assertIn(
                "#define AUDIO_RESPONSE_BLE_TRANSFER_CONTROL_CHARACTERISTIC_UUID "
                '"7467b398-9043-4453-bc5c-2d8e8b10680a"',
                c_header,
            )
            self.assertIn(
                "#define AUDIO_RESPONSE_BLE_TRANSFER_DATA_CHARACTERISTIC_PROPERTIES "
                "(PROTOCOL_BLE_PROPERTY_WRITE_WITHOUT_RESPONSE)",
                c_header,
            )
            self.assertIn(
                "#define AUDIO_RESPONSE_BLE_CONFIG_CHARACTERISTIC_PROPERTIES "
                "(PROTOCOL_BLE_PROPERTY_WRITE)",
                c_header,
            )
            self.assertIn(
                "#define AUDIO_RESPONSE_ZEPHYR_SERVICE_UUID "
                "BT_UUID_DECLARE_128(BT_UUID_128_ENCODE(",
                zephyr_header,
            )
            self.assertIn(
                "#define AUDIO_RESPONSE_ZEPHYR_TRANSFER_DATA_CHARACTERISTIC_PROPERTIES "
                "(BT_GATT_CHRC_WRITE_WITHOUT_RESP)",
                zephyr_header,
            )
            self.assertIn(
                "#define AUDIO_RESPONSE_ZEPHYR_TRANSFER_DATA_CHARACTERISTIC_PERMISSIONS "
                "(BT_GATT_PERM_WRITE)",
                zephyr_header,
            )
            self.assertNotIn("protocol_status_t protocol_write_uint16(", c_source)
            self.assertIn("protocol_status_t protocol_write_uint16(", c_runtime)
            self.assertIn('"src/audio_response_protocol.c"', c_cmake)
            self.assertIn("add_library(OpenEarable::Protocols ALIAS", c_cmake)
            self.assertIn("target_compile_features(open_earable_protocols PUBLIC c_std_99)", c_cmake)

    def test_rejects_implicit_or_out_of_range_union_tags(self) -> None:
        """Tagged unions must declare stable tags that fit their wire type."""

        implicit_schema = """\
protocol: invalid
version: 1
messages:
  first:
    fields: []
  second:
    fields: []
  container:
    fields:
      - name: type
        type: uint8
      - name: value
        type: first | second
"""
        out_of_range_schema = """\
protocol: invalid
version: 1
messages:
  first:
    fields: []
  container:
    fields:
      - name: value
        type: union
        tag_type: uint8
        variants:
          256: first
"""
        with tempfile.TemporaryDirectory() as temp_dir:
            schema_path = pathlib.Path(temp_dir) / "protocol.yml"
            schema_path.write_text(implicit_schema)
            with self.assertRaisesRegex(SchemaError, "unsupported field type"):
                load_protocol(schema_path)

            schema_path.write_text(out_of_range_schema)
            with self.assertRaisesRegex(SchemaError, "does not fit uint8"):
                load_protocol(schema_path)

    def test_generates_typed_api_for_embedded_union(self) -> None:
        """C unions with sibling fields should receive typed setters and dispatch."""

        schema = """\
protocol: events
version: 1
messages:
  started:
    fields: []
  stopped:
    fields: []
  event:
    fields:
      - name: sequence
        type: uint16
      - name: payload
        type: union
        tag_type: uint8
        variants:
          3: started
          7: stopped
"""
        with tempfile.TemporaryDirectory() as temp_dir:
            root = pathlib.Path(temp_dir)
            schema_path = root / "schemas/events/protocol.yml"
            schema_path.parent.mkdir(parents=True)
            schema_path.write_text(schema)

            generate(root / "schemas", root / "generated")

            header = (root / "generated/c/include/events_protocol.h").read_text()
            source = (root / "generated/c/src/events_protocol.c").read_text()
            self.assertIn("events_event_set_payload_started", header)
            self.assertIn("events_event_dispatch", header)
            self.assertNotIn("events_event_from_started", header)
            self.assertIn("EVENTS_EVENT_STARTED = 3", header)
            self.assertIn("case EVENTS_EVENT_STARTED:", source)

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
            c_header = (root / "generated/c/include/measurements_protocol.h").read_text()
            c_source = (root / "generated/c/src/measurements_protocol.c").read_text()

            self.assertIn("final double value;", dart_output)
            self.assertIn("final List<double> values;", dart_output)
            self.assertIn("reader.float32()", dart_output)
            self.assertIn("reader.float64()", dart_output)
            self.assertIn("float value;", c_header)
            self.assertIn("double precise_value;", c_header)
            self.assertIn("protocol_write_float", c_source)
            self.assertIn("protocol_write_double", c_source)
            self.assertIn(
                "/// Sample message for the measurements protocol.",
                dart_output,
            )
            self.assertIn(
                "/** Sample message for the measurements protocol. */",
                c_header,
            )

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

    def test_rejects_unknown_ble_property(self) -> None:
        """Unknown BLE properties should fail schema validation."""

        schema = """\
protocol: invalid
version: 1
transport:
  ble:
    service_uuid: 180d
    characteristics:
      - name: measurement
        uuid: 2a37
        properties: [read, unsupported]
messages:
  sample:
    fields:
      - name: value
        type: uint8
"""
        with tempfile.TemporaryDirectory() as temp_dir:
            schema_path = pathlib.Path(temp_dir) / "protocol.yml"
            schema_path.write_text(schema)

            with self.assertRaisesRegex(SchemaError, "unsupported BLE characteristic property"):
                load_protocol(schema_path)

    def test_rejects_non_string_message_description(self) -> None:
        """Message descriptions must be strings when provided."""

        schema = """\
protocol: invalid
version: 1
messages:
  sample:
    description: 42
    fields: []
"""
        with tempfile.TemporaryDirectory() as temp_dir:
            schema_path = pathlib.Path(temp_dir) / "protocol.yml"
            schema_path.write_text(schema)

            with self.assertRaisesRegex(SchemaError, "description must be a string"):
                load_protocol(schema_path)

    def test_normalizes_universal_ble_property_names(self) -> None:
        """UniversalBLE-style property names should map to standard properties."""

        schema = """\
protocol: ble-properties
version: 1
transport:
  ble:
    service_uuid: 180d
    characteristics:
      - name: values
        uuid: "12345678"
        properties: [writeWithoutResponse, authenticatedSignedWrites, extendedProperties]
messages:
  value:
    fields: []
"""
        with tempfile.TemporaryDirectory() as temp_dir:
            root = pathlib.Path(temp_dir)
            schema_path = root / "schemas/ble-properties/protocol.yml"
            schema_path.parent.mkdir(parents=True)
            schema_path.write_text(schema)

            protocol = load_protocol(schema_path)
            generate(root / "schemas", root / "generated")
            zephyr_header = (
                root / "generated/c/include/zephyr/ble_properties_ble.h"
            ).read_text()

            assert protocol.ble is not None
            self.assertEqual(protocol.ble.service_uuid, "180d")
            self.assertEqual(protocol.ble.characteristics[0].uuid, "12345678")
            self.assertEqual(
                protocol.ble.characteristics[0].properties,
                (
                    BleCharacteristicProperty.WRITE_WITHOUT_RESPONSE,
                    BleCharacteristicProperty.AUTHENTICATED_SIGNED_WRITES,
                    BleCharacteristicProperty.EXTENDED_PROPERTIES,
                ),
            )
            self.assertIn(
                "#define BLE_PROPERTIES_ZEPHYR_SERVICE_UUID BT_UUID_DECLARE_16(0x180d)",
                zephyr_header,
            )
            self.assertIn(
                "#define BLE_PROPERTIES_ZEPHYR_VALUES_CHARACTERISTIC_UUID "
                "BT_UUID_DECLARE_32(0x12345678)",
                zephyr_header,
            )
            self.assertIn(
                "(BT_GATT_CHRC_WRITE_WITHOUT_RESP | BT_GATT_CHRC_AUTH | "
                "BT_GATT_CHRC_EXT_PROP)",
                zephyr_header,
            )


if __name__ == "__main__":
    unittest.main()

"""Dart protocol emitter."""

from __future__ import annotations

import pathlib
import textwrap
from collections.abc import Sequence

from protocol_generator.emitters.base import LanguageEmitter
from protocol_generator.model import (
    ArrayType,
    BytesType,
    Field,
    FieldType,
    Message,
    MessageRefType,
    Protocol,
    ScalarType,
    UnionType,
)
from protocol_generator.naming import generated_banner, pascal_case, snake_case
from protocol_generator.output import GeneratedFile
from protocol_generator.text import _indent


DART_SCALAR_TYPES = {
    "uint8": "int",
    "uint16": "int",
    "uint32": "int",
    "int8": "int",
    "int16": "int",
    "int32": "int",
    "float": "double",
    "double": "double",
}

DART_CODEC_METHODS = {
    "uint8": "uint8",
    "uint16": "uint16",
    "uint32": "uint32",
    "int8": "int8",
    "int16": "int16",
    "int32": "int32",
    "float": "float32",
    "double": "float64",
}


class DartEmitter(LanguageEmitter):
    """Emit Dart value classes and binary codecs."""

    def emit_runtime_files(self) -> tuple[GeneratedFile, ...]:
        """Emit the shared Dart protocol runtime."""

        return (_DartRuntimeRenderer().render(),)

    def emit_protocol_files(
        self,
        protocol: Protocol,
        schema_path: pathlib.Path,
    ) -> tuple[GeneratedFile, ...]:
        """Emit the Dart protocol library."""

        return (_DartRenderer(protocol, schema_path).render(),)

    def emit_collection_files(
        self,
        protocols: Sequence[Protocol],
    ) -> tuple[GeneratedFile, ...]:
        """Emit the public package library that exports every protocol."""

        exports = "".join(
            f"export 'src/{snake_case(protocol.name)}_protocol.dart';\n"
            for protocol in protocols
        )
        contents = (
            "/// Binary protocol bindings for OpenEarable devices.\n"
            "library;\n\n"
            "export 'src/protocol_runtime.dart' show ProtocolFormatException;\n"
            f"{exports}"
        )
        return (
            GeneratedFile(
                pathlib.Path("dart/lib/open_earable_protocols.dart"),
                contents,
            ),
        )


class _DartRuntimeRenderer:
    """Render the shared Dart binary codec runtime."""

    def render(self) -> GeneratedFile:
        """Render the runtime library shared by generated protocols."""

        return GeneratedFile(
            pathlib.Path("dart/lib/src/protocol_runtime.dart"),
            self._support_code(),
        )

    def _support_code(self) -> str:
        return (
            "// Generated shared protocol runtime. Do not edit by hand.\n"
            "import 'dart:typed_data';\n\n"
            + textwrap.dedent(
                """
                /// Error thrown when binary protocol data is malformed.
                class ProtocolFormatException implements Exception {
                  /// Creates a protocol format error with a human-readable [message].
                  const ProtocolFormatException(this.message);

                  /// Description of the malformed data.
                  final String message;

                  @override
                  String toString() => 'ProtocolFormatException: $message';
                }

                /// Writes little-endian protocol values into a byte buffer.
                class ProtocolWriter {
                  final BytesBuilder _builder = BytesBuilder(copy: false);

                  void uint8(int value) => _builder.add([value & 0xff]);

                  void int8(int value) => _builder.add([value & 0xff]);

                  void uint16(int value) {
                    final data = ByteData(2)..setUint16(0, value, Endian.little);
                    _builder.add(data.buffer.asUint8List());
                  }

                  void int16(int value) {
                    final data = ByteData(2)..setInt16(0, value, Endian.little);
                    _builder.add(data.buffer.asUint8List());
                  }

                  void uint32(int value) {
                    final data = ByteData(4)..setUint32(0, value, Endian.little);
                    _builder.add(data.buffer.asUint8List());
                  }

                  void int32(int value) {
                    final data = ByteData(4)..setInt32(0, value, Endian.little);
                    _builder.add(data.buffer.asUint8List());
                  }

                  void float32(double value) {
                    final data = ByteData(4)..setFloat32(0, value, Endian.little);
                    _builder.add(data.buffer.asUint8List());
                  }

                  void float64(double value) {
                    final data = ByteData(8)..setFloat64(0, value, Endian.little);
                    _builder.add(data.buffer.asUint8List());
                  }

                  void bytes(Uint8List value) => _builder.add(value);

                  Uint8List takeBytes() => _builder.takeBytes();
                }

                /// Reads little-endian protocol values from a byte buffer.
                class ProtocolReader {
                  ProtocolReader(Uint8List bytes)
                      : _data = ByteData.sublistView(bytes),
                        _bytes = bytes;

                  final ByteData _data;
                  final Uint8List _bytes;
                  int _offset = 0;

                  void _require(int length) {
                    if (_offset + length > _bytes.length) {
                      throw const ProtocolFormatException('unexpected end of input');
                    }
                  }

                  int uint8() {
                    _require(1);
                    return _data.getUint8(_offset++);
                  }

                  int int8() {
                    _require(1);
                    return _data.getInt8(_offset++);
                  }

                  int uint16() {
                    _require(2);
                    final value = _data.getUint16(_offset, Endian.little);
                    _offset += 2;
                    return value;
                  }

                  int int16() {
                    _require(2);
                    final value = _data.getInt16(_offset, Endian.little);
                    _offset += 2;
                    return value;
                  }

                  int uint32() {
                    _require(4);
                    final value = _data.getUint32(_offset, Endian.little);
                    _offset += 4;
                    return value;
                  }

                  int int32() {
                    _require(4);
                    final value = _data.getInt32(_offset, Endian.little);
                    _offset += 4;
                    return value;
                  }

                  double float32() {
                    _require(4);
                    final value = _data.getFloat32(_offset, Endian.little);
                    _offset += 4;
                    return value;
                  }

                  double float64() {
                    _require(8);
                    final value = _data.getFloat64(_offset, Endian.little);
                    _offset += 8;
                    return value;
                  }

                  Uint8List bytes(int length) {
                    _require(length);
                    final value = Uint8List.sublistView(_bytes, _offset, _offset + length);
                    _offset += length;
                    return value;
                  }

                  void finish() {
                    if (_offset != _bytes.length) {
                      throw ProtocolFormatException('trailing ${_bytes.length - _offset} byte(s)');
                    }
                  }
                }

                """
            )
        )


class _DartRenderer:
    """Render one protocol schema into a Dart library."""

    def __init__(self, protocol: Protocol, schema_path: pathlib.Path) -> None:
        self.protocol = protocol
        self.schema_path = schema_path
        self.prefix = pascal_case(protocol.name)

    def render(self) -> GeneratedFile:
        """Render the configured protocol into its generated Dart file."""

        return GeneratedFile(
            pathlib.Path("dart/lib/src") / f"{snake_case(self.protocol.name)}_protocol.dart",
            self._emit(),
        )

    def _emit(self) -> str:
        parts = [
            generated_banner(self.schema_path),
            "import 'dart:typed_data';\n",
            "import 'protocol_runtime.dart';\n\n",
        ]
        for message in self.protocol.messages:
            parts.append(self._message(message))
        return "".join(parts)

    def _message(self, message: Message) -> str:
        class_name = self._class_name(message.name)
        ctor_params = ", ".join(f"required this.{field.name}" for field in message.fields)
        declarations = "\n".join(f"  {self._dart_type(field.type)} {field.name};" for field in message.fields)
        read_lines = self._read_lines(message)
        write_lines = self._write_lines(message)
        return (
            f"/// {pascal_case(message.name)} message for the {self.protocol.name} protocol.\n"
            f"class {class_name} {{\n"
            f"  /// Creates a {class_name} value.\n"
            f"  {class_name}({{{ctor_params}}});\n\n"
            f"{declarations}\n\n"
            f"  /// Decodes a complete {class_name} value from [bytes].\n"
            f"  factory {class_name}.fromBytes(Uint8List bytes) {{\n"
            f"    final reader = ProtocolReader(bytes);\n"
            f"    final value = {class_name}._read(reader);\n"
            f"    reader.finish();\n"
            f"    return value;\n"
            f"  }}\n\n"
            f"  static {class_name} _read(ProtocolReader reader) {{\n"
            f"{read_lines}\n"
            f"    return {class_name}({self._ctor_args(message)});\n"
            f"  }}\n\n"
            f"  /// Encodes this value to the protocol binary representation.\n"
            f"  Uint8List toBytes() {{\n"
            f"    final writer = ProtocolWriter();\n"
            f"    _write(writer);\n"
            f"    return writer.takeBytes();\n"
            f"  }}\n\n"
            f"  void _write(ProtocolWriter writer) {{\n"
            f"{write_lines}\n"
            f"  }}\n"
            f"}}\n\n"
        )

    def _class_name(self, message_name: str) -> str:
        return f"{self.prefix}{pascal_case(message_name)}"

    def _dart_type(self, field_type: FieldType) -> str:
        if isinstance(field_type, ScalarType):
            return f"final {DART_SCALAR_TYPES[field_type.name]}"
        if isinstance(field_type, BytesType):
            return "final Uint8List"
        if isinstance(field_type, ArrayType):
            return f"final List<{DART_SCALAR_TYPES[field_type.item_type.name]}>"
        if isinstance(field_type, MessageRefType):
            return f"final {self._class_name(field_type.name)}"
        if isinstance(field_type, UnionType):
            variant_types = ", ".join(self._class_name(variant.name) for variant in field_type.variants)
            return f"final Object /* {variant_types} */"
        raise AssertionError(field_type)

    def _read_lines(self, message: Message) -> str:
        lines: list[str] = []
        for field in message.fields:
            lines.extend(self._read_field(field))
        return _indent("\n".join(lines), 4)

    def _read_field(self, field: Field) -> list[str]:
        field_type = field.type
        if isinstance(field_type, ScalarType):
            return [f"final {field.name} = reader.{DART_CODEC_METHODS[field_type.name]}();"]
        if isinstance(field_type, BytesType):
            return [f"final {field.name} = reader.bytes({field_type.length_field});"]
        if isinstance(field_type, ArrayType):
            item_type = DART_SCALAR_TYPES[field_type.item_type.name]
            return [
                f"final {field.name} = List<{item_type}>.generate(",
                f"  {field_type.length_field},",
                f"  (_) => reader.{DART_CODEC_METHODS[field_type.item_type.name]}(),",
                ");",
            ]
        if isinstance(field_type, MessageRefType):
            return [f"final {field.name} = {self._class_name(field_type.name)}._read(reader);"]
        if isinstance(field_type, UnionType):
            lines = [f"final Object {field.name};", "switch (type) {"]
            for index, variant in enumerate(field_type.variants):
                lines.extend(
                    [
                        f"  case {index}:",
                        f"    {field.name} = {self._class_name(variant.name)}._read(reader);",
                        "    break;",
                    ]
                )
            lines.extend(
                [
                    "  default:",
                    "    throw ProtocolFormatException('unknown union discriminator $type');",
                    "}",
                ]
            )
            return lines
        raise AssertionError(field_type)

    def _write_lines(self, message: Message) -> str:
        lines: list[str] = []
        for field in message.fields:
            lines.extend(self._write_field(field))
        return _indent("\n".join(lines), 4)

    def _write_field(self, field: Field) -> list[str]:
        field_type = field.type
        if isinstance(field_type, ScalarType):
            return [f"writer.{DART_CODEC_METHODS[field_type.name]}({field.name});"]
        if isinstance(field_type, BytesType):
            return [
                f"if ({field.name}.length != {field_type.length_field}) {{",
                f"  throw ProtocolFormatException('{field.name} length does not match {field_type.length_field}');",
                "}",
                f"writer.bytes({field.name});",
            ]
        if isinstance(field_type, ArrayType):
            return [
                f"if ({field.name}.length != {field_type.length_field}) {{",
                f"  throw ProtocolFormatException('{field.name} length does not match {field_type.length_field}');",
                "}",
                f"for (final value in {field.name}) {{",
                f"  writer.{DART_CODEC_METHODS[field_type.item_type.name]}(value);",
                "}",
            ]
        if isinstance(field_type, MessageRefType):
            return [f"{field.name}._write(writer);"]
        if isinstance(field_type, UnionType):
            lines: list[str] = []
            for index, variant in enumerate(field_type.variants):
                class_name = self._class_name(variant.name)
                lines.extend(
                    [
                        f"if ({field.name} is {class_name}) {{",
                        f"    if (type != {index}) {{",
                        f"      throw const ProtocolFormatException('union discriminator does not match payload type');",
                        "    }",
                        f"    ({field.name} as {class_name})._write(writer);",
                        "    return;",
                        "}",
                        ]
                )
            lines.extend(
                [
                    f"throw ProtocolFormatException('unsupported union payload: ${{{field.name}.runtimeType}}');",
                ]
            )
            return lines
        raise AssertionError(field_type)

    def _ctor_args(self, message: Message) -> str:
        return ", ".join(f"{field.name}: {field.name}" for field in message.fields)

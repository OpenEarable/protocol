"""Dart protocol emitter."""

from __future__ import annotations

import pathlib
import textwrap
from collections.abc import Sequence

from protocol_generator.emitters.base import LanguageEmitter
from protocol_generator.model import (
    ArrayType,
    BleCharacteristicProperty,
    BytesType,
    Field,
    FieldType,
    Message,
    MessageRefType,
    Protocol,
    ScalarType,
    UnionType,
)
from protocol_generator.naming import generated_banner, lower_camel_case, pascal_case, snake_case
from protocol_generator.output import GeneratedFile
from protocol_generator.text import _indent, dart_doc_comment


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

DART_BLE_PROPERTIES = {
    BleCharacteristicProperty.BROADCAST: "broadcast",
    BleCharacteristicProperty.READ: "read",
    BleCharacteristicProperty.WRITE_WITHOUT_RESPONSE: "writeWithoutResponse",
    BleCharacteristicProperty.WRITE: "write",
    BleCharacteristicProperty.NOTIFY: "notify",
    BleCharacteristicProperty.INDICATE: "indicate",
    BleCharacteristicProperty.AUTHENTICATED_SIGNED_WRITES: "authenticatedSignedWrites",
    BleCharacteristicProperty.EXTENDED_PROPERTIES: "extendedProperties",
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
            "export 'src/protocol_runtime.dart'\n"
            "    show\n"
            "        ProtocolBleCharacteristicDefinition,\n"
            "        ProtocolBleCharacteristicProperty,\n"
            "        ProtocolBleServiceDefinition,\n"
            "        ProtocolFormatException;\n"
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

                /// Standard Bluetooth GATT characteristic properties.
                ///
                /// The enum value names intentionally match Universal BLE's
                /// `CharacteristicProperty` names.
                enum ProtocolBleCharacteristicProperty {
                  broadcast,
                  read,
                  writeWithoutResponse,
                  write,
                  notify,
                  indicate,
                  authenticatedSignedWrites,
                  extendedProperties,
                }

                /// Framework-neutral BLE characteristic metadata.
                class ProtocolBleCharacteristicDefinition {
                  /// Creates immutable BLE characteristic metadata.
                  const ProtocolBleCharacteristicDefinition({
                    required this.name,
                    required this.uuid,
                    required this.properties,
                  });

                  /// Schema name of the characteristic.
                  final String name;

                  /// Bluetooth characteristic UUID.
                  final String uuid;

                  /// Standard GATT characteristic properties.
                  final Set<ProtocolBleCharacteristicProperty> properties;

                  /// Property names accepted by Universal BLE's
                  /// `CharacteristicProperty.values.byName`.
                  Set<String> get universalBlePropertyNames =>
                      properties.map((property) => property.name).toSet();

                  /// Whether a GATT client may read this characteristic.
                  bool get isReadable =>
                      properties.contains(ProtocolBleCharacteristicProperty.read);

                  /// Whether a GATT client may write this characteristic.
                  bool get isWritable =>
                      properties.contains(ProtocolBleCharacteristicProperty.write) ||
                      properties.contains(
                        ProtocolBleCharacteristicProperty.writeWithoutResponse,
                      ) ||
                      properties.contains(
                        ProtocolBleCharacteristicProperty.authenticatedSignedWrites,
                      );

                  /// Maps these properties to a framework enum with matching names.
                  ///
                  /// For Universal BLE, pass `CharacteristicProperty.values` and
                  /// `(property) => property.name`.
                  List<T> mapPropertiesByName<T>(
                    Iterable<T> availableProperties,
                    String Function(T property) nameOf,
                  ) {
                    final names = universalBlePropertyNames;
                    return availableProperties
                        .where((property) => names.contains(nameOf(property)))
                        .toList();
                  }
                }

                /// Framework-neutral BLE service metadata.
                class ProtocolBleServiceDefinition {
                  /// Creates immutable BLE service metadata.
                  const ProtocolBleServiceDefinition({
                    required this.uuid,
                    required this.characteristics,
                  });

                  /// Bluetooth service UUID.
                  final String uuid;

                  /// Characteristics exposed by this service.
                  final List<ProtocolBleCharacteristicDefinition> characteristics;
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
        if self.protocol.ble is not None:
            parts.append(self._ble_uuid_constants())
        parts.append(self._union_interfaces())
        for message in self.protocol.messages:
            parts.append(self._message(message))
        return "".join(parts)

    def _ble_uuid_constants(self) -> str:
        """Render BLE service and characteristic UUID constants."""

        assert self.protocol.ble is not None
        class_name = f"{self.prefix}BleUuids"
        lines = [
            f"/// BLE UUIDs for the {self.protocol.name} protocol.",
            f"abstract final class {class_name} {{",
            f"  /// BLE service UUID.",
            f"  static const String serviceUuid = '{self.protocol.ble.service_uuid}';",
        ]
        for characteristic in self.protocol.ble.characteristics:
            characteristic_prefix = lower_camel_case(characteristic.name)
            constant_name = f"{characteristic_prefix}CharacteristicUuid"
            properties = [
                f"ProtocolBleCharacteristicProperty.{DART_BLE_PROPERTIES[property]}"
                for property in characteristic.properties
            ]
            lines.extend(
                [
                    "",
                    f"  /// BLE UUID for the {characteristic.name} characteristic.",
                    f"  static const String {constant_name} = '{characteristic.uuid}';",
                    "",
                    f"  /// BLE metadata for the {characteristic.name} characteristic.",
                    f"  static const ProtocolBleCharacteristicDefinition "
                    f"{characteristic_prefix}Characteristic =",
                    "      ProtocolBleCharacteristicDefinition(",
                    f"        name: '{characteristic.name}',",
                    f"        uuid: {constant_name},",
                    "        properties: {",
                    *(f"          {property_value}," for property_value in properties),
                    "        },",
                    "      );",
                ]
            )
        characteristic_references = ", ".join(
            f"{lower_camel_case(characteristic.name)}Characteristic"
            for characteristic in self.protocol.ble.characteristics
        )
        lines.extend(
            [
                "",
                "  /// Complete framework-neutral BLE service metadata.",
                "  static const ProtocolBleServiceDefinition service =",
                "      ProtocolBleServiceDefinition(",
                "        uuid: serviceUuid,",
                f"        characteristics: [{characteristic_references}],",
                "      );",
            ]
        )
        lines.extend(["}", ""])
        return "\n".join(lines) + "\n"

    def _message(self, message: Message) -> str:
        class_name = self._class_name(message.name)
        documentation = dart_doc_comment(
            message.description,
            f"{pascal_case(message.name)} message for the {self.protocol.name} protocol.",
        )
        ctor_params = ", ".join(f"required this.{field.name}" for field in message.fields)
        declarations = "\n".join(
            f"  {self._dart_field_type(message, field)} {field.name};"
            for field in message.fields
        )
        read_lines = self._read_lines(message)
        write_lines = self._write_lines(message)
        union_factories = self._union_factories(message)
        interfaces = self._implemented_union_interfaces(message)
        implements = f" implements {', '.join(interfaces)}" if interfaces else ""
        return (
            f"{documentation}\n"
            f"class {class_name}{implements} {{\n"
            f"  /// Creates a {class_name} value.\n"
            f"  {class_name}({{{ctor_params}}});\n\n"
            f"{union_factories}"
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

    def _dart_field_type(self, message: Message, field: Field) -> str:
        """Return the public Dart declaration type for a message field."""

        field_type = field.type
        if isinstance(field_type, ScalarType):
            return f"final {DART_SCALAR_TYPES[field_type.name]}"
        if isinstance(field_type, BytesType):
            return "final Uint8List"
        if isinstance(field_type, ArrayType):
            return f"final List<{DART_SCALAR_TYPES[field_type.item_type.name]}>"
        if isinstance(field_type, MessageRefType):
            return f"final {self._class_name(field_type.name)}"
        if isinstance(field_type, UnionType):
            return f"final {self._union_interface_name(message, field)}"
        raise AssertionError(field_type)

    def _read_lines(self, message: Message) -> str:
        lines: list[str] = []
        for field in message.fields:
            lines.extend(self._read_field(message, field))
        return _indent("\n".join(lines), 4)

    def _read_field(self, message: Message, field: Field) -> list[str]:
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
            discriminator = f"{field.name}Type"
            interface_name = self._union_interface_name(message, field)
            lines = [
                f"final {discriminator} = reader.{DART_CODEC_METHODS[field_type.tag_type.name]}();",
                f"final {interface_name} {field.name};",
                f"switch ({discriminator}) {{",
            ]
            for variant in field_type.variants:
                lines.extend(
                    [
                        f"  case {variant.tag}:",
                        f"    {field.name} = "
                        f"{self._class_name(variant.message.name)}._read(reader);",
                        "    break;",
                    ]
                )
            lines.extend(
                [
                    "  default:",
                    f"    throw ProtocolFormatException("
                    f"'unknown union discriminator ${{{discriminator}}}');",
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
            for variant in field_type.variants:
                class_name = self._class_name(variant.message.name)
                lines.extend(
                    [
                        f"if ({field.name} is {class_name}) {{",
                        f"  writer.{DART_CODEC_METHODS[field_type.tag_type.name]}({variant.tag});",
                        f"  ({field.name} as {class_name})._write(writer);",
                        "  return;",
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

    def _union_factories(self, message: Message) -> str:
        """Render inferred-discriminator factories for a single-union message."""

        if len(message.fields) != 1 or not isinstance(message.fields[0].type, UnionType):
            return ""
        field = message.fields[0]
        field_type = field.type
        assert isinstance(field_type, UnionType)
        class_name = self._class_name(message.name)
        lines: list[str] = []
        for variant in field_type.variants:
            variant_name = variant.message.name
            short_name = self._short_variant_name(message, variant_name)
            variant_class = self._class_name(variant_name)
            lines.extend(
                [
                    f"  /// Creates a {class_name} containing {variant_class}.",
                    f"  factory {class_name}.{lower_camel_case(short_name)}"
                    f"({variant_class} command) =>",
                    f"      {class_name}({field.name}: command);",
                    "",
                ]
            )
        return "\n".join(lines) + "\n"

    def _union_interfaces(self) -> str:
        """Render sealed marker interfaces used by Dart tagged unions."""

        lines: list[str] = []
        for message in self.protocol.messages:
            for field in message.fields:
                if isinstance(field.type, UnionType):
                    name = self._union_interface_name(message, field)
                    lines.extend(
                        [
                            f"/// Payload accepted by {self._class_name(message.name)}.{field.name}.",
                            f"sealed class {name} {{}}",
                            "",
                        ]
                    )
        return "\n".join(lines) + ("\n" if lines else "")

    def _implemented_union_interfaces(self, message: Message) -> tuple[str, ...]:
        """Return marker interfaces implemented by a union variant message."""

        interfaces: list[str] = []
        for owner in self.protocol.messages:
            for field in owner.fields:
                if not isinstance(field.type, UnionType):
                    continue
                if any(variant.message.name == message.name for variant in field.type.variants):
                    interfaces.append(self._union_interface_name(owner, field))
        return tuple(interfaces)

    def _union_interface_name(self, message: Message, field: Field) -> str:
        """Return the Dart marker interface name for a tagged union field."""

        return f"{self._class_name(message.name)}{pascal_case(field.name)}"

    @staticmethod
    def _short_variant_name(message: Message, variant_name: str) -> str:
        """Remove a shared message prefix from a variant for concise APIs."""

        prefix = f"{message.name.removesuffix('_control')}_"
        return variant_name.removeprefix(prefix)

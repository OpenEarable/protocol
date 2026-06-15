"""C and C++ compatible protocol emitter."""

from __future__ import annotations

import pathlib
import re
import textwrap
from collections.abc import Mapping, Sequence

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
from protocol_generator.naming import generated_banner, pascal_case, snake_case
from protocol_generator.output import GeneratedFile
from protocol_generator.text import _indent, c_doc_comment


C_SCALAR_TYPES = {
    "uint8": "uint8_t",
    "uint16": "uint16_t",
    "uint32": "uint32_t",
    "int8": "int8_t",
    "int16": "int16_t",
    "int32": "int32_t",
    "float": "float",
    "double": "double",
}

C_BLE_PROPERTIES = {
    BleCharacteristicProperty.BROADCAST: "PROTOCOL_BLE_PROPERTY_BROADCAST",
    BleCharacteristicProperty.READ: "PROTOCOL_BLE_PROPERTY_READ",
    BleCharacteristicProperty.WRITE_WITHOUT_RESPONSE: "PROTOCOL_BLE_PROPERTY_WRITE_WITHOUT_RESPONSE",
    BleCharacteristicProperty.WRITE: "PROTOCOL_BLE_PROPERTY_WRITE",
    BleCharacteristicProperty.NOTIFY: "PROTOCOL_BLE_PROPERTY_NOTIFY",
    BleCharacteristicProperty.INDICATE: "PROTOCOL_BLE_PROPERTY_INDICATE",
    BleCharacteristicProperty.AUTHENTICATED_SIGNED_WRITES: (
        "PROTOCOL_BLE_PROPERTY_AUTHENTICATED_SIGNED_WRITES"
    ),
    BleCharacteristicProperty.EXTENDED_PROPERTIES: "PROTOCOL_BLE_PROPERTY_EXTENDED_PROPERTIES",
}

ZEPHYR_BLE_PROPERTIES = {
    BleCharacteristicProperty.BROADCAST: "BT_GATT_CHRC_BROADCAST",
    BleCharacteristicProperty.READ: "BT_GATT_CHRC_READ",
    BleCharacteristicProperty.WRITE_WITHOUT_RESPONSE: "BT_GATT_CHRC_WRITE_WITHOUT_RESP",
    BleCharacteristicProperty.WRITE: "BT_GATT_CHRC_WRITE",
    BleCharacteristicProperty.NOTIFY: "BT_GATT_CHRC_NOTIFY",
    BleCharacteristicProperty.INDICATE: "BT_GATT_CHRC_INDICATE",
    BleCharacteristicProperty.AUTHENTICATED_SIGNED_WRITES: "BT_GATT_CHRC_AUTH",
    BleCharacteristicProperty.EXTENDED_PROPERTIES: "BT_GATT_CHRC_EXT_PROP",
}


class CEmitter(LanguageEmitter):
    """Emit C99-compatible declarations and codecs usable from C++."""

    def emit_runtime_files(self) -> tuple[GeneratedFile, ...]:
        """Emit the shared C protocol runtime."""

        return _CRuntimeRenderer().render()

    def emit_protocol_files(
        self,
        protocol: Protocol,
        schema_path: pathlib.Path,
    ) -> tuple[GeneratedFile, ...]:
        """Emit C header and source files for the protocol."""

        return _CRenderer(protocol, schema_path).render()

    def emit_collection_files(
        self,
        protocols: Sequence[Protocol],
    ) -> tuple[GeneratedFile, ...]:
        """Emit the CMake project for all generated C protocols."""

        source_names = [
            "protocol_runtime.c",
            *(f"{snake_case(protocol.name)}_protocol.c" for protocol in protocols),
        ]
        cmake_sources = "\n".join(
            f'    "src/{source_name}"'
            for source_name in source_names
        )
        return (
            GeneratedFile(
                pathlib.Path("c/CMakeLists.txt"),
                (
                    "# Generated CMake project. Do not edit by hand.\n"
                    "cmake_minimum_required(VERSION 3.10)\n\n"
                    "project(open_earable_protocols LANGUAGES C)\n\n"
                    "add_library(open_earable_protocols STATIC\n"
                    f"{cmake_sources}\n"
                    ")\n"
                    "add_library(OpenEarable::Protocols ALIAS open_earable_protocols)\n\n"
                    "target_compile_features(open_earable_protocols PUBLIC c_std_99)\n"
                    "target_include_directories(open_earable_protocols\n"
                    "    PUBLIC\n"
                    '        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"\n'
                    ")\n"
                ),
            ),
        )


class _CRuntimeRenderer:
    """Render the C runtime shared by every generated protocol."""

    def render(self) -> tuple[GeneratedFile, ...]:
        """Render the shared runtime header and source."""

        return (
            GeneratedFile(pathlib.Path("c/include/protocol_runtime.h"), self._header()),
            GeneratedFile(pathlib.Path("c/src/protocol_runtime.c"), self._source()),
        )

    def _header(self) -> str:
        declarations = "\n".join(
            [
                f"protocol_status_t protocol_write_{name}(protocol_writer_t *writer, {c_type} value);"
                for name, c_type in C_SCALAR_TYPES.items()
            ]
            + [
                f"protocol_status_t protocol_read_{name}(protocol_reader_t *reader, {c_type} *value);"
                for name, c_type in C_SCALAR_TYPES.items()
            ]
        )
        header = textwrap.dedent(
            f"""\
            // Generated shared protocol runtime. Do not edit by hand.
            #pragma once

            #include <stdbool.h>
            #include <stddef.h>
            #include <stdint.h>

            #define PROTOCOL_BLE_PROPERTY_BROADCAST 0x01u
            #define PROTOCOL_BLE_PROPERTY_READ 0x02u
            #define PROTOCOL_BLE_PROPERTY_WRITE_WITHOUT_RESPONSE 0x04u
            #define PROTOCOL_BLE_PROPERTY_WRITE 0x08u
            #define PROTOCOL_BLE_PROPERTY_NOTIFY 0x10u
            #define PROTOCOL_BLE_PROPERTY_INDICATE 0x20u
            #define PROTOCOL_BLE_PROPERTY_AUTHENTICATED_SIGNED_WRITES 0x40u
            #define PROTOCOL_BLE_PROPERTY_EXTENDED_PROPERTIES 0x80u

            #ifdef __cplusplus
            extern "C" {{
            #endif

            typedef enum {{
              PROTOCOL_OK = 0,
              PROTOCOL_ERROR_BUFFER_TOO_SMALL = 1,
              PROTOCOL_ERROR_INVALID_DATA = 2,
            }} protocol_status_t;

            typedef struct {{
              uint8_t *buffer;
              size_t size;
              size_t offset;
            }} protocol_writer_t;

            typedef struct {{
              const uint8_t *buffer;
              size_t size;
              size_t offset;
            }} protocol_reader_t;

            __SCALAR_DECLARATIONS__
            protocol_status_t protocol_write_bytes(protocol_writer_t *writer, const uint8_t *value, size_t length);
            protocol_status_t protocol_read_bytes(protocol_reader_t *reader, uint8_t *value, size_t length);

            #ifdef __cplusplus
            }}
            #endif

            """
        )
        return header.replace("__SCALAR_DECLARATIONS__", declarations)

    def _source(self) -> str:
        implementation = _CRenderer._runtime_source_template()
        implementation = re.sub(
            r"typedef struct \{.*?\} protocol_reader_t;\n\n",
            "",
            implementation,
            count=1,
            flags=re.DOTALL,
        )
        implementation = re.sub(
            r"#if defined\(__GNUC__\).*?#endif\n\n",
            "",
            implementation,
            count=1,
            flags=re.DOTALL,
        )
        implementation = implementation.replace("static inline PROTOCOL_UNUSED ", "")
        implementation = implementation.replace("bool protocol_can_", "static bool protocol_can_")
        implementation = implementation.replace(
            "protocol_status_t protocol_write_uint64",
            "static protocol_status_t protocol_write_uint64",
        )
        implementation = implementation.replace(
            "protocol_status_t protocol_read_uint64",
            "static protocol_status_t protocol_read_uint64",
        )
        return (
            "// Generated shared protocol runtime. Do not edit by hand.\n"
            '#include "protocol_runtime.h"\n\n'
            + implementation
        )


class _CRenderer:
    """Render one protocol schema into a C header and source pair."""

    def __init__(self, protocol: Protocol, schema_path: pathlib.Path) -> None:
        self.protocol = protocol
        self.schema_path = schema_path
        self.prefix = snake_case(protocol.name)

    def render(self) -> tuple[GeneratedFile, ...]:
        """Render the configured protocol into C header and source files."""

        protocol_slug = snake_case(self.protocol.name)
        header_name = f"{protocol_slug}_protocol.h"
        files = [
            GeneratedFile(pathlib.Path("c/include") / header_name, self.emit_header()),
            GeneratedFile(
                pathlib.Path("c/src") / f"{protocol_slug}_protocol.c",
                self.emit_source(header_name),
            ),
        ]
        if self.protocol.ble is not None:
            files.append(
                GeneratedFile(
                    pathlib.Path("c/include/zephyr") / f"{protocol_slug}_ble.h",
                    self._emit_zephyr_header(header_name),
                )
            )
        return tuple(files)

    def emit_header(self) -> str:
        guard = f"{self.prefix.upper()}_PROTOCOL_H"
        parts = [
            generated_banner(self.schema_path),
            f"#pragma once\n\n",
            '#include "protocol_runtime.h"\n\n',
        ]
        if self.protocol.ble is not None:
            parts.append(self._ble_uuid_macros())
        parts.append("#ifdef __cplusplus\nextern \"C\" {\n#endif\n\n")
        for message in self.protocol.messages:
            parts.append(self._header_struct(message))
        for message in self.protocol.messages:
            parts.append(self._header_union_api(message))
        for message in self.protocol.messages:
            c_name = self._c_message_name(message.name)
            description = self._message_description(message)
            parts.append(
                c_doc_comment(
                    f"Encode a binary representation of this message. {description}",
                    f"Encode a {message.name} message.",
                )
                + "\n"
            )
            parts.append(
                f"protocol_status_t {c_name}_encode(const {c_name}_t *message, "
                "uint8_t *buffer, size_t buffer_size, size_t *bytes_written);\n"
            )
            parts.append(
                c_doc_comment(
                    f"Decode a binary representation into this message. {description}",
                    f"Decode a {message.name} message.",
                )
                + "\n"
            )
            parts.append(
                f"protocol_status_t {c_name}_decode({c_name}_t *message, "
                "const uint8_t *buffer, size_t buffer_size, size_t *bytes_read);\n\n"
            )
        parts.append("#ifdef __cplusplus\n}\n#endif\n\n")
        return "".join(parts)

    def _ble_uuid_macros(self) -> str:
        """Render BLE service and characteristic UUID macros."""

        assert self.protocol.ble is not None
        macro_prefix = self.prefix.upper()
        lines = [
            f'#define {macro_prefix}_BLE_SERVICE_UUID "{self.protocol.ble.service_uuid}"',
        ]
        for characteristic in self.protocol.ble.characteristics:
            characteristic_name = snake_case(characteristic.name).upper()
            properties = _c_property_expression(characteristic.properties, C_BLE_PROPERTIES, "0u")
            lines.append(
                f'#define {macro_prefix}_BLE_{characteristic_name}_CHARACTERISTIC_UUID '
                f'"{characteristic.uuid}"'
            )
            lines.append(
                f"#define {macro_prefix}_BLE_{characteristic_name}_CHARACTERISTIC_PROPERTIES "
                f"({properties})"
            )
        return "\n".join(lines) + "\n\n"

    def _emit_zephyr_header(self, protocol_header_name: str) -> str:
        """Render optional Zephyr UUID, property, and permission adapters."""

        assert self.protocol.ble is not None
        macro_prefix = self.prefix.upper()
        guard = f"{macro_prefix}_ZEPHYR_BLE_H"
        lines = [
            generated_banner(self.schema_path).rstrip(),
            f"#pragma once",
            "",
            f'#include "{protocol_header_name}"',
            "#include <zephyr/bluetooth/gatt.h>",
            "#include <zephyr/bluetooth/uuid.h>",
            "",
            f"#define {macro_prefix}_ZEPHYR_SERVICE_UUID "
            f"{_zephyr_uuid_expression(self.protocol.ble.service_uuid)}",
        ]
        for characteristic in self.protocol.ble.characteristics:
            name = snake_case(characteristic.name).upper()
            properties = _c_property_expression(characteristic.properties, ZEPHYR_BLE_PROPERTIES, "0")
            permissions = _zephyr_permission_expression(characteristic.properties)
            lines.extend(
                [
                    "",
                    f"#define {macro_prefix}_ZEPHYR_{name}_CHARACTERISTIC_UUID "
                    f"{_zephyr_uuid_expression(characteristic.uuid)}",
                    f"#define {macro_prefix}_ZEPHYR_{name}_CHARACTERISTIC_PROPERTIES "
                    f"({properties})",
                    f"#define {macro_prefix}_ZEPHYR_{name}_CHARACTERISTIC_PERMISSIONS "
                    f"({permissions})",
                ]
            )
        lines.extend([""])
        return "\n".join(lines)

    def emit_source(self, header_name: str) -> str:
        parts = [
            generated_banner(self.schema_path),
            f'#include "{header_name}"\n\n',
        ]
        for message in self.protocol.messages:
            parts.append(self._source_union_api(message))
            parts.append(self._source_message(message))
        return "".join(parts)

    def _header_struct(self, message: Message) -> str:
        c_name = self._c_message_name(message.name)
        documentation = c_doc_comment(
            message.description,
            self._message_description(message),
        )
        lines: list[str] = []
        for field in self._union_fields(message):
            field_type = field.type
            assert isinstance(field_type, UnionType)
            enum_name = self._union_enum_name(message, field)
            lines.extend([f"typedef enum {enum_name} {{\n"])
            for variant in field_type.variants:
                lines.append(
                    f"  {self._union_enum_constant(message, field, variant.message.name)} = "
                    f"{variant.tag},\n"
                )
            lines.append(f"}} {enum_name};\n\n")
        lines.extend([f"{documentation}\n", f"typedef struct {c_name}_t {c_name}_t;\n"])
        body = [f"struct {c_name}_t {{"]
        for field in message.fields:
            body.extend(self._field_declaration(message, field))
        body.append("};\n\n")
        return "".join(lines + [line + "\n" for line in body])

    def _header_union_api(self, message: Message) -> str:
        """Render typed constructors and visitor declarations for union messages."""

        c_name = self._c_message_name(message.name)
        lines: list[str] = []
        for field in self._union_fields(message):
            field_type = field.type
            assert isinstance(field_type, UnionType)
            handler_name = self._union_handler_name(message, field)
            lines.extend(
                [
                    f"/** Typed handlers used to dispatch {message.name}.{field.name}. */",
                    f"typedef struct {handler_name} {{",
                ]
            )
            for variant in field_type.variants:
                variant_name = variant.message.name
                lines.append(
                    f"  protocol_status_t (*{self._short_variant_name(message, variant_name)})"
                    f"(void *context, const {self._c_message_name(variant_name)}_t *command);"
                )
            lines.extend([f"}} {handler_name};", ""])
            for variant in field_type.variants:
                variant_name = variant.message.name
                short_name = self._short_variant_name(message, variant_name)
                lines.extend(
                    [
                        f"/** Set {message.name}.{field.name} to {variant_name}. */",
                        f"void {self._union_setter_name(message, field, short_name)}("
                        f"{c_name}_t *message, {self._c_message_name(variant_name)}_t command);",
                    ]
                )
                if len(message.fields) == 1:
                    lines.extend(
                        [
                            f"/** Build a {message.name} message containing {variant_name}. */",
                            f"{c_name}_t {c_name}_from_{short_name}("
                            f"{self._c_message_name(variant_name)}_t command);",
                        ]
                    )
            lines.extend(
                [
                    f"/** Dispatch {message.name}.{field.name} to its typed handler. */",
                    f"protocol_status_t {self._union_dispatch_name(message, field)}("
                    f"const {c_name}_t *message, const {handler_name} *handler, void *context);",
                    "",
                ]
            )
        return "\n".join(lines) + ("\n" if lines else "")

    def _message_description(self, message: Message) -> str:
        """Return schema documentation or a stable generated fallback."""

        return message.description or (
            f"{pascal_case(message.name)} message for the {self.protocol.name} protocol."
        )

    def _field_declaration(self, message: Message, field: Field) -> list[str]:
        field_type = field.type
        if isinstance(field_type, ScalarType):
            return [f"  {C_SCALAR_TYPES[field_type.name]} {field.name};"]
        if isinstance(field_type, BytesType):
            return [f"  uint8_t *{field.name};"]
        if isinstance(field_type, ArrayType):
            return [f"  {C_SCALAR_TYPES[field_type.item_type.name]} *{field.name};"]
        if isinstance(field_type, MessageRefType):
            return [f"  {self._c_message_name(field_type.name)}_t {field.name};"]
        if isinstance(field_type, UnionType):
            lines = [
                f"  {self._union_enum_name(message, field)} "
                f"{self._union_discriminator_name(message, field)};",
                "  union {",
            ]
            for variant in field_type.variants:
                lines.append(
                    f"    {self._c_message_name(variant.message.name)}_t {variant.message.name};"
                )
            lines.append(f"  }} {field.name};")
            return lines
        raise AssertionError(field_type)

    @staticmethod
    def _runtime_source_template() -> str:
        return textwrap.dedent(
            f"""
            #include <string.h>

            typedef struct {{
              uint8_t *buffer;
              size_t size;
              size_t offset;
            }} protocol_writer_t;

            typedef struct {{
              const uint8_t *buffer;
              size_t size;
              size_t offset;
            }} protocol_reader_t;

            #if defined(__GNUC__) || defined(__clang__)
            #define PROTOCOL_UNUSED __attribute__((unused))
            #else
            #define PROTOCOL_UNUSED
            #endif

            typedef char protocol_float_must_be_4_bytes[(sizeof(float) == 4) ? 1 : -1];
            typedef char protocol_double_must_be_8_bytes[(sizeof(double) == 8) ? 1 : -1];

            static inline PROTOCOL_UNUSED bool protocol_can_write(protocol_writer_t *writer, size_t length) {{
              return writer->offset <= writer->size && length <= writer->size - writer->offset;
            }}

            static inline PROTOCOL_UNUSED bool protocol_can_read(protocol_reader_t *reader, size_t length) {{
              return reader->offset <= reader->size && length <= reader->size - reader->offset;
            }}

            static inline PROTOCOL_UNUSED protocol_status_t protocol_write_uint8(protocol_writer_t *writer, uint8_t value) {{
              if (!protocol_can_write(writer, 1)) {{
                return PROTOCOL_ERROR_BUFFER_TOO_SMALL;
              }}
              writer->buffer[writer->offset++] = value;
              return PROTOCOL_OK;
            }}

            static inline PROTOCOL_UNUSED protocol_status_t protocol_write_int8(protocol_writer_t *writer, int8_t value) {{
              return protocol_write_uint8(writer, (uint8_t)value);
            }}

            static inline PROTOCOL_UNUSED protocol_status_t protocol_write_uint16(protocol_writer_t *writer, uint16_t value) {{
              if (!protocol_can_write(writer, 2)) {{
                return PROTOCOL_ERROR_BUFFER_TOO_SMALL;
              }}
              writer->buffer[writer->offset++] = (uint8_t)(value & 0xffu);
              writer->buffer[writer->offset++] = (uint8_t)((value >> 8u) & 0xffu);
              return PROTOCOL_OK;
            }}

            static inline PROTOCOL_UNUSED protocol_status_t protocol_write_int16(protocol_writer_t *writer, int16_t value) {{
              return protocol_write_uint16(writer, (uint16_t)value);
            }}

            static inline PROTOCOL_UNUSED protocol_status_t protocol_write_uint32(protocol_writer_t *writer, uint32_t value) {{
              if (!protocol_can_write(writer, 4)) {{
                return PROTOCOL_ERROR_BUFFER_TOO_SMALL;
              }}
              writer->buffer[writer->offset++] = (uint8_t)(value & 0xffu);
              writer->buffer[writer->offset++] = (uint8_t)((value >> 8u) & 0xffu);
              writer->buffer[writer->offset++] = (uint8_t)((value >> 16u) & 0xffu);
              writer->buffer[writer->offset++] = (uint8_t)((value >> 24u) & 0xffu);
              return PROTOCOL_OK;
            }}

            static inline PROTOCOL_UNUSED protocol_status_t protocol_write_int32(protocol_writer_t *writer, int32_t value) {{
              return protocol_write_uint32(writer, (uint32_t)value);
            }}

            static inline PROTOCOL_UNUSED protocol_status_t protocol_write_uint64(protocol_writer_t *writer, uint64_t value) {{
              if (!protocol_can_write(writer, 8)) {{
                return PROTOCOL_ERROR_BUFFER_TOO_SMALL;
              }}
              for (size_t index = 0; index < 8; ++index) {{
                writer->buffer[writer->offset++] = (uint8_t)((value >> (index * 8u)) & 0xffu);
              }}
              return PROTOCOL_OK;
            }}

            static inline PROTOCOL_UNUSED protocol_status_t protocol_write_float(protocol_writer_t *writer, float value) {{
              uint32_t bits;
              memcpy(&bits, &value, sizeof(bits));
              return protocol_write_uint32(writer, bits);
            }}

            static inline PROTOCOL_UNUSED protocol_status_t protocol_write_double(protocol_writer_t *writer, double value) {{
              uint64_t bits;
              memcpy(&bits, &value, sizeof(bits));
              return protocol_write_uint64(writer, bits);
            }}

            static inline PROTOCOL_UNUSED protocol_status_t protocol_read_uint8(protocol_reader_t *reader, uint8_t *value) {{
              if (!protocol_can_read(reader, 1)) {{
                return PROTOCOL_ERROR_INVALID_DATA;
              }}
              *value = reader->buffer[reader->offset++];
              return PROTOCOL_OK;
            }}

            static inline PROTOCOL_UNUSED protocol_status_t protocol_read_int8(protocol_reader_t *reader, int8_t *value) {{
              uint8_t raw_value;
              protocol_status_t status = protocol_read_uint8(reader, &raw_value);
              if (status != PROTOCOL_OK) {{
                return status;
              }}
              *value = (int8_t)raw_value;
              return PROTOCOL_OK;
            }}

            static inline PROTOCOL_UNUSED protocol_status_t protocol_read_uint16(protocol_reader_t *reader, uint16_t *value) {{
              if (!protocol_can_read(reader, 2)) {{
                return PROTOCOL_ERROR_INVALID_DATA;
              }}
              *value = (uint16_t)reader->buffer[reader->offset]
                  | ((uint16_t)reader->buffer[reader->offset + 1] << 8u);
              reader->offset += 2;
              return PROTOCOL_OK;
            }}

            static inline PROTOCOL_UNUSED protocol_status_t protocol_read_int16(protocol_reader_t *reader, int16_t *value) {{
              uint16_t raw_value;
              protocol_status_t status = protocol_read_uint16(reader, &raw_value);
              if (status != PROTOCOL_OK) {{
                return status;
              }}
              *value = (int16_t)raw_value;
              return PROTOCOL_OK;
            }}

            static inline PROTOCOL_UNUSED protocol_status_t protocol_read_uint32(protocol_reader_t *reader, uint32_t *value) {{
              if (!protocol_can_read(reader, 4)) {{
                return PROTOCOL_ERROR_INVALID_DATA;
              }}
              *value = (uint32_t)reader->buffer[reader->offset]
                  | ((uint32_t)reader->buffer[reader->offset + 1] << 8u)
                  | ((uint32_t)reader->buffer[reader->offset + 2] << 16u)
                  | ((uint32_t)reader->buffer[reader->offset + 3] << 24u);
              reader->offset += 4;
              return PROTOCOL_OK;
            }}

            static inline PROTOCOL_UNUSED protocol_status_t protocol_read_int32(protocol_reader_t *reader, int32_t *value) {{
              uint32_t raw_value;
              protocol_status_t status = protocol_read_uint32(reader, &raw_value);
              if (status != PROTOCOL_OK) {{
                return status;
              }}
              *value = (int32_t)raw_value;
              return PROTOCOL_OK;
            }}

            static inline PROTOCOL_UNUSED protocol_status_t protocol_read_uint64(protocol_reader_t *reader, uint64_t *value) {{
              if (!protocol_can_read(reader, 8)) {{
                return PROTOCOL_ERROR_INVALID_DATA;
              }}
              *value = 0;
              for (size_t index = 0; index < 8; ++index) {{
                *value |= (uint64_t)reader->buffer[reader->offset + index] << (index * 8u);
              }}
              reader->offset += 8;
              return PROTOCOL_OK;
            }}

            static inline PROTOCOL_UNUSED protocol_status_t protocol_read_float(protocol_reader_t *reader, float *value) {{
              uint32_t bits;
              protocol_status_t status = protocol_read_uint32(reader, &bits);
              if (status != PROTOCOL_OK) {{
                return status;
              }}
              memcpy(value, &bits, sizeof(bits));
              return PROTOCOL_OK;
            }}

            static inline PROTOCOL_UNUSED protocol_status_t protocol_read_double(protocol_reader_t *reader, double *value) {{
              uint64_t bits;
              protocol_status_t status = protocol_read_uint64(reader, &bits);
              if (status != PROTOCOL_OK) {{
                return status;
              }}
              memcpy(value, &bits, sizeof(bits));
              return PROTOCOL_OK;
            }}

            static inline PROTOCOL_UNUSED protocol_status_t protocol_write_bytes(protocol_writer_t *writer, const uint8_t *value, size_t length) {{
              if (!protocol_can_write(writer, length)) {{
                return PROTOCOL_ERROR_BUFFER_TOO_SMALL;
              }}
              for (size_t index = 0; index < length; ++index) {{
                writer->buffer[writer->offset++] = value[index];
              }}
              return PROTOCOL_OK;
            }}

            static inline PROTOCOL_UNUSED protocol_status_t protocol_read_bytes(protocol_reader_t *reader, uint8_t *value, size_t length) {{
              if (!protocol_can_read(reader, length)) {{
                return PROTOCOL_ERROR_INVALID_DATA;
              }}
              for (size_t index = 0; index < length; ++index) {{
                value[index] = reader->buffer[reader->offset++];
              }}
              return PROTOCOL_OK;
            }}

            """
        )

    def _source_message(self, message: Message) -> str:
        c_name = self._c_message_name(message.name)
        return (
            f"static protocol_status_t {c_name}_write(protocol_writer_t *writer, "
            f"const {c_name}_t *message) {{\n"
            f"{_indent(self._c_write_lines(message), 2)}\n"
            f"  return PROTOCOL_OK;\n"
            "}\n\n"
            f"static protocol_status_t {c_name}_read(protocol_reader_t *reader, "
            f"{c_name}_t *message) {{\n"
            f"{_indent(self._c_read_lines(message), 2)}\n"
            f"  return PROTOCOL_OK;\n"
            "}\n\n"
            f"protocol_status_t {c_name}_encode(const {c_name}_t *message, uint8_t *buffer, "
            "size_t buffer_size, size_t *bytes_written) {\n"
            f"  protocol_writer_t writer = {{ buffer, buffer_size, 0 }};\n"
            f"  protocol_status_t status = {c_name}_write(&writer, message);\n"
            f"  if (status != PROTOCOL_OK) {{\n"
            "    return status;\n"
            "  }\n"
            "  if (bytes_written != NULL) {\n"
            "    *bytes_written = writer.offset;\n"
            "  }\n"
            f"  return PROTOCOL_OK;\n"
            "}\n\n"
            f"protocol_status_t {c_name}_decode({c_name}_t *message, const uint8_t *buffer, "
            "size_t buffer_size, size_t *bytes_read) {\n"
            f"  protocol_reader_t reader = {{ buffer, buffer_size, 0 }};\n"
            f"  protocol_status_t status = {c_name}_read(&reader, message);\n"
            f"  if (status != PROTOCOL_OK) {{\n"
            "    return status;\n"
            "  }\n"
            "  if (bytes_read != NULL) {\n"
            "    *bytes_read = reader.offset;\n"
            "  }\n"
            f"  return PROTOCOL_OK;\n"
            "}\n\n"
        )

    def _source_union_api(self, message: Message) -> str:
        """Render typed constructors and centralized visitor dispatch."""

        c_name = self._c_message_name(message.name)
        lines: list[str] = []
        for field in self._union_fields(message):
            field_type = field.type
            assert isinstance(field_type, UnionType)
            discriminator = self._union_discriminator_name(message, field)
            for variant in field_type.variants:
                variant_name = variant.message.name
                short_name = self._short_variant_name(message, variant_name)
                setter_name = self._union_setter_name(message, field, short_name)
                lines.extend(
                    [
                        f"void {setter_name}({c_name}_t *message, "
                        f"{self._c_message_name(variant_name)}_t command) {{",
                        "  if (message == NULL) {",
                        "    return;",
                        "  }",
                        f"  message->{discriminator} = "
                        f"{self._union_enum_constant(message, field, variant_name)};",
                        f"  message->{field.name}.{variant_name} = command;",
                        "}",
                        "",
                    ]
                )
                if len(message.fields) == 1:
                    lines.extend(
                        [
                            f"{c_name}_t {c_name}_from_{short_name}("
                            f"{self._c_message_name(variant_name)}_t command) {{",
                            f"  {c_name}_t message = {{0}};",
                            f"  {setter_name}(&message, command);",
                            "  return message;",
                            "}",
                            "",
                        ]
                    )
            lines.extend(
                [
                    f"protocol_status_t {self._union_dispatch_name(message, field)}("
                    f"const {c_name}_t *message, "
                    f"const {self._union_handler_name(message, field)} *handler, "
                    "void *context) {",
                    "  if (message == NULL || handler == NULL) {",
                    "    return PROTOCOL_ERROR_INVALID_DATA;",
                    "  }",
                    f"  switch (message->{discriminator}) {{",
                ]
            )
            for variant in field_type.variants:
                variant_name = variant.message.name
                short_name = self._short_variant_name(message, variant_name)
                lines.extend(
                    [
                        f"  case {self._union_enum_constant(message, field, variant_name)}:",
                        f"    if (handler->{short_name} == NULL) {{",
                        "      return PROTOCOL_ERROR_INVALID_DATA;",
                        "    }",
                        f"    return handler->{short_name}(context, "
                        f"&message->{field.name}.{variant_name});",
                    ]
                )
            lines.extend(
                [
                    "  default:",
                    "    return PROTOCOL_ERROR_INVALID_DATA;",
                    "  }",
                    "}",
                    "",
                ]
            )
        return "\n".join(lines) + ("\n" if lines else "")

    def _c_write_lines(self, message: Message) -> str:
        lines: list[str] = [f"protocol_status_t status;"]
        for field in message.fields:
            lines.extend(self._c_write_field(message, field))
        return "\n".join(lines)

    def _c_write_field(self, message: Message, field: Field) -> list[str]:
        field_type = field.type
        if isinstance(field_type, ScalarType):
            return [
                f"status = protocol_write_{field_type.name}(writer, message->{field.name});",
                f"if (status != PROTOCOL_OK) return status;",
            ]
        if isinstance(field_type, BytesType):
            return [
                f"status = protocol_write_bytes(writer, message->{field.name}, message->{field_type.length_field});",
                f"if (status != PROTOCOL_OK) return status;",
            ]
        if isinstance(field_type, ArrayType):
            return [
                f"for (size_t index = 0; index < message->{field_type.length_field}; ++index) {{",
                f"  status = protocol_write_{field_type.item_type.name}(writer, message->{field.name}[index]);",
                f"  if (status != PROTOCOL_OK) return status;",
                "}",
            ]
        if isinstance(field_type, MessageRefType):
            return [
                f"status = {self._c_message_name(field_type.name)}_write(writer, &message->{field.name});",
                f"if (status != PROTOCOL_OK) return status;",
            ]
        if isinstance(field_type, UnionType):
            discriminator = self._union_discriminator_name(message, field)
            lines = [
                f"status = protocol_write_{field_type.tag_type.name}(writer, "
                f"message->{discriminator});",
                "if (status != PROTOCOL_OK) return status;",
                f"switch (message->{discriminator}) {{",
            ]
            for variant in field_type.variants:
                lines.extend(
                    [
                        f"case {self._union_enum_constant(message, field, variant.message.name)}:",
                        f"  status = {self._c_message_name(variant.message.name)}_write(writer, "
                        f"&message->{field.name}.{variant.message.name});",
                        f"  if (status != PROTOCOL_OK) return status;",
                        "  break;",
                    ]
                )
            lines.extend(["default:", f"  return PROTOCOL_ERROR_INVALID_DATA;", "}"])
            return lines
        raise AssertionError(field_type)

    def _c_read_lines(self, message: Message) -> str:
        lines = [f"protocol_status_t status;"]
        for field in message.fields:
            lines.extend(self._c_read_field(message, field))
        return "\n".join(lines)

    def _c_read_field(self, message: Message, field: Field) -> list[str]:
        field_type = field.type
        if isinstance(field_type, ScalarType):
            return [
                f"status = protocol_read_{field_type.name}(reader, &message->{field.name});",
                f"if (status != PROTOCOL_OK) return status;",
            ]
        if isinstance(field_type, BytesType):
            return [
                f"status = protocol_read_bytes(reader, message->{field.name}, message->{field_type.length_field});",
                f"if (status != PROTOCOL_OK) return status;",
            ]
        if isinstance(field_type, ArrayType):
            return [
                f"for (size_t index = 0; index < message->{field_type.length_field}; ++index) {{",
                f"  status = protocol_read_{field_type.item_type.name}(reader, &message->{field.name}[index]);",
                f"  if (status != PROTOCOL_OK) return status;",
                "}",
            ]
        if isinstance(field_type, MessageRefType):
            return [
                f"status = {self._c_message_name(field_type.name)}_read(reader, &message->{field.name});",
                f"if (status != PROTOCOL_OK) return status;",
            ]
        if isinstance(field_type, UnionType):
            discriminator = self._union_discriminator_name(message, field)
            raw_type = C_SCALAR_TYPES[field_type.tag_type.name]
            enum_name = self._union_enum_name(message, field)
            lines = [
                f"{raw_type} raw_{discriminator};",
                f"status = protocol_read_{field_type.tag_type.name}(reader, &raw_{discriminator});",
                "if (status != PROTOCOL_OK) return status;",
                f"message->{discriminator} = ({enum_name})raw_{discriminator};",
                f"switch (message->{discriminator}) {{",
            ]
            for variant in field_type.variants:
                lines.extend(
                    [
                        f"case {self._union_enum_constant(message, field, variant.message.name)}:",
                        f"  status = {self._c_message_name(variant.message.name)}_read(reader, "
                        f"&message->{field.name}.{variant.message.name});",
                        f"  if (status != PROTOCOL_OK) return status;",
                        "  break;",
                    ]
                )
            lines.extend(["default:", f"  return PROTOCOL_ERROR_INVALID_DATA;", "}"])
            return lines
        raise AssertionError(field_type)

    def _c_message_name(self, message_name: str) -> str:
        return f"{self.prefix}_{snake_case(message_name)}"

    @staticmethod
    def _union_fields(message: Message) -> tuple[Field, ...]:
        """Return the tagged-union fields declared by a message."""

        return tuple(field for field in message.fields if isinstance(field.type, UnionType))

    def _union_discriminator_name(self, message: Message, field: Field) -> str:
        """Return a concise discriminator name without causing field collisions."""

        return "type" if len(self._union_fields(message)) == 1 else f"{field.name}_type"

    def _union_enum_name(self, message: Message, field: Field) -> str:
        """Return the generated C enum type for a tagged union."""

        suffix = "type" if len(self._union_fields(message)) == 1 else f"{field.name}_type"
        return f"{self._c_message_name(message.name)}_{suffix}_t"

    def _union_enum_constant(self, message: Message, field: Field, variant_name: str) -> str:
        """Return the generated enum constant for a union variant."""

        parts = [self.prefix, message.name]
        if len(self._union_fields(message)) != 1:
            parts.append(field.name)
        parts.append(self._short_variant_name(message, variant_name))
        return snake_case("_".join(parts)).upper()

    def _union_handler_name(self, message: Message, field: Field) -> str:
        """Return the typed visitor structure name for a union field."""

        suffix = "" if len(self._union_fields(message)) == 1 else f"_{field.name}"
        return f"{self._c_message_name(message.name)}{suffix}_handler_t"

    def _union_dispatch_name(self, message: Message, field: Field) -> str:
        """Return the typed visitor function name for a union field."""

        suffix = "" if len(self._union_fields(message)) == 1 else f"_{field.name}"
        return f"{self._c_message_name(message.name)}_dispatch{suffix}"

    def _union_setter_name(self, message: Message, field: Field, variant_name: str) -> str:
        """Return the typed union setter name."""

        return f"{self._c_message_name(message.name)}_set_{field.name}_{variant_name}"

    @staticmethod
    def _short_variant_name(message: Message, variant_name: str) -> str:
        """Remove a shared message prefix from a variant for concise APIs."""

        prefix = f"{message.name.removesuffix('_control')}_"
        return variant_name.removeprefix(prefix)


def _c_property_expression(
    properties: Sequence[BleCharacteristicProperty],
    mapping: Mapping[BleCharacteristicProperty, str],
    empty_value: str,
) -> str:
    """Render a C bitwise-or expression for BLE characteristic properties."""

    return " | ".join(mapping[property_value] for property_value in properties) or empty_value


def _zephyr_permission_expression(properties: Sequence[BleCharacteristicProperty]) -> str:
    """Derive default Zephyr attribute permissions from GATT properties."""

    permissions: list[str] = []
    if BleCharacteristicProperty.READ in properties:
        permissions.append("BT_GATT_PERM_READ")
    if any(
        property_value in properties
        for property_value in (
            BleCharacteristicProperty.WRITE,
            BleCharacteristicProperty.WRITE_WITHOUT_RESPONSE,
            BleCharacteristicProperty.AUTHENTICATED_SIGNED_WRITES,
        )
    ):
        permissions.append("BT_GATT_PERM_WRITE")
    return " | ".join(permissions) or "BT_GATT_PERM_NONE"


def _zephyr_uuid_expression(uuid_value: str) -> str:
    """Render a Zephyr inline UUID declaration for a normalized BLE UUID."""

    if len(uuid_value) == 4:
        return f"BT_UUID_DECLARE_16(0x{uuid_value})"
    if len(uuid_value) == 8:
        return f"BT_UUID_DECLARE_32(0x{uuid_value})"

    word32, word1, word2, word3, word48 = uuid_value.split("-")
    return (
        "BT_UUID_DECLARE_128(BT_UUID_128_ENCODE("
        f"0x{word32}, 0x{word1}, 0x{word2}, 0x{word3}, 0x{word48}))"
    )

"""C and C++ compatible protocol emitter."""

from __future__ import annotations

import pathlib
import textwrap

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
from protocol_generator.naming import generated_banner, snake_case
from protocol_generator.output import GeneratedFile
from protocol_generator.text import _indent


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


class CEmitter(LanguageEmitter):
    """Emit C99-compatible declarations and codecs usable from C++."""

    def emit_files(self, protocol: Protocol, schema_path: pathlib.Path) -> tuple[GeneratedFile, ...]:
        """Emit C header and source files for the protocol."""

        return _CRenderer(protocol, schema_path).render()


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
        return (
            GeneratedFile(pathlib.Path("c") / header_name, self.emit_header()),
            GeneratedFile(
                pathlib.Path("c") / f"{protocol_slug}_protocol.c",
                self.emit_source(header_name),
            ),
        )

    def emit_header(self) -> str:
        guard = f"{self.prefix.upper()}_PROTOCOL_H"
        parts = [
            generated_banner(self.schema_path),
            f"#ifndef {guard}\n#define {guard}\n\n",
            "#include <stdbool.h>\n#include <stddef.h>\n#include <stdint.h>\n\n",
            "#ifdef __cplusplus\nextern \"C\" {\n#endif\n\n",
            "typedef enum {\n"
            f"  {self.prefix.upper()}_OK = 0,\n"
            f"  {self.prefix.upper()}_ERROR_BUFFER_TOO_SMALL = 1,\n"
            f"  {self.prefix.upper()}_ERROR_INVALID_DATA = 2,\n"
            f"}} {self.prefix}_status_t;\n\n",
        ]
        for message in self.protocol.messages:
            parts.append(self._header_struct(message))
        for message in self.protocol.messages:
            c_name = self._c_message_name(message.name)
            parts.append(
                f"{self.prefix}_status_t {c_name}_encode(const {c_name}_t *message, "
                "uint8_t *buffer, size_t buffer_size, size_t *bytes_written);\n"
            )
            parts.append(
                f"{self.prefix}_status_t {c_name}_decode({c_name}_t *message, "
                "const uint8_t *buffer, size_t buffer_size, size_t *bytes_read);\n\n"
            )
        parts.append("#ifdef __cplusplus\n}\n#endif\n\n")
        parts.append(f"#endif /* {guard} */\n")
        return "".join(parts)

    def emit_source(self, header_name: str) -> str:
        parts = [
            generated_banner(self.schema_path),
            f'#include "{header_name}"\n\n',
            self._support_code(),
        ]
        for message in self.protocol.messages:
            parts.append(self._source_message(message))
        return "".join(parts)

    def _header_struct(self, message: Message) -> str:
        c_name = self._c_message_name(message.name)
        lines = [f"typedef struct {c_name}_t {c_name}_t;\n"]
        body = [f"struct {c_name}_t {{"]
        for field in message.fields:
            body.extend(self._field_declaration(field))
        body.append("};\n\n")
        return "".join(lines + [line + "\n" for line in body])

    def _field_declaration(self, field: Field) -> list[str]:
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
            lines = ["  union {"]
            for variant in field_type.variants:
                lines.append(f"    {self._c_message_name(variant.name)}_t {variant.name};")
            lines.append(f"  }} {field.name};")
            return lines
        raise AssertionError(field_type)

    def _support_code(self) -> str:
        return textwrap.dedent(
            f"""
            #include <string.h>

            typedef struct {{
              uint8_t *buffer;
              size_t size;
              size_t offset;
            }} {self.prefix}_writer_t;

            typedef struct {{
              const uint8_t *buffer;
              size_t size;
              size_t offset;
            }} {self.prefix}_reader_t;

            #if defined(__GNUC__) || defined(__clang__)
            #define {self.prefix.upper()}_UNUSED __attribute__((unused))
            #else
            #define {self.prefix.upper()}_UNUSED
            #endif

            typedef char {self.prefix}_float_must_be_4_bytes[(sizeof(float) == 4) ? 1 : -1];
            typedef char {self.prefix}_double_must_be_8_bytes[(sizeof(double) == 8) ? 1 : -1];

            static inline {self.prefix.upper()}_UNUSED bool {self.prefix}_can_write({self.prefix}_writer_t *writer, size_t length) {{
              return writer->offset <= writer->size && length <= writer->size - writer->offset;
            }}

            static inline {self.prefix.upper()}_UNUSED bool {self.prefix}_can_read({self.prefix}_reader_t *reader, size_t length) {{
              return reader->offset <= reader->size && length <= reader->size - reader->offset;
            }}

            static inline {self.prefix.upper()}_UNUSED {self.prefix}_status_t {self.prefix}_write_uint8({self.prefix}_writer_t *writer, uint8_t value) {{
              if (!{self.prefix}_can_write(writer, 1)) {{
                return {self.prefix.upper()}_ERROR_BUFFER_TOO_SMALL;
              }}
              writer->buffer[writer->offset++] = value;
              return {self.prefix.upper()}_OK;
            }}

            static inline {self.prefix.upper()}_UNUSED {self.prefix}_status_t {self.prefix}_write_int8({self.prefix}_writer_t *writer, int8_t value) {{
              return {self.prefix}_write_uint8(writer, (uint8_t)value);
            }}

            static inline {self.prefix.upper()}_UNUSED {self.prefix}_status_t {self.prefix}_write_uint16({self.prefix}_writer_t *writer, uint16_t value) {{
              if (!{self.prefix}_can_write(writer, 2)) {{
                return {self.prefix.upper()}_ERROR_BUFFER_TOO_SMALL;
              }}
              writer->buffer[writer->offset++] = (uint8_t)(value & 0xffu);
              writer->buffer[writer->offset++] = (uint8_t)((value >> 8u) & 0xffu);
              return {self.prefix.upper()}_OK;
            }}

            static inline {self.prefix.upper()}_UNUSED {self.prefix}_status_t {self.prefix}_write_int16({self.prefix}_writer_t *writer, int16_t value) {{
              return {self.prefix}_write_uint16(writer, (uint16_t)value);
            }}

            static inline {self.prefix.upper()}_UNUSED {self.prefix}_status_t {self.prefix}_write_uint32({self.prefix}_writer_t *writer, uint32_t value) {{
              if (!{self.prefix}_can_write(writer, 4)) {{
                return {self.prefix.upper()}_ERROR_BUFFER_TOO_SMALL;
              }}
              writer->buffer[writer->offset++] = (uint8_t)(value & 0xffu);
              writer->buffer[writer->offset++] = (uint8_t)((value >> 8u) & 0xffu);
              writer->buffer[writer->offset++] = (uint8_t)((value >> 16u) & 0xffu);
              writer->buffer[writer->offset++] = (uint8_t)((value >> 24u) & 0xffu);
              return {self.prefix.upper()}_OK;
            }}

            static inline {self.prefix.upper()}_UNUSED {self.prefix}_status_t {self.prefix}_write_int32({self.prefix}_writer_t *writer, int32_t value) {{
              return {self.prefix}_write_uint32(writer, (uint32_t)value);
            }}

            static inline {self.prefix.upper()}_UNUSED {self.prefix}_status_t {self.prefix}_write_uint64({self.prefix}_writer_t *writer, uint64_t value) {{
              if (!{self.prefix}_can_write(writer, 8)) {{
                return {self.prefix.upper()}_ERROR_BUFFER_TOO_SMALL;
              }}
              for (size_t index = 0; index < 8; ++index) {{
                writer->buffer[writer->offset++] = (uint8_t)((value >> (index * 8u)) & 0xffu);
              }}
              return {self.prefix.upper()}_OK;
            }}

            static inline {self.prefix.upper()}_UNUSED {self.prefix}_status_t {self.prefix}_write_float({self.prefix}_writer_t *writer, float value) {{
              uint32_t bits;
              memcpy(&bits, &value, sizeof(bits));
              return {self.prefix}_write_uint32(writer, bits);
            }}

            static inline {self.prefix.upper()}_UNUSED {self.prefix}_status_t {self.prefix}_write_double({self.prefix}_writer_t *writer, double value) {{
              uint64_t bits;
              memcpy(&bits, &value, sizeof(bits));
              return {self.prefix}_write_uint64(writer, bits);
            }}

            static inline {self.prefix.upper()}_UNUSED {self.prefix}_status_t {self.prefix}_read_uint8({self.prefix}_reader_t *reader, uint8_t *value) {{
              if (!{self.prefix}_can_read(reader, 1)) {{
                return {self.prefix.upper()}_ERROR_INVALID_DATA;
              }}
              *value = reader->buffer[reader->offset++];
              return {self.prefix.upper()}_OK;
            }}

            static inline {self.prefix.upper()}_UNUSED {self.prefix}_status_t {self.prefix}_read_int8({self.prefix}_reader_t *reader, int8_t *value) {{
              uint8_t raw_value;
              {self.prefix}_status_t status = {self.prefix}_read_uint8(reader, &raw_value);
              if (status != {self.prefix.upper()}_OK) {{
                return status;
              }}
              *value = (int8_t)raw_value;
              return {self.prefix.upper()}_OK;
            }}

            static inline {self.prefix.upper()}_UNUSED {self.prefix}_status_t {self.prefix}_read_uint16({self.prefix}_reader_t *reader, uint16_t *value) {{
              if (!{self.prefix}_can_read(reader, 2)) {{
                return {self.prefix.upper()}_ERROR_INVALID_DATA;
              }}
              *value = (uint16_t)reader->buffer[reader->offset]
                  | ((uint16_t)reader->buffer[reader->offset + 1] << 8u);
              reader->offset += 2;
              return {self.prefix.upper()}_OK;
            }}

            static inline {self.prefix.upper()}_UNUSED {self.prefix}_status_t {self.prefix}_read_int16({self.prefix}_reader_t *reader, int16_t *value) {{
              uint16_t raw_value;
              {self.prefix}_status_t status = {self.prefix}_read_uint16(reader, &raw_value);
              if (status != {self.prefix.upper()}_OK) {{
                return status;
              }}
              *value = (int16_t)raw_value;
              return {self.prefix.upper()}_OK;
            }}

            static inline {self.prefix.upper()}_UNUSED {self.prefix}_status_t {self.prefix}_read_uint32({self.prefix}_reader_t *reader, uint32_t *value) {{
              if (!{self.prefix}_can_read(reader, 4)) {{
                return {self.prefix.upper()}_ERROR_INVALID_DATA;
              }}
              *value = (uint32_t)reader->buffer[reader->offset]
                  | ((uint32_t)reader->buffer[reader->offset + 1] << 8u)
                  | ((uint32_t)reader->buffer[reader->offset + 2] << 16u)
                  | ((uint32_t)reader->buffer[reader->offset + 3] << 24u);
              reader->offset += 4;
              return {self.prefix.upper()}_OK;
            }}

            static inline {self.prefix.upper()}_UNUSED {self.prefix}_status_t {self.prefix}_read_int32({self.prefix}_reader_t *reader, int32_t *value) {{
              uint32_t raw_value;
              {self.prefix}_status_t status = {self.prefix}_read_uint32(reader, &raw_value);
              if (status != {self.prefix.upper()}_OK) {{
                return status;
              }}
              *value = (int32_t)raw_value;
              return {self.prefix.upper()}_OK;
            }}

            static inline {self.prefix.upper()}_UNUSED {self.prefix}_status_t {self.prefix}_read_uint64({self.prefix}_reader_t *reader, uint64_t *value) {{
              if (!{self.prefix}_can_read(reader, 8)) {{
                return {self.prefix.upper()}_ERROR_INVALID_DATA;
              }}
              *value = 0;
              for (size_t index = 0; index < 8; ++index) {{
                *value |= (uint64_t)reader->buffer[reader->offset + index] << (index * 8u);
              }}
              reader->offset += 8;
              return {self.prefix.upper()}_OK;
            }}

            static inline {self.prefix.upper()}_UNUSED {self.prefix}_status_t {self.prefix}_read_float({self.prefix}_reader_t *reader, float *value) {{
              uint32_t bits;
              {self.prefix}_status_t status = {self.prefix}_read_uint32(reader, &bits);
              if (status != {self.prefix.upper()}_OK) {{
                return status;
              }}
              memcpy(value, &bits, sizeof(bits));
              return {self.prefix.upper()}_OK;
            }}

            static inline {self.prefix.upper()}_UNUSED {self.prefix}_status_t {self.prefix}_read_double({self.prefix}_reader_t *reader, double *value) {{
              uint64_t bits;
              {self.prefix}_status_t status = {self.prefix}_read_uint64(reader, &bits);
              if (status != {self.prefix.upper()}_OK) {{
                return status;
              }}
              memcpy(value, &bits, sizeof(bits));
              return {self.prefix.upper()}_OK;
            }}

            static inline {self.prefix.upper()}_UNUSED {self.prefix}_status_t {self.prefix}_write_bytes({self.prefix}_writer_t *writer, const uint8_t *value, size_t length) {{
              if (!{self.prefix}_can_write(writer, length)) {{
                return {self.prefix.upper()}_ERROR_BUFFER_TOO_SMALL;
              }}
              for (size_t index = 0; index < length; ++index) {{
                writer->buffer[writer->offset++] = value[index];
              }}
              return {self.prefix.upper()}_OK;
            }}

            static inline {self.prefix.upper()}_UNUSED {self.prefix}_status_t {self.prefix}_read_bytes({self.prefix}_reader_t *reader, uint8_t *value, size_t length) {{
              if (!{self.prefix}_can_read(reader, length)) {{
                return {self.prefix.upper()}_ERROR_INVALID_DATA;
              }}
              for (size_t index = 0; index < length; ++index) {{
                value[index] = reader->buffer[reader->offset++];
              }}
              return {self.prefix.upper()}_OK;
            }}

            """
        )

    def _source_message(self, message: Message) -> str:
        c_name = self._c_message_name(message.name)
        return (
            f"static {self.prefix}_status_t {c_name}_write({self.prefix}_writer_t *writer, "
            f"const {c_name}_t *message) {{\n"
            f"{_indent(self._c_write_lines(message), 2)}\n"
            f"  return {self.prefix.upper()}_OK;\n"
            "}\n\n"
            f"static {self.prefix}_status_t {c_name}_read({self.prefix}_reader_t *reader, "
            f"{c_name}_t *message) {{\n"
            f"{_indent(self._c_read_lines(message), 2)}\n"
            f"  return {self.prefix.upper()}_OK;\n"
            "}\n\n"
            f"{self.prefix}_status_t {c_name}_encode(const {c_name}_t *message, uint8_t *buffer, "
            "size_t buffer_size, size_t *bytes_written) {\n"
            f"  {self.prefix}_writer_t writer = {{ buffer, buffer_size, 0 }};\n"
            f"  {self.prefix}_status_t status = {c_name}_write(&writer, message);\n"
            f"  if (status != {self.prefix.upper()}_OK) {{\n"
            "    return status;\n"
            "  }\n"
            "  if (bytes_written != NULL) {\n"
            "    *bytes_written = writer.offset;\n"
            "  }\n"
            f"  return {self.prefix.upper()}_OK;\n"
            "}\n\n"
            f"{self.prefix}_status_t {c_name}_decode({c_name}_t *message, const uint8_t *buffer, "
            "size_t buffer_size, size_t *bytes_read) {\n"
            f"  {self.prefix}_reader_t reader = {{ buffer, buffer_size, 0 }};\n"
            f"  {self.prefix}_status_t status = {c_name}_read(&reader, message);\n"
            f"  if (status != {self.prefix.upper()}_OK) {{\n"
            "    return status;\n"
            "  }\n"
            "  if (bytes_read != NULL) {\n"
            "    *bytes_read = reader.offset;\n"
            "  }\n"
            f"  return {self.prefix.upper()}_OK;\n"
            "}\n\n"
        )

    def _c_write_lines(self, message: Message) -> str:
        lines: list[str] = [f"{self.prefix}_status_t status;"]
        for field in message.fields:
            lines.extend(self._c_write_field(field))
        return "\n".join(lines)

    def _c_write_field(self, field: Field) -> list[str]:
        field_type = field.type
        if isinstance(field_type, ScalarType):
            return [
                f"status = {self.prefix}_write_{field_type.name}(writer, message->{field.name});",
                f"if (status != {self.prefix.upper()}_OK) return status;",
            ]
        if isinstance(field_type, BytesType):
            return [
                f"status = {self.prefix}_write_bytes(writer, message->{field.name}, message->{field_type.length_field});",
                f"if (status != {self.prefix.upper()}_OK) return status;",
            ]
        if isinstance(field_type, ArrayType):
            return [
                f"for (size_t index = 0; index < message->{field_type.length_field}; ++index) {{",
                f"  status = {self.prefix}_write_{field_type.item_type.name}(writer, message->{field.name}[index]);",
                f"  if (status != {self.prefix.upper()}_OK) return status;",
                "}",
            ]
        if isinstance(field_type, MessageRefType):
            return [
                f"status = {self._c_message_name(field_type.name)}_write(writer, &message->{field.name});",
                f"if (status != {self.prefix.upper()}_OK) return status;",
            ]
        if isinstance(field_type, UnionType):
            lines = ["switch (message->type) {"]
            for index, variant in enumerate(field_type.variants):
                lines.extend(
                    [
                        f"case {index}:",
                        f"  status = {self._c_message_name(variant.name)}_write(writer, &message->{field.name}.{variant.name});",
                        f"  if (status != {self.prefix.upper()}_OK) return status;",
                        "  break;",
                    ]
                )
            lines.extend(["default:", f"  return {self.prefix.upper()}_ERROR_INVALID_DATA;", "}"])
            return lines
        raise AssertionError(field_type)

    def _c_read_lines(self, message: Message) -> str:
        lines = [f"{self.prefix}_status_t status;"]
        for field in message.fields:
            lines.extend(self._c_read_field(field))
        return "\n".join(lines)

    def _c_read_field(self, field: Field) -> list[str]:
        field_type = field.type
        if isinstance(field_type, ScalarType):
            return [
                f"status = {self.prefix}_read_{field_type.name}(reader, &message->{field.name});",
                f"if (status != {self.prefix.upper()}_OK) return status;",
            ]
        if isinstance(field_type, BytesType):
            return [
                f"status = {self.prefix}_read_bytes(reader, message->{field.name}, message->{field_type.length_field});",
                f"if (status != {self.prefix.upper()}_OK) return status;",
            ]
        if isinstance(field_type, ArrayType):
            return [
                f"for (size_t index = 0; index < message->{field_type.length_field}; ++index) {{",
                f"  status = {self.prefix}_read_{field_type.item_type.name}(reader, &message->{field.name}[index]);",
                f"  if (status != {self.prefix.upper()}_OK) return status;",
                "}",
            ]
        if isinstance(field_type, MessageRefType):
            return [
                f"status = {self._c_message_name(field_type.name)}_read(reader, &message->{field.name});",
                f"if (status != {self.prefix.upper()}_OK) return status;",
            ]
        if isinstance(field_type, UnionType):
            lines = ["switch (message->type) {"]
            for index, variant in enumerate(field_type.variants):
                lines.extend(
                    [
                        f"case {index}:",
                        f"  status = {self._c_message_name(variant.name)}_read(reader, &message->{field.name}.{variant.name});",
                        f"  if (status != {self.prefix.upper()}_OK) return status;",
                        "  break;",
                    ]
                )
            lines.extend(["default:", f"  return {self.prefix.upper()}_ERROR_INVALID_DATA;", "}"])
            return lines
        raise AssertionError(field_type)

    def _c_message_name(self, message_name: str) -> str:
        return f"{self.prefix}_{snake_case(message_name)}"

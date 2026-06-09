// Generated shared protocol runtime. Do not edit by hand.
#include "protocol_runtime.h"


#include <string.h>

typedef char protocol_float_must_be_4_bytes[(sizeof(float) == 4) ? 1 : -1];
typedef char protocol_double_must_be_8_bytes[(sizeof(double) == 8) ? 1 : -1];

static bool protocol_can_write(protocol_writer_t *writer, size_t length) {
  return writer->offset <= writer->size && length <= writer->size - writer->offset;
}

static bool protocol_can_read(protocol_reader_t *reader, size_t length) {
  return reader->offset <= reader->size && length <= reader->size - reader->offset;
}

protocol_status_t protocol_write_uint8(protocol_writer_t *writer, uint8_t value) {
  if (!protocol_can_write(writer, 1)) {
    return PROTOCOL_ERROR_BUFFER_TOO_SMALL;
  }
  writer->buffer[writer->offset++] = value;
  return PROTOCOL_OK;
}

protocol_status_t protocol_write_int8(protocol_writer_t *writer, int8_t value) {
  return protocol_write_uint8(writer, (uint8_t)value);
}

protocol_status_t protocol_write_uint16(protocol_writer_t *writer, uint16_t value) {
  if (!protocol_can_write(writer, 2)) {
    return PROTOCOL_ERROR_BUFFER_TOO_SMALL;
  }
  writer->buffer[writer->offset++] = (uint8_t)(value & 0xffu);
  writer->buffer[writer->offset++] = (uint8_t)((value >> 8u) & 0xffu);
  return PROTOCOL_OK;
}

protocol_status_t protocol_write_int16(protocol_writer_t *writer, int16_t value) {
  return protocol_write_uint16(writer, (uint16_t)value);
}

protocol_status_t protocol_write_uint32(protocol_writer_t *writer, uint32_t value) {
  if (!protocol_can_write(writer, 4)) {
    return PROTOCOL_ERROR_BUFFER_TOO_SMALL;
  }
  writer->buffer[writer->offset++] = (uint8_t)(value & 0xffu);
  writer->buffer[writer->offset++] = (uint8_t)((value >> 8u) & 0xffu);
  writer->buffer[writer->offset++] = (uint8_t)((value >> 16u) & 0xffu);
  writer->buffer[writer->offset++] = (uint8_t)((value >> 24u) & 0xffu);
  return PROTOCOL_OK;
}

protocol_status_t protocol_write_int32(protocol_writer_t *writer, int32_t value) {
  return protocol_write_uint32(writer, (uint32_t)value);
}

static protocol_status_t protocol_write_uint64(protocol_writer_t *writer, uint64_t value) {
  if (!protocol_can_write(writer, 8)) {
    return PROTOCOL_ERROR_BUFFER_TOO_SMALL;
  }
  for (size_t index = 0; index < 8; ++index) {
    writer->buffer[writer->offset++] = (uint8_t)((value >> (index * 8u)) & 0xffu);
  }
  return PROTOCOL_OK;
}

protocol_status_t protocol_write_float(protocol_writer_t *writer, float value) {
  uint32_t bits;
  memcpy(&bits, &value, sizeof(bits));
  return protocol_write_uint32(writer, bits);
}

protocol_status_t protocol_write_double(protocol_writer_t *writer, double value) {
  uint64_t bits;
  memcpy(&bits, &value, sizeof(bits));
  return protocol_write_uint64(writer, bits);
}

protocol_status_t protocol_read_uint8(protocol_reader_t *reader, uint8_t *value) {
  if (!protocol_can_read(reader, 1)) {
    return PROTOCOL_ERROR_INVALID_DATA;
  }
  *value = reader->buffer[reader->offset++];
  return PROTOCOL_OK;
}

protocol_status_t protocol_read_int8(protocol_reader_t *reader, int8_t *value) {
  uint8_t raw_value;
  protocol_status_t status = protocol_read_uint8(reader, &raw_value);
  if (status != PROTOCOL_OK) {
    return status;
  }
  *value = (int8_t)raw_value;
  return PROTOCOL_OK;
}

protocol_status_t protocol_read_uint16(protocol_reader_t *reader, uint16_t *value) {
  if (!protocol_can_read(reader, 2)) {
    return PROTOCOL_ERROR_INVALID_DATA;
  }
  *value = (uint16_t)reader->buffer[reader->offset]
      | ((uint16_t)reader->buffer[reader->offset + 1] << 8u);
  reader->offset += 2;
  return PROTOCOL_OK;
}

protocol_status_t protocol_read_int16(protocol_reader_t *reader, int16_t *value) {
  uint16_t raw_value;
  protocol_status_t status = protocol_read_uint16(reader, &raw_value);
  if (status != PROTOCOL_OK) {
    return status;
  }
  *value = (int16_t)raw_value;
  return PROTOCOL_OK;
}

protocol_status_t protocol_read_uint32(protocol_reader_t *reader, uint32_t *value) {
  if (!protocol_can_read(reader, 4)) {
    return PROTOCOL_ERROR_INVALID_DATA;
  }
  *value = (uint32_t)reader->buffer[reader->offset]
      | ((uint32_t)reader->buffer[reader->offset + 1] << 8u)
      | ((uint32_t)reader->buffer[reader->offset + 2] << 16u)
      | ((uint32_t)reader->buffer[reader->offset + 3] << 24u);
  reader->offset += 4;
  return PROTOCOL_OK;
}

protocol_status_t protocol_read_int32(protocol_reader_t *reader, int32_t *value) {
  uint32_t raw_value;
  protocol_status_t status = protocol_read_uint32(reader, &raw_value);
  if (status != PROTOCOL_OK) {
    return status;
  }
  *value = (int32_t)raw_value;
  return PROTOCOL_OK;
}

static protocol_status_t protocol_read_uint64(protocol_reader_t *reader, uint64_t *value) {
  if (!protocol_can_read(reader, 8)) {
    return PROTOCOL_ERROR_INVALID_DATA;
  }
  *value = 0;
  for (size_t index = 0; index < 8; ++index) {
    *value |= (uint64_t)reader->buffer[reader->offset + index] << (index * 8u);
  }
  reader->offset += 8;
  return PROTOCOL_OK;
}

protocol_status_t protocol_read_float(protocol_reader_t *reader, float *value) {
  uint32_t bits;
  protocol_status_t status = protocol_read_uint32(reader, &bits);
  if (status != PROTOCOL_OK) {
    return status;
  }
  memcpy(value, &bits, sizeof(bits));
  return PROTOCOL_OK;
}

protocol_status_t protocol_read_double(protocol_reader_t *reader, double *value) {
  uint64_t bits;
  protocol_status_t status = protocol_read_uint64(reader, &bits);
  if (status != PROTOCOL_OK) {
    return status;
  }
  memcpy(value, &bits, sizeof(bits));
  return PROTOCOL_OK;
}

protocol_status_t protocol_write_bytes(protocol_writer_t *writer, const uint8_t *value, size_t length) {
  if (!protocol_can_write(writer, length)) {
    return PROTOCOL_ERROR_BUFFER_TOO_SMALL;
  }
  for (size_t index = 0; index < length; ++index) {
    writer->buffer[writer->offset++] = value[index];
  }
  return PROTOCOL_OK;
}

protocol_status_t protocol_read_bytes(protocol_reader_t *reader, uint8_t *value, size_t length) {
  if (!protocol_can_read(reader, length)) {
    return PROTOCOL_ERROR_INVALID_DATA;
  }
  for (size_t index = 0; index < length; ++index) {
    value[index] = reader->buffer[reader->offset++];
  }
  return PROTOCOL_OK;
}


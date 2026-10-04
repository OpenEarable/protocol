// Generated from schemas/ppg/protocol.yml. Do not edit by hand.
#include "ppg_protocol.h"

static protocol_status_t ppg_legacy_sample_write(protocol_writer_t *writer, const ppg_legacy_sample_t *message) {
  protocol_status_t status;
  status = protocol_write_uint32(writer, message->red);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint32(writer, message->infrared);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint32(writer, message->green);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint32(writer, message->ambient);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

static protocol_status_t ppg_legacy_sample_read(protocol_reader_t *reader, ppg_legacy_sample_t *message) {
  protocol_status_t status;
  status = protocol_read_uint32(reader, &message->red);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint32(reader, &message->infrared);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint32(reader, &message->green);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint32(reader, &message->ambient);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

protocol_status_t ppg_legacy_sample_encode(const ppg_legacy_sample_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written) {
  protocol_writer_t writer = { buffer, buffer_size, 0 };
  protocol_status_t status = ppg_legacy_sample_write(&writer, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_written != NULL) {
    *bytes_written = writer.offset;
  }
  return PROTOCOL_OK;
}

protocol_status_t ppg_legacy_sample_decode(ppg_legacy_sample_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read) {
  protocol_reader_t reader = { buffer, buffer_size, 0 };
  protocol_status_t status = ppg_legacy_sample_read(&reader, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_read != NULL) {
    *bytes_read = reader.offset;
  }
  return PROTOCOL_OK;
}

static protocol_status_t ppg_compact_sample_write(protocol_writer_t *writer, const ppg_compact_sample_t *message) {
  protocol_status_t status;
  status = protocol_write_uint32(writer, message->bits_0_31);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint32(writer, message->bits_32_63);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint16(writer, message->bits_64_79);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

static protocol_status_t ppg_compact_sample_read(protocol_reader_t *reader, ppg_compact_sample_t *message) {
  protocol_status_t status;
  status = protocol_read_uint32(reader, &message->bits_0_31);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint32(reader, &message->bits_32_63);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint16(reader, &message->bits_64_79);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

protocol_status_t ppg_compact_sample_encode(const ppg_compact_sample_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written) {
  protocol_writer_t writer = { buffer, buffer_size, 0 };
  protocol_status_t status = ppg_compact_sample_write(&writer, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_written != NULL) {
    *bytes_written = writer.offset;
  }
  return PROTOCOL_OK;
}

protocol_status_t ppg_compact_sample_decode(ppg_compact_sample_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read) {
  protocol_reader_t reader = { buffer, buffer_size, 0 };
  protocol_status_t status = ppg_compact_sample_read(&reader, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_read != NULL) {
    *bytes_read = reader.offset;
  }
  return PROTOCOL_OK;
}


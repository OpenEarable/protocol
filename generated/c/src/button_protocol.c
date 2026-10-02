// Generated from schemas/button/protocol.yml. Do not edit by hand.
#include "button_protocol.h"

static protocol_status_t button_state_write(protocol_writer_t *writer, const button_state_t *message) {
  protocol_status_t status;
  status = protocol_write_uint8(writer, message->action);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

static protocol_status_t button_state_read(protocol_reader_t *reader, button_state_t *message) {
  protocol_status_t status;
  status = protocol_read_uint8(reader, &message->action);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

protocol_status_t button_state_encode(const button_state_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written) {
  protocol_writer_t writer = { buffer, buffer_size, 0 };
  protocol_status_t status = button_state_write(&writer, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_written != NULL) {
    *bytes_written = writer.offset;
  }
  return PROTOCOL_OK;
}

protocol_status_t button_state_decode(button_state_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read) {
  protocol_reader_t reader = { buffer, buffer_size, 0 };
  protocol_status_t status = button_state_read(&reader, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_read != NULL) {
    *bytes_read = reader.offset;
  }
  return PROTOCOL_OK;
}


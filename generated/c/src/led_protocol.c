// Generated from schemas/led/protocol.yml. Do not edit by hand.
#include "led_protocol.h"

static protocol_status_t led_rgb_write(protocol_writer_t *writer, const led_rgb_t *message) {
  protocol_status_t status;
  status = protocol_write_uint8(writer, message->red);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint8(writer, message->green);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint8(writer, message->blue);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

static protocol_status_t led_rgb_read(protocol_reader_t *reader, led_rgb_t *message) {
  protocol_status_t status;
  status = protocol_read_uint8(reader, &message->red);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint8(reader, &message->green);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint8(reader, &message->blue);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

protocol_status_t led_rgb_encode(const led_rgb_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written) {
  protocol_writer_t writer = { buffer, buffer_size, 0 };
  protocol_status_t status = led_rgb_write(&writer, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_written != NULL) {
    *bytes_written = writer.offset;
  }
  return PROTOCOL_OK;
}

protocol_status_t led_rgb_decode(led_rgb_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read) {
  protocol_reader_t reader = { buffer, buffer_size, 0 };
  protocol_status_t status = led_rgb_read(&reader, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_read != NULL) {
    *bytes_read = reader.offset;
  }
  return PROTOCOL_OK;
}

static protocol_status_t led_state_write(protocol_writer_t *writer, const led_state_t *message) {
  protocol_status_t status;
  status = protocol_write_uint8(writer, message->mode);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

static protocol_status_t led_state_read(protocol_reader_t *reader, led_state_t *message) {
  protocol_status_t status;
  status = protocol_read_uint8(reader, &message->mode);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

protocol_status_t led_state_encode(const led_state_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written) {
  protocol_writer_t writer = { buffer, buffer_size, 0 };
  protocol_status_t status = led_state_write(&writer, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_written != NULL) {
    *bytes_written = writer.offset;
  }
  return PROTOCOL_OK;
}

protocol_status_t led_state_decode(led_state_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read) {
  protocol_reader_t reader = { buffer, buffer_size, 0 };
  protocol_status_t status = led_state_read(&reader, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_read != NULL) {
    *bytes_read = reader.offset;
  }
  return PROTOCOL_OK;
}


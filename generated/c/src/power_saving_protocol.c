// Generated from schemas/power-saving/protocol.yml. Do not edit by hand.
#include "power_saving_protocol.h"

static protocol_status_t power_saving_mode_write(protocol_writer_t *writer, const power_saving_mode_t *message) {
  protocol_status_t status;
  status = protocol_write_uint8(writer, message->id);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

static protocol_status_t power_saving_mode_read(protocol_reader_t *reader, power_saving_mode_t *message, bool bounded) {
  protocol_status_t status;
  (void)bounded;
  status = protocol_read_uint8(reader, &message->id);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

protocol_status_t power_saving_mode_encode(const power_saving_mode_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written) {
  protocol_writer_t writer = { buffer, buffer_size, 0 };
  protocol_status_t status = power_saving_mode_write(&writer, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_written != NULL) {
    *bytes_written = writer.offset;
  }
  return PROTOCOL_OK;
}

protocol_status_t power_saving_mode_decode(power_saving_mode_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read) {
  protocol_reader_t reader = { buffer, buffer_size, 0 };
  protocol_status_t status = power_saving_mode_read(&reader, message, false);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_read != NULL) {
    *bytes_read = reader.offset;
  }
  return PROTOCOL_OK;
}

protocol_status_t power_saving_mode_decode_bounded(power_saving_mode_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read) {
  protocol_reader_t reader = { buffer, buffer_size, 0 };
  if (message == NULL || (buffer == NULL && buffer_size != 0)) return PROTOCOL_ERROR_INVALID_DATA;
  protocol_status_t status = power_saving_mode_read(&reader, message, true);
  if (status != PROTOCOL_OK) return status;
  if (bytes_read != NULL) *bytes_read = reader.offset;
  return PROTOCOL_OK;
}

static protocol_status_t power_saving_mode_description_write(protocol_writer_t *writer, const power_saving_mode_description_t *message) {
  protocol_status_t status;
  status = protocol_write_uint8(writer, message->id);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint8(writer, message->name_length);
  if (status != PROTOCOL_OK) return status;
  if (message->name_length && message->name == NULL) return PROTOCOL_ERROR_INVALID_DATA;
  status = protocol_write_bytes(writer, message->name, message->name_length);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

static protocol_status_t power_saving_mode_description_read(protocol_reader_t *reader, power_saving_mode_description_t *message, bool bounded) {
  protocol_status_t status;
  (void)bounded;
  status = protocol_read_uint8(reader, &message->id);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint8(reader, &message->name_length);
  if (status != PROTOCOL_OK) return status;
  if (bounded && (size_t)message->name_length > message->name_capacity) return PROTOCOL_ERROR_BUFFER_TOO_SMALL;
  if (message->name_length && message->name == NULL) return PROTOCOL_ERROR_INVALID_DATA;
  status = protocol_read_bytes(reader, message->name, message->name_length);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

protocol_status_t power_saving_mode_description_encode(const power_saving_mode_description_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written) {
  protocol_writer_t writer = { buffer, buffer_size, 0 };
  protocol_status_t status = power_saving_mode_description_write(&writer, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_written != NULL) {
    *bytes_written = writer.offset;
  }
  return PROTOCOL_OK;
}

protocol_status_t power_saving_mode_description_decode(power_saving_mode_description_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read) {
  protocol_reader_t reader = { buffer, buffer_size, 0 };
  protocol_status_t status = power_saving_mode_description_read(&reader, message, false);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_read != NULL) {
    *bytes_read = reader.offset;
  }
  return PROTOCOL_OK;
}

protocol_status_t power_saving_mode_description_decode_bounded(power_saving_mode_description_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read) {
  protocol_reader_t reader = { buffer, buffer_size, 0 };
  if (message == NULL || (buffer == NULL && buffer_size != 0)) return PROTOCOL_ERROR_INVALID_DATA;
  protocol_status_t status = power_saving_mode_description_read(&reader, message, true);
  if (status != PROTOCOL_OK) return status;
  if (bytes_read != NULL) *bytes_read = reader.offset;
  return PROTOCOL_OK;
}

static protocol_status_t power_saving_supported_modes_write(protocol_writer_t *writer, const power_saving_supported_modes_t *message) {
  protocol_status_t status;
  status = protocol_write_uint8(writer, message->count);
  if (status != PROTOCOL_OK) return status;
  if (message->count && message->modes == NULL) return PROTOCOL_ERROR_INVALID_DATA;
  for (size_t index = 0; index < (size_t)message->count; ++index) {
    status = power_saving_mode_description_write(writer, &message->modes[index]);
    if (status != PROTOCOL_OK) return status;
  }
  return PROTOCOL_OK;
}

static protocol_status_t power_saving_supported_modes_read(protocol_reader_t *reader, power_saving_supported_modes_t *message, bool bounded) {
  protocol_status_t status;
  (void)bounded;
  status = protocol_read_uint8(reader, &message->count);
  if (status != PROTOCOL_OK) return status;
  if (true && (size_t)message->count > message->modes_capacity) return PROTOCOL_ERROR_BUFFER_TOO_SMALL;
  if (message->count && message->modes == NULL) return PROTOCOL_ERROR_INVALID_DATA;
  for (size_t index = 0; index < (size_t)message->count; ++index) {
    status = power_saving_mode_description_read(reader, &message->modes[index], true);
    if (status != PROTOCOL_OK) return status;
  }
  return PROTOCOL_OK;
}

protocol_status_t power_saving_supported_modes_encode(const power_saving_supported_modes_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written) {
  protocol_writer_t writer = { buffer, buffer_size, 0 };
  protocol_status_t status = power_saving_supported_modes_write(&writer, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_written != NULL) {
    *bytes_written = writer.offset;
  }
  return PROTOCOL_OK;
}

protocol_status_t power_saving_supported_modes_decode(power_saving_supported_modes_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read) {
  protocol_reader_t reader = { buffer, buffer_size, 0 };
  protocol_status_t status = power_saving_supported_modes_read(&reader, message, false);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_read != NULL) {
    *bytes_read = reader.offset;
  }
  return PROTOCOL_OK;
}

protocol_status_t power_saving_supported_modes_decode_bounded(power_saving_supported_modes_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read) {
  protocol_reader_t reader = { buffer, buffer_size, 0 };
  if (message == NULL || (buffer == NULL && buffer_size != 0)) return PROTOCOL_ERROR_INVALID_DATA;
  protocol_status_t status = power_saving_supported_modes_read(&reader, message, true);
  if (status != PROTOCOL_OK) return status;
  if (bytes_read != NULL) *bytes_read = reader.offset;
  return PROTOCOL_OK;
}


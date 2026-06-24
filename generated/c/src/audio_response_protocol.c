// Generated from schemas/audio-response/protocol.yml. Do not edit by hand.
#include "audio_response_protocol.h"

static protocol_status_t audio_response_transfer_start_write(protocol_writer_t *writer, const audio_response_transfer_start_t *message) {
  protocol_status_t status;
  status = protocol_write_uint16(writer, message->transfer_id);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint32(writer, message->total_samples);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint32(writer, message->sampling_rate);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint32(writer, message->checksum);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

static protocol_status_t audio_response_transfer_start_read(protocol_reader_t *reader, audio_response_transfer_start_t *message) {
  protocol_status_t status;
  status = protocol_read_uint16(reader, &message->transfer_id);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint32(reader, &message->total_samples);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint32(reader, &message->sampling_rate);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint32(reader, &message->checksum);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

protocol_status_t audio_response_transfer_start_encode(const audio_response_transfer_start_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written) {
  protocol_writer_t writer = { buffer, buffer_size, 0 };
  protocol_status_t status = audio_response_transfer_start_write(&writer, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_written != NULL) {
    *bytes_written = writer.offset;
  }
  return PROTOCOL_OK;
}

protocol_status_t audio_response_transfer_start_decode(audio_response_transfer_start_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read) {
  protocol_reader_t reader = { buffer, buffer_size, 0 };
  protocol_status_t status = audio_response_transfer_start_read(&reader, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_read != NULL) {
    *bytes_read = reader.offset;
  }
  return PROTOCOL_OK;
}

static protocol_status_t audio_response_transfer_commit_write(protocol_writer_t *writer, const audio_response_transfer_commit_t *message) {
  protocol_status_t status;
  status = protocol_write_uint16(writer, message->transfer_id);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

static protocol_status_t audio_response_transfer_commit_read(protocol_reader_t *reader, audio_response_transfer_commit_t *message) {
  protocol_status_t status;
  status = protocol_read_uint16(reader, &message->transfer_id);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

protocol_status_t audio_response_transfer_commit_encode(const audio_response_transfer_commit_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written) {
  protocol_writer_t writer = { buffer, buffer_size, 0 };
  protocol_status_t status = audio_response_transfer_commit_write(&writer, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_written != NULL) {
    *bytes_written = writer.offset;
  }
  return PROTOCOL_OK;
}

protocol_status_t audio_response_transfer_commit_decode(audio_response_transfer_commit_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read) {
  protocol_reader_t reader = { buffer, buffer_size, 0 };
  protocol_status_t status = audio_response_transfer_commit_read(&reader, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_read != NULL) {
    *bytes_read = reader.offset;
  }
  return PROTOCOL_OK;
}

static protocol_status_t audio_response_transfer_abort_write(protocol_writer_t *writer, const audio_response_transfer_abort_t *message) {
  protocol_status_t status;
  status = protocol_write_uint16(writer, message->transfer_id);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

static protocol_status_t audio_response_transfer_abort_read(protocol_reader_t *reader, audio_response_transfer_abort_t *message) {
  protocol_status_t status;
  status = protocol_read_uint16(reader, &message->transfer_id);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

protocol_status_t audio_response_transfer_abort_encode(const audio_response_transfer_abort_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written) {
  protocol_writer_t writer = { buffer, buffer_size, 0 };
  protocol_status_t status = audio_response_transfer_abort_write(&writer, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_written != NULL) {
    *bytes_written = writer.offset;
  }
  return PROTOCOL_OK;
}

protocol_status_t audio_response_transfer_abort_decode(audio_response_transfer_abort_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read) {
  protocol_reader_t reader = { buffer, buffer_size, 0 };
  protocol_status_t status = audio_response_transfer_abort_read(&reader, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_read != NULL) {
    *bytes_read = reader.offset;
  }
  return PROTOCOL_OK;
}

void audio_response_transfer_control_set_command_start(audio_response_transfer_control_t *message, audio_response_transfer_start_t command) {
  if (message == NULL) {
    return;
  }
  message->type = AUDIO_RESPONSE_TRANSFER_CONTROL_START;
  message->command.transfer_start = command;
}

audio_response_transfer_control_t audio_response_transfer_control_from_start(audio_response_transfer_start_t command) {
  audio_response_transfer_control_t message = {0};
  audio_response_transfer_control_set_command_start(&message, command);
  return message;
}

void audio_response_transfer_control_set_command_commit(audio_response_transfer_control_t *message, audio_response_transfer_commit_t command) {
  if (message == NULL) {
    return;
  }
  message->type = AUDIO_RESPONSE_TRANSFER_CONTROL_COMMIT;
  message->command.transfer_commit = command;
}

audio_response_transfer_control_t audio_response_transfer_control_from_commit(audio_response_transfer_commit_t command) {
  audio_response_transfer_control_t message = {0};
  audio_response_transfer_control_set_command_commit(&message, command);
  return message;
}

void audio_response_transfer_control_set_command_abort(audio_response_transfer_control_t *message, audio_response_transfer_abort_t command) {
  if (message == NULL) {
    return;
  }
  message->type = AUDIO_RESPONSE_TRANSFER_CONTROL_ABORT;
  message->command.transfer_abort = command;
}

audio_response_transfer_control_t audio_response_transfer_control_from_abort(audio_response_transfer_abort_t command) {
  audio_response_transfer_control_t message = {0};
  audio_response_transfer_control_set_command_abort(&message, command);
  return message;
}

protocol_status_t audio_response_transfer_control_dispatch(const audio_response_transfer_control_t *message, const audio_response_transfer_control_handler_t *handler, void *context) {
  if (message == NULL || handler == NULL) {
    return PROTOCOL_ERROR_INVALID_DATA;
  }
  switch (message->type) {
  case AUDIO_RESPONSE_TRANSFER_CONTROL_START:
    if (handler->start == NULL) {
      return PROTOCOL_ERROR_INVALID_DATA;
    }
    return handler->start(context, &message->command.transfer_start);
  case AUDIO_RESPONSE_TRANSFER_CONTROL_COMMIT:
    if (handler->commit == NULL) {
      return PROTOCOL_ERROR_INVALID_DATA;
    }
    return handler->commit(context, &message->command.transfer_commit);
  case AUDIO_RESPONSE_TRANSFER_CONTROL_ABORT:
    if (handler->abort == NULL) {
      return PROTOCOL_ERROR_INVALID_DATA;
    }
    return handler->abort(context, &message->command.transfer_abort);
  default:
    return PROTOCOL_ERROR_INVALID_DATA;
  }
}

static protocol_status_t audio_response_transfer_control_write(protocol_writer_t *writer, const audio_response_transfer_control_t *message) {
  protocol_status_t status;
  status = protocol_write_uint8(writer, message->type);
  if (status != PROTOCOL_OK) return status;
  switch (message->type) {
  case AUDIO_RESPONSE_TRANSFER_CONTROL_START:
    status = audio_response_transfer_start_write(writer, &message->command.transfer_start);
    if (status != PROTOCOL_OK) return status;
    break;
  case AUDIO_RESPONSE_TRANSFER_CONTROL_COMMIT:
    status = audio_response_transfer_commit_write(writer, &message->command.transfer_commit);
    if (status != PROTOCOL_OK) return status;
    break;
  case AUDIO_RESPONSE_TRANSFER_CONTROL_ABORT:
    status = audio_response_transfer_abort_write(writer, &message->command.transfer_abort);
    if (status != PROTOCOL_OK) return status;
    break;
  default:
    return PROTOCOL_ERROR_INVALID_DATA;
  }
  return PROTOCOL_OK;
}

static protocol_status_t audio_response_transfer_control_read(protocol_reader_t *reader, audio_response_transfer_control_t *message) {
  protocol_status_t status;
  uint8_t raw_type;
  status = protocol_read_uint8(reader, &raw_type);
  if (status != PROTOCOL_OK) return status;
  message->type = (audio_response_transfer_control_type_t)raw_type;
  switch (message->type) {
  case AUDIO_RESPONSE_TRANSFER_CONTROL_START:
    status = audio_response_transfer_start_read(reader, &message->command.transfer_start);
    if (status != PROTOCOL_OK) return status;
    break;
  case AUDIO_RESPONSE_TRANSFER_CONTROL_COMMIT:
    status = audio_response_transfer_commit_read(reader, &message->command.transfer_commit);
    if (status != PROTOCOL_OK) return status;
    break;
  case AUDIO_RESPONSE_TRANSFER_CONTROL_ABORT:
    status = audio_response_transfer_abort_read(reader, &message->command.transfer_abort);
    if (status != PROTOCOL_OK) return status;
    break;
  default:
    return PROTOCOL_ERROR_INVALID_DATA;
  }
  return PROTOCOL_OK;
}

protocol_status_t audio_response_transfer_control_encode(const audio_response_transfer_control_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written) {
  protocol_writer_t writer = { buffer, buffer_size, 0 };
  protocol_status_t status = audio_response_transfer_control_write(&writer, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_written != NULL) {
    *bytes_written = writer.offset;
  }
  return PROTOCOL_OK;
}

protocol_status_t audio_response_transfer_control_decode(audio_response_transfer_control_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read) {
  protocol_reader_t reader = { buffer, buffer_size, 0 };
  protocol_status_t status = audio_response_transfer_control_read(&reader, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_read != NULL) {
    *bytes_read = reader.offset;
  }
  return PROTOCOL_OK;
}

static protocol_status_t audio_response_transfer_chunk_write(protocol_writer_t *writer, const audio_response_transfer_chunk_t *message) {
  protocol_status_t status;
  status = protocol_write_uint16(writer, message->transfer_id);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint32(writer, message->sample_offset);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint16(writer, message->sample_count);
  if (status != PROTOCOL_OK) return status;
  for (size_t index = 0; index < message->sample_count; ++index) {
    status = protocol_write_int16(writer, message->samples[index]);
    if (status != PROTOCOL_OK) return status;
  }
  return PROTOCOL_OK;
}

static protocol_status_t audio_response_transfer_chunk_read(protocol_reader_t *reader, audio_response_transfer_chunk_t *message) {
  protocol_status_t status;
  status = protocol_read_uint16(reader, &message->transfer_id);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint32(reader, &message->sample_offset);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint16(reader, &message->sample_count);
  if (status != PROTOCOL_OK) return status;
  for (size_t index = 0; index < message->sample_count; ++index) {
    status = protocol_read_int16(reader, &message->samples[index]);
    if (status != PROTOCOL_OK) return status;
  }
  return PROTOCOL_OK;
}

protocol_status_t audio_response_transfer_chunk_encode(const audio_response_transfer_chunk_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written) {
  protocol_writer_t writer = { buffer, buffer_size, 0 };
  protocol_status_t status = audio_response_transfer_chunk_write(&writer, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_written != NULL) {
    *bytes_written = writer.offset;
  }
  return PROTOCOL_OK;
}

protocol_status_t audio_response_transfer_chunk_decode(audio_response_transfer_chunk_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read) {
  protocol_reader_t reader = { buffer, buffer_size, 0 };
  protocol_status_t status = audio_response_transfer_chunk_read(&reader, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_read != NULL) {
    *bytes_read = reader.offset;
  }
  return PROTOCOL_OK;
}

static protocol_status_t audio_response_transfer_status_write(protocol_writer_t *writer, const audio_response_transfer_status_t *message) {
  protocol_status_t status;
  status = protocol_write_uint16(writer, message->transfer_id);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint8(writer, message->status);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint32(writer, message->next_sample_offset);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint16(writer, message->credits);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

static protocol_status_t audio_response_transfer_status_read(protocol_reader_t *reader, audio_response_transfer_status_t *message) {
  protocol_status_t status;
  status = protocol_read_uint16(reader, &message->transfer_id);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint8(reader, &message->status);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint32(reader, &message->next_sample_offset);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint16(reader, &message->credits);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

protocol_status_t audio_response_transfer_status_encode(const audio_response_transfer_status_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written) {
  protocol_writer_t writer = { buffer, buffer_size, 0 };
  protocol_status_t status = audio_response_transfer_status_write(&writer, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_written != NULL) {
    *bytes_written = writer.offset;
  }
  return PROTOCOL_OK;
}

protocol_status_t audio_response_transfer_status_decode(audio_response_transfer_status_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read) {
  protocol_reader_t reader = { buffer, buffer_size, 0 };
  protocol_status_t status = audio_response_transfer_status_read(&reader, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_read != NULL) {
    *bytes_read = reader.offset;
  }
  return PROTOCOL_OK;
}

static protocol_status_t audio_response_config_write(protocol_writer_t *writer, const audio_response_config_t *message) {
  protocol_status_t status;
  status = protocol_write_uint8(writer, message->id);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint16(writer, message->transfer_id);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_float(writer, message->volume);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint8(writer, message->points);
  if (status != PROTOCOL_OK) return status;
  for (size_t index = 0; index < message->points; ++index) {
    status = protocol_write_uint16(writer, message->frequencies[index]);
    if (status != PROTOCOL_OK) return status;
  }
  return PROTOCOL_OK;
}

static protocol_status_t audio_response_config_read(protocol_reader_t *reader, audio_response_config_t *message) {
  protocol_status_t status;
  status = protocol_read_uint8(reader, &message->id);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint16(reader, &message->transfer_id);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_float(reader, &message->volume);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint8(reader, &message->points);
  if (status != PROTOCOL_OK) return status;
  for (size_t index = 0; index < message->points; ++index) {
    status = protocol_read_uint16(reader, &message->frequencies[index]);
    if (status != PROTOCOL_OK) return status;
  }
  return PROTOCOL_OK;
}

protocol_status_t audio_response_config_encode(const audio_response_config_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written) {
  protocol_writer_t writer = { buffer, buffer_size, 0 };
  protocol_status_t status = audio_response_config_write(&writer, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_written != NULL) {
    *bytes_written = writer.offset;
  }
  return PROTOCOL_OK;
}

protocol_status_t audio_response_config_decode(audio_response_config_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read) {
  protocol_reader_t reader = { buffer, buffer_size, 0 };
  protocol_status_t status = audio_response_config_read(&reader, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_read != NULL) {
    *bytes_read = reader.offset;
  }
  return PROTOCOL_OK;
}

static protocol_status_t audio_response_result_write(protocol_writer_t *writer, const audio_response_result_t *message) {
  protocol_status_t status;
  status = protocol_write_uint8(writer, message->id);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint8(writer, message->points);
  if (status != PROTOCOL_OK) return status;
  for (size_t index = 0; index < message->points; ++index) {
    status = protocol_write_uint16(writer, message->frequencies[index]);
    if (status != PROTOCOL_OK) return status;
  }
  for (size_t index = 0; index < message->points; ++index) {
    status = protocol_write_uint16(writer, message->response[index]);
    if (status != PROTOCOL_OK) return status;
  }
  return PROTOCOL_OK;
}

static protocol_status_t audio_response_result_read(protocol_reader_t *reader, audio_response_result_t *message) {
  protocol_status_t status;
  status = protocol_read_uint8(reader, &message->id);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint8(reader, &message->points);
  if (status != PROTOCOL_OK) return status;
  for (size_t index = 0; index < message->points; ++index) {
    status = protocol_read_uint16(reader, &message->frequencies[index]);
    if (status != PROTOCOL_OK) return status;
  }
  for (size_t index = 0; index < message->points; ++index) {
    status = protocol_read_uint16(reader, &message->response[index]);
    if (status != PROTOCOL_OK) return status;
  }
  return PROTOCOL_OK;
}

protocol_status_t audio_response_result_encode(const audio_response_result_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written) {
  protocol_writer_t writer = { buffer, buffer_size, 0 };
  protocol_status_t status = audio_response_result_write(&writer, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_written != NULL) {
    *bytes_written = writer.offset;
  }
  return PROTOCOL_OK;
}

protocol_status_t audio_response_result_decode(audio_response_result_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read) {
  protocol_reader_t reader = { buffer, buffer_size, 0 };
  protocol_status_t status = audio_response_result_read(&reader, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_read != NULL) {
    *bytes_read = reader.offset;
  }
  return PROTOCOL_OK;
}


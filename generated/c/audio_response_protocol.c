// Generated from schemas/audio-response/protocol.yml. Do not edit by hand.
#include "audio_response_protocol.h"

static protocol_status_t audio_response_buffer_write(protocol_writer_t *writer, const audio_response_buffer_t *message) {
  protocol_status_t status;
  status = protocol_write_uint16(writer, message->length);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint16(writer, message->sampling_rate);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_bytes(writer, message->buffer, message->length);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

static protocol_status_t audio_response_buffer_read(protocol_reader_t *reader, audio_response_buffer_t *message) {
  protocol_status_t status;
  status = protocol_read_uint16(reader, &message->length);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint16(reader, &message->sampling_rate);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_bytes(reader, message->buffer, message->length);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

protocol_status_t audio_response_buffer_encode(const audio_response_buffer_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written) {
  protocol_writer_t writer = { buffer, buffer_size, 0 };
  protocol_status_t status = audio_response_buffer_write(&writer, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_written != NULL) {
    *bytes_written = writer.offset;
  }
  return PROTOCOL_OK;
}

protocol_status_t audio_response_buffer_decode(audio_response_buffer_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read) {
  protocol_reader_t reader = { buffer, buffer_size, 0 };
  protocol_status_t status = audio_response_buffer_read(&reader, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_read != NULL) {
    *bytes_read = reader.offset;
  }
  return PROTOCOL_OK;
}

static protocol_status_t audio_response_tone_write(protocol_writer_t *writer, const audio_response_tone_t *message) {
  protocol_status_t status;
  status = protocol_write_uint16(writer, message->frequency);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint16(writer, message->duration);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

static protocol_status_t audio_response_tone_read(protocol_reader_t *reader, audio_response_tone_t *message) {
  protocol_status_t status;
  status = protocol_read_uint16(reader, &message->frequency);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint16(reader, &message->duration);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

protocol_status_t audio_response_tone_encode(const audio_response_tone_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written) {
  protocol_writer_t writer = { buffer, buffer_size, 0 };
  protocol_status_t status = audio_response_tone_write(&writer, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_written != NULL) {
    *bytes_written = writer.offset;
  }
  return PROTOCOL_OK;
}

protocol_status_t audio_response_tone_decode(audio_response_tone_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read) {
  protocol_reader_t reader = { buffer, buffer_size, 0 };
  protocol_status_t status = audio_response_tone_read(&reader, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_read != NULL) {
    *bytes_read = reader.offset;
  }
  return PROTOCOL_OK;
}

static protocol_status_t audio_response_audio_response_write(protocol_writer_t *writer, const audio_response_audio_response_t *message) {
  protocol_status_t status;
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

static protocol_status_t audio_response_audio_response_read(protocol_reader_t *reader, audio_response_audio_response_t *message) {
  protocol_status_t status;
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

protocol_status_t audio_response_audio_response_encode(const audio_response_audio_response_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written) {
  protocol_writer_t writer = { buffer, buffer_size, 0 };
  protocol_status_t status = audio_response_audio_response_write(&writer, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_written != NULL) {
    *bytes_written = writer.offset;
  }
  return PROTOCOL_OK;
}

protocol_status_t audio_response_audio_response_decode(audio_response_audio_response_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read) {
  protocol_reader_t reader = { buffer, buffer_size, 0 };
  protocol_status_t status = audio_response_audio_response_read(&reader, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_read != NULL) {
    *bytes_read = reader.offset;
  }
  return PROTOCOL_OK;
}

static protocol_status_t audio_response_sound_write(protocol_writer_t *writer, const audio_response_sound_t *message) {
  protocol_status_t status;
  status = protocol_write_uint8(writer, message->type);
  if (status != PROTOCOL_OK) return status;
  switch (message->type) {
  case 0:
    status = audio_response_buffer_write(writer, &message->data.buffer);
    if (status != PROTOCOL_OK) return status;
    break;
  case 1:
    status = audio_response_tone_write(writer, &message->data.tone);
    if (status != PROTOCOL_OK) return status;
    break;
  default:
    return PROTOCOL_ERROR_INVALID_DATA;
  }
  return PROTOCOL_OK;
}

static protocol_status_t audio_response_sound_read(protocol_reader_t *reader, audio_response_sound_t *message) {
  protocol_status_t status;
  status = protocol_read_uint8(reader, &message->type);
  if (status != PROTOCOL_OK) return status;
  switch (message->type) {
  case 0:
    status = audio_response_buffer_read(reader, &message->data.buffer);
    if (status != PROTOCOL_OK) return status;
    break;
  case 1:
    status = audio_response_tone_read(reader, &message->data.tone);
    if (status != PROTOCOL_OK) return status;
    break;
  default:
    return PROTOCOL_ERROR_INVALID_DATA;
  }
  return PROTOCOL_OK;
}

protocol_status_t audio_response_sound_encode(const audio_response_sound_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written) {
  protocol_writer_t writer = { buffer, buffer_size, 0 };
  protocol_status_t status = audio_response_sound_write(&writer, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_written != NULL) {
    *bytes_written = writer.offset;
  }
  return PROTOCOL_OK;
}

protocol_status_t audio_response_sound_decode(audio_response_sound_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read) {
  protocol_reader_t reader = { buffer, buffer_size, 0 };
  protocol_status_t status = audio_response_sound_read(&reader, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_read != NULL) {
    *bytes_read = reader.offset;
  }
  return PROTOCOL_OK;
}


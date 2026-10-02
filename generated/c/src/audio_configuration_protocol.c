// Generated from schemas/audio-configuration/protocol.yml. Do not edit by hand.
#include "audio_configuration_protocol.h"

static protocol_status_t audio_configuration_audio_mode_write(protocol_writer_t *writer, const audio_configuration_audio_mode_t *message) {
  protocol_status_t status;
  status = protocol_write_uint8(writer, message->mode);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

static protocol_status_t audio_configuration_audio_mode_read(protocol_reader_t *reader, audio_configuration_audio_mode_t *message) {
  protocol_status_t status;
  status = protocol_read_uint8(reader, &message->mode);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

protocol_status_t audio_configuration_audio_mode_encode(const audio_configuration_audio_mode_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written) {
  protocol_writer_t writer = { buffer, buffer_size, 0 };
  protocol_status_t status = audio_configuration_audio_mode_write(&writer, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_written != NULL) {
    *bytes_written = writer.offset;
  }
  return PROTOCOL_OK;
}

protocol_status_t audio_configuration_audio_mode_decode(audio_configuration_audio_mode_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read) {
  protocol_reader_t reader = { buffer, buffer_size, 0 };
  protocol_status_t status = audio_configuration_audio_mode_read(&reader, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_read != NULL) {
    *bytes_read = reader.offset;
  }
  return PROTOCOL_OK;
}

static protocol_status_t audio_configuration_microphone_selection_write(protocol_writer_t *writer, const audio_configuration_microphone_selection_t *message) {
  protocol_status_t status;
  status = protocol_write_uint8(writer, message->microphone);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

static protocol_status_t audio_configuration_microphone_selection_read(protocol_reader_t *reader, audio_configuration_microphone_selection_t *message) {
  protocol_status_t status;
  status = protocol_read_uint8(reader, &message->microphone);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

protocol_status_t audio_configuration_microphone_selection_encode(const audio_configuration_microphone_selection_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written) {
  protocol_writer_t writer = { buffer, buffer_size, 0 };
  protocol_status_t status = audio_configuration_microphone_selection_write(&writer, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_written != NULL) {
    *bytes_written = writer.offset;
  }
  return PROTOCOL_OK;
}

protocol_status_t audio_configuration_microphone_selection_decode(audio_configuration_microphone_selection_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read) {
  protocol_reader_t reader = { buffer, buffer_size, 0 };
  protocol_status_t status = audio_configuration_microphone_selection_read(&reader, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_read != NULL) {
    *bytes_read = reader.offset;
  }
  return PROTOCOL_OK;
}

static protocol_status_t audio_configuration_audio_channel_write(protocol_writer_t *writer, const audio_configuration_audio_channel_t *message) {
  protocol_status_t status;
  status = protocol_write_uint8(writer, message->channel);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

static protocol_status_t audio_configuration_audio_channel_read(protocol_reader_t *reader, audio_configuration_audio_channel_t *message) {
  protocol_status_t status;
  status = protocol_read_uint8(reader, &message->channel);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

protocol_status_t audio_configuration_audio_channel_encode(const audio_configuration_audio_channel_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written) {
  protocol_writer_t writer = { buffer, buffer_size, 0 };
  protocol_status_t status = audio_configuration_audio_channel_write(&writer, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_written != NULL) {
    *bytes_written = writer.offset;
  }
  return PROTOCOL_OK;
}

protocol_status_t audio_configuration_audio_channel_decode(audio_configuration_audio_channel_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read) {
  protocol_reader_t reader = { buffer, buffer_size, 0 };
  protocol_status_t status = audio_configuration_audio_channel_read(&reader, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_read != NULL) {
    *bytes_read = reader.offset;
  }
  return PROTOCOL_OK;
}

static protocol_status_t audio_configuration_microphone_gain_write(protocol_writer_t *writer, const audio_configuration_microphone_gain_t *message) {
  protocol_status_t status;
  status = protocol_write_uint8(writer, message->outer);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint8(writer, message->inner);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

static protocol_status_t audio_configuration_microphone_gain_read(protocol_reader_t *reader, audio_configuration_microphone_gain_t *message) {
  protocol_status_t status;
  status = protocol_read_uint8(reader, &message->outer);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint8(reader, &message->inner);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

protocol_status_t audio_configuration_microphone_gain_encode(const audio_configuration_microphone_gain_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written) {
  protocol_writer_t writer = { buffer, buffer_size, 0 };
  protocol_status_t status = audio_configuration_microphone_gain_write(&writer, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_written != NULL) {
    *bytes_written = writer.offset;
  }
  return PROTOCOL_OK;
}

protocol_status_t audio_configuration_microphone_gain_decode(audio_configuration_microphone_gain_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read) {
  protocol_reader_t reader = { buffer, buffer_size, 0 };
  protocol_status_t status = audio_configuration_microphone_gain_read(&reader, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_read != NULL) {
    *bytes_read = reader.offset;
  }
  return PROTOCOL_OK;
}


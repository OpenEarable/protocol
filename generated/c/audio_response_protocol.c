// Generated from schemas/audio-response/protocol.yml. Do not edit by hand.
#include "audio_response_protocol.h"


#include <string.h>

typedef struct {
  uint8_t *buffer;
  size_t size;
  size_t offset;
} audio_response_writer_t;

typedef struct {
  const uint8_t *buffer;
  size_t size;
  size_t offset;
} audio_response_reader_t;

#if defined(__GNUC__) || defined(__clang__)
#define AUDIO_RESPONSE_UNUSED __attribute__((unused))
#else
#define AUDIO_RESPONSE_UNUSED
#endif

typedef char audio_response_float_must_be_4_bytes[(sizeof(float) == 4) ? 1 : -1];
typedef char audio_response_double_must_be_8_bytes[(sizeof(double) == 8) ? 1 : -1];

static inline AUDIO_RESPONSE_UNUSED bool audio_response_can_write(audio_response_writer_t *writer, size_t length) {
  return writer->offset <= writer->size && length <= writer->size - writer->offset;
}

static inline AUDIO_RESPONSE_UNUSED bool audio_response_can_read(audio_response_reader_t *reader, size_t length) {
  return reader->offset <= reader->size && length <= reader->size - reader->offset;
}

static inline AUDIO_RESPONSE_UNUSED audio_response_status_t audio_response_write_uint8(audio_response_writer_t *writer, uint8_t value) {
  if (!audio_response_can_write(writer, 1)) {
    return AUDIO_RESPONSE_ERROR_BUFFER_TOO_SMALL;
  }
  writer->buffer[writer->offset++] = value;
  return AUDIO_RESPONSE_OK;
}

static inline AUDIO_RESPONSE_UNUSED audio_response_status_t audio_response_write_int8(audio_response_writer_t *writer, int8_t value) {
  return audio_response_write_uint8(writer, (uint8_t)value);
}

static inline AUDIO_RESPONSE_UNUSED audio_response_status_t audio_response_write_uint16(audio_response_writer_t *writer, uint16_t value) {
  if (!audio_response_can_write(writer, 2)) {
    return AUDIO_RESPONSE_ERROR_BUFFER_TOO_SMALL;
  }
  writer->buffer[writer->offset++] = (uint8_t)(value & 0xffu);
  writer->buffer[writer->offset++] = (uint8_t)((value >> 8u) & 0xffu);
  return AUDIO_RESPONSE_OK;
}

static inline AUDIO_RESPONSE_UNUSED audio_response_status_t audio_response_write_int16(audio_response_writer_t *writer, int16_t value) {
  return audio_response_write_uint16(writer, (uint16_t)value);
}

static inline AUDIO_RESPONSE_UNUSED audio_response_status_t audio_response_write_uint32(audio_response_writer_t *writer, uint32_t value) {
  if (!audio_response_can_write(writer, 4)) {
    return AUDIO_RESPONSE_ERROR_BUFFER_TOO_SMALL;
  }
  writer->buffer[writer->offset++] = (uint8_t)(value & 0xffu);
  writer->buffer[writer->offset++] = (uint8_t)((value >> 8u) & 0xffu);
  writer->buffer[writer->offset++] = (uint8_t)((value >> 16u) & 0xffu);
  writer->buffer[writer->offset++] = (uint8_t)((value >> 24u) & 0xffu);
  return AUDIO_RESPONSE_OK;
}

static inline AUDIO_RESPONSE_UNUSED audio_response_status_t audio_response_write_int32(audio_response_writer_t *writer, int32_t value) {
  return audio_response_write_uint32(writer, (uint32_t)value);
}

static inline AUDIO_RESPONSE_UNUSED audio_response_status_t audio_response_write_uint64(audio_response_writer_t *writer, uint64_t value) {
  if (!audio_response_can_write(writer, 8)) {
    return AUDIO_RESPONSE_ERROR_BUFFER_TOO_SMALL;
  }
  for (size_t index = 0; index < 8; ++index) {
    writer->buffer[writer->offset++] = (uint8_t)((value >> (index * 8u)) & 0xffu);
  }
  return AUDIO_RESPONSE_OK;
}

static inline AUDIO_RESPONSE_UNUSED audio_response_status_t audio_response_write_float(audio_response_writer_t *writer, float value) {
  uint32_t bits;
  memcpy(&bits, &value, sizeof(bits));
  return audio_response_write_uint32(writer, bits);
}

static inline AUDIO_RESPONSE_UNUSED audio_response_status_t audio_response_write_double(audio_response_writer_t *writer, double value) {
  uint64_t bits;
  memcpy(&bits, &value, sizeof(bits));
  return audio_response_write_uint64(writer, bits);
}

static inline AUDIO_RESPONSE_UNUSED audio_response_status_t audio_response_read_uint8(audio_response_reader_t *reader, uint8_t *value) {
  if (!audio_response_can_read(reader, 1)) {
    return AUDIO_RESPONSE_ERROR_INVALID_DATA;
  }
  *value = reader->buffer[reader->offset++];
  return AUDIO_RESPONSE_OK;
}

static inline AUDIO_RESPONSE_UNUSED audio_response_status_t audio_response_read_int8(audio_response_reader_t *reader, int8_t *value) {
  uint8_t raw_value;
  audio_response_status_t status = audio_response_read_uint8(reader, &raw_value);
  if (status != AUDIO_RESPONSE_OK) {
    return status;
  }
  *value = (int8_t)raw_value;
  return AUDIO_RESPONSE_OK;
}

static inline AUDIO_RESPONSE_UNUSED audio_response_status_t audio_response_read_uint16(audio_response_reader_t *reader, uint16_t *value) {
  if (!audio_response_can_read(reader, 2)) {
    return AUDIO_RESPONSE_ERROR_INVALID_DATA;
  }
  *value = (uint16_t)reader->buffer[reader->offset]
      | ((uint16_t)reader->buffer[reader->offset + 1] << 8u);
  reader->offset += 2;
  return AUDIO_RESPONSE_OK;
}

static inline AUDIO_RESPONSE_UNUSED audio_response_status_t audio_response_read_int16(audio_response_reader_t *reader, int16_t *value) {
  uint16_t raw_value;
  audio_response_status_t status = audio_response_read_uint16(reader, &raw_value);
  if (status != AUDIO_RESPONSE_OK) {
    return status;
  }
  *value = (int16_t)raw_value;
  return AUDIO_RESPONSE_OK;
}

static inline AUDIO_RESPONSE_UNUSED audio_response_status_t audio_response_read_uint32(audio_response_reader_t *reader, uint32_t *value) {
  if (!audio_response_can_read(reader, 4)) {
    return AUDIO_RESPONSE_ERROR_INVALID_DATA;
  }
  *value = (uint32_t)reader->buffer[reader->offset]
      | ((uint32_t)reader->buffer[reader->offset + 1] << 8u)
      | ((uint32_t)reader->buffer[reader->offset + 2] << 16u)
      | ((uint32_t)reader->buffer[reader->offset + 3] << 24u);
  reader->offset += 4;
  return AUDIO_RESPONSE_OK;
}

static inline AUDIO_RESPONSE_UNUSED audio_response_status_t audio_response_read_int32(audio_response_reader_t *reader, int32_t *value) {
  uint32_t raw_value;
  audio_response_status_t status = audio_response_read_uint32(reader, &raw_value);
  if (status != AUDIO_RESPONSE_OK) {
    return status;
  }
  *value = (int32_t)raw_value;
  return AUDIO_RESPONSE_OK;
}

static inline AUDIO_RESPONSE_UNUSED audio_response_status_t audio_response_read_uint64(audio_response_reader_t *reader, uint64_t *value) {
  if (!audio_response_can_read(reader, 8)) {
    return AUDIO_RESPONSE_ERROR_INVALID_DATA;
  }
  *value = 0;
  for (size_t index = 0; index < 8; ++index) {
    *value |= (uint64_t)reader->buffer[reader->offset + index] << (index * 8u);
  }
  reader->offset += 8;
  return AUDIO_RESPONSE_OK;
}

static inline AUDIO_RESPONSE_UNUSED audio_response_status_t audio_response_read_float(audio_response_reader_t *reader, float *value) {
  uint32_t bits;
  audio_response_status_t status = audio_response_read_uint32(reader, &bits);
  if (status != AUDIO_RESPONSE_OK) {
    return status;
  }
  memcpy(value, &bits, sizeof(bits));
  return AUDIO_RESPONSE_OK;
}

static inline AUDIO_RESPONSE_UNUSED audio_response_status_t audio_response_read_double(audio_response_reader_t *reader, double *value) {
  uint64_t bits;
  audio_response_status_t status = audio_response_read_uint64(reader, &bits);
  if (status != AUDIO_RESPONSE_OK) {
    return status;
  }
  memcpy(value, &bits, sizeof(bits));
  return AUDIO_RESPONSE_OK;
}

static inline AUDIO_RESPONSE_UNUSED audio_response_status_t audio_response_write_bytes(audio_response_writer_t *writer, const uint8_t *value, size_t length) {
  if (!audio_response_can_write(writer, length)) {
    return AUDIO_RESPONSE_ERROR_BUFFER_TOO_SMALL;
  }
  for (size_t index = 0; index < length; ++index) {
    writer->buffer[writer->offset++] = value[index];
  }
  return AUDIO_RESPONSE_OK;
}

static inline AUDIO_RESPONSE_UNUSED audio_response_status_t audio_response_read_bytes(audio_response_reader_t *reader, uint8_t *value, size_t length) {
  if (!audio_response_can_read(reader, length)) {
    return AUDIO_RESPONSE_ERROR_INVALID_DATA;
  }
  for (size_t index = 0; index < length; ++index) {
    value[index] = reader->buffer[reader->offset++];
  }
  return AUDIO_RESPONSE_OK;
}

static audio_response_status_t audio_response_buffer_write(audio_response_writer_t *writer, const audio_response_buffer_t *message) {
  audio_response_status_t status;
  status = audio_response_write_uint16(writer, message->length);
  if (status != AUDIO_RESPONSE_OK) return status;
  status = audio_response_write_uint16(writer, message->sampling_rate);
  if (status != AUDIO_RESPONSE_OK) return status;
  status = audio_response_write_bytes(writer, message->buffer, message->length);
  if (status != AUDIO_RESPONSE_OK) return status;
  return AUDIO_RESPONSE_OK;
}

static audio_response_status_t audio_response_buffer_read(audio_response_reader_t *reader, audio_response_buffer_t *message) {
  audio_response_status_t status;
  status = audio_response_read_uint16(reader, &message->length);
  if (status != AUDIO_RESPONSE_OK) return status;
  status = audio_response_read_uint16(reader, &message->sampling_rate);
  if (status != AUDIO_RESPONSE_OK) return status;
  status = audio_response_read_bytes(reader, message->buffer, message->length);
  if (status != AUDIO_RESPONSE_OK) return status;
  return AUDIO_RESPONSE_OK;
}

audio_response_status_t audio_response_buffer_encode(const audio_response_buffer_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written) {
  audio_response_writer_t writer = { buffer, buffer_size, 0 };
  audio_response_status_t status = audio_response_buffer_write(&writer, message);
  if (status != AUDIO_RESPONSE_OK) {
    return status;
  }
  if (bytes_written != NULL) {
    *bytes_written = writer.offset;
  }
  return AUDIO_RESPONSE_OK;
}

audio_response_status_t audio_response_buffer_decode(audio_response_buffer_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read) {
  audio_response_reader_t reader = { buffer, buffer_size, 0 };
  audio_response_status_t status = audio_response_buffer_read(&reader, message);
  if (status != AUDIO_RESPONSE_OK) {
    return status;
  }
  if (bytes_read != NULL) {
    *bytes_read = reader.offset;
  }
  return AUDIO_RESPONSE_OK;
}

static audio_response_status_t audio_response_tone_write(audio_response_writer_t *writer, const audio_response_tone_t *message) {
  audio_response_status_t status;
  status = audio_response_write_uint16(writer, message->frequency);
  if (status != AUDIO_RESPONSE_OK) return status;
  status = audio_response_write_uint16(writer, message->duration);
  if (status != AUDIO_RESPONSE_OK) return status;
  return AUDIO_RESPONSE_OK;
}

static audio_response_status_t audio_response_tone_read(audio_response_reader_t *reader, audio_response_tone_t *message) {
  audio_response_status_t status;
  status = audio_response_read_uint16(reader, &message->frequency);
  if (status != AUDIO_RESPONSE_OK) return status;
  status = audio_response_read_uint16(reader, &message->duration);
  if (status != AUDIO_RESPONSE_OK) return status;
  return AUDIO_RESPONSE_OK;
}

audio_response_status_t audio_response_tone_encode(const audio_response_tone_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written) {
  audio_response_writer_t writer = { buffer, buffer_size, 0 };
  audio_response_status_t status = audio_response_tone_write(&writer, message);
  if (status != AUDIO_RESPONSE_OK) {
    return status;
  }
  if (bytes_written != NULL) {
    *bytes_written = writer.offset;
  }
  return AUDIO_RESPONSE_OK;
}

audio_response_status_t audio_response_tone_decode(audio_response_tone_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read) {
  audio_response_reader_t reader = { buffer, buffer_size, 0 };
  audio_response_status_t status = audio_response_tone_read(&reader, message);
  if (status != AUDIO_RESPONSE_OK) {
    return status;
  }
  if (bytes_read != NULL) {
    *bytes_read = reader.offset;
  }
  return AUDIO_RESPONSE_OK;
}

static audio_response_status_t audio_response_audio_response_write(audio_response_writer_t *writer, const audio_response_audio_response_t *message) {
  audio_response_status_t status;
  status = audio_response_write_uint8(writer, message->points);
  if (status != AUDIO_RESPONSE_OK) return status;
  for (size_t index = 0; index < message->points; ++index) {
    status = audio_response_write_uint16(writer, message->frequencies[index]);
    if (status != AUDIO_RESPONSE_OK) return status;
  }
  for (size_t index = 0; index < message->points; ++index) {
    status = audio_response_write_uint16(writer, message->response[index]);
    if (status != AUDIO_RESPONSE_OK) return status;
  }
  return AUDIO_RESPONSE_OK;
}

static audio_response_status_t audio_response_audio_response_read(audio_response_reader_t *reader, audio_response_audio_response_t *message) {
  audio_response_status_t status;
  status = audio_response_read_uint8(reader, &message->points);
  if (status != AUDIO_RESPONSE_OK) return status;
  for (size_t index = 0; index < message->points; ++index) {
    status = audio_response_read_uint16(reader, &message->frequencies[index]);
    if (status != AUDIO_RESPONSE_OK) return status;
  }
  for (size_t index = 0; index < message->points; ++index) {
    status = audio_response_read_uint16(reader, &message->response[index]);
    if (status != AUDIO_RESPONSE_OK) return status;
  }
  return AUDIO_RESPONSE_OK;
}

audio_response_status_t audio_response_audio_response_encode(const audio_response_audio_response_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written) {
  audio_response_writer_t writer = { buffer, buffer_size, 0 };
  audio_response_status_t status = audio_response_audio_response_write(&writer, message);
  if (status != AUDIO_RESPONSE_OK) {
    return status;
  }
  if (bytes_written != NULL) {
    *bytes_written = writer.offset;
  }
  return AUDIO_RESPONSE_OK;
}

audio_response_status_t audio_response_audio_response_decode(audio_response_audio_response_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read) {
  audio_response_reader_t reader = { buffer, buffer_size, 0 };
  audio_response_status_t status = audio_response_audio_response_read(&reader, message);
  if (status != AUDIO_RESPONSE_OK) {
    return status;
  }
  if (bytes_read != NULL) {
    *bytes_read = reader.offset;
  }
  return AUDIO_RESPONSE_OK;
}

static audio_response_status_t audio_response_sound_write(audio_response_writer_t *writer, const audio_response_sound_t *message) {
  audio_response_status_t status;
  status = audio_response_write_uint8(writer, message->type);
  if (status != AUDIO_RESPONSE_OK) return status;
  switch (message->type) {
  case 0:
    status = audio_response_buffer_write(writer, &message->data.buffer);
    if (status != AUDIO_RESPONSE_OK) return status;
    break;
  case 1:
    status = audio_response_tone_write(writer, &message->data.tone);
    if (status != AUDIO_RESPONSE_OK) return status;
    break;
  default:
    return AUDIO_RESPONSE_ERROR_INVALID_DATA;
  }
  return AUDIO_RESPONSE_OK;
}

static audio_response_status_t audio_response_sound_read(audio_response_reader_t *reader, audio_response_sound_t *message) {
  audio_response_status_t status;
  status = audio_response_read_uint8(reader, &message->type);
  if (status != AUDIO_RESPONSE_OK) return status;
  switch (message->type) {
  case 0:
    status = audio_response_buffer_read(reader, &message->data.buffer);
    if (status != AUDIO_RESPONSE_OK) return status;
    break;
  case 1:
    status = audio_response_tone_read(reader, &message->data.tone);
    if (status != AUDIO_RESPONSE_OK) return status;
    break;
  default:
    return AUDIO_RESPONSE_ERROR_INVALID_DATA;
  }
  return AUDIO_RESPONSE_OK;
}

audio_response_status_t audio_response_sound_encode(const audio_response_sound_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written) {
  audio_response_writer_t writer = { buffer, buffer_size, 0 };
  audio_response_status_t status = audio_response_sound_write(&writer, message);
  if (status != AUDIO_RESPONSE_OK) {
    return status;
  }
  if (bytes_written != NULL) {
    *bytes_written = writer.offset;
  }
  return AUDIO_RESPONSE_OK;
}

audio_response_status_t audio_response_sound_decode(audio_response_sound_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read) {
  audio_response_reader_t reader = { buffer, buffer_size, 0 };
  audio_response_status_t status = audio_response_sound_read(&reader, message);
  if (status != AUDIO_RESPONSE_OK) {
    return status;
  }
  if (bytes_read != NULL) {
    *bytes_read = reader.offset;
  }
  return AUDIO_RESPONSE_OK;
}


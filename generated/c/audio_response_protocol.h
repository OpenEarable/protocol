// Generated from schemas/audio-response/protocol.yml. Do not edit by hand.
#ifndef AUDIO_RESPONSE_PROTOCOL_H
#define AUDIO_RESPONSE_PROTOCOL_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  AUDIO_RESPONSE_OK = 0,
  AUDIO_RESPONSE_ERROR_BUFFER_TOO_SMALL = 1,
  AUDIO_RESPONSE_ERROR_INVALID_DATA = 2,
} audio_response_status_t;

typedef struct audio_response_buffer_t audio_response_buffer_t;
struct audio_response_buffer_t {
  uint16_t length;
  uint16_t sampling_rate;
  uint8_t *buffer;
};


typedef struct audio_response_tone_t audio_response_tone_t;
struct audio_response_tone_t {
  uint16_t frequency;
  uint16_t duration;
};


typedef struct audio_response_audio_response_t audio_response_audio_response_t;
struct audio_response_audio_response_t {
  uint8_t points;
  uint16_t *frequencies;
  uint16_t *response;
};


typedef struct audio_response_sound_t audio_response_sound_t;
struct audio_response_sound_t {
  uint8_t type;
  union {
    audio_response_buffer_t buffer;
    audio_response_tone_t tone;
  } data;
};


audio_response_status_t audio_response_buffer_encode(const audio_response_buffer_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written);
audio_response_status_t audio_response_buffer_decode(audio_response_buffer_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read);

audio_response_status_t audio_response_tone_encode(const audio_response_tone_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written);
audio_response_status_t audio_response_tone_decode(audio_response_tone_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read);

audio_response_status_t audio_response_audio_response_encode(const audio_response_audio_response_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written);
audio_response_status_t audio_response_audio_response_decode(audio_response_audio_response_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read);

audio_response_status_t audio_response_sound_encode(const audio_response_sound_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written);
audio_response_status_t audio_response_sound_decode(audio_response_sound_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read);

#ifdef __cplusplus
}
#endif

#endif /* AUDIO_RESPONSE_PROTOCOL_H */

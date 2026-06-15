// Generated from schemas/audio-response/protocol.yml. Do not edit by hand.
#pragma once

#include "protocol_runtime.h"

#define AUDIO_RESPONSE_BLE_SERVICE_UUID "7467b395-9043-4453-bc5c-2d8e8b10680a"
#define AUDIO_RESPONSE_BLE_TRANSFER_CONTROL_CHARACTERISTIC_UUID "7467b398-9043-4453-bc5c-2d8e8b10680a"
#define AUDIO_RESPONSE_BLE_TRANSFER_CONTROL_CHARACTERISTIC_PROPERTIES (PROTOCOL_BLE_PROPERTY_WRITE)
#define AUDIO_RESPONSE_BLE_TRANSFER_DATA_CHARACTERISTIC_UUID "7467b399-9043-4453-bc5c-2d8e8b10680a"
#define AUDIO_RESPONSE_BLE_TRANSFER_DATA_CHARACTERISTIC_PROPERTIES (PROTOCOL_BLE_PROPERTY_WRITE_WITHOUT_RESPONSE)
#define AUDIO_RESPONSE_BLE_TRANSFER_STATUS_CHARACTERISTIC_UUID "7467b39a-9043-4453-bc5c-2d8e8b10680a"
#define AUDIO_RESPONSE_BLE_TRANSFER_STATUS_CHARACTERISTIC_PROPERTIES (PROTOCOL_BLE_PROPERTY_NOTIFY)
#define AUDIO_RESPONSE_BLE_CONFIG_CHARACTERISTIC_UUID "7467b39b-9043-4453-bc5c-2d8e8b10680a"
#define AUDIO_RESPONSE_BLE_CONFIG_CHARACTERISTIC_PROPERTIES (PROTOCOL_BLE_PROPERTY_WRITE)
#define AUDIO_RESPONSE_BLE_RESULT_CHARACTERISTIC_UUID "7467b39c-9043-4453-bc5c-2d8e8b10680a"
#define AUDIO_RESPONSE_BLE_RESULT_CHARACTERISTIC_PROPERTIES (PROTOCOL_BLE_PROPERTY_NOTIFY)

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Starts uploading an audio sample buffer. The checksum is CRC-32/ISO-HDLC over all
 * little-endian encoded samples.
 */
typedef struct audio_response_transfer_start_t audio_response_transfer_start_t;
struct audio_response_transfer_start_t {
  uint16_t transfer_id;
  uint32_t total_samples;
  uint32_t sampling_rate;
  uint32_t checksum;
};


/** Validates and makes a completely uploaded audio sample buffer available. */
typedef struct audio_response_transfer_commit_t audio_response_transfer_commit_t;
struct audio_response_transfer_commit_t {
  uint16_t transfer_id;
};


/** Aborts an active audio sample buffer upload. */
typedef struct audio_response_transfer_abort_t audio_response_transfer_abort_t;
struct audio_response_transfer_abort_t {
  uint16_t transfer_id;
};


typedef enum audio_response_transfer_control_type_t {
  AUDIO_RESPONSE_TRANSFER_CONTROL_START = 0,
  AUDIO_RESPONSE_TRANSFER_CONTROL_COMMIT = 1,
  AUDIO_RESPONSE_TRANSFER_CONTROL_ABORT = 2,
} audio_response_transfer_control_type_t;

/**
 * A tagged transfer control command. Type 0 starts, type 1 commits, and type 2 aborts a
 * transfer.
 */
typedef struct audio_response_transfer_control_t audio_response_transfer_control_t;
struct audio_response_transfer_control_t {
  audio_response_transfer_control_type_t type;
  union {
    audio_response_transfer_start_t transfer_start;
    audio_response_transfer_commit_t transfer_commit;
    audio_response_transfer_abort_t transfer_abort;
  } command;
};


/** Uploads a contiguous section of an audio sample buffer. */
typedef struct audio_response_transfer_chunk_t audio_response_transfer_chunk_t;
struct audio_response_transfer_chunk_t {
  uint16_t transfer_id;
  uint32_t sample_offset;
  uint16_t sample_count;
  int16_t *samples;
};


/** Reports transfer progress, available chunk credits, or an error. */
typedef struct audio_response_transfer_status_t audio_response_transfer_status_t;
struct audio_response_transfer_status_t {
  uint16_t transfer_id;
  uint8_t status;
  uint32_t next_sample_offset;
  uint16_t credits;
};


/** Starts an audio response measurement using a committed audio sample buffer. */
typedef struct audio_response_config_t audio_response_config_t;
struct audio_response_config_t {
  uint8_t id;
  uint16_t transfer_id;
  float volume;
};


/**
 * A message containing audio response data. Each point represents a frequency and its
 * corresponding response value.
 */
typedef struct audio_response_result_t audio_response_result_t;
struct audio_response_result_t {
  uint8_t id;
  uint8_t points;
  uint16_t *frequencies;
  uint16_t *response;
};


/** Typed handlers used to dispatch transfer_control.command. */
typedef struct audio_response_transfer_control_handler_t {
  protocol_status_t (*start)(void *context, const audio_response_transfer_start_t *command);
  protocol_status_t (*commit)(void *context, const audio_response_transfer_commit_t *command);
  protocol_status_t (*abort)(void *context, const audio_response_transfer_abort_t *command);
} audio_response_transfer_control_handler_t;

/** Set transfer_control.command to transfer_start. */
void audio_response_transfer_control_set_command_start(audio_response_transfer_control_t *message, audio_response_transfer_start_t command);
/** Build a transfer_control message containing transfer_start. */
audio_response_transfer_control_t audio_response_transfer_control_from_start(audio_response_transfer_start_t command);
/** Set transfer_control.command to transfer_commit. */
void audio_response_transfer_control_set_command_commit(audio_response_transfer_control_t *message, audio_response_transfer_commit_t command);
/** Build a transfer_control message containing transfer_commit. */
audio_response_transfer_control_t audio_response_transfer_control_from_commit(audio_response_transfer_commit_t command);
/** Set transfer_control.command to transfer_abort. */
void audio_response_transfer_control_set_command_abort(audio_response_transfer_control_t *message, audio_response_transfer_abort_t command);
/** Build a transfer_control message containing transfer_abort. */
audio_response_transfer_control_t audio_response_transfer_control_from_abort(audio_response_transfer_abort_t command);
/** Dispatch transfer_control.command to its typed handler. */
protocol_status_t audio_response_transfer_control_dispatch(const audio_response_transfer_control_t *message, const audio_response_transfer_control_handler_t *handler, void *context);

/**
 * Encode a binary representation of this message. Starts uploading an audio sample buffer.
 * The checksum is CRC-32/ISO-HDLC over all little-endian encoded samples.
 */
protocol_status_t audio_response_transfer_start_encode(const audio_response_transfer_start_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written);
/**
 * Decode a binary representation into this message. Starts uploading an audio sample
 * buffer. The checksum is CRC-32/ISO-HDLC over all little-endian encoded samples.
 */
protocol_status_t audio_response_transfer_start_decode(audio_response_transfer_start_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read);

/**
 * Encode a binary representation of this message. Validates and makes a completely
 * uploaded audio sample buffer available.
 */
protocol_status_t audio_response_transfer_commit_encode(const audio_response_transfer_commit_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written);
/**
 * Decode a binary representation into this message. Validates and makes a completely
 * uploaded audio sample buffer available.
 */
protocol_status_t audio_response_transfer_commit_decode(audio_response_transfer_commit_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read);

/**
 * Encode a binary representation of this message. Aborts an active audio sample buffer
 * upload.
 */
protocol_status_t audio_response_transfer_abort_encode(const audio_response_transfer_abort_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written);
/**
 * Decode a binary representation into this message. Aborts an active audio sample buffer
 * upload.
 */
protocol_status_t audio_response_transfer_abort_decode(audio_response_transfer_abort_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read);

/**
 * Encode a binary representation of this message. A tagged transfer control command. Type
 * 0 starts, type 1 commits, and type 2 aborts a transfer.
 */
protocol_status_t audio_response_transfer_control_encode(const audio_response_transfer_control_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written);
/**
 * Decode a binary representation into this message. A tagged transfer control command.
 * Type 0 starts, type 1 commits, and type 2 aborts a transfer.
 */
protocol_status_t audio_response_transfer_control_decode(audio_response_transfer_control_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read);

/**
 * Encode a binary representation of this message. Uploads a contiguous section of an audio
 * sample buffer.
 */
protocol_status_t audio_response_transfer_chunk_encode(const audio_response_transfer_chunk_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written);
/**
 * Decode a binary representation into this message. Uploads a contiguous section of an
 * audio sample buffer.
 */
protocol_status_t audio_response_transfer_chunk_decode(audio_response_transfer_chunk_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read);

/**
 * Encode a binary representation of this message. Reports transfer progress, available
 * chunk credits, or an error.
 */
protocol_status_t audio_response_transfer_status_encode(const audio_response_transfer_status_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written);
/**
 * Decode a binary representation into this message. Reports transfer progress, available
 * chunk credits, or an error.
 */
protocol_status_t audio_response_transfer_status_decode(audio_response_transfer_status_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read);

/**
 * Encode a binary representation of this message. Starts an audio response measurement
 * using a committed audio sample buffer.
 */
protocol_status_t audio_response_config_encode(const audio_response_config_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written);
/**
 * Decode a binary representation into this message. Starts an audio response measurement
 * using a committed audio sample buffer.
 */
protocol_status_t audio_response_config_decode(audio_response_config_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read);

/**
 * Encode a binary representation of this message. A message containing audio response
 * data. Each point represents a frequency and its corresponding response value.
 */
protocol_status_t audio_response_result_encode(const audio_response_result_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written);
/**
 * Decode a binary representation into this message. A message containing audio response
 * data. Each point represents a frequency and its corresponding response value.
 */
protocol_status_t audio_response_result_decode(audio_response_result_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read);

#ifdef __cplusplus
}
#endif


// Generated from schemas/audio-configuration/protocol.yml. Do not edit by hand.
#pragma once

#include "protocol_runtime.h"

#define AUDIO_CONFIGURATION_BLE_SERVICE_UUID "1410df95-5f68-4ebb-a7c7-5e0fb9ae7557"
#define AUDIO_CONFIGURATION_BLE_AUDIO_MODE_CHARACTERISTIC_UUID "1410df96-5f68-4ebb-a7c7-5e0fb9ae7557"
#define AUDIO_CONFIGURATION_BLE_AUDIO_MODE_CHARACTERISTIC_PROPERTIES (PROTOCOL_BLE_PROPERTY_READ | PROTOCOL_BLE_PROPERTY_WRITE)
#define AUDIO_CONFIGURATION_BLE_MICROPHONE_SELECTION_CHARACTERISTIC_UUID "1410df97-5f68-4ebb-a7c7-5e0fb9ae7557"
#define AUDIO_CONFIGURATION_BLE_MICROPHONE_SELECTION_CHARACTERISTIC_PROPERTIES (PROTOCOL_BLE_PROPERTY_READ | PROTOCOL_BLE_PROPERTY_WRITE)
#define AUDIO_CONFIGURATION_BLE_AUDIO_CHANNEL_CHARACTERISTIC_UUID "1410df98-5f68-4ebb-a7c7-5e0fb9ae7557"
#define AUDIO_CONFIGURATION_BLE_AUDIO_CHANNEL_CHARACTERISTIC_PROPERTIES (PROTOCOL_BLE_PROPERTY_READ)
#define AUDIO_CONFIGURATION_BLE_MICROPHONE_GAIN_CHARACTERISTIC_UUID "1410df99-5f68-4ebb-a7c7-5e0fb9ae7557"
#define AUDIO_CONFIGURATION_BLE_MICROPHONE_GAIN_CHARACTERISTIC_PROPERTIES (PROTOCOL_BLE_PROPERTY_READ | PROTOCOL_BLE_PROPERTY_WRITE)

#ifdef __cplusplus
extern "C" {
#endif

/** Audio mode: 0 normal, 1 transparency, 2 ANC. */
typedef struct audio_configuration_audio_mode_t audio_configuration_audio_mode_t;
struct audio_configuration_audio_mode_t {
  uint8_t mode;
};


/** Encoder microphone: 0 left, 1 right. */
typedef struct audio_configuration_microphone_selection_t audio_configuration_microphone_selection_t;
struct audio_configuration_microphone_selection_t {
  uint8_t microphone;
};


/** Assigned audio channel. */
typedef struct audio_configuration_audio_channel_t audio_configuration_audio_channel_t;
struct audio_configuration_audio_channel_t {
  uint8_t channel;
};


/** Raw DMIC gain registers in outer then inner microphone order. */
typedef struct audio_configuration_microphone_gain_t audio_configuration_microphone_gain_t;
struct audio_configuration_microphone_gain_t {
  uint8_t outer;
  uint8_t inner;
};


/**
 * Encode a binary representation of this message. Audio mode: 0 normal, 1 transparency, 2
 * ANC.
 */
protocol_status_t audio_configuration_audio_mode_encode(const audio_configuration_audio_mode_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written);
/**
 * Decode a binary representation into this message. Audio mode: 0 normal, 1 transparency,
 * 2 ANC.
 */
protocol_status_t audio_configuration_audio_mode_decode(audio_configuration_audio_mode_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read);

/** Encode a binary representation of this message. Encoder microphone: 0 left, 1 right. */
protocol_status_t audio_configuration_microphone_selection_encode(const audio_configuration_microphone_selection_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written);
/** Decode a binary representation into this message. Encoder microphone: 0 left, 1 right. */
protocol_status_t audio_configuration_microphone_selection_decode(audio_configuration_microphone_selection_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read);

/** Encode a binary representation of this message. Assigned audio channel. */
protocol_status_t audio_configuration_audio_channel_encode(const audio_configuration_audio_channel_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written);
/** Decode a binary representation into this message. Assigned audio channel. */
protocol_status_t audio_configuration_audio_channel_decode(audio_configuration_audio_channel_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read);

/**
 * Encode a binary representation of this message. Raw DMIC gain registers in outer then
 * inner microphone order.
 */
protocol_status_t audio_configuration_microphone_gain_encode(const audio_configuration_microphone_gain_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written);
/**
 * Decode a binary representation into this message. Raw DMIC gain registers in outer then
 * inner microphone order.
 */
protocol_status_t audio_configuration_microphone_gain_decode(audio_configuration_microphone_gain_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read);

#ifdef __cplusplus
}
#endif


// Generated from schemas/power-saving/protocol.yml. Do not edit by hand.
#pragma once

#include "protocol_runtime.h"

#define POWER_SAVING_BLE_SERVICE_UUID "d63fd1f0-5f68-4ebb-a7c7-5e0fb9ae7557"
#define POWER_SAVING_BLE_MODE_CHARACTERISTIC_UUID "d63fd1f1-5f68-4ebb-a7c7-5e0fb9ae7557"
#define POWER_SAVING_BLE_MODE_CHARACTERISTIC_PROPERTIES (PROTOCOL_BLE_PROPERTY_READ | PROTOCOL_BLE_PROPERTY_WRITE)
#define POWER_SAVING_BLE_SUPPORTED_MODES_CHARACTERISTIC_UUID "d63fd1f2-5f68-4ebb-a7c7-5e0fb9ae7557"
#define POWER_SAVING_BLE_SUPPORTED_MODES_CHARACTERISTIC_PROPERTIES (PROTOCOL_BLE_PROPERTY_READ)

#ifdef __cplusplus
extern "C" {
#endif

/** Selected automatic power-off mode identified by its supported-mode ID. */
typedef struct power_saving_mode_t power_saving_mode_t;
struct power_saving_mode_t {
  uint8_t id;
};


/** Supported mode ID and its display name without a terminating NUL. */
typedef struct power_saving_mode_description_t power_saving_mode_description_t;
struct power_saving_mode_description_t {
  uint8_t id;
  uint8_t name_length;
  uint8_t *name;
  /** Caller-owned decode capacity in bytes; not encoded. */
  size_t name_capacity;
};


/** Supported automatic power-off modes in display order. */
typedef struct power_saving_supported_modes_t power_saving_supported_modes_t;
struct power_saving_supported_modes_t {
  uint8_t count;
  power_saving_mode_description_t *modes;
  /** Caller-owned decode capacity in elements; not encoded. */
  size_t modes_capacity;
};


/**
 * Encode a binary representation of this message. Selected automatic power-off mode
 * identified by its supported-mode ID.
 */
protocol_status_t power_saving_mode_encode(const power_saving_mode_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written);
/**
 * Decode a binary representation into this message. Selected automatic power-off mode
 * identified by its supported-mode ID.
 */
protocol_status_t power_saving_mode_decode(power_saving_mode_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read);

/**
 * Encode a binary representation of this message. Supported mode ID and its display name
 * without a terminating NUL.
 */
protocol_status_t power_saving_mode_description_encode(const power_saving_mode_description_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written);
/**
 * Decode a binary representation into this message. Supported mode ID and its display name
 * without a terminating NUL.
 */
protocol_status_t power_saving_mode_description_decode(power_saving_mode_description_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read);

/**
 * Encode a binary representation of this message. Supported automatic power-off modes in
 * display order.
 */
protocol_status_t power_saving_supported_modes_encode(const power_saving_supported_modes_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written);
/**
 * Decode a binary representation into this message. Supported automatic power-off modes in
 * display order.
 */
protocol_status_t power_saving_supported_modes_decode(power_saving_supported_modes_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read);

/** Decode using caller-provided capacities on every dynamic field. Output may be partial on failure. */
protocol_status_t power_saving_mode_decode_bounded(power_saving_mode_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read);

/** Decode using caller-provided capacities on every dynamic field. Output may be partial on failure. */
protocol_status_t power_saving_mode_description_decode_bounded(power_saving_mode_description_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read);

/** Decode using caller-provided capacities on every dynamic field. Output may be partial on failure. */
protocol_status_t power_saving_supported_modes_decode_bounded(power_saving_supported_modes_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read);

#ifdef __cplusplus
}
#endif


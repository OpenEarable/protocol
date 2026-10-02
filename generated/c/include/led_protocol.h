// Generated from schemas/led/protocol.yml. Do not edit by hand.
#pragma once

#include "protocol_runtime.h"

#define LED_BLE_SERVICE_UUID "81040a2e-4819-11ee-be56-0242ac120002"
#define LED_BLE_RGB_CHARACTERISTIC_UUID "81040e7a-4819-11ee-be56-0242ac120002"
#define LED_BLE_RGB_CHARACTERISTIC_PROPERTIES (PROTOCOL_BLE_PROPERTY_WRITE)
#define LED_BLE_STATE_CHARACTERISTIC_UUID "81040e7b-4819-11ee-be56-0242ac120002"
#define LED_BLE_STATE_CHARACTERISTIC_PROPERTIES (PROTOCOL_BLE_PROPERTY_WRITE)

#ifdef __cplusplus
extern "C" {
#endif

/** Custom color in red, green, blue order. */
typedef struct led_rgb_t led_rgb_t;
struct led_rgb_t {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
};


/** Indication mode: 0 state indication, 1 custom. */
typedef struct led_state_t led_state_t;
struct led_state_t {
  uint8_t mode;
};


/** Encode a binary representation of this message. Custom color in red, green, blue order. */
protocol_status_t led_rgb_encode(const led_rgb_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written);
/**
 * Decode a binary representation into this message. Custom color in red, green, blue
 * order.
 */
protocol_status_t led_rgb_decode(led_rgb_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read);

/**
 * Encode a binary representation of this message. Indication mode: 0 state indication, 1
 * custom.
 */
protocol_status_t led_state_encode(const led_state_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written);
/**
 * Decode a binary representation into this message. Indication mode: 0 state indication, 1
 * custom.
 */
protocol_status_t led_state_decode(led_state_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read);

#ifdef __cplusplus
}
#endif


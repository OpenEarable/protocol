// Generated from schemas/button/protocol.yml. Do not edit by hand.
#pragma once

#include "protocol_runtime.h"

#define BUTTON_BLE_SERVICE_UUID "29c10bdc-4773-11ee-be56-0242ac120002"
#define BUTTON_BLE_STATE_CHARACTERISTIC_UUID "29c10f38-4773-11ee-be56-0242ac120002"
#define BUTTON_BLE_STATE_CHARACTERISTIC_PROPERTIES (PROTOCOL_BLE_PROPERTY_READ | PROTOCOL_BLE_PROPERTY_NOTIFY)

#ifdef __cplusplus
extern "C" {
#endif

/** Button action: 0 released, 1 pressed. */
typedef struct button_state_t button_state_t;
struct button_state_t {
  uint8_t action;
};


/** Encode a binary representation of this message. Button action: 0 released, 1 pressed. */
protocol_status_t button_state_encode(const button_state_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written);
/** Decode a binary representation into this message. Button action: 0 released, 1 pressed. */
protocol_status_t button_state_decode(button_state_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read);

#ifdef __cplusplus
}
#endif


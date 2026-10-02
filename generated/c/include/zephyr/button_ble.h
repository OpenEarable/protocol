// Generated from schemas/button/protocol.yml. Do not edit by hand.
#pragma once

#include "button_protocol.h"
#include <zephyr/bluetooth/gatt.h>
#include <zephyr/bluetooth/uuid.h>

#define BUTTON_ZEPHYR_SERVICE_UUID BT_UUID_DECLARE_128(BT_UUID_128_ENCODE(0x29c10bdc, 0x4773, 0x11ee, 0xbe56, 0x0242ac120002))

#define BUTTON_ZEPHYR_STATE_CHARACTERISTIC_UUID BT_UUID_DECLARE_128(BT_UUID_128_ENCODE(0x29c10f38, 0x4773, 0x11ee, 0xbe56, 0x0242ac120002))
#define BUTTON_ZEPHYR_STATE_CHARACTERISTIC_PROPERTIES (BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY)
#define BUTTON_ZEPHYR_STATE_CHARACTERISTIC_PERMISSIONS (BT_GATT_PERM_READ)

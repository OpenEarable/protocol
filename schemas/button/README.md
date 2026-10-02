# Button protocol

Use this BLE service to read the latest play/pause button action and receive
notifications when that button is pressed or released.

Service UUID: `29c10bdc-4773-11ee-be56-0242ac120002`.

## Characteristic and payload

| Characteristic | UUID | Operations | Payload size |
|---|---|---|---|
| State | `29c10f38-4773-11ee-be56-0242ac120002` | Read, notify | 1 byte |

Reads and notifications carry the same single unsigned 8-bit value:

| Value | Action |
|---|---|
| `00` | Released |
| `01` | Pressed |

There is no button ID, timestamp, sequence number, message ID, or version byte.
The service forwards the play/pause button only; other physical buttons are not
identified by this payload. The characteristic is not writable.

## Receiving events

1. Connect and discover the service and State characteristic.
2. Enable notifications using the characteristic's Client Characteristic
   Configuration Descriptor (CCCD; notification value `01 00`). A BLE library's
   subscribe operation normally handles this descriptor write.
3. Read State to obtain the latest action, then handle subsequent notifications.

A notification containing `01` means the button was pressed; a later `00`
means it was released. The stored value starts at `00` and is updated even when
notifications are disabled, so reads return the latest recorded action.
Notifications contain live events, not a replay of actions missed while
unsubscribed or disconnected. A read and a notification can overlap; do not
interpret them as a sequence-numbered event history.

The message does not distinguish clicks, long presses, or double presses.
Applications that need those gestures must derive them from press/release
notifications and their own timing.

## Generated bindings

[`protocol.yml`](protocol.yml) defines the State message and BLE metadata.
In Dart, decode a characteristic value with `ButtonState.fromBytes(bytes)` and
inspect `action`. `ButtonBleUuids` exposes the service and State characteristic
definitions.

C provides `button_state_t` with an `action` field and
`button_state_encode` / `button_state_decode` in `button_protocol.h`. Zephyr
service definitions are available in `zephyr/button_ble.h`.

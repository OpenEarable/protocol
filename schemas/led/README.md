# LED protocol

Use this BLE service to display a custom RGB color or let the earable indicate
its connection, charging, and recording state automatically.

Service UUID: `81040a2e-4819-11ee-be56-0242ac120002`.

## Characteristics

| Characteristic | UUID | Operations | Payload size |
|---|---|---|---|
| RGB | `81040e7a-4819-11ee-be56-0242ac120002` | Read, write, notify | 3 bytes |
| State | `81040e7b-4819-11ee-be56-0242ac120002` | Read, write, notify | 1 byte |

Send the payload directly to its characteristic, without a message ID, length
prefix, or version byte. Firmware 2.3.x adds reads and notifications using the
same payloads and UUIDs. Older firmware is write-only: clients must check the
discovered characteristic properties before reading or subscribing.

## RGB color

The RGB payload contains three unsigned 8-bit color components:

| Byte offset | Field | Range |
|---|---|---|
| 0 | Red | 0–255 |
| 1 | Green | 0–255 |
| 2 | Blue | 0–255 |

Examples: `FF 00 00` is red, `00 FF 00` is green, `00 00 FF` is blue, and
`00 00 00` switches off the LED while custom mode is active.

Writing RGB stores the custom color. It updates the visible color immediately
when custom mode is active. In automatic mode, it stores the color for the next
switch to custom mode.

## Indication mode

Write a single byte to State:

| Value | Behavior |
|---|---|
| `00` | Automatic state indication; firmware chooses colors and animations |
| `01` | Custom mode; display the stored RGB color |

Use only these two values. The firmware callback does not reject
other numeric values on older versions; firmware 2.3.x rejects them with
ATT Value Not Allowed and preserves the current mode.

To show blue:

1. Write `00 00 FF` to RGB.
2. Write `01` to State to activate the stored color.

Further RGB writes change the color without another State write. Write `00`
to State to resume automatic indication. Firmware update (DFU) indication can
take priority over the custom color.

Use writes with response and offset zero. The firmware rejects RGB payloads
that are not exactly three bytes, State payloads that are not exactly one byte,
and writes with a nonzero offset. Successful writes have no separate response
payload.

## Readback and notifications

Read RGB to retrieve the stored custom color, including while automatic mode
is active. Read State to retrieve the configured indication mode. These are
configuration values, not the instantaneous color of a pulse or a DFU override.
At boot the custom color is black and the indication mode is automatic.

Subscribe using each characteristic’s CCC descriptor, then read its current
value. After a successful write, firmware notifies the accepted value to
subscribers. Rejected writes leave the configuration unchanged and produce no
notification. A successful write while unsubscribed remains valid. Settings
are volatile and reset at reboot, as before.

## Generated bindings

[`protocol.yml`](protocol.yml) defines both messages and their BLE metadata.
In Dart, use `LedRgb(red: 0, green: 0, blue: 255).toBytes()` for the blue payload
and `LedState(mode: 1).toBytes()` for custom mode. `LedBleUuids` exposes service
and characteristic definitions.

C provides `led_rgb_t`, `led_state_t`, and their `led_*_encode` /
`led_*_decode` functions in `led_protocol.h`. Zephyr service definitions are
available in `zephyr/led_ble.h`.

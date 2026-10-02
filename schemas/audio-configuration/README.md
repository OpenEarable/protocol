# Audio configuration protocol

Use this BLE service to select the audio processing mode, choose the microphone
channel sent to the audio encoder, adjust microphone gain, and read the earable's
assigned left/right audio channel.

Service UUID: `1410df95-5f68-4ebb-a7c7-5e0fb9ae7557`.

## Characteristics

| Characteristic | UUID | Operations | Payload size |
|---|---|---|---|
| Audio mode | `1410df96-5f68-4ebb-a7c7-5e0fb9ae7557` | Read, write | 1 byte |
| Microphone selection | `1410df97-5f68-4ebb-a7c7-5e0fb9ae7557` | Read, write | 1 byte |
| Audio channel | `1410df98-5f68-4ebb-a7c7-5e0fb9ae7557` | Read | 1 byte |
| Microphone gain | `1410df99-5f68-4ebb-a7c7-5e0fb9ae7557` | Read, write | 2 bytes |

Each characteristic carries its own message. Send the bytes below directly as
its value, without a message ID, length prefix, or version byte. All fields are
unsigned 8-bit integers. Reads return the same layout used for writes.

## Audio mode

The single byte selects the codec's audio processing mode:

| Value | Mode |
|---|---|
| `00` | Normal |
| `01` | Transparency |
| `02` | Active noise cancellation (ANC) |

For example, write `02` to Audio mode to enable ANC. Reading Audio mode returns
the current mode. Values above 2 are rejected.

## Microphone selection and audio channel

Write `00` to Microphone selection to use the left input channel for the mono
audio encoder, or `01` to use the right input channel. Read this characteristic
to retrieve the current selection. Other values are rejected.

Audio channel reports the earable's assigned channel: `00` means left and `01`
means right. It is read-only. Selecting an encoder microphone does not change
the earable's assigned audio channel.

## Microphone gain

The two bytes contain codec gain register values in this order:

| Byte offset | Field | Microphone |
|---|---|---|
| 0 | `outer` | Outer microphone (DMIC channel 0) |
| 1 | `inner` | Inner microphone (DMIC channel 1) |

These values encode gain rather than a percentage:

| Register value | Gain |
|---|---|
| `00` | +24 dB |
| `01` through `3F` | +23.625 through +0.375 dB |
| `40` | 0 dB |
| `41` through `FD` | −0.375 through −70.875 dB |
| `FE` | −71.25 dB |
| `FF` | Mute |

For values `00` through `FE`, gain in dB is `24 − 0.375 × value`.
For example, write `40 FF` to set the outer microphone to 0 dB and mute the inner
microphone. Read Microphone gain to retrieve both register values.

## Client workflow

1. Connect and discover the service and its characteristics.
2. Read the current settings to initialize the application controls.
3. Write a complete one- or two-byte value to the relevant characteristic.
4. Read it again when the application needs the resulting setting.

Use writes with response. Incorrect payload lengths are rejected with an ATT
invalid attribute length error; invalid mode or microphone selections produce
an ATT value not allowed error. Codec failures also produce a write error.
There are no notifications or separate application response messages.

## Generated bindings

[`protocol.yml`](protocol.yml) defines the message fields and BLE metadata.
The Dart classes are `AudioConfigurationAudioMode`,
`AudioConfigurationMicrophoneSelection`, `AudioConfigurationAudioChannel`, and
`AudioConfigurationMicrophoneGain`. Construct a value and call `toBytes()` for a
write; use `fromBytes()` to decode a read. `AudioConfigurationBleUuids` exposes
the service and characteristic definitions.

C provides corresponding `audio_configuration_*_t` types and
`audio_configuration_*_encode` / `audio_configuration_*_decode` functions in
`audio_configuration_protocol.h`. Zephyr service definitions are available in
`zephyr/audio_configuration_ble.h`.

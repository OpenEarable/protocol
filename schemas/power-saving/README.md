# Power-saving protocol

Use this BLE service to select how aggressively the earable powers off when it
is idle and to discover the selectable modes and their display names.

Service UUID: `d63fd1f0-5f68-4ebb-a7c7-5e0fb9ae7557`.

## Characteristics

| Characteristic | UUID | Operations |
|---|---|---|
| Mode | `d63fd1f1-5f68-4ebb-a7c7-5e0fb9ae7557` | Read, write |
| Supported modes | `d63fd1f2-5f68-4ebb-a7c7-5e0fb9ae7557` | Read |

There are no notifications or extra message/version headers. Use writes with
response at offset zero. Mode reads and writes carry exactly one byte: the mode
ID. The firmware rejects unsupported IDs and payloads with other lengths.

| ID | Display name | Behavior |
|---|---|---|
| `00` | Off | Disable automatic power-off |
| `01` | Minimal | Least aggressive enabled mode |
| `02` | Balanced | Intermediate automatic power-off policy |
| `03` | Aggressive | Most aggressive automatic power-off policy |

Higher enabled mode IDs use shorter configured idle timeouts and allow fewer
firmware components to veto automatic power-off. Timeout values are firmware
configuration, not fields in this protocol.

## Discovering supported modes

Supported modes returns a count byte followed by that many records:

| Field | Width | Meaning |
|---|---|---|
| `count` | 1 byte | Number of following mode records |
| `id` | 1 byte per record | ID used when reading/writing Mode |
| `name_length` | 1 byte per record | Number of name bytes |
| `name` | `name_length` bytes | Display name, without a terminating NUL |

For example, a list containing Off and Balanced is:

```text
02 00 03 4F 66 66 02 08 42 61 6C 61 6E 63 65 64
```

The first `02` is the record count. The first record is ID `00` with three bytes
spelling `Off`; the second is ID `02` with eight bytes spelling `Balanced`.
The firmware currently exposes all four modes and uses a 128-byte response
buffer. Read the list to populate controls instead of assuming every firmware
offers the same set of IDs.

A typical client discovers the service, reads Supported modes and Mode, then
writes the desired supported ID to Mode. For example, writing `02` selects
Balanced. Read Mode again when the application needs the resulting selection.

## Generated bindings

[`protocol.yml`](protocol.yml) defines `mode`, `mode_description`, and
`supported_modes`. In Dart, decode with
`PowerSavingSupportedModes.fromBytes(bytes)` and iterate over `modes`; each
record has `id`, `name_length`, and `name`. `PowerSavingMode(id: 2).toBytes()`
produces the write for Balanced. `PowerSavingBleUuids` exposes BLE metadata.

C uses `power_saving_supported_modes_t` and
`power_saving_mode_description_t`. Encoding reads the caller's record array and
name bytes synchronously without modifying them. For decoding, initialize
`modes`, `modes_capacity`, and every available record's `name` and
`name_capacity` before calling `power_saving_supported_modes_decode_bounded`.
Capacities describe allocated storage; decoded counts describe received data.
Insufficient storage returns `PROTOCOL_ERROR_BUFFER_TOO_SMALL`. Decoding does
not allocate memory, append NULs, or roll back partially decoded fields.

# PPG sensor data

The sensor stream uses service `34c2e3bb-34aa-11eb-adc1-0242ac120002`
and notify characteristic `34c2e3bc-34aa-11eb-adc1-0242ac120002`.
PPG keeps sensor ID **4** and its advertised four `uint32` logical components.

## Select the BLE format by firmware version

Read each device's firmware version before subscribing. Firmware **2.1.x and
2.2.x**, including 2.2.9 and 2.2.10, sends 16-byte samples. Firmware **2.3.x**
sends 10-byte samples. Development versions such as `2.3.0-dev.1+gabc` use the
2.3 format too. Keep this selection per connection, including mixed-version
stereo pairs, and refresh it after reconnect/FOTA. Do not infer the format from
packet length: some lengths are valid in both encodings.

There is no new packet discriminator, sensor ID, or characteristic. This is a
minor-version wire-format change; older clients need the new decoder to stream
PPG from 2.3 firmware. Updated clients continue supporting older firmware.

## Packet envelope (unchanged)

| Offset | Field |
|---|---|
| 0 | Sensor ID, `04` |
| 1 | Payload byte length, excluding the ten-byte header |
| 2–9 | First sample's uint64 timestamp, microseconds, little-endian |
| 10… | One or more samples |
| Last two bytes, only with multiple samples | uint16 sample period in microseconds, little-endian |

A single sample has no period suffix. Multiple samples share the first
timestamp and one period: timestamp(i) = first + i × period. The firmware's
existing bounded timestamp batching policy is unchanged.

## Sample encodings

The legacy sample is four little-endian uint32 values in **red, infrared,
green, ambient** order (16 bytes). It remains the format in **all SD/.oe files,
even when recorded by firmware 2.3.x**. File readers must not select compact
encoding based on the recording firmware version.

For BLE on 2.3.x, pack each of those values into 19 bits in the same order:

| Bits in the ten-byte little-endian sample | Value |
|---|---|
| 0–18 | Red |
| 19–37 | Infrared |
| 38–56 | Green |
| 57–75 | Ambient |
| 76–79 | Reserved, zero |

All sensor bits are retained; no rescaling, quantization, or channel removal
occurs. Values outside 0…524287 and nonzero reserved bits are invalid.

The schema represents the packed sample as two uint32 words `a`, `b` and a
uint16 word `c`, avoiding 64-bit bitwise arithmetic on Dart web. Decode with:

```
red      = a & 0x7ffff
infrared = (a >> 19) | ((b & 0x3f) << 13)
green    = (b >> 6) & 0x7ffff
ambient  = (b >> 25) | (c << 7)
```

For all four channels at full scale, the encoded sample is
`ff ff ff ff ff ff ff ff ff 0f`. Zero channels encode as ten zero bytes.
Per-sample payload shrinks by 37.5%. A 244-byte notification holds 23 compact
samples (242 bytes including header and period), versus 14 legacy samples
(236 bytes). This is packet capacity, not a guarantee of achieved BLE rate.

# IMU sensor data

Keep sensor ID **0**, the existing sensor-stream UUIDs, and the existing packet
header/timestamps. Read each device's firmware version before subscribing:
firmware 2.1.x/2.2.x sends nine little-endian float32 values (36 bytes/sample);
firmware 2.3.x, including prereleases, sends the 24-byte sample below. Select
per connection and refresh after reconnect/FOTA; do not infer from packet size.

| Byte offsets | Wire value |
|---|---|
| 0–5 | Accelerometer X/Y/Z, three little-endian signed int16 counts |
| 6–11 | Gyroscope X/Y/Z, three little-endian signed int16 counts |
| 12–23 | Magnetometer X/Y/Z, three unchanged little-endian float32 values in µT |

Restore the six motion values to float32 before applying the existing parsing
scheme or exposing values to applications:

- Acceleration in m/s²: `float32(raw * 0.0005985504249110818)`.
  This is exactly the firmware's float32 `(2.0f * 9.80665f) / 32768.0f` scale.
- Angular velocity in degrees/s: `float32(raw * 0.06103515625)`.
  This is exactly `2000.0f / 32768.0f`.

These scales are part of the 2.3.x wire contract, matching the existing ±2 g
and ±2000 degrees/s sensor configuration. Recover counts by rounding the
existing float divided by its scale; reject values outside int16 or values
that do not reconstruct the original float32 exactly. Do not round, rescale,
or remove magnetometer values: they already include factory compensation.

The advertised parsing scheme, library values/types/units and phone CSVs stay
unchanged. **All SD/.oe IMU samples remain nine float32 values (36 bytes)**,
including recordings from 2.3.x. File readers must use the legacy layout.

The packet envelope is unchanged: sensor ID (uint8), payload byte length
(uint8), first timestamp (uint64 microseconds), samples, then a uint16 period
in microseconds for multi-sample packets only. All integers are little-endian.
A 244-byte notification holds nine compact samples (228 bytes), versus six
legacy samples (228 bytes). Sample payload shrinks by one third; actual BLE
throughput still depends on radio scheduling and batching.

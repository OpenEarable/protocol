## Compact PPG

- Define firmware-selected BLE PPG packing; retain sensor ID, envelope, timestamps, and SD samples.

## [Unreleased]

* added `uint64` and `int64` scalar and array support; Dart uses `BigInt`
  to preserve the full range and rejects values outside the wire type range

* created wireless-audio-configuration protocol for device-owned ACL and
  Unicast Server policies plus read-only negotiated runtime state

## [0.0.2]

* created audio-response protocol

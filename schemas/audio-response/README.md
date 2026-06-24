# Audio Response

Audio response measures the response of an OpenEarable device while it plays an
uploaded signed 16-bit PCM sample buffer.

## BLE Transfer

Protocol version 1 transfers audio independently from starting a measurement so
buffers are not limited to a single GATT write. The transfer characteristics use
dedicated UUIDs and must not be confused with the config or result
characteristics.

1. Write a `transfer_control` containing `transfer_start`.
2. Wait for a successful `transfer_status` notification.
3. Write up to `credits` sequential `transfer_chunk` messages to
   `transfer_data`.
4. Wait for another `transfer_status` notification before exceeding the
   advertised credits.
5. Write a `transfer_control` containing `transfer_commit`.
6. After a successful committed status, write `config` to start the
   measurement.

Write a `transfer_control` containing `transfer_abort` to release an incomplete
transfer.

Transfer control discriminator values are:

| Value | Command |
| --- | --- |
| `0` | `transfer_start` |
| `1` | `transfer_commit` |
| `2` | `transfer_abort` |

Transfer status values are:

| Value | Status |
| --- | --- |
| `0` | Ready to receive chunks |
| `1` | Transfer committed |
| `2` | Transfer aborted |
| `3` | Invalid command or transfer state |
| `4` | Invalid chunk offset or length |
| `5` | Insufficient storage |
| `6` | Checksum mismatch |
| `7` | Transfer timed out |

Chunks must be contiguous and must use the `next_sample_offset` reported by the
most recent status. `credits` is the number of additional chunks the central
may send without waiting for another status notification. A sender must treat
zero credits as backpressure.

`transfer_start.checksum` is CRC-32/ISO-HDLC of the complete sample stream,
where every signed 16-bit sample is encoded little-endian. Its parameters are
polynomial `0x04C11DB7`, initial value `0xFFFFFFFF`, reflected input and output,
and final XOR `0xFFFFFFFF`. The firmware must validate the declared sample
count and checksum before committing a transfer.

The transfer chunk header occupies 8 bytes. The maximum samples per chunk are:

```text
floor((maximum characteristic write payload - 8) / 2)
```

For an ATT MTU of 247, the maximum write payload is 244 bytes and a chunk can
carry 118 samples. A 3,200-sample buffer therefore requires 28 chunks.

Firmware must reject oversized transfers and chunks, duplicate or unexpected
offsets, incomplete commits, and unknown transfer IDs. Incomplete transfers
should be released after an implementation-defined timeout.

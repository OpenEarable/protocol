# Wireless Audio Configuration Protocol

This protocol configures Bluetooth ACL behavior and LE Audio preferences without
conflating the ACL connection interval with the Connected Isochronous Stream
(CIS) SDU interval. All multi-byte values use little-endian encoding.

## Transport

Write a `configuration_command` to `command`. The device indicates exactly one
correlated `configuration_response` on `response` for every accepted write.
Malformed writes are rejected with an ATT error and do not produce a response.
The client must enable response indications before issuing a command; the
device must reject a command when the response CCC is not configured.

`runtime_state` can be read for a snapshot and notifies when effective or
negotiated values change. `capabilities` is read-only and describes the current
firmware build and Bluetooth controller. Clients must read it before writing an
optional configuration section.

The `request_id` is chosen by the client. A device copies it unchanged into the
response. Reusing an ID while an earlier command is outstanding is invalid.

The largest version 1 command or response is 40 bytes. Notifications of the
65-byte runtime state require an ATT MTU of at least 68 bytes; clients with a
smaller MTU can still retrieve it using a long read. The capabilities value is
64 bytes and is also readable using normal GATT long-read behavior.

## Diagrams

The [PlantUML diagram set](diagrams/README.md) covers command application,
configuration queries, runtime-state reporting, the adaptive-linear policy, and
the protocol message model. These diagrams describe the intended protocol
behavior for a future firmware implementation; they do not imply that the
firmware integration already exists.

## Stable identifiers

Numeric identifiers are permanent. New values may be added, but an assigned
value must never be reused with another meaning.

### Configuration sections

The following IDs identify configuration sections. Their corresponding bits are
used by `section_mask` and `supported_section_mask`:

| ID/bit | Section |
| --- | --- |
| 0 | ACL connection policy |
| 1 | ACL radio preferences |
| 2 | LC3 codec preferences |
| 3 | CIS ISO QoS preferences |

A zero `section_mask` means all supported sections for `restore_defaults`.
Unknown nonzero bits must be rejected. `get_configuration.section` accepts one
section ID and returns the matching configured-section response variant.

### Commands

Command tags are also represented by the corresponding bit in
`supported_command_mask`:

| Tag | Command |
| --- | --- |
| 0 | Set ACL connection policy |
| 1 | Set ACL radio preferences |
| 2 | Set LC3 preferences |
| 3 | Set ISO QoS preferences |
| 4 | Get configuration |
| 5 | Restore defaults |

`persist` must be 0 for a session-only setting or 1 to retain the setting across
device restarts. Any other value is invalid. A session-only setting remains in
effect until it is replaced, restored, or the device restarts.
`restore_defaults` clears persisted values in every selected section before
applying the firmware's compiled defaults.

### ACL connection policies

Policy tags are also represented by the corresponding bit in
`supported_acl_policy_mask`:

| Tag | Policy |
| --- | --- |
| 0 | Controller default |
| 1 | Fixed interval |
| 2 | Adaptive linear |

`controller_default_acl_policy.reserved` must be zero. It preserves a portable
C representation for this otherwise parameterless policy.

The adaptive-linear policy increases the requested interval once per reported
audio underrun episode. During stable streaming, it decreases the interval once
per `recovery_period_ms`. It never changes the interval more frequently than
`minimum_update_period_ms`. An implementation must saturate at the configured
minimum and maximum and must not use wrapping integer arithmetic.

ACL intervals must be exact multiples of the interval resolution reported in
`capabilities`. A requested fixed interval is still negotiated with the peer;
the effective value is reported in `runtime_state`.

### PHY values

PHY masks use bit 0 for LE 1M, bit 1 for LE 2M, and bit 2 for LE Coded. A zero
preference mask leaves selection to the Bluetooth stack. Effective PHY fields in
`runtime_state` contain one of these single-bit values, or zero when unknown.

### Directions

Direction masks use bit 0 for sink, meaning audio received by the device, and
bit 1 for source, meaning audio transmitted by the device. At least one
supported direction bit must be selected when setting LC3 or ISO QoS
preferences.

## Optional preference fields

Preference messages contain a `fields_present` mask. Values in fields whose bit
is clear must be encoded as zero and ignored by the receiver.

### ACL radio preferences

| Bit | Field |
| --- | --- |
| 0 | `transmit_phy_mask` |
| 1 | `receive_phy_mask` |
| 2 | `transmit_max_data_octets` |
| 3 | `transmit_max_time_us` |

### LC3 preferences

| Bit | Field |
| --- | --- |
| 0 | `sampling_frequency_hz` |
| 1 | `frame_duration_us` |
| 2 | `octets_per_frame` |
| 3 | `frame_blocks_per_sdu` |
| 4 | `channel_allocation` |

Sampling frequencies are represented in `supported_lc3_sampling_frequency_mask`
in ascending Bluetooth-assigned-number order: bits 0 through 12 represent 8,
11.025, 16, 22.05, 24, 32, 44.1, 48, 88.2, 96, 176.4, 192, and 384 kHz.
Frame-duration mask bit 0 represents 7.5 ms and bit 1 represents 10 ms.

### ISO QoS preferences

| Bit | Field |
| --- | --- |
| 0 | `sdu_interval_us` |
| 1 | `framing` |
| 2 | `phy_mask` |
| 3 | `retransmission_number` |
| 4 | `maximum_sdu_octets` |
| 5 | `maximum_transport_latency_ms` |
| 6 | `presentation_delay_us` |
| 7 | `minimum_presentation_delay_us` |
| 8 | `maximum_presentation_delay_us` |
| 9 | `preferred_minimum_presentation_delay_us` |
| 10 | `preferred_maximum_presentation_delay_us` |

`framing` is 0 for unframed and 1 for framed. These values are preferences or
advertised constraints, depending on the device's BAP role. The final values
are selected during LE Audio codec and QoS negotiation and are reported through
`runtime_state`. A device must reject internally inconsistent presentation-delay
ranges.

## Responses and runtime state

Response payload tag 0 is a `command_result`. Tags 1 through 4 are configured
ACL connection, ACL radio, LC3, and ISO QoS values, respectively.
`get_configuration` returns the variant matching its requested section.
Mutating commands return a result after validation and storage, even when
applying the setting to a peer remains asynchronous.

Command-result status values are:

| Value | Meaning |
| --- | --- |
| 0 | Accepted and applied where currently possible |
| 1 | Accepted; application is pending |
| 2 | Accepted; a reconnect is required |
| 3 | Accepted; an audio stream restart is required |
| 4 | Unsupported command, section, or value |
| 5 | Invalid value or inconsistent fields |
| 6 | Busy |
| 7 | Failed |

Error domains are 0 for no error, 1 for protocol validation, 2 for a platform
or host-stack error, and 3 for a Bluetooth HCI status. `error_code` is zero when
the domain is zero. Platform errors retain their signed value; HCI statuses are
encoded as positive values.

`restart_required_mask` uses configuration-section bits. It states which
accepted settings cannot affect the current connection or stream.

Capability `feature_flags` use bit 0 for runtime policy switching, bit 1 for
persistent configuration, bit 2 for negotiated-state notifications, and bit 3
for reporting multiple streams independently. Unassigned bits must be zero.

Runtime validity bits are:

| Bit | Valid fields |
| --- | --- |
| 0 | Connection identity and ACL connection parameters |
| 1 | ACL PHY fields |
| 2 | ACL data length fields |
| 3 | LC3 fields |
| 4 | ISO QoS fields |
| 5 | Presentation delay |
| 6 | Audio underrun and adjustment counters |

`connection_id` and `stream_id` are session-local identifiers and must not be
persisted by clients. Direction values are 0 for sink and 1 for source.
Lifecycle values are 0 disconnected, 1 connected, 2 codec configured, 3 QoS
configured, 4 enabled, 5 streaming, and 6 releasing.

The runtime state characteristic retains the latest state. When multiple audio
streams exist, notifications identify each stream independently; a read returns
the implementation-defined primary stream and its identifiers indicate which
one was selected.

## Compatibility

Clients must ignore capability bits they do not understand and must not send
unsupported commands or policy tags. Future protocol releases may add tagged
command, response, or policy variants and new characteristics. Existing tags,
field order, field types, bit assignments, and UUIDs remain stable.

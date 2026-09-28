# Wireless Audio Configuration Protocol

This protocol configures device-owned Bluetooth audio policies and reports
effective runtime state. It deliberately does not replace the Bluetooth LE
Audio control plane:

- Published LC3 capabilities remain authoritative in PACS.
- A Unicast Client selects the codec configuration with ASCS Config Codec.
- The server returns its QoS preferences in the Codec Configured ASE state.
- The Unicast Client selects the actual CIS QoS with ASCS Config QoS.

Consequently, LC3 and actual ISO QoS values are read-only observations in
`runtime_state`. All multi-byte protocol values use little-endian encoding.

## Transport and security

Write a `configuration_command` to `command`. The device indicates exactly one
correlated `configuration_response` on `response` for every accepted write.
Malformed writes are rejected with an ATT error and do not produce a response.
The client must enable response indications before issuing a command; the
device must reject a command when the response CCC is not configured.

`runtime_state` can be read for a snapshot and notifies when effective or
standard-negotiated values change. `capabilities` is read-only and describes
only this custom policy service. Clients discover codec capabilities through
PACS and must not infer them from this service.

Policy writes and response indications must require an encrypted, authenticated
connection to a bonded peer. The generated Zephyr adapter only supplies generic
permissions, so a firmware integration is responsible for choosing the
corresponding encrypted or authenticated GATT permissions.

The `request_id` is chosen by the client and copied unchanged into the response.
Reusing an ID while an earlier command is outstanding is invalid.

The largest version 1 command or response is 35 bytes. Notifications of the
65-byte runtime state require an ATT MTU of at least 68 bytes; clients with a
smaller MTU can use a long read. The 61-byte capabilities value is also
available through normal GATT long-read behavior.

## Ownership and scope

Configuration is global device policy. ACL policies apply only to an ACL
connection associated with an OpenEarable LE Audio stream; they must never
retarget an unrelated control connection. When several qualifying connections
exist, the same policy applies independently to each one.

Requested ACL parameters are preferences, not guarantees. The Bluetooth
controller or peer may reject them or negotiate different effective values.
Only confirmed values belong in `runtime_state`.

Unicast Server QoS preferences affect subsequent ASCS Config Codec operations.
They do not reconfigure an existing CIG or CIS. An implementation may require
ASE release and codec reconfiguration before changed preferences are visible.

## Stable identifiers

Numeric identifiers are permanent once version 1 is released. New values may
be added, but an assigned value must never be reused with another meaning.

### Policy sections

The following IDs identify configuration sections. Their corresponding bits are
used by `section_mask` and `supported_section_mask`:

| ID/bit | Section |
| --- | --- |
| 0 | ACL connection policy |
| 1 | ACL radio policy |
| 2 | Unicast Server QoS preferences |

A zero `section_mask` means all supported sections for `restore_defaults`.
Unknown nonzero bits must be rejected. `get_configuration.section` accepts one
section ID and returns the matching configured-section response variant.

### Commands

Command tags are also represented by the corresponding bit in
`supported_command_mask`:

| Tag | Command |
| --- | --- |
| 0 | Set ACL connection policy |
| 1 | Set ACL radio policy |
| 2 | Set Unicast Server QoS preferences |
| 3 | Get configuration |
| 4 | Restore defaults |

`persist` must be 0 for a session-only setting or 1 to retain it across device
restarts. A session-only setting remains active until replaced, restored, or
the device restarts. `restore_defaults` clears persisted values in every
selected section before applying compiled defaults.

### ACL connection policies

Policy tags are also represented by the corresponding bit in
`supported_acl_policy_mask`:

| Tag | Policy |
| --- | --- |
| 0 | Controller default |
| 1 | Fixed interval |
| 2 | Preferred interval range |
| 3 | Adaptive linear |

`controller_default_acl_policy.reserved` must be zero. A preferred range maps
to the normal GAP connection-parameter model. A fixed interval is encoded as a
separate policy for convenience but still uses the standard Bluetooth update
procedure and remains subject to peer negotiation.

The adaptive-linear policy increases the requested interval once per audio
underrun episode. During stable streaming, it decreases the interval once per
`recovery_period_ms`. It never issues an update more frequently than
`minimum_update_period_ms`; arithmetic must saturate at the configured bounds.

Intervals must be exact multiples of `capabilities.acl_interval_resolution_us`.
For every range, the minimum must not exceed the maximum. Implementations must
also validate the Core-specification relationship between interval, peripheral
latency, and supervision timeout.

### ACL radio policy

Radio policy tag 0 leaves PHY and Data Length Extension behavior to the stack;
`automatic_acl_radio_policy.reserved` must be zero. Tag 1 requests explicit
preferences. PHY masks use bit 0 for LE 1M, bit 1 for LE 2M, and bit 2 for LE
Coded. A zero mask or zero data-length value leaves that setting automatic.
Nonzero data octet and time values must lie within the corresponding ranges in
`capabilities`.

Data Length Extension is an ACL transport setting, not CIS QoS. Requested PHY
and data length values may be negotiated or rejected independently. Effective
values are reported only in `runtime_state`.

### Unicast Server QoS preferences

Direction masks use bit 0 for sink, meaning audio received by the device, and
bit 1 for source, meaning audio transmitted by the device. At least one
supported direction must be selected.

The remaining fields map directly to the BAP/ASCS server QoS preference tuple:

- `unframed_supported`
- `preferred_phy_mask`
- `preferred_retransmission_number`
- `maximum_transport_latency_ms`
- minimum and maximum presentation delay
- preferred minimum and maximum presentation delay

`unframed_supported` must be 0 or 1. The preferred presentation-delay interval
must be contained by the supported interval. These values are returned by the
server after ASCS Config Codec; the Unicast Client remains responsible for
choosing and configuring actual QoS through ASCS Config QoS.

## Responses and application timing

Response payload tag 0 is `command_result`. Tags 1 through 3 contain the
configured ACL connection policy, ACL radio policy, and Unicast Server QoS
preferences. A mutating command returns after validation and storage even when
Bluetooth application remains asynchronous.

Command-result status values are:

| Value | Meaning |
| --- | --- |
| 0 | Accepted and applied where currently possible |
| 1 | Accepted; application is pending |
| 2 | Accepted; an ACL reconnect is required |
| 3 | Accepted; ASE release and codec reconfiguration are required |
| 4 | Unsupported command, section, or value |
| 5 | Invalid value or inconsistent fields |
| 6 | Busy |
| 7 | Failed |

Error domains are 0 for no error, 1 for protocol validation, 2 for a platform
or host-stack error, and 3 for a Bluetooth HCI status. `error_code` is zero when
the domain is zero. `restart_required_mask` uses policy-section bits.

Capability `feature_flags` use bit 0 for runtime policy switching, bit 1 for
persistent configuration, bit 2 for runtime-state notifications, and bit 3 for
reporting multiple streams independently. Unassigned bits must be zero.

## Runtime state

Runtime validity bits are:

| Bit | Valid fields |
| --- | --- |
| 0 | Connection identity and ACL connection parameters |
| 1 | ACL PHY fields |
| 2 | ACL data length fields |
| 3 | Standard-negotiated LC3 fields |
| 4 | Standard-negotiated ISO QoS fields |
| 5 | Standard-negotiated presentation delay |
| 6 | Audio underrun and ACL-adjustment counters |

`connection_id` and `stream_id` are session-local identifiers and must not be
persisted by clients. Direction values are 0 for sink and 1 for source.
Lifecycle values are 0 disconnected, 1 connected, 2 codec configured, 3 QoS
configured, 4 enabled, 5 streaming, and 6 releasing.

The characteristic retains the latest state. With multiple streams,
notifications identify each stream independently; a read returns the
implementation-defined primary stream and its identifiers identify that choice.

## Diagrams

The [PlantUML diagram set](diagrams/README.md) covers the standard LE Audio
boundary, policy commands and queries, runtime reporting, adaptive behavior, and
the message model. It specifies intended future firmware behavior; it does not
imply that firmware integration exists.

## Standards references

- [Basic Audio Profile (BAP)](https://www.bluetooth.com/specifications/specs/basic-audio-profile-1-0-3/)
- [Published Audio Capabilities Service (PACS)](https://www.bluetooth.com/specifications/specs/published-audio-capabilities-service-1-0-1/)
- [Audio Stream Control Service (ASCS)](https://www.bluetooth.com/specifications/specs/audio-stream-control-service-1-0-1/)
- [Bluetooth Core Generic Access Profile](https://www.bluetooth.com/wp-content/uploads/Files/Specification/HTML/Core-54/out/en/host/generic-access-profile.html)

## Compatibility

Clients must ignore capability bits they do not understand and must not send
unsupported commands or policy tags. Future releases may add tagged variants
and characteristics. Existing tags, field order, field types, bit assignments,
and UUIDs remain stable after version 1 is released.

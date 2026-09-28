# Protocol Diagrams

These PlantUML diagrams illustrate the version 1 wire contract and the intended
behavior of a future firmware implementation. They do not describe functionality
that is already implemented in the firmware.

- [`configuration-command-sequence.puml`](configuration-command-sequence.puml)
  shows a mutating command, persistence, asynchronous Bluetooth application, and
  effective-state reporting.
- [`configuration-query-sequence.puml`](configuration-query-sequence.puml)
  shows capability discovery, configuration reads, and the difference between a
  malformed write and a valid but rejected command.
- [`runtime-state-sequence.puml`](runtime-state-sequence.puml) shows how ACL,
  codec, QoS, streaming, and underrun events produce runtime-state snapshots.
- [`protocol-model.puml`](protocol-model.puml) shows the main message envelopes,
  tagged unions, configuration sections, and GATT characteristics.
- [`adaptive-linear-policy.puml`](adaptive-linear-policy.puml) shows the state
  machine for the adaptive-linear ACL policy.

Render all diagrams from this directory with a local PlantUML installation:

```sh
plantuml *.puml
```

SVG output can be generated with:

```sh
plantuml -tsvg *.puml
```

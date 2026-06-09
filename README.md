# OpenEarable Protocol Schemas

This repository defines OpenEarable binary protocols as YAML schemas and
generates language bindings from those schemas.

## Generate Code

Run the generator from the repository root:

```sh
.venv/bin/python -m protocol_generator
```

By default, schemas are read from `schemas/*/protocol.yml` and generated code is
written to:

- `generated/dart/lib/open_earable_protocols.dart`
- `generated/dart/lib/src/protocol_runtime.dart`
- `generated/dart/lib/src/*_protocol.dart`
- `generated/c/protocol_runtime.h`
- `generated/c/protocol_runtime.c`
- `generated/c/*_protocol.h`
- `generated/c/*_protocol.c`
- `generated/c/protocol_sources.cmake`
- `generated/c/protocol_sources.mk`

Custom directories can be provided when integrating with a build system:

```sh
.venv/bin/python -m protocol_generator --schema-dir schemas --output-dir generated
```

Generate only one language target:

```sh
.venv/bin/python -m protocol_generator --language dart
```

The generator is implemented as the `protocol_generator` package. See
[`docs/architecture.md`](docs/architecture.md) for module responsibilities and
the process for adding another language.

Each language emits one shared binary codec runtime. Generated protocol files
import or include that runtime instead of embedding duplicate reader, writer,
status, and primitive codec helpers.

## Dart Package

The generated Dart bindings form the publishable `open_earable_protocols`
package under `generated/dart`. Flutter and Dart applications can depend on
that directory and import all generated protocols from:

```dart
import 'package:open_earable_protocols/open_earable_protocols.dart';
```

Before publishing a release, update `generated/dart/pubspec.yaml` and
`generated/dart/CHANGELOG.md`, regenerate the bindings, and run:

```sh
cd generated/dart
dart pub publish --dry-run
```

## Schema Format

Each protocol schema defines metadata and ordered message fields:

```yaml
protocol: audio-response
version: 1
description: Protocol description.

messages:
  message_name:
    fields:
      - name: count
        type: uint8
      - name: values
        type: uint16[count]
```

Supported scalar field types are:

- Integers: `uint8`, `uint16`, `uint32`, `int8`, `int16`, and `int32`.
- Floating point: `float` and `double`.

Multi-byte values are encoded little-endian. `float` uses the 4-byte IEEE-754
binary32 representation and `double` uses the 8-byte IEEE-754 binary64
representation.

Supported dynamic field types:

- `bytes[length_field]` for variable-length byte payloads.
- `uint16[length_field]` and other scalar arrays for variable-length arrays.
- `float[length_field]` and `double[length_field]` for floating-point arrays.
- `message_a | message_b` for tagged unions.

Length fields must be integer fields and must appear before the dynamic field
that references them. Union fields require a preceding integer field named
`type`; discriminator value `0` maps to the first union variant, `1` to the
second, and so on.

## C Decode Ownership

Generated C structs use pointers for variable-length byte and array fields.
The caller owns that memory and must allocate enough space before calling a
decode function. The decoder fills the caller-provided buffers and reports
`PROTOCOL_ERROR_INVALID_DATA` if the input is truncated or has an unknown union
tag.
Compile `protocol_runtime.c` once and link it together with all generated
protocol-specific C sources. All generated C encode/decode functions return the
shared `protocol_status_t` type.

## C Package

The generated C99 bindings under `generated/c` can be consumed by CMake, Make,
or Zephyr. CMake projects can add the directory and link
`OpenEarable::Protocols`. Make projects can either build the provided static
library or include `protocol_sources.mk` to compile the generated sources
directly.

The repository is also a Zephyr module. Add it to a west manifest and Zephyr
will compile the generated protocol sources and expose their headers
automatically. See [`generated/c/README.md`](generated/c/README.md) for usage
examples and [`docs/open-earable-2-integration.md`](docs/open-earable-2-integration.md)
for firmware integration.

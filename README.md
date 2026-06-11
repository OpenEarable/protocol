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
- `generated/c/include/protocol_runtime.h`
- `generated/c/include/*_protocol.h`
- `generated/c/include/zephyr/*_ble.h`
- `generated/c/src/protocol_runtime.c`
- `generated/c/src/*_protocol.c`
- `generated/c/CMakeLists.txt`

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
    description: Human-readable documentation for the generated message type.
    fields:
      - name: count
        type: uint8
      - name: values
        type: uint16[count]
```

Message descriptions are optional but recommended. The generator emits them as
Dart documentation comments and C Doxygen comments. When omitted, it generates
a stable description from the message and protocol names.

Optional BLE transport metadata is retained in generated APIs:

```yaml
transport:
  ble:
    service_uuid: 12345678-1234-5678-1234-56789abcdef0
    characteristics:
      - name: measurements
        uuid: 12345678-1234-5678-1234-56789abcdef1
        properties: [read, notify]
```

Supported characteristic properties are `broadcast`, `read`,
`write_without_response`, `write`, `notify`, `indicate`,
`authenticated_signed_writes`, and `extended_properties`. Hyphenated and
UniversalBLE-style camelCase spellings such as `writeWithoutResponse` are also
accepted.

Dart exposes framework-neutral service and characteristic definitions through
a protocol-specific `*BleUuids` constants class. Its property enum names match
UniversalBLE's `CharacteristicProperty` names, so an application can convert
them without making the generated package depend on UniversalBLE:

```dart
import 'package:open_earable_protocols/open_earable_protocols.dart';
import 'package:universal_ble/universal_ble.dart';

final definition = AudioResponseBleUuids.transferControlCharacteristic;
final properties = definition.mapPropertiesByName(
  CharacteristicProperty.values,
  (property) => property.name,
);
final characteristic = BleCharacteristic(definition.uuid, properties, []);
```

`isReadable` and `isWritable` are available when deriving peripheral
permissions.

C exposes UUID strings and standard GATT property bitmasks as
protocol-prefixed macros. An additional opt-in Zephyr header maps those values
to Zephyr UUID declarations, characteristic properties, and default
permissions:

```c
#include "zephyr/audio_response_ble.h"

BT_GATT_SERVICE_DEFINE(audio_response_service,
  BT_GATT_PRIMARY_SERVICE(AUDIO_RESPONSE_ZEPHYR_SERVICE_UUID),
  BT_GATT_CHARACTERISTIC(
    AUDIO_RESPONSE_ZEPHYR_TRANSFER_CONTROL_CHARACTERISTIC_UUID,
    AUDIO_RESPONSE_ZEPHYR_TRANSFER_CONTROL_CHARACTERISTIC_PROPERTIES,
    AUDIO_RESPONSE_ZEPHYR_TRANSFER_CONTROL_CHARACTERISTIC_PERMISSIONS,
    read_callback, write_callback, NULL),
  BT_GATT_CCC(configuration_changed, BT_GATT_PERM_READ | BT_GATT_PERM_WRITE));
```

Add a `BT_GATT_CCC` entry when a characteristic uses `notify` or `indicate`.
The Zephyr adapter derives ordinary read/write permissions; applications remain
responsible for selecting encrypted or authenticated permission variants when
required.

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

The generated C99 bindings under `generated/c` are a CMake library. CMake
projects can add the directory and link `OpenEarable::Protocols`. The generated
target compiles every protocol source and exposes `generated/c/include` to
consumers.

See [`generated/c/README.md`](generated/c/README.md) for general usage and
[`docs/open-earable-2-integration.md`](docs/open-earable-2-integration.md) for
explicit firmware integration.

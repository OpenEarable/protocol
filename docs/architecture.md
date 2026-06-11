# Generator Architecture

The generator is organized around a language-neutral protocol model and
language-specific emitter strategies.

## Generation Flow

1. `ProtocolSchemaRepository` discovers each `schemas/*/protocol.yml` file.
2. The schema loader parses YAML and validates it into immutable domain objects
   from `model.py`.
3. `ProtocolGenerator` resolves each requested language through
   `EmitterRegistry`.
4. Each `LanguageEmitter` emits its shared runtime files once.
5. For every schema, each emitter converts the domain model into
   protocol-specific `GeneratedFile` values.
6. Each emitter can generate collection files that aggregate all protocols.
7. `ProtocolGenerator` writes those files below the configured output
   directory.

The domain model contains protocol concepts only. Language-specific mappings,
such as Dart `double` or C `float`, stay inside their respective emitter.
Optional BLE service and characteristic metadata is also represented in the
domain model so every emitter can expose transport identifiers appropriately.
Protocol and message descriptions are retained as validated metadata so each
emitter can produce native documentation comments.

## Shared Language Runtimes

The emitter strategy contract separates language-level runtime generation from
protocol-level generation:

```python
class LanguageEmitter(ABC):
    def emit_runtime_files(self) -> tuple[GeneratedFile, ...]:
        ...

    def emit_protocol_files(
        self,
        protocol: Protocol,
        schema_path: Path,
    ) -> tuple[GeneratedFile, ...]:
        ...

    def emit_collection_files(
        self,
        protocols: Sequence[Protocol],
    ) -> tuple[GeneratedFile, ...]:
        ...
```

The Dart emitter generates private runtime and protocol implementations below
`generated/dart/lib/src`. It also generates the public
`open_earable_protocols.dart` package library, which exports every protocol
implementation.

The C emitter generates public headers under `generated/c/include` and sources
under `generated/c/src`. The shared runtime contains `protocol_status_t`,
reader/writer state, and primitive codecs. Every protocol header includes the
runtime header. Its collection output generates `generated/c/CMakeLists.txt`,
which compiles the runtime once together with every protocol source and exposes
the public include directory through `OpenEarable::Protocols`.

## Scalar Encoding

All generated codecs use little-endian byte order. Integer fields use their
declared fixed width. `float` and `double` use IEEE-754 binary32 and binary64
respectively. Integer fields may control dynamic lengths and union
discriminators; floating-point fields may not.

## Generated Documentation

The schema loader preserves each optional message `description` in the
language-neutral `Message` model. Emitters format that text using native
documentation syntax: Dart emits `///` comments and C emits Doxygen `/** */`
comments for message structs and public codec functions. Shared formatting
helpers normalize whitespace, wrap long descriptions, and protect C comment
boundaries. Emitters generate a stable fallback when a message has no
description.

## BLE Metadata

The schema loader converts an optional `transport.ble` section into
`BleTransport` and `BleCharacteristic` domain values. Characteristic properties
are validated into the language-neutral `BleCharacteristicProperty` enum.
UUIDs are validated and normalized as Bluetooth 16-, 32-, or 128-bit UUIDs
before they reach an emitter.

The Dart emitter exposes UUID strings plus framework-neutral
`ProtocolBleServiceDefinition` and `ProtocolBleCharacteristicDefinition`
values. Generated property enum names intentionally match UniversalBLE's
`CharacteristicProperty` names. `mapPropertiesByName` converts the generated
properties to UniversalBLE or another compatible enum without adding a
UniversalBLE dependency to the generated package. `isReadable` and `isWritable`
support deriving peripheral permissions.

The C emitter exposes UUID strings and standard GATT property bitmasks in the
general protocol header. BLE protocols also receive an opt-in
`include/zephyr/*_ble.h` adapter. This header maps normalized UUIDs to
`BT_UUID_DECLARE_*`, properties to `BT_GATT_CHRC_*`, and default read/write
permissions to `BT_GATT_PERM_*`. Keeping the Zephyr include separate prevents
the general C API from depending on Zephyr.

## Package Responsibilities

- `model.py`: immutable language-neutral protocol domain objects.
- `schema/yaml_subset.py`: dependency-free YAML syntax parsing.
- `schema/loader.py`: type-expression parsing and domain validation.
- `schema/parser.py`: stable public facade for schema parsing APIs.
- `repository.py`: schema discovery and loading.
- `generator.py`: application orchestration.
- `registry.py`: emitter strategy registration and lookup.
- `output.py`: generated-file value object and filesystem write boundary.
- `emitters/base.py`: strategy interface for language emitters.
- `emitters/dart.py`: Dart-specific rendering.
- `emitters/c.py`: C/C++-compatible rendering.
- `defaults.py`: composition root for built-in emitter registration.
- `cli.py`: command-line argument handling.

## Adding A Language

1. Implement `LanguageEmitter` in a new module under `emitters/`.
2. Return shared support files from `emit_runtime_files`.
3. Return protocol-specific files from `emit_protocol_files`.
4. Optionally return aggregate files from `emit_collection_files`.
5. Register the emitter in `default_emitter_registry`.
6. Add emitter-focused tests.

Emitters do not discover schemas or write files directly. The
`ProtocolGenerator` coordinates those operations and treats every language
through the same strategy interface.

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

The C emitter generates `protocol_runtime.h` and `protocol_runtime.c`,
containing `protocol_status_t`, reader/writer state, and primitive codecs. Every
protocol header includes the runtime header, and applications compile the
runtime source once. Its collection output generates CMake and Make source
manifests so every build system receives the complete source set without
duplicating the runtime.

## Scalar Encoding

All generated codecs use little-endian byte order. Integer fields use their
declared fixed width. `float` and `double` use IEEE-754 binary32 and binary64
respectively. Integer fields may control dynamic lengths and union
discriminators; floating-point fields may not.

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

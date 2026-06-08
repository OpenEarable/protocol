# Generator Architecture

The generator is organized around a language-neutral protocol model and
language-specific emitter strategies.

## Generation Flow

1. `ProtocolSchemaRepository` discovers each `schemas/*/protocol.yml` file.
2. The schema loader parses YAML and validates it into immutable domain objects
   from `model.py`.
3. `ProtocolGenerator` resolves each requested language through
   `EmitterRegistry`.
4. Each `LanguageEmitter` strategy converts the domain model into one or more
   `GeneratedFile` values.
5. `ProtocolGenerator` writes those files below the configured output
   directory.

The domain model contains protocol concepts only. Language-specific mappings,
such as Dart `double` or C `float`, stay inside their respective emitter.

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
2. Return one or more `GeneratedFile` values from `emit_files`.
3. Register the emitter in `default_emitter_registry`.
4. Add emitter-focused tests.

Emitters do not discover schemas or write files directly. The
`ProtocolGenerator` coordinates those operations and treats every language
through the same strategy interface.

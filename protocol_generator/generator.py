"""Protocol generation orchestration."""

from __future__ import annotations

import pathlib
from typing import Iterable

from protocol_generator.registry import EmitterRegistry
from protocol_generator.repository import ProtocolSchemaRepository


class ProtocolGenerator:
    """Coordinates schema loading, emitter strategies, and file writes."""

    def __init__(
        self,
        schema_repository: ProtocolSchemaRepository,
        emitter_registry: EmitterRegistry,
    ) -> None:
        self.schema_repository = schema_repository
        self.emitter_registry = emitter_registry

    def generate(
        self,
        output_dir: pathlib.Path,
        languages: Iterable[str] | None = None,
    ) -> list[pathlib.Path]:
        """Generate selected language targets for all discovered schemas."""

        selected_languages = tuple(languages) if languages is not None else self.emitter_registry.languages()
        written: list[pathlib.Path] = []
        for schema_path in self.schema_repository.schema_paths():
            protocol = self.schema_repository.load(schema_path)
            for language in selected_languages:
                emitter = self.emitter_registry.create(language)
                for generated_file in emitter.emit_files(protocol, schema_path):
                    written.append(generated_file.write_to(output_dir))
        return written

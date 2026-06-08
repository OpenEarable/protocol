"""Protocol schema repository."""

from __future__ import annotations

import pathlib

from protocol_generator.model import Protocol
from protocol_generator.schema.parser import load_protocol


class ProtocolSchemaRepository:
    """Discovers and loads protocol schemas from a schema directory."""

    def __init__(self, schema_dir: pathlib.Path) -> None:
        self.schema_dir = schema_dir

    def schema_paths(self) -> tuple[pathlib.Path, ...]:
        """Return all schema files below the repository directory."""

        return tuple(sorted(self.schema_dir.glob("*/protocol.yml")))

    def load(self, schema_path: pathlib.Path) -> Protocol:
        """Load one schema file into a validated protocol model."""

        return load_protocol(schema_path)

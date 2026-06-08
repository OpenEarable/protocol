"""Convenience API for protocol generation."""

from __future__ import annotations

import pathlib

from protocol_generator.defaults import default_emitter_registry
from protocol_generator.generator import ProtocolGenerator
from protocol_generator.repository import ProtocolSchemaRepository


def generate(schema_dir: pathlib.Path, output_dir: pathlib.Path) -> list[pathlib.Path]:
    """Generate all protocol schemas below [schema_dir]."""

    generator = ProtocolGenerator(
        ProtocolSchemaRepository(schema_dir),
        default_emitter_registry(),
    )
    return generator.generate(output_dir)

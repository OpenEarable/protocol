"""Language emitter strategy contract."""

from __future__ import annotations

import pathlib
from abc import ABC, abstractmethod

from protocol_generator.model import Protocol
from protocol_generator.output import GeneratedFile


class LanguageEmitter(ABC):
    """Strategy interface implemented by all language-specific emitters."""

    @abstractmethod
    def emit_files(self, protocol: Protocol, schema_path: pathlib.Path) -> tuple[GeneratedFile, ...]:
        """Return all files required for [protocol] in this language."""

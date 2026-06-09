"""Language emitter strategy contract."""

from __future__ import annotations

import pathlib
from abc import ABC, abstractmethod
from collections.abc import Sequence

from protocol_generator.model import Protocol
from protocol_generator.output import GeneratedFile


class LanguageEmitter(ABC):
    """Strategy interface implemented by all language-specific emitters."""

    @abstractmethod
    def emit_runtime_files(self) -> tuple[GeneratedFile, ...]:
        """Return language runtime files shared by all generated protocols."""

    @abstractmethod
    def emit_protocol_files(
        self,
        protocol: Protocol,
        schema_path: pathlib.Path,
    ) -> tuple[GeneratedFile, ...]:
        """Return files specific to [protocol] in this language."""

    def emit_collection_files(
        self,
        protocols: Sequence[Protocol],
    ) -> tuple[GeneratedFile, ...]:
        """Return files that aggregate all generated protocols."""

        return ()

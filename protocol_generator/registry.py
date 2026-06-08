"""Language emitter strategy registry."""

from __future__ import annotations

from collections.abc import Callable

from protocol_generator.emitters.base import LanguageEmitter
from protocol_generator.errors import SchemaError


class EmitterRegistry:
    """Registry for language emitter strategies.

    Adding a language should only require implementing [LanguageEmitter] and
    registering it here, not changing the orchestration code.
    """

    def __init__(self) -> None:
        self._factories: dict[str, Callable[[], LanguageEmitter]] = {}

    def register(self, language: str, factory: Callable[[], LanguageEmitter]) -> None:
        """Register an emitter factory for [language]."""

        normalized = language.lower()
        if normalized in self._factories:
            raise ValueError(f"emitter already registered for language '{language}'")
        self._factories[normalized] = factory

    def create(self, language: str) -> LanguageEmitter:
        """Create the emitter strategy registered for [language]."""

        normalized = language.lower()
        try:
            return self._factories[normalized]()
        except KeyError as exc:
            supported = ", ".join(self.languages())
            raise SchemaError(f"unsupported language '{language}'. Supported languages: {supported}") from exc

    def languages(self) -> tuple[str, ...]:
        """Return registered language names in stable order."""

        return tuple(sorted(self._factories))

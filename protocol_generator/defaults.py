"""Built-in emitter registration."""

from __future__ import annotations

from protocol_generator.emitters.c import CEmitter
from protocol_generator.emitters.dart import DartEmitter
from protocol_generator.registry import EmitterRegistry


def default_emitter_registry() -> EmitterRegistry:
    """Create the standard registry with all built-in language emitters."""

    registry = EmitterRegistry()
    registry.register("dart", DartEmitter)
    registry.register("c", CEmitter)
    return registry

"""Extensible protocol code generation package."""

from protocol_generator.api import generate
from protocol_generator.emitters.base import LanguageEmitter
from protocol_generator.generator import ProtocolGenerator
from protocol_generator.model import Protocol
from protocol_generator.output import GeneratedFile
from protocol_generator.registry import EmitterRegistry
from protocol_generator.repository import ProtocolSchemaRepository
from protocol_generator.schema.parser import load_protocol

__all__ = [
    "EmitterRegistry",
    "GeneratedFile",
    "LanguageEmitter",
    "Protocol",
    "ProtocolGenerator",
    "ProtocolSchemaRepository",
    "generate",
    "load_protocol",
]

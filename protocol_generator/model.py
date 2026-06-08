"""Language-neutral protocol domain model."""

from __future__ import annotations

from dataclasses import dataclass


INTEGER_SCALAR_TYPE_NAMES = frozenset(
    {
        "uint8",
        "uint16",
        "uint32",
        "int8",
        "int16",
        "int32",
    }
)
FLOATING_POINT_SCALAR_TYPE_NAMES = frozenset({"float", "double"})
SCALAR_TYPE_NAMES = INTEGER_SCALAR_TYPE_NAMES | FLOATING_POINT_SCALAR_TYPE_NAMES


@dataclass(frozen=True)
class ScalarType:
    """A fixed-width numeric field."""

    name: str


@dataclass(frozen=True)
class BytesType:
    """A byte field whose length is controlled by another field."""

    length_field: str


@dataclass(frozen=True)
class ArrayType:
    """A fixed-width integer array whose length is controlled by another field."""

    item_type: ScalarType
    length_field: str


@dataclass(frozen=True)
class MessageRefType:
    """A nested message field."""

    name: str


@dataclass(frozen=True)
class UnionType:
    """A tagged union of message variants."""

    variants: tuple[MessageRefType, ...]


FieldType = ScalarType | BytesType | ArrayType | MessageRefType | UnionType


@dataclass(frozen=True)
class Field:
    """A named protocol field."""

    name: str
    type: FieldType


@dataclass(frozen=True)
class Message:
    """A protocol message with ordered fields."""

    name: str
    fields: tuple[Field, ...]


@dataclass(frozen=True)
class Protocol:
    """Validated protocol schema used by language emitters."""

    name: str
    version: int
    description: str
    messages: tuple[Message, ...]

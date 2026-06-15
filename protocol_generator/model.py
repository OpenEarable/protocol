"""Language-neutral protocol domain model."""

from __future__ import annotations

from dataclasses import dataclass
from enum import StrEnum


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


class BleCharacteristicProperty(StrEnum):
    """Standard Bluetooth GATT characteristic property."""

    BROADCAST = "broadcast"
    READ = "read"
    WRITE_WITHOUT_RESPONSE = "write_without_response"
    WRITE = "write"
    NOTIFY = "notify"
    INDICATE = "indicate"
    AUTHENTICATED_SIGNED_WRITES = "authenticated_signed_writes"
    EXTENDED_PROPERTIES = "extended_properties"


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
    """A fixed-width scalar array whose length is controlled by another field."""

    item_type: ScalarType
    length_field: str


@dataclass(frozen=True)
class MessageRefType:
    """A nested message field."""

    name: str


@dataclass(frozen=True)
class UnionVariant:
    """A message variant and its explicit wire discriminator."""

    tag: int
    message: MessageRefType


@dataclass(frozen=True)
class UnionType:
    """A tagged union with an explicit integer discriminator type."""

    tag_type: ScalarType
    variants: tuple[UnionVariant, ...]


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
    description: str
    fields: tuple[Field, ...]


@dataclass(frozen=True)
class BleCharacteristic:
    """A BLE characteristic exposed by a protocol service."""

    name: str
    uuid: str
    properties: tuple[BleCharacteristicProperty, ...]


@dataclass(frozen=True)
class BleTransport:
    """BLE service metadata associated with a protocol."""

    service_uuid: str
    characteristics: tuple[BleCharacteristic, ...]


@dataclass(frozen=True)
class Protocol:
    """Validated protocol schema used by language emitters."""

    name: str
    version: int
    description: str
    messages: tuple[Message, ...]
    ble: BleTransport | None = None

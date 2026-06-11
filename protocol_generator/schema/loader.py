"""Protocol schema loading and domain validation."""

from __future__ import annotations

import pathlib
import re
import uuid
from typing import Any

from protocol_generator.errors import SchemaError
from protocol_generator.model import (
    INTEGER_SCALAR_TYPE_NAMES,
    SCALAR_TYPE_NAMES,
    ArrayType,
    BleCharacteristic,
    BleCharacteristicProperty,
    BleTransport,
    BytesType,
    Field,
    FieldType,
    Message,
    MessageRefType,
    Protocol,
    ScalarType,
    UnionType,
)
from protocol_generator.schema.yaml_subset import parse_yaml_subset


def load_protocol(path: pathlib.Path) -> Protocol:
    """Load and validate a protocol schema."""

    raw = parse_yaml_subset(path.read_text(encoding="utf-8"))
    try:
        name = _required_str(raw, "protocol")
        version = _required_int(raw, "version")
        description = _optional_str(raw, "description")
        raw_messages = raw["messages"]
    except KeyError as exc:
        raise SchemaError(f"{path}: missing required key {exc}") from exc

    if not isinstance(raw_messages, dict) or not raw_messages:
        raise SchemaError(f"{path}: messages must be a non-empty map")

    message_names = set(raw_messages.keys())
    messages: list[Message] = []
    for message_name, raw_message in raw_messages.items():
        if not isinstance(raw_message, dict):
            raise SchemaError(f"{path}: message {message_name} must be a map")
        raw_fields = raw_message.get("fields")
        if not isinstance(raw_fields, list):
            raise SchemaError(f"{path}: message {message_name} must define fields")

        fields: list[Field] = []
        known_integer_fields: set[str] = set()
        for raw_field in raw_fields:
            if not isinstance(raw_field, dict):
                raise SchemaError(f"{path}: fields in {message_name} must be maps")
            field_name = _required_str(raw_field, "name")
            field_type = parse_type(_required_str(raw_field, "type"), message_names)
            _validate_field_type(path, message_name, field_name, field_type, known_integer_fields)
            fields.append(Field(field_name, field_type))
            if isinstance(field_type, ScalarType) and field_type.name in INTEGER_SCALAR_TYPE_NAMES:
                known_integer_fields.add(field_name)
        messages.append(
            Message(
                name=message_name,
                description=_optional_str(raw_message, "description"),
                fields=tuple(fields),
            )
        )

    return Protocol(
        name=name,
        version=version,
        description=description,
        messages=tuple(messages),
        ble=_load_ble_transport(path, raw.get("transport")),
    )


def _load_ble_transport(path: pathlib.Path, raw_transport: Any) -> BleTransport | None:
    """Load optional BLE service metadata from a schema transport section."""

    if raw_transport is None:
        return None
    if not isinstance(raw_transport, dict):
        raise SchemaError(f"{path}: transport must be a map")

    raw_ble = raw_transport.get("ble")
    if raw_ble is None:
        return None
    if not isinstance(raw_ble, dict):
        raise SchemaError(f"{path}: transport.ble must be a map")

    service_uuid = _required_ble_uuid(path, raw_ble, "service_uuid")
    raw_characteristics = raw_ble.get("characteristics")
    if not isinstance(raw_characteristics, list):
        raise SchemaError(f"{path}: transport.ble.characteristics must be a list")

    characteristics: list[BleCharacteristic] = []
    characteristic_names: set[str] = set()
    for raw_characteristic in raw_characteristics:
        if not isinstance(raw_characteristic, dict):
            raise SchemaError(f"{path}: BLE characteristics must be maps")
        name = _required_str(raw_characteristic, "name")
        if name in characteristic_names:
            raise SchemaError(f"{path}: duplicate BLE characteristic name '{name}'")
        characteristic_names.add(name)

        raw_properties = raw_characteristic.get("properties", [])
        if not isinstance(raw_properties, list) or not all(isinstance(value, str) for value in raw_properties):
            raise SchemaError(f"{path}: BLE characteristic '{name}' properties must be a string list")
        properties: list[BleCharacteristicProperty] = []
        for property_name in raw_properties:
            normalized = re.sub(r"(?<!^)(?=[A-Z])", "_", property_name).replace("-", "_").lower()
            try:
                property_value = BleCharacteristicProperty(normalized)
            except ValueError as exc:
                supported = ", ".join(value.value for value in BleCharacteristicProperty)
                raise SchemaError(
                    f"{path}: unsupported BLE characteristic property '{property_name}'. "
                    f"Supported properties: {supported}"
                ) from exc
            if property_value in properties:
                raise SchemaError(
                    f"{path}: duplicate BLE property '{property_name}' on characteristic '{name}'"
                )
            properties.append(property_value)
        characteristics.append(
            BleCharacteristic(
                name=name,
                uuid=_required_ble_uuid(path, raw_characteristic, "uuid"),
                properties=tuple(properties),
            )
        )

    return BleTransport(service_uuid=service_uuid, characteristics=tuple(characteristics))


def _required_ble_uuid(path: pathlib.Path, mapping: dict[str, Any], key: str) -> str:
    """Read and normalize a Bluetooth 16-, 32-, or 128-bit UUID."""

    value = _required_str(mapping, key).lower()
    if re.fullmatch(r"[0-9a-f]{4}", value) or re.fullmatch(r"[0-9a-f]{8}", value):
        return value
    try:
        return str(uuid.UUID(value))
    except ValueError as exc:
        raise SchemaError(f"{path}: {key} must be a valid Bluetooth UUID") from exc


def _required_str(mapping: dict[str, Any], key: str) -> str:
    value = mapping[key]
    if not isinstance(value, str) or not value:
        raise SchemaError(f"{key} must be a non-empty string")
    return value


def _optional_str(mapping: dict[str, Any], key: str) -> str:
    """Read an optional string value, returning an empty string when omitted."""

    value = mapping.get(key, "")
    if not isinstance(value, str):
        raise SchemaError(f"{key} must be a string")
    return value


def _required_int(mapping: dict[str, Any], key: str) -> int:
    value = mapping[key]
    if not isinstance(value, int):
        raise SchemaError(f"{key} must be an integer")
    return value


def parse_type(raw_type: str, message_names: set[str]) -> FieldType:
    """Parse a schema field type expression."""

    union_parts = [part.strip() for part in raw_type.split("|")]
    if len(union_parts) > 1:
        variants = []
        for part in union_parts:
            if part not in message_names:
                raise SchemaError(f"union variant '{part}' is not a message")
            variants.append(MessageRefType(part))
        return UnionType(tuple(variants))

    array_match = re.fullmatch(r"([A-Za-z0-9_]+)\[([A-Za-z_][A-Za-z0-9_]*)\]", raw_type)
    if array_match:
        item_type, length_field = array_match.groups()
        if item_type == "bytes":
            return BytesType(length_field)
        if item_type not in SCALAR_TYPE_NAMES:
            raise SchemaError(f"unsupported array item type '{item_type}'")
        return ArrayType(ScalarType(item_type), length_field)

    if raw_type in SCALAR_TYPE_NAMES:
        return ScalarType(raw_type)
    if raw_type in message_names:
        return MessageRefType(raw_type)
    raise SchemaError(f"unsupported field type '{raw_type}'")


def _validate_field_type(
    path: pathlib.Path,
    message_name: str,
    field_name: str,
    field_type: FieldType,
    known_integer_fields: set[str],
) -> None:
    if isinstance(field_type, (BytesType, ArrayType)) and field_type.length_field not in known_integer_fields:
        raise SchemaError(
            f"{path}: {message_name}.{field_name} references length field "
            f"'{field_type.length_field}' before it is defined"
        )
    if isinstance(field_type, UnionType) and "type" not in known_integer_fields:
        raise SchemaError(
            f"{path}: {message_name}.{field_name} is a union and requires a preceding "
            "'type' integer discriminator field"
        )

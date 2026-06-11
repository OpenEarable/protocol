"""Shared naming transformations."""

from __future__ import annotations

import pathlib
import re


def pascal_case(value: str) -> str:
    """Convert snake/kebab case names to PascalCase."""

    return "".join(part.capitalize() for part in re.split(r"[-_]+", value) if part)


def snake_case(value: str) -> str:
    """Convert protocol names to C identifier style."""

    return re.sub(r"[^A-Za-z0-9]+", "_", value).strip("_").lower()


def lower_camel_case(value: str) -> str:
    """Convert snake/kebab case names to lowerCamelCase."""

    pascal = pascal_case(value)
    return pascal[:1].lower() + pascal[1:]


def generated_banner(schema_path: pathlib.Path) -> str:
    """Return the generated file warning banner."""

    return f"// Generated from {schema_path.as_posix()}. Do not edit by hand.\n"

"""Text formatting helpers."""

from __future__ import annotations




def _indent(value: str, spaces: int) -> str:
    prefix = " " * spaces
    return "\n".join(prefix + line if line else line for line in value.splitlines())

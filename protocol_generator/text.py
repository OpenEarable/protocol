"""Text formatting helpers."""

from __future__ import annotations

import textwrap


def dart_doc_comment(description: str, fallback: str) -> str:
    """Render a wrapped Dart documentation comment."""

    return "\n".join(f"/// {line}" for line in _documentation_lines(description, fallback))


def c_doc_comment(description: str, fallback: str) -> str:
    """Render a wrapped Doxygen documentation comment safe for C headers."""

    lines = _documentation_lines(description.replace("*/", "* /"), fallback)
    if len(lines) == 1:
        return f"/** {lines[0]} */"
    return "\n".join(["/**", *(f" * {line}" for line in lines), " */"])


def _documentation_lines(description: str, fallback: str) -> list[str]:
    """Normalize and wrap schema documentation for generated source files."""

    value = " ".join((description or fallback).split())
    return textwrap.wrap(value, width=88, break_long_words=False, break_on_hyphens=False) or [
        fallback
    ]


def _indent(value: str, spaces: int) -> str:
    prefix = " " * spaces
    return "\n".join(prefix + line if line else line for line in value.splitlines())

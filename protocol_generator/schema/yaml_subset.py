"""Conservative dependency-free YAML subset parser."""

from __future__ import annotations

import re
from typing import Any

from protocol_generator.errors import SchemaError


def parse_yaml_subset(source: str) -> dict[str, Any]:
    """Parse the small YAML subset used by protocol schemas.

    This parser is deliberately conservative. It rejects tabs, multiline
    strings, anchors, and other advanced YAML features instead of interpreting
    them incorrectly.
    """

    root: dict[str, Any] = {}
    stack: list[tuple[int, Any]] = [(-1, root)]
    lines = source.splitlines()

    for line_no, raw_line in enumerate(lines, start=1):
        line = _strip_comment(raw_line).rstrip()
        if not line:
            continue
        if "\t" in raw_line:
            raise SchemaError(f"YAML line {line_no}: tabs are not supported")

        indent = len(line) - len(line.lstrip(" "))
        content = line.lstrip(" ")
        while stack and indent <= stack[-1][0]:
            stack.pop()
        if not stack:
            raise SchemaError(f"YAML line {line_no}: invalid indentation")
        parent = stack[-1][1]

        if content.startswith("- "):
            if not isinstance(parent, list):
                raise SchemaError(f"YAML line {line_no}: list item without list parent")
            item_content = content[2:].strip()
            if not item_content:
                item: Any = {}
                parent.append(item)
                stack.append((indent, item))
                continue
            if ":" in item_content and not item_content.startswith(("'", '"')):
                key, value = _split_key_value(item_content, line_no)
                item = {}
                parent.append(item)
                if value == "":
                    child: Any = {}
                    item[key] = child
                    stack.append((indent, item))
                    stack.append((indent + 2, child))
                else:
                    item[key] = _parse_scalar(value)
                    stack.append((indent, item))
                continue
            parent.append(_parse_scalar(item_content))
            continue

        key, value = _split_key_value(content, line_no)
        if not isinstance(parent, dict):
            raise SchemaError(f"YAML line {line_no}: mapping entry without map parent")
        if value == "":
            child = [] if _next_content_is_list(lines, line_no, indent) else {}
            parent[key] = child
            stack.append((indent, child))
        else:
            parent[key] = _parse_scalar(value)

    return root


def _strip_comment(line: str) -> str:
    in_single = False
    in_double = False
    for index, char in enumerate(line):
        if char == "'" and not in_double:
            in_single = not in_single
        elif char == '"' and not in_single:
            in_double = not in_double
        elif char == "#" and not in_single and not in_double:
            return line[:index]
    return line


def _split_key_value(content: str, line_no: int) -> tuple[str, str]:
    if ":" not in content:
        raise SchemaError(f"YAML line {line_no}: expected 'key: value'")
    key, value = content.split(":", 1)
    key = key.strip()
    if not key:
        raise SchemaError(f"YAML line {line_no}: empty key")
    return key, value.strip()


def _next_content_is_list(lines: list[str], line_no: int, indent: int) -> bool:
    for raw_line in lines[line_no:]:
        line = _strip_comment(raw_line).rstrip()
        if not line:
            continue
        next_indent = len(line) - len(line.lstrip(" "))
        if next_indent <= indent:
            return False
        return line.lstrip(" ").startswith("- ")
    return False


def _parse_scalar(value: str) -> Any:
    if value.startswith("[") and value.endswith("]"):
        inner = value[1:-1].strip()
        if not inner:
            return []
        return [_parse_scalar(part.strip()) for part in inner.split(",")]
    if value in {"true", "false"}:
        return value == "true"
    if re.fullmatch(r"-?\d+", value):
        return int(value)
    if (
        (value.startswith('"') and value.endswith('"'))
        or (value.startswith("'") and value.endswith("'"))
    ):
        return value[1:-1]
    return value

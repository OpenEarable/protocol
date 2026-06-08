"""Generated output value objects."""

from __future__ import annotations

import pathlib
from dataclasses import dataclass


@dataclass(frozen=True)
class GeneratedFile:
    """A generated file path and its text contents.

    The path is relative to the configured output directory. This keeps emitters
    focused on language layout while the generator owns filesystem writes.
    """

    relative_path: pathlib.Path
    contents: str

    def write_to(self, output_dir: pathlib.Path) -> pathlib.Path:
        """Write this generated file below [output_dir] and return its path."""

        target_path = output_dir / self.relative_path
        target_path.parent.mkdir(parents=True, exist_ok=True)
        target_path.write_text(self.contents, encoding="utf-8")
        return target_path

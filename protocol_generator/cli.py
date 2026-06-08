"""Protocol generator command-line interface."""

from __future__ import annotations

import argparse
import pathlib
from typing import Iterable

from protocol_generator.defaults import default_emitter_registry
from protocol_generator.generator import ProtocolGenerator
from protocol_generator.repository import ProtocolSchemaRepository


def main(argv: Iterable[str] | None = None) -> int:
    """Run the protocol generator command line interface."""

    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--schema-dir", type=pathlib.Path, default=pathlib.Path("schemas"))
    parser.add_argument("--output-dir", type=pathlib.Path, default=pathlib.Path("generated"))
    parser.add_argument(
        "--language",
        action="append",
        choices=default_emitter_registry().languages(),
        help="Language target to generate. Repeat to generate multiple targets. Defaults to all.",
    )
    args = parser.parse_args(argv)

    generator = ProtocolGenerator(
        ProtocolSchemaRepository(args.schema_dir),
        default_emitter_registry(),
    )
    written = generator.generate(args.output_dir, args.language)
    for path in written:
        print(path)
    return 0

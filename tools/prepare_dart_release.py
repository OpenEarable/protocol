#!/usr/bin/env python3
"""Prepare the generated Dart protocol package for release."""

from __future__ import annotations

import argparse
import pathlib
import re


SEMVER_RE = re.compile(
    r"^(0|[1-9]\d*)\.(0|[1-9]\d*)\.(0|[1-9]\d*)"
    r"(?:-[0-9A-Za-z-]+(?:\.[0-9A-Za-z-]+)*)?"
    r"(?:\+[0-9A-Za-z-]+(?:\.[0-9A-Za-z-]+)*)?$"
)
PUBSPEC_VERSION_RE = re.compile(r"^version:\s*.+$", re.MULTILINE)
CHANGELOG_HEADING_RE = re.compile(r"^##\s+(.+)$", re.MULTILINE)


class ReleasePreparationError(RuntimeError):
    """Raised when release metadata cannot be prepared safely."""


def validate_version(version: str) -> str:
    """Return a normalized SemVer version or raise for invalid input."""

    normalized = version.strip()
    if normalized.startswith("v"):
        raise ReleasePreparationError("Pass the package version without a leading 'v'.")
    if not SEMVER_RE.fullmatch(normalized):
        raise ReleasePreparationError(f"Invalid SemVer version: {version!r}")
    return normalized


def update_pubspec_version(pubspec_path: pathlib.Path, version: str) -> None:
    """Set the package version in a pubspec file."""

    content = pubspec_path.read_text()
    updated, count = PUBSPEC_VERSION_RE.subn(f"version: {version}", content, count=1)
    if count != 1:
        raise ReleasePreparationError(f"Could not find a single version field in {pubspec_path}.")
    pubspec_path.write_text(updated)


def release_unreleased_section(
    changelog_path: pathlib.Path,
    version: str,
) -> str:
    """Release a Keep-a-Changelog style ``[Unreleased]`` section.

    The function keeps a fresh empty ``[Unreleased]`` section at the top and
    returns the notes that were moved into the versioned release.
    """

    content = changelog_path.read_text()
    match = re.search(r"^##\s+\[Unreleased\]\s*$", content, flags=re.MULTILINE)
    if match is None:
        raise ReleasePreparationError(f"{changelog_path} must contain a '## [Unreleased]' section.")

    next_heading = CHANGELOG_HEADING_RE.search(content, match.end())
    section_end = next_heading.start() if next_heading else len(content)
    notes = content[match.end() : section_end].strip()
    if not notes:
        raise ReleasePreparationError(f"{changelog_path} has no unreleased notes to publish.")

    released_heading = f"## [{version}]"
    replacement = f"## [Unreleased]\n\n{released_heading}\n\n{notes}\n\n"
    updated = content[: match.start()] + replacement + content[section_end:].lstrip()
    changelog_path.write_text(updated)
    return notes


def ensure_dart_changelog_section(
    changelog_path: pathlib.Path,
    version: str,
    notes: str,
) -> None:
    """Ensure the Dart package changelog contains the released schema notes."""

    content = changelog_path.read_text() if changelog_path.exists() else ""
    if re.search(rf"^##\s+\[?{re.escape(version)}\]?", content, flags=re.MULTILINE):
        return

    released_section = f"## {version}\n\n{notes}\n\n"
    changelog_path.write_text(released_section + content.lstrip())


def parse_args() -> argparse.Namespace:
    """Parse command-line arguments."""

    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("version", help="Dart package version to release, without a leading v.")
    parser.add_argument(
        "--repo-root",
        type=pathlib.Path,
        default=pathlib.Path.cwd(),
        help="Repository root containing generated and schemas directories.",
    )
    return parser.parse_args()


def main() -> int:
    """Prepare release metadata for the generated Dart package."""

    args = parse_args()
    repo_root = args.repo_root.resolve()
    version = validate_version(args.version)
    schema_notes = release_unreleased_section(
        repo_root / "schemas" / "CHANGELOG.md",
        version,
    )
    update_pubspec_version(repo_root / "generated" / "dart" / "pubspec.yaml", version)
    ensure_dart_changelog_section(
        repo_root / "generated" / "dart" / "CHANGELOG.md",
        version,
        schema_notes,
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())

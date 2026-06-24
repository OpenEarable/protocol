"""Tests for Dart release metadata preparation."""

from __future__ import annotations

import datetime as dt
import pathlib
import tempfile
import unittest

from tools.prepare_dart_release import (
    ReleasePreparationError,
    ensure_dart_changelog_section,
    release_unreleased_section,
    update_pubspec_version,
    validate_version,
)


class PrepareDartReleaseTest(unittest.TestCase):
    """Validate release metadata updates used by the GitHub workflow."""

    def test_releases_schema_changelog_and_preserves_unreleased_heading(self) -> None:
        """Unreleased schema notes should move into the requested version."""

        with tempfile.TemporaryDirectory() as temp_dir:
            changelog_path = pathlib.Path(temp_dir) / "CHANGELOG.md"
            changelog_path.write_text(
                "## [Unreleased]\n\n"
                "- Added transfer status payload.\n\n"
                "## [0.1.0] - 2026-01-01\n\n"
                "- Initial release.\n"
            )

            notes = release_unreleased_section(
                changelog_path,
                "0.2.0",
                dt.date(2026, 6, 24),
            )

            self.assertEqual(notes, "- Added transfer status payload.")
            self.assertEqual(
                changelog_path.read_text(),
                "## [Unreleased]\n\n"
                "## [0.2.0] - 2026-06-24\n\n"
                "- Added transfer status payload.\n\n"
                "## [0.1.0] - 2026-01-01\n\n"
                "- Initial release.\n",
            )

    def test_rejects_empty_unreleased_changelog(self) -> None:
        """A release should not be created without schema release notes."""

        with tempfile.TemporaryDirectory() as temp_dir:
            changelog_path = pathlib.Path(temp_dir) / "CHANGELOG.md"
            changelog_path.write_text("## [Unreleased]\n\n")

            with self.assertRaises(ReleasePreparationError):
                release_unreleased_section(changelog_path, "0.2.0", dt.date(2026, 6, 24))

    def test_updates_pubspec_version(self) -> None:
        """The generated Dart package version should be replaced exactly once."""

        with tempfile.TemporaryDirectory() as temp_dir:
            pubspec_path = pathlib.Path(temp_dir) / "pubspec.yaml"
            pubspec_path.write_text("name: open_earable_protocols\nversion: 0.1.0\n")

            update_pubspec_version(pubspec_path, "0.2.0")

            self.assertEqual(
                pubspec_path.read_text(),
                "name: open_earable_protocols\nversion: 0.2.0\n",
            )

    def test_inserts_dart_changelog_section_once(self) -> None:
        """Schema notes should appear once in the Dart package changelog."""

        with tempfile.TemporaryDirectory() as temp_dir:
            changelog_path = pathlib.Path(temp_dir) / "CHANGELOG.md"
            changelog_path.write_text("## 0.1.0\n\n- Initial release.\n")

            ensure_dart_changelog_section(
                changelog_path,
                "0.2.0",
                dt.date(2026, 6, 24),
                "- Added transfer status payload.",
            )
            ensure_dart_changelog_section(
                changelog_path,
                "0.2.0",
                dt.date(2026, 6, 24),
                "- Added transfer status payload.",
            )

            self.assertEqual(
                changelog_path.read_text(),
                "## 0.2.0 - 2026-06-24\n\n"
                "- Added transfer status payload.\n\n"
                "## 0.1.0\n\n"
                "- Initial release.\n",
            )

    def test_validates_semver_without_tag_prefix(self) -> None:
        """Release inputs should be package versions rather than tag names."""

        self.assertEqual(validate_version("1.2.3-beta.1"), "1.2.3-beta.1")
        with self.assertRaises(ReleasePreparationError):
            validate_version("v1.2.3")


if __name__ == "__main__":
    unittest.main()

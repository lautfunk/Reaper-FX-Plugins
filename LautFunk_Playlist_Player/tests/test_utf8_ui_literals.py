#!/usr/bin/env python3
"""Static regression check for JUCE UI text: keep all UTF-8 strings explicit.

JUCE treats plain const char* as ASCII. Non-ASCII UI literals must be wrapped
in juce::String::fromUTF8() with portable ASCII-only hex escapes.
Run: python LautFunk_Playlist_Player/tests/test_utf8_ui_literals.py
"""
import codecs
import pathlib
import re
import sys

ROOT = pathlib.Path(__file__).resolve().parents[1]
SOURCES = sorted((ROOT / "Source").glob("*.cpp")) + sorted((ROOT / "Source").glob("*.h"))
EXPLICIT = re.compile(r'juce::String::fromUTF8\(((?:"(?:[^"\\]|\\.)*"\s*)+)\)')
LITERAL = re.compile(r'"((?:[^"\\]|\\.)*)"')
REQUIRED = {
    "LAUTSTÄRKE",
    "BIS NÄCHSTER DURCHLAUF",
    "Playlist öffnen",
    "Keine Datei ausgewählt",
    "Bitte zuerst Musik hinzufügen",
    " belegt / nicht verfügbar",
    "Rechtsklick: Menü / Einstellungen",
}
found = set()
total = 0

for source in SOURCES:
    raw = source.read_bytes()
    try:
        raw.decode("ascii")
    except UnicodeDecodeError as err:
        sys.exit(f"FAIL {source.name}: non-ASCII bytes in C++ source: {err}")
    text = raw.decode("ascii")
    for match in EXPLICIT.finditer(text):
        tokens = LITERAL.findall(match.group(1))
        # Decode C++ \xNN byte escapes; adjacent "" literals are concatenated.
        try:
            value = b"".join(codecs.decode(part, "unicode_escape").encode("latin1")
                             for part in tokens).decode("utf-8")
        except (UnicodeError, ValueError) as err:
            sys.exit(f"FAIL {source.name}: invalid escaped UTF-8: {err}")
        found.add(value)
        total += 1

missing = sorted(term for term in REQUIRED if not any(term in value for value in found))
if missing:
    sys.exit("FAIL: required Unicode UI strings were not decoded correctly: " + str(missing))

print(f"PASS: {len(SOURCES)} C++ files ASCII-safe, "
      f"{total} explicitly decoded UTF-8 strings, all expected UI terms valid.")

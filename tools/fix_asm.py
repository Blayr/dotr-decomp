#!/usr/bin/env python3
"""Post-split fixes for PS2 asm. `make split` runs this after every split.

1. Instructions GNU as can't assemble (PS2 VU0 macro ops and friends) become
   .word directives holding the original bytes. splat's comments carry each
   instruction's bytes, so the result is exact. Mnemonics come from
   config/asm_words.txt (one per line; a trailing * matches a prefix).
2. A .L label that another file jumps to (a function jumping into the middle
   of another) gets a global alias without the dot, which the other files use.
   mwccgap assembles each function alone, .L labels never leave their object,
   and mwccgap drops a global its own function also references, so the owner
   keeps using the local name.
Safe to re-run."""
import re
import sys
from pathlib import Path

root = Path(__file__).resolve().parent.parent
names = [ln.strip() for ln in (root / "config/asm_words.txt").read_text().splitlines() if ln.strip()]
exact = {n for n in names if not n.endswith("*")}
prefixes = tuple(n[:-1] for n in names if n.endswith("*"))
line_re = re.compile(r"^(\s*/\* [0-9A-F]+ [0-9A-F]{8} ([0-9A-F]{8}) \*/\s+)([a-z][\w.]*)(.*)$", re.M)


def fix(m):
    op = m.group(3)
    base = op.split(".")[0]
    if base not in exact and op not in exact and not op.startswith(prefixes):
        return m.group(0)
    word = int.from_bytes(bytes.fromhex(m.group(2)), "little")
    return f"{m.group(1)}.word 0x{word:08X} /* {op}{m.group(4)} */"


files = {path: path.read_text() for path in sorted((root / "asm").rglob("*.s"))}
changed = set()
for path, text in files.items():
    new = line_re.sub(fix, text)
    if new != text:
        files[path] = new
        changed.add(path)
print(f"fix_asm: {len(changed)} files use .word for instructions GNU as lacks", file=sys.stderr)

label_def = re.compile(r"^\s*(?:jlabel\s+)?(\.L[0-9A-F]{8})\b:?", re.M)
defined = {}
for path, text in files.items():
    for m in label_def.finditer(text):
        defined.setdefault(m.group(1), path)
crossing = set()
for path, text in files.items():
    for name in set(re.findall(r"\.L[0-9A-F]{8}\b", text)):
        if name in defined and defined[name] != path:
            crossing.add(name)
for name in crossing:
    owner = defined[name]
    if f"jlabel {name[1:]}\n" not in files[owner]:
        files[owner] = re.sub(rf"^(\s*)(?:jlabel\s+)?{re.escape(name)}:?[ \t]*$",
                              lambda m: f"jlabel {name[1:]}\n{m.group(1)}{name}:", files[owner],
                              count=1, flags=re.M)
        changed.add(owner)
for path, text in files.items():
    new = re.sub(r"\.L[0-9A-F]{8}\b",
                 lambda m: m.group(0)[1:] if m.group(0) in crossing and defined[m.group(0)] != path
                 else m.group(0), text)
    if new != text:
        files[path] = new
        changed.add(path)
for path in changed:
    path.write_text(files[path])
print(f"fix_asm: {len(crossing)} labels used across files made global", file=sys.stderr)

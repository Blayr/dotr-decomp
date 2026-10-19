#!/usr/bin/env python3
"""Load a GCC file's double constants from the game's own literal pool, as the original's assembler did.

GCC writes a double constant as the macro `li.d $5,1.00000000000000005551e-1`. Today's assembler builds every
one in registers (lui/ori/dsll); the one Sony used put the costly ones in the object's .rodata, one entry per
use, and loaded them with `ld $5,sym` ($at: lui $at,%hi(sym); ld $5,%lo(sym)($at)). The game's printfloat
(sdk/kernel_sif.c) has three: 0.1 twice and 1e6.
So for each function in GCC's assembly: its asm file (asm/**/<name>.s) lists the original's pool loads in
order (`ld $X, %lo(D_XXXXXXXX)($at)`) and the original executable gives each entry's 8 bytes. A `li.d` whose
value equals the next unused entry becomes `ld $R,D_XXXXXXXX`; every other li.d stays as it is (the cheap
ones the original built in registers too). A function whose asm has no pool loads is left alone.
Usage: litpool_fix.py out.s   (GCC's assembly, from the project root; tools/cc.sh runs it)"""
import json
import re
import struct
import sys
from pathlib import Path

LID_RE = re.compile(r"^(\s*)li\.d\s+(\$\d+),\s*(\S+)\s*$")
POOL_RE = re.compile(r"\bld\s+\$\w+,\s*%lo\((D_[0-9A-F]{8})\)\(\$at\)")
FUNC_RE = re.compile(r"^\s*\.ent\s+(\w+)")


def exe_reader():
    cfg = json.loads(Path("dk.json").read_text())
    data = Path("assets", cfg["exe"]).read_bytes() if Path("assets", cfg["exe"]).exists() else None
    if data is None:
        return None
    off, vram = cfg["offset"], cfg["vram"]
    return lambda addr: data[addr - vram + off: addr - vram + off + 8]


def pool_of(name: str) -> list[str]:
    for f in Path("asm").glob(f"**/{name}.s"):
        if "/mod/" not in f.as_posix():
            return POOL_RE.findall(f.read_text())
    return []


def main(path: Path) -> None:
    lines = path.read_text().splitlines(keepends=True)
    read = None
    pool, changed = [], 0
    for i, line in enumerate(lines):
        m = FUNC_RE.match(line)
        if m:
            pool = pool_of(m.group(1))
            continue
        m = LID_RE.match(line)
        if not m or not pool:
            continue
        read = read or exe_reader()
        if read is None:
            return
        value = struct.pack("<d", float(m.group(3)))
        sym = pool[0]
        if read(int(sym[2:], 16)) == value:
            # through $at as Sony's assembler did (today's builds the address in the destination register)
            ind = m.group(1)
            lines[i] = (f"{ind}.set\tnoat\n{ind}lui\t$1,%hi({sym})\n{ind}ld\t{m.group(2)},%lo({sym})($1)\n"
                        f"{ind}.set\tat\n")
            pool.pop(0)
            changed += 1
    if changed:
        path.write_text("".join(lines))


if __name__ == "__main__":
    main(Path(sys.argv[1]))

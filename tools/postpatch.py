"""postpatch.py ELF LIST : apply the game's post-build binary patches to the linked ELF, in place.

The shipped game was built from C and then had a few instruction words overwritten (compare branches turned
into nops, a branch forced). LIST holds one patch per line, `VRAM BUILT SHIPPED  # note` (hex words):
the word the compiler makes from the C, and the word the game ships. For each line the word at VRAM must
be BUILT (compiled C: written as SHIPPED) or already SHIPPED (that code is still asm, which holds the
shipped bytes); anything else stops the build. An empty or missing LIST changes nothing."""
import struct
import sys
from pathlib import Path


def sections(elf):
    if elf[:4] != b"\x7fELF" or elf[4] != 1 or elf[5] != 1:
        sys.exit("postpatch: not a 32-bit little-endian ELF")
    shoff, = struct.unpack_from("<I", elf, 0x20)
    shentsize, shnum = struct.unpack_from("<HH", elf, 0x2E)
    for i in range(shnum):
        _, typ, flags, addr, off, size = struct.unpack_from("<IIIIII", elf, shoff + i * shentsize)
        if typ == 1 and flags & 2 and size:  # SHT_PROGBITS, SHF_ALLOC
            yield addr, off, size


def main():
    elf_path, list_path = Path(sys.argv[1]), Path(sys.argv[2])
    rows = []
    if list_path.exists():
        for n, line in enumerate(list_path.read_text().splitlines(), 1):
            line = line.split("#", 1)[0].split()
            if not line:
                continue
            if len(line) != 3:
                sys.exit(f"postpatch: {list_path}:{n}: want VRAM BUILT SHIPPED")
            rows.append((n, *(int(x, 16) for x in line)))
    if not rows:
        return
    elf = bytearray(elf_path.read_bytes())
    secs = list(sections(elf))
    applied = 0
    for n, vram, built, shipped in rows:
        off = next((o + vram - a for a, o, s in secs if a <= vram <= a + s - 4), None)
        if off is None:
            sys.exit(f"postpatch: {list_path}:{n}: 0x{vram:08X} is in no loaded section")
        word, = struct.unpack_from("<I", elf, off)
        if word == built:
            struct.pack_into("<I", elf, off, shipped)
            applied += 1
        elif word != shipped:
            sys.exit(f"postpatch: {list_path}:{n}: 0x{vram:08X} holds 0x{word:08X}, "
                     f"neither the built 0x{built:08X} nor the shipped 0x{shipped:08X}")
    if applied:
        elf_path.write_bytes(elf)


if __name__ == "__main__":
    main()

#!/usr/bin/env bash
# Try a module function at its real spot in its module file: everything in src/mod/<module>.c above the
# function's INCLUDE_ASM line, then your work file (its #include lines dropped). Use it when plain `dk try` is
# close but not exact and the function calls a static function defined earlier in the same module file: the
# compiler then knows which argument registers that callee leaves alone, exactly as in the real build.
# Usage (repository root, toolchain loaded): tools/mod_infile.sh func_01E04E60_b582 work/func_01E04E60_b582.c [LINES]
set -euo pipefail
F="$1"
WORK="$2"
M="${F##*_}"
OUT="work/infile/$F.c"
mkdir -p work/infile
{
    awk -v pat="INCLUDE_ASM(\"asm/nonmatchings/mod/$M\", $F);" 'index($0, pat) == 1 { found = 1; exit } { print }
        END { if (!found) { print "#error " FILENAME ": no INCLUDE_ASM line for this function" } }' "src/mod/$M.c"
    grep -v '^#include' "$WORK"
} > "$OUT"
dk try "$F" "$OUT" --no-context --lines "${3:-40}"

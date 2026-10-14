#!/usr/bin/env bash
# Compile one C file the way the original PS2 game was built: an EE GCC
# (Sony's Linux builds, or SN Systems' Windows builds under wibo) followed by
# GNU as for the R5900, or Metrowerks CodeWarrior (mwccps2.exe under wibo),
# which writes the object itself.
# Usage: tools/cc.sh in.c out.o   (or: tools/cc.sh in.c -o out.o)
# Settings come from the environment (dk, make) or else from config.mk:
# DK_GCC (an ee-gcc version, or mwcps2-<version>), DK_CFLAGS, DK_G, DK_WARM.
set -euo pipefail

# A warm build (below) has mwccgap run this script as its compiler, with mwccps2's
# arguments ending in `-o OUT FILE.c`: one mwccps2 run compiles the warm-up file and
# then FILE.c, and only FILE.c's object is kept.
if [ "${1:-}" = "-c" ]; then
    ARGS=("$@")
    N=$#
    DIR="$(mktemp -d)"
    trap 'rm -rf "$DIR"' EXIT
    wibo "${DK_WARM_MWCC:?}" "${ARGS[@]:0:N-2}" "$DIR" "${DK_WARM_FILE:?}" "${ARGS[N-1]}"
    NAME="$(basename "${ARGS[N-1]}")"
    mv "$DIR/${NAME%.*}.o" "${ARGS[N-2]}"
    exit 0
fi

IN="$1"
if [ "${2:-}" = "-o" ]; then OUT="$3"; else OUT="$2"; fi
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
TC="${DK_TOOLCHAIN:?load the toolchain first: . ~/decomp/toolchain/env.sh}"
if [ -z "${DK_GCC:-}" ]; then
    eval "$(sed -n 's/^export \(DK_[A-Z]*\) := \(.*\)$/\1="\2"/p' "$ROOT/config.mk")"
fi
# Files in config/gcc_files.txt (Sony's SDK libraries) were built with an EE GCC, not the
# game's compiler. Each line gives the file, the GCC version, -G and the flags:
# `src/main_022.c 2.9-991111 0 -O2`. DK_GCC_LIST=0 (dk try --gcc) ignores the list.
GCC_LIST="$ROOT/config/gcc_files.txt"
if [ "${DK_GCC_LIST:-1}" = 1 ] && [ -f "$GCC_LIST" ]; then
    IN_ABS="$(cd "$(dirname "$IN")" && pwd)/$(basename "$IN")"
    ROW="$(awk -v f="${IN_ABS#"$ROOT"/}" '{ sub(/#.*/, "") } $1 == f { $1 = ""; print; exit }' "$GCC_LIST")"
    if [ -n "$ROW" ]; then
        read -r DK_GCC DK_G DK_CFLAGS <<< "$ROW"
    fi
fi
EE="$TC/ee-gcc/$DK_GCC"
PRE="$TC/ee-gcc/2.96"  # a Linux build, used only to preprocess
PRE_LIB="$(dirname "$(find "$PRE/lib" -name cpp0 | head -1)")"
G="${DK_G:-0}"
TMP="$(mktemp -d)"
trap 'rm -rf "$TMP"' EXIT

# DK_EXTRA_INCLUDE (from dk try) shadows headers, e.g. a game.h without a guessed
# prototype of the function being tried.
CPP_FLAGS="${DK_EXTRA_INCLUDE:+-I$DK_EXTRA_INCLUDE} -I$ROOT/include -I$ROOT/src"
mkdir -p "$(dirname "$OUT")"
# Dependencies for make come from the system cpp. It is 64-bit, so Metrowerks
# builds also run inside sandboxes that ban 32-bit programs (Codex on Linux).
cpp -M -nostdinc $CPP_FLAGS "$IN" 2>/dev/null | sed "1s|^[^:]*:|$OUT:|" > "$TMP/deps" || true
[ -z "${ROW:-}" ] || echo "$OUT: $GCC_LIST" >> "$TMP/deps"  # taken off the list = compiled again

if [[ "$DK_GCC" == mwcps2-* ]]; then
    # mwccgap swaps each INCLUDE_ASM line for its assembled function. It reads C
    # from stdin whenever stdin isn't a terminal, so stdin must be empty.
    IN_ABS="$(cd "$(dirname "$IN")" && pwd)/$(basename "$IN")"
    OUT_ABS="$(cd "$(dirname "$OUT")" && pwd)/$(basename "$OUT")"
    MW="$TC/mwcps2/${DK_GCC#mwcps2-}/mwccps2.exe"
    [ -f "$MW" ] || MW="${MW%/*}/mwccmips.exe"  # 2.3 (1999) has the older name
    # Warm files: the original game was compiled many files per mwccps2 run. Once the
    # compiler has called a runtime helper with arguments in a0/a1 (double maths or
    # compare, 64-bit divide), every later `(s32)` float cast (jal fptosi) is treated
    # as using a0/a1, in later functions and later files of the same run. A file listed
    # in config/warm_files.txt (path from the project root) is compiled in one run right
    # after a tiny warm-up file that makes such a call. DK_WARM=1 or 0 overrides the
    # list (dk try sets it for a function whose file is listed).
    WARM_LIST="$ROOT/config/warm_files.txt"
    if [ -z "${DK_WARM:-}" ]; then
        DK_WARM=0
        if [ -f "$WARM_LIST" ] && awk -v f="${IN_ABS#"$ROOT"/}" \
                '{ sub(/#.*/, ""); $1 = $1 } $0 == f { hit = 1 } END { exit !hit }' "$WARM_LIST"; then
            DK_WARM=1
        fi
    fi
    COMPILER=(--mwcc-path "$MW" --use-wibo --wibo-path "$(command -v wibo)")
    if [ "$DK_WARM" = 1 ]; then
        printf 'double warm(double a, double b) {\n    return a * b;\n}\n' > "$TMP/dk_warm.c"
        export DK_WARM_FILE="$TMP/dk_warm.c" DK_WARM_MWCC="$MW"
        COMPILER=(--mwcc-path "$ROOT/tools/cc.sh")
        echo "$OUT: $WARM_LIST" >> "$TMP/deps"  # taken off the list = compiled again
    fi
    (cd "$ROOT" && python3 "$TC/src/mwccgap/mwccgap.py" "$IN_ABS" "$OUT_ABS" "${COMPILER[@]}" \
        --as-path "$(command -v mipsel-none-elf-as)" --as-march r5900 --as-mabi eabi --as-flags "-G$G" \
        --macro-inc-path include/mwccgap.inc \
        -nostdinc -stderr ${DK_EXTRA_INCLUDE:+"-I$DK_EXTRA_INCLUDE"} "-I$ROOT/include" "-I$ROOT/src" $DK_CFLAGS \
        < /dev/null)
    python3 "$ROOT/tools/pad_functions.py" "$OUT_ABS"
    # Switch tables: point them at the game's own tables in the data blob (see there).
    (cd "$ROOT" && python3 tools/jtbl_fix.py "$OUT_ABS")
    mv "$TMP/deps" "$OUT.d"
    exit 0
fi
"$PRE/bin/ee-gcc" -B"$PRE_LIB/" -E $CPP_FLAGS "$IN" -o "$TMP/in.i"
if [ -x "$EE/bin/ee-gcc" ]; then
    LIB="$(dirname "$(find "$EE/lib" -name cc1 | head -1)")"
    (cd "$TMP" && "$EE/bin/ee-gcc" -B"$LIB/" -S "-G$G" $DK_CFLAGS in.i -o out.s)
else
    (cd "$TMP" && wibo "$EE/bin/ee-gcc.exe" -S "-G$G" $DK_CFLAGS in.i -o out.s)
fi
# Switch tables: GCC's own go to .rdata, which the link drops; load the game's (see there).
(cd "$ROOT" && python3 tools/jtbl_fix.py --gcc "$TMP/out.s")
# Sony's EE assembler turned GCC's `move` into a 64-bit daddu; binutils 2.45 makes it `or`.
# The C library's assembler (the 2.96 files) never moved that macro into a branch's delay
# slot (`move $2,$4; j $31; nop`, `move $4,$2; jal dptofp; nop`); a plain daddu would be
# moved, so there it is emitted as a noreorder instruction. The SDK libraries' assembler
# (2.9 files) did move it.
if [ "$DK_GCC" = 2.96 ]; then
    sed -i -E 's/^([[:space:]]+)move([[:space:]]+)([^,]+),([^[:space:]#]+)/\1.set\tpush\n\1.set\tnoreorder\n\1daddu\2\3,\4,$0\n\1.set\tpop/' "$TMP/out.s"
else
    sed -i -E 's/^([[:space:]]+)move([[:space:]]+)([^,]+),([^[:space:]#]+)/\1daddu\2\3,\4,$0/' "$TMP/out.s"
fi
# binutils refuses cvt.w.s on the r5900 (the EE's rounds toward zero); Sony's assembler took
# it (libm's floor/ceil/modf), so write its word: 0x46000024 | fs << 11 | fd << 6.
perl -pi -e 's/^(\s+)cvt\.w\.s\s+\$f(\d+),\s*\$f(\d+)/sprintf("%s.word 0x%08X", $1, 0x46000024 | ($3 << 11) | ($2 << 6))/e' "$TMP/out.s"
# GCC loads a double constant into a GPR (soft-float doubles) as `li.d $N,<value>`; binutils
# refuses it for the r5900, Sony's assembler expanded it as `dli` does (libgcc2's __floatdidf).
perl -pi -e 's/^(\s+)li\.d\s+\$(\d+),\s*(\S+)\s*$/sprintf("%sdli\t\$%s,0x%016X\n", $1, $2, unpack("Q<", pack("d<", $3)))/e' "$TMP/out.s"
# GCC's divide-by-zero trap is `break 7`; Sony's assembler put the 7 in the low code field
# (0x000001CD, shown as `break 0, 7`), binutils in the high one (0x0007000D).
sed -i -E 's/^([[:space:]]+)break([[:space:]]+)7[[:space:]]*$/\1break\20,7/' "$TMP/out.s"
# GCC objects were linked 8-byte aligned; the linker script's SUBALIGN(4) is not, so the
# file's last function keeps its padding here. The list's last file ends where Metrowerks
# code starts, on a 16-byte boundary (main_036 -> main_037 at 0x1A6C80).
P2=3
if [ -n "$ROW" ] && [ "${IN_ABS#"$ROOT"/}" = "$(awk '{ sub(/#.*/, "") } NF { f = $1 } END { print f }' "$GCC_LIST")" ]; then
    P2=4
fi
printf '\t.text\n\t.p2align %s\n' "$P2" >> "$TMP/out.s"

# Sony's assembler expanded GCC's address macros (`lbu $3,D_X($2)`, `la`) with 32-bit adds
# (`addu`, `addiu`); binutils' eabi64 uses `daddu`/`daddiu`. o64 assembles the same 64-bit
# code with 32-bit addresses; the header's ABI field is then set back to eabi64 for the link.
mipsel-none-elf-as -EL "-G$G" -march=r5900 -mabi=o64 -no-pad-sections \
    -I "$ROOT" -I "$ROOT/include" -o "$OUT" "$TMP/out.s"
perl -e 'open(F, "+<", $ARGV[0]) or die; binmode F; seek(F, 0x24, 0); read(F, $b, 4);
    seek(F, 0x24, 0); print F pack("V", (unpack("V", $b) & ~0xF000) | 0x4000); close F' "$OUT"
mv "$TMP/deps" "$OUT.d"

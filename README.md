# Yu-Gi-Oh! The Duelists of the Roses: matching decompilation

A matching decompilation of **Yu-Gi-Oh! The Duelists of the Roses** (PlayStation 2, NTSC-U, `SLUS_205.15`):
C source that compiles to the exact bytes of the retail executable and of the game's 762 code modules.

This repository contains no game data. You need your own copy of the game to build anything.

## Status (15 October 2026)

| | Functions in C | Code in C |
|---|---|---|
| Main executable (`SLUS_205.15`) | 3,248 of 3,464 (93.8%) | 76.3% of 1.5 MB |
| Code modules (`DATA/BMODULE.MRG`, `CMODULE.MRG`, `MMODULE.MRG`) | 5,779 of 8,620 (67.0%) | 40.4% of 11.6 MB |

- `make check` rebuilds the whole executable and all 762 module files and compares them byte for byte with the
  originals. A function counts as done only when its C is in that build and the check passes.
- 34 main-program functions are kept as assembly on purpose (vector-unit code, code patched after the original
  build, hand-written assembly). They count as not done. About 110 others, mostly Sony's system-call stubs and a
  few vector-unit helpers, are written as assembly inside the C files and do count.
- Module functions repeat across modules; one C file per distinct function is renamed into every module that has
  a copy.

## Compilers

- Game code and modules: Metrowerks CodeWarrior for PS2 2.3.3 (`mwccps2`, build 000906),
  `-O4,p -sdatathreshold 0 -relax_pointers`; some module functions use `-O1,p`, `-O2,p` or `-O3,p`, set per
  function with `#pragma optimization_level`. Some files only match when the compiler has compiled another file
  first in the same process ("warm"); `config/warm_files.txt` lists them.
- Sony's libraries: ee-gcc 2.9-991111. The C library (newlib 1.9.0): ee-gcc 2.96. All GCC files are preprocessed
  with the 2.96 preprocessor; `tools/cc.sh` reproduces the old assembler's behaviour.

None of the compilers are included.

## Building

1. Put your `SLUS_205.15` (sha1 `077ac97a878d1bc3b7eb1c3e09bc7fef7becdf68`) in `assets/`, and point `disc` in
   `dk.json` at your disc image (the modules are read from it).
2. `make split`, `make split-modules`, then `make check`.

The scripts currently assume our local toolchain layout (`~/decomp/toolchain`, see `config.mk` and `tools/cc.sh`)
and our helper kit for reading the disc image; expect to adapt a few paths.

## Layout

- `src/main_*.c`: the main executable, one file per original object where known.
- `src/mod/<module>.c`: the code modules; functions not yet in C are included as assembly.
- `include/functions.h`: prototypes of every main-program function.
- `config/`: splat configuration, linker names, the module list.
- `tools/`: compile wrapper, jump-table fixer, module split/pack/check, post-build patch step.

## Names

Functions are still named by address (`func_001F5620`). The Japanese release (`SLPM_650.50`) shipped with its
symbol table; its real names (for example `SzDuel_Act`, `SzEffect_GetRef2`) are being matched to these addresses
and will replace them.

## License

Our own work in this repository is released under **CC0 1.0** (see `LICENSE`). Code taken from other projects
keeps its original license and credit: see `THIRD_PARTY_NOTICES.md` (kfiv-decomp, the ICO decompilation,
gt4-decomp, newlib 1.9.0).

Yu-Gi-Oh! and The Duelists of the Roses belong to their respective owners. This project is not affiliated with
or endorsed by them.

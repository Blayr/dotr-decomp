# Sony's libraries and the C library

These files are not the game's code: they are the parts of Sony's PS2 SDK, the C library (newlib 1.9.0) and the
compiler's run-time library (libgcc) that were linked into `SLUS_205.15`. They were built with EE GCC, not with
the game's Metrowerks compiler (`config/gcc_files.txt` gives each file's GCC version and flags).

Unlike the rest of `src/`, they keep the cuts by address the project started with, only renamed: one library's
object files often run across a cut, and GCC's output here depends on details of the file it compiles (the
libgcc file's path has to stay 14 characters long: `sdk/lgcc.c`). Each file's first line says what it holds.

| File | Was | Contents |
|---|---|---|
| `kernel_syscalls_1.c` | `main_019.c` | Metrowerks float helpers, overlay start-up, kernel calls |
| `kernel_syscalls_2.c` | `main_020.c` | kernel calls (threads, semaphores, event flags) |
| `kernel_syscalls_3.c` | `main_021.c` | libkernl: interrupt / DMA handlers, cache, GS, file stubs |
| `kernel_glue.c` | `main_022.c` | libkernl: C-library glue, cache, thread start, TTY |
| `kernel_sif.c` | `main_023.c` | libkernl: kprintf, SIF commands and RPC |
| `sif_fileio.c` | `main_024.c` | file I/O and module loading over the SIF |
| `libgraph.c` | `main_025.c` | module loading (end), libgraph |
| `libdev.c` | `main_026.c` | libgraph (end), libdev |
| `libvu0_1.c`, `libvu0_2.c` | `main_027.c`, `main_028.c` | libdev (end), libvu0, libipu, libmpeg (start) |
| `libmpeg_1.c`, `libmpeg_2.c` | `main_029.c`, `main_030.c` | libmpeg |
| `libcdvd_1.c`, `libcdvd_2.c` | `main_031.c`, `main_032.c` | libmpeg (end), libcdvd, libpad |
| `libmc.c` | `main_033.c` | libmc (memory card) |
| `newlib_1.c` .. `newlib_8.c`, `newlib_findenv_r.c` | `main_033b.c` .. `main_035e.c` | the C library (newlib) |
| `lgcc.c` | `main_036.c` | libgcc: integer and float helpers |

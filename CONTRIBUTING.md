# Proposing names and fixes

Thank you for helping make this code readable. The rule that matters most:

**The build must not change.** After any change, `make check` must print both

```
OK: build/SLUS_205.15 matches the original
OK: 762 modules match the disc
```

A change that makes either line fail is not accepted, however good the name.

## What makes a good change

- **Names say what a thing is**, in clear English, worked out from how the code uses it (see
  `docs/NAMING.md`). When you are not sure, leave the placeholder (`arg0`, `D_00317490`): a wrong name is
  worse.
- **Keep the original names.** A global or function with a Japanese name keeps it as a note
  (`/* original: gSzDuel_dl */`) and as a linker alias (`config/old_data_names.txt`, `config/old_names.txt`).
- **Renames go through the project's files**, not only the C: functions and globals through
  `config/symbol_addrs.txt` plus the alias file, then `make split`.
- **Comments:** one line above a function saying what it does; short notes on constructs that exist only to
  match (do not remove those constructs or their notes).
- **Small, one-subject changes** are easiest to check: one file, one system.

## How to send one

1. Make the change on a branch.
2. Run `make split` (if you changed `config/symbol_addrs.txt`) and `make check`; both lines must say OK.
3. Send the branch or patch with a few words on what you named and why (what in the code shows it).

## Things to watch

- **Some files are sensitive** to the compiler's carried state: `src/duel/szduel_act.c`, `duel/szduel_cards.c`,
  `battle/szbattle.c`, `campaign/tkcamp.c`, `game/szview_look.c`, `campaign/taku_camp_cinema.c`,
  `campaign/taku_camp_act.c`. Even a rename there can change the bytes of a later function; check after every
  small step, and never move a function to another file without a `make check`.
- **Struct fields:** describing raw offsets as struct fields usually keeps the bytes, but not always (an array
  index can fold an offset differently). Where the readable form changes the build, keep the matching form
  and add a note.
- **Shared headers** recompile everything: run the full `make check`.
- The code modules (`src/mod`) are a separate build; leave them out of naming changes unless agreed first.

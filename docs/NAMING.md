# Naming conventions

How names are chosen in this decompilation, so that new names read like the old ones. The one rule above all
others: **a rename never changes the build.** After any change, `make check` must still print both
`OK: build/SLUS_205.15 matches the original` and `OK: 762 modules match the disc`.

## Where names come from (best first)

1. **The Japanese release's own names.** `SLPM_650.50` shipped with its symbol table: about 3,400 function
   names and 1,020 named data objects. Its debug section (DWARF 1) adds the real parameter, local and struct
   member names for the AI files (`C:\dm2\Prog\etc\*.c`, JP 0x244460-0x284A28: the `Ta*` functions).
   These are the original source names. Use them unchanged, even when they are Japanese romaji (`Taku_`,
   `tex_bara_data`) or terse (`gSzDuel_dl`).
2. **The other team's names** (dotr-decomp, CC0), credited in the commit or comment that uses them.
3. **The game's own strings** (menu text, file names, debug messages).
4. **A clear English name in the house style below**, when the code makes the meaning plain. If the meaning is
   not plain yet, keep the placeholder: a wrong name is worse than `D_00317490`.

## Functions

- Real (JP) names stay exactly as they are: `SzDuel_Act`, `lSzBattle_DrawFakeShadow`, `Ta_Manage_ActEfc`.
  The JP prefix is the module: `Sz*` duel/game layer, `Ta*` AI and card logic, `Taku_*` the campaign map,
  `Rh*` the renderer, `G*` geometry helpers. A leading `l` marks a file-local function.
- A function the JP table does not name keeps `func_XXXXXXXX` until the code says what it does; then it gets a
  name in the style of its neighbours (`SzDuel_` + verb + object for a duel function, and so on).
- Renames go through `config/symbol_addrs.txt`, with the old name kept as an alias in `config/old_names.txt`
  (the code modules call the old names).

## Globals

- Real (JP) names first; they follow the JP style: `g` + module + `_` + a Hungarian-prefixed noun
  (`gSzDuel_dl` the duel state, `gSzModel_ahModel` an array of model handles, `gSzData_bRoseFlag` a byte).
  Common prefixes in the JP names: `a` array, `p` pointer, `pch` string, `b` byte or bool, `w` 16-bit,
  `n` int, `dw` 32-bit word, `f` flag, `h` handle, `pfn` function pointer, `vec`/`pnt` vector/point,
  `icol` colour.
- New names for unnamed globals copy that style: `gSzDuel_` + prefix + noun for a duel global.
- A JP function-local static (`nCurLight$42` in the symbol table) takes its plain name (`nCurLight`).
- Data renames go through `config/symbol_addrs.txt` (`name = 0xADDR;`, no type), with the old name kept as an
  alias in `config/old_data_names.txt`; then `make split` and `make check`.
- An address inside a named object (`D_003181CA`, 0xD3A bytes into `gSzDuel_dl`) keeps its `D_` name for now:
  turning it into a field access can change the generated code, so that is done function by function, with
  `make check`.

## Types and struct fields

- A type shared by several files lives in `include/structs.h` (or the header of its system) under a real name:
  the JP debug name where there is one (`TreeTag`), else an English noun (`DuelState`). A type used by one
  function stays beside it.
- Field names: the JP debug member names where they exist (`dwID`, `eNO`, `bType`); else short English
  camelCase (`cardId`, `lifePoints`), with the byte offset in a comment (`/* 0x6D8 */`).
- Placeholder padding is `u8 padXXX[...]`, named by its offset.
- Changing a shared header can shift the compiler's carried state in the state-sensitive files (see below):
  prefer a forward `typedef struct X_s X;` in `structs.h` with the body where it is used, or prove the header
  change with `make check`.

## Parameters and locals

- JP debug names where they exist (Ta* files): `eInfo`, `nSide`, `Effect`.
- Elsewhere English camelCase: `card`, `player`, `i`/`j` for loop counters. `argN`, `temp_*`, `var_*` are the
  decompiler's placeholders and are replaced only together with a `make check`.
- A rename should never change the code, but check it anyway: if one breaks the match, keep the old name and
  note why.

## Comments

- One line above a function saying what it does, in plain words: `/* Draws the life-point bar of one player. */`
- `/* 0x6D8 */`-style offsets beside struct fields; nothing else inside function bodies unless a line is truly
  surprising (and then why, not what).
- Notes on how a function was matched (compiler tricks, ordering) stay in the existing `/* ... */` blocks;
  do not delete them.

## The state-sensitive files

MWCC carries memory from one function to the next inside a file. In four files a function only matches behind
its real predecessors: `src/main_042.c` (SzDuel_Act), `src/main_043.c` (SzDuel_SetupCard_Pipe),
`src/main_047.c` (lSzBattle_DrawFakeShadow / FakeMirror) and `src/main_063.c` (Taku_Camp_Ivent_Name /
Ivent_Window). Edit them in small steps and run `make check` after each one.

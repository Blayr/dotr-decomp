# Naming conventions

How names are chosen in this decompilation, so that new names read like the old ones and the code reads like
a program, not a dump. The one rule above all others: **a rename never changes the build.** After any change,
`make check` must still print both `OK: build/SLUS_205.15 matches the original` and
`OK: 762 modules match the disc`. Where the readable form changes the bytes, the matching form stays, with a
comment saying so.

## Names say what the thing is

A name describes what the thing **is**, in clear English, worked out from how the code uses it: what reads and
writes it, its size, the game's own strings and behaviour. `duelState`, `lifePoints`, `deck.cards`, not
`gSzDuel_dl` or `D_00317490`. If the meaning is not plain yet, keep the placeholder: a wrong name is worse
than `D_00317490`.

The **original developers' names** are never lost:

- The Japanese release (`SLPM_650.50`) shipped with its symbol table (about 3,400 function names, 1,020 named
  data objects) and, for the AI files (`C:\dm2\Prog\etc\*.c`, JP 0x244460-0x284A28: the `Ta*` functions),
  debug information with the real parameter, local and struct member names.
- A global renamed to English keeps its JP name as a note on its declaration and as a linker alias:

  ```c
  extern DuelStateBytes duelState; /* original: gSzDuel_dl */
  ```

  (`config/old_data_names.txt`: `gSzDuel_dl = duelState;`), so JP-based tools and notes still line up.
- The JP names are the best evidence of what a thing is (`gSzData_bRoseFlag`: a byte flag of the rose
  data), so read them before naming.

Other sources: the other team's names (dotr-decomp, CC0), credited where used; the game's own strings.

## Functions

- The JP function names stay as they are: they already say what the function does (`SzDuel_GetLP`,
  `SzDuel_AddGrave`, `Ta_Manage_ActEfc`). Their prefix is the module: `Sz*` the duel/game layer, `Ta*` the
  AI and card logic, `Taku_*` the campaign map, `Rh*` the renderer, `G*` geometry helpers. A leading `l`
  marks a file-local function.
- A JP name written in romanized Japanese (`Taku_Camp_Kumo`, "clouds") is translated into English with the
  module prefix kept (`Taku_Camp_Clouds`); the JP name stays a linker alias in `config/old_names.txt` and a
  note in the comment above the function (`(original: Taku_Camp_Kumo)`), so JP tools still line up.
- **batzpup's names** (his Ghidra project): the developers' prefix stays, as it is the system tag anyone can
  check against the JP table; inside it his words and duelist names win when the code agrees
  (`TaLogic_Weevil_GetMinimumTask`, `Ta_IsInLeaderRange` for `Ta_IsLDRange`). Where he only changed a spelling
  (`Exodia` for the developers' `Exzodia`), replaced the prefix (`Home_` for `Taku_`) or read the code
  differently, his name is a linker alias in `config/ghidra_names.txt`.
- **Inline helpers.** The compiler wrote small functions inline into their callers, so the same body shows up in
  many places. Each body is written once: the shared ones are in `include/inlines.h` (`lSzDuel_GetUnit`, the body
  of `SzDuel_GetUnit`; `Max`, `Abs`, ...) and `SzDuel_MapInfo`, the body of `SzDuel_GetMapInfo`, sits in
  `include/game.h` next to `boardSquares`; the real function returns its inline. A `static inline` helper still
  named `<what>_<address>` (`slot_001CEE60`) has one caller's file to itself, or is a copy whose own spelling the
  match needs (a note says so).
- A function the JP table does not name keeps `func_XXXXXXXX` until the code says what it does; then it gets a
  name in the style of its neighbours (`SzDuel_` + verb + object for a duel function).
- Renames go through `config/symbol_addrs.txt`, with the old name kept as an alias in `config/old_names.txt`
  (the code modules call the old names).
- **One line above every function** saying what it does: `/* Side player's life points. */`

## Globals

- English lowerCamelCase for a global (`duelState`), with `/* original: <JP name> */` when it has one.
- Renames go through `config/symbol_addrs.txt` (`name = 0xADDR;`, no type), with the old `D_` name, and the JP
  name when it differs, as aliases in `config/old_data_names.txt`; then `make split` and `make check`.
- An address inside a named object (`D_003181E4`, 0xD54 bytes into `duelState`) becomes a field of that
  object's struct (`duelState.s.turnOwner`), checked with `make check`. Where a function only matches reading
  the separate symbol, the symbol stays, declared next to the struct with a comment saying which field it is.

## Types, struct fields and numbers

- Shared data is described as named structs, so code reads `DUEL_PLAYER(player)->lifePoints`, not
  `*(u16 *)(duelState.b + player * 0x350 + 0x33A)`. A type shared by several files lives in a header
  (`include/game.h` for now, by system later) under an English noun (`DuelPlayer`, `DuelDeck`); the JP debug
  name where there is one (`TreeTag`). A type used by one function only stays beside it.
- Field names: the JP debug member names where they exist (`dwID`, `eNO`); else English lowerCamelCase
  (`lifePoints`, `cursorX`), with the byte offset in a comment (`/* 0x33A */`). Unknown space is
  `u8 padXXX[...]` (named by its offset); a field whose use is known but not its meaning is `unkXXX`.
- Special numbers get names: `#define CARD_NONE 999` (an empty card slot), `CARD_COUNT`, the operation codes
  `DUEL_CALC_ADD`..`DUEL_CALC_SET`; enums for states and phases.
- A fixed memory area with a layout gets a struct and a name for it (`campaignWork`, `include/campaign.h`).
  Where the original reads a field with another type than the declared one, the read keeps it:
  `*(u8 *)&campaignWork.eventPictureAlpha` is the same address, and the read type picks the instruction.
- The function-local view structs the decompiler wrote (`Entry_001DE5C0`, `State_001C35A0`) are replaced by the
  shared types once the shared type covers them.
- Changing a shared header recompiles every file: run the full `make check`, and watch the state-sensitive
  files below. Prefer adding fields in place of padding over moving things.

## Parameters and locals

- Every function's own variables get names too: parameters (`arg0` -> `player`, `card`, `slot`) and locals
  (`temp_v0` -> `damage`), the JP debug names where they exist (`eInfo`, `nSide`). A parameter rename follows
  the definition, `include/functions.h` and the callers.
- Loop counters stay `i`/`j`.

## Comments

- One line above each function: what it does, in plain words.
- Byte offsets beside struct fields.
- **Every construct that exists only to match the original bytes gets a short note**, so a reader knows not
  to "clean it up": pragmas, block-scope prototypes, `(void)x;`, dead stores, a pointer computed by hand
  instead of indexing, a local pointer instead of a direct access:

  ```c
  extern s32 func_001A22C0(f32); /* declared here with a float parameter: needed for the match */
  value = result; /* this copy is kept for the match */
  ```

- Notes on how a function was matched stay in the existing `/* ... */` blocks; do not delete them.

## The state-sensitive files

MWCC carries memory from one function to the next inside a file. In these files a function only matches behind
its predecessors: `src/duel/szduel_act.c` (SzDuel_Act), `src/duel/szduel_cards.c` (SzDuel_SetupCard_Pipe),
`src/battle/szbattle.c` (lSzBattle_DrawGrass_Pipe, DrawFakeShadow / FakeMirror), `src/campaign/tkcamp.c`
(Taku_Camp_Event_Name / Event_Window), `src/game/szview_look.c` (SzView_RollCamera),
`src/campaign/taku_camp_cinema.c` (Taku_Camp_TEXT_WHO); `src/campaign/taku_camp_act.c`'s first function
(Taku_Camp_ENEMY_WINDOW) only matches first in its file. The README's *How the files are split* has more.Edit them in small steps and run `make check` after each one.

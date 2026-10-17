# How a duel runs

## Getting there

The game is a stack of **modes** (`gameState`, `src/main_037.c`): `SzGame_Push` enters a mode on top of the
current one, `SzGame_Pop` returns, `SzGame_Goto` replaces it. Each mode has an init (`SzGame_ModeInit`), a
per-frame act (`SzGame_ModeAct`), draw functions (`SzGame_ModeDraw`, `ModeDrawAfter`, `ModeDrawLast`) and a
term (`SzGame_ModeTerm`). A duel is one of these modes; deck building, trade, custom duel, the map editor, the
3D card viewer, the campaign map and the title screen are others.

## Setting up

`SzDuel_Init(stage, firstSide, newDuel)` (`src/main_038.c`) clears both sides' deck, graveyard and hand. A
new duel then deals each side's current deck from its save profile (40 cards, shuffled into random free
slots by `SzDuel_AddDeck`, or in order when the debug menu says so), places both leaders (side 0 at square
(3, 6), side 1 at (3, 0)), resets the board's field colours and sets both sides' starting values: 4000 life
points and summon charge 3 (stages below 0x16 only), summon power 4. `SzDuel_SetupMap(stage)` lays out the field types
of the board from the built-in maps or the player's edited ones.

## The duel state

Everything about the running duel is in `duelState` (`include/game.h`): two `DuelPlayer` records (one per
side: deck, graveyard, hand, life points, who plays it, the board cursor, summon power and charge, the
camera orbit) and the shared fields after them (whose turn it is, the turn count, window flags, and the work
areas of the duel-side menus). Read and change a side through the accessors in `src/main_044.c`
(`SzDuel_GetLP`, `SzDuel_CalcLP`, `SzDuel_AddHand`, `SzDuel_DrawDeck`, `SzDuel_AddGrave`, ...).

The board is `boardSquares` (7 x 7 records of 0x1C bytes: field type, colour, highlight, the unit standing
there). Units are `duelUnits`: 3 groups (side 0, side 1, and a third group not yet explained) of 11 units (0 =
the leader, 1..10 the cards), 0x5C bytes each, read with `SzDuel_GetUnit(side, unit)` and the `SzDuel_GetUnit*` /
`SzDuel_SetUnit*` accessors (`src/main_045.c`, `main_046.c`): attack and defence (with their power-ups),
level, kind and attribute, curse and spell-binding counters, status flags, position.

## One frame

`SzDuel_Act` (`src/main_042.c`) is the duel's state machine: it reads the side's input (`lSzDuel_GetControl`:
the pad, or the computer opponent's or the tutorial's moves), moves the cursor, opens the hand
(`lSzDuel_InitHandUp` draws up to five cards, with the destiny draw), summons, moves, fights
(`SzBattle_Entry` starts a 3D battle; `SzDuel_GetPlayMotion` picks its animation), fuses and equips, runs
effects (`SzEffect_EntryCallback`), and ends the turn (`SzDuel_InitTurn`). The computer opponent's choices
come from the `TaLogic*` files; the card rules from the `Ta_*` files.

## Drawing

The duel screen is drawn by `SzDuel_DrawStage_Pipe` (the board), `SzDuel_DrawUnit_Pipe` (monsters and cards on
the board), `SzDuel_DrawAllCard_Pipe` (cards in the air and in hand), `SzDuel_DrawWindow_Pipe` (the info
windows: player info, level, summon cost, card info, field) and `SzDuel_DrawDialog_Pipe` (pick windows and
messages). Card faces are rendered into textures by `SzDuel_SetupCard_Pipe`.

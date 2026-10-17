# How the code is organised

A map of the main program (`SLUS_205.15`) for modders. Every function in it is C that rebuilds the retail
executable byte for byte; the code modules (`DATA/*MODULE.MRG`) are a separate program family (`src/mod`).

## Where things are

| Files | System | Prefixes |
|---|---|---|
| `src/main_000.c` | start-up, main loop, frame drawing; small geometry helpers; effect helpers | `main`, `Main_*`, `G*`, `ShFx_*` |
| `src/main_001.c`, `main_002.c` | the effect scripts' object helpers (fades, colours, vectors, quads) | `Lk*`, `OBJ_*`, `MODEL_*`, `CARD_*`, `PAINT_*` |
| `src/main_003.c` | the sound driver's EE side | `SD_*` |
| `src/main_004.c`-`main_016.c` | how the computer opponent chooses its moves: each computer duelist has its own copy of the same routines (its controller is an entry of `duelistControllers`) | `TaLogic*` |
| `src/main_017.c`, `main_080.c` (part) | the tutorial | `TaTuto_*` |
| `src/main_018.c`-`main_036.c` (with `main_033b`..`main_035e`) | Sony's libraries and the C library (newlib, libgcc) | `sce*`, kernel calls, libc names |
| `src/main_037.c` | game modes (the state machine above everything), title screen, debug menu, memory-card jobs | `SzGame_*` |
| `src/main_038.c`-`main_046.c` | the duel screen and the duel-side menus: windows, hand, cards on the board, units, the board itself, deck building, trade, custom duel, map editor, pop-ups | `SzDuel_*` |
| `src/main_042.c` | `SzDuel_Act`, the duel's state machine (one frame of a duel) | |
| `src/main_047.c`-`main_049.c` | 3D battles, events, the model system (84 model slots) | `SzBattle_*`, `SzEvent_*`, `SzModel_*` |
| `src/main_050.c`-`main_052.c` | effects (24 slots) and their scene settings | `SzEffect_*` |
| `src/main_052.c`, `main_053.c` | the camera | `SzView_*` |
| `src/main_053.c` | fades, message text, file reads | `SzFade_*`, `SzMsg_*`, `SzFile_*` |
| `src/main_054.c`, `main_055.c` | files, textures, pads, debug tools, screen projection | `SzFile_*`, `RhFile_*`, `SzText_*`, `SzPad_*`, `SzDebug_*`, `Ex3d_*` |
| `src/main_056.c`-`main_059.c` | the renderer: draw lists, VU1, frame buffers, matrices, views, model drawing and motions | `Ex*`, `RhVu1Mac_*`, `RhBase_*`, `RhMem_*`, `RhMath_*`, `RhGeom*`, `RhView_*`, `RhModel*`, `RhZSort_*` |
| `src/main_059.c`, `main_060.c` | the save profiles: trunk, decks, ranks, options, treasures | `SzData_*` |
| `src/main_060.c` | sound | `SzSound_*` |
| `src/main_061.c`-`main_068.c`, several `big_func_002*` | the campaign map and its events | `Taku_*`, `TkCamp_*` |
| `src/main_068.c` | memory card save/load, colours, the movie player's buffers | `TkMc_*`, `TakuSave_*`, `TakuLoad_*`, `SzColor_*` |
| `src/main_069.c`, `main_070.c` | the movie player (Sony's ezmpeg sample), duelist faces | `audioDec*`, `viBuf*`, `videoDec*`, `ShFace_*` |
| `src/main_070.c`-`main_079.c` | card rules and the AI's tools: battles, fusions, equips, traps, effects | `Ta_*`, `TaEnc_*`, `TaUtil_*`, `TaEffect_*`, `TaHand_*`, `TaView_*` |
| `src/main_080.c` | the slot machine | `ShSlot_*` |
| `src/big_func_*.c` | very large functions kept in a file of their own (one function each, named by address) | |

## Conventions you will meet

- **`*_Pipe` functions** write GS/VIF packets: the first parameter is where the packet continues, and the
  return value is the new end. The plain version (`SzDuel_DrawWindow`) wraps it:
  `RhBase_SetVifPacketArea(X_Pipe(RhBase_GetVifPacketArea()))`.
- **Units** are addressed as (side, unit): side 0 or 1, unit 0 the leader and 1..10 the cards on the board.
  Effects and battle code pack the pair as `(side << 8) | unit` (a unit id); a board location word is
  `(z << 8) | x` (`SzDuel_GetUnitLoc`).
- **Board squares** are (x, z), 0..6 each; the 3D position of square (x, z) is `((x - 3) * 50, height,
  (z - 3) * 50)`.
- **Model slots** are 0..83 (`modelSlots`); 0 is the stage, 5 and 6 the two leaders.
- **Card ids** are 0..0x355 (`CARD_COUNT`); `CARD_NONE` (999) marks an empty slot; card 0x29F
  (`CARD_REJECTED`) is treated as no card: the deck, graveyard and hand adders refuse it.
- **Arithmetic operations** of the `Calc*` functions (`SzDuel_CalcLP`, `SzDuel_CalcSummonPower`,
  `SzData_CalcExp`, `SzDuel_CalcUnitAP`) are `DUEL_CALC_ADD`, `SUB`, `MUL`, `DIV`, `SET`.
- **Pads:** `SzPad_Check(pad, mode, mask)` with mode 0 newly pressed, 1 held, 2 newly pressed or repeating.
- Constructs written only so the build matches carry a short note (`needed for the match`); leave them as they
  are.

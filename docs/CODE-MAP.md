# How the code is organised

A map of the main program (`SLUS_205.15`) for modders. Every function in it is C that rebuilds the retail
executable byte for byte; the code modules (`DATA/*MODULE.MRG`) are a separate program family (`src/mod`).

## Where things are

One folder per area, one file per system. Where the Japanese release's symbol table shows where one of Konami's
source files ended, a file ends there too; the README's *How the files are split* says how the cuts were found and
which files are parts of one bigger original file.

| Files (`src/`) | System | Prefixes |
|---|---|---|
| `core/crt0.c`, `core/main.c` | Sony's start-up code; `main()` and the main loop (start every system, run and draw each frame) | `main`, `Main_*` |
| `core/mw_cpp_rts.c` | Metrowerks' C++ run-time start-up | |
| `effect_lib/g.c`, `shfx.c`, `lk.c`, `objlib.c` | the effect helpers (one original file in four parts): small geometry, clipping, timers, texture UVs, splines, vibration, counters, and the object helpers the effect scripts call | `G*`, `ShFx_*`, `Lk*`, `OBJ_*`, `MODEL_*`, `CARD_*`, `PAINT_*` |
| `sound/sd*.c` | the sound driver's EE side: start-up, BGM and sound effects, PCM streaming, request queues, file reads, calls to the IOP | `SD_*`, `SDFS_*`, `SDRPC_*` |
| `sound/szsound.c` | the game's sound calls | `SzSound_*` |
| `ai/<duelist>.c` | how the computer opponent chooses its moves: each computer duelist has its own file with its own copy of the same routines (its controller is an entry of `duelistControllers`); `ai/default.c` serves every duelist without its own | `TaLogic*` |
| `ai/talogic.c` | the AI logic every duelist shares | `TaLogic_*` |
| `tutorial/` | the tutorial: the scripted opponent of lessons 1 to 5, the tutorial driver | `TaTuto_*` |
| `game/szgame.c` | game modes (the state machine above everything), title screen, debug menu, memory-card jobs | `SzGame_*` |
| `duel/szduel_*.c` | the duel screen and the duel-side menus (one original file in 12 parts): start-up and stage, windows and hand cards, deck building, trade, custom duel, the map editor, cards and card sessions, the board squares, players and life points, units, terrain, pop-ups | `SzDuel_*` |
| `duel/szduel_act.c` | `SzDuel_Act`, the duel's state machine (one frame of a duel) | |
| `battle/` | 3D battles, events, the model system (84 model slots), effects (24 slots) and their scene settings | `SzBattle_*`, `SzEvent_*`, `SzModel_*`, `SzEffect_*` |
| `game/szview.c`, `szview_look.c` | the camera | `SzView_*` |
| `game/szfade.c`, `szmsg.c` | screen fades; message boxes and their font | `SzFade_*`, `SzMsg_*` |
| `game/shanime.c`, `shface.c`, `shslot.c` | 2D animation data, duelist faces, the slot-machine reels | `ShAnime_*`, `ShFace_*`, `ShSlot_*` |
| `system/` | file reads, text and texture files, the pad, debug tools, the save profiles (trunk, decks, ranks, options, treasures), memory helpers, colours | `SzFile_*`, `RhFile_*`, `SzText_*`, `SzPad_*`, `SzDebug_*`, `SzData_*`, `RhMemCard_*`, `SzMem_*`, `SzColor_*` |
| `render/` | the renderer: screen projection, draw lists, VU1, frame buffers, matrices, views, textures, model drawing and motions, model file relocation | `Ex3d_*`, `Ex*`, `RhVu1Mac_*`, `RhBase_*`, `RhMem_*`, `RhMath_*`, `RhGeom*`, `RhView_*`, `RhText_*`, `RhModel*`, `RhZSort_*`, `NjaReloc_*` |
| `campaign/taku_*.c`, `tkcamp.c` | the campaign map and its events, windows, cut scenes | `Taku_*`, `TkCamp_*` |
| `campaign/tkmc.c` | memory card save / load / trade | `TkMc_*`, `TakuSave_*`, `TakuLoad_*`, `TakuTrade_*` |
| `movie/` | the movie player (Sony's ezmpeg sample code, one file per sample file) | `readBuf*`, `audioDec*`, `viBuf*`, `videoDec*`, `voBuf*` |
| `rules/` | card rules and the AI's tools: battles, enchantments and fusions, traps, card effects, leader abilities, the end phase | `Ta_*`, `TaEnc_*`, `TaUtil_*`, `TaEffect_*`, `TaHand_*`, `TaView_*` |
| `sdk/` | Sony's libraries and the C library (newlib, libgcc), still cut by address: see `src/sdk/README.md` | `sce*`, kernel calls, libc names |

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

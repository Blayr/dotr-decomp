# Where the game's data lives

## Cards

- **Card ids** run 0..0x355 (854 cards, `CARD_COUNT`). Cards from 0x2AB on earn no leader rank (`SzData_GetRank`).
- **Constant card data:** 20 bytes per card at `D_002BF080` (`SzDuel_GetCardConstInfo(card)`): kind in the
  top bits of byte 0, deck cost at byte 3, attack at +8 and defence at +0xA (13 bits each), level in a nibble
  of byte 2. Not a named struct yet.
- **Card numbers vs ids:** the old card-list order maps to ids through `D_002CD8A0`
  (`SzDuel_Xax2New` / `SzDuel_New2Xax`).
- **Names:** card `card`'s name is message `card + 0x140` (`SzDuel_GetMsgName`).
- **3D view distance** per monster: `D_002CE4A4` (`SzDuel_GetCamDist`).
- **Leader abilities:** `D_002C3338[card][5]` (`SzDuel_GetUnitLeaderAbility3`, `..._Detail_Ability_Pipe`).
- **Card passwords:** looked up by `lSzDuel_HitPassword` (the 8-digit table at `D_002BEF79`).
- **Card rules tables:** fusions `fusionTable` (`Fusion`, `WallFusion`), equips `equipMatchTable`
  (`Do_ChkEncMatch`, `Enchant`), the destiny draw's card triples `destinyDrawTable` (`Ta_GetDestinyDraw`).

## Decks

- **Built-in decks:** 51 decks of 41 cards (`D_002D0970[deck][slot]`, the leader first, card id in the low 12
  bits and the leader's rank in the top 4): `SzData_GetConstDeck`, `SzData_SetupFromConstDeck`.
- **A side's decks:** three per save profile (see SAVE.md).

## Duelists

- `DuelPlayer.duelistId` says who plays a side: 0..0x1F a computer duelist, 0x20..0x63 a tutorial script (both
  play through `duelistControllers[id]`, JP `g_aLogFunc`: duelist N is `duelistControllerNN`, id 0
  and the unused ids use `duelistControllerDefault`, 0x20..0x24 are `TaTuto_Lesson1..5`), 100 + n the
  human on pad n.
- Duelist portraits are texture items of category 2 (`lSzDuel_DrawWindow_PicMini_Pipe`).

## Maps

- Built-in maps: `D_002CEE5C[map][7][7]` field types (maps 0..0x2D); maps 0x2E..0x32 are duel side 0's
  five edited maps, 0x33..0x37 side 1's, each read from that side's save profile (`SzDuel_SetupMap`, `SzData_GetData(side)`).
- Field type 7 is the plain field (edited maps start all 7); 8 behaves as a labyrinth wall for walking
  (`lSzDuel_CalcMapMovableRecursive`).

## Models and textures

- Models load by group and set from merged files (`SzModel_LoadMerge`, `modelFileOffsets`,
  `modelGroupInfo`) or one by one (`SzModel_Load`), into the 84 `modelSlots`.
- Textures are TIM2 files kept as texture items (`textureItems`, 1024 records, categories 0..9) and sent to
  GS memory per frame (`SzText_DoRequest_Pipe`).

## Fixed memory areas

Memory the game uses at fixed addresses outside the program's own data (names in `include/common.h`):

- `CAMPAIGN_WORK_ADDR` (0x01ED0000, 0x54B0 bytes): the campaign map's running state, laid out as
  `CampaignWork` in `include/campaign.h` and read as `campaignWork.field` (the camera, the routes between
  places, the event script's step, the talk window, the cut-scene player, the name entry, the starting-deck
  choice, the windows and menus). Deck building, trade, the duel, effects, the AI's search tree and the slot
  machine borrow the same memory as scratch while the campaign is not running.
- `CUSTOM_DUEL_ADDR` (0x00A9C000): the custom-duel and map-editor settings (layout in the comment beside it).
- `OVERLAY_ADDR` (0x01E00000): where a duel effect's code overlay is copied and linked.
- `GAME_DATA_COPY_ADDR` (0x01E301E0): a copy of the game data; the save file is read into it.
- `include/ee_regs.h`: the EE and GS hardware registers and the scratchpad (`SCRATCHPAD_ADDR`), by the names of
  Sony's manuals, as plain addresses (`*(volatile u32 *)D_STAT_ADDR`).

# The save profiles

Offsets are into one profile; numbers are hexadecimal.

The game keeps two profiles in `saveProfiles` (JP `gSzData_All`, 2 x 0xFFA0 bytes). `profileZeroSide` (JP
`gSzData_bRoseFlag`) is the duel side that plays with profile 0; the other side gets profile 1
(`SzData_GetData(side)`). The memory-card code (`TkMc_*`, `TakuSave_*`, `TakuLoad_*`, `src/main_068.c`) writes
and reads them.

| Offset | Size | What | Read/written by |
|---|---|---|---|
| 0x0000 | 0x356 x 0x4C | per card: 9 trunk entries of 8 bytes (each copy owned: the profile it came from and a serial, a type, a flag), the experience with the card (u16, `SzData_CalcExp`), its rank, its seen/new/password flags | `SzData_AddBag`, `AddBag2`, `DelBag`, `CheckDup`, `GetBagCount`, `GetRank`, `SetRankDirect`, `GetLookFlag`, `IsBagNew`, `GetPassFlag` |
| 0xFD88 | 5 x u16 | the five newest cards the side got, newest first (CARD_NONE when empty) | `SzData_PushBagNew`, `SzData_IsBagNew` |
| 0xFD94 | 3 x 0x54 | the three decks: 40 card ids, the leader, the card count | `SzData_PushDeck`, `PullDeck`, `PushDeckLeader`, `GetLeader`, `GetCardNo`, `GetDeckCount`, `CalcDeckCost` |
| 0xFE90 | 16 | one counter per special-card entry: which alternative card the side gets next (stepped by `SzData_RollSpecial`, wrapping) | `SzData_RollSpecial`, `SzData_ExchSpecial` |
| 0xFEA3 | 5 x 7 x 7 | the five edited maps' field types (7 = plain field) | `SzDuel_ActMapEdit`, `SzDuel_SetupMap` |
| later | | the treasures found, the current deck, the profile id (`defaultCard` in the code: the owner id stamped on trunk copies), the options (bits: two duel options and the sound output) | `SzData_GetTreasureFlag`, `GetCurrentDeck`, `GetOption` |

Notes:

- A **trunk copy** records which profile it came from (0: this one) and a serial, so a traded card cannot be
  added twice (`SzData_CheckDup`).
- `SzData_SetupFromConstDeck(side, deck)` builds a fresh profile from a built-in deck (the start of a new game
  and the custom duel's computer side).
- The memory-card file also holds the icon (`card_icon_tukuru`) and a checksum (`LkCheckData`).

To be completed and checked when the save's struct is named (a later batch).

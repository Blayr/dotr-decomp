/* The duel screen (SzDuel_*), part 1 of 15 of one original Konami file (szduel, 361 functions, cut here by feature): start-up, shutdown, the stage. */

#include "common.h"

/* Clears the duel state and sets up the cards, map and requests for a new duel. */
void SzDuel_Initialize(void) {
    u8 *state = duelState.b;
    s32 x;
    s32 y;
    u8 *cell;
    s32 group;
    s32 index;
    u8 *entry;
    u8 *row;

    RhMem_FillMemory((s8 *)duelState.b, 0, 0xD70);
    SzDuel_InitCardRequest();
    SzDuel_InitCardControl();
    y = 0;
    do {
        x = 0;
        do {
            cell = SzDuel_GetMapInfo(x, y);
            SzDuel_InitMapInfo(cell);
            cell[0x16] = (y + x) % 10;
            x++;
        } while (x < 7);
        y++;
    } while (y < 7);

    row = duelUnits;
    group = 0;
    do {
        index = 0;
        entry = row;
        do {
            SzDuel_InitCardInfo(entry, -1);
            index++;
            entry += 0x5C;
        } while (index < 11);
        group++;
        row += 0x3F4;
    } while (group < 3);

    state[0x33C] = 100;
    state[0x68C] = 100;
    SzDuel_Init(0, 0, 0);
}

/* Sets up what every duel-side mode shares: which models draw, and the lights and fog for duels and monsters. */
void lSzDuel_InitCom(s32 arg0) {
    extern s32 SzGame_GetMode();
    s32 mode;
    s32 i;

    mode = SzGame_GetMode(1);
    SzView_SetStraightLight(0, 9, 1);
    i = 0;
    do {
        SzModel_SetDrawFlag(i, 0);
        i++;
    } while (i < 0x54);
    i = 0;
    do {
        SzModel_SetDrawFlag(i, 1);
        i++;
    } while (i < 5);
    i = 0;
    do {
        SzModel_SetDrawFlag(i + 5, 1);
        i++;
    } while (i < 2);
    i = 0;
    do {
        SzModel_SetDrawFlag(i + 0x14, 1);
        i++;
    } while (i < 0xA);
    i = 0;
    do {
        SzModel_SetDrawFlag(i + 0x1E, 1);
        i++;
    } while (i < 2);
    i = 0;
    do {
        SzModel_SetDrawFlag(i + 0x20, 1);
        i++;
    } while (i < 2);
    i = 0;
    do {
        SzModel_SetDrawFlag(i + 0x4A, 1);
        i++;
    } while (i < 0xA);
    if (mode == 1) {
        s32 j = 0;
        do {
            SzModel_SetDeform(j + 0x14, 1);
            SzModel_SetDeformRatio(j + 0x14, 0x20);
            j++;
        } while (j < 0xA);
        j = 0;
        do {
            SzModel_SetDeform(j + 0x1E, 1);
            SzModel_SetDeformRatio(j + 0x1E, 0x20);
            j++;
        } while (j < 2);
    }
    if (arg0 != 0) {
        s32 color = (s32) &duelStageParams;
        s32 ambient = (s32) &D_0029100C;
        s32 matrix = (s32) &D_00291020;
        s32 range = (s32) &D_002910B0;
        s32 position = (s32) &D_002910B8;

        SzEffect_SetFogColorForMonster((s32) position);
        SzEffect_SetFogColorForDuel((s32) position);
        SzEffect_SetFogParamZForMonster(0);
        SzEffect_SetFogParamZForDuel(0);
        if (((f32 *) range)[0] == ((f32 *) range)[1]) {
            SzEffect_SetFogParamYForMonster(0);
            SzEffect_SetFogParamYForDuel(0);
        } else {
            SzEffect_SetFogParamYForMonster((s32) range);
            SzEffect_SetFogParamYForDuel((s32) range);
        }
        SzEffect_SetStraightLightForMonster((s32) matrix);
        SzEffect_SetStraightLightForDuel((s32) matrix);
        SzEffect_SetPointLightForMonster(0);
        SzEffect_SetPointLightForDuel(0);
        SzEffect_SetIntensityForMonster((s32) ambient);
        SzEffect_SetIntensityForDuel((s32) color);
        SzEffect_SetBlackOutForMonster(0x80);
        SzEffect_SetBlackOutForDuel(0x80);
    }
}

typedef union {
    __int128 quad;
    f32 f[4];
} Vec_001ADD00;

typedef struct {
    s8 bit0 : 1;
    s8 bit1 : 1;
    s8 bit2 : 1;
    s8 bit3 : 1;
    s8 bit4 : 1;
    s8 bit5 : 1;
    s8 bit6 : 1;
    s8 bit7 : 1;
} Bits_001ADD00;

typedef struct {
    s8 low : 2;
    s8 next : 2;
    s8 unused : 2;
    s8 bit6 : 1;
    s8 bit7 : 1;
} Modes_001ADD00;

typedef struct {
    s8 bit0 : 1;
    u8 bit1 : 1;
    s8 bit2 : 1;
    s8 bit3 : 1;
    s8 bit4 : 1;
    s8 bit5 : 1;
    s8 bit6 : 1;
    s8 bit7 : 1;
} MixedBits_001ADD00;

extern Vec_001ADD00 D_002910C0;
extern Vec_001ADD00 D_002910D0;

/* Sets up a duel on map `stage` with side `firstSide` to move first; a `newDuel` also deals both decks, places the
   leaders and resets the board. */
void SzDuel_Init(s32 stage, s32 firstSide, s32 newDuel) {
    Vec_001ADD00 cameraPos;
    Vec_001ADD00 cameraLook;
    u8 *state = duelState.b;
    s32 row;
    u8 *side1;
    u8 *halfwords;
    u8 *words;
    s32 i;

    SzDuel_InitDeck(0);
    SzDuel_InitGrave(0);
    SzDuel_InitHand(0);
    SzDuel_InitDeck(1);
    SzDuel_InitGrave(1);
    SzDuel_InitHand(1);
    row = 0;
    if (newDuel != 0) {
        s32 deck0;
        s32 deck1;
        s32 unit;
        s32 leader0;
        s32 leader1;
        s32 card0;
        s32 card1;
        s32 slot;
        s32 x;
        s32 z;
        s32 otherPlayer;
        s32 option;
        s32 heading;
        deck0 = SzData_GetCurrentDeck(0);
        deck1 = SzData_GetCurrentDeck(1);
        leader0 = SzData_GetLeader(0, deck0);
        leader1 = SzData_GetLeader(1, deck1);
        SzDuel_InitCardRequest();
        SzDuel_InitCardControl();
        unit = 0;
        do {
            SzDuel_DelUnit(0, unit);
            SzDuel_DelUnit(1, unit);
            unit += 1;
        } while (unit < 0xB);
        SzDuel_InitMapColor(0, 0, 1);
        SzDuel_AddUnit(0, 3, 6, leader0, 1);
        SzDuel_AddUnit(1, 3, 0, leader1, 1);
        SzDuel_SetUnitCtlRateM(0, 0, 0, 0);
        SzDuel_SetUnitCtlModeM(0, 0, 7);
        SzDuel_SetUnitCtlRateM(1, 0, 0, 0);
        SzDuel_SetUnitCtlModeM(1, 0, 7);
        slot = 0;
        do {
            card0 = SzData_GetCardNo(0, deck0, slot);
            card1 = SzData_GetCardNo(1, deck1, slot);
            if (SzGame_GetMenuNum(3) >= 0x3E8) {
                SzDuel_AddDeck(0, card0);
            } else {
                SzDuel_SetDeck(0, slot, card0);
            }
            if (SzGame_GetMenuNum(4) >= 0x3E8) {
                SzDuel_AddDeck(1, card1);
            } else {
                SzDuel_SetDeck(1, slot, card1);
            }
            slot += 1;
        } while (slot < 0x28);
        option = 0;
        otherPlayer = firstSide ^ 1;
        do {
            SzData_SetOption(otherPlayer, option, SzData_GetOption(firstSide, option));
            option += 1;
        } while (option < 3);
        heading = (firstSide != 0) ? 0xC000 : 0x4000;
        cameraPos = D_002910C0;
        cameraLook = D_002910D0;
        cameraLook.f[1] = (3.1415927f * (f32) heading) / 32768.0f;
        SzView_SetCP(0, &cameraPos);
        SzView_SetLookSP(0, cameraLook.f);
        z = 0;
        do {
            x = 0;
            do {
                SzDuel_SetFieldRate(x, z, -0x80);
                x += 1;
            } while (x < 7);
            z += 1;
        } while (z < 7);
        *(u8 *)(state + 0xD34) = 0;
        SzSound_TransferSEGrp(1, 0, 0);
    } else {
        s32 column;
        for (row = 0; row < 7; row++) {
            for (column = 0; column < 7; column++) {
                SzDuel_SetFieldRate(column, row, 0);
            }
        }
        *(u8 *)(state + 0xD34) = 0x80;
    }
    *(u8 *)(state + 0xD37) = (u8) stage;
    SzDuel_SetupMap((s32) *(u8 *)(state + 0xD37));
    lSzDuel_InitCom(newDuel);
    TaLogic_InitLogicData(0, state);
    *(s32 *)(state + 0x330) = -1;
    if (*(s32 *)(state + 0x334) != 0) {
        SzMem_Free(*(s32 *)(state + 0x334));
    }
    *(s32 *)(state + 0x334) = 0;
    *(s16 *)(state + 0x338) = 0;
    *(s32 *)(state + 0x1D0) = 0xC8;
    *(s32 *)(state + 0x1D4) = 0x4000;
    *(s32 *)(state + 0x1D8) = 0x2000;
    *(s8 *)(state + 0x341) = 4;
    if (stage < 0x16) {
        *(s16 *)(state + 0x33A) = 0xFA0;
        *(s8 *)(state + 0x342) = 3;
    }
    *(s8 *)(state + 0x343) = 0;
    ((Bits_001ADD00 *)(state + 0x346))->bit0 = 1;
    *(s8 *)(state + 0x344) = 0;
    *(s8 *)(state + 0x345) = 0x28;
    *(s8 *)(state + 0x33D) = 3;
    *(s8 *)(state + 0x33E) = 6;
    side1 = state + 0x350;
    TaLogic_InitLogicData(1, side1);
    *(s32 *)(side1 + 0x330) = -1;
    if (*(s32 *)(side1 + 0x334) != 0) {
        SzMem_Free(*(s32 *)(side1 + 0x334));
    }
    *(s32 *)(side1 + 0x334) = 0;
    *(s16 *)(side1 + 0x338) = 0;
    *(s32 *)(side1 + 0x1D0) = 0xC8;
    *(s32 *)(side1 + 0x1D4) = 0xC000;
    *(s32 *)(side1 + 0x1D8) = 0x2000;
    *(s8 *)(side1 + 0x341) = 4;
    if (stage < 0x16) {
        *(s16 *)(side1 + 0x33A) = 0xFA0;
        *(s8 *)(side1 + 0x342) = 3;
    }
    *(s8 *)(side1 + 0x343) = 0;
    ((Bits_001ADD00 *)(side1 + 0x346))->bit0 = 1;
    *(s8 *)(side1 + 0x344) = 0;
    *(s8 *)(side1 + 0x345) = 0x28;
    *(s8 *)(side1 + 0x33D) = 3;
    *(s8 *)(side1 + 0x33E) = 0;
    *(s32 *)(state + 0x6C8) = 0;
    *(s32 *)(state + 0x6CC) = 0;
    *(s8 *)(state + 0xD35) = 0;
    *(s8 *)(state + 0xD36) = 0;
    *(s8 *)(state + 0xD38) = 0;
    *(s8 *)(state + 0xD39) = 0;
    *(s8 *)(state + 0xD3A) = 0;
    *(s8 *)(state + 0xD3B) = 0;
    *(s8 *)(state + 0xD50) = 2;
    *(s8 *)(state + 0xD51) = 0;
    *(u8 *)(state + 0xD52) = (u8) firstSide;
    *(u8 *)(state + 0xD54) = (u8) *(u8 *)(state + 0xD52);
    *(u8 *)(state + 0xD53) = 0U;
    *(u8 *)(state + 0xD55) = 0xFF;
    *(u8 *)(state + 0xD56) = 0xFF;
    *(s8 *)(state + 0xD57) = 0;
    *(s8 *)(state + 0xD58) = 0x18;
    *(s8 *)(state + 0xD5B) = 0;
    *(s8 *)(state + 0xD59) = 0;
    *(s8 *)(state + 0xD5A) = 0;
    *(u8 *)(state + 0xD3C) = (u8) *(u8 *)(state + 0xD52);
    *(u8 *)(state + 0xD3D) = (u8) *(u8 *)(state + 0xD53);
    *(u8 *)(state + 0xD3E) = 0x80;
    *(s8 *)(state + 0xD3F) = 0;
    *(s8 *)(state + 0xD40) = 0;
    *(s8 *)(state + 0xD41) = 0;
    *(s8 *)(state + 0xD42) = 0;
    *(s8 *)(state + 0xD43) = 0;
    *(s8 *)(state + 0xD44) = 0;
    *(s8 *)(state + 0xD45) = 0;
    *(s8 *)(state + 0xD46) = 0;
    *(s8 *)(state + 0xD47) = 0;
    *(s8 *)(state + 0xD48) = 0;
    *(s8 *)(state + 0xD49) = 0;
    *(s8 *)(state + 0xD4A) = 0;
    *(s8 *)(state + 0xD4B) = 0;
    *(s8 *)(state + 0xD4C) = 0;
    *(s8 *)(state + 0xD4D) = 0;
    *(s8 *)(state + 0xD4E) = 0;
    *(s8 *)(state + 0xD4F) = 0;
    *(s8 *)(state + 0xD63) = 0;
    *(s16 *)(state + 0xC86) = 0;
    *(s16 *)(state + 0xC88) = 0;
    ((Modes_001ADD00 *)(state + 0xD64))->low = 1;
    ((Modes_001ADD00 *)(state + 0xD64))->next = 1;
    *(s16 *)(state + 0xC96) = 0;
    *(s16 *)(state + 0xC98) = 0;
    i = 0;
    halfwords = state;
    words = state;
    do {
        *(s8 *)(&state[i] + 0xCB2) = 0x18;
        *(s16 *)(halfwords + 0xCAA) = 0;
        i += 1;
        *(s16 *)(words + 0xC9C) = 0;
        *(s16 *)(words + 0xC9A) = 0;
        halfwords += 2;
        words += 4;
    } while (i < 4);
    *(s32 *)(state + 0xC5C) = 0;
    *(s32 *)(state + 0xC60) = 0;
    *(s32 *)(state + 0xC64) = 0;
    *(s32 *)(state + 0xC68) = 0;
    *(s32 *)(state + 0xC78) = -1;
    *(s32 *)(state + 0xC6C) = 0;
    *(s32 *)(state + 0xC70) = 0;
    *(s32 *)(state + 0xC74) = 0;
    ((Modes_001ADD00 *)(state + 0xD64))->bit6 = 0;
    ((Modes_001ADD00 *)(state + 0xD64))->bit7 = 0;
    ((Bits_001ADD00 *)(state + 0xD65))->bit0 = 0;
    ((Bits_001ADD00 *)(state + 0xD65))->bit1 = 0;
    ((Bits_001ADD00 *)(state + 0xD65))->bit2 = 0;
    ((Bits_001ADD00 *)(state + 0xD65))->bit3 = 0;
    ((Bits_001ADD00 *)(state + 0xD65))->bit4 = 0;
    ((Bits_001ADD00 *)(state + 0xD65))->bit5 = 0;
    ((Bits_001ADD00 *)(state + 0xD65))->bit6 = 0;
    ((Bits_001ADD00 *)(state + 0xD65))->bit7 = 0;
    ((MixedBits_001ADD00 *)(state + 0xD66))->bit0 = 0;
    ((MixedBits_001ADD00 *)(state + 0xD66))->bit1 = 0;
    ((MixedBits_001ADD00 *)(state + 0xD66))->bit2 = 0;
    ((MixedBits_001ADD00 *)(state + 0xD66))->bit3 = 0;
    ((MixedBits_001ADD00 *)(state + 0xD66))->bit4 = 0;
    ((MixedBits_001ADD00 *)(state + 0xD66))->bit5 = 0;
    ((MixedBits_001ADD00 *)(state + 0xD66))->bit6 = 0;
    ((MixedBits_001ADD00 *)(state + 0xD66))->bit7 = 1;
    ((Bits_001ADD00 *)(state + 0xD67))->bit0 = ((MixedBits_001ADD00 *)(state + 0xD66))->bit7;
    ((Bits_001ADD00 *)(state + 0xD67))->bit1 = 1;
    ((Bits_001ADD00 *)(state + 0xD67))->bit2 = 0;
    ((Bits_001ADD00 *)(state + 0xD67))->bit3 = 0;
    ((Bits_001ADD00 *)(state + 0xD67))->bit4 = 0;
    ((Bits_001ADD00 *)(state + 0xD67))->bit5 = 0;
}

/* Ends a duel: removes every unit from the board. */
void SzDuel_Term(void) {
    u8 *data = duelState.b;
    s32 i;
    s32 unit;

    i = 0;
    do {
        data[i + 0xCB2] = 0x18;
        i += 1;
    } while (i < 4);
    unit = 1;
    do {
        SzDuel_DelUnit(0, unit);
        SzDuel_DelUnit(1, unit);
        unit += 1;
    } while (unit < 0xB);
}

/* Draws the duel board into `packet` if the stage model is shown. */
s32 SzDuel_DrawStage_Pipe(s32 packet) {
    if (SzModel_GetDrawFlag(0) != 0) {
        return lSzDuel_DrawStage_Pipe(packet);
    }
    return packet;
}

typedef struct Color_001AE5F0 {
    u8 r, g, b, a;
} Color_001AE5F0;

typedef struct Vector_001AE5F0 {
    s32 coord[4];
} Vector_001AE5F0;

extern Color_001AE5F0 D_002910E0;
extern Color_001AE5F0 D_002910E8;
extern Color_001AE5F0 D_002910F0;
extern Color_001AE5F0 D_002910F8;
extern Color_001AE5F0 D_00291100;
extern Color_001AE5F0 D_00291108;
extern Vector_001AE5F0 D_00291110;
extern u16 D_00318116;

/* Draws the duel board: its squares and their colours, the movable-square highlights and the box cursor. */
s32 lSzDuel_DrawStage_Pipe(s32 packet) {
    extern s32 SzDuel_DrawBoxCursor_Pipe();
    extern void SzDuel_InitMapColor();
    extern void SzDuel_SetMapColor();
    extern s32 SzDuel_GetMapMovable();
    extern s32 SzDuel_SetMapAlpha();
    extern s32 SzEffect_GetBlackOutForDuel();
    u8 *player;
    u8 *state;
    u32 opacity;
    s32 x;
    s32 y;
    u8 alpha;
    s64 mode;
    Color_001AE5F0 *color;
    f32 position[4];
    Vector_001AE5F0 offset;
    Color_001AE5F0 own;
    Color_001AE5F0 other;
    Color_001AE5F0 special;
    Color_001AE5F0 board;
    Color_001AE5F0 range;
    Color_001AE5F0 background;
    f32 scale;
    s32 brightness;

    state = duelState.b;
    player = duelState.b + duelState.s.turnOwner * 0x350;
    mode = SzGame_GetMode(1);
    alpha = (u8)((((s32)D_00318116 >> 8) & 0xFF) + 0x40);
    own = D_002910E0;
    own.r = duelState.s.turnOwner == 1 ? 0x60 : 0;
    own.g = state[0xD54] == 1 ? 0x60 : 0;
    own.b = state[0xD54] == 1 ? 0x60 : 0x80;
    own.a = alpha;
    other = D_002910E8;
    other.r = state[0xD54] == 0 ? 0x60 : 0;
    other.g = state[0xD54] == 0 ? 0x60 : 0;
    other.b = state[0xD54] == 0 ? 0x60 : 0x80;
    other.a = alpha;
    special = D_002910F0;
    special.r = state[0xD54] == 0 ? 0x60 : 0x60;
    special.g = state[0xD54] == 0 ? 0 : 0x80;
    special.b = state[0xD54] == 0 ? 0x80 : 0;
    special.a = alpha;
    color = NULL;
    opacity = (u8)SzEffect_GetBlackOutForDuel();
    scale = (f32)opacity / 128.0f;
    SzEffect_SetIntensityOnly(0, scale);
    SzEffect_SetIntensityOnly(1, scale);
    SzEffect_SetIntensityOnly(8, scale);
    brightness = (u8)opacity;
    y = 0;
    do {
        x = 0;
        do {
            SzDuel_SetMapAlpha(x, y, brightness);
            x++;
        } while (x < 7);
        y++;
    } while (y < 7);

    if ((u64)mode < 2U) {
        SzDuel_InitMapColor(0, 0, 0);
    }
    if (mode == 1 && state[0xD57] >= 0x13) {
        s32 row;
        s32 col;
        u8 *tile;
        board = D_002910F8;
        range = D_00291100;
        background = D_00291108;
        tile = (u8 *)SzDuel_GetMapUnit(player[0x33D], player[0x33E]);
        if (tile != NULL && tile[0x44] != state[0xD54]) {
            color = &other;
        } else {
            color = &own;
        }
        if (state[0xD57] >= 0x1D) {
            color = &special;
        }
        switch (state[0xD57]) {
        case 0x16:
        case 0x18:
            own.a = 0x40;
            for (row = 0; row < 7; row++) {
                for (col = 0; col < 7; col++) {
                    if (player[0x33D] != col && player[0x33E] != row) {
                        continue;
                    }
                    SzDuel_SetMapColor(col, row, 1, &own, 0);
                }
            }
            own.a = alpha;
            break;
        case 0x1D:
            SzDuel_InitMapColor(2, &background, 0);
            row = 0;
            do {
                col = 0;
                do {
                    s32 distance = SzDuel_GetMapMovable(col, row);
                    if (distance < 0xFF) {
                        range.a = distance <= state[0xD5A] ? 0xD0 : 0x40;
                        SzDuel_SetMapColor(col, row, 1, &range, 0);
                    }
                    col++;
                } while (col < 7);
                row++;
            } while (row < 7);
            for (row = 0; row < state[0xD59]; row++) {
                SzDuel_SetMapColor(state[0xCCA + row], state[0xCFB + row], 1, &special, 0);
            }
            break;
        case 0x21:
            break;
        case 0x3E:
            SzDuel_InitMapColor(2, &background, 0);
            row = 0;
            do {
                col = 0;
                do {
                    if (SzDuel_GetMapMovable(col, row) < 0xFF) {
                        SzDuel_SetMapColor(col, row, 1, &board, 0);
                    }
                    col++;
                } while (col < 7);
                row++;
            } while (row < 7);
            break;
        }
        SzDuel_SetMapColor(player[0x33D], player[0x33E], 1, color, 0);
        row = 0;
        do {
            col = 0;
            do {
                SzDuel_CalcMapColor(col, row);
                col++;
            } while (col < 7);
            row++;
        } while (row < 7);
    }
    {
        u8 *tile;
        s32 id;
        tile = SzDuel_GetMapInfo(player[0x33D], player[0x33E]);
        id = tile[0x16] + 0x4A;
        if (SzModel_IsModelDisp(id) != 0 && color != NULL) {
            SzDuel_CalcUnitPos(player[0x33D], player[0x33E], *(s16 *)(tile + 0x14), position);
            if (*(s16 *)(tile + 0x14) > 0) {
                packet = SzDuel_DrawBoxCursor_Pipe(packet, position, NULL, 1);
            }
            packet = SzModel_DrawWithOutCalc_Pipe(packet, id, (s32)position, 0, 0, 0, 0);
            color->a = (alpha * tile[0x1A]) >> 7;
            SzModel_SetFilter(id, -1, color);
            packet = SzModel_DrawWithOutCalc_Pipe(packet, id, (s32)position, 0, 0, 0, 0x80FFFFF6);
            SzModel_SetFilter(id, -1, NULL);
            color->a = alpha;
        }
    }
    {
        s32 id;
        u8 *tile;
        s32 row;
        s32 col;
        s32 kind;
        kind = 0;
        do {
            id = kind + 0x4A;
            if (SzModel_IsModelDisp(id) != 0) {
                row = 0;
                do {
                    col = 0;
                    do {
                        tile = SzDuel_GetMapInfo(col, row);
                        if (tile[0x16] == kind) {
                            if (color == NULL || player[0x33D] != col || player[0x33E] != row) {
                                SzDuel_CalcUnitPos(col, row, *(s16 *)(tile + 0x14), position);
                                if (*(s16 *)(tile + 0x14) > 0) {
                                    packet = SzDuel_DrawBoxCursor_Pipe(packet, position, NULL, 1);
                                }
                                packet = SzModel_DrawWithOutCalc_Pipe(packet, id, (s32)position, 0, 0, 0, 0);
                            }
                        }
                        col++;
                    } while (col < 7);
                    row++;
                } while (row < 7);
            }
            kind++;
        } while (kind < 10);
    }
    {
        s32 id = 0;
        do {
            if (SzModel_IsModelDisp(id) != 0) {
                packet = SzModel_DrawWithOutCalc_Pipe(packet, id, 0, 0, 0, 0, 0);
            }
            id++;
        } while (id < 3);
    }
    {
        s32 id;
        x = 0;
        do {
            id = x + 5;
            offset = D_00291110;
            offset.coord[1] = x != 0 ? 0 : 0x8000;
            if (SzModel_IsModelDisp(id) != 0) {
                offset.coord[1] -= 0x2000;
                packet = SzModel_DrawWithOutCalc_Pipe(packet, id, 0, (s32)&offset, 0, 0, 0);
                offset.coord[1] += 0x4000;
                packet = SzModel_DrawWithOutCalc_Pipe(packet, id, 0, (s32)&offset, 0, 0, 0);
            }
            x++;
        } while (x < 2);
    }
    return packet;
}

/* Draws what goes over the board (the side walls and the line). */
void SzDuel_DrawStageAfter(void) {
    RhBase_SetVifPacketArea(SzDuel_DrawStageAfter_Pipe(RhBase_GetVifPacketArea()));
}

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4_001AEEB0;

extern Vec4_001AEEB0 D_00291120;
#pragma opt_lifetimes off

/* Draws the two side models mirrored left and right, then the board line. */
s32 SzDuel_DrawStageAfter_Pipe(s32 packet) {
    Vec4_001AEEB0 pos;
    s32 model;
    s32 out;

    out = packet;
    if (SzModel_GetDrawFlag(0) == 0) {
        return out;
    }
    model = 3;
    do {
        pos = D_00291120;
        pos.z = (model == 4) ? 180.0f : -180.0f;
        if (SzModel_IsModelDisp(model) != 0) {
            out = SzModel_ExSort_Pipe(out, model, (s32)&pos, 0, 0, 0, 0);
            pos.x *= -1.0f;
            out = SzModel_ExSort_Pipe(out, model, (s32)&pos, 0, 0, 0, 0);
        }
        model += 1;
    } while ((s32) model < 5);
    return SzDuel_DrawLine_Pipe(out);
}
#pragma opt_lifetimes reset

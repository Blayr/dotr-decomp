#include "common.h"

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

void SzDuel_Init(s32 arg0, s32 arg1, s32 arg2) {
    Vec_001ADD00 spA0;
    Vec_001ADD00 spB0;
    u8 *state = duelState.b;
    s32 var_s1;
    u8 *temp_s1_2;
    u8 *var_t2;
    u8 *var_t3;
    s32 var_t4;

    SzDuel_InitDeck(0);
    SzDuel_InitGrave(0);
    SzDuel_InitHand(0);
    SzDuel_InitDeck(1);
    SzDuel_InitGrave(1);
    SzDuel_InitHand(1);
    var_s1 = 0;
    if (arg2 != 0) {
        s32 temp_s1;
        s32 temp_s2;
        s32 var_s3;
        s32 temp_s5;
        s32 temp_s4;
        s32 temp_s3;
        s32 temp_s4_2;
        s32 var_s5;
        s32 var_s1_2;
        s32 var_s2_2;
        s32 otherPlayer;
        s32 var_s2;
        s32 heading;
        temp_s1 = SzData_GetCurrentDeck(0);
        temp_s2 = SzData_GetCurrentDeck(1);
        temp_s5 = SzData_GetLeader(0, temp_s1);
        temp_s4 = SzData_GetLeader(1, temp_s2);
        SzDuel_InitCardRequest();
        SzDuel_InitCardControl();
        var_s3 = 0;
        do {
            SzDuel_DelUnit(0, var_s3);
            SzDuel_DelUnit(1, var_s3);
            var_s3 += 1;
        } while (var_s3 < 0xB);
        SzDuel_InitMapColor(0, 0, 1);
        SzDuel_AddUnit(0, 3, 6, temp_s5, 1);
        SzDuel_AddUnit(1, 3, 0, temp_s4, 1);
        SzDuel_SetUnitCtlRateM(0, 0, 0, 0);
        SzDuel_SetUnitCtlModeM(0, 0, 7);
        SzDuel_SetUnitCtlRateM(1, 0, 0, 0);
        SzDuel_SetUnitCtlModeM(1, 0, 7);
        var_s5 = 0;
        do {
            temp_s3 = SzData_GetCardNo(0, temp_s1, var_s5);
            temp_s4_2 = SzData_GetCardNo(1, temp_s2, var_s5);
            if (SzGame_GetMenuNum(3) >= 0x3E8) {
                SzDuel_AddDeck(0, temp_s3);
            } else {
                SzDuel_SetDeck(0, var_s5, temp_s3);
            }
            if (SzGame_GetMenuNum(4) >= 0x3E8) {
                SzDuel_AddDeck(1, temp_s4_2);
            } else {
                SzDuel_SetDeck(1, var_s5, temp_s4_2);
            }
            var_s5 += 1;
        } while (var_s5 < 0x28);
        var_s2 = 0;
        otherPlayer = arg1 ^ 1;
        do {
            SzData_SetOption(otherPlayer, var_s2, SzData_GetOption(arg1, var_s2));
            var_s2 += 1;
        } while (var_s2 < 3);
        heading = (arg1 != 0) ? 0xC000 : 0x4000;
        spA0 = D_002910C0;
        spB0 = D_002910D0;
        spB0.f[1] = (3.1415927f * (f32) heading) / 32768.0f;
        SzView_SetCP(0, &spA0);
        SzView_SetLookSP(0, spB0.f);
        var_s2_2 = 0;
        do {
            var_s1_2 = 0;
            do {
                SzDuel_SetFieldRate(var_s1_2, var_s2_2, -0x80);
                var_s1_2 += 1;
            } while (var_s1_2 < 7);
            var_s2_2 += 1;
        } while (var_s2_2 < 7);
        *(u8 *)(state + 0xD34) = 0;
        SzSound_TransferSEGrp(1, 0, 0);
    } else {
        s32 var_s2_3;
        for (var_s1 = 0; var_s1 < 7; var_s1++) {
            for (var_s2_3 = 0; var_s2_3 < 7; var_s2_3++) {
                SzDuel_SetFieldRate(var_s2_3, var_s1, 0);
            }
        }
        *(u8 *)(state + 0xD34) = 0x80;
    }
    *(u8 *)(state + 0xD37) = (u8) arg0;
    SzDuel_SetupMap((s32) *(u8 *)(state + 0xD37));
    lSzDuel_InitCom(arg2);
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
    if (arg0 < 0x16) {
        *(s16 *)(state + 0x33A) = 0xFA0;
        *(s8 *)(state + 0x342) = 3;
    }
    *(s8 *)(state + 0x343) = 0;
    ((Bits_001ADD00 *)(state + 0x346))->bit0 = 1;
    *(s8 *)(state + 0x344) = 0;
    *(s8 *)(state + 0x345) = 0x28;
    *(s8 *)(state + 0x33D) = 3;
    *(s8 *)(state + 0x33E) = 6;
    temp_s1_2 = state + 0x350;
    TaLogic_InitLogicData(1, temp_s1_2);
    *(s32 *)(temp_s1_2 + 0x330) = -1;
    if (*(s32 *)(temp_s1_2 + 0x334) != 0) {
        SzMem_Free(*(s32 *)(temp_s1_2 + 0x334));
    }
    *(s32 *)(temp_s1_2 + 0x334) = 0;
    *(s16 *)(temp_s1_2 + 0x338) = 0;
    *(s32 *)(temp_s1_2 + 0x1D0) = 0xC8;
    *(s32 *)(temp_s1_2 + 0x1D4) = 0xC000;
    *(s32 *)(temp_s1_2 + 0x1D8) = 0x2000;
    *(s8 *)(temp_s1_2 + 0x341) = 4;
    if (arg0 < 0x16) {
        *(s16 *)(temp_s1_2 + 0x33A) = 0xFA0;
        *(s8 *)(temp_s1_2 + 0x342) = 3;
    }
    *(s8 *)(temp_s1_2 + 0x343) = 0;
    ((Bits_001ADD00 *)(temp_s1_2 + 0x346))->bit0 = 1;
    *(s8 *)(temp_s1_2 + 0x344) = 0;
    *(s8 *)(temp_s1_2 + 0x345) = 0x28;
    *(s8 *)(temp_s1_2 + 0x33D) = 3;
    *(s8 *)(temp_s1_2 + 0x33E) = 0;
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
    *(u8 *)(state + 0xD52) = (u8) arg1;
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
    var_t4 = 0;
    var_t2 = state;
    var_t3 = state;
    do {
        *(s8 *)(&state[var_t4] + 0xCB2) = 0x18;
        *(s16 *)(var_t2 + 0xCAA) = 0;
        var_t4 += 1;
        *(s16 *)(var_t3 + 0xC9C) = 0;
        *(s16 *)(var_t3 + 0xC9A) = 0;
        var_t2 += 2;
        var_t3 += 4;
    } while (var_t4 < 4);
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

void SzDuel_Term(void) {
    u8 *data = duelState.b;
    s32 var_a1;
    s32 var_s0;

    var_a1 = 0;
    do {
        data[var_a1 + 0xCB2] = 0x18;
        var_a1 += 1;
    } while (var_a1 < 4);
    var_s0 = 1;
    do {
        SzDuel_DelUnit(0, var_s0);
        SzDuel_DelUnit(1, var_s0);
        var_s0 += 1;
    } while (var_s0 < 0xB);
}

s32 SzDuel_DrawStage_Pipe(s32 arg0) {
    if (SzModel_GetDrawFlag(0) != 0) {
        return lSzDuel_DrawStage_Pipe(arg0);
    }
    return arg0;
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

s32 lSzDuel_DrawStage_Pipe(s32 arg0) {
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
    player = duelState.b + D_003181E4 * 0x350;
    mode = SzGame_GetMode(1);
    alpha = (u8)((((s32)D_00318116 >> 8) & 0xFF) + 0x40);
    own = D_002910E0;
    own.r = D_003181E4 == 1 ? 0x60 : 0;
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
                arg0 = SzDuel_DrawBoxCursor_Pipe(arg0, position, NULL, 1);
            }
            arg0 = SzModel_DrawWithOutCalc_Pipe(arg0, id, (s32)position, 0, 0, 0, 0);
            color->a = (alpha * tile[0x1A]) >> 7;
            SzModel_SetFilter(id, -1, color);
            arg0 = SzModel_DrawWithOutCalc_Pipe(arg0, id, (s32)position, 0, 0, 0, 0x80FFFFF6);
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
                                    arg0 = SzDuel_DrawBoxCursor_Pipe(arg0, position, NULL, 1);
                                }
                                arg0 = SzModel_DrawWithOutCalc_Pipe(arg0, id, (s32)position, 0, 0, 0, 0);
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
                arg0 = SzModel_DrawWithOutCalc_Pipe(arg0, id, 0, 0, 0, 0, 0);
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
                arg0 = SzModel_DrawWithOutCalc_Pipe(arg0, id, 0, (s32)&offset, 0, 0, 0);
                offset.coord[1] += 0x4000;
                arg0 = SzModel_DrawWithOutCalc_Pipe(arg0, id, 0, (s32)&offset, 0, 0, 0);
            }
            x++;
        } while (x < 2);
    }
    return arg0;
}

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

s32 SzDuel_DrawStageAfter_Pipe(s32 arg0) {
    Vec4_001AEEB0 sp30;
    s32 var_s0;
    s32 var_s1;

    var_s1 = arg0;
    if (SzModel_GetDrawFlag(0) == 0) {
        return var_s1;
    }
    var_s0 = 3;
    do {
        sp30 = D_00291120;
        sp30.z = (var_s0 == 4) ? 180.0f : -180.0f;
        if (SzModel_IsModelDisp(var_s0) != 0) {
            var_s1 = SzModel_ExSort_Pipe(var_s1, var_s0, (s32)&sp30, 0, 0, 0, 0);
            sp30.x *= -1.0f;
            var_s1 = SzModel_ExSort_Pipe(var_s1, var_s0, (s32)&sp30, 0, 0, 0, 0);
        }
        var_s0 += 1;
    } while ((s32) var_s0 < 5);
    return SzDuel_DrawLine_Pipe(var_s1);
}
#pragma opt_lifetimes reset

s32 SzDuel_StartWindowSession_Pipe(s32 arg0) {
    return SzDuel_StartWindowSessionWithPalette_Pipe(arg0, 0);
}

s32 SzDuel_StartWindowSessionWithPalette_Pipe(s32 arg0, s32 arg1) {
    extern s32 *SzMsg_GetInfo(s32);
    extern s32 SzText_InitClutManage(s32, s32);
    u8 *base;
    s32 addr;
    s32 length;
    s32 i;

    base = duelState.b;
    addr = RhBase_GetUserGsAddress();
    addr += SzText_InitClutManage(addr, 2);
    arg0 = SzMsg_Init_Pipe(arg0, arg1, addr, &length);
    i = 0;
    addr += length;
    do {
        *(s32 *)(base + i * 4 + 0x6A0) = 0;
        i++;
    } while (i < 9);
    *(s32 *)(base + 0x6B8) = SzText_LoadRequest(3, 6);
    *(s32 *)(base + 0x6BC) = SzText_LoadRequest(3, 7);
    arg0 = SzText_DoRequest_Pipe(arg0, 3, addr, &length);
    addr += length;
    SzText_FreeRequest(3, -1);
    {
        s32 *info;

        arg0 = SzMsg_LoadFont_Pipe(arg0, 0, 0x15, 0, 0);
        info = SzMsg_GetInfo(0);
        info[3] = 0x16;
        arg0 = RhText_SetTextureFlush(arg0);
    }
    *(s32 *)(base + 0xC7C) = addr;
    *(s32 *)(base + 0xC58) = 0xFFFFF8;
    SzMsg_SetDefPrioZ(0xFFFFF8);
    return arg0;
}

s32 SzDuel_FinishWindowSession_Pipe(s32 arg0) {
    SzMsg_Free(0);
    return arg0;
}

typedef struct {
    u8 pad[0x6A0];
    s32 entries[8];
} Data_001AF140;

s32 SzDuel_GetWindowTexture(s32 arg0) {
    Data_001AF140 *data = (Data_001AF140 *)duelState.b;

    if ((arg0 < 0) || (arg0 >= 8)) {
        return 0;
    }
    return data->entries[arg0];
}

typedef struct {
    s8 bit0 : 1;
    s8 bit1 : 1;
    s8 bit2 : 1;
    s8 bit3 : 1;
    s8 bit4 : 1;
    s8 bit5 : 1;
    s8 bit6 : 1;
    s8 bit7 : 1;
} Flags_001AF180;

typedef struct {
    u8 r, g, b, a;
} Color_001AF180;

typedef struct {
    u8 pad00[4];
    Color_001AF180 color;
} Palette_001AF180;

struct CardNode_001AF180_s {
    f32 x, y;
    u8 pad08[0x3C];
    Color_001AF180 color;
    u8 pad48[0x39];
    Flags_001AF180 flags81;
    u8 pad82;
    Flags_001AF180 flags83;
    u8 pad84[0xC];
    s32 resource;
};

typedef struct {
    CardNode_001AF180 *object;
    u8 pad04[0xC];
    u8 tracks[2][0x10];
    u8 pad30[0x40];
    f32 scale;
    u8 pad74[0x24];
    u16 duration;
    u16 timer;
    u8 pad9C[3];
    Flags_001AF180 flags9F;
} Actor_001AF180;

s32 func_001D9F00(void *, s32);
extern u16 D_00318118;

static inline f32 abs_001AF180(f32 value) {
    if (value < 0.0f) {
        return -value;
    }
    return value;
}

s32 SzDuel_DrawHandCard_Pipe(s32 arg0, CardNode_001AF180 *object) {
    extern Palette_001AF180 gSzDuel_aaicolRgba[];
    u8 *state = duelState.b;
    s32 i;
    s32 id;
    Actor_001AF180 *actor;
    s32 resource;

    if (func_001AAF60(1) != 1) {
        return arg0;
    }
    if (!((Flags_001AF180 *)(state + 0xD67))->bit2) {
        if (state[0xD45] == 0 && state[0xD47] == 0 && state[0xD48] == 0) {
            return arg0;
        }
    }
    i = 5;
    do {
        id = state[0xD2C + i];
        actor = func_001CDE70(id);
        if (actor != NULL) {
            object = actor->object;
            if (object != NULL) {
                resource = object->resource;
                if (!object->flags83.bit6) {
                    if (id != 0) {
                        if (state[0xD47] == 0 && state[0xD4F] == id - 1) {
                            object->color = gSzDuel_aaicolRgba[state[0xD3C]].color;
                            object->color.a = D_00318118 >> 8;
                        } else {
                            object->color.a = 0;
                        }
                    }
                    if (actor->flags9F.bit6) {
                        s32 phase;
                        f32 difference = actor->scale - 0.1f;
                        u32 color;
                        f32 progress;
                        extern u32 Ex3d_GetSampleZ(f32, void *);
                        difference = difference >= 0.0f ? difference : -difference;
                        phase = difference <= 0.000001f ? 0 : 1;
                        color = Ex3d_GetSampleZ(30.0f, actor->tracks[phase]);
                        progress = (f32)(u32)actor->timer / (f32)(u32)actor->duration;
                        if (phase != 0) {
                            progress = 1.0f - progress;
                        }
                        func_001D9ED0((u32)((f32)color * (1.0f - progress) + 16777210.0f * progress));
                    } else {
                        func_001D9ED0(0xFFFFFA);
                    }
                    if (actor->flags9F.bit2) {
                        func_001DA2B0(object, 1, object->x, object->y);
                        arg0 = func_001DBC40(arg0, resource, object);
                    } else {
                        s32 result = func_001D9F00(object, 1);
                        resource = result ? resource : 0;
                        arg0 = func_001DBC40(arg0, resource, object);
                        if (0 != id) {
                            if (state[0xD47] != 0) {
                                if (((Flags_001AF180 *)(state + 0xD67))->bit4) {
                                    if (object->flags81.bit4 && result == 0) {
                                        object->flags81.bit4 = 0;
                                        object->flags81.bit6 = 0;
                                    }
                                } else {
                                    if (!object->flags81.bit4 && result == 0) {
                                        object->flags81.bit4 = 1;
                                        object->flags81.bit6 = 1;
                                    }
                                }
                            }
                        }
                    }
                    arg0 = func_0020A0B0(func_001DBD30(func_0020A0B0(arg0, 1), (s32)object), 0);
                }
            }
        }
        i--;
    } while (i >= 0);
    return arg0;
}

s32 SzDuel_DrawHandCursor_Pipe(s32 arg0) {
    extern s32 SzGame_GetMode(s32);
    extern s32 lSzDuel_DrawWindow_Frame_Pipe();
    extern s32 lSzDuel_DrawWindow_Icon_Pipe();
    extern s32 SzDuel_DrawWindow_FontDigit_Pipe();
    extern u8 D_002902A6[];
    s32 mode;
    s32 player;
    u8 *state;
    f32 *pos;
    s32 count;
    s32 i;
    s32 x;
    s32 y;
    s32 kind;

    state = duelState.b;
    mode = SzGame_GetMode(1);
    player = D_003181E4;
    count = SzDuel_GetHandCount(player);
    if (mode != 1) {
        return arg0;
    }
    if (state[0xD45] == 0) {
        return arg0;
    }
    if (state[0xD47] != 0) {
        return arg0;
    }
    for (i = 0; i < count; i++) {
        pos = (f32 *)SzDuel_GetUnit(2, i + 1);
        if (pos != NULL) {
            pos = ((f32 **)pos)[1];
            if (pos != NULL) {
                x = (s32)pos[0] + 0x104;
                y = (s32)pos[1] + 0x8B;
                kind = SzDuel_InqHand(player, i);
                if (kind >= 0) {
                    if (state[0xD4F] == i) {
                        arg0 = lSzDuel_DrawWindow_Frame_Pipe(arg0, -1, -1, 8, x, y - 4, 0xC, 0x13, 1);
                    }
                    if ((kind & 0xFFF) != 0x3E7) {
                        kind = (kind & 0xF000) >> 12;
                        if (kind != 0) {
                            arg0 = lSzDuel_DrawWindow_Icon_Pipe(arg0, D_002902A6, x + 0x6C0, y + 0x704, 1, 1, 0, 0, 1, 0, -1);
                            arg0 = SzDuel_DrawWindow_FontDigit_Pipe(arg0, x + 0x10, y - 0x17, 0, 2, 1, kind);
                        }
                    }
                }
            }
        }
    }
    return arg0;
}

void SzDuel_DrawDialog(void) {
    RhBase_SetVifPacketArea(SzDuel_DrawDialog_Pipe(RhBase_GetVifPacketArea()));
}

typedef struct Flags_001AF7E0 {
    s8 unused : 4;
    s8 horizontal : 1;
    s8 enabled : 1;
    s8 colored : 1;
    s8 reserved : 1;
} Flags_001AF7E0;

typedef struct Draw_001AF7E0 {
    u8 pad00[0x30];
    s32 scale[4];
    u8 pad40[0x41];
    Flags_001AF7E0 flags;
    u8 pad82[0xE];
} Draw_001AF7E0;

typedef struct Card_001AF7E0 {
    u8 pad00[0x44];
    s8 owner;
    u8 pad45[0x1B];
} Card_001AF7E0;

extern char *D_00291130[];
extern u8 gSzDuel_Icon[];
extern u8 D_00290828[];
extern u8 D_00290832[];
extern u8 D_00290AA8[];
extern u8 D_00290AB2[];
extern u8 D_00290AF8[];
extern u8 D_00290B02[];

s32 SzDuel_DrawDialog_Pipe(s32 arg0) {
    extern s32 lSzDuel_DrawDialog_Window_Pipe();
    extern s32 lSzDuel_DrawWindow_Icon_Pipe();
    extern s32 lSzDuel_DrawWindow_Frame_Pipe();
    extern s32 lSzDuel_DrawWindow_Board_Pipe();
    extern s32 func_001BDAF0();
    extern s32 SzMsg_LoadFont_Pipe();
    extern s32 SzMsg_DrawX_Pipe();
    extern s32 SzDuel_DrawWindow_Font_Pipe();
    extern s32 SzData_GetRank();
    extern s32 lSzDuel_OpenHandCursor_Pipe();
    extern s32 SzMsg_DrawRatioX_Pipe(s32, s32, s32, s32, f32, f32, s32, void (*)(void));
    extern void SzDuel_ClearDrawCard();
    s32 x_c21;
    s32 x_c20;
    s32 y_c21;
    s32 y_c20;
    char *text_c12;
    s32 x_c12;
    s32 value_c21;
    s32 x_c18;
    s32 width_c21;
    s32 value_c20;
    s32 i_c18;
    s32 width_c20;
    char *text_c8;
    char *text_c7;
    s32 side_c7;
    s32 width;
    char *text1_c8;
    Card_001AF7E0 card;
    s32 y_c7;
    char *text2_c8;
    Draw_001AF7E0 draw;
    Draw_001AF7E0 draw2;
    s32 slot_c7;
    Card_001AF7E0 card2;
    s32 mode2;
    u8 *entry;
    u8 *state = duelState.b;
    s32 mode4;
    char *text;
    s32 x_c7;
    s32 index;
    u8 *p2;
    s32 lowB;
    u8 type;
    s32 icon;
    s32 extra_c9;
    s32 packet;
    char *text_c14;
    u16 *list;
    f32 scale;
    s32 y;
    s32 start;
    s32 page;
    s32 end;
    s32 cardId;
    s32 count;
    s32 value;
    s32 row;
    s32 side;
    s32 cursor;
    s32 on;
    s32 color;
    s32 x;
    s32 lowA;
    s32 dir;
    s32 w;
    s32 msg;
    s32 id;
    u8 *pic;
    u8 *p4;
    char *text1;
    char *text2;
    s32 y_c22;
    s32 value_c22_c22;
    s32 width_c22;
    s32 i;
    s32 side_c9;
    s32 id_c9;
    s32 res;

    index = count = 0;
    for (; index < 4; index++) {
        if (state[index + 0xCB2] != 0x18) {
            count++;
        }
    }
    if (count == 0) {
        return arg0;
    }
    packet = SzDuel_StartWindowSessionWithPalette_Pipe(arg0, 0);
    SzDuel_SetWindowDefPrioZ(0xFFFFFE);
    SzMsg_SetDefPrioZ(0xFFFFFE);
    for (index = 0, p4 = state, p2 = state; index < 4; p4 += 4, index++, p2 += 2) {
        type = state[index + 0xCB2];
        if (type == 0x18) {
            continue;
        }
        switch (type) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
            side = state[0xD54];
            text = D_00291130[type];
            y = 0x200 - ((*(s16 *)(p4 + 0xC9C) << 9) >> 6);
            cardId = *(u16 *)(p2 + 0xCAA);
            color = side | 0x8000;
            if (type == 2U || type == 3U || type == 4U || type == 5U) {
                cardId = -1;
            }
            if (type == 6) {
                cardId = -1;
                side = 2;
            }
            packet = lSzDuel_DrawDialog_Window_Pipe(packet, side, color, cardId, 0x140, y + 0x80, 0x15A, 0, func_0019BEF0(text), (s32)text, 1);
            break;
        case 7:
            y_c7 = *(s16 *)(p4 + 0xC9C);
            x_c7 = y_c7 + 0xD9;
            text_c7 = D_00291130[type];
            slot_c7 = state[0xD35];
            side_c7 = state[0xD54];
            mode2 = state[0xD36] & 2;
            mode4 = state[0xD36] & 4;
            packet = lSzDuel_DrawDialog_Window_Pipe(packet, side_c7, -1, -1, 0x140, y_c7 + 0x94, 0x234, 0x98, func_0019BEF0(text_c7), (s32)text_c7, 0);
            packet = SzMsg_LoadFont_Pipe(packet, 4, 0x73, 0, 0x58);
            packet = SzMsg_LoadFont_Pipe(packet, 5, 0x77, 0, 0x6E);
            packet = SzMsg_LoadFont_Pipe(packet, 6, 0x78, 0, 0x84);
            packet = SzMsg_LoadFont_Pipe(packet, 7, 0x74, 0, 0x9A);
            packet = SzMsg_LoadFont_Pipe(packet, 8, 0x7A, 0, 0xB0);
            packet = SzMsg_LoadFont_Pipe(packet, 9, 0x79, 0, 0xC6);
            packet = RhText_SetTextureFlush(packet);
            packet = SzMsg_DrawX_Pipe(packet, 4, 0x3E, x_c7, 0, SzMsg_DrawRect_Pipe);
            packet = SzMsg_DrawX_Pipe(packet, 5, 0x11A, x_c7, (s32)(mode2 != 0 ? NULL : D_002BE944), SzMsg_DrawRect_Pipe);
            packet = SzMsg_DrawX_Pipe(packet, 6, 0x1BA, x_c7, (s32)(mode2 != 0 ? D_002BE944 : NULL), SzMsg_DrawRect_Pipe);
            packet = SzMsg_DrawX_Pipe(packet, 7, 0x3E, x_c7 + 0x28, 0, SzMsg_DrawRect_Pipe);
            packet = SzMsg_DrawX_Pipe(packet, 8, 0x11A, x_c7 + 0x28, (s32)(mode4 != 0 ? NULL : D_002BE944), SzMsg_DrawRect_Pipe);
            packet = SzMsg_DrawX_Pipe(packet, 9, 0x1BA, x_c7 + 0x28, (s32)(mode4 != 0 ? D_002BE944 : NULL), SzMsg_DrawRect_Pipe);
            SzMsg_Free(1);
            SzMsg_Free(2);
            SzMsg_Free(3);
            SzMsg_Free(4);
            SzMsg_Free(5);
            SzMsg_Free(6);
            SzMsg_Free(7);
            SzMsg_Free(8);
            SzMsg_Free(9);
            packet = lSzDuel_DrawWindow_Frame_Pipe(packet, -1, -1, 7, 0x3E, x_c7 + slot_c7 * 0x28, -0x204, -0x16, 1);
            break;
        case 8:
            side = state[0xD54];
            text_c8 = D_00291130[type];
            text1_c8 = D_002BEF6F;
            text2_c8 = D_002BEF73;
            y = 0x200 - ((*(s16 *)(p4 + 0xC9C) << 9) >> 6);
            packet = lSzDuel_DrawDialog_Window_Pipe(packet, side, -1, 0x7B, 0x140, y + 0x9F, 0x15A, 0x82, func_0019BEF0(text_c8), (s32)text_c8, 0);
            res = SzDuel_DrawWindow_Font_Pipe(packet, 0xEA, y + 0xFD, 2, 3, func_0019BEF0(text1_c8), text1_c8, state[0xD35] != 0 ? 0 : (s32)D_002BE944);
            packet = SzDuel_DrawWindow_Font_Pipe(res, 0x196, y + 0xFD, 2, 3, func_0019BEF0(text2_c8), text2_c8, state[0xD35] != 0 ? (s32)D_002BE944 : 0);
            break;
        case 9:
        case 10:
            value = *(u16 *)(p2 + 0xCAA);
            text = D_00291130[type + ((value & 0x4000) ? 1 : 0)];
            y = 0x200 - ((*(s16 *)(p4 + 0xC9C) << 9) >> 6);
            id_c9 = value & 0x3FFF;
            if (value & 0x8000) {
                side_c9 = 1;
            } else {
                side_c9 = 0;
            }
            msg = (value & 0x4000) ? 0x60 : 0x5F;
            icon = SzDuel_GetMsgName(id_c9);
            extra_c9 = SzData_GetRank(side_c9, id_c9);
            packet = lSzDuel_DrawDialog_Window_Pipe(packet, side_c9, id_c9, icon, 0x140, y + 0x4C, -0x1CC, 0x128, func_0019BEF0(text), (s32)text, 1);
            packet = SzMsg_LoadFont_Pipe(packet, 1, extra_c9 + 0x52, 0, 0x16);
            packet = SzMsg_LoadFont_Pipe(packet, 2, msg, 0, 0x2C);
            packet = RhText_SetTextureFlush(packet);
            SzMsg_GetInfo(1);
            packet = SzMsg_DrawX_Pipe(packet, 2, 0x140 - (*(s32 *)((u8 *)SzMsg_GetInfo(2) + 0xC) >> 1), y + 0x136, 0, SzMsg_DrawRect_Pipe);
            SzMsg_Free(1);
            SzMsg_Free(2);
            break;
        case 11:
            value = *(u16 *)(p2 + 0xCAA);
            text = D_00291130[type];
            y = 0x200 - ((*(s16 *)(p4 + 0xC9C) << 9) >> 6);
            icon = SzDuel_GetMsgName(value);
            width = 0x15A;
            res = RhText_SetTextureFlush(SzMsg_LoadFont_Pipe(SzMsg_LoadFont_Pipe(packet, 2, icon, 0, 0x16), 3, 0x98, 0, 0x2C));
            w = *(s32 *)((u8 *)SzMsg_GetInfo(2) + 0xC) + 0x18;
            if (w > 0x15A) {
                width = w;
            }
            w = *(s32 *)((u8 *)SzMsg_GetInfo(3) + 0xC) + 0x18;
            if (width < w) {
                width = w;
            }
            packet = lSzDuel_DrawDialog_Window_Pipe(res, 2, -1, -1, 0x140, y + 0x32, width, 0x15C, func_0019BEF0(text), (s32)text, 1);
            packet = SzMsg_DrawX_Pipe(packet, 2, 0x140 - (*(s32 *)((u8 *)SzMsg_GetInfo(2) + 0xC) >> 1), y + 0x12E, 0, SzMsg_DrawRect_Pipe);
            packet = SzMsg_DrawX_Pipe(packet, 3, 0x140 - (*(s32 *)((u8 *)SzMsg_GetInfo(3) + 0xC) >> 1), y + 0x150, 0, SzMsg_DrawRect_Pipe);
            SzMsg_Free(2);
            SzMsg_Free(3);
            SzDuel_InitCardInfo(&card, value);
            SzDuel_ClearDrawCard(&draw);
            draw.scale[0] = 0x3EF00000;
            draw.scale[1] = 0x3EFA6F4E;
            draw.scale[2] = 0x3F800000;
            draw.scale[3] = 0;
            draw.flags.reserved = 0;
            SzMsg_Free(0);
            packet = SzDuel_StartCardSession_Pipe(packet);
            SzDuel_SetCardDefPrioZ(0xFFFFFE);
            SzDuel_GetCardNodeOnScreen(&draw, 0, 0.0f, (f32)(y - 0x18));
            packet = SzDuel_DrawCard_Pipe(SzDuel_SetupCard2_Pipe(packet, (s32)&card, &draw), (s32)&draw);
            packet = SzDuel_StartWindowSessionWithPalette_Pipe(SzDuel_FinishCardSessionX_Pipe(packet), 0);
            SzDuel_SetWindowDefPrioZ(0xFFFFFE);
            SzMsg_SetDefPrioZ(0xFFFFFE);
            break;
        case 12:
        case 13:
            value = *(u16 *)(p2 + 0xCAA);
            x_c12 = *(s16 *)(p4 + 0xC9A);
            text_c12 = D_00291130[type];
            y = *(s16 *)(p4 + 0xC9C);
            icon = SzDuel_GetMsgName(value);
            packet = lSzDuel_DrawDialog_Window_Pipe(packet, 2, value, icon, x_c12 + 0x140, y + 0x4C, 0x15A, 0x128, func_0019BEF0(text_c12), (s32)text_c12, 1);
            packet = SzMsg_LoadFont_Pipe(packet, 1, 0x99, 0, 0x16);
            packet = RhText_SetTextureFlush(packet);
            entry = (u8 *)SzMsg_GetInfo(1);
            packet = SzMsg_DrawX_Pipe(packet, 1, (0x140 - (*(s32 *)(entry + 0xC) >> 1)) + x_c12, y + 0x136, 0, SzMsg_DrawRect_Pipe);
            SzMsg_Free(1);
            break;
        case 14:
            text_c14 = D_00291130[type];
            lowA = SzDuel_GetPlayer(0);
            lowB = SzDuel_GetPlayer(1);
            lowA = (lowA & 0xFF) < 0x64 ? 1 : 0;
            lowB = (lowB & 0xFF) < 0x64 ? 1 : 0;
            y = 0x200 - ((*(s16 *)(p4 + 0xC9C) << 9) >> 6);
            on = (state[0xD36] & 0x80) ? 1 : 0;
            page = state[0xD36] & 0x7F;
            start = page != 0 ? *(u16 *)(state + 0xC8E) : *(u16 *)(state + 0xC8A);
            end = page != 0 ? *(u16 *)(state + 0xC90) : *(u16 *)(state + 0xC8C);
            cursor = page != 0 ? state[0xD5F] : state[0xD5E];
            list = page != 0 ? *(u16 **)(state + 0x6DC) : *(u16 **)(state + 0x6D8);
            packet = lSzDuel_DrawDialog_Window_Pipe(packet, 2, -1, -1, 0x140, y + 0x68, 0x15A, 0xF0, func_0019BEF0(text_c14), (s32)text_c14, 0);
            if (on != 0) {
                w = y + 0x7BE;
                if (page == 0) {
                    packet = lSzDuel_DrawWindow_Icon_Pipe(packet, gSzDuel_Icon + (lowA + 0xB9) * 10, 0x7E8, w, 0, 1, 0, 0, 1, 0, 1);
                } else {
                    packet = lSzDuel_DrawWindow_Icon_Pipe(packet, gSzDuel_Icon + (lowB + 0xBB) * 10, 0x7E8, w, 0, 1, 0, 0, 1, 0, 1);
                }
            } else {
                dir = page == 0 ? 1 : -1;
                packet = lSzDuel_DrawWindow_Icon_Pipe(packet, gSzDuel_Icon + (lowA + 0xB9) * 10, 0x7B8, y + 0x7BE, 0, 1, 0, 0, (page == 0 ? 1 : 0), 0, dir);
                packet = lSzDuel_DrawWindow_Icon_Pipe(packet, D_00290B02, 0x7F1, y + 0x7C3, 0, 1, 0, 0, 1, 0, -1);
                packet = lSzDuel_DrawWindow_Icon_Pipe(packet, D_00290AF8, 0x804, y + 0x7C3, 0, 1, 0, 0, 1, 0, -1);
                w = y + 0x7BE;
                if (page == 1) {
                    dir = 1;
                } else {
                    dir = -1;
                }
                packet = lSzDuel_DrawWindow_Icon_Pipe(packet, gSzDuel_Icon + (lowB + 0xBB) * 10, 0x818, w, 0, 1, 0, 0, (page == 1 ? 1 : 0), 0, dir);
            }
            packet = lSzDuel_DrawWindow_Icon_Pipe(packet, D_00290828, 0x867, y + 0x7C2, 0, 1, 0, 0, 1, 0, -1);
            packet = lSzDuel_DrawWindow_Icon_Pipe(packet, D_00290AA8, 0x88B, y + 0x7C7, 0, 1, 0, 0, 1, 0, -1);
            packet = lSzDuel_DrawWindow_Board_Pipe(packet, page + 0xE, 0xB4, y + 0xB8, -0x118, -0x7E, page + 0xE);
            packet = lSzDuel_DrawWindow_Icon_Pipe(packet, D_00290832, 0x867, y + 0x85C, 0, 1, 0, 0, 1, 0, -1);
            packet = lSzDuel_DrawWindow_Icon_Pipe(packet, D_00290AB2, 0x88B, y + 0x85C, 0, 1, 0, 0, 1, 0, -1);
            for (i = 0, w = y + 0xBB; i < 5 && start + i < end; w += 0x18, i++) {
                id = list[start + i];
                entry = SzDuel_GetCardConstInfo(id);
                if (entry != NULL) {
                    msg = *entry >> 5;
                    value = *entry & 0x1F;
                    if (msg == 0) {
                        pic = gSzDuel_Icon + value * 10;
                    } else {
                        pic = gSzDuel_Icon + (msg + 0x14) * 10;
                    }
                    scale = 1.0f;
                    packet = SzMsg_LoadFont_Pipe(packet, 1, SzDuel_GetMsgName(id), 0, 0x16);
                    packet = RhText_SetTextureFlush(packet);
                    packet = lSzDuel_DrawWindow_Icon_Pipe(packet, pic, 0x777, w + 0x720, 0, 1, 0, 0, 1, 0, -1);
                    width = *(s32 *)((u8 *)SzMsg_GetInfo(1) + 0xC);
                    if (width > 0xFA) {
                        scale = 250.0f / (f32)width;
                    }
                    packet = SzMsg_DrawRatioX_Pipe(packet, 1, 0xCF, w, scale, 1.0f, 0, SzMsg_DrawRect_Pipe);
                    SzMsg_Free(1);
                }
            }
            if (end != 0) {
                w = y + 0xBB;
                w += cursor * 0x18;
                packet = lSzDuel_DrawWindow_Frame_Pipe(packet, -1, -1, 7, 0xB7, w, -0x112, -0x18, 1);
            }
            break;
        case 15:
        case 16:
            x = *(s16 *)(p4 + 0xC9A);
            y = *(s16 *)(p4 + 0xC9C);
            text = D_00291130[type];
            value = *(u16 *)(p2 + 0xCAA);
            packet = lSzDuel_DrawDialog_Window_Pipe(packet, 2, -1, value, x + 0x140, y + 0xE0, 0, 0, func_0019BEF0(text), (s32)text, 0);
            break;
        case 17:
            y = 0x200 - ((state[0xD3A] << 9) >> 6);
            if (state[0xD35] == 24) {
                value = *(u16 *)(*(u8 **)(state + 0x6C8) + 0x3C);
                state[0xD5C] = *(u8 *)(*(u8 **)(state + 0x6C8) + 0x44);
            } else if (state[0xD35] == 45) {
                value = *(u16 *)(p2 + 0xCAA);
                state[0xD5C] = state[0xD36] & 0x7F;
            } else if (state[0xD35] == 48) {
                value = *(u16 *)(p2 + 0xCAA);
                state[0xD5C] = state[0xD36] & 0x7F;
            } else {
                value = SzDuel_InqHand(state[0xD54], state[0xD4F]);
                if (value < 0) {
                    value = 0x3E7;
                } else {
                    value &= 0xFFF;
                }
                state[0xD5C] = state[0xD54];
            }
            packet = func_001BDAF0(packet, value, -0x1E0, y, 1, 1, 1, 0);
            break;
        case 18:
            x_c18 = *(s16 *)(p4 + 0xC9A);
            y = *(s16 *)(p4 + 0xC9C);
            value = *(u16 *)(p2 + 0xCAA);
            SzMsg_Free(0);
            packet = SzDuel_StartCardSession_Pipe(packet);
            SzDuel_SetCardDefPrioZ(0xFFFFFE);
            SzDuel_ClearDrawCard(&draw2);
            row = -0xFA;
            draw2.flags.horizontal = 0;
            draw2.flags.colored = 0;
            for (i_c18 = 0; i_c18 < 5; i_c18++) {
                id = SzDuel_InqHand(value, i_c18);
                if (id >= 0) {
                    id &= 0xFFF;
                    if (id != 0x3E7) {
                        SzDuel_InitCardInfo(&card2, id);
                        card2.owner = value;
                        SzDuel_GetCardNodeOnScreen(&draw2, 0, (f32)(x_c18 + row), (f32)y);
                        packet = SzDuel_DrawCard_Pipe(SzDuel_SetupCard2_Pipe(packet, (s32)&card2, &draw2), (s32)&draw2);
                    }
                }
                row += 0x7D;
            }
            packet = SzDuel_StartWindowSessionWithPalette_Pipe(SzDuel_FinishCardSessionX_Pipe(packet), 0);
            SzDuel_SetWindowDefPrioZ(0xFFFFFE);
            SzMsg_SetDefPrioZ(0xFFFFFE);
            break;
        case 19:
            packet = lSzDuel_DrawDialog_Window_Pipe(packet, -1, -1, *(u16 *)(p2 + 0xCAA), *(s16 *)(p4 + 0xC9A) + 0x140, *(s16 *)(p4 + 0xC9C) + 0xE0, 0, 0, 0, 0, 0);
            break;
        case 20:
            value_c20 = *(u16 *)(p2 + 0xCAA);
            x_c20 = *(s16 *)(p4 + 0xC9A);
            y_c20 = *(s16 *)(p4 + 0xC9C);
            res = SzMsg_LoadFont_Pipe(packet, 1, value_c20, 0, 0x16);
            res = RhText_SetTextureFlush(res);
            width_c20 = *(s32 *)((u8 *)SzMsg_GetInfo(1) + 0x10) + 0x18;
            SzMsg_Free(1);
            packet = lSzDuel_DrawDialog_Window_Pipe(res, -1, -1, value_c20, x_c20 + 0x140, (0xE0 - (width_c20 / 2)) + y_c20, 0, width_c20, 0, 0, 0);
            break;
        case 21:
            value_c21 = *(u16 *)(p2 + 0xCAA);
            x_c21 = *(s16 *)(p4 + 0xC9A);
            y_c21 = *(s16 *)(p4 + 0xC9C);
            res = SzMsg_LoadFont_Pipe(packet, 1, value_c21, 0, 0x16);
            res = RhText_SetTextureFlush(res);
            width_c21 = *(s32 *)((u8 *)SzMsg_GetInfo(1) + 0x10) + 0x34;
            SzMsg_Free(1);
            packet = lSzDuel_DrawDialog_Window_Pipe(res, -1, -1, value_c21, x_c21 + 0x140, (0xE0 - (width_c21 / 2)) + y_c21, 0, width_c21, 0, 0, 1);
            break;
        case 22:
            text1 = D_002BEF6F;
            y_c22 = *(s16 *)(p4 + 0xC9C);
            text2 = D_002BEF73;
            value_c22_c22 = *(u16 *)(p2 + 0xCAA);
            res = RhText_SetTextureFlush(SzMsg_LoadFont_Pipe(packet, 1, value_c22_c22, 0, 0x16));
            width_c22 = *(s32 *)((u8 *)SzMsg_GetInfo(1) + 0x10) + 0x3C;
            SzMsg_Free(1);
            packet = lSzDuel_DrawDialog_Window_Pipe(res, 2, -1, value_c22_c22, 0x140, (0xE0 - (width_c22 >> 1)) + y_c22, 0x15A, width_c22, 0, 0, 0);
            res = SzDuel_DrawWindow_Font_Pipe(packet, 0xEA, (width_c22 >> 1) + 0xBC + y_c22, 2, 3, func_0019BEF0(text1), text1, state[0xD35] != 0 ? 0 : (s32)D_002BE944);
            packet = SzDuel_DrawWindow_Font_Pipe(res, 0x196, (width_c22 >> 1) + 0xBC + y_c22, 2, 3, func_0019BEF0(text2), text2, state[0xD35] != 0 ? (s32)D_002BE944 : 0);
            break;
        case 23:
            packet = lSzDuel_OpenHandCursor_Pipe(packet, *(u16 *)(p2 + 0xCAA), *(s16 *)(p4 + 0xC9A), *(s16 *)(p4 + 0xC9C));
            break;
        }
    }
    SzMsg_Free(0);
    return packet;
}

static inline s32 abs_001B0CE0(s32 value) {
    if (value >= 0) {
        return value;
    }
    return -value;
}

s32 lSzDuel_DrawDialog_Window_Pipe(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                  s32 arg8, s32 arg9, s32 arg10) {
    extern u8 gSzDuel_Icon[];
    extern s32 func_001B3C80();
    extern s32 func_001B4780();
    extern s32 func_001B6F70(s32, s32, s32, s32, s32, s32, s8 *, s32);
    extern s32 func_001FE660(s32, s32, s32, s32, f32, f32, s32, void (*)(void));
    u8 *state;
    s32 frame;
    s32 flip;
    s32 card;
    s32 textW;
    s32 textH;
    s32 minW;
    s32 minH;
    s32 id;
    s32 *info;
    f32 scale;
    s32 nw;

    state = duelState.b;
    frame = (u32)func_001A8720() / 5;
    if (arg6 < 0) {
        flip = 1;
    } else {
        flip = 0;
    }
    card = (arg2 >= 0x8000) ? 1 : 0;
    scale = 1.0f;
    arg6 = abs_001B0CE0(arg6);
    if (card) {
        arg2 -= 0x8000;
    }
    if (arg8 > 0) {
        func_001B76E0(2, 3, arg8, (s8 *)arg9, &textW, &textH);
        textW += 0x18;
        textH += 0xC;
    } else {
        textH = 0;
        textW = 0;
    }
    if (arg3 >= 0) {
        arg0 = func_001FD680(arg0, 1, arg3, 0, 0x16);
        arg0 = func_0020F290(arg0);
        info = func_001FEAB0(1);
        if (flip) {
            if (arg6 - 0x18 < info[3]) {
                scale = (f32)(arg6 - 0x18) / (f32)info[3];
            }
            minW = arg6;
        } else {
            minW = ((info[3] > textW) ? info[3] : textW) + 0x18;
        }
        minH = info[4] + ((arg8 > 0) ? textH + 0x18 : 0xC) + 0xC;
    } else {
        minW = textW + 0x18;
        minH = (arg8 > 0) ? textH + 0x18 : 0xC;
    }
    if (card) {
        minH += 0x3C;
    } else if (arg2 >= 0) {
        minH += 0x8C;
    }
    if (arg10 != 0) {
        minH += 0x1C;
    }
    if (arg6 < minW) {
        arg6 = minW;
    }
    if (arg7 < minH) {
        arg7 = minH;
    }
    nw = -arg6;
    (void)nw; /* keeps the negation at its own statement, ahead of the frame call's argument copies, as in the original */
    id = func_001B4780(arg0, 0xD, -1, 1, arg4 - (arg6 >> 1) - 4, arg5, nw, -arg7, 1);
    if (arg8 > 0) {
        id = func_001B4780(id, arg1, -1, 0xB, arg4 - (textW >> 1), arg5 + 0xC, -textW, -textH, 1);
        id = func_001B6F70(id, arg4, arg5 + 0x14, 2, 3, arg8, (s8 *)arg9, 0);
    }
    if (card) {
        minW = arg4 - 0x18;
        minH = arg5 + ((arg8 > 0) ? textH + 0x18 : 0xC);
        id = func_001B7F90(id, arg2, minW, minH, 0x30, 0x30, *(s32 *)(state + 0xC58), 1);
        id = func_001B4780(id, -1, -1, 4, minW, minH, 3, 6, 1);
    } else if (arg2 >= 0) {
        id = func_001B7D60(id, arg2, arg4 - 0x40, arg5 + ((arg8 > 0) ? textH + 0x18 : 0xC), 0x80, 0x80,
                           *(s32 *)(state + 0xC58));
    }
    if (arg3 >= 0) {
        minW = arg4 - (s32)((f32)info[3] * scale / 2.0f);
        minH = arg5 + ((arg8 > 0) ? textH + 0x18 : 0x10);
        if (card) {
            minH += 0x3C;
        } else if (arg2 >= 0) {
            minH += 0x8C;
        }
        id = func_001FE660(id, 1, minW, minH, scale, 1.0f, 0, SzMsg_DrawRect_Pipe);
        func_001FEAF0(1);
    }
    if (arg10 != 0) {
        id = func_001B3C80(id, gSzDuel_Icon + (frame % 3 + 0xBE) * 10, arg4 + 0x6B8, arg5 + 0x704 + arg7,
                           0, 1, 0, 0, 1, 0, -1);
    }
    return id;
}

void SzDuel_DrawWindow(void) {
    RhBase_SetVifPacketArea(SzDuel_DrawWindow_Pipe(RhBase_GetVifPacketArea()));
}

typedef int DotrDrawWord;
struct DotrWindowUnit {
    unsigned char unknown_00[64];
    unsigned char x;
    unsigned char y;
    unsigned char unknown_42[2];
    unsigned char side;
    unsigned char place;
    unsigned char unknown_46[17];
    signed char unknown_57_bit_0 : 1;
    signed char unknown_57_bits_1_3 : 3;
    signed char unknown_57_bit_4 : 1;
    signed char unknown_57_bit_5 : 1;
    signed char unknown_57_bit_6 : 1;
    signed char unknown_57_bit_7 : 1;
};
struct DotrWindowSide {
    unsigned char unknown_000[826];
    unsigned short points;
    unsigned char player;
    unsigned char x;
    unsigned char y;
    unsigned char unknown_33f[2];
    unsigned char hand;
    unsigned char unknown_342[4];
    signed char unknown_346_bit_0 : 1;
    signed char unknown_346_high : 7;
    unsigned char unknown_347[9];
};
struct DotrWindowControl {
    struct DotrWindowSide sides[2];
    unsigned char unknown_6a0[40];
    struct DotrWindowUnit *unit_6c8;
    struct DotrWindowUnit *unit_6cc;
    unsigned char unknown_6d0[1416];
    unsigned int unknown_c58;
    unsigned char unknown_c5c[217];
    unsigned char unknown_d35;
    unsigned char unknown_d36[6];
    unsigned char side;
    unsigned char unknown_d3d;
    unsigned char slide;
    unsigned char slide2;
    unsigned char x;
    unsigned char y;
    unsigned char x2;
    unsigned char y2;
    unsigned char unknown_d44;
    unsigned char unknown_d45;
    unsigned char unknown_d46;
    unsigned char unknown_d47;
    unsigned char unknown_d48;
    unsigned char unknown_d49[6];
    unsigned char unknown_d4f;
    unsigned char unknown_d50[3];
    unsigned char unknown_d53;
    unsigned char unknown_d54;
    unsigned char unknown_d55[2];
    unsigned char unknown_d57;
    unsigned char unknown_d58[13];
    signed char unknown_d65_low : 4;
    signed char unknown_d65_bit_4 : 1;
    signed char unknown_d65_high : 3;
    signed char unknown_d66_low : 3;
    signed char unknown_d66_bit_3 : 1;
    signed char unknown_d66_bits_4_6 : 3;
    signed char unknown_d66_bit_7 : 1;
    signed char unknown_d67_bit_0 : 1;
    signed char unknown_d67_bit_1 : 1;
    signed char unknown_d67_bit_2 : 1;
    signed char unknown_d67_bit_3 : 1;
    signed char unknown_d67_bit_4 : 1;
    signed char unknown_d67_high : 3;
};
extern struct DotrWindowControl D_00317490_b;
extern DotrDrawWord func_001B3790_b(DotrDrawWord cursor, int colour, int field, float f, int x, int y);
extern struct DotrWindowUnit *func_001DF540_b(int a, int b);
extern struct DotrWindowUnit *func_001E36E0_b(int x, int y);
extern DotrDrawWord func_001B3100_b(DotrDrawWord cursor, int a1, int a2, int a3);
extern DotrDrawWord func_001B4780_b(DotrDrawWord cursor, int a1, int a2, int a3, int x, int y, int a6, int a7, long a8);
extern DotrDrawWord func_001B6EA0_b(DotrDrawWord cursor, int x, int y, int a, int flags, int width, int value);

int SzDuel_DrawWindow_Pipe(int cursor)
{
    extern DotrDrawWord lSzDuel_DrawWindow_CardInfo_Pipe(DotrDrawWord cursor, struct DotrWindowUnit *unit, int x, int y,
        unsigned char side, int a5, int a6, int a7, long a8, long a9);
    struct DotrWindowControl *g = &D_00317490_b;
    int off;
    struct DotrWindowUnit *unit;
    struct DotrWindowUnit *other;
    int x;
    int y;
    int adv;
    DotrDrawWord out;
    struct DotrWindowSide *side;
    long first = 1;
    int adv2;
    int closing = D_00317490_b.unknown_d67_bit_0;
    int step = 8;
    struct DotrWindowSide *s;
    int v;
    int a;
    int px;
    int c1;
    int c2;
    int py;

    if (D_00317490_b.unknown_d67_bit_1) {
        return cursor;
    }
    if (g->unknown_d67_bit_2 || g->unknown_d45 != 0 || g->unknown_d47 != 0 || g->unknown_d48 != 0) {
        if (!g->unknown_d65_bit_4) {
            closing = 1;
            step = 16;
        }
    }
    if (closing) {
        v = g->slide - step;
        g->slide = v > 0 ? v : 0;
    } else {
        v = g->slide + step;
        g->slide = v < 128 ? v : 128;
        if (g->slide == 128) {
            g->side = g->unknown_d54;
            g->unknown_d3d = g->unknown_d53;
            g->unknown_d67_bit_0 = g->unknown_d66_bit_7;
            s = &g->sides[g->side];
            g->x = s->x;
            g->y = s->y;
        }
    }
    if (g->slide == 128) {
        return cursor;
    }
    off = g->slide << 7 >> 7;
    side = &g->sides[g->side];
    SzDuel_SetWindowDefPrioZ(0xfffff8);
    cursor = func_001B3790_b(cursor, g->side, SzDuel_GetField(side->x, side->y), 100.0f, g->side != 0 ? 6 : 538,
                                                off + 336);
    cursor = SzDuel_StartWindowSessionWithPalette_Pipe(cursor, 0);
    cursor = lSzDuel_DrawWindow_PlayerInfo_Pipe(cursor, 0, 18, 20 - off, g->side == 0 ? 1 : 0);
    out = lSzDuel_DrawWindow_PlayerInfo_Pipe(cursor, 1, 440, 20 - off, g->side == 1 ? 1 : 0);
    if (g->unknown_d45 != 0 || g->unknown_d47 != 0) {
        other = g->unit_6cc;
        unit = func_001DF540_b(2, g->unknown_d4f + 1);
        if (g->unknown_d67_bit_3 || (!g->unknown_d67_bit_4 && g->unknown_d47 != 0)) {
            v = g->slide2 - 16;
            g->slide2 = v > 0 ? v : 0;
        } else {
            v = g->slide2 + 16;
            g->slide2 = v < 128 ? v : 128;
        }
        

        if (!(g->unknown_d57 != 81 && g->unknown_d57 != 82 && g->unknown_d57 != 83)) {
            other = g->unit_6c8;
        } else if (g->unknown_d35 == 83) {
            if (!(g->unknown_d57 != 32 && g->unknown_d57 != 33 && g->unknown_d57 != 34)) {
                other = g->unit_6c8;
            }
        }
        a = g->slide2;
        if (a != 0) {
            out = lSzDuel_DrawWindow_CardInfo_Pipe(out, unit, side->x, side->y, unit != 0 ? (int)unit->side : (int)g->side, 104,
                                                   368 - ((unsigned char)a << 6 >> 7) + off, -1, 6, 1);
            first = 0;
        }
        out = lSzDuel_DrawWindow_CardInfo_Pipe(out, other, side->x, side->y, other != 0 ? (int)other->side : (int)g->side, 104,
                                               off + 368, -1, 3, first);
    } else {
        x = -1;
        adv = 1;
        y = -1;
        adv2 = 1;
        if (g->unit_6c8 != 0 && g->unit_6c8->place < 11 && g->unit_6cc != 0 && g->unit_6cc->place < 11) {
            c1 = Ta_IsUnitControl(g->unit_6c8->side, g->unit_6c8->place);
            c2 = Ta_IsUnitControl(g->unit_6cc->side, g->unit_6cc->place);
            if (c1 != c2) {
            adv = Ta_IsVisualAttrAdv(g->unit_6c8->side, g->unit_6c8->place, g->unit_6cc->side, g->unit_6cc->place);
            if (adv < 0) {
                adv2 = adv;
            } else {
                adv2 = 2 - adv;
            }
            }
        }
        px = side->x;
        py = side->y;
        if (g->unit_6c8 != 0 && g->unit_6c8->place < 11 && g->unit_6c8->unknown_57_bit_6) {
            g->x = px = g->unit_6c8->x;
            g->y = py = g->unit_6c8->y;
            if (side->x != px || side->y != py) {
                x = side->x;
                y = side->y;
                if (g->slide2 == 0) {
                    g->x2 = x;
                    g->y2 = y;
                }
            }
        } else if (g->unknown_d57 == 24 || g->unknown_d57 == 62 || g->unknown_d57 == 48) {
            g->x = px;
            g->y = py;
        }
        if (g->x2 == x && g->y2 == y && func_001E36E0_b(x, y) != 0) {
            v = g->slide2 + 16;
            g->slide2 = v < 128 ? v : 128;
        } else {
            v = g->slide2 - 16;
            g->slide2 = v > 0 ? v : 0;
        }
        if (g->slide2 != 0) {
            unit = func_001E36E0_b(g->x2, g->y2);
            out = lSzDuel_DrawWindow_CardInfo_Pipe(out, unit, g->x2, g->y2, unit != 0 ? (int)unit->side : (int)g->side, 104,
                                                   368 - (g->slide2 << 6 >> 7) + off, adv2, 3, 1);
            first = 0;
        }
        unit = func_001E36E0_b(g->x, g->y);
        out = lSzDuel_DrawWindow_CardInfo_Pipe(out, unit, side->x, side->y, unit != 0 ? (int)unit->side : (int)g->side, 104, off + 368,
                                               adv, 3, first);
    }
    cursor = func_001B3100_b(out, g->side, g->side != 0 ? 538 : 6, off + 336);
    cursor = lSzDuel_DrawWindow_Field_Pipe(cursor, SzDuel_GetField(side->x, side->y), g->side != 0 ? 6 : 538, off + 336);
    cursor = func_001B4780_b(cursor, 5, 3, 4, 292, 16 - off, 4, 2, 1);
    cursor = func_001B6EA0_b(cursor, 320, 22 - off, 2, 34, 2, 100 - g->unknown_d3d);
    if (g->unknown_d44 != 0) {
        cursor = lSzDuel_DrawWindow_DualShock2_Pipe(cursor, 320, 72 - off, (unsigned char)((unsigned char)g->unknown_d44 << 7 >> 7));
    }
    if (g->unknown_d48 != 0) {
        y = g->unknown_d45 << 7 >> 7;
        y = 54 - off + (y - 128);
        cursor = lSzDuel_DrawWindow_Level_Pipe(cursor, 220, y);
        cursor = lSzDuel_DrawWindow_SummonCost_Pipe(cursor, 332, y);
    }
    SzDuel_SetWindowDefPrioZ(0xfffffc);
    cursor = SzDuel_DrawHandCursor_Pipe(cursor);
    SzMsg_Free(0);
    return cursor;
}

extern u8 gSzDuel_Icon[];
extern u8 D_00290882[];
extern u8 D_002908E6[];
extern u8 D_0029094A[];
extern u8 D_00290954[];
extern u8 D_00290A1C[];
extern s8 D_002BEF76[];

#pragma opt_propagation off

s32 lSzDuel_DrawWindow_PlayerInfo_Pipe(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 c0;
    s32 c1;
    s32 baseX;
    s32 screenX;
    s32 lowLevel;
    s32 playerOffset;
    extern s32 SzDuel_GetPlayer();
    extern s32 lSzDuel_DrawWindow_PicMini_Pipe();
    extern s32 lSzDuel_DrawWindow_Frame_Pipe();
    extern s32 SzDuel_DrawWindow_Digit_Pipe();
    extern s32 lSzDuel_DrawWindow_Board_Pipe();
    extern s32 lSzDuel_DrawWindow_Icon_Pipe();
    extern s32 SzDuel_DrawWindow_FontDigit_Pipe();
    extern s32 SzDuel_DrawWindow_Font_Pipe();
    u8 *playerData;
    u8 *data;
    s32 iconX;
    s32 valueX;
    s32 baseY;
    s32 iconY;
    s32 screenY;
    s32 rowX;
    s32 secondValueY;
    s32 lastX;
    s32 screenValueX;
    s32 numberX;
    s32 numberY;
    s32 screenRowX;
    s32 lastY;
    s32 lowerY;
    s32 hidden;
    s32 rowX2;

    data = duelState.b;
    playerData = duelState.b + arg1 * 0x350;
    baseY = arg3 + 3;
    baseX = arg2 + 3;
    screenY = baseY + 0x720;
    hidden = 1;
    screenX = baseX + 0x6C0;
    if (playerData[0x33C] < 100) {
        lowLevel = 1;
    } else {
        lowLevel = 0;
    }
    if (SzDuel_GetPlayer(0) < 100 && SzDuel_GetPlayer(1) < 100) {
        hidden = 0;
    } else {
        if (SzDuel_GetPlayer(data[0xD3C]) >= 100) {
            if (data[0xD3C] == arg1) {
                hidden = 0;
            }
        } else if (data[0xD3C] != arg1) {
            hidden = 0;
        }
    }
    arg0 = lSzDuel_DrawWindow_Frame_Pipe(arg0, arg1, arg1, 0, arg2 - 13, arg3 - 15, 37, 13, 1);
    iconX = arg2 + 3 + (arg1 != 0 ? 1 : 127);
    iconY = arg3 + 4;
    arg0 = lSzDuel_DrawWindow_PicMini_Pipe(arg0, arg1, iconX, iconY, 48, 48, *(s32 *)(data + 0xC58), arg4);
    arg0 = lSzDuel_DrawWindow_Frame_Pipe(arg0, -1, -1, 4, iconX, iconY, 3, 6, arg4);
    playerOffset = arg1 * 48;
    numberY = baseY + 6;
    rowX = baseX + playerOffset;
    numberX = rowX + 4;
    arg0 = lSzDuel_DrawWindow_Board_Pipe(arg0, arg1, numberX, numberY, 12, 1, -1);
    arg0 = SzDuel_DrawWindow_Digit_Pipe(arg0, numberX + 34, numberY + 2, 4, *(u16 *)(playerData + 0x33A), 0);
    iconX = screenX + (arg1 != 0 ? 1 : 127);
    arg0 = lSzDuel_DrawWindow_Icon_Pipe(arg0, (s32)(gSzDuel_Icon + (lowLevel + (arg1 * 2 + 185)) * 10), iconX, 48 + screenY, 0, 1, 0, 0, arg4, 0, -1);
    screenRowX = screenX + playerOffset;
    valueX = screenRowX + 8;
    iconX = screenRowX + 8;
    iconY = screenY + 12;
    arg0 = lSzDuel_DrawWindow_Icon_Pipe(arg0, D_00290A1C, iconX, iconY, 0, 1, 0, 0, 1, 0, -1);
    arg0 = lSzDuel_DrawWindow_Icon_Pipe(arg0, D_002908E6, valueX, screenY + 36, 0, 1, 0, 0, 1, 0, -1);
    rowX2 = rowX + 26;
    iconX = rowX + 26;
    lowerY = baseY + 37;
    if (hidden != 0) {
        arg0 = SzDuel_DrawWindow_Font_Pipe(arg0, iconX, lowerY, 0, 0, 2, D_002BEF76, 0);
    } else {
        arg0 = SzDuel_DrawWindow_FontDigit_Pipe(arg0, iconX, lowerY, 0, 0, 2, playerData[0x341]);
    }
    screenValueX = screenRowX + 64;
    iconX = screenRowX + 64;
    arg0 = lSzDuel_DrawWindow_Icon_Pipe(arg0, D_00290882, iconX, screenY + 36, 0, 1, 0, 0, 1, 0, -1);
    lastX = rowX + 82;
    lowerY = baseY + 37;
    arg0 = SzDuel_DrawWindow_FontDigit_Pipe(arg0, lastX, lowerY, 0, 0, 2, SzDuel_GetDeckCount(arg1));
    c0 = lSzDuel_DrawWindow_Icon_Pipe(arg0, D_0029094A, valueX, screenY + 52, 0, 1, 0, 0, 1, 0, -1);
    secondValueY = 53 + baseY;
    if (0 != hidden) {
        c0 = SzDuel_DrawWindow_Font_Pipe(c0, rowX2, secondValueY, 0, 0, 2, D_002BEF76, 0);
    } else {
        c0 = SzDuel_DrawWindow_FontDigit_Pipe(c0, rowX2, secondValueY, 0, 0, 2, SzDuel_GetUnitMonsterCount(arg1));
    }
    c1 = lSzDuel_DrawWindow_Icon_Pipe(c0, D_00290954, screenValueX, screenY + 52, 0, 1, 0, 0, 1, 0, -1);
    lastY = baseY + 53;
    if (hidden != 0) {
        c1 = SzDuel_DrawWindow_Font_Pipe(c1, lastX, lastY, 0, 0, 2, D_002BEF76, 0);
    } else {
        c1 = SzDuel_DrawWindow_FontDigit_Pipe(c1, lastX, lastY, 0, 0, 2, SzDuel_GetUnitSpellCount(arg1));
    }
    return c1;
}
#pragma opt_propagation reset

s32 lSzDuel_DrawWindow_Level_Pipe(s32 arg0, s32 arg1, s32 arg2) {
    extern s32 lSzDuel_DrawWindow_Icon_Pipe();
    extern s32 lSzDuel_DrawWindow_Board_Pipe();
    extern s32 SzDuel_DrawWindow_Digit_Pipe();
    extern s32 SzMsg_GetInfo();
    extern s32 SzDuel_GetUnitLevel();
    extern s32 SzDuel_GetPlayer();
    extern s32 SzMsg_DrawX_Pipe();
    extern u8 D_002901CA[];
    u8 *global;
    s32 x;
    s32 xResult;
    s32 y;
    s32 yResult;
    s32 xCoord;
    s32 result;
    s32 temp;
    s32 flag;
    s32 areaX;
    s32 areaY;

    global = duelState.b;
    x = arg1 + 3;
    y = arg2 + 3;
    areaX = x + 0x6C0;
    areaY = y + 0x720;
    flag = 0;
    if (SzDuel_GetPlayer(D_003181CC) < 0x20) {
        if (SzDuel_GetPlayer(global[0xD3C] ^ 1) >= 0x64) {
            flag = 1;
        }
    }

    arg0 = lSzDuel_DrawWindow_Frame_Pipe(arg0, global[0xD54], -1, 6, arg1, arg2, 8, 3, (s64) 1);
    result = lSzDuel_DrawWindow_Icon_Pipe(arg0, (s32) D_002901CA, areaX + 4, areaY + 3,
                           0, 1, 0, 0, 1, 0, -1);
    xCoord = x + 0x1E;
    yResult = y + 1;
    xResult = lSzDuel_DrawWindow_Board_Pipe(result, global[0xD54], xCoord, yResult, 3, 1, -1);
    if (flag != 0) {
        temp = RhText_SetTextureFlush(SzMsg_LoadFont_Pipe(xResult, 1, 0x1C, 0, 0x16));
        result = SzMsg_GetInfo(1);
        *(s32 *)(result + 0xC) = 0x2C;
        result = SzMsg_DrawX_Pipe(temp, 1, xCoord + 3, yResult + 2, 0, SzMsg_DrawRect_Pipe);
        SzMsg_Free(1);
    } else {
        temp = SzDuel_GetUnitLevel(2, global[0xD4F] + 1, 0);
        result = SzDuel_DrawWindow_Digit_Pipe(xResult, xCoord + 3, yResult + 2, 2, temp, 0);
    }
    return result;
}

s32 lSzDuel_DrawWindow_SummonCost_Pipe(s32 arg0, s32 arg1, s32 arg2) {
    extern s32 lSzDuel_DrawWindow_Icon_Pipe();
    extern s32 lSzDuel_DrawWindow_Board_Pipe();
    extern s32 SzDuel_DrawWindow_Digit_Pipe();
    extern s32 SzMsg_GetInfo();
    extern s32 SzDuel_GetUnitLevel();
    extern s32 SzDuel_GetPlayer();
    extern s32 SzMsg_DrawX_Pipe();
    u8 *global;
    s32 x;
    s32 xResult;
    s32 y;
    s32 yResult;
    s32 xCoord;
    s32 result;
    s32 temp;
    s32 flag;
    s32 areaX;
    s32 areaY;

    global = duelState.b;
    x = arg1 + 3;
    y = arg2 + 3;
    areaX = x + 0x6C0;
    areaY = y + 0x720;
    flag = 0;
    if (SzDuel_GetPlayer(D_003181CC) < 0x20) {
        if (SzDuel_GetPlayer(global[0xD3C] ^ 1) >= 0x64) {
            flag = 1;
        }
    }

    arg0 = lSzDuel_DrawWindow_Frame_Pipe(arg0, global[0xD54], -1, 6, arg1, arg2, 8, 3, (s64) 1);
    result = lSzDuel_DrawWindow_Icon_Pipe(arg0, (s32) D_002909B8, areaX + 4, areaY + 3,
                           0, 1, 0, 0, 1, 0, -1);
    xCoord = x + 0x1E;
    yResult = y + 1;
    xResult = lSzDuel_DrawWindow_Board_Pipe(result, global[0xD54], xCoord, yResult, 3, 1, -1);
    if (flag != 0) {
        temp = RhText_SetTextureFlush(SzMsg_LoadFont_Pipe(xResult, 1, 0x1C, 0, 0x16));
        result = SzMsg_GetInfo(1);
        *(s32 *)(result + 0xC) = 0x2C;
        result = SzMsg_DrawX_Pipe(temp, 1, xCoord + 3, yResult + 2, 0, SzMsg_DrawRect_Pipe);
        SzMsg_Free(1);
    } else {
        temp = SzDuel_GetUnitLevel(2, global[0xD4F] + 1, 0);
        result = SzDuel_DrawWindow_Digit_Pipe(xResult, xCoord + 3, yResult + 2, 2,
                             global[0xD4E] != 0 ? Ta_GetSummonCost() : temp, 0);
    }
    return result;
}

typedef struct Flags_001B22F0 {
    signed char bit0 : 1;
    signed char bit1 : 1;
    signed char bit2 : 1;
    signed char rest : 5;
} Flags_001B22F0;

typedef struct Card_001B22F0 {
    s32 active;
    u8 pad04[0x38];
    u16 id;
    u8 type;
    u8 attribute;
    u8 pad40[4];
    u8 owner;
    u8 state;
    u8 pad46[3];
    u8 count1;
    u8 count2;
    u8 pad4B[0xD];
    Flags_001B22F0 flags;
} Card_001B22F0;

#define MAX_001B22F0(a, b) ((a) > (b) ? (a) : (b))
#define MIN_001B22F0(a, b) ((a) < (b) ? (a) : (b))

#pragma opt_propagation off

s32 lSzDuel_DrawWindow_CardInfo_Pipe(s32 arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, long arg8, long arg9) {
    extern s32 lSzDuel_DrawWindow_Icon_Pipe();
    extern s32 lSzDuel_DrawWindow_Board_Pipe();
    extern s32 SzDuel_DrawWindow_Digit_Pipe();
    extern s32 SzData_GetRank();
    extern s32 SzMsg_DrawRatioX_Pipe(s32, s32, s32, s32, f32, f32, s32, void *);
    extern u8 gSzDuel_Attr[];
    extern u8 gSzDuel_Icon[];
    extern u8 D_002901D4[];
    extern u8 D_002901DE[];
    extern u8 D_002901E8[];
    extern u8 D_002901F2[];
    extern u8 D_002901FC[];
    extern u8 D_00290206[];
    extern u8 D_00290210[];
    extern u8 D_0029021A[];
    extern u8 D_00290224[];
    extern u8 D_0029022E[];
    extern u8 D_00290238[];
    extern u8 D_00290242[];
    extern u8 D_0029024C[];
    extern u8 D_002909A4[];
    extern u8 D_002909AE[];
    extern u8 D_002909C2[];
    extern u8 D_002909E0[];
    extern u8 D_002909EA[];
    u8 *globalBase;
    u8 *playerState;
    s32 x;
    s32 cardState;
    s32 cardType;
    s32 attribute;
    s32 cardIndex;
    s32 icon1;
    s32 icon3;
    s32 defenseBase;
    s32 effect;
    u8 *label;
    s32 enabled;
    s32 text2;
    s32 mode;
    f32 scale1;
    f32 scale2;
    f32 scale3;
    s32 y;
    s32 labelX;
    s32 labelY;
    s32 cur;
    s32 typeIcon;
    s32 owner;
    s32 hidden;
    s32 textX1;
    s32 textX2;
    s32 textY2;
    s32 textX3;
    s32 text3;
    s32 width1;
    s32 width2;
    s32 width3;
    s32 amount;
    s32 canUse;
    s32 count;
    s32 attackBase;
    s32 numX2;
    s32 attack;
    s32 defense;
    s32 iconY;
    s32 statX;
    s32 statY;
    s32 numX1;
    s32 numY2;
    s64 color;
    Card_001B22F0 *card;
    s32 iconX;

    globalBase = duelState.b;
    playerState = duelState.b + arg4 * 0x350;
    x = arg5 + 3;
    y = arg6 + 4;
    labelX = x + 0x6C0;
    mode = arg7;
    labelY = y + 0x720;
    card = arg1;
    cur = lSzDuel_DrawWindow_Frame_Pipe(arg0, arg4, (s32)arg9 != 0 ? 7 : -1, (s32)arg8, arg5, arg6, 0x33, 10, 1);
    if (card != NULL && card->active != 0) {
        owner = card->owner;
        cardState = card->state;
        cardType = (s32)card->type >> 5;
        typeIcon = card->type & 0x1F;
        attribute = SzDuel_Kind2Attr(cardType, card->attribute);
        if (cardType == 0) {
            label = gSzDuel_Icon + typeIcon * 10;
        } else {
            label = gSzDuel_Icon + (cardType + 0x14) * 10;
        }
        cardIndex = SzData_GetRank(arg4, card->id);
        icon1 = SzDuel_GetMsgName(card->id);
        if (cardType == 0) {
            typeIcon += 0x25;
        } else {
            typeIcon = cardType + 0x1E;
        }
        hidden = 0;
        icon3 = cardIndex + 0x52;
        if (SzGame_GetMenuNum(0x1E) != 0 && cardState > 0) {
            hidden = lSzDuel_IsUnitHide(card);
        }
        if (hidden != 0) {
            icon1 = 0x1C;
        }
        arg0 = SzMsg_LoadFont_Pipe(cur, 1, icon1, 0, 0x16);
        if (hidden != 0) {
            typeIcon = 0x1D;
        }
        arg0 = SzMsg_LoadFont_Pipe(arg0, 2, typeIcon, 0, 0x2C);
        if (hidden != 0) {
            icon3 = 0x51;
        }
        arg0 = SzMsg_LoadFont_Pipe(arg0, 3, icon3, 0, 0x42);
        arg0 = RhText_SetTextureFlush(arg0);
        textX1 = x + 2;
        typeIcon = lSzDuel_DrawWindow_Board_Pipe(arg0, arg4, textX1, y, 0x1B, 1, -1);
        width1 = *(s32 *)((u8 *)SzMsg_GetInfo(1) + 0xC);
        scale1 = (width1 < 229) ^ 1 ? 228.0f / (f32)width1 : 1.0f;
        arg0 = SzMsg_DrawRatioX_Pipe(typeIcon, 1, textX1 + 5, y + 2, scale1, 1.0f, 0, SzMsg_DrawRect_Pipe);
        arg0 = lSzDuel_DrawWindow_Icon_Pipe(arg0, label, labelX + 3, labelY + 0x1F, hidden, enabled = !hidden, hidden, 0, 1, 0, -1);
        textY2 = y + 0x1D;
        textX2 = x + 0x1D;
        text2 = lSzDuel_DrawWindow_Board_Pipe(arg0, arg4, textX2, textY2, 0xB, 1, -1);
        width2 = *(s32 *)((u8 *)SzMsg_GetInfo(2) + 0xC);
        scale2 = width2 > 100 ? 100.0f / (f32)width2 : 1.0f;
        arg0 = SzMsg_DrawRatioX_Pipe(text2, 2, textX2 + 5, textY2 + 2, scale2, 1.0f, 0, SzMsg_DrawRect_Pipe);
        iconX = labelX + 0x90;
        iconY = labelY + 0x1F;
        if (mode == 2) {
            color = 1;
        } else {
            color = mode == 0 ? 2LL : -1LL;
        }
        cur = lSzDuel_DrawWindow_Icon_Pipe(arg0, gSzDuel_Attr + attribute * 10, iconX, iconY, 1, enabled, 1, 0, 1, 0, color);
        if (cardType == 0) {
            if (cardState == 0) {
                arg0 = lSzDuel_DrawWindow_Emblem_Pipe(cur, x + 0xF1, y + 2, cardIndex, 1, 0);
                textX3 = x + 0x10C;
                text3 = lSzDuel_DrawWindow_Board_Pipe(arg0, arg4, textX3, y, 9, 1, -1);
                width3 = *(s32 *)((u8 *)SzMsg_GetInfo(3) + 0xC);
                scale3 = width3 > 88 ? 88.0f / (f32)width3 : 1.0f;
                cur = SzMsg_DrawRatioX_Pipe(text3, 3, textX3 + 3, y + 2, scale3, 1.0f, 0, SzMsg_DrawRect_Pipe);
                if (globalBase[0xD3C] == owner) {
                    amount = SzDuel_GetDeckCount(owner);
                    count = SzDuel_GetHandCount(owner);
                    if (((Flags_001B22F0 *)(playerState + 0x346))->bit0 != 0 && amount + count > 0) {
                        canUse = 0;
                        if ((amount > 0 && playerState[0x344] > 0) != 0) {
                            if (!(playerState[0x344] & 0x80)) {
                                canUse = 1;
                            }
                        }
                        iconX = labelX + 0x16E;
                        iconY = labelY + 2;
                        cur = lSzDuel_DrawWindow_Icon_Pipe(cur, D_002909B8, iconX, iconY, 0, 1, 0, 0, 1, 0, (canUse != 0 ? 1LL : -1LL));
                    }
                }
                statX = labelX + 0xF1;
                statY = labelY + 0x1F;
                if (SzDuel_GetUnitLeaderAbility2(card, 4, 0) != 0) {
                    cur = lSzDuel_DrawWindow_Icon_Pipe(cur, D_002901D4, statX, statY, 0, 1, 0, 0, 1, 0, -1);
                    statX += 0x19;
                }
                if (SzDuel_GetUnitLeaderAbility2(card, 5, 0) != 0) {
                    cur = lSzDuel_DrawWindow_Icon_Pipe(cur, D_002901DE, statX, statY, 0, 1, 0, 0, 1, 0, -1);
                    statX += 0x19;
                }
                if (SzDuel_GetUnitLeaderAbility2(card, 6, 0) != 0) {
                    cur = lSzDuel_DrawWindow_Icon_Pipe(cur, D_002901E8, statX, statY, 0, 1, 0, 0, 1, 0, -1);
                    statX += 0x19;
                }
                if (SzDuel_GetUnitLeaderAbility2(card, 7, 0) != 0) {
                    cur = lSzDuel_DrawWindow_Icon_Pipe(cur, D_002901F2, statX, statY, 0, 1, 0, 0, 1, 0, -1);
                    statX += 0x19;
                }
                if (SzDuel_GetUnitLeaderAbility2(card, 8, 0) != 0) {
                    cur = lSzDuel_DrawWindow_Icon_Pipe(cur, D_002901FC, statX, statY, 0, 1, 0, 0, 1, 0, -1);
                    statX += 0x19;
                }
                if (SzDuel_GetUnitLeaderAbility2(card, 9, 0) != 0) {
                    cur = lSzDuel_DrawWindow_Icon_Pipe(cur, D_00290206, statX, statY, 0, 1, 0, 0, 1, 0, -1);
                    statX += 0x19;
                }
                if (SzDuel_GetUnitLeaderAbility2(card, 10, 0) != 0) {
                    cur = lSzDuel_DrawWindow_Icon_Pipe(cur, D_00290210, statX, statY, 0, 1, 0, 0, 1, 0, -1);
                    statX += 0x19;
                }
                if (SzDuel_GetUnitLeaderAbility2(card, 11, 0) != 0) {
                    cur = lSzDuel_DrawWindow_Icon_Pipe(cur, D_0029021A, statX, statY, 0, 1, 0, 0, 1, 0, -1);
                    statX += 0x19;
                }
                if (SzDuel_GetUnitLeaderAbility2(card, 12, 0) != 0) {
                    cur = lSzDuel_DrawWindow_Icon_Pipe(cur, D_00290224, statX, statY, 0, 1, 0, 0, 1, 0, -1);
                    statX += 0x19;
                }
                if (SzDuel_GetUnitLeaderAbility2(card, 13, 0) != 0) {
                    cur = lSzDuel_DrawWindow_Icon_Pipe(cur, D_0029022E, statX, statY, 0, 1, 0, 0, 1, 0, -1);
                    statX += 0x19;
                }
                if (SzDuel_GetUnitLeaderAbility2(card, 14, 0) != 0) {
                    cur = lSzDuel_DrawWindow_Icon_Pipe(cur, D_00290238, statX, statY, 0, 1, 0, 0, 1, 0, -1);
                    statX += 0x19;
                }
                if (SzDuel_GetUnitLeaderAbility2(card, 15, 0) != 0) {
                    cur = lSzDuel_DrawWindow_Icon_Pipe(cur, D_00290242, statX, statY, 0, 1, 0, 0, 1, 0, -1);
                    statX += 0x19;
                }
                if (SzDuel_GetUnitLeaderAbility2(card, 16, 0) != 0) {
                    cur = lSzDuel_DrawWindow_Icon_Pipe(cur, D_0029024C, statX, statY, 0, 1, 0, 0, 1, 0, -1);
                }
            } else if (hidden == 0) {
                attackBase = Ta_GetParamOfs((s32)card, arg2, arg3, 1);
                defenseBase = Ta_GetParamOfs((s32)card, arg2, arg3, 0);
                attack = attackBase + SzDuel_GetUnitAP2(card, 0);
                defense = defenseBase + SzDuel_GetUnitDP2(card, 0);
                effect = CheckLandAgreement(SzDuel_GetField(arg2, arg3), card);
                attack = MIN_001B22F0(MAX_001B22F0(attack, 0), 9999);
                defense = MIN_001B22F0(MAX_001B22F0(defense, 0), 9999);
                if (SzDuel_GetUnitConstEffect2(card, 0) != NULL) {
                    iconX = labelX + 0xAD;
                    iconY = labelY + 0x1C;
                    cur = lSzDuel_DrawWindow_Icon_Pipe(cur, D_002909EA, iconX, iconY, 0, 1, 0, 0, 1, 0, -1);
                }
                iconX = labelX + 0xF2;
                iconY = labelY + 2;
                arg0 = lSzDuel_DrawWindow_Icon_Pipe(cur, D_002909A4, iconX, iconY, 0, 1, 0, 0, 1, 0, -1);
                numX1 = x + 0x10C;
                arg0 = lSzDuel_DrawWindow_Board_Pipe(arg0, arg4, numX1, y, 9, 1, -1);
                arg0 = SzDuel_DrawWindow_Digit_Pipe(arg0, numX1 + 6, y + 2, 4, attack, 0);
                iconX = labelX + 0xF2;
                iconY = labelY + 0x1F;
                arg0 = lSzDuel_DrawWindow_Icon_Pipe(arg0, D_002909AE, iconX, iconY, 0, 1, 0, 0, 1, 0, -1);
                numY2 = y + 0x1D;
                numX2 = x + 0x10C;
                arg0 = lSzDuel_DrawWindow_Board_Pipe(arg0, arg4, numX2, numY2, 9, 1, -1);
                cur = SzDuel_DrawWindow_Digit_Pipe(arg0, numX2 + 6, numY2 + 2, 4, defense, 0);
                if (effect != 0) {
                    iconX = labelX + 0x16E;
                    iconY = labelY + 2;
                    cur = lSzDuel_DrawWindow_Icon_Pipe(cur, gSzDuel_Icon + (effect + 0xED) * 10, iconX, iconY, 0, 1, 0, 0, 1, 0, -1);
                }
            }
            if (hidden == 0 && (GetMoveRev((s32)card, arg2, arg3) & 0xF) > 1U) {
                iconX = labelX + 0x18B;
                iconY = labelY + 2;
                cur = lSzDuel_DrawWindow_Icon_Pipe(cur, D_002909E0, iconX, iconY, 0, 1, 0, 0, 1, 0, -1);
            }
        }
        SzMsg_Free(1);
        SzMsg_Free(2);
        SzMsg_Free(3);
        if ((cardType != 0 || cardState != 0) && card->flags.bit2 == 0) {
            amount = card->count1;
            if (amount == 0xFF) {
                count = 0x7FFFFFFF;
            } else {
                canUse = card->count2;
                if (canUse == 0xFF) {
                    count = 0x7FFFFFFF;
                } else {
                    count = (u8)(canUse < amount ? amount : canUse);
                }
            }
            if (count != 0) {
                arg0 = lSzDuel_DrawWindow_Icon_Pipe(cur, D_002909C2, labelX + 0x16E, labelY + 0x1F, 0, 1, 0, 0, 1, 0, -1);
                y += 0x1D;
                labelX = x + 0x188;
                arg0 = lSzDuel_DrawWindow_Board_Pipe(arg0, arg4, labelX, y, 1, 1, -1);
                cur = SzDuel_DrawWindow_Digit_Pipe(arg0, labelX + 4, y + 2, 1, count, 0);
            }
        }
    }
    return cur;
}

#pragma opt_propagation reset

typedef struct {
    s8 bit0 : 1;
    s8 bit1 : 1;
    s8 bit2 : 1;
    s8 bit3 : 1;
    s8 bit4 : 1;
    s8 bit5 : 1;
    s8 bit6 : 1;
    s8 bit7 : 1;
} Flags_001B3100;

typedef struct {
    u8 pad[0x44];
    u8 x;
    u8 y;
    u8 pad46[0x11];
    Flags_001B3100 flags;
} Card_001B3100;

typedef struct {
    u8 pad[0x33D];
    u8 x;
    u8 y;
    u8 pad33F[7];
    Flags_001B3100 flags;
    u8 pad347[0x381];
    Card_001B3100 *card;
    Card_001B3100 *other;
    u8 pad6D0[0x66C];
    u8 player;
    u8 padD3D[0x29];
    Flags_001B3100 state;
} State_001B3100;

typedef struct {
    u16 graphic : 10;
    u16 x : 3;
    u16 y : 3;
    u16 text;
} Entry_001B3100;

typedef struct {
    u8 pad[0xC];
    s32 width;
} Text_001B3100;

extern u8 gSzDuel_Icon[];
extern Entry_001B3100 D_00291180[];
extern u8 D_003181E7;

s32 lSzDuel_DrawWindow_CommandGuide_Pipe(s32 arg0, s32 arg1, s64 arg2, s64 arg3) {
    extern s32 lSzDuel_DrawWindow_Icon_Pipe();
    extern s32 lSzDuel_DrawWindow_Frame_Pipe();
    extern void *SzMsg_GetInfo();
    extern s32 SzDuel_GetMapMovable();
    extern s32 SzMsg_DrawRatioX_Pipe(s32, s32, s32, s32, f32, f32, s32, void (*)(void));
    State_001B3100 *state;
    State_001B3100 *player;
    s32 choice;
    s32 x;
    s32 y;
    s32 renderX;
    s32 count;
    s32 text;
    Entry_001B3100 *entry;
    s32 value;
    s32 otherValue;
    Text_001B3100 *info;
    s32 graphic;
    s32 entryX;
    s32 entryY;
    f32 scale;

    state = (State_001B3100 *)duelState.b;
    player = (State_001B3100 *)(duelState.b + D_003181CC * 0x350);
    x = (s32)arg2 + 4;
    y = (s32)arg3 + 4;
    choice = -1;
    arg0 = lSzDuel_DrawWindow_Frame_Pipe(arg0, arg1, 2, 3, arg2, arg3, 9, 0x12, 1);
    switch (D_003181E7) {
    case 0x18:
        if (state->card != NULL) {
            value = Ta_IsUnitControl(state->card->x, state->card->y);
            if (state->player == value) {
                if (state->card->y == 0) {
                    value = SzDuel_GetDeckCount(state->player);
                    otherValue = SzDuel_GetHandCount(state->player);
                    if (player->flags.bit0 && value + otherValue > 0) {
                        if (state->card->flags.bit0) {
                            choice = 3;
                        } else {
                            choice = 1;
                        }
                    } else if (otherValue != 0) {
                        if (state->card->flags.bit0) {
                            choice = 4;
                        } else {
                            choice = 2;
                        }
                    } else {
                        if (state->card->flags.bit0) {
                            choice = 11;
                        } else {
                            choice = 10;
                        }
                    }
                } else {
                    if (state->card->flags.bit0) {
                        choice = 11;
                    } else {
                        choice = 10;
                    }
                }
            } else {
                value = 0;
                if (state->card->y > 0) {
                    value = Ta_IsUnitHide((s32)state->card, state->player);
                }
                choice = value == 0 ? 11 : 0;
            }
        } else {
            choice = 0;
        }
        break;
    case 0x1D:
        if (state->card->y == 0) {
            choice = 5;
            if (state->other != NULL && state->other != state->card) {
                value = Ta_IsUnitControl(state->other->x, state->other->y);
                if (state->player == value) {
                    choice = 6;
                }
            }
        } else {
            if (state->other != NULL) {
                if (state->other == state->card) {
                    if (state->card->flags.bit4) {
                        choice = 13;
                    } else {
                        choice = 12;
                    }
                } else {
                    value = Ta_IsUnitControl(state->other->x, state->other->y);
                    if (state->player == value) {
                        choice = 14;
                    } else {
                        choice = 15;
                    }
                }
            } else {
                choice = 5;
            }
        }
        break;
    case 0x3E:
        if (SzDuel_GetMapMovable(player->x, player->y) == 0) {
            choice = 7;
        }
        break;
    case 0x43:
        choice = 8;
        break;
    case 0x53:
        choice = 17;
        break;
    case 0x46:
        choice = 9;
        break;
    case 0x29:
    case 0x25:
        choice = 18;
        break;
    case 0x2D:
        if (state->state.bit3) {
            choice = 16;
        } else {
            choice = 17;
        }
        break;
    case 0x30:
        if (SzView_InqRequest(-1, -1) == NULL) {
            choice = 19;
        }
        break;
    case 0x63:
        choice = 20;
        break;
    }
    if (choice < 0) {
        return arg0;
    }
    renderX = x + 10;
    entry = D_00291180 + choice * 4;
    count = 0;
    do {
        graphic = entry->graphic;
        entryX = entry->x;
        entryY = entry->y;
        text = entry->text;
        if (graphic < 0x3FF) {
            arg0 = lSzDuel_DrawWindow_Icon_Pipe(arg0, gSzDuel_Icon + graphic * 10,
                                  renderX + 0x6C0 + entryX, y + 0x720 + entryY,
                                  0, 1, 0, 0, 1, 0, -1);
        }
        if (text < 0xFFFF) {
            arg0 = RhText_SetTextureFlush(SzMsg_LoadFont_Pipe(arg0, 1, text, 0, 0x16));
            info = SzMsg_GetInfo(1);
            if (info->width >= 0x2D) {
                scale = 44.0f / (f32)info->width;
            } else {
                scale = 1.0f;
            }
            arg0 = SzMsg_DrawRatioX_Pipe(arg0, 1, renderX + 0x1A, y, scale, 1.0f, 0,
                                  SzMsg_DrawRect_Pipe);
            SzMsg_Free(1);
        }
        count++;
        y += 0x16;
        entry++;
    } while (count < 4);
    return arg0;
}

s32 lSzDuel_DrawWindow_Field_Pipe(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    extern s32 lSzDuel_DrawWindow_Frame_Pipe();
    extern s32 SzMsg_DrawRatioX_Pipe(s32, s32, s32, s32, f32, f32, s32, void (*)(void));
    s32 id;
    s32 width;
    s32 result;
    f32 scale;

    scale = 1.0f;
    id = RhText_SetTextureFlush(SzMsg_LoadFont_Pipe(arg0, 1, arg1 + 0x47, 0, 0x16));
    id = lSzDuel_DrawWindow_Frame_Pipe(id, -1, 2, 3, arg2, arg3, 9, 0x12, 1);
    id = lSzDuel_DrawWindow_Frame_Pipe(id, 5, -1, 3, arg2, arg3 + 0x40, 9, 2, 1);
    width = ((s32 *)SzMsg_GetInfo(1))[3];
    if (width > 0x54) {
        scale = 84.0f / (f32)width;
    }
    result = SzMsg_DrawRatioX_Pipe(id, 1, (arg2 + 0x30) - (s32)((f32)(width >> 1) * scale), arg3 + 0x43,
                           scale, 1.0f, 0, SzMsg_DrawRect_Pipe);
    SzMsg_Free(1);
    return result;
}

typedef struct {
    u16 count;
    u16 flags;
    u32 padding;
    u64 registers;
} Tag_001B3790;

typedef struct {
    u8 pad[4];
    u8 b;
    u8 g;
    u8 r;
    u8 a;
} Source_001B3790;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Color_001B3790;

typedef struct {
    u64 u : 14;
    u64 pad0 : 2;
    u64 v : 14;
    u64 pad1 : 34;
} UV_001B3790;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Vertex_001B3790;

typedef struct {
    u64 tag[2];
    Color_001B3790 color;
    Vertex_001B3790 vertex0;
    Vertex_001B3790 vertex1;
    u64 end;
} Box_001B3790;

typedef struct {
    u64 tag[2];
    Color_001B3790 color;
    u64 uv0;
    Vertex_001B3790 vertex0;
    u64 uv1;
    Vertex_001B3790 vertex1;
    u64 test;
    s64 texture0;
    s64 texture1;
    u64 clamp;
} Sprite_001B3790;

typedef struct {
    u8 pad00[0x40];
    f32 eyeX;
    f32 eyeY;
    f32 eyeZ;
    u8 pad4C[4];
    f32 targetX;
    f32 targetY;
    f32 targetZ;
    u8 pad5C[0x24];
    s32 roll;
    u8 pad84[0xC];
} View_001B3790;

typedef union {
    __int128 q;
    s32 w[4];
} Params_001B3790;

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Vec_001B3790;

static inline void set_uv_001B3790(UV_001B3790 *p, s32 u, s32 v) {
    p->u = u;
    p->v = v;
}

s32 lSzDuel_DrawWindow_FieldPiece_Pipe(s32 arg0, s32 colorIndex, s32 card, s32 x, s32 y, f32 scale) {
    extern Source_001B3790 gSzDuel_aaicolRgba[];
    extern Params_001B3790 D_002912D0;
    extern s32 D_0031AB80;
    extern s32 RhBase_AssignRenderFrame(s32, s32, s32);
    u8 *state = duelState.b;
    Source_001B3790 *color = &gSzDuel_aaicolRgba[colorIndex];
    s32 left;
    s32 top;
    s32 width = 0x60;
    s32 height = 0x40;
    s32 id;
    s32 packet;
    View_001B3790 view;
    Params_001B3790 params;
    Box_001B3790 box __attribute__((aligned(8)));
    Sprite_001B3790 sprite __attribute__((aligned(8)));
    Vec_001B3790 rotation;
    Vec_001B3790 front;

    ((Tag_001B3790 *)box.tag)->flags = 6;
    ((Tag_001B3790 *)box.tag)->count = 3;
    ((Tag_001B3790 *)box.tag)->registers = 0x441;
    ((Tag_001B3790 *)box.tag)->padding = 0;
    left = x + 0x6C0;
    top = y + 0x720;
    box.color.r = color->r;
    box.color.g = color->g;
    box.color.b = color->b;
    box.color.a = 0x80;
    box.color.q = 1.0f;
    box.vertex0.x = (left + 2) << 4;
    box.vertex0.y = (top + 2) << 4;
    box.vertex0.z = D_003180E8;
    box.vertex0.fog = 0;
    box.vertex1.x = (left + width - 2) << 4;
    box.vertex1.y = (top + height) << 4;
    box.vertex1.z = D_003180E8;
    box.vertex1.fog = 0;
    id = ExSortPrim_Pipe(arg0, (s32)box.tag, 0, 0);
    if (SzModel_IsModelDisp(card + 0x4A) == 0) {
        return id;
    }
    left += 3;
    top += 3;
    width -= 6;
    height -= 3;
    ((Tag_001B3790 *)sprite.tag)->flags = 0x26;
    ((Tag_001B3790 *)sprite.tag)->count = 5;
    ((Tag_001B3790 *)sprite.tag)->registers = 0x42421;
    ((Tag_001B3790 *)sprite.tag)->padding = 0;
    ((Tag_001B3790 *)sprite.tag)->flags |= 0x800;
    ExAssignAlpha(sprite.tag, 0x44 | ((s64)0x80 << 32));
    sprite.color.r = 0xFF;
    sprite.color.g = 0xFF;
    sprite.color.b = 0xFF;
    sprite.color.a = 0x80;
    sprite.color.q = 1.0f;
    sprite.vertex0.z = *(s32 *)(state + 0xC58);
    sprite.vertex0.fog = 0;
    sprite.vertex1.z = *(s32 *)(state + 0xC58);
    sprite.vertex1.fog = 0;
    RhView_GetCurView(&view);
    if (RhView_PushStack() != 0) {
        params = D_002912D0;
        params.w[1] = D_0031AB80;
        RhBase_AssignRenderFrame(0, 0xA, 0x31);
        packet = (s32)RhBase_EnableRenderFrame((void *)id);
        packet = (s32)RhBase_ClearRenderFrame((u8 *)packet, 0);
        view.targetZ = func_001A6C60(view.targetX * view.targetX + view.targetZ * view.targetZ);
        view.targetX = 0.0f;
        RhGeom_NormalizeVector(&view.targetX);
        view.eyeX = -(view.targetX * scale);
        view.eyeY = -(view.targetY * scale) - 25.0f;
        view.eyeZ = -(view.targetZ * scale);
        view.roll = 0;
        RhView_Modify(&view);
        id = RhBase_SetZBufferMode(RhView_SendViewParameters(packet), 1);
        SzModel_GetIntensity(card + 0x4A, &rotation.x);
        front = rotation;
        front.z = 1.0f;
        SzModel_SetIntensity(card + 0x4A, &front.x);
        id = SzModel_DrawWithOutCalc_Pipe(id, card + 0x4A, 0, (s32)&params, 0, 0, 0);
        SzModel_SetIntensity(card + 0x4A, &rotation.x);
        id = RhBase_SetZBufferMode(id, 0);
        RhBase_GetTextureInfoForRender(&sprite.texture0, &sprite.texture1);
        id = RhText_SetTextureFlush((s32)RhBase_DisableRenderFrame((void *)id));
        set_uv_001B3790((UV_001B3790 *)&sprite.uv0, 0, 0);
        set_uv_001B3790((UV_001B3790 *)&sprite.uv1, 0x280 << 4, 0x1C0 << 4);
        sprite.vertex0.x = (left << 4) - 8;
        sprite.vertex0.y = (top << 4) - 8;
        sprite.vertex1.x = ((left + width) << 4) - 8;
        sprite.vertex1.y = ((top + height) << 4) - 8;
        RhView_PopStack();
        RhView_GetCurView(&view);
        RhView_Modify(&view);
        id = ExSortPrim_Pipe(RhView_SendViewParameters(id), (s32)&sprite, 0, 0);
        RhBase_FreeRenderFrame();
        D_0031AB80 += 0x200;
    }
    return id;
}

void lSzDuel_DrawWindow_Icon_Pipe(s32 arg0, s32 arg1, s32 arg2, s32 arg3,
                   s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                   s32 arg8, s32 arg9, s32 arg10) {
    extern void lSzDuel_DrawWindow_ExIcon_Pipe(s32, s32, s32, s32, s32, s32, s32, s32,
                              s64, s64, s64, s64, s64, s64);

    lSzDuel_DrawWindow_ExIcon_Pipe(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
                  0, 0, (s64) arg8, (s64) arg9, (s64) arg10, 0x80);
}

typedef struct Tag_001B3CC0 {
    u32 count : 16;
    u32 flags : 16;
    u32 reserved;
    u64 registers;
} Tag_001B3CC0;

typedef struct Color_001B3CC0 {
    u32 r : 8;
    u32 g : 8;
    u32 b : 8;
    u32 a : 8;
    f32 q;
} Color_001B3CC0;

typedef struct UV_001B3CC0 {
    u16 u : 14;
    u16 pad0 : 2;
    u16 v : 14;
    u16 pad1 : 2;
    u32 reserved;
} UV_001B3CC0;

typedef struct XYZ_001B3CC0 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} XYZ_001B3CC0;

typedef struct Sprite_001B3CC0 {
    u64 tag[2];
    Color_001B3CC0 color;
    u64 uv0;
    XYZ_001B3CC0 xyz0;
    u64 uv1;
    XYZ_001B3CC0 xyz1;
    u64 texture[4];
} Sprite_001B3CC0;

typedef struct Solid_001B3CC0 {
    u64 tag[2];
    Color_001B3CC0 color;
    XYZ_001B3CC0 xyz0;
    XYZ_001B3CC0 xyz1;
    u64 unused;
} Solid_001B3CC0;

typedef struct Texture_001B3CC0 {
    u8 index;
    u8 reserved;
    u16 x0;
    u16 y0;
    u16 x1;
    u16 y1;
} Texture_001B3CC0;

typedef struct State_001B3CC0 {
    u8 pad000[0x6A0];
    void *textures[16];
    u8 pad6E0[0x578];
    s32 depth;
} State_001B3CC0;

extern u8 D_002909F4[];
extern u16 D_00318118;

static inline void tag_001B3CC0(Tag_001B3CC0 *tag, s32 count, s32 flags, u64 registers) {
    tag->flags = flags;
    tag->count = count;
    tag->registers = registers;
    tag->reserved = 0;
}

static inline s32 abs_001B3CC0(s32 value) {
    if (value >= 0) {
        return value;
    }
    return -value;
}

static inline s32 intensity_001B3CC0(s32 bright) {
    if (bright != 0) {
        return 0x80;
    }
    return 0x30;
}

static inline s32 lower_001B3CC0(s32 value) {
    if (value > 0) {
        return value;
    }
    return 0;
}

static inline s32 upper_001B3CC0(s32 value) {
    if (value < 0x3FFF) {
        return value;
    }
    return 0x3FFF;
}

s32 lSzDuel_DrawWindow_ExIcon_Pipe(s32 packet, u16 *src, s32 x, s32 y,
                  s32 background, s32 image, s32 border, s32 shrink,
                  s32 flipX, s32 flipY, s32 bright, u8 *rgb,
                  s32 blend, u8 alpha) {
    Sprite_001B3CC0 sprite __attribute__((aligned(8)));
    Solid_001B3CC0 solid __attribute__((aligned(8)));
    State_001B3CC0 *graphics;
    s32 width;
    s32 height;

    graphics = (State_001B3CC0 *)duelState.b;
    width = abs_001B3CC0(src[3] - src[1]);
    height = abs_001B3CC0(src[4] - src[2]);
    if (shrink != 0) {
        width = (width * 3) >> 2;
        height = (height * 3) >> 2;
    }
    tag_001B3CC0((Tag_001B3CC0 *)sprite.tag, 5, 0x26, 0x42421);
    ((Tag_001B3CC0 *)sprite.tag)->flags |= 0x800;
    ExAssignAlpha(&sprite, 0x8000000044LL);
    sprite.color.r = sprite.color.g = sprite.color.b = intensity_001B3CC0(bright);
    sprite.color.a = alpha;
    sprite.color.q = 1.0f;
    sprite.xyz0.z = graphics->depth;
    sprite.xyz0.fog = 0;
    sprite.xyz1.z = graphics->depth;
    sprite.xyz1.fog = 0;
    tag_001B3CC0((Tag_001B3CC0 *)solid.tag, 3, 6, 0x441);
    solid.color.r = 0x80;
    solid.color.g = 0x80;
    solid.color.b = 0x80;
    solid.color.a = 0x80;
    solid.color.q = 1.0f;
    solid.xyz0.z = graphics->depth;
    solid.xyz0.fog = 0;
    solid.xyz1.z = graphics->depth;
    solid.xyz1.fog = 0;
    if (background != 0) {
        solid.color.r = solid.color.g = solid.color.b = 0;
        solid.xyz0.x = x * 16;
        solid.xyz0.y = y * 16;
        solid.xyz1.x = (x + width) * 16;
        solid.xyz1.y = (y + height) * 16;
        packet = ExSortPrim_Pipe(packet, (s32)&solid, 0, 0);
    }
    if (image != 0) {
        ExAssignTexture(&sprite, graphics->textures[((u8 *)src)[0]], 0);
        if (flipX != 0 && flipY != 0) {
            ((UV_001B3CC0 *)&sprite.uv0)->u = lower_001B3CC0(src[3] * 16 - 8);
            ((UV_001B3CC0 *)&sprite.uv0)->v = lower_001B3CC0(src[4] * 16 - 8);
            ((UV_001B3CC0 *)&sprite.uv1)->u = lower_001B3CC0(src[1] * 16 - 8);
            ((UV_001B3CC0 *)&sprite.uv1)->v = lower_001B3CC0(src[2] * 16 - 8);
        } else if (flipX != 0 && flipY == 0) {
            ((UV_001B3CC0 *)&sprite.uv0)->u = lower_001B3CC0(src[3] * 16 - 8);
            ((UV_001B3CC0 *)&sprite.uv0)->v = upper_001B3CC0(src[2] * 16 + 8);
            ((UV_001B3CC0 *)&sprite.uv1)->u = lower_001B3CC0(src[1] * 16 - 8);
            ((UV_001B3CC0 *)&sprite.uv1)->v = upper_001B3CC0(src[4] * 16 + 8);
        } else if (flipX == 0 && flipY != 0) {
            ((UV_001B3CC0 *)&sprite.uv0)->u = upper_001B3CC0(src[1] * 16 + 8);
            ((UV_001B3CC0 *)&sprite.uv0)->v = lower_001B3CC0(src[4] * 16 - 8);
            ((UV_001B3CC0 *)&sprite.uv1)->u = upper_001B3CC0(src[3] * 16 + 8);
            ((UV_001B3CC0 *)&sprite.uv1)->v = lower_001B3CC0(src[2] * 16 - 8);
        } else {
            ((UV_001B3CC0 *)&sprite.uv0)->u = upper_001B3CC0(src[1] * 16 + 8);
            ((UV_001B3CC0 *)&sprite.uv0)->v = upper_001B3CC0(src[2] * 16 + 8);
            ((UV_001B3CC0 *)&sprite.uv1)->u = upper_001B3CC0(src[3] * 16 + 8);
            ((UV_001B3CC0 *)&sprite.uv1)->v = upper_001B3CC0(src[4] * 16 + 8);
        }
        sprite.xyz0.x = x * 16;
        sprite.xyz0.y = y * 16;
        sprite.xyz1.x = (x + width) * 16;
        sprite.xyz1.y = (y + height) * 16;
        packet = ExSortPrim_Pipe(packet, (s32)&sprite, 0, 0);
    }
    if (border != 0) {
        packet = lSzDuel_DrawWindow_ExIcon_Pipe(packet, (u16 *)D_002909F4, x, y, 0, 1, 0, shrink,
                              0, 0, bright, NULL, -1, 0x80);
    }
    if (blend >= 0) {
        ExAssignAlpha(&solid, ExGetAlphaVal(blend));
        if (rgb != NULL) {
            solid.color.r = rgb[2];
            solid.color.g = rgb[1];
            solid.color.b = rgb[0];
        } else {
            solid.color.r = solid.color.g = solid.color.b = 0x80;
        }
        solid.color.a = D_00318118 >> 8;
        solid.xyz0.x = x * 16;
        solid.xyz0.y = y * 16;
        solid.xyz1.x = (x + width) * 16;
        solid.xyz1.y = (y + height) * 16;
        packet = ExSortPrim_Pipe(packet, (s32)&solid, 0, 0);
    }
    return packet;
}

extern u8 gSzDuel_Icon[];
extern u16 D_00290864[];

#pragma opt_propagation off

s32 lSzDuel_DrawWindow_Emblem_Pipe(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 result;

    result = arg0;
    if (arg3 > 0) {
        s32 parts;
        s32 px;
        s32 py;
        s32 width;
        s32 quotient;
        u16 *src;

        parts = arg4 ? 0xC : 0x10;
        if (arg3 > 0) {
            width = ((arg3 - 1) % 3) + 1;
        } else {
            width = 0;
        }
        quotient = 0;
        if (arg3 > 0) {
            quotient = (arg3 - 1) / 3;
        }
        src = (u16 *)(gSzDuel_Icon + (quotient + 0xC6) * 10);
        result = func_001B3CC0(arg0, src, arg1 + 0x6C0, arg2 + 0x720,
                               0, 1, 0, arg4, (arg5 != 0) ? 1 : 0, 0, 1, 0, -1, 0x80);
        if (width & 1) {
            px = arg1 + 0x6C0 + ((arg5 != 0) ? 0 : parts);
            result = func_001B3CC0(result, D_00290864, px, arg2 + 0x720,
                                   0, 1, 0, arg4, 0, 0, 1, 0, -1, 0x80);
        }
        if (width & 2) {
            px = arg1 + 0x6C0 + ((arg5 != 0) ? parts : 0);
            result = func_001B3CC0(result, D_00290864, px, arg2 + 0x720, 0, 1, 0, arg4, 0, 0, 1, 0, -1, 0x80);
            px = arg1 + 0x6C0 + ((arg5 != 0) ? 0 : parts);
            py = arg2 + 0x720 + parts;
            result = func_001B3CC0(result, D_00290864, px, py, 0, 1, 0, arg4, 0, 0, 1, 0, -1, 0x80);
        }
    }
    return result;
}


#pragma opt_propagation reset

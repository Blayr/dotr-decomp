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
    u8 *state = D_00317490.b;
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
    u8 *data = D_00317490.b;
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

    state = D_00317490.b;
    player = D_00317490.b + D_003181E4 * 0x350;
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

    base = D_00317490.b;
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
    Data_001AF140 *data = (Data_001AF140 *)D_00317490.b;

    if ((arg0 < 0) || (arg0 >= 8)) {
        return 0;
    }
    return data->entries[arg0];
}

INCLUDE_ASM("asm/nonmatchings/main_038", SzDuel_DrawHandCard_Pipe);

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

    state = D_00317490.b;
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

INCLUDE_ASM("asm/nonmatchings/main_038", SzDuel_DrawDialog_Pipe);

INCLUDE_ASM("asm/nonmatchings/main_038", lSzDuel_DrawDialog_Window_Pipe);

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
extern DotrDrawWord lSzDuel_DrawWindow_PlayerInfo_Pipe(DotrDrawWord cursor, int side, int x, int y, int active);
extern DotrDrawWord lSzDuel_DrawWindow_CardInfo_Pipe(DotrDrawWord cursor, struct DotrWindowUnit *unit, int x, int y,
                                                     unsigned char side, int a5, int a6, int a7, long a8, long a9);
extern struct DotrWindowUnit *func_001DF540_b(int a, int b);
extern struct DotrWindowUnit *func_001E36E0_b(int x, int y);
extern DotrDrawWord func_001B3100_b(DotrDrawWord cursor, int a1, int a2, int a3);
extern DotrDrawWord func_001B4780_b(DotrDrawWord cursor, int a1, int a2, int a3, int x, int y, int a6, int a7, long a8);
extern DotrDrawWord func_001B6EA0_b(DotrDrawWord cursor, int x, int y, int a, int flags, int width, int value);

int SzDuel_DrawWindow_Pipe(int cursor)
{
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

INCLUDE_ASM("asm/nonmatchings/main_038", lSzDuel_DrawWindow_PlayerInfo_Pipe);

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

    global = D_00317490.b;
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

    global = D_00317490.b;
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

INCLUDE_ASM("asm/nonmatchings/main_038", lSzDuel_DrawWindow_CardInfo_Pipe);

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

extern u8 D_00290080[];
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

    state = (State_001B3100 *)D_00317490.b;
    player = (State_001B3100 *)(D_00317490.b + D_003181CC * 0x350);
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
            arg0 = lSzDuel_DrawWindow_Icon_Pipe(arg0, D_00290080 + graphic * 10,
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
    extern Source_001B3790 D_002BE840[];
    extern Params_001B3790 D_002912D0;
    extern s32 D_0031AB80;
    extern s32 RhBase_AssignRenderFrame(s32, s32, s32);
    u8 *state = D_00317490.b;
    Source_001B3790 *color = &D_002BE840[colorIndex];
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

    graphics = (State_001B3CC0 *)D_00317490.b;
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

INCLUDE_ASM("asm/nonmatchings/main_038", lSzDuel_DrawWindow_Emblem_Pipe);

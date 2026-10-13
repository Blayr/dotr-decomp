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

void func_001ADD00(s32 arg0, s32 arg1, s32 arg2) {
    Vec_001ADD00 spA0;
    Vec_001ADD00 spB0;
    u8 *state = D_00317490;
    s32 var_s1;
    u8 *temp_s1_2;
    u8 *var_t2;
    u8 *var_t3;
    s32 var_t4;

    func_001DE970(0);
    func_001DEDB0(0);
    func_001DF070(0);
    func_001DE970(1);
    func_001DEDB0(1);
    func_001DF070(1);
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
        temp_s1 = func_002158B0(0);
        temp_s2 = func_002158B0(1);
        temp_s5 = func_002159D0(0, temp_s1);
        temp_s4 = func_002159D0(1, temp_s2);
        func_001CDA10();
        func_001CDD40();
        var_s3 = 0;
        do {
            func_001DFBB0(0, var_s3);
            func_001DFBB0(1, var_s3);
            var_s3 += 1;
        } while (var_s3 < 0xB);
        func_001E2FB0(0, 0, 1);
        func_001DF580(0, 3, 6, temp_s5, 1);
        func_001DF580(1, 3, 0, temp_s4, 1);
        func_001E1C10(0, 0, 0, 0);
        func_001E18A0(0, 0, 7);
        func_001E1C10(1, 0, 0, 0);
        func_001E18A0(1, 0, 7);
        var_s5 = 0;
        do {
            temp_s3 = func_00215A60(0, temp_s1, var_s5);
            temp_s4_2 = func_00215A60(1, temp_s2, var_s5);
            if (func_001A82E0(3) >= 0x3E8) {
                func_001DEA30(0, temp_s3);
            } else {
                func_001DEC00(0, var_s5, temp_s3);
            }
            if (func_001A82E0(4) >= 0x3E8) {
                func_001DEA30(1, temp_s4_2);
            } else {
                func_001DEC00(1, var_s5, temp_s4_2);
            }
            var_s5 += 1;
        } while (var_s5 < 0x28);
        var_s2 = 0;
        otherPlayer = arg1 ^ 1;
        do {
            func_00214BB0(otherPlayer, var_s2, func_00214D00(arg1, var_s2));
            var_s2 += 1;
        } while (var_s2 < 3);
        heading = (arg1 != 0) ? 0xC000 : 0x4000;
        spA0 = D_002910C0;
        spB0 = D_002910D0;
        spB0.f[1] = (3.1415927f * (f32) heading) / 32768.0f;
        func_001F9D80(0, &spA0);
        func_001FB360(0, spB0.f);
        var_s2_2 = 0;
        do {
            var_s1_2 = 0;
            do {
                func_001E23A0(var_s1_2, var_s2_2, -0x80);
                var_s1_2 += 1;
            } while (var_s1_2 < 7);
            var_s2_2 += 1;
        } while (var_s2_2 < 7);
        *(u8 *)(state + 0xD34) = 0;
        func_00217590(1, 0, 0);
    } else {
        s32 var_s2_3;
        for (var_s1 = 0; var_s1 < 7; var_s1++) {
            for (var_s2_3 = 0; var_s2_3 < 7; var_s2_3++) {
                func_001E23A0(var_s2_3, var_s1, 0);
            }
        }
        *(u8 *)(state + 0xD34) = 0x80;
    }
    *(u8 *)(state + 0xD37) = (u8) arg0;
    func_001DDE80((s32) *(u8 *)(state + 0xD37));
    func_001ADA80(arg2);
    func_00275D00(0, state);
    *(s32 *)(state + 0x330) = -1;
    if (*(s32 *)(state + 0x334) != 0) {
        func_00217B50(*(s32 *)(state + 0x334));
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
    func_00275D00(1, temp_s1_2);
    *(s32 *)(temp_s1_2 + 0x330) = -1;
    if (*(s32 *)(temp_s1_2 + 0x334) != 0) {
        func_00217B50(*(s32 *)(temp_s1_2 + 0x334));
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

void func_001AE520(void) {
    u8 *data = D_00317490;
    s32 var_a1;
    s32 var_s0;

    var_a1 = 0;
    do {
        data[var_a1 + 0xCB2] = 0x18;
        var_a1 += 1;
    } while (var_a1 < 4);
    var_s0 = 1;
    do {
        func_001DFBB0(0, var_s0);
        func_001DFBB0(1, var_s0);
        var_s0 += 1;
    } while (var_s0 < 0xB);
}

s32 func_001AE5A0(s32 arg0) {
    if (func_001F3130(0) != 0) {
        return func_001AE5F0(arg0);
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

s32 func_001AE5F0(s32 arg0) {
    extern s32 func_001DBFE0();
    extern void func_001E2FB0();
    extern void func_001E3060();
    extern s32 func_001E24E0();
    extern s32 func_001E3650();
    extern s32 func_001F6D20();
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

    state = D_00317490;
    player = D_00317490 + D_003181E4 * 0x350;
    mode = func_001AAF60(1);
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
    opacity = (u8)func_001F6D20();
    scale = (f32)opacity / 128.0f;
    func_001F6E80(0, scale);
    func_001F6E80(1, scale);
    func_001F6E80(8, scale);
    brightness = (u8)opacity;
    y = 0;
    do {
        x = 0;
        do {
            func_001E3650(x, y, brightness);
            x++;
        } while (x < 7);
        y++;
    } while (y < 7);

    if ((u64)mode < 2U) {
        func_001E2FB0(0, 0, 0);
    }
    if (mode == 1 && state[0xD57] >= 0x13) {
        s32 row;
        s32 col;
        u8 *tile;
        board = D_002910F8;
        range = D_00291100;
        background = D_00291108;
        tile = (u8 *)func_001E36E0(player[0x33D], player[0x33E]);
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
                    func_001E3060(col, row, 1, &own, 0);
                }
            }
            own.a = alpha;
            break;
        case 0x1D:
            func_001E2FB0(2, &background, 0);
            row = 0;
            do {
                col = 0;
                do {
                    s32 distance = func_001E24E0(col, row);
                    if (distance < 0xFF) {
                        range.a = distance <= state[0xD5A] ? 0xD0 : 0x40;
                        func_001E3060(col, row, 1, &range, 0);
                    }
                    col++;
                } while (col < 7);
                row++;
            } while (row < 7);
            for (row = 0; row < state[0xD59]; row++) {
                func_001E3060(state[0xCCA + row], state[0xCFB + row], 1, &special, 0);
            }
            break;
        case 0x21:
            break;
        case 0x3E:
            func_001E2FB0(2, &background, 0);
            row = 0;
            do {
                col = 0;
                do {
                    if (func_001E24E0(col, row) < 0xFF) {
                        func_001E3060(col, row, 1, &board, 0);
                    }
                    col++;
                } while (col < 7);
                row++;
            } while (row < 7);
            break;
        }
        func_001E3060(player[0x33D], player[0x33E], 1, color, 0);
        row = 0;
        do {
            col = 0;
            do {
                func_001E3230(col, row);
                col++;
            } while (col < 7);
            row++;
        } while (row < 7);
    }
    {
        u8 *tile;
        s32 id;
        tile = func_001DCD00(player[0x33D], player[0x33E]);
        id = tile[0x16] + 0x4A;
        if (func_001F1370(id) != 0 && color != NULL) {
            func_001E10F0(player[0x33D], player[0x33E], *(s16 *)(tile + 0x14), position);
            if (*(s16 *)(tile + 0x14) > 0) {
                arg0 = func_001DBFE0(arg0, position, NULL, 1);
            }
            arg0 = func_001EFA80(arg0, id, (s32)position, 0, 0, 0, 0);
            color->a = (alpha * tile[0x1A]) >> 7;
            func_001F2860(id, -1, color);
            arg0 = func_001EFA80(arg0, id, (s32)position, 0, 0, 0, 0x80FFFFF6);
            func_001F2860(id, -1, NULL);
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
            if (func_001F1370(id) != 0) {
                row = 0;
                do {
                    col = 0;
                    do {
                        tile = func_001DCD00(col, row);
                        if (tile[0x16] == kind) {
                            if (color == NULL || player[0x33D] != col || player[0x33E] != row) {
                                func_001E10F0(col, row, *(s16 *)(tile + 0x14), position);
                                if (*(s16 *)(tile + 0x14) > 0) {
                                    arg0 = func_001DBFE0(arg0, position, NULL, 1);
                                }
                                arg0 = func_001EFA80(arg0, id, (s32)position, 0, 0, 0, 0);
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
            if (func_001F1370(id) != 0) {
                arg0 = func_001EFA80(arg0, id, 0, 0, 0, 0, 0);
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
            if (func_001F1370(id) != 0) {
                offset.coord[1] -= 0x2000;
                arg0 = func_001EFA80(arg0, id, 0, (s32)&offset, 0, 0, 0);
                offset.coord[1] += 0x4000;
                arg0 = func_001EFA80(arg0, id, 0, (s32)&offset, 0, 0, 0);
            }
            x++;
        } while (x < 2);
    }
    return arg0;
}

void func_001AEE80(void) {
    func_00209D30(func_001AEEB0(func_00209D20()));
}

INCLUDE_ASM("asm/nonmatchings/main_038", func_001AEEB0);

s32 func_001AEFC0(s32 arg0) {
    return func_001AEFD0(arg0, 0);
}

s32 func_001AEFD0(s32 arg0, s32 arg1) {
    extern s32 *func_001FEAB0(s32);
    extern s32 func_00202E00(s32, s32);
    u8 *base;
    s32 addr;
    s32 length;
    s32 i;

    base = D_00317490;
    addr = func_00209E50();
    addr += func_00202E00(addr, 2);
    arg0 = func_001FD320(arg0, arg1, addr, &length);
    i = 0;
    addr += length;
    do {
        *(s32 *)(base + i * 4 + 0x6A0) = 0;
        i++;
    } while (i < 9);
    *(s32 *)(base + 0x6B8) = func_00202BF0(3, 6);
    *(s32 *)(base + 0x6BC) = func_00202BF0(3, 7);
    arg0 = func_00202B00(arg0, 3, addr, &length);
    addr += length;
    func_00202D60(3, -1);
    {
        s32 *info;

        arg0 = func_001FD680(arg0, 0, 0x15, 0, 0);
        info = func_001FEAB0(0);
        info[3] = 0x16;
        arg0 = func_0020F290(arg0);
    }
    *(s32 *)(base + 0xC7C) = addr;
    *(s32 *)(base + 0xC58) = 0xFFFFF8;
    func_001FD4B0(0xFFFFF8);
    return arg0;
}

s32 func_001AF110(s32 arg0) {
    func_001FEAF0(0);
    return arg0;
}

typedef struct {
    u8 pad[0x6A0];
    s32 entries[8];
} Data_001AF140;

s32 func_001AF140(s32 arg0) {
    Data_001AF140 *data = (Data_001AF140 *)D_00317490;

    if ((arg0 < 0) || (arg0 >= 8)) {
        return 0;
    }
    return data->entries[arg0];
}

INCLUDE_ASM("asm/nonmatchings/main_038", func_001AF180);

s32 func_001AF5C0(s32 arg0) {
    extern s32 func_001AAF60(s32);
    extern s32 func_001B4780();
    extern s32 func_001B3C80();
    extern s32 func_001B6EA0();
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

    state = D_00317490;
    mode = func_001AAF60(1);
    player = D_003181E4;
    count = func_001DF110(player);
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
        pos = (f32 *)func_001DF540(2, i + 1);
        if (pos != NULL) {
            pos = ((f32 **)pos)[1];
            if (pos != NULL) {
                x = (s32)pos[0] + 0x104;
                y = (s32)pos[1] + 0x8B;
                kind = func_001DF0C0(player, i);
                if (kind >= 0) {
                    if (state[0xD4F] == i) {
                        arg0 = func_001B4780(arg0, -1, -1, 8, x, y - 4, 0xC, 0x13, 1);
                    }
                    if ((kind & 0xFFF) != 0x3E7) {
                        kind = (kind & 0xF000) >> 12;
                        if (kind != 0) {
                            arg0 = func_001B3C80(arg0, D_002902A6, x + 0x6C0, y + 0x704, 1, 1, 0, 0, 1, 0, -1);
                            arg0 = func_001B6EA0(arg0, x + 0x10, y - 0x17, 0, 2, 1, kind);
                        }
                    }
                }
            }
        }
    }
    return arg0;
}

void func_001AF7B0(void) {
    func_00209D30(func_001AF7E0(func_00209D20()));
}

INCLUDE_ASM("asm/nonmatchings/main_038", func_001AF7E0);

INCLUDE_ASM("asm/nonmatchings/main_038", func_001B0CE0);

void func_001B1190(void) {
    func_00209D30(func_001B11C0(func_00209D20()));
}

INCLUDE_ASM("asm/nonmatchings/main_038", func_001B11C0);

INCLUDE_ASM("asm/nonmatchings/main_038", func_001B19F0);

INCLUDE_ASM("asm/nonmatchings/main_038", func_001B1EF0);

s32 func_001B20E0(s32 arg0, s32 arg1, s32 arg2) {
    extern s32 func_001B3C80();
    extern s32 func_001B65E0();
    extern s32 func_001B6C90();
    extern s32 func_001FEAB0();
    extern s32 func_001E08F0();
    extern s32 func_001DE4E0();
    extern s32 func_001FE7D0();
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

    global = D_00317490;
    x = arg1 + 3;
    y = arg2 + 3;
    areaX = x + 0x6C0;
    areaY = y + 0x720;
    flag = 0;
    if (func_001DE4E0(D_003181CC) < 0x20) {
        if (func_001DE4E0(global[0xD3C] ^ 1) >= 0x64) {
            flag = 1;
        }
    }

    arg0 = func_001B4780(arg0, global[0xD54], -1, 6, arg1, arg2, 8, 3, (s64) 1);
    result = func_001B3C80(arg0, (s32) D_002909B8, areaX + 4, areaY + 3,
                           0, 1, 0, 0, 1, 0, -1);
    xCoord = x + 0x1E;
    yResult = y + 1;
    xResult = func_001B65E0(result, global[0xD54], xCoord, yResult, 3, 1, -1);
    if (flag != 0) {
        temp = func_0020F290(func_001FD680(xResult, 1, 0x1C, 0, 0x16));
        result = func_001FEAB0(1);
        *(s32 *)(result + 0xC) = 0x2C;
        result = func_001FE7D0(temp, 1, xCoord + 3, yResult + 2, 0, func_001FDFE0);
        func_001FEAF0(1);
    } else {
        temp = func_001E08F0(2, global[0xD4F] + 1, 0);
        result = func_001B6C90(xResult, xCoord + 3, yResult + 2, 2,
                             global[0xD4E] != 0 ? func_0026E950() : temp, 0);
    }
    return result;
}

INCLUDE_ASM("asm/nonmatchings/main_038", func_001B22F0);

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

s32 func_001B3100(s32 arg0, s32 arg1, s64 arg2, s64 arg3) {
    extern s32 func_001B3C80();
    extern s32 func_001B4780();
    extern void *func_001FEAB0();
    extern s32 func_001E24E0();
    extern s32 func_001FE660(s32, s32, s32, s32, f32, f32, s32, void (*)(void));
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

    state = (State_001B3100 *)D_00317490;
    player = (State_001B3100 *)(D_00317490 + D_003181CC * 0x350);
    x = (s32)arg2 + 4;
    y = (s32)arg3 + 4;
    choice = -1;
    arg0 = func_001B4780(arg0, arg1, 2, 3, arg2, arg3, 9, 0x12, 1);
    switch (D_003181E7) {
    case 0x18:
        if (state->card != NULL) {
            value = func_00250360(state->card->x, state->card->y);
            if (state->player == value) {
                if (state->card->y == 0) {
                    value = func_001DE9C0(state->player);
                    otherValue = func_001DF110(state->player);
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
                    value = func_00267380((s32)state->card, state->player);
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
                value = func_00250360(state->other->x, state->other->y);
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
                    value = func_00250360(state->other->x, state->other->y);
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
        if (func_001E24E0(player->x, player->y) == 0) {
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
        if (func_001FA6F0(-1, -1) == NULL) {
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
            arg0 = func_001B3C80(arg0, D_00290080 + graphic * 10,
                                  renderX + 0x6C0 + entryX, y + 0x720 + entryY,
                                  0, 1, 0, 0, 1, 0, -1);
        }
        if (text < 0xFFFF) {
            arg0 = func_0020F290(func_001FD680(arg0, 1, text, 0, 0x16));
            info = func_001FEAB0(1);
            if (info->width >= 0x2D) {
                scale = 44.0f / (f32)info->width;
            } else {
                scale = 1.0f;
            }
            arg0 = func_001FE660(arg0, 1, renderX + 0x1A, y, scale, 1.0f, 0,
                                  func_001FDFE0);
            func_001FEAF0(1);
        }
        count++;
        y += 0x16;
        entry++;
    } while (count < 4);
    return arg0;
}

s32 func_001B3640(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    extern s32 func_001B4780();
    extern s32 func_001FE660(s32, s32, s32, s32, f32, f32, s32, void (*)(void));
    s32 id;
    s32 width;
    s32 result;
    f32 scale;

    scale = 1.0f;
    id = func_0020F290(func_001FD680(arg0, 1, arg1 + 0x47, 0, 0x16));
    id = func_001B4780(id, -1, 2, 3, arg2, arg3, 9, 0x12, 1);
    id = func_001B4780(id, 5, -1, 3, arg2, arg3 + 0x40, 9, 2, 1);
    width = ((s32 *)func_001FEAB0(1))[3];
    if (width > 0x54) {
        scale = 84.0f / (f32)width;
    }
    result = func_001FE660(id, 1, (arg2 + 0x30) - (s32)((f32)(width >> 1) * scale), arg3 + 0x43,
                           scale, 1.0f, 0, func_001FDFE0);
    func_001FEAF0(1);
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

s32 func_001B3790(s32 arg0, s32 colorIndex, s32 card, s32 x, s32 y, f32 scale) {
    extern Source_001B3790 D_002BE840[];
    extern Params_001B3790 D_002912D0;
    extern s32 D_0031AB80;
    extern s32 func_0020A470(s32, s32, s32);
    u8 *state = D_00317490;
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
    id = func_00207650(arg0, (s32)box.tag, 0, 0);
    if (func_001F1370(card + 0x4A) == 0) {
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
    func_002086D0(sprite.tag, 0x44 | ((s64)0x80 << 32));
    sprite.color.r = 0xFF;
    sprite.color.g = 0xFF;
    sprite.color.b = 0xFF;
    sprite.color.a = 0x80;
    sprite.color.q = 1.0f;
    sprite.vertex0.z = *(s32 *)(state + 0xC58);
    sprite.vertex0.fog = 0;
    sprite.vertex1.z = *(s32 *)(state + 0xC58);
    sprite.vertex1.fog = 0;
    func_0020DEF0(&view);
    if (func_0020E460() != 0) {
        params = D_002912D0;
        params.w[1] = D_0031AB80;
        func_0020A470(0, 0xA, 0x31);
        packet = (s32)func_0020A610((void *)id);
        packet = (s32)func_0020A870((u8 *)packet, 0);
        view.targetZ = func_001A6C60(view.targetX * view.targetX + view.targetZ * view.targetZ);
        view.targetX = 0.0f;
        func_0020D070(&view.targetX);
        view.eyeX = -(view.targetX * scale);
        view.eyeY = -(view.targetY * scale) - 25.0f;
        view.eyeZ = -(view.targetZ * scale);
        view.roll = 0;
        func_0020E360(&view);
        id = func_0020A0B0(func_0020EC60(packet), 1);
        func_001F1E10(card + 0x4A, &rotation.x);
        front = rotation;
        front.z = 1.0f;
        func_001F1EE0(card + 0x4A, &front.x);
        id = func_001EFA80(id, card + 0x4A, 0, (s32)&params, 0, 0, 0);
        func_001F1EE0(card + 0x4A, &rotation.x);
        id = func_0020A0B0(id, 0);
        func_0020AA30(&sprite.texture0, &sprite.texture1);
        id = func_0020F290((s32)func_0020A760((void *)id));
        set_uv_001B3790((UV_001B3790 *)&sprite.uv0, 0, 0);
        set_uv_001B3790((UV_001B3790 *)&sprite.uv1, 0x280 << 4, 0x1C0 << 4);
        sprite.vertex0.x = (left << 4) - 8;
        sprite.vertex0.y = (top << 4) - 8;
        sprite.vertex1.x = ((left + width) << 4) - 8;
        sprite.vertex1.y = ((top + height) << 4) - 8;
        func_0020E4F0();
        func_0020DEF0(&view);
        func_0020E360(&view);
        id = func_00207650(func_0020EC60(id), (s32)&sprite, 0, 0);
        func_0020A9E0();
        D_0031AB80 += 0x200;
    }
    return id;
}

void func_001B3C80(s32 arg0, s32 arg1, s32 arg2, s32 arg3,
                   s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                   s32 arg8, s32 arg9, s32 arg10) {
    extern void func_001B3CC0(s32, s32, s32, s32, s32, s32, s32, s32,
                              s64, s64, s64, s64, s64, s64);

    func_001B3CC0(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
                  0, 0, (s64) arg8, (s64) arg9, (s64) arg10, 0x80);
}

INCLUDE_ASM("asm/nonmatchings/main_038", func_001B3CC0);

INCLUDE_ASM("asm/nonmatchings/main_038", func_001B4540);

#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_064", func_00228150);

INCLUDE_ASM("asm/nonmatchings/main_064", func_00228460);

INCLUDE_ASM("asm/nonmatchings/main_064", func_00228660);

void func_00228940(s16 arg0, s16 arg1) {
    *(s16 *)0x01ED01A4 = arg0;
    *(s16 *)0x01ED01B2 = arg1;
    *(s16 *)0x01ED01B0 = 0;
    *(s16 *)0x01ED01A6 = 0;
    *(s8 *)0x01ED01B4 = 1;
}

s32 func_00228970(void) {
    s16 temp_v1;
    s16 temp_v1_2;

    if (*(s16 *)0x01ED0060 == 0) {
        *(f32 *)0x01ED0050 = *(f32 *)0x01ED0040;
        *(f32 *)0x01ED0058 = *(f32 *)0x01ED0048;
    }
    *(s16 *)0x01ED0060 += 0x10;
    if (*(s16 *)0x01ED0060 >= 0x100) {
        *(s16 *)0x01ED0060 = 0x100;
    }
    temp_v1 = *(s16 *)0x01ED0060;
    *(f32 *)0x01ED0040 = ((*(f32 *)0x01ED0050 * (f32)(0x100 - temp_v1)) / 256.0f) + ((*(f32 *)0x01ED01B8 * (f32)temp_v1) / 256.0f);
    temp_v1_2 = *(s16 *)0x01ED0060;
    *(f32 *)0x01ED0048 = ((*(f32 *)0x01ED0058 * (f32)(0x100 - temp_v1_2)) / 256.0f) + ((*(f32 *)0x01ED01C0 * (f32)temp_v1_2) / 256.0f);
    if (*(s16 *)0x01ED0060 >= 0x100) {
        *(s16 *)0x01ED0060 = 0;
        *(f32 *)0x01ED0050 = *(f32 *)0x01ED0040;
        *(f32 *)0x01ED0058 = *(f32 *)0x01ED0048;
        *(s8 *)0x01ED5372 = 0;
        *(s8 *)0x01ED5375 = 0;
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_064", func_00228AD0);

INCLUDE_ASM("asm/nonmatchings/main_064", func_00228F50);

typedef struct State_00229140 {
    s8 pad0[3];
    s8 levels[17];
    u8 pad14[0xAE];
    s16 fieldC2;
    u8 padC4[2];
    s8 selection;
    s8 padC7;
    s8 previous;
    s8 snapshot;
} State_00229140;

extern f32 D_00298BA0[];
extern f32 D_00298BA8[];

s32 func_00229140(s32 arg0, s32 arg1, s16 arg2) {
    State_00229140 *state = (State_00229140 *)&D_00299E10;
    f32 startX;
    f32 startZ;
    s32 index;

    if ((*(s8 *)0x01ED5372 == 0 &&
         arg2 <= *(s16 *)0x01ED536C &&
         *(s8 *)0x01ED537B != 0) ||
        state->levels[state->selection] >= 2 ||
        (state->selection == 15 && state->levels[16] == 0)) {
        switch (*(s8 *)0x01ED5373) {
        case 1:
            state->previous = state->selection;
            *(f32 *)0x01ED0050 = *(f32 *)0x01ED0040;
            *(f32 *)0x01ED0058 = *(f32 *)0x01ED0048;
            *(s16 *)0x01ED0076 = *(s16 *)0x01ED0000;
            *(s16 *)0x01ED0078 = *(s16 *)0x01ED0002;
            *(s16 *)0x01ED0060 = 0;
            *(s8 *)0x01ED5373 += 1;
            *(s16 *)0x01ED01DA = 0;
            *(s16 *)0x01ED01DE = 0;
            *(s16 *)0x01ED01D8 = 1;
            state->snapshot = *(s8 *)0x01ED53C2;
            break;
        case 2:
            *(s16 *)0x01ED0060 += 8;
            startX = *(f32 *)0x01ED0050;
            *(f32 *)0x01ED0040 = startX +
                ((f32)*(s16 *)0x01ED0060 *
                 (D_00298BA0[state->selection * 13] - startX)) / 256.0f;
            startZ = *(f32 *)0x01ED0058;
            *(f32 *)0x01ED0048 = startZ +
                ((f32)*(s16 *)0x01ED0060 *
                 (D_00298BA8[state->selection * 13] - startZ)) / 256.0f;
            index = state->selection * 13;
            if (*(f32 *)0x01ED0040 == D_00298BA0[index]) {
                if (*(f32 *)0x01ED0048 == D_00298BA8[index]) {
                    *(s16 *)0x01ED0060 = 256;
                }
            }
            if (*(s16 *)0x01ED0060 >= 256) {
                *(s16 *)0x01ED0060 = 0;
                *(f32 *)0x01ED0040 = D_00298BA0[state->selection * 13];
                *(f32 *)0x01ED0048 = D_00298BA8[state->selection * 13];
                *(s8 *)0x01ED5373 = 3;
                if (state->selection == 15 && state->levels[16] == 0) {
                    state->fieldC2 = 0x2F08;
                }
                return 1;
            }
            break;
        case 3:
            if (*(s8 *)0x01ED53A0 <= 0 && *(s16 *)0x01ED01D8 == 3) {
                func_002336F0();
            }
            break;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_064", func_002294B0);

INCLUDE_ASM("asm/nonmatchings/main_064", func_002297C0);

INCLUDE_ASM("asm/nonmatchings/main_064", func_0022A020);

INCLUDE_ASM("asm/nonmatchings/main_064", func_0022A140);

INCLUDE_ASM("asm/nonmatchings/main_064", func_0022A710);

INCLUDE_ASM("asm/nonmatchings/main_064", func_0022B060);

s32 func_0022C3C0(s32 arg0) {
    switch (arg0) {
    case 0:
        *(s16 *)0x01ED547C -= 4;
        if (*(s16 *)0x01ED547C <= 0) {
            *(s16 *)0x01ED547C = 0;
            return 1;
        }
        break;
    case 1:
        *(s16 *)0x01ED547C += 4;
        if (*(s16 *)0x01ED547C >= 0x80) {
            *(s16 *)0x01ED547C = 0x80;
            return 1;
        }
        break;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_064", func_0022C450);

INCLUDE_ASM("asm/nonmatchings/main_064", func_0022C570);

s32 func_0022CC40(s32 arg0, s16 arg1, s16 arg2, s16 arg3) {
    extern s32 func_001A22C0(f32);
    extern s16 D_00299066[][16][38];
    f32 (*xData)[16][129] = (f32 (*)[16][129])0x01ED022C;
    f32 (*zData)[16][129] = (f32 (*)[16][129])0x01ED032C;
    s16 (*countData)[16][258] = (s16 (*)[16][258])0x01ED042C;
    s32 rotation[3];
    f32 dx1;
    f32 dz1;
    f32 dx0;
    f32 dz0;
    s16 point;
    f32 *x;
    f32 *z;
    s32 angle;

    point = *(s16 *)0x01ED01B0;
    dx1 = xData[arg1][arg2][point + 2] - xData[arg1][arg2][point + 1];
    dz1 = zData[arg1][arg2][point + 2] - zData[arg1][arg2][point + 1];
    func_001A6C18(dx1, dz1);
    dx0 = xData[arg1][arg2][point + 1] - xData[arg1][arg2][point];
    dz0 = zData[arg1][arg2][point + 1] - zData[arg1][arg2][point];
    x = &xData[arg1][arg2][point];
    z = &zData[arg1][arg2][point];
    angle = func_001A22C0(65536.0f * (func_001A6C18(dx0, dz0) / 6.2831855f)) % 65536;
    *(f32 *)0x01ED01B8 = *x + dx0 * (f32)*(s16 *)0x01ED01A6 / 1024.0f;
    *(f32 *)0x01ED01BC = D_00298BA4;
    *(f32 *)0x01ED01C0 = *z + dz0 * (f32)*(s16 *)0x01ED01A6 / 1024.0f;
    if (countData[arg1][arg2][0] <= point) {
        s32 previousAngle = func_001A22C0(65536.0f * (func_001A6C18(
            *x - xData[arg1][arg2][point - 1],
            *z - zData[arg1][arg2][point - 1]) / 6.2831855f)) % 65536;
        rotation[0] = 0;
        rotation[1] = previousAngle;
        rotation[2] = 0;
    } else if (countData[arg1][arg2][0] - 1 <= point) {
        rotation[0] = 0;
        rotation[1] = angle;
        rotation[2] = 0;
    } else {
        s16 progress = *(s16 *)0x01ED01A6;
        rotation[0] = 0;
        rotation[1] = func_001A22C0(65536.0f * (func_001A6C18(
            dx0 * (f32)(1024 - progress) / 1024.0f
                + dx1 * (f32)progress / 1024.0f,
            dz0 * (f32)(1024 - progress) / 1024.0f
                + dz1 * (f32)progress / 1024.0f) / 6.2831855f)) % 65536;
        rotation[2] = 0;
    }
    *(s32 *)0x01ED01A8 = rotation[1];
    if (*(s8 *)0x01ED01B4 != 0) {
        arg0 = func_001EE4B0(arg0, arg3 + 0x22, 0x01ED01B8, (s32)rotation, 0, 0, 0);
    }
    if (*(s16 *)0x01ED01A4 > 0) {
        if (*(s16 *)0x01ED01A6 < 1024 && *(s16 *)0x01ED01B0 < countData[arg1][arg2][0]) {
            if (*(s16 *)0x01ED01A4 == 1) {
                func_001F48F0(0, 0x193, 0, 0, 0);
                *(s16 *)0x01ED01A4 = 2;
            }
            if (*(s16 *)0x01ED01A4 == 2) {
                *(s16 *)0x01ED01A6 += 256;
                if (*(s16 *)0x01ED01A6 >= 1024) {
                    *(s16 *)0x01ED01B0 += 1;
                    if (countData[arg1][arg2][0] <= *(s16 *)0x01ED01B0) {
                        *(s16 *)0x01ED01A6 = 0;
                        *(s16 *)0x01ED01A4 = 3;
                        *(s16 *)0x01ED01B0 = countData[arg1][arg2][0];
                        ((s16 *)0x01ED52EC)[D_00299066[arg1][arg2][0]] = 1;
                    } else {
                        *(s16 *)0x01ED01A6 = 0;
                    }
                }
            }
        }
    }
    return arg0;
}

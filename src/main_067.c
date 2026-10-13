#include "common.h"

s32 func_00236C50(s32 arg0) {
    extern s32 func_002195E0(s32, void *, s32, s32, u16, s32, s32, s32, s32);
    extern s32 func_00236F90(s32, u16, u16, s32);
    extern s32 func_00217BD0();
    extern s32 func_00218020();
    extern u8 D_00297B90[];
    extern u8 D_00297B9A[];
    extern u8 D_00297BA4[];
    extern u8 D_00298490[];
    extern u8 D_002984E0[];
    extern u8 D_00298530[];
    extern u8 D_00298A00[];
    extern u8 D_00298BB0[];
    s8 *state;
    s16 baseX;
    s64 alpha;
    s64 side;
    s32 i;
    u8 *p;
    s32 j;
    s32 y;
    s32 row;
    u8 *q;
    s16 fade;

    baseX = D_00299ED4;
    state = &D_00299E10;
    if (*(s8 *)0x01ED0066 != 0) {
        *(s16 *)0x01ED0068 += 2;
        if (*(s16 *)0x01ED0068 > 16) {
            *(s16 *)0x01ED0068 = 16;
        }
    } else {
        *(s16 *)0x01ED0068 -= 2;
        if (*(s16 *)0x01ED0068 < 0) {
            *(s16 *)0x01ED0068 = 0;
        }
    }
    fade = *(s16 *)0x01ED0068;
    alpha = (s16)(256 - ((fade << 8) >> 4));
    if (*(s8 *)0x01ED018C == 1 && state[0xC6] == 11) {
        side = (s8)(state[0] ^ 1);
    } else if (state[0xC6] == 11) {
        side = (s8)(state[0] ^ 1);
    } else {
        if (*(s16 *)(D_00298BB0 + state[0xC6] * 0x34) == 8) {
            side = 0;
        } else {
            side = 1;
        }
    }
    if (fade != 0) {
        arg0 = func_002195E0(arg0, D_00297B90, (u16)(s8)side & 0xFFFF, 0,
                              alpha, 0, 0, 128, *(s16 *)0x01ED0228);
        arg0 = func_00236F90(arg0, baseX, alpha, 0);
        arg0 = func_002195E0(arg0, D_00297B9A, (u16)(s8)side, 0,
                              alpha, 0, 0, 128, 128);
        arg0 = func_002195E0(arg0, D_00297BA4, (u16)(state[0] ^ 1), 0,
                              alpha, 0, 0, 128, 128);
        p = D_00298530;
        i = 0;
        do {
            arg0 = func_00217BD0(arg0, p, alpha, 0);
            i++;
            p += 0x26;
        } while (i < 10);
        row = 0;
        y = 0;
        do {
            q = D_00298A00;
            j = 0;
            do {
                arg0 = func_00217BD0(arg0, q, alpha, y);
                j++;
                q += 0x26;
            } while (j < 3);
            y = (s16)(y + 16);
            row++;
        } while (row < 10);
        arg0 = func_00218020(arg0, D_00298490 + (s8)side * 0x26, alpha, 0, 0);
        arg0 = func_00218020(arg0, D_002984E0 + state[0] * 0x26, alpha, 0, 2);
    }
    return arg0;
}

INCLUDE_ASM("asm/nonmatchings/main_067", func_00236F90);

INCLUDE_ASM("asm/nonmatchings/main_067", func_002374D0);

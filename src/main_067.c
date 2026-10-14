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

extern u8 D_00298BA0[];
extern u8 D_00299F60[];
extern s32 D_0029A000;
extern u8 D_0029A44C[];

#pragma opt_strength_reduction off

void func_002374D0(void) {
    s16 spB0;
    u8 *spC0;
    s32 spD0;
    s16 var_s0;
    s32 var_s1;
    u8 *var_s2;
    s32 var_s3;
    s32 var_s4;
    s32 var_s5;
    f32 temp_f0;
    f32 temp_f20;
    s32 var_fp;
    s32 var_s7;
    u8 *var_s6;
    s16 var_s0_2;

    spC0 = D_00299F60;
    var_s6 = D_0029A44C;
    var_s1 = 0;
    func_0021BAE0(spC0);
    var_fp = 1;
    var_s7 = 2;
    D_0029A000 = 0;
    spB0 = 0;
    spD0 = 0;
    for (; spB0 < 16; spB0++) {
        var_s2 = spC0;
        var_s0 = 0;
        var_s3 = spD0 >> 5;
        var_s4 = (var_fp << 16) >> 5;
        var_s5 = (var_s7 << 16) >> 5;
        for (; var_s0 < 4; var_s0++) {
            if (var_s0 == 2) {
                *(s32 *)(var_s2 + 0xEC) = 0;
                *(s32 *)(var_s2 + 0xF0) = 0x410A6666;
                *(s32 *)(var_s2 + 0xF4) = 0;
                *(s32 *)(var_s2 + 0xF8) = 0;
            } else {
                switch (var_s0) {
                case 0:
                    var_s1 = var_s3;
                    break;
                case 1:
                    var_s1 = var_s4;
                    break;
                case 3:
                    var_s1 = var_s5;
                    break;
                }
                temp_f20 = 5.0f * func_0020B480(var_s1);
                temp_f0 = 5.0f * func_0020B550(var_s1);
                *(f32 *)(var_s2 + 0xEC) = temp_f20;
                *(s32 *)(var_s2 + 0xF0) = 0x410A6666;
                *(f32 *)(var_s2 + 0xF4) = temp_f0;
                *(s32 *)(var_s2 + 0xF8) = 0;
            }
            var_s2 += 0x10;
        }
        var_fp += 2;
        var_s7 += 2;
        spC0 += 0x40;
        spD0 += 0x20000;
    }
    var_s0_2 = 0;
    for (; var_s0_2 < 16; var_s0_2++) {
        func_0021BB70(var_s6, D_00298BA0);
        *(s32 *)(var_s6 + 0x20) = 0;
        var_s6[0x26] = 0;
        var_s6[0x2A] = 0;
        var_s6[0x2E] = 0x80;
        var_s6[0x32] = 0x80;
        var_s6[0x24] = 0x80;
        var_s6[0x28] = 0;
        var_s6[0x2C] = 0;
        var_s6[0x30] = 0x80;
        var_s6[0x25] = 0;
        var_s6[0x29] = 0x80;
        var_s6[0x2D] = 0;
        var_s6[0x31] = 0x80;
        var_s6[0x27] = 0x80;
        var_s6[0x2B] = 0;
        var_s6[0x2F] = 0;
        var_s6[0x33] = 0x80;
        var_s6 += 0x34;
    }
}
#pragma opt_strength_reduction reset

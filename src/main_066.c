#include "common.h"

void func_002336F0(void) {
    s16 temp_s0;

    temp_s0 = D_00299ED4;
    func_001A8320(1, (s32) temp_s0);
    func_001A8320(2, (s32) D_00299E10);
    if (D_00299E10 == 0) {
        func_001A8320(3, 0x44C);
        func_001A8320(4, temp_s0 + 0x3E8);
    } else {
        func_001A8320(3, temp_s0 + 0x3E8);
        func_001A8320(4, 0x44C);
    }
    func_001A8870(1, 0);
}

INCLUDE_ASM("asm/nonmatchings/main_066", func_002337A0);

void func_00233F50(s8 arg0) {
    *(s16 *)0x01ED001C = 0;
    switch (arg0) {
    case 0:
        *(s16 *)0x01ED001A = 0;
        *(s16 *)0x01ED001E = 0;
        *(s16 *)0x01ED0020 = 0;
        *(s16 *)0x01ED0022 = 0;
        break;
    case 1:
        *(s16 *)0x01ED001A = 1;
        *(s16 *)0x01ED001E = 0x40;
        *(s16 *)0x01ED0020 = 0;
        *(s16 *)0x01ED0022 = 0;
        break;
    case 2:
        *(s16 *)0x01ED001A = 2;
        *(s16 *)0x01ED001E = 0x40;
        *(s16 *)0x01ED0020 = 0x40;
        *(s16 *)0x01ED0022 = 0;
        break;
    case 3:
        *(s16 *)0x01ED001A = 3;
        *(s16 *)0x01ED001E = 0x40;
        *(s16 *)0x01ED0020 = 0x40;
        *(s16 *)0x01ED0022 = 0x74;
        break;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_066", func_00234040);

INCLUDE_ASM("asm/nonmatchings/main_066", func_002347D0);

void *func_002351A0(void *arg0) {
    s16 coords[19];
    u8 *state;
    s64 alpha;
    s32 i;
    s16 *row;
    u8 *fade;
    s32 y;
    s32 count;
    s16 *dst;
    s16 *src;
    s8 mode;
    s8 length;
    s8 *text;
    extern void *func_00218970();
    extern void *func_00217BD0();
    extern void *func_001B6F70();

    alpha = (s16)(0x80 - ((*(s16 *)0x01ED0070 << 7) >> 8));
    state = (u8 *)0x01ED0000;
    arg0 = func_00218970(arg0, D_002982F8, 0, alpha);
    row = D_00298260;
    y = (s16)alpha + 0x14F;
    i = 0;
    fade = state;
    do {
        dst = coords;
        count = 19;
        src = row;
        do {
            count--;
            *dst = *src;
            src++;
            dst++;
        } while (count > 0);
        if (i == *(s16 *)(state + 0x80) && *(s8 *)(state + 0x7E) != 0) {
            *(s16 *)(fade + 0x82) += 4;
            if (*(s16 *)(fade + 0x82) >= 16) {
                *(s16 *)(fade + 0x82) = 16;
            }
            coords[0] = row[0] - ((*(s16 *)(fade + 0x82) * 6) >> 4);
            coords[1] = row[1] - ((*(s16 *)(fade + 0x82) * 6) >> 4);
            coords[2] = row[2] + ((*(s16 *)(fade + 0x82) * 6) >> 4);
            coords[3] = row[3] + ((*(s16 *)(fade + 0x82) * 6) >> 4);
        } else {
            if (0 < *(s16 *)(fade + 0x82)) {
                *(s16 *)(fade + 0x82) -= 4;
                if (*(s16 *)(fade + 0x82) <= 0) {
                    *(s16 *)(fade + 0x82) = 0;
                }
            }
        }
        arg0 = func_00217BD0(arg0, coords, 0, alpha);
        mode = *(s8 *)(state + 0x7E);
        if (mode == 1 && i == *(s16 *)(state + 0x80) && mode != 0) {
            if (i == 0) {
                text = D_0030F102;
                length = 4;
            } else if (i == 1) {
                text = D_0030F107;
                length = 4;
            } else if (i == 2) {
                text = D_0030F10C;
                length = 6;
            } else {
                text = D_0030F113;
                length = 4;
            }
            arg0 = func_001B6F70(arg0, 0x232, y, 1, 1, length, text, 0);
        }
        i++;
        row += 19;
        fade += 2;
    } while (i < 4);
    if (*(s8 *)0x01ED007E == 0) {
        arg0 = func_00217BD0(arg0, D_00298B50, 0, alpha);
    } else {
        arg0 = func_00217BD0(arg0, D_00298B76, 0, alpha);
    }
    if (*(s8 *)0x01ED007E == 0) {
        arg0 = func_001B6F70(arg0, 0x232, y, 1, 1, 6, D_0030F118, 0);
    }
    return arg0;
}

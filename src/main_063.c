#include "common.h"

typedef struct {
    __int128 value;
} Scale_002232F0;

extern Scale_002232F0 D_0029A7D0;

typedef struct {
    s32 x, y, w, h;
} Rect_002232F0;

typedef struct {
    s32 pad;
    Rect_002232F0 rect;
} Texture_002232F0;

typedef struct {
    u8 r, g, b, a;
} Color_002232F0;

s32 func_002232F0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    extern s32 func_001FEAB0();
    extern s32 func_001FDFE0();
    Rect_002232F0 rect;
    Scale_002232F0 scale;
    Color_002232F0 color;
    s16 i;
    s16 column;
    s16 row;
    s16 x;
    s32 digit;
    Texture_002232F0 *texture;

    scale = D_0029A7D0;
    color.r = color.g = color.b = 0xFF;
    color.a = 0x80;
    i = 0;
    x = 0xA0;
    for (; i < 4; i++) {
        digit = 0;
        switch (i) {
        case 0:
            digit = arg1 % 10;
            break;
        case 1:
            digit = 10;
            break;
        case 2:
            digit = (arg2 / 10) % 10;
            break;
        case 3:
            digit = arg2 % 10;
            break;
        }
        if (digit == 0) {
            column = 4;
            row = 1;
        } else if (digit < 6) {
            column = digit - 1;
            row = 0;
        } else if (digit < 10) {
            column = digit - 6;
            row = 1;
        } else {
            column = 2;
            row = 4;
        }
        arg0 = func_001FD680(arg0, 1, 7, 0, 0x16);
        arg0 = func_0020F290(arg0);
        texture = (Texture_002232F0 *)func_001FEAB0(1);
        rect = texture->rect;
        color.r = color.g = color.b = 0xFF;
        color.a = 0x80;
        texture->rect.x = rect.x + column * 0x16;
        texture->rect.y = rect.y + row * 0x16;
        texture->rect.w = 0x16;
        texture->rect.h = 0x16;
        arg0 = func_001FDFE0(arg0, 1, x + arg3, 0x110, &scale, &color);
        func_001FEAF0(1);
        x += 0x10;
    }
    return arg0;
}

INCLUDE_ASM("asm/nonmatchings/main_063", func_00223600);

INCLUDE_ASM("asm/nonmatchings/main_063", func_00224A40);

INCLUDE_ASM("asm/nonmatchings/main_063", func_00224E40);

typedef struct Packet_00226120 {
    s16 x0, y0, x1, y1, x2, y2, x3, y3;
    u8 r0, g0, b0, a0;
    u8 r1, g1, b1, a1;
    u8 r2, g2, b2, a2;
    u8 r3, g3, b3, a3;
    s16 field20;
    s16 depth;
    s16 field24;
} Packet_00226120;

extern s16 D_00299ED2;
extern u8 D_00299F60;
extern Packet_00226120 D_0029AB80;

void *func_00226120(void *arg0) {
    extern void *func_00218970();
    s8 *context = &D_00299E10;
    u8 *slot = &D_00299F60;
    Packet_00226120 packet = D_0029AB80;
    s16 state;
    s16 i;

    if (D_00299ED2 == 0x2724 && *(s16 *)0x01ED536C < 6) {
        packet.depth = -10;
    } else if (*(s16 *)(context + 0xC2) == 0x2BB0) {
        packet.depth = -10;
    } else if (*(s16 *)(context + 0xC2) == 0x2F7C) {
        packet.depth = -10;
    }

    state = *(s16 *)0x01ED53A2;
    if (state != 0) {
        switch ((s16)state) {
        case 2:
            break;
        case 3:
            if (0 <= *(s16 *)0x01ED53A4) {
                *(s16 *)0x01ED53A4 -= 0x10;
                if (*(s16 *)0x01ED53A4 <= 0) {
                    *(s16 *)0x01ED53A4 = 0;
                    *(s16 *)0x01ED53A2 = 0;
                }
            }
            break;
        case 4:
            if (*(s16 *)0x01ED53A4 <= 0x1000) {
                *(s16 *)0x01ED53A4 += 0x20;
                if (*(s16 *)0x01ED53A4 >= 0x1000) {
                    *(s16 *)0x01ED53A4 = 0x1000;
                    *(s16 *)0x01ED53A2 = 4;
                }
            }
            break;
        case 10:
            *(s16 *)0x01ED53A4 += 0x400;
            if (*(s16 *)0x01ED53A4 >= 0x1000) {
                *(s16 *)0x01ED53A4 = 0x1000;
                *(s16 *)0x01ED53A2 = 11;
            }
            break;
        case 20:
            *(s16 *)0x01ED53A4 -= 0x100;
            if (*(s16 *)0x01ED53A4 <= 0) {
                *(s16 *)0x01ED53A4 = 0;
                *(s16 *)0x01ED53A2 = 21;
            }
            break;
        case 22:
            *(s16 *)0x01ED53A4 += 0x100;
            if (*(s16 *)0x01ED53A4 >= 0x1000) {
                *(s16 *)0x01ED53A4 = 0x1000;
                *(s16 *)0x01ED53A2 = 23;
            }
            break;
        case 30:
            *(s16 *)0x01ED53A4 += 0x400;
            if (*(s16 *)0x01ED53A4 >= 0x1000) {
                *(s16 *)0x01ED53A4 = 0x1000;
                *(s16 *)0x01ED53A2 = 31;
            }
            break;
        case 32:
            *(s16 *)0x01ED53A4 -= 0x20;
            if (*(s16 *)0x01ED53A4 <= 0) {
                *(s16 *)0x01ED53A4 = 0;
                *(s16 *)0x01ED53A2 = 33;
            }
            break;
        }

        state = *(s16 *)0x01ED53A2;
        if (state >= 30) {
            packet.r0 = packet.r1 = packet.r2 = packet.r3 = 255;
            packet.g0 = packet.g1 = packet.g2 = packet.g3 = 255;
            packet.b0 = packet.b1 = packet.b2 = packet.b3 = 255;
        } else if (state >= 20) {
            packet.r0 = packet.r1 = packet.r2 = packet.r3 = 0;
            packet.g0 = packet.g1 = packet.g2 = packet.g3 = 0;
            packet.b0 = packet.b1 = packet.b2 = packet.b3 = 0;
        } else if (state >= 10) {
            packet.r0 = packet.r1 = packet.r2 = packet.r3 = 0;
            packet.g0 = packet.g1 = packet.g2 = packet.g3 = 0;
            packet.b0 = packet.b1 = packet.b2 = packet.b3 = 32;
        }

        packet.x0 = packet.x2 = 0;
        packet.x1 = packet.x3 = 640;
        packet.y0 = packet.y1 = 0;
        packet.y2 = packet.y3 = 448;

        if (*(s16 *)(context + 0xC2) == 0x2738 && *(s16 *)0x01ED536C > 1) {
            packet.a0 = packet.a1 = packet.a2 = packet.a3 = 0;
        } else if (*(s16 *)(context + 0xC2) == 0x2B9A ||
                   *(s16 *)(context + 0xC2) == 0x2F64) {
            packet.a0 = packet.a1 = packet.a2 = packet.a3 = 0;
        } else {
            packet.a0 = packet.a1 = packet.a2 = packet.a3 =
                (*(s16 *)0x01ED53A4 << 7) >> 12;
            arg0 = func_00218970(arg0, &packet, 0, 0);
        }
    }

    func_0021BB20(slot);
    for (i = 0; i < 16; i++) {
    }
    return arg0;
}

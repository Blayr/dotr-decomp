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

INCLUDE_ASM("asm/nonmatchings/main_063", func_00226120);

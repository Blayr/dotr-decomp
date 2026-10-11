#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F3790);

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F3870);

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F3910);

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F3CB0);

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F3E40);

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F3EA0);

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F3F20);

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F40D0);

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F48F0);

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F4900);

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F4CB0);

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F4E50);

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F4F10);

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F4FD0);

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F5090);

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F51D0);

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F5240);

typedef struct {
    u8 unk00[0x10];
    s32 unk10;
    s32 unk14;
} Entry_001F52D0;

typedef struct {
    u8 unk00[0x100];
    Entry_001F52D0 entries[0x18];
} Data_001F52D0;

extern Data_001F52D0 D_0031BB50;

s32 func_001F52D0(s32 arg0) {
    Entry_001F52D0 *entry = &D_0031BB50.entries[arg0];
    s32 ret;

    if ((arg0 < 0) || (arg0 >= 0x18)) {
        ret = -1;
    } else {
        ret = entry->unk10;
    }
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F5320);

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F5370);

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F5380);

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F5390);

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F53A0);

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F53B0);

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F53C0);

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F54E0);

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F5560);

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F5620);

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F56D0);

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F57B0);

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F57C0);

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F5850);

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F5860);

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F58E0);

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F5970);

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F59D0);

s32 func_001F5A30(s32 arg0, s32 arg1) {
    s32 row;
    s32 column;

    row = arg0 >> 8;
    column = arg0 & 0xFF;
    if (row < 0 || row >= 3 || column < 0 || column >= 11) {
        return 0;
    }
    return func_001E3990(row, column, arg1);
}

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F5A90);

s32 func_001F5AF0(s32 arg0) {
    s32 temp_v0;

    temp_v0 = func_001DF540(arg0 >> 8, arg0 & 0xFF);
    if (temp_v0 == 0) {
        return 0;
    }
    return (*(s32 *)((u8 *)temp_v0 + 4) != 0) ? 1 : 0;
}

s32 func_001F5B30(s32 arg0) {
    s32 *temp_v0;

    temp_v0 = (s32 *)func_001DF540(arg0 >> 8, arg0 & 0xFF);
    if (temp_v0 == 0) {
        return 0;
    }
    return temp_v0[1];
}

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F5B70);

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F5BD0);

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F5C40);

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F5CA0);

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F5D10);

typedef struct {
    f32 x, y, z, w;
} Vec4_001F5D70;

s32 func_001E3DD0(s32, s32, void *);

s32 func_001F5D70(s32 arg0, void *arg1) {
    Vec4_001F5D70 *out = (Vec4_001F5D70 *)arg1;
    s32 a = arg0 >> 8;
    s32 b = arg0 & 0xFF;

    out->z = 0.0f;
    out->y = 0.0f;
    out->x = 0.0f;
    out->w = 1.0f;
    if (a < 0 || a >= 3 || b < 0 || b >= 0xB) {
        return 0;
    }
    return func_001E3DD0(a, b, out);
}

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F5DE0);

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F5E40);

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F5EB0);

s32 func_001F5EC0(s32 arg0) {
    s32 temp_v0;

    temp_v0 = func_001DF540(arg0 >> 8, arg0 & 0xFF);
    if (temp_v0 != 0) {
        return func_001F1370(*((u8 *)temp_v0 + 0x46));
    }
    return 0;
}

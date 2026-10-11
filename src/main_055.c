#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_055", func_00202220);

INCLUDE_ASM("asm/nonmatchings/main_055", func_002024D0);

INCLUDE_ASM("asm/nonmatchings/main_055", func_00202810);

INCLUDE_ASM("asm/nonmatchings/main_055", func_002029B0);

s32 func_00202AB0(s32 arg0, s32 arg1) {
    s32 sp3C;

    func_00209D30(func_00202B00(func_00209D20(), arg0, arg1, &sp3C));
    return sp3C;
}

INCLUDE_ASM("asm/nonmatchings/main_055", func_00202B00);

INCLUDE_ASM("asm/nonmatchings/main_055", func_00202BF0);

INCLUDE_ASM("asm/nonmatchings/main_055", func_00202CB0);

INCLUDE_ASM("asm/nonmatchings/main_055", func_00202D60);

u16 func_00202E00(s16 arg0, s32 arg1) {
    D_00322990 = arg0;
    D_00322992 = (u16) ((s32) ((s32) (arg1 << 0xD) >> 6) >> 2);
    D_00322994 = 0;
    return D_00322992;
}

INCLUDE_ASM("asm/nonmatchings/main_055", func_00202E30);

INCLUDE_ASM("asm/nonmatchings/main_055", func_00202F00);

void func_00202F50(s32 arg0, s32 arg1, s32 arg2) {
    func_00209D30(func_00202FB0(func_00209D20(), arg0, arg1, arg2));
}

INCLUDE_ASM("asm/nonmatchings/main_055", func_00202FB0);

INCLUDE_ASM("asm/nonmatchings/main_055", func_002031F0);

void func_002032A0(void) {
    func_0020B400(D_003259C0, 0, 0xB0);
}

INCLUDE_ASM("asm/nonmatchings/main_055", func_002032C0);

INCLUDE_ASM("asm/nonmatchings/main_055", func_00203320);

INCLUDE_ASM("asm/nonmatchings/main_055", func_00203840);

INCLUDE_ASM("asm/nonmatchings/main_055", func_002038F0);

INCLUDE_ASM("asm/nonmatchings/main_055", func_00203A40);

INCLUDE_ASM("asm/nonmatchings/main_055", func_00203B50);

INCLUDE_ASM("asm/nonmatchings/main_055", func_00203BC0);

INCLUDE_ASM("asm/nonmatchings/main_055", func_00203C00);

typedef struct Entry_00203C40 {
    u8 pad[0x206];
    u8 value;
} Entry_00203C40;

u8 func_00203C40(s32 arg0, s32 arg1) {
    return ((Entry_00203C40 *)(D_003259C0 + arg0 * 0x5C + arg1))->value;
}

void func_00203C70(s32 arg0, s32 arg1, s8 arg2) {
    *(s8 *)(D_003259C0 + arg0 * 0x5C + arg1 + 0x206) = arg2;
}

INCLUDE_ASM("asm/nonmatchings/main_055", func_00203CA0);

INCLUDE_ASM("asm/nonmatchings/main_055", func_00203CD0);

INCLUDE_ASM("asm/nonmatchings/main_055", func_00203E20);

INCLUDE_ASM("asm/nonmatchings/main_055", func_002047F0);

INCLUDE_ASM("asm/nonmatchings/main_055", func_00205150);

INCLUDE_ASM("asm/nonmatchings/main_055", func_00205160);

INCLUDE_ASM("asm/nonmatchings/main_055", func_00205170);

INCLUDE_ASM("asm/nonmatchings/main_055", func_002051C0);

typedef struct {
    s8 : 2;
    s8 flag : 1;
} Flags_002051F0;

extern Flags_002051F0 D_00325CAC;

s32 func_002051F0(void) {
    return D_00325CAC.flag ? 1 : 0;
}

INCLUDE_ASM("asm/nonmatchings/main_055", func_00205210);

INCLUDE_ASM("asm/nonmatchings/main_055", func_00205440);

INCLUDE_ASM("asm/nonmatchings/main_055", func_00205630);

INCLUDE_ASM("asm/nonmatchings/main_055", func_002058D0);

f32 func_00205C40(s32 arg0) {
    f32 *temp_s0;

    temp_s0 = func_001FAF60(0);
    func_001FAFB0(0, arg0);
    return *temp_s0;
}

INCLUDE_ASM("asm/nonmatchings/main_055", func_00205C90);

INCLUDE_ASM("asm/nonmatchings/main_055", func_00205CA0);

INCLUDE_ASM("asm/nonmatchings/main_055", func_00205CB0);

INCLUDE_ASM("asm/nonmatchings/main_055", func_00205D10);

INCLUDE_ASM("asm/nonmatchings/main_055", func_00205DF0);

INCLUDE_ASM("asm/nonmatchings/main_055", func_00205E70);

INCLUDE_ASM("asm/nonmatchings/main_055", func_00206030);

INCLUDE_ASM("asm/nonmatchings/main_055", func_002060F0);

INCLUDE_ASM("asm/nonmatchings/main_055", func_002061F0);

INCLUDE_ASM("asm/nonmatchings/main_055", func_002062F0);

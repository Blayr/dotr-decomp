#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_059", func_0020F780);

INCLUDE_ASM("asm/nonmatchings/main_059", func_0020FA10);

INCLUDE_ASM("asm/nonmatchings/main_059", func_0020FAF0);

INCLUDE_ASM("asm/nonmatchings/main_059", func_0020FED0);

INCLUDE_ASM("asm/nonmatchings/main_059", func_0020FF80);

INCLUDE_ASM("asm/nonmatchings/main_059", func_00210010);

INCLUDE_ASM("asm/nonmatchings/main_059", func_00210260);

INCLUDE_ASM("asm/nonmatchings/main_059", func_00210310);

INCLUDE_ASM("asm/nonmatchings/main_059", func_002106E0);

INCLUDE_ASM("asm/nonmatchings/main_059", func_002108C0);

INCLUDE_ASM("asm/nonmatchings/main_059", func_00210940);

INCLUDE_ASM("asm/nonmatchings/main_059", func_00210CF0);

INCLUDE_ASM("asm/nonmatchings/main_059", func_002114B0);

INCLUDE_ASM("asm/nonmatchings/main_059", func_00211530);

INCLUDE_ASM("asm/nonmatchings/main_059", func_002118F0);

INCLUDE_ASM("asm/nonmatchings/main_059", func_00211F70);

INCLUDE_ASM("asm/nonmatchings/main_059", func_00212170);

INCLUDE_ASM("asm/nonmatchings/main_059", func_00212250);

INCLUDE_ASM("asm/nonmatchings/main_059", func_00212D70);

INCLUDE_ASM("asm/nonmatchings/main_059", func_00212DE0);

INCLUDE_ASM("asm/nonmatchings/main_059", func_00212DF0);

INCLUDE_ASM("asm/nonmatchings/main_059", func_00212E60);

INCLUDE_ASM("asm/nonmatchings/main_059", func_00212FD0);

INCLUDE_ASM("asm/nonmatchings/main_059", func_002130A0);

INCLUDE_ASM("asm/nonmatchings/main_059", func_002131D0);

INCLUDE_ASM("asm/nonmatchings/main_059", func_00213410);

INCLUDE_ASM("asm/nonmatchings/main_059", func_002134D0);

INCLUDE_ASM("asm/nonmatchings/main_059", func_00213680);

INCLUDE_ASM("asm/nonmatchings/main_059", func_002138D0);

INCLUDE_ASM("asm/nonmatchings/main_059", func_00213A40);

INCLUDE_ASM("asm/nonmatchings/main_059", func_00213D00);

INCLUDE_ASM("asm/nonmatchings/main_059", func_00213F10);

INCLUDE_ASM("asm/nonmatchings/main_059", func_00213F60);

void func_00213F90(void) {
    func_00209D30(func_00213FC0(func_00209D20()));
}

INCLUDE_ASM("asm/nonmatchings/main_059", func_00213FC0);

s32 func_00214080(s32 *arg0, s32 *arg1) {
    return *arg0 - *arg1;
}

INCLUDE_ASM("asm/nonmatchings/main_059", func_00214090);

INCLUDE_ASM("asm/nonmatchings/main_059", func_00214100);

INCLUDE_ASM("asm/nonmatchings/main_059", func_00214190);

INCLUDE_ASM("asm/nonmatchings/main_059", func_00214210);

INCLUDE_ASM("asm/nonmatchings/main_059", func_00214290);

INCLUDE_ASM("asm/nonmatchings/main_059", func_002145D0);

INCLUDE_ASM("asm/nonmatchings/main_059", func_002145E0);

INCLUDE_ASM("asm/nonmatchings/main_059", func_00214620);

INCLUDE_ASM("asm/nonmatchings/main_059", func_00214910);

INCLUDE_ASM("asm/nonmatchings/main_059", func_00214990);

INCLUDE_ASM("asm/nonmatchings/main_059", func_00214BB0);

typedef struct {
    u8 pad[0xFF9C];
    u8 lo : 2;
    u8 flag2 : 1;
    u8 flag3 : 1;
    u8 flag4 : 1;
    u8 hi : 3;
    u8 pad2[3];
} Side_00214D00;

extern Side_00214D00 D_0032F790[];
extern u8 D_0034F6D0;

s32 func_00214D00(s32 arg0, s32 arg1) {
    Side_00214D00 *side;
    s32 idx;

    if (D_0034F6D0 == arg0) {
        idx = 0;
    } else {
        idx = 1;
    }
    side = &D_0032F790[idx];
    switch (arg1) {
    case 0:
        return side->flag2 ? 1 : 0;
    case 1:
        return side->flag3 ? 1 : 0;
    case 2:
        return side->flag4 ? 1 : 0;
    default:
        return -1;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_059", func_00214DD0);

INCLUDE_ASM("asm/nonmatchings/main_059", func_00214F00);

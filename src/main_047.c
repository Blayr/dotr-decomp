#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_047", func_001E4570);

INCLUDE_ASM("asm/nonmatchings/main_047", func_001E4E50);

typedef struct {
    s8 pad0 : 5;
    s8 flag : 1;
    s8 pad1 : 2;
} Flags;

extern Flags D_003181F7;

void func_001E4E60(s64 arg0) {
    D_003181F7.flag = arg0;
}

INCLUDE_ASM("asm/nonmatchings/main_047", func_001E4E90);

INCLUDE_ASM("asm/nonmatchings/main_047", func_001E4F00);

typedef struct {
    u8 padding[8];
    s32 field8;
} State_001E5210;

extern State_001E5210 D_0031AB88;

void func_001E5210(void *arg0, s32 arg1) {
    State_001E5210 *state = &D_0031AB88;
    s32 var_v1;

    if (arg1 != 0) {
        var_v1 = *(s32 *)((u8 *)arg0 + 0x14);
    } else {
        var_v1 = 0;
    }
    state->field8 = var_v1;
}

INCLUDE_ASM("asm/nonmatchings/main_047", func_001E5230);

INCLUDE_ASM("asm/nonmatchings/main_047", func_001E5240);

INCLUDE_ASM("asm/nonmatchings/main_047", func_001E5260);

INCLUDE_ASM("asm/nonmatchings/main_047", func_001E53C0);

s32 func_001E5590(s32 arg0) {
    if (func_001F3130(8) != 0) {
        return func_001E55E0(arg0);
    }
    return arg0;
}

INCLUDE_ASM("asm/nonmatchings/main_047", func_001E55E0);

s32 func_001E5D30(s32 arg0, s32 arg1, s32 arg2) {
    s32 parameters[4];

    arg0 = func_001EFA80(arg0, arg1, 0, 0, 0, 0, 0);
    if (arg2 < 9) {
        func_001F2330(arg1, parameters);
        parameters[1] = 0x8000;
        arg0 = func_001EFA80(arg0, arg1, 0, (s32) parameters, 0, 0, 0);
    }
    return arg0;
}

INCLUDE_ASM("asm/nonmatchings/main_047", func_001E5DD0);

INCLUDE_ASM("asm/nonmatchings/main_047", func_001E5EB0);

INCLUDE_ASM("asm/nonmatchings/main_047", func_001E60E0);

INCLUDE_ASM("asm/nonmatchings/main_047", func_001E6650);

INCLUDE_ASM("asm/nonmatchings/main_047", func_001E6F90);

void func_001E77A0(void) {
    s32 i;

    i = 0;
    do {
        func_001E53C0(i, 0);
        i += 1;
    } while (i < 2);
}

INCLUDE_ASM("asm/nonmatchings/main_047", func_001E77E0);

void func_001E7890(void) {
    func_00209D30(func_001E78C0(func_00209D20()));
}

INCLUDE_ASM("asm/nonmatchings/main_047", func_001E78C0);

void func_001E7A50(void) {

}

INCLUDE_ASM("asm/nonmatchings/main_047", func_001E7A60);

INCLUDE_ASM("asm/nonmatchings/main_047", func_001E7B20);

INCLUDE_ASM("asm/nonmatchings/main_047", func_001E7D00);

INCLUDE_ASM("asm/nonmatchings/main_047", func_001E7DE0);

INCLUDE_ASM("asm/nonmatchings/main_047", func_001E7E70);

INCLUDE_ASM("asm/nonmatchings/main_047", func_001E7F70);

INCLUDE_ASM("asm/nonmatchings/main_047", func_001E84D0);

INCLUDE_ASM("asm/nonmatchings/main_047", func_001E8780);

INCLUDE_ASM("asm/nonmatchings/main_047", func_001E8BF0);

INCLUDE_ASM("asm/nonmatchings/main_047", func_001E8E90);

INCLUDE_ASM("asm/nonmatchings/main_047", func_001E8FA0);

INCLUDE_ASM("asm/nonmatchings/main_047", func_001E90B0);

typedef struct Object_001E9280 {
    u8 pad_00[0x14];
    s32 value;
    u8 pad_18[4];
    s32 packed;
} Object_001E9280;

void func_001E9280(void *arg0, s32 arg1) {
    Object_001E9280 *object = arg0;
    s32 packed = object->packed;
    s32 *entry = (s32 *)(packed & 0x03FFFFFF);

    packed >>= 26;
    if (arg1 != 0) {
        entry = (s32 *)((u8 *)entry + packed * 0x10);
        *entry = object->value;
        func_0020F250(*entry);
    }
}

INCLUDE_ASM("asm/nonmatchings/main_047", func_001E92C0);

INCLUDE_ASM("asm/nonmatchings/main_047", func_001E9340);

INCLUDE_ASM("asm/nonmatchings/main_047", func_001EA0F0);

void func_001EA270(void *arg0, s32 arg1) {
    s32 *temp_v1;

    temp_v1 = *(s32 **)((u8 *)arg0 + 0x1C);
    if (arg1 != 0) {
        *temp_v1 = *(s32 *)((u8 *)arg0 + 0x14);
        func_0020F250(*temp_v1);
    }
}

INCLUDE_ASM("asm/nonmatchings/main_047", func_001EA2A0);

INCLUDE_ASM("asm/nonmatchings/main_047", func_001EA410);

#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_038", func_001ADD00);

INCLUDE_ASM("asm/nonmatchings/main_038", func_001AE520);

s32 func_001AE5A0(s32 arg0) {
    if (func_001F3130(0) != 0) {
        return func_001AE5F0(arg0);
    }
    return arg0;
}

INCLUDE_ASM("asm/nonmatchings/main_038", func_001AE5F0);

void func_001AEE80(void) {
    func_00209D30(func_001AEEB0(func_00209D20()));
}

INCLUDE_ASM("asm/nonmatchings/main_038", func_001AEEB0);

INCLUDE_ASM("asm/nonmatchings/main_038", func_001AEFC0);

INCLUDE_ASM("asm/nonmatchings/main_038", func_001AEFD0);

s32 func_001AF110(s32 arg0) {
    func_001FEAF0(0);
    return arg0;
}

typedef struct {
    u8 pad[0x6A0];
    s32 entries[8];
} Data_001AF140;

s32 func_001AF140(s32 arg0) {
    Data_001AF140 *data = (Data_001AF140 *)D_00317490;

    if ((arg0 < 0) || (arg0 >= 8)) {
        return 0;
    }
    return data->entries[arg0];
}

INCLUDE_ASM("asm/nonmatchings/main_038", func_001AF180);

INCLUDE_ASM("asm/nonmatchings/main_038", func_001AF5C0);

void func_001AF7B0(void) {
    func_00209D30(func_001AF7E0(func_00209D20()));
}

INCLUDE_ASM("asm/nonmatchings/main_038", func_001AF7E0);

INCLUDE_ASM("asm/nonmatchings/main_038", func_001B0CE0);

void func_001B1190(void) {
    func_00209D30(func_001B11C0(func_00209D20()));
}

INCLUDE_ASM("asm/nonmatchings/main_038", func_001B11C0);

INCLUDE_ASM("asm/nonmatchings/main_038", func_001B19F0);

INCLUDE_ASM("asm/nonmatchings/main_038", func_001B1EF0);

INCLUDE_ASM("asm/nonmatchings/main_038", func_001B20E0);

INCLUDE_ASM("asm/nonmatchings/main_038", func_001B22F0);

INCLUDE_ASM("asm/nonmatchings/main_038", func_001B3100);

INCLUDE_ASM("asm/nonmatchings/main_038", func_001B3640);

INCLUDE_ASM("asm/nonmatchings/main_038", func_001B3790);

void func_001B3CC0(s32, s32, s32, s32, s32, s32, s32, s32,
                   s64, s64, s64, s64, s64, s64);

void func_001B3C80(s32 arg0, s32 arg1, s32 arg2, s32 arg3,
                   s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                   s32 arg8, s32 arg9, s32 arg10) {
    func_001B3CC0(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
                  0, 0, (s64) arg8, (s64) arg9, (s64) arg10, 0x80);
}

INCLUDE_ASM("asm/nonmatchings/main_038", func_001B3CC0);

INCLUDE_ASM("asm/nonmatchings/main_038", func_001B4540);

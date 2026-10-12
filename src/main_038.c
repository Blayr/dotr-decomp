#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_038", func_001ADD00);

void func_001AE520(void) {
    u8 *data = D_00317490;
    s32 var_a1;
    s32 var_s0;

    var_a1 = 0;
    do {
        data[var_a1 + 0xCB2] = 0x18;
        var_a1 += 1;
    } while (var_a1 < 4);
    var_s0 = 1;
    do {
        func_001DFBB0(0, var_s0);
        func_001DFBB0(1, var_s0);
        var_s0 += 1;
    } while (var_s0 < 0xB);
}

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

s32 func_001AEFC0(s32 arg0) {
    return func_001AEFD0(arg0, 0);
}

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

s32 func_001B20E0(s32 arg0, s32 arg1, s32 arg2) {
    extern s32 func_001B3C80();
    extern s32 func_001B65E0();
    extern s32 func_001B6C90();
    extern s32 func_001FEAB0();
    extern s32 func_001E08F0();
    extern s32 func_001DE4E0();
    extern s32 func_001FE7D0();
    u8 *global;
    s32 x;
    s32 xResult;
    s32 y;
    s32 yResult;
    s32 xCoord;
    s32 result;
    s32 temp;
    s32 flag;
    s32 areaX;
    s32 areaY;

    global = D_00317490;
    x = arg1 + 3;
    y = arg2 + 3;
    areaX = x + 0x6C0;
    areaY = y + 0x720;
    flag = 0;
    if (func_001DE4E0(D_003181CC) < 0x20) {
        if (func_001DE4E0(global[0xD3C] ^ 1) >= 0x64) {
            flag = 1;
        }
    }

    arg0 = func_001B4780(arg0, global[0xD54], -1, 6, arg1, arg2, 8, 3, (s64) 1);
    result = func_001B3C80(arg0, (s32) D_002909B8, areaX + 4, areaY + 3,
                           0, 1, 0, 0, 1, 0, -1);
    xCoord = x + 0x1E;
    yResult = y + 1;
    xResult = func_001B65E0(result, global[0xD54], xCoord, yResult, 3, 1, -1);
    if (flag != 0) {
        temp = func_0020F290(func_001FD680(xResult, 1, 0x1C, 0, 0x16));
        result = func_001FEAB0(1);
        *(s32 *)(result + 0xC) = 0x2C;
        result = func_001FE7D0(temp, 1, xCoord + 3, yResult + 2, 0, func_001FDFE0);
        func_001FEAF0(1);
    } else {
        temp = func_001E08F0(2, global[0xD4F] + 1, 0);
        result = func_001B6C90(xResult, xCoord + 3, yResult + 2, 2,
                             global[0xD4E] != 0 ? func_0026E950() : temp, 0);
    }
    return result;
}

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

#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_074", func_00254890);

INCLUDE_ASM("asm/nonmatchings/main_074", func_00254B20);

INCLUDE_ASM("asm/nonmatchings/main_074", func_00254C90);

INCLUDE_ASM("asm/nonmatchings/main_074", func_002550C0);

INCLUDE_ASM("asm/nonmatchings/main_074", func_00255960);

INCLUDE_ASM("asm/nonmatchings/main_074", func_00255A30);

INCLUDE_ASM("asm/nonmatchings/main_074", func_00255AC0);

INCLUDE_ASM("asm/nonmatchings/main_074", func_00255B50);

INCLUDE_ASM("asm/nonmatchings/main_074", func_00255C30);

INCLUDE_ASM("asm/nonmatchings/main_074", func_00255CD0);

void func_00255D40(s32 *arg0) {
    if (func_001DE540() == 0) {
        arg0[0] = 0x1F4;
        arg0[1] = 0x3FFF;
        arg0[2] = 0x17FF;
        arg0[3] = 0;
    } else {
        arg0[0] = 0x1F4;
        arg0[1] = 0xBFFF;
        arg0[2] = 0x17FF;
        arg0[3] = 0;
    }
}

typedef struct Config_00255DB0 {
    s32 value;
    s32 flags;
    s32 limit;
    s32 reserved;
} Config_00255DB0;

void func_00255DB0(void *arg0) {
    Config_00255DB0 *config = arg0;

    if (func_001DE540() == 0) {
        config->value = 0x1F4;
        config->flags = 0x3FFF;
        config->limit = 0x3800;
        config->reserved = 0;
    } else {
        config->value = 0x2BC;
        config->flags = 0xBFFF;
        config->limit = 0x3800;
        config->reserved = 0;
    }
}

void func_00255E20(void *arg0) {
    s32 *values = arg0;

    if (func_001DE540() == 0) {
        values[0] = 0x1F4;
        values[1] = 0x2000;
        values[2] = 0x400;
        values[3] = 0;
    } else {
        values[0] = 0x1F4;
        values[1] = 0xA000;
        values[2] = 0x400;
        values[3] = 0;
    }
}

void func_00255E90(void *arg0) {
    s32 *values = (s32 *)arg0;

    if (func_001DE540() == 0) {
        values[0] = 0x7A;
        values[1] = 0x5000;
        values[2] = -0x1000;
        values[3] = 0;
    } else {
        values[0] = 0x7A;
        values[1] = 0xD000;
        values[2] = -0x1000;
        values[3] = 0;
    }
}

void func_00255F00(void *arg0, s32 arg1) {
    s32 *data = arg0;

    if (func_001DE540() == 0) {
        data[0] = arg1;
        data[1] = 0x3FFF;
        data[2] = 0x1000;
        data[3] = 0;
    } else {
        data[0] = arg1;
        data[1] = 0xBFFF;
        data[2] = 0x1000;
        data[3] = 0;
    }
}

typedef struct {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
} Block_00255F70;

void func_00255F70(void *arg0, s32 arg1) {
    if (func_001DE540() == 0) {
        ((Block_00255F70 *)arg0)->f0 = arg1;
        ((Block_00255F70 *)arg0)->f4 = 0x4FFF;
        ((Block_00255F70 *)arg0)->f8 = 0x1800;
        ((Block_00255F70 *)arg0)->fC = 0;
    } else {
        ((Block_00255F70 *)arg0)->f0 = arg1;
        ((Block_00255F70 *)arg0)->f4 = 0xCFFF;
        ((Block_00255F70 *)arg0)->f8 = 0x1800;
        ((Block_00255F70 *)arg0)->fC = 0;
    }
}

void func_00255FE0(void *arg0) {
    s32 *values = arg0;

    if (func_001DE540() == 0) {
        values[0] = 0xFA;
        values[1] = 0x2000;
        values[2] = -0x1800;
        values[3] = 0;
    } else {
        values[0] = 0xFA;
        values[1] = 0xA000;
        values[2] = -0x1800;
        values[3] = 0;
    }
}

void func_00256050(void *arg0) {
    s32 *values = arg0;

    if (func_001DE540() == 0) {
        values[0] = 0x1F4;
        values[1] = 0x6000;
        values[2] = -0x800;
        values[3] = 0;
    } else {
        values[0] = 0x1F4;
        values[1] = 0xE000;
        values[2] = -0x800;
        values[3] = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_074", func_002560C0);

INCLUDE_ASM("asm/nonmatchings/main_074", func_00256520);

INCLUDE_ASM("asm/nonmatchings/main_074", func_00256AB0);

INCLUDE_ASM("asm/nonmatchings/main_074", func_00256D80);

INCLUDE_ASM("asm/nonmatchings/main_074", func_00257340);

INCLUDE_ASM("asm/nonmatchings/main_074", func_00257AA0);

INCLUDE_ASM("asm/nonmatchings/main_074", func_00258490);

INCLUDE_ASM("asm/nonmatchings/main_074", func_00258760);

INCLUDE_ASM("asm/nonmatchings/main_074", func_00258E20);

INCLUDE_ASM("asm/nonmatchings/main_074", func_002594D0);

INCLUDE_ASM("asm/nonmatchings/main_074", func_00259D90);

INCLUDE_ASM("asm/nonmatchings/main_074", func_0025A060);

INCLUDE_ASM("asm/nonmatchings/main_074", func_0025A4C0);

INCLUDE_ASM("asm/nonmatchings/main_074", func_0025A940);

INCLUDE_ASM("asm/nonmatchings/main_074", func_0025AA80);

INCLUDE_ASM("asm/nonmatchings/main_074", func_0025AD60);

INCLUDE_ASM("asm/nonmatchings/main_074", func_0025B050);

INCLUDE_ASM("asm/nonmatchings/main_074", func_0025B330);

INCLUDE_ASM("asm/nonmatchings/main_074", func_0025B610);

INCLUDE_ASM("asm/nonmatchings/main_074", func_0025B900);

INCLUDE_ASM("asm/nonmatchings/main_074", func_0025BE50);

INCLUDE_ASM("asm/nonmatchings/main_074", func_0025C0B0);

INCLUDE_ASM("asm/nonmatchings/main_074", func_0025C330);

INCLUDE_ASM("asm/nonmatchings/main_074", func_0025C9E0);

INCLUDE_ASM("asm/nonmatchings/main_074", func_0025D230);

INCLUDE_ASM("asm/nonmatchings/main_074", func_0025D640);

INCLUDE_ASM("asm/nonmatchings/main_074", func_0025D9D0);

INCLUDE_ASM("asm/nonmatchings/main_074", func_0025DE70);

INCLUDE_ASM("asm/nonmatchings/main_074", func_0025E200);

INCLUDE_ASM("asm/nonmatchings/main_074", func_0025E710);

INCLUDE_ASM("asm/nonmatchings/main_074", func_0025EBE0);

s32 func_0025ECB0(void) {
    s32 var_s0;
    s32 var_s1;

    var_s0 = 0;
    do {
        var_s1 = 0;
        do {
            if (func_001E3790(var_s0, var_s1) < 0) {
                return (var_s1 << 8) | var_s0;
            }
            var_s1 += 1;
        } while (var_s1 < 7);
        var_s0 += 1;
    } while (var_s0 < 7);
    return -1;
}

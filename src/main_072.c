#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_072", func_0024B310);

INCLUDE_ASM("asm/nonmatchings/main_072", func_0024C330);

void func_0024C450(s32 *arg0, s32 arg1, s32 arg2) {
    s32 temp_a0;
    s32 *temp_a1;
    s32 *temp_a2;

    temp_a1 = arg0 + arg1;
    temp_a2 = arg0 + arg2;
    temp_a0 = *temp_a1;
    *temp_a1 = *temp_a2;
    *temp_a2 = temp_a0;
}

INCLUDE_ASM("asm/nonmatchings/main_072", func_0024C480);

s32 func_0024C780(u32 arg0, s32 arg1, s32 arg2) {
    if (arg1 == 0) {
        return (arg0 & 0x7FF) | (((arg0 >> 0xB) | (1 << (0xA - arg2))) << 0xB);
    }
    return arg0 | (1 << (0xA - arg2));
}

INCLUDE_ASM("asm/nonmatchings/main_072", func_0024C7D0);

INCLUDE_ASM("asm/nonmatchings/main_072", func_0024C870);

INCLUDE_ASM("asm/nonmatchings/main_072", func_0024C910);

INCLUDE_ASM("asm/nonmatchings/main_072", func_0024CA40);

INCLUDE_ASM("asm/nonmatchings/main_072", func_0024DD80);

s32 func_0024DE20(s32 arg0, s32 arg1) {
    switch (arg1) {
    case 1:
        return arg0;
    case 2:
        return (arg0 == 0) ? 1 : 0;
    default:
        return -1;
    }
}

s32 func_0024DE70(s32 arg0, s32 arg1) {
    if (func_001E2100(arg0, arg1, 1) != 0) {
        return (arg0 == 0) ? 1 : 0;
    }
    return arg0;
}

INCLUDE_ASM("asm/nonmatchings/main_072", func_0024DEB0);

INCLUDE_ASM("asm/nonmatchings/main_072", func_0024DF00);

INCLUDE_ASM("asm/nonmatchings/main_072", func_0024DF80);

INCLUDE_ASM("asm/nonmatchings/main_072", func_0024E220);

INCLUDE_ASM("asm/nonmatchings/main_072", func_0024E300);

INCLUDE_ASM("asm/nonmatchings/main_072", func_0024E410);

INCLUDE_ASM("asm/nonmatchings/main_072", func_0024E780);

INCLUDE_ASM("asm/nonmatchings/main_072", func_0024E880);

s32 func_0024E910(s32 arg0) {
    s32 count = 0;
    s32 bit = 0;

    do {
        if ((((u32) arg0 >> bit) & 1) == 1) {
            count += 1;
        }
        bit += 1;
    } while (bit < 0x16);
    return count;
}

INCLUDE_ASM("asm/nonmatchings/main_072", func_0024E950);

INCLUDE_ASM("asm/nonmatchings/main_072", func_0024EA10);

s32 func_0024EA60(void) {
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_072", func_0024EA70);

INCLUDE_ASM("asm/nonmatchings/main_072", func_0024EBD0);

INCLUDE_ASM("asm/nonmatchings/main_072", func_0024EC50);

INCLUDE_ASM("asm/nonmatchings/main_072", func_0024ECD0);

INCLUDE_ASM("asm/nonmatchings/main_072", func_0024EFB0);

INCLUDE_ASM("asm/nonmatchings/main_072", func_0024F060);

INCLUDE_ASM("asm/nonmatchings/main_072", func_0024F150);

INCLUDE_ASM("asm/nonmatchings/main_072", func_0024F200);

INCLUDE_ASM("asm/nonmatchings/main_072", func_0024F2F0);

INCLUDE_ASM("asm/nonmatchings/main_072", func_0024F370);

INCLUDE_ASM("asm/nonmatchings/main_072", func_0024F430);

INCLUDE_ASM("asm/nonmatchings/main_072", func_0024F520);

INCLUDE_ASM("asm/nonmatchings/main_072", func_0024F780);

INCLUDE_ASM("asm/nonmatchings/main_072", func_0024F830);

INCLUDE_ASM("asm/nonmatchings/main_072", func_0024FD10);

void func_0024FDA0(void) {
    func_0024FDD0(func_001DF540());
}

INCLUDE_ASM("asm/nonmatchings/main_072", func_0024FDD0);

INCLUDE_ASM("asm/nonmatchings/main_072", func_0024FE40);

INCLUDE_ASM("asm/nonmatchings/main_072", func_0024FEB0);

INCLUDE_ASM("asm/nonmatchings/main_072", func_00250000);

INCLUDE_ASM("asm/nonmatchings/main_072", func_002500C0);

INCLUDE_ASM("asm/nonmatchings/main_072", func_00250300);

s32 func_00250360(s32 arg0, s32 arg1) {
    return func_0024DE70(arg0, arg1);
}

typedef struct {
    s8 unused : 1;
    s8 inverted : 1;
    s8 reserved : 6;
} Flags_00250370;

typedef struct {
    u8 pad_00[0x44];
    u8 value;
    u8 pad_45[0x12];
    Flags_00250370 flags;
} Data_00250370;

s32 func_00250370(void *arg0) {
    Data_00250370 *data = arg0;

    if (arg0 == NULL) {
        return -1;
    }
    if (data->flags.inverted == 0) {
        return data->value;
    }
    return (data->value == 0) ? 1 : 0;
}

INCLUDE_ASM("asm/nonmatchings/main_072", func_002503B0);

INCLUDE_ASM("asm/nonmatchings/main_072", func_00250430);

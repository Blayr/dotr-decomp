#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_044", func_001DE0B0);

INCLUDE_ASM("asm/nonmatchings/main_044", func_001DE130);

INCLUDE_ASM("asm/nonmatchings/main_044", func_001DE1A0);

INCLUDE_ASM("asm/nonmatchings/main_044", func_001DE210);

s32 func_001DE260(s32 arg0) {
    if (arg0 < 0 || arg0 >= 0x356) {
        return -1;
    }
    return D_002CE4A4[arg0];
}

INCLUDE_ASM("asm/nonmatchings/main_044", func_001DE2A0);

INCLUDE_ASM("asm/nonmatchings/main_044", func_001DE2B0);

typedef struct {
    u8 padding[0x33C];
    u8 value;
    u8 trailing_padding[0x13];
} Record_001DE4E0;

u8 func_001DE4E0(s32 arg0) {
    return ((Record_001DE4E0 *)(D_00317490 + arg0 * 0x350))->value;
}

void func_001DE500(s32 arg0, s32 arg1) {
    u8 *entry;

    entry = D_00317490 + (arg0 * 0x350);
    if (entry[0x33C] != (arg1 & 0xFF)) {
        arg1 &= 0x7F;
        entry[0x33C] = arg1;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_044", func_001DE540);

INCLUDE_ASM("asm/nonmatchings/main_044", func_001DE550);

INCLUDE_ASM("asm/nonmatchings/main_044", func_001DE560);

INCLUDE_ASM("asm/nonmatchings/main_044", func_001DE570);

typedef struct {
    u8 padding[0x341];
    u8 value;
    u8 trailing[0xE];
} Entry_001DE5C0;

s32 func_001DE5C0(s32 arg0) {
    return ((Entry_001DE5C0 *)(D_00317490 + arg0 * 0x350))->value;
}

INCLUDE_ASM("asm/nonmatchings/main_044", func_001DE5E0);

typedef struct Entry_001DE690 {
    u8 padding[0x342];
    u8 value;
    u8 tail[0xD];
} Entry_001DE690;

u8 func_001DE690(s32 arg0) {
    return ((Entry_001DE690 *)(D_00317490 + arg0 * 0x350))->value;
}

typedef struct {
    u8 padding[0x342];
    s8 value;
    u8 reserved[0xD];
} Entry_001DE6B0;

void func_001DE6B0(s32 arg0, s8 arg1) {
    ((Entry_001DE6B0 *)(D_00317490 + arg0 * 0x350))->value = arg1;
}

typedef struct {
    u8 padding[0x346];
    s8 flag : 1;
    u8 tail[9];
} Entry_001DE6D0;

s32 func_001DE6D0(s32 arg0) {
    return ((Entry_001DE6D0 *) (D_00317490 + arg0 * 0x350))->flag ? 1 : 0;
}

typedef struct {
    u8 pad0[0x346];
    s8 enabled : 1;
    s8 reserved : 7;
    u8 pad347[9];
} Flags_001DE700;

void func_001DE700(s32 arg0, s32 arg1) {
    Flags_001DE700 *record = (Flags_001DE700 *)(D_00317490 + arg0 * 0x350);

    record->enabled = arg1 ? 1 : 0;
}

typedef struct {
    u8 pad[0x344];
    u8 field_344;
    u8 tail[0xB];
} Entry_001DE740;

u8 func_001DE740(s32 arg0) {
    return ((Entry_001DE740 *)(D_00317490 + arg0 * 0x350))->field_344;
}

void func_001DE760(s32 arg0, s8 arg1) {
    *(s8 *)(D_00317490 + arg0 * 0x350 + 0x344) = arg1;
}

typedef struct {
    s8 unused : 7;
    s8 enabled : 1;
} Flags_001DE780;

extern Flags_001DE780 D_003181F6;

s32 func_001DE780(void) {
    return D_003181F6.enabled ? 1 : 0;
}

typedef struct {
    u8 padding[0xD66];
    s8 : 7;
    s8 enabled : 1;
} Flags_001DE7A0;

void func_001DE7A0(s32 arg0) {
    Flags_001DE7A0 *flags = (Flags_001DE7A0 *) D_00317490;

    flags->enabled = (s8) (arg0 ? 1 : 0);
}

INCLUDE_ASM("asm/nonmatchings/main_044", func_001DE7E0);

INCLUDE_ASM("asm/nonmatchings/main_044", func_001DE820);

INCLUDE_ASM("asm/nonmatchings/main_044", func_001DE860);

INCLUDE_ASM("asm/nonmatchings/main_044", func_001DE970);

typedef struct Record_001DE9C0 {
    u8 padding[0x230];
    u8 field230;
} Record_001DE9C0;

s32 func_001DE9C0(s32 arg0) {
    return ((Record_001DE9C0 *)(D_00317490 + arg0 * 0x350))->field230;
}

INCLUDE_ASM("asm/nonmatchings/main_044", func_001DE9E0);

INCLUDE_ASM("asm/nonmatchings/main_044", func_001DEA30);

INCLUDE_ASM("asm/nonmatchings/main_044", func_001DEB20);

INCLUDE_ASM("asm/nonmatchings/main_044", func_001DEC00);

INCLUDE_ASM("asm/nonmatchings/main_044", func_001DECC0);

INCLUDE_ASM("asm/nonmatchings/main_044", func_001DED30);

INCLUDE_ASM("asm/nonmatchings/main_044", func_001DEDB0);

INCLUDE_ASM("asm/nonmatchings/main_044", func_001DEE00);

u8 func_001DEE50(s32 arg0) {
    return *(u8 *)(D_00317490 + (arg0 * 0x350) + 0x322);
}

INCLUDE_ASM("asm/nonmatchings/main_044", func_001DEE70);

INCLUDE_ASM("asm/nonmatchings/main_044", func_001DEF20);

INCLUDE_ASM("asm/nonmatchings/main_044", func_001DF000);

INCLUDE_ASM("asm/nonmatchings/main_044", func_001DF070);

INCLUDE_ASM("asm/nonmatchings/main_044", func_001DF0C0);

INCLUDE_ASM("asm/nonmatchings/main_044", func_001DF110);

INCLUDE_ASM("asm/nonmatchings/main_044", func_001DF130);

INCLUDE_ASM("asm/nonmatchings/main_044", func_001DF1E0);

INCLUDE_ASM("asm/nonmatchings/main_044", func_001DF2C0);

s32 func_001DF330(s32 arg0) {
    s32 var_a0;
    u16 *var_a1;

    var_a1 = (u16 *)(D_00317490 + (arg0 * 0x350) + 0x324);
    var_a0 = 0;
    do {
        var_a0 += 1;
        *var_a1 &= 0xFFF;
        var_a1++;
    } while (var_a0 < 5);
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_044", func_001DF370);

INCLUDE_ASM("asm/nonmatchings/main_044", func_001DF470);

INCLUDE_ASM("asm/nonmatchings/main_044", func_001DF490);

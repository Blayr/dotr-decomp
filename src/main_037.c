#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_037", func_001A6C30);

INCLUDE_ASM("asm/nonmatchings/main_037", func_001A6C48);

INCLUDE_ASM("asm/nonmatchings/main_037", func_001A6C60);

INCLUDE_ASM("asm/nonmatchings/main_037", func_001A6C80);

INCLUDE_ASM("asm/nonmatchings/main_037", func_001A6FF0);

INCLUDE_ASM("asm/nonmatchings/main_037", func_001A7380);

typedef struct {
    u8 padding[0x138];
    s32 entries[0x25];
} Table_001A82E0;

s32 func_001A82E0(s32 arg0) {
    Table_001A82E0 *table = (Table_001A82E0 *)&D_00317250;
    s32 result;

    if ((arg0 < 0) || (arg0 >= 0x25)) {
        result = -1;
    } else {
        result = table->entries[arg0];
    }
    return result;
}

typedef struct State_001A8320 {
    u8 padding[0x138];
    s32 values[0x25];
} State_001A8320;

s32 func_001A8320(s32 arg0, s32 arg1) {
    State_001A8320 *state = (State_001A8320 *)&D_00317250;

    if ((arg0 < 0) || (arg0 >= 0x25)) {
        return 0;
    }
    state->values[arg0] = arg1;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_037", func_001A8360);

INCLUDE_ASM("asm/nonmatchings/main_037", func_001A83E0);

INCLUDE_ASM("asm/nonmatchings/main_037", func_001A8520);

INCLUDE_ASM("asm/nonmatchings/main_037", func_001A8690);

typedef struct {
    u8 pad00[0xF4];
    u32 count;
    u8 padF8[0x133];
    s8 selected;
} State_001A86A0;

void func_001A86A0(s32 arg0) {
    State_001A86A0 *state = (State_001A86A0 *)&D_00317250;

    if ((arg0 >= 0) && ((u32)arg0 < state->count)) {
        state->selected = arg0;
    }
}

typedef struct Flags_001A86D0 {
    s8 reserved0 : 5;
    s8 enabled : 1;
    s8 reserved1 : 2;
} Flags_001A86D0;

extern Flags_001A86D0 D_0031747E;

s32 func_001A86D0(void) {
    return D_0031747E.enabled != 0 ? 1 : 0;
}

s32 func_001A86F0(void) {
    D_00317250 += 1;
    return 1;
}

s32 func_001A8710(void) {
    return *(s32 *)0x10000800;
}

INCLUDE_ASM("asm/nonmatchings/main_037", func_001A8720);

s32 func_001A8730(void) {
    return ++D_00317254;
}

INCLUDE_ASM("asm/nonmatchings/main_037", func_001A8750);

INCLUDE_ASM("asm/nonmatchings/main_037", func_001A8760);

INCLUDE_ASM("asm/nonmatchings/main_037", func_001A8770);

INCLUDE_ASM("asm/nonmatchings/main_037", func_001A87A0);

INCLUDE_ASM("asm/nonmatchings/main_037", func_001A87C0);

INCLUDE_ASM("asm/nonmatchings/main_037", func_001A8870);

INCLUDE_ASM("asm/nonmatchings/main_037", func_001A8920);

INCLUDE_ASM("asm/nonmatchings/main_037", func_001A89C0);

INCLUDE_ASM("asm/nonmatchings/main_037", func_001A8BB0);

INCLUDE_ASM("asm/nonmatchings/main_037", func_001A8DB0);

INCLUDE_ASM("asm/nonmatchings/main_037", func_001A9590);

INCLUDE_ASM("asm/nonmatchings/main_037", func_001A9800);

INCLUDE_ASM("asm/nonmatchings/main_037", func_001A98B0);

INCLUDE_ASM("asm/nonmatchings/main_037", func_001A9F50);

INCLUDE_ASM("asm/nonmatchings/main_037", func_001AA260);

INCLUDE_ASM("asm/nonmatchings/main_037", func_001AAAF0);

INCLUDE_ASM("asm/nonmatchings/main_037", func_001AAD50);

typedef struct {
    u8 pad[0x1F1];
    s8 values[0x2D];
    s8 negative;
    s8 zero;
    u8 pad220[2];
    u8 selected;
} State_001AAF60;

s64 func_001AAF60(s32 arg0) {
    s8 value;
    State_001AAF60 *state = (State_001AAF60 *)&D_00317250;

    if (arg0 > 0) {
        value = state->values[state->selected];
    } else if (arg0 < 0) {
        value = state->negative;
    } else {
        value = state->zero;
    }
    return value;
}

INCLUDE_ASM("asm/nonmatchings/main_037", func_001AAFA0);

INCLUDE_ASM("asm/nonmatchings/main_037", func_001AB1D0);

INCLUDE_ASM("asm/nonmatchings/main_037", func_001AC290);

INCLUDE_ASM("asm/nonmatchings/main_037", func_001AC510);

INCLUDE_ASM("asm/nonmatchings/main_037", func_001AC560);

void func_001AC600(void) {

}

INCLUDE_ASM("asm/nonmatchings/main_037", func_001AC610);

void func_001AC6F0(void) {

}

INCLUDE_ASM("asm/nonmatchings/main_037", func_001AC700);

void func_001ACC50(void) {
    func_00209D30(func_001ACC80(func_00209D20()));
}

INCLUDE_ASM("asm/nonmatchings/main_037", func_001ACC80);

INCLUDE_ASM("asm/nonmatchings/main_037", func_001AD670);

INCLUDE_ASM("asm/nonmatchings/main_037", func_001AD960);

INCLUDE_ASM("asm/nonmatchings/main_037", func_001ADA80);

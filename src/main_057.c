#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_057", func_00209D20);

INCLUDE_ASM("asm/nonmatchings/main_057", func_00209D30);

typedef struct {
    u8 padding[0x244];
    f32 field_244;
    s32 field_248;
} Data_00209D40;

f32 func_00209D40(s32 *arg0) {
    Data_00209D40 *data = (Data_00209D40 *)D_00325F50;

    if (arg0 != NULL) {
        *arg0 = data->field_248;
    }
    return data->field_244;
}

s32 func_00209D60(s32 *arg0, s32 *arg1) {
    *arg0 = D_0032618C;
    *arg1 = D_00326190;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_057", func_00209D80);

s32 func_00209E30(s32 *arg0, s32 *arg1) {
    *arg0 = D_003261B0;
    *arg1 = D_003261B4;
    return 1;
}

typedef struct {
    u8 pad[0x10];
    s32 index;
} State_00209E50;

typedef struct {
    s8 enabled : 1;
} Flags_00209E50;

extern State_00209E50 D_00325F20;
extern Flags_00209E50 D_00325F40;

s32 func_00209E50(void) {
    u8 *base = D_00325F50;
    State_00209E50 *state = &D_00325F20;
    s32 var_v0;

    if (D_00325F40.enabled != 0) {
        var_v0 = state->index;
    } else {
        var_v0 = 0;
    }
    return *(s32 *)(base + 0x268) + (var_v0 << 5);
}

INCLUDE_ASM("asm/nonmatchings/main_057", func_00209E90);

INCLUDE_ASM("asm/nonmatchings/main_057", func_00209EF0);

INCLUDE_ASM("asm/nonmatchings/main_057", func_00209F60);

INCLUDE_ASM("asm/nonmatchings/main_057", func_00209F70);

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020A0B0);

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020A280);

void *func_0020A340(void *arg0, void *arg1) {
    *(s32 *)((u8 *)arg0 + 0) = 0x10000002;
    *(s32 *)((u8 *)arg0 + 4) = 0;
    *(s32 *)((u8 *)arg0 + 8) = 0;
    *(s32 *)((u8 *)arg0 + 0xC) = 0x51000002;
    *(s64 *)((u8 *)arg0 + 0x10) = ((s64)0x10000000 << 32) | 0x8001;
    *(s64 *)((u8 *)arg0 + 0x18) = 0xE;
    *(s64 *)((u8 *)arg0 + 0x20) = ((s64)((u8 *)arg1)[0] << 16) |
        ((s64)((u8 *)arg1)[2] | ((s64)((u8 *)arg1)[1] << 8));
    *(s64 *)((u8 *)arg0 + 0x28) = 0x3D;
    return (u8 *)arg0 + 0x30;
}

void func_0020A3B0(s64 arg0) {
    u8 *base = D_00325F50;
    u16 *p;

    func_00185578(0, 0);
    if (D_003261BC & 1) {
        p = (u16 *)(base + 0x60);
    } else {
        p = (u16 *)(base + 0x150);
    }
    func_00185890(D_00325E80, (*p & 0x1FF) << 5, 10, 10, 0, 0, 0x280, 0x1C0);
    func_0017BB60(0);
    func_001859D0(D_00325E80, arg0 & 0x0FFFFFFF);
    func_00185578(0, 0);
}

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020A470);

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020A610);

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020A760);

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020A870);

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020A9E0);

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020AA30);

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020AD10);

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020B000);

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020B1E0);

u8 *func_0020B300(u8 *arg0, u8 *arg1, s32 arg2) {
    if (arg2 > 0) {
        do {
            arg2 -= 1;
            *arg0 = *arg1;
            arg1 += 1;
            arg0 += 1;
        } while (arg2 > 0);
    }
    return arg0;
}

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020B340);

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020B380);

s8 *func_0020B3C0(s8 *arg0, s8 arg1, s32 arg2) {
    if (arg2 > 0) {
        do {
            *arg0 = arg1;
            arg2 -= 1;
            arg0 += 1;
        } while (arg2 > 0);
    }
    return arg0;
}

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020B400);

s64 *func_0020B440(s64 *arg0, s64 arg1, s32 arg2) {
    while (arg2 > 0) {
        *arg0 = arg1;
        arg2 -= 1;
        arg0++;
    }
    return arg0;
}

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020B480);

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020B550);

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020B620);

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020B730);

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020B840);

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020BA70);

s32 func_0020BA80(void) {
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020BA90);

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020BAD0);

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020BAF0);

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020BB50);

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020BBA0);

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020BBB0);

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020BC00);

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020BCF0);

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020BDE0);

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020C630);

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020C750);

typedef struct {
    f32 rotation[12];
    f32 translation[3];
} Matrix_0020C8F0;

void func_0020BBB0(void *arg0);

void func_0020C8F0(void *arg0, f32 *arg1) {
    Matrix_0020C8F0 *matrix = arg0;

    func_0020BBB0(arg0);
    matrix->translation[0] = arg1[0];
    matrix->translation[1] = arg1[1];
    matrix->translation[2] = arg1[2];
}

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020C940);

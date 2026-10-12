#include "common.h"

s32 func_00209D20(void) {
    return D_003261D0;
}

void func_00209D30(s32 arg0) {
    D_003261D0 = arg0;
}

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

s32 func_00209D80(s32 *arg0, s32 *arg1) {
    typedef struct Flags_00209D80 {
        s8 active : 1;
        s8 useSaved : 1;
    } Flags_00209D80;

    typedef struct State_00209D80 {
        u8 pad0[0x18];
        s32 value;
        u8 pad1[4];
        Flags_00209D80 flags;
    } State_00209D80;

    extern State_00209D80 D_00325F20;
    extern Flags_00209D80 D_00325F40;
    extern s32 D_003261A8;

    State_00209D80 *state;
    s32 value;

    value = D_003261A8;
    state = &D_00325F20;
    if (D_00325F40.active) {
        if (state->flags.useSaved) {
            value = state->value;
        }
    }
    *arg0 = 0;
    switch (value) {
    case 0x30:
        *arg1 = 0x7FFFFFFF;
        break;
    case 0x31:
        *arg1 = 0xFFFFFF;
        break;
    case 0x32:
    case 0x3A:
        *arg1 = 0xFFFF;
        break;
    }
    return 1;
}

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

typedef struct {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
    s32 timer;
    u8 pad08[0xE8];
} Slot_00209E90;

extern Slot_00209E90 D_00326050[2];

s32 func_00209E90(u8 arg0, u8 arg1, u8 arg2, u8 arg3) {
    D_00326050[0].r = arg0;
    D_00326050[0].g = arg1;
    D_00326050[0].b = arg2;
    D_00326050[0].a = arg3;
    D_00326050[0].timer = 0;
    D_00326050[1].r = arg0;
    D_00326050[1].g = arg1;
    D_00326050[1].b = arg2;
    D_00326050[1].a = arg3;
    D_00326050[1].timer = 0;
    return 1;
}

typedef struct State_00209EF0 {
    u8 pad00[0x60];
    u16 value60;
    u8 pad62[0xEE];
    u16 value150;
    u8 pad152[0xFE];
    s32 value250;
    s32 pad254;
    s32 value258;
    u8 pad25C[0x10];
    s32 flags26C;
} State_00209EF0;

s32 func_00209EF0(s32 arg0, s32 *arg1, s32 *arg2, s32 *arg3) {
    State_00209EF0 *state = (State_00209EF0 *)D_00325F50;
    u16 *var_v0;

    if (arg1 != NULL) {
        if ((state->flags26C & 1) == (arg0 ? 1 : 0)) {
            var_v0 = &state->value150;
        } else {
            var_v0 = &state->value60;
        }
        *arg1 = (*var_v0 & 0x1FF) << 5;
    }
    if (arg2 != NULL) {
        *arg2 = state->value250;
    }
    if (arg3 != NULL) {
        *arg3 = state->value258;
    }
    return 1;
}

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

s32 func_0020B000(s32 arg0) {
    extern void func_00187828();

    D_00326180 = 0x63721405 | ((u64)0x72630514 << 32);
    func_001875F8(D_00325F00, arg0);
    func_00187660(D_00325F00, 0);
    func_001877F8(D_00325F00, 0x01000404);
    func_00187810(D_00325F00, 0x20000000);
    func_00187810(D_00325F00, 0x05000000);
    func_00187778(D_00325F00, 2, 3);
    func_00187858(D_00325F00, 0);
    *(u64 *)&D_00325EF0 = 0x8000 | ((u64)0x10000000 << 32);
    *((u64 *)&D_00325EF0 + 1) = 0xE;
    func_001876B8(D_00325F00, D_00325EF0);
    func_00187828(D_00325F00, 0x46, 1);
    func_00187828(D_00325F00, 0x40, ((u64)(D_0032618C - 1) << 16) | ((u64)(D_00326190 - 1) << 48));
    func_00187828(D_00325F00, 0x1A, 1);
    func_00187828(D_00325F00, 0x3B, (u64)0x80 << 32);
    func_00187828(D_00325F00, 0x3D, 0xC0C0C0);
    func_00187828(D_00325F00, 0x45, 1);
    func_00187828(D_00325F00, 0x44, D_00326180);
    func_001876D0(D_00325F00);
    func_001878B0(D_00325F00);
    return func_00187608(D_00325F00);
}

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

void *func_0020B400(void *dst, s32 val, s32 count) {
    s32 *p = dst;

    while (count > 0) {
        *p++ = val;
        count--;
    }
    return p;
}

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

f32 func_0020B730(f32 angle) {
    s32 phase;
    f32 sign;
    s32 fraction;
    f32 weight;
    f32 *entry;
    f32 lower;
    f32 upper;

    phase = (s16)func_001A22C0(0.5f + ((65536.0f * angle) / 6.2831855f));
    sign = 1.0f;
    if (phase < 0) {
        sign = -1.0f;
        phase = -phase;
    }
    if (phase > 0x4000) {
        phase = 0x8000 - phase;
    }
    if ((phase & 0x3FFF) == 0) {
        if (phase == 0x4000) {
            return sign;
        }
        sign = 0.0f;
    } else {
        fraction = phase & 0xF;
        weight = fraction;
        entry = &D_00294050[phase >> 4];
        lower = entry[0];
        upper = entry[1];
        sign = (sign * (lower * (16 - fraction) + upper * weight)) / 16.0f;
    }
    return sign;
}

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020B840);

s32 func_0020BA70(void) {
    D_0032A220 = 0;
    return 1;
}

s32 func_0020BA80(void) {
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020BA90);

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020BAD0);

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020BAF0);

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020BB50);

s32 func_0020BBA0(void) {
    D_0032A220 = 0;
    return 1;
}

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

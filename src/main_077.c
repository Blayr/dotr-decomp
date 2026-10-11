#include "common.h"

s32 func_0026EA80(s32 arg0, s32 arg1) {
    s32 temp_s0;
    u8 *temp_v0;
    u8 temp_s1;

    temp_v0 = func_001DD0E0(arg1);
    if (temp_v0 == NULL) {
        return 0;
    }
    temp_s1 = *temp_v0;
    temp_s0 = temp_s1 & 0x1F;
    if (temp_s0 == (func_001E0700(arg0, 0) & 0x1F)) {
        if (((s32) temp_s1 >> 5) == 0) {
            return func_00271830(arg0);
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_077", func_0026EB10);

s32 func_0026EEA0(void *arg0, s32 arg1, s32 arg2) {
    ((s32 *)arg0)[0] = 0x96;
    ((s32 *)arg0)[1] = 0;
    ((s32 *)arg0)[2] = (arg1 << 8) | arg2;
    ((s32 *)arg0)[3] = 0;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_077", func_0026EED0);

INCLUDE_ASM("asm/nonmatchings/main_077", func_0026EFD0);

s32 func_0026F600(s32 arg0, s32 *arg1) {
    extern s32 func_001DE740(s32);
    s32 flags;

    flags = func_001DE740(arg0);
    arg1[0] = 0x3E7;
    arg1[1] = 0;
    arg1[2] = 0;
    arg1[3] = 0;
    if (!(flags & 0x80) && func_001DF110(arg0) < 5) {
        if (arg1 != NULL) {
            arg1[0] = 0x72;
            arg1[1] = func_001DE540();
            arg1[2] = 0;
            arg1[3] = 0;
        }
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_077", func_0026F690);

s32 func_0026FA70(s32 arg0, s32 arg1) {
    return func_0026FA80(arg0 & 0xFFF, arg1);
}

typedef struct {
    u8 flags;
    u8 pad;
    u8 unused : 4;
    u8 value : 4;
} Flags_0026FA80;

s32 func_00271830(s32);

s32 func_0026FA80(s32 arg0, s32 arg1) {
    s32 owner;
    s32 value;
    Flags_0026FA80 *data;

    data = (Flags_0026FA80 *)func_001DD0E0(arg0);
    if (data == NULL) {
        return 0xFF;
    }
    value = data->value;
    if ((data->flags >> 5) == 0) {
        owner = data->flags & 0x1F;
        if (owner == (func_001E0700(arg1, 0) & 0x1F)) {
            value -= func_00271830(arg1);
        }
    }
    return value;
}

s32 func_0026FB10(s32 arg0, s32 arg1) {
    s32 temp_s0;

    temp_s0 = func_0026FA80(arg1, arg0);
    return (func_001DE5C0(arg0) < temp_s0) ? 0 : 1;
}

s32 func_0026FB60(s32 arg0, s32 arg1) {
    s32 temp_s0;

    temp_s0 = func_0026FA80(arg1 & 0xFFF, arg0);
    return (func_001DE5C0(arg0) < temp_s0) ? 0 : 1;
}

INCLUDE_ASM("asm/nonmatchings/main_077", func_0026FBB0);

s32 func_0026FC10(s32 arg0) {
    u8 *p;

    if (arg0 == 0x3E7) {
        return 0;
    }
    p = func_001DD0E0(arg0);
    if (p == NULL) {
        return 0;
    }
    if ((p[0] >> 5) == 0) {
        if (*(u16 *)(p + 4) == 0xFFFF) {
            return 2;
        }
        return 1;
    }
    return 0;
}

void *func_0026FC90(s32 arg0, s32 arg1) {
    u8 data[0x60];

    if (arg0 == 0x3E7) {
        return NULL;
    }
    func_001DCD70(data, arg0);
    return data + 8 + arg1 * 8;
}

s32 func_0026FCE0(s32 arg0) {
    u8 *temp_v0;

    if (arg0 == 0x3E7) {
        return 0U;
    }
    temp_v0 = func_001DD0E0();
    if (temp_v0 == NULL) {
        return 0U;
    }
    return *temp_v0;
}

void func_0026FD30(s32 arg0, s32 *arg1) {
    s32 index;
    s32 count;
    s32 value;

    index = 0;
    count = 0;
    do {
        value = func_001DF0C0(arg0, index) & 0xFFF;
        if (value != 0x3E7) {
            arg1[count] = value;
            count++;
        }
        index++;
    } while (index < 5);
    index = func_001DF110(arg0);
    count = 0;
    while (index < func_0026FE20(arg0)) {
        arg1[index] = func_001DE9E0(arg0, count);
        index++;
        count++;
    }
}

s32 func_0026FE20(s32 arg0) {
    s32 temp_s0;
    s32 var_v0;

    temp_s0 = func_001DF110();
    var_v0 = temp_s0 + func_001DE9C0(arg0);
    if (var_v0 >= 5) {
        var_v0 = 5;
    }
    return var_v0;
}

INCLUDE_ASM("asm/nonmatchings/main_077", func_0026FE70);

INCLUDE_ASM("asm/nonmatchings/main_077", func_00270030);

INCLUDE_ASM("asm/nonmatchings/main_077", func_00270260);

INCLUDE_ASM("asm/nonmatchings/main_077", func_00270C30);

typedef struct State_00271630 {
    u8 pad[4];
    u16 count;
    u8 handle;
} State_00271630;

void func_0024F430(u32, s32);
void func_00255960(void *);
u8 func_00255A30(s32 *, void *);
void func_00255AC0(void *, s32);

s32 func_00271630(void *arg0, void *arg1, s32 arg2) {
    s32 values[4];
    State_00271630 *state = arg1;
    s32 *packet = values;
    u32 value;

    values[0] = 0x3E7;
    values[1] = 0;
    values[2] = 0;
    values[3] = 0;

    if (arg2 >= 0) {
        func_00255960(state);
        func_00255AC0(state, 0x25B);
        return 1;
    }

    switch (state->count) {
    case 0:
        if (func_00255B50(state) == 1) {
            packet[0] = 0x25B;
            packet[1] = 0;
            packet[2] = *(u32 *)((u8 *)arg0 + 8);
            packet[3] = 0;
            state->handle = func_00255A30(packet, state);
            state->count++;
        }
        break;
    default:
        if (func_001F51D0(state->handle) != 0) {
            return 1;
        }
        value = *(u32 *)((u8 *)arg0 + 8);
        func_0024F430(value >> 8, value & 0xFF);
        func_001E4530();
        return 0;
    }
    return 1;
}

s32 func_00271740(s32 arg0, s32 arg1) {
    if (func_00266F70(0x58, (arg1 == 0) ? 1 : 0) > 0) {
        return 0;
    }
    return func_001E0C00(arg1, 0, arg0, 0);
}

s32 func_002717A0(s32 arg0) {
    s32 ret;

    switch (arg0) {
    case 1:
    case 7:
        ret = 5;
        break;
    case 9:
        ret = 0;
        break;
    case 10:
        ret = 1;
        break;
    case 16:
        ret = 4;
        break;
    case 20:
        ret = 9;
        break;
    default:
        ret = 7;
        break;
    }

    return ret;
}

INCLUDE_ASM("asm/nonmatchings/main_077", func_00271830);

INCLUDE_ASM("asm/nonmatchings/main_077", func_00271950);

s32 func_00271A40(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_s0;

    temp_s0 = func_001E1090(arg0, 0);
    if (func_00271740(9, arg0) != 0) {
        return (func_00271950(temp_s0 & 0xFF, temp_s0 >> 8, arg1, arg2, 5) != 0) ? 1 : 0;
    } else {
        return (func_00271950(temp_s0 & 0xFF, temp_s0 >> 8, arg1, arg2, 3) != 0) ? 1 : 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_077", func_00271AF0);

INCLUDE_ASM("asm/nonmatchings/main_077", func_00271C90);

INCLUDE_ASM("asm/nonmatchings/main_077", func_00271E40);

s32 func_00271F00(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    extern s32 func_001E0690(s32, s32);

    if (func_00271A40(arg1, arg0 & 0xFF, arg0 >> 8) != 0 && func_00271740(arg3, arg1) != 0 &&
        arg2 == (func_001E0690(arg1, 0) & 0x1F)) {
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_077", func_00271F90);

s32 func_00272050(s32 arg0, s32 arg1) {
    extern s32 func_001E0690(s32, s32);

    switch (func_001E0690(arg0, 0) & 0x1F) {
    case 8:
        return (arg1 == 2) ? 1 : 0;
    case 11:
        return (arg1 == 0x10) ? 1 : 0;
    case 17:
        return ((u32)(arg1 - 5) < 2U) ? 1 : 0;
    case 19:
        return (arg1 == 0) ? 1 : 0;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_077", func_002720F0);

u32 func_00272210(s32 arg0, s32 arg1) {
    s32 i;
    s32 count;
    s32 result;
    s32 owner;
    s32 y;
    s32 x;
    s32 position;

    count = func_0024E910(arg0);
    result = arg0;
    for (i = 0; i < count; i++) {
            position = func_0024EC50(arg0, i);
            x = position >> 8;
            y = position & 0xFF;
            owner = func_0024DE70(x, y);
            if ((func_00271E40(x, y, 0xB) != 0) && (owner != arg1)) {
                result = func_0024C7D0((u32) result, x, y);
            } else if ((func_00267700(x, y) != 0) && (owner != arg1)) {
                result = func_0024C7D0((u32) result, x, y);
            }
    }
    return (u32) result;
}

u32 func_00272330(s32 arg0, s32 arg1) {
    s32 i;
    s32 remaining;
    s32 card;
    s32 position;
    s32 y;
    s32 x;
    s32 count;
    s32 packed;

    count = func_0024E910(arg0);
    remaining = arg0;
    for (i = 0; i < count; i++) {
            packed = func_0024EC50(arg0, i);
            x = packed >> 8;
            y = packed & 0xFF;
            card = func_0024DE70(x, y);
            position = func_001E1090(card, 0);
            if (func_00271E40(x, y, 0xB) != 0 && card != arg1) {
                func_001E42C0(0, -0x78, 0x50, 0x10E);
                func_00260490(position & 0xFF, position >> 8, 0,
                             func_00271740(9, card), 1, 1, 0xB);
                remaining = func_0024C7D0((u32) remaining, x, y);
            } else if (func_00267700(x, y) != 0 && card != arg1) {
                func_001E42C0(0, 0, 0x50, func_001DE210(0x53));
                remaining = func_0024C7D0((u32) remaining, x, y);
            }
    }
    return (u32) remaining;
}

s32 func_002724C0(s32 arg0) {
    return func_00271740(9, arg0) ? 5 : 3;
}

INCLUDE_ASM("asm/nonmatchings/main_077", func_002724F0);

INCLUDE_ASM("asm/nonmatchings/main_077", func_00272CC0);

INCLUDE_ASM("asm/nonmatchings/main_077", func_00273460);

INCLUDE_ASM("asm/nonmatchings/main_077", func_002738B0);

INCLUDE_ASM("asm/nonmatchings/main_077", func_00273E60);

INCLUDE_ASM("asm/nonmatchings/main_077", func_002747A0);

typedef struct {
    u32 unknown;
    u16 first;
    u16 padding6;
    u16 second;
    u16 paddingA;
    u32 flags;
} Source_002755D0;

typedef struct {
    u16 first;
    u16 second;
    u8 padding[0xFE];
    u16 counter;
} State_002755D0;

typedef struct {
    s32 id;
    s32 x;
    s32 y;
    s32 z;
} Params_002755D0;

void func_0024F370(s32, s32);
void func_002500C0(s32, s32, s32, s32, s32);
void func_00255960(void *);
void func_00260490(s32, s32, s32, s32, s32, s32, s32);

static inline s32 update_002755D0(void *arg0, void *arg1, void *params_arg, s32 arg2) {
    State_002755D0 *state = arg1;
    Source_002755D0 *source = arg0;
    Params_002755D0 *values = params_arg;
    s32 card;
    s32 position;
    u16 counter;

    if (source == NULL || state == NULL || values == NULL) {
        func_001E4530();
        return 0;
    }
    if (arg2 >= 0) {
        func_00255960(state);
        if ((source->flags & 1) == 1) {
            state->first = source->second;
            state->second = source->first;
        } else {
            state->first = source->first;
            state->second = source->second;
        }
        if ((source->flags >> 1) != 0) {
            card = func_0024DE70((s32) state->second >> 8, state->second & 0xFF);
            position = func_001E1090(card, 0);
            func_00260490(position & 0xFF, position >> 8, 0,
                         func_00271740(9, card), 1, 1, 11);
        }
        func_002500C0((s32) state->first >> 8, state->first & 0xFF, -1, 1, 3);
        return 1;
    }
    counter = state->counter;
    state->counter = counter + 1;
    if ((s32) counter < 16) {
        return 1;
    }
    func_0024F370((s32) state->first >> 8, state->first & 0xFF);
    func_001E4530();
    return 0;
}

static inline void init_params_002755D0(void *params_arg) {
    Params_002755D0 *values = params_arg;

    values->id = 999;
    values->x = 0;
    values->y = 0;
    values->z = 0;
}

s32 func_002755D0(void *arg0, void *arg1, s32 arg2) {
    Params_002755D0 values;
    Params_002755D0 *params = &values;

    init_params_002755D0(params);
    return update_002755D0(arg0, arg1, params, arg2);
}

INCLUDE_ASM("asm/nonmatchings/main_077", func_00275740);

INCLUDE_ASM("asm/nonmatchings/main_077", func_002759D0);

INCLUDE_ASM("asm/nonmatchings/main_077", func_00275D00);

s32 func_00275E30(void *arg0) {
    if (func_0027F830(func_001DE540()) == 1) {
        return 1;
    }
    *(s16 *)((u8 *)arg0 + 0x1A2) = 0;
    return func_00275E80(arg0);
}

INCLUDE_ASM("asm/nonmatchings/main_077", func_00275E80);

s32 func_002760E0(u16 value, u16 *entries) {
    s32 i = 0;

    do {
        if (value == *entries) {
            return 1;
        }
        i++;
        entries += 8;
    } while (i < 22);

    return 0;
}

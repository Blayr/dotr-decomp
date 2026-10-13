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

s32 func_0026EED0(s32 arg0) {
    extern s32 func_001DE4E0();
    extern s32 func_00215D30();
    extern s32 func_0026EFD0(s32);
    s32 state;
    s32 value;

    state = func_001DE4E0(func_001DE540());
    if (state < 0x20 && state != 0x13 && state != 1) {
        return -1;
    }
    value = func_00215D30(arg0, func_002159D0(arg0, func_002158B0(arg0)));
    if (state > 99 && func_00271740(3, arg0) == 0) {
        return -1;
    }
    if (func_001DF470(arg0) < 1000) {
        if ((state = func_0026EFD0(arg0)) >= 0) {
            return state | (func_00250860(0, value - 8) << 4);
        }
    }
    return -1;
}

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

typedef struct CardStats_0026FBB0 {
    u8 padding[8];
    u16 attack;
    u16 defense;
} CardStats_0026FBB0;

u32 func_0026FBB0(s32 arg0) {
    CardStats_0026FBB0 *card;

    if (arg0 == 0x3E7) {
        return 0U;
    }
    card = (CardStats_0026FBB0 *)func_001DD0E0(arg0);
    if (card == NULL) {
        return 0U;
    }
    return ((card->attack & 0x1FFF) << 16) | (card->defense & 0x1FFF);
}

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
    temp_v0 = func_001DD0E0(arg0);
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

    temp_s0 = func_001DF110(arg0);
    var_v0 = temp_s0 + func_001DE9C0(arg0);
    if (var_v0 >= 5) {
        var_v0 = 5;
    }
    return var_v0;
}

INCLUDE_ASM("asm/nonmatchings/main_077", func_0026FE70);

typedef struct {
    u32 unused;
    u32 value1;
    u32 value2;
    s32 flags;
} Input_00270030;

typedef struct {
    u8 pad0[4];
    u16 state;
    u8 type;
    u8 pad7;
    u8 pad8[0x18];
    s32 once;
    u8 pad24[0xAC];
    s32 count;
} Object_00270030;

extern void func_0024F430(u32, s32);

s32 func_00270030(void *src, void *obj, s32 mode) {
    s32 words[4];
    s32 *message = words;
    Input_00270030 *input = src;
    Object_00270030 *target = obj;
    s32 count;
    u32 color;

    message[0] = 0x3E7;
    message[1] = 0;
    message[2] = 0;
    message[3] = 0;

    if (mode >= 0) {
        func_00255960(obj);
        func_00255AC0(obj, 0x258);
        message[0] = 0x25A;
        message[1] = input->value1;
        message[2] = input->value2;
        message[3] = 0;
        func_0027EB00((u8 *)obj + 0x110, message, 0);
        goto common_return;
    }

    switch (target->state) {
    case 0:
        goto no_state;
    default:
        goto active;
    }

no_state:
    if (func_00255B50(obj) == 1) {
        message[0] = 0x258;
        message[1] = input->value1;
        message[2] = input->value2;
        message[3] = 0;
        *(u8 *)((u8 *)obj + 6) = func_00255A30(message, obj);
        target->once = 0;
        target->state = target->state + 1;
    }

    message[0] = 0x25A;
    message[1] = input->value1;
    message[2] = input->value2;
    message[3] = 0;
    func_0027EB00((u8 *)obj + 0x110, message, -1);
    return 1;

active:
    if (func_001F51D0(target->type) != 0) {
        count = target->count;
        target->count = count + 1;
        switch (count) {
        case 1:
            func_00217710(1, 0x4C);
            break;
        case 0x12:
            func_00217710(1, 0x3A);
            break;
        case 0x50:
            func_00217710(1, 0x3B);
            break;
        }

        if (func_001F52D0(target->type) == 2 && target->once == 0) {
            target->once = 1;
            color = input->value1;
            func_0024F430(color >> 8, color & 0xFF);
            color = input->value2;
            func_0024F430(color >> 8, color & 0xFF);
            return (input->flags << 16) | 2;
        }
        return 1;
    } else {
        func_001E4530();
        return 0;
    }

common_return:
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_077", func_00270260);

INCLUDE_ASM("asm/nonmatchings/main_077", func_00270C30);

typedef struct State_00271630 {
    u8 pad[4];
    u16 count;
    u8 handle;
} State_00271630;

void func_0024F430(u32, s32);

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

s32 func_00271830(s32 arg0) {
    extern s32 func_001E08F0(s32, s32, s32);

    if (func_00271740(8, arg0) != 0) {
        switch (func_001E0690(arg0, 0) & 0x1F) {
        case 0:
        case 6:
        case 12:
        case 14:
            return func_001E08F0(arg0, 0, 0) > 6 ? 2 : 1;
        case 4:
        case 13:
            if (func_001E08F0(arg0, 0, 0) > 5) {
                return 2;
            }
            return 1;
        case 20:
            return 1;
        default:
            return 0;
        }
    }
    return 0;
}

s32 func_00271950(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 x;
    s32 half;
    s32 xEnd;
    s32 yStart;
    s32 yEnd;
    s32 y;

    half = arg4 >> 1;
    x = func_00250860(0, arg0 - half);
    if (arg0 + half >= 7) {
        xEnd = 6;
    } else {
        xEnd = arg0 + half;
    }
    yStart = func_00250860(0, arg1 - half);
    if (arg1 + half >= 7) {
        yEnd = 6;
    } else {
        yEnd = arg1 + half;
    }
    for (; x <= xEnd; x++) {
        for (y = yStart; y <= yEnd; y++) {
            if (x == arg2 && y == arg3) {
                return 1;
            }
        }
    }
    return 0;
}

s32 func_00271A40(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_s0;

    temp_s0 = func_001E1090(arg0, 0);
    if (func_00271740(9, arg0) != 0) {
        return (func_00271950(temp_s0 & 0xFF, temp_s0 >> 8, arg1, arg2, 5) != 0) ? 1 : 0;
    } else {
        return (func_00271950(temp_s0 & 0xFF, temp_s0 >> 8, arg1, arg2, 3) != 0) ? 1 : 0;
    }
}

s32 func_00271AF0(void *arg0, s32 arg1, s32 arg2) {
    extern s32 func_001E08F0();
    s32 score;
    s32 kind;
    s32 player;
    s32 other;

    score = 0;
    if (arg0 == NULL) {
        return 0;
    }
    player = func_00250370(arg0);
    kind = ((u8 *)arg0)[0x3E] & 0x1F;
    other = player == 0 ? 1 : 0;
    if (func_00271F00((arg2 << 8) | arg1, player, kind, 10)) {
        score += func_001E08F0(player, 0, 0) * 100 >= 500 ? 500 : func_001E08F0(player, 0, 0) * 100;
    }
    if (func_00271A40(other, arg1, arg2)) {
        if (func_00271740(14, other) && func_00271C90(other, kind)) {
            score -= func_001E08F0(other, 0, 0) * 100 >= 500 ? 500 : func_001E08F0(other, 0, 0) * 100;
        }
    }
    return score;
}

INCLUDE_ASM("asm/nonmatchings/main_077", func_00271C90);

s32 func_00271E40(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_s0;
    s32 temp_s1;
    s32 temp_s2;

    temp_s0 = func_001E1090(arg0, arg1);
    temp_s2 = func_0024DE70(arg0, arg1);
    temp_s1 = func_001E0700(arg0, arg1) & 0x1F;
    if (func_00271A40(temp_s2, temp_s0 & 0xFF, temp_s0 >> 8) != 0 && func_00271740(arg2, temp_s2) != 0 &&
        temp_s1 == (func_001E0690(temp_s2, 0) & 0x1F)) {
        return 1;
    }
    return 0;
}

s32 func_00271F00(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {

    if (func_00271A40(arg1, arg0 & 0xFF, arg0 >> 8) != 0 && func_00271740(arg3, arg1) != 0 &&
        arg2 == (func_001E0690(arg1, 0) & 0x1F)) {
        return 1;
    }
    return 0;
}

s32 func_00271F90(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 temp_s0;
    s32 temp_s1;

    temp_s1 = func_0024DE70(arg0, arg1);
    temp_s0 = func_001E0700(arg0, arg1) & 0x1F;
    if (func_00271A40(temp_s1, arg2, arg3) != 0 && func_00271740(arg4, temp_s1) != 0 &&
        temp_s0 == (func_001E0690(temp_s1, 0) & 0x1F)) {
        return 1;
    }
    return 0;
}

s32 func_00272050(s32 arg0, s32 arg1) {

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

s32 func_002720F0(s32 arg0, s32 arg1) {
    s32 result;

    switch (func_001E0690(arg0, 0) & 0x1F) {
    case 8:
        result = (arg1 == 7) ? 1 : 0;
        break;
    case 11:
        result = (arg1 == 9) ? 1 : 0;
        break;
    case 17:
        if (arg1 == 2 || arg1 == 19) {
            result = 1;
        } else {
            result = 0;
        }
        break;
    case 18:
        result = (arg1 == 10) ? 1 : 0;
        break;
    case 19:
        result = (arg1 == 18) ? 1 : 0;
        break;
    default:
        result = 0;
        break;
    }
    return result;
}

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

typedef struct Context_00273460 {
    u8 pad0[8];
    s32 cards;
} Context_00273460;

typedef struct State_00273460 {
    u16 alpha;
    u16 pad2;
    u16 phase;
    u8 ids[0x1A];
    s32 cards[45];
    u8 count;
    u8 padD5[0x2D];
    u16 timer;
} State_00273460;

typedef struct Setup_00273460 {
    s32 card;
    s32 x;
    s32 y;
    s32 z;
} Setup_00273460;

void func_0024F370(s32, s32);

s32 func_00273460(void *arg0, void *arg1, s32 arg2) {
    Setup_00273460 setup;
    s32 complete;
    Setup_00273460 *config = &setup;
    State_00273460 *walk;
    u8 *id;
    s32 index;
    s32 card;
    State_00273460 *state = arg1;
    Context_00273460 *context = arg0;

    setup.card = 999;
    setup.x = 0;
    setup.y = 0;
    setup.z = 0;
    complete = 0;
    func_001DE7E0(0);
    if (arg2 >= 0) {
        func_00255960(state);
        func_00260020(context, state, arg2, -1, 1, 1);
        state->alpha = 128;
        func_00255AC0(state, 612);
        for (arg2 = 0; arg2 < func_0024E910(context->cards); arg2++) {
            card = func_0024EC50(context->cards, arg2);
            func_001F5970(card, 0);
            func_002516D0(card >> 8, card & 255, 1);
        }
        func_00260740(30);
        return 1;
    }
    switch (state->phase) {
    case 0:
        arg2 = 0;
        if (state->alpha > 48) {
            state->alpha -= 15;
        } else {
            for (arg2 = 0; arg2 < func_0024E910(context->cards); arg2++) {
                if (func_001F5EC0(func_0024EC50(context->cards, arg2)) != 0) {
                    complete++;
                }
            }
            if (complete == func_0024E910(context->cards)) {
                if (func_00255B50(state) == 1) {
                    if (state->timer++ >= 46) {
                        if (complete == 1) {
                            func_00260AF0(0, func_0024EC50(context->cards, 0), 100, 180);
                        }
                        func_001E42C0(0, -120, 80, 276);
                        func_0025F720(context, state, config, 612);
                        state->timer = 0;
                        state->phase++;
                    }
                }
            }
            state->alpha = 48;
        }
        if (state->alpha < 48) {
            state->alpha = 48;
        }
        func_001F6CF0((u8)state->alpha);
        break;
    case 1:
        index = 0;
        walk = state;
        for (; index < state->count; index++) {
            id = &state->ids[index];
            if (func_001F51D0(*id) == 1) {
                func_00261680((u16)walk->cards[0]);
                if ((walk->cards[0] >> 16) == 0) {
                    if (state->timer++ >= 32) {
                        card = walk->cards[0];
                        func_002500C0((card & 65535) >> 8, card & 255, -1, 1, 3);
                        walk->cards[0] |= 0x10000;
                    }
                }
                if (func_001F52D0(*id) == 2) {
                    card = walk->cards[0];
                    if (card >= 0) {
                        func_001F5970(card & 65535, 1);
                        card = walk->cards[0];
                        func_0024F370((card & 65535) >> 8, card & 255);
                        walk->cards[0] = -1;
                    }
                }
            } else {
                complete++;
            }
            walk = (State_00273460 *)((u8 *)walk + 4);
        }
        if (complete >= state->count) {
            func_00260020(context, state, arg2, 1, 0, 1);
            state->timer = 0;
            func_001E4530();
            func_00260A70(state, 16);
            state->phase++;
        }
        break;
    default:
        state->alpha += 15;
        if (state->alpha > 128) {
            state->alpha = 128;
        }
        func_001F6CF0((u8)state->alpha);
        if (state->alpha == 128) {
            if (state->timer++ > 16 && func_0025FD90() == 1) {
                if (func_001DE780() != 0) {
                    func_001DE7E0(1);
                }
                func_001E4530();
                return 0;
            }
        }
        break;
    }
    return 1;
}

typedef struct Masks_002738B0 {
    u32 unknown;
    u32 first : 22;
    u32 firstFlags : 10;
    s32 second;
    u32 third : 22;
    u32 thirdFlags : 9;
    u32 inverted : 1;
} Masks_002738B0;

typedef struct State_002738B0 {
    u16 player;
    u16 unknown02;
    u16 step;
    u8 handles[0x1A];
    s32 counter;
    u8 unknown24[0xB0];
    u8 count;
    u8 unknownD5[0x2D];
    u16 ticks;
} State_002738B0;

typedef struct Command_002738B0 {
    s32 id;
    s32 flags;
    s32 position;
    s32 argument;
} Command_002738B0;

void func_001E1E70(u32, s32, s32, s32);
void func_0024F370(s32, s32);

s32 func_002738B0(void *arg0, void *arg1, s32 arg2) {
    extern s32 func_001E15E0();
    Command_002738B0 command;
    Command_002738B0 *cmd = &command;
    Masks_002738B0 *masks = arg0;
    State_002738B0 *state = arg1;
    s32 position;
    s32 player;
    s32 position0;
    s32 i;
    s32 ready;
    s32 column;
    s32 row;
    s32 secondIndex;
    s32 secondCount;
    s32 thirdIndex;
    s32 thirdCount;
    s32 firstCount;
    s32 firstIndex;
    s32 packed;

    command.id = 999;
    command.flags = 0;
    command.position = 0;
    command.argument = 0;
    func_001DE7E0(0);
    if (arg2 >= 0) {
        func_00255960(state);
        if (((u32 *)masks)[3] >> 31) {
            player = (func_001DE540() == 0) ? 1 : 0;
        } else {
            player = func_001DE540();
        }
        state->player = player;
        position = func_001E1090(state->player, 0);
        func_00260AF0(0, state->player << 8, 300, 300);
        func_001E42C0(0, -120, 80, 270);
        if (masks->first) {
            func_00260490(position & 0xFF, position >> 8, 0,
                         func_00271740(9, state->player), 1, 1, 16);
        } else if (masks->second) {
            func_00260490(position & 0xFF, position >> 8, 0,
                         func_00271740(9, state->player), 1, 1, 15);
        } else if (masks->third) {
            func_00260490(position & 0xFF, position >> 8, 0,
                         func_00271740(9, state->player), 1, 1, 13);
        }
        func_00255AC0(state, 0x265);
        if (masks->first) {
            func_00255AC0(state, 0x25B);
        }
        if (masks->second) {
            func_00255AC0(state, 0x1F4);
        }
        if (masks->third) {
            func_00255AC0(state, 0x201);
        }
        return 1;
    }

    switch (state->step) {
    case 0:
        if (func_00255B50(state) == 1) {
            position0 = func_001E1090(state->player, 0);
            func_00260490(position0 & 0xFF, position0 >> 8, 0,
                         func_00271740(9, state->player), 0, -1, 16);
            cmd->id = 0x265;
            cmd->flags = 0;
            cmd->position = state->player << 8;
            cmd->argument = 0;
            state->handles[0] = func_00255A30((s32 *)cmd, state);
            state->counter = 0;
            state->step++;
        }
        break;
    case 1:
        if (func_001F51D0(state->handles[0]) == 1) {
            return 1;
        }
        func_00260740(16);
        state->step++;
        return 1;
    case 2:
        if (state->ticks++ >= 16) {
            if (masks->first) {
                func_0025F990(masks, state, (s32 *)cmd, 0x25B);
            }
            if (masks->second) {
                func_0025F720(masks, state, (s32 *)cmd, 0x1F4);
            }
            if (masks->third) {
                func_0025F820(masks, state, (s32 *)cmd, 0x201);
            }
            state->step++;
        }
        return 1;
    case 3:
        i = 0;
        ready = 0;
        while (i < state->count) {
            if (func_001F51D0(state->handles[i]) == 0) {
                ready++;
            }
            i++;
        }
        if (state->count == ready) {
            state->step++;
        }
        return 1;
    case 4:
        firstCount = func_0024E910(masks->first);
        for (firstIndex = 0; firstIndex < firstCount; firstIndex++) {
            packed = func_0024EC50(masks->first, firstIndex);
            func_0024F370(packed >> 8, packed & 0xFF);
        }
        secondCount = func_0024E910(masks->second);
        for (secondIndex = 0; secondIndex < secondCount; secondIndex++) {
            packed = func_0024EC50(masks->second, secondIndex);
            row = packed >> 8;
            column = packed & 0xFF;
            func_001E15E0(row, column, 255);
            func_001E1E70(row, column, 0, 1);
        }
        thirdCount = func_0024E910(masks->third);
        for (thirdIndex = 0; thirdIndex < thirdCount; thirdIndex++) {
            packed = func_0024EC50(masks->third, thirdIndex);
            func_002516D0(packed >> 8, packed & 0xFF, 1);
        }
        func_001E4530();
        func_00260A70(state, 16);
        state->ticks = 0;
        state->step++;
        break;
    default:
        if (state->ticks++ > 16) {
            if (func_001DE780() != 0) {
                func_001DE7E0(1);
            }
            func_001E4530();
            return 0;
        }
        break;
    }
    return 1;
}

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

typedef struct State_00275740 {
    u8 pad0[4];
    u16 phase;
    u8 handle;
    u8 pad7[0xFB];
    u16 timer;
} State_00275740;

typedef struct Request_00275740 {
    s32 command;
    s32 value;
    u32 cell;
    s32 flag;
} Request_00275740;

void func_001E1E70(u32, s32, s32, s32);
void func_0024F370(s32, s32);

s32 func_00275740(u32 *arg0, void *arg1, s32 arg2) {
    extern s32 func_001E1E10();
    extern s32 func_001E1030();
    Request_00275740 data;
    Request_00275740 *request = &data;
    State_00275740 *state = arg1;
    u32 cell;

    data.command = 999;
    data.value = 0;
    data.cell = 0;
    data.flag = 0;
    func_001DE7E0(0);
    if (arg2 >= 0) {
        func_00255960(arg1);
        func_00255AC0(arg1, 0x259);
        func_00255AC0(arg1, 0x25A);
        cell = arg0[1];
        func_002516D0(cell >> 8, cell & 0xFF, 1);
        func_00260AF0(0, arg0[1], 100, 180);
        return 1;
    }

    switch (state->phase) {
    case 0:
        if (func_00255B50(arg1) == 1) {
            cell = arg0[1];
            if (func_001E1E10(cell >> 8, cell & 0xFF) == 0xFF) {
                func_001E42C0(0, -120, 80, 0x103);
                request->command = 0x25A;
                request->value = 0;
                request->cell = arg0[1];
                request->flag = 0;
                state->handle = func_00255A30((s32 *)request, arg1);
                state->phase++;
            }
        }
        break;
    case 1:
        if (func_001F51D0(state->handle) == 1) {
            return 1;
        }
        cell = arg0[1];
        func_001E1E70(cell >> 8, cell & 0xFF, 0, 1);
        cell = arg0[1];
        func_001E42C0(0, -120, 80, func_001DE210(func_001E1030(cell >> 8, cell & 0xFF)));
        request->command = 0x259;
        request->value = 0;
        request->cell = arg0[1];
        request->flag = 1;
        state->handle = func_00255A30((s32 *)request, arg1);
        state->phase++;
        break;
    case 2:
        if (func_001F51D0(state->handle) == 1) {
            return 1;
        }
        cell = arg0[1];
        func_0024F370(cell >> 8, cell & 0xFF);
        state->phase++;
        func_001E4530();
        func_00260A70(arg1, 16);
        break;
    default:
        if (state->timer++ > 16) {
            if (func_001DE780() != 0) {
                func_001DE7E0(1);
            }
            func_001E4530();
            return 0;
        }
        break;
    }
    return 1;
}

typedef struct {
    u32 unused;
    u32 source;
    u32 destination;
    s32 flag;
} Data_002759D0;

typedef struct {
    u8 unused[4];
    u16 phase;
    u8 id;
    u8 padding[0xFB];
    u16 timer;
} State_002759D0;

typedef struct {
    s32 code;
    s32 unused;
    s32 position;
    s32 flags;
} Command_002759D0;

void func_001E1E70(u32, s32, s32, s32);

s32 func_002759D0(void *arg0, void *arg1, s32 arg2) {
    Command_002759D0 storage;
    Command_002759D0 *command = &storage;
    Data_002759D0 *data = arg0;
    State_002759D0 *state = arg1;
    u32 position;
    u16 timer;
    extern s32 func_001DDAC0();
    extern s32 func_001E1E10();
    extern s32 func_001E1030();

    command->code = 0x3E7;
    command->unused = 0;
    command->position = 0;
    command->flags = 0;
    func_001DE7E0(0);
    if (arg2 >= 0) {
        func_00255960(arg1);
        position = data->source;
        func_002516D0(position >> 8, position & 0xFF, 1);
        func_00260AF0(0, data->source, 0x64, 0xB4);
        func_00255AC0(arg1, 0x25A);
        if (data->flag != 0) {
            func_00255AC0(arg1, 0x1F4);
        } else {
            func_00255AC0(arg1, 0x201);
        }
        return 1;
    }
    switch (state->phase) {
    case 0:
        position = data->source;
        if (func_001E1E10(position >> 8, position & 0xFF) == 0xFF) {
            if (func_00255B50(arg1) == 1) {
                func_001E42C0(0, -0x78, 0x50, 0x103);
                command->code = 0x25A;
                command->unused = 0;
                command->position = data->source;
                command->flags = 0;
                state->id = func_00255A30((s32 *)command, arg1);
                state->phase++;
            }
        }
        break;
    case 1:
        if (func_001F51D0(state->id) == 1) {
            return 1;
        }
        position = data->source;
        func_001E1E70(position >> 8, position & 0xFF, 0, 1);
        func_00260AF0(0, data->destination, 0x64, 0xB4);
        if (data->flag != 0) {
            command->code = 0x1F4;
            command->unused = 0;
            command->position = data->destination;
            command->flags = 0;
        } else {
            command->code = 0x201;
            command->unused = 0;
            command->position = data->destination;
            command->flags = 0;
        }
        position = data->source;
        func_001E42C0(0, -0x78, 0x50,
            func_001DE210(func_001E1030(position >> 8, position & 0xFF)));
        state->id = func_00255A30((s32 *)command, arg1);
        state->phase++;
        return 1;
    case 2:
        if (func_001F51D0(state->id) == 1) {
            return 1;
        }
        if (data->flag != 0) {
            position = data->destination;
            func_002503B0(position >> 8, position & 0xFF, 0xFF);
        } else {
            position = data->destination;
            func_001E1E70(position >> 8, position & 0xFF, 3, 0);
            position = data->destination;
            func_001E1E70(position >> 8, position & 0xFF, 5, 0);
        }
        state->phase++;
        func_001E4530();
        func_00260A70(arg1, 0x10);
        break;
    default:
        timer = state->timer;
        state->timer = timer + 1;
        if (timer > 0x10) {
            if (func_001DE780() != 0) {
                func_001DE7E0(1);
            }
            func_001E4530();
            return 0;
        }
        break;
    }
    return 1;
}

typedef struct Entry_00275D00 {
    u16 id;
    u16 value;
    u16 other;
    u16 pad6;
    s32 index;
    u8 flags : 2;
    u8 rest : 6;
    u8 padD[3];
} Entry_00275D00;

typedef struct Data_00275D00 {
    Entry_00275D00 entries[22];
    u16 list[32];
    u8 idx : 5;
    u8 pad1A0 : 3;
    u8 sel : 4;
    u8 pad1A1 : 4;
    u16 count;
} Data_00275D00;

s32 func_00275D00(s32 arg0, void *arg1) {
    Data_00275D00 *data = arg1;
    s32 i;

    if (func_0027F830(arg0) == 1) {
        func_0027F3E0(func_001DE4E0(arg0) & 0xFF, (s32) arg1);
        return 1;
    }
    if (data != NULL) {
        for (i = 0; i < 22; i++) {
            data->entries[i].id = 0xFFFF;
            data->entries[i].value = 0xFF;
            data->entries[i].index = -1;
            data->entries[i].other = 0xFFFF;
            data->entries[i].flags = 0;
        }
        for (i = 0; i < 32; i++) {
            data->list[i] = 0xFFFF;
        }
        data->idx = 0;
        data->sel = 0;
        data->count = 0;
        data->entries[0].id = arg0 << 8;
        data->entries[0].value = func_001E13C0(arg0, 0);
        return 1;
    }
    return -1;
}

s32 func_00275E30(void *arg0) {
    if (func_0027F830(func_001DE540()) == 1) {
        return 1;
    }
    *(s16 *)((u8 *)arg0 + 0x1A2) = 0;
    return func_00275E80(arg0);
}

typedef struct Entry_00275E80 {
    u16 id;
    u16 value;
    u16 other;
    u16 pad6;
    s32 index;
    u8 flags : 2;
    u8 rest : 6;
    u8 padD[3];
} Entry_00275E80;

typedef struct Data_00275E80 {
    Entry_00275E80 entries[22];
    u16 list[32];
    u8 idx : 5;
    u8 pad1A0 : 3;
} Data_00275E80;

s32 func_00275E80(void *arg0) {
    Data_00275E80 *data = arg0;
    s32 owner;
    s32 i;

    owner = func_001DE540();
    if (func_0027F830(owner) == 1) {
        return 1;
    }
    if (data != NULL) {
        data->idx = 0;
        for (i = 0; i < 32; i++) {
            data->list[i] = 0xFFFF;
        }
        for (i = 0; i < 22; i++) {
            if (data->entries[i].id < 0xFFFF) {
                if (func_001DF540(data->entries[i].id >> 8, data->entries[i].id & 0xFF) == 0 ||
                    owner != func_0024DE70(data->entries[i].id >> 8, data->entries[i].id & 0xFF)) {
                    data->entries[i].id = 0xFFFF;
                    data->entries[i].value = 0xFF;
                    data->entries[i].index = -1;
                    data->entries[i].other = 0xFFFF;
                    data->entries[i].flags = 0;
                } else if (func_001E13C0(data->entries[i].id >> 8,
                                         (data->entries[i].id & 0xFF) != data->entries[i].value) != 0) {
                    data->entries[i].value = func_001E13C0(data->entries[i].id >> 8, data->entries[i].id & 0xFF);
                    data->entries[i].index = -1;
                    data->entries[i].other = 0xFFFF;
                    data->entries[i].flags = 0;
                }
            }
        }
        for (i = 0; i < 11; i++) {
            if (owner == func_0024DE70(0, i)) {
                if (func_002760E0(i, (u16 *)data) == 0 && func_001DF540(0, i) != 0) {
                    func_00276120(i, data);
                }
            }
            if (owner == func_0024DE70(1, i)) {
                if (func_002760E0(i | 0x100, (u16 *)data) == 0 && func_001DF540(1, i) != 0) {
                    func_00276120(i | 0x100, data);
                }
            }
        }
        func_002761D0(data);
        return 1;
    }
    return -1;
}

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

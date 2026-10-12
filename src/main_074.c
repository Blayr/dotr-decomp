#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_074", func_00254890);

s32 func_00254B20(void *arg0, s32 arg1) {
    s32 result;
    s32 *src;
    s32 selections[3];
    s32 *selection;
    u32 selector;
    s32 i;
    s32 j;
    s32 mask;
    s32 card;
    s32 count;

    selection = selections;
    selector = arg1;
    src = arg0;
    i = 0;
    result = 0;
    do {
        if ((mask = func_0024CA40(0, 0, selector, 1, *src, 14)) > 0) {
            for (j = 0; j < func_0024E910(result); j++) {
                card = func_0024EC50(result, j);
                if (func_0024EA10(card, mask) != 0) {
                    mask = func_0024C7D0(mask, card >> 8, card & 0xFF);
                }
            }
            count = func_0024F200(mask);
            if (count > 0) {
                if ((*selection = func_0024EFB0(count)) >= 0) {
                    result = func_0024C780(result, *selection >> 8, *selection & 0xFF);
                }
            }
        }
        i++;
        src++;
        selection++;
    } while (i < 3);
    if (func_0024E910(result) != 3) {
        return -1;
    }
    return result;
}

void func_00254C90(s32 *arg0, s32 arg1) {
    arg0[2] = -1;
    arg0[1] = -1;
    arg0[0] = -1;
    switch (arg1) {
    case 0xBD:
        arg0[0] = 0x07D00039;
        arg0[1] = 0x07D00039;
        arg0[2] = 0x07D00039;
        break;
    case 0xD:
        arg0[0] = 4;
        arg0[1] = 0;
        arg0[2] = 0x11;
        break;
    case 0x91:
        arg0[0] = 0x63001C;
        arg0[1] = 0x023D001C;
        arg0[2] = 0x0216001C;
        break;
    case 0x8F:
        arg0[0] = 0x9B001C;
        arg0[1] = 0x05DC0025;
        arg0[2] = 0x05DC0025;
        break;
    case 0x151:
        arg0[0] = 0x012C001C;
        arg0[1] = 7;
        arg0[2] = 7;
        break;
    case 0xF8:
        arg0[0] = 0xF9001C;
        arg0[1] = 5;
        arg0[2] = 5;
        break;
    case 0x152:
        arg0[0] = 0x0149001C;
        arg0[1] = 0x0121001C;
        arg0[2] = 7;
        break;
    case 0x2:
        arg0[0] = 0x1C;
        arg0[1] = 0x1C;
        arg0[2] = 0x1C;
        break;
    case 0xC3:
        arg0[0] = 0x0236001C;
        arg0[1] = 6;
        arg0[2] = 3;
        break;
    case 0x93:
        arg0[0] = 0xD2001C;
        arg0[1] = 0x0150001C;
        arg0[2] = 0x0295001C;
        break;
    case 0xDC:
        arg0[0] = 0x0279001C;
        arg0[1] = 4;
        arg0[2] = 4;
        break;
    case 0x87:
        arg0[0] = 0x23001C;
        arg0[1] = 3;
        arg0[2] = 3;
        break;
    case 0xA:
        arg0[0] = 0x5001C;
        arg0[1] = 0x0125001C;
        arg0[2] = 0x6001C;
        break;
    case 0xB:
        arg0[0] = 0x8001C;
        arg0[1] = 3;
        arg0[2] = 6;
        break;
    case 0x254:
        arg0[0] = 0x0248001C;
        arg0[1] = 0x10;
        arg0[2] = 0x10;
        break;
    case 0x4D:
        arg0[0] = 0x0131001C;
        arg0[1] = 1;
        arg0[2] = 1;
        break;
    case 0x160:
        arg0[0] = 0x014A001C;
        arg0[1] = 0x03E80025;
        arg0[2] = 0x03E80025;
        break;
    case 0x161:
        arg0[0] = 0xAD001C;
        arg0[1] = 0xE;
        arg0[2] = 0xE;
        break;
    case 0x1A6:
        arg0[0] = 0x018E001C;
        arg0[1] = 9;
        arg0[2] = 9;
        break;
    case 0x94:
        arg0[0] = 0x92001C;
        arg0[1] = 3;
        arg0[2] = 3;
        break;
    case 0x4C:
        arg0[0] = 0x029B001C;
        arg0[1] = 0xCC001C;
        arg0[2] = 0x4F001C;
        break;
    case 0x80:
        arg0[0] = 2;
        arg0[1] = 0xE;
        arg0[2] = 9;
        break;
    case 0x1D8:
        arg0[0] = 0x0214001C;
        arg0[1] = 0xC;
        arg0[2] = 0xC;
        break;
    case 0x4E:
        arg0[0] = 0x3C001C;
        arg0[1] = 0x05DC0025;
        arg0[2] = 0x05DC0025;
        break;
    default:
        arg0[0] = -1;
        arg0[1] = -1;
        arg0[2] = -1;
        break;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_074", func_002550C0);

void func_00255960(void *arg0) {
    f32 *temp_v0_2;
    f32 *temp_s0;
    s32 var_a0;
    u8 *var_a1;

    *(s16 *)((u8 *)arg0 + 0) = 0;
    *(s16 *)((u8 *)arg0 + 2) = 0;
    *(s16 *)((u8 *)arg0 + 4) = 0;
    *(s8 *)((u8 *)arg0 + 0xD4) = 0;
    func_00255CD0(arg0);
    var_a0 = 0;
    var_a1 = arg0;
    do {
        *(u8 *)((u32)arg0 + var_a0 + 6) = 0xFF;
        *(s32 *)(var_a1 + 0x20) = 0;
        var_a0 += 1;
        var_a1 += 4;
    } while (var_a0 < 0x18);
    temp_s0 = (f32 *)func_001F9D30(0);
    temp_v0_2 = func_001FAF60(0);
    *(s32 *)((u8 *)arg0 + 0xD0) = 0;
    *(s32 *)((u8 *)arg0 + 0xCC) = 0;
    *(s8 *)((u8 *)arg0 + 0x100) = 0;
    *(s16 *)((u8 *)arg0 + 0x102) = 0;
    *(f32 *)((u8 *)arg0 + 0xE0) = temp_s0[0];
    *(f32 *)((u8 *)arg0 + 0xE4) = temp_s0[1];
    *(f32 *)((u8 *)arg0 + 0xE8) = temp_s0[2];
    *(f32 *)((u8 *)arg0 + 0xEC) = temp_s0[3];
    *(f32 *)((u8 *)arg0 + 0xF0) = temp_v0_2[0];
    *(f32 *)((u8 *)arg0 + 0xF4) = temp_v0_2[1];
    *(f32 *)((u8 *)arg0 + 0xF8) = temp_v0_2[2];
    *(f32 *)((u8 *)arg0 + 0xFC) = temp_v0_2[3];
}

INCLUDE_ASM("asm/nonmatchings/main_074", func_00255A30);

INCLUDE_ASM("asm/nonmatchings/main_074", func_00255AC0);

typedef struct {
    s8 ready : 1;
    u8 count : 5;
    u8 reserved : 2;
} Flags_00255B50;

typedef struct {
    u8 pad[0x80];
    Flags_00255B50 flags;
    u8 pad81;
    u16 ids[24];
    s8 types[24];
} Data_00255B50;

u8 *func_001F3EA0(s32, u16);

s32 func_00255B50(void *arg0) {
    s32 i;
    Data_00255B50 *cursor;
    Data_00255B50 *data;
    u16 id;
    u8 *entry;
    s32 type;

    data = arg0;
    i = 0;
    cursor = data;
    for (; i < data->flags.count; i++) {
        id = cursor->ids[0];
        if (id != 0xFFFF) {
            entry = func_001F3EA0(0, id);
            if (entry != NULL) {
                type = *entry & 7;
                if (type < 2) {
                    if (type == 0) {
                        data->types[i] = 0;
                    } else {
                        return -1;
                    }
                } else {
                    data->types[i] = type;
                }
            }
        }
        cursor = (Data_00255B50 *)((u8 *)cursor + 2);
    }
    data->flags.ready = 1;
    return 1;
}

typedef struct Slots_00255C30 {
    u8 pad[0x82];
    u16 ids[24];
} Slots_00255C30;

u8 *func_001F3EA0(s32, u16);

s32 func_00255C30(void *arg0, s32 arg1) {
    s32 state;
    s32 i;
    u8 *entry;
    Slots_00255C30 *slots = arg0;

    if (arg0 == NULL) {
        return 0;
    }

    for (i = 0; i < 24; i++) {
        if (arg1 == slots->ids[i]) {
            entry = func_001F3EA0(0, slots->ids[i]);
            if (entry != NULL) {
                state = *entry & 7;
                if (state < 2) {
                    return state == 0 ? 0 : -1;
                }
            }
            return 1;
        }
    }
    return 0;
}

typedef struct {
    u8 padding[0x80];
    s8 active : 1;
    u8 count : 5;
    u8 reserved : 2;
    u8 padding81;
    u16 entries[0x18];
    u8 states[0x18];
} State_00255CD0;

void func_00255CD0(void *arg0) {
    State_00255CD0 *state = arg0;
    s32 i;

    state->active = 0;
    state->count = 0;
    for (i = 0; i < 0x18; i++) {
        state->entries[i] = 0xFFFF;
        state->states[i] = 0;
    }
}

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

typedef struct Flags_002560C0 {
    s8 ready : 1;
    s8 unused : 7;
} Flags_002560C0;

typedef struct Context_002560C0 {
    s32 unused;
    s32 mode;
    s32 handle;
    s32 option;
} Context_002560C0;

typedef struct State_002560C0 {
    u16 alpha;
    u16 unused2;
    u16 phase;
    u8 handles[0x1A];
    s32 positions[24];
    Flags_002560C0 flags;
    u8 unused81[0x53];
    u8 count;
    u8 unusedD5[0x2B];
    u8 active;
    u8 unused101;
    u16 timer;
} State_002560C0;

void func_001E1E70(s32, s32, s32, s32);
void func_00255AC0(void *, s32);
void func_00260740(s32);
void func_00260A70(void *, s32);

s32 func_002560C0(void *arg0, void *arg1, s32 arg2) {
    extern s32 func_0024EA60();
    extern s32 func_001E15E0();
    s32 effect[4];
    Context_002560C0 *context = arg0;
    State_002560C0 *state = arg1;
    s32 *effectData = effect;
    s32 i;
    s32 count;
    u8 flags;
    u8 *cursor;
    s32 position;

    effect[0] = 999;
    effect[1] = 0;
    effect[2] = 0;
    effect[3] = 0;
    count = 0;
    flags = 0;
    func_001DE7E0(0);
    if (arg2 >= 0) {
        func_00255960(state);
        func_0024E910(context->handle);
        state->alpha = 0x80;
        func_00260020(context, state, arg2, -1, 1, 1);
        func_00255AC0(state, 500);
        if (func_0024E910(context->handle) == 1) {
            func_00260AF0(0x20, func_0024EC50(context->handle, 0), 100, 180);
        } else {
            func_00260740(0x20);
        }
        return 1;
    }

    switch (state->phase) {
    case 0:
        if (state->alpha > 0x30) {
            state->alpha -= 15;
        } else {
            state->alpha = 0x30;
            if (state->timer++ >= 0x30) {
                if (state->flags.ready == 0) {
                    if (func_00255B50(state) == 1) {
                        state->flags.ready = 1;
                    }
                } else {
                    if (context->option != 0) {
                        func_001E42C0(func_0024EA60(context->handle), -120, 80, 0x108);
                    } else {
                        func_001E42C0(func_0024EA60(context->handle), -120, 80, 0x118);
                    }
                    func_0025F720(context, state, effectData, 500);
                    state->phase++;
                }
            }
        }
        if (state->alpha < 0x30) {
            state->alpha = 0x30;
        }
        func_001F6CF0((u8)state->alpha);
        break;
    case 1:
        for (i = 0; i < state->count; i++) {
            if (func_001F51D0(state->handles[i]) == 0) {
                count++;
            }
        }
        if (count >= state->count) {
            func_001E4530();
            for (count = 0, cursor = (u8 *)state; count < state->count; cursor += 4, count++) {
                if (context->mode == 1) {
                    position = *(s32 *)(cursor + 0x20);
                    func_001E15E0(position >> 8, position & 0xFF, 0xFF);
                } else {
                    position = *(s32 *)(cursor + 0x20);
                    func_002503B0(position >> 8, position & 0xFF, (u8)context->option);
                    if (context->option != 0) {
                        position = *(s32 *)(cursor + 0x20);
                        func_001E1E70(position >> 8, position & 0xFF, 0, 1);
                    }
                }
            }
            state->phase++;
            func_00260020(context, state, arg2, 1, 0, 1);
        }
        break;
    default:
        state->alpha += 15;
        if (state->alpha > 0x80) {
            state->alpha = 0x80;
        }
        func_001F6CF0((u8)state->alpha);
        if (state->alpha == 0x80) {
            flags = 1;
        }
        break;
    }

    switch (state->active) {
    case 0:
        if (flags & 1) {
            if (state->timer++ > 0x10) {
                state->active++;
                state->timer = 0;
                func_00260A70(state, 0x20);
            }
        }
        break;
    default:
        if (state->timer++ > 0x20) {
            flags |= 2;
        }
        break;
    }
    if (flags == 3) {
        if (func_0025FD90() == 1) {
            if (func_001DE780() != 0) {
                func_001DE7E0(1);
            }
            func_001E4530();
            return 0;
        }
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_074", func_00256520);

typedef struct State_00256AB0 {
    u8 pad0[4];
    u16 state;
    u8 ids[0x1A];
    s32 values[0x2D];
    u8 count;
    u8 padD5[0x2D];
    u16 timer;
} State_00256AB0;

typedef struct Input_00256AB0 {
    s32 unused;
    s32 first;
    s32 second;
} Input_00256AB0;

typedef struct Request_00256AB0 {
    s32 id;
    s32 flags;
    s32 value;
    s32 kind;
} Request_00256AB0;

u8 func_00255A30(s32 *, void *);
void func_00255AC0(void *, s32);
void func_0025FC30(void *, void *, s32, s32, s32, s32);
void func_00260740(s32);
void func_00260A70(void *, s32);

s32 func_00256AB0(void *arg0, void *arg1, s32 arg2) {
    Request_00256AB0 request;
    State_00256AB0 *state = arg1;
    Input_00256AB0 *input = arg0;
    {
    Request_00256AB0 *p = &request;
    s32 complete;
    s32 i;
    u8 *walk;

    request.id = 999;
    request.flags = 0;
    request.value = 0;
    request.kind = 0;
    complete = 0;

    if (arg2 >= 0) {
        func_00255960(arg1);
        func_0025FC30(arg0, arg1, arg2, -1, 1, 3);
        func_00260740(30);
        func_00255AC0(arg1, 503);
        func_00255AC0(arg1, 502);
        return 1;
    } else {
        switch (state->state) {
        case 0: {
            if (state->timer++ > 30) {
              if (func_00255B50(arg1) == 1) {
                u8 id;
                p->id = 503;
                p->flags = 1;
                p->value = input->second;
                p->kind = 8;
                id = func_00255A30((s32 *)p, arg1);
                state->ids[state->count] = id;
                if ((s32)id >= 0) {
                    state->values[state->count] = input->second;
                    state->count++;
                }
                p->id = 502;
                p->flags = 0;
                p->value = input->first;
                p->kind = 7;
                id = func_00255A30((s32 *)p, arg1);
                state->ids[state->count] = id;
                if ((s32)id >= 0) {
                    state->values[state->count] = input->first;
                    state->count++;
                }
                state->state++;
              }
            }
            return 1;
        }
        case 1: {
            i = 0;
            walk = arg1;
            for (; i < state->count; walk += 4, i++) {
                if (func_001F51D0(state->ids[i]) != 0) {
                    if (func_001F52D0(state->ids[i]) == 2 && *(u16 *)(walk + 0x20) != 0xFFFF) {
                        *(s32 *)(walk + 0x20) = 0xFFFF;
                    }
                } else {
                    complete++;
                }
            }
            if (complete >= state->count) {
                state->state++;
                func_00260A70(arg1, 30);
                state->timer = 0;
                func_0025FC30(arg0, arg1, arg2, 1, 1, 3);
            }
            return 1;
        }
        default: {
            if (state->timer++ > 30 && func_0025FD90() == 1) {
                return 0;
            }
            break;
        }
        }
    }
    return 1;
    }
}

typedef struct Command_00256D80 {
    s32 type;
    union {
        u32 word;
        struct {
            u16 id;
            u16 options;
        } parts;
        struct {
            u32 id : 16;
            u32 copy : 1;
            u32 remove : 1;
            u32 unused : 14;
        } bits;
    } flags;
    u32 position;
    u32 card;
} Command_00256D80;

typedef struct State_00256D80 {
    s32 unused0;
    u16 step;
    u8 slot;
    u8 unused7[0x19];
    union {
        u32 word;
        u8 byte;
    } pending;
    u8 unused24[0xA8];
    u32 position;
    u8 unusedD0[4];
    u8 count;
    u8 unusedD5[0x2B];
    u8 phase;
    u8 unused101;
    u16 timer;
} State_00256D80;

typedef struct Card_00256D80 {
    u8 unused0[0x3E];
    u8 kind;
    u8 unused3F[5];
    u8 x;
    u8 y;
    u8 unused46[0x11];
    struct {
        s8 marked : 1;
        s8 unused : 7;
    } flags;
} Card_00256D80;

extern void func_001DEF20(u32);
extern void func_002516D0(s32, s32, s32);
extern u8 func_00255A30(s32 *, void *);
extern void func_00255AC0(void *, s32);
extern void func_00260A70(void *, s32);
extern void func_002614C0(s32, u32, s32);

s32 func_00256D80(void *arg0, void *arg1, s32 arg2) {
    extern s32 func_001DEE50();
    extern void *func_001DF580();
    s32 packet[4];
    s32 *p;
    Command_00256D80 *command = arg0;
    State_00256D80 *state = arg1;
    s32 i;
    s32 count;
    u32 card;

    packet[0] = 999;
    packet[1] = 0;
    packet[2] = 0;
    packet[3] = 0;
    p = packet;

    if (arg2 >= 0) {
        func_00255960(state);
        if (command->card == 999) {
            func_001E4530();
            return 0;
        }
        switch (func_0026FCE0(command->card & 0xFFFF) >> 5) {
        case 0:
            if (func_001E0150(command->flags.parts.id) >= 5) {
                command->card = 999;
                func_001E4530();
                return 0;
            }
            break;
        default:
            if (func_001E01F0(command->flags.parts.id) >= 5) {
                command->card = 999;
                func_001E4530();
                return 0;
            }
            break;
        }
        func_001DE7E0(0);
        func_00255AC0(state, 501);
        func_002614C0(16, command->position, 180);
        return 1;
    }

    switch (state->step) {
    case 0:
        if (command->card == 999) {
            func_001E4530();
            return 0;
        }
        switch (func_0026FCE0(command->card & 0xFFFF) >> 5) {
        case 0:
            if (func_001E0150(command->flags.parts.id) >= 5) {
                if (func_001DE780() != 0) {
                    func_001DE7E0(1);
                }
                func_001E4530();
                return 0;
            }
            break;
        default:
            if (func_001E01F0(command->flags.parts.id) >= 5) {
                if (func_001DE780() != 0) {
                    func_001DE7E0(1);
                }
                func_001E4530();
                return 0;
            }
            break;
        }
        func_001DE7E0(0);
        if (func_00255B50(state) != 1) {
            return 1;
        }
        state->step++;
        break;
    case 1:
        func_001DE7E0(0);
        p[0] = 501;
        p[1] = 0;
        p[2] = command->position;
        p[3] = 0;
        if ((s32)(state->slot = func_00255A30(p, state)) >= 0) {
            state->count++;
        }
        state->step++;
        break;
    case 2:
        func_001DE7E0(0);
        if (func_001F51D0(state->slot) != 0) {
            if (func_001F52D0(state->slot) == 2) {
                if (state->pending.byte != 0xFFFF) {
                    if (command->card == 999) {
                        u32 position = command->position;
                        Card_00256D80 *result;
                        result = func_001DF580(command->flags.parts.id,
                            position & 0xFF, position >> 8,
                            func_001DEE00(command->flags.parts.id,
                                func_001DEE50(command->flags.parts.id) - 1), 0);
                        if (result != 0) {
                            if (((s32)result->kind >> 5) != 0) {
                                result->flags.marked = 1;
                            }
                            if (((command->flags.word >> 16) & 1) == 1) {
                                state->position = (result->x << 8) | result->y;
                            }
                        }
                        if ((command->flags.word >> 17) & 1) {
                            func_001DF000(command->card >> 16,
                                func_001DEE50(command->flags.word & 0xFFFF) - 1);
                            func_001DEF20(command->card >> 16);
                        }
                    } else {
                        Card_00256D80 *result;
                        result = func_001DF580(command->flags.parts.id,
                            command->position & 0xFF, command->position >> 8,
                            command->card & 0xFFFF, 0);
                        if (result != 0) {
                            if (((s32)result->kind >> 5) != 0) {
                                result->flags.marked = 1;
                            }
                            if (((command->flags.word >> 16) & 1) == 1) {
                                state->position = (result->x << 8) | result->y;
                            }
                        }
                        if ((command->flags.word >> 17) & 1) {
                            count = func_001DEE50(command->card >> 16);
                            for (i = 0; i < count; i++) {
                                card = command->card;
                                if ((card & 0xFFFF) == func_001DEE00(card >> 16, i)) {
                                    func_001DF000(card / 0x10000, i);
                                    i = count;
                                }
                            }
                            func_001DEF20(command->card >> 16);
                        }
                    }
                    state->pending.word = 0xFFFF;
                }
            }
            return 1;
        }
        state->step++;
        break;
    case 3:
        func_001DE7E0(0);
        if (state->position != 0) {
            func_002516D0(state->position >> 8, state->position & 0xFF, 1);
            state->step++;
        } else {
            state->step++;
        }
        break;
    default:
        func_001DE7E0(0);
        switch (state->phase) {
        case 0:
            func_00260A70(state, 16);
            state->timer = 0;
            state->phase++;
            break;
        default: {
            u16 timer = state->timer++;
            if (timer > 16) {
                if (func_001DE780() != 0) {
                    func_001DE7E0(1);
                }
                func_001E4530();
                return 0;
            }
            break;
        }
        }
        break;
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_074", func_00257340);

INCLUDE_ASM("asm/nonmatchings/main_074", func_00257AA0);

typedef struct Command_00258490 {
    s32 kind;
    s32 arg;
    u32 mask;
    s32 extra;
} Command_00258490;

typedef struct State_00258490 {
    u8 pad0[4];
    u16 state;
    u8 handle;
    u8 pad7[0xF9];
    u8 phase;
    u8 pad101;
    u16 timer;
} State_00258490;

void func_0024F370(s32, s32);
u8 func_00255A30(s32 *, void *);
void func_00255AC0(void *, s32);
void func_00260740(s32);
void func_00260A70(void *, s32);

s32 func_00258490(void *arg0, void *arg1, s32 arg2) {
    Command_00258490 request;
    {
    Command_00258490 *command = &request;
    u8 flags = 0;
    State_00258490 *state = arg1;
    Command_00258490 *src = arg0;
    s32 i;

    request.kind = 999;
    request.arg = 0;
    request.mask = 0;
    request.extra = 0;
    func_001DE7E0(0);
    if (arg2 >= 0) {
        func_00255960(state);
        func_00255AC0(state, 6);
        return 1;
    }
    switch (state->state) {
    case 0:
        if (func_00255B50(state) == 1) {
            command->kind = 6;
            command->arg = 0;
            command->mask = src->mask;
            command->extra = 0;
            state->handle = func_00255A30((s32 *)command, state);
            state->state++;
        }
        break;
    case 1:
        if (func_001F51D0(state->handle) != 1) {
            i = 0;
            do {
                if ((src->mask >> (21 - i) & 1) == 1) {
                    if (i < 11) {
                        func_0024F370(0, i);
                    } else {
                        func_0024F370(1, i - 11);
                    }
                }
                i++;
            } while (i < 22);
            state->state++;
        }
        break;
    default:
        flags = 1;
        break;
    }
    switch (state->phase) {
    case 0:
        func_00260740(30);
        state->phase++;
        break;
    case 1:
        if (state->timer++ >= 30) {
            state->phase++;
            state->timer = 0;
        }
        break;
    case 2:
        if (!(flags & 1)) {
            if (state->timer++ == 0) {
                func_00260990(60, 0x3FFF);
            } else if (state->timer >= 60) {
                state->timer = 0;
            }
        } else {
            func_00260A70(state, 16);
            state->timer = 0;
            state->phase++;
        }
        break;
    default:
        if (state->timer++ >= 16) {
            flags |= 2;
        }
        break;
    }
    if (flags == 3) {
        if (func_001DE780() != 0) {
            func_001DE7E0(1);
        }
        func_001E4530();
        return 0;
    }
    return 1;
    }
}

void func_001E1E70(s32, s32, s32, s32);
void func_0024F370(s32, s32);
void func_002516D0(s32, s32, s32);
u8 func_00255A30(s32 *, void *);
void func_00260740(s32);
void func_00260A70(void *, s32);

typedef struct Request_00258760 {
    s32 command;
    s32 field4;
    s32 coord;
    s32 fieldC;
} Request_00258760;

typedef struct Input_00258760 {
    s32 command;
    u32 value;
    u32 field8;
    s32 fieldC;
} Input_00258760;

typedef struct State_00258760 {
    u16 coord;
    u16 next;
    u16 step;
    u8 handles[0x1A];
    s32 coords[0x2C];
    u32 flags;
    u8 count;
    u8 padding[0x2D];
    u16 timer;
} State_00258760;

s32 func_00258760(void *arg0, void *arg1, s32 arg2) {
    extern s32 func_001E1E10();
    Request_00258760 requestData;
    s32 i;
    Request_00258760 *request = &requestData;
    s32 second;
    s32 first;
    s32 j;
    s32 k;
    State_00258760 *walk;
    s32 object;
    s32 coord;
    u8 handle;
    Input_00258760 *input = arg0;
    State_00258760 *state = arg1;

    request->command = 999;
    request->field4 = 0;
    request->coord = 0;
    request->fieldC = 0;
    func_001DE7E0(0);
    if (arg2 >= 0) {
        func_00255960(state);
        state->flags = func_00272210(input->field8, (u16)input->fieldC);
        if ((first = func_0026AB80(input->fieldC, 0x4B)) >= 0) {
            if ((second = func_0026AB80(input->fieldC == 0 ? 1 : 0, 0x2E)) >= 0) {
                func_00260AF0(0, first, 0xB4, 0xB4);
                func_002516D0(second >> 8, second & 0xFF, 1);
                state->step = 0x20;
                state->coord = second;
                state->next = 0x24;
                func_00255AC0(state, 0x25A);
                func_00255AC0(state, 0x1FB);
            } else {
                func_00260AF0(0, second, 0xB4, 0xB4);
                func_002516D0(first >> 8, first & 0xFF, 1);
                state->step = 0x20;
                state->coord = first;
                state->next = 0x22;
                func_00255AC0(state, 0x25A);
                func_00255AC0(state, 0x25B);
            }
        } else {
            func_00260490(input->value & 0xFF, input->value >> 8, 0, 0, 1, 0x12, 0xFF);
            func_00260740(0x1E);
            func_00255AC0(state, 0x1FB);
            func_00255AC0(state, 0x25B);
        }
        return 1;
    }
    if (func_00255B50(state) != 1) {
        return 1;
    }
    switch (state->step) {
    case 0:
        func_0025F720(input, state, request, 0x1FB);
        state->step++;
        break;
    case 1:
        for (i = 0, walk = state; i < state->count; walk = (State_00258760 *)((u8 *)walk + 4), i++) {
            if (func_001F51D0(state->handles[i]) == 1 && func_001F52D0(state->handles[i]) == 2 && walk->coords[0] >= 0) {
                if (func_0024EA10(walk->coords[0], state->flags) != 0) {
                    request->command = 0x25B;
                    request->field4 = 0;
                    request->coord = walk->coords[0];
                    request->fieldC = 1;
                    handle = func_00255A30((s32 *)request, state);
                    state->handles[state->count + i] = handle;
                    if (handle >= 0) {
                        state->coords[state->count + i] = walk->coords[0];
                        state->next++;
                        walk->coords[0] = -1;
                    }
                } else {
                    object = func_0024DE70(walk->coords[0] >> 8, walk->coords[0] & 0xFF);
                    coord = func_001E1090(object, 0);
                    if (func_00271E40(walk->coords[0] >> 8, walk->coords[0] & 0xFF, 0xB) == 1) {
                        func_00260490(coord & 0xFF, coord >> 8, 0, func_00271740(9, object), 1, 1, 0xB);
                        func_001E42C0(0, -0x78, 0x50, 0x10E);
                    }
                    walk->coords[0] = -1;
                }
            }
        }
        for (j = 0; j < state->count + state->next; j++) {
            if (func_001F51D0(state->handles[j]) == 1) {
                return 1;
            }
        }
        k = 0;
        do {
            if (((state->flags >> (0x15 - k)) & 1) == 1) {
                if (k < 0xB) {
                    func_0024F370(0, k);
                } else {
                    func_0024F370(1, k - 0xB);
                }
            }
            k++;
        } while (k < 0x16);
        func_001E4530();
        func_00260A70(state, 0x10);
        state->timer = 0;
        if (func_001DE780() != 0) {
            func_001DE7E0(1);
        }
        state->step++;
        break;
    case 2:
        if (state->timer++ > 0x10) {
            func_001E4530();
            return 0;
        }
        break;
    case 0x20:
        if (func_001E1E10(state->coord >> 8, state->coord & 0xFF) != 0xFF) {
            return 1;
        }
        if (state->next == 0x24) {
            func_001E42C0(0, -0x78, 0x50, func_001DE210(0x339));
        } else {
            func_001E42C0(0, -0x78, 0x50, func_001DE210(0x334));
        }
        request->command = 0x25A;
        request->field4 = 0;
        request->coord = state->coord;
        request->fieldC = 0;
        state->handles[state->count] = func_00255A30((s32 *)request, state);
        state->count++;
        state->step++;
        break;
    case 0x21:
        if (func_001F51D0(state->handles[state->count - 1]) == 1) {
            return 1;
        }
        func_001E1E70(state->coord >> 8, state->coord & 0xFF, 0, 1);
        func_001E4530();
        state->step = state->next;
        break;
    case 0x22:
        request->command = 0x25B;
        request->field4 = 0;
        request->coord = state->coord;
        request->fieldC = 0;
        state->handles[state->count] = func_00255A30((s32 *)request, state);
        state->count++;
        state->next = 0x23;
        state->step = 0x21;
        break;
    case 0x23:
        func_0024F370(state->coord >> 8, state->coord & 0xFF);
        func_00260A70(state, 0x10);
        state->timer = 0;
        if (func_001DE780() != 0) {
            func_001DE7E0(1);
        }
        state->step = 2;
        break;
    case 0x24:
        state->count = 0;
        state->next = 0;
        func_00260740(0x1E);
        func_0025F720(input, state, request, 0x1FB);
        state->step = 1;
        return 1;
    default:
        return 1;
    }
    return 1;
}

void func_001E1E70(s32, s32, s32, s32);
void func_002516D0(s32, s32, s32);
u8 func_00255A30(s32 *, void *);
void func_00260A70(void *, s32);

typedef struct Input_00258E20 {
    s32 unused[2];
    s32 index;
    u32 value;
} Input_00258E20;

typedef struct State_00258E20 {
    s16 active;
    u16 position;
    u16 phase;
    u8 entries[0xCE];
    u8 count;
    u8 padding[0x2D];
    u16 timer;
} State_00258E20;

typedef struct Command_00258E20 {
    s32 type;
    s32 flags;
    s32 position;
    s32 amount;
} Command_00258E20;

s32 func_00258E20(void *arg0, void *arg1, s32 arg2) {
    extern s32 func_001E1E10();
    Input_00258E20 *input = arg0;
    State_00258E20 *state = arg1;
    s32 var_s0;
    Command_00258E20 command;
    Command_00258E20 *action = &command;
    s32 temp_v0;
    s32 temp_v0_2;
    u16 temp_v0_3;
    u16 temp_v0_4;
    u16 temp_v0_5;
    u16 temp_v0_6;
    u16 temp_v0_7;
    u16 temp_v0_8;
    u16 temp_v1;
    u32 temp_a0;

    action->type = 0x3E7;
    action->flags = 0;
    action->position = 0;
    action->amount = 0;
    temp_a0 = input->value;
    if ((temp_a0 >> 0x10) == 4) {
        s32 currentValue = func_001DF470(input->index);
        var_s0 = (u16) input->value - currentValue;
    } else {
        var_s0 = func_002670F0(0x2B, temp_a0 & 0xFFFF);
    }
    if (var_s0 < 0) {
        var_s0 = 0;
    }
    func_001DE7E0(0);
    if (arg2 >= 0) {
        func_00255960(arg1);
        func_00255AC0(arg1, 0x1FC);
        if ((temp_v0 = func_0026AB80(input->index, 0x2A)) < 0) {
            state->phase = 0x20U;
        } else {
            if ((temp_v0_2 = func_0026AB80(input->index, 0x2E)) < 0) {
                state->position = (u16) temp_v0;
                func_00255AC0(arg1, 0x25A);
                func_00255AC0(arg1, 0x224);
                state->phase = 0x40U;
            } else {
                func_00255AC0(arg1, 0x25A);
                func_00260AF0(0, temp_v0_2, 0xB4, 0xB4);
                state->position = (u16) temp_v0_2;
                func_002516D0(temp_v0_2 >> 8, temp_v0_2 & 0xFF, 1);
                state->phase = 0x10U;
                state->active = 1;
            }
        }
        return 1;
    }
    if (func_00255B50(arg1) == 1) {
        temp_v1 = state->phase;
        switch (temp_v1) {                          
        case 0x0:
            if (func_001F51D0((s32) *(u8 *)(state->count + (u32)state + 5)) == 1) {
                return 1;
            }
            func_001DF490(input->index, 0, var_s0);
            func_001E4530();
            if (func_001DE780() != 0) {
                func_001DE7E0(1);
            }
            func_001E4530();
            return 0;
        case 0x1:
            if (func_001E1E10((s32) state->position >> 8, state->position & 0xFF) != 0xFF) {
                temp_v0_3 = state->position;
                if (func_001E2100((s32) temp_v0_3 >> 8, temp_v0_3 & 0xFF, 4) == 0) {
                    temp_v0_4 = state->position;
                    func_002516D0((s32) temp_v0_4 >> 8, temp_v0_4 & 0xFF, 1);
                }
                return 1;
            }
            func_00260AF0(0, (s32) state->position, 0xB4, 0xB4);
            func_001E42C0(0, -0x78, 0x50, func_001DE210(0x32F));
            action->type = 0x25A;
            action->flags = 0;
            action->position = (s32) state->position;
            action->amount = 0;
            state->entries[state->count] = func_00255A30((s32 *)action, arg1);
            state->count = (u8) (state->count + 1);
            state->phase = (u16) (state->phase + 1);
            return 1;
        case 0x2:
        case 0x4:
        case 0x11:
            if (func_001F51D0((s32) *(u8 *)(state->count + (u32)state + 5)) == 0) {
                if (state->phase != 4) {
                    temp_v0_5 = state->position;
                    func_001E1E70((s32) temp_v0_5 >> 8, temp_v0_5 & 0xFF, 0, 1);
                }
                state->phase = (u16) (state->phase + 1);
            }
            break;
        case 0x3:
            func_001E42C0(0, -0x78, 0x50, 0x10B);
            action->type = 0x224;
            action->flags = 0;
            action->position = 0;
            action->amount = var_s0;
            state->entries[state->count] = func_00255A30((s32 *)action, arg1);
            state->count = (u8) (state->count + 1);
            state->phase = (u16) (state->phase + 1);
            return 1;
        case 0x5:
            func_001E4530();
            temp_v0_6 = state->position;
            func_001E1E70((s32) temp_v0_6 >> 8, temp_v0_6 & 0xFF, 0, 1);
            func_001DF490(input->index, 1, var_s0);
            state->phase = (u16) (state->phase + 1);
            func_00260A70(arg1, 0x10);
            state->timer = 0U;
            break;
        case 0x6:
            if (state->timer++ > 0x10) {
                if (func_001DE780() != 0) {
                    func_001DE7E0(1);
                }
                func_001E4530();
                return 0;
            }
            break;
        case 0x10:
            if (func_001E1E10((s32) state->position >> 8, state->position & 0xFF) != 0xFF) {
                temp_v0_7 = state->position;
                if (func_001E2100((s32) temp_v0_7 >> 8, temp_v0_7 & 0xFF, 4) == 0) {
                    temp_v0_8 = state->position;
                    func_002516D0((s32) temp_v0_8 >> 8, temp_v0_8 & 0xFF, 1);
                }
                return 1;
            }
            func_001E42C0(0, -0x78, 0x50, func_001DE210(0x339));
            action->type = 0x25A;
            action->flags = 0;
            action->position = (s32) state->position;
            action->amount = 0;
            state->entries[state->count] = func_00255A30((s32 *)action, arg1);
            state->count = (u8) (state->count + 1);
            state->phase = (u16) (state->phase + 1);
            break;
        case 0x12:
            func_001E42C0(0, -0x78, 0x50, 0x10A);
            action->type = 0x1FC;
            action->flags = 0;
            action->position = 0;
            action->amount = var_s0;
            state->entries[state->count] = func_00255A30((s32 *)action, arg1);
            state->count = (u8) (state->count + 1);
            state->phase = 0U;
            return 1;
        case 0x20:
            action->type = 0x1FC;
            action->flags = 0;
            action->position = 0;
            action->amount = var_s0;
            state->entries[state->count] = func_00255A30((s32 *)action, arg1);
            state->count = (u8) (state->count + 1);
            func_001E42C0(0, -0x78, 0x50, 0x10A);
            state->phase = 0U;
            break;
        case 0x40:
            action->type = 0x1FC;
            action->flags = 0;
            action->position = 0;
            action->amount = (s32) (var_s0 | 0x10000);
            func_001E42C0(0, -0x78, 0x50, 0x10A);
            state->phase = (u16) (state->phase + 1);
            state->entries[state->count] = func_00255A30((s32 *)action, arg1);
            state->count = (u8) (state->count + 1);
            break;
        case 0x41:
            if (func_001F51D0((s32) *(u8 *)(state->count + (u32)state + 5)) == 1) {
                return 1;
            }
            state->phase = 1U;
            break;
        default:
            return 1;
        }
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_074", func_002594D0);

void func_001E1E70(s32, s32, s32, s32);
void func_002516D0(s32, s32, s32);
void func_00255AC0(void *, s32);
void func_00260740(s32);
void func_00260A70(void *, s32);

typedef struct Task_00259D90 {
    u8 pad0[4];
    u16 active;
    u8 ids[0x1A];
    s32 positions[0x2D];
    u8 count;
    u8 padD5[0x2B];
    u8 state;
    u8 pad101;
    u16 timer;
} Task_00259D90;

s32 func_00259D90(void *arg0, void *arg1, s32 arg2) {
    s32 setupData[4];
    s32 *setup = setupData;
    Task_00259D90 *task = arg1;
    s32 i;
    s32 complete;
    u8 flags;
    u8 *position;
    u8 *id;

    setup[0] = 999;
    setup[1] = 0;
    setup[2] = 0;
    setup[3] = 0;
    complete = 0;
    flags = 0;
    func_001DE7E0(0);
    if (arg2 >= 0) {
        func_00255960(arg1);
        func_00261580();
        func_00255AC0(arg1, 0x200);
        return 1;
    }

    switch (task->active) {
    case 0:
        if (func_00255B50(arg1) == 1) {
            func_001E42C0(0, -120, 80, 0x108);
            func_0025F720(arg0, arg1, setup, 0x200);
            task->active++;
        }
        break;
    default:
        for (i = 0, position = arg1; i < task->count; position += 4, i++) {
            id = &task->ids[i];
            if (func_001F51D0(*id) == 1) {
                if (func_001F52D0(*id) == 2 && *(s32 *)(position + 0x20) >= 0) {
                    func_002516D0(*(s32 *)(position + 0x20) >> 8, *(s32 *)(position + 0x20) & 0xFF, 1);
                    func_001E1E70(*(s32 *)(position + 0x20) >> 8, *(s32 *)(position + 0x20) & 0xFF, 0, 1);
                    func_002503B0(*(s32 *)(position + 0x20) >> 8, *(s32 *)(position + 0x20) & 0xFF, *((u8 *)arg0 + 0xC));
                    *(s32 *)(position + 0x20) = -1;
                }
            } else {
                complete++;
            }
        }
        func_001E4530();
        if (complete >= task->count) {
            flags = 1;
        }
        break;
    }

    switch (task->state) {
    case 0:
        if (task->timer++ > 10) {
            func_00260740(16);
            task->state++;
            task->timer = 0;
        }
        break;
    case 1:
        if (flags & 1) {
            if (task->timer++ > 16) {
                task->state++;
                task->timer = 0;
                func_00260A70(arg1, 16);
            }
        }
        break;
    default:
        if (task->timer++ > 16) {
            if (func_001DE780() != 0) {
                func_001DE7E0(1);
            }
            flags |= 2;
        }
        break;
    }
    if (flags == 3) {
        func_001E4530();
        return 0;
    }
    return 1;
}

typedef struct Request_0025A060 {
    s32 command;
    s32 kind;
    s32 mask;
    s32 value;
} Request_0025A060;

typedef struct State_0025A060 {
    u16 alpha;
    u16 unused;
    u16 phase;
    u8 handles[0x1A];
    s32 cards[0x2D];
    u8 count;
    u8 padding[0x2D];
    u16 timer;
} State_0025A060;

void func_001E1E70(s32, s32, s32, s32);
void func_002516D0(s32, s32, s32);
u8 func_00255A30(s32 *, void *);
void func_00255AC0(void *, s32);
void func_00260740(s32);
void func_00260A70(void *, s32);

s32 func_0025A060(void *arg0, void *arg1, s32 arg2) {
    State_0025A060 *state = arg1;
    Request_0025A060 *request = arg0;
    Request_0025A060 task;
    s32 i;
    s32 finished;
    s32 total;
    s32 card;
    u8 handle;
    u8 *cursor;
    Request_0025A060 *next = &task;

    next->command = 999;
    next->kind = 0;
    next->mask = 0;
    next->value = 0;
    i = 0;
    func_001DE7E0(0);
    if (arg2 >= 0) {
        func_00255960(state);
        state->alpha = 0x80;
        func_00260020(request, state, arg2, -1, 1, 1);
        if (func_0024E910(request->mask) == 1) {
            func_00260AF0(0, func_0024EC50(request->mask, 0), 100, 180);
        } else {
            func_00260740(0x10);
        }
        func_00255AC0(state, 0x201);
        return 1;
    }

    switch (state->phase) {
    case 0:
        if ((s32)state->alpha > 0x3F) {
            state->alpha -= 0xF;
        } else {
            state->alpha = 0x30;
            if (func_00255B50(state) == 1) {
                if ((s32)state->timer++ > 0x10) {
                    if ((request->kind == 2 || request->kind == 4) && request->value == 0) {
                        total = func_0024E910(request->mask);
                        for (finished = 0; finished < total; finished++) {
                            card = func_0024EC50(request->mask, finished);
                            next->command = 0x201;
                            next->kind = 0;
                            next->mask = card;
                            next->value = 1;
                            handle = func_00255A30((s32 *)next, state);
                            state->handles[state->count] = handle;
                            if ((s32)handle >= 0) {
                                state->cards[state->count] = card;
                                state->count++;
                            }
                        }
                    } else {
                        func_0025F720(request, state, next, 0x201);
                    }
                    state->phase++;
                    state->timer = 0;
                }
            }
        }
        func_001F6CF0((u8)state->alpha);
        break;
    case 1:
        finished = 0;
        cursor = (u8 *)state;
        while (finished < state->count) {
            if (func_001F51D0(state->handles[finished]) != 0) {
                if (func_001F52D0(state->handles[finished]) == 2) {
                    if (*(s32 *)(cursor + 0x20) >= 0) {
                        func_001F5970(*(s32 *)(cursor + 0x20), 0);
                        if (request->kind == 3 || request->kind == 5) {
                            func_001E1E70(*(s32 *)(cursor + 0x20) >> 8, *(s32 *)(cursor + 0x20) & 0xFF, 5, request->value);
                            func_001E1E70(*(s32 *)(cursor + 0x20) >> 8, *(s32 *)(cursor + 0x20) & 0xFF, 3, request->value);
                        }
                        if (request->kind == 2 || request->kind == 4) {
                            func_002516D0(*(s32 *)(cursor + 0x20) >> 8, *(s32 *)(cursor + 0x20) & 0xFF, request->value);
                        }
                        *(s32 *)(cursor + 0x20) = -1;
                    }
                }
            } else {
                i++;
            }
            cursor += 4;
            finished++;
        }
        if (i < state->count) {
            break;
        }
        if ((s32)state->timer++ > 0x10) {
            func_00260A70(state, 0x10);
            state->timer = 0;
            func_00260020(request, state, arg2, 1, 0, 1);
            state->phase++;
        }
        break;
    default:
        state->alpha += 0xF;
        if ((s32)state->alpha > 0x80) {
            state->alpha = 0x80;
        }
        func_001F6CF0((u8)state->alpha);
        if (state->alpha == 0x80 && (s32)state->timer++ > 0x10 && func_0025FD90() == 1) {
            func_001E4530();
            if (func_001DE780() != 0) {
                func_001DE7E0(1);
            }
            return 0;
        }
        break;
    }
    return 1;
}

typedef struct Context_0025A4C0 {
    u8 pad0[8];
    s32 side;
    s32 mode;
} Context_0025A4C0;

typedef struct State_0025A4C0 {
    u16 counter;
    u16 field2;
    u16 step;
    u8 handle;
    u8 pad7[0x19];
    s32 side;
    u8 pad24[0xA8];
    s32 fieldCC;
} State_0025A4C0;

typedef struct Command_0025A4C0 {
    s32 id;
    s32 field4;
    s32 field8;
    s32 fieldC;
} Command_0025A4C0;

u8 func_00255A30(s32 *, void *);
void func_00255AC0(void *, s32);

s32 func_0025A4C0(void *arg0, u16 *arg1, s32 arg2) {
    Command_0025A4C0 command;
    Command_0025A4C0 *packet = &command;
    Context_0025A4C0 *context = arg0;
    State_0025A4C0 *state = (State_0025A4C0 *)arg1;

    command.id = 999;
    command.field4 = 0;
    command.field8 = 0;
    command.fieldC = 0;
    func_001DE7E0(0);
    if (arg2 >= 0) {
        func_00255960(arg1);
        func_00255AC0(arg1, 0x202);
        if (context->mode != 0) {
            func_00255AC0(arg1, 0x263);
        }
        return 1;
    }
    switch (state->step) {
    case 0:
        if (func_00255B50(arg1) == 1) {
            packet->id = 0x202;
            packet->field4 = 0;
            packet->field8 = 0;
            packet->fieldC = 0;
            state->handle = func_00255A30((s32 *)packet, arg1);
            state->step++;
        }
        break;
    case 1:
        if (func_001F51D0(state->handle) == 1) {
            return 1;
        }
        if (context->mode == 0) {
            if (func_001DF110(context->side) == 0) {
                if (func_001DE780() != 0) {
                    func_001DE7E0(1);
                }
                func_001E4530();
                return 0;
            }
            if (state->counter < 150) {
                func_0025A940((s32)arg0, arg1, 1, context->side, 1);
                state->counter++;
                return 1;
            }
            if (func_0025A940((s32)arg0, arg1, 1, context->side, 0) == 0) {
                func_001E3FE0();
                if (func_001DE780() != 0) {
                    func_001DE7E0(1);
                }
                return 0;
            }
        } else {
            if (func_001DF110(context->side == 0 ? 1 : 0) == 0) {
                state->step++;
                return 1;
            }
            if (func_0025A940((s32)arg0, arg1, 0, context->side == 0 ? 1 : 0, 1) == 0) {
                return 1;
            }
            packet->id = 0x263;
            packet->field4 = 0;
            packet->field8 = 0;
            packet->fieldC = 0;
            state->handle = func_00255A30((s32 *)packet, arg1);
            state->step++;
            state->side = context->side;
        }
        break;
    case 2:
        if (func_001F51D0(state->handle) != 0) {
            if (state->counter++ == 6) {
                func_001E3FE0();
                state->fieldCC = 0;
                state->field2 = 0;
            }
            return 1;
        }
        state->counter = 0;
        if (func_001DF110(context->side) == 0) {
            state->step = 16;
            return 1;
        }
        if (func_0025A940((s32)arg0, arg1, 1, context->side, 1) == 0) {
            return 1;
        }
        packet->id = 0x263;
        packet->field4 = 0;
        packet->field8 = 0;
        packet->fieldC = 0;
        state->handle = func_00255A30((s32 *)packet, arg1);
        state->side = context->side;
        state->step++;
        break;
    case 3:
        if (func_001F51D0(state->handle) != 0) {
            if (state->counter++ == 6) {
                func_001E3FE0();
            }
            return 1;
        }
        state->step++;
        break;
    default:
        {
            s32 i = 0;
            s32 card;
            do {
                card = func_001DF0C0(0, i) & 0xFFF;
                if (card >= 0 && card != 999) {
                    func_001DF2C0(0, i);
                    func_001DEE70(0, card);
                }
                i++;
            } while (i < 5);
            i = 0;
            do {
                card = func_001DF0C0(1, i) & 0xFFF;
                if (card >= 0 && card != 999) {
                    func_001DF2C0(1, i);
                    func_001DEE70(1, card);
                }
                i++;
            } while (i < 5);
        }
        if (func_001DE780() != 0) {
            func_001DE7E0(1);
        }
        func_001E4530();
        return 0;
    }
    return 1;
}

s32 func_0025A940(s32 arg0, u16 *arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 temp_a1;
    s32 temp_v1;
    s32 var_s0;
    s32 var_v0_2;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v0;

    var_s0 = 0;
    if (arg1[1] == 0) {
        temp_v1 = *(s32 *)((u8 *)arg1 + 0xCC);
        *(s32 *)((u8 *)arg1 + 0xCC) = temp_v1 + 1;
        if (temp_v1 == 0) {
            var_v0 = (arg2 & 0xFF) == 1 ? 0 : 0x3C0;
            arg1[1] = var_v0;
        }
    }
    func_001E3FB0(arg3, 0, arg1[1] - 0x1E0);
    if ((arg4 & 0xFF) == 1) {
        if (arg1[1] != 0x1E0) {
            var_v1 = (arg2 & 0xFF) == 1 ? 0x1E : -0x1E;
            arg1[1] += var_v1;
        } else {
            var_s0 = 1;
        }
    } else {
        temp_a1 = arg2 & 0xFF;
        var_v0_2 = temp_a1 == 1 ? 0 : 0x3C0;
        if (arg1[1] != var_v0_2) {
            var_v1_2 = temp_a1 == 1 ? 0x1E : -0x1E;
            arg1[1] -= var_v1_2;
        } else {
            var_s0 = 1;
        }
    }
    return var_s0;
}

typedef struct State_0025AA80 {
    u8 pad0[4];
    u16 step;
    u8 handles[26];
    s32 entries[45];
    u8 count;
    u8 padD5[0x2B];
    u8 phase;
    u8 pad101;
    u16 timer;
} State_0025AA80;

typedef struct Mask_0025AA80 {
    u8 pad0[8];
    u32 mask;
} Mask_0025AA80;

u8 func_00255A30(s32 *, void *);
void func_00255AC0(void *, s32);
void func_002607D0(s32);
void func_00260A70(void *, s32);

s32 func_0025AA80(void *arg0, void *arg1, s32 arg2) {
    s32 descriptor[4];
    s32 i;
    u8 flags;
    s32 *request = descriptor;
    State_0025AA80 *state = arg1;
    Mask_0025AA80 *source = arg0;
    s32 mode = arg2;
    u8 handle;
    u8 phase;

    descriptor[0] = 999;
    descriptor[1] = 0;
    descriptor[2] = 0;
    descriptor[3] = 0;
    i = 0;
    flags = 0;
    func_001DE7E0(0);
    if (mode >= 0) {
        func_00255960(arg1);
        func_002607D0(0);
        func_00255AC0(arg1, 15);
        return 1;
    }
    switch (state->step) {
    case 0:
        if (func_00255B50(arg1) == 1) {
            do {
                if ((source->mask >> (21 - i) & 1) == 1) {
                    if (i < 11) {
                        request[0] = 15;
                        request[1] = 0;
                        request[2] = i;
                        request[3] = func_001E0700(0, i) >> 5;
                        handle = func_00255A30(request, arg1);
                        state->handles[state->count] = handle;
                        if (handle >= 0) {
                            state->entries[state->count] = i;
                            state->count++;
                        }
                    } else {
                        s32 entry;
                        request[0] = 15;
                        entry = i - 11;
                        request[1] = 0;
                        request[2] = entry | 0x100;
                        request[3] = func_001E0700(1, entry) >> 5;
                        handle = func_00255A30(request, arg1);
                        state->handles[state->count] = handle;
                        if (handle >= 0) {
                            state->entries[state->count] = (i - 11) | 0x100;
                            state->count++;
                        }
                    }
                }
                i++;
            } while (i < 22);
            state->step++;
        }
        break;
    default: {
        s32 j;
        for (j = 0; j < state->count; j++) {
            if (func_001F51D0(state->handles[j]) == 0) {
                i++;
            }
        }
        if (i >= state->count) {
            flags = 1;
        }
        break;
    }
    }
    phase = state->phase;
    switch (phase) {
    case 0:
        if (flags & 1) {
            state->phase = phase + 1;
            state->timer = 0;
            func_00260A70(arg1, 30);
        }
        break;
    default:
        if (state->timer++ > 30) {
            flags |= 2;
        }
        break;
    }
    if (flags == 3) {
        if (func_001DE780() != 0) {
            func_001DE7E0(1);
        }
        func_001E4530();
        return 0;
    }
    return 1;
}

typedef struct State_0025AD60 {
    u16 alpha;
    u16 unk2;
    u16 phase;
    u8 slots[0xCE];
    u8 count;
    u8 padding[0x2D];
    u16 timer;
} State_0025AD60;

u8 func_00255A30(s32 *, void *);
void func_00255AC0(void *, s32);
void func_00260740(s32);
void func_00260A70(void *, s32);

s32 func_0025AD60(void *arg0, void *arg1, s32 arg2) {
    s32 packetData[4];
    s32 *packet = packetData;
    State_0025AD60 *state = arg1;
    s32 slot;
    extern s32 func_0025F670();

    packetData[0] = 999;
    packetData[1] = 0;
    packetData[2] = 0;
    packetData[3] = 0;
    func_001DE7E0(0);
    if (arg2 >= 0) {
        func_00255960(arg1);
        func_00260740(0x10);
        func_00255AC0(arg1, 0x204);
        func_00255AC0(arg1, 0x1F);
        func_00255AC0(arg1, 0x25B);
        func_00260020(arg0, arg1, arg2, -1, 1, 1);
        state->alpha = 0x80;
        return 1;
    }

    if (state->phase == 0) {
        if (state->alpha > 0x3F) {
            state->alpha -= 0xF;
        } else {
            state->alpha = 0x30;
            if (func_00255B50(arg1) == 1 && state->timer++ > 0x10) {
                packet[0] = 0x204;
                packet[1] = 0;
                packet[2] = 0;
                packet[3] = 0;
                slot = func_00255A30(packet, arg1);
                state->slots[state->count] = slot;
                if (slot >= 0) {
                    state->count++;
                }
                state->phase++;
                state->timer = 0;
            }
        }
        func_001F6CF0((u8)state->alpha);
    } else if (state->phase == 1) {
        if (func_001F51D0(state->slots[0]) == 1) {
            return 1;
        }
        func_0025F720(arg0, arg1, packet, 0x1F);
        state->phase++;
    } else if (state->phase == 2) {
        if (func_0025F400(arg0, arg1, packet) != 0) {
            state->phase++;
        }
    } else if (state->phase == 3) {
        if (func_0025F670(arg0, arg1, packet) != 0) {
            func_00260020(arg0, arg1, arg2, 1, 0, 1);
            func_00260A70(arg1, 0x10);
            state->timer = 0;
            state->phase++;
        }
    } else {
        state->alpha += 0xF;
        if (state->alpha > 0x80) {
            state->alpha = 0x80;
        }
        func_001F6CF0((u8)state->alpha);
        if (state->alpha == 0x80 && state->timer++ > 0x10 && func_0025FD90() == 1) {
            if (func_001DE780() != 0) {
                func_001DE7E0(1);
            }
            func_001E4530();
            return 0;
        }
    }
    return 1;
}

typedef struct State_0025B050 {
    u16 alpha;
    u16 unk2;
    u16 phase;
    u8 slots[0xCE];
    u8 count;
    u8 padD5[0x2D];
    u16 timer;
} State_0025B050;

typedef struct Params_0025B050 {
    s32 id;
    s32 value1;
    s32 value2;
    s32 value3;
} Params_0025B050;

u8 func_00255A30(s32 *, void *);
void func_00255AC0(void *, s32);
void func_00260740(s32);
void func_00260A70(void *, s32);

s32 func_0025B050(void *arg0, void *arg1, s32 arg2) {
    extern s32 func_0025F670();
    Params_0025B050 params;
    Params_0025B050 *p = &params;
    State_0025B050 *state = arg1;
    s32 slot;

    p->id = 999;
    p->value1 = 0;
    p->value2 = 0;
    p->value3 = 0;
    func_001DE7E0(0);
    if (arg2 >= 0) {
        func_00255960(arg1);
        func_00260740(0x10);
        func_00255AC0(arg1, 0x14);
        func_00255AC0(arg1, 0x1F);
        func_00255AC0(arg1, 0x25B);
        func_00260020(arg0, arg1, arg2, -1, 1, 1);
        state->alpha = 0x80;
        return 1;
    }
    if (state->phase == 0) {
        if (state->alpha > 0x3F) {
            state->alpha -= 0xF;
        } else {
            state->alpha = 0x30;
            if (func_00255B50(arg1) == 1) {
                p->id = 0x14;
                p->value1 = 0;
                p->value2 = 0;
                p->value3 = 0;
                slot = func_00255A30((s32 *)p, arg1);
                state->slots[state->count] = slot;
                if (slot >= 0) {
                    state->count++;
                }
                state->phase++;
            }
        }
        func_001F6CF0((u8)state->alpha);
    } else if (state->phase == 1) {
        if (func_001F51D0(state->slots[0]) == 1) {
            return 1;
        }
        func_0025F720(arg0, arg1, p, 0x1F);
        state->phase++;
    } else if (state->phase == 2) {
        if (func_0025F400(arg0, arg1, p) != 0) {
            state->phase++;
        }
    } else if (state->phase == 3) {
        if (func_0025F670(arg0, arg1, p) != 0) {
            func_00260020(arg0, arg1, arg2, 1, 0, 1);
            func_00260A70(arg1, 0x10);
            state->timer = 0;
            state->phase++;
        }
    } else {
        state->alpha += 0xF;
        if (state->alpha > 0x80) {
            state->alpha = 0x80;
        }
        func_001F6CF0((u8)state->alpha);
        if (state->alpha == 0x80) {
            if (state->timer++ > 0x10 && func_0025FD90() == 1) {
                if (func_001DE780() != 0) {
                    func_001DE7E0(1);
                }
                func_001E4530();
                return 0;
            }
        }
    }
    return 1;
}

typedef struct {
    u16 fade;
    u16 pad2;
    u16 state;
    u8 entries[0xCE];
    u8 count;
    u8 padD5[0x2D];
    u16 timer;
} State_0025B330;

u8 func_00255A30(s32 *, void *);
void func_00255AC0(void *, s32);
void func_00260740(s32);
void func_00260A70(void *, s32);

s32 func_0025B330(void *arg0, void *arg1, s32 arg2) {
    extern s32 func_0025F670();
    s32 data[4];
    s32 *params = data;
    State_0025B330 *state = arg1;
    s32 result;
    u16 stage;

    data[0] = 999;
    data[1] = 0;
    data[2] = 0;
    data[3] = 0;
    func_001DE7E0(0);
    if (arg2 >= 0) {
        func_00255960(arg1);
        func_00255AC0(arg1, 0x206);
        func_00255AC0(arg1, 0x1F);
        func_00255AC0(arg1, 0x25B);
        func_00260020(arg0, arg1, arg2, -1, 1, 1);
        state->fade = 0x80;
        return 1;
    }

    stage = state->state;
    if (stage == 0) {
        if (state->fade > 0x3F) {
            state->fade -= 0xF;
        } else {
            state->fade = 0x30;
            if (func_00255B50(arg1) == 1) {
                params[0] = 0x206;
                params[1] = 0;
                params[2] = 0;
                params[3] = 0;
                func_00260740(0x10);
                result = func_00255A30(params, arg1);
                state->entries[state->count] = result;
                if (result >= 0) {
                    state->count++;
                }
                state->state++;
            }
        }
        func_001F6CF0((u8)state->fade);
    } else if (stage == 1) {
        if (func_001F51D0(state->entries[0]) == 1) {
            return 1;
        }
        func_0025F720(arg0, arg1, params, 0x1F);
        state->state++;
    } else if (stage == 2) {
        if (func_0025F400(arg0, arg1, params) != 0) {
            state->state++;
        }
    } else if (stage == 3) {
        if (func_0025F670(arg0, arg1, params) != 0) {
            func_00260020(arg0, arg1, arg2, 1, 0, 1);
            func_00260A70(arg1, 0x10);
            state->timer = 0;
            state->state++;
        }
    } else {
        state->fade += 0xF;
        if (state->fade > 0x80) {
            state->fade = 0x80;
        }
        func_001F6CF0((u8)state->fade);
        if (state->fade == 0x80 && state->timer++ > 0x10 && func_0025FD90() == 1) {
            if (func_001DE780() != 0) {
                func_001DE7E0(1);
            }
            func_001E4530();
            return 0;
        }
    }
    return 1;
}

typedef struct State_0025B610 {
    u16 fade;
    u16 unk2;
    u16 phase;
    u8 ids[0x1A];
    s32 flags[0x2D];
    u8 count;
    u8 padding[0x2D];
    u16 timer;
} State_0025B610;

typedef struct Source_0025B610 {
    u8 padding[8];
    u32 mask;
} Source_0025B610;

void func_0024F370(s32, s32);
u8 func_00255A30(s32 *, void *);
void func_00255AC0(void *, s32);
void func_00260740(s32);
void func_00260A70(void *, s32);

s32 func_0025B610(void *arg0, void *arg1, s32 arg2) {
    s32 event[4];
    s32 *command = event;
    State_0025B610 *state = arg1;
    s32 i;
    u8 id;

    event[0] = 0x3E7;
    event[1] = 0;
    event[2] = 0;
    event[3] = 0;
    func_001DE7E0(0);
    if (arg2 >= 0) {
        func_00255960(arg1);
        func_00260020(arg0, arg1, arg2, -1, 1, 1);
        func_00260740(0x10);
        state->fade = 0x80;
        func_00255AC0(arg1, 0x38);
    } else if (state->phase == 0) {
        if (state->fade > 0x3F) {
            state->fade -= 0xF;
        } else {
            state->fade = 0x30;
            if (func_00255B50(arg1) == 1) {
                command[0] = 0x38;
                command[1] = 0;
                command[2] = ((Source_0025B610 *)arg0)->mask;
                command[3] = 0;
                state->flags[state->count] = 1;
                id = func_00255A30(command, arg1);
                state->ids[state->count] = id;
                if (id >= 0) {
                    state->count++;
                }
                state->phase++;
            }
        }
        func_001F6CF0((u8)state->fade);
        return 1;
    } else if (state->phase == 1) {
        if (func_001F51D0(state->ids[0]) == 1) {
            if (func_001F52D0(state->ids[0]) == 2) {
                if (state->flags[0] == 1) {
                    i = 0;
                    do {
                        if ((((Source_0025B610 *)arg0)->mask >> (0x15 - i) & 1) == 1) {
                            if (i < 0xB) {
                                func_0024F370(0, i);
                            } else {
                                func_0024F370(1, i - 0xB);
                            }
                        }
                        i++;
                    } while (i < 0x16);
                    state->flags[0] = 0;
                }
            }
            return 1;
        }
        func_00260020(arg0, arg1, arg2, 1, 0, 1);
        func_00260A70(arg1, 0x10);
        state->timer = 0;
        state->phase++;
    } else {
        state->fade += 0xF;
        if (state->fade > 0x80) {
            state->fade = 0x80;
        }
        func_001F6CF0((u8)state->fade);
        if (state->fade == 0x80 && state->timer++ > 0x10 && func_0025FD90() == 1) {
            if (func_001DE780() != 0) {
                func_001DE7E0(1);
            }
            func_001E4530();
            return 0;
        }
    }
    return 1;
}

typedef struct State_0025B900 {
    u16 alpha;
    u16 pad2;
    u16 phase;
    u8 events[0x1A];
    s32 handle;
    u8 pad24[0xAC];
    s32 target;
    u8 count;
    u8 padD5[0x2D];
    u16 timer;
} State_0025B900;

u8 func_00255A30(s32 *, void *);
void func_00255AC0(void *, s32);
void func_00260860(s32);
void func_00260A70(void *, s32);
extern char D_002B86E8[];

s32 func_0025B900(s32 arg0, void *arg1, s32 arg2) {
    s32 data[4];
    State_0025B900 *state = arg1;
    s32 i;
    s32 position;
    u32 pool;
    s32 *command = data;
    s32 y;
    s32 x;
    s32 result;

    extern s32 func_0025F670();
    extern s32 func_001E1A90();
    extern s32 func_001E1A30();
    extern s32 func_001E1D10();
    extern s32 func_001E1CB0();

    command[0] = 999;
    command[1] = 0;
    command[2] = 0;
    command[3] = 0;
    func_001DE7E0(0);
    if (arg2 >= 0) {
        func_00255960(arg1);
        func_00255AC0(arg1, 0x11);
        func_00255AC0(arg1, 0x18);
        func_00255AC0(arg1, 0x25B);
        func_00260020((void *)arg0, arg1, arg2, -1, 1, 1);
        func_00260860(0x10);
        state->alpha = 0x80;
        return 1;
    }

    if (state->phase == 0) {
        state->timer++;
        if (state->alpha > 0x3F) {
            state->alpha -= 0xF;
        } else {
            state->alpha = 0x30;
            if (state->timer >= 0x10 && func_00255B50(arg1) == 1) {
                command[0] = 0x11;
                command[1] = 0;
                command[2] = 0;
                command[3] = 0;
                result = (u8)func_00255A30(command, arg1);
                state->events[state->count] = result;
                if (result >= 0) {
                    state->count++;
                }
                state->phase++;
            }
        }
        func_001F6CF0((u8)state->alpha);
    } else if (state->phase == 1) {
        if (func_001F51D0(state->events[0]) == 1) {
            return 1;
        }
        pool = 0;
        for (i = 0; i < func_0024E910(*(s32 *)(arg0 + 8)); i++) {
            position = func_0024EC50(*(s32 *)(arg0 + 8), i);
            x = position >> 8;
            y = position & 0xFF;
            if (func_001E2100(x, y, 4) != 0 &&
                (func_001E0700(x, y) >> 5) == 0) {
                pool = func_0024C780(pool, x, y);
            }
        }
        if (func_0024E910(pool) == 0) {
            pool = *(s32 *)(arg0 + 8);
        }
        state->target = func_0024EBD0(pool);
        func_00260AF0(0, state->target, 100, 180);
        func_001E1090(position >> 8, position & 0xFF);
        command[0] = 0x18;
        command[1] = 0;
        command[2] = state->target;
        command[3] = 0;
        result = (u8)func_00255A30(command, arg1);
        state->events[0] = result;
        if (result >= 0) {
            state->count++;
            state->handle = state->target;
        }
        {
            s32 otherY;
            s32 otherX;
            s32 j;
            s32 other;

            for (j = 0; j < func_0024E910(*(s32 *)(arg0 + 8)); j++) {
                other = func_0024EC50(*(s32 *)(arg0 + 8), j);
                if (other != position) {
                    otherX = other >> 8;
                    otherY = other & 0xFF;
                    func_002500C0(otherX, otherY, -1, 7, 3);
                    func_001E1AF0(otherX, otherY, -1, 0);
                }
            }
        }
        state->phase++;
    } else if (state->phase == 2) {
        if (func_001F51D0(state->events[0]) != 0 &&
            func_001F52D0(state->events[0]) == 2 && state->handle >= 0) {
            state->handle = -1;
            command[0] = 0x25B;
            command[1] = 0;
            command[2] = state->target;
            command[3] = 0;
            result = (u8)func_00255A30(command, arg1);
            state->events[state->count] = result;
            if (result >= 0) {
                state->count++;
            }
            state->phase++;
        }
    } else if (state->phase == 3) {
        if (func_0025F670((void *)arg0, arg1, command) != 0) {
            func_00260020((void *)arg0, arg1, arg2, 1, 0, 1);
            func_00260A70(arg1, 0x10);
            state->timer = 0;
            state->phase++;
        }
    } else {
        {
            s32 c;
            s32 b;
            s32 a;
            s32 d;

            a = func_001E1A90(0, 0);
            b = func_001E1A30(0, 0);
            c = func_001E1D10(0, 0);
            d = func_001E1CB0(0, 0);
            func_00199B50(D_002B86E8, a, b, c, d);
        }
        state->alpha += 0xF;
        if (state->alpha > 0x80) {
            state->alpha = 0x80;
        }
        func_001F6CF0((u8)state->alpha);
        if (state->alpha == 0x80) {
            if (state->timer++ > 0x10 && func_0025FD90() == 1) {
                if (func_001DE780() != 0) {
                    func_001DE7E0(1);
                }
                func_001E4530();
                return 0;
            }
        }
    }
    return 1;
}

typedef struct Obj_0025BE50 {
    u16 amount;
    u16 pad2;
    u16 mode;
    u8 pad6[0x102 - 6];
    u16 timer;
} Obj_0025BE50;

extern void func_00255AC0(void *, s32);
extern void func_00260740(s32);
extern void func_00260A70(void *, s32);

s32 func_0025BE50(void *arg0, void *arg1, s32 arg2) {
    extern s32 func_0025F670();
    s32 work[4];
    s32 *workp;
    Obj_0025BE50 *obj;

    workp = work;
    obj = arg1;
    work[0] = 0x3E7;
    work[1] = 0;
    work[2] = 0;
    work[3] = 0;
    func_001DE7E0(0);

    if (arg2 >= 0) {
        func_00255960(arg1);
        obj->amount = 0x80;
        func_00260740(0x10);
        func_00260020(arg0, arg1, arg2, -1, 1, 1);
        func_00255AC0(arg1, 0x1F);
        func_00255AC0(arg1, 0x25B);
        return 1;
    }

    switch (obj->mode) {
    case 0: {
        u16 amount = obj->amount;

        if (amount > 0x3F) {
            amount -= 0xF;
            obj->amount = amount;
        } else {
            amount = 0x30;
            obj->amount = amount;
            if (func_00255B50(arg1) == 1) {
                func_0025F720(arg0, arg1, workp, 0x1F);
                obj->mode++;
            }
        }
        func_001F6CF0((u8)obj->amount);
        break;
    }
    case 1:
        if (func_0025F400(arg0, arg1, workp) != 0) {
            obj->mode++;
        }
        break;
    case 2:
        if (func_0025F670(arg0, arg1, workp) != 0) {
            func_00260020(arg0, arg1, arg2, 1, 0, 1);
            func_00260A70(arg1, 0x10);
            obj->timer = 0;
            obj->mode++;
        }
        break;
    default:
        obj->amount += 0xF;
        if (obj->amount > 0x80) {
            obj->amount = 0x80;
        }
        func_001F6CF0((u8)obj->amount);
        if (obj->amount == 0x80) {
            u16 oldTimer = obj->timer;
            obj->timer = oldTimer + 1;
            if (oldTimer > 0x10 && func_0025FD90() == 1) {
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

typedef struct Obj_0025C0B0 {
    u16 amount;
    u16 pad2;
    u16 mode;
    u8 pad6[0x102 - 6];
    u16 timer;
} Obj_0025C0B0;

extern void func_00255AC0(void *, s32);
extern void func_00260860(s32);
extern void func_00260A70(void *, s32);

s32 func_0025C0B0(void *arg0, void *arg1, s32 arg2) {
    extern s32 func_0025F670();
    s32 work[4];
    s32 *workp;
    Obj_0025C0B0 *obj;

    workp = work;
    obj = arg1;
    work[0] = 0x3E7;
    work[1] = 0;
    work[2] = 0;
    work[3] = 0;
    func_001DE7E0(0);

    if (arg2 >= 0) {
        func_00255960(arg1);
        obj->amount = 0x80;
        func_00260860(0x10);
        func_00260020(arg0, arg1, arg2, -1, 1, 1);
        func_00255AC0(arg1, 0x20B);
        func_00255AC0(arg1, 0x25B);
        return 1;
    }

    switch (obj->mode) {
    case 0: {
        u16 amount;

        obj->timer++;
        amount = obj->amount;
        if (amount > 0x3F) {
            amount -= 0xF;
            obj->amount = amount;
        } else {
            amount = 0x30;
            obj->amount = amount;
            if (obj->timer >= 0x10 && func_00255B50(arg1) == 1) {
                func_0025F720(arg0, arg1, workp, 0x20B);
                obj->mode++;
            }
        }
        func_001F6CF0((u8)obj->amount);
        break;
    }
    case 1:
        if (func_0025F400(arg0, arg1, workp) != 0) {
            obj->mode++;
        }
        break;
    case 2:
        if (func_0025F670(arg0, arg1, workp) != 0) {
            func_00260020(arg0, arg1, arg2, 1, 0, 1);
            func_00260A70(arg1, 0x10);
            obj->timer = 0;
            obj->mode++;
        }
        break;
    default:
        obj->amount += 0xF;
        if (obj->amount > 0x80) {
            obj->amount = 0x80;
        }
        func_001F6CF0((u8)obj->amount);
        if (obj->amount == 0x80) {
            u16 oldTimer = obj->timer;
            obj->timer = oldTimer + 1;
            if (oldTimer > 0x10 && func_0025FD90() == 1) {
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

void func_0024F370(s32, s32);
u8 func_00255A30(s32 *, void *);
void func_00255AC0(void *, s32);
void func_00260740(s32);
void func_00260A70(void *, s32);

typedef struct Command_0025C330 {
    s32 kind;
    s32 value;
    s32 position;
    s32 flags;
} Command_0025C330;

typedef struct Owner_0025C330 {
    u8 pad0[12];
    s32 entity;
} Owner_0025C330;

typedef struct State_0025C330 {
    u16 fade;
    u16 count;
    u16 phase;
    u8 primary[10];
    u8 secondary[10];
    u8 pad1A[6];
    s32 positions[10];
    s32 targets[10];
    u8 pad70[0x64];
    u8 allocated;
    u8 padD5[0x2B];
    u8 stage;
    u8 pad101;
    u16 timer;
} State_0025C330;

static inline u8 *primary_0025C330(u8 *bytes) {
    return bytes + 6;
}

s32 func_0025C330(void *arg0, void *arg1, s32 arg2) {
    s32 complete;
    u8 flags;
    Command_0025C330 command;
    s32 randomX;
    s32 entity;
    s32 index;
    s32 cleanupIndex;
    u8 handle;
    u16 oldTimer;
    u8 *entry;
    u8 *cleanupEntry;
    State_0025C330 *state = arg1;
    Command_0025C330 *cmd = &command;

    cmd->kind = 999;
    cmd->value = 0;
    cmd->position = 0;
    cmd->flags = 0;
    complete = 0;
    flags = 0;
    func_001DE7E0(0);
    if (arg2 >= 0) {
        func_00255960(state);
        index = 0;
        entry = (u8 *)state;
        do {
            randomX = (func_0019A5C8() % 7) << 8;
            *(s32 *)(entry + 0x20) = randomX | (func_0019A5C8() % 7);
            index++;
            entry += 4;
        } while (index < 10);
        state->fade = 0x80;
        func_00255AC0(state, 0x20D);
        func_00255AC0(state, 0x25B);
        return 1;
    }

    switch (state->stage) {
    case 0:
        if (state->phase > 0) {
            oldTimer = state->timer++;
            if (oldTimer == 0) {
                func_00260740(0x10);
            } else if (state->timer >= 0x10) {
                state->timer = 0;
                state->stage++;
            }
        }
        break;
    case 1:
        if (state->phase < 2) {
            oldTimer = state->timer++;
            if (oldTimer == 0) {
                func_00260990(0x3C, 0x3FFF);
            } else if (state->timer >= 0x3C) {
                state->timer = 0;
            }
        } else {
            func_001E4530();
            func_00260A70(state, 0x10);
            state->timer = 0;
            state->stage++;
        }
        break;
    default:
        oldTimer = state->timer++;
        if (oldTimer >= 0x10) {
            flags = 2;
        }
        break;
    }

    switch (state->phase) {
    case 0:
        if (state->fade > 0x30) {
            state->fade -= 15;
        } else {
            state->fade = 0x30;
            if (func_00255B50(state) == 1) {
                func_00261600();
                state->phase++;
            }
        }
        if (state->fade < 0x30) {
            state->fade = 0x30;
        }
        func_001F6CF0((u8)state->fade);
        break;
    case 1: {
        s32 resolvedPosition;
        u8 *primary;
        u8 *activeEntry;
        s32 x;
        s32 y;
        if ((s32)state->fade % 8 == 0) {
            if (state->count < 10) {
                u8 *scanEntry;
                s32 position;
                s32 scanIndex;
                cmd->kind = 0x20D;
                cmd->value = 0;
                cmd->position = state->positions[state->count];
                cmd->flags = 0;
                handle = func_00255A30((s32 *)cmd, state);
                state->primary[state->allocated] = handle;
                if ((s32)handle >= 0) {
                    state->allocated++;
                }
                scanIndex = 0;
                scanEntry = (u8 *)state;
                while (scanIndex < state->count) {
                    position = *(s32 *)(scanEntry + 0x20);
                    if (state->positions[(u16)state->count] == position) {
                        *(s32 *)(scanEntry + 0x20) = position | 0x10000;
                    }
                    scanEntry += 4;
                    scanIndex++;
                }
                state->count++;
            }
        }
        index = 0;
        activeEntry = (u8 *)state;
        while (index < state->count) {
            s32 position;
            primary = &state->primary[index];
            if (func_001F51D0(state->primary[index]) == 1 &&
                func_001F52D0(*primary) == 2) {
                position = *(s32 *)(activeEntry + 0x20);
                if (position >> 16 == 0) {
                    if ((resolvedPosition = func_001E3790(position & 0xFF, position >> 8)) >= 0 &&
                        (x = resolvedPosition & 0xFF) > 0) {
                            y = resolvedPosition >> 8;
                            entity = func_0024DE70(y, x);
                            if (func_00271E40(y, x, 11)) {
                                func_001E42C0(0, -120, 80, 270);
                                resolvedPosition = func_001E1090(entity, 0);
                                func_00260490(resolvedPosition & 0xFF, resolvedPosition >> 8, 0,
                                    func_00271740(9, entity), 1, 1, 11);
                            } else if (func_00267700(y, x) && entity != ((Owner_0025C330 *)arg0)->entity) {
                                func_001E42C0(0, 0, 0, func_001DE210(0x53));
                            } else {
                                cmd->kind = 0x25B;
                                cmd->value = 0;
                                cmd->position = resolvedPosition;
                                cmd->flags = 1;
                                handle = func_00255A30((s32 *)cmd, state);
                                state->secondary[index] = handle;
                                if ((s32)handle >= 0) {
                                    *(s32 *)(activeEntry + 0x48) = resolvedPosition;
                                }
                            }
                    }
                    *(s32 *)(activeEntry + 0x20) |= 0x10000;
                }
            }
            activeEntry += 4;
            index++;
        }

        cleanupIndex = 0;
        cleanupEntry = (u8 *)state;
        do {
            s32 position;
            primary = &state->primary[cleanupIndex];
            if (func_001F51D0(state->primary[cleanupIndex]) == 0 &&
                func_001F51D0(state->secondary[cleanupIndex]) == 0) {
                position = *(s32 *)(cleanupEntry + 0x48);
                if (position > 0) {
                    func_0024F370(position >> 8, position & 0xFF);
                    *(s32 *)(cleanupEntry + 0x48) = 0;
                }
            }
            if (state->count > 0 && func_001F51D0(*primary) == 0 && func_001F51D0(*primary) == 0) {
                complete++;
            }
            cleanupIndex++;
            cleanupEntry += 4;
        } while (cleanupIndex < 10);

        if (complete >= 10) {
            state->fade = 0x30;
            state->phase++;
        } else {
            u8 *releaseEntry;
            s32 releaseIndex;
            releaseIndex = 10;
            releaseEntry = (u8 *)state + 0x28;
            do {
                s32 position = *(s32 *)(releaseEntry + 0x20);
                if (position > 0) {
                    func_0024F370(position >> 8, position & 0xFF);
                }
                releaseIndex++;
                releaseEntry += 4;
            } while (releaseIndex < 20);
            state->fade++;
        }
        break;
    }
    default:
        state->fade += 15;
        if (state->fade > 0x80) {
            state->fade = 0x80;
        }
        func_001F6CF0((u8)state->fade);
        if (state->fade == 0x80) {
            flags |= 1;
        }
        break;
    }
    if (flags == 3) {
        if (func_001DE780()) {
            func_001DE7E0(1);
        }
        func_001E4530();
        return 0;
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_074", func_0025C9E0);

typedef struct State_0025D230 {
    u16 alpha;
    u16 unused2;
    u16 phase;
    u8 handles[0xCE];
    u8 count;
    u8 unusedD5[0x2D];
    u16 timer;
} State_0025D230;

typedef struct Mask_0025D230 {
    u8 unused0[8];
    u32 mask;
} Mask_0025D230;

typedef struct Command_0025D230 {
    s32 id;
    s32 x;
    s32 y;
    s32 z;
} Command_0025D230;

void func_00255AC0(void *, s32);
void func_00260740(s32);
void func_00260A70(void *, s32);

s32 func_0025D230(void *arg0, void *arg1, s32 arg2) {
    s32 i = 0;
    Command_0025D230 data;
    Command_0025D230 *command = &data;
    s32 j;
    State_0025D230 *state = arg1;
    Mask_0025D230 *input = arg0;

    command->id = 999;
    command->x = 0;
    command->y = 0;
    command->z = 0;
    func_001DE7E0(0);
    if (arg2 >= 0) {
        func_00255960(arg1);
        state->alpha = 0x80;
        if (func_0024E910(input->mask) == 1) {
            func_00260AF0(0x10, func_0024EC50(input->mask, 0), 100, 180);
        } else {
            func_00260740(0x10);
        }
        func_00260020(arg0, arg1, arg2, -1, 1, 1);
        func_00255AC0(arg1, 0x211);
        return 1;
    }

    switch (state->phase) {
    case 0:
        if (state->alpha > 0x30) {
            state->alpha -= 15;
        } else {
            state->alpha = 0x30;
            if (func_00255B50(arg1) == 1) {
                func_001E42C0(0, -120, 80, func_001DE210(0x2E0));
                func_0025F720(arg0, arg1, command, 0x211);
                state->phase++;
            }
        }
        if (state->alpha < 0x30) {
            state->alpha = 0x30;
        }
        func_001F6CF0((u8)state->alpha);
        break;
    case 1:
        for (j = 0; j < state->count; j++) {
            if (func_001F51D0(state->handles[j]) == 0) {
                i++;
            }
        }
        if (i >= state->count) {
            func_001E4530();
            i = 0;
            do {
                if ((input->mask >> (21 - i)) & 1) {
                    s32 attackDelta;
                    s32 defenseDelta;
                    if (i < 11) {
                        attackDelta = func_001E0370(0, i, 0) - func_001E0290(0, i, 0);
                        defenseDelta = func_001E0290(0, i, 0) - func_001E0370(0, i, 0);
                        func_00250CA0(0, i, 0, attackDelta);
                        func_00250E80(0, i, 0, defenseDelta);
                    } else {
                        attackDelta = func_001E0370(1, i - 11, 0) - func_001E0290(1, i - 11, 0);
                        defenseDelta = func_001E0290(1, i - 11, 0) - func_001E0370(1, i - 11, 0);
                        func_00250CA0(1, i - 11, 0, attackDelta);
                        func_00250E80(1, i - 11, 0, defenseDelta);
                    }
                }
                i++;
            } while (i < 22);
            func_00260020(arg0, arg1, arg2, 1, 0, 1);
            func_00260A70(arg1, 0x10);
            state->phase++;
        }
        break;
    default:
        state->alpha += 15;
        if (state->alpha > 0x80) {
            state->alpha = 0x80;
        }
        func_001F6CF0((u8)state->alpha);
        if (state->alpha == 0x80) {
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

typedef struct Command_0025D640 {
    s32 unk0;
    s32 kind;
    u32 flags;
    u32 values;
} Command_0025D640;

typedef struct State_0025D640 {
    u16 value;
    u16 unk2;
    u16 stage;
    u8 ids[0xCE];
    u8 count;
    u8 padding[0x2D];
    u16 timer;
} State_0025D640;

void func_00255AC0(void *, s32);
void func_00260740(s32);
void func_00260A70(void *, s32);

s32 func_0025D640(void *arg0, void *arg1, s32 arg2) {
    s32 data[4];
    s32 completed;
    s32 *params = data;
    s32 i;
    Command_0025D640 *command = arg0;
    State_0025D640 *state = arg1;

    params[0] = 999;
    params[1] = 0;
    params[2] = 0;
    params[3] = 0;
    completed = 0;
    func_001DE7E0(0);
    if (arg2 >= 0) {
        func_00255960(arg1);
        state->value = 0x80;
        if (func_0024E910(command->flags) == 1) {
            func_00260AF0(0x10, func_0024EC50(command->flags, 0), 100, 180);
        } else {
            func_00260740(0x10);
        }
        func_00260020(arg0, arg1, arg2, -1, 1, 1);
        func_00255AC0(arg1, 0x211);
        return 1;
    }

    switch (state->stage) {
    case 0:
        if (state->value > 0x30) {
            state->value -= 15;
        } else {
            state->value = 0x30;
            if (func_00255B50(arg1) == 1) {
                func_001E42C0(0, -120, 80, 0x106);
                func_0025F720(arg0, arg1, params, 0x211);
                state->stage++;
            }
        }
        if (state->value < 0x30) {
            state->value = 0x30;
        }
        func_001F6CF0((u8)state->value);
        break;
    case 1:
        for (i = 0; i < state->count; i++) {
            if (func_001F51D0(state->ids[i]) == 0) {
                completed++;
            }
        }
        if (completed >= state->count) {
            func_001E4530();
            completed = 0;
            do {
                if ((command->flags >> (21 - completed)) & 1) {
                    if (completed < 11) {
                        func_00250E80(0, completed, command->values >> 16, command->values & 0xFFFF);
                        if (command->kind == 1) {
                            func_00250CA0(0, completed, command->values >> 16, command->values & 0xFFFF);
                        }
                    } else {
                        func_00250E80(1, completed - 11, command->values >> 16, command->values & 0xFFFF);
                        if (command->kind == 1) {
                            func_00250CA0(1, completed - 11, command->values >> 16, command->values & 0xFFFF);
                        }
                    }
                }
                completed++;
            } while (completed < 22);
            func_00260020(arg0, arg1, arg2, 1, 0, 1);
            func_00260A70(arg1, 0x10);
            state->stage++;
        }
        break;
    default:
        state->value += 15;
        if (state->value > 0x80) {
            state->value = 0x80;
        }
        func_001F6CF0((u8)state->value);
        if (state->value == 0x80 && state->timer++ > 16 && func_0025FD90() == 1) {
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

typedef struct Input_0025D9D0 {
    s32 unused;
    s32 selection;
    u32 mask;
} Input_0025D9D0;

typedef struct State_0025D9D0 {
    u16 alpha;
    u16 unused;
    u16 step;
    u8 effects[0xCE];
    u8 count;
    u8 padD5[0x2D];
    u16 timer;
} State_0025D9D0;

typedef struct Packet_0025D9D0 {
    s32 type;
    s32 unused;
    s32 position;
    s32 flag;
} Packet_0025D9D0;

void func_0024F370(s32, s32);
u8 func_00255A30(s32 *, void *);
void func_00255AC0(void *, s32);
void func_00260740(s32);
void func_00260A70(void *, s32);

s32 func_0025D9D0(void *arg0, void *arg1, s32 arg2) {
    Packet_0025D9D0 data;
    s32 done;
    Packet_0025D9D0 *packet = &data;
    s32 i;
    s32 j;
    u8 effect;
    Input_0025D9D0 *input = arg0;
    State_0025D9D0 *state = arg1;

    data.type = 999;
    data.unused = 0;
    data.position = 0;
    data.flag = 0;
    done = 0;
    func_001DE7E0(0);
    if (arg2 >= 0) {
        func_00255960(state);
        state->alpha = 0x80;
        func_00260740(0x10);
        func_00255AC0(state, 0x16);
        func_00255AC0(state, 0x25B);
        return 1;
    }

    switch (state->step) {
    case 0:
        if (state->alpha > 0x30) {
            state->alpha -= 15;
        } else {
            state->alpha = 0x30;
            if (func_00255B50(state) == 1) {
                packet->type = 0x16;
                packet->unused = 0;
                packet->position = 0;
                packet->flag = 0;
                effect = func_00255A30((s32 *)packet, state);
                state->effects[state->count] = effect;
                if (effect >= 0) {
                    state->count++;
                }
                state->step++;
            }
        }
        if (state->alpha < 0x30) {
            state->alpha = 0x30;
        }
        func_001F6CF0((u8)state->alpha);
        break;

    case 1: {
        s32 selection;
        s32 y;
        s32 x;
        s32 position;

        if (func_001F51D0(state->effects[0]) == 1) {
            return 1;
        }
        selection = func_0024CA40(0, 0, 0, 3, 0x34, 0xE);
        func_00272330(selection, input->selection);
        if (0 < func_0024E910(selection)) {
            do {
                position = func_0024EC50(selection, done);
                x = position >> 8;
                y = position & 0xFF;
                func_002503B0(x, y, 0);
                func_001E15E0(x, y, 0);
                func_00250CA0(x, y, 4, 0);
                func_00250E80(x, y, 4, 0);
                done++;
            } while (done < func_0024E910(selection));
        }
        state->step++;
        break;
    }

    case 2:
        i = 0;
        do {
            if (((input->mask >> (21 - i)) & 1) == 1) {
                if (i < 11) {
                    packet->type = 0x25B;
                    packet->unused = 0;
                    packet->position = i;
                    packet->flag = 1;
                    effect = func_00255A30((s32 *)packet, state);
                    *((u8 *)state + state->count + 6) = effect;
                    if (effect >= 0) {
                        state->count++;
                    }
                } else {
                    packet->type = 0x25B;
                    packet->unused = 0;
                    packet->position = (i - 11) | 0x100;
                    packet->flag = 1;
                    effect = func_00255A30((s32 *)packet, state);
                    *((u8 *)state + state->count + 6) = effect;
                    if (effect >= 0) {
                        state->count++;
                    }
                }
            }
            i++;
        } while (i < 22);
        state->alpha = 0;
        state->step++;

    case 3:
        for (j = 0; j < state->count; j++) {
            if (func_001F51D0(state->effects[j]) == 0) {
                done++;
            }
        }
        if (done < state->count) {
            return 1;
        }
        i = 0;
        do {
            if ((input->mask >> (21 - i)) & 1) {
                if (i < 11) {
                    func_0024F370(0, i);
                } else {
                    func_0024F370(1, i - 11);
                }
            }
            i++;
        } while (i < 22);
        state->step++;
        func_00260A70(state, 0x10);
        state->timer = 0;
        break;

    default:
        state->alpha += 15;
        if (state->alpha > 0x80) {
            state->alpha = 0x80;
        }
        func_001F6CF0((u8)state->alpha);
        if (state->alpha == 0x80) {
            if (state->timer++ > 16) {
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

INCLUDE_ASM("asm/nonmatchings/main_074", func_0025DE70);

typedef struct {
    u32 unk0;
    u32 target;
    s32 mask;
    u32 position;
} Command_0025E200;

typedef struct {
    s8 ready : 1;
    s8 reserved : 7;
} Flags_0025E200;

typedef struct {
    u16 alpha;
    u16 unk2;
    u16 phase;
    u8 slots[0x7A];
    Flags_0025E200 flags;
    u8 unk81[0x53];
    u8 count;
    u8 unkD5[0x2D];
    u16 timer;
} State_0025E200;

void func_00255AC0(void *, s32);
void func_00260740(s32);
void func_00260A70(void *, s32);

s32 func_0025E200(void *arg0, void *arg1, s32 arg2) {
    extern s32 func_001E1D10();
    extern s32 func_001E19D0();
    extern s32 func_00255A30(s32 *, void *);
    s32 request[4];
    s32 *data = request;
    Command_0025E200 *command = arg0;
    State_0025E200 *state = arg1;

    request[0] = 999;
    request[1] = 0;
    request[2] = 0;
    request[3] = 0;
    func_001DE7E0(0);
    if (arg2 >= 0) {
        func_00255960(state);
        state->alpha = 0x80;
        func_00255AC0(state, 0x213);
        func_00255AC0(state, 0x214);
        if (func_0024E910(command->mask) == 1) {
            func_00260AF0(0, func_0024EC50(command->mask, 0), 100, 180);
        } else {
            func_00260740(0);
        }
        func_00260020(command, state, arg2, -1, 1, 1);
        return 1;
    }

    switch (state->phase) {
    case 0:
        if (state->alpha > 0x30) {
            state->alpha -= 15;
        } else {
            state->alpha = 0x30;
            if (state->flags.ready == 0) {
                if (func_00255B50(state) == 1) {
                    state->flags.ready = 1;
                }
            } else {
                s32 result;
                data[0] = 0x213;
                data[1] = 0;
                data[2] = (u16)command->target;
                data[3] = 0;
                result = func_00255A30(data, state);
                if (result >= 0) {
                    state->slots[state->count] = result;
                    state->count++;
                    state->phase++;
                } else if ((u32)(result + 2) < 2) {
                    func_001E4530();
                    return 0;
                }
            }
        }
        if (state->alpha < 0x30) {
            state->alpha = 0x30;
        }
        func_001F6CF0((u8)state->alpha);
        break;

    case 1:
        if (func_001F51D0(state->slots[state->count - 1]) == 1 &&
            func_001F52D0(state->slots[state->count - 1]) == 2) {
            if ((command->target >> 16) == 1) {
                func_001F5970(command->target & 0xFFFF, 0);
                func_001F66A0((u16)command->target, 0);
                if (func_001E1D10((command->target & 0xFFFF) >> 8,
                                  command->target & 0xFF) == 0) {
                    func_001E19D0((command->target & 0xFFFF) >> 8,
                                  command->target & 0xFF, 0x80);
                    func_001E1C10((command->target & 0xFFFF) >> 8,
                                  command->target & 0xFF, 1, 0x80);
                }
            }
            func_001DFD50((command->target & 0xFFFF) >> 8, command->target & 0xFF,
                          command->position & 0xFF, command->position >> 8);
            state->timer = 0;
            state->phase++;
        }
        break;

    case 2:
        if (state->timer == 0) {
            if (func_0024E910(command->mask) == 1) {
                func_00260AF0(30, func_0024EC50(command->mask, 0), 100, 180);
            } else {
                func_00260740(16);
            }
        }
        if (state->timer++ >= 24 &&
            func_001F51D0(state->slots[state->count - 1]) != 1) {
            s32 result;
            data[0] = 0x214;
            data[1] = 0;
            data[2] = (u16)command->target;
            data[3] = 0;
            result = func_00255A30(data, state);
            if (result >= 0) {
                state->slots[state->count] = result;
                state->count++;
                state->phase++;
            } else if ((u32)(result + 2) < 2) {
                func_001E4530();
                return 0;
            }
        }
        break;

    case 3:
        if (func_001F51D0(state->slots[state->count - 1]) != 1) {
            state->phase++;
            func_00260A70(state, 16);
            func_00260020(command, state, arg2, 1, 0, 1);
        }
        break;

    default:
        state->alpha += 15;
        if (state->alpha > 0x80) {
            state->alpha = 0x80;
        }
        func_001F6CF0((u8)state->alpha);
        if (state->alpha == 0x80) {
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

INCLUDE_ASM("asm/nonmatchings/main_074", func_0025E710);

void func_0025EBE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_s0;
    s32 temp_s1;
    s32 temp_v0;

    temp_v0 = func_0025ECB0();
    if (temp_v0 >= 0) {
        temp_s0 = func_001E1090(arg0, arg1);
        temp_s1 = func_001E1090(arg2, arg3);
        func_001DFD50(arg0, arg1, temp_v0 & 0xFF, temp_v0 >> 8);
        func_001DFD50(arg2, arg3, temp_s0 & 0xFF, temp_s0 >> 8);
        func_001DFD50(arg0, arg1, temp_s1 & 0xFF, temp_s1 >> 8);
    }
}

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

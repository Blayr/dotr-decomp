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

INCLUDE_ASM("asm/nonmatchings/main_074", func_00256AB0);

INCLUDE_ASM("asm/nonmatchings/main_074", func_00256D80);

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

INCLUDE_ASM("asm/nonmatchings/main_074", func_00258760);

INCLUDE_ASM("asm/nonmatchings/main_074", func_00258E20);

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

INCLUDE_ASM("asm/nonmatchings/main_074", func_0025A060);

INCLUDE_ASM("asm/nonmatchings/main_074", func_0025A4C0);

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

INCLUDE_ASM("asm/nonmatchings/main_074", func_0025AD60);

INCLUDE_ASM("asm/nonmatchings/main_074", func_0025B050);

INCLUDE_ASM("asm/nonmatchings/main_074", func_0025B330);

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

INCLUDE_ASM("asm/nonmatchings/main_074", func_0025B900);

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
extern s32 func_0025F400(void *, void *, s32 *);
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

INCLUDE_ASM("asm/nonmatchings/main_074", func_0025C330);

INCLUDE_ASM("asm/nonmatchings/main_074", func_0025C9E0);

INCLUDE_ASM("asm/nonmatchings/main_074", func_0025D230);

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

INCLUDE_ASM("asm/nonmatchings/main_074", func_0025D9D0);

INCLUDE_ASM("asm/nonmatchings/main_074", func_0025DE70);

INCLUDE_ASM("asm/nonmatchings/main_074", func_0025E200);

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

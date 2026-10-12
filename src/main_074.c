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

INCLUDE_ASM("asm/nonmatchings/main_074", func_00254C90);

INCLUDE_ASM("asm/nonmatchings/main_074", func_002550C0);

INCLUDE_ASM("asm/nonmatchings/main_074", func_00255960);

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

INCLUDE_ASM("asm/nonmatchings/main_074", func_002560C0);

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
void func_00255960(void *);
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

INCLUDE_ASM("asm/nonmatchings/main_074", func_00259D90);

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

INCLUDE_ASM("asm/nonmatchings/main_074", func_0025AA80);

INCLUDE_ASM("asm/nonmatchings/main_074", func_0025AD60);

INCLUDE_ASM("asm/nonmatchings/main_074", func_0025B050);

INCLUDE_ASM("asm/nonmatchings/main_074", func_0025B330);

INCLUDE_ASM("asm/nonmatchings/main_074", func_0025B610);

INCLUDE_ASM("asm/nonmatchings/main_074", func_0025B900);

typedef struct Obj_0025BE50 {
    u16 amount;
    u16 pad2;
    u16 mode;
    u8 pad6[0x102 - 6];
    u16 timer;
} Obj_0025BE50;

extern void func_00255960(void *);
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

extern void func_00255960(void *);
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

INCLUDE_ASM("asm/nonmatchings/main_074", func_0025D640);

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

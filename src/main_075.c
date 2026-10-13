#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_075", func_0025ED20);

INCLUDE_ASM("asm/nonmatchings/main_075", func_0025EE40);

INCLUDE_ASM("asm/nonmatchings/main_075", func_0025EF40);

s32 func_0025F2A0(void) {
    s32 row;
    s32 column;
    s32 result;

    for (row = 0; row < 7; row++) {
        for (column = 0; column < 7; column++) {
            result = func_001E3790(row, column);
            if (result < 0) {
                return result;
            }
        }
    }
    return -1;
}

void func_0025F310(void) {
    s32 var_s0;
    s32 var_s1;

    var_s0 = 0;
    var_s1 = 0;
    do {
        do {
            if (func_001E22B0(var_s0, var_s1) == 8) {
                func_001E2220(var_s0, var_s1, 7);
            }
            var_s1 += 1;
        } while (var_s1 < 7);
        var_s0 += 1;
        var_s1 = 0;
    } while (var_s0 < 7);
}

s32 func_0025F390(void *arg0) {
    s32 i;

    for (i = 0; i < ((u8 *)arg0)[0xD4]; i++) {
        if (func_001F51D0(((u8 *)((u32)arg0 + i))[6]) != 0) {
            return -1;
        }
    }
    return 1;
}

typedef struct State_0025F400 {
    u16 unknown0;
    u16 timer;
    u16 unknown4;
    u8 ids[0x1A];
    s32 entries[0x2D];
    u8 count;
} State_0025F400;

typedef struct Source_0025F400 {
    u8 padding[8];
    s32 mask;
} Source_0025F400;

typedef struct Command_0025F400 {
    s32 kind;
    s32 flags;
    s32 position;
    s32 extra;
} Command_0025F400;


s32 func_0025F400(void *arg0, void *arg1, void *arg2) {
    s32 i;
    u32 mask;
    Source_0025F400 *source = arg0;
    State_0025F400 *state = arg1;
    Command_0025F400 *command = arg2;
    u16 timer;

    mask = 0;
    for (i = 0; i < state->count; i++) {
        if (func_001F51D0(state->ids[i]) != 0 &&
            func_001F52D0(state->ids[i]) == 2 &&
            state->entries[i] >= 0) {
            state->entries[i] = -1;
            state->timer = 1;
        }
    }
    timer = state->timer;
    if (timer > 0) {
        state->timer = timer + 1;
        if (timer > 0x10) {
            s32 position;
            u8 id;
            s32 final_y;
            s32 final_x;
            s32 j;

            for (i = 0; i < func_0024E910(source->mask); i++) {
                s32 value = func_0024EC50(source->mask, i);
                s32 y;
                s32 x;

                x = value >> 8;
                y = value & 0xFF;

                if (func_001E2100(x, y, 4) != 0 &&
                    (func_001E0700(x, y) >> 5) == 0) {
                    mask = func_0024C780(mask, x, y);
                }
            }
            if (func_0024E910(mask) == 0) {
                mask = source->mask;
            }
            position = func_0024EBD0(mask);
            func_001E1090(position >> 8, position & 0xFF);
            command->kind = 0x25B;
            command->flags = 0;
            command->position = position;
            command->extra = 0;
            id = func_00255A30(command, state);
            state->ids[state->count] = id;
            if (id >= 0) {
                state->count++;
            }
            func_00260AF0(0, position, 0x64, 0xB4);
            for (j = 0; j < func_0024E910(source->mask); j++) {
                s32 value = func_0024EC50(source->mask, j);

                if (value != position) {
                    final_x = value >> 8;
                    final_y = value & 0xFF;

                    func_002500C0(final_x, final_y, -1, 7, 3);
                    func_001E1AF0(final_x, final_y, -1, 0);
                }
            }
            state->timer = 0;
            return 1;
        }
    }
    return 0;
}

void func_0024F370(s32, s32);

typedef struct {
    u8 pad[8];
    u32 flags;
} Flags_0025F670;

s32 func_0025F670(void *arg0, void *arg1) {
    s32 var_s1;

    if (func_0025F390(arg1) == 1) {
        var_s1 = 0;
        do {
            if (((((Flags_0025F670 *)arg0)->flags >> (0x15 - var_s1)) & 1) == 1) {
                if (var_s1 < 0xB) {
                    func_0024F370(0, var_s1);
                } else {
                    func_0024F370(1, var_s1 - 0xB);
                }
            }
            var_s1 += 1;
        } while (var_s1 < 0x16);
        return 1;
    }
    return 0;
}


typedef struct Source_0025F720 {
    s32 pad[2];
    s32 handle;
} Source_0025F720;
typedef struct Request_0025F720 {
    s32 type, zero, value, flag;
} Request_0025F720;
typedef struct Result_0025F720 {
    u8 pad[6];
    u8 status[26];
    s32 values[45];
    u8 count;
} Result_0025F720;

void func_0025F720(void *arg0, void *arg1, void *arg2, s32 arg3) {
    s32 index;
    s32 count;
    s32 value;
    s64 flag;
    u8 result;
    Source_0025F720 *src = arg0;
    Result_0025F720 *dst = arg1;
    Request_0025F720 *req = arg2;

    count = func_0024E910(src->handle);
    for (index = 0; index < count; index++) {
        value = func_0024EC50(src->handle, index);
        req->type = arg3;
        req->zero = 0;
        req->value = value;
        if (arg3 == 0x25B) {
            flag = 1;
        } else {
            flag = 0;
        }
        req->flag = flag;
        result = func_00255A30(req, dst);
        dst->status[dst->count] = result;
        if ((s32)result >= 0) {
            dst->values[dst->count] = value;
            dst->count++;
        }
    }
}

typedef struct Source_0025F820 {
    u8 pad[0xC];
    u32 flags;
} Source_0025F820;

typedef struct Results_0025F820 {
    u8 pad[6];
    u8 results[0x1A];
    s32 slots[45];
    u8 count;
} Results_0025F820;

typedef struct Request_0025F820 {
    s32 id;
    s32 mode;
    s32 slot;
    u32 special;
} Request_0025F820;


void func_0025F820(void *arg0, void *arg1, void *arg2, s32 arg3) {
    Source_0025F820 *source = arg0;
    Results_0025F820 *results = arg1;
    Request_0025F820 *request = arg2;
    s32 special;
    s32 i;

    i = 0;
    do {
        special = 1;
        if (((source->flags >> (0x15 - i)) & 1) == 1) {
            if (i < 0xB) {
                request->id = arg3;
                request->mode = 0;
                request->slot = i;
                if (arg3 == 0x25B) {
                    special = 1;
                } else {
                    special = 0;
                }
                request->special = special;
                if ((results->results[results->count] = func_00255A30(request, results)) >= 0) {
                    results->slots[results->count] = i;
                    results->count++;
                }
            } else {
                request->id = arg3;
                request->mode = 0;
                request->slot = (i - 0xB) | 0x100;
                if (arg3 == 0x25B) {
                    special = 1;
                } else {
                    special = 0;
                }
                request->special = special;
                if ((results->results[results->count] = func_00255A30(request, results)) >= 0) {
                    results->slots[results->count] = ((u32)i - 0xB) | 0x100;
                    results->count++;
                }
            }
        }
        i++;
    } while (i < 0x16);
}

typedef struct {
    u32 unused;
    u32 flags;
} Source_0025F990;

typedef struct {
    u8 unused[6];
    u8 results[26];
    s32 slots[45];
    u8 count;
} Output_0025F990;

typedef struct {
    s32 id;
    s32 unused;
    s32 slot;
    u32 enabled;
} Request_0025F990;


void func_0025F990(void *arg0, void *arg1, void *arg2, s32 arg3) {
    Source_0025F990 *source = arg0;
    Output_0025F990 *output = arg1;
    Request_0025F990 *request = arg2;
    s32 enabled;
    s32 i;

    i = 0;
    do {
        enabled = 1;
        if (((source->flags >> (21 - i)) & 1) == 1) {
            if (i < 11) {
                request->id = arg3;
                request->unused = 0;
                request->slot = i;
                if (arg3 == 0x25B) {
                    enabled = 1;
                } else {
                    enabled = 0;
                }
                request->enabled = enabled;
                if ((output->results[output->count] = func_00255A30(request, output)) >= 0) {
                    output->slots[output->count] = i;
                    output->count++;
                }
            } else {
                request->id = arg3;
                request->unused = 0;
                request->slot = (i - 11) | 0x100;
                if (arg3 == 0x25B) {
                    enabled = 1;
                } else {
                    enabled = 0;
                }
                request->enabled = enabled;
                if ((output->results[output->count] = func_00255A30(request, output)) >= 0) {
                    output->slots[output->count] = ((u32)i - 11) | 0x100;
                    output->count++;
                }
            }
        }
        i++;
    } while (i < 22);
}

INCLUDE_ASM("asm/nonmatchings/main_075", func_0025FB00);

INCLUDE_ASM("asm/nonmatchings/main_075", func_0025FC30);

s32 func_0025FD90(void) {
    s32 row;
    s32 col;
    s32 total;
    s32 done;
    s32 cell;
    s32 kind;
    extern s32 func_001E1CB0();
    extern s32 func_001E1A30();
    extern s32 func_001E1D10();
    extern s32 func_001E1A90();

    total = 0;
    done = 0;
    for (row = 0; row < 7; row++) {
        for (col = 0; col < 7; col++) {
            cell = func_001E3790(row, col);
            if (cell >= 0) {
                total++;
                if (func_001E1CB0(cell >> 8, cell & 0xFF) == func_001E1A30(cell >> 8, cell & 0xFF)) {
                    if ((func_001E2100(cell >> 8, cell & 0xFF, 4) != 0 || (cell & 0xFF) == 0) && (cell & 0xFF) < 6) {
                        kind = func_001E1D10(cell >> 8, cell & 0xFF);
                        if (kind == 0 || kind == 0x80) {
                            if (func_001E1A90(cell >> 8, cell & 0xFF) == 0x80) {
                                func_0025FF30(cell >> 8, cell & 0xFF);
                            }
                            done++;
                        }
                    } else {
                        if (func_001E1A30(cell >> 8, cell & 0xFF) == 0x80) {
                            func_0025FF30(cell >> 8, cell & 0xFF);
                        }
                        done++;
                    }
                }
            }
        }
    }
    if (total == done) {
        return 1;
    }
    return 0;
}

void func_0025FF30(s32 arg0, s32 arg1) {
    extern s32 func_001E19D0();
    extern s32 func_001E1970();

    func_001E1840(arg0, arg1, 1);
    if (func_001E2100(arg0, arg1, 4) != 0 || arg1 == 0) {
        func_001E18A0(arg0, arg1, 7);
        func_001E19D0(arg0, arg1, 0x80);
        func_001E1C10(arg0, arg1, 1, 0x80);
    } else {
        func_001E18A0(arg0, arg1, 7);
        func_001E19D0(arg0, arg1, 0x80);
        func_001E1C10(arg0, arg1, 0, 0);
    }
    func_001E1970(arg0, arg1, 0x80);
    func_001E1B70(arg0, arg1, 1, 0x80);
}

typedef struct {
    u8 pad00[8];
    u32 bits;
} Owner_00260020;

typedef struct {
    u8 pad00[0xCC];
    u32 bits;
} Field_00260020;


void func_00260020(void *arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    Owner_00260020 *owner = arg0;
    Field_00260020 *field = arg1;
    s32 i;
    extern s32 func_001E1A30();
    extern s32 func_001E1A90();

    for (i = 0; i < 22; i++) {
        if (((owner->bits >> (21 - i)) & 1) == 1) {
            if (i < 11) {
                func_001F5970(i, arg4);
            } else {
                func_001F5970((i - 11) | 0x100, arg4);
            }
        } else if (arg3 < 0) {
            if (i < 11) {
                if (func_001E1A90(0, i) > 0 && func_001E1A30(0, i) > 0) {
                    func_002500C0(0, i, arg3, arg5, 1);
                    field->bits = func_0024C780(field->bits, 0, i);
                }
            } else if (func_001E1A90(1, i - 11) > 0 && func_001E1A30(1, i - 11) > 0) {
                func_002500C0(1, i - 11, arg3, arg5, 1);
                field->bits = func_0024C780(field->bits, 1, i - 11);
            }
        } else if (((field->bits >> (21 - i)) & 1) == 1) {
            if (i < 11) {
                func_002500C0(0, i, arg3, arg5, 1);
            } else {
                func_002500C0(1, i - 11, arg3, arg5, 1);
            }
        }
    }
}

void func_001E42C0(s32, s32, s32, s32);
void func_00255AC0(void *, s32);

typedef struct State_00260200 {
    u32 unknown;
    u16 phase;
    u8 handles[0xCE];
    u8 index;
} State_00260200;

s32 func_00260200(void *arg0, void *arg1, s32 arg2) {
    s32 request[4];
    s32 *p = request;
    State_00260200 *state = arg1;

    request[0] = 0x3E7;
    request[1] = 0;
    request[2] = 0;
    request[3] = 0;
    if (arg2 >= 0) {
        func_00255960(arg1);
        func_00255AC0(arg1, 0x201);
    } else {
        switch (state->phase) {
        case 0:
            if (func_00255B50(arg1) == 1) {
                state->phase++;
                func_001E42C0(0, -0x78, 0x50, 0x104);
                p[0] = 0x201;
                p[1] = 0;
                p[2] = *(s32 *)((u8 *)arg0 + 8);
                p[3] = 0;
                state->handles[state->index] = func_00255A30(p, arg1);
            }
            break;
        default:
            if (func_001F51D0(state->handles[0]) == 0) {
                func_001E4530();
                return 0;
            }
            break;
        }
    }
    return 1;
}

typedef struct {
    u8 padding[8];
    s32 id;
    u32 duration;
} Config_00260320;

typedef struct {
    u16 ticks;
    u16 padding2;
    u16 phase;
    u8 padding6[0xFC];
    u16 fade;
} State_00260320;

void func_001E42C0(s32, s32, s32, s32);
void func_00260A70(void *, s32);
void func_00260AF0(s32, s32, s32, s32);

s32 func_00260320(void *arg0, void *arg1, s32 arg2) {
    State_00260320 *state = arg1;
    Config_00260320 *config = arg0;
    s32 id;
    u16 fade;

    if (config->id != 0xFFFF) {
        func_001DE7E0(0);
    }
    if (arg2 >= 0) {
        func_00255960(state);
        id = config->id;
        if (id != 0xFFFF) {
            func_00260AF0(0, id, 0x12C, 0x12C);
            func_001E42C0(0, -0x78, 0x50, 0x10E);
        }
        state->ticks++;
    } else {
        switch (state->phase) {
        case 0:
            if (state->ticks++ <= config->duration) {
                return 1;
            }
            func_001E4530();
            if (config->id != 0xFFFF) {
                func_00260A70(state, 0x10);
            }
            state->phase++;
            break;
        default:
            if (config->id != 0xFFFF) {
                fade = state->fade;
                state->fade = fade + 1;
                if (fade > 0x10) {
                    if (func_001DE780() != 0) {
                        func_001DE7E0(1);
                    }
                    func_001E4530();
                    return 0;
                }
            } else {
                func_001E4530();
                return 0;
            }
            break;
        }
    }
    return 1;
}

void func_00260490(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    u8 colorData[4];
    s32 y;
    s32 yMax;
    s32 yMin;
    u8 *color = colorData;
    s32 xMax;
    s32 x;
    s32 i;

    if (arg6 > 0) {
        switch (arg6) {
        case 0x10:
            color[2] = 0;
            color[1] = 0xFF;
            color[0] = 0;
            color[3] = 0x80;
            break;
        case 0xF:
            color[2] = 0xFF;
            color[1] = 0;
            color[0] = 0x80;
            color[3] = 0x80;
            break;
        case 0xD:
            color[2] = 0;
            color[1] = 0x80;
            color[0] = 0xFF;
            color[3] = 0x80;
            break;
        case 0xB:
            color[2] = 0;
            color[1] = 0xFF;
            color[0] = 0xFF;
            color[3] = 0x80;
            break;
        default:
            color[2] = 0xFF;
            color[1] = 0xFF;
            color[0] = 0xFF;
            color[3] = 0x80;
            break;
        }
    } else {
        color[2] = 0;
        color[1] = 0;
        color[0] = 0;
        color[3] = 0xFF;
    }
    if (arg5 == 0x12) {
        i = 0;
        do {
            func_001E3060(i, arg1, arg2, (s32) color, arg4);
            func_001E3060(arg0, i, arg2, (s32) color, arg4);
            i++;
        } while (i < 7);
    } else {
        x = func_00250860(0, arg0 - (arg3 == 1 ? 2 : 1));
        if (arg0 + (arg3 == 1 ? 2 : 1) >= 7) {
            xMax = 6;
        } else {
            xMax = arg0 + (arg3 == 1 ? 2 : 1);
        }
        yMin = func_00250860(0, arg1 - (arg3 == 1 ? 2 : 1));
        if (arg1 + (arg3 == 1 ? 2 : 1) >= 7) {
            yMax = 6;
        } else {
            yMax = arg1 + (arg3 == 1 ? 2 : 1);
        }
        for (; x <= xMax; x++) {
            for (y = yMin; y <= yMax; y++) {
                func_001E3060(x, y, arg2, (s32) color, arg4);
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/main_075", func_00260740);

INCLUDE_ASM("asm/nonmatchings/main_075", func_002607D0);

INCLUDE_ASM("asm/nonmatchings/main_075", func_00260860);

void func_002608F0(s32 arg0) {
    f32 sp20[4];
    f32 sp30[4];
    f32 sp40[4];

    func_001FA810(0, 0);
    switch ((u8)arg0) {
    case 0:
        func_001E10F0(3, 3, 0x190, &sp20);
        func_00255E90(&sp30);
        func_001FC950(&sp30, &sp40);
        func_001FA8A0(0, 0, 3, 0, 0, &sp20);
        func_001FA8A0(0, 0, 4, 0, 0, &sp40);
        break;
    }
}

typedef struct {
    s32 x;
    s32 y;
    s32 z;
    s32 w;
} Vec4_00260990;

void func_001FC890(f32 *, void *);

void func_00260990(s32 arg0, s32 arg1) {
    Vec4_00260990 *rotation;
    Vec4_00260990 sp40;
    f32 sp50[4];
    s32 var_v0;
    s32 var_v1;

    rotation = &sp40;
    func_001FA810(0, 0);
    func_001FC890(func_001FAF60(0), rotation);
    if ((rotation->y + arg1) >= 0) {
        var_v1 = rotation->y + arg1;
    } else {
        var_v1 = -(rotation->y + arg1);
    }
    if (var_v1 >= 0xFFFF) {
        var_v0 = ((rotation->y + arg1) - 0x8000) - 0x7FFF;
    } else {
        var_v0 = rotation->y + arg1;
    }
    rotation->y = var_v0;
    func_001FC950(rotation, sp50);
    func_001FA8A0(0, 0, 4, arg0 & 0xFF, 0, sp50);
}

INCLUDE_ASM("asm/nonmatchings/main_075", func_00260A70);

INCLUDE_ASM("asm/nonmatchings/main_075", func_00260AF0);

INCLUDE_ASM("asm/nonmatchings/main_075", func_00260D10);

INCLUDE_ASM("asm/nonmatchings/main_075", func_00260EB0);

INCLUDE_ASM("asm/nonmatchings/main_075", func_002610D0);

void func_002612E0(void *arg0, s32 arg1, s32 arg2) {
    s32 temp_a0;
    s32 temp_s1;
    s32 var_a1;

    temp_s1 = func_001DF540(arg1 >> 8, arg1 & 0xFF);
    func_001F6160(arg1, arg0);
    ((s32 *)arg0)[0] += arg2;
    temp_a0 = *(s32 *)((u8 *)temp_s1 + 0x30);
    var_a1 = 0x47FF - temp_a0;
    if (var_a1 < 0) {
        var_a1 = 0x147FE - temp_a0;
    }
    ((s32 *)arg0)[1] += var_a1;
    ((s32 *)arg0)[2] += 0x2000;
}

void func_00261380(void *arg0, s32 arg1, s32 arg2) {
    s32 temp_a0;
    s32 temp_s1;
    s32 var_a1;

    temp_s1 = func_001DF540(arg1 >> 8, arg1 & 0xFF);
    func_001F6160(arg1, arg0);
    ((s32 *)arg0)[0] += arg2;
    temp_a0 = *(s32 *)((u8 *)temp_s1 + 0x30);
    var_a1 = 0x3FFF - temp_a0;
    if (var_a1 < 0) {
        var_a1 = 0x13FFE - temp_a0;
    }
    ((s32 *)arg0)[1] += var_a1;
    ((s32 *)arg0)[2] += 0x1000;
}

void func_00261420(void *arg0, s32 arg1, s32 arg2) {
    s32 temp_a0;
    s32 *temp_s1;
    s32 var_a1;

    temp_s1 = (s32 *)func_001DF540(arg1 >> 8, arg1 & 0xFF);
    func_001F6160(arg1, arg0);
    ((s32 *)arg0)[0] += arg2;
    temp_a0 = temp_s1[12];
    var_a1 = 0xC7FF - temp_a0;
    if (var_a1 < 0) {
        var_a1 = 0x1C7FE - temp_a0;
    }
    ((s32 *)arg0)[1] += var_a1;
    ((s32 *)arg0)[2] += 0x2000;
}

INCLUDE_ASM("asm/nonmatchings/main_075", func_002614C0);

void func_00261570(s32 arg0, s32 arg1, u8 arg2, u8 arg3) {
    func_00260AF0(arg0, arg1, arg2, arg3);
}

void func_00261580(void) {
    s32 params[4];
    s32 position[4];
    s32 converted[4];

    func_001FA810(0, 0);
    func_001E10F0(3, 3, 0x3E8, params);
    func_00255FE0(position);
    func_001FC950(position, converted);
    func_001FA8A0(0, 0, 3, 0, 0, params);
    func_001FA8A0(0, 0, 4, 0, 0, converted);
}

void func_00261600(void) {
    s32 sp10[4];
    s32 sp20[4];
    s32 sp30[4];

    func_001FA810(0, 0);
    func_001E10F0(3, 3, 0x3E8, sp10);
    func_00256050(sp20);
    func_001FC950(sp20, sp30);
    func_001FA8A0(0, 0, 3, 0, 0, sp10);
    func_001FA8A0(0, 0, 4, 0, 0, sp30);
}

void func_00261680(s32 arg0) {
    f32 temp_f0;

    if (func_001F6620(arg0) != 4) {
        func_001F66A0(arg0, 4);
        return;
    }
    temp_f0 = func_001F67C0(arg0, 4);
    if (!(temp_f0 < 16.0f)) {
        func_001F6840(arg0, 11.0f);
        return;
    }
    if (!(temp_f0 <= 11.0f) && ((func_0019A5C8() % 3) == 0)) {
        func_001F6840(arg0, temp_f0 - 2.0f);
    }
}

INCLUDE_ASM("asm/nonmatchings/main_075", func_00261760);

typedef struct Command_00261B70 {
    s32 unk0;
    s32 mode;
    u32 mask;
    u32 value;
} Command_00261B70;

typedef struct State_00261B70 {
    u16 fade;
    u16 unk2;
    u16 phase;
    u8 handles[0xCE];
    u8 count;
    u8 padD5[0x2D];
    u16 timer;
} State_00261B70;

typedef struct Effect_00261B70 {
    s32 kind;
    s32 value1;
    s32 value2;
    s32 value3;
} Effect_00261B70;

void func_00255AC0(void *, s32);
void func_00260740(s32);
void func_00260A70(void *, s32);

s32 func_00261B70(void *arg0, void *arg1, s32 arg2) {
    Effect_00261B70 effect;
    s32 complete;
    Effect_00261B70 *command = &effect;
    Command_00261B70 *config = arg0;
    State_00261B70 *state = arg1;

    effect.kind = 999;
    effect.value1 = 0;
    effect.value2 = 0;
    effect.value3 = 0;
    complete = 0;
    func_001DE7E0(0);
    if (arg2 >= 0) {
        func_00255960(arg1);
        state->fade = 0x80;
        func_00260740(30);
        func_00255AC0(arg1, 6);
        func_00255AC0(arg1, 0x211);
    } else {
        switch (state->phase) {
    case 0:
        if (state->fade > 0x30) {
            state->fade -= 15;
        } else {
            state->fade = 0x30;
            if (func_00255B50(arg1) == 1) {
                command->kind = 6;
                command->value1 = 0;
                command->value2 = 0;
                command->value3 = 0;
                state->handles[state->count] = func_00255A30((s32 *)command, arg1);
                state->count++;
                state->phase++;
            }
        }
        if (state->fade < 0x30) {
            state->fade = 0x30;
        }
        func_001F6CF0((u8)state->fade);
        return 1;
    case 1:
        if (func_001F51D0(state->handles[0]) == 1) {
            return 1;
        }
        func_001E42C0(0, -120, 80, 0x106);
        func_0025F720(arg0, arg1, command, 0x211);
        state->phase++;
        return 1;
    case 2:
        {
            s32 i;

            for (i = 0; i < state->count; i++) {
                if (func_001F51D0(state->handles[i]) == 0) {
                    complete++;
                }
            }
            if (complete < state->count) {
                return 1;
            }
            func_001E4530();
            complete = 0;
            do {
                if ((config->mask >> (21 - complete)) & 1) {
                    if (complete < 11) {
                        func_00250E80(0, complete, config->value >> 16, config->value & 0xFFFF);
                        if (config->mode == 1) {
                            func_00250CA0(0, complete, config->value >> 16, config->value & 0xFFFF);
                        }
                    } else {
                        func_00250E80(1, complete - 11, config->value >> 16, config->value & 0xFFFF);
                        if (config->mode == 1) {
                            func_00250CA0(1, complete - 11, config->value >> 16, config->value & 0xFFFF);
                        }
                    }
                }
                complete++;
            } while (complete < 22);
            state->phase++;
            func_00260A70(arg1, 16);
            if (func_001DE780() != 0) {
                func_001DE7E0(1);
            }
        }
        break;
    default:
        state->fade += 15;
        if (state->fade > 0x80) {
            state->fade = 0x80;
        }
        func_001F6CF0((u8)state->fade);
        if (state->fade == 0x80) {
            if (state->timer++ >= 16 && func_0025FD90() == 1) {
                func_001E4530();
                return 0;
            }
        }
        break;
        }
    }
    return 1;
}

typedef struct Flags_00261F20 {
    u8 pad0:5;
    u8 field5:1;
    u8 field6:1;
    u8 pad7:1;
} Flags_00261F20;

typedef struct Result_00261F20 {
    u8 pad0[0xC];
    s32 value;
    Flags_00261F20 flags;
} Result_00261F20;


s32 func_00261F20(s32 arg0, s32 arg1, s32 arg2, s32 arg3, void *arg4) {
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_v0_2;
    s32 temp_v0_4;
    s32 var_fp;
    s32 var_s0;
    s32 var_s1;
    s32 var_s7;
    Result_00261F20 *temp_s2;
    void *temp_v0;
    void *temp_v0_3;

    temp_s2 = (Result_00261F20 *)arg4;
    var_s7 = 0;
    var_fp = 0;
    var_s1 = 0;
    var_s0 = 0;
    temp_s2->value = func_0024EA70(func_001E0830(arg0, arg1), func_001E0830(arg2, arg3));
    temp_v0 = func_00250740(arg0, arg1, 0);
    if (temp_v0 != NULL) {
        temp_v0_2 = func_00262190(*(s32 *)temp_v0, *(s32 *)((u8 *)temp_v0 + 4), temp_s2, arg0, arg1, arg2, arg3, 0);
        var_s0 = temp_v0_2;
        var_fp = 1;
        temp_s2->flags.field5 = ((temp_v0_2 >> 0x18) & 1);
    }
    temp_v0_3 = func_00250740(arg2, arg3, 0);
    if (temp_v0_3 != NULL) {
        temp_v0_4 = func_00262190(*(s32 *)temp_v0_3, *(s32 *)((u8 *)temp_v0_3 + 4), temp_s2, arg2, arg3, arg0, arg1, 1);
        var_s1 = temp_v0_4;
        var_s7 = 1;
        temp_s2->flags.field6 = ((temp_v0_4 >> 0x18) & 1);
    }
    if ((var_fp == 0) && (var_s7 == 0) && (temp_s2->value == 0)) {
        return 0;
    }
    temp_a0 = var_s0 & 0xFF;
    if ((temp_a0 == 1) && ((var_s1 & 0xFF) == 1)) {
        return 0x01010001;
    }
    if (temp_a0 == 1) {
        return 0x01000001;
    }
    if ((var_s1 & 0xFF) == 1) {
        return 0x10001;
    }
    temp_a0_2 = (var_s0 >> 0x10) & 1;
    if ((temp_a0_2 == 1) && (((var_s1 >> 0x10) & 1) == 1)) {
        return 0x01010000;
    }
    if (temp_a0_2 == 0) {
        if (((var_s1 >> 0x10) & 1) == 1) {
            return 0x10000;
        }
    }
    if (temp_a0_2 == 1) {
        if (((var_s1 >> 0x10) & 1) == 0) {
            return 0x01000000;
        }
    }
    return 0;
}

typedef struct Flags_00262190 {
    u8 bit0 : 1;
    u8 bit1 : 1;
    u8 bit2 : 1;
    u8 bit3 : 1;
    u8 bit4 : 1;
    u8 unused : 3;
} Flags_00262190;

typedef struct State_00262190 {
    Flags_00262190 flags;
    u8 pad1[3];
    s32 value0;
    s32 value1;
    u8 padC[4];
    Flags_00262190 flags10;
} State_00262190;

s32 func_00262190(u32 arg0, u32 arg1, void *arg2, s32 arg3, s32 arg4,
                  s32 arg5, s32 arg6, s32 arg7) {
    extern s32 func_001E2220();

    switch (arg0 >> 8) {
    case 4:
        if (func_00262680((arg0 >> 6) & 3, arg0 & 0x3F, arg3, arg4, arg5, arg6) == 1) {
            if (arg6 != 0 && arg4 != 0) {
                ((State_00262190 *)arg2)->flags.bit0 = 0;
                if (arg7 == 1) {
                    ((State_00262190 *)arg2)->flags.bit1 = 1;
                } else {
                    ((State_00262190 *)arg2)->flags.bit2 = 1;
                }
                return 0x10001;
            }
        }
        return 0;
    case 2: {
        s32 row;
        s32 y;
        s32 x;
        s32 col;
        u32 range;
        u32 value;

        if (arg7 == 0) {
            y = func_001E1090(arg3, arg4) & 0xFF;
            x = func_001E1090(arg3, arg4) >> 8;
        } else {
            y = func_001E1090(arg5, arg6) & 0xFF;
            x = func_001E1090(arg5, arg6) >> 8;
        }
        row = 0;
        range = arg1 >> 16;
        value = arg1 & 0xFFFF;
        do {
            col = 0;
            do {
                if ((u32)(((row < y ? y : row) - (y < row ? y : row)) +
                          ((col < x ? x : col) - (x < col ? x : col))) <= range &&
                    func_001E22B0(row, col) != 8) {
                    func_001E2220(row, col, value);
                }
                col++;
            } while (col < 7);
            row++;
        } while (row < 7);
        return 0x10000;
    }
    case 27:
        if (func_00262680(2, arg1 >> 16, arg3, arg4, arg5, arg6) == 1) {
            if (arg6 != 0 && arg4 != 0) {
                if (arg7 == 0) {
                    ((State_00262190 *)arg2)->value0 += arg1 & 0xFFFF;
                } else {
                    ((State_00262190 *)arg2)->value1 += arg1 & 0xFFFF;
                }
                return 0x10000;
            }
        }
        return 0;
    case 5:
        if (arg6 != 0) {
            if (arg4 != 0) {
                if (arg7 == 0) {
                    ((State_00262190 *)arg2)->flags10.bit0 = 1;
                } else {
                    ((State_00262190 *)arg2)->flags10.bit1 = 1;
                }
                return 0x10000;
            }
        }
        break;
    case 13: {
        s32 value = arg1 & 0xFFFF;
        arg1 >>= 16;
        switch (arg1) {
        case 0:
            value = func_002670F0(0x2B, value);
            break;
        case 1:
            value = func_002670F0(0x2C, value);
            break;
        }
        func_001DF490(arg3, arg1, value);
        return 0x10000;
    }
    case 0x3A:
        if (arg6 != 0 && arg4 != 0) {
            ((State_00262190 *)arg2)->flags10.bit2 = 1;
            return 0x10000;
        }
        break;
    case 1:
        if (arg6 != 0 && arg4 != 0) {
            if (arg7 == 0) {
                ((State_00262190 *)arg2)->flags10.bit4 = 1;
            } else {
                ((State_00262190 *)arg2)->flags10.bit3 = 1;
            }
            return 0x10000;
        }
        break;
    case 0x3F:
        if (arg7 == 0) {
            u32 first;
            u32 divisor;
            divisor = ((arg1 & 0xFFFF) / 100) + 1;
            first = (u32)func_0019A5C8() % divisor;
            ((State_00262190 *)arg2)->value0 = (first - (u32)func_0019A5C8() % divisor) * 100;
        } else {
            u32 first;
            u32 divisor;
            divisor = ((arg1 & 0xFFFF) / 100) + 1;
            first = (u32)func_0019A5C8() % divisor;
            ((State_00262190 *)arg2)->value1 = (first - (u32)func_0019A5C8() % divisor) * 100;
        }
        return 0x10000;
    default:
        return 0;
    }
    return 0;
}

s32 func_00262680(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    switch (arg0) {
    case 1:
        return func_002626F0(arg1, arg2, arg3);
    case 2:
        return func_002626F0(arg1, arg4, arg5);
    default:
        return 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_075", func_002626F0);

typedef struct {
    s32 kind;
    u32 source;
    u32 target;
    s32 value;
} Command_00262BE0;

typedef struct {
    u16 sourceActive;
    u16 targetActive;
    u16 stage;
    u8 effect;
    u8 pad07[0x19];
    s32 applied;
    u8 pad24[0xAC];
    s32 timer;
} State_00262BE0;

void func_0024F370(s32, s32);
void func_00255AC0(void *, s32);

s32 func_00262BE0(void *arg0, void *arg1, s32 arg2) {
    extern s32 func_001E1D10();
    extern s32 func_001E1A90();
    extern s32 func_001E1030();
    extern s32 func_001E1840();
    extern s32 func_001E1970();
    s32 scratch[4];
    s32 *command = scratch;
    State_00262BE0 *state = arg1;
    Command_00262BE0 *input = arg0;
    s32 status;

    command[0] = 999;
    command[1] = 0;
    command[2] = 0;
    command[3] = 0;

    if (arg2 >= 0) {
        func_00255960(state);
        if (func_001E1D10(input->source >> 8, input->source & 0xFF) > 0) {
            func_002500C0(input->source >> 8, input->source & 0xFF, -1, 1, 1);
            state->sourceActive = 1;
        }
        if (func_001E1D10(input->target >> 8, input->target & 0xFF) > 0) {
            func_002500C0(input->target >> 8, input->target & 0xFF, -1, 1, 1);
            state->targetActive = 1;
        }
        if (input->value == 999) {
            func_00255AC0(state, 0x21A);
        } else if (input->kind == 0x2B) {
            func_00255AC0(state, 0x21F);
        } else {
            func_00255AC0(state, 0x258);
        }
        return 1;
    }

    switch (state->stage) {
        case 0:
        if (func_00255B50(state) != 1) {
            return 1;
        }
        if (state->sourceActive != 0) {
            status = func_001E1D10(input->source >> 8, input->source & 0xFF);
            if (status != func_001E1A90(input->source >> 8, input->source & 0xFF)) {
                return 1;
            }
        }
        if (state->targetActive != 0) {
            status = func_001E1D10(input->target >> 8, input->target & 0xFF);
            if (status != func_001E1A90(input->target >> 8, input->target & 0xFF)) {
                return 1;
            }
        }
        if (input->value == 999) {
            command[0] = 0x21A;
            command[1] = input->source;
            command[2] = input->target;
            command[3] = 1;
        } else if (input->kind == 0x2B) {
            command[0] = 0x21F;
            command[1] = input->source;
            command[2] = input->target;
            command[3] = 1;
        } else {
            command[0] = 0x258;
            command[1] = input->source;
            command[2] = input->target;
            command[3] = 1;
        }
        state->effect = func_00255A30(command, state);
        state->applied = 0;
        state->stage++;
        return 1;
        default:
        if (input->value == 999) {
            if (func_001F51D0(state->effect) != 0) {
                switch (state->timer++) {
                    case 0:
                        func_00217710(1, 0x38);
                        break;
                    case 20:
                        func_00217710(1, 0x39);
                        break;
                    case 30:
                        func_00217710(1, 0x4C);
                        break;
                    case 36:
                        func_00217710(1, 0x4A);
                        break;
                    case 48:
                        func_00217710(1, 0x3C);
                        break;
                }
                return 1;
            }
            func_0024F370(input->source >> 8, input->source & 0xFF);
            if (state->targetActive != 0) {
                func_002500C0(input->target >> 8, input->target & 0xFF, 1, 1, 1);
            }
            func_001E4530();
            return 0;
        }

        if (func_001F51D0(state->effect) != 0) {
            switch (state->timer++) {
                case 0:
                    func_00217710(1, 0x38);
                    break;
                case 20:
                    func_00217710(1, 0x39);
                    break;
                case 30:
                    func_00217710(1, 0x4C);
                    break;
                case 40:
                    func_00217710(1, 0x3A);
                    break;
                case 100:
                    func_00217710(1, 0x3B);
                    break;
                case 120:
                    func_00217710(1, 0x3C);
                    break;
            }
            if (func_001F52D0(state->effect) != 2) {
                return 1;
            }
            if (state->applied == 0) {
                func_001DEE70(input->target >> 8,
                             func_001E1030(input->target >> 8, input->target & 0xFF));
                func_001DFAF0(input->target >> 8, input->target & 0xFF, input->value);
                func_0024F370(input->source >> 8, input->source & 0xFF);
                func_001E1840(input->target >> 8, input->target & 0xFF, 1);
                func_001E1970(input->target >> 8, input->target & 0xFF, 0);
                func_001E1B70(input->target >> 8, input->target & 0xFF, -1, 0);
                state->applied = 1;
            }
            return 1;
        }

        func_001E1840(input->target >> 8, input->target & 0xFF, 1);
        func_001E1970(input->target >> 8, input->target & 0xFF, 0x80);
        func_001E1B70(input->target >> 8, input->target & 0xFF, 1, 0x80);
        func_00217710(0, 2);
        func_001E4530();
        return 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_075", func_00263180);

typedef struct {
    u8 pad0[8];
    s32 mask;
    s32 owner;
} Context_00263500;

typedef struct {
    u8 pad0[4];
    u16 state;
    u8 ids[0x1A];
    u8 pad20[0xB4];
    u8 count;
    u8 padD5[0x2D];
    u16 timer;
} State_00263500;

void func_0024F370(s32, s32);
void func_00255AC0(void *, s32);
void func_00260740(s32);
void func_00260A70(void *, s32);

s32 func_00263500(void *arg0, void *arg1, s32 arg2) {
    s32 data[4];
    s32 *data_ptr = data;
    s32 i;
    s32 inactive;
    Context_00263500 *context = arg0;
    State_00263500 *state = arg1;

    data[0] = 999;
    data[1] = 0;
    data[2] = 0;
    data[3] = 0;
    inactive = 0;
    func_001DE7E0(0);
    if (arg2 >= 0) {
        func_00255960(arg1);
        func_00255AC0(arg1, 0x230);
        if (func_0024E910(context->mask) == 1) {
            func_00260AF0(0x1E, func_0024EC50(context->mask, 0), 0x64, 0xB4);
        } else {
            func_00260740(0x1E);
        }
        return 1;
    }

    switch (state->state) {
    case 0:
        if (func_00255B50(arg1) == 1) {
            if (state->timer++ >= 0x1E) {
                func_0025F720(arg0, arg1, data_ptr, 0x230);
                state->state++;
            }
        }
        break;
    case 1: {
        u8 *entry;
        s32 target;
        s32 location;

        for (i = 0, entry = arg1; i < state->count; entry += 4, i++) {
            if (func_001F51D0(state->ids[i]) == 1) {
                if (func_001F52D0(state->ids[i]) == 2) {
                    target = *(s32 *)(entry + 0x20);
                    if ((target & 0xFFFF) != 0xFFFF) {
                        location = func_001E1090(target >> 8, target & 0xFF);
                        target = *(s32 *)(entry + 0x20);
                        func_0024F370(target >> 8, target & 0xFF);
                        func_001DF580(*(s32 *)(entry + 0x20) >> 8,
                                     location & 0xFF, location >> 8, context->owner, 0);
                        *(s32 *)(entry + 0x20) = 0xFFFF;
                    }
                }
            } else {
                inactive++;
            }
        }
        if (inactive < state->count) {
            return 1;
        } else {
            state->state++;
            state->timer = 0;
            func_00260A70(arg1, 0x10);
        }
        break;
    }
    default:
        if (state->timer++ > 0x10) {
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

void func_00255AC0(void *, s32);

typedef struct Config_00263790 {
    u8 padding[8];
    u32 id;
    s32 duration;
} Config_00263790;

typedef struct State_00263790 {
    u32 unknown;
    u16 phase;
    u8 handle;
} State_00263790;

s32 func_00263790(void *arg0, void *arg1, s32 arg2) {
    s32 request[4];
    s32 *p = request;
    State_00263790 *state = arg1;
    Config_00263790 *config = arg0;

    request[0] = 0x3E7;
    request[1] = 0;
    request[2] = 0;
    request[3] = 0;
    func_001DE7E0(0);
    if (arg2 >= 0) {
        func_00255960(arg1);
        func_00255AC0(arg1, 0x216);
        return 1;
    }
    switch (state->phase) {
    case 0:
        if (func_00255B50(arg1) != 1) {
            break;
        }
        if (func_001DE5C0(config->id) <= (u32)config->duration) {
            p[0] = 0x216;
            p[1] = 0;
            p[2] = 0;
            p[3] = config->duration - func_001DE5C0(config->id);
        } else {
            p[0] = 0x216;
            p[1] = 0;
            p[2] = 1;
            p[3] = func_001DE5C0(config->id) - config->duration;
        }
        state->handle = func_00255A30(p, arg1);
        state->phase++;
        break;
    default:
        if (func_001F51D0(state->handle) == 1) {
            return 1;
        }
        func_001DE5E0(config->id, 4, config->duration);
        if (func_001DE780() != 0) {
            func_001DE7E0(1);
        }
        func_001E4530();
        return 0;
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_075", func_00263930);

typedef struct State_00265050 {
    u32 unk0;
    u16 state;
    u8 handle;
    u8 handle2;
    u8 pad8[0xFA];
    u16 timer;
} State_00265050;

typedef struct Request_00265050 {
    s32 id;
    s32 unk4;
    u32 position;
    s32 flag;
} Request_00265050;

void func_001E1E70(u32, s32, s32, s32);
void func_0024F370(s32, s32);
void func_002516D0(u32, s32, s32);
void func_00255AC0(void *, s32);
void func_00260A70(void *, s32);

s32 func_00265050(void *arg0, void *arg1, s32 arg2) {
    Request_00265050 packet;
    Request_00265050 *request = &packet;
    State_00265050 *state = arg1;
    u32 *data = arg0;
    extern s32 func_001E1E10();
    extern s32 func_001E1CB0();

    packet.id = 999;
    packet.unk4 = 0;
    packet.position = 0;
    packet.flag = 0;
    func_001DE7E0(0);
    if (arg2 >= 0) {
        func_00255960(arg1);
        func_002516D0(data[1] >> 8, data[1] & 0xFF, 1);
        func_002516D0(data[2] >> 8, data[2] & 0xFF, 1);
        func_00260AF0(0, data[1], 100, 180);
        func_00255AC0(arg1, 0x221);
        func_00255AC0(arg1, 0x259);
        func_00255AC0(arg1, 0x25A);
        func_00255AC0(arg1, 0x25B);
        return 1;
    }
    switch (state->state) {
    case 0:
        if (func_001E1E10(data[1] >> 8, data[1] & 0xFF) < 255 ||
            func_001E1E10(data[2] >> 8, data[2] & 0xFF) < 255 ||
            func_001E1CB0(data[2] >> 8, data[2] & 0xFF) < 128) {
            return 1;
        }
        if ((func_001E0700(data[2] >> 8, data[2] & 0xFF) >> 5) == 0 &&
            func_001F5EC0(data[2]) == 0) {
            return 1;
        }
        if (func_00255B50(arg1) == 1) {
            state->state++;
        }
        return 1;
    case 1:
        func_001E42C0(0, -120, 80, 0x103);
        request->id = 0x25A;
        request->unk4 = 0;
        request->position = data[1];
        request->flag = 0;
        state->handle = func_00255A30(request, arg1);
        state->state++;
        return 1;
    case 2:
        if (func_001F51D0(state->handle) == 0) {
            func_001E1E70(data[1] >> 8, data[1] & 0xFF, 0, 1);
            request->id = 0x259;
            request->unk4 = 0;
            request->position = data[1];
            request->flag = 1;
            state->handle = func_00255A30(request, arg1);
            state->state++;
        }
        return 1;
    case 3:
        if (func_001F51D0(state->handle) == 0) {
            func_00260AF0(16, data[2], 100, 180);
            func_0024F370(data[1] >> 8, data[1] & 0xFF);
            request->id = 0x25B;
            request->unk4 = 0;
            request->position = data[2];
            request->flag = 0;
            state->handle = func_00255A30(request, arg1);
            request->id = 0x221;
            request->unk4 = 0;
            request->position = data[2];
            request->flag = 0;
            state->handle2 = func_00255A30(request, arg1);
            state->state++;
        }
        return 1;
    case 4:
        if (func_001F51D0(state->handle) != 0 ||
            func_001F51D0(state->handle2) != 0) {
            return 1;
        }
        func_0024F370(data[2] >> 8, data[2] & 0xFF);
        func_001E4530();
        func_00260A70(arg1, 16);
        state->state++;
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

INCLUDE_ASM("asm/nonmatchings/main_075", func_00265440);

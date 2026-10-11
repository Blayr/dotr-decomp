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

INCLUDE_ASM("asm/nonmatchings/main_075", func_0025F400);

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

s32 func_00255A30(void *, void *);

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

s32 func_00255A30(void *, void *);

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

INCLUDE_ASM("asm/nonmatchings/main_075", func_0025F990);

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

INCLUDE_ASM("asm/nonmatchings/main_075", func_0025FF30);

INCLUDE_ASM("asm/nonmatchings/main_075", func_00260020);

void func_001E42C0(s32, s32, s32, s32);
void func_00255960(void *);
s32 func_00255A30(void *, void *);
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
void func_00255960(void *);
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

INCLUDE_ASM("asm/nonmatchings/main_075", func_00260490);

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

INCLUDE_ASM("asm/nonmatchings/main_075", func_00261B70);

INCLUDE_ASM("asm/nonmatchings/main_075", func_00261F20);

INCLUDE_ASM("asm/nonmatchings/main_075", func_00262190);

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

INCLUDE_ASM("asm/nonmatchings/main_075", func_00262BE0);

INCLUDE_ASM("asm/nonmatchings/main_075", func_00263180);

INCLUDE_ASM("asm/nonmatchings/main_075", func_00263500);

INCLUDE_ASM("asm/nonmatchings/main_075", func_00263790);

INCLUDE_ASM("asm/nonmatchings/main_075", func_00263930);

INCLUDE_ASM("asm/nonmatchings/main_075", func_00265050);

INCLUDE_ASM("asm/nonmatchings/main_075", func_00265440);

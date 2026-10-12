#include "common.h"

s32 func_00162580(s32 arg0) {
    if (func_001DF470(arg0) > 0x4B0) {
        if (func_001E0150(arg0) >= 4) {
            return 0x1F4;
        }
        return 0x3E8;
    }
    return 0x7D0;
}

s32 func_001625E0(s32 arg0) {
    u16 sp40[22];
    s32 temp_s0;
    s32 temp_s2;
    s32 temp_v0;
    s32 var_a0;
    s32 var_a0_2;
    u16 *var_a1;
    u16 *var_s0;

    var_s0 = sp40;
    var_a0 = 0;
    var_a1 = var_s0;
    do {
        var_a0 += 1;
        *var_a1 = 0xFFFF;
        var_a1++;
    } while (var_a0 < 0x16);
    func_0027C2C0((arg0 == 0) ? 1 : 0, sp40, 0x1D, 0, 0);
    temp_s2 = func_0027B650(sp40);
    var_a0_2 = 0;
    do {
        var_a0_2 += 1;
        *var_s0 = 0xFFFF;
        var_s0++;
    } while (var_a0_2 < 0x16);
    func_0027C070(arg0, sp40, 0x1D, 1);
    temp_s0 = func_0027B650(sp40);
    if (temp_s2 >= 0) {
        if (temp_s0 >= 0) {
            temp_v0 = func_001E1090(temp_s2 >> 8, temp_s2 & 0xFF);
            if (func_002781F0(temp_s0, temp_s2, temp_v0 & 0xFF, temp_v0 >> 8) < 0) {
                return temp_s2;
            }
        }
    }
    return -1;
}

s32 func_001626F0(s32 arg0) {
    s32 i;
    u8 count;
    s32 handle;
    s32 card;

    count = 0;
    if (func_0027BBC0(arg0, 0, 0) == 1) {
        return 1;
    }
    handle = func_0024CA40(0, 0, arg0, 2, 0x34, 0xE);
    for (i = 0; i < func_0024E910(handle); i++) {
        card = func_0024EC50(handle, i);
        if (func_001E2100(card >> 8, card & 0xFF, 4) == 0) {
            count++;
        }
    }
    return count < 5 ? 0 : 1;
}

s32 func_001627D0(s32 arg0) {
    extern s32 func_001DEE50(s32);
    s32 i;

    if (func_001E0150(arg0) >= 5) {
        return -1;
    }
    if (func_0027DD20(arg0, 3, 0x3C) > 0 || func_0027DD20(arg0, 3, 0x57) > 0 ||
        func_0027DD20(arg0, 3, 0x2B) > 0) {
        for (i = 0; i < func_001DEE50(arg0); i++) {
            if (func_001DEE00(arg0, i) == 0x57) {
                return (arg0 << 16) | i;
            }
        }
        for (i = 0; i < func_001DEE50(arg0 == 0 ? 1 : 0); i++) {
            if (func_001DEE00(arg0 == 0 ? 1 : 0, i) == 0x57) {
                return ((arg0 == 0 ? 1 : 0) << 16) | i;
            }
        }
        for (i = 0; i < func_001DEE50(arg0); i++) {
            if (func_001DEE00(arg0, i) == 0x2B) {
                return (arg0 << 16) | i;
            }
        }
        for (i = 0; i < func_001DEE50(arg0 == 0 ? 1 : 0); i++) {
            if (func_001DEE00(arg0 == 0 ? 1 : 0, i) == 0x2B) {
                return ((arg0 == 0 ? 1 : 0) << 16) | i;
            }
        }
        for (i = 0; i < func_001DEE50(arg0); i++) {
            if (func_001DEE00(arg0, i) == 0x3C) {
                return (arg0 << 16) | i;
            }
        }
        for (i = 0; i < func_001DEE50(arg0 == 0 ? 1 : 0); i++) {
            if (func_001DEE00(arg0 == 0 ? 1 : 0, i) == 0x3C) {
                return ((arg0 == 0 ? 1 : 0) << 16) | i;
            }
        }
    }
    return -1;
}

s32 func_00162A70(s32 arg0) {
    extern s32 func_001DEE50(s32);
    s32 i;

    if (func_001E01F0(arg0) >= 5) {
        return -1;
    }
    if (func_0027DD20(arg0, 3, 0x2BC) > 0 || func_0027DD20(arg0, 3, 0x2CB) > 0 ||
        func_0027DD20(arg0, 3, 0x33B) > 0) {
        for (i = 0; i < func_001DEE50(arg0); i++) {
            if (func_001DEE00(arg0, i) == 0x33B) {
                return (arg0 << 16) | i;
            }
        }
        for (i = 0; i < func_001DEE50(arg0 == 0 ? 1 : 0); i++) {
            if (func_001DEE00(arg0 == 0 ? 1 : 0, i) == 0x33B) {
                return ((arg0 == 0 ? 1 : 0) << 16) | i;
            }
        }
        for (i = 0; i < func_001DEE50(arg0); i++) {
            if (func_001DEE00(arg0, i) == 0x2BC) {
                return (arg0 << 16) | i;
            }
        }
        for (i = 0; i < func_001DEE50(arg0 == 0 ? 1 : 0); i++) {
            if (func_001DEE00(arg0 == 0 ? 1 : 0, i) == 0x2BC) {
                return ((arg0 == 0 ? 1 : 0) << 16) | i;
            }
        }
        for (i = 0; i < func_001DEE50(arg0); i++) {
            if (func_001DEE00(arg0, i) == 0x2CB) {
                return (arg0 << 16) | i;
            }
        }
        for (i = 0; i < func_001DEE50(arg0 == 0 ? 1 : 0); i++) {
            if (func_001DEE00(arg0 == 0 ? 1 : 0, i) == 0x2CB) {
                return ((arg0 == 0 ? 1 : 0) << 16) | i;
            }
        }
    }
    return -1;
}

#define MAX_00162D10(a, b) ((a) > (b) ? (a) : (b))
#define MIN_00162D10(a, b) ((a) < (b) ? (a) : (b))

s32 func_00162D10(s32 arg0) {
    extern s32 func_001E1580(s32, s32);
    extern s32 func_001E1640(s32, s32);
    s32 pos;
    s32 x0;
    s32 y0;
    u16 *p;
    s32 x;
    s32 y;
    s32 bestPos;
    s32 i;
    s32 best;
    u32 obj;
    s32 score;
    s32 cur;
    s32 found;
    u16 list[22];

    pos = func_001E1090(arg0 == 0 ? 1 : 0, 0);
    if (func_00266DF0(0x39) > 0) {
        return -1;
    }
    obj = func_00272210(func_0024CA40(0, 0, arg0, 2, 0x21, 0xE), arg0);
    p = list;
    for (i = 0; i < 22; i++) {
        p[i] = 0xFFFF;
    }
    func_0027C070(arg0 == 0 ? 1 : 0, list, 0x34, 0);
    found = -1;
    bestPos = found;
    best = 1;
    i = 0;
    if (i < func_0027C670(list)) {
        x0 = pos >> 8;
        y0 = pos & 0xFF;
        do {
            cur = func_001E1090(*p >> 8, *p & 0xFF);
            x = cur >> 8;
            y = cur & 0xFF;
            if (MAX_00162D10(y0, y) - MIN_00162D10(y0, y) + (MAX_00162D10(x0, x) - MIN_00162D10(x0, x)) == 1) {
                if (func_001E2100(*p >> 8, *p & 0xFF, 1) == 0 &&
                    func_001E1580(*p >> 8, *p & 0xFF) == 0 &&
                    func_001E1640(*p >> 8, *p & 0xFF) == 0) {
                    if ((score = func_002509E0(*p >> 8, *p & 0xFF, y, x)) >= best) {
                        bestPos = *p;
                        if (bestPos == func_0024EC50(obj, 0)) {
                            found = bestPos;
                        }
                        best = score;
                    }
                }
            }
            p++;
            i++;
        } while (i < func_0027C670(list));
    }
    if (bestPos < 0) {
        return -1;
    }
    return ((u16)bestPos << 16) | (u16)found;
}

typedef struct {
    u16 unk0;
    u8 unk2;
    u8 pad3;
    u16 unk4;
    u8 unk6[5];
    u8 padB;
    s32 unkC;
    u8 unk10;
} Req_00162F60;

typedef struct {
    u8 pad0[0x160];
    u16 list[32];    /* 0x160 */
    u8 idx : 5;      /* 0x1A0 */
    u8 pad1A0 : 3;
    u8 pad1A1;
    u16 count;       /* 0x1A2 */
} Work_00162F60;

s32 func_0015D350(void *, void *, s32);
s32 func_00276290(void *, void *, s32);

s32 func_00162F60(s32 arg0, void *arg1) {
    Req_00162F60 req;
    Work_00162F60 *w;
    s32 i;
    s32 ret;

    w = arg1;
    req.unk0 = 0xFFFF;
    req.unk2 = 0xFF;
    req.unk4 = 0xFFFF;
    req.unkC = 0;
    req.unk10 = 0xFF;
    if (w == NULL) {
        return 0x800;
    }
    for (i = 0; i < 5; i++) {
        req.unk6[i] = 0xFF;
    }
    w->count++;
    if (w->count == 600) {
        return 0x20;
    }
    if (w->count == 601) {
        return 0x20;
    }
    if (w->count == 602) {
        return 0x20;
    }
    if (!(w->count < 603)) {
        return 0x800;
    }
    if (w->idx == 0) {
        func_00275E80(w);
        if (func_0015D350(w, &req, arg0) == 0) {
            return 0x800;
        }
        if (func_00276290(w, &req, arg0) < 0) {
            return 0;
        }
    }
    ret = w->list[w->idx - 1];
    if (ret == 0xFFFF) {
        return 0;
    }
    if (w->list[w->idx] == 0xFFFF) {
        w->idx = 0;
        for (i = 0; i < 32; i++) {
            w->list[i] = 0xFFFF;
        }
    } else {
        w->idx++;
    }
    return (u16)ret;
}

INCLUDE_ASM("asm/nonmatchings/main_015", func_00163130);

INCLUDE_ASM("asm/nonmatchings/main_015", func_00163660);

s32 func_00163870(u16 *arg0, s32 arg1, s32 arg2) {
    s32 i;
    s32 pos;
    s32 ret;
    s32 idx;
    u16 list[22];

    for (i = 0; i < 22; i++) {
        list[i] = 0xFFFF;
    }
    func_0027C070(arg1, list, 0x1D, 1);
    ret = func_0027B360(arg1, list, arg0);
    if (ret >= 0) {
        return ret;
    }
    for (i = 0; i < 22; i++) {
        list[i] = 0xFFFF;
    }
    func_0027C070(arg1, list, 0x1E, 1);
    for (i = 0; i < func_0027C670(list); i++) {
        if ((func_001E0700(list[i] >> 8, list[i] & 0xFF) >> 5) == 3 &&
            func_0027B9B0(list[i]) == 1 && func_0027C6D0(list[i]) == 1) {
            return list[i];
        }
    }
    pos = arg1 << 8;
    idx = func_00276C80(arg0, pos);
    func_00163660(arg0 + idx * 8);
    if (((arg0[idx * 8 + 2] >> 8) & 0xFF) == 10) {
        if (func_001DE6D0(arg1) == 1 && func_001643F0(pos, arg1, arg2) >= 0) {
            return pos | 0x10000;
        }
        if (func_0027B9B0(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (func_001E2100(arg1, 0, 0) == 0) {
        if (func_0027B9B0(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (func_001DE6D0(arg1) == 1 && func_001643F0(pos, arg1, arg2) >= 0) {
        return pos | 0x10000;
    }
    for (i = 0; i < 22; i++) {
        list[i] = 0xFFFF;
    }
    func_0027C070(arg1, list, 0x1F, 1);
    for (i = 0; i < func_0027C670(list); i++) {
        if (func_0027B9B0(list[i]) == 1 && func_0027C6D0(list[i]) == 1) {
            return list[i];
        }
    }
    for (i = 0; i < 22; i++) {
        list[i] = 0xFFFF;
    }
    func_0027C070(arg1, list, 0x1F, 1);
    for (i = 0; i < func_0027C670(list); i++) {
        if (func_001E2100(list[i] >> 8, list[i] & 0xFF, 0) == 0 && func_0027C6D0(list[i]) == 1) {
            return list[i];
        }
    }
    return -1;
}

typedef struct {
    u16 coordinates;
    u16 unk02;
    s16 state;
    u16 unk06;
    union {
        u32 word;
        struct {
            u16 low;
            u16 high;
        } halves;
    } data;
} Entry_00163C50;

typedef struct {
    u16 card;
    u8 flag;
    u8 pad;
} Slot_00163C50;

void func_00163C50(void *arg0, s32 arg1) {
    extern void func_0027E770();
    extern s32 func_0027B200();
    extern s32 func_00163EC0();
    extern s32 func_001676D0(s32);
    extern void func_00163F20(void *);
    Entry_00163C50 *entry = arg0;
    s32 side;
    s32 player;
    s32 other;
    s32 pos;
    s32 otherPos;
    s32 i;
    u8 work[0x70];
    Slot_00163C50 list[22];
    s16 countA;
    s16 countB;

    if (func_001DF540(entry->coordinates >> 8, entry->coordinates & 0xFF) != 0) {
        side = func_0024DE70(entry->coordinates >> 8, entry->coordinates & 0xFF);
        other = (side == 0 ? 1 : 0) << 8;
        pos = func_001E1090(entry->coordinates >> 8, entry->coordinates & 0xFF);
        otherPos = func_001E1090(other >> 8, other & 0xFF);
        player = func_001DF540(entry->coordinates >> 8, entry->coordinates & 0xFF);
        func_0027E770(work);
        for (i = 0; i < 22; i++) {
            list[i].card = 0xFFFF;
            list[i].flag = 0xFF;
        }
        if (arg1 != 0) {
            if (func_0027B200(entry->coordinates >> 8, entry->coordinates & 0xFF, pos & 0xFF, pos >> 8,
                              other >> 8, other & 0xFF, otherPos & 0xFF, otherPos >> 8, 5) > 0) {
                entry->state = 0x2FF;
                entry->data.word = (other << 16) | entry->data.halves.low;
                return;
            }
        }
        countB = 0;
        countA = 0;
        i = 1;
        while (1) {
            switch (func_00163EC0(entry, 0, player, pos & 0xFF, pos >> 8,
                                  func_0024DE70(entry->coordinates >> 8, entry->coordinates & 0xFF) == 0 ? 1 : 0,
                                  i & 0xFF, func_001676D0(side), list, 0, &countA, &countB, 5, work)) {
            case 3:
                entry->state = 0x6FF;
                entry->data.word = (pos << 16) | entry->data.halves.low;
                return;
            case 2:
                entry->state = 0x3FF;
                entry->data.word = (pos << 16) | entry->data.halves.low;
                return;
            case 1:
                return;
            case 0:
                entry->state = 0x5FF;
                return;
            }
            i++;
            if (i > 5) {
                break;
            }
        }
        func_00163F20(entry);
    }
}

void func_00163EC0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28) {
    func_0027DE20(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
                 arg_sp0, arg_sp8, arg_sp10, arg_sp18, arg_sp20,
                 1, 3000, arg_sp28);
}


typedef struct {
    u16 location;
    u16 padding2;
    s16 field4;
    u16 padding6;
    union {
        u16 low;
        u32 word;
    } field8;
} State_00163F20;

void func_00163F20(void *arg0) {
    State_00163F20 *state = arg0;
    s32 temp_v0_3;
    u16 temp_v0;
    u16 temp_v0_2;

    temp_v0 = state->location;
    func_00250360((s32) temp_v0 >> 8, temp_v0 & 0xFF);
    temp_v0_2 = state->location;
    temp_v0_3 = func_001E1090((s32) temp_v0_2 >> 8, temp_v0_2 & 0xFF);
    state->field4 = 0x6FF;
    state->field8.word = state->field8.low |
        (func_00163F90(temp_v0_3 & 0xFF, temp_v0_3 >> 8) << 16);
}

s32 func_00163F90(s32 arg0, s32 arg1) {
    if (arg1 == 0) {
        if (arg0 >= 3) {
            return 0x106;
        }
        if (arg0 < 3) {
            return 0x100;
        }
    }
    if (arg1 < 6) {
        if (arg0 >= 3) {
            return 0x605;
        }
        if (arg0 < 3) {
            return 0x601;
        }
    }
    if (arg0 >= 3) {
        return 0x601;
    }
    return 0x605;
}

INCLUDE_ASM("asm/nonmatchings/main_015", func_00164020);

INCLUDE_ASM("asm/nonmatchings/main_015", func_00164260);

s32 func_00164360(s32 arg0) {
    s32 temp_v1;

    temp_v1 = arg0 & 0xFF;
    switch (temp_v1) {
    case 0:
        return 0x203;
    case 1:
        return 0x301;
    case 2:
        return 0x305;
    case 3:
        return 0x202;
    case 4:
        return 0x204;
    default:
        return 0x203;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_015", func_001643F0);

s32 func_00164680(s32 arg0, void *arg1) {
    extern s32 func_00278890();
    s32 ids[8];
    s32 data[8];
    u8 type = (u8)func_00278890(arg0, 0);
    u8 attr = (u8)func_00278890(arg0, 1);

    if (arg1 == NULL) {
        return -1;
    }
    func_0026FD30(arg0, ids);
    if (type == 5) {
        s32 result = func_00164AE0(arg0, (u8 *)data, arg1, 0x3E7);
        if (result >= 0) {
            result = 1;
        } else {
            result = -1;
        }
        return result;
    }
    if (attr == 5) {
        s32 i;
        s32 *p;
        s32 count;

        i = 0;
        count = func_0026FE20(arg0);
        if (i < count) {
            p = ids;
            do {
                if ((func_0026FCE0(*p) >> 5) == 0 && func_0026FB10(arg0, *p) == 1) {
                    func_001DCD70(arg1, ids[i]);
                    return 0;
                }
                p++;
                i++;
                count = func_0026FE20(arg0);
            } while (i < count);
        }
        return -1;
    }
    if (func_00164910(arg0, (u8 *)data, arg1, 0x34A) >= 0) {
        if (func_00167670(arg0, 0x34A) == 1) {
            return 2;
        }
    }
    if (func_00164910(arg0, (u8 *)data, arg1, 0x352) >= 0) {
        if (func_00167670(arg0, 0x352) == 1) {
            return 2;
        }
    }
    if (func_00164A00(arg0, (u8 *)data, arg1) >= 0) {
        return 2;
    }
    {
        s32 *p;
        s32 i;
        s32 count;

        i = 0;
        count = func_0026FE20(arg0);
        if (i < count) {
            p = ids;
            do {
                if ((func_0026FCE0(*p) >> 5) == 0 && func_0026FB10(arg0, *p) == 1) {
                    func_001DCD70(arg1, ids[i]);
                    return 0;
                }
                p++;
                i++;
                count = func_0026FE20(arg0);
            } while (i < count);
        }
    }
    {
        s32 result = func_00164AE0(arg0, (u8 *)data, arg1, 0x3E7);
        if (result >= 0) {
            return result;
        }
        return -1;
    }
}

s32 func_00164910(s32 arg0, void *arg1, void *arg2, s32 arg3) {
    s32 i;
    s32 ids[8];

    func_0026FD30(arg0, ids);
    for (i = 0; i < func_0026FE20(arg0); i++) {
        if ((arg3 & 0xFFFF) == ids[i] && func_0026FB10(arg0, ids[i]) == 1) {
            *((s8 *)arg1 + 6) = i;
            func_001DCD70(arg2, ids[i]);
            return func_0026FCE0(ids[i]) >> 5;
        }
    }
    return -1;
}

s32 func_00164A00(s32 arg0, void *arg1, void *arg2) {
    s32 values[8];
    s32 index;
    s32 *p;

    func_0026FD30(arg0, values);
    index = 0;
    if (index < func_0026FE20(arg0)) {
        p = values;
        do {
            if (func_001DE020(func_0026FCE0(*p) >> 5) == 2) {
                *((s8 *)arg1 + 6) = index;
                func_001DCD70(arg2, values[index]);
                return func_0026FCE0(values[index]) >> 5;
            }
            p++;
            index++;
        } while (index < func_0026FE20(arg0));
    }
    return -1;
}

s32 func_00164AE0(s32 arg0, u8 *arg1, void *arg2, s32 arg3) {
    s32 buf[8];
    s32 i;

    func_0026FD30(arg0, buf);
    if (arg2 == NULL) {
        return -1;
    }
    for (i = 0; i < 5; i++) {
        arg1[i + 6] = 0xFF;
    }
    for (i = 0; i < func_0026FE20(arg0); i++) {
        if (arg3 == buf[i] && arg3 != 999) {
            arg1[6] = i;
            func_001DCD70(arg2, buf[i]);
            return 1;
        }
    }
    for (i = 0; i < func_0026FE20(arg0); i++) {
        if ((func_0026FCE0(buf[i]) >> 5) != 0 && (func_0026FCE0(buf[i]) >> 5) != 2) {
            arg1[6] = i;
            func_001DCD70(arg2, buf[i]);
            return 1;
        }
    }
    for (i = 0; i < func_0026FE20(arg0); i++) {
        if ((func_0026FCE0(buf[i]) >> 5) != 0) {
            arg1[6] = i;
            func_001DCD70(arg2, buf[i]);
            return 1;
        }
    }
    return -1;
}

typedef struct Info_00164CE0 {
    u8 pad00[8];
    u16 x;
    s16 y;
} Info_00164CE0;

typedef struct Sprite_00164CE0 {
    Info_00164CE0 *info;
    u8 pad04[0x34];
    s16 x;
    s16 y;
} Sprite_00164CE0;

u16 *func_00278A90(s32, u16 *, s32, s32, s32, s16 *, s16 *);
s32 func_00278F10(s32, u16 *, s32, s32);

s32 func_00164CE0(s32 arg0, u8 *arg1, void *arg2) {
    u16 *nodes[8];
    s32 entries[7];
    s16 a;
    s16 b;
    s32 i;
    s32 card;
    s32 value;
    s32 best;

    if (arg2 == NULL) {
        return -1;
    } else {
        s32 top;
        s32 *entry;
        u16 **node;

        func_0026FD30(arg0, entries);
        best = -1;
        top = -1;
        i = 0;
        if (i < func_0026FE20(arg0)) {
            entry = entries;
            node = nodes;
            do {
                b = 0;
                a = 0;
                card = *entry;
                *node = NULL;
                if ((func_0026FCE0(card) >> 5) == 0) {
                    *node = func_00278A90(arg0, *node, i & 0xFF, card & 0xFFFF, 0, &a, &b);
                    *node = func_00278E40(*node);
                    value = func_00278F10(arg0, *node, 0, 0);
                    if (func_0026FB10(arg0, card) == 1) {
                        if (best < value) {
                            func_00164EC0(arg0, *node, entries);
                            func_00278DD0((u8 *)*node + 2, arg1 + 6);
                            func_001DCD70(arg2, **node);
                            ((Sprite_00164CE0 *)arg2)->x = (value >> 16) - (((Sprite_00164CE0 *)arg2)->info->x & 0x1FFF);
                            ((Sprite_00164CE0 *)arg2)->y = (value & 0xFFFF) - (((Sprite_00164CE0 *)arg2)->info->y & 0x1FFF);
                            best = value;
                            if (top < value) {
                                top = value;
                            }
                        }
                    } else if (top < value) {
                        top = value;
                    }
                }
                entry++;
                node++;
                i++;
            } while (i < func_0026FE20(arg0));
        }
        return top;
    }
}

typedef struct {
    u16 id;
    u8 values[5];
} Info_00164EC0;

void func_00164EC0(s32 arg0, void *arg1, s32 *arg2) {
    Info_00164EC0 *info = arg1;
    u8 buf[5];
    s32 count;
    s32 i;
    s32 card;
    u8 level;
    u32 cost;
    extern u32 func_0026FBB0();

    if (info != NULL) {
        level = func_0026FA80(info->id, arg0);
        for (i = 0; i < 5; i++) {
            buf[i] = 0xFF;
        }
        for (i = 0, count = 0; i < func_0026FE20(arg0); i++) {
            if ((u8)func_00278E00(i, info->values) == 0) {
                buf[count++] = i;
            }
        }
        if (count != 0) {
            for (i = 0; i < (u8)func_00278D90(buf); i++) {
                card = arg2[buf[i]];
                if (card != 0x3E7 && func_001650A0(card) == 0 && level >= func_0026FA80(card, arg0)) {
                    cost = func_0026FBB0(card);
                    if ((cost & 0xFFFF) + (cost >> 16) * 2 == 0 && func_0026FC10(card) == 2 &&
                        (u16)func_002789F0(info->id, (u16)card) == 0x3E7) {
                        func_00278D20(info->values, buf[i]);
                    }
                }
            }
        }
    }
}

s32 func_001650A0(s32 arg0) {
    if ((func_0026FCE0(arg0) >> 5) != 0) {
        return 1;
    }
    if (func_0026FC10(arg0) == 1) {
        return 1;
    }
    return 0;
}

typedef struct {
    u8 pad0[6];
    u8 slot[5];
} Obj1_00165100;

typedef struct {
    u8 pad0[0x3C];
    u16 id;
} Obj2_00165100;

s32 func_00165100(s32 arg0, void *arg1, void *arg2) {
    Obj1_00165100 *o1 = arg1;
    Obj2_00165100 *o2 = arg2;
    s32 list[8];
    s32 i;
    u8 k;

    for (i = 0; i < 5; i++) {
        o1->slot[i] = 0xFF;
    }
    func_0026FD30(arg0, list);
    if (o2 == NULL) {
        return -1;
    }
    for (i = 0; i < func_0026FE20(arg0); i++) {
        if (i != o1->slot[0] && i != o1->slot[1]) {
            if (o2->id == list[i] && func_0026FB10(arg0, list[i]) == 1) {
                o1->slot[0] = i;
            }
        }
    }
    k = 1;
    if ((func_0026FCE0(list[o1->slot[0]]) >> 5) == 0) {
        for (i = 0; i < func_0026FE20(arg0); i++) {
            if (i != o1->slot[0] && i != o1->slot[1]) {
                if (func_00248F60(list[o1->slot[0]], list[i]) >= 0 && (func_0026FCE0(list[i]) >> 5) == 2) {
                    if (list[i] != 0x31B && list[i] != 0x31C) {
                        o1->slot[k] = i;
                        k++;
                    }
                }
            }
        }
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_015", func_001652F0);

INCLUDE_ASM("asm/nonmatchings/main_015", func_001658F0);

INCLUDE_ASM("asm/nonmatchings/main_015", func_00165EC0);

INCLUDE_ASM("asm/nonmatchings/main_015", func_001664A0);

typedef struct {
    u8 low : 4;
    u8 high : 4;
} Nibbles_00166D10;

typedef struct {
    u16 pos;
    u8 kind;
    u8 pad3;
    u16 target;
    u8 pad6[6];
    s32 flag;
    u8 result;
} Out_00166D10;

s32 func_001664A0(u16 *, s32, void *, u8, s32);
s32 func_00166EE0(s32);
s32 func_001E1E70(s32, s32, s32, s32);
s32 func_0027DBC0(s32, s32, s32);

s32 func_00166D10(u16 *arg0, s32 arg1, void *arg2, u8 arg3) {
    u16 *unit = arg0;
    s32 card;
    s32 col;
    u16 row;
    Out_00166D10 *out = arg2;
    Nibbles_00166D10 entries[12];
    s32 i;
    Nibbles_00166D10 *entry;

    func_001E1090(*unit >> 8, *unit & 0xFF);
    entry = entries;
    i = 0;
    do {
        entry->low = entry->high = 15;
        entry++;
        i++;
    } while (i < 12);
    card = func_00166EE0(arg1);
    if (func_0027D830(*unit >> 8, *unit & 0xFF, 0, 0, 6, 1) == 5) {
        card = -1;
    }
    if (card >= 0) {
        row = card >> 16;
        col = func_0027DBC0(row, card & 0xFF, 0x1E);
        out->pos = *unit;
        out->kind = 12;
        out->result = func_0027E360(*unit >> 8, *unit & 0xFF, out->target, 1, 1);
        out->flag = 1;
        out->target = (row << 8) | col;
        func_0027B1B0(unit, arg3);
        return 0;
    }
    if (func_001E2100(*unit >> 8, *unit & 0xFF, 4) != 0) {
        func_001E1E70(*unit >> 8, *unit & 0xFF, 0, 1);
        out->pos = *unit;
        out->kind = 14;
        return 0;
    }
    return func_001664A0(unit, arg1, out, arg3, 1);
}

INCLUDE_ASM("asm/nonmatchings/main_015", func_00166EE0);

INCLUDE_ASM("asm/nonmatchings/main_015", func_001670A0);

static inline s32 max_00167570(s32 a, s32 b) {
    if (a < b) {
        return b;
    }
    return a;
}

s32 func_00167570(s32 arg0, s32 arg1, s32 arg2, s32 arg3,
                  s32 arg4, s32 arg5) {
    s32 min_y;
    s32 min_x;

    min_y = arg3 < arg5 ? arg3 : arg5;
    arg5 = max_00167570(arg5, arg3);
    min_x = arg2 < arg4 ? arg2 : arg4;
    arg4 = max_00167570(arg4, arg2);
    if ((arg4 - min_x) + (arg5 - min_y) != 2) {
        return 0;
    }
    if (func_001DF540(arg0, arg1) == 0) {
        return 0;
    }
    if (func_001E2100(arg0, arg1, 0) == 0) {
        if (func_0024DF00(func_001E22B0(arg2, arg3), arg0, arg1) != 1) {
            return 0;
        }
        return 1;
    }
    return 0;
}

s32 func_00167670(s32 arg0, s32 arg1) {
    s32 sp20[4];

    func_00254C90(sp20, *(s32 *)((u8 *)func_0026FC90(arg1, 0) + 4));
    if (func_00254890(sp20, arg0) < 0) {
        return 0;
    }
    return 1;
}

s32 func_001676D0(void) {
    return 0;
}

typedef struct {
    u16 unk0;
    u8 unk2;
    u8 pad3;
    u16 unk4;
    u8 unk6[5];
    u8 padB;
    s32 unkC;
    u8 unk10;
} Req_001676E0;

typedef struct {
    u8 pad0[0x160];
    u16 list[32];    /* 0x160 */
    u8 idx : 5;      /* 0x1A0 */
    u8 pad1A0 : 3;
    u8 pad1A1;
    u16 count;       /* 0x1A2 */
} Work_001676E0;

s32 func_00163130(void *, void *, s32);
s32 func_00276290(void *, void *, s32);

s32 func_001676E0(s32 arg0, void *arg1) {
    Req_001676E0 req;
    Work_001676E0 *w;
    s32 i;
    s32 ret;

    w = arg1;
    req.unk0 = 0xFFFF;
    req.unk2 = 0xFF;
    req.unk4 = 0xFFFF;
    req.unkC = 0;
    req.unk10 = 0xFF;
    if (w == NULL) {
        return 0x800;
    }
    for (i = 0; i < 5; i++) {
        req.unk6[i] = 0xFF;
    }
    w->count++;
    if (w->count == 600) {
        return 0x20;
    }
    if (w->count == 601) {
        return 0x20;
    }
    if (w->count == 602) {
        return 0x20;
    }
    if (!(w->count < 603)) {
        return 0x800;
    }
    if (w->idx == 0) {
        func_00275E80(w);
        if (func_00163130(w, &req, arg0) == 0) {
            return 0x800;
        }
        if (func_00276290(w, &req, arg0) < 0) {
            return 0;
        }
    }
    ret = w->list[w->idx - 1];
    if (ret == 0xFFFF) {
        return 0;
    }
    if (w->list[w->idx] == 0xFFFF) {
        w->idx = 0;
        for (i = 0; i < 32; i++) {
            w->list[i] = 0xFFFF;
        }
    } else {
        w->idx++;
    }
    return (u16)ret;
}

INCLUDE_ASM("asm/nonmatchings/main_015", func_001678B0);

INCLUDE_ASM("asm/nonmatchings/main_015", func_00167D30);

s32 func_00167E80(u16 *arg0, s32 arg1, s32 arg2) {
    s32 i;
    s32 pos;
    s32 ret;
    s32 idx;
    u16 list[22];

    for (i = 0; i < 22; i++) {
        list[i] = 0xFFFF;
    }
    func_0027C070(arg1, list, 0x1D, 1);
    ret = func_0027B360(arg1, list, arg0);
    if (ret >= 0) {
        return ret;
    }
    for (i = 0; i < 22; i++) {
        list[i] = 0xFFFF;
    }
    func_0027C070(arg1, list, 0x1E, 1);
    for (i = 0; i < func_0027C670(list); i++) {
        if ((func_001E0700(list[i] >> 8, list[i] & 0xFF) >> 5) == 3 &&
            func_0027B9B0(list[i]) == 1 && func_0027C6D0(list[i]) == 1) {
            return list[i];
        }
    }
    for (i = 0; i < 22; i++) {
        list[i] = 0xFFFF;
    }
    func_0027C070(arg1, list, 0x1F, 1);
    for (i = 0; i < func_0027C670(list); i++) {
        if (func_0027B9B0(list[i]) == 1 && func_0027C6D0(list[i]) == 1) {
            return list[i];
        }
    }
    pos = arg1 << 8;
    idx = func_00276C80(arg0, pos);
    func_00167D30(arg0 + idx * 8);
    if (((arg0[idx * 8 + 2] >> 8) & 0xFF) == 10) {
        if (func_001DE6D0(arg1) == 1 && func_001687A0(pos, arg1, arg2) >= 0) {
            return pos | 0x10000;
        }
        if (func_0027B9B0(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (func_001E2100(arg1, 0, 0) == 0) {
        if (func_0027B9B0(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (func_001DE6D0(arg1) == 1 && func_001687A0(pos, arg1, arg2) >= 0) {
        return pos | 0x10000;
    }
    for (i = 0; i < 22; i++) {
        list[i] = 0xFFFF;
    }
    func_0027C070(arg1, list, 0x1F, 1);
    for (i = 0; i < func_0027C670(list); i++) {
        if (func_001E2100(list[i] >> 8, list[i] & 0xFF, 0) == 0 && func_0027C6D0(list[i]) == 1) {
            return list[i];
        }
    }
    return -1;
}

typedef struct {
    u16 coordinates;
    u16 unk02;
    s16 state;
    u16 unk06;
    union {
        u32 word;
        struct {
            u16 low;
            u16 high;
        } halves;
    } data;
} Entry_00168260;

typedef struct {
    u16 card;
    u8 flag;
    u8 pad;
} Slot_00168260;

void func_00168530(void *);

void func_00168260(void *arg0, s32 arg1) {
    extern void func_0027E770();
    extern s32 func_0027B200();
    extern s32 func_001684D0();
    extern s32 func_0016B0E0();
    Entry_00168260 *entry = arg0;
    s32 side;
    s32 player;
    s32 other;
    s32 pos;
    s32 otherPos;
    s32 i;
    u8 work[0x70];
    Slot_00168260 list[22];
    s16 countA;
    s16 countB;

    if (func_001DF540(entry->coordinates >> 8, entry->coordinates & 0xFF) != 0) {
        side = func_0024DE70(entry->coordinates >> 8, entry->coordinates & 0xFF);
        other = (side == 0 ? 1 : 0) << 8;
        pos = func_001E1090(entry->coordinates >> 8, entry->coordinates & 0xFF);
        otherPos = func_001E1090(other >> 8, other & 0xFF);
        player = func_001DF540(entry->coordinates >> 8, entry->coordinates & 0xFF);
        for (i = 0; i < 22; i++) {
            list[i].card = 0xFFFF;
            list[i].flag = 0xFF;
        }
        func_0027E770(work);
        if (arg1 != 0) {
            if (func_0027B200(entry->coordinates >> 8, entry->coordinates & 0xFF, pos & 0xFF, pos >> 8,
                              other >> 8, other & 0xFF, otherPos & 0xFF, otherPos >> 8, 4) > 0) {
                entry->state = 0x2FF;
                entry->data.word = (other << 16) | entry->data.halves.low;
                return;
            }
        }
        countB = 0;
        countA = 0;
        i = 1;
        while (1) {
            switch (func_001684D0(entry, 0, player, pos & 0xFF, pos >> 8,
                                  func_0024DE70(entry->coordinates >> 8, entry->coordinates & 0xFF) == 0 ? 1 : 0,
                                  i & 0xFF, func_0016B0E0(side), list, 0, &countA, &countB, 4, work)) {
            case 3:
                entry->state = 0x6FF;
                entry->data.word = (pos << 16) | entry->data.halves.low;
                return;
            case 2:
                entry->state = 0x3FF;
                entry->data.word = (pos << 16) | entry->data.halves.low;
                return;
            case 1:
                return;
            case 0:
                entry->state = 0x5FF;
                return;
            }
            i++;
            if (i > 4) {
                break;
            }
        }
        func_00168530(entry);
    }
}

void func_001684D0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28) {
    func_0027DE20(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
                  arg_sp0, arg_sp8, arg_sp10, arg_sp18, arg_sp20,
                  1, 3000, arg_sp28);
}

INCLUDE_ASM("asm/nonmatchings/main_015", func_00168530);

typedef struct {
    u8 pad00[0x3C];
    u16 unk3C;
    u8 pad3E[0x22];
} Work_001687A0;

typedef struct {
    u16 id;
    u8 unk2;
    u8 pad3;
    s16 unk4;
    u8 pad6[6];
    s32 unkC;
} Ctx_001687A0;

s32 func_00168A30(s32 arg0, void *arg1);
s32 func_00169610(s32 arg0, u8 arg1, void *arg2, s32 arg3);

s32 func_001687A0(s32 arg0, s32 arg1, s32 arg2) {
    extern s32 func_00278890();
    extern s32 func_0016B0E0();
    Work_001687A0 work;
    s32 ret;
    s32 res;
    s32 pos;
    s32 kind;
    Ctx_001687A0 *ctx = (Ctx_001687A0 *)arg2;

    ctx->id = arg0;
    if (func_001DE6D0(arg1) == 0) {
        return -1;
    }
    if (func_00278890(arg1, 0) == 5 && func_00278890(arg1, 1) == 5) {
        return -1;
    }
    kind = func_00168A30(arg1, &work);
    if (kind < 0) {
        return -1;
    }
    ctx->unk2 = 10;
    ctx->unkC = 0;
    pos = func_001E1090(arg0 >> 8, arg0 & 0xFF);
    if (kind == 0) {
        if (func_00169000(arg1, (u8 *)ctx, &work) >= 0) {
            ret = func_00276F10(&work, pos & 0xFF, pos >> 8,
                                arg1 == 0 ? 1 : 0, 2, 0x1F, 2, 2,
                                1, func_0016B0E0(arg1));
            if (ret < 0) {
                if (func_001E0150(arg1) < 6) {
                    res = func_00169610(arg1, kind, &work, ret);
                    if (res < 0) {
                        return -1;
                    }
                    ctx->unk4 = res;
                    return 1;
                }
            } else {
                res = func_00169610(arg1, kind, &work, ret);
                if (res < 0) {
                    return -1;
                }
                ctx->unk4 = res;
                return 1;
            }
        }
    } else {
        ret = func_00276F10(&work, pos & 0xFF, pos >> 8,
                            arg1 == 0 ? 1 : 0, 2, 0x1F, 2, 2,
                            1, func_0016B0E0(arg1));
    }
    if (kind == 2) {
        func_00169420(arg1, ctx, &work);
        res = func_00169610(arg1, kind, &work, ret);
        if (res < 0) {
            return -1;
        }
        ctx->unk4 = res;
        return 1;
    }
    if (func_00168E00(arg1, (u8 *)ctx, &work, work.unk3C) < 0) {
        return -1;
    }
    res = func_00169610(arg1, kind, &work, ret);
    if (res < 0) {
        return -1;
    }
    ctx->unk4 = res;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_015", func_00168A30);

s32 func_00168D10(s32 arg0, void *arg1, void *arg2, s32 arg3) {
    s32 values[8];
    s32 index;

    func_0026FD30(arg0, values);
    for (index = 0; index < func_0026FE20(arg0); index++) {
        if (((arg3 & 0xFFFF) == values[index]) && (func_0026FB10(arg0, values[index]) == 1)) {
            ((u8 *)arg1)[6] = index;
            func_001DCD70(arg2, values[index]);
            return func_0026FCE0(values[index]) >> 5;
        }
    }
    return -1;
}

s32 func_00168E00(s32 arg0, u8 *arg1, void *arg2, s32 arg3) {
    s32 buf[8];
    s32 i;

    func_0026FD30(arg0, buf);
    if (arg2 == NULL) {
        return -1;
    }
    for (i = 0; i < 5; i++) {
        arg1[i + 6] = 0xFF;
    }
    for (i = 0; i < func_0026FE20(arg0); i++) {
        if (arg3 == buf[i] && arg3 != 999) {
            arg1[6] = i;
            func_001DCD70(arg2, buf[i]);
            return 1;
        }
    }
    for (i = 0; i < func_0026FE20(arg0); i++) {
        if ((func_0026FCE0(buf[i]) >> 5) != 0 && (func_0026FCE0(buf[i]) >> 5) != 2) {
            arg1[6] = i;
            func_001DCD70(arg2, buf[i]);
            return 1;
        }
    }
    for (i = 0; i < func_0026FE20(arg0); i++) {
        if ((func_0026FCE0(buf[i]) >> 5) != 0) {
            arg1[6] = i;
            func_001DCD70(arg2, buf[i]);
            return 1;
        }
    }
    return -1;
}

typedef struct Info_00169000 {
    u8 pad00[8];
    u16 x;
    s16 y;
} Info_00169000;

typedef struct Sprite_00169000 {
    Info_00169000 *info;
    u8 pad04[0x34];
    s16 x;
    s16 y;
} Sprite_00169000;

u16 *func_00278A90(s32, u16 *, s32, s32, s32, s16 *, s16 *);
s32 func_00278F10(s32, u16 *, s32, s32);

s32 func_00169000(s32 arg0, u8 *arg1, void *arg2) {
    u16 *nodes[8];
    s32 entries[7];
    s16 a;
    s16 b;
    s32 i;
    s32 card;
    s32 value;
    s32 best;

    if (arg2 == NULL) {
        return -1;
    } else {
        s32 top;
        s32 *entry;
        u16 **node;

        func_0026FD30(arg0, entries);
        best = -1;
        top = -1;
        i = 0;
        if (i < func_0026FE20(arg0)) {
            entry = entries;
            node = nodes;
            do {
                b = 0;
                a = 0;
                card = *entry;
                *node = NULL;
                if ((func_0026FCE0(card) >> 5) == 0) {
                    *node = func_00278A90(arg0, *node, i & 0xFF, card & 0xFFFF, 0, &a, &b);
                    *node = func_00278E40(*node);
                    value = func_00278F10(arg0, *node, 0, 0);
                    if (func_0026FB10(arg0, card) == 1) {
                        if (best < value) {
                            func_001691E0(arg0, *node, entries);
                            func_00278DD0((u8 *)*node + 2, arg1 + 6);
                            func_001DCD70(arg2, **node);
                            ((Sprite_00169000 *)arg2)->x = (value >> 16) - (((Sprite_00169000 *)arg2)->info->x & 0x1FFF);
                            ((Sprite_00169000 *)arg2)->y = (value & 0xFFFF) - (((Sprite_00169000 *)arg2)->info->y & 0x1FFF);
                            best = value;
                            if (top < value) {
                                top = value;
                            }
                        }
                    } else if (top < value) {
                        top = value;
                    }
                }
                entry++;
                node++;
                i++;
            } while (i < func_0026FE20(arg0));
        }
        return top;
    }
}

typedef struct {
    u16 id;
    u8 values[5];
} Info_001691E0;

void func_001691E0(s32 arg0, void *arg1, s32 *arg2) {
    Info_001691E0 *info = arg1;
    u8 buf[5];
    s32 count;
    s32 i;
    s32 card;
    u8 level;
    u32 cost;
    extern u32 func_0026FBB0();

    if (info != NULL) {
        level = func_0026FA80(info->id, arg0);
        for (i = 0; i < 5; i++) {
            buf[i] = 0xFF;
        }
        for (i = 0, count = 0; i < func_0026FE20(arg0); i++) {
            if ((u8)func_00278E00(i, info->values) == 0) {
                buf[count++] = i;
            }
        }
        if (count != 0) {
            for (i = 0; i < (u8)func_00278D90(buf); i++) {
                card = arg2[buf[i]];
                if (card != 0x3E7 && func_001693C0(card) == 0 && level >= func_0026FA80(card, arg0)) {
                    cost = func_0026FBB0(card);
                    if ((cost & 0xFFFF) + (cost >> 16) * 2 == 0 && func_0026FC10(card) == 2 &&
                        (u16)func_002789F0(info->id, (u16)card) == 0x3E7) {
                        func_00278D20(info->values, buf[i]);
                    }
                }
            }
        }
    }
}

s32 func_001693C0(s32 arg0) {
    if ((func_0026FCE0(arg0) >> 5) != 0) {
        return 1;
    }
    if (func_0026FC10(arg0) == 1) {
        return 1;
    }
    return 0;
}

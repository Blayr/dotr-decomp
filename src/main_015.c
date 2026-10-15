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

#pragma conditional_move off

s32 func_00163130(void *work, void *arg1, s32 arg2) {
    extern s32 func_001676D0(s32);
    u16 *arg0 = work;
    s32 side;
    s32 found;
    s32 result;
    s32 index;

    side = func_001DE540();
    found = 0;
    if ((result = func_00163870(arg0, side, (s32)arg1)) < 0) {
        return 0;
    }
    index = func_00276C80(arg0, result & 0xFFFF);
    if (index < 0) {
        return 0;
    }
    if ((result >> 16) == 1) {
        if (((arg0[index * 8 + 2] >> 8) & 0xFF) == 10) {
            func_0027B1B0(arg0 + index * 8, 1);
        } else {
            func_0027B1B0(arg0 + index * 8, 0);
        }
        return 1;
    }
    func_00163660(arg0 + index * 8);
    switch ((arg0[index * 8 + 2] >> 8) & 0xFF) {
    case 5:
        if (func_001E2100(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            func_001658F0(arg0 + index * 8, side, arg1, 1);
            found = 1;
        }
        break;
    case 2:
        if (func_001E2100(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            if (func_00165EC0(arg0 + index * 8, side, arg1, 1) < 0) {
                func_0027B1B0(arg0 + index * 8, 1);
                return 1;
            }
            found = 1;
        }
        break;
    case 10:
        if (func_001643F0(arg0[index * 8], side, (s32)arg1) < 0) {
            func_0027B1B0(arg0 + index * 8, 1);
            *(u8 *)((u8 *)arg1 + 2) = 0xFF;
            *(s32 *)((u8 *)arg1 + 0xC) = 0;
        } else {
            func_0027B1B0(arg0 + index * 8, 1);
            found = 1;
        }
        break;
    case 6:
        if (func_001E2100(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            func_001664A0(arg0 + index * 8, side, arg1, 1, 0);
            found = 1;
        }
        break;
    case 3:
        if (func_001E2100(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            func_001664A0(arg0 + index * 8, side, arg1, 1, 1);
            found = 1;
        }
        break;
    case 9:
        func_0027D020(arg0 + index * 8, side, arg1, 1, 1, func_001676D0(side), 5, 1);
        found = 1;
        break;
    case 12:
        func_00166D10(arg0 + index * 8, side, arg1, 1);
        found = 1;
        break;
    case 14:
        func_00276EC0(arg0 + index * 8, side, arg1);
        found = 1;
        break;
    default:
        found = 0;
        break;
    }
    if (found == 1) {
        return 1;
    }
    found = 0;
    switch (arg0[index * 8 + 2] & 0xFF) {
    case 5:
        if (func_001E2100(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            func_001658F0(arg0 + index * 8, side, arg1, 0);
            found = 1;
        }
        break;
    case 2:
        if (func_001E2100(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            if (func_00165EC0(arg0 + index * 8, side, arg1, 0) < 0) {
                func_001658F0(arg0 + index * 8, side, arg1, 0);
            }
            found = 1;
        }
        break;
    case 10:
        if (func_001643F0(arg0[index * 8], side, (s32)arg1) < 0) {
            func_0027B1B0(arg0 + index * 8, 0);
            *(u8 *)((u8 *)arg1 + 2) = 0xFF;
            found = 1;
            *(s32 *)((u8 *)arg1 + 0xC) = 0;
        } else {
            func_0027B1B0(arg0 + index * 8, 0);
            found = 1;
        }
        break;
    case 6:
        if (func_001E2100(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            func_001664A0(arg0 + index * 8, side, arg1, 0, 0);
            found = 1;
        }
        break;
    case 3:
        if (func_001E2100(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            func_001664A0(arg0 + index * 8, side, arg1, 0, 1);
            found = 1;
        }
        break;
    case 9:
        func_0027D020(arg0 + index * 8, side, arg1, 0, 1, func_001676D0(side), 5, 1);
        found = 1;
        break;
    case 12:
        func_00166D10(arg0 + index * 8, side, arg1, 0);
        found = 1;
        break;
    case 14:
        func_00276EC0(arg0 + index * 8, side, arg1);
        break;
    default:
        return 0;
    }
    if (found == 1) {
        return 1;
    }
    return 0;
}
#pragma conditional_move reset

typedef struct Entry_00163660 {
    u16 coordinates;
    u16 pad2;
    s16 action;
    u16 pad6;
    s32 target;
} Entry_00163660;

s32 func_00163660(void *arg0) {
    extern s32 func_001676D0();
    Entry_00163660 *entry = arg0;
    s32 card;
    u16 coordinates;

    func_001E1090(entry->coordinates >> 8, entry->coordinates & 0xFF);
    card = func_00250360(entry->coordinates >> 8, entry->coordinates & 0xFF);
    if (func_001DF540(entry->coordinates >> 8, entry->coordinates & 0xFF) != 0) {
        if (func_001E2100(entry->coordinates >> 8, entry->coordinates & 0xFF, 0) == 0) {
            coordinates = entry->coordinates;
            if (coordinates != 0xFFFF) {
                if ((coordinates & 0xFF) == 0) {
                    if (entry->target == -1) {
                        if (func_0027BBC0(coordinates >> 8, coordinates & 0xFF, 1) == 1) {
                            if (func_001DE6D0(entry->coordinates >> 8) == 1) {
                                entry->action = 0x50A;
                            } else {
                                entry->action = 0x5FF;
                            }
                        } else if (func_001DE6D0(entry->coordinates >> 8) == 1) {
                            entry->action = 0xA06;
                            entry->target = (entry->target & 0xFFFF0000) | 0x103;
                        } else {
                            entry->action = 0x6FF;
                            entry->target = (u16)entry->target | 0x1030000;
                        }
                    }
                } else {
                    switch (func_001E0700(coordinates >> 8, coordinates & 0xFF) >> 5) {
                    case 0:
                    case 5:
                        if (func_002507D0(entry->coordinates >> 8, entry->coordinates & 0xFF) == 1) {
                            func_00164020((s32)entry);
                        } else {
                            func_00163C50(entry, 1);
                        }
                        break;
                    case 2:
                        func_0027CA50(entry, 5, 1, func_001676D0(card) & 0xFF);
                        break;
                    case 1:
                    case 3:
                    case 4:
                        func_00164260(entry);
                        break;
                    default:
                        entry->action = 0x5FF;
                        break;
                    }
                }
                return 1;
            }
        }
    }
    return 0;
}

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

typedef struct Entry_00164020 {
    u16 position;
    u8 flag;
    u8 padding;
} Entry_00164020;

typedef struct Record_00164020 {
    u16 position;
    u16 unused2;
    u16 mode;
    u16 unused6;
    union {
        u32 value;
        struct {
            u16 low;
            u16 high;
        } parts;
    } result;
} Record_00164020;

s32 func_00277160(s32, s32, s32, void *, s32, s32, s32, s32, s32, s32, u16);

void func_00164020(s32 arg0) {
    extern void func_0027E770();
    extern s32 func_001E1030();
    extern s32 func_001676D0();
    extern s32 func_002770E0();
    u8 work[112];
    Entry_00164020 entries[22];
    u16 first;
    u16 second;
    u16 count;
    s32 attempt;
    Record_00164020 *record = (Record_00164020 *)arg0;
    s32 kind;
    u16 coordinate;

    coordinate = record->position;
    if (func_001DF540((s32)coordinate >> 8, coordinate & 0xFF) != 0) {
        s32 owner;
        s32 position;
        s32 state;
        s32 card;
        s32 x;
        coordinate = record->position;
        owner = func_0024DE70((s32)coordinate >> 8, coordinate & 0xFF);
        coordinate = record->position;
        position = func_001E1090((s32)coordinate >> 8, coordinate & 0xFF);
        count = 0;
        second = 0;
        first = 0;
        coordinate = record->position;
        card = func_001DF540((s32)coordinate >> 8, coordinate & 0xFF);
        {
            s32 i = 0;
            Entry_00164020 *entry = entries;
            do {
                i++;
                entry->position = 0xFFFF;
                entry->flag = 0xFF;
                entry++;
            } while (i < 22);
        }
        func_0027E770(work);
        state = 0;
        coordinate = record->position;
        kind = func_001E1030((s32)coordinate >> 8, coordinate & 0xFF);
        switch (kind) {
        case 0x129:
            x = position >> 8;
                attempt = 1;
                position &= 0xFF;
                while (1) {
                    s32 result;
                    result = func_001676D0(owner);
                    state = func_002770E0(state, card, position, x, owner == 0 ? 1 : 0,
                                         (u8)attempt, 1, result, entries, &count,
                                         &first, &second, work);
                    result = func_00277160(card, position, x, entries, 5, 0x34, 0, 2,
                                          1, func_001676D0(owner), count);
                    if (result >= 0) {
                        record->mode = 0x2FF;
                        record->result.value = (result << 16) | record->result.parts.low;
                        return;
                    }
                    attempt++;
                    if (attempt <= 5) {
                        continue;
                    }
                    break;
                }
            break;
        case 0x4F:
            if (func_001DF470(owner) < 2000) {
                record->mode = 0x2FF;
                record->result.value = (position << 16) | record->result.parts.low;
            }
            break;
        }
        func_00163C50(record, 1);
    }
}

typedef struct {
    u16 location;
    u16 unk02;
    u16 flags;
    u16 unk06;
    union {
        u32 word;
        u16 low;
    } destination;
} Entry_00164260;

void func_00164260(void *arg0) {
    Entry_00164260 *entry = arg0;
    s32 i;
    s32 location;
    s32 result;

    if (func_001DF540(entry->location >> 8, entry->location & 0xFF) == 0) {
        return;
    }
    func_0024DE70(entry->location >> 8, entry->location & 0xFF);
    func_001E1090(entry->location >> 8, entry->location & 0xFF);
    if (*(u16 *)((u8 *)func_001DF540(entry->location >> 8, entry->location & 0xFF) + 0x3C) == 0x2B0) {
        entry->flags = 0xCFF;
    } else {
        entry->flags = 0x3FF;
    }
    i = 0;
    do {
        result = func_00164360(i & 0xFF);
        location = result & 0xFFFF;
        result = func_001E3790(result & 0xFF, location >> 8);
        if (result == entry->location || result < 0) {
            entry->destination.word = (location << 16) | entry->destination.low;
            return;
        }
    } while (++i < 5);
    return;
}

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

typedef struct {
    s16 id;
    u8 unk2;
    u8 pad3;
    s16 unk4;
    u8 pad6[6];
    s32 unkC;
} Ctx_001643F0;

typedef struct {
    u8 pad0[0x3C];
    u16 unk3C;
    u8 pad3E[0x22];
} Work_001643F0;


s32 func_001643F0(s32 arg0, s32 arg1, s32 arg2) {
    extern s32 func_00278890(s32, s32);
    extern s32 func_001676D0();
    Work_001643F0 work;
    s32 ret;
    s32 res;
    s32 pos;
    s32 kind;
    Ctx_001643F0 *ctx = (Ctx_001643F0 *)arg2;

    ctx->id = arg0;
    if (func_001DE6D0(arg1) == 0) {
        return -1;
    }
    if (func_00278890(arg1, 0) == 5 && func_00278890(arg1, 1) == 5) {
        return -1;
    }
    kind = func_00164680(arg1, &work);
    if (kind < 0) {
        return -1;
    }
    ctx->unk2 = 10;
    ctx->unkC = 0;
    pos = func_001E1090(arg0 >> 8, arg0 & 0xFF);
    if (kind == 0) {
        if (func_00164CE0(arg1, (u8 *)ctx, &work) >= 0) {
            ret = func_00276F10(&work, pos & 0xFF, pos >> 8, arg1 == 0 ? 1 : 0,
                                2, 0x1F, 2, 2, 1, func_001676D0(arg1));
            if (ret < 0) {
                if (func_001E0150(arg1) < 6) {
                    res = func_001652F0(arg1, kind, &work, ret);
                    if (res < 0) {
                        return -1;
                    }
                    ctx->unk4 = res;
                    return 1;
                }
            } else {
                res = func_001652F0(arg1, kind, &work, ret);
                if (res < 0) {
                    return -1;
                }
                ctx->unk4 = res;
                return 1;
            }
        }
    } else {
        ret = func_00276F10(&work, pos & 0xFF, pos >> 8, arg1 == 0 ? 1 : 0,
                            2, 0x1F, 2, 2, 1, func_001676D0(arg1));
    }
    if (kind == 2) {
        func_00165100(arg1, ctx, &work);
        res = func_001652F0(arg1, kind, &work, ret);
        if (res < 0) {
            return -1;
        }
        ctx->unk4 = res;
        return 1;
    }
    if (func_00164AE0(arg1, (u8 *)ctx, &work, work.unk3C) < 0) {
        return -1;
    }
    res = func_001652F0(arg1, kind, &work, ret);
    if (res < 0) {
        return -1;
    }
    ctx->unk4 = res;
    return 1;
}

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

typedef struct Nibbles_001652F0 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_001652F0;

static inline u16 target_001652F0(u8 index) {
    switch (index) {
        case 0: return (u16)0x203;
        case 1: return (u16)0x301;
        case 2: return (u16)0x305;
        case 3: return (u16)0x202;
        case 4: return (u16)0x204;
        default: return (u16)0x203;
    }
}

static inline s32 fallback_001652F0(s32 x, s32 y) {
    if (y == 0) {
        if (x >= 3) return 0x106;
        if (x < 3) return 0x100;
    }
    if (y < 6) {
        if (x >= 3) return 0x605;
        if (x < 3) return 0x601;
    }
    if (x >= 3) return 0x601;
    return 0x605;
}


s32 func_001652F0(s32 arg0, u8 arg1, void *arg2, s32 arg3) {
    extern s32 func_001676D0();
    extern s32 func_00278510();
    extern s32 func_0027A130();
    extern s32 func_002792C0(void *, void *, s32, s32, s32, s32, u16, u8);
    s32 bestCandidate;
    s32 bestScore;
    s32 index;
    s32 searchCandidate;
    s32 fallbackCandidate;
    Nibbles_001652F0 path[12];
    s32 targetY1;
    s32 targetX1;
    s32 targetY2;
    s32 targetY;
    s32 targetX;
    s32 score;
    s32 target;
    s32 occupied;
    s32 limit;
    u8 kind;
    s32 count;
    Nibbles_001652F0 *p;

    if (arg2 == NULL) {
        return -1;
    }
    p = path;
    count = 0;
    do {
        count++;
        p->low = p->high = 15;
        p++;
    } while (count < 12);

    kind = *(u8 *)((u8 *)arg2 + 0x3E) >> 5;
    if (kind == 0 || kind == 5) {
        if (arg3 >= 0) {
            s32 candidate;
            s32 y;
            s32 x;
            s32 i;
            bestScore = 255;
            bestCandidate = 65535;
            target = func_001E1090(arg3 >> 8, arg3 & 255);
            i = 0;
            targetY1 = target >> 8;
            targetX1 = target & 255;
            do {
                candidate = func_0024E410(arg0, i);
                if (candidate >= 0) {
                    x = candidate & 255;
                    y = candidate >> 8;
                    if (func_001E22B0(x, y) != 8 &&
                        (func_001E22B0(x, y) != 9 || func_0024FE40(arg2, x, y) != 1) &&
                        func_001E36E0(x, y) == 0) {
                        if (func_00278510(arg2, arg3, func_001676D0(arg0), targetX1, targetY1, 1) > 0) {
                            score = func_0027A130(arg2, path, x, y, targetX1, targetY1, arg3, 1, 5, (u16)func_001676D0(arg0));
                        } else {
                            score = func_002792C0(arg2, path, x, y, targetX1, targetY1, arg3, 5);
                        }
                        if (func_0027AFC0((u8 *)path) > 0 && score < bestScore) {
                            bestScore = score;
                            bestCandidate = candidate;
                        }
                    }
                }
                i++;
            } while (i < 8);
            if (bestCandidate != 65535) {
                return bestCandidate;
            }
        }
        {
            s32 y2;
            s32 x2;
            s32 targetX2;
            s32 j;
            s32 candidate2;
        limit = 14;
        fallbackCandidate = -1;
        j = 0;
        do {
            candidate2 = func_0024E410(arg0, j);
            if (candidate2 >= 0) {
                x2 = candidate2 & 255;
                y2 = candidate2 >> 8;
                if (func_001E22B0(x2, y2) != 8 &&
                    (func_001E22B0(x2, y2) != 9 || func_0024FE40(arg2, x2, y2) != 1) &&
                    func_001E3790(x2, y2) < 0) {
                    target = fallback_001652F0(x2, y2);
                    targetX2 = target & 255;
                    targetY2 = target >> 8;
                    occupied = func_001E3790(targetX2, targetY2);
                    if (occupied < 0) {
                        occupied = 65535;
                    }
                    score = func_002792C0(arg2, path, x2, y2, targetX2, targetY2, occupied, 7);
                    if (score < limit && score >= 0) {
                        fallbackCandidate = candidate2;
                        limit = score;
                    }
                }
            }
            j++;
        } while (j < 8);
        if (limit < 14) {
            return fallbackCandidate;
        } else {
            fallbackCandidate = -1;
        }
        return fallbackCandidate;
        }
    } else {
        s32 k;
        s32 y3;
        s32 x3;
        s32 limit3;
        s32 candidate3;
        index = 0;
        do {
            target = (u16)target_001652F0((u8)index);
            limit3 = 14;
            searchCandidate = -1;
            if (target >= 0) {
                k = 0;
                targetY = target >> 8;
                targetX = target & 255;
                do {
                    candidate3 = func_0024E410(arg0, k);
                    if (candidate3 >= 0) {
                        x3 = candidate3 & 255;
                        y3 = candidate3 >> 8;
                        if (func_001E22B0(x3, y3) != 8 &&
                            (func_001E22B0(x3, y3) != 9 || func_0024FE40(arg2, x3, y3) != 1) &&
                            func_001E3790(x3, y3) < 0) {
                            occupied = func_001E3790(x3, y3);
                            if (occupied < 0) {
                                occupied = 65535;
                            }
                            score = func_002792C0(arg2, path, x3, y3, targetX, targetY, occupied, 7);
                            if (score < limit3 && score >= 0) {
                                searchCandidate = candidate3;
                                limit3 = score;
                            }
                        }
                    }
                    k++;
                } while (k < 8);
                if (limit3 < 14) {
                    return searchCandidate;
                }
            }
            index++;
        } while (index < 5);
    }
    return -1;
}

typedef struct Nibbles_001658F0 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_001658F0;

typedef struct Output_001658F0 {
    u16 position;
    u8 action;
    u8 pad3;
    u16 destination;
    u8 pad6[6];
    s32 special;
    u8 result;
} Output_001658F0;


s32 func_001658F0(u16 *arg0, s32 arg1, void *arg2, u8 arg3) {
    Output_001658F0 *output = arg2;
    s32 target;
    u8 endX;
    u8 extra;
    Nibbles_001658F0 nibbles[12];
    s32 bestScore;
    s32 best;
    s32 i;
    Nibbles_001658F0 *p;
    extern s32 func_001670A0();
    extern s32 func_001676D0();
    extern s32 func_00279C40(s32, s32, s32, s32, s32, s32, void *, u8);

    target = func_001E1090(*arg0 >> 8, *arg0 & 0xFF);
    p = nibbles;
    i = 0;
    do {
        i++;
        p->low = p->high = 0xF;
        p++;
    } while (i < 12);
    {
        s32 range;
        s32 y;
        u8 minY;
        u8 minX;
        s32 candidateScore;
        u8 maxY;
        s32 packedY;
        s32 centerY;
        s32 centerX;
        s32 x;
        s32 limit;
        u16 initialScore;

        initialScore = func_001676D0(arg1);
        centerX = target & 0xFF;
        centerY = target >> 8;
        if (func_00276CC0(centerX, centerY, *arg0, 2, initialScore, 1) == 0) {
            output->position = *arg0;
            output->action = 6;
            output->destination = target;
            output->result = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, output->destination, 1, 1);
            output->special = func_001670A0(*arg0 >> 8, *arg0 & 0xFF, arg0);
            func_0027B1B0(arg0, arg3);
            return 0;
        }
        if ((range = func_002464F0(func_001DF540(*arg0 >> 8, *arg0 & 0xFF), centerX, centerY)) == 0) {
            output->position = *arg0;
            output->action = 6;
            output->destination = target;
            output->result = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, output->destination, 1, 1);
            output->special = func_001670A0(*arg0 >> 8, *arg0 & 0xFF, arg0);
            func_0027B1B0(arg0, arg3);
            return 0;
        }
        if (func_001E2100(*arg0 >> 8, *arg0 & 0xFF, 4) != 0) {
            if ((func_001E0700(*arg0 >> 8, *arg0 & 0xFF) >> 5) == 1 ||
                (func_001E0700(*arg0 >> 8, *arg0 & 0xFF) >> 5) == 5) {
                func_001E1E70(*arg0 >> 8, *arg0 & 0xFF, 0, 1);
                output->position = *arg0;
                output->action = 0xE;
                return 0;
            }
        }
        best = 0xFF;
        bestScore = 0xFFFF;
        minX = (u8)func_00250860(0, centerX - (range & 0xF));
        limit = centerX + (range & 0xF);
        endX = limit >= 7 ? 6 : limit;
        minY = (u8)func_00250860(0, centerY - (range & 0xF));
        limit = centerY + (range & 0xF);
        if (limit >= 7) {
            limit = 6;
        }
        maxY = (u8)limit;
        if ((*arg0 & 0xFF) == 0) {
            extra = (u8)func_0027BBC0(*arg0 >> 8, *arg0 & 0xFF, 1);
        } else {
            extra = 0;
        }
        for (x = minX; x <= endX; x++) {
            y = minY;
            packedY = y << 8;
            for (; y <= maxY; packedY += 0x100, y++) {
                if ((((x < centerX ? centerX : x) - (centerX < x ? centerX : x)) +
                    ((y < centerY ? centerY : y) - (centerY < y ? centerY : y))) > (range & 0xF)) {
                    continue;
                }
                if (func_00279C40(*arg0 >> 8, *arg0 & 0xFF, centerX, centerY, x, y, arg0, extra) == 1) {
                    if (func_0027BE10(*arg0 >> 8, *arg0 & 0xFF, x, y, 1) == 0 || (u8)*arg0 == 0) {
                        candidateScore = func_00276CC0(x, y, *arg0, 2, (u16)func_001676D0(arg1), 1);
                        if (candidateScore < bestScore) {
                            bestScore = candidateScore;
                            best = packedY | x;
                        } else if (candidateScore == bestScore && func_001E36E0(x, y) == 0 &&
                            func_001E36E0(best & 0xFF, best >> 8) != 0) {
                            bestScore = candidateScore;
                            best = packedY | x;
                        }
                    }
                }
            }
        }
        if (best != 0xFF) {
            output->position = *arg0;
            output->action = 6;
            output->destination = best;
            if (best == target) {
                output->result = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, output->destination, 1, 1);
            } else {
                output->result = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, output->destination, 0, 1);
            }
            output->special = func_001670A0(*arg0 >> 8, *arg0 & 0xFF, arg0);
        } else {
            output->position = *arg0;
            output->action = 6;
            output->destination = target;
            output->result = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, output->destination, 1, 1);
            output->special = func_001670A0(*arg0 >> 8, *arg0 & 0xFF, arg0);
        }
        func_0027B1B0(arg0, arg3);
        return 0;
    }
}

typedef struct Coord_00165EC0 {
    u8 x : 4;
    u8 y : 4;
} Coord_00165EC0;

typedef struct Input_00165EC0 {
    u16 position;
    u8 pad[6];
    u32 targets;
} Input_00165EC0;

typedef struct Output_00165EC0 {
    u16 position;
    u8 command;
    u8 pad3;
    u16 destination;
    u8 pad6[6];
    s32 flag;
    u8 result;
} Output_00165EC0;

static inline u32 target_00165EC0(void *input, u8 mode) {
    Input_00165EC0 *p = input;
    if (mode == 1) {
        return (u16)(p->targets >> 16);
    }
    return *(u16 *)&p->targets;
}


s32 func_00165EC0(void *arg0, s32 arg1, void *arg2, u8 arg3) {
    extern s32 func_001670A0();
    extern s32 func_001676D0();
    extern void func_0027A090();
    Input_00165EC0 *input = arg0;
    Output_00165EC0 *output = arg2;
    s32 fallback;
    s32 source;
    s32 count;
    s32 target;
    s32 sourceY;
    s32 sourceX;
    s32 targetY;
    s32 targetX;
    Coord_00165EC0 *candidate;
    s32 flag;
    s32 i;
    s32 bestCost;
    s32 bestIndex;
    Coord_00165EC0 coords[12];
    s32 cost;
    s32 position;
    u32 low;
    u32 high;

    low = target_00165EC0(input, arg3);
    high = target_00165EC0(input, arg3);
    if (func_001DF540((u32)high >> 8, low & 0xFF) == 0) {
        func_0027B1B0(input, 1);
        return -1;
    }
    fallback = func_001670A0(input->position >> 8, input->position & 0xFF, input);
    source = func_001E1090(input->position >> 8, input->position & 0xFF);
    low = target_00165EC0(input, arg3);
    high = target_00165EC0(input, arg3);
    target = func_001E1090((u32)high >> 8, low & 0xFF);
    {
        s32 j = 0;
        Coord_00165EC0 *cursor = coords;
        do {
            cursor->x = cursor->y = 15;
            cursor++;
            j++;
        } while (j < 12);
    }
    cost = func_001DF540(input->position >> 8, input->position & 0xFF);
    sourceX = source & 0xFF;
    sourceY = source >> 8;
    if (func_002464F0(cost, sourceX, sourceY) == 0) {
        output->position = input->position;
        output->command = 6;
        output->destination = source;
        cost = func_00276CC0(sourceX, sourceY, arg1, 2, 0,
                           (u8)func_001676D0(arg1));
        if (cost >= func_001E0290(input->position >> 8, input->position & 0xFF, 0)) {
            output->result = func_0027E360(input->position >> 8, input->position & 0xFF,
                                         output->destination, 1, 1);
        } else {
            output->result = func_0027E360(input->position >> 8, input->position & 0xFF,
                                         output->destination, 0, 1);
        }
        func_0027B1B0(input, arg3);
    } else {
        position = input->position;
        cost = (u16)func_001676D0(arg1);
        func_0027A090(position >> 8, position & 0xFF, coords, sourceX, sourceY,
                     targetX = target & 0xFF, targetY = target >> 8,
                     target_00165EC0(input, arg3), 1, 30, cost);
        count = func_0027AFC0((u8 *)coords);
        bestIndex = 0xFF;
        if (count > 0) {
            flag = 0;
            bestCost = 0xFFFF;
            for (i = 0; i < count; i++) {
                if (func_00167570(input->position >> 8, input->position & 0xFF,
                                 sourceX, sourceY, targetX, targetY) == 1) {
                    bestIndex = i;
                    flag = 1;
                    coords[i].x = targetX;
                    coords[i].y = targetY;
                    i = count;
                } else {
                    candidate = &coords[i];
                    cost = func_00276CC0(candidate->x, candidate->y, arg1, 5, 0,
                                       (u8)func_001676D0(arg1));
                    if (cost < bestCost) {
                        bestCost = cost;
                        bestIndex = i;
                    } else if (cost == bestCost) {
                        Coord_00165EC0 *selected = &coords[bestIndex];
                        s32 oldMinY;
                        s32 oldMaxY;
                        s32 oldMinX;
                        s32 oldMaxX;
                        s32 newMinY;
                        s32 newMaxY;
                        s32 newMinX;
                        s32 newMaxX;
                        oldMinY = selected->y < targetY ? selected->y : targetY;
                        oldMaxY = targetY < selected->y ? selected->y : targetY;
                        oldMinX = selected->x < targetX ? selected->x : targetX;
                        oldMaxX = targetX < selected->x ? selected->x : targetX;
                        newMinY = candidate->y < targetY ? candidate->y : targetY;
                        newMaxY = targetY < candidate->y ? candidate->y : targetY;
                        newMinX = candidate->x < targetX ? candidate->x : targetX;
                        newMaxX = targetX < candidate->x ? candidate->x : targetX;
                        if ((newMaxX - newMinX) + (newMaxY - newMinY) <
                            (oldMaxX - oldMinX) + (oldMaxY - oldMinY)) {
                            bestCost = cost;
                            bestIndex = i;
                        }
                    }
                }
            }

        } else {
            output->position = input->position;
            output->command = 6;
            output->destination = source;
            output->flag = fallback;
            output->result = func_0027E360(input->position >> 8, input->position & 0xFF,
                                         output->destination, 0, 1);
            func_0027B1B0(input, arg3);
            return 0;
        }
        if (bestIndex != 0xFF) {
            output->position = input->position;
            output->command = 6;
            output->destination = (coords[bestIndex].y << 8) | coords[bestIndex].x;
            output->flag = flag;
            output->result = func_0027E360(input->position >> 8, input->position & 0xFF,
                                         output->destination, 0, 1);
        } else {
            output->position = input->position;
            output->command = 6;
            output->destination = source;
            output->flag = flag;
            output->result = func_0027E360(input->position >> 8, input->position & 0xFF,
                                         output->destination, 0, 1);
            func_0027B1B0(input, arg3);
            return 0;
        }
    }
    return 0;
}

typedef struct Coord_001664A0 {
    u8 x : 4;
    u8 y : 4;
} Coord_001664A0;

typedef struct Unit_001664A0 {
    u16 position;
    u8 pad2[6];
    union {
        u32 packed;
        u16 low;
    } target;
} Unit_001664A0;

typedef struct Output_001664A0 {
    u16 position;
    u8 kind;
    u8 pad3;
    u16 target;
    u8 pad6[6];
    s32 value;
    u8 flag;
} Output_001664A0;


static inline u32 target_001664A0(void *unit, s32 side) {
    return side == 1 ? (u32)(u16)(((Unit_001664A0 *)unit)->target.packed >> 16) : (u32)((Unit_001664A0 *)unit)->target.low;
}

static inline u32 minY_001664A0(void *unit, s32 side, u8 coord) {
    return coord < (target_001664A0(unit, side) >> 8) ? coord : (target_001664A0(unit, side) >> 8);
}

static inline u32 maxY_001664A0(void *unit, s32 side, u8 coord) {
    return (target_001664A0(unit, side) >> 8) < coord ? coord : (target_001664A0(unit, side) >> 8);
}

static inline u32 minX_001664A0(void *unit, s32 side, u8 coord) {
    return coord < (target_001664A0(unit, side) & 0xFF) ? coord : (target_001664A0(unit, side) & 0xFF);
}

static inline u32 maxX_001664A0(void *unit, s32 side, u8 coord) {
    return (target_001664A0(unit, side) & 0xFF) < coord ? coord : (target_001664A0(unit, side) & 0xFF);
}

s32 func_001664A0(void *arg0, s32 arg1, void *arg2, u8 arg3, u8 arg4) {
    extern s32 func_001670A0();
    extern s32 func_001676D0();
    extern s32 func_00276CC0();
    extern void func_00279230();
    extern s32 func_0027E360(s32, s32, s32, u8, s32);
    Coord_001664A0 coords[12];
    s32 initial;
    s32 cell;
    s32 count;

    initial = func_001E1090(((Unit_001664A0 *)arg0)->position >> 8, ((Unit_001664A0 *)arg0)->position & 0xFF);
    {
    s32 bestScore;
    s32 best;
    s32 side = arg3;
    Coord_001664A0 *candidate;
    s32 index;
    if (target_001664A0(arg0, side) == 0xFFFF) {
        if (initial == target_001664A0(arg0, side)) {
            ((Output_001664A0 *)arg2)->position = ((Unit_001664A0 *)arg0)->position;
            ((Output_001664A0 *)arg2)->kind = 6;
            ((Output_001664A0 *)arg2)->target = initial;
            ((Output_001664A0 *)arg2)->flag = func_0027E360(((Unit_001664A0 *)arg0)->position >> 8, ((Unit_001664A0 *)arg0)->position & 0xFF, ((Output_001664A0 *)arg2)->target, arg4, 1);
            ((Output_001664A0 *)arg2)->value = func_001670A0(((Unit_001664A0 *)arg0)->position >> 8, ((Unit_001664A0 *)arg0)->position & 0xFF, arg0);
            func_0027B1B0(arg0, arg3);
            return 0;
        }
    }

    if (func_001E2100(((Unit_001664A0 *)arg0)->position >> 8,
                      ((Unit_001664A0 *)arg0)->position & 0xFF, 4) != 0) {
        if ((func_001E0700(((Unit_001664A0 *)arg0)->position >> 8,
                          ((Unit_001664A0 *)arg0)->position & 0xFF) >> 5) == 1 ||
            (func_001E0700(((Unit_001664A0 *)arg0)->position >> 8,
                          ((Unit_001664A0 *)arg0)->position & 0xFF) >> 5) == 5) {
            func_001E1E70(((Unit_001664A0 *)arg0)->position >> 8,
                          ((Unit_001664A0 *)arg0)->position & 0xFF, 0, 1);
            ((Output_001664A0 *)arg2)->position = ((Unit_001664A0 *)arg0)->position;
            ((Output_001664A0 *)arg2)->kind = 14;
            return 0;
        }
    }

    candidate = coords;
    {
        s32 i = 0;
        Coord_001664A0 *entry = candidate;
        do {
            entry->x = entry->y = 0xF;
            i++;
            entry++;
        } while (i < 12);
    }

    cell = func_001E3790(target_001664A0(arg0, side) & 0xFF, ((u32)target_001664A0(arg0, side)) >> 8);
    if (cell < 0) {
        cell = 0xFFFF;
    }
    func_00279230(((Unit_001664A0 *)arg0)->position >> 8, ((Unit_001664A0 *)arg0)->position & 0xFF,
                 coords, initial & 0xFF, initial >> 8, target_001664A0(arg0, side) & 0xFF,
                 ((u32)target_001664A0(arg0, side)) >> 8, (u16)cell, 7);
    count = func_0027AFC0((u8 *)coords);
    {
        if (count > 0) {
        best = 0xFF;
        bestScore = 0xFFFF;
        for (index = 0; index < count; index++) {
                if (func_001E36E0(candidate->x, candidate->y) == 0) {
                    s32 score = func_00276CC0(candidate->x, candidate->y, arg1, 5, 0, (u8)func_001676D0(arg1));
                    if (score < bestScore) {
                        bestScore = score;
                        best = index;
                    } else if (score == bestScore) {
                        u32 bestMinY;
                        u32 bestMaxY;
                        u32 bestMinX;
                        u32 bestMaxX;
                        u32 currentMinY;
                        u32 currentMaxY;
                        u32 currentMinX;
                        u32 currentMaxX;
                        u32 bestY;
                        u32 bestX;
                        u32 currentY;
                        u32 currentX;
                        bestY = (u8)(&coords[best])->y;
                        bestMinY = minY_001664A0(arg0, side, bestY);
                        bestMaxY = maxY_001664A0(arg0, side, bestY);
                        bestX = (&coords[best])->x;
                        bestMinX = minX_001664A0(arg0, side, bestX);
                        bestMaxX = maxX_001664A0(arg0, side, bestX);
                        currentY = (u8)candidate->y;
                        currentMinY = minY_001664A0(arg0, side, currentY);
                        currentMaxY = maxY_001664A0(arg0, side, currentY);
                        currentX = candidate->x;
                        currentMinX = minX_001664A0(arg0, side, currentX);
                        currentMaxX = maxX_001664A0(arg0, side, currentX);
                        if ((currentMaxX - currentMinX) + (currentMaxY - currentMinY) < (bestMaxX - bestMinX) + (bestMaxY - bestMinY)) {
                            bestScore = score;
                            best = index;
                        }
                    }
                }
            candidate++;
        }
    } else {
        ((Output_001664A0 *)arg2)->position = ((Unit_001664A0 *)arg0)->position;
            ((Output_001664A0 *)arg2)->kind = 6;
            ((Output_001664A0 *)arg2)->target = initial;
            ((Output_001664A0 *)arg2)->flag = func_0027E360(((Unit_001664A0 *)arg0)->position >> 8, ((Unit_001664A0 *)arg0)->position & 0xFF, ((Output_001664A0 *)arg2)->target, arg4, 1);
            ((Output_001664A0 *)arg2)->value = func_001670A0(((Unit_001664A0 *)arg0)->position >> 8, ((Unit_001664A0 *)arg0)->position & 0xFF, arg0);
        func_0027B1B0(arg0, arg3);
        return 0;
    }

        if (best != 0xFF) {
            ((Output_001664A0 *)arg2)->position = ((Unit_001664A0 *)arg0)->position;
            ((Output_001664A0 *)arg2)->kind = 6;
            ((Output_001664A0 *)arg2)->target = (coords[best].y << 8) | coords[best].x;
            ((Output_001664A0 *)arg2)->flag = func_0027E360(((Unit_001664A0 *)arg0)->position >> 8, ((Unit_001664A0 *)arg0)->position & 0xFF, ((Output_001664A0 *)arg2)->target, arg4, 1);
            ((Output_001664A0 *)arg2)->value = func_001670A0(((Unit_001664A0 *)arg0)->position >> 8, ((Unit_001664A0 *)arg0)->position & 0xFF, arg0);
        } else {
            ((Output_001664A0 *)arg2)->position = ((Unit_001664A0 *)arg0)->position;
            ((Output_001664A0 *)arg2)->kind = 6;
            ((Output_001664A0 *)arg2)->target = initial;
            ((Output_001664A0 *)arg2)->flag = func_0027E360(((Unit_001664A0 *)arg0)->position >> 8, ((Unit_001664A0 *)arg0)->position & 0xFF, ((Output_001664A0 *)arg2)->target, arg4, 1);
            ((Output_001664A0 *)arg2)->value = func_001670A0(((Unit_001664A0 *)arg0)->position >> 8, ((Unit_001664A0 *)arg0)->position & 0xFF, arg0);
        }
        func_0027B1B0(arg0, arg3);
    }
    }
    return 0;
}

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

s32 func_00166EE0(s32);

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

s32 func_001670A0(s32 arg0, s32 arg1) {
    extern s32 func_001E1030();
    extern s32 func_0027D830();
    extern s32 func_0024CA40();
    u8 count;
    s32 card;
    s32 side;
    u32 *effect;
    s32 location;
    s32 i;
    s32 mask;
    s32 mask2;
    s32 j;
    s32 position;
    u32 fields;

    count = 0;
    card = func_001E1030();
    side = func_00250360(arg0, arg1);
    effect = func_001E0B70(arg0, arg1, 0);
    location = func_001E1090(arg0, arg1);
    if (func_001E2100(arg0, arg1, 4) != 0) {
        return 0;
    }
    switch (func_001E0700(arg0, arg1) >> 5) {
    case 5:
        if (func_00167670(func_00250360(arg0, arg1), card) == 1 &&
            func_001E22B0(location & 0xFF, location >> 8) != 9) {
            return 1;
        }
        break;
    case 1:
        if (func_0027D830(arg0, arg1, 0, 0, 6, 1) == 5) {
            return 2;
        }
        if (effect == NULL) {
            return 2;
        }
        fields = effect[0];
        switch (fields >> 8) {
        case 23:
            position = func_0024EC50(func_00272210(func_0024C7D0(
                func_0024CA40(0, 0, side, (fields >> 6) & 3, fields & 0x3F, 14),
                arg0, arg1), side), 0);
            if (position >= 0 && side != func_00250360(position >> 8, position & 0xFF)) {
                return 1;
            }
            break;
        case 4:
            switch (effect[1] >> 16) {
            case 18:
                mask = func_0024C7D0(func_0024C7D0(func_0024C7D0(
                    func_0024CA40(location & 0xFF, location >> 8, side,
                        (fields >> 6) & 3, fields & 0x3F, 18),
                    arg0, arg1), arg0, 0), arg0 == 0 ? 1 : 0, 0);
                for (i = 0; i < func_0024E910(mask); i++) {
                    position = func_0024EC50(mask, i);
                    if (position >= 0) {
                        if (side == func_00250360(position >> 8, position & 0xFF)) {
                            return 2;
                        }
                        count++;
                    }
                }
                if ((s32)(u8)count >= 0) {
                    return 1;
                }
                break;
            default:
                mask2 = func_00272210(func_0024C7D0(
                    func_0024CA40(0, 0, side, (fields >> 6) & 3, fields & 0x3F, 14),
                    arg0, arg1), side);
                for (j = 0; j < func_0024E910(mask2); j++) {
                    position = func_0024EC50(mask2, j);
                    if (position >= 0) {
                        if (side == func_00250360(position >> 8, position & 0xFF)) {
                            return 2;
                        }
                        count++;
                    }
                }
                if ((s32)(u8)count >= 0) {
                    return (u8)count;
                }
                break;
            }
            break;
        case 13:
            switch (func_001E1030(arg0, arg1)) {
            case 0x2C3:
                if (func_001DF470(side) < 2000) {
                    return 1;
                }
                break;
            case 0x2C9:
                return 1;
            case 0x2CA:
                if (func_001E0110(side == 0 ? 1 : 0) >= 3) {
                    return 1;
                }
                break;
            }
            break;
        case 24:
            if (func_0024E910(func_00272210(func_0024C7D0(
                func_0024CA40(0, 0, side, (fields >> 6) & 3, fields & 0x3F, 14),
                arg0, arg1), side)) >= 5) {
                return 1;
            }
            break;
        case 38:
            if (func_001DE6D0(side) == 0) {
                return 1;
            }
            break;
        }
        break;
    }
    return 2;
}

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

#pragma conditional_move off

s32 func_001678B0(void *work, void *arg1, s32 arg2) {
    extern s32 func_0016B0E0(s32);
    u16 *arg0 = work;
    s32 side;
    s32 found;
    s32 result;
    s32 index;

    side = func_001DE540();
    found = 0;
    if ((result = func_00167E80(arg0, side, (s32)arg1)) < 0) {
        return 0;
    }
    index = func_00276C80(arg0, result & 0xFFFF);
    if (index < 0) {
        return 0;
    }
    if ((result >> 16) == 1) {
        if (((arg0[index * 8 + 2] >> 8) & 0xFF) == 10) {
            func_0027B1B0(arg0 + index * 8, 1);
        } else {
            func_0027B1B0(arg0 + index * 8, 0);
        }
        return 1;
    }
    func_00167D30(arg0 + index * 8);
    switch ((arg0[index * 8 + 2] >> 8) & 0xFF) {
    case 5:
        if (func_001E2100(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            func_00169A10(arg0 + index * 8, side, arg1, 1);
            found = 1;
        }
        break;
    case 2:
        if (func_001E2100(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            if (func_00169FE0(arg0 + index * 8, side, arg1, 1) < 0) {
                func_0027B1B0(arg0 + index * 8, 1);
                return 1;
            }
            found = 1;
        }
        break;
    case 10:
        if (func_001687A0(arg0[index * 8], side, (s32)arg1) < 0) {
            func_0027B1B0(arg0 + index * 8, 1);
            *(u8 *)((u8 *)arg1 + 2) = 0xFF;
            *(s32 *)((u8 *)arg1 + 0xC) = 0;
        } else {
            func_0027B1B0(arg0 + index * 8, 1);
            found = 1;
        }
        break;
    case 6:
    case 16:
    case 15:
        if (func_001E2100(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            func_0016A5C0(arg0 + index * 8, side, arg1, 1, 0);
            found = 1;
        }
        break;
    case 9:
        func_0027D020(arg0 + index * 8, side, arg1, 1, 1, func_0016B0E0(side), 4, 1);
        found = 1;
        break;
    case 14:
        func_00276EC0(arg0 + index * 8, side, arg1);
        found = 1;
        break;
    default:
        found = 0;
        break;
    }
    if (found == 1) {
        return 1;
    }
    switch (arg0[index * 8 + 2] & 0xFF) {
    case 5:
        if (func_001E2100(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            func_00169A10(arg0 + index * 8, side, arg1, 0);
            found = 1;
        }
        break;
    case 2:
        if (func_001E2100(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            if (func_00169FE0(arg0 + index * 8, side, arg1, 0) < 0) {
                func_00169A10(arg0 + index * 8, side, arg1, 0);
            }
            found = 1;
        }
        break;
    case 10:
        if (func_001687A0(arg0[index * 8], side, (s32)arg1) < 0) {
            func_0027B1B0(arg0 + index * 8, 0);
            *(u8 *)((u8 *)arg1 + 2) = 0xFF;
            found = 1;
            *(s32 *)((u8 *)arg1 + 0xC) = 0;
        } else {
            func_0027B1B0(arg0 + index * 8, 0);
            found = 1;
        }
        break;
    case 6:
    case 16:
    case 15:
        if (func_001E2100(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            func_0016A5C0(arg0 + index * 8, side, arg1, 0, 0);
            found = 1;
        }
        break;
    case 9:
        func_0027D020(arg0 + index * 8, side, arg1, 0, 1, func_0016B0E0(side), 4, 1);
        found = 1;
        break;
    case 14:
        func_00276EC0(arg0 + index * 8, side, arg1);
        break;
    default:
        return 0;
    }
    if (found == 1) {
        return 1;
    }
    return 0;
}
#pragma conditional_move reset

typedef struct {
    u16 coordinates;
    u8 pad2[2];
    u16 state;
    u8 pad6[2];
    union {
        u32 word;
        struct {
            u16 low;
            u16 high;
        } halves;
    } data;
} Entry_00167D30;

s32 func_00167D30(void *arg0) {
    extern s32 func_0016B0E0(s32);
    Entry_00167D30 *entry = arg0;
    u16 coord;
    s32 slot;
    s32 kind;

    func_001E1090(entry->coordinates >> 8, entry->coordinates & 0xFF);
    slot = func_00250360(entry->coordinates >> 8, entry->coordinates & 0xFF);
    if (func_001DF540(entry->coordinates >> 8, entry->coordinates & 0xFF) != 0) {
        if (func_001E2100(entry->coordinates >> 8, entry->coordinates & 0xFF, 0) == 0) {
            coord = entry->coordinates;
            if (coord != 0xFFFF) {
                if ((coord & 0xFF) == 0) {
                    if (entry->data.word == -1) {
                        func_0027E210(entry, 3, 1, 1);
                    }
                } else {
                    kind = func_001E0700(coord >> 8, coord & 0xFF) >> 5;
                    switch (kind) {
                    case 0:
                        func_00168260(entry, 1);
                        break;
                    case 2:
                        func_0027CA50(entry, 4, 1, func_0016B0E0(slot) & 0xFF);
                        break;
                    default:
                        entry->state = 0x5FF;
                        break;
                    }
                }
                return 1;
            }
        }
    }
    return 0;
}

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

void func_00168530(u16 *arg0) {
    s32 owner;
    s32 result;
    s32 mode;
    s32 index;
    u16 id;

    id = arg0[0];
    owner = func_00250360(id >> 8, id & 0xFF);
    id = arg0[0];
    result = func_001E1090(id >> 8, id & 0xFF);
    mode = (arg0[2] >> 8) & 0xFF;
    if (mode == 0x10) {
        if ((result >> 8) == 6) {
            arg0[2] = 0xFFF;
            *(u32 *)(arg0 + 4) = ((result & 0xFF) << 16) | arg0[4];
        } else {
            arg0[2] = 0x10FF;
            *(u32 *)(arg0 + 4) = (((result & 0xFF) | 0x600) << 16) | arg0[4];
        }
    } else {
        if (mode == 0xF) {
            if ((result >> 8) == 0) {
                arg0[2] = 0x10FF;
                *(u32 *)(arg0 + 4) = (((result & 0xFF) | 0x600) << 16) | arg0[4];
            } else {
                arg0[2] = 0xFFF;
                *(u32 *)(arg0 + 4) = ((result & 0xFF) << 16) | arg0[4];
            }
        } else if ((result >> 8) < 4) {
            if ((result >> 8) == 0) {
                arg0[2] = 0x10FF;
                *(u32 *)(arg0 + 4) = ((result & 0xFF) << 16) | arg0[4];
            } else {
                index = result & 0xFF;
                if (index == 3) {
                    arg0[2] = 0x6FF;
                    *(u32 *)(arg0 + 4) = arg0[4] | 0x30000;
                } else if (index > 3) {
                    arg0[2] = 0x6FF;
                    *(u32 *)(arg0 + 4) = arg0[4] | 0x60000;
                } else {
                    arg0[2] = 0x6FF;
                    *(u32 *)(arg0 + 4) = arg0[4];
                }
            }
        } else if (func_001E36E0(3, 3) == 0) {
            arg0[2] = 0x6FF;
            *(u32 *)(arg0 + 4) = arg0[4] | 0x03030000;
        } else if (func_001E36E0(2, 3) == 0) {
            arg0[2] = 0x6FF;
            *(u32 *)(arg0 + 4) = arg0[4] | 0x03020000;
        } else if (func_001E36E0(2, 3) == 0) {
            arg0[2] = 0x6FF;
            *(u32 *)(arg0 + 4) = arg0[4] | 0x03040000;
        } else {
            arg0[2] = 0x6FF;
            *(u32 *)(arg0 + 4) = arg0[4] | (func_001E1090((owner == 0) ? 1 : 0, 0) << 16);
        }
    }
}

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

s32 func_00168A30(s32 arg0, void *arg1) {
    extern s32 func_00278890();
    s32 cards[8];
    u8 buffer[32];
    u8 first;
    u8 second;

    first = (u8)func_00278890(arg0, 0);
    second = (u8)func_00278890(arg0, 1);
    if (arg1 == NULL) {
        return -1;
    }
    func_0026FD30(arg0, cards);
    if (first == 5) {
        if (func_00168E00(arg0, buffer, arg1, 0x3E7) >= 0) {
            return 1;
        }
        return -1;
    }
    if (second == 5) {
        s32 i = 0;
        s32 *p;
        if (i < func_0026FE20(arg0)) {
            p = cards;
            do {
                if ((func_0026FCE0(*p) >> 5) == 0 && func_0026FB10(arg0, *p) == 1) {
                    func_001DCD70(arg1, cards[i]);
                    return 0;
                }
                p++;
                i++;
            } while (i < func_0026FE20(arg0));
        }
        return -1;
    }
    if (func_0016B0F0(arg0) == 1) {
        if (func_00168D10(arg0, buffer, arg1, 0x2BB) >= 0) {
            return 2;
        }
    }
    if (func_00168D10(arg0, buffer, arg1, 0x339) >= 0) {
        return 2;
    }
    if (func_001DE5C0(arg0) < 4) {
        if (func_00168D10(arg0, buffer, arg1, 0x2EC) >= 0) {
            return 2;
        }
        if (func_00168D10(arg0, buffer, arg1, 0xE0) >= 0) {
            return 2;
        }
        if (func_00168D10(arg0, buffer, arg1, 0x16C) >= 0) {
            return 2;
        }
    }
    {
        s32 *p;
        s32 i = 0;
        s32 result;
        if (i < func_0026FE20(arg0)) {
            p = cards;
            do {
                if ((func_0026FCE0(*p) >> 5) == 0 && func_0026FB10(arg0, *p) == 1) {
                    func_001DCD70(arg1, cards[i]);
                    return 0;
                }
                p++;
                i++;
            } while (i < func_0026FE20(arg0));
        }
        result = func_00168E00(arg0, buffer, arg1, 0x3E7);
        if (result >= 0) {
            return result;
        }
    }
    return -1;
}

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

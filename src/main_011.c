#include "common.h"

typedef struct {
    u16 id;
    u8 values[5];
} Info_00144630;

void func_00144630(s32 arg0, void *arg1, s32 *arg2) {
    Info_00144630 *info = arg1;
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
                if (card != 0x3E7 && func_00144810(card) == 0 && level >= func_0026FA80(card, arg0)) {
                    cost = func_0026FBB0(card);
                    if ((cost & 0xFFFF) + (cost >> 16) * 2 < 0xAF1 && func_0026FC10(card) == 2 &&
                        (u16)func_002789F0(info->id, (u16)card) == 0x3E7) {
                        func_00278D20(info->values, buf[i]);
                    }
                }
            }
        }
    }
}

s32 func_00144810(s32 arg0) {
    if ((func_0026FCE0(arg0) >> 5) != 0) {
        return 1;
    }
    return (func_0026FC10(arg0) != 0) ? 1 : 0;
}

typedef struct {
    u8 pad0[6];
    u8 slot[5];
} Obj1_00144860;

typedef struct {
    u8 pad0[0x3C];
    u16 id;
    u8 f3E;
} Obj2_00144860;

s32 func_00144860(s32 arg0, void *arg1, void *arg2) {
    Obj1_00144860 *o1 = arg1;
    Obj2_00144860 *o2 = arg2;
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
    return o2->f3E >> 5;
}

INCLUDE_ASM("asm/nonmatchings/main_011", func_00144A60);

INCLUDE_ASM("asm/nonmatchings/main_011", func_00144EC0);

INCLUDE_ASM("asm/nonmatchings/main_011", func_00145400);

INCLUDE_ASM("asm/nonmatchings/main_011", func_001459E0);

s32 func_001461C0(s32 arg0) {
    if (func_001DF470(arg0) > 2000) {
        if (func_001E0150(arg0) >= 4) {
            return 0;
        }
        return 0;
    }
    return 0;
}

s32 func_00146220(s32 arg0, s32 arg1) {
    s32 pos;
    s32 kind;
    s32 slot;
    u8 count;
    s32 i;
    s32 list;
    s32 pair;
    extern s32 func_001E1030();

    pos = func_001E1090(arg0, arg1);
    kind = func_001E1030(arg0, arg1);
    slot = func_00250360(arg0, arg1);
    count = 0;
    if (func_001E2100(arg0, arg1, 4) != 0) {
        return 0;
    }
    switch (kind) {
    case 0x145:
        list = func_0024CA40(0, 0, arg0, 2, 0x34, 0xE);
        for (i = 0; i < func_0024E910(list); i++) {
            pair = func_0024EC50(list, i);
            if (func_001E2100(pair >> 8, pair & 0xFF, 3) != 0) {
                count++;
            }
        }
        if (count >= 3) {
            return 1;
        }
        break;
    case 0xC0:
        if (func_0024E910(func_0024CA40(0, 0, arg0, 1, 5, 0xE)) >= 3) {
            return 1;
        }
        break;
    case 0x2DB:
    case 0x2EF:
        if (func_0027D830(arg0, arg1, 0, 0, 6, 0) == 5) {
            return 2;
        }
        if (func_001465A0(slot) == 1) {
            return 1;
        }
        break;
    case 0x34E:
        if (func_0027D830(arg0, arg1, 0, 0, 6, 0) == 5) {
            return 2;
        }
        if (func_001466A0(func_00250360(arg0, arg1), 0x34E) == 1 &&
            func_001E22B0(pos & 0xFF, pos >> 8) != 9) {
            return 1;
        }
        break;
    }
    return 2;
}

static inline s32 max_001464A0(s32 a, s32 b) {
    if (a < b) {
        return b;
    }
    return a;
}

s32 func_001464A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 min_y;
    s32 min_x;

    min_y = arg3 < arg5 ? arg3 : arg5;
    arg5 = max_001464A0(arg5, arg3);
    min_x = arg2 < arg4 ? arg2 : arg4;
    arg4 = max_001464A0(arg4, arg2);

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

INCLUDE_ASM("asm/nonmatchings/main_011", func_001465A0);

s32 func_001466A0(s32 arg0, s32 arg1) {
    s32 data[4];
    s32 index;
    s32 mask;
    s32 low;
    s32 high;
    s32 pair;
    s32 value;

    func_00254C90(data, *(s32 *)((u8 *)func_0026FC90(arg1, 0) + 4));
    if ((mask = func_00254890(data, arg0)) < 0) {
        return 0;
    }
    for (index = 0; index < func_0024E910(mask); index++) {
        pair = func_0024EC50(mask, index);
        high = pair >> 8;
        low = pair & 0xFF;
        value = func_001E1090(high, low);
        if (func_002509E0(high, low, value & 0xFF, value >> 8) >= 0x9C4) {
            return 0;
        }
    }
    return 1;
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
} Req_00146790;

typedef struct {
    u8 pad0[0x160];
    u16 list[32];    /* 0x160 */
    u8 idx : 5;      /* 0x1A0 */
    u8 pad1A0 : 3;
    u8 pad1A1;
    u16 count;       /* 0x1A2 */
} Work_00146790;

s32 func_001424B0(void *, void *, s32);
s32 func_00276290(void *, void *, s32);

s32 func_00146790(s32 arg0, void *arg1) {
    Req_00146790 req;
    Work_00146790 *w;
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
        if (func_001424B0(w, &req, arg0) == 0) {
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

INCLUDE_ASM("asm/nonmatchings/main_011", func_00146960);

s32 func_00146EC0(void *arg0, s32 arg1) {
    extern s32 func_0014B390();
    s32 temp_s0;

    func_001E1090(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF);
    temp_s0 = func_00250360(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF);
    if (func_001DF540(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF) != 0) {
        if (func_001E2100(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF, 0) == 0) {
            if (*(u16 *)arg0 != 0xFFFF) {
                if ((*(u16 *)arg0 & 0xFF) == 0) {
                    if (*(s32 *)((u8 *)arg0 + 8) == -1) {
                        if (func_0027BBC0(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF, 0) == 1) {
                            if (func_001DE6D0(*(u16 *)arg0 >> 8) == 1) {
                                *(s16 *)((u8 *)arg0 + 4) = 0x50A;
                            } else {
                                *(s16 *)((u8 *)arg0 + 4) = 0x5FF;
                            }
                        } else {
                            if (func_001DE6D0(*(u16 *)arg0 >> 8) == 1) {
                                *(s16 *)((u8 *)arg0 + 4) = 0xA05;
                            } else {
                                *(s16 *)((u8 *)arg0 + 4) = 0x5FF;
                            }
                        }
                    }
                } else {
                    switch (func_001E0700(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF) >> 5) {
                    case 0:
                        if (func_0014B390(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF) == 1) {
                            func_00147830(arg0);
                        } else if (func_002507D0(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF) == 1) {
                            func_00147AC0(arg0);
                        } else {
                            func_001474F0(arg0);
                        }
                        break;
                    case 2:
                        func_0027CA50(arg0, 5, 0, (u8)func_0014B330(temp_s0));
                        break;
                    case 1:
                    case 3:
                        func_00147B90(arg0, arg1);
                        break;
                    default:
                        *(s16 *)((u8 *)arg0 + 4) = 0x5FF;
                        break;
                    }
                }
                return 1;
            }
        }
    }
    return 0;
}

s32 func_00147100(u16 *arg0, s32 arg1, s32 arg2, void *arg3) {
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
    func_00146EC0(arg0 + idx * 8, arg2);
    if (((arg0[idx * 8 + 2] >> 8) & 0xFF) == 10) {
        if (func_001DE6D0(arg1) == 1 && func_00148020(pos, arg1, arg3) >= 0) {
            return pos | 0x10000;
        }
        if (func_0027B9B0(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (func_001E2100(arg1, 0, 0) == 0) {
        if (func_0027B9B0(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (func_001DE6D0(arg1) == 1 && func_00148020(pos, arg1, arg3) >= 0) {
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

INCLUDE_ASM("asm/nonmatchings/main_011", func_001474F0);

void func_001477D0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, u16 arg9, s32 arg10, s32 arg11, u8 arg12, s32 arg13) {
    func_0027DE20(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, 0, 0x960, arg13);
}

INCLUDE_ASM("asm/nonmatchings/main_011", func_00147830);

INCLUDE_ASM("asm/nonmatchings/main_011", func_00147AC0);

INCLUDE_ASM("asm/nonmatchings/main_011", func_00147B90);

s32 func_00147E00(s32 arg0, s32 arg1, s32 arg2) {
    if (arg2 < 3) {
        return (arg1 >= 3) ? 0x306 : 0x300;
    }
    return func_001E1090((arg0 == 0) ? 1 : 0, 0);
}

s32 func_00147E50(s32 arg0, s32 arg1) {
    s32 var_s0;

    var_s0 = 0;
loop_1:
    if (((arg1 << 8) | arg0) == func_00147EB0(var_s0)) {
        return 1;
    }
    var_s0 += 1;
    if (var_s0 >= 5) {
        return 0;
    }
    goto loop_1;
}

s32 func_00147EB0(s32 arg0) {
    switch (arg0) {
    case 0:
        return 0x403;
    case 1:
        return 0x402;
    case 2:
        return 0x404;
    case 3:
        return 0x401;
    case 4:
        return 0x405;
    default:
        return -1;
    }
}

s32 func_00147F40(void) {
    s32 i;
    s32 value;
    s32 result;

    i = 0;
    do {
        value = func_00147EB0(i);
        if (((func_001E36E0(value & 0xFF, value >> 8) == 0) ? 1 : 0) == 1) {
            switch (i) {
            case 0:
                result = 0x403;
                break;
            case 1:
                result = 0x402;
                break;
            case 2:
                result = 0x404;
                break;
            case 3:
                result = 0x401;
                break;
            case 4:
                result = 0x405;
                break;
            default:
                result = -1;
                break;
            }
            return result;
        }
        i++;
    } while (i < 5);
    return -1;
}

typedef struct {
    s16 card;
    u8 f2;
    u8 pad3;
    s16 f4;
    u8 pad6[6];
    s32 fC;
} Act_00148020;

typedef struct {
    u8 pad0[0x3C];
    u16 id;
    u8 pad3E[0x22];
} Card_00148020;

s32 func_001482F0(s32 arg0, void *arg1);
s32 func_001491B0(s32 arg0, u8 arg1, void *arg2, s32 arg3);
s32 func_00276F10(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8,
                  s32 arg9);

s32 func_00148020(s32 arg0, s32 arg1, void *arg2) {
    extern s32 func_00278890(s32, s32);
    Act_00148020 *act = arg2;
    Card_00148020 buf;
    s32 res;
    s32 type;
    s32 card;
    s32 r;

    act->card = arg0;
    if (func_001DE6D0(arg1) == 0) {
        return -1;
    }
    if (func_00278890(arg1, 0) == 5 && func_00278890(arg1, 1) == 5) {
        return -1;
    }
    type = func_001482F0(arg1, &buf);
    if (type < 0) {
        return -1;
    }
    act->f2 = 10;
    act->fC = 0;
    card = func_001E1090(arg0 >> 8, arg0 & 0xFF);
    if (type == 0) {
        if (func_00148B60(arg1, arg2, &buf) >= 0) {
            res = func_00276F10(&buf, card & 0xFF, card >> 8, arg1 == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, func_0014B330(arg1));
            if (res < 0) {
                if (func_001E0150(arg1) < 4) {
                    r = func_001491B0(arg1, type, &buf, res);
                    if (r < 0) {
                        return -1;
                    }
                    act->f4 = r;
                    return 1;
                }
            } else {
                r = func_001491B0(arg1, type, &buf, res);
                if (r < 0) {
                    return -1;
                }
                act->f4 = r;
                return 1;
            }
        }
    } else {
        res = func_00276F10(&buf, card & 0xFF, card >> 8, arg1 == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, func_0014B330(arg1));
    }
    if (type == 2) {
        func_00148F80(arg1, arg2, &buf);
        r = func_001491B0(arg1, type, &buf, res);
        if (r < 0) {
            return -1;
        }
        act->f4 = r;
        return 1;
    } else if (type == 3) {
        func_00148630(arg1, arg2, &buf);
        r = func_001491B0(arg1, type, &buf, res);
        if (r < 0) {
            return -1;
        }
        act->f4 = r;
        return 1;
    } else {
        if (func_00148960(arg1, arg2, &buf, buf.id) < 0) {
            return -1;
        }
        r = func_001491B0(arg1, type, &buf, res);
        if (r < 0) {
            return -1;
        }
        act->f4 = r;
        return 1;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_011", func_001482F0);

typedef struct {
    u8 pad0[6];
    u8 slot[5];
} Obj1_00148630;

typedef struct {
    u8 pad0[0x38];
    s16 attack;
    s16 defense;
} Obj2_00148630;

s64 func_002493A0(s32);

s32 func_00148630(s32 arg0, void *arg1, void *arg2) {
    Obj2_00148630 *o2 = arg2;
    Obj1_00148630 *o1 = arg1;
    s32 list[8];
    s32 i;
    s32 found;
    u8 k;

    func_0026FD30(arg0, list);
    for (i = 0, found = 0; i < func_0026FE20(arg0); i++) {
        if (list[i] == 0x31D) {
            found = 1;
            o1->slot[0] = i;
        }
    }
    if (found == 0) {
        return -1;
    }
    for (i = 0, found = 0; i < func_0026FE20(arg0); i++) {
        if (list[i] == 0x110 && func_0026FB10(arg0, list[i]) == 1) {
            o1->slot[1] = i;
            found = 1;
        }
    }
    if (found == 0) {
        return -1;
    }
    k = 2;
    func_001DCD70(o2, 0x111);
    for (i = 0; i < func_0026FE20(arg0); i++) {
        if (i != o1->slot[0] && i != o1->slot[1]) {
            if (func_00248F60(0x111, list[i]) >= 0 && (func_0026FCE0(list[i]) >> 5) == 2) {
                if (list[i] != 0x31B && list[i] != 0x31C) {
                    o1->slot[k] = i;
                    k++;
                    o2->attack += (s16)func_002493A0(list[i]);
                    o2->defense += (s16)func_002493A0(list[i]);
                }
            }
        }
    }
    return 1;
}

s32 func_00148870(s32 arg0, void *arg1, void *arg2, s32 arg3) {
    s32 entries[8];
    s32 index;
    s32 *entry;

    func_0026FD30(arg0, entries);
    index = 0;
    if (index < func_0026FE20(arg0)) {
        entry = entries;
        do {
            if (((arg3 & 0xFFFF) == *entry) && (func_0026FB10(arg0, *entry) == 1)) {
                *((s8 *)arg1 + 6) = index;
                func_001DCD70(arg2, entries[index]);
                return func_0026FCE0(entries[index]) >> 5;
            }
            entry++;
            index++;
        } while (index < func_0026FE20(arg0));
    }
    return -1;
}

s32 func_00148960(s32 arg0, u8 *arg1, void *arg2, s32 arg3) {
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

typedef struct Info_00148B60 {
    u8 pad00[8];
    u16 x;
    s16 y;
} Info_00148B60;

typedef struct Sprite_00148B60 {
    Info_00148B60 *info;
    u8 pad04[0x34];
    s16 x;
    s16 y;
} Sprite_00148B60;

u16 *func_00278A90(s32, u16 *, s32, s32, s32, s16 *, s16 *);
s32 func_00278F10(s32, u16 *, s32, s32);

s32 func_00148B60(s32 arg0, u8 *arg1, void *arg2) {
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
                            func_00148D40(arg0, *node, entries);
                            func_00278DD0((u8 *)*node + 2, arg1 + 6);
                            func_001DCD70(arg2, **node);
                            ((Sprite_00148B60 *)arg2)->x = (value >> 16) - (((Sprite_00148B60 *)arg2)->info->x & 0x1FFF);
                            ((Sprite_00148B60 *)arg2)->y = (value & 0xFFFF) - (((Sprite_00148B60 *)arg2)->info->y & 0x1FFF);
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
} Info_00148D40;

void func_00148D40(s32 arg0, void *arg1, s32 *arg2) {
    Info_00148D40 *info = arg1;
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
                if (card != 0x3E7 && func_00148F20(card) == 0 && level >= func_0026FA80(card, arg0)) {
                    cost = func_0026FBB0(card);
                    if ((cost & 0xFFFF) + (cost >> 16) * 2 < 0x1069 && func_0026FC10(card) == 2 &&
                        (u16)func_002789F0(info->id, (u16)card) == 0x3E7) {
                        func_00278D20(info->values, buf[i]);
                    }
                }
            }
        }
    }
}

s32 func_00148F20(s32 arg0) {
    if ((func_0026FCE0(arg0) >> 5) != 0) {
        return 1;
    } else if (func_0026FC10(arg0) == 1) {
        return 1;
    } else {
        return 0;
    }
}

s64 func_002493A0(s32);

typedef struct {
    u8 pad0[6];
    u8 slot[5];
} Obj1_00148F80;

typedef struct {
    u8 pad0[0x38];
    s16 f38;
    s16 f3A;
    u16 id;
} Obj2_00148F80;

s32 func_00148F80(s32 arg0, void *arg1, void *arg2) {
    Obj1_00148F80 *o1 = arg1;
    Obj2_00148F80 *o2 = arg2;
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
                        o2->f38 += (s16)func_002493A0(list[i]);
                        o2->f3A += (s16)func_002493A0(list[i]);
                    }
                }
            }
        }
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_011", func_001491B0);

INCLUDE_ASM("asm/nonmatchings/main_011", func_00149690);

INCLUDE_ASM("asm/nonmatchings/main_011", func_00149C60);

INCLUDE_ASM("asm/nonmatchings/main_011", func_0014A240);

typedef struct {
    u8 low : 4;
    u8 high : 4;
} Nibbles_0014AAB0;

typedef struct {
    u16 pos;
} Unit_0014AAB0;

typedef struct {
    u16 pos;
    u8 kind;
    u8 pad3;
    u16 target;
    u8 pad6[6];
    s32 flag;
    u8 result;
} Out_0014AAB0;

s32 func_0027DBC0(s32, s32, s32);
void func_001E1E70(s32, s32, s32, s32);
s32 func_00149690(void *, s32, void *, u8);

s32 func_0014AAB0(void *arg0, s32 arg1, void *arg2, u8 arg3) {
    Unit_0014AAB0 *unit = arg0;
    s32 pos;
    s32 card;
    s32 col;
    u16 row;
    Out_0014AAB0 *out = arg2;
    Nibbles_0014AAB0 entries[12];
    s32 i;
    Nibbles_0014AAB0 *entry;

    pos = func_001E1090(unit->pos >> 8, unit->pos & 0xFF);
    entry = entries;
    i = 0;
    do {
        entry->low = entry->high = 15;
        entry++;
        i++;
    } while (i < 12);
    card = func_0014B490(arg1);
    if (func_001E22B0(pos & 0xFF, pos >> 8) == 9) {
        card = -1;
    }
    if (func_0027D830(unit->pos >> 8, unit->pos & 0xFF, 0, 0, 6, 0) == 5) {
        card = -1;
    }
    if (card >= 0) {
        row = card >> 16;
        col = func_0027DBC0(row, card & 0xFF, 1);
        out->pos = unit->pos;
        out->kind = 12;
        out->result = func_0027E360(unit->pos >> 8, unit->pos & 0xFF, out->target, 1, 0);
        out->flag = 1;
        out->target = (row << 8) | col;
        func_0027B1B0(unit, arg3);
        return 0;
    }
    if (func_001E2100(unit->pos >> 8, unit->pos & 0xFF, 4) != 0) {
        func_001E1E70(unit->pos >> 8, unit->pos & 0xFF, 0, 1);
        out->pos = unit->pos;
        out->kind = 14;
        return 0;
    }
    return func_00149690(unit, arg1, out, arg3);
}

s32 func_0014ACA0(void) {
    s32 player;
    s32 i;
    s32 list;
    s32 pair;

    player = func_001DE540();
    list = func_0024CA40(0, 0, player, 1, 0x111001C, 0xE);
    for (i = 0; i < func_0024E910(list); i++) {
        pair = func_0024EC50(list, i);
        if (func_001E0290(pair >> 8, pair & 0xFF, 0) > func_001E0290(pair >> 8, pair & 0xFF, 1)) {
            return 1;
        }
    }
    list = func_0024CA40(0, 0, player, 1, 0x1E001C, 0xE);
    for (i = 0; i < func_0024E910(list); i++) {
        pair = func_0024EC50(list, i);
        if (func_001E0290(pair >> 8, pair & 0xFF, 0) > func_001E0290(pair >> 8, pair & 0xFF, 1)) {
            return 1;
        }
    }
    return func_0024CA40(0, 0, player, 1, 0xB001C, 0xE) != 0 ? 1 : 0;
}

s32 func_0014AE60(s32 arg0, s32 arg1) {
    s32 kind;
    s32 pos;
    s32 slot;
    u32 *card;
    s32 found;

    kind = func_001E1030();
    pos = func_001E1090(arg0, arg1);
    slot = func_00250360(arg0, arg1);
    card = func_001E0B70(arg0, arg1, 0);
    if (func_001E2100(arg0, arg1, 4) != 0) {
        return 0;
    }
    switch (func_001E0700(arg0, arg1) >> 5) {
    case 0:
        switch (kind) {
        case 0x123:
            if (func_0024E910(func_0024CA40(0, 0, arg0, 1, 6, 0xE)) >= 3) {
                return 1;
            }
            break;
        case 0x110:
        case 0x111:
            if (func_0024E910(func_0024CA40(0, 0, arg0, 1, 0x1E001C, 0xE)) > 0) {
                return 1;
            }
            break;
        }
        return 2;
    case 5:
        if (func_0027D830(arg0, arg1, 0, 0, 6, 0) == 5) {
            return 2;
        }
        if (func_0014B240(func_00250360(arg0, arg1), kind) == 1 &&
            func_001E22B0(pos & 0xFF, pos >> 8) != 9) {
            return 1;
        }
        break;
    case 1:
        if (func_0027D830(arg0, arg1, 0, 0, 6, 0) == 5) {
            return 2;
        }
        if (card == NULL) {
            return 2;
        }
        switch (*card >> 8) {
        case 0xD:
            return 1;
        case 2:
            found = func_0027C770(func_001DF540(arg0, arg1), pos & 0xFF, pos >> 8, 2, 6, 2);
            if (found >= 0 && found == pos) {
                return 1;
            }
            break;
        case 4:
            if (func_0014B3E0(arg0, pos & 0xFF, pos >> 8) == 1) {
                return 1;
            }
            break;
        }
        break;
    default:
        return 2;
    }
    return 2;
}

static inline s32 max_0014B140(s32 a, s32 b) {
    if (a < b) {
        return b;
    }
    return a;
}

static inline s32 check_0014B140(s32 status) {
    if (status != 1) {
        return 0;
    }
    return 1;
}

s32 func_0014B140(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 min_y;
    s32 min_x;

    min_y = arg3 < arg5 ? arg3 : arg5;
    arg5 = max_0014B140(arg5, arg3);
    min_x = arg2 < arg4 ? arg2 : arg4;
    arg4 = max_0014B140(arg4, arg2);
    if ((arg4 - min_x) + (arg5 - min_y) != 2) {
        return 0;
    }
    if (func_001DF540(arg0, arg1) == 0) {
        return 0;
    }
    if (func_001E2100(arg0, arg1, 0) == 0) {
        return check_0014B140(func_0024DF00(func_001E22B0(arg2, arg3), arg0, arg1));
    }
    return 0;
}

s32 func_0014B240(s32 arg0, s32 arg1) {
    s32 sp50[4];
    s32 i;
    s32 mask;
    s32 low;
    s32 high;
    s32 value;
    s32 result;

    func_00254C90(sp50, *(s32 *)((u8 *)func_0026FC90(arg1, 0) + 4));
    if ((mask = func_00254890(sp50, arg0)) < 0) {
        return 0;
    }
    for (i = 0; i < func_0024E910(mask); i++) {
        value = func_0024EC50(mask, i);
        high = value >> 8;
        low = value & 0xFF;
        result = func_001E1090(high, low);
        if (func_002509E0(high, low, result & 0xFF, result >> 8) >= 0x960) {
            return 0;
        }
    }
    return 1;
}

s32 func_0014B330(s32 arg0) {
    return func_001DF470(arg0) > 0x5DC
        ? (func_001E0150(arg0) >= 4 ? 0x2EE : 0x5DC)
        : 0x7D0;
}

s32 func_0014B390(void) {
    s32 value;

    value = func_001E1030();
    if (value == 0x111 || value == 0x1E || value == 0xB) {
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_011", func_0014B3E0);

s32 func_0014B490(s32 arg0) {
    extern s32 func_001DEE50(s32);
    s32 i;

    if (func_001E0150(arg0) >= 5) {
        return -1;
    }
    if (func_0027DD20(arg0, 3, 0x111) > 0 || func_0027DD20(arg0, 3, 0x1E) > 0 ||
        func_0027DD20(arg0, 3, 0xB) > 0) {
        for (i = 0; i < func_001DEE50(arg0); i++) {
            if (func_001DEE00(arg0, i) == 0xB) {
                return (arg0 << 16) | i;
            }
        }
        for (i = 0; i < func_001DEE50(arg0 == 0 ? 1 : 0); i++) {
            if (func_001DEE00(arg0 == 0 ? 1 : 0, i) == 0xB) {
                return ((arg0 == 0 ? 1 : 0) << 16) | i;
            }
        }
        for (i = 0; i < func_001DEE50(arg0); i++) {
            if (func_001DEE00(arg0, i) == 0x1E) {
                return (arg0 << 16) | i;
            }
        }
        for (i = 0; i < func_001DEE50(arg0 == 0 ? 1 : 0); i++) {
            if (func_001DEE00(arg0 == 0 ? 1 : 0, i) == 0x1E) {
                return ((arg0 == 0 ? 1 : 0) << 16) | i;
            }
        }
        for (i = 0; i < func_001DEE50(arg0); i++) {
            if (func_001DEE00(arg0, i) == 0x111) {
                return (arg0 << 16) | i;
            }
        }
        for (i = 0; i < func_001DEE50(arg0 == 0 ? 1 : 0); i++) {
            if (func_001DEE00(arg0 == 0 ? 1 : 0, i) == 0x111) {
                return ((arg0 == 0 ? 1 : 0) << 16) | i;
            }
        }
    }
    return -1;
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
} Req_0014B730;

typedef struct {
    u8 pad0[0x160];
    u16 list[32];    /* 0x160 */
    u8 idx : 5;      /* 0x1A0 */
    u8 pad1A0 : 3;
    u8 pad1A1;
    u16 count;       /* 0x1A2 */
} Work_0014B730;

s32 func_00146960(void *, void *, s32);
s32 func_00276290(void *, void *, s32);

s32 func_0014B730(s32 arg0, void *arg1) {
    Req_0014B730 req;
    Work_0014B730 *w;
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
        if (func_00146960(w, &req, arg0) == 0) {
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

INCLUDE_ASM("asm/nonmatchings/main_011", func_0014B900);

INCLUDE_ASM("asm/nonmatchings/main_011", func_0014BDE0);

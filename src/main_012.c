#include "common.h"

s32 func_0014BFD0(u16 *arg0, s32 arg1, s32 arg2) {
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
    func_0014BDE0(arg0 + idx * 8);
    if (((arg0[idx * 8 + 2] >> 8) & 0xFF) == 10) {
        if (func_001DE6D0(arg1) == 1 && func_0014CBA0(pos, arg1, arg2) >= 0) {
            return pos | 0x10000;
        }
        if (func_0027B9B0(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (func_001E2100(arg1, 0, 0) == 0) {
        if (func_0027B9B0(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (func_001DE6D0(arg1) == 1 && func_0014CBA0(pos, arg1, arg2) >= 0) {
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

INCLUDE_ASM("asm/nonmatchings/main_012", func_0014C3B0);

void func_0014C6C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28) {
    func_0027DE20(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
        arg_sp0, arg_sp8, arg_sp10, arg_sp18, arg_sp20, 0, 2500, arg_sp28);
}

INCLUDE_ASM("asm/nonmatchings/main_012", func_0014C720);

typedef struct Entry_0014C870 {
    u16 position;
    u16 unk2;
    u16 state;
    u16 unk6;
    u32 data;
} Entry_0014C870;

s32 func_0027C770(s32, s32, s32, s32, s32, s32);

void func_0014C870(void *arg0) {
    Entry_0014C870 *entry = arg0;
    u32 *card;
    s32 position;
    s32 result;

    func_00250360((s32)entry->position >> 8, entry->position & 0xFF);
    card = func_00250740((s32)entry->position >> 8, entry->position & 0xFF, 0);
    position = func_001E1090((s32)entry->position >> 8, entry->position & 0xFF);
    if (card == NULL) {
        entry->state = 0x5FF;
    } else {
        switch (*card >> 8) {
        case 2:
            if (func_0014F3A0() == 1) {
                result = func_0027C770(func_001DF540((s32)entry->position >> 8, entry->position & 0xFF),
                                      position & 0xFF, position >> 8, 4, 9, 2);
                if (result >= 0) {
                    entry->state = 0x6FF;
                    entry->data = (result << 16) | (entry->data & 0xFFFF);
                }
            }
            break;
        }
        entry->state = 0x5FF;
    }
}

s32 func_0014C970(s32 arg0, s32 arg1) {
    s32 var_s0;

    var_s0 = 0;
loop_1:
    if (((arg1 << 8) | arg0) == func_0014C9D0(var_s0)) {
        return 1;
    }
    var_s0 += 1;
    if (var_s0 >= 3) {
        return 0;
    }
    goto loop_1;
}

s32 func_0014C9D0(s32 arg0) {
    s32 func_0014DA30(s32, s32);
    s32 id;

    id = func_001DE540();
    switch (arg0) {
    case 0:
        return func_0014DA30(id, 0);
    case 1:
        return func_0014DA30(id, 3);
    case 2:
        return func_0014DA30(id, 4);
    default:
        return -1;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_012", func_0014CA60);

INCLUDE_ASM("asm/nonmatchings/main_012", func_0014CBA0);

INCLUDE_ASM("asm/nonmatchings/main_012", func_0014CE30);

s32 func_0014D0F0(s32 arg0, void *arg1, void *arg2, s32 arg3) {
    s32 entries[8];
    s32 i;
    s32 *p;
    s32 key;

    func_0026FD30(arg0, entries);
    i = 0;
    if (0 < func_0026FE20(arg0)) {
        key = arg3 & 0xFFFF;
        p = entries;
        do {
            if (key == *p && func_0026FB10(arg0, *p) == 1) {
                ((s8 *)arg1)[6] = i;
                func_001DCD70(arg2, entries[i]);
                return func_0026FCE0(entries[i]) >> 5;
            }
            p++;
            i++;
        } while (i < func_0026FE20(arg0));
    }
    return -1;
}

s32 func_0014D1E0(s32 arg0, u8 *arg1, void *arg2, s32 arg3) {
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

typedef struct Info_0014D3E0 {
    u8 pad00[8];
    u16 x;
    s16 y;
} Info_0014D3E0;

typedef struct Sprite_0014D3E0 {
    Info_0014D3E0 *info;
    u8 pad04[0x34];
    s16 x;
    s16 y;
} Sprite_0014D3E0;

u16 *func_00278A90(s32, u16 *, s32, s32, s32, s16 *, s16 *);
s32 func_00278F10(s32, u16 *, s32, s32);

s32 func_0014D3E0(s32 arg0, u8 *arg1, void *arg2) {
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
                            func_0014D5C0(arg0, *node, entries);
                            func_00278DD0((u8 *)*node + 2, arg1 + 6);
                            func_001DCD70(arg2, **node);
                            ((Sprite_0014D3E0 *)arg2)->x = (value >> 16) - (((Sprite_0014D3E0 *)arg2)->info->x & 0x1FFF);
                            ((Sprite_0014D3E0 *)arg2)->y = (value & 0xFFFF) - (((Sprite_0014D3E0 *)arg2)->info->y & 0x1FFF);
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
} Info_0014D5C0;

void func_0014D5C0(s32 arg0, void *arg1, s32 *arg2) {
    Info_0014D5C0 *info = arg1;
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
                if (card != 0x3E7 && func_0014D7A0(card) == 0 && level >= func_0026FA80(card, arg0)) {
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

s32 func_0014D7A0(s32 arg0) {
    if (func_0026FCE0(arg0) >> 5) {
        return 1;
    }
    if (func_0026FC10(arg0) == 1) {
        return 1;
    }
    return 0;
}

s64 func_002493A0(s32);

typedef struct {
    u8 pad0[6];
    u8 slot[5];
} Obj1_0014D800;

typedef struct {
    u8 pad0[0x38];
    s16 f38;
    s16 f3A;
    u16 id;
} Obj2_0014D800;

s32 func_0014D800(s32 arg0, void *arg1, void *arg2) {
    Obj1_0014D800 *o1 = arg1;
    Obj2_0014D800 *o2 = arg2;
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

void func_0014DA30(s32 unused0, s32 unused1) {
    func_0024E410(unused0, unused1);
}

INCLUDE_ASM("asm/nonmatchings/main_012", func_0014DA40);

INCLUDE_ASM("asm/nonmatchings/main_012", func_0014DF80);

INCLUDE_ASM("asm/nonmatchings/main_012", func_0014E550);

INCLUDE_ASM("asm/nonmatchings/main_012", func_0014EB30);

static inline s32 dispatch_0014F3A0(s32 index, s32 id) {
    switch (index) {
    case 0:
        return func_0024E410(id, 0);
    case 1:
        return func_0024E410(id, 3);
    case 2:
        return func_0024E410(id, 4);
    default:
        return -1;
    }
}

static inline s32 select_0014F3A0(void) {
    s32 index;
    s32 position;
    s32 id;

    index = 0;
    do {
        position = func_0014C9D0(index);
        if (((func_001E36E0(position & 0xFF, position >> 8) == 0) ? 1 : 0) == 1) {
            id = func_001DE540();
            return dispatch_0014F3A0(index, id);
        }
        index++;
    } while (index < 3);
    return -1;
}

s32 func_0014F3A0(void) {
    s32 result;

    result = select_0014F3A0();
    if (result < 0) {
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_012", func_0014F490);

INCLUDE_ASM("asm/nonmatchings/main_012", func_0014F7C0);

s32 func_0014F8C0(s32 arg0, s32 arg1) {
    s32 sp50[4];
    s32 i;
    s32 mask;
    s32 low;
    s32 high;
    s32 cell;
    s32 value;

    func_00254C90(sp50, *(s32 *)((u8 *)func_0026FC90(arg1, 0) + 4));
    if ((mask = func_00254890(sp50, arg0)) < 0) {
        return 0;
    }
    for (i = 0; i < func_0024E910(mask); i++) {
        cell = func_0024EC50(mask, i);
        high = cell >> 8;
        low = cell & 0xFF;
        value = func_001E1090(high, low);
        if (func_002509E0(high, low, value & 0xFF, value >> 8) >= 0x9C4) {
            return 0;
        }
    }
    return 1;
}

s32 func_0014F9B0(s32 arg0) {
    if (func_001DF470(arg0) > 0x4B0) {
        if (func_001E0150(arg0) >= 5) {
            return 0x2EE;
        } else {
            return 0x5DC;
        }
    } else {
        return 0x960;
    }
}

s32 func_0014FA10(s32 arg0, s32 arg1) {
    s32 index;
    u8 count;
    s32 mask;
    s32 entry;

    count = 0;
    switch (arg1) {
    case 0x264:
        if (func_0024E910(func_0024CA40(0, 0, arg0, 1, 0x10, 0xE)) <= 3) {
            break;
        }
        return 1;
    case 0x227:
        if (func_0024E910(func_0024CA40(0, 0, arg0, 1, 0xF, 0xE)) > 0) {
            return 0;
        }
        mask = func_0024CA40(0, 0, arg0, 2, 0xF, 0xE);
        for (index = 0; index < func_0024E910(mask); index++) {
            entry = func_0024EC50(mask, index);
            if (func_002781B0(entry >> 8, entry & 0xFF, 0) == 1) {
                count++;
            }
        }
        if (count >= 2) {
            return 1;
        }
        break;
    }
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
} Req_0014FB70;

typedef struct {
    u8 pad0[0x160];
    u16 list[32];    /* 0x160 */
    u8 idx : 5;      /* 0x1A0 */
    u8 pad1A0 : 3;
    u8 pad1A1;
    u16 count;       /* 0x1A2 */
} Work_0014FB70;

s32 func_0014B900(void *, void *, s32);
s32 func_00276290(void *, void *, s32);

s32 func_0014FB70(s32 arg0, void *arg1) {
    Req_0014FB70 req;
    Work_0014FB70 *w;
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
        if (func_0014B900(w, &req, arg0) == 0) {
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

INCLUDE_ASM("asm/nonmatchings/main_012", func_0014FD40);

INCLUDE_ASM("asm/nonmatchings/main_012", func_00150270);

s32 func_00150470(u16 *arg0, s32 arg1, s32 arg2) {
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
    func_00150270(arg0 + idx * 8);
    if (((arg0[idx * 8 + 2] >> 8) & 0xFF) == 10) {
        if (func_001DE6D0(arg1) == 1 && func_00150C40(pos, arg1, arg2) >= 0) {
            return pos | 0x10000;
        }
        if (func_0027B9B0(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (func_001E2100(arg1, 0, 0) == 0) {
        if (func_0027B9B0(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (func_001DE6D0(arg1) == 1 && func_00150C40(pos, arg1, arg2) >= 0) {
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

INCLUDE_ASM("asm/nonmatchings/main_012", func_00150850);

void func_00150BE0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7,
                   s32 a8, u16 a9, s32 a10, s32 a11, u8 a12, s32 a13) {
    func_0027DE20(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, 0, 2000, a13);
}

typedef struct {
    s16 card;
    u8 f2;
    u8 pad3;
    s16 f4;
    u8 pad6[6];
    s32 fC;
} Act_00150C40;

typedef struct {
    u8 pad0[0x3C];
    u16 id;
    u8 pad3E[0x22];
} Card_00150C40;

s32 func_00150F10(s32 arg0, void *arg1);
s32 func_00151170(s32 arg0, void *arg1, void *arg2);
s32 func_001516A0(s32 arg0, void *arg1, void *arg2);
s32 func_00151CF0(s32 arg0, u8 arg1, void *arg2, s32 arg3);
s32 func_00276F10(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8,
                  s32 arg9);

s32 func_00150C40(s32 arg0, s32 arg1, s32 arg2) {
    extern s32 func_00278890(s32, s32);
    Card_00150C40 buf;
    s32 res;
    s32 type;
    Act_00150C40 *act = (Act_00150C40 *)arg2;
    s32 card;
    s32 r;

    act->card = arg0;
    if (func_001DE6D0(arg1) == 0) {
        return -1;
    }
    if (func_00278890(arg1, 0) == 5 && func_00278890(arg1, 1) == 5) {
        return -1;
    }
    type = func_00150F10(arg1, &buf);
    if (type < 0) {
        return -1;
    }
    act->f2 = 10;
    act->fC = 0;
    card = func_001E1090(arg0 >> 8, arg0 & 0xFF);
    if (type == 0) {
        if (func_001516A0(arg1, act, &buf) >= 0) {
            res = func_00276F10(&buf, card & 0xFF, card >> 8, arg1 == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, func_00153ED0(arg1));
            if (res < 0) {
                if (func_001E0150(arg1) < 6) {
                    r = func_00151CF0(arg1, type, &buf, res);
                    if (r < 0) {
                        return -1;
                    }
                    act->f4 = r;
                    return 1;
                }
            } else {
                r = func_00151CF0(arg1, type, &buf, res);
                if (r < 0) {
                    return -1;
                }
                act->f4 = r;
                return 1;
            }
        }
    } else {
        res = func_00276F10(&buf, card & 0xFF, card >> 8, arg1 == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, func_00153ED0(arg1));
    }
    if (type == 2) {
        func_00151AC0(arg1, act, &buf);
        r = func_00151CF0(arg1, type, &buf, res);
        if (r < 0) {
            return -1;
        }
        act->f4 = r;
        return 1;
    } else if (type == 3) {
        func_00151170(arg1, act, &buf);
        r = func_00151CF0(arg1, type, &buf, res);
        if (r < 0) {
            return -1;
        }
        act->f4 = r;
        return 1;
    } else {
        if (func_001514A0(arg1, (u8 *)act, &buf, buf.id) < 0) {
            return -1;
        }
        r = func_00151CF0(arg1, type, &buf, res);
        if (r < 0) {
            return -1;
        }
        act->f4 = r;
        return 1;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_012", func_00150F10);

INCLUDE_ASM("asm/nonmatchings/main_012", func_00151170);

s32 func_001513B0(s32 arg0, void *arg1, void *arg2, s32 arg3) {
    s32 i;
    s32 ids[8];

    func_0026FD30(arg0, ids);
    for (i = 0; i < func_0026FE20(arg0); i++) {
        if (((arg3 & 0xFFFF) == ids[i]) &&
            (func_0026FB10(arg0, ids[i]) == 1)) {
            ((u8 *)arg1)[6] = i;
            func_001DCD70(arg2, ids[i]);
            return func_0026FCE0(ids[i]) >> 5;
        }
    }
    return -1;
}

s32 func_001514A0(s32 arg0, u8 *arg1, void *arg2, s32 arg3) {
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

INCLUDE_ASM("asm/nonmatchings/main_012", func_001516A0);

typedef struct {
    u16 id;
    u8 values[5];
} Info_00151880;

void func_00151880(s32 arg0, void *arg1, s32 *arg2) {
    Info_00151880 *info = arg1;
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
                if (card != 0x3E7 && func_00151A60(card) == 0 && level >= func_0026FA80(card, arg0)) {
                    cost = func_0026FBB0(card);
                    if ((cost & 0xFFFF) + (cost >> 16) * 2 < 0xDAD && func_0026FC10(card) == 2 &&
                        (u16)func_002789F0(info->id, (u16)card) == 0x3E7) {
                        func_00278D20(info->values, buf[i]);
                    }
                }
            }
        }
    }
}

s32 func_00151A60(s32 arg0) {
    if ((func_0026FCE0(arg0) >> 5) != 0) {
        return 1;
    }
    if (func_0026FC10(arg0) == 1) {
        return 1;
    }
    return 0;
}

s64 func_002493A0(s32);

typedef struct {
    u8 pad0[6];
    u8 slot[5];
} Obj1_00151AC0;

typedef struct {
    u8 pad0[0x38];
    s16 f38;
    s16 f3A;
    u16 id;
} Obj2_00151AC0;

s32 func_00151AC0(s32 arg0, void *arg1, void *arg2) {
    Obj1_00151AC0 *o1 = arg1;
    Obj2_00151AC0 *o2 = arg2;
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

INCLUDE_ASM("asm/nonmatchings/main_012", func_00151CF0);

INCLUDE_ASM("asm/nonmatchings/main_012", func_00152100);

INCLUDE_ASM("asm/nonmatchings/main_012", func_001526D0);

INCLUDE_ASM("asm/nonmatchings/main_012", func_00152CD0);

INCLUDE_ASM("asm/nonmatchings/main_012", func_00153550);

s32 func_00153AB0(void) {
    return (func_001E0110(func_001DE540()) < 3) ? 0 : 1;
}

s32 func_00153AE0(s32 arg0, s32 arg1) {
    extern s32 func_001E1030();
    u16 buf[22];
    s32 kind;
    u32 *info;
    s32 c1;
    s32 c2;
    s32 player;
    s32 y1;
    s32 x1;
    s32 y2;
    s32 x2;
    s32 pos;
    s32 score;

    kind = func_001E1030(arg0, arg1);
    func_001E1090(arg0, arg1);
    player = func_00250360(arg0, arg1);
    info = func_001E0B70(arg0, arg1, 0);
    if (func_001E2100(arg0, arg1, 4) != 0) {
        return 0;
    }
    func_0024C910(player, 2, buf);
    switch (func_001E0700(arg0, arg1) >> 5) {
    case 0:
        switch (kind) {
        case 0x24:
            if (func_0024E910(func_0024CA40(0, 0, player, 1, 0x95F0037, 0xE)) >= 2) {
                return 1;
            }
            break;
        case 0xD5:
            if (func_0024E910(func_0024CA40(0, 0, player, 1, 0x1D, 0x16)) >= 2) {
                return 1;
            }
            break;
        }
        return 2;
    case 1:
        if (func_0027D830(arg0, arg1, 0, 0, 6, 0) == 5) {
            return 2;
        }
        if (info == NULL) {
            return 2;
        }
        switch (*info >> 8) {
        case 0xD:
            return 1;
        case 0x21:
            func_0027C2C0((player == 0) ? 1 : 0, buf, 0x1D, 0, 0);
            pos = func_0027B650(buf);
            x1 = pos >> 8;
            y1 = pos & 0xFF;
            c1 = func_001E1090(x1, y1);
            func_0027C070(player, buf, 0x1D, 1);
            pos = func_0027B650(buf);
            x2 = pos >> 8;
            y2 = pos & 0xFF;
            c2 = func_001E1090(x2, y2);
            func_0024C910(player, 1, buf);
            if (func_002509E0(x1, y1, c1 & 0xFF, c1 >> 8) >= 2000) {
                score = func_002509E0(x1, y1, c1 & 0xFF, c1 >> 8);
                if (func_002509E0(x2, y2, c2 & 0xFF, c2 >> 8) < score) {
                    return 1;
                }
            }
            break;
        }
        break;
    default:
        return 2;
    }
    return 2;
}

static inline s32 max_00153DD0(s32 a, s32 b) {
    if (a < b) {
        return b;
    }
    return a;
}

s32 func_00153DD0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 min_y;
    s32 min_x;

    min_y = arg3 < arg5 ? arg3 : arg5;
    arg5 = max_00153DD0(arg5, arg3);
    min_x = arg2 < arg4 ? arg2 : arg4;
    arg4 = max_00153DD0(arg4, arg2);
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

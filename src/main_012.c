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

typedef struct {
    u16 card;
    u8 flag;
    u8 pad3;
} Slot_0014C3B0;

typedef struct {
    u16 low;
    u16 high;
} DataHalves_0014C3B0;

typedef struct {
    u16 coordinates;
    u8 pad2[2];
    u16 state;
    u8 pad6[2];
    union {
        u32 word;
        DataHalves_0014C3B0 halves;
    } data;
} Entry_0014C3B0;


void func_0014C3B0(void *arg0) {
    extern s32 func_0027B200();
    extern void func_0027E770();
    extern s32 func_0014C6C0();
    Entry_0014C3B0 *entry = arg0;
    s32 side;
    s32 player;
    s32 pos;
    s32 other;
    s32 otherPos;
    s32 i;
    s32 result;
    u8 work[0x70];
    Slot_0014C3B0 list[22];
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
        if (func_0027B200(entry->coordinates >> 8, entry->coordinates & 0xFF, pos & 0xFF, pos >> 8,
                          other >> 8, other & 0xFF, otherPos & 0xFF, otherPos >> 8, 3) > 0) {
            entry->state = 0x2FF;
            entry->data.word = (other << 16) | entry->data.halves.low;
            return;
        }
        countB = 0;
        countA = 0;
        i = 1;
        while (1) {
            switch (func_0014C6C0(entry, 0, player, pos & 0xFF, pos >> 8,
                                  func_0024DE70(entry->coordinates >> 8, entry->coordinates & 0xFF) == 0 ? 1 : 0,
                                  (u8)i, func_0014F9B0(side), list, 0,
                                  &countA, &countB, 3, work)) {
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
                entry->state = 0x3FF;
                entry->data.word = (pos << 16) | entry->data.halves.low;
                return;
            }
            i++;
            if (i > 3) {
                break;
            }
        }
        if (func_0014C970(pos & 0xFF, pos >> 8) == 1) {
            if (func_0014F3A0() == 1) {
                entry->state = 0x2FF;
                entry->data.word = (other << 16) | entry->data.halves.low;
            } else {
                entry->state = 0x6FF;
                entry->data.word = (pos << 16) | entry->data.halves.low;
            }
            return;
        }
        result = func_0014CA60();
        if (result >= 0) {
            entry->state = 0x6FF;
            entry->data.word = (result << 16) | entry->data.halves.low;
        } else {
            entry->state = 0x2FF;
            entry->data.word = (other << 16) | entry->data.halves.low;
        }
    }
}

void func_0014C6C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28) {
    func_0027DE20(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
        arg_sp0, arg_sp8, arg_sp10, arg_sp18, arg_sp20, 0, 2500, arg_sp28);
}

void func_0014C720(void *arg0) {
    extern s32 func_001E1030();
    Entry_0014C3B0 *entry = arg0;
    s32 slot;
    s32 kind;

    slot = func_00250360(entry->coordinates >> 8, entry->coordinates & 0xFF);
    kind = func_001E1030(entry->coordinates >> 8, entry->coordinates & 0xFF);
    switch (kind) {
    case 0x264:
    case 0x227:
        if (func_0014FA10(slot, kind) == 1) {
            entry->state = 0x3FF;
            entry->data.word = (func_001E1090(entry->coordinates >> 8, entry->coordinates & 0xFF) << 16) | entry->data.halves.low;
            return;
        }
        break;
    case 0x23A:
        if (func_0014F3A0() == 1 && func_0027D720(entry, 0) == 1) {
            return;
        }
        break;
    case 0x23F:
        if (func_0014F3A0() == 1 && func_001E2100(entry->coordinates >> 8, entry->coordinates & 0xFF, 4) == 0 && func_0027D720(entry, 0) == 1) {
            return;
        }
        break;
    }
    func_0014C3B0(entry);
}

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

static inline s32 slot_0014CA60(s32 index) {
    s32 func_0014DA30(s32, s32);
    s32 id;

    id = func_001DE540();
    switch (index) {
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

s32 func_0014CA60(void) {
    s32 index;
    s32 position;

    index = 0;
    do {
        position = slot_0014CA60(index);
        if (((func_001E36E0(position & 0xFF, position >> 8) == 0) ? 1 : 0) == 1) {
            return slot_0014CA60(index);
        }
        index++;
    } while (index < 3);
    return -1;
}

typedef struct {
    s16 id;
    u8 unk2;
    u8 pad3;
    s16 unk4;
    u8 pad6[6];
    s32 unkC;
} Ctx_0014CBA0;

typedef struct {
    u8 pad0[0x3C];
    u16 unk3C;
    u8 pad3E[0x22];
} Work_0014CBA0;

s32 func_0014DA40(s32 arg0, u8 arg1, void *arg2, s32 arg3);
s32 func_00276F10(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8,
                  s32 arg9);

s32 func_0014CBA0(s32 arg0, s32 arg1, s32 arg2) {
    s32 ret;
    s32 kind;
    Ctx_0014CBA0 *ctx = (Ctx_0014CBA0 *)arg2;
    Work_0014CBA0 work;
    s32 res;
    extern s32 func_00278890();

    ctx->id = arg0;
    if (func_001DE6D0(arg1) == 0) {
        return -1;
    }
    if (func_00278890(arg1, 0) == 5 && func_00278890(arg1, 1) == 5) {
        return -1;
    }
    kind = func_0014CE30(arg1, &work);
    if (kind < 0) {
        return -1;
    }
    ctx->unk2 = 10;
    ctx->unkC = 2;
    arg0 = func_001E1090(arg0 >> 8, arg0 & 0xFF);
    if (kind == 0) {
        if (func_0014D3E0(arg1, (u8 *)ctx, &work) >= 0) {
            ret = func_00276F10(&work, arg0 & 0xFF, arg0 >> 8, arg1 == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, func_0014F9B0(arg1));
            if (ret < 0) {
                if (func_001E0150(arg1) < 6) {
                    res = func_0014DA40(arg1, kind, &work, ret);
                    if (res < 0) {
                        return -1;
                    }
                    ctx->unk4 = res;
                    return 1;
                }
            } else {
                res = func_0014DA40(arg1, kind, &work, ret);
                if (res < 0) {
                    return -1;
                }
                ctx->unk4 = res;
                return 1;
            }
        }
    } else {
        ret = func_00276F10(&work, arg0 & 0xFF, arg0 >> 8, arg1 == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, func_0014F9B0(arg1));
    }
    if (kind == 2) {
        func_0014D800(arg1, ctx, &work);
        res = func_0014DA40(arg1, kind, &work, ret);
        if (res < 0) {
            return -1;
        }
        ctx->unk4 = res;
        return 1;
    }
    if (func_0014D1E0(arg1, (u8 *)ctx, &work, work.unk3C) < 0) {
        return -1;
    }
    res = func_0014DA40(arg1, kind, &work, ret);
    if (res < 0) {
        return -1;
    }
    ctx->unk4 = res;
    return 1;
}

s32 func_0014CE30(s32 arg0, void *arg1) {
    extern s32 func_00278890();
    extern s32 func_001F9FE0();
    s32 ids[8];
    s32 data[8];
    u8 type = (u8)func_00278890(arg0, 0);
    u8 attr = (u8)func_00278890(arg0, 1);

    if (arg1 == NULL) {
        return -1;
    }
    func_0026FD30(arg0, ids);
    if (type == 5) {
        s32 result = func_0014D1E0(arg0, (u8 *)data, arg1, 0x3E7);
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
    if (func_0014D0F0(arg0, (u8 *)data, arg1, 0x354) >= 0) {
        if (func_0014F8C0(arg0, 0x354) == 1) {
            return 2;
        }
    }
    if (func_0014F3A0() == 1) {
        if (func_001E01F0(arg0) == 0) {
            if (func_0014D0F0(arg0, (u8 *)data, arg1, 0x2BD) >= 0) {
                return 2;
            }
        }
    }
    if (func_001E0150(arg0) >= 4) {
        if (func_0014D0F0(arg0, (u8 *)data, arg1, 0x2E6) >= 0) {
            return 2;
        }
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
        s32 result = func_0014D1E0(arg0, (u8 *)data, arg1, 0x3E7);
        if (result >= 0) {
            return result;
        }
        return -1;
    }
}

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

typedef struct Nibbles_0014DF80 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_0014DF80;

typedef struct Output_0014DF80 {
    u16 position;
    u8 action;
    u8 pad3;
    u16 destination;
    u8 pad6[6];
    s32 special;
    u8 result;
} Output_0014DF80;

void func_001E1E70(s32, s32, s32, s32);
s32 func_00276CC0(s32, s32, s32, s32, s32, u8);
s32 func_0027BE10(s32, s32, s32, s32, s32);

s32 func_0014DF80(u16 *arg0, s32 arg1, void *arg2, u8 arg3) {
    Output_0014DF80 *output = arg2;
    s32 target;
    u8 endX;
    u8 extra;
    Nibbles_0014DF80 nibbles[12];
    s32 bestScore;
    s32 best;
    s32 i;
    Nibbles_0014DF80 *p;
    extern s32 func_0014F490();
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

        initialScore = func_0014F9B0(arg1);
        centerX = target & 0xFF;
        centerY = target >> 8;
        if (func_00276CC0(centerX, centerY, *arg0, 3, initialScore, 0) == 0) {
            output->position = *arg0;
            output->action = 6;
            output->destination = target;
            output->result = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, output->destination, 1, 0);
            output->special = func_0014F490(*arg0 >> 8, *arg0 & 0xFF, arg0);
            func_0027B1B0(arg0, arg3);
            return 0;
        }
        if ((range = func_002464F0(func_001DF540(*arg0 >> 8, *arg0 & 0xFF), centerX, centerY)) == 0) {
            output->position = *arg0;
            output->action = 6;
            output->destination = target;
            output->result = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, output->destination, 1, 0);
            output->special = func_0014F490(*arg0 >> 8, *arg0 & 0xFF, arg0);
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
            extra = (u8)func_0027BBC0(*arg0 >> 8, *arg0 & 0xFF, 0);
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
                    if (func_0027BE10(*arg0 >> 8, *arg0 & 0xFF, x, y, 0) == 0 || (u8)*arg0 == 0) {
                        candidateScore = func_00276CC0(x, y, *arg0, 3, (u16)func_0014F9B0(arg1), 0);
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
                output->result = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, output->destination, 1, 0);
            } else {
                output->result = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, output->destination, 0, 0);
            }
            output->special = func_0014F490(*arg0 >> 8, *arg0 & 0xFF, arg0);
        } else {
            output->position = *arg0;
            output->action = 6;
            output->destination = target;
            output->result = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, output->destination, 1, 0);
            output->special = func_0014F490(*arg0 >> 8, *arg0 & 0xFF, arg0);
        }
        func_0027B1B0(arg0, arg3);
        return 0;
    }
}

typedef struct {
    u16 position;
    u8 pad2[6];
    u32 targets;
} Input_0014E550;

typedef struct {
    u16 position;
    u8 action;
    u8 pad3;
    u16 destination;
    u8 pad6[6];
    s32 flag;
    u8 result;
} Output_0014E550;

typedef struct {
    u8 x : 4;
    u8 y : 4;
} Point_0014E550;

static inline u32 target_0014E550(void *src, u8 mode) {
    Input_0014E550 *input = src;
    if (mode == 1) {
        return (input->targets >> 16) & 0xFFFF;
    }
    return *(u16 *)&input->targets;
}

static inline s32 max_0014E550(s32 a, s32 b) {
    return a > b ? a : b;
}

s32 func_0014E550(void *arg0, s32 arg1, void *arg2, u8 arg3) {
    extern s32 func_0014F490();
    extern void func_0027A090();
    extern s32 func_002464F0(s32, s32, s32);
    extern s32 func_00276CC0(s32, s32, s32, s32, s32, u8);
    s32 sourcePosition;
    s32 count;
    s32 sourceY;
    s32 sourceX;
    s32 flag;
    Point_0014E550 points[12];
    s32 destination;
    s32 oldFlag;
    s32 i;
    s32 best;
    u32 targetX;
    u32 targetY;
    Point_0014E550 *p;
    Input_0014E550 *input = arg0;
    Output_0014E550 *output = arg2;

    targetX = target_0014E550(input, arg3);
    targetY = target_0014E550(input, arg3);
    if (func_001DF540(targetY >> 8, targetX & 0xFF) == 0) {
        func_0027B1B0(input, 1);
        return -1;
    }
    oldFlag = func_0014F490(input->position >> 8, input->position & 0xFF, input);
    sourcePosition = func_001E1090(input->position >> 8, input->position & 0xFF);
    targetX = target_0014E550(input, arg3);
    targetY = target_0014E550(input, arg3);
    destination = func_001E1090(targetY >> 8, targetX & 0xFF);
    p = points;
    i = 0;
    do {
        i++;
        p->x = p->y = 15;
        p++;
    } while (i < 12);
    {
        s32 card = func_001DF540(input->position >> 8, input->position & 0xFF);
        sourceX = sourcePosition & 0xFF;
        sourceY = sourcePosition >> 8;
        if (func_002464F0(card, sourceX, sourceY) == 0) {
            s32 cost;
            output->position = input->position;
            output->action = 6;
            output->destination = sourcePosition;
            cost = func_00276CC0(sourceX, sourceY, arg1, 3, 1, (u8)func_0014F9B0(arg1));
            if (cost >= func_001E0290(input->position >> 8, input->position & 0xFF, 0)) {
                output->result = func_0027E360(input->position >> 8, input->position & 0xFF,
                                             output->destination, 1, 0);
            } else {
                output->result = func_0027E360(input->position >> 8, input->position & 0xFF,
                                             output->destination, 0, 0);
            }
            func_0027B1B0(input, arg3);
            return 0;
        } else {
            s32 position = input->position;
            s32 destinationX;
            Point_0014E550 *candidate;
            s32 n;
            s32 minCost;
            s32 identity;
            s32 positionY;
            s32 positionX;

            identity = (u16)func_0014F9B0(arg1);
            positionY = position >> 8;
            positionX = position & 0xFF;
            destinationX = destination & 0xFF;

            func_0027A090(positionY, positionX, points,
                         sourceX, sourceY, destinationX, destination >>= 8,
                         target_0014E550(input, arg3), 0, 30, identity);
            count = func_0027AFC0((u8 *)points);
            best = 0xFF;
            if (count > 0) {
                flag = 0;
                minCost = 0xFFFF;
                for (n = 0; n < count; n++) {
                    if (func_0014F7C0(input->position >> 8, input->position & 0xFF,
                                     sourceX, sourceY, destinationX, destination) == 1) {
                        best = n;
                        flag = 1;
                        points[n].x = destinationX;
                        points[n].y = destination;
                        n = count;
                    } else {
                        s32 cost;
                        candidate = &points[n];
                        cost = func_00276CC0(candidate->x, candidate->y, arg1,
                                                3, 1, (u8)func_0014F9B0(arg1));
                        if (cost < minCost) {
                            minCost = cost;
                            best = n;
                        } else if (cost == minCost) {
                            if ((max_0014E550(candidate->x, destinationX) -
                                 (candidate->x < destinationX ? candidate->x : destinationX)) +
                                (max_0014E550(candidate->y, destination) -
                                 (candidate->y < destination ? candidate->y : destination)) <
                                (max_0014E550(points[best].x, destinationX) -
                                 (points[best].x < destinationX ? points[best].x : destinationX)) +
                                (max_0014E550(points[best].y, destination) -
                                 (points[best].y < destination ? points[best].y : destination))) {
                                minCost = cost;
                                best = n;
                            }
                        }
                    }
                }
            } else {
                output->position = input->position;
                output->action = 6;
                output->destination = sourcePosition;
                output->flag = oldFlag;
                output->result = func_0027E360(input->position >> 8, input->position & 0xFF,
                                             output->destination, 0, 0);
                func_0027B1B0(input, arg3);
                return 0;
            }
                if (best != 0xFF) {
                    output->position = input->position;
                    output->action = 6;
                    output->destination = (points[best].y << 8) | points[best].x;
                    output->flag = flag;
                    output->result = func_0027E360(input->position >> 8, input->position & 0xFF,
                                                 output->destination, 0, 0);
                } else {
                    output->position = input->position;
                    output->action = 6;
                    output->destination = sourcePosition;
                    output->flag = flag;
                    output->result = func_0027E360(input->position >> 8, input->position & 0xFF,
                                                 output->destination, 0, 0);
                    func_0027B1B0(input, arg3);
                    return 0;
                }

        }
    }
    return 0;
}

typedef struct Coord_0014EB30 {
    u8 x : 4;
    u8 y : 4;
} Coord_0014EB30;

typedef struct Unit_0014EB30 {
    u16 position;
    u8 pad2[6];
    union {
        u32 packed;
        u16 low;
    } target;
} Unit_0014EB30;

typedef struct Output_0014EB30 {
    u16 position;
    u8 kind;
    u8 pad3;
    u16 target;
    u8 pad6[6];
    s32 value;
    u8 flag;
} Output_0014EB30;

void func_001E1E70(s32, s32, s32, s32);

static inline u32 target_0014EB30(void *unit, s32 side) {
    return side == 1 ? (u32)(u16)(((Unit_0014EB30 *)unit)->target.packed >> 16) : (u32)((Unit_0014EB30 *)unit)->target.low;
}

static inline u32 minY_0014EB30(void *unit, s32 side, u8 coord) {
    return coord < (target_0014EB30(unit, side) >> 8) ? coord : (target_0014EB30(unit, side) >> 8);
}

static inline u32 maxY_0014EB30(void *unit, s32 side, u8 coord) {
    return (target_0014EB30(unit, side) >> 8) < coord ? coord : (target_0014EB30(unit, side) >> 8);
}

static inline u32 minX_0014EB30(void *unit, s32 side, u8 coord) {
    return coord < (target_0014EB30(unit, side) & 0xFF) ? coord : (target_0014EB30(unit, side) & 0xFF);
}

static inline u32 maxX_0014EB30(void *unit, s32 side, u8 coord) {
    return (target_0014EB30(unit, side) & 0xFF) < coord ? coord : (target_0014EB30(unit, side) & 0xFF);
}

s32 func_0014EB30(void *arg0, s32 arg1, void *arg2, u8 arg3, u8 arg4) {
    extern s32 func_0014F490();
    extern s32 func_00276CC0();
    extern void func_00279230();
    extern s32 func_0027E360(s32, s32, s32, u8, s32);
    Coord_0014EB30 coords[12];
    s32 initial;
    s32 cell;
    s32 count;

    initial = func_001E1090(((Unit_0014EB30 *)arg0)->position >> 8, ((Unit_0014EB30 *)arg0)->position & 0xFF);
    {
    s32 bestScore;
    s32 best;
    s32 side = arg3;
    Coord_0014EB30 *candidate;
    s32 index;
    if (target_0014EB30(arg0, side) == 0xFFFF) {
        if (initial == target_0014EB30(arg0, side)) {
            ((Output_0014EB30 *)arg2)->position = ((Unit_0014EB30 *)arg0)->position;
            ((Output_0014EB30 *)arg2)->kind = 6;
            ((Output_0014EB30 *)arg2)->target = initial;
            ((Output_0014EB30 *)arg2)->flag = func_0027E360(((Unit_0014EB30 *)arg0)->position >> 8, ((Unit_0014EB30 *)arg0)->position & 0xFF, ((Output_0014EB30 *)arg2)->target, arg4, 0);
            ((Output_0014EB30 *)arg2)->value = func_0014F490(((Unit_0014EB30 *)arg0)->position >> 8, ((Unit_0014EB30 *)arg0)->position & 0xFF, arg0);
            func_0027B1B0(arg0, arg3);
            return 0;
        }
    }

    if (func_001E2100(((Unit_0014EB30 *)arg0)->position >> 8,
                      ((Unit_0014EB30 *)arg0)->position & 0xFF, 4) != 0) {
        if ((func_001E0700(((Unit_0014EB30 *)arg0)->position >> 8,
                          ((Unit_0014EB30 *)arg0)->position & 0xFF) >> 5) == 1 ||
            (func_001E0700(((Unit_0014EB30 *)arg0)->position >> 8,
                          ((Unit_0014EB30 *)arg0)->position & 0xFF) >> 5) == 5) {
            func_001E1E70(((Unit_0014EB30 *)arg0)->position >> 8,
                          ((Unit_0014EB30 *)arg0)->position & 0xFF, 0, 1);
            ((Output_0014EB30 *)arg2)->position = ((Unit_0014EB30 *)arg0)->position;
            ((Output_0014EB30 *)arg2)->kind = 0xE;
            return 0;
        }
    }

    candidate = coords;
    {
        s32 i = 0;
        Coord_0014EB30 *entry = candidate;
        do {
            entry->x = entry->y = 0xF;
            i++;
            entry++;
        } while (i < 12);
    }

    cell = func_001E3790(target_0014EB30(arg0, side) & 0xFF, ((u32)target_0014EB30(arg0, side)) >> 8);
    if (cell < 0) {
        cell = 0xFFFF;
    }
    func_00279230(((Unit_0014EB30 *)arg0)->position >> 8, ((Unit_0014EB30 *)arg0)->position & 0xFF,
                 coords, initial & 0xFF, initial >> 8, target_0014EB30(arg0, side) & 0xFF,
                 ((u32)target_0014EB30(arg0, side)) >> 8, (u16)cell, 7);
    count = func_0027AFC0((u8 *)coords);
    {
        if (count > 0) {
        best = 0xFF;
        bestScore = 0xFFFF;
        for (index = 0; index < count; index++) {
                if (func_001E36E0(candidate->x, candidate->y) == 0) {
                    s32 score = func_00276CC0(candidate->x, candidate->y, arg1, 3, 1, (u8)func_0014F9B0(arg1));
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
                        bestMinY = minY_0014EB30(arg0, side, bestY);
                        bestMaxY = maxY_0014EB30(arg0, side, bestY);
                        bestX = (&coords[best])->x;
                        bestMinX = minX_0014EB30(arg0, side, bestX);
                        bestMaxX = maxX_0014EB30(arg0, side, bestX);
                        currentY = (u8)candidate->y;
                        currentMinY = minY_0014EB30(arg0, side, currentY);
                        currentMaxY = maxY_0014EB30(arg0, side, currentY);
                        currentX = candidate->x;
                        currentMinX = minX_0014EB30(arg0, side, currentX);
                        currentMaxX = maxX_0014EB30(arg0, side, currentX);
                        if ((currentMaxX - currentMinX) + (currentMaxY - currentMinY) < (bestMaxX - bestMinX) + (bestMaxY - bestMinY)) {
                            bestScore = score;
                            best = index;
                        }
                    }
                }
            candidate++;
        }
    } else {
        ((Output_0014EB30 *)arg2)->position = ((Unit_0014EB30 *)arg0)->position;
            ((Output_0014EB30 *)arg2)->kind = 6;
            ((Output_0014EB30 *)arg2)->target = initial;
            ((Output_0014EB30 *)arg2)->flag = func_0027E360(((Unit_0014EB30 *)arg0)->position >> 8, ((Unit_0014EB30 *)arg0)->position & 0xFF, ((Output_0014EB30 *)arg2)->target, arg4, 0);
            ((Output_0014EB30 *)arg2)->value = func_0014F490(((Unit_0014EB30 *)arg0)->position >> 8, ((Unit_0014EB30 *)arg0)->position & 0xFF, arg0);
        func_0027B1B0(arg0, arg3);
        return 0;
    }

        if (best != 0xFF) {
            ((Output_0014EB30 *)arg2)->position = ((Unit_0014EB30 *)arg0)->position;
            ((Output_0014EB30 *)arg2)->kind = 6;
            ((Output_0014EB30 *)arg2)->target = (coords[best].y << 8) | coords[best].x;
            ((Output_0014EB30 *)arg2)->flag = func_0027E360(((Unit_0014EB30 *)arg0)->position >> 8, ((Unit_0014EB30 *)arg0)->position & 0xFF, ((Output_0014EB30 *)arg2)->target, arg4, 0);
            ((Output_0014EB30 *)arg2)->value = func_0014F490(((Unit_0014EB30 *)arg0)->position >> 8, ((Unit_0014EB30 *)arg0)->position & 0xFF, arg0);
        } else {
            ((Output_0014EB30 *)arg2)->position = ((Unit_0014EB30 *)arg0)->position;
            ((Output_0014EB30 *)arg2)->kind = 6;
            ((Output_0014EB30 *)arg2)->target = initial;
            ((Output_0014EB30 *)arg2)->flag = func_0027E360(((Unit_0014EB30 *)arg0)->position >> 8, ((Unit_0014EB30 *)arg0)->position & 0xFF, ((Output_0014EB30 *)arg2)->target, arg4, 0);
            ((Output_0014EB30 *)arg2)->value = func_0014F490(((Unit_0014EB30 *)arg0)->position >> 8, ((Unit_0014EB30 *)arg0)->position & 0xFF, arg0);
        }
        func_0027B1B0(arg0, arg3);
    }
    }
    return 0;
}

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

static inline s32 max_0014F7C0(s32 a, s32 b) {
    if (b < a) {
        return a;
    }
    return b;
}

s32 func_0014F7C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 min_y;
    s32 min_x;

    min_y = arg3 < arg5 ? arg3 : arg5;
    arg5 = max_0014F7C0(arg3, arg5);
    min_x = arg2 < arg4 ? arg2 : arg4;
    arg4 = max_0014F7C0(arg2, arg4);
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

typedef struct {
    u16 pos;
    u16 unk2;
    u16 unk4;
    u16 unk6;
    s32 unk8;
} Unit_00150270;

void func_00150850(void *);
void func_0027CA50(void *, s32, s32, s32);

s32 func_00150270(void *arg0) {
    Unit_00150270 *unit = arg0;
    s32 handle;

    func_001E1090(unit->pos >> 8, unit->pos & 0xFF);
    handle = func_00250360(unit->pos >> 8, unit->pos & 0xFF);
    if (func_001DF540(unit->pos >> 8, unit->pos & 0xFF) != 0 &&
        func_001E2100(unit->pos >> 8, unit->pos & 0xFF, 0) == 0 && unit->pos != 0xFFFF) {
        if ((unit->pos & 0xFF) == 0) {
            if (unit->unk8 == -1) {
                if (func_00153AB0() == 1) {
                    func_0027E210(unit, 3, 3, 0);
                } else if (func_0027BBC0(unit->pos >> 8, unit->pos & 0xFF, 0) == 1) {
                    if (func_001DE6D0(unit->pos >> 8) == 1) {
                        unit->unk4 = 0x50A;
                    } else {
                        unit->unk4 = 0x5FF;
                    }
                } else {
                    if (func_001DE6D0(unit->pos >> 8) == 1) {
                        unit->unk4 = 0xA05;
                    } else {
                        unit->unk4 = 0x5FF;
                    }
                }
            }
        } else {
            switch (func_001E0700(unit->pos >> 8, unit->pos & 0xFF) >> 5) {
            case 0:
            case 1:
            case 3:
            case 4:
                func_00150850(unit);
                break;
            case 2:
                func_0027CA50(unit, 5, 0, (u8)func_00153ED0(handle));
                break;
            default:
                unit->unk4 = 0x5FF;
                break;
            }
        }
        return 1;
    }
    return 0;
}

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

s32 func_00150F10(s32 arg0, void *arg1) {
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
        s32 result = func_001514A0(arg0, (u8 *)data, arg1, 0x3E7);
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
    if (func_00151170(arg0, (u8 *)data, arg1) == 1) {
        return 3;
    }
    if (func_00153F30(arg0) == 1) {
        s32 result = func_001513B0(arg0, (u8 *)data, arg1, 0x2AE);
        if (result >= 0) {
            return 2;
        }
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
        s32 result = func_001514A0(arg0, (u8 *)data, arg1, 0x3E7);
        if (result >= 0) {
            return result;
        }
        return -1;
    }
}

typedef struct {
    u8 pad0[6];
    u8 slot[5];
} Obj1_00151170;

typedef struct {
    u8 pad0[0x38];
    s16 attack;
    s16 defense;
} Obj2_00151170;


s32 func_00151170(s32 arg0, void *arg1, void *arg2) {
    Obj2_00151170 *o2 = arg2;
    Obj1_00151170 *o1 = arg1;
    s32 list[8];
    s32 i;
    s32 found;
    u8 k;

    func_0026FD30(arg0, list);
    for (i = 0, found = 0; i < func_0026FE20(arg0); i++) {
        if (list[i] == 0x31F) {
            found = 1;
            o1->slot[0] = i;
        }
    }
    if (found == 0) {
        return -1;
    }
    for (i = 0, found = 0; i < func_0026FE20(arg0); i++) {
        if (list[i] == 7 && func_0026FB10(arg0, list[i]) == 1) {
            o1->slot[1] = i;
            found = 1;
        }
    }
    if (found == 0) {
        return -1;
    }
    k = 2;
    func_001DCD70(o2, 0x1F5);
    for (i = 0; i < func_0026FE20(arg0); i++) {
        if (i != o1->slot[0] && i != o1->slot[1]) {
            if (func_00248F60(0x1F5, list[i]) >= 0 && (func_0026FCE0(list[i]) >> 5) == 2) {
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

typedef struct Info_001516A0 {
    u8 pad00[8];
    u16 x;
    s16 y;
} Info_001516A0;

typedef struct Sprite_001516A0 {
    Info_001516A0 *info;
    u8 pad04[0x34];
    s16 x;
    s16 y;
} Sprite_001516A0;

u16 *func_00278A90(s32, u16 *, s32, s32, s32, s16 *, s16 *);

s32 func_001516A0(s32 arg0, u8 *arg1, void *arg2) {
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
                if ((func_0026FCE0(card) >> 5) == 0 && func_0026FB10(arg0, card) == 1) {
                    *node = func_00278A90(arg0, *node, i & 0xFF, card & 0xFFFF, 0, &a, &b);
                    *node = func_00278E40(*node);
                    value = func_00278F10(arg0, *node, 0, 0);
                    if (best < value) {
                        func_001DCD70(arg2, **node);
                        ((Sprite_001516A0 *)arg2)->x = (value >> 16) - (((Sprite_001516A0 *)arg2)->info->x & 0x1FFF);
                        ((Sprite_001516A0 *)arg2)->y = (value & 0xFFFF) - (((Sprite_001516A0 *)arg2)->info->y & 0x1FFF);
                        func_00151880(arg0, *node, entries);
                        func_00278DD0((u8 *)*node + 2, arg1 + 6);
                        best = value;
                        if (top < value) {
                            top = value;
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

typedef struct Nibbles_00151CF0 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_00151CF0;

s32 func_00151CF0(s32 arg0, u8 arg1, void *arg2, s32 arg3) {
    s32 bestPosition;
    s32 bestScore;
    Nibbles_00151CF0 cells[12];
    s32 targetY;
    s32 targetX;
    s32 kind;
    s32 type;
    s32 j;
    Nibbles_00151CF0 *cell;

    extern s32 func_00278510();
    extern s32 func_001DE020();
    extern s32 func_0027A130();
    extern s32 func_002792C0(s32, s32, s32, s32, s32, s32, u16, u8);

    if (arg2 == NULL) {
        return -1;
    }
    cell = cells;
    j = 0;
    do {
        cell->low = cell->high = 15;
        j++;
        cell++;
    } while (j < 12);
    kind = (type = (u8)(*((u8 *)arg2 + 0x3E) >> 5));
    if (kind == 0 || func_001DE020(kind, type) == 2) {
        if (arg3 >= 0) {
            s32 position;
            s32 y;
            s32 x;
            s32 i;
            s32 score;
            s32 target;
            bestScore = 255;
            bestPosition = 65535;
            target = func_001E1090(arg3 >> 8, arg3 & 255);
            i = 0;
            targetY = target >> 8;
            targetX = target & 255;
            do {
                position = func_0024E410(arg0, i);
                if (position >= 0) {
                    x = position & 255;
                    y = position >> 8;
                    if (func_001E22B0(x, y) != 8 &&
                        (func_001E22B0(x, y) != 9 || func_0024FE40(arg2, x, y) != 1) &&
                        func_001E36E0(x, y) == 0) {
                        if (func_00278510(arg2, arg3, func_00153ED0(arg0), targetX, targetY, 0) > 0) {
                            score = func_0027A130(arg2, cells, x, y, targetX, targetY,
                                                arg3, 0, 3, (u16)func_00153ED0(arg0));
                        } else {
                            score = func_002792C0((s32)arg2, (s32)cells, x, y, targetX, targetY, arg3, 3);
                        }
                        if (func_0027AFC0((u8 *)cells) > 0 && score < bestScore) {
                            bestScore = score;
                            bestPosition = position;
                        }
                    }
                }
                i++;
            } while (i < 8);
            if (bestPosition != 65535) {
                return bestPosition;
            }
        }
        {
        s32 y;
        s32 x;
        s32 i;
        s32 position;
        func_001E1090(arg3 >> 8, arg3 & 255);
        i = 0;
        do {
            position = func_0024E410(arg0, i);
            if (position >= 0) {
                x = position & 255;
                y = position >> 8;
                if (func_001E22B0(x, y) != 8 &&
                    (func_001E22B0(x, y) != 9 || func_0024FE40(arg2, x, y) != 1) &&
                    func_001E3790(x, y) < 0) {
                    return position;
                }
            }
            i++;
        } while (i < 8);
        return -1;
        }
    } else {
        s32 y;
        s32 x;
        s32 i;
        s32 result;
        s32 position;
        result = -1;
        i = 0;
        do {
            position = func_0024E410(arg0, i);
            if (position >= 0) {
                x = position & 255;
                y = position >> 8;
                if (func_001E22B0(x, y) != 8 &&
                    (func_001E22B0(x, y) != 9 || func_0024FE40(arg2, x, y) != 1) &&
                    func_001E3790(x, y) < 0 && y < 8) {
                    result = position;
                }
            }
            i++;
        } while (i < 8);
        if (result >= 0) {
            return result;
        }
        result = -1;
        return result;
    }
}

typedef struct Nibbles_00152100 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_00152100;

typedef struct Output_00152100 {
    u16 position;
    u8 action;
    u8 pad3;
    u16 destination;
    u8 pad6[6];
    s32 special;
    u8 result;
} Output_00152100;

void func_001E1E70(s32, s32, s32, s32);
s32 func_00276CC0(s32, s32, s32, s32, s32, u8);
s32 func_0027BE10(s32, s32, s32, s32, s32);

s32 func_00152100(u16 *arg0, s32 arg1, void *arg2, u8 arg3) {
    Output_00152100 *output = arg2;
    s32 target;
    u8 endX;
    u8 extra;
    Nibbles_00152100 nibbles[12];
    s32 bestScore;
    s32 best;
    s32 i;
    Nibbles_00152100 *p;
    extern s32 func_00153AE0();
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

        initialScore = func_00153ED0(arg1);
        centerX = target & 0xFF;
        centerY = target >> 8;
        if (func_00276CC0(centerX, centerY, *arg0, 3, initialScore, 0) == 0) {
            output->position = *arg0;
            output->action = 6;
            output->destination = target;
            output->result = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, output->destination, 1, 0);
            output->special = func_00153AE0(*arg0 >> 8, *arg0 & 0xFF, arg0);
            func_0027B1B0(arg0, arg3);
            return 0;
        }
        if ((range = func_002464F0(func_001DF540(*arg0 >> 8, *arg0 & 0xFF), centerX, centerY)) == 0) {
            output->position = *arg0;
            output->action = 6;
            output->destination = target;
            output->result = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, output->destination, 1, 0);
            output->special = func_00153AE0(*arg0 >> 8, *arg0 & 0xFF, arg0);
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
            extra = (u8)func_0027BBC0(*arg0 >> 8, *arg0 & 0xFF, 0);
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
                    if (func_0027BE10(*arg0 >> 8, *arg0 & 0xFF, x, y, 0) == 0 || (u8)*arg0 == 0) {
                        candidateScore = func_00276CC0(x, y, *arg0, 3, (u16)func_00153ED0(arg1), 0);
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
                output->result = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, output->destination, 1, 0);
            } else {
                output->result = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, output->destination, 0, 0);
            }
            output->special = func_00153AE0(*arg0 >> 8, *arg0 & 0xFF, arg0);
        } else {
            output->position = *arg0;
            output->action = 6;
            output->destination = target;
            output->result = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, output->destination, 1, 0);
            output->special = func_00153AE0(*arg0 >> 8, *arg0 & 0xFF, arg0);
        }
        func_0027B1B0(arg0, arg3);
        return 0;
    }
}

typedef struct Input_001526D0 {
    u16 position;
    u8 pad2[6];
    u32 destinations;
} Input_001526D0;

typedef struct Output_001526D0 {
    u16 position;
    u8 command;
    u8 pad3;
    u16 destination;
    u8 pad6[6];
    s32 state;
    u8 result;
} Output_001526D0;

typedef struct Point_001526D0 {
    u8 x : 4;
    u8 y : 4;
} Point_001526D0;

static inline u32 destination_001526D0(void *src, u8 mode) {
    if (mode == 1) {
        return (u16)(((Input_001526D0 *)src)->destinations >> 16);
    }
    return *(u16 *)((u8 *)src + 8);
}

s32 func_00276CC0(s32, s32, s32, s32, s32, u8);

s32 func_001526D0(void *src, s32 arg1, u16 *out, u8 arg3) {
    extern s32 func_00153AE0();
    extern void func_0027A090();
    s32 state;
    s32 current;
    s32 count;
    u8 mode;
    s32 target;
    s32 currentY;
    s32 currentX;
    s32 forced;
    s32 i;
    s32 unit;
    u32 destinationX;
    u32 destinationY;
    Point_001526D0 points[12];

    mode = func_00153AB0();
    destinationX = destination_001526D0(src, arg3);
    destinationY = destination_001526D0(src, arg3);
    if (func_001DF540(destinationY >> 8, destinationX & 0xFF) == 0) {
        func_0027B1B0(src, 1);
        return -1;
    }
    state = func_00153AE0(((Input_001526D0 *)src)->position >> 8,
                         ((Input_001526D0 *)src)->position & 0xFF, src);
    current = func_001E1090(((Input_001526D0 *)src)->position >> 8,
                           ((Input_001526D0 *)src)->position & 0xFF);
    destinationX = destination_001526D0(src, arg3);
    destinationY = destination_001526D0(src, arg3);
    target = func_001E1090(destinationY >> 8, destinationX & 0xFF);
    for (i = 0; i < 12; i++) {
        points[i].x = points[i].y = 0xF;
    }
    unit = func_001DF540(((Input_001526D0 *)src)->position >> 8,
                        ((Input_001526D0 *)src)->position & 0xFF);
    currentX = current & 0xFF;
    currentY = current >> 8;
    if (func_002464F0(unit, currentX, currentY) == 0) {
        s32 cost;
        ((Output_001526D0 *)out)->position = ((Input_001526D0 *)src)->position;
        ((Output_001526D0 *)out)->command = 6;
        ((Output_001526D0 *)out)->destination = current;
        cost = func_00276CC0(currentX, currentY, arg1, 3, 1,
                            (u8)func_00153ED0(arg1));
        if (cost >= func_001E0290(((Input_001526D0 *)src)->position >> 8,
                                 ((Input_001526D0 *)src)->position & 0xFF, 0)) {
            ((Output_001526D0 *)out)->result = func_0027E360(
                ((Input_001526D0 *)src)->position >> 8,
                ((Input_001526D0 *)src)->position & 0xFF,
                out[2], 1, 0);
        } else {
            ((Output_001526D0 *)out)->result = func_0027E360(
                ((Input_001526D0 *)src)->position >> 8,
                ((Input_001526D0 *)src)->position & 0xFF,
                out[2], 0, 0);
        }
        func_0027B1B0(src, arg3);
    } else {
        s32 y;
        s32 x;
        Point_001526D0 *point;
        s32 index;
        s32 bestCost;
        s32 selected;
        s32 position = ((Input_001526D0 *)src)->position;
        func_0027A090(position >> 8, position & 0xFF, points, currentX, currentY,
                      x = target & 0xFF, y = target >> 8,
                      destination_001526D0(src, arg3), 0, 30,
                      (u16)func_00153ED0(arg1));
        count = func_0027AFC0((u8 *)points);
        selected = 0xFF;
        if (count > 0) {
            forced = 0;
            bestCost = 0xFFFF;
            for (index = 0; index < count; index++) {
                s32 hit = func_00153DD0(((Input_001526D0 *)src)->position >> 8,
                                      ((Input_001526D0 *)src)->position & 0xFF,
                                      currentX, currentY, x, y);
                if (hit == 1) {
                    Point_001526D0 *forcedPoint = &points[index];
                    selected = index;
                    forced = 1;
                    index = count;
                    forcedPoint->x = x;
                    forcedPoint->y = y;
                } else {
                    s32 cost;
                    point = &points[index];
                    cost = func_00276CC0(point->x, point->y, arg1,
                                        (u8)(mode ? 5 : 2), 1,
                                        (u8)func_00153ED0(arg1));
                    if (cost < bestCost) {
                        bestCost = cost;
                        selected = index;
                    } else if (cost == bestCost) {
                        if (((x < point->x ? point->x : x) -
                             (point->x < x ? point->x : x)) +
                            ((y < point->y ? point->y : y) -
                             (point->y < y ? point->y : y)) <
                            ((x < points[selected].x ? points[selected].x : x) -
                             (points[selected].x < x ? points[selected].x : x)) +
                            ((y < points[selected].y ? points[selected].y : y) -
                             (points[selected].y < y ? points[selected].y : y))) {
                            bestCost = cost;
                            selected = index;
                        }
                    }
                }
            }
        } else {
            ((Output_001526D0 *)out)->position = ((Input_001526D0 *)src)->position;
            ((Output_001526D0 *)out)->command = 6;
            ((Output_001526D0 *)out)->destination = current;
            ((Output_001526D0 *)out)->state = state;
            ((Output_001526D0 *)out)->result = func_0027E360(
                ((Input_001526D0 *)src)->position >> 8,
                ((Input_001526D0 *)src)->position & 0xFF,
                ((Output_001526D0 *)out)->destination, 0, 0);
            func_0027B1B0(src, arg3);
            return 0;
        }
        if (selected != 0xFF) {
            ((Output_001526D0 *)out)->position = ((Input_001526D0 *)src)->position;
            ((Output_001526D0 *)out)->command = 6;
            ((Output_001526D0 *)out)->destination = (points[selected].y << 8) | points[selected].x;
            ((Output_001526D0 *)out)->state = forced;
            ((Output_001526D0 *)out)->result = func_0027E360(
                ((Input_001526D0 *)src)->position >> 8,
                ((Input_001526D0 *)src)->position & 0xFF,
                ((Output_001526D0 *)out)->destination, 0, 0);
        } else {
            ((Output_001526D0 *)out)->position = ((Input_001526D0 *)src)->position;
            ((Output_001526D0 *)out)->command = 6;
            ((Output_001526D0 *)out)->destination = current;
            ((Output_001526D0 *)out)->state = forced;
            ((Output_001526D0 *)out)->result = func_0027E360(
                ((Input_001526D0 *)src)->position >> 8,
                ((Input_001526D0 *)src)->position & 0xFF,
                ((Output_001526D0 *)out)->destination, 0, 0);
            func_0027B1B0(src, arg3);
            return 0;
        }
    }
    return 0;
}

typedef struct Coord_00152CD0 {
    u8 x : 4;
    u8 y : 4;
} Coord_00152CD0;

typedef struct Unit_00152CD0 {
    u16 position;
    u8 pad2[6];
    union {
        u32 packed;
        u16 low;
    } target;
} Unit_00152CD0;

typedef struct Output_00152CD0 {
    u16 position;
    u8 kind;
    u8 pad3;
    u16 target;
    u8 pad6[6];
    s32 value;
    u8 flag;
} Output_00152CD0;

void func_001E1E70(s32, s32, s32, s32);

static inline u32 target_00152CD0(void *unit, s32 side) {
    return side == 1 ? (u32)(u16)(((Unit_00152CD0 *)unit)->target.packed >> 16) : (u32)((Unit_00152CD0 *)unit)->target.low;
}

static inline u32 minY_00152CD0(void *unit, s32 side, u8 coord) {
    return coord < (target_00152CD0(unit, side) >> 8) ? coord : (target_00152CD0(unit, side) >> 8);
}

static inline u32 maxY_00152CD0(void *unit, s32 side, u8 coord) {
    return (target_00152CD0(unit, side) >> 8) < coord ? coord : (target_00152CD0(unit, side) >> 8);
}

static inline u32 minX_00152CD0(void *unit, s32 side, u8 coord) {
    return coord < (target_00152CD0(unit, side) & 0xFF) ? coord : (target_00152CD0(unit, side) & 0xFF);
}

static inline u32 maxX_00152CD0(void *unit, s32 side, u8 coord) {
    return (target_00152CD0(unit, side) & 0xFF) < coord ? coord : (target_00152CD0(unit, side) & 0xFF);
}

s32 func_00152CD0(void *arg0, s32 arg1, void *arg2, u8 arg3, u8 arg4) {
    extern s32 func_00153AE0();
    extern s32 func_00276CC0();
    extern void func_00279230();
    extern s32 func_0027E360(s32, s32, s32, u8, s32);
    Coord_00152CD0 coords[12];
    s32 initial;
    s32 cell;
    s32 count;
    u8 status;

    status = func_00153AB0();
    initial = func_001E1090(((Unit_00152CD0 *)arg0)->position >> 8, ((Unit_00152CD0 *)arg0)->position & 0xFF);
    {
        s32 bestScore;
        s32 best;
        s32 side = arg3;
        Coord_00152CD0 *candidate;
        s32 index;
        if (target_00152CD0(arg0, side) == 0xFFFF) {
            if (initial == target_00152CD0(arg0, side)) {
                ((Output_00152CD0 *)arg2)->position = ((Unit_00152CD0 *)arg0)->position;
                ((Output_00152CD0 *)arg2)->kind = 6;
                ((Output_00152CD0 *)arg2)->target = initial;
                ((Output_00152CD0 *)arg2)->flag = func_0027E360(((Unit_00152CD0 *)arg0)->position >> 8, ((Unit_00152CD0 *)arg0)->position & 0xFF, ((Output_00152CD0 *)arg2)->target, arg4, 0);
                ((Output_00152CD0 *)arg2)->value = func_00153AE0(((Unit_00152CD0 *)arg0)->position >> 8, ((Unit_00152CD0 *)arg0)->position & 0xFF, arg0);
                func_0027B1B0(arg0, arg3);
                return 0;
            }
        }

        if (func_001E2100(((Unit_00152CD0 *)arg0)->position >> 8, ((Unit_00152CD0 *)arg0)->position & 0xFF, 4) != 0) {
            if ((func_001E0700(((Unit_00152CD0 *)arg0)->position >> 8, ((Unit_00152CD0 *)arg0)->position & 0xFF) >> 5) == 1 ||
                (func_001E0700(((Unit_00152CD0 *)arg0)->position >> 8, ((Unit_00152CD0 *)arg0)->position & 0xFF) >> 5) == 5) {
                func_001E1E70(((Unit_00152CD0 *)arg0)->position >> 8, ((Unit_00152CD0 *)arg0)->position & 0xFF, 0, 1);
                ((Output_00152CD0 *)arg2)->position = ((Unit_00152CD0 *)arg0)->position;
                ((Output_00152CD0 *)arg2)->kind = 14;
                return 0;
            }
        }

        candidate = coords;
        {
            s32 i = 0;
            Coord_00152CD0 *entry = candidate;
            do {
                entry->x = entry->y = 0xF;
                i++;
                entry++;
            } while (i < 12);
        }

        cell = func_001E3790(target_00152CD0(arg0, side) & 0xFF, target_00152CD0(arg0, side) >> 8);
        if (cell < 0) {
            cell = 0xFFFF;
        }
        func_00279230(((Unit_00152CD0 *)arg0)->position >> 8, ((Unit_00152CD0 *)arg0)->position & 0xFF,
                     coords, initial & 0xFF, initial >> 8, target_00152CD0(arg0, side) & 0xFF,
                     target_00152CD0(arg0, side) >> 8, (u16)cell, 7);
        count = func_0027AFC0((u8 *)coords);
        {
            if (count > 0) {
                best = 0xFF;
                bestScore = 0xFFFF;
                for (index = 0; index < count; index++) {
                    if (func_001E36E0(candidate->x, candidate->y) == 0) {
                        s32 score = func_00276CC0(candidate->x, candidate->y, arg1, (u8)(status ? 5 : 2), 1, (u8)func_00153ED0(arg1));
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
                            bestMinY = minY_00152CD0(arg0, side, bestY);
                            bestMaxY = maxY_00152CD0(arg0, side, bestY);
                            bestX = (&coords[best])->x;
                            bestMinX = minX_00152CD0(arg0, side, bestX);
                            bestMaxX = maxX_00152CD0(arg0, side, bestX);
                            currentY = (u8)candidate->y;
                            currentMinY = minY_00152CD0(arg0, side, currentY);
                            currentMaxY = maxY_00152CD0(arg0, side, currentY);
                            currentX = candidate->x;
                            currentMinX = minX_00152CD0(arg0, side, currentX);
                            currentMaxX = maxX_00152CD0(arg0, side, currentX);
                            if ((currentMaxX - currentMinX) + (currentMaxY - currentMinY) < (bestMaxX - bestMinX) + (bestMaxY - bestMinY)) {
                                bestScore = score;
                                best = index;
                            }
                        }
                    }
                    candidate++;
                }
            } else {
                ((Output_00152CD0 *)arg2)->position = ((Unit_00152CD0 *)arg0)->position;
                ((Output_00152CD0 *)arg2)->kind = 6;
                ((Output_00152CD0 *)arg2)->target = initial;
                ((Output_00152CD0 *)arg2)->flag = func_0027E360(((Unit_00152CD0 *)arg0)->position >> 8, ((Unit_00152CD0 *)arg0)->position & 0xFF, ((Output_00152CD0 *)arg2)->target, arg4, 0);
                ((Output_00152CD0 *)arg2)->value = func_00153AE0(((Unit_00152CD0 *)arg0)->position >> 8, ((Unit_00152CD0 *)arg0)->position & 0xFF, arg0);
                func_0027B1B0(arg0, arg3);
                return 0;
            }

            if (best != 0xFF) {
                ((Output_00152CD0 *)arg2)->position = ((Unit_00152CD0 *)arg0)->position;
                ((Output_00152CD0 *)arg2)->kind = 6;
                ((Output_00152CD0 *)arg2)->target = (coords[best].y << 8) | coords[best].x;
                ((Output_00152CD0 *)arg2)->flag = func_0027E360(((Unit_00152CD0 *)arg0)->position >> 8, ((Unit_00152CD0 *)arg0)->position & 0xFF, ((Output_00152CD0 *)arg2)->target, arg4, 0);
                ((Output_00152CD0 *)arg2)->value = func_00153AE0(((Unit_00152CD0 *)arg0)->position >> 8, ((Unit_00152CD0 *)arg0)->position & 0xFF, arg0);
            } else {
                ((Output_00152CD0 *)arg2)->position = ((Unit_00152CD0 *)arg0)->position;
                ((Output_00152CD0 *)arg2)->kind = 6;
                ((Output_00152CD0 *)arg2)->target = initial;
                ((Output_00152CD0 *)arg2)->flag = func_0027E360(((Unit_00152CD0 *)arg0)->position >> 8, ((Unit_00152CD0 *)arg0)->position & 0xFF, ((Output_00152CD0 *)arg2)->target, arg4, 0);
                ((Output_00152CD0 *)arg2)->value = func_00153AE0(((Unit_00152CD0 *)arg0)->position >> 8, ((Unit_00152CD0 *)arg0)->position & 0xFF, arg0);
            }
            func_0027B1B0(arg0, arg3);
        }
    }
    return 0;
}

typedef struct Input_00153550 {
    u16 position;
    u8 pad2[6];
    u32 target;
} Input_00153550;

typedef struct Output_00153550 {
    u16 position;
    u8 action;
    u8 pad3;
    u16 destination;
    u8 pad6[10];
    u8 result;
} Output_00153550;

typedef struct Point_00153550 {
    u8 x : 4;
    u8 y : 4;
} Point_00153550;

#define MIN_00153550(a, b) ((a) < (b) ? (a) : (b))
#define MAX_00153550(a, b) ((b) < (a) ? (a) : (b))

s32 func_00276CC0(s32, s32, s32, s32, s32, u8);

static inline u32 target_00153550(void *src, s32 mode) {
    if (mode == 1) {
        return (u16)(((Input_00153550 *)src)->target >> 16);
    } else {
        return *(u16 *)((u8 *)src + 8);
    }
}

static inline void stay_00153550(void *src, void *dst, s32 position, s32 flag) {
    Input_00153550 *source = src;
    Output_00153550 *out = dst;

    out->position = source->position;
    out->action = 6;
    out->destination = position;
    out->result = func_0027E360(source->position >> 8, source->position & 0xFF,
                                out->destination, flag, 0);
}

s32 func_00153550(void *arg0, s32 arg1, void *arg2, s32 arg3) {
    s32 start;
    s32 count;
    u8 flag;
    s32 startY;
    Point_00153550 points[12];
    s32 bestScore;
    Point_00153550 *p;
    s32 targetY;
    s32 targetX;
    s32 i;
    s32 bestIndex;
    s32 mode;
    s32 target;
    s32 startX;
    u32 xPosition;
    u32 yPosition;
    Input_00153550 *source = arg0;
    Output_00153550 *out = arg2;
    extern void func_0027A090();

    flag = func_00153AB0();
    mode = arg3 & 0xFF;
    xPosition = target_00153550(arg0, mode);
    yPosition = target_00153550(arg0, mode);
    if (func_001DF540(yPosition >> 8, xPosition & 0xFF) == 0) {
        func_0027B1B0(arg0, 1);
        return -1;
    }
    start = func_001E1090(source->position >> 8, source->position & 0xFF);
    xPosition = target_00153550(arg0, mode);
    yPosition = target_00153550(arg0, mode);
    target = func_001E1090(yPosition >> 8, xPosition & 0xFF);
    if (target_00153550(arg0, mode) == 0xFFFF) {
        stay_00153550(arg0, arg2, start, 1);
        return 0;
    } else {
        s32 unit = func_001DF540(source->position >> 8, source->position & 0xFF);
        startX = start & 0xFF;
        startY = start >> 8;
        if (func_002464F0(unit, startX, startY) == 0 ||
                func_0027BBC0(source->position >> 8, source->position & 0xFF, 0) == 1) {
            stay_00153550(arg0, arg2, start, 1);
            return 0;
        } else {
            p = points;
            {
                s32 n = 0;
                Point_00153550 *q = p;
                do {
                    q->x = q->y = 0xF;
                    q++;
                    n++;
                } while (n < 12);
            }
            {
                s32 position = source->position;
                u16 card = (u16)func_00153ED0(arg1);
                func_0027A090(position >> 8, position & 0xFF, points,
                    startX, startY, targetX = target & 0xFF,
                    targetY = target >> 8, target_00153550(arg0, mode),
                    0, 30, card);
            }
            count = func_0027AFC0((u8 *)points);
            bestIndex = 0xFF;
            if (count > 0) {
                bestScore = 0;
                for (i = 0; i < count; i++, p++) {
                    if (func_001E36E0(p->x, p->y) == 0) {
                        s32 score = func_00276CC0(p->x, p->y, arg1, (u8)(flag ? 5 : 2), 1,
                            (u8)func_00153ED0(arg1));
                        if (bestScore < score) {
                            bestScore = score;
                            bestIndex = i;
                        } else if (score == bestScore) {
                            if (MAX_00153550(p->x, targetX) - MIN_00153550(p->x, targetX)
                                    + (MAX_00153550(p->y, targetY) - MIN_00153550(p->y, targetY))
                                    < MAX_00153550(points[bestIndex].x, targetX) - MIN_00153550(points[bestIndex].x, targetX)
                                    + (MAX_00153550(points[bestIndex].y, targetY) - MIN_00153550(points[bestIndex].y, targetY))) {
                                bestScore = score;
                                bestIndex = i;
                            }
                        }
                    }
                }
            } else {
                stay_00153550(arg0, arg2, start, 1);
                return 0;
            }
            if (bestIndex != 0xFF) {
                out->position = source->position;
                out->action = 6;
                out->destination = (points[bestIndex].y << 8) | points[bestIndex].x;
                out->result = func_0027E360(source->position >> 8,
                    source->position & 0xFF, out->destination, 0, 0);
            } else {
                stay_00153550(arg0, arg2, start, 1);
                return 0;
            }
        }
    }
    return 0;
}

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

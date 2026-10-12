#include "common.h"

s32 func_00153ED0(s32 arg0) {
    if (func_001DF470(arg0) > 1200) {
        if (func_001E0150(arg0) >= 4) {
            return 500;
        } else {
            return 1000;
        }
    } else {
        return 1500;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_013", func_00153F30);

typedef struct {
    u16 unk0;
    u8 unk2;
    u8 pad3;
    u16 unk4;
    u8 unk6[5];
    u8 padB;
    s32 unkC;
    u8 unk10;
} Req_00154040;

typedef struct {
    u8 pad0[0x160];
    u16 list[32];    /* 0x160 */
    u8 idx : 5;      /* 0x1A0 */
    u8 pad1A0 : 3;
    u8 pad1A1;
    u16 count;       /* 0x1A2 */
} Work_00154040;

s32 func_0014FD40(void *, void *, s32);
s32 func_00276290(void *, void *, s32);

s32 func_00154040(s32 arg0, void *arg1) {
    Req_00154040 req;
    Work_00154040 *w;
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
        if (func_0014FD40(w, &req, arg0) == 0) {
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

void func_00154210(void) {
    func_00172370();
}

INCLUDE_ASM("asm/nonmatchings/main_013", func_00154220);

INCLUDE_ASM("asm/nonmatchings/main_013", func_001547A0);

s32 func_00154AD0(u16 *arg0, s32 arg1, s32 arg2) {
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
    func_001547A0(arg0 + idx * 8);
    if (((arg0[idx * 8 + 2] >> 8) & 0xFF) == 10) {
        if (func_001DE6D0(arg1) == 1 && func_00155770(pos, arg1, arg2) >= 0) {
            return pos | 0x10000;
        }
        if (func_0027B9B0(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (func_001E2100(arg1, 0, 0) == 0) {
        if (func_0027B9B0(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (func_001DE6D0(arg1) == 1 && func_00155770(pos, arg1, arg2) >= 0) {
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

INCLUDE_ASM("asm/nonmatchings/main_013", func_00154EB0);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00155070);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00155230);

s32 func_001554B0(s32 arg0, s32 arg1, s32 arg2) {
    s32 i = 0;

    do {
        if (func_00155520(i, arg2) == ((arg1 << 8) | arg0)) {
            return 1;
        }
        i++;
    } while (i < 7);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_013", func_00155520);

s32 func_001555F0(s32 arg0) {
    s32 i;
    s32 temp_v0;

    i = 0;
    do {
        temp_v0 = func_00155520(i, arg0);
        if (((func_001E36E0(temp_v0 & 0xFF, temp_v0 >> 8) == 0) ? 1 : 0) == 1) {
            return func_00155520(i, arg0);
        }
        i++;
    } while (i < 7);
    return -1;
}

s32 func_00155670(s32 arg0, s32 arg1) {
    s32 i;
    s32 side;
    s32 otherSide;
    s32 position;
    s32 candidate;

    func_001E1090(arg0, arg1);
    func_00250360(arg0, arg1);
    side = func_001E0700(arg0, arg1) >> 5;
    otherSide = side != 0 ? 0 : side + 1;
    arg0 = (arg0 << 8) | arg1;

    i = 0;
    do {
        position = func_00155520(i, side);
        candidate = func_001E3790(position & 0xFF, position >> 8);
        if (candidate < 0) {
            return 0;
        }
        if (candidate == arg0) {
            return 1;
        }
    } while (++i < 7);

    i = 0;
    do {
        position = func_00155520(i, otherSide);
        candidate = func_001E3790(position & 0xFF, position >> 8);
        if (candidate < 0) {
            return 0;
        }
        if (candidate == arg0) {
            return 1;
        }
    } while (++i < 7);

    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_013", func_00155770);

s32 func_00155A00(s32 arg0, void *arg1) {
    extern s32 func_00278890();
    extern s32 func_00158800();
    s32 entries[8];
    u8 work[32];
    u8 kind0;
    u8 kind1;
    s32 i;
    s32 ret;

    kind0 = (u8)func_00278890(arg0, 0);
    kind1 = (u8)func_00278890(arg0, 1);
    if (arg1 == NULL) {
        return -1;
    }
    func_0026FD30(arg0, entries);
    if (kind0 == 5) {
        if (func_001562E0(arg0, work, arg1, 999) >= 0) {
            return 1;
        }
        return -1;
    }
    if (kind1 == 5) {
        for (i = 0; i < func_0026FE20(arg0); i++) {
            if ((func_0026FCE0(entries[i]) >> 5) == 0 &&
                func_0026FB10(arg0, entries[i]) == 1) {
                func_001DCD70(arg1, entries[i]);
                return 0;
            }
        }
        return -1;
    }
    for (i = 0; i < func_0026FE20(arg0); i++) {
        if (func_001DE020(func_0026FCE0(entries[i]) >> 5) == 2) {
            func_001DCD70(arg1, entries[i]);
            return 2;
        }
    }
    if (func_00158800(arg0) == 1) {
        if (func_00155C90(arg0, work, arg1) >= 0) {
            return 3;
        }
    }
    for (i = 0; i < func_0026FE20(arg0); i++) {
        if ((func_0026FCE0(entries[i]) >> 5) == 0 &&
            func_0026FB10(arg0, entries[i]) == 1) {
            return 0;
        }
    }
    ret = func_001562E0(arg0, work, arg1, 999);
    if (ret >= 0) {
        return ret;
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/main_013", func_00155C90);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00155FB0);

void func_001562B0(s32 *arg0, s32 arg1, s32 arg2) {
    s32 temp_a0;
    s32 *temp_a1;
    s32 *temp_a2;

    temp_a1 = &arg0[arg1];
    temp_a2 = &arg0[arg2];
    temp_a0 = *temp_a1;
    *temp_a1 = *temp_a2;
    *temp_a2 = temp_a0;
}

s32 func_001562E0(s32 arg0, u8 *arg1, void *arg2, s32 arg3) {
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

u16 *func_00278A90(s32, u16 *, s32, s32, s32, s16 *, s16 *);
s32 func_00278F10(s32, u16 *, s32, s32);

typedef struct Info_001564E0 {
    u8 pad[8];
    u16 x;
    s16 y;
} Info_001564E0;

typedef struct Sprite_001564E0 {
    Info_001564E0 *info;
    u8 pad[0x34];
    s16 x;
    s16 y;
} Sprite_001564E0;

s32 func_001564E0(s32 arg0, u8 *arg1, void *arg2) {
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
                    if (best < (value & 0xFFFF)) {
                        func_001566D0(arg0, *node, entries);
                        func_00278DD0((u8 *)*node + 2, arg1 + 6);
                        func_001DCD70(arg2, (s32)**node);
                        ((Sprite_001564E0 *)arg2)->x = (value >> 16) - (((Sprite_001564E0 *)arg2)->info->x & 0x1FFF);
                        ((Sprite_001564E0 *)arg2)->y = (value & 0xFFFF) - (((Sprite_001564E0 *)arg2)->info->y & 0x1FFF);
                        best = value;
                        if (top < (value & 0xFFFF)) {
                            top = value & 0xFFFF;
                        }
                    } else if (top < (value & 0xFFFF)) {
                        top = value & 0xFFFF;
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

void func_001566D0(s32 arg0, u16 *arg1, s32 *arg2) {
    s32 count;
    s32 i;
    s32 id;
    u8 limit;
    u8 buf[5];

    if (arg1 == NULL) {
        return;
    }
    limit = func_0026FA80(*arg1, arg0);
    for (i = 0; i < 5; i++) {
        buf[i] = 0xFF;
    }
    for (i = 0, count = 0; i < func_0026FE20(arg0); i++) {
        if ((u8)func_00278E00(i, (u8 *)(arg1 + 1)) == 0) {
            buf[count++] = i;
        }
    }
    if (count != 0) {
        for (i = 0; i < (u8)func_00278D90(buf); i++) {
            id = arg2[buf[i]];
            if (id != 999 && func_00156870(id) == 0 && limit >= func_0026FA80(id, arg0) &&
                (u16)func_002789F0(*arg1, (u16)id) == 999) {
                func_00278D20((u8 *)(arg1 + 1), buf[i]);
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/main_013", func_00156870);

s64 func_002493A0(s32);

typedef struct {
    u8 pad0[6];
    u8 slot[5];
} Obj1_00156910;

typedef struct {
    u8 pad0[0x38];
    s16 f38;
    s16 f3A;
    u16 id;
} Obj2_00156910;

s32 func_00156910(s32 arg0, void *arg1, void *arg2) {
    Obj1_00156910 *o1 = arg1;
    Obj2_00156910 *o2 = arg2;
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

INCLUDE_ASM("asm/nonmatchings/main_013", func_00156B40);

s32 func_00156EA0(void) {
    s32 i;
    s32 value;

    for (i = 0; i < 4; i++) {
        switch ((u8)i) {
        case 0:
            value = 0x303;
            break;
        case 1:
            value = 0x404;
            break;
        case 2:
            value = 0x402;
            break;
        case 3:
            value = 0x503;
            break;
        default:
            value = 0x503;
            break;
        }
        if (func_001E36E0(value & 0xFF, value >> 8) == 0) {
            return value;
        }
    }
    return -1;
}

s32 func_00156F70(void) {
    if (func_001E36E0(2, 3) == 0) {
        return 0x302;
    }
    return (func_001E36E0(4, 3) == 0) ? 0x304 : -1;
}

INCLUDE_ASM("asm/nonmatchings/main_013", func_00156FC0);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00157480);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00157A50);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00158360);

s32 func_00158780(s32 arg0) {
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

s32 func_001587E0(s32 arg0) {
    s32 result;

    result = (u32) (arg0 - 0x36) < 4U ? 1 : 0;
    return result;
}

void func_00158800(void) {
    func_00158810();
}

INCLUDE_ASM("asm/nonmatchings/main_013", func_00158810);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00158960);

typedef struct {
    u16 unk0;
    u8 unk2;
    u8 pad3;
    u16 unk4;
    u8 unk6[5];
    u8 padB;
    s32 unkC;
    u8 unk10;
} Req_00158AB0;

typedef struct {
    u8 pad0[0x160];
    u16 list[32];    /* 0x160 */
    u8 idx : 5;      /* 0x1A0 */
    u8 pad1A0 : 3;
    u8 pad1A1;
    u16 count;       /* 0x1A2 */
} Work_00158AB0;

s32 func_00154220(void *, void *, s32);
s32 func_00276290(void *, void *, s32);

s32 func_00158AB0(s32 arg0, void *arg1) {
    Req_00158AB0 req;
    Work_00158AB0 *w;
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
        if (func_00154220(w, &req, arg0) == 0) {
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

INCLUDE_ASM("asm/nonmatchings/main_013", func_00158C80);

INCLUDE_ASM("asm/nonmatchings/main_013", func_001591B0);

s32 func_00159380(u16 *arg0, s32 arg1, s32 arg2) {
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
    func_001591B0(arg0 + idx * 8);
    if (((arg0[idx * 8 + 2] >> 8) & 0xFF) == 10) {
        if (func_001DE6D0(arg1) == 1 && func_0015A360(pos, arg1, arg2) >= 0) {
            return pos | 0x10000;
        }
        if (func_0027B9B0(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (func_001E2100(arg1, 0, 0) == 0) {
        if (func_0027B9B0(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (func_001DE6D0(arg1) == 1 && func_0015A360(pos, arg1, arg2) >= 0) {
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

INCLUDE_ASM("asm/nonmatchings/main_013", func_00159760);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00159930);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00159BE0);

typedef struct {
    u16 card;
    u8 flag;
    u8 pad3;
} Slot_00159D00;

typedef struct {
    u16 low;
    u16 high;
} DataHalves_00159D00;

typedef struct {
    u16 coordinates;
    u8 pad2[2];
    u16 state;
    u8 pad6[2];
    union {
        u32 word;
        DataHalves_00159D00 halves;
    } data;
} Entry_00159D00;

void func_00159D00(void *arg0) {
    extern s32 func_0027B200();
    extern void func_0027E770();
    extern s32 func_00159F80();
    Entry_00159D00 *entry = arg0;
    s32 side;
    s32 player;
    s32 pos;
    s32 other;
    s32 otherPos;
    s32 i;
    u8 work[0x70];
    Slot_00159D00 list[22];
    s16 countA;
    s16 countB;

    if (func_001DF540(entry->coordinates >> 8, entry->coordinates & 0xFF) != 0) {
        func_0027E770(work);
        side = func_0024DE70(entry->coordinates >> 8, entry->coordinates & 0xFF);
        other = (side == 0 ? 1 : 0) << 8;
        pos = func_001E1090(entry->coordinates >> 8, entry->coordinates & 0xFF);
        otherPos = func_001E1090(other >> 8, other & 0xFF);
        player = func_001DF540(entry->coordinates >> 8, entry->coordinates & 0xFF);
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
            switch (func_00159F80(entry, 0, player, pos & 0xFF, pos >> 8,
                                  func_0024DE70(entry->coordinates >> 8, entry->coordinates & 0xFF) == 0 ? 1 : 0,
                                  (u8)i, func_0015D120(side), list, 0,
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
            default:
                break;
            }
            i++;
            if (i > 3) {
                break;
            }
        }
        entry->state = 0x6FF;
        entry->data.word = (otherPos << 16) | entry->data.halves.low;
    }
}

void func_00159F80(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28) {
    func_0027DE20(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
                  arg_sp0, arg_sp8, arg_sp10, arg_sp18, arg_sp20,
                  0, 2500, arg_sp28);
}

INCLUDE_ASM("asm/nonmatchings/main_013", func_00159FE0);

void func_0015A120(s32 a0, s32 a1, u16 *buf) {
    s32 i;

    for (i = 0; i < 0x31; i++) {
        buf[i] = 0xFFFF;
    }
    func_0015A180(a0, a1, buf);
    func_0015A320(buf);
}

static inline s32 upper_0015A180(s32 value) {
    if (value >= 7) {
        return 6;
    }
    return value;
}

void func_0015A180(s32 arg0, s32 arg1, u16 *arg2) {
    s32 var_s0;
    s32 var_s1;

    if ((func_0015A2E0((arg1 << 8) | arg0, arg2) != 1) && (func_001E22B0(arg0, arg1) == 9)) {
        arg2[func_0015A320(arg2)] = (arg1 << 8) | arg0;
        for (var_s0 = func_00250860(0, arg0 - 1); var_s0 <= upper_0015A180(arg0 + 1); var_s0++) {
            for (var_s1 = func_00250860(0, arg1 - 1); var_s1 <= upper_0015A180(arg1 + 1); var_s1++) {
                if (((((arg0 < var_s0) ? var_s0 : arg0) - ((var_s0 < arg0) ? var_s0 : arg0)) + (((arg1 < var_s1) ? var_s1 : arg1) - ((var_s1 < arg1) ? var_s1 : arg1))) == 1) {
                    func_0015A180(var_s0, var_s1, arg2);
                }
            }
        }
    }
}

s32 func_0015A2E0(s32 arg0, u16 *arg1) {
    s32 i;

    i = 0;
    do {
        if (arg0 == *arg1) {
            return 1;
        }
        i++;
        arg1++;
    } while (i < 0x31);
    return 0;
}

s32 func_0015A320(u16 *arg0) {
    s32 i;
    u8 count;

    count = 0;
    i = 0;
    do {
        if (*arg0 != 0xFFFF) {
            count++;
        }
        i++;
        arg0++;
    } while (i < 0x31);
    return count;
}

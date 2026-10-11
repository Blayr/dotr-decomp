#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_005", func_00114D40);

typedef struct {
    u16 id;
    u8 values[5];
} Info_00114F20;

void func_00114F20(s32 arg0, void *arg1, s32 *arg2) {
    Info_00114F20 *info = arg1;
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
                if (card != 0x3E7 && func_00115100(card) == 0 && level >= func_0026FA80(card, arg0)) {
                    cost = func_0026FBB0(card);
                    if ((cost & 0xFFFF) + (cost >> 16) * 2 < 0x1389 && func_0026FC10(card) == 2 &&
                        (u16)func_002789F0(info->id, (u16)card) == 0x3E7) {
                        func_00278D20(info->values, buf[i]);
                    }
                }
            }
        }
    }
}

s32 func_00115100(s32 arg0) {
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
} Obj1_00115160;

typedef struct {
    u8 pad0[0x3C];
    u16 id;
} Obj2_00115160;

s32 func_00115160(s32 arg0, void *arg1, void *arg2) {
    Obj1_00115160 *o1 = arg1;
    Obj2_00115160 *o2 = arg2;
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
            if (o2->id == list[i]) {
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

INCLUDE_ASM("asm/nonmatchings/main_005", func_00115340);

INCLUDE_ASM("asm/nonmatchings/main_005", func_00115850);

INCLUDE_ASM("asm/nonmatchings/main_005", func_00115E20);

INCLUDE_ASM("asm/nonmatchings/main_005", func_001162F0);

INCLUDE_ASM("asm/nonmatchings/main_005", func_00116B60);

INCLUDE_ASM("asm/nonmatchings/main_005", func_001170A0);

s32 func_00117340(void) {
    if (func_0027DD20(func_001DE540(), 3, 2) != 0 ||
        func_0027DD20(func_001DE540(), 3, 0x345) != 0 ||
        func_0024CA40(0, 0, func_001DE540(), 1, 0x2001C, 14) != 0) {
        return 1;
    }
    return 0;
}

s32 func_001173E0(s32 arg0) {
    s32 i;
    u8 n = 0;
    s32 need;
    u8 m;
    s32 j;

    if (func_001DF470(arg0) < 0x5DC) {
        return 0;
    }
    need = func_0027DD20(arg0, 3, 2) & 0xFF;
    if (need > 0) {
        for (i = 0; i < 8; i++) {
            if (func_0024E300(arg0, i, 1) >= 0) {
                n++;
            }
        }
        if (n >= need && 5 - func_001E0150(arg0) >= need) {
            return 1;
        }
    }
    m = 0;
    need = func_0027DD20(arg0, 3, 0) & 0xFF;
    if (need > 0) {
        for (j = 0; j < 8; j++) {
            if (func_0024E300(arg0, j, 1) >= 0) {
                m++;
            }
        }
        if (m >= need && 5 - func_001E0150(arg0) >= need) {
            return 1;
        }
    }
    return 0;
}

s32 func_00117550(s32 arg0) {
    s32 count;

    if (func_001DF470(arg0) < 0x5DC) {
        return 0;
    }
    count = func_0024CA40(0, 0, arg0, 1, 0x2001C, 14);
    count += func_0024CA40(0, 0, arg0, 1, 0x2001C, 14);
    if (count != 0) {
        if (func_001E0150(arg0) >= 4) {
            return 1;
        }
    }
    return 0;
}

s32 func_00117600(s32 arg0) {
    if (func_0024CA40(0, 0, arg0, 1, 0x2001C, 0xE) != 0) {
        return 1;
    }
    return (func_0024CA40(0, 0, arg0, 1, 0x1C, 0xE) != 0) ? 1 : 0;
}

s32 func_00117680(s32 arg0) {
    extern s32 func_001DEE50(s32);
    s32 i;

    if (func_001E0150(arg0) >= 5) {
        return -1;
    }
    if ((func_0027DD20(arg0, 3, 0) > 0 || func_0027DD20(arg0, 3, 2) > 0) &&
        func_0024CA40(0, 0, arg0, 1, 0x179001C, 0xE) == 0) {
        for (i = 0; i < func_001DEE50(arg0); i++) {
            if (func_001DEE00(arg0, i) == 2) {
                return (arg0 << 16) | i;
            }
        }
        for (i = 0; i < func_001DEE50(arg0 == 0 ? 1 : 0); i++) {
            if (func_001DEE00(arg0 == 0 ? 1 : 0, i) == 2) {
                return i | ((arg0 == 0 ? 1 : 0) << 16);
            }
        }
        for (i = 0; i < func_001DEE50(arg0); i++) {
            if (func_001DEE00(arg0, i) == 0) {
                return (arg0 << 16) | i;
            }
        }
        for (i = 0; i < func_001DEE50(arg0 == 0 ? 1 : 0); i++) {
            if (func_001DEE00(arg0 == 0 ? 1 : 0, i) == 0) {
                return i | ((arg0 == 0 ? 1 : 0) << 16);
            }
        }
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/main_005", func_00117870);

static inline s32 min_00117B10(s32 a, s32 b) {
    return (a < b) ? a : b;
}

static inline s32 max_00117B10(s32 a, s32 b) {
    return (a > b) ? a : b;
}

static inline s32 distance_00117B10(s32 x, s32 y) {
    return (max_00117B10(y, 3) - min_00117B10(y, 3)) +
           (max_00117B10(x, 3) - min_00117B10(x, 3));
}

s32 func_00117B10(s32 arg0) {
    s32 temp_s0;
    s32 temp_v0;

    if (arg0 == 0x303) {
        return 1;
    }
    temp_v0 = func_001E36E0(3, 3);
    if (temp_v0 != 0) {
        temp_s0 = func_00250370((void *) temp_v0);
        if (temp_s0 != func_001DE540()) {
            if (distance_00117B10(arg0 >> 8, arg0 & 0xFF) == 1) {
                return 1;
            }
        }
    }
    return 0;
}

s32 func_00117BD0(s32 arg0, s32 arg1) {
    s32 sp20[3];

    func_00254C90(sp20, *(s32 *)((u8 *)func_0026FC90(arg1, 0) + 4));
    if (func_00254890(sp20, arg0) < 0) {
        return 0;
    }
    return 1;
}

s32 func_00117C30(s32 arg0) {
    if (func_001DF470() > 0x4B0) {
        if (func_001E0150(arg0) >= 4) {
            return 0x2EE;
        } else {
            return 0x5DC;
        }
    } else {
        return 0x9C4;
    }
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
} Req_00117C90;

typedef struct {
    u8 pad0[0x160];
    u16 list[32];    /* 0x160 */
    u8 idx : 5;      /* 0x1A0 */
    u8 pad1A0 : 3;
    u8 pad1A1;
    u16 count;       /* 0x1A2 */
} Work_00117C90;

s32 func_00112B90(void *, void *, s32);
s32 func_00276290(void *, void *, s32);

s32 func_00117C90(s32 arg0, void *arg1) {
    Req_00117C90 req;
    Work_00117C90 *w;
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
        if (func_00112B90(w, &req, arg0) == 0) {
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

INCLUDE_ASM("asm/nonmatchings/main_005", func_00117E60);

INCLUDE_ASM("asm/nonmatchings/main_005", func_00118330);

s32 func_00118510(u16 *arg0, s32 arg1, s32 arg2) {
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
    func_00118330(arg0 + idx * 8);
    if (((arg0[idx * 8 + 2] >> 8) & 0xFF) == 10) {
        if (func_001DE6D0(arg1) == 1 && func_00119300(pos, arg1, arg2) >= 0) {
            return pos | 0x10000;
        }
        if (func_0027B9B0(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (func_001E2100(arg1, 0, 0) == 0) {
        if (func_0027B9B0(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (func_001DE6D0(arg1) == 1 && func_00119300(pos, arg1, arg2) >= 0) {
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

INCLUDE_ASM("asm/nonmatchings/main_005", func_001188F0);

void func_00118B60(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28) {
    func_0027DE20(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
                 arg_sp0, arg_sp8, arg_sp10, arg_sp18, arg_sp20,
                 0, 0x5DC, arg_sp28);
}

typedef struct {
    u16 id;
    u16 pad2;
    u16 state;
    u16 pad6;
    union {
        u32 word;
        u16 low;
    } data;
} State_00118BC0;

void func_00118BC0(void *arg0) {
    State_00118BC0 *state = arg0;
    s32 new_type;
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_s1;
    s32 temp_s1_2;
    s32 temp_s2;
    s32 temp_v0_2;
    u16 temp_v0;

    temp_s1 = func_001DE540();
    temp_v0 = state->id;
    temp_s2 = func_001E1090((s32) temp_v0 >> 8, temp_v0 & 0xFF);
    temp_s1_2 = func_00118DD0(temp_s1);
    temp_v0_2 = func_00118E90(temp_s1);
    temp_a2 = temp_s2 >> 8;
    switch (temp_a2) {
    case 0:
        if (temp_s2 == temp_s1_2) {
            state->state = 0xFFF;
        } else {
            state->state = 0x6FF;
            state->data.word = (temp_s1_2 << 16) | state->data.low;
        }
        break;
    case 6:
        if (temp_s2 == temp_v0_2) {
            state->state = 0x10FF;
        } else {
            state->state = 0x6FF;
            state->data.word = (temp_v0_2 << 16) | state->data.low;
        }
        break;
    default:
        temp_a1 = ((s32) state->state >> 8) & 0xFF;
        if ((temp_a1 != 0xF) && (temp_a1 != 0x10)) {
            new_type = (temp_a2 < 4) ? 0xF : 0x10;
            state->state = (new_type << 8) | 0xFF;
            state->data.word = state->data.low | 0xFFFF0000;
        }
        break;
    }
}

s32 func_00118CE0(s32 arg0, s32 arg1) {
    s32 index;
    s32 row;
    s32 low;
    s32 high;
    s32 slot;

    switch ((u8)arg1) {
    case 0:
        row = 2;
        break;
    case 1:
        row = 4;
        break;
    case 2:
        row = 0;
        break;
    case 3:
    default:
        row = 6;
        break;
    }
    index = 1;
    while (1) {
        slot = func_001E3790(row, index);
        if (slot >= 0) {
            high = slot >> 8;
            low = slot & 0xFF;
            if (arg0 == func_00250360(high, low) &&
                (func_001E0700(high, low) >> 5) == 0) {
                return 0;
            }
        }
        index++;
        if (index > 5) {
            return 1;
        }
    }
}

s32 func_00118DD0(s32 arg0) {
    s32 i;

    i = 0;
    do {
        if (func_00118CE0(arg0, (u8)i) != 0) {
            switch (i) {
            case 0:
                return 0x102;
            case 1:
                return 0x104;
            case 2:
                return 0x100;
            case 3:
            default:
                return 0x106;
            }
        }
        i++;
    } while (i < 4);
    return -1;
}

s32 func_00118E90(s32 arg0) {
    s32 i = 0;

    do {
        if (func_00118CE0(arg0, (u8)i) == 0) {
            switch (i) {
            case 0:
                return 0x602;
            case 1:
                return 0x604;
            case 2:
                return 0x600;
            case 3:
            default:
                return 0x606;
            }
        }
        i++;
    } while (i < 4);

    return -1;
}

typedef struct {
    u16 position;
    u8 flag;
    u8 pad;
} Slot_00118F50;

s32 func_00277CD0(s32, s32, s32, s32, void *, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_002774F0(s32, s32, void *, s32, s32, s32, s32, s32);

void func_00118F50(void *arg0) {
    u8 work[112];
    Slot_00118F50 slots[22];
    s16 c;
    s16 b;
    u16 a;
    s32 i;
    s32 player;
    s32 position;
    s32 owner;
    s32 state;
    s32 result;
    u16 *record = arg0;
    extern s32 func_002770E0();
    extern void func_0027E770();

    if (func_001DF540((s32) record[0] >> 8, record[0] & 0xFF) != 0) {
        player = func_0024DE70((s32) record[0] >> 8, record[0] & 0xFF);
        position = func_001E1090((s32) record[0] >> 8, record[0] & 0xFF);
        owner = func_001DF540((s32) record[0] >> 8, record[0] & 0xFF);
        record[2] = 0xBFF;
        for (i = 0; i < 22; i++) {
            slots[i].position = 0xFFFF;
            slots[i].flag = 0xFF;
        }
        func_0027E770(work);
        a = 0;
        b = 0;
        c = 0;
        state = 0;
        for (i = 1; i < 3; i++) {
            state = func_002770E0(state, owner, position & 0xFF, position >> 8,
                                  func_0024DE70((s32) record[0] >> 8, record[0] & 0xFF) == 0 ? 1 : 0, (u8) i, 0,
                                  func_0011AA10(player), slots, &a, &c, &b, work);
            result = func_00277CD0((s32) record[0] >> 8, record[0] & 0xFF, position & 0xFF, position >> 8,
                                   slots, 3, 0x1F, 1, 2, 0, func_0011AA10(player), a, 1);
            if (result >= 0) {
                *(u32 *) (record + 4) = (result << 16) | record[4];
                return;
            }
            result = func_00277CD0((s32) record[0] >> 8, record[0] & 0xFF, position & 0xFF, position >> 8,
                                   slots, 3, 0x1F, 0, 2, 0, func_0011AA10(player), a, 1);
            if (result >= 0) {
                *(u32 *) (record + 4) = (result << 16) | record[4];
                return;
            }
        }
        a = 0;
        b = 0;
        c = 0;
        state = 0;
        for (i = 1; i < 3; i++) {
            state = func_002770E0(state, owner, position & 0xFF, position >> 8,
                                  func_0024DE70((s32) record[0] >> 8, record[0] & 0xFF), (u8) i, 0,
                                  func_0011AA10(player), slots, &a, &c, &b, work);
            result = func_002774F0(position & 0xFF, position >> 8, slots, 3, 0x22, 2, 2, a);
            if (result >= 0) {
                *(u32 *) (record + 4) = (result << 16) | record[4];
                return;
            }
            result = func_002774F0(position & 0xFF, position >> 8, slots, 3, 0x1F, 1, 2, a);
            if (result >= 0) {
                *(u32 *) (record + 4) = (result << 16) | record[4];
                return;
            }
            result = func_002774F0(position & 0xFF, position >> 8, slots, 3, 0x1F, 0, 2, a);
            if (result >= 0) {
                *(u32 *) (record + 4) = (result << 16) | record[4];
                return;
            }
        }
        record[2] = 0x5FF;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_005", func_00119300);

INCLUDE_ASM("asm/nonmatchings/main_005", func_00119520);

INCLUDE_ASM("asm/nonmatchings/main_005", func_00119A40);

s32 func_00119D30(s32 arg0, u8 *arg1, void *arg2, s32 arg3) {
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

typedef struct Info_00119F30 {
    u8 pad0[6];
    u8 slots[5];
} Info_00119F30;

s32 func_00119F30(s32 arg0, void *arg1, s32 arg2) {
    Info_00119F30 *info = arg1;
    u16 cards[22];
    s32 ids[8];
    s32 i;
    s32 card;
    s32 type;

    for (i = 0; i < 22; i++) {
        cards[i] = 0xFFFF;
    }
    func_0024C910(arg0, 2, cards);
    func_0026FD30(arg0, ids);
    if (arg2 == 0) {
        return -1;
    }
    for (i = 0; i < 5; i++) {
        info->slots[i] = 0xFF;
    }
    card = func_0027B650(cards);
    if (card >= 0) {
        switch (func_001E0700(card >> 8, card & 0xFF) & 0x1F) {
        case 0xE:
            type = 0x2D2;
            break;
        case 2:
            type = 0x2D1;
            break;
        case 0x12:
            type = 0x2D4;
            break;
        default:
            type = 0x3E7;
            break;
        }
        if (type != 0x3E7) {
            for (i = 0; i < func_0026FE20(arg0); i++) {
                if (type == ids[i]) {
                    info->slots[0] = i;
                }
            }
            return type;
        }
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/main_005", func_0011A0D0);

typedef struct {
    u16 id;
    u8 values[5];
} Info_0011A2F0;

void func_0011A2F0(s32 arg0, void *arg1, s32 *arg2) {
    Info_0011A2F0 *info = arg1;
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
                if (card != 0x3E7 && level >= func_0026FA80(card, arg0)) {
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

void func_0011A4C0(void) {
    func_0024E410();
}

INCLUDE_ASM("asm/nonmatchings/main_005", func_0011A4D0);

s32 func_0011AA10(s32 arg0) {
    if (func_001DF470() > 0x5DC) {
        if (func_001E0150(arg0) >= 3) {
            return 0;
        } else {
            return 0;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_005", func_0011AA70);

INCLUDE_ASM("asm/nonmatchings/main_005", func_0011B0E0);

INCLUDE_ASM("asm/nonmatchings/main_005", func_0011B680);

s32 func_0011C140(s32 arg0, s32 arg1, u32 *arg2) {
    /* really takes (arg0, arg1); the header says (void) */
    s32 func_001E1030();
    u8 info[32];
    u32 *entry;

    if (func_001E2100(arg0, arg1, 4) != 0) {
        return 0;
    }
    switch (func_001E0700(arg0, arg1) >> 5) {
    case 0:
        return 2;
    case 1:
        if (func_0027D830(arg0, arg1, 0, 0, 6, 0) == 5) {
            return 2;
        }
        entry = func_00250740(arg0, arg1, 0);
        if (entry == NULL) {
            return 2;
        }
        switch (*entry >> 8) {
        case 2:
            if ((u16)(arg2[2] >> 16) == func_001E1090(arg0, arg1)) {
                return 1;
            }
            break;
        case 0xD:
            return 1;
        default:
            if (func_001E1030(arg0, arg1) ==
                func_00119F30(func_00250360(arg0, arg1), info, func_001DF540(arg0, arg1))) {
                return 1;
            }
            break;
        }
        return 2;
    }
    return 2;
}

INCLUDE_ASM("asm/nonmatchings/main_005", func_0011C2E0);

typedef struct {
    u8 pad[8];
    u32 value;
} Data_0011C3E0;

void func_0011C3E0(void *arg0, u8 arg1) {
    Data_0011C3E0 *data = arg0;

    if (arg1 < 2) {
        if (arg1 == 1) {
            data->value = (data->value & 0xFFFF) | 0xFFFF0000;
        } else {
            data->value = (data->value & 0xFFFF0000) | 0xFFFF;
        }
    }
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
} Req_0011C430;

typedef struct {
    u8 pad0[0x160];
    u16 list[32];    /* 0x160 */
    u8 idx : 5;      /* 0x1A0 */
    u8 pad1A0 : 3;
    u8 pad1A1;
    u16 count;       /* 0x1A2 */
} Work_0011C430;

s32 func_00117E60(void *, void *, s32);
s32 func_00276290(void *, void *, s32);

s32 func_0011C430(s32 arg0, void *arg1) {
    Req_0011C430 req;
    Work_0011C430 *w;
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
        if (func_00117E60(w, &req, arg0) == 0) {
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

INCLUDE_ASM("asm/nonmatchings/main_005", func_0011C600);

INCLUDE_ASM("asm/nonmatchings/main_005", func_0011CB20);

s32 func_0011CD30(u16 *arg0, s32 arg1, s32 arg2) {
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
    func_0011CB20(arg0 + idx * 8);
    if (((arg0[idx * 8 + 2] >> 8) & 0xFF) == 10) {
        if (func_001DE6D0(arg1) == 1 && func_0011DFB0(pos, arg1, arg2) >= 0) {
            return pos | 0x10000;
        }
        if (func_0027B9B0(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (func_001E2100(arg1, 0, 0) == 0) {
        if (func_0027B9B0(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (func_001DE6D0(arg1) == 1 && func_0011DFB0(pos, arg1, arg2) >= 0) {
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

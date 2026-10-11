#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_014", func_0015A360);

INCLUDE_ASM("asm/nonmatchings/main_014", func_0015A5F0);

s32 func_0015A820(s32 arg0, void *arg1, void *arg2, s32 arg3) {
    s32 entries[8];
    s32 index;
    s32 *entry;
    s32 key;

    func_0026FD30(arg0, entries);
    index = 0;
    if (index < func_0026FE20(arg0)) {
        key = arg3 & 0xFFFF;
        entry = entries;
        do {
            if (key == *entry && func_0026FB10(arg0, *entry) == 1) {
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

s32 func_0015A910(s32 arg0, u8 *arg1, void *arg2, s32 arg3) {
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

INCLUDE_ASM("asm/nonmatchings/main_014", func_0015AB10);

s64 func_002493A0(s32);

typedef struct {
    u8 pad0[6];
    u8 slot[5];
} Obj1_0015AD00;

typedef struct {
    u8 pad0[0x38];
    s16 f38;
    s16 f3A;
    u16 id;
} Obj2_0015AD00;

s32 func_0015AD00(s32 arg0, void *arg1, void *arg2) {
    Obj1_0015AD00 *o1 = arg1;
    Obj2_0015AD00 *o2 = arg2;
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

INCLUDE_ASM("asm/nonmatchings/main_014", func_0015AF30);

INCLUDE_ASM("asm/nonmatchings/main_014", func_0015B250);

INCLUDE_ASM("asm/nonmatchings/main_014", func_0015B820);

INCLUDE_ASM("asm/nonmatchings/main_014", func_0015BE00);

INCLUDE_ASM("asm/nonmatchings/main_014", func_0015C670);

s32 func_0015CBB0(s32 arg0, s32 arg1) {
    s32 kind;
    s32 pos;
    s32 slot;
    u32 *card;

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
        case 0xE0:
            if (func_001DE5C0(slot) < 2) {
                return 1;
            }
            break;
        case 0x28C:
            if (func_0024E910(func_0024CA40(pos & 0xFF, pos >> 8, slot, 1, 0x34, 0x14)) > 1) {
                return 2;
            }
            if (func_0024E910(func_0024CA40(pos & 0xFF, pos >> 8, slot, 2, 0x34, 0x14)) > 5) {
                return 1;
            }
            break;
        case 0x28F:
            if (func_0024E910(func_0024CA40(0, 0, arg0, 2, 0x34, 0xE)) > 5) {
                return 1;
            }
            break;
        }
        return 2;
    case 5:
        if (func_0027D830(arg0, arg1, 0, 0, 6, 0) == 5) {
            return 2;
        }
        if (func_0015D030(func_00250360(arg0, arg1), kind) == 1 &&
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
        case 0x18:
            if (func_0024E910(func_0024CA40(0, 0, arg0, 2, 0x34, 0xE)) > 5) {
                return 1;
            }
            break;
        case 0x12:
            if (func_0024E910(func_0024CA40(pos & 0xFF, pos >> 8, slot, 1, 0x1D, 0x1D)) > 0) {
                return 2;
            }
            if (func_0024E910(func_0024CA40(0, 0, slot, 1, 0x13, 0xE)) > 2) {
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

static inline s32 max_0015CF30(s32 a, s32 b) {
    if (b < a) {
        return a;
    }
    return b;
}

s32 func_0015CF30(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 minY;
    s32 minX;

    minY = (arg3 < arg5) ? arg3 : arg5;
    arg5 = max_0015CF30(arg3, arg5);
    minX = (arg2 < arg4) ? arg2 : arg4;
    arg4 = max_0015CF30(arg2, arg4);

    if (((arg4 - minX) + (arg5 - minY)) != 2) {
        return 0;
    }
    if (func_001DF540(arg0, arg1) == 0) {
        return 0;
    }
    if (func_001E2100(arg0, arg1, 0) == 0) {
        return (func_0024DF00(func_001E22B0(arg2, arg3), arg0, arg1) != 1) ? 0 : 1;
    }
    return 0;
}

s32 func_0015D030(s32 arg0, s32 arg1) {
    s32 data[4];
    s32 index;
    s32 mask;
    s32 low;
    s32 high;
    s32 value;

    func_00254C90(data, *(s32 *)((u8 *)func_0026FC90(arg1, 0) + 4));
    if ((mask = func_00254890(data, arg0)) < 0) {
        return 0;
    }
    for (index = 0; index < func_0024E910(mask); index++) {
        value = func_0024EC50(mask, index);
        high = value >> 8;
        low = value & 0xFF;
        value = func_001E1090(high, low);
        if (func_002509E0(high, low, value & 0xFF, value >> 8) >= 0) {
            return 0;
        }
    }
    return 1;
}

s32 func_0015D120(s32 arg0) {
    if (func_001DF470(arg0) > 0x4B0) {
        if (func_001E0150(arg0) >= 5) {
            return 0x2EE;
        } else {
            return 0x5DC;
        }
    } else {
        return 0x7D0;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_014", func_0015D180);

INCLUDE_ASM("asm/nonmatchings/main_014", func_0015D350);

INCLUDE_ASM("asm/nonmatchings/main_014", func_0015D8E0);

s32 func_0015DAF0(u16 *arg0, s32 arg1, s32 arg2) {
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
    func_0015D8E0(arg0 + idx * 8);
    if (((arg0[idx * 8 + 2] >> 8) & 0xFF) == 10) {
        if (func_001DE6D0(arg1) == 1 && func_0015F300(pos, arg1, arg2) >= 0) {
            return pos | 0x10000;
        }
        if (func_0027B9B0(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (func_001E2100(arg1, 0, 0) == 0) {
        if (func_0027B9B0(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (func_001DE6D0(arg1) == 1 && func_0015F300(pos, arg1, arg2) >= 0) {
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

typedef struct Action_0015DED0 {
    u16 location;
    u16 unk2;
    s16 state;
    u16 unk6;
    union {
        u32 value;
        u16 low;
    } data;
} Action_0015DED0;

void func_0015E030(void *);
void func_0015E520(void *, s32);

void func_0015DED0(void *arg0) {
    s32 other;
    s32 result;
    Action_0015DED0 *action = arg0;

    if (func_001DF540(action->location >> 8, action->location & 0xFF) != 0) {
        other = (func_0024DE70(action->location >> 8, action->location & 0xFF) == 0 ? 1 : 0) << 8;
        func_001E1090(action->location >> 8, action->location & 0xFF);
        func_001E1090(other >> 8, other & 0xFF);
        func_001DF540(action->location >> 8, action->location & 0xFF);
        if (func_001E0290(action->location >> 8, action->location & 0xFF, 0) >= 2500) {
            func_0015E030(arg0);
            return;
        }
        if (func_0015E440(action->location >> 8, action->location & 0xFF, 1) == 1) {
            func_0015E520(arg0, 1);
            return;
        }
        result = func_0015E2E0(action->location >> 8, action->location & 0xFF);
        if (result >= 0) {
            action->state = 0x6FF;
            action->data.value = (result << 16) | action->data.low;
            return;
        }
        if (func_0015E440(action->location >> 8, action->location & 0xFF, 2) == 1) {
            func_0015E520(arg0, 2);
            return;
        }
        func_0015E030(arg0);
    }
}

INCLUDE_ASM("asm/nonmatchings/main_014", func_0015E030);

s32 func_0015E2E0(s32 arg0, s32 arg1) {
    s32 temp_s0;
    s32 temp_s2;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;

    temp_v0 = func_00250360(arg0, arg1);
    if (func_0024CA40(0, 0, temp_v0, 1, 0x033B001C, 14) != 0) {
        temp_v0_2 = func_001E3790(0, 5);
        if (temp_v0_2 >= 0) {
            if (temp_v0_2 == ((arg0 << 8) | arg1)) {
                return 0x500;
            }
            temp_s2 = func_00250360(temp_v0_2 >> 8, temp_v0_2 & 0xFF);
            if (temp_s2 != func_00250360(arg0, arg1)) {
                return 0x500;
            }
        } else {
            return 0x500;
        }
    }
    if (func_0024CA40(0, 0, temp_v0, 1, 0x02ED001C, 14) != 0) {
        temp_v0_3 = func_001E3790(6, 3);
        if (temp_v0_3 >= 0) {
            if (temp_v0_3 == ((arg0 << 8) | arg1)) {
                return 0x306;
            }
            temp_s0 = func_00250360(temp_v0_3 >> 8, temp_v0_3 & 0xFF);
            if (temp_s0 != func_00250360(arg0, arg1)) {
                return 0x306;
            }
        } else {
            return 0x306;
        }
    }
    return -1;
}

s32 func_0015E440(s32 arg0, s32 arg1, s32 arg2) {
    s32 otherType;
    s32 card;
    s32 i;
    s32 mode;
    s32 key;

    if ((arg2 & 0xFF) == 1) {
        mode = 3;
    } else {
        mode = 4;
    }
    key = (arg0 << 8) | arg1;
    i = 1;
    do {
        card = func_001E3790(i, mode);
        if (card != 0) {
            if (card == key) {
                return 1;
            }
            otherType = func_00250360(card >> 8, card & 0xFF);
            if (otherType == func_00250360(arg0, arg1)) {
                return 0;
            }
        }
        i++;
        if (i > 5) {
            return 1;
        }
    } while (1);
}

INCLUDE_ASM("asm/nonmatchings/main_014", func_0015E520);

void func_0015E8F0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28) {
    func_0027DE20(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
                  arg_sp0, arg_sp8, arg_sp10, arg_sp18, arg_sp20,
                  0, 2500, arg_sp28);
}

INCLUDE_ASM("asm/nonmatchings/main_014", func_0015E950);

typedef struct {
    u32 field0;
    u16 field4;
    u16 field6;
    union {
        u32 word;
        struct {
            u32 lower : 16;
            u32 upper : 16;
        } bits;
    } field8;
} Item_0015EC60;

s32 func_0015EE40(void);

static inline void set_index_0015EC60(void *arg, s32 index) {
    Item_0015EC60 *item = arg;

    item->field4 = 0x3FF;
    item->field8.word = (index << 16) | item->field8.bits.lower;
}

void func_0015EC60(s32 arg0, s32 arg1, void *arg2) {
    Item_0015EC60 *item = arg2;
    s32 index;
    s32 next;

    func_00250360(arg0, arg1);
    index = func_001E1090(arg0, arg1);
    if (func_0015ED30(index & 0xFF, index >> 8) == 1) {
        set_index_0015EC60(item, index);
    } else {
        set_index_0015EC60(item, index);
    }
    next = func_0015EE40();
    if (next >= 0) {
        set_index_0015EC60(item, next);
    } else {
        func_0015DED0(item);
    }
}

s32 func_0015ED30(s32 arg0, s32 arg1) {
    s32 var_s0;

    var_s0 = 0;
loop_1:
    if (((arg1 << 8) | arg0) == func_0015ED90(var_s0)) {
        return 1;
    }
    var_s0 += 1;
    if (var_s0 >= 4) {
        return 0;
    }
    goto loop_1;
}

s32 func_0015ED90(s32 arg0) {
    extern s32 func_001604A0();
    s32 temp;

    temp = func_001DE540();
    switch (arg0) {
    case 0:
        return func_001604A0(temp, 0);
    case 1:
        return func_001604A0(temp, 3);
    case 2:
        return func_001604A0(temp, 4);
    case 3:
        return func_001604A0(temp, 5);
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/main_014", func_0015EE40);

INCLUDE_ASM("asm/nonmatchings/main_014", func_0015EF40);

INCLUDE_ASM("asm/nonmatchings/main_014", func_0015F300);

INCLUDE_ASM("asm/nonmatchings/main_014", func_0015F5E0);

s32 func_0015FA00(s32 arg0, void *arg1, void *arg2) {
    s32 cards[8];
    s32 i;
    s32 found;
    s32 *entry;
    s32 *entry2;
    s32 j;
    s32 found2;
    s32 card;

    func_0026FD30(arg0, cards);
    i = 0;
    found = 0;
    if (0 < func_0026FE20(arg0)) {
        entry = cards;
        do {
            if (*entry == 0x316) {
                found = 1;
                ((u8 *)arg1)[6] = i;
            }
            entry++;
            i++;
        } while (i < func_0026FE20(arg0));
    }
    if (found == 0) {
        return -1;
    }
    j = 0;
    found2 = 0;
    if (0 < func_0026FE20(arg0)) {
        entry2 = cards;
        do {
            card = *entry2;
            if ((card == 0x129) && (func_0026FB10(arg0, card) == 1)) {
                ((u8 *)arg1)[7] = j;
                found2 = 1;
            }
            entry2++;
            j++;
        } while (j < func_0026FE20(arg0));
    }
    if (found2 == 0) {
        return -1;
    }
    func_001DCD70(arg2, 0x129);
    return 1;
}

s32 func_0015FB60(s32 arg0, void *arg1, void *arg2, s32 arg3) {
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

s32 func_0015FC50(s32 arg0, u8 *arg1, void *arg2, s32 arg3) {
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

INCLUDE_ASM("asm/nonmatchings/main_014", func_0015FE50);

typedef struct {
    u16 id;
    u8 values[5];
} Info_00160030;

void func_00160030(s32 arg0, void *arg1, s32 *arg2) {
    Info_00160030 *info = arg1;
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
                if (card != 0x3E7 && func_00160210(card) == 0 && level >= func_0026FA80(card, arg0)) {
                    cost = func_0026FBB0(card);
                    if ((cost & 0xFFFF) + (cost >> 16) * 2 < 0xFA1 && func_0026FC10(card) == 2 &&
                        (u16)func_002789F0(info->id, (u16)card) == 0x3E7) {
                        func_00278D20(info->values, buf[i]);
                    }
                }
            }
        }
    }
}

s32 func_00160210(s32 arg0) {
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
} Obj1_00160270;

typedef struct {
    u8 pad0[0x38];
    s16 f38;
    s16 f3A;
    u16 id;
} Obj2_00160270;

s32 func_00160270(s32 arg0, void *arg1, void *arg2) {
    Obj1_00160270 *o1 = arg1;
    Obj2_00160270 *o2 = arg2;
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

void func_001604A0(s32 unused0, s32 unused1) {
    func_0024E410(unused0, unused1);
}

INCLUDE_ASM("asm/nonmatchings/main_014", func_001604B0);

INCLUDE_ASM("asm/nonmatchings/main_014", func_001607D0);

INCLUDE_ASM("asm/nonmatchings/main_014", func_00160DA0);

INCLUDE_ASM("asm/nonmatchings/main_014", func_00161380);

INCLUDE_ASM("asm/nonmatchings/main_014", func_00161BF0);

INCLUDE_ASM("asm/nonmatchings/main_014", func_00161EA0);

s32 func_001620B0(s32 arg0, s32 arg1) {
    s32 s0;
    s32 s1;
    s32 s2;
    u32 *s3;
    s32 a;
    s32 b;

    s0 = func_001E1030();
    s1 = func_001E1090(arg0, arg1);
    s2 = func_00250360(arg0, arg1);
    s3 = func_001E0B70(arg0, arg1, 0);
    if (func_001E2100(arg0, arg1, 4) != 0) {
        return 0;
    }
    switch (func_001E0700(arg0, arg1) >> 5) {
    case 5:
        if (func_0027D830(arg0, arg1, 0, 0, 6, 0) == 5) {
            return 2;
        }
        if (func_00162490(func_00250360(arg0, arg1), s0) == 1) {
            if (func_001E22B0(s1 & 0xFF, s1 >> 8) != 9) {
                return 1;
            }
        }
        break;
    case 1:
        if (func_0027D830(arg0, arg1, 0, 0, 6, 0) == 5) {
            return 2;
        }
        if (s3 == NULL) {
            return 2;
        }
        switch (*s3 >> 8) {
        case 4:
            a = func_001625E0(s2);
            s1 = func_001E1090(arg0, arg1);
            b = func_001E1090(a >> 8, a & 0xFF);
            if ((s1 & 0xFF) == (b & 0xFF) || (s1 >> 8) == (b >> 8)) {
                return 1;
            }
            break;
        case 0x49:
            if (func_001626F0(s2) == 1) {
                return 1;
            }
            break;
        case 0x25:
            if (s0 == 0x2ED && func_0027BBC0(arg0, 0, 0) == 1) {
                return 1;
            }
            if (s0 == 0x2EA && func_0027BBC0(arg0, arg1, 0) == 1) {
                return 1;
            }
            break;
        case 0x1F:
            if (s0 == 0x2DD && func_00162D10(s2) == 1) {
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

static inline s32 max_00162390(s32 a, s32 b) {
    if (a < b) {
        return b;
    }
    return a;
}

s32 func_00162390(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 min_y;
    s32 min_x;

    min_y = (arg3 < arg5) ? arg3 : arg5;
    arg5 = max_00162390(arg5, arg3);
    min_x = (arg2 < arg4) ? arg2 : arg4;
    arg4 = max_00162390(arg4, arg2);
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

s32 func_00162490(s32 arg0, s32 arg1) {
    s32 i;
    s32 mask;
    s32 low;
    s32 high;
    s32 packed;
    s32 position;
    s32 sp50[4];

    func_00254C90(sp50, *(s32 *)((u8 *)func_0026FC90(arg1, 0) + 4));
    if ((mask = func_00254890(sp50, arg0)) < 0) {
        return 0;
    }

    i = 0;
    if (i < func_0024E910(mask)) {
        do {
            packed = func_0024EC50(mask, i);
            high = packed >> 8;
            low = packed & 0xFF;
            position = func_001E1090(high, low);
            if (func_002509E0(high, low, position & 0xFF, position >> 8) >= 0xBB8) {
                return 0;
            }
            i++;
        } while (i < func_0024E910(mask));
    }
    return 1;
}

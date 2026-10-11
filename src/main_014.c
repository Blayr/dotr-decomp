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

INCLUDE_ASM("asm/nonmatchings/main_014", func_0015A910);

INCLUDE_ASM("asm/nonmatchings/main_014", func_0015AB10);

INCLUDE_ASM("asm/nonmatchings/main_014", func_0015AD00);

INCLUDE_ASM("asm/nonmatchings/main_014", func_0015AF30);

INCLUDE_ASM("asm/nonmatchings/main_014", func_0015B250);

INCLUDE_ASM("asm/nonmatchings/main_014", func_0015B820);

INCLUDE_ASM("asm/nonmatchings/main_014", func_0015BE00);

INCLUDE_ASM("asm/nonmatchings/main_014", func_0015C670);

INCLUDE_ASM("asm/nonmatchings/main_014", func_0015CBB0);

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
    if (func_001DF470() > 0x4B0) {
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

INCLUDE_ASM("asm/nonmatchings/main_014", func_0015DAF0);

INCLUDE_ASM("asm/nonmatchings/main_014", func_0015DED0);

INCLUDE_ASM("asm/nonmatchings/main_014", func_0015E030);

INCLUDE_ASM("asm/nonmatchings/main_014", func_0015E2E0);

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

void func_0015DED0(void *);
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

INCLUDE_ASM("asm/nonmatchings/main_014", func_0015ED90);

INCLUDE_ASM("asm/nonmatchings/main_014", func_0015EE40);

INCLUDE_ASM("asm/nonmatchings/main_014", func_0015EF40);

INCLUDE_ASM("asm/nonmatchings/main_014", func_0015F300);

INCLUDE_ASM("asm/nonmatchings/main_014", func_0015F5E0);

INCLUDE_ASM("asm/nonmatchings/main_014", func_0015FA00);

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

INCLUDE_ASM("asm/nonmatchings/main_014", func_0015FC50);

INCLUDE_ASM("asm/nonmatchings/main_014", func_0015FE50);

INCLUDE_ASM("asm/nonmatchings/main_014", func_00160030);

s32 func_00160210(s32 arg0) {
    if ((func_0026FCE0(arg0) >> 5) != 0) {
        return 1;
    }
    if (func_0026FC10(arg0) == 1) {
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_014", func_00160270);

void func_001604A0(void) {
    func_0024E410();
}

INCLUDE_ASM("asm/nonmatchings/main_014", func_001604B0);

INCLUDE_ASM("asm/nonmatchings/main_014", func_001607D0);

INCLUDE_ASM("asm/nonmatchings/main_014", func_00160DA0);

INCLUDE_ASM("asm/nonmatchings/main_014", func_00161380);

INCLUDE_ASM("asm/nonmatchings/main_014", func_00161BF0);

INCLUDE_ASM("asm/nonmatchings/main_014", func_00161EA0);

INCLUDE_ASM("asm/nonmatchings/main_014", func_001620B0);

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

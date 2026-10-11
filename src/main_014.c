#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_014", func_0015A360);

INCLUDE_ASM("asm/nonmatchings/main_014", func_0015A5F0);

INCLUDE_ASM("asm/nonmatchings/main_014", func_0015A820);

INCLUDE_ASM("asm/nonmatchings/main_014", func_0015A910);

INCLUDE_ASM("asm/nonmatchings/main_014", func_0015AB10);

INCLUDE_ASM("asm/nonmatchings/main_014", func_0015AD00);

INCLUDE_ASM("asm/nonmatchings/main_014", func_0015AF30);

INCLUDE_ASM("asm/nonmatchings/main_014", func_0015B250);

INCLUDE_ASM("asm/nonmatchings/main_014", func_0015B820);

INCLUDE_ASM("asm/nonmatchings/main_014", func_0015BE00);

INCLUDE_ASM("asm/nonmatchings/main_014", func_0015C670);

INCLUDE_ASM("asm/nonmatchings/main_014", func_0015CBB0);

INCLUDE_ASM("asm/nonmatchings/main_014", func_0015CF30);

INCLUDE_ASM("asm/nonmatchings/main_014", func_0015D030);

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

INCLUDE_ASM("asm/nonmatchings/main_014", func_0015FB60);

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

INCLUDE_ASM("asm/nonmatchings/main_014", func_00162390);

INCLUDE_ASM("asm/nonmatchings/main_014", func_00162490);

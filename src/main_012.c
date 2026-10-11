#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_012", func_0014BFD0);

INCLUDE_ASM("asm/nonmatchings/main_012", func_0014C3B0);

void func_0014C6C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28) {
    func_0027DE20(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
        arg_sp0, arg_sp8, arg_sp10, arg_sp18, arg_sp20, 0, 2500, arg_sp28);
}

INCLUDE_ASM("asm/nonmatchings/main_012", func_0014C720);

INCLUDE_ASM("asm/nonmatchings/main_012", func_0014C870);

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

INCLUDE_ASM("asm/nonmatchings/main_012", func_0014C9D0);

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

INCLUDE_ASM("asm/nonmatchings/main_012", func_0014D1E0);

INCLUDE_ASM("asm/nonmatchings/main_012", func_0014D3E0);

INCLUDE_ASM("asm/nonmatchings/main_012", func_0014D5C0);

s32 func_0014D7A0(s32 arg0) {
    if (func_0026FCE0(arg0) >> 5) {
        return 1;
    }
    if (func_0026FC10(arg0) == 1) {
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_012", func_0014D800);

void func_0014DA30(void) {
    func_0024E410();
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
    if (func_001DF470() > 0x4B0) {
        if (func_001E0150(arg0) >= 5) {
            return 0x2EE;
        } else {
            return 0x5DC;
        }
    } else {
        return 0x960;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_012", func_0014FA10);

INCLUDE_ASM("asm/nonmatchings/main_012", func_0014FB70);

INCLUDE_ASM("asm/nonmatchings/main_012", func_0014FD40);

INCLUDE_ASM("asm/nonmatchings/main_012", func_00150270);

INCLUDE_ASM("asm/nonmatchings/main_012", func_00150470);

INCLUDE_ASM("asm/nonmatchings/main_012", func_00150850);

void func_00150BE0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7,
                   s32 a8, u16 a9, s32 a10, s32 a11, u8 a12, s32 a13) {
    func_0027DE20(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, 0, 2000, a13);
}

INCLUDE_ASM("asm/nonmatchings/main_012", func_00150C40);

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

INCLUDE_ASM("asm/nonmatchings/main_012", func_001514A0);

INCLUDE_ASM("asm/nonmatchings/main_012", func_001516A0);

INCLUDE_ASM("asm/nonmatchings/main_012", func_00151880);

s32 func_00151A60(s32 arg0) {
    if ((func_0026FCE0(arg0) >> 5) != 0) {
        return 1;
    }
    if (func_0026FC10(arg0) == 1) {
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_012", func_00151AC0);

INCLUDE_ASM("asm/nonmatchings/main_012", func_00151CF0);

INCLUDE_ASM("asm/nonmatchings/main_012", func_00152100);

INCLUDE_ASM("asm/nonmatchings/main_012", func_001526D0);

INCLUDE_ASM("asm/nonmatchings/main_012", func_00152CD0);

INCLUDE_ASM("asm/nonmatchings/main_012", func_00153550);

s32 func_00153AB0(void) {
    return (func_001E0110(func_001DE540()) < 3) ? 0 : 1;
}

INCLUDE_ASM("asm/nonmatchings/main_012", func_00153AE0);

INCLUDE_ASM("asm/nonmatchings/main_012", func_00153DD0);

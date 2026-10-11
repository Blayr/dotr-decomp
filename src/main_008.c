#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_008", func_0012CE50);

INCLUDE_ASM("asm/nonmatchings/main_008", func_0012D270);

INCLUDE_ASM("asm/nonmatchings/main_008", func_0012D520);

INCLUDE_ASM("asm/nonmatchings/main_008", func_0012D960);

s32 func_0012DAE0(s32 arg0, s32 *arg1, void *arg2, void *arg3, s32 arg4) {
    s32 i;
    s32 *entry;
    s32 wanted;

    i = 0;
    if (i < func_0026FE20(arg0)) {
        wanted = arg4 & 0xFFFF;
        entry = arg1;
        do {
            if (func_0026FB10(arg0, *entry) == 1) {
                if (wanted == *entry && func_0026FB10(arg0, *entry) == 1) {
                    *((u8 *)arg3 + 6) = i;
                    func_001DCD70(arg2, arg1[i]);
                    return func_0026FCE0(arg1[i]) >> 5;
                }
            }
            entry++;
            i++;
        } while (i < func_0026FE20(arg0));
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/main_008", func_0012DBE0);

INCLUDE_ASM("asm/nonmatchings/main_008", func_0012DDE0);

INCLUDE_ASM("asm/nonmatchings/main_008", func_0012DFC0);

s32 func_0012E1A0(s32 arg0) {
    if ((func_0026FCE0(arg0) >> 5) != 0) {
        return 1;
    }
    return func_0026FC10(arg0) != 0 ? 1 : 0;
}

INCLUDE_ASM("asm/nonmatchings/main_008", func_0012E1F0);

INCLUDE_ASM("asm/nonmatchings/main_008", func_0012E3F0);

INCLUDE_ASM("asm/nonmatchings/main_008", func_0012E820);

INCLUDE_ASM("asm/nonmatchings/main_008", func_0012ED70);

INCLUDE_ASM("asm/nonmatchings/main_008", func_0012F350);

INCLUDE_ASM("asm/nonmatchings/main_008", func_0012F930);

INCLUDE_ASM("asm/nonmatchings/main_008", func_00130120);

INCLUDE_ASM("asm/nonmatchings/main_008", func_00130660);

s32 func_00130780(s32 arg0) {
    if (func_001DF470() > 0x7D0) {
        if (func_001E0150(arg0) >= 4) {
            return 0x2EE;
        } else {
            return 0x5DC;
        }
    } else {
        return 0x960;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_008", func_001307E0);

INCLUDE_ASM("asm/nonmatchings/main_008", func_00130940);

static inline s32 max_00130BB0(s32 a, s32 b) {
    if (a < b) {
        return b;
    }
    return a;
}

s32 func_00130BB0(s32 arg0, s32 arg1, s32 arg2, s32 arg3,
                  s32 arg4, s32 arg5) {
    s32 min_y;
    s32 min_x;

    min_y = arg3 < arg5 ? arg3 : arg5;
    arg5 = max_00130BB0(arg5, arg3);
    min_x = arg2 < arg4 ? arg2 : arg4;
    arg4 = max_00130BB0(arg4, arg2);
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

INCLUDE_ASM("asm/nonmatchings/main_008", func_00130CB0);

INCLUDE_ASM("asm/nonmatchings/main_008", func_00130E90);

INCLUDE_ASM("asm/nonmatchings/main_008", func_00131060);

INCLUDE_ASM("asm/nonmatchings/main_008", func_00131540);

INCLUDE_ASM("asm/nonmatchings/main_008", func_00131750);

INCLUDE_ASM("asm/nonmatchings/main_008", func_00131B30);

INCLUDE_ASM("asm/nonmatchings/main_008", func_00131DE0);

INCLUDE_ASM("asm/nonmatchings/main_008", func_00131E40);

INCLUDE_ASM("asm/nonmatchings/main_008", func_00131F80);

INCLUDE_ASM("asm/nonmatchings/main_008", func_00132280);

INCLUDE_ASM("asm/nonmatchings/main_008", func_00132460);

INCLUDE_ASM("asm/nonmatchings/main_008", func_001326F0);

s32 func_00132A10(s32 arg0, void *arg1, void *arg2, s32 arg3) {
    s32 values[8];
    s32 index;
    s32 *value;

    func_0026FD30(arg0, values);
    index = 0;
    if (index < func_0026FE20(arg0)) {
        value = values;
        do {
            if (((arg3 & 0xFFFF) == *value) && (func_0026FB10(arg0, *value) == 1)) {
                *((s8 *)arg1 + 6) = index;
                func_001DCD70(arg2, values[index]);
                return func_0026FCE0(values[index]) >> 5;
            }
            value++;
            index++;
        } while (index < func_0026FE20(arg0));
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/main_008", func_00132B00);

INCLUDE_ASM("asm/nonmatchings/main_008", func_00132D00);

INCLUDE_ASM("asm/nonmatchings/main_008", func_00132EE0);

s32 func_001330C0(s32 arg0) {
    if ((func_0026FCE0(arg0) >> 5) != 0) {
        return 1;
    }
    if ((arg0 == 0x23D) || (arg0 == 0x216) || (arg0 == 0x63)) {
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_008", func_00133130);

INCLUDE_ASM("asm/nonmatchings/main_008", func_00133320);

INCLUDE_ASM("asm/nonmatchings/main_008", func_001336A0);

INCLUDE_ASM("asm/nonmatchings/main_008", func_00133BE0);

INCLUDE_ASM("asm/nonmatchings/main_008", func_001341C0);

INCLUDE_ASM("asm/nonmatchings/main_008", func_001349A0);

INCLUDE_ASM("asm/nonmatchings/main_008", func_00134AE0);

INCLUDE_ASM("asm/nonmatchings/main_008", func_00134B40);

static inline s32 min_00134F00(s32 a, s32 b) {
    if (a < b) {
        return a;
    }
    return b;
}

static inline s32 max_00134F00(s32 a, s32 b) {
    if (a < b) {
        return b;
    }
    return a;
}

s32 func_00134F00(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 min_y;
    s32 min_x;

    min_y = min_00134F00(arg3, arg5);
    arg5 = max_00134F00(arg5, arg3);
    min_x = min_00134F00(arg2, arg4);
    arg4 = max_00134F00(arg4, arg2);
    if ((arg4 - min_x) + (arg5 - min_y) != 2) {
        return 0;
    }
    if (func_001DF540(arg0, arg1) == 0) {
        return 0;
    }
    if (func_001E2100(arg0, arg1, 0) == 0) {
        return func_0024DF00(func_001E22B0(arg2, arg3), arg0, arg1) != 1 ? 0 : 1;
    }
    return 0;
}

s32 func_00135000(s32 arg0, s32 arg1) {
    s32 sp20[4];

    func_00254C90(sp20, *(s32 *)((u8 *)func_0026FC90(arg1, 0) + 4));
    if (func_00254890(sp20, arg0) < 0) {
        return 0;
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_008", func_00135060);

INCLUDE_ASM("asm/nonmatchings/main_008", func_00135230);

#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_011", func_00144630);

s32 func_00144810(s32 arg0) {
    if ((func_0026FCE0(arg0) >> 5) != 0) {
        return 1;
    }
    return (func_0026FC10(arg0) != 0) ? 1 : 0;
}

INCLUDE_ASM("asm/nonmatchings/main_011", func_00144860);

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

INCLUDE_ASM("asm/nonmatchings/main_011", func_00146220);

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

INCLUDE_ASM("asm/nonmatchings/main_011", func_00146790);

INCLUDE_ASM("asm/nonmatchings/main_011", func_00146960);

INCLUDE_ASM("asm/nonmatchings/main_011", func_00146EC0);

INCLUDE_ASM("asm/nonmatchings/main_011", func_00147100);

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

INCLUDE_ASM("asm/nonmatchings/main_011", func_00148020);

INCLUDE_ASM("asm/nonmatchings/main_011", func_001482F0);

INCLUDE_ASM("asm/nonmatchings/main_011", func_00148630);

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

INCLUDE_ASM("asm/nonmatchings/main_011", func_00148960);

INCLUDE_ASM("asm/nonmatchings/main_011", func_00148B60);

INCLUDE_ASM("asm/nonmatchings/main_011", func_00148D40);

s32 func_00148F20(s32 arg0) {
    if ((func_0026FCE0(arg0) >> 5) != 0) {
        return 1;
    } else if (func_0026FC10(arg0) == 1) {
        return 1;
    } else {
        return 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_011", func_00148F80);

INCLUDE_ASM("asm/nonmatchings/main_011", func_001491B0);

INCLUDE_ASM("asm/nonmatchings/main_011", func_00149690);

INCLUDE_ASM("asm/nonmatchings/main_011", func_00149C60);

INCLUDE_ASM("asm/nonmatchings/main_011", func_0014A240);

INCLUDE_ASM("asm/nonmatchings/main_011", func_0014AAB0);

INCLUDE_ASM("asm/nonmatchings/main_011", func_0014ACA0);

INCLUDE_ASM("asm/nonmatchings/main_011", func_0014AE60);

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

INCLUDE_ASM("asm/nonmatchings/main_011", func_0014B490);

INCLUDE_ASM("asm/nonmatchings/main_011", func_0014B730);

INCLUDE_ASM("asm/nonmatchings/main_011", func_0014B900);

INCLUDE_ASM("asm/nonmatchings/main_011", func_0014BDE0);

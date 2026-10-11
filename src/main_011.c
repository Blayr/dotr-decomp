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

INCLUDE_ASM("asm/nonmatchings/main_011", func_001461C0);

INCLUDE_ASM("asm/nonmatchings/main_011", func_00146220);

INCLUDE_ASM("asm/nonmatchings/main_011", func_001464A0);

INCLUDE_ASM("asm/nonmatchings/main_011", func_001465A0);

INCLUDE_ASM("asm/nonmatchings/main_011", func_001466A0);

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

INCLUDE_ASM("asm/nonmatchings/main_011", func_00147EB0);

INCLUDE_ASM("asm/nonmatchings/main_011", func_00147F40);

INCLUDE_ASM("asm/nonmatchings/main_011", func_00148020);

INCLUDE_ASM("asm/nonmatchings/main_011", func_001482F0);

INCLUDE_ASM("asm/nonmatchings/main_011", func_00148630);

INCLUDE_ASM("asm/nonmatchings/main_011", func_00148870);

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

INCLUDE_ASM("asm/nonmatchings/main_011", func_0014B140);

INCLUDE_ASM("asm/nonmatchings/main_011", func_0014B240);

s32 func_0014B330(s32 arg0) {
    return func_001DF470() > 0x5DC
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

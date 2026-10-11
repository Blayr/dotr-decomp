#include "common.h"

void func_001031C0(u16 *arg0, s32 arg1) {
    s32 d;
    s32 e;

    d = ((arg1 - arg0[0]) + 1) & 0xFFFF;
    if (d != 0) {
        e = d & 0xFFFF;
        if (e < 6) {
            func_001F6D00((0x80 - (e * 0x10)) & 0xFF);
        }
    }
    d = ((arg1 - arg0[1]) + 1) & 0xFFFF;
    if (d != 0) {
        e = d & 0xFFFF;
        if (e < 6) {
            func_001F6D00(((e * 0x10) + 0x30) & 0xFF);
        }
    }
}

s32 func_00103260(s32 *arg0) {
    *arg0 = func_00202BF0(4);
    return 0;
}

s32 func_00103290(s32 *arg0) {
    *arg0 = func_00202BF0(5);
    return 0;
}

s32 func_001032C0(u8 *arg0, u8 arg1, u8 arg2) {
    u8 temp_a3;

    temp_a3 = *arg0;
    if (temp_a3 <= (arg1 - arg2)) {
        *arg0 = temp_a3 + arg2;
        return 1;
    }
    *arg0 = arg1;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_001", func_00103300);

s32 func_00103350(s32 *arg0, s32 arg1, s32 arg2) {
    s32 temp_v1;
    s32 result;

    temp_v1 = *arg0;
    if (temp_v1 <= (arg1 - arg2)) {
        *arg0 = temp_v1 + arg2;
        result = 1;
    } else {
        *arg0 = arg1;
        result = 0;
    }
    return result;
}

s32 func_00103390(f32 *arg0, f32 fparg0, f32 fparg1) {
    f32 temp_f1;

    temp_f1 = *arg0;
    if (temp_f1 <= (fparg0 - fparg1)) {
        *arg0 = temp_f1 + fparg1;
        return 1;
    }
    *arg0 = fparg0;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_001", func_001033D0);

s32 func_00103470(u8 *arg0, u8 arg1, s32 arg2) {
    u8 temp_a3;

    temp_a3 = *arg0;
    if ((s32) temp_a3 >= ((arg1 & 0xFF) + (arg2 & 0xFF))) {
        *arg0 = temp_a3 - arg2;
        return 1;
    }
    *arg0 = arg1;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_001", func_001034B0);

s32 func_00103500(s32 *arg0, s32 arg1, s32 arg2) {
    s32 temp_v1;

    temp_v1 = *arg0;
    if (temp_v1 >= (arg1 + arg2)) {
        *arg0 = temp_v1 - arg2;
        return 1;
    }
    *arg0 = arg1;
    return 0;
}

s32 func_00103540(f32 *arg0, f32 fparg0, f32 fparg1) {
    f32 temp_f1;

    temp_f1 = *arg0;
    if (!(temp_f1 < (fparg0 + fparg1))) {
        *arg0 = temp_f1 - fparg1;
        return 1;
    }
    *arg0 = fparg0;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_001", func_00103580);

INCLUDE_ASM("asm/nonmatchings/main_001", func_00103620);

INCLUDE_ASM("asm/nonmatchings/main_001", func_00103660);

INCLUDE_ASM("asm/nonmatchings/main_001", func_001036A0);

INCLUDE_ASM("asm/nonmatchings/main_001", func_001036E0);

INCLUDE_ASM("asm/nonmatchings/main_001", func_00103760);

INCLUDE_ASM("asm/nonmatchings/main_001", func_001037C0);

INCLUDE_ASM("asm/nonmatchings/main_001", func_00103890);

INCLUDE_ASM("asm/nonmatchings/main_001", func_001038D0);

INCLUDE_ASM("asm/nonmatchings/main_001", func_00103920);

INCLUDE_ASM("asm/nonmatchings/main_001", func_001039A0);

INCLUDE_ASM("asm/nonmatchings/main_001", func_00103A30);

INCLUDE_ASM("asm/nonmatchings/main_001", func_00103B50);

INCLUDE_ASM("asm/nonmatchings/main_001", func_00103C40);

INCLUDE_ASM("asm/nonmatchings/main_001", func_00103D00);

INCLUDE_ASM("asm/nonmatchings/main_001", func_00103DB0);

INCLUDE_ASM("asm/nonmatchings/main_001", func_00103EC0);

INCLUDE_ASM("asm/nonmatchings/main_001", func_001043F0);

INCLUDE_ASM("asm/nonmatchings/main_001", func_00104490);

s32 func_00104520(s32 arg0, s32 arg1) {
    return !(arg0 & (1 << arg1)) ? 0 : 1;
}

INCLUDE_ASM("asm/nonmatchings/main_001", func_00104540);

INCLUDE_ASM("asm/nonmatchings/main_001", func_00104DC0);

INCLUDE_ASM("asm/nonmatchings/main_001", func_00105260);

INCLUDE_ASM("asm/nonmatchings/main_001", func_00105830);

INCLUDE_ASM("asm/nonmatchings/main_001", func_00105C40);

INCLUDE_ASM("asm/nonmatchings/main_001", func_00105D00);

INCLUDE_ASM("asm/nonmatchings/main_001", func_00106080);

INCLUDE_ASM("asm/nonmatchings/main_001", func_00106A00);

INCLUDE_ASM("asm/nonmatchings/main_001", func_00106AB0);

INCLUDE_ASM("asm/nonmatchings/main_001", func_00106B50);

s32 func_00106B90(void *arg0, s32 arg1, s32 arg2) {
    ((u8 *)arg0)[0xAF] = (u8)(((u8 *)arg0)[0xAF] - arg1);
    ((u8 *)arg0)[0xB3] = (u8)(((u8 *)arg0)[0xB3] - arg1);
    return (((u8 *)arg0)[0xAF] < (arg2 & 0xFF)) ? 1 : 0;
}

s32 func_00106BC0(void *arg0, s32 arg1, s32 arg2) {
    *((u8 *)arg0 + 0xAF) = (u8)(*((u8 *)arg0 + 0xAF) + arg1);
    *((u8 *)arg0 + 0xB3) = (u8)(*((u8 *)arg0 + 0xB3) + arg1);
    return *((u8 *)arg0 + 0xAF) > (arg2 & 0xFF) ? 1 : 0;
}

INCLUDE_ASM("asm/nonmatchings/main_001", func_00106BF0);

INCLUDE_ASM("asm/nonmatchings/main_001", func_00106C50);

s32 func_00106CC0(s32 arg0, s32 arg1) {
    func_00195108(arg0, (s16)arg1);
    return arg0;
}

INCLUDE_ASM("asm/nonmatchings/main_001", func_00106CF0);

INCLUDE_ASM("asm/nonmatchings/main_001", func_00106D80);

INCLUDE_ASM("asm/nonmatchings/main_001", func_00106DD0);

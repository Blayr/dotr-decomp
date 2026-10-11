#include "common.h"

s32 func_001F5F00(s32 arg0, void *arg1) {
    extern s32 func_001E1360(s32, s32);
    s32 hi;
    s32 lo;

    hi = arg0 >> 8;
    lo = arg0 & 0xFF;
    if (hi < 0 || hi >= 3 || lo < 0 || lo >= 0xB) {
        return 0;
    }
    arg0 = func_001E1360(hi, lo);
    if (arg0 < 0) {
        return 0;
    }
    return func_001F22B0(arg0, arg1);
}

s32 func_001F5F90(s32 arg0, f32 *arg1) {
    extern s32 func_001E1360(s32, s32);
    s32 hi = arg0 >> 8;
    s32 lo = arg0 & 0xFF;

    arg1[2] = 0.0f;
    arg1[1] = 0.0f;
    arg1[0] = 0.0f;
    arg1[3] = 1.0f;
    if (hi < 0 || hi >= 3 || lo < 0 || lo >= 0xB) {
        return 0;
    }
    arg0 = func_001E1360(hi, lo);
    if (arg0 < 0) {
        return 0;
    }
    return func_001F1FD0(arg0, arg1);
}

s32 func_001F6030(s32 arg0, void *arg1) {
    extern s32 func_001E1360(s32, s32);
    s32 hi;
    s32 lo;

    hi = arg0 >> 8;
    lo = arg0 & 0xFF;
    if (hi < 0 || hi >= 3 || lo < 0 || lo >= 0xB) {
        return 0;
    }
    arg0 = func_001E1360(hi, lo);
    if (arg0 < 0) {
        return 0;
    }
    return func_001F2430(arg0, arg1);
}

void func_001F60C0(s32 arg0) {
    func_001F60D0(D_0031BE98, arg0);
}

INCLUDE_ASM("asm/nonmatchings/main_051", func_001F60D0);

s32 func_001F6160(s32 arg0, void *arg1) {
    extern s32 func_001E1360(s32, s32);
    s32 hi = arg0 >> 8;
    s32 lo = arg0 & 0xFF;

    ((s32 *)arg1)[3] = 0;
    ((s32 *)arg1)[2] = 0;
    ((s32 *)arg1)[1] = 0;
    ((s32 *)arg1)[0] = 0;
    if (hi < 0 || hi >= 3 || lo < 0 || lo >= 0xB) {
        return 0;
    }
    arg0 = func_001E1360(hi, lo);
    if (arg0 < 0) {
        return 0;
    }
    return func_001F2330(arg0, arg1);
}

void func_001F6200(s32 arg0) {
    func_001F6210(D_0031BE98, arg0);
}

s32 func_001F6210(s32 arg0, s32 arg1) {
    extern s32 func_001E1360(s32, s32);
    s32 hi = arg0 >> 8;
    s32 lo = arg0 & 0xFF;

    ((s32 *)arg1)[3] = 0;
    ((s32 *)arg1)[2] = 0;
    ((s32 *)arg1)[1] = 0;
    ((s32 *)arg1)[0] = 0;
    if (hi < 0 || hi >= 3 || lo < 0 || lo >= 0xB) {
        return 0;
    }
    arg0 = func_001E1360(hi, lo);
    if (arg0 < 0) {
        return 0;
    }
    return func_001F23B0(arg0, (void *)arg1);
}

s32 func_001F62B0(s32 arg0, void *arg1) {
    extern s32 func_001E1360(s32, s32);
    s32 hi;
    s32 lo;

    hi = arg0 >> 8;
    lo = arg0 & 0xFF;
    if (hi < 0 || hi >= 3 || lo < 0 || lo >= 0xB) {
        return 0;
    }
    arg0 = func_001E1360(hi, lo);
    if (arg0 < 0) {
        return 0;
    }
    return func_001F25D0(arg0, arg1);
}

s32 func_001F6340(s32 arg0, f32 *arg1) {
    extern s32 func_001E1360(s32, s32);
    s32 hi = arg0 >> 8;
    s32 lo = arg0 & 0xFF;

    arg1[2] = 0.0f;
    arg1[1] = 0.0f;
    arg1[0] = 0.0f;
    arg1[3] = 1.0f;
    if (hi < 0 || hi >= 3 || lo < 0 || lo >= 0xB) {
        return 0;
    }
    arg0 = func_001E1360(hi, lo);
    if (arg0 < 0) {
        return 0;
    }
    return func_001F2550(arg0, arg1);
}

void func_001F63E0(s32 arg0, s32 arg1) {
    func_001F63F0(arg0, -1, arg1);
}

s32 func_001F63F0(s32 arg0, s32 arg1, s32 arg2) {
    extern s32 func_001E1360(s32, s32);
    s32 hi;
    s32 lo;

    hi = arg0 >> 8;
    lo = arg0 & 0xFF;
    if (hi < 0 || hi >= 3 || lo < 0 || lo >= 0xB) {
        return 0;
    }
    arg0 = func_001E1360(hi, lo);
    if (arg0 < 0) {
        return 0;
    }
    return func_001F26E0(arg0, arg1, (void *) arg2);
}

INCLUDE_ASM("asm/nonmatchings/main_051", func_001F6480);

s32 func_001F6490(void) {
    if (func_001F64C0() >= 0) {
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_051", func_001F64C0);

void func_001F6560(s32 arg0) {
    func_001F6590(D_0031BE98, -1, arg0);
}

void func_001F6580(s32 arg0, s32 arg1) {
    func_001F6590(arg0, -1, arg1);
}

s32 func_001F6590(s32 arg0, s32 arg1, s32 arg2) {
    extern s32 func_001E1360(s32, s32);
    s32 hi;
    s32 lo;

    hi = arg0 >> 8;
    lo = arg0 & 0xFF;
    if (hi < 0 || hi >= 3 || lo < 0 || lo >= 0xB) {
        return 0;
    }
    arg0 = func_001E1360(hi, lo);
    if (arg0 < 0) {
        return 0;
    }
    return func_001F2860(arg0, arg1, (void *) arg2);
}

INCLUDE_ASM("asm/nonmatchings/main_051", func_001F6620);

s32 func_001F66A0(s32 arg0, s32 arg1) {
    extern s32 func_001E1360(s32, s32);
    s32 hi;
    s32 lo;

    hi = arg0 >> 8;
    lo = arg0 & 0xFF;
    if (hi < 0 || hi >= 3 || lo < 0 || lo >= 0xB) {
        return 0;
    }
    arg0 = func_001E1360(hi, lo);
    if (arg0 < 0) {
        return 0;
    }
    return func_001F1550(arg0, arg1);
}

s32 func_001F6730(s32 arg0, s64 arg1) {
    extern s32 func_001E1360(s32, s32);
    s32 hi;
    s32 lo;

    hi = arg0 >> 8;
    lo = arg0 & 0xFF;
    if (hi < 0 || hi >= 3 || lo < 0 || lo >= 0xB) {
        return 0;
    }
    arg0 = func_001E1360(hi, lo);
    if (arg0 < 0) {
        return 0;
    }
    return func_001F1A00(arg0, arg1);
}

f32 func_001F67C0(s32 arg0, s32 arg1) {
    s32 func_001E1360();
    f32 func_001F1B50();
    s32 hi = arg0 >> 8;
    s32 lo = arg0 & 0xFF;

    if (hi < 0 || hi >= 3 || lo < 0 || lo >= 11) {
        return 0.0f;
    }
    arg0 = func_001E1360(hi, lo);
    if (arg0 < 0) {
        return 0.0f;
    }
    return func_001F1B50(arg0);
}

s32 func_001F6840(s32 arg0, f32 arg1) {
    extern s32 func_001E1360(s32, s32);
    extern s32 func_001F1C40(s32, f32);
    s32 hi;
    s32 lo;

    hi = arg0 >> 8;
    lo = arg0 & 0xFF;
    if (hi < 0 || hi >= 3 || lo < 0 || lo >= 0xB) {
        return 0;
    }
    arg0 = func_001E1360(hi, lo);
    if (arg0 < 0) {
        return 0;
    }
    return func_001F1C40(arg0, arg1);
}

void func_001F68D0(s32 arg0) {
    func_001F9170(0, 4, arg0);
    func_001F9170(0, 5, arg0);
}

void func_001F6910(s32 arg0) {
    func_001F9170(0, 0, arg0);
    func_001F9170(0, 1, arg0);
    func_001F9170(0, 8, arg0);
}

void func_001F6960(s32 arg0) {
    func_001F9170(0, 2, arg0);
    func_001F9170(0, 3, arg0);
}

void func_001F69A0(s32 arg0) {
    func_001F9230(0, 4, arg0);
    func_001F9230(0, 5, arg0);
}

void func_001F69E0(s32 arg0) {
    func_001F9230(0, 0, arg0);
    func_001F9230(0, 1, arg0);
    func_001F9230(0, 8, arg0);
}

void func_001F6A30(s32 arg0) {
    func_001F9230(0, 2, arg0);
    func_001F9230(0, 3, arg0);
}

void func_001F6A70(s32 arg0) {
    func_001F9310(0, 4, arg0);
    func_001F9310(0, 5, arg0);
}

void func_001F6AB0(s32 arg0) {
    func_001F9310(0, 0, arg0);
    func_001F9310(0, 1, arg0);
    func_001F9310(0, 8, arg0);
}

void func_001F6B00(s32 arg0) {
    func_001F9310(0, 2, arg0);
    func_001F9310(0, 3, arg0);
}

void func_001F6B40(s32 arg0) {
    func_001F9770(0, 4, arg0);
    func_001F9770(0, 5, arg0);
}

void func_001F6B80(s32 arg0) {
    func_001F9770(0, 0, arg0);
    func_001F9770(0, 1, arg0);
    func_001F9770(0, 8, arg0);
}

void func_001F6BD0(s32 arg0) {
    func_001F9770(0, 2, arg0);
    func_001F9770(0, 3, arg0);
}

void func_001F6C10(s32 arg0) {
    func_001F9940(0, 4, arg0);
    func_001F9940(0, 5, arg0);
}

void func_001F6C50(s32 arg0) {
    func_001F9940(0, 0, arg0);
    func_001F9940(0, 1, arg0);
    func_001F9940(0, 8, arg0);
}

void func_001F6CA0(s32 arg0) {
    func_001F9940(0, 2, arg0);
    func_001F9940(0, 3, arg0);
}

INCLUDE_ASM("asm/nonmatchings/main_051", func_001F6CE0);

INCLUDE_ASM("asm/nonmatchings/main_051", func_001F6CF0);

void func_001F6D00(s32 arg0) {
    D_0031BEA2 = (s8) arg0;
}

u8 func_001F6D10(void) {
    return D_0031BEA0;
}

u8 func_001F6D20(void) {
    return (u8)D_0031BEA1;
}

u8 func_001F6D30(void) {
    return D_0031BEA2;
}

void func_001F6D40(s32 arg0) {
    func_001F6E10(4, arg0);
    func_001F6E10(5, arg0);
}

void func_001F6D80(s32 arg0) {
    func_001F6E10(0, arg0);
    func_001F6E10(1, arg0);
    func_001F6E10(8, arg0);
}

void func_001F6DD0(s32 arg0) {
    func_001F6E10(2, arg0);
    func_001F6E10(3, arg0);
}

s32 func_001F6E10(s32 arg0, s32 arg1) {
    extern s32 func_001F2980(s32);
    s32 i;

    i = 0;
    do {
        if (arg0 < 0 || arg0 == func_001F2980(i)) {
            func_001F1EE0(i, (f32 *) arg1);
        }
        i += 1;
    } while (i < 0x54);
}

void func_001F6E80(s32 arg0, f32 fparg0) {
    extern s32 func_001F2980(s32);
    s32 i;

    i = 0;
    do {
        if (arg0 < 0 || arg0 == func_001F2980(i)) {
            func_001F1F70(i, fparg0);
        }
        i++;
    } while (i < 0x54);
}

INCLUDE_ASM("asm/nonmatchings/main_051", func_001F6EF0);

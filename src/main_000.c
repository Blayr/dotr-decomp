#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_000", func_00100000);

INCLUDE_ASM("asm/nonmatchings/main_000", func_00100008);

INCLUDE_ASM("asm/nonmatchings/main_000", func_001000B8);

INCLUDE_ASM("asm/nonmatchings/main_000", func_001000C0);

INCLUDE_ASM("asm/nonmatchings/main_000", func_001000D0);

INCLUDE_ASM("asm/nonmatchings/main_000", func_001001D0);

INCLUDE_ASM("asm/nonmatchings/main_000", func_00100350);

void func_001004C0(void) {
    s32 i;

    func_001F7720(0);
    i = 0;
    do {
        func_001E7DE0(i);
        i += 1;
    } while (i < 0x54);
    func_00209870();
    func_002032A0();
}

void func_00100520(void) {
    func_00209F60(func_001F73C0);
    for (;;) {
        if (func_001AAF60(1) == 1) {
            func_00100780();
        }
        func_00100560();
    }
}

INCLUDE_ASM("asm/nonmatchings/main_000", func_00100560);

INCLUDE_ASM("asm/nonmatchings/main_000", func_00100610);

INCLUDE_ASM("asm/nonmatchings/main_000", func_00100780);

s32 func_00100820(void) {
    func_0019A5C8();
    func_002038F0();
    func_001A86F0();
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_000", func_00100850);

INCLUDE_ASM("asm/nonmatchings/main_000", func_00100B00);

INCLUDE_ASM("asm/nonmatchings/main_000", func_00100BA0);

INCLUDE_ASM("asm/nonmatchings/main_000", func_00100C60);

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Vec3_00100D00;

void func_001F5F90(s32, void *);

s32 func_00100D00(s32 arg0) {
    Vec3_00100D00 v;
    s32 ret;

    ret = 1;
    func_001F5F90(arg0, &v);
    if (v.z < 0.0f) {
        ret = -1;
    }
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/main_000", func_00100D50);

typedef struct {
    u32 values[4];
} Config_00100E00;

void func_0020CB90(s32, u32 *);
extern Config_00100E00 D_0028C210;

void func_00100E00(s32 arg0, s32 arg1, s32 arg2) {
    Config_00100E00 values;
    u32 *words = (u32 *)&values;

    values = D_0028C210;
    arg1 &= 0xFFFF;
    words[arg2] = arg1;
    func_0020CB90(arg0, words);
}

INCLUDE_ASM("asm/nonmatchings/main_000", func_00100E40);

INCLUDE_ASM("asm/nonmatchings/main_000", func_00100F60);

f32 func_00100FF0(f32 fparg0, f32 fparg1, f32 fparg2) {
    f32 var_f0;

    var_f0 = 1.0f;
    if (!(fparg0 <= fparg2)) {
        var_f0 = (fparg0 - fparg1) / (fparg2 - fparg1);
    }
    return var_f0;
}

f32 func_00101020(f32 fparg0, f32 fparg1) {
    f32 var_f0;

    var_f0 = 1.0f;
    if (fparg0 < fparg1) {
        var_f0 = fparg0 / fparg1;
    }
    return var_f0;
}

s32 func_00101050(s32 arg0, s32 arg1, s32 arg2) {
    if (arg0 < arg1) {
        arg0 = arg1;
    } else if (arg2 < arg0) {
        arg0 = arg2;
    }
    return arg0;
}

INCLUDE_ASM("asm/nonmatchings/main_000", func_00101080);

INCLUDE_ASM("asm/nonmatchings/main_000", func_00101430);

INCLUDE_ASM("asm/nonmatchings/main_000", func_00101600);

s32 func_00101770(void *arg0) {
    u16 *p = (u16 *)arg0;
    if ((f32)(u32)p[0] < 27648.0f) return 0;
    if ((f32)(u32)p[0] > 37888.0f) return 0;
    if ((f32)(u32)p[1] < 29184.0f) return 0;
    if ((f32)(u32)p[1] > 36352.0f) return 0;
    return 1;
}

f32 func_001018E0(f32 fparg0, f32 fparg1) {
    return (fparg0 / (fparg1 / 256.0f)) * (func_001F9A20(0) / 800.0f);
}

INCLUDE_ASM("asm/nonmatchings/main_000", func_00101940);

INCLUDE_ASM("asm/nonmatchings/main_000", func_00101A00);

void func_00101AD0(s8 *arg0, s8 arg1, s8 arg2, s8 arg3) {
    arg0[2] = arg1;
    arg0[0] = arg1;
    arg0[1] = arg2;
    arg0[3] = arg3;
}

typedef struct Timer_00101AF0 {
    u8 count;
    u8 delay;
} Timer_00101AF0;

s32 func_00101AF0(void *arg0) {
    Timer_00101AF0 *timer = arg0;
    u8 temp_v0;
    u8 temp_v1;

    temp_v1 = timer->count;
    if (temp_v1 == 0) {
        return 0;
    }
    temp_v0 = timer->delay;
    if (temp_v0 != 0) {
        timer->delay = (u8) (temp_v0 - 1);
        return 0;
    }
    timer->count = (u8) (temp_v1 - 1);
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_000", func_00101B40);

typedef struct Counter_00101B50 {
    u8 count;
    u8 delay;
} Counter_00101B50;

s32 func_00101B50(void *arg0) {
    Counter_00101B50 *counter = arg0;

    if (counter->count == 0) {
        return 0;
    }
    if (counter->delay != 0) {
        counter->delay--;
        return 0;
    }
    counter->count--;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_000", func_00101BA0);

s32 func_00101C30(u8 *arg0, s32 arg1, s32 arg2) {
    s32 offset;
    s32 i;

    i = 0;
    if (i < arg2) {
        offset = 0;
        do {
            if (arg0[offset] == 0) {
                return i;
            }
            i++;
            offset += arg1;
        } while (i < arg2);
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/main_000", func_00101C80);

INCLUDE_ASM("asm/nonmatchings/main_000", func_00101D20);

INCLUDE_ASM("asm/nonmatchings/main_000", func_00101EE0);

INCLUDE_ASM("asm/nonmatchings/main_000", func_001020B0);

INCLUDE_ASM("asm/nonmatchings/main_000", func_00102210);

INCLUDE_ASM("asm/nonmatchings/main_000", func_001022D0);

void func_00102330(s8 *arg0, s32 arg1) {
    s8 *var_s0;
    s32 var_s1;

    var_s0 = arg0;
    for (var_s1 = 0; var_s1 < arg1; var_s1 += 1) {
        *var_s0 = (s8) (func_0019A5C8() >> 4);
        var_s0 += 1;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_000", func_00102390);

INCLUDE_ASM("asm/nonmatchings/main_000", func_00102550);

INCLUDE_ASM("asm/nonmatchings/main_000", func_00102A50);

INCLUDE_ASM("asm/nonmatchings/main_000", func_00102CB0);

INCLUDE_ASM("asm/nonmatchings/main_000", func_00102F20);

#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_010", func_0013D3D0);

INCLUDE_ASM("asm/nonmatchings/main_010", func_0013D880);

s32 func_0013D980(s32 arg0, s32 arg1) {
    s32 sp50[4];
    s32 var_s0;
    s32 temp_v0;
    s32 temp_s2;
    s32 temp_s3;
    s32 temp_v0_2;
    s32 temp_v0_3;

    func_00254C90(sp50, *(s32 *)((u8 *)func_0026FC90(arg1, 0) + 4));
    if ((temp_v0 = func_00254890(sp50, arg0)) < 0) {
        return 0;
    }
    var_s0 = 0;
    if (var_s0 < func_0024E910(temp_v0)) {
        do {
            temp_v0_2 = func_0024EC50(temp_v0, var_s0);
            temp_s3 = temp_v0_2 >> 8;
            temp_s2 = temp_v0_2 & 0xFF;
            temp_v0_3 = func_001E1090(temp_s3, temp_s2);
            if (func_002509E0(temp_s3, temp_s2, temp_v0_3 & 0xFF, temp_v0_3 >> 8) >= 0xBB8) {
                return 0;
            }
            var_s0++;
        } while (var_s0 < func_0024E910(temp_v0));
    }
    return 1;
}

s32 func_0013DA70(s32 arg0) {
    if (func_001DF470() > 1000) {
        if (func_001E0150(arg0) >= 5) {
            return 0;
        }
        return 0;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_010", func_0013DAD0);

INCLUDE_ASM("asm/nonmatchings/main_010", func_0013DCA0);

INCLUDE_ASM("asm/nonmatchings/main_010", func_0013E1D0);

INCLUDE_ASM("asm/nonmatchings/main_010", func_0013E3D0);

INCLUDE_ASM("asm/nonmatchings/main_010", func_0013E7B0);

void func_0013EA20(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28) {
    func_0027DE20(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
                  arg_sp0, arg_sp8, arg_sp10, arg_sp18, arg_sp20,
                  0, 0x708, arg_sp28);
}

s32 func_0013EB20(s32, s32, s32);

typedef struct {
    u16 code;
    u16 unknown2;
    u16 state;
    u16 unknown6;
    u32 data;
} Entry_0013EA80;

void func_0013EA80(void *arg0) {
    Entry_0013EA80 *entry = arg0;
    s32 packed;
    s32 result;

    packed = func_001E1090(entry->code >> 8, entry->code & 0xFF);
    func_00250360(entry->code >> 8, entry->code & 0xFF);
    result = func_0013EB20(func_001DF540(entry->code >> 8, entry->code & 0xFF), packed & 0xFF, packed >> 8);
    if (result >= 0) {
        entry->state = 0x6FF;
        entry->data = (result << 16) | (entry->data & 0xFFFF);
    } else {
        entry->state = 0x5FF;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_010", func_0013EB20);

INCLUDE_ASM("asm/nonmatchings/main_010", func_0013ECF0);

INCLUDE_ASM("asm/nonmatchings/main_010", func_0013EEE0);

INCLUDE_ASM("asm/nonmatchings/main_010", func_0013F170);

INCLUDE_ASM("asm/nonmatchings/main_010", func_0013F3B0);

INCLUDE_ASM("asm/nonmatchings/main_010", func_0013F540);

INCLUDE_ASM("asm/nonmatchings/main_010", func_0013F640);

INCLUDE_ASM("asm/nonmatchings/main_010", func_0013F850);

INCLUDE_ASM("asm/nonmatchings/main_010", func_0013FA90);

s32 func_0013FC70(s32 arg0) {
    if ((func_0026FCE0(arg0) >> 5) != 0) {
        return 1;
    }
    return (func_0026FC10(arg0) != 0) ? 1 : 0;
}

INCLUDE_ASM("asm/nonmatchings/main_010", func_0013FCC0);

INCLUDE_ASM("asm/nonmatchings/main_010", func_0013FEB0);

INCLUDE_ASM("asm/nonmatchings/main_010", func_001402F0);

INCLUDE_ASM("asm/nonmatchings/main_010", func_00140830);

INCLUDE_ASM("asm/nonmatchings/main_010", func_00140E10);

INCLUDE_ASM("asm/nonmatchings/main_010", func_001415F0);

s32 func_00141B30(s32 arg0) {
    if (func_001DF470() > 2000) {
        if (func_001E0150(arg0) >= 4) {
            return 0;
        }
        return 0;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_010", func_00141B90);

INCLUDE_ASM("asm/nonmatchings/main_010", func_00141E30);

INCLUDE_ASM("asm/nonmatchings/main_010", func_00141F30);

INCLUDE_ASM("asm/nonmatchings/main_010", func_00142040);

s32 func_00142220(s32 arg0) {
    if (func_001DF470() < 0x4B0) {
        /* Duplicate return node #6. Try simplifying control flow for better match */
        return 0;
    }
    if (func_001E0150(arg0) >= 4) {
        return 1;
    }
    return 0;
}

s32 func_00142280(s32 arg0) {
    if (func_0024E910(func_0024CA40(0, 0, arg0, 1, 0x3E80025, 0xE)) >= 3) {
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_010", func_001422E0);

INCLUDE_ASM("asm/nonmatchings/main_010", func_001424B0);

INCLUDE_ASM("asm/nonmatchings/main_010", func_001429B0);

INCLUDE_ASM("asm/nonmatchings/main_010", func_00142B70);

INCLUDE_ASM("asm/nonmatchings/main_010", func_00142F50);

INCLUDE_ASM("asm/nonmatchings/main_010", func_00143540);

void func_00143790(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28) {
    func_0027DE20(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
                  arg_sp0, arg_sp8, arg_sp10, arg_sp18, arg_sp20,
                  0, 0x708, arg_sp28);
}

INCLUDE_ASM("asm/nonmatchings/main_010", func_001437F0);

s32 func_00143900(void *arg0) {
    s32 i;

    for (i = 1; i <= 5; i++) {
        if (func_0024DEB0(func_001E22B0(0, i), arg0) == 1) {
            return i;
        }
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/main_010", func_00143970);

INCLUDE_ASM("asm/nonmatchings/main_010", func_00143A80);

INCLUDE_ASM("asm/nonmatchings/main_010", func_00143BA0);

INCLUDE_ASM("asm/nonmatchings/main_010", func_00143DE0);

INCLUDE_ASM("asm/nonmatchings/main_010", func_00144150);

INCLUDE_ASM("asm/nonmatchings/main_010", func_00144250);

INCLUDE_ASM("asm/nonmatchings/main_010", func_00144450);

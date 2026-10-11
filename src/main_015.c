#include "common.h"

s32 func_00162580(s32 arg0) {
    if (func_001DF470() > 0x4B0) {
        if (func_001E0150(arg0) >= 4) {
            return 0x1F4;
        }
        return 0x3E8;
    }
    return 0x7D0;
}

INCLUDE_ASM("asm/nonmatchings/main_015", func_001625E0);

INCLUDE_ASM("asm/nonmatchings/main_015", func_001626F0);

INCLUDE_ASM("asm/nonmatchings/main_015", func_001627D0);

INCLUDE_ASM("asm/nonmatchings/main_015", func_00162A70);

INCLUDE_ASM("asm/nonmatchings/main_015", func_00162D10);

INCLUDE_ASM("asm/nonmatchings/main_015", func_00162F60);

INCLUDE_ASM("asm/nonmatchings/main_015", func_00163130);

INCLUDE_ASM("asm/nonmatchings/main_015", func_00163660);

INCLUDE_ASM("asm/nonmatchings/main_015", func_00163870);

INCLUDE_ASM("asm/nonmatchings/main_015", func_00163C50);

void func_00163EC0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28) {
    func_0027DE20(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
                 arg_sp0, arg_sp8, arg_sp10, arg_sp18, arg_sp20,
                 1, 3000, arg_sp28);
}

s32 func_00163F90(s32, s32);

typedef struct {
    u16 location;
    u16 padding2;
    s16 field4;
    u16 padding6;
    union {
        u16 low;
        u32 word;
    } field8;
} State_00163F20;

void func_00163F20(void *arg0) {
    State_00163F20 *state = arg0;
    s32 temp_v0_3;
    u16 temp_v0;
    u16 temp_v0_2;

    temp_v0 = state->location;
    func_00250360((s32) temp_v0 >> 8, temp_v0 & 0xFF);
    temp_v0_2 = state->location;
    temp_v0_3 = func_001E1090((s32) temp_v0_2 >> 8, temp_v0_2 & 0xFF);
    state->field4 = 0x6FF;
    state->field8.word = state->field8.low |
        (func_00163F90(temp_v0_3 & 0xFF, temp_v0_3 >> 8) << 16);
}

INCLUDE_ASM("asm/nonmatchings/main_015", func_00163F90);

INCLUDE_ASM("asm/nonmatchings/main_015", func_00164020);

INCLUDE_ASM("asm/nonmatchings/main_015", func_00164260);

INCLUDE_ASM("asm/nonmatchings/main_015", func_00164360);

INCLUDE_ASM("asm/nonmatchings/main_015", func_001643F0);

INCLUDE_ASM("asm/nonmatchings/main_015", func_00164680);

INCLUDE_ASM("asm/nonmatchings/main_015", func_00164910);

INCLUDE_ASM("asm/nonmatchings/main_015", func_00164A00);

INCLUDE_ASM("asm/nonmatchings/main_015", func_00164AE0);

INCLUDE_ASM("asm/nonmatchings/main_015", func_00164CE0);

INCLUDE_ASM("asm/nonmatchings/main_015", func_00164EC0);

s32 func_001650A0(s32 arg0) {
    if ((func_0026FCE0(arg0) >> 5) != 0) {
        return 1;
    }
    if (func_0026FC10(arg0) == 1) {
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_015", func_00165100);

INCLUDE_ASM("asm/nonmatchings/main_015", func_001652F0);

INCLUDE_ASM("asm/nonmatchings/main_015", func_001658F0);

INCLUDE_ASM("asm/nonmatchings/main_015", func_00165EC0);

INCLUDE_ASM("asm/nonmatchings/main_015", func_001664A0);

INCLUDE_ASM("asm/nonmatchings/main_015", func_00166D10);

INCLUDE_ASM("asm/nonmatchings/main_015", func_00166EE0);

INCLUDE_ASM("asm/nonmatchings/main_015", func_001670A0);

INCLUDE_ASM("asm/nonmatchings/main_015", func_00167570);

s32 func_00167670(s32 arg0, s32 arg1) {
    s32 sp20[4];

    func_00254C90(sp20, *(s32 *)((u8 *)func_0026FC90(arg1, 0) + 4));
    if (func_00254890(sp20, arg0) < 0) {
        return 0;
    }
    return 1;
}

s32 func_001676D0(void) {
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_015", func_001676E0);

INCLUDE_ASM("asm/nonmatchings/main_015", func_001678B0);

INCLUDE_ASM("asm/nonmatchings/main_015", func_00167D30);

INCLUDE_ASM("asm/nonmatchings/main_015", func_00167E80);

INCLUDE_ASM("asm/nonmatchings/main_015", func_00168260);

void func_001684D0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28) {
    func_0027DE20(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
                  arg_sp0, arg_sp8, arg_sp10, arg_sp18, arg_sp20,
                  1, 3000, arg_sp28);
}

INCLUDE_ASM("asm/nonmatchings/main_015", func_00168530);

INCLUDE_ASM("asm/nonmatchings/main_015", func_001687A0);

INCLUDE_ASM("asm/nonmatchings/main_015", func_00168A30);

INCLUDE_ASM("asm/nonmatchings/main_015", func_00168D10);

INCLUDE_ASM("asm/nonmatchings/main_015", func_00168E00);

INCLUDE_ASM("asm/nonmatchings/main_015", func_00169000);

INCLUDE_ASM("asm/nonmatchings/main_015", func_001691E0);

s32 func_001693C0(s32 arg0) {
    if ((func_0026FCE0(arg0) >> 5) != 0) {
        return 1;
    }
    if (func_0026FC10(arg0) == 1) {
        return 1;
    }
    return 0;
}

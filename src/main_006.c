#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_006", func_0011D110);

void func_0011D380(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28) {
    func_0027DE20(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
                  arg_sp0, arg_sp8, arg_sp10, arg_sp18, arg_sp20,
                  0, 1500, arg_sp28);
}

INCLUDE_ASM("asm/nonmatchings/main_006", func_0011D3E0);

INCLUDE_ASM("asm/nonmatchings/main_006", func_0011D4E0);

INCLUDE_ASM("asm/nonmatchings/main_006", func_0011D6D0);

INCLUDE_ASM("asm/nonmatchings/main_006", func_0011D7B0);

s32 func_0011D8D0(s32 arg0, s32 arg1) {
    s32 result;

    switch (arg1) {
    case 0:
        result = 0x204;
        break;
    case 1:
        result = 0x202;
        break;
    case 2:
        result = 0;
        break;
    default:
    case 3:
        result = 6;
        break;
    }

    return result;
}

s32 func_0011D940(s32 arg0, s32 arg1) {
    switch (arg1) {
    case 0:
        return 0x402;
    case 1:
        return 0x404;
    case 2:
        return 0x600;
    default:
    case 3:
        return 0x606;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_006", func_0011D9B0);

INCLUDE_ASM("asm/nonmatchings/main_006", func_0011DC00);

INCLUDE_ASM("asm/nonmatchings/main_006", func_0011DFB0);

INCLUDE_ASM("asm/nonmatchings/main_006", func_0011E270);

INCLUDE_ASM("asm/nonmatchings/main_006", func_0011E6E0);

INCLUDE_ASM("asm/nonmatchings/main_006", func_0011EB10);

INCLUDE_ASM("asm/nonmatchings/main_006", func_0011ED50);

INCLUDE_ASM("asm/nonmatchings/main_006", func_0011EF60);

INCLUDE_ASM("asm/nonmatchings/main_006", func_0011F150);

INCLUDE_ASM("asm/nonmatchings/main_006", func_0011F330);

INCLUDE_ASM("asm/nonmatchings/main_006", func_0011F3C0);

void func_0011F530(void) {
    func_0024E410();
}

INCLUDE_ASM("asm/nonmatchings/main_006", func_0011F540);

s32 func_0011FA80(s32 arg0) {
    if (func_001DF470() > 0x3E8) {
        if (func_001E0150(arg0) >= 3) {
            return 0x1F4;
        } else {
            return 0x3E8;
        }
    } else {
        return 0x7D0;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_006", func_0011FAE0);

INCLUDE_ASM("asm/nonmatchings/main_006", func_00120150);

INCLUDE_ASM("asm/nonmatchings/main_006", func_001206F0);

INCLUDE_ASM("asm/nonmatchings/main_006", func_001211B0);

INCLUDE_ASM("asm/nonmatchings/main_006", func_001214E0);

void func_001215E0(void *arg0, u8 arg1) {
    if (arg1 < 2) {
        if (arg1 == 1) {
            *(u32 *)((u8 *)arg0 + 8) =
                (*(u32 *)((u8 *)arg0 + 8) & 0xFFFF) | 0xFFFF0000;
        } else {
            *(u32 *)((u8 *)arg0 + 8) =
                (*(u32 *)((u8 *)arg0 + 8) & 0xFFFF0000) | 0xFFFF;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/main_006", func_00121630);

INCLUDE_ASM("asm/nonmatchings/main_006", func_00121800);

INCLUDE_ASM("asm/nonmatchings/main_006", func_00121CE0);

INCLUDE_ASM("asm/nonmatchings/main_006", func_00121E90);

INCLUDE_ASM("asm/nonmatchings/main_006", func_00122270);

void func_001224D0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28) {
    func_0027DE20(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
                  arg_sp0, arg_sp8, arg_sp10, arg_sp18, arg_sp20,
                  0, 1500, arg_sp28);
}

INCLUDE_ASM("asm/nonmatchings/main_006", func_00122530);

INCLUDE_ASM("asm/nonmatchings/main_006", func_00122680);

INCLUDE_ASM("asm/nonmatchings/main_006", func_00122810);

INCLUDE_ASM("asm/nonmatchings/main_006", func_00122970);

INCLUDE_ASM("asm/nonmatchings/main_006", func_001229F0);

INCLUDE_ASM("asm/nonmatchings/main_006", func_00122B50);

INCLUDE_ASM("asm/nonmatchings/main_006", func_00122D30);

INCLUDE_ASM("asm/nonmatchings/main_006", func_00123010);

INCLUDE_ASM("asm/nonmatchings/main_006", func_00123500);

s32 func_00123670(s32 arg0) {
    switch (arg0) {                                 /* irregular */
    case 0:
        return 0x303;
    case 1:
        return 0x304;
    default:
    case 2:
        return 0x302;
    }
}

s32 func_001236C0(s32 arg0) {
    s32 var_v0;

    switch (arg0) {
        case 0:
            var_v0 = 0x303;
            break;
        case 1:
            var_v0 = 0x304;
            break;
        case 2:
        default:
            var_v0 = 0x302;
            break;
    }
    if ((var_v0 >= 0) && (func_001E36E0(var_v0 & 0xFF, var_v0 >> 8) == 0)) {
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_006", func_00123740);

INCLUDE_ASM("asm/nonmatchings/main_006", func_00123D70);

INCLUDE_ASM("asm/nonmatchings/main_006", func_00123F90);

INCLUDE_ASM("asm/nonmatchings/main_006", func_00124040);

INCLUDE_ASM("asm/nonmatchings/main_006", func_00124520);

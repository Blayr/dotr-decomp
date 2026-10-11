#include "common.h"

s32 func_00153ED0(s32 arg0) {
    if (func_001DF470() > 1200) {
        if (func_001E0150(arg0) >= 4) {
            return 500;
        } else {
            return 1000;
        }
    } else {
        return 1500;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_013", func_00153F30);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00154040);

void func_00154210(void) {
    func_00172370();
}

INCLUDE_ASM("asm/nonmatchings/main_013", func_00154220);

INCLUDE_ASM("asm/nonmatchings/main_013", func_001547A0);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00154AD0);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00154EB0);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00155070);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00155230);

s32 func_001554B0(s32 arg0, s32 arg1, s32 arg2) {
    s32 i = 0;

    do {
        if (func_00155520(i, arg2) == ((arg1 << 8) | arg0)) {
            return 1;
        }
        i++;
    } while (i < 7);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_013", func_00155520);

INCLUDE_ASM("asm/nonmatchings/main_013", func_001555F0);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00155670);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00155770);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00155A00);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00155C90);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00155FB0);

void func_001562B0(s32 *arg0, s32 arg1, s32 arg2) {
    s32 temp_a0;
    s32 *temp_a1;
    s32 *temp_a2;

    temp_a1 = &arg0[arg1];
    temp_a2 = &arg0[arg2];
    temp_a0 = *temp_a1;
    *temp_a1 = *temp_a2;
    *temp_a2 = temp_a0;
}

INCLUDE_ASM("asm/nonmatchings/main_013", func_001562E0);

INCLUDE_ASM("asm/nonmatchings/main_013", func_001564E0);

INCLUDE_ASM("asm/nonmatchings/main_013", func_001566D0);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00156870);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00156910);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00156B40);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00156EA0);

s32 func_00156F70(void) {
    if (func_001E36E0(2, 3) == 0) {
        return 0x302;
    }
    return (func_001E36E0(4, 3) == 0) ? 0x304 : -1;
}

INCLUDE_ASM("asm/nonmatchings/main_013", func_00156FC0);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00157480);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00157A50);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00158360);

s32 func_00158780(s32 arg0) {
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

s32 func_001587E0(s32 arg0) {
    s32 result;

    result = (u32) (arg0 - 0x36) < 4U ? 1 : 0;
    return result;
}

void func_00158800(void) {
    func_00158810();
}

INCLUDE_ASM("asm/nonmatchings/main_013", func_00158810);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00158960);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00158AB0);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00158C80);

INCLUDE_ASM("asm/nonmatchings/main_013", func_001591B0);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00159380);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00159760);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00159930);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00159BE0);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00159D00);

void func_00159F80(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28) {
    func_0027DE20(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
                  arg_sp0, arg_sp8, arg_sp10, arg_sp18, arg_sp20,
                  0, 2500, arg_sp28);
}

INCLUDE_ASM("asm/nonmatchings/main_013", func_00159FE0);

void func_0015A120(s32 a0, s32 a1, u16 *buf) {
    s32 i;

    for (i = 0; i < 0x31; i++) {
        buf[i] = 0xFFFF;
    }
    func_0015A180(a0, a1, buf);
    func_0015A320(buf);
}

INCLUDE_ASM("asm/nonmatchings/main_013", func_0015A180);

s32 func_0015A2E0(s32 arg0, u16 *arg1) {
    s32 i;

    i = 0;
    do {
        if (arg0 == *arg1) {
            return 1;
        }
        i++;
        arg1++;
    } while (i < 0x31);
    return 0;
}

s32 func_0015A320(u16 *arg0) {
    s32 i;
    u8 count;

    count = 0;
    i = 0;
    do {
        if (*arg0 != 0xFFFF) {
            count++;
        }
        i++;
        arg0++;
    } while (i < 0x31);
    return count;
}

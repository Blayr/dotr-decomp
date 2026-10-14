#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_026", func_00184650);

void func_00184700(void) {
    func_00183E10();
}

INCLUDE_ASM("asm/nonmatchings/main_026", func_00184708);

void func_00184768(s32 arg0, s32 arg1, s32 arg2) {
    func_00184700();
    func_0017B520(arg0, arg1, arg2);
}

INCLUDE_ASM("asm/nonmatchings/main_026", func_001847B0);

void func_001847D8(s32 arg0, s32 arg1) {
    func_00184700();
    func_0017BD00(arg0, arg1);
}

INCLUDE_ASM("asm/nonmatchings/main_026", func_00184810);

s32 *func_001849A0(void) {
    return &D_0028D8F0;
}

INCLUDE_ASM("asm/nonmatchings/main_026", func_001849B0);

INCLUDE_ASM("asm/nonmatchings/main_026", func_00184A18);

INCLUDE_ASM("asm/nonmatchings/main_026", func_00184C88);

INCLUDE_ASM("asm/nonmatchings/main_026", func_00184D48);

INCLUDE_ASM("asm/nonmatchings/main_026", func_00184E10);

INCLUDE_ASM("asm/nonmatchings/main_026", func_00184FF8);

INCLUDE_ASM("asm/nonmatchings/main_026", func_00185100);

INCLUDE_ASM("asm/nonmatchings/main_026", func_001851E8);

INCLUDE_ASM("asm/nonmatchings/main_026", func_00185480);

INCLUDE_ASM("asm/nonmatchings/main_026", func_001854E0);

INCLUDE_ASM("asm/nonmatchings/main_026", func_00185578);

INCLUDE_ASM("asm/nonmatchings/main_026", func_00185890);

INCLUDE_ASM("asm/nonmatchings/main_026", func_001859D0);

INCLUDE_ASM("asm/nonmatchings/main_026", func_00186060);

void func_001860E8(s8 *arg0, s32 arg1) {
    s32 var_v0;
    s8 *var_a0;

    var_a0 = arg0;
    var_v0 = arg1 - 1;
    if (arg1 != 0) {
        do {
            *var_a0 = 0;
            var_v0 -= 1;
            var_a0 += 1;
        } while (var_v0 != -1);
    }
}

INCLUDE_ASM("asm/nonmatchings/main_026", func_00186120);

INCLUDE_ASM("asm/nonmatchings/main_026", func_00186148);

s32 func_00186228(s32 arg0) {
    s32 temp_v0;

    temp_v0 = D_0028D958;
    D_0028D958 = arg0;
    return temp_v0;
}

INCLUDE_ASM("asm/nonmatchings/main_026", func_00186238);

INCLUDE_ASM("asm/nonmatchings/main_026", func_00186410);

INCLUDE_ASM("asm/nonmatchings/main_026", func_00186448);

INCLUDE_ASM("asm/nonmatchings/main_026", func_00186470);

INCLUDE_ASM("asm/nonmatchings/main_026", func_00186548);

INCLUDE_ASM("asm/nonmatchings/main_026", func_00186630);

INCLUDE_ASM("asm/nonmatchings/main_026", func_00186718);

INCLUDE_ASM("asm/nonmatchings/main_026", func_001867E0);

INCLUDE_ASM("asm/nonmatchings/main_026", func_001868D0);

INCLUDE_ASM("asm/nonmatchings/main_026", func_001869C0);

INCLUDE_ASM("asm/nonmatchings/main_026", func_00186A88);

INCLUDE_ASM("asm/nonmatchings/main_026", func_00186B58);

s32 func_00186BA0(u32 *arg0, u32 arg1) {
    u32 temp_v0;

    temp_v0 = *arg0;
    *arg0 = arg1;
    return (temp_v0 >> 8) & 1;
}

INCLUDE_ASM("asm/nonmatchings/main_026", func_00186BB8);

INCLUDE_ASM("asm/nonmatchings/main_026", func_00186BD0);

INCLUDE_ASM("asm/nonmatchings/main_026", func_00186BE8);

INCLUDE_ASM("asm/nonmatchings/main_026", func_00186C48);

INCLUDE_ASM("asm/nonmatchings/main_026", func_00186C98);

INCLUDE_ASM("asm/nonmatchings/main_026", func_00186CC8);

INCLUDE_ASM("asm/nonmatchings/main_026", func_00186CF8);

INCLUDE_ASM("asm/nonmatchings/main_026", func_00186D08);

INCLUDE_ASM("asm/nonmatchings/main_026", func_00186D18);

INCLUDE_ASM("asm/nonmatchings/main_026", func_00186D58);

INCLUDE_ASM("asm/nonmatchings/main_026", func_00186D68);

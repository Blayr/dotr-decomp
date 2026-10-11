#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_003", func_00109CA0);

INCLUDE_ASM("asm/nonmatchings/main_003", func_00109D50);

void func_00109D70(s32 arg0) {
    if (arg0 != 0) {
        func_0010A160(0, 0);
        func_0010C720(0x5004, 0x7FFF);
    }
    func_0010C720(0xF006, arg0);
}

INCLUDE_ASM("asm/nonmatchings/main_003", func_00109DC0);

INCLUDE_ASM("asm/nonmatchings/main_003", func_00109E80);

INCLUDE_ASM("asm/nonmatchings/main_003", func_00109F10);

INCLUDE_ASM("asm/nonmatchings/main_003", func_00109F60);

INCLUDE_ASM("asm/nonmatchings/main_003", func_00109FC0);

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010A010);

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010A090);

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010A0F0);

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010A160);

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010A1D0);

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010A280);

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010A390);

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010A3B0);

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010A450);

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010A4D0);

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010A780);

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010A8A0);

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010A8B0);

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010A8D0);

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010AC20);

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010ADB0);

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010B1F0);

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010B270);

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010B330);

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010B360);

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010B3C0);

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010B490);

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010B6C0);

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010BBC0);

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010BC30);

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010BCC0);

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010BD40);

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010BDC0);

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010BDE0);

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010BE20);

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010BE60);

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010C110);

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010C220);

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010C290);

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010C2C0);

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010C2D0);

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010C3D0);

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010C580);

typedef char *VaList_0010C720;
#define VA_START_0010C720(ap, parm) \
    ((ap) = (char *)__builtin_next_arg(parm) - (__builtin_args_info(2) >= 8 ? 0 : (8 - __builtin_args_info(2)) * 8))
#define VA_ARG_0010C720(ap, T) (*(T *)((ap += 8) - 8))

extern s32 func_0017EA80(s32 *, s32, s32, s32 *, s32, s32 *, s32, s32, s32);

s32 func_0010C720(s32 cmd, ...) {
    s32 id;
    s32 i;
    VaList_0010C720 ap;

    if (D_0030FF40 == NULL) {
        return 0;
    }
    id = cmd;
    VA_START_0010C720(ap, cmd);
    D_0030FF40[0x20] = (s32)&D_0030FF40[0x20];
    for (i = 1; i < 7; i++) {
        D_0030FF40[0x20 + i] = VA_ARG_0010C720(ap, s32);
    }
    return func_0017EA80(&D_0030FF40[7], id, 0, &D_0030FF40[0x20], 0x40, &D_0030FF40[0x60], 0x10, 0, 0);
}

s32 func_0010C800(s32 arg0, s32 arg1, s32 arg2) {
    func_0017BB60(0);
    D_0030FF40[0x11] = arg0;
    D_0030FF40[0x12] = arg1;
    D_0030FF40[0x13] = arg2;
    D_0030FF40[0x14] = 0;
    D_0030FF40[0x19] = func_0017BCA0(&D_0030FF40[0x11], 1);
    return D_0030FF40[0x19];
}

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010C8A0);

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010C8B0);

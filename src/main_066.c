#include "common.h"

void func_002336F0(void) {
    s16 temp_s0;

    temp_s0 = D_00299ED4;
    func_001A8320(1, (s32) temp_s0);
    func_001A8320(2, (s32) D_00299E10);
    if (D_00299E10 == 0) {
        func_001A8320(3, 0x44C);
        func_001A8320(4, temp_s0 + 0x3E8);
    } else {
        func_001A8320(3, temp_s0 + 0x3E8);
        func_001A8320(4, 0x44C);
    }
    func_001A8870(1, 0);
}

INCLUDE_ASM("asm/nonmatchings/main_066", func_002337A0);

void func_00233F50(s8 arg0) {
    *(s16 *)0x01ED001C = 0;
    switch (arg0) {
    case 0:
        *(s16 *)0x01ED001A = 0;
        *(s16 *)0x01ED001E = 0;
        *(s16 *)0x01ED0020 = 0;
        *(s16 *)0x01ED0022 = 0;
        break;
    case 1:
        *(s16 *)0x01ED001A = 1;
        *(s16 *)0x01ED001E = 0x40;
        *(s16 *)0x01ED0020 = 0;
        *(s16 *)0x01ED0022 = 0;
        break;
    case 2:
        *(s16 *)0x01ED001A = 2;
        *(s16 *)0x01ED001E = 0x40;
        *(s16 *)0x01ED0020 = 0x40;
        *(s16 *)0x01ED0022 = 0;
        break;
    case 3:
        *(s16 *)0x01ED001A = 3;
        *(s16 *)0x01ED001E = 0x40;
        *(s16 *)0x01ED0020 = 0x40;
        *(s16 *)0x01ED0022 = 0x74;
        break;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_066", func_00234040);

INCLUDE_ASM("asm/nonmatchings/main_066", func_002347D0);

INCLUDE_ASM("asm/nonmatchings/main_066", func_002351A0);

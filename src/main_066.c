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

INCLUDE_ASM("asm/nonmatchings/main_066", func_00233F50);

INCLUDE_ASM("asm/nonmatchings/main_066", func_00234040);

INCLUDE_ASM("asm/nonmatchings/main_066", func_002347D0);

INCLUDE_ASM("asm/nonmatchings/main_066", func_002351A0);

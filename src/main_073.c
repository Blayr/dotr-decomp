#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_073", func_00250620);

INCLUDE_ASM("asm/nonmatchings/main_073", func_00250740);

INCLUDE_ASM("asm/nonmatchings/main_073", func_002507D0);

s32 func_00250860(s32 arg0, s32 arg1) {
    switch (arg0) {
    case 0:
    case 1:
        if (arg1 < arg0) {
            return arg0;
        }
        return arg1;
    case 7:
    case 6:
    case 0x270F:
    case 0x1F4:
    case 0x5DC:
        return arg1 >= arg0 ? arg0 : arg1;
    default:
        return 0;
    }
}

s32 func_002508D0(s32 arg0) {
    if (arg0 < 0) {
        return 0;
    }
    arg0 = arg0 > 9999 ? 9999 : arg0;
    return arg0;
}

INCLUDE_ASM("asm/nonmatchings/main_073", func_00250900);

INCLUDE_ASM("asm/nonmatchings/main_073", func_00250940);

INCLUDE_ASM("asm/nonmatchings/main_073", func_002509E0);

INCLUDE_ASM("asm/nonmatchings/main_073", func_00250A60);

INCLUDE_ASM("asm/nonmatchings/main_073", func_00250AC0);

INCLUDE_ASM("asm/nonmatchings/main_073", func_00250B40);

INCLUDE_ASM("asm/nonmatchings/main_073", func_00250BC0);

INCLUDE_ASM("asm/nonmatchings/main_073", func_00250C20);

INCLUDE_ASM("asm/nonmatchings/main_073", func_00250CA0);

INCLUDE_ASM("asm/nonmatchings/main_073", func_00250E80);

INCLUDE_ASM("asm/nonmatchings/main_073", func_00251060);

INCLUDE_ASM("asm/nonmatchings/main_073", func_00251370);

INCLUDE_ASM("asm/nonmatchings/main_073", func_002514F0);

INCLUDE_ASM("asm/nonmatchings/main_073", func_002516D0);

INCLUDE_ASM("asm/nonmatchings/main_073", func_002517D0);

INCLUDE_ASM("asm/nonmatchings/main_073", func_00252440);

#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_073", func_00250620);

void *func_00250740(s32 arg0, s32 arg1, s32 arg2) {
    void *var_v0;

    if (func_001DF540(arg0, arg1) == 0) {
        return NULL;
    }
    var_v0 = func_001E0B70(arg0, arg1, arg2);
    if (var_v0 == NULL) {
        return NULL;
    }
    if ((((s32 *)var_v0)[0] == -1) && (((s32 *)var_v0)[1] == -1)) {
        var_v0 = NULL;
    }
    return var_v0;
}

s32 func_002507D0(s32 arg0, s32 arg1) {
    s32 var_s0;

    if ((func_001E0700(arg0, arg1) >> 5) != 0) {
        return -1;
    }
    var_s0 = 0;
    do {
        if (func_00250740(arg0, arg1, var_s0) != NULL) {
            return 1;
        }
        var_s0++;
    } while (var_s0 <= 4);
    return 0;
}

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

s32 func_00250900(void *arg0) {
    u8 state;

    if (*((u8 *)arg0 + 0x45) == 0) {
        state = *((u8 *)arg0 + 0x44);
        if (state == 0 || state == 1) {
            return 1;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_073", func_00250940);

INCLUDE_ASM("asm/nonmatchings/main_073", func_002509E0);

INCLUDE_ASM("asm/nonmatchings/main_073", func_00250A60);

s32 func_00250AC0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_s0;
    s32 result;

    temp_s0 = func_002660E0(func_001DF540(arg0, arg1), arg2, arg3, 1);
    result = func_001E0290(arg0, arg1, 0);
    result += temp_s0;
    return result;
}

INCLUDE_ASM("asm/nonmatchings/main_073", func_00250B40);

INCLUDE_ASM("asm/nonmatchings/main_073", func_00250BC0);

s32 func_00250C20(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_s0;
    s32 result;

    temp_s0 = func_002660E0(func_001DF540(arg0, arg1), arg2, arg3, 0);
    result = func_001E0370(arg0, arg1, 0);
    return result + temp_s0;
}

INCLUDE_ASM("asm/nonmatchings/main_073", func_00250CA0);

INCLUDE_ASM("asm/nonmatchings/main_073", func_00250E80);

INCLUDE_ASM("asm/nonmatchings/main_073", func_00251060);

INCLUDE_ASM("asm/nonmatchings/main_073", func_00251370);

INCLUDE_ASM("asm/nonmatchings/main_073", func_002514F0);

INCLUDE_ASM("asm/nonmatchings/main_073", func_002516D0);

INCLUDE_ASM("asm/nonmatchings/main_073", func_002517D0);

INCLUDE_ASM("asm/nonmatchings/main_073", func_00252440);

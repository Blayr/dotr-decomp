#include "common.h"

s32 func_002494D0(void) {
    s32 roll;

    roll = func_0019A5C8() % 6;
    switch (roll) {
    case 0:
        return 0x23;
    case 1:
        return 0x4F;
    case 2:
        return 0x2C;
    case 3:
        return 0x5C;
    case 4:
        return 0x17B;
    case 5:
    default:
        return 0x18A;
    }
}

s32 func_00249560(s32 arg0) {
    return (D_0029D1F0[arg0 & 0xFFFF] == 0) ? 1 : 0;
}

u8 func_00249580(s32 arg0) {
    return D_0029D1F0[arg0 & 0xFFFF];
}

u32 func_002495A0(s32 arg0, s32 arg1) {
    s32 i;
    u32 *entry;
    u32 packed;
    s32 temp;

    if (arg0 < arg1) {
        temp = arg0;
        arg0 = arg1;
        arg1 = temp;
    }
    entry = D_0029E830;
    i = 0;
    do {
        packed = *entry;
        if ((arg0 == (packed & 0x3FF)) &&
            (arg1 == ((packed & 0xFFC00) >> 10))) {
            return (D_0029E830[i] & 0x3FF00000) >> 20;
        }
        i++;
        entry++;
    } while (i < 0x67AC);
    return 0x3E7U;
}

s32 func_00249630(s32 arg0, s32 arg1) {
    void *temp_v0;

    temp_v0 = func_00250740(arg0, arg1, 1);
    if ((temp_v0 != NULL) && ((*(u32 *)temp_v0 >> 8) == 9)) {
        return *(u16 *)((u8 *)temp_v0 + 4);
    }
    return -1;
}

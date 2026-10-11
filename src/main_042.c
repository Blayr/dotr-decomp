#include "common.h"

void func_001CDD40(void) {
    u8 *p;
    s32 i;

    p = D_0031A7C0;
    i = 0;
    do {
        func_001CDD90(p);
        i += 1;
        p += 0xA0;
    } while (i < 6);
}

INCLUDE_ASM("asm/nonmatchings/main_042", func_001CDD90);

void *func_001CDE70(s32 arg0) {
    if (arg0 < 0 || arg0 >= 6) {
        return NULL;
    }

    return &D_0031A7C0[arg0 * 0xA0];
}

INCLUDE_ASM("asm/nonmatchings/main_042", func_001CDEB0);

void func_001CE400(void) {
    func_00209D30(func_001CE430(func_00209D20()));
}

INCLUDE_ASM("asm/nonmatchings/main_042", func_001CE430);

INCLUDE_ASM("asm/nonmatchings/main_042", func_001CEA50);

INCLUDE_ASM("asm/nonmatchings/main_042", func_001CECF0);

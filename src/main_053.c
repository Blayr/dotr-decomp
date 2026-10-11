#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FB500);

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FB6A0);

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FB940);

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FBE50);

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FC050);

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FC210);

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FC6D0);

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FC760);

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FC7F0);

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FC840);

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FC890);

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FC950);

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FC9B0);

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FCA70);

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FCAB0);

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FCC20);

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FCC70);

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FCD60);

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FCDA0);

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FCDE0);

void func_001FCF30(s32 arg0, s32 arg1, s32 arg2) {
    func_00209D30(func_001FCF90(func_00209D20(), arg0, arg1, arg2));
}

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FCF90);

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FD0B0);

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FD130);

s32 func_001FD1B0(s32 arg0) {
    Entry_0031C050 *e;

    if (arg0 < 0 || arg0 >= 2) {
        return -1;
    }
    e = &D_0031C050[arg0];
    if (e->flag != 0) {
        return -1;
    }
    return e->hi - e->lo;
}

static inline s32 calc_001FD220(s32 idx) {
    Entry_0031C050 *e;

    if (idx < 0 || idx >= 2) {
        return -1;
    }
    e = &D_0031C050[idx];
    if (e->flag) {
        return -1;
    }
    return e->hi - e->lo;
}

s32 func_001FD220(s32 arg0) {
    s32 i;
    s32 want = arg0 ? 1 : 0;

    for (i = 0; i < 2; i++) {
        if (calc_001FD220(i) >= want) {
            return 1;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FD2B0);

s32 func_001FD2D0(s32 arg0, s32 arg1) {
    s32 sp3C;

    func_00209D30(func_001FD320(func_00209D20(), arg0, arg1, &sp3C));
    return sp3C;
}

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FD320);

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FD4B0);

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FD4C0);

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FD610);

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FD680);

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FDB90);

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FDD70);

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FDFE0);

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FE290);

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FE660);

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FE750);

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FE7D0);

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FE880);

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FE8F0);

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FEA80);

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FEAB0);

typedef struct {
    u8 pad00[0x13];
    s8 low_001FEAF0 : 7;
    s8 flag_001FEAF0 : 1;
} Entry_001FEAF0;

typedef struct {
    u8 pad00[0xC];
    Entry_001FEAF0 entries[30];
} Table_001FEAF0;

extern Table_001FEAF0 D_0031C070;

void func_001FEAF0(s32 arg0) {
    Table_001FEAF0 *t = &D_0031C070;

    if (arg0 >= 0 && arg0 < 0x1E) {
        t->entries[arg0].flag_001FEAF0 = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FEB40);

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FEB80);

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FEC70);

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FECB0);

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FEDA0);

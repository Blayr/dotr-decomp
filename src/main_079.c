#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027AF20);

void func_0027AF80(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 var_a2;
    s32 *var_a3;

    *(s8 *)arg0 = (s8) ((arg3 << 4) | arg2);
    var_a2 = 0;
    var_a3 = arg0;
    do {
        var_a2 += 1;
        var_a3[1] = 0;
        var_a3++;
    } while (var_a2 < 0xC);
    *(s32 *)((u8 *)arg0 + 0x34) = arg1;
}

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027AFC0);

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027B010);

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027B150);

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027B1B0);

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027B200);

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027B290);

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027B360);

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027B520);

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027B650);

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027B740);

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027B860);

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027B9B0);

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027BBC0);

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027BE10);

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027C070);

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027C2C0);

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027C5A0);

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027C670);

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027C6D0);

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027C770);

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027CA50);

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027D020);

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027D720);

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027D830);

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027DA40);

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027DBC0);

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027DD20);

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027DE20);

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027E150);

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027E210);

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027E360);

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027E5B0);

void func_0027E770(void) {

}

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027E780);

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027E840);

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027EB00);

void func_0027F0D0(void *arg0) {
    f32 *values = arg0;

    values[0] = values[1] = values[2] = values[3] = 1.0f;
    values[4] = values[5] = values[6] = values[7] = 0.0f;
    values[8] = values[9] = values[10] = values[11] = 0.0f;
}

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027F110);

s32 func_0027F160(s32 arg0, s32 arg1) {
    return !(arg0 & (1 << arg1)) ? 0 : 1;
}

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027F180);

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027F290);

void func_0027F360(void *arg0, void *arg1) {
    f32 *dst = arg0;
    f32 *src = arg1;

    dst[0] += src[0];
    dst[1] += src[1];
    dst[2] += src[2];
}

void func_0027F3A0(void *arg0, void *arg1) {
    f32 *dst = arg0;
    f32 *src = arg1;

    dst[0] -= src[0];
    dst[1] -= src[1];
    dst[2] -= src[2];
}

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027F3E0);

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027F480);

void func_0027F5A0(void) {

}

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027F5B0);

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027F630);

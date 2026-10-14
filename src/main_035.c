#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019AE78);

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019AEB8);

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019B0A0);

void func_0019B0F8(s32 arg0, s32 arg1, s32 arg2) {
    func_0019B148(D_0028FA98, arg0, arg1, arg2);
}

void func_0019B128(s32 arg0) {
    func_0019B418(D_0028FA98, arg0);
}

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019B148);

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019B418);

f32 func_0019B4B8(f32 fparg0, f32 fparg1) {
    u32 gw0;
    u32 gw4;

    do { fshape gf_u; gf_u.value = (fparg0); (gw0) = gf_u.word; } while (0);
    do { fshape gf_u; gf_u.value = (fparg1); (gw4) = gf_u.word; } while (0);
    do { fshape sf_u; sf_u.word = (((gw0 & 0x7FFFFFFF) | (gw4 & 0x80000000))); (fparg0) = sf_u.value; } while (0);
    return fparg0;
}

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019B4F8);

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019B5C0);

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019B648);

s32 func_0019B6D8(void) {
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019B6E0);

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019B788);

s32 func_0019B7F0(void *arg0, s32 arg1, s32 arg2) {
    if ((*(u16 *)((u8 *)arg0 + 0xC)) & 0x100) {
        func_001977D8((*(s32 *)((u8 *)arg0 + 0x54)), (*(s16 *)((u8 *)arg0 + 0xE)), 0, 2);
    }
    (*(u16 *)((u8 *)arg0 + 0xC)) = (u16) ((*(s32 *)((u8 *)arg0 + 0xC)) & 0xEFFF);
    return func_001A0478((*(s32 *)((u8 *)arg0 + 0x54)), (*(s16 *)((u8 *)arg0 + 0xE)), arg1, arg2);
}

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019B870);

void func_0019B8D8(void *arg0) {
    func_001951F8((*(s32 *)((u8 *)arg0 + 0x54)), (*(s16 *)((u8 *)arg0 + 0xE)));
}

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019B8F8);

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019B9D0);

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019BB00);

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019BC90);

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019BDD8);

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019BEF0);

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019C028);

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019C100);

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019C2B8);

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019C478);

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019C4C8);

void func_0019D3E0(s32 arg0, s32 arg1) {
    func_0019C4C8(D_0028FA98, arg0, arg1);
}

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019D408);

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019D430);

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019D450);

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019D518);

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019D750);

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019D780);

void func_0019D9B0(s32 arg0, s32 arg1, s32 arg2) {
    func_0019D780(D_0028FA98, arg0, arg1, arg2);
}

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019D9E0);

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019DA00);

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019DAE8);

s32 func_0019DC70(s32 arg0, void *arg1) {
    s32 temp_v0;

    if ((*(s32 *)((u8 *)arg1 + 8)) == 0) {
        (*(s32 *)((u8 *)arg1 + 4)) = 0;
        return 0;
    }
    temp_v0 = func_001970A8();
    (*(s32 *)((u8 *)arg1 + 8)) = 0;
    (*(s32 *)((u8 *)arg1 + 4)) = 0;
    return temp_v0;
}

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019DCB8);

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019DD70);

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019DDE8);

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019F448);

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019F608);

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019F6E8);

INCLUDE_ASM("asm/nonmatchings/main_035", func_001A0378);

INCLUDE_ASM("asm/nonmatchings/main_035", func_001A0478);

INCLUDE_ASM("asm/nonmatchings/main_035", func_001A04D8);

INCLUDE_ASM("asm/nonmatchings/main_035", func_001A05E8);

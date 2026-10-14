#include "common.h"

s32 func_00195070(s32 arg0) {
    return arg0 < 0 ? -arg0 : arg0;
}

void func_00195088(s32 arg0) {
    func_0019D3E0(arg0, 0);
}

s32 func_001950A0(const char *s) {
    return func_0019D750(s, NULL, 10);
}

void func_001950C8(s8 *arg0) {
    func_0019D750(arg0, NULL, 0xA);
}

void func_001950E8(s32 arg0, s32 arg1) {
    func_00198840(arg1, arg0);
}

void func_00195108(s32 arg0, s32 arg1) {
    s32 var_a0;
    s32 var_v0;

    var_a0 = arg0;
    var_v0 = arg1 - 1;
    if (arg1 != 0) {
        do {
            var_v0 -= 1;
            *(s8 *)var_a0 = 0;
            var_a0 += 1;
        } while (var_v0 != -1);
    }
}

INCLUDE_ASM("asm/nonmatchings/main_033b", func_00195140);

s32 func_001951F8(s32 *ptr, s32 fd) {
    s32 ret;
    D_003512F8 = 0;
    if ((ret = ((s32 (*)(s32))func_0017BFC8)(fd)) == -1 && D_003512F8 != 0)
        *ptr = D_003512F8;
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/main_033b", func_00195250);

INCLUDE_ASM("asm/nonmatchings/main_033b", func_00195480);

void func_001966E8(void) {
}

void func_001966F0(void) {
}

s32 func_001966F8(void) {
    return D_0028FA98;
}

INCLUDE_ASM("asm/nonmatchings/main_033b", func_00196708);

void func_00196820(void *arg0, s16 arg1, s16 arg2, s32 arg3) {
    (*(s32 *)((u8 *)arg0 + 0x54)) = arg3;
    (*(s16 *)((u8 *)arg0 + 0xC)) = arg1;
    (*(s16 *)((u8 *)arg0 + 0xE)) = arg2;
    (*(s32 **)((u8 *)arg0 + 0x20)) = &func_0019B788;
    (*(s32 **)((u8 *)arg0 + 0x24)) = &func_0019B7F0;
    (*(s32 **)((u8 *)arg0 + 0x28)) = &func_0019B870;
    (*(void (**)(void *))((u8 *)arg0 + 0x2C)) = func_0019B8D8;
    (*(s32 *)((u8 *)arg0 + 4)) = 0;
    (*(s32 *)((u8 *)arg0 + 8)) = 0;
    (*(s32 *)((u8 *)arg0 + 0x10)) = 0;
    (*(s32 *)((u8 *)arg0 + 0x14)) = 0;
    (*(s32 *)((u8 *)arg0 + 0x18)) = 0;
    (*(void **)((u8 *)arg0 + 0x1C)) = arg0;
    (*(s32 *)arg0) = 0;
}

INCLUDE_ASM("asm/nonmatchings/main_033b", func_00196880);

INCLUDE_ASM("asm/nonmatchings/main_033b", func_001968F8);

INCLUDE_ASM("asm/nonmatchings/main_033b", func_001969F0);

void func_00196A10(void) {
    func_001969F0(D_0028FA98);
}

void func_00196A30(void *arg0) {
    void *temp_s1;

    temp_s1 = arg0 + 0x1E4;
    (*(s32 (**)(s32))((u8 *)arg0 + 0x3C)) = func_001969F0;
    (*(s32 *)((u8 *)arg0 + 0x38)) = 1;
    func_00196820(temp_s1, 4, 0, arg0);
    func_00196820(arg0 + 0x23C, 9, 1, arg0);
    func_00196820(arg0 + 0x294, 0xA, 2, arg0);
    (*(s32 *)((u8 *)arg0 + 0x1D8)) = 0;
    (*(void **)((u8 *)arg0 + 0x1E0)) = temp_s1;
    (*(s32 *)((u8 *)arg0 + 0x1DC)) = 3;
}

INCLUDE_ASM("asm/nonmatchings/main_033b", func_00196AC0);

INCLUDE_ASM("asm/nonmatchings/main_033b", func_00196BE0);

INCLUDE_ASM("asm/nonmatchings/main_033b", func_00196ED8);

s32 func_00197048(s32 *ptr, s32 fd, void *st) {
    s32 ret;
    D_003512F8 = 0;
    if ((ret = func_0017C098(fd, st)) == -1 && D_003512F8 != 0)
        *ptr = D_003512F8;
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/main_033b", func_001970A8);

INCLUDE_ASM("asm/nonmatchings/main_033b", func_00197488);

void func_00197520(s32 arg0, s32 arg1) {
    func_00197570(D_0028FA98, arg0, arg1);
}

u8 *func_00197548(s32 arg0) {
    s32 sp0[4];
    return func_00197570(D_0028FA98, arg0, (s32) sp0);
}

INCLUDE_ASM("asm/nonmatchings/main_033b", func_00197570);

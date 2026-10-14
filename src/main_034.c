#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_034", func_001976B8);

INCLUDE_ASM("asm/nonmatchings/main_034", func_001976D8);

INCLUDE_ASM("asm/nonmatchings/main_034", func_001976F0);

s32 *func_00197780(void) {
    return &D_002BD230;
}

void func_00197790(s32 arg0, s32 arg1) {
    func_001976F0(D_0028FA98, arg0, arg1);
}

INCLUDE_ASM("asm/nonmatchings/main_034", func_001977B8);

INCLUDE_ASM("asm/nonmatchings/main_034", func_001977D8);

INCLUDE_ASM("asm/nonmatchings/main_034", func_00197838);

INCLUDE_ASM("asm/nonmatchings/main_034", func_00197990);

INCLUDE_ASM("asm/nonmatchings/main_034", func_001979F8);

INCLUDE_ASM("asm/nonmatchings/main_034", func_00197BC0);

s32 func_00197C18(s32 arg0) {
    func_00198A08(D_0028FA98);
    func_00196BE0(D_0028FA98, arg0);
    return func_00198A88(D_0028FA98);
}

INCLUDE_ASM("asm/nonmatchings/main_034", func_00197C60);

INCLUDE_ASM("asm/nonmatchings/main_034", func_00197EB8);

INCLUDE_ASM("asm/nonmatchings/main_034", func_001985E0);

INCLUDE_ASM("asm/nonmatchings/main_034", func_00198618);

INCLUDE_ASM("asm/nonmatchings/main_034", func_001986F8);

INCLUDE_ASM("asm/nonmatchings/main_034", func_00198790);

INCLUDE_ASM("asm/nonmatchings/main_034", func_00198840);

INCLUDE_ASM("asm/nonmatchings/main_034", func_00198948);

INCLUDE_ASM("asm/nonmatchings/main_034", func_00198A08);

INCLUDE_ASM("asm/nonmatchings/main_034", func_00198A88);

INCLUDE_ASM("asm/nonmatchings/main_034", func_00198AD8);

void func_00198B80(void *arg0, void *arg1) {
    void **temp_v0;

    if (arg1 != NULL) {
        temp_v0 = ((*(s32 *)((u8 *)arg1 + 4)) * 4) + (*(s32 *)((u8 *)arg0 + 0x4C));
        (*(void **)arg1) = (void *) *temp_v0;
        *temp_v0 = arg1;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_034", func_00198BB0);

INCLUDE_ASM("asm/nonmatchings/main_034", func_00198CB8);

INCLUDE_ASM("asm/nonmatchings/main_034", func_00198DE8);

INCLUDE_ASM("asm/nonmatchings/main_034", func_00198E68);

INCLUDE_ASM("asm/nonmatchings/main_034", func_00198F28);

INCLUDE_ASM("asm/nonmatchings/main_034", func_00198F60);

INCLUDE_ASM("asm/nonmatchings/main_034", func_00199170);

INCLUDE_ASM("asm/nonmatchings/main_034", func_00199270);

INCLUDE_ASM("asm/nonmatchings/main_034", func_001993C8);

INCLUDE_ASM("asm/nonmatchings/main_034", func_00199430);

INCLUDE_ASM("asm/nonmatchings/main_034", func_001995C0);

INCLUDE_ASM("asm/nonmatchings/main_034", func_00199690);

INCLUDE_ASM("asm/nonmatchings/main_034", func_00199828);

INCLUDE_ASM("asm/nonmatchings/main_034", func_001999B0);

INCLUDE_ASM("asm/nonmatchings/main_034", func_00199A80);

INCLUDE_ASM("asm/nonmatchings/main_034", func_00199AF0);

INCLUDE_ASM("asm/nonmatchings/main_034", func_00199B50);

INCLUDE_ASM("asm/nonmatchings/main_034", func_00199BC0);

void func_0019A5B0(s64 arg0) {
    (*(u64 *)((u8 *)D_0028FA98 + 0xA8)) = (u64) ((u64) (arg0 << 0x20) >> 0x20);
}

INCLUDE_ASM("asm/nonmatchings/main_034", func_0019A5C8);

INCLUDE_ASM("asm/nonmatchings/main_034", func_0019A630);

INCLUDE_ASM("asm/nonmatchings/main_034", func_0019A690);

s32 func_0019AC30(void *arg0) {
    if (((*(u16 *)((u8 *)arg0 + 0xC)) & 9) == 9) {
        return func_00196708();
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_034", func_0019AC68);

INCLUDE_ASM("asm/nonmatchings/main_034", func_0019ADE8);

INCLUDE_ASM("asm/nonmatchings/main_034", func_0019AE30);

#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_040", func_001BA3B0);

INCLUDE_ASM("asm/nonmatchings/main_040", func_001BA420);

INCLUDE_ASM("asm/nonmatchings/main_040", func_001BA520);

void func_001BA5F0(void) {
    func_00199BC0(D_00317B68, 0x356, 2, func_001BA630);
}

void func_001BA610(void) {
    func_00199BC0(D_00317B6C + 2, 0x28, 2, func_001BA710);
}

INCLUDE_ASM("asm/nonmatchings/main_040", func_001BA630);

INCLUDE_ASM("asm/nonmatchings/main_040", func_001BA710);

INCLUDE_ASM("asm/nonmatchings/main_040", func_001BA7F0);

INCLUDE_ASM("asm/nonmatchings/main_040", func_001BA8A0);

INCLUDE_ASM("asm/nonmatchings/main_040", func_001BA930);

s32 func_001BA9C0(u16 *arg0, u16 *arg1) {
    s32 var_v0;
    s32 var_v1;
    s32 temp_s0;
    u8 *temp_s0_2;
    u8 *temp_v0;

    temp_s0 = *arg1;
    temp_s0_2 = func_001DD0E0(*arg0);
    temp_v0 = func_001DD0E0(temp_s0);
    var_v1 = -1;
    if (temp_s0_2 != NULL) {
        var_v1 = *(u16 *)(temp_s0_2 + 8) & 0x1FFF;
    }
    var_v0 = (temp_v0 != NULL) ? (*(u16 *)(temp_v0 + 8) & 0x1FFF) : -1;
    if (var_v1 < var_v0) {
        var_v0 = 1;
    } else {
        var_v0 = (var_v0 < var_v1) ? -1 : 0;
    }
    return var_v0;
}

s32 func_001BAA30(u16 *arg0, u16 *arg1) {
    s32 var_v0;
    s32 var_v1;
    s32 result;
    s32 temp_s0;
    u8 *temp_s0_2;
    u8 *temp_v0;

    temp_s0 = *arg1;
    temp_s0_2 = func_001DD0E0(*arg0);
    temp_v0 = func_001DD0E0(temp_s0);
    var_v1 = -1;
    if (temp_s0_2 != NULL) {
        var_v1 = *(u16 *)(temp_s0_2 + 0xA) & 0x1FFF;
    }
    if (temp_v0 != NULL) {
        var_v0 = *(u16 *)(temp_v0 + 0xA) & 0x1FFF;
    } else {
        var_v0 = -1;
    }
    if (var_v1 < var_v0) {
        result = 1;
    } else {
        result = (var_v0 < var_v1) ? -1 : 0;
    }
    return result;
}

INCLUDE_ASM("asm/nonmatchings/main_040", func_001BAAA0);

INCLUDE_ASM("asm/nonmatchings/main_040", func_001BAB60);

INCLUDE_ASM("asm/nonmatchings/main_040", func_001BAC00);

INCLUDE_ASM("asm/nonmatchings/main_040", func_001BAC90);

INCLUDE_ASM("asm/nonmatchings/main_040", func_001BAD40);

s32 func_001BAE40(u16 *arg0, u16 *arg1) {
    u16 temp_v1;
    u16 temp_v0;
    s32 result;

    temp_v1 = *arg0;
    temp_v0 = *arg1;
    if ((s32) temp_v1 > (s32) temp_v0) {
        result = 1;
    } else {
        result = ((s32) temp_v1 < (s32) temp_v0) ? -1 : 0;
    }
    return result;
}

void func_001BAE70(void) {
    func_00209D30(func_001BAEA0(func_00209D20()));
}

INCLUDE_ASM("asm/nonmatchings/main_040", func_001BAEA0);

INCLUDE_ASM("asm/nonmatchings/main_040", func_001BB260);

INCLUDE_ASM("asm/nonmatchings/main_040", func_001BB6D0);

INCLUDE_ASM("asm/nonmatchings/main_040", func_001BB940);

INCLUDE_ASM("asm/nonmatchings/main_040", func_001BC350);

INCLUDE_ASM("asm/nonmatchings/main_040", func_001BCCE0);

INCLUDE_ASM("asm/nonmatchings/main_040", func_001BCE20);

INCLUDE_ASM("asm/nonmatchings/main_040", func_001BD8A0);

INCLUDE_ASM("asm/nonmatchings/main_040", func_001BDAF0);

INCLUDE_ASM("asm/nonmatchings/main_040", func_001BE5F0);

INCLUDE_ASM("asm/nonmatchings/main_040", func_001BF180);

INCLUDE_ASM("asm/nonmatchings/main_040", func_001BF2A0);

INCLUDE_ASM("asm/nonmatchings/main_040", func_001BF470);

INCLUDE_ASM("asm/nonmatchings/main_040", func_001BF710);

INCLUDE_ASM("asm/nonmatchings/main_040", func_001BFF00);

INCLUDE_ASM("asm/nonmatchings/main_040", func_001C02E0);

INCLUDE_ASM("asm/nonmatchings/main_040", func_001C05F0);

INCLUDE_ASM("asm/nonmatchings/main_040", func_001C07E0);

INCLUDE_ASM("asm/nonmatchings/main_040", func_001C0A30);

INCLUDE_ASM("asm/nonmatchings/main_040", func_001C0CE0);

INCLUDE_ASM("asm/nonmatchings/main_040", func_001C0EE0);

INCLUDE_ASM("asm/nonmatchings/main_040", func_001C0F70);

INCLUDE_ASM("asm/nonmatchings/main_040", func_001C1000);

INCLUDE_ASM("asm/nonmatchings/main_040", func_001C1090);

void func_001C1270(void) {
    func_001E7E70(0x1D, -1, 0x3E7);
    func_001F9940(0, 4, 0);
}

INCLUDE_ASM("asm/nonmatchings/main_040", func_001C12B0);

void func_001C1AD0(void) {
    func_00209D30(func_001C1B00(func_00209D20()));
}

INCLUDE_ASM("asm/nonmatchings/main_040", func_001C1B00);

INCLUDE_ASM("asm/nonmatchings/main_040", func_001C1FE0);

INCLUDE_ASM("asm/nonmatchings/main_040", func_001C21A0);

INCLUDE_ASM("asm/nonmatchings/main_040", func_001C2300);

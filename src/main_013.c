#include "common.h"

s32 func_00153ED0(s32 arg0) {
    if (func_001DF470() > 1200) {
        if (func_001E0150(arg0) >= 4) {
            return 500;
        } else {
            return 1000;
        }
    } else {
        return 1500;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_013", func_00153F30);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00154040);

void func_00154210(void) {
    func_00172370();
}

INCLUDE_ASM("asm/nonmatchings/main_013", func_00154220);

INCLUDE_ASM("asm/nonmatchings/main_013", func_001547A0);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00154AD0);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00154EB0);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00155070);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00155230);

s32 func_001554B0(s32 arg0, s32 arg1, s32 arg2) {
    s32 i = 0;

    do {
        if (func_00155520(i, arg2) == ((arg1 << 8) | arg0)) {
            return 1;
        }
        i++;
    } while (i < 7);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_013", func_00155520);

INCLUDE_ASM("asm/nonmatchings/main_013", func_001555F0);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00155670);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00155770);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00155A00);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00155C90);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00155FB0);

INCLUDE_ASM("asm/nonmatchings/main_013", func_001562B0);

INCLUDE_ASM("asm/nonmatchings/main_013", func_001562E0);

INCLUDE_ASM("asm/nonmatchings/main_013", func_001564E0);

INCLUDE_ASM("asm/nonmatchings/main_013", func_001566D0);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00156870);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00156910);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00156B40);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00156EA0);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00156F70);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00156FC0);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00157480);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00157A50);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00158360);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00158780);

s32 func_001587E0(s32 arg0) {
    s32 result;

    result = (u32) (arg0 - 0x36) < 4U ? 1 : 0;
    return result;
}

void func_00158800(void) {
    func_00158810();
}

INCLUDE_ASM("asm/nonmatchings/main_013", func_00158810);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00158960);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00158AB0);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00158C80);

INCLUDE_ASM("asm/nonmatchings/main_013", func_001591B0);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00159380);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00159760);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00159930);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00159BE0);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00159D00);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00159F80);

INCLUDE_ASM("asm/nonmatchings/main_013", func_00159FE0);

void func_0015A120(s32 a0, s32 a1, u16 *buf) {
    s32 i;

    for (i = 0; i < 0x31; i++) {
        buf[i] = 0xFFFF;
    }
    func_0015A180(a0, a1, buf);
    func_0015A320(buf);
}

INCLUDE_ASM("asm/nonmatchings/main_013", func_0015A180);

INCLUDE_ASM("asm/nonmatchings/main_013", func_0015A2E0);

INCLUDE_ASM("asm/nonmatchings/main_013", func_0015A320);

#include "common.h"

void func_001C2530(void) {

}

INCLUDE_ASM("asm/nonmatchings/main_041", func_001C2540);

INCLUDE_ASM("asm/nonmatchings/main_041", func_001C2720);

INCLUDE_ASM("asm/nonmatchings/main_041", func_001C32B0);

INCLUDE_ASM("asm/nonmatchings/main_041", func_001C33A0);

typedef struct {
    u8 pad_000[0x6D8];
    s32 values[2];
    u8 pad_6E0[0x67C];
    s8 selection;
} State_001C3520;

void func_001C3520(s32 arg0) {
    State_001C3520 *state = (State_001C3520 *)D_00317490;
    s32 var_a1;
    void (*var_a3)(void);

    if (arg0 != 0) {
        var_a1 = state->values[1];
    } else {
        var_a1 = state->values[0];
    }
    if (arg0 != 0) {
        var_a3 = func_001BA710;
    } else {
        var_a3 = func_001BA630;
    }
    state->selection = arg0;
    func_00199BC0(var_a1, 0x356, 2, var_a3);
}

void func_001C3570(void) {
    func_00209D30(func_001C35A0(func_00209D20()));
}

INCLUDE_ASM("asm/nonmatchings/main_041", func_001C35A0);

INCLUDE_ASM("asm/nonmatchings/main_041", func_001C38E0);

INCLUDE_ASM("asm/nonmatchings/main_041", func_001C3D50);

INCLUDE_ASM("asm/nonmatchings/main_041", func_001C3E20);

INCLUDE_ASM("asm/nonmatchings/main_041", func_001C4B00);

INCLUDE_ASM("asm/nonmatchings/main_041", func_001C5550);

INCLUDE_ASM("asm/nonmatchings/main_041", func_001C5870);

INCLUDE_ASM("asm/nonmatchings/main_041", func_001C5980);

INCLUDE_ASM("asm/nonmatchings/main_041", func_001C5B30);

void func_001C5CE0(s32 arg0, s32 arg1, s32 arg2) {
    s32 text = (s32) &D_002BF040;
    s32 length = func_0019BEF0((const char *) text);

    func_001B0CE0(arg0, 2, -1, 0x80, arg1 + 0x140, arg2 + 0xA3,
                  0x140, 0x7A, length, text, 1);
}

INCLUDE_ASM("asm/nonmatchings/main_041", func_001C5D70);

INCLUDE_ASM("asm/nonmatchings/main_041", func_001C5DB8);

void func_001C6120(void) {

}

INCLUDE_ASM("asm/nonmatchings/main_041", func_001C6130);

INCLUDE_ASM("asm/nonmatchings/main_041", func_001C6170);

void func_001C7430(void) {
    func_00209D30(func_001C7460(func_00209D20()));
}

INCLUDE_ASM("asm/nonmatchings/main_041", func_001C7460);

INCLUDE_ASM("asm/nonmatchings/main_041", func_001C7790);

INCLUDE_ASM("asm/nonmatchings/main_041", func_001C7C00);

INCLUDE_ASM("asm/nonmatchings/main_041", func_001C7D20);

INCLUDE_ASM("asm/nonmatchings/main_041", func_001C8590);

INCLUDE_ASM("asm/nonmatchings/main_041", func_001C8690);

INCLUDE_ASM("asm/nonmatchings/main_041", func_001C8DC0);

INCLUDE_ASM("asm/nonmatchings/main_041", func_001C92C0);

INCLUDE_ASM("asm/nonmatchings/main_041", func_001C9C60);

INCLUDE_ASM("asm/nonmatchings/main_041", func_001CA0E0);

INCLUDE_ASM("asm/nonmatchings/main_041", func_001CA450);

INCLUDE_ASM("asm/nonmatchings/main_041", func_001CA7C0);

INCLUDE_ASM("asm/nonmatchings/main_041", func_001CB6B0);

INCLUDE_ASM("asm/nonmatchings/main_041", func_001CC380);

INCLUDE_ASM("asm/nonmatchings/main_041", func_001CC4B0);

void func_001CC610(void) {

}

INCLUDE_ASM("asm/nonmatchings/main_041", func_001CC620);

void func_001CCB80(void) {
    func_00209D30(func_001CCBB0(func_00209D20()));
}

INCLUDE_ASM("asm/nonmatchings/main_041", func_001CCBB0);

INCLUDE_ASM("asm/nonmatchings/main_041", func_001CCEA0);

INCLUDE_ASM("asm/nonmatchings/main_041", func_001CD560);

void func_001CD6E0(void) {
    func_00209D30(func_001CD710(func_00209D20()));
}

INCLUDE_ASM("asm/nonmatchings/main_041", func_001CD710);

void func_001CDA10(void) {
    u8 *entry;
    s32 i;

    entry = D_003193C0;
    i = 0;
    do {
        func_001CDA60(entry);
        i += 1;
        entry += 0xA0;
    } while (i < 0x20);
}

s32 func_001CDA60(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    func_001CD560();
    *(s32 *)((u8 *)arg0 + 0x90) = 0;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_041", func_001CDAA0);

INCLUDE_ASM("asm/nonmatchings/main_041", func_001CDB00);

#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_021", func_0017BAB0);

INCLUDE_ASM("asm/nonmatchings/main_021", func_0017BAC0);

INCLUDE_ASM("asm/nonmatchings/main_021", func_0017BAD0);

INCLUDE_ASM("asm/nonmatchings/main_021", func_0017BAE0);

INCLUDE_ASM("asm/nonmatchings/main_021", func_0017BAF0);

INCLUDE_ASM("asm/nonmatchings/main_021", func_0017BB00);

INCLUDE_ASM("asm/nonmatchings/main_021", func_0017BB10);

INCLUDE_ASM("asm/nonmatchings/main_021", func_0017BB20);

INCLUDE_ASM("asm/nonmatchings/main_021", func_0017BB30);

INCLUDE_ASM("asm/nonmatchings/main_021", func_0017BB40);

INCLUDE_ASM("asm/nonmatchings/main_021", func_0017BB50);

INCLUDE_ASM("asm/nonmatchings/main_021", func_0017BB60);

INCLUDE_ASM("asm/nonmatchings/main_021", func_0017BB70);

INCLUDE_ASM("asm/nonmatchings/main_021", func_0017BB80);

INCLUDE_ASM("asm/nonmatchings/main_021", func_0017BB90);

INCLUDE_ASM("asm/nonmatchings/main_021", func_0017BBA0);

INCLUDE_ASM("asm/nonmatchings/main_021", func_0017BBB0);

INCLUDE_ASM("asm/nonmatchings/main_021", func_0017BBC0);

INCLUDE_ASM("asm/nonmatchings/main_021", func_0017BBD0);

INCLUDE_ASM("asm/nonmatchings/main_021", func_0017BBE0);

INCLUDE_ASM("asm/nonmatchings/main_021", func_0017BBF0);

INCLUDE_ASM("asm/nonmatchings/main_021", func_0017BC00);

INCLUDE_ASM("asm/nonmatchings/main_021", func_0017BC10);

INCLUDE_ASM("asm/nonmatchings/main_021", func_0017BC20);

INCLUDE_ASM("asm/nonmatchings/main_021", func_0017BC30);

INCLUDE_ASM("asm/nonmatchings/main_021", func_0017BC40);

INCLUDE_ASM("asm/nonmatchings/main_021", func_0017BC50);

INCLUDE_ASM("asm/nonmatchings/main_021", func_0017BC60);

INCLUDE_ASM("asm/nonmatchings/main_021", func_0017BC70);

INCLUDE_ASM("asm/nonmatchings/main_021", func_0017BC80);

INCLUDE_ASM("asm/nonmatchings/main_021", func_0017BC90);

INCLUDE_ASM("asm/nonmatchings/main_021", func_0017BCA0);

INCLUDE_ASM("asm/nonmatchings/main_021", func_0017BCB0);

INCLUDE_ASM("asm/nonmatchings/main_021", func_0017BCC0);

INCLUDE_ASM("asm/nonmatchings/main_021", func_0017BCD0);

INCLUDE_ASM("asm/nonmatchings/main_021", func_0017BCE0);

INCLUDE_ASM("asm/nonmatchings/main_021", func_0017BCF0);

INCLUDE_ASM("asm/nonmatchings/main_021", func_0017BD00);

INCLUDE_ASM("asm/nonmatchings/main_021", func_0017BD10);

INCLUDE_ASM("asm/nonmatchings/main_021", func_0017BD20);

INCLUDE_ASM("asm/nonmatchings/main_021", func_0017BD30);

INCLUDE_ASM("asm/nonmatchings/main_021", func_0017BD40);

INCLUDE_ASM("asm/nonmatchings/main_021", func_0017BD50);

INCLUDE_ASM("asm/nonmatchings/main_021", func_0017BD60);

void func_0017BD70(void) {
    s32 temp_v0;
    s32 temp_v0_2;

    temp_v0 = func_001843E0();
    *(volatile s32 *)0x1000F000 = 4;
    __asm__ volatile("sync");
    if (temp_v0 != 0) {
        func_00184428();
    }
    do {

    } while (!(*(volatile s32 *)0x1000F000 & 4));
    temp_v0_2 = func_001843E0();
    *(volatile s32 *)0x1000F000 = 4;
    __asm__ volatile("sync");
    if (temp_v0_2 != 0) {
        func_00184428();
    }
}

s64 func_0017BE00(void) {
    volatile s32 done;
    volatile s64 val;
    s32 eie;

    done = 0;
    func_0017BC50((void *)&done, (s64 *)&val);
    eie = func_001843E0();
    *(volatile s32 *)0x1000F000 = 4;
    __asm__ volatile("sync");
    if (eie) {
        func_00184428();
    }
    while (!(*(volatile s32 *)0x1000F000 & 4) && done == 0) {
    }
    eie = func_001843E0();
    *(volatile s32 *)0x1000F000 = 4;
    __asm__ volatile("sync");
    if (eie) {
        func_00184428();
    }
    return val;
}

INCLUDE_ASM("asm/nonmatchings/main_021", func_0017BEA8);

INCLUDE_ASM("asm/nonmatchings/main_021", func_0017BF28);

s32 func_0017BFA0(void) {
    *(s32 *)func_001966F8() = 5;
    return -1;
}

s32 func_0017BFC8(void) {
    return -1;
}

#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_031", func_0018F648);

INCLUDE_ASM("asm/nonmatchings/main_031", func_0018F6A8);

void func_0018F768(s32 arg0) {
    func_00199B50(&D_002BCA98, arg0);
}

void func_0018F778(s32 arg0, void *arg1, s32 arg2) {
    s32 sp0[64];
    func_0019B648(sp0, arg1, arg2);
    func_0018F7B0(arg0, sp0);
}

void func_0018F7B0(s32 arg0, void *arg1) {
    s32 sp0[4];
    s32 temp_v1;

    temp_v1 = (*(s32 *)((u8 *)arg0 + 0x858));
    if ((temp_v1 != 0) && (arg0 != 0) && ((*(s32 *)((u8 *)arg0 + 0xC)) != 0)) {
        sp0[0] = 0;
        sp0[1] = arg1;
        func_0018EF48(temp_v1, sp0);
        return;
    }
    func_0018F768((s32) arg1);
}

INCLUDE_ASM("asm/nonmatchings/main_031", func_0018F808);

s32 func_0018F8F8(void *arg0, s32 arg1, s32 arg2) {
    (*(s32 *)((u8 *)arg0 + 4)) = arg1;
    (*(s32 *)((u8 *)arg0 + 0xC)) = (s32) (arg1 >> 4);
    (*(s32 *)((u8 *)arg0 + 8)) = arg2;
    (*(s32 *)((u8 *)arg0 + 0x10)) = (s32) (arg2 >> 4);
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_031", func_0018F918);

INCLUDE_ASM("asm/nonmatchings/main_031", func_0018FA40);

INCLUDE_ASM("asm/nonmatchings/main_031", func_0018FCE8);

INCLUDE_ASM("asm/nonmatchings/main_031", func_0018FDC8);

INCLUDE_ASM("asm/nonmatchings/main_031", func_0018FEA0);

INCLUDE_ASM("asm/nonmatchings/main_031", func_0018FFD0);

void func_00190060(s32 arg0) {
    func_0018F7B0(arg0, D_002BCB08);
}

void func_00190070(s32 arg0) {
    func_0018F7B0(arg0, D_002BCB38);
}

void func_00190080(s32 arg0) {
    func_0018F7B0(arg0, D_002BCB50);
}

void func_00190090(s32 arg0) {
    func_0018F7B0(arg0, D_002BCB88);
}

void func_001900A0(void *arg0) {
    func_00190190(*(s32 *)((u8 *)arg0 + 0x40) + 0x4C);
}

void func_001900B0(void *arg0) {
    func_00190278(*(s32 *)((u8 *)arg0 + 0x40) + 0x4C);
}

void func_001900C0(s32 arg0) {
    func_001843E0();
    *(volatile s32 *)0x1000F590 = *(volatile s32 *)0x1000F520 | 0x10000;
    *(volatile s32 *)0x1000B000 = arg0;
    *(volatile s32 *)0x1000F590 = *(volatile s32 *)0x1000F520 & 0xFFFEFFFF;
    func_00184428();
}

void func_00190128(s32 arg0) {
    func_001843E0();
    *(volatile s32 *)0x1000F590 = *(volatile s32 *)0x1000F520 | 0x10000;
    *(volatile s32 *)0x1000B400 = arg0;
    *(volatile s32 *)0x1000F590 = *(volatile s32 *)0x1000F520 & 0xFFFEFFFF;
    func_00184428();
}

INCLUDE_ASM("asm/nonmatchings/main_031", func_00190190);

INCLUDE_ASM("asm/nonmatchings/main_031", func_00190278);

INCLUDE_ASM("asm/nonmatchings/main_031", func_001903C8);

void func_00190430(s32 arg0) {
    func_001843E0();
    *(volatile s32 *)0x1000F590 = *(volatile s32 *)0x1000F520 | 0x10000;
    *(volatile s32 *)0x1000B400 = arg0;
    *(volatile s32 *)0x1000F590 = *(volatile s32 *)0x1000F520 & 0xFFFEFFFF;
    func_00184428();
}

INCLUDE_ASM("asm/nonmatchings/main_031", func_00190498);

INCLUDE_ASM("asm/nonmatchings/main_031", func_001906D0);

s32 func_00190778(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_v0;

    if ((arg3 == 0) || ((*(s32 *)(&D_00315500)) = arg0, (*(s32 *)((u8 *)(&D_00315500) + 4)) = arg1, (*(s32 *)((u8 *)(&D_00315500) + 8)) = arg2, (*(s32 *)((u8 *)(&D_00315500) + 0xC)) = 0, temp_v0 = func_0017BCA0(&D_00315500, 1), (temp_v0 == 0))) {
        return -1;
    }
    if (arg3 == 1) {
        do {

        } while (func_0017BC80(temp_v0) >= 0);
    }
    return 0;
}

s32 func_00190800(s32 arg0) {
    s32 temp_v0;

    temp_v0 = D_0028DC90;
    D_0028DC90 = arg0;
    return temp_v0;
}

INCLUDE_ASM("asm/nonmatchings/main_031", func_00190810);

INCLUDE_ASM("asm/nonmatchings/main_031", func_00190A00);

INCLUDE_ASM("asm/nonmatchings/main_031", func_00190A28);

INCLUDE_ASM("asm/nonmatchings/main_031", func_00190A90);

INCLUDE_ASM("asm/nonmatchings/main_031", func_00190AE8);

INCLUDE_ASM("asm/nonmatchings/main_031", func_00190B88);

INCLUDE_ASM("asm/nonmatchings/main_031", func_00190D20);

INCLUDE_ASM("asm/nonmatchings/main_031", func_00190DC0);

INCLUDE_ASM("asm/nonmatchings/main_031", func_00190E58);

INCLUDE_ASM("asm/nonmatchings/main_031", func_00190ED8);

INCLUDE_ASM("asm/nonmatchings/main_031", func_00190F48);

INCLUDE_ASM("asm/nonmatchings/main_031", func_00190F88);

INCLUDE_ASM("asm/nonmatchings/main_031", func_00190FF0);

INCLUDE_ASM("asm/nonmatchings/main_031", func_001912F0);

INCLUDE_ASM("asm/nonmatchings/main_031", func_00191460);

INCLUDE_ASM("asm/nonmatchings/main_031", func_001914F8);

INCLUDE_ASM("asm/nonmatchings/main_031", func_00191598);

INCLUDE_ASM("asm/nonmatchings/main_031", func_00191608);

INCLUDE_ASM("asm/nonmatchings/main_031", func_00191778);

INCLUDE_ASM("asm/nonmatchings/main_031", func_00191A58);

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

void func_0018FFD0(void *arg0, s32 arg1) {
    func_0018BA48(arg0, 3);
    if (func_0018BA48(arg0, 1) != 0) {
        func_0018BA48(arg0, 8);
        func_0018BA48(arg0, 8);
        (*(s32 *)((u8 *)arg0 + 0x144)) = func_0018BA48(arg0, 8);
    }
    (*(s32 *)((u8 *)arg0 + 0x148)) = func_0018BA48(arg0, 0xE);
    func_0018BA48(arg0, 1);
    (*(s32 *)((u8 *)arg0 + 0x14C)) = func_0018BA48(arg0, 0xE);
}

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

void func_00190190(s32 arg0) {
    func_00190128(1);
    (*(s32 *)arg0) = (s32) *(volatile s32 *)0x1000B410;
    (*(s32 *)((u8 *)arg0 + 4)) = (s32) *(volatile s32 *)0x1000B430;
    (*(s32 *)((u8 *)arg0 + 8)) = (s32) *(volatile s32 *)0x1000B420;
    (*(s32 *)((u8 *)arg0 + 0xC)) = (s32) *(volatile s32 *)0x1000B400;
    do {

    } while (*(volatile s32 *)0x10002010 & 0xF0);
    func_001900C0(0);
    (*(s32 *)((u8 *)arg0 + 0x10)) = (s32) *(volatile s32 *)0x1000B010;
    (*(s32 *)((u8 *)arg0 + 0x14)) = (s32) *(volatile s32 *)0x1000B020;
    (*(s32 *)((u8 *)arg0 + 0x18)) = (s32) *(volatile s32 *)0x1000B000;
    (*(s32 *)((u8 *)arg0 + 0x1C)) = (s32) *(volatile s32 *)0x10002020;
    (*(s32 *)((u8 *)arg0 + 0x20)) = (s32) *(volatile s32 *)0x10002010;
}

void func_00190278(s32 arg0) {
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_s1;
    s32 temp_s2;
    s32 temp_s3;
    s32 temp_v0_2;
    u32 temp_v0;

    temp_v0 = (*(u32 *)((u8 *)arg0 + 0x1C));
    temp_s3 = temp_v0 & 0x7F;
    temp_a1 = (*(s32 *)arg0);
    temp_v0_2 = ((temp_v0 >> 0x10) & 3) + ((temp_v0 >> 8) & 0xF);
    temp_a2 = (*(s32 *)((u8 *)arg0 + 0x10));
    temp_s2 = (*(s32 *)((u8 *)arg0 + 8)) + temp_v0_2;
    temp_s1 = temp_a1 - (temp_v0_2 * 0x10);
    if ((temp_a2 != 0) && ((*(s32 *)((u8 *)arg0 + 0x14)) != 0)) {
        *(volatile s32 *)0x1000B010 = temp_a2;
        *(volatile s32 *)0x1000B020 = (*(s32 *)((u8 *)arg0 + 0x14));
        func_001900C0((*(s32 *)((u8 *)arg0 + 0x18)) | 0x100);
    }
    do {

    } while (*(volatile s32 *)0x10002010 < 0);
    *(volatile s32 *)0x10002000 = temp_s3;
    do {

    } while (*(volatile s32 *)0x10002010 < 0);
    if (temp_s1 != 0) {
        if (temp_s2 != 0) {
            *(volatile s32 *)0x1000B410 = temp_s1;
            *(volatile s32 *)0x1000B430 = (*(s32 *)((u8 *)arg0 + 4));
            *(volatile s32 *)0x1000B420 = temp_s2;
            func_00190128((*(s32 *)((u8 *)arg0 + 0xC)) | 0x100);
        }
    }
}

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

void func_00190A28(u16 arg0) {
    s32 sp0[8];
    s32 temp_v0;

    sp0[1] = 1;
    sp0[2] = 0;
    sp0[5] = 0;
    temp_v0 = func_0017B8E0(sp0);
    func_0017B660(arg0, &func_00190A00, temp_v0);
    func_0017B920(temp_v0);
    func_0017B8F0(temp_v0);
}

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

s32 func_00191460(void) {
    s32 temp_s0;

    if (func_001912F0(2) == 0) {
        return 0;
    }
    if (func_0017EA80(&D_0028EE90, 0xE, 0, 0, 0, &D_0028DD40, 4, 0, 0) < 0) {
        func_0017B900(D_0028DCE8);
        return 0;
    }
    temp_s0 = *(s32 *)((s32) &D_0028DD40 | 0x20000000);
    func_0017B900(D_0028DCE8);
    return temp_s0;
}

INCLUDE_ASM("asm/nonmatchings/main_031", func_001914F8);

INCLUDE_ASM("asm/nonmatchings/main_031", func_00191598);

INCLUDE_ASM("asm/nonmatchings/main_031", func_00191608);

INCLUDE_ASM("asm/nonmatchings/main_031", func_00191778);

INCLUDE_ASM("asm/nonmatchings/main_031", func_00191A58);

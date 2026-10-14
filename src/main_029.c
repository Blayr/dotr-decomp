#include "common.h"

void func_0018A378(s32 arg0) {
    *(s32 *)0x10002010 = (*(s32 *)0x10002010 & 0xFF7FFFFF) | (arg0 << 0x17);
}

INCLUDE_ASM("asm/nonmatchings/main_029", func_0018A3A0);

s32 func_0018A590(s32 arg0) {
    return func_0018B6D8(arg0, 3);
}

INCLUDE_ASM("asm/nonmatchings/main_029", func_0018A5B0);

INCLUDE_ASM("asm/nonmatchings/main_029", func_0018A738);

INCLUDE_ASM("asm/nonmatchings/main_029", func_0018A848);

INCLUDE_ASM("asm/nonmatchings/main_029", func_0018A950);

INCLUDE_ASM("asm/nonmatchings/main_029", func_0018AA80);

INCLUDE_ASM("asm/nonmatchings/main_029", func_0018AC70);

INCLUDE_ASM("asm/nonmatchings/main_029", func_0018AD30);

INCLUDE_ASM("asm/nonmatchings/main_029", func_0018B1D8);

INCLUDE_ASM("asm/nonmatchings/main_029", func_0018B260);

INCLUDE_ASM("asm/nonmatchings/main_029", func_0018B400);

s32 func_0018B550(void *arg0, s32 arg1) {
    s32 temp_v0;

    *(volatile s32 *)0x10002000 = arg1;
    temp_v0 = (&D_0028DA50)[((u32) arg1 >> 0x1C)];
    (*(s32 *)((u8 *)arg0 + 0x818)) = temp_v0;
    return temp_v0;
}

INCLUDE_ASM("asm/nonmatchings/main_029", func_0018B580);

INCLUDE_ASM("asm/nonmatchings/main_029", func_0018B628);

INCLUDE_ASM("asm/nonmatchings/main_029", func_0018B6D8);

INCLUDE_ASM("asm/nonmatchings/main_029", func_0018B850);

INCLUDE_ASM("asm/nonmatchings/main_029", func_0018B958);

INCLUDE_ASM("asm/nonmatchings/main_029", func_0018BA48);

INCLUDE_ASM("asm/nonmatchings/main_029", func_0018BB98);

s32 func_0018BC18(void *arg0, s32 arg1) {
    (*(s32 *)((u8 *)arg0 + 0x1B4)) = func_0018BA48(arg0, 5);
    if (func_0018BA48(arg0, 1) != 0) {
        func_0018BA48(arg0, 1);
        func_0018B958(arg0, 7);
        func_0018C170(arg0);
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_029", func_0018BC80);

void func_0018BD90(void *arg0, s32 arg1) {
    s32 temp_s1;

    temp_s1 = func_0018BA48(arg0, 0xA);
    (*(s32 *)((u8 *)arg0 + 0x150)) = func_0018BA48(arg0, 3);
    func_0018BA48(arg0, 0x10);
    if ((u32) ((*(s32 *)((u8 *)arg0 + 0x150)) - 2) < 2U) {
        (*(s32 *)((u8 *)arg0 + 0x154)) = func_0018BA48(arg0, 1);
        (*(s32 *)((u8 *)arg0 + 0x158)) = func_0018BA48(arg0, 3);
    }
    if ((*(s32 *)((u8 *)arg0 + 0x150)) == 3) {
        (*(s32 *)((u8 *)arg0 + 0x15C)) = func_0018BA48(arg0, 1);
        (*(s32 *)((u8 *)arg0 + 0x160)) = func_0018BA48(arg0, 3);
    }
    func_0018C170(arg0);
    func_0018BE58(arg0);
    func_0018C1B8(arg0, temp_s1);
}

INCLUDE_ASM("asm/nonmatchings/main_029", func_0018BE58);

void func_0018BF80(void *arg0) {
    s32 temp_v0;

    (*(s32 *)((u8 *)arg0 + 0x164)) = func_0018BA48(arg0, 4);
    (*(s32 *)((u8 *)arg0 + 0x168)) = func_0018BA48(arg0, 4);
    (*(s32 *)((u8 *)arg0 + 0x16C)) = func_0018BA48(arg0, 4);
    (*(s32 *)((u8 *)arg0 + 0x170)) = func_0018BA48(arg0, 4);
    *(s32 *)0x10002010 = (*(s32 *)0x10002010 & 0xFFFCFFFF) | (func_0018BA48(arg0, 2) << 0x10);
    temp_v0 = func_0018BA48(arg0, 2);
    (*(s32 *)((u8 *)arg0 + 0x174)) = temp_v0;
    if ((*(s32 *)((u8 *)arg0 + 0xD4)) == 0) {
        (*(s32 *)((u8 *)arg0 + 0xD4)) = temp_v0;
    }
    (*(s32 *)((u8 *)arg0 + 0x178)) = func_0018BA48(arg0, 1);
    (*(s32 *)((u8 *)arg0 + 0x17C)) = func_0018BA48(arg0, 1);
    (*(s32 *)((u8 *)arg0 + 0x180)) = func_0018BA48(arg0, 1);
    *(volatile s32 *)0x10002010 = (s32) ((*(volatile s32 *)0x10002010 & 0xFFBFFFFF) | (func_0018BA48(arg0, 1) << 0x16));
    *(volatile s32 *)0x10002010 = (s32) ((*(volatile s32 *)0x10002010 & 0xFFDFFFFF) | (func_0018BA48(arg0, 1) << 0x15));
    *(volatile s32 *)0x10002010 = (s32) ((*(volatile s32 *)0x10002010 & 0xFFEFFFFF) | (func_0018BA48(arg0, 1) << 0x14));
    (*(s32 *)((u8 *)arg0 + 0x184)) = func_0018BA48(arg0, 1);
    func_0018BA48(arg0, 1);
    (*(s32 *)((u8 *)arg0 + 0x188)) = func_0018BA48(arg0, 1);
    if (func_0018BA48(arg0, 1) != 0) {
        func_0018BA48(arg0, 1);
        func_0018BA48(arg0, 3);
        func_0018BA48(arg0, 1);
        func_0018BA48(arg0, 7);
        func_0018BA48(arg0, 8);
    }
}

INCLUDE_ASM("asm/nonmatchings/main_029", func_0018C170);

s32 func_0018C1B8(void *arg0, s32 arg1) {
    s32 temp_a0;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v1;
    s32 var_a0;
    s32 var_a3;

    var_a3 = 0;
    var_a0 = 0;
    if (((*(s32 *)((u8 *)arg0 + 0x150)) != 3) && (arg1 != 0)) {
        if (arg1 < 0) {
            var_a3 = (*(s32 *)((u8 *)arg0 + 0x854)) == 0;
        }
        (*(s32 *)((u8 *)arg0 + 0x854)) = 0;
        var_a0 = arg1;
    }
    temp_v1 = (*(s32 *)((u8 *)arg0 + 0x84C)) + arg1;
    (*(s32 *)((u8 *)arg0 + 0x1AC)) = temp_v1;
    if ((var_a3 != 0) && (var_a0 >= arg1)) {
        (*(s32 *)((u8 *)arg0 + 0x1AC)) = (s32) (temp_v1 + 0x400);
    }
    temp_v0_2 = (*(s32 *)((u8 *)arg0 + 0x850));
    temp_a0 = (*(s32 *)((u8 *)arg0 + 0x1AC));
    temp_v0 = (temp_v0_2 < temp_a0) ? temp_a0 : temp_v0_2;
    (*(s32 *)((u8 *)arg0 + 0x850)) = temp_v0;
    return temp_v0;
}

void func_0018C230(void *arg0, s32 arg1) {
    (*(s32 *)((u8 *)arg0 + 0xE8)) = 0;
    (*(s32 *)((u8 *)arg0 + 0x854)) = 1;
    (*(s32 *)((u8 *)arg0 + 0x84C)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x850)) + 1);
    func_0018BA48(arg0, 1);
    func_0018BA48(arg0, 5);
    func_0018BA48(arg0, 6);
    func_0018BA48(arg0, 1);
    func_0018BA48(arg0, 6);
    func_0018BA48(arg0, 6);
    (*(s32 *)((u8 *)arg0 + 0x1A4)) = func_0018BA48(arg0, 1);
    (*(s32 *)((u8 *)arg0 + 0x1A8)) = func_0018BA48(arg0, 1);
    func_0018BE58(arg0);
}

void func_0018C2D0(void *arg0, s32 arg1) {
    s32 temp_v0;
    s32 temp_v0_2;

    temp_v0 = func_0018BA48(arg0, 1);
    (*(s32 *)((u8 *)arg0 + 0x840)) = temp_v0;
    if (temp_v0 != 0) {
        func_0018B580(arg0);
        func_0018B550(arg0, 0x50000000);
        func_0018B580(arg0);
    }
    temp_v0_2 = func_0018BA48(arg0, 1);
    (*(s32 *)((u8 *)arg0 + 0x844)) = temp_v0_2;
    if (temp_v0_2 != 0) {
        func_0018B580(arg0);
        func_0018B550(arg0, 0x58000000);
        func_0018B580(arg0);
    }
    if (func_0018BA48(arg0, 1) != 0) {
        func_0018F7B0((s32) arg0, &D_002BC8A8);
    }
    if (func_0018BA48(arg0, 1) != 0) {
        func_0018F7B0((s32) arg0, &D_002BC8D0);
    }
}

INCLUDE_ASM("asm/nonmatchings/main_029", func_0018C398);

void func_0018C490(s32 arg0, s32 arg1) {
    func_0018BA48(arg0, 1);
    func_0018BA48(arg0, 8);
    func_0018BA48(arg0, 1);
    func_0018BA48(arg0, 7);
    func_0018BA48(arg0, 1);
    func_0018BA48(arg0, 0x14);
    func_0018BA48(arg0, 1);
    func_0018BA48(arg0, 0x16);
    func_0018BA48(arg0, 1);
    func_0018BA48(arg0, 0x16);
}

s32 func_0018C520(void *arg0) {
    s32 temp_v0;
    void *var_s1;

    if (((*(s32 *)((u8 *)arg0 + 0x174)) == 3) && ((*(s32 *)((u8 *)arg0 + 0x120)) != 0)) {
        func_0018F7B0((s32) arg0, &D_002BC900);
        (*(s32 *)((u8 *)arg0 + 0x120)) = 0;
    }
    switch ((*(s32 *)((u8 *)arg0 + 0x174))) {        /* irregular */
    case 3:
        var_s1 = (*(void **)((u8 *)arg0 + 0x1C0));
        break;
    case 1:
        var_s1 = (*(void **)((u8 *)arg0 + 0x1D0));
        break;
    case 2:
        var_s1 = (*(void **)((u8 *)arg0 + 0x1E0));
        break;
    default:
        var_s1 = (*(void **)((u8 *)arg0 + 0x1C0));
        func_0018F7B0((s32) arg0, &D_002BC920);
        break;
    }
    temp_v0 = func_0018A848(arg0);
    if (temp_v0 != 0) {
        (*(s32 *)((u8 *)var_s1 + 0x28)) = 1;
    }
    return temp_v0;
}

INCLUDE_ASM("asm/nonmatchings/main_029", func_0018C5F0);

INCLUDE_ASM("asm/nonmatchings/main_029", func_0018C680);

INCLUDE_ASM("asm/nonmatchings/main_029", func_0018C938);

INCLUDE_ASM("asm/nonmatchings/main_029", func_0018C9D8);

void func_0018CC48(void *arg0) {
    if ((*(s32 *)((u8 *)arg0 + 8)) != 2) {
        (*(s32 *)((u8 *)arg0 + 8)) = 2;
        (*(s32 *)((u8 *)arg0 + 0xAC)) = (s32) (*(s32 *)((u8 *)arg0 + 0x118));
    }
    (*(s32 *)((u8 *)arg0 + 0x820)) = 1;
}

INCLUDE_ASM("asm/nonmatchings/main_029", func_0018CC70);

INCLUDE_ASM("asm/nonmatchings/main_029", func_0018CE00);

INCLUDE_ASM("asm/nonmatchings/main_029", func_0018CF10);

INCLUDE_ASM("asm/nonmatchings/main_029", func_0018D0C8);

void func_0018D220(s32 arg0, s32 arg1) {
    func_001843E0();
    *(volatile s32 *)0x1000B010 = (arg0 & 0x0FFFFFFF) | 0x80000000;
    *(volatile s32 *)0x1000B020 = arg1 >> 4;
    *(volatile s32 *)0x1000B000 = 0x100;
    func_00184428();
}

void func_0018D290(void *arg0, s32 arg1, s32 arg2) {
    s32 sp0[8];
    do {

    } while (*(volatile s32 *)0x10002010 < 0);
    func_001843E0();
    *(volatile s32 *)0x1000B010 = arg1 & 0x0FFFFFFF;
    *(volatile s32 *)0x1000B020 = arg2 << 6;
    *(volatile u32 *)0x1000B000 = 0x100;
    func_00184428();
    func_0018B550(arg0, arg2 | 0x70000000);
    sp0[0] = 4;
    func_0018EF48((*(s32 *)((u8 *)arg0 + 0x858)), sp0);
    do {

    } while (((u32) *(volatile s32 *)0x1000B000 >> 8) & 1);
    do {

    } while (*(volatile s32 *)0x10002010 < 0);
}

INCLUDE_ASM("asm/nonmatchings/main_029", func_0018D3A8);

INCLUDE_ASM("asm/nonmatchings/main_029", func_0018D520);

s32 func_0018D6D0(s32 arg0, void *arg1) {
    u32 temp_v0;

    *(volatile s32 *)0x1000E010 = 0x10;
    temp_v0 = (*(u32 *)arg1);
    if (temp_v0 == 0) {
        return 1;
    }
    if (temp_v0 > 0xFFFFU) {
        func_001843E0();
        *(volatile s32 *)0x1000B410 = (*(s32 *)((u8 *)arg1 + 4));
        *(volatile u32 *)0x1000B420 = 0xFFFF;
        *(volatile s32 *)0x1000B400 = 0x101;
        func_00184428();
        (*(u32 *)arg1) = (u32) ((*(u32 *)arg1) - 0xFFFF);
        (*(s32 *)((u8 *)arg1 + 4)) = (s32) (((*(s32 *)((u8 *)arg1 + 4)) + 0xFFFF0) & 0x0FFFFFFF);
    } else {
        func_001843E0();
        *(volatile s32 *)0x1000B410 = (s32) (*(s32 *)((u8 *)arg1 + 4));
        *(volatile s32 *)0x1000B420 = (u32) (*(u32 *)arg1);
        *(volatile s32 *)0x1000B400 = 0x101;
        func_00184428();
        (*(u32 *)arg1) = 0U;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_029", func_0018D7D8);

void func_0018DA50(u64 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    (*(s32 *)((u8 *)arg0 + 8)) = arg1;
    (*(u64 *)arg0) = 0;
    (*(s32 *)((u8 *)arg0 + 0xC)) = arg1;
    (*(s32 *)((u8 *)arg0 + 0x10)) = 0;
    (*(s64 *)((u8 *)arg0 + 0x18)) = 0;
    (*(s32 *)((u8 *)arg0 + 0x20)) = arg2;
    (*(s32 *)((u8 *)arg0 + 0x24)) = (s32) (arg2 + arg3);
    (*(s32 *)((u8 *)arg0 + 0x28)) = arg3;
    func_0018DAA8(arg0, 0);
}

s32 func_0018DA88(u64 *arg0, s32 arg1) {
    return *arg0 >> (64 - arg1);
}

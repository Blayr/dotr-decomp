#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_025", func_001831A0);

s32 func_00183240(s32 arg0) {
    s32 var_v0;

    var_v0 = -0x10000;
    if (func_00182B38() < 0) {
        return var_v0;
    }
    if (func_00182C38() != 0) {
        return -0x10004;
    }
    D_00313E00 = arg0;
    if (func_0017EA80(&D_00314000, 0xA, 0, &D_00313E00, 4, &D_00313E00, 4, 0, 0) < 0) {
        var_v0 = -0x10001;
        /* Duplicate return node #7. Try simplifying control flow for better match */
        return var_v0;
    }
    return D_00313E00;
}

s32 func_001832D0(s32 arg0, s32 arg1, s32 arg2) {
    s32 buf[4];
    return ((s32 (*)(s32, s32, s32, s32 *))func_00182D00)(arg0, arg1, arg2, buf);
}

s32 func_001832F0(s32 arg0) {
    return func_00182D00(arg0);
}

INCLUDE_ASM("asm/nonmatchings/main_025", func_00183310);

void func_00183538(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp0[4];
    func_00183310(arg0, arg1, arg2, (s32) sp0, 0);
}

s32 func_00183558(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return func_00183310(arg0, arg1, arg2, arg3, 0);
}

INCLUDE_ASM("asm/nonmatchings/main_025", func_00183578);

s32 func_00183680(s32 arg0, s32 arg1, s32 arg2) {
    return func_00183578(arg0, arg1, arg2, 1);
}

s32 func_001836A0(s32 arg0, s32 arg1) {
    return func_00183578(arg0, (s32) &D_002BC1E8, arg1, 1);
}

INCLUDE_ASM("asm/nonmatchings/main_025", func_001836C8);

INCLUDE_ASM("asm/nonmatchings/main_025", func_001837B8);

INCLUDE_ASM("asm/nonmatchings/main_025", func_00183898);

INCLUDE_ASM("asm/nonmatchings/main_025", func_001839D8);

INCLUDE_ASM("asm/nonmatchings/main_025", func_00183A00);

INCLUDE_ASM("asm/nonmatchings/main_025", func_00183A38);

s32 func_00183B48(s32 arg0) {
    D_0028CDF0 = arg0;
    func_0017B590(1, &func_00184080);
    func_0017B590(2, &func_00184080);
    func_0017B590(3, &func_00184080);
    return arg0;
}

u32 func_00183BA8(s32 arg0, s32 arg1) {
    s32 *temp_v1;
    s32 temp_s0;
    u32 temp_a0;

    temp_a0 = arg0 - 1;
    if (temp_a0 >= 0xDU) {
        return 0xFFFFFFFF;
    }
    temp_v1 = (&D_0028CDF8 + arg0);
    temp_s0 = *temp_v1;
    *temp_v1 = arg1;
    if (temp_a0 < 3U) {
        func_0017B590(arg0, &D_001842C0);
    } else {
        func_0017B5A0(arg0, &D_001842C0);
    }
    return temp_s0;
}

INCLUDE_ASM("asm/nonmatchings/main_025", func_00183C30);

s32 func_00183C40(s32 *arg0, s32 *arg1, u32 arg2) {
    s32 *var_a0;
    s32 *var_a1;
    s32 temp_v1;
    u32 temp_a2;
    u32 var_a3;

    var_a0 = arg0;
    var_a1 = arg1;
    temp_a2 = arg2 >> 2;
    var_a3 = 0;
    if (temp_a2 != 0) {
        do {
            temp_v1 = *var_a1;
            var_a3 += 1;
            var_a1 += 1;
            *var_a0 = temp_v1;
            var_a0 += 1;
        } while (var_a3 < temp_a2);
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_025", func_00183C78);

INCLUDE_ASM("asm/nonmatchings/main_025", func_00183C88);

INCLUDE_ASM("asm/nonmatchings/main_025", func_00183C98);

INCLUDE_ASM("asm/nonmatchings/main_025", func_00183D50);

INCLUDE_ASM("asm/nonmatchings/main_025", func_00183D60);

INCLUDE_ASM("asm/nonmatchings/main_025", func_00183D70);

INCLUDE_ASM("asm/nonmatchings/main_025", func_00183D80);

INCLUDE_ASM("asm/nonmatchings/main_025", func_00183DB0);

INCLUDE_ASM("asm/nonmatchings/main_025", func_00183DC0);

INCLUDE_ASM("asm/nonmatchings/main_025", func_00183DD0);

INCLUDE_ASM("asm/nonmatchings/main_025", func_00183DE0);

INCLUDE_ASM("asm/nonmatchings/main_025", func_00183DF0);

INCLUDE_ASM("asm/nonmatchings/main_025", func_00183E00);

s32 func_00183E10(void) {
    if (func_0017BD40() == 0x02000000) {
        return func_00183E50();
    }
    return func_0017BD50();
}

INCLUDE_ASM("asm/nonmatchings/main_025", func_00183E50);

INCLUDE_ASM("asm/nonmatchings/main_025", func_00184080);

INCLUDE_ASM("asm/nonmatchings/main_025", func_001843E0);

s32 func_00184428(void) {
    s32 eie;
    __asm__ volatile("mfc0\t%0, $12" : "=r"(eie));
    eie &= 0x10000;
    __asm__ volatile("ei");
    return eie != 0;
}

INCLUDE_ASM("asm/nonmatchings/main_025", func_00184440);

INCLUDE_ASM("asm/nonmatchings/main_025", func_00184488);

INCLUDE_ASM("asm/nonmatchings/main_025", func_001844C0);

s32 func_001844D0(void) {
    func_00184510((*(s32 *)(&D_0028D108)), (*(s32 *)((u8 *)(&D_0028D108) + 4)));
    return func_001844C0(&func_00184488) - 0x20C;
}

INCLUDE_ASM("asm/nonmatchings/main_025", func_00184510);

s32 *func_00184520(s32 arg0) {
    __asm__ volatile("addiu $3, $0, 0x74\n\tsyscall");
    return D_0028D11C + arg0;
}

void func_00184540(void) {
    func_00184440();
    func_001844D0();
    func_0017C648();
    func_0017C7F8();
    func_00184650();
    func_00183C98();
}

INCLUDE_ASM("asm/nonmatchings/main_025", func_00184580);

INCLUDE_ASM("asm/nonmatchings/main_025", func_00184590);

s32 func_001845A0(s32 *arg0, s32 *arg1, u32 arg2) {
    s32 *var_a0;
    s32 *var_a1;
    s32 temp_v1;
    u32 temp_a2;
    u32 var_a3;

    var_a0 = arg0;
    var_a1 = arg1;
    temp_a2 = arg2 >> 2;
    var_a3 = 0;
    if (temp_a2 != 0) {
        do {
            temp_v1 = *var_a1;
            var_a3 += 1;
            var_a1 += 1;
            *var_a0 = temp_v1;
            var_a0 += 1;
        } while (var_a3 < temp_a2);
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_025", func_001845D8);

s32 func_001845E8(void) {
    u32 sp0;
    u32 sp4;

    func_0017B990(&sp0);
    sp4 = (sp0 & 0xFFFF1FFF) | 0x2000;
    func_0017B980(&sp4);
    func_0017B990(&sp4);
    func_0017B980(&sp0);
    return ((sp4 >> 0xD) & 7) == 0;
}

#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_024", func_0017F288);

INCLUDE_ASM("asm/nonmatchings/main_024", func_0017F2F8);

void func_0017F6B8(void) {
    s32 sp0[8];
    if (D_0028CAA4 == -1) {
        sp0[2] = 1;
        sp0[1] = 1;
        sp0[5] = 0;
        D_0028CAA4 = func_0017B8E0(sp0);
    }
}

s32 func_0017F708(void) {
    func_0017F6B8();
    func_0017B920(D_0028CAA4);
    return 0;
}

void func_0017F738(void) {
    func_0017B900(D_0028CAA4);
}

s32 func_0017F748(s32 arg0, s32 arg1) {
    u8 *b_D_00313C00 = (u8 *)&D_00313C00;
    s32 temp_s0;

    ((s32 (*)(s32))func_0017F708)(0x1B);
    if (D_0028CAA0 == 0) {
        func_0017F808();
    }
    func_001843E0();
    temp_s0 = (*(s32 *)(&D_00313C00));
    (*(s32 *)(b_D_00313C00 + 4)) = arg1;
    (*(s32 *)(&D_00313C00)) = arg0;
    func_00184428();
    func_0017F738();
    return temp_s0;
}

void func_0017F7D8(s32 arg0, hcall_t *arg1) {
    if (arg1->fn != NULL) {
        arg1->fn(arg1->arg);
    }
    __asm__ volatile("sync");
    __asm__ volatile("ei");
}

INCLUDE_ASM("asm/nonmatchings/main_024", func_0017F808);

s32 func_0017F9D0(void) {
    s32 *a_D_0028C24C = &D_0028C24C;
    s32 *a_D_00313BA8 = &D_00313BA8;
    s32 var_s2;

    var_s2 = 0;
    if ((func_001986F8(a_D_00313BA8, a_D_0028C24C, 4) != 0) && (func_001986F8(a_D_00313BA8, D_0028CAB0, 4) != 0)) {
        var_s2 = func_001986F8(a_D_0028C24C, D_0028CAB0, 4) != 0;
    }
    return var_s2;
}

s32 func_0017FA60(void) {
    D_0028CAA0 = 0;
    func_00198948(&D_00313BA8, 0, 4U);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_024", func_0017FA98);

INCLUDE_ASM("asm/nonmatchings/main_024", func_0017FD20);

INCLUDE_ASM("asm/nonmatchings/main_024", func_0017FEA0);

INCLUDE_ASM("asm/nonmatchings/main_024", func_001800D8);

INCLUDE_ASM("asm/nonmatchings/main_024", func_00180348);

INCLUDE_ASM("asm/nonmatchings/main_024", func_00180608);

INCLUDE_ASM("asm/nonmatchings/main_024", func_00180958);

INCLUDE_ASM("asm/nonmatchings/main_024", func_00180B38);

s32 func_00180CE0(s32 arg0) {
    return func_00180B38(arg0, 6);
}

INCLUDE_ASM("asm/nonmatchings/main_024", func_00180D00);

s32 func_00180EB0(s32 arg0) {
    return func_00180B38(arg0, 8);
}

INCLUDE_ASM("asm/nonmatchings/main_024", func_00180ED0);

extern s32 D_00313500;
extern s32 D_00313B80;

typedef struct FioReq_00181140 {
    s32 sema;
    s32 *result;
    s32 size;
    s32 arg;
} FioReq_00181140;

extern FioReq_00181140 D_003128C0;

s32 func_00181140(s32 arg0) {
    s32 sp[8];
    s32 result;
    FioReq_00181140 *p;
    s32 sema;
    s32 r;

    ((s32 (*)(s32))func_0017F708)(0xF);
    p = &D_003128C0;
    if (D_0028CAA0 == 0) {
        func_0017F808();
    }
    p->arg = arg0;
    sp[1] = 1;
    sp[2] = 0;
    sp[5] = 0;
    sema = func_0017B8E0(sp);
    D_003128C0.sema = sema;
    p->result = &result;
    p->size = 4;
    if (func_0017EA80(&D_00313B80, 0xF, 0, (s32 *)p, 0x10, &D_00313500, 4, 0, 0) < 0) {
        func_0017B8F0(sema);
        func_0017F738();
        return -1;
    }
    r = *(s32 *)((u32)&D_00313500 | 0x20000000);
    func_0017F738();
    if (r == 0) {
        func_0017B8F0(sema);
        return -1;
    }
    func_0017B920(sema);
    func_0017B8F0(sema);
    return result;
}

s32 func_00181260(s32 arg0) {
    return func_00180B38(arg0, 0x10);
}

INCLUDE_ASM("asm/nonmatchings/main_024", func_00181280);

INCLUDE_ASM("asm/nonmatchings/main_024", func_00181348);

INCLUDE_ASM("asm/nonmatchings/main_024", func_001814B0);

INCLUDE_ASM("asm/nonmatchings/main_024", func_00181608);

INCLUDE_ASM("asm/nonmatchings/main_024", func_001817A8);

INCLUDE_ASM("asm/nonmatchings/main_024", func_001819E8);

s32 func_00181BD8(s32 arg0) {
    return func_00180B38(arg0, 0x12);
}

INCLUDE_ASM("asm/nonmatchings/main_024", func_00181BF8);

INCLUDE_ASM("asm/nonmatchings/main_024", func_00181D90);

s32 func_00182000(s32 arg0) {
    return func_00180B38(arg0, 0x15);
}

INCLUDE_ASM("asm/nonmatchings/main_024", func_00182020);

INCLUDE_ASM("asm/nonmatchings/main_024", func_00182258);

INCLUDE_ASM("asm/nonmatchings/main_024", func_00182490);

INCLUDE_ASM("asm/nonmatchings/main_024", func_00182670);

INCLUDE_ASM("asm/nonmatchings/main_024", func_00182838);

s32 func_001828C0(s32 arg0) {
    if (D_0028CAB8 < 0) {
        return 0;
    }
    D_00313CC0 = arg0;
    if (func_0017EA80(&D_00313C40, 1, 0, &D_00313CC0, 4, &D_00313C80, 4, 0, 0) < 0) {
        return 0;
    }
    return D_00313C80;
}

INCLUDE_ASM("asm/nonmatchings/main_024", func_00182930);

s32 func_001829B0(s32 arg0) {
    if (D_0028CAB8 < 0) {
        return 0;
    }
    D_00313CC0 = arg0;
    if (func_0017EA80(&D_00313C40, 2, 0, &D_00313CC0, 4, &D_00313C80, 4, 0, 0) < 0) {
        return -1;
    }
    return D_00313C80;
}

s32 func_00182A28(s32 arg0) {
    return func_001829B0(arg0);
}

INCLUDE_ASM("asm/nonmatchings/main_024", func_00182A48);

extern s32 D_0028CAC0;
extern s32 D_00314028;

typedef struct IopCd_00182B38 {
    s32 unk0[9];
    s32 serve;
} IopCd_00182B38;

typedef struct IopVer_00182B38 {
    u8 b[4];
} IopVer_00182B38;

s32 func_00182B38(void) {
    s32 i;

    if (D_0028CAC0 < 0) {
        while (1) {
            if (func_0017E8B0(&D_00314000, 0x80000006, 0) < 0) {
                return -1;
            }
            if ((*(IopCd_00182B38 *)&D_00314000).serve != 0) {
                D_0028CAC0 = 0;
                if (func_0017EA80(&D_00314000, 0xFF, 0, 0, 0, &D_00313E00, 4, 0, 0) < 0) {
                    return 0xFFFEFFFF;
                }
                *(IopVer_00182B38 *)&D_00314028 = *(IopVer_00182B38 *)&D_00313E00;
                return 0;
            }
            for (i = 0x100000; i != -1; i--) {
            }
        }
    }
    return 0;
}

s32 func_00182C38(void) {
    s32 *a = &D_0028C24C;
    s32 *b = &D_00314028;
    s32 var_s2;
    var_s2 = 0;
    if ((func_001986F8(b, a, 4) != 0) && (func_001986F8(b, D_0028CAC4, 4) != 0)) {
        var_s2 = func_001986F8(a, D_0028CAC4, 4) != 0;
    }
    return var_s2;
}

s32 func_00182CC8(void) {
    D_0028CAC0 = -1;
    func_00198948(&D_00314028, 0, 4U);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_024", func_00182D00);

INCLUDE_ASM("asm/nonmatchings/main_024", func_00182F08);

s32 func_00183110(s32 arg0) {
    s32 var_v0;

    var_v0 = -0x10000;
    if (func_00182B38() < 0) {
        return var_v0;
    }
    if (func_00182C38() != 0) {
        return -0x10004;
    }
    D_00313E00 = arg0;
    if (func_0017EA80(&D_00314000, 8, 0, &D_00313E00, 4, &D_00313E00, 4, 0, 0) < 0) {
        var_v0 = -0x10001;
        /* Duplicate return node #7. Try simplifying control flow for better match */
        return var_v0;
    }
    return D_00313E00;
}

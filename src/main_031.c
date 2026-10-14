#include "common.h"

void func_0018F648(void *arg0) {
    u8 *spr;

    spr = (u8 *)0x70000000;
    func_0018A378(1);
    *(u8 **)((u8 *)arg0 + 0x590) = spr;
    *(u8 **)((u8 *)arg0 + 0x594) = spr + 0x1800;
    *(u8 **)((u8 *)arg0 + 0x6D0) = spr + 0x1B00;
    *(u8 **)((u8 *)arg0 + 0x6D4) = spr + 0x3300;
    *(s32 *)((u8 *)arg0 + 0x810) = 0;
}

void func_0018F6A8(void *arg0) {
    (*(s32 *)((u8 *)arg0 + 0x818)) = 1;
    (*(s32 *)((u8 *)arg0 + 0x1B0)) = 0;
    func_001843E0();
    *(volatile s32 *)0x1000F590 = *(volatile s32 *)0x1000F520 | 0x10000;
    *(volatile s32 *)0x1000B000 = 0;
    *(volatile s32 *)0x1000B400 = 0;
    *(volatile s32 *)0x1000D400 = 0;
    *(volatile s32 *)0x1000F590 = *(volatile s32 *)0x1000F520 & 0xFFFEFFFF;
    func_00184428();
    *(volatile s32 *)0x1000B020 = 0;
    *(volatile s32 *)0x1000B420 = 0;
    *(volatile s32 *)0x1000D420 = 0;
    *(volatile s32 *)0x10002010 = 0x40000000;
    func_001903C8(0, 0);
}

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

void func_0018F918(void *arg0) {
    u32 v;

    (*(s32 *)((u8 *)arg0 + 0xD4)) = 0;
    v = func_0018BA48(arg0, 0x20);
    (*(s32 *)((u8 *)arg0 + 0x124)) = v >> 20;
    (*(s32 *)((u8 *)arg0 + 0x128)) = (v >> 8) & 0xFFF;
    if ((*(s32 *)((u8 *)arg0 + 0x128)) > 0xAF0) {
        func_0018F7B0((s32)arg0, &D_002BCAA8);
    }
    v = func_0018BA48(arg0, 0x1E);
    (*(s32 *)((u8 *)arg0 + 0x134)) = v >> 12;
    (*(s32 *)((u8 *)arg0 + 0x138)) = (v >> 1) & 0x3FF;
    if (((*(s32 *)((u8 *)arg0 + 0x840)) = func_0018BA48(arg0, 1)) != 0) {
        func_0018B580(arg0);
        func_0018B550(arg0, 0x50000000);
        func_0018B580(arg0);
    } else {
        func_0018FDC8(arg0, 0x50000000, (s32)&D_0028DB80);
    }
    if (((*(s32 *)((u8 *)arg0 + 0x844)) = func_0018BA48(arg0, 1)) != 0) {
        func_0018B580(arg0);
        func_0018B550(arg0, 0x58000000);
        func_0018B580(arg0);
    } else {
        func_0018FDC8(arg0, 0x58000000, (s32)&D_0028DBC0);
    }
    func_0018BE58(arg0);
    func_0018FA40(*(void **)((u8 *)arg0 + 0x858));
}

INCLUDE_ASM("asm/nonmatchings/main_031", func_0018FA40);

static inline int uncachedAddr_0018FCE8(int addr) {
    return (addr & 0x0FFFFFFF) | 0x20000000;
}

/* _initRefImages (this SDK passes the picture size as two more arguments): adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

void func_0018FCE8(int *frame0, int *frame1, int *frame2, int *top0, int *top1, int *top2, int *bot0, int *bot1,
                   int *bot2, int y, int cb, int cr, int width, int height) {
    int size = width * height;

    *frame0 = uncachedAddr_0018FCE8(y);
    *frame1 = uncachedAddr_0018FCE8(cb);
    *frame2 = uncachedAddr_0018FCE8(cr);
    *top0 = uncachedAddr_0018FCE8(y);
    *top1 = uncachedAddr_0018FCE8(cb);
    *top2 = uncachedAddr_0018FCE8(cr);
    *bot0 = uncachedAddr_0018FCE8(y + size / 512 * 384);
    *bot1 = uncachedAddr_0018FCE8(cb + size / 512 * 384);
    *bot2 = uncachedAddr_0018FCE8(cr + size / 512 * 384);
}

void func_0018FDC8(void *arg0, s32 arg1, s32 arg2) {
    s32 sp0[8];
    sp0[0] = /* extra? */ 2;
    func_0018EF48((*(s32 *)((u8 *)arg0 + 0x858)), sp0);
    func_0018B580(arg0);
    *(volatile s32 *)0x10002000 = 0;
    func_0018B580(arg0);
    func_001843E0();
    *(volatile s32 *)0x1000B410 = arg2 & 0x0FFFFFFF;
    *(volatile s32 *)0x1000B420 = 4;
    *(volatile s32 *)0x1000B400 = 0x101;
    func_00184428();
    func_0018B550(arg0, arg1);
    func_0018B580(arg0);
    sp0[0] = /* extra? */ 3;
    func_0018EF48((*(s32 *)((u8 *)arg0 + 0x858)), sp0);
}

void func_0018FEA0(void *arg0) {
    u8 *d;
    u32 v;
    u32 prof;
    s32 chroma;
    s32 hext;
    s32 vext;
    s32 brext;
    s32 vbvext;

    d = arg0;
    *(s32 *)(d + 0x848) = 1;
    func_0018A378(0);
    v = func_0018BA48(arg0, 28);
    brext = (v >> 1) & 0xFFF;
    vext = (v >> 13) & 3;
    hext = (v >> 15) & 3;
    chroma = (v >> 17) & 3;
    *(s32 *)(d + 0x140) = chroma;
    if (chroma != 1) {
        func_0018F7B0((s32)arg0, &D_002BCAC0);
    }
    *(s32 *)(d + 0x13C) = (v >> 19) & 1;
    prof = v >> 20;
    vbvext = (u32)func_0018BA48(arg0, 16) >> 8;
    if (prof != 0x48 && prof != 0x58 && prof != 0x44) {
        func_0018F7B0((s32)arg0, &D_002BCAE8);
    }
    *(s32 *)(d + 0x124) = (hext << 12) | (*(s32 *)(d + 0x124) & 0xFFF);
    *(s32 *)(d + 0x128) = (vext << 12) | (*(s32 *)(d + 0x128) & 0xFFF);
    *(s32 *)(d + 0x134) += brext << 18;
    *(s32 *)(d + 0x138) += vbvext << 10;
}

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

s32 func_001903C8(s32 arg0, s32 arg1) {
    u32 r;

    r = 0;
    switch (arg0) {
    case 0:
        while (*(volatile s32 *)0x10002010 < 0) {
        }
        r = 0;
        break;
    case 1:
        r = (u32)*(volatile s32 *)0x10002010 >> 31;
        break;
    }
    return r;
}

void func_00190430(s32 arg0) {
    func_001843E0();
    *(volatile s32 *)0x1000F590 = *(volatile s32 *)0x1000F520 | 0x10000;
    *(volatile s32 *)0x1000B400 = arg0;
    *(volatile s32 *)0x1000F590 = *(volatile s32 *)0x1000F520 & 0xFFFEFFFF;
    func_00184428();
}

extern volatile __int128 D_0028DC10[5];
extern __int128 D_0028DC60[2];

/* sceIpuInit: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

void func_00190498(void) {
    func_00190430(1);
    *(volatile s32 *)0x10002010 = 0x40000000;
    while (*(volatile s32 *)0x10002010 < 0) {}
    *(volatile s32 *)0x10002000 = 0;
    while (*(volatile s32 *)0x10002010 < 0) {}
    *(volatile __int128 *)0x10007010 = D_0028DC10[0];
    *(volatile __int128 *)0x10007010 = D_0028DC10[1];
    *(volatile __int128 *)0x10007010 = D_0028DC10[2];
    *(volatile __int128 *)0x10007010 = D_0028DC10[3];
    *(volatile __int128 *)0x10007010 = D_0028DC10[4];
    *(volatile __int128 *)0x10007010 = D_0028DC10[4];
    *(volatile __int128 *)0x10007010 = D_0028DC10[4];
    *(volatile __int128 *)0x10007010 = D_0028DC10[4];
    *(volatile s32 *)0x10002000 = 0x50000000;
    while (*(volatile s32 *)0x10002010 < 0) {}
    *(volatile s32 *)0x10002000 = 0x58000000;
    while (*(volatile s32 *)0x10002010 < 0) {}
    *(volatile __int128 *)0x10007010 = D_0028DC60[0];
    *(volatile __int128 *)0x10007010 = D_0028DC60[1];
    *(volatile s32 *)0x10002000 = 0x60000000;
    while (*(volatile s32 *)0x10002010 < 0) {}
    *(volatile s32 *)0x10002000 = 0x90000000;
    while (*(volatile s32 *)0x10002010 < 0) {}
    *(volatile s32 *)0x10002010 = 0x40000000;
    while (*(volatile s32 *)0x10002010 < 0) {}
    *(volatile s32 *)0x10002000 = 0;
    while (*(volatile s32 *)0x10002010 < 0) {}
}

s32 func_0017E240(s32);
extern s8 D_002BCBC0;
extern s32 D_00315680;

typedef struct CdCd_001906D0 {
    s32 unk0[9];
    s32 serve;
} CdCd_001906D0;

s32 func_001906D0(void) {
    s32 i;

    func_0017E240(0);
    while (1) {
        if (func_0017E8B0(&D_00315680, 0x80000701, 0) < 0) {
            func_00199B50(&D_002BCBC0);
            return -1;
        }
        for (i = 10000; i != -1; i--) {
        }
        if ((*(CdCd_001906D0 *)&D_00315680).serve != 0) {
            break;
        }
    }
    func_0017BB60(0);
    return 0;
}

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

void func_00190A00(s32 arg0, s32 arg1, s32 arg2) {
    func_0017B910(arg2);
    __asm__ volatile("sync");
    __asm__ volatile("ei");
}

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

s32 func_00190A90(void (*arg0)(void)) {
    s32 old;

    if (func_001914F8(1) != 0) {
        return 0;
    }
    func_001843E0();
    old = (s32) D_003156C0;
    D_003156C0 = (void (*)(s32)) arg0;
    func_00184428();
    return old;
}

INCLUDE_ASM("asm/nonmatchings/main_031", func_00190AE8);

void func_00190B88(void) {
    while (1) {
        func_0017B920(D_0028DCE0);
        if (D_0028DD14 == -1) {
            D_0028DCF0 = 0;
            D_0028DD14 = 0;
            D_0028DCD4 = 0;
            D_003156CC = 0;
            func_0017B720();
        }
        if (D_0028DCD0 > 0) {
            ((s32 (*)(char *, ...))func_0017DA98)(D_002BCBE8, D_003156C0, D_0028DD18);
        }
        if (D_003156C0 != NULL && D_0028DD18 != 0) {
            D_003156C0(D_0028DD18);
        }
        D_0028DCF0 = 0;
    }
}

typedef struct {
    s32 status;
    void *entry;
    void *stack;
    s32 stackSize;
    void *gpReg;
    s32 initPriority;
} ThParam_00190C48;

extern s32 D_0028DCD4;
extern s32 D_003156D0;
extern s32 D_003156D8;
extern ThParam_00190C48 D_00315708;
extern s32 D_00317EF0;

s32 func_00190C48(s32 arg0, void *arg1, s32 arg2) {
    s32 ret = 1;

    if (D_0028DCD4 == 0) {
        D_003156D0 = func_0017B7D0();
        func_0017B7E0(D_003156D0, &D_003156D8);
        D_00315708.stackSize = arg2;
        D_00315708.gpReg = &D_00317EF0;
        D_00315708.entry = func_00190B88;
        D_00315708.stack = arg1;
        D_00315708.initPriority = arg0;
        D_0028DCD4 = func_0017B6E0(&D_00315708);
        func_0017B700(D_0028DCD4, 0);
    } else {
        func_0017B770(D_0028DCD4, arg0);
        ret = 0;
    }
    return ret;
}

void func_00190AE8(s32 *);

typedef struct CdDirBuf_00190D20 {
    s32 n1;
    s32 n2;
    u8 *d1;
    u8 *d2;
    u8 b1[0x40];
    u8 b2[0x40];
} CdDirBuf_00190D20;

void func_00190D20(void *arg0) {
    CdDirBuf_00190D20 *p;
    u8 *d;
    s32 i;

    p = (CdDirBuf_00190D20 *)((u32)arg0 | 0x20000000);
    if (p->n1 > 0) {
        d = p->d1;
        for (i = 0; i < p->n1; i++) {
            d[i] = p->b1[i];
        }
    }
    if (p->n2 > 0) {
        d = p->d2;
        for (i = 0; i < p->n2; i++) {
            d[i] = p->b2[i];
        }
    }
    func_00190AE8(&D_0028DD14);
}

void func_00190DC0(void) {
    s32 sp0[8];

    if (D_0028DCE8 == -1 || D_0028DCEC == -1) {
        sp0[5] = 0;
        sp0[2] = 1;
        sp0[1] = 1;
        (*(volatile s32 *)&D_0028DCE8) = func_0017B8E0(sp0);
        D_0028DCEC = func_0017B8E0(sp0);
        sp0[2] = 0;
        (*(volatile s32 *)&D_0028DCE0) = func_0017B8E0(sp0);
        D_0028DCF0 = 0;
    }
}

void func_00190E58(void) {
    if (D_0028DCD4 != 0) {
        *(volatile s32 *)&D_0028DD14 = -1;
        func_0017B900(*(volatile s32 *)&D_0028DCE0);
    }
    func_0017B8F0(D_0028DCE8);
    func_0017B8F0(D_0028DCEC);
    func_0017B8F0(D_0028DCE0);
    func_001843E0();
    func_0017DE88(0x80000012);
    func_00184428();
}

s32 func_00190ED8(s32 arg0, s32 arg1) {
    s32 temp_s0;

    if (D_0028DCFC < 0) {
        func_00190F88();
    }
    func_001843E0();
    temp_s0 = D_003156C4;
    D_003156C8 = arg1;
    D_003156C4 = arg0;
    func_00184428();
    return temp_s0;
}

void func_00190F48(void) {
    if (D_003156C4 != 0) {
        if (D_0028DCE4 == 0) {
            ((void (*)(s32)) D_003156C4)(D_003156C8);
        }
    }
}

s32 func_00190F88(void) {
    D_0028DCE4 = 1;
    func_001843E0();
    func_0017DE58(0x80000012, &func_00190F48, 0);
    func_00184428();
    D_0028DCE4 = 0;
    D_0028DCFC = 1;
    return 1;
}

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

s32 func_001914F8(s32 arg0) {
    if (arg0 == 0) {
        if (D_0028DCD0 > 0) {
            func_0017DA98(&D_002BCCC0);
        }
        while (D_0028DCF0 != 0 || func_0017EC70(&D_0028EE90) != 0) {
            func_00190A28(0x3C);
        }
        return 0;
    }
    if (D_0028DCF0 != 0 || func_0017EC70(&D_0028EE90) != 0) {
        return 1;
    }
    return 0;
}

s32 func_00191598(s32 arg0) {
    if (arg0 == 0) {
        if (D_0028DCD0 > 0) {
            func_0017DA98(&D_002BCCD0);
        }
        while (func_0017EC70(&D_0028F708) != 0) {
            func_00190A28(0x3C);
        }
        return 0;
    }
    return func_0017EC70(&D_0028F708);
}

INCLUDE_ASM("asm/nonmatchings/main_031", func_00191608);

typedef struct CdClient_00191778 {
    void *pkt;
    int pid;
    int sema;
    unsigned int mode;
    unsigned int command;
    unsigned int buff;
    unsigned int cbuff;
    void (*endFunc)(void *);
    void *endParam;
    unsigned int serve;
} CdClient_00191778;

extern volatile int D_0028DCF4;
extern char D_002BCD20[];
extern char D_002BCD40[];
extern int D_0028DCF8;
extern int D_0028DD00;
extern int D_0028DD04;
extern int D_0028DD08;
extern int D_0028DD0C;
extern int D_0028DD10;
extern int D_003156D0;
extern CdClient_00191778 D_003158E8;
extern int D_00315940;
s32 func_0017E240(s32);

/* sceCdInit: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

s32 func_00191778(s32 mode) {
    int *p;
    int ver;
    int r;
    int w;
    int type;
    int v1;
    int v2;

    if (func_00191598(1) != 0) {
        return 0;
    }
    func_0017E240(0);
    D_003156D0 = func_0017B7D0();
    *(volatile int *)&D_0028DCE4 = 1;
    D_0028DD00 = -1;
    D_0028DCF8 = -1;
    D_0028DD08 = -1;
    D_0028DD04 = -1;
    D_0028DD0C = -1;
    D_0028DCFC = -1;
    D_0028DCF4 = 0;
    D_0028DD10++;
    while (1) {
        r = func_0017E8B0(&D_003158E8, 0x80000592, 0);
        if (r < 0) {
            if (D_0028DCD0 > 0) {
                ((void (*)(const char *, ...))func_0017DA98)(D_002BCD20, r, D_0028DD10);
            }
            w = 0x100000;
            while (w--) {}
            continue;
        }
        if (D_003158E8.serve != 0) {
            D_00315940 = mode;
            D_0028DD0C = 0;
            func_0017E190(&D_00315940, 4);
            p = &D_0028EEC0;
            if (func_0017EA80((s32 *)&D_003158E8, 0, 0, &D_00315940, 4, p, 16, 0, 0) < 0) {
                *(volatile int *)&D_0028DCE4 = 0;
                return 0;
            }
            break;
        }
        w = 0x100000;
        while (w--) {}
    }
    v1 = *(int *)((int)(p + 1) | 0x20000000);
    v2 = *(int *)((int)(p + 2) | 0x20000000);
    type = *(int *)((int)(p + 3) | 0x20000000);
    ver = 1;
    if (type == 0xFF) {
    } else if (type == 0xFE) {
        D_0028DCD0 = 1;
    } else if (v1 / 256 < 2 || v2 / 256 < 2) {
        ver = 2;
    }
    *(volatile int *)&D_0028DCE4 = 0;
    switch (mode) {
    case 5:
        if (D_0028DCD0 > 0) {
            ((void (*)(const char *, ...))func_0017DA98)(D_002BCD40);
        }
        func_00190E58();
        *(volatile int *)&D_0028DCE8 = -1;
        *(volatile int *)&D_0028DCEC = -1;
        *(volatile int *)&D_0028DCE0 = -1;
        break;
    case 0:
    case 1:
    default:
        func_00190DC0();
        func_00190F88();
        break;
    }
    return ver;
}

INCLUDE_ASM("asm/nonmatchings/main_031", func_00191A58);

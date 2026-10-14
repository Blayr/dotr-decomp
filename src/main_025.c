#include "common.h"
#include "sce/libkernl.h"

s32 func_001831A0(void *arg0) {
    u8 *b_D_00313E08;
    s32 *temp_v1;
    s32 var_v0;

    var_v0 = 0xFFFF0000;
    if (func_00182B38() < 0) {
        return var_v0;
    }
    if (func_00182C38() != 0) {
        return 0xFFFEFFFC;
    }
    b_D_00313E08 = (u8 *)&D_00313E08;
    func_0019C2B8((void *)b_D_00313E08, arg0, 0xFCU);
    temp_v1 = (void *)b_D_00313E08 - 8;
    (*(s8 *)((u8 *)temp_v1 + 0x103)) = 0;
    if (func_0017EA80(&D_00314000, 9, 0, temp_v1, 0x200, temp_v1, 4, 0, 0) < 0) {
        var_v0 = 0xFFFEFFFF;
        /* Duplicate return node #9. Try simplifying control flow for better match */
        return var_v0;
    }
    return (*(s32 *)(b_D_00313E08 + -8));
}

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
    return ((s32 (*)(s32))func_00182D00)(arg0);
}

/* _sceSifLoadModule: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

s32 func_00183310(s32 name, s32 arglen, s32 args, s32 ret, s32 rpcno) {
    char *buf;
    s32 r;

    if (func_00182B38() < 0) {
        return 0xFFFF0000;
    }
    if (func_00182C38() != 0) {
        return 0xFFFEFFFC;
    }
    func_0019C2B8((char *)&D_00313E00 + 8, (char *)name, 252);
    buf = ((char *)&D_00313E00 + 8) - 8;
    buf[0x103] = 0;
    if (args != 0) {
        if (arglen >= 0xFD) {
            *(SceLfArgBuf *)(buf + 0x104) = *(SceLfArgBuf *)args;
            *(s32 *)&D_00313E00 = 0xFC;
        } else {
            func_00198790(buf + 0x104, (char *)args, arglen);
            *(s32 *)buf = arglen;
        }
    } else {
        buf[0x104] = 0;
        *(s32 *)buf = 0;
    }
    if (func_0017EA80(&D_00314000, rpcno, 0, &D_00313E00, 0x200, &D_00313E00, 8, 0, 0) < 0) {
        return 0xFFFEFFFF;
    }
    r = *(s32 *)((char *)&D_00313E00 + 0);
    *(s32 *)ret = *(s32 *)((char *)&D_00313E00 + 4);
    return r;
}

void func_00183538(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp0[4];
    func_00183310(arg0, arg1, arg2, (s32) sp0, 0);
}

s32 func_00183558(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return func_00183310(arg0, arg1, arg2, arg3, 0);
}

/* _sceSifLoadElfPart: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

s32 func_00183578(s32 name, s32 sec, s32 out, s32 rpcno) {
    char *buf;
    s32 r;

    if (func_00182B38() < 0) {
        return 0xFFFF0000;
    }
    if (func_00182C38() != 0) {
        return 0xFFFEFFFC;
    }
    func_0019C2B8((char *)&D_00313E00 + 8, (char *)name, 252);
    buf = ((char *)&D_00313E00 + 8) - 8;
    buf[0x103] = 0;
    func_0019C2B8(((char *)&D_00313E00 + 8) + 252, (char *)sec, 252);
    buf[0x1FF] = 0;
    if (func_0017EA80(&D_00314000, rpcno, 0, (s32 *)buf, 0x200, (s32 *)buf, 0x10, 0, 0) < 0) {
        return 0xFFFEFFFF;
    }
    r = *(s32 *)buf;
    if (r == 0) {
        return 0xFFFEFFFD;
    }
    ((s32 *)out)[0] = r;
    ((s32 *)out)[1] = *(s32 *)(buf + 4);
    return 0;
}

s32 func_00183680(s32 arg0, s32 arg1, s32 arg2) {
    return func_00183578(arg0, arg1, arg2, 1);
}

s32 func_001836A0(s32 arg0, s32 arg1) {
    return func_00183578(arg0, (s32) &D_002BC1E8, arg1, 1);
}


typedef struct IopPeek_001836C8 {
    s32 addr;
    s32 type;
} IopPeek_001836C8;

s32 func_001836C8(s32 arg0, void *arg1, u32 arg2) {
    IopPeek_001836C8 *p;

    if (func_00182B38() < 0) {
        return 0xFFFF0000;
    }
    if (arg2 >= 3) {
        goto bad;
    }
    p = (IopPeek_001836C8 *)&D_00313E00;
    p->addr = arg0;
    p->type = arg2;
    if (func_0017EA80(&D_00314000, 3, 0, (s32 *)p, 0x20, (s32 *)p, 0x20, 0, 0) < 0) {
        return 0xFFFEFFFF;
    }
    if (arg2 == 0) {
        *(u8 *)arg1 = *(u8 *)&D_00313E00;
    } else if (arg2 == 1) {
        *(u16 *)arg1 = *(u16 *)&D_00313E00;
    } else if (arg2 != 2) {
bad:
        return 0xFFFEFFFE;
    } else {
        *(s32 *)arg1 = D_00313E00;
    }
    return 0;
}

extern s32 D_00313E00;
extern s32 D_00314000;

typedef struct IopPoke_001837B8 {
    s32 addr;
    s32 type;
    s32 val;
} IopPoke_001837B8;

s32 func_001837B8(s32 arg0, void *arg1, s32 arg2) {
    IopPoke_001837B8 *p;

    if (func_00182B38() < 0) {
        return 0xFFFF0000;
    }
    p = (IopPoke_001837B8 *)&D_00313E00;
    p->addr = arg0;
    p->type = arg2;
    if (arg2 == 0) {
        *(u8 *)&p->val = *(u8 *)arg1;
    } else if (arg2 == 1) {
        *(u16 *)&p->val = *(u16 *)arg1;
    } else if (arg2 == 2) {
        p->val = *(s32 *)arg1;
    } else {
        return 0xFFFEFFFE;
    }
    if (func_0017EA80(&D_00314000, 2, 0, &D_00313E00, 0x20, &D_00313E00, 0x10, 0, 0) < 0) {
        return 0xFFFEFFFF;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_025", func_00183898);

s32 func_001839D8(void) {
    s32 x;

    x = func_0017BCF0(4) & 0x10000;
    return x != 0;
}

s32 func_00183A00(void) {
    if (func_0017BCF0(4) & 0x40000) {
        func_0017BD60();
        return 1;
    }
    return 0;
}

extern char D_002BC1F0[];
extern char D_002BC200[];

/* sceSifRebootIop: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

s32 func_00183A38(char *arg) {
    extern void func_0017E240(s32);
    char buf[80];
    char *s = D_002BC1F0;
    char *d;
    char *p;

    for (p = arg; *p != 0; p++) {}
    if ((u32)(p + 11 - arg) > 80) {
        func_0017DA98(D_002BC200, arg);
        return 0;
    }
    func_0017E240(0);
    func_0017E3E0();
    d = buf;
    while (*s != 0) {
        *d++ = *s++;
    }
    while (*arg != 0) {
        *d++ = *arg++;
    }
    *d = 0;
    return func_00183898(buf, 0);
}

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

int func_00183C30(int arg0, int *arg1, int arg2) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x5A\n\tsyscall" : "=r" (ret));
    return ret;
}

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

int func_00183C78(int arg0) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x5B\n\tsyscall" : "=r" (ret));
    return ret;
}

void func_00183C88(int arg0, int arg1) {
    __asm__ __volatile__("addiu\t$3,$0,0x74\n\tsyscall");
}

extern s32 D_0028CAC8;
extern s32 D_0028CE38;

typedef struct KPatch_00183C98 {
    s32 addr;
    s32 val;
} KPatch_00183C98;

void func_00183C98(void) {
    KPatch_00183C98 *t;
    u32 i;

    t = (KPatch_00183C98 *)&D_0028CE38;
    func_00183C88(t[0].addr, t[0].val);
    func_00183C30(0x80075000, &D_0028CAC8, 0x328);
    func_0017BB60(0);
    func_0017BB60(2);
    func_00183C88(t[1].addr, t[1].val);
    func_00183C88(t[2].addr, t[2].val);
    for (i = 3; i < 8; i++) {
        func_00183C88(t[i].addr, func_00183C78(t[i].addr));
    }
}

int func_00183D50(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x55\n\tsyscall" : "=r" (ret));
    return ret;
}

int func_00183D60(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,-0x55\n\tsyscall" : "=r" (ret));
    return ret;
}

int func_00183D70(int arg0, int arg1, int arg2, int arg3, int arg4) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x56\n\tsyscall" : "=r" (ret));
    return ret;
}

s32 func_00183D80(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 r;

    if ((u32)(arg0 - 13) >= 35) {
        r = -1;
    } else {
        r = func_00183D70(arg0, arg1, arg2, arg3, arg4);
    }
    return r;
}

int func_00183DB0(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,-0x56\n\tsyscall" : "=r" (ret));
    return ret;
}

int func_00183DC0(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x57\n\tsyscall" : "=r" (ret));
    return ret;
}

int func_00183DD0(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,-0x57\n\tsyscall" : "=r" (ret));
    return ret;
}

int func_00183DE0(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x58\n\tsyscall" : "=r" (ret));
    return ret;
}

int func_00183DF0(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,-0x58\n\tsyscall" : "=r" (ret));
    return ret;
}

int func_00183E00(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x59\n\tsyscall" : "=r" (ret));
    return ret;
}

s32 func_00183E10(void) {
    if (func_0017BD40() == 0x02000000) {
        return func_00183E50();
    }
    return func_0017BD50();
}

extern s32 D_0028D0E8;
extern char D_002BC220[];
extern char D_002BC258[];
extern char D_002BC270[];
extern char D_002BC288[];

typedef struct {
    s32 a, b, c, d;
} TlbEnt;

s32 func_00183E50(void) {
    register s32 i __asm__("$25");
    s32 *d;
    TlbEnt *e;
    s32 n, j, addr;

    d = &D_0028D0E8;
    func_0017DA60(D_002BC220, d[0] - 1, d[0], d[0] + d[1] - 1, d[0] + d[1], d[0] + d[1] + d[2] - 1);
    __asm__ volatile("mtc0\t$0, $6");
    __asm__ volatile("sync.p");
    n = d[0];
    i = 0;
    if (n > 48) {
        func_0017DA60(D_002BC258);
        func_001847B0(1);
    }
    for (e = (TlbEnt *)d[4]; i < n; i++, e++) {
        func_00183D70(i, e->a, e->b, e->c, e->d);
    }
    d = &D_0028D0E8;
    n = i + d[1];
    if (n > 48) {
        func_0017DA60(D_002BC270);
        func_001847B0(1);
    }
    for (e = (TlbEnt *)d[5]; i < n; i++, e++) {
        func_00183D70(i, e->a, e->b, e->c, e->d);
    }
    d = &D_0028D0E8;
    d[3] = i;
    __asm__ volatile("mtc0\t%0, $6" : : "r"(i));
    __asm__ volatile("sync.p");
    if (d[2] > 0) {
        n = i + d[2];
        if (n > 48) {
            func_0017DA60(D_002BC288);
            func_001847B0(1);
        }
        for (e = (TlbEnt *)d[6]; i < n; i++, e++) {
            func_00183D70(i, e->a, e->b, e->c, e->d);
        }
    }
    for (j = i; j < 48; j++) {
        func_00183D70(j, 0, 0xE0000000 + (j << 13), 0, 0);
    }
    return i;
}

/* the 15 padding nops after it (func_00184080 starts at 0x184080) */
__asm__(".space 60");

INCLUDE_ASM("asm/nonmatchings/main_025", func_00184080);

s32 func_001843E0(void) {
    s32 eie, res, st;
    __asm__ volatile("mfc0\t%0, $12" : "=r"(eie));
    eie &= 0x10000;
    if (eie) {
        res = eie != 0;
        __asm__(".p2align 3");
    again:
        __asm__ volatile("di");
        __asm__ volatile("sync.p");
        __asm__ volatile("mfc0\t%0, $12" : "=r"(st));
        if (st & 0x10000) goto again;
    } else {
        res = 0;
    }
    return res;
}

s32 func_00184428(void) {
    s32 eie;
    __asm__ volatile("mfc0\t%0, $12" : "=r"(eie));
    eie &= 0x10000;
    __asm__ volatile("ei");
    return eie != 0;
}

void func_00184440(void) {
    s32 a[8];
    s32 b[8];

    a[1] = 1;
    a[2] = 1;
    b[1] = 1;
    b[2] = 1;
    D_0028D114 = func_0017B8E0(a);
    D_0028D118 = func_0017B8E0(b);
}

s32 *func_00184488(s32 arg0) {
    s32 *p = (s32 *)0x80000000;
    while (*p != arg0) {
        p++;
    }
    return p;
}

s32 func_001844C0(s32 *arg0) {
    register s32 ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x83\n\tsyscall" : "=r" (ret));
    return ret;
}

s32 func_001844D0(void) {
    func_00184510((*(s32 *)(&D_0028D108)), (*(s32 *)((u8 *)(&D_0028D108) + 4)));
    return func_001844C0(&func_00184488) - 0x20C;
}

void func_00184510(int arg0, int arg1) {
    __asm__ __volatile__("addiu\t$3,$0,0x74\n\tsyscall");
}

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

void func_00184580(int arg0, int arg1) {
    __asm__ __volatile__("addiu\t$3,$0,0x74\n\tsyscall");
}

int func_00184590(int arg0, int *arg1, int arg2) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x5A\n\tsyscall" : "=r" (ret));
    return ret;
}

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

int func_001845D8(int arg0) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x5B\n\tsyscall" : "=r" (ret));
    return ret;
}

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

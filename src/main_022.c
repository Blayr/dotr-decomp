#include "common.h"

s32 func_0017BFD0(void) {
    return -1;
}

s32 func_0017BFD8(void) {
    return -1;
}

u32 func_0017BFE0(s32 incr) {
    s32 eie, st, old, new;
    __asm__ volatile("mfc0\t%0, $12" : "=r"(eie));
    eie &= 0x10000;
    if (eie) {
    again:
        __asm__ volatile("di");
        __asm__ volatile("sync.p");
        __asm__ volatile("mfc0\t%0, $12" : "=r"(st));
        if (st & 0x10000) goto again;
    }
    new = D_0028C254 + incr;
    if (func_0017B8C0() < (u32)new) {
        *(s32 *)func_001966F8() = 12;
        if (eie) {
            __asm__ volatile("ei");
        }
        return 0xFFFFFFFF;
    }
    old = D_0028C254;
    D_0028C254 = new;
    if (eie) {
        __asm__ volatile("ei");
    }
    return old;
}

s32 func_0017C090(void) {
    return 1;
}

s32 func_0017C098(s32 arg0, void *arg1) {
    (*(s64 *)((u8 *)arg1 + 0x48)) = 0;
    (*(s32 *)((u8 *)arg1 + 4)) = 0x2000;
    return 0;
}

s32 func_0017C0B0(void) {
    return 1;
}

s32 func_0017C0B8(s32 arg0, s32 arg1) {
    if (arg0 == 1) {
        func_001847B0(arg1);
    }
    return 0;
}

s32 func_0017C0E0(void) {
    *(s32 *)func_001966F8() = 5;
    return -1;
}

s32 func_0017C108(void) {
    *(s32 *)func_001966F8() = 5;
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/main_022", func_0017C130);

void func_0017C1D8(u32 arg0, u32 arg1) {
    s32 eie;
    __asm__ volatile("mfc0	%0, $12" : "=r"(eie));
    eie &= 0x10000;
    if (eie) {
        func_001843E0();
    }
    func_0017C130(arg0 & 0xFFFFFFC0, arg1 & 0xFFFFFFC0);
    if (eie) {
        func_00184428();
    }
}

void func_0017C258(u32 arg0, u32 arg1) {
    func_0017C130(arg0 & ~0x3F, arg1 & ~0x3F);
}

INCLUDE_ASM("asm/nonmatchings/main_022", func_0017C270);

void func_0017C318(u32 arg0, u32 arg1) {
    s32 eie;
    __asm__ volatile("mfc0	%0, $12" : "=r"(eie));
    eie &= 0x10000;
    if (eie) {
        func_001843E0();
    }
    func_0017C270(arg0 & 0xFFFFFFC0, arg1 & 0xFFFFFFC0);
    if (eie) {
        func_00184428();
    }
}

void func_0017C398(u32 arg0, u32 arg1) {
    func_0017C270(arg0 & ~0x3F, arg1 & ~0x3F);
}

s32 func_0017C3B0(void) {
    s32 s;
    __asm__ volatile("mfc0\t%0, $12" : "=r"(s));
    return (s ^ 1) & 1;
}

s32 func_0017C3C0(s32 arg0) {
    s32 eie, ret;
    __asm__ volatile("mfc0	%0, $12" : "=r"(eie));
    eie &= 0x10000;
    if (eie) {
        func_001843E0();
    }
    ret = func_0017B630(arg0);
    __asm__ volatile("sync");
    if (eie) {
        func_00184428();
    }
    return ret;
}

s32 func_0017C428(s32 arg0) {
    s32 eie, ret;
    __asm__ volatile("mfc0	%0, $12" : "=r"(eie));
    eie &= 0x10000;
    if (eie) {
        func_001843E0();
    }
    ret = func_0017B620(arg0);
    __asm__ volatile("sync");
    if (eie) {
        func_00184428();
    }
    return ret;
}

s32 func_0017C490(s32 arg0) {
    s32 eie, ret;
    __asm__ volatile("mfc0	%0, $12" : "=r"(eie));
    eie &= 0x10000;
    if (eie) {
        func_001843E0();
    }
    ret = func_0017B650(arg0);
    __asm__ volatile("sync");
    if (eie) {
        func_00184428();
    }
    return ret;
}

s32 func_0017C4F8(s32 arg0) {
    s32 eie, ret;
    __asm__ volatile("mfc0	%0, $12" : "=r"(eie));
    eie &= 0x10000;
    if (eie) {
        func_001843E0();
    }
    ret = func_0017B640(arg0);
    __asm__ volatile("sync");
    if (eie) {
        func_00184428();
    }
    return ret;
}

void func_0017C560(void) {
    func_0017B680();
    __asm__ volatile("sync");
}

void func_0017C580(void) {
    func_0017B690();
    __asm__ volatile("sync");
}

void func_0017C5A0(void) {
    func_0017B6A0();
    __asm__ volatile("sync");
}

void func_0017C5C0(void) {
    func_0017B6B0();
    __asm__ volatile("sync");
}

void func_0017C5E0(int arg0, int arg1) {
    __asm__ __volatile__("addiu\t$3,$0,0x74\n\tsyscall");
}

int func_0017C5F0(int arg0, int *arg1, int arg2) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x5A\n\tsyscall" : "=r" (ret));
    return ret;
}

s32 func_0017C600(s32 *arg0, s32 *arg1, u32 arg2) {
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

INCLUDE_ASM("asm/nonmatchings/main_022", func_0017C638);

s32 func_0017C638(s32);
extern s32 D_0028C258;
extern s32 D_0028C998;
extern s32 D_0028C9C0;

typedef struct KPatch_0017C648 {
    s32 addr;
    s32 val;
} KPatch_0017C648;

void func_0017C648(void) {
    KPatch_0017C648 *t;
    u32 i;

    if (!(*(volatile s32 *)0x10001810 & 0x100)) {
        t = (KPatch_0017C648 *)&D_0028C9C0;
        func_0017C5E0(t[0].addr, t[0].val);
        func_0017C5F0(0x80076000, &D_0028C258, 0x740);
        func_0017C5F0(0x82000, &D_0028C998, 0x28);
        func_0017BB60(0);
        func_0017BB60(2);
        func_0017C5E0(t[1].addr, t[1].val);
        for (i = 2; i < 8; i++) {
            func_0017C5E0(t[i].addr, func_0017C638(t[i].addr));
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/main_022", func_0017C720);

typedef struct {
    s32 status;
    void *entry;
    void *stack;
    s32 stackSize;
    void *gpReg;
    s32 initPriority;
    s32 currentPriority;
    u32 attr;
    u32 option;
    s32 waitType;
    s32 waitId;
    s32 wakeupCount;
} ThParam_0017C7F8;

typedef struct {
    s32 count;
    s32 max_count;
    s32 init_count;
    s32 wait_threads;
    u32 attr;
    u32 option;
} SemParam_0017C7F8;

extern u8 D_00310110[];
extern s32 D_00317EF0;
void func_0017C720(void);
s32 func_0017B6E0(ThParam_0017C7F8 *);
s32 func_0017B700(s32, void *);
s32 func_0017B770(s32, s32);

s32 func_0017C7F8(void) {
    ThParam_0017C7F8 tp;
    SemParam_0017C7F8 sp;
    s32 tid;
    ring_t *r;

    if (D_0028CA00 > 0) {
        return -1;
    }
    sp.init_count = 0;
    sp.max_count = 0xFF;
    D_00310510 = func_0017B8E0(&sp);
    if (D_00310510 < 0) {
        return -1;
    }
    tp.entry = func_0017C720;
    tp.stack = D_00310110;
    tp.stackSize = 0x400;
    tp.gpReg = &D_00317EF0;
    tp.initPriority = 0;
    D_0028CA00 = tid = func_0017B6E0(&tp);
    if (tid < 0) {
        func_0017B8F0(D_00310510);
        return -1;
    }
    r = (ring_t *)&D_00310518;
    r->x0 = 0;
    r->count = 0;
    func_0017B700(tid, r);
    func_0017B770(func_0017B7D0(), 1);
    return D_0028CA00;
}

s32 func_0017C8D0(s32 arg0) {
    s32 tid;
    __asm__ volatile("addiu $3, $0, -0x2F\n\tsyscall\n\tdaddu %0, $2, $0" : "=r"(tid));
    if (tid != arg0) {
        return func_0017B820(arg0);
    }
    if ((u32)tid >= 0x100 || D_0028CA00 == 0) {
        return -1;
    }
    {
        ring_t *r = (ring_t *)&D_00310518;
        u32 i = r->count & 0x1FF;
        r->count = i + 1;
        r->e[i].a = 0;
        r->e[i].b = tid;
        func_0017B910(D_00310510);
    }
    return tid;
}

s32 func_0017C968(u32 arg0) {
    if (arg0 >= 0x80 || D_0028CA00 == 0) {
        return -1;
    }
    {
        ring_t *r = (ring_t *)&D_00310518;
        u32 i = r->count & 0x1FF;
        r->count = i + 1;
        r->e[i].a = 1;
        r->e[i].b = arg0;
        func_0017B910(D_00310510);
    }
    return arg0;
}

s32 func_0017C9E8(s32 arg0) {
    s32 tid;
    __asm__ volatile("addiu $3, $0, -0x2F\n\tsyscall\n\tdaddu %0, $2, $0" : "=r"(tid));
    if (tid != arg0) {
        return func_0017B860(arg0);
    }
    if ((u32)tid >= 0x100 || D_0028CA00 == 0) {
        return -1;
    }
    {
        ring_t *r = (ring_t *)&D_00310518;
        u32 i = r->count & 0x1FF;
        r->count = i + 1;
        r->e[i].a = 2;
        r->e[i].b = tid;
        func_0017B910(D_00310510);
    }
    return tid;
}

s32 func_0017CA80(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp0[4];
    sp0[0] = /* extra? */ (arg0 & 0xFFFF);
    sp0[1] = /* extra? */ arg1;
    sp0[2] = /* extra? */ arg2;
    sp0[3] = /* extra? */ ((s32) &D_00310920 | 0x20000000);
    return func_0017BD10(1, sp0);
}

void func_0017CAC8(s32 arg0) {
    s32 sp0[4];
    sp0[0] = arg0;
    func_0017BD10(2, sp0);
}

void func_0017CAF0(s32 arg0, s8 arg1) {
    s32 sp0[4];
    sp0[0] = arg0;
    sp0[1] = (s32) arg1;
    func_0017BD10(3, sp0);
}

void func_0017CB20(s32 arg0) {
    s32 sp0[4];
    sp0[0] = arg0;
    func_0017BD10(4, sp0);
}

void func_0017CB48(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp0[4];
    s32 temp_a2;

    temp_a2 = arg2 & 0xFFFF;
    sp0[0] = arg0;
    sp0[1] = arg1;
    sp0[2] = temp_a2;
    func_0017BD10(-5, sp0);
}

void func_0017CB80(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp0[4];
    s32 temp_a2;

    temp_a2 = arg2 & 0xFFFF;
    sp0[0] = arg0;
    sp0[1] = arg1;
    sp0[2] = temp_a2;
    func_0017BD10(-6, sp0);
}

void func_0017CBB8(s32 arg0, s8 arg1) {
    s32 sp0[4];
    sp0[0] = arg0;
    sp0[1] = (s32) arg1;
    func_0017BD10(-7, sp0);
}

void func_0017CBE8(s32 arg0) {
    s32 sp0[4];
    sp0[0] = arg0;
    func_0017BD10(-8, sp0);
}

void func_0017CC10(s32 arg0) {
    s32 sp0[4];
    sp0[0] = arg0;
    func_0017BD10(-9, sp0);
}

void func_0017CC38(s32 arg0) {
    s32 sp0[4];
    sp0[0] = arg0;
    func_0017BD10(0x10, sp0);
}

s32 *func_0017CC60(s32 arg0) {
    void *temp_a0;

    (*(s32 *)(&D_00310980)) = arg0;
    temp_a0 = (u8 *)&D_00310980 + 0x10;
    (*(s32 *)((u8 *)(&D_00310980) + 4)) = 0;
    (*(void **)((u8 *)(&D_00310980) + 0xC)) = temp_a0;
    (*(void **)((u8 *)(&D_00310980) + 8)) = temp_a0;
    return &D_00310980;
}

void func_0017CC88(void *arg0) {
    void *temp_a0;

    (*(s32 *)((u8 *)arg0 + 4)) = (s32) ((*(s32 *)((u8 *)arg0 + 4)) + 1);
    temp_a0 = (*(void **)((u8 *)arg0 + 0xC)) + 1;
    (*(void **)((u8 *)arg0 + 0xC)) = temp_a0;
    if (temp_a0 == (arg0 + ((*(s32 *)arg0) + 0x10))) {
        (*(void **)((u8 *)arg0 + 0xC)) = (void *) (arg0 + 0x10);
    }
}

void func_0017CCC8(void *arg0) {
    void *temp_a0;

    (*(s32 *)((u8 *)arg0 + 4)) = (s32) ((*(s32 *)((u8 *)arg0 + 4)) - 1);
    temp_a0 = (*(void **)((u8 *)arg0 + 8)) + 1;
    (*(void **)((u8 *)arg0 + 8)) = temp_a0;
    if (temp_a0 == (arg0 + ((*(s32 *)arg0) + 0x10))) {
        (*(void **)((u8 *)arg0 + 8)) = (void *) (arg0 + 0x10);
    }
}

INCLUDE_ASM("asm/nonmatchings/main_022", func_0017CD08);

INCLUDE_ASM("asm/nonmatchings/main_022", func_0017CEA0);

typedef struct Deci2Q_0017CFF0 {
    s32 unk0;
    volatile s32 count;
    u8 *rptr;
} Deci2Q_0017CFF0;

typedef struct Deci2Tty_0017CFF0 {
    s32 sock;
    s32 unk4[5];
    Deci2Q_0017CFF0 *q;
} Deci2Tty_0017CFF0;

extern Deci2Tty_0017CFF0 D_00310A90;

s32 func_0017CFF0(char *arg0, s32 arg1) {
    s32 i;
    char *p;

    for (i = 0; i < arg1; i++) {
        p = &arg0[i];
        while (D_00310A90.q->count == 0) {
        }
        *p = *(*(Deci2Tty_0017CFF0 *)&D_00310A90).q->rptr;
        func_0017CCC8((*(Deci2Tty_0017CFF0 *)&D_00310A90).q);
        if (*p == '\n' || *p == '\r') {
            return i + 1;
        }
    }
    return i;
}

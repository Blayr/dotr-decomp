#include "common.h"

s32 func_0017BFD0(void) {
    return -1;
}

s32 func_0017BFD8(void) {
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/main_022", func_0017BFE0);

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

INCLUDE_ASM("asm/nonmatchings/main_022", func_0017C3B0);

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

INCLUDE_ASM("asm/nonmatchings/main_022", func_0017C5E0);

INCLUDE_ASM("asm/nonmatchings/main_022", func_0017C5F0);

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

INCLUDE_ASM("asm/nonmatchings/main_022", func_0017C648);

INCLUDE_ASM("asm/nonmatchings/main_022", func_0017C720);

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

INCLUDE_ASM("asm/nonmatchings/main_022", func_0017C968);

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

INCLUDE_ASM("asm/nonmatchings/main_022", func_0017CFF0);

#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_026", func_00184650);

void func_00184700(void) {
    func_00183E10();
}

s32 func_00184708(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_00184700();
    return func_0017B530(arg0, arg1, arg2, arg3);
}

void func_00184768(s32 arg0, s32 arg1, s32 arg2) {
    func_00184700();
    func_0017B520(arg0, arg1, arg2);
}

void func_001847B0(s32 arg0) {
    func_00184700();
    func_0017B500(arg0);
}

void func_001847D8(s32 arg0, s32 arg1) {
    func_00184700();
    func_0017BD00(arg0, arg1);
}

INCLUDE_ASM("asm/nonmatchings/main_026", func_00184810);

s32 *func_001849A0(void) {
    return &D_0028D8F0;
}

INCLUDE_ASM("asm/nonmatchings/main_026", func_001849B0);

INCLUDE_ASM("asm/nonmatchings/main_026", func_00184A18);

INCLUDE_ASM("asm/nonmatchings/main_026", func_00184C88);

INCLUDE_ASM("asm/nonmatchings/main_026", func_00184D48);

INCLUDE_ASM("asm/nonmatchings/main_026", func_00184E10);

INCLUDE_ASM("asm/nonmatchings/main_026", func_00184FF8);

INCLUDE_ASM("asm/nonmatchings/main_026", func_00185100);

INCLUDE_ASM("asm/nonmatchings/main_026", func_001851E8);

s32 func_00185480(u8 *arg0, s32 arg1) {
    s32 odd;
    s32 ret;

    odd = arg1 & 1;
    func_00184C88(arg0 + odd * 0x28);
    if (odd != 0) {
        ret = func_00185100(arg0 + 0x140);
    } else {
        ret = func_00185100(arg0 + 0x50);
    }
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/main_026", func_001854E0);

INCLUDE_ASM("asm/nonmatchings/main_026", func_00185578);

INCLUDE_ASM("asm/nonmatchings/main_026", func_00185890);

typedef struct {
    u64 SBP : 14;
    u64 pad14 : 2;
    u64 SBW : 6;
    u64 pad22 : 2;
    u64 SPSM : 6;
    u64 pad30 : 2;
    u64 DBP : 14;
    u64 pad46 : 2;
    u64 DBW : 6;
    u64 pad54 : 2;
    u64 DPSM : 6;
    u64 pad62 : 2;
} Bitbltbuf_59D0;

typedef struct {
    u64 RRW : 12;
    u64 pad12 : 20;
    u64 RRH : 12;
    u64 pad44 : 20;
} Trxreg_59D0;

typedef struct {
    u32 vifcode[4];
    u64 giftag[2];
    Bitbltbuf_59D0 bitbltbuf;
    s64 bitbltbufaddr;
    u64 trxpos;
    s64 trxposaddr;
    Trxreg_59D0 trxreg;
    s64 trxregaddr;
    u64 finish;
    s64 finishaddr;
    u64 trxdir;
    s64 trxdiraddr;
} StoreImage_59D0;

u64 func_0017BC00(void);
u64 func_0017BC20(u64);
extern __int128 D_0028D920;
extern char D_002BC4A0[];
extern char D_002BC4D8[];
extern char D_002BC508[];
extern char D_002BC548[];

#define D1_CHCR ((volatile u32 *)0x10009000)
#define D1_MADR ((volatile u32 *)0x10009010)
#define D1_QWC ((volatile u32 *)0x10009020)
#define GS_CSR ((volatile u64 *)0x12001000)
#define GS_BUSDIR ((volatile u64 *)0x12001040)
#define VIF1_STAT ((volatile u32 *)0x10003C00)
#define VIF1_FBRST ((volatile u32 *)0x10003C10)
#define GIF_CTRL ((volatile u32 *)0x10003000)
#define PRINTF ((s32 (*)(const char *, ...))func_00199B50)
#define VIF1_FIFO ((volatile __int128 *)0x10005000)
#define SET_MADR(a) if (((u32)(a) & 0x70000000) == 0x70000000) *D1_MADR = ((u32)(a) & 0x0FFFFFFF) | 0x80000000; else *D1_MADR = (u32)(a) & 0x0FFFFFFF

#define sp ((StoreImage_59D0 *)arg0)
#define dstaddr ((__int128 *)arg1)

s32 func_001859D0(void *arg0, void *arg1) {
    u32 timeout = 0;
    s32 dummy = 0;
    s32 rest = 0;
    s32 qwc1 = 0;
    s32 qwc8 = 0;
    s32 w, h, h2, bytes, size, i;
    u64 imr;
    union { __int128 q; u8 b[16]; } buf;

    w = sp->trxreg.RRW;
    h = sp->trxreg.RRH;
    h2 = 0;
    switch (sp->bitbltbuf.SPSM) {
    case 0:
    case 48:
        bytes = w * h * 4;
        rest = bytes & 15;
        qwc1 = (bytes >> 4) & 7;
        qwc8 = (bytes >> 4) & 0xFFFFFFF8;
        if (rest == 0) {
            h2 = h;
            dummy = 0;
        } else {
            h2 = (h + 3) & 0xFFFFFFFC;
            size = ((w * h2) >> 2);
            dummy = size - qwc8 - qwc1 - 1;
        }
        break;
    case 1:
    case 49:
        bytes = w * h * 3;
        rest = bytes & 15;
        qwc1 = (bytes >> 4) & 7;
        qwc8 = (bytes >> 4) & 0xFFFFFFF8;
        if (rest == 0) {
            h2 = h;
            dummy = 0;
        } else {
            h2 = (h + 15) & 0xFFFFFFF0;
            size = ((w * h2 * 3) >> 4);
            dummy = size - qwc8 - qwc1 - 1;
        }
        break;
    case 2:
    case 10:
    case 50:
    case 58:
        bytes = w * h * 2;
        rest = bytes & 15;
        qwc1 = (bytes >> 4) & 7;
        qwc8 = (bytes >> 4) & 0xFFFFFFF8;
        if (rest == 0) {
            h2 = h;
            dummy = 0;
        } else {
            h2 = (h + 7) & 0xFFFFFFF8;
            size = ((w * h2) >> 3);
            dummy = size - qwc8 - qwc1 - 1;
        }
        break;
    case 19:
    case 27:
        bytes = w * h;
        rest = bytes & 15;
        qwc1 = (bytes >> 4) & 7;
        qwc8 = (bytes >> 4) & 0xFFFFFFF8;
        if (rest == 0) {
            h2 = h;
            dummy = 0;
        } else {
            h2 = (h + 7) & 0xFFFFFFF8;
            size = ((w * h2) >> 4);
            dummy = size - qwc8 - qwc1 - 1;
        }
        break;
    case 20:
    case 36:
    case 44:
        bytes = (w * h) >> 1;
        rest = bytes & 15;
        qwc1 = (bytes >> 4) & 7;
        qwc8 = (bytes >> 4) & 0xFFFFFFF8;
        if (rest == 0) {
            h2 = h;
            dummy = 0;
        } else {
            h2 = (h + 7) & 0xFFFFFFF8;
            size = ((w * h2) >> 5);
            dummy = size - qwc8 - qwc1 - 1;
        }
        break;
    }

    if (rest) {
        *(volatile u64 *)((u32)&sp->trxreg | 0x20000000) = (u64)(s32)sp->trxreg.RRW | ((u64)h2 << 32);
    }

    while (*D1_CHCR & 0x100) {
        if (timeout++ > 0x1000000) {
            PRINTF(D_002BC4A0);
            return -1;
        }
    }

    imr = func_0017BC20(func_0017BC00() | 0x200);
    *GS_CSR = 2;
    *D1_QWC = 7;
    SET_MADR(sp);
    *D1_CHCR = 0x101;

    while (*D1_CHCR & 0x100) {
        if (timeout++ > 0x1000000) {
            PRINTF(D_002BC4A0);
            return -1;
        }
    }

    while (!(*GS_CSR & 2)) {
        if (timeout++ > 0x1000000) {
            PRINTF(D_002BC4D8);
            *VIF1_FIFO = D_0028D920;
            return -1;
        }
    }

    *VIF1_STAT = 0x800000;
    *GS_BUSDIR = 1;

    if (qwc8) {
        *D1_QWC = qwc8;
        SET_MADR(dstaddr);
        *D1_CHCR = 0x100;
        while (*D1_CHCR & 0x100) {
            if (timeout++ > 0x1000000) {
                PRINTF(D_002BC508);
                *GS_CSR = 0x100;
                *GS_BUSDIR = 0;
                *GIF_CTRL = 1;
                *VIF1_FBRST = 1;
                return -1;
            }
        }
    }

    for (i = 0; i < qwc1; i++) {
        while (!(*VIF1_STAT & 0x1F000000)) {
            if (timeout++ > 0x1000000) {
                PRINTF(D_002BC548);
                *GS_CSR = 0x100;
                *GS_BUSDIR = 0;
                *GIF_CTRL = 1;
                *VIF1_FBRST = 1;
                return -1;
            }
        }
        dstaddr[qwc8 + i] = *VIF1_FIFO;
    }

    if (rest) {
        while (!(*VIF1_STAT & 0x1F000000)) {
            if (timeout++ > 0x1000000) {
                PRINTF(D_002BC548);
                *GS_CSR = 0x100;
                *GS_BUSDIR = 0;
                *GIF_CTRL = 1;
                *VIF1_FBRST = 1;
                return -1;
            }
        }
        buf.q = *VIF1_FIFO;
        for (i = 0; i < rest; i++) {
            ((u8 *)(dstaddr + (qwc8 + qwc1)))[i] = buf.b[i];
        }
        for (i = 0; i < dummy; i++) {
            while (!(*VIF1_STAT & 0x1F000000)) {
                if (timeout++ > 0x1000000) {
                    PRINTF(D_002BC548);
                    *GS_CSR = 0x100;
                    *GS_BUSDIR = 0;
                    *GIF_CTRL = 1;
                    *VIF1_FBRST = 1;
                    return -1;
                }
            }
            buf.q = *VIF1_FIFO;
        }
    }

    *VIF1_STAT = 0;
    *GS_BUSDIR = 0;
    func_0017BC20(imr);
    {
        __int128 code = D_0028D920;
        *GS_CSR = 2;
        *VIF1_FIFO = code;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_026", func_00186060);

void func_001860E8(s8 *arg0, s32 arg1) {
    s32 var_v0;
    s8 *var_a0;

    var_a0 = arg0;
    var_v0 = arg1 - 1;
    if (arg1 != 0) {
        do {
            *var_a0 = 0;
            var_v0 -= 1;
            var_a0 += 1;
        } while (var_v0 != -1);
    }
}

s32 func_00186120(s32 arg0) {
    if ((u32) arg0 < 0xAU) {
        return ((s32 *)&D_0028D930)[arg0];
    }
    return 0;
}

s32 func_00186148(s32 arg0) {
    s32 sp0[8];
    s32 prev;
    s32 i;
    volatile s32 *ch;

    prev = *(volatile s32 *)0x1000E000 & 1;
    for (i = 0; i < 10; i++) {
        if ((&D_0028D970)[i] != 0) {
            ch = (volatile s32 *)(&D_0028D930)[i];
            ch[0x20] = 0;
            ch[0] = 0;
            ch[0xC] = 0;
            ch[4] = 0;
            ch[0x14] = 0;
            ch[0x10] = 0;
        }
    }
    *(volatile s32 *)0x1000E010 = 0xFF1F;
    *(volatile s32 *)0x1000E010 &= 0xFF1F0000;
    func_001860E8((s8 *)sp0, 0x14);
    func_00186238(sp0);
    if (arg0 == 1) {
        *(volatile s32 *)0x1000E000 = *(volatile s32 *)0x1000E000 | 1;
    }
    return prev;
}

s32 func_00186228(s32 arg0) {
    s32 temp_v0;

    temp_v0 = D_0028D958;
    D_0028D958 = arg0;
    return temp_v0;
}

INCLUDE_ASM("asm/nonmatchings/main_026", func_00186238);

INCLUDE_ASM("asm/nonmatchings/main_026", func_00186410);

s32 func_00186448(u32 arg0) {
    s32 old = *(volatile s32 *)0x1000E060;
    if (arg0 != 0xFFFFFFFF) {
        *(volatile s32 *)0x1000E060 = arg0;
    }
    return old;
}

INCLUDE_ASM("asm/nonmatchings/main_026", func_00186470);

INCLUDE_ASM("asm/nonmatchings/main_026", func_00186548);

INCLUDE_ASM("asm/nonmatchings/main_026", func_00186630);

INCLUDE_ASM("asm/nonmatchings/main_026", func_00186718);

INCLUDE_ASM("asm/nonmatchings/main_026", func_001867E0);

INCLUDE_ASM("asm/nonmatchings/main_026", func_001868D0);

INCLUDE_ASM("asm/nonmatchings/main_026", func_001869C0);

INCLUDE_ASM("asm/nonmatchings/main_026", func_00186A88);

INCLUDE_ASM("asm/nonmatchings/main_026", func_00186B58);

s32 func_00186BA0(u32 *arg0, u32 arg1) {
    u32 temp_v0;

    temp_v0 = *arg0;
    *arg0 = arg1;
    return (temp_v0 >> 8) & 1;
}

INCLUDE_ASM("asm/nonmatchings/main_026", func_00186BB8);

INCLUDE_ASM("asm/nonmatchings/main_026", func_00186BD0);

s32 func_00186BE8(void) {
    s32 ret;

    ret = 0;
    switch (func_00186D18()) {
    case 4:
        __asm__ volatile(".set noreorder\n\tcfc2.ni $2, $vi28\n\tori $2, $2, 1\n\tctc2.ni $2, $vi28\n\t.set reorder" : : : "$2");
    case 0:
    case 3:
        ret = 1;
        break;
    case 1:
    case 2:
        break;
    }
    return ret;
}

s32 func_00186C48(void) {
    s32 temp_v0;
    s32 var_v0;

    var_v0 = 0;
    temp_v0 = func_00186D18();
    if (temp_v0 < 4) {
        if (temp_v0 > 0) {
            func_00186D58(func_00186D68());
            var_v0 = 1;
        }
    }
    return var_v0;
}

INCLUDE_ASM("asm/nonmatchings/main_026", func_00186C98);

INCLUDE_ASM("asm/nonmatchings/main_026", func_00186CC8);

INCLUDE_ASM("asm/nonmatchings/main_026", func_00186CF8);

INCLUDE_ASM("asm/nonmatchings/main_026", func_00186D08);

INCLUDE_ASM("asm/nonmatchings/main_026", func_00186D18);

INCLUDE_ASM("asm/nonmatchings/main_026", func_00186D58);

INCLUDE_ASM("asm/nonmatchings/main_026", func_00186D68);

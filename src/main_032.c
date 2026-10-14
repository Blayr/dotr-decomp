#include "common.h"

s32 func_00191C50(s32 arg0) {
    u8 *b_D_0028F300 = (u8 *)&D_0028F300;
    s32 temp_s0;

    if (func_00191608(0x22) == 0) {
        return 0;
    }
    (*(s32 *)b_D_0028F300) = arg0;
    func_0017E190(&D_0028F300, 4);
    if (func_0017EA80(&D_0028F708, 0x22, 0, &D_0028F300, 4, &D_0028EEC0, 4, 0, 0) < 0) {
        func_0017B900(D_0028DCEC);
        return 0;
    }
    temp_s0 = *(s32 *)((s32) &D_0028EEC0 | 0x20000000);
    func_0017B900(D_0028DCEC);
    return temp_s0;
}

INCLUDE_ASM("asm/nonmatchings/main_032", func_00191D18);

s32 func_00191EF8(void) {
    s32 temp_s0;

    if (func_00191608(3) == 0) {
        return -1;
    }
    if (func_0017EA80(&D_0028F708, 4, 0, 0, 0, &D_0028EEC0, 4, 0, 0) < 0) {
        func_0017B900(D_0028DCEC);
        return -1;
    }
    temp_s0 = *(s32 *)((s32) &D_0028EEC0 | 0x20000000);
    func_0017B900(D_0028DCEC);
    return temp_s0;
}

s32 func_00191F90(s32 arg0, s32 arg1, s32 arg2) {
    D_0028F730 = 0;
    return func_00192308(arg0, arg1, arg2, 5, &D_00315958);
}

s32 func_00191FC0(s32 arg0, s32 *arg1) {
    D_0028F730 = 1;
    return func_00192308(arg0, 0, 0, 1, arg1);
}

s32 func_00191FF8(s32 arg0) {

    return func_00192308(arg0, 0, 0, 9, &D_00315958);
}

s32 func_00192028(s32 arg0) {

    return func_00192308(arg0, 0, 0, 4, &D_00315958);
}

s32 func_00192058(void) {
    D_0028F730 = 0;
    return func_00192308(0, 0, 0, 3, &D_00315958);
}

INCLUDE_ASM("asm/nonmatchings/main_032", func_00192090);

s32 func_00192218(void) {
    D_0028F730 = 0;
    if (D_0028DCD0 > 0) {
        func_0017DA98(&D_002BCE58);
    }
    return func_00192308(0, 0, 0, 7, &D_00315958);
}

s32 func_00192268(void) {
    D_0028F730 = 1;
    if (D_0028DCD0 > 0) {
        func_0017DA98(&D_002BCE70);
    }
    return func_00192308(0, 0, 0, 8, &D_00315958);
}

s32 func_001922C0(void) {
    if (D_0028DCD0 > 0) {
        func_0017DA98(&D_002BCE88);
    }
    return func_00192308(0, 0, 0, 6, &D_00315958);
}

extern s32 D_0028DDC0;
extern s32 D_0028DD40;
extern s32 D_002BCEA0;
extern s32 D_002BCEB8;
extern s32 D_002BCED0;

typedef struct CdRead_00192308 {
    s32 lbn;
    s32 sectors;
    s32 buf;
    s32 unkC;
    u8 mode[4];
} CdRead_00192308;

s32 func_00192308(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 *arg4) {
    CdRead_00192308 *p;
    s32 *q;
    s32 r;

    p = (CdRead_00192308 *)&D_0028DDC0;
    if (func_001912F0(0xF) == 0) {
        return 0;
    }
    if (D_0028DCD0 > 0) {
        func_0017DA98(&D_002BCEA0);
    }
    p->lbn = arg0;
    p->sectors = arg1;
    p->buf = arg2;
    p->unkC = arg3;
    if (arg4 != NULL) {
        p->mode[0] = ((u8 *)arg4)[0];
        p->mode[1] = ((u8 *)arg4)[1];
        p->mode[2] = ((u8 *)arg4)[2];
    }
    if (D_0028DCD0 > 0) {
        func_0017DA98(&D_002BCEB8);
    }
    func_0017E190((s32 *)p, 0x14);
    q = &D_0028DD40;
    if (func_0017EA80(&D_0028EE90, 9, 0, (s32 *)p, 0x14, q, 4, 0, 0) < 0) {
        func_0017B900(D_0028DCE8);
        return 0;
    }
    if (D_0028DCD0 > 0) {
        func_0017DA98(&D_002BCED0);
    }
    r = *(s32 *)((u32)q | 0x20000000);
    func_0017B900(D_0028DCE8);
    return r;
}

INCLUDE_ASM("asm/nonmatchings/main_032", func_00192470);

INCLUDE_ASM("asm/nonmatchings/main_032", func_00192588);

INCLUDE_ASM("asm/nonmatchings/main_032", func_001926C8);

s32 func_00192768(void) {
    (*(s32 *)(&D_00315BC0)) = 0xF;
    if (func_0017EA80(&D_00315980, 1, 0, &D_00315BC0, 0x80, &D_00315BC0, 0x80, 0, 0) < 0) {
        return 0;
    }
    if ((*(s32 *)((u8 *)(&D_00315BC0) + 0xC)) == 1) {
        D_0028F748 = 0;
    }
    return (*(s32 *)((u8 *)(&D_00315BC0) + 0xC));
}

INCLUDE_ASM("asm/nonmatchings/main_032", func_001927E8);

INCLUDE_ASM("asm/nonmatchings/main_032", func_001929D0);

u8 *func_00192A88(s32 arg0, s32 arg1) {
    u8 *p;
    s32 i;

    p = ((PadSlot_00192A88 *)((u8 *)&D_003159D0 + arg1 * 0x1C + arg0 * 0x70))->buf;
    func_0017C1D8((u32)p, (u32)(p + 0x100));
    i = *(s32 *)(p + 0x58) < *(s32 *)(p + 0xD8);
    return p + i * 0x80;
}

INCLUDE_ASM("asm/nonmatchings/main_032", func_00192AE8);

INCLUDE_ASM("asm/nonmatchings/main_032", func_00192B38);

INCLUDE_ASM("asm/nonmatchings/main_032", func_00192BB8);

void func_00192C30(u32 arg0, s8 *arg1) {
    if (arg0 < 8U) {
        func_0019BDD8(arg1, (&D_0028F750)[arg0]);
        return;
    }
    *arg1 = (s8) D_002BD000;
}

INCLUDE_ASM("asm/nonmatchings/main_032", func_00192C68);

u8 func_00192CD0(s32 port, s32 slot) {
    if (D_003159D0[port][slot].open == 0) {
        return 0;
    }
    return func_00192A88(port, slot)[0x71];
}

void func_00192D20(u32 arg0, s8 *arg1) {
    if (arg0 < 4U) {
        func_0019BDD8(arg1, (&D_0028F770)[arg0]);
        return;
    }
    *arg1 = (s8) D_002BD000;
}

INCLUDE_ASM("asm/nonmatchings/main_032", func_00192D58);

INCLUDE_ASM("asm/nonmatchings/main_032", func_00192E78);

INCLUDE_ASM("asm/nonmatchings/main_032", func_00192F98);

s32 func_001930D0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 *b_D_00315BC0 = (u8 *)&D_00315BC0;

    (*(s32 *)(b_D_00315BC0 + 0xC)) = arg2;
    (*(s32 *)(b_D_00315BC0 + 0x10)) = arg3;
    (*(s32 *)(&D_00315BC0)) = 6;
    (*(s32 *)(b_D_00315BC0 + 4)) = arg0;
    (*(s32 *)(b_D_00315BC0 + 8)) = arg1;
    if (func_0017EA80(&D_00315980, 1, 0, &D_00315BC0, 0x80, &D_00315BC0, 0x80, 0, 0) < 0) {
        return 0;
    }
    if ((*(s32 *)(b_D_00315BC0 + 0x14)) == 1) {
        func_00192C68(arg0, arg1, 2);
    }
    return ((*(s32 *)(b_D_00315BC0 + 0x14)));
}

INCLUDE_ASM("asm/nonmatchings/main_032", func_00193188);

s32 func_00192C68(s32, s32, s32);

typedef struct CdRpcBuf_00193248 {
    s32 cmd;
    s32 arg0;
    s32 arg1;
    u8 data[8];
    s32 result;
} CdRpcBuf_00193248;

s32 func_00193248(s32 arg0, s32 arg1, u8 *arg2) {
    CdRpcBuf_00193248 *p;
    s32 i;

    p = (CdRpcBuf_00193248 *)&D_00315BC0;

    p->cmd = 8;
    p->arg0 = arg0;
    p->arg1 = arg1;
    for (i = 0; i < 6; i++) {
        p->data[i] = arg2[i];
    }
    if (func_0017EA80(&D_00315980, 1, 0, (s32 *)p, 0x80, (s32 *)p, 0x80, 0, 0) < 0) {
        return 0;
    }
    if (p->result == 1) {
        func_00192C68(arg0, arg1, 2);
    }
    return p->result;
}

INCLUDE_ASM("asm/nonmatchings/main_032", func_00193320);

s32 func_001933D8(s32 arg0, s32 arg1, s32 arg2) {
    u8 *b_D_00315BC0 = (u8 *)&D_00315BC0;
    s32 temp_v0;

    (*(s32 *)(b_D_00315BC0 + 0xC)) = arg2;
    (*(s32 *)(&D_00315BC0)) = 0xA;
    (*(s32 *)(b_D_00315BC0 + 4)) = arg0;
    (*(s32 *)(b_D_00315BC0 + 8)) = arg1;
    if (func_0017EA80(&D_00315980, 1, 0, &D_00315BC0, 0x80, &D_00315BC0, 0x80, 0, 0) < 0) {
        return 0;
    }
    if ((*(s32 *)(b_D_00315BC0 + 0x10)) == 1) {
        func_00192C68(arg0, arg1, 2);
    }
    return (*(s32 *)(b_D_00315BC0 + 0x10));
}

INCLUDE_ASM("asm/nonmatchings/main_032", func_00193488);

s32 func_001934E8(s32 port, s32 slot) {
    if (D_003159D0[port][slot].open == 0) {
        return 0;
    }
    return func_001933D8(port, slot, 0xFFF);
}

s32 func_00193540(s32 port, s32 slot) {
    if (D_003159D0[port][slot].open == 0) {
        return 0;
    }
    return func_001933D8(port, slot, 0);
}

INCLUDE_ASM("asm/nonmatchings/main_032", func_00193598);

s32 func_00193668(void) {
    (*(s32 *)(&D_00315BC0)) = 0xC;
    if (func_0017EA80(&D_00315980, 1, 0, &D_00315BC0, 0x80, &D_00315BC0, 0x80, 0, 0) < 0) {
        return 0;
    }
    return (*(s32 *)((u8 *)(&D_00315BC0) + 0xC));
}

s32 func_001936D0(s32 arg0) {
    (*(s32 *)(&D_00315BC0)) = 0xD;
    (*(s32 *)((u8 *)(&D_00315BC0) + 4)) = arg0;
    if (func_0017EA80(&D_00315980, 1, 0, &D_00315BC0, 0x80, &D_00315BC0, 0x80, 0, 0) < 0) {
        return 0;
    }
    return (*(s32 *)((u8 *)(&D_00315BC0) + 0xC));
}

s32 func_00193738(void) {
    (*(s32 *)(&D_00315BC0)) = 0x12;
    if (func_0017EA80(&D_00315980, 1, 0, &D_00315BC0, 0x80, &D_00315BC0, 0x80, 0, 0) < 0) {
        return 0;
    }
    return (*(s32 *)((u8 *)(&D_00315BC0) + 0xC));
}

s32 func_001937A0(s32 arg0) {
    (*(s32 *)(&D_00315BC0)) = 0x14;
    (*(s32 *)((u8 *)(&D_00315BC0) + 4)) = arg0;
    if (func_0017EA80(&D_00315980, 1, 0, &D_00315BC0, 0x80, &D_00315BC0, 0x80, 0, 0) < 0) {
        return 0;
    }
    return (*(s32 *)((u8 *)(&D_00315BC0) + 8));
}

extern s8 D_002BD038;
extern s8 D_002BD050;
extern s8 D_002BD078;
s32 func_0017E240(s32);

typedef struct McCd_00193808 {
    s32 unk0[9];
    s32 serve;
} McCd_00193808;

s32 func_00193808(void) {
    s32 sp0[8];
    s32 ret;
    s32 i;

    if (D_0028F794 < 0) {
        sp0[5] = 0;
        sp0[2] = 1;
        sp0[1] = 1;
        D_0028F794 = func_0017B8E0(sp0);
    }
    func_00194248(0, NULL, NULL);
    func_0017B920(D_0028F794);
    func_0017E240(0);
    while (1) {
        if (func_0017E8B0(&D_00315C40, 0x80000400, 0) < 0) {
            func_00199B50(&D_002BD038);
            while (1) {
            }
        }
        if ((*(McCd_00193808 *)&D_00315C40).serve != 0) {
            break;
        }
        i = 0x100000;
        while (--i != 0) {
        }
    }
    ret = func_0017EA80(&D_00315C40, 0xFE, 0, &D_00315CC0, 0x30, &D_00317200, 0xC, 0, 0);
    func_0017B900(D_0028F794);
    if (ret < 0) {
        (*(McCd_00193808 *)&D_00315C40).serve = 0;
        return ret - 0x64;
    }
    if ((&D_00317200)[1] < 0x20A) {
        func_00199B50(&D_002BD050);
        (*(McCd_00193808 *)&D_00315C40).serve = 0;
        return -0x78;
    }
    if ((&D_00317200)[2] < 0x20E) {
        func_00199B50(&D_002BD078);
        (*(McCd_00193808 *)&D_00315C40).serve = 0;
        return -0x79;
    }
    return D_00317200;
}

s32 func_001939C0(void) {
    if (D_0028F794 >= 0) {
        func_0017B8F0(D_0028F794);
        D_0028F794 = -1;
    }
    return 1;
}

s32 *func_00193A00(s32 **arg0, s32 **arg1) {
    *arg0 = &D_00317200;
    *arg1 = &D_0028F790;
    (*(s32 *)((u8 *)(&D_00317200) + 0x3C)) = (s32) D_0028F794;
    return &D_00315C40;
}

s32 func_00193A30(s32 arg0) {
    u8 *b_D_00315CC0;
    u8 *b_D_00315C40;
    s32 temp_v0;

    if (func_0017B930(D_0028F794) < 0) {
        return -0xC8;
    }
    b_D_00315C40 = (u8 *)&D_00315C40;
    if ((*(s32 *)(b_D_00315C40 + 0x24)) == 0) {
        func_0017B900(D_0028F794);
        return -0x64;
    }
    b_D_00315CC0 = (u8 *)&D_00315CC0;
    (*(s32 *)(b_D_00315CC0 + 0x14)) = arg0;
    temp_v0 = func_0017EA80((void *)b_D_00315C40, 0x14, 1, (void *)b_D_00315CC0, 0x30, &D_00317200, 4, 0, 0);
    if (temp_v0 == 0) {
        D_0028F790 = 0x14;
    } else {
        func_0017B900(D_0028F794);
    }
    return temp_v0;
}

s32 func_00193AE8(s32 arg0) {
    u8 *b_D_00315CC0;
    u8 *b_D_00315C40;
    s32 temp_v0;

    if (func_0017B930(D_0028F794) < 0) {
        return -0xC8;
    }
    b_D_00315C40 = (u8 *)&D_00315C40;
    if ((*(s32 *)(b_D_00315C40 + 0x24)) == 0) {
        func_0017B900(D_0028F794);
        return -0x64;
    }
    b_D_00315CC0 = (u8 *)&D_00315CC0;
    (*(s32 *)(b_D_00315CC0 + 4)) = arg0;
    temp_v0 = func_0017EA80((void *)b_D_00315C40, 0x15, 0, (void *)b_D_00315CC0, 0x30, &D_00317200, 4, 0, 0);
    if (temp_v0 != 0) {
        func_0017B900(D_0028F794);
        return temp_v0;
    }
    func_0017B900(D_0028F794);
    return D_00317200;
}

s32 func_00193BA8(s32 arg0, s32 arg1, s8 *arg2, s32 arg3) {
    u8 *b_D_00315D04;
    u8 *b_D_00315C40;
    s32 *temp_v1;
    s32 temp_v0;

    if (func_0017B930(D_0028F794) < 0) {
        return -0xC8;
    }
    b_D_00315C40 = (u8 *)&D_00315C40;
    if ((*(s32 *)(b_D_00315C40 + 0x24)) == 0) {
        func_0017B900(D_0028F794);
        return -0x64;
    }
    if ((arg2 == NULL) || (*arg2 == 0)) {
        func_0017B900(D_0028F794);
        return -0xD2;
    }
    b_D_00315D04 = (u8 *)&D_00315D04;
    func_0019C2B8((void *)b_D_00315D04, arg2, 0x3FFU);
    temp_v1 = (void *)b_D_00315D04 - 0x14;
    (*(s32 *)(b_D_00315D04 + -0x14)) = arg0;
    (*(s32 *)((u8 *)temp_v1 + 8)) = arg3;
    (*(s32 *)((u8 *)temp_v1 + 4)) = arg1;
    (*(s8 *)((u8 *)temp_v1 + 0x413)) = 0;
    temp_v0 = func_0017EA80((void *)b_D_00315C40, 2, 1, temp_v1, 0x414, &D_00317200, 4, 0, 0);
    if (temp_v0 == 0) {
        D_0028F790 = 2;
    } else {
        func_0017B900(D_0028F794);
    }
    return temp_v0;
}

s32 func_00193CE0(s32 arg0, s32 arg1, void *arg2) {
    s32 ret;

    ret = func_00193BA8(arg0, arg1, arg2, 0x40);
    if (ret == 0) {
        D_0028F790 = 0xB;
    }
    return ret;
}

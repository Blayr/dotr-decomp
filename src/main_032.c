#include "common.h"
#include "sce/libkernl.h"

s32 func_00191C50(s32 arg0) {
    u8 *b_D_0028F300 = (u8 *)&D_0028F300;
    s32 temp_s0;

    if (scmd_prechk(0x22) == 0) {
        return 0;
    }
    (*(s32 *)b_D_0028F300) = arg0;
    func_0017E190(&D_0028F300, 4);
    if (sceSifCallRpc(&D_0028F708, 0x22, 0, &D_0028F300, 4, &D_0028EEC0, 4, 0, 0) < 0) {
        SignalSema(D_0028DCEC);
        return 0;
    }
    temp_s0 = *(s32 *)((s32) &D_0028EEC0 | 0x20000000);
    SignalSema(D_0028DCEC);
    return temp_s0;
}

typedef struct {
    int lsn;
    int sectors;
    void *buf;
    unsigned char trycount;
    unsigned char spindlctrl;
    unsigned char datapattern;
    unsigned char pad;
    int *intr_data;
    int *cur_pos;
} CdReadCmd_00191D18;

typedef struct {
    unsigned char trycount;
    unsigned char spindlctrl;
    unsigned char datapattern;
    unsigned char pad;
} CdRMode_00191D18;

extern s32 D_0028DDC0;
extern int D_0028EDC0[];
extern int D_0028EE80[];
extern volatile int D_0028DCF4;
extern char D_002BCD98[];
extern char D_002BCDB0[];

#define mode_00191D18 ((CdRMode_00191D18 *)arg3)
#define scePrintf_00191D18 ((void (*)(const char *, ...))scePrintf)

/* sceCdRead: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

s32 func_00191D18(s32 lsn, s32 sectors, s32 buf, void *arg3) {
    CdReadCmd_00191D18 *sd = (CdReadCmd_00191D18 *)&D_0028DDC0;
    int size;

    if ((D_0028DCF4 & 1) == 0) {
        if (func_00191460() == 6) {
            return 0;
        }
    }
    if (ncmd_prechk(4) == 0) {
        return 0;
    }
    sd->lsn = lsn;
    sd->sectors = sectors;
    sd->buf = (void *)buf;
    sd->trycount = mode_00191D18->trycount;
    sd->spindlctrl = mode_00191D18->spindlctrl;
    sd->datapattern = mode_00191D18->datapattern;
    sd->intr_data = D_0028EDC0;
    sd->cur_pos = D_0028EE80;
    switch (mode_00191D18->datapattern) {
    case 1:
        size = sectors * 2328;
        break;
    case 2:
        size = sectors * 2340;
        break;
    case 0:
    default:
        size = sectors * 2048;
        break;
    }
    D_0028EE80[0] = 0;
    if ((D_0028DCF4 & 2) == 0) {
        func_0017E190((s32 *)buf, size);
    }
    func_0017E190(D_0028EDC0, 144);
    func_0017E190((s32 *)sd, 24);
    func_0017E190(D_0028EE80, 4);
    if (D_0028DCD0 > 0) {
        scePrintf_00191D18(D_002BCD98);
    }
    *(volatile s32 *)&D_0028DD14 = 1;
    D_0028DCF0 = 1;
    if (sceSifCallRpc(&D_0028EE90, 1, 1, (s32 *)sd, 24, 0, 0, (s32)cd_read_intr, (s32)D_0028EDC0) < 0) {
        *(volatile s32 *)&D_0028DD14 = 0;
        D_0028DCF0 = 0;
        ((s32 (*)(s32))SignalSema)(*(volatile s32 *)&D_0028DCE8);
        return 0;
    }
    if (D_0028DCD0 > 0) {
        scePrintf_00191D18(D_002BCDB0);
    }
    return 1;
}

#undef mode_00191D18
#undef scePrintf_00191D18

s32 func_00191EF8(void) {
    s32 temp_s0;

    if (scmd_prechk(3) == 0) {
        return -1;
    }
    if (sceSifCallRpc(&D_0028F708, 4, 0, 0, 0, &D_0028EEC0, 4, 0, 0) < 0) {
        SignalSema(D_0028DCEC);
        return -1;
    }
    temp_s0 = *(s32 *)((s32) &D_0028EEC0 | 0x20000000);
    SignalSema(D_0028DCEC);
    return temp_s0;
}

s32 sceCdStInit(s32 arg0, s32 arg1, s32 arg2) {
    D_0028F730 = 0;
    return sceCdStream(arg0, arg1, arg2, 5, &D_00315958);
}

s32 sceCdStStart(s32 arg0, s32 *arg1) {
    D_0028F730 = 1;
    return sceCdStream(arg0, 0, 0, 1, arg1);
}

s32 sceCdStSeekF(s32 arg0) {

    return sceCdStream(arg0, 0, 0, 9, &D_00315958);
}

s32 sceCdStSeek(s32 arg0) {

    return sceCdStream(arg0, 0, 0, 4, &D_00315958);
}

s32 sceCdStStop(void) {
    D_0028F730 = 0;
    return sceCdStream(0, 0, 0, 3, &D_00315958);
}

extern char D_002BCDC0[];
extern char D_002BCDF0[];
extern char D_002BCE38[];

#define scePrintf_00192090 ((void (*)(const char *, ...))scePrintf)

/* sceCdStRead: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

s32 sceCdStRead(s32 sectors, s32 buf, s32 mode, s32 *err) {
    int got;
    unsigned int r;
    unsigned int n;
    int e;
    int rerr;

    if (D_0028DCD0 > 0) {
        scePrintf_00192090(D_002BCDC0, sectors);
    }
    if (D_0028F730 == 0) {
        return 0;
    }
    rerr = 0;
    got = 0;
    func_0017E190((s32 *)buf, sectors << 11);
    if (mode != 0) {
        do {
            r = sceCdStream(0, sectors - got, buf + (got << 11), 2, &D_00315958);
            n = r & 0xFFFF;
            e = r >> 16;
            got += n;
            if (e != 0) {
                rerr = e;
                if (D_0028DCD0 > 0) {
                    scePrintf_00192090(D_002BCDF0, got, n, sectors, e);
                }
            } else if (n == 0) {
                sceCdDelayThread(8);
            }
        } while (got != sectors && (e == 0 || n != 0));
        if (D_0028DCD0 > 0) {
            scePrintf_00192090(D_002BCE38);
        }
        *err = rerr;
    } else {
        r = sceCdStream(0, sectors, buf, 2, &D_00315958);
        e = r >> 16;
        got = r & 0xFFFF;
        *err = e;
    }
    return got;
}

#undef scePrintf_00192090

s32 sceCdStPause(void) {
    D_0028F730 = 0;
    if (D_0028DCD0 > 0) {
        scePrintf(&D_002BCE58);
    }
    return sceCdStream(0, 0, 0, 7, &D_00315958);
}

s32 sceCdStResume(void) {
    D_0028F730 = 1;
    if (D_0028DCD0 > 0) {
        scePrintf(&D_002BCE70);
    }
    return sceCdStream(0, 0, 0, 8, &D_00315958);
}

s32 sceCdStStat(void) {
    if (D_0028DCD0 > 0) {
        scePrintf(&D_002BCE88);
    }
    return sceCdStream(0, 0, 0, 6, &D_00315958);
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

s32 sceCdStream(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 *arg4) {
    CdRead_00192308 *p;
    s32 *q;
    s32 r;

    p = (CdRead_00192308 *)&D_0028DDC0;
    if (ncmd_prechk(0xF) == 0) {
        return 0;
    }
    if (D_0028DCD0 > 0) {
        scePrintf(&D_002BCEA0);
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
        scePrintf(&D_002BCEB8);
    }
    func_0017E190((s32 *)p, 0x14);
    q = &D_0028DD40;
    if (sceSifCallRpc(&D_0028EE90, 9, 0, (s32 *)p, 0x14, q, 4, 0, 0) < 0) {
        SignalSema(D_0028DCE8);
        return 0;
    }
    if (D_0028DCD0 > 0) {
        scePrintf(&D_002BCED0);
    }
    r = *(s32 *)((u32)q | 0x20000000);
    SignalSema(D_0028DCE8);
    return r;
}

s32 _send_to_iop(s32 port, s32 slot) {
    s32 dma[64];
    u32 *buf;
    u32 addr;
    s32 id;
    u32 n;

    buf = (u32 *)D_003159D0[port][slot].unk4[0];
    if (D_003159D0[port][slot].unk4[2] != 0 && sceSifDmaStat(D_003159D0[port][slot].unk4[2]) >= 0) {
        if (D_0028F74C != 0) {
            func_00199B50(D_002BCEE0);
        }
        return 0;
    }
    n = buf[0] + 1;
    addr = D_003159D0[port][slot].unk4[1] + ((n & 1) << 5);
    buf[0] = n;
    SyncDCache((u32)buf, (u32)(buf + 8));
    dma[1] = addr;
    dma[0] = (s32)buf;
    dma[2] = 0x20;
    dma[3] = 0;
    id = sceSifSetDma(dma, 1);
    if (id == 0) {
        if (D_0028F74C != 0) {
            func_00199B50(D_002BCEE0);
        }
        return 0;
    }
    D_003159D0[port][slot].unk4[2] = id;
    return 1;
}

extern char D_002BCF28[];
extern char D_002BCF50[];

/* scePadInit: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

s32 scePadInit(s32 a0) {
    s32 ver;
    s32 major;
    s32 i;

    D_0028F748 = 1;
    while (1) {
        sceSifBindRpc(&D_00315980[0], 0x80000100, 0);
        if (D_00315980[0].serve != 0) {
            break;
        }
        for (i = 0x10000; i != -1; i--) {}
    }
    while (1) {
        sceSifBindRpc(&D_00315980[1], 0x80000101, 0);
        if (D_00315980[1].serve != 0) {
            break;
        }
        for (i = 0x10000; i != -1; i--) {}
    }
    ver = scePadGetModVersion();
    major = ver >> 8;
    if (major != 4) {
        if (D_0028F74C != 0) {
            ((s32 (*)(const char *, ...))func_00199B50)(D_002BCF28);
            ((s32 (*)(const char *, ...))func_00199B50)(D_002BCF50, 4, 0, major, ver & 0xFF);
        }
        return 0;
    }
    return scePadInit2(a0);
}

/* scePadInit2: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

s32 scePadInit2(s32 a0) {
    s32 ret;
    s32 i;

    for (i = 0; i < 4; i++) {
        D_003159D0[0][i].open = 0;
        D_003159D0[0][i].unk14[1] = 0;
        D_003159D0[0][i].unk14[0] = 0;
        D_003159D0[1][i].open = 0;
        D_003159D0[1][i].unk14[1] = 0;
        D_003159D0[1][i].unk14[0] = 0;
    }
    (&D_00315BC0)[0] = 0x10;
    (&D_00315BC0)[4] = 0;
    ret = sceSifCallRpc((s32 *)D_00315980, 1, 0, &D_00315BC0, 0x80, &D_00315BC0, 0x80, 0, 0);
    if (ret < 0) {
        return 0;
    }
    return (&D_00315BC0)[3];
}

s32 scePadEnd(void) {
    (*(s32 *)(&D_00315BC0)) = 0xF;
    if (sceSifCallRpc((s32 *)D_00315980, 1, 0, &D_00315BC0, 0x80, &D_00315BC0, 0x80, 0, 0) < 0) {
        return 0;
    }
    if ((*(s32 *)((u8 *)(&D_00315BC0) + 0xC)) == 1) {
        D_0028F748 = 0;
    }
    return (*(s32 *)((u8 *)(&D_00315BC0) + 0xC));
}

extern s32 D_00315AC0[2][4][8];
extern char D_002BCF78[];
extern char D_002BCFA8[];

/* scePadPortOpen: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

s32 scePadPortOpen(s32 port, s32 slot, void *addr) {
    s32 ret;
    s32 val;
    s32 i;
    char *p;
    s32 *q;

    if (((u32)addr & 0x3F) != 0) {
        if (D_0028F74C != 0) {
            ((s32 (*)(const char *, ...))func_00199B50)(D_002BCF78, addr);
        }
        return 0;
    }
    if (D_003159D0[port][slot].open == 1) {
        if (D_0028F74C != 0) {
            ((s32 (*)(const char *, ...))func_00199B50)(D_002BCFA8, port, slot);
        }
        return 0;
    }
    p = (char *)addr;
    for (i = 0; i < 2; i++) {
        *(s32 *)(p + 0x58) = 0;
        p[0x70] = 5;
        p[0x71] = 2;
        p[0x67] = 0;
        func_00198948(p, 0xFF, 0x20);
        *(s32 *)(p + 0x60) = 0;
        p += 0x80;
    }
    (&D_00315BC0)[0] = 1;
    (&D_00315BC0)[1] = port;
    (&D_00315BC0)[2] = slot;
    (&D_00315BC0)[4] = (s32)addr;
    ret = sceSifCallRpc((s32 *)D_00315980, 1, 0, &D_00315BC0, 0x80, &D_00315BC0, 0x80, 0, 0);
    if (ret < 0) {
        return 0;
    }
    q = D_00315AC0[port][slot];
    val = (s32)*(void **)&(&D_00315BC0)[5];
    D_003159D0[port][slot].open = 1;
    *(s32 **)&D_003159D0[port][slot].unk4[1] = (s32 *)val;
    *(void **)&D_003159D0[port][slot].buf = addr;
    *(s32 **)&D_003159D0[port][slot].unk4[0] = q;
    q[0] = 0;
    D_003159D0[port][slot].unk4[2] = 0;
    return (&D_00315BC0)[3];
}

s32 scePadPortClose(s32 port, s32 slot) {
    u8 *b;

    if (D_003159D0[port][slot].open == 0) {
        return 0;
    }
    b = (u8 *)&D_00315BC0;
    *(s32 *)&D_00315BC0 = 0xE;
    *(s32 *)(b + 4) = port;
    *(s32 *)(b + 8) = slot;
    *(s32 *)(b + 0x10) = 1;
    if (sceSifCallRpc((s32 *)D_00315980, 1, 0, &D_00315BC0, 0x80, &D_00315BC0, 0x80, 0, 0) < 0) {
        return 0;
    }
    D_003159D0[port][slot].open = 0;
    return *(s32 *)(b + 0xC);
}

u8 *scePadGetDmaStr(s32 arg0, s32 arg1) {
    u8 *p;
    s32 i;

    p = ((PadSlot_00192A88 *)((u8 *)&D_003159D0 + arg1 * 0x1C + arg0 * 0x70))->buf;
    SyncDCache((u32)p, (u32)(p + 0x100));
    i = *(s32 *)(p + 0x58) < *(s32 *)(p + 0xD8);
    return p + i * 0x80;
}

/* scePadGetFrameCount: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

s32 scePadGetFrameCount(s32 port, s32 slot) {
    s32 ret = 0;

    if (D_003159D0[port][slot].open == 0) {
        return ret;
    }
    return *(s32 *)(scePadGetDmaStr(port, slot) + 0x58);
}

s32 scePadRead(s32 port, s32 slot, u8 *data) {
    u8 *p;

    if (D_003159D0[port][slot].open == 0) {
        return 0;
    }
    p = scePadGetDmaStr(port, slot);
    func_00198790(data, p, *(s32 *)(p + 0x60));
    return *(s32 *)(p + 0x60);
}

s32 scePadGetState(s32 port, s32 slot) {
    u8 *p;

    if (D_003159D0[port][slot].open == 0) {
        return 0x63;
    }
    p = scePadGetDmaStr(port, slot);
    if (p[0x70] == 6) {
        if (p[0x71] == 2) {
            return 5;
        }
    }
    return p[0x70];
}

void scePadStateIntToStr(u32 arg0, s8 *arg1) {
    if (arg0 < 8U) {
        func_0019BDD8(arg1, (&D_0028F750)[arg0]);
        return;
    }
    *arg1 = (s8) D_002BD000;
}

s32 scePadSetReqState(s32 port, s32 slot, s32 state) {
    if (D_003159D0[port][slot].open == 0) {
        return 0;
    }
    scePadGetDmaStr(port, slot)[0x71] = state;
    return 1;
}

u8 scePadGetReqState(s32 port, s32 slot) {
    if (D_003159D0[port][slot].open == 0) {
        return 0;
    }
    return scePadGetDmaStr(port, slot)[0x71];
}

void scePadReqIntToStr(u32 arg0, s8 *arg1) {
    if (arg0 < 4U) {
        func_0019BDD8(arg1, (&D_0028F770)[arg0]);
        return;
    }
    *arg1 = (s8) D_002BD000;
}

typedef struct PadInfo_00192D58 {
    u8 unk0[0x30];
    u8 mode[4][4];
    u8 act[8][4];
} PadInfo_00192D58;

s32 scePadInfoAct(s32 port, s32 slot, s32 term, s32 offs) {
    u8 *p;

    if (D_003159D0[port][slot].open == 0) {
        return 0;
    }
    p = scePadGetDmaStr(port, slot);
    if (p[0x72] != 1) {
        return 0;
    }
    if (p[0x64] < 2) {
        return 0;
    }
    if (term >= p[0x6A]) {
        return 0;
    }
    if (term == -1) {
        return p[0x6A];
    }
    switch (offs) {
    case 1:
        return ((PadInfo_00192D58 *)p)->mode[term][0];
    case 2:
        return ((PadInfo_00192D58 *)p)->mode[term][1];
    case 3:
        return ((PadInfo_00192D58 *)p)->mode[term][2];
    case 4:
        return ((PadInfo_00192D58 *)p)->mode[term][3];
    }
    return 0;
}

typedef struct PadInfo_00192E78 {
    u8 unk0[0x30];
    u8 mode[4][4];
    u8 act[8][4];
} PadInfo_00192E78;

s32 scePadInfoComb(s32 port, s32 slot, s32 actno, s32 term) {
    u8 *p;

    if (D_003159D0[port][slot].open == 0) {
        return 0;
    }
    p = scePadGetDmaStr(port, slot);
    if (p[0x72] != 1) {
        return 0;
    }
    if (p[0x64] < 2) {
        return 0;
    }
    if (actno == -1) {
        return p[0x6B];
    }
    if (actno >= p[0x6B]) {
        return 0;
    }
    switch (term) {
    case -1:
        return ((PadInfo_00192E78 *)p)->act[actno][0];
    case 0:
        return ((PadInfo_00192E78 *)p)->act[actno][1];
    case 1:
        return ((PadInfo_00192E78 *)p)->act[actno][2];
    case 2:
        return ((PadInfo_00192E78 *)p)->act[actno][3];
    }
    return 0;
}

typedef struct PadMode_00192F98 {
    u8 unk0[0x50];
    u16 table[12];
} PadMode_00192F98;

s32 scePadInfoMode(s32 port, s32 slot, s32 term, s32 offs) {
    u8 *p;

    if (D_003159D0[port][slot].open == 0) {
        return 0;
    }
    p = scePadGetDmaStr(port, slot);
    if (p[0x72] != 1) {
        return 0;
    }
    if (p[0x71] == 2) {
        return 0;
    }
    switch (term) {
    case 1:
        if (p[0x65] == 0xF3) {
            return 0;
        }
        return p[0x65] >> 4;
    case 2:
        if (p[0x64] == 1) {
            return 0;
        }
        return ((PadMode_00192F98 *)p)->table[p[0x69]];
    case 3:
        if (p[0x64] == 1) {
            return 0;
        }
        return p[0x69];
    case 4:
        if (p[0x64] == 1) {
            return 0;
        }
        if (offs == -1) {
            return p[0x68];
        }
        if (offs >= p[0x68]) {
            return 0;
        }
        return ((PadMode_00192F98 *)p)->table[offs];
    }
    return 0;
}

s32 scePadSetMainMode(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 *b_D_00315BC0 = (u8 *)&D_00315BC0;

    (*(s32 *)(b_D_00315BC0 + 0xC)) = arg2;
    (*(s32 *)(b_D_00315BC0 + 0x10)) = arg3;
    (*(s32 *)(&D_00315BC0)) = 6;
    (*(s32 *)(b_D_00315BC0 + 4)) = arg0;
    (*(s32 *)(b_D_00315BC0 + 8)) = arg1;
    if (sceSifCallRpc((s32 *)D_00315980, 1, 0, &D_00315BC0, 0x80, &D_00315BC0, 0x80, 0, 0) < 0) {
        return 0;
    }
    if ((*(s32 *)(b_D_00315BC0 + 0x14)) == 1) {
        scePadSetReqState(arg0, arg1, 2);
    }
    return ((*(s32 *)(b_D_00315BC0 + 0x14)));
}

s32 scePadSetActDirect(s32 port, s32 slot, u8 *data) {
    u8 *p;
    u8 *q;
    s32 i;
    s32 ret;

    if (scePadGetDmaStr(port, slot)[0x72] != 1) {
        return 0;
    }
    p = (u8 *)D_003159D0[port][slot].unk4[0];
    q = p + 0xC;
    for (i = 0; i < 6; i++) {
        q[i] = data[i];
    }
    ret = 1;
    *(s32 *)(p + 4) = 1;
    *(s32 *)(p + 8) = 6;
    if (_send_to_iop(port, slot) != 1) {
        ret = 0;
    }
    return ret;
}


typedef struct CdRpcBuf_00193248 {
    s32 cmd;
    s32 arg0;
    s32 arg1;
    u8 data[8];
    s32 result;
} CdRpcBuf_00193248;

s32 scePadSetActAlign(s32 arg0, s32 arg1, u8 *arg2) {
    CdRpcBuf_00193248 *p;
    s32 i;

    p = (CdRpcBuf_00193248 *)&D_00315BC0;

    p->cmd = 8;
    p->arg0 = arg0;
    p->arg1 = arg1;
    for (i = 0; i < 6; i++) {
        p->data[i] = arg2[i];
    }
    if (sceSifCallRpc((s32 *)D_00315980, 1, 0, (s32 *)p, 0x80, (s32 *)p, 0x80, 0, 0) < 0) {
        return 0;
    }
    if (p->result == 1) {
        scePadSetReqState(arg0, arg1, 2);
    }
    return p->result;
}

s32 scePadGetButtonMask(s32 port, s32 slot) {
    u8 *p;

    if (D_003159D0[port][slot].open == 0) {
        return 0;
    }
    p = scePadGetDmaStr(port, slot);
    if (p[0x72] != 1) {
        return 0;
    }
    if (p[0x64] < 2) {
        return 0;
    }
    if (p[0x66] < 2) {
        return 0;
    }
    return p[0x79] + ((long)p[0x7A] << 8) + ((long)p[0x7B] << 16) + ((long)p[0x7C] << 24);
}

s32 scePadSetButtonInfo(s32 arg0, s32 arg1, s32 arg2) {
    u8 *b_D_00315BC0 = (u8 *)&D_00315BC0;
    s32 temp_v0;

    (*(s32 *)(b_D_00315BC0 + 0xC)) = arg2;
    (*(s32 *)(&D_00315BC0)) = 0xA;
    (*(s32 *)(b_D_00315BC0 + 4)) = arg0;
    (*(s32 *)(b_D_00315BC0 + 8)) = arg1;
    if (sceSifCallRpc((s32 *)D_00315980, 1, 0, &D_00315BC0, 0x80, &D_00315BC0, 0x80, 0, 0) < 0) {
        return 0;
    }
    if ((*(s32 *)(b_D_00315BC0 + 0x10)) == 1) {
        scePadSetReqState(arg0, arg1, 2);
    }
    return (*(s32 *)(b_D_00315BC0 + 0x10));
}

/* scePadInfoPressMode: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

s32 scePadInfoPressMode(s32 port, s32 slot) {
    if (D_003159D0[port][slot].open == 0) {
        return 0;
    }
    return scePadGetButtonMask(port, slot) == 0x3FFFF;
}

s32 scePadEnterPressMode(s32 port, s32 slot) {
    if (D_003159D0[port][slot].open == 0) {
        return 0;
    }
    return scePadSetButtonInfo(port, slot, 0xFFF);
}

s32 scePadExitPressMode(s32 port, s32 slot) {
    if (D_003159D0[port][slot].open == 0) {
        return 0;
    }
    return scePadSetButtonInfo(port, slot, 0);
}

s32 scePadSetVrefParam(s32 port, s32 slot, u8 *data) {
    u8 *b = (u8 *)&D_00315BC0;

    *(s32 *)&D_00315BC0 = 0xB;
    *(s32 *)(b + 4) = port;
    *(s32 *)(b + 8) = slot;
    __builtin_memcpy(b + 0xC, data, 12);
    if (sceSifCallRpc((s32 *)D_00315980, 1, 0, &D_00315BC0, 0x80, &D_00315BC0, 0x80, 0, 0) < 0) {
        return 0;
    }
    if (*(s32 *)(b + 0x1C) == 1) {
        scePadSetReqState(port, slot, 2);
    }
    return *(s32 *)(b + 0x1C);
}

s32 scePadGetPortMax(void) {
    (*(s32 *)(&D_00315BC0)) = 0xC;
    if (sceSifCallRpc((s32 *)D_00315980, 1, 0, &D_00315BC0, 0x80, &D_00315BC0, 0x80, 0, 0) < 0) {
        return 0;
    }
    return (*(s32 *)((u8 *)(&D_00315BC0) + 0xC));
}

s32 scePadGetSlotMax(s32 arg0) {
    (*(s32 *)(&D_00315BC0)) = 0xD;
    (*(s32 *)((u8 *)(&D_00315BC0) + 4)) = arg0;
    if (sceSifCallRpc((s32 *)D_00315980, 1, 0, &D_00315BC0, 0x80, &D_00315BC0, 0x80, 0, 0) < 0) {
        return 0;
    }
    return (*(s32 *)((u8 *)(&D_00315BC0) + 0xC));
}

s32 scePadGetModVersion(void) {
    (*(s32 *)(&D_00315BC0)) = 0x12;
    if (sceSifCallRpc((s32 *)D_00315980, 1, 0, &D_00315BC0, 0x80, &D_00315BC0, 0x80, 0, 0) < 0) {
        return 0;
    }
    return (*(s32 *)((u8 *)(&D_00315BC0) + 0xC));
}

s32 scePadSetWarningLevel(s32 arg0) {
    (*(s32 *)(&D_00315BC0)) = 0x14;
    (*(s32 *)((u8 *)(&D_00315BC0) + 4)) = arg0;
    if (sceSifCallRpc((s32 *)D_00315980, 1, 0, &D_00315BC0, 0x80, &D_00315BC0, 0x80, 0, 0) < 0) {
        return 0;
    }
    return (*(s32 *)((u8 *)(&D_00315BC0) + 8));
}

extern s8 D_002BD038;
extern s8 D_002BD050;
extern s8 D_002BD078;

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
        D_0028F794 = CreateSema(sp0);
    }
    func_00194248(0, NULL, NULL);
    WaitSema(D_0028F794);
    func_0017E240(0);
    while (1) {
        if (sceSifBindRpc(&D_00315C40, 0x80000400, 0) < 0) {
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
    ret = sceSifCallRpc(&D_00315C40, 0xFE, 0, &D_00315CC0, 0x30, &D_00317200, 0xC, 0, 0);
    SignalSema(D_0028F794);
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
        DeleteSema(D_0028F794);
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

    if (PollSema(D_0028F794) < 0) {
        return -0xC8;
    }
    b_D_00315C40 = (u8 *)&D_00315C40;
    if ((*(s32 *)(b_D_00315C40 + 0x24)) == 0) {
        SignalSema(D_0028F794);
        return -0x64;
    }
    b_D_00315CC0 = (u8 *)&D_00315CC0;
    (*(s32 *)(b_D_00315CC0 + 0x14)) = arg0;
    temp_v0 = sceSifCallRpc((void *)b_D_00315C40, 0x14, 1, (void *)b_D_00315CC0, 0x30, &D_00317200, 4, 0, 0);
    if (temp_v0 == 0) {
        D_0028F790 = 0x14;
    } else {
        SignalSema(D_0028F794);
    }
    return temp_v0;
}

s32 func_00193AE8(s32 arg0) {
    u8 *b_D_00315CC0;
    u8 *b_D_00315C40;
    s32 temp_v0;

    if (PollSema(D_0028F794) < 0) {
        return -0xC8;
    }
    b_D_00315C40 = (u8 *)&D_00315C40;
    if ((*(s32 *)(b_D_00315C40 + 0x24)) == 0) {
        SignalSema(D_0028F794);
        return -0x64;
    }
    b_D_00315CC0 = (u8 *)&D_00315CC0;
    (*(s32 *)(b_D_00315CC0 + 4)) = arg0;
    temp_v0 = sceSifCallRpc((void *)b_D_00315C40, 0x15, 0, (void *)b_D_00315CC0, 0x30, &D_00317200, 4, 0, 0);
    if (temp_v0 != 0) {
        SignalSema(D_0028F794);
        return temp_v0;
    }
    SignalSema(D_0028F794);
    return D_00317200;
}

s32 func_00193BA8(s32 arg0, s32 arg1, s8 *arg2, s32 arg3) {
    u8 *b_D_00315D04;
    u8 *b_D_00315C40;
    s32 *temp_v1;
    s32 temp_v0;

    if (PollSema(D_0028F794) < 0) {
        return -0xC8;
    }
    b_D_00315C40 = (u8 *)&D_00315C40;
    if ((*(s32 *)(b_D_00315C40 + 0x24)) == 0) {
        SignalSema(D_0028F794);
        return -0x64;
    }
    if ((arg2 == NULL) || (*arg2 == 0)) {
        SignalSema(D_0028F794);
        return -0xD2;
    }
    b_D_00315D04 = (u8 *)&D_00315D04;
    func_0019C2B8((void *)b_D_00315D04, arg2, 0x3FFU);
    temp_v1 = (void *)b_D_00315D04 - 0x14;
    (*(s32 *)(b_D_00315D04 + -0x14)) = arg0;
    (*(s32 *)((u8 *)temp_v1 + 8)) = arg3;
    (*(s32 *)((u8 *)temp_v1 + 4)) = arg1;
    (*(s8 *)((u8 *)temp_v1 + 0x413)) = 0;
    temp_v0 = sceSifCallRpc((void *)b_D_00315C40, 2, 1, temp_v1, 0x414, &D_00317200, 4, 0, 0);
    if (temp_v0 == 0) {
        D_0028F790 = 2;
    } else {
        SignalSema(D_0028F794);
    }
    return temp_v0;
}

s32 sceMcMkdir(s32 arg0, s32 arg1, void *arg2) {
    s32 ret;

    ret = func_00193BA8(arg0, arg1, arg2, 0x40);
    if (ret == 0) {
        D_0028F790 = 0xB;
    }
    return ret;
}

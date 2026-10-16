#include "common.h"

void _clearOnce(void *arg0) {
    u8 *spr;

    spr = (u8 *)0x70000000;
    _ipuSetMPEG1(1);
    *(u8 **)((u8 *)arg0 + 0x590) = spr;
    *(u8 **)((u8 *)arg0 + 0x594) = spr + 0x1800;
    *(u8 **)((u8 *)arg0 + 0x6D0) = spr + 0x1B00;
    *(u8 **)((u8 *)arg0 + 0x6D4) = spr + 0x3300;
    *(s32 *)((u8 *)arg0 + 0x810) = 0;
}

void _clearEach(void *arg0) {
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
    sceIpuSync(0, 0);
}

void _ErrMessage(s32 arg0) {
    func_00199B50(&D_002BCA98, arg0);
}

void _Error1(s32 arg0, void *arg1, s32 arg2) {
    s32 sp0[64];
    func_0019B648(sp0, arg1, arg2);
    _Error(arg0, sp0);
}

void _Error(s32 arg0, void *arg1) {
    s32 sp0[4];
    s32 temp_v1;

    temp_v1 = (*(s32 *)((u8 *)arg0 + 0x858));
    if ((temp_v1 != 0) && (arg0 != 0) && ((*(s32 *)((u8 *)arg0 + 0xC)) != 0)) {
        sp0[0] = 0;
        sp0[1] = arg1;
        _dispatchMpegCallback(temp_v1, sp0);
        return;
    }
    _ErrMessage((s32) arg1);
}

void _sendDataToIPU(s32 buf, u32 data, s32 size) {
    u64 *tag;
    u64 *t;
    s32 n;
    s32 id;
    u64 addr;

    tag = (u64 *)(((u32)(buf + 0x88F) >> 4) << 4);
    t = tag;
    while (size > 0) {
        n = (size > 0xFFF40) ? 0xFFF40 : size;
        addr = data & 0x0FFFFFFF;
        size -= n;
        id = 0;
        if (size != 0) {
            id = 3;
        }
        *t = (addr << 32) | ((u64)id << 28) | (u32)((n + 15) / 16);
        __asm__ volatile("sync");
        data += n;
        t += 2;
    }
    FlushCache(0);
    func_001843E0();
    *(volatile u32 *)0x1000B430 = (u32)tag & 0x0FFFFFFF;
    *(volatile u32 *)0x1000B420 = 0;
    *(volatile u32 *)0x1000B400 = 0x105;
    func_00184428();
}

s32 _RefImageInit(void *arg0, s32 arg1, s32 arg2) {
    (*(s32 *)((u8 *)arg0 + 4)) = arg1;
    (*(s32 *)((u8 *)arg0 + 0xC)) = (s32) (arg1 >> 4);
    (*(s32 *)((u8 *)arg0 + 8)) = arg2;
    (*(s32 *)((u8 *)arg0 + 0x10)) = (s32) (arg2 >> 4);
    return 1;
}

void _sequenceHeader(void *arg0) {
    u32 v;

    (*(s32 *)((u8 *)arg0 + 0xD4)) = 0;
    v = func_0018BA48(arg0, 0x20);
    (*(s32 *)((u8 *)arg0 + 0x124)) = v >> 20;
    (*(s32 *)((u8 *)arg0 + 0x128)) = (v >> 8) & 0xFFF;
    if ((*(s32 *)((u8 *)arg0 + 0x128)) > 0xAF0) {
        _Error((s32)arg0, &D_002BCAA8);
    }
    v = func_0018BA48(arg0, 0x1E);
    (*(s32 *)((u8 *)arg0 + 0x134)) = v >> 12;
    (*(s32 *)((u8 *)arg0 + 0x138)) = (v >> 1) & 0x3FF;
    if (((*(s32 *)((u8 *)arg0 + 0x840)) = func_0018BA48(arg0, 1)) != 0) {
        func_0018B580(arg0);
        func_0018B550(arg0, 0x50000000);
        func_0018B580(arg0);
    } else {
        _setDefaultQM(arg0, 0x50000000, (s32)&D_0028DB80);
    }
    if (((*(s32 *)((u8 *)arg0 + 0x844)) = func_0018BA48(arg0, 1)) != 0) {
        func_0018B580(arg0);
        func_0018B550(arg0, 0x58000000);
        func_0018B580(arg0);
    } else {
        _setDefaultQM(arg0, 0x58000000, (s32)&D_0028DBC0);
    }
    func_0018BE58(arg0);
    _initSeq(*(void **)((u8 *)arg0 + 0x858));
}

void _initSeq(void *arg0) {
    u8 *d;
    s32 dec;
    s32 mbh;
    s32 w;
    s32 h;
    u32 size;
    u8 *top0;
    u8 *top1;
    u8 *top2;
    u8 *bot0;
    u8 *bot1;
    u8 *bot2;
    u8 *b2;
    u8 *frame0;
    u8 *frame1;
    u8 *frame2;
    u8 *f0;
    u8 *f1;
    u8 *f2;

    d = *(u8 **)((u8 *)arg0 + 0x40);
    dec = *(s32 *)(d + 0x848);
    if (dec == 0) {
        *(s32 *)(d + 0x13C) = 1;
        *(s32 *)(d + 0x140) = 1;
        *(s32 *)(d + 0x188) = 1;
        *(s32 *)(d + 0x174) = 3;
        *(s32 *)(d + 0x17C) = 1;
        *(s32 *)(d + 0x144) = 5;
    }
    *(s32 *)(d + 0x12C) = (*(s32 *)(d + 0x124) + 0xF) >> 4;
    if (dec != 0 && *(s32 *)(d + 0x13C) == 0) {
        mbh = ((*(s32 *)(d + 0x128) + 0x1F) >> 5) * 2;
    } else {
        mbh = (*(s32 *)(d + 0x128) + 0xF) >> 4;
    }
    *(s32 *)(d + 0x130) = mbh;
    h = mbh * 16;
    w = *(s32 *)(d + 0x12C) * 16;
    if (w != *(s32 *)arg0 || h != *(s32 *)((u8 *)arg0 + 4)) {
        b2 = d + 0x528;
        do { } while (0); /* empty loop: a scheduling barrier, the bot2 address comes first */
        *(s32 *)((u8 *)arg0 + 4) = h;
        *(s32 *)arg0 = w;
        size = (u32)(w * 0x180 * h) >> 8;
        f0 = d + 0x1E8;
        f1 = d + 0x250;
        f2 = d + 0x2B8;
        _alalcFree(d + 0x108);
        bot2 = b2;
        frame0 = f0;
        frame1 = f1;
        frame2 = f2;
        b2 = f0 = f1 = f2 = d; /* the early copies are done with */
        *(s32 *)(d + 0xFC) = _alalcAlloc((s32)d, d + 0x108, size, 0x40);
        *(s32 *)(d + 0x100) = _alalcAlloc((s32)d, d + 0x108, size, 0x40);
        *(s32 *)(d + 0x104) = _alalcAlloc((s32)d, d + 0x108, size, 0x40);
        top0 = d + 0x320;
        top1 = d + 0x388;
        top2 = d + 0x3F0;
        bot0 = d + 0x458;
        bot1 = d + 0x4C0;
        _initRefImages(frame0, frame1, frame2, top0, top1, top2, bot0, bot1, bot2,
                       *(s32 *)(d + 0xFC), *(s32 *)(d + 0x100), *(s32 *)(d + 0x104), w, h);
        _RefImageInit(frame0, w, h);
        _RefImageInit(frame1, w, h);
        _RefImageInit(frame2, w, h);
        _RefImageInit(top0, w, h >> 1);
        _RefImageInit(top1, w, h >> 1);
        _RefImageInit(top2, w, h >> 1);
        _RefImageInit(bot0, w, h >> 1);
        _RefImageInit(bot1, w, h >> 1);
        _RefImageInit(bot2, w, h >> 1);
    }
}

static inline int uncachedAddr_0018FCE8(int addr) {
    return (addr & 0x0FFFFFFF) | 0x20000000;
}

/* _initRefImages (this SDK passes the picture size as two more arguments): adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

void _initRefImages(int *frame0, int *frame1, int *frame2, int *top0, int *top1, int *top2, int *bot0, int *bot1,
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

void _setDefaultQM(void *arg0, s32 arg1, s32 arg2) {
    s32 sp0[8];
    sp0[0] = /* extra? */ 2;
    _dispatchMpegCallback((*(s32 *)((u8 *)arg0 + 0x858)), sp0);
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
    _dispatchMpegCallback((*(s32 *)((u8 *)arg0 + 0x858)), sp0);
}

void _sequenceExtension(void *arg0) {
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
    _ipuSetMPEG1(0);
    v = func_0018BA48(arg0, 28);
    brext = (v >> 1) & 0xFFF;
    vext = (v >> 13) & 3;
    hext = (v >> 15) & 3;
    chroma = (v >> 17) & 3;
    *(s32 *)(d + 0x140) = chroma;
    if (chroma != 1) {
        _Error((s32)arg0, &D_002BCAC0);
    }
    *(s32 *)(d + 0x13C) = (v >> 19) & 1;
    prof = v >> 20;
    vbvext = (u32)func_0018BA48(arg0, 16) >> 8;
    if (prof != 0x48 && prof != 0x58 && prof != 0x44) {
        _Error((s32)arg0, &D_002BCAE8);
    }
    *(s32 *)(d + 0x124) = (hext << 12) | (*(s32 *)(d + 0x124) & 0xFFF);
    *(s32 *)(d + 0x128) = (vext << 12) | (*(s32 *)(d + 0x128) & 0xFFF);
    *(s32 *)(d + 0x134) += brext << 18;
    *(s32 *)(d + 0x138) += vbvext << 10;
}

void _sequenceDisplayExtension(void *arg0, s32 arg1) {
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

void _sequenceScalableExtension(s32 arg0) {
    _Error(arg0, D_002BCB08);
}

void _unknown_extension(s32 arg0) {
    _Error(arg0, D_002BCB38);
}

void _pictureSpatialScalableExtension(s32 arg0) {
    _Error(arg0, D_002BCB50);
}

void _pictureTemporalScalableExtension(s32 arg0) {
    _Error(arg0, D_002BCB88);
}

void _defStopDMA(void *arg0) {
    func_00190190(*(s32 *)((u8 *)arg0 + 0x40) + 0x4C);
}

void _defRestartDMA(void *arg0) {
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

s32 sceIpuSync(s32 arg0, s32 arg1) {
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
        if (sceSifBindRpc(&D_00315680, 0x80000701, 0) < 0) {
            func_00199B50(&D_002BCBC0);
            return -1;
        }
        for (i = 10000; i != -1; i--) {
        }
        if ((*(CdCd_001906D0 *)&D_00315680).serve != 0) {
            break;
        }
    }
    FlushCache(0);
    return 0;
}

s32 func_00190778(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_v0;

    if ((arg3 == 0) || ((*(s32 *)(&D_00315500)) = arg0, (*(s32 *)((u8 *)(&D_00315500) + 4)) = arg1, (*(s32 *)((u8 *)(&D_00315500) + 8)) = arg2, (*(s32 *)((u8 *)(&D_00315500) + 0xC)) = 0, temp_v0 = sceSifSetDma(&D_00315500, 1), (temp_v0 == 0))) {
        return -1;
    }
    if (arg3 == 1) {
        do {

        } while (sceSifDmaStat(temp_v0) >= 0);
    }
    return 0;
}

s32 func_00190800(s32 arg0) {
    s32 temp_v0;

    temp_v0 = D_0028DC90;
    D_0028DC90 = arg0;
    return temp_v0;
}

s32 func_00190810(s32 arg, ...) {
    char *ap;
    s32 command;
    s32 i;
    s32 mode;
    s32 cb;
    s32 ret;
    s32 unused[4];
    s32 *p;

    cb = 0;
    ap = (char *)__builtin_next_arg(arg) - (8 - __builtin_args_info(0)) * 8;
    D_00315640[0] = (s32)D_00315640;
    command = *(s32 *)((ap += 8) - 8);
    p = &D_00315640[1];
    for (i = 0; i < 6; i++) {
        *p++ = *(s32 *)((ap += 8) - 8);
    }
    mode = 0;
    if (arg == 0) {
        mode = 1;
        cb = D_0028DC90;
    }
    if (command == 0x8160) {
        if (D_00315640[1] == 0) {
            D_0028DCA4 = D_00315640[2];
            D_0028DCB0 = D_00315640[3];
        } else {
            D_0028DCA8 = D_00315640[2];
            D_0028DCB4 = D_00315640[3];
        }
    } else if (command == 0x8170) {
        D_0028DCAC = D_00315640[1];
        D_0028DCB8 = D_00315640[2];
    }
    if (command == 0x8130) {
        func_0017EA80(&D_00315680, D_00315640[1] | 0x8130, mode, (s32 *)D_00315640[2], 0x40, 0, 0, cb, D_00315640[0]);
        ret = D_00315640[0];
    } else if (command == 0x8140) {
        func_0017EA80(&D_00315680, D_00315640[1] | 0x8140, mode, D_00315640, 0x40, (s32 *)D_00315640[2], 0x40, cb, D_00315640[2]);
    } else if ((u32)(command - 0x9000) < 0xF1) {
        func_0017EA80(&D_00315680, command, mode, (s32 *)D_00315640[1], D_00315640[2], D_00315640, 0x10, cb, (s32)D_00315640);
        ret = D_00315640[0];
    } else {
        func_0017EA80(&D_00315680, command, mode, D_00315640, 0x40, D_00315640, 0x10, cb, (s32)D_00315640);
        ret = D_00315640[0];
    }
    return ret;
}

void func_00190A00(s32 arg0, s32 arg1, s32 arg2) {
    iSignalSema(arg2);
    __asm__ volatile("sync");
    __asm__ volatile("ei");
}

void sceCdDelayThread(u16 arg0) {
    s32 sp0[8];
    s32 temp_v0;

    sp0[1] = 1;
    sp0[2] = 0;
    sp0[5] = 0;
    temp_v0 = CreateSema(sp0);
    _SetAlarm(arg0, &func_00190A00, temp_v0);
    WaitSema(temp_v0);
    DeleteSema(temp_v0);
}

s32 func_00190A90(void (*arg0)(void)) {
    s32 old;

    if (sceCdSync(1) != 0) {
        return 0;
    }
    func_001843E0();
    old = (s32) D_003156C0;
    D_003156C0 = (void (*)(s32)) arg0;
    func_00184428();
    return old;
}

#define cbfunc_num_00190AE8 (*(volatile s32 *)&D_0028DD14)

/* _sceCd_cd_callback: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

void cd_callback(void *data) {
    s32 *result = data;

    cbfunc_num_00190AE8 = result[0];
    *(volatile s32 *)&D_0028DD18 = cbfunc_num_00190AE8;
    if (cbfunc_num_00190AE8 == 11) {
        cbfunc_num_00190AE8 = 0;
        *(volatile s32 *)&D_0028DCF0 = 0;
        return;
    }
    ((s32 (*)(s32))iSignalSema)(*(volatile s32 *)&D_0028DCE8);
    if (D_0028DCD4 != 0 && D_003156C0 != 0) {
        ((s32 (*)(s32))iSignalSema)(*(volatile s32 *)&D_0028DCE0);
    } else {
        D_0028DCF0 = 0;
    }
    cbfunc_num_00190AE8 = 0;
}

#undef cbfunc_num_00190AE8

void _Cdvd_cbLoop(void) {
    while (1) {
        WaitSema(D_0028DCE0);
        if (D_0028DD14 == -1) {
            D_0028DCF0 = 0;
            D_0028DD14 = 0;
            D_0028DCD4 = 0;
            D_003156CC = 0;
            ExitDeleteThread();
        }
        if (D_0028DCD0 > 0) {
            ((s32 (*)(char *, ...))scePrintf)(D_002BCBE8, D_003156C0, D_0028DD18);
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

s32 sceCdInitEeCB(s32 arg0, void *arg1, s32 arg2) {
    s32 ret = 1;

    if (D_0028DCD4 == 0) {
        D_003156D0 = GetThreadId();
        ReferThreadStatus(D_003156D0, &D_003156D8);
        D_00315708.stackSize = arg2;
        D_00315708.gpReg = &D_00317EF0;
        D_00315708.entry = _Cdvd_cbLoop;
        D_00315708.stack = arg1;
        D_00315708.initPriority = arg0;
        D_0028DCD4 = CreateThread(&D_00315708);
        StartThread(D_0028DCD4, 0);
    } else {
        ChangeThreadPriority(D_0028DCD4, arg0);
        ret = 0;
    }
    return ret;
}


typedef struct CdDirBuf_00190D20 {
    s32 n1;
    s32 n2;
    u8 *d1;
    u8 *d2;
    u8 b1[0x40];
    u8 b2[0x40];
} CdDirBuf_00190D20;

void cd_read_intr(void *arg0) {
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
    cd_callback(&D_0028DD14);
}

void cmd_sem_init(void) {
    s32 sp0[8];

    if (D_0028DCE8 == -1 || D_0028DCEC == -1) {
        sp0[5] = 0;
        sp0[2] = 1;
        sp0[1] = 1;
        (*(volatile s32 *)&D_0028DCE8) = CreateSema(sp0);
        D_0028DCEC = CreateSema(sp0);
        sp0[2] = 0;
        (*(volatile s32 *)&D_0028DCE0) = CreateSema(sp0);
        D_0028DCF0 = 0;
    }
}

void cdvd_exit(void) {
    if (D_0028DCD4 != 0) {
        *(volatile s32 *)&D_0028DD14 = -1;
        SignalSema(*(volatile s32 *)&D_0028DCE0);
    }
    DeleteSema(D_0028DCE8);
    DeleteSema(D_0028DCEC);
    DeleteSema(D_0028DCE0);
    func_001843E0();
    sceSifRemoveCmdHandler(0x80000012);
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
    sceSifAddCmdHandler(0x80000012, &func_00190F48, 0);
    func_00184428();
    D_0028DCE4 = 0;
    D_0028DCFC = 1;
    return 1;
}

typedef struct CdClient_00190FF0 {
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
} CdClient_00190FF0;

typedef struct {
    unsigned char file[0x24];
    char name[0x100];
    void *addr;
} CdSearchReq_00190FF0;

typedef struct {
    unsigned char b[0x24];
} CdlFILE_00190FF0;

extern int D_0028DCDC;
extern s32 D_003156D0;
extern s32 D_003156D8;
extern int D_0028DD00;
extern CdClient_00190FF0 D_003158C0;
extern CdSearchReq_00190FF0 D_00315740;
extern int D_00315880[16];
extern char D_002BCC10[];
extern char D_002BCC30[];
extern char D_002BCC48[];
extern char D_002BCC58[];
extern char D_002BCC68[];

#define scePrintf_00190FF0 ((void (*)(const char *, ...))scePrintf)

/* sceCdSearchFile: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

s32 sceCdSearchFile(void *arg0, const char *name) {
    char *req;
    int w;
    int i;
    int v;

    cmd_sem_init();
    if (D_0028DCE8 != PollSema(*(volatile int *)&D_0028DCE8)) {
        return 0;
    }
    D_0028DCDC = 1;
    ReferThreadStatus(D_003156D0, &D_003156D8);
    if (sceCdSync(1) != 0) {
        SignalSema(*(volatile int *)&D_0028DCE8);
        return 0;
    }
    ((void (*)(s32))func_0017E240)(0);
    if (D_0028DD00 < 0) {
        while (1) {
            if (sceSifBindRpc(&D_003158C0, 0x80000597, 0) < 0) {
                if (D_0028DCD0 > 0) {
                    scePrintf_00190FF0(D_002BCC10);
                }
                w = 0x100000;
                while (w--) {}
                continue;
            }
            if (D_003158C0.serve != 0) {
                D_0028DD00 = 0;
                break;
            }
            w = 0x100000;
            while (w--) {}
        }
    }
    for (i = 0; i < 0x100; i++) {
        if ((D_00315740.name[i] = name[i]) == 0) {
            break;
        }
    }
    if (i == 0x100) {
        D_00315740.name[i - 1] = 0;
    }
    req = (char *)&D_00315740;
    *(char **)(req + 0x124) = req;
    if (D_0028DCD0 > 0) {
        scePrintf_00190FF0(D_002BCC30, req + 0x24);
    }
    func_0017E190((s32 *)req, 0x128);
    if (sceSifCallRpc((s32 *)&D_003158C0, 0, 0, (s32 *)req, 0x128, D_00315880, 4, 0, 0) < 0) {
        SignalSema(*(volatile int *)&D_0028DCE8);
        return 0;
    }
    *(CdlFILE_00190FF0 *)arg0 = *(CdlFILE_00190FF0 *)((int)req | 0x20000000);
    if (D_0028DCD0 > 0) {
        scePrintf_00190FF0(D_002BCC48, (char *)arg0 + 8);
    }
    if (D_0028DCD0 > 0) {
        scePrintf_00190FF0(D_002BCC58, ((int *)arg0)[1]);
    }
    if (D_0028DCD0 > 0) {
        scePrintf_00190FF0(D_002BCC68, ((int *)arg0)[0]);
    }
    v = *(int *)((int)D_00315880 | 0x20000000);
    SignalSema(D_0028DCE8);
    return v;
}

#undef scePrintf_00190FF0

typedef struct CdClient_001912F0 {
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
} CdClient_001912F0;

extern int D_0028DCDC;
extern int D_0028DCF8;
#define cd_001912F0 (*(CdClient_001912F0 *)&D_0028EE90)
extern s32 D_003156D0;
extern s32 D_003156D8;
extern char D_002BCC80[];
extern char D_002BCCA8[];

#define scePrintf_001912F0 ((void (*)(const char *, ...))scePrintf)

/* _sceCd_ncmd_prechk: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

s32 ncmd_prechk(int cmd) {
    int w;

    cmd_sem_init();
    if (D_0028DCE8 != PollSema(*(volatile int *)&D_0028DCE8)) {
        if (D_0028DCD0 > 0) {
            scePrintf_001912F0(D_002BCC80, cmd, D_0028DCDC);
        }
        return 0;
    }
    D_0028DCDC = cmd;
    ReferThreadStatus(D_003156D0, &D_003156D8);
    if (sceCdSync(1) != 0) {
        SignalSema(*(volatile int *)&D_0028DCE8);
        return 0;
    }
    ((void (*)(s32))func_0017E240)(0);
    if (D_0028DCF8 < 0) {
        while (1) {
            if (sceSifBindRpc(&cd_001912F0, 0x80000595, 0) < 0) {
                if (D_0028DCD0 > 0) {
                    scePrintf_001912F0(D_002BCCA8);
                }
                w = 0x100000;
                while (w--) {}
                continue;
            }
            if (cd_001912F0.serve != 0) {
                D_0028DCF8 = 0;
                break;
            }
            w = 0x100000;
            while (w--) {}
        }
    }
    return 1;
}

#undef scePrintf_001912F0
#undef cd_001912F0

s32 func_00191460(void) {
    s32 temp_s0;

    if (ncmd_prechk(2) == 0) {
        return 0;
    }
    if (sceSifCallRpc(&D_0028EE90, 0xE, 0, 0, 0, &D_0028DD40, 4, 0, 0) < 0) {
        SignalSema(D_0028DCE8);
        return 0;
    }
    temp_s0 = *(s32 *)((s32) &D_0028DD40 | 0x20000000);
    SignalSema(D_0028DCE8);
    return temp_s0;
}

s32 sceCdSync(s32 arg0) {
    if (arg0 == 0) {
        if (D_0028DCD0 > 0) {
            scePrintf(&D_002BCCC0);
        }
        while (D_0028DCF0 != 0 || sceSifCheckStatRpc(&D_0028EE90) != 0) {
            sceCdDelayThread(0x3C);
        }
        return 0;
    }
    if (D_0028DCF0 != 0 || sceSifCheckStatRpc(&D_0028EE90) != 0) {
        return 1;
    }
    return 0;
}

s32 sceCdSyncS(s32 arg0) {
    if (arg0 == 0) {
        if (D_0028DCD0 > 0) {
            scePrintf(&D_002BCCD0);
        }
        while (sceSifCheckStatRpc(&D_0028F708) != 0) {
            sceCdDelayThread(0x3C);
        }
        return 0;
    }
    return sceSifCheckStatRpc(&D_0028F708);
}

typedef struct CdClient_00191608 {
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
} CdClient_00191608;

extern int D_0028DCD8;
extern int D_0028DD08;
#define cd_00191608 (*(CdClient_00191608 *)&D_0028F708)
extern s32 D_003156D0;
extern s32 D_003156D8;
extern char D_002BCCE0[];
extern char D_002BCD08[];

#define scePrintf_00191608 ((void (*)(const char *, ...))scePrintf)

/* _sceCd_scmd_prechk: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

s32 scmd_prechk(int cmd) {
    int w;

    cmd_sem_init();
    if (D_0028DCEC != PollSema(*(volatile int *)&D_0028DCEC)) {
        if (D_0028DCD0 > 0) {
            scePrintf_00191608(D_002BCCE0, cmd, D_0028DCD8);
        }
        return 0;
    }
    D_0028DCD8 = cmd;
    ReferThreadStatus(D_003156D0, &D_003156D8);
    if (sceCdSyncS(1) != 0) {
        SignalSema(*(volatile int *)&D_0028DCEC);
        return 0;
    }
    ((void (*)(s32))func_0017E240)(0);
    if (D_0028DD08 < 0) {
        while (1) {
            if (sceSifBindRpc(&cd_00191608, 0x80000593, 0) < 0) {
                if (D_0028DCD0 > 0) {
                    scePrintf_00191608(D_002BCD08);
                }
                w = 0x100000;
                while (w--) {}
                continue;
            }
            if (cd_00191608.serve != 0) {
                D_0028DD08 = 0;
                break;
            }
            w = 0x100000;
            while (w--) {}
        }
    }
    return 1;
}

#undef scePrintf_00191608
#undef cd_00191608

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

/* sceCdInit: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

s32 func_00191778(s32 mode) {
    int *p;
    int ver;
    int r;
    int w;
    int type;
    int v1;
    int v2;

    if (sceCdSyncS(1) != 0) {
        return 0;
    }
    func_0017E240(0);
    D_003156D0 = GetThreadId();
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
        r = sceSifBindRpc(&D_003158E8, 0x80000592, 0);
        if (r < 0) {
            if (D_0028DCD0 > 0) {
                ((void (*)(const char *, ...))scePrintf)(D_002BCD20, r, D_0028DD10);
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
            if (sceSifCallRpc((s32 *)&D_003158E8, 0, 0, &D_00315940, 4, p, 16, 0, 0) < 0) {
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
            ((void (*)(const char *, ...))scePrintf)(D_002BCD40);
        }
        cdvd_exit();
        *(volatile int *)&D_0028DCE8 = -1;
        *(volatile int *)&D_0028DCEC = -1;
        *(volatile int *)&D_0028DCE0 = -1;
        break;
    case 0:
    case 1:
    default:
        cmd_sem_init();
        func_00190F88();
        break;
    }
    return ver;
}

typedef struct CdClient_00191A58 {
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
} CdClient_00191A58;

extern int D_0028DD04;
extern CdClient_00191A58 D_00315910;
extern int D_00315950;
extern char D_002BCD50[];
extern char D_002BCD60[];
extern char D_002BCD80[];

#define scePrintf_00191A58 ((void (*)(const char *, ...))scePrintf)

/* sceCdDiskReady: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

s32 func_00191A58(int mode) {
    int v;
    int w;

    if (D_0028DCD0 > 0) {
        scePrintf_00191A58(D_002BCD50);
    }
    cmd_sem_init();
    if (D_0028DCEC != PollSema(*(volatile int *)&D_0028DCEC)) {
        return 6;
    }
    if (sceCdSyncS(1) != 0) {
        SignalSema(*(volatile int *)&D_0028DCEC);
        return (mode != 8) ? 6 : -1;
    }
    ((void (*)(s32))func_0017E240)(0);
    if (D_0028DD04 < 0) {
        while (1) {
            if (sceSifBindRpc(&D_00315910, 0x8000059A, 0) < 0) {
                if (D_0028DCD0 > 0) {
                    scePrintf_00191A58(D_002BCD60);
                }
                w = 0x100000;
                while (w--) {}
                continue;
            }
            if (D_00315910.serve != 0) {
                D_0028DD04 = 0;
                break;
            }
            w = 0x100000;
            while (w--) {}
        }
    }
    D_00315950 = mode;
    func_0017E190(&D_00315950, 4);
    if (sceSifCallRpc((s32 *)&D_00315910, 0, 0, &D_00315950, 4, &D_0028EEC0, 4, 0, 0) < 0) {
        SignalSema(*(volatile int *)&D_0028DCEC);
        return (mode != 8) ? 6 : -1;
    }
    if (D_0028DCD0 > 0) {
        scePrintf_00191A58(D_002BCD80);
    }
    v = *(int *)((int)&D_0028EEC0 | 0x20000000);
    SignalSema(D_0028DCEC);
    return v;
}

#undef scePrintf_00191A58

#include "common.h"
#include "sce/libkernl.h"

/* get_iob: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

void *func_0017F288(u32 i) {
    char *p;

    func_0017F1A0();
    ((s32 (*)(s32))WaitSema)(D_0028CAA8);
    if (i < 0x20) {
        goto ok;
    }
    ((s32 (*)(s32))SignalSema)(D_0028CAA8);
    return 0;
ok:
    p = &D_00313980[i * 16];
    ((s32 (*)(s32))SignalSema)(D_0028CAA8);
    return p;
}

/* _sceFs_Rcv_Intr: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

void func_0017F2F8(void) {
    s32 id;
    s32 cmd;
    s32 buf;
    s32 size;
    s32 addr;
    s32 len;
    s32 *q;
    s32 i;
    s32 k;

    *(SceFsVersion *)&id = *(SceFsVersion *)((s32)(D_00313540 + 0x0) | 0x20000000);
    *(SceFsVersion *)&cmd = *(SceFsVersion *)((s32)(D_00313540 + 0x4) | 0x20000000);
    *(SceFsVersion *)&buf = *(SceFsVersion *)((s32)(D_00313540 + 0x8) | 0x20000000);
    *(SceFsVersion *)&size = *(SceFsVersion *)((s32)(D_00313540 + 0xC) | 0x20000000);
    if (id >= 0)
        func_00198790((void *)buf, (void *)((s32)(D_00313540 + 0x10) | 0x20000000), size);
    switch (cmd) {
    case 2:
        q = (s32 *)((s32)(D_00313540 + 0x14) | 0x20000000);
        if (q[0] > 0) {
            char *dst = (char *)q[2];

            for (i = 0; i < q[0]; i++) {
                char *src = (char *)q + 0x10;

                dst[i] = src[i];
            }
        }
        if (q[1] > 0) {
            char *dst = (char *)q[3];

            for (i = 0; i < q[1]; i++) {
                char *src = (char *)q + 0x50;

                dst[i] = src[i];
            }
        }
        break;
    case 11:
        *(SceFsVersion *)&addr = *(SceFsVersion *)((s32)(D_00313540 + 0x14) | 0x20000000);
        *(SceFsDirent *)addr = *(SceFsDirent *)((s32)((D_00313540 + 0x14) + 4) | 0x20000000);
        break;
    case 12:
        *(SceFsVersion *)&addr = *(SceFsVersion *)((s32)(D_00313540 + 0x14) | 0x20000000);
        *(SceFsStatRec *)addr = *(SceFsStatRec *)((s32)((D_00313540 + 0x14) + 4) | 0x20000000);
        break;
    case 23:
    case 25:
    case 26:
        *(SceFsVersion *)&addr = *(SceFsVersion *)((s32)(D_00313540 + 0x14) | 0x20000000);
        *(SceFsVersion *)&len = *(SceFsVersion *)((s32)((D_00313540 + 0x14) + 4) | 0x20000000);
        k = len;
        if (1024 < (u32)k) {
            len = 1024;
            k = 1024;
        }
        func_00198790((void *)addr, (void *)((s32)((D_00313540 + 0x14) + 8) | 0x20000000), k);
        break;
    }
    if (id < 0) {
        id = -id;
        for (i = 0; i < 32; i++) {
            if (D_0028CA20[i] == id) {
                D_0028CA20[i] = -1;
                break;
            }
        }
    } else {
        iSignalSema(id);
    }
}

void func_0017F6B8(void) {
    s32 sp0[8];
    if (D_0028CAA4 == -1) {
        sp0[2] = 1;
        sp0[1] = 1;
        sp0[5] = 0;
        D_0028CAA4 = CreateSema(sp0);
    }
}

s32 func_0017F708(void) {
    func_0017F6B8();
    WaitSema(D_0028CAA4);
    return 0;
}

void _cleanup(void) {
    SignalSema(D_0028CAA4);
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
    _cleanup();
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

s32 sceFsReset(void) {
    D_0028CAA0 = 0;
    func_00198948(&D_00313BA8, 0, 4U);
    return 0;
}

/* sceOpen: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

s32 func_0017FA98(void *name, s32 flags, ...) {
    s32 *g = (s32 *)&D_003128C0;
    s32 mode;
    SceIob *iob;
    s32 i;
    s32 idx;
    s32 h;
    s32 rc;
    s32 result;
    struct SemaParam buf;

    ((s32 (*)(s32))func_0017F708)(0);
    if (D_0028CAA0 == 0)
        func_0017F808();
    if (func_0017F9D0() != 0) {
        _cleanup();
        return 0xFFFEFFFC;
    }
    iob = func_0017F200();
    if (iob == 0) {
        _cleanup();
        return -0x13;
    }
    mode = *(s32 *)((char *)__builtin_next_arg(flags) - 0x30);
    for (i = 0; i < 0x400; i++) {
        *((char *)g + i + 0x14) = ((u8 *)name)[i];
        if (*((char *)g + i + 0x14) == 0) {
            break;
        }
    }
    if (i == 0x400) {
        ((char *)g)[0x413] = 0;
    }
    idx = iob - (SceIob *)D_00313980;
    g[3] = flags & 0x6FFFFFFF;
    g[4] = mode;
    g[0x414 / 4] = idx;
    buf.maxCount = 1;
    buf.initCount = 0;
    buf.option = 0;
    g[0] = h = CreateSema(&buf);
    *(void **)(g + 1) = &result;
    g[2] = 4;
    rc = sceSifCallRpc(&D_00313B80, 0, 0, (s32 *)&D_003128C0, 0x418, &D_00313500, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _cleanup();
        return -0xB;
    }
    rc = *(s32 *)((s32)&D_00313500 | 0x20000000);
    _cleanup();
    if (rc == 0) {
        DeleteSema(h);
        return -0xB;
    }
    WaitSema(h);
    DeleteSema(h);
    if (result < 0) {
        WaitSema(D_0028CAA8);
        iob->inuse = 0;
        SignalSema(D_0028CAA8);
        return result;
    }
    rc = idx;
    ((s32 (*)(s32))WaitSema)(D_0028CAA8);
    iob->fd = result;
    iob->inuse |= flags;
    SignalSema(D_0028CAA8);
    return rc;
}

/* sceClose: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

s32 func_0017FD20(u32 fd) {
    s32 *g = (s32 *)&D_003128C0;
    SceIob *iob;
    s32 handle;
    s32 uv;
    s32 h;
    s32 rc;
    s32 result;
    struct SemaParam buf;

    iob = func_0017F288(fd);
    ((s32 (*)(s32))func_0017F708)(1);
    if (D_0028CAA0 == 0) {
        _cleanup();
        return -1;
    }
    if (iob == 0 || iob->inuse == 0) {
        _cleanup();
        return -9;
    }
    handle = iob->fd;
    g[3] = handle;
    g[4] = iob - (SceIob *)D_00313980;
    buf.maxCount = 1;
    buf.initCount = 0;
    buf.option = 0;
    D_003128C0.sema = h = CreateSema(&buf);
    *(void **)(g + 1) = &result;
    g[2] = 4;
    rc = sceSifCallRpc(&D_00313B80, 1, 0, g, 0x14, &D_00313500, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _cleanup();
        return -0xB;
    }
    iob->inuse = 0;
    uv = *(s32 *)((s32)&D_00313500 | 0x20000000);
    _cleanup();
    if (uv == 0) {
        DeleteSema(h);
        return -0xB;
    }
    WaitSema(h);
    DeleteSema(h);
    if (result < 0) {
        return result;
    }
    return 0;
}

/* sceLseek: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

s32 func_0017FEA0(u32 fd, s32 offset, s32 whence) {
    s32 *g = (s32 *)&D_003128C0;
    SceIob *iob;
    s32 inuse;
    s32 uv;
    s32 h;
    s32 rc;
    s32 i;
    s32 result;
    struct SemaParam buf;

    iob = func_0017F288(fd);
    ((s32 (*)(s32))func_0017F708)(4);
    if (D_0028CAA0 == 0) {
        _cleanup();
        return -1;
    }
    if (iob == 0 || (inuse = iob->inuse) == 0) {
        _cleanup();
        return -9;
    }
    g[3] = iob->fd;
    g[4] = offset;
    g[5] = whence;
    g[6] = iob - (SceIob *)D_00313980;
    buf.maxCount = 1;
    buf.initCount = 0;
    buf.option = 0;
    D_003128C0.sema = h = CreateSema(&buf);
    *(void **)(g + 1) = &result;
    g[2] = 4;
    if (inuse & 0x8000) {
        WaitSema(D_0028CAAC);
        for (i = 0; i < 0x20; i++) {
            if (D_0028CA20[i] == -1) {
                D_0028CA20[i] = g[0];
                g[0] = -g[0];
                break;
            }
        }
        SignalSema(D_0028CAAC);
    }
    rc = sceSifCallRpc(&D_00313B80, 4, 0, (s32 *)&D_003128C0, 0x1C, &D_00313500, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _cleanup();
        return -0xB;
    }
    uv = *(s32 *)((s32)&D_00313500 | 0x20000000);
    _cleanup();
    if (uv == 0) {
        DeleteSema(h);
        return -0xB;
    }
    if (sceFsIsNowait(inuse)) {
        DeleteSema(h);
        return 0;
    }
    WaitSema(h);
    DeleteSema(h);
    return result;
}

/* sceRead: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

s32 func_001800D8(s32 fd, s32 buf, s32 nbyte) {
    FsReadReq *g = (FsReadReq *)&D_003128C0;
    SceIob *iob;
    s32 inuse;
    s32 uv;
    s32 h;
    s32 rc;
    s32 i;
    s32 result;
    struct SemaParam sema;

    iob = func_0017F288(fd);
    ((s32 (*)(s32))func_0017F708)(2);
    if (D_0028CAA0 == 0) {
        _cleanup();
        return -1;
    }
    if (iob == 0 || (inuse = iob->inuse) == 0) {
        _cleanup();
        return -9;
    }
    g->fd = iob->fd;
    g->iob = iob - (SceIob *)D_00313980;
    g->buf = (void *)buf;
    g->nbyte = nbyte;
    sema.maxCount = 1;
    sema.initCount = 0;
    sema.option = 0;
    D_003128C0.sema = h = CreateSema(&sema);
    g->result = &result;
    g->mode = 4;
    if (inuse & 0x8000) {
        WaitSema(D_0028CAAC);
        for (i = 0; i < 0x20; i++) {
            if (D_0028CA20[i] == -1) {
                D_0028CA20[i] = g->sema;
                g->sema = -g->sema;
                break;
            }
        }
        SignalSema(D_0028CAAC);
    }
    if ((inuse & 0x20000000) == 0) {
        func_0017E190((s32 *)buf, nbyte);
    }
    func_0017E190((s32 *)D_00313540, 0xA4);
    func_0017E190((s32 *)g, 0x20);
    rc = sceSifCallRpc(&D_00313B80, 2, 0, (s32 *)&D_003128C0, 0x20, &D_00313500, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _cleanup();
        return -0xB;
    }
    uv = *(s32 *)((s32)&D_00313500 | 0x20000000);
    _cleanup();
    if (uv == 0) {
        DeleteSema(h);
        return -0xB;
    }
    if (sceFsIsNowait(inuse)) {
        DeleteSema(h);
        return 0;
    }
    WaitSema(h);
    DeleteSema(h);
    return result;
}

/* sceWrite: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

s32 func_00180348(s32 fd, void *buf, s32 nbyte) {
    FsWriteReq *g = (FsWriteReq *)&D_003128C0;
    SceIob *iob;
    s32 inuse;
    s32 uv;
    s32 h;
    s32 rc;
    s32 i;
    s32 j;
    char *dst;
    s32 nb;
    s32 result;
    struct SemaParam sema;

    iob = func_0017F288(fd);
    ((s32 (*)(s32))func_0017F708)(3);
    if (D_0028CAA0 == 0) {
        _cleanup();
        return -1;
    }
    if (iob == 0 || (inuse = iob->inuse) == 0) {
        _cleanup();
        return -9;
    }
    g->fd = iob->fd;
    g->iob = iob - (SceIob *)D_00313980;
    g->nbyte = nbyte;
    g->buf = buf;
    sema.maxCount = 1;
    sema.initCount = 0;
    sema.option = 0;
    D_003128C0.sema = h = CreateSema(&sema);
    g->result = &result;
    g->mode = 4;
    if (inuse & 0x8000) {
        WaitSema(D_0028CAAC);
        for (i = 0; i < 0x20; i++) {
            if (D_0028CA20[i] == -1) {
                D_0028CA20[i] = g->sema;
                g->sema = -g->sema;
                break;
            }
        }
        SignalSema(D_0028CAAC);
    }
    if (((u32)buf & 0xF) == 0) {
        nb = 0;
    } else {
        nb = (u32)buf / 16 * 16 + 16 - (u32)buf;
    }
    if (nb > nbyte) {
        nb = nbyte;
    }
    if ((inuse & 0x20000000) == 0) {
        func_0017E190(buf, nbyte);
    }
    buf = (char *)((u32)buf | 0x20000000);
    g->headLen = nb;
    for (j = 0; j < nb; j++) {
        dst = g->head;
        dst[j] = ((char *)buf)[j];
    }
    rc = sceSifCallRpc(&D_00313B80, 3, 0, (s32 *)&D_003128C0, 0x30, &D_00313500, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _cleanup();
        return -0xB;
    }
    uv = *(s32 *)((s32)&D_00313500 | 0x20000000);
    _cleanup();
    if (uv == 0) {
        DeleteSema(h);
        return -0xB;
    }
    if (sceFsIsNowait(inuse)) {
        DeleteSema(h);
        return 0;
    }
    WaitSema(h);
    DeleteSema(h);
    return result;
}

/* sceIoctl: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

s32 func_00180608(u32 fd, s32 request, void *argp) {
    s32 *g = (s32 *)&D_003128C0;
    SceIob *iob;
    s32 uv;
    s32 h;
    s32 rc;
    s32 i;
    s32 result;
    struct SemaParam sema;

    rc = 1;

    iob = func_0017F288(fd);
    ((s32 (*)(s32))func_0017F708)(5);
    D_00312884 = argp;
    if (D_0028CAA0 == 0) {
        func_0017F808();
    }
    if (iob == 0 || iob->inuse == 0) {
        _cleanup();
        return -9;
    }
    g[0x105] = 0;
    g[0x106] = 0;
    switch (request) {
    case 1:
        WaitSema(D_0028CAAC);
        for (i = 0; i < 0x20; i++) {
            if (D_0028CA20[i] != -1) {
                break;
            }
        }
        if (i == 0x20) {
            *(s32 *)D_00312884 = 0;
        } else {
            *(s32 *)D_00312884 = 1;
        }
        SignalSema(D_0028CAAC);
        _cleanup();
        return 0;
    case 2:
        *(s32 *)argp = *(s32 *)((s32)(D_00313540 + 0x10) | 0x20000000);
        _cleanup();
        return 0;
    case 3:
        *(s64 *)argp = *(s64 *)((s32)(D_00313540 + 0x10) | 0x20000000);
        _cleanup();
        return 0;
    }
    g[3] = iob->fd;
    g[4] = request;
    if (argp == 0) {
        g[0x107] = 0;
    } else {
        g[0x107] = 1024;
        *(SceIoctlArg *)((char *)g + 0x14) = *(SceIoctlArg *)argp;
    }
    sema.maxCount = 1;
    sema.initCount = 0;
    sema.option = 0;
    h = CreateSema(&sema);
    g[2] = 4;
    *(void **)(g + 1) = &result;
    g[0] = h;
    func_0017E190((s32 *)&D_003128C0, 0x420);
    rc = sceSifCallRpc(&D_00313B80, 5, 0, (s32 *)&D_003128C0, 0x420, &D_00313500, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _cleanup();
        return -0xB;
    }
    uv = *(s32 *)((s32)&D_00313500 | 0x20000000);
    _cleanup();
    if (uv == 0) {
        DeleteSema(h);
        return -0xB;
    }
    WaitSema(h);
    DeleteSema(h);
    return result;
}

/* sceIoctl2: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

s32 func_00180958(u32 fd, s32 request, void *argp, u32 arglen, void *bufp, u32 buflen) {
    s32 *g = (s32 *)&D_003128C0;
    SceIob *iob;
    s32 uv;
    s32 h;
    s32 rc;
    s32 result;
    struct SemaParam buf;

    iob = func_0017F288(fd);
    ((s32 (*)(s32))func_0017F708)(0x1A);
    if (D_0028CAA0 == 0) {
        func_0017F808();
    }
    if (iob == 0 || iob->inuse == 0) {
        _cleanup();
        return -9;
    }
    if (arglen > 0x400 || buflen > 0x400) {
        _cleanup();
        return -0x16;
    }
    if (argp == 0) {
        g[0x107] = 0;
    } else {
        func_00198790((char *)g + 0x14, argp, arglen);
    }
    g[3] = iob->fd;
    g[4] = request;
    g[0x107] = arglen;
    buf.maxCount = 1;
    buf.initCount = 0;
    buf.option = 0;
    h = CreateSema(&buf);
    *(void **)(g + 1) = &result;
    g[0x106] = buflen;
    g[2] = 4;
    *(void **)(g + 0x105) = bufp;
    g[0] = h;
    func_0017E190((s32 *)&D_003128C0, 0x420);
    rc = sceSifCallRpc(&D_00313B80, 0x1A, 0, (s32 *)&D_003128C0, 0x420, &D_00313500, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _cleanup();
        return -0xB;
    }
    uv = *(s32 *)((s32)&D_00313500 | 0x20000000);
    _cleanup();
    if (uv == 0) {
        DeleteSema(h);
        return -0xB;
    }
    WaitSema(h);
    DeleteSema(h);
    return result;
}

/* _sceCallCode: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

s32 func_00180B38(s32 name, s32 code) {
    s32 *g = (s32 *)&D_003128C0;
    s32 uv;
    s32 h;
    s32 rc;
    s32 i;
    s32 result;
    struct SemaParam buf;

    ((s32 (*)(s32))func_0017F708)(code);
    if (D_0028CAA0 == 0) {
        func_0017F808();
    }
    for (i = 0; i < 0x400; i++) {
        *((char *)g + i + 0xC) = ((char *)name)[i];
        if (*((char *)g + i + 0xC) == 0) {
            break;
        }
    }
    if (i == 0x400) {
        *((char *)g + 0x40B) = 0;
        i = 0x3FF;
    }
    buf.maxCount = 1;
    buf.initCount = 0;
    buf.option = 0;
    g[0] = h = CreateSema(&buf);
    *(void **)(g + 1) = &result;
    g[2] = 4;
    rc = sceSifCallRpc(&D_00313B80, code, 0, (s32 *)&D_003128C0, i + 0xD, &D_00313500, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _cleanup();
        return -0xB;
    }
    uv = *(s32 *)((s32)&D_00313500 | 0x20000000);
    _cleanup();
    if (uv == 0) {
        DeleteSema(h);
        return -0xB;
    }
    WaitSema(h);
    DeleteSema(h);
    return result;
}

s32 func_00180CE0(s32 arg0) {
    return func_00180B38(arg0, 6);
}

/* sceMkdir: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

s32 func_00180D00(char *name, s32 mode) {
    s32 *g = (s32 *)&D_003128C0;
    s32 uv;
    s32 h;
    s32 rc;
    s32 i;
    s32 result;
    struct SemaParam buf;

    ((s32 (*)(s32))func_0017F708)(7);
    if (D_0028CAA0 == 0) {
        func_0017F808();
    }
    for (i = 0; i < 0x400; i++) {
        *((char *)g + i + 0x10) = name[i];
        if (*((char *)g + i + 0x10) == 0) {
            break;
        }
    }
    if (i == 0x400) {
        *((char *)g + 0x40F) = 0;
        i = 0x3FF;
    }
    g[3] = mode;
    buf.maxCount = 1;
    buf.initCount = 0;
    buf.option = 0;
    g[0] = h = CreateSema(&buf);
    *(void **)(g + 1) = &result;
    g[2] = 4;
    rc = sceSifCallRpc(&D_00313B80, 7, 0, (s32 *)&D_003128C0, i + 0x11, &D_00313500, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _cleanup();
        return -0xB;
    }
    uv = *(s32 *)((s32)&D_00313500 | 0x20000000);
    _cleanup();
    if (uv == 0) {
        DeleteSema(h);
        return -0xB;
    }
    WaitSema(h);
    DeleteSema(h);
    return result;
}

s32 func_00180EB0(s32 arg0) {
    return func_00180B38(arg0, 8);
}

/* sceFormat: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

s32 func_00180ED0(u8 *dev, u8 *blockdev, u8 *arg, s32 arglen) {
    s32 *g = (s32 *)&D_003128C0;
    s32 uv;
    s32 h;
    s32 rc;
    s32 i;
    s32 result;
    struct SemaParam buf;

    ((s32 (*)(s32))func_0017F708)(0xE);
    if (D_0028CAA0 == 0) {
        func_0017F808();
    }
    for (i = 0; i < 0x400; i++) {
        *((char *)g + i + 0xC) = dev[i];
        if (*((char *)g + i + 0xC) == 0) {
            break;
        }
    }
    if (i == 0x400) {
        ((char *)g)[0x40B] = 0;
    }
    if (blockdev == 0) {
        ((char *)g)[0x40C] = 0;
    } else {
        for (i = 0; i < 0x400; i++) {
            char *d = (char *)g + 0x40C;
            d[i] = blockdev[i];
            if (d[i] == 0) {
                break;
            }
        }
        if (i == 0x400) {
            ((char *)g)[0x80B] = 0;
        }
    }
    if (arglen > 0x400) {
        _cleanup();
        return -7;
    }
    for (i = 0; i < arglen; i++) {
        char *d = (char *)g + 0x80C;
        d[i] = arg[i];
    }
    g[0x303] = arglen;
    buf.maxCount = 1;
    buf.initCount = 0;
    buf.option = 0;
    g[0] = h = CreateSema(&buf);
    *(void **)(g + 1) = &result;
    g[2] = 4;
    func_0017E190((s32 *)&D_003128C0, 0xC10);
    rc = sceSifCallRpc(&D_00313B80, 0xE, 0, (s32 *)&D_003128C0, 0xC10, &D_00313500, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _cleanup();
        return -0xB;
    }
    uv = *(s32 *)((s32)&D_00313500 | 0x20000000);
    _cleanup();
    if (uv == 0) {
        DeleteSema(h);
        return -0xB;
    }
    WaitSema(h);
    DeleteSema(h);
    return result;
}

extern s32 D_00313500;
extern s32 D_00313B80;

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
    sema = CreateSema(sp);
    D_003128C0.sema = sema;
    p->result = &result;
    p->size = 4;
    if (sceSifCallRpc(&D_00313B80, 0xF, 0, (s32 *)p, 0x10, &D_00313500, 4, 0, 0) < 0) {
        DeleteSema(sema);
        _cleanup();
        return -1;
    }
    r = *(s32 *)((u32)&D_00313500 | 0x20000000);
    _cleanup();
    if (r == 0) {
        DeleteSema(sema);
        return -1;
    }
    WaitSema(sema);
    DeleteSema(sema);
    return result;
}

s32 func_00181260(s32 arg0) {
    return func_00180B38(arg0, 0x10);
}

/* Open a file on the IOP (fio RPC 9): take a free iob slot, open, store the handle; returns the slot's index
   or the open's error. The semaphore calls return int as in Sony's headers (our prototypes say void). */

s32 func_00181280(s32 arg0) {
    SceIob *slot;
    s32 r;

    ((s32 (*)(s32))func_0017F708)(9);
    if (D_0028CAA0 == 0) {
        func_0017F808();
    }
    _cleanup();
    slot = func_0017F200();
    if (slot == NULL) {
        return -0x13;
    }
    r = func_00180B38(arg0, 9);
    if (r < 0) {
        ((int (*)(int))WaitSema)(D_0028CAA8);
        slot->inuse = 0;
        ((int (*)(int))SignalSema)(D_0028CAA8);
        return r;
    }
    ((int (*)(int))WaitSema)(D_0028CAA8);
    slot->fd = r;
    r = slot - (SceIob *)D_00313980;
    ((int (*)(int))SignalSema)(D_0028CAA8);
    return r;
}

/* sceDclose: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

s32 func_00181348(u32 fd) {
    s32 *g = (s32 *)&D_003128C0;
    void *obj;
    s32 handle;
    s32 uv;
    s32 h;
    s32 rc;
    s32 result;
    struct SemaParam buf;

    obj = func_0017F288(fd);
    ((s32 (*)(s32))func_0017F708)(0xA);
    if (D_0028CAA0 == 0) {
        _cleanup();
        return -1;
    }
    if (obj == 0 || ((s32 *)obj)[1] == 0) {
        _cleanup();
        return -9;
    }
    handle = ((s32 *)obj)[0];
    g[3] = handle;
    buf.maxCount = 1;
    buf.initCount = 0;
    buf.option = 0;
    D_003128C0.sema = h = CreateSema(&buf);
    *(void **)(g + 1) = &result;
    g[2] = 4;
    rc = sceSifCallRpc(&D_00313B80, 0xA, 0, g, 0x14, &D_00313500, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _cleanup();
        return -0xB;
    }
    ((s32 *)obj)[1] = 0;
    uv = *(s32 *)((s32)&D_00313500 | 0x20000000);
    _cleanup();
    if (uv == 0) {
        DeleteSema(h);
        return -0xB;
    }
    WaitSema(h);
    DeleteSema(h);
    if (result < 0) {
        return result;
    }
    return 0;
}

s32 func_001814B0(s32 arg0, s32 arg1) {
    s32 sp[8];
    s32 result;
    FioReq_00181140 *p;
    s32 *slot;
    s32 sema;
    s32 r;

    p = &D_003128C0;
    slot = func_0017F288(arg0);
    ((s32 (*)(s32))func_0017F708)(0xB);
    if (D_0028CAA0 == 0) {
        _cleanup();
        return -1;
    }
    if (slot == NULL || slot[1] == 0) {
        _cleanup();
        return -9;
    }
    p->arg = slot[0];
    *(s32 *)((u8 *)p + 0x10) = arg1;
    sp[1] = 1;
    sp[2] = 0;
    sp[5] = 0;
    sema = CreateSema(sp);
    D_003128C0.sema = sema;
    p->result = &result;
    p->size = 4;
    if (sceSifCallRpc(&D_00313B80, 0xB, 0, (s32 *)p, 0x20, &D_00313500, 4, 0, 0) < 0) {
        WaitSema(sema);
        _cleanup();
        return -0xB;
    }
    r = *(s32 *)((u32)&D_00313500 | 0x20000000);
    _cleanup();
    if (r == 0) {
        DeleteSema(sema);
        return -0xB;
    }
    WaitSema(sema);
    DeleteSema(sema);
    return result;
}

/* sceGetstat: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

s32 func_00181608(u8 *name, void *stat) {
    FsGetstatReq *g = (FsGetstatReq *)&D_003128C0;
    s32 uv;
    s32 h;
    s32 rc;
    s32 i;
    s32 result;
    struct SemaParam buf;

    ((s32 (*)(s32))func_0017F708)(0xC);
    if (D_0028CAA0 == 0) {
        func_0017F808();
    }
    for (i = 0; i < 0x400; i++) {
        g->name[i] = name[i];
        if (g->name[i] == 0) {
            break;
        }
    }
    if (i == 0x400) {
        g->name[0x3FF] = 0;
        i = 0x3FF;
    }
    g->stat = stat;
    buf.maxCount = 1;
    buf.initCount = 0;
    buf.option = 0;
    g->sema = h = CreateSema(&buf);
    g->result = &result;
    g->mode = 4;
    rc = sceSifCallRpc(&D_00313B80, 0xC, 0, (s32 *)&D_003128C0, i + 0x11, &D_00313500, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _cleanup();
        return -0xB;
    }
    uv = *(s32 *)((s32)&D_00313500 | 0x20000000);
    _cleanup();
    if (uv == 0) {
        DeleteSema(h);
        return -0xB;
    }
    WaitSema(h);
    DeleteSema(h);
    return result;
}

/* sceChstat: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

s32 func_001817A8(u8 *name, void *stat, s32 mask) {
    s32 *g = (s32 *)&D_003128C0;
    s32 uv;
    s32 h;
    s32 rc;
    s32 i;
    s32 result;
    struct SemaParam buf;

    ((s32 (*)(s32))func_0017F708)(0xD);
    if (D_0028CAA0 == 0) {
        func_0017F808();
    }
    for (i = 0; i < 0x400; i++) {
        *((u8 *)g + i + 0x50) = name[i];
        if (*((u8 *)g + i + 0x50) == 0) {
            break;
        }
    }
    if (i == 0x400) {
        *((char *)g + 0x44F) = 0;
        i = 0x3FF;
    }
    *(SceFsStatRec *)((char *)g + 0x10) = *(SceFsStatRec *)stat;
    g[3] = mask;
    buf.maxCount = 1;
    buf.initCount = 0;
    buf.option = 0;
    g[0] = h = CreateSema(&buf);
    *(void **)(g + 1) = &result;
    g[2] = 4;
    func_0017E190((s32 *)&D_003128C0, 0x450);
    rc = sceSifCallRpc(&D_00313B80, 0xD, 0, (s32 *)&D_003128C0, i + 0x51, &D_00313500, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _cleanup();
        return -0xB;
    }
    uv = *(s32 *)((s32)&D_00313500 | 0x20000000);
    _cleanup();
    if (uv == 0) {
        DeleteSema(h);
        return -0xB;
    }
    WaitSema(h);
    DeleteSema(h);
    return result;
}

/* sceRename: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

s32 func_001819E8(u8 *oldname, u8 *newname) {
    s32 *g = (s32 *)&D_003128C0;
    s32 uv;
    s32 h;
    s32 rc;
    s32 i;
    s32 result;
    struct SemaParam buf;

    ((s32 (*)(s32))func_0017F708)(0x11);
    if (D_0028CAA0 == 0) {
        func_0017F808();
    }
    for (i = 0; i < 0x400; i++) {
        *((char *)g + i + 0xC) = oldname[i];
        if (*((char *)g + i + 0xC) == 0) {
            break;
        }
    }
    if (i == 0x400) {
        ((char *)g)[0x40B] = 0;
    }
    for (i = 0; i < 0x400; i++) {
        char *d = (char *)g + 0x40C;
        d[i] = newname[i];
        if (d[i] == 0) {
            break;
        }
    }
    if (i == 0x400) {
        ((char *)g)[0x80B] = 0;
    }
    buf.maxCount = 1;
    buf.initCount = 0;
    buf.option = 0;
    g[0] = h = CreateSema(&buf);
    *(void **)(g + 1) = &result;
    g[2] = 4;
    func_0017E190((s32 *)&D_003128C0, 0x80C);
    rc = sceSifCallRpc(&D_00313B80, 0x11, 0, (s32 *)&D_003128C0, 0x80C, &D_00313500, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _cleanup();
        return -0xB;
    }
    uv = *(s32 *)((s32)&D_00313500 | 0x20000000);
    _cleanup();
    if (uv == 0) {
        DeleteSema(h);
        return -0xB;
    }
    WaitSema(h);
    DeleteSema(h);
    return result;
}

s32 func_00181BD8(s32 arg0) {
    return func_00180B38(arg0, 0x12);
}

/* sceSync: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

s32 func_00181BF8(u8 *name, s32 flag) {
    s32 *g = (s32 *)&D_003128C0;
    s32 uv;
    s32 h;
    s32 rc;
    s32 i;
    s32 result;
    struct SemaParam buf;

    ((s32 (*)(s32))func_0017F708)(0x13);
    if (D_0028CAA0 == 0) {
        func_0017F808();
    }
    for (i = 0; i < 0x400; i++) {
        *((char *)g + i + 0x14) = name[i];
        if (*((char *)g + i + 0x14) == 0) {
            break;
        }
    }
    if (i == 0x400) {
        ((char *)g)[0x413] = 0;
    }
    g[4] = flag;
    buf.maxCount = 1;
    buf.initCount = 0;
    buf.option = 0;
    g[0] = h = CreateSema(&buf);
    *(void **)(g + 1) = &result;
    g[2] = 4;
    rc = sceSifCallRpc(&D_00313B80, 0x13, 0, (s32 *)&D_003128C0, 0x414, &D_00313500, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _cleanup();
        return -0xB;
    }
    uv = *(s32 *)((s32)&D_00313500 | 0x20000000);
    _cleanup();
    if (uv == 0) {
        DeleteSema(h);
        return -0xB;
    }
    WaitSema(h);
    DeleteSema(h);
    return result;
}

/* sceMount: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

s32 func_00181D90(u8 *fsname, u8 *devname, s32 flag, u8 *arg, s32 arglen) {
    s32 *g = (s32 *)&D_003128C0;
    s32 uv;
    s32 h;
    s32 rc;
    s32 i;
    s32 result;
    struct SemaParam buf;

    ((s32 (*)(s32))func_0017F708)(0x14);
    if (D_0028CAA0 == 0) {
        func_0017F808();
    }
    for (i = 0; i < 0x400; i++) {
        *((char *)g + i + 0xC) = fsname[i];
        if (*((char *)g + i + 0xC) == 0) {
            break;
        }
    }
    if (i == 0x400) {
        ((char *)g)[0x40B] = 0;
    }
    for (i = 0; i < 0x400; i++) {
        char *d = (char *)g + 0x40C;
        d[i] = devname[i];
        if (d[i] == 0) {
            break;
        }
    }
    if (i == 0x400) {
        ((char *)g)[0x80B] = 0;
    }
    if (arglen > 0x400) {
        _cleanup();
        return -7;
    }
    for (i = 0; i < arglen; i++) {
        char *d = (char *)g + 0x80C;
        d[i] = arg[i];
    }
    g[0x304] = arglen;
    g[0x303] = flag;
    buf.maxCount = 1;
    buf.initCount = 0;
    buf.option = 0;
    g[0] = h = CreateSema(&buf);
    *(void **)(g + 1) = &result;
    g[2] = 4;
    func_0017E190((s32 *)&D_003128C0, 0xC14);
    rc = sceSifCallRpc(&D_00313B80, 0x14, 0, (s32 *)&D_003128C0, 0xC14, &D_00313500, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _cleanup();
        return -0xB;
    }
    uv = *(s32 *)((s32)&D_00313500 | 0x20000000);
    _cleanup();
    if (uv == 0) {
        DeleteSema(h);
        return -0xB;
    }
    WaitSema(h);
    DeleteSema(h);
    return result;
}

s32 func_00182000(s32 arg0) {
    return func_00180B38(arg0, 0x15);
}

/* sceLseek64: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

s64 func_00182020(s32 fd, s64 offset, s32 whence) {
    s32 *g = (s32 *)&D_003128C0;
    SceIob *iob;
    s32 inuse;
    s32 uv;
    s32 h;
    s32 rc;
    s32 i;
    s64 result;
    struct SemaParam buf;

    iob = func_0017F288(fd);
    ((s32 (*)(s32))func_0017F708)(0x16);
    if (D_0028CAA0 == 0) {
        _cleanup();
        return -1;
    }
    if (iob == 0 || (inuse = iob->inuse) == 0) {
        _cleanup();
        return -9;
    }
    *(s64 *)(g + 4) = offset;
    g[3] = iob->fd;
    g[6] = whence;
    g[7] = iob - (SceIob *)D_00313980;
    buf.maxCount = 1;
    buf.initCount = 0;
    buf.option = 0;
    h = CreateSema(&buf);
    *(void **)(g + 1) = &result;
    g[2] = 8;
    D_003128C0.sema = h;
    if (inuse & 0x8000) {
        WaitSema(D_0028CAAC);
        for (i = 0; i < 0x20; i++) {
            if (D_0028CA20[i] == -1) {
                D_0028CA20[i] = g[0];
                g[0] = -g[0];
                break;
            }
        }
        SignalSema(D_0028CAAC);
    }
    rc = sceSifCallRpc(&D_00313B80, 0x16, 0, (s32 *)&D_003128C0, 0x20, &D_00313500, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _cleanup();
        return -0xB;
    }
    uv = *(s32 *)((s32)&D_00313500 | 0x20000000);
    _cleanup();
    if (uv == 0) {
        DeleteSema(h);
        return -0xB;
    }
    if (sceFsIsNowait(inuse)) {
        DeleteSema(h);
        return 0;
    }
    WaitSema(h);
    DeleteSema(h);
    return result;
}

/* sceDevctl: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

s32 func_00182258(u8 *name, s32 cmd, u8 *arg, u32 arglen, void *bufp, u32 buflen) {
    s32 *g = (s32 *)&D_003128C0;
    s32 uv;
    s32 h;
    s32 rc;
    s32 i;
    s32 result;
    struct SemaParam buf;

    ((s32 (*)(s32))func_0017F708)(0x17);
    if (D_0028CAA0 == 0) {
        func_0017F808();
    }
    for (i = 0; i < 0x400; i++) {
        *((char *)g + i + 0xC) = name[i];
        if (*((char *)g + i + 0xC) == 0) {
            break;
        }
    }
    if (i == 0x400) {
        ((char *)g)[0x40B] = 0;
    }
    if (arglen > 0x400 || buflen > 0x400) {
        _cleanup();
        return -0x16;
    }
    for (i = 0; i < arglen; i++) {
        char *d = (char *)g + 0x40C;
        d[i] = arg[i];
    }
    g[0x204] = arglen;
    g[0x203] = cmd;
    buf.maxCount = 1;
    buf.initCount = 0;
    buf.option = 0;
    h = CreateSema(&buf);
    g[0x206] = buflen;
    *(void **)(g + 1) = &result;
    g[2] = 4;
    *(void **)(g + 0x205) = bufp;
    g[0] = h;
    func_0017E190((s32 *)&D_003128C0, 0x81C);
    rc = sceSifCallRpc(&D_00313B80, 0x17, 0, (s32 *)&D_003128C0, 0x81C, &D_00313500, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _cleanup();
        return -0xB;
    }
    uv = *(s32 *)((s32)&D_00313500 | 0x20000000);
    _cleanup();
    if (uv == 0) {
        DeleteSema(h);
        return -0xB;
    }
    WaitSema(h);
    DeleteSema(h);
    return result;
}

/* sceSymlink: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

s32 func_00182490(u8 *existing, u8 *newpath) {
    s32 *g = (s32 *)&D_003128C0;
    s32 uv;
    s32 h;
    s32 rc;
    s32 i;
    s32 result;
    struct SemaParam buf;

    ((s32 (*)(s32))func_0017F708)(0x11);
    if (D_0028CAA0 == 0) {
        func_0017F808();
    }
    for (i = 0; i < 0x400; i++) {
        *((char *)g + i + 0xC) = existing[i];
        if (*((char *)g + i + 0xC) == 0) {
            break;
        }
    }
    if (i == 0x400) {
        ((char *)g)[0x40B] = 0;
    }
    for (i = 0; i < 0x400; i++) {
        char *d = (char *)g + 0x40C;
        d[i] = newpath[i];
        if (d[i] == 0) {
            break;
        }
    }
    if (i == 0x400) {
        ((char *)g)[0x80B] = 0;
    }
    buf.maxCount = 1;
    buf.initCount = 0;
    buf.option = 0;
    g[0] = h = CreateSema(&buf);
    *(void **)(g + 1) = &result;
    g[2] = 4;
    rc = sceSifCallRpc(&D_00313B80, 0x18, 0, (s32 *)&D_003128C0, 0x80C, &D_00313500, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _cleanup();
        return -0xB;
    }
    uv = *(s32 *)((s32)&D_00313500 | 0x20000000);
    _cleanup();
    if (uv == 0) {
        DeleteSema(h);
        return -0xB;
    }
    WaitSema(h);
    DeleteSema(h);
    return result;
}

/* sceReadlink: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

s32 func_00182670(u8 *name, void *buf, u32 len) {
    FsReadlinkReq *g = (FsReadlinkReq *)&D_003128C0;
    s32 uv;
    s32 h;
    s32 rc;
    s32 i;
    s32 result;
    struct SemaParam sema;

    ((s32 (*)(s32))func_0017F708)(0x11);
    if (D_0028CAA0 == 0) {
        func_0017F808();
    }
    for (i = 0; i < 0x400; i++) {
        g->name[i] = name[i];
        if (g->name[i] == 0) {
            break;
        }
    }
    if (i == 0x400) {
        g->name[0x3FF] = 0;
    }
    if (len >= 0x400) {
        len = 0x3FF;
    }
    g->buf = buf;
    g->len = len;
    func_0017E190(buf, len);
    sema.maxCount = 1;
    sema.initCount = 0;
    sema.option = 0;
    g->sema = h = CreateSema(&sema);
    g->result = &result;
    g->mode = 4;
    rc = sceSifCallRpc(&D_00313B80, 0x19, 0, (s32 *)&D_003128C0, 0x80C, &D_00313500, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _cleanup();
        return -0xB;
    }
    uv = *(s32 *)((s32)&D_00313500 | 0x20000000);
    _cleanup();
    if (uv == 0) {
        DeleteSema(h);
        return -0xB;
    }
    WaitSema(h);
    DeleteSema(h);
    return result;
}

/* sceSifInitIopHeap: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

s32 sceSifInitIopHeap(void) {
    s32 i;
    s32 ret;
    s32 val;

    for (;;) {
        ret = sceSifBindRpc(&D_00313C40, 0x80000003, 0);
        if (ret < 0)
            return -1;
        val = ((sceSifRpcClientData *)&D_00313C40)->serve;
        if (val != 0) {
            D_0028CAB8 = 0;
            break;
        }
        i = 0x100000;
        do {
            i--;
        } while (i != -1);
    }
    return 0;
}

s32 sceSifAllocIopHeap(s32 arg0) {
    if (D_0028CAB8 < 0) {
        return 0;
    }
    D_00313CC0 = arg0;
    if (sceSifCallRpc(&D_00313C40, 1, 0, &D_00313CC0, 4, &D_00313C80, 4, 0, 0) < 0) {
        return 0;
    }
    return D_00313C80;
}

s32 func_00182930(s32 arg0, s32 arg1, s32 arg2) {
    s32 *p;

    if (D_0028CAB8 < 0) {
        return 0;
    }
    p = &D_00313CC0;
    p[0] = arg1;
    p[1] = arg0;
    p[2] = arg2;
    if (sceSifCallRpc(&D_00313C40, 4, 0, p, 0xC, &D_00313C80, 4, 0, 0) < 0) {
        return 0;
    }
    return D_00313C80;
}

s32 sceSifFreeIopHeap(s32 arg0) {
    if (D_0028CAB8 < 0) {
        return 0;
    }
    D_00313CC0 = arg0;
    if (sceSifCallRpc(&D_00313C40, 2, 0, &D_00313CC0, 4, &D_00313C80, 4, 0, 0) < 0) {
        return -1;
    }
    return D_00313C80;
}

s32 func_00182A28(s32 arg0) {
    return sceSifFreeIopHeap(arg0);
}

typedef struct IopLoadHeap_00182A48 {
    void *addr;
    char name[252];
} IopLoadHeap_00182A48;

extern IopLoadHeap_00182A48 D_00313D00;

s32 sceSifLoadIopHeap(const char *name, void *addr) {
    s32 i;

    if (D_0028CAB8 < 0) {
        return 0;
    }
    for (i = 0; i < 252; i++) {
        if ((D_00313D00.name[i] = name[i]) == 0) {
            break;
        }
    }
    if (i == 252) {
        i = 251;
        D_00313D00.name[i] = 0;
    }
    D_00313D00.addr = addr;
    D_00313D00.name[251] = 0;
    if (sceSifCallRpc(&D_00313C40, 3, 0, &D_00313D00, i + 5, &D_00313C80, 4, 0, 0) < 0) {
        return -1;
    }
    return D_00313C80;
}

extern s32 D_0028CAC0;
extern s32 D_00314028;

typedef struct IopCd_00182B38 {
    s32 unk0[9];
    s32 serve;
} IopCd_00182B38;

typedef struct IopVer_00182B38 {
    u8 b[4];
} IopVer_00182B38;

s32 _lf_bind(void) {
    s32 i;

    if (D_0028CAC0 < 0) {
        while (1) {
            if (sceSifBindRpc(&D_00314000, 0x80000006, 0) < 0) {
                return -1;
            }
            if ((*(IopCd_00182B38 *)&D_00314000).serve != 0) {
                D_0028CAC0 = 0;
                if (sceSifCallRpc(&D_00314000, 0xFF, 0, 0, 0, &D_00313E00, 4, 0, 0) < 0) {
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

s32 sceSifLoadFileReset(void) {
    D_0028CAC0 = -1;
    func_00198948(&D_00314028, 0, 4U);
    return 0;
}

/* _sceSifLoadModuleBuffer: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

s32 func_00182D00(s32 addr, s32 arglen, s32 args, s32 *ret) {
    SceLfRpcBuf *p;
    s32 r;

    if (_lf_bind() < 0) {
        return 0xFFFF0000;
    }
    if (func_00182C38() != 0) {
        return 0xFFFEFFFC;
    }
    p = (SceLfRpcBuf *)&D_00313E00;
    ((SceLfRpcBuf *)&D_00313E00)->addr = addr;
    if (args != 0) {
        if (arglen >= 0xFD) {
            p->args = *(SceLfArgBuf *)args;
            ((SceLfRpcBuf *)&D_00313E00)->arglen = 0xFC;
        } else {
            func_00198790(&p->args, (char *)args, arglen);
            p->arglen = arglen;
        }
    } else {
        p->arglen = 0;
    }
    if (sceSifCallRpc(&D_00314000, 6, 0, &D_00313E00, 0x200, &D_00313E00, 8, 0, 0) < 0) {
        return 0xFFFEFFFF;
    }
    r = ((SceLfRpcBuf *)&D_00313E00)->addr;
    *ret = ((SceLfRpcBuf *)&D_00313E00)->arglen;
    return r;
}

/* _sceSifLoadModuleBuffer (with RPC 7 here): adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

s32 func_00182F08(s32 addr, s32 arglen, s32 args, s32 *ret) {
    SceLfRpcBuf *p;
    s32 r;

    if (_lf_bind() < 0) {
        return 0xFFFF0000;
    }
    if (func_00182C38() != 0) {
        return 0xFFFEFFFC;
    }
    p = (SceLfRpcBuf *)&D_00313E00;
    ((SceLfRpcBuf *)&D_00313E00)->addr = addr;
    if (args != 0) {
        if (arglen >= 0xFD) {
            p->args = *(SceLfArgBuf *)args;
            ((SceLfRpcBuf *)&D_00313E00)->arglen = 0xFC;
        } else {
            func_00198790(&p->args, (char *)args, arglen);
            p->arglen = arglen;
        }
    } else {
        p->arglen = 0;
    }
    if (sceSifCallRpc(&D_00314000, 7, 0, &D_00313E00, 0x200, &D_00313E00, 8, 0, 0) < 0) {
        return 0xFFFEFFFF;
    }
    r = ((SceLfRpcBuf *)&D_00313E00)->addr;
    *ret = ((SceLfRpcBuf *)&D_00313E00)->arglen;
    return r;
}

s32 func_00183110(s32 arg0) {
    s32 var_v0;

    var_v0 = -0x10000;
    if (_lf_bind() < 0) {
        return var_v0;
    }
    if (func_00182C38() != 0) {
        return -0x10004;
    }
    D_00313E00 = arg0;
    if (sceSifCallRpc(&D_00314000, 8, 0, &D_00313E00, 4, &D_00313E00, 4, 0, 0) < 0) {
        var_v0 = -0x10001;
        /* Duplicate return node #7. Try simplifying control flow for better match */
        return var_v0;
    }
    return D_00313E00;
}

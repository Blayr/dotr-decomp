#include "common.h"
#include "sce/libc.h"

s32 func_00195070(s32 arg0) {
    return arg0 < 0 ? -arg0 : arg0;
}

void func_00195088(s32 arg0) {
    func_0019D3E0(arg0, 0);
}

s32 func_001950A0(const char *s) {
    return func_0019D750(s, NULL, 10);
}

void func_001950C8(s8 *arg0) {
    func_0019D750(arg0, NULL, 0xA);
}

void func_001950E8(s32 arg0, s32 arg1) {
    func_00198840(arg1, arg0);
}

void func_00195108(s32 arg0, s32 arg1) {
    s32 var_a0;
    s32 var_v0;

    var_a0 = arg0;
    var_v0 = arg1 - 1;
    if (arg1 != 0) {
        do {
            var_v0 -= 1;
            *(s8 *)var_a0 = 0;
            var_a0 += 1;
        } while (var_v0 != -1);
    }
}

void *func_00195140(void *ptr, u32 n, u32 size) {
    cal_chunk *p;
    u32 csz;
    u32 sz = n * size;
    void *mem;

    mem = (void *)func_00197EB8((s32)ptr, sz);
    if (mem == 0) {
        return 0;
    } else {
        p = (cal_chunk *)((char *)mem - 8);
        csz = p->size & ~(0x1 | 0x2);
        do {
            u32 mzsz = (csz - 4);
            if (mzsz <= 9 * sizeof(mzsz)) {
                u32 *mz = (u32 *)(mem);
                if (mzsz >= 5 * sizeof(mzsz)) {
                    *mz++ = 0;
                    *mz++ = 0;
                    if (mzsz >= 7 * sizeof(mzsz)) {
                        *mz++ = 0;
                        *mz++ = 0;
                        if (mzsz >= 9 * sizeof(mzsz)) {
                            *mz++ = 0;
                            *mz++ = 0;
                        }
                    }
                }
                *mz++ = 0;
                *mz++ = 0;
                *mz = 0;
            } else func_00198948((mem), 0, mzsz);
        } while (0);
        return mem;
    }
}

s32 func_001951F8(s32 *ptr, s32 fd) {
    s32 ret;
    D_003512F8 = 0;
    if ((ret = ((s32 (*)(s32))func_0017BFC8)(fd)) == -1 && D_003512F8 != 0)
        *ptr = D_003512F8;
    return ret;
}

#define QR_Storeinc(a, b, c) (((u16 *)a)[1] = (u16)b, ((u16 *)a)[0] = (u16)c, a++)

s32 func_00195250(i2b_Bigint *b, i2b_Bigint *S) {
    s32 n;
    s32 borrow, y;
    u32 carry, q, ys;
    u32 *bx, *bxe, *sx, *sxe;
    s32 z;
    u32 si, zs;

    n = S->wds;
    if (b->wds < n)
        return 0;
    sx = S->x;
    sxe = sx + --n;
    bx = b->x;
    bxe = bx + n;
    q = *bxe / (*sxe + 1);
    if (q) {
        borrow = 0;
        carry = 0;
        do {
            si = *sx++;
            ys = (si & 0xffff) * q + carry;
            zs = (si >> 16) * q + (ys >> 16);
            carry = zs >> 16;
            y = (*bx & 0xffff) - (ys & 0xffff) + borrow;
            borrow = y >> 16;
            z = (*bx >> 16) - (zs & 0xffff) + borrow;
            borrow = z >> 16;
            QR_Storeinc(bx, z, y);
        } while (sx <= sxe);
        if (!*bxe) {
            bx = b->x;
            while (--bxe > bx && !*bxe)
                --n;
            b->wds = n;
        }
    }
    if (func_001993C8((void *)b, (void *)S) >= 0) {
        q++;
        borrow = 0;
        carry = 0;
        bx = b->x;
        sx = S->x;
        do {
            si = *sx++;
            ys = (si & 0xffff) + carry;
            zs = (si >> 16) + (ys >> 16);
            carry = zs >> 16;
            y = (*bx & 0xffff) - (ys & 0xffff) + borrow;
            borrow = y >> 16;
            z = (*bx >> 16) - (zs & 0xffff) + borrow;
            borrow = z >> 16;
            QR_Storeinc(bx, z, y);
        } while (sx <= sxe);
        bx = b->x;
        bxe = bx + n;
        if (!*bxe) {
            while (--bxe > bx && !*bxe)
                --n;
            b->wds = n;
        }
    }
    return q;
}

INCLUDE_ASM("asm/nonmatchings/main_033b", func_00195480);

void func_001966E8(void) {
}

void func_001966F0(void) {
}

s32 func_001966F8(void) {
    return D_0028FA98;
}

typedef struct ff_reent { u8 pad0[0x38]; s32 __sdidinit; } ff_reent;
typedef struct ff_sbuf { u8 *_base; s32 _size; } ff_sbuf;
typedef struct ff_FILE {
    u8 *_p;
    s32 _r;
    s32 _w;
    s16 _flags;
    s16 _file;
    ff_sbuf _bf;
    s32 _lbfsize;
    void *_cookie;
    s32 (*_read)(void *, char *, s32);
    s32 (*_write)(void *, const char *, s32);
    u8 pad28[0x2C];
    ff_reent *_data;
} ff_FILE;

s32 func_00196708(nl_FILE *arg0) {
    ff_FILE *fp = (ff_FILE *)arg0;
    u8 *p;
    s32 n, t;

    if (fp == NULL)
        return func_00197488((u8 *)D_0028FA98, func_00196708);

    do {
        if (fp->_data == 0)
            fp->_data = (ff_reent *)D_0028FA98;
        if (!fp->_data->__sdidinit)
            func_00196A30(fp->_data);
    } while (0);

    t = fp->_flags;
    if ((t & 8) == 0 || (p = fp->_bf._base) == NULL)
        return 0;
    n = fp->_p - p;

    fp->_p = p;
    fp->_w = t & (1 | 2) ? 0 : fp->_bf._size;

    while (n > 0) {
        t = (*fp->_write)(fp->_cookie, (char *)p, n);
        if (t <= 0) {
            fp->_flags |= 0x40;
            return -1;
        }
        p += t;
        n -= t;
    }
    return 0;
}

void func_00196820(void *arg0, s16 arg1, s16 arg2, s32 arg3) {
    (*(s32 *)((u8 *)arg0 + 0x54)) = arg3;
    (*(s16 *)((u8 *)arg0 + 0xC)) = arg1;
    (*(s16 *)((u8 *)arg0 + 0xE)) = arg2;
    (*(s32 **)((u8 *)arg0 + 0x20)) = &func_0019B788;
    (*(s32 **)((u8 *)arg0 + 0x24)) = &func_0019B7F0;
    (*(s32 **)((u8 *)arg0 + 0x28)) = &func_0019B870;
    (*(void (**)(void *))((u8 *)arg0 + 0x2C)) = func_0019B8D8;
    (*(s32 *)((u8 *)arg0 + 4)) = 0;
    (*(s32 *)((u8 *)arg0 + 8)) = 0;
    (*(s32 *)((u8 *)arg0 + 0x10)) = 0;
    (*(s32 *)((u8 *)arg0 + 0x14)) = 0;
    (*(s32 *)((u8 *)arg0 + 0x18)) = 0;
    (*(void **)((u8 *)arg0 + 0x1C)) = arg0;
    (*(s32 *)arg0) = 0;
}

nl_mglue *func_00196880(s32 d, s32 n) {
    nl_mglue *g;
    nl_mFILE *p;

    g = (nl_mglue *)func_00197EB8(d, sizeof(*g) + n * sizeof(nl_mFILE));
    if (g == NULL)
        return NULL;
    p = (nl_mFILE *)(g + 1);
    g->_next = NULL;
    g->_niobs = n;
    g->_iobs = p;
    func_00198948(p, 0, n * sizeof(nl_mFILE));
    return g;
}

typedef struct sf_sbuf { u8 *_base; s32 _size; } sf_sbuf;
typedef struct sf_FILE {
    u8 *_p;
    s32 _r;
    s32 _w;
    s16 _flags;
    s16 _file;
    sf_sbuf _bf;
    s32 _lbfsize;
    u8 pad1C[0x14];
    sf_sbuf _ub;
    u8 pad38[0xC];
    sf_sbuf _lb;
    u8 pad4C[0x8];
    void *_data;
} sf_FILE;
typedef struct sf_glue { struct sf_glue *_next; s32 _niobs; sf_FILE *_iobs; } sf_glue;
typedef struct sf_reent { s32 _errno; u8 pad04[0x34]; s32 __sdidinit; u8 pad3C[0x19C]; sf_glue __sglue; } sf_reent;

void *func_001968F8(void *arg0) {
    sf_reent *d = arg0;
    sf_FILE *fp;
    s32 n;
    sf_glue *g;

    if (!d->__sdidinit)
        func_00196A30(d);
    for (g = &d->__sglue;; g = g->_next) {
        for (fp = g->_iobs, n = g->_niobs; --n >= 0; fp++)
            if (fp->_flags == 0)
                goto found;
        if (g->_next == NULL && (g->_next = (sf_glue *)func_00196880((s32)d, 4)) == NULL)
            break;
    }
    d->_errno = 12;
    return NULL;

found:
    fp->_flags = 1;
    fp->_p = NULL;
    fp->_w = 0;
    fp->_r = 0;
    fp->_bf._base = NULL;
    fp->_bf._size = 0;
    fp->_lbfsize = 0;
    fp->_file = -1;
    fp->_ub._base = NULL;
    fp->_ub._size = 0;
    fp->_lb._base = NULL;
    fp->_lb._size = 0;
    fp->_data = d;
    return fp;
}

s32 func_001969F0(s32 ptr) {
    return func_00197488(ptr, func_00196708);
}

void func_00196A10(void) {
    func_001969F0(D_0028FA98);
}

void func_00196A30(void *arg0) {
    void *temp_s1;

    temp_s1 = arg0 + 0x1E4;
    (*(s32 (**)(s32))((u8 *)arg0 + 0x3C)) = func_001969F0;
    (*(s32 *)((u8 *)arg0 + 0x38)) = 1;
    func_00196820(temp_s1, 4, 0, arg0);
    func_00196820(arg0 + 0x23C, 9, 1, arg0);
    func_00196820(arg0 + 0x294, 0xA, 2, arg0);
    (*(s32 *)((u8 *)arg0 + 0x1D8)) = 0;
    (*(void **)((u8 *)arg0 + 0x1E0)) = temp_s1;
    (*(s32 *)((u8 *)arg0 + 0x1DC)) = 3;
}

u32 func_00196AC0(void *buf, u32 size, u32 count, void *arg3) {
    fr_FILE *fp = arg3;
    u32 resid;
    char *p;
    s32 r;
    u32 total;

    if ((resid = count * size) == 0)
        return 0;
    if (fp->_r < 0)
        fp->_r = 0;
    total = resid;
    p = buf;
    while (resid > (r = fp->_r)) {
        func_00198790(p, fp->_p, r);
        fp->_p += r;
        p += r;
        resid -= r;
        if (func_0019AC68(fp)) {
            return (total - resid) / size;
        }
    }
    func_00198790(p, fp->_p, resid);
    fp->_r -= resid;
    fp->_p += resid;
    return count;
}

INCLUDE_ASM("asm/nonmatchings/main_033b", func_00196BE0);

#define SIZE_SZ (sizeof(INTERNAL_SIZE_T))
#define PREV_INUSE 0x1
#define SIZE_BITS 0x3
#define MINSIZE 16
#define chunksize(p) ((p)->size & ~(SIZE_BITS))
#define set_head(p, s) ((p)->size = (s))
#define bin_at(i) ((mchunkptr)((char *)&(D_0028FAA8[2 * (i) + 2]) - 2 * SIZE_SZ))
#define top (bin_at(0)->fd)

/* _malloc_trim_r (newlib 1.9.0 mallocr.c): adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

s32 func_00196ED8(s32 reent_ptr, u32 pad) {
    long top_size;
    long extra;
    char *current_brk;
    char *new_brk;
    unsigned long pagesz = 4096;

    func_00198A08(reent_ptr);
    top_size = chunksize(top);
    extra = ((top_size - pad - MINSIZE + (pagesz - 1)) / pagesz - 1) * pagesz;

    if (extra < (long)pagesz) {
        ((void (*)(s32))func_00198A88)(reent_ptr);
        return 0;
    } else {
        current_brk = (char *)(func_0019B0A0((s32 *)reent_ptr, 0));
        if (current_brk != (char *)(top) + top_size) {
            ((void (*)(s32))func_00198A88)(reent_ptr);
            return 0;
        } else {
            new_brk = (char *)(func_0019B0A0((s32 *)reent_ptr, -extra));
            if (new_brk == (char *)(-1)) {
                current_brk = (char *)(func_0019B0A0((s32 *)reent_ptr, 0));
                top_size = current_brk - (char *)top;
                if (top_size >= (long)MINSIZE) {
                    D_0028FED8.arena = current_brk - D_0028FEC0;
                    set_head(top, top_size | PREV_INUSE);
                }
                ((void (*)(s32))func_00198A88)(reent_ptr);
                return 0;
            } else {
                set_head(top, (top_size - extra) | PREV_INUSE);
                D_0028FED8.arena -= extra;
                ((void (*)(s32))func_00198A88)(reent_ptr);
                return 1;
            }
        }
    }
}

#undef SIZE_SZ
#undef PREV_INUSE
#undef SIZE_BITS
#undef MINSIZE
#undef chunksize
#undef set_head
#undef bin_at
#undef top

s32 func_00197048(s32 *ptr, s32 fd, void *st) {
    s32 ret;
    D_003512F8 = 0;
    if ((ret = func_0017C098(fd, st)) == -1 && D_003512F8 != 0)
        *ptr = D_003512F8;
    return ret;
}

#define MIN_001970A8(a, b) ((a) < (b) ? (a) : (b))
#define COPY_001970A8(n) (void)((void *(*)(void *, const void *, s32))func_00198840)((void *)fp->p, (void *)p, (int)(n))
#define GETIOV_001970A8(extra_work)                                                                \
    while (len == 0) {                                                                             \
        extra_work;                                                                                \
        p = iov->iov_base;                                                                         \
        len = iov->iov_len;                                                                        \
        iov++;                                                                                     \
    }

/* __sfvwrite (newlib 1.9.0 fvwrite.c): adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

s32 func_001970A8(void *arg0, void *arg1) {
    extern void *func_00198618();
    Fil *fp = arg0;
    struct __suio *uio = arg1;
    unsigned int len;
    const char *p;
    struct __siov *iov;
    int w, s;
    char *nl;
    int nlknown, nldist;

    if ((len = uio->uio_resid) == 0) {
        return 0;
    }
    if (((fp->flags & 0x0008) == 0 || fp->bf.base == 0) && func_001A04D8(fp)) {
        return -1;
    }

    iov = uio->uio_iov;
    len = 0;
    w = 0;
    if (fp->flags & 0x0002) {
        do {
            GETIOV_001970A8(;);
            w = (*fp->write)(fp->cookie, p, MIN_001970A8(len, 1024));
            if (w <= 0) {
                goto err;
            }
            p += w;
            len -= w;
        } while ((uio->uio_resid -= w) != 0);
    } else if ((fp->flags & 0x0001) == 0) {
        do {
            GETIOV_001970A8(;);
            w = fp->w;
            if (fp->flags & 0x0200) {
                if (len < w) {
                    w = len;
                }
                COPY_001970A8(w);
                fp->w -= w;
                fp->p += w;
                w = len;
            } else if (fp->p > fp->bf.base && len > w) {
                COPY_001970A8(w);
                fp->p += w;
                if (func_00196708((nl_FILE *)fp)) {
                    goto err;
                }
            } else if (len >= (w = fp->bf.size)) {
                w = (*fp->write)(fp->cookie, p, w);
                if (w <= 0) {
                    goto err;
                }
            } else {
                w = len;
                COPY_001970A8(w);
                fp->w -= w;
                fp->p += w;
            }
            p += w;
            len -= w;
        } while ((uio->uio_resid -= w) != 0);
    } else {
        nlknown = 0;
        do {
            GETIOV_001970A8(nlknown = 0);
            if (!nlknown) {
                nl = ((void *(*)(const void *, s32, u32))func_00198618)((void *)p, '\n', len);
                nldist = nl ? nl + 1 - p : len + 1;
                nlknown = 1;
            }
            s = MIN_001970A8(len, nldist);
            w = fp->w + fp->bf.size;
            if (fp->p > fp->bf.base && s > w) {
                COPY_001970A8(w);
                fp->p += w;
                if (func_00196708((nl_FILE *)fp)) {
                    goto err;
                }
            } else if (s >= (w = fp->bf.size)) {
                w = (*fp->write)(fp->cookie, p, w);
                if (w <= 0) {
                    goto err;
                }
            } else {
                w = s;
                COPY_001970A8(w);
                fp->w -= w;
                fp->p += w;
            }
            if ((nldist -= w) == 0) {
                if (func_00196708((nl_FILE *)fp)) {
                    goto err;
                }
                nlknown = 0;
            }
            p += w;
            len -= w;
        } while ((uio->uio_resid -= w) != 0);
    }
    return 0;

err:
    fp->flags |= 0x0040;
    return -1;
}

#undef MIN_001970A8
#undef COPY_001970A8
#undef GETIOV_001970A8

s32 func_00197488(u8 *ptr, s32 (*function)(nl_FILE *)) {
    nl_FILE *fp;
    s32 n, ret = 0;
    nl_glue *g;

    for (g = (nl_glue *)(ptr + 0x1D8); g != NULL; g = g->_next)
        for (fp = g->_iobs, n = g->_niobs; --n >= 0; fp++)
            if (fp->_flags != 0)
                ret |= (*function)(fp);
    return ret;
}

void func_00197520(s32 arg0, s32 arg1) {
    func_00197570(D_0028FA98, arg0, arg1);
}

u8 *func_00197548(s32 arg0) {
    s32 sp0[4];
    return func_00197570(D_0028FA98, arg0, (s32) sp0);
}

INCLUDE_ASM("asm/nonmatchings/main_033b", func_00197570);

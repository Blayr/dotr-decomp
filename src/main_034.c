#include "common.h"

void func_001976B8(s32 arg0, s32 arg1) {
    s32 sp0[4];
    func_00197570(arg0, arg1, (s32) sp0);
}

char *func_001976D8(char *arg0, s32 arg1) {
    return func_0019BB00(arg0, arg1);
}

s32 func_001976F0(s32 p, s32 category, s32 locale) {
    if (locale) {
        if (func_0019BC90((const char *)locale, D_002BD270) && func_0019BC90((const char *)locale, D_002BD260))
            return 0;
        *(s32 *)(p + 0x30) = category;
        *(s32 *)(p + 0x34) = locale;
    }
    return (s32)D_002BD270;
}

s32 *func_00197780(void) {
    return &D_002BD230;
}

void func_00197790(s32 arg0, s32 arg1) {
    func_001976F0(D_0028FA98, arg0, arg1);
}

s32 *func_001977B8(void) {
    return ((s32 *(*)(s32))func_00197780)(D_0028FA98);
}

s32 func_001977D8(s32 *ptr, s32 fd, s32 pos, s32 whence) {
    s32 ret;
    D_003512F8 = 0;
    if ((ret = ((s32 (*)(s32, s32, s32))func_0017BFD8)(fd, pos, whence)) == -1 && D_003512F8 != 0)
        *ptr = D_003512F8;
    return ret;
}

typedef struct mb_reent { u8 pad0[0x3C]; s32 (*__cleanup)(s32); } mb_reent;
typedef struct mb_sbuf { u8 *_base; s32 _size; } mb_sbuf;
typedef struct mb_FILE {
    u8 *_p;
    s32 _r;
    s32 _w;
    s16 _flags;
    s16 _file;
    mb_sbuf _bf;
    s32 _lbfsize;
    void *_cookie;
    void *_read;
    void *_write;
    void *_seek;
    void *_close;
    mb_sbuf _ub;
    u8 *_up;
    s32 _ur;
    u8 _ubuf[3];
    u8 _nbuf[1];
    mb_sbuf _lb;
    s32 _blksize;
    s32 _offset;
    mb_reent *_data;
} mb_FILE;
typedef struct mb_stat { s16 st_dev; u16 st_ino; u32 st_mode; u8 pad8[0x68]; } mb_stat;

void func_00197838(void *arg0) {
    mb_FILE *fp = arg0;
    u32 size, couldbetty;
    void *p;
    mb_stat st;

    if (fp->_flags & 2) {
        fp->_bf._base = fp->_p = fp->_nbuf;
        fp->_bf._size = 1;
        return;
    }
    if (fp->_file < 0 || func_00197048((s32 *)fp->_data, fp->_file, &st) < 0) {
        couldbetty = 0;
        size = 1024;
        fp->_flags |= 0x800;
    } else {
        couldbetty = (st.st_mode & 0xF000) == 0x2000;
        size = 1024;
        if ((st.st_mode & 0xF000) == 0x8000 && fp->_seek == (void *)func_0019B870) {
            fp->_flags |= 0x400;
            fp->_blksize = 1024;
        } else
            fp->_flags |= 0x800;
    }
    if ((p = (void *)func_00197EB8((s32)fp->_data, size)) == NULL) {
        fp->_flags |= 2;
        fp->_bf._base = fp->_p = fp->_nbuf;
        fp->_bf._size = 1;
    } else {
        fp->_data->__cleanup = func_001969F0;
        fp->_flags |= 0x80;
        fp->_bf._base = fp->_p = (u8 *)p;
        fp->_bf._size = size;
        if (couldbetty && ((s32 (*)(s32))func_0017C090)(fp->_file))
            fp->_flags |= 1;
    }
}

void *func_00197990(s32 arg0, s32 arg1) {
    void *temp_s1;

    func_00198A08(D_0028FA98);
    temp_s1 = func_001979F8(D_0028FA98, arg0, arg1);
    func_00198A88(D_0028FA98);
    return temp_s1;
}

INCLUDE_ASM("asm/nonmatchings/main_034", func_001979F8);

s32 func_00197BC0(s32 arg0) {
    s32 temp_s1;

    func_00198A08(D_0028FA98);
    temp_s1 = func_00197EB8(D_0028FA98, arg0);
    func_00198A88(D_0028FA98);
    return temp_s1;
}

s32 func_00197C18(s32 arg0) {
    func_00198A08(D_0028FA98);
    func_00196BE0(D_0028FA98, arg0);
    return func_00198A88(D_0028FA98);
}

INCLUDE_ASM("asm/nonmatchings/main_034", func_00197C60);

INCLUDE_ASM("asm/nonmatchings/main_034", func_00197EB8);

s32 func_001985E0(void *r, s32 *pwc, const char *s, u32 n, s32 *state) {
    s32 dummy;
    u8 *t = (u8 *)s;

    if (pwc == NULL)
        pwc = &dummy;
    if (s != NULL && n == 0)
        return -1;
    if (s == NULL)
        return 0;
    *pwc = (s32)*t;
    return (*t != '\0');
}

INCLUDE_ASM("asm/nonmatchings/main_034", func_00198618);

INCLUDE_ASM("asm/nonmatchings/main_034", func_001986F8);

INCLUDE_ASM("asm/nonmatchings/main_034", func_00198790);

INCLUDE_ASM("asm/nonmatchings/main_034", func_00198840);

INCLUDE_ASM("asm/nonmatchings/main_034", func_00198948);

void func_00198A08(s32 r) {
    s32 id = func_0017B7D0();

    if (D_0028FF00 == id) {
        D_0028FF04++;
    } else {
        func_0017B920(D_0028D114);
        D_0028FF00 = id;
        D_0028FF04++;
    }
}

s32 func_00198A88(s32 r) {
    if (--D_0028FF04 == 0) {
        D_0028FF00 = -1;
        return ((s32 (*)(s32))func_0017B900)(D_0028D114);
    }
}

i2b_Bigint *func_00198AD8(void *ptr, s32 k) {
    s32 x;
    i2b_Bigint *rv;

    if (*(i2b_Bigint ***)((u8 *)ptr + 0x4C) == NULL) {
        *(i2b_Bigint ***)((u8 *)ptr + 0x4C) = (i2b_Bigint **)func_00195140(ptr, sizeof(i2b_Bigint *), 15 + 1);
        if (*(i2b_Bigint ***)((u8 *)ptr + 0x4C) == NULL)
            return NULL;
    }
    if ((rv = (*(i2b_Bigint ***)((u8 *)ptr + 0x4C))[k]) != 0) {
        (*(i2b_Bigint ***)((u8 *)ptr + 0x4C))[k] = rv->next;
    } else {
        x = 1 << k;
        rv = (i2b_Bigint *)func_00195140(ptr, 1, sizeof(i2b_Bigint) + (x - 1) * sizeof(rv->x));
        if (rv == NULL) return NULL;
        rv->k = k;
        rv->maxwds = x;
    }
    rv->sign = rv->wds = 0;
    return rv;
}

void func_00198B80(void *arg0, void *arg1) {
    void **temp_v0;

    if (arg1 != NULL) {
        temp_v0 = ((*(s32 *)((u8 *)arg1 + 4)) * 4) + (*(s32 *)((u8 *)arg0 + 0x4C));
        (*(void **)arg1) = (void *) *temp_v0;
        *temp_v0 = arg1;
    }
}

i2b_Bigint *func_00198BB0(void *ptr, i2b_Bigint *b, s32 m, s32 a) {
    s32 i, wds;
    u32 *x, y;
    u32 xi, z;
    i2b_Bigint *b1;

    wds = b->wds;
    x = b->x;
    i = 0;
    do {
        xi = *x;
        y = (xi & 0xffff) * m + a;
        z = (xi >> 16) * m + (y >> 16);
        a = (s32)(z >> 16);
        *x++ = (z << 16) + (y & 0xffff);
    } while (++i < wds);
    if (a) {
        if (wds >= b->maxwds) {
            b1 = func_00198AD8(ptr, b->k + 1);
            func_00198790((char *)&b1->sign, (char *)&b->sign, b->wds * sizeof(s32) + 2 * sizeof(s32));
            func_00198B80(ptr, b);
            b = b1;
        }
        b->x[wds++] = a;
        b->wds = wds;
    }
    return b;
}

i2b_Bigint *func_00198CB8(void *ptr, const char *s, s32 nd0, s32 nd, u32 y9) {
    i2b_Bigint *b;
    s32 i, k;
    s32 x, y;

    x = (nd + 8) / 9;
    for (k = 0, y = 1; x > y; y <<= 1, k++);
    b = func_00198AD8(ptr, k);
    b->x[0] = y9;
    b->wds = 1;

    i = 9;
    if (9 < nd0) {
        s += 9;
        do
            b = func_00198BB0(ptr, b, 10, *s++ - '0');
        while (++i < nd0);
        s++;
    } else
        s += 10;
    for (; i < nd; i++)
        b = func_00198BB0(ptr, b, 10, *s++ - '0');
    return b;
}

s32 func_00198DE8(u32 x) {
    s32 k = 0;

    if (!(x & 0xffff0000)) {
        k = 16;
        x <<= 16;
    }
    if (!(x & 0xff000000)) {
        k += 8;
        x <<= 8;
    }
    if (!(x & 0xf0000000)) {
        k += 4;
        x <<= 4;
    }
    if (!(x & 0xc0000000)) {
        k += 2;
        x <<= 2;
    }
    if (!(x & 0x80000000)) {
        k++;
        if (!(x & 0x40000000))
            return 32;
    }
    return k;
}

s32 func_00198E68(u32 *y) {
    s32 k;
    u32 x = *y;

    if (x & 7) {
        if (x & 1)
            return 0;
        if (x & 2) {
            *y = x >> 1;
            return 1;
        }
        *y = x >> 2;
        return 2;
    }
    k = 0;
    if (!(x & 0xffff)) {
        k = 16;
        x >>= 16;
    }
    if (!(x & 0xff)) {
        k += 8;
        x >>= 8;
    }
    if (!(x & 0xf)) {
        k += 4;
        x >>= 4;
    }
    if (!(x & 0x3)) {
        k += 2;
        x >>= 2;
    }
    if (!(x & 1)) {
        k++;
        x >>= 1;
        if (!x & 1)
            return 32;
    }
    *y = x;
    return k;
}

i2b_Bigint *func_00198F28(void *ptr, s32 i) {
    i2b_Bigint *b;

    b = func_00198AD8(ptr, 1);
    b->x[0] = i;
    b->wds = 1;
    return b;
}

INCLUDE_ASM("asm/nonmatchings/main_034", func_00198F60);

i2b_Bigint *func_00199170(void *arg0, i2b_Bigint *b, s32 k) {
    p5_reent *ptr = arg0;
    i2b_Bigint *b1, *p5, *p51;
    s32 i;

    if ((i = k & 3))
        b = func_00198BB0(ptr, b, D_002BD274[i], 0);

    if (!(k >>= 2))
        return b;
    if (!(p5 = ptr->_p5s)) {
        p5 = ptr->_p5s = func_00198F28(ptr, 625);
        p5->next = 0;
    }
    for (;;) {
        if (k & 1) {
            b1 = func_00198F60(ptr, b, p5);
            func_00198B80(ptr, b);
            b = b1;
        }
        if (!(k >>= 1))
            break;
        if (!(p51 = p5->next)) {
            p51 = p5->next = func_00198F60(ptr, p5, p5);
            p51->next = 0;
        }
        p5 = p51;
    }
    return b;
}

INCLUDE_ASM("asm/nonmatchings/main_034", func_00199270);

s32 func_001993C8(mcmp_Bigint *a, mcmp_Bigint *b) {
    u32 *xa, *xa0, *xb, *xb0;
    s32 i, j;

    i = a->wds;
    j = b->wds;
    if (i -= j)
        return i;
    xa0 = a->x;
    xa = xa0 + j;
    xb0 = b->x;
    xb = xb0 + j;
    for (;;) {
        if (*--xa != *--xb)
            return *xa < *xb ? -1 : 1;
        if (xa <= xa0)
            break;
    }
    return 0;
}

#define md_Storeinc(a, b, c) (((u16 *)a)[1] = (u16)b, ((u16 *)a)[0] = (u16)c, a++)

i2b_Bigint *func_00199430(void *ptr, i2b_Bigint *a, i2b_Bigint *b) {
    s32 i, wa, wb;
    i2b_Bigint *c;
    s32 borrow, y;
    u32 *xa, *xae, *xb, *xbe, *xc;
    s32 z;

    i = func_001993C8((mcmp_Bigint *)a, (mcmp_Bigint *)b);
    if (!i) {
        c = func_00198AD8(ptr, 0);
        c->wds = 1;
        c->x[0] = 0;
        return c;
    }
    if (i < 0) {
        c = a;
        a = b;
        b = c;
        i = 1;
    } else
        i = 0;
    c = func_00198AD8(ptr, a->k);
    c->sign = i;
    wa = a->wds;
    xa = a->x;
    xae = xa + wa;
    wb = b->wds;
    xb = b->x;
    xbe = xb + wb;
    xc = c->x;
    borrow = 0;
    do {
        y = (*xa & 0xffff) - (*xb & 0xffff) + borrow;
        borrow = y >> 16;
        z = (*xa++ >> 16) - (*xb++ >> 16) + borrow;
        borrow = z >> 16;
        md_Storeinc(xc, z, y);
    } while (xb < xbe);
    while (xa < xae) {
        y = (*xa & 0xffff) + borrow;
        borrow = y >> 16;
        z = (*xa++ >> 16) + borrow;
        borrow = z >> 16;
        md_Storeinc(xc, z, y);
    }
    while (!*--xc)
        wa--;
    c->wds = wa;
    return c;
}

double func_001995C0(double _x) {
    ulp_du x, a;
    s32 L;

    x.d = _x;
    L = (x.i[1] & 0x7ff00000) - (53 - 1) * 0x100000;
    if (L > 0) {
        a.i[1] = L;
        a.i[0] = 0;
    } else {
        L = -L >> 20;
        if (L < 20) {
            a.i[1] = 0x80000 >> L;
            a.i[0] = 0;
        } else {
            a.i[1] = 0;
            L -= 20;
            a.i[0] = L >= 31 ? 1 : 1 << (31 - L);
        }
    }
    return a.d;
}

double func_00199690(i2b_Bigint *a, s32 *e) {
    u32 *xa, *xa0, w, y, z;
    s32 k;
    b2d_du d;

    xa0 = a->x;
    xa = xa0 + a->wds;
    y = *--xa;
    k = func_00198DE8(y);
    *e = 32 - k;
    if (k < 11) {
        d.i[1] = 0x3ff00000 | y >> (11 - k);
        w = xa > xa0 ? *--xa : 0;
        d.i[0] = y << ((32 - 11) + k) | w >> (11 - k);
        goto ret_d;
    }
    z = xa > xa0 ? *--xa : 0;
    if (k -= 11) {
        d.i[1] = 0x3ff00000 | y << k | z >> (32 - k);
        y = xa > xa0 ? *--xa : 0;
        d.i[0] = z << k | y >> (32 - k);
    } else {
        d.i[1] = 0x3ff00000 | y;
        d.i[0] = z;
    }
ret_d:
    return d.d;
}

INCLUDE_ASM("asm/nonmatchings/main_034", func_00199828);

double func_001999B0(i2b_Bigint *a, i2b_Bigint *b) {
    ratio_du da, db;
    s32 k, ka, kb;

    da.d = func_00199690(a, &ka);
    db.d = func_00199690(b, &kb);
    k = ka - kb + 32 * (a->wds - b->wds);
    if (k > 0)
        da.i[1] += k * 0x100000;
    else {
        k = -k;
        db.i[1] += k * 0x100000;
    }
    return da.d / db.d;
}

double func_00199A80(s32 dig) {
    double v = 1.0;

    if (dig < 24)
        return D_002BD288[dig];
    while (dig > 0) {
        v *= 10;
        dig--;
    }
    return v;
}

s32 func_00199AF0(vf_reent *ptr, const char *fmt, ...) {
    s32 ret;
    __builtin_va_list ap;

    __builtin_stdarg_start(ap, fmt);
    ret = func_0019DDE8(ptr, *(vf_FILE **)((u8 *)ptr + 8), fmt, ap);
    __builtin_va_end(ap);
    return ret;
}

typedef __builtin_va_list va_list;
#define va_start(v, l) __builtin_stdarg_start((v), l)
#define va_end(v) __builtin_va_end(v)

void func_00199B50(const char *fmt, ...) {
    s32 ret;
    va_list ap;

    va_start(ap, fmt);
    (*(vf_FILE **)(D_0028FA98 + 8))->_data = (vf_reent *)D_0028FA98;
    ret = func_0019DD70(*(vf_FILE **)(D_0028FA98 + 8), fmt, ap);
    va_end(ap);
}

INCLUDE_ASM("asm/nonmatchings/main_034", func_00199BC0);

void func_0019A5B0(s64 arg0) {
    (*(u64 *)((u8 *)D_0028FA98 + 0xA8)) = (u64) ((u64) (arg0 << 0x20) >> 0x20);
}

s32 func_0019A5C8(void) {
    u8 *r = (u8 *)D_0028FA98;

    *(u64 *)(r + 0xA8) = *(u64 *)(r + 0xA8) * 6364136223846793005ULL + 1;
    return (s32)((*(u64 *)(r + 0xA8) >> 32) & 0x7fffffff);
}

s64 func_0019A630(s32 *ptr, s32 fd, s32 buf, s32 cnt) {
    s64 ret;
    D_003512F8 = 0;
    if ((ret = (s64)func_0017BF28(fd, buf, cnt)) == -1 && D_003512F8 != 0)
        *ptr = D_003512F8;
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/main_034", func_0019A690);

s32 func_0019AC30(void *arg0) {
    if (((*(u16 *)((u8 *)arg0 + 0xC)) & 9) == 9) {
        return func_00196708(arg0);
    }
    return 0;
}

typedef struct sr_reent { u8 pad0[0x38]; s32 __sdidinit; } sr_reent;
typedef struct sr_sbuf { u8 *_base; s32 _size; } sr_sbuf;
typedef struct sr_FILE {
    u8 *_p;
    s32 _r;
    s32 _w;
    s16 _flags;
    s16 _file;
    sr_sbuf _bf;
    s32 _lbfsize;
    void *_cookie;
    s32 (*_read)(void *, char *, s32);
    s32 (*_write)(void *, const char *, s32);
    void *_seek;
    void *_close;
    sr_sbuf _ub;
    u8 *_up;
    s32 _ur;
    u8 _ubuf[3];
    u8 _nbuf[1];
    sr_sbuf _lb;
    s32 _blksize;
    s32 _offset;
    sr_reent *_data;
} sr_FILE;

s32 func_0019AC68(void *arg0) {
    sr_FILE *fp = arg0;

    do {
        if (fp->_data == 0)
            fp->_data = (sr_reent *)D_0028FA98;
        if (!fp->_data->__sdidinit)
            func_00196A30(fp->_data);
    } while (0);

    fp->_r = 0;

    if (fp->_flags & 0x20)
        return -1;

    if ((fp->_flags & 4) == 0) {
        if ((fp->_flags & 0x10) == 0)
            return -1;
        if (fp->_flags & 8) {
            if (func_00196708((nl_FILE *)fp))
                return -1;
            fp->_flags &= ~8;
            fp->_w = 0;
            fp->_lbfsize = 0;
        }
        fp->_flags |= 4;
    } else {
        if (fp->_ub._base != NULL) {
            if (fp->_ub._base != fp->_ubuf)
                func_00196BE0((s32)fp->_data, (s32)fp->_ub._base);
            fp->_ub._base = NULL;
            if ((fp->_r = fp->_ur) != 0) {
                fp->_p = fp->_up;
                return 0;
            }
        }
    }

    if (fp->_bf._base == NULL)
        func_00197838(fp);

    if (fp->_flags & (1 | 2))
        func_00197488((u8 *)fp->_data, (s32 (*)(nl_FILE *))func_0019AC30);
    fp->_p = fp->_bf._base;
    fp->_r = (*fp->_read)(fp->_cookie, (char *)fp->_p, fp->_bf._size);
    fp->_flags &= ~0x2000;
    if (fp->_r <= 0) {
        if (fp->_r == 0)
            fp->_flags |= 0x20;
        else {
            fp->_r = 0;
            fp->_flags |= 0x40;
        }
        return -1;
    }
    return 0;
}

double func_0019ADE8(double x, double y) {
    u32 hx, hy;

    do { nl_dshape gh_u; gh_u.value = (x); (hx) = gh_u.parts.msw; } while (0);
    do { nl_dshape gh_u; gh_u.value = (y); (hy) = gh_u.parts.msw; } while (0);
    do { nl_dshape sh_u; sh_u.value = (x); sh_u.parts.msw = ((hx & 0x7fffffff) | (hy & 0x80000000)); (x) = sh_u.value; } while (0);
    return x;
}

s32 func_0019AE30(double x) {
    s32 hx, lx;

    do { nl_dshape ew_u; ew_u.value = (x); (hx) = ew_u.parts.msw; (lx) = ew_u.parts.lsw; } while (0);
    hx &= 0x7fffffff;
    hx |= (u32)(lx | (-lx)) >> 31;
    hx = 0x7ff00000 - hx;
    return 1 - (s32)((u32)(hx | (-hx)) >> 31);
}

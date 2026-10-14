#include "common.h"
#include "sce/libc.h"

s32 func_0019AE78(double x) {
    s32 hx, lx;

    do { nl_dshape ew_u; ew_u.value = (x); (hx) = ew_u.parts.msw; (lx) = ew_u.parts.lsw; } while (0);
    hx &= 0x7fffffff;
    hx |= (u32)(lx | (-lx)) >> 31;
    hx = 0x7ff00000 - hx;
    return (s32)(((u32)(hx)) >> 31);
}

#define sb_EXTRACT_WORDS(ix0, ix1, d) \
    do { nl_dshape ew_u; ew_u.value = (d); (ix0) = ew_u.parts.msw; (ix1) = ew_u.parts.lsw; } while (0)
#define sb_GET_HIGH_WORD(i, d) \
    do { nl_dshape gh_u; gh_u.value = (d); (i) = gh_u.parts.msw; } while (0)
#define sb_SET_HIGH_WORD(d, v) \
    do { nl_dshape sh_u; sh_u.value = (d); sh_u.parts.msw = (v); (d) = sh_u.value; } while (0)

extern const double D_002BD3C8; /* tiny */
extern const double D_002BD3D0; /* huge */

double func_0019AEB8(double x, s32 n) {
    s32 k, hx, lx;
    sb_EXTRACT_WORDS(hx, lx, x);
    k = (hx & 0x7ff00000) >> 20;
    if (k == 0) {
        if ((lx | (hx & 0x7fffffff)) == 0)
            return x;
        x *= 1.80143985094819840000e+16;
        sb_GET_HIGH_WORD(hx, x);
        k = ((hx & 0x7ff00000) >> 20) - 54;
        if (n < -50000)
            return x * D_002BD3C8;
    }
    if (k == 0x7ff)
        return x + x;
    k = k + n;
    if (k > 0x7fe)
        return func_0019ADE8(D_002BD3D0, x) * D_002BD3D0;
    if (k > 0) {
        sb_SET_HIGH_WORD(x, (hx & 0x800fffff) | (k << 20));
        return x;
    }
    if (k <= -54) {
        if (n > 50000)
            return func_0019ADE8(D_002BD3D0, x) * D_002BD3D0;
        else
            return func_0019ADE8(D_002BD3C8, x) * D_002BD3C8;
    }
    k += 54;
    sb_SET_HIGH_WORD(x, (hx & 0x800fffff) | (k << 20));
    return x * 5.55111512312578270212e-17;
}

void *func_0019B0A0(s32 *ptr, s32 incr) {
    void *ret;
    D_003512F8 = 0;
    if ((ret = (void *)func_0017BFE0(incr)) == (void *)-1 && D_003512F8 != 0)
        *ptr = D_003512F8;
    return ret;
}

void func_0019B0F8(s32 arg0, s32 arg1, s32 arg2) {
    func_0019B148(D_0028FA98, arg0, arg1, arg2);
}

void func_0019B128(s32 arg0) {
    func_0019B418(D_0028FA98, arg0);
}

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019B148);

s32 func_0019B418(s32 reent_ptr, s32 name) {
    char **P;
    s32 offset;

    ((void (*)(s32))func_001966E8)(reent_ptr);
    while (func_00197570(reent_ptr, name, (s32)&offset))
        for (P = &(*D_0028FF08)[offset];; ++P)
            if (!(*P = *(P + 1)))
                break;
    ((void (*)(s32))func_001966F0)(reent_ptr);
}

f32 func_0019B4B8(f32 fparg0, f32 fparg1) {
    u32 gw0;
    u32 gw4;

    do { fshape gf_u; gf_u.value = (fparg0); (gw0) = gf_u.word; } while (0);
    do { fshape gf_u; gf_u.value = (fparg1); (gw4) = gf_u.word; } while (0);
    do { fshape sf_u; sf_u.word = (((gw0 & 0x7FFFFFFF) | (gw4 & 0x80000000))); (fparg0) = sf_u.value; } while (0);
    return fparg0;
}

f32 func_0019B4F8(f32 x, s32 n) {
    s32 k, ix;
    u32 hx;

    do { fshape gf_u; gf_u.value = (x); (ix) = gf_u.word; } while (0);
    hx = ix & 0x7fffffff;
    k = hx >> 23;
    if (hx < 0x00800000L)
        return x;
    if (!1)
        return x + x;
    if (0) {
        x *= (f32)33554434.0;
        do { fshape gf_u; gf_u.value = (x); (ix) = gf_u.word; } while (0);
        k = ((ix & 0x7f800000) >> 23) - 25;
        if (n < -50000) return (f32)0.0000000000000000000000000000010000000501908508838625516658847262427045785883927332161891232686912189819850027561187744140625 * x;
    }
    k = k + n;
    if (k > (0x7fffffffL >> 23)) return (f32)1000000052826398082833850564608.0 * func_0019B4B8((f32)1000000052826398082833850564608.0, x);
    if (k > 0) {
        do { fshape sf_u; sf_u.word = ((ix & 0x807fffff) | (k << 23)); (x) = sf_u.value; } while (0);
        return x;
    }
    if (k < 1) {
        if (n > 50000)
            return (f32)1000000052826398082833850564608.0 * func_0019B4B8((f32)1000000052826398082833850564608.0, x);
        else return (f32)0.0000000000000000000000000000010000000501908508838625516658847262427045785883927332161891232686912189819850027561187744140625 * func_0019B4B8((f32)0.0000000000000000000000000000010000000501908508838625516658847262427045785883927332161891232686912189819850027561187744140625, x);
    }
    k += 25;
    do { fshape sf_u; sf_u.word = ((ix & 0x807fffff) | (k << 23)); (x) = sf_u.value; } while (0);
    return x * (f32)0.0000000298023241640521519002504646778106689453125;
}

s32 func_0019B5C0(void *ptr, char *str, const char *fmt, ...) {
    s32 ret;
    __builtin_va_list ap;
    sprr_FILE f;

    f._flags = 0x0008 | 0x0200;
    f._bf_base = f._p = (u8 *)str;
    f._bf_size = f._w = 0x7fffffff;
    f._data = ptr;
    __builtin_stdarg_start(ap, fmt);
    ret = func_0019DD70((vf_FILE *)&f, fmt, ap);
    __builtin_va_end(ap);
    *f._p = 0;
    return ret;
}

s32 func_0019B648(char *str, const char *fmt, ...) {
    s32 ret;
    __builtin_va_list ap;
    spr_FILE f;

    f._flags = 0x0008 | 0x0200;
    f._bf_base = f._p = (u8 *)str;
    f._bf_size = f._w = 0x7fffffff;
    f._data = (void *)D_0028FA98;
    __builtin_stdarg_start(ap, fmt);
    ret = func_0019DD70((vf_FILE *)&f, fmt, ap);
    __builtin_va_end(ap);
    *f._p = 0;
    return ret;
}

s32 func_0019B6D8(void) {
    return 0;
}

s32 func_0019B6E0(const char *str, const char *fmt, ...) {
    s32 ret;
    __builtin_va_list ap;
    ssc_FILE f;

    f._flags = 0x0004;
    f._bf_base = f._p = (u8 *)str;
    f._bf_size = f._r = func_0019BEF0(str);
    f._read = (void *)func_0019B6D8;
    f._ub_base = NULL;
    f._lb_base = NULL;
    f._data = (void *)D_0028FA98;
    __builtin_stdarg_start(ap, fmt);
    ret = func_0019F6E8(&f, fmt, ap);
    __builtin_va_end(ap);
    return ret;
}

s32 func_0019B788(void *cookie, char *buf, s32 n) {
    sread_FILE *fp = (sread_FILE *)cookie;
    s32 ret;

    ret = func_0019A630(fp->_data, fp->_file, (s32)buf, n);
    if (ret >= 0)
        fp->_offset += ret;
    else
        fp->_flags &= ~0x1000;
    return ret;
}

s32 func_0019B7F0(void *arg0, s32 arg1, s32 arg2) {
    if ((*(u16 *)((u8 *)arg0 + 0xC)) & 0x100) {
        func_001977D8((*(s32 *)((u8 *)arg0 + 0x54)), (*(s16 *)((u8 *)arg0 + 0xE)), 0, 2);
    }
    (*(u16 *)((u8 *)arg0 + 0xC)) = (u16) ((*(s32 *)((u8 *)arg0 + 0xC)) & 0xEFFF);
    return func_001A0478((*(s32 *)((u8 *)arg0 + 0x54)), (*(s16 *)((u8 *)arg0 + 0xE)), arg1, arg2);
}

s64 func_0019B870(void *cookie, s64 offset, s32 whence) {
    sseek_FILE *fp = (sseek_FILE *)cookie;
    s64 ret;

    ret = ((s64 (*)(s32 *, s32, s64, s32))func_001977D8)(fp->_data, fp->_file, offset, whence);
    if (ret == -1L)
        fp->_flags &= ~0x1000;
    else {
        fp->_flags |= 0x1000;
        fp->_offset = ret;
    }
    return ret;
}

void func_0019B8D8(void *arg0) {
    func_001951F8((*(s32 *)((u8 *)arg0 + 0x54)), (*(s16 *)((u8 *)arg0 + 0xE)));
}

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019B8F8);

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019B9D0);

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019BB00);

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019BC90);

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019BDD8);

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019BEF0);

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019C028);

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019C100);

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019C2B8);

char *func_0019C478(const char *s, s32 i) {
    const char *last = NULL;
    char c = i;

    while (*s) {
        if (*s == c)
            last = s;
        s++;
    }
    if (*s == c)
        last = s;
    return (char *)last;
}

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019C4C8);

void func_0019D3E0(s32 arg0, s32 arg1) {
    func_0019C4C8(D_0028FA98, arg0, arg1);
}

f32 func_0019D408(s32 s, s32 ptr) {
    return ((double (*)(s32, s32))func_0019D3E0)(s, ptr);
}

char *func_0019D430(char *s, const char *delim) {
    return func_0019D450(s, delim, (char **)(D_0028FA98 + 0x5C));
}

char *func_0019D450(char *s, const char *delim, char **lasts) {
    char *spanp;
    s32 c, sc;
    char *tok;

    if (s == NULL && (s = *lasts) == NULL)
        return NULL;

cont:
    c = *s++;
    for (spanp = (char *)delim; (sc = *spanp++) != 0;) {
        if (c == sc)
            goto cont;
    }

    if (c == 0) {
        *lasts = NULL;
        return NULL;
    }
    tok = s - 1;

    for (;;) {
        c = *s++;
        spanp = (char *)delim;
        do {
            if ((sc = *spanp++) == c) {
                if (c == 0)
                    s = NULL;
                else
                    s[-1] = 0;
                *lasts = s;
                return tok;
            }
        } while (sc != 0);
    }
}

long func_0019D518(s32 rptr, const char *nptr, char **endptr, s32 base) {
    register const char *s = nptr;
    register u64 acc;
    register s32 c;
    register u64 cutoff;
    register s32 neg = 0, any, cutlim;

    do {
        c = *s++;
    } while ((D_002BD0C0 + 1)[(u32)c] & 8);
    if (c == '-') {
        neg = 1;
        c = *s++;
    } else if (c == '+')
        c = *s++;
    if ((base == 0 || base == 16) && c == '0' && (*s == 'x' || *s == 'X')) {
        c = s[1];
        s += 2;
        base = 16;
    }
    if (base == 0)
        base = c == '0' ? 8 : 10;
    cutoff = neg ? -(u64)(-0x7FFFFFFFFFFFFFFF - 1) : 0x7FFFFFFFFFFFFFFF;
    cutlim = cutoff % (u64)base;
    cutoff /= (u64)base;
    for (acc = 0, any = 0;; c = *s++) {
        if ((D_002BD0C0 + 1)[(u32)c] & 4)
            c -= '0';
        else if ((D_002BD0C0 + 1)[(u32)c] & 3)
            c -= ((D_002BD0C0 + 1)[(u32)c] & 1) ? 'A' - 10 : 'a' - 10;
        else
            break;
        if (c >= base)
            break;
        if (any < 0 || acc > cutoff || (acc == cutoff && c > cutlim))
            any = -1;
        else {
            any = 1;
            acc *= base;
            acc += c;
        }
    }
    if (any < 0) {
        acc = neg ? (-0x7FFFFFFFFFFFFFFF - 1) : 0x7FFFFFFFFFFFFFFF;
        ((sl_reent *)rptr)->_errno = 34;
    } else if (neg)
        acc = -acc;
    if (endptr != 0)
        *endptr = (char *)(any ? s - 1 : nptr);
    return acc;
}

long func_0019D750(const char *arg0, char **arg1, s32 arg2) {
    return func_0019D518(D_0028FA98, arg0, arg1, arg2);
}

u64 func_0019D780(s32 rptr, const char *nptr, char **endptr, s32 base) {
    register const char *s = nptr;
    register u64 acc;
    register s32 c;
    register u64 cutoff;
    register s32 neg = 0, any, cutlim;

    do {
        c = *s++;
    } while ((D_002BD0C0 + 1)[(u32)c] & 8);
    if (c == '-') {
        neg = 1;
        c = *s++;
    } else if (c == '+')
        c = *s++;
    if ((base == 0 || base == 16) && c == '0' && (*s == 'x' || *s == 'X')) {
        c = s[1];
        s += 2;
        base = 16;
    }
    if (base == 0)
        base = c == '0' ? 8 : 10;
    cutoff = (u64)0xFFFFFFFFFFFFFFFF / (u64)base;
    cutlim = (u64)0xFFFFFFFFFFFFFFFF % (u64)base;
    for (acc = 0, any = 0;; c = *s++) {
        if ((D_002BD0C0 + 1)[(u32)c] & 4)
            c -= '0';
        else if ((D_002BD0C0 + 1)[(u32)c] & 3)
            c -= ((D_002BD0C0 + 1)[(u32)c] & 1) ? 'A' - 10 : 'a' - 10;
        else
            break;
        if (c >= base)
            break;
        if (any < 0 || acc > cutoff || (acc == cutoff && c > cutlim))
            any = -1;
        else {
            any = 1;
            acc *= base;
            acc += c;
        }
    }
    if (any < 0) {
        acc = 0xFFFFFFFFFFFFFFFF;
        ((su_reent *)rptr)->_errno = 34;
    } else if (neg)
        acc = -acc;
    if (endptr != 0)
        *endptr = (char *)(any ? s - 1 : nptr);
    return acc;
}

void func_0019D9B0(s32 arg0, s32 arg1, s32 arg2) {
    func_0019D780(D_0028FA98, arg0, arg1, arg2);
}

s32 func_0019D9E0(s32 c) {
    return (D_002BD0C1[(u32)c] & 2) ? c - 'a' + 'A' : c;
}

typedef struct sm_buf { u8 *_base; s32 _size; } sm_buf;
typedef struct sm_FILE {
    u8 *_p;
    u8 pad04[0x2C];
    sm_buf _ub;
    u8 pad38[0x8];
    u8 _ubuf[3];
    u8 pad43[0x11];
    void *_data;
} sm_FILE;
void *func_0019A690(void *ptr, void *old, s32 size);

s32 func_0019DA00(void *arg0) {
    sm_FILE *fp = arg0;
    s32 i;
    u8 *p;

    if (fp->_ub._base == fp->_ubuf) {
        if ((p = (u8 *)func_00197EB8((s32)fp->_data, 1024)) == NULL)
            return -1;
        fp->_ub._base = p;
        fp->_ub._size = 1024;
        p += 1024 - sizeof(fp->_ubuf);
        for (i = sizeof(fp->_ubuf); --i >= 0;)
            p[i] = fp->_ubuf[i];
        fp->_p = p;
        return 0;
    }
    i = fp->_ub._size;
    p = (u8 *)func_0019A690(fp->_data, fp->_ub._base, i << 1);
    if (p == NULL)
        return -1;
    func_00198790(p + i, p, i);
    fp->_p = p + i;
    fp->_ub._base = p;
    fp->_ub._size = i << 1;
    return 0;
}

typedef struct ug_reent { u8 pad0[0x38]; s32 __sdidinit; } ug_reent;
typedef struct ug_sbuf { u8 *_base; s32 _size; } ug_sbuf;
typedef struct ug_FILE {
    u8 *_p;
    s32 _r;
    s32 _w;
    s16 _flags;
    s16 _file;
    ug_sbuf _bf;
    s32 _lbfsize;
    void *_cookie;
    void *_read;
    void *_write;
    void *_seek;
    void *_close;
    ug_sbuf _ub;
    u8 *_up;
    s32 _ur;
    u8 _ubuf[3];
    u8 _nbuf[1];
    ug_sbuf _lb;
    s32 _blksize;
    s32 _offset;
    ug_reent *_data;
} ug_FILE;

s32 func_0019DAE8(s32 c, void *arg1) {
    ug_FILE *fp = arg1;

    if (c == -1)
        return -1;

    do {
        if (fp->_data == 0)
            fp->_data = (ug_reent *)D_0028FA98;
        if (!fp->_data->__sdidinit)
            func_00196A30(fp->_data);
    } while (0);

    fp->_flags &= ~0x20;

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
    }
    c = (u8)c;

    if (fp->_ub._base != NULL) {
        if (fp->_r >= fp->_ub._size && func_0019DA00(fp))
            return -1;
        *--fp->_p = c;
        fp->_r++;
        return c;
    }

    if (fp->_bf._base != NULL && fp->_p > fp->_bf._base && fp->_p[-1] == c) {
        fp->_p--;
        fp->_r++;
        return c;
    }

    fp->_ur = fp->_r;
    fp->_up = fp->_p;
    fp->_ub._base = fp->_ubuf;
    fp->_ub._size = sizeof(fp->_ubuf);
    fp->_ubuf[sizeof(fp->_ubuf) - 1] = c;
    fp->_p = &fp->_ubuf[sizeof(fp->_ubuf) - 1];
    fp->_r = 1;
    return c;
}

s32 func_0019DC70(s32 arg0, void *arg1) {
    s32 temp_v0;

    if ((*(s32 *)((u8 *)arg1 + 8)) == 0) {
        (*(s32 *)((u8 *)arg1 + 4)) = 0;
        return 0;
    }
    temp_v0 = func_001970A8(arg0, arg1);
    (*(s32 *)((u8 *)arg1 + 8)) = 0;
    (*(s32 *)((u8 *)arg1 + 4)) = 0;
    return temp_v0;
}

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019DCB8);

s32 func_0019DD70(vf_FILE *fp, const char *fmt0, void *ap) {
    do {
        if ((fp)->_data == 0)
            (fp)->_data = (vf_reent *)D_0028FA98;
        if (!(fp)->_data->__sdidinit)
            func_00196A30((fp)->_data);
    } while (0);
    return func_0019DDE8(fp->_data, fp, fmt0, ap);
}

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019DDE8);

char *func_0019F448(void *data, double value, s32 ndigits, s32 flags, char *sign, s32 *decpt, s32 ch,
                    s32 *length) {
    extern char *func_00195480(void *, double, s32, s32, s32 *, s32 *, char **);
    s32 mode, dsgn;
    char *digits, *bp, *rve;
    cvt_du tmp;

    if (ch == 'f') {
        mode = 3;
    } else {
        if (ch == 'e' || ch == 'E') {
            ndigits++;
        }
        mode = 2;
    }

    tmp.d = value;
    if (tmp.i[1] & 0x80000000) {
        value = -value;
        *sign = '-';
    } else
        *sign = '\000';
    digits = func_00195480(data, value, mode, ndigits, decpt, &dsgn, &rve);
    if ((ch != 'g' && ch != 'G') || flags & 1) {
        bp = digits + ndigits;
        if (ch == 'f') {
            if (*digits == '0' && value)
                *decpt = -ndigits + 1;
            bp += *decpt;
        }
        if (value == 0)
            rve = bp;
        while (rve < bp)
            *rve++ = '0';
    }
    *length = rve - digits;
    return (digits);
}

s32 func_0019F608(char *p0, s32 exp, s32 fmtch) {
    char *p, *t;
    char expbuf[308];

    p = p0;
    *p++ = fmtch;
    if (exp < 0) {
        exp = -exp;
        *p++ = '-';
    } else
        *p++ = '+';
    t = expbuf + 308;
    if (exp > 9) {
        do {
            *--t = (exp % 10) + '0';
        } while ((exp /= 10) > 9);
        *--t = exp + '0';
        for (; t < expbuf + 308; *p++ = *t++);
    } else {
        *p++ = '0';
        *p++ = exp + '0';
    }
    return p - p0;
}

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019F6E8);

char *func_001A0378(char *tab, char *fmt) {
    s32 c, n, v;

    c = *fmt++;
    if (c == '^') {
        v = 1;
        c = *fmt++;
    } else
        v = 0;
    for (n = 0; n < 256; n++)
        tab[n] = v;
    if (c == 0)
        return fmt - 1;

    v = 1 - v;
    for (;;) {
        tab[c] = v;
    doswitch:
        n = *fmt++;
        switch (n) {

        case 0:
            return fmt - 1;

        case '-':
            n = *fmt;
            if (n == ']' || n < c) {
                c = '-';
                break;
            }
            fmt++;
            do {
                tab[++c] = v;
            } while (c < n);
            goto doswitch;

        case ']':
            return fmt;

        default:
            c = n;
            break;
        }
    }
}

s64 func_001A0478(s32 *ptr, s32 fd, s32 buf, s32 cnt) {
    s64 ret;
    D_003512F8 = 0;
    if ((ret = (s64)func_0017BEA8(fd, buf, cnt)) == -1 && D_003512F8 != 0)
        *ptr = D_003512F8;
    return ret;
}

typedef struct sw_reent { u8 pad0[0x38]; s32 __sdidinit; } sw_reent;
typedef struct sw_sbuf { u8 *_base; s32 _size; } sw_sbuf;
typedef struct sw_FILE {
    u8 *_p;
    s32 _r;
    s32 _w;
    s16 _flags;
    s16 _file;
    sw_sbuf _bf;
    s32 _lbfsize;
    void *_cookie;
    void *_read;
    void *_write;
    void *_seek;
    void *_close;
    sw_sbuf _ub;
    u8 *_up;
    s32 _ur;
    u8 _ubuf[3];
    u8 _nbuf[1];
    sw_sbuf _lb;
    s32 _blksize;
    s32 _offset;
    sw_reent *_data;
} sw_FILE;

s32 func_001A04D8(void *arg0) {
    sw_FILE *fp = arg0;

    do {
        if (fp->_data == 0)
            fp->_data = (sw_reent *)D_0028FA98;
        if (!fp->_data->__sdidinit)
            func_00196A30(fp->_data);
    } while (0);

    if ((fp->_flags & 8) == 0) {
        if ((fp->_flags & 0x10) == 0)
            return -1;
        if (fp->_flags & 4) {
            if (fp->_ub._base != NULL) {
                if (fp->_ub._base != fp->_ubuf)
                    func_00196BE0((s32)fp->_data, (s32)fp->_ub._base);
                fp->_ub._base = NULL;
            }
            fp->_flags &= ~(4 | 0x20);
            fp->_r = 0;
            fp->_p = fp->_bf._base;
        }
        fp->_flags |= 8;
    }

    if (fp->_bf._base == NULL)
        func_00197838(fp);

    if (fp->_flags & 1) {
        fp->_w = 0;
        fp->_lbfsize = -fp->_bf._size;
    } else
        fp->_w = fp->_flags & 2 ? 0 : fp->_bf._size;

    return 0;
}

/* __muldi3 */
typedef union { struct { s32 low, high; } s; s64 ll; } DIunion;

s64 func_001A05E8(s64 u, s64 v) {
    DIunion w;
    DIunion uu, vv;

    uu.ll = u, vv.ll = v;
    {
        DIunion __w;
        __asm__("multu %2,%3" : "=l"((u32)(__w.s.low)), "=h"((u32)(__w.s.high)) : "d"((u32)(uu.s.low)), "d"((u32)(vv.s.low)));
        w.ll = __w.ll;
    }
    w.s.high += ((u32)uu.s.low * (u32)vv.s.high + (u32)uu.s.high * (u32)vv.s.low);
    return w.ll;
}

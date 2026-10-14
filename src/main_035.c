#include "common.h"

s32 func_0019AE78(double x) {
    s32 hx, lx;

    do { nl_dshape ew_u; ew_u.value = (x); (hx) = ew_u.parts.msw; (lx) = ew_u.parts.lsw; } while (0);
    hx &= 0x7fffffff;
    hx |= (u32)(lx | (-lx)) >> 31;
    hx = 0x7ff00000 - hx;
    return (s32)(((u32)(hx)) >> 31);
}

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019AEB8);

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

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019D518);

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019D750);

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019D780);

void func_0019D9B0(s32 arg0, s32 arg1, s32 arg2) {
    func_0019D780(D_0028FA98, arg0, arg1, arg2);
}

s32 func_0019D9E0(s32 c) {
    return (D_002BD0C1[(u32)c] & 2) ? c - 'a' + 'A' : c;
}

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019DA00);

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019DAE8);

s32 func_0019DC70(s32 arg0, void *arg1) {
    s32 temp_v0;

    if ((*(s32 *)((u8 *)arg1 + 8)) == 0) {
        (*(s32 *)((u8 *)arg1 + 4)) = 0;
        return 0;
    }
    temp_v0 = func_001970A8();
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

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019F448);

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019F608);

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019F6E8);

INCLUDE_ASM("asm/nonmatchings/main_035", func_001A0378);

s64 func_001A0478(s32 *ptr, s32 fd, s32 buf, s32 cnt) {
    s64 ret;
    D_003512F8 = 0;
    if ((ret = (s64)func_0017BEA8(fd, buf, cnt)) == -1 && D_003512F8 != 0)
        *ptr = D_003512F8;
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/main_035", func_001A04D8);

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

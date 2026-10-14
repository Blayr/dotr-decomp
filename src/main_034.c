#include "common.h"

void func_001976B8(s32 arg0, s32 arg1) {
    s32 sp0[4];
    func_00197570(arg0, arg1, (s32) sp0);
}

char *func_001976D8(char *arg0, s32 arg1) {
    return func_0019BB00(arg0, arg1);
}

INCLUDE_ASM("asm/nonmatchings/main_034", func_001976F0);

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

INCLUDE_ASM("asm/nonmatchings/main_034", func_00197838);

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

INCLUDE_ASM("asm/nonmatchings/main_034", func_00198A08);

s32 func_00198A88(s32 r) {
    if (--D_0028FF04 == 0) {
        D_0028FF00 = -1;
        return ((s32 (*)(s32))func_0017B900)(D_0028D114);
    }
}

INCLUDE_ASM("asm/nonmatchings/main_034", func_00198AD8);

void func_00198B80(void *arg0, void *arg1) {
    void **temp_v0;

    if (arg1 != NULL) {
        temp_v0 = ((*(s32 *)((u8 *)arg1 + 4)) * 4) + (*(s32 *)((u8 *)arg0 + 0x4C));
        (*(void **)arg1) = (void *) *temp_v0;
        *temp_v0 = arg1;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_034", func_00198BB0);

INCLUDE_ASM("asm/nonmatchings/main_034", func_00198CB8);

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

INCLUDE_ASM("asm/nonmatchings/main_034", func_00198E68);

i2b_Bigint *func_00198F28(void *ptr, s32 i) {
    i2b_Bigint *b;

    b = func_00198AD8(ptr, 1);
    b->x[0] = i;
    b->wds = 1;
    return b;
}

INCLUDE_ASM("asm/nonmatchings/main_034", func_00198F60);

INCLUDE_ASM("asm/nonmatchings/main_034", func_00199170);

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

INCLUDE_ASM("asm/nonmatchings/main_034", func_00199430);

INCLUDE_ASM("asm/nonmatchings/main_034", func_001995C0);

INCLUDE_ASM("asm/nonmatchings/main_034", func_00199690);

INCLUDE_ASM("asm/nonmatchings/main_034", func_00199828);

INCLUDE_ASM("asm/nonmatchings/main_034", func_001999B0);

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
        return func_00196708();
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_034", func_0019AC68);

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

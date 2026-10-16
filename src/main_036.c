#include "common.h"

/* __divdi3 (libgcc2.c, __udivmoddi4 inlined; longlong.h generic udiv_qrnnd and count_leading_zeros, MIPS umul_ppmm) */

typedef struct {
    s32 low;
    s32 high;
} DIstruct_001A0660;

typedef union {
    DIstruct_001A0660 s;
    s64 ll;
} DIunion_001A0660;

extern const u8 D_002BDB30[];

#define __ll_B ((u32)1 << 16)
#define __ll_lowpart(t) ((u32)(t) & (__ll_B - 1))
#define __ll_highpart(t) ((u32)(t) >> 16)

#define sub_ddmmss(sh, sl, ah, al, bh, bl) \
    do { \
        u32 __x; \
        __x = (al) - (bl); \
        (sh) = (ah) - (bh) - (__x > (al)); \
        (sl) = __x; \
    } while (0)

#define umul_ppmm(w1, w0, u, v)     __asm__("multu %2,%3" : "=l"(w0), "=h"(w1) : "d"((u32)(u)), "d"((u32)(v)))

#define udiv_qrnnd(q, r, n1, n0, d) \
    do { \
        u32 __d1, __d0, __q1, __q0; \
        u32 __r1, __r0, __m; \
        __d1 = __ll_highpart(d); \
        __d0 = __ll_lowpart(d); \
        __r1 = (n1) % __d1; \
        __q1 = (n1) / __d1; \
        __m = (u32)__q1 * __d0; \
        __r1 = __r1 * __ll_B | __ll_highpart(n0); \
        if (__r1 < __m) { \
            __q1--, __r1 += (d); \
            if (__r1 >= (d)) \
                if (__r1 < __m) \
                    __q1--, __r1 += (d); \
        } \
        __r1 -= __m; \
        __r0 = __r1 % __d1; \
        __q0 = __r1 / __d1; \
        __m = (u32)__q0 * __d0; \
        __r0 = __r0 * __ll_B | __ll_lowpart(n0); \
        if (__r0 < __m) { \
            __q0--, __r0 += (d); \
            if (__r0 >= (d)) \
                if (__r0 < __m) \
                    __q0--, __r0 += (d); \
        } \
        __r0 -= __m; \
        (q) = (u32)__q1 * __ll_B | __q0; \
        (r) = __r0; \
    } while (0)

#define count_leading_zeros(count, x) \
    do { \
        u32 __xr = (x); \
        u32 __a; \
        __a = __xr < ((u32)1 << 16) ? (__xr < ((u32)1 << 8) ? 0 : 8) : (__xr < ((u32)1 << 24) ? 16 : 24); \
        (count) = 32 - (D_002BDB30[__xr >> __a] + __a); \
    } while (0)

static inline u64 __udivmoddi4_001A0660(u64 n, u64 d, u64 *rp) {
    DIunion_001A0660 ww;
    DIunion_001A0660 nn, dd;
    DIunion_001A0660 rr;
    u32 d0, d1, n0, n1, n2;
    u32 q0, q1;
    u32 b, bm;

    nn.ll = n;
    dd.ll = d;

    d0 = dd.s.low;
    d1 = dd.s.high;
    n0 = nn.s.low;
    n1 = nn.s.high;

    if (d1 == 0) {
        if (d0 > n1) {
            count_leading_zeros(bm, d0);

            if (bm != 0) {
                d0 = d0 << bm;
                n1 = (n1 << bm) | (n0 >> (32 - bm));
                n0 = n0 << bm;
            }

            udiv_qrnnd(q0, n0, n1, n0, d0);
            q1 = 0;
        } else {
            if (d0 == 0)
                d0 = 1 / d0;

            count_leading_zeros(bm, d0);

            if (bm == 0) {
                n1 -= d0;
                q1 = 1;
            } else {
                b = 32 - bm;

                d0 = d0 << bm;
                n2 = n1 >> b;
                n1 = (n1 << bm) | (n0 >> b);
                n0 = n0 << bm;

                udiv_qrnnd(q1, n1, n2, n1, d0);
            }

            udiv_qrnnd(q0, n0, n1, n0, d0);
        }

        if (rp != 0) {
            rr.s.low = n0 >> bm;
            rr.s.high = 0;
            *rp = rr.ll;
        }
    } else {
        if (d1 > n1) {
            q0 = 0;
            q1 = 0;

            if (rp != 0) {
                rr.s.low = n0;
                rr.s.high = n1;
                *rp = rr.ll;
            }
        } else {
            count_leading_zeros(bm, d1);
            if (bm == 0) {
                if (n1 > d1 || n0 >= d0) {
                    q0 = 1;
                    sub_ddmmss(n1, n0, n1, n0, d1, d0);
                } else
                    q0 = 0;

                q1 = 0;

                if (rp != 0) {
                    rr.s.low = n0;
                    rr.s.high = n1;
                    *rp = rr.ll;
                }
            } else {
                u32 m1, m0;

                b = 32 - bm;

                d1 = (d1 << bm) | (d0 >> b);
                d0 = d0 << bm;
                n2 = n1 >> b;
                n1 = (n1 << bm) | (n0 >> b);
                n0 = n0 << bm;

                udiv_qrnnd(q0, n1, n2, n1, d1);
                umul_ppmm(m1, m0, q0, d0);

                if (m1 > n1 || (m1 == n1 && m0 > n0)) {
                    q0--;
                    sub_ddmmss(m1, m0, m1, m0, d1, d0);
                }

                q1 = 0;

                if (rp != 0) {
                    sub_ddmmss(n1, n0, n1, n0, m1, m0);
                    rr.s.low = (n1 << b) | (n0 >> bm);
                    rr.s.high = n1 >> bm;
                    *rp = rr.ll;
                }
            }
        }
    }

    ww.s.low = q0;
    ww.s.high = q1;
    return ww.ll;
}

static inline s64 __negdi2_001A0660(s64 u) {
    DIunion_001A0660 w;
    DIunion_001A0660 uu;

    uu.ll = u;

    w.s.low = -uu.s.low;
    w.s.high = -uu.s.high - ((u32)w.s.low > 0);

    return w.ll;
}

s64 func_001A0660(s64 u, s64 v) {
    s32 c = 0;
    DIunion_001A0660 uu, vv;
    s64 w;

    uu.ll = u;
    vv.ll = v;

    if (uu.s.high < 0)
        c = ~c, uu.ll = __negdi2_001A0660(uu.ll);
    if (vv.s.high < 0)
        c = ~c, vv.ll = __negdi2_001A0660(vv.ll);

    w = __udivmoddi4_001A0660(uu.ll, vv.ll, (u64 *)0);
    if (c)
        w = __negdi2_001A0660(w);

    return w;
}

#undef __ll_B
#undef __ll_lowpart
#undef __ll_highpart
#undef sub_ddmmss
#undef umul_ppmm
#undef udiv_qrnnd
#undef count_leading_zeros

/* __moddi3 (libgcc2.c, __udivmoddi4 inlined; longlong.h generic udiv_qrnnd and count_leading_zeros, MIPS umul_ppmm) */

typedef struct {
    s32 low;
    s32 high;
} DIstruct_001A0CF8;

typedef union {
    DIstruct_001A0CF8 s;
    s64 ll;
} DIunion_001A0CF8;

extern const u8 D_002BDC30[];

#define __ll_B ((u32)1 << 16)
#define __ll_lowpart(t) ((u32)(t) & (__ll_B - 1))
#define __ll_highpart(t) ((u32)(t) >> 16)

#define sub_ddmmss(sh, sl, ah, al, bh, bl) \
    do { \
        u32 __x; \
        __x = (al) - (bl); \
        (sh) = (ah) - (bh) - (__x > (al)); \
        (sl) = __x; \
    } while (0)

#define umul_ppmm(w1, w0, u, v)     __asm__("multu %2,%3" : "=l"(w0), "=h"(w1) : "d"((u32)(u)), "d"((u32)(v)))

#define udiv_qrnnd(q, r, n1, n0, d) \
    do { \
        u32 __d1, __d0, __q1, __q0; \
        u32 __r1, __r0, __m; \
        __d1 = __ll_highpart(d); \
        __d0 = __ll_lowpart(d); \
        __r1 = (n1) % __d1; \
        __q1 = (n1) / __d1; \
        __m = (u32)__q1 * __d0; \
        __r1 = __r1 * __ll_B | __ll_highpart(n0); \
        if (__r1 < __m) { \
            __q1--, __r1 += (d); \
            if (__r1 >= (d)) \
                if (__r1 < __m) \
                    __q1--, __r1 += (d); \
        } \
        __r1 -= __m; \
        __r0 = __r1 % __d1; \
        __q0 = __r1 / __d1; \
        __m = (u32)__q0 * __d0; \
        __r0 = __r0 * __ll_B | __ll_lowpart(n0); \
        if (__r0 < __m) { \
            __q0--, __r0 += (d); \
            if (__r0 >= (d)) \
                if (__r0 < __m) \
                    __q0--, __r0 += (d); \
        } \
        __r0 -= __m; \
        (q) = (u32)__q1 * __ll_B | __q0; \
        (r) = __r0; \
    } while (0)

#define count_leading_zeros(count, x) \
    do { \
        u32 __xr = (x); \
        u32 __a; \
        __a = __xr < ((u32)1 << 16) ? (__xr < ((u32)1 << 8) ? 0 : 8) : (__xr < ((u32)1 << 24) ? 16 : 24); \
        (count) = 32 - (D_002BDC30[__xr >> __a] + __a); \
    } while (0)

static inline u64 __udivmoddi4_001A0CF8(u64 n, u64 d, u64 *rp) {
    DIunion_001A0CF8 ww;
    DIunion_001A0CF8 nn, dd;
    DIunion_001A0CF8 rr;
    u32 d0, d1, n0, n1, n2;
    u32 q0, q1;
    u32 b, bm;

    nn.ll = n;
    dd.ll = d;

    d0 = dd.s.low;
    d1 = dd.s.high;
    n0 = nn.s.low;
    n1 = nn.s.high;

    if (d1 == 0) {
        if (d0 > n1) {
            count_leading_zeros(bm, d0);

            if (bm != 0) {
                d0 = d0 << bm;
                n1 = (n1 << bm) | (n0 >> (32 - bm));
                n0 = n0 << bm;
            }

            udiv_qrnnd(q0, n0, n1, n0, d0);
            q1 = 0;
        } else {
            if (d0 == 0)
                d0 = 1 / d0;

            count_leading_zeros(bm, d0);

            if (bm == 0) {
                n1 -= d0;
                q1 = 1;
            } else {
                b = 32 - bm;

                d0 = d0 << bm;
                n2 = n1 >> b;
                n1 = (n1 << bm) | (n0 >> b);
                n0 = n0 << bm;

                udiv_qrnnd(q1, n1, n2, n1, d0);
            }

            udiv_qrnnd(q0, n0, n1, n0, d0);
        }

        if (rp != 0) {
            rr.s.low = n0 >> bm;
            rr.s.high = 0;
            *rp = rr.ll;
        }
    } else {
        if (d1 > n1) {
            q0 = 0;
            q1 = 0;

            if (rp != 0) {
                rr.s.low = n0;
                rr.s.high = n1;
                *rp = rr.ll;
            }
        } else {
            count_leading_zeros(bm, d1);
            if (bm == 0) {
                if (n1 > d1 || n0 >= d0) {
                    q0 = 1;
                    sub_ddmmss(n1, n0, n1, n0, d1, d0);
                } else
                    q0 = 0;

                q1 = 0;

                if (rp != 0) {
                    rr.s.low = n0;
                    rr.s.high = n1;
                    *rp = rr.ll;
                }
            } else {
                u32 m1, m0;

                b = 32 - bm;

                d1 = (d1 << bm) | (d0 >> b);
                d0 = d0 << bm;
                n2 = n1 >> b;
                n1 = (n1 << bm) | (n0 >> b);
                n0 = n0 << bm;

                udiv_qrnnd(q0, n1, n2, n1, d1);
                umul_ppmm(m1, m0, q0, d0);

                if (m1 > n1 || (m1 == n1 && m0 > n0)) {
                    q0--;
                    sub_ddmmss(m1, m0, m1, m0, d1, d0);
                }

                q1 = 0;

                if (rp != 0) {
                    sub_ddmmss(n1, n0, n1, n0, m1, m0);
                    rr.s.low = (n1 << b) | (n0 >> bm);
                    rr.s.high = n1 >> bm;
                    *rp = rr.ll;
                }
            }
        }
    }

    ww.s.low = q0;
    ww.s.high = q1;
    return ww.ll;
}

static inline s64 __negdi2_001A0CF8(s64 u) {
    DIunion_001A0CF8 w;
    DIunion_001A0CF8 uu;

    uu.ll = u;

    w.s.low = -uu.s.low;
    w.s.high = -uu.s.high - ((u32)w.s.low > 0);

    return w.ll;
}

s64 func_001A0CF8(s64 u, s64 v) {
    s32 c = 0;
    DIunion_001A0CF8 uu, vv;
    s64 w;

    uu.ll = u;
    vv.ll = v;

    if (uu.s.high < 0)
        c = ~c, uu.ll = __negdi2_001A0CF8(uu.ll);
    if (vv.s.high < 0)
        vv.ll = __negdi2_001A0CF8(vv.ll);

    (void)__udivmoddi4_001A0CF8(uu.ll, vv.ll, (u64 *)&w);
    if (c)
        w = __negdi2_001A0CF8(w);

    return w;
}

#undef __ll_B
#undef __ll_lowpart
#undef __ll_highpart
#undef sub_ddmmss
#undef umul_ppmm
#undef udiv_qrnnd
#undef count_leading_zeros

/* __udivdi3 (libgcc2.c, __udivmoddi4 inlined; longlong.h generic udiv_qrnnd and count_leading_zeros, MIPS umul_ppmm) */

typedef struct {
    s32 low;
    s32 high;
} DIstruct_001A1388;

typedef union {
    DIstruct_001A1388 s;
    s64 ll;
} DIunion_001A1388;

extern const u8 D_002BDD30[];

#define __ll_B ((u32)1 << 16)
#define __ll_lowpart(t) ((u32)(t) & (__ll_B - 1))
#define __ll_highpart(t) ((u32)(t) >> 16)

#define sub_ddmmss(sh, sl, ah, al, bh, bl) \
    do { \
        u32 __x; \
        __x = (al) - (bl); \
        (sh) = (ah) - (bh) - (__x > (al)); \
        (sl) = __x; \
    } while (0)

#define umul_ppmm(w1, w0, u, v)     __asm__("multu %2,%3" : "=l"(w0), "=h"(w1) : "d"((u32)(u)), "d"((u32)(v)))

#define udiv_qrnnd(q, r, n1, n0, d) \
    do { \
        u32 __d1, __d0, __q1, __q0; \
        u32 __r1, __r0, __m; \
        __d1 = __ll_highpart(d); \
        __d0 = __ll_lowpart(d); \
        __r1 = (n1) % __d1; \
        __q1 = (n1) / __d1; \
        __m = (u32)__q1 * __d0; \
        __r1 = __r1 * __ll_B | __ll_highpart(n0); \
        if (__r1 < __m) { \
            __q1--, __r1 += (d); \
            if (__r1 >= (d)) \
                if (__r1 < __m) \
                    __q1--, __r1 += (d); \
        } \
        __r1 -= __m; \
        __r0 = __r1 % __d1; \
        __q0 = __r1 / __d1; \
        __m = (u32)__q0 * __d0; \
        __r0 = __r0 * __ll_B | __ll_lowpart(n0); \
        if (__r0 < __m) { \
            __q0--, __r0 += (d); \
            if (__r0 >= (d)) \
                if (__r0 < __m) \
                    __q0--, __r0 += (d); \
        } \
        __r0 -= __m; \
        (q) = (u32)__q1 * __ll_B | __q0; \
        (r) = __r0; \
    } while (0)

#define count_leading_zeros(count, x) \
    do { \
        u32 __xr = (x); \
        u32 __a; \
        __a = __xr < ((u32)1 << 16) ? (__xr < ((u32)1 << 8) ? 0 : 8) : (__xr < ((u32)1 << 24) ? 16 : 24); \
        (count) = 32 - (D_002BDD30[__xr >> __a] + __a); \
    } while (0)

static inline u64 __udivmoddi4_001A1388(u64 n, u64 d, u64 *rp) {
    DIunion_001A1388 ww;
    DIunion_001A1388 nn, dd;
    DIunion_001A1388 rr;
    u32 d0, d1, n0, n1, n2;
    u32 q0, q1;
    u32 b, bm;

    nn.ll = n;
    dd.ll = d;

    d0 = dd.s.low;
    d1 = dd.s.high;
    n0 = nn.s.low;
    n1 = nn.s.high;

    if (d1 == 0) {
        if (d0 > n1) {
            count_leading_zeros(bm, d0);

            if (bm != 0) {
                d0 = d0 << bm;
                n1 = (n1 << bm) | (n0 >> (32 - bm));
                n0 = n0 << bm;
            }

            udiv_qrnnd(q0, n0, n1, n0, d0);
            q1 = 0;
        } else {
            if (d0 == 0)
                d0 = 1 / d0;

            count_leading_zeros(bm, d0);

            if (bm == 0) {
                n1 -= d0;
                q1 = 1;
            } else {
                b = 32 - bm;

                d0 = d0 << bm;
                n2 = n1 >> b;
                n1 = (n1 << bm) | (n0 >> b);
                n0 = n0 << bm;

                udiv_qrnnd(q1, n1, n2, n1, d0);
            }

            udiv_qrnnd(q0, n0, n1, n0, d0);
        }

        if (rp != 0) {
            rr.s.low = n0 >> bm;
            rr.s.high = 0;
            *rp = rr.ll;
        }
    } else {
        if (d1 > n1) {
            q0 = 0;
            q1 = 0;

            if (rp != 0) {
                rr.s.low = n0;
                rr.s.high = n1;
                *rp = rr.ll;
            }
        } else {
            count_leading_zeros(bm, d1);
            if (bm == 0) {
                if (n1 > d1 || n0 >= d0) {
                    q0 = 1;
                    sub_ddmmss(n1, n0, n1, n0, d1, d0);
                } else
                    q0 = 0;

                q1 = 0;

                if (rp != 0) {
                    rr.s.low = n0;
                    rr.s.high = n1;
                    *rp = rr.ll;
                }
            } else {
                u32 m1, m0;

                b = 32 - bm;

                d1 = (d1 << bm) | (d0 >> b);
                d0 = d0 << bm;
                n2 = n1 >> b;
                n1 = (n1 << bm) | (n0 >> b);
                n0 = n0 << bm;

                udiv_qrnnd(q0, n1, n2, n1, d1);
                umul_ppmm(m1, m0, q0, d0);

                if (m1 > n1 || (m1 == n1 && m0 > n0)) {
                    q0--;
                    sub_ddmmss(m1, m0, m1, m0, d1, d0);
                }

                q1 = 0;

                if (rp != 0) {
                    sub_ddmmss(n1, n0, n1, n0, m1, m0);
                    rr.s.low = (n1 << b) | (n0 >> bm);
                    rr.s.high = n1 >> bm;
                    *rp = rr.ll;
                }
            }
        }
    }

    ww.s.low = q0;
    ww.s.high = q1;
    return ww.ll;
}

u64 func_001A1388(u64 n, u64 d) {
    return __udivmoddi4_001A1388(n, d, (u64 *)0);
}

#undef __ll_B
#undef __ll_lowpart
#undef __ll_highpart
#undef sub_ddmmss
#undef umul_ppmm
#undef udiv_qrnnd
#undef count_leading_zeros

/* __umoddi3 (libgcc2.c, __udivmoddi4 inlined; longlong.h generic udiv_qrnnd and count_leading_zeros, MIPS umul_ppmm) */

typedef struct {
    s32 low;
    s32 high;
} DIstruct_001A1908;

typedef union {
    DIstruct_001A1908 s;
    s64 ll;
} DIunion_001A1908;

extern const u8 D_002BDE30[];

#define __ll_B ((u32)1 << 16)
#define __ll_lowpart(t) ((u32)(t) & (__ll_B - 1))
#define __ll_highpart(t) ((u32)(t) >> 16)

#define sub_ddmmss(sh, sl, ah, al, bh, bl) \
    do { \
        u32 __x; \
        __x = (al) - (bl); \
        (sh) = (ah) - (bh) - (__x > (al)); \
        (sl) = __x; \
    } while (0)

#define umul_ppmm(w1, w0, u, v)     __asm__("multu %2,%3" : "=l"(w0), "=h"(w1) : "d"((u32)(u)), "d"((u32)(v)))

#define udiv_qrnnd(q, r, n1, n0, d) \
    do { \
        u32 __d1, __d0, __q1, __q0; \
        u32 __r1, __r0, __m; \
        __d1 = __ll_highpart(d); \
        __d0 = __ll_lowpart(d); \
        __r1 = (n1) % __d1; \
        __q1 = (n1) / __d1; \
        __m = (u32)__q1 * __d0; \
        __r1 = __r1 * __ll_B | __ll_highpart(n0); \
        if (__r1 < __m) { \
            __q1--, __r1 += (d); \
            if (__r1 >= (d)) \
                if (__r1 < __m) \
                    __q1--, __r1 += (d); \
        } \
        __r1 -= __m; \
        __r0 = __r1 % __d1; \
        __q0 = __r1 / __d1; \
        __m = (u32)__q0 * __d0; \
        __r0 = __r0 * __ll_B | __ll_lowpart(n0); \
        if (__r0 < __m) { \
            __q0--, __r0 += (d); \
            if (__r0 >= (d)) \
                if (__r0 < __m) \
                    __q0--, __r0 += (d); \
        } \
        __r0 -= __m; \
        (q) = (u32)__q1 * __ll_B | __q0; \
        (r) = __r0; \
    } while (0)

#define count_leading_zeros(count, x) \
    do { \
        u32 __xr = (x); \
        u32 __a; \
        __a = __xr < ((u32)1 << 16) ? (__xr < ((u32)1 << 8) ? 0 : 8) : (__xr < ((u32)1 << 24) ? 16 : 24); \
        (count) = 32 - (D_002BDE30[__xr >> __a] + __a); \
    } while (0)

static inline u64 __udivmoddi4_001A1908(u64 n, u64 d, u64 *rp) {
    DIunion_001A1908 ww;
    DIunion_001A1908 nn, dd;
    DIunion_001A1908 rr;
    u32 d0, d1, n0, n1, n2;
    u32 q0, q1;
    u32 b, bm;

    nn.ll = n;
    dd.ll = d;

    d0 = dd.s.low;
    d1 = dd.s.high;
    n0 = nn.s.low;
    n1 = nn.s.high;

    if (d1 == 0) {
        if (d0 > n1) {
            count_leading_zeros(bm, d0);

            if (bm != 0) {
                d0 = d0 << bm;
                n1 = (n1 << bm) | (n0 >> (32 - bm));
                n0 = n0 << bm;
            }

            udiv_qrnnd(q0, n0, n1, n0, d0);
            q1 = 0;
        } else {
            if (d0 == 0)
                d0 = 1 / d0;

            count_leading_zeros(bm, d0);

            if (bm == 0) {
                n1 -= d0;
                q1 = 1;
            } else {
                b = 32 - bm;

                d0 = d0 << bm;
                n2 = n1 >> b;
                n1 = (n1 << bm) | (n0 >> b);
                n0 = n0 << bm;

                udiv_qrnnd(q1, n1, n2, n1, d0);
            }

            udiv_qrnnd(q0, n0, n1, n0, d0);
        }

        if (rp != 0) {
            rr.s.low = n0 >> bm;
            rr.s.high = 0;
            *rp = rr.ll;
        }
    } else {
        if (d1 > n1) {
            q0 = 0;
            q1 = 0;

            if (rp != 0) {
                rr.s.low = n0;
                rr.s.high = n1;
                *rp = rr.ll;
            }
        } else {
            count_leading_zeros(bm, d1);
            if (bm == 0) {
                if (n1 > d1 || n0 >= d0) {
                    q0 = 1;
                    sub_ddmmss(n1, n0, n1, n0, d1, d0);
                } else
                    q0 = 0;

                q1 = 0;

                if (rp != 0) {
                    rr.s.low = n0;
                    rr.s.high = n1;
                    *rp = rr.ll;
                }
            } else {
                u32 m1, m0;

                b = 32 - bm;

                d1 = (d1 << bm) | (d0 >> b);
                d0 = d0 << bm;
                n2 = n1 >> b;
                n1 = (n1 << bm) | (n0 >> b);
                n0 = n0 << bm;

                udiv_qrnnd(q0, n1, n2, n1, d1);
                umul_ppmm(m1, m0, q0, d0);

                if (m1 > n1 || (m1 == n1 && m0 > n0)) {
                    q0--;
                    sub_ddmmss(m1, m0, m1, m0, d1, d0);
                }

                q1 = 0;

                if (rp != 0) {
                    sub_ddmmss(n1, n0, n1, n0, m1, m0);
                    rr.s.low = (n1 << b) | (n0 >> bm);
                    rr.s.high = n1 >> bm;
                    *rp = rr.ll;
                }
            }
        }
    }

    ww.s.low = q0;
    ww.s.high = q1;
    return ww.ll;
}

u64 func_001A1908(u64 u, u64 v) {
    u64 w;

    (void)__udivmoddi4_001A1908(u, v, &w);

    return w;
}

#undef __ll_B
#undef __ll_lowpart
#undef __ll_highpart
#undef sub_ddmmss
#undef umul_ppmm
#undef udiv_qrnnd
#undef count_leading_zeros

/* __floatdidf */

double func_001A1E70(s64 u) {
    double d;

    d = (s32)(u >> 32);
    d *= (u64)1 << 16;
    d *= (u64)1 << 16;
    d += (u32)(u & (((u64)1 << 32) - 1));
    return d;
}

/* __floatdisf */

f32 func_001A1F18(s64 u) {
    double f;

    if (53 < 64 && 53 > (64 - 53 + 24)) {
        if (!(-((s64)1 << 53) < u && u < ((s64)1 << 53))) {
            if ((u64)u & (((u64)1 << (64 - 53)) - 1)) {
                u |= (u64)1 << (64 - 53);
            }
        }
    }
    f = (s32)(u >> 32);
    f *= (u64)1 << 16;
    f *= (u64)1 << 16;
    f += (u32)(u & (((u64)1 << 32) - 1));
    return (f32)f;
}

/* __fixunsdfdi */

u64 func_001A2000(double a) {
    double b;
    u64 v;

    if (a < 0) {
        return 0;
    }
    b = (a / ((u64)1 << 32));
    v = (u32)b;
    v <<= 32;
    a -= (double)v;
    if (a < 0) {
        v -= (u32)(-a);
    } else {
        v += (u32)a;
    }
    return v;
}

/* __fixdfdi */

s64 func_001A2118(double a) {
    if (func_001A2E60(a, 0.0) < 0) {
        return -func_001A2000(func_001A28B0(0.0, a));
    }
    return func_001A2000(a);
}

/* __pack_f */

f32 func_001A2190(fp_number_f *src) {
    fp_union_f dst;
    u32 fraction = src->fraction;
    s32 sign = src->sign;
    s32 exp = 0;

    if (fp_iszero_f(src)) {
        exp = 0;
        fraction = 0;
    } else if (fraction == 0) {
        exp = 0;
    } else {
        if (src->normal_exp < -126) {
            exp = 0;
            fraction = 0;
        } else if (src->normal_exp > 128) {
            exp = 0xFF;
            fraction = 0;
        } else {
            exp = src->normal_exp + 127;
            if ((fraction & 0x7F) == 0x40) {
                if (fraction & 0x80) {
                    fraction += 0x40;
                }
            } else {
                fraction += 0x3F;
            }
            if (fraction >= 0x80000000) {
                fraction >>= 1;
                exp += 1;
            }
            fraction >>= 7;
        }
    }
    dst.bits.fraction = fraction;
    dst.bits.exp = exp;
    dst.bits.sign = sign;
    return dst.value;
}

/* __unpack_f */

void func_001A2260(fp_union_f *src, fp_number_f *dst) {
    u32 fraction = src->bits.fraction;
    s32 exp = src->bits.exp;
    s32 sign = src->bits.sign;

    dst->sign = sign;
    if (exp == 0) {
        dst->class = CLASS_ZERO;
    } else {
        dst->normal_exp = exp - 127;
        dst->class = CLASS_NUMBER;
        dst->fraction = (fraction << 7) | 0x40000000;
    }
}

/* fptosi (float_to_si) */

s64 func_001A22C0(f32 arg_a) {
    fp_number_f a;
    s32 tmp;
    fp_union_f au;
    s32 r;

    au.value = arg_a;
    func_001A2260(&au, &a);
    if (fp_iszero_f(&a)) {
        return 0;
    }
    if (a.normal_exp < 0) {
        return 0;
    }
    if (a.normal_exp > 30) {
        r = a.sign ? (-0x7FFFFFFF - 1) : 0x7FFFFFFF;
        return r;
    }
    tmp = a.fraction >> (30 - a.normal_exp);
    r = a.sign ? (-tmp) : (tmp);
    return r;
}

/* __make_fp */
f32 func_001A2340(fp_class_type class, u32 sign, s32 exp, u32 frac) {
    fp_number_f in;

    in.class = class;
    in.sign = sign;
    in.normal_exp = exp;
    in.fraction = frac;
    return func_001A2190(&in);
}

/* fptodp (sf_to_df) */
double func_001A2370(f32 arg_a) {
    fp_number_f in;
    fp_union_f au;

    au.value = arg_a;
    func_001A2260(&au, &in);
    return func_001A3008(in.class, in.sign, in.normal_exp, ((u64)in.fraction) << 30);
}

/* fptoui (float_to_usi) */

s32 func_001A23B0(f32 arg_a) {
    fp_number_f a;
    fp_union_f au;

    au.value = arg_a;
    func_001A2260(&au, &a);
    if (fp_iszero_f(&a)) {
        return 0;
    }
    if (a.sign) {
        return 0;
    }
    if (a.normal_exp < 0) {
        return 0;
    }
    if (a.normal_exp > 31) {
        return 0xFFFFFFFF;
    } else if (a.normal_exp > 30) {
        return a.fraction << (a.normal_exp - 30);
    } else {
        return a.fraction >> (30 - a.normal_exp);
    }
}

/* __pack_d */

double func_001A2430(fp_number_d *src) {
    fp_union_d dst;
    u64 fraction = src->fraction;
    s32 sign = src->sign;
    s32 exp = 0;

    if (fp_isnan_d(src)) {
        exp = 0x7FF;
        fraction |= 0x8000000000000LL;
    } else if (fp_isinf_d(src)) {
        exp = 0x7FF;
        fraction = 0;
    } else if (fp_iszero_d(src)) {
        exp = 0;
        fraction = 0;
    } else if (fraction == 0) {
        exp = 0;
    } else {
        if (src->normal_exp < -1022) {
            exp = 0;
            fraction = 0;
        } else if (src->normal_exp > 1023) {
            exp = 0x7FF;
            fraction = 0;
        } else {
            exp = src->normal_exp + 1023;
            if ((fraction & 0xFF) == 0x80) {
                if (fraction & 0x100) {
                    fraction += 0x80;
                }
            } else {
                fraction += 0x7F;
            }
            if (fraction >= 0x2000000000000000LL) {
                fraction >>= 1;
                exp += 1;
            }
            fraction >>= 8;
        }
    }
    dst.bits.fraction = fraction;
    dst.bits.exp = exp;
    dst.bits.sign = sign;
    return dst.value;
}

/* __unpack_d */

void func_001A2548(fp_union_d *src, fp_number_d *dst) {
    u64 fraction = src->bits.fraction;
    s32 exp = src->bits.exp;
    s32 sign = src->bits.sign;

    dst->sign = sign;
    if (exp == 0) {
        dst->class = CLASS_ZERO;
    } else if (exp == 0x7FF) {
        if (fraction == 0) {
            dst->class = CLASS_INFINITY;
        } else {
            if (fraction & 0x8000000000000LL) {
                dst->class = CLASS_QNAN;
            } else {
                dst->class = CLASS_SNAN;
            }
            dst->fraction = fraction;
        }
    } else {
        dst->normal_exp = exp - 1023;
        dst->class = CLASS_NUMBER;
        dst->fraction = (fraction << 8) | 0x1000000000000000LL;
    }
}

/* _fpadd_parts */

fp_number_d *func_001A25F8(fp_number_d *a, fp_number_d *b, fp_number_d *tmp) {
    s64 tfraction;
    s32 a_normal_exp;
    s32 b_normal_exp;
    u64 a_fraction;
    u64 b_fraction;

    if (fp_isnan_d(a)) {
        return a;
    }
    if (fp_isnan_d(b)) {
        return b;
    }
    if (fp_isinf_d(a)) {
        if (fp_isinf_d(b) && a->sign != b->sign) {
            return &D_002BDF30;
        }
        return a;
    }
    if (fp_isinf_d(b)) {
        return b;
    }
    if (fp_iszero_d(b)) {
        if (fp_iszero_d(a)) {
            *tmp = *a;
            tmp->sign = a->sign & b->sign;
            return tmp;
        }
        return a;
    }
    if (fp_iszero_d(a)) {
        return b;
    }
    {
        s32 diff;

        a_normal_exp = a->normal_exp;
        b_normal_exp = b->normal_exp;
        a_fraction = a->fraction;
        b_fraction = b->fraction;

        diff = a_normal_exp - b_normal_exp;
        if (diff < 0) {
            diff = -diff;
        }
        if (diff < 64) {
            while (a_normal_exp > b_normal_exp) {
                b_normal_exp++;
                b_fraction = (b_fraction & 1) | (b_fraction >> 1);
            }
            while (b_normal_exp > a_normal_exp) {
                a_normal_exp++;
                a_fraction = (a_fraction & 1) | (a_fraction >> 1);
            }
        } else {
            if (a_normal_exp > b_normal_exp) {
                b_normal_exp = a_normal_exp;
                b_fraction = 0;
            } else {
                a_normal_exp = b_normal_exp;
                a_fraction = 0;
            }
        }
    }
    if (a->sign != b->sign) {
        if (a->sign) {
            tfraction = -a_fraction + b_fraction;
        } else {
            tfraction = a_fraction - b_fraction;
        }
        if (tfraction >= 0) {
            tmp->sign = 0;
            tmp->normal_exp = a_normal_exp;
            tmp->fraction = tfraction;
        } else {
            tmp->sign = 1;
            tmp->normal_exp = a_normal_exp;
            tmp->fraction = -tfraction;
        }
        while (tmp->fraction < 0x1000000000000000LL && tmp->fraction) {
            tmp->fraction <<= 1;
            tmp->normal_exp--;
        }
    } else {
        tmp->sign = a->sign;
        tmp->normal_exp = a_normal_exp;
        tmp->fraction = a_fraction + b_fraction;
    }
    tmp->class = CLASS_NUMBER;
    if (tmp->fraction >= 0x2000000000000000LL) {
        tmp->fraction = (tmp->fraction & 1) | (tmp->fraction >> 1);
        tmp->normal_exp++;
    }
    return tmp;
}

/* dpadd */
double func_001A2858(double arg_a, double arg_b) {
    fp_number_d a;
    fp_number_d b;
    fp_number_d tmp;
    fp_number_d *res;
    fp_union_d au, bu;

    au.value = arg_a;
    bu.value = arg_b;
    func_001A2548(&au, &a);
    func_001A2548(&bu, &b);
    res = func_001A25F8(&a, &b, &tmp);
    return func_001A2430(res);
}

/* dpsub */

double func_001A28B0(double arg_a, double arg_b) {
    fp_number_d a;
    fp_number_d b;
    fp_number_d tmp;
    fp_number_d *res;
    fp_union_d au, bu;

    au.value = arg_a;
    bu.value = arg_b;
    func_001A2548(&au, &a);
    func_001A2548(&bu, &b);
    b.sign ^= 1;
    res = func_001A25F8(&a, &b, &tmp);
    return func_001A2430(res);
}

/* dpmul, _fpmul_parts inlined. __pack_d is func_001A2430 (config/linker_syms.txt): by its
   func_ name GCC sees its body earlier in this file, which changes a branch here. */
double __pack_d(fp_number_d *src);

static __inline__ fp_number_d *_fpmul_parts(fp_number_d *a, fp_number_d *b, fp_number_d *tmp) {
    u64 low = 0;
    u64 high = 0;

    if (fp_isnan_d(a)) {
        a->sign = a->sign != b->sign;
        return a;
    }
    if (fp_isnan_d(b)) {
        b->sign = a->sign != b->sign;
        return b;
    }
    if (fp_isinf_d(a)) {
        if (fp_iszero_d(b)) {
            return &D_002BDF30;
        }
        a->sign = a->sign != b->sign;
        return a;
    }
    if (fp_isinf_d(b)) {
        if (fp_iszero_d(a)) {
            return &D_002BDF30;
        }
        b->sign = a->sign != b->sign;
        return b;
    }
    if (fp_iszero_d(a)) {
        a->sign = a->sign != b->sign;
        return a;
    }
    if (fp_iszero_d(b)) {
        b->sign = a->sign != b->sign;
        return b;
    }
    {
        u64 nl = a->fraction & 0xffffffff;
        u64 nh = a->fraction >> 32;
        u64 ml = b->fraction & 0xffffffff;
        u64 mh = b->fraction >> 32;
        u64 pp_ll = ml * nl;
        u64 pp_hl = mh * nl;
        u64 pp_lh = ml * nh;
        u64 pp_hh = mh * nh;
        u64 res2 = 0;
        u64 res0 = 0;
        u64 ps_hh__ = pp_hl + pp_lh;
        if (ps_hh__ < pp_hl) {
            res2 += 0x100000000LL;
        }
        pp_hl = (ps_hh__ << 32) & 0xffffffff00000000LL;
        res0 = pp_ll + pp_hl;
        if (res0 < pp_ll) {
            res2++;
        }
        res2 += ((ps_hh__ >> 32) & 0xffffffffL) + pp_hh;
        high = res2;
        low = res0;
    }
    tmp->normal_exp = a->normal_exp + b->normal_exp;
    tmp->sign = a->sign != b->sign;
    tmp->normal_exp += 4;
    while (high >= 0x2000000000000000LL) {
        tmp->normal_exp++;
        if (high & 1) {
            low >>= 1;
            low |= 0x8000000000000000LL;
        }
        high >>= 1;
    }
    while (high < 0x1000000000000000LL) {
        tmp->normal_exp--;
        high <<= 1;
        if (low & 0x8000000000000000LL) {
            high |= 1;
        }
        low <<= 1;
    }
    if ((high & 0xFF) == 0x80) {
        if (high & 0x100) {
            high += 0x80;
        } else if (low) {
            high += 0x80;
        }
    }
    tmp->fraction = high;
    tmp->class = CLASS_NUMBER;
    return tmp;
}

double func_001A2918(double arg_a, double arg_b) {
    fp_number_d a;
    fp_number_d b;
    fp_number_d tmp;
    fp_number_d *res;
    fp_union_d au, bu;

    au.value = arg_a;
    bu.value = arg_b;
    func_001A2548(&au, &a);
    func_001A2548(&bu, &b);
    res = _fpmul_parts(&a, &b, &tmp);
    return __pack_d(res);
}

/* dpdiv, _fpdiv_parts inlined */
static __inline__ fp_number_d *_fpdiv_parts(fp_number_d *a, fp_number_d *b) {
    u64 bit;
    u64 numerator;
    u64 denominator;
    u64 quotient;

    if (fp_isnan_d(a)) {
        return a;
    }
    if (fp_isnan_d(b)) {
        return b;
    }
    a->sign = a->sign ^ b->sign;
    if (fp_isinf_d(a) || fp_iszero_d(a)) {
        if (a->class == b->class) {
            return &D_002BDF30;
        }
        return a;
    }
    if (fp_isinf_d(b)) {
        a->fraction = 0;
        a->normal_exp = 0;
        return a;
    }
    if (fp_iszero_d(b)) {
        a->class = CLASS_INFINITY;
        return a;
    }
    {
        a->normal_exp = a->normal_exp - b->normal_exp;
        numerator = a->fraction;
        denominator = b->fraction;
        if (numerator < denominator) {
            numerator *= 2;
            a->normal_exp--;
        }
        bit = 0x1000000000000000LL;
        quotient = 0;
        while (bit) {
            if (numerator >= denominator) {
                quotient |= bit;
                numerator -= denominator;
            }
            bit >>= 1;
            numerator *= 2;
        }
        if ((quotient & 0xFF) == 0x80) {
            if (quotient & 0x100) {
                quotient += 0x80;
            } else if (numerator) {
                quotient += 0x80;
            }
        }
        a->fraction = quotient;
        return a;
    }
}

double func_001A2BC8(double arg_a, double arg_b) {
    fp_number_d a;
    fp_number_d b;
    fp_number_d *res;
    fp_union_d au, bu;

    au.value = arg_a;
    bu.value = arg_b;
    func_001A2548(&au, &a);
    func_001A2548(&bu, &b);
    res = _fpdiv_parts(&a, &b);
    return func_001A2430(res);
}

/* __fpcmp_parts_d */

s32 func_001A2D40(fp_number_d *a, fp_number_d *b) {
    if (fp_isnan_d(a) || fp_isnan_d(b)) {
        return 1;
    }
    if (fp_isinf_d(a) && fp_isinf_d(b)) {
        return b->sign - a->sign;
    }
    if (fp_isinf_d(a)) {
        return a->sign ? -1 : 1;
    }
    if (fp_isinf_d(b)) {
        return b->sign ? 1 : -1;
    }
    if (fp_iszero_d(a) && fp_iszero_d(b)) {
        return 0;
    }
    if (fp_iszero_d(a)) {
        return b->sign ? 1 : -1;
    }
    if (fp_iszero_d(b)) {
        return a->sign ? -1 : 1;
    }
    if (a->sign != b->sign) {
        return a->sign ? -1 : 1;
    }
    if (a->normal_exp > b->normal_exp) {
        return a->sign ? -1 : 1;
    }
    if (a->normal_exp < b->normal_exp) {
        return a->sign ? 1 : -1;
    }
    if (a->fraction > b->fraction) {
        return a->sign ? -1 : 1;
    }
    if (a->fraction < b->fraction) {
        return a->sign ? 1 : -1;
    }
    return 0;
}

/* dpcmp */

s32 func_001A2E60(double arg_a, double arg_b) {
    fp_number_d a;
    fp_number_d b;
    fp_union_d au, bu;

    au.value = arg_a;
    bu.value = arg_b;
    func_001A2548(&au, &a);
    func_001A2548(&bu, &b);
    return func_001A2D40(&a, &b);
}

/* litodp (si_to_float) */

double func_001A2EB0(s32 arg_a) {
    fp_number_d in;

    in.class = CLASS_NUMBER;
    in.sign = arg_a < 0;
    if (!arg_a) {
        in.class = CLASS_ZERO;
    } else {
        in.normal_exp = 60;
        if (in.sign) {
            if (arg_a == (-0x7FFFFFFF - 1)) {
                return (double)(-0x7FFFFFFF - 1);
            }
            in.fraction = (-arg_a);
        } else {
            in.fraction = arg_a;
        }
        while (in.fraction < (1LL << 60)) {
            in.fraction <<= 1;
            in.normal_exp -= 1;
        }
    }
    return func_001A2430(&in);
}

/* dptoli (float_to_si) */

s32 func_001A2F68(double arg_a) {
    fp_number_d a;
    s32 tmp;
    fp_union_d au;

    au.value = arg_a;
    func_001A2548(&au, &a);
    if (fp_iszero_d(&a)) {
        return 0;
    }
    if (fp_isnan_d(&a)) {
        return 0;
    }
    if (fp_isinf_d(&a)) {
        return a.sign ? (-0x7FFFFFFF - 1) : 0x7FFFFFFF;
    }
    if (a.normal_exp < 0) {
        return 0;
    }
    if (a.normal_exp > 30) {
        return a.sign ? (-0x7FFFFFFF - 1) : 0x7FFFFFFF;
    }
    tmp = a.fraction >> (60 - a.normal_exp);
    return a.sign ? (-tmp) : (tmp);
}

/* __make_dp */

double func_001A3008(fp_class_type class, u32 sign, s32 exp, u64 frac) {
    fp_number_d in;

    in.class = class;
    in.sign = sign;
    in.normal_exp = exp;
    in.fraction = frac;
    return func_001A2430(&in);
}

/* dptofp (df_to_sf) */

f32 func_001A3038(double arg_a) {
    fp_number_d in;
    u32 sffrac;
    fp_union_d au;

    au.value = arg_a;
    func_001A2548(&au, &in);
    sffrac = in.fraction >> 30;
    if ((in.fraction & (((u32)1 << 30) - 1)) != 0) {
        sffrac |= 1;
    }
    return func_001A2340(in.class, in.sign, in.normal_exp, sffrac);
}

/* dptoul (float_to_usi) */

u32 func_001A3090(double arg_a) {
    fp_number_d a;
    fp_union_d au;

    au.value = arg_a;
    func_001A2548(&au, &a);
    if (fp_iszero_d(&a)) {
        return 0;
    }
    if (fp_isnan_d(&a)) {
        return 0;
    }
    if (a.sign) {
        return 0;
    }
    if (fp_isinf_d(&a)) {
        return 0xFFFFFFFF;
    }
    if (a.normal_exp < 0) {
        return 0;
    }
    if (a.normal_exp > 31) {
        return 0xFFFFFFFF;
    } else if (a.normal_exp > 60) {
        return a.fraction << (a.normal_exp - 60);
    } else {
        return a.fraction >> (60 - a.normal_exp);
    }
}

/* __ieee754_pow: newlib 1.9.0 libm/math/e_pow.c (fdlibm, Sun Microsystems notice: see THIRD_PARTY_NOTICES.md)
   as cpp leaves it for this little-endian target. The tables and the huge/tiny constants are the game pool. */

double func_001A3130(double x, double y)
{
 extern const double D_002BDF48[]; /* bp */
 extern const double D_002BDF58[]; /* dp_h */
 extern const double D_002BDF68[]; /* dp_l */
 extern const double D_002BE050; /* huge*huge, folded by the compiler */
 extern const double D_002BE058; /* huge */
 extern const double D_002BE060; /* tiny */
 double z,ax,z_h,z_l,p_h,p_l;
 double y1,t1,t2,r,s,t,u,v,w;
 s32 i,j,k,yisint,n;
 s32 hx,hy,ix,iy;
 u32 lx,ly;
 do { nl_dshape ew_u; ew_u.value = (x); (hx) = ew_u.parts.msw; (lx) = ew_u.parts.lsw; } while (0);
 do { nl_dshape ew_u; ew_u.value = (y); (hy) = ew_u.parts.msw; (ly) = ew_u.parts.lsw; } while (0);
 ix = hx&0x7fffffff; iy = hy&0x7fffffff;
 if((iy|ly)==0) return (1.0);
 if(ix > 0x7ff00000 || ((ix==0x7ff00000)&&(lx!=0)) ||
    iy > 0x7ff00000 || ((iy==0x7ff00000)&&(ly!=0)))
  return x+y;
 yisint = 0;
 if(hx<0) {
     if(iy>=0x43400000) yisint = 2;
     else if(iy>=0x3ff00000) {
  k = (iy>>20)-0x3ff;
  if(k>20) {
      j = ly>>(52-k);
      if((j<<(52-k))==ly) yisint = 2-(j&1);
  } else if(ly==0) {
      j = iy>>(20-k);
      if((j<<(20-k))==iy) yisint = 2-(j&1);
  }
     }
 }
 if(ly==0) {
     if (iy==0x7ff00000) {
         if(((ix-0x3ff00000)|lx)==0)
      return y - y;
         else if (ix >= 0x3ff00000)
      return (hy>=0)? y: (0.0);
         else
      return (hy<0)?-y: (0.0);
     }
     if(iy==0x3ff00000) {
  if(hy<0) return (1.0)/x; else return x;
     }
     if(hy==0x40000000) return x*x;
     if(hy==0x3fe00000) {
  if(hx>=0)
  return func_001A4088(x);
     }
 }
 ax = func_001A65C0(x);
 if(lx==0) {
     if(ix==0x7ff00000||ix==0||ix==0x3ff00000){
  z = ax;
  if(hy<0) z = (1.0)/z;
  if(hx<0) {
      if(((ix-0x3ff00000)|yisint)==0) {
   z = (z-z)/(z-z);
      } else if(yisint==1)
   z = -z;
  }
  return z;
     }
 }
 if(((((u32)hx>>31)-1)|yisint)==0) return (x-x)/(x-x);
 if(iy>0x41e00000) {
     if(iy>0x43f00000){
  if(ix<=0x3fefffff) return (hy<0)? D_002BE050:(1e-300)*(1e-300);
  if(ix>=0x3ff00000) return (hy>0)? D_002BE050:(1e-300)*(1e-300);
     }
     if(ix<0x3fefffff) return (hy<0)? D_002BE050:(1e-300)*(1e-300);
     if(ix>0x3ff00000) return (hy>0)? D_002BE050:(1e-300)*(1e-300);
     t = x-1;
     w = (t*t)*(0.5-t*(0.333333333333333315-t*0.25));
     u = (1.4426950216293335)*t;
     v = t*(1.9259629911266175e-08)-w*(1.4426950408889634);
     t1 = u+v;
     do { nl_dshape sl_u; sl_u.value = (t1); sl_u.parts.lsw = (0); (t1) = sl_u.value; } while (0);
     t2 = v-(t1-u);
 } else {
     double s2,s_h,s_l,t_h,t_l;
     n = 0;
     if(ix<0x00100000)
  {ax *= (9007199254740992.0); n -= 53; do { nl_dshape gh_u; gh_u.value = (ax); (ix) = gh_u.parts.msw; } while (0); }
     n += ((ix)>>20)-0x3ff;
     j = ix&0x000fffff;
     ix = j|0x3ff00000;
     if(j<=0x3988E) k=0;
     else if(j<0xBB67A) k=1;
     else {k=0;n+=1;ix -= 0x00100000;}
     do { nl_dshape sh_u; sh_u.value = (ax); sh_u.parts.msw = (ix); (ax) = sh_u.value; } while (0);
     u = ax-D_002BDF48[k];
     v = (1.0)/(ax+D_002BDF48[k]);
     s = u*v;
     s_h = s;
     do { nl_dshape sl_u; sl_u.value = (s_h); sl_u.parts.lsw = (0); (s_h) = sl_u.value; } while (0);
     t_h = (0.0);
     do { nl_dshape sh_u; sh_u.value = (t_h); sh_u.parts.msw = (((ix>>1)|0x20000000)+0x00080000+(k<<18)); (t_h) = sh_u.value; } while (0);
     t_l = ax - (t_h-D_002BDF48[k]);
     s_l = v*((u-s_h*t_h)-s_h*t_l);
     s2 = s*s;
     r = s2*s2*((0.59999999999999465)+s2*((0.4285714285785501843)+s2*((0.333333329818377433)+s2*((0.27272812380853401)+s2*((0.2306607457755617541)+s2*(0.20697501780033842))))));
     r += s_l*(s_h+s);
     s2 = s_h*s_h;
     t_h = 3.0+s2+r;
     do { nl_dshape sl_u; sl_u.value = (t_h); sl_u.parts.lsw = (0); (t_h) = sl_u.value; } while (0);
     t_l = r-((t_h-3.0)-s2);
     u = s_h*t_h;
     v = s_l*t_h+t_l*s;
     p_h = u+v;
     do { nl_dshape sl_u; sl_u.value = (p_h); sl_u.parts.lsw = (0); (p_h) = sl_u.value; } while (0);
     p_l = v-(p_h-u);
     z_h = (0.96179670095443726)*p_h;
     z_l = (-7.0284616509527583e-09)*p_h+p_l*(0.96179669392597555433)+D_002BDF68[k];
     t = (double)n;
     t1 = (((z_h+z_l)+D_002BDF58[k])+t);
     do { nl_dshape sl_u; sl_u.value = (t1); sl_u.parts.lsw = (0); (t1) = sl_u.value; } while (0);
     t2 = z_l-(((t1-t)-D_002BDF58[k])-z_h);
 }
 s = (1.0);
 if(((((u32)hx>>31)-1)|(yisint-1))==0)
     s = -(1.0);
 y1 = y;
 do { nl_dshape sl_u; sl_u.value = (y1); sl_u.parts.lsw = (0); (y1) = sl_u.value; } while (0);
 p_l = (y-y1)*t1+y*t2;
 p_h = y1*t1;
 z = p_l+p_h;
 do { nl_dshape ew_u; ew_u.value = (z); (j) = ew_u.parts.msw; (i) = ew_u.parts.lsw; } while (0);
 if (j>=0x40900000) {
     if(((j-0x40900000)|i)!=0)
  return s*D_002BE058*D_002BE058;
     else {
  if(p_l+(8.008566259537294102e-17)>z-p_h) return s*D_002BE058*D_002BE058;
     }
 } else if((j&0x7fffffff)>=0x4090cc00 ) {
     if(((j-0xc090cc00)|i)!=0)
  return s*D_002BE060*D_002BE060;
     else {
  if(p_l<=z-p_h) return s*D_002BE060*D_002BE060;
     }
 }
 i = j&0x7fffffff;
 k = (i>>20)-0x3ff;
 n = 0;
 if(i>0x3fe00000) {
     n = j+(0x00100000>>(k+1));
     k = ((n&0x7fffffff)>>20)-0x3ff;
     t = (0.0);
     do { nl_dshape sh_u; sh_u.value = (t); sh_u.parts.msw = (n&~(0x000fffff>>k)); (t) = sh_u.value; } while (0);
     n = ((n&0x000fffff)|0x00100000)>>(20-k);
     if(j<0) n = -n;
     p_h -= t;
 }
 t = p_l+p_h;
 do { nl_dshape sl_u; sl_u.value = (t); sl_u.parts.lsw = (0); (t) = sl_u.value; } while (0);
 u = t*(0.69314718246459961);
 v = (p_l-(t-p_h))*(0.69314718055994529)+t*(-1.90465429995776805e-09);
 z = u+v;
 w = v-(z-u);
 t = z*z;
 t1 = z - t*((0.16666666666666602)+t*((-0.00277777777770155934)+t*((6.6137563214379344e-05)+t*((-1.6533902205465252e-06)+t*(4.1381367970572385e-08)))));
 r = (z*t1)/(t1-(2.0))-(w+z*w);
 z = (1.0)-(r-z);
 do { nl_dshape gh_u; gh_u.value = (z); (j) = gh_u.parts.msw; } while (0);
 j += (n<<20);
 if((j>>20)<=0) z = func_0019AEB8(z,(int)n);
 else do { nl_dshape sh_u; sh_u.value = (z); sh_u.parts.msw = (j); (z) = sh_u.value; } while (0);
 return s*z;
}

double func_001A4088(double x) {
    double z;
    s32 sign = (int)0x80000000;
    u32 r, t1, s1, ix1, q1;
    s32 ix0, s0, q, m, t, i;

    do { nl_dshape ew_u; ew_u.value = (x); (ix0) = ew_u.parts.msw; (ix1) = ew_u.parts.lsw; } while (0);

    if ((ix0 & 0x7ff00000) == 0x7ff00000) {
        return x * x + x;
    }
    if (ix0 <= 0) {
        if (((ix0 & (~sign)) | ix1) == 0) return x;
        else if (ix0 < 0)
            return (x - x) / (x - x);
    }
    m = (ix0 >> 20);
    if (m == 0) {
        while (ix0 == 0) {
            m -= 21;
            ix0 |= (ix1 >> 11); ix1 <<= 21;
        }
        for (i = 0; (ix0 & 0x00100000) == 0; i++) ix0 <<= 1;
        m -= i - 1;
        ix0 |= (ix1 >> (32 - i));
        ix1 <<= i;
    }
    m -= 1023;
    ix0 = (ix0 & 0x000fffff) | 0x00100000;
    if (m & 1) {
        ix0 += ix0 + ((ix1 & sign) >> 31);
        ix1 += ix1;
    }
    m >>= 1;

    ix0 += ix0 + ((ix1 & sign) >> 31);
    ix1 += ix1;
    q = q1 = s0 = s1 = 0;
    r = 0x00200000;

    while (r != 0) {
        t = s0 + r;
        if (t <= ix0) {
            s0 = t + r;
            ix0 -= t;
            q += r;
        }
        ix0 += ix0 + ((ix1 & sign) >> 31);
        ix1 += ix1;
        r >>= 1;
    }

    r = sign;
    while (r != 0) {
        t1 = s1 + r;
        t = s0;
        if ((t < ix0) || ((t == ix0) && (t1 <= ix1))) {
            s1 = t1 + r;
            if (((t1 & sign) == sign) && (s1 & sign) == 0) s0 += 1;
            ix0 -= t;
            if (ix1 < t1) ix0 -= 1;
            ix1 -= t1;
            q1 += r;
        }
        ix0 += ix0 + ((ix1 & sign) >> 31);
        ix1 += ix1;
        r >>= 1;
    }

    if ((ix0 | ix1) != 0) {
        z = 1.0 - 1.0e-300;
        if (z >= 1.0) {
            z = 1.0 + 1.0e-300;
            if (q1 == (u32)0xffffffff) { q1 = 0; q += 1; }
            else if (z > 1.0) {
                if (q1 == (u32)0xfffffffe) q += 1;
                q1 += 2;
            } else
                q1 += (q1 & 1);
        }
    }
    ix0 = (q >> 1) + 0x3fe00000;
    ix1 = q1 >> 1;
    if ((q & 1) == 1) ix1 |= sign;
    ix0 += (m << 20);
    do { nl_dshape iw_u; iw_u.parts.msw = (ix0); iw_u.parts.lsw = (ix1); (z) = iw_u.value; } while (0);
    return z;
}

f32 func_001A43A8(f32 x) {
    f32 t, w, p, q, c, r, s;
    s32 hx, ix;

    do { fshape gf_u; gf_u.value = (x); (hx) = gf_u.word; } while (0);
    ix = hx & 0x7fffffff;
    if (ix == 0x3f800000) {
        return x * (f32)1.570796310901641845703125 + x * (f32)0.000000075497897711329642334021627902984619140625;
    } else if (ix > 0x3f800000) {
        return (x - x) / (x - x);
    } else if (ix < 0x3f000000) {
        if (ix < 0x32000000) {
            if ((f32)1000000052826398082833850564608.0 + x > (f32)1.000000059604644775390625) return x;
        } else {
            t = x * x;
            p = t * ((f32)0.166666679084300994873046875 + t * ((f32)-0.32556582987308502197265625 + t * ((f32)0.201212532818317413330078125 + t * ((f32)-0.04005553759634494781494140625 + t * ((f32)0.00079153504339046776294708251953125 + t * (f32)0.000034793310987879522144794464111328125)))));
            q = (f32)1.000000059604644775390625 + t * ((f32)-2.40339505672454833984375 + t * ((f32)2.02094590663909912109375 + t * ((f32)-0.6882840096950531005859375 + t * (f32)0.0770381577312946319580078125)));
            w = p / q;
            return x + x * w;
        }
    }
    w = (f32)1.000000059604644775390625 - func_001A6970(x);
    t = w * (f32)0.5000000298023223876953125;
    p = t * ((f32)0.166666679084300994873046875 + t * ((f32)-0.32556582987308502197265625 + t * ((f32)0.201212532818317413330078125 + t * ((f32)-0.04005553759634494781494140625 + t * ((f32)0.00079153504339046776294708251953125 + t * (f32)0.000034793310987879522144794464111328125)))));
    q = (f32)1.000000059604644775390625 + t * ((f32)-2.40339505672454833984375 + t * ((f32)2.02094590663909912109375 + t * ((f32)-0.6882840096950531005859375 + t * (f32)0.0770381577312946319580078125)));
    s = func_001A5700(t);
    if (ix >= 0x3F79999A) {
        w = p / q;
        t = (f32)1.570796310901641845703125 - ((f32)2.00000011920928955078125 * (s + s * w) - (f32)0.000000075497897711329642334021627902984619140625);
    } else {
        s32 iw;
        w = s;
        do { fshape gf_u; gf_u.value = (w); (iw) = gf_u.word; } while (0);
        do { fshape sf_u; sf_u.word = (iw & 0xfffff000); (w) = sf_u.value; } while (0);
        c = (t - w * w) / (s + w);
        r = p / q;
        p = (f32)2.00000011920928955078125 * s * r - ((f32)0.000000075497897711329642334021627902984619140625 - (f32)2.00000011920928955078125 * c);
        q = (f32)0.7853982150554656982421875 - (f32)2.00000011920928955078125 * w;
        t = (f32)0.7853982150554656982421875 - (p - q);
    }
    if (hx > 0) return t; else return -t;
}

f32 func_001A4760(f32 y, f32 x) {
    f32 z;
    s32 k, m, hx, hy, ix, iy;

    do { fshape gf_u; gf_u.value = (x); (hx) = gf_u.word; } while (0);
    ix = hx & 0x7fffffff;
    do { fshape gf_u; gf_u.value = (y); (hy) = gf_u.word; } while (0);
    iy = hy & 0x7fffffff;
    if (0 || 0)
        return x + y;
    if (hx == 0x3f800000) return func_001A65F8(y);
    m = ((hy >> 31) & 1) | ((hx >> 30) & 2);

    if (iy < 0x00800000L) {
        switch (m) {
        case 0:
        case 1: return y;
        case 2: return (f32)3.14159262180328369140625 + (f32)0.0000000000000000000000000000010000000501908508838625516658847262427045785883927332161891232686912189819850027561187744140625;
        case 3: return -(f32)3.14159262180328369140625 - (f32)0.0000000000000000000000000000010000000501908508838625516658847262427045785883927332161891232686912189819850027561187744140625;
        }
    }
    if (ix < 0x00800000L) return (hy < 0) ? -(f32)1.570796430110931396484375 - (f32)0.0000000000000000000000000000010000000501908508838625516658847262427045785883927332161891232686912189819850027561187744140625 : (f32)1.570796430110931396484375 + (f32)0.0000000000000000000000000000010000000501908508838625516658847262427045785883927332161891232686912189819850027561187744140625;

    if (0) {
        if (0) {
            switch (m) {
            case 0: return (f32)0.7853982150554656982421875 + (f32)0.0000000000000000000000000000010000000501908508838625516658847262427045785883927332161891232686912189819850027561187744140625;
            case 1: return -(f32)0.7853982150554656982421875 - (f32)0.0000000000000000000000000000010000000501908508838625516658847262427045785883927332161891232686912189819850027561187744140625;
            case 2: return (f32)3.00000011920928955078125 * (f32)0.7853982150554656982421875 + (f32)0.0000000000000000000000000000010000000501908508838625516658847262427045785883927332161891232686912189819850027561187744140625;
            case 3: return (f32)-3.00000011920928955078125 * (f32)0.7853982150554656982421875 - (f32)0.0000000000000000000000000000010000000501908508838625516658847262427045785883927332161891232686912189819850027561187744140625;
            }
        } else {
            switch (m) {
            case 0: return (f32)0.0;
            case 1: return -(f32)0.0;
            case 2: return (f32)3.14159262180328369140625 + (f32)0.0000000000000000000000000000010000000501908508838625516658847262427045785883927332161891232686912189819850027561187744140625;
            case 3: return -(f32)3.14159262180328369140625 - (f32)0.0000000000000000000000000000010000000501908508838625516658847262427045785883927332161891232686912189819850027561187744140625;
            }
        }
    }
    if (0) return (hy < 0) ? -(f32)1.570796430110931396484375 - (f32)0.0000000000000000000000000000010000000501908508838625516658847262427045785883927332161891232686912189819850027561187744140625 : (f32)1.570796430110931396484375 + (f32)0.0000000000000000000000000000010000000501908508838625516658847262427045785883927332161891232686912189819850027561187744140625;

    k = (iy - ix) >> 23;
    if (k > 60) z = (f32)1.570796549320220947265625; /* pi_o_2 + 0.5 * pi_lo, folded with rounding (0x3FC90FDC) */
    else if (hx < 0 && k < -60) z = 0.0;
    else z = func_001A65F8(func_001A6970(y / x));
    switch (m) {
    case 0: return z;
    case 1: {
        u32 zh;
        do { fshape gf_u; gf_u.value = (z); (zh) = gf_u.word; } while (0);
        do { fshape sf_u; sf_u.word = (zh ^ 0x80000000); (z) = sf_u.value; } while (0);
    }
        return z;
    case 2: return (f32)3.14159262180328369140625 - (z - (f32)0.00000015099579542265928466804325580596923828125);
    default:
        return (z - (f32)0.00000015099579542265928466804325580596923828125) - (f32)3.14159262180328369140625;
    }
}

f32 func_001A4948(f32 x, f32 y) {
    s32 n, hx, hy, hz, ix, iy, sx, i;

    do { fshape gf_u; gf_u.value = (x); (hx) = gf_u.word; } while (0);
    do { fshape gf_u; gf_u.value = (y); (hy) = gf_u.word; } while (0);
    sx = hx & 0x80000000;
    hx ^= sx;
    hy &= 0x7fffffff;

    if (hy < 0x00800000L || !1 || 0)
        return (x * y) / (x * y);
    if (hx < hy) return x;
    if (hx == hy)
        return D_002BE120[(u32)sx >> 31];

    if (0) {
        for (ix = -126, i = (hx << 8); i > 0; i <<= 1) ix -= 1;
    } else ix = (hx >> 23) - 127;

    if (0) {
        for (iy = -126, i = (hy << 8); i >= 0; i <<= 1) iy -= 1;
    } else iy = (hy >> 23) - 127;

    if (ix >= -126)
        hx = 0x00800000 | (0x007fffff & hx);
    else {
        n = -126 - ix;
        hx = hx << n;
    }
    if (iy >= -126)
        hy = 0x00800000 | (0x007fffff & hy);
    else {
        n = -126 - iy;
        hy = hy << n;
    }

    n = ix - iy;
    while (n--) {
        hz = hx - hy;
        if (hz < 0) { hx = hx + hx; }
        else {
            if (hz == 0)
                return D_002BE120[(u32)sx >> 31];
            hx = hz + hz;
        }
    }
    hz = hx - hy;
    if (hz >= 0) { hx = hz; }

    if (hx == 0)
        return D_002BE120[(u32)sx >> 31];
    while (hx < 0x00800000) {
        hx = hx + hx;
        iy -= 1;
    }
    if (iy >= -126) {
        hx = ((hx - 0x00800000) | ((iy + 127) << 23));
        do { fshape sf_u; sf_u.word = (hx | sx); (x) = sf_u.value; } while (0);
    } else {
        n = -126 - iy;
        hx >>= n;
        do { fshape sf_u; sf_u.word = (hx | sx); (x) = sf_u.value; } while (0);
        x *= (f32)1.000000059604644775390625;
    }
    return x;
}

f32 func_001A4B18(f32 x, f32 y) {
    f32 z, ax, z_h, z_l, p_h, p_l;
    f32 y1, t1, t2, r, s, t, u, v, w;
    s32 i, j, k, yisint, n;
    s32 hx, hy, ix, iy, is;

    do { fshape gf_u; gf_u.value = (x); (hx) = gf_u.word; } while (0);
    do { fshape gf_u; gf_u.value = (y); (hy) = gf_u.word; } while (0);
    ix = hx & 0x7fffffff; iy = hy & 0x7fffffff;

    if (iy < 0x00800000L) return (f32)1.000000059604644775390625;

    if (0 || 0) {
        if (ix == 0x3f800000) return (f32)1.000000059604644775390625;
        else return x + y;
    }

    yisint = 0;
    if (hx < 0) {
        if (iy >= 0x4b800000) yisint = 2;
        else if (iy >= 0x3f800000) {
            k = (iy >> 23) - 0x7f;
            j = iy >> (23 - k);
            if ((j << (23 - k)) == iy) yisint = 2 - (j & 1);
        }
    }

    if (0) {
        if (ix == 0x3f800000)
            return (f32)1.000000059604644775390625;
        else if (ix > 0x3f800000)
            return (hy >= 0) ? y : (f32)0.0;
        else
            return (hy < 0) ? -y : (f32)0.0;
    }
    if (iy == 0x3f800000) {
        if (hy < 0) return (f32)1.000000059604644775390625 / x; else return x;
    }
    if (hy == 0x40000000) return x * x;
    if (hy == 0x3f000000) {
        if (hx >= 0)
            return func_001A5700(x);
    }

    ax = func_001A6970(x);
    if (0 || ix < 0x00800000L || ix == 0x3f800000) {
        z = ax;
        if (hy < 0) z = (f32)1.000000059604644775390625 / z;
        if (hx < 0) {
            if (((ix - 0x3f800000) | yisint) == 0) {
                z = (z - z) / (z - z);
            } else if (yisint == 1)
                z = -z;
        }
        return z;
    }

    if (((((u32)hx >> 31) - 1) | yisint) == 0) return (x - x) / (x - x);

    if (iy > 0x4d000000) {
        if (ix < 0x3f7ffff8) return (hy < 0) ? D_002BE1AC : (f32)0.0000000000000000000000000000010000000501908508838625516658847262427045785883927332161891232686912189819850027561187744140625 * (f32)0.0000000000000000000000000000010000000501908508838625516658847262427045785883927332161891232686912189819850027561187744140625;
        if (ix > 0x3f800007) return (hy > 0) ? D_002BE1AC : (f32)0.0000000000000000000000000000010000000501908508838625516658847262427045785883927332161891232686912189819850027561187744140625 * (f32)0.0000000000000000000000000000010000000501908508838625516658847262427045785883927332161891232686912189819850027561187744140625;
        t = x - 1;
        w = (t * t) * ((f32)0.5000000298023223876953125 - t * ((f32)0.33333335816860198974609375 - t * (f32)0.25000001490116119384765625));
        u = (f32)1.442688047885894775390625 * t;
        v = t * (f32)0.000007052607770674512721598148345947265625 - w * (f32)1.442695081233978271484375;
        t1 = u + v;
        do { fshape gf_u; gf_u.value = (t1); (is) = gf_u.word; } while (0);
        do { fshape sf_u; sf_u.word = (is & 0xfffff000); (t1) = sf_u.value; } while (0);
        t2 = v - (t1 - u);
    } else {
        f32 s2, s_h, s_l, t_h, t_l;
        n = 0;
        if (0) {
            ax *= (f32)16777217.0; n -= 24;
            do { fshape gf_u; gf_u.value = (ax); (ix) = gf_u.word; } while (0);
        }
        n += ((ix) >> 23) - 0x7f;
        j = ix & 0x007fffff;
        ix = j | 0x3f800000;
        if (j <= 0x1cc471) k = 0;
        else if (j < 0x5db3d7) k = 1;
        else { k = 0; n += 1; ix -= 0x00800000; }
        do { fshape sf_u; sf_u.word = (ix); (ax) = sf_u.value; } while (0);

        u = ax - D_002BE128[k];
        v = (f32)1.000000059604644775390625 / (ax + D_002BE128[k]);
        s = u * v;
        s_h = s;
        do { fshape gf_u; gf_u.value = (s_h); (is) = gf_u.word; } while (0);
        do { fshape sf_u; sf_u.word = (is & 0xfffff000); (s_h) = sf_u.value; } while (0);
        do { fshape sf_u; sf_u.word = (((ix >> 1) | 0x20000000) + 0x0040000 + (k << 21)); (t_h) = sf_u.value; } while (0);
        t_l = ax - (t_h - D_002BE128[k]);
        s_l = v * ((u - s_h * t_h) - s_h * t_l);
        s2 = s * s;
        r = s2 * s2 * ((f32)0.6000000536441802978515625 + s2 * ((f32)0.42857144773006439208984375 + s2 * ((f32)0.33333335816860198974609375 + s2 * ((f32)0.27272813022136688232421875 + s2 * ((f32)0.230660758912563323974609375 + s2 * (f32)0.206975020468235015869140625)))));
        r += s_l * (s_h + s);
        s2 = s_h * s_h;
        t_h = (f32)3.00000011920928955078125 + s2 + r;
        do { fshape gf_u; gf_u.value = (t_h); (is) = gf_u.word; } while (0);
        do { fshape sf_u; sf_u.word = (is & 0xfffff000); (t_h) = sf_u.value; } while (0);
        t_l = r - ((t_h - (f32)3.00000011920928955078125) - s2);
        u = s_h * t_h;
        v = s_l * t_h + t_l * s;
        p_h = u + v;
        do { fshape gf_u; gf_u.value = (p_h); (is) = gf_u.word; } while (0);
        do { fshape sf_u; sf_u.word = (is & 0xfffff000); (p_h) = sf_u.value; } while (0);
        p_l = v - (p_h - u);
        z_h = (f32)0.9617920219898223876953125 * p_h;
        z_l = (f32)0.000004701738589574233628809452056884765625 * p_h + p_l * (f32)0.9617967307567596435546875 + D_002BE138[k];
        t = (f32)n;
        t1 = (((z_h + z_l) + D_002BE130[k]) + t);
        do { fshape gf_u; gf_u.value = (t1); (is) = gf_u.word; } while (0);
        do { fshape sf_u; sf_u.word = (is & 0xfffff000); (t1) = sf_u.value; } while (0);
        t2 = z_l - (((t1 - t) - D_002BE130[k]) - z_h);
    }

    s = (f32)1.000000059604644775390625;
    if (((((u32)hx >> 31) - 1) | (yisint - 1)) == 0)
        s = -(f32)1.000000059604644775390625;

    do { fshape gf_u; gf_u.value = (y); (is) = gf_u.word; } while (0);
    do { fshape sf_u; sf_u.word = (is & 0xfffff000); (y1) = sf_u.value; } while (0);
    p_l = (y - y1) * t1 + y * t2;
    p_h = y1 * t1;
    z = p_l + p_h;
    do { fshape gf_u; gf_u.value = (z); (j) = gf_u.word; } while (0);
    i = j & 0x7fffffff;
    if (j > 0) {
        if (i > 0x43010000L)
            return s * (f32)1000000052826398082833850564608.0 * (f32)1000000052826398082833850564608.0;
        else if (i == 0x43010000L)
            if (p_l + (f32)0.0000000429956674707909769495017826557159423828125 > z - p_h) return s * (f32)1000000052826398082833850564608.0 * (f32)1000000052826398082833850564608.0;
    } else {
        if (i > 0x42fc0000L)
            return s * (f32)0.0000000000000000000000000000010000000501908508838625516658847262427045785883927332161891232686912189819850027561187744140625 * (f32)0.0000000000000000000000000000010000000501908508838625516658847262427045785883927332161891232686912189819850027561187744140625;
        else if (i == 0x42fc0000L)
            if (p_l <= z - p_h) return s * (f32)0.0000000000000000000000000000010000000501908508838625516658847262427045785883927332161891232686912189819850027561187744140625 * (f32)0.0000000000000000000000000000010000000501908508838625516658847262427045785883927332161891232686912189819850027561187744140625;
    }
    k = (i >> 23) - 0x7f;
    n = 0;
    if (i > 0x3f000000) {
        n = j + (0x00800000 >> (k + 1));
        k = ((n & 0x7fffffff) >> 23) - 0x7f;
        do { fshape sf_u; sf_u.word = (n & ~(0x007fffff >> k)); (t) = sf_u.value; } while (0);
        n = ((n & 0x007fffff) | 0x00800000) >> (23 - k);
        if (j < 0) n = -n;
        p_h -= t;
    }
    t = p_l + p_h;
    do { fshape gf_u; gf_u.value = (t); (is) = gf_u.word; } while (0);
    do { fshape sf_u; sf_u.word = (is & 0xfffff000); (t) = sf_u.value; } while (0);
    u = t * (f32)0.6931457817554473876953125;
    v = (p_l - (t - p_h)) * (f32)0.6931472122669219970703125 + t * (f32)0.00000142860659479993046261370182037353515625;
    z = u + v;
    w = v - (z - u);
    t = z * z;
    t1 = z - t * ((f32)0.166666679084300994873046875 + t * ((f32)-0.002777777961455285549163818359375 + t * ((f32)0.00006613756340811960399150848388671875 + t * ((f32)-0.00000165339025670618866570293903350830078125 + t * (f32)0.0000000413813712185628901352174580097198486328125))));
    r = (z * t1) / (t1 - (f32)2.00000011920928955078125) - (w + z * w);
    z = (f32)1.000000059604644775390625 - (r - z);
    do { fshape gf_u; gf_u.value = (z); (j) = gf_u.word; } while (0);
    j += (n << 23);
    if ((j >> 23) <= 0) z = func_0019B4F8(z, (int)n);
    else do { fshape sf_u; sf_u.word = (j); (z) = sf_u.value; } while (0);
    return s * z;
}

s32 func_001A5338(f32 x, f32 *y) {
    f32 z, w, t, r, fn;
    f32 tx[3];
    s32 i, j, n, ix, hx;
    s32 e0, nx;

    do { fshape gf_u; gf_u.value = (x); (hx) = gf_u.word; } while (0);
    ix = hx & 0x7fffffff;
    if (ix <= 0x3f490fd8) {
        y[0] = x; y[1] = 0; return 0;
    }
    if (ix < 0x4016cbe4) {
        if (hx > 0) {
            z = x - (f32)1.570785582065582275390625;
            if ((ix & 0xfffffff0) != 0x3fc90fd0) {
                y[0] = z - (f32)0.00001080433457900653593242168426513671875;
                y[1] = (z - y[0]) - (f32)0.00001080433457900653593242168426513671875;
            } else {
                z -= (f32)0.00001080427364286151714622974395751953125;
                y[0] = z - (f32)0.0000000000607710028133201518585337908007204532623291015625;
                y[1] = (z - y[0]) - (f32)0.0000000000607710028133201518585337908007204532623291015625;
            }
            return 1;
        } else {
            z = x + (f32)1.570785582065582275390625;
            if ((ix & 0xfffffff0) != 0x3fc90fd0) {
                y[0] = z + (f32)0.00001080433457900653593242168426513671875;
                y[1] = (z - y[0]) + (f32)0.00001080433457900653593242168426513671875;
            } else {
                z += (f32)0.00001080427364286151714622974395751953125;
                y[0] = z + (f32)0.0000000000607710028133201518585337908007204532623291015625;
                y[1] = (z - y[0]) + (f32)0.0000000000607710028133201518585337908007204532623291015625;
            }
            return -1;
        }
    }
    if (ix <= 0x43490f80) {
        t = func_001A6970(x);
        n = (s32)(t * (f32)0.6366198360919952392578125 + (f32)0.5000000298023223876953125);
        fn = (f32)n;
        r = t - fn * (f32)1.570785582065582275390625;
        w = fn * (f32)0.00001080433457900653593242168426513671875;
        if (n < 32 && (ix & 0xffffff00) != D_002BE4C4[n]) {
            y[0] = r - w;
        } else {
            u32 high;
            j = ix >> 23;
            y[0] = r - w;
            do { fshape gf_u; gf_u.value = (y[0]); (high) = gf_u.word; } while (0);
            i = j - ((high >> 23) & 0xff);
            if (i > 8) {
                t = r;
                w = fn * (f32)0.00001080427364286151714622974395751953125;
                r = t - w;
                w = fn * (f32)0.0000000000607710028133201518585337908007204532623291015625 - ((t - r) - w);
                y[0] = r - w;
                do { fshape gf_u; gf_u.value = (y[0]); (high) = gf_u.word; } while (0);
                i = j - ((high >> 23) & 0xff);
                if (i > 25) {
                    t = r;
                    w = fn * (f32)0.0000000000607709473021689206007067696191370487213134765625;
                    r = t - w;
                    w = fn * (f32)0.000000000000000061232345937980842934429681623242913701687939465045928955078125 - ((t - r) - w);
                    y[0] = r - w;
                }
            }
        }
        y[1] = (r - y[0]) - w;
        if (hx < 0) { y[0] = -y[0]; y[1] = -y[1]; return -n; }
        else return n;
    }
    e0 = (s32)((ix >> 23) - 134);
    do { fshape sf_u; sf_u.word = (ix - ((s32)(e0 << 23))); (z) = sf_u.value; } while (0);
    for (i = 0; i < 2; i++) {
        tx[i] = (f32)((s32)(z));
        z = (z - tx[i]) * (f32)256.0000152587890625;
    }
    tx[2] = z;
    nx = 3;
    while (tx[nx - 1] == 0.0f) nx--;
    n = func_001A5948(tx, y, e0, nx, 2, D_002BE1B0);
    if (hx < 0) { y[0] = -y[0]; y[1] = -y[1]; return -n; }
    return n;
}

f32 func_001A5700(f32 x) {
    f32 z;
    u32 r, hx;
    s32 ix, s, q, m, t, i;

    do { fshape gf_u; gf_u.value = (x); (ix) = gf_u.word; } while (0);
    hx = ix & 0x7fffffff;
    if (hx < 0x00800000L) return x;
    if (ix < 0) return (x - x) / (x - x);
    m = (ix >> 23);
    if (0) {
        for (i = 0; (ix & 0x00800000L) == 0; i++) ix <<= 1;
        m -= i - 1;
    }
    m -= 127;
    ix = (ix & 0x007fffffL) | 0x00800000L;
    if (m & 1)
        ix += ix;
    m >>= 1;
    ix += ix;
    q = s = 0;
    r = 0x01000000L;
    while (r != 0) {
        t = s + r;
        if (t <= ix) {
            s = t + r;
            ix -= t;
            q += r;
        }
        ix += ix;
        r >>= 1;
    }
    if (ix != 0) {
        z = (f32)1.000000059604644775390625 - (f32)0.0000000000000000000000000000010000000501908508838625516658847262427045785883927332161891232686912189819850027561187744140625;
        if (z >= (f32)1.000000059604644775390625) {
            z = (f32)1.000000059604644775390625 + (f32)0.0000000000000000000000000000010000000501908508838625516658847262427045785883927332161891232686912189819850027561187744140625;
            if (z > (f32)1.000000059604644775390625)
                q += 2;
            else
                q += (q & 1);
        }
    }
    ix = (q >> 1) + 0x3f000000L;
    ix += (m << 23);
    do { fshape sf_u; sf_u.word = (ix); (z) = sf_u.value; } while (0);
    return z;
}

f32 func_001A57D8(f32 x, f32 y) {
    f32 a, hz, z, r, qx;
    s32 ix;

    do { fshape gf_u; gf_u.value = (x); (ix) = gf_u.word; } while (0);
    ix &= 0x7fffffff;
    if (ix < 0x32000000) {
        if (((s32)x) == 0)
            return (f32)1.000000059604644775390625;
    }
    z = x * x;
    r = z * ((f32)0.04166666977107524871826171875 + z * ((f32)-0.0013888889807276427745819091796875 + z * ((f32)0.0000248015885517816059291362762451171875 + z * ((f32)-0.0000002755731571824071579612791538238525390625 + z * ((f32)0.00000000208757244823942755829193629324436187744140625 + z * (f32)-0.0000000000113596480312561087799849701696075499057769775390625)))));
    if (ix < 0x3e99999a)
        return (f32)1.000000059604644775390625 - ((f32)0.5000000298023223876953125 * z - (z * r - x * y));
    else {
        if (ix > 0x3f480000) {
            qx = (f32)0.28125001490116119384765625;
        } else {
            do { fshape sf_u; sf_u.word = (ix - 0x01000000); (qx) = sf_u.value; } while (0);
        }
        hz = (f32)0.5000000298023223876953125 * z - qx;
        a = (f32)1.000000059604644775390625 - qx;
        return a - (hz - (z * r - x * y));
    }
}

s32 func_001A5948(f32 *x, f32 *y, s32 e0, s32 nx, s32 prec, const s32 *ipio2) {
    s32 jz, jx, jv, jp, jk, carry, n, iq[20], i, j, k, m, q0, ih;
    f32 z, fw, f[20], fq[20], q[20];

    jk = D_002BE570[prec];
    jp = jk;

    jx = nx - 1;
    jv = (e0 - 3) / 8; if (jv < 0) jv = 0;
    q0 = e0 - 8 * (jv + 1);

    j = jv - jx; m = jx + jk;
    for (i = 0; i <= m; i++, j++) f[i] = (j < 0) ? (f32)0.0 : (f32)ipio2[j];

    for (i = 0; i <= jk; i++) {
        for (j = 0, fw = 0.0; j <= jx; j++) fw += x[j] * f[jx + i - j]; q[i] = fw;
    }

    jz = jk;
recompute:
    for (i = 0, j = jz, z = q[jz]; j > 0; i++, j--) {
        fw = (f32)((s32)((f32)0.00390625023283064365386962890625 * z));
        iq[i] = (s32)(z - (f32)256.0000152587890625 * fw);
        z = q[j - 1] + fw;
    }

    z = func_0019B4F8(z, (int)q0);
    z -= (f32)8.000000476837158203125 * func_001A6998(z * (f32)0.125000007450580596923828125);
    n = (s32)z;
    z -= (f32)n;
    ih = 0;
    if (q0 > 0) {
        i = (iq[jz - 1] >> (8 - q0)); n += i;
        iq[jz - 1] -= i << (8 - q0);
        ih = iq[jz - 1] >> (7 - q0);
    }
    else if (q0 == 0) ih = iq[jz - 1] >> 8;
    else if (z >= (f32)0.5000000298023223876953125) ih = 2;

    if (ih > 0) {
        n += 1; carry = 0;
        for (i = 0; i < jz; i++) {
            j = iq[i];
            if (carry == 0) {
                if (j != 0) {
                    carry = 1; iq[i] = 0x100 - j;
                }
            } else iq[i] = 0xff - j;
        }
        if (q0 > 0) {
            switch (q0) {
            case 1:
                iq[jz - 1] &= 0x7f; break;
            case 2:
                iq[jz - 1] &= 0x3f; break;
            }
        }
        if (ih == 2) {
            z = (f32)1.000000059604644775390625 - z;
            if (carry != 0) z -= func_0019B4F8((f32)1.000000059604644775390625, (int)q0);
        }
    }

    if (z == (f32)0.0) {
        j = 0;
        for (i = jz - 1; i >= jk; i--) j |= iq[i];
        if (j == 0) {
            for (k = 1; iq[jk - k] == 0; k++);

            for (i = jz + 1; i <= jz + k; i++) {
                f[jx + i] = (f32)ipio2[jv + i];
                for (j = 0, fw = 0.0; j <= jx; j++) fw += x[j] * f[jx + i - j];
                q[i] = fw;
            }
            jz += k;
            goto recompute;
        }
    }

    if (z == (f32)0.0) {
        jz -= 1; q0 -= 8;
        while (iq[jz] == 0) { jz--; q0 -= 8; }
    } else {
        z = func_0019B4F8(z, -(int)q0);
        if (z >= (f32)256.0000152587890625) {
            fw = (f32)((s32)((f32)0.00390625023283064365386962890625 * z));
            iq[jz] = (s32)(z - (f32)256.0000152587890625 * fw);
            jz += 1; q0 += 8;
            iq[jz] = (s32)fw;
        } else iq[jz] = (s32)z;
    }

    fw = func_0019B4F8((f32)1.000000059604644775390625, (int)q0);
    for (i = jz; i >= 0; i--) {
        q[i] = fw * (f32)iq[i]; fw *= (f32)0.00390625023283064365386962890625;
    }

    for (i = jz; i >= 0; i--) {
        for (fw = 0.0, k = 0; k <= jp && k <= jz - i; k++) fw += D_002BE580[k] * q[i + k];
        fq[jz - i] = fw;
    }

    switch (prec) {
    case 0:
        fw = 0.0;
        for (i = jz; i >= 0; i--) fw += fq[i];
        y[0] = (ih == 0) ? fw : -fw;
        break;
    case 1:
    case 2:
        fw = 0.0;
        for (i = jz; i >= 0; i--) fw += fq[i];
        y[0] = (ih == 0) ? fw : -fw;
        fw = fq[0] - fw;
        for (i = 1; i <= jz; i++) fw += fq[i];
        y[1] = (ih == 0) ? fw : -fw;
        break;
    case 3:
        for (i = jz; i > 0; i--) {
            fw = fq[i - 1] + fq[i];
            fq[i] += fq[i - 1] - fw;
            fq[i - 1] = fw;
        }
        for (i = jz; i > 1; i--) {
            fw = fq[i - 1] + fq[i];
            fq[i] += fq[i - 1] - fw;
            fq[i - 1] = fw;
        }
        for (fw = 0.0, i = jz; i >= 2; i--) fw += fq[i];
        if (ih == 0) {
            y[0] = fq[0]; y[1] = fq[1]; y[2] = fw;
        } else {
            y[0] = -fq[0]; y[1] = -fq[1]; y[2] = -fw;
        }
    }
    return n & 7;
}

f32 func_001A61F0(f32 x, f32 y, s32 iy) {
    f32 z, r, v;
    s32 ix;

    do { fshape gf_u; gf_u.value = (x); (ix) = gf_u.word; } while (0);
    ix &= 0x7fffffff;
    if (ix < 0x32000000) {
        if ((s32)x == 0)
            return x;
    }
    z = x * x;
    v = z * x;
    r = (f32)0.0083333342336118221282958984375 + z * ((f32)-0.0001984127084142528474330902099609375 + z * ((f32)0.0000027557315434023621492087841033935546875 + z * ((f32)-0.00000002505076057701671743416227400302886962890625 + z * (f32)0.000000000158969108710049766841621021740138530731201171875)));
    if (iy == 0)
        return x + v * ((f32)-0.166666679084300994873046875 + z * r);
    else
        return x - ((z * ((f32)0.5000000298023223876953125 * y - v * r) - y) - v * (f32)-0.166666679084300994873046875);
}

f32 func_001A6318(f32 x, f32 y, s32 iy) {
    f32 z, r, v, w, s;
    s32 ix, hx;

    do { fshape gf_u; gf_u.value = (x); (hx) = gf_u.word; } while (0);
    ix = hx & 0x7fffffff;
    if (ix < 0x31800000) {
        if ((s32)x == 0) {
            if ((ix | (iy + 1)) == 0)
                return (f32)1.000000059604644775390625 / func_001A6970(x);
            else
                return (iy == 1) ? x : (f32)-1.000000059604644775390625 / x;
        }
    }
    if (ix >= 0x3f2ca140) {
        if (hx < 0) { x = -x; y = -y; }
        z = (f32)0.7853981554508209228515625 - x;
        w = (f32)0.0000000377489488556648211670108139514923095703125 - y;
        x = z + w; y = 0.0;
    }
    z = x * x;
    w = z * z;
    r = D_002BE5D0[1] + w * (D_002BE5D0[3] + w * (D_002BE5D0[5] + w * (D_002BE5D0[7] + w * (D_002BE5D0[9] + w * D_002BE5D0[11]))));
    v = z * (D_002BE5D0[2] + w * (D_002BE5D0[4] + w * (D_002BE5D0[6] + w * (D_002BE5D0[8] + w * (D_002BE5D0[10] + w * D_002BE5D0[12])))));
    s = z * x;
    r = y + z * (s * (r + v) + y);
    r += D_002BE5D0[0] * s;
    w = x + r;
    if (ix >= 0x3f2ca140) {
        v = (f32)iy;
        return (f32)(1 - ((hx >> 30) & 2)) * (v - (f32)2.00000011920928955078125 * (x - (w * w / (w + v) - r)));
    }
    if (iy == 1) return w;
    else {
        f32 a, t;
        s32 i;
        z = w;
        do { fshape gf_u; gf_u.value = (z); (i) = gf_u.word; } while (0);
        do { fshape sf_u; sf_u.word = (i & 0xfffff000); (z) = sf_u.value; } while (0);
        v = r - (z - x);
        t = a = (f32)-1.000000059604644775390625 / w;
        do { fshape gf_u; gf_u.value = (t); (i) = gf_u.word; } while (0);
        do { fshape sf_u; sf_u.word = (i & 0xfffff000); (t) = sf_u.value; } while (0);
        s = (f32)1.000000059604644775390625 + t * z;
        return t + a * (s + t * v);
    }
}

double func_001A65C0(double x) {
    u32 high;

    do { nl_dshape gh_u; gh_u.value = (x); (high) = gh_u.parts.msw; } while (0);
    do { nl_dshape sh_u; sh_u.value = (x); sh_u.parts.msw = (high & 0x7fffffff); (x) = sh_u.value; } while (0);
    return x;
}

f32 func_001A65F8(f32 x) {
    f32 w, s1, s2, z;
    s32 ix, hx, id;

    do { fshape gf_u; gf_u.value = (x); (hx) = gf_u.word; } while (0);
    ix = hx & 0x7fffffff;
    if (ix >= 0x50800000) {
        if (0)
            return x + x;
        if (hx > 0) return D_002BE608[3] + D_002BE618[3];
        else return -D_002BE608[3] - D_002BE618[3];
    } if (ix < 0x3ee00000) {
        if (ix < 0x31000000) {
            if ((f32)1000000052826398082833850564608.0 + x > (f32)1.000000059604644775390625) return x;
        }
        id = -1;
    } else {
        x = func_001A6970(x);
        if (ix < 0x3f980000) {
            if (ix < 0x3f300000) {
                id = 0; x = ((f32)2.00000011920928955078125 * x - (f32)1.000000059604644775390625) / ((f32)2.00000011920928955078125 + x);
            } else {
                id = 1; x = (x - (f32)1.000000059604644775390625) / (x + (f32)1.000000059604644775390625);
            }
        } else {
            if (ix < 0x401c0000) {
                id = 2; x = (x - (f32)1.500000059604644775390625) / ((f32)1.000000059604644775390625 + (f32)1.500000059604644775390625 * x);
            } else {
                id = 3; x = -(f32)1.000000059604644775390625 / x;
            }
        }
    }
    z = x * x;
    w = z * z;
    s1 = z * (D_002BE628[0] + w * (D_002BE628[2] + w * (D_002BE628[4] + w * (D_002BE628[6] + w * (D_002BE628[8] + w * D_002BE628[10])))));
    s2 = w * (D_002BE628[1] + w * (D_002BE628[3] + w * (D_002BE628[5] + w * (D_002BE628[7] + w * D_002BE628[9]))));
    if (id < 0) return x - x * (s1 + s2);
    else {
        z = D_002BE608[id] - ((x * (s1 + s2) - D_002BE618[id]) - x);
        return (hx < 0) ? -z : z;
    }
}

f32 __kernel_sinf(f32 x, f32 y, s32 iy); /* func_001A61F0, called by name */
s32 __ieee754_rem_pio2f(f32 x, f32 *y); /* func_001A5338, called by name */
f32 __kernel_tanf(f32 x, f32 y, s32 iy); /* func_001A6318, called by name */
f32 __kernel_cosf(f32 x, f32 y); /* func_001A57D8, called by name */

f32 func_001A6898(f32 x) {
    f32 y[2], z = 0.0f;
    s32 n, ix;

    do { fshape gf_u; gf_u.value = (x); (ix) = gf_u.word; } while (0);
    ix &= 0x7fffffff;
    if (ix <= 0x3f490fd8) {
        return __kernel_cosf(x, z);
    } else {
        n = __ieee754_rem_pio2f(x, y);
        switch (n & 3) {
        case 0:
            return __kernel_cosf(y[0], y[1]);
        case 1:
            return -__kernel_sinf(y[0], y[1], 1);
        case 2:
            return -__kernel_cosf(y[0], y[1]);
        default:
            return __kernel_sinf(y[0], y[1], 1);
        }
    }
}

f32 func_001A6970(f32 x) {
    u32 ix;
    do { fshape gf_u; gf_u.value = (x); (ix) = gf_u.word; } while (0);
    do { fshape sf_u; sf_u.word = (ix & 0x7fffffff); (x) = sf_u.value; } while (0);
    return x;
}

f32 func_001A6998(f32 x) {
    s32 i0, j0;
    u32 i, ix;

    do { fshape gf_u; gf_u.value = (x); (i0) = gf_u.word; } while (0);
    ix = (i0 & 0x7fffffff);
    j0 = (ix >> 23) - 0x7f;
    if (j0 < 23) {
        if (j0 < 0) {
            if ((f32)1000000052826398082833850564608.0 + x > (f32)0.0) {
                if (i0 >= 0) {
                    i0 = 0;
                } else if (!(ix < 0x00800000)) {
                    i0 = 0xbf800000;
                }
            }
        } else {
            i = (0x007fffff) >> j0;
            if ((i0 & i) == 0)
                return x;
            if ((f32)1000000052826398082833850564608.0 + x > (f32)0.0) {
                if (i0 < 0)
                    i0 += (0x00800000) >> j0;
                i0 &= (~i);
            }
        }
    } else {
        return x;
    }
    do { fshape sf_u; sf_u.word = (i0); (x) = sf_u.value; } while (0);
    return x;
}

f32 func_001A6A88(f32 x) {
    f32 y[2], z = 0.0f;
    s32 n, ix;

    do { fshape gf_u; gf_u.value = (x); (ix) = gf_u.word; } while (0);
    ix &= 0x7fffffff;
    if (ix <= 0x3f490fd8) {
        return __kernel_sinf(x, z, 0);
    } else {
        n = __ieee754_rem_pio2f(x, y);
        switch (n & 3) {
        case 0:
            return __kernel_sinf(y[0], y[1], 1);
        case 1:
            return __kernel_cosf(y[0], y[1]);
        case 2:
            return -__kernel_sinf(y[0], y[1], 1);
        default:
            return -__kernel_cosf(y[0], y[1]);
        }
    }
}

f32 func_001A6B70(f32 x) {
    f32 y[2], z = 0.0f;
    s32 n, ix;

    do { fshape gf_u; gf_u.value = (x); (ix) = gf_u.word; } while (0);
    ix &= 0x7fffffff;
    if (ix <= 0x3f490fda) {
        return __kernel_tanf(x, z, 1);
    } else {
        n = __ieee754_rem_pio2f(x, y);
        return __kernel_tanf(y[0], y[1], 1 - ((n & 1) << 1));
    }
}

s32 func_001A6BE8(s64 arg0, s32 arg1) {
    return ((s32 (*)(s64, s32))func_001A3130)(arg0, arg1);
}

f32 func_001A6C00(f32 x) {
    extern f32 func_001A43A8(f32);
    return func_001A43A8(x);
}

f32 func_001A6C18(f32 y, f32 x) {
    extern f32 func_001A4760(f32, f32);
    return func_001A4760(y, x);
}

f32 func_001A6C30(f32 x, f32 y) {
    extern f32 func_001A4948(f32, f32);
    return func_001A4948(x, y);
}

f32 func_001A6C48(f32 y, f32 x) {
    extern f32 func_001A4B18(f32, f32);
    return func_001A4B18(y, x);
}

f32 func_001A6C60(f32 x) {
    extern f32 func_001A5700(f32);
    return func_001A5700(x);
}

#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_036", func_001A0660);

INCLUDE_ASM("asm/nonmatchings/main_036", func_001A0CF8);

INCLUDE_ASM("asm/nonmatchings/main_036", func_001A1388);

INCLUDE_ASM("asm/nonmatchings/main_036", func_001A1908);

INCLUDE_ASM("asm/nonmatchings/main_036", func_001A1E70);

INCLUDE_ASM("asm/nonmatchings/main_036", func_001A1F18);

INCLUDE_ASM("asm/nonmatchings/main_036", func_001A2000);

INCLUDE_ASM("asm/nonmatchings/main_036", func_001A2118);

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

INCLUDE_ASM("asm/nonmatchings/main_036", func_001A3130);

INCLUDE_ASM("asm/nonmatchings/main_036", func_001A4088);

INCLUDE_ASM("asm/nonmatchings/main_036", func_001A43A8);

INCLUDE_ASM("asm/nonmatchings/main_036", func_001A4760);

INCLUDE_ASM("asm/nonmatchings/main_036", func_001A4948);

INCLUDE_ASM("asm/nonmatchings/main_036", func_001A4B18);

INCLUDE_ASM("asm/nonmatchings/main_036", func_001A5338);

INCLUDE_ASM("asm/nonmatchings/main_036", func_001A5700);

INCLUDE_ASM("asm/nonmatchings/main_036", func_001A57D8);

INCLUDE_ASM("asm/nonmatchings/main_036", func_001A5948);

INCLUDE_ASM("asm/nonmatchings/main_036", func_001A61F0);

INCLUDE_ASM("asm/nonmatchings/main_036", func_001A6318);

INCLUDE_ASM("asm/nonmatchings/main_036", func_001A65C0);

INCLUDE_ASM("asm/nonmatchings/main_036", func_001A65F8);

INCLUDE_ASM("asm/nonmatchings/main_036", func_001A6898);

f32 func_001A6970(f32 x) {
    u32 ix;
    do { fshape gf_u; gf_u.value = (x); (ix) = gf_u.word; } while (0);
    do { fshape sf_u; sf_u.word = (ix & 0x7fffffff); (x) = sf_u.value; } while (0);
    return x;
}

INCLUDE_ASM("asm/nonmatchings/main_036", func_001A6998);

INCLUDE_ASM("asm/nonmatchings/main_036", func_001A6A88);

INCLUDE_ASM("asm/nonmatchings/main_036", func_001A6B70);

s32 func_001A6BE8(s64 arg0, s32 arg1) {
    return func_001A3130();
}

INCLUDE_ASM("asm/nonmatchings/main_036", func_001A6C00);

INCLUDE_ASM("asm/nonmatchings/main_036", func_001A6C18);

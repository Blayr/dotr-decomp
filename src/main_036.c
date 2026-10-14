#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_036", func_001A0660);

INCLUDE_ASM("asm/nonmatchings/main_036", func_001A0CF8);

INCLUDE_ASM("asm/nonmatchings/main_036", func_001A1388);

INCLUDE_ASM("asm/nonmatchings/main_036", func_001A1908);

INCLUDE_ASM("asm/nonmatchings/main_036", func_001A1E70);

INCLUDE_ASM("asm/nonmatchings/main_036", func_001A1F18);

INCLUDE_ASM("asm/nonmatchings/main_036", func_001A2000);

INCLUDE_ASM("asm/nonmatchings/main_036", func_001A2118);

INCLUDE_ASM("asm/nonmatchings/main_036", func_001A2190);

INCLUDE_ASM("asm/nonmatchings/main_036", func_001A2260);

INCLUDE_ASM("asm/nonmatchings/main_036", func_001A22C0);

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

INCLUDE_ASM("asm/nonmatchings/main_036", func_001A23B0);

INCLUDE_ASM("asm/nonmatchings/main_036", func_001A2430);

INCLUDE_ASM("asm/nonmatchings/main_036", func_001A2548);

INCLUDE_ASM("asm/nonmatchings/main_036", func_001A25F8);

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

INCLUDE_ASM("asm/nonmatchings/main_036", func_001A28B0);

INCLUDE_ASM("asm/nonmatchings/main_036", func_001A2918);

INCLUDE_ASM("asm/nonmatchings/main_036", func_001A2BC8);

INCLUDE_ASM("asm/nonmatchings/main_036", func_001A2D40);

INCLUDE_ASM("asm/nonmatchings/main_036", func_001A2E60);

INCLUDE_ASM("asm/nonmatchings/main_036", func_001A2EB0);

INCLUDE_ASM("asm/nonmatchings/main_036", func_001A2F68);

INCLUDE_ASM("asm/nonmatchings/main_036", func_001A3008);

INCLUDE_ASM("asm/nonmatchings/main_036", func_001A3038);

INCLUDE_ASM("asm/nonmatchings/main_036", func_001A3090);

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

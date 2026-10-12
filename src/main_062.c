#include "common.h"

void func_0021BAE0(void *arg0) {
    f32 *values = arg0;

    values[3] = 1.0f;
    values[2] = 1.0f;
    values[1] = 1.0f;
    values[0] = 1.0f;
    values[7] = 0.0f;
    values[6] = 0.0f;
    values[5] = 0.0f;
    values[4] = 0.0f;
    values[11] = 0.0f;
    values[10] = 0.0f;
    values[9] = 0.0f;
    values[8] = 0.0f;
}

void func_0020C940(void *, void *, void *, void *);
void func_0020EB40(void *);

typedef struct {
    f32 m[4][4];
} Matrix_0021BB20;

void func_0021BB20(u8 *arg0) {
    Matrix_0021BB20 matrix;

    func_0020EB40(arg0 + 0x30);
    func_0020C940(&matrix, arg0, arg0 + 0x10, arg0 + 0x20);
    func_0020BC00((s32)(arg0 + 0x30), &matrix);
}

void func_0021BB70(void *arg0, void *arg1) {
    ((f32 *)arg0)[0] = ((f32 *)arg1)[0];
    ((f32 *)arg0)[1] = ((f32 *)arg1)[1];
    ((f32 *)arg0)[2] = ((f32 *)arg1)[2];
}

void func_0021BB90(s32 *arg0, s32 *arg1, s32 arg2) {
    u16 projected[6];
    s32 depth;

    if (func_00205440(arg2, D_00299F90, projected, &depth) != 0) {
        *arg0 = ((s32) projected[0] >> 4) - 0x6C0;
        *arg1 = ((s32) projected[1] >> 4) - 0x720;
    } else {
        *arg0 = -1;
        *arg1 = -1;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_062", func_0021BC10);

f32 func_0021C320(f32 fparg0, f32 fparg1, f32 fparg2, f32 fparg3, f32 fparg4) {
    return 3.0f * (((fparg4 * (fparg1 - fparg0)) / fparg3) + ((fparg3 * (fparg2 - fparg1)) / fparg4));
}

void func_0021C350(f32 *a, f32 *b, f32 *c, f32 *r, f32 *u, s32 n) {
    f32 gamma[64];
    f32 denominator;
    s32 i;

    denominator = b[0];
    u[0] = r[0] / denominator;
    for (i = 1; i < n; i++) {
        gamma[i] = c[i - 1] / denominator;
        denominator = b[i] - a[i] * gamma[i];
        u[i] = (r[i] - a[i] * u[i - 1]) / denominator;
    }
    for (i = n - 2; i >= 0; i--) {
        u[i] -= gamma[i + 1] * u[i + 1];
    }
}

s32 func_0021C450(s32 arg0, s32 arg1, s32 arg2, s64 arg3, s64 arg4, s32 arg5, s32 arg6) {
    s32 result;
    s32 object;

    object = func_0020F290(func_001FD680(arg0, arg1, arg2, 0, arg1 * 22));
    func_001FEAB0(arg1);
    result = func_001FE660(object, arg1, (s16)arg3, (s16)arg4, 1.0f, 1.0f, arg6, func_001FDFE0);
    func_001FEAF0(arg1);
    return result;
}

INCLUDE_ASM("asm/nonmatchings/main_062", func_0021C510);

INCLUDE_ASM("asm/nonmatchings/main_062", func_0021D480);

INCLUDE_ASM("asm/nonmatchings/main_062", func_0021D850);

void func_0021DA60(void) {
    if (D_0034F710 == 0) {
        func_00209D30(func_0021DDA0(func_00209D20()));
    }
}

typedef struct {
    f32 x, y, z, w;
} Vec4_0021DAA0;

void *func_0021DFF0(void *, s32, s32, s32, f32, s32, s32, s32);
void *func_002297C0(s32);
void *func_0023BFF0(void *, s32, s32, f32, f32);
extern s16 D_00298AD0;
extern s16 D_00298AD2;
extern s16 D_00298AD4;
extern s16 D_00298ADA;
extern Vec4_0021DAA0 D_0029A7B0;
extern Vec4_0021DAA0 D_0029A7C0;

static inline s32 offset_y_0021DAA0(s32 y) {
    return (s16)y - 0x100;
}

void func_0021DAA0(void) {
    extern void *func_00218970(void *, void *, s16, s16);
    Vec4_0021DAA0 sp80;
    Vec4_0021DAA0 sp90;
    s8 *state;
    s16 angle;
    s16 x_offset;
    s16 y_offset;
    s32 temp_s4;
    s32 temp_s5;
    s16 temp_v0;
    s16 temp_v0_2;
    s8 temp_a1;
    void *var_s6;

    state = &D_00299E10;
    angle = ((*(s16 *)0x01ED5478 << 10) >> 12) - 0x200;
    if (D_0034F710 == 0) {
        var_s6 = func_002297C0(func_00209D20());
        temp_v0 = *(s16 *)0x01ED006C;
        if (temp_v0 != 0) {
            temp_a1 = *(s8 *)0x01ED5440;
            y_offset = offset_y_0021DAA0(temp_v0);
            x_offset = (temp_a1 * -0x280) / 100;
            if (*(s8 *)0x01ED5488 != 0) {
                var_s6 = func_00218970(var_s6, &D_00298AD0, x_offset, y_offset);
                *(s8 *)0x01ED5488 = 0;
            }
            if (func_001F12A0(0x1F) == 0) {
                if ((*(s8 *)0x01ED5406 == 1) && (*(s16 *)0x01ED006C != 0)) {
                    sp80 = D_0029A7B0;
                    sp90 = D_0029A7C0;
                    *(s16 *)0x01ED5404 = func_002159D0(1, 0);
                    func_001F22B0(0x1F, &sp80);
                    func_001F2430(0x1F, &sp90);
                    func_001E8780(0x1F, -1, func_001DE1A0(*(s16 *)0x01ED5404), 1);
                    *(s8 *)0x01ED5406 = 2;
                    *(s16 *)0x01ED543A = 0;
                }
            }
            if ((func_001F1300(0x1F) != 0) && (*(s8 *)0x01ED5406 == 2)) {
                temp_v0_2 = *(s16 *)0x01ED543A;
                if (temp_v0_2 < 0x80) {
                    *(s16 *)0x01ED543A = temp_v0_2 + 8;
                }
                if (*(s16 *)0x01ED543A >= 0x80) {
                    *(s16 *)0x01ED543A = 0x80;
                }
                temp_s4 = D_00298AD2;
                temp_s5 = D_00298AD0;
                var_s6 = func_0021DFF0(var_s6, 0x1F, temp_s5 + x_offset,
                    temp_s4 + y_offset, (f32)func_001DE260(*(s16 *)0x01ED5404),
                    D_00298AD4 - temp_s5, D_00298ADA - temp_s4, *(s16 *)0x01ED543A);
            }
        }
        if (*(s8 *)0x01ED5472 != 0) {
            var_s6 = func_0023BFF0(var_s6, *state ^ 1, *(s32 *)0x01ED5474, (f32)angle, 0.0f);
        }
        *(s8 *)0x01ED5481 = 0;
        func_00209D30((s32) var_s6);
    }
}

INCLUDE_ASM("asm/nonmatchings/main_062", func_0021DDA0);

INCLUDE_ASM("asm/nonmatchings/main_062", func_0021DFF0);

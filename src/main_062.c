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

INCLUDE_ASM("asm/nonmatchings/main_062", func_0021C350);

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

INCLUDE_ASM("asm/nonmatchings/main_062", func_0021DAA0);

INCLUDE_ASM("asm/nonmatchings/main_062", func_0021DDA0);

INCLUDE_ASM("asm/nonmatchings/main_062", func_0021DFF0);

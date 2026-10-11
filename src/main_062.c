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

INCLUDE_ASM("asm/nonmatchings/main_062", func_0021BB90);

INCLUDE_ASM("asm/nonmatchings/main_062", func_0021BC10);

f32 func_0021C320(f32 fparg0, f32 fparg1, f32 fparg2, f32 fparg3, f32 fparg4) {
    return 3.0f * (((fparg4 * (fparg1 - fparg0)) / fparg3) + ((fparg3 * (fparg2 - fparg1)) / fparg4));
}

INCLUDE_ASM("asm/nonmatchings/main_062", func_0021C350);

INCLUDE_ASM("asm/nonmatchings/main_062", func_0021C450);

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

/* Geometry: matrices, cameras, screen matrices (RhGeom_*). */

#include "common.h"

/* Starts the matrix stack. */
s32 RhGeom_Init(void) {
    RhGeom_Related = 0;
    return 1;
}

/* Ends the matrix stack. */
s32 RhGeom_Term(void) {
    return 1;
}

/* Loads matrix `p` into the VU0 registers. */
asm void RhGeom_SetMatrix(void *p) {
    .set noreorder
    beqz a0, L_0020BAAC
    nop
    lqc2 vf28, 0x0(a0)
    lqc2 vf29, 0x10(a0)
    lqc2 vf30, 0x20(a0)
    b L_0020BAC0
    lqc2 vf31, 0x30(a0)
L_0020BAAC:
    vsub.xyzw vf31, vf0, vf0
    vadd.w vf31, vf31, vf0
    vmr32.xyzw vf30, vf31
    vmr32.xyzw vf29, vf30
    vmr32.xyzw vf28, vf29
L_0020BAC0:
    jr ra
    nop
}

/* Stores the VU0 matrix into `p`. */
asm void RhGeom_GetMatrix(void *p) {
    .set noreorder
    sqc2 vf28, 0x0(a0)
    sqc2 vf29, 0x10(a0)
    sqc2 vf30, 0x20(a0)
    jr ra
    sqc2 vf31, 0x30(a0)
}

/* Pushes matrix `matrix` on the matrix stack (VU0). */
asm void RhGeom_PushMatrix(s32 matrix) {
    .set noreorder
    lw a2, RhGeom_Related
    la v1, matrixStack
    sll a1, a2, 3
    subu a1, a1, a2
    sll a1, a1, 4
    addu v1, v1, a1
    sqc2 vf28, 0x0(v1)
    sqc2 vf29, 0x10(v1)
    sqc2 vf30, 0x20(v1)
    beqz a0, L_0020BB38
    sqc2 vf31, 0x30(v1)
    lqc2 vf28, 0x0(a0)
    lqc2 vf29, 0x10(a0)
    lqc2 vf30, 0x20(a0)
    lqc2 vf31, 0x30(a0)
    nop
L_0020BB38:
    lw v1, RhGeom_Related
    addiu v1, v1, 0x1
    .set reorder
    sw v1, RhGeom_Related
    jr ra
}

/* Pops the matrix stack. */
asm void RhGeom_PopMatrix(void) {
    .set noreorder
    lw a0, RhGeom_Related
    la v1, matrixStack
    addiu a0, a0, -0x1
    sw a0, RhGeom_Related
    lw a1, RhGeom_Related
    sll a0, a1, 3
    subu a0, a0, a1
    sll a0, a0, 4
    addu v1, v1, a0
    lqc2 vf28, 0x0(v1)
    lqc2 vf29, 0x10(v1)
    lqc2 vf30, 0x20(v1)
    jr ra
    lqc2 vf31, 0x30(v1)
}

/* Empties the matrix stack. */
s32 RhGeom_ResetMatrixStack(void) {
    RhGeom_Related = 0;
    return 1;
}

/* Sets `matrix` to the identity. */
asm void RhGeom_UnitMatrix(void *matrix) {
    .set noreorder
    bnez a0, L_0020BBD0
    nop
    vsub.xyzw vf31, vf0, vf0
    vadd.w vf31, vf31, vf0
    vmr32.xyzw vf30, vf31
    vmr32.xyzw vf29, vf30
    b L_0020BBF4
    vmr32.xyzw vf28, vf29
L_0020BBD0:
    vsub.xyzw vf4, vf0, vf0
    vadd.w vf4, vf4, vf0
    vmr32.xyzw vf5, vf4
    vmr32.xyzw vf6, vf5
    vmr32.xyzw vf7, vf6
    sqc2 vf4, 0x30(a0)
    sqc2 vf5, 0x20(a0)
    sqc2 vf6, 0x10(a0)
    sqc2 vf7, 0x0(a0)
L_0020BBF4:
    jr ra
    nop
}

/* dst = dst x src (VU0). */
asm void RhGeom_MulMatrix(s32 dst, void *src) {
    .set noreorder
    bnez a0, L_0020BC6C
    nop
    lqc2 vf8, 0x0(a1)
    lqc2 vf9, 0x10(a1)
    lqc2 vf10, 0x20(a1)
    lqc2 vf11, 0x30(a1)
    vmulax.xyzw ACC, vf28, vf8x
    vmadday.xyzw ACC, vf29, vf8y
    vmaddaz.xyzw ACC, vf30, vf8z
    vmaddw.xyzw vf20, vf31, vf8w
    vmulax.xyzw ACC, vf28, vf9x
    vmadday.xyzw ACC, vf29, vf9y
    vmaddaz.xyzw ACC, vf30, vf9z
    vmaddw.xyzw vf21, vf31, vf9w
    vmulax.xyzw ACC, vf28, vf10x
    vmadday.xyzw ACC, vf29, vf10y
    vmaddaz.xyzw ACC, vf30, vf10z
    vmaddw.xyzw vf22, vf31, vf10w
    vmulax.xyzw ACC, vf28, vf11x
    vmadday.xyzw ACC, vf29, vf11y
    vmaddaz.xyzw ACC, vf30, vf11z
    vmaddw.xyzw vf23, vf31, vf11w
    vmove.xyzw vf28, vf20
    vmove.xyzw vf29, vf21
    vmove.xyzw vf30, vf22
    b L_0020BCDC
    vmove.xyzw vf31, vf23
L_0020BC6C:
    lqc2 vf4, 0x0(a0)
    lqc2 vf5, 0x10(a0)
    lqc2 vf6, 0x20(a0)
    lqc2 vf7, 0x30(a0)
    lqc2 vf8, 0x0(a1)
    vmulax.xyzw ACC, vf4, vf8x
    vmadday.xyzw ACC, vf5, vf8y
    vmaddaz.xyzw ACC, vf6, vf8z
    vmaddw.xyzw vf9, vf7, vf8w
    sqc2 vf9, 0x0(a0)
    lqc2 vf8, 0x10(a1)
    vmulax.xyzw ACC, vf4, vf8x
    vmadday.xyzw ACC, vf5, vf8y
    vmaddaz.xyzw ACC, vf6, vf8z
    vmaddw.xyzw vf9, vf7, vf8w
    sqc2 vf9, 0x10(a0)
    lqc2 vf8, 0x20(a1)
    vmulax.xyzw ACC, vf4, vf8x
    vmadday.xyzw ACC, vf5, vf8y
    vmaddaz.xyzw ACC, vf6, vf8z
    vmaddw.xyzw vf9, vf7, vf8w
    sqc2 vf9, 0x20(a0)
    lqc2 vf8, 0x30(a1)
    vmulax.xyzw ACC, vf4, vf8x
    vmadday.xyzw ACC, vf5, vf8y
    vmaddaz.xyzw ACC, vf6, vf8z
    vmaddw.xyzw vf9, vf7, vf8w
    sqc2 vf9, 0x30(a0)
L_0020BCDC:
    jr ra
    nop
}

/* dst = src x dst (VU0). */
asm void RhGeom_MulMatrixRev(s32 dst, s32 src) {
    .set noreorder
    bnez a0, L_0020BD5C
    nop
    lqc2 vf8, 0x0(a1)
    lqc2 vf9, 0x10(a1)
    lqc2 vf10, 0x20(a1)
    lqc2 vf11, 0x30(a1)
    vmulax.xyzw ACC, vf8, vf28x
    vmadday.xyzw ACC, vf9, vf28y
    vmaddaz.xyzw ACC, vf10, vf28z
    vmaddw.xyzw vf20, vf11, vf28w
    vmulax.xyzw ACC, vf8, vf29x
    vmadday.xyzw ACC, vf9, vf29y
    vmaddaz.xyzw ACC, vf10, vf29z
    vmaddw.xyzw vf21, vf11, vf29w
    vmulax.xyzw ACC, vf8, vf30x
    vmadday.xyzw ACC, vf9, vf30y
    vmaddaz.xyzw ACC, vf10, vf30z
    vmaddw.xyzw vf22, vf11, vf30w
    vmulax.xyzw ACC, vf8, vf31x
    vmadday.xyzw ACC, vf9, vf31y
    vmaddaz.xyzw ACC, vf10, vf31z
    vmaddw.xyzw vf23, vf11, vf31w
    vmove.xyzw vf28, vf20
    vmove.xyzw vf29, vf21
    vmove.xyzw vf30, vf22
    b L_0020BDCC
    vmove.xyzw vf31, vf23
L_0020BD5C:
    lqc2 vf4, 0x0(a1)
    lqc2 vf5, 0x10(a1)
    lqc2 vf6, 0x20(a1)
    lqc2 vf7, 0x30(a1)
    lqc2 vf8, 0x0(a0)
    vmulax.xyzw ACC, vf4, vf8x
    vmadday.xyzw ACC, vf5, vf8y
    vmaddaz.xyzw ACC, vf6, vf8z
    vmaddw.xyzw vf9, vf7, vf8w
    sqc2 vf9, 0x0(a0)
    lqc2 vf8, 0x10(a0)
    vmulax.xyzw ACC, vf4, vf8x
    vmadday.xyzw ACC, vf5, vf8y
    vmaddaz.xyzw ACC, vf6, vf8z
    vmaddw.xyzw vf9, vf7, vf8w
    sqc2 vf9, 0x10(a0)
    lqc2 vf8, 0x20(a0)
    vmulax.xyzw ACC, vf4, vf8x
    vmadday.xyzw ACC, vf5, vf8y
    vmaddaz.xyzw ACC, vf6, vf8z
    vmaddw.xyzw vf9, vf7, vf8w
    sqc2 vf9, 0x20(a0)
    lqc2 vf8, 0x30(a0)
    vmulax.xyzw ACC, vf4, vf8x
    vmadday.xyzw ACC, vf5, vf8y
    vmaddaz.xyzw ACC, vf6, vf8z
    vmaddw.xyzw vf9, vf7, vf8w
    sqc2 vf9, 0x30(a0)
L_0020BDCC:
    jr ra
    nop
}

typedef struct Matrix_0020BDE0 {
    f32 m[4][4];
} Matrix_0020BDE0;

/* dst = the inverse of matrix src. */
void RhGeom_InvertMatrix(void *dst, void *src) {
    Matrix_0020BDE0 result;
    f32 det;

    det = ((((Matrix_0020BDE0 *)src)->m[0][0] * ((((((Matrix_0020BDE0 *)src)->m[3][2] * (((Matrix_0020BDE0 *)src)->m[1][3] * ((Matrix_0020BDE0 *)src)->m[2][1]) + (((Matrix_0020BDE0 *)src)->m[3][3] * (((Matrix_0020BDE0 *)src)->m[1][1] * ((Matrix_0020BDE0 *)src)->m[2][2]) + ((Matrix_0020BDE0 *)src)->m[3][1] * (((Matrix_0020BDE0 *)src)->m[1][2] * ((Matrix_0020BDE0 *)src)->m[2][3])))
            - ((Matrix_0020BDE0 *)src)->m[3][1] * (((Matrix_0020BDE0 *)src)->m[1][3] * ((Matrix_0020BDE0 *)src)->m[2][2])) - ((Matrix_0020BDE0 *)src)->m[3][3] * (((Matrix_0020BDE0 *)src)->m[1][2] * ((Matrix_0020BDE0 *)src)->m[2][1])) - ((Matrix_0020BDE0 *)src)->m[3][2] * (((Matrix_0020BDE0 *)src)->m[1][1] * ((Matrix_0020BDE0 *)src)->m[2][3])) - ((Matrix_0020BDE0 *)src)->m[0][1] * ((((((Matrix_0020BDE0 *)src)->m[3][2] * (((Matrix_0020BDE0 *)src)->m[1][3] * ((Matrix_0020BDE0 *)src)->m[2][0]) + (((Matrix_0020BDE0 *)src)->m[3][3] * (((Matrix_0020BDE0 *)src)->m[1][0] * ((Matrix_0020BDE0 *)src)->m[2][2]) + ((Matrix_0020BDE0 *)src)->m[3][0] * (((Matrix_0020BDE0 *)src)->m[1][2] * ((Matrix_0020BDE0 *)src)->m[2][3])))
            - ((Matrix_0020BDE0 *)src)->m[3][0] * (((Matrix_0020BDE0 *)src)->m[1][3] * ((Matrix_0020BDE0 *)src)->m[2][2])) - ((Matrix_0020BDE0 *)src)->m[3][3] * (((Matrix_0020BDE0 *)src)->m[1][2] * ((Matrix_0020BDE0 *)src)->m[2][0])) - ((Matrix_0020BDE0 *)src)->m[3][2] * (((Matrix_0020BDE0 *)src)->m[1][0] * ((Matrix_0020BDE0 *)src)->m[2][3]))) + ((Matrix_0020BDE0 *)src)->m[0][2] * ((((((Matrix_0020BDE0 *)src)->m[3][1] * (((Matrix_0020BDE0 *)src)->m[1][3] * ((Matrix_0020BDE0 *)src)->m[2][0]) + (((Matrix_0020BDE0 *)src)->m[3][3] * (((Matrix_0020BDE0 *)src)->m[1][0] * ((Matrix_0020BDE0 *)src)->m[2][1]) + ((Matrix_0020BDE0 *)src)->m[3][0] * (((Matrix_0020BDE0 *)src)->m[1][1] * ((Matrix_0020BDE0 *)src)->m[2][3])))
            - ((Matrix_0020BDE0 *)src)->m[3][0] * (((Matrix_0020BDE0 *)src)->m[1][3] * ((Matrix_0020BDE0 *)src)->m[2][1])) - ((Matrix_0020BDE0 *)src)->m[3][3] * (((Matrix_0020BDE0 *)src)->m[1][1] * ((Matrix_0020BDE0 *)src)->m[2][0])) - ((Matrix_0020BDE0 *)src)->m[3][1] * (((Matrix_0020BDE0 *)src)->m[1][0] * ((Matrix_0020BDE0 *)src)->m[2][3]))) - ((Matrix_0020BDE0 *)src)->m[0][3] * ((((((Matrix_0020BDE0 *)src)->m[3][1] * (((Matrix_0020BDE0 *)src)->m[1][2] * ((Matrix_0020BDE0 *)src)->m[2][0]) + (((Matrix_0020BDE0 *)src)->m[3][2] * (((Matrix_0020BDE0 *)src)->m[1][0] * ((Matrix_0020BDE0 *)src)->m[2][1]) + ((Matrix_0020BDE0 *)src)->m[3][0] * (((Matrix_0020BDE0 *)src)->m[1][1] * ((Matrix_0020BDE0 *)src)->m[2][2])))
            - ((Matrix_0020BDE0 *)src)->m[3][0] * (((Matrix_0020BDE0 *)src)->m[1][2] * ((Matrix_0020BDE0 *)src)->m[2][1])) - ((Matrix_0020BDE0 *)src)->m[3][2] * (((Matrix_0020BDE0 *)src)->m[1][1] * ((Matrix_0020BDE0 *)src)->m[2][0])) - ((Matrix_0020BDE0 *)src)->m[3][1] * (((Matrix_0020BDE0 *)src)->m[1][0] * ((Matrix_0020BDE0 *)src)->m[2][2]));

    if (det != 0.0f) {
        result.m[0][0] = 1.0 * (((((((Matrix_0020BDE0 *)src)->m[3][2] * (((Matrix_0020BDE0 *)src)->m[1][3] * ((Matrix_0020BDE0 *)src)->m[2][1]) + (((Matrix_0020BDE0 *)src)->m[3][3] * (((Matrix_0020BDE0 *)src)->m[1][1] * ((Matrix_0020BDE0 *)src)->m[2][2]) + ((Matrix_0020BDE0 *)src)->m[3][1] * (((Matrix_0020BDE0 *)src)->m[1][2] * ((Matrix_0020BDE0 *)src)->m[2][3])))
            - ((Matrix_0020BDE0 *)src)->m[3][1] * (((Matrix_0020BDE0 *)src)->m[1][3] * ((Matrix_0020BDE0 *)src)->m[2][2])) - ((Matrix_0020BDE0 *)src)->m[3][3] * (((Matrix_0020BDE0 *)src)->m[1][2] * ((Matrix_0020BDE0 *)src)->m[2][1])) - ((Matrix_0020BDE0 *)src)->m[3][2] * (((Matrix_0020BDE0 *)src)->m[1][1] * ((Matrix_0020BDE0 *)src)->m[2][3])) / det);
        result.m[1][0] = -1.0 * (((((((Matrix_0020BDE0 *)src)->m[3][2] * (((Matrix_0020BDE0 *)src)->m[1][3] * ((Matrix_0020BDE0 *)src)->m[2][0]) + (((Matrix_0020BDE0 *)src)->m[3][3] * (((Matrix_0020BDE0 *)src)->m[1][0] * ((Matrix_0020BDE0 *)src)->m[2][2]) + ((Matrix_0020BDE0 *)src)->m[3][0] * (((Matrix_0020BDE0 *)src)->m[1][2] * ((Matrix_0020BDE0 *)src)->m[2][3])))
            - ((Matrix_0020BDE0 *)src)->m[3][0] * (((Matrix_0020BDE0 *)src)->m[1][3] * ((Matrix_0020BDE0 *)src)->m[2][2])) - ((Matrix_0020BDE0 *)src)->m[3][3] * (((Matrix_0020BDE0 *)src)->m[1][2] * ((Matrix_0020BDE0 *)src)->m[2][0])) - ((Matrix_0020BDE0 *)src)->m[3][2] * (((Matrix_0020BDE0 *)src)->m[1][0] * ((Matrix_0020BDE0 *)src)->m[2][3])) / det);
        result.m[2][0] = 1.0 * (((((((Matrix_0020BDE0 *)src)->m[3][1] * (((Matrix_0020BDE0 *)src)->m[1][3] * ((Matrix_0020BDE0 *)src)->m[2][0]) + (((Matrix_0020BDE0 *)src)->m[3][3] * (((Matrix_0020BDE0 *)src)->m[1][0] * ((Matrix_0020BDE0 *)src)->m[2][1]) + ((Matrix_0020BDE0 *)src)->m[3][0] * (((Matrix_0020BDE0 *)src)->m[1][1] * ((Matrix_0020BDE0 *)src)->m[2][3])))
            - ((Matrix_0020BDE0 *)src)->m[3][0] * (((Matrix_0020BDE0 *)src)->m[1][3] * ((Matrix_0020BDE0 *)src)->m[2][1])) - ((Matrix_0020BDE0 *)src)->m[3][3] * (((Matrix_0020BDE0 *)src)->m[1][1] * ((Matrix_0020BDE0 *)src)->m[2][0])) - ((Matrix_0020BDE0 *)src)->m[3][1] * (((Matrix_0020BDE0 *)src)->m[1][0] * ((Matrix_0020BDE0 *)src)->m[2][3])) / det);
        result.m[3][0] = -1.0 * (((((((Matrix_0020BDE0 *)src)->m[3][1] * (((Matrix_0020BDE0 *)src)->m[1][2] * ((Matrix_0020BDE0 *)src)->m[2][0]) + (((Matrix_0020BDE0 *)src)->m[3][2] * (((Matrix_0020BDE0 *)src)->m[1][0] * ((Matrix_0020BDE0 *)src)->m[2][1]) + ((Matrix_0020BDE0 *)src)->m[3][0] * (((Matrix_0020BDE0 *)src)->m[1][1] * ((Matrix_0020BDE0 *)src)->m[2][2])))
            - ((Matrix_0020BDE0 *)src)->m[3][0] * (((Matrix_0020BDE0 *)src)->m[1][2] * ((Matrix_0020BDE0 *)src)->m[2][1])) - ((Matrix_0020BDE0 *)src)->m[3][2] * (((Matrix_0020BDE0 *)src)->m[1][1] * ((Matrix_0020BDE0 *)src)->m[2][0])) - ((Matrix_0020BDE0 *)src)->m[3][1] * (((Matrix_0020BDE0 *)src)->m[1][0] * ((Matrix_0020BDE0 *)src)->m[2][2])) / det);

        result.m[0][1] = -1.0 * (
            ((((((Matrix_0020BDE0 *)src)->m[3][2] * (((Matrix_0020BDE0 *)src)->m[0][3] * ((Matrix_0020BDE0 *)src)->m[2][1]) + (((Matrix_0020BDE0 *)src)->m[3][3] * (((Matrix_0020BDE0 *)src)->m[0][1] * ((Matrix_0020BDE0 *)src)->m[2][2]) + ((Matrix_0020BDE0 *)src)->m[3][1] * (((Matrix_0020BDE0 *)src)->m[0][2] * ((Matrix_0020BDE0 *)src)->m[2][3])))
                - ((Matrix_0020BDE0 *)src)->m[3][1] * (((Matrix_0020BDE0 *)src)->m[0][3] * ((Matrix_0020BDE0 *)src)->m[2][2])) - ((Matrix_0020BDE0 *)src)->m[3][3] * (((Matrix_0020BDE0 *)src)->m[0][2] * ((Matrix_0020BDE0 *)src)->m[2][1])) - ((Matrix_0020BDE0 *)src)->m[3][2] * (((Matrix_0020BDE0 *)src)->m[0][1] * ((Matrix_0020BDE0 *)src)->m[2][3])) / det);
        result.m[1][1] = 1.0 * (
            ((((((Matrix_0020BDE0 *)src)->m[3][2] * (((Matrix_0020BDE0 *)src)->m[0][3] * ((Matrix_0020BDE0 *)src)->m[2][0]) + (((Matrix_0020BDE0 *)src)->m[3][3] * (((Matrix_0020BDE0 *)src)->m[0][0] * ((Matrix_0020BDE0 *)src)->m[2][2]) + ((Matrix_0020BDE0 *)src)->m[3][0] * (((Matrix_0020BDE0 *)src)->m[0][2] * ((Matrix_0020BDE0 *)src)->m[2][3])))
                - ((Matrix_0020BDE0 *)src)->m[3][0] * (((Matrix_0020BDE0 *)src)->m[0][3] * ((Matrix_0020BDE0 *)src)->m[2][2])) - ((Matrix_0020BDE0 *)src)->m[3][3] * (((Matrix_0020BDE0 *)src)->m[0][2] * ((Matrix_0020BDE0 *)src)->m[2][0])) - ((Matrix_0020BDE0 *)src)->m[3][2] * (((Matrix_0020BDE0 *)src)->m[0][0] * ((Matrix_0020BDE0 *)src)->m[2][3])) / det);
        result.m[2][1] = -1.0 * (
            ((((((Matrix_0020BDE0 *)src)->m[3][1] * (((Matrix_0020BDE0 *)src)->m[0][3] * ((Matrix_0020BDE0 *)src)->m[2][0]) + (((Matrix_0020BDE0 *)src)->m[3][3] * (((Matrix_0020BDE0 *)src)->m[0][0] * ((Matrix_0020BDE0 *)src)->m[2][1]) + ((Matrix_0020BDE0 *)src)->m[3][0] * (((Matrix_0020BDE0 *)src)->m[0][1] * ((Matrix_0020BDE0 *)src)->m[2][3])))
                - ((Matrix_0020BDE0 *)src)->m[3][0] * (((Matrix_0020BDE0 *)src)->m[0][3] * ((Matrix_0020BDE0 *)src)->m[2][1])) - ((Matrix_0020BDE0 *)src)->m[3][3] * (((Matrix_0020BDE0 *)src)->m[0][1] * ((Matrix_0020BDE0 *)src)->m[2][0])) - ((Matrix_0020BDE0 *)src)->m[3][1] * (((Matrix_0020BDE0 *)src)->m[0][0] * ((Matrix_0020BDE0 *)src)->m[2][3])) / det);
        result.m[3][1] = 1.0 * (
            ((((((Matrix_0020BDE0 *)src)->m[3][1] * (((Matrix_0020BDE0 *)src)->m[0][2] * ((Matrix_0020BDE0 *)src)->m[2][0]) + (((Matrix_0020BDE0 *)src)->m[3][2] * (((Matrix_0020BDE0 *)src)->m[0][0] * ((Matrix_0020BDE0 *)src)->m[2][1]) + ((Matrix_0020BDE0 *)src)->m[3][0] * (((Matrix_0020BDE0 *)src)->m[0][1] * ((Matrix_0020BDE0 *)src)->m[2][2])))
                - ((Matrix_0020BDE0 *)src)->m[3][0] * (((Matrix_0020BDE0 *)src)->m[0][2] * ((Matrix_0020BDE0 *)src)->m[2][1])) - ((Matrix_0020BDE0 *)src)->m[3][2] * (((Matrix_0020BDE0 *)src)->m[0][1] * ((Matrix_0020BDE0 *)src)->m[2][0])) - ((Matrix_0020BDE0 *)src)->m[3][1] * (((Matrix_0020BDE0 *)src)->m[0][0] * ((Matrix_0020BDE0 *)src)->m[2][2])) / det);

        result.m[0][2] = 1.0 * (
            ((((((Matrix_0020BDE0 *)src)->m[3][2] * (((Matrix_0020BDE0 *)src)->m[0][3] * ((Matrix_0020BDE0 *)src)->m[1][1]) + (((Matrix_0020BDE0 *)src)->m[3][3] * (((Matrix_0020BDE0 *)src)->m[0][1] * ((Matrix_0020BDE0 *)src)->m[1][2]) + ((Matrix_0020BDE0 *)src)->m[3][1] * (((Matrix_0020BDE0 *)src)->m[0][2] * ((Matrix_0020BDE0 *)src)->m[1][3])))
                - ((Matrix_0020BDE0 *)src)->m[3][1] * (((Matrix_0020BDE0 *)src)->m[0][3] * ((Matrix_0020BDE0 *)src)->m[1][2])) - ((Matrix_0020BDE0 *)src)->m[3][3] * (((Matrix_0020BDE0 *)src)->m[0][2] * ((Matrix_0020BDE0 *)src)->m[1][1])) - ((Matrix_0020BDE0 *)src)->m[3][2] * (((Matrix_0020BDE0 *)src)->m[0][1] * ((Matrix_0020BDE0 *)src)->m[1][3])) / det);
        result.m[1][2] = -1.0 * (
            ((((((Matrix_0020BDE0 *)src)->m[3][2] * (((Matrix_0020BDE0 *)src)->m[0][3] * ((Matrix_0020BDE0 *)src)->m[1][0]) + (((Matrix_0020BDE0 *)src)->m[3][3] * (((Matrix_0020BDE0 *)src)->m[0][0] * ((Matrix_0020BDE0 *)src)->m[1][2]) + ((Matrix_0020BDE0 *)src)->m[3][0] * (((Matrix_0020BDE0 *)src)->m[0][2] * ((Matrix_0020BDE0 *)src)->m[1][3])))
                - ((Matrix_0020BDE0 *)src)->m[3][0] * (((Matrix_0020BDE0 *)src)->m[0][3] * ((Matrix_0020BDE0 *)src)->m[1][2])) - ((Matrix_0020BDE0 *)src)->m[3][3] * (((Matrix_0020BDE0 *)src)->m[0][2] * ((Matrix_0020BDE0 *)src)->m[1][0])) - ((Matrix_0020BDE0 *)src)->m[3][2] * (((Matrix_0020BDE0 *)src)->m[0][0] * ((Matrix_0020BDE0 *)src)->m[1][3])) / det);
        result.m[2][2] = 1.0 * (
            ((((((Matrix_0020BDE0 *)src)->m[3][1] * (((Matrix_0020BDE0 *)src)->m[0][3] * ((Matrix_0020BDE0 *)src)->m[1][0]) + (((Matrix_0020BDE0 *)src)->m[3][3] * (((Matrix_0020BDE0 *)src)->m[0][0] * ((Matrix_0020BDE0 *)src)->m[1][1]) + ((Matrix_0020BDE0 *)src)->m[3][0] * (((Matrix_0020BDE0 *)src)->m[0][1] * ((Matrix_0020BDE0 *)src)->m[1][3])))
                - ((Matrix_0020BDE0 *)src)->m[3][0] * (((Matrix_0020BDE0 *)src)->m[0][3] * ((Matrix_0020BDE0 *)src)->m[1][1])) - ((Matrix_0020BDE0 *)src)->m[3][3] * (((Matrix_0020BDE0 *)src)->m[0][1] * ((Matrix_0020BDE0 *)src)->m[1][0])) - ((Matrix_0020BDE0 *)src)->m[3][1] * (((Matrix_0020BDE0 *)src)->m[0][0] * ((Matrix_0020BDE0 *)src)->m[1][3])) / det);
        result.m[3][2] = -1.0 * (
            ((((((Matrix_0020BDE0 *)src)->m[3][1] * (((Matrix_0020BDE0 *)src)->m[0][2] * ((Matrix_0020BDE0 *)src)->m[1][0]) + (((Matrix_0020BDE0 *)src)->m[3][2] * (((Matrix_0020BDE0 *)src)->m[0][0] * ((Matrix_0020BDE0 *)src)->m[1][1]) + ((Matrix_0020BDE0 *)src)->m[3][0] * (((Matrix_0020BDE0 *)src)->m[0][1] * ((Matrix_0020BDE0 *)src)->m[1][2])))
                - ((Matrix_0020BDE0 *)src)->m[3][0] * (((Matrix_0020BDE0 *)src)->m[0][2] * ((Matrix_0020BDE0 *)src)->m[1][1])) - ((Matrix_0020BDE0 *)src)->m[3][2] * (((Matrix_0020BDE0 *)src)->m[0][1] * ((Matrix_0020BDE0 *)src)->m[1][0])) - ((Matrix_0020BDE0 *)src)->m[3][1] * (((Matrix_0020BDE0 *)src)->m[0][0] * ((Matrix_0020BDE0 *)src)->m[1][2])) / det);

        result.m[0][3] = -1.0 * (
            ((((((Matrix_0020BDE0 *)src)->m[2][2] * (((Matrix_0020BDE0 *)src)->m[0][3] * ((Matrix_0020BDE0 *)src)->m[1][1]) + (((Matrix_0020BDE0 *)src)->m[2][3] * (((Matrix_0020BDE0 *)src)->m[0][1] * ((Matrix_0020BDE0 *)src)->m[1][2]) + ((Matrix_0020BDE0 *)src)->m[2][1] * (((Matrix_0020BDE0 *)src)->m[0][2] * ((Matrix_0020BDE0 *)src)->m[1][3])))
                - ((Matrix_0020BDE0 *)src)->m[2][1] * (((Matrix_0020BDE0 *)src)->m[0][3] * ((Matrix_0020BDE0 *)src)->m[1][2])) - ((Matrix_0020BDE0 *)src)->m[2][3] * (((Matrix_0020BDE0 *)src)->m[0][2] * ((Matrix_0020BDE0 *)src)->m[1][1])) - ((Matrix_0020BDE0 *)src)->m[2][2] * (((Matrix_0020BDE0 *)src)->m[0][1] * ((Matrix_0020BDE0 *)src)->m[1][3])) / det);
        result.m[1][3] = 1.0 * (
            ((((((Matrix_0020BDE0 *)src)->m[2][2] * (((Matrix_0020BDE0 *)src)->m[0][3] * ((Matrix_0020BDE0 *)src)->m[1][0]) + (((Matrix_0020BDE0 *)src)->m[2][3] * (((Matrix_0020BDE0 *)src)->m[0][0] * ((Matrix_0020BDE0 *)src)->m[1][2]) + ((Matrix_0020BDE0 *)src)->m[2][0] * (((Matrix_0020BDE0 *)src)->m[0][2] * ((Matrix_0020BDE0 *)src)->m[1][3])))
                - ((Matrix_0020BDE0 *)src)->m[2][0] * (((Matrix_0020BDE0 *)src)->m[0][3] * ((Matrix_0020BDE0 *)src)->m[1][2])) - ((Matrix_0020BDE0 *)src)->m[2][3] * (((Matrix_0020BDE0 *)src)->m[0][2] * ((Matrix_0020BDE0 *)src)->m[1][0])) - ((Matrix_0020BDE0 *)src)->m[2][2] * (((Matrix_0020BDE0 *)src)->m[0][0] * ((Matrix_0020BDE0 *)src)->m[1][3])) / det);
        result.m[2][3] = -1.0 * (
            ((((((Matrix_0020BDE0 *)src)->m[2][1] * (((Matrix_0020BDE0 *)src)->m[0][3] * ((Matrix_0020BDE0 *)src)->m[1][0]) + (((Matrix_0020BDE0 *)src)->m[2][3] * (((Matrix_0020BDE0 *)src)->m[0][0] * ((Matrix_0020BDE0 *)src)->m[1][1]) + ((Matrix_0020BDE0 *)src)->m[2][0] * (((Matrix_0020BDE0 *)src)->m[0][1] * ((Matrix_0020BDE0 *)src)->m[1][3])))
                - ((Matrix_0020BDE0 *)src)->m[2][0] * (((Matrix_0020BDE0 *)src)->m[0][3] * ((Matrix_0020BDE0 *)src)->m[1][1])) - ((Matrix_0020BDE0 *)src)->m[2][3] * (((Matrix_0020BDE0 *)src)->m[0][1] * ((Matrix_0020BDE0 *)src)->m[1][0])) - ((Matrix_0020BDE0 *)src)->m[2][1] * (((Matrix_0020BDE0 *)src)->m[0][0] * ((Matrix_0020BDE0 *)src)->m[1][3])) / det);
        result.m[3][3] = 1.0 * (
            ((((((Matrix_0020BDE0 *)src)->m[2][1] * (((Matrix_0020BDE0 *)src)->m[0][2] * ((Matrix_0020BDE0 *)src)->m[1][0]) + (((Matrix_0020BDE0 *)src)->m[2][2] * (((Matrix_0020BDE0 *)src)->m[0][0] * ((Matrix_0020BDE0 *)src)->m[1][1]) + ((Matrix_0020BDE0 *)src)->m[2][0] * (((Matrix_0020BDE0 *)src)->m[0][1] * ((Matrix_0020BDE0 *)src)->m[1][2])))
                - ((Matrix_0020BDE0 *)src)->m[2][0] * (((Matrix_0020BDE0 *)src)->m[0][2] * ((Matrix_0020BDE0 *)src)->m[1][1])) - ((Matrix_0020BDE0 *)src)->m[2][2] * (((Matrix_0020BDE0 *)src)->m[0][1] * ((Matrix_0020BDE0 *)src)->m[1][0])) - ((Matrix_0020BDE0 *)src)->m[2][1] * (((Matrix_0020BDE0 *)src)->m[0][0] * ((Matrix_0020BDE0 *)src)->m[1][2])) / det);

        *(Matrix_0020BDE0 *)dst = result;
    }
}

/* The rotation matrix for angles src (x, y, z) into dst. */
void RhGeom_GetRotXYZMatrix(void *dst, void *src) {
    f32 *matrix = dst;
    s32 *angles = src;
    f32 cx;
    f32 sx;
    f32 cy;
    f32 sy;
    f32 cz;
    f32 sz;

    cx = RhMath_CosI(angles[0]);
    sx = RhMath_SinI(angles[0]);
    cy = RhMath_CosI(angles[1]);
    sy = RhMath_SinI(angles[1]);
    cz = RhMath_CosI(angles[2]);
    sz = RhMath_SinI(angles[2]);
    matrix[0] = cy * cz;
    matrix[4] = cz * (sx * sy) - cx * sz;
    matrix[8] = cz * (cx * sy) + sx * sz;
    matrix[1] = cy * sz;
    matrix[5] = sz * (sx * sy) + cx * cz;
    matrix[9] = sz * (cx * sy) - sx * cz;
    matrix[2] = -sy;
    matrix[6] = sx * cy;
    matrix[10] = cx * cy;
    matrix[3] = 0.0f;
    matrix[7] = 0.0f;
    matrix[11] = 0.0f;
    matrix[12] = 0.0f;
    matrix[13] = 0.0f;
    matrix[14] = 0.0f;
    matrix[15] = 1.0f;
}

typedef struct Vec4_0020C750 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4_0020C750;

/* The rotation matrix turning around vector `axis` by `angle` into `dst`. */
void RhGeom_GetRotVectorMatrix(void *dst, void *axis, s32 angle) {
    f32 *m = dst;
    Vec4_0020C750 v;
    f32 c;
    f32 s;
    f32 t;

    v = *(Vec4_0020C750 *)axis;
    c = RhMath_CosI(angle);
    t = 1.0f - c;
    s = RhMath_SinI(angle);
    RhGeom_NormalizeVector(&v.x);
    m[0] = c + t * (v.x * v.x);
    m[4] = t * (v.x * v.y) - v.z * s;
    m[8] = t * (v.x * v.z) + v.y * s;
    m[1] = t * (v.x * v.y) + v.z * s;
    m[5] = c + t * (v.y * v.y);
    m[9] = t * (v.y * v.z) - v.x * s;
    m[2] = t * (v.x * v.z) - v.y * s;
    m[6] = t * (v.y * v.z) + v.x * s;
    m[10] = c + t * (v.z * v.z);
    m[12] = 0.0f;
    m[13] = 0.0f;
    m[14] = 0.0f;
    m[3] = 0.0f;
    m[7] = 0.0f;
    m[11] = 0.0f;
    m[15] = 1.0f;
}

typedef struct {
    f32 rotation[12];
    f32 translation[3];
} Matrix_0020C8F0;

/* The translation matrix for `pos` into `dst`. */
void RhGeom_GetTransMatrix(void *dst, f32 *pos) {
    Matrix_0020C8F0 *matrix = dst;

    RhGeom_UnitMatrix(dst);
    matrix->translation[0] = pos[0];
    matrix->translation[1] = pos[1];
    matrix->translation[2] = pos[2];
}

typedef struct {
    f32 m[3][4];
    f32 t[3];
} Matrix_0020C940;

/* The matrix scale x rotation x translation from p1 (scale), p2 (angles), p3 (position) into `dst`. */
void RhGeom_GetScaleRotXYZTransMatrix(void *dst, void *p1, void *p2, void *p3) {
    Matrix_0020C940 *mtx = dst;
    f32 *arg1 = p1;
    s32 *arg2 = p2;
    f32 *arg3 = p3;
    f32 cx;
    f32 sx;
    f32 cy;
    f32 sy;
    f32 cz;
    f32 sz;

    RhGeom_UnitMatrix(dst);
    if (arg3 != NULL) {
        mtx->t[0] = arg3[0];
        mtx->t[1] = arg3[1];
        mtx->t[2] = arg3[2];
    }
    if (arg2 != NULL) {
        cx = RhMath_CosI(arg2[0]);
        sx = RhMath_SinI(arg2[0]);
        cy = RhMath_CosI(arg2[1]);
        sy = RhMath_SinI(arg2[1]);
        cz = RhMath_CosI(arg2[2]);
        sz = RhMath_SinI(arg2[2]);
        mtx->m[0][0] = cy * cz;
        mtx->m[1][0] = sx * sy * cz - cx * sz;
        mtx->m[2][0] = cx * sy * cz + sx * sz;
        mtx->m[0][1] = cy * sz;
        mtx->m[1][1] = sx * sy * sz + cx * cz;
        mtx->m[2][1] = cx * sy * sz - sx * cz;
        mtx->m[0][2] = -sy;
        mtx->m[1][2] = sx * cy;
        mtx->m[2][2] = cx * cy;
    }
    if (arg1 != NULL) {
        mtx->m[0][0] *= arg1[0];
        mtx->m[0][1] *= arg1[0];
        mtx->m[0][2] *= arg1[0];
        mtx->m[1][0] *= arg1[1];
        mtx->m[1][1] *= arg1[1];
        mtx->m[1][2] *= arg1[1];
        mtx->m[2][0] *= arg1[2];
        mtx->m[2][1] *= arg1[2];
        mtx->m[2][2] *= arg1[2];
    }
}

/* Scales matrix `matrix` by `scaleIn` (x, y, z). */
void RhGeom_ScaleMatrix(void *matrix, void *scaleIn) {
    f32 m[4][4];
    register f32 *scale = scaleIn;

    if (matrix == NULL) {
        asm {
            lqc2 vf8, 0x0(scale)
            vmulx.xyzw vf28, vf28, vf8x
            vmuly.xyzw vf29, vf29, vf8y
            vmulz.xyzw vf30, vf30, vf8z
        }
    } else {
        RhGeom_UnitMatrix(m);
        m[0][0] = scale[0];
        m[1][1] = scale[1];
        m[2][2] = scale[2];
        RhGeom_MulMatrix((s32)matrix, m);
    }
}

/* Rotates matrix `matrixIn` by angles `rot` (x, y, z). */
void RhGeom_RotXYZMatrix(s32 matrixIn, u32 *rot) {
    extern void RhGeom_GetRotXYZMatrix();
    f32 matrix[4][4];

    RhGeom_GetRotXYZMatrix(matrix, rot);
    RhGeom_MulMatrix(matrixIn, matrix);
}

/* Rotates matrix `matrixIn` around a vector. */
void RhGeom_RotVectorMatrix(s32 matrixIn) {
    extern void RhGeom_GetRotVectorMatrix();
    f32 matrix[4][4];

    RhGeom_GetRotVectorMatrix(matrix);
    RhGeom_MulMatrix(matrixIn, matrix);
}

/* dst = dst x scale x rotation x translation. */
/* Apply translate, rotate (X, Y, Z angles) and scale to the current VU0 matrix (vf28-vf31),
   or with a destination matrix build the transform there (RhGeom_GetScaleRotXYZTransMatrix) and multiply. */
void RhGeom_ScaleRotXYZTransMatrix(void *dst, register f32 *scale, s32 *rot, register f32 *trans) {
    f32 m[4][4];
    f32 a0, b0, a1, b1, a2, b2;

    if (dst == NULL) {
    if (trans != NULL) {
        asm {
            lqc2 vf8, 0x0(trans)
            vmulax.xyzw ACC, vf28, vf8x
            vmadday.xyzw ACC, vf29, vf8y
            vmaddaz.xyzw ACC, vf30, vf8z
            vmaddw.xyzw vf31, vf31, vf0w
        }
    }
    if (rot != NULL) {
        a0 = RhMath_CosI(rot[0]);
        b0 = RhMath_SinI(rot[0]);
        a1 = RhMath_CosI(rot[1]);
        b1 = RhMath_SinI(rot[1]);
        a2 = RhMath_CosI(rot[2]);
        b2 = RhMath_SinI(rot[2]);
        m[0][0] = a1 * a2;
        m[1][0] = a2 * (b0 * b1) - a0 * b2;
        m[2][0] = a2 * (a0 * b1) + b0 * b2;
        m[0][1] = a1 * b2;
        m[1][1] = b2 * (b0 * b1) + a0 * a2;
        m[2][1] = b2 * (a0 * b1) - b0 * a2;
        m[0][2] = -b1;
        m[1][2] = b0 * a1;
        m[2][2] = a0 * a1;
        m[0][3] = 0.0f;
        m[1][3] = 0.0f;
        m[2][3] = 0.0f;
        {
        register f32 *p = m[0];
        asm {
            lqc2 vf8, 0x0(p)
            lqc2 vf9, 0x10(p)
            lqc2 vf10, 0x20(p)
            vmulax.xyzw ACC, vf28, vf8x
            vmadday.xyzw ACC, vf29, vf8y
            vmaddaz.xyzw ACC, vf30, vf8z
            vmaddw.xyzw vf20, vf31, vf8w
            vmulax.xyzw ACC, vf28, vf9x
            vmadday.xyzw ACC, vf29, vf9y
            vmaddaz.xyzw ACC, vf30, vf9z
            vmaddw.xyzw vf21, vf31, vf9w
            vmulax.xyzw ACC, vf28, vf10x
            vmadday.xyzw ACC, vf29, vf10y
            vmaddaz.xyzw ACC, vf30, vf10z
            vmaddw.xyzw vf22, vf31, vf10w
            vmove.xyzw vf28, vf20
            vmove.xyzw vf29, vf21
            vmove.xyzw vf30, vf22
        }
        }
    }
    if (scale != NULL) {
        asm {
            lqc2 vf8, 0x0(scale)
            vmulx.xyz vf28, vf28, vf8x
            vmuly.xyz vf29, vf29, vf8y
            vmulz.xyz vf30, vf30, vf8z
        }
    }
    } else {
        RhGeom_GetScaleRotXYZTransMatrix(m, scale, rot, trans);
        RhGeom_MulMatrix((s32)dst, m);
    }
}

/* out = matrix x vec (VU0; NULL `matrix` uses the VU0 matrix). */
asm void RhGeom_MulMatrixVector(void *out, void *matrix, void *vec) {
    .set noreorder
    bnez a1, L_0020CDF4
    addiu sp, sp, -0x10
    lqc2 vf8, 0x0(a2)
    vmulax.xyzw ACC, vf28, vf8x
    vmadday.xyzw ACC, vf29, vf8y
    vmaddaz.xyzw ACC, vf30, vf8z
    vmaddw.xyzw vf9, vf31, vf8w
    b L_0020CEF8
    sqc2 vf9, 0x0(a0)
L_0020CDF4:
    lwc1 f6, 0x4(a2)
    lwc1 f0, 0x10(a1)
    lwc1 f3, 0x8(a2)
    lwc1 f2, 0x20(a1)
    lwc1 f5, 0x0(a2)
    lwc1 f4, 0x0(a1)
    lwc1 f1, 0xC(a2)
    mula.s f6, f0
    lwc1 f0, 0x30(a1)
    mul.s f2, f3, f2
    addiu v1, sp, 0x0
    madd.s f4, f5, f4
    adda.s f2, f4
    madd.s f0, f1, f0
    swc1 f0, 0x0(sp)
    lwc1 f6, 0x0(a2)
    lwc1 f0, 0x4(a1)
    lwc1 f3, 0x8(a2)
    lwc1 f2, 0x24(a1)
    lwc1 f5, 0x4(a2)
    lwc1 f4, 0x14(a1)
    lwc1 f1, 0xC(a2)
    mula.s f6, f0
    lwc1 f0, 0x34(a1)
    mul.s f2, f3, f2
    madd.s f4, f5, f4
    adda.s f2, f4
    madd.s f0, f1, f0
    swc1 f0, 0x4(sp)
    lwc1 f6, 0x0(a2)
    lwc1 f0, 0x8(a1)
    lwc1 f3, 0x8(a2)
    lwc1 f2, 0x28(a1)
    lwc1 f5, 0x4(a2)
    lwc1 f4, 0x18(a1)
    lwc1 f1, 0xC(a2)
    mula.s f6, f0
    lwc1 f0, 0x38(a1)
    mul.s f2, f3, f2
    madd.s f4, f5, f4
    adda.s f2, f4
    madd.s f0, f1, f0
    swc1 f0, 0x8(sp)
    lwc1 f6, 0x0(a2)
    lwc1 f0, 0xC(a1)
    lwc1 f3, 0x8(a2)
    lwc1 f2, 0x2C(a1)
    lwc1 f5, 0x4(a2)
    lwc1 f4, 0x1C(a1)
    lwc1 f1, 0xC(a2)
    mula.s f6, f0
    lwc1 f0, 0x3C(a1)
    mul.s f2, f3, f2
    madd.s f4, f5, f4
    adda.s f2, f4
    madd.s f0, f1, f0
    swc1 f0, 0xC(sp)
    .word 0xC4630000
    .word 0xC4620004
    .word 0xC4610008
    .word 0xC460000C
    swc1 f3, 0x0(a0)
    swc1 f2, 0x4(a0)
    swc1 f1, 0x8(a0)
    swc1 f0, 0xC(a0)
L_0020CEF8:
    jr ra
    addiu sp, sp, 0x10
}

/* Transforms an array of vectors by a matrix (VU0). */
asm void RhGeom_MulMatrixVectorArray() {
    .set noreorder
    bnez a1, L_0020CF38
    addiu sp, sp, -0x10
L_0020CF08:
    lqc2 vf8, 0x0(a2)
    vmulax.xyzw ACC, vf28, vf8x
    vmadday.xyzw ACC, vf29, vf8y
    vmaddaz.xyzw ACC, vf30, vf8z
    vmaddw.xyzw vf9, vf31, vf8w
    sqc2 vf9, 0x0(a0)
    addi a3, a3, -0x1
    addi a0, a0, 0x10
    bne zero, a3, L_0020CF08
    addi a2, a2, 0x10
    b L_0020D060
    addiu sp, sp, 0x10
L_0020CF38:
    addiu t0, sp, 0x0
    b L_0020D050
    paddub t1, zero, zero
L_0020CF44:
    lwc1 f6, 0x4(a2)
    lwc1 f0, 0x10(a1)
    lwc1 f3, 0x8(a2)
    lwc1 f2, 0x20(a1)
    lwc1 f5, 0x0(a2)
    lwc1 f4, 0x0(a1)
    lwc1 f1, 0xC(a2)
    mula.s f6, f0
    lwc1 f0, 0x30(a1)
    mul.s f2, f3, f2
    addiu t1, t1, 0x1
    madd.s f4, f5, f4
    adda.s f2, f4
    madd.s f0, f1, f0
    swc1 f0, 0x0(sp)
    lwc1 f6, 0x0(a2)
    lwc1 f0, 0x4(a1)
    lwc1 f3, 0x8(a2)
    lwc1 f2, 0x24(a1)
    lwc1 f5, 0x4(a2)
    lwc1 f4, 0x14(a1)
    lwc1 f1, 0xC(a2)
    mula.s f6, f0
    lwc1 f0, 0x34(a1)
    mul.s f2, f3, f2
    madd.s f4, f5, f4
    adda.s f2, f4
    madd.s f0, f1, f0
    swc1 f0, 0x4(sp)
    lwc1 f6, 0x0(a2)
    lwc1 f0, 0x8(a1)
    lwc1 f3, 0x8(a2)
    lwc1 f2, 0x28(a1)
    lwc1 f5, 0x4(a2)
    lwc1 f4, 0x18(a1)
    lwc1 f1, 0xC(a2)
    mula.s f6, f0
    lwc1 f0, 0x38(a1)
    mul.s f2, f3, f2
    madd.s f4, f5, f4
    adda.s f2, f4
    madd.s f0, f1, f0
    swc1 f0, 0x8(sp)
    lwc1 f6, 0x0(a2)
    lwc1 f0, 0xC(a1)
    lwc1 f3, 0x8(a2)
    lwc1 f2, 0x2C(a1)
    lwc1 f5, 0x4(a2)
    lwc1 f1, 0xC(a2)
    lwc1 f4, 0x1C(a1)
    mula.s f6, f0
    lwc1 f0, 0x3C(a1)
    mul.s f2, f3, f2
    addiu a2, a2, 0x10
    madd.s f4, f5, f4
    adda.s f2, f4
    madd.s f0, f1, f0
    swc1 f0, 0xC(sp)
    lwc1 f3, 0x0(t0)
    lwc1 f2, 0x4(t0)
    lwc1 f1, 0x8(t0)
    lwc1 f0, 0xC(t0)
    swc1 f3, 0x0(a0)
    swc1 f2, 0x4(a0)
    swc1 f1, 0x8(a0)
    swc1 f0, 0xC(a0)
    addiu a0, a0, 0x10
L_0020D050:
    slt v1, t1, a3
    bnez v1, L_0020CF44
    nop
    addiu sp, sp, 0x10
L_0020D060:
    jr ra
    nop
}

/* Scales `vec` to length 1. */
void RhGeom_NormalizeVector(f32 *vec) {
    f32 length;

    length = func_001A6C60(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
    vec[0] /= length;
    vec[1] /= length;
    vec[2] /= length;
    vec[3] = vec[3];
}

/* The length of `vec`. */
f32 RhGeom_GetVectorScalor(f32 *vec) {
    return func_001A6C60(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
}

/* The distance between points a and b. */
f32 RhGeom_GetPointsDistance(f32 *a, f32 *b) {
    f32 x = a[0] - b[0];
    f32 y = a[1] - b[1];
    f32 z = a[2] - b[2];

    return func_001A6C60(x * x + y * y + z * z);
}

/* out = a x b (cross product). */
void RhGeom_OuterProduct(f32 *out, f32 *a, f32 *b) {
    out[0] = a[1] * b[2] - a[2] * b[1];
    out[1] = a[2] * b[0] - a[0] * b[2];
    out[2] = a[0] * b[1] - a[1] * b[0];
    out[3] = a[3];
}

/* a . b (dot product). */
f32 RhGeom_InnerProduct(f32 *a, f32 *b) {
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

/* Blends two angles (the shorter way round) with weights weight0 and weight1. */
s64 RhGeom_RotationInterpolate(s32 from, s32 to, f32 weight0, f32 weight1) {
    extern s64 func_001A22C0(s32, s32, f32);
    s32 end = to & 0xFFFF;
    s32 start = from & 0xFFFF;
    s32 delta = end - start;

    if (delta > 0x8000) {
        end -= 0x10000;
    } else if (delta < -0x8000) {
        end += 0x10000;
    }

    return func_001A22C0(from, to, (f32)start * weight0 + (f32)end * weight1 + 0.5f);
}

/* Blends two rotations (x, y, z) with weights weight0 and weight1 into `out`. */
void RhGeom_RoationComplexInterpolate(s32 *out, s32 *from, s32 *to, f32 weight0, f32 weight1) {
    s32 end[2][3];
    s32 diff[2][3];
    s32 start[3];
    f32 sinX;
    f32 cosX;
    f32 sinZ;
    f32 cosZ;
    f32 cosY;
    f32 cosY2;
    s32 d;
    s32 pick;

    start[0] = (from[0] & 0xFFFF) << 4;
    start[1] = (from[1] & 0xFFFF) << 4;
    start[2] = (from[2] & 0xFFFF) << 4;
    end[0][0] = (to[0] & 0xFFFF) << 4;
    end[0][1] = (to[1] & 0xFFFF) << 4;
    end[0][2] = (to[2] & 0xFFFF) << 4;
    sinX = RhMath_SinI(to[0]);
    cosX = RhMath_CosI(to[0]);
    sinZ = RhMath_SinI(to[2]);
    cosZ = RhMath_CosI(to[2]);
    cosY = RhMath_CosI(to[1]);
    end[1][1] = (0x80000 - end[0][1]) & 0xFFFFF;
    cosY2 = RhMath_CosI(end[1][1] >> 4);
    end[1][0] = ((s32)(65536.0f * (func_001A6C18(sinX * cosY / cosY2, cosX * cosY / cosY2) / 6.2831855f)) & 0xFFFF) << 4;
    end[1][2] = ((s32)(65536.0f * (func_001A6C18(cosY * sinZ / cosY2, cosY * cosZ / cosY2) / 6.2831855f)) & 0xFFFF) << 4;
    {
        s32 i;
        s32 j;

        for (i = 0; i < 2; i++) {
            for (j = 0; j < 3; j++) {
                d = end[i][j] - start[j];
                if (d > 0x80000) {
                    end[i][j] -= 0x100000;
                    diff[i][j] = 0x100000 - d;
                } else if (d < -0x80000) {
                    end[i][j] += 0x100000;
                    diff[i][j] = d + 0x100000;
                } else if (d < 0) {
                    diff[i][j] = -d;
                } else {
                    diff[i][j] = d;
                }
            }
        }
    }
    pick = (diff[0][0] + diff[0][1] + diff[0][2] > diff[1][0] + diff[1][1] + diff[1][2]) ? 1 : 0;
    out[0] = (((s32)(start[0] * weight0 + end[pick][0] * weight1) & 0xFFFFF) + 8) >> 4;
    out[1] = (((s32)(start[1] * weight0 + end[pick][1] * weight1) & 0xFFFFF) + 8) >> 4;
    out[2] = (((s32)(start[2] * weight0 + end[pick][2] * weight1) & 0xFFFFF) + 8) >> 4;
}

extern f32 vecX;
extern f32 D_003269F4;
extern f32 D_003269F8;
extern f32 vecY;
extern f32 D_00326A04;
extern f32 D_00326A08;
extern f32 vecZ;
extern f32 D_00326A14;
extern f32 D_00326A18;

typedef union Angles_0020D5E0 {
    s32 a[4];
    __int128 q;
} Angles_0020D5E0;

typedef union Matrix_0020D5E0 {
    f32 m[4][4];
    __int128 q[4];
} Matrix_0020D5E0;

/* Scales a vector to length 1. */
static inline void normalize_0020D5E0(f32 *dest, f32 *src) {
    f32 length;

    length = func_001A6C60(src[0] * src[0] + src[1] * src[1] + src[2] * src[2]);
    dest[0] = src[0] / length;
    dest[1] = src[1] / length;
    dest[2] = src[2] / length;
    dest[3] = src[3];
}

/* The camera matrix for a camera at `eye` looking at `target`, rolled by `roll`, into `out`. */
void RhGeom_CreateCameraMatrix2(f32 *out, f32 *eye, f32 *target, s32 roll) {
    Angles_0020D5E0 angles;
    Matrix_0020D5E0 matrix;

    vecX = target[2];
    D_003269F4 = 0.0f;
    D_003269F8 = -target[0];
    vecY = -target[1] * target[0];
    D_00326A04 = target[0] * target[0] + target[2] * target[2];
    D_00326A08 = -target[1] * target[2];
    *(__int128 *)&vecZ = *(__int128 *)target;
    normalize_0020D5E0(&vecX, &vecX);
    normalize_0020D5E0(&vecY, &vecY);
    normalize_0020D5E0(&vecZ, &vecZ);
    out[0] = -vecX;
    out[1] = -D_003269F4;
    out[2] = -D_003269F8;
    out[3] = 0.0f;
    out[4] = -vecY;
    out[5] = -D_00326A04;
    out[6] = -D_00326A08;
    out[7] = 0.0f;
    out[8] = vecZ;
    out[9] = D_00326A14;
    out[10] = D_00326A18;
    out[11] = 0.0f;
    out[12] = eye[0];
    out[13] = eye[1];
    out[14] = eye[2];
    out[15] = 1.0f;
    angles.a[0] = 0;
    angles.a[1] = 0;
    angles.a[2] = roll;
    RhGeom_GetRotXYZMatrix(&matrix, angles.a);
    RhGeom_MulMatrix((s32) out, &matrix);
    RhGeom_InvertMatrix(out, out);
}

/* The projection matrix for the screen distance, aspect, clip and screen offsets into `out`. */
void RhGeom_GetScreenMatrix(f32 *out, f32 fparg0, f32 fparg1, f32 fparg2, f32 fparg3, f32 fparg4, f32 fparg5, f32 fparg6, f32 fparg7, f32 arg_sp0) {
    extern void RhGeom_UnitMatrix(void *);
    f32 matrix[16];

    RhGeom_UnitMatrix(matrix);
    matrix[0] = fparg0;
    matrix[5] = fparg0;
    matrix[10] = 0.0f;
    matrix[15] = 0.0f;
    matrix[14] = 1.0f;
    matrix[11] = 1.0f;
    RhGeom_UnitMatrix(out);
    out[0] = fparg1;
    out[5] = fparg2;
    out[10] = (arg_sp0 * fparg7 * (-fparg5 + fparg6)) / (-fparg7 + arg_sp0);
    out[12] = fparg3;
    out[13] = fparg4;
    out[14] = (-fparg6 * fparg7 + fparg5 * arg_sp0) / (-fparg7 + arg_sp0);
    RhGeom_MulMatrix((s32) out, matrix);
}

/* Geometry extras: light matrices, scale-rotate-translate (RhGeomEx_*). */

#include "common.h"

/* Loads the point-light matrix into VU0, then multiplies it by the light matrix `lights`. */
void RhGeomEx_SetMatrixForStraightLight(void *lights) {
    register void *m = lights;

    RhGeomEx_SetMatrixForPointLight();
    asm {
        lqc2 vf8, 0x0(m)
        lqc2 vf9, 0x10(m)
        lqc2 vf10, 0x20(m)
        lqc2 vf11, 0x30(m)
        vmulax.xyzw ACC, vf8, vf28x
        vmadday.xyzw ACC, vf9, vf28y
        vmaddaz.xyzw ACC, vf10, vf28z
        vmaddw.xyzw vf28, vf11, vf28w
        vmulax.xyzw ACC, vf8, vf29x
        vmadday.xyzw ACC, vf9, vf29y
        vmaddaz.xyzw ACC, vf10, vf29z
        vmaddw.xyzw vf29, vf11, vf29w
        vmulax.xyzw ACC, vf8, vf30x
        vmadday.xyzw ACC, vf9, vf30y
        vmaddaz.xyzw ACC, vf10, vf30z
        vmaddw.xyzw vf30, vf11, vf30w
        vmulax.xyzw ACC, vf8, vf31x
        vmadday.xyzw ACC, vf9, vf31y
        vmaddaz.xyzw ACC, vf10, vf31z
        vmaddw.xyzw vf31, vf11, vf31w
    }
}

/* Loads the point-light matrix into VU0. */
asm void RhGeomEx_SetMatrixForPointLight(void) {
    .set noreorder
    la v1, vecNormal
    vmul.xyz vf1, vf28, vf28
    vmul.xyz vf2, vf29, vf29
    vmul.xyz vf3, vf30, vf30
    vmove.x vf5, vf1
    vmove.x vf6, vf2
    vmove.x vf7, vf3
    vmr32.xyzw vf1, vf1
    vmr32.xyzw vf2, vf2
    vmr32.xyzw vf3, vf3
    vadd.x vf5, vf5, vf1
    vadd.x vf6, vf6, vf2
    vadd.x vf7, vf7, vf3
    vmr32.xyzw vf1, vf1
    vmr32.xyzw vf2, vf2
    vmr32.xyzw vf3, vf3
    vadd.x vf5, vf5, vf1
    vadd.x vf6, vf6, vf2
    vadd.x vf7, vf7, vf3
    lqc2 vf8, 0x0(v1)
    vrsqrt Q, vf8x, vf5x
    vsub.w vf24, vf0, vf0
    vwaitq
    vmulq.xyz vf24, vf28, Q
    vrsqrt Q, vf8x, vf6x
    vsub.w vf25, vf0, vf0
    vwaitq
    vmulq.xyz vf25, vf29, Q
    vrsqrt Q, vf8x, vf7x
    vsub.w vf26, vf0, vf0
    vwaitq
    jr ra
    vmulq.xyz vf26, vf30, Q
}

/* Stores the second VU0 matrix into `out`. */
asm void RhGeomEx_GetMatrix(void *out) {
    .set noreorder
    sqc2 vf28, 0x0(a0)
    sqc2 vf29, 0x10(a0)
    sqc2 vf30, 0x20(a0)
    sqc2 vf31, 0x30(a0)
    sqc2 vf24, 0x40(a0)
    sqc2 vf25, 0x50(a0)
    jr ra
    sqc2 vf26, 0x60(a0)
}

/* Pushes the second VU0 matrix on its stack. */
asm void RhGeomEx_PushMatrix(void) {
    .set noreorder
    lw a1, D_0032A220
    la v1, matrixStack
    sll a0, a1, 3
    subu a0, a0, a1
    sll a0, a0, 4
    addu v1, v1, a0
    sqc2 vf28, 0x0(v1)
    sqc2 vf29, 0x10(v1)
    sqc2 vf30, 0x20(v1)
    sqc2 vf31, 0x30(v1)
    sqc2 vf24, 0x40(v1)
    sqc2 vf25, 0x50(v1)
    sqc2 vf26, 0x60(v1)
    sqc2 vf27, 0x70(v1)
    lw v1, D_0032A220
    addiu v1, v1, 0x1
    .set reorder
    sw v1, D_0032A220
    jr ra
}

/* Pops the second VU0 matrix stack. */
asm void RhGeomEx_PopMatrix(void) {
    .set noreorder
    lw a0, D_0032A220
    la v1, matrixStack
    addiu a0, a0, -0x1
    sw a0, D_0032A220
    lw a1, D_0032A220
    sll a0, a1, 3
    subu a0, a0, a1
    sll a0, a0, 4
    addu v1, v1, a0
    lqc2 vf28, 0x0(v1)
    lqc2 vf29, 0x10(v1)
    lqc2 vf30, 0x20(v1)
    lqc2 vf31, 0x30(v1)
    lqc2 vf24, 0x40(v1)
    lqc2 vf25, 0x50(v1)
    lqc2 vf26, 0x60(v1)
    jr ra
    lqc2 vf27, 0x70(v1)
}

/* The second VU0 matrix times scale x rotation x translation. */
/* RhGeom_ScaleRotXYZTransMatrix for the current matrix and its normal matrix: translate (vf28-vf31), rotate both
   (vf28-vf30 and vf24-vf26), scale (vf28-vf30). */
void RhGeomEx_ScaleRotXYZTransMatrix(register void *scale, void *rot, register void *trans) {
    f32 m[4][4];
    f32 a0, b0, a1, b1, a2, b2;

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
        a0 = RhMath_CosI(((s32 *)rot)[0]);
        b0 = RhMath_SinI(((s32 *)rot)[0]);
        a1 = RhMath_CosI(((s32 *)rot)[1]);
        b1 = RhMath_SinI(((s32 *)rot)[1]);
        a2 = RhMath_CosI(((s32 *)rot)[2]);
        b2 = RhMath_SinI(((s32 *)rot)[2]);
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
            vmulax.xyzw ACC, vf24, vf8x
            vmadday.xyzw ACC, vf25, vf8y
            vmaddaz.xyzw ACC, vf26, vf8z
            vmaddw.xyzw vf20, vf27, vf8w
            vmulax.xyzw ACC, vf24, vf9x
            vmadday.xyzw ACC, vf25, vf9y
            vmaddaz.xyzw ACC, vf26, vf9z
            vmaddw.xyzw vf21, vf27, vf9w
            vmulax.xyzw ACC, vf24, vf10x
            vmadday.xyzw ACC, vf25, vf10y
            vmaddaz.xyzw ACC, vf26, vf10z
            vmaddw.xyzw vf22, vf27, vf10w
            vmove.xyzw vf24, vf20
            vmove.xyzw vf25, vf21
            vmove.xyzw vf26, vf22
        }
        }
    }
    if (scale != NULL) {
        asm {
            lqc2 vf8, 0x0(scale)
            vmulx.xyzw vf28, vf28, vf8x
            vmuly.xyzw vf29, vf29, vf8y
            vmulz.xyzw vf30, vf30, vf8z
        }
    }
}

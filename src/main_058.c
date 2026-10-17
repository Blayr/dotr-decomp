#include "common.h"

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
extern f32 D_003269FC;
extern f32 vecY;
extern f32 D_00326A04;
extern f32 D_00326A08;
extern f32 D_00326A0C;
extern f32 vecZ;
extern f32 D_00326A14;
extern f32 D_00326A18;
extern f32 D_00326A1C;

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

/* Loads the directional-light matrix into VU0. */
/* normalize the current matrix (RhGeomEx_SetMatrixForPointLight), then multiply it by m */
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

typedef struct Entry_0020DDB0 {
    u8 pad0[0xC0];
    u8 unkC0[0x90];
    f32 centerX;
    f32 centerY;
    f32 unk158;
    f32 unk15C;
    f32 unk160;
    f32 width;
    f32 height;
    f32 unk16C;
    f32 farZ;
    f32 range;
    f32 unk178;
    f32 unk17C;
    f32 nearZ;
    u8 r;
    u8 g;
    u8 b;
    u8 a;
    u8 pad188[0x18];
} Entry_0020DDB0;

/* Starts the renderer's view: default screen, aspect, clip, fog and its stack. */
s32 RhView_Init(void) {
    extern s32 D_0032A294;
    extern Entry_0020DDB0 viewStack[];
    s32 width;
    s32 height;

    viewStackIndex = 0;
    D_0032A294 = 0;
    RhBase_GetScreenSize(&width, &height);
    viewStack[0].unk160 = 400.0f;
    viewStack[0].width = width;
    viewStack[0].height = height;
    viewStack[0].centerX = viewStack[0].width / 2.0f;
    viewStack[0].centerY = viewStack[0].height / 2.0f;
    viewStack[0].unk158 = 1.0f;
    viewStack[0].unk15C = 0.95f;
    viewStack[0].unk16C = 1.0f;
    viewStack[0].farZ = 10000.0f;
    viewStack[0].range = viewStack[0].farZ - 1000.0f;
    viewStack[0].unk178 = viewStack[0].farZ;
    viewStack[0].unk17C = 0.0f;
    viewStack[0].nearZ = 1000.0f;
    viewStack[0].a = 0xFF;
    viewStack[0].b = 0xFF;
    viewStack[0].g = 0xFF;
    viewStack[0].r = 0xFF;
    RhView_Reset(viewStack[0].unkC0);
    return 1;
}

/* Ends the renderer's view. */
s32 RhView_Term(void) {
    return 1;
}

typedef struct {
    __int128 data[9];
} Copy_0020DEF0;

extern u8 D_0032A360[];

/* The current view state into `out`. */
s32 RhView_GetCurView(void *out) {
    *(Copy_0020DEF0 *)out =
        *(Copy_0020DEF0 *)(D_0032A360 + viewStackIndex * 0x1A0);
    return 1;
}

typedef struct State_0020DF40 {
    u8 pad000[0x150];
    f32 field150;
    f32 field154;
    u8 pad158[8];
    f32 field160;
    f32 field164;
    f32 field168;
    u8 pad16C[0x34];
} State_0020DF40;

/* Sets the screen distance and the screen's centre and size. */
s32 RhView_SetScreen(f32 distance, f32 fparg1, f32 fparg2, f32 fparg3, f32 fparg4) {
    extern State_0020DF40 viewStack[];
    State_0020DF40 *state;

    state = &viewStack[viewStackIndex];
    state->field160 = distance;
    state->field164 = fparg1;
    state->field168 = fparg2;
    state->field150 = fparg3;
    state->field154 = fparg4;
    return 1;
}

typedef struct State_0020DF90 {
    u8 pad0[0x158];
    f32 field158;
    f32 field15C;
    u8 pad160[0x40];
} State_0020DF90;

/* Sets the aspect ratio (x, y). */
s32 RhView_SetAspect(f32 x, f32 y) {
    extern State_0020DF90 viewStack[];
    State_0020DF90 *state;

    state = &viewStack[viewStackIndex];
    state->field158 = x;
    state->field15C = y;
    return 1;
}

typedef struct {
    u8 pad_000[0x16C];
    f32 x;
    f32 y;
    u8 pad_174[0x2C];
} Entry_0020DFD0;

/* Sets the near and far clip depths. */
s32 RhView_SetClipZ(f32 near, f32 far) {
    extern Entry_0020DFD0 viewStack[];
    Entry_0020DFD0 *entry;

    entry = &viewStack[viewStackIndex];
    entry->x = near;
    entry->y = far;
    return 1;
}

typedef struct {
    u8 pad0[0x150];
    f32 x;
    f32 y;
    u8 pad158[0x48];
} Entry_0020E010;

extern s32 viewStackIndex; /* original: gRhView_nStackIndex */
extern Entry_0020E010 viewStack[]; /* original: gRhView_avl */

/* The screen centre. */
s32 RhView_GetScreenCenter(f32 *outX, f32 *outY) {
    Entry_0020E010 *e = &viewStack[viewStackIndex];

    *outX = e->x;
    *outY = e->y;
    return 1;
}

/* The screen distance. */
s32 RhView_GetScreenDist(f32 *out) {
    Entry_0020E010 *e = &viewStack[viewStackIndex];

    *out = *(f32 *)&e->pad158[8];
    return 1;
}

/* The near and far clip depths. */
s32 RhView_GetClipZ(f32 *outNear, f32 *outFar) {
    Entry_0020DFD0 *entry = (Entry_0020DFD0 *)&viewStack[viewStackIndex];

    *outNear = entry->x;
    *outFar = entry->y;
    return 1;
}

/* Sets the fog colour and its depth and height ranges. */
s32 RhView_SetFogParameter(void *colorIn, f32 nearZ, f32 farZ, f32 nearY, f32 farY) {
    typedef struct {
        u8 r;
        u8 g;
        u8 b;
        u8 a;
    } Color_0020E0D0;
    typedef struct {
        u8 pad[0x174];
        f32 x;
        f32 y;
        f32 z;
        f32 w;
        Color_0020E0D0 color;
        u8 pad188[0x18];
    } Entry_0020E0D0;
    Entry_0020E0D0 *entry;

    entry = (Entry_0020E0D0 *)&viewStack[viewStackIndex];
    entry->x = nearZ;
    entry->y = farZ;
    entry->z = nearY;
    entry->w = farY;
    entry->color = *(Color_0020E0D0 *)colorIn;
    return 1;
}

typedef struct Color_0020E130 {
    u8 r, g, b, a;
} Color_0020E130;

typedef struct Entry_0020E130 {
    u8 pad0[0x174];
    f32 values[4];
    Color_0020E130 color;
    u8 pad188[0x18];
} Entry_0020E130;

/* The fog ranges and colour. */
s32 RhView_GetFogParameter(f32 *outNearZ, f32 *outFarZ, f32 *outNearY, f32 *outFarY, u8 *outColor) {
    Entry_0020E130 *entry;

    entry = (Entry_0020E130 *)&viewStack[viewStackIndex];
    *outNearZ = entry->values[0];
    *outFarZ = entry->values[1];
    *outNearY = entry->values[2];
    *outFarY = entry->values[3];
    *(Color_0020E130 *)outColor = entry->color;
    return 1;
}

typedef struct {
    u8 pad[0x40];
    f32 vector40[4];
    f32 vector50[4];
    f32 vector60[4];
    f32 vector70[4];
    f32 vector80[4];
} State_0020E1A0;


/* Resets a view state to the defaults. */
s32 RhView_Reset(void *state) {
    if (state == NULL) {
        state = (u8 *)&viewStack[viewStackIndex] + 0xC0;
    }
    RhGeom_UnitMatrix(state);
    ((State_0020E1A0 *)state)->vector40[0] = 0.0f;
    ((State_0020E1A0 *)state)->vector40[1] = 0.0f;
    ((State_0020E1A0 *)state)->vector40[2] = 0.0f;
    ((State_0020E1A0 *)state)->vector40[3] = 1.0f;
    ((State_0020E1A0 *)state)->vector50[0] = 0.0f;
    ((State_0020E1A0 *)state)->vector50[1] = 0.0f;
    ((State_0020E1A0 *)state)->vector50[2] = -1.0f;
    ((State_0020E1A0 *)state)->vector50[3] = 0.0f;
    ((State_0020E1A0 *)state)->vector80[0] = 0.0f;
    ((State_0020E1A0 *)state)->vector60[0] = 0.0f;
    ((State_0020E1A0 *)state)->vector60[1] = 0.0f;
    ((State_0020E1A0 *)state)->vector60[2] = 0.0f;
    ((State_0020E1A0 *)state)->vector60[3] = 1.0f;
    ((State_0020E1A0 *)state)->vector70[0] = 0.0f;
    ((State_0020E1A0 *)state)->vector70[1] = 0.0f;
    ((State_0020E1A0 *)state)->vector70[2] = -1.0f;
    ((State_0020E1A0 *)state)->vector70[3] = 0.0f;
    ((State_0020E1A0 *)state)->vector80[1] = 0.0f;
    ((State_0020E1A0 *)state)->vector80[2] = 0.0f;
    ((State_0020E1A0 *)state)->vector80[3] = 0.0f;
    return 1;
}

/* Makes `view` the current view and builds its matrices. */
s32 RhView_Set(void *view) {
    typedef struct {
        u8 pad0[0x40];
        u8 unk40[0x80];
        u8 unkC0[0x90];
        f32 x;
        f32 y;
        u8 pad158[8];
        f32 radius;
        f32 width;
        f32 height;
        u8 pad16C[0x1C];
        f32 radius_squared;
        f32 width_squared;
        f32 height_squared;
        u8 pad194[0xC];
    } State_0020E260;
    State_0020E260 *state;

    state = (State_0020E260 *)&viewStack[viewStackIndex];
    RhMem_CopyMemory16(state->unkC0, view, 9);
    lRhView_ConstructMatrix();
    RhGeom_ResetMatrixStack();
    RhGeom_SetMatrix(state->unk40);
    state->radius_squared = 4186116.0f + state->radius * state->radius;
    state->width_squared = (state->width * state->width) / 4.0f + state->radius * state->radius;
    state->height_squared = (state->height * state->height) / 4.0f + state->radius * state->radius;
    RhGeom_GetMatrix(view);
    RhView_GetWorldViewMatrix(InvertView);
    RhGeom_InvertMatrix(InvertView, InvertView);
    return 1;
}

typedef struct State_0020E360 {
    u8 pad_000[0x40];
    f32 matrix[4][4];
    u8 pad_080[0xE0];
    f32 radius;
    f32 width;
    f32 height;
    u8 pad_16C[0x1C];
    f32 radius_squared;
    f32 width_squared;
    f32 height_squared;
    u8 pad_194[0xC];
} State_0020E360;

/* Changes the current view to `view` (and rebuilds its matrices). */
s32 RhView_Modify(void *view) {
    State_0020E360 *state;

    state = (State_0020E360 *)&viewStack[viewStackIndex];
    RhMem_CopyMemory16((u8 *)state + 0xC0, view, 9);
    lRhView_ConstructMatrix();
    RhGeom_SetMatrix(&state->matrix);
    RhMem_CopyMemory16(view, state->matrix, 4);
    state->radius_squared = 4186116.0f + state->radius * state->radius;
    state->width_squared = (state->width * state->width) / 4.0f +
                           state->radius * state->radius;
    state->height_squared = (state->height * state->height) / 4.0f +
                            state->radius * state->radius;
    RhView_GetWorldViewMatrix(InvertView);
    RhGeom_InvertMatrix(InvertView, InvertView);
    return 1;
}

typedef struct Copy_0020E460 {
    __int128 data[26];
} Copy_0020E460;

/* Saves the current view on the view stack. */
s32 RhView_PushStack(void) {
    extern u8 D_0032A440[];

    if (viewStackIndex + 1 >= 2) {
        return 0;
    }
    ((Copy_0020E460 *)D_0032A440)[viewStackIndex] = ((Copy_0020E460 *)viewStack)[viewStackIndex];
    viewStackIndex += 1;
    return 1;
}

/* Restores the view saved on the view stack. */
s32 RhView_PopStack(void) {
    if (viewStackIndex <= 0) {
        return 0;
    }
    viewStackIndex -= 1;
    return 1;
}

#ifndef GAME_H
/* The game translation unit already declares this array with its local type. */
extern unsigned char viewStack[]; /* original: gRhView_avl */
#endif


typedef struct Vec4_0020E520 {
    f32 x, y, z, w;
} Vec4_0020E520;

typedef struct State_0020E520 {
    Vec4_0020E520 point;
    Vec4_0020E520 normal;
    Vec4_0020E520 direction;
    Vec4_0020E520 displacement;
    f32 distance;
    s32 active;
} State_0020E520;

typedef struct Object_0020E520 {
    __int128 reserved0[4];
    Vec4_0020E520 point;
    Vec4_0020E520 direction;
    u8 reserved1[0x20];
    s32 angle;
    u8 reserved2[0xC];
} Object_0020E520;

typedef struct Block_0020E520 {
    __int128 data[26];
} Block_0020E520;

extern s32 D_0032A294;
extern u8 D_0032A360[];
extern u8 D_0032A440[];

/* Reflects a vector in a plane. */
static inline void reflect_0020E520(Vec4_0020E520 *v, Vec4_0020E520 *normal) {
    f32 twiceDot = 2.0f * (normal->x * v->x + normal->y * v->y + normal->z * v->z);
    v->x = twiceDot * normal->x - v->x;
    v->y = twiceDot * normal->y - v->y;
    v->z = twiceDot * normal->z - v->z;
}

/* Saves the view and mirrors it in the plane through `point` with `normal` (for fake reflections). */
s32 RhView_PushFakeMirror(f32 *point, f32 *normal, void *output) {
    extern State_0020E520 fakeMirrorSaved;
    extern s32 func_001A22C0(f32);
    State_0020E520 *state = &fakeMirrorSaved;
    Object_0020E520 *original = (Object_0020E520 *)D_0032A360;
    u8 scratch[0xA0 + 0xF];
    Vec4_0020E520 *up;
    f32 *cross;
    void *matrix;
    void *inverse;
    Object_0020E520 *object = (Object_0020E520 *)output;

    up = (Vec4_0020E520 *)(((u32)scratch + 0xF) & ~0xF);
    up->x = 0.0f;
    up->y = 1.0f;
    up->z = 0.0f;
    cross = (f32 *)((u8 *)up + 0x10);
    matrix = (u8 *)cross + 0x40;
    up->w = 0.0f;
    inverse = (u8 *)matrix + 0x40;
    if (D_0032A294 != 0) {
        return 0;
    }
    *object = *original;
    state->point = *(Vec4_0020E520 *)point;
    state->normal = *(Vec4_0020E520 *)normal;
    state->direction.x = -original->direction.x;
    state->direction.y = -original->direction.y;
    state->direction.z = -original->direction.z;
    state->displacement.x = original->point.x - state->point.x;
    state->displacement.y = original->point.y - state->point.y;
    state->displacement.z = original->point.z - state->point.z;
    state->distance = RhGeom_GetVectorScalor(&state->displacement.x);
    RhGeom_NormalizeVector(&state->normal.x);
    RhGeom_NormalizeVector(&state->direction.x);
    RhGeom_NormalizeVector(&state->displacement.x);
    reflect_0020E520(&state->direction, &state->normal);
    reflect_0020E520(&state->displacement, &state->normal);
    object->direction = state->direction;
    object->point.x = point[0] - state->displacement.x * state->distance;
    object->point.y = point[1] - state->displacement.y * state->distance;
    object->point.z = point[2] - state->displacement.z * state->distance;
    object->point.w = 0.0f;
    RhView_GetWorldViewMatrix(matrix);
    RhGeom_InvertMatrix(inverse, matrix);
    RhGeom_MulMatrixVector(up, inverse, up);
    reflect_0020E520(up, &state->normal);
    RhGeom_OuterProduct(cross, (f32 *)up, &object->direction.x);
    RhGeom_CreateCameraMatrix2(matrix, &object->point, &object->direction, 0);
    RhGeom_MulMatrixVector(cross, matrix, cross);
    object->angle = (s32)func_001A22C0(65536.0f * (func_001A6C18(cross[1], cross[0]) / 6.2831855f)) + 0x8000;
    if (viewStackIndex + 1 < 2) {
        ((Block_0020E520 *)D_0032A440)[viewStackIndex] = ((Block_0020E520 *)viewStack)[viewStackIndex];
        viewStackIndex++;
    }
    state->active = 1;
    return 1;
}

typedef struct {
    u8 padding[0x44];
    s32 ready;
} State_0020E970;

typedef struct {
    __int128 data[9];
} Buffer_0020E970;

extern State_0020E970 fakeMirrorSaved; /* original: gRhView_FakeMirror */
extern s32 D_0032A294;
extern u8 D_0032A360[];

/* Restores the view after a fake mirror. */
s32 RhView_PopFakeMirror(void *saved) {
    State_0020E970 *state = &fakeMirrorSaved;

    if (D_0032A294 == 0) {
        return 0;
    }
    if (viewStackIndex > 0) {
        viewStackIndex -= 1;
    }
    state->ready = 0;
    *(Buffer_0020E970 *)saved = *(Buffer_0020E970 *)D_0032A360;
    return 1;
}

#ifndef GAME_H
/* The game translation unit already declares this array with its local type. */
extern unsigned char viewStack[][0x1A0]; /* original: gRhView_avl */
#endif


typedef struct Object_0020E9F0 {
    u8 unk0[0x40];
    f32 matrix40[16];
    f32 matrix80[16];
    u8 unkC0[0x80];
    s32 unk140;
    u8 unk144[0xC];
    f32 unk150;
    f32 unk154;
    f32 unk158;
    f32 unk15C;
    f32 unk160;
    f32 unk164;
    f32 unk168;
    f32 unk16C;
    f32 unk170;
    u8 unk174[0x2C];
} Object_0020E9F0;


/* Builds the current view's world-view, view-screen and world-screen matrices. */
s32 lRhView_ConstructMatrix(void) {
    s32 sp50;
    s32 sp54;
    s32 sp58;
    s32 sp5C;
    f32 temp_f20;
    f32 temp_f21;
    Object_0020E9F0 *view;
    u8 *temp_s1;

    view = (Object_0020E9F0 *)&viewStack[viewStackIndex];
    temp_s1 = (u8 *) view + 0xC0;
    RhBase_GetScreenCenter(&sp50, &sp54);
    temp_f20 = ((f32) sp50 + view->unk150) - (view->unk164 / 2.0f);
    temp_f21 = ((f32) sp54 + view->unk154) - (view->unk168 / 2.0f);
    RhBase_GetZMinMax(&sp58, &sp5C);
    RhGeom_CreateCameraMatrix2(view->matrix40, temp_s1 + 0x40, temp_s1 + 0x50, *(s32 *) (temp_s1 + 0x80));
    RhGeom_GetScreenMatrix(view->matrix80, view->unk160, view->unk158, view->unk15C * RhBase_GetAspectY(NULL), temp_f20, temp_f21, (f32) sp58, (f32) sp5C, view->unk16C, 2.0f * view->unk170);
    RhMem_CopyMemory16(view, view->matrix80, 4);
    RhGeom_MulMatrix((s32) view, view->matrix40);
    RhMem_CopyMemory16(temp_s1, view, 4);
    return 1;
}

typedef struct {
    s32 words[16];
} Block_0020EB40;

/* The current world-to-screen matrix into `out`. */
void RhView_GetWorldScreenMatrix(void *out) {
    *(Block_0020EB40 *)out = *(Block_0020EB40 *)&viewStack[viewStackIndex];
}

typedef struct {
    s32 words[16];
} Block_0020EBA0;

extern u8 D_0032A2E0[][0x1A0];

/* The current world-to-view matrix into `out`. */
void RhView_GetWorldViewMatrix(void *out) {
    *(Block_0020EBA0 *)out = *(Block_0020EBA0 *)D_0032A2E0[viewStackIndex];
}

typedef struct {
    s32 words[16];
} Block_0020EC00;

typedef struct {
    Block_0020EC00 block;
    u8 padding[0x160];
} Entry_0020EC00;

extern Entry_0020EC00 D_0032A320[];

/* The current view-to-screen matrix into `dst`. */
void RhView_GetViewScreenMatrix(void *dst) {
    *(Block_0020EC00 *)dst = D_0032A320[viewStackIndex].block;
}

/* Sends the current view's matrices and clip values to VU1. */
s32 RhView_SendViewParameters(s32 packet) {
    u8 matrix_storage[0x4F];
    u8 *matrix;
    u8 *item;
    void *result;

    matrix = (u8 *)(((u32)matrix_storage + 0xF) & ~0xF);
    item = (u8 *)&viewStack[viewStackIndex];
    result = RhVu1Mac_SetViewScreenMatrix((void *)packet, item + 0x80);
    RhGeom_InvertMatrix(matrix, item);
    return (s32)RhVu1Mac_SetFogParameterEx(
        RhBase_SetFogColor(
            RhVu1Mac_SetClipParameter(RhVu1Mac_SetScreenWorldMatrix(result, matrix), 1,
                *(f32 *)(item + 0x160), *(f32 *)(item + 0x16C),
                *(f32 *)(item + 0x170)),
            item + 0x184),
        *(f32 *)(item + 0x174), *(f32 *)(item + 0x178),
        *(f32 *)(item + 0x17C), *(f32 *)(item + 0x180));
}

typedef struct {
    f32 x, y, z, w;
} Vec4_0020ED30;

/* The GS depth of point `point` (moved by `bias`). */
void RhView_GetSampleZ(void *point, f32 bias) {
    u8 buffer[31];
    Vec4_0020ED30 *vector;
    void *matrix;

    matrix = (u8 *)&viewStack[viewStackIndex] + 0x80;
    vector = (Vec4_0020ED30 *) (((u32) buffer + 15) & ~15);
    *vector = *(Vec4_0020ED30 *) point;
    vector->z -= bias;
    RhGeom_MulMatrixVector(vector, matrix, vector);
    func_001A23B0(vector->z / vector->w);
}

typedef __int128 DotrViewWord128;
struct DotrViewVector {
    float x, y, z;
    float unknown_w;
};
struct DotrViewQuad {
    unsigned char unknown_0;
    unsigned char unknown_1;
    unsigned char unknown_2;
    unsigned char unknown_3;
};
struct DotrViewBlock {
    DotrViewWord128 unknown_words[9];
};
struct DotrViewMatrix {
    float unknown_values[16];
};
struct DotrViewEntry {
    struct DotrViewMatrix unknown_000;
    struct DotrViewMatrix unknown_040;
    struct DotrViewMatrix unknown_080;
    struct DotrViewBlock unknown_0c0;
    float unknown_150;
    float unknown_154;
    float unknown_158;
    float unknown_15c;
    float unknown_160;
    float unknown_164;
    float unknown_168;
    float unknown_16c;
    float unknown_170;
    float unknown_174;
    float unknown_178;
    float unknown_17c;
    float unknown_180;
    struct DotrViewQuad unknown_184;
    unsigned char unknown_188[0x18];
};
typedef char DotrViewEntryMustBe1a0[(sizeof(struct DotrViewEntry) == 0x1a0) ? 1 : -1];
extern struct DotrViewEntry D_0032A2A0_20ede0[];
extern int D_0032A240_b[];
extern struct DotrViewVector pntDst;
#define DOTR_VIEW_SIDE(x, n, cross, outside) \
    { \
        float d = (x); \
        float q = d * d / (n); \
        if (d < 0.0f) { \
            if (q >= rr) { \
                return outside; \
            } \
            cross; \
        } else if (q <= rr) { \
            cross; \
        } \
    }

/* Whether a sphere at `centre` of `radius` is (partly) inside the view. */
int RhView_CheckViewVolume(void *centre_v, float radius)
{
    struct DotrViewVector * centre = centre_v;
    float sx;
    float rr;
    float z;
    float sy;
    float nn;
    int flags;
    float ny;
    float h;
    struct DotrViewEntry *e;
    float dist;
    float nx;
    float hy;
    float hx;

    flags = 0;
    e = &D_0032A2A0_20ede0[D_0032A240_b[0]];
    centre->unknown_w = 1.0f;
    RhGeom_MulMatrixVector(&pntDst, 0, centre);
    z = pntDst.z;
    if (e->unknown_16c > z + radius) {
        return 4;
    }
    if (e->unknown_16c > z - radius) {
        flags = 4;
    }
    if (e->unknown_170 < z - radius) {
        return 4;
    }
    if (e->unknown_170 < z + radius) {
        flags = 4;
    }
    sx = e->unknown_164 * (1.0f / e->unknown_158);
    sy = e->unknown_168 * (1.0f / e->unknown_15c);
    dist = e->unknown_160;
    nn = *(float *)&e->unknown_188[0];
    ny = dist * pntDst.y;
    h = 2046.0f * z;
    rr = radius * radius;
    DOTR_VIEW_SIDE(h - ny, nn, flags = 6, 4)
    DOTR_VIEW_SIDE(h + ny, nn, flags = 6, 4)
    nx = dist * pntDst.x;
    DOTR_VIEW_SIDE(h - nx, nn, flags = 6, 4)
    DOTR_VIEW_SIDE(h + nx, nn, flags = 6, 4)
    nn = *(float *)&e->unknown_188[8];
    hy = z * sy / 2.0f;
    DOTR_VIEW_SIDE(hy - ny, nn, flags |= 2, flags | 2)
    DOTR_VIEW_SIDE(hy + ny, nn, flags |= 2, flags | 2)
    hx = z * sx / 2.0f;
    nn = *(float *)&e->unknown_188[4];
    DOTR_VIEW_SIDE(hx - nx, nn, flags |= 2, flags | 2)
    DOTR_VIEW_SIDE(hx + nx, nn, flags |= 2, flags | 2)
    return flags | 1;
}
#undef DOTR_VIEW_SIDE

/* Relocates the TIM2 file at `address` (its offsets become pointers). */
void RhText_BindAddress(s32 address) {
    u8 *entry;
    s32 i;
    s32 count;

    *(s32 *)((u8 *)address + 0xC) = address;
    count = *(s32 *)((u8 *)address + 0x58);
    entry = (u8 *)address + *(s32 *)((u8 *)address + 0x10);
    for (i = 0; i < count; i += 1) {
        *(s32 *)(entry + 4) = address + *(s32 *)(entry + 4);
        entry += 0x30;
    }
}

/* Adds a texture-cache flush to the packet. */
s32 RhText_SetTextureFlush(s32 cursor) {
    sceVif1PkInit(D_0032A5E0, cursor);
    sceVif1PkCnt(D_0032A5E0, 0);
    sceVif1PkAddCode(D_0032A5E0, 0x11000000);
    sceVif1PkAlign(D_0032A5E0, 2, 3);
    sceVif1PkOpenDirectHLCode(D_0032A5E0, 0);
    *(u64 *)&D_0032A600 = 0x8000 | ((u64)0x10000000 << 32);
    *((u64 *)&D_0032A600 + 1) = 0xE;
    sceVif1PkOpenGifTag(D_0032A5E0, D_0032A600);
    sceVif1PkAddGsAD(D_0032A5E0, 0x3F, 1);
    sceVif1PkCloseGifTag(D_0032A5E0);
    sceVif1PkCloseDirectHLCode(D_0032A5E0);
    return sceVif1PkTerminate(D_0032A5E0);
}

/* Relocates the model file at `model` (its offsets become pointers) and binds its textures. */
s32 RhModel_BindAddress(void *model) {
    s32 *sections;
    s32 i;
    u32 *entries;
    u32 value;
    u32 *target;
    u8 *resolved;

    sections = (s32 *)((u8 *)model + 0x10);
    entries = (u32 *)((u8 *)model + *(s32 *)((u8 *)model + 0x50));
    for (i = 0; entries[i] != 0xFFFFFFFF; i++) {
        value = entries[i];
        switch (value & 0xF0000000) {
        case 0x20000000:
            target = (u32 *)((u8 *)model + sections[2] + (value & 0x0FFFFFFF));
            break;
        case 0x30000000:
            target = (u32 *)((u8 *)model + sections[4] + (value & 0x0FFFFFFF));
            break;
        case 0x40000000:
            target = (u32 *)((u8 *)model + sections[6] + (value & 0x0FFFFFFF));
            break;
        case 0x50000000:
            target = (u32 *)((u8 *)model + sections[8] + (value & 0x0FFFFFFF));
            break;
        default:
            continue;
        }
        value = *target;
        switch (value & 0xF0000000) {
        case 0x20000000:
            resolved = (u8 *)model + sections[2] + (value & 0x0FFFFFFF);
            break;
        case 0x30000000:
            resolved = (u8 *)model + sections[4] + (value & 0x0FFFFFFF);
            break;
        case 0x40000000:
            resolved = (u8 *)model + sections[6] + (value & 0x0FFFFFFF);
            break;
        case 0x50000000:
            resolved = (u8 *)model + sections[8] + (value & 0x0FFFFFFF);
            break;
        default:
            continue;
        }
        *target = (u32)resolved;
    }
    return 1;
}

typedef struct Flags_0020F4E0 {
    u8 bit0 : 1;
    u8 bit1 : 1;
    u8 bit2 : 1;
    u8 bit3 : 1;
    u8 bit4 : 1;
    u8 bit5 : 1;
    u8 bit6 : 1;
    u8 bit7 : 1;
} Flags_0020F4E0;

typedef struct Object_0020F4E0 {
    u8 *data;
    Flags_0020F4E0 flags4;
    Flags_0020F4E0 flags5;
    u8 pad6[0x26];
    s32 result;
} Object_0020F4E0;

typedef struct Offset_0020F4E0 {
    s32 unused;
    u32 value : 28;
    u32 flags : 4;
} Offset_0020F4E0;

typedef struct Transform_0020F4E0 {
    u8 pad0[0x30];
    union {
        __int128 quad;
        struct {
            f32 x, y, z, w;
        } values;
    } vector;
} Transform_0020F4E0;

extern s32 require_coordinate_index;

/* Draws model `model` with transform `transform` through VU1. */
void *RhModel_Draw(void *packet, void *model) {
    extern s32 RhView_GetSampleZ(void *, f32);
    s32 temp_v1;
    Transform_0020F4E0 *transform;
    s32 var_s1;
    Object_0020F4E0 *obj;

    obj = model;
    if (!obj->flags4.bit1 || !obj->flags5.bit2) {
        packet = RhVu1Mac_SetFogOnOff(packet, (u8)obj->flags4.bit1, obj->flags5.bit2);
    }
    *(void **)0x700000C0 = packet;
    *(u8 **)0x700000DC = obj->data + 0x10;
    *(s32 *)0x700000D8 = ((Offset_0020F4E0 *)(obj->data + *(s32 *)(*(u8 **)0x700000DC + 8)))->value;
    RhGeom_PushMatrix(0);
    transform = (Transform_0020F4E0 *)(obj->data + *(s32 *)*(u8 **)0x700000DC);
    *(__int128 *)0x70000020 = transform->vector.quad;
    *(s32 *)0x7000002C = 0x3F800000;
    if (obj->flags5.bit4 != 0) {
        RhMem_CopyMemory16((void *)0x70000000, (u8 *)model + 0x50, 1);
    } else {
        RhGeom_MulMatrixVector((void *)0x70000000, NULL, (void *)0x70000020);
    }
    obj->result = RhView_GetSampleZ((void *)0x70000000, transform->vector.values.w);
    var_s1 = 0;
    if (obj->flags4.bit0 && (RhVu1Mac_GetPointLight(NULL, (void *)0x70000050, (f32 *)0x70000030, (f32 *)0x70000034, (f32 *)0x70000038) != 0) && (RhGeom_GetPointsDistance((f32 *)0x70000050, (f32 *)0x70000000) <= (*(f32 *)0x70000034 + transform->vector.values.w))) {
        var_s1 = 1;
    }
    require_coordinate_index = 0;
    if (obj->flags4.bit2 != 0) {
        packet = lRhModel_DrawNormalMethod(model, var_s1);
    } else {
        *(s32 *)0x700000B0 = RhView_CheckViewVolume((void *)0x70000020, transform->vector.values.w);
        temp_v1 = *(s32 *)0x700000B0;
        if (temp_v1 & 1) {
            if ((temp_v1 & 4) || (*(s32 *)(*(u8 **)0x700000DC + 0x1C) > 0) || (var_s1 != 0)) {
                packet = lRhModel_DrawNormalMethod(model, var_s1);
            } else {
                packet = lRhModel_DrawFastMethod(model);
            }
        }
    }
    RhGeom_PopMatrix();
    if ((obj->flags4.bit1 == 0) || (obj->flags5.bit2 == 0)) {
        packet = RhVu1Mac_SetFogOnOff(packet, 1, 1);
    }
    return packet;
}

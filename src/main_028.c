#include "common.h"

/* `v0` = fixed-point `v1` (4 fraction bits) as floats. */
void sceVu0ITOF4Vector(void *v0, void *v1) {
    __asm__ __volatile__("\n\
	lqc2	$vf4,0x0(%1)\n\
	vitof4.xyzw	$vf5,$vf4\n\
	sqc2	$vf5,0x0(%0)\n\
	" :  : "r" (v0), "r" (v1));
}

/* `v0` = integer `v1` as floats. */
void sceVu0ITOF0Vector(void *v0, void *v1) {
    __asm__ __volatile__("\n\
	lqc2	$vf4,0x0(%1)\n\
	vitof0.xyzw	$vf5,$vf4\n\
	sqc2	$vf5,0x0(%0)\n\
	" :  : "r" (v0), "r" (v1));
}

/* `m0` = the identity matrix. */
void sceVu0UnitMatrix(void *m0) {
    __asm__ __volatile__("\n\
	vsub.xyzw	$vf4,$vf0,$vf0\n\
	vadd.w	$vf4,$vf4,$vf0\n\
	vmr32.xyzw	$vf5,$vf4\n\
	vmr32.xyzw	$vf6,$vf5\n\
	vmr32.xyzw	$vf7,$vf6\n\
	sqc2	$vf4,0x30(%0)\n\
	sqc2	$vf5,0x20(%0)\n\
	sqc2	$vf6,0x10(%0)\n\
	sqc2	$vf7,0x0(%0)\n\
	" :  : "r" (m0));
}

/* Cosine and sine of an angle (VU0 series). */
void _sceVu0ecossin(void *p0, void *p1, void *p2, void *p3) {
    __asm__ __volatile__("\n\
	lui	$8,%%hi(D_0028D9E0)\n\
	addiu	$8,$8,%%lo(D_0028D9E0)\n\
	lqc2	$vf5,0x0($8)\n\
	vmr32.w	$vf6,$vf6\n\
	vaddx.x	$vf4,$vf0,$vf6x\n\
	vmul.x	$vf6,$vf6,$vf6\n\
	vmulx.yzw	$vf4,$vf4,$vf0x\n\
	vmulw.xyzw	$vf8,$vf5,$vf6w\n\
	vsub.xyzw	$vf5,$vf0,$vf0\n\
	vmulx.xyzw	$vf8,$vf8,$vf6x\n\
	vmulx.xyz	$vf8,$vf8,$vf6x\n\
	vaddw.x	$vf4,$vf4,$vf8w\n\
	vmulx.xy	$vf8,$vf8,$vf6x\n\
	vaddz.x	$vf4,$vf4,$vf8z\n\
	vmulx.x	$vf8,$vf8,$vf6x\n\
	vaddy.x	$vf4,$vf4,$vf8y\n\
	vaddx.x	$vf4,$vf4,$vf8x\n\
	vaddx.xy	$vf4,$vf5,$vf4x\n\
	vmul.x	$vf7,$vf4,$vf4\n\
	vsubx.w	$vf7,$vf0,$vf7x\n\
	.word 0x4B8703BD\n\
	vwaitq\n\
	vaddq.x	$vf7,$vf0,$Q\n\
	bnez	%3,_func_00187C30_00187C98\n\
	vaddx.x	$vf4,$vf5,$vf7x\n\
	b	_func_00187C30_00187C9C\n\
_func_00187C30_00187C98:\n\
	vsubx.x	$vf4,$vf5,$vf7x\n\
_func_00187C30_00187C9C:\n\
	" :  : "r" (p0), "r" (p1), "r" (p2), "r" (p3));
}

/* `m0` = `m1` turned by `f0` round Z. */
void sceVu0RotMatrixZ(void *m0, void *m1, float f0) {
    __asm__ __volatile__("\n\
	.set noat\n\
	.set noreorder\n\
	mtc1	$0,$f0\n\
	c.lt.s	%2,$f0\n\
	.set reorder\n\
	lui	$1,(0x3FC90FDB >> 16)\n\
	ori	$1,$1,(0x3FC90FDB & 0xFFFF)\n\
	.set noreorder\n\
	mtc1	$1,$f0\n\
	.set reorder\n\
	bc1f	_func_00187CA8_00187CD0\n\
	add.s	%2,$f0,%2\n\
	addiu	$7,$0,0x1\n\
	j	_func_00187CA8_00187CD8\n\
_func_00187CA8_00187CD0:\n\
	sub.s	%2,$f0,%2\n\
	daddu	$7,$0,$0\n\
_func_00187CA8_00187CD8:\n\
	.set noreorder\n\
	mfc1	$8,%2\n\
	qmtc2.ni	$8,$vf6\n\
	.set reorder\n\
	daddu	$6,$31,$0\n\
	jal	_sceVu0ecossin\n\
	daddu	$31,$6,$0\n\
	vmove.xyzw	$vf6,$vf5\n\
	vmove.xyzw	$vf7,$vf5\n\
	vmove.xyzw	$vf9,$vf0\n\
	vsub.xyz	$vf9,$vf9,$vf9\n\
	vmr32.xyzw	$vf8,$vf9\n\
	vsub.zw	$vf4,$vf4,$vf4\n\
	vaddx.y	$vf6,$vf5,$vf4x\n\
	vaddy.x	$vf6,$vf5,$vf4y\n\
	vsubx.x	$vf7,$vf5,$vf4x\n\
	vaddy.y	$vf7,$vf5,$vf4y\n\
	addiu	$7,$0,0x4\n\
_func_00187CA8_00187D1C:\n\
	lqc2	$vf4,0x0(%1)\n\
	vmulax.xyzw	$ACC,$vf6,$vf4x\n\
	vmadday.xyzw	$ACC,$vf7,$vf4y\n\
	vmaddaz.xyzw	$ACC,$vf8,$vf4z\n\
	vmaddw.xyzw	$vf5,$vf9,$vf4w\n\
	sqc2	$vf5,0x0(%0)\n\
	addi	$7,$7,-0x1\n\
	addi	%1,%1,0x10\n\
	addi	%0,%0,0x10\n\
	bne	$0,$7,_func_00187CA8_00187D1C\n\
	.set at\n\
	" :  : "r" (m0), "r" (m1), "f" (f0));
}

/* `m0` = `m1` turned by `f0` round X. */
void sceVu0RotMatrixX(void *m0, void *m1, float f0) {
    __asm__ __volatile__("\n\
	.set noat\n\
	.set noreorder\n\
	mtc1	$0,$f0\n\
	c.lt.s	%2,$f0\n\
	.set reorder\n\
	lui	$1,(0x3FC90FDB >> 16)\n\
	ori	$1,$1,(0x3FC90FDB & 0xFFFF)\n\
	.set noreorder\n\
	mtc1	$1,$f0\n\
	.set reorder\n\
	bc1f	_func_00187D50_00187D78\n\
	add.s	%2,$f0,%2\n\
	addiu	$7,$0,0x1\n\
	j	_func_00187D50_00187D80\n\
_func_00187D50_00187D78:\n\
	sub.s	%2,$f0,%2\n\
	daddu	$7,$0,$0\n\
_func_00187D50_00187D80:\n\
	.set noreorder\n\
	mfc1	$8,%2\n\
	qmtc2.ni	$8,$vf6\n\
	.set reorder\n\
	daddu	$6,$31,$0\n\
	jal	_sceVu0ecossin\n\
	daddu	$31,$6,$0\n\
	vmove.xyzw	$vf6,$vf5\n\
	vmove.xyzw	$vf7,$vf5\n\
	vmove.xyzw	$vf8,$vf5\n\
	vmove.xyzw	$vf9,$vf5\n\
	vaddw.x	$vf6,$vf5,$vf0w\n\
	vaddw.w	$vf9,$vf5,$vf0w\n\
	vsub.zw	$vf4,$vf4,$vf4\n\
	vaddx.z	$vf7,$vf5,$vf4x\n\
	vaddy.y	$vf7,$vf5,$vf4y\n\
	vsubx.y	$vf8,$vf5,$vf4x\n\
	vaddy.z	$vf8,$vf5,$vf4y\n\
	addiu	$7,$0,0x4\n\
_func_00187D50_00187DC8:\n\
	lqc2	$vf4,0x0(%1)\n\
	vmulax.xyzw	$ACC,$vf6,$vf4x\n\
	vmadday.xyzw	$ACC,$vf7,$vf4y\n\
	vmaddaz.xyzw	$ACC,$vf8,$vf4z\n\
	vmaddw.xyzw	$vf5,$vf9,$vf4w\n\
	sqc2	$vf5,0x0(%0)\n\
	addi	$7,$7,-0x1\n\
	addi	%1,%1,0x10\n\
	addi	%0,%0,0x10\n\
	bne	$0,$7,_func_00187D50_00187DC8\n\
	.set at\n\
	" :  : "r" (m0), "r" (m1), "f" (f0));
}

/* `m0` = `m1` turned by `f0` round Y. */
void sceVu0RotMatrixY(void *m0, void *m1, float f0) {
    __asm__ __volatile__("\n\
	.set noat\n\
	.set noreorder\n\
	mtc1	$0,$f0\n\
	c.lt.s	%2,$f0\n\
	.set reorder\n\
	lui	$1,(0x3FC90FDB >> 16)\n\
	ori	$1,$1,(0x3FC90FDB & 0xFFFF)\n\
	.set noreorder\n\
	mtc1	$1,$f0\n\
	.set reorder\n\
	bc1f	_func_00187DF8_00187E20\n\
	add.s	%2,$f0,%2\n\
	addiu	$7,$0,0x1\n\
	j	_func_00187DF8_00187E28\n\
_func_00187DF8_00187E20:\n\
	sub.s	%2,$f0,%2\n\
	daddu	$7,$0,$0\n\
_func_00187DF8_00187E28:\n\
	.set noreorder\n\
	mfc1	$8,%2\n\
	qmtc2.ni	$8,$vf6\n\
	.set reorder\n\
	daddu	$6,$31,$0\n\
	jal	_sceVu0ecossin\n\
	daddu	$31,$6,$0\n\
	vmove.xyzw	$vf6,$vf5\n\
	vmove.xyzw	$vf7,$vf5\n\
	vmove.xyzw	$vf8,$vf5\n\
	vmove.xyzw	$vf9,$vf5\n\
	vaddw.y	$vf7,$vf5,$vf0w\n\
	vaddw.w	$vf9,$vf5,$vf0w\n\
	vsub.zw	$vf4,$vf4,$vf4\n\
	vsubx.z	$vf6,$vf5,$vf4x\n\
	vaddy.x	$vf6,$vf5,$vf4y\n\
	vaddx.x	$vf8,$vf5,$vf4x\n\
	vaddy.z	$vf8,$vf5,$vf4y\n\
	addiu	$7,$0,0x4\n\
_func_00187DF8_00187E70:\n\
	lqc2	$vf4,0x0(%1)\n\
	vmulax.xyzw	$ACC,$vf6,$vf4x\n\
	vmadday.xyzw	$ACC,$vf7,$vf4y\n\
	vmaddaz.xyzw	$ACC,$vf8,$vf4z\n\
	vmaddw.xyzw	$vf5,$vf9,$vf4w\n\
	sqc2	$vf5,0x0(%0)\n\
	addi	$7,$7,-0x1\n\
	addi	%1,%1,0x10\n\
	addi	%0,%0,0x10\n\
	bne	$0,$7,_func_00187DF8_00187E70\n\
	.set at\n\
	" :  : "r" (m0), "r" (m1), "f" (f0));
}

/* `m0` = `m1` turned by the angles in `rot` (Z, then Y, then X). */
void sceVu0RotMatrix(s32 m0, s32 m1, void *rot) {
    sceVu0RotMatrixZ(m0, m1, (*(f32 *)((u8 *)rot + 8)));
    sceVu0RotMatrixY(m0, m0, (*(f32 *)((u8 *)rot + 4)));
    sceVu0RotMatrixX(m0, m0, (*(f32 *)rot));
}

/* `v0` = `v1` kept between `f0` and `f1`. */
void sceVu0ClampVector(void *v0, void *v1, float f0, float f1) {
    __asm__ __volatile__("\n\
	mfc1	$8,%2\n\
	mfc1	$9,%3\n\
	lqc2	$vf6,0x0(%1)\n\
	qmtc2.ni	$8,$vf4\n\
	qmtc2.ni	$9,$vf5\n\
	vmaxx.xyzw	$vf6,$vf6,$vf4x\n\
	vminix.xyzw	$vf6,$vf6,$vf5x\n\
	sqc2	$vf6,0x0(%0)\n\
	" :  : "r" (v0), "r" (v1), "f" (f0), "f" (f1));
}

/* `m` = the camera matrix for position `p`, look direction `zd` and up `yd`. */
void sceVu0CameraMatrix(s32 m, s32 p, s32 *zd, s32 *yd) {
    s32 sp0[4];
    s32 sp10[4];
    s32 sp20[8];
    s32 sp40[4];

    sceVu0UnitMatrix(sp0);
    sceVu0OuterProduct(sp40, yd, zd);
    sceVu0Normalize(sp0, sp40);
    sceVu0Normalize(sp20, zd);
    sceVu0OuterProduct(sp10, sp20, sp0);
    sceVu0TransMatrix(sp0, sp0, p);
    sceVu0InversMatrix(m, sp0);
}

/* `m` = the matrix of three light directions `l0`, `l1`, `l2`. */
void sceVu0NormalLightMatrix(f32 (*m)[4], f32 *l0, f32 *l1, f32 *l2) {
    f32 v[4];

    sceVu0ScaleVector(v, l0, -1.0f);
    sceVu0Normalize(m[0], v);
    sceVu0ScaleVector(v, l1, -1.0f);
    sceVu0Normalize(m[1], v);
    sceVu0ScaleVector(v, l2, -1.0f);
    sceVu0Normalize(m[2], v);
    m[3][0] = m[3][1] = m[3][2] = 0.0f;
    m[3][3] = 1.0f;
    sceVu0TransposeMatrix(m, m);
}

/* `m` = the matrix of three light colours `c0`, `c1`, `c2` and ambient `a`. */
void sceVu0LightColorMatrix(s32 m, s32 c0, s32 c1, s32 c2, s32 a) {
    sceVu0CopyVector(m, c0);
    sceVu0CopyVector(m + 0x10, c1);
    sceVu0CopyVector(m + 0x20, c2);
    sceVu0CopyVector(m + 0x30, a);
}

/* `m` = the perspective matrix (screen distance, aspect, centre, depth range). */
void sceVu0ViewScreenMatrix(f32 (*m)[4], f32 scrz, f32 ax, f32 ay, f32 cx, f32 cy, f32 zmin, f32 zmax, f32 nearz, f32 farz) {
    f32 az, cz;
    f32 mt[4][4];

    cz = (-zmax * nearz + zmin * farz) / (-nearz + farz);
    az = farz * nearz * (-zmin + zmax) / (-nearz + farz);

    sceVu0UnitMatrix(m);
    m[0][0] = scrz;
    m[1][1] = scrz;
    m[2][2] = 0.0f;
    m[3][2] = 1.0f;
    m[2][3] = 1.0f;
    m[3][3] = 0.0f;

    sceVu0UnitMatrix(mt);
    mt[0][0] = ax;
    mt[1][1] = ay;
    mt[2][2] = az;
    mt[3][0] = cx;
    mt[3][1] = cy;
    mt[3][2] = cz;

    sceVu0MulMatrix(m, mt, m);
}

/* `m` = the matrix that flattens onto a plane from light `lp` (`mode`: point or parallel). */
void sceVu0DropShadowMatrix(f32 (*m)[4], f32 *lp, f32 a, f32 b, f32 c, s32 mode) {



    if (mode) {
        f32 x, y, z, d;

        x = lp[0];
        y = lp[1];
        z = lp[2];
        d = 1.0f - (a * x + b * y + c * z);
        m[0][0] = a * x + d;
        m[1][0] = b * x;
        m[2][0] = c * x;
        m[3][0] = -x;
        m[0][1] = a * y;
        m[1][1] = b * y + d;
        m[2][1] = c * y;
        m[3][1] = -y;
        m[0][2] = a * z;
        m[1][2] = b * z;
        m[2][2] = c * z + d;
        m[3][2] = -z;
        m[0][3] = a;
        m[1][3] = b;
        m[2][3] = c;
        m[3][3] = d - 1.0f;
    } else {
        f32 x, y, z, d, e;

        x = lp[0];
        y = lp[1];
        z = lp[2];
        d = a * x + b * y + c * z;
        e = -1.0f / d;
        m[0][0] = e * (a * x - d);
        m[1][0] = e * (b * x);
        m[2][0] = e * (c * x);
        m[3][0] = e * (-x);
        m[0][1] = e * (a * y);
        m[1][1] = e * (b * y - d);
        m[2][1] = e * (c * y);
        m[3][1] = e * (-y);
        m[0][2] = e * (a * z);
        m[1][2] = e * (b * z);
        m[2][2] = e * (c * z - d);
        m[3][2] = e * (-z);
        m[0][3] = 0.0f;
        m[1][3] = 0.0f;
        m[2][3] = 0.0f;
        m[3][3] = e * (-d);
    }
}

/* Transforms and projects `nIn` vertices `v1` into `v0` (matrix `m0`). */
void sceVu0RotTransPersN(void *v0, void *m0, void *v1, void *nIn) {
    __asm__ __volatile__("\n\
	lqc2	$vf4,0x0(%1)\n\
	lqc2	$vf5,0x10(%1)\n\
	lqc2	$vf6,0x20(%1)\n\
	lqc2	$vf7,0x30(%1)\n\
_func_00188388_00188398:\n\
	lqc2	$vf8,0x0(%2)\n\
	vmulax.xyzw	$ACC,$vf4,$vf8x\n\
	vmadday.xyzw	$ACC,$vf5,$vf8y\n\
	vmaddaz.xyzw	$ACC,$vf6,$vf8z\n\
	vmaddw.xyzw	$vf9,$vf7,$vf8w\n\
	vdiv	$Q,$vf0w,$vf9w\n\
	vwaitq\n\
	vmulq.xyz	$vf9,$vf9,$Q\n\
	vftoi4.xyzw	$vf10,$vf9\n\
	beqz	$8,_func_00188388_001883C4\n\
	vftoi0.zw	$vf10,$vf9\n\
_func_00188388_001883C4:\n\
	sqc2	$vf10,0x0(%0)\n\
	addi	%3,%3,-0x1\n\
	addi	%2,%2,0x10\n\
	addi	%0,%0,0x10\n\
	bne	$0,%3,_func_00188388_00188398\n\
	" :  : "r" (v0), "r" (m0), "r" (v1), "r" (nIn));
}

/* Transforms and projects vertex `v1` into `v0` (matrix `m0`, `mode`). */
void sceVu0RotTransPers(void *v0, void *m0, void *v1, void *mode) {
    __asm__ __volatile__("\n\
	lqc2	$vf4,0x0(%1)\n\
	lqc2	$vf5,0x10(%1)\n\
	lqc2	$vf6,0x20(%1)\n\
	lqc2	$vf7,0x30(%1)\n\
	lqc2	$vf8,0x0(%2)\n\
	vmulax.xyzw	$ACC,$vf4,$vf8x\n\
	vmadday.xyzw	$ACC,$vf5,$vf8y\n\
	vmaddaz.xyzw	$ACC,$vf6,$vf8z\n\
	vmaddw.xyzw	$vf9,$vf7,$vf8w\n\
	vdiv	$Q,$vf0w,$vf9w\n\
	vwaitq\n\
	vmulq.xyz	$vf9,$vf9,$Q\n\
	vftoi4.xyzw	$vf10,$vf9\n\
	beqz	%3,_func_001883E0_0018841C\n\
	vftoi0.zw	$vf10,$vf9\n\
_func_001883E0_0018841C:\n\
	sqc2	$vf10,0x0(%0)\n\
	" :  : "r" (v0), "r" (m0), "r" (v1), "r" (mode));
}

/* `v0` x, y, z = `v1`'s. */
void sceVu0CopyVectorXYZ(f32 *v0, f32 *v1) {
    v0[0] = v1[0];
    v0[1] = v1[1];
    v0[2] = v1[2];
}

/* `v0` x, y, z = `v1` and `v2` mixed by `f0`. */
void sceVu0InterVectorXYZ(void *v0, void *v1, void *v2, float f0) {
    __asm__ __volatile__("\n\
	lqc2	$vf4,0x0(%1)\n\
	lqc2	$vf5,0x0(%2)\n\
	.set noreorder\n\
	mfc1	$8,%3\n\
	qmtc2.ni	$8,$vf6\n\
	.set reorder\n\
	vmove.w	$vf9,$vf4\n\
	vaddw.x	$vf7,$vf0,$vf0w\n\
	vsub.x	$vf8,$vf7,$vf6\n\
	vmulax.xyz	$ACC,$vf4,$vf6x\n\
	vmaddx.xyz	$vf9,$vf5,$vf8x\n\
	sqc2	$vf9,0x0(%0)\n\
	" :  : "r" (v0), "r" (v1), "r" (v2), "f" (f0));
}

/* `v0` x, y, z = `v1`'s times `f0`. */
void sceVu0ScaleVectorXYZ(void *v0, void *v1, float f0) {
    __asm__ __volatile__("\n\
	lqc2	$vf4,0x0(%1)\n\
	.set noreorder\n\
	mfc1	$8,%2\n\
	qmtc2.ni	$8,$vf5\n\
	.set reorder\n\
	vmulx.xyz	$vf4,$vf4,$vf5x\n\
	sqc2	$vf4,0x0(%0)\n\
	" :  : "r" (v0), "r" (v1), "f" (f0));
}

/* Whether vertex `v0In` is off screen. */
int sceVu0ClipScreen(void *v0In) {
    register int ret __asm__("$2");
    __asm__ __volatile__("\n\
	vsub.xyzw	$vf4,$vf0,$vf0\n\
	lui	%0,(0x45800000 >> 16)\n\
	dsll	%0,%0,16\n\
	ori	%0,%0,0x4580\n\
	dsll	%0,%0,16\n\
	lqc2	$vf7,0x0(%1)\n\
	qmtc2.ni	%0,$vf6\n\
	.word 0x48C08000 # ctc2.ni $zero, $vi16\n\
	vsub.xyw	$vf5,$vf7,$vf4\n\
	vsub.xy	$vf5,$vf6,$vf7\n\
	vnop\n\
	vnop\n\
	vnop\n\
	vnop\n\
	vnop\n\
	.word 0x48428000 # cfc2.ni $v0, $vi16\n\
	andi	%0,%0,0xC0\n\
	" : "=r" (ret) : "r" (v0In));
    return ret;
}

/* Whether triangle `v0In`, `v1`, `v2` is entirely off screen. */
int sceVu0ClipScreen3(void *v0In, void *v1, void *v2) {
    register int ret __asm__("$2");
    __asm__ __volatile__("\n\
	vsub.xyzw	$vf4,$vf0,$vf0\n\
	lui	%0,(0x45800000 >> 16)\n\
	dsll	%0,%0,16\n\
	ori	%0,%0,0x4580\n\
	dsll	%0,%0,16\n\
	lqc2	$vf6,0x0(%1)\n\
	lqc2	$vf8,0x0(%2)\n\
	lqc2	$vf9,0x0(%3)\n\
	qmtc2.ni	%0,$vf7\n\
	.word 0x48C08000 # ctc2.ni $zero, $vi16\n\
	vsub.xyw	$vf5,$vf6,$vf4\n\
	vsub.xy	$vf5,$vf7,$vf6\n\
	vsub.xyw	$vf5,$vf8,$vf4\n\
	vsub.xy	$vf5,$vf7,$vf8\n\
	vsub.xyw	$vf5,$vf9,$vf4\n\
	vsub.xy	$vf5,$vf7,$vf9\n\
	vnop\n\
	vnop\n\
	vnop\n\
	vnop\n\
	vnop\n\
	.word 0x48428000 # cfc2.ni $v0, $vi16\n\
	andi	%0,%0,0xC0\n\
	" : "=r" (ret) : "r" (v0In), "r" (v1), "r" (v2));
    return ret;
}

/* Clip flags of the triangle at `v0In` against the box `minv`..`maxv` (matrix `ms`). */
int sceVu0ClipAll(void *minv, void *maxv, void *ms, void *v0In) {
    register int ret __asm__("$2");
    __asm__ __volatile__("\n\
	lqc2	$vf8,0x0(%4)\n\
	lqc2	$vf4,0x0(%3)\n\
	lqc2	$vf5,0x10(%3)\n\
	lqc2	$vf6,0x20(%3)\n\
	lqc2	$vf7,0x30(%3)\n\
	lqc2	$vf9,0x0(%1)\n\
	lqc2	$vf10,0x0(%2)\n\
	lqc2	$vf11,0x0(%1)\n\
	lqc2	$vf12,0x0(%2)\n\
_func_00188538_0018855C:\n\
	vmulax.xyzw	$ACC,$vf4,$vf8x\n\
	vmadday.xyzw	$ACC,$vf5,$vf8y\n\
	vmaddaz.xyzw	$ACC,$vf6,$vf8z\n\
	vmaddw.xyzw	$vf8,$vf7,$vf8w\n\
	vmulw.xyz	$vf11,$vf9,$vf8w\n\
	vmulw.xyz	$vf12,$vf10,$vf8w\n\
	vnop\n\
	vnop\n\
	.word 0x48C08000 # ctc2.ni $zero, $vi16\n\
	vsub.xyw	$vf11,$vf8,$vf11\n\
	vsub.xyw	$vf12,$vf12,$vf8\n\
	vmove.w	$vf11,$vf9\n\
	vmove.w	$vf12,$vf10\n\
	vnop\n\
	addi	%4,%4,0x10\n\
	lqc2	$vf8,0x0(%4)\n\
	addi	$8,$8,-0x1\n\
	.word 0x48428000 # cfc2.ni $v0, $vi16\n\
	andi	%0,%0,0xC0\n\
	beqz	%0,_func_00188538_001885BC\n\
	bne	$0,$8,_func_00188538_0018855C\n\
	addi	%0,$0,0x1\n\
_func_00188538_001885BC:\n\
	" : "=r" (ret) : "r" (minv), "r" (maxv), "r" (ms), "r" (v0In));
    return ret;
}

/* Resets the IPU and the MPEG decoder state. */
void sceVpu0Reset(void) {
    *(volatile int *)0x10003830 = 0;
    *(volatile int *)0x10003820 = 0;
    *(volatile int *)0x10003810 = 1;
    __asm__ __volatile__("\n\
	.set push\n\
	.set noreorder\n\
	cfc2	$8,$vi28\n\
	ori	$8,$8,0x2\n\
	.set pop\n\
	ctc2	$8,$vi28\n\
	sync.p\n\
	" : : : "$8");
    *(volatile __int128 *)0x10004000 = D_0028D9F0[0];
    *(volatile __int128 *)0x10004000 = D_0028D9F0[1];
}

__asm__(".space 12");

/* libmpeg: one macroblock's prediction setup (mpeg2decode-style): position from MBA, intra or
   form_predictions (func_00188880), then the IPU buffer record's flags and reference pointer */

typedef struct MpegRef_00188630 {
    s32 base;
    s32 unk4[3];
    s32 width;
} MpegRef_00188630;

typedef struct MpegBuf_00188630 {
    u8 unk0[0x128];
    s32 p;
    s32 n;
    s32 intra;
    s32 skipped;
    s32 predicted;
    s32 f13C;
} MpegBuf_00188630;

typedef struct MpegDec_00188630 {
    u8 unk0[0x11C];
    s32 error;
    u8 unk120[0xC];
    s32 mb_width;
    u8 unk130[0x44];
    s32 picture_structure;
    u8 unk178[0x48];
    MpegRef_00188630 *cur;
    u8 unk1C4[0xC];
    MpegRef_00188630 *cur_top;
    u8 unk1D4[0xC];
    MpegRef_00188630 *cur_bot;
    u8 unk1E4[0x3AC];
    MpegBuf_00188630 bufs[2];
    s32 idx;
} MpegDec_00188630;

extern char D_002BC6A8[];
extern void func_00188880(void *d, s32 bx, s32 by, s32 mb_type, s32 motion_type, s32 *pmv, s32 *mvfs,
                          s32 *dmvector);

#define IPU_BUSY_00188630() ((*(volatile u32 *)0x1000D400 >> 8) & 1)

/* Starts decoding one macroblock: motion prediction from the reference pictures, then the IPU decode. */
s32 func_00188630(void *arg0, s32 MBA, s32 MBAinc, s32 mb_type, s32 motion_type, void *pmv, s32 *mvfs,
                  s32 *dmvector) {
    MpegDec_00188630 *d = arg0;
    s32 intra;
    s32 mbx, mby;
    s32 bx;
    MpegDec_00188630 *dec;
    s32 by;
    MpegRef_00188630 *ref;
    s32 *predicted, *skipped, *intra_p, *p;
    s32 zero;

    intra = mb_type & 1;
    mbx = MBA % d->mb_width;
    dec = d;
    mby = MBA / d->mb_width;
    bx = mbx * 16;
    by = mby * 16;
    if (intra) {
        predicted = &d->bufs[0].predicted;
        skipped = &d->bufs[0].skipped;
        intra_p = &d->bufs[0].intra;
        p = &d->bufs[0].p;
    wait:
        if (IPU_BUSY_00188630()) {
            goto wait;
        }
        predicted[d->idx * 80] = 0;
    } else {
        if ((u32)(motion_type - 1) >= 3) {
            func_0018F778((s32)d, D_002BC6A8, motion_type);
            d->error = 1;
            return 0;
        }
        func_00188880(d, bx, by, mb_type, motion_type, pmv, mvfs, dmvector);
        do {
            zero = 0;
            predicted = &dec->bufs[zero].predicted;
            skipped = &dec->bufs[zero].skipped;
            intra_p = &dec->bufs[zero].intra;
            p = &dec->bufs[zero].p;
            while (IPU_BUSY_00188630()) {
            }
            func_0018D0C8(dec);
            predicted[dec->idx * 80] = 1;
        } while (0);
    }
    if (MBAinc == 1 && (mb_type & 2)) {
        skipped[d->idx * 80] = MBAinc;
    } else {
        /* the original's own bug: zero is never set on the intra path (GCC folds it to $zero) */
        skipped[d->idx * 80] = zero;
    }
    intra_p[d->idx * 80] = intra;
    if (d->picture_structure == 3) {
        p[d->idx * 80] = d->cur->base + (mbx * d->cur->width + mby) * 0x180;
    } else {
        ref = d->picture_structure == 2 ? d->cur_bot : d->cur_top;
        p[d->idx * 80] = ref->base + (mbx * ref->width + mby) * 0x180;
    }
    return 1;
}

#undef IPU_BUSY_00188630

/* libmpeg form_predictions (mpeg2decode recon.c, Sony's IPU version) */

typedef struct MpegDec_00188880 {
    u8 unk0[0x120];
    s32 second_field;
    u8 unk124[0x2C];
    s32 picture_coding_type;
    u8 unk154[0x20];
    s32 picture_structure;
    u8 unk178[0x40];
    s32 fwd;
    s32 bwd;
    s32 unk1C0[2];
    s32 fwd_top;
    s32 bwd_top;
    s32 unk1D0[2];
    s32 fwd_bot;
    s32 bwd_bot;
    u8 unk1E0[0x4DC];
    s32 n;
    u8 unk6C0[0x150];
    s32 cur;
} MpegDec_00188880;

extern char D_002BC6D0[];
extern char D_002BC6F0[];
extern char D_002BC710[];
extern void _getRef0(void *d, s32 ref, s32 sfield, s32 dfield, s32 yoff, s32 h, s32 bx, s32 by,
                          s32 dx, s32 dy, s32 fld, s32 avg);

/* Fetches every reference block a macroblock needs. */
void _getAllRefs(void *arg0, s32 bx, s32 by, s32 mb_type, s32 motion_type, s32 PMV[2][2][2],
                   s32 mvfs[2][2], s32 *dmvector) {
    MpegDec_00188880 *d = arg0;
    s32 currentfield;
    s32 DMV[2][2];
    s32 pf[2][2];
    s32 ptype;
    s32 avg;
    s32 one;

    one = 1;
    avg = 0;
    *(s32 *)((u8 *)&d->n + d->cur * 0x140) = 0;
    if ((mb_type & 8) || d->picture_coding_type == 2) {
        if (d->picture_structure == 3) {
            if (motion_type == 2 || !(mb_type & 8)) {
                _getRef0(d, d->fwd, 0, 0, 0, 16, bx, by, PMV[0][0][0], PMV[0][0][1], 0, 0);
            } else if (motion_type == 1) {
                _getRef0(d, d->fwd, mvfs[0][0], 0, 0, 8, bx, by, PMV[0][0][0], PMV[0][0][1] >> 1, one, 0);
                _getRef0(d, d->fwd, mvfs[1][0], 1, 0, 8, bx, by, PMV[1][0][0], PMV[1][0][1] >> 1, one, 0);
            } else if (motion_type == 3) {
                _dualPrimeVector(d, DMV, dmvector, PMV[0][0][0], PMV[0][0][1] >> 1);
                _getRef0(d, d->fwd, 0, 0, 0, 8, bx, by, PMV[0][0][0], PMV[0][0][1] >> 1, one, 0);
                _getRef0(d, d->fwd, 1, 0, 0, 8, bx, by, DMV[0][0], DMV[0][1], one, 1);
                _getRef0(d, d->fwd, 1, 1, 0, 8, bx, by, PMV[0][0][0], PMV[0][0][1] >> 1, one, 0);
                _getRef0(d, d->fwd, 0, 1, 0, 8, bx, by, DMV[1][0], DMV[1][1], one, 1);
            } else {
                _Error1((s32)d, D_002BC6D0, motion_type);
            }
        } else {
            currentfield = d->picture_structure == 2;
            pf[0][0] = d->fwd_top;
            pf[0][1] = d->fwd_bot;
            pf[1][0] = d->bwd_top;
            pf[1][1] = d->bwd_bot;
            ptype = 2;
            one = 0;
            if (d->picture_coding_type == ptype && d->second_field != 0) {
                one = currentfield != mvfs[0][0];
            }
            if (motion_type == 1 || !(mb_type & 8)) {
                _getRef0(d, pf[one][mvfs[0][0]], 0, 0, 0, 16, bx, by, PMV[0][0][0], PMV[0][0][1], 0, 0);
            } else if (motion_type == 2) {
                _getRef0(d, pf[one][mvfs[0][0]], 0, 0, 0, 8, bx, by, PMV[0][0][0], PMV[0][0][1], 0, 0);
                one = d->picture_coding_type == 2 && d->second_field != 0 && currentfield != mvfs[1][0];
                _getRef0(d, pf[one][mvfs[1][0]], 0, 0, 8, 8, bx, by, PMV[1][0][0], PMV[1][0][1], 0, 0);
            } else if (motion_type == 3) {
                if (d->second_field != 0) {
                    one = 1;
                } else {
                    one = 0;
                }
                _dualPrimeVector(d, DMV, dmvector, PMV[0][0][0], PMV[0][0][1]);
                _getRef0(d, pf[0][currentfield], 0, 0, 0, 16, bx, by, PMV[0][0][0], PMV[0][0][1], 0, 0);
                _getRef0(d, pf[one][!currentfield], 0, 0, 0, 16, bx, by, DMV[0][0], DMV[0][1], 0, 1);
            } else {
                _Error1((s32)d, D_002BC6F0, motion_type);
            }
        }
        avg = 1;
    }

    if (mb_type & 4) {
        if (d->picture_structure == 3) {
            one = 1;
            if (motion_type == 2) {
                _getRef0(d, d->bwd, 0, 0, 0, 16, bx, by, PMV[0][1][0], PMV[0][1][1], 0, avg);
            } else {
                _getRef0(d, d->bwd, mvfs[0][1], 0, 0, 8, bx, by, PMV[0][1][0], PMV[0][1][1] >> 1, one, avg);
                _getRef0(d, d->bwd, mvfs[1][1], 1, 0, 8, bx, by, PMV[1][1][0], PMV[1][1][1] >> 1, one, avg);
            }
        } else {
            if (motion_type == 1) {
                _getRef0(d, mvfs[0][1] ? d->bwd_bot : d->bwd_top, 0, 0, 0, 16, bx, by, PMV[0][1][0],
                              PMV[0][1][1], 0, avg);
            } else if (motion_type == 2) {
                _getRef0(d, mvfs[0][1] ? d->bwd_bot : d->bwd_top, 0, 0, 0, 8, bx, by, PMV[0][1][0],
                              PMV[0][1][1], 0, avg);
                _getRef0(d, mvfs[1][1] ? d->bwd_bot : d->bwd_top, 0, 0, 8, 8, bx, by, PMV[1][1][0],
                              PMV[1][1][1], 0, avg);
            } else {
                _Error1((s32)d, D_002BC710, motion_type);
            }
        }
    }
}

/* libmpeg form_prediction (mpeg2decode recon.c, adapted to the IPU sub-records): luma, then chroma reusing
 * xx/yy/xh/yh with halved parameters. The field types are the alias sets the original's schedule shows (int
 * stores keep d->cur reloads, the pointer fields don't); the two cnt pointers keep np first in np + cur*320.
 * chatF, 16 Oct 2026. */

typedef struct MpegSub_00188F88 {
    u8 *dst;
    s32 xr;
    s32 h1;
    s32 h2;
    s32 step;
    void *p0;
    void *p1;
} MpegSub_00188F88;

typedef struct MpegBuf_00188F88 {
    u8 *blk;
    s32 f4;
    void *src1[4];
    void *src2[4];
    void (*fn1[4])();
    void (*fn2[4])();
    MpegSub_00188F88 sub1[4];
    MpegSub_00188F88 sub2[4];
    s32 p;
    s32 n;
    s32 f130;
    s32 unk134;
    s32 f138;
    s32 f13C;
} MpegBuf_00188F88;

typedef struct MpegDec_00188F88 {
    u8 unk0[0x590];
    MpegBuf_00188F88 bufs[2];
    s32 cur;
    s32 unk814[2];
    u8 *out;
} MpegDec_00188F88;

typedef struct MpegRef_00188F88 {
    u8 *base;
    s32 unk4[3];
    s32 width;
} MpegRef_00188F88;

extern void (*D_0028DA10[])();
extern void (*D_0028DA30[])();

/* Fetches one reference block. */
void _getRef0(void *d_v, s32 ref_v, s32 sfield, s32 dfield, s32 yoff, s32 h, s32 bx, s32 by,
                   s32 dx, s32 dy, s32 fld, s32 avg) {
    MpegDec_00188F88 *d = (MpegDec_00188F88 *)d_v;
    MpegRef_00188F88 *ref = (MpegRef_00188F88 *)ref_v;
    s32 n;
    MpegSub_00188F88 *s1;
    MpegSub_00188F88 *s2;
    s32 xx, yy, xb, yb, cxb, cyb, k;
    u8 *blk, *blk2;
    u8 *out;
    s32 h2, o2, dx2, dy2;
    s32 idx1;
    s32 mb;
    s32 xh, yh;
    s32 *np;
    s32 *cnt;
    s32 *cnt2;

    np = &d->bufs[0].n;
    cnt = np + d->cur * 80;
    n = *cnt;
    out = d->out;
    s1 = &d->bufs[d->cur].sub1[n];
    s2 = &d->bufs[d->cur].sub2[n];

    xx = (dx >> 1) + bx;
    if (fld) {
        yy = ((dy >> 1) << 1) + (yoff + sfield) + by;
    } else {
        yy = (dy >> 1) + (yoff + sfield) + by;
    }
    xb = xx >> 4;
    yb = yy >> 4;
    mb = xb * ref->width + yb;
    yy -= yb << 4;
    s1->xr = xx - (xb << 4);
    s1->dst = out + (dfield + yoff) * 32;
    xh = dx & 1;
    yh = dy & 1;
    if (yh) {
        if (yy + (h << fld) < 16) {
            s1->h1 = h;
            s1->h2 = 0;
        } else {
            k = (16 >> fld) - (yy >> fld) - 1;
            s1->h1 = k;
            s1->h2 = h - k;
        }
    } else {
        if (yy + (h << fld) > 16) {
            k = (16 >> fld) - (yy >> fld);
            s1->h1 = k;
            s1->h2 = h - k;
        } else {
            s1->h1 = h;
            s1->h2 = 0;
        }
    }
    blk = d->bufs[d->cur].blk + n * 0x600;
    s1->p0 = blk + yy * 16;
    s1->p1 = blk + (yy * 16 + 0x300);
    s1->step = 16 << fld;
    idx1 = (avg << 2) | (xh << 1) | yh;

    o2 = yoff >> 1;
    h2 = h >> 1;
    dx2 = dx / 2;
    dy2 = dy / 2;
    xx = (dx2 >> 1) + (bx >> 1);
    if (fld) {
        yy = ((dy2 >> 1) << 1) + (o2 + sfield) + (by >> 1);
    } else {
        yy = (dy2 >> 1) + (o2 + sfield) + (by >> 1);
    }
    cxb = xx >> 3;
    cyb = yy >> 3;
    yy -= cyb << 3;
    xh = dx2 & 1;
    yh = dy2 & 1;
    s2->xr = xx - (cxb << 3);
    s2->dst = out + ((dfield + o2) * 16 + 0x200);
    if (yh) {
        if (yy + (h2 << fld) < 8) {
            s2->h1 = h2;
            s2->h2 = 0;
        } else {
            k = (8 >> fld) - (yy >> fld) - 1;
            s2->h1 = k;
            s2->h2 = h2 - k;
        }
    } else {
        if (yy + (h2 << fld) > 8) {
            k = (8 >> fld) - (yy >> fld);
            s2->h1 = k;
            s2->h2 = h2 - k;
        } else {
            s2->h1 = h2;
            s2->h2 = 0;
        }
    }
    blk2 = blk + (((cxb - xb) << 1) + (cyb - yb)) * 0x180;
    s2->p0 = blk2 + (yy * 8 + 0x100);
    s2->p1 = blk2 + (yy * 8 + 0x400);
    s2->step = 8 << fld;
    d->bufs[d->cur].fn1[n] = D_0028DA10[idx1];
    d->bufs[d->cur].src1[n] = ref->base + mb * 0x180;
    d->bufs[d->cur].src2[n] = ref->base + (mb + ref->width) * 0x180;
    d->bufs[d->cur].fn2[n] = D_0028DA30[(avg << 2) | (xh << 1) | yh];
    cnt2 = np + d->cur * 80;
    (*cnt2)++;
}

typedef struct MpegSub_001893A8 {
    u8 b[0x1C];
} MpegSub_001893A8;

typedef struct MpegBuf_001893A8 {
    s32 unk0;
    s32 f4;
    u8 unk8[0x20];
    void (*fn1[4])(void *);
    void (*fn2[4])(void *);
    MpegSub_001893A8 sub1[4];
    MpegSub_001893A8 sub2[4];
    s32 p;
    s32 n;
    s32 f130;
    s32 unk134;
    s32 f138;
    s32 f13C;
} MpegBuf_001893A8;

typedef struct MpegDec_001893A8 {
    u8 unk0[0x590];
    MpegBuf_001893A8 bufs[2];
    s32 unk810[3];
    s32 f81C;
} MpegDec_001893A8;

extern char D_002BC730[];

/* Finishes output buffer `idx`: runs its callbacks, then copies or averages its reference picture. */
void func_001893A8(void *arg0, s32 idx) {
    extern void func_0018A318(s32, s32);
    MpegDec_001893A8 *d = arg0;
    s32 i;

    if (d->bufs[idx].f138 != 0) {
        for (i = 0; i < d->bufs[idx].n; i++) {
            d->bufs[idx].fn1[i](&d->bufs[idx].sub1[i]);
            d->bufs[idx].fn2[i](&d->bufs[idx].sub2[i]);
        }
    }
    if (d->bufs[idx].f130 != 0 && d->bufs[idx].f13C != 0) {
        _Error((s32)d, D_002BC730);
    }
    if (d->bufs[idx].f130 != 0) {
        func_0018A318(d->bufs[idx].p, d->bufs[idx].f4);
    } else if (d->bufs[idx].f13C != 0) {
        func_0018A318(d->bufs[idx].p, d->f81C);
    } else {
        _copyAddRefImage((void *)d->bufs[idx].p, (void *)d->f81C, (void *)d->bufs[idx].f4);
    }
}

/* Reference block copy, variant 000 (half-pel flags x/y, field) — hand-written MMI code. */
void _rix_000(void *p0) {
    __asm__ __volatile__("\n\
	lw	$5,0x14(%0)\n\
	lw	$6,0x18(%0)\n\
	lw	$7,0x8(%0)\n\
	lw	$14,0x0(%0)\n\
	lw	$13,0x4(%0)\n\
	lw	$12,0x10(%0)\n\
	sll	$11,$12,1\n\
	addiu	$15,$0,-0x1\n\
	mtsab	$13,0x0\n\
_func_001895C8_001895EC:\n\
	lq	$8,0x0($5)\n\
	addi	$7,$7,-0x1\n\
	lq	$9,0x0($6)\n\
	addu	$5,$5,$12\n\
	qfsrv	$10,$9,$8\n\
	pextlb	$8,$0,$10\n\
	pextub	$9,$0,$10\n\
	sq	$8,0x0($14)\n\
	addu	$6,$6,$12\n\
	sq	$9,0x10($14)\n\
	addu	$14,$14,$11\n\
	bgtz	$7,_func_001895C8_001895EC\n\
	addiu	$5,$5,0x80\n\
	addiu	$6,$6,0x80\n\
	lw	$7,0xC(%0)\n\
	and	$10,$15,$7\n\
	daddu	$15,$0,$0\n\
	bnez	$10,_func_001895C8_001895EC\n\
	" :  : "r" (p0));
}

/* Reference block copy and average, variant 000 — hand-written MMI code. */
void _ri0_000(void *p0) {
    __asm__ __volatile__("\n\
	lw	$5,0x14(%0)\n\
	lw	$6,0x18(%0)\n\
	lw	$14,0x0(%0)\n\
	lw	$13,0x4(%0)\n\
	lw	$12,0x10(%0)\n\
	sll	$11,$12,1\n\
	mtsab	$13,0x0\n\
	addiu	$24,$0,-0x1\n\
_func_00189640_00189660:\n\
	lw	$7,0x8(%0)\n\
	addiu	$15,$0,-0x1\n\
_func_00189640_00189668:\n\
	ld	$8,0x0($5)\n\
	ld	$9,0x0($6)\n\
	pcpyld	$8,$9,$8\n\
	qfsrv	$9,$8,$8\n\
	pextlb	$8,$0,$9\n\
	sq	$8,0x0($14)\n\
	addi	$7,$7,-0x1\n\
	addu	$5,$5,$12\n\
	addu	$14,$14,$11\n\
	addu	$6,$6,$12\n\
	bgtz	$7,_func_00189640_00189668\n\
	addiu	$5,$5,0x140\n\
	addiu	$6,$6,0x140\n\
	lw	$7,0xC(%0)\n\
	and	$10,$15,$7\n\
	daddu	$15,$0,$0\n\
	bnez	$10,_func_00189640_00189668\n\
	lw	$5,0x14(%0)\n\
	lw	$6,0x18(%0)\n\
	lw	$14,0x0(%0)\n\
	addiu	$5,$5,0x40\n\
	addiu	$6,$6,0x40\n\
	addiu	$14,$14,0x80\n\
	.set noreorder\n\
	bnez	$24,_func_00189640_00189660\n\
	daddu	$24,$0,$0\n\
	.set reorder\n\
	" :  : "r" (p0));
}

/* Reference block copy, variant 001 — hand-written MMI code. */
void _rix_001(void *p0) {
    __asm__ __volatile__("\n\
	pnor	$25,$0,$0\n\
	psrlh	$25,$25,15\n\
	lw	$5,0x14(%0)\n\
	lw	$6,0x18(%0)\n\
	lw	$7,0x8(%0)\n\
	lw	$14,0x0(%0)\n\
	lw	$13,0x4(%0)\n\
	lw	$24,0x10(%0)\n\
	lq	$8,0x0($5)\n\
	sll	$12,$24,1\n\
	lq	$9,0x0($6)\n\
	mtsab	$13,0x0\n\
	qfsrv	$10,$9,$8\n\
	pextlb	$8,$0,$10\n\
	addiu	$11,$0,-0x1\n\
	pextub	$9,$0,$10\n\
	beqz	$7,_func_001896D8_0018976C\n\
_func_001896D8_0018971C:\n\
	addu	$5,$5,$24\n\
	addu	$6,$6,$24\n\
	lq	$10,0x0($5)\n\
	lq	$15,0x0($6)\n\
	qfsrv	$2,$15,$10\n\
	pextlb	$10,$0,$2\n\
	addi	$7,$7,-0x1\n\
	pextub	$15,$0,$2\n\
	paddh	$2,$8,$10\n\
	paddh	$3,$9,$15\n\
	por	$8,$10,$0\n\
	por	$9,$15,$0\n\
	paddh	$2,$2,$25\n\
	paddh	$3,$3,$25\n\
	psrlh	$2,$2,1\n\
	psrlh	$3,$3,1\n\
	sq	$2,0x0($14)\n\
	sq	$3,0x10($14)\n\
	addu	$14,$14,$12\n\
	bgtz	$7,_func_001896D8_0018971C\n\
_func_001896D8_0018976C:\n\
	addiu	$5,$5,0x80\n\
	addiu	$6,$6,0x80\n\
	lw	$7,0xC(%0)\n\
	and	$10,$11,$7\n\
	daddu	$11,$0,$0\n\
	bnez	$10,_func_001896D8_0018971C\n\
	" :  : "r" (p0));
}

/* Reference block copy and average, variant 001 — hand-written MMI code. */
void _ri0_001(void *p0) {
    __asm__ __volatile__("\n\
	pnor	$25,$0,$0\n\
	psrlh	$25,$25,15\n\
	lw	$5,0x14(%0)\n\
	lw	$6,0x18(%0)\n\
	lw	$14,0x0(%0)\n\
	lw	$13,0x4(%0)\n\
	lw	$12,0x10(%0)\n\
	addiu	$11,$0,0x1\n\
	sll	$24,$12,1\n\
	mtsab	$13,0x0\n\
_func_00189790_001897B8:\n\
	lw	$7,0x8(%0)\n\
	ld	$8,0x0($5)\n\
	ld	$9,0x0($6)\n\
	pcpyld	$8,$9,$8\n\
	qfsrv	$8,$8,$8\n\
	ori	$11,$11,0x8000\n\
	pextlb	$15,$0,$8\n\
	beqz	$7,_func_00189790_00189814\n\
_func_00189790_001897D8:\n\
	addu	$5,$5,$12\n\
	addu	$6,$6,$12\n\
	ld	$8,0x0($5)\n\
	ld	$9,0x0($6)\n\
	pcpyld	$8,$9,$8\n\
	qfsrv	$8,$8,$8\n\
	pextlb	$10,$0,$8\n\
	addi	$7,$7,-0x1\n\
	paddh	$9,$10,$15\n\
	por	$15,$10,$0\n\
	paddh	$10,$9,$25\n\
	psrlh	$10,$10,1\n\
	sq	$10,0x0($14)\n\
	addu	$14,$14,$24\n\
	bgtz	$7,_func_00189790_001897D8\n\
_func_00189790_00189814:\n\
	psrah	$10,$11,15\n\
	addiu	$5,$5,0x140\n\
	lw	$7,0xC(%0)\n\
	addiu	$6,$6,0x140\n\
	and	$10,$10,$7\n\
	andi	$11,$11,0x7FFF\n\
	bnez	$10,_func_00189790_001897D8\n\
	lw	$5,0x14(%0)\n\
	lw	$6,0x18(%0)\n\
	lw	$14,0x0(%0)\n\
	addiu	$5,$5,0x40\n\
	addiu	$6,$6,0x40\n\
	addiu	$14,$14,0x80\n\
	andi	$10,$11,0x1\n\
	andi	$11,$11,0xFFFE\n\
	bnez	$10,_func_00189790_001897B8\n\
	" :  : "r" (p0));
}

/* Reference block copy, variant 010 — hand-written MMI code. */
void _rix_010(void *p0) {
    __asm__ __volatile__("\n\
	pnor	$25,$0,$0\n\
	psrlh	$25,$25,15\n\
	lw	$5,0x14(%0)\n\
	lw	$6,0x18(%0)\n\
	lw	$7,0x8(%0)\n\
	lw	$14,0x0(%0)\n\
	lw	$13,0x4(%0)\n\
	addiu	$24,$0,0x1\n\
	lw	$9,0x10(%0)\n\
	sll	$8,$9,1\n\
	addiu	$11,$0,-0x1\n\
_func_00189860_0018988C:\n\
	lq	$10,0x0($5)\n\
	lq	$15,0x0($6)\n\
	mtsab	$13,0x0\n\
	qfsrv	$2,$15,$10\n\
	qfsrv	$3,$10,$15\n\
	pextlb	$10,$0,$2\n\
	addi	$7,$7,-0x1\n\
	pextub	$15,$0,$2\n\
	mtsab	$24,0x0\n\
	qfsrv	$3,$3,$2\n\
	pextlb	$2,$0,$3\n\
	pextub	$3,$0,$3\n\
	paddh	$10,$10,$2\n\
	paddh	$15,$15,$3\n\
	paddh	$2,$10,$25\n\
	paddh	$3,$15,$25\n\
	psrlh	$2,$2,1\n\
	psrlh	$3,$3,1\n\
	sq	$2,0x0($14)\n\
	sq	$3,0x10($14)\n\
	addu	$5,$5,$9\n\
	addu	$6,$6,$9\n\
	addu	$14,$14,$8\n\
	bgtz	$7,_func_00189860_0018988C\n\
	addiu	$5,$5,0x80\n\
	addiu	$6,$6,0x80\n\
	lw	$7,0xC(%0)\n\
	and	$12,$11,$7\n\
	daddu	$11,$0,$0\n\
	bnez	$12,_func_00189860_0018988C\n\
	" :  : "r" (p0));
}

/* Reference block copy and average, variant 010 — hand-written MMI code. */
void _ri0_010(void *p0) {
    __asm__ __volatile__("\n\
	pnor	$25,$0,$0\n\
	psrlh	$25,$25,15\n\
	lw	$5,0x14(%0)\n\
	lw	$6,0x18(%0)\n\
	lw	$14,0x0(%0)\n\
	lw	$13,0x4(%0)\n\
	addiu	$24,$0,0x1\n\
	addiu	$12,$0,-0x1\n\
	lw	$3,0x10(%0)\n\
	sll	$2,$3,1\n\
_func_00189910_00189938:\n\
	lw	$7,0x8(%0)\n\
	addiu	$11,$0,-0x1\n\
_func_00189910_00189940:\n\
	ld	$8,0x0($5)\n\
	ld	$9,0x0($6)\n\
	pcpyld	$8,$9,$8\n\
	mtsab	$13,0x0\n\
	qfsrv	$8,$8,$8\n\
	pextlb	$9,$0,$8\n\
	addi	$7,$7,-0x1\n\
	addu	$5,$5,$3\n\
	addu	$6,$6,$3\n\
	mtsab	$24,0x0\n\
	qfsrv	$10,$0,$8\n\
	pextlb	$8,$0,$10\n\
	paddh	$10,$9,$8\n\
	paddh	$10,$10,$25\n\
	psrlh	$10,$10,1\n\
	sq	$10,0x0($14)\n\
	addu	$14,$14,$2\n\
	bgtz	$7,_func_00189910_00189940\n\
	addiu	$5,$5,0x140\n\
	addiu	$6,$6,0x140\n\
	lw	$7,0xC(%0)\n\
	and	$10,$11,$7\n\
	daddu	$11,$0,$0\n\
	bnez	$10,_func_00189910_00189940\n\
	lw	$5,0x14(%0)\n\
	lw	$6,0x18(%0)\n\
	lw	$14,0x0(%0)\n\
	addiu	$5,$5,0x40\n\
	addiu	$6,$6,0x40\n\
	addiu	$14,$14,0x80\n\
	.set noreorder\n\
	bnez	$12,_func_00189910_00189938\n\
	daddu	$12,$0,$0\n\
	.set reorder\n\
	" :  : "r" (p0));
}

/* Reference block copy, variant 011 — hand-written MMI code. */
void _rix_011(void *p0) {
    __asm__ __volatile__("\n\
	pnor	$25,$0,$0\n\
	psrlh	$25,$25,15\n\
	psllh	$25,$25,1\n\
	lw	$5,0x14(%0)\n\
	lw	$6,0x18(%0)\n\
	lw	$7,0x8(%0)\n\
	lw	$14,0x0(%0)\n\
	lw	$13,0x4(%0)\n\
	lw	$12,0x10(%0)\n\
	addiu	$24,$0,0x1\n\
	lq	$8,0x0($5)\n\
	lq	$9,0x0($6)\n\
	mtsab	$13,0x0\n\
	qfsrv	$10,$9,$8\n\
	qfsrv	$15,$8,$9\n\
	pextlb	$8,$0,$10\n\
	pextub	$9,$0,$10\n\
	addiu	$11,$0,-0x1\n\
	mtsab	$24,0x0\n\
	qfsrv	$15,$15,$10\n\
	pextlb	$10,$0,$15\n\
	pextub	$15,$0,$15\n\
	paddh	$8,$8,$10\n\
	paddh	$9,$9,$15\n\
	beqz	$7,_func_001899C8_00189AA0\n\
_func_001899C8_00189A2C:\n\
	addu	$5,$5,$12\n\
	addu	$6,$6,$12\n\
	lq	$10,0x0($5)\n\
	lq	$15,0x0($6)\n\
	mtsab	$13,0x0\n\
	qfsrv	$2,$15,$10\n\
	qfsrv	$3,$10,$15\n\
	pextlb	$10,$0,$2\n\
	addi	$7,$7,-0x1\n\
	pextub	$15,$0,$2\n\
	mtsab	$24,0x0\n\
	qfsrv	$3,$3,$2\n\
	pextlb	$2,$0,$3\n\
	pextub	$3,$0,$3\n\
	paddh	$10,$10,$2\n\
	paddh	$15,$15,$3\n\
	paddh	$2,$8,$10\n\
	paddh	$3,$9,$15\n\
	por	$8,$10,$0\n\
	por	$9,$15,$0\n\
	paddh	$2,$2,$25\n\
	paddh	$3,$3,$25\n\
	psrlh	$2,$2,2\n\
	psrlh	$3,$3,2\n\
	sq	$2,0x0($14)\n\
	sll	$10,$12,1\n\
	sq	$3,0x10($14)\n\
	addu	$14,$14,$10\n\
	bgtz	$7,_func_001899C8_00189A2C\n\
_func_001899C8_00189AA0:\n\
	addiu	$5,$5,0x80\n\
	addiu	$6,$6,0x80\n\
	lw	$7,0xC(%0)\n\
	and	$10,$11,$7\n\
	daddu	$11,$0,$0\n\
	bnez	$10,_func_001899C8_00189A2C\n\
	" :  : "r" (p0));
}

/* Reference block copy and average, variant 011 — hand-written MMI code. */
void _ri0_011(void *p0) {
    __asm__ __volatile__("\n\
	pnor	$25,$0,$0\n\
	psrlh	$25,$25,15\n\
	psllh	$25,$25,1\n\
	lw	$5,0x14(%0)\n\
	lw	$6,0x18(%0)\n\
	lw	$14,0x0(%0)\n\
	lw	$13,0x4(%0)\n\
	lw	$12,0x10(%0)\n\
	addiu	$24,$0,0x1\n\
	addiu	$11,$0,0x1\n\
_func_00189AC0_00189AE8:\n\
	lw	$7,0x8(%0)\n\
	ld	$8,0x0($5)\n\
	ld	$9,0x0($6)\n\
	pcpyld	$8,$9,$8\n\
	mtsab	$13,0x0\n\
	qfsrv	$8,$8,$8\n\
	pextlb	$9,$0,$8\n\
	addu	$5,$5,$12\n\
	ori	$11,$11,0x8000\n\
	mtsab	$24,0x0\n\
	qfsrv	$10,$0,$8\n\
	pextlb	$8,$0,$10\n\
	paddh	$15,$9,$8\n\
	beqz	$7,_func_00189AC0_00189B74\n\
_func_00189AC0_00189B20:\n\
	addu	$6,$6,$12\n\
	ld	$8,0x0($5)\n\
	ld	$9,0x0($6)\n\
	pcpyld	$8,$9,$8\n\
	mtsab	$13,0x0\n\
	qfsrv	$8,$8,$8\n\
	pextlb	$9,$0,$8\n\
	addi	$7,$7,-0x1\n\
	addu	$5,$5,$12\n\
	mtsab	$24,0x0\n\
	qfsrv	$10,$0,$8\n\
	pextlb	$8,$0,$10\n\
	paddh	$10,$9,$8\n\
	paddh	$9,$10,$15\n\
	por	$15,$10,$0\n\
	paddh	$10,$9,$25\n\
	sll	$8,$12,1\n\
	psrlh	$10,$10,2\n\
	sq	$10,0x0($14)\n\
	addu	$14,$14,$8\n\
	bgtz	$7,_func_00189AC0_00189B20\n\
_func_00189AC0_00189B74:\n\
	psrah	$10,$11,15\n\
	addiu	$5,$5,0x140\n\
	lw	$7,0xC(%0)\n\
	addiu	$6,$6,0x140\n\
	and	$10,$10,$7\n\
	andi	$11,$11,0x7FFF\n\
	bnez	$10,_func_00189AC0_00189B20\n\
	lw	$5,0x14(%0)\n\
	lw	$6,0x18(%0)\n\
	lw	$14,0x0(%0)\n\
	addiu	$5,$5,0x40\n\
	addiu	$6,$6,0x40\n\
	addiu	$14,$14,0x80\n\
	andi	$10,$11,0x1\n\
	andi	$11,$11,0xFFFE\n\
	bnez	$10,_func_00189AC0_00189AE8\n\
	" :  : "r" (p0));
}

/* Reference block copy, variant 100 — hand-written MMI code. */
void _rix_100(void *p0) {
    __asm__ __volatile__("\n\
	lw	$5,0x14(%0)\n\
	lw	$6,0x18(%0)\n\
	lw	$7,0x8(%0)\n\
	lw	$14,0x0(%0)\n\
	lw	$13,0x4(%0)\n\
	lw	$9,0x10(%0)\n\
	sll	$8,$9,1\n\
	addiu	$11,$0,-0x1\n\
	mtsab	$13,0x0\n\
_func_00189BC0_00189BE4:\n\
	lq	$10,0x0($5)\n\
	lq	$15,0x0($6)\n\
	qfsrv	$2,$15,$10\n\
	pextlb	$10,$0,$2\n\
	pextub	$15,$0,$2\n\
	lq	$2,0x0($14)\n\
	lq	$3,0x10($14)\n\
	paddh	$2,$2,$10\n\
	paddh	$3,$3,$15\n\
	pnor	$25,$0,$0\n\
	psrlh	$25,$25,15\n\
	paddh	$10,$2,$25\n\
	psrlh	$2,$10,1\n\
	paddh	$10,$3,$25\n\
	psrlh	$3,$10,1\n\
	sq	$2,0x0($14)\n\
	sq	$3,0x10($14)\n\
	addi	$7,$7,-0x1\n\
	addu	$5,$5,$9\n\
	addu	$14,$14,$8\n\
	addu	$6,$6,$9\n\
	bgtz	$7,_func_00189BC0_00189BE4\n\
	addiu	$5,$5,0x80\n\
	addiu	$6,$6,0x80\n\
	lw	$7,0xC(%0)\n\
	and	$12,$11,$7\n\
	daddu	$11,$0,$0\n\
	bnez	$12,_func_00189BC0_00189BE4\n\
	" :  : "r" (p0));
}

/* Reference block copy and average, variant 100 — hand-written MMI code. */
void _ri0_100(void *p0) {
    __asm__ __volatile__("\n\
	lw	$5,0x14(%0)\n\
	lw	$6,0x18(%0)\n\
	lw	$14,0x0(%0)\n\
	lw	$13,0x4(%0)\n\
	addiu	$12,$0,-0x1\n\
	lw	$3,0x10(%0)\n\
	sll	$2,$3,1\n\
	mtsab	$13,0x0\n\
_func_00189C60_00189C80:\n\
	lw	$7,0x8(%0)\n\
	addiu	$11,$0,-0x1\n\
_func_00189C60_00189C88:\n\
	ld	$8,0x0($5)\n\
	ld	$9,0x0($6)\n\
	pcpyld	$8,$9,$8\n\
	qfsrv	$8,$8,$8\n\
	pextlb	$9,$0,$8\n\
	addi	$7,$7,-0x1\n\
	addu	$5,$5,$3\n\
	addu	$6,$6,$3\n\
	lq	$8,0x0($14)\n\
	paddh	$10,$9,$8\n\
	pcgth	$9,$10,$0\n\
	psrlh	$9,$9,15\n\
	paddh	$10,$10,$9\n\
	psrlh	$10,$10,1\n\
	sq	$10,0x0($14)\n\
	addu	$14,$14,$2\n\
	bgtz	$7,_func_00189C60_00189C88\n\
	addiu	$5,$5,0x140\n\
	addiu	$6,$6,0x140\n\
	lw	$7,0xC(%0)\n\
	and	$10,$11,$7\n\
	daddu	$11,$0,$0\n\
	bnez	$10,_func_00189C60_00189C88\n\
	lw	$5,0x14(%0)\n\
	lw	$6,0x18(%0)\n\
	lw	$14,0x0(%0)\n\
	addiu	$5,$5,0x40\n\
	addiu	$6,$6,0x40\n\
	addiu	$14,$14,0x80\n\
	.set noreorder\n\
	bnez	$12,_func_00189C60_00189C80\n\
	daddu	$12,$0,$0\n\
	.set reorder\n\
	" :  : "r" (p0));
}

/* Reference block copy, variant 101 — hand-written MMI code. */
void _rix_101(void *p0) {
    __asm__ __volatile__("\n\
	pnor	$25,$0,$0\n\
	psrlh	$25,$25,15\n\
	lw	$5,0x14(%0)\n\
	lw	$6,0x18(%0)\n\
	lw	$7,0x8(%0)\n\
	lw	$14,0x0(%0)\n\
	lw	$13,0x4(%0)\n\
	lw	$12,0x10(%0)\n\
	lq	$8,0x0($5)\n\
	lq	$9,0x0($6)\n\
	mtsab	$13,0x0\n\
	qfsrv	$10,$9,$8\n\
	sll	$24,$12,1\n\
	pextlb	$8,$0,$10\n\
	addiu	$11,$0,-0x1\n\
	pextub	$9,$0,$10\n\
	beqz	$7,_func_00189D10_00189DCC\n\
_func_00189D10_00189D54:\n\
	addu	$5,$5,$12\n\
	addu	$6,$6,$12\n\
	lq	$10,0x0($5)\n\
	lq	$15,0x0($6)\n\
	qfsrv	$2,$15,$10\n\
	pextlb	$10,$0,$2\n\
	addi	$7,$7,-0x1\n\
	pextub	$15,$0,$2\n\
	paddh	$2,$8,$10\n\
	paddh	$3,$9,$15\n\
	por	$8,$10,$0\n\
	por	$9,$15,$0\n\
	paddh	$2,$2,$25\n\
	paddh	$3,$3,$25\n\
	psrlh	$2,$2,1\n\
	psrlh	$3,$3,1\n\
	lq	$10,0x0($14)\n\
	lq	$15,0x10($14)\n\
	paddh	$2,$2,$10\n\
	paddh	$3,$3,$15\n\
	paddh	$10,$2,$25\n\
	psrlh	$2,$10,1\n\
	pcgth	$10,$3,$0\n\
	psrlh	$10,$10,15\n\
	paddh	$10,$3,$10\n\
	psrlh	$3,$10,1\n\
	sq	$2,0x0($14)\n\
	sq	$3,0x10($14)\n\
	addu	$14,$14,$24\n\
	bgtz	$7,_func_00189D10_00189D54\n\
_func_00189D10_00189DCC:\n\
	addiu	$5,$5,0x80\n\
	addiu	$6,$6,0x80\n\
	lw	$7,0xC(%0)\n\
	and	$10,$11,$7\n\
	daddu	$11,$0,$0\n\
	bnez	$10,_func_00189D10_00189D54\n\
	" :  : "r" (p0));
}

/* Reference block copy and average, variant 101 — hand-written MMI code. */
void _ri0_101(void *p0) {
    __asm__ __volatile__("\n\
	pnor	$25,$0,$0\n\
	psrlh	$25,$25,15\n\
	lw	$5,0x14(%0)\n\
	lw	$6,0x18(%0)\n\
	lw	$14,0x0(%0)\n\
	lw	$13,0x4(%0)\n\
	lw	$12,0x10(%0)\n\
	addiu	$11,$0,0x1\n\
	sll	$24,$12,1\n\
	mtsab	$13,0x0\n\
_func_00189DF0_00189E18:\n\
	lw	$7,0x8(%0)\n\
	ld	$8,0x0($5)\n\
	ld	$9,0x0($6)\n\
	pcpyld	$8,$9,$8\n\
	qfsrv	$8,$8,$8\n\
	ori	$11,$11,0x8000\n\
	pextlb	$15,$0,$8\n\
	beqz	$7,_func_00189DF0_00189E8C\n\
_func_00189DF0_00189E38:\n\
	addu	$5,$5,$12\n\
	addu	$6,$6,$12\n\
	ld	$8,0x0($5)\n\
	ld	$9,0x0($6)\n\
	pcpyld	$8,$9,$8\n\
	qfsrv	$8,$8,$8\n\
	pextlb	$10,$0,$8\n\
	addi	$7,$7,-0x1\n\
	paddh	$9,$10,$15\n\
	por	$15,$10,$0\n\
	paddh	$10,$9,$25\n\
	psrlh	$10,$10,1\n\
	lq	$8,0x0($14)\n\
	paddh	$10,$10,$8\n\
	pcgth	$9,$10,$0\n\
	psrlh	$9,$9,15\n\
	paddh	$10,$10,$9\n\
	psrlh	$10,$10,1\n\
	sq	$10,0x0($14)\n\
	addu	$14,$14,$24\n\
	bgtz	$7,_func_00189DF0_00189E38\n\
_func_00189DF0_00189E8C:\n\
	psrah	$10,$11,15\n\
	addiu	$5,$5,0x140\n\
	lw	$7,0xC(%0)\n\
	addiu	$6,$6,0x140\n\
	and	$10,$10,$7\n\
	andi	$11,$11,0x7FFF\n\
	bnez	$10,_func_00189DF0_00189E38\n\
	lw	$5,0x14(%0)\n\
	lw	$6,0x18(%0)\n\
	lw	$14,0x0(%0)\n\
	addiu	$5,$5,0x40\n\
	addiu	$6,$6,0x40\n\
	addiu	$14,$14,0x80\n\
	andi	$10,$11,0x1\n\
	andi	$11,$11,0xFFFE\n\
	bnez	$10,_func_00189DF0_00189E18\n\
	" :  : "r" (p0));
}

/* Reference block copy, variant 110 — hand-written MMI code. */
void _rix_110(void *p0) {
    __asm__ __volatile__("\n\
	pnor	$25,$0,$0\n\
	psrlh	$25,$25,15\n\
	lw	$5,0x14(%0)\n\
	lw	$6,0x18(%0)\n\
	lw	$7,0x8(%0)\n\
	lw	$14,0x0(%0)\n\
	lw	$13,0x4(%0)\n\
	addiu	$24,$0,0x1\n\
	lw	$9,0x10(%0)\n\
	sll	$8,$9,1\n\
	addiu	$11,$0,-0x1\n\
_func_00189ED8_00189F04:\n\
	lq	$10,0x0($5)\n\
	lq	$15,0x0($6)\n\
	mtsab	$13,0x0\n\
	qfsrv	$2,$15,$10\n\
	qfsrv	$3,$10,$15\n\
	pextlb	$10,$0,$2\n\
	addi	$7,$7,-0x1\n\
	pextub	$15,$0,$2\n\
	mtsab	$24,0x0\n\
	qfsrv	$3,$3,$2\n\
	pextlb	$2,$0,$3\n\
	pextub	$3,$0,$3\n\
	paddh	$10,$10,$2\n\
	paddh	$15,$15,$3\n\
	paddh	$2,$10,$25\n\
	paddh	$3,$15,$25\n\
	psrlh	$2,$2,1\n\
	psrlh	$3,$3,1\n\
	lq	$10,0x0($14)\n\
	lq	$15,0x10($14)\n\
	paddh	$2,$2,$10\n\
	paddh	$3,$3,$15\n\
	paddh	$10,$2,$25\n\
	psrlh	$2,$10,1\n\
	pcgth	$10,$3,$0\n\
	psrlh	$10,$10,15\n\
	paddh	$10,$3,$10\n\
	psrlh	$3,$10,1\n\
	sq	$2,0x0($14)\n\
	sq	$3,0x10($14)\n\
	addu	$5,$5,$9\n\
	addu	$6,$6,$9\n\
	addu	$14,$14,$8\n\
	bgtz	$7,_func_00189ED8_00189F04\n\
	addiu	$5,$5,0x80\n\
	addiu	$6,$6,0x80\n\
	lw	$7,0xC(%0)\n\
	and	$12,$11,$7\n\
	daddu	$11,$0,$0\n\
	bnez	$12,_func_00189ED8_00189F04\n\
	" :  : "r" (p0));
}

/* Reference block copy and average, variant 110 — hand-written MMI code. */
void _ri0_110(void *p0) {
    __asm__ __volatile__("\n\
	pnor	$25,$0,$0\n\
	psrlh	$25,$25,15\n\
	lw	$5,0x14(%0)\n\
	lw	$6,0x18(%0)\n\
	lw	$14,0x0(%0)\n\
	lw	$13,0x4(%0)\n\
	addiu	$24,$0,0x1\n\
	addiu	$12,$0,-0x1\n\
	lw	$3,0x10(%0)\n\
	sll	$2,$3,1\n\
_func_00189FB0_00189FD8:\n\
	lw	$7,0x8(%0)\n\
	addiu	$11,$0,-0x1\n\
_func_00189FB0_00189FE0:\n\
	ld	$8,0x0($5)\n\
	ld	$9,0x0($6)\n\
	pcpyld	$8,$9,$8\n\
	mtsab	$13,0x0\n\
	qfsrv	$8,$8,$8\n\
	pextlb	$9,$0,$8\n\
	addi	$7,$7,-0x1\n\
	addu	$5,$5,$3\n\
	addu	$6,$6,$3\n\
	mtsab	$24,0x0\n\
	qfsrv	$10,$0,$8\n\
	pextlb	$8,$0,$10\n\
	paddh	$10,$9,$8\n\
	paddh	$10,$10,$25\n\
	psrlh	$10,$10,1\n\
	lq	$8,0x0($14)\n\
	paddh	$10,$10,$8\n\
	pcgth	$9,$10,$0\n\
	psrlh	$9,$9,15\n\
	paddh	$10,$10,$9\n\
	psrlh	$10,$10,1\n\
	sq	$10,0x0($14)\n\
	addu	$14,$14,$2\n\
	bgtz	$7,_func_00189FB0_00189FE0\n\
	addiu	$5,$5,0x140\n\
	addiu	$6,$6,0x140\n\
	lw	$7,0xC(%0)\n\
	and	$10,$11,$7\n\
	daddu	$11,$0,$0\n\
	bnez	$10,_func_00189FB0_00189FE0\n\
	lw	$5,0x14(%0)\n\
	lw	$6,0x18(%0)\n\
	lw	$14,0x0(%0)\n\
	addiu	$5,$5,0x40\n\
	addiu	$6,$6,0x40\n\
	addiu	$14,$14,0x80\n\
	.set noreorder\n\
	bnez	$12,_func_00189FB0_00189FD8\n\
	daddu	$12,$0,$0\n\
	.set reorder\n\
	" :  : "r" (p0));
}

/* Reference block copy, variant 111 — hand-written MMI code. */
void _rix_111(void *p0) {
    __asm__ __volatile__("\n\
	pnor	$25,$0,$0\n\
	psrlh	$25,$25,15\n\
	psllh	$25,$25,1\n\
	lw	$5,0x14(%0)\n\
	lw	$6,0x18(%0)\n\
	lw	$7,0x8(%0)\n\
	lw	$14,0x0(%0)\n\
	lw	$13,0x4(%0)\n\
	lw	$24,0x10(%0)\n\
	addiu	$12,$0,0x1\n\
	lq	$8,0x0($5)\n\
	lq	$9,0x0($6)\n\
	mtsab	$13,0x0\n\
	qfsrv	$10,$9,$8\n\
	qfsrv	$15,$8,$9\n\
	pextlb	$8,$0,$10\n\
	pextub	$9,$0,$10\n\
	addiu	$11,$0,-0x1\n\
	mtsab	$12,0x0\n\
	qfsrv	$15,$15,$10\n\
	pextlb	$10,$0,$15\n\
	pextub	$15,$0,$15\n\
	paddh	$8,$8,$10\n\
	paddh	$9,$9,$15\n\
	beqz	$7,_func_0018A080_0018A180\n\
_func_0018A080_0018A0E4:\n\
	addu	$5,$5,$24\n\
	addu	$6,$6,$24\n\
	lq	$10,0x0($5)\n\
	lq	$15,0x0($6)\n\
	mtsab	$13,0x0\n\
	qfsrv	$2,$15,$10\n\
	qfsrv	$3,$10,$15\n\
	pextlb	$10,$0,$2\n\
	addi	$7,$7,-0x1\n\
	pextub	$15,$0,$2\n\
	mtsab	$12,0x0\n\
	qfsrv	$3,$3,$2\n\
	pextlb	$2,$0,$3\n\
	pextub	$3,$0,$3\n\
	paddh	$10,$10,$2\n\
	paddh	$15,$15,$3\n\
	paddh	$2,$8,$10\n\
	paddh	$3,$9,$15\n\
	por	$8,$10,$0\n\
	por	$9,$15,$0\n\
	paddh	$2,$2,$25\n\
	paddh	$3,$3,$25\n\
	psrlh	$2,$2,2\n\
	psrlh	$3,$3,2\n\
	lq	$10,0x0($14)\n\
	lq	$15,0x10($14)\n\
	paddh	$2,$2,$10\n\
	paddh	$3,$3,$15\n\
	pnor	$25,$0,$0\n\
	psrlh	$25,$25,15\n\
	paddh	$10,$2,$25\n\
	psrlh	$2,$10,1\n\
	paddh	$10,$3,$25\n\
	psrlh	$3,$10,1\n\
	sq	$2,0x0($14)\n\
	sll	$10,$24,1\n\
	sq	$3,0x10($14)\n\
	addu	$14,$14,$10\n\
	bgtz	$7,_func_0018A080_0018A0E4\n\
_func_0018A080_0018A180:\n\
	addiu	$5,$5,0x80\n\
	addiu	$6,$6,0x80\n\
	lw	$7,0xC(%0)\n\
	and	$10,$11,$7\n\
	daddu	$11,$0,$0\n\
	bnez	$10,_func_0018A080_0018A0E4\n\
	" :  : "r" (p0));
}

/* Reference block copy and average, variant 111 — hand-written MMI code. */
void _ri0_111(void *p0) {
    __asm__ __volatile__("\n\
	pnor	$25,$0,$0\n\
	psrlh	$25,$25,15\n\
	psllh	$25,$25,1\n\
	lw	$5,0x14(%0)\n\
	lw	$6,0x18(%0)\n\
	lw	$14,0x0(%0)\n\
	lw	$13,0x4(%0)\n\
	lw	$12,0x10(%0)\n\
	addiu	$24,$0,0x1\n\
	addiu	$11,$0,0x1\n\
_func_0018A1A0_0018A1C8:\n\
	lw	$7,0x8(%0)\n\
	ld	$8,0x0($5)\n\
	ld	$9,0x0($6)\n\
	pcpyld	$8,$9,$8\n\
	mtsab	$13,0x0\n\
	qfsrv	$8,$8,$8\n\
	pextlb	$9,$0,$8\n\
	addu	$5,$5,$12\n\
	ori	$11,$11,0x8000\n\
	mtsab	$24,0x0\n\
	qfsrv	$10,$0,$8\n\
	pextlb	$8,$0,$10\n\
	paddh	$15,$9,$8\n\
	beqz	$7,_func_0018A1A0_0018A26C\n\
_func_0018A1A0_0018A200:\n\
	addu	$6,$6,$12\n\
	ld	$8,0x0($5)\n\
	ld	$9,0x0($6)\n\
	pcpyld	$8,$9,$8\n\
	mtsab	$13,0x0\n\
	qfsrv	$8,$8,$8\n\
	pextlb	$9,$0,$8\n\
	addi	$7,$7,-0x1\n\
	addu	$5,$5,$12\n\
	mtsab	$24,0x0\n\
	qfsrv	$10,$0,$8\n\
	pextlb	$8,$0,$10\n\
	paddh	$10,$9,$8\n\
	paddh	$9,$10,$15\n\
	por	$15,$10,$0\n\
	paddh	$10,$9,$25\n\
	psrlh	$10,$10,2\n\
	lq	$8,0x0($14)\n\
	paddh	$10,$10,$8\n\
	pcgth	$9,$10,$0\n\
	psrlh	$9,$9,15\n\
	paddh	$10,$10,$9\n\
	sll	$8,$12,1\n\
	psrlh	$10,$10,1\n\
	sq	$10,0x0($14)\n\
	addu	$14,$14,$8\n\
	bgtz	$7,_func_0018A1A0_0018A200\n\
_func_0018A1A0_0018A26C:\n\
	psrah	$10,$11,15\n\
	addiu	$5,$5,0x140\n\
	lw	$7,0xC(%0)\n\
	addiu	$6,$6,0x140\n\
	and	$10,$10,$7\n\
	andi	$11,$11,0x7FFF\n\
	bnez	$10,_func_0018A1A0_0018A200\n\
	lw	$5,0x14(%0)\n\
	lw	$6,0x18(%0)\n\
	lw	$14,0x0(%0)\n\
	addiu	$5,$5,0x40\n\
	addiu	$6,$6,0x40\n\
	addiu	$14,$14,0x80\n\
	andi	$10,$11,0x1\n\
	andi	$11,$11,0xFFFE\n\
	bnez	$10,_func_0018A1A0_0018A1C8\n\
	" :  : "r" (p0));
}

/* Copies or averages a reference block into the output. */
void _copyAddRefImage(void *p0, void *p1, void *p2) {
    __asm__ __volatile__("\n\
	addiu	$12,$0,0x18\n\
	lui	$10,%%hi(D_0018A360)\n\
	addiu	$10,$10,%%lo(D_0018A360)\n\
	lq	$11,0x0($10)\n\
_func_0018A2B8_0018A2C8:\n\
	lq	$8,0x0(%1)\n\
	addi	$12,$12,-0x1\n\
	lq	$13,0x0(%2)\n\
	addiu	%0,%0,0x10\n\
	lq	$9,0x10(%1)\n\
	paddh	$8,$8,$13\n\
	lq	$2,0x10(%2)\n\
	pminh	$8,$8,$11\n\
	paddh	$9,$9,$2\n\
	pmaxh	$8,$8,$0\n\
	pminh	$9,$9,$11\n\
	addiu	%1,%1,0x20\n\
	pmaxh	$9,$9,$0\n\
	addiu	%2,%2,0x20\n\
	ppacb	$10,$9,$8\n\
	sq	$10,-0x10(%0)\n\
	bnez	$12,_func_0018A2B8_0018A2C8\n\
	" :  : "r" (p0), "r" (p1), "r" (p2));
}

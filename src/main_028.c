#include "common.h"

void func_00187BE8(void *p0, void *p1) {
    __asm__ __volatile__("\n\
	lqc2	$vf4,0x0(%1)\n\
	vitof4.xyzw	$vf5,$vf4\n\
	sqc2	$vf5,0x0(%0)\n\
	" :  : "r" (p0), "r" (p1));
}

void func_00187BF8(void *p0, void *p1) {
    __asm__ __volatile__("\n\
	lqc2	$vf4,0x0(%1)\n\
	vitof0.xyzw	$vf5,$vf4\n\
	sqc2	$vf5,0x0(%0)\n\
	" :  : "r" (p0), "r" (p1));
}

void func_00187C08(void *p0) {
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
	" :  : "r" (p0));
}

void func_00187C30(void *p0, void *p1, void *p2, void *p3) {
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

void func_00187CA8(void *p0, void *p1, float f0) {
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
	jal	func_00187C30\n\
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
	" :  : "r" (p0), "r" (p1), "f" (f0));
}

void func_00187D50(void *p0, void *p1, float f0) {
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
	jal	func_00187C30\n\
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
	" :  : "r" (p0), "r" (p1), "f" (f0));
}

void func_00187DF8(void *p0, void *p1, float f0) {
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
	jal	func_00187C30\n\
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
	" :  : "r" (p0), "r" (p1), "f" (f0));
}

void func_00187EA0(s32 arg0, s32 arg1, void *arg2) {
    func_00187CA8(arg0, arg1, (*(f32 *)((u8 *)arg2 + 8)));
    func_00187DF8(arg0, arg0, (*(f32 *)((u8 *)arg2 + 4)));
    func_00187D50(arg0, arg0, (*(f32 *)arg2));
}

void func_00187EF0(void *p0, void *p1, float f0, float f1) {
    __asm__ __volatile__("\n\
	mfc1	$8,%2\n\
	mfc1	$9,%3\n\
	lqc2	$vf6,0x0(%1)\n\
	qmtc2.ni	$8,$vf4\n\
	qmtc2.ni	$9,$vf5\n\
	vmaxx.xyzw	$vf6,$vf6,$vf4x\n\
	vminix.xyzw	$vf6,$vf6,$vf5x\n\
	sqc2	$vf6,0x0(%0)\n\
	" :  : "r" (p0), "r" (p1), "f" (f0), "f" (f1));
}

void func_00187F18(s32 arg0, s32 arg1, s32 *arg2, s32 *arg3) {
    s32 sp0[4];
    s32 sp10[4];
    s32 sp20[8];
    s32 sp40[4];

    func_00187C08(sp0);
    func_00187958(sp40, arg3, arg2);
    func_001879A0(sp0, sp40);
    func_001879A0(sp20, arg2);
    func_00187958(sp10, sp20, sp0);
    func_00187B60(sp0, sp0, arg1);
    func_00187A28(arg0, sp0);
}

void func_00187FC8(f32 (*m)[4], f32 *x, f32 *y, f32 *z) {
    f32 v[4];

    func_00187B48(v, x, -1.0f);
    func_001879A0(m[0], v);
    func_00187B48(v, y, -1.0f);
    func_001879A0(m[1], v);
    func_00187B48(v, z, -1.0f);
    func_001879A0(m[2], v);
    m[3][0] = m[3][1] = m[3][2] = 0.0f;
    m[3][3] = 1.0f;
    func_001879E0(m, m);
}

void func_00188088(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_00187B90(arg0, arg1);
    func_00187B90(arg0 + 0x10, arg2);
    func_00187B90(arg0 + 0x20, arg3);
    func_00187B90(arg0 + 0x30, arg4);
}

void func_001880F0(f32 (*m)[4], f32 scrz, f32 ax, f32 ay, f32 cx, f32 cy, f32 zmin, f32 zmax, f32 nearz, f32 farz) {
    f32 az, cz;
    f32 mt[4][4];

    cz = (-zmax * nearz + zmin * farz) / (-nearz + farz);
    az = farz * nearz * (-zmin + zmax) / (-nearz + farz);

    func_00187C08(m);
    m[0][0] = scrz;
    m[1][1] = scrz;
    m[2][2] = 0.0f;
    m[3][2] = 1.0f;
    m[2][3] = 1.0f;
    m[3][3] = 0.0f;

    func_00187C08(mt);
    mt[0][0] = ax;
    mt[1][1] = ay;
    mt[2][2] = az;
    mt[3][0] = cx;
    mt[3][1] = cy;
    mt[3][2] = cz;

    func_00187910(m, mt, m);
}

void func_001881F8(f32 (*m)[4], f32 *lp, f32 a, f32 b, f32 c, s32 mode) {



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

void func_00188388(void *p0, void *p1, void *p2, void *p3) {
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
	" :  : "r" (p0), "r" (p1), "r" (p2), "r" (p3));
}

void func_001883E0(void *p0, void *p1, void *p2, void *p3) {
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
	" :  : "r" (p0), "r" (p1), "r" (p2), "r" (p3));
}

void func_00188428(f32 *arg0, f32 *arg1) {
    arg0[0] = arg1[0];
    arg0[1] = arg1[1];
    arg0[2] = arg1[2];
}

void func_00188448(void *p0, void *p1, void *p2, float f0) {
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
	" :  : "r" (p0), "r" (p1), "r" (p2), "f" (f0));
}

void func_00188478(void *p0, void *p1, float f0) {
    __asm__ __volatile__("\n\
	lqc2	$vf4,0x0(%1)\n\
	.set noreorder\n\
	mfc1	$8,%2\n\
	qmtc2.ni	$8,$vf5\n\
	.set reorder\n\
	vmulx.xyz	$vf4,$vf4,$vf5x\n\
	sqc2	$vf4,0x0(%0)\n\
	" :  : "r" (p0), "r" (p1), "f" (f0));
}

int func_00188490(void *p0) {
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
	" : "=r" (ret) : "r" (p0));
    return ret;
}

int func_001884D8(void *p0, void *p1, void *p2) {
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
	" : "=r" (ret) : "r" (p0), "r" (p1), "r" (p2));
    return ret;
}

int func_00188538(void *p0, void *p1, void *p2, void *p3) {
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
	" : "=r" (ret) : "r" (p0), "r" (p1), "r" (p2), "r" (p3));
    return ret;
}

void func_001885C8(void) {
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

INCLUDE_ASM("asm/nonmatchings/main_028", func_00188630);

INCLUDE_ASM("asm/nonmatchings/main_028", func_00188880);

INCLUDE_ASM("asm/nonmatchings/main_028", func_00188F88);

INCLUDE_ASM("asm/nonmatchings/main_028", func_001893A8);

void func_001895C8(void *p0) {
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

void func_00189640(void *p0) {
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

void func_001896D8(void *p0) {
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

void func_00189790(void *p0) {
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

void func_00189860(void *p0) {
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

void func_00189910(void *p0) {
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

void func_001899C8(void *p0) {
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

void func_00189AC0(void *p0) {
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

void func_00189BC0(void *p0) {
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

void func_00189C60(void *p0) {
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

void func_00189D10(void *p0) {
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

void func_00189DF0(void *p0) {
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

void func_00189ED8(void *p0) {
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

void func_00189FB0(void *p0) {
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

void func_0018A080(void *p0) {
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

void func_0018A1A0(void *p0) {
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

void func_0018A2B8(void *p0, void *p1, void *p2) {
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

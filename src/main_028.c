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

INCLUDE_ASM("asm/nonmatchings/main_028", func_00187CA8);

INCLUDE_ASM("asm/nonmatchings/main_028", func_00187D50);

INCLUDE_ASM("asm/nonmatchings/main_028", func_00187DF8);

void func_00187EA0(s32 arg0, s32 arg1, void *arg2) {
    func_00187CA8((*(f32 *)((u8 *)arg2 + 8)));
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

INCLUDE_ASM("asm/nonmatchings/main_028", func_00187FC8);

void func_00188088(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_00187B90(arg0, arg1);
    func_00187B90(arg0 + 0x10, arg2);
    func_00187B90(arg0 + 0x20, arg3);
    func_00187B90(arg0 + 0x30, arg4);
}

INCLUDE_ASM("asm/nonmatchings/main_028", func_001880F0);

INCLUDE_ASM("asm/nonmatchings/main_028", func_001881F8);

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

INCLUDE_ASM("asm/nonmatchings/main_028", func_001885C8);

INCLUDE_ASM("asm/nonmatchings/main_028", func_00188630);

INCLUDE_ASM("asm/nonmatchings/main_028", func_00188880);

INCLUDE_ASM("asm/nonmatchings/main_028", func_00188F88);

INCLUDE_ASM("asm/nonmatchings/main_028", func_001893A8);

INCLUDE_ASM("asm/nonmatchings/main_028", func_001895C8);

INCLUDE_ASM("asm/nonmatchings/main_028", func_00189640);

INCLUDE_ASM("asm/nonmatchings/main_028", func_001896D8);

INCLUDE_ASM("asm/nonmatchings/main_028", func_00189790);

INCLUDE_ASM("asm/nonmatchings/main_028", func_00189860);

INCLUDE_ASM("asm/nonmatchings/main_028", func_00189910);

INCLUDE_ASM("asm/nonmatchings/main_028", func_001899C8);

INCLUDE_ASM("asm/nonmatchings/main_028", func_00189AC0);

INCLUDE_ASM("asm/nonmatchings/main_028", func_00189BC0);

INCLUDE_ASM("asm/nonmatchings/main_028", func_00189C60);

INCLUDE_ASM("asm/nonmatchings/main_028", func_00189D10);

INCLUDE_ASM("asm/nonmatchings/main_028", func_00189DF0);

INCLUDE_ASM("asm/nonmatchings/main_028", func_00189ED8);

INCLUDE_ASM("asm/nonmatchings/main_028", func_00189FB0);

INCLUDE_ASM("asm/nonmatchings/main_028", func_0018A080);

INCLUDE_ASM("asm/nonmatchings/main_028", func_0018A1A0);

INCLUDE_ASM("asm/nonmatchings/main_028", func_0018A2B8);

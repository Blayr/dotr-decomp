#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_027", func_00186D78);

INCLUDE_ASM("asm/nonmatchings/main_027", func_00186E58);

void func_00186FC8(void) {
    *(volatile s32 *)0x10003810 = 1;
    *(volatile s32 *)0x10003820 = 6;
}

s32 func_00186FF0(s32 arg0) {
    s32 r;

    r = func_001870C8();
    if (r == 0) {
        return 0;
    }
    if (r == 1) {
        return 0;
    }
    if (arg0 == 0) {
        *(volatile s32 *)0x10003810 = 2;
    } else if (arg0 == 1) {
        *(volatile s32 *)0x10003810 = 4;
    }
    return 1;
}

s32 func_00187058(void) {
    if (func_001870C8() != 1) {
        return 0;
    }
    *(volatile u32 *)0x10003810 = 8;
    return 1;
}

u32 func_00187098(u32 arg0, u32 arg1, u32 arg2) {
    u32 v = arg0 | (arg1 << 1) | (arg2 << 2);
    *(volatile u32 *)0x10003820 = v;
    return v;
}

s32 func_001870B8(void) {
    return *(volatile s32 *)0x10003820;
}

u32 func_001870C8(void) {
    s32 temp_a0;

    temp_a0 = *(volatile s32 *)0x10003800;
    if (!(temp_a0 & 3)) {
        return 0U;
    }
    if (temp_a0 & 0x700) {
        return 1U;
    }
    if (temp_a0 & 0xC) {
        return 2U;
    }
    return (temp_a0 & 0x3000) ? 3U : 4U;
}

s32 func_00187118(void *arg0) {
    u32 temp_s4;

    temp_s4 = *(volatile u32 *)0x10003840;
    if (func_001870C8() >= 2U) {
        return 0;
    }
    (*(s32 *)arg0) = (s32) *(volatile s32 *)0x10003900;
    (*(s32 *)((u8 *)arg0 + 4)) = (s32) *(volatile s32 *)0x10003910;
    (*(s32 *)((u8 *)arg0 + 8)) = (s32) *(volatile s32 *)0x10003920;
    (*(s32 *)((u8 *)arg0 + 0xC)) = (s32) *(volatile s32 *)0x10003930;
    (*(s32 *)((u8 *)arg0 + 0x10)) = (s32) *(volatile s32 *)0x10003940;
    (*(s32 *)((u8 *)arg0 + 0x14)) = (s32) *(volatile s32 *)0x10003950;
    (*(s32 *)((u8 *)arg0 + 0x18)) = (s32) *(volatile s32 *)0x10003960;
    (*(s32 *)((u8 *)arg0 + 0x1C)) = (s32) *(volatile s32 *)0x10003970;
    (*(s32 *)((u8 *)arg0 + 0x20)) = (s32) *(volatile s32 *)0x10003870;
    (*(s32 *)((u8 *)arg0 + 0x24)) = (s32) *(volatile s32 *)0x10003880;
    (*(s32 *)((u8 *)arg0 + 0x28)) = (s32) *(volatile s32 *)0x10003800;
    (*(s16 *)((u8 *)arg0 + 0x2C)) = (s16) *(volatile s32 *)0x100038D0;
    (*(s16 *)((u8 *)arg0 + 0x2E)) = (s16) *(volatile s32 *)0x10003890;
    (*(s16 *)((u8 *)arg0 + 0x30)) = (s16) *(volatile s32 *)0x10003830;
    (*(s16 *)((u8 *)arg0 + 0x32)) = (s16) *(volatile s32 *)0x10003860;
    (*(s8 *)((u8 *)arg0 + 0x34)) = (s8) *(volatile s32 *)0x10003820;
    (*(s8 *)((u8 *)arg0 + 0x35)) = (s8) temp_s4;
    (*(s8 *)((u8 *)arg0 + 0x36)) = (s8) (temp_s4 >> 8);
    (*(s8 *)((u8 *)arg0 + 0x37)) = (s8) *(volatile s32 *)0x10003850;
    return 1;
}

s32 func_00187298(__int128 *data, s32 n) {
    s32 i = 0;

    while (--n != -1) {
        if (*(volatile u32 *)0x10003800 & 0x10000000) {
            return i;
        }
        *(volatile __int128 *)0x10004000 = *data++;
        i++;
    }
    return i;
}

void func_001872F8(void *p0, u64 p1) {
    __asm__ __volatile__("\n\
	sw	%1,0x0(%0)\n\
	sw	$0,0x8(%0)\n\
	sw	%1,0x4(%0)\n\
	" :  : "r" (p0), "r" (p1));
}

void func_00187308(void *arg0) {
    (*(s32 *)((u8 *)arg0 + 8)) = 0;
    (*(s32 *)arg0) = (s32) (*(s32 *)((u8 *)arg0 + 4));
}

s32 func_00187318(void *arg0) {
    s32 *temp_a2;
    s32 var_a1;

    var_a1 = (*(s32 *)arg0);
    temp_a2 = (*(s32 **)((u8 *)arg0 + 8));
    if (var_a1 & 0xC) {
        do {
            *(s32 *)var_a1 = 0;
            var_a1 += 4;
        } while (var_a1 & 0xC);
    }
    if (temp_a2 != NULL) {
        s32 n = (((__int128 *)var_a1) - ((__int128 *)temp_a2)) - 1; *temp_a2 += n;
    }
    (*(s32 *)arg0) = var_a1;
    (*(s32 **)((u8 *)arg0 + 8)) = NULL;
    return var_a1;
}

void func_00187370(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    u32 *tag;
    s32 ret;

    ret = func_00187318(arg0);
    tag = *(u32 **)arg0;
    *(u32 **)((u8 *)arg0 + 8) = (u32 *)ret;
    *tag++ = arg3 | 0x10000000;
    tag[1] = arg1;
    *(u32 **)arg0 = tag + 3;
    tag[2] = arg2;
    tag[0] = 0;
}

void func_001873E8(void *arg0, s32 addr, s32 size, s32 a3, s32 a4, s32 a5) {
    u32 *tag;

    func_00187318(arg0);
    tag = *(u32 **)arg0;
    size |= 0x30000000;
    *tag++ = a5 | size;
    tag[0] = addr & 0x9FFFFFFF;
    tag[1] = a3;
    tag[2] = a4;
    *(u32 **)arg0 = tag + 3;
}

void func_00187480(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    u32 *tag;
    s32 ret;

    ret = func_00187318(arg0);
    tag = *(u32 **)arg0;
    *(u32 **)((u8 *)arg0 + 8) = (u32 *)ret;
    *tag++ = arg3 | 0x70000000;
    tag[1] = arg1;
    *(u32 **)arg0 = tag + 3;
    tag[2] = arg2;
    tag[0] = 0;
}

void *func_001874F8(void *p0, s32 p1) {
    u32 *cur = *(u32 **)p0;

    *(u32 **)p0 = cur + p1;
    return cur;
}

void func_00187510(s32 *arg0, __int128 arg1) {
    __int128 *p = (__int128 *) arg0[0];
    *p = arg1;
    arg0[3] = (s32) p;
    arg0[0] = (s32) (p + 1);
}

void func_00187528(void *arg0) {
    u64 *code = *(u64 **)((u8 *)arg0 + 0xC);
    s32 cur = *(s32 *)arg0;
    u64 v = *code;
    u32 n = ((cur - (s32)code) >> 3) - 2;
    u64 mode = (v >> 58) & 3;
    u32 d;
    s32 p;

    if (mode != 1) {
        n >>= 1;
    }
    if (mode != 2) {
        d = v >> 60;
        if (d == 0) {
            d = 16;
        }
        n = (n + d - 1) / d;
    }
    *(s32 *)((u8 *)arg0 + 0xC) = 0;
    *code = v + n;
    p = cur;
    if (p & 0xC) {
        do {
            *(s32 *)p = 0;
            p += 4;
        } while (p & 0xC);
    }
    *(s32 *)arg0 = p;
}

void func_001875D0(u64 **arg0, u32 arg1, u64 arg2) {
    u64 *p = *arg0;
    *p++ = arg2;
    *p++ = arg1;
    *arg0 = p;
}

void func_001875F8(s32 *arg0, s32 arg1) {
    arg0[1] = arg1;
    arg0[0] = arg1;
    arg0[2] = 0;
}

s32 func_00187608(void *arg0) {
    s32 *temp_a2;
    s32 var_a1;

    var_a1 = (*(s32 *)arg0);
    temp_a2 = (*(s32 **)((u8 *)arg0 + 8));
    if (var_a1 & 0xC) {
        do {
            *(s32 *)var_a1 = 0;
            var_a1 += 4;
        } while (var_a1 & 0xC);
    }
    if (temp_a2 != NULL) {
        s32 n = (((__int128 *)var_a1) - ((__int128 *)temp_a2)) - 1; *temp_a2 += n;
    }
    (*(s32 *)arg0) = var_a1;
    (*(s32 **)((u8 *)arg0 + 8)) = NULL;
    return var_a1;
}

void func_00187660(void *arg0, s32 arg1) {
    u32 *tag;
    s32 ret;

    ret = func_00187608(arg0);
    tag = *(u32 **)arg0;
    *(u32 **)((u8 *)arg0 + 8) = (u32 *)ret;
    *tag++ = arg1 | 0x10000000;
    *(s32 *)((u8 *)arg0 + 0xC) = 0;
    *(u32 **)arg0 = tag + 1;
    tag[0] = 0;
}

void func_001876B8(void *arg0, __int128 arg1) {
    __int128 *temp_v0;

    temp_v0 = (*(__int128 **)arg0);
    *temp_v0 = arg1;
    (*(__int128 **)((u8 *)arg0 + 0x14)) = temp_v0;
    (*(__int128 **)arg0) = (__int128 *) (temp_v0 + 1);
}

void func_001876D0(void *arg0) {
    u64 *code = *(u64 **)((u8 *)arg0 + 0x14);
    s32 cur = *(s32 *)arg0;
    u64 v = *code;
    u32 n = ((cur - (s32)code) >> 3) - 2;
    u64 mode = (v >> 58) & 3;
    u32 d;
    s32 p;

    if (mode != 1) {
        n >>= 1;
    }
    if (mode != 2) {
        d = v >> 60;
        if (d == 0) {
            d = 16;
        }
        n = (n + d - 1) / d;
    }
    *(s32 *)((u8 *)arg0 + 0x14) = 0;
    *code = v + n;
    p = cur;
    if (p & 0xC) {
        do {
            *(s32 *)p = 0;
            p += 4;
        } while (p & 0xC);
    }
    *(s32 *)arg0 = p;
}

INCLUDE_ASM("asm/nonmatchings/main_027", func_00187778);

void func_001877F8(s32 **arg0, s32 arg1) {
    *(*arg0)++ = arg1;
}

void func_00187810(s32 **arg0, s32 arg1) {
    *(*arg0)++ = arg1;
}

void func_00187828(void *arg0, s32 arg1, s64 arg2) {
    u32 *tag;

    tag = *(u32 **)arg0;
    *tag++ = (s32)arg2;
    tag[0] = arg2 >> 32;
    *(u32 **)arg0 = tag + 3;
    tag[1] = arg1;
    tag[2] = 0;
}

void func_00187858(void *arg0, s32 arg1) {
    s32 *temp_a1;

    func_00187778(arg0, 2, 3);
    temp_a1 = (*(s32 **)arg0);
    (*(s32 **)((u8 *)arg0 + 0xC)) = temp_a1;
    (*(s32 **)arg0) = (s32 *) (temp_a1 + 1);
    *temp_a1 = (arg1 != 0) ? 0xD1000000 : 0x51000000;
}

void func_001878B0(void *arg0) {
    u32 *tag;
    u32 *end;

    tag = *(u32 **)((u8 *)arg0 + 0xC);
    *(u32 **)((u8 *)arg0 + 0xC) = NULL;
    end = *(u32 **)arg0 - 1;
    *tag += (u32)(end - tag) >> 2;
}

void func_001878E0(void *p0, void *p1, void *p2) {
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
	sqc2	$vf9,0x0(%0)\n\
	" :  : "r" (p0), "r" (p1), "r" (p2));
}

void func_00187910(void *p0, void *p1, void *p2) {
    __asm__ __volatile__("\n\
	lqc2	$vf4,0x0(%1)\n\
	lqc2	$vf5,0x10(%1)\n\
	lqc2	$vf6,0x20(%1)\n\
	lqc2	$vf7,0x30(%1)\n\
	addiu	$7,$0,0x4\n\
_func_00187910_00187924:\n\
	lqc2	$vf8,0x0(%2)\n\
	vmulax.xyzw	$ACC,$vf4,$vf8x\n\
	vmadday.xyzw	$ACC,$vf5,$vf8y\n\
	vmaddaz.xyzw	$ACC,$vf6,$vf8z\n\
	vmaddw.xyzw	$vf9,$vf7,$vf8w\n\
	sqc2	$vf9,0x0(%0)\n\
	addi	$7,$7,-0x1\n\
	addi	%2,%2,0x10\n\
	addi	%0,%0,0x10\n\
	bne	$0,$7,_func_00187910_00187924\n\
	" :  : "r" (p0), "r" (p1), "r" (p2));
}

void func_00187958(void *p0, void *p1, void *p2) {
    __asm__ __volatile__("\n\
	lqc2	$vf4,0x0(%1)\n\
	lqc2	$vf5,0x0(%2)\n\
	vopmula.xyz	$ACC,$vf4,$vf5\n\
	vopmsub.xyz	$vf6,$vf5,$vf4\n\
	vsub.w	$vf6,$vf6,$vf6\n\
	sqc2	$vf6,0x0(%0)\n\
	" :  : "r" (p0), "r" (p1), "r" (p2));
}

float func_00187978(void *p0, void *p1) {
    float ret;
    __asm__ __volatile__("\n\
	lqc2	$vf4,0x0(%1)\n\
	lqc2	$vf5,0x0(%2)\n\
	vmul.xyz	$vf5,$vf4,$vf5\n\
	vaddy.x	$vf5,$vf5,$vf5y\n\
	vaddz.x	$vf5,$vf5,$vf5z\n\
	qmfc2.ni	$2,$vf5\n\
	mtc1	$2,%0\n\
	" : "=f" (ret) : "r" (p0), "r" (p1));
    return ret;
}

void func_001879A0(void *p0, void *p1) {
    __asm__ __volatile__("\n\
	lqc2	$vf4,0x0(%1)\n\
	vmul.xyz	$vf5,$vf4,$vf4\n\
	vaddy.x	$vf5,$vf5,$vf5y\n\
	vaddz.x	$vf5,$vf5,$vf5z\n\
	.word 0x4A0503BD\n\
	vwaitq\n\
	vaddq.x	$vf5,$vf0,$Q\n\
	vnop\n\
	vnop\n\
	vdiv	$Q,$vf0w,$vf5x\n\
	vsub.xyzw	$vf6,$vf0,$vf0\n\
	vwaitq\n\
	vmulq.xyz	$vf6,$vf4,$Q\n\
	sqc2	$vf6,0x0(%0)\n\
	" :  : "r" (p0), "r" (p1));
}

void func_001879E0(void *m0, void *m1) {
    __asm__ __volatile__("\n\
	lq $8,0x0000(%1)\n\
	lq $9,0x0010(%1)\n\
	lq $10,0x0020(%1)\n\
	lq $11,0x0030(%1)\n\
	pextlw     $12,$9,$8\n\
	pextuw     $13,$9,$8\n\
	pextlw     $14,$11,$10\n\
	pextuw     $15,$11,$10\n\
	pcpyld     $8,$14,$12\n\
	pcpyud     $9,$12,$14\n\
	pcpyld     $10,$15,$13\n\
	pcpyud     $11,$13,$15\n\
	sq $8,0x0000(%0)\n\
	sq $9,0x0010(%0)\n\
	sq $10,0x0020(%0)\n\
	sq $11,0x0030(%0)\n\
	" : : "r" (m0) , "r" (m1));
}

void func_00187A28(void *p0, void *p1) {
    __asm__ __volatile__("\n\
	lq	$8,0x0(%1)\n\
	lq	$9,0x10(%1)\n\
	lq	$10,0x20(%1)\n\
	lqc2	$vf4,0x30(%1)\n\
	vmove.xyzw	$vf5,$vf4\n\
	vsub.xyz	$vf4,$vf4,$vf4\n\
	vmove.xyzw	$vf9,$vf4\n\
	qmfc2.ni	$11,$vf4\n\
	pextlw	$12,$9,$8\n\
	pextuw	$13,$9,$8\n\
	pextlw	$14,$11,$10\n\
	pextuw	$15,$11,$10\n\
	pcpyld	$8,$14,$12\n\
	pcpyud	$9,$12,$14\n\
	pcpyld	$10,$15,$13\n\
	qmtc2.ni	$8,$vf6\n\
	qmtc2.ni	$9,$vf7\n\
	qmtc2.ni	$10,$vf8\n\
	vmulax.xyz	$ACC,$vf6,$vf5x\n\
	vmadday.xyz	$ACC,$vf7,$vf5y\n\
	vmaddz.xyz	$vf4,$vf8,$vf5z\n\
	vsub.xyz	$vf4,$vf9,$vf4\n\
	sq	$8,0x0(%0)\n\
	sq	$9,0x10(%0)\n\
	sq	$10,0x20(%0)\n\
	sqc2	$vf4,0x30(%0)\n\
	" :  : "r" (p0), "r" (p1));
}

void func_00187A98(void *p0, void *p1, float f0) {
    __asm__ __volatile__("\n\
	lqc2	$vf4,0x0(%1)\n\
	.set noreorder\n\
	mfc1	$8,%2\n\
	qmtc2.ni	$8,$vf5\n\
	.set reorder\n\
	vdiv	$Q,$vf0w,$vf5x\n\
	vwaitq\n\
	vmulq.xyzw	$vf4,$vf4,$Q\n\
	sqc2	$vf4,0x0(%0)\n\
	" :  : "r" (p0), "r" (p1), "f" (f0));
}

void func_00187AB8(void *p0, void *p1, float f0) {
    __asm__ __volatile__("\n\
	lqc2	$vf4,0x0(%1)\n\
	.set noreorder\n\
	mfc1	$8,%2\n\
	qmtc2.ni	$8,$vf5\n\
	.set reorder\n\
	vdiv	$Q,$vf0w,$vf5x\n\
	vwaitq\n\
	vmulq.xyz	$vf4,$vf4,$Q\n\
	sqc2	$vf4,0x0(%0)\n\
	" :  : "r" (p0), "r" (p1), "f" (f0));
}

void func_00187AD8(void *p0, void *p1, void *p2, float f0) {
    __asm__ __volatile__("\n\
	lqc2	$vf4,0x0(%1)\n\
	lqc2	$vf5,0x0(%2)\n\
	.set noreorder\n\
	mfc1	$8,%3\n\
	qmtc2.ni	$8,$vf6\n\
	.set reorder\n\
	vaddw.x	$vf7,$vf0,$vf0w\n\
	vsub.x	$vf8,$vf7,$vf6\n\
	vmulax.xyzw	$ACC,$vf4,$vf6x\n\
	vmaddx.xyzw	$vf9,$vf5,$vf8x\n\
	sqc2	$vf9,0x0(%0)\n\
	" :  : "r" (p0), "r" (p1), "r" (p2), "f" (f0));
}

void func_00187B00(void *v0, void *v1, void *v2) {
    __asm__ __volatile__("\n\
	lqc2    $vf4,0x0(%1)\n\
	lqc2    $vf5,0x0(%2)\n\
	vadd.xyzw	$vf6,$vf4,$vf5\n\
	sqc2    $vf6,0x0(%0)\n\
	" : : "r" (v0) , "r" (v1), "r" (v2));
}

void func_00187B18(void *v0, void *v1, void *v2) {
    __asm__ __volatile__("\n\
	lqc2    $vf4,0x0(%1)\n\
	lqc2    $vf5,0x0(%2)\n\
	.word 0x4BE521AC\n\
	sqc2    $vf6,0x0(%0)\n\
	" : : "r" (v0) , "r" (v1), "r" (v2));
}

void func_00187B30(void *p0, void *p1, void *p2) {
    __asm__ __volatile__("\n\
	lqc2	$vf4,0x0(%1)\n\
	lqc2	$vf5,0x0(%2)\n\
	vmul.xyzw	$vf6,$vf4,$vf5\n\
	sqc2	$vf6,0x0(%0)\n\
	" :  : "r" (p0), "r" (p1), "r" (p2));
}

void func_00187B48(void *p0, void *p1, float f0) {
    __asm__ __volatile__("\n\
	lqc2	$vf4,0x0(%1)\n\
	.set noreorder\n\
	mfc1	$8,%2\n\
	qmtc2.ni	$8,$vf5\n\
	.set reorder\n\
	vmulx.xyzw	$vf6,$vf4,$vf5x\n\
	sqc2	$vf6,0x0(%0)\n\
	" :  : "r" (p0), "r" (p1), "f" (f0));
}

void func_00187B60(void *p0, void *p1, void *p2) {
    __asm__ __volatile__("\n\
	lqc2	$vf4,0x0(%2)\n\
	lqc2	$vf5,0x30(%1)\n\
	lq	$7,0x0(%1)\n\
	lq	$8,0x10(%1)\n\
	lq	$9,0x20(%1)\n\
	vadd.xyz	$vf5,$vf5,$vf4\n\
	sq	$7,0x0(%0)\n\
	sq	$8,0x10(%0)\n\
	sq	$9,0x20(%0)\n\
	sqc2	$vf5,0x30(%0)\n\
	" :  : "r" (p0), "r" (p1), "r" (p2));
}

void func_00187B90(void *p0, void *p1) {
    __asm__ __volatile__("\n\
	lq	$6,0x0(%1)\n\
	sq	$6,0x0(%0)\n\
	" :  : "r" (p0), "r" (p1));
}

void func_00187BA0(void *m0, void *m1) {
    __asm__ __volatile__("\n\
	lq    $6,0x0(%1)\n\
	lq    $7,0x10(%1)\n\
	lq    $8,0x20(%1)\n\
	lq    $9,0x30(%1)\n\
	sq    $6,0x0(%0)\n\
	sq    $7,0x10(%0)\n\
	sq    $8,0x20(%0)\n\
	sq    $9,0x30(%0)\n\
	" : : "r" (m0) , "r" (m1));
}

void func_00187BC8(void *p0, void *p1) {
    __asm__ __volatile__("\n\
	lqc2	$vf4,0x0(%1)\n\
	vftoi4.xyzw	$vf5,$vf4\n\
	sqc2	$vf5,0x0(%0)\n\
	" :  : "r" (p0), "r" (p1));
}

void func_00187BD8(void *p0, void *p1) {
    __asm__ __volatile__("\n\
	lqc2	$vf4,0x0(%1)\n\
	vftoi0.xyzw	$vf5,$vf4\n\
	sqc2	$vf5,0x0(%0)\n\
	" :  : "r" (p0), "r" (p1));
}

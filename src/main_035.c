#include "common.h"
#include "sce/libc.h"

s32 func_0019AE78(double x) {
    s32 hx, lx;

    do { nl_dshape ew_u; ew_u.value = (x); (hx) = ew_u.parts.msw; (lx) = ew_u.parts.lsw; } while (0);
    hx &= 0x7fffffff;
    hx |= (u32)(lx | (-lx)) >> 31;
    hx = 0x7ff00000 - hx;
    return (s32)(((u32)(hx)) >> 31);
}

#define sb_EXTRACT_WORDS(ix0, ix1, d) \
    do { nl_dshape ew_u; ew_u.value = (d); (ix0) = ew_u.parts.msw; (ix1) = ew_u.parts.lsw; } while (0)
#define sb_GET_HIGH_WORD(i, d) \
    do { nl_dshape gh_u; gh_u.value = (d); (i) = gh_u.parts.msw; } while (0)
#define sb_SET_HIGH_WORD(d, v) \
    do { nl_dshape sh_u; sh_u.value = (d); sh_u.parts.msw = (v); (d) = sh_u.value; } while (0)

extern const double D_002BD3C8; /* tiny */
extern const double D_002BD3D0; /* huge */

double func_0019AEB8(double x, s32 n) {
    s32 k, hx, lx;
    sb_EXTRACT_WORDS(hx, lx, x);
    k = (hx & 0x7ff00000) >> 20;
    if (k == 0) {
        if ((lx | (hx & 0x7fffffff)) == 0)
            return x;
        x *= 1.80143985094819840000e+16;
        sb_GET_HIGH_WORD(hx, x);
        k = ((hx & 0x7ff00000) >> 20) - 54;
        if (n < -50000)
            return x * D_002BD3C8;
    }
    if (k == 0x7ff)
        return x + x;
    k = k + n;
    if (k > 0x7fe)
        return func_0019ADE8(D_002BD3D0, x) * D_002BD3D0;
    if (k > 0) {
        sb_SET_HIGH_WORD(x, (hx & 0x800fffff) | (k << 20));
        return x;
    }
    if (k <= -54) {
        if (n > 50000)
            return func_0019ADE8(D_002BD3D0, x) * D_002BD3D0;
        else
            return func_0019ADE8(D_002BD3C8, x) * D_002BD3C8;
    }
    k += 54;
    sb_SET_HIGH_WORD(x, (hx & 0x800fffff) | (k << 20));
    return x * 5.55111512312578270212e-17;
}

void *func_0019B0A0(s32 *ptr, s32 incr) {
    void *ret;
    D_003512F8 = 0;
    if ((ret = (void *)func_0017BFE0(incr)) == (void *)-1 && D_003512F8 != 0)
        *ptr = D_003512F8;
    return ret;
}

void func_0019B0F8(s32 arg0, s32 arg1, s32 arg2) {
    func_0019B148(D_0028FA98, arg0, arg1, arg2);
}

void func_0019B128(s32 arg0) {
    func_0019B418(D_0028FA98, arg0);
}

s32 func_0019B148(s32 reent_ptr, s32 name, s32 arg2, s32 rewrite) {
    const char *value = (const char *)arg2;
    char *C;
    s32 l_value;
    s32 offset;
    char *S;

    ((void (*)(s32))func_001966E8)(reent_ptr);
    if (*value == '=')
        ++value;
    l_value = func_0019BEF0(value);
    if ((C = (char *)func_00197570(reent_ptr, name, (s32)&offset))) {
        if (!rewrite) {
            ((void (*)(s32))func_001966F0)(reent_ptr);
            return 0;
        }
        if ((u32)func_0019BEF0(C) >= (u32)l_value) {
            while ((*C++ = *value++) != 0)
                ;
            ((void (*)(s32))func_001966F0)(reent_ptr);
            return 0;
        }
    } else {
        s32 cnt;
        char **P;

        for (P = *D_0028FF08, cnt = 0; *P; ++P, ++cnt)
            ;
        if (D_00317240) {
            if (!(*D_0028FF08 = (char **)func_0019A690((void *)reent_ptr, D_0028F79C, sizeof(char *) * (cnt + 2)))) {
                ((void (*)(s32))func_001966F0)(reent_ptr);
                return -1;
            }
        } else {
            D_00317240 = 1;
            P = (char **)func_00197EB8(reent_ptr, sizeof(char *) * (cnt + 2));
            if (!P) {
                ((void (*)(s32))func_001966F0)(reent_ptr);
                return -1;
            }
            ((void (*)(s32, s32, s32))func_001950E8)((s32)*D_0028FF08, (s32)P, cnt * sizeof(char *));
            *D_0028FF08 = P;
        }
        {
            char ***pe = D_0028FF08;
            offset = cnt;
            (*pe)[cnt + 1] = 0;
        }
    }
    for (C = (char *)name; *C && *C != '='; ++C)
        ;
    if (!((*D_0028FF08)[offset] = S = func_00197EB8(reent_ptr, (C - (char *)name) + l_value + 2))) {
        ((void (*)(s32))func_001966F0)(reent_ptr);
        return -1;
    }
    for (C = S; (*C = *(char *)name++) && *C != '='; ++C)
        ;
    for (*C++ = '='; (*C++ = *value++) != 0;)
        ;
    ((void (*)(s32))func_001966F0)(reent_ptr);
    return 0;
}

s32 func_0019B418(s32 reent_ptr, s32 name) {
    char **P;
    s32 offset;

    ((void (*)(s32))func_001966E8)(reent_ptr);
    while (func_00197570(reent_ptr, name, (s32)&offset))
        for (P = &(*D_0028FF08)[offset];; ++P)
            if (!(*P = *(P + 1)))
                break;
    ((void (*)(s32))func_001966F0)(reent_ptr);
}

f32 func_0019B4B8(f32 fparg0, f32 fparg1) {
    u32 gw0;
    u32 gw4;

    do { fshape gf_u; gf_u.value = (fparg0); (gw0) = gf_u.word; } while (0);
    do { fshape gf_u; gf_u.value = (fparg1); (gw4) = gf_u.word; } while (0);
    do { fshape sf_u; sf_u.word = (((gw0 & 0x7FFFFFFF) | (gw4 & 0x80000000))); (fparg0) = sf_u.value; } while (0);
    return fparg0;
}

f32 func_0019B4F8(f32 x, s32 n) {
    s32 k, ix;
    u32 hx;

    do { fshape gf_u; gf_u.value = (x); (ix) = gf_u.word; } while (0);
    hx = ix & 0x7fffffff;
    k = hx >> 23;
    if (hx < 0x00800000L)
        return x;
    if (!1)
        return x + x;
    if (0) {
        x *= (f32)33554434.0;
        do { fshape gf_u; gf_u.value = (x); (ix) = gf_u.word; } while (0);
        k = ((ix & 0x7f800000) >> 23) - 25;
        if (n < -50000) return (f32)0.0000000000000000000000000000010000000501908508838625516658847262427045785883927332161891232686912189819850027561187744140625 * x;
    }
    k = k + n;
    if (k > (0x7fffffffL >> 23)) return (f32)1000000052826398082833850564608.0 * func_0019B4B8((f32)1000000052826398082833850564608.0, x);
    if (k > 0) {
        do { fshape sf_u; sf_u.word = ((ix & 0x807fffff) | (k << 23)); (x) = sf_u.value; } while (0);
        return x;
    }
    if (k < 1) {
        if (n > 50000)
            return (f32)1000000052826398082833850564608.0 * func_0019B4B8((f32)1000000052826398082833850564608.0, x);
        else return (f32)0.0000000000000000000000000000010000000501908508838625516658847262427045785883927332161891232686912189819850027561187744140625 * func_0019B4B8((f32)0.0000000000000000000000000000010000000501908508838625516658847262427045785883927332161891232686912189819850027561187744140625, x);
    }
    k += 25;
    do { fshape sf_u; sf_u.word = ((ix & 0x807fffff) | (k << 23)); (x) = sf_u.value; } while (0);
    return x * (f32)0.0000000298023241640521519002504646778106689453125;
}

s32 func_0019B5C0(void *ptr, char *str, const char *fmt, ...) {
    s32 ret;
    __builtin_va_list ap;
    sprr_FILE f;

    f._flags = 0x0008 | 0x0200;
    f._bf_base = f._p = (u8 *)str;
    f._bf_size = f._w = 0x7fffffff;
    f._data = ptr;
    __builtin_stdarg_start(ap, fmt);
    ret = func_0019DD70((vf_FILE *)&f, fmt, ap);
    __builtin_va_end(ap);
    *f._p = 0;
    return ret;
}

s32 func_0019B648(char *str, const char *fmt, ...) {
    s32 ret;
    __builtin_va_list ap;
    spr_FILE f;

    f._flags = 0x0008 | 0x0200;
    f._bf_base = f._p = (u8 *)str;
    f._bf_size = f._w = 0x7fffffff;
    f._data = (void *)D_0028FA98;
    __builtin_stdarg_start(ap, fmt);
    ret = func_0019DD70((vf_FILE *)&f, fmt, ap);
    __builtin_va_end(ap);
    *f._p = 0;
    return ret;
}

s32 func_0019B6D8(void) {
    return 0;
}

s32 func_0019B6E0(const char *str, const char *fmt, ...) {
    s32 ret;
    __builtin_va_list ap;
    ssc_FILE f;

    f._flags = 0x0004;
    f._bf_base = f._p = (u8 *)str;
    f._bf_size = f._r = func_0019BEF0(str);
    f._read = (void *)func_0019B6D8;
    f._ub_base = NULL;
    f._lb_base = NULL;
    f._data = (void *)D_0028FA98;
    __builtin_stdarg_start(ap, fmt);
    ret = func_0019F6E8(&f, fmt, ap);
    __builtin_va_end(ap);
    return ret;
}

s32 func_0019B788(void *cookie, char *buf, s32 n) {
    sread_FILE *fp = (sread_FILE *)cookie;
    s32 ret;

    ret = func_0019A630(fp->_data, fp->_file, (s32)buf, n);
    if (ret >= 0)
        fp->_offset += ret;
    else
        fp->_flags &= ~0x1000;
    return ret;
}

s32 func_0019B7F0(void *arg0, s32 arg1, s32 arg2) {
    if ((*(u16 *)((u8 *)arg0 + 0xC)) & 0x100) {
        func_001977D8((*(s32 *)((u8 *)arg0 + 0x54)), (*(s16 *)((u8 *)arg0 + 0xE)), 0, 2);
    }
    (*(u16 *)((u8 *)arg0 + 0xC)) = (u16) ((*(s32 *)((u8 *)arg0 + 0xC)) & 0xEFFF);
    return func_001A0478((*(s32 *)((u8 *)arg0 + 0x54)), (*(s16 *)((u8 *)arg0 + 0xE)), arg1, arg2);
}

s64 func_0019B870(void *cookie, s64 offset, s32 whence) {
    sseek_FILE *fp = (sseek_FILE *)cookie;
    s64 ret;

    ret = ((s64 (*)(s32 *, s32, s64, s32))func_001977D8)(fp->_data, fp->_file, offset, whence);
    if (ret == -1L)
        fp->_flags &= ~0x1000;
    else {
        fp->_flags |= 0x1000;
        fp->_offset = ret;
    }
    return ret;
}

void func_0019B8D8(void *arg0) {
    func_001951F8((*(s32 *)((u8 *)arg0 + 0x54)), (*(s16 *)((u8 *)arg0 + 0xE)));
}

#define tolower_0019B8F8(c) ({ int __x = (c); ((D_002BD0C0 + 1)[(int)(__x)] & 01) ? (__x - 'A' + 'a') : __x; })

/* strcasecmp (newlib 1.9.0 strcasecmp.c): adapted from kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

s32 func_0019B8F8(const char *s1, const char *s2) {
    extern const char D_002BD0C0[];

    while (*s1 != '\0' && tolower_0019B8F8(*s1) == tolower_0019B8F8(*s2)) {
        s1++;
        s2++;
    }

    return tolower_0019B8F8(*(unsigned char *)s1) - tolower_0019B8F8(*(unsigned char *)s2);
}

#undef tolower_0019B8F8

/* strcat: newlib's hand-written r5900 assembly (libc/machine/r5900/strcat.S), kept as asm; identified via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

char *func_0019B9D0(char *dst, const char *src) {
    register char *ret __asm__("$2");

    __asm__ __volatile__(
        "	.set	noreorder\n"
        "	addiu	$29,$29,-0x20\n"
        "	sq	$16,0x0($29)\n"
        "	daddu	$16,$4,$0\n"
        "	andi	$2,$16,0x7\n"
        "	bnez	$2,_func_0019B9D0_0019BAC4\n"
        "	sq	$31,0x10($29)\n"
        "	andi	$2,$16,0xF\n"
        "	lui	$3,(0x1010101 >> 16)\n"
        "	ori	$3,$3,(0x1010101 & 0xFFFF)\n"
        "	dsll	$3,$3,16\n"
        "	ori	$3,$3,0x101\n"
        "	dsll	$3,$3,16\n"
        "	ori	$3,$3,0x101\n"
        "	lui	$4,(0x80808080 >> 16)\n"
        "	ori	$4,$4,(0x80808080 & 0xFFFF)\n"
        "	dsll	$4,$4,16\n"
        "	ori	$4,$4,0x8080\n"
        "	dsll	$4,$4,16\n"
        "	ori	$4,$4,0x8080\n"
        "	bnez	$2,_func_0019B9D0_0019BA80\n"
        "	ld	$6,0x0($16)\n"
        "	lq	$2,0x0($16)\n"
        "	pcpyld	$7,$3,$3\n"
        "	pcpyld	$8,$4,$4\n"
        "	psubb	$3,$2,$7\n"
        "	pnor	$2,$0,$2\n"
        "	pand	$3,$3,$2\n"
        "	pand	$3,$3,$8\n"
        "	pcpyud	$2,$3,$3\n"
        "	or	$3,$2,$3\n"
        "	bnez	$3,_func_0019B9D0_0019BAC4\n"
        "	daddu	$4,$16,$0\n"
        "	addiu	$6,$4,0x10\n"
        "_func_0019B9D0_0019BA54:\n"
        "	lq	$2,0x0($6)\n"
        "	pnor	$3,$0,$2\n"
        "	psubb	$2,$2,$7\n"
        "	pand	$2,$2,$3\n"
        "	pand	$2,$2,$8\n"
        "	pcpyud	$3,$2,$2\n"
        "	or	$2,$2,$3\n"
        "	beql	$2,$0,_func_0019B9D0_0019BA54\n"
        "	addiu	$6,$6,0x10\n"
        "	b	_func_0019B9D0_0019BAC4\n"
        "	daddu	$4,$6,$0\n"
        "_func_0019B9D0_0019BA80:\n"
        "	daddu	$7,$3,$0\n"
        "	daddu	$8,$4,$0\n"
        "	dsubu	$3,$6,$3\n"
        "	nor	$2,$0,$6\n"
        "	and	$3,$3,$2\n"
        "	and	$3,$3,$4\n"
        "	bnez	$3,_func_0019B9D0_0019BAC4\n"
        "	daddu	$4,$16,$0\n"
        "	addiu	$6,$16,0x8\n"
        "_func_0019B9D0_0019BAA4:\n"
        "	ld	$2,0x0($6)\n"
        "	nor	$3,$0,$2\n"
        "	dsubu	$2,$2,$7\n"
        "	and	$2,$2,$3\n"
        "	and	$2,$2,$8\n"
        "	beql	$2,$0,_func_0019B9D0_0019BAA4\n"
        "	addiu	$6,$6,0x8\n"
        "	daddu	$4,$6,$0\n"
        "_func_0019B9D0_0019BAC4:\n"
        "	lb	$2,0x0($4)\n"
        "	nop\n"
        "	nop\n"
        "	nop\n"
        "	nop\n"
        "	bnel	$2,$0,_func_0019B9D0_0019BAC4\n"
        "	addiu	$4,$4,0x1\n"
        "	jal	func_0019BDD8\n"
        "	nop\n"
        "	daddu	$2,$16,$0\n"
        "	lq	$31,0x10($29)\n"
        "	.set	reorder\n"
        "	lq	$16,0x0($29)\n"
        "	addiu	$29,$29,0x20\n"
        : "=r"(ret));
    return ret;
}

/* strchr: newlib's hand-written r5900 assembly (libc/machine/r5900/strchr.S), kept as asm; identified via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

char *func_0019BB00(char *s, s32 c) {
    register char *ret __asm__("$2");

    __asm__ __volatile__(
        "	.set	noreorder\n"
        "	andi	$2,$4,0x7\n"
        "	bnez	$2,_func_0019BB00_0019BC70\n"
        "	andi	$5,$5,0xFF\n"
        "	dsll	$3,$5,8\n"
        "	lui	$6,(0x1010101 >> 16)\n"
        "	ori	$6,$6,(0x1010101 & 0xFFFF)\n"
        "	dsll	$6,$6,16\n"
        "	ori	$6,$6,0x101\n"
        "	dsll	$6,$6,16\n"
        "	ori	$6,$6,0x101\n"
        "	daddu	$10,$3,$5\n"
        "	andi	$3,$4,0xF\n"
        "	dsll	$2,$10,16\n"
        "	lui	$8,(0x80808080 >> 16)\n"
        "	ori	$8,$8,(0x80808080 & 0xFFFF)\n"
        "	dsll	$8,$8,16\n"
        "	ori	$8,$8,0x8080\n"
        "	dsll	$8,$8,16\n"
        "	ori	$8,$8,0x8080\n"
        "	daddu	$2,$2,$10\n"
        "	dsll32	$10,$2,0\n"
        "	bnez	$3,_func_0019BB00_0019BBE8\n"
        "	daddu	$7,$2,$10\n"
        "_func_0019BB00_0019BB5C:\n"
        "	lq	$9,0x0($4)\n"
        "	pcpyld	$10,$6,$6\n"
        "	pnor	$3,$0,$9\n"
        "	psubb	$2,$9,$10\n"
        "	pcpyld	$6,$8,$8\n"
        "	pand	$2,$2,$3\n"
        "	pcpyld	$8,$7,$7\n"
        "	pand	$2,$2,$6\n"
        "	pcpyud	$3,$2,$7\n"
        "	or	$3,$2,$3\n"
        "	bnel	$3,$0,_func_0019BB00_0019BC74\n"
        "	lbu	$2,0x0($4)\n"
        "	pxor	$2,$9,$8\n"
        "	psubb	$3,$2,$10\n"
        "	pnor	$2,$0,$2\n"
        "	lui	$8,(0x80808080 >> 16)\n"
        "	ori	$8,$8,(0x80808080 & 0xFFFF)\n"
        "	dsll	$8,$8,16\n"
        "	ori	$8,$8,0x8080\n"
        "	dsll	$8,$8,16\n"
        "	ori	$8,$8,0x8080\n"
        "	pand	$3,$3,$2\n"
        "	pand	$3,$3,$6\n"
        "	lui	$6,(0x1010101 >> 16)\n"
        "	ori	$6,$6,(0x1010101 & 0xFFFF)\n"
        "	dsll	$6,$6,16\n"
        "	ori	$6,$6,0x101\n"
        "	dsll	$6,$6,16\n"
        "	ori	$6,$6,0x101\n"
        "	pcpyud	$2,$3,$5\n"
        "	or	$3,$2,$3\n"
        "	beql	$3,$0,_func_0019BB00_0019BB5C\n"
        "	addiu	$4,$4,0x10\n"
        "	b	_func_0019BB00_0019BC74\n"
        "	lbu	$2,0x0($4)\n"
        "_func_0019BB00_0019BBE8:\n"
        "	ld	$9,0x0($4)\n"
        "	nor	$3,$0,$9\n"
        "	dsubu	$2,$9,$6\n"
        "	and	$2,$2,$3\n"
        "	and	$2,$2,$8\n"
        "	bnel	$2,$0,_func_0019BB00_0019BC74\n"
        "	lbu	$2,0x0($4)\n"
        "	xor	$2,$9,$7\n"
        "	dsubu	$3,$2,$6\n"
        "	nor	$2,$0,$2\n"
        "	and	$3,$3,$2\n"
        "	and	$3,$3,$8\n"
        "	bnel	$3,$0,_func_0019BB00_0019BC74\n"
        "	lbu	$2,0x0($4)\n"
        "	daddu	$9,$6,$0\n"
        "	addiu	$4,$4,0x8\n"
        "_func_0019BB00_0019BC28:\n"
        "	ld	$6,0x0($4)\n"
        "	dsubu	$2,$6,$9\n"
        "	nor	$3,$0,$6\n"
        "	and	$2,$2,$3\n"
        "	and	$2,$2,$8\n"
        "	bnez	$2,_func_0019BB00_0019BC70\n"
        "	xor	$2,$6,$7\n"
        "	nor	$3,$0,$2\n"
        "	dsubu	$2,$2,$9\n"
        "	and	$2,$2,$3\n"
        "	and	$2,$2,$8\n"
        "	beql	$2,$0,_func_0019BB00_0019BC28\n"
        "	addiu	$4,$4,0x8\n"
        "	b	_func_0019BB00_0019BC74\n"
        "	lbu	$2,0x0($4)\n"
        "_func_0019BB00_0019BC64:\n"
        "	beql	$2,$5,_func_0019BB00_0019BC80\n"
        "	lbu	$3,0x0($4)\n"
        "	addiu	$4,$4,0x1\n"
        "_func_0019BB00_0019BC70:\n"
        "	lbu	$2,0x0($4)\n"
        "_func_0019BB00_0019BC74:\n"
        "	bnez	$2,_func_0019BB00_0019BC64\n"
        "	nop\n"
        "	lbu	$3,0x0($4)\n"
        "_func_0019BB00_0019BC80:\n"
        "	daddu	$2,$0,$0\n"
        "	.set	reorder\n"
        "	xor	$3,$3,$5\n"
        "	movz	$2,$4,$3\n"
        : "=r"(ret));
    return ret;
}

/* strcmp: newlib's hand-written r5900 assembly (libc/machine/r5900/strcmp.S), kept as asm; identified via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

s32 func_0019BC90(const char *a, const char *b) {
    register s32 ret __asm__("$2");

    __asm__ __volatile__(
        "	.set	noreorder\n"
        "	or	$8,$4,$5\n"
        "	andi	$2,$8,0x7\n"
        "	bnel	$2,$0,_func_0019BC90_0019BDC0\n"
        "	lb	$2,0x0($4)\n"
        "	andi	$9,$8,0xF\n"
        "	lui	$7,(0x1010101 >> 16)\n"
        "	ori	$7,$7,(0x1010101 & 0xFFFF)\n"
        "	dsll	$7,$7,16\n"
        "	ori	$7,$7,0x101\n"
        "	dsll	$7,$7,16\n"
        "	ori	$7,$7,0x101\n"
        "	lui	$6,(0x80808080 >> 16)\n"
        "	ori	$6,$6,(0x80808080 & 0xFFFF)\n"
        "	dsll	$6,$6,16\n"
        "	ori	$6,$6,0x8080\n"
        "	dsll	$6,$6,16\n"
        "	ori	$6,$6,0x8080\n"
        "	bnez	$9,_func_0019BC90_0019BD54\n"
        "	ld	$2,0x0($5)\n"
        "	lq	$3,0x0($4)\n"
        "	pcpyld	$8,$7,$7\n"
        "	lq	$2,0x0($5)\n"
        "	pcpyld	$10,$6,$6\n"
        "	psubw	$7,$2,$3\n"
        "	pcpyud	$6,$7,$4\n"
        "	or	$3,$6,$7\n"
        "	bnel	$3,$0,_func_0019BC90_0019BDC0\n"
        "	lb	$2,0x0($4)\n"
        "	lq	$2,0x0($4)\n"
        "	pnor	$3,$0,$2\n"
        "_func_0019BC90_0019BD08:\n"
        "	psubb	$2,$2,$8\n"
        "	pand	$2,$2,$3\n"
        "	pand	$2,$2,$10\n"
        "	pcpyud	$3,$2,$4\n"
        "	or	$6,$3,$2\n"
        "	beqz	$6,_func_0019BC90_0019BD2C\n"
        "	addiu	$4,$4,0x10\n"
        "	jr	$31\n"
        "	daddu	$2,$0,$0\n"
        "_func_0019BC90_0019BD2C:\n"
        "	addiu	$5,$5,0x10\n"
        "	lq	$2,0x0($4)\n"
        "	lq	$3,0x0($5)\n"
        "	psubw	$7,$2,$3\n"
        "	pcpyud	$6,$7,$4\n"
        "	or	$9,$6,$7\n"
        "	beql	$9,$0,_func_0019BC90_0019BD08\n"
        "	pnor	$3,$0,$2\n"
        "	b	_func_0019BC90_0019BDC0\n"
        "	lb	$2,0x0($4)\n"
        "_func_0019BC90_0019BD54:\n"
        "	ld	$3,0x0($4)\n"
        "	bnel	$3,$2,_func_0019BC90_0019BDC0\n"
        "	lb	$2,0x0($4)\n"
        "	ld	$2,0x0($4)\n"
        "	nor	$8,$0,$2\n"
        "_func_0019BC90_0019BD68:\n"
        "	dsubu	$2,$2,$7\n"
        "	and	$2,$2,$8\n"
        "	and	$2,$2,$6\n"
        "	beqz	$2,_func_0019BC90_0019BD84\n"
        "	addiu	$4,$4,0x8\n"
        "	jr	$31\n"
        "	daddu	$2,$0,$0\n"
        "_func_0019BC90_0019BD84:\n"
        "	addiu	$5,$5,0x8\n"
        "	ld	$2,0x0($4)\n"
        "	ld	$3,0x0($5)\n"
        "	beql	$3,$2,_func_0019BC90_0019BD68\n"
        "	nor	$8,$0,$2\n"
        "	b	_func_0019BC90_0019BDC0\n"
        "	lb	$2,0x0($4)\n"
        "_func_0019BC90_0019BDA0:\n"
        "	sll	$2,$3,24\n"
        "	lb	$3,0x0($5)\n"
        "	sra	$2,$2,24\n"
        "	bnel	$2,$3,_func_0019BC90_0019BDC8\n"
        "	lbu	$3,0x0($4)\n"
        "	addiu	$4,$4,0x1\n"
        "	addiu	$5,$5,0x1\n"
        "	lb	$2,0x0($4)\n"
        "_func_0019BC90_0019BDC0:\n"
        "	bnez	$2,_func_0019BC90_0019BDA0\n"
        "	lbu	$3,0x0($4)\n"
        "	.set	reorder\n"
        "_func_0019BC90_0019BDC8:\n"
        "	lbu	$2,0x0($5)\n"
        "	subu	$2,$3,$2\n"
        : "=r"(ret));
    return ret;
}

/* strcpy: newlib's hand-written r5900 assembly (libc/machine/r5900/strcpy.S), kept as asm; identified via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

char *func_0019BDD8(char *dst, const char *src) {
    register s32 r7 __asm__("$7");

    __asm__ __volatile__(
        "	.set	noreorder\n"
        "	daddu	$7,$4,$0\n"
        "	or	$8,$5,$7\n"
        "	andi	$2,$8,0x7\n"
        "	bnez	$2,_func_0019BDD8_0019BEC8\n"
        "	daddu	$3,$7,$0\n"
        "	andi	$2,$8,0xF\n"
        "	lui	$9,(0x1010101 >> 16)\n"
        "	ori	$9,$9,(0x1010101 & 0xFFFF)\n"
        "	dsll	$9,$9,16\n"
        "	ori	$9,$9,0x101\n"
        "	dsll	$9,$9,16\n"
        "	ori	$9,$9,0x101\n"
        "	lui	$4,(0x80808080 >> 16)\n"
        "	ori	$4,$4,(0x80808080 & 0xFFFF)\n"
        "	dsll	$4,$4,16\n"
        "	ori	$4,$4,0x8080\n"
        "	dsll	$4,$4,16\n"
        "	ori	$4,$4,0x8080\n"
        "	bnel	$2,$0,_func_0019BDD8_0019BE88\n"
        "	ld	$10,0x0($5)\n"
        "	pcpyld	$10,$9,$9\n"
        "	lq	$9,0x0($5)\n"
        "	pcpyld	$8,$4,$4\n"
        "	psubb	$2,$9,$10\n"
        "	pnor	$3,$0,$9\n"
        "	pand	$2,$2,$3\n"
        "	pand	$2,$2,$8\n"
        "	pcpyud	$4,$2,$9\n"
        "	or	$3,$2,$4\n"
        "	bnez	$3,_func_0019BDD8_0019BEC4\n"
        "	daddu	$6,$7,$0\n"
        "_func_0019BDD8_0019BE54:\n"
        "	sq	$9,0x0($6)\n"
        "	addiu	$5,$5,0x10\n"
        "	lq	$9,0x0($5)\n"
        "	psubb	$2,$9,$10\n"
        "	pnor	$3,$0,$9\n"
        "	pand	$2,$2,$3\n"
        "	pand	$2,$2,$8\n"
        "	pcpyud	$4,$2,$9\n"
        "	or	$3,$2,$4\n"
        "	beqz	$3,_func_0019BDD8_0019BE54\n"
        "	addiu	$6,$6,0x10\n"
        "	b	_func_0019BDD8_0019BEC8\n"
        "	daddu	$3,$6,$0\n"
        "_func_0019BDD8_0019BE88:\n"
        "	dsubu	$2,$10,$9\n"
        "	nor	$3,$0,$10\n"
        "	and	$2,$2,$3\n"
        "	and	$2,$2,$4\n"
        "	bnez	$2,_func_0019BDD8_0019BEC4\n"
        "	daddu	$6,$7,$0\n"
        "_func_0019BDD8_0019BEA0:\n"
        "	sd	$10,0x0($6)\n"
        "	addiu	$5,$5,0x8\n"
        "	ld	$10,0x0($5)\n"
        "	nor	$2,$0,$10\n"
        "	dsubu	$3,$10,$9\n"
        "	and	$3,$3,$2\n"
        "	and	$3,$3,$4\n"
        "	beqz	$3,_func_0019BDD8_0019BEA0\n"
        "	addiu	$6,$6,0x8\n"
        "_func_0019BDD8_0019BEC4:\n"
        "	daddu	$3,$6,$0\n"
        "_func_0019BDD8_0019BEC8:\n"
        "	lbu	$2,0x0($5)\n"
        "	addiu	$5,$5,0x1\n"
        "	sb	$2,0x0($3)\n"
        "	sll	$2,$2,24\n"
        "	addiu	$3,$3,0x1\n"
        "	bnez	$2,_func_0019BDD8_0019BEC8\n"
        "	nop\n"
        "	.set	reorder\n"
        : "=r"(r7));
    return (char *)r7;
}

/* strlen: newlib's hand-written r5900 assembly (libc/machine/r5900/strlen.S), kept as asm; identified via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

s32 func_0019BEF0(const char *s) {
    register s32 r4 __asm__("$4");
    register s32 r7 __asm__("$7");

    __asm__ __volatile__(
        "	.set	noreorder\n"
        "	andi	$2,$4,0x7\n"
        "	bnez	$2,_func_0019BEF0_0019C004\n"
        "	daddu	$7,$4,$0\n"
        "	andi	$3,$4,0xF\n"
        "	lui	$2,(0x1010101 >> 16)\n"
        "	ori	$2,$2,(0x1010101 & 0xFFFF)\n"
        "	dsll	$2,$2,16\n"
        "	ori	$2,$2,0x101\n"
        "	dsll	$2,$2,16\n"
        "	ori	$2,$2,0x101\n"
        "	bnez	$3,_func_0019BEF0_0019BF94\n"
        "	daddu	$5,$4,$0\n"
        "	lq	$3,0x0($5)\n"
        "	pcpyld	$8,$2,$2\n"
        "	lui	$4,(0x80808080 >> 16)\n"
        "	ori	$4,$4,(0x80808080 & 0xFFFF)\n"
        "	dsll	$4,$4,16\n"
        "	ori	$4,$4,0x8080\n"
        "	dsll	$4,$4,16\n"
        "	ori	$4,$4,0x8080\n"
        "	psubb	$2,$3,$8\n"
        "	pnor	$3,$0,$3\n"
        "	pcpyld	$9,$4,$4\n"
        "	pand	$2,$2,$3\n"
        "	pand	$2,$2,$9\n"
        "	pcpyud	$3,$2,$8\n"
        "	or	$6,$3,$2\n"
        "	bnel	$6,$0,_func_0019BEF0_0019C004\n"
        "	daddu	$4,$5,$0\n"
        "	addiu	$5,$5,0x10\n"
        "_func_0019BEF0_0019BF68:\n"
        "	lq	$2,0x0($5)\n"
        "	pnor	$3,$0,$2\n"
        "	psubb	$2,$2,$8\n"
        "	pand	$2,$2,$3\n"
        "	pand	$4,$2,$9\n"
        "	pcpyud	$3,$4,$6\n"
        "	or	$3,$3,$4\n"
        "	beql	$3,$0,_func_0019BEF0_0019BF68\n"
        "	addiu	$5,$5,0x10\n"
        "	b	_func_0019BEF0_0019C004\n"
        "	daddu	$4,$5,$0\n"
        "_func_0019BEF0_0019BF94:\n"
        "	ld	$3,0x0($5)\n"
        "	lui	$4,(0x80808080 >> 16)\n"
        "	ori	$4,$4,(0x80808080 & 0xFFFF)\n"
        "	dsll	$4,$4,16\n"
        "	ori	$4,$4,0x8080\n"
        "	dsll	$4,$4,16\n"
        "	ori	$4,$4,0x8080\n"
        "	dsubu	$2,$3,$2\n"
        "	nor	$3,$0,$3\n"
        "	and	$2,$2,$3\n"
        "	and	$2,$2,$4\n"
        "	bnel	$2,$0,_func_0019BEF0_0019C004\n"
        "	daddu	$4,$5,$0\n"
        "	lui	$6,(0x1010101 >> 16)\n"
        "	ori	$6,$6,(0x1010101 & 0xFFFF)\n"
        "	dsll	$6,$6,16\n"
        "	ori	$6,$6,0x101\n"
        "	dsll	$6,$6,16\n"
        "	ori	$6,$6,0x101\n"
        "	addiu	$5,$5,0x8\n"
        "_func_0019BEF0_0019BFE4:\n"
        "	ld	$2,0x0($5)\n"
        "	nor	$3,$0,$2\n"
        "	dsubu	$2,$2,$6\n"
        "	and	$2,$2,$3\n"
        "	and	$2,$2,$4\n"
        "	beql	$2,$0,_func_0019BEF0_0019BFE4\n"
        "	addiu	$5,$5,0x8\n"
        "	daddu	$4,$5,$0\n"
        "_func_0019BEF0_0019C004:\n"
        "	lb	$2,0x0($4)\n"
        "	nop\n"
        "	nop\n"
        "	nop\n"
        "	nop\n"
        "	bnel	$2,$0,_func_0019BEF0_0019C004\n"
        "	addiu	$4,$4,0x1\n"
        "	.set	reorder\n"
        : "=r"(r4), "=r"(r7));
    return r4 - r7;
}

#define tolower_0019C028(c) __extension__({ int __x = (c); ((D_002BD0C0 + 1)[(unsigned)(__x)] & 01) ? (__x - 'A' + 'a') : __x; })

/* strncasecmp (newlib 1.9.0 strncasecmp.c) via gt4-decomp (MIT, (c) Gustavo Canepa and gt4-decomp contributors; newlib notice in THIRD_PARTY_NOTICES.md) */

s32 func_0019C028(const char *s1, const char *s2, u32 n) {
    extern const char D_002BD0C0[];

    if (n == 0)
        return 0;

    while (n-- != 0 && tolower_0019C028(*s1) == tolower_0019C028(*s2)) {
        if (n == 0 || *s1 == '\0' || *s2 == '\0')
            break;
        s1++;
        s2++;
    }

    return tolower_0019C028(*(unsigned char *)s1) - tolower_0019C028(*(unsigned char *)s2);
}

#undef tolower_0019C028

/* strncmp: newlib's hand-written r5900 assembly (libc/machine/r5900/strncmp.S), kept as asm; identified via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

s32 func_0019C100(const char *a, const char *b, u32 n) {
    register s32 ret __asm__("$2");

    __asm__ __volatile__(
        "	.set	noreorder\n"
        "	bnez	$6,_func_0019C100_0019C110\n"
        "	or	$3,$4,$5\n"
        "_func_0019C100_0019C108:\n"
        "	jr	$31\n"
        "	daddu	$2,$0,$0\n"
        "_func_0019C100_0019C110:\n"
        "	andi	$2,$3,0x7\n"
        "	bnez	$2,_func_0019C100_0019C26C\n"
        "	daddu	$2,$6,$0\n"
        "	andi	$2,$3,0xF\n"
        "	sltiu	$7,$6,0x10\n"
        "	lui	$9,(0x1010101 >> 16)\n"
        "	ori	$9,$9,(0x1010101 & 0xFFFF)\n"
        "	dsll	$9,$9,16\n"
        "	ori	$9,$9,0x101\n"
        "	dsll	$9,$9,16\n"
        "	ori	$9,$9,0x101\n"
        "	or	$2,$2,$7\n"
        "	bnez	$2,_func_0019C100_0019C1E8\n"
        "	daddu	$7,$4,$0\n"
        "	lq	$3,0x0($4)\n"
        "	pcpyld	$10,$9,$9\n"
        "	lq	$2,0x0($5)\n"
        "	lui	$8,(0x80808080 >> 16)\n"
        "	ori	$8,$8,(0x80808080 & 0xFFFF)\n"
        "	dsll	$8,$8,16\n"
        "	ori	$8,$8,0x8080\n"
        "	dsll	$8,$8,16\n"
        "	ori	$8,$8,0x8080\n"
        "	psubw	$3,$3,$2\n"
        "	pcpyld	$9,$8,$8\n"
        "	pcpyud	$2,$3,$4\n"
        "	daddu	$8,$5,$0\n"
        "	or	$3,$2,$3\n"
        "	bnez	$3,_func_0019C100_0019C26C\n"
        "	daddu	$2,$6,$0\n"
        "	addiu	$6,$6,-0x10\n"
        "_func_0019C100_0019C18C:\n"
        "	beqz	$6,_func_0019C100_0019C108\n"
        "	nop\n"
        "	lq	$2,0x0($7)\n"
        "	pnor	$3,$0,$2\n"
        "	psubb	$2,$2,$10\n"
        "	pand	$2,$2,$3\n"
        "	pand	$3,$2,$9\n"
        "	pcpyud	$2,$3,$4\n"
        "	or	$2,$2,$3\n"
        "	bnez	$2,_func_0019C100_0019C108\n"
        "	addiu	$7,$7,0x10\n"
        "	sltiu	$2,$6,0x10\n"
        "	lq	$3,0x0($7)\n"
        "	bnez	$2,_func_0019C100_0019C260\n"
        "	addiu	$8,$8,0x10\n"
        "	lq	$2,0x0($8)\n"
        "	psubw	$3,$3,$2\n"
        "	pcpyud	$2,$3,$4\n"
        "	or	$2,$2,$3\n"
        "	beql	$2,$0,_func_0019C100_0019C18C\n"
        "	addiu	$6,$6,-0x10\n"
        "	b	_func_0019C100_0019C264\n"
        "	daddu	$4,$7,$0\n"
        "_func_0019C100_0019C1E8:\n"
        "	sltiu	$2,$6,0x8\n"
        "	bnez	$2,_func_0019C100_0019C260\n"
        "	daddu	$8,$5,$0\n"
        "	ld	$3,0x0($4)\n"
        "	ld	$2,0x0($5)\n"
        "	bne	$3,$2,_func_0019C100_0019C26C\n"
        "	daddu	$2,$6,$0\n"
        "	addiu	$6,$6,-0x8\n"
        "	lui	$10,(0x80808080 >> 16)\n"
        "	ori	$10,$10,(0x80808080 & 0xFFFF)\n"
        "	dsll	$10,$10,16\n"
        "	ori	$10,$10,0x8080\n"
        "	dsll	$10,$10,16\n"
        "	ori	$10,$10,0x8080\n"
        "_func_0019C100_0019C220:\n"
        "	beqz	$6,_func_0019C100_0019C108\n"
        "	nop\n"
        "	ld	$2,0x0($7)\n"
        "	nor	$3,$0,$2\n"
        "	dsubu	$2,$2,$9\n"
        "	and	$2,$2,$3\n"
        "	and	$2,$2,$10\n"
        "	bnez	$2,_func_0019C100_0019C108\n"
        "	addiu	$7,$7,0x8\n"
        "	sltiu	$2,$6,0x8\n"
        "	bnez	$2,_func_0019C100_0019C260\n"
        "	addiu	$8,$8,0x8\n"
        "	ld	$3,0x0($7)\n"
        "	ld	$2,0x0($8)\n"
        "	beql	$3,$2,_func_0019C100_0019C220\n"
        "	addiu	$6,$6,-0x8\n"
        "_func_0019C100_0019C260:\n"
        "	daddu	$4,$7,$0\n"
        "_func_0019C100_0019C264:\n"
        "	daddu	$5,$8,$0\n"
        "	daddu	$2,$6,$0\n"
        "_func_0019C100_0019C26C:\n"
        "	beqz	$2,_func_0019C100_0019C2A8\n"
        "	addiu	$6,$6,-0x1\n"
        "	b	_func_0019C100_0019C29C\n"
        "	lb	$3,0x0($4)\n"
        "	nop\n"
        "_func_0019C100_0019C280:\n"
        "	beqz	$6,_func_0019C100_0019C108\n"
        "	nop\n"
        "	beqz	$7,_func_0019C100_0019C108\n"
        "	addiu	$4,$4,0x1\n"
        "	addiu	$5,$5,0x1\n"
        "	lb	$3,0x0($4)\n"
        "	addiu	$6,$6,-0x1\n"
        "_func_0019C100_0019C29C:\n"
        "	lb	$2,0x0($5)\n"
        "	beq	$3,$2,_func_0019C100_0019C280\n"
        "	lbu	$7,0x0($4)\n"
        "_func_0019C100_0019C2A8:\n"
        "	lbu	$2,0x0($5)\n"
        "	.set	reorder\n"
        "	lbu	$3,0x0($4)\n"
        "	subu	$2,$3,$2\n"
        : "=r"(ret));
    return ret;
}

/* strncpy: newlib's hand-written r5900 assembly (libc/machine/r5900/strncpy.S), kept as asm; identified via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

void *func_0019C2B8(void *dst, const void *src, u32 n) {
    register s32 r8 __asm__("$8");

    __asm__ __volatile__(
        "	.set	noreorder\n"
        "	daddu	$8,$4,$0\n"
        "	or	$7,$5,$4\n"
        "	addiu	$10,$0,0x10\n"
        "	andi	$2,$7,0x7\n"
        "	addiu	$9,$0,0x8\n"
        "	bnez	$2,_func_0019C2B8_0019C420\n"
        "	andi	$2,$7,0xF\n"
        "	movz	$9,$10,$2\n"
        "	bnez	$2,_func_0019C2B8_0019C38C\n"
        "	sltu	$2,$6,$9\n"
        "	bnez	$2,_func_0019C2B8_0019C420\n"
        "	nop\n"
        "	lui	$7,(0x1010101 >> 16)\n"
        "	ori	$7,$7,(0x1010101 & 0xFFFF)\n"
        "	dsll	$7,$7,16\n"
        "	ori	$7,$7,0x101\n"
        "	dsll	$7,$7,16\n"
        "	ori	$7,$7,0x101\n"
        "	lq	$3,0x0($5)\n"
        "	pcpyld	$9,$7,$7\n"
        "	pnor	$3,$0,$3\n"
        "	lui	$7,(0x80808080 >> 16)\n"
        "	ori	$7,$7,(0x80808080 & 0xFFFF)\n"
        "	dsll	$7,$7,16\n"
        "	ori	$7,$7,0x8080\n"
        "	dsll	$7,$7,16\n"
        "	ori	$7,$7,0x8080\n"
        "	psubb	$2,$3,$9\n"
        "	pcpyld	$10,$7,$7\n"
        "	pand	$2,$2,$3\n"
        "	pand	$2,$2,$10\n"
        "	pcpyud	$3,$2,$4\n"
        "	or	$3,$2,$3\n"
        "	bnez	$3,_func_0019C2B8_0019C41C\n"
        "	daddu	$7,$8,$0\n"
        "	lq	$3,0x0($5)\n"
        "	addiu	$6,$6,-0x10\n"
        "	addiu	$5,$5,0x10\n"
        "	sltiu	$2,$6,0x10\n"
        "	sq	$3,0x0($7)\n"
        "	bnez	$2,_func_0019C2B8_0019C41C\n"
        "	addiu	$7,$7,0x10\n"
        "	lq	$2,0x0($5)\n"
        "	pnor	$3,$0,$2\n"
        "	psubb	$2,$2,$9\n"
        "	pand	$2,$2,$3\n"
        "	pand	$2,$2,$10\n"
        "	pcpyud	$3,$2,$4\n"
        "	or	$2,$2,$3\n"
        "	beql	$2,$0,_func_0019C2B8_0019C3E8\n"
        "	lq	$3,0x0($5)\n"
        "	b	_func_0019C2B8_0019C420\n"
        "	daddu	$4,$7,$0\n"
        "_func_0019C2B8_0019C38C:\n"
        "	bnez	$2,_func_0019C2B8_0019C420\n"
        "	nop\n"
        "	ld	$3,0x0($5)\n"
        "	lui	$9,(0x1010101 >> 16)\n"
        "	ori	$9,$9,(0x1010101 & 0xFFFF)\n"
        "	dsll	$9,$9,16\n"
        "	ori	$9,$9,0x101\n"
        "	dsll	$9,$9,16\n"
        "	ori	$9,$9,0x101\n"
        "	lui	$10,(0x80808080 >> 16)\n"
        "	ori	$10,$10,(0x80808080 & 0xFFFF)\n"
        "	dsll	$10,$10,16\n"
        "	ori	$10,$10,0x8080\n"
        "	dsll	$10,$10,16\n"
        "	ori	$10,$10,0x8080\n"
        "	dsubu	$2,$3,$9\n"
        "	nor	$3,$0,$3\n"
        "	and	$2,$2,$3\n"
        "	and	$2,$2,$10\n"
        "	bnez	$2,_func_0019C2B8_0019C41C\n"
        "	daddu	$7,$8,$0\n"
        "	ld	$3,0x0($5)\n"
        "	nop\n"
        "_func_0019C2B8_0019C3E8:\n"
        "	addiu	$6,$6,-0x8\n"
        "	addiu	$5,$5,0x8\n"
        "	sltiu	$2,$6,0x8\n"
        "	sd	$3,0x0($7)\n"
        "	bnez	$2,_func_0019C2B8_0019C41C\n"
        "	addiu	$7,$7,0x8\n"
        "	ld	$2,0x0($5)\n"
        "	nor	$3,$0,$2\n"
        "	dsubu	$2,$2,$9\n"
        "	and	$2,$2,$3\n"
        "	and	$2,$2,$10\n"
        "	beql	$2,$0,_func_0019C2B8_0019C3E8\n"
        "	ld	$3,0x0($5)\n"
        "_func_0019C2B8_0019C41C:\n"
        "	daddu	$4,$7,$0\n"
        "_func_0019C2B8_0019C420:\n"
        "	beqz	$6,_func_0019C2B8_0019C46C\n"
        "	daddu	$2,$6,$0\n"
        "	lbu	$2,0x0($5)\n"
        "	addiu	$6,$6,-0x1\n"
        "	addiu	$5,$5,0x1\n"
        "	sb	$2,0x0($4)\n"
        "	sll	$2,$2,24\n"
        "	bnez	$2,_func_0019C2B8_0019C420\n"
        "	addiu	$4,$4,0x1\n"
        "	daddu	$2,$6,$0\n"
        "	beqz	$2,_func_0019C2B8_0019C46C\n"
        "	addiu	$6,$6,-0x1\n"
        "_func_0019C2B8_0019C450:\n"
        "	sb	$0,0x0($4)\n"
        "	daddu	$2,$6,$0\n"
        "	addiu	$4,$4,0x1\n"
        "	addiu	$6,$6,-0x1\n"
        "	nop\n"
        "	bnez	$2,_func_0019C2B8_0019C450\n"
        "	nop\n"
        "_func_0019C2B8_0019C46C:\n"
        "	.set	reorder\n"
        : "=r"(r8));
    return (void *)r8;
}

char *func_0019C478(const char *s, s32 i) {
    const char *last = NULL;
    char c = i;

    while (*s) {
        if (*s == c)
            last = s;
        s++;
    }
    if (*s == c)
        last = s;
    return (char *)last;
}

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019C4C8);

void func_0019D3E0(s32 arg0, s32 arg1) {
    func_0019C4C8(D_0028FA98, arg0, arg1);
}

f32 func_0019D408(s32 s, s32 ptr) {
    return ((double (*)(s32, s32))func_0019D3E0)(s, ptr);
}

char *func_0019D430(char *s, const char *delim) {
    return func_0019D450(s, delim, (char **)(D_0028FA98 + 0x5C));
}

char *func_0019D450(char *s, const char *delim, char **lasts) {
    char *spanp;
    s32 c, sc;
    char *tok;

    if (s == NULL && (s = *lasts) == NULL)
        return NULL;

cont:
    c = *s++;
    for (spanp = (char *)delim; (sc = *spanp++) != 0;) {
        if (c == sc)
            goto cont;
    }

    if (c == 0) {
        *lasts = NULL;
        return NULL;
    }
    tok = s - 1;

    for (;;) {
        c = *s++;
        spanp = (char *)delim;
        do {
            if ((sc = *spanp++) == c) {
                if (c == 0)
                    s = NULL;
                else
                    s[-1] = 0;
                *lasts = s;
                return tok;
            }
        } while (sc != 0);
    }
}

long func_0019D518(s32 rptr, const char *nptr, char **endptr, s32 base) {
    register const char *s = nptr;
    register u64 acc;
    register s32 c;
    register u64 cutoff;
    register s32 neg = 0, any, cutlim;

    do {
        c = *s++;
    } while ((D_002BD0C0 + 1)[(u32)c] & 8);
    if (c == '-') {
        neg = 1;
        c = *s++;
    } else if (c == '+')
        c = *s++;
    if ((base == 0 || base == 16) && c == '0' && (*s == 'x' || *s == 'X')) {
        c = s[1];
        s += 2;
        base = 16;
    }
    if (base == 0)
        base = c == '0' ? 8 : 10;
    cutoff = neg ? -(u64)(-0x7FFFFFFFFFFFFFFF - 1) : 0x7FFFFFFFFFFFFFFF;
    cutlim = cutoff % (u64)base;
    cutoff /= (u64)base;
    for (acc = 0, any = 0;; c = *s++) {
        if ((D_002BD0C0 + 1)[(u32)c] & 4)
            c -= '0';
        else if ((D_002BD0C0 + 1)[(u32)c] & 3)
            c -= ((D_002BD0C0 + 1)[(u32)c] & 1) ? 'A' - 10 : 'a' - 10;
        else
            break;
        if (c >= base)
            break;
        if (any < 0 || acc > cutoff || (acc == cutoff && c > cutlim))
            any = -1;
        else {
            any = 1;
            acc *= base;
            acc += c;
        }
    }
    if (any < 0) {
        acc = neg ? (-0x7FFFFFFFFFFFFFFF - 1) : 0x7FFFFFFFFFFFFFFF;
        ((sl_reent *)rptr)->_errno = 34;
    } else if (neg)
        acc = -acc;
    if (endptr != 0)
        *endptr = (char *)(any ? s - 1 : nptr);
    return acc;
}

long func_0019D750(const char *arg0, char **arg1, s32 arg2) {
    return func_0019D518(D_0028FA98, arg0, arg1, arg2);
}

u64 func_0019D780(s32 rptr, const char *nptr, char **endptr, s32 base) {
    register const char *s = nptr;
    register u64 acc;
    register s32 c;
    register u64 cutoff;
    register s32 neg = 0, any, cutlim;

    do {
        c = *s++;
    } while ((D_002BD0C0 + 1)[(u32)c] & 8);
    if (c == '-') {
        neg = 1;
        c = *s++;
    } else if (c == '+')
        c = *s++;
    if ((base == 0 || base == 16) && c == '0' && (*s == 'x' || *s == 'X')) {
        c = s[1];
        s += 2;
        base = 16;
    }
    if (base == 0)
        base = c == '0' ? 8 : 10;
    cutoff = (u64)0xFFFFFFFFFFFFFFFF / (u64)base;
    cutlim = (u64)0xFFFFFFFFFFFFFFFF % (u64)base;
    for (acc = 0, any = 0;; c = *s++) {
        if ((D_002BD0C0 + 1)[(u32)c] & 4)
            c -= '0';
        else if ((D_002BD0C0 + 1)[(u32)c] & 3)
            c -= ((D_002BD0C0 + 1)[(u32)c] & 1) ? 'A' - 10 : 'a' - 10;
        else
            break;
        if (c >= base)
            break;
        if (any < 0 || acc > cutoff || (acc == cutoff && c > cutlim))
            any = -1;
        else {
            any = 1;
            acc *= base;
            acc += c;
        }
    }
    if (any < 0) {
        acc = 0xFFFFFFFFFFFFFFFF;
        ((su_reent *)rptr)->_errno = 34;
    } else if (neg)
        acc = -acc;
    if (endptr != 0)
        *endptr = (char *)(any ? s - 1 : nptr);
    return acc;
}

void func_0019D9B0(s32 arg0, s32 arg1, s32 arg2) {
    func_0019D780(D_0028FA98, arg0, arg1, arg2);
}

s32 func_0019D9E0(s32 c) {
    return (D_002BD0C1[(u32)c] & 2) ? c - 'a' + 'A' : c;
}

typedef struct sm_buf { u8 *_base; s32 _size; } sm_buf;
typedef struct sm_FILE {
    u8 *_p;
    u8 pad04[0x2C];
    sm_buf _ub;
    u8 pad38[0x8];
    u8 _ubuf[3];
    u8 pad43[0x11];
    void *_data;
} sm_FILE;
void *func_0019A690(void *ptr, void *old, s32 size);

s32 func_0019DA00(void *arg0) {
    sm_FILE *fp = arg0;
    s32 i;
    u8 *p;

    if (fp->_ub._base == fp->_ubuf) {
        if ((p = (u8 *)func_00197EB8((s32)fp->_data, 1024)) == NULL)
            return -1;
        fp->_ub._base = p;
        fp->_ub._size = 1024;
        p += 1024 - sizeof(fp->_ubuf);
        for (i = sizeof(fp->_ubuf); --i >= 0;)
            p[i] = fp->_ubuf[i];
        fp->_p = p;
        return 0;
    }
    i = fp->_ub._size;
    p = (u8 *)func_0019A690(fp->_data, fp->_ub._base, i << 1);
    if (p == NULL)
        return -1;
    func_00198790(p + i, p, i);
    fp->_p = p + i;
    fp->_ub._base = p;
    fp->_ub._size = i << 1;
    return 0;
}

typedef struct ug_reent { u8 pad0[0x38]; s32 __sdidinit; } ug_reent;
typedef struct ug_sbuf { u8 *_base; s32 _size; } ug_sbuf;
typedef struct ug_FILE {
    u8 *_p;
    s32 _r;
    s32 _w;
    s16 _flags;
    s16 _file;
    ug_sbuf _bf;
    s32 _lbfsize;
    void *_cookie;
    void *_read;
    void *_write;
    void *_seek;
    void *_close;
    ug_sbuf _ub;
    u8 *_up;
    s32 _ur;
    u8 _ubuf[3];
    u8 _nbuf[1];
    ug_sbuf _lb;
    s32 _blksize;
    s32 _offset;
    ug_reent *_data;
} ug_FILE;

s32 func_0019DAE8(s32 c, void *arg1) {
    ug_FILE *fp = arg1;

    if (c == -1)
        return -1;

    do {
        if (fp->_data == 0)
            fp->_data = (ug_reent *)D_0028FA98;
        if (!fp->_data->__sdidinit)
            func_00196A30(fp->_data);
    } while (0);

    fp->_flags &= ~0x20;

    if ((fp->_flags & 4) == 0) {
        if ((fp->_flags & 0x10) == 0)
            return -1;
        if (fp->_flags & 8) {
            if (func_00196708((nl_FILE *)fp))
                return -1;
            fp->_flags &= ~8;
            fp->_w = 0;
            fp->_lbfsize = 0;
        }
        fp->_flags |= 4;
    }
    c = (u8)c;

    if (fp->_ub._base != NULL) {
        if (fp->_r >= fp->_ub._size && func_0019DA00(fp))
            return -1;
        *--fp->_p = c;
        fp->_r++;
        return c;
    }

    if (fp->_bf._base != NULL && fp->_p > fp->_bf._base && fp->_p[-1] == c) {
        fp->_p--;
        fp->_r++;
        return c;
    }

    fp->_ur = fp->_r;
    fp->_up = fp->_p;
    fp->_ub._base = fp->_ubuf;
    fp->_ub._size = sizeof(fp->_ubuf);
    fp->_ubuf[sizeof(fp->_ubuf) - 1] = c;
    fp->_p = &fp->_ubuf[sizeof(fp->_ubuf) - 1];
    fp->_r = 1;
    return c;
}

s32 func_0019DC70(s32 arg0, void *arg1) {
    s32 temp_v0;

    if ((*(s32 *)((u8 *)arg1 + 8)) == 0) {
        (*(s32 *)((u8 *)arg1 + 4)) = 0;
        return 0;
    }
    temp_v0 = func_001970A8(arg0, arg1);
    (*(s32 *)((u8 *)arg1 + 8)) = 0;
    (*(s32 *)((u8 *)arg1 + 4)) = 0;
    return temp_v0;
}

#define fp_0019DCB8 ((Fil *)arg0)

/* __sbprintf (newlib 1.9.0 vfprintf.c): adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

s32 func_0019DCB8(void *arg0, const char *fmt, void *ap) {
    s32 ret;
    Fil fake;
    u8 buf[1024];

    fake.data = fp_0019DCB8->data;
    fake.flags = fp_0019DCB8->flags & ~0x0002;
    fake.file = fp_0019DCB8->file;
    fake.cookie = fp_0019DCB8->cookie;
    fake.write = fp_0019DCB8->write;

    fake.bf.base = fake.p = buf;
    fake.bf.size = fake.w = sizeof(buf);
    fake.lbfsize = 0;

    ret = func_0019DD70((vf_FILE *)&fake, fmt, ap);
    if (ret >= 0 && func_00196708((nl_FILE *)&fake))
        ret = -1;
    if (fake.flags & 0x0040)
        fp_0019DCB8->flags |= 0x0040;
    return ret;
}

#undef fp_0019DCB8

s32 func_0019DD70(vf_FILE *fp, const char *fmt0, void *ap) {
    do {
        if ((fp)->_data == 0)
            (fp)->_data = (vf_reent *)D_0028FA98;
        if (!(fp)->_data->__sdidinit)
            func_00196A30((fp)->_data);
    } while (0);
    return func_0019DDE8(fp->_data, fp, fmt0, ap);
}

INCLUDE_ASM("asm/nonmatchings/main_035", func_0019DDE8);

char *func_0019F448(void *data, double value, s32 ndigits, s32 flags, char *sign, s32 *decpt, s32 ch,
                    s32 *length) {
    extern char *func_00195480(void *, double, s32, s32, s32 *, s32 *, char **);
    s32 mode, dsgn;
    char *digits, *bp, *rve;
    cvt_du tmp;

    if (ch == 'f') {
        mode = 3;
    } else {
        if (ch == 'e' || ch == 'E') {
            ndigits++;
        }
        mode = 2;
    }

    tmp.d = value;
    if (tmp.i[1] & 0x80000000) {
        value = -value;
        *sign = '-';
    } else
        *sign = '\000';
    digits = func_00195480(data, value, mode, ndigits, decpt, &dsgn, &rve);
    if ((ch != 'g' && ch != 'G') || flags & 1) {
        bp = digits + ndigits;
        if (ch == 'f') {
            if (*digits == '0' && value)
                *decpt = -ndigits + 1;
            bp += *decpt;
        }
        if (value == 0)
            rve = bp;
        while (rve < bp)
            *rve++ = '0';
    }
    *length = rve - digits;
    return (digits);
}

s32 func_0019F608(char *p0, s32 exp, s32 fmtch) {
    char *p, *t;
    char expbuf[308];

    p = p0;
    *p++ = fmtch;
    if (exp < 0) {
        exp = -exp;
        *p++ = '-';
    } else
        *p++ = '+';
    t = expbuf + 308;
    if (exp > 9) {
        do {
            *--t = (exp % 10) + '0';
        } while ((exp /= 10) > 9);
        *--t = exp + '0';
        for (; t < expbuf + 308; *p++ = *t++);
    } else {
        *p++ = '0';
        *p++ = exp + '0';
    }
    return p - p0;
}

/* __svfscanf: newlib 1.9.0 stdio/vfscanf.c ((c) 1990 The Regents of the University of California,
   developed by the University of California, Berkeley), see THIRD_PARTY_NOTICES.md */

#define __sbuf __sbuf_0019F6E8
#define __sFILE __sFILE_0019F6E8
#define FILE FILE_0019F6E8
#define _fpos_t _fpos_t_0019F6E8
struct __sbuf {
    unsigned char *_base;
    int _size;
};
typedef long _fpos_t;
struct __sFILE {
    unsigned char *_p;
    int _r;
    int _w;
    short _flags;
    short _file;
    struct __sbuf _bf;
    int _lbfsize;
    void *_cookie;
    int (*_read)(void *_cookie, char *_buf, int _n);
    int (*_write)(void *_cookie, const char *_buf, int _n);
    _fpos_t (*_seek)(void *_cookie, _fpos_t _offset, int _whence);
    int (*_close)(void *_cookie);
    struct __sbuf _ub;
    unsigned char *_up;
    int _ur;
    unsigned char _ubuf[3];
    unsigned char _nbuf[1];
    struct __sbuf _lb;
    int _blksize;
    int _offset;
    void *_data;
};
typedef struct __sFILE FILE;
typedef unsigned int size_t_0019F6E8;
#define size_t size_t_0019F6E8
#define wchar_t int

extern const short D_002BD6C0[]; /* basefix */
extern const char D_002BD6E8[]; /* "e%ld" */
#define basefix D_002BD6C0
#define _ctype_ (D_002BD0C1 - 1)
#define __srefill(fp) func_0019AC68(fp)
#define ungetc(c, fp) func_0019DAE8(c, fp)
#define __sccl(tab, fmt) func_001A0378(tab, fmt)
#define sprintf func_0019B648
#define strtol func_0019D750
#define strtoul func_0019D9B0
#define fread(b, s, n, fp) func_00196AC0(b, s, n, fp)
#define atol(s) ((long (*)(const char *))func_001950C8)(s)
#define atof(s) ((double (*)(const char *))func_00195088)(s)
#define fp ((FILE *)fp_0019F6E8)

s32 func_0019F6E8(void *fp_0019F6E8, const char *fmt0, void *ap0)
{
  __builtin_va_list ap = ap0;
  register char *fmt = (char *) fmt0;
  register int c;
  register size_t width;
  register char *p;
  register int n;
  register int flags;
  register char *p0;
  int nassigned;
  int nread;
  int base = 0;
  int nbytes = 1;
  wchar_t wc;
  unsigned long (*ccfn) () = 0;
  char ccltab[256];
  char buf[(308+39+3)];
  char *lptr;
  short *sp;
  int *ip;
  float *flp;
  long double *ldp;
  double *dp;
  long *lp;
  nassigned = 0;
  nread = 0;
  for (;;)
    {
      wc = *fmt;
      fmt += nbytes;
      if (wc == 0)
        return nassigned;
      if (nbytes == 1 && ((_ctype_+1)[(unsigned)(wc)]&010))
        {
          for (;;)
            {
              if ((fp->_r <= 0 && __srefill(fp)))
                return nassigned;
              if (!((_ctype_+1)[(unsigned)(*fp->_p)]&010))
                break;
              nread++, fp->_r--, fp->_p++;
            }
          continue;
        }
      if (wc != '%')
        goto literal;
      width = 0;
      flags = 0;
    again:
      c = *fmt++;
      switch (c)
        {
        case '%':
        literal:
          lptr = fmt - nbytes;
          for (n = 0; n < nbytes; ++n)
            {
              if ((fp->_r <= 0 && __srefill(fp)))
                goto input_failure;
              if (*fp->_p != *lptr)
                goto match_failure;
              fp->_r--, fp->_p++;
              nread++;
              ++lptr;
            }
          continue;
        case '*':
          flags |= 0x08;
          goto again;
        case 'l':
          flags |= 0x01;
          goto again;
        case 'L':
          flags |= 0x02;
          goto again;
        case 'h':
          flags |= 0x04;
          goto again;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
          width = width * 10 + c - '0';
          goto again;
        case 'D':
          flags |= 0x01;
        case 'd':
          c = 3;
          ccfn = (unsigned long (*)())strtol;
          base = 10;
          break;
        case 'i':
          c = 3;
          ccfn = (unsigned long (*)())strtol;
          base = 0;
          break;
        case 'O':
          flags |= 0x01;
        case 'o':
          c = 3;
          ccfn = strtoul;
          base = 8;
          break;
        case 'u':
          c = 3;
          ccfn = strtoul;
          base = 10;
          break;
        case 'X':
        case 'x':
          flags |= 0x100;
          c = 3;
          ccfn = strtoul;
          base = 16;
          break;
        case 'E':
        case 'G':
        case 'e':
        case 'f':
        case 'g':
          c = 4;
          break;
        case 's':
          c = 2;
          break;
        case '[':
          fmt = __sccl (ccltab, fmt);
          flags |= 0x20;
          c = 1;
          break;
        case 'c':
          flags |= 0x20;
          c = 0;
          break;
        case 'p':
          flags |= 0x10 | 0x100;
          c = 3;
          ccfn = strtoul;
          base = 16;
          break;
        case 'n':
          if (flags & 0x08)
            continue;
          if (flags & 0x04)
            {
              sp = __builtin_va_arg(ap, short *);
              *sp = nread;
            }
          else if (flags & 0x01)
            {
              lp = __builtin_va_arg(ap, long *);
              *lp = nread;
            }
          else
            {
              ip = __builtin_va_arg(ap, int *);
              *ip = nread;
            }
          continue;
        case '\0':
          return (-1);
        default:
          if (((_ctype_+1)[(unsigned)(c)]&01))
            flags |= 0x01;
          c = 3;
          ccfn = (unsigned long (*)())strtol;
          base = 10;
          break;
        }
      if ((fp->_r <= 0 && __srefill(fp)))
        goto input_failure;
      if ((flags & 0x20) == 0)
        {
          while (((_ctype_+1)[(unsigned)(*fp->_p)]&010))
            {
              nread++;
              if (--fp->_r > 0)
                fp->_p++;
              else
              if (__srefill (fp))
                goto input_failure;
            }
        }
      switch (c)
        {
        case 0:
          if (width == 0)
            width = 1;
          if (flags & 0x08)
            {
              size_t sum = 0;
              for (;;)
                {
                  if ((n = fp->_r) < width)
                    {
                      sum += n;
                      width -= n;
                      fp->_p += n;
                      if (__srefill (fp))
                        {
                          if (sum == 0)
                            goto input_failure;
                          break;
                        }
                    }
                  else
                    {
                      sum += width;
                      fp->_r -= width;
                      fp->_p += width;
                      break;
                    }
                }
              nread += sum;
            }
          else
            {
              size_t r = fread ((void *) __builtin_va_arg(ap, char *), 1, width, fp);
              if (r == 0)
                goto input_failure;
              nread += r;
              nassigned++;
            }
          break;
        case 1:
          if (width == 0)
            width = ~0;
          if (flags & 0x08)
            {
              n = 0;
              while (ccltab[*fp->_p])
                {
                  n++, fp->_r--, fp->_p++;
                  if (--width == 0)
                    break;
                  if ((fp->_r <= 0 && __srefill(fp)))
                    {
                      if (n == 0)
                        goto input_failure;
                      break;
                    }
                }
              if (n == 0)
                goto match_failure;
            }
          else
            {
              p0 = p = __builtin_va_arg(ap, char *);
              while (ccltab[*fp->_p])
                {
                  fp->_r--;
                  *p++ = *fp->_p++;
                  if (--width == 0)
                    break;
                  if ((fp->_r <= 0 && __srefill(fp)))
                    {
                      if (p == p0)
                        goto input_failure;
                      break;
                    }
                }
              n = p - p0;
              if (n == 0)
                goto match_failure;
              *p = 0;
              nassigned++;
            }
          nread += n;
          break;
        case 2:
          if (width == 0)
            width = ~0;
          if (flags & 0x08)
            {
              n = 0;
              while (!((_ctype_+1)[(unsigned)(*fp->_p)]&010))
                {
                  n++, fp->_r--, fp->_p++;
                  if (--width == 0)
                    break;
                  if ((fp->_r <= 0 && __srefill(fp)))
                    break;
                }
              nread += n;
            }
          else
            {
              p0 = p = __builtin_va_arg(ap, char *);
              while (!((_ctype_+1)[(unsigned)(*fp->_p)]&010))
                {
                  fp->_r--;
                  *p++ = *fp->_p++;
                  if (--width == 0)
                    break;
                  if ((fp->_r <= 0 && __srefill(fp)))
                    break;
                }
              *p = 0;
              nread += p - p0;
              nassigned++;
            }
          continue;
        case 3:
          if (--width > sizeof (buf) - 2)
            width = sizeof (buf) - 2;
          width++;
          flags |= 0x40 | 0x80 | 0x200;
          for (p = buf; width; width--)
            {
              c = *fp->_p;
              switch (c)
                {
                case '0':
                  if (base == 0)
                    {
                      base = 8;
                      flags |= 0x100;
                    }
                  if (flags & 0x200)
                    flags &= ~(0x40 | 0x200 | 0x80);
                  else
                    flags &= ~(0x40 | 0x100 | 0x80);
                  goto ok;
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                  base = basefix[base];
                  flags &= ~(0x40 | 0x100 | 0x80);
                  goto ok;
                case '8':
                case '9':
                  base = basefix[base];
                  if (base <= 8)
                    break;
                  flags &= ~(0x40 | 0x100 | 0x80);
                  goto ok;
                case 'A':
                case 'B':
                case 'C':
                case 'D':
                case 'E':
                case 'F':
                case 'a':
                case 'b':
                case 'c':
                case 'd':
                case 'e':
                case 'f':
                  if (base <= 10)
                    break;
                  flags &= ~(0x40 | 0x100 | 0x80);
                  goto ok;
                case '+':
                case '-':
                  if (flags & 0x40)
                    {
                      flags &= ~0x40;
                      goto ok;
                    }
                  break;
                case 'x':
                case 'X':
                  if (flags & 0x100 && p == buf + 1)
                    {
                      base = 16;
                      flags &= ~0x100;
                      goto ok;
                    }
                  break;
                }
              break;
            ok:
              *p++ = c;
              if (--fp->_r > 0)
                fp->_p++;
              else
              if (__srefill (fp))
                break;
            }
          if (flags & 0x80)
            {
              if (p > buf)
                (void) ungetc (*(char *)-- p, fp);
              goto match_failure;
            }
          c = ((char *) p)[-1];
          if (c == 'x' || c == 'X')
            {
              --p;
                         ungetc (c, fp);
            }
          if ((flags & 0x08) == 0)
            {
              unsigned long res;
              *p = 0;
              res = (*ccfn) (buf, (char **) ((void *)0), base);
              if (flags & 0x10)
                *(__builtin_va_arg(ap, void * *)) = (void *) (unsigned long) res;
              else if (flags & 0x04)
                {
                  sp = __builtin_va_arg(ap, short *);
                  *sp = res;
                }
              else if (flags & 0x01)
                {
                  lp = __builtin_va_arg(ap, long *);
                  *lp = res;
                }
              else
                {
                  ip = __builtin_va_arg(ap, int *);
                  *ip = res;
                }
              nassigned++;
            }
          nread += p - buf;
          break;
        case 4:
        {
          long leading_zeroes;
          long zeroes, exp_adjust;
          char *exp_start;
          if (--width > sizeof (buf) - 2)
            width = sizeof (buf) - 2;
          width++;
          flags |= 0x40 | 0x80 | 0x100 | 0x200;
          zeroes = 0;
          exp_adjust = 0;
          for (p = buf; width; )
            {
              c = *fp->_p;
              switch (c)
                {
                case '0':
                  if (flags & 0x80)
                    {
                      flags &= ~0x40;
                      zeroes++;
                      goto fskip;
                    }
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                  flags &= ~(0x40 | 0x80);
                  goto fok;
                case '+':
                case '-':
                  if (flags & 0x40)
                    {
                      flags &= ~0x40;
                      goto fok;
                    }
                  break;
                case '.':
                  if (flags & 0x100)
                    {
                      flags &= ~(0x40 | 0x100);
                      leading_zeroes = zeroes;
                      goto fok;
                    }
                  break;
                case 'e':
                case 'E':
                  if ((flags & (0x80 | 0x200)) == 0x200
                      || ((flags & 0x200) && zeroes))
                    {
                      if (! (flags & 0x100))
                        {
                          exp_adjust = zeroes - leading_zeroes;
                          exp_start = p;
                        }
                      flags =
                        (flags & ~(0x200 | 0x100)) |
                        0x40 | 0x80;
                      zeroes = 0;
                      goto fok;
                    }
                  break;
                }
              break;
            fok:
              *p++ = c;
              width--;
            fskip:
              ++nread;
              if (--fp->_r > 0)
                fp->_p++;
              else
              if (__srefill (fp))
                break;
            }
          if (zeroes)
            flags &= ~0x80;
          if (flags & 0x80)
            {
              if (flags & 0x200)
                {
                  while (p > buf)
                    {
                      ungetc (*(char *)-- p, fp);
                      --nread;
                    }
                  goto match_failure;
                }
              c = *(char *)-- p;
              --nread;
              if (c != 'e' && c != 'E')
                {
                  (void) ungetc (c, fp);
                  c = *(char *)-- p;
                  --nread;
                }
              (void) ungetc (c, fp);
            }
          if ((flags & 0x08) == 0)
            {
              double res;
              long new_exp;
              *p = 0;
              if ((flags & (0x100 | 0x200)) == 0x200)
                {
                  exp_adjust = zeroes - leading_zeroes;
                  new_exp = -exp_adjust;
                  exp_start = p;
                }
              else if (exp_adjust)
                new_exp = atol (exp_start + 1) - exp_adjust;
              if (exp_adjust)
                {
                  if (exp_start >= buf + sizeof (buf) - ((8 * sizeof (long) - 1) * 4 / 13 + 2))
                    exp_start = buf + sizeof (buf) - ((8 * sizeof (long) - 1) * 4 / 13 + 2) - 1;
                 sprintf (exp_start, D_002BD6E8, new_exp);
                }
              res = atof (buf);
              if (flags & 0x01)
                {
                  dp = __builtin_va_arg(ap, double *);
                  *dp = res;
                }
              else if (flags & 0x02)
                {
                  ldp = __builtin_va_arg(ap, long double *);
                  *ldp = res;
                }
              else
                {
                  flp = __builtin_va_arg(ap, float *);
                  *flp = res;
                }
              nassigned++;
            }
          break;
        }
        }
    }
input_failure:
  return nassigned ? nassigned : -1;
match_failure:
  return nassigned;
}

#undef __sbuf
#undef __sFILE
#undef FILE
#undef _fpos_t
#undef size_t
#undef wchar_t
#undef basefix
#undef _ctype_
#undef __srefill
#undef ungetc
#undef __sccl
#undef sprintf
#undef strtol
#undef strtoul
#undef fread
#undef atol
#undef atof
#undef fp

char *func_001A0378(char *tab, char *fmt) {
    s32 c, n, v;

    c = *fmt++;
    if (c == '^') {
        v = 1;
        c = *fmt++;
    } else
        v = 0;
    for (n = 0; n < 256; n++)
        tab[n] = v;
    if (c == 0)
        return fmt - 1;

    v = 1 - v;
    for (;;) {
        tab[c] = v;
    doswitch:
        n = *fmt++;
        switch (n) {

        case 0:
            return fmt - 1;

        case '-':
            n = *fmt;
            if (n == ']' || n < c) {
                c = '-';
                break;
            }
            fmt++;
            do {
                tab[++c] = v;
            } while (c < n);
            goto doswitch;

        case ']':
            return fmt;

        default:
            c = n;
            break;
        }
    }
}

s64 func_001A0478(s32 *ptr, s32 fd, s32 buf, s32 cnt) {
    s64 ret;
    D_003512F8 = 0;
    if ((ret = (s64)func_0017BEA8(fd, buf, cnt)) == -1 && D_003512F8 != 0)
        *ptr = D_003512F8;
    return ret;
}

typedef struct sw_reent { u8 pad0[0x38]; s32 __sdidinit; } sw_reent;
typedef struct sw_sbuf { u8 *_base; s32 _size; } sw_sbuf;
typedef struct sw_FILE {
    u8 *_p;
    s32 _r;
    s32 _w;
    s16 _flags;
    s16 _file;
    sw_sbuf _bf;
    s32 _lbfsize;
    void *_cookie;
    void *_read;
    void *_write;
    void *_seek;
    void *_close;
    sw_sbuf _ub;
    u8 *_up;
    s32 _ur;
    u8 _ubuf[3];
    u8 _nbuf[1];
    sw_sbuf _lb;
    s32 _blksize;
    s32 _offset;
    sw_reent *_data;
} sw_FILE;

s32 func_001A04D8(void *arg0) {
    sw_FILE *fp = arg0;

    do {
        if (fp->_data == 0)
            fp->_data = (sw_reent *)D_0028FA98;
        if (!fp->_data->__sdidinit)
            func_00196A30(fp->_data);
    } while (0);

    if ((fp->_flags & 8) == 0) {
        if ((fp->_flags & 0x10) == 0)
            return -1;
        if (fp->_flags & 4) {
            if (fp->_ub._base != NULL) {
                if (fp->_ub._base != fp->_ubuf)
                    func_00196BE0((s32)fp->_data, (s32)fp->_ub._base);
                fp->_ub._base = NULL;
            }
            fp->_flags &= ~(4 | 0x20);
            fp->_r = 0;
            fp->_p = fp->_bf._base;
        }
        fp->_flags |= 8;
    }

    if (fp->_bf._base == NULL)
        func_00197838(fp);

    if (fp->_flags & 1) {
        fp->_w = 0;
        fp->_lbfsize = -fp->_bf._size;
    } else
        fp->_w = fp->_flags & 2 ? 0 : fp->_bf._size;

    return 0;
}

/* __muldi3 */
typedef union { struct { s32 low, high; } s; s64 ll; } DIunion;

s64 func_001A05E8(s64 u, s64 v) {
    DIunion w;
    DIunion uu, vv;

    uu.ll = u, vv.ll = v;
    {
        DIunion __w;
        __asm__("multu %2,%3" : "=l"((u32)(__w.s.low)), "=h"((u32)(__w.s.high)) : "d"((u32)(uu.s.low)), "d"((u32)(vv.s.low)));
        w.ll = __w.ll;
    }
    w.s.high += ((u32)uu.s.low * (u32)vv.s.high + (u32)uu.s.high * (u32)vv.s.low);
    return w.ll;
}

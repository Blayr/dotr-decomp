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
    if ((ret = (void *)sbrk(incr)) == (void *)-1 && D_003512F8 != 0)
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

    ((void (*)(s32))__env_lock)(reent_ptr);
    if (*value == '=')
        ++value;
    l_value = func_0019BEF0(value);
    if ((C = (char *)_findenv_r(reent_ptr, name, (s32)&offset))) {
        if (!rewrite) {
            ((void (*)(s32))__env_unlock)(reent_ptr);
            return 0;
        }
        if ((u32)func_0019BEF0(C) >= (u32)l_value) {
            while ((*C++ = *value++) != 0)
                ;
            ((void (*)(s32))__env_unlock)(reent_ptr);
            return 0;
        }
    } else {
        s32 cnt;
        char **P;

        for (P = *D_0028FF08, cnt = 0; *P; ++P, ++cnt)
            ;
        if (D_00317240) {
            if (!(*D_0028FF08 = (char **)func_0019A690((void *)reent_ptr, D_0028F79C, sizeof(char *) * (cnt + 2)))) {
                ((void (*)(s32))__env_unlock)(reent_ptr);
                return -1;
            }
        } else {
            D_00317240 = 1;
            P = (char **)_malloc_r(reent_ptr, sizeof(char *) * (cnt + 2));
            if (!P) {
                ((void (*)(s32))__env_unlock)(reent_ptr);
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
    if (!((*D_0028FF08)[offset] = S = _malloc_r(reent_ptr, (C - (char *)name) + l_value + 2))) {
        ((void (*)(s32))__env_unlock)(reent_ptr);
        return -1;
    }
    for (C = S; (*C = *(char *)name++) && *C != '='; ++C)
        ;
    for (*C++ = '='; (*C++ = *value++) != 0;)
        ;
    ((void (*)(s32))__env_unlock)(reent_ptr);
    return 0;
}

s32 func_0019B418(s32 reent_ptr, s32 name) {
    char **P;
    s32 offset;

    ((void (*)(s32))__env_lock)(reent_ptr);
    while (_findenv_r(reent_ptr, name, (s32)&offset))
        for (P = &(*D_0028FF08)[offset];; ++P)
            if (!(*P = *(P + 1)))
                break;
    ((void (*)(s32))__env_unlock)(reent_ptr);
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

s32 eofread(void) {
    return 0;
}

s32 sscanf(const char *str, const char *fmt, ...) {
    s32 ret;
    __builtin_va_list ap;
    ssc_FILE f;

    f._flags = 0x0004;
    f._bf_base = f._p = (u8 *)str;
    f._bf_size = f._r = func_0019BEF0(str);
    f._read = (void *)eofread;
    f._ub_base = NULL;
    f._lb_base = NULL;
    f._data = (void *)D_0028FA98;
    __builtin_stdarg_start(ap, fmt);
    ret = func_0019F6E8(&f, fmt, ap);
    __builtin_va_end(ap);
    return ret;
}

s32 __sread(void *cookie, char *buf, s32 n) {
    sread_FILE *fp = (sread_FILE *)cookie;
    s32 ret;

    ret = func_0019A630(fp->_data, fp->_file, (s32)buf, n);
    if (ret >= 0)
        fp->_offset += ret;
    else
        fp->_flags &= ~0x1000;
    return ret;
}

s32 __swrite(void *arg0, s32 arg1, s32 arg2) {
    if ((*(u16 *)((u8 *)arg0 + 0xC)) & 0x100) {
        _lseek_r((*(s32 *)((u8 *)arg0 + 0x54)), (*(s16 *)((u8 *)arg0 + 0xE)), 0, 2);
    }
    (*(u16 *)((u8 *)arg0 + 0xC)) = (u16) ((*(s32 *)((u8 *)arg0 + 0xC)) & 0xEFFF);
    return func_001A0478((*(s32 *)((u8 *)arg0 + 0x54)), (*(s16 *)((u8 *)arg0 + 0xE)), arg1, arg2);
}

s64 __sseek(void *cookie, s64 offset, s32 whence) {
    sseek_FILE *fp = (sseek_FILE *)cookie;
    s64 ret;

    ret = ((s64 (*)(s32 *, s32, s64, s32))_lseek_r)(fp->_data, fp->_file, offset, whence);
    if (ret == -1L)
        fp->_flags &= ~0x1000;
    else {
        fp->_flags |= 0x1000;
        fp->_offset = ret;
    }
    return ret;
}

void __sclose(void *arg0) {
    func_001951F8((*(s32 *)((u8 *)arg0 + 0x54)), (*(s16 *)((u8 *)arg0 + 0xE)));
}

#define tolower_0019B8F8(c) ({ int __x = (c); ((D_002BD0C0 + 1)[(int)(__x)] & 01) ? (__x - 'A' + 'a') : __x; })

/* strcasecmp (newlib 1.9.0 strcasecmp.c): adapted from kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

s32 strcasecmp(const char *s1, const char *s2) {
    extern const char D_002BD0C0[];

    while (*s1 != '\0' && tolower_0019B8F8(*s1) == tolower_0019B8F8(*s2)) {
        s1++;
        s2++;
    }

    return tolower_0019B8F8(*(unsigned char *)s1) - tolower_0019B8F8(*(unsigned char *)s2);
}

#undef tolower_0019B8F8

/* strcat: newlib's hand-written r5900 assembly (libc/machine/r5900/strcat.S), kept as asm; identified via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

char *strcat(char *dst, const char *src) {
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

char *strchr(char *s, s32 c) {
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

s32 strcmp(const char *a, const char *b) {
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

char *strcpy(char *dst, const char *src) {
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

s32 strlen(const char *s) {
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

s32 strncasecmp(const char *s1, const char *s2, u32 n) {
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

s32 strncmp(const char *a, const char *b, u32 n) {
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

void *strncpy(void *dst, const void *src, u32 n) {
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

char *strrchr(const char *s, s32 i) {
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

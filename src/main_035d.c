#include "common.h"
#include "sce/libc.h"

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

INCLUDE_ASM("asm/nonmatchings/main_035d", func_0019DDE8);

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

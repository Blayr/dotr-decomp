#include "common.h"
#include "sce/libc.h"

/* _vfprintf_r (newlib 1.9.0 vfprintf.c): adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

extern const char D_002BD4B0[]; /* blanks */
extern const char D_002BD4C0[]; /* zeroes */
extern const char D_002BD4D0[];
extern const char D_002BD4D8[];
extern const char D_002BD4E0[];
extern const char D_002BD4F8[];
extern const char D_002BD500[];
extern const char D_002BD518[];
extern const char D_002BD538[];
extern const char D_002BD540[];
extern s32 D_0028FAA0; /* __mb_cur_max */

#define va_list char *
#define va_arg(ap, type) __builtin_va_arg(ap, type)
#define wchar_t int
#define MAXEXP 308
#define MAXFRACT 39
#define BUF (MAXEXP + MAXFRACT + 1)
#define DEFPREC 6
#define __SLBF 0x0001
#define __SNBF 0x0002
#define __SRD 0x0004
#define __SWR 0x0008
#define __SRW 0x0010
#define __SEOF 0x0020
#define __SERR 0x0040
#define EOF (-1)
#define cantwrite(fp) ((((fp)->flags & __SWR) == 0 || (fp)->bf.base == NULL) && func_001A04D8(fp))
#define __sferror(p) ((p)->flags & __SERR)
#define to_digit(c) ((c) - '0')
#define is_digit(c) ((unsigned)to_digit(c) <= 9)
#define to_char(n) ((n) + '0')
#define ALT 0x001
#define HEXPREFIX 0x002
#define LADJUST 0x004
#define LONGDBL 0x008
#define LONGINT 0x010
#define QUADINT 0x020
#define SHORTINT 0x040
#define ZEROPAD 0x080
#define FPT 0x100
#define blanks D_002BD4B0
#define zeroes D_002BD4C0

#define fp ((Fil *)fp_0019DDE8)

s32 func_0019DDE8(vf_reent *data, vf_FILE *fp_0019DDE8, const char *fmt0, void *ap_0019DDE8) {
    __builtin_va_list ap = ap_0019DDE8;
    register char *fmt;           /* format string */
    register int ch;              /* character from fmt */
    register int n, m;            /* handy integers (short term usage) */
    register char *cp;            /* handy char pointer (short term usage) */
    register struct __siov *iovp; /* for PRINT macro */
    register int flags;           /* flags as above */
    int ret;                      /* return value accumulator */
    int width;                    /* width from format (%8d), or 0 */
    int prec;                     /* precision from format (%.3d), or -1 */
    char sign;                    /* sign prefix (' ', '+', '-', or \0) */
    wchar_t wc;
    char *decimal_point = *(char **)func_001977B8();
    char softsign;  /* temporary negative sign for floats */
    double _double; /* double precision arguments %[eEfgG] */
    int expt;       /* integer value of exponent */
    int expsize;    /* character count for expstr */
    int ndig;       /* actual number of digits returned by cvt */
    char expstr[7]; /* buffer for exponent string */

    unsigned long _uquad; /* integer arguments %[diouxX] */

    enum { OCT, DEC, HEX } base; /* base for [diouxX] conversion */

    int dprec;   /* a copy of prec if [diouxX], 0 otherwise */
    int realsz;  /* field size expanded by dprec */
    int size;    /* size of converted field or string */
    char *xdigs; /* digits for [xX] conversion */
#define NIOV 8
    struct __suio uio;       /* output information: summary */
    struct __siov iov[NIOV]; /* ... and individual io vectors */
    char buf[BUF];           /* space for %c, %[diouxX], %[eEfgG] */
    char ox[2];              /* space for 0x hex-prefix */
    int state = 0;           /* mbtowc calls from library must not change state */

#define PADSIZE 16 /* pad chunk size */

#define PRINT(ptr, len)                                                                            \
    {                                                                                              \
        iovp->iov_len = (len);                                                                     \
        iovp->iov_base = (ptr);                                                                    \
        uio.uio_resid += (len);                                                                    \
        iovp++;                                                                                    \
        if (++uio.uio_iovcnt >= NIOV) {                                                            \
            if (func_0019DC70((s32)fp, &uio))                                                                \
                goto error;                                                                        \
            iovp = iov;                                                                            \
        }                                                                                          \
    }
#define PAD(howmany, with)                                                                         \
    {                                                                                              \
        if ((n = (howmany)) > 0) {                                                                 \
            while (n > PADSIZE) {                                                                  \
                PRINT(with, PADSIZE);                                                              \
                n -= PADSIZE;                                                                      \
            }                                                                                      \
            PRINT(with, n);                                                                        \
        }                                                                                          \
    }
#define FLUSH()                                                                                    \
    {                                                                                              \
        if (uio.uio_resid && func_0019DC70((s32)fp, &uio))                                                   \
            goto error;                                                                            \
        uio.uio_iovcnt = 0;                                                                        \
        iovp = iov;                                                                                \
    }

#define SARG()                                                                                     \
    (flags & LONGINT    ? va_arg(ap, long)                                                         \
     : flags & SHORTINT ? (long)(short)va_arg(ap, int)                                             \
                        : (long)va_arg(ap, int))
#define UARG()                                                                                     \
    (flags & LONGINT    ? va_arg(ap, unsigned long)                                                \
     : flags & SHORTINT ? (unsigned long)(unsigned short)va_arg(ap, int)                           \
                        : (unsigned long)va_arg(ap, unsigned int))

    /* sorry, fprintf(read_only_file, "") returns EOF, not 0 */
    if (cantwrite(fp))
        return (EOF);

    /* optimise fprintf(stderr) (and other unbuffered Unix files) */
    if ((fp->flags & (__SNBF | __SWR | __SRW)) == (__SNBF | __SWR) && fp->file >= 0)
        return (func_0019DCB8(fp, fmt0, ap));

    fmt = (char *)fmt0;
    uio.uio_iov = iovp = iov;
    uio.uio_resid = 0;
    uio.uio_iovcnt = 0;
    ret = 0;

    /*
     * Scan the format for conversions (`%' character).
     */
    for (;;) {
        cp = fmt;
        while ((n = func_001985E0((void *)D_0028FA98, (s32 *)&wc, fmt, D_0028FAA0, &state)) > 0) {
            fmt += n;
            if (wc == '%') {
                fmt--;
                break;
            }
        }
        if ((m = fmt - cp) != 0) {
            PRINT(cp, m);
            ret += m;
        }
        if (n <= 0)
            goto done;
        fmt++; /* skip over '%' */

        flags = 0;
        dprec = 0;
        width = 0;
        prec = -1;
        sign = '\0';

    rflag:
        ch = *fmt++;
    reswitch:
        switch (ch) {
        case ' ':
            if (!sign)
                sign = ' ';
            goto rflag;
        case '#':
            flags |= ALT;
            goto rflag;
        case '*':
            if ((width = va_arg(ap, int)) >= 0)
                goto rflag;
            width = -width;
            /* FALLTHROUGH */
        case '-':
            flags |= LADJUST;
            goto rflag;
        case '+':
            sign = '+';
            goto rflag;
        case '.':
            if ((ch = *fmt++) == '*') {
                n = va_arg(ap, int);
                prec = n < 0 ? -1 : n;
                goto rflag;
            }
            n = 0;
            while (is_digit(ch)) {
                n = 10 * n + to_digit(ch);
                ch = *fmt++;
            }
            prec = n < 0 ? -1 : n;
            goto reswitch;
        case '0':
            flags |= ZEROPAD;
            goto rflag;
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            n = 0;
            do {
                n = 10 * n + to_digit(ch);
                ch = *fmt++;
            } while (is_digit(ch));
            width = n;
            goto reswitch;
        case 'L':
            flags |= LONGDBL;
            goto rflag;
        case 'h':
            flags |= SHORTINT;
            goto rflag;
        case 'l':
            if (*fmt == 'l') {
                fmt++;
                flags |= QUADINT;
            } else {
                flags |= LONGINT;
            }
            goto rflag;
        case 'q':
            flags |= QUADINT;
            goto rflag;
        case 'c':
            *(cp = buf) = va_arg(ap, int);
            size = 1;
            sign = '\0';
            break;
        case 'D':
            flags |= LONGINT;
            /*FALLTHROUGH*/
        case 'd':
        case 'i':
            _uquad = SARG();
            if ((long)_uquad < 0) {
                _uquad = -_uquad;
                sign = '-';
            }
            base = DEC;
            goto number;
        case 'e':
        case 'E':
        case 'f':
        case 'g':
        case 'G':
            if (prec == -1) {
                prec = DEFPREC;
            } else if ((ch == 'g' || ch == 'G') && prec == 0) {
                prec = 1;
            }

            if (flags & LONGDBL) {
                _double = (double)va_arg(ap, long double);
            } else {
                _double = va_arg(ap, double);
            }

            /* do this before tricky precision changes */
            if (func_0019AE30(_double)) {
                if (_double < 0)
                    sign = '-';
                cp = D_002BD4D0;
                size = 3;
                break;
            }
            if (func_0019AE78(_double)) {
                cp = D_002BD4D8;
                size = 3;
                break;
            }

            flags |= FPT;
            cp = func_0019F448(data, _double, prec, flags, &softsign, &expt, ch, &ndig);
            if (ch == 'g' || ch == 'G') {
                if (expt <= -4 || expt > prec)
                    ch = (ch == 'g') ? 'e' : 'E';
                else
                    ch = 'g';
            }
            if (ch <= 'e') { /* 'e' or 'E' fmt */
                --expt;
                expsize = func_0019F608(expstr, expt, ch);
                size = expsize + ndig;
                if (ndig > 1 || flags & ALT)
                    ++size;
            } else if (ch == 'f') { /* f fmt */
                if (expt > 0) {
                    size = expt;
                    if (prec || flags & ALT)
                        size += prec + 1;
                } else /* "0.X" */
                    size = prec + 2;
            } else if (expt >= ndig) { /* fixed g fmt */
                size = expt;
                if (flags & ALT)
                    ++size;
            } else
                size = ndig + (expt > 0 ? 1 : 2 - expt);

            if (softsign)
                sign = '-';
            break;
        case 'n':
            if (flags & LONGINT)
                *va_arg(ap, long *) = ret;
            else if (flags & SHORTINT)
                *va_arg(ap, short *) = ret;
            else
                *va_arg(ap, int *) = ret;
            continue; /* no output */
        case 'O':
            flags |= LONGINT;
            /*FALLTHROUGH*/
        case 'o':
            _uquad = UARG();
            base = OCT;
            goto nosign;
        case 'p':
            /* NOSTRICT */
            _uquad = (unsigned long)(unsigned long)va_arg(ap, void *);
            base = HEX;
            xdigs = D_002BD4E0;
            flags |= HEXPREFIX;
            ch = 'x';
            goto nosign;
        case 's':
            if ((cp = va_arg(ap, char *)) == NULL)
                cp = D_002BD4F8;
            if (prec >= 0) {
                char *p = func_00198618(cp, 0, prec);

                if (p != NULL) {
                    size = p - cp;
                    if (size > prec)
                        size = prec;
                } else
                    size = prec;
            } else
                size = func_0019BEF0(cp);
            sign = '\0';
            break;
        case 'U':
            flags |= LONGINT;
            /*FALLTHROUGH*/
        case 'u':
            _uquad = UARG();
            base = DEC;
            goto nosign;
        case 'X':
            xdigs = D_002BD500;
            goto hex;
        case 'x':
            xdigs = D_002BD4E0;
        hex:
            _uquad = UARG();
            base = HEX;
            /* leading 0x/X only if non-zero */
            if (flags & ALT && _uquad != 0)
                flags |= HEXPREFIX;

            /* unsigned conversions */
        nosign:
            sign = '\0';
        number:
            if ((dprec = prec) >= 0)
                flags &= ~ZEROPAD;

            cp = buf + BUF;
            if (_uquad != 0 || prec != 0) {
                switch (base) {
                case OCT:
                    do {
                        *--cp = to_char(_uquad & 7);
                        _uquad >>= 3;
                    } while (_uquad);
                    /* handle octal leading 0 */
                    if (flags & ALT && *cp != '0')
                        *--cp = '0';
                    break;

                case DEC:
                    /* many numbers are 1 digit */
                    while (_uquad >= 10) {
                        *--cp = to_char(_uquad % 10);
                        _uquad /= 10;
                    }
                    *--cp = to_char(_uquad);
                    break;

                case HEX:
                    do {
                        *--cp = xdigs[_uquad & 15];
                        _uquad >>= 4;
                    } while (_uquad);
                    break;

                default:
                    cp = D_002BD518;
                    size = func_0019BEF0(cp);
                    goto skipsize;
                }
            }
            size = buf + BUF - cp;
        skipsize:
            break;
        default: /* "%?" prints ?, unless ? is NUL */
            if (ch == '\0')
                goto done;
            /* pretend it was %c with argument ch */
            cp = buf;
            *cp = ch;
            size = 1;
            sign = '\0';
            break;
        }

        realsz = dprec > size ? dprec : size;
        if (sign)
            realsz++;
        else if (flags & HEXPREFIX)
            realsz += 2;

        /* right-adjusting blank padding */
        if ((flags & (LADJUST | ZEROPAD)) == 0)
            PAD(width - realsz, blanks);

        /* prefix */
        if (sign) {
            PRINT(&sign, 1);
        } else if (flags & HEXPREFIX) {
            ox[0] = '0';
            ox[1] = ch;
            PRINT(ox, 2);
        }

        /* right-adjusting zero padding */
        if ((flags & (LADJUST | ZEROPAD)) == ZEROPAD)
            PAD(width - realsz, zeroes);

        /* leading zeroes from decimal precision */
        PAD(dprec - size, zeroes);

        /* the string or number proper */
        if ((flags & FPT) == 0) {
            PRINT(cp, size);
        } else {             /* glue together f_p fragments */
            if (ch >= 'f') { /* 'f' or 'g' */
                if (_double == 0) {
                    /* kludge for __dtoa irregularity */
                    PRINT(D_002BD538, 1);
                    if (expt < ndig || (flags & ALT) != 0) {
                        PRINT(decimal_point, 1);
                        PAD(ndig - 1, zeroes);
                    }
                } else if (expt <= 0) {
                    PRINT(D_002BD538, 1);
                    if (ndig) {
                        PRINT(decimal_point, 1);
                        PAD(-expt, zeroes);
                        PRINT(cp, ndig);
                    }
                } else if (expt >= ndig) {
                    PRINT(cp, ndig);
                    PAD(expt - ndig, zeroes);
                    if (flags & ALT)
                        PRINT(D_002BD540, 1);
                } else {
                    PRINT(cp, expt);
                    cp += expt;
                    PRINT(D_002BD540, 1);
                    PRINT(cp, ndig - expt);
                }
            } else { /* 'e' or 'E' */
                if (ndig > 1 || flags & ALT) {
                    ox[0] = *cp++;
                    ox[1] = '.';
                    PRINT(ox, 2);
                    if (_double || flags & ALT == 0) {
                        PRINT(cp, ndig - 1);
                    } else /* 0.[0..] */
                        /* __dtoa irregularity */
                        PAD(ndig - 1, zeroes);
                } else /* XeYYY */
                    PRINT(cp, 1);
                PRINT(expstr, expsize);
            }
        }
        /* left-adjusting padding (always blank) */
        if (flags & LADJUST)
            PAD(width - realsz, blanks);

        /* finally, adjust ret */
        ret += width > realsz ? width : realsz;

        FLUSH(); /* copy out the I/O vectors */
    }
done:
    FLUSH();
error:
    return (__sferror(fp) ? EOF : ret);
    /* NOTREACHED */
}


#undef va_list
#undef va_arg
#undef wchar_t
#undef MAXEXP
#undef MAXFRACT
#undef BUF
#undef DEFPREC
#undef __SLBF
#undef __SNBF
#undef __SRD
#undef __SWR
#undef __SRW
#undef __SEOF
#undef __SERR
#undef EOF
#undef cantwrite
#undef __sferror
#undef to_digit
#undef is_digit
#undef to_char
#undef ALT
#undef HEXPREFIX
#undef LADJUST
#undef LONGDBL
#undef LONGINT
#undef QUADINT
#undef SHORTINT
#undef ZEROPAD
#undef FPT
#undef blanks
#undef zeroes
#undef NIOV
#undef PADSIZE
#undef PRINT
#undef PAD
#undef FLUSH
#undef SARG
#undef UARG
#undef fp

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

#include "common.h"
#include "sce/libc.h"

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
#define fread(b, s, n, fp) fread(b, s, n, fp)
#define atol(s) ((long (*)(const char *))func_001950C8)(s)
#define atof(s) ((double (*)(const char *))atof)(s)
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
    if ((ret = (s64)write(fd, buf, cnt)) == -1 && D_003512F8 != 0)
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
            __sinit(fp->_data);
    } while (0);

    if ((fp->_flags & 8) == 0) {
        if ((fp->_flags & 0x10) == 0)
            return -1;
        if (fp->_flags & 4) {
            if (fp->_ub._base != NULL) {
                if (fp->_ub._base != fp->_ubuf)
                    _free_r((s32)fp->_data, (s32)fp->_ub._base);
                fp->_ub._base = NULL;
            }
            fp->_flags &= ~(4 | 0x20);
            fp->_r = 0;
            fp->_p = fp->_bf._base;
        }
        fp->_flags |= 8;
    }

    if (fp->_bf._base == NULL)
        __smakebuf(fp);

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

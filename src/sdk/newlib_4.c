#include "common.h"
#include "sce/libc.h"

/* _strtod_r: newlib 1.9.0 stdlib/strtod.c (David M. Gay, (c) 1991 AT&T), see THIRD_PARTY_NOTICES.md */

#define _reent _reent_0019C4C8
#define double_union double_union_0019C4C8
#define _Bigint _Bigint_0019C4C8
struct _reent {
    int _errno;
};
union double_union {
    double d;
    u32 i[2];
};
typedef struct _Bigint _Bigint;
struct _Bigint {
    struct _Bigint *_next;
    int _k, _maxwds, _sign, _wds;
    u32 _x[1];
};
typedef u32 __ULong;
typedef u32 __uint32_t;
typedef s32 __int32_t;
typedef s32 __Long;

extern double D_002BD350[]; /* bigtens */
extern const double D_002BD498; /* .4999999 */
extern const double D_002BD4A0; /* .5000001 */
extern const double D_002BD4A8; /* .4999999 / 2 */
/* GCC writes these constants as `li.d`; Sony's assembler put a value with a non-zero low word in the
   literal pool and loaded it with the `ld $r, sym` macro. The game's pool entries are D_002BD498.. */
#define LITD(sym) ({ double _v; __asm__ __volatile__(".set noat\n\tlui $1, %%hi(" #sym ")\n\tld %0, %%lo(" #sym ")($1)\n\t.set at" : "=r"(_v)); _v; })
union __dmath_0019C4C8 {
    u32 i[2];
    double d;
};
extern const union __dmath_0019C4C8 D_002BD3A0[]; /* __infinity */
#define __infinity D_002BD3A0
extern double D_002BD378[]; /* tinytens */
#define __mprec_tens D_002BD288
#define memcpy func_00198790
#define __mprec_bigtens D_002BD350
#define __mprec_tinytens D_002BD378
#define _Balloc(p, k) ((_Bigint *)_Balloc(p, k))
#define _Bfree(p, v) _Bfree(p, v)
#define _s2b(p, s, a, b, y) ((_Bigint *)func_00198CB8(p, s, a, b, y))
#define _i2b(p, i) ((_Bigint *)func_00198F28(p, i))
#define _multiply(p, a, b) ((_Bigint *)func_00198F60(p, (i2b_Bigint *)(a), (i2b_Bigint *)(b)))
#define _pow5mult(p, b, k) ((_Bigint *)func_00199170(p, (i2b_Bigint *)(b), k))
#define _lshift(p, b, k) ((_Bigint *)func_00199270(p, (i2b_Bigint *)(b), k))
#define __mcmp(a, b) func_001993C8((mcmp_Bigint *)(a), (mcmp_Bigint *)(b))
#define __mdiff(p, a, b) ((_Bigint *)func_00199430(p, (i2b_Bigint *)(a), (i2b_Bigint *)(b)))
#define _ulp(x) func_001995C0(x)
#define _d2b(p, d, e, b) ((_Bigint *)func_00199828(p, d, e, b))
#define _ratio(a, b) func_001999B0((i2b_Bigint *)(a), (i2b_Bigint *)(b))
#define ptr ((struct _reent *)ptr0)

/* newlib _strtod_r: string `s00` as a double (the end into `se`). */
double func_0019C4C8(void *ptr0, const char *s00, char **se)
{
  int bb2, bb5, bbe, bd2, bd5, bbbits, bs2, c, dsign, e1, esign, i, j,
    k, nd, nd0, nf, nz, nz0, sign;
  long e;
  const char *s, *s0, *s1;
  double aadj, aadj1, adj;
  long L;
  unsigned long z;
  __ULong y;
  union double_union rv, rv0;
  _Bigint *bb, *bb1, *bd, *bd0, *bs, *delta;
  sign = nz0 = nz = 0;
  rv.d = 0.;
  for (s = s00;; s++)
    switch (*s)
      {
      case '-':
        sign = 1;
      case '+':
        if (*++s)
          goto break2;
      case 0:
        s = s00;
        goto ret;
      case '\t':
      case '\n':
      case '\v':
      case '\f':
      case '\r':
      case ' ':
        continue;
      default:
        goto break2;
      }
break2:
  if (*s == '0')
    {
      nz0 = 1;
      while (*++s == '0');
      if (!*s)
        goto ret;
    }
  s0 = s;
  y = z = 0;
  for (nd = nf = 0; (c = *s) >= '0' && c <= '9'; nd++, s++)
    if (nd < 9)
      y = 10 * y + c - '0';
    else if (nd < 16)
      z = 10 * z + c - '0';
  nd0 = nd;
  if (c == '.')
    {
      c = *++s;
      if (!nd)
        {
          for (; c == '0'; c = *++s)
            nz++;
          if (c > '0' && c <= '9')
            {
              s0 = s;
              nf += nz;
              nz = 0;
              goto have_dig;
            }
          goto dig_done;
        }
      for (; c >= '0' && c <= '9'; c = *++s)
        {
        have_dig:
          nz++;
          if (c -= '0')
            {
              nf += nz;
              for (i = 1; i < nz; i++)
                if (nd++ < 9)
                  y *= 10;
                else if (nd <= 15 + 1)
                  z *= 10;
              if (nd++ < 9)
                y = 10 * y + c;
              else if (nd <= 15 + 1)
                z = 10 * z + c;
              nz = 0;
            }
        }
    }
dig_done:
  e = 0;
  if (c == 'e' || c == 'E')
    {
      if (!nd && !nz && !nz0)
        {
          s = s00;
          goto ret;
        }
      s00 = s;
      esign = 0;
      switch (c = *++s)
        {
        case '-':
          esign = 1;
        case '+':
          c = *++s;
        }
      if (c >= '0' && c <= '9')
        {
          while (c == '0')
            c = *++s;
          if (c > '0' && c <= '9')
            {
              e = c - '0';
              s1 = s;
              while ((c = *++s) >= '0' && c <= '9')
                e = 10 * e + c - '0';
              if (s - s1 > 8)
                e = 9999999L;
              if (esign)
                e = -e;
            }
          else
            e = 0;
        }
      else
        s = s00;
    }
  if (!nd)
    {
      if (!nz && !nz0)
        s = s00;
      goto ret;
    }
  e1 = e -= nf;
  if (!nd0)
    nd0 = nd;
  k = nd < 15 + 1 ? nd : 15 + 1;
  rv.d = y;
  if (k > 9)
    rv.d = __mprec_tens[k - 9] * rv.d + z;
  bd0 = 0;
  if (nd <= 15
      && 0 == 1
    )
    {
      if (!e)
        goto ret;
      if (e > 0)
        {
          if (e <= 22)
            {
                           rv.d *= __mprec_tens[e];
              goto ret;
            }
          i = 15 - nd;
          if (e <= 22 + i)
            {
              e -= i;
              rv.d *= __mprec_tens[i];
                           rv.d *= __mprec_tens[e];
              goto ret;
            }
        }
      else if (e >= -22)
        {
                       rv.d /= __mprec_tens[-e];
          goto ret;
        }
    }
  e1 += nd - k;
  if (e1 > 0)
    {
      if ((i = e1 & 15) != 0)
        rv.d *= __mprec_tens[i];
      if (e1 &= ~15)
        {
          if (e1 > 308)
            {
            ovfl:
              ptr->_errno = 34;
              rv.d = (__infinity[0].d);
              if (bd0)
                goto retfree;
              goto ret;
            }
          if (e1 >>= 4)
            {
              for (j = 0; e1 > 1; j++, e1 >>= 1)
                if (e1 & 1)
                  rv.d *= __mprec_bigtens[j];
              (rv.i[1]) -= 53 * ((__uint32_t)0x100000L);
              rv.d *= __mprec_bigtens[j];
              if ((z = (rv.i[1]) & ((__uint32_t)0x7ff00000L))
                  > ((__uint32_t)0x100000L) * (1024 + 1023 - 53))
                goto ovfl;
              if (z > ((__uint32_t)0x100000L) * (1024 + 1023 - 1 - 53))
                {
                  (rv.i[1]) = (((__uint32_t)0xfffffL) | ((__uint32_t)0x100000L)*(1024+1023-1));
                  (rv.i[0]) = ((__uint32_t)0xffffffffL);
                }
              else
                (rv.i[1]) += 53 * ((__uint32_t)0x100000L);
            }
        }
    }
  else if (e1 < 0)
    {
      e1 = -e1;
      if ((i = e1 & 15) != 0)
        rv.d /= __mprec_tens[i];
      if (e1 &= ~15)
        {
          e1 >>= 4;
          if (e1 >= 1 << 5)
            goto undfl;
          for (j = 0; e1 > 1; j++, e1 >>= 1)
            if (e1 & 1)
              rv.d *= __mprec_tinytens[j];
          rv0.d = rv.d;
          rv.d *= __mprec_tinytens[j];
          if (!rv.d)
            {
              rv.d = 2. * rv0.d;
              rv.d *= __mprec_tinytens[j];
              if (!rv.d)
                {
                undfl:
                  rv.d = 0.;
                  ptr->_errno = 34;
                  if (bd0)
                    goto retfree;
                  goto ret;
                }
              (rv.i[1]) = 0;
              (rv.i[0]) = 1;
            }
        }
    }
  bd0 = _s2b (ptr, s0, nd0, nd, y);
  for (;;)
    {
      bd = _Balloc (ptr, bd0->_k);
      memcpy((char *)&bd->_sign, (char *)&bd0->_sign, bd0->_wds*sizeof(__int32_t) + 2*sizeof(int));
      bb = _d2b (ptr, rv.d, &bbe, &bbbits);
      bs = _i2b (ptr, 1);
      if (e >= 0)
        {
          bb2 = bb5 = 0;
          bd2 = bd5 = e;
        }
      else
        {
          bb2 = bb5 = -e;
          bd2 = bd5 = 0;
        }
      if (bbe >= 0)
        bb2 += bbe;
      else
        bd2 -= bbe;
      bs2 = bb2;
      i = bbe + bbbits - 1;
      if (i < (-1022))
        j = bbe + (53 - (-1022));
      else
        j = 53 + 1 - bbbits;
      bb2 += j;
      bd2 += j;
      i = bb2 < bd2 ? bb2 : bd2;
      if (i > bs2)
        i = bs2;
      if (i > 0)
        {
          bb2 -= i;
          bd2 -= i;
          bs2 -= i;
        }
      if (bb5 > 0)
        {
          bs = _pow5mult (ptr, bs, bb5);
          bb1 = _multiply (ptr, bs, bb);
          _Bfree (ptr, bb);
          bb = bb1;
        }
      if (bb2 > 0)
        bb = _lshift (ptr, bb, bb2);
      if (bd5 > 0)
        bd = _pow5mult (ptr, bd, bd5);
      if (bd2 > 0)
        bd = _lshift (ptr, bd, bd2);
      if (bs2 > 0)
        bs = _lshift (ptr, bs, bs2);
      delta = __mdiff (ptr, bb, bd);
      dsign = delta->_sign;
      delta->_sign = 0;
      i = __mcmp (delta, bs);
      if (i < 0)
        {
          if (dsign || (rv.i[0]) || (rv.i[1]) & ((__uint32_t)0xfffffL))
            break;
          delta = _lshift (ptr, delta, 1);
          if (__mcmp (delta, bs) > 0)
            goto drop_down;
          break;
        }
      if (i == 0)
        {
          if (dsign)
            {
              if (((rv.i[1]) & ((__uint32_t)0xfffffL)) == ((__uint32_t)0xfffffL)
                  && (rv.i[0]) == 0xffffffff)
                {
                  (rv.i[1]) = ((rv.i[1]) & ((__uint32_t)0x7ff00000L))
                    + ((__uint32_t)0x100000L)
                    ;
                  (rv.i[0]) = 0;
                  break;
                }
            }
          else if (!((rv.i[1]) & ((__uint32_t)0xfffffL)) && !(rv.i[0]))
            {
            drop_down:
              L = ((rv.i[1]) & ((__uint32_t)0x7ff00000L)) - ((__uint32_t)0x100000L);
              (rv.i[1]) = L | ((__uint32_t)0xfffffL);
              (rv.i[0]) = 0xffffffff;
              break;
            }
          if (!((rv.i[0]) & 1))
            break;
          if (dsign)
            rv.d += _ulp (rv.d);
          else
            {
              rv.d -= _ulp (rv.d);
              if (!rv.d)
                goto undfl;
            }
          break;
        }
      if ((aadj = _ratio (delta, bs)) <= 2.)
        {
          if (dsign)
            aadj = aadj1 = 1.;
          else if ((rv.i[0]) || (rv.i[1]) & ((__uint32_t)0xfffffL))
            {
              if ((rv.i[0]) == 1 && !(rv.i[1]))
                goto undfl;
              aadj = 1.;
              aadj1 = -1.;
            }
          else
            {
              if (aadj < 2. / 2)
                aadj = 1. / 2;
              else
                aadj *= 0.5;
              aadj1 = -aadj;
            }
        }
      else
        {
          aadj *= 0.5;
          aadj1 = dsign ? aadj : -aadj;
          if (0 == 0)
            aadj1 += 0.5;
        }
      y = (rv.i[1]) & ((__uint32_t)0x7ff00000L);
      if (y == ((__uint32_t)0x100000L) * (1024 + 1023 - 1))
        {
          rv0.d = rv.d;
          (rv.i[1]) -= 53 * ((__uint32_t)0x100000L);
          adj = aadj1 * _ulp (rv.d);
          rv.d += adj;
          if (((rv.i[1]) & ((__uint32_t)0x7ff00000L)) >=
              ((__uint32_t)0x100000L) * (1024 + 1023 - 53))
            {
              if ((rv0.i[1]) == (((__uint32_t)0xfffffL) | ((__uint32_t)0x100000L)*(1024+1023-1)) && (rv0.i[0]) == ((__uint32_t)0xffffffffL))
                goto ovfl;
              (rv.i[1]) = (((__uint32_t)0xfffffL) | ((__uint32_t)0x100000L)*(1024+1023-1));
              (rv.i[0]) = ((__uint32_t)0xffffffffL);
              goto cont;
            }
          else
            (rv.i[1]) += 53 * ((__uint32_t)0x100000L);
        }
      else
        {
          if (y <= (53 - 1) * ((__uint32_t)0x100000L) && aadj >= 1.)
            {
              aadj1 = (double) (int) (aadj + 0.5);
              if (!dsign)
                aadj1 = -aadj1;
            }
          adj = aadj1 * _ulp (rv.d);
          rv.d += adj;
        }
      z = (rv.i[1]) & ((__uint32_t)0x7ff00000L);
      if (y == z)
        {
          L = aadj;
          aadj -= L;
          if (dsign || (rv.i[0]) || (rv.i[1]) & ((__uint32_t)0xfffffL))
            {
              if (aadj < LITD(D_002BD498) || aadj > LITD(D_002BD4A0))
                break;
            }
          else if (aadj < LITD(D_002BD4A8))
            break;
        }
    cont:
      _Bfree (ptr, bb);
      _Bfree (ptr, bd);
      _Bfree (ptr, bs);
      _Bfree (ptr, delta);
    }
retfree:
  _Bfree (ptr, bb);
  _Bfree (ptr, bd);
  _Bfree (ptr, bs);
  _Bfree (ptr, bd0);
  _Bfree (ptr, delta);
ret:
  if (se)
    *se = (char *) s;
  return sign ? -rv.d : rv.d;
}

#undef ptr
#undef _reent
#undef double_union
#undef _Bigint
#undef __infinity
#undef LITD
#undef __mprec_tens
#undef memcpy
#undef __mprec_bigtens
#undef __mprec_tinytens
#undef _Balloc
#undef _Bfree
#undef _s2b
#undef _i2b
#undef _multiply
#undef _pow5mult
#undef _lshift
#undef __mcmp
#undef __mdiff
#undef _ulp
#undef _d2b
#undef _ratio

/* newlib strtod: string `arg0` as a double (the end into `arg1`). */
void func_0019D3E0(s32 arg0, s32 arg1) {
    func_0019C4C8(globals, arg0, arg1);
}

/* A newlib string-to-double helper (`s`, `ptr`). */
f32 func_0019D408(s32 s, s32 ptr) {
    return ((double (*)(s32, s32))func_0019D3E0)(s, ptr);
}

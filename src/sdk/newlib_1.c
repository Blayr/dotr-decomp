#include "common.h"
#include "sce/libc.h"

/* newlib abs: the absolute value of `arg0`. */
s32 abs(s32 arg0) {
    return arg0 < 0 ? -arg0 : arg0;
}

/* newlib atof: string `arg0` as a double (strtod). */
void atof(s32 arg0) {
    func_0019D3E0(arg0, 0);
}

/* newlib atoi: string `s` as an int (strtol, base 10). */
s32 atoi(const char *s) {
    return func_0019D750(s, NULL, 10);
}

/* newlib atol: string `arg0` as a long (strtol, base 10). */
void func_001950C8(s8 *arg0) {
    func_0019D750(arg0, NULL, 0xA);
}

/* newlib calloc: `arg0` items of `arg1` bytes, cleared. */
void func_001950E8(s32 arg0, s32 arg1) {
    func_00198840(arg1, arg0);
}

/* A newlib helper of two arguments (`arg0`, `arg1`). */
void func_00195108(s32 arg0, s32 arg1) {
    s32 var_a0;
    s32 var_v0;

    var_a0 = arg0;
    var_v0 = arg1 - 1;
    if (arg1 != 0) {
        do {
            var_v0 -= 1;
            *(s8 *)var_a0 = 0;
            var_a0 += 1;
        } while (var_v0 != -1);
    }
}

/* newlib _calloc_r: `n` items of `size` bytes from the heap, cleared (re-entrant). */
void *func_00195140(void *ptr, u32 n, u32 size) {
    cal_chunk *p;
    u32 csz;
    u32 sz = n * size;
    void *mem;

    mem = (void *)_malloc_r((s32)ptr, sz);
    if (mem == 0) {
        return 0;
    } else {
        p = (cal_chunk *)((char *)mem - 8);
        csz = p->size & ~(0x1 | 0x2);
        do {
            u32 mzsz = (csz - 4);
            if (mzsz <= 9 * sizeof(mzsz)) {
                u32 *mz = (u32 *)(mem);
                if (mzsz >= 5 * sizeof(mzsz)) {
                    *mz++ = 0;
                    *mz++ = 0;
                    if (mzsz >= 7 * sizeof(mzsz)) {
                        *mz++ = 0;
                        *mz++ = 0;
                        if (mzsz >= 9 * sizeof(mzsz)) {
                            *mz++ = 0;
                            *mz++ = 0;
                        }
                    }
                }
                *mz++ = 0;
                *mz++ = 0;
                *mz = 0;
            } else func_00198948((mem), 0, mzsz);
        } while (0);
        return mem;
    }
}

/* newlib _close_r: close() for re-entrancy record `ptr` (errno into it). */
s32 func_001951F8(s32 *ptr, s32 fd) {
    s32 ret;
    D_003512F8 = 0;
    if ((ret = ((s32 (*)(s32))close)(fd)) == -1 && D_003512F8 != 0)
        *ptr = D_003512F8;
    return ret;
}

#define QR_Storeinc(a, b, c) (((u16 *)a)[1] = (u16)b, ((u16 *)a)[0] = (u16)c, a++)

/* newlib dtoa quorem: divides big number `b` by `S` (one decimal digit). */
s32 func_00195250(i2b_Bigint *b, i2b_Bigint *S) {
    s32 n;
    s32 borrow, y;
    u32 carry, q, ys;
    u32 *bx, *bxe, *sx, *sxe;
    s32 z;
    u32 si, zs;

    n = S->wds;
    if (b->wds < n)
        return 0;
    sx = S->x;
    sxe = sx + --n;
    bx = b->x;
    bxe = bx + n;
    q = *bxe / (*sxe + 1);
    if (q) {
        borrow = 0;
        carry = 0;
        do {
            si = *sx++;
            ys = (si & 0xffff) * q + carry;
            zs = (si >> 16) * q + (ys >> 16);
            carry = zs >> 16;
            y = (*bx & 0xffff) - (ys & 0xffff) + borrow;
            borrow = y >> 16;
            z = (*bx >> 16) - (zs & 0xffff) + borrow;
            borrow = z >> 16;
            QR_Storeinc(bx, z, y);
        } while (sx <= sxe);
        if (!*bxe) {
            bx = b->x;
            while (--bxe > bx && !*bxe)
                --n;
            b->wds = n;
        }
    }
    if (func_001993C8((void *)b, (void *)S) >= 0) {
        q++;
        borrow = 0;
        carry = 0;
        bx = b->x;
        sx = S->x;
        do {
            si = *sx++;
            ys = (si & 0xffff) + carry;
            zs = (si >> 16) + (ys >> 16);
            carry = zs >> 16;
            y = (*bx & 0xffff) - (ys & 0xffff) + borrow;
            borrow = y >> 16;
            z = (*bx >> 16) - (zs & 0xffff) + borrow;
            borrow = z >> 16;
            QR_Storeinc(bx, z, y);
        } while (sx <= sxe);
        bx = b->x;
        bxe = bx + n;
        if (!*bxe) {
            while (--bxe > bx && !*bxe)
                --n;
            b->wds = n;
        }
    }
    return q;
}

/* _dtoa_r: newlib 1.9.0's stdlib/dtoa.c (David M. Gay, AT&T notice: see THIRD_PARTY_NOTICES.md) as cpp leaves it for this
   little-endian target, with main_034's mprec helpers, quorem (func_00195250 above), and the game's own
   strings and tens/bigtens tables. */
typedef struct dtoa_Bigint {
    struct dtoa_Bigint *_next;
    int _k, _maxwds, _sign, _wds;
    u32 _x[1];
} dtoa_Bigint;

typedef struct {
    u8 pad000[0x40];
    dtoa_Bigint *_result;
    int _result_k;
} dtoa_reent;

union dtoa_double {
    double d;
    u32 i[2];
};

extern char D_002BD1D0[]; /* "Infinity" */
extern char D_002BD1E0[]; /* "NaN" */
extern char D_002BD1E8[]; /* "0" */
extern double D_002BD350[]; /* bigtens */
#define __mprec_tens D_002BD288
#define __mprec_bigtens D_002BD350
#define _Bigint dtoa_Bigint
#define double_union dtoa_double
#define __int32_t s32
#define __uint32_t u32
#define __ULong u32
#define _Balloc(p, k) ((dtoa_Bigint *)_Balloc((p), (k)))
#define _Bfree(p, v) _Bfree((p), (v))
#define _multadd(p, b, m, a) ((dtoa_Bigint *)func_00198BB0((p), (i2b_Bigint *)(b), (m), (a)))
#define _i2b(p, i) ((dtoa_Bigint *)func_00198F28((p), (i)))
#define _multiply(p, a, b) ((dtoa_Bigint *)func_00198F60((p), (i2b_Bigint *)(a), (i2b_Bigint *)(b)))
#define _pow5mult(p, b, k) ((dtoa_Bigint *)func_00199170((p), (i2b_Bigint *)(b), (k)))
#define _lshift(p, b, k) ((dtoa_Bigint *)func_00199270((p), (i2b_Bigint *)(b), (k)))
#define __mcmp(a, b) func_001993C8((void *)(a), (void *)(b))
#define __mdiff(p, a, b) ((dtoa_Bigint *)func_00199430((p), (i2b_Bigint *)(a), (i2b_Bigint *)(b)))
#define _hi0bits(x) func_00198DE8(x)
#define _d2b(p, d, e, bits) func_00199828((p), (d), (e), (bits))
#define quorem(b, S) func_00195250((i2b_Bigint *)(b), (i2b_Bigint *)(S))

/* newlib _dtoa_r: double `_d` to decimal digits (mode, digit count; the decimal point and sign out). */
char *func_00195480(void *ptr, double _d , int mode , int ndigits , int *decpt , int *sign , char **rve)
{
  int bbits, b2, b5, be, dig, i, ieps, ilim, ilim0, ilim1, j, j1, k, k0,
    k_check, leftright, m2, m5, s2, s5, spec_case, try_quick;
  union double_union d, d2, eps;
  __int32_t L;
  int denorm;
  __ULong x;
  _Bigint *b, *b1, *delta, *mlo, *mhi, *S;
  double ds;
  char *s, *s0;
  d.d = _d;
  if (((dtoa_reent *)ptr)->_result)
    {
      ((dtoa_reent *)ptr)->_result->_k = ((dtoa_reent *)ptr)->_result_k;
      ((dtoa_reent *)ptr)->_result->_maxwds = 1 << ((dtoa_reent *)ptr)->_result_k;
      _Bfree (ptr, ((dtoa_reent *)ptr)->_result);
      ((dtoa_reent *)ptr)->_result = 0;
    }
  if ((d.i[1]) & ((__uint32_t)0x80000000L))
    {
      *sign = 1;
      (d.i[1]) &= ~((__uint32_t)0x80000000L);
    }
  else
    *sign = 0;
  if (((d.i[1]) & ((__uint32_t)0x7ff00000L)) == ((__uint32_t)0x7ff00000L))
    {
      *decpt = 9999;
      s =
 !(d.i[0]) && !((d.i[1]) & 0xfffff) ? D_002BD1D0 :
 D_002BD1E0;
      if (rve)
 *rve =
   s[3] ? s + 8 :
   s + 3;
      return s;
    }
  if (!d.d)
    {
      *decpt = 1;
      s = D_002BD1E8;
      if (rve)
 *rve = s + 1;
      return s;
    }
  b = _d2b (ptr, d.d, &be, &bbits);
  if ((i = (int) ((d.i[1]) >> 20 & (((__uint32_t)0x7ff00000L) >> 20))) != 0)
    {
      d2.d = d.d;
      (d2.i[1]) &= ((__uint32_t)0xfffffL);
      (d2.i[1]) |= ((__uint32_t)0x3ff00000L);
      i -= 1023;
      denorm = 0;
    }
  else
    {
      i = bbits + be + (1023 + (53 - 1) - 1);
      x = (i > 32) ? ((d.i[1]) << (64 - i)) | ((d.i[0]) >> (i - 32))
       : ((d.i[0]) << (32 - i));
      d2.d = x;
      (d2.i[1]) -= 31 * ((__uint32_t)0x100000L);
      i -= (1023 + (53 - 1) - 1) + 1;
      denorm = 1;
    }
  ds = (d2.d - 1.5) * 0.28952965460216801 + 0.17609125905580000349 + i * 0.30102999566398098;
  k = (int) ds;
  if (ds < 0. && ds != k)
    k--;
  k_check = 1;
  if (k >= 0 && k <= 22)
    {
      if (d.d < __mprec_tens[k])
 k--;
      k_check = 0;
    }
  j = bbits - i - 1;
  if (j >= 0)
    {
      b2 = 0;
      s2 = j;
    }
  else
    {
      b2 = -j;
      s2 = 0;
    }
  if (k >= 0)
    {
      b5 = 0;
      s5 = k;
      s2 += k;
    }
  else
    {
      b2 -= k;
      b5 = -k;
      s5 = 0;
    }
  if (mode < 0 || mode > 9)
    mode = 0;
  try_quick = 1;
  if (mode > 5)
    {
      mode -= 4;
      try_quick = 0;
    }
  leftright = 1;
  ilim = ilim1 = -1;
  switch (mode)
    {
    case 0:
    case 1:
      i = 18;
      ndigits = 0;
      break;
    case 2:
      leftright = 0;
    case 4:
      if (ndigits <= 0)
 ndigits = 1;
      ilim = ilim1 = i = ndigits;
      break;
    case 3:
      leftright = 0;
    case 5:
      i = ndigits + k + 1;
      ilim = i;
      ilim1 = i - 1;
      if (i <= 0)
 i = 1;
    }
  j = sizeof (__ULong);
  for (((dtoa_reent *)ptr)->_result_k = 0; sizeof (_Bigint) - sizeof (__ULong) + j <= i;
       j <<= 1)
    ((dtoa_reent *)ptr)->_result_k++;
  ((dtoa_reent *)ptr)->_result = _Balloc (ptr, ((dtoa_reent *)ptr)->_result_k);
  s = s0 = (char *) ((dtoa_reent *)ptr)->_result;
  if (ilim >= 0 && ilim <= 14 && try_quick)
    {
      i = 0;
      d2.d = d.d;
      k0 = k;
      ilim0 = ilim;
      ieps = 2;
      if (k > 0)
 {
   ds = __mprec_tens[k & 0xf];
   j = k >> 4;
   if (j & 0x10)
     {
       j &= 0x10 - 1;
       d.d /= __mprec_bigtens[5 - 1];
       ieps++;
     }
   for (; j; j >>= 1, i++)
     if (j & 1)
       {
  ieps++;
  ds *= __mprec_bigtens[i];
       }
   d.d /= ds;
 }
      else if ((j1 = -k) != 0)
 {
   d.d *= __mprec_tens[j1 & 0xf];
   for (j = j1 >> 4; j; j >>= 1, i++)
     if (j & 1)
       {
  ieps++;
  d.d *= __mprec_bigtens[i];
       }
 }
      if (k_check && d.d < 1. && ilim > 0)
 {
   if (ilim1 <= 0)
     goto fast_failed;
   ilim = ilim1;
   k--;
   d.d *= 10.;
   ieps++;
 }
      eps.d = ieps * d.d + 7.;
      (eps.i[1]) -= (53 - 1) * ((__uint32_t)0x100000L);
      if (ilim == 0)
 {
   S = mhi = 0;
   d.d -= 5.;
   if (d.d > eps.d)
     goto one_digit;
   if (d.d < -eps.d)
     goto no_digits;
   goto fast_failed;
 }
      if (leftright)
 {
   eps.d = 0.5 / __mprec_tens[ilim - 1] - eps.d;
   for (i = 0;;)
     {
       L = d.d;
       d.d -= L;
       *s++ = '0' + (int) L;
       if (d.d < eps.d)
  goto ret1;
       if (1. - d.d < eps.d)
  goto bump_up;
       if (++i >= ilim)
  break;
       eps.d *= 10.;
       d.d *= 10.;
     }
 }
      else
 {
   eps.d *= __mprec_tens[ilim - 1];
   for (i = 1;; i++, d.d *= 10.)
     {
       L = d.d;
       d.d -= L;
       *s++ = '0' + (int) L;
       if (i == ilim)
  {
    if (d.d > 0.5 + eps.d)
      goto bump_up;
    else if (d.d < 0.5 - eps.d)
      {
        while (*--s == '0');
        s++;
        goto ret1;
      }
    break;
  }
     }
 }
    fast_failed:
      s = s0;
      d.d = d2.d;
      k = k0;
      ilim = ilim0;
    }
  if (be >= 0 && k <= 14)
    {
      ds = __mprec_tens[k];
      if (ndigits < 0 && ilim <= 0)
 {
   S = mhi = 0;
   if (ilim < 0 || d.d <= 5 * ds)
     goto no_digits;
   goto one_digit;
 }
      for (i = 1;; i++)
 {
   L = d.d / ds;
   d.d -= L * ds;
   *s++ = '0' + (int) L;
   if (i == ilim)
     {
       d.d += d.d;
             if ((d.d > ds) || ((d.d == ds) && (L & 1)))
  {
  bump_up:
    while (*--s == '9')
      if (s == s0)
        {
   k++;
   *s = '0';
   break;
        }
    ++*s++;
  }
       break;
     }
   if (!(d.d *= 10.))
     break;
 }
      goto ret1;
    }
  m2 = b2;
  m5 = b5;
  mhi = mlo = 0;
  if (leftright)
    {
      if (mode < 2)
 {
   i =
     denorm ? be + (1023 + (53 - 1) - 1 + 1) :
     1 + 53 - bbits;
 }
      else
 {
   j = ilim - 1;
   if (m5 >= j)
     m5 -= j;
   else
     {
       s5 += j -= m5;
       b5 += j;
       m5 = 0;
     }
   if ((i = ilim) < 0)
     {
       m2 -= i;
       i = 0;
     }
 }
      b2 += i;
      s2 += i;
      mhi = _i2b (ptr, 1);
    }
  if (m2 > 0 && s2 > 0)
    {
      i = m2 < s2 ? m2 : s2;
      b2 -= i;
      m2 -= i;
      s2 -= i;
    }
  if (b5 > 0)
    {
      if (leftright)
 {
   if (m5 > 0)
     {
       mhi = _pow5mult (ptr, mhi, m5);
       b1 = _multiply (ptr, mhi, b);
       _Bfree (ptr, b);
       b = b1;
     }
         if ((j = b5 - m5) != 0)
     b = _pow5mult (ptr, b, j);
 }
      else
 b = _pow5mult (ptr, b, b5);
    }
  S = _i2b (ptr, 1);
  if (s5 > 0)
    S = _pow5mult (ptr, S, s5);
  spec_case = 0;
  if (mode < 2)
    {
      if (!(d.i[0]) && !((d.i[1]) & ((__uint32_t)0xfffffL))
   && (d.i[1]) & ((__uint32_t)0x7ff00000L)
 )
 {
   b2 += 1;
   s2 += 1;
   spec_case = 1;
 }
    }
  if ((i = ((s5 ? 32 - _hi0bits (S->_x[S->_wds - 1]) : 1) + s2) & 0x1f) != 0)
    i = 32 - i;
  if (i > 4)
    {
      i -= 4;
      b2 += i;
      m2 += i;
      s2 += i;
    }
  else if (i < 4)
    {
      i += 28;
      b2 += i;
      m2 += i;
      s2 += i;
    }
  if (b2 > 0)
    b = _lshift (ptr, b, b2);
  if (s2 > 0)
    S = _lshift (ptr, S, s2);
  if (k_check)
    {
      if (__mcmp (b, S) < 0)
 {
   k--;
   b = _multadd (ptr, b, 10, 0);
   if (leftright)
     mhi = _multadd (ptr, mhi, 10, 0);
   ilim = ilim1;
 }
    }
  if (ilim <= 0 && mode > 2)
    {
      if (ilim < 0 || __mcmp (b, S = _multadd (ptr, S, 5, 0)) <= 0)
 {
 no_digits:
   k = -1 - ndigits;
   goto ret;
 }
    one_digit:
      *s++ = '1';
      k++;
      goto ret;
    }
  if (leftright)
    {
      if (m2 > 0)
 mhi = _lshift (ptr, mhi, m2);
      mlo = mhi;
      if (spec_case)
 {
   mhi = _Balloc (ptr, mhi->_k);
   memcpy((char *)&mhi->_sign, (char *)&mlo->_sign, mlo->_wds*sizeof(__int32_t) + 2*sizeof(int));
   mhi = _lshift (ptr, mhi, 1);
 }
      for (i = 1;; i++)
 {
   dig = quorem (b, S) + '0';
   j = __mcmp (b, mlo);
   delta = __mdiff (ptr, S, mhi);
   j1 = delta->_sign ? 1 : __mcmp (b, delta);
   _Bfree (ptr, delta);
   if (j1 == 0 && !mode && !((d.i[0]) & 1))
     {
       if (dig == '9')
  goto round_9_up;
       if (j > 0)
  dig++;
       *s++ = dig;
       goto ret;
     }
         if ((j < 0) || ((j == 0) && !mode
       && !((d.i[0]) & 1)
           ))
     {
       if (j1 > 0)
  {
    b = _lshift (ptr, b, 1);
    j1 = __mcmp (b, S);
                 if (((j1 > 0) || ((j1 == 0) && (dig & 1)))
        && dig++ == '9')
      goto round_9_up;
  }
       *s++ = dig;
       goto ret;
     }
   if (j1 > 0)
     {
       if (dig == '9')
  {
  round_9_up:
    *s++ = '9';
    goto roundoff;
  }
       *s++ = dig + 1;
       goto ret;
     }
   *s++ = dig;
   if (i == ilim)
     break;
   b = _multadd (ptr, b, 10, 0);
   if (mlo == mhi)
     mlo = mhi = _multadd (ptr, mhi, 10, 0);
   else
     {
       mlo = _multadd (ptr, mlo, 10, 0);
       mhi = _multadd (ptr, mhi, 10, 0);
     }
 }
    }
  else
    for (i = 1;; i++)
      {
 *s++ = dig = quorem (b, S) + '0';
 if (i >= ilim)
   break;
 b = _multadd (ptr, b, 10, 0);
      }
  b = _lshift (ptr, b, 1);
  j = __mcmp (b, S);
  if ((j > 0) || ((j == 0) && (dig & 1)))
    {
    roundoff:
      while (*--s == '9')
 if (s == s0)
   {
     k++;
     *s++ = '1';
     goto ret;
   }
      ++*s++;
    }
  else
    {
      while (*--s == '0');
      s++;
    }
ret:
  _Bfree (ptr, S);
  if (mhi)
    {
      if (mlo && mlo != mhi)
 _Bfree (ptr, mlo);
      _Bfree (ptr, mhi);
    }
ret1:
  _Bfree (ptr, b);
  *s = 0;
  *decpt = k + 1;
  if (rve)
    *rve = s;
  return s0;
}

#undef _Bigint
#undef double_union
#undef __int32_t
#undef __uint32_t
#undef __ULong
#undef _Balloc
#undef _Bfree
#undef _multadd
#undef _i2b
#undef _multiply
#undef _pow5mult
#undef _lshift
#undef __mcmp
#undef __mdiff
#undef _hi0bits
#undef _d2b
#undef quorem
#undef __mprec_tens
#undef __mprec_bigtens

/* newlib __env_lock: locks the environment (nothing to do here). */
void __env_lock(void) {
}

/* newlib __env_unlock: unlocks the environment (nothing to do here). */
void __env_unlock(void) {
}

/* newlib __errno: the address of errno. */
s32 __errno(void) {
    return D_0028FA98;
}

typedef struct ff_reent { u8 pad0[0x38]; s32 __sdidinit; } ff_reent;
typedef struct ff_sbuf { u8 *_base; s32 _size; } ff_sbuf;
typedef struct ff_FILE {
    u8 *_p;
    s32 _r;
    s32 _w;
    s16 _flags;
    s16 _file;
    ff_sbuf _bf;
    s32 _lbfsize;
    void *_cookie;
    s32 (*_read)(void *, char *, s32);
    s32 (*_write)(void *, const char *, s32);
    u8 pad28[0x2C];
    ff_reent *_data;
} ff_FILE;

/* newlib fflush: writes out stream `arg0`'s buffer (all streams for NULL). */
s32 fflush(nl_FILE *arg0) {
    ff_FILE *fp = (ff_FILE *)arg0;
    u8 *p;
    s32 n, t;

    if (fp == NULL)
        return _fwalk((u8 *)D_0028FA98, fflush);

    do {
        if (fp->_data == 0)
            fp->_data = (ff_reent *)D_0028FA98;
        if (!fp->_data->__sdidinit)
            __sinit(fp->_data);
    } while (0);

    t = fp->_flags;
    if ((t & 8) == 0 || (p = fp->_bf._base) == NULL)
        return 0;
    n = fp->_p - p;

    fp->_p = p;
    fp->_w = t & (1 | 2) ? 0 : fp->_bf._size;

    while (n > 0) {
        t = (*fp->_write)(fp->_cookie, (char *)p, n);
        if (t <= 0) {
            fp->_flags |= 0x40;
            return -1;
        }
        p += t;
        n -= t;
    }
    return 0;
}

/* newlib stdio: sets up standard stream `arg0` (flags `arg1`, file `arg2`). */
void std(void *arg0, s16 arg1, s16 arg2, s32 arg3) {
    (*(s32 *)((u8 *)arg0 + 0x54)) = arg3;
    (*(s16 *)((u8 *)arg0 + 0xC)) = arg1;
    (*(s16 *)((u8 *)arg0 + 0xE)) = arg2;
    (*(s32 **)((u8 *)arg0 + 0x20)) = &__sread;
    (*(s32 **)((u8 *)arg0 + 0x24)) = &__swrite;
    (*(s32 **)((u8 *)arg0 + 0x28)) = &__sseek;
    (*(void (**)(void *))((u8 *)arg0 + 0x2C)) = __sclose;
    (*(s32 *)((u8 *)arg0 + 4)) = 0;
    (*(s32 *)((u8 *)arg0 + 8)) = 0;
    (*(s32 *)((u8 *)arg0 + 0x10)) = 0;
    (*(s32 *)((u8 *)arg0 + 0x14)) = 0;
    (*(s32 *)((u8 *)arg0 + 0x18)) = 0;
    (*(void **)((u8 *)arg0 + 0x1C)) = arg0;
    (*(s32 *)arg0) = 0;
}

/* newlib stdio: allocates `n` more FILE records (re-entrancy record `d`). */
nl_mglue *__sfmoreglue(s32 d, s32 n) {
    nl_mglue *g;
    nl_mFILE *p;

    g = (nl_mglue *)_malloc_r(d, sizeof(*g) + n * sizeof(nl_mFILE));
    if (g == NULL)
        return NULL;
    p = (nl_mFILE *)(g + 1);
    g->_next = NULL;
    g->_niobs = n;
    g->_iobs = p;
    func_00198948(p, 0, n * sizeof(nl_mFILE));
    return g;
}

typedef struct sf_sbuf { u8 *_base; s32 _size; } sf_sbuf;
typedef struct sf_FILE {
    u8 *_p;
    s32 _r;
    s32 _w;
    s16 _flags;
    s16 _file;
    sf_sbuf _bf;
    s32 _lbfsize;
    u8 pad1C[0x14];
    sf_sbuf _ub;
    u8 pad38[0xC];
    sf_sbuf _lb;
    u8 pad4C[0x8];
    void *_data;
} sf_FILE;
typedef struct sf_glue { struct sf_glue *_next; s32 _niobs; sf_FILE *_iobs; } sf_glue;
typedef struct sf_reent { s32 _errno; u8 pad04[0x34]; s32 __sdidinit; u8 pad3C[0x19C]; sf_glue __sglue; } sf_reent;

/* newlib stdio: a free FILE record (allocating more if needed). */
void *__sfp(void *arg0) {
    sf_reent *d = arg0;
    sf_FILE *fp;
    s32 n;
    sf_glue *g;

    if (!d->__sdidinit)
        __sinit(d);
    for (g = &d->__sglue;; g = g->_next) {
        for (fp = g->_iobs, n = g->_niobs; --n >= 0; fp++)
            if (fp->_flags == 0)
                goto found;
        if (g->_next == NULL && (g->_next = (sf_glue *)__sfmoreglue((s32)d, 4)) == NULL)
            break;
    }
    d->_errno = 12;
    return NULL;

found:
    fp->_flags = 1;
    fp->_p = NULL;
    fp->_w = 0;
    fp->_r = 0;
    fp->_bf._base = NULL;
    fp->_bf._size = 0;
    fp->_lbfsize = 0;
    fp->_file = -1;
    fp->_ub._base = NULL;
    fp->_ub._size = 0;
    fp->_lb._base = NULL;
    fp->_lb._size = 0;
    fp->_data = d;
    return fp;
}

/* newlib _cleanup_r: flushes every stream of re-entrancy record `ptr`. */
s32 func_001969F0(s32 ptr) {
    return _fwalk(ptr, fflush);
}

/* newlib _cleanup: flushes every stream (not the file library's _cleanup at 0x0017F738). */
void func_00196A10(void) {
    func_001969F0(D_0028FA98);
}

/* newlib stdio: sets up stdin, stdout and stderr once. */
void __sinit(void *arg0) {
    void *temp_s1;

    temp_s1 = arg0 + 0x1E4;
    (*(s32 (**)(s32))((u8 *)arg0 + 0x3C)) = func_001969F0;
    (*(s32 *)((u8 *)arg0 + 0x38)) = 1;
    std(temp_s1, 4, 0, arg0);
    std(arg0 + 0x23C, 9, 1, arg0);
    std(arg0 + 0x294, 0xA, 2, arg0);
    (*(s32 *)((u8 *)arg0 + 0x1D8)) = 0;
    (*(void **)((u8 *)arg0 + 0x1E0)) = temp_s1;
    (*(s32 *)((u8 *)arg0 + 0x1DC)) = 3;
}

/* newlib fread: reads `count` items of `size` bytes into `buf` from stream `arg3`. */
u32 fread(void *buf, u32 size, u32 count, void *arg3) {
    fr_FILE *fp = arg3;
    u32 resid;
    char *p;
    s32 r;
    u32 total;

    if ((resid = count * size) == 0)
        return 0;
    if (fp->_r < 0)
        fp->_r = 0;
    total = resid;
    p = buf;
    while (resid > (r = fp->_r)) {
        func_00198790(p, fp->_p, r);
        fp->_p += r;
        p += r;
        resid -= r;
        if (func_0019AC68(fp)) {
            return (total - resid) / size;
        }
    }
    func_00198790(p, fp->_p, resid);
    fp->_r -= resid;
    fp->_p += resid;
    return count;
}

#define malloc_unlock(r) ((void (*)(s32))func_00198A88)(r)
#define SIZE_SZ (sizeof(INTERNAL_SIZE_T))
#define PREV_INUSE 0x1
#define SIZE_BITS 0x3
#define chunksize(p) ((p)->size & ~(SIZE_BITS))
#define set_head(p, s) ((p)->size = (s))
#define set_foot(p, s) (((mchunkptr)((char *)(p) + (s)))->prev_size = (s))
#define chunk_at_offset(p, s) ((mchunkptr)(((char *)(p)) + (s)))
#define bin_at(i) ((mchunkptr)((char *)&(D_0028FAA8[2 * (i) + 2]) - 2 * SIZE_SZ))
#define top (bin_at(0)->fd)
#define last_remainder (bin_at(1))
#define binblocks (bin_at(0)->size)
#define MAX_SMALLBIN_SIZE 512
#define BINBLOCKWIDTH 4
#define smallbin_index(sz) (((unsigned long)(sz)) >> 3)
#define bin_index(sz)                                                                              \
    ((((sz) >> 9) == 0)      ? ((sz) >> 3)                                                         \
     : (((sz) >> 9) <= 4)    ? 56 + ((sz) >> 6)                                                    \
     : (((sz) >> 9) <= 20)   ? 91 + ((sz) >> 9)                                                    \
     : (((sz) >> 9) <= 84)   ? 110 + ((sz) >> 12)                                                  \
     : (((sz) >> 9) <= 340)  ? 119 + ((sz) >> 15)                                                  \
     : (((sz) >> 9) <= 1364) ? 124 + ((sz) >> 18)                                                  \
                             : 126)
#define idx2binblock(ix) ((unsigned long)1 << ((ix) / BINBLOCKWIDTH))
#define mark_binblock(ii) (binblocks |= idx2binblock(ii))
#define unlink(P, BK, FD)                                                                          \
    {                                                                                              \
        BK = P->bk;                                                                                \
        FD = P->fd;                                                                                \
        FD->bk = BK;                                                                               \
        BK->fd = FD;                                                                               \
    }
#define link_last_remainder(P)                                                                     \
    {                                                                                              \
        last_remainder->fd = last_remainder->bk = P;                                               \
        P->fd = P->bk = last_remainder;                                                            \
    }
#define frontlink(P, S, IDX, BK, FD)                                                               \
    {                                                                                              \
        if (S < MAX_SMALLBIN_SIZE) {                                                               \
            IDX = smallbin_index(S);                                                               \
            mark_binblock(IDX);                                                                    \
            BK = bin_at(IDX);                                                                      \
            FD = BK->fd;                                                                           \
            P->bk = BK;                                                                            \
            P->fd = FD;                                                                            \
            FD->bk = BK->fd = P;                                                                   \
        } else {                                                                                   \
            IDX = bin_index(S);                                                                    \
            BK = bin_at(IDX);                                                                      \
            FD = BK->fd;                                                                           \
            if (FD == BK) {                                                                        \
                mark_binblock(IDX);                                                                \
            } else {                                                                               \
                while (FD != BK && S < chunksize(FD))                                              \
                    FD = FD->fd;                                                                   \
                BK = FD->bk;                                                                       \
            }                                                                                      \
            P->bk = BK;                                                                            \
            P->fd = FD;                                                                            \
            FD->bk = BK->fd = P;                                                                   \
        }                                                                                          \
    }
#define MINSIZE 16
#define mem2chunk(mem) ((mchunkptr)((char *)(mem) - 2 * SIZE_SZ))
#define inuse_bit_at_offset(p, s) (((mchunkptr)((char *)(p) + (s)))->size & PREV_INUSE)

/* _free_r (newlib 1.9.0 mallocr.c): adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

void _free_r(s32 self, void *mem) {
    extern s32 _malloc_trim_r(s32, u32);
    mchunkptr p;
    INTERNAL_SIZE_T hd;
    INTERNAL_SIZE_T sz;
    s32 idx;
    mchunkptr next;
    INTERNAL_SIZE_T nextsz;
    INTERNAL_SIZE_T prevsz;
    mchunkptr bck;
    mchunkptr fwd;
    s32 islr;

    if (mem == 0) {
        return;
    }

    func_00198A08(self);
    p = mem2chunk(mem);
    hd = p->size;

    sz = hd & ~PREV_INUSE;
    next = chunk_at_offset(p, sz);
    nextsz = chunksize(next);

    if (next == top) {
        sz += nextsz;

        if (!(hd & PREV_INUSE)) {
            prevsz = p->prev_size;
            p = chunk_at_offset(p, -((long)prevsz));
            sz += prevsz;
            unlink(p, bck, fwd);
        }

        {
            unsigned long thr = D_0028FEB0;
            set_head(p, sz | PREV_INUSE);
            top = p;
            if ((unsigned long)(sz) >= thr) {
            _malloc_trim_r(self, D_0028FEB8);
        }
        }
        malloc_unlock(self);
        return;
    }

    set_head(next, nextsz);

    islr = 0;

    if (!(hd & PREV_INUSE)) {
        prevsz = p->prev_size;
        p = chunk_at_offset(p, -((long)prevsz));
        sz += prevsz;

        if (p->fd == last_remainder) {
            islr = 1;
        } else {
            unlink(p, bck, fwd);
        }
    }

    if (!(inuse_bit_at_offset(next, nextsz))) {
        sz += nextsz;

        if (!islr && next->fd == last_remainder) {
            islr = 1;
            link_last_remainder(p);
        } else {
            unlink(next, bck, fwd);
        }
    }

    set_head(p, sz | PREV_INUSE);
    set_foot(p, sz);
    if (!islr) {
        frontlink(p, sz, idx, bck, fwd);
    }

    malloc_unlock(self);
}

#undef malloc_unlock
#undef SIZE_SZ
#undef PREV_INUSE
#undef SIZE_BITS
#undef chunksize
#undef set_head
#undef set_foot
#undef chunk_at_offset
#undef bin_at
#undef top
#undef last_remainder
#undef binblocks
#undef MAX_SMALLBIN_SIZE
#undef BINBLOCKWIDTH
#undef smallbin_index
#undef bin_index
#undef idx2binblock
#undef mark_binblock
#undef unlink
#undef link_last_remainder
#undef frontlink
#undef MINSIZE
#undef mem2chunk
#undef inuse_bit_at_offset

#define SIZE_SZ (sizeof(INTERNAL_SIZE_T))
#define PREV_INUSE 0x1
#define SIZE_BITS 0x3
#define MINSIZE 16
#define chunksize(p) ((p)->size & ~(SIZE_BITS))
#define set_head(p, s) ((p)->size = (s))
#define bin_at(i) ((mchunkptr)((char *)&(D_0028FAA8[2 * (i) + 2]) - 2 * SIZE_SZ))
#define top (bin_at(0)->fd)

/* _malloc_trim_r (newlib 1.9.0 mallocr.c): adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

s32 _malloc_trim_r(s32 reent_ptr, u32 pad) {
    long top_size;
    long extra;
    char *current_brk;
    char *new_brk;
    unsigned long pagesz = 4096;

    func_00198A08(reent_ptr);
    top_size = chunksize(top);
    extra = ((top_size - pad - MINSIZE + (pagesz - 1)) / pagesz - 1) * pagesz;

    if (extra < (long)pagesz) {
        ((void (*)(s32))func_00198A88)(reent_ptr);
        return 0;
    } else {
        current_brk = (char *)(func_0019B0A0((s32 *)reent_ptr, 0));
        if (current_brk != (char *)(top) + top_size) {
            ((void (*)(s32))func_00198A88)(reent_ptr);
            return 0;
        } else {
            new_brk = (char *)(func_0019B0A0((s32 *)reent_ptr, -extra));
            if (new_brk == (char *)(-1)) {
                current_brk = (char *)(func_0019B0A0((s32 *)reent_ptr, 0));
                top_size = current_brk - (char *)top;
                if (top_size >= (long)MINSIZE) {
                    D_0028FED8.arena = current_brk - D_0028FEC0;
                    set_head(top, top_size | PREV_INUSE);
                }
                ((void (*)(s32))func_00198A88)(reent_ptr);
                return 0;
            } else {
                set_head(top, (top_size - extra) | PREV_INUSE);
                D_0028FED8.arena -= extra;
                ((void (*)(s32))func_00198A88)(reent_ptr);
                return 1;
            }
        }
    }
}

#undef SIZE_SZ
#undef PREV_INUSE
#undef SIZE_BITS
#undef MINSIZE
#undef chunksize
#undef set_head
#undef bin_at
#undef top

/* newlib _fstat_r: fstat() for re-entrancy record `ptr` (errno into it). */
s32 _fstat_r(s32 *ptr, s32 fd, void *st) {
    s32 ret;
    D_003512F8 = 0;
    if ((ret = fstat(fd, st)) == -1 && D_003512F8 != 0)
        *ptr = D_003512F8;
    return ret;
}

#define MIN_001970A8(a, b) ((a) < (b) ? (a) : (b))
#define COPY_001970A8(n) (void)((void *(*)(void *, const void *, s32))func_00198840)((void *)fp->p, (void *)p, (int)(n))
#define GETIOV_001970A8(extra_work)                                                                \
    while (len == 0) {                                                                             \
        extra_work;                                                                                \
        p = iov->iov_base;                                                                         \
        len = iov->iov_len;                                                                        \
        iov++;                                                                                     \
    }

/* __sfvwrite (newlib 1.9.0 fvwrite.c): adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

s32 __sfvwrite(void *arg0, void *arg1) {
    extern void *func_00198618();
    Fil *fp = arg0;
    struct __suio *uio = arg1;
    unsigned int len;
    const char *p;
    struct __siov *iov;
    int w, s;
    char *nl;
    int nlknown, nldist;

    if ((len = uio->uio_resid) == 0) {
        return 0;
    }
    if (((fp->flags & 0x0008) == 0 || fp->bf.base == 0) && func_001A04D8(fp)) {
        return -1;
    }

    iov = uio->uio_iov;
    len = 0;
    w = 0;
    if (fp->flags & 0x0002) {
        do {
            GETIOV_001970A8(;);
            w = (*fp->write)(fp->cookie, p, MIN_001970A8(len, 1024));
            if (w <= 0) {
                goto err;
            }
            p += w;
            len -= w;
        } while ((uio->uio_resid -= w) != 0);
    } else if ((fp->flags & 0x0001) == 0) {
        do {
            GETIOV_001970A8(;);
            w = fp->w;
            if (fp->flags & 0x0200) {
                if (len < w) {
                    w = len;
                }
                COPY_001970A8(w);
                fp->w -= w;
                fp->p += w;
                w = len;
            } else if (fp->p > fp->bf.base && len > w) {
                COPY_001970A8(w);
                fp->p += w;
                if (fflush((nl_FILE *)fp)) {
                    goto err;
                }
            } else if (len >= (w = fp->bf.size)) {
                w = (*fp->write)(fp->cookie, p, w);
                if (w <= 0) {
                    goto err;
                }
            } else {
                w = len;
                COPY_001970A8(w);
                fp->w -= w;
                fp->p += w;
            }
            p += w;
            len -= w;
        } while ((uio->uio_resid -= w) != 0);
    } else {
        nlknown = 0;
        do {
            GETIOV_001970A8(nlknown = 0);
            if (!nlknown) {
                nl = ((void *(*)(const void *, s32, u32))func_00198618)((void *)p, '\n', len);
                nldist = nl ? nl + 1 - p : len + 1;
                nlknown = 1;
            }
            s = MIN_001970A8(len, nldist);
            w = fp->w + fp->bf.size;
            if (fp->p > fp->bf.base && s > w) {
                COPY_001970A8(w);
                fp->p += w;
                if (fflush((nl_FILE *)fp)) {
                    goto err;
                }
            } else if (s >= (w = fp->bf.size)) {
                w = (*fp->write)(fp->cookie, p, w);
                if (w <= 0) {
                    goto err;
                }
            } else {
                w = s;
                COPY_001970A8(w);
                fp->w -= w;
                fp->p += w;
            }
            if ((nldist -= w) == 0) {
                if (fflush((nl_FILE *)fp)) {
                    goto err;
                }
                nlknown = 0;
            }
            p += w;
            len -= w;
        } while ((uio->uio_resid -= w) != 0);
    }
    return 0;

err:
    fp->flags |= 0x0040;
    return -1;
}

#undef MIN_001970A8
#undef COPY_001970A8
#undef GETIOV_001970A8

/* newlib stdio: calls `function` for every open stream. */
s32 _fwalk(u8 *ptr, s32 (*function)(nl_FILE *)) {
    nl_FILE *fp;
    s32 n, ret = 0;
    nl_glue *g;

    for (g = (nl_glue *)(ptr + 0x1D8); g != NULL; g = g->_next)
        for (fp = g->_iobs, n = g->_niobs; --n >= 0; fp++)
            if (fp->_flags != 0)
                ret |= (*function)(fp);
    return ret;
}

/* newlib _findenv: finds environment setting `arg0` (its index into `arg1`). */
void _findenv(s32 arg0, s32 arg1) {
    _findenv_r(D_0028FA98, arg0, arg1);
}

/* newlib getenv: the value of environment setting `arg0`, or NULL. */
u8 *getenv(s32 arg0) {
    s32 sp0[4];
    return _findenv_r(D_0028FA98, arg0, (s32) sp0);
}

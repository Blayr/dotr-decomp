#include "common.h"
#include "sce/libc.h"

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

s32 func_0019DA00(void *arg0) {
    sm_FILE *fp = arg0;
    s32 i;
    u8 *p;

    if (fp->_ub._base == fp->_ubuf) {
        if ((p = (u8 *)_malloc_r((s32)fp->_data, 1024)) == NULL)
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
            __sinit(fp->_data);
    } while (0);

    fp->_flags &= ~0x20;

    if ((fp->_flags & 4) == 0) {
        if ((fp->_flags & 0x10) == 0)
            return -1;
        if (fp->_flags & 8) {
            if (fflush((nl_FILE *)fp))
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

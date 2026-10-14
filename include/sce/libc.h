#ifndef SCE_LIBC_H
#define SCE_LIBC_H

/* newlib's malloc arena records (mallocr.c) as the ICO decompilation rebuilt them, via kfiv-decomp
 * (MIT); newlib's notices are in THIRD_PARTY_NOTICES.md. `long` is 64-bit in this C library's
 * build, so the arena statics are 8 bytes apart. */
typedef unsigned int INTERNAL_SIZE_T;

struct malloc_chunk {
    INTERNAL_SIZE_T prev_size;
    INTERNAL_SIZE_T size;
    struct malloc_chunk *fd;
    struct malloc_chunk *bk;
};

typedef struct malloc_chunk *mchunkptr;

struct mallinfo {
    int arena;
    int ordblks;
    int smblks;
    int hblks;
    int hblkhd;
    int usmblks;
    int fsmblks;
    int uordblks;
    int fordblks;
    int keepcost;
};

/* the stdio stream record of this libc */
typedef struct {
    u8 *base; /* 0x0 */
    int size; /* 0x4 */
} Sbuf;

struct Reent;

typedef struct Fil {
    u8 *p;                                              /* 0x00 */
    int r;                                              /* 0x04 */
    int w;                                              /* 0x08 */
    short flags;                                        /* 0x0C */
    short file;                                         /* 0x0E */
    Sbuf bf;                                            /* 0x10 */
    int lbfsize;                                        /* 0x18 */
    void *cookie;                                       /* 0x1C */
    int (*read)(void *cookie, char *buf, int n);        /* 0x20 */
    int (*write)(void *cookie, const char *buf, int n); /* 0x24 */
    long (*seek)(void *cookie, long off, int whence);   /* 0x28 */
    int (*close)(void *cookie);                         /* 0x2C */
    Sbuf ub;                                            /* 0x30 */
    u8 *up;                                             /* 0x38 */
    int ur;                                             /* 0x3C */
    u8 ubuf[3];                                         /* 0x40 */
    u8 nbuf[1];                                         /* 0x43 */
    Sbuf lb;                                            /* 0x44 */
    int blksize;                                        /* 0x4C */
    int offset;                                         /* 0x50 */
    struct Reent *data;                                 /* 0x54 */
} Fil;

/* the write requests __sfvwrite takes */
struct __siov {
    const char *iov_base;
    int iov_len;
};

struct __suio {
    struct __siov *uio_iov;
    int uio_iovcnt;
    int uio_resid;
};

extern mchunkptr D_0028FAA8[];     /* __malloc_av_, the bins */
extern unsigned long D_0028FEB0;   /* __malloc_trim_threshold */
extern unsigned long D_0028FEB8;   /* __malloc_top_pad */
extern char *D_0028FEC0;           /* __malloc_sbrk_base */
extern unsigned long D_0028FEC8;   /* __malloc_max_sbrked_mem */
extern unsigned long D_0028FED0;   /* __malloc_max_total_mem */
extern struct mallinfo D_0028FED8; /* __malloc_current_mallinfo */

#endif

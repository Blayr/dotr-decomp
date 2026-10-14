#ifndef SCE_LIBKERNL_H
#define SCE_LIBKERNL_H

/* Sony libkernl records (EE kernel, SIF, file stub). Adapted from the ICO decompilation via
 * kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md. */

/* the EE kernel's semaphore and thread parameter records */
struct SemaParam {
    s32 currentCount;    /* 0x00 */
    s32 maxCount;        /* 0x04 */
    s32 initCount;       /* 0x08 */
    s32 numWaitThreads;  /* 0x0C */
    u32 attr;            /* 0x10 */
    u32 option;          /* 0x14 */
};

struct ThreadParam {
    s32 status;            /* 0x00 */
    void (*entry)(void *); /* 0x04 */
    void *stack;           /* 0x08 */
    s32 stackSize;         /* 0x0C */
    void *gpReg;           /* 0x10 */
    s32 initPriority;      /* 0x14 */
    s32 currentPriority;   /* 0x18 */
    u32 attr;              /* 0x1C */
    u32 option;            /* 0x20 */
    s32 waitType;          /* 0x24 */
    s32 waitId;            /* 0x28 */
    s32 wakeupCount;       /* 0x2C */
};

/* one SIF DMA transfer; src and dest are bus addresses held as numbers */
typedef struct sceSifDmaData {
    u32 src;
    u32 dest;
    s32 size;
    union {
        s32 attr;
    } u;
} sceSifDmaData;

typedef void (*sceSifEndFunc)(void *param);
typedef void *(*sceSifRpcFunc)(s32 fno, void *buff, s32 size);

/* an EE client of an IOP RPC server */
typedef struct sceSifRpcClientData {
    void *pkt;             /* 0x00 */
    s32 pid;               /* 0x04 */
    s32 sema;              /* 0x08 */
    u32 mode;              /* 0x0C */
    u32 command;           /* 0x10 */
    u32 buff;              /* 0x14 */
    u32 cbuff;             /* 0x18 */
    sceSifEndFunc endFunc; /* 0x1C */
    void *endParam;        /* 0x20 */
    u32 serve;             /* 0x24 */
} sceSifRpcClientData;

typedef struct sceSifReceiveData {
    void *pkt;  /* 0x00 */
    s32 pid;    /* 0x04 */
    s32 sema;   /* 0x08 */
    u32 mode;   /* 0x0C */
    void *src;  /* 0x10 */
    void *dest; /* 0x14 */
    s32 size;   /* 0x18 */
} sceSifReceiveData;

typedef struct sceSifServeData {
    u32 command;                  /* 0x00 */
    sceSifRpcFunc func;           /* 0x04 */
    void *buff;                   /* 0x08 */
    s32 size;                     /* 0x0C */
    sceSifRpcFunc cfunc;          /* 0x10 */
    void *cbuff;                  /* 0x14 */
    s32 csize;                    /* 0x18 */
    sceSifRpcClientData *client;  /* 0x1C */
    void *paddr;                  /* 0x20 */
    u32 fno;                      /* 0x24 */
    void *receive;                /* 0x28 */
    s32 rsize;                    /* 0x2C */
    s32 rmode;                    /* 0x30 */
    u32 rid;                      /* 0x34 */
    struct sceSifServeData *link; /* 0x38 */
    struct sceSifServeData *next; /* 0x3C */
    struct sceSifQueueData *base; /* 0x40 */
} sceSifServeData;

typedef struct sceSifQueueData {
    s32 key;                       /* 0x00 */
    s32 active;                    /* 0x04 */
    struct sceSifServeData *link;  /* 0x08 */
    struct sceSifServeData *start; /* 0x0C */
    struct sceSifServeData *end;   /* 0x10 */
    struct sceSifQueueData *next;  /* 0x14 */
} sceSifQueueData;

/* the SIF command packet the EE sends the IOP kernel to ask for a reset */
typedef enum { SIF_CMD_DIAG = 0 } SifCmdId;

typedef struct {
    u64 psize : 8;
    u64 dsize : 24;
    void *dest;
    SifCmdId cid;
    u32 opt;
} SifCmdHeader;

typedef struct {
    SifCmdHeader header;
    s32 arglen;
    s32 mode;
    char arg[80];
} SifCmdResetData;

extern SifCmdResetData D_00314040; /* the reset packet */

/* the file stub (filestub.o): the requests the FS calls send in its send buffer */
typedef struct {
    s32 sema;
    s32 *result;
    s32 mode;
    s32 fd;
    void *buf;
    s32 nbyte;
    s32 pad6;
    s32 iob;
} FsReadReq;

typedef struct {
    s32 sema;
    s32 *result;
    s32 mode;
    s32 fd;
    void *buf;
    s32 nbyte;
    s32 headLen;
    char head[16];
    s32 iob;
} FsWriteReq;

typedef struct {
    s32 sema;
    s32 *result;
    s32 mode;
    void *stat;
    u8 name[0x400];
} FsGetstatReq;

typedef struct {
    s32 sema;
    s32 *result;
    s32 mode;
    u32 len;
    void *buf;
    char name[0x400];
} FsReadlinkReq;

/* the 16-byte descriptor record of the iob table: the driver handle and the in-use word */
typedef struct {
    s32 fd;
    s32 inuse;
    s32 pad8[2];
} SceIob;

/* records the FS calls copy whole */
typedef struct { char v[4]; } SceFsVersion;
typedef struct { char v[0x144]; } SceFsDirent;
typedef struct { char v[0x40]; } SceFsStatRec;
typedef struct { char b[1024]; } SceIoctlArg;

/* eeloadfile.o: the loadfile RPC buffer (0x200 bytes sent) and its 0xFC-byte argument block */
typedef struct { char v[0xFC]; } SceLfArgBuf;

typedef struct {
    s32 addr;
    s32 arglen;
    char name[0xFC];
    SceLfArgBuf args;
} SceLfRpcBuf;

typedef struct FioReq_00181140 {
    s32 sema;
    s32 *result;
    s32 size;
    s32 arg;
} FioReq_00181140;

/* whether a descriptor was opened no-wait (0x8000 in the open mode, the in-use word's low half) */
static inline s32 sceFsIsNowait(u16 mode) {
    return mode & 0x8000;
}

extern FioReq_00181140 D_003128C0; /* the RPC send buffer */
extern volatile s32 D_0028CA20[32]; /* the async request slots, -1 when free */
extern void *D_00312884;            /* the ioctl caller's argument pointer */
extern char D_00313540[0x440];      /* the reply packet the IOP writes */
extern char D_00313980[0x200];      /* the iob table */

#endif

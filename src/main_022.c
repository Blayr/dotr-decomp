#include "common.h"

/* newlib system call: does nothing. */
s32 ioctl(void) {
    return -1;
}

/* newlib system call: no seeking here (-1). */
s32 lseek(void) {
    return -1;
}

/* newlib system call: grows the heap by `incr` bytes, up to EndOfHeap. */
u32 sbrk(s32 incr) {
    s32 eie, st, old, new;
    __asm__ volatile("mfc0\t%0, $12" : "=r"(eie));
    eie &= 0x10000;
    if (eie) {
    again:
        __asm__ volatile("di");
        __asm__ volatile("sync.p");
        __asm__ volatile("mfc0\t%0, $12" : "=r"(st));
        if (st & 0x10000) goto again;
    }
    new = D_0028C254 + incr;
    if (EndOfHeap() < (u32)new) {
        *(s32 *)__errno() = 12;
        if (eie) {
            __asm__ volatile("ei");
        }
        return 0xFFFFFFFF;
    }
    old = D_0028C254;
    D_0028C254 = new;
    if (eie) {
        __asm__ volatile("ei");
    }
    return old;
}

/* newlib system call: whether a file is a terminal. */
s32 isatty(void) {
    return 1;
}

/* newlib system call: a file's status into `st` (always a character device). */
s32 fstat(s32 fd, void *st) {
    (*(s64 *)((u8 *)st + 0x48)) = 0;
    (*(s32 *)((u8 *)st + 4)) = 0x2000;
    return 0;
}

/* newlib system call: the process id (always 1). */
s32 getpid(void) {
    return 1;
}

/* newlib system call: ends the program with signal `sig`. */
s32 kill(s32 pid, s32 sig) {
    if (pid == 1) {
        func_001847B0(sig);
    }
    return 0;
}

/* newlib system call: no files here (sets errno). */
s32 stat(void) {
    *(s32 *)__errno() = 5;
    return -1;
}

/* newlib system call: no files here (errno 5, -1). */
s32 unlink(void) {
    *(s32 *)__errno() = 5;
    return -1;
}

/* _sceSDC: Sony's hand-written libkernl assembly, kept as asm (kfiv-decomp, MIT, writes it as an asm block in src/sce/libkernl/cache.c; see THIRD_PARTY_NOTICES.md) */

void _sceSDC(u32 start, u32 end) {
    __asm__ __volatile__(
        "	.set	noreorder\n"
        "	lui	$7,(0xFFFFF000 >> 16)\n"
        "	daddu	$6,$0,$0\n"
        "	ori	$7,$7,(0xFFFFF000 & 0xFFFF)\n"
        "	nop\n"
        "_func_0017C130_0017C140:\n"
        "	sync\n"
        "	cache	0x10,0x0($6)\n"
        "	sync\n"
        "	.word	0x4002E000\n"
        "	and	$2,$2,$7\n"
        "	addu	$2,$2,$6\n"
        "	sltu	$3,$5,$2\n"
        "	sltu	$2,$2,$4\n"
        "	bnez	$2,_func_0017C130_0017C17C\n"
        "	nop\n"
        "	bnez	$3,_func_0017C130_0017C17C\n"
        "	nop\n"
        "	sync\n"
        "	cache	0x14,0x0($6)\n"
        "	sync\n"
        "_func_0017C130_0017C17C:\n"
        "	sync\n"
        "	cache	0x10,0x1($6)\n"
        "	sync\n"
        "	.word	0x4002E000\n"
        "	and	$2,$2,$7\n"
        "	addu	$2,$2,$6\n"
        "	sltu	$3,$5,$2\n"
        "	sltu	$2,$2,$4\n"
        "	bnez	$2,_func_0017C130_0017C1B8\n"
        "	nop\n"
        "	bnez	$3,_func_0017C130_0017C1B8\n"
        "	nop\n"
        "	sync\n"
        "	cache	0x14,0x1($6)\n"
        "	sync\n"
        "_func_0017C130_0017C1B8:\n"
        "	sync\n"
        "	addiu	$6,$6,0x40\n"
        "	slti	$2,$6,0x1000\n"
        "	bnez	$2,_func_0017C130_0017C140\n"
        "	nop\n"
        "	.set	reorder\n"
       );
}

/* Writes the data cache back for `start`..`end`. */
void SyncDCache(u32 start, u32 end) {
    s32 eie;
    __asm__ volatile("mfc0	%0, $12" : "=r"(eie));
    eie &= 0x10000;
    if (eie) {
        func_001843E0();
    }
    _sceSDC(start & 0xFFFFFFC0, end & 0xFFFFFFC0);
    if (eie) {
        func_00184428();
    }
}

/* Writes the data cache back for `start`..`end` (from an interrupt). */
void iSyncDCache(u32 start, u32 end) {
    _sceSDC(start & ~0x3F, end & ~0x3F);
}

/* _sceIDC: Sony's hand-written libkernl assembly, kept as asm (kfiv-decomp, MIT, writes it as an asm block in src/sce/libkernl/cache.c; see THIRD_PARTY_NOTICES.md) */

void _sceIDC(u32 start, u32 end) {
    __asm__ __volatile__(
        "	.set	noreorder\n"
        "	lui	$7,(0xFFFFF000 >> 16)\n"
        "	daddu	$6,$0,$0\n"
        "	ori	$7,$7,(0xFFFFF000 & 0xFFFF)\n"
        "	nop\n"
        "_func_0017C270_0017C280:\n"
        "	sync\n"
        "	cache	0x10,0x0($6)\n"
        "	sync\n"
        "	.word	0x4002E000\n"
        "	and	$2,$2,$7\n"
        "	addu	$2,$2,$6\n"
        "	sltu	$3,$5,$2\n"
        "	sltu	$2,$2,$4\n"
        "	bnez	$2,_func_0017C270_0017C2BC\n"
        "	nop\n"
        "	bnez	$3,_func_0017C270_0017C2BC\n"
        "	nop\n"
        "	sync\n"
        "	cache	0x16,0x0($6)\n"
        "	sync\n"
        "_func_0017C270_0017C2BC:\n"
        "	sync\n"
        "	cache	0x10,0x1($6)\n"
        "	sync\n"
        "	.word	0x4002E000\n"
        "	and	$2,$2,$7\n"
        "	addu	$2,$2,$6\n"
        "	sltu	$3,$5,$2\n"
        "	sltu	$2,$2,$4\n"
        "	bnez	$2,_func_0017C270_0017C2F8\n"
        "	nop\n"
        "	bnez	$3,_func_0017C270_0017C2F8\n"
        "	nop\n"
        "	sync\n"
        "	cache	0x16,0x1($6)\n"
        "	sync\n"
        "_func_0017C270_0017C2F8:\n"
        "	sync\n"
        "	addiu	$6,$6,0x40\n"
        "	slti	$2,$6,0x1000\n"
        "	bnez	$2,_func_0017C270_0017C280\n"
        "	nop\n"
        "	.set	reorder\n"
       );
}

/* Discards the data cache for `start`..`end`. */
void InvalidDCache(u32 start, u32 end) {
    s32 eie;
    __asm__ volatile("mfc0	%0, $12" : "=r"(eie));
    eie &= 0x10000;
    if (eie) {
        func_001843E0();
    }
    _sceIDC(start & 0xFFFFFFC0, end & 0xFFFFFFC0);
    if (eie) {
        func_00184428();
    }
}

/* Discards the data cache for `start`..`end` (from an interrupt). */
void iInvalidDCache(u32 start, u32 end) {
    _sceIDC(start & ~0x3F, end & ~0x3F);
}

/* Whether interrupts are off (the COP0 status IE bit is clear). */
s32 func_0017C3B0(void) {
    s32 s;
    __asm__ volatile("mfc0\t%0, $12" : "=r"(s));
    return (s ^ 1) & 1;
}

/* DisableIntc with interrupts held: disables interrupt cause `cause`. */
s32 func_0017C3C0(s32 cause) {
    s32 eie, ret;
    __asm__ volatile("mfc0	%0, $12" : "=r"(eie));
    eie &= 0x10000;
    if (eie) {
        func_001843E0();
    }
    ret = _DisableIntc(cause);
    __asm__ volatile("sync");
    if (eie) {
        func_00184428();
    }
    return ret;
}

/* EnableIntc with interrupts held: enables interrupt cause `cause`. */
s32 func_0017C428(s32 cause) {
    s32 eie, ret;
    __asm__ volatile("mfc0	%0, $12" : "=r"(eie));
    eie &= 0x10000;
    if (eie) {
        func_001843E0();
    }
    ret = _EnableIntc(cause);
    __asm__ volatile("sync");
    if (eie) {
        func_00184428();
    }
    return ret;
}

/* DisableDmac with interrupts held: disables DMA channel `channel`'s interrupt. */
s32 func_0017C490(s32 channel) {
    s32 eie, ret;
    __asm__ volatile("mfc0	%0, $12" : "=r"(eie));
    eie &= 0x10000;
    if (eie) {
        func_001843E0();
    }
    ret = _DisableDmac(channel);
    __asm__ volatile("sync");
    if (eie) {
        func_00184428();
    }
    return ret;
}

/* EnableDmac with interrupts held: enables DMA channel `channel`'s interrupt. */
s32 func_0017C4F8(s32 channel) {
    s32 eie, ret;
    __asm__ volatile("mfc0	%0, $12" : "=r"(eie));
    eie &= 0x10000;
    if (eie) {
        func_001843E0();
    }
    ret = _EnableDmac(channel);
    __asm__ volatile("sync");
    if (eie) {
        func_00184428();
    }
    return ret;
}

/* Enables an interrupt cause (from an interrupt). */
void iEnableIntc(void) {
    _iEnableIntc();
    __asm__ volatile("sync");
}

/* Disables an interrupt cause (from an interrupt). */
void iDisableIntc(void) {
    _iDisableIntc();
    __asm__ volatile("sync");
}

/* Enables a DMA channel's interrupt (from an interrupt). */
void iEnableDmac(void) {
    _iEnableDmac();
    __asm__ volatile("sync");
}

/* Disables a DMA channel's interrupt (from an interrupt). */
void iDisableDmac(void) {
    _iDisableDmac();
    __asm__ volatile("sync");
}

/* EE kernel call 0x74 (SetSyscall): sets kernel call `arg0` to `arg1` (the names stay: the call reads them from
   registers). */
void func_0017C5E0(int arg0, int arg1) {
    __asm__ __volatile__("addiu\t$3,$0,0x74\n\tsyscall");
}

/* EE kernel call 0x5A (kernel copy): copies `arg2` bytes from `arg1` into kernel memory at `arg0`. */
int func_0017C5F0(int arg0, int *arg1, int arg2) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x5A\n\tsyscall" : "=r" (ret));
    return ret;
}

/* Copies `arg2` bytes (whole words) from `arg1` to `arg0`; returns 0. */
s32 func_0017C600(s32 *arg0, s32 *arg1, u32 arg2) {
    s32 *var_a0;
    s32 *var_a1;
    s32 temp_v1;
    u32 temp_a2;
    u32 i;

    var_a0 = arg0;
    var_a1 = arg1;
    temp_a2 = arg2 >> 2;
    i = 0;
    if (temp_a2 != 0) {
        do {
            temp_v1 = *var_a1;
            i += 1;
            var_a1 += 1;
            *var_a0 = temp_v1;
            var_a0 += 1;
        } while (i < temp_a2);
    }
    return 0;
}

/* EE kernel call 0x5B: reads kernel word `arg0`. */
int func_0017C638(int arg0) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x5B\n\tsyscall" : "=r" (ret));
    return ret;
}

extern s32 D_0028C258;
extern s32 D_0028C998;
extern s32 D_0028C9C0;

typedef struct KPatch_0017C648 {
    s32 addr;
    s32 val;
} KPatch_0017C648;

/* Installs the library's kernel patches (on consoles that need them): new kernel code and syscall entries. */
void func_0017C648(void) {
    KPatch_0017C648 *t;
    u32 i;

    if (!(*(volatile s32 *)0x10001810 & 0x100)) {
        t = (KPatch_0017C648 *)&D_0028C9C0;
        func_0017C5E0(t[0].addr, t[0].val);
        func_0017C5F0(0x80076000, &D_0028C258, 0x740);
        func_0017C5F0(0x82000, &D_0028C998, 0x28);
        FlushCache(0);
        FlushCache(2);
        func_0017C5E0(t[1].addr, t[1].val);
        for (i = 2; i < 8; i++) {
            func_0017C5E0(t[i].addr, func_0017C638(t[i].addr));
        }
    }
}

typedef struct {
    u8 code;
    u8 id;
} KernEvent_0017C720;

typedef struct {
    s32 ridx;
    s32 widx;
    KernEvent_0017C720 ent[512];
} KernEventRing_0017C720;

extern char D_002BBF78[];

/* topThread: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

void topThread(void *arg) {
    KernEventRing_0017C720 *ring = (KernEventRing_0017C720 *)arg;
    s32 i;

    while (1) {
        ((s32 (*)(s32))WaitSema)(D_00310510);
        i = ring->ridx & 0x1FF;
        ring->ridx = i + 1;
        switch (ring->ent[i].code) {
        case 0:
            ((s32 (*)(s32))WakeupThread)(ring->ent[i].id);
            break;
        case 1:
            RotateThreadReadyQueue(ring->ent[i].id);
            break;
        case 2:
            ((s32 (*)(s32))SuspendThread)(ring->ent[i].id);
            break;
        default:
            kprintf(D_002BBF78);
            break;
        }
    }
}

typedef struct {
    s32 status;
    void *entry;
    void *stack;
    s32 stackSize;
    void *gpReg;
    s32 initPriority;
    s32 currentPriority;
    u32 attr;
    u32 option;
    s32 waitType;
    s32 waitId;
    s32 wakeupCount;
} ThParam_0017C7F8;

typedef struct {
    s32 count;
    s32 max_count;
    s32 init_count;
    s32 wait_threads;
    u32 attr;
    u32 option;
} SemParam_0017C7F8;

extern u8 D_00310110[];
extern s32 D_00317EF0;

/* Sets up the library's thread support: the main thread's id and priority, the helper semaphores. */
s32 InitThread(void) {
    ThParam_0017C7F8 tp;
    SemParam_0017C7F8 sp;
    s32 tid;
    ring_t *r;

    if (topId > 0) {
        return -1;
    }
    sp.init_count = 0;
    sp.max_count = 0xFF;
    D_00310510 = CreateSema(&sp);
    if (D_00310510 < 0) {
        return -1;
    }
    tp.entry = topThread;
    tp.stack = D_00310110;
    tp.stackSize = 0x400;
    tp.gpReg = &D_00317EF0;
    tp.initPriority = 0;
    topId = tid = CreateThread(&tp);
    if (tid < 0) {
        DeleteSema(D_00310510);
        return -1;
    }
    r = (ring_t *)&D_00310518;
    r->x0 = 0;
    r->count = 0;
    StartThread(tid, r);
    ChangeThreadPriority(GetThreadId(), 1);
    return topId;
}

/* Wakes thread `thid` (from an interrupt). */
s32 iWakeupThread(s32 thid) {
    s32 tid;
    __asm__ volatile("addiu $3, $0, -0x2F\n\tsyscall\n\tdaddu %0, $2, $0" : "=r"(tid));
    if (tid != thid) {
        return _iWakeupThread(thid);
    }
    if ((u32)tid >= 0x100 || topId == 0) {
        return -1;
    }
    {
        ring_t *r = (ring_t *)&D_00310518;
        u32 i = r->count & 0x1FF;
        r->count = i + 1;
        r->e[i].a = 0;
        r->e[i].b = tid;
        iSignalSema(D_00310510);
    }
    return tid;
}

/* Rotates the ready queue of priority `priority` (from an interrupt). */
s32 iRotateThreadReadyQueue(u32 priority) {
    if (priority >= 0x80 || topId == 0) {
        return -1;
    }
    {
        ring_t *r = (ring_t *)&D_00310518;
        u32 i = r->count & 0x1FF;
        r->count = i + 1;
        r->e[i].a = 1;
        r->e[i].b = priority;
        iSignalSema(D_00310510);
    }
    return priority;
}

/* Suspends thread `thid` (from an interrupt). */
s32 iSuspendThread(s32 thid) {
    s32 tid;
    __asm__ volatile("addiu $3, $0, -0x2F\n\tsyscall\n\tdaddu %0, $2, $0" : "=r"(tid));
    if (tid != thid) {
        return _iSuspendThread(thid);
    }
    if ((u32)tid >= 0x100 || topId == 0) {
        return -1;
    }
    {
        ring_t *r = (ring_t *)&D_00310518;
        u32 i = r->count & 0x1FF;
        r->count = i + 1;
        r->e[i].a = 2;
        r->e[i].b = tid;
        iSignalSema(D_00310510);
    }
    return tid;
}

/* Opens DECI2 debug protocol `protocol` with handler `handler` (`opt`). */
s32 sceDeci2Open(s32 protocol, s32 opt, s32 handler) {
    s32 sp0[4];
    sp0[0] = /* extra? */ (protocol & 0xFFFF);
    sp0[1] = /* extra? */ opt;
    sp0[2] = /* extra? */ handler;
    sp0[3] = /* extra? */ ((s32) &D_00310920 | 0x20000000);
    return Deci2Call(1, sp0);
}

/* Closes DECI2 socket `s`. */
void sceDeci2Close(s32 s) {
    s32 sp0[4];
    sp0[0] = s;
    Deci2Call(2, sp0);
}

/* Asks to send on DECI2 socket `s` to node `dest`. */
void sceDeci2ReqSend(s32 s, s8 dest) {
    s32 sp0[4];
    sp0[0] = s;
    sp0[1] = (s32) dest;
    Deci2Call(3, sp0);
}

/* Polls DECI2 socket `s`. */
void sceDeci2Poll(s32 s) {
    s32 sp0[4];
    sp0[0] = s;
    Deci2Call(4, sp0);
}

/* Receives `len` bytes on DECI2 socket `s` into `buf`. */
void sceDeci2ExRecv(s32 s, s32 buf, s32 len) {
    s32 sp0[4];
    s32 temp_a2;

    temp_a2 = len & 0xFFFF;
    sp0[0] = s;
    sp0[1] = buf;
    sp0[2] = temp_a2;
    Deci2Call(-5, sp0);
}

/* Sends `len` bytes from `buf` on DECI2 socket `s`. */
void sceDeci2ExSend(s32 s, s32 buf, s32 len) {
    s32 sp0[4];
    s32 temp_a2;

    temp_a2 = len & 0xFFFF;
    sp0[0] = s;
    sp0[1] = buf;
    sp0[2] = temp_a2;
    Deci2Call(-6, sp0);
}

/* Asks to send on DECI2 socket `s` to node `dest`. */
void sceDeci2ExReqSend(s32 s, s8 dest) {
    s32 sp0[4];
    sp0[0] = s;
    sp0[1] = (s32) dest;
    Deci2Call(-7, sp0);
}

/* Locks DECI2 socket `s`. */
void sceDeci2ExLock(s32 s) {
    s32 sp0[4];
    sp0[0] = s;
    Deci2Call(-8, sp0);
}

/* Unlocks DECI2 socket `s`. */
void sceDeci2ExUnLock(s32 s) {
    s32 sp0[4];
    sp0[0] = s;
    Deci2Call(-9, sp0);
}

/* Writes string `s` to the debug console. */
void kputs(s32 s) {
    s32 sp0[4];
    sp0[0] = s;
    Deci2Call(0x10, sp0);
}

/* Clears debug-console queue `q`. */
s32 *QueueInit(s32 q) {
    void *temp_a0;

    (*(s32 *)(&D_00310980)) = q;
    temp_a0 = (u8 *)&D_00310980 + 0x10;
    (*(s32 *)((u8 *)(&D_00310980) + 4)) = 0;
    (*(void **)((u8 *)(&D_00310980) + 0xC)) = temp_a0;
    (*(void **)((u8 *)(&D_00310980) + 8)) = temp_a0;
    return &D_00310980;
}

/* Marks the next write slot of queue `q` used. */
void QueuePeekWriteDone(void *q) {
    void *temp_a0;

    (*(s32 *)((u8 *)q + 4)) = (s32) ((*(s32 *)((u8 *)q + 4)) + 1);
    temp_a0 = (*(void **)((u8 *)q + 0xC)) + 1;
    (*(void **)((u8 *)q + 0xC)) = temp_a0;
    if (temp_a0 == (q + ((*(s32 *)q) + 0x10))) {
        (*(void **)((u8 *)q + 0xC)) = (void *) (q + 0x10);
    }
}

/* Takes the next byte off queue `q`. */
void QueuePeekReadDone(void *q) {
    void *temp_a0;

    (*(s32 *)((u8 *)q + 4)) = (s32) ((*(s32 *)((u8 *)q + 4)) - 1);
    temp_a0 = (*(void **)((u8 *)q + 8)) + 1;
    (*(void **)((u8 *)q + 8)) = temp_a0;
    if (temp_a0 == (q + ((*(s32 *)q) + 0x10))) {
        (*(void **)((u8 *)q + 8)) = (void *) (q + 0x10);
    }
}

typedef struct {
    s32 size;
    s32 count;
    char *rp;
    char *wp;
    char buf[256];
} TtyQueue_0017CD08;

typedef struct {
    volatile s32 s;
    volatile s32 wlen;
    volatile s32 rlen;
    volatile s32 busy;
    char *wbuf;
    char *rbuf;
    TtyQueue_0017CD08 *q;
} TtyRec_0017CD08;

extern char D_002BBFA0[];
extern char D_002BBFC8[];
extern char D_002BBFE0[];
extern char D_002BBFF8[];

/* sceTtyHandler: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

void sceTtyHandler(s32 event, s32 param, void *opt) {
    TtyRec_0017CD08 *tty = opt;
    s32 n;
    s32 i;
    char *hdr;

    switch (event) {
    case 1:
    case 2:
        if (param != 0) {
            if (320 < (u32)(tty->rlen + param)) {
                kprintf(D_002BBFA0);
            }
            i = ((s32 (*)(s32, char *, u16))sceDeci2ExRecv)(tty->s, tty->rbuf + tty->rlen, (u16)param);
            if (i < 0) {
                kprintf(D_002BBFC8);
            }
            tty->rlen = tty->rlen + i;
            return;
        }
        hdr = tty->rbuf;
        for (i = 12; i < *(u16 *)hdr; i++) {
            *tty->q->wp = tty->rbuf[i];
            QueuePeekWriteDone(tty->q);
        }
        tty->rlen = 0;
        return;

    case 3:
        n = ((s32 (*)(s32, char *, u16))sceDeci2ExSend)(tty->s, tty->wbuf, (u16)tty->wlen);
        if (n < 0) {
            kprintf(D_002BBFE0, n);
            break;
        }
        tty->wbuf = tty->wbuf + n;
        tty->wlen = tty->wlen - n;
        return;

    case 4:
        if (tty->wlen != 0) {
            kprintf(D_002BBFF8, tty->wlen);
        }
        break;

    default:
        return;
    }
    tty->busy = 0;
}

typedef struct Deci2Q_0017CFF0 {
    s32 unk0;
    volatile s32 count;
    u8 *rptr;
} Deci2Q_0017CFF0;

typedef struct Deci2Tty_0017CFF0 {
    s32 sock;
    s32 unk4[5];
    Deci2Q_0017CFF0 *q;
} Deci2Tty_0017CFF0;

extern Deci2Tty_0017CFF0 D_00310A90;

extern char D_00310AC0[];

/* sceTtyWrite: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

s32 sceTtyWrite(const char *buf, int len) {
    char *hdr;
    char *out;
    int n = 0;
    int i = 0;

    if ((*(TtyRec_0017CD08 *)&D_00310A90).busy != 0) {
        return -1;
    }
    func_001843E0();
    (*(TtyRec_0017CD08 *)&D_00310A90).busy = 1;
    hdr = (char *)((u32)D_00310AC0 | 0x20000000);
    (*(TtyRec_0017CD08 *)&D_00310A90).wbuf = hdr;
    out = hdr + 12;
    while (len-- != 0) {
        if (*buf == '\n') {
            *out = '\r';
            n++;
            out++;
            if (n >= 256) {
                break;
            }
        }
        *out = *buf;
        n++;
        buf++;
        out++;
        i++;
        if (n >= 256) {
            break;
        }
    }
    (*(TtyRec_0017CD08 *)&D_00310A90).wlen = n + 12;
    *(s16 *)hdr = (*(TtyRec_0017CD08 *)&D_00310A90).wlen;
    if (((s32 (*)(s32, s8))sceDeci2ReqSend)((*(TtyRec_0017CD08 *)&D_00310A90).s, hdr[7]) < 0) {
        (*(TtyRec_0017CD08 *)&D_00310A90).busy = 0;
        func_00184428();
        return -1;
    }
    while ((*(TtyRec_0017CD08 *)&D_00310A90).busy != 0) {
        sceDeci2Poll((*(TtyRec_0017CD08 *)&D_00310A90).s);
    }
    func_00184428();
    return i;
}


/* Reads up to `nIn` bytes from the debug console into `buf`. */
s32 sceTtyRead(char *buf, s32 nIn) {
    s32 i;
    char *p;

    for (i = 0; i < nIn; i++) {
        p = &buf[i];
        while (D_00310A90.q->count == 0) {
        }
        *p = *(*(Deci2Tty_0017CFF0 *)&D_00310A90).q->rptr;
        QueuePeekReadDone((*(Deci2Tty_0017CFF0 *)&D_00310A90).q);
        if (*p == '\n' || *p == '\r') {
            return i + 1;
        }
    }
    return i;
}

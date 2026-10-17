#include "common.h"
#include "sce/libkernl.h"

typedef struct {
    volatile s32 s;
    volatile s32 wlen;
    volatile s32 rlen;
    volatile s32 busy;
    char *wbuf;
    char *rbuf;
    void *q;
} TtyRec_0017D0C0;

extern TtyRec_0017D0C0 D_00310A90;
extern char D_00310AC0[];
extern char D_00310C00[];

/* sceTtyInit: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

s32 sceTtyInit(void) {
    extern void sceTtyHandler(s32, s32, void *);
    char *snd;
    char *rcv;

    FlushCache(0);
    D_00310A90.s = sceDeci2Open(0x210, (s32)&D_00310A90, (s32)sceTtyHandler);
    if (D_00310A90.s < 0) {
        return 0;
    }
    D_00310A90.busy = 0;
    rcv = (char *)((u32)D_00310C00 | 0x20000000);
    snd = (char *)((u32)D_00310AC0 | 0x20000000);
    D_00310A90.wlen = 0;
    D_00310A90.rlen = 0;
    D_00310A90.rbuf = rcv;
    D_00310A90.wbuf = snd;
    *(s16 *)(snd + 4) = 0x210;
    snd[6] = 'E';
    snd[7] = 'H';
    *(s16 *)(snd + 2) = 0;
    *(s32 *)(snd + 8) = 0;
    D_00310A90.q = QueueInit(256);
    return 1;
}

/* Writes character `c` to the debug console. */
s32 kputchar(s32 c) {
    do {

    } while (*(volatile s32 *)0x1000F130 & 0x8000);
    *(volatile s8 *)0x1000F180 = (s8) c;
    return c;
}

/* Writes character `c` to the DECI2 debug console (buffered by line). */
void deci2Putchar(s32 c) {
    s32 i;

    if (D_0028CA08 >= 0x7E) {
        D_0028CA08 = 0;
        D_00310D40[0x7F] = 0;
        kputs((s32)D_00310D40);
    }
    if (c == '\n') {
        i = D_0028CA08;
        D_0028CA08 = 0;
        D_00310D40[i] = c;
        D_00310D40[i + 1] = 0;
        kputs((s32)D_00310D40);
    } else {
        D_00310D40[D_0028CA08++] = c;
    }
}

/* Writes character `c` to the serial debug port. */
void serialPutchar(s32 c) {
    if (c == 0xA) {
        kputchar(0xD);
        kputchar(0xA);
        return;
    }
    kputchar(c);
}

/* ftoi: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

s32 ftoi(u64 a) {
    u64 m = a;
    s64 e;

    e = (s64)((m << 1) >> 53);
    e -= 1075;
    if (e < -53) {
        return 0;
    }
    if (e >= 13) {
        return 9999;
    }
    m = (m << 12) >> 12;
    m |= (u64)1 << 52;
    if (e < 0) {
        s32 s;

        e = -e;
        s = e - 2;
        m >>= s;
        if ((m & 3) == 3) {
            m = (m >> 2) + 1;
        } else {
            m >>= 2;
        }
    } else {
        m <<= e;
    }
    return (s32)m;
}

extern char D_002BC010[];
extern char D_002BC018[];
extern char D_002BC020[];

/* printfloat: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

void printfloat(s64 bits) {
    union {
        s64 i;
        double d;
    } u;
    double v;
    double zero = 0.0;
    int e = 0;
    int n;

    u.i = bits;
    v = u.d;
    if (v < zero) {
        v = zero - v;
        _putchar('-');
    }
    if (v < 0.1) {
        while (v < 0.1) {
            v *= 10.0;
            e--;
        }
    } else if (v >= 1.0) {
        while (v >= 1.0) {
            v /= 10.0;
            e++;
        }
    }
    v *= 1000000.0;
    n = ftoi(v);
    kprintf(D_002BC010, n);
    if (e >= 0) {
        kprintf(D_002BC018, e);
    } else {
        kprintf(D_002BC020, e);
    }
}

/* The kernel printf core: formats `fmt` with argument list `ap`. */
void _printf(char *fmt, u8 *ap) {
    char buf[32];
    char *p;
    char *pad;
    s64 v;
    u64 u;
    s32 mod;
    s32 w;
    s32 c;
    f32 f;
    char *s;
    char ch;
    u64 d;
    u64 e;

    while (*fmt) {
        pad = 0;
        mod = 0;
        if (*fmt == '%') {
    again:
        switch (*++fmt) {
        case '0':
            w = fmt[1] - '0';
            c = fmt[2];
            if ((u8)w < 10) {
                if (c >= '0' && c <= '9') {
                    w = w * 10 + (c - '0');
                    fmt += 2;
                    if (w >= 32) {
                        w = 31;
                    }
                } else {
                    fmt++;
                }
                pad = buf + (31 - w);
                while (w > 0) {
                    buf[31 - w] = '0';
                    w--;
                }
            }
            goto again;
        case 'l':
            mod = 'l';
            goto again;
        case 'h':
            mod = 'h';
            goto again;
        case 'o':
            if (mod == 'l') {
                ap += 8;
                u = *(u64 *)(ap - 8);
            } else if (mod == 'h') {
                ap += 8;
                u = *(u16 *)(ap - 8);
            } else {
                ap += 8;
                u = *(u32 *)(ap - 8);
            }
            p = &buf[31];
            *p = 0;
            if (u == 0) {
                *--p = '0';
            } else {
                while (u != 0) {
                    *--p = (u & 7) + '0';
                    u >>= 3;
                }
            }
            if (pad != 0 && pad < p) {
                p = pad;
            }
            while (*p) {
                _putchar(*p++);
            }
            break;
        case 'x':
            if (mod == 'l') {
                ap += 8;
                u = *(u64 *)(ap - 8);
            } else if (mod == 'h') {
                ap += 8;
                u = *(u16 *)(ap - 8);
            } else {
                ap += 8;
                u = *(u32 *)(ap - 8);
            }
            p = &buf[31];
            *p = 0;
            if (u == 0) {
                *--p = '0';
            } else {
                while (u != 0) {
                    d = u & 0xF;
                    if (d < 10) {
                        *--p = d + '0';
                    } else {
                        *--p = d + 'a' - 10;
                    }
                    u >>= 4;
                }
            }
            if (pad != 0 && pad < p) {
                p = pad;
            }
            while (*p) {
                _putchar(*p++);
            }
            break;
        case 'd':
            if (mod == 'l') {
                ap += 8;
                v = *(s64 *)(ap - 8);
            } else if (mod == 'h') {
                ap += 8;
                v = *(s16 *)(ap - 8);
            } else {
                ap += 8;
                v = *(s32 *)(ap - 8);
            }
            p = &buf[31];
            *p = 0;
            if (v == 0) {
                *--p = '0';
            } else {
                if (v < 0) {
                    v = -v;
                    _putchar('-');
                }
                while (v != 0) {
                    *--p = func_001A0CF8(v, 10) + '0';
                    v = func_001A0660(v, 10);
                }
            }
            if (pad != 0 && pad < p) {
                p = pad;
            }
            while (*p) {
                _putchar(*p++);
            }
            break;
        case 'u':
            if (mod == 'l') {
                ap += 8;
                u = *(u64 *)(ap - 8);
            } else if (mod == 'h') {
                ap += 8;
                u = *(u16 *)(ap - 8);
            } else {
                ap += 8;
                u = *(u32 *)(ap - 8);
            }
            p = &buf[31];
            *p = 0;
            if (u == 0) {
                *--p = '0';
            } else {
                while (u != 0) {
                    *--p = func_001A1908(u, 10) + '0';
                    u = func_001A1388(u, 10);
                }
            }
            if (pad != 0 && pad < p) {
                p = pad;
            }
            while (*p) {
                _putchar(*p++);
            }
            break;
        case 'e':
        case 'f':
            ap += 8;
            f = *(f32 *)(ap - 8);
            if (f == 0.0f) {
                _putchar('0');
            } else {
                printfloat(((s64 (*)(f32))func_001A2370)(f));
            }
            break;
        case 's':
            ap += 8;
            s = *(char **)(ap - 8);
            if (*s == 0) {
                _putchar('(');
                _putchar('n');
                _putchar('u');
                _putchar('l');
                _putchar('l');
                _putchar(')');
            } else {
                p = s;
                do {
                    _putchar(*p++);
                } while (*p);
            }
            break;
        case 'c':
            ap += 8;
            v = *(char *)(ap - 8);
            _putchar(v);
            break;
        }
        } else {
            _putchar(*fmt);
        }
        fmt++;
    }
}

/* Prints `fmt` to the kernel debug console. */
s32 kprintf(const char *fmt, ...) {
    return ((s32 (*)(const char *, void *))_printf)(fmt, (char *)__builtin_next_arg(fmt) - (8 - __builtin_args_info(0)) * 8);
}

/* Prints `fmt` to the debug console. */
s32 scePrintf(const char *fmt, ...) {
    void (*old)(s32);
    s32 r;

    old = _putchar;
    _putchar = deci2Putchar;
    r = ((s32 (*)(const char *, void *))_printf)(fmt, (char *)__builtin_next_arg(fmt) - (8 - __builtin_args_info(0)) * 8);
    _putchar = old;
    return r;
}

/* Sets a SIF software register. */
void _set_sreg(s32 *arg0, s32 *arg1) {
    ((s32 **) arg1)[7][arg0[4]] = arg0[5];
}

/* Moves a SIF command buffer. */
void _change_addr(void *arg0, void *arg1) {
    (*(s32 *)((u8 *)arg1 + 8)) = (s32) (*(s32 *)((u8 *)arg0 + 0x10));
}

/* SIF software register `reg`. */
s32 sceSifGetSreg(s32 reg) {
    return (&D_00310FC0)[reg];
}

/* Sets SIF software register `reg` to `value`. */
s32 sceSifSetSreg(s32 reg, s32 value) {
    (&D_00310FC0)[reg] = value;
    return value;
}

/* The SIF command data table. */
s32 *sceSifGetDataTable(void) {
    return &D_00310E98;
}

typedef struct {
    void (*fn)();
    void *data;
} SifCmdEntry_0017DB70;

typedef struct {
    s32 sendbuf;
    s32 ackbuf;
    s32 iopbuf;
    SifCmdEntry_0017DB70 *systbl;
    s32 nsys;
    SifCmdEntry_0017DB70 *usrtbl;
    s32 nusr;
    s32 *sreg;
} SifCmdData_0017DB70;

extern s32 D_00310DC0[32];
extern s32 D_00310E40[16];
extern s32 D_00310E80[5];
extern SifCmdEntry_0017DB70 D_00310EC0[32];

#define cmdData_0017DB70 (*(SifCmdData_0017DB70 *)&D_00310E98)

/* sceSifInitCmd: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

void sceSifInitCmd(void) {
    SifCmdEntry_0017DB70 *h;
    s32 i;

    func_001843E0();
    if (_cmd_init_check != 0) {
        func_00184428();
        return;
    }
    _cmd_init_check = 1;
    cmdData_0017DB70.sendbuf = (s32)D_00310DC0 | 0x20000000;
    cmdData_0017DB70.ackbuf = (s32)D_00310E40 | 0x20000000;
    cmdData_0017DB70.iopbuf = 0;
    cmdData_0017DB70.systbl = D_00310EC0;
    cmdData_0017DB70.nsys = 0x20;
    cmdData_0017DB70.usrtbl = 0;
    cmdData_0017DB70.nusr = 0;
    cmdData_0017DB70.sreg = &D_00310FC0;
    h = D_00310EC0;
    for (i = 0; i < 32; i++) {
        h->fn = 0;
        h->data = 0;
        h++;
    }
    for (i = 0; i < 32; i++) {
        (&D_00310FC0)[i] = 0;
    }
    D_00310EC0[0].fn = (void (*)())_change_addr;
    D_00310EC0[0].data = &cmdData_0017DB70;
    D_00310EC0[1].fn = (void (*)())_set_sreg;
    D_00310EC0[1].data = &cmdData_0017DB70;
    func_00184428();
    FlushCache(0);
    if (*(volatile u32 *)0x1000E010 & 0x20) {
        *(volatile u32 *)0x1000E010 = 0x20;
    }
    if ((*(volatile u32 *)0x1000C000 & 0x100) == 0) {
        sceSifSetDChain();
    }
    D_00310E94 = AddDmacHandler(5, func_0017E068, 0);
    func_0017C4F8(5);
    cmdData_0017DB70.iopbuf = ((u32 (*)(u32))sceSifGetReg)(0x80000000);
    if (cmdData_0017DB70.iopbuf != 0) {
        D_00310E80[4] = (s32)D_00310DC0;
        sceSifSendCmd(0x80000000, D_00310E80, 0x14, 0, 0, 0);
        return;
    }
    while ((sceSifGetReg(4) & 0x20000) == 0) {
        ;
    }
    cmdData_0017DB70.iopbuf = sceSifGetReg(2);
    ((s32 (*)(s32, s32))sceSifSetReg)(0x80000000, cmdData_0017DB70.iopbuf);
    ((s32 (*)(s32, s32))sceSifSetReg)(0x80000001, (s32)&cmdData_0017DB70);
    D_00310E80[4] = (s32)D_00310DC0;
    D_00310E80[3] = 0;
    sceSifSendCmd(0x80000002, D_00310E80, 0x14, 0, 0, 0);
}

/* Shuts the SIF command system down. */
void sceSifExitCmd(void) {
    func_0017C490(5);
    RemoveDmacHandler(5, D_00310E94);
    _cmd_init_check = 0;
}

/* Sets the SIF command buffer (`buf`, `size`); returns the old one. */
s32 sceSifSetCmdBuffer(s32 buf, s32 size) {
    s32 *p = (s32 *)&D_00310E98;
    s32 old = p[5];
    p[5] = buf;
    p[6] = size;
    return old;
}

/* Sets the SIF system command buffer (`buf`, `size`). */
s32 sceSifSetSysCmdBuffer(s32 buf, s32 size) {
    s32 *p = (s32 *)&D_00310E98;
    s32 old = p[3];
    p[3] = buf;
    p[4] = size;
    return old;
}

/* Sets the handler of SIF command `cid` to `f` (with `data`). */
s32 sceSifAddCmdHandler(s32 cid, s32 *f, s32 data) {
    if (cid < 0) {
        D_00310EA4[cid].func = f;
        D_00310EA4[cid].data = (void *)data;
    } else {
        D_00310EAC[cid].func = f;
        D_00310EAC[cid].data = (void *)data;
    }
}

/* Removes the handler of SIF command `cid`. */
s32 sceSifRemoveCmdHandler(s32 cid) {
    if (cid < 0) {
        D_00310EA4[cid].func = 0;
    } else {
        D_00310EAC[cid].func = 0;
    }
}

/* _sceSifSendCmd: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

s32 _sceSifSendCmd(s32 cid, s32 mode, s32 pkt, s32 pktsize, s32 src, s32 dest, s32 size) {
    extern s32 D_00310EA0;
    sceSifDmaData dmat[2];
    SifCmdHeader *header;
    s32 count;

    if (pktsize < 16 || pktsize > 112) {
        return 0;
    }
    header = (SifCmdHeader *)pkt;
    count = 0;
    if (size > 0) {
        header->dsize = size;
        dmat[0].src = (u32)src;
        dmat[0].dest = (u32)dest;
        dmat[0].size = size;
        header->dest = (void *)dest;
        dmat[0].u.attr = 0;
        count = 1;
        if (mode & 4) {
            func_0017E190((s32 *)src, size);
        }
    } else {
        header->dsize = 0;
        header->dest = 0;
    }
    dmat[count].src = (u32)pkt;
    dmat[count].dest = D_00310EA0;
    dmat[count].size = pktsize;
    header->cid = cid;
    header->psize = pktsize;
    dmat[count].u.attr = 0x44;
    count++;
    func_0017E190((s32 *)pkt, pktsize);
    if (mode & 1) {
        return ((s32 (*)(sceSifDmaData *, s32))isceSifSetDma)(dmat, count);
    }
    return sceSifSetDma((s32 *)dmat, count);
}

/* Sends SIF command `cid` (`packet`, `size`) and data `src` -> `dst` (`len`) to the IOP. */
s32 sceSifSendCmd(s32 cid, void *packet, s32 size, s32 src, s32 dst, s32 len) {
    return _sceSifSendCmd(cid, 0, (s32)packet, size, src, dst, len);
}

/* Sends a SIF command to the IOP (from an interrupt). */
s32 isceSifSendCmd(s32 cid, void *packet, s32 size, s32 src, s32 dst, s32 len) {
    return _sceSifSendCmd(cid, 1, (s32)packet, size, src, dst, len);
}

/* _sceSifCmdIntrHdlr: Sony's hand-written libkernl assembly, kept as asm (kfiv-decomp, MIT, writes it as an asm block in src/sce/libkernl/sifcmd.c; see THIRD_PARTY_NOTICES.md) */

s32 func_0017E068(s32 ch) {
    register s32 ret __asm__("$2");

    __asm__ __volatile__(
        "	.set	noreorder\n"
        "	addiu	$29,$29,-0x90\n"
        "	sd	$16,0x70($29)\n"
        "	sd	$31,0x80($29)\n"
        "	jal	func_00184428\n"
        "	nop\n"
        "	lui	$3,%%hi(D_00310E98)\n"
        "	lw	$7,%%lo(D_00310E98)($3)\n"
        "	addiu	$16,$3,%%lo(D_00310E98)\n"
        "	lbu	$2,0x0($7)\n"
        "	andi	$5,$2,0xFF\n"
        "	beqz	$5,_func_0017E068_0017E180\n"
        "	daddu	$2,$0,$0\n"
        "	addiu	$2,$5,0xF\n"
        "	addiu	$3,$0,-0x1\n"
        "	addiu	$4,$5,0x1E\n"
        "	slt	$3,$3,$2\n"
        "	movn	$4,$2,$3\n"
        "	daddu	$6,$7,$0\n"
        "	sra	$5,$4,4\n"
        "	sb	$0,0x0($7)\n"
        "	blez	$5,_func_0017E068_0017E0E4\n"
        "	daddu	$4,$5,$0\n"
        "	daddu	$3,$29,$0\n"
        "	nop\n"
        "_func_0017E068_0017E0C8:\n"
        "	lq	$2,0x0($6)\n"
        "	addiu	$4,$4,-0x1\n"
        "	addiu	$6,$6,0x10\n"
        "	sq	$2,0x0($3)\n"
        "	addiu	$3,$3,0x10\n"
        "	bnez	$4,_func_0017E068_0017E0C8\n"
        "	nop\n"
        "_func_0017E068_0017E0E4:\n"
        "	jal	isceSifSetDChain\n"
        "	nop\n"
        "	lw	$3,0x8($29)\n"
        "	bgez	$3,_func_0017E068_0017E140\n"
        "	nop\n"
        "	lw	$2,0x8($29)\n"
        "	lui	$3,(0x7FFFFFFF >> 16)\n"
        "	ori	$3,$3,(0x7FFFFFFF & 0xFFFF)\n"
        "	lw	$4,0x10($16)\n"
        "	and	$5,$2,$3\n"
        "	slt	$4,$5,$4\n"
        "	beqz	$4,_func_0017E068_0017E174\n"
        "	sll	$2,$5,3\n"
        "	lw	$3,0xC($16)\n"
        "	addu	$2,$2,$3\n"
        "	lw	$6,0x0($2)\n"
        "	beqz	$6,_func_0017E068_0017E174\n"
        "	nop\n"
        "	lw	$5,0x4($2)\n"
        "	jalr	$6\n"
        "	daddu	$4,$29,$0\n"
        "	b	_func_0017E068_0017E174\n"
        "	nop\n"
        "_func_0017E068_0017E140:\n"
        "	lw	$5,0x8($29)\n"
        "	lw	$2,0x18($16)\n"
        "	slt	$2,$5,$2\n"
        "	beqz	$2,_func_0017E068_0017E174\n"
        "	sll	$2,$5,3\n"
        "	lw	$3,0x14($16)\n"
        "	addu	$2,$2,$3\n"
        "	lw	$6,0x0($2)\n"
        "	beqz	$6,_func_0017E068_0017E174\n"
        "	nop\n"
        "	lw	$5,0x4($2)\n"
        "	jalr	$6\n"
        "	daddu	$4,$29,$0\n"
        "_func_0017E068_0017E174:\n"
        "	sync\n"
        "	ei\n"
        "	daddu	$2,$0,$0\n"
        "_func_0017E068_0017E180:\n"
        "	ld	$31,0x80($29)\n"
        "	.set	reorder\n"
        "	ld	$16,0x70($29)\n"
        "	addiu	$29,$29,0x90\n"
        : "=r"(ret));
    return ret;
}

/* sceSifWriteBackDCache: Sony's hand-written libkernl assembly, kept as asm (kfiv-decomp, MIT, writes it as an asm block in src/sce/libkernl/sifcmd.c; see THIRD_PARTY_NOTICES.md) */

void func_0017E190(s32 *ptr, s32 size) {
    __asm__ __volatile__(
        "	.set	noreorder\n"
        "	lui	$25,(0xFFFFFFC0 >> 16)\n"
        "	ori	$25,$25,(0xFFFFFFC0 & 0xFFFF)\n"
        "	blez	$5,_func_0017E190_0017E234\n"
        "	addu	$10,$4,$5\n"
        "	and	$8,$4,$25\n"
        "	addiu	$10,$10,-0x1\n"
        "	and	$9,$10,$25\n"
        "	subu	$10,$9,$8\n"
        "	srl	$11,$10,6\n"
        "	addiu	$11,$11,0x1\n"
        "	andi	$9,$11,0x7\n"
        "	beqz	$9,_func_0017E190_0017E1E0\n"
        "	srl	$10,$11,3\n"
        "_func_0017E190_0017E1C4:\n"
        "	sync\n"
        "	cache	0x18,0x0($8)\n"
        "	sync\n"
        "	addiu	$9,$9,-0x1\n"
        "	nop\n"
        "	bgtz	$9,_func_0017E190_0017E1C4\n"
        "	addiu	$8,$8,0x40\n"
        "_func_0017E190_0017E1E0:\n"
        "	beqz	$10,_func_0017E190_0017E234\n"
        "_func_0017E190_0017E1E4:\n"
        "	addiu	$10,$10,-0x1\n"
        "	sync\n"
        "	cache	0x18,0x0($8)\n"
        "	sync\n"
        "	cache	0x18,0x40($8)\n"
        "	sync\n"
        "	cache	0x18,0x80($8)\n"
        "	sync\n"
        "	cache	0x18,0xC0($8)\n"
        "	sync\n"
        "	cache	0x18,0x100($8)\n"
        "	sync\n"
        "	cache	0x18,0x140($8)\n"
        "	sync\n"
        "	cache	0x18,0x180($8)\n"
        "	sync\n"
        "	cache	0x18,0x1C0($8)\n"
        "	sync\n"
        "	bgtz	$10,_func_0017E190_0017E1E4\n"
        "	addiu	$8,$8,0x200\n"
        "_func_0017E190_0017E234:\n"
        "	jr	$31\n"
        "	nop\n"
       );
}

typedef struct {
    s32 pid;
    void *pkt_table;
    s32 pkt_table_len;
    s32 unused1;
    s32 unused2;
    void *rdata_table;
    s32 rdata_table_len;
    void *client_table;
    s32 client_table_len;
    s32 client_table_idx;
} SifRpcData_0017E240;

#define _sif_rpc_data (*(SifRpcData_0017E240 *)&D_00312840)
extern u8 D_00311040[];
extern u8 D_00311840[];
extern u8 D_00312040[];

/* Starts the SIF command system once (sceSifInitCmd): handlers, the IOP's buffers, the software registers. */
void func_0017E240(s32 mode) {
    u32 *cmdp;

    func_001843E0();
    if (_sceSifInitCheck != 0) {
        func_00184428();
        return;
    }
    _sceSifInitCheck = 1;
    func_00184428();
    sceSifInitCmd();
    func_001843E0();
    _sif_rpc_data.pkt_table = (void *)((u32)D_00311040 | 0x20000000);
    _sif_rpc_data.pkt_table_len = 0x20;
    _sif_rpc_data.unused1 = 0;
    _sif_rpc_data.unused2 = 0;
    _sif_rpc_data.rdata_table = (void *)((u32)D_00311840 | 0x20000000);
    _sif_rpc_data.rdata_table_len = 0x20;
    _sif_rpc_data.client_table = (void *)((u32)D_00312040 | 0x20000000);
    _sif_rpc_data.client_table_len = 0x20;
    _sif_rpc_data.client_table_idx = 0;
    _sif_rpc_data.pid = 1;
    sceSifAddCmdHandler(0x80000008, (s32 *)_request_end, (s32)&_sif_rpc_data);
    sceSifAddCmdHandler(0x80000009, (s32 *)_request_bind, (s32)&_sif_rpc_data);
    sceSifAddCmdHandler(0x8000000A, (s32 *)_request_call, (s32)&_sif_rpc_data);
    sceSifAddCmdHandler(0x8000000C, (s32 *)_request_rdata, (s32)&_sif_rpc_data);
    func_00184428();
    if (sceSifGetReg(0x80000002) != 0) {
        return;
    }
    cmdp = (u32 *)(D_00311040 + 0x40);
    cmdp[3] = 1;
    sceSifSendCmd(0x80000002, cmdp, 0x10, 0, 0, 0);
    while (sceSifGetSreg(0) == 0) {
    }
    sceSifSetReg(0x80000002, 1);
}

/* Shuts the SIF remote call system down. */
void sceSifExitRpc(void) {
    sceSifExitCmd();
    _sceSifInitCheck = 0;
}

/* _sceRpcGetPacket: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

void *_sceRpcGetPacket(s32 *data) {
    SifRpcData *rd = (SifRpcData *)data;
    SifRpcPkt *p;
    s32 i;
    s32 sid;

    func_001843E0();
    p = rd->pkt_table;
    for (i = 0; i < rd->pkt_table_len; i++) {
        if ((p->rpch.recId & 1) == 0) {
            p->rpch.recId = (i << 16) | 5;
            ++rd->pid;
            if (rd->pid == 1) {
                ++rd->pid;
                sid = 1;
            } else {
                sid = rd->pid;
            }
            p->rpch.pktAddr = p;
            p->rpch.rpcId = sid;
            func_00184428();
            return p;
        }
        p++;
    }
    func_00184428();
    return 0;
}

/* Frees remote-call packet `packet`. */
void _sceRpcFreePacket(void *packet) {
    (*(s32 *)((u8 *)packet + 0x18)) = 0;
    (*(s32 *)((u8 *)packet + 0x10)) = (s32) ((*(s32 *)((u8 *)packet + 0x10)) & 0xFFFFFFFE);
}

/* A free remote-call packet from `data`. */
void *_sceRpcGetFPacket(s32 data) {
    u8 *q;
    s32 i;
    u8 *r;

    q = (u8 *)data;
    i = *(s32 *)(q + 0x24) % *(s32 *)(q + 0x18);
    r = *(u8 **)(q + 0x14) + i * 64;
    *(s32 *)(q + 0x24) = i + 1;
    return r;
}

/* A free remote-call packet from `data` at `rid`. */
void *_sceRpcGetFPacket2(void *data, s32 rid) {
    void *r;

    if (rid < 0 || rid >= *(s32 *)((u8 *)data + 0x20)) {
        r = _sceRpcGetFPacket((s32)data);
    } else {
        r = *(u8 **)((u8 *)data + 0x1C) + rid * 0x40;
    }
    return r;
}

/* _request_end: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

void _request_end(void *pkt, void *data) {
    SifRpcRendPkt *rend = pkt;
    sceSifRpcClientData *c;
    sceSifEndFunc fn;

    switch (rend->cid) {
    case 0x8000000A:
        c = rend->client;
        fn = c->endFunc;
        if (fn != 0) {
            fn(c->endParam);
        }
        break;
    case 0x80000009:
        c = rend->client;
        c->serve = rend->server;
        c->buff = rend->buff;
        c->cbuff = rend->cbuff;
        break;
    case 0x8000000C:
        break;
    }
    c = rend->client;
    if (c->sema >= 0) {
        iSignalSema(c->sema);
    }
    _sceRpcFreePacket(c->pkt);
    c->pkt = 0;
}

/* Handles an IOP request for EE data (`packet`, `data`). */
void _request_rdata(void *packet, s32 data) {
    void *sceRpcGetFPacket;
    s32 a;
    s32 b;

    sceRpcGetFPacket = _sceRpcGetFPacket(data);
    a = *(s32 *)((u8 *)packet + 0x14);
    b = *(s32 *)((u8 *)packet + 0x1C);
    (*(s32 *)((u8 *)sceRpcGetFPacket + 0x14)) = a;
    (*(s32 *)((u8 *)sceRpcGetFPacket + 0x1C)) = b;
    (*(s32 *)((u8 *)sceRpcGetFPacket + 0x20)) = 0x8000000C;
    isceSifSendCmd(0x80000008, sceRpcGetFPacket, 0x40, (*(s32 *)((u8 *)packet + 0x20)), (*(s32 *)((u8 *)packet + 0x24)), (*(s32 *)((u8 *)packet + 0x28)));
}

/* Reads `size` bytes from IOP address `src` into `dest` (`mode`). */
s32 sceSifGetOtherData(void *rd, s32 src, s32 dest, s32 size, s32 mode) {
    s32 sp0[8];
    void *p;

    p = _sceRpcGetPacket(&D_00312840);
    if (p == NULL) {
        return -1;
    }
    (*(void **)rd) = p;
    (*(s32 *)((u8 *)rd + 4)) = (*(s32 *)((u8 *)p + 0x18));
    (*(s32 *)((u8 *)p + 0x20)) = src;
    (*(s32 *)((u8 *)p + 0x24)) = dest;
    (*(s32 *)((u8 *)p + 0x28)) = size;
    (*(void **)((u8 *)p + 0x14)) = p;
    (*(void **)((u8 *)p + 0x1C)) = rd;
    if (!(mode & 1)) {
        sp0[1] = 1;
        sp0[2] = 0;
        (*(s32 *)((u8 *)rd + 8)) = CreateSema(sp0);
        if ((*(s32 *)((u8 *)rd + 8)) < 0) {
            _sceRpcFreePacket(p);
            return -3;
        }
        if (sceSifSendCmd(0x8000000C, p, 0x40, 0, 0, 0) == 0) {
            _sceRpcFreePacket(p);
            DeleteSema((*(s32 *)((u8 *)rd + 8)));
            return -2;
        }
        WaitSema((*(s32 *)((u8 *)rd + 8)));
        DeleteSema((*(s32 *)((u8 *)rd + 8)));
        return 0;
    }
    (*(s32 *)((u8 *)rd + 8)) = -1;
    if (sceSifSendCmd(0x8000000C, p, 0x40, 0, 0, 0) == 0) {
        _sceRpcFreePacket(p);
        return -2;
    }
    return 0;
}

typedef struct SifSrv_0017E7B0 {
    u32 sid;
    s32 unk4[13];
    struct SifSrv_0017E7B0 *link;
} SifSrv_0017E7B0;

typedef struct SifQ_0017E7B0 {
    s32 unk0[2];
    SifSrv_0017E7B0 *link;
    s32 unkC[2];
    struct SifQ_0017E7B0 *next;
} SifQ_0017E7B0;

/* The server of id `sid` in the server list (`data`). */
void *_search_svdata(s32 sid, s32 data) {
    SifSrv_0017E7B0 *server;
    SifQ_0017E7B0 *queue;

    queue = *(SifQ_0017E7B0 **)((u8 *)data + 0x28);
    while (queue) {
        server = queue->link;
        while (server) {
            if (server->sid == (u32)sid) {
                return server;
            }
            server = server->link;
        }
        queue = queue->next;
    }
    return NULL;
}

/* Handles an IOP bind request (`packet`, `data`). */
void _request_bind(void *packet, s32 data) {
    s32 hl0;
    void *sceRpcGetFPacket;
    void *svdata;

    sceRpcGetFPacket = _sceRpcGetFPacket(data);
    hl0 = (s32) (*(s32 *)((u8 *)packet + 0x14));
    (*(s32 *)((u8 *)sceRpcGetFPacket + 0x1C)) = (s32) (*(s32 *)((u8 *)packet + 0x1C));
    (*(s32 *)((u8 *)sceRpcGetFPacket + 0x14)) = hl0;
    (*(s32 *)((u8 *)sceRpcGetFPacket + 0x20)) = 0x80000009;
    svdata = _search_svdata((*(s32 *)((u8 *)packet + 0x20)), data);
    if (svdata == NULL) {
        (*(void **)((u8 *)sceRpcGetFPacket + 0x24)) = NULL;
        (*(s32 *)((u8 *)sceRpcGetFPacket + 0x28)) = 0;
        (*(s32 *)((u8 *)sceRpcGetFPacket + 0x2C)) = 0;
    } else {
        (*(void **)((u8 *)sceRpcGetFPacket + 0x24)) = svdata;
        (*(s32 *)((u8 *)sceRpcGetFPacket + 0x28)) = (s32) (*(s64 *)((u8 *)svdata + 8));
        (*(s32 *)((u8 *)sceRpcGetFPacket + 0x2C)) = (s32) (*(s32 *)((u8 *)svdata + 0x14));
    }
    isceSifSendCmd(0x80000008, sceRpcGetFPacket, 0x40, 0, 0, 0);
}

/* Binds remote call server `sid` on the IOP into client `cd` (`mode`). */
s32 sceSifBindRpc(void *cd, s32 sid, s32 mode) {
    s32 sp0[8];
    void *p;

    (*(s32 *)((u8 *)cd + 0x10)) = 0;
    (*(s32 *)((u8 *)cd + 0x24)) = 0;
    p = _sceRpcGetPacket(&D_00312840);
    if (p == NULL) {
        return -1;
    }
    (*(void **)cd) = p;
    (*(s32 *)((u8 *)cd + 4)) = (*(s32 *)((u8 *)p + 0x18));
    (*(s32 *)((u8 *)p + 0x20)) = sid;
    (*(void **)((u8 *)p + 0x14)) = p;
    (*(void **)((u8 *)p + 0x1C)) = cd;
    if (!(mode & 1)) {
        sp0[1] = 1;
        sp0[2] = 0;
        (*(s32 *)((u8 *)cd + 8)) = CreateSema(sp0);
        if ((*(s32 *)((u8 *)cd + 8)) < 0) {
            _sceRpcFreePacket(p);
            return -3;
        }
        if (sceSifSendCmd(0x80000009, p, 0x40, 0, 0, 0) == 0) {
            _sceRpcFreePacket(p);
            DeleteSema((*(s32 *)((u8 *)cd + 8)));
            return -2;
        }
        WaitSema((*(s32 *)((u8 *)cd + 8)));
        DeleteSema((*(s32 *)((u8 *)cd + 8)));
        return 0;
    }
    (*(s32 *)((u8 *)cd + 8)) = -1;
    if (sceSifSendCmd(0x80000009, p, 0x40, 0, 0, 0) == 0) {
        _sceRpcFreePacket(p);
        return -2;
    }
    return 0;
}

/* _request_call: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

void _request_call(void *pkt, void *data) {
    s32 *req = pkt;
    s32 *sd = (s32 *)req[13];
    s32 *q = (s32 *)sd[16];
    s32 *start = (s32 *)q[3];

    if (start == 0) {
        q[3] = (s32)sd;
    } else {
        ((s32 *)q[4])[15] = (s32)sd;
    }
    q[4] = (s32)sd;
    {
        s32 paddr = req[5], client = req[7];
        sd[8] = paddr;
        sd[7] = client;
    }
    sd[9] = req[8];
    sd[3] = req[9];
    sd[10] = req[10];
    sd[11] = req[11];
    sd[12] = req[12];
    sd[13] = req[4];
    if (q[0] < 0) {
        return;
    }
    if (q[1] != 0) {
        return;
    }
    iWakeupThread(q[0]);
}

/* sceSifCallRpc: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

s32 sceSifCallRpc(s32 *client, s32 rpc_number, s32 mode, s32 *sendbuf, s32 ssize, s32 *recvbuf, s32 rsize,
                  s32 end_func, s32 end_param) {
    sceSifRpcClientData *cd = (sceSifRpcClientData *)client;
    volatile s32 *vc = (volatile s32 *)cd;
    s32 *pkt;
    struct SemaParam buf;
    s32 pid;

    pkt = _sceRpcGetPacket(&D_00312840);
    if (pkt == 0) {
        return -1;
    }
    pid = pkt[6];
    vc[8] = end_param;
    vc[0] = (s32)pkt;
    vc[1] = pid;
    vc[7] = end_func;
    pkt[8] = rpc_number;
    pkt[9] = ssize;
    pkt[10] = (s32)recvbuf;
    pkt[11] = rsize;
    pkt[5] = (s32)pkt;
    pkt[13] = cd->serve;
    pkt[7] = (s32)cd;
    if ((mode & 2) == 0) {
        if (sendbuf == recvbuf) {
            func_0017E190(sendbuf, (ssize < rsize) ? rsize : ssize);
        } else {
            if (ssize > 0) {
                func_0017E190(sendbuf, ssize);
            }
            if (rsize > 0) {
                func_0017E190(recvbuf, rsize);
            }
        }
    }
    if (mode & 1) {
        if (end_func == 0) {
            pkt[12] = 0;
        } else {
            pkt[12] = 1;
        }
        cd->sema = -1;
        if (sceSifSendCmd(0x8000000A, pkt, 0x40, (s32)sendbuf, cd->buff, ssize) != 0) {
            return 0;
        }
        _sceRpcFreePacket(pkt);
        return -2;
    }
    buf.maxCount = 1;
    buf.initCount = 0;
    cd->sema = CreateSema(&buf);
    if (cd->sema < 0) {
        _sceRpcFreePacket(pkt);
        return -3;
    }
    pkt[12] = 1;
    if (sceSifSendCmd(0x8000000A, pkt, 0x40, (s32)sendbuf, cd->buff, ssize) == 0) {
        DeleteSema(cd->sema);
        _sceRpcFreePacket(pkt);
        return -2;
    }
    WaitSema(cd->sema);
    DeleteSema(cd->sema);
    return 0;
}

/* Whether remote call `cd` is still running. */
s32 sceSifCheckStatRpc(void *cd) {
    void *temp_a1;

    temp_a1 = (*(void **)cd);
    if ((temp_a1 == NULL) || ((*(s32 *)((u8 *)cd + 4)) != (*(s32 *)((u8 *)temp_a1 + 0x18))) || !((*(s32 *)((u8 *)temp_a1 + 0x10)) & 1)) {
        return 0;
    }
    return 1;
}

/* Sets up remote call queue `qd` for thread `thid`. */
void sceSifSetRpcQueue(void *qd, s32 thid) {
    u8 *b_D_00312840;
    void *temp_v0;
    void *var_a0;
    void *var_v1;

    func_001843E0();
    (*(s32 *)qd) = thid;
    (*(s32 *)((u8 *)qd + 4)) = 0;
    (*(s32 *)((u8 *)qd + 8)) = 0;
    (*(s32 *)((u8 *)qd + 0xC)) = 0;
    (*(s32 *)((u8 *)qd + 0x10)) = 0;
    (*(s32 *)((u8 *)qd + 0x14)) = 0;
    b_D_00312840 = (u8 *)&D_00312840;
    if ((*(void **)(b_D_00312840 + 0x28)) == NULL) {
        (*(void **)(b_D_00312840 + 0x28)) = qd;
    } else {
        var_a0 = (*(void **)(b_D_00312840 + 0x28));
        var_v1 = (*(void **)((u8 *)var_a0 + 0x14));
        if (var_v1 != NULL) {
            do {
                var_a0 = var_v1;
                temp_v0 = (*(void **)((u8 *)var_a0 + 0x14));
                var_v1 = temp_v0;
            } while (temp_v0 != NULL);
        }
        (*(void **)((u8 *)var_a0 + 0x14)) = qd;
    }
    func_00184428();
}

/* Registers remote call server `arg0` (id `arg1`, function `arg2`, buffer `arg3`, ...) in queue `arg6`. */
void func_0017ED48(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, void *arg6) {
    void *temp_v0;
    void *temp_v0_2;
    void *var_a0;
    void *var_v1;

    func_001843E0();
    (*(volatile s32 *)((u8 *)arg0 + 0x3C)) = 0;
    (*(volatile s32 *)((u8 *)arg0 + 0x38)) = 0;
    (*(volatile s32 *)arg0) = arg1;
    temp_v0 = (void *)(*(s32 *)((u8 *)arg6 + 8));
    (*(s32 *)((u8 *)arg0 + 4)) = arg2;
    (*(s32 *)((u8 *)arg0 + 8)) = arg3;
    (*(s32 *)((u8 *)arg0 + 0x10)) = arg4;
    (*(s32 *)((u8 *)arg0 + 0x14)) = arg5;
    (*(s32 *)((u8 *)arg0 + 0x40)) = (s32)arg6;
    if (temp_v0 == NULL) {
        (*(void **)((u8 *)arg6 + 8)) = arg0;
    } else {
        var_a0 = temp_v0;
        var_v1 = (*(void **)((u8 *)var_a0 + 0x38));
        if (var_v1 != NULL) {
            do {
                var_a0 = var_v1;
                temp_v0_2 = (*(void **)((u8 *)var_a0 + 0x38));
                var_v1 = temp_v0_2;
            } while (temp_v0_2 != NULL);
        }
        (*(void **)((u8 *)var_a0 + 0x38)) = arg0;
    }
    func_00184428();
}

/* Removes server `sd` from queue `qd`. */
void *sceSifRemoveRpc(void *sd, void *qd) {
    void *p;
    void *n;

    func_001843E0();
    p = (*(void **)((u8 *)qd + 8));
    if (p == sd) {
        (*(void **)((u8 *)qd + 8)) = (*(void **)((u8 *)p + 0x38));
    } else {
        for (; p != NULL; p = (*(void **)((u8 *)p + 0x38))) {
            if ((*(void **)((u8 *)p + 0x38)) == sd) {
                (*(void **)((u8 *)p + 0x38)) = (*(void **)((u8 *)sd + 0x38));
                break;
            }
        }
    }
    func_00184428();
    return p;
}

extern s32 D_00312840;

typedef struct SifRpcNode_0017EEB0 {
    s32 unk0[5];
    struct SifRpcNode_0017EEB0 *next;
} SifRpcNode_0017EEB0;

/* Removes remote call queue `qd`. */
void *sceSifRemoveRpcQueue(void *qd) {
    SifRpcNode_0017EEB0 *sd = qd;
    SifRpcNode_0017EEB0 *p;
    u8 *q;

    func_001843E0();
    q = (u8 *)&D_00312840;
    p = *(SifRpcNode_0017EEB0 **)(q + 0x28);
    if (p == sd) {
        *(SifRpcNode_0017EEB0 **)(q + 0x28) = p->next;
    } else {
        while (p != NULL) {
            if (p->next == sd) {
                p->next = sd->next;
                break;
            }
            p = p->next;
        }
    }
    func_00184428();
    return p;
}

/* The next remote call request in queue `qd`. */
void *sceSifGetNextRequest(void *qd) {
    void *temp_s1;

    func_001843E0();
    temp_s1 = (*(void **)((u8 *)qd + 0xC));
    if (temp_s1 == NULL) {
        (*(s32 *)((u8 *)qd + 4)) = 0;
    } else {
        (*(s32 *)((u8 *)qd + 4)) = 1;
        (*(void **)((u8 *)qd + 0xC)) = (void *) (*(void **)((u8 *)temp_s1 + 0x3C));
    }
    func_00184428();
    return temp_s1;
}

/* sceSifExecRequest: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

void sceSifExecRequest(void *data) {
    sceSifServeData *sd = data;
    s32 size = 0;
    void *rec;
    SifRpcRendPkt *pkt;
    s32 i;
    sceSifDmaData dmat[2];
    s32 j;
    s32 r;

    rec = sd->func(sd->fno, sd->buff, sd->size);
    if (rec != 0) {
        size = sd->rsize;
    }
    if (sd->size > 0) {
        func_0017E190(sd->buff, sd->size);
    }
    if (size > 0) {
        func_0017E190(rec, size);
    }
    func_001843E0();
    if (sd->rid & 4) {
        pkt = _sceRpcGetFPacket2(&D_00312840, sd->rid >> 16);
    } else {
        pkt = _sceRpcGetFPacket((s32)&D_00312840);
    }
    func_00184428();
    pkt->cid = 0x8000000A;
    pkt->client = sd->client;
    if (sd->rmode != 0) {
        while (sceSifSendCmd(0x80000008, pkt, 0x40, (s32)rec, (s32)sd->receive, size) == 0) {
            ;
        }
        return;
    }
    pkt->rpch.rpcId = 0;
    i = 0;
    pkt->rpch.recId = 0;
    if (size > 0) {
        dmat[0].src = (u32)rec;
        dmat[0].dest = (u32)sd->receive;
        dmat[0].size = size;
        dmat[0].u.attr = 0;
        i = 1;
    }
    dmat[i].src = (u32)pkt;
    dmat[i].dest = (u32)sd->paddr;
    dmat[i].size = 0x40;
    dmat[i].u.attr = 0;
    i++;
    do {
        r = sceSifSetDma((s32 *)dmat, i);
        if (r != 0) {
            break;
        }
        for (j = 0x100000; j != -1; j--) {
            ;
        }
    } while (r == 0);
}

/* Serves remote call queue `qd` forever. */
void sceSifRpcLoop(void *qd) {
    void *sd;

    while (1) {
        while ((sd = sceSifGetNextRequest(qd)) != NULL) {
            sceSifExecRequest(sd);
        }
        SleepThread();
    }
}

/* Creates the remote call library's two semaphores once. */
void func_0017F1A0(void) {
    s32 sp0[8];
    if (D_0028CAA8 == -1) {
        sp0[2] = 1;
        sp0[1] = 1;
        sp0[5] = 0;
        D_0028CAA8 = CreateSema(sp0);
        D_0028CAAC = CreateSema(sp0);
    }
}

/* new_iob: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

void *func_0017F200(void) {
    char *p;
    char *end;

    func_0017F1A0();
    ((s32 (*)(s32))WaitSema)(D_0028CAA8);
    p = D_00313980;
    end = p + 0x200;
    while (p < end) {
        if (*(s32 *)(p + 4) == 0) {
            *(s32 *)(p + 4) = 0x10000000;
            ((s32 (*)(s32))SignalSema)(D_0028CAA8);
            return p;
        }
        p += 0x10;
    }
    ((s32 (*)(s32))SignalSema)(D_0028CAA8);
    return 0;
}

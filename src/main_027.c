#include "common.h"

/* libdev: read VU0's control registers (status, MAC, clipping, R, I, Q, vi0-vi15) into a save area;
   returns 0 while VU0 is running (sceDevVu0CheckBusy) */

typedef struct Vu0Cnd_00186D78 {
    dk_int128 vf[32];
    u32 status;
    u32 mac;
    u32 clipping;
    u32 r;
    u32 i;
    u32 q;
    u16 vi[16];
} Vu0Cnd_00186D78;

#define CFC2_00186D78(dst, vi) __asm__("cfc2.ni %0, $" #vi : "=r"(dst))

/* VU0's registers and state into `cndIn`. */
s32 sceDevVu0GetCnd(void *cndIn) {
    Vu0Cnd_00186D78 *cnd = cndIn;
    register u32 s __asm__("$3");

    if (sceDevVu0CheckBusy() != 0) {
    return 0;
    }
    CFC2_00186D78(s, vi16);
    cnd->status = s;
    CFC2_00186D78(s, vi17);
    cnd->mac = s;
    CFC2_00186D78(s, vi18);
    cnd->clipping = s;
    CFC2_00186D78(s, vi20);
    cnd->r = s;
    CFC2_00186D78(s, vi21);
    cnd->i = s;
    CFC2_00186D78(s, vi22);
    cnd->q = s;
    CFC2_00186D78(s, vi0);
    cnd->vi[0] = s;
    CFC2_00186D78(s, vi1);
    cnd->vi[1] = s;
    CFC2_00186D78(s, vi2);
    cnd->vi[2] = s;
    CFC2_00186D78(s, vi3);
    cnd->vi[3] = s;
    CFC2_00186D78(s, vi4);
    cnd->vi[4] = s;
    CFC2_00186D78(s, vi5);
    cnd->vi[5] = s;
    CFC2_00186D78(s, vi6);
    cnd->vi[6] = s;
    CFC2_00186D78(s, vi7);
    cnd->vi[7] = s;
    CFC2_00186D78(s, vi8);
    cnd->vi[8] = s;
    CFC2_00186D78(s, vi9);
    cnd->vi[9] = s;
    CFC2_00186D78(s, vi10);
    cnd->vi[10] = s;
    CFC2_00186D78(s, vi11);
    cnd->vi[11] = s;
    CFC2_00186D78(s, vi12);
    cnd->vi[12] = s;
    CFC2_00186D78(s, vi13);
    cnd->vi[13] = s;
    CFC2_00186D78(s, vi14);
    cnd->vi[14] = s;
    CFC2_00186D78(s, vi15);
    cnd->vi[15] = s;
    return 1;
}

#undef CFC2_00186D78

/* libdev: write VU0's registers back from a save area (vf0-vf31, status, MAC, clipping, R, I, Q, vi0-vi15);
   returns 0 while VU0 is running (sceDevVu0CheckBusy). The reader is sceDevVu0GetCnd. */

typedef struct Vu0Cnd_00186E58 {
    dk_int128 vf[32];
    u32 status;
    u32 mac;
    u32 clipping;
    u32 r;
    u32 i;
    u32 q;
    u16 vi[16];
} Vu0Cnd_00186E58;

#define CTC2_00186E58(src, vi) __asm__ __volatile__("ctc2.ni %0, $" #vi : : "r"(src))

/* Sets VU0's registers and state from `cndIn`. */
s32 sceDevVu0PutCnd(void *cndIn) {
    dk_int128 *vf;
    Vu0Cnd_00186E58 *cnd = cndIn;
    u32 s;

    vf = cnd->vf;

    if (sceDevVu0CheckBusy() != 0) {
        return 0;
    }
    __asm__ __volatile__("lqc2 $vf0, 0x0(%0)" : : "r"(vf));
    __asm__ __volatile__("lqc2 $vf1, 0x10(%0)" : : "r"(vf));
    __asm__ __volatile__("lqc2 $vf2, 0x20(%0)" : : "r"(vf));
    __asm__ __volatile__("lqc2 $vf3, 0x30(%0)" : : "r"(vf));
    __asm__ __volatile__("lqc2 $vf4, 0x40(%0)" : : "r"(vf));
    __asm__ __volatile__("lqc2 $vf5, 0x50(%0)" : : "r"(vf));
    __asm__ __volatile__("lqc2 $vf6, 0x60(%0)" : : "r"(vf));
    __asm__ __volatile__("lqc2 $vf7, 0x70(%0)" : : "r"(vf));
    __asm__ __volatile__("lqc2 $vf8, 0x80(%0)" : : "r"(vf));
    __asm__ __volatile__("lqc2 $vf9, 0x90(%0)" : : "r"(vf));
    __asm__ __volatile__("lqc2 $vf10, 0xA0(%0)" : : "r"(vf));
    __asm__ __volatile__("lqc2 $vf11, 0xB0(%0)" : : "r"(vf));
    __asm__ __volatile__("lqc2 $vf12, 0xC0(%0)" : : "r"(vf));
    __asm__ __volatile__("lqc2 $vf13, 0xD0(%0)" : : "r"(vf));
    __asm__ __volatile__("lqc2 $vf14, 0xE0(%0)" : : "r"(vf));
    __asm__ __volatile__("lqc2 $vf15, 0xF0(%0)" : : "r"(vf));
    __asm__ __volatile__("lqc2 $vf16, 0x100(%0)" : : "r"(vf));
    __asm__ __volatile__("lqc2 $vf17, 0x110(%0)" : : "r"(vf));
    __asm__ __volatile__("lqc2 $vf18, 0x120(%0)" : : "r"(vf));
    __asm__ __volatile__("lqc2 $vf19, 0x130(%0)" : : "r"(vf));
    __asm__ __volatile__("lqc2 $vf20, 0x140(%0)" : : "r"(vf));
    __asm__ __volatile__("lqc2 $vf21, 0x150(%0)" : : "r"(vf));
    __asm__ __volatile__("lqc2 $vf22, 0x160(%0)" : : "r"(vf));
    __asm__ __volatile__("lqc2 $vf23, 0x170(%0)" : : "r"(vf));
    __asm__ __volatile__("lqc2 $vf24, 0x180(%0)" : : "r"(vf));
    __asm__ __volatile__("lqc2 $vf25, 0x190(%0)" : : "r"(vf));
    __asm__ __volatile__("lqc2 $vf26, 0x1A0(%0)" : : "r"(vf));
    __asm__ __volatile__("lqc2 $vf27, 0x1B0(%0)" : : "r"(vf));
    __asm__ __volatile__("lqc2 $vf28, 0x1C0(%0)" : : "r"(vf));
    __asm__ __volatile__("lqc2 $vf29, 0x1D0(%0)" : : "r"(vf));
    __asm__ __volatile__("lqc2 $vf30, 0x1E0(%0)" : : "r"(vf));
    __asm__ __volatile__("lqc2 $vf31, 0x1F0(%0)" : : "r"(vf));
    s = cnd->status;
    CTC2_00186E58(s, vi16);
    s = cnd->mac;
    CTC2_00186E58(s, vi17);
    s = cnd->clipping;
    CTC2_00186E58(s, vi18);
    s = cnd->r;
    CTC2_00186E58(s, vi20);
    s = cnd->i;
    CTC2_00186E58(s, vi21);
    s = cnd->q;
    CTC2_00186E58(s, vi22);
    s = cnd->vi[0];
    CTC2_00186E58(s, vi0);
    s = cnd->vi[1];
    CTC2_00186E58(s, vi1);
    s = cnd->vi[2];
    CTC2_00186E58(s, vi2);
    s = cnd->vi[3];
    CTC2_00186E58(s, vi3);
    s = cnd->vi[4];
    CTC2_00186E58(s, vi4);
    s = cnd->vi[5];
    CTC2_00186E58(s, vi5);
    s = cnd->vi[6];
    CTC2_00186E58(s, vi6);
    s = cnd->vi[7];
    CTC2_00186E58(s, vi7);
    s = cnd->vi[8];
    CTC2_00186E58(s, vi8);
    s = cnd->vi[9];
    CTC2_00186E58(s, vi9);
    s = cnd->vi[10];
    CTC2_00186E58(s, vi10);
    s = cnd->vi[11];
    CTC2_00186E58(s, vi11);
    s = cnd->vi[12];
    CTC2_00186E58(s, vi12);
    s = cnd->vi[13];
    CTC2_00186E58(s, vi13);
    s = cnd->vi[14];
    CTC2_00186E58(s, vi14);
    s = cnd->vi[15];
    CTC2_00186E58(s, vi15);
    return 1;
}

#undef CTC2_00186E58

/* Resets VIF0. */
void sceDevVif0Reset(void) {
    *(volatile s32 *)0x10003810 = 1;
    *(volatile s32 *)0x10003820 = 6;
}

/* Stops VIF0 (`mode`). */
s32 sceDevVif0Pause(s32 mode) {
    s32 r;

    r = sceDevVif0Sync();
    if (r == 0) {
        return 0;
    }
    if (r == 1) {
        return 0;
    }
    if (mode == 0) {
        *(volatile s32 *)0x10003810 = 2;
    } else if (mode == 1) {
        *(volatile s32 *)0x10003810 = 4;
    }
    return 1;
}

/* Restarts VIF0. */
s32 sceDevVif0Continue(void) {
    if (sceDevVif0Sync() != 1) {
        return 0;
    }
    *(volatile u32 *)0x10003810 = 8;
    return 1;
}

/* Sets VIF0's error masks. */
u32 sceDevVif0PutErr(u32 interrupt, u32 miss1, u32 miss2) {
    u32 v = interrupt | (miss1 << 1) | (miss2 << 2);
    *(volatile u32 *)0x10003820 = v;
    return v;
}

/* VIF0's error masks. */
s32 sceDevVif0GetErr(void) {
    return *(volatile s32 *)0x10003820;
}

/* Waits for VIF0 to finish. */
u32 sceDevVif0Sync(void) {
    s32 temp_a0;

    temp_a0 = *(volatile s32 *)0x10003800;
    if (!(temp_a0 & 3)) {
        return 0U;
    }
    if (temp_a0 & 0x700) {
        return 1U;
    }
    if (temp_a0 & 0xC) {
        return 2U;
    }
    return (temp_a0 & 0x3000) ? 3U : 4U;
}

/* VIF0's registers and state into `cnd`. */
s32 sceDevVif0GetCnd(void *cnd) {
    u32 temp_s4;

    temp_s4 = *(volatile u32 *)0x10003840;
    if (sceDevVif0Sync() >= 2U) {
        return 0;
    }
    (*(s32 *)cnd) = (s32) *(volatile s32 *)0x10003900;
    (*(s32 *)((u8 *)cnd + 4)) = (s32) *(volatile s32 *)0x10003910;
    (*(s32 *)((u8 *)cnd + 8)) = (s32) *(volatile s32 *)0x10003920;
    (*(s32 *)((u8 *)cnd + 0xC)) = (s32) *(volatile s32 *)0x10003930;
    (*(s32 *)((u8 *)cnd + 0x10)) = (s32) *(volatile s32 *)0x10003940;
    (*(s32 *)((u8 *)cnd + 0x14)) = (s32) *(volatile s32 *)0x10003950;
    (*(s32 *)((u8 *)cnd + 0x18)) = (s32) *(volatile s32 *)0x10003960;
    (*(s32 *)((u8 *)cnd + 0x1C)) = (s32) *(volatile s32 *)0x10003970;
    (*(s32 *)((u8 *)cnd + 0x20)) = (s32) *(volatile s32 *)0x10003870;
    (*(s32 *)((u8 *)cnd + 0x24)) = (s32) *(volatile s32 *)0x10003880;
    (*(s32 *)((u8 *)cnd + 0x28)) = (s32) *(volatile s32 *)0x10003800;
    (*(s16 *)((u8 *)cnd + 0x2C)) = (s16) *(volatile s32 *)0x100038D0;
    (*(s16 *)((u8 *)cnd + 0x2E)) = (s16) *(volatile s32 *)0x10003890;
    (*(s16 *)((u8 *)cnd + 0x30)) = (s16) *(volatile s32 *)0x10003830;
    (*(s16 *)((u8 *)cnd + 0x32)) = (s16) *(volatile s32 *)0x10003860;
    (*(s8 *)((u8 *)cnd + 0x34)) = (s8) *(volatile s32 *)0x10003820;
    (*(s8 *)((u8 *)cnd + 0x35)) = (s8) temp_s4;
    (*(s8 *)((u8 *)cnd + 0x36)) = (s8) (temp_s4 >> 8);
    (*(s8 *)((u8 *)cnd + 0x37)) = (s8) *(volatile s32 *)0x10003850;
    return 1;
}

/* Sends `n` quadwords from `data` into VIF0's FIFO. */
s32 sceDevVif0PutFifo(__int128 *data, s32 n) {
    s32 i = 0;

    while (--n != -1) {
        if (*(volatile u32 *)0x10003800 & 0x10000000) {
            return i;
        }
        *(volatile __int128 *)0x10004000 = *data++;
        i++;
    }
    return i;
}

/* Starts GIF packet `pkt` in buffer `buf`. */
void sceGifPkInit(void *pkt, u64 buf) {
    __asm__ __volatile__("\n\
	sw	%1,0x0(%0)\n\
	sw	$0,0x8(%0)\n\
	sw	%1,0x4(%0)\n\
	" :  : "r" (pkt), "r" (buf));
}

/* Rewinds GIF packet `pkt`. */
void sceGifPkReset(void *pkt) {
    (*(s32 *)((u8 *)pkt + 8)) = 0;
    (*(s32 *)pkt) = (s32) (*(s32 *)((u8 *)pkt + 4));
}

/* Closes GIF packet `pkt`; returns its end. */
s32 sceGifPkTerminate(void *pkt) {
    s32 *temp_a2;
    s32 var_a1;

    var_a1 = (*(s32 *)pkt);
    temp_a2 = (*(s32 **)((u8 *)pkt + 8));
    if (var_a1 & 0xC) {
        do {
            *(s32 *)var_a1 = 0;
            var_a1 += 4;
        } while (var_a1 & 0xC);
    }
    if (temp_a2 != NULL) {
        s32 n = (((__int128 *)var_a1) - ((__int128 *)temp_a2)) - 1; *temp_a2 += n;
    }
    (*(s32 *)pkt) = var_a1;
    (*(s32 **)((u8 *)pkt + 8)) = NULL;
    return var_a1;
}

/* Adds a DMA "cnt" tag to GIF packet `pkt`. */
void sceGifPkCnt(void *pkt, s32 arg1, s32 arg2, s32 arg3) {
    u32 *tag;
    s32 ret;

    ret = sceGifPkTerminate(pkt);
    tag = *(u32 **)pkt;
    *(u32 **)((u8 *)pkt + 8) = (u32 *)ret;
    *tag++ = arg3 | 0x10000000;
    tag[1] = arg1;
    *(u32 **)pkt = tag + 3;
    tag[2] = arg2;
    tag[0] = 0;
}

/* Adds a DMA "ref" tag (`addr`, `size`) to GIF packet `pkt`. */
void sceGifPkRef(void *pkt, s32 addr, s32 size, s32 a3, s32 a4, s32 a5) {
    u32 *tag;

    sceGifPkTerminate(pkt);
    tag = *(u32 **)pkt;
    size |= 0x30000000;
    *tag++ = a5 | size;
    tag[0] = addr & 0x9FFFFFFF;
    tag[1] = a3;
    tag[2] = a4;
    *(u32 **)pkt = tag + 3;
}

/* Adds a DMA "end" tag to GIF packet `pkt`. */
void sceGifPkEnd(void *pkt, s32 arg1, s32 arg2, s32 arg3) {
    u32 *tag;
    s32 ret;

    ret = sceGifPkTerminate(pkt);
    tag = *(u32 **)pkt;
    *(u32 **)((u8 *)pkt + 8) = (u32 *)ret;
    *tag++ = arg3 | 0x70000000;
    tag[1] = arg1;
    *(u32 **)pkt = tag + 3;
    tag[2] = arg2;
    tag[0] = 0;
}

/* Reserves `count` words in GIF packet `pkt`. */
void *sceGifPkReserve(void *pkt, s32 count) {
    u32 *cur = *(u32 **)pkt;

    *(u32 **)pkt = cur + count;
    return cur;
}

/* Opens GIF tag `tag` in packet `pkt`. */
void sceGifPkOpenGifTag(s32 *pkt, __int128 tag) {
    __int128 *p = (__int128 *) pkt[0];
    *p = tag;
    pkt[3] = (s32) p;
    pkt[0] = (s32) (p + 1);
}

/* Closes the open GIF tag of packet `pkt` (sets its loop count). */
void sceGifPkCloseGifTag(void *pkt) {
    u64 *code = *(u64 **)((u8 *)pkt + 0xC);
    s32 cur = *(s32 *)pkt;
    u64 v = *code;
    u32 n = ((cur - (s32)code) >> 3) - 2;
    u64 mode = (v >> 58) & 3;
    u32 d;
    s32 p;

    if (mode != 1) {
        n >>= 1;
    }
    if (mode != 2) {
        d = v >> 60;
        if (d == 0) {
            d = 16;
        }
        n = (n + d - 1) / d;
    }
    *(s32 *)((u8 *)pkt + 0xC) = 0;
    *code = v + n;
    p = cur;
    if (p & 0xC) {
        do {
            *(s32 *)p = 0;
            p += 4;
        } while (p & 0xC);
    }
    *(s32 *)pkt = p;
}

/* Adds GS register write `addr` = `data` to packet `pkt`. */
void sceGifPkAddGsAD(u64 **pkt, u32 addr, u64 data) {
    u64 *p = *pkt;
    *p++ = data;
    *p++ = addr;
    *pkt = p;
}

/* Starts VIF1 packet `pkt` in buffer `buf`. */
void sceVif1PkInit(s32 *pkt, s32 buf) {
    pkt[1] = buf;
    pkt[0] = buf;
    pkt[2] = 0;
}

/* Closes VIF1 packet `pkt`; returns its end. */
s32 sceVif1PkTerminate(void *pkt) {
    s32 *temp_a2;
    s32 var_a1;

    var_a1 = (*(s32 *)pkt);
    temp_a2 = (*(s32 **)((u8 *)pkt + 8));
    if (var_a1 & 0xC) {
        do {
            *(s32 *)var_a1 = 0;
            var_a1 += 4;
        } while (var_a1 & 0xC);
    }
    if (temp_a2 != NULL) {
        s32 n = (((__int128 *)var_a1) - ((__int128 *)temp_a2)) - 1; *temp_a2 += n;
    }
    (*(s32 *)pkt) = var_a1;
    (*(s32 **)((u8 *)pkt + 8)) = NULL;
    return var_a1;
}

/* Adds a DMA "cnt" tag to VIF1 packet `pkt`. */
void sceVif1PkCnt(void *pkt, s32 arg1) {
    u32 *tag;
    s32 ret;

    ret = sceVif1PkTerminate(pkt);
    tag = *(u32 **)pkt;
    *(u32 **)((u8 *)pkt + 8) = (u32 *)ret;
    *tag++ = arg1 | 0x10000000;
    *(s32 *)((u8 *)pkt + 0xC) = 0;
    *(u32 **)pkt = tag + 1;
    tag[0] = 0;
}

/* Opens GIF tag `tag` in VIF1 packet `pkt`. */
void sceVif1PkOpenGifTag(void *pkt, __int128 tag) {
    __int128 *temp_v0;

    temp_v0 = (*(__int128 **)pkt);
    *temp_v0 = tag;
    (*(__int128 **)((u8 *)pkt + 0x14)) = temp_v0;
    (*(__int128 **)pkt) = (__int128 *) (temp_v0 + 1);
}

/* Closes the open GIF tag of VIF1 packet `pkt`. */
void sceVif1PkCloseGifTag(void *pkt) {
    u64 *code = *(u64 **)((u8 *)pkt + 0x14);
    s32 cur = *(s32 *)pkt;
    u64 v = *code;
    u32 n = ((cur - (s32)code) >> 3) - 2;
    u64 mode = (v >> 58) & 3;
    u32 d;
    s32 p;

    if (mode != 1) {
        n >>= 1;
    }
    if (mode != 2) {
        d = v >> 60;
        if (d == 0) {
            d = 16;
        }
        n = (n + d - 1) / d;
    }
    *(s32 *)((u8 *)pkt + 0x14) = 0;
    *code = v + n;
    p = cur;
    if (p & 0xC) {
        do {
            *(s32 *)p = 0;
            p += 4;
        } while (p & 0xC);
    }
    *(s32 *)pkt = p;
}

/* libvifpk's sceVif1Packet */
struct sceVif1Packet {
    u32 *pCurrent;
    u32 *pBase;
    u32 *pDmaTag;
    u32 *pVifCode;
    u32 numlen;
    u32 pad;
};

#define pPacket ((struct sceVif1Packet *)pkt)

/* Pads VIF1 packet `pkt` to a `bit` boundary at `pos`. */
void sceVif1PkAlign(void *pkt, s32 bit, s32 pos)
{
    u32 ma;
    u32 end;

    ma = 0xffffffff >> (32 - ((bit + 2) & 0x1f));
    end = ((u32)pPacket->pCurrent & ~ma) + pos * 4;
    if (end < (u32)pPacket->pCurrent) {
        end = end + (ma + 1);
    }
    while ((u32)pPacket->pCurrent < end) {
        *pPacket->pCurrent++ = 0;
    }
}

#undef pPacket

/* Adds VIF code `code` to packet `pkt`. */
void sceVif1PkAddCode(s32 **pkt, s32 code) {
    *(*pkt)++ = code;
}

/* Adds data word `data` to packet `pkt`. */
void sceVif1PkAddData(s32 **pkt, s32 data) {
    *(*pkt)++ = data;
}

/* Adds GS register write `addr` = `data` to VIF1 packet `pkt`. */
void sceVif1PkAddGsAD(void *pkt, s32 addr, s64 data) {
    u32 *tag;

    tag = *(u32 **)pkt;
    *tag++ = (s32)data;
    tag[0] = data >> 32;
    *(u32 **)pkt = tag + 3;
    tag[1] = addr;
    tag[2] = 0;
}

/* Opens a DIRECTHL block in VIF1 packet `pkt` (`irq`). */
void sceVif1PkOpenDirectHLCode(void *pkt, s32 irq) {
    s32 *temp_a1;

    sceVif1PkAlign(pkt, 2, 3);
    temp_a1 = (*(s32 **)pkt);
    (*(s32 **)((u8 *)pkt + 0xC)) = temp_a1;
    (*(s32 **)pkt) = (s32 *) (temp_a1 + 1);
    *temp_a1 = (irq != 0) ? 0xD1000000 : 0x51000000;
}

/* Closes the open DIRECTHL block of VIF1 packet `pkt`. */
void sceVif1PkCloseDirectHLCode(void *pkt) {
    u32 *tag;
    u32 *end;

    tag = *(u32 **)((u8 *)pkt + 0xC);
    *(u32 **)((u8 *)pkt + 0xC) = NULL;
    end = *(u32 **)pkt - 1;
    *tag += (u32)(end - tag) >> 2;
}

/* `v0` = matrix `m0` times vector `v1`. */
void sceVu0ApplyMatrix(void *v0, void *m0, void *v1) {
    __asm__ __volatile__("\n\
	lqc2	$vf4,0x0(%1)\n\
	lqc2	$vf5,0x10(%1)\n\
	lqc2	$vf6,0x20(%1)\n\
	lqc2	$vf7,0x30(%1)\n\
	lqc2	$vf8,0x0(%2)\n\
	vmulax.xyzw	$ACC,$vf4,$vf8x\n\
	vmadday.xyzw	$ACC,$vf5,$vf8y\n\
	vmaddaz.xyzw	$ACC,$vf6,$vf8z\n\
	vmaddw.xyzw	$vf9,$vf7,$vf8w\n\
	sqc2	$vf9,0x0(%0)\n\
	" :  : "r" (v0), "r" (m0), "r" (v1));
}

/* `m0` = matrix `m1` times matrix `m2`. */
void sceVu0MulMatrix(void *m0, void *m1, void *m2) {
    __asm__ __volatile__("\n\
	lqc2	$vf4,0x0(%1)\n\
	lqc2	$vf5,0x10(%1)\n\
	lqc2	$vf6,0x20(%1)\n\
	lqc2	$vf7,0x30(%1)\n\
	addiu	$7,$0,0x4\n\
_func_00187910_00187924:\n\
	lqc2	$vf8,0x0(%2)\n\
	vmulax.xyzw	$ACC,$vf4,$vf8x\n\
	vmadday.xyzw	$ACC,$vf5,$vf8y\n\
	vmaddaz.xyzw	$ACC,$vf6,$vf8z\n\
	vmaddw.xyzw	$vf9,$vf7,$vf8w\n\
	sqc2	$vf9,0x0(%0)\n\
	addi	$7,$7,-0x1\n\
	addi	%2,%2,0x10\n\
	addi	%0,%0,0x10\n\
	bne	$0,$7,_func_00187910_00187924\n\
	" :  : "r" (m0), "r" (m1), "r" (m2));
}

/* `v0` = cross product of `v1` and `v2`. */
void sceVu0OuterProduct(void *v0, void *v1, void *v2) {
    __asm__ __volatile__("\n\
	lqc2	$vf4,0x0(%1)\n\
	lqc2	$vf5,0x0(%2)\n\
	vopmula.xyz	$ACC,$vf4,$vf5\n\
	vopmsub.xyz	$vf6,$vf5,$vf4\n\
	vsub.w	$vf6,$vf6,$vf6\n\
	sqc2	$vf6,0x0(%0)\n\
	" :  : "r" (v0), "r" (v1), "r" (v2));
}

/* The dot product of `v0` and `v1`. */
float sceVu0InnerProduct(void *v0, void *v1) {
    float ret;
    __asm__ __volatile__("\n\
	lqc2	$vf4,0x0(%1)\n\
	lqc2	$vf5,0x0(%2)\n\
	vmul.xyz	$vf5,$vf4,$vf5\n\
	vaddy.x	$vf5,$vf5,$vf5y\n\
	vaddz.x	$vf5,$vf5,$vf5z\n\
	qmfc2.ni	$2,$vf5\n\
	mtc1	$2,%0\n\
	" : "=f" (ret) : "r" (v0), "r" (v1));
    return ret;
}

/* `v0` = `v1` made unit length. */
void sceVu0Normalize(void *v0, void *v1) {
    __asm__ __volatile__("\n\
	lqc2	$vf4,0x0(%1)\n\
	vmul.xyz	$vf5,$vf4,$vf4\n\
	vaddy.x	$vf5,$vf5,$vf5y\n\
	vaddz.x	$vf5,$vf5,$vf5z\n\
	.word 0x4A0503BD\n\
	vwaitq\n\
	vaddq.x	$vf5,$vf0,$Q\n\
	vnop\n\
	vnop\n\
	vdiv	$Q,$vf0w,$vf5x\n\
	vsub.xyzw	$vf6,$vf0,$vf0\n\
	vwaitq\n\
	vmulq.xyz	$vf6,$vf4,$Q\n\
	sqc2	$vf6,0x0(%0)\n\
	" :  : "r" (v0), "r" (v1));
}

/* `m0` = `m1` transposed. */
void sceVu0TransposeMatrix(void *m0, void *m1) {
    __asm__ __volatile__("\n\
	lq $8,0x0000(%1)\n\
	lq $9,0x0010(%1)\n\
	lq $10,0x0020(%1)\n\
	lq $11,0x0030(%1)\n\
	pextlw     $12,$9,$8\n\
	pextuw     $13,$9,$8\n\
	pextlw     $14,$11,$10\n\
	pextuw     $15,$11,$10\n\
	pcpyld     $8,$14,$12\n\
	pcpyud     $9,$12,$14\n\
	pcpyld     $10,$15,$13\n\
	pcpyud     $11,$13,$15\n\
	sq $8,0x0000(%0)\n\
	sq $9,0x0010(%0)\n\
	sq $10,0x0020(%0)\n\
	sq $11,0x0030(%0)\n\
	" : : "r" (m0) , "r" (m1));
}

/* `m0` = the inverse of rotation-translation matrix `m1`. */
void sceVu0InversMatrix(void *m0, void *m1) {
    __asm__ __volatile__("\n\
	lq	$8,0x0(%1)\n\
	lq	$9,0x10(%1)\n\
	lq	$10,0x20(%1)\n\
	lqc2	$vf4,0x30(%1)\n\
	vmove.xyzw	$vf5,$vf4\n\
	vsub.xyz	$vf4,$vf4,$vf4\n\
	vmove.xyzw	$vf9,$vf4\n\
	qmfc2.ni	$11,$vf4\n\
	pextlw	$12,$9,$8\n\
	pextuw	$13,$9,$8\n\
	pextlw	$14,$11,$10\n\
	pextuw	$15,$11,$10\n\
	pcpyld	$8,$14,$12\n\
	pcpyud	$9,$12,$14\n\
	pcpyld	$10,$15,$13\n\
	qmtc2.ni	$8,$vf6\n\
	qmtc2.ni	$9,$vf7\n\
	qmtc2.ni	$10,$vf8\n\
	vmulax.xyz	$ACC,$vf6,$vf5x\n\
	vmadday.xyz	$ACC,$vf7,$vf5y\n\
	vmaddz.xyz	$vf4,$vf8,$vf5z\n\
	vsub.xyz	$vf4,$vf9,$vf4\n\
	sq	$8,0x0(%0)\n\
	sq	$9,0x10(%0)\n\
	sq	$10,0x20(%0)\n\
	sqc2	$vf4,0x30(%0)\n\
	" :  : "r" (m0), "r" (m1));
}

/* `v0` = `v1` divided by `f0`. */
void sceVu0DivVector(void *v0, void *v1, float f0) {
    __asm__ __volatile__("\n\
	lqc2	$vf4,0x0(%1)\n\
	.set noreorder\n\
	mfc1	$8,%2\n\
	qmtc2.ni	$8,$vf5\n\
	.set reorder\n\
	vdiv	$Q,$vf0w,$vf5x\n\
	vwaitq\n\
	vmulq.xyzw	$vf4,$vf4,$Q\n\
	sqc2	$vf4,0x0(%0)\n\
	" :  : "r" (v0), "r" (v1), "f" (f0));
}

/* `v0` = `v1`'s x, y, z divided by `f0`. */
void sceVu0DivVectorXYZ(void *v0, void *v1, float f0) {
    __asm__ __volatile__("\n\
	lqc2	$vf4,0x0(%1)\n\
	.set noreorder\n\
	mfc1	$8,%2\n\
	qmtc2.ni	$8,$vf5\n\
	.set reorder\n\
	vdiv	$Q,$vf0w,$vf5x\n\
	vwaitq\n\
	vmulq.xyz	$vf4,$vf4,$Q\n\
	sqc2	$vf4,0x0(%0)\n\
	" :  : "r" (v0), "r" (v1), "f" (f0));
}

/* `v0` = `v1` and `v2` mixed by `f0`. */
void sceVu0InterVector(void *v0, void *v1, void *v2, float f0) {
    __asm__ __volatile__("\n\
	lqc2	$vf4,0x0(%1)\n\
	lqc2	$vf5,0x0(%2)\n\
	.set noreorder\n\
	mfc1	$8,%3\n\
	qmtc2.ni	$8,$vf6\n\
	.set reorder\n\
	vaddw.x	$vf7,$vf0,$vf0w\n\
	vsub.x	$vf8,$vf7,$vf6\n\
	vmulax.xyzw	$ACC,$vf4,$vf6x\n\
	vmaddx.xyzw	$vf9,$vf5,$vf8x\n\
	sqc2	$vf9,0x0(%0)\n\
	" :  : "r" (v0), "r" (v1), "r" (v2), "f" (f0));
}

/* `v0` = `v1` + `v2`. */
void sceVu0AddVector(void *v0, void *v1, void *v2) {
    __asm__ __volatile__("\n\
	lqc2    $vf4,0x0(%1)\n\
	lqc2    $vf5,0x0(%2)\n\
	vadd.xyzw	$vf6,$vf4,$vf5\n\
	sqc2    $vf6,0x0(%0)\n\
	" : : "r" (v0) , "r" (v1), "r" (v2));
}

/* `v0` = `v1` - `v2`. */
void sceVu0SubVector(void *v0, void *v1, void *v2) {
    __asm__ __volatile__("\n\
	lqc2    $vf4,0x0(%1)\n\
	lqc2    $vf5,0x0(%2)\n\
	.word 0x4BE521AC\n\
	sqc2    $vf6,0x0(%0)\n\
	" : : "r" (v0) , "r" (v1), "r" (v2));
}

/* `v0` = `v1` times `v2`, element by element. */
void sceVu0MulVector(void *v0, void *v1, void *v2) {
    __asm__ __volatile__("\n\
	lqc2	$vf4,0x0(%1)\n\
	lqc2	$vf5,0x0(%2)\n\
	vmul.xyzw	$vf6,$vf4,$vf5\n\
	sqc2	$vf6,0x0(%0)\n\
	" :  : "r" (v0), "r" (v1), "r" (v2));
}

/* `v0` = `v1` times `f0`. */
void sceVu0ScaleVector(void *v0, void *v1, float f0) {
    __asm__ __volatile__("\n\
	lqc2	$vf4,0x0(%1)\n\
	.set noreorder\n\
	mfc1	$8,%2\n\
	qmtc2.ni	$8,$vf5\n\
	.set reorder\n\
	vmulx.xyzw	$vf6,$vf4,$vf5x\n\
	sqc2	$vf6,0x0(%0)\n\
	" :  : "r" (v0), "r" (v1), "f" (f0));
}

/* `m0` = `m1` moved by `tv`. */
void sceVu0TransMatrix(void *m0, void *m1, void *tv) {
    __asm__ __volatile__("\n\
	lqc2	$vf4,0x0(%2)\n\
	lqc2	$vf5,0x30(%1)\n\
	lq	$7,0x0(%1)\n\
	lq	$8,0x10(%1)\n\
	lq	$9,0x20(%1)\n\
	vadd.xyz	$vf5,$vf5,$vf4\n\
	sq	$7,0x0(%0)\n\
	sq	$8,0x10(%0)\n\
	sq	$9,0x20(%0)\n\
	sqc2	$vf5,0x30(%0)\n\
	" :  : "r" (m0), "r" (m1), "r" (tv));
}

/* `v0` = `v1`. */
void sceVu0CopyVector(void *v0, void *v1) {
    __asm__ __volatile__("\n\
	lq	$6,0x0(%1)\n\
	sq	$6,0x0(%0)\n\
	" :  : "r" (v0), "r" (v1));
}

/* `m0` = `m1`. */
void sceVu0CopyMatrix(void *m0, void *m1) {
    __asm__ __volatile__("\n\
	lq    $6,0x0(%1)\n\
	lq    $7,0x10(%1)\n\
	lq    $8,0x20(%1)\n\
	lq    $9,0x30(%1)\n\
	sq    $6,0x0(%0)\n\
	sq    $7,0x10(%0)\n\
	sq    $8,0x20(%0)\n\
	sq    $9,0x30(%0)\n\
	" : : "r" (m0) , "r" (m1));
}

/* `v0` = `v1` as fixed point (4 fraction bits). */
void sceVu0FTOI4Vector(void *v0, void *v1) {
    __asm__ __volatile__("\n\
	lqc2	$vf4,0x0(%1)\n\
	vftoi4.xyzw	$vf5,$vf4\n\
	sqc2	$vf5,0x0(%0)\n\
	" :  : "r" (v0), "r" (v1));
}

/* `v0` = `v1` as integers. */
void sceVu0FTOI0Vector(void *v0, void *v1) {
    __asm__ __volatile__("\n\
	lqc2	$vf4,0x0(%1)\n\
	vftoi0.xyzw	$vf5,$vf4\n\
	sqc2	$vf5,0x0(%0)\n\
	" :  : "r" (v0), "r" (v1));
}

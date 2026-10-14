#include "common.h"
#include "sce/libmpeg.h"

typedef struct {
    s64 buf;
    u8 *base;
    u8 *p;
    u32 cnt;
    s64 pos;
    u8 *wrap;
    u8 *end;
    s32 size;
} SysBit_0018DAA8;

#define bs_0018DAA8 ((SysBit_0018DAA8 *)arg0)

/* _sysbitFlush: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

void func_0018DAA8(void *arg0, s32 n) {
    bs_0018DAA8->buf <<= n;
    bs_0018DAA8->cnt -= n;
    while (bs_0018DAA8->cnt < 57) {
        bs_0018DAA8->buf |= (s64)*bs_0018DAA8->p++ << (56 - bs_0018DAA8->cnt);
        if (bs_0018DAA8->p >= bs_0018DAA8->end) {
            bs_0018DAA8->p = bs_0018DAA8->wrap;
        }
        bs_0018DAA8->cnt += 8;
    }
    bs_0018DAA8->pos += n;
}

s32 func_0018DB40(u64 *arg0, s32 arg1) {
    s32 temp_s2;

    temp_s2 = func_0018DA88(arg0, arg1);
    func_0018DAA8(arg0, arg1);
    return temp_s2;
}

s32 func_0018DB90(u64 *arg0) {
    s32 temp_s1;

    temp_s1 = func_0018DA88(arg0, 1);
    func_0018DAA8(arg0, 1);
    return temp_s1;
}

/* _sysbitJump: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

void func_0018DBD8(s32 *bs, s32 bytes) {
    s64 x = *(s64 *)(bs + 6) + (bytes << 3);
    s32 v;

    *(s64 *)bs = 0;
    bs[4] = 0;
    *(s64 *)(bs + 6) = x;
    v = bs[2] + (s32)(x >> 3);
    bs[3] = v;
    if ((u32)v >= (u32)bs[9]) {
        bs[3] = v - bs[10];
    }
    func_0018DAA8(bs, 0);
}

u32 func_0018DC30(void *arg0, s32 arg1) {
    u32 var_v1;

    var_v1 = (*(s32 *)((u8 *)arg0 + 8)) + (arg1 >> 3);
    if (var_v1 >= (u32) (*(u32 *)((u8 *)arg0 + 0x24))) {
        var_v1 -= (*(s32 *)((u8 *)arg0 + 0x28));
    }
    return var_v1;
}

/* _type2id: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

s64 func_0018DC60(s32 type, s32 ch) {
    s64 id = 0;
    s32 sh = 0;

    if ((u32)type < 10) {
        switch (D_0028DAB8[type].mask) {
        case 0xFFFFFFFFFFULL:
            sh = 0;
            break;
        case 0xFFFF000000ULL:
            sh = 24;
            break;
        case 0xFF00000000ULL:
            sh = 32;
            break;
        }
        id = D_0028DAB8[type].id | ((s64)ch << sh);
    }
    return id;
}

/* _id2type: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

s32 func_0018DCE8(s32 *type, s32 *num, u64 id) {
    StrDesc *p = D_0028DAB8;
    u32 i;
    s32 found = 0;

    for (i = 0; i < 10 && found == 0; i++) {
        u64 m = p->mask;
        u64 k;

        switch (m) {
        case 0xFFFFFFFFFFULL:
            m = id & 0xFFFFFF0000ULL;
            if (m == p->id) {
                *type = i;
                *num = id & 0xFFFF;
                found = 1;
            }
            break;
        case 0xFFFF000000ULL:
            switch (p->id) {
            case 0xBD20000000ULL:
                m = id & 0xFFE0000000ULL;
                k = 0x1F;
                break;
            case 0xBD80000000ULL:
            case 0xBD88000000ULL:
            case 0xBD90000000ULL:
            case 0xBDA0000000ULL:
                m = id & 0xFFF8000000ULL;
                k = 7;
                break;
            default:
                m = id & 0xFFFF000000ULL;
                k = 0;
                break;
            }
            if (m == p->id) {
                *type = i;
                *num = (id >> 24) & k;
                found = 1;
            }
            break;
        case 0xFF00000000ULL:
            if (p->id == 0xE000000000ULL) {
                m = id & 0xF000000000ULL;
                k = 0xF;
            } else if (p->id == 0xC000000000ULL) {
                m = id & 0xE000000000ULL;
                k = 0x1F;
            } else {
                m = id & m;
                k = 0;
            }
            if (m == p->id) {
                *type = i;
                *num = (id >> 32) & k;
                found = 1;
            }
            break;
        }
        p++;
    }
    return found;
}

INCLUDE_ASM("asm/nonmatchings/main_030", func_0018DEE8);

s32 func_0018E1E0(s32 arg0, s32 arg1, s32 arg2) {
    return func_0018DEE8(arg0, arg1, arg2, 0, -1);
}

/* sceMpegAddStrCallback: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

s32 func_0018E200(void *arg0, s32 type, s32 ch, void *func, void *data) {
    sceMpeg *mp = arg0;
    s32 ret = 0;
    MpegSys *p = mp->sys;
    StrCb *tbl = p->strCb;
    s64 id = func_0018DC60(type, ch);
    s32 n = p->nStrCb;
    s32 i;

    for (i = 0; i < n; i++) {
        if (id == tbl[i].id) {
            ret = (s32)tbl[i].func;
            break;
        }
    }
    if (i < 0x40) {
        p->nStrCb = n + 1;
        tbl[i].id = id;
        tbl[i].arg = data;
        tbl[i].func = (sceMpegCallback)func;
        tbl[i].mask = D_0028DAB8[type].mask;
    }
    return ret;
}

s32 func_0018E2F8(u64 *arg0, void *arg1) {
    s32 temp_s0;
    s32 temp_s1;
    s32 temp_s2;
    s32 temp_s4;
    u32 var_s5;

    func_0018DB40(arg0, 0x22);
    temp_s0 = func_0018DB40(arg0, 3);
    func_0018DB90(arg0);
    temp_s1 = func_0018DB40(arg0, 0xF);
    func_0018DB90(arg0);
    temp_s2 = func_0018DB40(arg0, 0xF);
    func_0018DB90(arg0);
    (*(s32 *)arg1) = func_0018DB40(arg0, 9);
    func_0018DB40(arg0, 0x1E);
    temp_s4 = func_0018DB40(arg0, 3);
    (*(s32 *)((u8 *)arg1 + 8)) = (s32) (((u32) temp_s0 >> 2) & 1);
    (*(s32 *)((u8 *)arg1 + 4)) = (s32) ((temp_s0 << 0x1E) | (temp_s1 << 0xF) | temp_s2);
    for (var_s5 = 0; var_s5 < (u32) temp_s4; var_s5++) {
        func_0018DB40(arg0, 8);
    }
    if (func_0018DA88(arg0, 0x20) == 0x1BB) {
        (*(s32 *)((u8 *)arg1 + 0xC)) = 1;
        func_0018E448(arg0, arg1);
    } else {
        (*(s32 *)((u8 *)arg1 + 0xC)) = 0;
    }
    return 1;
}

s32 func_0018E448(u64 *arg0, void *arg1) {
    func_0018DB40(arg0, 0x38);
    func_0018DB40(arg0, 0x28);
    while (func_0018DA88(arg0, 1) == 1) {
        func_0018DB40(arg0, 0x18);
    }
    return 1;
}

typedef struct {
    long long id;
    int length;
    int scramble;
    long long pts;
    long long dts;
    int pos;
    int datalen;
    int startpos;
} PesPkt_0018E4B8;

typedef struct {
    unsigned char b[16];
} HeaderBits_0018E4B8;

extern HeaderBits_0018E4B8 D_002BC988;
extern char D_002BC998[];

#define pkt_0018E4B8 ((PesPkt_0018E4B8 *)arg2)
#define bs_0018E4B8 ((u64 *)bs)

/* _PES_packet (this SDK passes the decoder handle first, for _Error, and keeps the header-bits table on
   the stack): adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

s32 func_0018E4B8(s32 mp, int *bs, void *arg2) {
    HeaderBits_0018E4B8 headerBits;
    int ptsdts;
    int escr;
    int flags;
    int ext;
    int hdrlen;
    int base;
    int n;
    int len;

    pkt_0018E4B8->startpos = bs[6];
    headerBits = D_002BC988;
    func_0018DB40(bs_0018E4B8, 0x18);
    pkt_0018E4B8->id = (long long)func_0018DB40(bs_0018E4B8, 8) << 32;
    pkt_0018E4B8->length = func_0018DB40(bs_0018E4B8, 0x10);
    pkt_0018E4B8->pts = pkt_0018E4B8->dts = -1;
    if (pkt_0018E4B8->id != 0xBC00000000 && pkt_0018E4B8->id != 0xBE00000000 && pkt_0018E4B8->id != 0xBF00000000 &&
        pkt_0018E4B8->id != 0xF000000000 && pkt_0018E4B8->id != 0xF100000000 && pkt_0018E4B8->id != 0xFF00000000 &&
        pkt_0018E4B8->id != 0xF200000000 && pkt_0018E4B8->id != 0xF800000000) {
        func_0018DB40(bs_0018E4B8, 2);
        pkt_0018E4B8->scramble = func_0018DB40(bs_0018E4B8, 2);
        func_0018DB40(bs_0018E4B8, 4);
        ptsdts = func_0018DB40(bs_0018E4B8, 2);
        escr = func_0018DB40(bs_0018E4B8, 1);
        flags = func_0018DB40(bs_0018E4B8, 4);
        ext = func_0018DB40(bs_0018E4B8, 1);
        hdrlen = func_0018DB40(bs_0018E4B8, 8);
        base = (int)*(long long *)(bs + 6);
        if (ptsdts & 2) {
            unsigned int a;
            int b;
            int c;
            unsigned int low;

            func_0018DB40(bs_0018E4B8, 4);
            a = func_0018DB40(bs_0018E4B8, 3);
            func_0018DB90(bs_0018E4B8);
            b = func_0018DB40(bs_0018E4B8, 0xF);
            func_0018DB90(bs_0018E4B8);
            c = func_0018DB40(bs_0018E4B8, 0xF);
            func_0018DB90(bs_0018E4B8);
            low = (a << 30) | (b << 15) | c;
            pkt_0018E4B8->pts = ((long long)((a >> 2) & 1) << 32) | low;
        }
        if (ptsdts == 3) {
            unsigned int a;
            int b;
            int c;
            unsigned int low;

            func_0018DB40(bs_0018E4B8, 4);
            a = func_0018DB40(bs_0018E4B8, 3);
            func_0018DB90(bs_0018E4B8);
            b = func_0018DB40(bs_0018E4B8, 0xF);
            func_0018DB90(bs_0018E4B8);
            c = func_0018DB40(bs_0018E4B8, 0xF);
            func_0018DB90(bs_0018E4B8);
            low = (a << 30) | (b << 15) | c;
            pkt_0018E4B8->dts = ((long long)((a >> 2) & 1) << 32) | low;
        }
        if (escr == 1) {
            func_0018DB40(bs_0018E4B8, 0x30);
        }
        if (flags != 0) {
            func_0018DB40(bs_0018E4B8, headerBits.b[flags]);
        }
        if (ext == 1) {
            int priv;
            int pack;
            int seq;
            int pstd;
            int ext2;
            unsigned int i;
            unsigned int cnt;

            priv = func_0018DB40(bs_0018E4B8, 1);
            pack = func_0018DB40(bs_0018E4B8, 1);
            seq = func_0018DB40(bs_0018E4B8, 1);
            pstd = func_0018DB40(bs_0018E4B8, 1);
            func_0018DB40(bs_0018E4B8, 3);
            ext2 = func_0018DB40(bs_0018E4B8, 1);
            if (priv == 1) {
                func_0018DB40(bs_0018E4B8, 0x30);
                func_0018DB40(bs_0018E4B8, 0x30);
                func_0018DB40(bs_0018E4B8, 0x20);
            }
            if (pack == 1) {
                func_0018F7B0(mp, D_002BC998);
                return 0;
            }
            if (seq == 1) {
                func_0018DB40(bs_0018E4B8, 0x10);
            }
            if (pstd == 1) {
                func_0018DB40(bs_0018E4B8, 0x10);
            }
            if (ext2 == 1) {
                func_0018DB90(bs_0018E4B8);
                cnt = func_0018DB40(bs_0018E4B8, 7);
                for (i = 0; i < cnt; i++) {
                    func_0018DB40(bs_0018E4B8, 8);
                }
            }
        }
        n = hdrlen - (int)((*(long long *)(bs + 6) - base) >> 3);
        if (n != 0) {
            func_0018DBD8(bs, n);
        }
        len = pkt_0018E4B8->length - hdrlen;
        n = len - 3;
        pkt_0018E4B8->datalen = n;
        pkt_0018E4B8->pos = bs[6];
        if (pkt_0018E4B8->id == 0xBD00000000) {
            pkt_0018E4B8->id = pkt_0018E4B8->id | (unsigned int)func_0018DB40(bs_0018E4B8, 0x20);
            n = len - 7;
        }
        if (n != 0) {
            func_0018DBD8(bs, n);
        }
    } else if (pkt_0018E4B8->id == 0xBC00000000 || pkt_0018E4B8->id == 0xBF00000000 || pkt_0018E4B8->id == 0xF000000000 ||
               pkt_0018E4B8->id == 0xF100000000 || pkt_0018E4B8->id == 0xFF00000000 || pkt_0018E4B8->id == 0xF200000000 ||
               pkt_0018E4B8->id == 0xF800000000) {
        len = pkt_0018E4B8->length;
        if (pkt_0018E4B8->id == 0xBF00000000) {
            len = len - 4;
            pkt_0018E4B8->id = pkt_0018E4B8->id | (unsigned int)func_0018DB40(bs_0018E4B8, 0x20);
        }
        if (len != 0) {
            func_0018DBD8(bs, len);
        }
    } else if (pkt_0018E4B8->id == 0xBE00000000) {
        n = pkt_0018E4B8->length;
        if (n != 0) {
            func_0018DBD8(bs, n);
        }
    }
    return 1;
}

#undef pkt_0018E4B8
#undef bs_0018E4B8

void func_0018EA68(void) {
    func_001843E0();
    *(volatile s32 *)0x1000F590 = *(volatile s32 *)0x1000F520 | 0x10000;
    *(volatile s32 *)0x1000B000 &= 0xFFFFFEFF;
    *(volatile s32 *)0x1000B400 &= 0xFFFFFEFF;
    *(volatile s32 *)0x1000F590 = *(volatile s32 *)0x1000F520 & 0xFFFEFFFF;
    func_00184428();
    *(volatile s32 *)0x1000B020 = 0;
    *(volatile s32 *)0x1000B420 = 0;
    func_00190498();
}

s32 func_0018EB08(void *arg0, s32 arg1, s32 arg2) {
    s32 temp_s2;
    s32 temp_v0;
    s32 ret;
    u32 temp_a2;
    void *temp_s1;

    func_00198948((void *) arg1, 0, (u32) arg2);
    temp_s2 = ((u32) (arg1 + 3) >> 2) * 4;
    temp_a2 = arg2 - (temp_s2 - arg1);
    if (temp_a2 < 0x10C0U) {
        func_0018F7B0(temp_s2, &D_002BC9D0);
        ret = 0;
    } else {
    temp_s1 = temp_s2 + 0x108;
    (*(s32 *)((u8 *)arg0 + 0x40)) = temp_s2;
    func_0018F060(temp_s1, temp_s2 + 0x10C0, temp_a2 - 0x10C0);
    (*(s32 *)arg0) = 0;
    (*(s32 *)((u8 *)arg0 + 4)) = 0;
    (*(s32 *)((u8 *)arg0 + 8)) = 0;
    (*(s64 *)((u8 *)arg0 + 0x10)) = -1;
    (*(s64 *)((u8 *)arg0 + 0x18)) = -1;
    (*(s64 *)((u8 *)arg0 + 0x20)) = 0;
    (*(s64 *)((u8 *)arg0 + 0x28)) = -1;
    (*(s64 *)((u8 *)arg0 + 0x30)) = -1;
    (*(s64 *)((u8 *)arg0 + 0x38)) = 0;
    (*(s32 *)((u8 *)temp_s2 + 0xB4)) = 0;
    (*(s32 *)((u8 *)temp_s2 + 0xB8)) = 0;
    (*(s32 *)((u8 *)temp_s2 + 0xBC)) = 0;
    (*(s32 *)((u8 *)temp_s2 + 0xC0)) = 0;
    (*(s32 *)((u8 *)temp_s2 + 0xC4)) = 0;
    (*(s32 *)((u8 *)temp_s2 + 0xC8)) = 0;
    (*(s32 *)((u8 *)temp_s2 + 0xCC)) = 0;
    (*(s32 *)((u8 *)temp_s2 + 0xD0)) = 0;
    (*(s32 *)((u8 *)temp_s2 + 0xD4)) = 0;
    (*(s32 *)((u8 *)temp_s2 + 0xD8)) = 0;
    (*(s32 *)((u8 *)temp_s2 + 0xDC)) = 0;
    (*(s32 *)((u8 *)temp_s2 + 0xE0)) = 0;
    (*(s32 *)((u8 *)temp_s2 + 0xE4)) = 0;
    (*(s32 *)((u8 *)temp_s2 + 0xE8)) = 0;
    (*(s32 *)((u8 *)temp_s2 + 0xF8)) = 0;
    (*(s32 *)((u8 *)temp_s2 + 0xC)) = 0;
    (*(s32 *)((u8 *)temp_s2 + 0x14)) = 0;
    (*(s32 *)((u8 *)temp_s2 + 0x2C)) = 0;
    (*(s32 *)((u8 *)temp_s2 + 0x34)) = 0;
    (*(s32 *)((u8 *)temp_s2 + 0x3C)) = 0;
    (*(s64 *)((u8 *)temp_s2 + 0xF0)) = -1;
    (*(void (**)(void *))((u8 *)temp_s2 + 0x1C)) = func_001900A0;
    (*(void (**)(void *))((u8 *)temp_s2 + 0x24)) = func_001900B0;
    temp_v0 = func_0018F098(temp_s2, temp_s1, 0x600, 8);
    (*(s32 *)((u8 *)temp_s2 + 0x48)) = 0;
    (*(s32 *)((u8 *)temp_s2 + 0xFC)) = 0;
    (*(s32 *)((u8 *)temp_s2 + 0x100)) = 0;
    (*(s32 *)((u8 *)temp_s2 + 0x104)) = 0;
    (*(s32 *)((u8 *)temp_s2 + 0x70)) = 0;
    (*(s64 *)((u8 *)temp_s2 + 0x78)) = 0;
    (*(s32 *)((u8 *)temp_s2 + 0x80)) = -1;
    (*(s64 *)((u8 *)temp_s2 + 0x88)) = 0;
    (*(s32 *)((u8 *)temp_s2 + 0x90)) = 0;
    (*(s32 *)((u8 *)temp_s2 + 0xAC)) = 0;
    (*(s32 *)((u8 *)temp_s2 + 0x94)) = -1;
    (*(s32 *)((u8 *)temp_s2 + 0x98)) = -1;
    (*(s32 *)((u8 *)temp_s2 + 0x9C)) = -1;
    (*(void **)((u8 *)temp_s2 + 0x858)) = arg0;
    (*(s32 *)((u8 *)temp_s2 + 0x44)) = temp_v0;
    (*(s32 *)((u8 *)temp_s2 + 0xB0)) = 1;
    func_0018F648(temp_s2);
    func_0018EE78(arg0);
    func_0018EEC8(arg0);
    (*(s32 *)((u8 *)temp_s2 + 0x1B8)) = (s32) (temp_s2 + 0x1E8);
    (*(s32 *)((u8 *)temp_s2 + 0x1BC)) = (s32) (temp_s2 + 0x250);
    (*(s32 *)((u8 *)temp_s2 + 0x1C4)) = (s32) (temp_s2 + 0x2B8);
    (*(s32 *)((u8 *)temp_s2 + 0x1C8)) = (s32) (temp_s2 + 0x320);
    (*(s32 *)((u8 *)temp_s2 + 0x1CC)) = (s32) (temp_s2 + 0x388);
    (*(s32 *)((u8 *)temp_s2 + 0x1D4)) = (s32) (temp_s2 + 0x3F0);
    (*(s32 *)((u8 *)temp_s2 + 0x1D8)) = (s32) (temp_s2 + 0x458);
    (*(s32 *)((u8 *)temp_s2 + 0x1DC)) = (s32) (temp_s2 + 0x4C0);
    (*(s32 *)((u8 *)temp_s2 + 0x1E4)) = (s32) (temp_s2 + 0x528);
    func_0018F078(temp_s1);
    (*(s32 *)((u8 *)temp_s2 + 0x850)) = -1;
    (*(s32 *)((u8 *)temp_s2 + 0x854)) = 0;
    (*(s32 *)((u8 *)temp_s2 + 0x84C)) = 0;
    ret = 0x70003600;
    (*(s32 *)((u8 *)temp_s2 + 0x81C)) = ret;
    }
    return ret;
}

s32 func_0018ED10(s32 unused0) {
    return 1;
}

void func_0018ED18(void *arg0, s32 arg1, s32 arg2) {
    func_0018F808(*(s32 *)((u8 *)arg0 + 0x40), arg1, (arg2 + 0x13) / 16 * 16);
}

s32 func_0018ED40(void *arg0, s32 arg1, s32 arg2) {
    void *temp_a3;

    temp_a3 = (*(void **)((u8 *)arg0 + 0x40));
    (*(s32 *)((u8 *)temp_a3 + 0xB0)) = 1;
    (*(s32 *)((u8 *)temp_a3 + 0xD8)) = (s32) ((arg1 & 0x0FFFFFFF) | 0x20000000);
    (*(s32 *)((u8 *)temp_a3 + 0xE4)) = arg2;
    (*(s32 *)((u8 *)temp_a3 + 0xE0)) = 0;
    (*(s32 *)((u8 *)temp_a3 + 0xDC)) = 0;
    return func_0018F120(arg0);
}

s32 func_0018ED88(void *arg0, s32 arg1, s32 arg2) {
    void *temp_a3;

    temp_a3 = (*(void **)((u8 *)arg0 + 0x40));
    (*(s32 *)((u8 *)temp_a3 + 0xE4)) = arg2;
    (*(s32 *)((u8 *)temp_a3 + 0xD8)) = (s32) ((arg1 & 0x0FFFFFFF) | 0x20000000);
    (*(s32 *)((u8 *)temp_a3 + 0xB0)) = 0;
    (*(s32 *)((u8 *)temp_a3 + 0xE0)) = 0;
    (*(s32 *)((u8 *)temp_a3 + 0xDC)) = 0;
    return func_0018F120(arg0);
}

s32 func_0018EDD0(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    void *temp_v1;

    temp_v1 = (*(void **)((u8 *)arg0 + 0x40));
    (*(s32 *)((u8 *)temp_v1 + 0xE0)) = (s32) (arg3 * 0x10);
    (*(s32 *)((u8 *)temp_v1 + 0xD8)) = (s32) ((arg1 & 0x0FFFFFFF) | 0x20000000);
    (*(s32 *)((u8 *)temp_v1 + 0xE4)) = (s32) (arg2 * arg3);
    (*(s32 *)((u8 *)temp_v1 + 0xDC)) = (s32) (arg2 * 0x10);
    (*(s32 *)((u8 *)temp_v1 + 0xB0)) = 0;
    return func_0018F120(arg0);
}

void func_0018EE20(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    void *temp_v0;

    temp_v0 = (*(void **)((u8 *)arg0 + 0x40));
    (*(s32 *)((u8 *)temp_v0 + 0x94)) = arg1;
    (*(s32 *)((u8 *)temp_v0 + 0x98)) = arg2;
    (*(s32 *)((u8 *)temp_v0 + 0x9C)) = arg3;
}

void func_0018EE38(void *arg0, s32 *arg1, s32 *arg2, s32 *arg3) {
    void *temp_t0;

    temp_t0 = (*(void **)((u8 *)arg0 + 0x40));
    *arg1 = (*(s32 *)((u8 *)temp_t0 + 0x94));
    *arg2 = (*(s32 *)((u8 *)temp_t0 + 0x98));
    *arg3 = (*(s32 *)((u8 *)temp_t0 + 0x9C));
}

s32 func_0018EE58(void *arg0) {
    return *(*(s32 **)((u8 *)arg0 + 0x40));
}

s32 func_0018EE68(void *arg0) {
    return (*(s32 *)((u8 *)((*(void **)((u8 *)arg0 + 0x40))) + 4)) == 0;
}

void func_0018EE78(void *arg0) {
    void *temp_s0;

    temp_s0 = (*(void **)((u8 *)arg0 + 0x40));
    (*(s32 *)temp_s0) = 0;
    (*(s32 *)((u8 *)temp_s0 + 4)) = 0;
    (*(s32 *)((u8 *)temp_s0 + 8)) = 0;
    (*(s32 *)((u8 *)arg0 + 8)) = 0;
    (*(s32 *)((u8 *)temp_s0 + 0xAC)) = 0;
    (*(s32 *)((u8 *)temp_s0 + 0x80)) = -1;
    func_0018F6A8(temp_s0);
    (*(s32 *)((u8 *)temp_s0 + 0x118)) = 0;
    func_0018F5B8(temp_s0);
}

s32 func_0018EEC8(void *arg0) {
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v0_3;
    void *temp_v0_4;
    void *temp_v0_5;
    void *temp_v0_6;
    void *temp_v1;

    temp_v1 = (*(void **)((u8 *)arg0 + 0x40));
    temp_v0 = (*(void **)((u8 *)temp_v1 + 0x1B8));
    if (temp_v0 != NULL) {
        (*(s32 *)((u8 *)temp_v0 + 0x28)) = 0;
    }
    temp_v0_2 = (*(void **)((u8 *)temp_v1 + 0x1C8));
    if (temp_v0_2 != NULL) {
        (*(s32 *)((u8 *)temp_v0_2 + 0x28)) = 0;
    }
    temp_v0_3 = (*(void **)((u8 *)temp_v1 + 0x1D8));
    if (temp_v0_3 != NULL) {
        (*(s32 *)((u8 *)temp_v0_3 + 0x28)) = 0;
    }
    temp_v0_4 = (*(void **)((u8 *)temp_v1 + 0x1BC));
    if (temp_v0_4 != NULL) {
        (*(s32 *)((u8 *)temp_v0_4 + 0x28)) = 0;
    }
    temp_v0_5 = (*(void **)((u8 *)temp_v1 + 0x1CC));
    if (temp_v0_5 != NULL) {
        (*(s32 *)((u8 *)temp_v0_5 + 0x28)) = 0;
    }
    temp_v0_6 = (*(void **)((u8 *)temp_v1 + 0x1DC));
    if (temp_v0_6 != NULL) {
        (*(s32 *)((u8 *)temp_v0_6 + 0x28)) = 0;
    }
    return 1;
}

s32 func_0018EF20(void *arg0, s32 arg1, s32 (*arg2)(), s32 arg3) {
    u8 *d;
    s32 (**p)();
    s32 (*old)();
    s32 (**t)();
    s32 *e;

    d = *(u8 **)((u8 *)arg0 + 0x40);
    t = (s32 (**)())(d + 0xC);
    p = t + arg1 * 2;
    e = (s32 *)(d + arg1 * 8);
    e[4] = arg3;
    old = *p;
    *p = arg2;
    return (s32)old;
}

/* _dispatchMpegCallback: adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

s32 func_0018EF48(s32 arg0, void *arg1) {
    sceMpeg *mp = (sceMpeg *)arg0;
    s32 *cbdata = arg1;
    s32 rv = 0;

    if (mp != 0) {
        MpegSys *p = mp->sys;
        if (p != 0) {
            s32 type = *cbdata;
            sceMpegCallback fn = p->cb[type].func;
            if (fn != 0) {
                rv = fn(mp, cbdata, p->cb[type].data);
            }
        }
    }
    return rv;
}

void func_0018EF98(s32 arg0) {
    s32 sp0[8];
    sp0[0] = /* extra? */ 1;
    func_0018EF48(arg0, sp0);
}

void func_0018EFC0(void *arg0, s64 arg1) {
    void *temp_v0;

    temp_v0 = (*(void **)((u8 *)arg0 + 0x40));
    (*(s32 *)((u8 *)temp_v0 + 0x70)) = 1;
    (*(s64 *)((u8 *)temp_v0 + 0x78)) = arg1;
}

void func_0018EFD8(void *arg0) {
    u8 *p = *(u8 **)((u8 *)arg0 + 0x40);

    *(s32 *)(p + 0x70) = 0;
    *(s64 *)(p + 0x78) = 0;
}

void func_0018EFE8(void *arg0, s32 arg1) {
    (*(s32 *)((u8 *)((*(void **)((u8 *)arg0 + 0x40))) + 0xD8)) = arg1;
}

s32 func_0018EFF8(void *arg0) {
    return (*(s32 *)((u8 *)((*(void **)((u8 *)arg0 + 0x40))) + 0xCC));
}

s32 func_0018F008(void *arg0) {
    return (*(s32 *)((u8 *)((*(void **)((u8 *)arg0 + 0x40))) + 0xD0));
}

s32 func_0018F018(void *arg0) {
    return (*(s32 *)((u8 *)arg0 + 0x40)) + 0xB4;
}

s32 func_0018F028(void *arg0) {
    return (*(s32 *)((u8 *)arg0 + 0x40)) + 0xB4;
}

s32 func_0018F038(void *arg0, s32 arg1) {
    s32 temp_v0;
    void *temp_v1;

    temp_v1 = (*(void **)((u8 *)arg0 + 0x40));
    temp_v0 = (*(s32 *)((u8 *)temp_v1 + 0xE8));
    (*(s32 *)((u8 *)temp_v1 + 0xE8)) = arg1;
    return temp_v0;
}

void func_0018F048(void *arg0, s64 arg1) {
    void *temp_v1;

    temp_v1 = (*(void **)((u8 *)arg0 + 0x40));
    (*(s64 *)((u8 *)temp_v1 + 0xF0)) = arg1;
    (*(s32 *)((u8 *)temp_v1 + 0xF8)) = 1;
}

void func_0018F060(void *arg0, s32 arg1, s32 arg2) {
    (*(s32 *)((u8 *)arg0 + 4)) = arg2;
    (*(s32 *)arg0) = arg1;
    (*(s32 *)((u8 *)arg0 + 8)) = arg1;
    (*(s32 *)((u8 *)arg0 + 0xC)) = arg1;
}

void func_0018F078(void *arg0) {
    (*(s32 *)((u8 *)arg0 + 0xC)) = (s32) (*(s32 *)((u8 *)arg0 + 8));
}

void func_0018F088(void *arg0) {
    (*(s32 *)((u8 *)arg0 + 8)) = (s32) (*(s32 *)((u8 *)arg0 + 0xC));
}

s32 func_0018F098(s32 arg0, void *arg1, s32 arg2, u32 arg3) {
    s32 temp_v0;
    u32 temp_a0;

    temp_v0 = ((u32) (((*(u32 *)((u8 *)arg1 + 8)) + arg3) - 1) / arg3) * arg3;
    temp_a0 = temp_v0 + arg2;
    if ((u32) ((*(s32 *)arg1) + (*(s32 *)((u8 *)arg1 + 4))) >= temp_a0) {
        (*(u32 *)((u8 *)arg1 + 8)) = temp_a0;
        return temp_v0;
    }
    func_0018F7B0(arg0, &D_002BC9F8);
    return 0;
}

s32 func_0018F108(s32 *arg0) {
    return (arg0[0] + arg0[1]) - arg0[2];
}

s32 func_0018F120(void *arg0) {
    s32 *p;
    s32 ret;
    u32 st;

    st = 1;
    ret = 0;
    p = *(s32 **)((u8 *)arg0 + 0x40);
    p[0] = 0;
    if (p[0xD8 / 4] & 0x3F) {
        func_0018F778((s32)p, D_002BCA18, p[0xD8 / 4]);
        return -1;
    }
    p[0x820 / 4] = 0;
    do {
        if (ret != -1) {
            do {
                st = func_0018BC80(p);
            } while (st != 0 && p[0x174 / 4] != p[0xD4 / 4] && p[0x848 / 4] != 0);
        }
        switch (st) {
        case 0:
            func_0018F550(arg0);
            p[0] = 1;
            break;
        case 1:
            p[0xA8 / 4] = 0;
            p[0xA4 / 4] = 0;
            p[0xA0 / 4] = 0;
            ret = func_0018F3A8(arg0, 0, p[0x94 / 4]);
            p[0xA0 / 4]++;
            break;
        case 2:
            ret = func_0018F3A8(arg0, p[0xA4 / 4], p[0x98 / 4]);
            p[0xA4 / 4]++;
            break;
        case 3:
        case 4:
            ret = func_0018F3A8(arg0, p[0xA8 / 4], p[0x9C / 4]);
            p[0xA8 / 4]++;
            break;
        }
        if (p[0x820 / 4] != 0) {
            return 1;
        }
    } while (p[0] == 0);
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_030", func_0018F290);

s32 func_0018F3A8(void *arg0, s32 arg1, s32 arg2) {
    s32 ret;

    if (*(s32 *)(*(u8 **)((u8 *)arg0 + 0x40) + 0x174) != 3) {
        ret = func_0018F3F0(arg0, arg1, arg2);
    } else {
        ret = func_0018F290(arg0, arg1, arg2);
    }
    return ret;
}

s32 func_0018F3F0(void *arg0, s32 arg1, s32 arg2) {
    u8 *d;
    s32 skip;
    s32 ret;
    s32 n;
    s32 c;

    skip = 0;
    d = *(u8 **)((u8 *)arg0 + 0x40);
    *(s32 *)(d + 0x120) = 0;
    if (arg2 == -1 || arg1 < arg2) {
        skip = 1;
    }
    if (*(s32 *)(d + 8) == 0) {
        *(s32 *)((u8 *)arg0 + 8) = 0;
        *(s32 *)(d + 8) = 1;
    }
    if (func_0018C680(d, 0) != 0 && skip != 0) {
        func_0018C520(d);
    }
    *(s32 *)(d + 0x120) = 1;
    if (func_0018BC80(d) == 0) {
        func_0018F550(arg0);
        *(s32 *)d = 1;
        return 0;
    }
    n = 2;
    if (*(s32 *)(d + 0xD4) != 1) {
        n = 1;
    }
    if (*(s32 *)(d + 0x174) != n) {
        return -1;
    }
    c = 0;
    if (func_0018C680(d, 1) != 0) {
        c = 1;
    }
    ret = 0;
    if (c != 0 && skip != 0) {
        if (func_0018C520(d) != 0) {
            ret = 1;
        }
    }
    func_0018C5F0(d, *(s32 *)(d + 0x118), *(s32 *)(d + 4));
    *(s32 *)(d + 0x120) = 0;
    *(s32 *)((u8 *)arg0 + 8) = *(s32 *)(d + 0x118) - *(s32 *)(d + 0xAC);
    *(s32 *)(d + 0x118) += 1;
    *(s32 *)(d + 4) += 1;
    if (skip == 0) {
        func_0018EF98((s32)arg0);
    }
    return ret;
}

s32 func_0018F550(void *arg0) {
    s32 var_a0;
    void *temp_s0;

    temp_s0 = (*(void **)((u8 *)arg0 + 0x40));
    var_a0 = 0;
    if ((*(s32 *)((u8 *)temp_s0 + 4)) != 0) {
        if ((*(s32 *)((u8 *)temp_s0 + 8)) != 0) {
            func_0018F5C8(temp_s0);
            var_a0 = 1;
            (*(s32 *)((u8 *)arg0 + 8)) = (s32) ((*(s32 *)((u8 *)temp_s0 + 0x118)) - (*(s32 *)((u8 *)temp_s0 + 0xAC)));
            (*(s32 *)((u8 *)temp_s0 + 4)) = 0;
        }
    }
    return var_a0;
}

void func_0018F5B8(void *arg0) {
    *(s32 *)((u8 *)arg0 + 0x848) = 0;
    func_0018A378(1);
}

void func_0018F5C8(void *arg0) {
    s32 temp_a2;

    temp_a2 = (*(s32 *)((u8 *)arg0 + 0x118));
    if ((*(s32 *)((u8 *)arg0 + 0x120)) != 0) {
        func_0018F7B0((s32) arg0, &D_002BCA78);
    } else {
        if ((*(s32 *)((u8 *)arg0 + 0x174)) == 3) {
            func_0018CE00(arg0, (*(s32 *)((u8 *)arg0 + 0x1BC)), temp_a2 - 1);
        } else {
            func_0018CF10(arg0, (*(s32 *)((u8 *)arg0 + 0x1CC)), (*(s32 *)((u8 *)arg0 + 0x1DC)), temp_a2 - 1);
        }
    }
    (*(s32 *)((u8 *)arg0 + 0x120)) = 0;
}

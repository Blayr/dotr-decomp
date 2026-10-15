#include "common.h"

typedef struct {
    f32 x, y, z, w;
} Vec_b005_01E00080;

typedef struct {
    u8 count;
    u8 pad01;
    u8 length;
    u8 mask;
    u8 mode;
    u8 pad05[0xB];
    u8 light[0x10];
    Vec_b005_01E00080 pos;
    u8 pad30[8];
    f32 value;
    u8 pad3C[4];
    Vec_b005_01E00080 vel;
    f32 base;
} Fx_b005_01E00080;

static void func_01E00080_b558(Fx_b005_01E00080 *o) {
    u8 phase;
    u8 mask;
    u8 rest;
    u8 count;
    f32 step;
    u8 length;
    s32 on;

    if (func_00101AF0(o) == 0) {
        return;
    }
    o->pos.x += o->vel.x;
    o->pos.y += o->vel.y;
    o->pos.z += o->vel.z;
    func_00101BA0(o, (s32)&o->pos);
    count = o->count;
    mask = o->mask;
    length = o->length;
    phase = count & mask;
    rest = length - count;
    if (mask == 0xFF) {
        step = o->base / length;
    } else {
        step = o->base / (mask + 1);
    }
    on = 1;
    switch (o->mode & 0xF) {
    case 1:
        o->value = step * phase;
        break;
    case 2:
        if (mask == 0xFF) {
            if (rest < length >> 1) {
                o->value = 2.0f * step * rest;
            } else {
                o->value = 2.0f * step * count;
            }
        } else {
            if (phase < mask >> 1) {
                o->value = 2.0f * step * (mask - phase);
            } else {
                o->value = 2.0f * step * phase;
            }
        }
        break;
    case 4:
        o->value = o->base;
        if (o->count & 1) {
            o->value *= 0.5f;
        }
        break;
    case 8:
        if (count & 1) {
            on = 0;
        }
    default:
        o->value = o->base;
        break;
    }
    if (on == 0 || o->count == 0) {
        func_001F6C10(0);
    } else {
        func_001F6C10((s32)o->light);
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b558", func_01E003A0_b558);

INCLUDE_ASM("asm/nonmatchings/mod/b558", func_01E00DF0_b558);

INCLUDE_ASM("asm/nonmatchings/mod/b558", func_01E018D0_b558);

/* shape b238:01E02360, 205 insns, 8 copies: b044:01E03490 (-O2,p) built at -O4,p: run a list of emitters (0x3C bytes each): a held emitter just moves;
   otherwise it takes a particle (0x40 bytes) from its pool, copies its colours/sizes/velocity into it and
   gives it a random offset (rand() % range - range / 2, in hundredths), either as is or as a +/- segment */

typedef struct Col_b238_01E02360 {
    u8 r, g, b, a;
} Col_b238_01E02360;

typedef struct Vec3_b238_01E02360 {
    f32 x, y, z;
} Vec3_b238_01E02360;

typedef struct Em_b238_01E02360 {
    u8 b0;
    u8 b1[2];
    u8 b3;
    u8 flags;
    u8 b5;
    u8 b6;
    u8 b7;
    u8 *pool;
    u8 count;
    u8 bD;
    u8 bE;
    u8 bF;
    u8 b10;
    u8 b11;
    u8 b12[2];
    s32 range;
    f32 f18;
    f32 f1C;
    Col_b238_01E02360 col;
    f32 pos[3];
    Vec3_b238_01E02360 vel;
} Em_b238_01E02360;

typedef struct Part_b238_01E02360 {
    u8 b0[4];
    u8 b4;
    u8 b5;
    u8 b6[2];
    u8 b8;
    u8 b9;
    u8 bA;
    u8 bB;
    u8 bC;
    u8 bD;
    u8 bE[2];
    f32 f10;
    f32 f14;
    Col_b238_01E02360 col;
    f32 a[3];
    f32 b[3];
    Vec3_b238_01E02360 vel;
} Part_b238_01E02360;

static s32 func_01E02360_b558(Em_b238_01E02360 *arg0, s32 arg1, s32 n) {
    extern s32 func_00101C30();
    extern void func_00101AD0(void *, u8, s32, s32);
    extern void func_00101BA0();
    extern s32 func_0019A5C8();
    Em_b238_01E02360 *e = arg0;
    Part_b238_01E02360 *q;
    s32 i;
    s32 k;
    f32 rx;
    f32 ry;
    f32 rz;
    Vec4f tmp;

    for (i = 0; i < n; i++) {
        if (i != 0) {
            e++;
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        if (e->b0 & e->b3) {
            e->pos[0] += e->vel.x;
            e->pos[1] += e->vel.y;
            e->pos[2] += e->vel.z;
            continue;
        }
        k = func_00101C30(e->pool, 0x40, e->count);
        if (k < 0) {
            continue;
        }
        q = (Part_b238_01E02360 *)(e->pool + k * 0x40);
        func_00101AD0(q, e->b11, 0, 0xFF);
        q->b5 = e->b5;
        q->b4 = e->flags;
        q->b9 = e->b6;
        q->b8 = e->bD;
        q->bB = e->bE;
        q->bC = e->bF;
        q->bD = e->b10;
        q->f10 = e->f18;
        q->f14 = e->f1C;
        q->col = e->col;
        q->vel = e->vel;
        if (e->b5) {
            func_00101BA0(e, &tmp);
            e->pos[0] = tmp.x;
            e->pos[1] = tmp.y;
            e->pos[2] = tmp.z;
        }
        rx = ((func_0019A5C8() >> 4) % e->range - (e->range >> 1)) / 100.0f;
        ry = ((func_0019A5C8() >> 4) % e->range - (e->range >> 1)) / 100.0f;
        rz = ((func_0019A5C8() >> 4) % e->range - (e->range >> 1)) / 100.0f;
        if (e->flags & 2) {
            q->a[0] = rx;
            q->a[1] = ry;
            q->a[2] = rz;
        } else {
            q->a[0] = e->pos[0] + rx;
            q->a[1] = e->pos[1] + ry;
            q->a[2] = e->pos[2] + rz;
            q->b[0] = e->pos[0] - rx;
            q->b[1] = e->pos[1] - ry;
            q->b[2] = e->pos[2] - rz;
        }
        if (e->b5 == 0) {
            e->pos[0] += e->vel.x;
            e->pos[1] += e->vel.y;
            e->pos[2] += e->vel.z;
        }
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/mod/b558", func_01E026A0_b558);

/* OVL_WARM: compile warm (DK_WARM=1, after a runtime-helper call as in the original many-files-per-run build).
   Its float -> int casts are MWCC runtime calls: fptosi = 0x001A22C0, fptoui = 0x001A23B0 (link names). */

/* shape b029:01E026A0, 310 insns, 35 copies: full-screen fade quad (4 vertices); its alpha follows the emitter's counter */

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
} Hdr_b029_01E026A0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b029_01E026A0;

typedef struct {
    Hdr_b029_01E026A0 h;
    Vtx_b029_01E026A0 v[4];
    u8 tail[8];
} Pkt_b029_01E026A0;

typedef struct {
    u8 cur;
    u8 pad1;
    u8 max;
    u8 pad3;
    u8 flags;
} Obj_b029_01E026A0;

static s32 func_01E03300_b558(Obj_b029_01E026A0 *o, s32 tex, s32 d, s32 h) {
    Pkt_b029_01E026A0 p __attribute__((aligned(8)));
    u8 a;
    u8 mode;
    u8 k;
    f32 w;
    f32 mid;
    f32 s;

    if (func_00101AF0(o) == 0) {
        return 0;
    }
    ((Hdr_b029_01E026A0 *)(s32)&p)->count = 0x14;
    ((Hdr_b029_01E026A0 *)(s32)&p)->tag = 8;
    ((Hdr_b029_01E026A0 *)(s32)&p)->regs = 0x41414141;
    ((Hdr_b029_01E026A0 *)(s32)&p)->pad = 0;
    mode = o->flags;
    switch (mode & 7) {
    case 1:
        a = 128.0f / o->max * o->cur;
        break;
    case 2:
        a = ((o->max - o->cur) << 7) / o->max;
        break;
    case 4:
    default:
        a = 0x80;
        break;
    }
    if (o->cur == 1 && (mode & 0x80)) {
        o->cur = o->max;
        if (o->flags & 1) {
            o->flags = 2;
        } else {
            o->flags = 1;
        }
    }
    if (o->flags & 8) {
        a >>= 1;
    }
    p.v[0].b = p.v[1].b = p.v[2].b = p.v[3].b = 0xFF;
    p.v[0].g = p.v[1].g = p.v[2].g = p.v[3].g = 0xFF;
    p.v[0].r = p.v[1].r = p.v[2].r = p.v[3].r = 0xFF;
    p.v[0].q = p.v[1].q = p.v[2].q = p.v[3].q = 1.0f;
    p.v[0].z = p.v[1].z = p.v[2].z = p.v[3].z = 0xFFFFFF;
    func_002086D0(&p, 0x48);
    if (o->flags & 0x10) {
        h = o->max >> 1;
        s = h;
        s = 7168.0f / s;
        d = o->max - o->cur;
        k = (0x80 / h) * (d >> 1);
        if (h < d) {
            p.v[0].a = p.v[1].a = k;
            d = o->max >> 1;
        } else {
            p.v[0].a = p.v[1].a = 0;
        }
        p.v[2].a = p.v[3].a = 0x80;
        p.v[0].x = p.v[2].x = 0x6C00;
        p.v[1].x = p.v[3].x = 0x9400;
        w = s * d;
        mid = 32768.0f;
        p.v[0].y = p.v[1].y = mid - w;
        p.v[2].y = p.v[3].y = mid;
        func_002075F0((s32)&p, tex, 0);
        p.v[2].a = p.v[3].a = p.v[1].a;
        p.v[1].a = p.v[0].a = 0x80;
        p.v[0].y = p.v[1].y = mid;
        p.v[2].y = p.v[3].y = mid + w;
        func_002075F0((s32)&p, tex, 0);
    } else {
        p.v[0].a = p.v[1].a = p.v[2].a = p.v[3].a = a;
        if (o->flags & 0x20) {
            p.v[2].a = p.v[3].a = 0;
        }
        if (o->flags & 0x40) {
            p.v[0].a = p.v[1].a = 0;
        }
        p.v[0].x = p.v[2].x = 0x6C00;
        p.v[1].x = p.v[3].x = 0x9400;
        p.v[0].y = p.v[1].y = 0x7200;
        p.v[2].y = p.v[3].y = 0x8E00;
        func_002075F0((s32)&p, tex, 0);
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/mod/b558", func_01E037E0_b558);

INCLUDE_ASM("asm/nonmatchings/mod/b558", func_01E040F0_b558);

INCLUDE_ASM("asm/nonmatchings/mod/b558", func_01E04830_b558);

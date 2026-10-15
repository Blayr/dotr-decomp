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

static void func_01E00080_b029(Fx_b005_01E00080 *o) {
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

INCLUDE_ASM("asm/nonmatchings/mod/b029", func_01E003A0_b029);

typedef struct {
    u8 pad00[3];
    u8 frame;
    f32 x, y, z;
    f32 vx, vy, vz;
    f32 ax, ay, az;
} Node_b029_01E00C20;

typedef struct {
    u8 pad00[8];
    Node_b029_01E00C20 *pool;
    s16 ids[8];
    u8 kind;
    u8 count;
} Sys_b029_01E00C20;

typedef struct {
    Sys_b029_01E00C20 *sys;
    u8 life;
    u8 mask;
    u8 pad06[2];
    f32 speed;
    f32 rise;
    f32 radius;
    f32 cx, cy, cz;
} Burst_b029_01E00C20;

static void func_01E00C20_b029(Burst_b029_01E00C20 *pr) {
    extern void func_00101B40(void *, u8, u8);
    extern s32 func_00101C30(void *, s32, s32);
    extern f32 func_001A6898(f32);
    extern f32 func_001A6A88(f32);
    Sys_b029_01E00C20 *s;
    Node_b029_01E00C20 *node;
    s32 i;
    s32 idx;
    f32 angle;
    f32 step;
    f32 c;
    f32 sn;

    s = pr->sys;
    angle = 180.0f + (f32)((func_0019A5C8() >> 4) % 36000 - 18000) / 100.0f;
    step = 360.0f / s->count;
    for (i = 0; i < s->count; i++) {
        idx = func_00101C30(s->pool, 0x28, s->kind);
        if (idx >= 0) {
            s->ids[i] = idx;
            node = &s->pool[idx];
            func_00101B40(node, pr->life, pr->mask & (func_0019A5C8() >> 4));
            node->frame = ((func_0019A5C8() >> 4) & 3) << 4;
            angle += step;
            if (!(angle <= 360.0f)) {
                angle -= 360.0f;
            }
            c = 3.1415927f * angle / 180.0f;
            c = func_001A6A88(c);
            sn = func_001A6898(3.1415927f * angle / 180.0f);
            node->x = pr->cx + pr->radius * sn;
            node->z = pr->cz + pr->radius * c;
            node->y = pr->cy;
            node->vx = pr->speed * sn;
            node->vz = pr->speed * c;
            node->vy = pr->rise;
            node->ax = -(node->vx / pr->life);
            node->az = -(node->vz / pr->life);
            node->ay = 0.0f;
        } else {
            s->ids[i] = -1;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b029", func_01E00EF0_b029);

INCLUDE_ASM("asm/nonmatchings/mod/b029", func_01E01340_b029);

INCLUDE_ASM("asm/nonmatchings/mod/b029", func_01E01D90_b029);

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

static s32 func_01E026A0_b029(Obj_b029_01E026A0 *o, s32 tex, s32 d, s32 h) {
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

INCLUDE_ASM("asm/nonmatchings/mod/b029", func_01E02B80_b029);

INCLUDE_ASM("asm/nonmatchings/mod/b029", func_01E03660_b029);

/* OVL_WARM: compile warm (its (u32) cast is jal fptoui, func_001A23B0) */

/* shape b095:01E02120, 345 insns, 17 copies: draws n billboards (0x3C-byte emitters): a quad that shrinks with age
   and grows along y, turned by the emitter's rotation at its position, perspective STQ, texture frame from
   func_001020B0, blend from func_00101C80 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b029_01E04780;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    f32 s, t;
    Xyz_b029_01E04780 xyz;
} Vtx_b029_01E04780;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b029_01E04780 v[4];
    u8 tail[0x20];
} Pkt_b029_01E04780;

typedef struct {
    u8 pad0[5];
    u8 b5;
    u8 pad6[2];
    s32 u, w, v, h;
} Tex_b029_01E04780;

typedef struct {
    u8 life;
    u8 pad1;
    u8 max;
    u8 pad3;
    u8 flags;
    u8 pad5[3];
    u8 texid;
    u8 b9;
    u8 bA;
    u8 bB;
    u8 b, g, r, a;
    f32 r0;
    f32 w0;
    f32 dw;
    Vec4f rot;
    Vec4f pos;
} Emit_b029_01E04780;

static s32 func_01E04780_b029(void *arg0, s32 ot __attribute__((aligned(8))), s32 n) {
    extern void func_001020B0();
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_0020BC00(void *, void *);
    extern void func_00101BA0(void *, void *);
    f32 mat[16];
    f32 mat2[16];
    Vec4f c[4];
    f32 depth[4];
    Tex_b029_01E04780 td;
    Pkt_b029_01E04780 pkt __attribute__((aligned(8)));
    u8 bl[4];
    Emit_b029_01E04780 *e;
    s32 i;
    void *tex;
    s32 d;
    f32 r0;
    f32 h;
    f32 w;
    s32 life;
    f32 q1;
    f32 q2;
    f32 q3;
    f32 z;

    e = arg0;
    for (i = 0; i < n; i++) {
        if (i != 0) {
            e++;
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        tex = (void *)func_00202BF0(5, e->texid);
        d = e->max - e->life;
        r0 = e->r0;
        h = r0 - d * (r0 / e->max);
        w = e->w0 + e->dw * d;
        c[0].z = c[1].z = c[2].z = c[3].z = 0.0f;
        c[0].x = c[2].x = -h;
        c[1].x = c[3].x = h;
        c[0].y = c[1].y = -w;
        c[2].y = c[3].y = w;
        func_00101BA0(e, &e->pos);
        func_0020EB40(mat);
        func_0020C940(mat2, NULL, &e->rot, &e->pos);
        func_0020BC00(mat, mat2);
        ((Pkt_b029_01E04780 *)(s32)&pkt)->count = 0x34;
        ((Pkt_b029_01E04780 *)(s32)&pkt)->tag = 0xC;
        ((Pkt_b029_01E04780 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Pkt_b029_01E04780 *)(s32)&pkt)->pad = 0;
        pkt.v[0].r = pkt.v[1].r = pkt.v[2].r = pkt.v[3].r = e->r;
        pkt.v[0].g = pkt.v[1].g = pkt.v[2].g = pkt.v[3].g = e->g;
        pkt.v[0].b = pkt.v[1].b = pkt.v[2].b = pkt.v[3].b = e->b;
        if (!(e->flags & 0x40) && (life = e->life) < 8) {
            pkt.v[0].a = pkt.v[1].a = pkt.v[2].a = pkt.v[3].a = (e->a >> 3) * life;
        } else {
            pkt.v[0].a = pkt.v[1].a = pkt.v[2].a = pkt.v[3].a = e->a;
        }
        if (func_00205440(&c[0], mat, &pkt.v[0].xyz, &depth[0]) != 0 &&
            func_00205440(&c[1], mat, &pkt.v[1].xyz, &depth[1]) != 0 &&
            func_00205440(&c[2], mat, &pkt.v[2].xyz, &depth[2]) != 0 &&
            func_00205440(&c[3], mat, &pkt.v[3].xyz, &depth[3]) != 0) {
            td.b5 = e->bB;
            func_001020B0(&td, e->bA, e->b9);
            pkt.v[0].q = 1.0f / depth[0];
            q1 = 1.0f / depth[1];
            pkt.v[1].q = q1;
            q2 = 1.0f / depth[2];
            pkt.v[2].q = q2;
            q3 = 1.0f / depth[3];
            pkt.v[3].q = q3;
            pkt.v[0].s = 0.0f;
            pkt.v[0].t = 0.0f;
            pkt.v[1].s = q1;
            pkt.v[1].t = 0.0f;
            pkt.v[2].s = 0.0f;
            pkt.v[2].t = q2;
            pkt.v[3].s = q3;
            pkt.v[3].t = q3;
            func_00208CB0(&pkt, (u64)0xA | ((u64)td.u << 4) | ((u64)(td.w - 1) << 14) | ((u64)td.v << 24) |
                                    ((u64)(td.h - 1) << 34));
            func_00101C80(&td, bl);
            func_002086D0(&pkt, (u64)bl[0] | ((u64)bl[1] << 2) | ((u64)bl[2] << 4) | ((u64)bl[3] << 6));
            func_00208700(&pkt, tex, 1);
            if (e->flags & 0x80) {
                pkt.v[0].xyz.z = pkt.v[1].xyz.z = pkt.v[2].xyz.z = pkt.v[3].xyz.z = 0xFFFFFE;
                z = 0.0f;
            } else {
                z = (depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f;
            }
            func_002075F0((s32)&pkt, ot, (u32)z);
        }
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/mod/b029", func_01E04C90_b029);

INCLUDE_ASM("asm/nonmatchings/mod/b029", func_01E05AA0_b029);

INCLUDE_ASM("asm/nonmatchings/mod/b029", func_01E05F20_b029);

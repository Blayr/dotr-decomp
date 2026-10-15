#include "common.h"

/* shape b081:01E00080, 30 insns, 24 copies (s32 twin of b034:01E00080): shift a position history down by one, the newest from src */

static s32 func_01E00080_b081(Vec4f *dst, s32 n, s32 arg2, Vec4f *src) {
    s32 i;
    s32 k = n - 1;
    Vec4f *prev = dst;

    prev--;
    for (i = 0; i < n; i++, dst--, prev--, k--) {
        if (k != 0) {
            dst->x = prev->x;
            dst->y = prev->y;
            dst->z = prev->z;
        } else {
            dst->x = src->x;
            dst->y = src->y;
            dst->z = src->z;
        }
    }
    return 0;
}

/* shape b003:01E00080, 552 insns, 183 copies: the module's first function. Texture coordinates of a
   sprite quad from a rectangle, in one of 8 corner orders (flips and quarter turns). Callers in the same
   file rely on it leaving $a0 alone, so it must stay in their file. */

typedef struct Rect_b003_01E00080 {
    s16 x, y, w, h;
} Rect_b003_01E00080;

typedef struct Uv_b003_01E00080 {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad4;
    u64 xyz;
} Uv_b003_01E00080;

typedef struct Pk_b003_01E00080 {
    u8 pad0[0x18];
    Uv_b003_01E00080 c[4];
} Pk_b003_01E00080;


/* static in its module (callers that include this file #define OVL_LOCAL static first) */

static void func_01E00100_b081(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
    if (mode == 0) {
        p->c[0].u = (r->x) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[1].u = (r->x + r->w) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[2].u = (r->x) << 4;
        p->c[2].v = (r->y + r->h) << 4;
        p->c[3].u = (r->x + r->w) << 4;
        p->c[3].v = (r->y + r->h) << 4;
    } else if (mode == 1) {
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y) << 4;
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y + r->h) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y + r->h) << 4;
    } else if (mode == 2) {
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y + r->h) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y + r->h) << 4;
    } else if (mode == 3) {
        p->c[2].u = (r->x) << 4;
        p->c[2].v = (r->y) << 4;
        p->c[3].u = (r->x + r->w) << 4;
        p->c[3].v = (r->y) << 4;
        p->c[0].u = (r->x) << 4;
        p->c[0].v = (r->y + r->h) << 4;
        p->c[1].u = (r->x + r->w) << 4;
        p->c[1].v = (r->y + r->h) << 4;
    } else if (mode == 4) {
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[3].u = (r->x + r->w) << 4;
        p->c[3].v = (r->y) << 4;
        p->c[0].u = (r->x) << 4;
        p->c[0].v = (r->y + r->h) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y + r->h) << 4;
    } else if (mode == 5) {
        p->c[2].u = (r->x) << 4;
        p->c[2].v = (r->y) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y + r->h) << 4;
        p->c[1].u = (r->x + r->w) << 4;
        p->c[1].v = (r->y + r->h) << 4;
    } else if (mode == 6) {
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y) << 4;
        p->c[1].u = (r->x + r->w) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[2].u = (r->x) << 4;
        p->c[2].v = (r->y + r->h) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y + r->h) << 4;
    } else if (mode == 7) {
        p->c[0].u = (r->x) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y) << 4;
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y + r->h) << 4;
        p->c[3].u = (r->x + r->w) << 4;
        p->c[3].v = (r->y + r->h) << 4;
    }
}

typedef struct {
    f32 x, y, z, w;
} Vec_b018_01E00EE0;


/* static in its module (callers that include this file #define OVL_LOCAL static first) */

static Vec_b018_01E00EE0 func_01E009A0_b081(Vec_b018_01E00EE0 *p, s32 type, f32 t) {
    Vec_b018_01E00EE0 r;
    f32 b0;
    f32 b1;
    f32 b2;
    f32 b3;

    if (type == 0) {
        b0 = -t * ((t - 1.0f) * (t - 2.0f)) / 6.0f;
        b1 = (t - 2.0f) * ((1.0f + t) * (t - 1.0f)) / 2.0f;
        b2 = -(1.0f + t) * (t * (t - 2.0f)) / 2.0f;
        b3 = (1.0f + t) * (t * (t - 1.0f)) / 6.0f;
    } else if (type == 1) {
        b0 = (1.0f - t) * ((1.0f - t) * (1.0f - t)) / 6.0f;
        b1 = 2.0f / 3.0f + ((t * (t * t)) / 2.0f - (t * t));
        b2 = 1.0f / 6.0f + (t / 2.0f + (-(t * (t * t)) / 2.0f + (t * t) / 2.0f));
        b3 = (t * (t * t)) / 6.0f;
    } else if (type == 2) {
        b0 = (1.0f - t) * ((1.0f - t) * (1.0f - t));
        b1 = 1.75f * (t * (t * t)) - 4.5f * (t * t) + 3.0f * t;
        b2 = -(11.0f / 12.0f * (t * (t * t))) + 1.5f * (t * t);
        b3 = 1.0f / 6.0f * (t * (t * t));
    } else if (type == 3) {
        b0 = 0.25f * ((1.0f - t) * ((1.0f - t) * (1.0f - t)));
        b1 = 7.0f / 12.0f + (7.0f / 12.0f * (t * (t * t)) - 1.25f * (t * t) + 0.25f * t);
        b2 = 1.0f / 6.0f + (t / 2.0f + (-(0.5f * (t * (t * t))) + 0.5f * (t * t)));
        b3 = 1.0f / 6.0f * (t * (t * t));
    } else if (type == 4) {
        b0 = 1.0f / 6.0f * ((1.0f - t) * ((1.0f - t) * (1.0f - t)));
        b1 = 1.0f / 6.0f + (-0.5f * ((1.0f - t) * ((1.0f - t) * (1.0f - t))) + 0.5f * ((1.0f - t) * (1.0f - t)) + 0.5f * (1.0f - t));
        b2 = 7.0f / 12.0f + (7.0f / 12.0f * ((1.0f - t) * ((1.0f - t) * (1.0f - t))) - 1.25f * ((1.0f - t) * (1.0f - t)) + 0.25f * (1.0f - t));
        b3 = 0.25f * (t * (t * t));
    } else if (type == 5) {
        b0 = 1.0f / 6.0f * ((1.0f - t) * ((1.0f - t) * (1.0f - t)));
        b1 = -11.0f / 12.0f * ((1.0f - t) * ((1.0f - t) * (1.0f - t))) + 1.5f * ((1.0f - t) * (1.0f - t));
        b2 = 1.75f * ((1.0f - t) * ((1.0f - t) * (1.0f - t))) - 4.5f * ((1.0f - t) * (1.0f - t)) + 3.0f * (1.0f - t);
        b3 = (t * (t * t));
    } else if (type == 6) {
        b0 = (1.0f - t) * ((1.0f - t) * (1.0f - t));
        b1 = 3.0f * t * ((1.0f - t) * (1.0f - t));
        b2 = (1.0f - t) * (3.0f * (t * t));
        b3 = t * (t * t);
    }
    r.x = p[0].x * b0 + p[1].x * b1 + p[2].x * b2 + p[3].x * b3;
    r.y = p[0].y * b0 + p[1].y * b1 + p[2].y * b2 + p[3].y * b3;
    r.z = p[0].z * b0 + p[1].z * b1 + p[2].z * b2 + p[3].z * b3;
    return r;
}

/* shape b081:01E00DE0, 282 insns: half ring of 18 segments (20 table steps each) between an s16 inner and outer
   radius, variant of b082:01E00920 with a smaller data layout; blend from flags >> 4, depth mode flags & 0xF */

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[0x54];
    u8 table[1];
} Obj_b081_01E00DE0;

typedef struct {
    u8 pad00[6];
    s16 outer;
    u8 pad08[8];
    Vec4f rot;
    u8 pad20[8];
    u8 mode0[4];
    u8 mode1[4];
    u8 pad30[8];
    s16 inner;
    s16 step;
} Data_b081_01E00DE0;

static void func_01E00DE0_b081(Obj_b081_01E00DE0 *o, Data_b081_01E00DE0 *data, s32 flags, Vec4f pos) {
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    Vec4f quad[4];
    Vec4f t;
    Vec4f scale;
    f32 m[16];
    f32 depth[4];
    u8 packet[0x90];
    s32 i;
    f32 inner;
    s16 j;
    s16 alpha;
    f32 outer;
    u8 *pkt;
    s32 a;
    s32 mode;

    pkt = packet;
    j = 0;
    func_00107990(pkt, data->mode0, 2);
    func_00107990(pkt, data->mode1, 1);
    func_001092E0(pkt, 0);
    func_001094F0(pkt);
    alpha = flags >> 4;
    if (alpha == 0) {
        func_002086D0(pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(pkt, ((s64)alpha << 2) | (((u64)0x80 << 32) | 0x40));
    }
    scale.x = 0.1f;
    t.x = pos.x;
    scale.y = 0.1f;
    t.y = pos.y;
    scale.z = 0.1f;
    t.z = pos.z;
    func_00108EF0(m, &scale, &data->rot, &t);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    mode = flags & 0xF;
    inner = data->inner;
    outer = data->outer;
    i = 0;
    do {
        if (i == 0) {
            a = data->step + j;
            quad[0].x = inner * func_00108030(o->table, a, 1);
            quad[0].z = inner * func_00108030(o->table, a, 0);
            quad[2].x = outer * func_00108030(o->table, a, 1);
            quad[2].z = outer * func_00108030(o->table, a, 0);
            a = j + (data->step + 20);
            quad[1].x = inner * func_00108030(o->table, a, 1);
            quad[1].z = inner * func_00108030(o->table, a, 0);
            quad[3].x = outer * func_00108030(o->table, a, 1);
            quad[3].z = outer * func_00108030(o->table, a, 0);
        } else {
            quad[0] = quad[1];
            quad[2] = quad[3];
            a = j + (data->step + 20);
            quad[1].x = inner * func_00108030(o->table, a, 1);
            quad[1].z = inner * func_00108030(o->table, a, 0);
            quad[3].x = outer * func_00108030(o->table, a, 1);
            quad[3].z = outer * func_00108030(o->table, a, 0);
        }
        if (mode == 0) {
            if (func_00205630(quad, 0x70000000, m, pkt, depth) != 0) {
                func_002075F0(pkt, o->ot, (u32)depth[0]);
            }
        } else if (mode == 1) {
            if (func_00205630(quad, 0x70000000, m, pkt, depth) != 0) {
                func_00109380(pkt, 1);
                func_002075F0(pkt, o->ot, 0);
            }
        } else if (func_00205630(quad, 0x70000000, m, pkt, depth) != 0) {
            func_002075F0(pkt, o->ot, -1);
        }
        j += 20;
        i++;
    } while (i < 18);
}

INCLUDE_ASM("asm/nonmatchings/mod/b081", func_01E01250_b081);

/* shape b081:01E015A0, 73 insns: open the draw packet for an object: its two blend modes (+0x28 as 1, +0x2C as 2), alpha test from flags >> 4, then send with a depth from the float unless flags & 0xF is 0 */

static void func_01E015A0_b081(s32 arg0, u8 *obj, s32 flags, f32 depth) {
    extern s32 func_00207500(void);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_001A23B0(f32);
    u8 packet[0x90];
    s16 alpha;
    s32 ctx;
    u8 *pkt;

    ctx = func_00207500();
    pkt = packet;
    func_00107990(pkt, obj + 0x28, 1);
    func_00107990(pkt, obj + 0x2C, 2);
    func_001092E0(pkt, 0);
    func_001094F0(pkt);
    alpha = flags >> 4;
    if (alpha == 0) {
        func_002086D0(pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(pkt, ((s64)alpha << 2) | (((u64)0x80 << 32) | 0x40));
    }
    if (!(flags & 0xF)) {
        func_002075F0(pkt, ctx, 0);
    } else {
        func_002075F0(pkt, ctx, func_001A23B0(depth));
    }
}

/* shape b081:01E016D0, 342 insns, 3 copies: draws a row of small camera-facing sprites at the object position (b008
   family): each shaken by a per-entry table offset turned by an extra axis and added to all four corners;
   blend from flags >> 4, depth mode flags & 0xF (projected, far, front). Texture corners by the module helper
   (shape b003:01E00080). */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b081_01E016D0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Rgbaq_b081_01E016D0 c;
    struct {
        u64 tc;
        u64 x : 16, y : 16, z : 24, f : 8;
    } v[4];
    u8 tail[0x38];
} Pkt_b081_01E016D0;

typedef struct {
    u8 pad00[0x20];
    Vec4f pos;
    u8 pad30[0x50];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    Rect_b003_01E00080 rect;
    u8 pad9C[0x1C];
    s16 count;
    u8 padBA[6];
    s16 mode;
    u8 padC2[0x16];
    u8 xD8[1];
} Obj_b081_01E016D0;

typedef struct {
    u8 pad00[8];
    s16 off;
    u8 pad0A[0x1E];
    u8 col[4];
    u8 pad2C[4];
    s16 w30;
    u8 pad32[6];
    s16 size;
    s16 axis;
} Spr_b081_01E016D0;

static void func_01E016D0_b081(Obj_b081_01E016D0 *o, Spr_b081_01E016D0 *s, s32 flags, s8 *tbl) {
    extern Rgbaq_b081_01E016D0 func_00107740(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern s32 func_00109100(void *, void *, s32, void *);
    extern void func_00108950(void *, void *, s32, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f e;
    Vec4f p2;
    Vec4f scale;
    f32 depth[4];
    f32 m[16];
    s32 rot[4];
    s32 ax[4];
    Pkt_b081_01E016D0 pkt __attribute__((aligned(8)));
    f32 f;
    s16 i;
    s16 b;
    Pkt_b081_01E016D0 *p;
    s32 mode;
    s32 h;
    s8 *j;

    func_00207500();
    p = (Pkt_b081_01E016D0 *)(s32)&pkt;
    p->count = 0x24;
    p->tag = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad = 0;
    p->count |= 0x800;
    b = flags >> 4;
    if (b == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((u64)b << 2) | (((u64)0x80 << 32) | 0x40));
    }
    p->c = func_00107740(s->col);
    func_00208700(p, o->texture, 1);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    rot[1] = rot[1] / 180;
    rot[1] = -rot[1];
    rot[0] = rot[0] / 180;
    rot[0] = -rot[0];
    ax[2] = s->axis;
    p2.x = o->pos.x;
    p2.y = o->pos.y;
    p2.z = o->pos.z;
    func_00108EF0(m, &scale, NULL, &p2);
    func_01E00100_b081((Pk_b003_01E00080 *)p, &o->rect, o->mode);
    mode = flags & 0xF;
    for (i = 0; i < o->count; i++) {
        func_00108CE0(quad, s->size, s->size);
        func_00109100(quad, rot, 1, o->xD8);
        func_00109100(quad, rot, 0, o->xD8);
        j = tbl + i;
        h = i >> 1;
        f = j[s->off];
        f /= 20.0f;
        e.x = f * (s->w30 + h);
        f = j[s->off + 100];
        f /= 20.0f;
        e.y = f * (s->w30 + h);
        func_00108950(&e, ax, 2, o->xD8);
        quad[0].x += e.x;
        quad[1].x += e.x;
        quad[2].x += e.x;
        quad[3].x += e.x;
        quad[0].y += e.y;
        quad[1].y += e.y;
        quad[2].y += e.y;
        quad[3].y += e.y;
        f = j[s->off + 180];
        f /= 20.0f;
        e.z = f * (s->w30 + h);
        quad[0].z += e.z;
        quad[1].z += e.z;
        quad[2].z += e.z;
        quad[3].z += e.z;
        if (mode == 0) {
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                func_002075F0(p, o->ot, (u32)depth[0]);
            }
        } else if (mode == 1) {
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
                func_002075F0(p, o->ot, 0);
            }
        } else if (mode == 2) {
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                func_002075F0(p, o->ot, -1);
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b081", func_01E01C30_b081);

/* shape b081:01E02740, 67 insns: a white-brown flash: set up once (frame 6, size 8 by 720), both alphas up by 0x40 to
   0x80 for 4 frames, then down by 15; it ends when the first runs out */

typedef struct {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[0x1C];
    u8 c0[4];
    u8 c1[4];
    u8 pad30[2];
    s16 t;
    u8 pad34[2];
    s16 state;
    s16 h38;
} Obj_b081_01E02740;

static s32 func_01E02740_b081(void *arg0, Obj_b081_01E02740 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 6;
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
        func_001076F0(o->c1, 0x40, 0x30, 8);
        o->w = 8;
        o->h = 0x2D0;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 4) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x40;
        }
        if (o->c1[3] < 0x80) {
            o->c1[3] += 0x40;
        }
    } else {
        if (o->c0[3] > 0x10) {
            o->c0[3] -= 0xF;
        } else {
            o->state = 0;
        }
        if (o->c1[3] > 0x10) {
            o->c1[3] -= 0xF;
        } else {
            o->c1[3] = 0;
        }
    }
    o->t++;
    return 0;
}

/* shape b081:01E02850, 70 insns: a pale yellow two-colour glow held 8 ticks (28 for kind 2): in by 21 up to 0x80, then out by 15 and ends */

typedef struct {
    u8 pad0[6];
    s16 h6;
    u8 pad8[0x20];
    u8 col[4];
    u8 col2[4];
    s16 h30;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
    s16 ang;
} Glow_b081_01E02850;

static s32 func_01E02850_b081(s32 arg0, Glow_b081_01E02850 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        func_001076F0(o->col, 0xC0, 0xC0, 0x80);
        func_001076F0(o->col2, 0xC0, 0xC0, 0x80);
        if (o->h30 == 2) {
            o->h6 = 28;
        } else {
            o->h6 = 8;
        }
        o->mode = 2;
    }
    if (o->tick < o->h6) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x15;
        }
        if (o->col2[3] < 0x80) {
            o->col2[3] += 0x15;
        }
    } else {
        if (o->col[3] > 0x10) {
            o->col[3] -= 15;
        } else {
            o->mode = 0;
        }
        if (o->col2[3] > 0x10) {
            o->col2[3] -= 15;
        } else {
            o->col2[3] = 0;
        }
    }
    o->tick++;
    return 0;
}

/* func_001076F0 takes plain ints here (functions.h says s8): hide that prototype */

/* shape b081:01E02970, 114 insns: glow pair whose life depends on its kind; fades in and out and flickers on
   frames 6 and 7 of every 8 */

typedef struct Fl_b081_01E02970 {
    u8 pad0[6];
    s16 life;
    u8 pad8[0x20];
    u8 c28[4];
    u8 c2C[4];
    s16 kind;
    s16 age;
    u8 pad34[2];
    s16 state;
} Fl_b081_01E02970;

static s32 func_01E02970_b081(s32 arg0, Fl_b081_01E02970 *o) {
    extern s32 func_001076F0();
    if (o->state == 1) {
        func_001076F0(o->c28, 0xC0, 0xC0, 0xC0);
        func_001076F0(o->c2C, 0xC0, 0xC0, 0xC0);
        if (o->kind == 0) {
            o->life = 8;
        } else if ((s16)o->kind == 1) {
            o->life = 30;
        } else if ((s16)o->kind == 2) {
            o->life = 35;
        }
        o->state = 2;
    }
    if (o->age < o->life) {
        if (o->c28[3] < 0x80) {
            o->c28[3] += 0x15;
        }
        if (o->c2C[3] < 0x80) {
            o->c2C[3] += 0x15;
        }
    } else {
        if (o->c28[3] > 10) {
            o->c28[3] -= 9;
        } else {
            o->state = 0;
        }
        if (o->c2C[3] > 10) {
            o->c2C[3] -= 9;
        } else {
            o->c2C[3] = 0;
        }
    }
    if (o->age % 8 == 7) {
        func_001076F0(o->c28, 0x20, 0xC0, 0xC0);
        func_001076F0(o->c2C, 0x20, 0xC0, 0xC0);
    } else if (o->age % 8 == 6) {
        func_001076F0(o->c28, 0x20, 0x20, 0xC0);
        func_001076F0(o->c2C, 0x20, 0x20, 0xC0);
    }
    o->age++;
    return 0;
}

/* shape b081:01E02B40, 134 insns: a grey puff with an orange core: on start size 10, grey 0x60, the core 0x80/0x30/0x10 or
   0x80/0x60/0x10 by the game counter's parity (g+0x3D42), a random angle, core alpha 8; alpha up by 12 for 18 ticks,
   then down by 9 until it ends; it blinks dark/grey on odd/even ticks, spins for 10 ticks, h30 is 0 on tick 10 and 2
   otherwise; it grows by 4 (8 once the counter reaches 248) and ends after 210 ticks */

typedef struct {
    u8 pad0[0x3D42];
    s16 count;
} Game_b081_01E02B40;

typedef struct {
    u8 pad0[0x10];
    s32 rot;
    u8 pad14[0x14];
    u8 c0[4];
    u8 c1[4];
    s16 h30;
    s16 t;
    u8 pad34[2];
    s16 mode;
    s16 size;
    s16 ang;
} Obj_b081_01E02B40;

static s32 func_01E02B40_b081(Game_b081_01E02B40 *g, Obj_b081_01E02B40 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->size = 10;
        func_001076F0(o->c0, 0x60, 0x60, 0x60);
        if (g->count % 2 == 1) {
            func_001076F0(o->c1, 0x80, 0x30, 0x10);
        } else {
            func_001076F0(o->c1, 0x80, 0x60, 0x10);
        }
        o->ang = func_0019A5C8() % 360;
        o->mode = 2;
        o->c1[3] = 8;
    }
    if (o->t < 18) {
        o->c0[3] += 12;
    } else if (o->c0[3] > 10) {
        o->c0[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->c0, 0x30, 0x30, 0x30);
    } else {
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
    }
    if (o->t < 10) {
        func_00205C40((s32)&o->rot);
        o->rot += 0x4000;
    }
    if (o->t == 10) {
        o->h30 = 0;
    } else {
        o->h30 = 2;
    }
    if (g->count < 248) {
        if (o->t != 0) {
            o->size += 4;
        }
    } else if (o->t != 0) {
        o->size += 8;
    }
    o->t++;
    if (o->t > 210) {
        o->mode = 0;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b081", func_01E02D60_b081);

/* shape b081:01E02FB0, 139 insns: b081:01E03BF0 family spark in two kinds: kind 0 white, size 12, f30 0..99, step 1..3; kind 1 dark grey, size 8, f30 0..24, step 2; frame 0..6, fA 0..7, fC = old kind, f8 0..34, life 2..4: full alpha then down by 15; grows 1 and f30 by the step each tick */

typedef struct {
    u8 pad0[6];
    s16 life;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 fE;
    u8 pad10[0x18];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b081_01E02FB0;

static s32 func_01E02FB0_b081(s32 arg0, Fx_b081_01E02FB0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        if (o->f30 == 0) {
            o->f38 = 12;
        } else {
            o->f38 = 8;
        }
        o->f34 = func_0019A5C8() % 7;
        if (o->f30 == 0) {
            func_001076F0(o->col, 0x80, 0x80, 0x80);
        } else {
            func_001076F0(o->col, 0x20, 0x20, 0x20);
        }
        o->fA = func_0019A5C8() % 8;
        o->fC = o->f30;
        if (o->f30 == 0) {
            o->f30 = func_0019A5C8() % 100;
        } else {
            o->f30 = func_0019A5C8() % 25;
        }
        if (o->fC == 0) {
            o->fE = func_0019A5C8() % 3 + 1;
        } else {
            o->fE = 2;
        }
        o->f8 = func_0019A5C8() % 35;
        o->life = func_0019A5C8() % 3 + 2;
        o->f3A = 0;
        o->mode = 2;
    }
    if (o->tick < o->life) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 16) {
        o->col[3] -= 15;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->f38++;
    }
    if (o->tick != 0) {
        o->f30 += o->fE;
    }
    o->tick++;
    return 0;
}

/* shape b081:01E031E0, 73 insns: a white/red two-colour flash (size 6, 6 x 20 growing 17 a tick): in by 64 up to 0x80 for 4 ticks, then out by 9 and ends */

typedef struct {
    u8 pad0[8];
    s16 h8;
    s16 hA;
    u8 padC[0x1C];
    u8 col[4];
    u8 col2[4];
    s16 h30;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
    s16 ang;
} Glow_b081_01E031E0;

static s32 func_01E031E0_b081(s32 arg0, Glow_b081_01E031E0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 6;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        func_001076F0(o->col2, 0x80, 0x10, 0x10);
        o->h8 = 6;
        o->hA = 20;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 4) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
        if (o->col2[3] < 0x80) {
            o->col2[3] += 0x40;
        }
    } else {
        if (o->col[3] > 10) {
            o->col[3] -= 9;
        } else {
            o->mode = 0;
        }
        if (o->col2[3] > 10) {
            o->col2[3] -= 9;
        } else {
            o->col2[3] = 0;
        }
    }
    if (o->tick != 0) {
        o->hA += 17;
    }
    o->tick++;
    return 0;
}

/* shape b081:01E03310, 96 insns: colour (0x80, 0x40, 0x40); on start reads the model angle, random rotation, size
   0x5A, alpha 0, 0x38 from the game value 0x3D3E; alpha grows by 0x80 (below 0x80) for 8 ticks, then fades by 9 and
   stops; the size grows by 0..6 a tick up to 0x10E, then it ends */

typedef struct {
    u8 pad0[0x3D3E];
    s16 v;
} Game_b081_01E03310;

typedef struct {
    u8 pad0[0x10];
    s32 rot[3];
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 size;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
} Fx_b081_01E03310;

static s32 func_01E03310_b081(Game_b081_01E03310 *g, Fx_b081_01E03310 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F6160(s32, void *);
    s32 ang[4];

    func_001076F0(o->col, 0x80, 0x40, 0x40);
    if (o->mode == 1) {
        func_001F6160(func_001F53A0(), ang);
        o->rot[0] = func_0019A5C8() % 0xFFFF;
        o->rot[1] = func_0019A5C8() % 0xFFFF;
        o->rot[2] = func_0019A5C8() % 0xFFFF;
        o->f34 = 0;
        o->size = 0x5A;
        o->mode = 2;
        o->col[3] = 0;
        o->f38 = g->v;
    }
    if (o->tick < 8) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x80;
        }
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->tick++;
    if (o->size < 0x10E) {
        o->size += (s16)(func_0019A5C8() % 7);
    } else {
        o->mode = 0;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b081", func_01E03490_b081);

INCLUDE_ASM("asm/nonmatchings/mod/b081", func_01E036E0_b081);

/* shape b081:01E03A70, 95 insns: on start 0x6 = 8, alpha 0, the game's 0x1D trail points (0x3AE0) set to its point
   0x3CC0, 0x38 = 45; after the first tick 0x6 grows by 2 below 0x1C; alpha 0xC0 while the game step 0x3D42 is below
   0xF0, then fades by 5 and stops while 0x38 counts down; colour flickers (0xF0, 0x40/0xF0, 0x40); below step 0xE6 the point
   is registered with the game list 0x3CB0 (b081:01E00080, kind 30) */

typedef struct {
    u8 pad0[0x3AE0];
    Vec4f trail[0x1D];
    u8 list[0x10];
    Vec4f point;
    u8 pad3CD0[0x72];
    s16 step;
} Game_b081_01E03A70;

typedef struct {
    u8 pad0[6];
    s16 f6;
    u8 pad8[0x20];
    u8 col[4];
    u8 pad2C[6];
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f38;
} Fx_b081_01E03A70;

static s32 func_01E03A70_b081(Game_b081_01E03A70 *g, Fx_b081_01E03A70 *o) {
    extern void b081_01E00080(void *, s32, s32, void *);
    extern void func_001076F0(void *, s32, s32, s32);
    s32 i;
    Vec4f *q;

    if (o->mode == 1) {
        o->f6 = 8;
        q = g->trail;
        o->col[3] = 0;
        for (i = 0; i < 0x1D; i++) {
            q->x = g->point.x;
            q->y = g->point.y;
            q->z = g->point.z;
            q++;
        }
        o->f38 = 45;
        o->mode = 2;
    }
    if (o->tick != 0) {
        if (o->f6 < 0x1C) {
            o->f6 += 2;
        }
    }
    if (g->step < 0xF0) {
        o->col[3] = 0xC0;
    } else {
        if (o->col[3] > 6) {
            o->col[3] -= 5;
        } else {
            o->mode = 0;
        }
        if (o->f38 > 0) {
            o->f38--;
        }
    }
    if (o->tick % 2 == 0) {
        func_001076F0(o->col, 0xF0, 0x40, 0x40);
    } else {
        func_001076F0(o->col, 0xF0, 0xF0, 0x40);
    }
    if (g->step < 0xE6) {
        b081_01E00080(g->list, 30, 0, &g->point);
    }
    o->tick++;
    return 0;
}

/* shape b081:01E03BF0, 124 insns: b484:01E01C50 family red spark (size 10, frame 0..3 stepping every third tick to 7 when fC was 0, life 8..15, then fades by 9); fA rerolled 0..7 and the angle turns 4 each tick */

typedef struct {
    u8 pad0[6];
    s16 life;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 fE;
    u8 pad10[0x18];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b081_01E03BF0;

static s32 func_01E03BF0_b081(s32 arg0, Fx_b081_01E03BF0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 10;
        o->f34 = func_0019A5C8() % 4;
        func_001076F0(o->col, 0xFF, 0x10, 0x10);
        o->fA = func_0019A5C8() % 2;
        o->fC = o->f30;
        o->f30 = func_0019A5C8() % 40 + 40;
        o->fE = func_0019A5C8() % 2 + 1;
        o->f8 = func_0019A5C8() % 35;
        o->life = func_0019A5C8() % 8 + 8;
        o->f3A = func_0019A5C8() % 360;
        o->mode = 2;
    }
    if (o->tick < o->life) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->fC == 0 && o->tick % 3 == 1) {
        if (o->f34 < 7) {
            o->f34++;
        }
    }
    o->fA = func_0019A5C8() % 8;
    o->f3A += 4;
    o->tick++;
    return 0;
}

/* shape b081:01E03DE0, 106 insns: a grey rising spark: frame 12, random sub-frame 0..3, frame 0..1, start height 40..239 (old one
   kept), rise 3..7 once started, width 0..34, hold 3..6, angle; alpha up by 32 to 0x80 until the hold, then down by 9 */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 w;
    s16 frame;
    s16 y0;
    s16 step;
    u8 pad10[0x18];
    u8 c0[4];
    u8 pad2C[4];
    s16 y;
    s16 t;
    s16 sub;
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b081_01E03DE0;

static s32 func_01E03DE0_b081(void *arg0, Obj_b081_01E03DE0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 0xC;
        o->sub = func_0019A5C8() % 4;
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
        o->frame = func_0019A5C8() % 2;
        o->y0 = o->y;
        o->y = func_0019A5C8() % 200 + 0x28;
        o->step = func_0019A5C8() % 5 + 3;
        o->w = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 4 + 3;
        o->ang = func_0019A5C8() % 360;
        o->state = 2;
    }
    if (o->t < o->hold) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x20;
        }
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        o->y += o->step;
    }
    o->t++;
    return 0;
}

/* shape b081:01E03F90, 108 insns: on start 0x38 = 3, variant 0..3, colour 0x80 grey, 0xA 0..1, 0xC keeps the old 0x30,
   0x30 40..439, speed 3..7 (0xE), 0x8 0..34, hold 1..4 (0x6), random 0x3A; alpha grows by 0x20 (below 0x80) during the
   hold, then fades by 9 and stops; after the first tick 0x30 shrinks by the speed while positive */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 speed;
    u8 pad10[0x18];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b081_01E03F90;

static s32 func_01E03F90_b081(s32 arg0, Fx_b081_01E03F90 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 3;
        o->f34 = func_0019A5C8() % 4;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->fA = func_0019A5C8() % 2;
        o->fC = o->f30;
        o->f30 = func_0019A5C8() % 400 + 40;
        o->speed = func_0019A5C8() % 5 + 3;
        o->f8 = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 4 + 1;
        o->f3A = func_0019A5C8() % 360;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x20;
        }
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        if (o->f30 > 0) {
            o->f30 -= o->speed;
        }
    }
    o->tick++;
    return 0;
}

/* shape b081:01E04140, 63 insns: a grey/olive two-colour glow of size 300 at a random angle, spun by 0x4000 a tick: in by 32 up to 0x80 for 22 ticks, then out by 7 and ends */

typedef struct {
    u8 pad0[2];
    s16 h2;
    u8 pad4[2];
    s16 h6;
    u8 pad8[8];
    s32 w10;
    s32 w14;
    s32 w18;
    u8 pad1C[0xC];
    u8 col[4];
    u8 col2[4];
    s16 state;
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f38;
    s16 ang;
} Glow_b081_01E04140;

static s32 func_01E04140_b081(s32 arg0, Glow_b081_01E04140 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 300;
        func_001076F0(o->col, 0x20, 0x20, 0x20);
        func_001076F0(o->col2, 0x30, 0x30, 0x10);
        o->ang = func_0019A5C8() % 360;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 22) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x20;
        }
    } else if (o->col[3] > 8) {
        o->col[3] -= 7;
    } else {
        o->mode = 0;
    }
    func_00205C40((s32)&o->w10);
    o->w10 += 0x4000;
    o->tick++;
    return 0;
}

/* shape b081:01E04240, 105 insns: a flickering light on the scene point: colour 128/4/2/0, range 100; power up by 0.05 while the
   scene timer is under 284, then flickering between 128/4/2 and 96/10/5 once full; down by 0.1 after until it ends; ends when
   the scene state is 1 */

typedef struct {
    u8 pad0[0x34F0];
    f32 l0[4];
    f32 pos[3];
    u8 pad350C[4];
    f32 f20;
    f32 range;
    f32 power;
    u8 pad351C[0x3CC0 - 0x351C];
    f32 src[3];
    u8 pad3CCC[0x24];
    s32 state;
    u8 pad3CF4[0x4E];
    s16 timer;
} Scene_b081_01E04240;

typedef struct {
    u8 pad0[0x30];
    s16 down;
    s16 t;
    u8 pad34[2];
    s16 live;
} Obj_b081_01E04240;

static s32 func_01E04240_b081(Scene_b081_01E04240 *g, Obj_b081_01E04240 *o) {
    extern void func_001F6C10(void *);

    if (o->live == 1) {
        g->l0[0] = 128.0f;
        g->l0[1] = 4.0f;
        g->l0[2] = 2.0f;
        g->l0[3] = 0.0f;
        g->f20 = 0.0f;
        g->range = 100.0f;
        g->power = 0.0f;
        o->live = 2;
        o->down = 0;
    }
    g->pos[0] = g->src[0];
    g->pos[1] = g->src[1];
    g->pos[2] = g->src[2];
    if (g->timer < 0x11C) {
        if (g->power < 1.0f) {
            g->power += 0.05f;
        } else if (o->t % 2 == 1) {
            g->l0[1] = 4.0f;
            g->l0[2] = 2.0f;
            g->l0[0] = 128.0f;
        } else {
            g->l0[1] = 10.0f;
            g->l0[2] = 5.0f;
            g->l0[0] = 96.0f;
        }
    } else if (!(g->power <= 0.1f)) {
        g->power -= 0.1f;
    } else {
        o->live = 0;
    }
    if (g->state == 1) {
        o->live = 0;
    }
    if (o->live == 0) {
        func_001F6C10(NULL);
    } else {
        func_001F6C10(g->l0);
    }
    o->t++;
    return 0;
}

/* shape b081:01E043F0, 51 insns: volume fade by game state (b003:01E02330 family): state at 0x3CF0 limit 0x1E, floor 0x60, down 10,
   up 10, cap 0x80; past frame 0x132 of the game timer the volume is set to 0x80 and the fade ends */

typedef struct {
    u8 pad[0x3CF0];
    s32 state;
    u8 pad3CF4[0x4E];
    s16 timer;
} Game_b081_01E043F0;

typedef struct {
    u8 pad[0x30];
    s16 vol;
    u8 pad32[4];
    s16 mode;
} Fade_b081_01E043F0;

static s32 func_01E043F0_b081(Game_b081_01E043F0 *g, Fade_b081_01E043F0 *o) {
    extern void func_001F6D00(s32);

    if (o->mode == 1) {
        o->vol = 0x80;
        o->mode = 2;
    }
    if (g->state > 0x1E) {
        if (o->vol > 0x60) {
            o->vol -= 10;
        } else {
            o->vol = 0x60;
        }
    } else {
        if (o->vol < 0x80) {
            o->vol += 10;
        } else {
            o->vol = 0x80;
        }
    }
    if (g->timer < 0x132) {
        func_001F6D00((u8)o->vol);
    } else {
        func_001F6D00(0x80);
        o->mode = 0;
    }
    return 0;
}

/* shape b081:01E044C0, 98 insns: a grey full-screen veil: one sprite over the whole screen at the object alpha, texture window
   0..0.625 x 0..0.875, sent at once; alpha up by 8 to 0x40 until frame 200, then down by 9 until it ends */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b081_01E044C0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    struct {
        f32 s, t;
        Xyz_b081_01E044C0 p;
    } v[2];
    u8 pad38[0x20];
} Pkt_b081_01E044C0;

typedef struct {
    u8 pad0[0x28];
    u8 c0[4];
    u8 pad2C[6];
    s16 t;
    u8 pad34[2];
    s16 state;
} Obj_b081_01E044C0;

static s32 func_01E044C0_b081(void *arg0, Obj_b081_01E044C0 *o) {
    extern void func_002087A0(void *, s32);
    extern s32 func_00207500(void);
    Pkt_b081_01E044C0 pkt __attribute__((aligned(8)));

    ((Pkt_b081_01E044C0 *)(s32)&pkt)->count = 0x26;
    ((Pkt_b081_01E044C0 *)(s32)&pkt)->tag = 5;
    ((Pkt_b081_01E044C0 *)(s32)&pkt)->regs = 0x42421;
    ((Pkt_b081_01E044C0 *)(s32)&pkt)->pad = 0;
    pkt.r = 0x80;
    pkt.g = 0x80;
    pkt.b = 0x80;
    pkt.a = o->c0[3];
    pkt.q = 1.0f;
    ((Xyz_b081_01E044C0 *)(s32)&pkt.v[0].p)->x = 0x6BF8;
    pkt.v[0].p.y = 0x71F8;
    pkt.v[0].p.z = 0xFFFFFF;
    pkt.v[0].p.f = 0;
    pkt.v[1].p.x = 0x93F8;
    pkt.v[1].p.y = 0x8DF8;
    pkt.v[1].p.z = 0xFFFFFF;
    pkt.v[1].p.f = 0;
    pkt.v[0].s = 0.0f;
    pkt.v[0].t = 0.0f;
    pkt.v[1].s = 0.625f;
    pkt.v[1].t = 0.875f;
    func_002086D0(&pkt, ((u64)0x80 << 32) | 0x44);
    func_002087A0(&pkt, 1);
    func_002075F0((s32)&pkt, func_00207500(), 0);
    if (o->t < 0xC8) {
        if (o->c0[3] < 0x40) {
            o->c0[3] += 8;
        }
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    o->t++;
    return 0;
}

/* shape b081:01E04650, 41 insns: look up the textures: group 4 cells 0-2, group 4 cells 13-15, group 5
   cells 0-2 (variant of b205:01E02370) */

typedef struct {
    u8 pad0[0x2B0];
    s32 tex[16];
    u8 pad2F0[0x39E0];
    s32 tex5[3];
} Scene_b081_01E04650;

static void func_01E04650_b081(s32 arg0, Scene_b081_01E04650 *o) {
    s32 i;

    for (i = 0; i < 3; i++) {
        o->tex[i] = func_00202BF0(4, i);
    }
    for (i = 13; i < 16; i++) {
        o->tex[i] = func_00202BF0(4, i);
    }
    for (i = 0; i < 3; i++) {
        o->tex5[i] = func_00202BF0(5, i);
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b081", func_01E04700_b081);

/* shape b081:01E056E0, 74 insns: twin of b046:01E03E20: take the first free slot of the 200-slot pool, clear it,
   give it the scene's colour twice, the scene matrix, the scene's value 0x3D38 and 0x3D32 and the two arguments; returns 1 if a
   slot was found */

typedef struct {
    u8 pad[0x20];
    s32 b;
    s32 a;
    u8 c0[4];
    u8 c1[4];
    s16 v;
    u8 pad32[0x4];
    s16 used;
    u8 pad38[0x2];
    s16 w;
    u8 pad3C[0x4];
} Slot_b081_01E056E0;

typedef struct {
    u8 pad[0x250];
    u8 m[0xA0];
    Slot_b081_01E056E0 s[200];
    u8 pad34F0[0x804];
    u8 r, g, b, a;
    u8 pad3CF8[0x3A];
    s16 w;
    u8 pad3D34[0x4];
    s16 v;
} Pool_b081_01E056E0;

static s32 func_01E056E0_b081(Pool_b081_01E056E0 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b081_01E056E0 *s = NULL;
    s16 i;
    s32 ret;

    for (i = 0; i < 200; i++) {
        if (o->s[i].used == 0) {
            func_00195108(&o->s[i], 0x40);
            o->s[i].used = 1;
            s = &o->s[i];
            i = 200;
        }
    }
    if (s != NULL) {
        func_001076F0(s->c0, o->r, o->g, o->b);
        s->c0[3] = o->a;
        func_001076F0(s->c1, o->r, o->g, o->b);
        s->c1[3] = o->a;
        func_00106AB0(s, o->m, 0);
        ret = 1;
        s->v = o->v;
        s->w = o->w;
        s->b = b;
        s->a = a;
    } else {
        ret = 0;
    }
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/mod/b081", func_01E05810_b081);

INCLUDE_ASM("asm/nonmatchings/mod/b081", func_01E05C10_b081);

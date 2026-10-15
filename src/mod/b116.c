#include "common.h"

/* shape b081:01E00080, 30 insns, 24 copies (s32 twin of b034:01E00080): shift a position history down by one, the newest from src */

static s32 func_01E00080_b116(Vec4f *dst, s32 n, s32 arg2, Vec4f *src) {
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

static void func_01E00100_b116(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

INCLUDE_ASM("asm/nonmatchings/mod/b116", func_01E009A0_b116);

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

static void func_01E00C80_b116(Obj_b081_01E016D0 *o, Spr_b081_01E016D0 *s, s32 flags, s8 *tbl) {
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
    func_01E00100_b116((Pk_b003_01E00080 *)p, &o->rect, o->mode);
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

/* shape b116:01E011E0, 282 insns: full ring of 36 segments (10 table steps each) between an s16 inner and outer
   radius, variant of b082:01E00920 with a smaller data layout; blend from flags >> 4, depth mode flags & 0xF */

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[0x54];
    u8 table[1];
} Obj_b116_01E011E0;

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
} Data_b116_01E011E0;

static void func_01E011E0_b116(Obj_b116_01E011E0 *o, Data_b116_01E011E0 *data, s32 flags, Vec4f pos) {
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
            a = j + (data->step + 10);
            quad[1].x = inner * func_00108030(o->table, a, 1);
            quad[1].z = inner * func_00108030(o->table, a, 0);
            quad[3].x = outer * func_00108030(o->table, a, 1);
            quad[3].z = outer * func_00108030(o->table, a, 0);
        } else {
            quad[0] = quad[1];
            quad[2] = quad[3];
            a = j + (data->step + 10);
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
        j += 10;
        i++;
    } while (i < 36);
}

INCLUDE_ASM("asm/nonmatchings/mod/b116", func_01E01650_b116);

/* shape b116:01E01CE0, 105 insns: on start 0x38 = 60, variant 0..6, colour (0x20, 0x10, 0x10), 0xA 0..7, 0xC keeps the old 0x30, 0x30
   0..19, speed 16..45 (0xE), 0x8 0..34, hold 3..7 (0x6), 0x3A 0..2; alpha 0x80 during the hold, then fades by 8 and
   stops; after the first tick 0x38 grows by 8 and 0x30 by the speed */

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
} Fx_b116_01E01CE0;

static s32 func_01E01CE0_b116(s32 arg0, Fx_b116_01E01CE0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 60;
        o->f34 = func_0019A5C8() % 7;
        func_001076F0(o->col, 0x20, 0x10, 0x10);
        o->fA = func_0019A5C8() % 8;
        o->fC = o->f30;
        o->f30 = func_0019A5C8() % 20;
        o->speed = func_0019A5C8() % 30 + 16;
        o->f8 = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 5 + 3;
        o->f3A = func_0019A5C8() % 3;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 9) {
        o->col[3] -= 8;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->f38 += 8;
    }
    if (o->tick != 0) {
        o->f30 += o->speed;
    }
    o->tick++;
    return 0;
}

/* shape b003:01E01780, 56 insns, 6 copies: a rising, spinning glow: fades in over 2 frames, then out (variant of b018:01E02480) */

typedef struct {
    u8 pad0[0xA];
    s16 fA;
    u8 padC[0x1C];
    u8 c0[4];
    u8 pad2C[6];
    s16 t;
    s16 f34;
    s16 state;
    s16 h38;
} Obj_b003_01E01780;

static s32 func_01E01E90_b116(void *arg0, Obj_b003_01E01780 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 0x50;
        o->f34 = func_0019A5C8() % 4;
        o->state = 2;
    }
    if (o->t < 2) {
        if (o->c0[3] < 0xA0) {
            o->c0[3] += 0x50;
        }
    } else if (o->c0[3] > 16) {
        o->c0[3] -= 15;
    } else {
        o->state = 0;
    }
    func_001076F0(o->c0, 0x80, 0x40, 0);
    o->fA += 6;
    o->t++;
    o->h38 += 0x14;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b116", func_01E01F70_b116);

INCLUDE_ASM("asm/nonmatchings/mod/b116", func_01E02370_b116);

INCLUDE_ASM("asm/nonmatchings/mod/b116", func_01E02630_b116);

typedef struct {
    u8 pad00[2];
    s16 h2;
    u8 pad04[2];
    s16 h6;
    s16 h8;
    u8 pad0A[2];
    s16 hC;
    s16 hE;
    s32 w10;
    s32 w14;
    s32 w18;
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 h30;
    s16 h32;
    s16 h34;
    s16 h36;
    s16 h38;
    s16 h3A;
} Obj_b003_01E01C70;

static s32 func_01E029F0_b116(s32 unused, Obj_b003_01E01C70 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->h36 == 1) {
        o->h38 = 45;
        o->h34 = 0;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->h30 = func_0019A5C8() % 300 + 130;
        o->h3A = func_0019A5C8() % 360;
        o->hE = 0;
        o->h8 = func_0019A5C8() % 35;
        o->hC = func_0019A5C8() % 3 + 2;
        o->h6 = func_0019A5C8() % 10 + 15;
        o->h36 = 2;
    }
    if (o->h32 < o->h6) {
        if (o->col[3] < 0x81) {
            o->col[3] += 0x12;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->h36 = 0;
    }
    if (o->h32 != 0) {
        if (o->h38 < 90) {
            o->h38 += 2;
        }
    }
    if (o->h32 % 2 == 1) {
        if (o->h34 < 5) {
            o->h34++;
        }
    }
    if (o->h32 != 0) {
        o->h30 += o->hE;
    }
    if (o->h32 != 0) {
        o->h38 += 2;
    }
    o->h2++;
    o->w10 = func_0019A5C8() % 360;
    o->w14 = func_0019A5C8() % 360;
    o->w18 = func_0019A5C8() % 360;
    o->h32++;
    return 0;
}

/* shape b003:01E01EC0, 146 insns, 4 copies: step of a rising puff: on state 1 sets a grey colour, random start, angle,
   size, layers and lifetime; fades in by 0x12, then out by 9 until it ends; grows, climbs and spins randomly. */

typedef struct {
    s16 x, y, z;
    s16 life;
    s16 h8;
    u8 padA[2];
    s16 layers;
    s16 speed;
    s32 rot[3];
    u8 pad1C[0xC];
    u8 c0[4];
    u8 pad2C[4];
    s16 pos;
    s16 t;
    s16 h34;
    s16 state;
    s16 size;
    s16 ang;
} Obj_b003_01E01EC0;

static s32 func_01E02C40_b116(void *arg0, Obj_b003_01E01EC0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = 0x2D;
        o->h34 = 0;
        func_001076F0(o->c0, 0x20, 0x20, 0x20);
        o->pos = func_0019A5C8() % 300 + 130;
        o->ang = func_0019A5C8() % 360;
        o->speed = 0;
        o->h8 = func_0019A5C8() % 35;
        o->layers = func_0019A5C8() % 3 + 2;
        o->life = func_0019A5C8() % 10 + 15;
        o->state = 2;
    }
    if (o->t < o->life) {
        if (o->c0[3] <= 0x80) {
            o->c0[3] += 0x12;
        }
    } else if (o->c0[3] > 10) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        if (o->size < 0x5A) {
            o->size += 2;
        }
    }
    if (o->t % 2 == 1) {
        if (o->h34 < 5) {
            o->h34++;
        }
    }
    if (o->t != 0) {
        o->pos += o->speed;
    }
    if (o->t != 0) {
        o->size += 2;
    }
    o->y++;
    o->rot[0] = func_0019A5C8() % 360;
    o->rot[1] = func_0019A5C8() % 360;
    o->rot[2] = func_0019A5C8() % 360;
    o->t++;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b116", func_01E02E90_b116);

INCLUDE_ASM("asm/nonmatchings/mod/b116", func_01E03190_b116);

INCLUDE_ASM("asm/nonmatchings/mod/b116", func_01E03360_b116);

/* shape b116:01E036C0, 108 insns: on start 0x38 = 50, both colours 0x80 grey (second alpha 0), 0x8/0xA = 100/200, 0xE
   = 1 when 0x3A is set, 0x18 = 0 for kind 1, 0x10 = 0x4000; both alphas grow by 10 for 12 ticks, then once the game
   step 0x4A62 reaches 0x147 they fade by 13 (the first ends it); after tick 20 0x10 winds down by 0x200 to 0 */

typedef struct {
    u8 pad0[0x4A62];
    s16 step;
} Game_b116_01E036C0;

typedef struct {
    u8 pad0[8];
    s16 f8;
    s16 fA;
    u8 padC[2];
    s16 fE;
    s32 w10;
    u8 pad14[4];
    s32 w18;
    u8 pad1C[0xC];
    u8 col[4];
    u8 col2[4];
    s16 kind;
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b116_01E036C0;

static s32 func_01E036C0_b116(Game_b116_01E036C0 *g, Fx_b116_01E036C0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 50;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        func_001076F0(o->col2, 0x80, 0x80, 0x80);
        o->f8 = 100;
        o->fA = 200;
        if (o->f3A == 0) {
            o->fE = 0;
        } else {
            o->fE = 1;
        }
        o->mode = 2;
        if (o->kind == 1) {
            o->w18 = 0;
        }
        o->w10 = 0x4000;
        o->col2[3] = 0;
    }
    if (o->tick < 12) {
        o->col[3] += 10;
        o->col2[3] += 10;
    } else if (g->step >= 0x147) {
        if (o->col[3] > 0xE) {
            o->col[3] -= 13;
        } else {
            o->mode = 0;
        }
        if (o->col2[3] > 0xE) {
            o->col2[3] -= 13;
        } else {
            o->col2[3] = 0;
        }
    }
    if (o->kind == 0) {
        if (o->tick > 0x14) {
            if (o->w10 > 0) {
                o->w10 -= 0x200;
            } else {
                o->w10 = 0;
            }
        }
    } else if (o->tick > 0x14) {
        if (o->w10 > 0) {
            o->w10 -= 0x200;
        } else {
            o->w10 = 0;
        }
    }
    o->tick++;
    return 0;
}

/* shape b116:01E03870, 74 insns: a white two-colour glow (size 185, 200 x 200, mirrored when it has an angle): in by 7 for 18 ticks; out by 13 once the scene value reaches 327, and ends */

typedef struct {
    u8 pad0[8];
    s16 h8;
    s16 hA;
    u8 padC[2];
    s16 hE;
    s32 w10;
    s32 w14;
    s32 w18;
    u8 pad1C[8];
    s32 w24;
    u8 col[4];
    u8 col2[4];
    s16 h30;
    s16 tick;
    s16 kind;
    s16 used;
    s16 f38;
    s16 ang;
    u8 pad3C[4];
} Glow_b116_01E03870;

typedef struct {
    u8 pad[0x4A62];
    s16 val;
} Game_b116_01E03870;

static s32 func_01E03870_b116(Game_b116_01E03870 *g, Glow_b116_01E03870 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->used == 1) {
        o->f38 = 185;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        func_001076F0(o->col2, 0x80, 0x80, 0x80);
        o->h8 = 200;
        o->hA = 200;
        if (o->ang == 0) {
            o->hE = 0;
        } else {
            o->hE = 1;
        }
        o->used = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 18) {
        o->col[3] += 7;
        o->col2[3] += 7;
    } else if (g->val >= 327) {
        if (o->col[3] > 14) {
            o->col[3] -= 13;
        } else {
            o->used = 0;
        }
        if (o->col2[3] > 14) {
            o->col2[3] -= 13;
        } else {
            o->col2[3] = 0;
        }
    }
    o->tick++;
    return 0;
}

/* shape b116:01E039A0, 62 insns: a white-green burst (b116:01E03D70 shape): frame 5 rising by 10, its h6 trailing 5
   behind; alpha up by 0x60 for 2 frames, then down by 10 until it ends; x turn a quarter */

typedef struct {
    u8 pad0[6];
    s16 h6;
    u8 pad8[8];
    s32 rot;
    u8 pad14[0x14];
    u8 c0[4];
    u8 c1[4];
    u8 pad30[2];
    s16 t;
    u8 pad34[2];
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b116_01E039A0;

static s32 func_01E039A0_b116(void *arg0, Obj_b116_01E039A0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 5;
        func_001076F0(o->c0, 0xF0, 0xF0, 0xF0);
        func_001076F0(o->c1, 0xF0, 0x80, 0x10);
        o->ang = func_0019A5C8() % 360;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 2) {
        o->c0[3] += 0x60;
    } else if (o->c0[3] > 0x10) {
        o->c0[3] -= 0xA;
    } else {
        o->state = 0;
    }
    o->rot = 0x4000;
    o->h6 = o->h38 - 5;
    o->h38 += 0xA;
    o->t++;
    return 0;
}

typedef struct {
    u8 pad00[0x10];
    s32 rot[4];
    u8 pad20[8];
    u8 c28[4];
    u8 c2C[4];
    s16 h30;
    s16 h32;
    u8 pad34[2];
    s16 h36;
    s16 h38;
    s16 h3A;
} Obj_b116_01E03AA0;

static s32 func_01E03AA0_b116(s32 unused, Obj_b116_01E03AA0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00205C40(void *);

    if (o->h36 == 1) {
        if (o->h30 == 0) {
            o->h38 = 500;
            func_001076F0(o->c28, 0xF0, 0xF0, 0xF0);
            func_001076F0(o->c2C, 0xF0, 0x80, 0x10);
        } else if (o->h30 == 1) {
            o->h38 = 210;
            func_001076F0(o->c2C, 0xF0, 0xF0, 0xF0);
            func_001076F0(o->c28, 0xF0, 0x80, 0x10);
        }
        o->h3A = func_0019A5C8() % 360;
        o->h36 = 2;
        o->c2C[3] = 0;
    }
    if (o->h32 < 12) {
        if (o->h30 == 0) {
            if (o->c28[3] < 0xC0) {
                o->c28[3] += 0x18;
            }
        }
        if (o->h30 == 1) {
            if (o->c28[3] < 0xC0) {
                o->c2C[3] += 0x18;
            }
        }
    } else {
        if (o->h30 == 0) {
            if (o->c28[3] > 10) {
                o->c28[3] -= 9;
            } else {
                o->h36 = 0;
            }
        }
        if (o->h30 == 1) {
            if (o->c2C[3] > 10) {
                o->c2C[3] -= 9;
            } else {
                o->h36 = 0;
            }
        }
    }
    func_00205C40(o->rot);
    o->rot[0] += 0x4000;
    o->h32++;
    return 0;
}

/* shape b116:01E03C60, 67 insns: a white-green spinning burst (b116:01E03D70 shape): frame 40, random angle; alpha up by
   0x60 for 2 frames, then once the game timer passes 0x1B4 down by 9 until it ends; random turn plus a quarter */

typedef struct {
    u8 pad0[0x4A62];
    s16 timer;
} Game_b116_01E03C60;

typedef struct {
    u8 pad0[0x10];
    s32 rot[4];
    u8 pad20[8];
    u8 c0[4];
    u8 c1[4];
    u8 pad30[2];
    s16 t;
    u8 pad34[2];
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b116_01E03C60;

static s32 func_01E03C60_b116(Game_b116_01E03C60 *g, Obj_b116_01E03C60 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 0x28;
        func_001076F0(o->c0, 0xF0, 0xF0, 0xF0);
        func_001076F0(o->c1, 0xF0, 0x80, 0x10);
        o->ang = func_0019A5C8() % 360;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 2) {
        o->c0[3] += 0x60;
    } else if (g->timer > 0x1B4) {
        if (o->c0[3] > 0xA) {
            o->c0[3] -= 9;
        } else {
            o->state = 0;
        }
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->t++;
    return 0;
}

/* shape b116:01E03D70, 59 insns: a white-green spinning burst: set up once (frame 100, random angle), alpha up by 0x60
   for 2 frames, then down by 10 until it ends; a random turn plus a quarter each frame */

typedef struct {
    u8 pad0[0x10];
    s32 rot[4];
    u8 pad20[8];
    u8 c0[4];
    u8 c1[4];
    u8 pad30[2];
    s16 t;
    u8 pad34[2];
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b116_01E03D70;

static s32 func_01E03D70_b116(void *arg0, Obj_b116_01E03D70 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 0x64;
        func_001076F0(o->c0, 0xF0, 0xF0, 0xF0);
        func_001076F0(o->c1, 0xF0, 0x80, 0x10);
        o->ang = func_0019A5C8() % 360;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 2) {
        o->c0[3] += 0x60;
    } else if (o->c0[3] > 0x10) {
        o->c0[3] -= 0xA;
    } else {
        o->state = 0;
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->t++;
    return 0;
}

/* shape b116:01E03E60, 92 insns: a scene light pulse (b443:01E03E80 shape): sets the scene light (range 70, at the object's point),
   raises its strength by 0.2f to 1, then lowers it by 0.1f until it ends; applies the light while live and ends when the
   scene state at 0x44A0 is 1 */

typedef struct {
    u8 pad0[0x4470];
    f32 l0[4];
    f32 pos[3];
    u8 pad448C[4];
    f32 f20;
    f32 range;
    f32 power;
    u8 pad449C[0x4];
    s32 state;
} Scene_b116_01E03E60;

typedef struct {
    s16 x, y, z;
    u8 pad6[0x2A];
    s16 down;
    u8 pad32[4];
    s16 live;
} Obj_b116_01E03E60;

static s32 func_01E03E60_b116(Scene_b116_01E03E60 *g, Obj_b116_01E03E60 *o) {
    extern void func_001F6C10(void *);

    if (o->live == 1) {
        g->l0[0] = 0.0f;
        g->l0[1] = 4.0f;
        g->l0[2] = 2.0f;
        g->l0[3] = 0.0f;
        g->f20 = 0.0f;
        g->range = 70.0f;
        g->power = 0.0f;
        g->pos[0] = o->x;
        g->pos[1] = o->y;
        g->pos[2] = o->z;
        o->live = 2;
        o->down = 0;
    }
    if (o->down == 0) {
        if (g->power < 1.0f) {
            g->power += 0.2f;
        } else {
            o->down = 1;
        }
    } else if (!(g->power <= 0.1f)) {
        g->power -= 0.1f;
    } else {
        o->live = 0;
    }
    if (o->live == 0) {
        func_001F6C10(NULL);
    } else {
        func_001F6C10(g->l0);
    }
    if (g->state == 1) {
        o->live = 0;
    }
    return 0;
}

/* shape b116:01E03FD0, 47 insns: constant variant of b205:01E01E50 (volume fade by game state): state at 0x44A0 limit 0x1F,
   floor 0x30, down 10, up 10, cap 0x80 */

typedef struct {
    u8 pad[0x44A0];
    s32 state;
} Game_b116_01E03FD0;

typedef struct {
    u8 pad[0x30];
    s16 vol;
    u8 pad32[4];
    s16 mode;
} Fade_b116_01E03FD0;

static s32 func_01E03FD0_b116(Game_b116_01E03FD0 *g, Fade_b116_01E03FD0 *o) {
    extern void func_001F6D00(s32);

    if (o->mode == 1) {
        o->vol = 0x80;
        o->mode = 2;
    }
    if (g->state > 0x1E) {
        if (o->vol > 0x30) {
            o->vol -= 10;
        } else {
            o->vol = 0x30;
        }
    } else {
        if (o->vol < 0x80) {
            o->vol += 10;
        } else {
            o->vol = 0x80;
        }
    }
    if (g->state == 1) {
        func_001F6D00((u8)o->vol);
    } else {
        func_001F6D00((u8)o->vol);
    }
    return 0;
}

/* shape b003:01E023F0: b018:01E02DB0 with other constants (chatG) */

extern f32 D_01E06A00_b116;
extern f32 D_01E06A08_b116;

static s32 func_01E04090_b116(void) {
    f32 a;
    f32 b;

    *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E06A00_b116;
    *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E06A08_b116;
    func_001F7170(1, 0, (s32)&a, (s32)&b, 1);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b116", func_01E040E0_b116);

INCLUDE_ASM("asm/nonmatchings/mod/b116", func_01E042F0_b116);

/* shape b116:01E05410, 72 insns: twin of b046:01E03E20: take the first free slot of the 170-slot pool, clear it, give
   it the scene's colour twice, the scene matrix, the scene's value 0x4A5C and the two arguments; returns 1 if a
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
    u8 pad38[0x8];
} Slot_b116_01E05410;

typedef struct {
    u8 pad[0x250];
    u8 m[0x50];
    Slot_b116_01E05410 s[170];
    u8 pad2D20[0x1784];
    u8 r, g, b, a;
    u8 pad44A8[0x5B4];
    s16 v;
} Pool_b116_01E05410;

static s32 func_01E05410_b116(Pool_b116_01E05410 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b116_01E05410 *s = NULL;
    s16 i;
    s32 ret;

    for (i = 0; i < 170; i++) {
        if (o->s[i].used == 0) {
            func_00195108(&o->s[i], 0x40);
            o->s[i].used = 1;
            s = &o->s[i];
            i = 170;
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
        s->b = b;
        s->a = a;
    } else {
        ret = 0;
    }
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/mod/b116", func_01E05530_b116);

INCLUDE_ASM("asm/nonmatchings/mod/b116", func_01E058C0_b116);

INCLUDE_ASM("asm/nonmatchings/mod/b116", func_01E05D00_b116);

/* OVL_WARM */

/* shape b116:01E06870, 79 insns: the module's draw pass (b593:01E039C0 shape): opens a sprite packet on the stack, then runs every
   live slot (170 of 0x40 bytes) whose handler is shape b116:01E040E0 through it; queues the batch at the scene depth - 2000
   if any slot was live. */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b116_01E06870;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    struct {
        u64 st;
        Xyz_b116_01E06870 p;
    } v[2];
    u8 pad38[8];
    u64 t40;
    u64 t48;
    u8 pad50[8];
} Pkt_b116_01E06870;

typedef struct {
    u8 pad0[0x24];
    void *fn;
    u8 pad28[0xE];
    s16 active;
    u8 pad38[8];
} Slot_b116_01E06870;

typedef struct {
    u8 pad0[0x2A0];
    Slot_b116_01E06870 slot[170];
    u8 padEnd[0x4A14 - 0x2A0 - 170 * 0x40];
    s32 ctx;
    Pkt_b116_01E06870 *pkt;
    f32 depth;
} Scene_b116_01E06870;

static void func_01E06870_b116(Scene_b116_01E06870 *s) {
    extern void b116_01E040E0(Scene_b116_01E06870 *, Slot_b116_01E06870 *);
    extern s32 func_00207F60(void);
    extern void func_00208460(void);
    extern s32 func_001F53A0(void);
    extern void func_001F7060(s32, s32, void *, void *);
    extern s32 func_00207500(void);
    extern void func_00207FD0(s32, s32, s32);
    Pkt_b116_01E06870 pkt __attribute__((aligned(8)));
    s32 i;
    s32 n;

    s->pkt = &pkt;
    n = 0;
    s->ctx = func_00207F60();
    s->pkt->count = 0x26;
    s->pkt->tag = 5;
    s->pkt->regs = 0x42421;
    s->pkt->pad = 0;
    func_00208460();
    func_002086D0(s->pkt, ((u64)0x80 << 32) | 0x48);
    func_001F7060(func_001F53A0(), 0, &pkt.t40, &pkt.t48);
    func_00208460();
    for (i = 0; i < 170; i++) {
        if (s->slot[i].active != 0) {
            n++;
            if (s->slot[i].fn == (void *)b116_01E040E0) {
                b116_01E040E0(s, &s->slot[i]);
            }
        }
    }
    if (n != 0) {
        func_00207FD0(s->ctx, func_00207500(), (u32)(s->depth - 2000.0f));
    }
}

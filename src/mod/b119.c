#include "common.h"

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

static void func_01E00080_b119(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

/* shape b119:01E00920, 258 insns, 4 copies: draws a flat ring of 18 quads like shape b112:01E00B60, turned by the ring's own
   rotation instead of the camera's; radii converted once. */

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[0x54];
    u8 xD8[1];
} Obj_b119_01E00920;

typedef struct {
    u8 pad00[6];
    s16 inner;
    u8 pad08[8];
    Vec4f rot;
    u8 pad20[8];
    u8 col0[4];
    u8 col1[4];
    u8 pad30[8];
    s16 outer;
    s16 start;
} Ring_b119_01E00920;

static void func_01E00920_b119(Obj_b119_01E00920 *o, Ring_b119_01E00920 *s, s32 mode, Vec4f pos) {
    extern void func_00107990(void *, void *, s32);
    extern void func_001092E0(void *, s32);
    extern void func_001094F0(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern void func_00109380(void *, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f p2;
    Vec4f scale;
    f32 m[16];
    f32 depth[4];
    u8 pkt[0x90];
    s32 t;
    f32 ro;
    f32 ri;
    s32 k;
    s16 a;
    u8 *p;

    p = pkt;
    a = 0;
    func_00107990(p, s->col0, 2);
    func_00107990(p, s->col1, 1);
    func_001092E0(p, 0);
    func_001094F0(p);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    p2.x = pos.x;
    p2.y = pos.y;
    p2.z = pos.z;
    func_00108EF0(m, &scale, &s->rot, &p2);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    ro = s->outer;
    ri = s->inner;
    for (k = 0; k < 18; k++) {
        if (k == 0) {
            t = s->start + a;
            quad[0].x = ro * func_00108030(o->xD8, t, 1);
            quad[0].z = ro * func_00108030(o->xD8, t, 0);
            quad[2].x = ri * func_00108030(o->xD8, t, 1);
            quad[2].z = ri * func_00108030(o->xD8, t, 0);
            t = a + (s->start + 20);
            quad[1].x = ro * func_00108030(o->xD8, t, 1);
            quad[1].z = ro * func_00108030(o->xD8, t, 0);
            quad[3].x = ri * func_00108030(o->xD8, t, 1);
            quad[3].z = ri * func_00108030(o->xD8, t, 0);
        } else {
            quad[0] = quad[1];
            quad[2] = quad[3];
            t = a + (s->start + 20);
            quad[1].x = ro * func_00108030(o->xD8, t, 1);
            quad[1].z = ro * func_00108030(o->xD8, t, 0);
            quad[3].x = ri * func_00108030(o->xD8, t, 1);
            quad[3].z = ri * func_00108030(o->xD8, t, 0);
        }
        if (mode == 0) {
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                func_002075F0(p, o->ot, (u32)depth[0]);
            }
        } else if (mode == 1) {
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                func_00109380(p, 1);
                func_002075F0(p, o->ot, 0);
            }
        } else {
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                func_002075F0(p, o->ot, -1);
            }
        }
        a += 20;
    }
}

/* OVL_WARM */

/* shape b119:01E00D30, 199 insns, 3 copies: draws one sprite at a given position plus a tenth of an offset, turned by
   the sprite's rotation; blend from flags >> 4, depth mode flags & 0xF (projected or far). Texture corners by
   the module helper (shape b003:01E00080). */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b119_01E00D30;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Rgbaq_b119_01E00D30 c;
    struct {
        u64 tc;
        u64 x : 16, y : 16, z : 24, f : 8;
    } v[4];
    u8 tail[0x38];
} Pkt_b119_01E00D30;

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    Rect_b003_01E00080 rect;
    u8 pad9C[0x22];
    s16 mode;
    u8 padC0[0x18];
    u8 xD8[1];
} Obj_b119_01E00D30;

typedef struct {
    u8 pad0[8];
    s16 dx, dy, dz;
    u8 padE[2];
    Vec4f rot;
    u8 pad20[8];
    u8 col[4];
    u8 pad2C[0xC];
    s16 size;
} Spr_b119_01E00D30;

static void func_01E00D30_b119(Obj_b119_01E00D30 *o, Spr_b119_01E00D30 *s, s32 flags, Vec4f pos) {
    extern Rgbaq_b119_01E00D30 func_00107740(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern s32 func_00109100(void *, void *, s32, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f p2;
    Vec4f scale;
    f32 depth[4];
    f32 m[16];
    s32 rot[4];
    Pkt_b119_01E00D30 pkt __attribute__((aligned(8)));
    Pkt_b119_01E00D30 *p;
    f32 dx;
    f32 dy;
    f32 dz;

    p = (Pkt_b119_01E00D30 *)(s32)&pkt;
    p->count = 0x24;
    p->tag = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad = 0;
    p->count |= 0x800;
    if ((flags >> 4) == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x48);
    } else if ((flags >> 4) == 1) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x44);
    } else {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    }
    p->c = func_00107740(s->col);
    func_01E00080_b119((Pk_b003_01E00080 *)p, &o->rect, o->mode);
    func_00208700(p, o->texture, 1);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    dx = s->dx;
    dy = s->dy;
    dz = s->dz;
    dx /= 10.0f;
    dy /= 10.0f;
    dz /= 10.0f;
    p2.x = pos.x + dx;
    p2.y = pos.y + dy;
    p2.z = pos.z + dz;
    func_00108EF0(m, &scale, rot, &p2);
    func_00108CE0(quad, s->size, s->size);
    func_00109100(quad, &s->rot, 2, o->xD8);
    if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
        if ((flags & 0xF) == 0) {
            func_002075F0(p, o->ot, (u32)depth[0]);
        } else if ((flags & 0xF) == 1) {
            p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
            func_002075F0(p, o->ot, 0);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b119", func_01E01050_b119);

INCLUDE_ASM("asm/nonmatchings/mod/b119", func_01E01800_b119);

INCLUDE_ASM("asm/nonmatchings/mod/b119", func_01E021F0_b119);

/* shape b119:01E024C0, 131 insns: a rising spark in a random colour (blue, red or yellow): keeps its start height in
   0xA, turn 0..359, rise 2..11, f8 0..34, hold 3..4; alpha grows by 0x2A (below 0x80) while held, then fades by 0xD
   (ends below 0xF); after the first tick it jitters y by -1..1 and rises */

typedef struct {
    u8 pad0[2];
    s16 y;
    u8 pad4[2];
    s16 hold;
    s16 f8;
    s16 h0;
    s16 fC;
    s16 rise;
    u8 pad10[0x18];
    u8 col[4];
    u8 pad2C[4];
    s16 h;
    s16 t;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 ang;
} Fx_b119_01E024C0;

static s32 func_01E024C0_b119(s32 arg0, Fx_b119_01E024C0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    s16 c;

    if (o->mode == 1) {
        o->f38 = 0x28;
        o->f34 = 0;
        c = func_0019A5C8() % 3;
        if (c == 0) {
            func_001076F0(o->col, 0x20, 0x20, 0x80);
        } else if (c == 1) {
            func_001076F0(o->col, 0x80, 0x20, 0x20);
        } else if (c == 2) {
            func_001076F0(o->col, 0x80, 0x80, 0x20);
        }
        o->h0 = o->h;
        o->h = 0;
        o->ang = func_0019A5C8() % 360;
        o->rise = func_0019A5C8() % 10 + 2;
        o->f8 = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 2 + 3;
        o->fC = 0;
        o->mode = 2;
    }
    if (o->t < o->hold) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x2A;
        }
    } else if (o->col[3] > 0xE) {
        o->col[3] -= 0xD;
    } else {
        o->mode = 0;
    }
    if (o->t != 0) {
        o->y += (s16)(func_0019A5C8() % 2);
    }
    if (o->t != 0) {
        o->h += o->rise;
    }
    o->t++;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b119", func_01E026D0_b119);

INCLUDE_ASM("asm/nonmatchings/mod/b119", func_01E02990_b119);

INCLUDE_ASM("asm/nonmatchings/mod/b119", func_01E02BE0_b119);

/* shape b119:01E02F60, 98 insns: a long coloured glow: frame 280, red, green or blue by its kind, random angle; alpha flickers
   0x80/0x70 by frame parity until frame 230, then down by 9 until it ends */

typedef struct {
    u8 pad0[0x28];
    u8 c0[4];
    u8 c1[4];
    s16 kind;
    s16 t;
    u8 pad34[2];
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b119_01E02F60;

static s32 func_01E02F60_b119(void *arg0, Obj_b119_01E02F60 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 0x118;
        if (o->kind == 0) {
            func_001076F0(o->c0, 0x80, 0x10, 0x10);
            func_001076F0(o->c1, 0x80, 0x10, 0x10);
        } else if (o->kind == 1) {
            func_001076F0(o->c0, 0x10, 0x80, 0x10);
            func_001076F0(o->c1, 0x10, 0x80, 0x10);
        } else if (o->kind == 2) {
            func_001076F0(o->c0, 0x10, 0x10, 0x80);
            func_001076F0(o->c1, 0x10, 0x10, 0x80);
        }
        o->ang = func_0019A5C8() % 360;
        o->state = 2;
        o->c0[3] = 0x80;
        o->c1[3] = 0;
    }
    if (o->t < 0xE6) {
        if (o->t % 2 == 1) {
            o->c0[3] = 0x80;
        } else {
            o->c0[3] = 0x70;
        }
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    o->t++;
    return 0;
}

/* shape b119:01E030F0, 106 insns: on start 0x38 = 50, both colours red, green or blue by the kind 0x30 (0..2), random
   0x3A, alpha 0x80 and second alpha 0; alpha flickers 0x80 / 0xC0 for 260 ticks, then fades by 9 and stops; 0x38 counts
   down while it fades; func_00205C40 on the rotation at 0x10, which advances 0x4000 */

typedef struct {
    u8 pad0[0x10];
    s32 rot[4];
    u8 pad20[8];
    u8 col[4];
    u8 col2[4];
    s16 kind;
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b119_01E030F0;

static s32 func_01E030F0_b119(s32 arg0, Fx_b119_01E030F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 50;
        if (o->kind == 0) {
            func_001076F0(o->col, 0xFF, 0x80, 0x80);
            func_001076F0(o->col2, 0xFF, 0x80, 0x80);
        } else if (o->kind == 1) {
            func_001076F0(o->col, 0x80, 0xFF, 0x80);
            func_001076F0(o->col2, 0x80, 0xFF, 0x80);
        } else if (o->kind == 2) {
            func_001076F0(o->col, 0x80, 0x80, 0xFF);
            func_001076F0(o->col2, 0x80, 0x80, 0xFF);
        }
        o->f3A = func_0019A5C8() % 360;
        o->mode = 2;
        o->col[3] = 0x80;
        o->col2[3] = 0;
    }
    if (o->tick < 0x104) {
        if (o->tick % 2 == 1) {
            o->col[3] = 0xC0;
        } else {
            o->col[3] = 0x80;
        }
    } else {
        if (o->col[3] > 0xA) {
            o->col[3] -= 9;
        } else {
            o->mode = 0;
        }
        o->f38--;
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->tick++;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b119", func_01E032A0_b119);

/* shape b119:01E03510, 96 insns: on start 0x38 = 60, variant 5, colour (0x80, 0x60, 0x60), 0x30 toggles between 0 and
   a random angle, random heading 0x3A; alpha 0x80 for 7 ticks, then fades by 15 and stops; while 0x30 is set it
   drifts 10 along the heading (0x8 by the sine, 0xC by the cosine of the game table 0x4420) */

typedef struct {
    u8 pad0[0x4420];
    u8 trig[1];
} Game_b119_01E03510;

typedef struct {
    u8 pad0[8];
    s16 x;
    u8 padA[2];
    s16 z;
    u8 padE[0x1A];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 heading;
} Fx_b119_01E03510;

static s32 func_01E03510_b119(Game_b119_01E03510 *g, Fx_b119_01E03510 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    if (o->mode == 1) {
        o->f38 = 60;
        o->f34 = 5;
        func_001076F0(o->col, 0x80, 0x60, 0x60);
        if (o->f30 == 0) {
            o->f30 = func_0019A5C8() % 360;
        } else {
            o->f30 = 0;
        }
        o->heading = func_0019A5C8() % 360;
        o->mode = 2;
    }
    if (o->tick < 7) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 15;
    } else {
        o->mode = 0;
    }
    if (o->f30 != 0) {
        o->x = o->x + 10.0f * func_00108030(g->trig, o->heading, 0);
        o->z = o->z + 10.0f * func_00108030(g->trig, o->heading, 1);
    }
    o->tick++;
    return 0;
}

/* shape b119:01E03690, 93 insns: a grey spark: frame 200, start height 130..629 (old one kept), random angle, rise 30..59, width
   0..34, hold 2..3, side 0..1; alpha up by 42 to 0x80 until the hold, then down by 13 until it ends */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 w;
    s16 y0;
    s16 side;
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
} Obj_b119_01E03690;

static s32 func_01E03690_b119(void *arg0, Obj_b119_01E03690 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 0xC8;
        o->sub = 0;
        func_0019A5C8();
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
        o->y0 = o->y;
        o->y = func_0019A5C8() % 500 + 0x82;
        o->ang = func_0019A5C8() % 360;
        o->step = func_0019A5C8() % 30 + 0x1E;
        o->w = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 2 + 2;
        o->side = func_0019A5C8() % 2;
        o->state = 2;
    }
    if (o->t < o->hold) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x2A;
        }
    } else if (o->c0[3] > 0xE) {
        o->c0[3] -= 0xD;
    } else {
        o->state = 0;
    }
    o->t++;
    return 0;
}

/* shape b119:01E03810, 124 insns: a drifting particle: on start a random life 400..599, angle 0..359, fall speed 20..39,
   frame 0..34, fade-in time 6..11 and parity; alpha up by 42 to 0x80 during the fade-in, then down by 13 until it ends;
   the frame counter steps on odd frames and wraps at 8; it ends when the life runs out */

typedef struct {
    u8 pad0[6];
    s16 fadein;
    s16 frame;
    s16 oldlife;
    s16 parity;
    s16 fall;
    u8 pad10[0x18];
    u8 c[4];
    u8 pad2C[4];
    s16 life;
    s16 t;
    s16 step;
    s16 state;
    s16 f38;
    s16 angle;
} Obj_b119_01E03810;

static s32 func_01E03810_b119(void *g, Obj_b119_01E03810 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_0019A5C8(void);

    if (o->state == 1) {
        o->f38 = 300;
        o->step = 0;
        func_0019A5C8();
        func_001076F0(o->c, 0x80, 0x80, 0x80);
        o->oldlife = o->life;
        o->life = func_0019A5C8() % 200 + 400;
        o->angle = func_0019A5C8() % 360;
        o->fall = func_0019A5C8() % 20 + 20;
        o->frame = func_0019A5C8() % 35;
        o->fadein = func_0019A5C8() % 6 + 6;
        o->parity = func_0019A5C8() % 2;
        o->state = 2;
    }
    if (o->t < o->fadein) {
        if (o->c[3] < 0x80) {
            o->c[3] += 0x2A;
        }
    } else if (o->c[3] > 0xE) {
        o->c[3] -= 0xD;
    } else {
        o->state = 0;
    }
    if (o->t % 2 == 1) {
        o->step++;
    }
    if (o->step > 7) {
        o->step = 0;
    }
    if (o->t != 0 && o->life < 0) {
        o->state = 0;
    }
    if (o->t != 0) {
        o->life -= o->fall;
    }
    o->t++;
    return 0;
}

/* shape b119:01E03A00, 130 insns: grey puff (b582:01E02D30 family): random spin words, turn, size 25..74, f38 a third of
   it plus 0..19, fE 0..9; alpha grows by 10 (below 0x80) until scene count 270, then fades by 9 (ends below 11);
   spins 0x4000 a tick */

typedef struct {
    u8 pad0[8];
    s16 f8;
    s16 fA;
    u8 padC[2];
    s16 fE;
    s32 i10;
    s32 i14;
    s32 i18;
    u8 pad1C[0xC];
    u8 c0[4];
    u8 c1[4];
    s16 kind;
    s16 t;
    u8 pad34[2];
    s16 mode;
    s16 f38;
    s16 ang;
} Obj_b119_01E03A00;

typedef struct {
    u8 pad0[0x3F1C];
    s16 count;
} Scene_b119_01E03A00;

static s32 func_01E03A00_b119(Scene_b119_01E03A00 *g, Obj_b119_01E03A00 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = func_0019A5C8() % 70 + 3;
        func_001076F0(o->c0, 0x60, 0x60, 0x60);
        func_001076F0(o->c1, 0x60, 0x60, 0x60);
        o->i10 = func_0019A5C8() % 30 + 5;
        o->i14 = func_0019A5C8() % 10 - 5;
        o->i18 = func_0019A5C8() % 30 + 5;
        o->ang = func_0019A5C8() % 360;
        o->mode = 2;
        o->fA = func_0019A5C8() % 50 + 25;
        o->f38 = o->fA / 3;
        o->f38 += (s16)(func_0019A5C8() % 20);
        o->fE = func_0019A5C8() % 10;
    }
    if (g->count < 0x10E) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 10;
        }
    } else if (o->c0[3] > 10) {
        o->c0[3] -= 9;
    } else {
        o->mode = 0;
    }
    func_00205C40((s32)&o->i10);
    o->i10 += 0x4000;
    o->t++;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b119", func_01E03C10_b119);

/* shape b119:01E03ED0, 138 insns: b757:01E029A0-family scene light in (128, 8, 0, 0), placed past joint B (twice the
   A-to-B step from A); for 300 ticks it pulses by 0.1 between 0.1 and 1, then dims by 0.1 and ends; handed to
   func_001F6C10 while alive; ends when 0x3ED0 is 1 */

typedef struct {
    f32 c[4];
    Vec4f pos;
    f32 fC0;
    f32 fC4;
    f32 level;
} Light_b119_01E03ED0;

typedef struct {
    u8 pad0[0x34A0];
    Light_b119_01E03ED0 light;
    u8 pad34CC[0xA04];
    s32 flag;
    u8 pad3ED4[0x32];
    s16 ja;
    s16 jb;
} Scene_b119_01E03ED0;

typedef struct {
    u8 pad0[0x30];
    s16 dir;
    s16 t;
    u8 pad34[2];
    s16 mode;
} Fx_b119_01E03ED0;

static s32 func_01E03ED0_b119(Scene_b119_01E03ED0 *g, Fx_b119_01E03ED0 *o) {
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F6C10(void *);
    Vec4f v[2];
    f32 dx;
    f32 dy;
    f32 dz;

    func_001F5620(func_001F53A0(), g->ja, &v[0]);
    func_001F5620(func_001F53A0(), g->jb, &v[1]);
    if (o->mode == 1) {
        g->light.c[0] = 128.0f;
        g->light.c[1] = 8.0f;
        g->light.c[2] = 0.0f;
        g->light.c[3] = 0.0f;
        g->light.fC0 = 0.0f;
        g->light.fC4 = 120.0f;
        g->light.level = 0.0f;
        o->mode = 2;
        o->dir = 0;
    }
    dx = v[1].x - v[0].x;
    dy = v[1].y - v[0].y;
    dz = v[1].z - v[0].z;
    g->light.pos.x = v[0].x + 2.0f * dx;
    g->light.pos.y = v[0].y + 2.0f * dy;
    g->light.pos.z = v[0].z + 2.0f * dz;
    if (o->t < 0x12C) {
        if (o->dir == 0) {
            if (g->light.level < 1.0f) {
                g->light.level += 0.1f;
            } else {
                o->dir = 1;
            }
        } else if (g->light.level > 0.1f) {
            g->light.level -= 0.1f;
        } else {
            o->dir = 0;
        }
    } else if (g->light.level > 0.1f) {
        g->light.level -= 0.1f;
    } else {
        o->mode = 0;
    }
    if (o->mode == 0) {
        func_001F6C10(NULL);
    } else {
        func_001F6C10(&g->light);
    }
    if (g->flag == 1) {
        o->mode = 0;
    }
    o->t++;
    return 0;
}

/* shape b119:01E04100, 47 insns: b718:01E03D10 family: a volume eased by 10 toward 0x30 once the scene state passes 30 (else toward 0x80); full volume at state 1 */

typedef struct {
    u8 pad[0x3ED0];
    s32 state;
} Game_b119_01E04100;

typedef struct {
    u8 pad[0x30];
    s16 vol;
    u8 pad32[4];
    s16 mode;
} Fade_b119_01E04100;

static s32 func_01E04100_b119(Game_b119_01E04100 *g, Fade_b119_01E04100 *o) {
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
        func_001F6D00(0x80);
    } else {
        func_001F6D00((u8)o->vol);
    }
    return 0;
}

/* shape b119:01E041C0, 31 insns: calls func_001F7170(2, 0, &a, &b, 0) with the module's two floats, stops the
   effect after 10 ticks */

typedef struct {
    u8 pad0[0x32];
    s16 tick;
    u8 pad34[2];
    s16 mode;
} Fx_b119_01E041C0;

typedef struct {
    f32 v;
} F1_b119_01E041C0;

extern F1_b119_01E041C0 D_01E05980_b119;
extern F1_b119_01E041C0 D_01E05988_b119;

static s32 func_01E041C0_b119(s32 arg0, Fx_b119_01E041C0 *o) {
    extern void func_001F7170(s32, s32, void *, void *, s32);
    F1_b119_01E041C0 a;
    F1_b119_01E041C0 b;

    a = D_01E05980_b119;
    b = D_01E05988_b119;
    func_001F7170(2, 0, &a, &b, 0);
    if (o->tick >= 10) {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b119", func_01E04240_b119);

/* shape b119:01E05220, 72 insns: twin of b046:01E03E20: take the first free slot of the 200-slot pool, clear it, give
   it the scene's colour twice, the scene matrix, the scene's value 0x3F14 and the two arguments; returns 1 if a
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
} Slot_b119_01E05220;

typedef struct {
    u8 pad[0x250];
    u8 m[0x50];
    Slot_b119_01E05220 s[200];
    u8 pad34A0[0xA34];
    u8 r, g, b, a;
    u8 pad3ED8[0x3C];
    s16 v;
} Pool_b119_01E05220;

static s32 func_01E05220_b119(Pool_b119_01E05220 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b119_01E05220 *s = NULL;
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
        s->b = b;
        s->a = a;
    } else {
        ret = 0;
    }
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/mod/b119", func_01E05340_b119);

INCLUDE_ASM("asm/nonmatchings/mod/b119", func_01E056A0_b119);

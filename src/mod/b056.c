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

static void func_01E00080_b056(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

/* shape b056:01E00920, 240 insns, 5 copies: draws a row of small camera-facing sprites (count, or 20) at a given position,
   each shaken by a per-entry table offset that grows along the row, turned by an extra axis; one texture
   corner mode for the whole row (module helper, shape b003:01E00080). */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b056_01E00920;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Rgbaq_b056_01E00920 c;
    struct {
        u64 tc;
        u64 x : 16, y : 16, z : 24, f : 8;
    } v[4];
    u8 tail[0x38];
} Pkt_b056_01E00920;

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    Rect_b003_01E00080 rect;
    u8 pad9C[0x1C];
    s16 count;
    u8 padBA[4];
    s16 mode;
    u8 padC0[0x18];
    u8 xD8[1];
} Obj_b056_01E00920;

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 off;
    u8 padA[0x1E];
    u8 col[4];
    u8 pad2C[4];
    s16 w30;
    u8 pad32[6];
    s16 size;
    s16 axis;
} Spr_b056_01E00920;

static void func_01E00920_b056(Obj_b056_01E00920 *o, Spr_b056_01E00920 *s, s8 *tbl, Vec4f pos) {
    extern Rgbaq_b056_01E00920 func_00107740(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern s32 func_00109100(void *, void *, s32, void *);
    extern void func_00108950(void *, void *, s32, void *);
    extern void func_00107070(void *, s32, f32);
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
    Pkt_b056_01E00920 pkt __attribute__((aligned(8)));
    s8 *j;
    s32 h;
    s16 i;
    s16 n;
    Pkt_b056_01E00920 *p;

    func_00207500();
    p = (Pkt_b056_01E00920 *)(s32)&pkt;
    p->count = 0x24;
    p->tag = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad = 0;
    p->count |= 0x800;
    func_002086D0(p, ((u64)0x80 << 32) | 0x48);
    pkt.c.q = 0;
    pkt.v[0].f = 0;
    pkt.v[1].f = 0;
    pkt.v[2].f = 0;
    pkt.v[3].f = 0;
    pkt.c = func_00107740(s->col);
    func_01E00080_b056((Pk_b003_01E00080 *)p, &o->rect, o->mode);
    func_00208700(p, o->texture, 1);
    if (o->count != 0) {
        n = o->count;
    } else {
        n = 20;
    }
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    p2.x = pos.x;
    p2.y = pos.y;
    p2.z = pos.z;
    func_00108EF0(m, &scale, NULL, &p2);
    rot[1] = rot[1] / 180;
    rot[1] = -rot[1];
    rot[0] = rot[0] / 180;
    rot[0] = -rot[0];
    ax[2] = s->axis;
    for (i = 0; i < n; i++) {
        func_00108CE0(quad, s->size, s->size);
        func_00109100(quad, rot, 0, o->xD8);
        func_00109100(quad, rot, 1, o->xD8);
        j = tbl + i;
        h = i >> 1;
        e.x = j[s->off] / 20.0f * (s->w30 + h);
        e.y = j[s->off + 100] / 20.0f * (s->w30 + h);
        e.z = j[s->off + 180] / 20.0f * (s->w30 + h);
        func_00108950(&e, ax, 2, o->xD8);
        func_00107070(quad, 0, e.x);
        func_00107070(quad, 1, e.y);
        func_00107070(quad, 2, e.z);
        if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
            func_002075F0(p, o->ot, (u32)depth[0]);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b056", func_01E00CE0_b056);

INCLUDE_ASM("asm/nonmatchings/mod/b056", func_01E012E0_b056);

/* shape b056:01E01660, 37 insns: pulse: alpha grows by 10 up to 0xA0, then (phase 1) fades by 10; at the bottom it rises
   again, clearing 0x36 once the game value at 0x3996 passes 0x15E; colour (0x5F, 0x3F, 0x3F) */

typedef struct {
    u8 pad0[0x3996];
    s16 v;
} Game_b056_01E01660;

typedef struct {
    u8 pad0[0x28];
    u8 col[4];
    u8 pad2C[4];
    s16 phase;
    u8 pad32[4];
    s16 f36;
} Fx_b056_01E01660;

static s32 func_01E01660_b056(Game_b056_01E01660 *g, Fx_b056_01E01660 *o) {
    if (o->phase == 0) {
        if (o->col[3] < 0xA0) {
            o->col[3] += 10;
        } else {
            o->phase = 1;
        }
    } else if (o->col[3] > 0xB) {
        o->col[3] -= 10;
    } else {
        if (g->v > 0x15E) {
            o->f36 = 0;
        }
        o->phase = 0;
    }
    func_001076F0(o->col, 0x5F, 0x3F, 0x3F);
    return 0;
}

/* shape b056:01E01700, 104 insns: a faint grey drifting haze: frame 150; sub-frame steps up to 7 every fourth scene tick; alpha up
   by 2 to 0x30 for 20 frames, then down by 4 until it ends; drifts 5 against the scene wind and bobs 2, its angle going 10 */

typedef struct {
    u8 pad0[0x3988];
    s16 wind;
    u8 pad398A[0xC];
    s16 tick;
    u8 pad3998[0x100];
    u8 sin[1];
} Game_b056_01E01700;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    u8 pad6[0x22];
    u8 c0[4];
    u8 pad2C[6];
    s16 t;
    s16 sub;
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b056_01E01700;

static s32 func_01E01700_b056(Game_b056_01E01700 *g, Obj_b056_01E01700 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s16 func_001A22C0(f32);
    s16 wind;

    o->h38 = 0x96;
    if (g->tick % 4 == 1) {
        if (o->sub < 7) {
            o->sub++;
        }
    }
    func_001076F0(o->c0, 0x3F, 0x3F, 0x3F);
    if (o->t < 0x14) {
        if (o->c0[3] < 0x30) {
            o->c0[3] += 2;
        }
    } else if (o->c0[3] > 5) {
        o->c0[3] -= 4;
    } else {
        o->state = 0;
    }
    o->t++;
    wind = g->wind;
    o->x = func_001A22C0(o->x - 5.0f * func_00108030(g->sin, wind, 0));
    o->y = func_001A22C0(o->y + 2.0f * func_00108030(g->sin, o->ang, 1));
    o->z = func_001A22C0(o->z - 5.0f * func_00108030(g->sin, wind, 1));
    o->ang += 0xA;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b056", func_01E018A0_b056);

/* shape b056:01E01AF0, 55 insns: a grey ring that follows the game's point (x, 30, z): set up once at full alpha;
   grows by 5 up to 100, turns 12 a frame, fades by 16 after 30 frames */

typedef struct {
    u8 pad0[0x3760];
    f32 x;
    f32 y;
    f32 z;
} Game_b056_01E01AF0;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    u8 pad6[0x22];
    u8 c0[4];
    u8 pad2C[0xA];
    s16 state;
    s16 size;
    s16 ang;
} Obj_b056_01E01AF0;

static s32 func_01E01AF0_b056(Game_b056_01E01AF0 *g, Obj_b056_01E01AF0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    func_001076F0(o->c0, 0x40, 0x40, 0x40);
    o->x = g->x;
    o->y = 0x1E;
    o->z = g->z;
    if (o->state == 1) {
        o->size = 0;
        o->state = 2;
        o->c0[3] = 0x80;
    }
    if (o->size > 0x1E) {
        if (o->c0[3] > 0x10) {
            o->c0[3] -= 0x10;
        } else {
            o->state = 0;
        }
    }
    if (o->size < 0x64) {
        o->size += 5;
    }
    o->ang += 0xC;
    return 0;
}

/* shape b056:01E01BD0, 106 insns: a flickering olive mote (size 13 bright / 9 dim on the scene's odd/even ticks) pushed back 5 a tick against the scene heading and bobbing 2 on its own angle (turning 10; sine table ctx+0x3A98): in by 5 up to 0x70 for 20 ticks, then out by 13 and ends */

typedef struct {
    s16 h0;
    s16 h2;
    s16 h4;
    u8 pad6[0x22];
    u8 col[4];
    u8 col2[4];
    s16 h30;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
    s16 ang;
} Glow_b056_01E01BD0;

typedef struct {
    u8 pad[0x3988];
    s16 head;
    u8 pad398A[0xC];
    s16 tick;
    u8 pad3998[0x100];
    u8 sin[1];
} Game_b056_01E01BD0;

static s32 func_01E01BD0_b056(Game_b056_01E01BD0 *g, Glow_b056_01E01BD0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s16 func_001A22C0(f32);
    s16 a;

    if (g->tick % 2 == 1) {
        func_001076F0(o->col, 0x40, 0x40, 0);
        o->f38 = 13;
    } else {
        func_001076F0(o->col, 0x20, 0x20, 0);
        o->f38 = 9;
    }
    if (o->tick < 20) {
        if (o->col[3] < 0x70) {
            o->col[3] += 5;
        }
    } else if (o->col[3] > 14) {
        o->col[3] -= 13;
    } else {
        o->mode = 0;
    }
    o->tick++;
    a = g->head;
    o->h0 = func_001A22C0(o->h0 - 5.0f * func_00108030(g->sin, a, 0));
    o->h2 = func_001A22C0(o->h2 + 2.0f * func_00108030(g->sin, o->ang, 1));
    o->h4 = func_001A22C0(o->h4 - 5.0f * func_00108030(g->sin, a, 1));
    o->ang += 10;
    return 0;
}

/* shape b056:01E01D80, 44 insns: a yellow glow: fades in by 0x16 up to 0x70 for 5 ticks, then out by 13 while growing 7 a tick; turns 10 a tick */

typedef struct {
    u8 pad0[0x28];
    u8 col[4];
    u8 pad2C[6];
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 size;
    s16 ang;
} Glow_b056_01E01D80;

static s32 func_01E01D80_b056(s32 arg0, Glow_b056_01E01D80 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    func_001076F0(o->col, 0x40, 0x40, 0);
    o->size = 15;
    if (o->tick < 5) {
        if (o->col[3] < 0x70) {
            o->col[3] += 0x16;
        }
    } else {
        if (o->col[3] > 14) {
            o->col[3] -= 13;
        } else {
            o->mode = 0;
        }
        o->size += 7;
    }
    o->tick++;
    o->ang += 10;
    return 0;
}

/* shape b056:01E01E30, 99 insns: a mover that starts 20 under the scene camera (func_001F53A0 view) and slides 1/110 of the way toward the other view (func_001F5380) each tick on x/z, ending when within 3 on z; every 4th tick it raises the scene value at ctx+0x3924 by 1 up to 20 */

typedef struct {
    f32 x, y, z, w;
} V4_b056_01E01E30;

typedef struct {
    u8 pad0[0x32];
    s16 tick;
    u8 pad34[2];
    s16 mode;
} Obj_b056_01E01E30;

typedef struct {
    u8 pad[0x38E0];
    f32 x, y, z;
    u8 pad38EC[0x38];
    f32 v;
} Game_b056_01E01E30;

static s32 func_01E01E30_b056(Game_b056_01E01E30 *g, Obj_b056_01E01E30 *o) {
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5F90(s32, void *);
    extern f32 func_001A6C60(f32);
    V4_b056_01E01E30 a;
    V4_b056_01E01E30 b;
    V4_b056_01E01E30 *p;
    f32 d;

    func_001F5F90(func_001F53A0(), &a);
    func_001F5F90(func_001F5380(), p = &b);
    if (o->mode == 1) {
        g->x = a.x;
        g->y = a.y - 20.0f;
        g->z = a.z;
        o->mode = 2;
    }
    if (o->mode == 2) {
        g->x += (p->x - a.x) / 110.0f;
        g->z += (b.z - a.z) / 110.0f;
        d = b.z - g->z;
        if (func_001A6C60(d * d) < 3.0f) {
            o->mode = 3;
        }
        if (o->tick % 4 == 1) {
            if (g->v < 20.0f) {
                g->v += 1.0f;
            }
        }
    }
    o->tick++;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b056", func_01E01FC0_b056);

INCLUDE_ASM("asm/nonmatchings/mod/b056", func_01E021A0_b056);

INCLUDE_ASM("asm/nonmatchings/mod/b056", func_01E023E0_b056);

/* shape b056:01E02600, 93 insns: a grey drifting puff (b393:01E02610 shape): frame 8, random sub-frame 0..6, tilt and angle; full
   alpha for 7 frames, then down by 20 until it ends; drifts 11 along its angle and sinks 2 a frame */

typedef struct {
    u8 pad0[0x3A98];
    u8 trig[1];
} Game_b056_01E02600;

typedef struct {
    u8 pad0[8];
    s16 x;
    s16 y;
    s16 z;
    u8 padE[0x1A];
    u8 c0[4];
    u8 pad2C[4];
    s16 tilt;
    s16 t;
    s16 sub;
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b056_01E02600;

static s32 func_01E02600_b056(Game_b056_01E02600 *g, Obj_b056_01E02600 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    if (o->state == 1) {
        o->h38 = 8;
        o->sub = func_0019A5C8() % 7;
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
        o->tilt = func_0019A5C8() % 360;
        o->ang = func_0019A5C8() % 360;
        o->state = 2;
    }
    if (o->t < 7) {
        o->c0[3] = 0x80;
    } else if (o->c0[3] > 0x15) {
        o->c0[3] -= 0x14;
    } else {
        o->state = 0;
    }
    o->x = o->x + 11.0f * func_00108030(g->trig, o->ang, 0);
    o->y -= 2;
    o->z = o->z + 11.0f * func_00108030(g->trig, o->ang, 1);
    o->t++;
    return 0;
}

/* shape b056:01E02780, 66 insns: a dark spark at a random frame and two random angles (size 10): in by 38 up to 0xC0 for 5 ticks, then out by 23 growing 2 a tick, and ends */

typedef struct {
    u8 pad0[0x28];
    u8 col[4];
    u8 col2[4];
    s16 h30;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
    s16 ang;
} Glow_b056_01E02780;

static s32 func_01E02780_b056(s32 arg0, Glow_b056_01E02780 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 10;
        o->kind = func_0019A5C8() % 7;
        func_001076F0(o->col, 0xF0, 0xF0, 0xF0);
        o->h30 = func_0019A5C8() % 360;
        o->ang = func_0019A5C8() % 360;
        o->mode = 2;
    }
    if (o->tick < 5) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x26;
        }
    } else {
        if (o->col[3] > 0x18) {
            o->col[3] -= 0x17;
        } else {
            o->mode = 0;
        }
        o->f38 += 2;
    }
    o->tick++;
    return 0;
}

/* shape b056:01E02890, 117 insns: a pale high spark: frame 7..26, height 150..799, random angle turning 9 a frame, rise 65..124,
   width 0..29, hold 3..7; alpha up by 25 to 0x80 until the hold, then down by 20; sub-frame steps up to 6 and it drifts up
   1..4 a frame once started */

typedef struct {
    u8 pad0[2];
    s16 h2;
    u8 pad4[2];
    s16 hold;
    s16 w;
    u8 padA[4];
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
} Obj_b056_01E02890;

static s32 func_01E02890_b056(void *arg0, Obj_b056_01E02890 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = func_0019A5C8() % 20 + 7;
        func_001076F0(o->c0, 0xF0, 0xF0, 0xF0);
        o->y = func_0019A5C8() % 650 + 0x96;
        o->ang = func_0019A5C8() % 360;
        o->step = func_0019A5C8() % 60 + 0x41;
        o->w = func_0019A5C8() % 30;
        o->hold = func_0019A5C8() % 5 + 3;
        o->sub = 0;
        o->state = 2;
    }
    if (o->t < o->hold) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x19;
        }
    } else if (o->c0[3] > 0x15) {
        o->c0[3] -= 0x14;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        if (o->sub < 6) {
            o->sub++;
        }
    }
    if (o->t != 0) {
        o->h2 += (s16)(func_0019A5C8() % 4 + 1);
    }
    o->t++;
    o->ang += 9;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b056", func_01E02A70_b056);

/* shape b056:01E038A0, 89 insns: take a free node (0x19 of 0x98 bytes at 0x2D0), clear it, copy the scene vector
   0x250, 0x92/0x8E from 0x398C/0x3992, y = 0x3950 and 0x14 = y - 18, then push it on the scene's list (0x3920,
   prev 0x70 / next 0x74) with 0x94/0x96 = 1; returns 1 if a node was found */

typedef struct {
    f32 x, y, z, w;
} V4_b056_01E038A0;

typedef struct Node_b056_01E038A0 {
    u8 pad0[4];
    f32 y;
    u8 pad8[0xC];
    f32 f14;
    u8 pad18[0x18];
    V4_b056_01E038A0 pos;
    u8 pad40[0x30];
    struct Node_b056_01E038A0 *prev;
    struct Node_b056_01E038A0 *next;
    u8 pad78[0x10];
    s16 used;
    u8 pad8A[4];
    s16 f8E;
    u8 pad90[2];
    s16 f92;
    s16 f94;
    s16 f96;
} Node_b056_01E038A0;

typedef struct {
    u8 pad0[0x250];
    V4_b056_01E038A0 pos;
    u8 pad260[0x70];
    Node_b056_01E038A0 nodes[0x19];
    u8 pad11A8[0x3920 - 0x11A8];
    Node_b056_01E038A0 *head;
    u8 pad3924[0x2C];
    f32 y;
    u8 pad3954[0x38];
    s16 f398C;
    u8 pad398E[4];
    s16 f3992;
} Scene_b056_01E038A0;

static s32 func_01E038A0_b056(Scene_b056_01E038A0 *g) {
    extern void func_00195108();
    Node_b056_01E038A0 *s = NULL;
    s16 i;

    for (i = 0; i < 0x19; i++) {
        if (g->nodes[i].used == 0) {
            func_00195108(&g->nodes[i], 0x98);
            g->nodes[i].used = 1;
            s = &g->nodes[i];
            i = 0x19;
        }
    }
    if (s != NULL) {
        s->pos = g->pos;
        s->f92 = g->f398C;
        s->prev = g->head;
        s->f8E = g->f3992;
        if (s->prev == NULL) {
            s->y = g->y;
            s->f14 = s->y - 18.0f;
        } else {
            s->y = g->y;
            s->f14 = s->y - 18.0f;
        }
        s->prev = g->head;
        if (s->prev != NULL) {
            s->prev->next = s;
        }
        s->f94 = 1;
        s->f96 = 1;
        g->head = s;
        return 1;
    }
    return 0;
}

/* shape b056:01E03A10, 74 insns: twin of b046:01E03E20: take the first free slot of the 150-slot pool, clear it,
   give it the scene's colour twice, the scene matrix, the scene's value 0x3992 and 0x398C and the two arguments; returns 1 if a
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
} Slot_b056_01E03A10;

typedef struct {
    u8 pad[0x250];
    u8 m[0xF58];
    Slot_b056_01E03A10 s[150];
    u8 pad3728[0x1EC];
    u8 r, g, b, a;
    u8 pad3918[0x74];
    s16 w;
    u8 pad398E[0x4];
    s16 v;
} Pool_b056_01E03A10;

static s32 func_01E03A10_b056(Pool_b056_01E03A10 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b056_01E03A10 *s = NULL;
    s16 i;
    s32 ret;

    for (i = 0; i < 150; i++) {
        if (o->s[i].used == 0) {
            func_00195108(&o->s[i], 0x40);
            o->s[i].used = 1;
            s = &o->s[i];
            i = 150;
        }
    }
    if (s != NULL) {
        func_001076F0(s->c0, o->r, o->g, o->b);
        s->c0[3] = o->a;
        func_001076F0(s->c1, o->r, o->g, o->b);
        s->c1[3] = o->a;
        func_00106AB0(s, o->m, 0);
        ret = 1;
        s->w = o->w;
        s->v = o->v;
        s->b = b;
        s->a = a;
    } else {
        ret = 0;
    }
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/mod/b056", func_01E03B40_b056);

INCLUDE_ASM("asm/nonmatchings/mod/b056", func_01E041D0_b056);

INCLUDE_ASM("asm/nonmatchings/mod/b056", func_01E04470_b056);

/* shape b056:01E047D0, 106 insns: b004:01E01860 family two-pass sprite draw (texture id 0x9B, scene texture at +0x2CC) placed at position + speed/10 in floats and scaled 0.1 */

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 dx, dy, dz;
    u8 padE[0x1A];
    u8 col[0xC];
    s16 h34;
    u8 pad36[2];
    s16 size;
} Fx_b056_01E047D0;

typedef struct {
    u8 pad0[0x2CC];
    s32 tex;
} Scene_b056_01E047D0;

static void func_01E047D0_b056(Scene_b056_01E047D0 *g, Fx_b056_01E047D0 *o, void *p, s32 lit) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern void func_00108F90(void *, void *, void *, s32);
    Vec4f quad[4];
    Vec4f pos;
    Vec4f sc;
    f32 f;
    f32 d;
    f32 rm[4];
    f32 m[16];
    s32 rot[4];
    s32 v;

    v = (s32)func_00207500();
    if (lit == 0) {
        func_00106080(rm, 0x9B, o->h34, rm);
        func_00109270(p, 0, 0);
        func_00107790(p, o->col, 0);
        func_00108500(p, rm, 0);
        func_00208700(p, g->tex, 1);
        return;
    }
    func_00205C40((s32)rot);
    d = o->dx;
    d = d / 10.0f;
    pos.x = o->x;
    pos.x += d;
    d = o->dy;
    d = d / 10.0f;
    pos.y = o->y;
    pos.y += d;
    d = o->dz;
    d = d / 10.0f;
    pos.z = o->z;
    pos.z += d;
    sc.x = 0.1f;
    sc.y = 0.1f;
    sc.z = 0.1f;
    func_00108EF0(m, &sc, rot, &pos);
    func_00108CE0(quad, o->size, o->size);
    func_00108F90(quad, p, m, v);
}

INCLUDE_ASM("asm/nonmatchings/mod/b056", func_01E04980_b056);

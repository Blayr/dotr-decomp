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

INCLUDE_ASM("asm/nonmatchings/mod/b056", func_01E01700_b056);

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

INCLUDE_ASM("asm/nonmatchings/mod/b056", func_01E01BD0_b056);

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

INCLUDE_ASM("asm/nonmatchings/mod/b056", func_01E01E30_b056);

INCLUDE_ASM("asm/nonmatchings/mod/b056", func_01E01FC0_b056);

INCLUDE_ASM("asm/nonmatchings/mod/b056", func_01E021A0_b056);

INCLUDE_ASM("asm/nonmatchings/mod/b056", func_01E023E0_b056);

INCLUDE_ASM("asm/nonmatchings/mod/b056", func_01E02600_b056);

INCLUDE_ASM("asm/nonmatchings/mod/b056", func_01E02780_b056);

INCLUDE_ASM("asm/nonmatchings/mod/b056", func_01E02890_b056);

INCLUDE_ASM("asm/nonmatchings/mod/b056", func_01E02A70_b056);

INCLUDE_ASM("asm/nonmatchings/mod/b056", func_01E038A0_b056);

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

INCLUDE_ASM("asm/nonmatchings/mod/b056", func_01E047D0_b056);

INCLUDE_ASM("asm/nonmatchings/mod/b056", func_01E04980_b056);

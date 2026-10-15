#include "common.h"

INCLUDE_ASM("asm/nonmatchings/mod/c017", func_01E00080_c017);

INCLUDE_ASM("asm/nonmatchings/mod/c017", func_01E006B0_c017);

INCLUDE_ASM("asm/nonmatchings/mod/c017", func_01E009E0_c017);

/* shape c017:01E00D50, 112 insns: a falling trail piece: drops 2 a tick to -50 then fades both colours by 16 and ends; its two screen heights are the scene scale (ctx+0x3914 / ctx+0x399E) x height - 40 (ends when negative); its turn eases by its speed; fades in by 8 while the scene value is under 13, out by 16 while the scene state is under 10; ends at state 2 */

typedef struct {
    u8 pad0[0x14];
    f32 y;
    u8 pad18[0xC];
    s32 w24;
    u8 pad28[0xC];
    f32 f34;
    u8 pad38[0x10];
    u8 col[4];
    u8 col2[4];
    s16 mode;
    u8 pad52[4];
    s16 h56;
    s16 h58;
} Obj_c017_01E00D50;

typedef struct {
    u8 pad[0x38DC];
    s32 state;
    u8 pad38E0[0x34];
    f32 scale;
    u8 pad3918[0x48];
    s16 val;
    u8 pad3962[0x3C];
    s16 div;
} Game_c017_01E00D50;

static s32 func_01E00D50_c017(Game_c017_01E00D50 *g, Obj_c017_01E00D50 *o) {
    extern s32 func_001A22C0(f32);
    f32 s;
    f32 d;

    d = g->div;
    if (o->y > -50.0f) {
        o->y -= 2.0f;
    } else {
        if (o->col[3] > 0x10) {
            o->col[3] -= 0x10;
        }
        if (o->col2[3] > 0x10) {
            o->col2[3] -= 0x10;
        } else {
            o->mode = 0;
        }
    }
    s = g->scale / d;
    o->h56 = func_001A22C0(s * o->y - 40.0f);
    if (o->h56 < 0) {
        o->mode = 0;
    }
    o->h58 = func_001A22C0(s * o->y - 40.0f);
    if (o->h58 < 0) {
        o->mode = 0;
    }
    o->w24 = func_001A22C0(o->w24 - o->f34);
    if (g->val < 13) {
        if (o->col[3] < 0x80) {
            o->col[3] += 8;
        }
        if (o->col2[3] < 0x80) {
            o->col2[3] += 8;
        }
    }
    if (g->state < 10) {
        if (o->col[3] > 0x10) {
            o->col[3] -= 0x10;
        }
        if (o->col2[3] > 0x10) {
            o->col2[3] -= 0x10;
        }
    }
    if (g->state == 2) {
        o->mode = 0;
    }
    return 0;
}

/* shape c017:01E00F10, 66 insns: sinks by its speed (0x34) down to -50, then both alphas fade by 0x10 (the second
   ends it); both grow by 8 (below 0x80) while the game step at 0x3960 is below 13; both fade by 0x10 while the
   counter at 0x38DC is below 10; the effect stops at counter 2 */

typedef struct {
    u8 pad0[0x38DC];
    s32 count;
    u8 pad38E0[0x80];
    s16 step;
} Game_c017_01E00F10;

typedef struct {
    u8 pad0[0x14];
    f32 y;
    u8 pad18[0x1C];
    f32 speed;
    u8 pad38[0x10];
    u8 col[4];
    u8 col2[4];
    s16 mode;
} Fx_c017_01E00F10;

static s32 func_01E00F10_c017(Game_c017_01E00F10 *g, Fx_c017_01E00F10 *o) {
    if (!(o->y <= -50.0f)) {
        o->y -= o->speed;
    } else {
        if (o->col[3] > 0x10) {
            o->col[3] -= 0x10;
        }
        if (o->col2[3] > 0x10) {
            o->col2[3] -= 0x10;
        } else {
            o->mode = 0;
        }
    }
    if (g->step < 0xD) {
        if (o->col[3] < 0x80) {
            o->col[3] += 8;
        }
        if (o->col2[3] < 0x80) {
            o->col2[3] += 8;
        }
    }
    if (g->count < 10) {
        if (o->col[3] > 0x10) {
            o->col[3] -= 0x10;
        }
        if (o->col2[3] > 0x10) {
            o->col2[3] -= 0x10;
        }
    }
    if (g->count == 2) {
        o->mode = 0;
    }
    return 0;
}

/* shape c017:01E01020, 40 insns: both alphas grow by 0x20 (below 0x80 and 0x60) while the game step at 0x3960 is
   below 8; both fade by 15 while the counter at 0x38DC is below 10; the effect stops below 3 */

typedef struct {
    u8 pad0[0x38DC];
    s32 count;
    u8 pad38E0[0x80];
    s16 step;
} Game_c017_01E01020;

typedef struct {
    u8 pad0[0x50];
    u8 col[4];
    u8 col2[4];
    s16 mode;
} Fx_c017_01E01020;

static s32 func_01E01020_c017(Game_c017_01E01020 *g, Fx_c017_01E01020 *o) {
    if (g->step < 8) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x20;
        }
        if (o->col2[3] < 0x60) {
            o->col2[3] += 0x20;
        }
    }
    if (g->count < 10) {
        if (o->col[3] > 0x10) {
            o->col[3] -= 15;
        }
        if (o->col2[3] > 0x10) {
            o->col2[3] -= 15;
        }
    }
    if (g->count < 3) {
        o->mode = 0;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/c017", func_01E010C0_c017);

INCLUDE_ASM("asm/nonmatchings/mod/c017", func_01E01400_c017);

INCLUDE_ASM("asm/nonmatchings/mod/c017", func_01E01610_c017);

/* shape c017:01E01840, 91 insns: take a free row (0x32 of 0x60 bytes at 0x261C, mark = index + 1), clear it, two
   colours from the scene colour 0x38E0 with alpha 0x80, copy the scene vector 0x180, 0x56/0x58 from the scene floats
   0x38F4/0x38F8, 0x52/0x5C/0x5A from 0x3952/0x395A/0x3956, f14 from 0x38FC, f34 random 16..2063, callback
   c017:01E025B0 and arg */

typedef struct {
    f32 x, y, z, w;
} V4_c017_01E01840;

typedef struct {
    V4_c017_01E01840 pos;
    u8 pad10[4];
    f32 f14;
    u8 pad18[0x1C];
    f32 f34;
    u8 pad38[8];
    void (*cb)(void);
    s32 arg;
    u8 c48[4];
    u8 c4C[4];
    s16 used;
    s16 f52;
    u8 pad54[2];
    s16 f56;
    s16 f58;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
} Row_c017_01E01840;

typedef struct {
    u8 pad0[0x180];
    V4_c017_01E01840 pos;
    u8 pad190[0x261C - 0x190];
    Row_c017_01E01840 rows[0x32];
    u8 pad38DC[4];
    u8 rgb[4];
    u8 pad38E4[0x10];
    f32 f38F4;
    f32 f38F8;
    f32 f38FC;
    u8 pad3900[0x52];
    s16 f3952;
    u8 pad3954[2];
    s16 f3956;
    u8 pad3958[2];
    s16 f395A;
} Scene_c017_01E01840;

static void func_01E01840_c017(Scene_c017_01E01840 *g, s32 arg) {
    extern void c017_01E025B0(void);
    extern void func_00195108();
    extern void func_001076F0(void *, s32, s32, s32);
    Row_c017_01E01840 *s = NULL;
    s32 i;

    for (i = 0; i < 0x32; i++) {
        if (g->rows[i].used == 0) {
            func_00195108(&g->rows[i], 0x60);
            g->rows[i].used = i + 1;
            s = &g->rows[i];
            i = 0x32;
        }
    }
    if (s != NULL) {
        func_001076F0(s->c48, g->rgb[0], g->rgb[1], g->rgb[2]);
        s->c48[3] = 0x80;
        func_001076F0(s->c4C, g->rgb[0], g->rgb[1], g->rgb[2]);
        s->c4C[3] = 0x80;
        s->pos = g->pos;
        s->f56 = g->f38F4;
        s->f58 = g->f38F8;
        s->f52 = g->f3952;
        s->f14 = g->f38FC;
        s->f5C = g->f395A;
        s->f34 = func_0019A5C8() % 0x800 + 0x10;
        s->f5A = g->f3956;
        s->cb = c017_01E025B0;
        s->arg = arg;
    }
}

/* shape c017:01E019B0, 82 insns: takes the first free of 50 effect slots (0x60 bytes, c017:01E01B00 family), marks it with its
   index + 1, colours both from the context at alpha 0x80, copies the context's point, frames, sizes and turn, and hooks
   c017:01E02790 with the given argument */

typedef struct {
    Vec4f pos;
    u8 pad10[4];
    f32 f14;
    u8 pad18[0x1C];
    f32 f34;
    u8 pad38[8];
    void (*cb)(void);
    s32 arg;
    u8 c48[4];
    u8 c4C[4];
    s16 used;
    s16 f52;
    u8 pad54[2];
    s16 w;
    s16 h;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
} Slot_c017_01E019B0;

typedef struct {
    u8 pad0[0x180];
    Vec4f pos;
    u8 pad190[0x261C - 0x190];
    Slot_c017_01E019B0 slots[0x32];
    u8 pad[0x38E0 - 0x261C - 0x32 * 0x60];
    u8 rgba[4];
    u8 pad38E4[0x10];
    f32 w;
    f32 h;
    f32 f38FC;
    u8 pad3900[8];
    f32 f3908;
    u8 pad390C[0x46];
    s16 f3952;
    u8 pad3954[2];
    s16 f3956;
    u8 pad3958[2];
    s16 f395A;
} Ctx_c017_01E019B0;

static void func_01E019B0_c017(Ctx_c017_01E019B0 *ctx, s32 arg) {
    extern void c017_01E02790(void);
    extern void func_001076F0();
    extern void func_00195108();
    s32 i;
    Slot_c017_01E019B0 *s = NULL;

    for (i = 0; i < 0x32; i++) {
        if (ctx->slots[i].used == 0) {
            s = &ctx->slots[i];
            func_00195108(s, 0x60);
            ctx->slots[i].used = i + 1;
            i = 0x32;
        }
    }
    if (s != NULL) {
        func_001076F0(s->c48, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        s->c48[3] = 0x80;
        func_001076F0(s->c4C, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        s->c4C[3] = 0x80;
        s->pos = ctx->pos;
        s->w = ctx->w;
        s->h = ctx->h;
        s->f52 = ctx->f3952;
        s->f14 = ctx->f38FC;
        s->f5C = ctx->f395A;
        s->f34 = ctx->f3908;
        s->f5A = ctx->f3956;
        s->cb = c017_01E02790;
        s->arg = arg;
    }
}

/* shape c017:01E01B00, 58 insns: takes the first free of 85 effect slots (0x6C bytes, b108:01E02FF0 family), marks it
   with its index + 1, colours both from the context at alpha 0, and hooks c017:01E02970 with the given argument */

typedef struct {
    u8 pad0[0x48];
    void (*cb)(void);
    s32 arg;
    u8 c50[4];
    u8 c54[4];
    s16 used;
    u8 pad5A[0x12];
} Slot_c017_01E01B00;

typedef struct {
    u8 pad0[0x240];
    Slot_c017_01E01B00 slots[0x55];
    u8 pad[0x38E0 - 0x240 - 0x55 * 0x6C];
    u8 rgba[4];
} Ctx_c017_01E01B00;

static void func_01E01B00_c017(Ctx_c017_01E01B00 *ctx, s32 arg) {
    extern void c017_01E02970(void);
    extern void func_001076F0();
    extern void func_00195108();
    s32 i;
    Slot_c017_01E01B00 *s = NULL;

    for (i = 0; i < 0x55; i++) {
        if (ctx->slots[i].used == 0) {
            s = &ctx->slots[i];
            func_00195108(s, 0x6C);
            ctx->slots[i].used = i + 1;
            i = 0x55;
        }
    }
    if (s != NULL) {
        func_001076F0(s->c50, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        s->c50[3] = 0;
        func_001076F0(s->c54, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        s->c54[3] = 0;
        s->cb = c017_01E02970;
        s->arg = arg;
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/c017", func_01E01BF0_c017);

INCLUDE_ASM("asm/nonmatchings/mod/c017", func_01E02120_c017);

/* shape c017:01E025B0, 118 insns: mode 0 sets the drawing state (a 0x9B matrix from the angle 0x5A, colours 0x48/0x4C,
   the scene texture 0x21C); otherwise sizes the scene quad 0x1A0 to 0x56, puts all four corners at height 0x14,
   pushes them 0x58 along the heading 0x52 (game table 0x39A4), builds the rotation matrix 0x140 from 0x20 and, when
   the quad is on screen, sends it with the scene texture 0x38E8 */

typedef struct {
    u8 pad0[0x14];
    f32 y;
    u8 pad18[8];
    s32 rot[4];
    u8 pad30[0x18];
    u8 col[4];
    u8 col2[4];
    u8 pad50[2];
    s16 heading;
    u8 pad54[2];
    s16 size;
    s16 dist;
    s16 angle;
} Fx_c017_01E025B0;

typedef struct {
    u8 pad0[0x140];
    f32 m[16];
    u8 pad180[0x20];
    Vec4f quad[4];
    u8 pad1E0[0x3C];
    s32 tex;
    u8 pad220[0x38E8 - 0x220];
    s32 tex2;
    u8 pad38EC[0x3934 - 0x38EC];
    f32 depth;
    u8 pad3938[0x39A4 - 0x3938];
    u8 trig[1];
} Scene_c017_01E025B0;

static void func_01E025B0_c017(Scene_c017_01E025B0 *g, Fx_c017_01E025B0 *o, void *p, s32 mode) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108D20(void *, f32, f32);
    extern f32 func_00108030(void *, s16, s32);
    extern void func_0020C940(void *, s32, void *, s32);
    extern void func_0020BC00(void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, void *);
    extern s32 func_001A23B0(f32);
    extern void func_002075F0(void *, s32, s32);
    f32 rm[4];
    f32 m[16];
    f32 a;
    f32 b;
    s16 size;

    size = o->size;
    if (mode == 0) {
        func_00106080(rm, 0x9B, o->angle, rm);
        func_00109270(p, 0, 0);
        func_00107790(p, o->col, 1);
        func_00107790(p, o->col2, 2);
        func_00108500(p, rm, 0);
        func_00208700(p, g->tex, 1);
    } else {
        func_00108D20(g->quad, size, size);
        g->quad[0].y = g->quad[1].y = g->quad[2].y = g->quad[3].y = o->y;
        a = o->dist * func_00108030(g->trig, o->heading, 1);
        b = o->dist * func_00108030(g->trig, o->heading, 0);
        g->quad[0].x += a;
        g->quad[0].z += b;
        g->quad[1].x += a;
        g->quad[1].z += b;
        g->quad[2].x += a;
        g->quad[2].z += b;
        g->quad[3].x += a;
        g->quad[3].z += b;
        func_0020C940(m, 0, o->rot, 0);
        func_0020BC00(g->m, m);
        if (func_00205630(g->quad, 0x70000000, g->m, p, &g->depth) != 0) {
            func_002075F0(p, g->tex2, func_001A23B0(g->depth));
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/c017", func_01E02790_c017);

/* shape c017:01E02970, 71 insns: draws a slot effect (c035:01E01290 shape with the effect colours at 0x50): mode 0 builds the
   gouraud packet with q 0, other modes queue it */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_c017_01E02970;

typedef struct {
    Rgbaq_c017_01E02970 c;
    u64 xyz;
} Vtx_c017_01E02970;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_c017_01E02970 v[4];
} Pkt_c017_01E02970;

typedef struct {
    u8 pad0[0x50];
    u8 c40[4];
    u8 c44[4];
} Fx_c017_01E02970;

typedef struct {
    u8 pad0[0x38E8];
    s32 target;
} Scene_c017_01E02970;

static void func_01E02970_c017(Scene_c017_01E02970 *g, Fx_c017_01E02970 *o, Pkt_c017_01E02970 *p, s32 mode) {
    extern Rgbaq_c017_01E02970 func_00107740(void *);
    extern void func_002075F0(void *, s32, s32);

    if (mode == 0) {
        p->count = 0x14;
        p->tag = 8;
        p->regs = 0x41414141;
        p->pad = 0;
        func_002086D0(p, ((u64)0x80 << 32) | 0x48);
        p->v[0].c = func_00107740(o->c40);
        p->v[1].c = func_00107740(o->c40);
        p->v[2].c = func_00107740(o->c44);
        p->v[3].c = func_00107740(o->c44);
        p->v[0].c.q = p->v[1].c.q = p->v[2].c.q = p->v[3].c.q = 0.0f;
        func_001094F0(p);
    } else {
        func_002075F0(p, g->target, 0);
    }
}

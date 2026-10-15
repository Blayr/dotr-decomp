#include "common.h"

/* shape c056:01E00080, 111 insns: sets up the scene's 22 models (ids 0..10 and 256..266): object 0x170 + i x 0x70 gets a
   random size 1..5 (0x54), 0x28 -2..12, 0x34 0x100..0x18FF, 0x38 -0x3FF..0x3FF, is registered with the model (0x4 and
   0x24 cleared), tagged from 0x40E0 + i x 0x10 and coloured; flagged models are switched, and func_00107310 runs for
   models func_001F5EC0 accepts */

typedef struct {
    u8 pad0[4];
    s32 w4;
    u8 pad8[0x1C];
    s32 w24;
    s32 w28;
    u8 pad2C[8];
    s32 w34;
    s32 w38;
    u8 pad3C[4];
    f32 scale[3];
    u8 pad4C[8];
    f32 f54;
    u8 pad58[8];
    u8 col[4];
    u8 pad64[0xC];
} Obj_c056_01E00080;

typedef struct {
    u8 tag[0x10];
} Tag_c056_01E00080;

typedef struct {
    u8 pad0[0x170];
    Obj_c056_01E00080 obj[22];
    u8 padB10[0x40E0 - 0xB10];
    Tag_c056_01E00080 tags[22];
} Scene_c056_01E00080;

static void func_01E00080_c056(Scene_c056_01E00080 *g) {
    extern s32 func_001F5AF0(s32);
    extern void func_001F5970(s32, s32);
    extern void func_001F5BD0(s32, void *);
    extern void func_001F5B70(s32, void *);
    extern void func_001F5CA0(s32, void *);
    extern void func_001F5E40(s32, void *);
    extern s32 func_001F5EC0(s32);
    extern void func_00107310(s32, s32, s32);
    s16 i;
    Obj_c056_01E00080 *p;
    s32 id;

    for (i = 0; i < 22; i++) {
        id = i;
        if (id > 10) {
            id += 0xF5;
        }
        p = &g->obj[i];
        p->f54 = (func_0019A5C8() % 26 + 9) / 6;
        p->w28 = func_0019A5C8() % 8 + 5;
        p->w34 = func_0019A5C8() % 0x1800 + 0x100;
        p->w38 = func_0019A5C8() % 0x800 - 0x400;
        func_001F5BD0(id, p);
        p->w4 = 0;
        func_001F5B70(id, p);
        p->w24 = 0;
        func_001F5CA0(id, &g->tags[i]);
        func_001F5E40(id, p->col);
        if (func_001F5AF0(id) != 0) {
            func_001F5970(id, 1);
        }
        if (func_001F5EC0(id) != 0) {
            func_00107310(id, 0, 1);
        }
    }
}

/* shape c056:01E00240, 70 insns: sound voice k (k + 0xF5 above 10) while the game counter at 0x4478 is below 10:
   if it plays, set its volume byte to 0x80 and (unless bit k of 0x447C) fade it to 0.15; if it is ready, aim it at
   the game's 16-byte slot 0x40E0[k], clear p->4 and attach p, and (unless bit k) start it (0x18) */

typedef struct {
    u8 pad0[0x40E0];
    u8 slot[0x39][16];
    u8 pad4470[8];
    s32 count;
    u32 mask;
} Game_c056_01E00240;

typedef struct {
    u8 pad0[4];
    s32 f4;
} P_c056_01E00240;

static s32 func_01E00240_c056(Game_c056_01E00240 *g, P_c056_01E00240 *p, s32 k) {
    extern s32 func_001F5EC0(s32);
    extern void func_001F6490(s32, void *);
    extern void func_001F63E0(s32, void *);
    extern void func_00107370(s32, s32, f32);
    extern s32 func_001F5AF0(s32);
    extern void func_001F5C40(s32, void *);
    extern void func_001F5B70(s32, void *);
    extern void func_00107650(s32, s32);
    u8 v[4];
    s32 ch;

    ch = k;
    if (k > 10) {
        ch = k + 0xF5;
    }
    if (g->count < 10) {
        if (func_001F5EC0(ch) != 0) {
            func_001F6490(ch, v);
            v[3] = 0x80;
            func_001F63E0(ch, v);
            if (!((g->mask >> k) & 1)) {
                func_00107370(ch, 0, 0.15f);
            }
        }
        if (func_001F5AF0(ch) != 0) {
            func_001F5C40(ch, g->slot[k]);
            p->f4 = 0;
            func_001F5B70(ch, p);
            if (!((g->mask >> k) & 1)) {
                func_00107650(ch, 0x18);
            }
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E00360_c056);

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E00800_c056);

/* shape c056:01E00C10, 15 insns: spawn an effect entity from the context's pool (kind 0x46) and store arg in it */

typedef struct Ent_c056_01E00C10 {
    u8 pad0[0x9C];
    s32 arg;
} Ent_c056_01E00C10;

typedef struct Ctx_c056_01E00C10 {
    u8 pad0[0xC60];
    u8 pool[1];
} Ctx_c056_01E00C10;

static void func_01E00C10_c056(Ctx_c056_01E00C10 *ctx, s32 arg) {
    Ent_c056_01E00C10 *e = (Ent_c056_01E00C10 *)func_00106A00((s32)ctx, (s32)ctx->pool, 0x46, 0);

    if (e != NULL) {
        e->arg = arg;
    }
}

/* shape c056:01E00C50, 54 insns, 1 copy: spawn an effect entity, random angle % 360; its callback is
   c056:01E02560 */

typedef struct Col_c056_01E00C50 {
    u8 r, g, b, a;
} Col_c056_01E00C50;

typedef struct Ent_c056_01E00C50 {
    u8 pad0[0x64];
    f32 f64;
    u8 pad68[0x30];
    void (*cb)(void);
    s32 arg;
    u8 padA0[0xC];
    Col_c056_01E00C50 col0;
    Col_c056_01E00C50 col1;
    u8 padB4[4];
    s16 fB8;
    u8 padBA[2];
    s16 fBC;
    s16 fBE;
} Ent_c056_01E00C50;

typedef struct Ctx_c056_01E00C50 {
    u8 pad0[0x84];
    f32 f84;
    u8 pad88[0xC60 - 0x88];
    u8 pool[0x4480 - 0xC60];
    u8 rgba[4];
    u8 pad4484[0x449C - 0x4484];
    f32 pos[3];
    u8 pad44A8[0x10];
    s16 f44B8;
    u8 pad44BA[2];
    s16 f44BC;
} Ctx_c056_01E00C50;

extern void c056_01E02560(void);

static void func_01E00C50_c056(Ctx_c056_01E00C50 *ctx, s32 arg) {
    extern void func_001076F0();
    Ent_c056_01E00C50 *e = (Ent_c056_01E00C50 *)func_00106A00((s32)ctx, (s32)ctx->pool, 0x46, 0);

    if (e != NULL) {
        func_001076F0(&e->col0, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        e->col0.a = 0;
        func_001076F0(&e->col1, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        e->col1.a = 0;
        e->f64 = ctx->f84;
        func_00107E40(ctx->pos[0], ctx->pos[1], ctx->pos[2], e);
        e->fBC = ctx->f44BC;
        e->fBE = func_0019A5C8() % 360;
        e->cb = c056_01E02560;
        e->arg = arg;
        e->fB8 = ctx->f44B8;
    }
}

/* shape c056:01E00D30, 127 insns: c056:01E012A0's trail link with the scene's colour (ctx+0x4480), the height split
   by kind (0 and 1 get a floor 22 below, never under 0), ctx+0x44B8 copied, and the module's 0x1E015A0 callback */

typedef struct {
    u8 r, g, b, a;
} Col_c056_01E00D30;

typedef struct Ent_c056_01E00D30 {
    u8 pad0[4];
    f32 f4;
    u8 pad8[0xC];
    f32 f14;
    u8 pad18[0xC];
    f32 f24;
    u8 pad28[0xC];
    f32 f34;
    u8 pad38[8];
    Vec4f a;
    u8 pad50[0x10];
    Vec4f v;
    Vec4f b;
    u8 pad80[0x10];
    struct Ent_c056_01E00D30 *prev;
    struct Ent_c056_01E00D30 *next;
    void (*cb)(void);
    s32 arg;
    u8 padA0[6];
    s16 fA6;
    u8 padA8[4];
    Col_c056_01E00D30 col0;
    Col_c056_01E00D30 col1;
    u8 padB4[4];
    s16 fB8;
    s16 fBA;
    s16 fBC;
    s16 fBE;
} Ent_c056_01E00D30;

typedef struct {
    u8 pad0[0x80];
    Vec4f v;
    u8 pad90[0xC60 - 0x90];
    u8 pool[0x4480 - 0xC60];
    u8 rgba[4];
    u8 pad4484[8];
    Ent_c056_01E00D30 *last;
    u8 pad4490[0x449C - 0x4490];
    f32 pos[3];
    u8 pad44A8[0x10];
    s16 f44B8;
    s16 f44BA;
    s16 f44BC;
    u8 pad44BE[0xA];
    s16 f44C8;
} Ctx_c056_01E00D30;

static void func_01E00D30_c056(Ctx_c056_01E00D30 *ctx, s32 arg) {
    extern void c056_01E015A0(void);
    extern void func_001076F0();
    Ent_c056_01E00D30 *e = (Ent_c056_01E00D30 *)func_00106A00((s32)ctx, (s32)ctx->pool, 0x46, 0);
    Ent_c056_01E00D30 *p;
    f32 h;

    if (e != NULL) {
        func_001076F0(&e->col0, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        e->col0.a = ctx->rgba[3];
        func_001076F0(&e->col1, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        e->col1.a = ctx->rgba[3];
        e->v = ctx->v;
        func_00107E40(ctx->pos[0], ctx->pos[1], ctx->pos[2], e);
        e->fBA = ctx->f44BA;
        e->prev = ctx->last;
        e->fA6 = ctx->f44C8;
        if (e->fA6 == 0) {
            h = ctx->pos[2];
            e->f4 = e->f14 = h;
            e->f34 = e->f24 = h - 22.0f;
            if (e->f24 < 0.0f) {
                e->f34 = e->f24 = 0.0f;
            }
        } else if (e->fA6 == 1) {
            h = ctx->pos[2];
            e->f4 = e->f14 = h;
            e->f34 = e->f24 = h - 22.0f;
            if (e->f24 < 0.0f) {
                e->f34 = e->f24 = 0.0f;
            }
        }
        e->prev = ctx->last;
        p = e->prev;
        if (p != NULL) {
            e->a = p->a;
            e->b = p->b;
            p->next = e;
        }
        e->fB8 = ctx->f44B8;
        e->cb = c056_01E015A0;
        e->arg = arg;
        e->fBC = ctx->f44BC;
        e->fBE = 1;
        ctx->last = e;
    }
}

/* shape c056:01E00F30, 106 insns: spawns one blue effect (handler c056:01E02020) from the scene pool: colours it with the scene
   alpha, scales it, puts it at the anchor point (copying x and z first when the mode is 0), picks a random flip and angle and
   copies the mode, a setting and the argument */

typedef struct {
    f32 x, y, z, w;
} V4_c056_01E00F30;

typedef struct {
    f32 x, y, z;
} V3_c056_01E00F30;

typedef struct {
    u8 pad0[0x118];
    V4_c056_01E00F30 pt;
} Anchor_c056_01E00F30;

typedef struct {
    u8 pad0[0x40];
    V4_c056_01E00F30 pos;
    u8 pad50[0x20];
    V4_c056_01E00F30 at;
    u8 pad80[0x10];
    s32 mode;
    u8 pad94[4];
    void *fn;
    s32 arg;
    f32 flip;
    u8 padA4[2];
    s16 hA6;
    u8 padA8[4];
    u8 c0[4];
    u8 c1[4];
    u8 padB4[4];
    s16 ang;
    s16 hBA;
} Fx_c056_01E00F30;

typedef struct {
    u8 pad0[0xC60];
    u8 pool[0x4270 - 0xC60];
    Anchor_c056_01E00F30 anchor;
    u8 pad[0x4483 - 0x4270 - sizeof(Anchor_c056_01E00F30)];
    u8 alpha;
    u8 pad4484[8];
    s32 mode;
    u8 pad4490[0xC];
    f32 sx, sy, sz;
    u8 pad44A8[0x12];
    s16 h44BA;
    u8 pad44BC[0xC];
    s16 h44C8;
} Scene_c056_01E00F30;

static void func_01E00F30_c056(Scene_c056_01E00F30 *g, s32 arg) {
    extern void c056_01E02020(void);
    extern Fx_c056_01E00F30 *func_00106A00(void *, void *, s32, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00107E40(f32, f32, f32, void *);
    Anchor_c056_01E00F30 *a;
    Fx_c056_01E00F30 *p;

    a = &g->anchor;
    if (a != NULL) {
        p = func_00106A00(g, g->pool, 0x46, 0);
        if (p != NULL) {
            func_001076F0(p->c0, 0xF0, 0xF0, 0x80);
            p->c0[3] = g->alpha;
            p->c1[3] = g->alpha;
            func_00107E40(g->sx, g->sy, g->sz, p);
            if (g->mode == 0) {
                p->at.x = a->pt.x;
                p->at.z = a->pt.z;
                p->at = a->pt;
                p->pos = p->at;
            } else {
                p->at = a->pt;
                p->pos = p->at;
            }
            p->flip = func_0019A5C8() % 2;
            p->hBA = g->h44BA;
            p->ang = func_0019A5C8() % 360;
            p->mode = g->mode;
            p->hA6 = g->h44C8;
            p->arg = arg;
            p->fn = c056_01E02020;
        }
    }
}

/* shape c056:01E010E0, 53 insns: spawns a green glow (c056:01E00C50 family): colours 0x20/0x38/0x24 with the context's
   alpha, the context's vector at 0x80 copied in, placed at the context's position; draws with c056:01E02E10 */

typedef struct {
    u8 r, g, b, a;
} Col_c056_01E010E0;

typedef struct {
    u8 pad0[0x60];
    Vec4f v;
    u8 pad70[0x28];
    void (*cb)(void);
    s32 arg;
    u8 padA0[0xC];
    Col_c056_01E010E0 col0;
    Col_c056_01E010E0 col1;
    u8 padB4[6];
    s16 fBA;
} Ent_c056_01E010E0;

typedef struct {
    u8 pad0[0x80];
    Vec4f v;
    u8 pad90[0xC60 - 0x90];
    u8 pool[0x4480 - 0xC60];
    u8 rgba[4];
    u8 pad4484[0x449C - 0x4484];
    f32 pos[3];
    u8 pad44A8[0x12];
    s16 f44BA;
} Ctx_c056_01E010E0;

static void func_01E010E0_c056(Ctx_c056_01E010E0 *ctx, s32 arg) {
    extern void c056_01E02E10(void);
    extern void func_001076F0();
    Ent_c056_01E010E0 *e = (Ent_c056_01E010E0 *)func_00106A00((s32)ctx, (s32)ctx->pool, 0x46, 0);

    if (e != NULL) {
        func_001076F0(&e->col0, 0x20, 0x38, 0x24);
        e->col0.a = ctx->rgba[3];
        func_001076F0(&e->col1, 0x20, 0x38, 0x24);
        e->col1.a = ctx->rgba[3];
        e->v = ctx->v;
        func_00107E40(ctx->pos[0], ctx->pos[1], ctx->pos[2], e);
        e->fBA = ctx->f44BA;
        e->cb = c056_01E02E10;
        e->arg = arg;
    }
}

/* shape c056:01E011C0, 53 insns: spawns a dark glow (c056:01E00C50 family): colours 0x18 grey with the context's
   alpha, the context's vector at 0x80 copied in, placed at the context's position; draws with c056:01E02BE0 */

typedef struct {
    u8 r, g, b, a;
} Col_c056_01E011C0;

typedef struct {
    u8 pad0[0x60];
    Vec4f v;
    u8 pad70[0x28];
    void (*cb)(void);
    s32 arg;
    u8 padA0[0xC];
    Col_c056_01E011C0 col0;
    Col_c056_01E011C0 col1;
    u8 padB4[6];
    s16 fBA;
} Ent_c056_01E011C0;

typedef struct {
    u8 pad0[0x80];
    Vec4f v;
    u8 pad90[0xC60 - 0x90];
    u8 pool[0x4480 - 0xC60];
    u8 rgba[4];
    u8 pad4484[0x449C - 0x4484];
    f32 pos[3];
    u8 pad44A8[0x12];
    s16 f44BA;
} Ctx_c056_01E011C0;

static void func_01E011C0_c056(Ctx_c056_01E011C0 *ctx, s32 arg) {
    extern void c056_01E02BE0(void);
    extern void func_001076F0();
    Ent_c056_01E011C0 *e = (Ent_c056_01E011C0 *)func_00106A00((s32)ctx, (s32)ctx->pool, 0x46, 0);

    if (e != NULL) {
        func_001076F0(&e->col0, 0x18, 0x18, 0x18);
        e->col0.a = ctx->rgba[3];
        func_001076F0(&e->col1, 0x18, 0x18, 0x18);
        e->col1.a = ctx->rgba[3];
        e->v = ctx->v;
        func_00107E40(ctx->pos[0], ctx->pos[1], ctx->pos[2], e);
        e->fBA = ctx->f44BA;
        e->cb = c056_01E02BE0;
        e->arg = arg;
    }
}

/* shape c056:01E012A0, 123 insns: c056:01E010E0 family trail link: spawns a dark grey (0x15) piece with the context's alpha and vector, at the context's position, ground height 18 below it (0 when that falls below 0); chained after the context's last piece, copying its two vectors, and becomes the new last piece; draws with c056:01E022F0 */

typedef struct {
    u8 r, g, b, a;
} Col_c056_01E012A0;

typedef struct Ent_c056_01E012A0 {
    u8 pad0[4];
    f32 f4;
    u8 pad8[0xC];
    f32 f14;
    u8 pad18[0xC];
    f32 f24;
    u8 pad28[0xC];
    f32 f34;
    u8 pad38[8];
    Vec4f a;
    u8 pad50[0x10];
    Vec4f v;
    Vec4f b;
    u8 pad80[0x10];
    struct Ent_c056_01E012A0 *prev;
    struct Ent_c056_01E012A0 *next;
    void (*cb)(void);
    s32 arg;
    u8 padA0[6];
    s16 fA6;
    u8 padA8[4];
    Col_c056_01E012A0 col0;
    Col_c056_01E012A0 col1;
    u8 padB4[6];
    s16 fBA;
    s16 fBC;
    s16 fBE;
} Ent_c056_01E012A0;

typedef struct {
    u8 pad0[0x80];
    Vec4f v;
    u8 pad90[0xC60 - 0x90];
    u8 pool[0x4480 - 0xC60];
    u8 rgba[4];
    u8 pad4484[8];
    Ent_c056_01E012A0 *last;
    u8 pad4490[0x449C - 0x4490];
    f32 pos[3];
    u8 pad44A8[0x12];
    s16 f44BA;
    s16 f44BC;
    u8 pad44BE[0xA];
    s16 f44C8;
} Ctx_c056_01E012A0;

static void func_01E012A0_c056(Ctx_c056_01E012A0 *ctx, s32 arg) {
    extern void c056_01E022F0(void);
    extern void func_001076F0();
    Ent_c056_01E012A0 *e = (Ent_c056_01E012A0 *)func_00106A00((s32)ctx, (s32)ctx->pool, 0x46, 0);
    Ent_c056_01E012A0 *p;
    f32 h;

    if (e != NULL) {
        func_001076F0(&e->col0, 0x15, 0x15, 0x15);
        e->col0.a = ctx->rgba[3];
        func_001076F0(&e->col1, 0x15, 0x15, 0x15);
        e->col1.a = ctx->rgba[3];
        e->v = ctx->v;
        func_00107E40(ctx->pos[0], ctx->pos[1], ctx->pos[2], e);
        e->fBA = ctx->f44BA;
        e->prev = ctx->last;
        e->fA6 = ctx->f44C8;
        if (e->prev == NULL) {
            h = ctx->pos[2];
            e->f4 = e->f14 = h;
            e->f34 = e->f24 = h - 18.0f;
        } else {
            h = ctx->pos[2];
            e->f4 = e->f14 = h;
            e->f34 = e->f24 = h - 18.0f;
        }
        if (ctx->pos[2] - 18.0f >= 0.0f) {
            e->f34 = e->f24 = e->f4 - 18.0f;
        } else {
            e->f34 = e->f24 = 0.0f;
        }
        e->prev = ctx->last;
        p = e->prev;
        if (p != NULL) {
            e->a = p->a;
            e->b = p->b;
            p->next = e;
        }
        e->cb = c056_01E022F0;
        e->arg = arg;
        e->fBC = ctx->f44BC;
        e->fBE = 1;
        ctx->last = e;
    }
}

/* shape c056:01E01490, 66 insns: spawns a grey glow (c056:01E00C50 family): colours 0x20 with the context's alpha, height
   from the context, placed at the context's position; links to the context's parent effect (copying its vector and
   pointing it back), draws with c056:01E02790, frame 7 */

typedef struct Ent_c056_01E01490 {
    u8 pad0[4];
    f32 f4;
    u8 pad8[0xC];
    f32 f14;
    u8 pad18[0x58];
    Vec4f v;
    u8 pad80[0x10];
    struct Ent_c056_01E01490 *parent;
    struct Ent_c056_01E01490 *child;
    void (*cb)(void);
    s32 arg;
    u8 padA0[0xC];
    u8 col0[4];
    u8 col1[4];
    u8 padB4[4];
    s16 fB8;
    s16 fBA;
    u8 padBC[2];
    s16 fBE;
} Ent_c056_01E01490;

typedef struct {
    u8 pad0[0x84];
    f32 f84;
    u8 pad88[0xC60 - 0x88];
    u8 pool[0x4480 - 0xC60];
    u8 rgba[4];
    u8 pad4484[8];
    Ent_c056_01E01490 *parent;
    u8 pad4490[0xC];
    f32 pos[3];
    u8 pad44A8[0x10];
    s16 f44B8;
    s16 f44BA;
} Ctx_c056_01E01490;

static void func_01E01490_c056(Ctx_c056_01E01490 *ctx, s32 arg) {
    extern void c056_01E02790(void);
    extern void func_001076F0();
    Ent_c056_01E01490 *e = (Ent_c056_01E01490 *)func_00106A00((s32)ctx, (s32)ctx->pool, 0x46, 0);
    Ent_c056_01E01490 *p;

    if (e != NULL) {
        func_001076F0(e->col0, 0x20, 0x20, 0x20);
        e->col0[3] = ctx->rgba[3];
        func_001076F0(e->col1, 0x20, 0x20, 0x20);
        e->col1[3] = ctx->rgba[3];
        e->fBA = ctx->f44BA;
        e->f14 = e->f4 = ctx->f84;
        func_00107E40(ctx->pos[0], ctx->pos[1], ctx->pos[2], e);
        e->parent = ctx->parent;
        p = e->parent;
        if (p != NULL) {
            e->v = p->v;
            p->child = e;
        }
        e->cb = c056_01E02790;
        e->arg = arg;
        e->fB8 = ctx->f44B8;
        e->fBE = 7;
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E015A0_c056);

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E02020_c056);

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E022F0_c056);

/* shape c056:01E02560, 139 insns: b194:01E02AB0's two-pass material with a 12-segment ring: mode 0 sets the material
   (frame 0x97, the object's two colours, scene texture 0xCC); other modes turn by the scene's rotation entry for the
   object, set the ring's height to twice its depth from the top, and draw 12 segments of 30 degrees between the radii at
   0xA8 and 0xAA (scale g+0x44D0, depth 0x44A8, packet list 0x4488) */

typedef struct {
    f32 x, y, z, w;
} Vec_c056_01E02560;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_c056_01E02560;

typedef struct {
    Rgbaq_c056_01E02560 c;
    u64 st;
    u64 xyz;
} Vtx_c056_01E02560;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_c056_01E02560 v[4];
} Pkt_c056_01E02560;


typedef struct {
    Vec_c056_01E02560 q[4];
    u8 pad40[0x60];
    f32 top;
    u8 padA4[4];
    s16 r0;
    s16 r1;
    u8 col[4];
    u8 col2[4];
    u8 padB4[8];
    s16 rot;
} Ring_c056_01E02560;

typedef struct {
    u8 pad00[0x40];
    u8 m[0x40];
    u8 pad80[0x4C];
    s32 texture;
    u8 padD0[0x30];
    Vec_c056_01E02560 rots[1];
    u8 pad110[0x4378];
    s32 target;
    u8 pad448C[0x1C];
    f32 depth;
    u8 pad44AC[0x24];
    f32 scale;
} Game_c056_01E02560;

static void func_01E02560_c056(Game_c056_01E02560 *g, Ring_c056_01E02560 *an, Pkt_c056_01E02560 *p, s32 mode) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(void *, s32, s32);
    extern Rgbaq_c056_01E02560 func_00107740(void *);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020BC00(void *, void *);
    extern void func_00106CF0(void *, s16, s32, f32 *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 rm[4];
    f32 m[16];
    f32 d;
    s32 i;

    if (mode == 0) {
        func_00106080(rm, 0x97, 0, rm);
        func_00109270(p, 0, 0);
        p->v[0].c = func_00107740(an->col);
        p->v[1].c = func_00107740(an->col);
        p->v[2].c = func_00107740(an->col2);
        p->v[3].c = func_00107740(an->col2);
        func_00108500(p, rm, 0);
        func_00208700(p, g->texture, 1);
    } else {
        func_0020C940(m, 0, &g->rots[an->rot], 0);
        func_0020BC00(g->m, m);
        d = 2.0f * (an->q[0].y - an->top);
        an->q[3].y = an->q[2].y = d;
        for (i = 0; i < 12; i++) {
            func_00106CF0(&an->q[0], i * 30, an->r0, &g->scale);
            func_00106CF0(&an->q[1], i * 30 + 30, an->r0, &g->scale);
            func_00106CF0(&an->q[2], i * 30, an->r1, &g->scale);
            func_00106CF0(&an->q[3], i * 30 + 30, an->r1, &g->scale);
            if (func_00205630(an->q, 0x70000000, g->m, p, &g->depth) != 0) {
                func_002075F0(p, g->target, (u32)g->depth);
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E02790_c056);

/* shape c056:01E02BE0, 139 insns: a ring of twelve flat quads: mode 0 sets the four corner colours (two of each of
   the effect's colours); otherwise the quad's inner edge sits at the centre (y 10) and its outer corners sweep a
   radius-150 circle 30 degrees apart from the effect's angle, each quad sent at the scene depth */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_c056_01E02BE0;

typedef struct {
    Rgbaq_c056_01E02BE0 c;
    u64 st;
} Vtx_c056_01E02BE0;

typedef struct {
    u8 pad0[0x10];
    Vtx_c056_01E02BE0 v[4];
} Pkt_c056_01E02BE0;

typedef struct {
    Vec4f q[4];
    u8 pad40[0x6C];
    u8 col[4];
    u8 col2[4];
    u8 padB4[6];
    s16 ang;
} Fx_c056_01E02BE0;

typedef struct {
    u8 pad0[0x4488];
    s32 ot;
    u8 pad448C[0x1C];
    f32 depth;
    u8 pad44AC[0x24];
    u8 sin[1];
} Scene_c056_01E02BE0;

static void func_01E02BE0_c056(Scene_c056_01E02BE0 *g, Fx_c056_01E02BE0 *o, Pkt_c056_01E02BE0 *p, s32 mode) {
    extern void func_001092E0(void *, s32);
    extern Rgbaq_c056_01E02BE0 func_00107740(void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_001A23B0(f32);
    s32 i;
    s16 a;

    a = 0;
    if (mode == 0) {
        func_001092E0(p, 0);
        p->v[0].c = func_00107740(o->col);
        p->v[1].c = func_00107740(o->col);
        p->v[2].c = func_00107740(o->col2);
        p->v[3].c = func_00107740(o->col2);
        return;
    }
    o->q[0].x = 0.0f;
    o->q[0].z = 0.0f;
    o->q[1].x = o->q[0].x;
    o->q[1].z = o->q[0].z;
    o->q[0].y = 10.0f;
    o->q[1].y = 10.0f;
    o->q[2].y = 10.0f;
    o->q[3].y = 10.0f;
    for (i = 0; i < 12; i++) {
        o->q[2].x = 150.0f * func_00108030(g->sin, o->ang + a, 1);
        o->q[2].z = 150.0f * func_00108030(g->sin, o->ang + a, 0);
        o->q[3].x = 150.0f * func_00108030(g->sin, o->ang + 30 + a, 1);
        o->q[3].z = 150.0f * func_00108030(g->sin, o->ang + 30 + a, 0);
        if (func_00205630(o, 0x70000000, 0, p, &g->depth) != 0) {
            func_002075F0(p, g->ot, func_001A23B0(g->depth));
        }
        a += 30;
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E02E10_c056);

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E03090_c056);

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E03AE0_c056);

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E03DA0_c056);

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E03FE0_c056);

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E044B0_c056);

/* shape c056:01E04780, 42 insns: a sprite that fades in by 16 to 0x30 while the scene value is under 16, out by 15 while the counter is under 21, holds size 190 and ends when the counter is under 11 */

typedef struct {
    u8 pad0[0x4478];
    s32 count;
    u8 pad447C[0x46];
    s16 val;
} Ctx_c056_01E04780;

typedef struct {
    u8 pad0[0xA0];
    f32 size;
    s16 state;
    u8 padA6[0xD];
    u8 alpha;
    u8 padB4[6];
    u8 bA[1];
} Obj_c056_01E04780;

static s32 func_01E04780_c056(Ctx_c056_01E04780 *ctx, Obj_c056_01E04780 *o) {
    extern void func_00106D80(s32, void *);

    func_00106D80(5, o->bA);
    if (ctx->val < 16) {
        if (o->alpha < 0x21) {
            o->alpha += 0x10;
        }
    }
    if (ctx->count < 21) {
        if (o->alpha > 0x10) {
            o->alpha -= 15;
        }
    }
    o->size = 190.0f;
    if (ctx->count < 11) {
        o->state = 0;
    }
    return 0;
}

/* shape c056:01E04830, 52 insns: c056:01E04780 two-alpha twin: in by 32/16 while the scene value is under 16, out by 15 while the counter is under 21, ends under 11 */

typedef struct {
    u8 pad0[0x4478];
    s32 count;
    u8 padC[0x46];
    s16 val;
} Ctx_c056_01E04830;

typedef struct {
    u8 pad0[0xA4];
    s16 state;
    u8 padA6[0x9];
    u8 alpha;
    u8 padB0[0x3];
    u8 alpha2;
    u8 padB4[0x6];
    u8 bA[1];
} Obj_c056_01E04830;

static s32 func_01E04830_c056(Ctx_c056_01E04830 *ctx, Obj_c056_01E04830 *o) {
    extern void func_00106D80(s32, void *);

    func_00106D80(5, o->bA);
    if (ctx->val < 0x10) {
        if (o->alpha < 0xC0) {
            o->alpha += 0x20;
        }
        if (o->alpha2 < 0x21) {
            o->alpha2 += 0x10;
        }
    }
    if (ctx->count < 0x15) {
        if (o->alpha > 0x10) {
            o->alpha -= 15;
        }
        if (o->alpha2 > 0x10) {
            o->alpha2 -= 15;
        }
    }
    if (ctx->count < 0xb) {
        o->state = 0;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E04900_c056);

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E04CF0_c056);

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E04FE0_c056);

#include "common.h"

INCLUDE_ASM("asm/nonmatchings/mod/c015", func_01E00080_c015);

/* shape c015:01E00270, 25 insns: while the game's step (0x44C2) is below 8 the alpha grows by 0x16 (below 0xB0);
   while the counter at 0x4478 is below 10 it fades by 0x1E, then the effect stops */

typedef struct {
    u8 pad0[0x4478];
    s32 count;
    u8 pad447C[0x46];
    s16 step;
} Game_c015_01E00270;

typedef struct {
    u8 pad0[0xA4];
    s16 mode;
    u8 padA6[9];
    u8 alpha;
} Fx_c015_01E00270;

static s32 func_01E00270_c015(Game_c015_01E00270 *g, Fx_c015_01E00270 *o) {
    if (g->step < 8) {
        if (o->alpha < 0xB0) {
            o->alpha += 0x16;
        }
    }
    if (g->count < 10) {
        if (o->alpha > 0x20) {
            o->alpha -= 0x1E;
        } else {
            o->mode = 0;
        }
    }
    return 0;
}

/* shape c015:01E002E0, 114 insns: the c015 module's main step: with a code it clears the scene, loads texture (4,6), keeps the code and a 166-tick timer; otherwise it runs the scene setup (c015:01E00080), every live slot's handler (70 of 0xC0 bytes), then draws every live slot at the camera (c015:01E00840 or, for flagged slots, c015:01E00620, two passes each) and counts down; returns 8 when the timer ends */

typedef struct {
    f32 x, y, z, w;
} V4_c015_01E002E0;

typedef struct Slot_c015_01E002E0 {
    u8 pad0[0x50];
    u8 m50[0x10];
    u8 v60[0x38];
    s32 w98;
    s32 (*fn)(void *, struct Slot_c015_01E002E0 *);
    u8 padA0[4];
    s16 used;
    u8 padA6[0x1A];
} Slot_c015_01E002E0;

typedef struct {
    u8 pad0[0x40];
    u8 cam[0x68];
    s32 tex;
    u8 padAC[0xC60 - 0xAC];
    Slot_c015_01E002E0 slot[70];
    u8 padEnd[0x4478 - 0xC60 - 70 * 0xC0];
    s32 timer;
    u8 pad447C[0xC];
    s32 ot;
    u8 pad448C[0x32];
    s16 code;
} Ctx_c015_01E002E0;

static s32 func_01E002E0_c015(s32 arg0, s32 code) {
    extern void c015_01E00080(Ctx_c015_01E002E0 *, s32);
    extern void c015_01E00620(Ctx_c015_01E002E0 *, Slot_c015_01E002E0 *, void *, s32);
    extern void c015_01E00840(Ctx_c015_01E002E0 *, Slot_c015_01E002E0 *, void *, s32);
    Ctx_c015_01E002E0 *g = (Ctx_c015_01E002E0 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern s32 func_00202BF0(s32, s32);
    extern s32 func_001F5380(void);
    extern void func_001F5BD0(s32, void *);
    extern void func_00106B50(void *, void *);
    extern void func_0020EB40(void *);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020BC00(void *, void *);
    V4_c015_01E002E0 b;
    V4_c015_01E002E0 a;
    u8 pkt[0x90];
    s32 n;
    s32 i;

    n = 0;
    g->ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x4730);
        g->tex = func_00202BF0(4, 6);
        g->code = code;
        g->timer = 166;
        return 0;
    }
    c015_01E00080(g, 0);
    for (i = 0; i < 70; i++) {
        if (g->slot[i].used != 0) {
            if (g->slot[i].fn != NULL) {
                g->slot[i].fn(g, &g->slot[i]);
            }
        }
    }
    for (i = 0; i < 70; i++) {
        if (g->slot[i].used != 0) {
            n++;
            func_001F5BD0(func_001F5380(), &a);
            b.x = a.x;
            b.y = a.y;
            b.z = a.z;
            func_00106B50(&b, g->slot[i].v60);
            func_0020EB40(g->cam);
            func_0020C940(g, NULL, g->slot[i].m50, &b);
            func_0020BC00(g->cam, g);
            if (g->slot[i].w98 == 0) {
                c015_01E00840(g, &g->slot[i], pkt, 0);
                c015_01E00840(g, &g->slot[i], pkt, 1);
            } else {
                c015_01E00620(g, &g->slot[i], pkt, 0);
                c015_01E00620(g, &g->slot[i], pkt, 1);
            }
        }
    }
    if (--g->timer <= 0) {
        return 8;
    }
    return 0;
}

/* shape c015:01E004B0, 43 insns: c015:01E00560 without the callback: grab a pool slot (func_00106A00), give it the scene colour twice, the scene vector and the argument */

typedef struct V4_c015_01E004B0 {
    f32 x, y, z, w;
} V4_c015_01E004B0;

typedef struct Col_c015_01E004B0 {
    u8 r, g, b, a;
} Col_c015_01E004B0;

typedef struct Ent_c015_01E004B0 {
    u8 pad0[0x60];
    V4_c015_01E004B0 v60;
    u8 pad70[0x2C];
    s32 arg;
    u8 padA0[0xC];
    Col_c015_01E004B0 col0;
    Col_c015_01E004B0 col1;
} Ent_c015_01E004B0;

typedef struct Ctx_c015_01E004B0 {
    u8 pad0[0x80];
    V4_c015_01E004B0 v80;
    u8 pad90[0xC60 - 0x90];
    u8 pool[0x4480 - 0xC60];
    u8 rgba[4];
} Ctx_c015_01E004B0;

static void func_01E004B0_c015(Ctx_c015_01E004B0 *ctx, s32 arg) {
    extern void func_001076F0();
    Ent_c015_01E004B0 *e = (Ent_c015_01E004B0 *)func_00106A00((s32)ctx, (s32)ctx->pool, 0x46, 0);

    if (e != NULL) {
        func_001076F0(&e->col0, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        e->col0.a = ctx->rgba[3];
        func_001076F0(&e->col1, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        e->col1.a = ctx->rgba[3];
        e->v60 = ctx->v80;
        e->arg = arg;
    }
}

/* shape c015:01E00560, 48 insns, 1 copy: spawn an effect entity with the scene colour; its callback is the
   module's next function (c015:01E00620) */

typedef struct V4_c015_01E00560 {
    f32 x, y, z, w;
} V4_c015_01E00560;

typedef struct Col_c015_01E00560 {
    u8 r, g, b, a;
} Col_c015_01E00560;

typedef struct Ent_c015_01E00560 {
    u8 pad0[0x60];
    V4_c015_01E00560 v60;
    u8 pad70[0x28];
    void (*cb)(void);
    s32 arg;
    u8 padA0[0xC];
    Col_c015_01E00560 col0;
    Col_c015_01E00560 col1;
    u8 padB4[8];
    s16 fBC;
} Ent_c015_01E00560;

typedef struct Ctx_c015_01E00560 {
    u8 pad0[0x80];
    V4_c015_01E00560 v80;
    u8 pad90[0xC60 - 0x90];
    u8 pool[0x4480 - 0xC60];
    u8 rgba[4];
    u8 pad4484[0x44BC - 0x4484];
    s16 f44BC;
} Ctx_c015_01E00560;

extern void c015_01E00620(void);

static void func_01E00560_c015(Ctx_c015_01E00560 *ctx, s32 arg) {
    extern void func_001076F0();
    Ent_c015_01E00560 *e = (Ent_c015_01E00560 *)func_00106A00((s32)ctx, (s32)ctx->pool, 0x46, 0);

    if (e != NULL) {
        func_001076F0(&e->col0, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        e->col0.a = ctx->rgba[3];
        func_001076F0(&e->col1, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        e->col1.a = ctx->rgba[3];
        e->v60 = ctx->v80;
        e->fBC = ctx->f44BC;
        e->cb = c015_01E00620;
        e->arg = arg;
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/c015", func_01E00620_c015);

/* shape c015:01E00840, 105 insns: two-pass draw of a 20 x 20 quad at the scene camera point lifted 10: pass 0 writes the packet header (4 UV pairs from the object's texture rect, func_00107740); pass 1 projects it (func_00205630) and sends it at the stored depth */

typedef struct {
    f32 u, v;
} Uv_c015_01E00840;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    struct {
        Uv_c015_01E00840 uv;
        u8 pad8[8];
    } v[4];
} Pkt_c015_01E00840;

typedef struct {
    u8 pad0[0x4488];
    s32 ot;
    u8 pad448C[0x1C];
    f32 depth;
} Scene_c015_01E00840;

static void func_01E00840_c015(Scene_c015_01E00840 *g, u8 *obj, Pkt_c015_01E00840 *p, s32 pass) {
    extern void func_00107740(void *, void *);
    extern void func_001094F0(void *);
    extern void func_001F53B0(s32, void *);
    extern void func_00108D20(void *, f32, f32);
    extern void func_00106FA0(void *, void *, s32);
    extern s32 func_00205630(void *, s32, s32, void *, void *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_001A23B0(f32);
    Vec4f quad[4];
    Vec4f cam;
    Uv_c015_01E00840 uv0;
    Uv_c015_01E00840 uv1;
    Uv_c015_01E00840 uv2;
    Uv_c015_01E00840 uv3;

    if (pass == 0) {
        p->count = 0x14;
        p->tag = 8;
        p->regs = 0x41414141;
        p->pad = 0;
        func_002086D0(p, ((u64)0x80 << 32) | 0x48);
        func_00107740(&uv0, obj + 0xAC);
        p->v[0].uv = uv0;
        func_00107740(&uv1, obj + 0xAC);
        p->v[1].uv = uv1;
        func_00107740(&uv2, obj + 0xAC);
        p->v[2].uv = uv2;
        func_00107740(&uv3, obj + 0xAC);
        p->v[3].uv = uv3;
        func_001094F0(p);
        return;
    }
    func_001F53B0(0, &cam);
    func_00108D20(quad, 20.0f, 20.0f);
    func_00106FA0(quad, &cam, 0);
    quad[0].y += 10.0f;
    quad[1].y += 10.0f;
    quad[2].y += 10.0f;
    quad[3].y += 10.0f;
    if (func_00205630(quad, 0x70000000, 0, p, &g->depth) != 0) {
        func_002075F0(p, g->ot, func_001A23B0(g->depth));
    }
}

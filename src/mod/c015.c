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

INCLUDE_ASM("asm/nonmatchings/mod/c015", func_01E002E0_c015);

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

INCLUDE_ASM("asm/nonmatchings/mod/c015", func_01E00840_c015);

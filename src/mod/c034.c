#include "common.h"

INCLUDE_ASM("asm/nonmatchings/mod/c034", func_01E00080_c034);

/* shape c034:01E00290, 45 insns: both alphas grow by 0x20 (below 0xB0) until the game step at 0xDD0 reaches 0x12;
   then phase 0 sets 0x1E = 3 and moves to phase 1, which fades both by 0x10 and stops */

typedef struct {
    u8 pad0[0xDD0];
    s16 step;
} Game_c034_01E00290;

typedef struct {
    u8 pad0[0x14];
    u8 col[4];
    u8 col2[4];
    s16 mode;
    s16 f1E;
    s16 phase;
} Fx_c034_01E00290;

static s32 func_01E00290_c034(Game_c034_01E00290 *g, Fx_c034_01E00290 *o) {
    if (g->step < 0x12) {
        if (o->col[3] < 0xB0) {
            o->col[3] += 0x20;
        }
        if (o->col2[3] < 0xB0) {
            o->col2[3] += 0x20;
        }
    } else if (o->phase == 0) {
        o->f1E = 3;
        o->phase = 1;
    } else if (o->phase == 1) {
        if (o->col[3] > 0x10) {
            o->col[3] -= 0x10;
        }
        if (o->col2[3] > 0x10) {
            o->col2[3] -= 0x10;
        } else {
            o->mode = 0;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/c034", func_01E00350_c034);

/* shape c034:01E00610, 75 insns: take the first free light slot of 10 (0x24 bytes each, at ctx+0x110), clear it, mark it with its index + 1, give it the scene colour twice, handler shape c034:01E00740 and the argument; the scene keeps it as current */

typedef struct {
    u8 pad0[8];
    s32 fn;
    s32 arg;
    u8 pad10[4];
    u8 col[4];
    u8 col2[4];
    s16 used;
    s16 h1E;
    u8 pad20[4];
} Slot_c034_01E00610;

typedef struct {
    u8 pad0[0x110];
    Slot_c034_01E00610 slot[10];
    u8 pad278[0xD70 - 0x278];
    u8 cur[4];
    u8 pad74[4];
    u8 rgba[4];
    u8 padD7C[8];
    Slot_c034_01E00610 *last;
} Ctx_c034_01E00610;

static void func_01E00610_c034(Ctx_c034_01E00610 *ctx, s32 arg) {
    extern void c034_01E00740();
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    s16 i;
    Slot_c034_01E00610 *s;

    s = NULL;
    for (i = 0; i < 10; i++) {
        if (ctx->slot[i].used == 0) {
            s = &ctx->slot[i];
            func_00195108(s, 0x24);
            ctx->slot[i].used = i + 1;
            i = 10;
        }
    }
    if (s != NULL) {
        func_001076F0(s->col, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        s->col[3] = ctx->rgba[3];
        func_001076F0(s->col2, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        s->col2[3] = ctx->rgba[3];
        s->h1E = 1;
        ctx->cur[0] = ctx->rgba[0];
        ctx->cur[1] = ctx->rgba[1];
        ctx->cur[2] = ctx->rgba[2];
        ctx->cur[3] = 0;
        s->fn = (s32)c034_01E00740;
        s->arg = arg;
        ctx->last = s;
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/c034", func_01E00740_c034);

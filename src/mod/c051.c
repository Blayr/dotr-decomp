#include "common.h"

INCLUDE_ASM("asm/nonmatchings/mod/c051", func_01E00080_c051);

INCLUDE_ASM("asm/nonmatchings/mod/c051", func_01E003A0_c051);

INCLUDE_ASM("asm/nonmatchings/mod/c051", func_01E00590_c051);

/* shape c051:01E00800, 83 insns: takes the first free of 8 effect slots (0x40 bytes, b108:01E02FF0 family), marks it with its
   index + 1, colours all four corners from the context, copies two of its values and its frame, and hooks c051:01E00950 */

typedef struct {
    u8 pad0[0x10];
    void (*cb)(void);
    s32 arg;
    f32 f18;
    u8 pad1C[4];
    f32 f20;
    u8 c24[4];
    u8 c28[4];
    u8 c2C[4];
    u8 c30[4];
    s16 f34;
    s16 used;
    u8 pad38[8];
} Slot_c051_01E00800;

typedef struct {
    u8 pad0[0xB0];
    Slot_c051_01E00800 slots[8];
    u8 pad[0x2B4 - 0xB0 - 8 * 0x40];
    u8 rgba[4];
    u8 pad2B8[0x10];
    f32 f2C8;
    u8 pad2CC[4];
    f32 f2D0;
    u8 pad2D4[0x1E];
    s16 f2F2;
} Ctx_c051_01E00800;

static void func_01E00800_c051(Ctx_c051_01E00800 *ctx, s32 arg) {
    extern void c051_01E00950(void);
    extern void func_001076F0();
    extern void func_00195108();
    Slot_c051_01E00800 *s = NULL;
    s16 i;

    for (i = 0; i < 8; i++) {
        if (ctx->slots[i].used == 0) {
            s = &ctx->slots[i];
            func_00195108(s, 0x40);
            ctx->slots[i].used = i + 1;
            i = 8;
        }
    }
    if (s != NULL) {
        func_001076F0(s->c24, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        s->c24[3] = ctx->rgba[3];
        func_001076F0(s->c28, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        s->c28[3] = ctx->rgba[3];
        func_001076F0(s->c2C, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        s->c2C[3] = ctx->rgba[3];
        func_001076F0(s->c30, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        s->c30[3] = ctx->rgba[3];
        s->f20 = ctx->f2D0;
        s->f18 = ctx->f2C8;
        s->f34 = ctx->f2F2;
        s->cb = c051_01E00950;
        s->arg = arg;
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/c051", func_01E00950_c051);

INCLUDE_ASM("asm/nonmatchings/mod/c051", func_01E00C50_c051);

/* shape c051:01E00EC0, 87 insns: take a free row (8 of 0x40 bytes at 0xB0, mark = index + 1), clear it, four colours
   from the scene colour 0x2B4 with alpha 0x80, 0x20/0x18 from the scene floats 0x2D0/0x2C8, 0x38/0x3A/0x34 from
   0x2EA/0x2EC/0x2F2, callback c051:01E00C50 and arg */

typedef struct {
    u8 pad0[0x10];
    void (*cb)(void);
    s32 arg;
    f32 f18;
    u8 pad1C[4];
    f32 f20;
    u8 c24[4];
    u8 c28[4];
    u8 c2C[4];
    u8 c30[4];
    s16 f34;
    s16 used;
    s16 f38;
    s16 f3A;
    u8 pad3C[4];
} Row_c051_01E00EC0;

typedef struct {
    u8 pad0[0xB0];
    Row_c051_01E00EC0 rows[8];
    u8 pad2B0[4];
    u8 rgb[4];
    u8 pad2B8[0x10];
    f32 f2C8;
    u8 pad2CC[4];
    f32 f2D0;
    u8 pad2D4[0x16];
    s16 f2EA;
    s16 f2EC;
    u8 pad2EE[4];
    s16 f2F2;
} Scene_c051_01E00EC0;

static void func_01E00EC0_c051(Scene_c051_01E00EC0 *g, s32 arg) {
    extern void c051_01E00C50(void);
    extern void func_00195108();
    extern void func_001076F0(void *, s32, s32, s32);
    Row_c051_01E00EC0 *s = NULL;
    s16 i;

    for (i = 0; i < 8; i++) {
        if (g->rows[i].used == 0) {
            func_00195108(&g->rows[i], 0x40);
            g->rows[i].used = i + 1;
            s = &g->rows[i];
            i = 8;
        }
    }
    if (s != NULL) {
        func_001076F0(s->c24, g->rgb[0], g->rgb[1], g->rgb[2]);
        s->c24[3] = 0x80;
        func_001076F0(s->c28, g->rgb[0], g->rgb[1], g->rgb[2]);
        s->c28[3] = 0x80;
        func_001076F0(s->c2C, g->rgb[0], g->rgb[1], g->rgb[2]);
        s->c2C[3] = 0x80;
        func_001076F0(s->c30, g->rgb[0], g->rgb[1], g->rgb[2]);
        s->c30[3] = 0x80;
        s->f20 = g->f2D0;
        s->f18 = g->f2C8;
        s->f38 = g->f2EA;
        s->f3A = g->f2EC;
        s->f34 = g->f2F2;
        s->cb = c051_01E00C50;
        s->arg = arg;
    }
}

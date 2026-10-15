#include "common.h"

INCLUDE_ASM("asm/nonmatchings/mod/c026", func_01E00080_c026);

/* shape c026:01E00B10, 54 insns: fades two alphas by the game timer: up 8 to 0x80 for 13 frames, then down 16 to 0x10
   while the phase is below 6, then up 8 to 0xB0; clears the flag below phase 2 */

typedef struct {
    u8 pad0[0x1A40];
    s32 phase;
    u8 pad1A44[0x80];
    s16 timer;
} Game_c026_01E00B10;

typedef struct {
    u8 pad0[0x64];
    u8 c0[4];
    u8 c1[4];
    s16 flag;
} Obj_c026_01E00B10;

static s32 func_01E00B10_c026(Game_c026_01E00B10 *g, Obj_c026_01E00B10 *o) {
    if (g->timer < 0xD) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 8;
        }
        if (o->c1[3] < 0x80) {
            o->c1[3] += 8;
        }
    } else if (g->phase < 6) {
        if (o->c0[3] > 0x10) {
            o->c0[3] -= 0x10;
        }
        if (o->c1[3] > 0x10) {
            o->c1[3] -= 0x10;
        }
    } else {
        if (o->c0[3] < 0xB0) {
            o->c0[3] += 8;
        }
        if (o->c1[3] < 0xB0) {
            o->c1[3] += 8;
        }
    }
    if (g->phase < 2) {
        o->flag = 0;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/c026", func_01E00BF0_c026);

INCLUDE_ASM("asm/nonmatchings/mod/c026", func_01E00F20_c026);

/* shape c026:01E01170, 64 insns: takes the first free of 50 effect slots (0x80 bytes, b108:01E02FF0 family), marks it with
   its index + 1, colours both from the context, hooks c026:01E014F0 with the given argument and remembers it */

typedef struct {
    u8 pad0[0x58];
    void (*cb)(void);
    s32 arg;
    u8 pad60[4];
    u8 c64[4];
    u8 c68[4];
    s16 used;
    u8 pad6E[0x12];
} Slot_c026_01E01170;

typedef struct {
    u8 pad0[0x140];
    Slot_c026_01E01170 slots[0x32];
    u8 pad[0x1A44 - 0x140 - 0x32 * 0x80];
    u8 rgba[4];
    u8 pad1A48[8];
    Slot_c026_01E01170 *last;
} Ctx_c026_01E01170;

static void func_01E01170_c026(Ctx_c026_01E01170 *ctx, s32 arg) {
    extern void c026_01E014F0(void);
    extern void func_001076F0();
    extern void func_00195108();
    Slot_c026_01E01170 *s = NULL;
    s16 i;

    for (i = 0; i < 0x32; i++) {
        if (ctx->slots[i].used == 0) {
            s = &ctx->slots[i];
            func_00195108(s, 0x80);
            ctx->slots[i].used = i + 1;
            i = 0x32;
        }
    }
    if (s != NULL) {
        func_001076F0(s->c64, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        s->c64[3] = ctx->rgba[3];
        func_001076F0(s->c68, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        s->c68[3] = ctx->rgba[3];
        s->cb = c026_01E014F0;
        s->arg = arg;
        ctx->last = s;
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/c026", func_01E01270_c026);

INCLUDE_ASM("asm/nonmatchings/mod/c026", func_01E014F0_c026);

INCLUDE_ASM("asm/nonmatchings/mod/c026", func_01E01860_c026);

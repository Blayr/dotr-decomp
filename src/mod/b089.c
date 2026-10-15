#include "common.h"

/* shape b081:01E00080, 30 insns, 24 copies (s32 twin of b034:01E00080): shift a position history down by one, the newest from src */

static s32 func_01E00080_b089(Vec4f *dst, s32 n, s32 arg2, Vec4f *src) {
    s32 i;
    s32 k = n - 1;
    Vec4f *prev = dst;

    prev--;
    for (i = 0; i < n; i++, dst--, prev--, k--) {
        if (k != 0) {
            dst->x = prev->x;
            dst->y = prev->y;
            dst->z = prev->z;
        } else {
            dst->x = src->x;
            dst->y = src->y;
            dst->z = src->z;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b089", func_01E00100_b089);

/* shape b089:01E00470, 73 insns: a grey smoke puff of random size 10..24, frame 0..14 and two random angles: in by 9 up to 0x60 for 10 ticks, then out by 5 and ends */

typedef struct {
    u8 pad0[8];
    s16 h8;
    s16 hA;
    u8 padC[0x1C];
    u8 col[4];
    u8 col2[4];
    s16 h30;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
    s16 ang;
} Glow_b089_01E00470;

static s32 func_01E00470_b089(s32 arg0, Glow_b089_01E00470 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    func_001076F0(o->col, 0x3F, 0x3F, 0x3F);
    if (o->mode == 1) {
        o->f38 = func_0019A5C8() % 15 + 10;
        o->ang = func_0019A5C8() % 360;
        o->col[3] = 0;
        o->kind = func_0019A5C8() % 15;
        o->h30 = func_0019A5C8() % 360;
        o->mode = 2;
    }
    if (o->tick < 10) {
        if (o->col[3] < 0x60) {
            o->col[3] += 9;
        }
    } else if (o->col[3] > 6) {
        o->col[3] -= 5;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b089:01E005A0, 79 insns: colour (0x5F, 0x50, 0x50); register its position with the game (b089:01E00080 on
   0x26D0, kind 10); sink z by 7 x the sine of the model angle - 180; on start 0x38 = 5; alpha 0x50, tick 8 */

typedef struct {
    u8 pad0[0x26D0];
    u8 list[0x3B8C - 0x26D0];
    u8 trig[1];
} Game_b089_01E005A0;

typedef struct {
    s16 x, y, z;
    u8 pad6[0x22];
    u8 col[4];
    u8 pad2C[6];
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f38;
} Fx_b089_01E005A0;

static s32 func_01E005A0_b089(Game_b089_01E005A0 *g, Fx_b089_01E005A0 *o) {
    extern void b089_01E00080(void *, s32, s32, void *);
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F6160(s32, void *);
    extern f32 func_00108030(void *, s32, s32);
    Vec4f pos;
    s32 ang[4];

    func_001076F0(o->col, 0x5F, 0x50, 0x50);
    pos.x = o->x;
    pos.y = o->y;
    pos.z = o->z;
    b089_01E00080(g->list, 10, 0, &pos);
    func_001F6160(func_001F53A0(), ang);
    o->z = o->z - 7.0f * func_00108030(g->trig, (s16)(ang[1] / 180.0f) - 180, 1);
    if (o->mode == 1) {
        o->f38 = 5;
        o->mode = 2;
    }
    o->col[3] = 0x50;
    o->tick = 8;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b089", func_01E006E0_b089);

INCLUDE_ASM("asm/nonmatchings/mod/b089", func_01E00890_b089);

INCLUDE_ASM("asm/nonmatchings/mod/b089", func_01E00A30_b089);

/* shape b089:01E013A0, 70 insns: a dark smoke puff (size 13) cycling frames 0..6 from a random start: in by 48 up to 0x60 for 2 ticks; out by 5 once the scene counter is under 25, then ends */

typedef struct {
    u8 pad0[6];
    s16 h6;
    u8 pad8[0x20];
    u8 col[4];
    u8 col2[4];
    s16 h30;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
    s16 ang;
} Glow_b089_01E013A0;

typedef struct {
    u8 pad[0x26E0];
    s32 count;
} Game_b089_01E013A0;

static s32 func_01E013A0_b089(Game_b089_01E013A0 *g, Glow_b089_01E013A0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    func_001076F0(o->col, 0x10, 0x10, 0x10);
    if (o->mode == 1) {
        o->kind = func_0019A5C8() % 5;
        o->f38 = 13;
        o->mode = 2;
        o->col[3] = 0;
    }
    if (o->tick < 2) {
        if (o->col[3] < 0x60) {
            o->col[3] += 0x30;
        }
    }
    if (o->tick != 0) {
        if (o->kind < 6) {
            o->kind++;
        } else {
            o->kind = 0;
        }
    }
    o->tick++;
    if (g->count < 25) {
        if (o->col[3] > 6) {
            o->col[3] -= 5;
        } else {
            o->mode = 0;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b089", func_01E014C0_b089);

INCLUDE_ASM("asm/nonmatchings/mod/b089", func_01E016D0_b089);

INCLUDE_ASM("asm/nonmatchings/mod/b089", func_01E01BA0_b089);

INCLUDE_ASM("asm/nonmatchings/mod/b089", func_01E01D90_b089);

INCLUDE_ASM("asm/nonmatchings/mod/b089", func_01E01F50_b089);

INCLUDE_ASM("asm/nonmatchings/mod/b089", func_01E020E0_b089);

INCLUDE_ASM("asm/nonmatchings/mod/b089", func_01E022C0_b089);

INCLUDE_ASM("asm/nonmatchings/mod/b089", func_01E024F0_b089);

/* shape b089:01E026B0, 47 insns: constant variant of b205:01E01E50 (volume fade by game state): state at 0x26E0 limit 0x1F,
   floor 0x30, down 10, up 10, cap 0x80 */

typedef struct {
    u8 pad[0x26E0];
    s32 state;
} Game_b089_01E026B0;

typedef struct {
    u8 pad[0x30];
    s16 vol;
    u8 pad32[4];
    s16 mode;
} Fade_b089_01E026B0;

static s32 func_01E026B0_b089(Game_b089_01E026B0 *g, Fade_b089_01E026B0 *o) {
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
        func_001F6D00((u8)o->vol);
    } else {
        func_001F6D00((u8)o->vol);
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b089", func_01E02770_b089);

/* shape b089:01E030B0, 72 insns: takes the first free of 20 effect slots (0x40 bytes, b108:01E02FF0 family), colours it
   from the context, places it at the context's position and stores the frame and both arguments */

typedef struct {
    u8 pad0[0x20];
    s32 a2;
    s32 a1;
    u8 c28[4];
    u8 c2C[4];
    s16 f30;
    u8 pad32[4];
    s16 used;
    u8 pad38[8];
} Slot_b089_01E030B0;

typedef struct {
    f32 pos[3];
    u8 padC[0xA4];
    Slot_b089_01E030B0 slots[0x14];
    u8 pad[0x26E4 - 0xB0 - 0x14 * 0x40];
    u8 rgba[4];
    u8 pad26E8[0x149C];
    s16 f3B84;
} Ctx_b089_01E030B0;

static s32 func_01E030B0_b089(Ctx_b089_01E030B0 *ctx, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b089_01E030B0 *s = NULL;
    s16 i;

    for (i = 0; i < 0x14; i++) {
        if (ctx->slots[i].used == 0) {
            func_00195108(&ctx->slots[i], 0x40);
            ctx->slots[i].used = 1;
            s = &ctx->slots[i];
            i = 0x14;
        }
    }
    if (s != NULL) {
        func_001076F0(s->c28, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        s->c28[3] = ctx->rgba[3];
        func_001076F0(s->c2C, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        s->c2C[3] = ctx->rgba[3];
        func_00106AB0(s, ctx->pos, 0);
        s->f30 = ctx->f3B84;
        s->a2 = arg2;
        s->a1 = arg1;
        return 1;
    }
    return 0;
}

/* shape b089:01E031D0, 72 insns: takes the first free of 50 effect slots (0x40 bytes, b108:01E02FF0 family), colours it
   from the context, places it at the context's position and stores the frame and both arguments */

typedef struct {
    u8 pad0[0x20];
    s32 a2;
    s32 a1;
    u8 c28[4];
    u8 c2C[4];
    s16 f30;
    u8 pad32[4];
    s16 used;
    u8 pad38[8];
} Slot_b089_01E031D0;

typedef struct {
    f32 pos[3];
    u8 padC[0x5A4];
    Slot_b089_01E031D0 slots[0x32];
    u8 pad[0x26E4 - 0x5B0 - 0x32 * 0x40];
    u8 rgba[4];
    u8 pad26E8[0x149C];
    s16 f3B84;
} Ctx_b089_01E031D0;

static s32 func_01E031D0_b089(Ctx_b089_01E031D0 *ctx, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b089_01E031D0 *s = NULL;
    s16 i;

    for (i = 0; i < 0x32; i++) {
        if (ctx->slots[i].used == 0) {
            func_00195108(&ctx->slots[i], 0x40);
            ctx->slots[i].used = 1;
            s = &ctx->slots[i];
            i = 0x32;
        }
    }
    if (s != NULL) {
        func_001076F0(s->c28, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        s->c28[3] = ctx->rgba[3];
        func_001076F0(s->c2C, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        s->c2C[3] = ctx->rgba[3];
        func_00106AB0(s, ctx->pos, 0);
        s->f30 = ctx->f3B84;
        s->a2 = arg2;
        s->a1 = arg1;
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b089", func_01E032F0_b089);

INCLUDE_ASM("asm/nonmatchings/mod/b089", func_01E035E0_b089);

INCLUDE_ASM("asm/nonmatchings/mod/b089", func_01E03780_b089);

INCLUDE_ASM("asm/nonmatchings/mod/b089", func_01E03930_b089);

INCLUDE_ASM("asm/nonmatchings/mod/b089", func_01E03D60_b089);

INCLUDE_ASM("asm/nonmatchings/mod/b089", func_01E040E0_b089);

INCLUDE_ASM("asm/nonmatchings/mod/b089", func_01E04330_b089);

INCLUDE_ASM("asm/nonmatchings/mod/b089", func_01E045A0_b089);

INCLUDE_ASM("asm/nonmatchings/mod/b089", func_01E04770_b089);

INCLUDE_ASM("asm/nonmatchings/mod/b089", func_01E048E0_b089);

#include "common.h"

INCLUDE_ASM("asm/nonmatchings/mod/c006", func_01E00080_c006);

/* shape c006:01E004C0, 74 insns: moves by 80 a tick, down to -400 (game flag 0x296C clear) or up to 400 (set), then
   ends; 0x56 wraps at 64; while the game counter at 0x2910 is below 14 both alphas fade by 8 (the second ends it),
   otherwise both are 0x1A; the effect stops below counter 2 */

typedef struct {
    u8 pad0[0x2910];
    s32 count;
    u8 pad2914[0x58];
    s16 dir;
} Game_c006_01E004C0;

typedef struct {
    f32 y;
    u8 pad4[0x34];
    u8 col[4];
    u8 pad3C[4];
    u8 col2[4];
    u8 pad44[4];
    s16 mode;
    u8 pad4A[0xC];
    s16 f56;
} Fx_c006_01E004C0;

static s32 func_01E004C0_c006(Game_c006_01E004C0 *g, Fx_c006_01E004C0 *o) {
    if (g->dir == 0) {
        if (!(o->y <= -400.0f)) {
            o->y -= 80.0f;
        } else {
            o->mode = 0;
        }
    } else if (o->y < 400.0f) {
        o->y += 80.0f;
    } else {
        o->mode = 0;
    }
    if (o->f56 >= 0x40) {
        o->f56 %= 0x40;
    }
    if (g->count < 14) {
        if (o->col[3] > 0xA) {
            o->col[3] -= 8;
        }
        if (o->col2[3] > 0xA) {
            o->col2[3] -= 8;
        } else {
            o->mode = 0;
        }
    } else {
        o->col[3] = 0x1A;
        o->col2[3] = 0x1A;
    }
    if (g->count < 2) {
        o->mode = 0;
    }
    return 0;
}

/* shape c006:01E005F0, 70 insns: an 8-tick counter (0x52); rises by its speed (0x20) up to 150, then ends; 0x56 wraps
   at 64; while the game counter at 0x2910 is below 14 both alphas fade by 7 (the second ends it), otherwise both
   grow by 0x10 (below 0x50); the effect stops below counter 2 */

typedef struct {
    u8 pad0[0x2910];
    s32 count;
} Game_c006_01E005F0;

typedef struct {
    f32 y;
    u8 pad4[0x1C];
    f32 speed;
    u8 pad24[0x14];
    u8 col[4];
    u8 pad3C[4];
    u8 col2[4];
    u8 pad44[4];
    s16 mode;
    u8 pad4A[8];
    s16 f52;
    u8 pad54[2];
    s16 f56;
} Fx_c006_01E005F0;

static s32 func_01E005F0_c006(Game_c006_01E005F0 *g, Fx_c006_01E005F0 *o) {
    o->f52++;
    if (o->f52 >= 8) {
        o->f52 = 0;
    }
    if (o->y < 150.0f) {
        o->y += o->speed;
    } else {
        o->mode = 0;
    }
    if (o->f56 >= 0x40) {
        o->f56 %= 0x40;
    }
    if (g->count < 14) {
        if (o->col[3] > 8) {
            o->col[3] -= 7;
        }
        if (o->col2[3] > 8) {
            o->col2[3] -= 7;
        } else {
            o->mode = 0;
        }
    } else {
        if (o->col[3] < 0x50) {
            o->col[3] += 0x10;
        }
        if (o->col2[3] < 0x50) {
            o->col2[3] += 0x10;
        }
    }
    if (g->count < 2) {
        o->mode = 0;
    }
    return 0;
}

/* shape c006:01E00710, 118 insns: sets up the scene's 22 models (ids 0..10 and 256..266): object 0x1C90 + i x 0x70 gets
   a random size 1..5 (0x54), 0x28 -2..12, 0x34 0x100..0x18FF, 0x38 -0x3FF..0x3FF; all but models 0 and 11 are
   switched, it is registered (0x4 cleared, func_001F5B70 for flagged models), tagged from 0x2780 + i x 0x10 and
   coloured; flagged models get alpha 0x80 */

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
} Obj_c006_01E00710;

typedef struct {
    u8 tag[0x10];
} Tag_c006_01E00710;

typedef struct {
    u8 pad0[0x1C90];
    Obj_c006_01E00710 obj[22];
    u8 pad2630[0x2780 - 0x2630];
    Tag_c006_01E00710 tags[22];
} Scene_c006_01E00710;

static void func_01E00710_c006(Scene_c006_01E00710 *g) {
    extern s32 func_001F5AF0(s32);
    extern void func_001F5970(s32, s32);
    extern void func_001F5BD0(s32, void *);
    extern void func_001F5B70(s32, void *);
    extern void func_001F5CA0(s32, void *);
    extern void func_001F5E40(s32, void *);
    extern void func_001F5DE0(s32, void *);
    s16 i;
    s32 id;

    for (i = 0; i < 22; i++) {
        id = i;
        if (i > 10) {
            id = i + 0xF5;
        }
        {
        Obj_c006_01E00710 *p = &g->obj[i];
        p->f54 = (func_0019A5C8() % 26 + 9) / 6;
        p->w28 = func_0019A5C8() % 8 + 5;
        p->w34 = func_0019A5C8() % 0x1800 + 0x100;
        p->w38 = func_0019A5C8() % 0x800 - 0x400;
        if (i != 0 && i != 11) {
            func_001F5970(id, 1);
        }
        func_001F5BD0(id, p);
        p->w4 = 0;
        if (func_001F5AF0(id) != 0) {
            func_001F5B70(id, p);
        }
        func_001F5CA0(id, &g->tags[i]);
        func_001F5E40(id, p->col);
        if (func_001F5AF0(id) != 0) {
            func_001F5E40(id, p->col);
            p->col[3] = 0x80;
            func_001F5DE0(id, p->col);
        }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/c006", func_01E008F0_c006);

INCLUDE_ASM("asm/nonmatchings/mod/c006", func_01E00B80_c006);

/* shape c006:01E00F00, 70 insns: take a free slot (0x50 of 0x58 bytes at 0x110), clear it, copy the scene's pair at
   0x2914 twice, its vector at 0x80 and 0x296A; callback c006:01E01180 and arg */

typedef struct {
    f32 x, y, z, w;
} V4_c006_01E00F00;

typedef struct {
    f32 a, b;
} P2_c006_01E00F00;

typedef struct {
    V4_c006_01E00F00 pos;
    u8 pad10[0x20];
    void (*cb)(void);
    s32 arg;
    P2_c006_01E00F00 p38;
    P2_c006_01E00F00 p40;
    s16 used;
    u8 pad4A[0xC];
    s16 f56;
} Slot_c006_01E00F00;

typedef struct {
    u8 pad0[0x80];
    V4_c006_01E00F00 pos;
    u8 pad90[0x80];
    Slot_c006_01E00F00 slots[0x50];
    u8 pad1C90[0x2914 - 0x1C90];
    P2_c006_01E00F00 pair;
    u8 pad291C[0x4E];
    s16 f296A;
} Scene_c006_01E00F00;

static void func_01E00F00_c006(Scene_c006_01E00F00 *g, s32 arg) {
    extern void c006_01E01180(void);
    extern void func_00195108();
    Slot_c006_01E00F00 *s = NULL;
    s16 i;

    for (i = 0; i < 0x50; i++) {
        if (g->slots[i].used == 0) {
            func_00195108(&g->slots[i], 0x58);
            g->slots[i].used = 1;
            s = &g->slots[i];
            i = 0x50;
        }
    }
    if (s != NULL) {
        s->p38 = g->pair;
        s->p40 = g->pair;
        s->pos = g->pos;
        s->f56 = g->f296A;
        s->cb = c006_01E01180;
        s->arg = arg;
    }
}

/* shape c006:01E01020, 88 insns: takes the first free of 80 effect slots (0x58 bytes, b108:01E02FF0 family), gives it the
   context's UV pair twice and point, a random size 10..19 and side 0..1, the context's frame, and hooks c006:01E012D0 */

typedef struct {
    f32 s, t;
} St_c006_01E01020;

typedef struct {
    Vec4f pos;
    u8 pad10[0x10];
    f32 size;
    u8 pad24[0xC];
    void (*cb)(void);
    s32 arg;
    St_c006_01E01020 st0;
    St_c006_01E01020 st1;
    s16 used;
    u8 pad4A[0xA];
    s16 side;
    s16 f56;
} Slot_c006_01E01020;

typedef struct {
    u8 pad0[0x80];
    Vec4f pos;
    u8 pad90[0x80];
    Slot_c006_01E01020 slots[0x50];
    u8 pad[0x2914 - 0x110 - 0x50 * 0x58];
    St_c006_01E01020 st;
    u8 pad291C[0x4E];
    s16 f296A;
} Ctx_c006_01E01020;

static void func_01E01020_c006(Ctx_c006_01E01020 *ctx, s32 arg) {
    extern void c006_01E012D0(void);
    extern void func_00195108();
    Slot_c006_01E01020 *s = NULL;
    s16 i;

    for (i = 0; i < 0x50; i++) {
        if (ctx->slots[i].used == 0) {
            func_00195108(&ctx->slots[i], 0x58);
            ctx->slots[i].used = 1;
            s = &ctx->slots[i];
            i = 0x50;
        }
    }
    if (s != NULL) {
        s->st0 = ctx->st;
        s->st1 = ctx->st;
        s->pos = ctx->pos;
        s->size = func_0019A5C8() % 10 + 0xA;
        s->side = func_0019A5C8() % 2;
        s->f56 = ctx->f296A;
        s->cb = c006_01E012D0;
        s->arg = arg;
    }
}

/* shape c006:01E01180, 83 insns: draws a textured quad effect: mode 0 builds the packet (texture page 0x99 rectangle, UVs from
   the effect's two corners, the context's texture); other modes place it at 600 x 720 and queue it at the context depth */

typedef struct {
    f32 s, t;
} St_c006_01E01180;

typedef struct {
    St_c006_01E01180 st;
    u8 c[8];
    u64 xyz;
} Vtx_c006_01E01180;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_c006_01E01180 v[4];
} Pkt_c006_01E01180;

typedef struct {
    u8 pad0[0x38];
    St_c006_01E01180 st0;
    St_c006_01E01180 st1;
} Fx_c006_01E01180;

typedef struct {
    u8 pad0[0xDC];
    void *tex;
    u8 padE0[0x291C - 0xE0];
    s32 ot;
    u8 pad2920[0x28];
    f32 depth;
} Ctx_c006_01E01180;

static void func_01E01180_c006(Ctx_c006_01E01180 *g, Fx_c006_01E01180 *o, Pkt_c006_01E01180 *p, s32 mode) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00108500(void *, void *, s32);
    extern void func_00106DD0(void *, f32, f32, f32);
    extern void func_001095D0(void *, void *, void *);
    extern void func_002075F0(void *, s32, s32);
    s16 rect[8];
    Vec4f v;

    if (mode == 0) {
        func_00106080(rect, 0x99, 2, rect);
        p->count = 0x34;
        p->tag = 0xC;
        p->regs = ((u64)0x4214 << 32) | 0x21421421;
        p->pad = 0;
        p->count |= 0x800;
        func_002086D0(p, ((u64)0x80 << 32) | 0x48);
        p->v[0].st = o->st0;
        p->v[1].st = o->st0;
        p->v[2].st = o->st1;
        p->v[3].st = o->st1;
        func_00108500(p, rect, 1);
        func_00208700(p, g->tex, 1);
    } else {
        func_00106DD0(&v, 600.0f, 720.0f, 0.0f);
        func_001095D0(p, &v, o);
        func_002075F0(p, g->ot, (u32)g->depth);
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/c006", func_01E012D0_c006);

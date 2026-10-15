#include "common.h"

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E00080_c059);

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E00340_c059);

/* shape c059:01E005C0, 68 insns: brings a sound channel up (channels past 10 are shifted by 0xF5): while the scene's
   state is below 10, fades a playing channel that is none of the three reserved ones and raises its volume byte by 16
   up to 0x80 */

typedef struct {
    u8 pad0[0x2A50];
    s32 state;
    u8 pad2A54[0x258];
    s32 res[3];
} Ctx_c059_01E005C0;

static s32 func_01E005C0_c059(Ctx_c059_01E005C0 *c, s32 arg1, s32 ch) {
    extern s32 func_001F5EC0(s32);
    extern s32 func_001F5AF0(s32);
    extern void func_00107370(s32, s32, f32);
    extern void func_001F5E40(s32, void *);
    extern void func_001F5DE0(s32, void *);
    u8 vol[4];
    s32 n;

    n = ch;
    if (ch > 0xA) {
        n = ch + 0xF5;
    }
    if (c->state < 0xA) {
        if (func_001F5EC0(n) != 0) {
            if (c->res[0] != n && c->res[1] != n && c->res[2] != n) {
                func_00107370(n, 0, 0.15f);
            }
        }
        if (func_001F5AF0(n) != 0) {
            func_001F5E40(n, vol);
            if (c->res[0] != n && c->res[1] != n && c->res[2] != n) {
                vol[3] += 0x10;
                if (vol[3] > 0x80) {
                    vol[3] = 0x80;
                }
                func_001F5DE0(n, vol);
            }
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E006D0_c059);

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E00B30_c059);

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E00FB0_c059);

/* shape c059:01E01BB0, 75 insns: takes the first free of 48 effect slots (0x58 bytes, c021:01E028F0 shape), marks it with its
   index + 1, colours both from the context, copies the context's point and stores both arguments */

typedef struct {
    u8 pad0[0x10];
    Vec4f pos;
    u8 pad20[0x18];
    s32 a2;
    s32 a1;
    u8 c40[4];
    u8 c44[4];
    s16 used;
    u8 pad4A[0xE];
} Slot_c059_01E01BB0;

typedef struct {
    u8 pad0[0x290];
    Slot_c059_01E01BB0 slots[0x30];
    u8 pad[0x2A20 - 0x290 - 0x30 * 0x58];
    Vec4f pos;
    u8 pad2A30[0x24];
    u8 rgba[4];
} Ctx_c059_01E01BB0;

static void func_01E01BB0_c059(Ctx_c059_01E01BB0 *ctx, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106CC0();
    s16 i;
    Slot_c059_01E01BB0 *s;

    for (i = 0; i < 0x30; i++) {
        if (ctx->slots[i].used == 0) {
            s = &ctx->slots[i];
            func_00106CC0(s, 0x58);
            ctx->slots[i].used = i + 1;
            goto found;
        }
    }
    s = NULL;
found:
    if (s != NULL) {
        func_001076F0(s->c44, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        s->c44[3] = ctx->rgba[3];
        func_001076F0(s->c40, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        s->c40[3] = ctx->rgba[3];
        s->pos = ctx->pos;
        s->a2 = arg2;
        s->a1 = arg1;
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E01CE0_c059);

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E01EE0_c059);

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E020E0_c059);

/* shape c059:01E02310, 84 insns: takes the first free of 40 effect slots (0x30 bytes, c059:01E01BB0 shape), marks it with its
   index + 1, colours both from the context at alpha 0, copies two frames, links it to the context's parent effect (taking
   its point twice and pointing it back), frame 5, and stores both arguments */

typedef struct Slot_c059_01E02310 {
    s16 x0, y0, z0;
    u8 pad6[2];
    s16 x, y, z;
    u8 padE[2];
    struct Slot_c059_01E02310 *parent;
    struct Slot_c059_01E02310 *child;
    s32 a2;
    s32 a1;
    u8 c20[4];
    u8 c24[4];
    s16 used;
    s16 f2A;
    s16 f2C;
    s16 f2E;
} Slot_c059_01E02310;

typedef struct {
    u8 pad0[0x1C30];
    Slot_c059_01E02310 slots[0x28];
    u8 pad[0x2A54 - 0x1C30 - 0x28 * 0x30];
    u8 rgba[4];
    u8 pad2A58[4];
    Slot_c059_01E02310 *parent;
    u8 pad2A60[0x36];
    s16 f2A96;
    u8 pad2A98[4];
    s16 f2A9C;
} Ctx_c059_01E02310;

static void func_01E02310_c059(Ctx_c059_01E02310 *ctx, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106CC0();
    s16 i;
    Slot_c059_01E02310 *s;
    Slot_c059_01E02310 *p;

    for (i = 0; i < 0x28; i++) {
        if (ctx->slots[i].used == 0) {
            s = &ctx->slots[i];
            func_00106CC0(s, 0x30);
            ctx->slots[i].used = i + 1;
            goto found;
        }
    }
    s = NULL;
found:
    if (s != NULL) {
        func_001076F0(s->c24, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        s->c24[3] = 0;
        func_001076F0(s->c20, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        s->c20[3] = 0;
        s->f2A = ctx->f2A96;
        s->f2E = ctx->f2A9C;
        s->parent = ctx->parent;
        p = s->parent;
        if (p != NULL) {
            p->child = s;
            s->x0 = s->x = p->x;
            s->y0 = s->y = p->y;
            s->z0 = s->z = p->z;
        }
        s->f2C = 5;
        s->a2 = arg2;
        s->a1 = arg1;
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E02460_c059);

/* shape c059:01E025E0, 92 insns: c059:01E01BB0 family: take the first free slot of 48 (0x58 bytes), clear it, mark it with its index + 1, give it the scene colour twice, position, three turns (fptosi of ctx+0x2A40..48), ids and both arguments */

typedef struct {
    u8 pad0[0x10];
    Vec4f pos;
    u8 pad20[0x10];
    s32 w30;
    u8 pad34[4];
    s32 a2;
    s32 a1;
    u8 c40[4];
    u8 c44[4];
    s16 used;
    s16 h4A;
    s16 h4C;
    s16 h4E;
    s16 h50;
    s16 h52;
    u8 pad54[2];
    s16 h56;
} Slot_c059_01E025E0;

typedef struct {
    u8 pad0[0x290];
    Slot_c059_01E025E0 slots[0x30];
    u8 pad[0x2A20 - 0x290 - 0x30 * 0x58];
    Vec4f pos;
    u8 pad2A30[0x10];
    f32 rx, ry, rz;
    u8 pad2A4C[8];
    u8 rgba[4];
    u8 pad2A58[4];
    s32 w2A5C;
    u8 pad2A60[0x30];
    s16 h2A90;
    u8 pad2A92[4];
    s16 h2A96;
    u8 pad2A98[4];
    s16 h2A9C;
} Ctx_c059_01E025E0;

static void func_01E025E0_c059(Ctx_c059_01E025E0 *ctx, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106CC0();
    extern s16 func_001A22C0(f32);
    s16 i;
    Slot_c059_01E025E0 *s;

    for (i = 0; i < 0x30; i++) {
        if (ctx->slots[i].used == 0) {
            s = &ctx->slots[i];
            func_00106CC0(s, 0x58);
            ctx->slots[i].used = i + 1;
            goto found;
        }
    }
    s = NULL;
found:
    if (s != NULL) {
        func_001076F0(s->c44, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        s->c44[3] = ctx->rgba[3];
        func_001076F0(s->c40, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        s->c40[3] = ctx->rgba[3];
        s->pos = ctx->pos;
        s->h4E = func_001A22C0(ctx->rx);
        s->h50 = func_001A22C0(ctx->ry);
        s->h4C = func_001A22C0(ctx->rz);
        s->h4A = ctx->h2A90;
        s->w30 = ctx->w2A5C;
        s->h56 = ctx->h2A9C;
        s->h52 = ctx->h2A96;
        s->a2 = arg2;
        s->a1 = arg1;
    }
}

/* shape c059:01E02750, 80 insns: take a free row (0x1B of 0x30 bytes at 0x1720), clear it, mark it with its index + 1;
   colour it from the scene colour 0x2A54, attach it to the scene points 0x2A20 / 0x2A10, one random roll thrown away,
   0x2A from the scene float 0x2A40, random 0x2C 0..1, scale 1, 0x2E from 0x2A9C, store arg */

typedef struct {
    u8 pad0[0x10];
    f32 sx, sy, sz;
    u8 pad1C[4];
    s32 arg;
    u8 col[4];
    s16 used;
    s16 f2A;
    s16 f2C;
    s16 f2E;
} Row_c059_01E02750;

typedef struct {
    u8 pad0[0x1720];
    Row_c059_01E02750 rows[0x1B];
    u8 pad1C30[0x2A10 - 0x1C30];
    u8 p2A10[0x10];
    u8 p2A20[0x20];
    f32 f2A40;
    u8 pad2A44[0x10];
    u8 rgba[4];
    u8 pad2A58[0x44];
    s16 f2A9C;
} Scene_c059_01E02750;

static void func_01E02750_c059(Scene_c059_01E02750 *g, s32 arg1, s32 arg) {
    extern void func_00106CC0(void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106AB0(void *, void *, s32);
    s16 i;
    Row_c059_01E02750 *s;

    for (i = 0; i < 0x1B; i++) {
        if (g->rows[i].used == 0) {
            s = &g->rows[i];
            func_00106CC0(s, 0x30);
            g->rows[i].used = i + 1;
            goto found;
        }
    }
    s = NULL;
found:
    if (s != NULL) {
        func_001076F0(s->col, g->rgba[0], g->rgba[1], g->rgba[2]);
        s->col[3] = g->rgba[3];
        func_00106AB0(s, g->p2A20, 0);
        func_0019A5C8();
        s->f2A = g->f2A40;
        s->f2C = func_0019A5C8() % 2;
        func_00106AB0(s, g->p2A10, 1);
        s->sx = 1.0f;
        s->sy = 1.0f;
        s->sz = 1.0f;
        s->f2E = g->f2A9C;
        s->arg = arg;
    }
}

/* shape c059:01E02890, 67 insns: take a free slot (10 of 0x3C bytes at 0x23B0), clear it, mark it with its index + 1;
   attach it to the scene points 0x2A20 (mode 0) and 0x2A10 (mode 1), 0x30 from the scene float 0x2A40, 0x32/0x28 from
   0x2A90/0x2A9C, store the two arguments */

typedef struct {
    u8 pad0[0x20];
    s32 a2;
    s32 a1;
    s16 f28;
    u8 pad2A[4];
    s16 used;
    s16 f30;
    s16 f32;
    u8 pad34[8];
} Slot_c059_01E02890;

typedef struct {
    u8 pad0[0x23B0];
    Slot_c059_01E02890 slots[10];
    u8 pad2608[0x2A10 - 0x2608];
    u8 p2A10[0x10];
    u8 p2A20[0x20];
    f32 f2A40;
    u8 pad2A44[0x4C];
    s16 f2A90;
    u8 pad2A92[0xA];
    s16 f2A9C;
} Scene_c059_01E02890;

static void func_01E02890_c059(Scene_c059_01E02890 *g, s32 a1, s32 a2) {
    extern void func_00195108();
    extern void func_00106AB0(void *, void *, s32);
    Slot_c059_01E02890 *s = NULL;
    s16 i;

    for (i = 0; i < 10; i++) {
        if (g->slots[i].used == 0) {
            func_00195108(&g->slots[i], 0x3C);
            g->slots[i].used = i + 1;
            s = &g->slots[i];
            i = 10;
        }
    }
    if (s != NULL) {
        func_00106AB0(s, g->p2A20, 0);
        s->f30 = g->f2A40;
        s->f32 = g->f2A90;
        s->f28 = g->f2A9C;
        func_00106AB0(s, g->p2A10, 1);
        s->a2 = a2;
        s->a1 = a1;
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E029A0_c059);

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E02C10_c059);

/* shape c059:01E02DE0, 85 insns: draws an effect: mode 0 sets the packet's two colours from the scene colour with the effect's
   alphas and the scene texture; other modes lay the scene's quad (-20..20 by 30..120) and draw it three times with random
   frames 0..5 of texture page 0x82 */

typedef struct {
    u8 pad0[0x40];
    u8 c40[4];
    u8 c44[4];
} Fx_c059_01E02DE0;

typedef struct {
    u8 pad0[0x80];
    f32 m[16];
    u8 padC0[0x190];
    Vec4f quad[4];
    u8 pad290[0x263C - 0x290];
    void *tex;
    u8 pad2640[0x48C];
    s32 ot;
    u8 pad2AD0[0x25C];
    u8 col[4];
} Ctx_c059_01E02DE0;

static void func_01E02DE0_c059(Ctx_c059_01E02DE0 *c, Fx_c059_01E02DE0 *o, void *p, s32 mode) {
    extern void func_00107790(void *, void *, s32);
    extern void func_00106080(void *, s32, s16, void *);
    extern void func_00108500(void *, void *, s32);
    extern void func_00108FF0(void *, void *, void *, s32);
    s16 rect[8];
    s16 i;

    func_0019A5C8();
    if (mode == 0) {
        c->col[3] = o->c44[3];
        func_00107790(p, c->col, 1);
        c->col[3] = o->c40[3];
        func_00107790(p, c->col, 2);
        func_00208700(p, c->tex, 1);
    } else {
        c->quad[0].x = -20.0f;
        c->quad[0].y = 120.0f;
        c->quad[1].x = 20.0f;
        c->quad[1].y = 120.0f;
        c->quad[2].x = -20.0f;
        c->quad[2].y = 30.0f;
        c->quad[3].x = 20.0f;
        c->quad[3].y = 30.0f;
        c->quad[0].z = 0.0f;
        c->quad[2].z = 0.0f;
        c->quad[3].z = 0.0f;
        c->quad[1].z = 0.0f;
        for (i = 0; i < 3; i++) {
            func_00106080(rect, 0x82, func_0019A5C8() % 6, rect);
            func_00108500(p, rect, 0);
            func_00108FF0(c->quad, p, c->m, c->ot);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E02F40_c059);

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E031C0_c059);

/* shape b073:01E03BC0, 2 insns, 5 copies: an empty callback */

static void func_01E03600_c059(void) {
}

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E03610_c059);

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E03B00_c059);

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E03D70_c059);

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E040B0_c059);

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E04420_c059);

/* shape c059:01E053B0, 35 insns: raises two alphas by 16 up to 0x80 while the scene value is under 10, lowers them by 16 down to 16 while the other one is */

typedef struct {
    u8 pad0[0x2A50];
    s32 w2A50;
    u8 pad2A54[0x4E];
    s16 h2AA2;
} Ctx_c059_01E053B0;

typedef struct {
    u8 pad0[0x43];
    u8 a43;
    u8 pad44[3];
    u8 a47;
} Obj_c059_01E053B0;

static s32 func_01E053B0_c059(Ctx_c059_01E053B0 *ctx, Obj_c059_01E053B0 *o) {
    if (ctx->h2AA2 < 10) {
        if (o->a47 < 0x80) {
            o->a47 += 0x10;
        }
        if (o->a43 < 0x80) {
            o->a43 += 0x10;
        }
    }
    if (ctx->w2A50 < 10) {
        if (o->a47 > 0x10) {
            o->a47 -= 0x10;
        }
        if (o->a43 > 0x10) {
            o->a43 -= 0x10;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E05440_c059);

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E05710_c059);

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E05A70_c059);

/* shape c059:01E05E40, 83 insns: a blue glow following a scene point plus its offset (or the scene's own point once the timer
   passes 0x87 with the flag set); fades in by 16 to 0xB0 while the state is at least 11, else out by 15; grows by 4 to 60,
   turns 2048 */

typedef struct {
    Vec4f p;
    Vec4f off;
    u8 pad20[0x50];
} Pt_c059_01E05E40;

typedef struct {
    u8 pad0[0x2650];
    Pt_c059_01E05E40 pts[6];
    f32 x, y, z;
    u8 pad28FC[0x154];
    s32 state;
    u8 pad2A54[0x4E];
    s16 timer;
    u8 pad2AA4[0x24];
    s32 flag;
} Ctx_c059_01E05E40;

typedef struct {
    u8 pad0[0x10];
    f32 x, y, z;
    u8 pad1C[8];
    f32 ang;
    u8 pad28[0x18];
    u8 c40[4];
    u8 c44[4];
    s16 live;
    u8 pad4A[2];
    s16 size;
    u8 pad4E[8];
    s16 idx;
} Fx_c059_01E05E40;

static s32 func_01E05E40_c059(Ctx_c059_01E05E40 *c, Fx_c059_01E05E40 *o) {
    o->x = c->pts[o->idx].p.x + c->pts[o->idx].off.x;
    o->y = c->pts[o->idx].p.y + c->pts[o->idx].off.y;
    o->z = c->pts[o->idx].p.z + c->pts[o->idx].off.z;
    if (c->timer > 0x87) {
        if (c->flag != 0) {
            o->x = c->x;
            o->y = c->y;
            o->z = c->z;
        }
    }
    o->c44[3] = 0;
    o->c44[0] = 0x50;
    o->c44[1] = 0x50;
    o->c44[2] = 0xFF;
    if (c->state > 0xA) {
        if (o->c40[3] < 0xB0) {
            o->c40[3] += 0x10;
        }
    } else if (o->c40[3] > 0x10) {
        o->c40[3] -= 0xF;
    } else {
        o->live = 0;
    }
    o->c40[0] = 0xB0;
    o->c40[1] = 0xB0;
    o->c40[2] = 0xBF;
    if (o->size < 0x3C) {
        o->size += 4;
    }
    o->ang += 2048.0f;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E05F90_c059);

/* shape c059:01E06280, 27 insns: second alpha 0; while the counter at 0x2A50 is below 10 fade by 0x15 and stop at
   the end, otherwise grow by 0x3C (below 0xF0); colour (0x20, 0, 0x40) */

typedef struct {
    u8 pad0[0x2A50];
    s32 count;
} Game_c059_01E06280;

typedef struct {
    u8 pad0[0x40];
    u8 col[4];
    u8 col2[4];
    s16 mode;
} Fx_c059_01E06280;

static s32 func_01E06280_c059(Game_c059_01E06280 *g, Fx_c059_01E06280 *o) {
    o->col2[3] = 0;
    if (g->count < 10) {
        if (o->col[3] > 0x20) {
            o->col[3] -= 0x15;
        } else {
            o->mode = 0;
        }
    } else {
        if (o->col[3] < 0xF0) {
            o->col[3] += 0x3C;
        }
    }
    o->col[0] = 0x20;
    o->col[1] = 0;
    o->col[2] = 0x40;
    return 0;
}

/* shape c059:01E062F0, 41 insns, 1 copy */

typedef struct Obj_c059_01E062F0 {
    u8 pad0[0x43];
    u8 c43;
    u8 pad44[3];
    u8 c47;
    s16 f48;
    u8 pad4A[0xC];
    s16 f56;
} Obj_c059_01E062F0;

static s32 func_01E062F0_c059(void *ctx, Obj_c059_01E062F0 *o) {
    if (o->f56 == 0) {
        if (o->c47 < 0xE0) {
            o->c47 += 0x30;
        }
        if (o->c43 < 0xE0) {
            o->c43 += 0x30;
        } else {
            o->f56 = 1;
        }
    } else if (o->f56 < 4) {
        o->f56++;
    } else {
        if (o->c47 > 0x13) {
            o->c47 -= 0x10;
        }
        if (o->c43 > 0x13) {
            o->c43 -= 0x10;
        } else {
            o->f48 = 0;
        }
    }
    return 0;
}

/* shape c059:01E063A0, 51 insns: a 10-tick counter (0x52); 0x4E swings by 2 between 0x14 and 0x3C (direction 0x56);
   while the game counter at 0x2A50 is below 10 the alpha fades by 0x10 and stops, otherwise grows by 9 below 0x80 */

typedef struct {
    u8 pad0[0x2A50];
    s32 count;
} Game_c059_01E063A0;

typedef struct {
    u8 pad0[0x40];
    u8 col[4];
    u8 pad44[4];
    s16 mode;
    u8 pad4A[4];
    s16 swing;
    u8 pad50[2];
    s16 f52;
    u8 pad54[2];
    s16 dir;
} Fx_c059_01E063A0;

static s32 func_01E063A0_c059(Game_c059_01E063A0 *g, Fx_c059_01E063A0 *o) {
    o->f52++;
    if (o->f52 >= 10) {
        o->f52 = 0;
    }
    if (o->dir == 0) {
        o->swing += 2;
        if (o->swing > 0x3C) {
            o->dir = 1;
        }
    } else {
        o->swing -= 2;
        if (o->swing < 0x14) {
            o->dir = 0;
        }
    }
    if (g->count < 10) {
        if (o->col[3] > 0x10) {
            o->col[3] -= 0x10;
        } else {
            o->mode = 0;
        }
    } else if (o->col[3] < 0x80) {
        o->col[3] += 9;
    }
    return 0;
}

/* shape c059:01E06470, 85 insns: a flying shard: moves by its s16 velocity and ends below ground; within 35 of the origin it
   shrinks by 0.35 on three axes and ends when the third runs out; flickers its colour every other frame */

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 vx, vy, vz;
    u8 padE[2];
    f32 sx, sy, sz;
    u8 pad1C[8];
    u8 c24[4];
    s16 live;
    u8 pad2A[2];
    s16 flip;
} Fx_c059_01E06470;

static s32 func_01E06470_c059(void *arg0, Fx_c059_01E06470 *o) {
    extern f32 func_001A6C60(f32);
    extern void func_00106BF0(void *, s32, s32, s32);
    extern void func_00106C50(void *, s32, s32, s32);
    s16 x;
    s16 y;
    s16 z;

    o->y += o->vy;
    if (o->y < 0) {
        o->live = 0;
    }
    o->x += o->vx;
    o->z += o->vz;
    x = o->x;
    z = o->z;
    y = o->y;
    if (!(35.0f <= func_001A6C60(x * x + z * z + y * y))) {
        o->sx -= 0.35f;
        o->sz -= 0.35f;
        o->sy -= 0.35f;
        if (o->sz < 0.0f) {
            o->live = 0;
        }
    }
    if (o->flip == 0) {
        func_00106BF0(o->c24, 0x30, 0, 1);
        o->flip = 1;
    } else {
        func_00106BF0(o->c24, 0x30, 0, 0);
        o->flip = 0;
    }
    func_00106C50(o->c24, 0x12, 0x80, 0);
    return 0;
}

/* shape c059:01E065D0, 84 insns: a purple rising glow: rises 9 a frame (its sub-frame stepped by the module timer); between
   heights 41 and 130 fades both alphas in by 19 to 0x80 while the scene state is at least 11 (else out by 15); above 130
   fades out and ends when the second runs out; ends at height 160 */

typedef struct {
    u8 pad0[0x2A50];
    s32 state;
} Ctx_c059_01E065D0;

typedef struct {
    u8 pad0[2];
    s16 y;
    u8 pad4[0x2A];
    s16 live;
    u8 pad30[2];
    s16 sub;
    u8 c34[4];
    u8 c38[4];
} Fx_c059_01E065D0;

static s32 func_01E065D0_c059(Ctx_c059_01E065D0 *c, Fx_c059_01E065D0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106D80(s32, void *);

    o->y += 9;
    func_00106D80(5, &o->sub);
    if (o->y > 0x82) {
        if (o->c34[3] > 0x10) {
            o->c34[3] -= 0xF;
        }
        if (o->c38[3] > 0x10) {
            o->c38[3] -= 0xF;
        } else {
            o->live = 0;
        }
    } else if (o->y > 0x28) {
        if (c->state > 0xA) {
            if (o->c34[3] < 0x80) {
                o->c34[3] += 0x13;
            }
            if (o->c38[3] < 0x80) {
                o->c38[3] += 0x13;
            }
        } else {
            if (o->c34[3] > 0x10) {
                o->c34[3] -= 0xF;
            }
            if (o->c38[3] > 0x10) {
                o->c38[3] -= 0xF;
            }
        }
    }
    if (o->y >= 0xA0) {
        o->live = 0;
    }
    func_001076F0(o->c34, 0x80, 0x40, 0x80);
    func_001076F0(o->c38, 0x80, 0x40, 0x80);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E06720_c059);

/* shape c059:01E06DC0, 88 insns: draws a scene effect (c017:01E02970 shape): mode 0 builds the gouraud packet (blend 0x48 for
   the c059:01E063A0 and c059:01E062F0 effects, else 0x42; colours swapped, q 0), other modes queue it */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_c059_01E06DC0;

typedef struct {
    Rgbaq_c059_01E06DC0 c;
    u64 xyz;
} Vtx_c059_01E06DC0;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_c059_01E06DC0 v[4];
} Pkt_c059_01E06DC0;

typedef struct {
    u8 pad0[0x3C];
    void *cb;
    u8 c40[4];
    u8 c44[4];
} Fx_c059_01E06DC0;

typedef struct {
    u8 pad0[0x2ACC];
    s32 target;
} Scene_c059_01E06DC0;

static void func_01E06DC0_c059(Scene_c059_01E06DC0 *g, Fx_c059_01E06DC0 *o, Pkt_c059_01E06DC0 *p, s32 mode) {
    extern void c059_01E062F0(void);
    extern void c059_01E063A0(void);
    extern Rgbaq_c059_01E06DC0 func_00107740(void *);
    extern void func_002075F0(void *, s32, s32);

    if (mode == 0) {
        p->count = 0x14;
        p->tag = 8;
        p->regs = 0x41414141;
        p->pad = 0;
        if (o->cb == (void *)c059_01E063A0 || o->cb == (void *)c059_01E062F0) {
            func_002086D0(p, ((u64)0x80 << 32) | 0x48);
        } else {
            func_002086D0(p, ((u64)0x80 << 32) | 0x42);
        }
        p->v[0].c = func_00107740(o->c44);
        p->v[1].c = func_00107740(o->c44);
        p->v[2].c = func_00107740(o->c40);
        p->v[3].c = func_00107740(o->c40);
        p->v[0].c.q = p->v[1].c.q = p->v[2].c.q = p->v[3].c.q = 0.0f;
        func_001094F0(p);
    } else {
        func_002075F0(p, g->target, 0);
    }
}

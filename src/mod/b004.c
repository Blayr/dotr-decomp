#include "common.h"

INCLUDE_ASM("asm/nonmatchings/mod/b004", func_01E00080_b004);

/* shape b004:01E00460, 32 insns, 5 copies: step of a flash: first rises to alpha 0xF0 (then marks itself done rising),
   afterwards fades by 14 until it ends; keeps its colour at 0x9F/0x5F/0x5F */

typedef struct {
    u8 pad0[0x28];
    u8 c0[4];
    u8 pad2C[4];
    s16 up;
    u8 pad32[4];
    s16 state;
} Obj_b004_01E00460;

static s32 func_01E00460_b004(void *arg0, Obj_b004_01E00460 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->up == 0) {
        if (o->c0[3] < 0xF0) {
            o->c0[3] = 0xF0;
        } else {
            o->up = 1;
        }
    } else if (o->c0[3] > 15) {
        o->c0[3] -= 14;
    } else {
        o->state = 0;
    }
    func_001076F0(o->c0, 0x9F, 0x5F, 0x5F);
    return 0;
}

/* shape b004:01E004E0, 30 insns: colour from the module's table at 0x01E01F80; at game step 0x50 clear 0x36; below
   step 0x46 hold the countdown at 8, else count it down to 0 */

typedef struct {
    u8 r, g, b, a;
} Col_b004_01E004E0;

typedef struct {
    u8 pad0[0x34AC];
    s16 step;
} Game_b004_01E004E0;

typedef struct {
    u8 pad0[0x28];
    Col_b004_01E004E0 col;
    u8 pad2C[6];
    s16 count;
    u8 pad34[2];
    s16 f36;
} Fx_b004_01E004E0;

extern Col_b004_01E004E0 D_01E01F80_b004;

static s32 func_01E004E0_b004(Game_b004_01E004E0 *g, Fx_b004_01E004E0 *o) {
    o->col = D_01E01F80_b004;
    if (g->step == 0x50) {
        o->f36 = 0;
    }
    if (g->step < 0x46) {
        o->count = 8;
    } else if (o->count != 0) {
        o->count--;
    }
    return 0;
}

/* shape b004:01E00560, 83 insns: a purple mote (size 9) drifting 20 a tick along its two angles (sine table at ctx+0x34E0): in by 9 up to 0x60 for 10 ticks, then out by 10 and ends */

typedef struct {
    u8 pad0[2];
    s16 h2;
    s16 h4;
    u8 pad6[2];
    s16 h8;
    s16 hA;
    s16 hC;
    u8 padE[2];
    s32 w10;
    s32 w14;
    s32 w18;
    u8 pad1C[0xC];
    u8 col[4];
    u8 col2[4];
    s16 h30;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
    s16 ang;
} Glow_b004_01E00560;

typedef struct {
    u8 pad[0x34E0];
    u8 sin[1];
} Game_b004_01E00560;

static s32 func_01E00560_b004(Game_b004_01E00560 *g, Glow_b004_01E00560 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s16 func_001A22C0(f32);

    o->f38 = 9;
    func_001076F0(o->col, 0x3F, 0, 0x6F);
    if (o->tick < 10) {
        if (o->col[3] < 0x60) {
            o->col[3] += 9;
        }
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    o->tick++;
    o->h8 = func_001A22C0(o->h8 + 20.0f * func_00108030(g->sin, o->ang, 0));
    o->hA = func_001A22C0(o->hA + 20.0f * func_00108030(g->sin, o->h30, 1));
    o->hC = func_001A22C0(o->hC + 20.0f * func_00108030(g->sin, o->ang, 1));
    return 0;
}

/* shape b004:01E006B0, 56 insns: a pink rising ring: grows by 4 up to 10, rises 2 a frame from 15 and ends past 180;
   fades both alphas by 32 from height 80 */

typedef struct {
    u8 pad0[2];
    s16 y;
    u8 pad4[2];
    s16 size;
    u8 pad8[0x20];
    u8 c0[4];
    u8 c1[4];
    u8 pad30[6];
    s16 state;
} Obj_b004_01E006B0;

static s32 func_01E006B0_b004(void *arg0, Obj_b004_01E006B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->size < 0xA) {
        o->size += 4;
    }
    o->y += 2;
    func_001076F0(o->c0, 0xFF, 0xF0, 0xFF);
    if (o->y > 0xB4) {
        o->state = 0;
    }
    if (o->state == 1) {
        o->y = 0xF;
        o->size = 0;
        o->c0[3] = 0xC0;
        o->state = 2;
    }
    if (o->y >= 0x50) {
        if (o->c0[3] > 0x20) {
            o->c0[3] -= 0x20;
        } else {
            o->state = 0;
        }
        if (o->c1[3] > 0x20) {
            o->c1[3] -= 0x20;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b004", func_01E00790_b004);

/* shape b004:01E009F0, 84 insns: a purple pulse: set up once at alpha 0 with frame 22 (6 before game frame 0x4F); alpha up by
   0x50 for 2 frames, then down by 10 until it ends; sub-frame up to 7, frame down by one every third frame; at game frame
   0x53 the alpha drops to 0x20 and at 0x54 it ends */

typedef struct {
    u8 pad0[0x34AC];
    s16 frame;
} Game_b004_01E009F0;

typedef struct {
    u8 pad0[0x28];
    u8 c0[4];
    u8 pad2C[6];
    s16 t;
    s16 sub;
    s16 state;
    s16 h38;
} Obj_b004_01E009F0;

static s32 func_01E009F0_b004(Game_b004_01E009F0 *g, Obj_b004_01E009F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    func_001076F0(o->c0, 0x9F, 0, 0x3F);
    if (o->state == 1) {
        o->c0[3] = 0;
        o->sub = 0;
        if (g->frame < 0x4F) {
            o->h38 = 6;
        } else {
            o->h38 = 0x16;
        }
        o->state = 2;
    }
    if (o->t < 2) {
        o->c0[3] += 0x50;
    } else if (o->c0[3] > 0xB) {
        o->c0[3] -= 0xA;
    } else {
        o->state = 0;
    }
    if (o->sub < 7) {
        o->sub++;
    }
    if (o->t % 3 == 1) {
        if (o->h38 != 0) {
            o->h38--;
        }
    }
    o->t++;
    if (g->frame == 0x53) {
        o->c0[3] = 0x20;
    }
    if (g->frame == 0x54) {
        o->state = 0;
    }
    return 0;
}

typedef struct {
    f32 x, y, z, w;
} Vec_b004_01E00B40;

static s32 func_01E00B40_b004(Vec_b004_01E00B40 *trail, s32 n, s32 arg2) {
    extern s32 func_001F53A0();
    s32 k;
    Vec_b004_01E00B40 *dst;
    Vec_b004_01E00B40 *src;
    Vec_b004_01E00B40 pos;
    s32 i;

    src = trail;
    k = n - 1;
    dst = trail;
    src--;
    func_001F5620(func_001F53A0(trail), arg2, (s32)&pos);
    for (i = 0; i < n; i++) {
        if (k != 0) {
            dst->x = src->x;
            dst->y = src->y;
            dst->z = src->z;
        } else {
            dst->x = pos.x;
            dst->y = pos.y;
            dst->z = pos.z;
        }
        dst--;
        src--;
        k--;
    }
    return 0;
}

/* shape b004:01E00C10, 9 insns: asks func_001F6160 for a pair of ints and returns the second as a float */

static f32 func_01E00C10_b004(s32 arg0) {
    extern void func_001F6160(s32, s32 *);
    s32 v[4];

    func_001F6160(arg0, v);
    return v[1];
}

INCLUDE_ASM("asm/nonmatchings/mod/b004", func_01E00C40_b004);

/* shape b004:01E012B0, 80 insns: c035:01E01150 family: take the first free glow slot of 200 (0x40 bytes each, at ctx+0x100), clear it, give it the scene colour twice, position, turns, two angles and both arguments; returns 1 when it got one */

typedef struct {
    u8 pad0[0x10];
    s32 w10;
    s32 w14;
    s32 w18;
    u8 pad1C[4];
    s32 w20;
    s32 w24;
    u8 col[4];
    u8 col2[4];
    s16 h30;
    u8 pad32[4];
    s16 used;
    u8 pad38[2];
    s16 ang;
    u8 pad3C[4];
} Glow_b004_01E012B0;

typedef struct {
    u8 pad0[0x80];
    u8 pos[0x20];
    s32 rot[3];
    u8 padAC[0x100 - 0xAC];
    Glow_b004_01E012B0 slot[200];
    u8 padEnd[0x3454 - 0x100 - 200 * 0x40];
    u8 r;
    u8 g;
    u8 b;
    u8 a;
    u8 pad3458[0x48];
    s16 ang;
    u8 pad34A2[6];
    s16 h30;
} Ctx_b004_01E012B0;

static s32 func_01E012B0_b004(Ctx_b004_01E012B0 *ctx, s32 arg1, s32 arg2) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106AB0(void *, void *, s32);
    s16 i;
    Glow_b004_01E012B0 *s;

    s = NULL;
    for (i = 0; i < 200; i++) {
        if (ctx->slot[i].used == 0) {
            func_00195108(&ctx->slot[i], 0x40);
            ctx->slot[i].used = 1;
            s = &ctx->slot[i];
            i = 200;
        }
    }
    if (s != NULL) {
        func_001076F0(s->col, ctx->r, ctx->g, ctx->b);
        s->col[3] = ctx->a;
        func_001076F0(s->col2, ctx->r, ctx->g, ctx->b);
        s->col2[3] = ctx->a;
        func_00106AB0(s, ctx->pos, 0);
        s->w10 = ctx->rot[0];
        s->w14 = ctx->rot[1];
        s->w18 = ctx->rot[2];
        s->ang = ctx->ang;
        s->h30 = ctx->h30;
        s->w20 = arg2;
        s->w24 = arg1;
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b004", func_01E013F0_b004);

INCLUDE_ASM("asm/nonmatchings/mod/b004", func_01E01860_b004);

INCLUDE_ASM("asm/nonmatchings/mod/b004", func_01E01A00_b004);

/* shape b004:01E01DA0, 89 insns: draws a sprite: mode 0 builds the packet (texture page 0x99 frame from the object, its colour,
   the scene texture); other modes turn it at random, place it at the object's point, make a square of its size and queue it
   at its depth */

typedef struct {
    s16 x, y, z;
    u8 pad6[0x22];
    u8 c0[4];
    u8 pad2C[8];
    s16 sub;
    u8 pad36[2];
    s16 size;
} Obj_b004_01E01DA0;

typedef struct {
    u8 pad0[0xFC];
    void *tex;
    u8 pad100[0x345C - 0x100];
    s32 ot;
    u8 pad3460[0x24];
    f32 depth;
} Game_b004_01E01DA0;

static void func_01E01DA0_b004(Game_b004_01E01DA0 *g, Obj_b004_01E01DA0 *o, void *p, s32 mode) {
    extern void func_00106080(void *, s32, s16, void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_00109380(void *, s32);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f pos;
    s16 rect[8];
    f32 m[16];
    s32 rot[4];
    f32 s;

    func_00207500();
    if (mode == 0) {
        func_00106080(rect, 0x99, o->sub, rect);
        func_00109270(p, 0, 0);
        func_00107790(p, o->c0, 0);
        func_00108500(p, rect, 0);
        func_00208700(p, g->tex, 1);
    } else {
        func_00205C40((s32)rot);
        pos.x = o->x;
        pos.y = o->y;
        pos.z = o->z;
        func_00108EF0(m, NULL, rot, &pos);
        s = o->size;
        func_00108CE0(quad, s, s);
        if (func_00205630(quad, 0x70000000, m, p, &g->depth) != 0) {
            func_00109380(p, 0);
            func_002075F0(p, g->ot, (u32)g->depth);
        }
    }
}

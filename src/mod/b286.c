#include "common.h"

/* shape b008:01E00080, 273 insns, 45 copies: the 4-mode version of b003:01E00080 (texture coordinates of a
   sprite quad from a rectangle). Callers rely on it being static in their file. */

typedef struct Rect_b008_01E00080 {
    s16 x, y, w, h;
} Rect_b008_01E00080;

typedef struct Uv_b008_01E00080 {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad4;
    u64 xyz;
} Uv_b008_01E00080;

typedef struct Pk_b008_01E00080 {
    u8 pad0[0x18];
    Uv_b008_01E00080 c[4];
} Pk_b008_01E00080;

static void func_01E00080_b286(Pk_b008_01E00080 *p, Rect_b008_01E00080 *r, s32 mode) {
    if (mode == 0) {
        p->c[0].u = (r->x) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[1].u = (r->x + r->w) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[2].u = (r->x) << 4;
        p->c[2].v = (r->y + r->h) << 4;
        p->c[3].u = (r->x + r->w) << 4;
        p->c[3].v = (r->y + r->h) << 4;
    } else if (mode == 1) {
        p->c[0].u = (r->x) << 4;
        p->c[0].v = (r->y + r->h) << 4;
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y + r->h) << 4;
        p->c[3].u = (r->x + r->w) << 4;
        p->c[3].v = (r->y) << 4;
    } else if (mode == 2) {
        p->c[2].u = (r->x) << 4;
        p->c[2].v = (r->y) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y + r->h) << 4;
        p->c[1].u = (r->x + r->w) << 4;
        p->c[1].v = (r->y + r->h) << 4;
    } else {
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y + r->h) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y + r->h) << 4;
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b286", func_01E004D0_b286);

/* shape b286:01E009B0, 99 insns: an orange or teal (by kind) streak: frame 15 growing by 4, random tilt 0..0x3FFF, turn and
   sub-frame 0..6; alpha up by 0x50 for 2 frames, then down by 13 once grown past 15, and by 15 when the scene timer drops under 10 */

typedef struct {
    u8 pad0[0x6A80];
    s32 timer;
} Scene_b286_01E009B0;

typedef struct {
    u8 pad0[6];
    s16 h6;
    u8 pad8[8];
    s32 rot0;
    s32 rot1;
    u8 pad18[0x10];
    u8 c0[4];
    u8 pad2C[4];
    s16 kind;
    s16 t;
    s16 sub;
    s16 state;
    s16 h38;
} Obj_b286_01E009B0;

static s32 func_01E009B0_b286(Scene_b286_01E009B0 *g, Obj_b286_01E009B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    s32 base;

    if (o->state == 1) {
        o->h38 = 0xF;
        base = 0;
        o->rot0 = func_0019A5C8() % 0x4000 + base;
        o->rot1 = func_0019A5C8() % 65535;
        o->sub = func_0019A5C8() % 7;
        o->state = 2;
        o->h6 = 1;
        if (o->kind == 0) {
            func_001076F0(o->c0, 0x80, 0x40, 0);
        } else {
            func_001076F0(o->c0, 0, 0x80, 0x80);
        }
    }
    if (o->t < 2) {
        if (o->c0[3] < 0xA0) {
            o->c0[3] += 0x50;
        }
    } else {
        if (o->h38 > 0xF) {
            if (o->c0[3] > 0xE) {
                o->c0[3] -= 0xD;
            } else {
                o->state = 0;
            }
        }
        if (g->timer < 0xA) {
            if (o->c0[3] > 0x10) {
                o->c0[3] -= 0xF;
            } else {
                o->state = 0;
            }
        }
    }
    o->t++;
    o->h38 += 4;
    return 0;
}

/* shape b286:01E00B40, 70 insns: an orange flame: set up once (reads the model's point, clears its y turn), alpha up by
   0x40 for 2 frames, then down by 9; frame 50; fades faster (13) while the game state is below 15; rises 5 a frame */

typedef struct {
    u8 pad0[0x6A80];
    s32 state;
} Game_b286_01E00B40;

typedef struct {
    u8 pad0[0xE];
    s16 y;
    u8 pad10[4];
    s32 rot1;
    u8 pad18[0x10];
    u8 c0[4];
    u8 pad2C[6];
    s16 t;
    s16 h34;
    s16 state;
    s16 h38;
} Obj_b286_01E00B40;

static s32 func_01E00B40_b286(Game_b286_01E00B40 *g, Obj_b286_01E00B40 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F6160(s32, void *);
    Vec4f v;

    func_001076F0(o->c0, 0x80, 0x40, 0);
    if (o->state == 1) {
        func_001F6160(func_001F53A0(), &v);
        o->rot1 = 0;
        o->h34 = 0;
        o->state = 2;
        o->c0[3] = 0;
    }
    if (o->t < 2) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x40;
        }
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    o->h38 = 0x32;
    o->t++;
    if (g->state < 0xF) {
        if (o->c0[3] > 0xE) {
            o->c0[3] -= 0xD;
        } else {
            o->state = 0;
        }
    }
    o->y += 5;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b286", func_01E00C60_b286);

/* shape b286:01E00F90, 101 insns: an orange ember (size 13, frame 2) at two random angles drifting 13 a tick on all three axes (sine table ctx+0x6AE8): alpha 0x80 for 10 ticks, then out by 10 and ends */

typedef struct {
    u8 pad0[8];
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
} Glow_b286_01E00F90;

typedef struct {
    u8 pad[0x6ae8];
    u8 sin[1];
} Game_b286_01E00F90;

static s32 func_01E00F90_b286(Game_b286_01E00F90 *g, Glow_b286_01E00F90 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s16 func_001A22C0(f32);

    if (o->mode == 1) {
        o->f38 = 13;
        o->kind = 2;
        func_001076F0(o->col, 0x60, 0x40, 0);
        o->h30 = func_0019A5C8() % 360;
        o->ang = func_0019A5C8() % 360;
        o->mode = 2;
    }
    if (o->tick < 10) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    o->tick++;
    o->h8 = func_001A22C0(o->h8 + 13.0f * func_00108030(g->sin, o->ang, 0));
    o->hA = func_001A22C0(o->hA + 13.0f * func_00108030(g->sin, o->h30, 1));
    o->hC = func_001A22C0(o->hC + 13.0f * func_00108030(g->sin, o->ang, 1));
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b286", func_01E01130_b286);

/* shape b286:01E013F0, 54 insns: volume fade: starts at 0x80; while the game counter at 0x6A80 is over 0x1E it drops by
   10 to 0x30, otherwise it rises by 10 (clamped) and stops at 0x80; func_001F6D00 gets it when the counter is 1,
   else the volume */

typedef struct {
    u8 pad0[0x6A80];
    s32 count;
} Game_b286_01E013F0;

typedef struct {
    u8 pad0[0x30];
    s16 v;
    u8 pad32[0x4];
    s16 mode;
} Fx_b286_01E013F0;

static s32 func_01E013F0_b286(Game_b286_01E013F0 *g, Fx_b286_01E013F0 *o) {
    extern void func_001F6D00(u8);

    if (o->mode == 1) {
        o->v = 0x80;
        o->mode = 2;
    }
    if (g->count > 0x1E) {
        if (o->v > 0x30) {
            o->v -= 10;
        } else {
            o->v = 0x30;
        }
    } else {
        if (o->v < 0x80) {
            o->v += 10;
        } else {
            o->v = 0x80;
            o->mode = 0;
        }
        if (o->v > 0x80) {
            o->v = 0x80;
        }
    }
    if (g->count == 1) {
        func_001F6D00(o->v);
    } else {
        func_001F6D00(o->v);
    }
    return 0;
}

/* shape b194:01E01AE0: b018:01E02DB0 with other constants (chatG) */

extern f32 D_01E02500_b286;
extern f32 D_01E02508_b286;

static s32 func_01E014D0_b286(void) {
    f32 a;
    f32 b;

    *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E02500_b286;
    *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E02508_b286;
    func_001F7170(3, 0, (s32)&a, (s32)&b, 0);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b286", func_01E01520_b286);

/* shape b286:01E01990, 72 insns: twin of b046:01E03E20: take the first free slot of the 420-slot pool, clear it, give
   it the scene's colour twice, the scene matrix, the scene's value 0x6ADE and the two arguments; returns 1 if a
   slot was found */

typedef struct {
    u8 pad[0x20];
    s32 b;
    s32 a;
    u8 c0[4];
    u8 c1[4];
    s16 v;
    u8 pad32[0x4];
    s16 used;
    u8 pad38[0x8];
} Slot_b286_01E01990;

typedef struct {
    u8 pad[0x80];
    u8 m[0xA0];
    Slot_b286_01E01990 s[420];
    u8 pad6A20[0x64];
    u8 r, g, b, a;
    u8 pad6A88[0x56];
    s16 v;
} Pool_b286_01E01990;

static s32 func_01E01990_b286(Pool_b286_01E01990 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b286_01E01990 *s = NULL;
    s16 i;
    s32 ret;

    for (i = 0; i < 420; i++) {
        if (o->s[i].used == 0) {
            func_00195108(&o->s[i], 0x40);
            o->s[i].used = 1;
            s = &o->s[i];
            i = 420;
        }
    }
    if (s != NULL) {
        func_001076F0(s->c0, o->r, o->g, o->b);
        s->c0[3] = o->a;
        func_001076F0(s->c1, o->r, o->g, o->b);
        s->c1[3] = o->a;
        func_00106AB0(s, o->m, 0);
        ret = 1;
        s->v = o->v;
        s->b = b;
        s->a = a;
    } else {
        ret = 0;
    }
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/mod/b286", func_01E01AB0_b286);

/* shape b286:01E01D40, 158 insns: variant of b112:01E039F0 (flat ring of 9 quads, each 2 wide) with the texture at 0x11C, the
   target/depth/trig table at 0x6A8C/0x6AB4/0x6AE8, and an additive blend (0x80, 0x42) when the anim's w is set */

typedef struct {
    f32 x, y, z, w;
} Vec_b286_01E01D40;

typedef struct {
    s16 x, y, z;
    s16 w;
    u8 pad08[8];
    u8 rot[0x18];
    u8 col[0xC];
    s16 h34;
    u8 pad36[2];
    s16 radius;
    s16 start;
} Anim_b286_01E01D40;

typedef struct {
    u8 pad00[0x11C];
    s32 texture;
    u8 pad120[0x6A8C - 0x120];
    s32 target;
    u8 pad31B0[0x6AB4 - 0x6A90];
    f32 depth;
    u8 pad31CC[0x6AE8 - 0x6AB8];
    u8 trig[1];
} Game_b286_01E01D40;

static void func_01E01D40_b286(Game_b286_01E01D40 *g, Anim_b286_01E01D40 *an, void *p, s32 mode) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_002086D0(void *, u64);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec_b286_01E01D40 quad[4];
    Vec_b286_01E01D40 pos;
    Vec_b286_01E01D40 scale;
    f32 m[16];
    f32 rm[4];
    s32 k;
    s32 a;
    s16 j;

    j = 0;
    if (mode == 0) {
        func_00106080(rm, 0x97, an->h34, rm);
        func_00109270(p, 0, 0);
        func_00107790(p, an->col, 0);
        func_00108500(p, rm, 0);
        func_00208700(p, g->texture, 1);
    } else {
        if (an->w != 0) {
            func_002086D0(p, 0x8000000042);
        }
        pos.x = an->x;
        pos.y = an->y;
        pos.z = an->z;
        scale.x = 1.0f;
        scale.y = 1.5f;
        scale.z = 1.0f;
        func_00108EF0(m, &scale, an->rot, &pos);
        quad[0].y = 0.0f;
        quad[1].y = 0.0f;
        quad[2].y = 0.0f;
        quad[3].y = 0.0f;
        for (k = 0; k < 9; k++) {
            a = an->start + j;
            quad[2].x = an->radius * func_00108030(g->trig, a, 1);
            quad[2].z = an->radius * func_00108030(g->trig, a, 0);
            quad[0].x = 0.0f;
            quad[0].z = 0.0f;
            a = j + (an->start + 2);
            quad[3].x = an->radius * func_00108030(g->trig, a, 1);
            quad[3].z = an->radius * func_00108030(g->trig, a, 0);
            quad[1].x = 0.0f;
            quad[1].z = 0.0f;
            if (func_00205630(quad, 0x70000000, m, p, &g->depth) != 0) {
                func_002075F0(p, g->target, (u32)g->depth);
            }
            j += 40;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b286", func_01E01FC0_b286);

INCLUDE_ASM("asm/nonmatchings/mod/b286", func_01E022A0_b286);

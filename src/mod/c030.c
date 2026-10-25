#include "common.h"

INCLUDE_ASM("asm/nonmatchings/mod/c030", func_01E00080_c030);

/* shape c030:01E00B60, 179 insns: c560:01E02520 family falling column segment: its angle turns back by 18 (wrapped past
   -359), the bottom drops by 5 to the floor while the top follows within 13, then the top closes down and ends it
   (clearing the linked node); while it may still spawn and its top is under 50 it hands the scene one more segment
   (this function) at its place, angle + 35, grey 0x10, numbered on, side by flag 0x78, once the scene timer is 23 or
   more; both alphas rise by 8 to 0x40 for 8 frames, fade by 10 when low, else rise by 7 to 0x80 (the second only
   while linked) */

typedef struct {
    u8 pad0[0x50];
    s32 w50;
} Link_c030_01E00B60;

typedef struct {
    u8 pad0[4];
    f32 f4;
    u8 pad8[0xC];
    f32 f14;
    u8 pad18[0x3C];
    Link_c030_01E00B60 *link;
    u8 pad58[8];
    u8 col[4];
    u8 col2[4];
    s16 h68;
    s16 h6A;
    s16 h6C;
    u8 pad6E[2];
    s16 h70;
    s16 ang;
    s16 h74;
    u8 pad76[2];
    s16 h78;
} Seg_c030_01E00B60;

typedef struct {
    u8 pad0[0xF0];
    s32 timer;
    u8 col[4];
    u8 padF8[8];
    Seg_c030_01E00B60 *parent;
    u8 pad104[4];
    f32 px, py, pz;
    u8 pad114[0x1C0];
    s16 h2D4;
    s16 ang;
    u8 pad2D8[2];
    s16 h2DA;
    u8 pad2DC[2];
    s16 h2DE;
    u8 pad2E0[4];
    s16 frame;
    u8 pad2E6[4];
    s16 h2EA;
    u8 pad2EC[4];
    s16 h2F0;
} Scene_c030_01E00B60;

static s32 func_01E00B60_c030(Scene_c030_01E00B60 *g, Seg_c030_01E00B60 *o) {
    extern void c030_01E018C0(Scene_c030_01E00B60 *, void *);
    extern s16 func_001A22C0(f32);

    o->ang -= 18;
    if (o->ang < -359) {
        o->ang %= 360;
    }
    o->h6A = func_001A22C0(o->f4);
    o->h6C = func_001A22C0(o->f14);
    if (o->f4 > 0.0f) {
        o->f4 -= 5.0f;
        if (o->f14 - o->f4 >= 13.0f) {
            o->f14 -= 5.0f;
        }
    } else {
        o->f14 -= 5.0f;
        if (o->f14 < o->f4) {
            o->f14 = o->f4;
            if (o->link != NULL) {
                o->link->w50 = 0;
            }
            o->h68 = 0;
        }
    }
    if (o->h74 > 0 && o->f14 < 50.0f) {
        g->parent = o;
        g->px = o->h6A;
        g->py = o->h6C;
        g->col[3] = 0;
        g->col[0] = 0x10;
        g->col[1] = 0x10;
        g->col[2] = 0x10;
        g->h2DA = 1;
        g->pz = o->f14;
        g->h2DE = 1;
        g->ang = o->ang + 35;
        if (o->h78 != 0) {
            g->h2F0 = 0;
        } else {
            g->h2F0 = 1;
        }
        g->h2D4 = o->h70;
        g->h2EA = 7;
        if (g->timer > 22) {
            c030_01E018C0(g, func_01E00B60_c030);
        }
        o->h74 = 0;
    }
    if (g->frame < 8) {
        if (o->col[3] < 0x40) {
            o->col[3] += 8;
        }
        if (o->col2[3] < 0x40) {
            o->col2[3] += 8;
        }
    } else if (o->f14 < 15.0f) {
        if (o->col[3] > 16) {
            o->col[3] -= 10;
        }
        if (o->col2[3] > 16) {
            o->col2[3] -= 10;
        }
    } else {
        if (o->col[3] < 0x80) {
            o->col[3] += 7;
        }
        if (o->link != NULL) {
            if (o->col2[3] < 0x80) {
                o->col2[3] += 7;
            }
        }
    }
    return 0;
}

/* shape c030:01E00E30, 182 insns: c030:01E00B60's segment handing on in grey 0x70 with the scene turn (0x80) cleared,
   through the other spawner (0x1E01AE0), alphas capped at 0xC0 */

typedef struct {
    u8 pad0[0x50];
    s32 w50;
} Link_c030_01E00E30;

typedef struct {
    u8 pad0[4];
    f32 f4;
    u8 pad8[0xC];
    f32 f14;
    u8 pad18[0x3C];
    Link_c030_01E00E30 *link;
    u8 pad58[8];
    u8 col[4];
    u8 col2[4];
    s16 h68;
    s16 h6A;
    s16 h6C;
    u8 pad6E[2];
    s16 h70;
    s16 ang;
    s16 h74;
    u8 pad76[2];
    s16 h78;
} Seg_c030_01E00E30;

typedef struct {
    u8 pad0[0x80];
    s32 r80, r84, r88;
    u8 pad8C[0x64];
    s32 timer;
    u8 col[4];
    u8 padF8[8];
    Seg_c030_01E00E30 *parent;
    u8 pad104[4];
    f32 px, py, pz;
    u8 pad114[0x1C0];
    s16 h2D4;
    s16 ang;
    u8 pad2D8[2];
    s16 h2DA;
    u8 pad2DC[2];
    s16 h2DE;
    u8 pad2E0[4];
    s16 frame;
    u8 pad2E6[4];
    s16 h2EA;
    u8 pad2EC[4];
    s16 h2F0;
} Scene_c030_01E00E30;

static s32 func_01E00E30_c030(Scene_c030_01E00E30 *g, Seg_c030_01E00E30 *o) {
    extern void c030_01E01AE0(Scene_c030_01E00E30 *, void *);
    extern s16 func_001A22C0(f32);

    o->ang -= 18;
    if (o->ang < -359) {
        o->ang %= 360;
    }
    o->h6A = func_001A22C0(o->f4);
    o->h6C = func_001A22C0(o->f14);
    if (o->f4 > 0.0f) {
        o->f4 -= 5.0f;
        if (o->f14 - o->f4 >= 13.0f) {
            o->f14 -= 5.0f;
        }
    } else {
        o->f14 -= 5.0f;
        if (o->f14 < o->f4) {
            o->f14 = o->f4;
            if (o->link != NULL) {
                o->link->w50 = 0;
            }
            o->h68 = 0;
        }
    }
    if (o->h74 > 0 && o->f14 < 50.0f) {
        g->parent = o;
        g->px = o->h6A;
        g->py = o->h6C;
        g->col[3] = 0;
        g->col[0] = 0x70;
        g->col[1] = 0x70;
        g->col[2] = 0x70;
        g->h2DA = 1;
        g->pz = o->f14;
        g->h2DE = 1;
        g->r84 = 0;
        g->r80 = 0;
        g->r88 = 0;
        g->ang = o->ang + 35;
        g->h2EA = 7;
        if (o->h78 != 0) {
            g->h2F0 = 0;
        } else {
            g->h2F0 = 1;
        }
        g->h2D4 = o->h70;
        if (g->timer > 22) {
            c030_01E01AE0(g, func_01E00E30_c030);
        }
        o->h74 = 0;
    }
    if (g->frame < 8) {
        if (o->col[3] < 0x40) {
            o->col[3] += 8;
        }
        if (o->col2[3] < 0x40) {
            o->col2[3] += 8;
        }
    } else if (o->f14 < 15.0f) {
        if (o->col[3] > 16) {
            o->col[3] -= 10;
        }
        if (o->col2[3] > 16) {
            o->col2[3] -= 10;
        }
    } else {
        if (o->col[3] < 0xC0) {
            o->col[3] += 7;
        }
        if (o->link != NULL) {
            if (o->col2[3] < 0xC0) {
                o->col2[3] += 7;
            }
        }
    }
    return 0;
}

/* shape c030:01E01110, 98 insns, 1 copy (C030_CARD_EAREY_1): sets up 22 models (0..10 and 256..266): random speed 1..5, frame 5..12, turn 256..6399 and
   tilt -1024..1023; the current model gets its flag set if it has one; each model present takes its position and turn */

typedef struct {
    f32 pos[8];
    f32 rot[2];
    s32 frame;
    u8 pad2C[8];
    s32 turn;
    s32 tilt;
    u8 pad3C[0x18];
    f32 speed;
    u8 pad58[0x18];
} Ent_c030_01E01110;

typedef struct {
    u8 pad0[0x22B0];
    Ent_c030_01E01110 ents[22];
} Ctx_c030_01E01110;

static void func_01E01110_c030(Ctx_c030_01E01110 *ctx) {
    extern s32 func_001F5380();
    extern s32 func_001F5AF0(s32);
    extern f32 func_001F5970(s32, s32);
    extern s32 func_001F5EC0(s32);
    extern void func_001F5F90(s32, void *);
    extern void func_001F6210(s32, void *);
    s16 i;
    Ent_c030_01E01110 *e;
    s32 id;

    func_001F5380(ctx);
    for (i = 0; i < 0x16; i++) {
        id = i;
        if (id > 10) {
            id += 0xF5;
        }
        e = &ctx->ents[i];
        e->speed = (func_0019A5C8() % 26 + 9) / 6;
        e->frame = func_0019A5C8() % 8 + 5;
        e->turn = func_0019A5C8() % 6144 + 0x100;
        e->tilt = func_0019A5C8() % 0x800 - 0x400;
        if (id == func_001F5380()) {
            if (func_001F5AF0(id) != 0) {
                func_001F5970(id, 1);
            }
        }
        if (func_001F5EC0(id) != 0) {
            func_001F5F90(id, e->pos);
            func_001F6210(id, e->rot);
        }
    }
}

/* shape c030:01E012A0, 155 insns: c030's camera step for one view (id, or id + 245 past 10): when that view is the active
   one and is live, from scene time 15 it lowers the view's height by 4 (not below 0) and slides its depth by a 24th of
   the camera speed (backwards for ids under 11); from time 28 it eases the view's three offsets down by 0.02 to 0; from
   time 10 it turns the view by 0x1000; then the view is committed */

typedef struct {
    u8 pad0[0x2E4];
    s16 time;
} Ctx_c030_01E012A0;

static s32 func_01E012A0_c030(Ctx_c030_01E012A0 *g, s32 unused, s32 id) {
    extern s32 func_001F5380(void);
    extern s32 func_001F5EC0(s32);
    extern void func_00107450(s32, s32, f32);
    extern void func_001F5F90(s32, void *);
    extern f32 func_001F5860(s32);
    extern void func_001F5F00(s32, void *);
    extern void func_001F5D70(s32, void *);
    extern void func_001F5D10(s32, void *);
    extern void func_001F6210(s32, void *);
    extern void func_001F60D0(s32, void *);
    extern void func_001F5AF0(s32);
    f32 v[4];
    f32 w[4];
    s32 r[4];
    s32 k;

    k = id;
    if (id > 10) {
        k = id + 245;
    }
    if (k != func_001F5380()) {
        return 0;
    }
    if (func_001F5EC0(k)) {
        if (g->time > 14) {
            func_00107450(k, 0, 0.08f);
            func_001F5F90(k, v);
            v[1] -= 4.0f;
            if (v[1] < 0.0f) {
                v[1] = 0.0f;
            }
            if (id < 11) {
                v[2] += -func_001F5860(func_001F5380()) / 24.0f;
            } else {
                v[2] += func_001F5860(func_001F5380()) / 24.0f;
            }
            func_001F5F00(k, v);
        }
        if (g->time >= 28) {
            func_001F5D70(k, w);
            if (!(w[0] <= 0.0f)) {
                w[0] -= 0.02f;
            } else {
                w[0] = 0.0f;
            }
            if (!(w[1] <= 0.0f)) {
                w[1] -= 0.02f;
            } else {
                w[1] = 0.0f;
            }
            if (!(w[2] <= 0.0f)) {
                w[2] -= 0.02f;
            } else {
                w[2] = 0.0f;
            }
            func_001F5D10(k, w);
        }
        if (g->time > 9) {
            func_001F6210(k, r);
            r[1] += 0x1000;
            func_001F60D0(k, r);
        }
    }
    func_001F5AF0(k);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/c030", func_01E01510_c030);

/* shape c030:01E018C0, 133 insns: c030 trail link spawner (c560:01E01C50 family, 65 slots of 0x7C at ctx+0x334): first free slot (marked slot+1), both colours and alpha from the context, its vector, sizes as shorts, height 18 above, both capped at 50, chained after the context's last piece and becomes it; draws with c030:01E02170 */

/* OVL_WARM */

typedef struct {
    u8 r, g, b, a;
} Col_c030_01E018C0;

typedef struct Ent_c030_01E018C0 {
    u8 pad0[4];
    f32 f4;
    u8 pad8[0xC];
    f32 f14;
    u8 pad18[0x18];
    Vec4f v;
    u8 pad40[0x10];
    struct Ent_c030_01E018C0 *prev;
    struct Ent_c030_01E018C0 *next;
    void (*cb)(void);
    s32 arg;
    Col_c030_01E018C0 col0;
    Col_c030_01E018C0 col1;
    s16 used;
    s16 f6A;
    s16 f6C;
    s16 f6E;
    s16 f70;
    s16 f72;
    s16 f74;
    u8 pad76[2];
    s16 f78;
    u8 pad7A[2];
} Ent_c030_01E018C0;

typedef struct {
    u8 pad0[0x80];
    Vec4f v;
    u8 pad90[0xF4 - 0x90];
    u8 rgba[4];
    u8 padF8[8];
    Ent_c030_01E018C0 *last;
    u8 pad104[4];
    f32 f108;
    f32 f10C;
    f32 f110;
    u8 pad114[0x2D4 - 0x114];
    s16 f2D4;
    s16 f2D6;
    u8 pad2D8[2];
    s16 f2DA;
    u8 pad2DC[2];
    s16 f2DE;
    u8 pad2E0[0x2F0 - 0x2E0];
    s16 f2F0;
    u8 pad2F2[0x334 - 0x2F2];
    Ent_c030_01E018C0 ent[65];
} Ctx_c030_01E018C0;

static void func_01E018C0_c030(Ctx_c030_01E018C0 *g, s32 arg) {
    extern void c030_01E02170(void);
    extern void func_00195108(void *, s32);
    extern void func_001076F0();
    s16 i;
    Ent_c030_01E018C0 *e = NULL;
    Ent_c030_01E018C0 *p;
    f32 h;
    f32 d;

    for (i = 0; i < 65; i++) {
        if (g->ent[i].used == 0) {
            e = &g->ent[i];
            func_00195108(e, 0x7C);
            g->ent[i].used = i + 1;
            i = 65;
        }
    }
    if (e != NULL) {
        d = 18.0f;
        func_001076F0(&e->col0, g->rgba[0], g->rgba[1], g->rgba[2]);
        e->col0.a = g->rgba[3];
        func_001076F0(&e->col1, g->rgba[0], g->rgba[1], g->rgba[2]);
        e->col1.a = g->rgba[3];
        e->v = g->v;
        e->f6A = (s16)g->f108;
        e->f6C = (s16)g->f10C;
        e->f72 = g->f2D6;
        e->prev = g->last;
        e->f6E = g->f2DE;
        if (e->prev == NULL) {
            h = g->f110;
            e->f4 = h;
            e->f14 = h + d;
        } else {
            h = g->f110;
            e->f4 = h;
            e->f14 = h + d;
        }
        e->f70 = g->f2D4;
        if (50.0f < e->f4) {
            e->f4 = 50.0f;
        }
        if (50.0f < e->f14) {
            e->f14 = 50.0f;
        }
        e->f78 = g->f2F0;
        e->prev = g->last;
        p = e->prev;
        if (p != NULL) {
            p->next = e;
        }
        e->cb = c030_01E02170;
        e->arg = arg;
        e->f74 = g->f2DA;
        g->last = e;
    }
}

/* shape c030:01E01AE0, 134 insns: c030:01E018C0 with f70 copied after the caps and the c030:01E01D00 draw callback */

/* OVL_WARM */

typedef struct {
    u8 r, g, b, a;
} Col_c030_01E01AE0;

typedef struct Ent_c030_01E01AE0 {
    u8 pad0[4];
    f32 f4;
    u8 pad8[0xC];
    f32 f14;
    u8 pad18[0x18];
    Vec4f v;
    u8 pad40[0x10];
    struct Ent_c030_01E01AE0 *prev;
    struct Ent_c030_01E01AE0 *next;
    void (*cb)(void);
    s32 arg;
    Col_c030_01E01AE0 col0;
    Col_c030_01E01AE0 col1;
    s16 used;
    s16 f6A;
    s16 f6C;
    s16 f6E;
    s16 f70;
    s16 f72;
    s16 f74;
    u8 pad76[2];
    s16 f78;
    u8 pad7A[2];
} Ent_c030_01E01AE0;

typedef struct {
    u8 pad0[0x80];
    Vec4f v;
    u8 pad90[0xF4 - 0x90];
    u8 rgba[4];
    u8 padF8[8];
    Ent_c030_01E01AE0 *last;
    u8 pad104[4];
    f32 f108;
    f32 f10C;
    f32 f110;
    u8 pad114[0x2D4 - 0x114];
    s16 f2D4;
    s16 f2D6;
    u8 pad2D8[2];
    s16 f2DA;
    u8 pad2DC[2];
    s16 f2DE;
    u8 pad2E0[0x2F0 - 0x2E0];
    s16 f2F0;
    u8 pad2F2[0x334 - 0x2F2];
    Ent_c030_01E01AE0 ent[65];
} Ctx_c030_01E01AE0;

static void func_01E01AE0_c030(Ctx_c030_01E01AE0 *g, s32 arg) {
    extern void c030_01E01D00(void);
    extern void func_00195108(void *, s32);
    extern void func_001076F0();
    s16 i;
    Ent_c030_01E01AE0 *e = NULL;
    Ent_c030_01E01AE0 *p;
    f32 h;
    f32 d;

    for (i = 0; i < 65; i++) {
        if (g->ent[i].used == 0) {
            e = &g->ent[i];
            func_00195108(e, 0x7C);
            g->ent[i].used = i + 1;
            i = 65;
        }
    }
    if (e != NULL) {
        d = 18.0f;
        func_001076F0(&e->col0, g->rgba[0], g->rgba[1], g->rgba[2]);
        e->col0.a = g->rgba[3];
        func_001076F0(&e->col1, g->rgba[0], g->rgba[1], g->rgba[2]);
        e->col1.a = g->rgba[3];
        e->v = g->v;
        e->f6A = (s16)g->f108;
        e->f6C = (s16)g->f10C;
        e->f72 = g->f2D6;
        e->prev = g->last;
        e->f6E = g->f2DE;
        if (e->prev == NULL) {
            h = g->f110;
            e->f4 = h;
            e->f14 = h + d;
        } else {
            h = g->f110;
            e->f4 = h;
            e->f14 = h + d;
        }
        if (50.0f < e->f4) {
            e->f4 = 50.0f;
        }
        if (50.0f < e->f14) {
            e->f14 = 50.0f;
        }
        e->f78 = g->f2F0;
        e->f70 = g->f2D4;
        e->prev = g->last;
        p = e->prev;
        if (p != NULL) {
            p->next = e;
        }
        e->cb = c030_01E01D00;
        e->arg = arg;
        e->f74 = g->f2DA;
        g->last = e;
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/c030", func_01E01D00_c030);

INCLUDE_ASM("asm/nonmatchings/mod/c030", func_01E02170_c030);

INCLUDE_ASM("asm/nonmatchings/mod/c030", func_01E02600_c030);

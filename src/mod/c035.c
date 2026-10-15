#include "common.h"

/* shape c035:01E00080, 161 insns: the c035 module's main step: red scene colour, sizes 20/130; on its first tick sets two colours, eight 160 values, and two scene points (-100,100) / (100,-100) and spawns c035:01E00310; at scene time 29 greys the colour and spawns c035:01E004D0; on the first tick spawns c035:01E00710; from time 17 drops seven c035:01E00580 at random spots 20 high; from 54 runs c035:01E009B0 twice a tick with a counter cycling 0..39 */

typedef struct {
    u8 pad0[0x80];
    f32 v80[4];
    u8 pad90[0x34D0 - 0x90];
    s32 time;
    u8 col[4];
    u8 pad34D8[0x3508 - 0x34D8];
    f32 f3508[8];
    u8 pad3528[0x354E - 0x3528];
    s16 h354E;
    u8 pad3550[4];
    s16 timer;
    u8 pad3556[8];
    s16 h355E;
    s16 h3560;
    s16 h3562;
    u8 pad3564[0x362C - 0x3564];
    s16 h362C;
    u8 pad362E[2];
    u8 c3630[4];
    u8 c3634[4];
} Ctx_c035_01E00080;

static void func_01E00080_c035(Ctx_c035_01E00080 *g) {
    extern void c035_01E00310(void);
    extern void c035_01E004D0(void);
    extern void c035_01E00580(void);
    extern void c035_01E00710(void);
    extern void c035_01E009B0(Ctx_c035_01E00080 *);
    extern void c035_01E00F60(Ctx_c035_01E00080 *, void (*)(void));
    extern void c035_01E01050(Ctx_c035_01E00080 *, void (*)(void));
    extern void c035_01E01150(Ctx_c035_01E00080 *, void (*)(void));
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106DD0(void *, f32, f32, f32);
    s32 i;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->h355E = 20;
    g->h362C = 130;
    g->timer++;
    if (g->timer == 1) {
        g->h3560 = 0;
        g->c3630[0] = 0x40;
        g->c3630[1] = 0x20;
        g->c3630[2] = 0x30;
        g->c3634[0] = 0xC0;
        g->c3634[1] = 0;
        g->c3634[2] = 0;
        g->col[0] = 0x30;
        g->col[1] = 0x30;
        g->col[2] = 0x30;
        g->col[0] = 0x80;
        g->col[1] = 0;
        g->col[2] = 0;
        g->col[3] = 0;
        for (i = 0; i < 8; i++) {
            g->f3508[i] = 160.0f;
        }
        g->h354E = 0;
        func_00106DD0(g->v80, -100.0f, 100.0f, 0.0f);
        g->h354E = 1;
        g->h354E = 2;
        g->h354E = 3;
        func_00106DD0(g->v80, 100.0f, -100.0f, 0.0f);
        c035_01E00F60(g, c035_01E00310);
    }
    if (g->time == 29) {
        func_001076F0(g->col, 0xBF, 0xBF, 0xBF);
        c035_01E01050(g, c035_01E004D0);
    }
    if (g->timer == 1) {
        c035_01E01050(g, c035_01E00710);
    }
    if (g->time > 16 && g->timer != 0) {
        for (i = 0; i < 7; i++) {
            g->v80[0] = func_0019A5C8() % 300 - 150;
            g->v80[1] = 20.0f;
            g->v80[2] = func_0019A5C8() % 300 - 150;
            c035_01E01150(g, c035_01E00580);
        }
    }
    if (g->time > 53 && g->timer != 0) {
        for (i = 0; i < 2; i++) {
            c035_01E009B0(g);
            g->h3562++;
            if (g->h3562 >= 40) {
                g->h3562 = 0;
            }
        }
    }
}

/* func_00108030 really takes an s16 angle (functions.h says s32): hide that prototype */

/* shape c035:01E00310, 109 insns: move the scene's three light/camera points (orbiting once the counter passes 16) */

typedef struct Obj_c035_01E00310 {
    u8 pad0[0x48];
    s16 h48;
    s16 ax;
    s16 ay;
} Obj_c035_01E00310;

typedef struct Scn_c035_01E00310 {
    u8 pad0[0x4D0];
    Vec4f *p0;
    Vec4f *p1;
    Vec4f *p2;
    u8 pad4DC[0x14];
    Vec4f v0;
    Vec4f v1;
    Vec4f v2;
    u8 pad520[0x2FB0];
    s32 count;
    u8 pad34D4[0x18C];
    u8 table[0x10];
} Scn_c035_01E00310;

static s32 func_01E00310_c035(Scn_c035_01E00310 *w, Obj_c035_01E00310 *o) {
    extern f32 func_00108030(void *table, s16 angle, s32 axis);
    if (w->count > 15) {
        o->ax += 0x28;
        o->ay -= 0x46;
        w->p1->x = w->v1.x + 6.0f * func_00108030(w->table, -o->ay, 1);
        w->p1->y = w->v1.y + 7.0f * func_00108030(w->table, -o->ax, 1);
        w->p1->z = w->v1.z + 6.0f * func_00108030(w->table, -o->ay, 0);
        func_001F9D80(0, w->p1);
    } else {
        w->p0->x = w->v0.x;
        w->p0->y = w->v0.y;
        w->p0->z = w->v0.z;
        func_001F9B20(0, w->p0);
        w->p1->x = w->v1.x;
        w->p1->y = w->v1.y;
        w->p1->z = w->v1.z;
        func_001F9D80(0, w->p1);
        w->p2->x = w->v2.x;
        w->p2->y = w->v2.y;
        w->p2->z = w->v2.z;
        func_001FAD60(0, w->p2);
    }
    if (w->count == 2) {
        o->h48 = 0;
    }
    return 0;
}

/* shape c035:01E004D0, 43 insns, 1 copy */

typedef struct Ctx_c035_01E004D0 {
    u8 pad[0x34D0];
    s32 phase;
} Ctx_c035_01E004D0;

typedef struct Obj_c035_01E004D0 {
    u8 pad0[0x43];
    u8 c43;
    u8 pad44[3];
    u8 c47;
    s16 f48;
    u8 pad4A[0x10];
    s16 t;
} Obj_c035_01E004D0;

static s32 func_01E004D0_c035(Ctx_c035_01E004D0 *ctx, Obj_c035_01E004D0 *o) {
    if (o->t < 8) {
        if (o->c43 < 0xC0) {
            o->c43 += 0x18;
        }
        if (o->c47 < 0xC0) {
            o->c47 += 0x18;
        }
    } else if (o->t >= 0xD) {
        if (o->c43 > 0xB) {
            o->c43 -= 10;
        }
        if (o->c47 > 0xB) {
            o->c47 -= 10;
        }
    }
    o->t++;
    if (ctx->phase == 2) {
        o->f48 = 0;
    }
    return 0;
}

/* shape c035:01E00580, 98 insns: a purple drifting mote: frame 20; alpha up by 9 to 0x60 for 10 frames, then down by 10 until
   it ends; sub-frame steps up to 6 every other frame; drifts 20 along its angle and bobs 20 by its second angle */

typedef struct {
    u8 pad0[0x3660];
    u8 sin[1];
} Game_c035_01E00580;

typedef struct {
    u8 pad0[8];
    s16 h8;
    s16 hA;
    s16 hC;
    u8 padE[0x1A];
    u8 c0[4];
    u8 pad2C[4];
    s16 bob;
    s16 t;
    s16 sub;
    s16 state;
    s16 h38;
    s16 ang;
} Obj_c035_01E00580;

static s32 func_01E00580_c035(Game_c035_01E00580 *g, Obj_c035_01E00580 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s16 func_001A22C0(f32);

    o->h38 = 0x14;
    func_001076F0(o->c0, 0x3F, 0x20, 0x6F);
    if (o->t < 0xA) {
        if (o->c0[3] < 0x60) {
            o->c0[3] += 9;
        }
    } else if (o->c0[3] > 0x10) {
        o->c0[3] -= 0xA;
    } else {
        o->state = 0;
    }
    o->t++;
    if (o->t % 2 == 1) {
        if (o->sub < 6) {
            o->sub++;
        }
    }
    o->h8 = func_001A22C0(o->h8 + 20.0f * func_00108030(g->sin, o->ang, 0));
    o->hA = func_001A22C0(o->hA + 20.0f * func_00108030(g->sin, o->bob, 1));
    o->hC = func_001A22C0(o->hC + 20.0f * func_00108030(g->sin, o->ang, 1));
    return 0;
}

/* shape c035:01E00710, 84 insns: b001:01E00900 twin: draws the fixed grey bar sprite, then ends itself at scene state 10 */

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
} Hdr_c035_01E00710;

typedef struct {
    Hdr_c035_01E00710 h;
    u8 r, g, b, a;
    f32 q;
    f32 s0, t0;
    u64 x0 : 16;
    u64 y0 : 16;
    u64 z0 : 24;
    u64 f0 : 8;
    f32 s1, t1;
    u64 x1 : 16;
    u64 y1 : 16;
    u64 z1 : 24;
    u64 f1 : 8;
    u8 tail[0x20];
} Pkt_c035_01E00710;

typedef struct {
    u8 pad[0x34D0];
    s32 state;
} Game_c035_01E00710;

typedef struct {
    u8 pad[0x48];
    s16 mode;
} Obj_c035_01E00710;

static s32 func_01E00710_c035(Game_c035_01E00710 *g, Obj_c035_01E00710 *o) {
    Pkt_c035_01E00710 p __attribute__((aligned(8)));

    ((Hdr_c035_01E00710 *)(s32)&p)->count = 0x26;
    ((Hdr_c035_01E00710 *)(s32)&p)->tag = 5;
    ((Hdr_c035_01E00710 *)(s32)&p)->regs = 0x42421;
    ((Hdr_c035_01E00710 *)(s32)&p)->pad = 0;
    p.r = 0x80;
    p.g = 0x80;
    p.b = 0x80;
    p.a = 0x60;
    p.q = 1.0f;
    p.x0 = 0x6BF8;
    p.y0 = 0x71F8;
    p.z0 = 0xFFFFFF;
    p.f0 = 0;
    p.x1 = 0x93F8;
    p.y1 = 0x8DF8;
    p.z1 = 0xFFFFFF;
    p.f1 = 0;
    p.s0 = 0.0f;
    p.t0 = 0.0f;
    p.s1 = 0.625f;
    p.t1 = 0.875f;
    func_002086D0(&p, ((u64)0x80 << 32) | 0x44);
    func_002087A0(&p, 1);
    func_002075F0((s32)&p, (s32)func_00207500(), 0);
    if (g->state == 10) {
        o->mode = 0;
    }
    return 0;
}

/* shape c035:01E00860, 82 insns: a two-voice sound fade: state 0 lowers the shared volume by its step until below -127,
   state 1 sets both voices' levels, state 2 raises the volume back to 0 (then frees both channel slots); the volume is
   applied to both voices each step */

typedef struct {
    s32 bank0;
    u8 pad4[4];
    s32 ch0;
    u8 padC[4];
    s32 active;
    s32 vol;
    s32 lv1;
    s32 lv0;
    s32 bank1;
    u8 pad24[4];
    s32 ch1;
    s32 step;
    s32 state;
} Fade_c035_01E00860;

typedef struct {
    u8 pad0[0x3564];
    s32 used[1][7];
} Snd_c035_01E00860;

static void func_01E00860_c035(Snd_c035_01E00860 *s, Fade_c035_01E00860 *f) {
    extern void func_001E23A0(s32, s32, s32);
    extern void func_001E2220(s32, s32, s32);

    if (f->state == 0) {
        f->vol -= f->step;
        func_001E23A0(f->bank0, f->ch0, f->vol);
        func_001E23A0(f->bank1, f->ch1, f->vol);
        if (f->vol < -0x7F) {
            f->state = 1;
        }
    } else if (f->state == 1) {
        func_001E2220(f->bank0, f->ch0, f->lv0);
        func_001E2220(f->bank1, f->ch1, f->lv1);
        f->state = 2;
    } else if (f->state == 2) {
        f->vol += f->step;
        if (f->vol >= 0) {
            f->active = 0;
            f->vol = 0;
            s->used[f->bank0][f->ch0] = 0;
            s->used[f->bank1][f->ch1] = 0;
        }
        func_001E23A0(f->bank0, f->ch0, f->vol);
        func_001E23A0(f->bank1, f->ch1, f->vol);
    }
}

/* shape c035:01E009B0, 113 insns: takes the current pair slot (0x40 bytes) if free, clears and marks it, then picks two random
   board cells and a delay 5..16; if both cells are free it claims them and looks up both pieces, otherwise it clears the
   slot's result */

typedef struct {
    s32 r0;
    u8 pad4[4];
    s32 c0;
    u8 padC[4];
    s32 result;
    u8 pad14[4];
    s32 p0;
    s32 p1;
    s32 r1;
    u8 pad24[4];
    s32 c1;
    s32 delay;
    u8 pad30[0x10];
} Pair_c035_01E009B0;

typedef struct {
    u8 pad0[0x550];
    Pair_c035_01E009B0 pairs[1];
    u8 pad590[0x3562 - 0x590];
    s16 cur;
    s32 used[7][7];
} Scene_c035_01E009B0;

static void func_01E009B0_c035(Scene_c035_01E009B0 *s) {
    extern void func_00195108(void *, s32);
    extern s32 func_001E22B0(s32, s32);
    Pair_c035_01E009B0 *p;

    if (s->pairs[s->cur].result == 0) {
        func_00195108(&s->pairs[s->cur], 0x40);
        s->pairs[s->cur].result = 1;
        p = &s->pairs[s->cur];
    } else {
        p = NULL;
    }
    if (p != NULL) {
        p->r0 = func_0019A5C8() % 7;
        p->c0 = func_0019A5C8() % 7;
        p->r1 = func_0019A5C8() % 7;
        p->c1 = func_0019A5C8() % 7;
        p->delay = func_0019A5C8() % 12 + 5;
        if (s->used[p->r0][p->c0] == 0 && s->used[p->r1][p->c1] == 0) {
            s->used[p->r1][p->c1] = 1;
            s->used[p->r0][p->c0] = 1;
            p->p0 = func_001E22B0(p->r0, p->c0);
            p->p1 = func_001E22B0(p->r1, p->c1);
            return;
        }
        p->result = 0;
    }
}

/* shape c035:01E00B80, 247 insns: the c035 module's main step: with a code it clears the scene, sets the scene step
   (c035:01E00080), fills the cosine table (0..90 degrees at ctx+0x3660), keeps the code and a 180-tick timer,
   texture (4,2) and the view (its eye, centre, relative and look pointers, look vector and copies of the first three);
   otherwise it runs the scene step and every live slot's handler (10 of 0x60 bytes), draws them at the camera point
   (func_001F9D30) turned a quarter, scale (0.5, 0.2, 0.5), two passes each; runs the 40 sound fades
   (c035:01E00860), then moves and draws the 150 effects (c035:01E00580, c035:01E013A0); counts the timer down and
   returns 2 from step 158 while more than 2 ticks remain, 8 when the timer ends */

typedef struct {
    f32 x, y, z, w;
} V4_c035_01E00B80;

typedef struct Slot_c035_01E00B80 {
    u8 pad0[0x38];
    s32 (*draw)(void *, struct Slot_c035_01E00B80 *, void *, s32);
    s32 (*fn)(void *, struct Slot_c035_01E00B80 *);
    u8 pad40[8];
    s16 used;
    u8 pad4A[0x16];
} Slot_c035_01E00B80;

typedef struct {
    u8 pad0[0x10];
    s32 active;
    u8 pad14[0x2C];
} Fade_c035_01E00B80;

typedef struct {
    u8 pad0[0x36];
    s16 used;
    u8 pad38[8];
} Fx_c035_01E00B80;

typedef struct {
    V4_c035_01E00B80 *sp;
    V4_c035_01E00B80 *cp;
    V4_c035_01E00B80 *rel;
    f32 *look;
    V4_c035_01E00B80 lookv;
    V4_c035_01E00B80 sp0;
    V4_c035_01E00B80 cp0;
    V4_c035_01E00B80 rel0;
} View_c035_01E00B80;

typedef struct {
    u8 pad0[0x40];
    u8 cam[0x68];
    s32 tex;
    u8 padAC[0x34];
    s32 rot[4];
    u8 padF0[0x10];
    V4_c035_01E00B80 sc;
    Slot_c035_01E00B80 slot[10];
    View_c035_01E00B80 view;
    u8 pad520[0x30];
    Fade_c035_01E00B80 fade[40];
    Fx_c035_01E00B80 fx[150];
    s32 timer;
    u8 pad34D4[8];
    s32 ot;
    u8 pad34E0[4];
    void (*step)(void *, s32);
    u8 pad34E8[0x3550 - 0x34E8];
    s16 code;
    u8 pad3552[2];
    s16 count;
    u8 pad3556[0x3660 - 0x3556];
    f32 cos[91];
} Ctx_c035_01E00B80;

static s32 func_01E00B80_c035(s32 arg0, s32 code) {
    extern void c035_01E00080(void *, s32);
    extern s32 c035_01E00580(Ctx_c035_01E00B80 *, Fx_c035_01E00B80 *);
    extern s32 c035_01E00860(Ctx_c035_01E00B80 *, Fade_c035_01E00B80 *);
    extern void c035_01E013A0(Ctx_c035_01E00B80 *, Fx_c035_01E00B80 *, void *, s32);
    Ctx_c035_01E00B80 *g = (Ctx_c035_01E00B80 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern s32 func_00202BF0(s32, s32);
    extern f32 func_001A6A88(f32);
    extern V4_c035_01E00B80 *func_001F9AD0(s32);
    extern V4_c035_01E00B80 *func_001F9D30(s32);
    extern V4_c035_01E00B80 *func_001FAD10(s32);
    extern f32 *func_001FAF60(s32);
    extern void func_001FAFB0(s32, void *);
    extern void func_0020EB40(void *);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020BC00(void *, void *);
    s32 n;
    V4_c035_01E00B80 pos;
    u8 pkt[0x90];
    s32 (*draw)(void *, Slot_c035_01E00B80 *, void *, s32);
    s32 i;

    n = 0;
    g->ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x37D0);
        g->step = c035_01E00080;
        for (i = 0; i < 91; i++) {
            g->cos[i] = func_001A6A88(3.1415927f * i / 180.0f);
        }
        g->code = code;
        g->timer = 180;
        g->tex = func_00202BF0(4, 2);
        if (&g->view != NULL) {
            g->view.sp = func_001F9AD0(0);
            g->view.cp = func_001F9D30(0);
            g->view.rel = func_001FAD10(0);
            g->view.look = func_001FAF60(0);
            func_001FAFB0(0, &g->view.lookv);
            g->view.sp0 = *g->view.sp;
            g->view.cp0 = *g->view.cp;
            g->view.rel0 = *g->view.rel;
        }
        return 0;
    }
    if (g->step != NULL) {
        g->step(g, 0);
    }
    for (i = 0; i < 10; i++) {
        if (g->slot[i].used != 0) {
            if (g->slot[i].fn != NULL) {
                g->slot[i].fn(g, &g->slot[i]);
            }
        }
    }
    pos.x = pos.y = pos.z = 0.0f;
    pos.y = 50.0f;
    pos = *func_001F9D30(0);
    func_00205C40((s32)g->rot);
    g->rot[0] += 0x4000;
    g->sc.y = 0.2f;
    g->sc.x = 0.5f;
    g->sc.z = 0.5f;
    for (i = 0; i < 10; i++) {
        if (g->slot[i].used != 0) {
            n++;
            func_0020EB40(g->cam);
            func_0020C940(g, &g->sc, g->rot, &pos);
            func_0020BC00(g->cam, g);
            draw = g->slot[i].draw;
            if (draw != NULL) {
                draw(g, &g->slot[i], pkt, 0);
                draw(g, &g->slot[i], pkt, 1);
            }
        }
    }
    n = 0;
    for (i = 0; i < 40; i++) {
        if (g->fade[i].active != 0) {
            n++;
            c035_01E00860(g, &g->fade[i]);
        }
    }
    for (i = 0; i < 150; i++) {
        if (g->fx[i].used != 0) {
            c035_01E00580(g, &g->fx[i]);
        }
    }
    for (i = 0; i < 150; i++) {
        if (g->fx[i].used != 0) {
            c035_01E013A0(g, &g->fx[i], pkt, 0);
        }
    }
    if (g->timer != 0) {
        g->timer--;
    }
    if (g->count >= 158) {
        if (g->timer > 2) {
            return 2;
        }
    }
    if (g->timer <= 0) {
        return 8;
    }
    return 0;
}

/* shape c035:01E00F60, 60 insns: take a free slot (10 of 0x60 bytes at 0x110), clear it, mark it with its index + 1;
   give it a random 0x4A of 5..14, the module's callback c035:01E01280 and arg */

typedef struct {
    u8 pad0[0x38];
    void (*cb)(void);
    s32 arg;
    u8 pad40[8];
    s16 used;
    s16 f4A;
    u8 pad4C[0x14];
} Slot_c035_01E00F60;

typedef struct {
    u8 pad0[0x110];
    Slot_c035_01E00F60 slots[10];
} Obj_c035_01E00F60;

static void func_01E00F60_c035(Obj_c035_01E00F60 *obj, s32 arg) {
    extern void c035_01E01280(void);
    extern void func_00195108();
    Slot_c035_01E00F60 *s = NULL;
    s16 i;

    for (i = 0; i < 10; i++) {
        if (obj->slots[i].used == 0) {
            func_00195108(&obj->slots[i], 0x60);
            obj->slots[i].used = i + 1;
            s = &obj->slots[i];
            i = 10;
        }
    }
    if (s != NULL) {
        s->f4A = func_0019A5C8() % 10 + 5;
        s->cb = c035_01E01280;
        s->arg = arg;
    }
}

/* shape c035:01E01050, 61 insns: takes the first free of 10 effect slots (0x60 bytes, b108:01E02FF0 family), marks it
   with its index + 1, colours both from the context and hooks c035:01E01290 with the given argument */

typedef struct {
    u8 pad0[0x38];
    void (*cb)(void);
    s32 arg;
    u8 c40[4];
    u8 c44[4];
    s16 used;
    u8 pad4A[0x16];
} Slot_c035_01E01050;

typedef struct {
    u8 pad0[0x110];
    Slot_c035_01E01050 slots[0xA];
    u8 pad[0x34D4 - 0x110 - 0xA * 0x60];
    u8 rgba[4];
} Ctx_c035_01E01050;

static void func_01E01050_c035(Ctx_c035_01E01050 *ctx, s32 arg) {
    extern void c035_01E01290(void);
    extern void func_001076F0();
    extern void func_00195108();
    s16 i;
    Slot_c035_01E01050 *s = NULL;

    for (i = 0; i < 0xA; i++) {
        if (ctx->slots[i].used == 0) {
            s = &ctx->slots[i];
            func_00195108(s, 0x60);
            ctx->slots[i].used = i + 1;
            i = 0xA;
        }
    }
    if (s != NULL) {
        func_001076F0(s->c40, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        func_001076F0(s->c44, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        s->cb = c035_01E01290;
        s->arg = arg;
    }
}

/* shape c035:01E01150, 73 insns: take the first free glow slot of 150 (0x40 bytes each, at ctx+0xF50), clear it, then give it the scene colour twice, the scene position (func_00106AB0), turns, two angles and the argument */

typedef struct {
    u8 pad0[8];
    s16 h8;
    s16 hA;
    u8 padC[2];
    s16 hE;
    s32 w10;
    s32 w14;
    s32 w18;
    u8 pad1C[8];
    s32 w24;
    u8 col[4];
    u8 col2[4];
    s16 h30;
    s16 tick;
    s16 kind;
    s16 used;
    s16 f38;
    s16 ang;
    u8 pad3C[4];
} Glow_c035_01E01150;

typedef struct {
    u8 pad0[0x80];
    u8 pos[0x60];
    s32 rot[3];
    u8 padEC[0xF50 - 0xEC];
    Glow_c035_01E01150 slot[150];
    u8 padEnd[0x34D4 - 0xF50 - 150 * 0x40];
    u8 r;
    u8 g;
    u8 b;
    u8 a;
    u8 pad34D8[0x6E];
    s16 ang;
    u8 pad3548[6];
    s16 h30;
} Ctx_c035_01E01150;

static void func_01E01150_c035(Ctx_c035_01E01150 *ctx, s32 arg) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106AB0(void *, void *, s32);
    Glow_c035_01E01150 *s;
    s16 i;

    s = NULL;
    for (i = 0; i < 150; i++) {
        if (ctx->slot[i].used == 0) {
            s = &ctx->slot[i];
            func_00195108(s, 0x40);
            ctx->slot[i].used = 1;
            i = 150;
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
        s->w24 = arg;
    }
}

/* shape b073:01E03BC0, 2 insns, 5 copies: an empty callback */

static void func_01E01280_c035(void) {
}

/* shape c035:01E01290, 67 insns: mode 0 builds a 4-vertex packet (tag 8, 0x14 qwords, blend 0x48) with the effect's
   colours (0x40 on the first two corners, 0x44 on the last two) and finishes it (func_001094F0); otherwise sends it
   to the scene target (0x34DC) */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_c035_01E01290;

typedef struct {
    Rgbaq_c035_01E01290 c;
    u64 xyz;
} Vtx_c035_01E01290;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_c035_01E01290 v[4];
} Pkt_c035_01E01290;

typedef struct {
    u8 pad0[0x40];
    u8 c40[4];
    u8 c44[4];
} Fx_c035_01E01290;

typedef struct {
    u8 pad0[0x34DC];
    s32 target;
} Scene_c035_01E01290;

static void func_01E01290_c035(Scene_c035_01E01290 *g, Fx_c035_01E01290 *o, Pkt_c035_01E01290 *p, s32 mode) {
    extern Rgbaq_c035_01E01290 func_00107740(void *);
    extern void func_002075F0(void *, s32, s32);

    if (mode == 0) {
        p->count = 0x14;
        p->tag = 8;
        p->regs = 0x41414141;
        p->pad = 0;
        func_002086D0(p, ((u64)0x80 << 32) | 0x48);
        p->v[0].c = func_00107740(o->c40);
        p->v[1].c = func_00107740(o->c40);
        p->v[2].c = func_00107740(o->c44);
        p->v[3].c = func_00107740(o->c44);
        func_001094F0(p);
    } else {
        func_002075F0(p, g->target, 0);
    }
}

/* shape c035:01E013A0, 97 insns: draws the effect as a camera-facing square of its size 0x38: drawing state (a 0x14
   matrix from its angle 0x34, colour, the scene texture 0xA8), camera rotation, world matrix at its position offset by
   a tenth of 0x8..0xC, then func_00108F90 */

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 dx, dy, dz;
    u8 padE[0x1A];
    u8 col[0xC];
    s16 h34;
    u8 pad36[2];
    s16 size;
} Fx_c035_01E013A0;

typedef struct {
    u8 pad0[0xA8];
    s32 tex;
} Scene_c035_01E013A0;

static void func_01E013A0_c035(Scene_c035_01E013A0 *g, Fx_c035_01E013A0 *o, void *p) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern void func_00108F90(void *, void *, void *, s32);
    Vec4f quad[4];
    Vec4f pos;
    f32 rm[4];
    f32 m[16];
    s32 rot[4];
    s32 v;

    v = (s32)func_00207500();
    func_00106080(rm, 0x14, o->h34, rm);
    func_00109270(p, 0, 0);
    func_00107790(p, o->col, 0);
    func_00108500(p, rm, 0);
    func_00208700(p, g->tex, 1);
    func_00205C40((s32)rot);
    pos.x = o->x + o->dx / 10;
    pos.y = o->y + o->dy / 10;
    pos.z = o->z + o->dz / 10;
    func_00108EF0(m, 0, rot, &pos);
    func_00108CE0(quad, o->size, o->size);
    func_00108F90(quad, p, m, v);
}

INCLUDE_ASM("asm/nonmatchings/mod/c035", func_01E01580_c035);

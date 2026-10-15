#include "common.h"

INCLUDE_ASM("asm/nonmatchings/mod/c035", func_01E00080_c035);

INCLUDE_ASM("asm/nonmatchings/mod/c035", func_01E00310_c035);

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

INCLUDE_ASM("asm/nonmatchings/mod/c035", func_01E00580_c035);

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

INCLUDE_ASM("asm/nonmatchings/mod/c035", func_01E009B0_c035);

INCLUDE_ASM("asm/nonmatchings/mod/c035", func_01E00B80_c035);

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

INCLUDE_ASM("asm/nonmatchings/mod/c035", func_01E013A0_c035);

INCLUDE_ASM("asm/nonmatchings/mod/c035", func_01E01580_c035);

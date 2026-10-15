#include "common.h"

INCLUDE_ASM("asm/nonmatchings/mod/c021", func_01E00080_c021);

INCLUDE_ASM("asm/nonmatchings/mod/c021", func_01E00630_c021);

/* shape c021:01E00AF0, 40 insns, 1 copy */

typedef struct Ctx_c021_01E00AF0 {
    u8 pad0[0x3578];
    s32 timer;
    u8 pad357C[0x38BA - 0x357C];
    s16 phase;
} Ctx_c021_01E00AF0;

typedef struct Obj_c021_01E00AF0 {
    u8 pad0[0x7F];
    u8 c7F;
    u8 pad80[3];
    u8 c83;
    s16 f84;
} Obj_c021_01E00AF0;

static s32 func_01E00AF0_c021(Ctx_c021_01E00AF0 *ctx, Obj_c021_01E00AF0 *o) {
    if (ctx->phase < 8) {
        if (o->c7F < 0x80) {
            o->c7F += 0x20;
        }
        if (o->c83 < 0x60) {
            o->c83 += 0x20;
        }
    }
    if (ctx->timer < 0x12) {
        if (o->c7F > 0x10) {
            o->c7F -= 0xF;
        }
        if (o->c83 > 0x10) {
            o->c83 -= 0xF;
        }
    }
    if (ctx->timer < 0xB) {
        o->f84 = 0;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/c021", func_01E00B90_c021);

INCLUDE_ASM("asm/nonmatchings/mod/c021", func_01E00E00_c021);

INCLUDE_ASM("asm/nonmatchings/mod/c021", func_01E013C0_c021);

INCLUDE_ASM("asm/nonmatchings/mod/c021", func_01E016C0_c021);

/* shape c021:01E01C50, 111 insns: sets up the scene's 22 models (ids 0..10 and 256..266): object 0x26C0 + i x 0x70 gets
   a random size 1..6 (0x54), 0x28 2..7, 0x34 0x100..0x18FF, 0x38 -0x3FF..0x3FF, is registered with the model (0x4 and
   0x24 cleared), tagged from 0x31B0 + i x 0x10, coloured, alpha 0x80, scaled 0.1 */

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
} Obj_c021_01E01C50;

typedef struct {
    u8 tag[0x10];
} Tag_c021_01E01C50;

typedef struct {
    u8 pad0[0x26C0];
    Obj_c021_01E01C50 obj[22];
    u8 pad3060[0x31B0 - 0x3060];
    Tag_c021_01E01C50 tags[22];
} Scene_c021_01E01C50;

static void func_01E01C50_c021(Scene_c021_01E01C50 *g) {
    extern s32 func_001F5380(void);
    extern s32 func_001F5AF0(s32);
    extern void func_001F5970(s32, s32);
    extern void func_001F5BD0(s32, void *);
    extern void func_001F5B70(s32, void *);
    extern void func_001F5CA0(s32, void *);
    extern void func_001F5E40(s32, void *);
    extern void func_001F5D10(s32, void *);
    s16 i;
    Obj_c021_01E01C50 *p;
    s32 id;

    func_001F5380();
    for (i = 0; i < 22; i++) {
        id = i;
        if (id > 10) {
            id += 0xF5;
        }
        p = &g->obj[i];
        p->f54 = (func_0019A5C8() % 33 + 6) / 6;
        p->w28 = func_0019A5C8() % 6 + 2;
        p->w34 = func_0019A5C8() % 0x1800 + 0x100;
        p->w38 = func_0019A5C8() % 0x800 - 0x400;
        if (func_001F5AF0(id) != 0) {
            func_001F5970(id, 1);
        }
        func_001F5BD0(id, p);
        p->w4 = 0;
        func_001F5B70(id, p);
        p->w24 = 0;
        func_001F5CA0(id, &g->tags[i]);
        func_001F5E40(id, p->col);
        p->col[3] = 0x80;
        p->scale[0] = 0.1f;
        p->scale[1] = 0.1f;
        p->scale[2] = 0.1f;
        func_001F5D10(id, p->scale);
    }
}

/* shape c021:01E01E10, 84 insns: c059:01E005C0 family voice step: unless the scene state reached 10, re-trigger channel n (ch, or ch + 245 past 10) unless its bit in the mute mask is set, then place it on the scene's per-channel matrix, reset the object, and (unmuted) raise its volume by 16 up to 0x80; ease 0.18 */

typedef struct {
    u8 pad0[0x31B0];
    Vec4f m[22];
    u8 pad3310[0x3578 - 0x3310];
    s32 state;
    u8 pad357C[0x38A0 - 0x357C];
    u32 mute;
} Ctx_c021_01E01E10;

typedef struct {
    u8 pad0[4];
    s32 w4;
    u8 pad8[0x58];
    u8 col[4];
} Obj_c021_01E01E10;

static s32 func_01E01E10_c021(Ctx_c021_01E01E10 *c, Obj_c021_01E01E10 *o, s32 ch) {
    extern s32 func_001F5EC0(s32);
    extern s32 func_001F5AF0(s32);
    extern void func_00107370(s32, s32, f32);
    extern void func_001F5C40(s32, void *);
    extern void func_001F5B70(s32, void *);
    extern void func_001F5E40(s32, void *);
    extern void func_001F5DE0(s32, void *);
    extern void func_00107510(s32, s32, f32);
    s32 n;

    n = ch;
    if (ch > 0xA) {
        n = ch + 0xF5;
    }
    if (c->state < 0xA) {
        if (func_001F5EC0(n) != 0) {
            if (!((c->mute >> (21 - ch)) & 1)) {
                func_00107370(n, 0, 0.15f);
            }
        }
        if (func_001F5AF0(n) != 0) {
            func_001F5C40(n, &c->m[ch]);
            o->w4 = 0;
            func_001F5B70(n, o);
            if (!((c->mute >> (21 - ch)) & 1)) {
                func_001F5E40(n, o->col);
                o->col[3] += 0x10;
                if (o->col[3] >= 0x80) {
                    o->col[3] = 0x80;
                }
                func_001F5DE0(n, o->col);
            }
            func_00107510(n, 0, 0.18f);
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/c021", func_01E01F60_c021);

INCLUDE_ASM("asm/nonmatchings/mod/c021", func_01E02350_c021);

/* shape c021:01E02820, 49 insns: take the first free slot of the 65-slot pool (0x94 bytes each), clear it, mark it with its index + 1 and give it the argument */

typedef struct {
    u8 pad0[0x74];
    s32 arg;
    u8 pad78[0xC];
    s16 used;
    u8 pad86[0xE];
} Slot_c021_01E02820;

typedef struct {
    u8 pad0[0x120];
    Slot_c021_01E02820 s[65];
} Pool_c021_01E02820;

static void func_01E02820_c021(Pool_c021_01E02820 *o, s32 arg) {
    extern void func_00106CC0(void *, s32);
    s16 i;
    Slot_c021_01E02820 *s;

    for (i = 0; i < 65; i++) {
        if (o->s[i].used == 0) {
            func_00106CC0(&o->s[i], 0x94);
            o->s[i].used = i + 1;
            s = &o->s[i];
            goto done;
        }
    }
    s = NULL;
done:
    if (s != NULL) {
        s->arg = arg;
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/c021", func_01E028F0_c021);

typedef struct {
    f32 x, y, z, w;
} Vec_c021_01E029F0;

typedef struct {
    u8 pad00[0x24];
    s32 w24;
    u8 pad28[8];
    Vec_c021_01E029F0 pos;
    u8 pad40[0x14];
    f32 f54;
    u8 pad58[0x18];
    void *cb;
    s32 parent;
    f32 f78;
    u8 c7C[4];
    u8 c80[4];
    s16 active;
    u8 b86;
    u8 b87;
    u8 pad88[2];
    s16 h8A;
    u8 pad8C[2];
    s16 h8E;
    u8 pad90[4];
} Ent_c021_01E029F0;

typedef struct {
    u8 pad0000[0xC0];
    Vec_c021_01E029F0 vC0;
    u8 pad00D0[0x50];
    Ent_c021_01E029F0 ents[65];
    u8 pad[0x3344 - 0x120 - 65 * 0x94];
    s32 w3344;
    u8 pad3348[0x357C - 0x3348];
    u8 r, g, b;
    u8 pad357F[0x11];
    f32 f3590;
    f32 f3594;
    f32 f3598;
} Mgr_c021_01E029F0;

static void func_01E029F0_c021(Mgr_c021_01E029F0 *m, s32 parent) {
    extern void c021_01E03280(void);
    extern void func_00106CC0(void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    s16 i;
    Ent_c021_01E029F0 *e;

    for (i = 0; i < 65; i++) {
        if (m->ents[i].active == 0) {
            e = &m->ents[i];
            func_00106CC0(e, 0x94);
            m->ents[i].active = i + 1;
            goto found;
        }
    }
    e = 0;
found:
    if (e != 0) {
        func_001076F0(e->c7C, m->r, m->g, m->b);
        e->c7C[3] = 0;
        func_001076F0(e->c80, m->r, m->g, m->b);
        e->c80[3] = 0;
        e->pos = m->vC0;
        e->b86 = (u32)m->f3590;
        e->b87 = (u32)m->f3594;
        e->f78 = m->f3598;
        e->h8E = func_0019A5C8() % 4;
        e->w24 = m->w3344;
        e->h8A = func_0019A5C8() % 10 + 5;
        e->parent = parent;
        e->cb = (void *)c021_01E03280;
        func_0019A5C8();
        e->f54 = func_0019A5C8() % 9 + 3;
        e->w24 = (s16)(func_0019A5C8() % 360) * 182;
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/c021", func_01E02BE0_c021);

INCLUDE_ASM("asm/nonmatchings/mod/c021", func_01E02E40_c021);

INCLUDE_ASM("asm/nonmatchings/mod/c021", func_01E03060_c021);

/* shape c021:01E03280, 67 insns: mode 0 sets up the drawing state (a 0x9B matrix from the effect's angle at 0x8E,
   colours at 0x7C/0x80, the scene texture at 0xBC); otherwise sizes the scene quad (0xE0) to (h / 2, h) from the
   effect's 0x8A and draws it with the scene matrix (0x40) into the scene target (0x3584) at its depth (0x35D0) */

typedef struct {
    u8 pad0[0x7C];
    u8 c7C[4];
    u8 c80[4];
    u8 pad84[6];
    s16 h8A;
    u8 pad8C[2];
    s16 h8E;
} Fx_c021_01E03280;

typedef struct {
    u8 pad0[0x40];
    u8 m[0x7C];
    s32 tex;
    u8 padC0[0x20];
    u8 quad[0x34A4];
    s32 target;
    u8 pad3588[0x48];
    f32 depth;
} Scene_c021_01E03280;

static void func_01E03280_c021(Scene_c021_01E03280 *g, Fx_c021_01E03280 *o, void *p, s32 mode) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108CE0(void *, f32, f32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 rm[4];
    s16 h;

    h = o->h8A;
    if (mode == 0) {
        func_00106080(rm, 0x9B, o->h8E, rm);
        func_00109270(p, 0, 0);
        func_00107790(p, o->c7C, 1);
        func_00107790(p, o->c80, 2);
        func_00108500(p, rm, 0);
        func_00208700(p, g->tex, 1);
    } else {
        func_00108CE0(g->quad, h >> 1, h);
        if (func_00205630(g->quad, 0x70000000, g->m, p, &g->depth) != 0) {
            func_002075F0(p, g->target, (u32)g->depth);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/c021", func_01E03390_c021);

INCLUDE_ASM("asm/nonmatchings/mod/c021", func_01E038A0_c021);

INCLUDE_ASM("asm/nonmatchings/mod/c021", func_01E03BA0_c021);

/* shape c021:01E03EA0, 71 insns: draws a slot effect (c035:01E01290 shape with the effect colours at 0x7C, blend 0x42): mode 0 builds
   the gouraud packet with q 0, other modes queue it */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_c021_01E03EA0;

typedef struct {
    Rgbaq_c021_01E03EA0 c;
    u64 xyz;
} Vtx_c021_01E03EA0;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_c021_01E03EA0 v[4];
} Pkt_c021_01E03EA0;

typedef struct {
    u8 pad0[0x7C];
    u8 c40[4];
    u8 c44[4];
} Fx_c021_01E03EA0;

typedef struct {
    u8 pad0[0x3584];
    s32 target;
} Scene_c021_01E03EA0;

static void func_01E03EA0_c021(Scene_c021_01E03EA0 *g, Fx_c021_01E03EA0 *o, Pkt_c021_01E03EA0 *p, s32 mode) {
    extern Rgbaq_c021_01E03EA0 func_00107740(void *);
    extern void func_002075F0(void *, s32, s32);

    if (mode == 0) {
        p->count = 0x14;
        p->tag = 8;
        p->regs = 0x41414141;
        p->pad = 0;
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
        p->v[0].c = func_00107740(o->c40);
        p->v[1].c = func_00107740(o->c40);
        p->v[2].c = func_00107740(o->c44);
        p->v[3].c = func_00107740(o->c44);
        p->v[0].c.q = p->v[1].c.q = p->v[2].c.q = p->v[3].c.q = 0.0f;
        func_001094F0(p);
    } else {
        func_002075F0(p, g->target, 0);
    }
}

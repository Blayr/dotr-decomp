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

/* shape c021:01E00B90, 154 insns: a ribbon node's step: its angle turns by -0x54 (wrapped past +-360), the length 0x34
   shortens by 1 and the width 0x30 by 2 while above 0; both alphas grow (by 6 when 0x64 is above 120, else by 15, to
   0x60) for the first 8 scene frames (0x38BA); when the scene timer (0x3578) drops below 13 they fade by 25, when the
   node gets too short or thin they fade by 10, otherwise they grow by 5 to 0x60; the node ends below timer 11 */

typedef struct {
    u8 pad0[0x24];
    s32 ang;
    u8 pad28[8];
    f32 w30;
    f32 len;
    u8 pad38[0x1C];
    f32 turn;
    u8 pad58[0xC];
    f32 f64;
    u8 pad68[0x14];
    u8 col[4];
    u8 col2[4];
    s16 live;
} Node_c021_01E00B90;

typedef struct {
    u8 pad0[0x3578];
    s32 timer;
    u8 pad357C[0x33E];
    s16 frame;
} Scene_c021_01E00B90;

static s32 func_01E00B90_c021(Scene_c021_01E00B90 *g, Node_c021_01E00B90 *o) {
    extern s32 func_001A22C0(f32);

    o->ang = func_001A22C0(o->ang - o->turn);
    if (o->ang > 360 || o->ang < -360) {
        o->ang %= 360;
    }
    o->len -= 1.0f;
    if (o->w30 > 0.0f) {
        o->w30 -= 2.0f;
    }
    if (g->frame < 8) {
        if (o->f64 > 120.0f) {
            if (o->col[3] < 0x60) {
                o->col[3] += 6;
            }
            if (o->col2[3] < 0x60) {
                o->col2[3] += 6;
            }
        } else {
            if (o->col[3] < 0x60) {
                o->col[3] += 15;
            }
            if (o->col2[3] < 0x60) {
                o->col2[3] += 15;
            }
        }
    } else if (g->timer < 13) {
        if (o->col[3] > 0x19) {
            o->col[3] -= 25;
        }
        if (o->col2[3] > 0x19) {
            o->col2[3] -= 25;
        } else {
            o->live = 0;
        }
    } else if (o->len < 50.0f || o->w30 < 8.0f) {
        if (o->col[3] > 0x10) {
            o->col[3] -= 10;
        }
        if (o->col2[3] > 0x10) {
            o->col2[3] -= 10;
        } else {
            o->live = 0;
        }
    } else {
        if (o->col[3] < 0x60) {
            o->col[3] += 5;
        }
        if (o->col2[3] < 0x60) {
            o->col2[3] += 5;
        }
    }
    if (g->timer < 11) {
        o->live = 0;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/c021", func_01E00E00_c021);

/* shape c021:01E013C0, 192 insns: c030:01E00E30's segment hand-on: turning back 1 a tick, its two lengths (f60/f64)
   saved as bytes and shrinking by 4 (the tail follows once 18 behind); while under 200 it hands its colour, lengths
   and turn + 15 to the scene's next segment (ctx+0x3588..) and spawns it through c021:01E02E40; alphas up by 5 to
   0x30 for the first 8 scene frames, down by 16 while the scene timer is under 18, else up by 4 to 0x80 */

typedef struct {
    u8 pad0[0x68];
    s32 w68;
} Link_c021_01E013C0;

typedef struct {
    u8 pad0[0x60];
    f32 f60;
    f32 f64;
    u8 pad68[4];
    Link_c021_01E013C0 *link;
    u8 pad70[0xC];
    u8 col[4];
    u8 col2[4];
    s16 h84;
    u8 c86;
    u8 c87;
    u8 pad88[4];
    s16 ang;
    s16 h8E;
    u8 pad90[2];
    s16 h92;
} Seg_c021_01E013C0;

typedef struct {
    u8 pad0[0xC0];
    s32 rC0, rC4, rC8;
    u8 padCC[0x3578 - 0xCC];
    s32 timer;
    u8 col[4];
    u8 pad3580[8];
    Seg_c021_01E013C0 *parent;
    u8 pad358C[4];
    f32 px, py, pz;
    u8 pad359C[0x38A6 - 0x359C];
    s16 ang;
    u8 pad38A8[8];
    s16 h38B0;
    u8 pad38B2[2];
    s16 h38B4;
    u8 pad38B6[4];
    s16 frame;
    u8 pad38BC[8];
    s16 h38C4;
} Scene_c021_01E013C0;

static s32 func_01E013C0_c021(Scene_c021_01E013C0 *g, Seg_c021_01E013C0 *o) {
    extern void c021_01E02E40(Scene_c021_01E013C0 *, void *);
    extern u32 func_001A23B0(f32);

    o->ang -= 1;
    if (o->ang < -359) {
        o->ang %= 360;
    }
    o->c86 = func_001A23B0(o->f60);
    o->c87 = func_001A23B0(o->f64);
    if (o->f60 > 0.0f) {
        o->f60 -= 4.0f;
        if (o->f64 - o->f60 >= 18.0f) {
            o->f64 -= 4.0f;
        }
    } else {
        o->f64 -= 4.0f;
        if (o->f64 < o->f60) {
            o->f64 = o->f60;
            if (o->link != NULL) {
                o->link->w68 = 0;
            }
            o->h84 = 0;
        }
    }
    if (o->h8E > 0 && o->f64 < 200.0f) {
        g->parent = o;
        g->px = (f32)(u32)o->c86;
        g->py = (f32)(u32)o->c87;
        g->col[3] = 0;
        g->col[0] = o->col[0];
        g->col[1] = o->col[1];
        g->col[2] = o->col[2];
        g->h38B0 = 1;
        g->pz = o->f64;
        g->h38B4 = 1;
        g->rC4 = 0;
        g->rC0 = 0;
        g->rC8 = 0;
        g->ang = o->ang + 15;
        if (o->h92 != 0) {
            g->h38C4 = 0;
        } else {
            g->h38C4 = 1;
        }
        c021_01E02E40(g, func_01E013C0_c021);
        o->h8E = 0;
    }
    if (g->frame < 8) {
        if (o->col[3] < 0x30) {
            o->col[3] += 5;
        }
        if (o->col2[3] < 0x30) {
            o->col2[3] += 5;
        }
    } else if (g->timer < 18) {
        if (o->col[3] > 16) {
            o->col[3] -= 16;
        }
        if (o->col2[3] > 16) {
            o->col2[3] -= 16;
        }
    } else {
        if (o->col[3] < 0x80) {
            o->col[3] += 4;
        }
        if (o->col2[3] < 0x80) {
            o->col2[3] += 4;
        }
    }
    if (g->timer < 11) {
        o->h84 = 0;
    }
    return 0;
}

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

/* shape c021:01E02BE0, 150 insns: c021 trail link spawner (c017:01E01400 family, 65 slots of 0x94 at ctx+0x120, cleared by func_00106CC0): both colours and alpha from the context, its vector, two sizes as bytes, height kept 18 above for kinds 0/1 and capped at 180, chained after the context's last piece (copying its two vectors) and becomes it; draws with c021:01E03390 */

/* OVL_WARM */

typedef struct {
    u8 r, g, b, a;
} Col_c021_01E02BE0;

typedef struct Ent_c021_01E02BE0 {
    Vec4f v0;
    u8 pad10[0x20];
    Vec4f v30;
    Vec4f v40;
    u8 pad50[0x10];
    f32 f60;
    f32 f64;
    struct Ent_c021_01E02BE0 *prev;
    struct Ent_c021_01E02BE0 *next;
    void (*cb)(void);
    s32 arg;
    f32 f78;
    Col_c021_01E02BE0 col0;
    Col_c021_01E02BE0 col1;
    s16 used;
    u8 b86;
    u8 b87;
    s16 h88;
    u8 pad8A[2];
    s16 h8C;
    s16 h8E;
    s16 h90;
    s16 h92;
} Ent_c021_01E02BE0;

typedef struct {
    u8 pad0[0xC0];
    Vec4f v;
    u8 padD0[0x120 - 0xD0];
    Ent_c021_01E02BE0 ent[65];
    u8 padEnd[0x357C - 0x120 - 65 * 0x94];
    u8 rgba[4];
    u8 pad3580[8];
    Ent_c021_01E02BE0 *last;
    u8 pad358C[4];
    f32 f3590;
    f32 f3594;
    f32 f3598;
    u8 pad359C[0x38A6 - 0x359C];
    s16 h38A6;
    u8 pad38A8[8];
    s16 h38B0;
    u8 pad38B2[2];
    s16 h38B4;
    u8 pad38B6[0x38C4 - 0x38B6];
    s16 h38C4;
} Ctx_c021_01E02BE0;


static inline Ent_c021_01E02BE0 *take_c021_01E02BE0(Ctx_c021_01E02BE0 *g) {
    extern void func_00106CC0(void *, s32);
    Ent_c021_01E02BE0 *e;
    s16 i;

    for (i = 0; i < 65; i++) {
        if (g->ent[i].used == 0) {
            e = &g->ent[i];
            func_00106CC0(e, 0x94);
            g->ent[i].used = i + 1;
            return e;
        }
    }
    return NULL;
}

static void func_01E02BE0_c021(Ctx_c021_01E02BE0 *g, s32 arg) {
    extern void c021_01E03390(void);
    extern void func_001076F0();
    Ent_c021_01E02BE0 *e;
    Ent_c021_01E02BE0 *p;
    f32 h;
    f32 d;

    e = take_c021_01E02BE0(g);
    if (e != NULL) {
        d = 18.0f;
        func_001076F0(&e->col0, g->rgba[0], g->rgba[1], g->rgba[2]);
        e->col0.a = g->rgba[3];
        func_001076F0(&e->col1, g->rgba[0], g->rgba[1], g->rgba[2]);
        e->col1.a = g->rgba[3];
        e->v30 = g->v;
        e->b86 = g->f3590;
        e->b87 = g->f3594;
        e->f78 = g->f3598;
        e->h8C = g->h38A6;
        e->prev = g->last;
        e->h88 = g->h38B4;
        if (e->h88 == 0) {
            h = g->f3598;
            e->f60 = h;
            e->f64 = h + d;
            if (e->f64 > 180.0f) {
                e->f64 = 180.0f;
            }
        } else if (e->h88 == 1) {
            h = g->f3598;
            e->f60 = h;
            e->f64 = h + d;
            if (e->f64 > 180.0f) {
                e->f64 = 180.0f;
            }
        }
        e->h92 = g->h38C4;
        e->prev = g->last;
        p = e->prev;
        if (p != NULL) {
            e->v0 = p->v0;
            e->v40 = p->v40;
            p->next = e;
        }
        e->cb = c021_01E03390;
        e->arg = arg;
        e->h8E = g->h38B0;
        e->h90 = 1;
        g->last = e;
    }
}

/* OVL_WARM */

/* shape c021:01E02E40, 135 insns: c030:01E018C0-style ribbon node: takes the first free of 65 (0x94 bytes at ctx+0x120),
   clears it, colours both from the scene colour, copies the scene point, two byte levels (fptoui), the width and
   settings, links it after the scene's last node, widths clamped to 200, handler 0x1E03BA0 and the argument */

typedef struct Ent_c021_01E02E40 {
    u8 pad0[0x30];
    Vec4f v;
    u8 pad40[0x20];
    f32 f60;
    f32 f64;
    struct Ent_c021_01E02E40 *prev;
    struct Ent_c021_01E02E40 *next;
    void (*cb)(void);
    s32 arg;
    f32 f78;
    u8 col0[4];
    u8 col1[4];
    s16 used;
    u8 b86;
    u8 b87;
    s16 h88;
    u8 pad8A[2];
    s16 h8C;
    s16 h8E;
    u8 pad90[2];
    s16 h92;
} Ent_c021_01E02E40;

typedef struct {
    u8 pad0[0xC0];
    Vec4f v;
    u8 padD0[0x50];
    Ent_c021_01E02E40 ent[65];
    u8 pad26B4[0x357C - 0x26B4];
    u8 col[4];
    u8 pad3580[8];
    Ent_c021_01E02E40 *last;
    u8 pad358C[4];
    f32 f3590;
    f32 f3594;
    f32 f3598;
    u8 pad359C[0x30A];
    s16 h38A6;
    u8 pad38A8[8];
    s16 h38B0;
    u8 pad38B2[2];
    s16 h38B4;
    u8 pad38B6[0xE];
    s16 h38C4;
} Ctx_c021_01E02E40;

static void func_01E02E40_c021(Ctx_c021_01E02E40 *g, s32 arg) {
    extern void c021_01E03BA0(void);
    extern void func_00106CC0(void *, s32);
    extern void func_001076F0();
    s16 i;
    Ent_c021_01E02E40 *e;
    Ent_c021_01E02E40 *p;
    f32 h;
    f32 d;

    for (i = 0; i < 65; i++) {
        if (g->ent[i].used == 0) {
            e = &g->ent[i];
            func_00106CC0(e, 0x94);
            g->ent[i].used = i + 1;
            goto found;
        }
    }
    e = NULL;
found:
    if (e != NULL) {
        d = 18.0f;
        func_001076F0(e->col0, g->col[0], g->col[1], g->col[2]);
        e->col0[3] = g->col[3];
        func_001076F0(e->col1, g->col[0], g->col[1], g->col[2]);
        e->col1[3] = g->col[3];
        e->v = g->v;
        e->b86 = g->f3590;
        e->b87 = g->f3594;
        e->f78 = g->f3598;
        e->h8C = g->h38A6;
        e->prev = g->last;
        e->h88 = g->h38B4;
        if (e->prev == NULL) {
            h = g->f3598;
            e->f60 = h;
            e->f64 = h + d;
        } else {
            h = g->f3598;
            e->f60 = h;
            e->f64 = h + d;
        }
        if (200.0f < e->f60) {
            e->f60 = 200.0f;
        }
        if (200.0f < e->f64) {
            e->f64 = 200.0f;
        }
        e->h92 = g->h38C4;
        e->prev = g->last;
        p = e->prev;
        if (p != NULL) {
            p->next = e;
        }
        e->cb = c021_01E03BA0;
        e->arg = arg;
        e->h8E = g->h38B0;
        g->last = e;
    }
}

/* OVL_WARM */

/* shape c021:01E03060, 135 insns: c021:01E02E40's ribbon node with widths clamped to 180 and handler 0x1E038A0 */

typedef struct Ent_c021_01E03060 {
    u8 pad0[0x30];
    Vec4f v;
    u8 pad40[0x20];
    f32 f60;
    f32 f64;
    struct Ent_c021_01E03060 *prev;
    struct Ent_c021_01E03060 *next;
    void (*cb)(void);
    s32 arg;
    f32 f78;
    u8 col0[4];
    u8 col1[4];
    s16 used;
    u8 b86;
    u8 b87;
    s16 h88;
    u8 pad8A[2];
    s16 h8C;
    s16 h8E;
    u8 pad90[2];
    s16 h92;
} Ent_c021_01E03060;

typedef struct {
    u8 pad0[0xC0];
    Vec4f v;
    u8 padD0[0x50];
    Ent_c021_01E03060 ent[65];
    u8 pad26B4[0x357C - 0x26B4];
    u8 col[4];
    u8 pad3580[8];
    Ent_c021_01E03060 *last;
    u8 pad358C[4];
    f32 f3590;
    f32 f3594;
    f32 f3598;
    u8 pad359C[0x30A];
    s16 h38A6;
    u8 pad38A8[8];
    s16 h38B0;
    u8 pad38B2[2];
    s16 h38B4;
    u8 pad38B6[0xE];
    s16 h38C4;
} Ctx_c021_01E03060;

static void func_01E03060_c021(Ctx_c021_01E03060 *g, s32 arg) {
    extern void c021_01E038A0(void);
    extern void func_00106CC0(void *, s32);
    extern void func_001076F0();
    s16 i;
    Ent_c021_01E03060 *e;
    Ent_c021_01E03060 *p;
    f32 h;
    f32 d;

    for (i = 0; i < 65; i++) {
        if (g->ent[i].used == 0) {
            e = &g->ent[i];
            func_00106CC0(e, 0x94);
            g->ent[i].used = i + 1;
            goto found;
        }
    }
    e = NULL;
found:
    if (e != NULL) {
        d = 18.0f;
        func_001076F0(e->col0, g->col[0], g->col[1], g->col[2]);
        e->col0[3] = g->col[3];
        func_001076F0(e->col1, g->col[0], g->col[1], g->col[2]);
        e->col1[3] = g->col[3];
        e->v = g->v;
        e->b86 = g->f3590;
        e->b87 = g->f3594;
        e->f78 = g->f3598;
        e->h8C = g->h38A6;
        e->prev = g->last;
        e->h88 = g->h38B4;
        if (e->prev == NULL) {
            h = g->f3598;
            e->f60 = h;
            e->f64 = h + d;
        } else {
            h = g->f3598;
            e->f60 = h;
            e->f64 = h + d;
        }
        if (180.0f < e->f60) {
            e->f60 = 180.0f;
        }
        if (180.0f < e->f64) {
            e->f64 = 180.0f;
        }
        e->h92 = g->h38C4;
        e->prev = g->last;
        p = e->prev;
        if (p != NULL) {
            p->next = e;
        }
        e->cb = c021_01E038A0;
        e->arg = arg;
        e->h8E = g->h38B0;
        g->last = e;
    }
}

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

/* shape c021:01E038A0, 189 insns: c021:01E03280 family ribbon draw: mode 0 sets texture 0x97 (frame 1) and the scene texture (g+0xBC); else five 15-degree segments at the scene's angle table (g+0x38C6), the inner edge from the linked object (0x68: its radius 0x87, height 0x64, colour 0x7C, func_00107DD0 between them) or its own radius 0x86, the outer edge at radius 0x87 and its height, coloured 0x80 (or its 0x7C at alpha 10 unless 0x6C), depth-tested into g+0x3584 */

typedef struct {
    u8 r, g, b, a;
} Col_c021_01E038A0;

typedef struct Rib_c021_01E038A0 {
    u8 pad0[0x40];
    u8 m40[0x20];
    f32 f60;
    f32 f64;
    struct Rib_c021_01E038A0 *link;
    s32 w6C;
    u8 pad70[0xC];
    u8 c7C[4];
    u8 c80[4];
    u8 pad84[2];
    u8 c86;
    u8 c87;
    u8 pad88[4];
    s16 ang;
} Rib_c021_01E038A0;

typedef struct {
    u8 pad0[0x40];
    u8 m40[0x7C];
    s32 tex;
    u8 padC0[0x20];
    Vec4f q[4];
    u8 pad120[0x3584 - 0x120];
    s32 ot;
    u8 pad3588[0x35E4 - 0x3588];
    u8 scale[0x38C6 - 0x35E4];
    s16 angs[5];
} Game_c021_01E038A0;

static void func_01E038A0_c021(Game_c021_01E038A0 *g, Rib_c021_01E038A0 *o, void *p, s32 mode) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00106CF0(void *, s16, s32, void *);
    extern void func_00107DD0(void *, void *, void *, s32);
    extern void func_00106FA0(void *, void *, s32);
    extern void func_00107790(void *, void *, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 rm[4];
    f32 d[4];
    Col_c021_01E038A0 c;
    Rib_c021_01E038A0 *q;
    s16 a;
    s32 k;

    q = o->link;
    a = 0;
    if (mode == 0) {
        func_00106080(rm, 0x97, 0, rm);
        func_00109270(p, 0, 0);
        func_00108500(p, rm, 1);
        func_00208700(p, g->tex, 0);
    } else {
        g->q[2].y = g->q[3].y = o->f64;
        for (k = 0; k < 5; k++) {
            if (q != NULL) {
                func_00106CF0(&g->q[0], a + q->ang, q->c87, g->scale);
                func_00106CF0(&g->q[1], a + q->ang + 15, q->c87, g->scale);
                g->q[0].y = g->q[1].y = o->f60 = q->f64;
                func_00107DD0(&g->q[0], q->m40, o->m40, 0);
            } else {
                func_00106CF0(&g->q[0], a + o->ang, o->c86, g->scale);
                func_00106CF0(&g->q[1], a + o->ang + 15, o->c86, g->scale);
                g->q[0].y = g->q[1].y = o->f60;
            }
            func_00106CF0(&g->q[2], a + o->ang, o->c87, g->scale);
            func_00106CF0(&g->q[3], a + o->ang + 15, o->c87, g->scale);
            func_00106FA0(&g->q[0], o->m40, 0);
            func_00107DD0(&g->q[2], o->m40, o, 0);
            if (q == NULL) {
                func_00107790(p, o->c80, 1);
            } else {
                func_00107790(p, q->c7C, 1);
            }
            if (o->w6C != 0) {
                func_00107790(p, o->c80, 2);
            } else {
                c = *(Col_c021_01E038A0 *)o->c7C;
                c.a = 10;
                func_00107790(p, &c, 2);
            }
            if (func_00205630(&g->q[0], 0x70000000, g->m40, p, d) != 0) {
                func_002075F0(p, g->ot, (u32)d[0]);
            }
            a = g->angs[k];
        }
    }
}

/* shape c021:01E03BA0, 189 insns: c056:01E022F0 family ring: eight segments 45 apart drawn with the scene's quad
   (g+0xE0, height 10): the outer edge follows the parent's ring (its angle 0x8C, radius 0x87, taking its depth 0x64)
   or its own at radius 0x86, the inner edge its own at radius 0x87; the slot colour per segment takes the parent's or
   its own alpha for one corner pair and its own 0x83 for the other; mode 0 sets up the packet (blend by scene flag) */

typedef struct Ring_c021_01E03BA0 {
    u8 pad0[0x60];
    f32 f60;
    f32 f64;
    struct Ring_c021_01E03BA0 *parent;
    u8 pad6C[0x13];
    u8 a7F;
    u8 pad80[3];
    u8 a83;
    u8 pad84[2];
    u8 r86;
    u8 r87;
    u8 pad88[4];
    s16 ang;
} Ring_c021_01E03BA0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
} Pk_c021_01E03BA0;

typedef struct {
    u8 pad0[0xBC];
    void *tex;
    u8 padC0[0x20];
    Vec4f quad[4];
    u8 pad120[0x3464];
    s32 ot;
    u8 pad3588[0x48];
    f32 depth;
    u8 pad35D4[0x10];
    u8 sin[0x2D2];
    s16 flag;
    u8 pad38B8[0x18];
    u8 cols[8][4];
} Scene_c021_01E03BA0;

static void func_01E03BA0_c021(Scene_c021_01E03BA0 *g, Ring_c021_01E03BA0 *o, Pk_c021_01E03BA0 *pk, s32 mode) {
    extern void func_00105D00(void *, s32, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, void *, s32);
    extern void func_00106CF0(void *, s16, s32, void *);
    extern void func_00107790(void *, void *, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    s16 rm[4] __attribute__((aligned(16)));
    Ring_c021_01E03BA0 *p;
    s32 k;
    s16 a;

    p = o->parent;
    a = 0;
    if (mode == 0) {
        func_00105D00(rm, 3, 0);
        pk->count = 0x34;
        pk->tag = 0xC;
        pk->regs = 0x21421421 | ((u64)0x4214 << 32);
        pk->pad = 0;
        pk->count |= 0x800;
        if (g->flag == 0) {
            func_002086D0(pk, ((u64)0xF0 << 32) | 0x42);
        } else {
            func_002086D0(pk, 0x48);
        }
        func_00108500(pk, rm, 0);
        func_00208700(pk, g->tex, 1);
    } else {
    g->quad[3].y = 10.0f;
    g->quad[2].y = 10.0f;
    g->quad[1].y = 10.0f;
    g->quad[0].y = 10.0f;
    for (k = 0; k < 8; k++) {
        if (p != NULL) {
            func_00106CF0(&g->quad[0], a + p->ang, p->r87, g->sin);
            func_00106CF0(&g->quad[1], a + p->ang + 45, p->r87, g->sin);
            o->f60 = p->f64;
        } else {
            func_00106CF0(&g->quad[0], a + o->ang, o->r86, g->sin);
            func_00106CF0(&g->quad[1], a + o->ang + 45, o->r86, g->sin);
        }
        func_00106CF0(&g->quad[2], a + o->ang, o->r87, g->sin);
        func_00106CF0(&g->quad[3], a + o->ang + 45, o->r87, g->sin);
        if (p == NULL) {
            g->cols[k][3] = o->a7F;
        } else {
            g->cols[k][3] = p->a83;
        }
        func_00107790(pk, g->cols[k], 1);
        g->cols[k][3] = o->a83;
        func_00107790(pk, g->cols[k], 2);
        rm[0] = 0x81;
        rm[1] = 0x81;
        rm[2] = 0x7F;
        rm[3] = 0x1E;
        func_00108500(pk, rm, 0);
        if (func_00205630(g->quad, 0x70000000, 0, pk, &g->depth) != 0) {
            func_002075F0(pk, g->ot, (u32)g->depth);
        }
        a += 45;
    }
    }
}

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

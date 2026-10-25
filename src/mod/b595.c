#include "common.h"

/* shape b003:01E00080, 552 insns, 183 copies: the module's first function. Texture coordinates of a
   sprite quad from a rectangle, in one of 8 corner orders (flips and quarter turns). Callers in the same
   file rely on it leaving $a0 alone, so it must stay in their file. */

typedef struct Rect_b003_01E00080 {
    s16 x, y, w, h;
} Rect_b003_01E00080;

typedef struct Uv_b003_01E00080 {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad4;
    u64 xyz;
} Uv_b003_01E00080;

typedef struct Pk_b003_01E00080 {
    u8 pad0[0x18];
    Uv_b003_01E00080 c[4];
} Pk_b003_01E00080;


/* static in its module (callers that include this file #define OVL_LOCAL static first) */

static void func_01E00080_b595(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y) << 4;
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y + r->h) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y + r->h) << 4;
    } else if (mode == 2) {
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y + r->h) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y + r->h) << 4;
    } else if (mode == 3) {
        p->c[2].u = (r->x) << 4;
        p->c[2].v = (r->y) << 4;
        p->c[3].u = (r->x + r->w) << 4;
        p->c[3].v = (r->y) << 4;
        p->c[0].u = (r->x) << 4;
        p->c[0].v = (r->y + r->h) << 4;
        p->c[1].u = (r->x + r->w) << 4;
        p->c[1].v = (r->y + r->h) << 4;
    } else if (mode == 4) {
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[3].u = (r->x + r->w) << 4;
        p->c[3].v = (r->y) << 4;
        p->c[0].u = (r->x) << 4;
        p->c[0].v = (r->y + r->h) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y + r->h) << 4;
    } else if (mode == 5) {
        p->c[2].u = (r->x) << 4;
        p->c[2].v = (r->y) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y + r->h) << 4;
        p->c[1].u = (r->x + r->w) << 4;
        p->c[1].v = (r->y + r->h) << 4;
    } else if (mode == 6) {
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y) << 4;
        p->c[1].u = (r->x + r->w) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[2].u = (r->x) << 4;
        p->c[2].v = (r->y + r->h) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y + r->h) << 4;
    } else if (mode == 7) {
        p->c[0].u = (r->x) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y) << 4;
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y + r->h) << 4;
        p->c[3].u = (r->x + r->w) << 4;
        p->c[3].v = (r->y + r->h) << 4;
    }
}

/* OVL_WARM */
/* z offset: in-place divide (fq = t; fq /= 20.0f;) puts the quotient in the dividend's register (chatA fix pass 16 Oct). */

typedef struct {
    f32 x, y, z, w;
} Vec_b038_01E00920;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Col_b038_01E00920;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b038_01E00920;

typedef struct {
    u64 st;
    Xyz_b038_01E00920 p;
} Vtx_b038_01E00920;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Col_b038_01E00920 c;
    Vtx_b038_01E00920 v[4];
    u8 tail[0x30];
} Pkt_b038_01E00920;

typedef struct {
    s32 rot[4];
    s32 v[4];
} Rot_b038_01E00920;

typedef struct {
    s8 x[100];
    s8 y[80];
    s8 z[1];
} Tbl_b038_01E00920;

typedef struct {
    u8 pad00[8];
    s16 base;
    u8 pad0A[0x3E];
    f32 size;
    u8 pad4C[4];
    s16 scale;
    u8 pad52[8];
    s16 spin;
    s16 tilt;
    u8 pad5E[2];
    u8 col[1];
} Anim_b038_01E00920;

typedef struct {
    u8 pad00[0x20];
    f32 x, y, z;
    u8 pad2C[0x54];
    s32 target;
    u8 pad84[4];
    s32 texture;
    u8 pad8C[8];
    u8 b94[0x24];
    s16 count;
    u8 padBA[6];
    s16 hC0;
    u8 padC2[0x16];
    u8 bD8[1];
} Obj_b038_01E00920;

extern void b595_01E00080(Pkt_b038_01E00920 *, void *, s32);

static void func_01E00920_b595(Obj_b038_01E00920 *o, Anim_b038_01E00920 *an, s32 mode, Tbl_b038_01E00920 *tbl) {
    f32 fq;
    extern void func_00207500(void);
    extern void func_00107740(void *, void *);
    extern void func_00208700(void *, s32, s32);
    extern void func_00205C40(void *);
    extern void func_00108EF0(void *, void *, s32, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern void func_00109100(void *, void *, s32, void *);
    extern void func_00108950(void *, void *, s32, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec_b038_01E00920 quad[4];
    Vec_b038_01E00920 d;
    Vec_b038_01E00920 pos;
    Vec_b038_01E00920 scale;
    f32 depth __attribute__((aligned(16)));
    f32 m[16];
    Rot_b038_01E00920 r;
    struct {
        u64 pre;
        Pkt_b038_01E00920 pk;
    } buf;
    Col_b038_01E00920 col;
    s16 i;
    Pkt_b038_01E00920 *p;
    s16 blend;
    s32 kind;
    s32 h;
    s8 *t;

    func_00207500();
    p = &buf.pk;
    p->count = 0x24;
    p->tag = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad = 0;
    p->count |= 0x800;
    blend = mode >> 4;
    if (blend == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((u64)blend << 2) | ((u64)0x80 << 32) | 0x40);
    }
    func_00107740(&col, an->col);
    p->c = col;
    func_00208700(p, o->texture, 1);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40(&r);
    r.rot[1] /= 180;
    r.rot[1] = -r.rot[1];
    r.rot[0] /= 180;
    r.rot[0] = -r.rot[0];
    r.rot[2] = an->tilt;
    r.v[1] = an->spin;
    pos.x = o->x;
    pos.y = o->y;
    pos.z = o->z;
    func_00108EF0(m, &scale, 0, &pos);
    b595_01E00080(p, o->b94, o->hC0);
    kind = mode & 0xF;
    for (i = 0; i < o->count; i++) {
        func_00108CE0(quad, an->size, an->size);
        func_00109100(quad, &r, 2, o->bD8);
        func_00109100(quad, &r, 1, o->bD8);
        func_00109100(quad, &r, 0, o->bD8);
        t = &tbl->x[i];
        h = i >> 1;
        d.x = t[an->base] / 20.0f * (an->scale + h);
        d.y = t[an->base + 100] / 20.0f * (an->scale + h);
        d.z = 0.0f;
        func_00108950(&d, r.v, 0, o->bD8);
        quad[0].x += d.x;
        quad[1].x += d.x;
        quad[2].x += d.x;
        quad[3].x += d.x;
        quad[0].y += d.y;
        quad[1].y += d.y;
        quad[2].y += d.y;
        quad[3].y += d.y;
        fq = t[an->base + 180];
        fq /= 20.0f;
        d.z = fq * (an->scale + h);
        quad[0].z += d.z;
        quad[1].z += d.z;
        quad[2].z += d.z;
        quad[3].z += d.z;
        if (kind == 0) {
            if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
                func_002075F0(p, o->target, (u32)depth);
            }
        } else if (kind == 1) {
            if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
                p->v[0].p.z = p->v[1].p.z = p->v[2].p.z = p->v[3].p.z = 0xFFFFFF;
                func_002075F0(p, o->target, 0);
            }
        } else if (kind == 2) {
            if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
                func_002075F0(p, o->target, -1);
            }
        }
    }
}

/* shape b595:01E00E90, 116 insns: the module's spawn step (b356:01E00E90 shape): ticks the timer; from frame 67 to 280 it spawns
   two b595:01E01060 effects at one joint and two b595:01E01420 effects at another, each half a unit lower */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0xDDE8 - 0x260];
    s16 joint0;
    s16 joint1;
    u8 padDDEC[0x32];
    s16 t;
} Scene_b595_01E00E90;

static void func_01E00E90_b595(Scene_b595_01E00E90 *s) {
    extern void b595_01E01060(void);
    extern void b595_01E01420(void);
    extern s32 b595_01E01D50(Scene_b595_01E00E90 *, void *, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    s16 i;
    s16 n;

    s->t++;
    if (s->t >= 0x43 && s->t < 0x119) {
        if (s->t < 0x64) {
            n = 2;
        } else {
            n = 2;
        }
        for (i = 0; i < n; i++) {
            func_001F5620(func_001F53A0(), s->joint0, &s->pos);
            s->pos.y -= 0.5f;
            b595_01E01D50(s, b595_01E01060, 0);
        }
    }
    if (s->t >= 0x43 && s->t < 0x119) {
        if (s->t < 0x64) {
            n = 2;
        } else {
            n = 2;
        }
        for (i = 0; i < n; i++) {
            func_001F5620(func_001F53A0(), s->joint1, &s->pos);
            s->pos.y -= 0.5f;
            b595_01E01D50(s, b595_01E01420, 0);
        }
    }
}

/* shape b595:01E01060, 237 insns: the b276:01E01060 smoke-puff source with a green-white colour (0x80, 0xFF, 0x80), size
   15 growing 1.5 a tick, fade-in step 0xC0, an extra joint read each tick, and the tick jumped to 100 once the
   scene counter at ctx+0xDE1E passes 0x122 (chatA, 16 Oct) */

typedef struct {
    u8 pad0[0xDDE8];
    s16 v;
    u8 padDDEA[0xDE1E - 0xDDEA];
    s16 limit;
} Ctx_b595_01E01060;

typedef struct {
    u8 pad00[6];
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
    s16 hE;
    f32 x, y, z;
    u8 pad1C[0x14];
    f32 f30;
    f32 f34;
    f32 f38;
    f32 f3C;
    u8 pad40[8];
    f32 f48;
    u8 pad4C[4];
    s16 h50;
    s16 h52;
    s16 t;
    s16 h56;
    s16 state;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
} Obj_b595_01E01060;

static s32 func_01E01060_b595(Ctx_b595_01E01060 *ctx, Obj_b595_01E01060 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F5380(void);
    extern s32 func_001F53A0(void);
    extern void func_001F5F90(s32, f32 *);
    extern void func_001F5620(s32, s32, f32 *);
    f32 a[4];
    f32 b[4];
    f32 c[4];

    if (o->state == 1) {
        o->f48 = 15.0f;
        o->h56 = (func_0019A5C8() >> 4) % 8;
        func_001076F0(o->col, 0x80, 0xFF, 0x80);
        o->h5A = func_0019A5C8() % 360;
        o->h5C = func_0019A5C8() % 360;
        if (func_0019A5C8() % 2 != 0) {
            o->hA = 2;
        } else {
            o->hA = 0;
        }
        o->hC = o->h50;
        o->h50 = 0;
        o->h52 = func_0019A5C8() % 350 + 100;
        o->hE = func_0019A5C8() % 20 + 10;
        o->h8 = func_0019A5C8() % 35;
        o->h6 = func_0019A5C8() % 5 + 3;
        o->f30 = func_0019A5C8() % 40 - 20;
        o->f34 = func_0019A5C8() % 40 - 20;
        o->f38 = func_0019A5C8() % 40 - 20;
        o->f30 /= 60.0f;
        o->f34 /= 60.0f;
        o->f38 /= 60.0f;
        func_001F5F90(func_001F5380(), a);
        func_001F5620(func_001F53A0(), ctx->v, b);
        o->f3C = (a[2] - b[2]) / 80.0f;
        o->state = 2;
    }
    if (o->t < 90) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0xC0;
        }
    } else if (o->col[3] > 12) {
        o->col[3] -= 11;
    } else {
        o->state = 0;
    }
    if (o->t > 10 && o->t < 70) {
        o->x += o->f30;
        o->y += o->f34;
        o->z += o->f38;
    }
    if (o->t > 10 && o->t < 40) {
        o->y -= 0.05f;
    }
    func_001F5F90(func_001F5380(), c);
    if (o->t != 0) {
        o->z += o->f3C;
        o->f48 += 1.5f;
    }
    if (ctx->limit > 0x122) {
        o->t = 100;
    }
    o->t++;
    return 0;
}

/* shape b595:01E01420, 237 insns: the b276:01E01060 smoke-puff source with a red colour (0xFF, 0x80, 0x80), size
   15 growing 1.5 a tick, fade-in step 0xC0, an extra joint read each tick, and the tick jumped to 100 once the
   scene counter at ctx+0xDE1E passes 0x122; rises 0.05 a tick while sinking in b595:01E01060 (chatA, 16 Oct) */

typedef struct {
    u8 pad0[0xDDE8];
    s16 v;
    u8 padDDEA[0xDE1E - 0xDDEA];
    s16 limit;
} Ctx_b595_01E01420;

typedef struct {
    u8 pad00[6];
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
    s16 hE;
    f32 x, y, z;
    u8 pad1C[0x14];
    f32 f30;
    f32 f34;
    f32 f38;
    f32 f3C;
    u8 pad40[8];
    f32 f48;
    u8 pad4C[4];
    s16 h50;
    s16 h52;
    s16 t;
    s16 h56;
    s16 state;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
} Obj_b595_01E01420;

static s32 func_01E01420_b595(Ctx_b595_01E01420 *ctx, Obj_b595_01E01420 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F5380(void);
    extern s32 func_001F53A0(void);
    extern void func_001F5F90(s32, f32 *);
    extern void func_001F5620(s32, s32, f32 *);
    f32 a[4];
    f32 b[4];
    f32 c[4];

    if (o->state == 1) {
        o->f48 = 15.0f;
        o->h56 = (func_0019A5C8() >> 4) % 8;
        func_001076F0(o->col, 0xFF, 0x80, 0x80);
        o->h5A = func_0019A5C8() % 360;
        o->h5C = func_0019A5C8() % 360;
        if (func_0019A5C8() % 2 != 0) {
            o->hA = 2;
        } else {
            o->hA = 0;
        }
        o->hC = o->h50;
        o->h50 = 0;
        o->h52 = func_0019A5C8() % 350 + 100;
        o->hE = func_0019A5C8() % 20 + 10;
        o->h8 = func_0019A5C8() % 35;
        o->h6 = func_0019A5C8() % 5 + 3;
        o->f30 = func_0019A5C8() % 40 - 20;
        o->f34 = func_0019A5C8() % 40 - 20;
        o->f38 = func_0019A5C8() % 40 - 20;
        o->f30 /= 60.0f;
        o->f34 /= 60.0f;
        o->f38 /= 60.0f;
        func_001F5F90(func_001F5380(), a);
        func_001F5620(func_001F53A0(), ctx->v, b);
        o->f3C = (a[2] - b[2]) / 80.0f;
        o->state = 2;
    }
    if (o->t < 90) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0xC0;
        }
    } else if (o->col[3] > 12) {
        o->col[3] -= 11;
    } else {
        o->state = 0;
    }
    if (o->t > 10 && o->t < 70) {
        o->x += o->f30;
        o->y += o->f34;
        o->z += o->f38;
    }
    if (o->t > 10 && o->t < 40) {
        o->y += 0.05f;
    }
    func_001F5F90(func_001F5380(), c);
    if (o->t != 0) {
        o->z += o->f3C;
        o->f48 += 1.5f;
    }
    if (ctx->limit > 0x122) {
        o->t = 100;
    }
    o->t++;
    return 0;
}

/* shape b595:01E017E0, 348 insns: b595's scene manager (b069:01E01210 family): with a scene id (>= 0) it clears the
   scene, resets both camera blocks, keeps the id, sets the 315-frame countdown, takes three model handles, loads page-5
   textures 0..1, keeps the player's heading (degrees / 180), sets the three scales to 0.1 and fills the jitter tables
   (0..255: -15..14, then 100..179: 0..3 and 180..255: -8..7; second table -20..19); otherwise it runs the module's step
   and every live node's update, draws the nodes of the two sprite kinds with texture 0, rect 0x14 and the jitter table,
   counts down and returns 1 / 3 / 6 at frames 120 / 310 / 131..304, 8 once the countdown runs out */

typedef struct {
    u8 pad0[0x10];
    f32 x, y, z;
    u8 pad1C[0x28];
    void (*fn)();
    u8 pad48[0xE];
    s16 h56;
    s16 used;
    u8 pad5A[0x16];
} Node_b595_01E017E0;

typedef struct {
    u8 pad0[0x10];
    f32 sc[3];
    u8 pad1C[4];
    f32 px, py, pz;
    u8 pad2C[0x54];
    s32 ot2;
    u8 pad84[4];
    s32 tex88;
    u8 pad8C[8];
    Vec4f rect;
    u8 padA4[0x14];
    s16 hB8;
    u8 padBA[4];
    s16 hBE;
    s16 hC0;
    u8 padC2[0x16];
    u8 camD8[0x1C8];
    Node_b595_01E017E0 node[500];
    u8 padDD60[0xDD90 - 0xDD60];
    s32 tex5[2];
    u8 padDD98[0x18];
    s32 count;
    u8 padDDB4[8];
    s32 ot;
    u8 padDDC0[0x28];
    s16 model0;
    s16 model1;
    u8 padDDEC[0xC];
    s16 model2;
    u8 padDDFA[0x20];
    s16 ang;
    s16 id;
    s16 timer;
    s8 rnd[256];
    s8 rnd2[256];
} Scene_b595_01E017E0;

static s32 func_01E017E0_b595(s32 arg0, s32 id) {
    Scene_b595_01E017E0 *g = (Scene_b595_01E017E0 *)arg0;
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern s32 func_00202BF0(s32, s32);
    extern void func_001F6160(s32, void *);
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_01E00920_b595();
    extern void func_01E00E90_b595();
    extern void func_01E01060_b595();
    extern void b595_01E01420();
    s16 n;
    Vec4f r1;
    Vec4f r2;
    s32 iv[4];
    s32 i;
    s16 k;

    n = 0;
    g->ot = (s32)func_00207500();
    g->ot2 = (s32)func_00207500();
    if (id >= 0) {
        func_00195108(g, 0xE190);
        func_00107C10((u8 *)g + 0xE020);
        func_00107C10(g->camD8);
        g->id = id;
        g->count = 315;
        g->model0 = func_001F5560(func_001F53A0(), 0x42, 1);
        g->model1 = func_001F5560(func_001F53A0(), 0x45, 0);
        g->model2 = func_001F5560(func_001F5380(), 1, 1);
        for (i = 0; i < 2; i++) {
            g->tex5[i] = func_00202BF0(5, i);
        }
        func_001F6160(func_001F53A0(), iv);
        g->ang = iv[1] / 180.0f;
        g->sc[0] = 0.1f;
        g->sc[1] = 0.1f;
        g->sc[2] = 0.1f;
        for (k = 0; k < 256; k++) {
            g->rnd[k] = func_0019A5C8() % 30 - 15;
        }
        for (k = 100; k < 180; k++) {
            g->rnd[k] = func_0019A5C8() % 4;
        }
        for (k = 180; k < 256; k++) {
            g->rnd[k] = func_0019A5C8() % 16 - 8;
        }
        for (k = 0; k < 256; k++) {
            g->rnd2[k] = func_0019A5C8() % 40 - 20;
        }
        return 0;
    }
    func_01E00E90_b595(g, 0);
    for (k = 0; k < 500; k++) {
        if (g->node[k].used != 0) {
            if (g->node[k].fn != 0) {
                g->node[k].fn(g, &g->node[k]);
            }
        }
    }
    for (k = 0; k < 500; k++) {
        if (g->node[k].used != 0) {
            n++;
            if (g->node[k].fn == func_01E01060_b595) {
                func_00106080(&r1, 0x14, g->node[k].h56, 0);
                g->rect = r1;
                g->hC0 = 5;
                g->tex88 = g->tex5[0];
                g->hB8 = 1;
                g->px = g->node[k].x;
                g->py = g->node[k].y;
                g->pz = g->node[k].z;
                g->hBE = 0;
                func_01E00920_b595(g, &g->node[k], 16, g->rnd);
                g->hB8 = 0;
            }
            if (g->node[k].fn == b595_01E01420) {
                func_00106080(&r2, 0x14, g->node[k].h56, 0);
                g->rect = r2;
                g->hC0 = 5;
                g->tex88 = g->tex5[0];
                g->hB8 = 1;
                g->px = g->node[k].x;
                g->py = g->node[k].y;
                g->pz = g->node[k].z;
                g->hBE = 0;
                func_01E00920_b595(g, &g->node[k], 16, g->rnd);
                g->hB8 = 0;
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->timer == 120) {
        return 1;
    }
    if (g->timer == 310) {
        return 3;
    }
    if (g->timer > 130 && g->timer < 305) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b515:01E01BD0, 98 insns, 2 copies (b236:01E02330's code, generated by chatG/ovl/gen236.py): take a free effect slot (0x1f4 of 0x70 bytes), clear it, colour it from the
   owner's colour, place it at the owner's position; returns 1, or 0 if every slot is in use */

typedef struct Slot_b515_01E01BD0 {
    u8 pad0[0x10];
    f32 pos[3];
    u8 pad1C[0x24];
    s32 f40;
    s32 f44;
    u8 pad48[8];
    s16 f50;
    u8 pad52[6];
    s16 used;
    u8 pad5A[6];
    u8 c60[4];
    u8 c64[4];
    u8 pad68[8];
} Slot_b515_01E01BD0;

typedef struct Obj_b515_01E01BD0 {
    u8 pad0[0x250];
    f32 pos[3];
    u8 padA[0x2a0 - 0x250 - 12];
    Slot_b515_01E01BD0 slots[0x1f4];
    u8 padB[0xddb4 - 0x2a0 - 0x1f4 * 0x70];
    u8 rgba[4];
    u8 padC[0xde16 - 0xddb4 - 4];
    s16 fB2B0;
} Obj_b515_01E01BD0;

static s32 func_01E01D50_b595(Obj_b515_01E01BD0 *obj, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b515_01E01BD0 *s = NULL;
    s16 i;

    for (i = 0; i < 0x1f4; i++) {
        if (obj->slots[i].used == 0) {
            func_00195108(&obj->slots[i], 0x70);
            obj->slots[i].used = 1;
            s = &obj->slots[i];
            i = 0x1f4;
        }
    }
    if (s != NULL) {
        func_001076F0(s->c60, obj->rgba[0], obj->rgba[1], obj->rgba[2]);
        s->c60[3] = obj->rgba[3];
        func_001076F0(s->c64, obj->rgba[0], obj->rgba[1], obj->rgba[2]);
        s->c64[3] = obj->rgba[3];
        func_00106AB0(s, obj->pos, 0);
        s->pos[0] = obj->pos[0];
        s->pos[1] = obj->pos[1];
        s->pos[2] = obj->pos[2];
        s->f50 = obj->fB2B0;
        s->f40 = arg2;
        s->f44 = arg1;
        return 1;
    }
    return 0;
}

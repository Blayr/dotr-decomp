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

static void func_01E00080_b206(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

typedef struct {
    f32 x, y, z, w;
} Vec_b193_01E009B0;

typedef struct {
    u8 pad00[0x20];
    u8 rot[0x14];
    f32 y;
    u8 pad38[0x10];
    f32 w0;
    f32 w1;
    u8 pad50[0xA];
    s16 step;
    u8 pad5C[4];
    u8 col0[4];
    u8 col1[4];
} Anim_b193_01E009B0;

typedef struct {
    u8 pad00[0x80];
    s32 target;
    u8 pad84[0x54];
    u8 bD8[1];
} Obj_b193_01E009B0;

typedef struct {
    u8 b[0x90];
} Pkt_b193_01E009B0;

static void func_01E00920_b206(Obj_b193_01E009B0 *o, Anim_b193_01E009B0 *an, s32 mode, Vec_b193_01E009B0 pos) {
    extern void func_00107990(void *, void *, s32);
    extern void func_001092E0(void *, s32);
    extern void func_001094F0(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_00109380(void *, s32);
    extern void func_002075F0(void *, s32, s32);
    Vec_b193_01E009B0 quad[4];
    Vec_b193_01E009B0 at;
    Vec_b193_01E009B0 scale;
    f32 m[16];
    f32 depth __attribute__((aligned(16)));
    Pkt_b193_01E009B0 pkt;
    s32 a;
    s32 k;
    s16 j;
    Pkt_b193_01E009B0 *p;
    s16 blend;
    s32 kind;
    f32 w0;
    f32 w1;

    p = &pkt;
    j = 0;
    func_00107990(p, an->col0, 2);
    func_00107990(p, an->col1, 1);
    func_001092E0(p, 0);
    func_001094F0(p);
    blend = mode >> 4;
    if (blend == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((u64)blend << 2) | ((u64)0x80 << 32) | 0x40);
    }
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    at.x = pos.x;
    at.y = pos.y;
    at.z = pos.z;
    func_00108EF0(m, &scale, an->rot, &at);
    kind = mode & 0xF;
    quad[0].y = an->y;
    quad[1].y = an->y;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    w0 = an->w0;
    w1 = an->w1;
    for (k = 0; k < 36; k++) {
        if (k == 0) {
            a = an->step + j;
            quad[0].x = w0 * func_00108030(o->bD8, a, 1);
            quad[0].z = w0 * func_00108030(o->bD8, a, 0);
            quad[2].x = w1 * func_00108030(o->bD8, a, 1);
            quad[2].z = w1 * func_00108030(o->bD8, a, 0);
            a = j + (an->step + 10);
            quad[1].x = w0 * func_00108030(o->bD8, a, 1);
            quad[1].z = w0 * func_00108030(o->bD8, a, 0);
            quad[3].x = w1 * func_00108030(o->bD8, a, 1);
            quad[3].z = w1 * func_00108030(o->bD8, a, 0);
        } else {
            quad[0] = quad[1];
            quad[2] = quad[3];
            a = j + (an->step + 10);
            quad[1].x = w0 * func_00108030(o->bD8, a, 1);
            quad[1].z = w0 * func_00108030(o->bD8, a, 0);
            quad[3].x = w1 * func_00108030(o->bD8, a, 1);
            quad[3].z = w1 * func_00108030(o->bD8, a, 0);
        }
        if (kind == 0) {
            if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
                func_002075F0(p, o->target, (u32)depth);
            }
        } else if (kind == 1) {
            if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
                func_00109380(p, 1);
                func_002075F0(p, o->target, 0);
            }
        } else {
            if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
                func_002075F0(p, o->target, -1);
            }
        }
        j += 10;
    }
}

/* OVL_WARM */
/* z offset: in-place divide (fq = t; fq /= 20.0f;) puts the quotient in the dividend's register (chatA fix pass 16 Oct). */

typedef struct {
    f32 x, y, z, w;
} Vec_b020_01E00920;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Col_b020_01E00920;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b020_01E00920;

typedef struct {
    u64 st;
    Xyz_b020_01E00920 p;
} Vtx_b020_01E00920;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Col_b020_01E00920 c;
    Vtx_b020_01E00920 v[4];
    u8 tail[0x30];
} Pkt_b020_01E00920;

typedef struct {
    s32 rot[4];
    s32 v[4];
} Rot_b020_01E00920;

typedef struct {
    s8 x[100];
    s8 y[80];
    s8 z[1];
} Tbl_b020_01E00920;

typedef struct {
    u8 pad00[8];
    s16 base;
    u8 pad0A[0x3E];
    f32 size;
    u8 pad4C[4];
    s16 scale;
    u8 pad52[8];
    s16 spin;
    u8 pad5C[4];
    u8 col[1];
} Anim_b020_01E00920;

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
} Obj_b020_01E00920;

extern void b206_01E00080(Pkt_b020_01E00920 *, void *, s32);

static void func_01E00D80_b206(Obj_b020_01E00920 *o, Anim_b020_01E00920 *an, s32 mode, Tbl_b020_01E00920 *tbl) {
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
    Vec_b020_01E00920 quad[4];
    Vec_b020_01E00920 d;
    Vec_b020_01E00920 pos;
    Vec_b020_01E00920 scale;
    f32 depth __attribute__((aligned(16)));
    f32 m[16];
    Rot_b020_01E00920 r;
    struct {
        u64 pre;
        Pkt_b020_01E00920 pk;
    } buf;
    Col_b020_01E00920 col;
    s16 i;
    Pkt_b020_01E00920 *p;
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
    r.v[2] = an->spin;
    pos.x = o->x;
    pos.y = o->y;
    pos.z = o->z;
    func_00108EF0(m, &scale, 0, &pos);
    b206_01E00080(p, o->b94, o->hC0);
    kind = mode & 0xF;
    for (i = 0; i < o->count; i++) {
        func_00108CE0(quad, an->size, an->size);
        func_00109100(quad, &r, 1, o->bD8);
        func_00109100(quad, &r, 0, o->bD8);
        t = &tbl->x[i];
        h = i >> 1;
        d.x = t[an->base] / 20.0f * (an->scale + h);
        d.y = t[an->base + 100] / 20.0f * (an->scale + h);
        d.z = 0.0f;
        func_00108950(&d, r.v, 2, o->bD8);
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

/* shape b206:01E012D0, 160 insns: the b206 module's event step: counts ticks; keeps its point on the tracked point (ctx+0x4C48) pushed 2 along z by the scene flag and every other tick from 64 to 275 spawns b206:01E01550 with a slot cycling 0..119; then on the second point (camera id at ctx+0x4C56) pushed 50 the other way spawns b206:01E01770 until 300; at 100 spawns b206:01E01B80 for slots 0 and 1; at 56 spawns b206:01E019D0 at the two other tracked points */

typedef struct {
    u8 pad0[0x250];
    f32 pos[3];
    u8 pad25C[0x4C48 - 0x25C];
    s16 id0;
    s16 id1;
    s16 id2;
    u8 pad4C4E[0x4C56 - 0x4C4E];
    s16 id3;
    u8 pad4C58[0x4C76 - 0x4C58];
    s16 slot;
    s16 next;
    s16 flag;
    u8 pad4C7C[2];
    s16 timer;
} Ctx_b206_01E012D0;

static void func_01E012D0_b206(Ctx_b206_01E012D0 *g) {
    extern s32 b206_01E01550(void);
    extern s32 b206_01E01770(void);
    extern s32 b206_01E019D0(void);
    extern s32 b206_01E01B80(void);
    extern void b206_01E02320(Ctx_b206_01E012D0 *, s32 (*)(void), s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, f32 *);
    s16 i;
    s16 n;

    g->timer++;
    func_001F5620(func_001F53A0(), g->id0, g->pos);
    if (g->flag != 0) {
        g->pos[2] -= 2.0f;
    } else {
        g->pos[2] += 2.0f;
    }
    if (g->timer >= 64 && g->timer < 276) {
        if (g->timer % 2 == 1) {
            if (g->timer < 100) {
                n = 1;
            } else {
                n = 1;
            }
            for (i = 0; i < n; i++) {
                g->slot = g->next;
                b206_01E02320(g, b206_01E01550, 0);
                g->next++;
                if (g->next >= 120) {
                    g->next = 0;
                }
            }
        }
    }
    func_001F5620(func_001F5380(), g->id3, g->pos);
    if (g->flag != 0) {
        g->pos[2] += 50.0f;
    } else {
        g->pos[2] -= 50.0f;
    }
    if (g->timer < 301) {
        b206_01E02320(g, b206_01E01770, 0);
    }
    if (g->timer == 100) {
        g->slot = 0;
        b206_01E02320(g, b206_01E01B80, 0);
        g->slot = 1;
        b206_01E02320(g, b206_01E01B80, 0);
    }
    if (g->timer == 56) {
        func_001F5620(func_001F53A0(), g->id1, g->pos);
        g->slot = 0;
        b206_01E02320(g, b206_01E019D0, 0);
        func_001F5620(func_001F53A0(), g->id2, g->pos);
        g->slot = 0;
        b206_01E02320(g, b206_01E019D0, 0);
    }
}

/* shape b206:01E01550, 134 insns: a white rising ring: on start size 15, both colours 0x80; alpha up by 64 to 0x80 for
   35 ticks, then down by 9 until it ends; blinks 0x80/0x60 on odd/even ticks; spin 0x4000; f34 grows by 1.6 to 50, f30
   by 0.2 to 10; size grows by 7.5 with f4C = size - f34; h5C turns by 9; after the first tick it moves its height by 5
   (down when the game flag at g+0x4C7A is set) */

typedef struct {
    u8 pad0[0x4C7A];
    s16 down;
} Game_b206_01E01550;

typedef struct {
    u8 pad0[0x18];
    f32 y;
    u8 pad1C[4];
    s32 rot;
    u8 pad24[0xC];
    f32 f30;
    f32 f34;
    u8 pad38[0x10];
    f32 size;
    f32 f4C;
    u8 pad50[4];
    s16 t;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[2];
    s16 h5C;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b206_01E01550;

static s32 func_01E01550_b206(Game_b206_01E01550 *g, Obj_b206_01E01550 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->size = 15.0f;
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
        func_001076F0(o->c1, 0x80, 0x80, 0x80);
        o->mode = 2;
        o->c1[3] = 0;
    }
    if (o->t < 35) {
        if (o->c1[3] < 0x80) {
            o->c1[3] += 0x40;
        }
    } else if (o->c1[3] > 10) {
        o->c1[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
    } else {
        func_001076F0(o->c0, 0x60, 0x60, 0x60);
    }
    o->rot = 0x4000;
    if (o->f34 < 50.0f) {
        o->f34 += 1.6f;
    }
    if (o->f30 < 10.0f) {
        o->f30 += 0.2f;
    }
    o->size += 7.5f;
    o->f4C = o->size - o->f34;
    o->h5C += 9;
    o->t++;
    if (o->t != 0) {
        if (g->down != 0) {
            o->y -= 5.0f;
        } else {
            o->y += 5.0f;
        }
    }
    return 0;
}

/* shape b206:01E01770, 150 insns: red flare swelling on a half sine (height 12 x the model scale x sin(h5C), h5C stepping 9 and ending past 180), base rising 3.8 to 40; outer alpha up by 64 to 0x80 for 15 ticks, then down by 9; flickers 0x80/0xC0; drifts 2.5..5.5 along z by the scene flag */

typedef struct {
    u8 pad0[0xD8];
    u8 tab[0x4C7A - 0xD8];
    s16 flag;
} Ctx_b206_01E01770;

typedef struct {
    u8 pad0[0x18];
    f32 z;
    u8 pad1C[4];
    s32 rot[4];
    u8 pad30[4];
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    f32 f4C;
    u8 pad50[4];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[2];
    s16 ang;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b206_01E01770;

static s32 func_01E01770_b206(Ctx_b206_01E01770 *g, Fx_b206_01E01770 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F5380(void);
    extern f32 func_001F5860(s32);
    extern f32 func_00108030(void *, s16, s32);
    f32 sc;

    sc = func_001F5860(func_001F5380());
    if (o->mode == 1) {
        o->f48 = 15.0f;
        func_001076F0(o->col, 0x80, 0x10, 0x10);
        func_001076F0(o->col2, 0x80, 0x10, 0x10);
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 15) {
        if (o->col2[3] < 0x80) {
            o->col2[3] += 0x40;
        }
    } else if (o->col2[3] > 10) {
        o->col2[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->tick % 2 == 1) {
        func_001076F0(o->col, 0x80, 0x10, 0x10);
    } else {
        func_001076F0(o->col, 0xC0, 0x10, 0x10);
    }
    o->rot[0] = 0x4000;
    if (o->f34 < 40.0f) {
        o->f34 += 3.8f;
    }
    o->f48 = 12.0f * sc * func_00108030(g->tab, o->ang, 0);
    o->f4C = o->f48 - o->f34;
    o->ang += 9;
    if (o->ang > 180) {
        o->mode = 0;
    }
    o->tick++;
    if (g->flag != 0) {
        o->z -= 2.5f + func_0019A5C8() % 4;
    } else {
        o->z += 2.5f + func_0019A5C8() % 4;
    }
    return 0;
}

/* shape b206:01E019D0, 106 insns: b183:01E012F0 family: grey ring (size 60 growing 2 a frame, frame 0..6, start 5..14, growth 9..23) */

typedef struct {
    u8 pad00[6];
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
    s16 hE;
    u8 pad10[0x38];
    f32 f48;
    u8 pad4C[4];
    s16 h50;
    u8 pad52[2];
    s16 t;
    s16 h56;
    s16 state;
    s16 h5A;
    u8 pad5C[4];
    u8 col[4];
} Obj_b206_01E019D0;

static s32 func_01E019D0_b206(void *arg0, Obj_b206_01E019D0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f48 = 60.0f;
        o->h56 = func_0019A5C8() % 7;
        func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
        o->h5A = func_0019A5C8() % 360;
        o->hA = func_0019A5C8() % 8;
        o->hC = o->h50;
        o->h50 = func_0019A5C8() % 10 + 5;
        o->hE = func_0019A5C8() % 15 + 9;
        o->h8 = func_0019A5C8() % 35;
        o->h6 = func_0019A5C8() % 5 + 3;
        o->state = 2;
    }
    if (o->t < o->h6) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->state = 0;
    }
    o->f48 += 2.0f;
    if (o->t != 0) {
        o->h50 += o->hE;
    }
    o->t++;
    return 0;
}

/* shape b206:01E01B80, 140 insns: a swaying full-screen veil written into the scene's own packet (0x4C28): grey, both
   corners shifted sideways by the effect's sway (0x8), fixed texture window (0..0.625, 0..0.875), drawn with
   func_002075F0; the sway follows 15 x the sine of an angle turning 25 a tick (starting 0 or 180 by kind); alpha up
   by 10 (below 0x80) for 200 ticks, then down by 9 (ends below 11) */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b206_01E01B80;

typedef struct {
    f32 s, t;
    Xyz_b206_01E01B80 p;
} Tv_b206_01E01B80;

typedef struct {
    u8 pad0[0x10];
    u8 r, g, b, a;
    f32 q;
    Tv_b206_01E01B80 v[2];
} Tex_b206_01E01B80;

typedef struct {
    u8 pad0[0x4C28];
    Tex_b206_01E01B80 *pk;
    u8 pad4C2C[0x254];
    u8 sin[1];
} Scene_b206_01E01B80;

typedef struct {
    u8 pad0[8];
    s16 sway;
    u8 padA[0x46];
    s16 kind;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 mode;
    s16 ang;
    u8 pad5C[4];
    u8 col[4];
} Fx_b206_01E01B80;

static s32 func_01E01B80_b206(Scene_b206_01E01B80 *g, Fx_b206_01E01B80 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s16 func_001A22C0(f32);
    extern void func_002075F0(void *, s32, s32);
    s16 w;

    w = o->sway;
    if (o->mode == 1) {
        o->col[3] = 0;
        func_001076F0(o->col, 0x60, 0x60, 0x60);
        if (o->kind == 0) {
            o->ang = 0;
        }
        if (o->kind == 1) {
            o->ang = 180;
        }
        o->mode = 2;
    }
    g->pk->r = o->col[0];
    g->pk->g = o->col[1];
    g->pk->b = o->col[2];
    g->pk->a = o->col[3];
    g->pk->q = 1.0f;
    g->pk->v[0].p.x = (w + 0x6C0) * 16 - 8;
    g->pk->v[0].p.y = 0x71F8;
    g->pk->v[0].p.z = 0xFFFFFF;
    g->pk->v[0].p.f = 0;
    g->pk->v[1].p.x = (w + 0x940) * 16 - 8;
    g->pk->v[1].p.y = 0x8DF8;
    g->pk->v[1].p.z = 0xFFFFFF;
    g->pk->v[1].p.f = 0;
    g->pk->v[0].s = 0.0f;
    g->pk->v[0].t = 0.0f;
    g->pk->v[1].s = 0.625f;
    g->pk->v[1].t = 0.875f;
    func_002075F0(g->pk, 0, 0);
    o->sway = func_001A22C0(15.0f * func_00108030(g->sin, o->ang, 1));
    o->ang += 25;
    if (o->t < 200) {
        if (o->col[3] < 0x80) {
            o->col[3] += 10;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->t++;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b206", func_01E01DB0_b206);

/* shape b206:01E02320, 80 insns: twin of b034:01E05330: take a free effect slot (0x96 of 0x70 bytes), clear
   it, colour it from the scene colour, copy the scene position and value, store the two arguments; returns 1 if a
   slot was found */

typedef struct Slot_b206_01E02320 {
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
} Slot_b206_01E02320;

typedef struct Obj_b206_01E02320 {
    u8 pad0[0x250];
    f32 pos[3];
    u8 padA[0x44];
    Slot_b206_01E02320 slots[0x96];
    u8 padB[0x7D4];
    u8 rgba[4];
    u8 padC[0x5E];
    s16 fB2B0;
} Obj_b206_01E02320;

static s32 func_01E02320_b206(Obj_b206_01E02320 *obj, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b206_01E02320 *s = NULL;
    s16 i;

    for (i = 0; i < 0x96; i++) {
        if (obj->slots[i].used == 0) {
            func_00195108(&obj->slots[i], 0x70);
            obj->slots[i].used = 1;
            s = &obj->slots[i];
            i = 0x96;
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

/* shape b206:01E02460, 73 insns: draw pass for the effect pool: open a sprite packet on the stack (kept at 0x4C28, ot at
   0x4C24), texture from func_001F5380, then every used slot (0x96 of 0x70 bytes at 0x2A0) whose
   callback is b206:01E01B80 is drawn by it; close the ot if any slot was used */

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 body[0x30];
    u64 t40;
    u64 t48;
    u8 pad50[8];
} Pkt_b206_01E02460;

typedef struct {
    u8 pad0[0x44];
    void (*cb)(void *, void *);
    u8 pad48[0x10];
    s16 used;
    u8 pad5A[0x16];
} Slot_b206_01E02460;

typedef struct {
    u8 pad0[0x2A0];
    Slot_b206_01E02460 slots[0x96];
    u8 pad4440[0x7E4];
    s32 ot;
    Pkt_b206_01E02460 *pk;
} Scene_b206_01E02460;

static void func_01E02460_b206(Scene_b206_01E02460 *g) {
    extern void b206_01E01B80(void *, void *);
    extern s32 func_00207F60(void);
    extern void func_00208460(void);
    extern s32 func_001F5380(void);
    extern void func_001F7060(s32, s32, void *, void *);
    extern s32 func_00207500(void);
    extern void func_00207FD0(s32, s32, s32);
    Pkt_b206_01E02460 pkt __attribute__((aligned(8)));
    s32 i;
    s32 n;

    n = 0;
    g->pk = &pkt;
    g->ot = func_00207F60();
    g->pk->count = 0x26;
    g->pk->tag = 5;
    g->pk->regs = 0x42421;
    g->pk->pad = 0;
    func_00208460();
    func_002086D0(g->pk, ((u64)0x80 << 32) | 0x48);
    func_001F7060(func_001F5380(), 0, &pkt.t40, &pkt.t48);
    func_00208460();
    for (i = 0; i < 0x96; i++) {
        if (g->slots[i].used != 0) {
            n++;
            if (g->slots[i].cb == b206_01E01B80) {
                b206_01E01B80(g, &g->slots[i]);
            }
        }
    }
    if (n != 0) {
        func_00207FD0(g->ot, func_00207500(), 0);
    }
}

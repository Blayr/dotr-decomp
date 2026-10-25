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

static void func_01E00080_b708(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E00920_b708(Obj_b193_01E009B0 *o, Anim_b193_01E009B0 *an, s32 mode, Vec_b193_01E009B0 pos) {
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

extern void b708_01E00080(Pkt_b020_01E00920 *, void *, s32);

static void func_01E00D80_b708(Obj_b020_01E00920 *o, Anim_b020_01E00920 *an, s32 mode, Tbl_b020_01E00920 *tbl) {
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
    b708_01E00080(p, o->b94, o->hC0);
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

/* shape b708:01E012D0, 206 insns: b280:01E012D0's effect scene step: counts the frame (0x4C7E), places the spawn
   point on joint 0x4C48 nudged 2 along z (back with the flag 0x4C7A); from frame 30 to 170 spawns three b708:01E01610,
   at joints 0x4C48..0x4C4C on odd frames or 0x4C4E..0x4C52 on even ones; before frame 195, on even frames, puts the
   point at the camera jittered by -15..14 and spawns b708:01E01B10 and b708:01E01C00; turns the scene angle by 6 */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0x4C48 - 0x260];
    s16 ja[3];
    s16 jb[3];
    u8 pad4C54[0x4C70 - 0x4C54];
    s16 ang;
    u8 pad4C72[4];
    s16 side;
    u8 pad4C78[2];
    s16 flag;
    u8 pad4C7C[2];
    s16 t;
} Scene_b708_01E012D0;

static void func_01E012D0_b708(Scene_b708_01E012D0 *g) {
    extern s32 b708_01E01610(void);
    extern s32 b708_01E01B10(void);
    extern s32 b708_01E01C00(void);
    extern void b708_01E022D0(Scene_b708_01E012D0 *, s32 (*)(void), s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    s16 i;
    s16 n;

    g->t++;
    func_001F5620(func_001F53A0(), g->ja[0], &g->pos);
    if (g->flag != 0) {
        g->pos.z -= 2.0f;
    } else {
        g->pos.z += 2.0f;
    }
    if (g->t >= 30 && g->t < 171 && g->t != 0) {
        if (g->t < 100) {
            n = 3;
        } else {
            n = 3;
        }
        for (i = 0; i < n; i++) {
            g->side = g->t % 6;
            if (g->t % 2 == 1) {
                func_001F5620(func_001F53A0(), g->ja[i], &g->pos);
            } else {
                func_001F5620(func_001F53A0(), g->jb[i], &g->pos);
            }
            b708_01E022D0(g, b708_01E01610, 0);
        }
    }
    if (g->t < 195) {
        if (g->t % 2 == 0) {
            n = 1;
        } else {
            n = 0;
        }
        for (i = 0; i < n; i++) {
            g->side = g->t % 2;
            func_001F5F90(func_001F5380(), &g->pos);
            g->pos.x += func_0019A5C8() % 30 - 15;
            g->pos.y += func_0019A5C8() % 30 - 15;
            g->pos.z += func_0019A5C8() % 30 - 15;
            b708_01E022D0(g, b708_01E01B10, 0);
            b708_01E022D0(g, b708_01E01C00, 0);
        }
    }
    g->ang += 6;
    if (g->ang >= 360) {
        g->ang %= 360;
    }
}

/* shape b708:01E01610, 319 insns: a magenta wing beat on one side of the b708 scene (side flag 0x4C7A picks the colour
   slot, the drift and the tilt direction): size 5 that swells 7.5 a tick for 8 ticks and then on a sine, tilts up
   to 50 and spreads to 6, flashes grey every other tick, fades in for 25 ticks then out by 9, drifts sideways and
   falls; late in the scene (0x4C7E past 201) it ages 25 a tick */

typedef struct {
    u8 pad0[0x4C7A];
    s16 side;
    u8 pad4C7C[2];
    s16 step;
    u8 pad4C80[0x200];
    u8 table[1];
} Scene_b708_01E01610;

typedef struct {
    u8 pad0[0x10];
    f32 x;
    f32 y;
    f32 z;
    u8 pad1C[4];
    s32 rot;
    u8 pad24[0xC];
    f32 spread;
    f32 tilt;
    f32 swing;
    u8 pad3C[0xC];
    f32 size;
    f32 top;
    s16 flip;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 ang;
    s16 h5C;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Wing_b708_01E01610;

static s32 func_01E01610_b708(Scene_b708_01E01610 *g, Wing_b708_01E01610 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    if (o->state == 1) {
        o->size = 5.0f;
        if (g->side != 0) {
            func_001076F0(o->c0, 0x80, 0x10, 0xFF);
            func_001076F0(o->c1, 0x80, 0x10, 0xFF);
        } else {
            func_001076F0(o->c1, 0x80, 0x10, 0xFF);
            func_001076F0(o->c0, 0x80, 0x10, 0xFF);
        }
        o->state = 2;
        if (o->flip != 0) {
            o->h5C = 0;
        } else {
            o->h5C = 0xB4;
        }
        o->swing = 0.0f;
        o->c1[3] = 0;
    }
    if (o->t < 25) {
        if (g->side != 0) {
            if (o->c1[3] < 0x80) {
                o->c1[3] += 0x80;
            }
        } else if (o->c0[3] < 0x80) {
            o->c0[3] += 0x80;
        }
    } else if (g->side != 0) {
        if (o->c1[3] > 10) {
            o->c1[3] -= 9;
        } else {
            o->state = 0;
        }
    } else if (o->c0[3] > 10) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    if (g->side != 0) {
        if (o->t % 2 == 1) {
            func_001076F0(o->c0, 0x80, 0x80, 0x80);
        } else {
            func_001076F0(o->c0, 0x60, 0x60, 0x60);
        }
    } else if (o->t % 2 == 1) {
        func_001076F0(o->c1, 0x80, 0x80, 0x80);
    } else {
        func_001076F0(o->c1, 0x60, 0x60, 0x60);
    }
    o->rot = 0x4000;
    if (g->side != 0) {
        if (o->tilt < 50.0f) {
            o->tilt += 1.6f;
        }
    } else if (o->tilt > -50.0f) {
        o->tilt -= 1.6f;
    }
    if (o->spread < 6.0f) {
        o->spread += 0.8f;
    }
    if (o->t >= 10) {
        o->ang += 30;
    }
    if (o->t < 8) {
        o->size += 7.5f;
    } else {
        o->size += o->swing + 26.5f * func_00108030(g->table, o->ang, 0);
        if (o->swing < 20.0f) {
            o->swing += 0.2f;
        }
    }
    o->top = o->size - o->tilt;
    o->h5C += 20;
    if (o->t > 2) {
        if (o->flip == 0) {
            if (g->side != 0) {
                o->x += 0.4f;
            } else {
                o->x -= 0.4f;
            }
        } else if (g->side != 0) {
            o->x -= 0.4f;
        } else {
            o->x += 0.4f;
        }
    }
    o->t++;
    if (o->t != 0) {
        if (g->side != 0) {
            o->z -= 5.0f;
        } else {
            o->z += 5.0f;
        }
        o->y -= 0.5f;
    }
    if (g->step > 0xC9) {
        o->t += 25;
    }
    return 0;
}

/* shape b708:01E01B10, 60 insns: a growing glow: on start f48 5, colour 0xC0 grey, second colour (0x80, 0x10, 0xFF)
   with alpha 0; alpha grows by 0x40 (below 0x80) for 6 ticks, then fades by 14 and stops; the rotation at 0x20
   advances 0x4000 and f48 grows by 3.5 each tick */

typedef struct {
    u8 pad0[0x20];
    s32 rot[4];
    u8 pad30[0x18];
    f32 f48;
    u8 pad4C[8];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
    u8 col2[4];
} Fx_b708_01E01B10;

static s32 func_01E01B10_b708(s32 arg0, Fx_b708_01E01B10 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 5.0f;
        func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
        func_001076F0(o->col2, 0x80, 0x10, 0xFF);
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 6) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 0xF) {
        o->col[3] -= 14;
    } else {
        o->mode = 0;
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->f48 += 3.5f;
    o->tick++;
    return 0;
}

/* shape b708:01E01C00, 106 insns: a pale growing spark (b082:01E02400 shape): size 20 growing by 2, random sub-frame 0..6, angle,
   frame 0..7, start height 5..14 (old one kept), rise 9..23 once started, width 0..34, hold 3..7; full alpha, then down by 15 */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 w;
    s16 frame;
    s16 y0;
    s16 step;
    u8 pad10[0x38];
    f32 size;
    u8 pad4C[4];
    s16 y;
    u8 pad52[2];
    s16 t;
    s16 sub;
    s16 state;
    s16 ang;
    u8 pad5C[4];
    u8 c0[4];
} Obj_b708_01E01C00;

static s32 func_01E01C00_b708(void *arg0, Obj_b708_01E01C00 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = 20.0f;
        o->sub = func_0019A5C8() % 7;
        func_001076F0(o->c0, 0xC0, 0xC0, 0xC0);
        o->ang = func_0019A5C8() % 360;
        o->frame = func_0019A5C8() % 8;
        o->y0 = o->y;
        o->y = func_0019A5C8() % 10 + 5;
        o->step = func_0019A5C8() % 15 + 9;
        o->w = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 5 + 3;
        o->state = 2;
    }
    if (o->t < o->hold) {
        o->c0[3] = 0x80;
    } else if (o->c0[3] > 0x10) {
        o->c0[3] -= 0xF;
    } else {
        o->state = 0;
    }
    o->size += 2.0f;
    if (o->t != 0) {
        o->y += o->step;
    }
    o->t++;
    return 0;
}

/* shape b027:01E00DA0, 2 insns, 89 copies: an empty handler that returns 0 */

static s32 func_01E01DB0_b708(void) {
    return 0;
}

/* shape b708:01E01DC0, 324 insns: the b708 module's main step (b538:01E00EA0 family): keeps two order tables; with a
   code it clears the scene, sets up its two coordinates, keeps the code and a 210-tick timer, the model's joints
   0x25/0x29/0x2D/0x53/0x57/0x5B, texture (5,0), the camera's turned-back side (turn / 180), scale 0.1 and three noise
   tables (-12..11, 0..3 from 100, -20..19); otherwise it runs the scene script (b708:01E012D0), every live slot's
   handler (150 of 0x70 bytes) except the idle one, then draws the wings (b708:01E01610) as magic circles swung by the
   scene angle, the flashes (b708:01E01B10) as rings and the glows (b708:01E01C00) as gas; counts the timer down and
   returns 1 / 3 at steps 120 / 205, 6 between 131 and 199, 8 when the timer ends */

typedef struct {
    u8 pad0[0xA];
    s16 hA;
    u8 padC[4];
    Vec4f pos;
    u8 pad20[0x10];
    f32 f30;
    u8 pad34[0x10];
    s32 (*fn)(void *, void *);
    u8 pad48[0xE];
    s16 frame;
    s16 used;
    u8 pad5A[2];
    s16 h5C;
    u8 pad5E[0x12];
} Slot_b708_01E01DC0;

typedef struct {
    u8 pad0[0x10];
    f32 sx, sy, sz;
    u8 pad1C[4];
    f32 px, py, pz;
    u8 pad2C[0x54];
    s32 ot;
    u8 pad84[4];
    s32 tex88;
    u8 pad8C[8];
    Vec4f rect;
    u8 padA4[0x14];
    s16 hB8;
    u8 padBA[6];
    s16 hC0;
    u8 padC2[0x16];
    u8 crdD8[0x2A0 - 0xD8];
    Slot_b708_01E01DC0 slot[150];
    u8 pad4440[0x7B0];
    s32 tex[1];
    u8 pad4BF4[0x1C];
    s32 timer;
    u8 pad4C14[8];
    s32 ot2;
    u8 pad4C20[0x28];
    s16 joint[6];
    u8 pad4C54[0x1C];
    s16 ang;
    u8 pad4C72[8];
    s16 turn;
    s16 code;
    s16 step;
    s8 noise[0x100];
    s8 noise2[0x100];
    u8 crd4E80[1];
} Scene_b708_01E01DC0;

static s32 func_01E01DC0_b708(s32 arg0, s32 code) {
    extern void b708_01E012D0();
    extern s32 b708_01E01DB0();
    extern s32 b708_01E01610();
    extern s32 b708_01E01B10();
    extern s32 b708_01E01C00();
    extern void b708_01E02420(void *, void *, s32, Vec4f);
    extern void b708_01E00920(void *, void *, s32, Vec4f);
    extern void b708_01E00D80();
    Scene_b708_01E01DC0 *g = (Scene_b708_01E01DC0 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_001F53A0(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F6160(s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00106080(void *, s32, s32, void *);
    extern f32 func_00108030(void *, s16, s32);
    Vec4f p;
    f32 rm[4];
    s32 ang[4];
    s32 k;
    s16 n;
    s16 i;

    n = 0;
    g->ot2 = func_00207500();
    g->ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x4FF0);
        func_00107C10(g->crd4E80);
        func_00107C10(g->crdD8);
        g->code = code;
        g->timer = 210;
        g->joint[0] = func_001F5560(func_001F53A0(), 0x25, 1);
        g->joint[1] = func_001F5560(func_001F53A0(), 0x29, 0);
        g->joint[2] = func_001F5560(func_001F53A0(), 0x2D, 0);
        g->joint[3] = func_001F5560(func_001F53A0(), 0x53, 0);
        g->joint[4] = func_001F5560(func_001F53A0(), 0x57, 0);
        g->joint[5] = func_001F5560(func_001F53A0(), 0x5B, 0);
        for (k = 0; k < 1; k++) {
            g->tex[k] = func_00202BF0(5, k);
        }
        func_001F6160(func_001F53A0(), ang);
        g->turn = (s16)(ang[1] / 180.0f);
        g->sx = 0.1f;
        g->sy = 0.1f;
        g->sz = 0.1f;
        for (i = 0; i < 0x100; i++) {
            g->noise[i] = func_0019A5C8() % 24 - 12;
        }
        for (i = 100; i < 180; i++) {
            g->noise[i] = func_0019A5C8() % 4;
        }
        for (i = 0; i < 0x100; i++) {
            g->noise2[i] = func_0019A5C8() % 40 - 20;
        }
        return 0;
    }
    b708_01E012D0(g, 0);
    for (i = 0; i < 150; i++) {
        if (g->slot[i].used != 0) {
            if (g->slot[i].fn != NULL && g->slot[i].fn != b708_01E01DB0) {
                g->slot[i].fn(g, &g->slot[i]);
            }
        }
    }
    for (i = 0; i < 150; i++) {
        if (g->slot[i].used != 0) {
            n++;
            if (g->slot[i].fn == b708_01E01610) {
                p = g->slot[i].pos;
                p.x += g->slot[i].f30 * func_00108030(g->crdD8, g->slot[i].h5C + g->ang, 0);
                b708_01E02420(g, &g->slot[i], 0x20, p);
            }
            if (g->slot[i].fn == b708_01E01B10) {
                n++;
                p = g->slot[i].pos;
                b708_01E00920(g, &g->slot[i], 0x20, p);
            }
            if (g->slot[i].fn == b708_01E01C00) {
                func_00106080(rm, 0x14, g->slot[i].frame, 0);
                g->rect = *(Vec4f *)rm;
                g->tex88 = g->tex[0];
                g->hB8 = 6;
                g->hC0 = g->slot[i].hA;
                g->px = g->slot[i].pos.x;
                g->py = g->slot[i].pos.y;
                g->pz = g->slot[i].pos.z;
                b708_01E00D80(g, &g->slot[i], 0x20, g->noise);
                g->hB8 = 0;
            }
        }
    }
    if (g->timer != 0) {
        g->timer--;
    }
    if (g->step == 120) {
        return 1;
    }
    if (g->step == 205) {
        return 3;
    }
    if (g->step > 130 && g->step < 200) {
        return 6;
    }
    if (g->timer <= 0) {
        return 8;
    }
    return 0;
}

/* shape b280:01E02530, 82 insns, 2 copies: spawns an effect into the first free slot (150 of 0x70 bytes): clears it, marks it
   live, both colours from the scene, placed at the scene position, with the caller's handler and argument */

typedef struct {
    u8 pad0[0x10];
    f32 x, y, z;
    u8 pad1C[0x24];
    s32 w40;
    s32 w44;
    u8 pad48[8];
    s16 h50;
    s16 h52;
    u8 pad54[4];
    s16 active;
    u8 pad5A[6];
    u8 c0[4];
    u8 c1[4];
    u8 pad68[8];
} Slot_b280_01E02530;

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0x40];
    Slot_b280_01E02530 slot[150];
    u8 pad4500[0x4C14 - 0x2A0 - 150 * 0x70];
    u8 col[4];
    u8 pad4C18[0x5E];
    s16 h4C76;
} Scene_b280_01E02530;

static s32 func_01E022D0_b708(Scene_b280_01E02530 *s, s32 fn, s32 arg) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b280_01E02530 *sl;
    s16 i;

    sl = NULL;
    for (i = 0; i < 150; i++) {
        if (s->slot[i].active == 0) {
            func_00195108(&s->slot[i], 0x70);
            s->slot[i].active = 1;
            sl = &s->slot[i];
            i = 150;
        }
    }
    if (sl != NULL) {
        func_001076F0(sl->c0, s->col[0], s->col[1], s->col[2]);
        sl->c0[3] = s->col[3];
        func_001076F0(sl->c1, s->col[0], s->col[1], s->col[2]);
        sl->c1[3] = s->col[3];
        func_00106AB0(sl, &s->pos, 0);
        sl->x = s->pos.x;
        sl->y = s->pos.y;
        sl->z = s->pos.z;
        sl->h50 = s->h4C76;
        sl->h52 = s->h4C76;
        sl->w40 = arg;
        sl->w44 = fn;
        return 1;
    }
    return 0;
}

/* shape b708:01E02420, 262 insns: draws a ring of 18 segments (20 table steps each) between an inner and an outer
   radius around a position (passed by value), the inner edge raised to the data's height; blend from flags >> 4,
   depth mode flags & 0xF (b082:01E00920 family) */

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[0x54];
    u8 table[1];
} Obj_b708_01E02420;

typedef struct {
    u8 pad00[0x20];
    Vec4f rot;
    u8 pad30[4];
    f32 height;
    u8 pad38[0x10];
    f32 inner;
    f32 outer;
    u8 pad50[0x0A];
    s16 step;
    u8 pad5C[4];
    u8 mode0[4];
    u8 mode1[4];
} Data_b708_01E02420;

static void func_01E02420_b708(Obj_b708_01E02420 *o, Data_b708_01E02420 *data, s32 flags, Vec4f pos) {
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    Vec4f quad[4];
    Vec4f t;
    Vec4f scale;
    f32 m[16];
    f32 depth[4];
    u8 packet[0x90];
    s32 i;
    f32 inner;
    s16 j;
    s16 alpha;
    f32 outer;
    u8 *pkt;
    s32 a;
    s32 mode;

    pkt = packet;
    j = 0;
    func_00107990(pkt, data->mode0, 2);
    func_00107990(pkt, data->mode1, 1);
    func_001092E0(pkt, 0);
    func_001094F0(pkt);
    alpha = flags >> 4;
    if (alpha == 0) {
        func_002086D0(pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(pkt, ((s64)alpha << 2) | (((u64)0x80 << 32) | 0x40));
    }
    scale.x = 0.1f;
    t.x = pos.x;
    scale.y = 0.1f;
    t.y = pos.y;
    scale.z = 0.1f;
    t.z = pos.z;
    func_00108EF0(m, &scale, &data->rot, &t);
    mode = flags & 0xF;
    i = 0;
    quad[0].y = data->height;
    quad[1].y = data->height;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    inner = data->inner;
    outer = data->outer;
    do {
        if (i == 0) {
            a = data->step + j;
            quad[0].x = inner * func_00108030(o->table, a, 1);
            quad[0].z = inner * func_00108030(o->table, a, 0);
            quad[2].x = outer * func_00108030(o->table, a, 1);
            quad[2].z = outer * func_00108030(o->table, a, 0);
            a = j + 20;
            quad[1].x = inner * func_00108030(o->table, a, 1);
            quad[1].z = inner * func_00108030(o->table, a, 0);
            quad[3].x = outer * func_00108030(o->table, a, 1);
            quad[3].z = outer * func_00108030(o->table, a, 0);
        } else {
            quad[0] = quad[1];
            quad[2] = quad[3];
            a = j + 20;
            quad[1].x = inner * func_00108030(o->table, a, 1);
            quad[1].z = inner * func_00108030(o->table, a, 0);
            quad[3].x = outer * func_00108030(o->table, a, 1);
            quad[3].z = outer * func_00108030(o->table, a, 0);
        }
        if (mode == 0) {
            if (func_00205630(quad, 0x70000000, m, pkt, depth) != 0) {
                func_002075F0(pkt, o->ot, (u32)depth[0]);
            }
        } else if (mode == 1) {
            if (func_00205630(quad, 0x70000000, m, pkt, depth) != 0) {
                func_00109380(pkt, 1);
                func_002075F0(pkt, o->ot, 0);
            }
        }
        j += 20;
        i++;
    } while (i < 18);
}

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

static void func_01E00080_b280(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E00920_b280(Obj_b193_01E009B0 *o, Anim_b193_01E009B0 *an, s32 mode, Vec_b193_01E009B0 pos) {
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

extern void b280_01E00080(Pkt_b020_01E00920 *, void *, s32);

static void func_01E00D80_b280(Obj_b020_01E00920 *o, Anim_b020_01E00920 *an, s32 mode, Tbl_b020_01E00920 *tbl) {
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
    b280_01E00080(p, o->b94, o->hC0);
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

/* shape b280:01E012D0, 191 insns: the effect scene's step: counts the frame (0x4C7E), places the spawn point on joint
   0x4C48 nudged 2 along z (back with the flag 0x4C7A); from frame 64 to 320 it spawns a 0x1E015D0 at joint 0x4C4A or
   0x4C4C by odd/even frame, and every frame a 0x1E01AA0 the same way (0.8 back when flagged); it then parks the point
   on the other model's joint 0x4C56 pushed 3 x its speed along z, and turns the scene angle by 6 */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0x49E8];
    s16 j48;
    s16 j4A;
    s16 j4C;
    u8 pad4C4E[8];
    s16 j56;
    u8 pad4C58[0x18];
    s16 ang;
    u8 pad4C72[4];
    s16 side;
    u8 pad4C78[2];
    s16 flag;
    u8 pad4C7C[2];
    s16 t;
} Scene_b280_01E012D0;

static void func_01E012D0_b280(Scene_b280_01E012D0 *g) {
    extern void b280_01E015D0(void);
    extern void b280_01E01AA0(void);
    extern s32 b280_01E02530(Scene_b280_01E012D0 *, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);
    extern f32 func_001F5860(s32);
    s16 i;
    s16 n;

    g->t++;
    func_001F5620(func_001F53A0(), g->j48, &g->pos);
    if (g->flag != 0) {
        g->pos.z -= 2.0f;
    } else {
        g->pos.z += 2.0f;
    }
    if (g->t >= 64 && g->t < 321 && g->t != 0) {
        if (g->t < 100) {
            n = 1;
        } else {
            n = 1;
        }
        for (i = 0; i < n; i++) {
            g->side = g->t % 2;
            if (g->side != 0) {
                func_001F5620(func_001F53A0(), g->j4A, &g->pos);
            } else {
                func_001F5620(func_001F53A0(), g->j4C, &g->pos);
            }
            b280_01E02530(g, (s32)b280_01E015D0, 0);
        }
    }
    if (g->t != 0) {
        for (i = 0; i < 1; i++) {
            g->side = g->t % 2;
            if (g->side != 0) {
                func_001F5620(func_001F53A0(), g->j4A, &g->pos);
            } else {
                func_001F5620(func_001F53A0(), g->j4C, &g->pos);
            }
            if (g->flag != 0 && g->flag != 0) {
                g->pos.z -= 0.8f;
            }
            b280_01E02530(g, (s32)b280_01E01AA0, 0);
        }
    }
    func_001F5620(func_001F5380(), g->j56, &g->pos);
    if (g->flag != 0) {
        g->pos.z += 3.0f * func_001F5860(func_001F5380());
    } else {
        g->pos.z -= 3.0f * func_001F5860(func_001F5380());
    }
    g->ang += 6;
    if (g->ang >= 360) {
        g->ang %= 360;
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b280", func_01E015D0_b280);

/* shape b280:01E01AA0, 244 insns (B280_OBJ_MOVE_3_): a two-colour sprite whose side follows the scene flag at
   ctx+0x4C7A: on start size 5 and both colours (0x80,0x80,0x10), the second one clear; for 7 ticks the flagged
   colour's alpha grows by 0x40 (below 0x80), then fades by 9 and the object stops; the other colour blinks
   0x80/0x60 by tick parity; turn 0x4000; f34 swings by 1.6 towards +50 (flag) or -50, f30 grows by 0.2 up to 10,
   the angle turns 30 a tick from tick 10, the size grows 3.5 a tick and f4C = size - f34; from tick 3 x drifts 0.3
   a tick, its sign set by the flag and the object's side (h50) */

typedef struct {
    u8 pad0[0x4C7A];
    s16 flag;
} Ctx_b280_01E01AA0;

typedef struct {
    u8 pad0[0x10];
    f32 x, y, z;
    u8 pad1C[4];
    s32 rot[4];
    f32 f30;
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    f32 f4C;
    s16 side;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 ang;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
} Obj_b280_01E01AA0;

static s32 func_01E01AA0_b280(Ctx_b280_01E01AA0 *g, Obj_b280_01E01AA0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f48 = 5.0f;
        if (g->flag) {
            func_001076F0(o->col, 0x80, 0x80, 0x10);
            func_001076F0(o->col2, 0x80, 0x80, 0x10);
        } else {
            func_001076F0(o->col2, 0x80, 0x80, 0x10);
            func_001076F0(o->col, 0x80, 0x80, 0x10);
        }
        o->state = 2;
        o->col2[3] = 0;
    }
    if (o->t < 7) {
        if (g->flag) {
            if (o->col2[3] < 0x80) {
                o->col2[3] += 0x40;
            }
        } else if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (g->flag) {
        if (o->col2[3] > 10) {
            o->col2[3] -= 9;
        } else {
            o->state = 0;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->state = 0;
    }
    if (g->flag) {
        if (o->t % 2 == 1) {
            func_001076F0(o->col, 0x80, 0x80, 0x80);
        } else {
            func_001076F0(o->col, 0x60, 0x60, 0x60);
        }
    } else if (o->t % 2 == 1) {
        func_001076F0(o->col2, 0x80, 0x80, 0x80);
    } else {
        func_001076F0(o->col2, 0x60, 0x60, 0x60);
    }
    o->rot[0] = 0x4000;
    if (g->flag) {
        if (o->f34 < 50.0f) {
            o->f34 += 1.6f;
        }
    } else if (o->f34 > -50.0f) {
        o->f34 -= 1.6f;
    }
    if (o->f30 < 10.0f) {
        o->f30 += 0.2f;
    }
    if (o->t >= 10) {
        o->ang += 30;
    }
    o->f48 += 3.5f;
    o->f4C = o->f48 - o->f34;
    if (o->t > 2) {
        if (o->side == 0) {
            if (g->flag) {
                o->x += 0.3f;
            } else {
                o->x -= 0.3f;
            }
        } else if (g->flag) {
            o->x -= 0.3f;
        } else {
            o->x += 0.3f;
        }
    }
    o->t++;
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

static s32 func_01E01E70_b280(void *arg0, Obj_b206_01E019D0 *o) {
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

/* shape b027:01E00DA0, 2 insns, 89 copies: an empty handler that returns 0 */

static s32 func_01E02020_b280(void) {
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b280", func_01E02030_b280);

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

static s32 func_01E02530_b280(Scene_b280_01E02530 *s, s32 fn, s32 arg) {
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

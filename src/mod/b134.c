#include "common.h"

typedef struct {
    f32 x, y, z, w;
} Vec_b004_01E00B40;

static s32 func_01E00080_b134(Vec_b004_01E00B40 *trail, s32 n, s32 arg2) {
    extern s32 func_001F53A0();
    s32 k;
    Vec_b004_01E00B40 *dst;
    Vec_b004_01E00B40 *src;
    Vec_b004_01E00B40 pos;
    s32 i;

    src = trail;
    k = n - 1;
    dst = trail;
    src--;
    func_001F5620(func_001F53A0(trail), arg2, (s32)&pos);
    for (i = 0; i < n; i++) {
        if (k != 0) {
            dst->x = src->x;
            dst->y = src->y;
            dst->z = src->z;
        } else {
            dst->x = pos.x;
            dst->y = pos.y;
            dst->z = pos.z;
        }
        dst--;
        src--;
        k--;
    }
    return 0;
}

/* shape b018:01E00C50: draws a flat ring of 18 quads around a point (radius obj->radius, angle step 0x14),
   scaled 0.1, turned a quarter, through the module's GS packet. */

typedef struct {
    s16 x, y, z;
    s16 pad6;
    s16 dx, dy, dz;
    u8 padE[0x1A];
    s32 tex0;
    s32 tex1;
    u8 pad30[8];
    s16 radius;
    s16 angle;
} Obj_b018_01E00C50;

static void func_01E00150_b134(u8 *self, Obj_b018_01E00C50 *obj, void *pk) {
    extern f32 func_00108030(s32, s16, s32);
    extern void func_00108EF0();
    Vec4f q[4];
    Vec4f pos;
    Vec4f scale;
    f32 mat[16];
    f32 depth[4];
    s32 rot[4];
    s32 i;
    s16 a;
    s32 k;
    f32 fx;
    f32 fy;
    f32 fz;

    a = 0;
    func_00107990(pk, (u8 *)&obj->tex0, 1);
    func_00107990(pk, (u8 *)&obj->tex1, 2);
    func_001092E0(pk, 0);
    func_001094F0(pk);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    rot[0] += 0x4000;
    fx = obj->dx;
    fy = obj->dy;
    fz = obj->dz;
    fx /= 10.0f;
    fy /= 10.0f;
    fz /= 10.0f;
    pos.x = obj->x + fx;
    pos.y = obj->y + fy;
    pos.z = obj->z + fz;
    func_00108EF0(mat, &scale, rot, &pos);
    q[0].y = 0.0f;
    q[1].y = 0.0f;
    q[2].y = 0.0f;
    q[3].y = 0.0f;
    q[0].x = 0.0f;
    q[0].z = 0.0f;
    q[1].x = 0.0f;
    q[1].z = 0.0f;
    for (i = 0; i < 18; i++) {
        k = obj->angle + a;
        q[2].x = (f32)obj->radius * func_00108030((s32)(self + 0xD8), k, 1);
        q[2].z = (f32)obj->radius * func_00108030((s32)(self + 0xD8), k, 0);
        k = a + (obj->angle + 0x14);
        q[3].x = (f32)obj->radius * func_00108030((s32)(self + 0xD8), k, 1);
        q[3].z = (f32)obj->radius * func_00108030((s32)(self + 0xD8), k, 0);
        if (func_00205630((s32)q, 0x70000000, (s32)mat, (s32)pk, depth) != 0) {
            func_002075F0((s32)pk, *(s32 *)(self + 0x80), func_001A23B0(depth[0]));
        }
        a += 0x14;
    }
}

typedef struct {
    f32 x, y, z, w;
} Vec_b018_01E00EE0;


/* static in its module (callers that include this file #define OVL_LOCAL static first) */

static Vec_b018_01E00EE0 func_01E003E0_b134(Vec_b018_01E00EE0 *p, s32 type, f32 t) {
    Vec_b018_01E00EE0 r;
    f32 b0;
    f32 b1;
    f32 b2;
    f32 b3;

    if (type == 0) {
        b0 = -t * ((t - 1.0f) * (t - 2.0f)) / 6.0f;
        b1 = (t - 2.0f) * ((1.0f + t) * (t - 1.0f)) / 2.0f;
        b2 = -(1.0f + t) * (t * (t - 2.0f)) / 2.0f;
        b3 = (1.0f + t) * (t * (t - 1.0f)) / 6.0f;
    } else if (type == 1) {
        b0 = (1.0f - t) * ((1.0f - t) * (1.0f - t)) / 6.0f;
        b1 = 2.0f / 3.0f + ((t * (t * t)) / 2.0f - (t * t));
        b2 = 1.0f / 6.0f + (t / 2.0f + (-(t * (t * t)) / 2.0f + (t * t) / 2.0f));
        b3 = (t * (t * t)) / 6.0f;
    } else if (type == 2) {
        b0 = (1.0f - t) * ((1.0f - t) * (1.0f - t));
        b1 = 1.75f * (t * (t * t)) - 4.5f * (t * t) + 3.0f * t;
        b2 = -(11.0f / 12.0f * (t * (t * t))) + 1.5f * (t * t);
        b3 = 1.0f / 6.0f * (t * (t * t));
    } else if (type == 3) {
        b0 = 0.25f * ((1.0f - t) * ((1.0f - t) * (1.0f - t)));
        b1 = 7.0f / 12.0f + (7.0f / 12.0f * (t * (t * t)) - 1.25f * (t * t) + 0.25f * t);
        b2 = 1.0f / 6.0f + (t / 2.0f + (-(0.5f * (t * (t * t))) + 0.5f * (t * t)));
        b3 = 1.0f / 6.0f * (t * (t * t));
    } else if (type == 4) {
        b0 = 1.0f / 6.0f * ((1.0f - t) * ((1.0f - t) * (1.0f - t)));
        b1 = 1.0f / 6.0f + (-0.5f * ((1.0f - t) * ((1.0f - t) * (1.0f - t))) + 0.5f * ((1.0f - t) * (1.0f - t)) + 0.5f * (1.0f - t));
        b2 = 7.0f / 12.0f + (7.0f / 12.0f * ((1.0f - t) * ((1.0f - t) * (1.0f - t))) - 1.25f * ((1.0f - t) * (1.0f - t)) + 0.25f * (1.0f - t));
        b3 = 0.25f * (t * (t * t));
    } else if (type == 5) {
        b0 = 1.0f / 6.0f * ((1.0f - t) * ((1.0f - t) * (1.0f - t)));
        b1 = -11.0f / 12.0f * ((1.0f - t) * ((1.0f - t) * (1.0f - t))) + 1.5f * ((1.0f - t) * (1.0f - t));
        b2 = 1.75f * ((1.0f - t) * ((1.0f - t) * (1.0f - t))) - 4.5f * ((1.0f - t) * (1.0f - t)) + 3.0f * (1.0f - t);
        b3 = (t * (t * t));
    } else if (type == 6) {
        b0 = (1.0f - t) * ((1.0f - t) * (1.0f - t));
        b1 = 3.0f * t * ((1.0f - t) * (1.0f - t));
        b2 = (1.0f - t) * (3.0f * (t * t));
        b3 = t * (t * t);
    }
    r.x = p[0].x * b0 + p[1].x * b1 + p[2].x * b2 + p[3].x * b3;
    r.y = p[0].y * b0 + p[1].y * b1 + p[2].y * b2 + p[3].y * b3;
    r.z = p[0].z * b0 + p[1].z * b1 + p[2].z * b2 + p[3].z * b3;
    return r;
}

/* shape b134:01E00820, 365 insns, 5 copies: draws a ribbon between two point trails: each segment is 4 spline quads
   (module curve function, shape b018:01E00EE0) from the first trail to the second, colours from two
   colours whose alpha fades along the ribbon; the first segment runs on local copies (second trail's
   first point doubled). */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b134_01E00820;

typedef struct {
    Rgbaq_b134_01E00820 c;
    u64 uv;
    u64 xyz;
} Vtx_b134_01E00820;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b134_01E00820 v[4];
    u8 tail[0x20];
} Pkt_b134_01E00820;

typedef struct {
    u8 pad00[0x88];
    void *texture;
    u8 pad8C[8];
    s16 rect[4];
    u8 pad9C[0x22];
    s16 mode;
} Obj_b134_01E00820;

typedef struct {
    u8 r, g, b, a;
} C4_b134_01E00820;

typedef struct {
    u8 pad00[6];
    s16 n;
    u8 pad08[0x20];
    C4_b134_01E00820 col0;
    C4_b134_01E00820 col1;
} Rib_b134_01E00820;

static void func_01E00820_b134(Obj_b134_01E00820 *o, Rib_b134_01E00820 *s, Vec_b018_01E00EE0 *pa, Vec_b018_01E00EE0 *pb) {
    extern Rgbaq_b134_01E00820 func_00107740(void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00108500(void *, void *, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 depth[4];
    Vec_b018_01E00EE0 quad[4];
    Vec_b018_01E00EE0 A[4];
    Vec_b018_01E00EE0 B[4];
    Vec_b018_01E00EE0 a4[4];
    Vec_b018_01E00EE0 b4[4];
    Pkt_b134_01E00820 pkt __attribute__((aligned(8)));
    C4_b134_01E00820 c0;
    C4_b134_01E00820 c1;
    s32 k;
    s32 j;
    s16 n;
    Pkt_b134_01E00820 *p;
    s32 ot;
    Vec_b018_01E00EE0 *pq;
    f32 t;

    ot = (s32)func_00207500();
    n = s->n;
    p = (Pkt_b134_01E00820 *)(s32)&pkt;
    func_00109270(p, 0, 0);
    pkt.v[0].c = func_00107740(&s->col0);
    pkt.v[1].c = func_00107740(&s->col1);
    pkt.v[2].c = func_00107740(&s->col0);
    pkt.v[3].c = func_00107740(&s->col1);
    func_00108500(p, o->rect, o->mode);
    func_00208700(p, o->texture, 1);
    c0 = s->col0;
    c1 = s->col1;
    a4[0] = pa[0];
    a4[1] = pa[1];
    a4[2] = pa[2];
    a4[3] = pa[3];
    b4[0] = pb[0];
    b4[1] = pb[0];
    b4[2] = pb[1];
    b4[3] = pb[2];
    for (k = 0; k < n - 2; k++) {
        p->v[0].c = func_00107740(&c0);
        p->v[1].c = func_00107740(&c1);
        c0.a -= (u8)(s->col0.a / (n - 1));
        c1.a -= (u8)(s->col1.a / (n - 1));
        p->v[2].c = func_00107740(&c0);
        p->v[3].c = func_00107740(&c1);
        t = 0.0f;
        pq = pb + (k - 1);
        for (j = 0; j < 4; j++) {
            if (k != 0) {
                A[0] = func_01E003E0_b134(pa, 0, t);
                B[0] = func_01E003E0_b134(pq, 0, t);
                t += 0.25f;
                A[1] = func_01E003E0_b134(pa, 0, t);
                B[1] = func_01E003E0_b134(pq, 0, t);
            } else {
                A[0] = func_01E003E0_b134(a4, 0, t);
                B[0] = func_01E003E0_b134(b4, 0, t);
                t += 0.25f;
                A[1] = func_01E003E0_b134(a4, 0, t);
                B[1] = func_01E003E0_b134(b4, 0, t);
            }
            quad[0].x = A[0].x;
            quad[0].y = A[0].y;
            quad[0].z = A[0].z;
            quad[1].x = A[1].x;
            quad[1].y = A[1].y;
            quad[1].z = A[1].z;
            quad[2].x = B[0].x;
            quad[2].y = B[0].y;
            quad[2].z = B[0].z;
            quad[3].x = B[1].x;
            quad[3].y = B[1].y;
            quad[3].z = B[1].z;
            if (func_00205630(quad, 0x70000000, NULL, p, depth) != 0) {
                func_002075F0(p, ot, 0);
            }
        }
        pa++;
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b134", func_01E00DE0_b134);

INCLUDE_ASM("asm/nonmatchings/mod/b134", func_01E011E0_b134);

INCLUDE_ASM("asm/nonmatchings/mod/b134", func_01E016D0_b134);

/* shape b080:01E02140, 55 insns: colour (0xFF,0xF0,0xFF); on start f38 50, random direction, f34 0, f30 random
   -15..14; alpha grows by 0x26 (below 0xC0) for 5 ticks; resets f0/f2/f4 to (0, 20, 0) every tick */

typedef struct {
    s16 f0, f2, f4;
    s16 life;
    u8 pad8[0x20];
    u8 col[4];
    u8 col2[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 dir;
} Glow_b080_01E02140;

static s32 func_01E01B90_b134(s32 arg0, Glow_b080_01E02140 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    func_001076F0(o->col, 0xFF, 0xF0, 0xFF);
    if (o->mode == 1) {
        o->f38 = 50;
        o->dir = func_0019A5C8() % 360;
        o->f34 = 0;
        o->f30 = func_0019A5C8() % 30 - 15;
        o->mode = 2;
    }
    if (o->tick < 5) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x26;
        }
    }
    o->tick++;
    o->f0 = 0;
    o->f2 = 20;
    o->f4 = 0;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b134", func_01E01C70_b134);

INCLUDE_ASM("asm/nonmatchings/mod/b134", func_01E01E20_b134);

/* shape b134:01E01FB0, 52 insns: a white/red two-colour glow of size 130 at a random angle: alpha 0x80 on its first tick, then out by 15 and ends */

typedef struct {
    u8 pad0[6];
    s16 h6;
    u8 pad8[0x10];
    s32 w18;
    u8 pad1C[0xC];
    u8 col[4];
    u8 col2[4];
    s16 h30;
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f38;
    s16 ang;
} Glow_b134_01E01FB0;

static s32 func_01E01FB0_b134(s32 arg0, Glow_b134_01E01FB0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 0x82;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        func_001076F0(o->col2, 0x80, 0x10, 0x10);
        o->ang = func_0019A5C8() % 360;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 1) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 15;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b134:01E02080, 45 insns: red flash (0x80, 0x20, 0x20): on start 0x38 = 13 and a hold of 8 ticks (0xE);
   alpha 0x80 during the hold, then fades by 0x1D and stops; 0x6 = 9 each tick */

typedef struct {
    u8 pad0[6];
    s16 f6;
    u8 pad8[6];
    s16 hold;
    u8 pad10[0x18];
    u8 col[4];
    u8 pad2C[6];
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f38;
} Fx_b134_01E02080;

static s32 func_01E02080_b134(s32 arg0, Fx_b134_01E02080 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    func_001076F0(o->col, 0x80, 0x20, 0x20);
    if (o->mode == 1) {
        o->f38 = 13;
        o->hold = 8;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0x1E) {
        o->col[3] -= 0x1D;
    } else {
        o->mode = 0;
    }
    o->f6 = 9;
    o->tick++;
    return 0;
}

/* shape b134:01E02140, 43 insns: constant variant of b018:01E02AC0 (glow): on start colour (0x60, 0x60, 0x60) and fields;
   alpha 0x80 for the first 0xD ticks, then fade out by 29 and stop */

typedef struct {
    u8 pad0[6];
    s16 life;
    u8 pad8[0x20];
    u8 col[4];
    u8 pad2C[6];
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f38;
} Glow_b134_01E02140;

static s32 func_01E02140_b134(s32 arg0, Glow_b134_01E02140 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        func_001076F0(o->col, 0x60, 0x60, 0x60);
        o->life = 7;
        o->col[3] = 0x80;
        o->f38 = 6;
        o->mode = 2;
    }
    if (o->tick < 0xD) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0x1E) {
        o->col[3] -= 29;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b134", func_01E021F0_b134);

typedef struct {
    u8 pad00[6];
    s16 limit;
    s16 h8;
    u8 pad0A[4];
    s16 speed;
    u8 pad10[8];
    s32 seed;
    u8 pad1C[0xC];
    u8 col[3];
    u8 alpha;
    u8 pad2C[4];
    s16 pos;
    s16 age;
    s16 kind;
    s16 state;
    s16 mode;
    s16 angle;
} Spark_b018_01E02950;

static s32 func_01E02300_b134(s32 unused, Spark_b018_01E02950 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->mode = 2;
        o->kind = func_0019A5C8() % 4;
        func_001076F0(o->col, 0x80, 0x40, 0);
        o->seed = func_0019A5C8() % 0xFFFF;
        o->pos = 0;
        o->angle = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 16 + 3;
        o->h8 = func_0019A5C8() % 10;
        o->limit = func_0019A5C8() % 3 + 1;
        o->state = 2;
    }
    if (o->age < o->limit) {
        o->alpha = 0x80;
    } else if (o->alpha > 16) {
        o->alpha -= 10;
    } else {
        o->state = 0;
    }
    o->pos += o->speed;
    o->age++;
    return 0;
}

/* shape b080:01E02C10, 23 insns: a glow start: on mode 1 set f38 = 0x14, colour (0x10,0x10,0x10), alpha 0x20, mode 2 */

typedef struct {
    u8 pad0[0x28];
    u8 col[4];
    u8 pad2C[0xA];
    s16 mode;
    s16 f38;
} Glow_b080_01E02C10;

static s32 func_01E02470_b134(s32 arg0, Glow_b080_01E02C10 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 0x14;
        func_001076F0(o->col, 0x10, 0x10, 0x10);
        o->col[3] = 0x20;
        o->mode = 2;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b134", func_01E024D0_b134);

/* shape b134:01E02690, 47 insns: constant variant of b205:01E01E50 (volume fade by game state): state at 0x2FC0 limit 0x1F,
   floor 0x30, down 10, up 10, cap 0x80 */

typedef struct {
    u8 pad[0x2FC0];
    s32 state;
} Game_b134_01E02690;

typedef struct {
    u8 pad[0x30];
    s16 vol;
    u8 pad32[4];
    s16 mode;
} Fade_b134_01E02690;

static s32 func_01E02690_b134(Game_b134_01E02690 *g, Fade_b134_01E02690 *o) {
    extern void func_001F6D00(s32);

    if (o->mode == 1) {
        o->vol = 0x80;
        o->mode = 2;
    }
    if (g->state > 0x1E) {
        if (o->vol > 0x30) {
            o->vol -= 10;
        } else {
            o->vol = 0x30;
        }
    } else {
        if (o->vol < 0x80) {
            o->vol += 10;
        } else {
            o->vol = 0x80;
        }
    }
    if (g->state == 1) {
        func_001F6D00((u8)o->vol);
    } else {
        func_001F6D00((u8)o->vol);
    }
    return 0;
}

/* shape b134:01E02750, 38 insns: func_001F7170(10, 0, &a, &b, 0) with copies of the module's floats at 0x01E03F80 and
   0x01E03F88; mode 1 becomes 2; the effect stops once its tick (0x32) reaches 0x50; return 0 */

typedef struct {
    f32 v;
} F_b134_01E02750;

typedef struct {
    u8 pad0[0x32];
    s16 tick;
    u8 pad34[2];
    s16 mode;
} Fx_b134_01E02750;

extern F_b134_01E02750 D_01E03F80_b134;
extern F_b134_01E02750 D_01E03F88_b134;

static s32 func_01E02750_b134(s32 arg0, Fx_b134_01E02750 *o) {
    extern void func_001F7170(s32, s32, void *, void *, s32);
    F_b134_01E02750 a;
    F_b134_01E02750 b;

    a = D_01E03F80_b134;
    b = D_01E03F88_b134;
    if (o->mode == 1) {
        o->mode = 2;
    }
    func_001F7170(10, 0, &a, &b, 0);
    if (o->tick >= 0x50) {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b134", func_01E027F0_b134);

/* shape b134:01E02960, 40 insns: b734:01E03310 family: textures group 4 cells 0-2 and 11-15, group 5 cell 0 */

typedef struct {
    u8 pad0[0x340];
    s32 tex[16];
    u8 pad380[0x2c20];
    s32 tex5[3];
} Scene_b134_01E02960;

static void func_01E02960_b134(s32 arg0, Scene_b134_01E02960 *o) {
    s32 i;

    for (i = 0; i < 3; i++) {
        o->tex[i] = func_00202BF0(4, i);
    }
    for (i = 11; i < 16; i++) {
        o->tex[i] = func_00202BF0(4, i);
    }
    for (i = 0; i < 1; i++) {
        o->tex5[i] = func_00202BF0(5, i);
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b134", func_01E02A00_b134);

/* shape b134:01E03760, 72 insns: twin of b046:01E03E20: take the first free slot of the 150-slot pool, clear it, give
   it the scene's colour twice, the scene matrix, the scene's value 0x3022 and the two arguments; returns 1 if a
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
} Slot_b134_01E03760;

typedef struct {
    u8 pad[0x2D0];
    u8 m[0xB0];
    Slot_b134_01E03760 s[150];
    u8 pad2900[0x6C4];
    u8 r, g, b, a;
    u8 pad2FC8[0x5A];
    s16 v;
} Pool_b134_01E03760;

static s32 func_01E03760_b134(Pool_b134_01E03760 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b134_01E03760 *s = NULL;
    s16 i;
    s32 ret;

    for (i = 0; i < 150; i++) {
        if (o->s[i].used == 0) {
            func_00195108(&o->s[i], 0x40);
            o->s[i].used = 1;
            s = &o->s[i];
            i = 150;
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

INCLUDE_ASM("asm/nonmatchings/mod/b134", func_01E03880_b134);

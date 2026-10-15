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

static void func_01E00080_b484(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E00920_b484(u8 *self, Obj_b018_01E00C50 *obj, void *pk) {
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

/* shape b046:01E00BB0, 133 insns, 4 copies: draws one camera-facing sprite at a position plus a tenth of an offset,
   blend by mode (0 normal, 1, other), texture corners by the module helper (shape b003:01E00080). */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b046_01E00BB0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Rgbaq_b046_01E00BB0 c;
    struct {
        u64 tc;
        u64 xyz;
    } v[4];
    u8 tail[0x38];
} Pkt_b046_01E00BB0;

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    Rect_b003_01E00080 rect;
    u8 pad9C[0x22];
    s16 mode;
} Obj_b046_01E00BB0;

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 dx, dy, dz;
    u8 padE[0x1A];
    u8 col[4];
    u8 pad2C[0xC];
    s16 size;
} Spr_b046_01E00BB0;

static void func_01E00BB0_b484(Obj_b046_01E00BB0 *o, Spr_b046_01E00BB0 *s, s32 blend) {
    extern Rgbaq_b046_01E00BB0 func_00107740(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f pos;
    Vec4f scale;
    f32 depth[4];
    f32 m[16];
    s32 rot[4];
    Pkt_b046_01E00BB0 pkt __attribute__((aligned(8)));
    Pkt_b046_01E00BB0 *p;
    f32 dx;
    f32 dy;
    f32 dz;

    p = (Pkt_b046_01E00BB0 *)(s32)&pkt;
    p->count = 0x24;
    p->tag = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad = 0;
    p->count |= 0x800;
    if (blend == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x48);
    } else if (blend == 1) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x44);
    } else {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    }
    p->c = func_00107740(s->col);
    func_01E00080_b484((Pk_b003_01E00080 *)p, &o->rect, o->mode);
    func_00208700(p, o->texture, 1);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    dx = s->dx;
    dy = s->dy;
    dz = s->dz;
    dx /= 10.0f;
    dy /= 10.0f;
    dz /= 10.0f;
    pos.x = s->x + dx;
    pos.y = s->y + dy;
    pos.z = s->z + dz;
    func_00108EF0(m, &scale, rot, &pos);
    func_00108CE0(quad, s->size, s->size);
    if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
        func_002075F0(p, o->ot, (u32)depth[0]);
    }
}

/* shape b046:01E01A60, 283 insns, 10 copies: draws obj->count (0 = 20) sprites along a curve read from three s8
   tables (0x64 apart), each turned on three axes by the definition's angles; mode 0 = depth from the
   projection, 1 = far z, 2 = -1. Calls the module's sprite-UV helper (shape b003:01E00080) as a static
   function. Sibling of b003:01E00EA0 and b018:01E005A0. */

typedef struct {
    u8 pad0[0x20];
    Vec4f pos;
    u8 pad30[0x50];
    s32 f80;
    u8 pad84[4];
    void *f88;
    u8 pad8C[8];
    u8 f94[0x24];
    s16 count;
    u8 padBA[4];
    s16 fBE;
    u8 padC0[0x18];
    u8 fD8[4];
} Obj_b046_01E01A60;

typedef struct {
    u8 pad0[8];
    s16 tab;
    u8 padA[6];
    s32 rot[4];
    u8 pad20[8];
    u8 tex[8];
    s16 scale;
    u8 pad32[6];
    s16 size;
} Def_b046_01E01A60;

typedef struct {
    union {
        struct {
            u64 x : 16;
            u64 y : 16;
            u64 z : 24;
            u64 fog : 8;
        } b;
        struct {
            u8 pad[7];
            u8 fog;
        } h;
    } xyz;
    u64 reg;
} Xyz_b046_01E01A60;

typedef struct {
    f32 u, v;
} Uv_b046_01E01A60;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b046_01E01A60 uv;
    u64 pad18;
    Xyz_b046_01E01A60 v[4];
    u64 pad60[6];
} Pk_b046_01E01A60;

typedef struct {
    u64 tag;
    Pk_b046_01E01A60 pk;
} Buf_b046_01E01A60;

static void func_01E00DD0_b484(Obj_b046_01E01A60 *obj, Def_b046_01E01A60 *def, s32 mode, s8 *base) {
    f32 m2[4][4];
    Vec4f pos;
    Vec4f s;
    f32 out[4];
    f32 m[4][4];
    s32 rot[4];
    Buf_b046_01E01A60 buf;
    Uv_b046_01E01A60 uv;
    s16 i;
    Pk_b046_01E01A60 *p;
    s16 n;
    s32 h;
    s8 *t;
    f32 f;
    f32 r;
    extern void func_00108EF0();
    extern void func_00109100();

    func_00207500();
    p = &buf.pk;
    p->flags = 0x24;
    p->size = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad4 = 0;
    p->flags |= 0x800;
    func_002086D0(p, ((u64)0x80 << 32) | 0x48);
    buf.pk.uv.v = 0.0f;
    buf.pk.v[0].xyz.h.fog = 0;
    buf.pk.v[1].xyz.h.fog = 0;
    buf.pk.v[2].xyz.h.fog = 0;
    buf.pk.v[3].xyz.h.fog = 0;
    func_00107740(&uv, def->tex);
    buf.pk.uv = uv;
    func_01E00080_b484((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
    func_00208700(p, obj->f88, 1);
    n = (obj->count != 0) ? obj->count : (s16)20;
    s.x = 0.1f;
    s.y = 0.1f;
    s.z = 0.1f;
    func_00205C40((s32)rot);
    pos.x = obj->pos.x;
    pos.y = obj->pos.y;
    pos.z = obj->pos.z;
    func_00108EF0(m, &s, rot, &pos);
    for (i = 0; i < n; i++) {
        r = def->size;
        func_00108CE0(m2, r, r);
        t = base + i;
        h = i >> 1;
        f = t[def->tab];
        f /= 20.0f;
        func_00107070(m2, 0, f * (def->scale + h));
        f = t[def->tab + 100];
        f /= 20.0f;
        func_00107070(m2, 1, f * (def->scale + h));
        f = t[def->tab + 180];
        f /= 20.0f;
        func_00107070(m2, 2, f * (def->scale + h));
        func_00109100(m2, def->rot, 0, obj->fD8);
        func_00109100(m2, def->rot, 1, obj->fD8);
        func_00109100(m2, def->rot, 2, obj->fD8);
        if (mode == 0) {
            if (func_00205630((s32)m2, 0x70000000, (s32)m, (s32)p, out) != 0) {
                func_002075F0((s32)p, obj->f80, func_001A23B0(out[0]));
            }
        } else if (mode == 1) {
            if (func_00205630((s32)m2, 0x70000000, (s32)m, (s32)p, out) != 0) {
                p->v[0].xyz.b.z = p->v[1].xyz.b.z = p->v[2].xyz.b.z = p->v[3].xyz.b.z = 0xFFFFFF;
                func_002075F0((s32)p, obj->f80, 0);
            }
        } else if (mode == 2) {
            if (func_00205630((s32)m2, 0x70000000, (s32)m, (s32)p, out) != 0) {
                func_002075F0((s32)p, obj->f80, -1);
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b484", func_01E01240_b484);

/* shape b484:01E016C0, 90 insns: a purple rising spark (b709:01E035F0 family): frame 17, random sub-frame 0..3, y turn
   and angle, rise 30..79, height 0..9, hold 5..14; then fades by 15 until it ends; rises every frame */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 h8;
    u8 padA[4];
    s16 step;
    u8 pad10[4];
    s32 rot1;
    s32 rot2;
    u8 pad1C[0xC];
    u8 c0[4];
    u8 pad2C[4];
    s16 y;
    s16 t;
    s16 sub;
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b484_01E016C0;

static s32 func_01E016C0_b484(void *arg0, Obj_b484_01E016C0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 0x11;
        o->sub = func_0019A5C8() % 4;
        func_001076F0(o->c0, 0x80, 0x40, 0x80);
        o->rot2 = 0;
        o->rot1 = func_0019A5C8() % 360;
        o->y = 0;
        o->ang = func_0019A5C8() % 360;
        o->step = func_0019A5C8() % 50 + 0x1E;
        o->h8 = func_0019A5C8() % 10;
        o->hold = func_0019A5C8() % 10 + 5;
        o->state = 2;
    }
    if (o->t < o->hold) {
        o->c0[3] = 0x80;
    } else if (o->c0[3] > 0x10) {
        o->c0[3] -= 0xF;
    } else {
        o->state = 0;
    }
    o->y += o->step;
    o->t++;
    return 0;
}

/* func_001076F0 takes plain ints here (functions.h says s8): hide that prototype */

/* OVL_WARM */

/* shape b484:01E01830, 117 insns: mote with a small random offset drifting 30 units a frame along a random angle */

typedef struct Mo_b484_01E01830 {
    u8 pad0[8];
    s16 x, y, z;
    u8 padE[0x1A];
    u8 c28[4];
    u8 c2C[4];
    s16 h30;
    s16 age;
    s16 h34;
    s16 state;
    s16 h38;
    s16 ang;
} Mo_b484_01E01830;

typedef struct Scn_b484_01E01830 {
    u8 pad0[0x3A5C];
    u8 table[0x10];
} Scn_b484_01E01830;

static s32 func_01E01830_b484(Scn_b484_01E01830 *w, Mo_b484_01E01830 *o) {
    extern s32 func_001076F0();
    if (o->state == 1) {
        o->h38 = 100;
        func_001076F0(o->c28, 0x80, 0x80, 0x80);
        o->h30 = func_0019A5C8() % 360;
        o->ang = func_0019A5C8() % 360;
        o->x = func_0019A5C8() % 4 - 2;
        o->y = func_0019A5C8() % 4 - 2;
        o->z = func_0019A5C8() % 4 - 2;
        o->state = 2;
    }
    if (o->age < 7) {
        o->c28[3] = 0x80;
    } else if (o->c28[3] > 0x10) {
        o->c28[3] -= 0xF;
    } else {
        o->state = 0;
    }
    o->h34 = func_0019A5C8() % 8;
    o->x = (s32)(o->x + 30.0f * func_00108030((s32)w->table, o->ang, 0));
    o->z = (s32)(o->z + 30.0f * func_00108030((s32)w->table, o->ang, 1));
    o->age++;
    return 0;
}

/* shape b484:01E01A10, 141 insns: b064:01E01C00 family: a grey or purple spark thrown 40 along a random direction (4 along its tilt), random frame each tick (sine table at g+0x3A5C) */

typedef struct {
    u8 pad0[8];
    s16 f8;
    s16 fA;
    s16 fC;
    u8 padE[0x1A];
    u8 col[4];
    u8 pad2C[4];
    s16 angle;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
    s16 dir;
} Spark_b484_01E01A10;

static s32 func_01E01A10_b484(u8 *g, Spark_b484_01E01A10 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    if (o->mode == 1) {
        o->f38 = 200;
        if (o->angle == 0) {
            func_001076F0(o->col, 0xF0, 0xF0, 0xF0);
        } else {
            func_001076F0(o->col, 0x80, 0x10, 0xF0);
        }
        o->angle = func_0019A5C8() % 360;
        o->dir = func_0019A5C8() % 360;
        o->f8 = func_0019A5C8() % 4 - 2;
        o->fA = func_0019A5C8() % 4 - 2;
        o->fC = func_0019A5C8() % 4 - 2;
        o->mode = 2;
    }
    if (o->tick < 7) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 15;
    } else {
        o->mode = 0;
    }
    o->kind = func_0019A5C8() % 8;
    o->f8 = o->f8 + 40.0f * func_00108030(g + 0x3A5C, o->dir, 0);
    o->fC = o->fC + 4.0f * func_00108030(g + 0x3A5C, o->angle, 1);
    o->fA = o->fA + 40.0f * func_00108030(g + 0x3A5C, o->dir, 1);
    o->tick++;
    return 0;
}

/* shape b484:01E01C50, 86 insns: on start 0x38 = 200, colour (0x80, 0x10, 0xF0), random 0x30 and 0x3A, drift
   -2..1 on 0x8/0xA/0xC; alpha 0x80 for 7 ticks, then fades by 15 and stops; 0x34 is rerolled 0..7 each tick */

typedef struct {
    u8 pad0[8];
    s16 f8;
    s16 fA;
    s16 fC;
    u8 padE[0x1A];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b484_01E01C50;

static s32 func_01E01C50_b484(s32 arg0, Fx_b484_01E01C50 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 200;
        func_001076F0(o->col, 0x80, 0x10, 0xF0);
        o->f30 = func_0019A5C8() % 360;
        o->f3A = func_0019A5C8() % 360;
        o->f8 = func_0019A5C8() % 4 - 2;
        o->fA = func_0019A5C8() % 4 - 2;
        o->fC = func_0019A5C8() % 4 - 2;
        o->mode = 2;
    }
    if (o->tick < 7) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 15;
    } else {
        o->mode = 0;
    }
    o->f34 = func_0019A5C8() % 8;
    o->tick++;
    return 0;
}

/* shape b484:01E01DB0, 56 insns: a red/white two-colour glow of size 430 at a random angle: alpha 0x80 for 5 ticks, then out by 10 and ends; grows 20 a tick */

typedef struct {
    u8 pad0[2];
    s16 h2;
    u8 pad4[2];
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
    u8 padE[0x1A];
    u8 col[4];
    u8 col2[4];
    s16 h30;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
    s16 ang;
} Glow_b484_01E01DB0;

static s32 func_01E01DB0_b484(s32 arg0, Glow_b484_01E01DB0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 0x1AE;
        func_001076F0(o->col, 0x80, 0x10, 0xF0);
        func_001076F0(o->col2, 0x80, 0x80, 0x80);
        o->ang = func_0019A5C8() % 360;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 5) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    o->tick++;
    o->f38 += 20;
    return 0;
}

/* shape b484:01E01E90, 93 insns: a scene light pulse (b443:01E03E80 shape): sets the scene light (range 140, at the object's point),
   raises its strength by 0.2f to 1, then lowers it by 0.1f until it ends; applies the light while live and ends when the
   scene state at 0x3610 is 1 */

typedef struct {
    u8 pad0[0x34F0];
    f32 l0[4];
    f32 pos[3];
    u8 pad350C[4];
    f32 f20;
    f32 range;
    f32 power;
    u8 pad351C[0xF4];
    s32 state;
} Scene_b484_01E01E90;

typedef struct {
    s16 x, y, z;
    u8 pad6[0x2A];
    s16 down;
    u8 pad32[4];
    s16 live;
} Obj_b484_01E01E90;

static s32 func_01E01E90_b484(Scene_b484_01E01E90 *g, Obj_b484_01E01E90 *o) {
    extern void func_001F6C10(void *);

    if (o->live == 1) {
        g->l0[0] = 128.0f;
        g->l0[1] = 2.0f;
        g->l0[2] = 0.0f;
        g->l0[3] = 4.0f;
        g->f20 = 0.0f;
        g->range = 140.0f;
        g->power = 0.0f;
        g->pos[0] = o->x;
        g->pos[1] = o->y;
        g->pos[2] = o->z;
        o->live = 2;
        o->down = 0;
    }
    if (o->down == 0) {
        if (g->power < 1.0f) {
            g->power += 0.2f;
        } else {
            o->down = 1;
        }
    } else if (!(g->power <= 0.1f)) {
        g->power -= 0.1f;
    } else {
        o->live = 0;
    }
    if (o->live == 0) {
        func_001F6C10(NULL);
    } else {
        func_001F6C10(g->l0);
    }
    if (g->state == 1) {
        o->live = 0;
    }
    return 0;
}

/* shape b270:01E04340, 47 insns, 1 copy: fade a level toward 0x40 or 0x80 by the scene timer */

typedef struct Ctx_b046_01E030F0 {
    u8 pad[0x3610];
    s32 timer;
} Ctx_b046_01E030F0;

typedef struct Obj_b046_01E030F0 {
    u8 pad0[0x30];
    s16 level;
    u8 pad32[4];
    s16 state;
} Obj_b046_01E030F0;

static s32 func_01E02010_b484(Ctx_b046_01E030F0 *ctx, Obj_b046_01E030F0 *o) {
    if (o->state == 1) {
        o->level = 0x80;
        o->state = 2;
    }
    if (ctx->timer > 0x1E) {
        if (o->level > 0x30) {
            o->level -= 10;
        } else {
            o->level = 0x30;
        }
    } else {
        if (o->level < 0x80) {
            o->level += 10;
        } else {
            o->level = 0x80;
        }
    }
    if (ctx->timer == 1) {
        func_001F6D00((u8)o->level);
    } else {
        func_001F6D00((u8)o->level);
    }
    return 0;
}

static s32 func_01E020D0_b484(void) {
    f32 a;
    f32 b;

    *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E02C80_b484;
    *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E02C88_b484;
    func_001F7170(2, 0, (s32)&a, (s32)&b, 0);
    return 0;
}

/* shape b417:01E04700, 41 insns: look up the textures: group 4 cells 0-2 and 13-15, group 5 cells 0-1 */

typedef struct {
    u8 pad0[0x2B0];
    s32 tex[16];
    u8 pad2F0[0x3300];
    s32 tex5[2];
} Scene_b417_01E04700;

static void func_01E02120_b484(s32 arg0, Scene_b417_01E04700 *o) {
    s32 i;

    for (i = 0; i < 3; i++) {
        o->tex[i] = func_00202BF0(4, i);
    }
    for (i = 13; i < 16; i++) {
        o->tex[i] = func_00202BF0(4, i);
    }
    for (i = 0; i < 2; i++) {
        o->tex5[i] = func_00202BF0(5, i);
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b484", func_01E021D0_b484);

/* shape b046:01E03E20, 72 insns: take the first free slot of the 200-slot pool, clear it, give it the scene's
   colour twice, the scene matrix, the scene's value 0x3656 and the two arguments; returns 1 if a slot was found */

typedef struct {
    u8 pad[0x20];
    s32 b;
    s32 a;
    u8 c0[4];
    u8 c1[4];
    s16 v;
    u8 pad32[4];
    s16 used;
    u8 pad38[8];
} Slot_b046_01E03E20;

typedef struct {
    u8 pad[0x250];
    u8 m[0xA0];
    Slot_b046_01E03E20 s[200];
    u8 pad34F0[0x124];
    u8 r, g, b, a;
    u8 pad3618[0x3E];
    s16 v;
} Pool_b046_01E03E20;

static s32 func_01E02B50_b484(Pool_b046_01E03E20 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b046_01E03E20 *s = NULL;
    s16 i;
    s32 ret;

    for (i = 0; i < 200; i++) {
        if (o->s[i].used == 0) {
            func_00195108(&o->s[i], 0x40);
            o->s[i].used = 1;
            s = &o->s[i];
            i = 200;
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

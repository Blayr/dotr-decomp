#include "common.h"

/* shape b034:01E00080, 33 insns, 52 copies: shift a position history down by one, the newest from src */

static s32 func_01E00080_c063(Vec4f *dst, s32 n, s32 arg2, Vec4f *src) {
    s16 i;
    s32 k = n - 1;
    Vec4f *prev = dst;

    prev--;
    for (i = 0; i < n; i++, dst--, prev--, k--) {
        if (k != 0) {
            dst->x = prev->x;
            dst->y = prev->y;
            dst->z = prev->z;
        } else {
            dst->x = src->x;
            dst->y = src->y;
            dst->z = src->z;
        }
    }
    return 0;
}

/* shape b034:01E00110, 276 insns, 11 copies: texture coordinates of a sprite quad from a rectangle, 4 explicit
   modes (corner orders differ from b008:01E00080's). Module-internal: callers include it with OVL_LOCAL static. */

typedef struct Rect_b034_01E00110 {
    s16 x, y, w, h;
} Rect_b034_01E00110;

typedef struct Uv_b034_01E00110 {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad4;
    u64 xyz;
} Uv_b034_01E00110;

typedef struct Pk_b034_01E00110 {
    u8 pad0[0x18];
    Uv_b034_01E00110 c[4];
} Pk_b034_01E00110;

static void func_01E00110_c063(Pk_b034_01E00110 *p, Rect_b034_01E00110 *r, s32 mode) {
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

extern void c063_01E00110(Pkt_b038_01E00920 *, void *, s32);

static void func_01E00560_c063(Obj_b038_01E00920 *o, Anim_b038_01E00920 *an, s32 mode, Tbl_b038_01E00920 *tbl) {
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
    c063_01E00110(p, o->b94, o->hC0);
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

INCLUDE_ASM("asm/nonmatchings/mod/c063", func_01E00AD0_c063);

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

/* shape b016:01E00ED0, 175 insns, 99 copies: draw one sprite quad (GS packet of 9 qwords) at an object's
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00110_c063 in the
   same file and static (the original reuses $a0 across the call). The colour is passed by value. */

typedef struct Cam_b016_01E00ED0 {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[0x14];
    Vec4f pos;
    u8 pad30[0x30];
    Vec4f at;
} Cam_b016_01E00ED0;

typedef struct Obj_b016_01E00ED0 {
    u8 pad0[0x80];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    u8 f94[0x2A];
    s16 fBE;
} Obj_b016_01E00ED0;

typedef struct Xyz_b016_01E00ED0 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b016_01E00ED0;

typedef struct Uv_b016_01E00ED0 {
    f32 u, v;
} Uv_b016_01E00ED0;

typedef struct Pk_b016_01E00ED0 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b016_01E00ED0 uv;
    u64 pad18;
    Xyz_b016_01E00ED0 v[4];
    u64 pad60[6];
} Pk_b016_01E00ED0;

typedef struct Buf_b016_01E00ED0 {
    u64 tag;
    Pk_b016_01E00ED0 pk;
} Buf_b016_01E00ED0;

static void func_01E00E10_c063(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
    extern void func_00108EF0();
    f32 view[4][4];
    Vec4f a;
    Vec4f s;
    f32 out[4];
    f32 m[4][4];
    Buf_b016_01E00ED0 buf;
    Uv_b016_01E00ED0 uv;
    s32 sel;
    s32 mode;
    Pk_b016_01E00ED0 *p = &buf.pk;

    sel = (flags >> 4) & 0xF;
    p->flags = 0x24;
    p->size = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad4 = 0;
    p->flags |= 0x800;
    if (sel == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((s64)sel << 2) | (((u64)0x80 << 32) | 0x40));
    }
    func_00107740(&uv, &cam->at);
    p->uv = uv;
    func_01E00110_c063((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
    func_00208700(p, (void *)obj->f88, 1);
    s.x = 0.1f;
    a.x = c.x;
    s.y = 0.1f;
    a.y = c.y;
    s.z = 0.1f;
    a.z = c.z;
    func_00108EF0(m, &s, &cam->pos, &a);
    func_00108CE0(view, cam->w, cam->h);
    if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, out) != 0) {
        mode = flags & 0xF;
        if (mode == 0) {
            func_002075F0((s32)p, obj->f80, func_001A23B0(out[0]));
        } else if (mode == 1) {
            p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
            func_002075F0((s32)p, obj->f80, 0);
        } else {
            func_002075F0((s32)p, obj->f80, -1);
        }
    }
}

/* shape b034:01E00E60, 115 insns, 33 copies: builds a 4-vertex sprite packet from the object's two
   texture refs, sets the blend mode from arg2 >> 4 and, when arg2 & 0xF is 0, puts every vertex at the
   far depth; then sends it with the given (or no) level. */

typedef struct {
    u64 rgbaq;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b034_01E00E60;

typedef struct {
    u64 tag[2];
    Vtx_b034_01E00E60 v[4];
    u8 rest[0x40];
} Pk_b034_01E00E60;

static void func_01E010D0_c063(s32 arg0, u8 *obj, s32 mode, f32 level) {
    Pk_b034_01E00E60 pk;
    u8 *dst;
    Pk_b034_01E00E60 *p;
    s16 blend;

    dst = func_00207500();
    p = (Pk_b034_01E00E60 *)(u32)&pk;
    func_00107990(p, obj + 0x60, 1);
    func_00107990(p, obj + 0x64, 2);
    func_001092E0(p, 0);
    func_001094F0(p);
    blend = mode >> 4;
    if (blend == 0) {
        func_002086D0(p, 0x42 | ((s64)0x80 << 32));
    } else {
        func_002086D0(p, ((s64)blend << 2) | (0x40 | ((s64)0x80 << 32)));
    }
    if ((mode & 0xF) == 0) {
        p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
        func_002075F0((s32)p, (s32)dst, 0);
    } else {
        func_002075F0((s32)p, (s32)dst, func_001A23B0(level));
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/c063", func_01E012A0_c063);

INCLUDE_ASM("asm/nonmatchings/mod/c063", func_01E01690_c063);

INCLUDE_ASM("asm/nonmatchings/mod/c063", func_01E02340_c063);

INCLUDE_ASM("asm/nonmatchings/mod/c063", func_01E02640_c063);

INCLUDE_ASM("asm/nonmatchings/mod/c063", func_01E029C0_c063);

/* shape c063:01E02D00, 61 insns: a white spinning flash (b236:01E01B70 family): scale 300, frame count 0x109, size 10x10;
   alpha up by 13 to 0xA0 for that many frames, then down by 12 until it ends; a random turn plus a quarter each frame */

typedef struct {
    u8 pad0[6];
    s16 hold;
    u8 pad8[0x18];
    s32 rot[4];
    u8 pad30[0x18];
    f32 scale;
    u8 pad4C[8];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 w;
    s16 h;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_c063_01E02D00;

static s32 func_01E02D00_c063(void *arg0, Obj_c063_01E02D00 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->scale = 300.0f;
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->c1, 0xFF, 0xFF, 0xFF);
        o->hold = 0x109;
        o->w = 0xA;
        o->h = 0xA;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < o->hold) {
        if (o->c0[3] < 0xA0) {
            o->c0[3] += 0xD;
        }
    } else if (o->c0[3] > 0xD) {
        o->c0[3] -= 0xC;
    } else {
        o->state = 0;
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->t++;
    return 0;
}

/* shape c063:01E02E00, 78 insns: on start 0x8/0xA = 0x12C, random flip 0x56, both colours 0x80 grey (second alpha 0);
   both alphas grow by 0x13 (below 0xC0) for 0x108 ticks, then fade by 14 (the first ends it); 0x56 toggles each tick;
   func_00205C40 on the rotation at 0x20 */

typedef struct {
    u8 pad0[8];
    s16 f8;
    s16 fA;
    u8 padC[0x14];
    s32 rot[4];
    u8 pad30[0x24];
    s16 tick;
    s16 flip;
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
    u8 col2[4];
} Fx_c063_01E02E00;

static s32 func_01E02E00_c063(s32 arg0, Fx_c063_01E02E00 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f8 = 0x12C;
        o->fA = 0x12C;
        o->flip = func_0019A5C8() % 2;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        func_001076F0(o->col2, 0x80, 0x80, 0x80);
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 0x109) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x13;
        }
        if (o->col2[3] < 0xC0) {
            o->col2[3] += 0x13;
        }
    } else {
        if (o->col[3] > 0xF) {
            o->col[3] -= 14;
        } else {
            o->mode = 0;
        }
        if (o->col[3] > 0xF) {
            o->col[3] -= 14;
        }
    }
    if (o->flip != 0) {
        o->flip = 0;
    } else {
        o->flip = 1;
    }
    func_00205C40((s32)o->rot);
    o->tick++;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/c063", func_01E02F40_c063);

INCLUDE_ASM("asm/nonmatchings/mod/c063", func_01E031E0_c063);

/* shape c063:01E03430, 106 insns: a white-yellow expanding flash (b283:01E03260 shape): size 20 growing by 55 with the inner size a
   fifth of it, random turn, sub-frame 4; alpha up by 0x40 for 7 frames, then down by 8 until it ends; second colour flickers */

typedef struct {
    u8 pad0[1];
} Game_c063_01E03430;

typedef struct {
    u8 pad0[0x20];
    s32 rot[3];
    u8 pad2C[0x1C];
    f32 f48;
    f32 f4C;
    s16 kind;
    u8 pad52[2];
    s16 t;
    s16 sub;
    s16 state;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_c063_01E03430;

static s32 func_01E03430_c063(Game_c063_01E03430 *g, Obj_c063_01E03430 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f48 = 20.0f;
        o->f4C = 0.0f;
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
        o->kind = 0;
        o->h5A = 0x3C;
        o->h5C = 3;
        o->sub = 4;
        o->state = 2;
        o->c1[3] = 0;
        o->rot[0] = func_0019A5C8() % 65535;
        o->rot[1] = func_0019A5C8() % 65535;
        o->rot[2] = func_0019A5C8() % 65535;
    }
    if (o->t < 7) {
        if (o->c0[3] < 0xC0) {
            o->c0[3] += 0x40;
        }
    } else if (o->c0[3] > 9) {
        o->c0[3] -= 8;
    } else {
        o->state = 0;
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->c1, 0xA0, 0xA0, 0x60);
    } else {
        func_001076F0(o->c1, 0xC0, 0xC0, 0x60);
    }
    o->f48 += 55.0f;
    o->f4C = 0.2f * o->f48;
    o->t++;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/c063", func_01E035E0_c063);

INCLUDE_ASM("asm/nonmatchings/mod/c063", func_01E03B30_c063);

/* shape c063:01E03DB0, 88 insns: a yellow tumbling spark: random turn on all three axes, scale from the scene, angle 90 climbing
   by 0..6 a frame until 270 (then it ends); alpha up by 0x80 for 8 frames, then down by 9 until it ends */

typedef struct {
    u8 pad0[0x5A64];
    f32 scale;
} Scene_c063_01E03DB0;

typedef struct {
    u8 pad0[0x20];
    s32 rot[3];
    u8 pad2C[0x1C];
    f32 scale;
    u8 pad4C[4];
    s16 ang;
    u8 pad52[2];
    s16 t;
    s16 h56;
    s16 state;
    u8 pad5A[6];
    u8 c0[4];
} Obj_c063_01E03DB0;

static s32 func_01E03DB0_c063(Scene_c063_01E03DB0 *g, Obj_c063_01E03DB0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->rot[0] = func_0019A5C8() % 65535;
        o->rot[1] = func_0019A5C8() % 65535;
        o->rot[2] = func_0019A5C8() % 65535;
        o->h56 = 0;
        func_001076F0(o->c0, 0x80, 0x80, 0x40);
        o->ang = 0x5A;
        o->state = 2;
        o->c0[3] = 0;
        o->scale = g->scale;
    }
    if (o->t < 8) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x80;
        }
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    o->t++;
    if (o->ang < 0x10E) {
        o->ang += (s16)(func_0019A5C8() % 7);
    } else {
        o->state = 0;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/c063", func_01E03F10_c063);

INCLUDE_ASM("asm/nonmatchings/mod/c063", func_01E04250_c063);

/* func_001076F0 takes plain ints here (functions.h says s8): hide that prototype */

/* shape c063:01E04510, 115 insns: glow pair in one of three colour/life presets, fading in and out */

typedef struct Glow_c063_01E04510 {
    u8 pad0[6];
    s16 life;
    u8 pad8[0x48];
    s16 kind;
    u8 pad52[2];
    s16 age;
    u8 pad56[2];
    s16 state;
    u8 pad5A[6];
    u8 c0[4];
    u8 c1[4];
} Glow_c063_01E04510;

static s32 func_01E04510_c063(s32 arg0, Glow_c063_01E04510 *o) {
    extern s32 func_001076F0();
    if (o->state == 1) {
        if (o->kind == 0) {
            func_001076F0(o->c0, 0xF0, 0xF0, 0xF0);
            func_001076F0(o->c1, 0xF0, 0xF0, 0xF0);
            o->life = 20;
        }
        if (o->kind == 1) {
            func_001076F0(o->c0, 0xD0, 0xD0, 0x80);
            func_001076F0(o->c1, 0xC0, 0xC0, 0x80);
            o->life = 20;
        }
        if (o->kind == 2) {
            func_001076F0(o->c0, 0xF0, 0xE0, 0xFF);
            func_001076F0(o->c1, 0xF0, 0xE0, 0xFF);
            o->life = 30;
        }
        o->state = 2;
    }
    if (o->age < o->life) {
        if (o->kind != 2) {
            if (o->c0[3] < 0x80) {
                o->c0[3] += 7;
            }
            if (o->c1[3] < 0x80) {
                o->c1[3] += 7;
            }
        } else {
            if (o->c0[3] < 0xC0) {
                o->c0[3] += 0xC;
            }
            if (o->c1[3] < 0xC0) {
                o->c1[3] += 0xC;
            }
        }
    } else {
        if (o->c0[3] > 5) {
            o->c0[3] -= 4;
        } else {
            o->state = 0;
        }
        if (o->c1[3] > 5) {
            o->c1[3] -= 4;
        } else {
            o->c1[3] = 0;
        }
    }
    o->age++;
    return 0;
}

/* shape c063:01E046E0, 48 insns: b718:01E03D10 family: volume eased by 10 toward 0x30 once the scene state passes 30, else toward 0x80; counts its tick */

typedef struct {
    u8 pad[0x6B30];
    s32 state;
} Game_c063_01E046E0;

typedef struct {
    u8 pad[0x50];
    s16 vol;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 mode;
} Fade_c063_01E046E0;

static s32 func_01E046E0_c063(Game_c063_01E046E0 *g, Fade_c063_01E046E0 *o) {
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
        if (o->vol > 0x80) {
            o->vol = 0x80;
        }
    }
    o->t++;
    func_001F6D00((u8)o->vol);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/c063", func_01E047A0_c063);

INCLUDE_ASM("asm/nonmatchings/mod/c063", func_01E04AC0_c063);

/* shape c063:01E05750, 60 insns: take a free slot (0xC8 of 0x70 bytes at 0x2A0), clear it, copy the object's
   position (0x250), 0x5A and 0x50 from the object (0x6C26, 0x6C32), store arg; returns 1 if a slot was found */

typedef struct {
    u8 pad0[0x10];
    f32 pos[3];
    u8 pad1C[0x28];
    s32 arg;
    u8 pad48[8];
    s16 f50;
    u8 pad52[6];
    s16 used;
    s16 f5A;
    u8 pad5C[0x14];
} Slot_c063_01E05750;

typedef struct {
    u8 pad0[0x250];
    f32 pos[3];
    u8 pad25C[0x44];
    Slot_c063_01E05750 slots[0xC8];
    u8 pad5A20[0x6C26 - 0x5A20];
    s16 f6C26;
    u8 pad6C28[0xA];
    s16 f6C32;
} Obj_c063_01E05750;

static s32 func_01E05750_c063(Obj_c063_01E05750 *obj, s32 arg) {
    extern void func_00195108();
    Slot_c063_01E05750 *s = NULL;
    s16 i;

    for (i = 0; i < 0xC8; i++) {
        if (obj->slots[i].used == 0) {
            func_00195108(&obj->slots[i], 0x70);
            obj->slots[i].used = 1;
            s = &obj->slots[i];
            i = 0xC8;
        }
    }
    if (s != NULL) {
        s->pos[0] = obj->pos[0];
        s->pos[1] = obj->pos[1];
        s->pos[2] = obj->pos[2];
        s->f5A = obj->f6C26;
        s->f50 = obj->f6C32;
        s->arg = arg;
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/c063", func_01E05840_c063);

INCLUDE_ASM("asm/nonmatchings/mod/c063", func_01E05B50_c063);

/* shape b363:01E06930, 264 insns, 4 copies: draws a band of 12 quads (two rings, radius and height from the table at two
   angles 20 apart) around a position, scaled by size / 1500, turned by the object's rotation; blend from
   flags >> 4. */

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    s16 rect[4];
    u8 pad9C[0x22];
    s16 mode;
    u8 padC0[0x18];
    u8 xD8[1];
} Obj_b363_01E06930;

typedef struct {
    u8 pad00[0x20];
    Vec4f rot;
    u8 pad30[0x18];
    f32 size;
    u8 pad4C[4];
    s16 h50;
    u8 pad52[8];
    s16 start;
    u8 pad5C[4];
    u8 col[4];
} Band_b363_01E06930;

static void func_01E06640_c063(Obj_b363_01E06930 *o, Band_b363_01E06930 *s, Vec4f pos, s32 flags) {
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00106DD0(void *, f32, f32, f32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f p2;
    Vec4f scale;
    f32 m[16];
    f32 depth[4];
    u8 pkt[0x90];
    f32 r0;
    s32 k;
    s16 b;
    s16 a;
    s16 t;
    u8 *p;
    f32 r1;
    f32 sc;

    p = pkt;
    func_00109270(p, 0, 0);
    func_00107790(p, s->col, 0);
    b = flags >> 4;
    if (b == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((u64)b << 2) | (((u64)0x80 << 32) | 0x40));
    }
    func_00108500(p, o->rect, o->mode);
    func_00208700(p, o->texture, 1);
    p2.x = pos.x;
    p2.y = pos.y;
    p2.z = pos.z;
    sc = s->size;
    sc /= 1500.0f;
    func_00106DD0(&scale, sc, sc, sc);
    func_00108EF0(m, &scale, &s->rot, &p2);
    quad[0].y = 90.0f * func_00108030(o->xD8, s->h50, 0);
    quad[1].y = quad[0].y;
    quad[2].y = 90.0f * func_00108030(o->xD8, s->h50 + 20, 0);
    quad[3].y = quad[2].y;
    r0 = 90.0f * func_00108030(o->xD8, s->h50, 1);
    r1 = 90.0f * func_00108030(o->xD8, s->h50 + 20, 1);
    a = 0;
    for (k = 0; k < 12; k++) {
        if (k == 0) {
            t = s->start + a;
            quad[2].x = r1 * func_00108030(o->xD8, t, 1);
            quad[2].z = r1 * func_00108030(o->xD8, t, 0);
            quad[0].x = r0 * func_00108030(o->xD8, t, 1);
            quad[0].z = r0 * func_00108030(o->xD8, t, 0);
            t = s->start + 30 + a;
            quad[3].x = r1 * func_00108030(o->xD8, t, 1);
            quad[3].z = r1 * func_00108030(o->xD8, t, 0);
            quad[1].x = r0 * func_00108030(o->xD8, t, 1);
            quad[1].z = r0 * func_00108030(o->xD8, t, 0);
        } else {
            quad[2].x = quad[3].x;
            quad[2].z = quad[3].z;
            quad[0].x = quad[1].x;
            quad[0].z = quad[1].z;
            t = s->start + 30 + a;
            quad[3].x = r1 * func_00108030(o->xD8, t, 1);
            quad[3].z = r1 * func_00108030(o->xD8, t, 0);
            quad[1].x = r0 * func_00108030(o->xD8, t, 1);
            quad[1].z = r0 * func_00108030(o->xD8, t, 0);
        }
        if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
            func_002075F0(p, o->ot, (u32)depth[0]);
        }
        a += 30;
    }
}

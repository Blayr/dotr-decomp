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

static void func_01E00080_b537(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

typedef struct Rect_b008_01E00080 {
    s16 x, y, w, h;
} Rect_b008_01E00080;
typedef struct Uv_b008_01E00080 {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad4;
    u64 xyz;
} Uv_b008_01E00080;
typedef struct Pk_b008_01E00080 {
    u8 pad0[0x18];
    Uv_b008_01E00080 c[4];
} Pk_b008_01E00080;

/* shape b008:01E004D0, 351 insns, 12 copies: draws a row of small camera-facing sprites (one per entry, texture corner
   mode per entry via b008:01E00080), each shaken by a per-entry table offset that grows along the row;
   depth mode 0 (projected), 1 (far) or 2 (front). Calls the module's UV helper (shape b008:01E00080). */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b008_01E004D0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Rgbaq_b008_01E004D0 c;
    struct {
        u64 tc;
        u64 x : 16;
        u64 y : 16;
        u64 z : 24;
        u64 f : 8;
    } v[4];
    u8 tail[0x38];
} Pkt_b008_01E004D0;

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    Rect_b008_01E00080 rect;
    u8 pad9C[0x1C];
    s16 count;
    u8 padBA[6];
    s16 ids[12];
    u8 xD8[1];
} Obj_b008_01E004D0;

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 off;
    u8 padA[0x1E];
    u8 col[4];
    u8 pad2C[4];
    s16 w30;
    u8 pad32[6];
    s16 size;
} Spr_b008_01E004D0;

static void func_01E00920_b537(Obj_b008_01E004D0 *o, Spr_b008_01E004D0 *s, s32 mode, s8 *tbl) {
    extern Rgbaq_b008_01E004D0 func_00107740(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern s32 func_00109100(void *, void *, s32, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f pos;
    Vec4f scale;
    f32 depth[4];
    f32 m[16];
    s32 rot[4];
    Pkt_b008_01E004D0 pkt __attribute__((aligned(8)));
    s16 i;
    f32 size;
    Pkt_b008_01E004D0 *p;
    f32 d;
    s32 h;
    f32 f;
    s8 *j;

    func_00207500();
    p = (Pkt_b008_01E004D0 *)(s32)&pkt;
    p->count = 0x24;
    p->tag = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad = 0;
    p->count |= 0x800;
    func_002086D0(p, ((u64)0x80 << 32) | 0x44);
    pkt.c = func_00107740(s->col);
    func_00208700(p, o->texture, 1);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    rot[1] = rot[1] / 180;
    rot[1] = -rot[1];
    rot[0] = rot[0] / 180;
    rot[0] = -rot[0];
    pos.x = s->x;
    pos.y = s->y;
    pos.z = s->z;
    func_00108EF0(m, &scale, NULL, &pos);
    for (i = 0; i < o->count; i++) {
        func_01E00080_b537((Pk_b008_01E00080 *)p, &o->rect, o->ids[i]);
        size = s->size;
        func_00108CE0(quad, size, size);
        func_00109100(quad, rot, 1, o->xD8);
        func_00109100(quad, rot, 0, o->xD8);
        j = tbl + i;
        h = i >> 1;
        f = j[s->off] / 20.0f;
        d = f * (s->w30 + h);
        quad[0].x += d;
        quad[1].x += d;
        quad[2].x += f * (s->w30 + h);
        quad[3].x += f * (s->w30 + h);
        f = j[s->off + 100] / 20.0f;
        d = f * (s->w30 + h);
        quad[0].y += d;
        quad[1].y += d;
        quad[2].y += f * (s->w30 + h);
        quad[3].y += f * (s->w30 + h);
        f = j[s->off + 180] / 20.0f;
        d = f * (s->w30 + h);
        quad[0].z += d;
        quad[1].z += d;
        quad[2].z += f * (s->w30 + h);
        quad[3].z += f * (s->w30 + h);
        if (mode == 0) {
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                func_002075F0(p, o->ot, (u32)depth[0]);
            }
        } else if (mode == 1) {
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
                func_002075F0(p, o->ot, 0);
            }
        } else if (mode == 2) {
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                func_002075F0(p, o->ot, -1);
            }
        }
    }
}

/* shape b500:01E01850, 342 insns, 15 copies: draws obj->count sprites along a curve read from three s8 tables
   (0x64 apart), each turned by the object's angles; mode (flags & 0xF) 0 = depth from the projection,
   1 = far z, 2 = -1. Calls the module's sprite-UV helper (shape b003:01E00080) as a static function. */

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
    u8 padBA[6];
    s16 fC0;
    u8 padC2[0x16];
    u8 fD8[4];
} Obj_b500_01E01850;

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 tab;
    u8 padA[0x1E];
    u8 tex[8];
    s16 scale;
    u8 pad32[6];
    s16 size;
    s16 angle;
} Def_b500_01E01850;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b500_01E01850;

typedef struct {
    f32 u, v;
} Uv_b500_01E01850;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b500_01E01850 uv;
    u64 pad18;
    Xyz_b500_01E01850 v[4];
    u64 pad60[6];
} Pk_b500_01E01850;

typedef struct {
    u64 tag;
    Pk_b500_01E01850 pk;
} Buf_b500_01E01850;

static void func_01E00EA0_b537(Obj_b500_01E01850 *obj, Def_b500_01E01850 *def, s32 flags, s8 *base) {
    f32 m2[4][4];
    Vec4f pos;
    Vec4f s;
    f32 out[4];
    f32 m[4][4];
    s32 rot[4];
    Buf_b500_01E01850 buf;
    Uv_b500_01E01850 uv;
    s16 sel;
    s16 i;
    Pk_b500_01E01850 *p;
    s32 mode;
    s8 *t;
    s32 h;
    f32 f;
    f32 r;
    f32 x;
    f32 y;
    f32 z;
    extern void func_00108EF0();
    extern void func_00109100();

    func_00207500();
    p = &buf.pk;
    p->flags = 0x24;
    p->size = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad4 = 0;
    p->flags |= 0x800;
    sel = flags >> 4;
    if (sel == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((s64)sel << 2) | (((u64)0x80 << 32) | 0x40));
    }
    func_00107740(&uv, def->tex);
    p->uv = uv;
    func_00208700(p, obj->f88, 1);
    s.x = 0.1f;
    s.y = 0.1f;
    s.z = 0.1f;
    func_00205C40((s32)rot);
    rot[1] /= 180;
    rot[1] = -rot[1];
    rot[0] /= 180;
    rot[0] = -rot[0];
    pos.x = def->x;
    pos.y = def->y;
    pos.z = def->z;
    func_00108EF0(m, &s, NULL, &pos);
    mode = flags & 0xF;
    for (i = 0; i < obj->count; i++) {
        func_01E00080_b537((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fC0);
        r = def->size;
        func_00108CE0(m2, r, r);
        func_00109100(m2, rot, 1, obj->fD8);
        func_00109100(m2, rot, 0, obj->fD8);
        t = base + i;
        h = i >> 1;
        f = t[def->tab];
        f /= 20.0f;
        x = f * (def->scale + h);
        f = t[def->tab + 100];
        f /= 20.0f;
        y = f * (def->scale + h);
        m2[0][0] += x;
        m2[1][0] += x;
        m2[2][0] += x;
        m2[3][0] += x;
        m2[0][1] += y;
        m2[1][1] += y;
        m2[2][1] += y;
        m2[3][1] += y;
        f = t[def->tab + 180];
        f /= 20.0f;
        z = f * (def->scale + h);
        m2[0][2] += z;
        m2[1][2] += z;
        m2[2][2] += z;
        m2[3][2] += z;
        if (mode == 0) {
            if (func_00205630((s32)m2, 0x70000000, (s32)m, (s32)p, out) != 0) {
                func_002075F0((s32)p, obj->f80, func_001A23B0(out[0]));
            }
        } else if (mode == 1) {
            if (func_00205630((s32)m2, 0x70000000, (s32)m, (s32)p, out) != 0) {
                p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
                func_002075F0((s32)p, obj->f80, 0);
            }
        } else if (mode == 2) {
            if (func_00205630((s32)m2, 0x70000000, (s32)m, (s32)p, out) != 0) {
                func_002075F0((s32)p, obj->f80, -1);
            }
        }
    }
}

/* shape b537:01E013B0, 57 insns: sets the scene colour to red 0x80, counts its timer and, on frames 0x87..0x93, puts the
   effect point 1 above the first model's joint and spawns two b537:01E01820 effects (sides 0 and 1) */

typedef struct {
    u8 pad0[0x250];
    f32 x, y, z;
    u8 pad25C[0x2FD4 - 0x25C];
    u8 r, g, b, a;
    u8 pad2FD8[0x24];
    s16 joint0;
    s16 joint1;
    u8 pad3000[0x12];
    s16 side;
    u8 pad3014[6];
    s16 t;
} Scene_b537_01E013B0;

static void func_01E013B0_b537(Scene_b537_01E013B0 *s) {
    extern void b537_01E01820(void);
    extern s32 b537_01E021C0(Scene_b537_01E013B0 *, void *, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    Vec4f a;
    Vec4f b;

    s->r = 0x80;
    s->g = 0;
    s->b = 0;
    s->a = 0;
    s->t++;
    if (s->t >= 0x87 && s->t < 0x94) {
        func_001F5620(func_001F53A0(), s->joint0, &a);
        func_001F5620(func_001F53A0(), s->joint1, &b);
        s->x = a.x;
        s->y = 1.0f + a.y;
        s->z = a.z;
        s->side = 0;
        b537_01E021C0(s, b537_01E01820, 0);
        s->side = 1;
        b537_01E021C0(s, b537_01E01820, 0);
    }
}

/* shape b027:01E00DA0, 2 insns, 89 copies: an empty handler that returns 0 */

static s32 func_01E014A0_b537(void) {
    return 0;
}

/* shape b027:01E00DA0, 2 insns, 89 copies: an empty handler that returns 0 */

static s32 func_01E014B0_b537(void) {
    return 0;
}

/* shape b537:01E014C0, 213 insns: b566:01E015D0 family dark grey (0x50) smoke: size 4 growing by 2 for 20 ticks,
   frame 0..7 cycling to 6 on odd ticks, speed 4..6 swept from tick 15 to 99; a fresh puff (the old h30 kept in hA is 0)
   holds 90..179 ticks, a follow-up 0..9; alpha up by 16 to 0x40, then down by 4; it sinks toward the second point by
   1/160 of the gap for 20 ticks, then (fresh puffs only) by 1/160 or 1/136 once the scene count (0x301A) passes 178,
   growing 2 more a tick */

typedef struct {
    u8 pad0[0x301A];
    s16 count;
} Ctx_b537_01E014C0;

typedef struct {
    s16 x, y, z;
    s16 hold;
    s16 h8;
    s16 hA;
    s16 hC;
    s16 speed;
    s32 rot[3];
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b537_01E014C0;

static s32 func_01E014C0_b537(Ctx_b537_01E014C0 *g, Fx_b537_01E014C0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5F90(s32, f32 *);
    f32 v[12];

    if (o->mode == 1) {
        o->f38 = 4;
        o->f34 = func_0019A5C8() % 8;
        o->hA = o->f30;
        func_001076F0(o->col, 0x50, 0x50, 0x50);
        o->f30 = 0;
        o->f3A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 3 + 4;
        o->h8 = func_0019A5C8() % 25;
        if (o->hA == 0) {
            o->hold = func_0019A5C8() % 90 + 90;
        } else {
            o->hold = func_0019A5C8() % 10;
        }
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0x30) {
            o->col[3] += 16;
        }
    } else if (o->col[3] > 5) {
        o->col[3] -= 4;
    } else {
        o->mode = 0;
    }
    func_001F5F90(func_001F5380(), v);
    func_001F5F90(func_001F53A0(), &v[4]);
    *(f32 *)(u32)&v[2] -= v[6];
    if (o->tick < 20) {
        *(f32 *)(u32)&v[2] /= 160.0f;
        o->z = o->z + v[2];
    } else if (o->hA == 0) {
        if (g->count > 178) {
            if (g->count < 230) {
                *(f32 *)(u32)&v[2] /= 160.0f;
            } else {
                *(f32 *)(u32)&v[2] /= 136.0f;
            }
            o->z = o->z + v[2];
            o->f38 += 2;
        } else {
            o->f38 += 2;
        }
    }
    if (o->tick % 2 == 1) {
        if (o->f34 < 6) {
            o->f34++;
        } else {
            o->f34 = 0;
        }
    }
    if (o->tick > 14 && o->tick < 100 && o->tick != 0) {
        o->f30 += o->speed;
    }
    if (o->tick < 20 && o->tick != 0) {
        o->f38 += 2;
    }
    o->tick++;
    return 0;
}

/* OVL_WARM */

/* shape b537:01E01820, 223 insns: b008:01E00FB0 family puff, grey 0xA0, size 4 growing 2, frame 0..7 cycling every
   other tick, kind kept in 0xA, speed 4..6, 0x8 0..24, hold 90..179 (kind 0) or 0..9; nudged 3 toward the scene side
   (0x3014); alpha up by 0x10 to 0x30 during the hold, then down by 4; closes a 160th of the camera depth gap for 20
   ticks, then (kind 0, scene time 179..229 a 160th, from 230 a 136th) while growing; turns 6 a tick after tick 20 */

typedef struct {
    s16 x, y, z;
    s16 hold;
    s16 h8;
    s16 kind;
    u8 padC[2];
    s16 speed;
    u8 pad10[0x18];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 frame;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b537_01E01820;

typedef struct {
    u8 pad0[0x3014];
    s16 side;
    u8 pad3016[4];
    s16 timer;
} Scn_b537_01E01820;

static s32 func_01E01820_b537(Scn_b537_01E01820 *g, Fx_b537_01E01820 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5F90(s32, f32 *);
    f32 v[12];

    if (o->mode == 1) {
        o->f38 = 4;
        o->frame = func_0019A5C8() % 8;
        o->kind = o->f30;
        func_001076F0(o->col, 0xA0, 0xA0, 0xA0);
        o->f30 = 0;
        o->speed = func_0019A5C8() % 3 + 4;
        o->h8 = func_0019A5C8() % 25;
        if (o->kind == 0) {
            o->hold = func_0019A5C8() % 90 + 90;
        } else {
            o->hold = func_0019A5C8() % 10;
        }
        if (g->side != 0) {
            o->z += 3;
        } else {
            o->z -= 3;
        }
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0x30) {
            o->col[3] += 0x10;
        }
    } else if (o->col[3] > 5) {
        o->col[3] -= 4;
    } else {
        o->mode = 0;
    }
    func_001F5F90(func_001F5380(), v);
    func_001F5F90(func_001F53A0(), &v[4]);
    *(f32 *)(u32)&v[2] -= v[6];
    if (o->tick < 20) {
        *(f32 *)(u32)&v[2] /= 160.0f;
        o->z = o->z + *(f32 *)(u32)&v[2];
    } else if (o->kind == 0) {
        if (g->timer > 178) {
            if (g->timer < 230) {
                *(f32 *)(u32)&v[2] /= 160.0f;
            } else {
                *(f32 *)(u32)&v[2] /= 136.0f;
            }
            o->z = o->z + *(f32 *)(u32)&v[2];
            o->f38 += 2;
        } else {
            o->f38 += 2;
        }
    }
    if (o->tick % 2 == 1) {
        if (o->frame < 6) {
            o->frame++;
        } else {
            o->frame = 0;
        }
    }
    if (o->tick > 14 && o->tick < 100 && o->tick != 0) {
        o->f30 += o->speed;
    }
    if (o->tick < 20 && o->tick != 0) {
        o->f38 += 2;
    }
    if (o->tick > 20) {
        o->f3A += 6;
    }
    o->tick++;
    return 0;
}

/* shape b537:01E01BA0, 391 insns: b537's scene manager (b069:01E01210 family): with a scene id (>= 0) it clears the
   scene, resets both camera blocks, keeps the id, sets the 335-frame countdown, takes seven model handles, loads
   textures 11..15, 2 and page-5 textures 0..1, keeps the player's heading (degrees / 180) and fills the jitter tables
   (100..179: -10..9, 0..99: -40..39, 180..255: 1..2, then all of it -10..9); otherwise it runs the module's step and
   the live nodes' updates, draws the four sprite kinds with page-5 texture 1, rect 0x14 and a random frame, counts down
   and returns 1 / 3 / 6 at frames 250 / 320 / 261..314, 8 once the countdown runs out */

typedef struct {
    u8 pad0[0x24];
    void *fn;
    u8 pad28[0xC];
    s16 h34;
    s16 used;
    u8 pad38[8];
} Node_b537_01E01BA0;

typedef struct {
    u8 pad0[0x80];
    s32 ot2;
    u8 pad84[4];
    s32 tex88;
    u8 pad8C[8];
    Vec4f rect;
    u8 padA4[0x14];
    s16 hB8;
    u8 padBA[4];
    s16 hBE;
    u8 padC0[0x18];
    u8 camD8[0x188];
    s32 tex[16];
    u8 pad2A0[0x31C - 0x2A0];
    Node_b537_01E01BA0 node[150];
    u8 pad289C[0x2FB0 - 0x289C];
    s32 tex5[2];
    u8 pad2FB8[0x18];
    s32 count;
    u8 pad2FD4[8];
    s32 ot;
    u8 pad2FE0[0x1C];
    s16 model[7];
    u8 pad300A[0xA];
    s16 ang;
    u8 pad3016[2];
    s16 id;
    s16 timer;
    s8 rnd[256];
    s8 rnd2[256];
    u8 cam[0x170];
} Scene_b537_01E01BA0;

static s32 func_01E01BA0_b537(s32 arg0, s32 id) {
    Scene_b537_01E01BA0 *g = (Scene_b537_01E01BA0 *)arg0;
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern s32 func_00202BF0(s32, s32);
    extern void func_001F5F90(s32, void *);
    extern void func_001F6160(s32, void *);
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_01E00920_b537();
    extern void func_01E00EA0_b537();
    extern void func_01E013B0_b537();
    extern s32 func_01E014A0_b537();
    extern s32 func_01E014B0_b537();
    extern s32 func_01E014C0_b537();
    extern s32 func_01E01820_b537();
    s32 n;
    Vec4f v;
    Vec4f r1;
    Vec4f r2;
    Vec4f r3;
    Vec4f r4;
    s32 iv[4];
    s32 i;

    n = 0;
    g->ot = (s32)func_00207500();
    g->ot2 = (s32)func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x3390);
        func_00107C10(g->cam);
        func_00107C10(g->camD8);
        g->id = id;
        g->count = 335;
        g->model[0] = func_001F5560(func_001F53A0(), 0x1D, 1);
        g->model[1] = func_001F5560(func_001F53A0(), 1, 0);
        g->model[2] = func_001F5560(func_001F53A0(), 0x1B, 0);
        g->model[3] = func_001F5560(func_001F53A0(), 0x26, 0);
        g->model[4] = func_001F5560(func_001F53A0(), 0xF, 0);
        g->model[5] = func_001F5560(func_001F53A0(), 0xA, 0);
        g->model[6] = func_001F5560(func_001F53A0(), 0x3D, 0);
        for (i = 11; i < 16; i++) {
            g->tex[i] = func_00202BF0(4, i);
        }
        g->tex[2] = func_00202BF0(4, 2);
        for (i = 0; i < 2; i++) {
            g->tex5[i] = func_00202BF0(5, i);
        }
        func_001F6160(func_001F53A0(), iv);
        g->ang = iv[1] / 180.0f;
        for (i = 100; i < 180; i++) {
            g->rnd[i] = func_0019A5C8() % 20 - 10;
        }
        for (i = 0; i < 100; i++) {
            g->rnd[i] = func_0019A5C8() % 80 - 40;
        }
        for (i = 180; i < 256; i++) {
            g->rnd[i] = func_0019A5C8() % 2 + 1;
        }
        for (i = 0; i < 256; i++) {
            g->rnd[i] = func_0019A5C8() % 20 - 10;
        }
        return 0;
    }
    func_01E013B0_b537(g, 0);
    for (i = 0; i < 150; i++) {
        if (g->node[i].used != 0) {
            if (g->node[i].fn == func_01E014C0_b537) {
                func_01E014C0_b537(g, &g->node[i]);
            }
            if (g->node[i].fn == func_01E01820_b537) {
                func_01E01820_b537(g, &g->node[i]);
            }
        }
    }
    func_001F5F90(func_001F5380(), &v);
    v.z -= 25.0f;
    for (i = 0; i < 150; i++) {
        if (g->node[i].used != 0) {
            n++;
            if (g->node[i].fn == func_01E014A0_b537) {
                g->tex88 = g->tex5[1];
                func_00106080(&r1, 0x14, g->node[i].h34, 0);
                g->rect = r1;
                g->hB8 = 4;
                g->hBE = func_0019A5C8() % 4;
                func_01E00920_b537(g, &g->node[i], 0, g->rnd);
                g->hB8 = 0;
            }
            if (g->node[i].fn == func_01E014B0_b537) {
                g->tex88 = g->tex5[1];
                func_00106080(&r2, 0x14, g->node[i].h34, 0);
                g->rect = r2;
                g->hB8 = 2;
                g->hBE = func_0019A5C8() % 4;
                func_01E00920_b537(g, &g->node[i], 1, g->rnd2);
                g->hB8 = 0;
            }
            if (g->node[i].fn == func_01E014C0_b537) {
                g->tex88 = g->tex5[1];
                func_00106080(&r3, 0x14, g->node[i].h34, 0);
                g->rect = r3;
                g->hB8 = 6;
                g->hBE = func_0019A5C8() % 4;
                func_01E00920_b537(g, &g->node[i], 1, g->rnd);
                g->hB8 = 0;
            }
            if (g->node[i].fn == func_01E01820_b537) {
                g->tex88 = g->tex5[1];
                func_00106080(&r4, 0x14, g->node[i].h34, 0);
                g->rect = r4;
                g->hB8 = 3;
                g->hBE = func_0019A5C8() % 4;
                func_01E00EA0_b537(g, &g->node[i], 32, g->rnd);
                g->hB8 = 0;
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->timer == 250) {
        return 1;
    }
    if (g->timer == 320) {
        return 3;
    }
    if (g->timer > 260 && g->timer < 315) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b537:01E021C0, 74 insns: twin of b046:01E03E20: take the first free slot of the 150-slot pool, clear it,
   give it the scene's colour twice, the scene matrix, the scene's value 0x3012 and 0x300E and the two arguments; returns 1 if a
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
    u8 pad38[0x2];
    s16 w;
    u8 pad3C[0x4];
} Slot_b537_01E021C0;

typedef struct {
    u8 pad[0x250];
    u8 m[0xCC];
    Slot_b537_01E021C0 s[150];
    u8 pad289C[0x738];
    u8 r, g, b, a;
    u8 pad2FD8[0x36];
    s16 w;
    u8 pad3010[0x2];
    s16 v;
} Pool_b537_01E021C0;

static s32 func_01E021C0_b537(Pool_b537_01E021C0 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b537_01E021C0 *s = NULL;
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
        s->w = o->w;
        s->b = b;
        s->a = a;
    } else {
        ret = 0;
    }
    return ret;
}

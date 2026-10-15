#include "common.h"

/* shape b081:01E00080, 30 insns, 24 copies (s32 twin of b034:01E00080): shift a position history down by one, the newest from src */

static s32 func_01E00080_b718(Vec4f *dst, s32 n, s32 arg2, Vec4f *src) {
    s32 i;
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

/* shape b008:01E00080, 273 insns, 45 copies: the 4-mode version of b003:01E00080 (texture coordinates of a
   sprite quad from a rectangle). Callers rely on it being static in their file. */

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

static void func_01E00100_b718(Pk_b008_01E00080 *p, Rect_b008_01E00080 *r, s32 mode) {
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
        p->c[0].u = (r->x) << 4;
        p->c[0].v = (r->y + r->h) << 4;
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y + r->h) << 4;
        p->c[3].u = (r->x + r->w) << 4;
        p->c[3].v = (r->y) << 4;
    } else if (mode == 2) {
        p->c[2].u = (r->x) << 4;
        p->c[2].v = (r->y) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y + r->h) << 4;
        p->c[1].u = (r->x + r->w) << 4;
        p->c[1].v = (r->y + r->h) << 4;
    } else {
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y + r->h) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y + r->h) << 4;
    }
}

/* shape b045:01E005A0, 118 insns, 7 copies: one camera-facing sprite at the object position plus offset / 10,
   scaled by obj->size: the single-sprite member of the b018:01E00920 family. Calls the module's
   sprite-UV helper (shape b008:01E00080) as a static function. */

typedef struct {
    f32 s;
    f32 t;
} St_b045_01E005A0;

typedef struct {
    s16 n;
    u16 nreg;
    s32 pad4;
    u64 regs;
    St_b045_01E005A0 st;
    u8 pad18[0xF];
    u8 q0;
    u8 pad28[0xF];
    u8 q1;
    u8 pad38[0xF];
    u8 q2;
    u8 pad48[0xF];
    u8 q3;
} Pk_b045_01E005A0;

typedef struct {
    s16 x, y, z;
    s16 pad6;
    s16 dx;
    s16 dy;
    s16 dz;
    s16 padE;
    s32 rx, ry, rz;
    u8 pad1C[0xC];
    u8 tex[8];
    s16 scale;
    u8 pad32[6];
    s16 size;
} Obj_b045_01E005A0;

static void func_01E00550_b718(u8 *self, Obj_b045_01E005A0 *obj, Pk_b045_01E005A0 *pk, s8 *base) {
    extern void func_00108EF0();
    f32 m[16];
    Vec4f pos;
    Vec4f scale;
    f32 depth[4];
    f32 world[16];
    s32 rot[4];
    St_b045_01E005A0 uv;
    f32 r;
    f32 fx;
    f32 fy;
    f32 fz;

    pk->nreg = 0x24;
    pk->n = 9;
    pk->regs = 0x24242421 | ((s64)4 << 32);
    pk->pad4 = 0;
    pk->nreg |= 0x800;
    func_002086D0(pk, 0x48 | ((s64)0x80 << 32));
    *(s32 *)&pk->st.t = 0;
    pk->q0 = 0;
    pk->q1 = 0;
    pk->q2 = 0;
    pk->q3 = 0;
    func_00107740(&uv, obj->tex);
    pk->st = uv;
    func_01E00100_b718((Pk_b008_01E00080 *)pk, (Rect_b008_01E00080 *)(self + 0x94), 0);
    func_00208700(pk, *(void **)(self + 0x88), 1);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    fx = obj->dx;
    fy = obj->dy;
    fz = obj->dz;
    fx /= 10.0f;
    fy /= 10.0f;
    fz /= 10.0f;
    pos.x = obj->x + fx;
    pos.y = obj->y + fy;
    pos.z = obj->z + fz;
    func_00108EF0(world, &scale, rot, &pos);
    r = obj->size;
    func_00108CE0(m, r, r);
    if (func_00205630((s32)m, 0x70000000, (s32)world, (s32)pk, depth) != 0) {
        func_002075F0((s32)pk, *(s32 *)(self + 0x80), func_001A23B0(depth[0]));
    }
}

/* shape b018:01E00920: draws 20 textured sprites along a curve read from a per-frame table (three s8
   angle tables 0x64 apart), each scaled by obj->size. Calls the module's sprite-UV helper (shape
   b008:01E00080), included above as a static function: the call keeps pk in $a0 across it. */

typedef struct {
    f32 s;
    f32 t;
} St_b018_01E005A0;

typedef struct {
    s16 n;
    u16 nreg;
    s32 pad4;
    u64 regs;
    St_b018_01E005A0 st;
    u8 pad18[0xF];
    u8 q0;
    u8 pad28[0xF];
    u8 q1;
    u8 pad38[0xF];
    u8 q2;
    u8 pad48[0xF];
    u8 q3;
} Pk_b018_01E005A0;

typedef struct {
    s16 x, y, z;
    s16 pad6;
    s16 tab;
    s16 dy;
    s16 dz;
    s16 padE;
    s32 rx, ry, rz;
    u8 pad1C[0xC];
    u8 tex[8];
    s16 scale;
    u8 pad32[6];
    s16 size;
} Obj_b018_01E005A0;

static void func_01E00730_b718(u8 *self, Obj_b018_01E005A0 *obj, Pk_b018_01E005A0 *pk, s8 *base) {
    extern void func_00108EF0();
    f32 m[16];
    Vec4f pos;
    Vec4f scale;
    f32 depth[4];
    f32 world[16];
    s32 rot[4];
    St_b018_01E005A0 uv;
    s16 i;
    s16 n;
    s32 h;
    s8 *p;
    f32 r;
    f32 f;
    f32 fx;
    f32 fy;
    f32 fz;

    func_00207500();
    pk->nreg = 0x24;
    pk->n = 9;
    pk->regs = 0x24242421 | ((s64)4 << 32);
    pk->pad4 = 0;
    pk->nreg |= 0x800;
    func_002086D0(pk, 0x48 | ((s64)0x80 << 32));
    *(s32 *)&pk->st.t = 0;
    pk->q0 = 0;
    pk->q1 = 0;
    pk->q2 = 0;
    pk->q3 = 0;
    func_00107740(&uv, obj->tex);
    pk->st = uv;
    func_01E00100_b718((Pk_b008_01E00080 *)pk, (Rect_b008_01E00080 *)(self + 0x94), 0);
    func_00208700(pk, *(void **)(self + 0x88), 1);
    n = (*(s16 *)(self + 0xB8) != 0) ? *(s16 *)(self + 0xB8) : (s16)20;
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    rot[0] += obj->rx;
    rot[1] += obj->ry;
    rot[2] += obj->rz;
    fx = obj->tab;
    fy = obj->dy;
    fz = obj->dz;
    fx /= 10.0f;
    fy /= 10.0f;
    fz /= 10.0f;
    pos.x = obj->x + fx;
    pos.y = obj->y + fy;
    pos.z = obj->z + fz;
    func_00108EF0(world, &scale, rot, &pos);
    for (i = 0; i < n; i++) {
        r = obj->size;
        func_00108CE0(m, r, r);
        p = base + i;
        h = i >> 1;
        f = p[obj->tab];
        f /= 20.0f;
        func_00107070(m, 0, f * (obj->scale + h));
        f = p[obj->tab + 100];
        f /= 20.0f;
        func_00107070(m, 1, f * (obj->scale + h));
        f = p[obj->tab + 180];
        f /= 20.0f;
        func_00107070(m, 2, f * (obj->scale + h));
        if (func_00205630((s32)m, 0x70000000, (s32)world, (s32)pk, depth) != 0) {
            func_002075F0((s32)pk, *(s32 *)(self + 0x80), func_001A23B0(depth[0]));
        }
    }
}

/* shape b018:01E00920: draws 20 textured sprites along a curve read from a per-frame table (three s8
   angle tables 0x64 apart), each scaled by obj->size. Calls the module's sprite-UV helper (shape
   b008:01E00080), included above as a static function: the call keeps pk in $a0 across it. */

typedef struct {
    f32 s;
    f32 t;
} St_b018_01E00920;

typedef struct {
    s16 n;
    u16 nreg;
    s32 pad4;
    u64 regs;
    St_b018_01E00920 st;
    u8 pad18[0xF];
    u8 q0;
    u8 pad28[0xF];
    u8 q1;
    u8 pad38[0xF];
    u8 q2;
    u8 pad48[0xF];
    u8 q3;
} Pk_b018_01E00920;

typedef struct {
    s16 x, y, z;
    s16 pad6;
    s16 tab;
    u8 padA[6];
    s32 rx, ry, rz;
    u8 pad1C[0xC];
    u8 tex[8];
    s16 scale;
    u8 pad32[6];
    s16 size;
} Obj_b018_01E00920;

static void func_01E00AB0_b718(u8 *self, Obj_b018_01E00920 *obj, Pk_b018_01E00920 *pk, s8 *base) {
    extern void func_00108EF0();
    f32 m[16];
    Vec4f pos;
    Vec4f scale;
    f32 depth[4];
    f32 world[16];
    s32 rot[4];
    St_b018_01E00920 uv;
    s16 i;
    s32 h;
    s8 *p;
    f32 r;
    f32 f;

    func_00207500();
    pk->nreg = 0x24;
    pk->n = 9;
    pk->regs = 0x24242421 | ((s64)4 << 32);
    pk->pad4 = 0;
    pk->nreg |= 0x800;
    func_002086D0(pk, 0x48 | ((s64)0x80 << 32));
    *(s32 *)&pk->st.t = 0;
    pk->q0 = 0;
    pk->q1 = 0;
    pk->q2 = 0;
    pk->q3 = 0;
    func_00107740(&uv, obj->tex);
    pk->st = uv;
    func_01E00100_b718((Pk_b008_01E00080 *)pk, (Rect_b008_01E00080 *)(self + 0x94), 0);
    func_00208700(pk, *(void **)(self + 0x88), 1);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    rot[0] += obj->rx;
    rot[1] += obj->ry;
    rot[2] += obj->rz;
    pos.x = obj->x;
    pos.y = obj->y;
    pos.z = obj->z;
    func_00108EF0(world, &scale, rot, &pos);
    for (i = 0; i < 20; i++) {
        r = obj->size;
        func_00108CE0(m, r, r);
        p = base + i;
        h = i >> 1;
        f = p[obj->tab];
        f /= 20.0f;
        func_00107070(m, 0, f * (obj->scale + h));
        f = p[obj->tab + 100];
        f /= 20.0f;
        func_00107070(m, 1, f * (obj->scale + h));
        f = p[obj->tab + 180];
        f /= 20.0f;
        func_00107070(m, 2, f * (obj->scale + h));
        m[1] = 0.0f;
        m[5] = 0.0f;
        m[0] = 1.0f;
        m[4] = -1.0f;
        m[2] = 0.0f;
        m[6] = 0.0f;
        if (func_00205630((s32)m, 0x70000000, (s32)world, (s32)pk, depth) != 0) {
            func_002075F0((s32)pk, *(s32 *)(self + 0x80), func_001A23B0(depth[0]));
        }
    }
}

/* shape b045:01E00E30, 224 insns: b018:01E005A0 with n taken as is, rot[1] = -(rot[1] / 180) instead of the
   object's rotation (no rotation for the world matrix), and func_00109100(m, rot, 0, self + 0xD8) per sprite; draws n textured sprites along a curve read from a per-frame table (three s8
   angle tables 0x64 apart), each scaled by obj->size. Calls the module's sprite-UV helper (shape
   b008:01E00080), included above as a static function: the call keeps pk in $a0 across it. */

typedef struct {
    f32 s;
    f32 t;
} St_b045_01E00E30;

typedef struct {
    s16 n;
    u16 nreg;
    s32 pad4;
    u64 regs;
    St_b045_01E00E30 st;
    u8 pad18[0xF];
    u8 q0;
    u8 pad28[0xF];
    u8 q1;
    u8 pad38[0xF];
    u8 q2;
    u8 pad48[0xF];
    u8 q3;
} Pk_b045_01E00E30;

typedef struct {
    s16 x, y, z;
    s16 pad6;
    s16 tab;
    s16 dy;
    s16 dz;
    s16 padE;
    s32 rx, ry, rz;
    u8 pad1C[0xC];
    u8 tex[8];
    s16 scale;
    u8 pad32[6];
    s16 size;
} Obj_b045_01E00E30;

static void func_01E00DE0_b718(u8 *self, Obj_b045_01E00E30 *obj, Pk_b045_01E00E30 *pk, s8 *base) {
    extern void func_00108EF0();
    extern void func_00109100();
    f32 m[16];
    Vec4f pos;
    Vec4f scale;
    f32 depth[4];
    f32 world[16];
    s32 rot[4];
    St_b045_01E00E30 uv;
    s16 i;
    s16 n;
    s32 h;
    s8 *p;
    f32 r;
    f32 f;
    f32 fx;
    f32 fy;
    f32 fz;

    func_00207500();
    n = *(s16 *)(self + 0xB8);
    pk->nreg = 0x24;
    pk->n = 9;
    pk->regs = 0x24242421 | ((s64)4 << 32);
    pk->pad4 = 0;
    pk->nreg |= 0x800;
    func_002086D0(pk, 0x48 | ((s64)0x80 << 32));
    *(s32 *)&pk->st.t = 0;
    pk->q0 = 0;
    pk->q1 = 0;
    pk->q2 = 0;
    pk->q3 = 0;
    func_00107740(&uv, obj->tex);
    pk->st = uv;
    func_01E00100_b718((Pk_b008_01E00080 *)pk, (Rect_b008_01E00080 *)(self + 0x94), 0);
    func_00208700(pk, *(void **)(self + 0x88), 1);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    rot[1] /= 180;
    rot[1] = -rot[1];
    fx = obj->tab;
    fy = obj->dy;
    fz = obj->dz;
    fx /= 10.0f;
    fy /= 10.0f;
    fz /= 10.0f;
    pos.x = obj->x + fx;
    pos.y = obj->y + fy;
    pos.z = obj->z + fz;
    func_00108EF0(world, &scale, 0, &pos);
    for (i = 0; i < n; i++) {
        r = obj->size;
        func_00108CE0(m, r, r);
        func_00109100(m, rot, 0, self + 0xD8);
        p = base + i;
        h = i >> 1;
        f = p[obj->tab];
        f /= 20.0f;
        func_00107070(m, 0, f * (obj->scale + h));
        f = p[obj->tab + 100];
        f /= 20.0f;
        func_00107070(m, 1, f * (obj->scale + h));
        f = p[obj->tab + 180];
        f /= 20.0f;
        func_00107070(m, 2, f * (obj->scale + h));
        if (func_00205630((s32)m, 0x70000000, (s32)world, (s32)pk, depth) != 0) {
            func_002075F0((s32)pk, *(s32 *)(self + 0x80), func_001A23B0(depth[0]));
        }
    }
}

/* shape b045:01E011B0, 277 insns: draws a row of small camera-facing sprites (4 wide, the sprite's h38 high) into
   the given packet, the camera rotation offset by the sprite's own rotation; each is shaken by a per-entry table
   offset growing along the row, the far corners by 0.7 of it. Calls the module's sprite-UV helper (shape
   b008:01E00080), included above as a static function. */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b045_01E011B0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Rgbaq_b045_01E011B0 c;
    struct {
        u64 tc;
        u64 x : 16;
        u64 y : 16;
        u64 z : 24;
        u64 f : 8;
    } v[4];
} Pkt_b045_01E011B0;

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    Rect_b008_01E00080 rect;
    u8 pad9C[0x1C];
    s16 count;
    u8 padBA[0x1E];
    u8 xD8[1];
} Obj_b045_01E011B0;

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 off;
    u8 padA[6];
    s32 rot[3];
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 w30;
    u8 pad32[6];
    s16 h38;
} Spr_b045_01E011B0;

static void func_01E01160_b718(Obj_b045_01E011B0 *o, Spr_b045_01E011B0 *s, Pkt_b045_01E011B0 *p, s8 *tbl) {
    f32 hh;
    extern Rgbaq_b045_01E011B0 func_00107740(void *);
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
    s16 i;
    f32 d;
    s32 h;
    f32 f;
    s8 *j;
    f32 w;

    func_00207500();
    p->count = 0x24;
    p->tag = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad = 0;
    p->count |= 0x800;
    func_002086D0(p, ((u64)0x80 << 32) | 0x48);
    p->c.q = 0.0f;
    p->v[0].f = 0;
    p->v[1].f = 0;
    p->v[2].f = 0;
    p->v[3].f = 0;
    p->c = func_00107740(s->col);
    func_01E00100_b718((Pk_b008_01E00080 *)p, &o->rect, 0);
    func_00208700(p, o->texture, 1);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    rot[0] += s->rot[0];
    rot[1] += s->rot[1];
    rot[2] += s->rot[2];
    func_00205C40((s32)rot);
    rot[1] = rot[1] / 180;
    rot[1] = -rot[1];
    pos.x = s->x;
    pos.y = s->y;
    pos.z = s->z;
    func_00108EF0(m, &scale, NULL, &pos);
    for (i = 0; i < o->count; i++) {
        hh = s->h38;
        func_00108CE0(quad, w = 4.0f, hh);
        func_00109100(quad, rot, 0, o->xD8);
        j = tbl + i;
        h = i >> 1;
        f = j[s->off];
        f /= 20.0f;
        d = f * (s->w30 + h);
        quad[0].x += d;
        quad[1].x += d;
        quad[2].x += 0.7f * (f * (s->w30 + h));
        quad[3].x += 0.7f * (f * (s->w30 + h));
        f = j[s->off + 100];
        f /= 20.0f;
        d = f * (s->w30 + h);
        quad[0].y += d;
        quad[1].y += d;
        quad[2].y += 0.7f * (f * (s->w30 + h));
        quad[3].y += 0.7f * (f * (s->w30 + h));
        f = j[s->off + 180];
        f /= 20.0f;
        d = f * (s->w30 + h);
        quad[0].z += d;
        quad[1].z += d;
        quad[2].z += 0.7f * (f * (s->w30 + h));
        quad[3].z += 0.7f * (f * (s->w30 + h));
        if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
            func_002075F0(p, o->ot, (u32)depth[0]);
        }
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

static void func_01E015C0_b718(u8 *self, Obj_b018_01E00C50 *obj, void *pk) {
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

static Vec_b018_01E00EE0 func_01E01850_b718(Vec_b018_01E00EE0 *p, s32 type, f32 t) {
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

/* OVL_WARM */

/* shape b018:01E01320: curved beam along func_01E01850_b718 spline points. Needs func_01E01850_b718 in the same file and
   static: the original keeps $a0 (the returned Vec buffer) across each call. */

typedef struct {
    u8 r, g, b, a;
} Col_b018_01E01320;

typedef struct {
    u8 pad00[6];
    s16 count;
    u8 pad08[0x20];
    Col_b018_01E01320 col;
    u8 pad2C[0xC];
    s16 width;
} Beam_b018_01E01320;

typedef struct {
    u8 b[0x90];
} Pkt_b018_01E01320;

static void func_01E01C90_b718(s32 unused, Beam_b018_01E01320 *an, Vec_b018_01E00EE0 *pts) {
    extern s32 func_00207500(void);
    extern void func_001094F0(void *);
    extern void func_00107990(void *, void *, s32);
    extern void func_001092E0(void *, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec_b018_01E00EE0 ab[2];
    Vec_b018_01E00EE0 ctrl[4];
    Vec_b018_01E00EE0 q[4];
    f32 depth __attribute__((aligned(16)));
    Vec_b018_01E00EE0 r1;
    Vec_b018_01E00EE0 r2;
    Pkt_b018_01E01320 pkt __attribute__((aligned(8)));
    Col_b018_01E01320 col;
    s32 x;
    s32 i;
    s32 k;
    s32 j;
    s16 n;
    Pkt_b018_01E01320 *p;
    s32 target;
    f32 t;
    f32 w;

    w = an->width;
    target = func_00207500();
    p = &pkt;
    w /= 10.0f;
    n = an->count;
    func_001094F0(p);
    func_00107990(p, &an->col, 0);
    func_001092E0(p, 0);
    func_001094F0(p);
    col = an->col;
    ctrl[0] = pts[0];
    ctrl[1] = pts[0];
    ctrl[2] = pts[1];
    ctrl[3] = pts[2];
    for (i = 0; i < n - 1; i++) {
        t = 0.0f;
        for (j = 0; j < 4; j++) {
            if (i != 0) {
                ab[0] = func_01E01850_b718(&pts[(s16)i - 1], 0, t);
                t += 0.25f;
                r1 = func_01E01850_b718(&pts[(s16)i - 1], 0, t);
                ab[1] = r1;
            } else {
                ab[0] = func_01E01850_b718(ctrl, 0, t);
                t += 0.25f;
                r2 = func_01E01850_b718(ctrl, 0, t);
                ab[1] = r2;
            }
            func_00107990(p, &col, 1);
            x = col.a - (s16)(an->col.a / (n * 3));
            if (x <= 0) {
                col.a = 0;
            } else {
                col.a = x;
            }
            func_00107990(p, &col, 2);
            for (k = 0; k < 4; k++) {
                q[0].x = ab[0].x;
                q[0].y = ab[0].y;
                q[0].z = ab[0].z;
                q[1].x = ab[0].x;
                q[1].y = ab[0].y;
                q[1].z = ab[0].z;
                q[2].x = ab[1].x;
                q[2].y = ab[1].y;
                q[2].z = ab[1].z;
                q[3].x = ab[1].x;
                q[3].y = ab[1].y;
                q[3].z = ab[1].z;
                if (k == 0) {
                    q[0].z += w;
                    q[2].z += w;
                } else if (k == 1) {
                    q[0].z -= w;
                    q[2].z -= w;
                } else if (k == 2) {
                    q[0].x += w;
                    q[2].x += w;
                } else if (k == 3) {
                    q[0].x -= w;
                    q[2].x -= w;
                }
                if (func_00205630(q, 0x70000000, 0, p, &depth) != 0) {
                    func_002075F0(p, target, (u32)depth);
                }
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b718", func_01E020D0_b718);

/* shape b718:01E02510, 134 insns: b019:01E01F60 with its sine table at ctx+0x37C4 */

/* OVL_WARM */

typedef struct {
    u8 pad0[0x37C4];
    u8 tab[1];
} Mgr_b718_01E02510;

typedef struct {
    u8 pad0[8];
    s16 x;
    s16 y;
    s16 z;
    u8 padE[0x1A];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b718_01E02510;

static s32 func_01E02510_b718(Mgr_b718_01E02510 *m, Fx_b718_01E02510 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    func_001076F0(o->col, 0x3F, 0x30, 0x3F);
    if (o->mode == 1) {
        o->f38 = 0;
        o->f3A = func_0019A5C8() % 360;
        o->f34 = 0;
        o->f30 = func_0019A5C8() % 30 - 15;
        o->mode = 2;
    }
    if (o->tick < 10) {
        if (o->col[3] < 0x60) {
            o->col[3] += 9;
        }
    } else if (o->col[3] > 16) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    o->tick++;
    if (o->tick % 2 == 1) {
        if (o->f38 < 18) {
            o->f38++;
        }
    }
    if (o->tick % 3 == 1) {
        if (o->f34 < 7) {
            o->f34++;
        }
    }
    o->x = o->x + 10.0f * func_00108030(m->tab, o->f3A, 0);
    o->y = o->y + 4.0f * func_00108030(m->tab, o->f30, 1);
    o->z = o->z + 10.0f * func_00108030(m->tab, o->f3A, 1);
    return 0;
}

/* shape b718:01E02730, 87 insns: on start 0x38 = 8, random rotation (0x18 -0x2000..0x1FFF, 0x14), variant 0..6; alpha grows
   by 0x50 (below 0xA0) for 2 ticks, then fades by 13 once 0x38 passes 0x14 and by 15 while the game counter at
   0x3260 is below 10; colour (0x80, 0x40, 0); 0x38 grows by 4 */

typedef struct {
    u8 pad0[0x3260];
    s32 count;
} Game_b718_01E02730;

typedef struct {
    u8 pad0[0x14];
    s32 rot14;
    s32 rot18;
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[6];
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
} Fx_b718_01E02730;

static s32 func_01E02730_b718(Game_b718_01E02730 *g, Fx_b718_01E02730 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 8;
        o->rot18 = func_0019A5C8() % 0x4000 - 0x2000;
        o->rot14 = func_0019A5C8() % 0xFFFF;
        o->f34 = func_0019A5C8() % 7;
        o->mode = 2;
    }
    if (o->tick < 2) {
        if (o->col[3] < 0xA0) {
            o->col[3] += 0x50;
        }
    } else {
        if (o->f38 > 0x14) {
            if (o->col[3] > 0xE) {
                o->col[3] -= 13;
            } else {
                o->mode = 0;
            }
        }
        if (g->count < 10) {
            if (o->col[3] > 0x10) {
                o->col[3] -= 15;
            } else {
                o->mode = 0;
            }
        }
    }
    func_001076F0(o->col, 0x80, 0x40, 0);
    o->tick++;
    o->f38 += 4;
    return 0;
}

/* OVL_WARM */

typedef struct {
    u8 pad0000[0x3250];
    f32 x, y, z;
    u8 pad325C[4];
    s32 w3260;
} Mgr_b718_01E02890;

typedef struct {
    s16 x, y, z;
    u8 pad06[0xA];
    s32 w10;
    s32 w14;
    s32 w18;
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 h30;
    s16 h32;
    s16 h34;
    s16 h36;
    s16 h38;
    s16 h3A;
} Obj_b718_01E02890;

static s32 func_01E02890_b718(Mgr_b718_01E02890 *m, Obj_b718_01E02890 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F6160(s32, void *);
    s32 v[4];

    func_001076F0(o->col, 0x20, 0x20, 0);
    if (o->h36 == 1) {
        func_001F6160(func_001F53A0(), v);
        if ((s32)(v[1] / 180.0f) != 0) {
            o->w10 = -0x4000;
        } else {
            o->w10 = -0xC000;
        }
        o->w14 = 0;
        o->w18 = 0x3800;
        o->h34 = 0;
        o->h3A = func_0019A5C8() % 360;
        o->h30 = 90;
        o->h36 = 2;
        o->col[3] = 0;
    }
    if (o->h32 < 10) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 6) {
        o->col[3] -= 5;
    } else {
        o->h36 = 0;
    }
    o->h38 = 50;
    o->h32++;
    o->h30 += (s16)(func_0019A5C8() % 5 + 3);
    if (m->w3260 < 15) {
        if (o->col[3] > 14) {
            o->col[3] -= 13;
        } else {
            o->h36 = 0;
        }
    }
    o->x = m->x;
    o->y = m->y;
    o->z = m->z;
    return 0;
}

/* shape b018:01E02480, 54 insns, 11 copies: step of a fading effect: on state 1 sets its two colours, a random angle and
   state 2; full alpha for the first 5 ticks, then fades by 10 until state 0 */

typedef struct {
    u8 pad0[0x28];
    u8 c0[4];
    u8 c1[4];
    u8 pad30[2];
    s16 t;
    u8 pad34[2];
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b018_01E02480;

static s32 func_01E02A70_b718(void *arg0, Obj_b018_01E02480 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 0x14A;
        func_001076F0(o->c0, 0xC0, 0x70, 0);
        func_001076F0(o->c1, 0x20, 0x10, 0);
        o->ang = func_0019A5C8() % 360;
        o->state = 2;
        o->c1[3] = 0x10;
    }
    if (o->t < 5) {
        o->c0[3] = 0x80;
    } else if (o->c0[3] > 16) {
        o->c0[3] -= 10;
    } else {
        o->state = 0;
    }
    o->t++;
    return 0;
}

/* shape b718:01E02B50, 42 insns: colour (0x40, 0x30, 0); on start 0x38 = 5; alpha 0x30 for 0x4B ticks, then fades by 9
   and stops; 0x6 = 10 each tick */

typedef struct {
    u8 pad0[6];
    s16 f6;
    u8 pad8[0x20];
    u8 col[4];
    u8 pad2C[6];
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f38;
} Fx_b718_01E02B50;

static s32 func_01E02B50_b718(s32 arg0, Fx_b718_01E02B50 *o) {
    func_001076F0(o->col, 0x40, 0x30, 0);
    if (o->mode == 1) {
        o->f38 = 5;
        o->mode = 2;
    }
    if (o->tick < 0x4B) {
        o->col[3] = 0x30;
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->f6 = 10;
    o->tick++;
    return 0;
}

/* shape b718:01E02C00, 108 insns: variant of b018:01E02610 (f38 20): a twinkling sprite: on start pick a random variant, position, angle, spin speed,
   delay and lifetime and colour (0x20,0x10,8); fade in by 0x38 while younger than its lifetime, then fade out by
   10 and stop; spin while running */

typedef struct {
    u8 pad0[6];
    s16 life;
    s16 delay;
    u8 padA[4];
    s16 spin;
    s32 x;
    s32 y;
    s32 z;
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 angle;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
    s16 dir;
} Spark_b718_01E02C00;

static s32 func_01E02C00_b718(s32 arg0, Spark_b718_01E02C00 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 0x14;
        o->kind = func_0019A5C8() % 4;
        o->x = func_0019A5C8() % 0xFFFF;
        o->y = func_0019A5C8() % 0xFFFF;
        o->z = func_0019A5C8() % 0xFFFF;
        func_001076F0(o->col, 0x20, 0x10, 8);
        o->angle = 0;
        o->dir = func_0019A5C8() % 360;
        o->spin = func_0019A5C8() % 16 + 3;
        o->delay = func_0019A5C8() % 10;
        o->life = func_0019A5C8() % 7 + 5;
        o->mode = 2;
    }
    if (o->tick < o->life) {
        if (o->col[3] < 0x71) {
            o->col[3] += 0x38;
        }
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->angle += o->spin;
    }
    o->tick++;
    return 0;
}

/* shape b718:01E02DB0, 97 insns: on start 0x38 = 3, variant 0..3, colour (0x80, 0x40, 0), random rotation,
   random 0x3A, speed 5..21 (0xE), 0x8 0..9, hold 2..7 (0x6); alpha 0x80 during the hold, then fades by 10 and
   stops; 0x30 grows by the speed */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    u8 padA[4];
    s16 speed;
    s32 rot10;
    u8 pad14[4];
    s32 rot18;
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b718_01E02DB0;

static s32 func_01E02DB0_b718(s32 arg0, Fx_b718_01E02DB0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 3;
        o->f34 = func_0019A5C8() % 4;
        func_001076F0(o->col, 0x80, 0x40, 0);
        o->rot18 = func_0019A5C8() % 0xFFFF;
        o->rot10 = func_0019A5C8() % 0xFFFF;
        o->f30 = 0;
        o->f3A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 17 + 5;
        o->f8 = func_0019A5C8() % 10;
        o->hold = func_0019A5C8() % 6 + 2;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    o->f30 += o->speed;
    o->tick++;
    return 0;
}

/* shape b718:01E02F40, 143 insns: an orange flame at the scene's point (ctx+0x320, height 50) with frame 0..3, turning 5 per tick one way or the other by the old f30, f30 0..4 growing 12..31 per tick (+28 after scene count 188 or 195 by direction), f8 0..49, life 8..24: full alpha then down by 32 */

/* OVL_WARM */

typedef struct {
    u8 pad0[0x320];
    f32 x;
    f32 y;
    f32 z;
    u8 pad32C[0x32BE - 0x32C];
    s16 count;
} Ctx_b718_01E02F40;

typedef struct {
    s16 x, y, z;
    s16 life;
    s16 f8;
    u8 padA[4];
    s16 speed;
    u8 pad10[8];
    s32 rot;
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 dir;
} Fx_b718_01E02F40;

static s32 func_01E02F40_b718(Ctx_b718_01E02F40 *g, Fx_b718_01E02F40 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 11;
        o->f34 = func_0019A5C8() % 4;
        func_001076F0(o->col, 0x80, 0x40, 0);
        o->rot = func_0019A5C8() % 360;
        o->dir = o->f30;
        o->f30 = func_0019A5C8() % 5;
        o->speed = func_0019A5C8() % 20 + 12;
        o->f8 = func_0019A5C8() % 50;
        o->life = func_0019A5C8() % 17 + 8;
        o->mode = 2;
    }
    if (o->tick < o->life) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 32) {
        o->col[3] -= 32;
    } else {
        o->mode = 0;
    }
    o->x = g->x;
    o->y = 50;
    o->z = g->z;
    if (o->dir != 0) {
        o->rot += 5;
    } else {
        o->rot -= 5;
    }
    if (o->dir == 0) {
        if (g->count < 188) {
            o->f30 += o->speed;
        } else {
            o->f30 += o->speed + 28;
        }
    }
    if (o->dir == 1) {
        if (g->count < 195) {
            o->f30 += o->speed;
        } else {
            o->f30 += o->speed + 28;
        }
    }
    o->tick++;
    return 0;
}

/* shape b718:01E03180, 150 insns: amber trail head: on start snaps scene point o->kind (ctx+0x2A30) to the tracked point (10 lower) and fills its 10-point trail (ctx+0x2C10); each tick pushes it by h8 along its angle and by hC up, pushes the trail (b718:01E00080), h8 grows 1 and hC sways by 2 x the sine of the model angle - 180; alpha 0x60 for 10 ticks, then ends */

/* OVL_WARM */

typedef struct {
    Vec4f pt[10];
} Trail_b718_01E03180;

typedef struct {
    u8 pad0[0x2A30];
    Vec4f pts[(0x2C10 - 0x2A30) / 16];
    Trail_b718_01E03180 tr[(0x32A8 - 0x2C10) / 0xA0];
    u8 pad[0x32A8 - 0x2C10 - ((0x32A8 - 0x2C10) / 0xA0) * 0xA0];
    s16 id;
    u8 pad32AA[0x37C4 - 0x32AA];
    u8 tab[1];
} Ctx_b718_01E03180;

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 h8;
    u8 padA[2];
    s16 hC;
    u8 padE[0x1A];
    u8 col[4];
    u8 pad2C[4];
    s16 kind;
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f38;
    s16 ang;
} Fx_b718_01E03180;

static s32 func_01E03180_b718(Ctx_b718_01E03180 *g, Fx_b718_01E03180 *o) {
    extern void b718_01E00080(Vec4f *, s32, s32, Vec4f *);
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, Vec4f *);
    extern void func_001F6160(s32, void *);
    extern f32 func_00108030(void *, s32, s32);
    s32 a[4];
    s32 i;
    Vec4f *src;
    Vec4f *dst;
    s32 d;

    if (o->mode == 1) {
        func_001076F0(o->col, 0xA0, 0x80, 8);
        o->hold = 9;
        o->col[3] = 0x80;
        o->ang = func_0019A5C8() % 360;
        o->f38 = 8;
        func_001F5620(func_001F53A0(), g->id, &g->pts[o->kind]);
        g->pts[o->kind].z -= 10.0f;
        src = &g->pts[o->kind];
        dst = g->tr[o->kind].pt;
        for (i = 0; i < 10; i++) {
            dst[i].x = src->x;
            dst[i].y = src->y;
            dst[i].z = src->z;
        }
        o->mode = 2;
    }
    g->pts[o->kind].x += o->h8 * func_00108030(g->tab, o->ang, 0);
    g->pts[o->kind].z += o->hC;
    b718_01E00080(&g->tr[o->kind].pt[9], 10, 0, &g->pts[o->kind]);
    o->h8++;
    func_001F6160(func_001F53A0(), a);
    d = (s16)(2.0f * -func_00108030(g->tab, (s16)(a[1] / 180.0f) - 180, 1));
    o->hC -= d;
    if (o->tick < 10) {
        o->col[3] = 0x60;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* OVL_WARM */

/* shape b718:01E033E0, 141 insns: an orange ember on the scene point (g+0x320/0x328, height 50): on start size 4, frame
   0..3, a random spin, side = the old height, height 0..4, rise 12..31, frame 0..49, life 8..24; alpha 0x80 for its life,
   then down by 32 until it ends; it spins by +-5 by side and rises by its speed (both sides, before scene times 188 / 195
   and after) */

typedef struct {
    u8 pad0[0x320];
    f32 x;
    u8 pad324[4];
    f32 z;
    u8 pad32C[0x2F92];
    s16 time;
} Game_b718_01E033E0;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s16 life;
    s16 frame;
    u8 padA[4];
    s16 rise;
    u8 pad10[8];
    s32 spin;
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 h;
    s16 t;
    s16 f34;
    s16 mode;
    s16 size;
    s16 side;
} Obj_b718_01E033E0;

static s32 func_01E033E0_b718(Game_b718_01E033E0 *g, Obj_b718_01E033E0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->size = 4;
        o->f34 = func_0019A5C8() % 4;
        func_001076F0(o->col, 0x80, 0x40, 0);
        o->spin = func_0019A5C8() % 360;
        o->side = o->h;
        o->h = func_0019A5C8() % 5;
        o->rise = func_0019A5C8() % 20 + 12;
        o->frame = func_0019A5C8() % 50;
        o->life = func_0019A5C8() % 17 + 8;
        o->mode = 2;
    }
    if (o->t < o->life) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 32) {
        o->col[3] -= 32;
    } else {
        o->mode = 0;
    }
    o->x = g->x;
    o->y = 50;
    o->z = g->z;
    if (o->side != 0) {
        o->spin += 5;
    } else {
        o->spin -= 5;
    }
    if (o->side == 0) {
        if (g->time < 188) {
            o->h += o->rise;
        } else {
            o->h += o->rise;
        }
    }
    if (o->side == 1) {
        if (g->time < 195) {
            o->h += o->rise;
        } else {
            o->h += o->rise;
        }
    }
    o->t++;
    return 0;
}

/* shape b718:01E03620, 88 insns: a red rising spark (b192:01E01DA0 family): frame 10, random sub-frame 0..3, turn, rise 12..31, height 0..49,
   full-alpha time 14..33, angle from its old height; then fades by 32 until it ends */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 h8;
    u8 padA[4];
    s16 step;
    u8 pad10[8];
    s32 rot;
    u8 pad1C[0xC];
    u8 c0[4];
    u8 pad2C[4];
    s16 y;
    s16 t;
    s16 sub;
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b718_01E03620;

static s32 func_01E03620_b718(void *arg0, Obj_b718_01E03620 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 0xA;
        o->sub = func_0019A5C8() % 4;
        func_001076F0(o->c0, 0xC0, 0x30, 0x30);
        o->rot = func_0019A5C8() % 360;
        o->ang = o->y;
        o->y = 0;
        o->step = func_0019A5C8() % 20 + 0xC;
        o->h8 = func_0019A5C8() % 50;
        o->hold = func_0019A5C8() % 20 + 0xE;
        o->state = 2;
    }
    if (o->t < o->hold) {
        o->c0[3] = 0x80;
    } else if (o->c0[3] > 0x20) {
        o->c0[3] -= 0x20;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        o->y += o->step;
    }
    o->t++;
    return 0;
}

/* shape b718:01E03780, 115 insns: on start 0x38 = 65, variant 0, colour 0x40 grey, random headings 0x30 and 0x3A; alpha 0x70
   for 10 ticks, then fades by 10 and stops; the variant counts up to 7 every third tick; it drifts (x by 8.0 x the
   cosine of 0x3A, y by 2.0 x the sine of 0x30, z by 8.0 x the sine of 0x3A, game table 0x37C4) */

typedef struct {
    u8 pad0[0x37C4];
    u8 trig[1];
} Game_b718_01E03780;

typedef struct {
    u8 pad0[8];
    s16 x;
    s16 y;
    s16 z;
    u8 padE[0x1A];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b718_01E03780;

static s32 func_01E03780_b718(Game_b718_01E03780 *g, Fx_b718_01E03780 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s16 func_001A22C0(f32);

    if (o->mode == 1) {
        o->f38 = 65;
        o->f34 = 0;
        func_001076F0(o->col, 0x40, 0x40, 0x40);
        o->f30 = func_0019A5C8() % 360;
        o->f3A = func_0019A5C8() % 360;
        o->mode = 2;
    }
    if (o->tick < 10) {
        o->col[3] = 0x70;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    if (o->tick % 3 == 1) {
        if (o->f34 < 7) {
            o->f34++;
        }
    }
    o->tick++;
    o->x = func_001A22C0(o->x + 8.0f * func_00108030(g->trig, o->f3A, 0));
    o->y = func_001A22C0(o->y + 2.0f * func_00108030(g->trig, o->f30, 1));
    o->z = func_001A22C0(o->z + 8.0f * func_00108030(g->trig, o->f3A, 1));
    return 0;
}

/* shape b718:01E03950, 54 insns: variant of b257:01E031C0 (flash): start block as below; alpha held at 0x80
   for the first 5 ticks, then fades out by 12 and stops */

typedef struct {
    u8 pad0[6];
    s16 life;
    u8 pad8[0x20];
    u8 col[4];
    u8 col2[4];
    u8 pad30[2];
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f38;
    s16 dir;
} Flash_b718_01E03950;

static s32 func_01E03950_b718(s32 arg0, Flash_b718_01E03950 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 0x1AE;
        func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
        func_001076F0(o->col2, 0x10, 0x10, 0x10);
        o->dir = func_0019A5C8() % 360;
        o->mode = 2;
        o->col2[3] = 0x10;
    }
    if (o->tick < 5) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 12;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b718:01E03A30, 88 insns: a dark rising spark (b718:01E03620 shape): frame 50, full-alpha time 7..26 */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 h8;
    u8 padA[4];
    s16 step;
    u8 pad10[8];
    s32 rot;
    u8 pad1C[0xC];
    u8 c0[4];
    u8 pad2C[4];
    s16 y;
    s16 t;
    s16 sub;
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b718_01E03A30;

static s32 func_01E03A30_b718(void *arg0, Obj_b718_01E03A30 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 0x32;
        o->sub = func_0019A5C8() % 4;
        func_001076F0(o->c0, 0x30, 0x30, 0x30);
        o->rot = func_0019A5C8() % 360;
        o->ang = o->y;
        o->y = 0;
        o->step = func_0019A5C8() % 20 + 0xC;
        o->h8 = func_0019A5C8() % 50;
        o->hold = func_0019A5C8() % 20 + 7;
        o->state = 2;
    }
    if (o->t < o->hold) {
        o->c0[3] = 0x80;
    } else if (o->c0[3] > 0x20) {
        o->c0[3] -= 0x20;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        o->y += o->step;
    }
    o->t++;
    return 0;
}

/* shape b718:01E03B90, 93 insns: a screen fog: on start sets the scene fog block (0x2A00: 128, 8.0, 4.0, 0.0, position from
   the effect, colour (0, 180.0, 0)); its strength 0x2A28 rises by 0.2 to 1, then falls by 0.1 and ends; the block is
   passed to func_001F6C10 while alive (NULL once ended); it ends at scene counter 1 (0x3260) */

typedef struct {
    u8 pad0[0x2A00];
    f32 f2A00;
    f32 f2A04;
    f32 f2A08;
    f32 f2A0C;
    f32 pos[3];
    u8 pad2A1C[4];
    f32 f2A20;
    f32 f2A24;
    f32 strength;
    u8 pad2A2C[0x3260 - 0x2A2C];
    s32 count;
} Game_b718_01E03B90;

typedef struct {
    s16 x, y, z;
    u8 pad6[0x2A];
    s16 phase;
    u8 pad32[0x4];
    s16 mode;
} Fx_b718_01E03B90;

static s32 func_01E03B90_b718(Game_b718_01E03B90 *g, Fx_b718_01E03B90 *o) {
    extern void func_001F6C10(void *);

    if (o->mode == 1) {
        g->f2A00 = 128.0f;
        g->f2A04 = 8.0f;
        g->f2A08 = 4.0f;
        g->f2A0C = 0.0f;
        g->f2A20 = 0.0f;
        g->f2A24 = 180.0f;
        g->strength = 0.0f;
        g->pos[0] = o->x;
        g->pos[1] = o->y;
        g->pos[2] = o->z;
        o->mode = 2;
        o->phase = 0;
    }
    if (o->phase == 0) {
        if (g->strength < 1.0f) {
            g->strength += 0.2f;
        } else {
            o->phase = 1;
        }
    } else if (!(g->strength <= 0.1f)) {
        g->strength -= 0.1f;
    } else {
        o->mode = 0;
    }
    if (o->mode == 0) {
        func_001F6C10(0);
    } else {
        func_001F6C10(&g->f2A00);
    }
    if (g->count == 1) {
        o->mode = 0;
    }
    return 0;
}

/* shape b718:01E03D10, 47 insns: constant variant of b205:01E01E50 (volume fade by game state): state at 0x3260 limit 0x1F,
   floor 0x30, down 10, up 10, cap 0x80 */

typedef struct {
    u8 pad[0x3260];
    s32 state;
} Game_b718_01E03D10;

typedef struct {
    u8 pad[0x30];
    s16 vol;
    u8 pad32[4];
    s16 mode;
} Fade_b718_01E03D10;

static s32 func_01E03D10_b718(Game_b718_01E03D10 *g, Fade_b718_01E03D10 *o) {
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

static s32 func_01E03DD0_b718(void) {
    f32 a;
    f32 b;

    *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E05600_b718;
    *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E05608_b718;
    func_001F7170(2, 0, (s32)&a, (s32)&b, 0);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b718", func_01E03E20_b718);

/* shape b718:01E04BB0, 72 insns: twin of b046:01E03E20: take the first free slot of the 150-slot pool, clear it, give
   it the scene's colour twice, the scene matrix, the scene's value 0x32BA and the two arguments; returns 1 if a
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
} Slot_b718_01E04BB0;

typedef struct {
    u8 pad[0x2D0];
    u8 m[0x1A8];
    Slot_b718_01E04BB0 s[150];
    u8 pad29F8[0x86C];
    u8 r, g, b, a;
    u8 pad3268[0x52];
    s16 v;
} Pool_b718_01E04BB0;

static s32 func_01E04BB0_b718(Pool_b718_01E04BB0 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b718_01E04BB0 *s = NULL;
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

INCLUDE_ASM("asm/nonmatchings/mod/b718", func_01E04CD0_b718);

INCLUDE_ASM("asm/nonmatchings/mod/b718", func_01E05130_b718);

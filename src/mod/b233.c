#include "common.h"

typedef struct {
    f32 x, y, z, w;
} Vec_b004_01E00B40;

static s32 func_01E00080_b233(Vec_b004_01E00B40 *trail, s32 n, s32 arg2) {
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

static void func_01E00150_b233(Pk_b008_01E00080 *p, Rect_b008_01E00080 *r, s32 mode) {
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

typedef struct {
    f32 x, y, z, w;
} Vec_b018_01E00EE0;


/* static in its module (callers that include this file #define OVL_LOCAL static first) */

static Vec_b018_01E00EE0 func_01E005A0_b233(Vec_b018_01E00EE0 *p, s32 type, f32 t) {
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

INCLUDE_ASM("asm/nonmatchings/mod/b233", func_01E009E0_b233);

/* shape b027:01E02300, 162 insns, 8 copies: a fan of 18 quads (centre at the origin, outer edge on a circle of
   radius data->radius, 20 angle units per step) sent through the caller's packet; same family as b016:01E01190 */

typedef struct {
    f32 x, y, z, w;
} Vec_b027_01E02300;

typedef struct {
    u8 pad00[0x80];
    s32 texture;
    u8 pad84[0x54];
    u8 table[1];
} Obj_b027_01E02300;

typedef struct {
    s16 x, y, z;
    u8 pad06[2];
    s16 dx, dy, dz;
    u8 pad0E[0x1A];
    u8 mode0[4];
    u8 mode1[4];
    u8 pad30[8];
    s16 radius;
    s16 step;
} Data_b027_01E02300;

static void func_01E00E50_b233(Obj_b027_01E02300 *obj, Data_b027_01E02300 *data, void *pkt) {
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    Vec_b027_01E02300 quad[4];
    Vec_b027_01E02300 pos;
    Vec_b027_01E02300 scale;
    f32 matrix[16];
    f32 depth[4];
    s32 rot[4];
    s32 i;
    s16 j;
    s32 a;
    f32 fx;
    f32 fy;
    f32 fz;

    j = 0;
    func_00107990(pkt, data->mode0, 1);
    func_00107990(pkt, data->mode1, 2);
    func_001092E0(pkt, 0);
    func_001094F0(pkt);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    rot[0] += 0x4000;
    fx = data->dx;
    fy = data->dy;
    fz = data->dz;
    fx /= 10.0f;
    fy /= 10.0f;
    fz /= 10.0f;
    pos.x = data->x + fx;
    pos.y = data->y + fy;
    pos.z = data->z + fz;
    func_00108EF0(matrix, &scale, rot, &pos);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    quad[0].x = 0.0f;
    quad[0].z = 0.0f;
    quad[1].x = 0.0f;
    quad[1].z = 0.0f;
    for (i = 0; i < 18; i++) {
        a = data->step + j;
        quad[2].x = data->radius * func_00108030(obj->table, a, 1);
        quad[2].z = data->radius * func_00108030(obj->table, a, 0);
        a = j + (data->step + 20);
        quad[3].x = data->radius * func_00108030(obj->table, a, 1);
        quad[3].z = data->radius * func_00108030(obj->table, a, 0);
        if (func_00205630(quad, 0x70000000, matrix, pkt, depth) != 0) {
            func_00109380(pkt, 1);
            func_002075F0(pkt, obj->texture, 0);
        }
        j += 20;
    }
}

/* shape b218:01E00ED0, 325 insns: b134:01E00820 family: a textured ribbon between two point trails, each segment 4
   spline quads (module curve function, shape b018:01E00EE0), the alpha fading along it; no matrix, far order 0;
   the first segment runs on local copies (each trail's first point doubled) */

typedef struct {
    f32 u, v;
} Uv_b218_01E00ED0;

typedef struct {
    Uv_b218_01E00ED0 st;
    u64 rgba;
    u64 xyz;
} Vtx_b218_01E00ED0;

typedef struct {
    u8 hdr[0x10];
    Vtx_b218_01E00ED0 v[4];
    u8 tail[0x20];
} Pk_b218_01E00ED0;

typedef struct {
    u8 r, g, b, a;
} Col_b218_01E00ED0;

typedef struct {
    u8 pad00[0x88];
    void *texture;
    u8 pad8C[8];
    u8 rect[0x2A];
    s16 mode;
} Obj_b218_01E00ED0;

typedef struct {
    u8 pad00[6];
    s16 n;
    u8 pad08[0x20];
    u8 col[4];
} Rib_b218_01E00ED0;

static void func_01E010E0_b233(Obj_b218_01E00ED0 *o, Rib_b218_01E00ED0 *s, Vec_b018_01E00EE0 *pa, Vec_b018_01E00EE0 *pb) {
    extern s32 func_00109270();
    f32 depth[4];
    Vec_b018_01E00EE0 quad[4];
    Vec_b018_01E00EE0 A[2];
    Vec_b018_01E00EE0 B[2];
    Vec_b018_01E00EE0 a4[4];
    Vec_b018_01E00EE0 b4[4];
    Pk_b218_01E00ED0 pkt __attribute__((aligned(8)));
    Uv_b218_01E00ED0 uv0;
    Uv_b218_01E00ED0 uv1;
    Uv_b218_01E00ED0 uv2;
    Uv_b218_01E00ED0 uv3;
    Col_b218_01E00ED0 col;
    s32 k;
    s32 j;
    s16 n;
    Pk_b218_01E00ED0 *p;
    u8 *ot;
    Vec_b018_01E00EE0 *qa;
    Vec_b018_01E00EE0 *qb;
    f32 t;

    ot = func_00207500();
    n = s->n;
    p = (Pk_b218_01E00ED0 *)(s32)&pkt;
    func_00109270(p, 0, 0);
    func_00107740(&uv0, s->col);
    pkt.v[0].st = uv0;
    func_00107740(&uv1, s->col);
    pkt.v[1].st = uv1;
    func_00107740(&uv2, s->col);
    pkt.v[2].st = uv2;
    func_00107740(&uv3, s->col);
    pkt.v[3].st = uv3;
    func_00108500(p, o->rect, o->mode);
    func_00208700(p, o->texture, 1);
    col = *(Col_b218_01E00ED0 *)s->col;
    a4[0] = pa[0];
    a4[1] = pa[0];
    a4[2] = pa[1];
    a4[3] = pa[2];
    b4[0] = pb[0];
    b4[1] = pb[0];
    b4[2] = pb[1];
    b4[3] = pb[2];
    for (k = 0; k < n - 1; k++) {
        func_00107790(p, &col.r, 1);
        col.a -= (u8)(s->col[3] / n);
        func_00107790(p, &col.r, 2);
        t = 0.0f;
        qa = pa + (k - 1);
        qb = pb + (k - 1);
        for (j = 0; j < 4; j++) {
            if (k != 0) {
                A[0] = func_01E005A0_b233(qa, 0, t);
                B[0] = func_01E005A0_b233(qb, 0, t);
                t += 0.25f;
                A[1] = func_01E005A0_b233(qa, 0, t);
                B[1] = func_01E005A0_b233(qb, 0, t);
            } else {
                A[0] = func_01E005A0_b233(a4, 0, t);
                B[0] = func_01E005A0_b233(b4, 0, t);
                t += 0.25f;
                A[1] = func_01E005A0_b233(a4, 0, t);
                B[1] = func_01E005A0_b233(b4, 0, t);
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
            if (func_00205630((s32)quad, 0x70000000, 0, (s32)p, depth) != 0) {
                func_002075F0((s32)p, (s32)ot, 0);
            }
        }
    }
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

static void func_01E01600_b233(Obj_b134_01E00820 *o, Rib_b134_01E00820 *s, Vec_b018_01E00EE0 *pa, Vec_b018_01E00EE0 *pb) {
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
                A[0] = func_01E005A0_b233(pa, 0, t);
                B[0] = func_01E005A0_b233(pq, 0, t);
                t += 0.25f;
                A[1] = func_01E005A0_b233(pa, 0, t);
                B[1] = func_01E005A0_b233(pq, 0, t);
            } else {
                A[0] = func_01E005A0_b233(a4, 0, t);
                B[0] = func_01E005A0_b233(b4, 0, t);
                t += 0.25f;
                A[1] = func_01E005A0_b233(a4, 0, t);
                B[1] = func_01E005A0_b233(b4, 0, t);
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

/* shape b233:01E01BC0, 166 insns: b069:01E01A70 with the position passed by value: draws 4 copies of a gradient
   quad (colour A on three corners, B on the last), each turned by the effect's rotation; far z. The packet is
   passed in. */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b233_01E01BC0;

typedef struct {
    Rgbaq_b233_01E01BC0 c;
    u64 st;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b233_01E01BC0;

typedef struct {
    s16 count;
    u16 flags;
    s32 pad;
    u64 regs;
    Vtx_b233_01E01BC0 v[4];
    u8 tail[0x20];
} Pkt_b233_01E01BC0;

typedef struct {
    u8 pad00[0x20];
    Vec4f pts[6];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    u8 tex[0x2A];
    s16 page;
    u8 padC0[0x18];
    u8 xD8[1];
} Obj_b233_01E01BC0;

typedef struct {
    u8 pad00[8];
    s16 u, v;
    u8 pad0C[0x1C];
    u8 colB[4];
    u8 colA[4];
    s16 point;
    u8 pad32[8];
    s16 rz;
} Fx_b233_01E01BC0;

static void func_01E01BC0_b233(Obj_b233_01E01BC0 *o, Fx_b233_01E01BC0 *fx, Pkt_b233_01E01BC0 *p, Vec4f pos) {
    extern s32 func_00109270(void *, s32, s32);
    extern Rgbaq_b233_01E01BC0 func_00107740(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00109100(void *, void *, s32, void *);
    Vec4f quad[4];
    Vec4f t;
    Vec4f scale;
    f32 depth[4];
    f32 m[16];
    s32 rot[4];
    s16 i;

    func_00109270(p, 0, 0);
    p->v[0].c = func_00107740(fx->colA);
    p->v[1].c = func_00107740(fx->colA);
    p->v[2].c = func_00107740(fx->colA);
    p->v[3].c = func_00107740(fx->colB);
    func_00108500(p, o->tex, o->page);
    func_00208700(p, o->texture, 1);
    scale.x = 0.05f;
    scale.y = 0.05f;
    scale.z = 0.05f;
    func_00205C40((s32)rot);
    t.x = pos.x;
    t.y = pos.y;
    t.z = pos.z;
    func_00108EF0(m, &scale, rot, &t);
    rot[2] = fx->rz;
    rot[1] = 0;
    rot[0] = 0;
    for (i = 0; i < 4; i++) {
        func_00108D60(quad, fx->u, fx->v, i);
        func_00109100(quad, rot, 2, o->xD8);
        if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
            p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
            func_002075F0(p, o->ot, 0);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b233", func_01E01E60_b233);

INCLUDE_ASM("asm/nonmatchings/mod/b233", func_01E02640_b233);

INCLUDE_ASM("asm/nonmatchings/mod/b233", func_01E02860_b233);

INCLUDE_ASM("asm/nonmatchings/mod/b233", func_01E029C0_b233);

INCLUDE_ASM("asm/nonmatchings/mod/b233", func_01E02B60_b233);

typedef struct {
    u8 pad00[6];
    s16 h6;
    u8 pad08[0x10];
    s32 w18;
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 h30;
    s16 h32;
    s16 h34;
    s16 h36;
    s16 h38;
} Obj_b112_01E017B0;

static s32 func_01E02C50_b233(s32 unused, Obj_b112_01E017B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    func_001076F0(o->col, 0x8F, 0x8F, 0x8F);
    if (o->h36 == 1) {
        o->h38 = func_0019A5C8() % 8 + 3;
        if (o->h30 == 0) {
            o->w18 = -0x2000;
        } else {
            o->w18 = 0x2000;
        }
        o->h6 = o->h30;
        o->h34 = func_0019A5C8() % 7;
    }
    if (o->h32 < 4) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x20;
        }
    } else {
        if (o->col[3] > 20) {
            o->col[3] -= 0x13;
        } else {
            o->h36 = 0;
        }
    }
    o->h32++;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b233", func_01E02D60_b233);

/* shape b233:01E02F10, 52 insns: a blue glow at a random angle: in by 0x1B up to 0xC0 for 10 ticks, then out by 11 and ends */

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
} Glow_b233_01E02F10;

static s32 func_01E02F10_b233(s32 arg0, Glow_b233_01E02F10 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        func_001076F0(o->col, 0x20, 0x20, 0x80);
        o->h6 = 9;
        o->col[3] = 0;
        o->ang = func_0019A5C8() % 360;
        o->f38 = 2;
        o->mode = 2;
    }
    if (o->tick < 10) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x1B;
        }
    } else if (o->col[3] > 12) {
        o->col[3] -= 11;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b233:01E02FE0, 43 insns: constant variant of b018:01E02AC0 (glow): on start colour (0x80, 0x10, 0xF0) and fields;
   alpha 0x60 for the first 0x7 ticks, then fade out by 9 and stop */

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
} Glow_b233_01E02FE0;

static s32 func_01E02FE0_b233(s32 arg0, Glow_b233_01E02FE0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        func_001076F0(o->col, 0x80, 0x10, 0xF0);
        o->life = 9;
        o->col[3] = 0x80;
        o->f38 = 6;
        o->mode = 2;
    }
    if (o->tick < 0x7) {
        o->col[3] = 0x60;
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b233", func_01E03090_b233);

/* shape b233:01E031F0, 56 insns: a grey two-colour glow: both alphas held at 0x80 for 7 ticks, then both fade
   out by 11; stops when the first is gone */

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
} Glow_b233_01E031F0;

static s32 func_01E031F0_b233(s32 arg0, Glow_b233_01E031F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        func_001076F0(o->col2, 0x80, 0x80, 0x80);
        o->life = 9;
        o->col[3] = 0x80;
        o->col2[3] = 0x80;
        o->f38 = 6;
        o->mode = 2;
    }
    if (o->tick < 7) {
        o->col[3] = 0x80;
        o->col2[3] = 0x80;
    } else {
        if (o->col[3] > 0xC) {
            o->col[3] -= 11;
        } else {
            o->mode = 0;
        }
        if (o->col2[3] > 0xC) {
            o->col2[3] -= 11;
        }
    }
    o->tick++;
    return 0;
}

/* shape b233:01E031F0, 56 insns: a grey two-colour glow: both alphas held at 0x80 for 7 ticks, then both fade
   out by 11; stops when the first is gone */

static s32 func_01E032D0_b233(s32 arg0, Glow_b233_01E031F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        func_001076F0(o->col2, 0x80, 0x80, 0x80);
        o->life = 9;
        o->col[3] = 0x80;
        o->col2[3] = 0x80;
        o->f38 = 6;
        o->mode = 2;
    }
    if (o->tick < 7) {
        o->col[3] = 0x80;
        o->col2[3] = 0x80;
    } else {
        if (o->col[3] > 0xC) {
            o->col[3] -= 11;
        } else {
            o->mode = 0;
        }
        if (o->col2[3] > 0xC) {
            o->col2[3] -= 11;
        }
    }
    o->tick++;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b233", func_01E033B0_b233);

/* shape b233:01E03490, 54 insns: variant of b257:01E031C0 (flash): start block as below; alpha grows by 0x60
   for the first 2 ticks, then fades out by 6 and stops */

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
} Flash_b233_01E03490;

static s32 func_01E03490_b233(s32 arg0, Flash_b233_01E03490 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 0xFA;
        func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
        func_001076F0(o->col2, 0x80, 0x20, 0xF0);
        o->dir = func_0019A5C8() % 360;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 2) {
        o->col[3] += 0x60;
    } else if (o->col[3] > 0x7) {
        o->col[3] -= 6;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b233", func_01E03570_b233);

INCLUDE_ASM("asm/nonmatchings/mod/b233", func_01E036D0_b233);

/* shape b233:01E03840, 47 insns: constant variant of b205:01E01E50 (volume fade by game state): state at 0x3930 limit 0x1F,
   floor 0x30, down 10, up 10, cap 0x80 */

typedef struct {
    u8 pad[0x3930];
    s32 state;
} Game_b233_01E03840;

typedef struct {
    u8 pad[0x30];
    s16 vol;
    u8 pad32[4];
    s16 mode;
} Fade_b233_01E03840;

static s32 func_01E03840_b233(Game_b233_01E03840 *g, Fade_b233_01E03840 *o) {
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

/* shape b233:01E03900, 31 insns: b018:01E02DB0 family: func_001F7170(4, 0) with the module's two floats, then ends the object while its tick is under 65; counts the tick */

extern f32 D_01E04E00_b233;
extern f32 D_01E04E08_b233;

typedef struct {
    u8 pad0[0x10];
    s16 v;
} Ctx_b233_01E03900;

typedef struct {
    u8 pad0[0x32];
    s16 h32;
    u8 pad34[2];
    s16 h36;
    u8 pad38[0x1C];
    s16 h54;
    u8 pad56[2];
    s16 h58;
} Obj_b233_01E03900;

static s32 func_01E03900_b233(Ctx_b233_01E03900 *ctx, Obj_b233_01E03900 *o) {
    f32 a;
    f32 b;

    *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E04E00_b233;
    *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E04E08_b233;
    func_001F7170(4, 0, (s32)&a, (s32)&b, 0);
    if (o->h32 < 65) {
        o->h36 = 0;
    }
    o->h32++;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b233", func_01E03980_b233);

INCLUDE_ASM("asm/nonmatchings/mod/b233", func_01E03B90_b233);

INCLUDE_ASM("asm/nonmatchings/mod/b233", func_01E03D60_b233);

/* shape b233:01E04760, 74 insns: twin of b046:01E03E20: take the first free slot of the 150-slot pool, clear it,
   give it the scene's colour twice, the scene matrix, the scene's value 0x396E and 0x3968 and the two arguments; returns 1 if a
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
} Slot_b233_01E04760;

typedef struct {
    u8 pad[0x250];
    u8 m[0xA0];
    Slot_b233_01E04760 s[150];
    u8 pad2870[0x10C4];
    u8 r, g, b, a;
    u8 pad3938[0x30];
    s16 w;
    u8 pad396A[0x4];
    s16 v;
} Pool_b233_01E04760;

static s32 func_01E04760_b233(Pool_b233_01E04760 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b233_01E04760 *s = NULL;
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

INCLUDE_ASM("asm/nonmatchings/mod/b233", func_01E04890_b233);

INCLUDE_ASM("asm/nonmatchings/mod/b233", func_01E04A70_b233);

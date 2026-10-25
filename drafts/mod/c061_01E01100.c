#include "common.h"

/* shape c061:01E01100, 249 insns: draws an arc band of count textured quads (b108:01E00DF0 family): outer and inner
   radius, each quad spanning the band's span, stepping by its step; gouraud from the two colours, texture window
   from the object; blend from flags >> 4, depth mode flags & 0xF (projected, or far after a packet tweak) */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_c061_01E01100;

typedef struct {
    u8 hdr[0x10];
    struct {
        Rgbaq_c061_01E01100 c;
        u64 st;
        u64 xyz;
    } v[4];
    u8 tail[0x20];
} Pkt_c061_01E01100;

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    s16 rect[4];
    u8 pad9C[0x1C];
    s16 count;
    u8 padBA[4];
    s16 mode;
    u8 padC0[0x18];
    u8 xD8[1];
} Obj_c061_01E01100;

typedef struct {
    u8 pad00[0x20];
    Vec4f rot;
    u8 pad30[0x18];
    f32 outer;
    f32 inner;
    u8 pad50[0xA];
    s16 step;
    s16 spn;
    u8 pad5E[2];
    u8 col0[4];
    u8 col1[4];
} Band_c061_01E01100;

static void func_01E01100_c061(Obj_c061_01E01100 *o, Band_c061_01E01100 *s, s32 flags, Vec4f pos) {
    extern Rgbaq_c061_01E01100 func_00107740(void *);
    extern void func_00107990(void *, void *, s32);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern void func_00109380(void *, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f p2;
    Vec4f scale;
    f32 m[16];
    f32 depth[4];
    Pkt_c061_01E01100 pkt;
    s32 t;
    s16 b;
    s16 span;
    Pkt_c061_01E01100 *p;
    s32 k;
    s16 a;
    f32 ro;
    f32 ri;

    p = &pkt;
    span = s->spn;
    a = 0;
    func_00107990(p, s->col0, 2);
    func_00107990(p, s->col1, 1);
    func_00109270(p, 0, 0);
    b = flags >> 4;
    func_00107790(p, s->col0, 0);
    if (b == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((u64)b << 2) | (((u64)0x80 << 32) | 0x40));
    }
    func_00108500(p, o->rect, o->mode);
    func_00208700(p, o->texture, 1);
    p->v[0].c = func_00107740(s->col0);
    p->v[2].c = func_00107740(s->col1);
    p->v[1].c = func_00107740(s->col0);
    p->v[3].c = func_00107740(s->col1);
    scale.x = 0.1f;
    scale.y = 0.1f;
    p2.x = pos.x;
    p2.y = pos.y;
    scale.z = 0.1f;
    p2.z = pos.z;
    func_00108EF0(m, &scale, &s->rot, &p2);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    ro = s->outer;
    ri = s->inner;
    flags &= 0xF;
    for (k = 0; k < o->count; k++) {
        t = a;
        quad[0].x = ro * func_00108030(o->xD8, t, 1);
        quad[0].z = ro * func_00108030(o->xD8, t, 0);
        quad[2].x = ri * func_00108030(o->xD8, t, 1);
        quad[2].z = ri * func_00108030(o->xD8, t, 0);
        t = span + t;
        quad[1].x = ro * func_00108030(o->xD8, t, 1);
        quad[1].z = ro * func_00108030(o->xD8, t, 0);
        quad[3].x = ri * func_00108030(o->xD8, t, 1);
        quad[3].z = ri * func_00108030(o->xD8, t, 0);
        if (flags == 0) {
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                func_002075F0(p, o->ot, (u32)depth[0]);
            }
        } else if (flags == 1 && func_00205630(quad, 0x70000000, m, p, depth) != 0) {
            func_00109380(p, 1);
            func_002075F0(p, o->ot, 0);
        }
        a += s->step;
    }
}

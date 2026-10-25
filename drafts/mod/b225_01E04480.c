#include "common.h"
#define OVL_LOCAL static

/* shape b225:01E04480, 267 insns: b018:01E03760's cone, here of 12 quads 30 apart, hung on a point moved from joint
   B towards joint A (ctx+0x31B0 / ctx+0x320, joint o->h6) by o->hE fiftieths and scaled by size/250: latitudes from
   the tilt + 8 and the tilt, heights 30 x their sines, radius 90 at the tilt (capped at 160) and tilt+14; trig table
   ctx+0x36EC, depth ctx+0x33BC, ot ctx+0x338C; mode 0 only sets up the packet (texture 0x97). */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b225_01E04480;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b225_01E04480;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Rgbaq_b225_01E04480 c;
    struct {
        u64 tc;
        Xyz_b225_01E04480 p;
    } v[4];
} Pkt_b225_01E04480;

typedef struct {
    u8 pad0[0x320];
    Vec4f a[5];
    u8 pad370[0xC];
    void *texture;
    u8 pad380[0x31B0 - 0x380];
    Vec4f b[29];
    u8 pad3380[0xC];
    s32 ot;
    u8 pad3390[0x33BC - 0x3390];
    f32 dep;
    u8 pad33C0[0x36EC - 0x33C0];
    u8 trig[1];
} Ctx_b225_01E04480;

typedef struct {
    u8 pad0[6];
    s16 joint;
    u8 pad8[6];
    s16 step;
    s32 rot[4];
    u8 pad20[8];
    u8 col[4];
    u8 pad2C[4];
    s16 tilt;
    u8 pad32[2];
    s16 page;
    u8 pad36[2];
    s16 size;
    s16 ang;
} Fan_b225_01E04480;

static void func_01E04480_b225(Ctx_b225_01E04480 *c, Fan_b225_01E04480 *o, Pkt_b225_01E04480 *p, s32 mode) {
    extern void func_00106080(void *, s32, s16, void *);
    extern void func_01E00080_b225();
    extern Rgbaq_b225_01E04480 func_00107740(void *);
    extern void func_00106DD0(void *, f32, f32, f32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f pos;
    Vec4f sc;
    f32 m[16];
    u8 td[0x18];
    s32 k;
    s32 j;
    s16 tl;
    s16 a;
    s16 t;
    f32 r0;
    f32 r1;
    f32 sn;
    f32 cs;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 s;
    s32 st;

    if (mode == 0) {
        func_00106080(td, 0x97, o->page, td);
        p->count = 0x24;
        p->tag = 9;
        p->regs = ((u64)4 << 32) | 0x24242421;
        p->pad = 0;
        p->count |= 0x800;
        func_002086D0(p, ((u64)0x80 << 32) | 0x48);
        p->c.q = 0.0f;
        p->v[0].p.f = 0;
        p->v[1].p.f = 0;
        p->v[2].p.f = 0;
        p->v[3].p.f = 0;
        p->c = func_00107740(o->col);
        func_01E00080_b225(p, td, 0);
        func_00208700(p, c->texture, 1);
    } else {
    st = o->step;
    dx = (c->a[o->joint].x - c->b[o->joint].x) / 50.0f;
    dy = (c->a[o->joint].y - c->b[o->joint].y) / 50.0f;
    dz = (c->a[o->joint].z - c->b[o->joint].z) / 50.0f;
    pos.x = c->b[o->joint].x;
    pos.y = c->b[o->joint].y;
    pos.z = c->b[o->joint].z;
    pos.x += st * dx;
    pos.y += st * dy;
    pos.z += st * dz;
    s = o->size;
    s /= 250.0f;
    func_00106DD0(&sc, s, s, s);
    func_00108EF0(m, &sc, o->rot, &pos);
    for (j = 0; j < 1; j++) {
        tl = o->tilt;
        quad[0].y = 30.0f * func_00108030(c->trig, tl + 8, 0);
        quad[1].y = quad[0].y;
        quad[2].y = 30.0f * func_00108030(c->trig, o->tilt, 0);
        quad[3].y = quad[2].y;
        tl = (s16)tl > 0xA0 ? 0xA0 : tl;
        r0 = 90.0f * func_00108030(c->trig, tl, 1);
        r1 = 90.0f * func_00108030(c->trig, tl + 14, 1);
        a = 0;
        for (k = 0; k < 12; k++) {
            t = o->ang + a;
            sn = func_00108030(c->trig, t, 1);
            cs = func_00108030(c->trig, t, 0);
            quad[2].x = sn * r1;
            quad[2].z = cs * r1;
            quad[0].x = r0 * func_00108030(c->trig, t, 1);
            quad[0].z = r0 * func_00108030(c->trig, t, 0);
            t = o->ang + 30 + a;
            sn = func_00108030(c->trig, t, 1);
            cs = func_00108030(c->trig, t, 0);
            quad[3].x = sn * r1;
            quad[3].z = cs * r1;
            quad[1].x = sn * r0;
            quad[1].z = cs * r0;
            if (func_00205630(quad, 0x70000000, m, p, &c->dep) != 0) {
                func_002075F0(p, c->ot, (u32)c->dep);
            }
            a += 30;
        }
    }
    }
}

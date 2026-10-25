#include "common.h"

/* shape b709:01E055C0, 267 insns: b018:01E03760's cone of quads: mode 0 only sets up the packet (texture 0x97 at page
   0x34, flat colour, texture corners by the module helper at 0x1E00150, shape b008:01E00080); otherwise it sits
   between the scene's point tables 0x31B0 and 0x320 (index 0x6, step 0xE / 50), scaled by size / 250, and draws 12
   quads 30 apart: heights 30 x sines of tilt and tilt+8, radii 90 x cosines of tilt (capped at 160) and tilt+14 */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b709_01E055C0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b709_01E055C0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Rgbaq_b709_01E055C0 c;
    struct {
        u64 tc;
        Xyz_b709_01E055C0 p;
    } v[4];
} Pkt_b709_01E055C0;

typedef struct {
    u8 pad0[0x320];
    Vec4f ta[5];
    u8 pad370[0xC];
    void *texture;
    u8 pad380[0x31B0 - 0x380];
    Vec4f tb[0x1B];
    u8 pad3360[0xC];
    s32 ot;
    u8 pad3370[0x24];
    f32 dep;
    u8 pad3398[0x36C4 - 0x3398];
    u8 trig[1];
} Ctx_b709_01E055C0;

typedef struct {
    u8 pad0[6];
    s16 idx;
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
} Fan_b709_01E055C0;

static void func_01E055C0_b709(Ctx_b709_01E055C0 *c, Fan_b709_01E055C0 *o, Pkt_b709_01E055C0 *p, s32 mode) {
    extern void func_00106080(void *, s32, s16, void *);
    extern Rgbaq_b709_01E055C0 func_00107740(void *);
    extern void func_00106DD0(void *, f32, f32, f32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    f32 v[4];
    Vec4f scale;
    f32 m[16];
    u8 td[0x18];
    s32 k;
    s32 j;
    s16 tl;
    s32 t2;
    s16 a;
    s16 t;
    f32 r0;
    f32 r1;
    f32 sn;
    f32 cs;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 st;
    f32 sc;

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
        func_01E00150_b709((Pk_b008_01E00080 *)p, (Rect_b008_01E00080 *)td, 0);
        func_00208700(p, c->texture, 1);
    } else {
    dx = (c->ta[o->idx].x - c->tb[o->idx].x) / 50.0f;
    dy = (c->ta[o->idx].y - c->tb[o->idx].y) / 50.0f;
    dz = (c->ta[o->idx].z - c->tb[o->idx].z) / 50.0f;
    st = o->step;
    v[0] = c->tb[o->idx].x;
    v[1] = c->tb[o->idx].y;
    v[2] = c->tb[o->idx].z;
    v[0] += st * dx;
    v[1] += st * dy;
    v[2] += st * dz;
    sc = o->size;
    sc /= 250.0f;
    func_00106DD0(&scale, sc, sc, sc);
    func_00108EF0(m, &scale, o->rot, v);
    for (j = 0; j < 1; j++) {
        tl = o->tilt;
        quad[0].y = 30.0f * func_00108030(c->trig, o->tilt, 0);
        quad[1].y = quad[0].y;
        quad[2].y = 30.0f * func_00108030(c->trig, o->tilt + 8, 0);
        quad[3].y = quad[2].y;
        if (tl > 0xA0) {
            tl = 0xA0;
        }
        r0 = 90.0f * func_00108030(c->trig, tl, 1);
        t2 = tl + 14;
        r1 = 90.0f * func_00108030(c->trig, t2, 1);
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

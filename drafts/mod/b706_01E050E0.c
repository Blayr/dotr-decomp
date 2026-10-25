#include "common.h"

/* shape b706:01E050E0, 318 insns: ShFx_Lap4p, n four-point laps (0x50 bytes each): project the four corners, scroll
   the texture by age * f14 / f18 (wrapped to 0..1), draw one perspective-correct textured quad (texture 5:b8) in the
   lap's colour, alpha faded in over the first 8 frames unless flag 0x40; flag 0x80 puts it on the far plane, else it
   sorts by the mean depth. The s coordinate uses the corner loop's final counter (4 and 5) */

typedef struct {
    u8 r, g, b, a;
    f32 q;
    f32 s;
    f32 t;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b706_01E050E0;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b706_01E050E0 v[4];
} Pkt_b706_01E050E0;

typedef struct {
    f32 x, y, z;
} P3_b706_01E050E0;

typedef struct {
    u8 life;
    u8 pad1;
    u8 max;
    u8 pad3;
    u8 flags;
    u8 pad5[3];
    u8 tex;
    u8 pad9[3];
    f32 tw;
    u8 pad10[4];
    f32 su;
    f32 sv;
    u8 b, g, r, a;
    P3_b706_01E050E0 pts[4];
} Lap_b706_01E050E0;

static s32 func_01E050E0_b706(void *arg0, s32 ot, s32 n) {
    extern s32 func_00101AF0(void *);
    extern void *func_00202BF0(s32, s32);
    extern void func_0020EB40(void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 m[16];
    Vec4f v;
    u64 xyz[4];
    f32 depth[4];
    Pkt_b706_01E050E0 pk;
    Lap_b706_01E050E0 *e;
    s32 i;
    s32 k;
    void *tex;
    s32 age;
    u8 a;
    f32 u0;
    f32 v0;
    f32 tw;
    f32 s0;
    f32 s1;
    f32 z;

    e = arg0;
    for (i = 0; i < n; i++) {
        if (i != 0) {
            e = (Lap_b706_01E050E0 *)((u8 *)e + 0x50);
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        tex = func_00202BF0(5, e->tex);
        func_0020EB40(m);
        for (k = 0; k < 4; k++) {
            v.x = e->pts[k].x;
            v.y = e->pts[k].y;
            v.z = e->pts[k].z;
            func_00205440(&v, m, &xyz[k], &depth[k]);
        }
        age = e->max - e->life;
        u0 = e->su * age;
        tw = e->tw;
        if (u0 > 1.0f) {
            u0 -= (s32)u0;
        }
        v0 = e->sv * age;
        if (v0 > 1.0f) {
            v0 -= (s32)v0;
        }
        ((Pkt_b706_01E050E0 *)(s32)&pk)->count = 0x34;
        ((Pkt_b706_01E050E0 *)(s32)&pk)->tag = 0xC;
        s0 = u0 + tw * k;
        ((Pkt_b706_01E050E0 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Pkt_b706_01E050E0 *)(s32)&pk)->pad = 0;
        s1 = u0 + tw * (k + 1);
        pk.v[0].q = 1.0f / depth[0];
        pk.v[1].q = 1.0f / depth[1];
        pk.v[2].q = 1.0f / depth[2];
        pk.v[3].q = 1.0f / depth[3];
        pk.v[0].s = s0 / depth[0];
        pk.v[0].t = (1.0f + v0) / depth[0];
        pk.v[1].s = s1 / depth[1];
        pk.v[1].t = (1.0f + v0) / depth[1];
        pk.v[2].s = s0 / depth[2];
        pk.v[2].t = v0 / depth[2];
        pk.v[3].s = s1 / depth[3];
        pk.v[3].t = v0 / depth[3];
        *(u64 *)&pk.v[0].x = xyz[0];
        *(u64 *)&pk.v[1].x = xyz[1];
        *(u64 *)&pk.v[2].x = xyz[2];
        *(u64 *)&pk.v[3].x = xyz[3];
        func_002086D0(&pk, 0x48);
        if (!(e->flags & 0x40) && e->life < 8) {
            a = (e->a >> 3) * e->life;
        } else {
            a = e->a;
        }
        pk.v[0].r = pk.v[1].r = pk.v[2].r = pk.v[3].r = e->r;
        pk.v[0].g = pk.v[1].g = pk.v[2].g = pk.v[3].g = e->g;
        pk.v[0].b = pk.v[1].b = pk.v[2].b = pk.v[3].b = e->b;
        pk.v[0].a = pk.v[1].a = pk.v[2].a = pk.v[3].a = a;
        pk.v[0].f = pk.v[1].f = pk.v[2].f = pk.v[3].f = 0;
        func_00208700(&pk, tex, 1);
        if (e->flags & 0x80) {
            pk.v[0].z = pk.v[1].z = pk.v[2].z = pk.v[3].z = 0xFFFFFE;
            z = 0.0f;
        } else {
            z = (u32)((depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f);
        }
        func_002075F0(&pk, ot, (u32)z);
    }
    return 1;
}

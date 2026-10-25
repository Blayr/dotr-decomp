#include "common.h"

/* shape b205:01E02D10, 289 insns, 1 copy: B205KPOINT_RAIN_2: a fan of quads along a point trail (n = o->n points,
   two at a time): per segment 14 steps of 10 degrees from -70, each drawn 4 times nudged by 0.3 in +z/-z/+x/-x,
   radius from the owner's x, height from its z, alpha fading by col.a / n */

typedef struct Rgba_b205_01E02D10 {
    u8 r, g, b, a;
} Rgba_b205_01E02D10;

typedef struct Fx_b205_01E02D10 {
    u8 pad0[6];
    s16 n;
    u8 pad8[0x20];
    Rgba_b205_01E02D10 col;
} Fx_b205_01E02D10;

typedef struct Own_b205_01E02D10 {
    f32 x;
    f32 y;
    f32 z;
    u8 padC[0xCC];
    u8 trig[1];
} Own_b205_01E02D10;

static void func_01E02D10_b205(Own_b205_01E02D10 *g, Fx_b205_01E02D10 *o, Vec4f *pa, Vec4f *pb) {
    extern void func_001092E0();
    extern void func_001094F0();
    extern void func_00107990();
    extern f32 func_00108030();
    extern void func_00107070();
    extern s32 func_00205630();
    extern void func_002075F0();
    Vec4f q[4];
    Vec4f d;
    Vec4f e;
    f32 depth[4];
    u8 pk[0x90] __attribute__((aligned(16)));
    Rgba_b205_01E02D10 col;
    u8 *p;
    s32 ot;
    s16 n;
    s32 cnt;
    s32 last;
    s32 k;
    s32 m;
    s32 j;
    s16 ang;
    s16 a;
    f32 t;
    f32 r;
    f32 h;
    f32 dy;
    f32 dz;
    f32 lift;

    ot = (s32)func_00207500();
    t = 0.0f;
    p = pk;
    n = o->n;
    func_001092E0(p, 0);
    func_001094F0(p);
    cnt = n;
    k = 0;
    col = o->col;
    d = *pa;
    e = *pb;
    last = cnt - 1;
    d.x -= e.x;
    d.y -= e.y;
    d.z -= e.z;
    d.x = g->x;
    d.y = -d.y;
    d.z = g->z;
    dz = d.z;
    dy = d.y;
    lift = 0.6f * dz;
    for (; k < last; k++) {
        func_00107990(p, &col, 1);
        a = 0;
        col.a -= o->col.a / cnt;
        func_00107990(p, &col, 2);
        ang = -70;
        for (m = 2; m < 16; m++) {
            r = d.x * func_00108030(g->trig, ang, 0);
            h = dz * func_00108030(g->trig, ang, 1) - lift;
            for (j = 0; j < 4; j++) {
                q[0].x = pa[k].x;
                q[0].y = pa[k].y;
                q[0].z = pa[k].z;
                q[1].x = pa[k].x;
                q[1].y = pa[k].y;
                q[1].z = pa[k].z;
                q[2].x = pa[k + 1].x;
                q[2].y = pa[k + 1].y;
                q[2].z = pa[k + 1].z;
                q[3].x = pa[k + 1].x;
                q[3].y = pa[k + 1].y;
                q[3].z = pa[k + 1].z;
                func_00107070(q, 0, r);
                func_00107070(q, 2, h);
                func_00107070(q, 1, dy);
                if (j == 0) {
                    q[0].z += 0.3f;
                    q[2].z += 0.3f;
                } else if (j == 1) {
                    q[0].z -= 0.3f;
                    q[2].z -= 0.3f;
                } else if (j == 2) {
                    q[0].x += 0.3f;
                    q[2].x += 0.3f;
                } else if (j == 3) {
                    q[0].x -= 0.3f;
                    q[2].x -= 0.3f;
                }
                if (func_00205630(q, 0x70000000, 0, p, depth)) {
                    func_002075F0(p, ot, func_001A23B0(depth[0]));
                }
                a += 30;
            }
            ang += 10;
        }
        t += 1.0f;
    }
}

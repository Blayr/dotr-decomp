#include "common.h"

/* shape b397:01E02D10, 273 insns, 1 copy (B397KPOINT_RAIN_2): draws a rain of thin quads between consecutive trail
   points: per segment the colour's alpha drops by alpha / count, then 18 turns (from -90, 10 apart) of 4 slim quads
   nudged 0.2 apart, rotated by the scene sine table (ctx+0xD8) */

typedef struct {
    u8 pad0[6];
    s16 count;
    u8 pad8[0x20];
    u8 col[4];
} Obj_b397_01E02D10;

typedef struct {
    u8 r, g, b, a;
} Col_b397_01E02D10;

typedef struct {
    u8 b[0x90];
} Pkt_b397_01E02D10;

static void func_01E02D10_b397(u8 *g, Obj_b397_01E02D10 *o, Vec4f *pts, Vec4f *base) {
    extern s32 func_00207500(void);
    extern void func_001092E0(void *, s32);
    extern void func_001094F0(void *);
    extern void func_00107990(void *, void *, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern void func_00107070(void *, s32, f32);
    extern s32 func_00205630(void *, s32, void *, void *, void *);
    extern void func_002075F0(void *, s32, s32);
    u8 depth[0x10];
    Vec4f q[4];
    Vec4f d;
    Vec4f b;
    Pkt_b397_01E02D10 pk;
    Col_b397_01E02D10 col;
    s32 k;
    s32 j;
    s32 last;
    s32 n;
    Pkt_b397_01E02D10 *p;
    s32 ot;
    s16 x;
    s16 ang;
    s32 m;
    f32 cnt;
    f32 r;
    f32 h;
    f32 z;

    ot = func_00207500();
    x = o->count;
    p = &pk;
    cnt = 0.0f;
    func_001092E0(p, 0);
    func_001094F0(p);
    n = x;
    k = 0;
    col = *(Col_b397_01E02D10 *)o->col;
    d = pts[0];
    last = n - 1;
    b = *base;
    d.x -= b.x;
    d.y -= b.y;
    d.z -= b.z;
    d.x = ((Vec4f *)g)->x;
    d.y = -d.y;
    d.z = ((Vec4f *)g)->z;
    z = d.z;
    for (; k < last; k++) {
        func_00107990(p, &col, 1);
        x = 0;
        col.a -= (u8)(o->col[3] / n);
        func_00107990(p, &col, 2);
        ang = -90;
        for (j = 0; j < 18; j++) {
            r = d.x * func_00108030(g + 0xD8, ang, 0);
            h = z * func_00108030(g + 0xD8, ang, 1) - z;
            for (m = 0; m < 4; m++) {
                q[0].x = pts->x;
                q[0].y = pts->y;
                q[0].z = pts->z;
                q[1].x = pts->x;
                q[1].y = pts->y;
                q[1].z = pts->z;
                q[2].x = pts[1].x;
                q[2].y = pts[1].y;
                q[2].z = pts[1].z;
                q[3].x = pts[1].x;
                q[3].y = pts[1].y;
                q[3].z = pts[1].z;
                func_00107070(q, 0, r);
                func_00107070(q, 2, h);
                if (m == 0) {
                    q[0].z += 0.2f;
                    q[2].z += 0.2f;
                } else if (m == 1) {
                    q[0].z -= 0.2f;
                    q[2].z -= 0.2f;
                } else if (m == 2) {
                    q[0].x += 0.2f;
                    q[2].x += 0.2f;
                } else if (m == 3) {
                    q[0].x -= 0.2f;
                    q[2].x -= 0.2f;
                }
                if (func_00205630(q, 0x70000000, NULL, p, depth) != 0) {
                    func_002075F0(p, ot, 0);
                }
                x += 30;
            }
            ang += 10;
        }
        pts++;
        cnt += 1.0f;
    }
}

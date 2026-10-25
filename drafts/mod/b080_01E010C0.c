#include "common.h"

/* shape b080:01E010C0 (KPOINT_RAIN_2), 278 insns, 1 copy: draws a fading tube along a point path: for each of the
   n - 1 links the colour loses alpha / n, then a fan of seven spokes (-90..90 by 30) is spun around the link in
   four slightly shifted copies (+-0.2 in z, then in x) and sent */

typedef struct {
    u8 r, g, b, a;
} Col_b080_01E010C0;

typedef struct {
    f32 x, y, z, w;
} V4_b080_01E010C0;

typedef struct {
    f32 x0;
    f32 x4;
    f32 x8;
    u8 padC[0xCC];
    u8 sin[1];
} Scene_b080_01E010C0;

typedef struct {
    u8 pad0[6];
    s16 n;
    u8 pad8[0x20];
    Col_b080_01E010C0 col;
} Fx_b080_01E010C0;

static void func_01E010C0_b080(Scene_b080_01E010C0 *g, Fx_b080_01E010C0 *o, V4_b080_01E010C0 *pos, V4_b080_01E010C0 *dir) {
    extern void func_001092E0(void *, s32);
    extern void func_001094F0(void *);
    extern void func_00107990(void *, void *, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern void func_00107070(void *, s32, f32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    s32 ot;
    s32 n;
    s32 k;
    s32 last;
    s32 j;
    s32 i;
    s16 z;
    s16 ang;
    f32 t;
    f32 sx;
    f32 sz;
    f32 ry;
    f32 rz;
    Col_b080_01E010C0 col;
    u8 pk[0x90];
    V4_b080_01E010C0 a;
    V4_b080_01E010C0 b;
    V4_b080_01E010C0 q[4];
    f32 depth;

    ot = (s32)func_00207500();
    z = o->n;
    t = 0.0f;
    func_001092E0(pk, 0);
    func_001094F0(pk);
    n = z;
    k = 0;
    col = o->col;
    a = *pos;
    b = *dir;
    last = n - 1;
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    a.x = g->x0;
    a.y = -a.y;
    a.z = g->x8;
    ry = a.y;
    rz = a.z;
    for (; k < last; k++) {
        func_00107990(pk, &col, 1);
        z = 0;
        col.a -= (u8)(o->col.a / n);
        func_00107990(pk, &col, 2);
        ang = -90;
        for (j = 0; j < 7; j++) {
            sx = a.x * func_00108030(g->sin, ang, 0);
            sz = rz * func_00108030(g->sin, ang, 1);
            for (i = 0; i < 4; i++) {
                q[0].x = pos->x;
                q[0].y = pos->y;
                q[0].z = pos->z;
                q[1].x = pos->x;
                q[1].y = pos->y;
                q[1].z = pos->z;
                q[2].x = pos[1].x;
                q[2].y = pos[1].y;
                q[2].z = pos[1].z;
                q[3].x = pos[1].x;
                q[3].y = pos[1].y;
                q[3].z = pos[1].z;
                func_00107070(q, 0, sx);
                func_00107070(q, 2, sz);
                func_00107070(q, 1, ry);
                if (i == 0) {
                    q[0].z += 0.2f;
                    q[2].z += 0.2f;
                } else if (i == 1) {
                    q[0].z -= 0.2f;
                    q[2].z -= 0.2f;
                } else if (i == 2) {
                    q[0].x += 0.2f;
                    q[2].x += 0.2f;
                } else if (i == 3) {
                    q[0].x -= 0.2f;
                    q[2].x -= 0.2f;
                }
                if (func_00205630(q, 0x70000000, NULL, pk, &depth) != 0) {
                    func_002075F0(pk, ot, 0);
                }
                z += 30;
            }
            ang += 30;
        }
        pos++;
        t += 1.0f;
    }
}

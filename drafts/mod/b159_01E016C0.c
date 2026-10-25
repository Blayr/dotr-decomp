#include "common.h"

/* shape b159:01E016C0, 282 insns, 1 copy (B159PAINT_RAIN4): draws a widening tube along the scene's trail points
   (ctx+0x3A60): per segment the colour's alpha drops by alpha / count, then 12 quads around (30 apart in the sine
   table at ctx+0x3B68) from radius r at one point to r + 0.8 at the next; r grows 1 per segment */

typedef struct {
    u8 pad0[0x28];
    u8 col[4];
    u8 pad2C[6];
    s16 count;
} Obj_b159_01E016C0;

typedef struct {
    u8 r, g, b, a;
} Col_b159_01E016C0;

typedef struct {
    u8 b[0x90];
} Pkt_b159_01E016C0;

static void func_01E016C0_b159(u8 *g, Obj_b159_01E016C0 *o) {
    extern s32 func_00207500(void);
    extern void func_001092E0(void *, s32);
    extern void func_001094F0(void *);
    extern void func_00107990(void *, void *, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern void func_00109380(void *, s32);
    extern s32 func_00205630(void *, s32, void *, void *, void *);
    extern void func_002075F0(void *, s32, s32);
    u8 depth[0x10];
    Vec4f q[4];
    Pkt_b159_01E016C0 pk;
    Col_b159_01E016C0 col;
    s32 k;
    s32 ot;
    s32 last;
    s32 n;
    Pkt_b159_01E016C0 *p;
    Vec4f *pt;
    s16 a;
    s16 b;
    s16 m;
    f32 r;

    ot = func_00207500();
    r = 0.0f;
    m = o->count;
    p = &pk;
    func_001092E0(p, 0);
    func_001094F0(p);
    n = m;
    k = 0;
    pt = (Vec4f *)g;
    col = *(Col_b159_01E016C0 *)o->col;
    last = n - 1;
    for (; k < last; k++) {
        a = 0;
        func_00107990(p, &col, 1);
        col.a -= (u8)(o->col[3] / n);
        func_00107990(p, &col, 2);
        for (m = 0; m < 12; m++) {
            q[0].x = pt[0x3A6].x;
            q[0].y = pt[0x3A6].y;
            q[0].z = pt[0x3A6].z;
            q[1].x = pt[0x3A6].x;
            q[1].y = pt[0x3A6].y;
            q[1].z = pt[0x3A6].z;
            q[0].y += r * func_00108030(g + 0x3B68, a, 1);
            q[0].x += r * func_00108030(g + 0x3B68, a, 0);
            b = a + 30;
            q[0].z += r * func_00108030(g + 0x3B68, a, 1);
            q[1].y += r * func_00108030(g + 0x3B68, b, 1);
            q[1].x += r * func_00108030(g + 0x3B68, b, 0);
            q[1].z += r * func_00108030(g + 0x3B68, b, 1);
            q[2].x = pt[0x3A7].x;
            q[2].y = pt[0x3A7].y;
            q[2].z = pt[0x3A7].z;
            q[3].x = pt[0x3A7].x;
            q[3].y = pt[0x3A7].y;
            q[3].z = pt[0x3A7].z;
            q[2].y += (r + 0.8f) * func_00108030(g + 0x3B68, a, 1);
            q[2].x += (r + 0.8f) * func_00108030(g + 0x3B68, a, 0);
            q[2].z += (r + 0.8f) * func_00108030(g + 0x3B68, a, 1);
            q[3].y += (r + 0.8f) * func_00108030(g + 0x3B68, b, 1);
            q[3].x += (r + 0.8f) * func_00108030(g + 0x3B68, b, 0);
            q[3].z += (r + 0.8f) * func_00108030(g + 0x3B68, b, 1);
            if (func_00205630(q, 0x70000000, NULL, p, depth) != 0) {
                func_00109380(p, 1);
                func_002075F0(p, ot, 0);
            }
            a += 30;
        }
        pt++;
        r += 1.0f;
    }
}

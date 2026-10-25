#include "common.h"

/* shape b004:01E013F0, 282 insns: rain of quads between successive scene points: for each pair of points 18 quads
   swept around by 20 degrees on the sine table (ctx+0x34E0), radius 2.0 growing 0.3 per pair, the far edge 0.3 wider;
   the colour's alpha falls by alpha/n per pair */

typedef struct {
    f32 x, y, z, w;
} Pt_b004_01E013F0;

typedef struct {
    u8 pad0[0x3300];
    Pt_b004_01E013F0 pts[30];
    u8 pad34E0[4];
} Ctx_b004_01E013F0;

typedef struct {
    u8 pad0[0x28];
    u8 col[4];
    u8 pad2C[6];
    s16 n;
} Obj_b004_01E013F0;

static void func_01E013F0_b004(Ctx_b004_01E013F0 *g, Obj_b004_01E013F0 *o) {
    extern s32 func_00205630();
    extern void func_002075F0();
    Ctx_b004_01E013F0 *c;
    f32 q[4][4];
    u8 prim[0x90];
    u8 col[4];
    f32 out[4];
    f32 r;
    s32 ot;
    s32 n;
    s32 i;
    s32 m;
    s32 j;
    s16 ang;
    s16 ang2;

    ot = (s32)func_00207500();
    n = o->n;
    r = 2.0f;
    func_001092E0(prim, 0);
    func_001094F0(prim);
    c = g;
    col[0] = o->col[0];
    col[1] = o->col[1];
    col[2] = o->col[2];
    col[3] = o->col[3];
    m = n - 1;
    for (i = 0; i < m; i++) {
        ang = 0;
        func_00107990(prim, col, 1);
        col[3] -= (u8)(o->col[3] / n);
        func_00107990(prim, col, 2);
        for (j = 0; j < 18; j++) {
            q[0][0] = c->pts[0].x;
            q[0][1] = c->pts[0].y;
            q[0][2] = c->pts[0].z;
            q[1][0] = c->pts[0].x;
            q[1][1] = c->pts[0].y;
            q[1][2] = c->pts[0].z;
            q[0][1] += r * func_00108030((s32)((u8 *)g + 0x34E0), ang, 1);
            q[0][0] += r * func_00108030((s32)((u8 *)g + 0x34E0), ang, 0);
            q[0][2] += r * func_00108030((s32)((u8 *)g + 0x34E0), ang, 1);
            ang2 = ang + 20;
            q[1][1] += r * func_00108030((s32)((u8 *)g + 0x34E0), ang2, 1);
            q[1][0] += r * func_00108030((s32)((u8 *)g + 0x34E0), ang2, 0);
            q[1][2] += r * func_00108030((s32)((u8 *)g + 0x34E0), ang2, 1);
            q[2][0] = c->pts[1].x;
            q[2][1] = c->pts[1].y;
            q[2][2] = c->pts[1].z;
            q[3][0] = c->pts[1].x;
            q[3][1] = c->pts[1].y;
            q[3][2] = c->pts[1].z;
            q[2][1] += (r + 0.3f) * func_00108030((s32)((u8 *)g + 0x34E0), ang, 1);
            q[2][0] += (r + 0.3f) * func_00108030((s32)((u8 *)g + 0x34E0), ang, 0);
            q[2][2] += (r + 0.3f) * func_00108030((s32)((u8 *)g + 0x34E0), ang, 1);
            q[3][1] += (r + 0.3f) * func_00108030((s32)((u8 *)g + 0x34E0), ang2, 1);
            q[3][0] += (r + 0.3f) * func_00108030((s32)((u8 *)g + 0x34E0), ang2, 0);
            q[3][2] += (r + 0.3f) * func_00108030((s32)((u8 *)g + 0x34E0), ang2, 1);
            if (func_00205630(q, 0x70000000, 0, prim, out) != 0) {
                func_00109380(prim, 1);
                func_002075F0(prim, ot, 0);
            }
            ang += 20;
        }
        c = (Ctx_b004_01E013F0 *)((u8 *)c + 0x10);
        r += 0.3f;
    }
}

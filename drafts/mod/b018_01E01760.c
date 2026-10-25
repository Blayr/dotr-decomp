#include "common.h"

/* shape b018:01E01760, 281 insns, 7 copies: KPOINT_RAIN_1_1: draws a ribbon between two point trails (pathA/pathB, n points each)
   as 4 quads per segment along a spline (the module's spline b018:01E00EE0), alpha fading along the ribbon. */

typedef struct Obj_b018_01E01760 {
    u8 pad0[6];
    s32 n;
    u8 pad8[0x20];
    u8 col[4];
} Obj_b018_01E01760;

static void func_01E01760_b018(s32 arg0, Obj_b018_01E01760 *obj, Vec_b018_01E00EE0 *pa0, Vec_b018_01E00EE0 *pb0) {
    Vec_b018_01E00EE0 quad[4];
    Vec_b018_01E00EE0 q[4];
    Vec_b018_01E00EE0 a[4];
    Vec_b018_01E00EE0 b[4];
    Vec_b018_01E00EE0 t0;
    Vec_b018_01E00EE0 t1;
    Vec_b018_01E00EE0 t2;
    Vec_b018_01E00EE0 t3;
    u8 pk[0x80] __attribute__((aligned(16)));
    u8 col[4];
    f32 depth[4];
    s32 dst;
    s32 n;
    s32 last;
    s32 i;
    s32 j;
    f32 t;
    Vec_b018_01E00EE0 *pa;
    Vec_b018_01E00EE0 *pb;

    dst = (s32)func_00207500();
    n = obj->n;
    func_001092E0(pk, 0);
    func_001094F0(pk);
    col[0] = obj->col[0];
    col[1] = obj->col[1];
    col[2] = obj->col[2];
    col[3] = obj->col[3];
    a[0] = pa0[0];
    a[1] = pa0[0];
    a[2] = pa0[1];
    a[3] = pa0[2];
    last = n - 1;
    b[0] = pb0[0];
    b[1] = pb0[0];
    b[2] = pb0[1];
    b[3] = pb0[2];
    for (i = 0; i < last; i++) {
        func_00107990(pk, col, 1);
        col[3] -= obj->col[3] / n;
        func_00107990(pk, col, 2);
        t = 0.0f;
        pa = pa0 + (i - 1);
        pb = pb0 + (i - 1);
        for (j = 0; j < 4; j++) {
            if (i != 0) {
                q[0] = func_01E00EE0_b018(pa, 0, t);
                q[2] = func_01E00EE0_b018(pb, 0, t);
                t += 0.25f;
                t0 = func_01E00EE0_b018(pa, 0, t);
                q[1] = t0;
                t1 = func_01E00EE0_b018(pb, 0, t);
                q[3] = t1;
            } else {
                q[0] = func_01E00EE0_b018(a, 0, t);
                q[2] = func_01E00EE0_b018(b, 0, t);
                t += 0.25f;
                t2 = func_01E00EE0_b018(a, 0, t);
                q[1] = t2;
                t3 = func_01E00EE0_b018(b, 0, t);
                q[3] = t3;
            }
            quad[0].x = q[0].x;
            quad[0].y = q[0].y;
            quad[0].z = q[0].z;
            quad[1].x = q[1].x;
            quad[1].y = q[1].y;
            quad[1].z = q[1].z;
            quad[2].x = q[2].x;
            quad[2].y = q[2].y;
            quad[2].z = q[2].z;
            quad[3].x = q[3].x;
            quad[3].y = q[3].y;
            quad[3].z = q[3].z;
            if (func_00205630((s32)quad, 0x70000000, 0, (s32)pk, depth) != 0) {
                func_002075F0((s32)pk, dst, 0);
            }
        }
    }
}

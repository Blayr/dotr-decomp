#include "common.h"

/* shape b134:01E011E0, 315 insns: IWTusk1, a tusk along one point trail: each segment is 4 spline steps (module
   curve, shape b018:01E00EE0), each drawn as two crossed quads of width h38 / 10 (one widened in z, one in x), scaled,
   the colour's alpha falling by a / (3 n) per step; the first segment runs on local copies (first point doubled) */

typedef struct {
    u8 r, g, b, a;
} C4_b134_01E011E0;

typedef struct {
    u8 pad00[6];
    s16 n;
    u8 pad08[0x20];
    C4_b134_01E011E0 col;
    u8 pad2C[0xC];
    s16 width;
} Tusk_b134_01E011E0;

static void func_01E011E0_b134(void *o, Tusk_b134_01E011E0 *s, Vec_b018_01E00EE0 *pts, Vec_b018_01E00EE0 *scale) {
    extern void func_001094F0(void *);
    extern void func_00107990(void *, void *, s32);
    extern void func_001092E0(void *, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec_b018_01E00EE0 sc;
    Vec_b018_01E00EE0 A;
    Vec_b018_01E00EE0 B;
    Vec_b018_01E00EE0 a4[4];
    Vec_b018_01E00EE0 q[4];
    f32 depth[4];
    u8 pkt[0x94];
    u8 *p;
    C4_b134_01E011E0 c;
    s16 k;
    s32 j;
    s32 m;
    s32 n3;
    s32 last;
    Vec_b018_01E00EE0 *pq;
    s32 ot;
    s16 n;
    f32 w;
    f32 t;
    s32 a;

    sc = *scale;
    w = s->width;
    ot = (s32)func_00207500();
    n = s->n;
    w /= 10.0f;
    p = (u8 *)(s32)pkt;
    func_001094F0(p);
    func_00107990(p, &s->col, 0);
    func_001092E0(p, 0);
    func_001094F0(p);
    c = s->col;
    n3 = n * 3;
    last = n - 1;
    a4[0] = pts[0];
    a4[1] = pts[0];
    a4[2] = pts[1];
    a4[3] = pts[2];
    for (k = 0; k < last; k++) {
        t = 0.0f;
        pq = pts + (k - 1);
        for (j = 0; j < 4; j++) {
            if (k != 0) {
                A = func_01E003E0_b134(pq, 0, t);
                t += 0.25f;
                B = func_01E003E0_b134(pq, 0, t);
            } else {
                A = func_01E003E0_b134(a4, 0, t);
                t += 0.25f;
                B = func_01E003E0_b134(a4, 0, t);
            }
            func_00107990(p, &c, 1);
            a = c.a - (s16)(s->col.a / n3);
            if (a <= 0) {
                c.a = 0;
            } else {
                c.a = a;
            }
            func_00107990(p, &c, 2);
            for (m = 0; m < 2; m++) {
                q[0].x = A.x;
                q[0].y = A.y;
                q[0].z = A.z;
                q[1].x = A.x;
                q[1].y = A.y;
                q[1].z = A.z;
                q[2].x = B.x;
                q[2].y = B.y;
                q[2].z = B.z;
                q[3].x = B.x;
                q[3].y = B.y;
                q[3].z = B.z;
                func_00107070(q, 0, sc.x);
                func_00107070(q, 1, sc.y);
                func_00107070(q, 2, sc.z);
                if (m == 0) {
                    q[0].z += w;
                    q[2].z += w;
                    q[1].z += w;
                    q[3].z += w;
                } else if (m == 1) {
                    q[0].x += w;
                    q[2].x += w;
                    q[1].x -= w;
                    q[3].x -= w;
                }
                if (func_00205630(q, 0x70000000, NULL, p, depth) != 0) {
                    func_002075F0(p, ot, (u32)depth[0]);
                }
            }
        }
    }
}

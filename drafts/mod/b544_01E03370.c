#include "common.h"

/* shape b544:01E03370, 340 insns: a ribbon between two splines (B544KPOINT_RAIN_3, b045:01E04270 style): untextured
   quads, 4 steps of 0.25 per segment along both point lists (b544:01E00550 type 0, the first segment from doubled
   first points); the near edge colour has alpha 0, the far edge fades by 3 a step while above 4 */

typedef struct {
    f32 x, y, z, w;
} Vec_b018_01E00EE0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b544_01E03370;

typedef struct {
    Rgbaq_b544_01E03370 c;
    u64 xyz;
} Vtx_b544_01E03370;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b544_01E03370 v[4];
    u8 tail[0x40];
} Pkt_b544_01E03370;

typedef struct {
    u8 r, g, b, a;
} Col_b544_01E03370;

typedef struct {
    u8 pad0[6];
    s16 count;
    u8 pad8[0x58];
    Col_b544_01E03370 col;
} Rib_b544_01E03370;

static void func_01E03370_b544(void *arg0, Rib_b544_01E03370 *an, Vec_b018_01E00EE0 *pa0, Vec_b018_01E00EE0 *pb0) {
    extern Rgbaq_b544_01E03370 func_00107740(void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern Vec_b018_01E00EE0 func_01E00550_b544(Vec_b018_01E00EE0 *, s32, f32);
    f32 depth __attribute__((aligned(16)));
    Vec_b018_01E00EE0 q[4];
    Vec_b018_01E00EE0 e[4];
    Vec_b018_01E00EE0 ca[4];
    Vec_b018_01E00EE0 cb[4];
    Vec_b018_01E00EE0 r1;
    Vec_b018_01E00EE0 r2;
    Vec_b018_01E00EE0 r3;
    Vec_b018_01E00EE0 r4;
    Pkt_b544_01E03370 pkt __attribute__((aligned(8)));
    Col_b544_01E03370 c1;
    Col_b544_01E03370 c2;
    Pkt_b544_01E03370 *p;
    Vec_b018_01E00EE0 *pa;
    Vec_b018_01E00EE0 *pb;
    s32 target;
    s32 n;
    s32 m;
    s32 i;
    s32 j;
    s16 a;
    f32 t;

    target = (s32)func_00207500();
    n = an->count;
    p = &pkt;
    func_001092E0(p, 0);
    func_001094F0(p);
    c1 = an->col;
    c2 = an->col;
    c1.a = 0;
    ca[0] = pa0[0];
    ca[1] = pa0[0];
    ca[2] = pa0[1];
    ca[3] = pa0[2];
    cb[0] = pb0[0];
    cb[1] = pb0[0];
    cb[2] = pb0[1];
    cb[3] = pb0[2];
    p->v[0].c = func_00107740(&c1);
    p->v[1].c = func_00107740(&c1);
    p->v[2].c = func_00107740(&c2);
    p->v[3].c = func_00107740(&c2);
    m = (s16)n - 1;
    for (i = 0; i < m; i++) {
        t = 0.0f;
        pa = &pa0[i - 1];
        pb = &pb0[i - 1];
        for (j = 0; j < 4; j++) {
            p->v[2].c = func_00107740(&c2);
            a = c2.a;
            if (a - 4 > 0) {
                a -= 3;
                if (a < 0) {
                    a = 0;
                }
                c2.a = a;
            } else {
                c2.a = 0;
            }
            p->v[3].c = func_00107740(&c2);
            if (i != 0) {
                e[0] = func_01E00550_b544(pa, 0, t);
                e[2] = func_01E00550_b544(pb, 0, t);
                t += 0.25f;
                r1 = func_01E00550_b544(pa, 0, t);
                e[1] = r1;
                r2 = func_01E00550_b544(pb, 0, t);
                e[3] = r2;
            } else {
                e[0] = func_01E00550_b544(ca, 0, t);
                e[2] = func_01E00550_b544(cb, 0, t);
                t += 0.25f;
                r3 = func_01E00550_b544(ca, 0, t);
                e[1] = r3;
                r4 = func_01E00550_b544(cb, 0, t);
                e[3] = r4;
            }
            q[0].x = e[0].x;
            q[0].y = e[0].y;
            q[0].z = e[0].z;
            q[1].x = e[1].x;
            q[1].y = e[1].y;
            q[1].z = e[1].z;
            q[2].x = e[2].x;
            q[2].y = e[2].y;
            q[2].z = e[2].z;
            q[3].x = e[3].x;
            q[3].y = e[3].y;
            q[3].z = e[3].z;
            if (func_00205630(q, 0x70000000, 0, p, &depth) != 0) {
                func_002075F0(p, target, 0);
            }
        }
    }
}

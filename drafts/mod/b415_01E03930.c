#include "common.h"

/* shape b415:01E03930, 321 insns (B415KPOINT_RAIN_3): draws a ribbon between two point curves: per segment four
   quads along the curves (module curve function b018:01E00EE0, steps of 0.25), the near edge in the object's colour
   and the far edge in the same colour at alpha 0, both alphas stepping down by alpha / (3 n) per quad; corners
   through func_00109A70, no world matrix */

typedef struct {
    f32 x, y, z, w;
} Vec_b018_01E00EE0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b415_01E03930;

typedef struct {
    Rgbaq_b415_01E03930 c;
    u64 xyz;
} Vtx_b415_01E03930;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b415_01E03930 v[4];
    u8 tail[0x40];
} Pkt_b415_01E03930;

typedef struct {
    u8 r, g, b, a;
} C4_b415_01E03930;

typedef struct {
    u8 pad00[6];
    s16 n;
    u8 pad08[0x58];
    C4_b415_01E03930 col;
} Obj_b415_01E03930;

static Vec_b018_01E00EE0 func_01E00D10_b415();

static void func_01E03930_b415(s32 arg0, Obj_b415_01E03930 *o, Vec_b018_01E00EE0 *pa, Vec_b018_01E00EE0 *pb) {
    extern Rgbaq_b415_01E03930 func_00107740(void *);
    extern void func_001092E0(void *, s32);
    extern void func_001094F0(void *);
    extern void func_00109A70(void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 depth[4];
    Vec_b018_01E00EE0 r[4];
    Vec_b018_01E00EE0 q[4];
    Vec_b018_01E00EE0 a4[4];
    Vec_b018_01E00EE0 b4[4];
    Pkt_b415_01E03930 pkt __attribute__((aligned(8)));
    C4_b415_01E03930 c0;
    C4_b415_01E03930 c1;
    s32 ot;
    s32 last;
    s32 k;
    s32 j;
    s16 n;
    s16 a;
    s16 step;
    Vec_b018_01E00EE0 *pp;
    Vec_b018_01E00EE0 *pq;
    Pkt_b415_01E03930 *p;
    f32 t;

    n = o->n;
    ot = (s32)func_00207500();
    p = &pkt;
    func_001092E0(p, 0);
    func_001094F0(p);
    c0 = o->col;
    c1 = o->col;
    c0.a = 0;
    a4[0] = pa[0];
    a4[1] = pa[0];
    a4[2] = pa[1];
    a4[3] = pa[2];
    b4[0] = pb[0];
    b4[1] = pb[0];
    b4[2] = pb[1];
    b4[3] = pb[2];
    p->v[0].c = func_00107740(&c0);
    p->v[1].c = func_00107740(&c0);
    p->v[2].c = func_00107740(&c1);
    p->v[3].c = func_00107740(&c1);
    last = n - 1;
    a = o->col.a;
    step = a / (s16)(n * 3);
    for (k = 0; k < last; k++) {
        t = 0.0f;
        pp = pa + (k - 1);
        pq = pb + (k - 1);
        for (j = 0; j < 4; j++) {
            p->v[2].c.a = a;
            a = a - step;
            if (a < 0) {
                a = 0;
            }
            p->v[3].c.a = a;
            if (k != 0) {
                q[0] = func_01E00D10_b415(pp, 0, t);
                q[2] = func_01E00D10_b415(pq, 0, t);
                t += 0.25f;
                q[1] = func_01E00D10_b415(pp, 0, t);
                q[3] = func_01E00D10_b415(pq, 0, t);
            } else {
                q[0] = func_01E00D10_b415(a4, 0, t);
                q[2] = func_01E00D10_b415(b4, 0, t);
                t += 0.25f;
                q[1] = func_01E00D10_b415(a4, 0, t);
                q[3] = func_01E00D10_b415(b4, 0, t);
            }
            func_00109A70(&r[0], &q[0]);
            func_00109A70(&r[1], &q[1]);
            func_00109A70(&r[2], &q[2]);
            func_00109A70(&r[3], &q[3]);
            if (func_00205630(r, 0x70000000, 0, p, depth) != 0) {
                func_002075F0(p, ot, 0);
            }
        }
    }
}

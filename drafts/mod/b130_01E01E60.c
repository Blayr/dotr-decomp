#include "common.h"

/* shape b130:01E01E60, 282 insns, 1 copy: B130PAINT_RAIN4: a tube along the scene's point trail (ctx+0x3A60, n =
   o->n points): per segment 18 quads around it, the near ring radius t and the far one t + 0.3 (t grows by 0.5 a
   segment), alpha fading by col.a / n along the tube */

typedef struct Rgba_b130_01E01E60 {
    u8 r, g, b, a;
} Rgba_b130_01E01E60;

typedef struct Fx_b130_01E01E60 {
    u8 pad0[0x28];
    Rgba_b130_01E01E60 col;
    u8 pad2C[6];
    s16 n;
} Fx_b130_01E01E60;

typedef struct Game_b130_01E01E60 {
    u8 pad0[0x3A60];
    Vec4f pts[16];
    u8 pad3B60[1];
} Game_b130_01E01E60;

static void func_01E01E60_b130(Game_b130_01E01E60 *g, Fx_b130_01E01E60 *o) {
    extern void func_001092E0();
    extern void func_001094F0();
    extern void func_00107990();
    extern f32 func_00108030();
    extern s32 func_00205630();
    extern void func_00109380();
    extern void func_002075F0();
    Vec4f q[4];
    f32 depth[4];
    u8 pk[0x90] __attribute__((aligned(16)));
    Rgba_b130_01E01E60 col;
    u8 *p;
    s32 ot;
    s16 n;
    s32 cnt;
    s32 last;
    s32 k;
    s32 j;
    s16 a;
    s16 b;
    f32 t;

    ot = (s32)func_00207500();
    t = 0.0f;
    n = o->n;
    p = pk;
    func_001092E0(p, 0);
    func_001094F0(p);
    cnt = n;
    col = o->col;
    last = cnt - 1;
    for (k = 0; k < last; k++) {
        func_00107990(p, &col, 1);
        col.a -= o->col.a / cnt;
        func_00107990(p, &col, 2);
        a = 0;
        for (j = 0; j < 18; j++) {
            q[0].x = g->pts[k].x;
            q[0].y = g->pts[k].y;
            q[0].z = g->pts[k].z;
            q[1].x = g->pts[k].x;
            q[1].y = g->pts[k].y;
            q[1].z = g->pts[k].z;
            q[0].y += t * func_00108030(g->pad3B60, a, 1);
            q[0].x += t * func_00108030(g->pad3B60, a, 0);
            q[0].z += t * func_00108030(g->pad3B60, a, 1);
            b = a + 20;
            q[1].y += t * func_00108030(g->pad3B60, b, 1);
            q[1].x += t * func_00108030(g->pad3B60, b, 0);
            q[1].z += t * func_00108030(g->pad3B60, b, 1);
            q[2].x = g->pts[k + 1].x;
            q[2].y = g->pts[k + 1].y;
            q[2].z = g->pts[k + 1].z;
            q[3].x = g->pts[k + 1].x;
            q[3].y = g->pts[k + 1].y;
            q[3].z = g->pts[k + 1].z;
            q[2].y += (t + 0.3f) * func_00108030(g->pad3B60, a, 1);
            q[2].x += (t + 0.3f) * func_00108030(g->pad3B60, a, 0);
            q[2].z += (t + 0.3f) * func_00108030(g->pad3B60, a, 1);
            q[3].y += (t + 0.3f) * func_00108030(g->pad3B60, b, 1);
            q[3].x += (t + 0.3f) * func_00108030(g->pad3B60, b, 0);
            q[3].z += (t + 0.3f) * func_00108030(g->pad3B60, b, 1);
            if (func_00205630(q, 0x70000000, 0, p, depth)) {
                func_00109380(p, 1);
                func_002075F0(p, ot, 0);
            }
            a += 20;
        }
        t += 0.5f;
    }
}

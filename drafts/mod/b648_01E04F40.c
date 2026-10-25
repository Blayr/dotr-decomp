#include "common.h"

/* shape b648:01E04F40, 137 insns: the scene's falling-ash ring: while flag 0x1F is set it moves the camera block at
   g+0x22B4 towards -30 (else +30), the scene's top flag bit follows whether it is done; the module's emitter runs on
   g+0x2260/0x21F0; each live particle falls by 3 and spreads (x0.8 above the ground, x1.05 below), and once below -200 it
   is reborn at a random angle on the scene radius (g+0x22AC), alpha 0x40 from scene step 43; past step 380 the scene's
   0x226B block is cleared */

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    u8 a;
    u8 pad;
    s16 d;
} Part_b648_01E04F40;

typedef struct {
    u8 pad0[0x21F0];
    u8 v21F0[0x70];
    u8 v2260[0xB];
    u8 b226B[0x41];
    f32 radius;
    u8 pad22B0[4];
    f32 cam[1]; u8 cam2[2];
    s16 n;
    u8 pad22BC[4];
    Part_b648_01E04F40 part[137];
    u8 pad2B50[0xC];
    s32 step;
    u8 pad2B60[4];
    u32 flags;
} Scene_b648_01E04F40;


static void func_01E04F40_b648(Scene_b648_01E04F40 *g, s32 arg) {
    extern void b648_01E01C70(s32, void *, void *);
    extern s32 func_00104520(s32, s32);
    extern s32 func_00103540(void *, f32, f32);
    extern s32 func_00103390(void *, f32, f32);
    extern f32 func_0020B480(s32);
    extern f32 func_0020B550(s32);
    extern void func_00103470(void *, s32, s32);
    s32 i;
    s32 r;

    if (func_00104520(g->flags, 0x1F)) {
        if (func_00103540(g->cam, -30.0f, 1.5f) == 0) {
            g->flags &= 0x7FFFFFFF;
        }
    } else {
        if (func_00103390(g->cam, 30.0f, 1.5f) == 0) {
            g->flags |= 0x80000000;
        }
    }
    b648_01E01C70(arg, g->v2260, g->v21F0);
    for (i = 0; i < g->n; i++) {
        if (g->part[i].d < 0) {
            continue;
        }
        g->part[i].y -= 3.0f;
        if (g->part[i].y > 0.0f) {
            g->part[i].z *= 0.8f;
            g->part[i].x *= 0.8f;
        } else {
            g->part[i].z *= 1.05f;
            g->part[i].x *= 1.05f;
        }
        if (g->part[i].y < -200.0f) {
            r = func_0019A5C8() % 0x10000;
            g->part[i].d = -i;
            g->part[i].z = g->radius * func_0020B480(r);
            g->part[i].x = g->radius * func_0020B550(r);
            g->part[i].y = 0.0f;
            if (g->step >= 43) {
                g->part[i].a = 0x40;
            } else {
                g->part[i].a = 0;
            }
        }
    }
    if (g->step > 380) {
        func_00103470(g->b226B, 0, 0x10);
    }
}

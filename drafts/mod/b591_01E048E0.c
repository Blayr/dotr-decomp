#include "common.h"

/* shape b591:01E048E0, 135 insns: a swirl of rising points: the scene's top flag bit flips when its level (0x22B4) reaches
   -30 or 30 (1.5 a step); the module's 0x1E02080 runs; each live point rises 3 a tick, closing in by 0.8 while above 0
   and widening by 1.05 below; under -200 it restarts at a random angle on the scene radius (0x22AC), turned bright
   after scene frame 60; after frame 340 the colour at 0x226B is cleared */

typedef struct {
    f32 x, y, z;
    s8 b;
    u8 padD;
    s16 id;
} Pt_b591_01E048E0;

typedef struct {
    u8 pad0[0x21F0];
    u8 a21F0[0x70];
    u8 a2260[0xB];
    u8 c226B[0x41];
    f32 radius;
    u8 pad22B0[4];
    f32 level;
    u8 pad22B8[2];
    s16 count;
    u8 pad22BC[4];
    Pt_b591_01E048E0 pt[1];
    u8 pad22D0[0xB10];
    s32 frame;
    u8 pad2DE4[4];
    u32 bits;
} Scene_b591_01E048E0;

extern void b591_01E02080(s32, void *, void *);

static void func_01E048E0_b591(Scene_b591_01E048E0 *g, s32 arg) {
    extern s32 func_00104520(u32, s32);
    extern s32 func_00103540(void *, f32, f32);
    extern s32 func_00103390(void *, f32, f32);
    extern f32 func_0020B480(s32);
    extern f32 func_0020B550(s32);
    extern void func_00103470(void *, s32, s32);
    s32 i;
    s32 n;

    if (func_00104520(g->bits, 0x1F) != 0) {
        if (func_00103540(&g->level, -30.0f, 1.5f) == 0) {
            g->bits &= 0x7FFFFFFF;
        }
    } else if (func_00103390(&g->level, 30.0f, 1.5f) == 0) {
        g->bits |= 0x80000000;
    }
    b591_01E02080(arg, g->a2260, g->a21F0);
    for (i = 0; i < g->count; i++) {
        if (g->pt[i].id >= 0) {
            g->pt[i].y -= 3.0f;
            if (g->pt[i].y > 0.0f) {
                g->pt[i].z *= 0.8f;
                g->pt[i].x *= 0.8f;
            } else {
                g->pt[i].z *= 1.05f;
                g->pt[i].x *= 1.05f;
            }
            if (g->pt[i].y < -200.0f) {
                n = func_0019A5C8() % 0x10000;
                g->pt[i].id = -i;
                g->pt[i].z = g->radius * func_0020B480(n);
                g->pt[i].x = g->radius * func_0020B550(n);
                g->pt[i].y = 0.0f;
                if (g->frame >= 0x3C) {
                    g->pt[i].b = 0x40;
                }
            }
        }
    }
    if (g->frame > 0x154) {
        func_00103470(g->c226B, 0, 0x10);
    }
}

#include "common.h"

/* shape b037:01E05F30, 141 insns: the b037 module's late-scene step (scene time s32 at ctx+0x5334): from 124 to 232 runs b037:01E010B0 with a random dark colour, a counter at 0x37C growing 10 from 184 and clearing 8 bytes at 0x36B past 300; from 209 runs b037:01E003E0 at the origin (clearing 4 bytes at 0x103B from 243); from 248 places a light at the scene point (b037:01E03BD0/01E03E90) and spreads three angles by 2, then 1 (from 293), then 1 every other tick (from 308) */

typedef struct {
    u8 pad0[0x2F0];
    u8 m2F0[0x70];
    u8 m360[8];
    s8 col[3];
    u8 m36B[0x37C - 0x36B];
    s32 n37C;
    u8 pad380[0x570 - 0x380];
    u8 m570[0x70];
    u8 m5E0[0xC];
    s32 w5EC;
    u8 pad5F0[0xDF0 - 0x5F0];
    s16 a0;
    s16 a1;
    s16 a2;
    u8 padDF6[0xFC0 - 0xDF6];
    u8 mFC0[0x20];
    u8 mFE0[0x50];
    u8 m1030[0xB];
    u8 m103B[0x5334 - 0x103B];
    s32 time;
} Ctx_b037_01E05F30;

extern void b037_01E003E0(s32, void *, void *, s32 *);
extern void b037_01E010B0(s32, void *, void *);
extern void b037_01E03BD0(void *, void *, f32, f32, f32);
extern void b037_01E03E90(void *);

static void func_01E05F30_b037(Ctx_b037_01E05F30 *g, s32 arg) {
    extern void func_00103470(void *, s32, s32);
    extern s32 func_00205D10(void *, f32);
    s32 v[4];

    if (g->time > 123 && g->time < 233) {
        b037_01E010B0(arg, g->m360, g->m2F0);
        g->col[2] = func_0019A5C8() % 128;
        g->col[1] = func_0019A5C8() % 128;
        g->col[0] = func_0019A5C8() % 128;
        if (g->time >= 184) {
            g->n37C += 10;
        }
        if (g->n37C > 300) {
            func_00103470(g->m36B, 0, 8);
        }
    }
    if (g->time >= 209) {
        v[0] = v[1] = v[2] = 0;
        b037_01E003E0(arg, g->mFC0, g->m1030, v);
        if (g->time >= 243) {
            func_00103470(g->m103B, 0, 4);
        }
    }
    if (g->time >= 248) {
        g->w5EC = func_00205D10(g->mFE0, 10.0f);
        b037_01E03BD0(g->m5E0, g->m570, 4.0f, 10.0f, 0.0f);
        b037_01E03E90(g->m5E0);
        if (g->time < 293) {
            g->a0 += 2;
            g->a1 -= 2;
            g->a2 += 2;
        } else if (g->time < 308) {
            g->a0 += 1;
            g->a1 -= 1;
            g->a2 += 1;
        } else if (g->time % 2 == 0) {
            g->a0 += 1;
            g->a1 -= 1;
            g->a2 += 1;
        }
    }
}

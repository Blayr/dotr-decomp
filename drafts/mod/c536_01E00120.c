#include "common.h"

/* shape c536:01E00120, 131 insns, 12 copies: move a camera state one step toward a target: 1/steps of the
   remaining distance for two floats, two integer triples and the position; returns the steps left */

typedef struct Cam_c536_01E00120 {
    f32 pos[3];
    u8 padC[4];
    s32 a[3];
    u8 pad1C[4];
    s32 b[3];
    u8 pad2C[4];
    f32 f30;
    f32 f34;
    u8 pad38[0x10];
    s32 steps;
} Cam_c536_01E00120;

static s32 func_01E00120_c536(Cam_c536_01E00120 *c, Cam_c536_01E00120 *t) {
    f32 k;
    f32 dx;
    f32 dy;
    f32 px;
    f32 py;
    f32 pz;
    s32 a0;
    s32 a1;
    s32 a2;
    s32 b1;
    s32 b2;

    if (t->steps != 0) {
        k = 1.0f / t->steps;
        dy = t->f34 - c->f34;
        c->f30 += k * (t->f30 - c->f30);
        c->f34 += k * dy;
        a0 = k * (t->a[0] - c->a[0]);
        a1 = k * (t->a[1] - c->a[1]);
        a2 = k * (t->a[2] - c->a[2]);
        c->a[0] += a0;
        c->a[1] += a1;
        c->a[2] += a2;
        a2 = k * (t->b[0] - c->b[0]);
        a0 = k * (t->b[1] - c->b[1]);
        a1 = k * (t->b[2] - c->b[2]);
        c->b[0] += a2;
        c->b[1] += a0;
        c->b[2] += a1;
        px = t->pos[0] - c->pos[0];
        pz = t->pos[2] - c->pos[2];
        py = t->pos[1] - c->pos[1];
        c->pos[0] += k * px;
        c->pos[1] += k * py;
        c->pos[2] += k * pz;
    }
    t->steps--;
    return t->steps;
}

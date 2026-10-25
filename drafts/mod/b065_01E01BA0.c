#include "common.h"

/* shape b065:01E01BA0, 131 insns: b377:01E01F60's joint-to-joint glow: size 15 + 5 * n, dark grey (0x18) over (0x20, 0x30,
   0x20), alpha up by 0x30 for 60 ticks; ends when the scene frame (0xB2BA) passes 0x43 */

typedef struct {
    u8 pad0[0x10];
    f32 x, y, z;
    u8 pad1C[4];
    s32 w20;
    u8 pad24[0x28];
    f32 f4C;
    s16 n;
    s16 h52;
    s16 t;
    u8 pad56[2];
    s16 mode;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b065_01E01BA0;

typedef struct {
    u8 pad[0xB248];
    s16 j0;
    s16 j1;
    u8 padB24C[0x6E];
    s16 frame;
} Game_b065_01E01BA0;

static s32 func_01E01BA0_b065(Game_b065_01E01BA0 *g, Obj_b065_01E01BA0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5620(s32, s32, void *);
    f32 d[4];
    f32 k;

    if (o->mode == 1) {
        o->f4C = 15.0f + 5.0f * o->n;
        func_001076F0(o->col, 0x18, 0x18, 0x18);
        func_001076F0(o->col2, 0x20, 0x30, 0x20);
        o->h52 = 0;
        o->h5A = 10;
        o->h5C = 10;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->t < 0x3C) {
        if (o->col2[3] < 0xC0) {
            o->col2[3] += 0x30;
        }
    } else if (o->col2[3] > 10) {
        o->col2[3] -= 9;
    } else {
        o->mode = 0;
    }
    func_001F5620(func_001F53A0(), g->j0, &o->x);
    func_001F5620(func_001F53A0(), g->j1, d);
    d[0] = (d[0] - o->x) / 10.0f;
    d[1] = (d[1] - o->y) / 10.0f;
    d[2] = (d[2] - o->z) / 10.0f;
    k = o->n;
    o->x += d[0] * k;
    o->y += d[1] * k;
    o->z += d[2] * k;
    func_00205C40((s32)&o->w20);
    o->w20 += 0x4000;
    o->t++;
    if (g->frame > 0x43) {
        o->mode = 0;
    }
    return 0;
}

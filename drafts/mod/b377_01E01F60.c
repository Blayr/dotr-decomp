#include "common.h"

/* shape b377:01E01F60, 124 insns: on start size 30 + 6 * n, dark grey colour, purple second colour (alpha 0), 0x5A/0x5C 10;
   the second alpha grows by 0x13 (below 0xC0) for 140 ticks, then fades by 9 (ends below 11); sits on joint A, moved
   n tenths of the way to joint B; turn 0x20 += 0x4000 */

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
} Obj_b377_01E01F60;

typedef struct {
    u8 pad[0xB244];
    s16 j0;
    s16 j1;
} Game_b377_01E01F60;

static s32 func_01E01F60_b377(Game_b377_01E01F60 *g, Obj_b377_01E01F60 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5620(s32, s32, void *);
    f32 d[4];
    f32 k;

    if (o->mode == 1) {
        o->f4C = 30.0f + 6.0f * o->n;
        func_001076F0(o->col, 0x40, 0x40, 0x40);
        func_001076F0(o->col2, 0x30, 0x10, 0x60);
        o->h52 = 0;
        o->h5A = 10;
        o->h5C = 10;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->t < 0x8C) {
        if (o->col2[3] < 0xC0) {
            o->col2[3] += 0x13;
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
    return 0;
}

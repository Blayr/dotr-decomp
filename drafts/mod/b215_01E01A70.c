#include "common.h"

/* shape b215:01E01A70 (B215_OBJ_MOVE_3_), 267 insns, 1 copy: a 20 by 28 ripple grid under the unit: mode 1 lays the
   grid out (step 2 * 4.2, centred), then every tick each point closer to the unit than the ripple radius rises by 0.8
   and moves its two counters by -5/+5; bright (0x80) for 20 ticks, then fades by 9 once the scene timer is under 20 */

typedef struct {
    u8 pad0[8];
    s16 f8;
    u8 padA[0x1A];
    s32 f24;
    u8 pad28[0xC];
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    u8 pad4C[8];
    s16 tick;
    s16 f56;
    s16 mode;
    u8 pad5A[6];
    u8 col0[4];
    u8 col1[4];
} Fx_b215_01E01A70;

typedef struct {
    u8 pad0[0x3BC0];
    Vec4f grid[20][40];
    u8 pad6DC0[0x9FC0 - 0x6DC0];
    f32 rx;
    u8 pad9FC4[4];
    f32 rz;
    u8 pad9FCC[0x24];
    s32 timer;
    u8 pad9FF4[0x44];
    s16 unit;
    u8 padA03A[0xB460 - 0xA03A];
    s16 a[20][40];
    u8 padBAA0[0xC0E0 - 0xBAA0];
    s16 b[20][40];
    u8 padC720[0xCD60 - 0xC720];
    s16 c[20][40];
} Game_b215_01E01A70;

static s32 func_01E01A70_b215(Game_b215_01E01A70 *g, Fx_b215_01E01A70 *o) {
    extern s32 func_001F5380(void);
    extern s32 func_001F5620(s32, s32, void *);
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_001A6C60(f32);
    Vec4f pos;
    Vec4f d;
    s16 i;
    s16 j;

    func_001F5620(func_001F5380(), g->unit, &pos);
    if (o->mode == 1) {
        o->f48 = 4.2f;
        o->f56 = func_0019A5C8() % 7;
        o->mode = 2;
        o->f8 = func_0019A5C8() % 3 + 4;
        o->f34 = 1.2f;
        for (i = 0; i < 20; i++) {
            for (j = 0; j < 28; j++) {
                g->grid[i][j].x = 2.0f * o->f48 * i - 2.0f * o->f48 * 20.0f / 2.0f;
                g->grid[i][j].z = 2.0f * o->f48 * j - 2.0f * o->f48 * 28.0f / 2.0f;
                g->grid[i][j].y = 0.0f;
                g->a[i][j] = 0;
                g->b[i][j] = 0;
                g->c[i][j] = 0;
            }
        }
    }
    if (o->tick < 20) {
        o->col0[3] = 0x80;
        o->col1[3] = 0x80;
    } else if (g->timer < 20) {
        if (o->col0[3] > 10) {
            o->col0[3] -= 9;
        } else {
            o->mode = 0;
        }
        if (o->col1[3] > 10) {
            o->col1[3] -= 9;
        }
    }
    func_001A6C60(g->rx * g->rx + g->rz * g->rz);
    for (i = 0; i < 20; i++) {
        for (j = 0; j < 28; j++) {
            ((f32 *)&d)[0] = pos.x - (pos.x + g->grid[i][j].x);
            ((f32 *)&d)[2] = pos.z - (pos.z + g->grid[i][j].z);
            if (g->rx > func_001A6C60(((f32 *)&d)[0] * ((f32 *)&d)[0] + ((f32 *)&d)[2] * ((f32 *)&d)[2])) {
                g->grid[i][j].y += 0.8f;
                g->a[i][j] -= 5;
                g->b[i][j] += 5;
            }
        }
    }
    if (o->tick % 2 == 1) {
        func_001076F0(o->col0, 0x80, 0x80, 0x80);
        func_001076F0(o->col1, 0x80, 0x80, 0x80);
    } else {
        func_001076F0(o->col0, 0x80, 0x80, 0x80);
        func_001076F0(o->col1, 0x80, 0x80, 0x80);
    }
    o->f24 = 0x4000;
    o->tick++;
    return 0;
}

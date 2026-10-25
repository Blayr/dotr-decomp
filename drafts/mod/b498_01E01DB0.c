#include "common.h"

/* shape b498:01E01DB0 (B498_OBJ_MOVE_12_), 352 insns, 1 copy: a twin trail wall on track idx: set up once (height
   2.0, turned by the scene side, a random x drift of -3..2.9 a tick, the track point taken from the camera and pushed
   4 x drift, both 19-point trails filled flat and at the height); then it brightens by 10 for 18 ticks and fades by
   9, feeds both trails (the upper one 10 to the side's z), blinks blue, its count grows to 18, and the point slides
   6.5 along z (by the side) and drifts */

typedef struct {
    Vec4f a[20];
    Vec4f b[20];
} Trail_b498_01E01DB0;

typedef struct {
    u8 pad0[0x2C30];
    Trail_b498_01E01DB0 tr[1];
    u8 pad2EB0[0xA930 - 0x2EB0];
    Vec4f pts[1];
    u8 padA940[0xACB8 - 0xA940];
    s16 side;
} Scene_b498_01E01DB0;

typedef struct {
    u8 pad0[6];
    s16 f6;
    s16 f8;
    s16 fA;
    u8 padC[8];
    s32 rot;
    u8 pad18[4];
    s32 drift;
    u8 pad20[8];
    u8 col[4];
    u8 col2[4];
    s16 idx;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 ang;
} Fx_b498_01E01DB0;

static s32 func_01E01DB0_b498(Scene_b498_01E01DB0 *g, Fx_b498_01E01DB0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5F90(s32, void *);
    Vec4f v;
    f32 h;
    f32 d;
    s32 i;

    if (o->mode == 1) {
        h = o->fA = 20;
        o->f8 = func_0019A5C8() % 2;
        h /= 10.0f;
        if (g->side != 0) {
            o->rot = 0;
        } else {
            o->rot = 0x4000;
        }
        o->drift = func_0019A5C8() % 60 - 30;
        o->drift = o->drift / 10.0f;
        func_001076F0(o->col2, 0x80, 0x80, 0x80);
        func_001F5F90(func_001F53A0(), &g->pts[o->idx]);
        g->pts[o->idx].x += 4.0f * o->drift;
        v.y = 0.0f;
        o->ang = func_0019A5C8() % 360;
        v.z = g->pts[o->idx].z;
        v.x = g->pts[o->idx].x;
        for (i = 0; i < 19; i++) {
            g->tr[o->idx].a[i].x = v.x;
            g->tr[o->idx].a[i].y = v.y;
            g->tr[o->idx].a[i].z = v.z;
        }
        v.y = h;
        for (i = 0; i < 19; i++) {
            g->tr[o->idx].b[i].x = v.x;
            g->tr[o->idx].b[i].y = v.y;
            g->tr[o->idx].b[i].z = v.z;
        }
        o->f6 = 2;
        o->col[3] = 0;
        o->f8 = 0;
        o->f34 = 0;
        o->f38 = 5;
        o->mode = 2;
    }
    if (o->tick < 18) {
        if (o->col[3] < 0x80) {
            o->col[3] += 10;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    d = o->fA / 10.0f;
    if (o->ang >= 360) {
        o->ang %= 360;
    }
    v.y = o->f8;
    v.z = g->pts[o->idx].z;
    v.x = g->pts[o->idx].x;
    func_01E00260_b498(&g->tr[o->idx].a[19], 20, 0, &v);
    v.y = d + o->f8;
    if (g->side != 0) {
        v.z = 10.0f + g->pts[o->idx].z;
    } else {
        v.z = g->pts[o->idx].z - 10.0f;
    }
    v.x = g->pts[o->idx].x;
    func_01E00260_b498(&g->tr[o->idx].b[19], 20, 0, &v);
    if (o->tick % 2 == 1) {
        func_001076F0(o->col, 0x20, 0x20, 0x80);
    } else {
        func_001076F0(o->col, 0x10, 0x10, 0x70);
    }
    if (o->tick != 0) {
        if (o->f6 < 18) {
            o->f6++;
        }
    }
    if (g->side != 0) {
        g->pts[o->idx].z -= 6.5f;
    } else {
        g->pts[o->idx].z += 6.5f;
    }
    if (o->tick != 0) {
        g->pts[o->idx].x += o->drift;
    }
    o->tick++;
    return 0;
}

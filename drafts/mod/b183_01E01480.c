#include "common.h"

/* shape b183:01E01480, 324 insns: B183_OBJ_MOVE_3_, a glow that flies from the camera joint to the scene joint:
   size 20 growing to 50, fades in until 140 then out, blinks white/grey, moves a 75th of the gap a frame over
   61..139, bursts thirty 0x1E01990 at 140 and two 0x1E01B50 at 140..141, trails 0x1E01CE0, animates 8 frames */

typedef struct {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[4];
    Vec4f pos;
    u8 rot[0x34];
    s16 t;
    s16 frame;
    s16 state;
    u8 pad5A[6];
    u8 c0[4];
    u8 c1[4];
} Glow_b183_01E01480;

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
} Scene_b183_01E01480;

static s32 func_01E01480_b183(Scene_b183_01E01480 *g, Glow_b183_01E01480 *o) {
    extern void b183_01E01990(void);
    extern void b183_01E01B50(void);
    extern void b183_01E01CE0(void);
    extern void b183_01E028A0(Scene_b183_01E01480 *, void (*)(void), s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5F90(s32, void *);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00205C40(void *);
    Vec4f a;
    Vec4f b;
    f32 *p;
    s16 i;

    func_001F5F90(func_001F5380(), &a);
    func_001F5F90(func_001F53A0(), p = (f32 *)(u32)&b);
    a.x = (a.x - p[0]) / 75.0f;
    a.y = (a.y - b.y) / 75.0f;
    a.z = (a.z - b.z) / 75.0f;
    if (o->state == 1) {
        o->w = 20;
        o->h = 20;
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
        func_001076F0(o->c1, 0x80, 0x80, 0x80);
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 140) {
        if (o->c0[3] < 128) {
            o->c0[3] += 42;
        }
        if (o->c1[3] < 128) {
            o->c1[3] += 42;
        }
    } else {
        if (o->c0[3] > 15) {
            o->c0[3] -= 14;
        } else {
            o->state = 0;
        }
        if (o->c0[3] > 15) {
            o->c0[3] -= 14;
        }
    }
    if (o->t != 0) {
        if (o->w < 50) {
            o->w += 2;
        }
        if (o->h < 50) {
            o->h += 2;
        }
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
    } else {
        func_001076F0(o->c0, 0xC0, 0xC0, 0xC0);
    }
    if (o->t > 60 && o->t < 140) {
        o->pos.x += a.x;
        o->pos.y += a.y;
        o->pos.z += a.z;
    }
    if (o->t == 140) {
        for (i = 0; i < 30; i++) {
            g->pos = o->pos;
            g->pos.x += func_0019A5C8() % 10 - 5;
            g->pos.y += func_0019A5C8() % 10 - 5;
            g->pos.z += func_0019A5C8() % 10 - 5;
            b183_01E028A0(g, b183_01E01990, 0);
        }
    }
    if (o->t >= 140 && o->t < 142) {
        for (i = 0; i < 2; i++) {
            g->pos = o->pos;
            g->pos.x += func_0019A5C8() % 20 - 10;
            g->pos.y += func_0019A5C8() % 20 - 10;
            g->pos.z += func_0019A5C8() % 20 - 10;
            b183_01E028A0(g, b183_01E01B50, 0);
        }
    }
    if (o->t > 60 && o->t < 140) {
        g->pos = o->pos;
        b183_01E028A0(g, b183_01E01CE0, 0);
    }
    if (o->t > 60) {
        o->frame++;
        if (o->frame > 7) {
            o->frame = 0;
        }
    }
    func_00205C40(o->rot);
    o->t++;
    return 0;
}

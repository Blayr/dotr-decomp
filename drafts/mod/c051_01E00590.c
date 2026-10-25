#include "common.h"

/* shape c051:01E00590, 155 insns: c051's scene manager: with a scene id (>= 0) it clears the scene, installs the module's
   step, loads texture 15, builds the sine table for 0..90 degrees, keeps the id and sets the 36-frame countdown;
   otherwise it runs the step, every live node's update callback, reads the camera point, and draws every live node twice
   at it; it returns 2 once the scene clock (0x2F8) reaches 20 with more than 2 frames left, else 8 once the countdown
   runs out */

typedef struct Node_c051_01E00590 {
    u8 pad0[0x10];
    void (*draw)(void *, struct Node_c051_01E00590 *, void *, s32);
    void (*update)(void *, struct Node_c051_01E00590 *);
    u8 pad18[0x1E];
    s16 used;
    u8 pad38[8];
} Node_c051_01E00590;

typedef struct {
    u8 m0[0x40];
    u8 m[0x40];
    u8 pad80[0x30];
    Node_c051_01E00590 node[8];
    s32 count;
    u8 pad2B4[8];
    s32 ot;
    u8 pad2C0[4];
    void (*step)();
    u8 pad2C8[0x2C];
    s16 id;
    u8 pad2F6[2];
    s16 clock;
    u8 pad2FA[6];
    f32 sintab[91];
    s32 tex[16];
} Scene_c051_01E00590;


static s32 func_01E00590_c051(Scene_c051_01E00590 *g, s32 id) {
    extern void func_00195108(void *, s32);
    extern f32 func_001A6A88(f32);
    extern s32 func_00202BF0(s32, s32);
    extern s32 func_001F5380(void);
    extern void func_001F5BD0(s32, void *);
    extern void func_001E11B0(s32, s32, void *);
    extern void func_0020EB40(void *);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020BC00(void *, void *);
    void (*draw)(void *, Node_c051_01E00590 *, void *, s32);
    f32 w[4];
    f32 v[4];
    u8 buf[0x90];
    s32 n;
    s32 i;

    n = 0;
    g->ot = (s32)func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x4B0);
        g->step = func_01E00080_c051;
        for (n = 15; n < 16; n++) {
            g->tex[n] = func_00202BF0(4, n);
        }
        for (n = 0; n < 91; n++) {
            g->sintab[n] = func_001A6A88(3.1415927f * n / 180.0f);
        }
        g->id = id;
        g->count = 36;
        return 0;
    }
    {
        extern void c051_01E00080();
        c051_01E00080(g, 0);
    }
    for (i = 0; i < 8; i++) {
        if (g->node[i].used != 0 && g->node[i].update != 0) {
            g->node[i].update(g, &g->node[i]);
        }
    }
    func_001F5BD0(func_001F5380(), v);
    func_001E11B0(func_001F5380() >> 8, func_001F5380() & 0xF, v);
    w[0] = v[0];
    w[1] = v[1];
    w[2] = v[2];
    for (i = 0; i < 8; i++) {
        if (g->node[i].used != 0) {
            func_0020EB40(g->m);
            n++;
            func_0020C940(g, 0, 0, w);
            func_0020BC00(g->m, g);
            draw = g->node[i].draw;
            if (draw != 0) {
                draw(g, &g->node[i], buf, 0);
                draw(g, &g->node[i], buf, 1);
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->clock >= 20 && g->count > 2) {
        return 2;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

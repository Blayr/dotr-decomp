#include "common.h"

/* shape c022:01E00C70, 168 insns: c022's scene manager (c027:01E00660 family): with a scene id (>= 0) it clears the
   scene, keeps the step (0x1E00080), loads texture 15, keeps the id, builds the sine table for 0..90 degrees and sets
   the 68-frame countdown; otherwise it runs the step, updates every live node (the 0x1E01850 kind spins its colours
   in for 8 frames and out after 35, and dies under 3 frames left; others run 0x1E00750), draws each twice by kind,
   and returns 8 once the countdown runs out */

typedef struct {
    u8 pad0[0x18];
    s32 fn;
    u8 pad1C[0xC];
    u8 col[4];
    u8 col2[4];
    u8 pad30[2];
    s16 used;
    u8 spin[0xC];
} Node_c022_01E00C70;

typedef struct {
    u8 pad0[0x90];
    s32 tex[16];
    u8 padD0[0x20];
    Node_c022_01E00C70 node[193];
    u8 pad3130[0x8C0];
    s32 count;
    u8 pad39F4[8];
    s32 ot;
    u8 pad3A00[4];
    s32 step;
    u8 pad3A08[0x3C];
    s16 id;
    u8 pad3A46[2];
    s16 frame;
    u8 pad3A4A[6];
    f32 sintab[91];
} Scene_c022_01E00C70;

extern void c022_01E00080(Scene_c022_01E00C70 *, s32);
extern void c022_01E00750(Scene_c022_01E00C70 *, Node_c022_01E00C70 *);
extern void c022_01E010E0(Scene_c022_01E00C70 *, Node_c022_01E00C70 *, void *, s32);
extern void c022_01E01850(Scene_c022_01E00C70 *, Node_c022_01E00C70 *, void *, s32);

static s32 func_01E00C70_c022(Scene_c022_01E00C70 *g, s32 id) {
    extern void func_00195108(void *, s32);
    extern f32 func_001A6A88(f32);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00106D80(s32, void *);
    u8 buf[0x90];
    s32 i;

    i = 0;
    g->ot = (s32)func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x3BC0);
        g->step = (s32)c022_01E00080;
        for (i = 15; i < 16; i++) {
            g->tex[i] = func_00202BF0(4, i);
        }
        g->id = id;
        for (i = 0; i < 91; i++) {
            g->sintab[i] = func_001A6A88(3.1415927f * i / 180.0f);
        }
        g->count = 68;
        return 0;
    }
    c022_01E00080(g, 0);
    for (i = 0; i < 193; i++) {
        if (g->node[i].used != 0) {
            if (g->node[i].fn != (s32)c022_01E01850) {
                c022_01E00750(g, &g->node[i]);
            } else {
                func_00106D80(5, g->node[i].spin);
                if (g->frame < 8) {
                    if (g->node[i].col[3] < 0xC0) {
                        g->node[i].col[3] += 0x20;
                    }
                    if (g->node[i].col2[3] < 17) {
                        g->node[i].col2[3] += 0x10;
                    }
                }
                if (g->frame > 35) {
                    if (g->node[i].col[3] > 16) {
                        g->node[i].col[3] -= 15;
                    }
                    if (g->node[i].col2[3] > 16) {
                        g->node[i].col2[3] -= 15;
                    }
                }
                if (g->count < 3) {
                    g->node[i].used = 0;
                }
            }
        }
    }
    for (i = 0; i < 193; i++) {
        if (g->node[i].used != 0) {
            if (g->node[i].fn != (s32)c022_01E01850) {
                c022_01E010E0(g, &g->node[i], buf, 0);
                c022_01E010E0(g, &g->node[i], buf, 1);
            } else {
                c022_01E01850(g, &g->node[i], buf, 0);
                c022_01E01850(g, &g->node[i], buf, 1);
            }
        }
    }
    if (--g->count <= 0) {
        return 8;
    }
    return 0;
}

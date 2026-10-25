#include "common.h"

/* shape c026:01E00F20, 147 insns: c017:01E010C0's scene manager for c026: 50 nodes of 0x80 at 0x140, texture 15,
   scale 0.7/0.2/0.7, a 126-frame countdown, the draw buffer inside the scene at 0x1B58 */

typedef struct {
    f32 x, y, z, w;
} V4_c026_01E00F20;

typedef struct Node_c026_01E00F20 {
    u8 pad0[0x58];
    s32 (*draw)(void *, struct Node_c026_01E00F20 *, void *, s32);
    s32 (*fn)(void *, struct Node_c026_01E00F20 *);
    u8 pad60[0xC];
    s16 used;
    u8 pad6E[0x12];
} Node_c026_01E00F20;

typedef struct {
    u8 pad0[0x40];
    u8 cam[0x60];
    s32 tex[16];
    s32 rot[4];
    V4_c026_01E00F20 sc;
    u8 pad100[0x40];
    Node_c026_01E00F20 node[50];
    s32 timer;
    u8 pad1A44[8];
    s32 ot;
    u8 pad1A50[0x70];
    s16 code;
    u8 pad1AC2[0x96];
    u8 buf[0xC0];
    f32 cos[91];
} Ctx_c026_01E00F20;

static void func_01E00080_c026();

static s32 func_01E00F20_c026(s32 arg0, s32 code) {
    Ctx_c026_01E00F20 *g = (Ctx_c026_01E00F20 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern s32 func_00202BF0(s32, s32);
    extern f32 func_001A6A88(f32);
    extern V4_c026_01E00F20 *func_001F9D30(s32);
    extern void func_0020EB40(void *);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020BC00(void *, void *);
    s32 n;
    V4_c026_01E00F20 pos;
    s32 (*draw)(void *, Node_c026_01E00F20 *, void *, s32);
    s32 i;

    n = 0;
    g->ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x1D90);
        for (; n < 91; n++) {
            g->cos[n] = func_001A6A88(3.1415927f * n / 180.0f);
        }
        g->code = code;
        g->timer = 126;
        for (i = 15; i < 16; i++) {
            g->tex[i] = func_00202BF0(4, i);
        }
        return 0;
    }
    func_01E00080_c026(g, 0);
    for (i = 0; i < 50; i++) {
        if (g->node[i].used != 0) {
            if (g->node[i].fn != NULL) {
                g->node[i].fn(g, &g->node[i]);
            }
        }
    }
    pos.x = pos.y = pos.z = 0.0f;
    pos.y = 50.0f;
    pos = *func_001F9D30(0);
    func_00205C40((s32)g->rot);
    g->rot[0] += 0x4000;
    g->sc.y = 0.2f;
    g->sc.x = 0.7f;
    g->sc.z = 0.7f;
    for (i = 0; i < 50; i++) {
        if (g->node[i].used != 0) {
            n++;
            func_0020EB40(g->cam);
            func_0020C940(g, &g->sc, g->rot, &pos);
            func_0020BC00(g->cam, g);
            draw = g->node[i].draw;
            if (draw != NULL) {
                draw(g, &g->node[i], g->buf, 0);
                draw(g, &g->node[i], g->buf, 1);
            }
        }
    }
    if (--g->timer <= 0) {
        return 8;
    }
    return 0;
}

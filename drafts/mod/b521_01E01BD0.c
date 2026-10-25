#include "common.h"

/* shape b521:01E01BD0, 286 insns: the scene's main step. id >= 0: set up (clear 0x57B0 bytes, textures 4:14..15 and
   5:0..2, four joints, a 360-frame timer, 256 random tilts -15..14 with 100..179 cleared); else run the 25 ribbons
   (update, draw twice) and the 150 effects (step each, then draw the 0x1E01440 ones as a lit sprite at their swing
   and the 0x1E01790 ones as tilted sparks), count the timer down and pick the next scene by the frame at 0x5536 */

typedef struct {
    s16 x, y, w, h;
    u8 pad8[8];
} Rect_b521_01E01BD0;

typedef struct {
    u8 pad0[0x88];
    s16 on;
    u8 pad8A[0xE];
} Rib_b521_01E01BD0;

typedef struct {
    u8 pad0[0xA];
    s16 hA;
    u8 padC[4];
    f32 x;
    f32 y;
    f32 z;
    u8 pad1C[0x44 - 0x1C];
    void *fn;
    f32 swing;
    u8 pad4C[0x56 - 0x4C];
    s16 tex;
    s16 on;
    s16 ang;
    u8 pad5C[0x14];
} Fx_b521_01E01BD0;

typedef struct {
    u8 pad0[0x20];
    f32 px;
    f32 py;
    f32 pz;
    u8 pad2C[0x80 - 0x2C];
    s32 t80;
    u8 pad84[4];
    s32 tex;
    u8 pad8C[0x94 - 0x8C];
    Rect_b521_01E01BD0 rect;
    u8 padA4[0xB8 - 0xA4];
    s16 mode;
    u8 padBA[4];
    s16 hBE;
    s16 hC0;
    u8 padC2[0xD8 - 0xC2];
    u8 objD8[0x290 - 0xD8];
    s32 tex4[16];
    Rib_b521_01E01BD0 rib[25];
    u8 pad11A8[0x11B0 - 0x11A8];
    Fx_b521_01E01BD0 fx[150];
    u8 pad5350[0x5490 - 0x5350];
    s32 tex5[8];
    s32 timer;
    u8 pad54B4[8];
    s32 t54BC;
    u8 pad54C0[0x5518 - 0x54C0];
    s16 joint[4];
    u8 pad5520[0x5534 - 0x5520];
    s16 id;
    s16 frame;
    s8 tilt[256];
    u8 obj5638[0x10];
} Scene_b521_01E01BD0;

#pragma opt_propagation off
static s32 func_01E01BD0_b521(Scene_b521_01E01BD0 *g0, s32 id) {
    Scene_b521_01E01BD0 *g = g0;
    extern void b521_01E02310();
    extern void func_00107C10(void *);
    extern void func_00106080(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s32, s32);
    extern s32 func_001F5560(s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_00207500();
    extern void func_00195108(void *, s32);
    extern s32 func_00202BF0(s32, s32);
    Vec4f c;
    Rect_b521_01E01BD0 r0;
    Rect_b521_01E01BD0 r1;
    u8 tmp[0x90];
    s32 n;
    s32 i;

    n = 0;
    g->t54BC = func_00207500();
    g->t80 = func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x57B0);
        func_00107C10(g->obj5638);
        func_00107C10(g->objD8);
        g->joint[0] = func_001F5560(func_001F53A0(), 1, 1);
        for (i = 14; i < 16; i++) {
            g->tex4[i] = func_00202BF0(4, i);
        }
        for (i = 0; i < 3; i++) {
            g->tex5[i] = func_00202BF0(5, i);
        }
        g->joint[1] = func_001F5560(func_001F5380(), 1, 1);
        g->joint[2] = func_001F5560(func_001F53A0(), 0x37, 0);
        g->joint[3] = func_001F5560(func_001F53A0(), 0x3D, 0);
        g->id = id;
        g->timer = 360;
        for (i = 0; i < 256; i++) {
            g->tilt[i] = func_0019A5C8() % 30 - 15;
        }
        for (i = 100; i < 180; i++) {
            g->tilt[i] = 0;
        }
        return 0;
    }
    func_01E00CE0_b521((void *)g, 0);
    for (i = 0; i < 25; i++) {
        if (g->rib[i].on != 0) {
            func_01E010C0_b521((void *)g, (void *)&g->rib[i]);
        }
    }
    for (i = 0; i < 25; i++) {
        if (g->rib[i].on != 0) {
            b521_01E02310(g, &g->rib[i], tmp, 0);
            b521_01E02310(g, &g->rib[i], tmp, 1);
        }
    }
    for (i = 0; i < 150; i++) {
        if (g->fx[i].on != 0 && g->fx[i].fn != NULL) {
            ((s32 (*)(void *, void *))g->fx[i].fn)(g, &g->fx[i]);
        }
    }
    for (i = 0; i < 150; i++) {
        if (g->fx[i].on != 0) {
            n++;
            if (g->fx[i].fn == (void *)func_01E01440_b521) {
                g->tex = g->tex5[1];
                func_00106080(&r0, 0x14, g->fx[i].tex, 0);
                g->rect = r0;
                g->rect.x = 0;
                g->rect.y = 0;
                g->rect.w = 0x7F;
                g->rect.h = 0x3F;
                g->hBE = 0;
                c.x = g->fx[i].x + g->fx[i].swing * func_00108030(g->obj5638, g->fx[i].ang, 1);
                c.y = g->fx[i].y;
                c.z = g->fx[i].z + g->fx[i].swing * func_00108030(g->obj5638, g->fx[i].ang, 0);
                func_01E004D0_b521((void *)g, (void *)&g->fx[i], 0x10, c);
            }
            if (g->fx[i].fn == (void *)func_01E01790_b521) {
                func_00106080(&r1, 0x14, g->fx[i].tex, 0);
                g->rect = r1;
                g->tex = g->tex5[2];
                g->mode = 5;
                g->hC0 = g->fx[i].hA;
                g->px = g->fx[i].x;
                g->py = g->fx[i].y;
                g->pz = g->fx[i].z;
                func_01E00790_b521((void *)g, (void *)&g->fx[i], 0x10, g->tilt);
                g->mode = 0;
            }
        }
    }
    if (g->timer != 0) {
        g->timer--;
    }
    if (g->frame == 0xCD) {
        return 1;
    }
    if (g->frame == 0x163) {
        return 4;
    }
    if (g->frame == 0x154) {
        return 2;
    }
    if (g->frame >= 0xD8 && g->frame < 0x14F) {
        return 6;
    }
    if (g->timer <= 0) {
        return 8;
    }
    return 0;
}
#pragma opt_propagation reset

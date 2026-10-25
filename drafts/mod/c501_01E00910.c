#include "common.h"

/* shape c501:01E00910, 165 insns, 1 copy: c501's scene manager: with a scene id (>= 0) it sets up the scene (60-frame
   countdown, grey colour, the sprite and its 24-scaled quad template, the camera view numbers); otherwise it steps
   it: from frame 8 it draws the sprite fading in by 16, grows the glow by 2 to 30 once full, fades the colour out in
   the last 8 frames; returns 2 on frame 32 and 8 when the countdown runs out */

typedef struct Quad_c501_01E00910 {
    Vec4f v[4];
} Quad_c501_01E00910;

typedef struct Scene_c501_01E00910 {
    u8 pad0[0x20];
    Vec4f v20;
    u8 pad30[0x40];
    s32 w70;
    s32 w74;
    u8 col78[4];
    f32 glow;
    Vec4f quad[4];
    u8 padC0[0x40];
    u32 flags;
    s32 count;
    s32 frame;
    s32 id;
    s32 cam0;
    s32 cam1;
    u8 col[4];
} Scene_c501_01E00910;

#pragma opt_propagation off
static s32 func_01E00910_c501(Scene_c501_01E00910 *g0, s32 id) {
    Scene_c501_01E00910 *g = g0;
    extern Quad_c501_01E00910 D_01E00C00_c501;
    extern s32 func_001F5380();
    extern s32 func_00103260();
    s32 t[4];
    Quad_c501_01E00910 q;
    s32 ot;
    s32 i;
    Vec4f *src;
    Vec4f *dst;

    ot = (s32)func_00207500();
    if (id >= 0) {
        func_00195108((s32)g, 0x120);
        g->flags = 0;
        g->count = 60;
        g->frame = 0;
        g->id = id;
        g->col[0] = 0x80;
        g->col[1] = 0x80;
        g->col[2] = 0x80;
        g->col[3] = 0xFF;
        func_00103890(g);
        func_00103260(t, 0);
        g->w70 = t[0];
        g->w74 = 0;
        g->col78[2] = 0x40;
        g->col78[1] = 0x50;
        g->col78[0] = 0x60;
        g->col78[3] = 0;
        q = D_01E00C00_c501;
        for (i = 0, src = q.v, dst = g->quad; i < 4; i++, src++, dst++) {
            dst->x = 24.0f * src->x;
            dst->y = src->y;
            dst->z = 24.0f * src->z;
        }
        g->glow = 0.0f;
        g->cam0 = func_001F5380() & 0xFF;
        g->cam1 = func_001F5380() >> 8;
        func_001E10F0(g->cam0, g->cam1, 0, &g->v20);
        return 0;
    }
    func_001038D0(g);
    if (g->count > 7) {
        func_01E001E0_c501(ot, (void *)&g->w70, (void *)g);
        if (g->col78[3] < 0xF0) {
            g->col78[3] += 16;
        } else {
            g->col78[3] = 0xFF;
        }
    }
    if (!func_00104520(g->flags, 0x1F)) {
        if (g->col78[3] == 0xFF) {
            if (g->glow < 30.0f) {
                g->glow += 2.0f;
            } else {
                g->glow = 30.0f;
            }
            if (g->count < 8) {
                if (!func_00103470(&g->col[3], 0, 0x20)) {
                    g->flags |= 0x80000000;
                }
                func_01E00080_c501(ot, (void *)g->col);
            }
        }
    }
    g->frame++;
    g->count--;
    if (g->frame == 32) {
        return 2;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}
#pragma opt_propagation reset

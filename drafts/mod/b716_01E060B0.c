#include "common.h"

/* shape b716:01E060B0, 154 insns: between frames lo and hi of its counter, lays four points from joint C toward the
   middle of joints A and B (quarter steps); on frame lo it also sets up the four 0x4C-byte particles at +0x672C (life
   hi - lo, flags, size 180 / 10, grey colour, red-orange second colour); each frame the particles get the points and an
   alpha of 0xC0 on odd frames, 0x70 on even ones */

typedef struct {
    u8 b0[4];
    u8 b4;
    u8 b5;
    u8 pad6;
    u8 b7;
    u8 c8[3];
    u8 padB;
    u8 cC[3];
    u8 alpha;
    f32 f10;
    f32 f14;
    f32 f18;
    Vec4f pos;
    u8 pad2C[0x10];
    s32 w3C;
    s32 w40;
    s32 w44;
    u8 pad48[4];
} Part_b716_01E060B0;

typedef struct {
    u16 t;
    u8 pad2[2];
    s32 skel;
    u8 pad8[0x14];
    s32 ja;
    s32 jb;
    u8 pad24[4];
    s32 jc;
    u8 pad2C[0x6700];
    Part_b716_01E060B0 p[4];
} Fx_b716_01E060B0;

static void func_01E060B0_b716(Fx_b716_01E060B0 *o, s32 lo, s32 hi) {
    extern void func_001F5620(s32, s32, void *);
    extern void func_00101AD0(void *, u8, s32, s32);
    f32 a[4];
    f32 b[4];
    f32 dx;
    f32 dy;
    f32 dz;
    f32 f;
    s32 i;

    if (o->t >= lo) {
        if (o->t > hi) {
            return;
        }
        func_001F5620(o->skel, o->ja, a);
        func_001F5620(o->skel, o->jb, b);
        a[0] = (a[0] + b[0]) / 2.0f;
        a[1] = (a[1] + b[1]) / 2.0f;
        a[2] = (a[2] + b[2]) / 2.0f;
        func_001F5620(o->skel, o->jc, b);
        dx = (a[0] - b[0]) / 4.0f;
        dy = (a[1] - b[1]) / 4.0f;
        dz = (a[2] - b[2]) / 4.0f;
        for (i = 0; i < 4; i++) {
            f = i;
            a[0] = b[0] + dx * f;
            a[1] = b[1] + dy * f;
            a[2] = b[2] + dz * f;
            if (o->t == lo) {
                func_00101AD0(&o->p[i], hi - lo, 0, 0xFF);
                o->p[i].b5 = 0;
                o->p[i].b4 = 0x81;
                o->p[i].b7 = 4;
                o->p[i].f10 = 180.0f;
                o->p[i].f14 = 0.0f;
                o->p[i].f18 = 10.0f;
                o->p[i].cC[0] = 0xC0;
                o->p[i].cC[1] = 0xC0;
                o->p[i].cC[2] = 0xC0;
                o->p[i].c8[2] = 0x80;
                o->p[i].c8[1] = 0x80;
                o->p[i].c8[0] = 0x10;
                o->p[i].w44 = 0;
                o->p[i].w40 = 0;
                o->p[i].w3C = 0;
            }
            if (o->t & 1) {
                o->p[i].alpha = 0xC0;
            } else {
                o->p[i].alpha = 0x70;
            }
            o->p[i].pos = *(Vec4f *)a;
        }
    }
}

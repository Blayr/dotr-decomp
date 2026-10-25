#include "common.h"

/* shape b378:01E02440, 321 insns (B378PAINT_RAIN): mode 0 sets up the packet (texture cell 0x9C of the object's
   0x34, its colour, the scene texture); otherwise objects of kind 10 / 100 first sit on joint 0x3BEC / 0x3BEE while
   the scene count is below 256; then it draws 35 rings of twelve wall quads (30-degree steps, radius 14 / 7 + 25,
   height 0..15), each ring turned a further 0x800, at the object's position plus its 0x8/0xA/0xC tenths, the object's
   turn advanced 0x4000 */

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 dx, dy, dz;
    u8 padE[2];
    Vec4f r;
    u8 pad20[8];
    u8 col[4];
    u8 pad2C[4];
    s16 kind;
    u8 pad32[2];
    s16 cell;
} Obj_b378_01E02440;

typedef struct {
    u8 pad0[0x110];
    u8 m110[0x4C];
    s32 texture;
    u8 pad160[0x3BEC - 0x160];
    s16 j0;
    s16 j1;
    u8 pad3BF0[0xE];
    s16 count;
    u8 pad3C00[4];
    u8 sin[4];
} Scene_b378_01E02440;

static void func_01E02440_b378(Scene_b378_01E02440 *g, Obj_b378_01E02440 *o, s32 pk, s32 mode) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(s32, s32, s32);
    extern void func_00107790(s32, void *, s32);
    extern void func_00108500(s32, void *, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_0020C940(void *, s32, void *, s32);
    extern void func_0020BC00(void *, void *);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern s32 func_00205630(void *, s32, void *, s32, void *);
    extern void func_002075F0(s32, s32, s32);
    Vec4f q[4];
    Vec4f p;
    Vec4f v;
    Vec4f c;
    f32 m[16];
    f32 m2[16];
    f32 depth[4];
    s32 rot[4];
    Vec4f r;
    s32 ot;
    s16 i;
    s16 j;
    s16 a;
    f32 s0;
    f32 c0;
    f32 s1;
    f32 c1;

    ot = (s32)func_00207500();
    if (mode == 0) {
        func_00106080(&c, 0x9C, o->cell, &c);
        func_00109270(pk, 0, 0);
        func_00107790(pk, o->col, 0);
        func_00108500(pk, &c, 0);
        func_00208700((void *)pk, (void *)g->texture, 1);
        return;
    }
    if (o->kind == 10) {
        if (g->count < 256) {
            func_001F5620(func_001F53A0(), g->j0, &v);
            o->x = v.x;
            o->y = v.y;
            o->z = v.z;
        }
    } else if (o->kind == 100) {
        if (g->count < 256) {
            func_001F5620(func_001F53A0(), g->j1, &v);
            o->x = v.x;
            o->y = v.y;
            o->z = v.z;
        }
    }
    rot[1] = 0;
    rot[0] = 0;
    rot[2] = 0;
    p.x = ((o->kind == 10 || o->kind == 100) && g->count < 256) ? v.x : o->x;
    p.x += o->dx / 10.0f;
    p.y = ((o->kind == 10 || o->kind == 100) && g->count < 256) ? v.y : o->y;
    p.y += o->dy / 10.0f;
    p.z = ((o->kind == 10 || o->kind == 100) && g->count < 256) ? v.z : o->z;
    p.z += o->dz / 10.0f;
    r = o->r;
    *(s32 *)&r.z += 0x4000;
    for (i = 0; i < 35; i++) {
        q[0].y = 0.0f;
        func_00108EF0(m, g->m110, &r, &p);
        func_0020C940(m2, 0, rot, 0);
        func_0020BC00(m, m2);
        rot[1] += 0x800;
        for (j = 0, a = 0; j < 12; j++, a += 30) {
            s0 = func_00108030(g->sin, a, 0);
            c0 = func_00108030(g->sin, a, 1);
            s1 = func_00108030(g->sin, a + 30, 0);
            c1 = func_00108030(g->sin, a + 30, 1);
            q[0].y = 14.0f * s0;
            q[0].x = 7.0f * c0 + 25.0f;
            q[0].z = 0.0f;
            q[1].y = 14.0f * s1;
            q[1].x = 7.0f * c1 + 25.0f;
            q[1].z = 0.0f;
            q[2].y = 14.0f * s0;
            q[2].x = 7.0f * c0 + 25.0f;
            q[2].z = 15.0f;
            q[3].y = 14.0f * s1;
            q[3].x = 7.0f * c1 + 25.0f;
            q[3].z = 15.0f;
            if (func_00205630(q, 0x70000000, m, pk, depth) != 0) {
                func_002075F0(pk, ot, 0);
            }
        }
    }
}

#include "common.h"

/* shape b034:01E05A90, 349 insns, 1 copy: draws a ring of up to 18 quads (20 apart, a frame from the scene's table
   each) or, in mode 2, 9 wider ones (40 apart, one fixed frame) between two radii, up to the scene's angle limit,
   blended by flags >> 4, at the object's position and turn; radii from the scene (mode 0) or the object */

typedef struct {
    u8 pad0[0x20];
    s32 rot[4];
    u8 pad30[0x18];
    f32 r0;
    f32 r1;
    u8 pad50[0xA];
    s16 ang;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
} Obj_b034_01E05A90;

typedef struct {
    u8 pad0[0x88];
    s32 tex;
    u8 pad8C[8];
    s32 rm[4];
    u8 padA4[0xC];
    s16 mode;
    u8 padB2[0xC];
    s16 hBE;
    u8 padC0[0xA84C];
    s32 ot;
    u8 padA910[0x10];
    f32 rA920;
    f32 rA924;
    u8 padA928[0x44];
    s16 frame[18];
    u8 padA990[0x70];
    s16 limit;
    u8 padAA02[0x312];
    u8 sin[4];
} Scene_b034_01E05A90;

static void func_01E05A90_b034(Scene_b034_01E05A90 *g, Obj_b034_01E05A90 *o, s32 flags, Vec4f *pos) {
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_002086D0(void *, u64);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00106080(void *, s32, s32, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_001A23B0(f32);
    Vec4f p;
    Vec4f q[4];
    Vec4f v;
    f32 m[16];
    f32 depth[4];
    s32 rm[4];
    s32 rm2[4];
    u8 pk[0x90];
    u8 *pp;
    s16 i;
    s16 a;
    s16 k;
    f32 r0;
    f32 r1;
    f32 s;
    f32 c;

    pp = pk;
    p = *pos;
    a = 0;
    func_00109270(pp, 0, 0);
    func_00107790(pp, o->col, 1);
    func_00107790(pp, o->col2, 2);
    func_00108500(pp, g->rm, g->hBE);
    func_00208700(pp, g->tex, 1);
    if (flags >> 4 == 0) {
        func_002086D0(pp, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(pp, ((u64)(flags >> 4) << 2) | (((u64)0x80 << 32) | 0x40));
    }
    v.x = p.x;
    v.y = p.y;
    v.z = p.z;
    func_00108EF0(m, NULL, o->rot, &v);
    q[0].y = 0.0f;
    q[1].y = 0.0f;
    q[2].y = 0.0f;
    q[3].y = 0.0f;
    if (g->mode == 0) {
        r0 = g->rA920;
        r1 = r0 + g->rA924;
    } else if (g->mode == 1) {
        r1 = o->r1;
        r0 = o->r0;
    } else if (g->mode == 2) {
        r0 = r1 = o->r0;
        q[0].y = o->r1;
        q[1].y = o->r1;
    }
    if (g->mode != 2) {
        for (i = 0; i < 18; i++) {
            func_00106080(rm, 0x14, g->frame[i], NULL);
            *(Vec4f *)g->rm = *(Vec4f *)rm;
            func_00108500(pp, g->rm, g->hBE);
            if (a < g->limit) {
                k = -(o->ang + a + 90);
                s = func_00108030(g->sin, k, 1);
                c = func_00108030(g->sin, k, 0);
                q[2].x = s * r0;
                q[2].z = c * r0;
                q[0].x = s * r1;
                q[0].z = c * r1;
                k = -(o->ang + 20 + a + 90);
                s = func_00108030(g->sin, k, 1);
                c = func_00108030(g->sin, k, 0);
                q[3].x = s * r0;
                q[3].z = c * r0;
                q[1].x = s * r1;
                q[1].z = c * r1;
                if (func_00205630(q, 0x70000000, m, pp, depth) != 0) {
                    func_002075F0(pp, g->ot, func_001A23B0(depth[0]));
                }
            }
            a += 20;
        }
        return;
    }
    if (g->mode == 2) {
        func_00106080(rm2, 0x9B, 0, NULL);
        *(Vec4f *)g->rm = *(Vec4f *)rm2;
        func_00108500(pp, g->rm, g->hBE);
        for (i = 0; i < 9; i++) {
            if (a < g->limit) {
                k = -(o->ang + a + 90);
                s = func_00108030(g->sin, k, 1);
                c = func_00108030(g->sin, k, 0);
                q[2].x = s * r0;
                q[2].z = c * r0;
                q[0].x = s * r1;
                q[0].z = c * r1;
                k = -(o->ang + 20 + a + 90);
                s = func_00108030(g->sin, k, 1);
                c = func_00108030(g->sin, k, 0);
                q[3].x = s * r0;
                q[3].z = c * r0;
                q[1].x = s * r1;
                q[1].z = c * r1;
                if (func_00205630(q, 0x70000000, m, pp, depth) != 0) {
                    func_002075F0(pp, g->ot, func_001A23B0(depth[0]));
                }
            }
            a += 40;
        }
    }
}

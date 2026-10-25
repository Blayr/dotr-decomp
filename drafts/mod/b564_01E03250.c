#include "common.h"

/* shape b564:01E03250, 287 insns: draws n-1 rings of a falling rain trail: for each point pair, 18 angles from -90 by
   10 (radius and 0.6-lowered height from the scene's sine table), four 0.2-nudged copies of the segment each sent as a
   line in the effect colour, its alpha falling by alpha/n per ring */

typedef struct {
    f32 r;
    f32 pad4;
    f32 h;
    u8 padC[0xD8 - 0xC];
    u8 sin[4];
} Game_b564_01E03250;

typedef struct {
    u8 pad0[6];
    s16 n;
    u8 pad8[0x20];
    u8 col[4];
} Obj_b564_01E03250;

typedef struct {
    f32 x, y, z, w;
} V4_b564_01E03250;

static void func_01E03250_b564(Game_b564_01E03250 *g, Obj_b564_01E03250 *o, V4_b564_01E03250 *pt, V4_b564_01E03250 *ofs) {
    extern s32 func_00207500(void);
    extern void func_001092E0(void *, s32);
    extern void func_001094F0(void *);
    extern void func_00107990(void *, void *, s32);
    extern f32 func_00108030(void *, s32, s32);
    extern void func_00107070(void *, s32, f32);
    extern s32 func_00205630(void *, s32, s32, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    u8 pk[0x94];
    u8 col[4];
    V4_b564_01E03250 d;
    V4_b564_01E03250 o4;
    V4_b564_01E03250 seg[4];
    f32 depth;
    s32 ot;
    s32 n;
    s32 last;
    s32 i;
    s32 k;
    s32 m;
    s16 ang;
    s16 c;
    f32 f;
    f32 rx;
    f32 ry;
    f32 h;
    f32 y;
    f32 lo;

    ot = func_00207500();
    n = o->n;
    func_001092E0(pk, 0);
    func_001094F0(pk);
    f = 0.0f;
    i = 0;
    col[0] = o->col[0];
    col[1] = o->col[1];
    col[2] = o->col[2];
    col[3] = o->col[3];
    d = *pt;
    last = n - 1;
    o4 = *ofs;
    d.x -= o4.x;
    d.y -= o4.y;
    d.z -= o4.z;
    d.x = g->r;
    d.y = -d.y;
    d.z = g->h;
    h = d.z;
    y = d.y;
    lo = 0.6f * h;
    for (; i < last; i++) {
        func_00107990(pk, col, 1);
        col[3] -= o->col[3] / n;
        func_00107990(pk, col, 2);
        ang = -0x5A;
        for (k = 0; k < 0x12; k++) {
            rx = d.x * func_00108030(g->sin, ang, 0);
            ry = h * func_00108030(g->sin, ang, 1) - lo;
            for (m = 0; m < 4; m++) {
                seg[0].x = pt->x;
                seg[0].y = pt->y;
                seg[0].z = pt->z;
                seg[1].x = pt->x;
                seg[1].y = pt->y;
                seg[1].z = pt->z;
                seg[2].x = pt[1].x;
                seg[2].y = pt[1].y;
                seg[2].z = pt[1].z;
                seg[3].x = pt[1].x;
                seg[3].y = pt[1].y;
                seg[3].z = pt[1].z;
                func_00107070(seg, 0, rx);
                func_00107070(seg, 2, ry);
                func_00107070(seg, 1, y);
                if (m == 0) {
                    seg[0].z += 0.2f;
                    seg[2].z += 0.2f;
                } else if (m == 1) {
                    seg[0].z -= 0.2f;
                    seg[2].z -= 0.2f;
                } else if (m == 2) {
                    seg[0].x += 0.2f;
                    seg[2].x += 0.2f;
                } else if (m == 3) {
                    seg[0].x -= 0.2f;
                    seg[2].x -= 0.2f;
                }
                if (func_00205630(seg, 0x70000000, 0, pk, &depth) != 0) {
                    func_002075F0(pk, ot, (s32)depth);
                }
                c += 0x1E;
            }
            ang += 10;
        }
        pt++;
        f += 1.0f;
    }
}

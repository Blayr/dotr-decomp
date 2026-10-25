#include "common.h"

/* shape b701:01E037D0, 282 insns (B701KPOINT_RAIN_2): draws a falling-light column through the object's points: for
   each segment between point i and i+1 (the colour's alpha dropping by alpha / n per segment) it lays 18 thin
   strips round the column (angles -90 step 10, radius from the owner's 0x0/0x8), each drawn four times nudged 0.2
   in +z, -z, +x, -x; the strip height is the first point's height above the given centre */

typedef struct {
    u8 r, g, b, a;
} Col_b701_01E037D0;

typedef struct {
    f32 sx;
    u8 pad4[4];
    f32 sz;
    u8 padC[0xCC];
    u8 sin[4];
} Self_b701_01E037D0;

typedef struct {
    u8 pad0[6];
    s16 n;
    u8 pad8[0x20];
    Col_b701_01E037D0 col;
} Obj_b701_01E037D0;

static void func_01E037D0_b701(Self_b701_01E037D0 *self, Obj_b701_01E037D0 *obj, Vec4f *pt, Vec4f *at) {
    extern void func_001092E0(void *, s32);
    extern void func_001094F0(void *);
    extern void func_00107990(void *, void *, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern void func_00107070(void *, s32, f32);
    extern s32 func_00205630(void *, s32, void *, void *, void *);
    extern void func_00109380(void *, s32);
    extern void func_002075F0(void *, s32, s32);
    Vec4f depth;
    Vec4f q[4];
    Vec4f d;
    Vec4f c;
    u8 pk[0x94];
    Col_b701_01E037D0 col;
    s32 ot;
    s32 n;
    s32 i;
    s32 last;
    s32 k;
    s32 j;
    s16 ang;
    f32 h;
    f32 xr;
    f32 zr;

    ot = (s32)func_00207500();
    n = obj->n;
    func_001092E0(pk, 0);
    func_001094F0(pk);
    i = 0;
    col = obj->col;
    d = *pt;
    last = n - 1;
    c = *at;
    d.x -= c.x;
    d.y -= c.y;
    d.z -= c.z;
    d.x = self->sx;
    d.y = -d.y;
    d.z = self->sz;
    h = d.y;
    for (; i < last; i++) {
        func_00107990(pk, &col, 1);
        col.a -= obj->col.a / n;
        func_00107990(pk, &col, 2);
        for (k = 0, ang = -90; k < 18; k++, ang += 10) {
            xr = d.x * func_00108030(self->sin, ang, 0);
            zr = d.z * func_00108030(self->sin, ang, 1);
            for (j = 0; j < 4; j++) {
                q[0].x = pt[0].x;
                q[0].y = pt[0].y;
                q[0].z = pt[0].z;
                q[1].x = pt[0].x;
                q[1].y = pt[0].y;
                q[1].z = pt[0].z;
                q[2].x = pt[1].x;
                q[2].y = pt[1].y;
                q[2].z = pt[1].z;
                q[3].x = pt[1].x;
                q[3].y = pt[1].y;
                q[3].z = pt[1].z;
                func_00107070(q, 0, xr);
                func_00107070(q, 2, zr);
                func_00107070(q, 1, h);
                switch (j) {
                case 0:
                    q[0].z += 0.2f;
                    q[2].z += 0.2f;
                    break;
                case 1:
                    q[0].z -= 0.2f;
                    q[2].z -= 0.2f;
                    break;
                case 2:
                    q[0].x += 0.2f;
                    q[2].x += 0.2f;
                    break;
                case 3:
                    q[0].x -= 0.2f;
                    q[2].x -= 0.2f;
                    break;
                }
                if (func_00205630(q, 0x70000000, 0, pk, &depth) != 0) {
                    func_00109380(pk, 1);
                    func_002075F0(pk, ot, 0);
                }
            }
        }
        pt++;
    }
}

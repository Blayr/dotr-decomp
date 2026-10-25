/* func_00108030 really takes an s16 angle (functions.h says s32): hide that prototype */
#include "common.h"

/* shape b390:01E015E0, 316 insns: b016:01E014F0's ring of bands, flat (y 0), each corner turned by the object's two
   angles (func_00108BE0); start angle 180 unless o->fB0 */

typedef struct Cam_b390_01E015E0 {
    u8 pad0[0x20];
    Vec4f pos;
    u8 pad30[0x18];
    f32 w0;
    f32 w1;
    u8 pad50[0xA];
    s16 step;
    s16 n;
    u8 pad5E[2];
    u8 uv0[4];
    u8 uv1[4];
} Cam_b390_01E015E0;

typedef struct Obj_b390_01E015E0 {
    u8 pad0[0x20];
    f32 f20;
    f32 f24;
    u8 pad28[0x58];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    u8 rect[0x1C];
    s16 fB0;
    u8 padB2[6];
    s16 count;
    u8 padBA[4];
    s16 fBE;
    u8 padC0[0x18];
    u8 table[0x10];
} Obj_b390_01E015E0;

typedef struct Uv_b390_01E015E0 {
    f32 u, v;
} Uv_b390_01E015E0;

typedef struct Vtx_b390_01E015E0 {
    Uv_b390_01E015E0 st;
    u64 rgba;
    u64 xyz;
} Vtx_b390_01E015E0;

typedef struct Pk_b390_01E015E0 {
    u8 hdr[0x10];
    Vtx_b390_01E015E0 v[4];
    u8 pad70[0x20];
} Pk_b390_01E015E0;

static void func_01E015E0_b390(Obj_b390_01E015E0 *o, Cam_b390_01E015E0 *cam, s32 flags, Vec4f c) {
    extern void func_00108EF0();
    extern s32 func_00109270();
    extern Vec4f func_00108BE0(Vec4f *, s32, f32, f32);
    s32 nn;
    s32 k;
    s16 ang;
    Pk_b390_01E015E0 *p;
    f32 w0;
    s32 n;
    s32 idx;
    s32 i;
    f32 w1;
    s16 sel;
    s32 mode;

    Vec4f pts[4];
    Vec4f a;
    Vec4f s;
    f32 m[4][4];
    f32 out[4];
    Vec4f r1;
    Vec4f r2;
    Vec4f r3;
    Pk_b390_01E015E0 pk;
    Uv_b390_01E015E0 uv0;
    Uv_b390_01E015E0 uv1;
    Uv_b390_01E015E0 uv2;
    Uv_b390_01E015E0 uv3;

    p = &pk;
    n = cam->n;
    ang = 0;
    func_00107990(p, cam->uv0, 2);
    func_00107990(p, cam->uv1, 1);
    sel = flags >> 4;
    func_00109270(p, 0, 0);
    func_00107790(p, cam->uv0, 0);
    if (sel == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((s64)sel << 2) | (((u64)0x80 << 32) | 0x40));
    }
    func_00108500(p, o->rect, o->fBE);
    func_00208700(p, (void *)o->f88, 1);
    func_00107740(&uv0, cam->uv0);
    p->v[0].st = uv0;
    func_00107740(&uv1, cam->uv1);
    p->v[2].st = uv1;
    func_00107740(&uv2, cam->uv0);
    p->v[1].st = uv2;
    func_00107740(&uv3, cam->uv1);
    p->v[3].st = uv3;
    s.x = 0.1f;
    s.y = 0.1f;
    s.z = 0.1f;
    a.x = c.x;
    a.y = c.y;
    a.z = c.z;
    func_00108EF0(m, &s, NULL, &a);
    w0 = cam->w0;
    w1 = cam->w1;
    if (o->fB0 == 0) {
        ang = 180;
    } else {
        ang = 0;
    }
    nn = (s16)n;
    mode = flags & 0xF;
    for (i = 0; i < o->count; i++) {
        pts[0].y = 0.0f;
        pts[1].y = 0.0f;
        pts[2].y = 0.0f;
        pts[3].y = 0.0f;
        k = ang;
        pts[0].x = w0 * func_00108030((s32)o->table, k, 1);
        pts[0].z = w0 * func_00108030((s32)o->table, k, 0);
        pts[2].x = w1 * func_00108030((s32)o->table, k, 1);
        pts[2].z = w1 * func_00108030((s32)o->table, k, 0);
        idx = nn + k;
        pts[1].x = w0 * func_00108030((s32)o->table, idx, 1);
        pts[1].z = w0 * func_00108030((s32)o->table, idx, 0);
        pts[3].x = w1 * func_00108030((s32)o->table, idx, 1);
        pts[3].z = w1 * func_00108030((s32)o->table, idx, 0);
        pts[0] = func_00108BE0(&pts[0], 1, o->f24, o->f20);
        r1 = func_00108BE0(&pts[1], 1, o->f24, o->f20);
        pts[1] = r1;
        r2 = func_00108BE0(&pts[2], 1, o->f24, o->f20);
        pts[2] = r2;
        r3 = func_00108BE0(&pts[3], 1, o->f24, o->f20);
        pts[3] = r3;
        if (mode == 0) {
            if (func_00205630((s32)pts, 0x70000000, (s32)m, (s32)p, out) != 0) {
                func_002075F0((s32)p, o->f80, func_001A23B0(out[0]));
            }
        } else if (mode == 1) {
            if (func_00205630((s32)pts, 0x70000000, (s32)m, (s32)p, out) != 0) {
                func_00109380(p, 1);
                func_002075F0((s32)p, o->f80, 0);
            }
        }
        ang += cam->step;
    }
}

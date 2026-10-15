#include "common.h"

/* shape b000:01E00100, 38 insns, 169 copies: one colour into the four vertices of a quad (q = 1.0) */

typedef struct Src_b000_01E00100 {
    u8 b, g, r, a;
} Src_b000_01E00100;

typedef struct Col_b000_01E00100 {
    u8 r, g, b, a;
    f32 q;
} Col_b000_01E00100;

typedef struct Vtx_b000_01E00100 {
    u8 pad[0x10];
    Col_b000_01E00100 c;
} Vtx_b000_01E00100;


/* static in its module (callers that include this file #define OVL_LOCAL static first) */

static void func_01E00080_b543(Vtx_b000_01E00100 *v, Src_b000_01E00100 *s) {
    v[0].c.r = s->r;
    v[0].c.g = s->g;
    v[0].c.b = s->b;
    v[0].c.a = s->a;
    v[0].c.q = 1.0f;
    v[1].c.r = s->r;
    v[1].c.g = s->g;
    v[1].c.b = s->b;
    v[1].c.a = s->a;
    v[1].c.q = 1.0f;
    v[2].c.r = s->r;
    v[2].c.g = s->g;
    v[2].c.b = s->b;
    v[2].c.a = s->a;
    v[2].c.q = 1.0f;
    v[3].c.r = s->r;
    v[3].c.g = s->g;
    v[3].c.b = s->b;
    v[3].c.a = s->a;
    v[3].c.q = 1.0f;
}

/* shape b000:01E03A30, 81 insns, 30 copies: finds the last free slot of a point trail, then pushes a new
   point at the front (every older point moves one slot back). */

typedef struct {
    f32 x, y, z;
    u8 c;
    u8 d;
    s16 e;
} Pt_b000_01E03A30;

typedef struct {
    u8 pad0[7];
    u8 c;
    u8 pad8[0x1A];
    u8 kind;
    u8 pad23[3];
    s16 limit;
    s16 count;
    s16 idx;
} Obj_b000_01E03A30;

static s32 func_01E00120_b543(Obj_b000_01E03A30 *obj, Pt_b000_01E03A30 *pts, f32 *pos) {
    s32 i;
    Pt_b000_01E03A30 *p;
    Pt_b000_01E03A30 *q;
    s32 j;

    i = obj->idx;
    if (i > -1) {
        p = &pts[i];
        do {
            if (p->e > obj->limit && func_00103470(&p->c, 0, obj->kind) == 0 && p[-1].c == 0) {
                obj->idx = i;
            }
            i--;
            p--;
        } while (i > -1);
    }
    if (obj->idx < obj->count - 1) {
        obj->idx++;
        j = obj->idx;
        if (j > 0) {
            q = &pts[j];
            do {
                j--;
                q->x = q[-1].x;
                q->y = q[-1].y;
                q->z = q[-1].z;
                q->d = q[-1].d;
                q->e = q[-1].e;
                q->c = q[-1].c;
                q--;
            } while (j > 0);
        }
        pts->x = pos[0];
        pts->y = pos[1];
        pts->z = pos[2];
        pts->d = 0;
        pts->e = 0;
        pts->c = obj->c;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b543", func_01E00270_b543);

INCLUDE_ASM("asm/nonmatchings/mod/b543", func_01E00C30_b543);

/* shape b543:01E04F30, 45 insns: refresh the scene's camera (0xAE40, func_0020DEF0), copy it, aim the copy along
   (0, 50, 0) / (0, 0, -c) with c the scene's s32 at 0xC, load it (func_0020E360) and func_0020EC60(arg) */

typedef struct {
    f32 m[16];
    Vec4f a;
    Vec4f b;
    __int128 pad60[3];
} Cam_b543_01E04F30;

typedef struct {
    u8 pad0[0xC];
    s32 c;
    u8 pad10[0xAE40 - 0x10];
    Cam_b543_01E04F30 cam;
} Scene_b543_01E04F30;

extern Scene_b543_01E04F30 *D_01E05100_b543;

static void func_01E04F30_b543(s32 arg) {
    Scene_b543_01E04F30 *s;
    Cam_b543_01E04F30 cam;

    s = D_01E05100_b543;
    func_0020DEF0(&s->cam);
    cam = s->cam;
    cam.a.x = 0.0f;
    cam.a.y = 50.0f;
    cam.a.z = 0.0f;
    cam.a.w = 1.0f;
    cam.b.x = 0.0f;
    cam.b.y = 0.0f;
    cam.b.z = -1.0f * s->c;
    cam.b.w = 1.0f;
    func_0020E360(&cam);
    func_0020EC60(arg);
}

INCLUDE_ASM("asm/nonmatchings/mod/b543", func_01E04FF0_b543);

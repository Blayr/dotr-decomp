#include "common.h"

/* shape b357:01E01CD0, 299 insns (IWTThunder2): draws a lightning ribbon through the object's points: per segment a
   quad from point i to i+1, widened by the object's 0x38 across the camera (rotation / 180, y negated), the near
   edge in the current colours and the far edge with both alphas lowered by alpha / (n - 1); world matrix at the
   object's position, scale its 0x8/0xA/0xC tenths */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b357_01E01CD0;

typedef struct {
    Rgbaq_b357_01E01CD0 c;
    f32 s, t;
    u64 xyz;
} Vtx_b357_01E01CD0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b357_01E01CD0 v[4];
    u8 tail[0x20];
} Pkt_b357_01E01CD0;

typedef struct {
    u8 r, g, b, a;
} Col_b357_01E01CD0;

typedef struct {
    u8 pad0[0x88];
    void *texture;
    u8 pad8C[8];
    u8 rect[0x2A];
    s16 mode;
    u8 padC0[0x18];
    u8 fD8[4];
} Self_b357_01E01CD0;

typedef struct {
    s16 x, y, z;
    s16 n;
    s16 sx, sy, sz;
    u8 padE[0x1A];
    Col_b357_01E01CD0 c0;
    Col_b357_01E01CD0 c1;
    u8 pad30[8];
    s16 w;
} Obj_b357_01E01CD0;

static void func_01E01CD0_b357(Self_b357_01E01CD0 *self, Obj_b357_01E01CD0 *obj, Vec4f *pt) {
    extern void func_00109270(void *, s32, s32);
    extern Rgbaq_b357_01E01CD0 func_00107740(void *);
    extern void func_00108500(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern void func_00109100(void *, void *, s32, void *);
    extern void func_00106B50(void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    s32 i;
    s32 last;
    f32 d[4];
    Vec4f pos;
    Vec4f sc;
    f32 m[16];
    s32 rot[4];
    Vec4f p[4];
    Vec4f q[4];
    Pkt_b357_01E01CD0 pk __attribute__((aligned(8)));
    Col_b357_01E01CD0 c0;
    Col_b357_01E01CD0 c1;
    s32 ot;
    s32 j;
    s16 n;
    Pkt_b357_01E01CD0 *pp;

    n = obj->n;
    ot = (s32)func_00207500();
    pp = &pk;
    func_00109270(pp, 0, 0);
    pp->v[0].c = func_00107740(&obj->c0);
    pp->v[1].c = func_00107740(&obj->c1);
    pp->v[2].c = func_00107740(&obj->c0);
    pp->v[3].c = func_00107740(&obj->c1);
    func_00108500(pp, self->rect, self->mode);
    func_00208700(pp, self->texture, 1);
    c0 = obj->c0;
    c1 = obj->c1;
    pos.x = obj->x;
    pos.y = obj->y;
    pos.z = obj->z;
    sc.x = obj->sx;
    sc.y = obj->sy;
    sc.z = obj->sz;
    sc.x /= 10.0f;
    sc.y /= 10.0f;
    sc.z /= 10.0f;
    func_00205C40((s32)rot);
    rot[1] /= 180;
    rot[1] = -rot[1];
    func_00108EF0(m, &sc, 0, &pos);
    last = n - 1;
    for (i = 0; i < last; i++) {
        pp->v[0].c = func_00107740(&c0);
        pp->v[1].c = func_00107740(&c1);
        c0.a -= obj->c0.a / last;
        c1.a -= obj->c1.a / last;
        pp->v[2].c = func_00107740(&c0);
        pp->v[3].c = func_00107740(&c1);
        for (j = 0; j < 1; j++) {
            func_00108CE0(q, obj->w, 0);
            func_00109100(q, rot, 0, self->fD8);
            p[0].x = pt[0].x;
            p[0].y = pt[0].y;
            p[0].z = pt[0].z;
            p[1].x = pt[0].x;
            p[1].y = pt[0].y;
            p[1].z = pt[0].z;
            p[2].x = pt[1].x;
            p[2].y = pt[1].y;
            p[2].z = pt[1].z;
            p[3].x = pt[1].x;
            p[3].y = pt[1].y;
            p[3].z = pt[1].z;
            func_00106B50(&p[0], &q[0]);
            func_00106B50(&p[1], &q[1]);
            func_00106B50(&p[2], &q[2]);
            func_00106B50(&p[3], &q[3]);
            if (func_00205630(p, 0x70000000, m, pp, d) != 0) {
                func_002075F0(pp, ot, (u32)d[0]);
            }
        }
        pt++;
    }
}

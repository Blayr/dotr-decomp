#include "common.h"

/* shape b774:01E04530, 179 insns: a two-blade cross at the object (two quads 180 apart, each running from radius 3 to
   radius 25 over a 10-wide slice), drawn twice; mode 0 sets up the packet with the first colour on the inner and the
   second on the outer corners */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b774_01E04530;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    struct {
        Rgbaq_b774_01E04530 c;
        u64 p;
    } v[4];
} Pkt_b774_01E04530;

typedef struct {
    u8 pad0[0x36DC];
    s32 ot;
    u8 pad36E0[0x1C];
    f32 depth;
    u8 pad3700[0x24];
    u8 trig[1];
} Ctx_b774_01E04530;

typedef struct {
    s16 x, y, z;
    u8 pad6[0xA];
    s32 rot[3];
    u8 pad1C[0xC];
    u8 col[4];
    u8 col2[4];
} Obj_b774_01E04530;

static void func_01E04530_b774(Ctx_b774_01E04530 *c, Obj_b774_01E04530 *o, Pkt_b774_01E04530 *p, s32 mode) {
    extern void func_001092E0(void *, s32);
    extern void func_001094F0(void *);
    extern Rgbaq_b774_01E04530 func_00107740(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f pos;
    f32 m[16];
    s32 k;
    s32 n;
    s16 a;
    s16 t;

    if (mode == 0) {
        func_001092E0(p, 0);
        func_001094F0(p);
        p->v[0].c = func_00107740(o->col);
        p->v[1].c = func_00107740(o->col);
        p->v[2].c = func_00107740(o->col2);
        p->v[3].c = func_00107740(o->col2);
        return;
    }
    pos.x = o->x;
    pos.y = o->y;
    pos.z = o->z;
    func_00108EF0(m, 0, o->rot, &pos);
    for (n = 0; n < 2; n++) {
        quad[0].y = 0.0f;
        quad[1].y = 0.0f;
        quad[2].y = 0.0f;
        quad[3].y = 0.0f;
        a = 0;
        for (k = 0; k < 1; k++) {
            quad[2].x = 25.0f * func_00108030(c->trig, a, 1);
            quad[2].z = 25.0f * func_00108030(c->trig, a, 0);
            quad[0].x = 3.0f * func_00108030(c->trig, a, 1);
            quad[0].z = 3.0f * func_00108030(c->trig, a, 0);
            t = a + 10;
            quad[3].x = 25.0f * func_00108030(c->trig, t, 1);
            quad[3].z = 25.0f * func_00108030(c->trig, t, 0);
            quad[1].x = 3.0f * func_00108030(c->trig, t, 1);
            quad[1].z = 3.0f * func_00108030(c->trig, t, 0);
            if (func_00205630(quad, 0x70000000, m, p, &c->depth) != 0) {
                func_002075F0(p, c->ot, (u32)c->depth);
            }
            a += 180;
        }
    }
}

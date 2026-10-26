#include "common.h"

/* shape b847:01E06FB0 (B847PAINT_RAIN20), 178 insns, 1 copy: b232:01E01B90's draw with one quad: two-colour packet,
   the scene rect and texture, blend by the mode's high nibble; placed at the point turned by the object; the frame
   rect comes from b847:01E009B0 (20 frames, by the object's 0x56); one quad of size f48, twisted by 0x5C, pushed f4C
   out at angle 0x5A - 200 (trig g+0xD8F0), depth-tested into the scene's ordering table */

typedef struct {
    u8 pad0[0x20];
    s32 rot[4];
    u8 pad30[0x18];
    f32 size;
    f32 r;
    u8 pad50[6];
    s16 h56;
    u8 pad58[2];
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b847_01E06FB0;

typedef struct {
    u8 pad0[0x88];
    s32 tex;
    u8 pad8C[8];
    Vec4f rect;
    u8 padA4[0x1A];
    s16 frame;
    u8 padC0[0xD62C - 0xC0];
    s32 ot;
    u8 padD630[0xD8F0 - 0xD630];
    u8 trig[1];
} Game_b847_01E06FB0;

static void func_01E06FB0_b847(Game_b847_01E06FB0 *g, Obj_b847_01E06FB0 *o, s32 mode, Vec4f *in) {
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern void func_00108CE0(void *, f32, f32);
    extern void func_00109100(void *, void *, s32, void *);
    extern void func_00107070(void *, s32, f32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern Vec4f b847_01E009B0(s32, s32, s32);
    f32 pos[4];
    Vec4f q[4];
    f32 v[4];
    f32 m[16];
    f32 depth[4];
    s32 tw[4];
    Vec4f rc;
    struct {
        u8 pk[0x70];
        u8 tail[0x20];
    } buf;
    s32 k;
    s16 i;
    s16 s;
    s16 a;
    void *p = &buf;
    f32 r;
    f32 c;
    f32 sn;

    *(Vec4f *)pos = *in;
    s = 0;
    func_00109270(p, 0, 0);
    func_00107790(p, o->col, 1);
    func_00107790(p, o->col2, 2);
    func_00108500(p, &g->rect, g->frame);
    func_00208700(p, g->tex, 1);
    k = mode >> 4;
    if (k == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((s64)k << 2) | (((u64)0x80 << 32) | 0x40));
    }
    v[0] = pos[0];
    v[1] = pos[1];
    v[2] = pos[2];
    func_00108EF0(m, 0, o->rot, v);
    q[0].y = 0.0f;
    q[1].y = 0.0f;
    q[2].y = 0.0f;
    q[3].y = 0.0f;
    r = o->r;
    tw[2] = o->h5C;
    rc = b847_01E009B0(0x14, o->h56, 0);
    g->rect = rc;
    func_00108500(p, &g->rect, g->frame);
    for (i = 0; i < 1; i++) {
        a = o->h5A + s - 200;
        c = r * func_00108030(g->trig, a, 1);
        sn = r * func_00108030(g->trig, a, 0);
        func_00108CE0(q, o->size, o->size);
        func_00109100(q, tw, 2, g->trig);
        func_00107070(q, 0, c);
        func_00107070(q, 1, sn);
        if (func_00205630(q, 0x70000000, m, p, depth) != 0) {
            func_002075F0(p, g->ot, (u32)depth[0]);
        }
        s += 10;
    }
}

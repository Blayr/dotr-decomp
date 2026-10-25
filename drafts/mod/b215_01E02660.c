#include "common.h"

/* shape b215:01E02660 (B215_OBJ_MOVE_203_1), 322 insns, 1 copy: a 24-segment flat ring of radius r at height h: the
   packet takes both colours, the ring is placed at the object's point, and each segment (15 degrees wide) that is on
   screen gets screen-mapped texture coordinates (the outer edge from the object's screen row, clamped at 0, the inner
   edge from the bottom row, clamped at 1) and is sent */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b215_01E02660;

typedef struct {
    Rgbaq_b215_01E02660 c;
    f32 s, t;
    u16 x, y;
    u32 z;
} Vtx_b215_01E02660;

typedef struct {
    u8 pad0[0x10];
    Vtx_b215_01E02660 v[4];
} Pkt_b215_01E02660;

typedef struct {
    u8 pad0[0xA];
    s16 hA;
    u8 padC[4];
    Vec4f p;
    u8 pad20[0x14];
    f32 h;
    u8 pad38[0x10];
    f32 r;
    u8 pad4C[0xE];
    s16 ang;
    u8 pad5C[4];
    u8 col0[4];
    u8 col1[4];
} Fx_b215_01E02660;

typedef struct {
    u8 pad0[0xA00C];
    Pkt_b215_01E02660 *pk;
    u8 padA010[0xE878 - 0xA010];
    u8 sin[1];
} Game_b215_01E02660;

static s32 func_01E02660_b215(Game_b215_01E02660 *g, Fx_b215_01E02660 *o) {
    extern Rgbaq_b215_01E02660 func_00107740(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 depth[4];
    Vec4f q[4];
    Vec4f pos;
    f32 m[16];
    f32 r;
    f32 s;
    f32 c;
    f32 u;
    f32 x;
    f32 z;
    f32 v;
    s16 i;
    s16 a;
    s16 t;

    a = 0;
    g->pk->v[0].c = func_00107740(o->col0);
    g->pk->v[1].c = func_00107740(o->col0);
    g->pk->v[2].c = func_00107740(o->col1);
    g->pk->v[3].c = func_00107740(o->col1);
    pos.x = o->p.x;
    pos.y = o->p.y;
    pos.z = o->p.z;
    func_00108EF0(m, NULL, NULL, &pos);
    r = o->r;
    q[0].y = o->h;
    q[1].y = o->h;
    q[2].y = 0.0f;
    q[3].y = 0.0f;
    for (i = 0; i < 24; i++) {
        t = o->ang + a;
        s = func_00108030(g->sin, t, 1);
        c = func_00108030(g->sin, t, 0);
        x = s * r;
        z = c * r;
        q[2].x = x;
        q[2].z = z;
        q[0].x = x;
        q[0].z = z;
        t = a + (o->ang + 15);
        s = func_00108030(g->sin, t, 1);
        c = func_00108030(g->sin, t, 0);
        x = s * r;
        z = c * r;
        q[3].x = x;
        q[3].z = z;
        q[1].x = x;
        q[1].z = z;
        a += 15;
        if (func_00205630(q, 0x70000000, m, g->pk, depth) != 0) {
            u = (0x6BF8 - g->pk->v[0].x) / -16.0f;
            v = ((o->hA + 0x720) * 16 - 8 - g->pk->v[0].y) / -16.0f;
            if (v < 0.0f) {
                v = 0.0f;
            }
            g->pk->v[0].s = u / 1024.0f;
            g->pk->v[0].t = v / 512.0f;
            u = (0x6BF8 - g->pk->v[1].x) / -16.0f;
            v = ((o->hA + 0x720) * 16 - 8 - g->pk->v[1].y) / -16.0f;
            if (v < 0.0f) {
                v = 0.0f;
            }
            g->pk->v[1].s = u / 1024.0f;
            g->pk->v[1].t = v / 512.0f;
            u = (0x6BF8 - g->pk->v[2].x) / -16.0f;
            v = (0x71F8 - g->pk->v[2].y) / -16.0f;
            if (v > 1.0f) {
                v = 1.0f;
            }
            g->pk->v[2].s = u / 1024.0f;
            g->pk->v[2].t = v / 512.0f;
            u = (0x6BF8 - g->pk->v[3].x) / -16.0f;
            v = (0x71F8 - g->pk->v[3].y) / -16.0f;
            if (v > 1.0f) {
                v = 1.0f;
            }
            g->pk->v[3].s = u / 1024.0f;
            g->pk->v[3].t = v / 512.0f;
            func_002075F0(g->pk, 0, 0);
        }
    }
    return 0;
}

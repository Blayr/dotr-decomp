#include "common.h"

/* shape b443:01E01EA0, 292 insns: IWWhirlpool2: draw an object as one ring of 12 quads (angles 30 apart from o->h3A
   through the sine table g+0xD8), scaled 0.1 * o->h38 / 1000 at the colour-passed position; the edge heights follow
   90 * cos of o->h30 and o->h30 + 40 (past 160 clamped there and lowered by o->h30 / 160 * 5), the radii 90 * sin of
   o->h30 (at least 160) and of 30 more */

typedef struct {
    u8 pad0[0x10];
    f32 pos[3];
    u8 pad1C[0xC];
    u8 uv0[4];
    u8 uv1[4];
    s16 h30;
    u8 pad32[6];
    s16 rad;
    s16 ang;
} Obj_b443_01E01EA0;

typedef struct {
    u8 pad0[0x80];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    u8 rect[0x2A];
    s16 fBE;
    u8 padC0[0x18];
    u8 table[0x10];
} G_b443_01E01EA0;


static void func_01E01EA0_b443(G_b443_01E01EA0 *g, Obj_b443_01E01EA0 *o, s32 flags, Vec4f c) {
    extern f32 func_00108030(void *, s16, s32);
    extern void func_00109270(void *, s32, s32);
    extern void func_00106DD0(void *, f32, f32, f32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_001A23B0(f32);
    Vec4f v[4];
    Vec4f t;
    Vec4f s;
    f32 m[16];
    f32 out[4];
    u8 pk[0x90];
    u8 *p;
    f32 r;
    f32 r1;
    f32 r2;
    f32 d;
    s32 k;
    s32 i;
    s16 a;
    s16 b;
    s16 j;

    p = pk;
    func_00109270(p, 0, 0);
    func_00107790(p, o->uv0, 1);
    func_00107790(p, o->uv1, 2);
    func_00108500(p, g->rect, g->fBE);
    func_00208700(p, (void *)g->f88, 1);
    s.x = s.y = s.z = 0.1f;
    t.x = c.x;
    t.y = c.y;
    t.z = c.z;
    r = o->rad / 1000.0f;
    func_00106DD0(&s, r, r, r);
    func_00108EF0(m, &s, o->pos, &t);
    for (k = 0; k < 1; k++) {
        if (o->h30 < 160) {
            v[0].y = v[1].y = 90.0f * func_00108030(g->table, o->h30, 0);
            v[2].y = v[3].y = 90.0f * func_00108030(g->table, o->h30 + 40, 0);
        } else {
            a = o->h30;
            b = a;
            if (a > 160) {
                a = 160;
            }
            v[0].y = v[1].y = 90.0f * func_00108030(g->table, a, 0);
            v[2].y = v[3].y = 90.0f * func_00108030(g->table, a + 40, 0);
            d = (s16)(b / 160) * 5;
            v[0].y -= d;
            v[1].y -= d;
            v[2].y -= d;
            v[3].y -= d;
        }
        a = o->h30;
        if (a < 160) {
            a = 160;
        }
        r1 = 90.0f * func_00108030(g->table, a, 1);
        r2 = 90.0f * func_00108030(g->table, a + 30, 1);
        j = 0;
        for (i = 0; i < 12; i++) {
            b = o->ang + j;
            v[2].x = r2 * func_00108030(g->table, b, 1);
            v[2].z = r2 * func_00108030(g->table, b, 0);
            v[0].x = r1 * func_00108030(g->table, b, 1);
            v[0].z = r1 * func_00108030(g->table, b, 0);
            b = o->ang + 30 + j;
            v[3].x = r2 * func_00108030(g->table, b, 1);
            v[3].z = r2 * func_00108030(g->table, b, 0);
            v[1].x = r1 * func_00108030(g->table, b, 1);
            v[1].z = r1 * func_00108030(g->table, b, 0);
            if (func_00205630(v, 0x70000000, m, p, out) != 0) {
                func_002075F0(p, g->f80, func_001A23B0(out[0]));
            }
            j += 30;
        }
    }
}


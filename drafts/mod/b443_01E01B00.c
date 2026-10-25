/* func_00108030 really takes an s16 angle (functions.h says s32): hide that prototype */
#define func_00108030 func_00108030_s32
#include "common.h"
#undef func_00108030
extern f32 func_00108030(void *table, s16 angle, s32 axis);

/* shape b443:01E01B00, 232 insns: draw an object as o->n rings of 9 quads (angles 40 apart through the sine table
   g+0xD8), the radius growing by o->h38 / o->n each ring, the ring angle turning o->h1C; each quad reuses the previous
   ring's edge (two rows of 9 points); the packet rect g+0x94 scrolls by g+0x9A / o->n a ring; colour passed by value */

typedef struct {
    u8 pad0[6];
    s16 n;
    u8 pad8[8];
    f32 pos[3];
    s16 turn;
    u8 pad1E[0xA];
    u8 uv0[4];
    u8 uv1[4];
    u8 pad30[8];
    s16 rad;
    s16 ang;
} Obj_b443_01E01B00;

typedef struct {
    u8 pad0[0x80];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    u8 rect[2];
    s16 h96;
    u8 pad98[2];
    s16 h9A;
    u8 pad9C[0x1C];
    s16 count;
    u8 padBA[4];
    s16 fBE;
    u8 padC0[0x18];
    u8 table[0x10];
} G_b443_01E01B00;

typedef struct {
    u8 b[0x90];
} Pk_b443_01E01B00;

static void func_01E01B00_b443(G_b443_01E01B00 *g, Obj_b443_01E01B00 *o, s32 flags, Vec4f c) {
    extern void func_00108EF0();
    extern s32 func_00109270();
    extern void func_00195108(void *, s32);
    Pk_b443_01E01B00 *p;
    s32 i;
    s32 j;
    s32 a;
    s16 k;
    Vec4f *w;
    s32 r_i;
    s16 base;
    f32 r;
    f32 dr;

    Vec4f v[4];
    Vec4f t;
    Vec4f s;
    Vec4f row[2][9];
    f32 m[4][4];
    f32 out[4];
    Pk_b443_01E01B00 pk;

    p = &pk;
    base = 2;
    func_00109270(p, 0, 0);
    func_00107790(p, o->uv0, 1);
    func_00107790(p, o->uv1, 2);
    func_00208700(p, (void *)g->f88, 1);
    s.x = 1.0f;
    t.x = c.x;
    s.y = 1.0f;
    t.y = c.y;
    s.z = 1.0f;
    t.z = c.z;
    g->h9A /= o->n;
    func_00108500(p, g->rect, g->fBE);
    func_00108EF0(m, &s, o->pos, &t);
    v[0].y = 0.0f;
    v[1].y = 0.0f;
    v[2].y = 0.0f;
    v[3].y = 0.0f;
    v[0].x = 0.0f;
    *(f32 *)(u32)&v[0].z = 0.0f;
    *(f32 *)(u32)&v[1].x = 0.0f;
    *(f32 *)(u32)&v[1].z = 0.0f;
    r = o->rad;
    r /= o->n;
    dr = r;
    func_00195108(row, 0x120);
    for (r_i = 0; r_i < o->n; r_i++) {
        k = 0;
        for (i = 0; i < 9; i++) {
            a = base + (o->ang + k);
            *(f32 *)(u32)&v[2].x = r * func_00108030(g->table, a, 1);
            *(f32 *)(u32)&v[2].z = r * func_00108030(g->table, a, 0);
            a = base + (k + (o->ang + 10));
            w = (Vec4f *)(u32)&v[3];
            w->x = r * func_00108030(g->table, a, 1);
            w->z = r * func_00108030(g->table, a, 0);
            v[0].x = row[0][i].x;
            *(f32 *)(u32)&v[0].z = row[0][i].z;
            *(f32 *)(u32)&v[1].x = row[1][i].x;
            *(f32 *)(u32)&v[1].z = row[1][i].z;
            row[0][i].x = *(f32 *)(u32)&v[2].x;
            row[0][i].z = *(f32 *)(u32)&v[2].z;
            row[1][i].x = w->x;
            row[1][i].z = w->z;
            if (func_00205630((s32)v, 0x70000000, (s32)m, (s32)p, out) != 0) {
                for (j = 0; j < g->count + 1; j++) {
                    func_002075F0((s32)p, g->f80, func_001A23B0(out[0]));
                }
            }
            k += 40;
        }
        g->h96 += g->h9A;
        func_00108500(p, g->rect, g->fBE);
        r += dr;
        base += o->turn;
    }
}

#include "common.h"

/* shape c059:01E03610, 313 insns: draw one link of a c059 rain sheet: mode 0 sets the material (frame 0x96) and the near
   and far colours (alpha 0 at a free end, else the link's or the next link's colour); otherwise the quad spans 12 wide
   at the link and the next one, each edge lifted 50 plus the sheet's swing (the sheet entry's sine of base + height x
   rate), pushed out by its depth sine, and drawn twice through the entry's half-height matrix */

typedef struct {
    u8 r, g, b, a;
} Col_c059_01E03610;

typedef struct {
    Vec4f pos;
    s32 rot[4];
    s16 depth;
    u8 pad22[2];
    s16 swing;
    u8 pad26[4];
    s16 base;
    u8 pad2C[4];
    f32 rate;
} Sheet_c059_01E03610;

typedef struct Link_c059_01E03610 {
    s16 h0;
    s16 h2;
    u8 pad4[4];
    s16 h8;
    s16 hA;
    u8 padC[2];
    s16 hE;
    struct Link_c059_01E03610 *next;
    s32 f14;
    u8 pad18[8];
    Col_c059_01E03610 c20;
    Col_c059_01E03610 c24;
    u8 pad28[4];
    s16 h2C;
    s16 sheet;
} Link_c059_01E03610;

typedef struct {
    u8 pad0[0x250];
    Vec4f quad[4];
    u8 pad290[0x23B4];
    s32 tex;
    u8 pad2648[0x3D8];
    Vec4f sc;
    u8 pad2A30[0x9C];
    s32 ot;
    u8 pad2AD0[0x60];
    u8 table[0x368];
    Sheet_c059_01E03610 sh[1];
} Scene_c059_01E03610;

static void func_01E03610_c059(Scene_c059_01E03610 *g, Link_c059_01E03610 *e, void *p, s32 mode) {
    extern Col_c059_01E03610 D_01E06F80_c059;
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern f32 func_00108030();
    extern void func_00106DD0(void *, f32, f32, f32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108FF0(void *, void *, void *, s32);
    Link_c059_01E03610 *q = e->next;
    Col_c059_01E03610 c = D_01E06F80_c059;
    f32 rm[4];
    Vec4f sc;
    f32 m[16];
    f32 rate;
    s16 a;

    if (mode == 0) {
        func_00106080(rm, 0x96, 0, rm);
        if (e->f14 == 0) {
            c = e->c24;
            c.a = 0;
            func_00107790(p, &c, 1);
        } else {
            func_00107790(p, &e->c24, 1);
        }
        if (e->h2C == 0) {
            c = e->c20;
            c.a = 0;
            func_00107790(p, &c, 2);
        } else if (q != 0) {
            func_00107790(p, &q->c24, 2);
        }
        func_00108500(p, rm, 0);
        func_00208700(p, g->tex, 1);
        return;
    }
    g->quad[0].x = e->hE + (e->h8 - 6);
    g->quad[1].x = e->hE + (e->h8 + 6);
    if (q != 0) {
        g->quad[2].x = q->hE + (q->h8 - 6);
        g->quad[3].x = q->hE + (q->h8 + 6);
    } else {
        g->quad[2].x = e->h0 - 6;
        g->quad[3].x = e->h0 + 6;
    }
    rate = g->sh[e->sheet].rate;
    a = g->sh[e->sheet].base + e->hA * rate;
    g->quad[1].y = g->quad[0].y = 50.0f + g->sh[e->sheet].swing * func_00108030(g->table, a, 1);
    if (q != 0) {
        a = g->sh[e->sheet].base + q->hA * rate;
    } else {
        a = g->sh[e->sheet].base + e->h2 * rate;
    }
    g->quad[3].y = g->quad[2].y = 50.0f + g->sh[e->sheet].swing * func_00108030(g->table, a, 1);
    g->quad[1].z = g->quad[0].z = g->sh[e->sheet].depth * func_00108030(g->table, (s16)(e->hA - 110), 1);
    if (q != 0) {
        g->quad[3].z = g->quad[2].z = g->sh[e->sheet].depth * func_00108030(g->table, (s16)(q->hA - 110), 1);
    } else {
        g->quad[3].z = g->quad[2].z = 0.0f;
    }
    func_00106DD0(&g->sc, 150.0f, 0.0f, 150.0f);
    func_00106DD0(&sc, 1.0f, 0.5f, 1.0f);
    func_00108EF0(m, &sc, g->sh[e->sheet].rot, &g->sh[e->sheet].pos);
    func_00108FF0(&g->quad[0], p, m, g->ot);
    func_00108FF0(&g->quad[0], p, m, g->ot);
}

#include "common.h"

/* shape c059:01E031C0, 272 insns: draw one link of c059's rain column: mode 0 sets the material (frame 0x9C, colour 0x40,
   scene texture 0x2644); other modes build the link's quad from the previous link's ring (or its own inner ring) and its
   own outer ring off the scene's ring tables, lift both edges on a 150-high sine of their heights (less 110), colour the
   near edge, and draw it 12 times turned 0x1554 apart (a second 1.8-tall copy while the link is under 100) */

typedef struct {
    f32 m[16];
} Mat_c059_01E031C0;

typedef struct Ent_c059_01E031C0 {
    u8 pad0[2];
    s16 h2;
    u8 pad4[6];
    s16 hA;
    u8 padC[0x14];
    Vec4f v20;
    struct Ent_c059_01E031C0 *prev;
    u8 pad34[0xC];
    u8 c40[4];
    u8 c44[4];
    u8 pad48[6];
    s16 r0;
    s16 r1;
} Ent_c059_01E031C0;

typedef struct {
    u8 pad0[0x80];
    Mat_c059_01E031C0 m;
    u8 padC0[0x180];
    Vec4f sc;
    Vec4f quad[4];
    u8 pad290[0x23B4];
    s32 tex;
    u8 pad2648[0x484];
    s32 ot;
    u8 pad2AD0[0x50];
    f32 dep;
    u8 pad2B24[0xC];
    u8 table[0x228];
    f32 t0[20];
    f32 t1[20];
    f32 t2[20];
    f32 t3[20];
} Scene_c059_01E031C0;

static void func_01E031C0_c059(Scene_c059_01E031C0 *g, Ent_c059_01E031C0 *e, void *p, s32 mode) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00107DD0(void *, void *, void *, s32);
    extern void func_00106FA0(void *, void *, s32);
    extern f32 func_00108030();
    extern void func_0020EB40(void *);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020BC00(void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_00106DD0(void *, f32, f32, f32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108FF0(void *, void *, void *, s32);
    Ent_c059_01E031C0 *q = e->prev;
    f32 rm[4];
    s32 rot[4];
    Vec4f sv;
    Mat_c059_01E031C0 m;
    Mat_c059_01E031C0 m2;
    s16 a;
    s32 i;
    s32 r;

    a = 0;
    if (mode == 0) {
        func_00106080(rm, 0x9C, 0, rm);
        func_00107790(p, e->c40, 2);
        func_00108500(p, rm, 0);
        func_00208700(p, g->tex, 0);
        return;
    }
    for (i = 0; i < 1; i++) {
        if (q != 0) {
            g->quad[0].x = g->t1[i] * q->r1;
            g->quad[0].z = g->t0[i] * q->r1;
            g->quad[1].x = g->t3[i] * q->r1;
            g->quad[1].z = g->t2[i] * q->r1;
            g->quad[0].y = g->quad[1].y = e->h2 = q->hA;
            func_00107DD0(&g->quad[0], &q->v20, &e->v20, 0);
        } else {
            g->quad[0].x = g->t1[i] * e->r0;
            g->quad[0].z = g->t0[i] * e->r0;
            g->quad[1].x = g->t3[i] * e->r0;
            g->quad[1].z = g->t2[i] * e->r0;
        }
        g->quad[2].x = g->t1[i] * e->r1;
        g->quad[2].z = g->t0[i] * e->r1;
        g->quad[3].x = g->t3[i] * e->r1;
        g->quad[3].z = g->t2[i] * e->r1;
        g->quad[2].y = g->quad[3].y = e->hA;
        func_00106FA0(&g->quad[0], &e->v20, 0);
        g->quad[1].y = g->quad[0].y = 30.0f + 150.0f * func_00108030(g->table, (s16)(e->h2 - 110), 1);
        g->quad[3].y = g->quad[2].y = 30.0f + 150.0f * func_00108030(g->table, e->hA - 110, 1);
        if (q == 0) {
            func_00107790(p, e->c44, 1);
        } else {
            func_00107790(p, q->c40, 1);
        }
    }
    rot[2] = rot[0] = rot[1] = 0;
    for (i = 0, r = 0; i < 12; i++) {
        func_0020EB40(&g->m);
        func_0020C940(&m, &g->sc, rot, 0);
        func_0020BC00(&g->m, &m);
        if (func_00205630(&g->quad[0], 0x70000000, &g->m, p, &g->dep) != 0) {
            func_002075F0(p, g->ot, (u32)g->dep);
        }
        if (e->h2 < 100) {
            func_00106DD0(&sv, 1.0f, 1.8f, 1.0f);
            func_00108EF0(&m2, &sv, rot, 0);
            g->m = m2;
            func_00108FF0(&g->quad[0], p, &g->m, g->ot);
        }
        r += 0x1554;
        rot[1] = r;
        a += 30;
    }
}

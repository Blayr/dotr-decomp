#include "common.h"

/* shape b351:01E068F0, 187 insns: lays a spiral of sparks between two joints: for each of five spots a quarter of the way
   apart along the line from joint 0x10 to joint 0x0C, it turns the module's table matrix (0x1E07AB0, one row each),
   swings a point round by 45 degrees per spot (radius 0.4 and phase 8 per frame left of 40) and drops two particles
   (kind 9/7, frame 3, size 35, life 300) there into the particle pool at +0xE48 */

typedef struct {
    Vec4f v[5];
} Tab_b351_01E068F0;

typedef struct {
    u8 pad0[4];
    u8 b4;
    u8 b5;
    u8 pad6[2];
    u8 b8;
    u8 b9;
    u8 bA;
    u8 bB;
    u8 col[4];
    f32 size;
    s32 life;
    f32 x, y, z;
    u8 pad24[0x18];
} Part_b351_01E068F0;

typedef struct {
    u16 left;
    u8 pad2[2];
    s32 model;
    u8 pad8[4];
    s32 ja;
    s32 jb;
    u8 pad14[0xE34];
    Part_b351_01E068F0 part[100];
} Scene_b351_01E068F0;

extern Tab_b351_01E068F0 D_01E07AB0_b351;

static void func_01E068F0_b351(Scene_b351_01E068F0 *g) {
    extern void func_001F5620(s32, s32, void *);
    extern void func_00101A00(void *, void *);
    extern f32 func_001A6898(f32);
    extern f32 func_001A6A88(f32);
    extern void func_0020CDD0(void *, void *, void *);
    extern s32 func_00101C30(void *, s32, s32);
    extern void func_00101AD0(void *, s32, s32, s32);
    Vec4f v[2];
    Vec4f d;
    Vec4f e;
    f32 m[16];
    Tab_b351_01E068F0 tab;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 f;
    f32 r;
    f32 base;
    f32 ox;
    f32 oy;
    f32 oz;
    f32 ang;
    s32 i;
    s32 k;
    s32 n;

    tab = D_01E07AB0_b351;
    func_001F5620(g->model, g->ja, &v[0]);
    func_001F5620(g->model, g->jb, &v[1]);
    dx = (v[0].x - v[1].x) / 4.0f;
    dy = (v[0].y - v[1].y) / 4.0f;
    dz = (v[0].z - v[1].z) / 4.0f;
    r = 0.4f * (40 - g->left);
    base = 8.0f * (40 - g->left);
    for (i = 0; i < 5; i++) {
        func_00101A00(&tab.v[i], m);
        ang = 3.1415927f * (45.0f * i + base) / 180.0f;
        d.x = r * func_001A6898(ang);
        d.y = 0.0f;
        d.z = r * func_001A6A88(ang);
        func_0020CDD0(&e, m, &d);
        ox = dx * i;
        oy = dy * i;
        oz = dz * i;
        for (k = 0; k < 2; k++) {
            n = func_00101C30(g->part, 0x3C, 100);
            if (n >= 0) {
                func_00101AD0(&g->part[n], 9, 0, 7);
                g->part[n].b5 = 0;
                g->part[n].b4 = 0;
                g->part[n].b8 = 0;
                g->part[n].b9 = 3;
                g->part[n].bA = 2;
                g->part[n].bB = 0;
                g->part[n].col[3] = 0x80;
                g->part[n].col[0] = 0x80;
                g->part[n].col[1] = 0x80;
                g->part[n].col[2] = 0x80;
                g->part[n].size = 35.0f;
                g->part[n].life = 300;
                g->part[n].x = e.x + (v[1].x + ox);
                g->part[n].y = e.y + (v[1].y + oy);
                g->part[n].z = e.z + (v[1].z + oz);
            }
        }
    }
}

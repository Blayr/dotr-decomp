#include "common.h"

/* shape b034:01E054C0, 369 insns, 1 copy: draws the scene's box at a point, turned half round when the scene flag is
   clear: mode 0 its six faces from the corner table (ctx+0xA880, indices at ctx+0xA9B4), each face's far edge pushed out
   by the scene width; other modes a ring of 36 sectors (10 apart) of two bands (inner radius r, r + d and r + w,
   r + w + d) */

typedef struct {
    f32 c;
    f32 s;
} Cs_b034_01E054C0;

typedef struct {
    f32 r0;
    f32 r1;
} Rr_b034_01E054C0;

typedef struct {
    s16 a;
    s16 b;
    s16 c;
    s16 d;
} Face_b034_01E054C0;

typedef struct {
    u8 pad0[0xA880];
    Vec4f tab[8];
    u8 padA900[0xC];
    s32 ot;
    u8 padA910[0x10];
    f32 r;
    f32 w;
    f32 d;
    f32 wA92C;
    u8 padA930[0x84];
    Face_b034_01E054C0 face[6];
    u8 padA9E4[0x2A];
    s16 flag;
    u8 padAA10[0x304];
    u8 trig[4];
} Scene_b034_01E054C0;

typedef struct {
    u8 pad0[0x60];
    u8 col[4];
    u8 col2[4];
} Obj_b034_01E054C0;

static void func_01E054C0_b034(Scene_b034_01E054C0 *g, Obj_b034_01E054C0 *o, s32 mode, Vec4f *pos) {
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00107990(void *, void *, s32);
    extern void func_001092E0(void *, s32);
    extern void func_001094F0(void *);
    extern void func_00195108(void *, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_001A23B0(f32);
    Vec4f p;
    Vec4f q[4];
    Vec4f v;
    f32 m[16];
    f32 depth[4];
    Cs_b034_01E054C0 cs[2];
    Rr_b034_01E054C0 rr[2];
    s32 rot[4];
    u8 pk[0x90];
    u8 *pp;
    Rr_b034_01E054C0 *pr;
    Cs_b034_01E054C0 *pc;
    Vec4f *pq;
    s16 i;
    s16 j;
    s16 n;
    s16 a;
    f32 r0;
    f32 r1;

    pp = pk;
    p = *pos;
    rot[0] = 0;
    rot[2] = 0;
    a = 0;
    if (g->flag != 0) {
        rot[1] = 0;
    } else {
        rot[1] = 0x8000;
    }
    v.x = p.x;
    v.y = p.y;
    v.z = p.z;
    func_00108EF0(m, NULL, rot, &v);
    func_00107990(pp, o->col2, 2);
    func_00107990(pp, o->col, 1);
    func_001092E0(pp, 0);
    func_001094F0(pp);
    if (mode == 0) {
        for (i = 0; i < 6; i++) {
            func_00195108(q, 0x40);
            q[0] = g->tab[g->face[i].a];
            q[2] = g->tab[g->face[i].b];
            q[1] = g->tab[g->face[i].c];
            q[3] = g->tab[g->face[i].d];
            if (i == 0 || i == 5) {
                q[2].x -= g->wA92C;
                q[3].x -= g->wA92C;
            }
            if (i == 1) {
                q[2].z += g->wA92C;
                q[3].z += g->wA92C;
            }
            if (i == 3 || i == 2) {
                q[2].x += g->wA92C;
                q[3].x += g->wA92C;
            }
            if (i == 4) {
                q[2].z -= g->wA92C;
                q[3].z -= g->wA92C;
            }
            if (func_00205630(q, 0x70000000, m, pp, depth) != 0) {
                func_002075F0(pp, g->ot, func_001A23B0(depth[0]));
            }
        }
        return;
    }
    func_00107990(pp, o->col2, 2);
    func_00107990(pp, o->col, 1);
    q[0].y = 0.0f;
    q[1].y = 0.0f;
    q[2].y = 0.0f;
    q[3].y = 0.0f;
    rr[0].r0 = g->r;
    rr[0].r1 = g->r + g->d;
    rr[1].r0 = g->r + g->w;
    rr[1].r1 = g->d + (g->r + g->w);
    for (i = 0; i < 36; i++) {
        cs[0].c = func_00108030(g->trig, a, 0);
        cs[0].s = func_00108030(g->trig, a, 1);
        a += 10;
        cs[1].c = func_00108030(g->trig, a, 0);
        cs[1].s = func_00108030(g->trig, a, 1);
        pr = rr;
        for (j = 0; j < 2; j++) {
            r0 = pr->r0;
            r1 = pr->r1;
            pc = cs;
            pq = q;
            for (n = 0; n < 2; n++) {
                pq[0].z = pc->c * r0;
                pq[0].x = pc->s * r0;
                pq[2].z = pc->c * r1;
                pq[2].x = pc->s * r1;
                pc++;
                pq++;
            }
            if (func_00205630(q, 0x70000000, m, pp, depth) != 0) {
                func_002075F0(pp, g->ot, func_001A23B0(depth[0]));
            }
            pr++;
        }
    }
}

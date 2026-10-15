#include "common.h"

/* shape b000:01E00100, 38 insns, 169 copies: one colour into the four vertices of a quad (q = 1.0) */

typedef struct Src_b000_01E00100 {
    u8 b, g, r, a;
} Src_b000_01E00100;

typedef struct Col_b000_01E00100 {
    u8 r, g, b, a;
    f32 q;
} Col_b000_01E00100;

typedef struct Vtx_b000_01E00100 {
    u8 pad[0x10];
    Col_b000_01E00100 c;
} Vtx_b000_01E00100;


/* static in its module (callers that include this file #define OVL_LOCAL static first) */

static void func_01E00080_c603(Vtx_b000_01E00100 *v, Src_b000_01E00100 *s) {
    v[0].c.r = s->r;
    v[0].c.g = s->g;
    v[0].c.b = s->b;
    v[0].c.a = s->a;
    v[0].c.q = 1.0f;
    v[1].c.r = s->r;
    v[1].c.g = s->g;
    v[1].c.b = s->b;
    v[1].c.a = s->a;
    v[1].c.q = 1.0f;
    v[2].c.r = s->r;
    v[2].c.g = s->g;
    v[2].c.b = s->b;
    v[2].c.a = s->a;
    v[2].c.q = 1.0f;
    v[3].c.r = s->r;
    v[3].c.g = s->g;
    v[3].c.b = s->b;
    v[3].c.a = s->a;
    v[3].c.q = 1.0f;
}

/* OVL_WARM: compile warm (its (u32) cast is jal fptoui, func_001A23B0) */

/* shape c602:01E01620, 510 insns: draws a 23 x 16 grid of textured tiles: each tile's alpha from a per-tile table,
   its texture cell (tw / 16 by th / 23) from (u0, v0), a square of half-size half around its point (z only under
   flag 0x1E, else additive blend when z > 0); the first tile also binds the object's texture (func_001DA7A0). */

typedef struct {
    u8 b, g, r, a;
} Src_c602_01E01620;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_c602_01E01620;

typedef struct {
    u64 v;
} Q_c602_01E01620;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Uv_c602_01E01620 uv;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_c602_01E01620;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_c602_01E01620 v[4];
    u8 pad70[8];
    Q_c602_01E01620 t0, t1, t2;
} Pkt_c602_01E01620;

typedef struct {
    f32 x, y, z;
} Pt_c602_01E01620;

typedef struct {
    u8 pad0[4];
    s32 flags;
    f32 half;
    Src_c602_01E01620 col;
    s16 u, v;
    s16 tw, th;
    s16 u0, v0;
    u8 pad1C[4];
    Pt_c602_01E01620 pos[23][16];
    u8 pad1160[0x6C0];
    u8 alpha[23][16];
} Grid_c602_01E01620;

typedef struct {
    u8 pad0[0x60];
    Q_c602_01E01620 t0, t1, t2;
    u8 pad78[0x18];
    s32 f90;
} Obj_c602_01E01620;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_c602_01E01620;

static s32 func_01E00120_c603(Obj_c602_01E01620 *o, Cam_c602_01E01620 *cam, Grid_c602_01E01620 *g) {
    extern void c603_01E00080(void *, void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_001D9F00(void *, s32);
    extern void func_001DA7A0(s32, void *);
    s32 r;
    s32 fl;
    s32 du;
    s32 c;
    s32 dv;
    f32 dep[4];
    Vec4f p[3];
    Pkt_c602_01E01620 pkt;

    fl = func_001D9F00(o, 1);
    ((Pkt_c602_01E01620 *)(s32)&pkt)->count = 0x34;
    ((Pkt_c602_01E01620 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_c602_01E01620 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_c602_01E01620 *)(s32)&pkt)->pad = 0;
    if (func_00104520(g->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(g->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    du = g->tw >> 4;
    dv = g->th / 23;
    for (r = 0; r < 23; r++) {
        for (c = 0; c < 16; c++) {
            g->col.a = g->alpha[r][c];
            c603_01E00080(&pkt, &g->col);
            g->u = g->u0 + (s16)(c * du);
            g->v = g->v0 + (s16)(r * dv);
            ((Pkt_c602_01E01620 *)(s32)&pkt)->count |= 0x800;
            ((Uv_c602_01E01620 *)(s32)&pkt.v[0].uv)->u = g->u << 4;
            ((Uv_c602_01E01620 *)(s32)&pkt.v[0].uv)->v = g->v << 4;
            ((Uv_c602_01E01620 *)(s32)&pkt.v[1].uv)->u = (g->u + du - 1) << 4;
            ((Uv_c602_01E01620 *)(s32)&pkt.v[1].uv)->v = g->v << 4;
            ((Uv_c602_01E01620 *)(s32)&pkt.v[2].uv)->u = g->u << 4;
            ((Uv_c602_01E01620 *)(s32)&pkt.v[2].uv)->v = (g->v + dv - 1) << 4;
            ((Uv_c602_01E01620 *)(s32)&pkt.v[3].uv)->u = (g->u + du - 1) << 4;
            ((Uv_c602_01E01620 *)(s32)&pkt.v[3].uv)->v = (g->v + dv - 1) << 4;
            if (func_00104520(g->flags, 0x1E) == 0 && !(g->pos[r][c].z <= 0.0f)) {
                func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
            }
            p[0].x = g->pos[r][c].x - g->half;
            p[0].y = g->pos[r][c].y + g->half;
            if (func_00104520(g->flags, 0x1E) != 0) {
                p[0].z = g->pos[r][c].z;
            } else {
                p[0].z = 0.0f;
            }
            if (func_00205440(&p[0], cam->view, &pkt.v[0].uv + 1, &dep[0]) != 0) {
                g->flags |= 0x100000;
            }
            p[0].x = g->pos[r][c].x + g->half;
            p[0].y = g->pos[r][c].y + g->half;
            if (func_00104520(g->flags, 0x1E) != 0) {
                p[0].z = g->pos[r][c].z;
            } else {
                p[0].z = 0.0f;
            }
            if (func_00205440(&p[0], cam->view, &pkt.v[1].uv + 1, &dep[1]) != 0) {
                g->flags |= 0x200000;
            }
            p[1].x = g->pos[r][c].x - g->half;
            p[1].y = g->pos[r][c].y - g->half;
            if (func_00104520(g->flags, 0x1E) != 0) {
                p[1].z = g->pos[r][c].z;
            } else {
                p[1].z = 0.0f;
            }
            if (func_00205440(&p[1], cam->view, &pkt.v[2].uv + 1, &dep[2]) != 0) {
                g->flags |= 0x400000;
            }
            p[2].x = g->pos[r][c].x + g->half;
            p[2].y = g->pos[r][c].y - g->half;
            if (func_00104520(g->flags, 0x1E) != 0) {
                p[2].z = g->pos[r][c].z;
            } else {
                p[2].z = 0.0f;
            }
            if (func_00205440(&p[2], cam->view, &pkt.v[3].uv + 1, &dep[3]) != 0) {
                g->flags |= 0x800000;
            }
            pkt.t0 = o->t0;
            pkt.t1 = o->t1;
            pkt.t2 = o->t2;
            if (r == 0 && c == 0) {
                if (fl != 0) {
                    func_001DA7A0(o->f90, o);
                } else {
                    func_001DA7A0(0, o);
                }
            }
            if (func_00104520(g->flags, 0x14) != 0) {
                if (func_00104520(g->flags, 0x15) != 0 && func_00104520(g->flags, 0x16) != 0 &&
                    func_00104520(g->flags, 0x17) != 0) {
                    if (func_00104520(g->flags, 0x13) != 0) {
                        pkt.v[0].z = pkt.v[1].z = pkt.v[2].z = pkt.v[3].z = 0xFFFFFF;
                        func_002075F0(&pkt, 0, 0);
                    } else {
                        func_002075F0(&pkt, 0, func_001A23B0((dep[0] + dep[1] + dep[2] + dep[3]) / 4.0f));
                    }
                }
            }
            g->flags &= 0xFF0FFFFF;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/c603", func_01E00920_c603);

INCLUDE_ASM("asm/nonmatchings/mod/c603", func_01E00E10_c603);

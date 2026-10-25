#include "common.h"

/* shape c603:01E00920, 314 insns: LkSortDividedCard2: c602:01E01620's tiled card as an 8 x 8 grid of sprites (one
   colour for all, each tile's alpha from the table at +0x1820, cell tw / 8 by th / 8), each a square of half-size
   half around its point, drawn at its depth; the first tile also binds the object's texture */

typedef struct {
    u8 b, g, r, a;
} Src_c603_01E00920;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_c603_01E00920;

typedef struct {
    u64 v;
} Q_c603_01E00920;

typedef struct {
    Uv_c603_01E00920 uv;
    u64 xyz;
} Vtx_c603_01E00920;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Vtx_c603_01E00920 v[4];
    u8 pad58[8];
    Q_c603_01E00920 t0, t1, t2;
} Pkt_c603_01E00920;

typedef struct {
    f32 x, y, z;
} Pt_c603_01E00920;

typedef struct {
    u8 pad0[4];
    s32 flags;
    f32 half;
    Src_c603_01E00920 col;
    s16 u, v;
    s16 tw, th;
    s16 u0, v0;
    u8 pad1C[4];
    Pt_c603_01E00920 pos[32][16];
    u8 alpha[8][16];
} Grid_c603_01E00920;

typedef struct {
    u8 pad0[0x60];
    Q_c603_01E00920 t0, t1, t2;
    u8 pad78[0x18];
    s32 f90;
} Obj_c603_01E00920;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_c603_01E00920;

static s32 func_01E00920_c603(Obj_c603_01E00920 *o, Cam_c603_01E00920 *cam, Grid_c603_01E00920 *g) {
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_001D9F00(void *, s32);
    extern void func_001DA7A0(s32, void *);
    s32 r;
    s32 fl;
    s32 du;
    s32 c;
    s32 dv;
    f32 dep[4];
    Vec4f p[4];
    Pkt_c603_01E00920 pkt;

    fl = func_001D9F00(o, 1);
    ((Pkt_c603_01E00920 *)(s32)&pkt)->count = 0x24;
    ((Pkt_c603_01E00920 *)(s32)&pkt)->tag = 9;
    ((Pkt_c603_01E00920 *)(s32)&pkt)->regs = ((u64)4 << 32) | 0x24242421;
    ((Pkt_c603_01E00920 *)(s32)&pkt)->pad = 0;
    if (func_00104520(g->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(g->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    du = g->tw >> 3;
    dv = g->th >> 3;
    pkt.r = g->col.r;
    pkt.g = g->col.g;
    pkt.b = g->col.b;
    pkt.a = g->col.a;
    pkt.q = 1.0f;
    for (r = 0; r < 8; r++) {
        for (c = 0; c < 8; c++) {
            g->col.a = g->alpha[r][c];
            g->u = g->u0 + (s16)(c * du);
            g->v = g->v0 + (s16)(r * dv);
            ((Pkt_c603_01E00920 *)(s32)&pkt)->count |= 0x800;
            ((Uv_c603_01E00920 *)(s32)&pkt.v[0].uv)->u = g->u << 4;
            ((Uv_c603_01E00920 *)(s32)&pkt.v[0].uv)->v = g->v << 4;
            ((Uv_c603_01E00920 *)(s32)&pkt.v[1].uv)->u = (g->u + du - 1) << 4;
            ((Uv_c603_01E00920 *)(s32)&pkt.v[1].uv)->v = g->v << 4;
            ((Uv_c603_01E00920 *)(s32)&pkt.v[2].uv)->u = g->u << 4;
            ((Uv_c603_01E00920 *)(s32)&pkt.v[2].uv)->v = (g->v + dv - 1) << 4;
            ((Uv_c603_01E00920 *)(s32)&pkt.v[3].uv)->u = (g->u + du - 1) << 4;
            ((Uv_c603_01E00920 *)(s32)&pkt.v[3].uv)->v = (g->v + dv - 1) << 4;
            p[0].x = g->pos[r][c].x - g->half;
            p[0].y = g->pos[r][c].y + g->half;
            p[0].z = g->pos[r][c].z;
            p[1].x = g->pos[r][c].x + g->half;
            p[1].y = g->pos[r][c].y + g->half;
            p[1].z = g->pos[r][c].z;
            p[2].x = g->pos[r][c].x - g->half;
            p[2].y = g->pos[r][c].y - g->half;
            p[2].z = g->pos[r][c].z;
            p[3].x = g->pos[r][c].x + g->half;
            p[3].y = g->pos[r][c].y - g->half;
            p[3].z = g->pos[r][c].z;
            func_00205630(p, 0x70000000, cam->view, &pkt, dep);
            if (r == 0 && c == 0) {
                pkt.t0 = o->t0;
                pkt.t1 = o->t1;
                pkt.t2 = o->t2;
                if (fl != 0) {
                    func_001DA7A0(o->f90, o);
                } else {
                    func_001DA7A0(0, o);
                }
            }
            func_002075F0(&pkt, 0, func_001A23B0(dep[0]));
        }
    }
    return 0;
}

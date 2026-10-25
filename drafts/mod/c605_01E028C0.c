#include "common.h"

/* shape c605:01E028C0, 352 insns: c625:01E01E10-style card quad that is wiped from the bottom: corners from the
   module's table with the lower two at height 184 - h, UVs cut to the visible part (rows x h / 368); colour helper
   b000:01E00100; the model is lit by func_001D9F00 and its light handed on by func_001DA7A0; drawn at far z or the
   corners' mean depth once all four corners project */

typedef struct {
    u8 b, g, r, a;
} Src_c605_01E028C0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    union {
        struct {
            f32 s, t;
        } st;
        struct {
            u64 u : 14;
            u64 pad0 : 2;
            u64 v : 14;
            u64 pad1 : 34;
        } uv;
    } tc;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_c605_01E028C0;

typedef struct {
    u64 u : 14;
    u64 pad0 : 2;
    u64 v : 14;
    u64 pad1 : 34;
} UV_c605_01E028C0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_c605_01E028C0 v[4];
    u8 tail[0x20];
} Pkt_c605_01E028C0;

typedef struct {
    Vec4f v[4];
} Tbl_c605_01E028C0;

typedef struct {
    u64 w[3];
} Save_c605_01E028C0;

typedef struct {
    u8 pad0[0x60];
    Save_c605_01E028C0 save;
    u8 pad78[0x18];
    s32 f90;
} Obj_c605_01E028C0;

typedef struct {
    u8 pad0[4];
    s32 flags;
    f32 h;
    Src_c605_01E028C0 color;
    s16 u, v, w, hh;
} Spr_c605_01E028C0;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_c605_01E028C0;

static void func_01E00080_c605();

static s32 func_01E028C0_c605(Obj_c605_01E028C0 *o, Cam_c605_01E028C0 *cam, Spr_c605_01E028C0 *spr) {
    extern Tbl_c605_01E028C0 D_01E03E00_c605;
    extern s32 func_001D9F00();
    extern void func_001DA7A0();
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 depth[4];
    Tbl_c605_01E028C0 pts;
    Pkt_c605_01E028C0 pkt;
    Save_c605_01E028C0 save;
    s32 lit;
    f32 f;
    f32 k;

    f = 184.0f - spr->h;
    pts = D_01E03E00_c605;
    pts.v[2].y = pts.v[3].y = f;
    lit = func_001D9F00(o, 1);
    ((Pkt_c605_01E028C0 *)(s32)&pkt)->count = 0x34;
    ((Pkt_c605_01E028C0 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_c605_01E028C0 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_c605_01E028C0 *)(s32)&pkt)->pad = 0;
    if (func_00104520(spr->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(spr->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    func_01E00080_c605(&pkt, &spr->color);
    k = spr->hh * (spr->h / 368.0f);
    ((Pkt_c605_01E028C0 *)(s32)&pkt)->count |= 0x800;
    ((UV_c605_01E028C0 *)(s32)&pkt.v[0].tc)->u = spr->u * 16;
    ((UV_c605_01E028C0 *)(s32)&pkt.v[0].tc)->v = spr->v * 16;
    ((UV_c605_01E028C0 *)(s32)&pkt.v[1].tc)->u = (spr->u + spr->w - 1) * 16;
    ((UV_c605_01E028C0 *)(s32)&pkt.v[1].tc)->v = spr->v * 16;
    ((UV_c605_01E028C0 *)(s32)&pkt.v[2].tc)->u = spr->u * 16;
    ((UV_c605_01E028C0 *)(s32)&pkt.v[2].tc)->v = (spr->v + (s32)k - 1) * 16;
    ((UV_c605_01E028C0 *)(s32)&pkt.v[3].tc)->u = (spr->u + spr->w - 1) * 16;
    ((UV_c605_01E028C0 *)(s32)&pkt.v[3].tc)->v = (spr->v + (s32)k - 1) * 16;
    if (func_00205440(&pts.v[0], cam->view, &pkt.v[0].tc + 1, &depth[0]) != 0) {
        spr->flags |= 0x100000;
    }
    if (func_00205440(&pts.v[1], cam->view, &pkt.v[1].tc + 1, &depth[1]) != 0) {
        spr->flags |= 0x200000;
    }
    if (func_00205440(&pts.v[2], cam->view, &pkt.v[2].tc + 1, &depth[2]) != 0) {
        spr->flags |= 0x400000;
    }
    if (func_00205440(&pts.v[3], cam->view, &pkt.v[3].tc + 1, &depth[3]) != 0) {
        spr->flags |= 0x800000;
    }
    if (lit != 0) {
        func_001DA7A0(o->f90, o);
    } else {
        func_001DA7A0(0, o);
    }
    save = o->save;
    if (func_00104520(spr->flags, 0x14) != 0 && func_00104520(spr->flags, 0x15) != 0 &&
        func_00104520(spr->flags, 0x16) != 0 && func_00104520(spr->flags, 0x17) != 0) {
        if (func_00104520(spr->flags, 0x13) != 0) {
            pkt.v[0].z = pkt.v[1].z = pkt.v[2].z = pkt.v[3].z = 0xFFFFFF;
            func_002075F0(&pkt, 0, 0);
        } else {
            func_002075F0(&pkt, 0, func_001A23B0((depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f));
        }
    }
    spr->flags &= 0xFF0FFFFF;
    return 0;
}

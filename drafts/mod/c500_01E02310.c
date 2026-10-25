#include "common.h"

/* shape c500:01E02310, 307 insns: LkSortElec, a lightning bolt: jitter its five points (x -5..4, y 0..19, the last
   y -5..4), then draw 5 - n segments as textured quads of width ctx+0x2C from the start (or the previous point) to
   each point, depth-sorted when all four corners are in view */

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_c500_01E02310;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_c500_01E02310 v[4];
    u8 tail[0x20];
} Pkt_c500_01E02310;

typedef struct {
    void *texture;
    u8 x4[8];
    s16 n;
    u8 padE[2];
    s16 u, v, w, h;
    u8 pad18[8];
    Vec4f p0;
    Vec4f pts[5];
} Elec_c500_01E02310;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_c500_01E02310;

static s32 func_01E02310_c500(s32 ot, Elec_c500_01E02310 *s, Cam_c500_01E02310 *cam) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00104540(void *, void *, s32);
    f32 depth[4];
    Pkt_c500_01E02310 pkt;
    s32 flags;
    s32 i;

    ((Pkt_c500_01E02310 *)(s32)&pkt)->count = 0x34;
    ((Pkt_c500_01E02310 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_c500_01E02310 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_c500_01E02310 *)(s32)&pkt)->pad = 0;
    flags = 0;
    func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    for (i = 0; i < 5; i++) {
        if (i == 4) {
            s->pts[i].x = func_0019A5C8() % 10 - 5;
            s->pts[i].y = func_0019A5C8() % 10 - 5;
        } else {
            s->pts[i].x = func_0019A5C8() % 10 - 5;
            s->pts[i].y = func_0019A5C8() % 20;
        }
    }
    for (i = 0; i < 5 - s->n; i++) {
        func_01E00120_c500((Pk_b021_01E00120 *)&pkt, (Src_b021_01E00120 *)s->x4, i);
        func_00104540(&pkt, &s->u, 1);
        if (i == 0) {
            if (func_00205440(&s->p0, cam->view, &pkt.v[0].st + 1, &depth[0]) != 0) {
                flags |= 0x100000;
            }
            if (func_00205440(&s->pts[i], cam->view, &pkt.v[1].st + 1, &depth[1]) != 0) {
                flags |= 0x200000;
            }
            s->p0.x += s->p0.w;
            s->pts[i].x += s->p0.w;
            if (func_00205440(&s->p0, cam->view, &pkt.v[2].st + 1, &depth[2]) != 0) {
                flags |= 0x400000;
            }
            if (func_00205440(&s->pts[i], cam->view, &pkt.v[3].st + 1, &depth[3]) != 0) {
                flags |= 0x800000;
            }
            s->p0.x -= s->p0.w;
            s->pts[i].x -= s->p0.w;
        } else {
            if (func_00205440(&s->pts[i - 1], cam->view, &pkt.v[0].st + 1, &depth[0]) != 0) {
                flags |= 0x100000;
            }
            if (func_00205440(&s->pts[i], cam->view, &pkt.v[1].st + 1, &depth[1]) != 0) {
                flags |= 0x200000;
            }
            s->pts[i - 1].x += s->p0.w;
            s->pts[i].x += s->p0.w;
            if (func_00205440(&s->pts[i - 1], cam->view, &pkt.v[2].st + 1, &depth[2]) != 0) {
                flags |= 0x400000;
            }
            if (func_00205440(&s->pts[i], cam->view, &pkt.v[3].st + 1, &depth[3]) != 0) {
                flags |= 0x800000;
            }
            s->pts[i - 1].x -= s->p0.w;
            s->pts[i].x -= s->p0.w;
        }
        func_00208CB0(&pkt, (u64)0xA | ((u64)s->u << 4) | ((u64)(s->u + s->w - 1) << 14) |
                                ((u64)s->v << 24) | ((u64)(s->v + s->h - 1) << 34));
        func_00208700(&pkt, s->texture, 1);
        if (func_00104520(flags, 0x14) != 0 && func_00104520(flags, 0x15) != 0 &&
            func_00104520(flags, 0x16) != 0 && func_00104520(flags, 0x17) != 0) {
            func_002075F0(&pkt, ot, (u32)((depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f));
        }
        flags &= 0xFF0FFFFF;
    }
    return 0;
}

#include "common.h"

/* shape c604:01E03200, 369 insns, 2 copies (LkSortSlash): draws one slash as a textured quad: blend from flags 0xB /
   0xA, the colour into all four corners (the module's colour helper, shape b000:01E00100), integer (flag 0) or float
   texture coordinates, two edge widths from the size, its four corner points turned by its rotation and projected
   (clip flags 0x100000..0x800000); far z under flag 0x13, else depth-sorted when all four corners are in view */

typedef struct {
    u16 s : 14;
    u16 ps : 2;
    u16 t : 14;
    u16 pt : 2;
    u32 pad;
} Uv_c604_01E03200;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    union {
        Uv_c604_01E03200 i;
        struct {
            f32 s, t;
        } f;
    } st;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fg : 8;
} Vtx_c604_01E03200;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_c604_01E03200 v[4];
    u8 tail[0x20];
} Pkt_c604_01E03200;

typedef struct {
    void *texture;
    s32 flags;
    u8 color[4];
    f32 size;
    union {
        struct {
            s16 u, v, w, h;
        } i;
        struct {
            f32 u, v, w, h;
        } f;
    } uv;
    Vec4f p[4];
    s32 rot[4];
} Slash_c604_01E03200;

typedef struct {
    u8 pad0[0x30];
    u8 view[1];
} Cam_c604_01E03200;

static s32 func_01E03200_c604(s32 obj, Slash_c604_01E03200 *e, Cam_c604_01E03200 *cam) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_00103540(void *, f32, f32);
    extern void func_0020C630(void *, void *);
    extern void func_0020CDD0(void *, void *, void *);
    Vec4f c;
    f32 m[16];
    f32 depth[4];
    Pkt_c604_01E03200 pkt;
    Uv_c604_01E03200 *u0;
    Uv_c604_01E03200 *u1;
    Uv_c604_01E03200 *u2;
    Uv_c604_01E03200 *u3;

    ((Pkt_c604_01E03200 *)(s32)&pkt)->count = 0x34;
    ((Pkt_c604_01E03200 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_c604_01E03200 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_c604_01E03200 *)(s32)&pkt)->pad = 0;
    if (func_00104520(e->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(e->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    func_01E00080_c604((Vtx_b000_01E00100 *)&pkt, (Src_b000_01E00100 *)e->color);
    if (func_00104520(e->flags, 0) != 0) {
        ((Pkt_c604_01E03200 *)(s32)&pkt)->count |= 0x800;
        u0 = &pkt.v[0].st.i;
        u1 = &pkt.v[1].st.i;
        u2 = &pkt.v[2].st.i;
        u3 = &pkt.v[3].st.i;
        u0->s = e->uv.i.u << 4;
        u0->t = e->uv.i.v << 4;
        u1->s = (e->uv.i.u + e->uv.i.w - 1) << 4;
        u1->t = e->uv.i.v << 4;
        u2->s = e->uv.i.u << 4;
        u2->t = (e->uv.i.v + e->uv.i.h - 1) << 4;
        u3->s = (e->uv.i.u + e->uv.i.w - 1) << 4;
        u3->t = (e->uv.i.v + e->uv.i.h - 1) << 4;
    } else {
        pkt.v[0].st.f.s = e->uv.f.u;
        pkt.v[0].st.f.t = e->uv.f.v;
        pkt.v[1].st.f.s = e->uv.f.u + e->uv.f.w;
        pkt.v[1].st.f.t = e->uv.f.v;
        pkt.v[2].st.f.s = e->uv.f.u;
        pkt.v[2].st.f.t = e->uv.f.v + e->uv.f.h;
        pkt.v[3].st.f.s = e->uv.f.u + e->uv.f.w;
        pkt.v[3].st.f.t = e->uv.f.v + e->uv.f.h;
    }
    func_00103540(&e->p[2].y, -10.0f * e->size, 4.0f * e->size);
    func_00103540(&e->p[3].y, -10.0f * e->size, 4.0f * e->size);
    func_0020C630(m, e->rot);
    func_0020CDD0(&c, m, &e->p[0]);
    if (func_00205440(&c, cam->view, &pkt.v[0].st + 1, &depth[0]) != 0) {
        e->flags |= 0x100000;
    }
    func_0020CDD0(&c, m, &e->p[1]);
    if (func_00205440(&c, cam->view, &pkt.v[1].st + 1, &depth[1]) != 0) {
        e->flags |= 0x200000;
    }
    func_0020CDD0(&c, m, &e->p[2]);
    if (func_00205440(&c, cam->view, &pkt.v[2].st + 1, &depth[2]) != 0) {
        e->flags |= 0x400000;
    }
    func_0020CDD0(&c, m, &e->p[3]);
    if (func_00205440(&c, cam->view, &pkt.v[3].st + 1, &depth[3]) != 0) {
        e->flags |= 0x800000;
    }
    func_00208700(&pkt, e->texture, 0);
    if (func_00104520(e->flags, 0x13) != 0) {
        pkt.v[0].z = pkt.v[1].z = pkt.v[2].z = pkt.v[3].z = 0xFFFFFF;
        func_002075F0(&pkt, obj, 0);
    } else if (func_00104520(e->flags, 0x14) != 0 && func_00104520(e->flags, 0x15) != 0 &&
               func_00104520(e->flags, 0x16) != 0 && func_00104520(e->flags, 0x17) != 0) {
        func_002075F0(&pkt, obj, (u32)((depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f));
    }
    e->flags &= 0xFF0FFFFF;
    return 0;
}

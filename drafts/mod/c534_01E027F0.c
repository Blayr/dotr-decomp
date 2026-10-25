#include "common.h"

/* shape c534:01E027F0, 399 insns: LkSortLevelmark: draws a row of n level marks (b001:01E03860's sprite packet,
   colour via c534:01E00100, blend by flags 0xB / 0xA): each mark a square of half-size 0xC around its point, texel
   UVs from the sprite rect (flag 0) unless flag 0x18, drawn when all four corners land (flags 0x14..0x17); a mark
   whose counter is 9999 sits in its slot of the row (x = (2i - (n - 1)) * size, y -15, z 120), otherwise it eases
   toward z 600 at 150 and parks at 9999 once there */

typedef struct {
    u8 b, g, r, a;
} Src_c534_01E027F0;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_c534_01E027F0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Uv_c534_01E027F0 uv;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_c534_01E027F0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_c534_01E027F0 v[4];
    u8 tail[0x20];
} Pkt_c534_01E027F0;

typedef struct {
    f32 x, y, z;
    u8 padC[2];
    s16 cnt;
} Pt_c534_01E027F0;

typedef struct {
    void *texture;
    s32 flags;
    Src_c534_01E027F0 color;
    f32 size;
    u8 pad10[0x10];
    s16 u;
    s16 v;
    s16 w;
    s16 h;
    u8 pad28[8];
    Pt_c534_01E027F0 pt[16];
    s16 n;
} Mark_c534_01E027F0;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_c534_01E027F0;

static s32 func_01E027F0_c534(s32 obj, Cam_c534_01E027F0 *cam, Mark_c534_01E027F0 *m) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00103390(void *, f32, f32);
    extern void func_01E00100_c534();
    f32 depth[4];
    Vec4f p;
    Pkt_c534_01E027F0 pkt;
    s32 i;

    ((Pkt_c534_01E027F0 *)(s32)&pkt)->count = 0x34;
    ((Pkt_c534_01E027F0 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_c534_01E027F0 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_c534_01E027F0 *)(s32)&pkt)->pad = 0;
    if (func_00104520(m->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(m->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    func_01E00100_c534(&pkt, &m->color);
    ((Pkt_c534_01E027F0 *)(s32)&pkt)->count |= 0x800;
    pkt.v[0].uv.u = m->u << 4;
    pkt.v[0].uv.v = m->v << 4;
    pkt.v[1].uv.u = (m->u + m->w - 1) << 4;
    pkt.v[1].uv.v = m->v << 4;
    pkt.v[2].uv.u = m->u << 4;
    pkt.v[2].uv.v = (m->v + m->h - 1) << 4;
    pkt.v[3].uv.u = (m->u + m->w - 1) << 4;
    pkt.v[3].uv.v = (m->v + m->h - 1) << 4;
    for (i = 0; i < m->n; i++) {
        p.x = m->pt[i].x - m->size;
        p.y = m->pt[i].y + m->size;
        p.z = m->pt[i].z;
        if (func_00205440(&p, cam->view, &pkt.v[0].uv + 1, &depth[0]) != 0) {
            m->flags |= 0x100000;
        }
        p.x = m->pt[i].x + m->size;
        p.y = m->pt[i].y + m->size;
        if (func_00205440(&p, cam->view, &pkt.v[1].uv + 1, &depth[1]) != 0) {
            m->flags |= 0x200000;
        }
        p.x = m->pt[i].x - m->size;
        p.y = m->pt[i].y - m->size;
        if (func_00205440(&p, cam->view, &pkt.v[2].uv + 1, &depth[2]) != 0) {
            m->flags |= 0x400000;
        }
        p.x = m->pt[i].x + m->size;
        p.y = m->pt[i].y - m->size;
        if (func_00205440(&p, cam->view, &pkt.v[3].uv + 1, &depth[3]) != 0) {
            m->flags |= 0x800000;
        }
        if (func_00104520(m->flags, 0x18) != 0) {
            func_00208700(&pkt, m->texture, 0);
        } else {
            if (func_00104520(m->flags, 0) != 0) {
                func_00208CB0(&pkt, (u64)0xA | ((u64)m->u << 4) | ((u64)(m->u + m->w - 1) << 14) |
                                        ((u64)m->v << 24) | ((u64)(m->v + m->h - 1) << 34));
            }
            func_00208700(&pkt, m->texture, 1);
        }
        if (func_00104520(m->flags, 0x14) != 0 && func_00104520(m->flags, 0x15) != 0 &&
            func_00104520(m->flags, 0x16) != 0 && func_00104520(m->flags, 0x17) != 0) {
            pkt.v[0].z = pkt.v[1].z = pkt.v[2].z = pkt.v[3].z = 0xFFFFFF;
            func_002075F0(&pkt, obj, 0);
        }
        m->flags &= 0xFF0FFFFF;
        if (m->pt[i].cnt == 9999) {
            m->pt[i].x = -m->size * (m->n - 1) + m->size * (i * 2);
            m->pt[i].y = -15.0f;
            m->pt[i].z = 120.0f;
        } else if (func_00103390(&m->pt[i].z, 600.0f, 150.0f) == 0) {
            m->pt[i].cnt = 9999;
        } else {
            m->pt[i].cnt++;
        }
    }
    return 0;
}

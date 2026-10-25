#include "common.h"

/* shape b379:01E046B0, 369 insns: ShFx_GRing: for each live emitter (0x3C each) the two radii grow by their speeds,
   its point follows the source (func_00101BA0) and a quarter ring of up to 9 segments (90 / n degrees each) is drawn
   as Gouraud quads between the inner and outer radius, mirrored into all four quarters; inner colour 0x0C..0x0F,
   outer 0x08..0x0B, alpha scaled by life / 8 for the first 8 frames unless flag 0x40; returns 1 */

typedef struct {
    u8 life;
    u8 pad1[3];
    u8 flags;
    u8 pad5[2];
    u8 segs;
    u8 b1, g1, r1, a1;
    u8 b0, g0, r0, a0;
    f32 rin;
    f32 rout;
    f32 din;
    f32 dout;
    f32 x, y, z;
    s32 rot[4];
} Emit_b379_01E046B0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b379_01E046B0;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b379_01E046B0 v[4];
} Pkt_b379_01E046B0;

static s32 func_01E046B0_b379(void *arg0, s32 ot __attribute__((aligned(8))), s32 n) {
    extern void func_00101BA0(void *, void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_0020EB40(void *);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020BC00(void *, void *);
    extern void func_002075F0(void *, s32, s32);
    Emit_b379_01E046B0 *e = arg0;
    f32 m2[16];
    f32 mat[16];
    Vec4f ab[2][10];
    Vec4f q[4];
    f32 d[4];
    f32 v[6];
    Pkt_b379_01E046B0 pkt __attribute__((aligned(8)));
    s32 i;
    s32 segs;
    s32 j;
    s32 k;
    s32 m;
    f32 step;
    f32 ang;
    f32 c;

    for (i = 0; i < n; i++) {
        if (i != 0) {
            e++;
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        e->rin += e->din;
        e->rout += e->dout;
        segs = e->segs;
        if (segs > 9) {
            segs = 9;
        }
        step = 90.0f / segs;
        v[0] = e->x;
        v[1] = e->y;
        v[2] = e->z;
        func_00101BA0(e, v);
        e->x = v[0];
        e->y = v[1];
        e->z = v[2];
        func_0020EB40(mat);
        func_0020C940(m2, 0, e->rot, v);
        func_0020BC00(mat, m2);
        for (k = 0; k < segs + 1; k++) {
            ang = 3.1415927f * (step * k) / 180.0f;
            c = func_001A6A88(ang);
            ang = func_001A6898(ang);
            ab[0][k].x = e->rin * ang;
            ab[0][k].z = e->rin * c;
            ab[1][k].x = e->rout * ang;
            ab[1][k].z = e->rout * c;
        }
        ((Pkt_b379_01E046B0 *)(s32)&pkt)->count = 0x14;
        ((Pkt_b379_01E046B0 *)(s32)&pkt)->tag = 8;
        ((Pkt_b379_01E046B0 *)(s32)&pkt)->regs = 0x41414141;
        ((Pkt_b379_01E046B0 *)(s32)&pkt)->pad = 0;
        pkt.v[0].r = pkt.v[1].r = e->r0;
        pkt.v[2].r = pkt.v[3].r = e->r1;
        pkt.v[0].g = pkt.v[1].g = e->g0;
        pkt.v[2].g = pkt.v[3].g = e->g1;
        pkt.v[0].b = pkt.v[1].b = e->b0;
        pkt.v[2].b = pkt.v[3].b = e->b1;
        pkt.v[0].q = pkt.v[1].q = pkt.v[2].q = pkt.v[3].q = 1.0f;
        pkt.v[0].f = pkt.v[1].f = pkt.v[2].f = pkt.v[3].f = 0;
        pkt.v[0].a = pkt.v[1].a = e->a0;
        pkt.v[2].a = pkt.v[3].a = e->a1;
        if (!(e->flags & 0x40) && e->life < 8) {
            pkt.v[0].a = pkt.v[1].a = (e->a0 >> 3) * e->life;
            pkt.v[2].a = pkt.v[3].a = (e->a1 >> 3) * e->life;
        }
        func_002086D0(&pkt, 0x48);
        q[0].w = q[1].w = q[2].w = q[3].w = 0.0f;
        for (j = 0; j < segs; j++) {
            for (m = 0; m < 4; m++) {
                switch (m) {
                case 0:
                    q[0].x = ab[0][j].x;
                    q[1].x = ab[0][j + 1].x;
                    q[2].x = ab[1][j].x;
                    q[3].x = ab[1][j + 1].x;
                    q[0].z = ab[0][j].z;
                    q[1].z = ab[0][j + 1].z;
                    q[2].z = ab[1][j].z;
                    q[3].z = ab[1][j + 1].z;
                    break;
                case 1:
                    q[0].x = -ab[0][j].x;
                    q[1].x = -ab[0][j + 1].x;
                    q[2].x = -ab[1][j].x;
                    q[3].x = -ab[1][j + 1].x;
                    break;
                case 2:
                    q[0].z = -ab[0][j].z;
                    q[1].z = -ab[0][j + 1].z;
                    q[2].z = -ab[1][j].z;
                    q[3].z = -ab[1][j + 1].z;
                    break;
                case 3:
                    q[0].x = ab[0][j].x;
                    q[1].x = ab[0][j + 1].x;
                    q[2].x = ab[1][j].x;
                    q[3].x = ab[1][j + 1].x;
                    break;
                }
                if (func_00205440(&q[0], mat, &pkt.v[0].x, &d[0]) != 0 &&
                    func_00205440(&q[1], mat, &pkt.v[1].x, &d[1]) != 0 &&
                    func_00205440(&q[2], mat, &pkt.v[2].x, &d[2]) != 0 &&
                    func_00205440(&q[3], mat, &pkt.v[3].x, &d[3]) != 0) {
                    func_002075F0(&pkt, ot, (u32)((d[0] + d[1] + d[2] + d[3]) / 4.0f));
                }
            }
        }
    }
    return 1;
}

#include "common.h"

/* shape b738:01E05B00, 333 insns, 1 copy (Gb738_GenAuraTex), b704:01E03240 twin: renders the aura texture: clears a sprite-sized grey square,
   then draws the aura's 16 x 16 grid of quads (points at aura+0x8DE0, 17 a row) in grey (0x80, alpha 0x64) with a 4 x 4
   tiled UV, through a matrix from the aura's position turned randomly on all three axes */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b738_01E05B00;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b738_01E05B00;

typedef struct {
    s16 count;
    s16 tag;
    s32 pad;
    u64 regs;
} Hdr_b738_01E05B00;

typedef struct {
    u64 tag;
    Hdr_b738_01E05B00 h;
    Rgbaq_b738_01E05B00 c;
    Xyz_b738_01E05B00 v[2];
} Clr_b738_01E05B00;

typedef struct {
    Rgbaq_b738_01E05B00 c;
    f32 s;
    f32 t;
    Xyz_b738_01E05B00 xyz;
} Vtx_b738_01E05B00;

typedef struct {
    Hdr_b738_01E05B00 h;
    Vtx_b738_01E05B00 v[4];
    u8 tail[0x24];
} Pkt_b738_01E05B00;

typedef struct {
    u8 pad0[0x1C];
    s32 tex;
    u8 pad20[0x50];
    Vec4f pos;
    u8 pad80[0x8D60];
    Vec4f grid[17][17];
} Aura_b738_01E05B00;

static void func_01E05B00_b738(s32 arg0) {
    extern Aura_b738_01E05B00 *D_01E06080_b738;
    extern s32 func_00209F70();
    extern s32 func_00207650(s32, void *, s32, s32);
    extern void func_002086D0(void *, u64);
    extern u64 func_00208D00(s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00208CB0(void *, s32);
    extern void func_0020EB40(void *);
    extern void func_0020BBB0(void *);
    extern void func_00187B60(void *, void *, void *);
    extern void func_00100E00(void *, s32, s32);
    extern void func_0020BC00(void *, void *);
    extern s32 func_00100BA0(void *, void *, void *, void *, void *, void *, s32 *);
    s32 out;
    f32 m[16];
    f32 m2[16];
    Clr_b738_01E05B00 clr;
    Pkt_b738_01E05B00 pk;
    Aura_b738_01E05B00 *a;
    s32 j;
    s32 i;
    s32 ot;
    s32 r;
    s32 c;
    f32 t0;
    f32 t1;
    f32 s0;
    f32 s1;

    a = D_01E06080_b738;
    ot = func_00209F70(arg0, 0xFF000000);
    ((Hdr_b738_01E05B00 *)(s32)&clr.h)->tag = 6;
    ((Hdr_b738_01E05B00 *)(s32)&clr.h)->count = 3;
    ((Hdr_b738_01E05B00 *)(s32)&clr.h)->regs = 0x441;
    ((Hdr_b738_01E05B00 *)(s32)&clr.h)->pad = 0;
    func_002086D0(&clr.h, func_00208D00(2));
    clr.c.r = 0x40;
    clr.c.g = 0x40;
    clr.c.b = 0x40;
    clr.c.a = 0x80;
    clr.c.q = 1.0f;
    clr.v[0].x = 0x6BF8;
    clr.v[0].y = 0x71F8;
    clr.v[0].z = 0xFFFFF8;
    clr.v[0].f = 0;
    clr.v[1].x = 0x93F8;
    clr.v[1].y = 0x8DF8;
    clr.v[1].z = 0xFFFFF8;
    clr.v[1].f = 0;
    ot = func_00207650(ot, &clr.h, 0, 0);
    ((Hdr_b738_01E05B00 *)(s32)&pk)->tag = 0x34;
    ((Hdr_b738_01E05B00 *)(s32)&pk)->count = 0xC;
    ((Hdr_b738_01E05B00 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Hdr_b738_01E05B00 *)(s32)&pk)->pad = 0;
    func_002086D0(&pk, func_00208D00(1));
    func_00208700(&pk, a->tex, 1);
    func_00208CB0(&pk, 0);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_00187B60(m2, m2, &a->pos);
    func_00100E00(m2, ((func_0019A5C8() >> 23) % 256 << 16) >> 8, 0);
    func_00100E00(m2, ((func_0019A5C8() >> 23) % 256 << 16) >> 8, 1);
    func_00100E00(m2, ((func_0019A5C8() >> 23) % 256 << 16) >> 8, 2);
    func_0020BC00(m, m2);
    pk.v[0].c.r = 0x80;
    pk.v[0].c.g = 0x80;
    pk.v[0].c.b = 0x80;
    pk.v[0].c.a = 0x64;
    pk.v[0].c.q = 1.0f;
    pk.v[1].c = pk.v[0].c;
    pk.v[2].c = pk.v[0].c;
    pk.v[3].c = pk.v[0].c;
    for (j = 0; j < 16; j++) {
        r = j % 4;
        t0 = r / 4.0f;
        t1 = (r + 1) / 4.0f;
        for (i = 0; i < 16; i++) {
            c = i % 4;
            s0 = c / 4.0f;
            s1 = (c + 1) / 4.0f;
            pk.v[0].s = s0;
            pk.v[0].t = t0;
            pk.v[1].s = s1;
            pk.v[1].t = t0;
            pk.v[2].s = s0;
            pk.v[2].t = t1;
            pk.v[3].s = s1;
            pk.v[3].t = t1;
            if (func_00100BA0(&a->grid[j][i], &a->grid[j][i + 1], &a->grid[j + 1][i], &a->grid[j + 1][i + 1], m, &pk, &out) == 1) {
                pk.v[0].xyz.z = 0xFFFFF8;
                pk.v[1].xyz.z = pk.v[0].xyz.z;
                pk.v[2].xyz.z = pk.v[0].xyz.z;
                pk.v[3].xyz.z = pk.v[0].xyz.z;
                ot = func_00207650(ot, &pk, 0, 0);
            }
        }
    }
    func_00209F70(ot, 0);
}

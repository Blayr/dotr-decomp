#include "common.h"

/* shape b216:01E052E0, 173 insns: two flat GS sprites between func_00209F70 calls (mask 0xFF000000 on, then off):
   first a textured white one (RGBAQ, UV, XYZ2, UV, XYZ2) on the frame func_00208870 picks, then a red one
   (RGBAQ, XYZ2, XYZ2) over the same 0x6BF8..0x93F8 x 0x71F8..0x8DF8 box */

typedef struct {
    u16 tag;
    u16 count;
    s32 pad;
    u64 regs;
} Hdr_b216_01E052E0;

typedef struct {
    u64 u : 14;
    u64 pu : 2;
    u64 v : 14;
    u64 pv : 34;
} Uv_b216_01E052E0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b216_01E052E0;

typedef struct {
    Hdr_b216_01E052E0 h;
    u8 r, g, b, a;
    f32 q;
    Uv_b216_01E052E0 uv0;
    Xyz_b216_01E052E0 p0;
    Uv_b216_01E052E0 uv1;
    Xyz_b216_01E052E0 p1;
    u64 tail;
} Tex_b216_01E052E0;

typedef struct {
    Hdr_b216_01E052E0 h;
    u8 r, g, b, a;
    f32 q;
    Xyz_b216_01E052E0 p0;
    Xyz_b216_01E052E0 p1;
    u64 tail;
} Flat_b216_01E052E0;

static void func_01E052E0_b216(void *arg0) {
    extern void *func_00209F70(void *, u32);
    extern s32 func_0020F290(s32);
    extern s32 func_00208870(s32, s32, s32, void *, void *);
    extern u64 func_00208D00(s32);
    extern void func_002086D0(void *, u64);
    extern s32 func_00208CB0(void *, u64);
    extern void *func_00207650(void *, void *, s32, s32);

    Flat_b216_01E052E0 f __attribute__((aligned(8)));
    Tex_b216_01E052E0 t __attribute__((aligned(8)));
    u64 w;
    u64 h;
    void *ctx;
    void *c2;

    ctx = func_00209F70(arg0, 0xFF000000);
    ((Hdr_b216_01E052E0 *)(s32)&t)->count = 0x26;
    ((Hdr_b216_01E052E0 *)(s32)&t)->tag = 5;
    ((Hdr_b216_01E052E0 *)(s32)&t)->regs = 0x42421;
    ((Hdr_b216_01E052E0 *)(s32)&t)->pad = 0;
    ctx = (void *)func_0020F290(func_00208870(func_0020F290((s32)ctx), -1, 1, &w, &h));
    func_002086D0(&t, func_00208D00(0));
    func_00208CB0(&t, 0x0000070000A0000AULL);
    ((Hdr_b216_01E052E0 *)(s32)&t)->count |= 0x800;
    t.r = 0xFF;
    t.g = 0xFF;
    t.b = 0xFF;
    t.a = 0x80;
    t.q = 1.0f;
    t.uv0.u = 0;
    t.uv0.v = 0;
    t.uv1.u = 0x2800;
    t.uv1.v = 0x1C00;
    t.p0.x = 0x6BF8;
    t.p0.y = 0x71F8;
    t.p0.z = 0xFFFFF8;
    t.p0.f = 0;
    t.p1.x = 0x93F8;
    t.p1.y = 0x8DF8;
    t.p1.z = 0xFFFFF8;
    t.p1.f = 0;
    c2 = func_00207650(ctx, &t, 0, 0);
    ((Hdr_b216_01E052E0 *)(s32)&f)->count = 6;
    ((Hdr_b216_01E052E0 *)(s32)&f)->tag = 3;
    ((Hdr_b216_01E052E0 *)(s32)&f)->regs = 0x441;
    ((Hdr_b216_01E052E0 *)(s32)&f)->pad = 0;
    func_002086D0(&f, func_00208D00(3));
    f.r = 0x80;
    f.g = 0;
    f.b = 0;
    f.a = 0xFF;
    f.q = 1.0f;
    f.p0.x = 0x6BF8;
    f.p0.y = 0x71F8;
    f.p0.z = 0xFFFFF8;
    f.p0.f = 0;
    f.p1.x = 0x93F8;
    f.p1.y = 0x8DF8;
    f.p1.z = 0xFFFFF8;
    f.p1.f = 0;
    func_00209F70(func_00207650(c2, &f, 0, 0), 0);
}

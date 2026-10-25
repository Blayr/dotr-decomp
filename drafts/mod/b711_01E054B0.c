#include "common.h"

/* shape b711:01E054B0, 174 insns: b453:01E02F10 with the orange cover at (0xC8, 0x46, 0) alpha 0xE4 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b711_01E054B0;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Xyz_b711_01E054B0 v[2];
    u64 tail;
} Flat_b711_01E054B0;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u8 pad4[4];
    Xyz_b711_01E054B0 p;
} Uv_b711_01E054B0;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Uv_b711_01E054B0 v[2];
    u64 tail;
} Spr_b711_01E054B0;

static void func_01E054B0_b711(void *buf) {
    extern void *func_00209F70(void *, u32);
    extern void *func_0020F290(void *);
    extern void *func_00208870(void *, s32, s32, void *, void *);
    extern u64 func_00208D00(s32);
    extern void func_00208CB0(void *, u64);
    extern void *func_00207650(void *, void *, s32, s32);
    Flat_b711_01E054B0 flat __attribute__((aligned(8)));
    Spr_b711_01E054B0 pk __attribute__((aligned(8)));
    s32 a;
    s32 b;
    void *p;

    p = func_00209F70(buf, 0xFF000000);
    ((Spr_b711_01E054B0 *)(s32)&pk)->flags = 0x26;
    ((Spr_b711_01E054B0 *)(s32)&pk)->size = 5;
    ((Spr_b711_01E054B0 *)(s32)&pk)->regs = 0x42421;
    ((Spr_b711_01E054B0 *)(s32)&pk)->pad4 = 0;
    p = func_0020F290(func_00208870(func_0020F290(p), -1, 1, &a, &b));
    func_002086D0(&pk, func_00208D00(0));
    func_00208CB0(&pk, ((u64)0x700 << 32) | 0xA0000A);
    ((Spr_b711_01E054B0 *)(s32)&pk)->flags |= 0x800;
    pk.r = 0xFF;
    pk.g = 0xFF;
    pk.b = 0xFF;
    pk.a = 0x80;
    pk.q = 1.0f;
    pk.v[0].u = 0;
    pk.v[0].v = 0;
    pk.v[1].u = 0x2800;
    pk.v[1].v = 0x1C00;
    pk.v[0].p.x = 0x6BF8;
    pk.v[0].p.y = 0x71F8;
    pk.v[0].p.z = 0xFFFFF8;
    pk.v[0].p.f = 0;
    pk.v[1].p.x = 0x93F8;
    pk.v[1].p.y = 0x8DF8;
    pk.v[1].p.z = 0xFFFFF8;
    pk.v[1].p.f = 0;
    p = func_00207650(p, &pk, 0, 0);
    ((Flat_b711_01E054B0 *)(s32)&flat)->flags = 6;
    ((Flat_b711_01E054B0 *)(s32)&flat)->size = 3;
    ((Flat_b711_01E054B0 *)(s32)&flat)->regs = 0x441;
    ((Flat_b711_01E054B0 *)(s32)&flat)->pad4 = 0;
    func_002086D0(&flat, func_00208D00(3));
    flat.r = 0xC8;
    flat.g = 0x46;
    flat.b = 0;
    flat.a = 0xE4;
    flat.q = 1.0f;
    flat.v[0].x = 0x6BF8;
    flat.v[0].y = 0x71F8;
    flat.v[0].z = 0xFFFFF8;
    flat.v[0].f = 0;
    flat.v[1].x = 0x93F8;
    flat.v[1].y = 0x8DF8;
    flat.v[1].z = 0xFFFFF8;
    flat.v[1].f = 0;
    p = func_00207650(p, &flat, 0, 0);
    func_00209F70(p, 0);
}

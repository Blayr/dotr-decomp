#include "common.h"

INCLUDE_ASM("asm/nonmatchings/mod/b713", func_01E00080_b713);

/* shape b222:01E03780, 192 insns: draw a flat dark sprite (screen rect 0x6C00,0x7200 - 0x9400,0x8E00, far z) and a
   40x40 textured quad at the scene object's position whose texture scrolls with the object's counter (t =
   -(counter % 32) / 32); the quad is sent only when it projects fully on screen */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b222_01E03780;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Xyz_b222_01E03780 v[2];
    u64 tail;
} Flat_b222_01E03780;

typedef struct {
    f32 s, t;
    Xyz_b222_01E03780 p;
} Tv_b222_01E03780;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b222_01E03780 v[2];
    u8 tail[0x20];
} Tex_b222_01E03780;

typedef struct {
    s32 counter;
    u8 pad4[0x14];
    void *texture;
    u8 pad1C[4];
    u8 pos[0x10];
} Obj_b222_01E03780;

extern Obj_b222_01E03780 *D_01E03B00_b713;
extern u8 D_0030FF00[];

static void func_01E03780_b713(void *buf) {
    extern void *func_00209F70(void *, u32);
    extern void func_00205CA0(void *);
    extern u64 func_00208D00(s32);
    extern void *func_00207650(void *, void *, s32, s32);
    extern void func_00187B60(void *, void *, void *);
    f32 m[4][4];
    f32 m2[4][4];
    f32 cam[4][4];
    Vec4f v[2];
    Flat_b222_01E03780 flat __attribute__((aligned(8)));
    Tex_b222_01E03780 pk __attribute__((aligned(8)));
    f32 depth;
    Obj_b222_01E03780 *o;
    void *p;
    f32 t;
    f32 w;

    o = D_01E03B00_b713;
    p = func_00209F70(buf, 0xFF000000);
    func_00205CA0(cam);
    ((Flat_b222_01E03780 *)(s32)&flat)->flags = 6;
    ((Flat_b222_01E03780 *)(s32)&flat)->size = 3;
    ((Flat_b222_01E03780 *)(s32)&flat)->regs = 0x441;
    ((Flat_b222_01E03780 *)(s32)&flat)->pad4 = 0;
    func_002086D0(&flat, func_00208D00(0));
    flat.r = 0;
    flat.g = 0;
    flat.b = 0;
    flat.a = 0x80;
    flat.q = 1.0f;
    flat.v[0].x = 0x6C00;
    flat.v[0].y = 0x7200;
    flat.v[0].z = 0xFFFFF8;
    flat.v[0].f = 0;
    flat.v[1].x = 0x9400;
    flat.v[1].y = 0x8E00;
    flat.v[1].z = 0xFFFFF8;
    flat.v[1].f = 0;
    p = func_00207650(p, &flat, 0, 0);
    ((Tex_b222_01E03780 *)(s32)&pk)->flags = 0x26;
    ((Tex_b222_01E03780 *)(s32)&pk)->size = 5;
    ((Tex_b222_01E03780 *)(s32)&pk)->regs = 0x42421;
    ((Tex_b222_01E03780 *)(s32)&pk)->pad4 = 0;
    func_002086D0(&pk, func_00208D00(1));
    func_00208700(&pk, o->texture, 1);
    func_00208CB0(&pk, 0);
    func_0020EB40(m);
    func_00187B60(m2, cam, o->pos);
    func_0020BC00((s32)m, m2);
    pk.r = 0xFF;
    pk.g = 0xFF;
    pk.b = 0xFF;
    pk.a = 0x80;
    pk.q = 1.0f;
    t = (-1.0f * (o->counter % 32)) / 32.0f;
    w = 20.0f;
    pk.v[0].s = 0.0f;
    pk.v[0].t = t;
    pk.v[1].s = 5.0f;
    pk.v[1].t = 2.0f + t;
    v[0].x = -w;
    v[0].y = -w;
    v[0].z = 0.0f;
    v[0].w = 1.0f;
    v[1].x = w;
    v[1].y = w;
    v[1].z = 0.0f;
    v[1].w = 1.0f;
    if (func_00205630((s32)v, (s32)D_0030FF00, (s32)m, (s32)&pk, &depth) == 1) {
        pk.v[0].p.z = 0xFFFFF8;
        pk.v[1].p.z = pk.v[0].p.z;
        p = func_00207650(p, &pk, 0, 0);
    }
    func_00209F70(p, 0);
}

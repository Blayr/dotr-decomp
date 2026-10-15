#include "common.h"

INCLUDE_ASM("asm/nonmatchings/mod/b066", func_01E00080_b066);

INCLUDE_ASM("asm/nonmatchings/mod/b066", func_01E036B0_b066);

/* shape b066:01E03BE0, 69 insns, 8 copies: one flat GS sprite (RGBAQ, XYZ2, XYZ2) in grey 0x80, drawn between two
   func_00209F70 calls (mask 0xFF000000 on, then off) */

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
} Hdr_b066_01E03BE0;

typedef struct {
    Hdr_b066_01E03BE0 h;
    u8 r, g, b, a;
    f32 q;
    u64 x0 : 16;
    u64 y0 : 16;
    u64 z0 : 24;
    u64 f0 : 8;
    u64 x1 : 16;
    u64 y1 : 16;
    u64 z1 : 24;
    u64 f1 : 8;
} Pkt_b066_01E03BE0;

static void func_01E03BE0_b066(void *arg0) {
    extern void *func_00207650();
    Pkt_b066_01E03BE0 p;
    void *ctx;

    ctx = func_00209F70(arg0, 0xFF000000);
    ((Hdr_b066_01E03BE0 *)(s32)&p)->count = 6;
    ((Hdr_b066_01E03BE0 *)(s32)&p)->tag = 3;
    ((Hdr_b066_01E03BE0 *)(s32)&p)->regs = 0x441;
    ((Hdr_b066_01E03BE0 *)(s32)&p)->pad = 0;
    func_002086D0(&p, func_00208D00(3));
    p.r = 0x80;
    p.g = 0x80;
    p.b = 0x80;
    p.a = 0xFF;
    p.q = 1.0f;
    p.x0 = 0x6BF8;
    p.y0 = 0x71F8;
    p.z0 = 0xFFFFF8;
    p.f0 = 0;
    p.x1 = 0x93F8;
    p.y1 = 0x8DF8;
    p.z1 = 0xFFFFF8;
    p.f1 = 0;
    func_00209F70(func_00207650(ctx, &p, 0, 0), 0);
}

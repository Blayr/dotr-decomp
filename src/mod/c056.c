#include "common.h"

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E00080_c056);

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E00240_c056);

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E00360_c056);

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E00800_c056);

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E00C10_c056);

/* shape c056:01E00C50, 54 insns, 1 copy: spawn an effect entity, random angle % 360; its callback is
   c056:01E02560 */

typedef struct Col_c056_01E00C50 {
    u8 r, g, b, a;
} Col_c056_01E00C50;

typedef struct Ent_c056_01E00C50 {
    u8 pad0[0x64];
    f32 f64;
    u8 pad68[0x30];
    void (*cb)(void);
    s32 arg;
    u8 padA0[0xC];
    Col_c056_01E00C50 col0;
    Col_c056_01E00C50 col1;
    u8 padB4[4];
    s16 fB8;
    u8 padBA[2];
    s16 fBC;
    s16 fBE;
} Ent_c056_01E00C50;

typedef struct Ctx_c056_01E00C50 {
    u8 pad0[0x84];
    f32 f84;
    u8 pad88[0xC60 - 0x88];
    u8 pool[0x4480 - 0xC60];
    u8 rgba[4];
    u8 pad4484[0x449C - 0x4484];
    f32 pos[3];
    u8 pad44A8[0x10];
    s16 f44B8;
    u8 pad44BA[2];
    s16 f44BC;
} Ctx_c056_01E00C50;

extern void c056_01E02560(void);

static void func_01E00C50_c056(Ctx_c056_01E00C50 *ctx, s32 arg) {
    extern void func_001076F0();
    Ent_c056_01E00C50 *e = (Ent_c056_01E00C50 *)func_00106A00((s32)ctx, (s32)ctx->pool, 0x46, 0);

    if (e != NULL) {
        func_001076F0(&e->col0, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        e->col0.a = 0;
        func_001076F0(&e->col1, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        e->col1.a = 0;
        e->f64 = ctx->f84;
        func_00107E40(ctx->pos[0], ctx->pos[1], ctx->pos[2], e);
        e->fBC = ctx->f44BC;
        e->fBE = func_0019A5C8() % 360;
        e->cb = c056_01E02560;
        e->arg = arg;
        e->fB8 = ctx->f44B8;
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E00D30_c056);

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E00F30_c056);

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E010E0_c056);

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E011C0_c056);

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E012A0_c056);

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E01490_c056);

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E015A0_c056);

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E02020_c056);

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E022F0_c056);

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E02560_c056);

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E02790_c056);

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E02BE0_c056);

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E02E10_c056);

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E03090_c056);

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E03AE0_c056);

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E03DA0_c056);

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E03FE0_c056);

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E044B0_c056);

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E04780_c056);

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E04830_c056);

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E04900_c056);

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E04CF0_c056);

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E04FE0_c056);

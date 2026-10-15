#include "common.h"

INCLUDE_ASM("asm/nonmatchings/mod/c021", func_01E00080_c021);

INCLUDE_ASM("asm/nonmatchings/mod/c021", func_01E00630_c021);

/* shape c021:01E00AF0, 40 insns, 1 copy */

typedef struct Ctx_c021_01E00AF0 {
    u8 pad0[0x3578];
    s32 timer;
    u8 pad357C[0x38BA - 0x357C];
    s16 phase;
} Ctx_c021_01E00AF0;

typedef struct Obj_c021_01E00AF0 {
    u8 pad0[0x7F];
    u8 c7F;
    u8 pad80[3];
    u8 c83;
    s16 f84;
} Obj_c021_01E00AF0;

static s32 func_01E00AF0_c021(Ctx_c021_01E00AF0 *ctx, Obj_c021_01E00AF0 *o) {
    if (ctx->phase < 8) {
        if (o->c7F < 0x80) {
            o->c7F += 0x20;
        }
        if (o->c83 < 0x60) {
            o->c83 += 0x20;
        }
    }
    if (ctx->timer < 0x12) {
        if (o->c7F > 0x10) {
            o->c7F -= 0xF;
        }
        if (o->c83 > 0x10) {
            o->c83 -= 0xF;
        }
    }
    if (ctx->timer < 0xB) {
        o->f84 = 0;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/c021", func_01E00B90_c021);

INCLUDE_ASM("asm/nonmatchings/mod/c021", func_01E00E00_c021);

INCLUDE_ASM("asm/nonmatchings/mod/c021", func_01E013C0_c021);

INCLUDE_ASM("asm/nonmatchings/mod/c021", func_01E016C0_c021);

INCLUDE_ASM("asm/nonmatchings/mod/c021", func_01E01C50_c021);

INCLUDE_ASM("asm/nonmatchings/mod/c021", func_01E01E10_c021);

INCLUDE_ASM("asm/nonmatchings/mod/c021", func_01E01F60_c021);

INCLUDE_ASM("asm/nonmatchings/mod/c021", func_01E02350_c021);

INCLUDE_ASM("asm/nonmatchings/mod/c021", func_01E02820_c021);

INCLUDE_ASM("asm/nonmatchings/mod/c021", func_01E028F0_c021);

INCLUDE_ASM("asm/nonmatchings/mod/c021", func_01E029F0_c021);

INCLUDE_ASM("asm/nonmatchings/mod/c021", func_01E02BE0_c021);

INCLUDE_ASM("asm/nonmatchings/mod/c021", func_01E02E40_c021);

INCLUDE_ASM("asm/nonmatchings/mod/c021", func_01E03060_c021);

INCLUDE_ASM("asm/nonmatchings/mod/c021", func_01E03280_c021);

INCLUDE_ASM("asm/nonmatchings/mod/c021", func_01E03390_c021);

INCLUDE_ASM("asm/nonmatchings/mod/c021", func_01E038A0_c021);

INCLUDE_ASM("asm/nonmatchings/mod/c021", func_01E03BA0_c021);

INCLUDE_ASM("asm/nonmatchings/mod/c021", func_01E03EA0_c021);

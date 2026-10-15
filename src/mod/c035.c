#include "common.h"

INCLUDE_ASM("asm/nonmatchings/mod/c035", func_01E00080_c035);

INCLUDE_ASM("asm/nonmatchings/mod/c035", func_01E00310_c035);

/* shape c035:01E004D0, 43 insns, 1 copy */

typedef struct Ctx_c035_01E004D0 {
    u8 pad[0x34D0];
    s32 phase;
} Ctx_c035_01E004D0;

typedef struct Obj_c035_01E004D0 {
    u8 pad0[0x43];
    u8 c43;
    u8 pad44[3];
    u8 c47;
    s16 f48;
    u8 pad4A[0x10];
    s16 t;
} Obj_c035_01E004D0;

static s32 func_01E004D0_c035(Ctx_c035_01E004D0 *ctx, Obj_c035_01E004D0 *o) {
    if (o->t < 8) {
        if (o->c43 < 0xC0) {
            o->c43 += 0x18;
        }
        if (o->c47 < 0xC0) {
            o->c47 += 0x18;
        }
    } else if (o->t >= 0xD) {
        if (o->c43 > 0xB) {
            o->c43 -= 10;
        }
        if (o->c47 > 0xB) {
            o->c47 -= 10;
        }
    }
    o->t++;
    if (ctx->phase == 2) {
        o->f48 = 0;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/c035", func_01E00580_c035);

INCLUDE_ASM("asm/nonmatchings/mod/c035", func_01E00710_c035);

INCLUDE_ASM("asm/nonmatchings/mod/c035", func_01E00860_c035);

INCLUDE_ASM("asm/nonmatchings/mod/c035", func_01E009B0_c035);

INCLUDE_ASM("asm/nonmatchings/mod/c035", func_01E00B80_c035);

INCLUDE_ASM("asm/nonmatchings/mod/c035", func_01E00F60_c035);

INCLUDE_ASM("asm/nonmatchings/mod/c035", func_01E01050_c035);

INCLUDE_ASM("asm/nonmatchings/mod/c035", func_01E01150_c035);

/* shape b073:01E03BC0, 2 insns, 5 copies: an empty callback */

static void func_01E01280_c035(void) {
}

INCLUDE_ASM("asm/nonmatchings/mod/c035", func_01E01290_c035);

INCLUDE_ASM("asm/nonmatchings/mod/c035", func_01E013A0_c035);

INCLUDE_ASM("asm/nonmatchings/mod/c035", func_01E01580_c035);

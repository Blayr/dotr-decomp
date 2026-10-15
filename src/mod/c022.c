#include "common.h"

INCLUDE_ASM("asm/nonmatchings/mod/c022", func_01E00080_c022);

INCLUDE_ASM("asm/nonmatchings/mod/c022", func_01E00750_c022);

/* shape c022:01E00BA0, 52 insns: c056:01E04780 family two-alpha sprite: in by 32/16 while the scene value is under 8, out by 15 from 36, ends when the counter is under 3 */

typedef struct {
    u8 pad0[0x39f0];
    s32 count;
    u8 padC[0x54];
    s16 val;
} Ctx_c022_01E00BA0;

typedef struct {
    u8 pad0[0x2B];
    u8 alpha;
    u8 pad2C[0x3];
    u8 alpha2;
    u8 pad30[0x2];
    s16 state;
    u8 bA[1];
} Obj_c022_01E00BA0;

static s32 func_01E00BA0_c022(Ctx_c022_01E00BA0 *ctx, Obj_c022_01E00BA0 *o) {
    extern void func_00106D80(s32, void *);

    func_00106D80(5, o->bA);
    if (ctx->val < 0x8) {
        if (o->alpha < 0xC0) {
            o->alpha += 0x20;
        }
        if (o->alpha2 < 0x11) {
            o->alpha2 += 0x10;
        }
    }
    if (ctx->val > 0x23) {
        if (o->alpha > 0x10) {
            o->alpha -= 15;
        }
        if (o->alpha2 > 0x10) {
            o->alpha2 -= 15;
        }
    }
    if (ctx->count < 0x3) {
        o->state = 0;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/c022", func_01E00C70_c022);

INCLUDE_ASM("asm/nonmatchings/mod/c022", func_01E00F10_c022);

INCLUDE_ASM("asm/nonmatchings/mod/c022", func_01E010E0_c022);

/* shape b073:01E03BC0, 2 insns, 5 copies: an empty callback */

static void func_01E01570_c022(void) {
}

INCLUDE_ASM("asm/nonmatchings/mod/c022", func_01E01580_c022);

INCLUDE_ASM("asm/nonmatchings/mod/c022", func_01E01730_c022);

INCLUDE_ASM("asm/nonmatchings/mod/c022", func_01E01850_c022);

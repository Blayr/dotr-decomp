#include "common.h"

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E00080_c059);

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E00340_c059);

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E005C0_c059);

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E006D0_c059);

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E00B30_c059);

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E00FB0_c059);

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E01BB0_c059);

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E01CE0_c059);

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E01EE0_c059);

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E020E0_c059);

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E02310_c059);

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E02460_c059);

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E025E0_c059);

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E02750_c059);

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E02890_c059);

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E029A0_c059);

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E02C10_c059);

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E02DE0_c059);

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E02F40_c059);

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E031C0_c059);

/* shape b073:01E03BC0, 2 insns, 5 copies: an empty callback */

static void func_01E03600_c059(void) {
}

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E03610_c059);

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E03B00_c059);

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E03D70_c059);

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E040B0_c059);

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E04420_c059);

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E053B0_c059);

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E05440_c059);

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E05710_c059);

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E05A70_c059);

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E05E40_c059);

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E05F90_c059);

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E06280_c059);

/* shape c059:01E062F0, 41 insns, 1 copy */

typedef struct Obj_c059_01E062F0 {
    u8 pad0[0x43];
    u8 c43;
    u8 pad44[3];
    u8 c47;
    s16 f48;
    u8 pad4A[0xC];
    s16 f56;
} Obj_c059_01E062F0;

static s32 func_01E062F0_c059(void *ctx, Obj_c059_01E062F0 *o) {
    if (o->f56 == 0) {
        if (o->c47 < 0xE0) {
            o->c47 += 0x30;
        }
        if (o->c43 < 0xE0) {
            o->c43 += 0x30;
        } else {
            o->f56 = 1;
        }
    } else if (o->f56 < 4) {
        o->f56++;
    } else {
        if (o->c47 > 0x13) {
            o->c47 -= 0x10;
        }
        if (o->c43 > 0x13) {
            o->c43 -= 0x10;
        } else {
            o->f48 = 0;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E063A0_c059);

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E06470_c059);

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E065D0_c059);

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E06720_c059);

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E06DC0_c059);

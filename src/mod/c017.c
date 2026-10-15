#include "common.h"

INCLUDE_ASM("asm/nonmatchings/mod/c017", func_01E00080_c017);

INCLUDE_ASM("asm/nonmatchings/mod/c017", func_01E006B0_c017);

INCLUDE_ASM("asm/nonmatchings/mod/c017", func_01E009E0_c017);

INCLUDE_ASM("asm/nonmatchings/mod/c017", func_01E00D50_c017);

INCLUDE_ASM("asm/nonmatchings/mod/c017", func_01E00F10_c017);

/* shape c017:01E01020, 40 insns: both alphas grow by 0x20 (below 0x80 and 0x60) while the game step at 0x3960 is
   below 8; both fade by 15 while the counter at 0x38DC is below 10; the effect stops below 3 */

typedef struct {
    u8 pad0[0x38DC];
    s32 count;
    u8 pad38E0[0x80];
    s16 step;
} Game_c017_01E01020;

typedef struct {
    u8 pad0[0x50];
    u8 col[4];
    u8 col2[4];
    s16 mode;
} Fx_c017_01E01020;

static s32 func_01E01020_c017(Game_c017_01E01020 *g, Fx_c017_01E01020 *o) {
    if (g->step < 8) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x20;
        }
        if (o->col2[3] < 0x60) {
            o->col2[3] += 0x20;
        }
    }
    if (g->count < 10) {
        if (o->col[3] > 0x10) {
            o->col[3] -= 15;
        }
        if (o->col2[3] > 0x10) {
            o->col2[3] -= 15;
        }
    }
    if (g->count < 3) {
        o->mode = 0;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/c017", func_01E010C0_c017);

INCLUDE_ASM("asm/nonmatchings/mod/c017", func_01E01400_c017);

INCLUDE_ASM("asm/nonmatchings/mod/c017", func_01E01610_c017);

INCLUDE_ASM("asm/nonmatchings/mod/c017", func_01E01840_c017);

INCLUDE_ASM("asm/nonmatchings/mod/c017", func_01E019B0_c017);

INCLUDE_ASM("asm/nonmatchings/mod/c017", func_01E01B00_c017);

INCLUDE_ASM("asm/nonmatchings/mod/c017", func_01E01BF0_c017);

INCLUDE_ASM("asm/nonmatchings/mod/c017", func_01E02120_c017);

INCLUDE_ASM("asm/nonmatchings/mod/c017", func_01E025B0_c017);

INCLUDE_ASM("asm/nonmatchings/mod/c017", func_01E02790_c017);

INCLUDE_ASM("asm/nonmatchings/mod/c017", func_01E02970_c017);

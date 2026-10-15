#include "common.h"

INCLUDE_ASM("asm/nonmatchings/mod/c034", func_01E00080_c034);

/* shape c034:01E00290, 45 insns: both alphas grow by 0x20 (below 0xB0) until the game step at 0xDD0 reaches 0x12;
   then phase 0 sets 0x1E = 3 and moves to phase 1, which fades both by 0x10 and stops */

typedef struct {
    u8 pad0[0xDD0];
    s16 step;
} Game_c034_01E00290;

typedef struct {
    u8 pad0[0x14];
    u8 col[4];
    u8 col2[4];
    s16 mode;
    s16 f1E;
    s16 phase;
} Fx_c034_01E00290;

static s32 func_01E00290_c034(Game_c034_01E00290 *g, Fx_c034_01E00290 *o) {
    if (g->step < 0x12) {
        if (o->col[3] < 0xB0) {
            o->col[3] += 0x20;
        }
        if (o->col2[3] < 0xB0) {
            o->col2[3] += 0x20;
        }
    } else if (o->phase == 0) {
        o->f1E = 3;
        o->phase = 1;
    } else if (o->phase == 1) {
        if (o->col[3] > 0x10) {
            o->col[3] -= 0x10;
        }
        if (o->col2[3] > 0x10) {
            o->col2[3] -= 0x10;
        } else {
            o->mode = 0;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/c034", func_01E00350_c034);

INCLUDE_ASM("asm/nonmatchings/mod/c034", func_01E00610_c034);

INCLUDE_ASM("asm/nonmatchings/mod/c034", func_01E00740_c034);

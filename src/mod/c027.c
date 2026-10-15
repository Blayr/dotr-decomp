#include "common.h"

INCLUDE_ASM("asm/nonmatchings/mod/c027", func_01E00080_c027);

/* shape c027:01E00290, 66 insns: 0x6A..0x6E = 360; while the game counter at 0x22D8 is below 6 both alphas fade by
   0x30 (the second ends it), otherwise both grow by 0x10 (below 0x80) and a full second alpha sets the game flag
   0x2368; after game step 0x235C passes 12 the game colour at 0x2372 dims by 10 (above 0x30), 0x2373 = 0 and 0x2374
   grows by 10 (below 0x50); the effect stops below counter 2 */

typedef struct {
    u8 pad0[0x22D8];
    s32 count;
    u8 pad22DC[0x80];
    s16 step;
    u8 pad235E[0xA];
    s16 flag;
    u8 pad236A[8];
    u8 c2372;
    u8 c2373;
    u8 c2374;
} Game_c027_01E00290;

typedef struct {
    u8 pad0[0x60];
    u8 col[4];
    u8 col2[4];
    s16 mode;
    s16 f6A;
    s16 f6C;
    s16 f6E;
} Fx_c027_01E00290;

static s32 func_01E00290_c027(Game_c027_01E00290 *g, Fx_c027_01E00290 *o) {
    o->f6A = 360;
    o->f6C = 360;
    o->f6E = 360;
    if (g->count < 6) {
        if (o->col[3] > 0x30) {
            o->col[3] -= 0x30;
        }
        if (o->col2[3] > 0x30) {
            o->col2[3] -= 0x30;
        } else {
            o->mode = 0;
        }
    } else {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x10;
        }
        if (o->col2[3] < 0x80) {
            o->col2[3] += 0x10;
        }
        if (o->col2[3] >= 0x80) {
            g->flag = 1;
        }
    }
    if (g->step > 0xC) {
        if (g->c2372 > 0x30) {
            g->c2372 -= 10;
        }
        g->c2373 = 0;
        if (g->c2374 < 0x50) {
            g->c2374 += 10;
        }
    }
    if (g->count < 2) {
        o->mode = 0;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/c027", func_01E003A0_c027);

INCLUDE_ASM("asm/nonmatchings/mod/c027", func_01E00660_c027);

INCLUDE_ASM("asm/nonmatchings/mod/c027", func_01E008B0_c027);

INCLUDE_ASM("asm/nonmatchings/mod/c027", func_01E00AA0_c027);

INCLUDE_ASM("asm/nonmatchings/mod/c027", func_01E00C50_c027);

INCLUDE_ASM("asm/nonmatchings/mod/c027", func_01E01930_c027);

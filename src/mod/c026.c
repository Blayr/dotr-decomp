#include "common.h"

INCLUDE_ASM("asm/nonmatchings/mod/c026", func_01E00080_c026);

/* shape c026:01E00B10, 54 insns: fades two alphas by the game timer: up 8 to 0x80 for 13 frames, then down 16 to 0x10
   while the phase is below 6, then up 8 to 0xB0; clears the flag below phase 2 */

typedef struct {
    u8 pad0[0x1A40];
    s32 phase;
    u8 pad1A44[0x80];
    s16 timer;
} Game_c026_01E00B10;

typedef struct {
    u8 pad0[0x64];
    u8 c0[4];
    u8 c1[4];
    s16 flag;
} Obj_c026_01E00B10;

static s32 func_01E00B10_c026(Game_c026_01E00B10 *g, Obj_c026_01E00B10 *o) {
    if (g->timer < 0xD) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 8;
        }
        if (o->c1[3] < 0x80) {
            o->c1[3] += 8;
        }
    } else if (g->phase < 6) {
        if (o->c0[3] > 0x10) {
            o->c0[3] -= 0x10;
        }
        if (o->c1[3] > 0x10) {
            o->c1[3] -= 0x10;
        }
    } else {
        if (o->c0[3] < 0xB0) {
            o->c0[3] += 8;
        }
        if (o->c1[3] < 0xB0) {
            o->c1[3] += 8;
        }
    }
    if (g->phase < 2) {
        o->flag = 0;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/c026", func_01E00BF0_c026);

INCLUDE_ASM("asm/nonmatchings/mod/c026", func_01E00F20_c026);

INCLUDE_ASM("asm/nonmatchings/mod/c026", func_01E01170_c026);

INCLUDE_ASM("asm/nonmatchings/mod/c026", func_01E01270_c026);

INCLUDE_ASM("asm/nonmatchings/mod/c026", func_01E014F0_c026);

INCLUDE_ASM("asm/nonmatchings/mod/c026", func_01E01860_c026);

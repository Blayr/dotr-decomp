#include "common.h"

INCLUDE_ASM("asm/nonmatchings/mod/c020", func_01E00080_c020);

INCLUDE_ASM("asm/nonmatchings/mod/c020", func_01E001C0_c020);

/* shape c020:01E00300, 48 insns: a rising wave: height 4 * sine of its angle (table at ctx+0x3250); the angle steps by 30 up to 180 while it grows; past 90 both levels drop by 28 down to 30, ending it */

typedef struct {
    u8 pad0[0x28];
    s16 h28;
    s16 h2A;
    s16 h2C;
    s16 ang;
    s16 h30;
    s16 h32;
    s16 h34;
} Wave_c020_01E00300;

static s32 func_01E00300_c020(u8 *ctx, Wave_c020_01E00300 *o) {
    extern f32 func_00108030(void *, s16, s32);

    o->h30 = 4.0f * func_00108030(ctx + 0x3250, o->ang, 0);
    if (o->ang < 180) {
        o->ang += 30;
        o->h34++;
        o->h32 += 2;
    }
    if (o->ang > 90) {
        if (o->h28 > 30) {
            o->h28 -= 28;
        }
        if (o->h2A > 30) {
            o->h2A -= 28;
        } else {
            o->h2C = 0;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/c020", func_01E003C0_c020);

INCLUDE_ASM("asm/nonmatchings/mod/c020", func_01E006F0_c020);

INCLUDE_ASM("asm/nonmatchings/mod/c020", func_01E00990_c020);

INCLUDE_ASM("asm/nonmatchings/mod/c020", func_01E00A80_c020);

INCLUDE_ASM("asm/nonmatchings/mod/c020", func_01E00E50_c020);

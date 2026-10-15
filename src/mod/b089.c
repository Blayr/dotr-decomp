#include "common.h"

/* shape b081:01E00080, 30 insns, 24 copies (s32 twin of b034:01E00080): shift a position history down by one, the newest from src */

static s32 func_01E00080_b089(Vec4f *dst, s32 n, s32 arg2, Vec4f *src) {
    s32 i;
    s32 k = n - 1;
    Vec4f *prev = dst;

    prev--;
    for (i = 0; i < n; i++, dst--, prev--, k--) {
        if (k != 0) {
            dst->x = prev->x;
            dst->y = prev->y;
            dst->z = prev->z;
        } else {
            dst->x = src->x;
            dst->y = src->y;
            dst->z = src->z;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b089", func_01E00100_b089);

INCLUDE_ASM("asm/nonmatchings/mod/b089", func_01E00470_b089);

INCLUDE_ASM("asm/nonmatchings/mod/b089", func_01E005A0_b089);

INCLUDE_ASM("asm/nonmatchings/mod/b089", func_01E006E0_b089);

INCLUDE_ASM("asm/nonmatchings/mod/b089", func_01E00890_b089);

INCLUDE_ASM("asm/nonmatchings/mod/b089", func_01E00A30_b089);

INCLUDE_ASM("asm/nonmatchings/mod/b089", func_01E013A0_b089);

INCLUDE_ASM("asm/nonmatchings/mod/b089", func_01E014C0_b089);

INCLUDE_ASM("asm/nonmatchings/mod/b089", func_01E016D0_b089);

INCLUDE_ASM("asm/nonmatchings/mod/b089", func_01E01BA0_b089);

INCLUDE_ASM("asm/nonmatchings/mod/b089", func_01E01D90_b089);

INCLUDE_ASM("asm/nonmatchings/mod/b089", func_01E01F50_b089);

INCLUDE_ASM("asm/nonmatchings/mod/b089", func_01E020E0_b089);

INCLUDE_ASM("asm/nonmatchings/mod/b089", func_01E022C0_b089);

INCLUDE_ASM("asm/nonmatchings/mod/b089", func_01E024F0_b089);

/* shape b089:01E026B0, 47 insns: constant variant of b205:01E01E50 (volume fade by game state): state at 0x26E0 limit 0x1F,
   floor 0x30, down 10, up 10, cap 0x80 */

typedef struct {
    u8 pad[0x26E0];
    s32 state;
} Game_b089_01E026B0;

typedef struct {
    u8 pad[0x30];
    s16 vol;
    u8 pad32[4];
    s16 mode;
} Fade_b089_01E026B0;

static s32 func_01E026B0_b089(Game_b089_01E026B0 *g, Fade_b089_01E026B0 *o) {
    extern void func_001F6D00(s32);

    if (o->mode == 1) {
        o->vol = 0x80;
        o->mode = 2;
    }
    if (g->state > 0x1E) {
        if (o->vol > 0x30) {
            o->vol -= 10;
        } else {
            o->vol = 0x30;
        }
    } else {
        if (o->vol < 0x80) {
            o->vol += 10;
        } else {
            o->vol = 0x80;
        }
    }
    if (g->state == 1) {
        func_001F6D00((u8)o->vol);
    } else {
        func_001F6D00((u8)o->vol);
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b089", func_01E02770_b089);

INCLUDE_ASM("asm/nonmatchings/mod/b089", func_01E030B0_b089);

INCLUDE_ASM("asm/nonmatchings/mod/b089", func_01E031D0_b089);

INCLUDE_ASM("asm/nonmatchings/mod/b089", func_01E032F0_b089);

INCLUDE_ASM("asm/nonmatchings/mod/b089", func_01E035E0_b089);

INCLUDE_ASM("asm/nonmatchings/mod/b089", func_01E03780_b089);

INCLUDE_ASM("asm/nonmatchings/mod/b089", func_01E03930_b089);

INCLUDE_ASM("asm/nonmatchings/mod/b089", func_01E03D60_b089);

INCLUDE_ASM("asm/nonmatchings/mod/b089", func_01E040E0_b089);

INCLUDE_ASM("asm/nonmatchings/mod/b089", func_01E04330_b089);

INCLUDE_ASM("asm/nonmatchings/mod/b089", func_01E045A0_b089);

INCLUDE_ASM("asm/nonmatchings/mod/b089", func_01E04770_b089);

INCLUDE_ASM("asm/nonmatchings/mod/b089", func_01E048E0_b089);

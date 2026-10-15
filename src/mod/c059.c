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

/* shape c059:01E053B0, 35 insns: raises two alphas by 16 up to 0x80 while the scene value is under 10, lowers them by 16 down to 16 while the other one is */

typedef struct {
    u8 pad0[0x2A50];
    s32 w2A50;
    u8 pad2A54[0x4E];
    s16 h2AA2;
} Ctx_c059_01E053B0;

typedef struct {
    u8 pad0[0x43];
    u8 a43;
    u8 pad44[3];
    u8 a47;
} Obj_c059_01E053B0;

static s32 func_01E053B0_c059(Ctx_c059_01E053B0 *ctx, Obj_c059_01E053B0 *o) {
    if (ctx->h2AA2 < 10) {
        if (o->a47 < 0x80) {
            o->a47 += 0x10;
        }
        if (o->a43 < 0x80) {
            o->a43 += 0x10;
        }
    }
    if (ctx->w2A50 < 10) {
        if (o->a47 > 0x10) {
            o->a47 -= 0x10;
        }
        if (o->a43 > 0x10) {
            o->a43 -= 0x10;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E05440_c059);

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E05710_c059);

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E05A70_c059);

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E05E40_c059);

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E05F90_c059);

/* shape c059:01E06280, 27 insns: second alpha 0; while the counter at 0x2A50 is below 10 fade by 0x15 and stop at
   the end, otherwise grow by 0x3C (below 0xF0); colour (0x20, 0, 0x40) */

typedef struct {
    u8 pad0[0x2A50];
    s32 count;
} Game_c059_01E06280;

typedef struct {
    u8 pad0[0x40];
    u8 col[4];
    u8 col2[4];
    s16 mode;
} Fx_c059_01E06280;

static s32 func_01E06280_c059(Game_c059_01E06280 *g, Fx_c059_01E06280 *o) {
    o->col2[3] = 0;
    if (g->count < 10) {
        if (o->col[3] > 0x20) {
            o->col[3] -= 0x15;
        } else {
            o->mode = 0;
        }
    } else {
        if (o->col[3] < 0xF0) {
            o->col[3] += 0x3C;
        }
    }
    o->col[0] = 0x20;
    o->col[1] = 0;
    o->col[2] = 0x40;
    return 0;
}

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

/* shape c059:01E063A0, 51 insns: a 10-tick counter (0x52); 0x4E swings by 2 between 0x14 and 0x3C (direction 0x56);
   while the game counter at 0x2A50 is below 10 the alpha fades by 0x10 and stops, otherwise grows by 9 below 0x80 */

typedef struct {
    u8 pad0[0x2A50];
    s32 count;
} Game_c059_01E063A0;

typedef struct {
    u8 pad0[0x40];
    u8 col[4];
    u8 pad44[4];
    s16 mode;
    u8 pad4A[4];
    s16 swing;
    u8 pad50[2];
    s16 f52;
    u8 pad54[2];
    s16 dir;
} Fx_c059_01E063A0;

static s32 func_01E063A0_c059(Game_c059_01E063A0 *g, Fx_c059_01E063A0 *o) {
    o->f52++;
    if (o->f52 >= 10) {
        o->f52 = 0;
    }
    if (o->dir == 0) {
        o->swing += 2;
        if (o->swing > 0x3C) {
            o->dir = 1;
        }
    } else {
        o->swing -= 2;
        if (o->swing < 0x14) {
            o->dir = 0;
        }
    }
    if (g->count < 10) {
        if (o->col[3] > 0x10) {
            o->col[3] -= 0x10;
        } else {
            o->mode = 0;
        }
    } else if (o->col[3] < 0x80) {
        o->col[3] += 9;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E06470_c059);

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E065D0_c059);

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E06720_c059);

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E06DC0_c059);

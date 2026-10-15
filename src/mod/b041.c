#include "common.h"

/* shape b034:01E00110, 276 insns, 11 copies: texture coordinates of a sprite quad from a rectangle, 4 explicit
   modes (corner orders differ from b008:01E00080's). Module-internal: callers include it with OVL_LOCAL static. */

typedef struct Rect_b034_01E00110 {
    s16 x, y, w, h;
} Rect_b034_01E00110;

typedef struct Uv_b034_01E00110 {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad4;
    u64 xyz;
} Uv_b034_01E00110;

typedef struct Pk_b034_01E00110 {
    u8 pad0[0x18];
    Uv_b034_01E00110 c[4];
} Pk_b034_01E00110;

static void func_01E00080_b041(Pk_b034_01E00110 *p, Rect_b034_01E00110 *r, s32 mode) {
    if (mode == 0) {
        p->c[0].u = (r->x) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[1].u = (r->x + r->w) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[2].u = (r->x) << 4;
        p->c[2].v = (r->y + r->h) << 4;
        p->c[3].u = (r->x + r->w) << 4;
        p->c[3].v = (r->y + r->h) << 4;
    } else if (mode == 1) {
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y) << 4;
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y + r->h) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y + r->h) << 4;
    } else if (mode == 2) {
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y + r->h) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y + r->h) << 4;
    } else if (mode == 3) {
        p->c[2].u = (r->x) << 4;
        p->c[2].v = (r->y) << 4;
        p->c[3].u = (r->x + r->w) << 4;
        p->c[3].v = (r->y) << 4;
        p->c[0].u = (r->x) << 4;
        p->c[0].v = (r->y + r->h) << 4;
        p->c[1].u = (r->x + r->w) << 4;
        p->c[1].v = (r->y + r->h) << 4;
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b041", func_01E004D0_b041);

INCLUDE_ASM("asm/nonmatchings/mod/b041", func_01E00740_b041);

INCLUDE_ASM("asm/nonmatchings/mod/b041", func_01E00CF0_b041);

INCLUDE_ASM("asm/nonmatchings/mod/b041", func_01E00FD0_b041);

INCLUDE_ASM("asm/nonmatchings/mod/b041", func_01E012A0_b041);

INCLUDE_ASM("asm/nonmatchings/mod/b041", func_01E01660_b041);

INCLUDE_ASM("asm/nonmatchings/mod/b041", func_01E01820_b041);

INCLUDE_ASM("asm/nonmatchings/mod/b041", func_01E01940_b041);

INCLUDE_ASM("asm/nonmatchings/mod/b041", func_01E01A70_b041);

INCLUDE_ASM("asm/nonmatchings/mod/b041", func_01E01C40_b041);

INCLUDE_ASM("asm/nonmatchings/mod/b041", func_01E01DF0_b041);

INCLUDE_ASM("asm/nonmatchings/mod/b041", func_01E01FC0_b041);

INCLUDE_ASM("asm/nonmatchings/mod/b041", func_01E020B0_b041);

INCLUDE_ASM("asm/nonmatchings/mod/b041", func_01E022D0_b041);

INCLUDE_ASM("asm/nonmatchings/mod/b041", func_01E02C00_b041);

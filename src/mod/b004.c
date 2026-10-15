#include "common.h"

INCLUDE_ASM("asm/nonmatchings/mod/b004", func_01E00080_b004);

/* shape b004:01E00460, 32 insns, 5 copies: step of a flash: first rises to alpha 0xF0 (then marks itself done rising),
   afterwards fades by 14 until it ends; keeps its colour at 0x9F/0x5F/0x5F */

typedef struct {
    u8 pad0[0x28];
    u8 c0[4];
    u8 pad2C[4];
    s16 up;
    u8 pad32[4];
    s16 state;
} Obj_b004_01E00460;

static s32 func_01E00460_b004(void *arg0, Obj_b004_01E00460 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->up == 0) {
        if (o->c0[3] < 0xF0) {
            o->c0[3] = 0xF0;
        } else {
            o->up = 1;
        }
    } else if (o->c0[3] > 15) {
        o->c0[3] -= 14;
    } else {
        o->state = 0;
    }
    func_001076F0(o->c0, 0x9F, 0x5F, 0x5F);
    return 0;
}

/* shape b004:01E004E0, 30 insns: colour from the module's table at 0x01E01F80; at game step 0x50 clear 0x36; below
   step 0x46 hold the countdown at 8, else count it down to 0 */

typedef struct {
    u8 r, g, b, a;
} Col_b004_01E004E0;

typedef struct {
    u8 pad0[0x34AC];
    s16 step;
} Game_b004_01E004E0;

typedef struct {
    u8 pad0[0x28];
    Col_b004_01E004E0 col;
    u8 pad2C[6];
    s16 count;
    u8 pad34[2];
    s16 f36;
} Fx_b004_01E004E0;

extern Col_b004_01E004E0 D_01E01F80_b004;

static s32 func_01E004E0_b004(Game_b004_01E004E0 *g, Fx_b004_01E004E0 *o) {
    o->col = D_01E01F80_b004;
    if (g->step == 0x50) {
        o->f36 = 0;
    }
    if (g->step < 0x46) {
        o->count = 8;
    } else if (o->count != 0) {
        o->count--;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b004", func_01E00560_b004);

/* shape b004:01E006B0, 56 insns: a pink rising ring: grows by 4 up to 10, rises 2 a frame from 15 and ends past 180;
   fades both alphas by 32 from height 80 */

typedef struct {
    u8 pad0[2];
    s16 y;
    u8 pad4[2];
    s16 size;
    u8 pad8[0x20];
    u8 c0[4];
    u8 c1[4];
    u8 pad30[6];
    s16 state;
} Obj_b004_01E006B0;

static s32 func_01E006B0_b004(void *arg0, Obj_b004_01E006B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->size < 0xA) {
        o->size += 4;
    }
    o->y += 2;
    func_001076F0(o->c0, 0xFF, 0xF0, 0xFF);
    if (o->y > 0xB4) {
        o->state = 0;
    }
    if (o->state == 1) {
        o->y = 0xF;
        o->size = 0;
        o->c0[3] = 0xC0;
        o->state = 2;
    }
    if (o->y >= 0x50) {
        if (o->c0[3] > 0x20) {
            o->c0[3] -= 0x20;
        } else {
            o->state = 0;
        }
        if (o->c1[3] > 0x20) {
            o->c1[3] -= 0x20;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b004", func_01E00790_b004);

INCLUDE_ASM("asm/nonmatchings/mod/b004", func_01E009F0_b004);

typedef struct {
    f32 x, y, z, w;
} Vec_b004_01E00B40;

static s32 func_01E00B40_b004(Vec_b004_01E00B40 *trail, s32 n, s32 arg2) {
    extern s32 func_001F53A0();
    s32 k;
    Vec_b004_01E00B40 *dst;
    Vec_b004_01E00B40 *src;
    Vec_b004_01E00B40 pos;
    s32 i;

    src = trail;
    k = n - 1;
    dst = trail;
    src--;
    func_001F5620(func_001F53A0(trail), arg2, (s32)&pos);
    for (i = 0; i < n; i++) {
        if (k != 0) {
            dst->x = src->x;
            dst->y = src->y;
            dst->z = src->z;
        } else {
            dst->x = pos.x;
            dst->y = pos.y;
            dst->z = pos.z;
        }
        dst--;
        src--;
        k--;
    }
    return 0;
}

/* shape b004:01E00C10, 9 insns: asks func_001F6160 for a pair of ints and returns the second as a float */

static f32 func_01E00C10_b004(s32 arg0) {
    extern void func_001F6160(s32, s32 *);
    s32 v[4];

    func_001F6160(arg0, v);
    return v[1];
}

INCLUDE_ASM("asm/nonmatchings/mod/b004", func_01E00C40_b004);

INCLUDE_ASM("asm/nonmatchings/mod/b004", func_01E012B0_b004);

INCLUDE_ASM("asm/nonmatchings/mod/b004", func_01E013F0_b004);

INCLUDE_ASM("asm/nonmatchings/mod/b004", func_01E01860_b004);

INCLUDE_ASM("asm/nonmatchings/mod/b004", func_01E01A00_b004);

INCLUDE_ASM("asm/nonmatchings/mod/b004", func_01E01DA0_b004);

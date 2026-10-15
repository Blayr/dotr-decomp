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

INCLUDE_ASM("asm/nonmatchings/mod/b004", func_01E004E0_b004);

INCLUDE_ASM("asm/nonmatchings/mod/b004", func_01E00560_b004);

INCLUDE_ASM("asm/nonmatchings/mod/b004", func_01E006B0_b004);

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

#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_048", func_001ED460);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001ED4A0);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001EDA40);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001EDCB0);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001EDF20);

void func_001EDF90(s32 arg0) {
    func_00209D30(func_001EDFD0(func_00209D20(), arg0));
}

INCLUDE_ASM("asm/nonmatchings/main_048", func_001EDFD0);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001EE4A0);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001EE4B0);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001EE570);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001EE6C0);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001EF8A0);

s32 func_001EFA80(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    s32 saved;

    saved = func_001F3210(arg1);
    func_001F3190(arg1, 0);
    arg0 = func_001EE4B0(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
    func_001F3190(arg1, saved);
    return arg0;
}

INCLUDE_ASM("asm/nonmatchings/main_048", func_001EFB40);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001EFBD0);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001EFD30);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001EFDC0);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001EFF70);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F0060);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F01A0);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F0390);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F0500);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F0760);

typedef struct {
    u8 pad00[4];
    s32 f4;
} Inner_001F0830;

typedef struct {
    u8 pad00[0x14];
    Inner_001F0830 *f14;
} Item_001F0830;

typedef struct {
    u8 pad00[0x14];
    Item_001F0830 *f14;
    u8 pad18[4];
    s32 f1C;
} Arg_001F0830;

typedef struct {
    u8 pad00[0x178];
    Item_001F0830 *slots[18];
    s32 vals[18];
} Base_001F0830;

void func_00214090(Item_001F0830 *);
extern Base_001F0830 *D_0031ABB0[];

void func_001F0830(void *arg0, s32 arg1) {
    Arg_001F0830 *a = (Arg_001F0830 *)arg0;
    s32 v;
    s32 idx;
    s32 sub;
    Base_001F0830 *base;

    v = a->f1C;
    idx = v >> 8;
    sub = v & 0xFF;
    if (idx < 0 || idx >= 0x54) {
        return;
    }
    base = D_0031ABB0[idx];
    if (base != NULL && arg1 != 0) {
        base->slots[sub] = a->f14;
        func_00214090(base->slots[sub]);
        base->vals[sub] = base->slots[sub]->f14->f4;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F08D0);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F0C10);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F0CD0);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F0E50);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F0F40);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F0FA0);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F0FF0);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F1070);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F1130);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F11B0);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F1240);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F12A0);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F1300);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F1370);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F13F0);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F1400);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F1480);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F1490);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F1550);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F1560);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F16B0);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F16C0);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F1830);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F1940);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F19A0);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F1A00);

#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_070", func_00245150);

INCLUDE_ASM("asm/nonmatchings/main_070", func_00245160);

typedef struct {
    u8 pad00[0x48];
    u8 unk48[0x60];
    s32 unkA8;
} Obj_002451A0;

typedef struct {
    f32 v;
} Flt_002451A0;

void func_002440F0(void *, s32 *, s32 *, s32 *, s32 *);
void func_002441F0(void *, s32);
void func_00244B20(void *);
s32 func_00245630(s32, s32, s32, s32, void *, s32, s32, s32);
extern Flt_002451A0 D_0029B300;
extern u8 D_003506C8[];

s32 func_002451A0(void *arg0) {
    Obj_002451A0 *p = (Obj_002451A0 *)arg0;
    s32 sp2C;
    s32 sp30;
    Flt_002451A0 sp34;
    s32 sp38;
    s32 sp3C;

    sp34 = D_0029B300;
    func_002440F0(p->unk48, &sp2C, &sp38, &sp30, &sp3C);
    if ((sp38 + sp3C) < 4) {
        return 0;
    }
    func_002441F0(D_003506C8, func_00245630((sp2C & 0xFFFFFFF) | 0x20000000, sp38, (sp30 & 0xFFFFFFF) | 0x20000000, sp3C, &sp34, 4, 0, 0));
    func_00244B20(p->unk48);
    if (p->unkA8 == 0) {
        p->unkA8 = 2;
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_070", func_00245280);

INCLUDE_ASM("asm/nonmatchings/main_070", func_002452E0);

INCLUDE_ASM("asm/nonmatchings/main_070", func_00245340);

s32 func_00245520(void *arg0, void *arg1) {
    func_00199B50(&D_0030F8E9, *(s32 *)((u8 *)arg1 + 4));
    return 1;
}

s32 func_00245550(void) {
    func_00242900();
    func_00244250(D_003506C8);
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_070", func_00245580);

INCLUDE_ASM("asm/nonmatchings/main_070", func_002455B0);

INCLUDE_ASM("asm/nonmatchings/main_070", func_002455E0);

INCLUDE_ASM("asm/nonmatchings/main_070", func_00245630);

INCLUDE_ASM("asm/nonmatchings/main_070", func_00245770);

void func_002457C0(void) {

}

INCLUDE_ASM("asm/nonmatchings/main_070", func_002457D0);

typedef struct {
    u8 pad[0xC];
    s32 field_C;
    s32 field_10;
} Fields_002457E0;

s32 func_002457E0(void *arg0) {
    return ((Fields_002457E0 *)arg0)->field_C == ((Fields_002457E0 *)arg0)->field_10;
}

INCLUDE_ASM("asm/nonmatchings/main_070", func_00245800);

INCLUDE_ASM("asm/nonmatchings/main_070", func_00245890);

INCLUDE_ASM("asm/nonmatchings/main_070", func_002458E0);

INCLUDE_ASM("asm/nonmatchings/main_070", func_00245960);

INCLUDE_ASM("asm/nonmatchings/main_070", func_00245980);

INCLUDE_ASM("asm/nonmatchings/main_070", func_002459D0);

INCLUDE_ASM("asm/nonmatchings/main_070", func_00245A30);

INCLUDE_ASM("asm/nonmatchings/main_070", func_00245AE0);

INCLUDE_ASM("asm/nonmatchings/main_070", func_00245BE0);

INCLUDE_ASM("asm/nonmatchings/main_070", func_00245D80);

INCLUDE_ASM("asm/nonmatchings/main_070", func_00245DB0);

INCLUDE_ASM("asm/nonmatchings/main_070", func_002460F0);

INCLUDE_ASM("asm/nonmatchings/main_070", func_00246340);

INCLUDE_ASM("asm/nonmatchings/main_070", func_00246450);

void func_00246490(void) {
    func_00209D30(func_00246340(func_00209D20()));
}

void func_002464C0(void) {
    if (D_00351170) {
        return;
    }
}

void func_002464E0(void) {

}

INCLUDE_ASM("asm/nonmatchings/main_070", func_002464F0);

INCLUDE_ASM("asm/nonmatchings/main_070", func_00246810);

INCLUDE_ASM("asm/nonmatchings/main_070", func_00247F40);

INCLUDE_ASM("asm/nonmatchings/main_070", func_00248370);

INCLUDE_ASM("asm/nonmatchings/main_070", func_00248460);

INCLUDE_ASM("asm/nonmatchings/main_070", func_002487A0);

INCLUDE_ASM("asm/nonmatchings/main_070", func_00248AF0);

INCLUDE_ASM("asm/nonmatchings/main_070", func_00248E30);

INCLUDE_ASM("asm/nonmatchings/main_070", func_00248EA0);

INCLUDE_ASM("asm/nonmatchings/main_070", func_00248F60);

INCLUDE_ASM("asm/nonmatchings/main_070", func_00248FD0);

INCLUDE_ASM("asm/nonmatchings/main_070", func_00249040);

INCLUDE_ASM("asm/nonmatchings/main_070", func_00249200);

INCLUDE_ASM("asm/nonmatchings/main_070", func_002492F0);

INCLUDE_ASM("asm/nonmatchings/main_070", func_00249320);

INCLUDE_ASM("asm/nonmatchings/main_070", func_002493A0);

INCLUDE_ASM("asm/nonmatchings/main_070", func_00249410);

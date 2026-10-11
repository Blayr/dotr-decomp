#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_070", func_00245150);

typedef struct Values_00245160 {
    s64 first;
    s64 second;
    s32 offset;
    s32 fourth;
} Values_00245160;

extern u8 D_003506C8[];
void func_00244CB0(u8 *, void *);

void func_00245160(void *arg0, s64 arg1, s64 arg2, s32 arg3, s32 arg4) {
    Values_00245160 values;

    values.first = arg1;
    values.second = arg2;
    values.offset = arg3 - *(s32 *)((u8 *)arg0 + 0x48);
    values.fourth = arg4;
    func_00244CB0(D_003506C8, &values);
}

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

s32 func_00245280(void *arg0) {
    s32 result;

    result = 0;
    if (func_00244AD0((u8 *)arg0 + 0x48) == 0) {
        if (func_0018EE68(arg0) != 0) {
            result = 1;
        }
    }
    return result;
}

void func_002452E0(void *arg0) {
    func_00243F60((u8 *)arg0 + 0x48);
    func_002457D0(D_00350600);
    func_00245340(arg0);
    do {

    } while (D_0035060C != 0);
    *(s32 *)((u8 *)arg0 + 0xA8) = 3;
}

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

s32 func_00245580(void) {
    func_00244530(D_003506C8);
    return 1;
}

s32 func_002455B0(void) {
    func_00244680(D_003506C8);
    return 1;
}

typedef struct Entry_002455E0 {
    s64 values[2];
    s32 offset;
    s32 size;
} Entry_002455E0;

s32 func_00244DE0(u8 *, void *);

s32 func_002455E0(s32 arg0, void *arg1) {
    Entry_002455E0 entry;

    func_00244DE0(D_003506C8, &entry);
    *(s64 *)((u8 *)arg1 + 8) = entry.values[0];
    *(s64 *)((u8 *)arg1 + 0x10) = entry.values[1];
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_070", func_00245630);

typedef struct State_00245770 {
    s32 value;
    u8 *entries;
    s32 field8;
    s32 fieldC;
    s32 count;
} State_00245770;

void func_00245770(void *arg0, s32 arg1, void *arg2, s32 arg3) {
    State_00245770 *state = arg0;
    s32 *temp_a2;
    s32 var_t0;

    state->value = arg1;
    state->entries = arg2;
    state->count = arg3;
    state->fieldC = 0;
    state->field8 = 0;
    for (var_t0 = 0; var_t0 < arg3; var_t0++) {
        temp_a2 = (s32 *)(state->entries + var_t0 * 0x4CE40);
        *temp_a2 = 0;
    }
}

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

typedef struct Quad_00245980 {
    s16 x;
    s16 y;
    s16 z;
    s16 w;
} Quad_00245980;

extern Quad_00245980 **D_0029D488[];

void func_00245980(s32 arg0, s32 arg1, void *arg2) {
    *(Quad_00245980 *)arg2 = (*D_0029D488[(u8)arg0])[(u8)arg1];
}

INCLUDE_ASM("asm/nonmatchings/main_070", func_002459D0);

INCLUDE_ASM("asm/nonmatchings/main_070", func_00245A30);

INCLUDE_ASM("asm/nonmatchings/main_070", func_00245AE0);

INCLUDE_ASM("asm/nonmatchings/main_070", func_00245BE0);

typedef struct {
    s32 value;
    u8 padding[0x30];
} Entry_00245D80;

extern Entry_00245D80 D_00350FD0[];

void func_00245D80(u8 *arg0) {
    D_00350FD0[*arg0].value = 0;
}

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

s32 func_00248E30(s32 arg0, s32 arg1) {
    s32 var_v0;

    if (arg0 < 2) {
        var_v0 = func_001DF470((arg0 == 0) ? 1 : 0) >> 1;
    } else {
        var_v0 = func_001DF470((func_001DE540() == 0) ? 1 : 0) >> 1;
    }
    var_v0 = func_002670F0(0x2C, var_v0);
    var_v0 += arg1;
    return var_v0;
}

INCLUDE_ASM("asm/nonmatchings/main_070", func_00248EA0);

s32 func_00248F60(s32 arg0, s32 arg1) {
    s32 temp_a2;

    temp_a2 = arg1 - 0x2F0;
    if ((D_0029D580[arg0 * 7 + (temp_a2 >> 3)] >> (temp_a2 % 8)) & 1) {
        return func_00249040(arg0, arg1);
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/main_070", func_00248FD0);

INCLUDE_ASM("asm/nonmatchings/main_070", func_00249040);

INCLUDE_ASM("asm/nonmatchings/main_070", func_00249200);

s32 func_002492F0(s32 arg0) {
    return ((s32) D_0029D586[arg0 * 7] >> 1) & 1;
}

s32 func_00249320(s32 arg0) {
    u8 temp_v1;

    temp_v1 = D_0029D1F0[arg0];
    switch (temp_v1) {
    case 2:
    case 3:
        return -1;
    case 4:
        if (D_0029CF32[arg0] == 9) {
            return -1;
        }
    default:
        return 1;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_070", func_002493A0);

INCLUDE_ASM("asm/nonmatchings/main_070", func_00249410);

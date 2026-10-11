#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_055", func_00202220);

INCLUDE_ASM("asm/nonmatchings/main_055", func_002024D0);

INCLUDE_ASM("asm/nonmatchings/main_055", func_00202810);

INCLUDE_ASM("asm/nonmatchings/main_055", func_002029B0);

s32 func_00202AB0(s32 arg0, s32 arg1) {
    s32 sp3C;

    func_00209D30(func_00202B00(func_00209D20(), arg0, arg1, &sp3C));
    return sp3C;
}

INCLUDE_ASM("asm/nonmatchings/main_055", func_00202B00);

INCLUDE_ASM("asm/nonmatchings/main_055", func_00202BF0);

INCLUDE_ASM("asm/nonmatchings/main_055", func_00202CB0);

typedef struct {
    s32 data;
    s32 unknown;
    s16 active : 1;
    s16 flags : 2;
    s16 category : 13;
    s16 id;
} Entry_00202D60;

extern Entry_00202D60 D_003229A0[];

s32 func_00202D60(s32 arg0, s32 arg1) {
    Entry_00202D60 *var_t0;
    s32 var_t1;
    s32 var_v0;

    var_t0 = D_003229A0;
    var_v0 = 0;
    var_t1 = 0;
    do {
        if (var_t0->data != 0 && var_t0->active != 0) {
            if ((arg0 < 0 || var_t0->category == arg0) &&
                (arg1 < 0 || var_t0->id == arg1)) {
                var_v0 = 1;
                var_t0->active = 0;
            }
        }
        var_t1 += 1;
        var_t0++;
    } while (var_t1 < 0x400);
    return var_v0;
}

u16 func_00202E00(s16 arg0, s32 arg1) {
    D_00322990 = arg0;
    D_00322992 = (u16) ((s32) ((s32) (arg1 << 0xD) >> 6) >> 2);
    D_00322994 = 0;
    return D_00322992;
}

INCLUDE_ASM("asm/nonmatchings/main_055", func_00202E30);

typedef struct {
    u16 base;
    u16 capacity;
    u16 used;
} Buffer_00202F00;

s32 func_00202F00(s32 arg0) {
    s32 temp_v0;
    Buffer_00202F00 *buffer = (Buffer_00202F00 *)&D_00322990;

    if (((u16) D_00322994 + arg0) > (s32) D_00322992) {
        return -1;
    }
    temp_v0 = buffer->base + buffer->used;
    buffer->used += arg0;
    return temp_v0;
}

void func_00202F50(s32 arg0, s32 arg1, s32 arg2) {
    func_00209D30(func_00202FB0(func_00209D20(), arg0, arg1, arg2));
}

INCLUDE_ASM("asm/nonmatchings/main_055", func_00202FB0);

INCLUDE_ASM("asm/nonmatchings/main_055", func_002031F0);

void func_002032A0(void) {
    func_0020B400(D_003259C0, 0, 0xB0);
}

extern s8 D_00325C19[];

typedef struct {
    u8 pad[0x25A];
    s8 low : 4;
    s8 high : 4;
} Flags_002032C0;

void func_002032C0(s32 arg0, s8 arg1, s64 arg2) {
    s32 offset;
    Flags_002032C0 *entry;

    offset = arg0 * 0x5C;
    D_00325C19[offset] = arg1;
    entry = (Flags_002032C0 *)(D_003259C0 + offset);
    entry->low = arg2;
}

INCLUDE_ASM("asm/nonmatchings/main_055", func_00203320);

INCLUDE_ASM("asm/nonmatchings/main_055", func_00203840);

INCLUDE_ASM("asm/nonmatchings/main_055", func_002038F0);

INCLUDE_ASM("asm/nonmatchings/main_055", func_00203A40);

s32 func_00203B50(s32 arg0, s32 arg1) {
    u8 *temp_a0;
    s32 var_a1;
    u8 *var_a2;

    temp_a0 = D_003259C0 + (arg0 * 0x5C) + 0x200;
    var_a1 = 0;
    var_a2 = temp_a0;
    do {
        if (arg1 & 0xFFFF & (1 << var_a1)) {
            *(s32 *)(var_a2 + 0x18) = -*(s8 *)(temp_a0 + 0x59);
        }
        var_a1 += 1;
        var_a2 += 4;
    } while (var_a1 < 0x10);
    return 0;
}

typedef struct {
    u8 padding[0x25B];
    s8 unused : 6;
    s8 flag : 1;
    s8 unused_high : 1;
} Flags_00203BC0;

extern u8 D_003259C0[];

s32 func_00203BC0(s32 arg0) {
    return ((Flags_00203BC0 *)(D_003259C0 + arg0 * 0x5C))->flag ? 1 : 0;
}

typedef struct {
    u8 padding[0x25B];
    s8 : 7;
    s8 flag : 1;
} Flags_00203C00;

s32 func_00203C00(s32 arg0) {
    Flags_00203C00 *flags = (Flags_00203C00 *)(D_003259C0 + arg0 * 0x5C);

    return flags->flag ? 1 : 0;
}

typedef struct Entry_00203C40 {
    u8 pad[0x206];
    u8 value;
} Entry_00203C40;

u8 func_00203C40(s32 arg0, s32 arg1) {
    return ((Entry_00203C40 *)(D_003259C0 + arg0 * 0x5C + arg1))->value;
}

void func_00203C70(s32 arg0, s32 arg1, s8 arg2) {
    *(s8 *)(D_003259C0 + arg0 * 0x5C + arg1 + 0x206) = arg2;
}

typedef struct {
    u8 pad[0x20A];
    u8 value;
} Entry_00203CA0;

u8 func_00203CA0(s32 arg0, s32 arg1) {
    return ((Entry_00203CA0 *)(arg1 + (D_003259C0 + arg0 * 0x5C)))->value;
}

INCLUDE_ASM("asm/nonmatchings/main_055", func_00203CD0);

INCLUDE_ASM("asm/nonmatchings/main_055", func_00203E20);

INCLUDE_ASM("asm/nonmatchings/main_055", func_002047F0);

INCLUDE_ASM("asm/nonmatchings/main_055", func_00205150);

INCLUDE_ASM("asm/nonmatchings/main_055", func_00205160);

INCLUDE_ASM("asm/nonmatchings/main_055", func_00205170);

INCLUDE_ASM("asm/nonmatchings/main_055", func_002051C0);

typedef struct {
    s8 : 2;
    s8 flag : 1;
} Flags_002051F0;

extern Flags_002051F0 D_00325CAC;

s32 func_002051F0(void) {
    return D_00325CAC.flag ? 1 : 0;
}

INCLUDE_ASM("asm/nonmatchings/main_055", func_00205210);

INCLUDE_ASM("asm/nonmatchings/main_055", func_00205440);

INCLUDE_ASM("asm/nonmatchings/main_055", func_00205630);

INCLUDE_ASM("asm/nonmatchings/main_055", func_002058D0);

f32 func_00205C40(s32 arg0) {
    f32 *temp_s0;

    temp_s0 = func_001FAF60(0);
    func_001FAFB0(0, arg0);
    return *temp_s0;
}

INCLUDE_ASM("asm/nonmatchings/main_055", func_00205C90);

INCLUDE_ASM("asm/nonmatchings/main_055", func_00205CA0);

void func_00205CB0(void *arg0, f32 fparg0, f32 fparg1) {
    f32 matrix[4][4];
    f32 *vector = arg0;

    vector[0] = fparg0;
    vector[1] = fparg1;
    vector[2] = func_001F9A20(0);
    vector[3] = 1.0f;
    func_0020EBA0(matrix);
    func_0020BDE0(matrix, matrix);
    func_0020CDD0(vector, matrix, vector);
}

INCLUDE_ASM("asm/nonmatchings/main_055", func_00205D10);

f32 func_00205DF0(void *arg0, f32 fparg0) {
    f32 vector[4];
    f32 matrix1[4][4];
    f32 matrix2[4][4];

    func_0020EBA0(matrix1);
    func_0020EC00(matrix2);
    ((f32 *)arg0)[3] = 1.0f;
    func_0020CDD0(vector, matrix1, arg0);
    vector[2] -= fparg0;
    func_0020CDD0(vector, matrix2, vector);
    return vector[3];
}

INCLUDE_ASM("asm/nonmatchings/main_055", func_00205E70);

INCLUDE_ASM("asm/nonmatchings/main_055", func_00206030);

INCLUDE_ASM("asm/nonmatchings/main_055", func_002060F0);

INCLUDE_ASM("asm/nonmatchings/main_055", func_002061F0);

INCLUDE_ASM("asm/nonmatchings/main_055", func_002062F0);

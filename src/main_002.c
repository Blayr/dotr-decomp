#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_002", func_00106DE0);

INCLUDE_ASM("asm/nonmatchings/main_002", func_00106E40);

void func_00106E90(void *arg0, void *arg1) {
    f32 *dst = arg0;
    f32 *src = arg1;

    dst[0] *= src[0];
    dst[1] *= src[1];
    dst[2] *= src[2];
}

INCLUDE_ASM("asm/nonmatchings/main_002", func_00106ED0);

INCLUDE_ASM("asm/nonmatchings/main_002", func_00106FA0);

INCLUDE_ASM("asm/nonmatchings/main_002", func_00107070);

s32 func_00107130(void *arg0, void *arg1, s32 arg2) {
    if (arg2 == 0) {
        ((f32 *)arg0)[0] = ((f32 *)arg1)[0];
        ((f32 *)arg0)[1] = ((f32 *)arg1)[1];
        ((f32 *)arg0)[2] = ((f32 *)arg1)[2];
    } else {
        ((f32 *)arg1)[0] = ((f32 *)arg0)[0];
        ((f32 *)arg1)[1] = ((f32 *)arg0)[1];
        ((f32 *)arg1)[2] = ((f32 *)arg0)[2];
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_002", func_00107180);

INCLUDE_ASM("asm/nonmatchings/main_002", func_00107280);

s32 func_00107310(s32 arg0, s32 arg1, s32 arg2) {
    f32 scale[3];

    if ((func_001F5EC0(arg0) != 0) && (arg2 != 0)) {
        scale[0] = 1.0f;
        scale[1] = 1.0f;
        scale[2] = 1.0f;
        func_001F62B0(arg0, scale);
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_002", func_00107370);

INCLUDE_ASM("asm/nonmatchings/main_002", func_00107450);

INCLUDE_ASM("asm/nonmatchings/main_002", func_00107510);

INCLUDE_ASM("asm/nonmatchings/main_002", func_00107650);

s32 func_001076F0(void *arg0, s8 arg1, s8 arg2, s8 arg3) {
    ((s8 *)arg0)[0] = arg1;
    ((s8 *)arg0)[1] = arg2;
    ((s8 *)arg0)[2] = arg3;
    return 0;
}

s32 func_00107710(u8 *arg0, u8 *arg1) {
    arg0[0] = arg1[0];
    arg0[1] = arg1[1];
    arg0[2] = arg1[2];
    arg0[3] = arg1[3];
    return 0;
}

typedef struct {
    f32 x;
    f32 y;
} FloatPair_00107740;

typedef union {
    struct {
        u8 bytes[4];
        f32 value;
    } packed;
    FloatPair_00107740 pair;
} PackedPair_00107740;

void func_00107740(void *arg0, void *arg1) {
    PackedPair_00107740 temp;
    u8 *src = arg1;

    temp.packed.bytes[0] = src[0];
    temp.packed.bytes[1] = src[1];
    temp.packed.bytes[2] = src[2];
    temp.packed.bytes[3] = src[3];
    temp.packed.value = 1.0f;
    *(FloatPair_00107740 *)arg0 = temp.pair;
}

INCLUDE_ASM("asm/nonmatchings/main_002", func_00107790);

INCLUDE_ASM("asm/nonmatchings/main_002", func_00107990);

INCLUDE_ASM("asm/nonmatchings/main_002", func_00107B90);

INCLUDE_ASM("asm/nonmatchings/main_002", func_00107C10);

INCLUDE_ASM("asm/nonmatchings/main_002", func_00107CB0);

INCLUDE_ASM("asm/nonmatchings/main_002", func_00107DD0);

INCLUDE_ASM("asm/nonmatchings/main_002", func_00107E40);

s32 func_00107EA0(void *arg0, f32 fparg0, f32 fparg1, f32 fparg2) {
    *(f32 *)((u8 *)arg0 + 0x449C) = fparg0;
    *(f32 *)((u8 *)arg0 + 0x44A0) = fparg1;
    *(f32 *)((u8 *)arg0 + 0x44A4) = fparg2;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_002", func_00107EC0);

INCLUDE_ASM("asm/nonmatchings/main_002", func_00108030);

INCLUDE_ASM("asm/nonmatchings/main_002", func_001082B0);

INCLUDE_ASM("asm/nonmatchings/main_002", func_00108500);

INCLUDE_ASM("asm/nonmatchings/main_002", func_00108950);

INCLUDE_ASM("asm/nonmatchings/main_002", func_00108BE0);

typedef struct Vec4_00108CE0 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4_00108CE0;

s32 func_00108CE0(void *arg0, f32 fparg0, f32 fparg1) {
    Vec4_00108CE0 *vertices = arg0;
    f32 negative_x;
    f32 negative_y;

    negative_x = -fparg0;
    vertices[0].x = negative_x;
    vertices[0].y = fparg1;
    vertices[0].z = 0.0f;
    vertices[1].x = fparg0;
    vertices[1].y = fparg1;
    vertices[1].z = 0.0f;
    vertices[2].x = negative_x;
    negative_y = -fparg1;
    vertices[2].y = negative_y;
    vertices[2].z = 0.0f;
    vertices[3].x = fparg0;
    vertices[3].y = negative_y;
    vertices[3].z = 0.0f;
    return 0;
}

s32 func_00108D20(void *dst, f32 x, f32 z) {
    f32 (*vertices)[4] = dst;

    vertices[0][0] = -x;
    vertices[0][1] = 0.0f;
    vertices[0][2] = z;
    vertices[1][0] = x;
    vertices[1][1] = 0.0f;
    vertices[1][2] = z;
    vertices[2][0] = -x;
    vertices[2][1] = 0.0f;
    vertices[2][2] = -z;
    vertices[3][0] = x;
    vertices[3][1] = 0.0f;
    vertices[3][2] = -z;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_002", func_00108D60);

INCLUDE_ASM("asm/nonmatchings/main_002", func_00108EF0);

s32 func_00108F90(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    f32 result[4];

    if (func_00205630(arg0, 0x70000000, arg2, arg1, result) != 0) {
        func_002075F0(arg1, arg3, func_001A23B0(result[0]));
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_002", func_00108FF0);

INCLUDE_ASM("asm/nonmatchings/main_002", func_00109050);

INCLUDE_ASM("asm/nonmatchings/main_002", func_00109100);

INCLUDE_ASM("asm/nonmatchings/main_002", func_001091B0);

INCLUDE_ASM("asm/nonmatchings/main_002", func_00109270);

INCLUDE_ASM("asm/nonmatchings/main_002", func_001092E0);

INCLUDE_ASM("asm/nonmatchings/main_002", func_00109380);

INCLUDE_ASM("asm/nonmatchings/main_002", func_001094F0);

INCLUDE_ASM("asm/nonmatchings/main_002", func_001095D0);

INCLUDE_ASM("asm/nonmatchings/main_002", func_00109830);

INCLUDE_ASM("asm/nonmatchings/main_002", func_001098E0);

INCLUDE_ASM("asm/nonmatchings/main_002", func_001099E0);

s32 func_00109A70(void *arg0, void *arg1) {
    ((f32 *)arg0)[0] = ((f32 *)arg1)[0];
    ((f32 *)arg0)[1] = ((f32 *)arg1)[1];
    ((f32 *)arg0)[2] = ((f32 *)arg1)[2];
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_002", func_00109A90);

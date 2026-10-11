#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_078", func_00276120);

INCLUDE_ASM("asm/nonmatchings/main_078", func_002761D0);

INCLUDE_ASM("asm/nonmatchings/main_078", func_00276290);

INCLUDE_ASM("asm/nonmatchings/main_078", func_00276B60);

s32 func_00276C80(u16 *arg0, s32 arg1) {
    s32 i = 0;

    do {
        if (arg1 == *arg0) {
            return i;
        }
        i++;
        arg0 += 8;
    } while (i < 0x16);
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/main_078", func_00276CC0);

typedef struct {
    u16 field_0;
    u8 field_2;
    u8 pad_3;
    s16 field_4;
    u8 pad_6[10];
    u8 field_10;
} Data_00276EC0;

void func_00276EC0(u16 *arg0, s32 arg1, void *arg2) {
    Data_00276EC0 *dest = arg2;
    u16 temp_v0;

    dest->field_0 = *arg0;
    dest->field_2 = 6;
    temp_v0 = *arg0;
    dest->field_4 = func_001E1090((s32) temp_v0 >> 8, temp_v0 & 0xFF);
    dest->field_10 = 2;
}

INCLUDE_ASM("asm/nonmatchings/main_078", func_00276F10);

void func_002777F0(s32, s32, s32, s32, s32, s32, s32, s32,
                   s64, s64, s64, s64, s64, s64, s64);

void func_002770E0(s32 arg0, s32 arg1, s32 arg2, s32 arg3,
                   s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                   s32 arg8, s32 arg9, s32 arg10, s32 arg11, s32 arg12) {
    func_002777F0(arg0, 0, arg1, arg2, arg3, arg4, arg5, arg6,
                   (u16) arg7, 0, (s64) arg10, (s64) arg11,
                   (s64) arg8, (s64) arg9, (s64) arg12);
}

INCLUDE_ASM("asm/nonmatchings/main_078", func_00277160);

INCLUDE_ASM("asm/nonmatchings/main_078", func_002774F0);

INCLUDE_ASM("asm/nonmatchings/main_078", func_002777F0);

typedef struct Entry_00277C60 {
    u16 key;
    u8 value;
    u8 pad;
} Entry_00277C60;

s32 func_00277C60(void *arg0, s32 arg1, s32 arg2) {
    s32 i;
    s32 result;
    Entry_00277C60 *entry;
    u16 key;
    u8 *value;

    i = 0;
    result = 0;
    do {
        entry = &((Entry_00277C60 *)arg0)[i];
        key = entry->key;
        if (arg1 == key) {
            value = &entry->value;
            if (arg2 < *value) {
                *value = arg2;
            }
            result = 1;
        } else if (key == 0xFFFF) {
            i = 0x16;
        }
        i++;
    } while (i < 0x16);
    return result;
}

INCLUDE_ASM("asm/nonmatchings/main_078", func_00277CD0);

s32 func_00278150(s32 arg0, s32 arg1) {
    switch (arg1) {
    case 0:
        if (arg0 == 0) {
            return 1;
        }
        break;
    case 1:
        if (arg0 == 1) {
            return 1;
        }
        break;
    case 2:
    default:
        return 1;
    }
    return 0;
}

s32 func_002781B0(s32 arg0, s32 arg1, s32 arg2) {
    if (arg2 != 0) {
        return 1;
    }
    if (func_001E2100(arg0, arg1, 2) == 1) {
        return 1;
    }
    return 0;
}

s32 func_002781F0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return func_00278250(func_001DF540(arg0 >> 8, arg0 & 0xFF), arg1, arg2, arg3);
}

INCLUDE_ASM("asm/nonmatchings/main_078", func_00278250);

INCLUDE_ASM("asm/nonmatchings/main_078", func_00278420);

INCLUDE_ASM("asm/nonmatchings/main_078", func_00278510);

INCLUDE_ASM("asm/nonmatchings/main_078", func_002785D0);

INCLUDE_ASM("asm/nonmatchings/main_078", func_002787F0);

void func_00278890(s32 arg0, s32 arg1) {
    if (arg1 == 1) {
        func_001E01F0(arg0);
        return;
    }
    func_001E0150(arg0);
}

typedef struct {
    u8 b[0x18];
} Ent_002788D0;

void *func_002788D0(u16 *arg0, u16 *arg1) {
    u16 idx;

    if ((s64)(u32)(*arg0 + 0x38) > 0x10000) {
        return 0;
    }
    idx = *arg1;
    *arg1 = idx + 1;
    *arg0 += 0x18;
    return &((Ent_002788D0 *)0x01ED0000)[idx];
}

INCLUDE_ASM("asm/nonmatchings/main_078", func_00278930);

s32 func_002789F0(s32 arg0, s32 arg1) {
    s32 temp_v0;
    s32 temp_s1;
    s32 temp_s2;

    temp_s2 = arg0 & 0xFFFF;
    if ((temp_s2 == 0x3E7) || (temp_s1 = arg1 & 0xFFFF, (temp_s1 == 0x3E7))) {
        return 0x3E7;
    }
    temp_v0 = func_00248F60(temp_s2, temp_s1);
    if ((temp_v0 >> 0x10) == 0) {
        if (func_00249320(temp_s1) == 1) {
            return temp_v0 & 0xFFFF;
        }
    }
    return func_002495A0(temp_s2, temp_s1) & 0xFFFF;
}

INCLUDE_ASM("asm/nonmatchings/main_078", func_00278A90);

void *func_00278C80(s32 arg0, s32 arg1, s32 arg2, s32 arg3,
                    s32 arg4, u16 *arg5, u16 *arg6) {
    s32 sp60[8];
    void *temp_v0;

    func_0026FD30(arg0, sp60);
    if (arg4 != 0) {
        return NULL;
    }
    if ((temp_v0 = func_002788D0(arg5, arg6)) == NULL) {
        return NULL;
    }
    func_00278930(temp_v0, arg3 & 0xFFFF, arg4, arg2);
    return temp_v0;
}

void func_00278D20(u8 *arg0, u8 arg1) {
    s32 var_a0;
    u8 *temp_a1;
    u8 temp_v1;

    if ((func_00278D90(arg0) & 0xFF) != 5) {
        var_a0 = 3;
        do {
            temp_a1 = &arg0[var_a0];
            temp_v1 = temp_a1[0];
            var_a0 -= 1;
            temp_a1[1] = temp_v1;
        } while (var_a0 >= 0);
        *arg0 = arg1;
    }
}

s32 func_00278D90(u8 *arg0) {
    s32 index;
    s32 count;

    index = 0;
    count = 0;
    do {
        if (arg0[index] == 0xFF) {
            return count;
        }
        index++;
        count++;
    } while (index < 5);
    return count;
}

void func_00278DD0(u8 *src, u8 *dst) {
    s32 i;

    i = 0;
    do {
        dst[i] = src[i];
        i++;
    } while (i < 5);
}

s32 func_00278E00(u8 value, u8 *values) {
    s32 i;

    i = 0;
    do {
        if (value == values[i]) {
            return 1;
        }
        i++;
    } while (i < 5);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_078", func_00278E40);

INCLUDE_ASM("asm/nonmatchings/main_078", func_00278F10);

s32 func_00279130(s32 arg0, u16 *arg1) {
    u32 temp_s0;

    temp_s0 = func_0026FBB0(*arg1) >> 0x10;
    return (temp_s0 << 0x10) | (func_0026FBB0(*arg1) & 0xFFFF);
}

INCLUDE_ASM("asm/nonmatchings/main_078", func_00279170);

void func_00279230(s32 arg0, s32 arg1, s32 arg2, s32 arg3,
                   s32 arg4, s32 arg5, s32 arg6, s32 arg7, u8 arg8) {
    func_002792C0(func_001DF540(arg0, arg1), arg2, arg3, arg4,
                  arg5, arg6, arg7, arg8);
}

INCLUDE_ASM("asm/nonmatchings/main_078", func_002792C0);

INCLUDE_ASM("asm/nonmatchings/main_078", func_002794E0);

void func_00279850(s32 arg0, s32 arg1, s32 arg2, s32 arg3,
                   s32 arg4, s32 arg5, s32 arg6) {
    func_002798C0(func_001DF540(arg0, arg1), arg2, arg3, arg4, arg5, arg6);
}

INCLUDE_ASM("asm/nonmatchings/main_078", func_002798C0);

void func_00279C40(s32 arg0, s32 arg1, s32 arg2, s32 arg3,
                   s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    func_00279CC0(func_001DF540(arg0, arg1), arg2, arg3,
                  arg4, arg5, arg6, arg7);
}

INCLUDE_ASM("asm/nonmatchings/main_078", func_00279CC0);

void func_0027A090(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4,
                   s32 arg5, s32 arg6, s32 arg7, s32 arg8, u8 arg9, u16 arg10) {
    func_0027A130(func_001DF540(arg0, arg1), arg2, arg3, arg4, arg5,
                  arg6, arg7, arg8, arg9, arg10);
}

INCLUDE_ASM("asm/nonmatchings/main_078", func_0027A130);

INCLUDE_ASM("asm/nonmatchings/main_078", func_0027A360);

INCLUDE_ASM("asm/nonmatchings/main_078", func_0027A710);

s32 func_0027ABD0(void *arg0, u8 arg1, u8 arg2) {
    s32 i;
    void **children;
    s32 nextDepth;
    s32 result;

    if (arg0 != NULL) {
        if (arg1 == arg2) {
            return 1;
        }
        nextDepth = arg1 + 1;
        children = arg0;
        i = 0;
        do {
            result = func_0027ABD0(children[1], nextDepth, arg2);
            if (result == 1) {
                return result;
            }
            i++;
            children++;
        } while (i < 12);
    }
    return 0;
}

void func_0027AC70(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp18;
    u8 sp1F;

    sp1F = 0xFF;
    sp18 = 0;
    func_0027ACB0(arg0, &sp18, &sp1F, arg1, arg2, arg3, arg0, 0);
}

INCLUDE_ASM("asm/nonmatchings/main_078", func_0027ACB0);

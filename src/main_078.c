#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_078", func_00276120);

typedef struct {
    u16 id;
    s16 field_02;
    u16 field_04;
    u16 field_06;
    s32 field_08;
    u8 state : 2;
    u8 flags : 6;
    u8 padding[3];
} Entry_002761D0;

void func_002761D0(void *arg0) {
    s32 i;
    s32 j;
    Entry_002761D0 *dst;
    Entry_002761D0 *src;

    i = 0;
    dst = arg0;
    do {
        if (dst->id == 0xFFFF) {
            for (j = i + 1; j < 22; j++) {
                src = &((Entry_002761D0 *)arg0)[j];
                if (src->id != 0xFFFF) {
                    j = 22;
                    *dst = *src;
                    src->id = 0xFFFF;
                    src->field_02 = 0xFF;
                    src->field_08 = -1;
                    src->field_04 = 0xFFFF;
                    src->state = 0;
                }
            }
        }
        i++;
        dst++;
    } while (i < 22);
}

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

typedef struct {
    u16 position;
    u8 flag;
    u8 pad;
} Slot_00276F10;

s32 func_00277160(void *arg0, s32 arg1, s32 arg2, void *arg3, s32 arg4, s32 arg5, u8 arg6, u8 arg7, u8 arg8,
                  s32 arg9, s32 arg10);

s32 func_00276F10(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8,
                  s32 arg9) {
    s32 state;
    s32 i;
    s32 result;
    u8 work[112];
    Slot_00276F10 slots[22];
    s16 c;
    s16 b;
    u16 a;
    extern s32 func_002770E0();
    extern void func_0027E770();

    if ((u32)func_001A8710() > 12000) {
        return -1;
    }
    for (i = 0; i < 22; i++) {
        slots[i].position = 0xFFFF;
        slots[i].flag = 0xFF;
    }
    func_0027E770(work);
    a = 0;
    b = 0;
    c = 0;
    state = 0;
    for (i = 1; i <= (u8)arg4; i++) {
        state = func_002770E0(state, arg0, arg1, arg2, arg3, (u8)i, arg8, arg9, slots, &a, &c, &b, work);
        result = func_00277160(arg0, arg1, arg2, slots, arg4, arg5, arg6, arg7, arg8, arg9, a);
        if (result >= 0) {
            return result;
        }
        if ((u32)func_001A8710() > 12000) {
            return -1;
        }
    }
    return -1;
}

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

s32 func_002774F0(s32 arg0, s32 arg1, void *arg2, s32 arg3, s32 arg4, u8 arg5, u8 arg6, u16 arg7) {
    extern s32 func_001E1030();
    s32 var_s0;
    s32 temp_s1;
    s32 temp_s2;
    u16 var_s3;
    u8 *var_s4;
    s32 spA0;
    s32 temp_v0_6;

    u8 var_fp;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v1;
    s32 var_a0;
    s32 var_a1;
    s32 var_v0_3;
    s32 var_v1_2;
    s32 var_a0_2;
    s32 var_a1_2;
    s32 y;
    s32 x;
    s32 y2;
    s32 x2;
    u16 temp_v0;
    u16 temp_v0_2;
    u16 temp_v0_3;
    u16 temp_v0_4;
    u16 temp_v0_5;
    s32 temp_v0_7;

    var_s4 = arg2;
    var_fp = 7;
    var_s3 = 0xFFFF & 0xFFFF;
    for (var_s0 = 0; var_s0 < arg7; var_s0++) {
        temp_v0 = *(u16 *)var_s4;
        if (func_001DF540((s32) temp_v0 >> 8, temp_v0 & 0xFF) != 0) {
            temp_v0_2 = *(u16 *)var_s4;
            temp_s1 = func_001E1090((s32) temp_v0_2 >> 8, temp_v0_2 & 0xFF);
            temp_v0_3 = *(u16 *)var_s4;
            if (func_00278150(func_001E2100((s32) temp_v0_3 >> 8, temp_v0_3 & 0xFF, 2), arg5) == 1) {
                temp_v0_4 = *(u16 *)var_s4;
                if (func_00278150(func_001E2100((s32) temp_v0_4 >> 8, temp_v0_4 & 0xFF, 5), arg6) == 1) {
                    temp_v0_5 = *(u16 *)var_s4;
                    if (func_0027C5A0((s32) temp_v0_5 >> 8, temp_v0_5 & 0xFF, arg4) == 1) {
                        temp_s2 = var_s4[2];
                        if (temp_s2 <= (u8) arg3) {
                          if ((s32) temp_s2 > 0) {
                            temp_v0_6 = var_fp & 0xFF;
                            if ((s32) temp_s2 < temp_v0_6) {
                                y = temp_s1 >> 8;
                                if (arg1 < y) {
                                    var_v0_2 = arg1;
                                } else {
                                    var_v0_2 = y;
                                }
                                if (y < arg1) {
                                    var_a0 = arg1;
                                } else {
                                    var_a0 = y;
                                }
                                x = temp_s1 & 0xFF;
                                if (arg0 < x) {
                                    var_v1 = arg0;
                                } else {
                                    var_v1 = x;
                                }
                                if (x < arg0) {
                                    var_a1 = arg0;
                                } else {
                                    var_a1 = x;
                                }
                                var_s3 = *(u16 *)var_s4;
                                var_fp = ((var_a1 - var_v1) + (var_a0 - var_v0_2)) & 0xFF;
                                arg3 = temp_s2 & 0xFF;
                            } else if (temp_s2 == temp_v0_6) {
                                temp_v0_7 = func_001DD0E0(func_001E1030(*(u16 *)var_s4 >> 8, *(u16 *)var_s4 & 0xFF))[3];
                                spA0 = (s32) temp_v0_7;
                                if ((s32) func_001DD0E0(func_001E1030(var_s3 >> 8, var_s3 & 0xFF))[3] < spA0) {
                                    y2 = temp_s1 >> 8;
                                    var_s3 = *(u16 *)var_s4;
                                    if (arg1 < y2) {
                                        var_v0_3 = arg1;
                                    } else {
                                        var_v0_3 = y2;
                                    }
                                    if (y2 < arg1) {
                                        var_a0_2 = arg1;
                                    } else {
                                        var_a0_2 = y2;
                                    }
                                    x2 = temp_s1 & 0xFF;
                                    if (arg0 < x2) {
                                        var_v1_2 = arg0;
                                    } else {
                                        var_v1_2 = x2;
                                    }
                                    if (x2 < arg0) {
                                        var_a1_2 = arg0;
                                    } else {
                                        var_a1_2 = x2;
                                    }
                                    var_fp = ((var_a1_2 - var_v1_2) + (var_a0_2 - var_v0_3)) & 0xFF;
                                    arg3 = temp_s2 & 0xFF;
                                }
                            }
                          }
                        }
                    }
                }
            }
        }
        var_s4 += 4;
    }
    var_v0 = var_s3 & 0xFFFF;
    if (var_v0 == 0xFFFF) {
        var_v0 = -1;
    }
    return var_v0;
}

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

typedef struct {
    u8 pad0[0x3E];
    u8 unk3E;
    u8 pad3F;
    u8 unk40;
    u8 unk41;
    u8 pad42[0x15];
    s8 low : 3;
    s8 flag : 1;
    s8 high : 4;
} Obj_00278250;

s32 func_00278250(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    extern s32 func_00250BC0(s32, s32, s32);
    extern s32 func_00250A60();
    extern s32 func_002787F0(void *, void *);
    Obj_00278250 *obj = (Obj_00278250 *)arg0;
    s32 mine;
    s32 theirs;

    if (obj == NULL) {
        return 0;
    }
    if (func_00250900(obj) == 1) {
        mine = 0;
    } else if ((obj->unk3E >> 5) != 0) {
        mine = 0;
    } else if (obj->unk40 == arg2 && obj->unk41 == arg3 && obj->flag) {
        mine = func_00250BC0(arg0, arg2, arg3);
    } else {
        mine = func_00250A60(arg0, arg2, arg3);
    }
    mine += func_002787F0(obj, (void *)func_001DF540(arg1 >> 8, arg1 & 0xFF));
    if (func_00250900((void *)func_001DF540(arg1 >> 8, arg1 & 0xFF)) == 1) {
        theirs = 0;
    } else if ((func_001E0700(arg1 >> 8, arg1 & 0xFF) >> 5) != 0) {
        theirs = 0;
    } else if (func_001E2100(arg1 >> 8, arg1 & 0xFF, 5) != 0) {
        theirs = func_00250B40(arg1 >> 8, arg1 & 0xFF, arg2, arg3);
    } else {
        theirs = func_002509E0(arg1 >> 8, arg1 & 0xFF, arg2, arg3);
    }
    theirs += func_002787F0((void *)func_001DF540(arg1 >> 8, arg1 & 0xFF), obj);
    return mine - theirs;
}

INCLUDE_ASM("asm/nonmatchings/main_078", func_00278420);

void func_00278510(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    if (arg1 == -1) {
        func_00278420(arg0, arg2, arg3, arg4);
        return;
    }
    if (func_002781B0(arg1 >> 8, arg1 & 0xFF, arg5 & 0xFF) == 0) {
        func_00278420(arg0, arg2, arg3, arg4);
        return;
    }
    func_00278250(arg0, arg1, arg3, arg4);
}

INCLUDE_ASM("asm/nonmatchings/main_078", func_002785D0);

typedef struct Info_002787F0 {
    u32 packed;
    u16 value;
} Info_002787F0;

typedef struct Object_002787F0 {
    u8 pad00[8];
    Info_002787F0 info;
    u8 pad10[0x2E];
    u8 flags;
} Object_002787F0;

u16 func_002787F0(void *arg0, void *arg1) {
    Object_002787F0 *first = arg0;
    Object_002787F0 *second = arg1;
    Info_002787F0 *info = &second->info;
    u32 packed = info->packed;
    u8 flags;

    switch (packed >> 8) {
    case 0x1B:
        flags = first->flags;
        if (((packed & 0x3F) == (flags & 0x1F)) && (((s32) flags >> 5) == 0)) {
            return info->value;
        }
        break;
    }
    info = &first->info;
    packed = info->packed;
    switch (packed >> 8) {
    case 0x1B:
        flags = second->flags;
        if (((packed & 0x3F) == (flags & 0x1F)) && (((s32) flags >> 5) == 0)) {
            return info->value;
        }
        break;
    }
    return 0;
}

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

typedef struct Entry_00278930 {
    s16 id;
    u8 slots[5];
    u8 pad;
    s32 values[4];
} Entry_00278930;

void func_00278930(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    Entry_00278930 *entry = arg0;
    s32 i;
    u8 *p;

    entry->id = arg1;
    i = 0;
    do {
        entry->slots[i] = 0xFF;
        i++;
    } while (i < 5);
    i = 0;
    p = arg0;
    do {
        i++;
        *(s32 *)(p + 8) = 0;
        p += 4;
    } while (i < 4);
    if (arg2 == 0) {
        ((u8 *)arg0)[2] = arg3;
        return;
    }
    func_00278DD0((u8 *)arg2, (u8 *)arg0 + 2);
    entry->slots[(u8)func_00278D90((u8 *)arg2)] = arg3;
}

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

u16 *func_00278E40(u16 *arg0) {
    s32 var_s3;
    u16 *temp_v0;
    s32 var_s5;
    u8 *var_s0;
    u16 *var_s1;

    var_s1 = arg0;
    if (var_s1 != NULL) {
        var_s5 = (func_0026FBB0(*var_s1) >> 0x10) & 0xFFFF;
        var_s3 = 0;
        var_s0 = (u8 *) var_s1;
        do {
            temp_v0 = func_00278E40(*(u16 **)(var_s0 + 8));
            if ((temp_v0 != NULL) && ((u32) (var_s5 & 0xFFFF) < (u32) (func_0026FBB0(*temp_v0) >> 0x10))) {
                var_s5 = (func_0026FBB0(*temp_v0) >> 0x10) & 0xFFFF;
                var_s1 = temp_v0;
            }
            var_s3 += 1;
            var_s0 += 4;
        } while (var_s3 < 4);
    } else {
        return NULL;
    }
    return var_s1;
}

INCLUDE_ASM("asm/nonmatchings/main_078", func_00278F10);

s32 func_00279130(s32 arg0, u16 *arg1) {
    u32 temp_s0;

    temp_s0 = func_0026FBB0(*arg1) >> 0x10;
    return (temp_s0 << 0x10) | (func_0026FBB0(*arg1) & 0xFFFF);
}

typedef struct Condition_00279170 {
    u16 id;
    u16 operation;
    u32 value;
} Condition_00279170;

s32 func_00279170(void *arg0, s32 arg1, u16 arg2) {
    Condition_00279170 *condition = arg0;

    if (condition == NULL) {
        return 1;
    }
    if (arg1 != condition->id) {
        return 1;
    }
    switch (condition->operation) {
    case 36:
        if ((func_0026FBB0(arg2) >> 16) >= condition->value) {
            return 1;
        }
        break;
    case 37:
        if ((func_0026FBB0(arg2) >> 16) <= condition->value) {
            return 1;
        }
        break;
    }
    return 0;
}

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

s32 func_002464F0();
s32 func_0024FE40(void *, s32, s32);

static inline s32 distance_0027A710(s32 y1, s32 x1, s32 y2, s32 x2) {
    return (((y2 < y1) ? y1 : y2) - ((y1 < y2) ? y1 : y2)) +
           (((x2 < x1) ? x1 : x2) - ((x1 < x2) ? x1 : x2));
}

s32 func_0027A710(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4,
                  s32 *arg5, s32 arg6, u8 arg7, u16 arg8) {
    s32 flags;
    s32 dy;
    extern s32 func_00278420();

    flags = func_002464F0(arg0, arg1, arg2);
    if (arg0 == NULL) {
        return 0;
    }
    if (distance_0027A710(arg1, arg2, arg3, arg4) == 0) {
        return 1;
    }
    if (distance_0027A710(arg1, arg2, arg3, arg4) == 1) {
        s32 cell;
        s32 y;
        s32 x;
        s32 result;

        if ((func_001E22B0(arg3, arg4) == 8 && !(flags & 0x10)) ||
            (func_001E22B0(arg3, arg4) == 9 &&
             func_0024FE40(arg0, arg3, arg4) == 1)) {
            return 0;
        }
        if (func_001E36E0(arg3, arg4) == 0) {
            return 1;
        }
        cell = func_001E3790(arg3, arg4);
        if (arg5 != NULL && cell == *arg5) {
            return 1;
        }
        y = cell >> 8;
        x = cell & 0xFF;
        if (func_00250360(y, x) != func_00250370(arg0)) {
            if (func_002781B0(y, x, arg6) != 0) {
                result = func_00278250((s32)arg0, cell, arg3, arg4) > 0;
            } else {
                result = func_00278420((s32)arg0, arg8, arg3, arg4) > 0;
            }
            if (result) {
                return 1;
            }
            return 2;
        } else {
            if (x != 0) {
                return arg7 == 1 ? 0 : 1;
            }
            return 0;
        }
    }
    if (distance_0027A710(arg1, arg2, arg3, arg4) == 2) {
        dy = arg1 - arg3;
        dy = dy >= 0 ? dy : -dy;
        switch (dy) {
        case 0: {
            s32 midX = (arg2 + arg4) >> 1;
            if (func_0027A710(arg0, arg1, arg2, arg3, midX, arg5, arg6, arg7, arg8) == 1) {
                return func_0027A710(arg0, arg1, midX, arg3, arg4, arg5, arg6, arg7, arg8);
            }
            goto failed;
        }
        case 2: {
            s32 midY = (arg1 + arg3) >> 1;
            if (func_0027A710(arg0, arg1, arg2, midY, arg4, arg5, arg6, arg7, arg8) == 1) {
                return func_0027A710(arg0, midY, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
            }
            goto failed;
        }
        case 1:
            if (func_0027A710(arg0, arg1, arg2, arg3, arg2, arg5, arg6, arg7, arg8) == 1 &&
                func_0027A710(arg0, arg3, arg2, arg3, arg4, arg5, arg6, arg7, arg8) == 1) {
                return 1;
            }
            if (func_0027A710(arg0, arg1, arg2, arg1, arg4, arg5, arg6, arg7, arg8) == 1 &&
                func_0027A710(arg0, arg1, arg4, arg3, arg4, arg5, arg6, arg7, arg8) == 1) {
                return 1;
            }
            return 0;
        default:
            return 0;
        }
    }
failed:
    return 0;
}

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

typedef struct Position_0027ACB0 {
    u8 x : 4;
    u8 y : 4;
    u8 nextX : 4;
    u8 nextY : 4;
} Position_0027ACB0;

void func_0027ACB0(s32 first, s32 *count, u8 *bestDepth, s32 node,
                   s32 x, s32 y, s32 closest, u8 depth) {
    s32 i;

    if (node != 0) {
        if (((Position_0027ACB0 *)node)->x == x &&
            (*(u8 *)node >> 4) == y) {
            s32 currentDepth = (u8)depth;

            if (currentDepth < *bestDepth) {
                s32 position;

                *count = 0;
                *bestDepth = depth;
                position = (u8)func_0027AF20((void *)node, 0);
                if (position < 0) {
                    ((Position_0027ACB0 *)closest)->x = x;
                    ((Position_0027ACB0 *)closest)->y = y;
                } else {
                    ((Position_0027ACB0 *)closest)->x = (u8)position & 0xF;
                    ((Position_0027ACB0 *)closest)->y = (u8)position >> 4;
                }
                ((Position_0027ACB0 *)closest)->nextX = 0xF;
                ((Position_0027ACB0 *)closest)->nextY = 0xF;
            } else if (*bestDepth == currentDepth) {
                s32 position;

                *count += 1;
                position = (u8)func_0027AF20((void *)node, 0);
                if (position < 0) {
                    ((Position_0027ACB0 *)first)->nextX = x;
                    ((Position_0027ACB0 *)first)->nextY = y;
                } else {
                    ((Position_0027ACB0 *)first)->nextX = (u8)position & 0xF;
                    ((Position_0027ACB0 *)first)->nextY = (u8)position >> 4;
                }
            }
            return;
        } else {
            s32 *child = (s32 *)node;
            s32 nextDepth = (u8)depth + 1;

            i = 0;
            do {
                func_0027ACB0(first, count, bestDepth, child[1], x, y,
                              closest, nextDepth);
                i++;
                child++;
            } while (i < 12);
        }
    }
}

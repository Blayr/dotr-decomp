#include "common.h"

typedef struct Node_0027AF20 {
    u8 value;
    u8 padding[0x33];
    struct Node_0027AF20 *next;
} Node_0027AF20;

u8 func_0027AF20(void *arg0, u8 depth) {
    Node_0027AF20 *node = arg0;
    Node_0027AF20 *next;

    if (depth >= 7) {
        return 0xFFU;
    }
    next = node->next;
    if (next == NULL) {
        return 0xFFU;
    }
    if (next->next == NULL) {
        return node->value;
    }
    return func_0027AF20(next, depth + 1);
}

void func_0027AF80(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 var_a2;
    s32 *var_a3;

    *(s8 *)arg0 = (s8) ((arg3 << 4) | arg2);
    var_a2 = 0;
    var_a3 = arg0;
    do {
        var_a2 += 1;
        var_a3[1] = 0;
        var_a3++;
    } while (var_a2 < 0xC);
    *(s32 *)((u8 *)arg0 + 0x34) = arg1;
}

typedef struct {
    u8 low : 4;
    u8 high : 4;
} Nibbles_0027AFC0;

s32 func_0027AFC0(u8 *arg0) {
    s32 i;
    s32 count;
    Nibbles_0027AFC0 *entries = (Nibbles_0027AFC0 *)arg0;

    i = 0;
    count = 0;
    do {
        if (entries[i].low != 0xF && entries[i].high != 0xF) {
            count++;
        }
        i++;
    } while (i < 0xC);
    return count;
}

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027B010);

u8 *func_0027B150(u16 *arg0, u16 *arg1) {
    u16 temp_a2;

    if ((s64) (u32) (*arg0 + 0x38) > 0x10000) {
        return 0;
    }
    temp_a2 = *arg1;
    *arg1 = temp_a2 + 1;
    *arg0 += 0x38;
    return (u8 *) 0x01ED0000 + temp_a2 * 0x38;
}

void func_0027B1B0(void *arg0, u8 arg1) {
    if (arg1 < 2) {
        if (arg1 == 1) {
            *(u32 *)((u8 *)arg0 + 8) =
                (*(u32 *)((u8 *)arg0 + 8) & 0xFFFF) | 0xFFFF0000;
        } else {
            *(u32 *)((u8 *)arg0 + 8) =
                (*(u32 *)((u8 *)arg0 + 8) & 0xFFFF0000) | 0xFFFF;
        }
    }
}

void func_0027B200(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4,
                   s32 arg5, s32 arg6, s32 arg7, u8 arg8) {
    func_0027B290(func_001DF540(arg0, arg1), arg2, arg3, arg4, arg5,
                  arg6, arg7, arg8);
}

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027B290);

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027B360);

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027B520);

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027B650);

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027B740);

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027B860);

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027B9B0);

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027BBC0);

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027BE10);

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027C070);

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027C2C0);

s32 func_0027C5A0(s32 arg0, s32 arg1, s32 arg2) {
    switch (arg2) {
    case 0x22:
        if (arg1 != 0) {
            break;
        }
        return 1;
    case 0x1D:
        if ((arg1 > 0) && (arg1 < 6)) {
            return 1;
        }
        break;
    case 0x1E:
        if ((arg1 > 5) && (arg1 < 0xC)) {
            return 1;
        }
        break;
    case 0x1F:
        return 1;
    case 0x34:
        if (arg1 != 0) {
            return 1;
        }
        break;
    default:
        if (arg1 != 0) {
            return 1;
        }
        break;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027C670);

s32 func_0027C6D0(s32 arg0) {
    s32 column;
    s32 row;
    s32 terrain;

    column = arg0 & 0xFF;
    row = arg0 >> 8;
    if (func_001E2100(row, column, 0) != 0) {
        return 1;
    }
    terrain = func_001E0700(row, column) >> 5;
    switch (terrain) {
    case 3:
    case 4:
        if (func_001E2100(row, column, 4) != 0) {
            return 0;
        }
        break;
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027C770);

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027CA50);

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027D020);

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027D720);

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027D830);

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027DA40);

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027DBC0);

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027DD20);

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027DE20);

s32 func_0027E150(s32 arg0) {
    s32 index;
    s32 count;
    s32 result;
    s32 low;
    s32 high;
    s32 value;

    count = func_0024E910(arg0);
    result = arg0;
    for (index = 0; index < count; index++) {
        value = func_0024EC50(arg0, index);
        high = value >> 8;
        low = value & 0xFF;
        if (func_001E2100(high, low, 4) == 0) {
            result = func_0024C7D0((u32) high, low, result);
        }
    }
    return result;
}

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027E210);

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027E360);

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027E5B0);

void func_0027E770(void) {

}

typedef struct State_0027E780 {
    u16 position;
    u16 pad2;
    u16 flags;
    u16 pad6;
    u32 destination;
} State_0027E780;

s32 func_0027D830(s32, s32, s32, s32, s32, s32);

void func_0027E780(void *arg0, s32 arg1, s32 arg2) {
    State_0027E780 *state = arg0;
    s32 destination;
    s32 result;
    u32 packed_destination;
    u16 position;

    destination = func_001E1090(arg1 >> 8, arg1 & 0xFF);
    position = state->position;
    result = func_0027D830(position >> 8, position & 0xFF,
                         destination & 0xFF, destination >> 8, 0, arg2);
    switch (result) {
    case 1:
    case 2:
        state->flags = 0x6FF;
        packed_destination = state->destination & 0xFFFF;
        state->destination = (destination << 16) | packed_destination;
        break;
    default:
        state->flags = 0x2FF;
        packed_destination = state->destination & 0xFFFF;
        state->destination = (arg1 << 16) | packed_destination;
        break;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027E840);

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027EB00);

void func_0027F0D0(void *arg0) {
    f32 *values = arg0;

    values[0] = values[1] = values[2] = values[3] = 1.0f;
    values[4] = values[5] = values[6] = values[7] = 0.0f;
    values[8] = values[9] = values[10] = values[11] = 0.0f;
}

void func_0020C940(void *, void *, void *, void *);
void func_0020EB40(void *);

typedef struct {
    f32 values[4][4];
} Matrix_0027F110;

void func_0027F110(u8 *arg0) {
    Matrix_0027F110 matrix;

    func_0020EB40(arg0 + 0x30);
    func_0020C940(&matrix, arg0, arg0 + 0x10, arg0 + 0x20);
    func_0020BC00((s32)(arg0 + 0x30), &matrix);
}

s32 func_0027F160(s32 arg0, s32 arg1) {
    return !(arg0 & (1 << arg1)) ? 0 : 1;
}

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027F180);

typedef struct Vec3_0027F290 {
    f32 x;
    f32 y;
    f32 z;
} Vec3_0027F290;

void func_0027F290(void *arg0, void *arg1, s32 arg2) {
    Vec3_0027F290 vec;
    f32 temp_f1;

    if (arg2 != 0) {
        vec.x = ((Vec3_0027F290 *)arg1)->x;
        vec.y = ((Vec3_0027F290 *)arg1)->y;
        vec.z = ((Vec3_0027F290 *)arg1)->z;
        func_0027F3A0(&vec, arg0);
        temp_f1 = (f32) arg2;
        vec.x /= temp_f1;
        vec.y /= temp_f1;
        vec.z /= temp_f1;
        func_0027F360(arg0, &vec);
        return;
    }
    ((Vec3_0027F290 *)arg0)->x = ((Vec3_0027F290 *)arg1)->x;
    ((Vec3_0027F290 *)arg0)->y = ((Vec3_0027F290 *)arg1)->y;
    ((Vec3_0027F290 *)arg0)->z = ((Vec3_0027F290 *)arg1)->z;
}

void func_0027F360(void *arg0, void *arg1) {
    f32 *dst = arg0;
    f32 *src = arg1;

    dst[0] += src[0];
    dst[1] += src[1];
    dst[2] += src[2];
}

void func_0027F3A0(void *arg0, void *arg1) {
    f32 *dst = arg0;
    f32 *src = arg1;

    dst[0] -= src[0];
    dst[1] -= src[1];
    dst[2] -= src[2];
}

void func_0027F3E0(u8 arg0, s32 arg1) {
    func_0027F480(arg1);
    switch (arg0) {
    case 32:
        func_0027F5A0();
        break;
    case 35:
        func_001DE5E0(0, 4, 8);
        func_001DE5E0(1, 4, 8);
        break;
    case 36:
        func_0027F5B0();
        break;
    }
}

typedef struct Entry_0027F480 {
    u16 field_0;
    u16 field_2;
    u16 field_4;
    u16 field_6;
    s32 field_8;
    u8 flags : 2;
    u8 reserved : 6;
    u8 padding[3];
} Entry_0027F480;

typedef struct State_0027F480 {
    Entry_0027F480 entries[22];
    u16 indices[32];
    u8 flags : 5;
    u8 reserved : 3;
    u8 padding_1a1;
    u16 field_1a2;
    u16 field_1a4;
    u8 padding_1a6[10];
    f32 position[4];
    f32 rotation[4];
} State_0027F480;

void func_0027F480(s32 arg0) {
    f32 *rotation;
    f32 *position;
    u8 *cursor;
    s32 j;
    s32 i;
    Entry_0027F480 *entry;
    State_0027F480 *state = (State_0027F480 *)arg0;

    position = (f32 *)func_001F9D30(0);
    rotation = func_001FAF60(0);
    if (state != 0) {
        state->field_1a2 = 0;
        state->field_1a4 = 0;
        i = 0;
        entry = state->entries;
        do {
            entry->field_0 = 0xFFFF;
            entry->field_2 = 0xFF;
            entry->field_8 = -1;
            entry->field_4 = 0xFFFF;
            i += 1;
            entry->flags = 0;
            entry++;
        } while (i < 22);
        j = 0;
        cursor = (u8 *)state;
        do {
            j += 1;
            *(u16 *)(cursor + 0x160) = 0xFFFF;
            cursor += 2;
        } while (j < 32);
        state->flags = 0;
        state->position[0] = position[0];
        state->position[1] = position[1];
        state->position[2] = position[2];
        state->position[3] = position[3];
        state->rotation[0] = rotation[0];
        state->rotation[1] = rotation[1];
        state->rotation[2] = rotation[2];
        state->rotation[3] = rotation[3];
        state->indices[1] = 0;
    }
}

void func_0027F5A0(void) {

}

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027F5B0);

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027F630);

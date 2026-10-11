#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_055", func_00202220);

INCLUDE_ASM("asm/nonmatchings/main_055", func_002024D0);

typedef struct {
    s32 data;
    char *name;
    s8 flag0 : 1;
    s8 flag1 : 1;
    s8 flag2 : 1;
    s16 category : 13;
    s16 id;
} Slot_00202810;

void func_002029B0(s32, s32);

static inline void *find_00202810(s32 arg0, s32 arg1) {
    Slot_00202810 *entry = func_002008A0(arg0, arg1);
    if (entry != NULL && !(entry->data & 0x80000000)) {
        return entry;
    }
    return NULL;
}

static inline void *alloc_00202810(void) {
    extern Slot_00202810 D_003229A0[];
    Slot_00202810 *entry;
    s32 i;

    entry = D_003229A0;
    i = 0;
    do {
        if (entry->data == 0) {
            return entry;
        }
        i++;
        entry++;
    } while (i < 0x400);
    return NULL;
}

s32 func_00202810(s32 arg0, s32 arg1, char *arg2, s32 arg3) {
    Slot_00202810 *entry;

    if (arg0 < 0 || arg0 >= 10) {
        return 0;
    }
    if (arg1 < 0) {
        return 0;
    }
    entry = find_00202810(arg0, arg1);
    if (entry == NULL) {
        entry = alloc_00202810();
        if (entry == NULL) {
            return 0;
        }
    } else {
        func_002029B0(arg0, arg1);
    }
    entry->name = (arg2 != NULL) ? func_00217B60(arg2) : NULL;
    entry->data = arg3;
    entry->flag0 = 0;
    entry->flag1 = 0;
    entry->flag2 = 0;
    entry->category = arg0;
    entry->id = arg1;
    return 1;
}

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

typedef struct Fields_00202E30 {
    u8 padding[0x40];
    u16 field40;
    u16 field42;
} Fields_00202E30;

s32 func_00202E30(void *arg0) {
    s32 multiplier;
    s32 shift;
    s32 result;

    switch (((Fields_00202E30 *)arg0)->field40) {
    case 0x14:
        shift = 4;
        break;
    case 0x13:
        shift = 8;
        break;
    default:
        return 0;
    }

    switch (((Fields_00202E30 *)arg0)->field42) {
    case 0:
        multiplier = 4;
        break;
    case 2:
    case 0xA:
        multiplier = 2;
        break;
    default:
        return 0;
    }

    result = ((1 << shift) * multiplier / 64) / 4;
    return result <= 0 ? 1 : result;
}

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

void func_00192588(s32);
void func_001927E8(s32, s32, u8 *);

typedef struct {
    s8 low : 4;
    s8 high : 4;
} Flags_002031F0;

typedef struct {
    s8 type;
    Flags_002031F0 mode;
    u8 pad[0x5A];
} Port_002031F0;

extern u8 D_00325AC0;
extern Port_002031F0 D_00325C75[];

void func_002031F0(void) {
    func_0020B3C0((s8 *) D_003259C0, 0, 0x2C0);
    D_00325C75[-1].type = 0xA;
    D_00325C75[0].type = 0xA;
    D_00325C75[-1].mode.low = 4;
    D_00325C75[0].mode.low = 4;
    func_00192588(0);
    func_001927E8(0, 0, D_003259C0);
    func_001927E8(1, 0, &D_00325AC0);
}

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

typedef struct Flags_00203840 {
    s8 status : 6;
    s8 unused : 2;
} Flags_00203840;

void func_00203840(void) {
    s32 var_a2;
    s32 var_a3;
    u8 *temp_t0;
    s32 temp_t1;
    u8 *var_t2;
    u8 *var_t3;
    s32 temp_t4;

    var_t3 = D_003259C0;
    var_a2 = 0;
    do {
        temp_t0 = var_t3 + 0x200;
        if (((Flags_00203840 *)(var_t3 + 0x25B))->status == 5) {
            var_a3 = 0;
            var_t2 = temp_t0;
            do {
                temp_t1 = 1 << var_a3;
                temp_t4 = *(u16 *)temp_t0 & temp_t1;
                if ((temp_t4 != 0) && (temp_t4 == (*(u16 *)(temp_t0 + 2) & temp_t1))) {
                    *(s32 *)(var_t2 + 0x18) += 1;
                } else {
                    *(s32 *)(var_t2 + 0x18) = -*(s8 *)(temp_t0 + 0x59);
                }
                var_a3 += 1;
                var_t2 += 4;
            } while (var_a3 < 0x10);
            *(u16 *)(temp_t0 + 2) = *(u16 *)temp_t0;
            *(u16 *)temp_t0 = *(u16 *)(temp_t0 + 4);
            *(u16 *)(temp_t0 + 4) = 0;
        }
        var_a2 += 1;
        var_t3 += 0x5C;
    } while (var_a2 < 2);
}

typedef struct Flags_002038F0 {
    s8 mode : 6;
    s8 axes : 1;
    s8 pressure : 1;
} Flags_002038F0;

extern u8 D_003259C0[];
s32 func_00192B38(s32, s32, void *);
s32 func_00192BB8(s32, s32);

s32 func_002038F0(void) {
    u8 data[20];
    u8 *pressure;
    s32 axisIndex;
    s32 state;
    u8 *axes;
    s32 pressureIndex;
    s32 port;
    u8 *pad;
    u8 *entry;

    entry = D_003259C0;
    port = 0;
    do {
        pad = entry + 0x200;
        if (((Flags_002038F0 *)(entry + 0x25B))->mode == 5) {
            state = func_00192BB8(port, 0);
            if (state == 2 || state == 6) {
                if (func_00192B38(port, 0, data) != 0) {
                    if (((Flags_002038F0 *)(pad + 0x5B))->axes) {
                        axes = data;
                        axisIndex = 0;
                        do {
                            pad[6 + axisIndex] = axes[4];
                            axisIndex++;
                            axes++;
                        } while (axisIndex < 4);
                    }
                    if (((Flags_002038F0 *)(pad + 0x5B))->pressure) {
                        pressure = data;
                        pressureIndex = 0;
                        do {
                            pad[0xA + pressureIndex] = pressure[8];
                            pressureIndex++;
                            pressure++;
                        } while (pressureIndex < 12);
                    }
                    *(u16 *)(pad + 4) |= ((data[2] << 8) | data[3]) ^ 0xFFFF;
                }
            }
        }
        port++;
        entry += 0x5C;
    } while (port < 2);
    return 1;
}

typedef struct State_00203A40 {
    u16 flags;
    u16 disabled;
    u8 padding04[0x14];
    s32 counters[16];
    u8 padding58[2];
    s8 interval : 4;
    s8 other : 4;
    u8 padding5B;
} State_00203A40;

s32 func_00203A40(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_a1;
    State_00203A40 *temp_a3;
    s32 temp_t0;
    u8 *var_t1;
    s32 mask;
    s32 temp_t3;
    s32 var_s0;
    u8 *temp_v0;

    temp_v0 = D_003259C0 + (arg0 * 0x5C);
    temp_a3 = (State_00203A40 *)(temp_v0 + 0x200);
    switch (arg1) {
    case 0:
        return arg2 & (temp_a3->flags & ~temp_a3->disabled);
    case 2:
        var_s0 = 0;
        var_a1 = 0;
        var_t1 = (u8 *)temp_a3;
        mask = arg2 & 0xFFFF;
        do {
            temp_t0 = 1 << var_a1;
            if (mask & temp_t0) {
                temp_t3 = *(s32 *)(var_t1 + 0x18);
                if ((temp_t3 >= 0) && ((temp_t3 % temp_a3->interval) == 0)) {
                    var_s0 = (var_s0 | temp_t0) & 0xFFFF;
                }
            }
            var_a1 += 1;
            var_t1 += 4;
        } while (var_a1 < 0x10);
        return var_s0 | func_00203A40(arg0, 0, arg2);
    case 1:
        return temp_a3->flags & arg2;
    }
    return 0;
}

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

s32 func_00205150(void) {
    return D_00325C80;
}

s32 func_00205160(void) {
    return D_00325C84;
}

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

void func_00205C90(s32 arg0) {
    func_001FB0B0(0, arg0);
}

void func_00205CA0(s32 arg0) {
    func_001FB1D0(0, arg0);
}

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

s32 func_00205D10(void *arg0, f32 fparg0) {
    f32 vector[4];
    f32 matrix1[4][4];
    f32 matrix2[4][4];

    func_0020EBA0(matrix1);
    func_0020EC00(matrix2);
    ((f32 *)arg0)[3] = 1.0f;
    func_0020CDD0(vector, matrix1, arg0);
    vector[2] -= fparg0;
    func_0020CDD0(vector, matrix2, vector);
    if (vector[3] <= 0.0f) {
        return 0xFFFFF6;
    }
    if (vector[2] <= 0.0f) {
        return 0;
    }
    return func_001A23B0(vector[2] / vector[3]);
}

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

typedef struct Vec4_00206030 {
    f32 x, y, z, w;
} Vec4_00206030;

s32 func_00206030(s32 count, void *arg1, void *arg2) {
    Vec4_00206030 *src = arg1;
    Vec4_00206030 *dst = arg2;
    s32 i;
    f32 divisor;

    dst->x = 0.0f;
    dst->y = 0.0f;
    dst->z = 0.0f;
    dst->w = 0.0f;
    if (count == 0) {
        return 0;
    }
    for (i = 0; i < count; i++) {
        dst->x += src->x;
        dst->y += src->y;
        dst->z += src->z;
        dst->w += src->w;
        src++;
    }
    divisor = (f32) count;
    dst->x /= divisor;
    dst->y /= divisor;
    dst->z /= divisor;
    dst->w /= divisor;
    return 1;
}

s32 func_002060F0(f32 *origin, s32 count, f32 *points, f32 *out) {
    s32 i;
    f32 divisor;

    out[0] = 0.0f;
    out[1] = 0.0f;
    out[2] = 0.0f;
    out[3] = 0.0f;
    if (count == 0) {
        return 0;
    }

    for (i = 0; i < count; i++) {
        out[0] += (origin != NULL ? origin[0] : 0.0f) - points[0];
        out[1] += (origin != NULL ? origin[1] : 0.0f) - points[1];
        out[2] += (origin != NULL ? origin[2] : 0.0f) - points[2];
        points += 4;
    }

    divisor = (f32) count;
    out[0] /= divisor;
    out[1] /= divisor;
    out[2] /= divisor;
    func_0020D070(out);
    return 1;
}

typedef struct Point_002061F0 {
    f32 x;
    f32 y;
    f32 z;
    u8 padding[0x24];
} Point_002061F0;

s32 func_002061F0(f32 *origin, s32 count, void *src, f32 *out) {
    f32 divisor;
    s32 i;
    Point_002061F0 *point;

    point = src;
    out[0] = 0.0f;
    out[1] = 0.0f;
    out[2] = 0.0f;
    out[3] = 0.0f;
    if (count == 0) {
        return 0;
    }

    for (i = 0; i < count; i++, point++) {
        out[0] += (origin != NULL ? origin[0] : 0.0f) - point->x;
        out[1] += (origin != NULL ? origin[1] : 0.0f) - point->y;
        out[2] += (origin != NULL ? origin[2] : 0.0f) - point->z;
    }

    divisor = (f32)count;
    out[0] /= divisor;
    out[1] /= divisor;
    out[2] /= divisor;
    func_0020D070(out);
    return 1;
}

void func_002062F0(f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    arg3[0] = arg0[1] * (arg1[2] - arg2[2])
            + arg1[1] * (arg2[2] - arg0[2])
            + arg2[1] * (arg0[2] - arg1[2]);
    arg3[1] = arg0[2] * (arg1[0] - arg2[0])
            + arg1[2] * (arg2[0] - arg0[0])
            + arg2[2] * (arg0[0] - arg1[0]);
    arg3[2] = arg0[0] * (arg1[1] - arg2[1])
            + arg1[0] * (arg2[1] - arg0[1])
            + arg2[0] * (arg0[1] - arg1[1]);
    arg3[3] = arg0[0] * (arg1[2] * arg2[1] - arg1[1] * arg2[2])
            + arg0[1] * (arg1[0] * arg2[2] - arg1[2] * arg2[0])
            + arg0[2] * (arg1[1] * arg2[0] - arg1[0] * arg2[1]);
    arg3[4] = func_001A6C60(arg3[0] * arg3[0]
                           + arg3[1] * arg3[1]
                           + arg3[2] * arg3[2]);
}

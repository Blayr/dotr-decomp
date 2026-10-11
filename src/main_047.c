#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_047", func_001E4570);

void func_001E4E50(void) {
    D_00318144 = 0x18;
}

typedef struct {
    s8 pad0 : 5;
    s8 flag : 1;
    s8 pad1 : 2;
} Flags;

extern Flags D_003181F7;

void func_001E4E60(s64 arg0) {
    D_003181F7.flag = arg0;
}

typedef struct {
    s32 entries[2];
    s32 count;
} State_001E4E90;

void func_001E4E90(void) {
    extern State_001E4E90 D_0031AB88;
    State_001E4E90 *state = &D_0031AB88;
    s32 i;

    func_0020B3C0((s8 *)&D_0031AB88, 0, 0xC);
    i = 0;
    do {
        state->entries[i] = -1;
        i++;
    } while (i < 2);
    state->count = 0;
}

INCLUDE_ASM("asm/nonmatchings/main_047", func_001E4F00);

typedef struct {
    u8 padding[8];
    s32 field8;
} State_001E5210;

extern State_001E5210 D_0031AB88;

void func_001E5210(void *arg0, s32 arg1) {
    State_001E5210 *state = &D_0031AB88;
    s32 var_v1;

    if (arg1 != 0) {
        var_v1 = *(s32 *)((u8 *)arg0 + 0x14);
    } else {
        var_v1 = 0;
    }
    state->field8 = var_v1;
}

s32 func_001E5230(void) {
    return D_0031AB90;
}

INCLUDE_ASM("asm/nonmatchings/main_047", func_001E5240);

INCLUDE_ASM("asm/nonmatchings/main_047", func_001E5260);

INCLUDE_ASM("asm/nonmatchings/main_047", func_001E53C0);

s32 func_001E5590(s32 arg0) {
    if (func_001F3130(8) != 0) {
        return func_001E55E0(arg0);
    }
    return arg0;
}

INCLUDE_ASM("asm/nonmatchings/main_047", func_001E55E0);

s32 func_001E5D30(s32 arg0, s32 arg1, s32 arg2) {
    s32 parameters[4];

    arg0 = func_001EFA80(arg0, arg1, 0, 0, 0, 0, 0);
    if (arg2 < 9) {
        func_001F2330(arg1, parameters);
        parameters[1] = 0x8000;
        arg0 = func_001EFA80(arg0, arg1, 0, (s32) parameters, 0, 0, 0);
    }
    return arg0;
}

INCLUDE_ASM("asm/nonmatchings/main_047", func_001E5DD0);

INCLUDE_ASM("asm/nonmatchings/main_047", func_001E5EB0);

INCLUDE_ASM("asm/nonmatchings/main_047", func_001E60E0);

INCLUDE_ASM("asm/nonmatchings/main_047", func_001E6650);

INCLUDE_ASM("asm/nonmatchings/main_047", func_001E6F90);

void func_001E77A0(void) {
    s32 i;

    i = 0;
    do {
        func_001E53C0(i, 0);
        i += 1;
    } while (i < 2);
}

void func_001E77E0(s32 arg0) {
    s32 var_s0;

    func_001F9770(0, 9, 1);
    var_s0 = 0;
    do {
        func_001F30B0(var_s0, 0);
        var_s0 += 1;
    } while (var_s0 < 0x54);
    var_s0 = 0;
    do {
        func_001F30B0(var_s0 + 0x22, 1);
        var_s0 += 1;
    } while (var_s0 < 0x28);
    var_s0 = 0;
    do {
        func_001F30B0(var_s0 + 0x1E, 1);
        var_s0 += 1;
    } while (var_s0 < 2);
    if (arg0 != D_00292468) {
        D_00292468 = arg0;
    }
}

void func_001E7890(void) {
    func_00209D30(func_001E78C0(func_00209D20()));
}

INCLUDE_ASM("asm/nonmatchings/main_047", func_001E78C0);

void func_001E7A50(void) {

}

INCLUDE_ASM("asm/nonmatchings/main_047", func_001E7A60);

INCLUDE_ASM("asm/nonmatchings/main_047", func_001E7B20);

typedef struct {
    s8 bit0 : 1;
    s8 bit1 : 1;
    s8 bits2_4 : 3;
    s8 bit5 : 1;
    s8 bits6_7 : 2;
} Flags_001E7D00;

void func_001F2C60(s32, s32, s32);

s32 func_001E7D00(s32 index) {
    Obj_0031ABB0 *object;

    if ((index < 0) || (index >= 0x54)) {
        return 0;
    }
    object = D_0031ABB0[index];
    if (object == NULL) {
        return 0;
    }
    *(f32 *)((u8 *)object + 0x198) = 1.0f;
    *(f32 *)((u8 *)object + 0x19C) = 1.0f;
    *(f32 *)((u8 *)object + 0x1A0) = 1.0f;
    *(f32 *)((u8 *)object + 0x1A4) = 1.0f;
    *(f32 *)((u8 *)object + 0x1A8) = 1.0f;
    *(f32 *)((u8 *)object + 0x1AC) = 0.0f;
    object->lv[1] = -1;
    object->lv[0] = 0;
    ((Flags_001E7D00 *)((u8 *)object + 0x20D))->bit1 = 0;
    *(s8 *)((u8 *)object + 0x200) = 0;
    *(s16 *)((u8 *)object + 0x20A) = 0;
    *(s8 *)((u8 *)object + 0x1FB) = 6;
    *(s8 *)((u8 *)object + 0x1FC) = 0;
    *(s8 *)((u8 *)object + 0x1FD) = 0;
    ((Flags_001E7D00 *)((u8 *)object + 0x20C))->bit5 = 0;
    func_001F2C60(index, -1, 1);
    *(s16 *)((u8 *)object + 0x1F0) = 0x7FFF;
    return 1;
}

s32 func_001E7DE0(s32 arg0) {
    s32 func_001F08D0(s32);
    void func_00217B50(void *);
    Obj_0031ABB0 *obj;
    Obj_0031ABB0 **slot;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    slot = &D_0031ABB0[arg0];
    obj = *slot;
    if (obj == NULL) {
        return 0;
    }
    if (func_001F08D0(arg0) == 0) {
        return 0;
    }
    func_00217B50(obj);
    *slot = NULL;
    return 1;
}

typedef struct {
    s8 unused0 : 2;
    s8 pending : 1;
    s8 busy : 1;
    s8 unused4 : 4;
} Flags_001E7E70;

void func_001F08D0(s32);

static inline s64 busy_001E7E70(Obj_0031ABB0 *obj) {
    return (s64) ((u64) obj->lv[0x2C] << 60) >> 63;
}

s32 func_001E7E70(s32 arg0, s32 arg1, s32 arg2) {
    Obj_0031ABB0 *temp_s0;

    if ((arg0 < 0) || (arg0 >= 0x54)) {
        return 0;
    }
    temp_s0 = D_0031ABB0[arg0];
    if (temp_s0 == NULL) {
        return 0;
    }
    if (busy_001E7E70(temp_s0)) {
        while (busy_001E7E70(temp_s0)) {
            func_001FF420();
        }
    }
    func_001F08D0(arg0);
    *(s8 *) ((u8 *) temp_s0 + 0x1F2) = -1;
    if (arg1 >= 0) {
        *(s8 *) ((u8 *) temp_s0 + 0x1F3) = (s8) arg1;
    }
    *(s16 *) ((u8 *) temp_s0 + 0x1F4) = (s16) arg2;
    ((Flags_001E7E70 *) &temp_s0->lv[0x2C])->pending = 1;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_047", func_001E7F70);

INCLUDE_ASM("asm/nonmatchings/main_047", func_001E84D0);

INCLUDE_ASM("asm/nonmatchings/main_047", func_001E8780);

INCLUDE_ASM("asm/nonmatchings/main_047", func_001E8BF0);

INCLUDE_ASM("asm/nonmatchings/main_047", func_001E8E90);

typedef struct {
    s32 data;
    s32 unk04;
    s32 additional;
    s32 resolved;
} Entry_001E8FA0;

s32 func_001E8FA0(s32 arg0) {
    Obj_0031ABB0 *obj;
    Entry_001E8FA0 *entry;
    s32 count;
    s32 i;
    void *directory;
    s32 base;
    u8 *table;

    if ((arg0 < 0) || (arg0 >= 0x54)) {
        return 0;
    }
    obj = D_0031ABB0[arg0];
    if (obj == NULL) {
        return 0;
    }
    base = *(s32 *)&obj->pad040[0xF8];
    if (base == 0) {
        return 1;
    }
    directory = *(void **)&obj->pad040[0xFC];
    if (*(s32 *)((u8 *)directory + 0x2C) == 0) {
        return 1;
    }
    i = 0;
    table = (u8 *)(base + *(s32 *)((u8 *)directory + 0x28));
    count = *(s32 *)table;
    entry = (Entry_001E8FA0 *)(table + 0x10);
    for (; i < count; i++, entry++) {
        if (entry->data != 0) {
            entry->data = *(s32 *)&obj->pad040[0xF8] + entry->data;
            func_0020F250(entry->data);
            if (entry->additional != 0) {
                entry->additional = *(s32 *)&obj->pad040[0xF8] + entry->additional;
            }
            entry->resolved = 0;
        }
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_047", func_001E90B0);

typedef struct Object_001E9280 {
    u8 pad_00[0x14];
    s32 value;
    u8 pad_18[4];
    s32 packed;
} Object_001E9280;

void func_001E9280(void *arg0, s32 arg1) {
    Object_001E9280 *object = arg0;
    s32 packed = object->packed;
    s32 *entry = (s32 *)(packed & 0x03FFFFFF);

    packed >>= 26;
    if (arg1 != 0) {
        entry = (s32 *)((u8 *)entry + packed * 0x10);
        *entry = object->value;
        func_0020F250(*entry);
    }
}

INCLUDE_ASM("asm/nonmatchings/main_047", func_001E92C0);

INCLUDE_ASM("asm/nonmatchings/main_047", func_001E9340);

INCLUDE_ASM("asm/nonmatchings/main_047", func_001EA0F0);

void func_001EA270(void *arg0, s32 arg1) {
    s32 *temp_v1;

    temp_v1 = *(s32 **)((u8 *)arg0 + 0x1C);
    if (arg1 != 0) {
        *temp_v1 = *(s32 *)((u8 *)arg0 + 0x14);
        func_0020F250(*temp_v1);
    }
}

INCLUDE_ASM("asm/nonmatchings/main_047", func_001EA2A0);

INCLUDE_ASM("asm/nonmatchings/main_047", func_001EA410);

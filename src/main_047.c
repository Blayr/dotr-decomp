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

s32 func_001E5240(s32 index) {
    return *(s32 *)&D_0031AB88.padding[index * 4];
}

#ifndef GAME_H
/* The game translation unit already declares this global with its local type. */
typedef struct {
    unsigned char padding[8];
    int field8;
} State_001E5210;

extern State_001E5210 D_0031AB88;
#endif



typedef union {
    __int128 value;
    s32 axis[4];
} Rotation_001E5260;

extern Rotation_001E5260 D_002921C0;

void func_001E5260(s32 arg0, s32 arg1) {
    extern s32 func_001F2920();
    s32 *states = (s32 *)&D_0031AB88;
    s32 x = arg1 >> 8;
    s32 y = arg1 & 0xFF;
    void *card;
    s32 model;
    Rotation_001E5260 rotation;
    f32 position[4];
    f32 offset;

    card = (void *)func_001DF540(x, y);
    rotation = D_002921C0;
    rotation.axis[1] = (arg0 != 0) ? 0 : 0x8000;
    if (card != NULL && *(s32 *)card != 0) {
        func_001E3850(x, y, 1);
        model = *((u8 *)card + 0x46);
        func_00217590(arg0 + 2, func_001F2920(model), 0);
        func_001F2430(model, &rotation);
        func_001F1FD0(model, position);
        position[0] = 0.0f;
        if (arg0 != 0) {
            offset = -80.0f;
        } else {
            offset = 80.0f;
        }
        position[2] = offset;
        func_001F22B0(model, position);
        func_001F30B0(model, 1);
        func_001F29E0(model, 0);
        func_001F2AD0(model, 0);
        func_001F1830(model, 0);
        func_001F1A00(model, 1);
        states[arg0] = arg1;
    }
}

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

typedef union {
    __int128 q;
    f32 f[4];
    s32 i[4];
} Quad_001E60E0;

s32 func_001E6F90(s32, s32, s32, f32, f32);
extern Quad_001E60E0 D_002922B0;
extern Quad_001E60E0 D_002922C0;
extern Quad_001E60E0 D_002922D0;
extern Quad_001E60E0 D_002922E0;
extern Quad_001E60E0 D_002922F0;
extern Quad_001E60E0 D_00292300;

s32 func_001E60E0(s32 arg0, s32 arg1, s32 arg2) {
    s32 i;
    s32 j;
    s32 *entry = (s32 *)&D_0031AB88;
    Quad_001E60E0 scale;

    scale = D_002922B0;
    switch (arg2) {
    case 1: {
        Quad_001E60E0 rotation;
        rotation = D_002922C0;
        i = 0;
        do {
            arg0 = func_001EFA80(arg0, arg1, 0, (s32)&rotation, (s32)&scale, 0, 0);
            rotation.i[1] += 0x4000;
            i++;
        } while (i < 4);
        break;
    }
    case 3: {
        Quad_001E60E0 rotation;
        rotation = D_002922D0;
        i = 0;
        do {
            arg0 = func_001EFA80(arg0, arg1, 0, (s32)&rotation, (s32)&scale, 0, 0);
            rotation.i[1] += 0x8000;
            i++;
        } while (i < 2);
        break;
    }
    case 5: {
        Quad_001E60E0 rotation;
        Quad_001E60E0 position;
        f32 signZ;
        f32 baseX;
        f32 baseZ;
        f32 signX;

        rotation = D_002922E0;
        func_001F1FD0(arg1, &position);
        i = 0;
        do {
            if (i % 2 == 0) {
                signX = -1.0f;
            } else {
                signX = 1.0f;
            }
            if (i >> 1 == 0) {
                signZ = -1.0f;
            } else {
                signZ = 1.0f;
            }
            baseX = 275.0f * signX;
            position.f[0] = baseX * scale.f[0];
            baseZ = 275.0f * signZ;
            position.f[2] = baseZ * scale.f[2];
            arg0 = func_001EFA80(arg0, arg1, (s32)&position, (s32)&rotation, (s32)&scale, 0, 0);
            position.f[0] = scale.f[0] * (baseX - 100.0f * signX);
            position.f[2] = baseZ * scale.f[2];
            arg0 = func_001EFA80(arg0, arg1, (s32)&position, (s32)&rotation, (s32)&scale, 0, 0);
            position.f[0] = baseX * scale.f[0];
            position.f[2] = scale.f[2] * (baseZ - 100.0f * signZ);
            arg0 = func_001EFA80(arg0, arg1, (s32)&position, (s32)&rotation, (s32)&scale, 0, 0);
            i++;
        } while (i < 4);
        break;
    }
    case 6: {
        Quad_001E60E0 rotation;
        Quad_001E60E0 position;
        f32 signX;
        f32 signZ;
        f32 baseX;
        f32 baseZ;
        f32 distance;

        rotation = D_002922F0;
        func_001F1FD0(arg1, &position);
        i = 0;
        do {
            if (i % 2 == 0) {
                signX = -1.0f;
            } else {
                signX = 1.0f;
            }
            if (i >> 1 == 0) {
                signZ = -1.0f;
            } else {
                signZ = 1.0f;
            }
            baseX = 425.0f * signX;
            position.f[0] = baseX * scale.f[0];
            baseZ = 425.0f * signZ;
            position.f[2] = baseZ * scale.f[2];
            arg0 = func_001EFA80(arg0, arg1, (s32)&position, (s32)&rotation, (s32)&scale, 0, 0);
            j = 0;
            do {
                distance = 100.0f * (f32)(j + 1);
                position.f[0] = scale.f[0] * (baseX - distance * signX);
                position.f[2] = baseZ * scale.f[2];
                arg0 = func_001EFA80(arg0, arg1, (s32)&position, 0, (s32)&scale, 0, 0);
                position.f[0] = baseX * scale.f[0];
                position.f[2] = scale.f[2] * (baseZ - distance * signZ);
                arg0 = func_001EFA80(arg0, arg1, (s32)&position, 0, (s32)&scale, 0, 0);
                j++;
            } while (j < 3);
            i++;
        } while (i < 4);
        break;
    }
    default: {
        Quad_001E60E0 rotation;
        rotation = D_00292300;
        arg0 = func_001EFA80(arg0, arg1, 0, (s32)&rotation, (s32)&scale, 0, 0);
        break;
    }
    }
    if (arg2 == 0) {
        arg0 = func_001E6F90(arg0, 7, -1, -13.5f, 400.0f);
        i = 0;
        do {
            s32 value = *entry;
            if (value >= 0) {
                u8 *card = (u8 *)func_001DF540(value >> 8, value & 0xFF);
                if (card != NULL) {
                    arg0 = func_001E6F90(arg0, card[0x46], -1, -13.5f, 400.0f);
                }
            }
            i++;
            entry++;
        } while (i < 2);
    }
    return arg0;
}

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

typedef struct Entry_001E78C0 {
    s16 first;
    s16 second;
    f32 x;
    f32 z;
} Entry_001E78C0;

typedef union Quad_001E78C0 {
    __int128 q;
    f32 f[4];
} Quad_001E78C0;

s32 func_001E78C0(s32 arg0) {
    extern Quad_001E78C0 D_00292470;
    extern Entry_001E78C0 D_002CF750[];
    Quad_001E78C0 position;
    s32 i;
    s32 firstId;
    s32 secondId;
    s32 id;

    if (func_001F3130(0x22) != 0) {
        if (D_00292468 == 2) {
            for (i = 0; D_002CF750[i].second >= 0; i++) {
                secondId = D_002CF750[i].second + 0x22;
                firstId = D_002CF750[i].first + 0x22;
                position = D_00292470;
                position.f[0] = D_002CF750[i].x;
                position.f[2] = D_002CF750[i].z;
                if (D_002CF750[i].first >= 0 && func_001F1370(firstId) != 0) {
                    arg0 = func_001EFA80(arg0, firstId, (s32) &position, 0, 0, 0, 0);
                }
                if (D_002CF750[i].second >= 0 && func_001F1370(secondId) != 0) {
                    arg0 = func_001EFA80(arg0, secondId, (s32) &position, 0, 0, 0, 0);
                }
            }
        } else {
            for (i = 0; i < 0x28; i++) {
                id = i + 0x22;
                if (func_001F1370(id) != 0) {
                    arg0 = func_001EFA80(arg0, id, 0, 0, 0, 0, 0);
                }
            }
        }
    }
    return arg0;
}

void func_001E7A50(void) {

}

typedef struct Entry_001E7A60 {
    u8 padding[0x68];
    s32 id : 27;
    u32 flags : 5;
    u32 padding_6C;
} Entry_001E7A60;

extern Entry_001E7A60 D_0031AD00[];
extern s32 D_0031BB00;
extern s32 D_0031BB18;
extern u8 D_002CF9D0[];
extern u8 D_002CF9D5[];

s32 func_001E7A60(void) {
    extern u8 *func_00197548();
    s32 i;
    Entry_001E7A60 *entry;
    s32 j;

    for (i = 0; i < 0x54; i++) {
        D_0031ABB0[i] = NULL;
    }
    entry = D_0031AD00;
    for (j = 0; j < 0x20; j++) {
        entry->id = -1;
        entry++;
    }
    D_0031BB00 = 0;
    if (func_00197548(D_002CF9D0) != NULL || func_00197548(D_002CF9D5) != NULL) {
        D_0031BB18 = 1;
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_047", func_001E7B20);

typedef struct {
    s8 bit0 : 1;
    s8 bit1 : 1;
    s8 bits2_4 : 3;
    s8 bit5 : 1;
    s8 bits6_7 : 2;
} Flags_001E7D00;


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

typedef struct {
    s8 unused0 : 2;
    s8 loading : 1;
    s8 busy : 1;
    s8 unused4 : 4;
} Flags_001E8780;

typedef struct {
    Obj_0031ABB0 shared;
    u8 pad1E4[0x1F2 - sizeof(Obj_0031ABB0)];
    s8 state;
    s8 kind;
    s16 value;
    u8 pad1F6[0x16];
    s8 unused0 : 2;
    s8 loading : 1;
    s8 busy : 1;
    s8 unused4 : 4;
} Fields_001E8780;

typedef struct {
    s32 values[3];
} Table_001E8780;

extern s32 D_00292480[];
extern s32 D_00292A50[];
extern s32 D_00292A54[];
extern Table_001E8780 D_00292F20;
extern Table_001E8780 D_00292F30;
extern u16 D_002CF910[];
extern u8 D_002CF9D5[];
extern u8 D_002CF9DD[];
extern u8 D_002CF9F0[];
extern u8 D_002CF9F5[];
extern u8 D_002CFA0A[];
extern u8 D_002CFA17[];
extern u8 D_002CFA1D[];
extern s32 D_0031BB18;

s32 func_001E8780(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 format[128];
    u8 path[128];
    Table_001E8780 slots;
    Table_001E8780 starts;
    Fields_001E8780 *obj;
    s32 slot;
    s32 base;
    u8 *root;
    s32 value;
    s32 id;
    s32 group;
    s32 index;
    s32 start;
    s32 size;
    s32 card;
    s32 leader;
    s32 kind;
    s32 tableIndex;

    extern void func_0019B648();

    value = arg2;
    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    obj = (Fields_001E8780 *)D_0031ABB0[arg0];
    if (obj == NULL) {
        return 0;
    }
    if (obj->busy) {
        while (obj->busy) {
            func_001FF420();
        }
    }
    obj->state = -1;
    if (arg1 >= 0) {
        obj->kind = arg1;
    }
    if (value >= 0) {
        obj->value = value;
    } else {
        value = obj->value;
    }
    obj->loading = 0;
    if (value < 0 || value >= D_002CF910[obj->kind]) {
        return 0;
    }
    base = D_00292480[obj->kind];
    if (arg3 != 0 && D_0031BB18 != 0) {
        if (func_00197548((s32)D_002CF9D5) != NULL) {
            root = func_001FFF90((s32)D_002CF9F0);
            kind = obj->kind;
            card = 0;
            leader = 0;
            if (kind == 4) {
                goto card_kind;
            }
            if (kind == 5) {
                goto card_kind;
            }
            if (kind == 6) {
            card_kind:
                card = 1;
            }
            if (kind == 1) {
                leader = 1;
            }
            if (card) {
                if (value == 0x2E1) {
                    id = 0x29F;
                } else {
                    id = func_001DE130(value);
                }
                if (id < 0x2AB) {
                    slot = obj->kind - 4;
                    slots = D_00292F20;
                    starts = D_00292F30;
                    func_0019B648(path, D_002CF9F5, root);
                    if (func_001F0060(arg0, path, starts.values[slot] + ((arg0 - slots.values[slot]) << 20), 0x100000, id << 20, 0x100000)) {
                        return 1;
                    }
                }
                return 0;
            } else if (leader) {
                group = value / 100;
                index = value % 100;
                if (group >= 0 && group < 2 && index >= 0 && index < 21) {
                    tableIndex = index + (group != 0 ? 0x3C : 0x27);
                    start = D_00292A50[tableIndex];
                    size = D_00292A54[tableIndex] - start;
                    func_0019B648(path, D_002CF9DD, root);
                    if (func_001F0060(arg0, path, (s32)((s64)group * 0xA000 + 0x010AA800), size, start, size)) {
                        return 1;
                    }
                }
                return 0;
            }
        }
        func_0019B648(format, D_002CFA0A, func_001FFF90((s32)D_002CFA17), base, base);
        func_0019B648(path, format, value, value);
        if (func_001F0060(arg0, path, 0, -1, 0, -1) == 0) {
            return 0;
        }
    } else {
        func_0019B648(format, D_002CFA1D, func_001FFF90((s32)D_002CFA17), base, base);
        func_0019B648(path, format, value, value);
        if (func_001EFF70(arg0, path) == 0) {
            return 0;
        }
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_047", func_001E8BF0);

typedef struct {
    u8 pad0[0xC];
    u16 count;
} Res_001E8E90;

typedef struct {
    u8 pad0[4];
    u32 flags;
} Sub_001E8E90;

typedef struct {
    u8 pad000[0x138];
    Sub_001E8E90 *sub;
    u8 pad13C[0x30];
    Res_001E8E90 *res0;
    Res_001E8E90 *res1;
    u8 pad174[0x8E];
    u16 cur;
    u16 last;
} Obj_001E8E90;

typedef struct {
    u8 pad0[0x14];
    Res_001E8E90 *res;
    u8 pad18[4];
    u32 bits;
} Req_001E8E90;

void func_001E8E90(void *arg0, s32 arg1) {
    Req_001E8E90 *req = arg0;
    s32 second;
    Obj_001E8E90 *obj;
    s32 index;

    index = req->bits & 0x7F;
    second = req->bits & 0x80;
    if (index < 0 || index >= 0x54) {
        return;
    }
    obj = (Obj_001E8E90 *)D_0031ABB0[index];
    if (obj == NULL) {
        return;
    }
    if (obj->sub == NULL) {
        func_00217B50((s32)req->res);
        arg1 = 0;
    }
    if (arg1 == 0) {
        if (second) {
            obj->res1 = NULL;
        } else {
            obj->res0 = NULL;
        }
        return;
    }
    if (second) {
        obj->res1 = req->res;
        obj->sub->flags &= ~0x100000;
    } else {
        obj->res0 = req->res;
        obj->cur = obj->last = obj->res0->count - 1;
        obj->sub->flags &= ~0x80000;
    }
}

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

typedef struct Slot_001E92C0 {
    s32 key;
    s32 unk04;
    u8 *data;
    s32 unk0C;
} Slot_001E92C0;

typedef struct State_001E92C0 {
    u8 unk00[8];
    signed int length : 31;
    unsigned int flag : 1;
    u8 unk0C[8];
    u8 *data;
    u8 unk18[4];
    s32 packed;
} State_001E92C0;

u8 *func_001E9340(s32, u8 *);

void func_001E92C0(void *arg0, s32 arg1) {
    void func_00217B50(u8 *);
    Slot_001E92C0 *slot;
    u8 *buffer;
    s32 index;
    State_001E92C0 *state = arg0;

    slot = (Slot_001E92C0 *)(state->packed & 0x3FFFFFF);
    index = state->packed >> 26;
    if (arg1 != 0) {
        slot += index;
        slot->data = state->data;
        buffer = slot->data;
        if (buffer != NULL) {
            buffer[state->length - 1] = 0;
            slot->data = func_001E9340(slot->key, buffer);
            func_00217B50(buffer);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/main_047", func_001E9340);

s32 func_001EA0F0(s32 arg0) {
    extern u8 D_002CFA17[];
    extern u8 D_002CFB4F[];
    extern u8 D_002CFB64[];
    extern s32 D_00292480[];
    extern void func_0019B648();
    extern s32 func_001FEC70();
    u8 buf1[0x80];
    u8 buf2[0x80];
    s32 s0;
    s32 s1;
    u8 *obj;
    s32 s4;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    obj = (u8 *)D_0031ABB0[arg0];
    if (obj == NULL) {
        return 0;
    }
    s0 = (s32)func_001FFF90((s32)D_002CFA17);
    s1 = *(s16 *)(obj + 0x1F4);
    if (*(s32 *)(obj + 0x138) == 0) {
        return 1;
    }
    s4 = D_00292480[*(s8 *)(obj + 0x1F3)];
    *(s32 *)(obj + 0x140) = 0;
    func_0019B648(buf1, D_002CFB4F, s0, s4);
    func_0019B648(buf2, buf1, s1, s1);
    func_001FEC70(arg0, buf2, 0, -1, func_001EA270, (s32)(obj + 0x140));
    func_0019B648(buf1, D_002CFB64, s0, s4);
    s0 = 0;
    do {
        *(s32 *)(obj + 0x144) = 0;
        func_0019B648(buf2, buf1, s1, s1, s0);
        func_001FEC70(arg0, buf2, 0, -1, func_001EA270, (s32)(obj + 0x144));
        s0 += 1;
        obj += 4;
    } while (s0 < 8);
    return 1;
}

void func_001EA270(void *arg0, s32 arg1) {
    s32 *temp_v1;

    temp_v1 = *(s32 **)((u8 *)arg0 + 0x1C);
    if (arg1 != 0) {
        *temp_v1 = *(s32 *)((u8 *)arg0 + 0x14);
        func_0020F250(*temp_v1);
    }
}

typedef struct {
    s32 id;
    s32 unused;
    s32 enabled;
    s32 count;
} Entry_001EA2A0;

typedef struct {
    u8 unused[0x28];
    s32 offset;
    s32 present;
} Header_001EA2A0;

s32 func_001EA410(s32, s32, s32, void *);

s32 func_001EA2A0(s32 current, s32 object, void *data, s32 *size) {
    extern s32 func_00202E00();
    s32 cursor;
    s32 count;
    s32 index;
    Entry_001EA2A0 *entry;
    s32 base;
    s32 entry_size;
    s32 *table;
    Header_001EA2A0 *header;

    if (size != NULL) {
        *size = 0;
    }
    if (data == NULL) {
        return current;
    }
    header = (Header_001EA2A0 *)((u8 *)data + 0x10);
    if (header->present == 0) {
        return current;
    }
    table = (s32 *)((u8 *)data + header->offset);
    count = *table;
    entry = (Entry_001EA2A0 *)((u8 *)table + 0x10);
    base = cursor = func_00209E50();
    cursor += func_00202E00(cursor, 2);
    for (index = 0; index < count; index++, entry++) {
        if (entry->id != 0) {
            current = func_00202FB0(current, entry->id, cursor, (s32)&entry_size);
            if (entry->enabled != 0 && func_001F3360(object) == 0 && func_001F3440(object) == 0) {
                current = func_001EA410(current, object, cursor, entry);
                entry->count++;
            }
            cursor += entry_size;
        }
    }
    if (size != NULL) {
        *size = cursor - base;
    }
    return func_0020F290(current);
}

INCLUDE_ASM("asm/nonmatchings/main_047", func_001EA410);

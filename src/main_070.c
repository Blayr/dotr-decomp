#include "common.h"

s32 func_00245150(void *arg0) {
    return *(s32 *)((u8 *)arg0 + 0xA8);
}

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

s32 func_00245630(s32 arg0, s32 arg1, s32 arg2, s32 arg3,
                  void *arg4, s32 arg5, s32 arg6, s32 arg7) {
    s32 temp_fp;
    s32 temp_s0;

    temp_s0 = arg5 + arg7;
    if ((arg1 + arg3) < temp_s0) {
        return 0;
    }
    if (arg5 >= arg1) {
        func_00198790((u8 *)arg0, arg4, arg1);
        func_00198790((u8 *)arg2, (u8 *)arg4 + arg1, arg5 - arg1);
        func_00198790(((u8 *)arg2 + arg5) - arg1, (u8 *)arg6, arg7);
    } else {
        temp_fp = arg1 - arg5;
        if (arg7 >= temp_fp) {
            func_00198790((u8 *)arg0, arg4, arg5);
            func_00198790((u8 *)arg0 + arg5, (u8 *)arg6, temp_fp);
            func_00198790((u8 *)arg2, ((u8 *)arg6 + arg1) - arg5, arg7 - temp_fp);
        } else {
            func_00198790((u8 *)arg0, arg4, arg5);
            func_00198790((u8 *)arg0 + arg5, (u8 *)arg6, arg7);
        }
    }
    return temp_s0;
}

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

void func_002457D0(void *arg0) {
    *(s32 *)((u8 *)arg0 + 0xC) = 0;
    *(s32 *)((u8 *)arg0 + 0x8) = 0;
}

typedef struct {
    u8 pad[0xC];
    s32 field_C;
    s32 field_10;
} Fields_002457E0;

s32 func_002457E0(void *arg0) {
    return ((Fields_002457E0 *)arg0)->field_C == ((Fields_002457E0 *)arg0)->field_10;
}

typedef struct {
    s32 unk0;
    u8 *data;
    s32 index;
    s32 count;
    s32 capacity;
} Queue_00245800;

void func_001843E0(void);
void func_00184428(void);

void func_00245800(void *arg0) {
    Queue_00245800 *queue = (Queue_00245800 *)arg0;

    func_001843E0();
    *(s32 *)(queue->data + queue->index * 0x4CE40) = 2;
    queue->count++;
    queue->index = (queue->index + 1) % queue->capacity;
    func_00184428();
}

typedef struct State_00245890 {
    s32 base;
    s32 unk4;
    s32 index;
    s32 current;
    s32 end;
} State_00245890;

static inline u8 empty_00245890(void *arg0) {
    State_00245890 *state = arg0;

    return state->current == state->end;
}

s32 func_00245890(void *arg0) {
    State_00245890 *state = arg0;

    if (empty_00245890(state)) {
        return 0;
    }
    return state->base + (state->index * 0x195000);
}

INCLUDE_ASM("asm/nonmatchings/main_070", func_002458E0);

typedef struct Counter_00245960 {
    u8 pad[0xC];
    volatile s32 count;
} Counter_00245960;

void func_00245960(void *arg0) {
    Counter_00245960 *counter = arg0;

    if (counter->count > 0) {
        counter->count--;
    }
}

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

s32 func_00248AF0(s32 arg0, s32 arg1, s32 arg2) {
    s32 kind;
    extern s32 func_001E1030();

    kind = func_001E1030(arg0, arg1);
    if (func_00248370(arg0, arg1, arg2) != 0) {
        switch (D_0029D1F0[arg2]) {
        case 4:
            switch (D_0029CF32[arg2]) {
            case 6:
                return arg2 | 0x40444000;
            case 7:
                return arg2 | 0x406AC000;
            case 8:
                switch (kind) {
                case 0x156:
                    return arg2 | 0x407A0000;
                case 7:
                    return arg2 | 0x407D4000;
                }
                break;
            case 9:
                switch (kind) {
                case 0x10:
                    return arg2 | (((func_0019A5C8() % 5 + 0xD) << 14) | 0x40000000);
                case 0x11:
                    return arg2 | (((func_0019A5C8() % 5 + 0xD) << 14) | 0x40000000);
                case 0xA7:
                    return arg2 | (((func_0019A5C8() % 15 + 0xD1) << 14) | 0x40000000);
                case 0x14C:
                    return arg2 | (((func_0019A5C8() % 32 + 0x65) << 14) | 0x40000000);
                case 0x17B:
                    return arg2 | (((u16)func_002494D0() << 14) | 0x40000000);
                }
                break;
            }
            break;
        case 0:
            switch (D_0029CF32[arg2]) {
            case 0:
                return arg2 | 0x864000;
            default:
                return arg2 | 0x860000;
            }
        case 3:
            return arg2 | 0x874000;
        case 2:
            return arg2 | 0x878000;
        case 1:
            switch (D_0029CF32[arg2]) {
            case 5:
                return arg2 | 0x870000;
            default:
                return arg2 | 0x860000;
            }
        default:
            return arg2 | 0x860000;
        }
    } else {
        return 0x3E7;
    }
    return 0x3E7;
}

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

typedef struct Entry_00248EA0 {
    u32 unk0;
    u32 value;
} Entry_00248EA0;


s32 func_00248EA0(void) {
    s32 index;
    s32 total;
    s32 count;
    s32 id;
    u32 kind;
    Entry_00248EA0 *entry;

    total = 0;
    count = func_00266DF0(0x34);
    for (index = 0; index < count; index++) {
            id = func_00266C70(0x34, index);
            if (id >= 0) {
                entry = func_00250740(id >> 8, id & 0xFF, 2);
                kind = entry->value >> 16;
                switch (kind) {
                case 0:
                    total += *(u16 *)((u8 *)entry + 4);
                    break;
                case 1:
                    total -= *(u16 *)((u8 *)entry + 4);
                    break;
                }
            }
    }
    return total;
}

s32 func_00248F60(s32 arg0, s32 arg1) {
    s32 temp_a2;

    temp_a2 = arg1 - 0x2F0;
    if ((D_0029D580[arg0 * 7 + (temp_a2 >> 3)] >> (temp_a2 % 8)) & 1) {
        return func_00249040(arg0, arg1);
    }
    return -1;
}

s32 func_00248FD0(s32 arg0, s32 arg1, s32 arg2) {
    extern s32 func_001E1030();

    if (func_00248370(arg0, arg1, arg2) != 0) {
        return func_00249040(func_001E1030(arg0, arg1), arg2);
    }
    return -1;
}

s32 func_00249040(s32 arg0, s32 arg1) {
    s32 result;

    switch (D_0029CF32[arg1]) {
    case 6:
        result = 0x111;
        break;
    case 7:
        result = 0x1AB;
        break;
    case 8:
        switch (arg0) {
        case 0x156:
            result = 0x1E8;
            break;
        case 7:
            result = 0x1F5;
            break;
        default:
            result = -1;
            break;
        }
        break;
    case 9:
        switch (arg0) {
        case 0x10:
            result = func_0019A5C8() % 5 + 0xD;
            break;
        case 0x11:
            result = func_0019A5C8() % 5 + 0xD;
            break;
        case 0xA7:
            result = func_0019A5C8() % 15 + 0xD1;
            break;
        case 0x14C:
            result = func_0019A5C8() % 32 + 0x65;
            break;
        case 0x17B:
            result = (u16)func_002494D0();
            break;
        default:
            result = -1;
            break;
        }
        break;
    default:
        result = arg0 | 0x10000;
        break;
    }
    return result;
}

s32 func_00249200(s32 arg0) {
    u8 temp_v1;
    s32 result;

    temp_v1 = D_0029D1F0[arg0];
    switch (temp_v1) {
    case 0:
        switch (D_0029CF32[arg0]) {
        case 0:
            result = 0x219;
            break;
        default:
            result = 0x218;
            break;
        }
        break;
    case 3:
        result = 0x21D;
        break;
    case 2:
        result = 0x21E;
        break;
    case 1:
        switch (D_0029CF32[arg0]) {
        case 5:
            result = 0x21C;
            break;
        default:
            result = 0x218;
            break;
        }
        break;
    default:
        result = 0x218;
        break;
    }
    return result;
}

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

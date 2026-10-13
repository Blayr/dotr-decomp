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

typedef struct Buffer_002458E0 {
    s32 unk0;
    s32 base;
    s32 index;
    volatile s32 count;
    s32 capacity;
} Buffer_002458E0;

static inline u8 is_empty_002458E0(void *arg0) {
    return ((Buffer_002458E0 *)arg0)->count == 0;
}

s32 func_002458E0(void *arg0) {
    s32 capacity;
    Buffer_002458E0 *buffer = arg0;

    if (is_empty_002458E0(arg0)) {
        return 0;
    }
    capacity = buffer->capacity;
    return buffer->base + ((capacity + (buffer->index - buffer->count)) % capacity) * 0x4CE40;
}

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

typedef struct Name_002459D0 {
    u8 text[8];
} Name_002459D0;

void func_002459D0(u8 arg0, u8 arg1, void *arg2) {
    *(Name_002459D0 *)arg2 = ((Name_002459D0 **)D_0029D488[arg0])[1][arg1];
}

typedef struct Record_00245A30 {
    s16 x;
    s16 y;
    s16 width;
    s16 height;
} Record_00245A30;

typedef struct Data_00245A30 {
    s32 unk0;
    u8 (*indices)[8];
    Record_00245A30 *records;
} Data_00245A30;

void func_00245A30(s32 arg0, s32 arg1, s32 arg2, void *arg3) {
    extern struct Quad_00245980 **D_0029D488[];
    u8 var_a1;
    u8 temp_a0;
    Record_00245A30 *records;
    s32 var_t1;

    var_t1 = 0;
    var_a1 = ((Data_00245A30 *)D_0029D488[arg0 & 0xFF])->indices[arg1 & 0xFF][1];
    if (arg2 != 0) {
        records = ((Data_00245A30 *)D_0029D488[arg0 & 0xFF])->records;
        while (var_t1 != (arg2 & 0xFF)) {
            temp_a0 = *(u8 *)&records[var_a1 & 0xFF];
            if (temp_a0 == 0 || temp_a0 == 0xFF) {
                break;
            }
            var_t1 += 1;
            var_a1 = temp_a0 & 0xFF;
        }
    }
    *(Record_00245A30 *)arg3 = ((Data_00245A30 *)D_0029D488[arg0 & 0xFF])->records[var_a1 & 0xFF];
}

typedef struct Record_00245AE0 {
    s16 x;
    s16 y;
    s16 width;
    s16 height;
} Record_00245AE0;

typedef struct Data_00245AE0 {
    s32 unk0;
    u8 (*indices)[8];
    union {
        Record_00245AE0 *records;
        u8 (*links)[8];
    } u;
} Data_00245AE0;

void func_00245AE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, void *arg4) {
    extern struct Quad_00245980 **D_0029D488[];
    Record_00245AE0 *table;
    u8 var_a1;
    u8 temp_a0;
    Record_00245AE0 *records;
    s32 var_t1;
    s32 count;

    var_t1 = 0;
    var_a1 = ((Data_00245AE0 *)D_0029D488[arg0 & 0xFF])->indices[arg1 & 0xFF][1];
    if (arg2 != 0) {
        records = ((Data_00245AE0 *)D_0029D488[arg0 & 0xFF])->u.records;
        while (var_t1 != (arg2 & 0xFF)) {
            temp_a0 = *(u8 *)&records[var_a1 & 0xFF];
            if (temp_a0 == 0 || temp_a0 == 0xFF) {
                break;
            }
            var_t1 += 1;
            var_a1 = temp_a0 & 0xFF;
        }
    }
    var_t1 = ((Data_00245AE0 *)D_0029D488[arg0 & 0xFF])->u.links[var_a1 & 0xFF][6];
    table = ((Data_00245AE0 *)D_0029D488[arg0 & 0xFF])->u.records;
    count = 0;
    if (arg3 != 0) {
        while (count != (arg3 & 0xFF)) {
            temp_a0 = *(u8 *)&table[var_t1 & 0xFF];
            if (temp_a0 == 0 || temp_a0 == 0xFF) {
                break;
            }
            count += 1;
            var_t1 = temp_a0 & 0xFF;
        }
    }
    *(Record_00245AE0 *)arg4 = table[var_t1 & 0xFF];
}

typedef struct Request_00245BE0 {
    u8 slot;
    u8 a;
    u8 b;
    u8 c;
    u16 d;
    u16 e;
} Request_00245BE0;

typedef struct Slot_00245BE0 {
    s32 value;
    u8 a;
    u8 b;
    u8 c;
    u8 pad7[4];
    u8 x[16];
    u8 y[16];
    u8 pad2B;
    u16 d;
    u16 e;
    u8 pad30[4];
} Slot_00245BE0;

s32 func_00245BE0(void *arg0) {
    Request_00245BE0 *req = arg0;
    Slot_00245BE0 *entry;
    s32 i;
    extern Slot_00245BE0 D_00350FD0[];

    if (req->slot == 0xFF) {
        for (i = 0; i < 8; i++) {
            if (D_00350FD0[i].value == 0) {
                break;
            }
        }
        if (i == 8) {
            return 0;
        }
        req->slot = i;
        D_00350FD0[req->slot].value = 1;
        D_00350FD0[req->slot].b = 0xFF;
    }
    entry = &D_00350FD0[req->slot];
    if (entry->value == 0) {
        return 0;
    }
    if (entry->b != req->b) {
        for (i = 0; i < 16; i++) {
            D_00350FD0[req->slot].y[i] = 0;
            D_00350FD0[req->slot].x[i] = 0;
        }
    }
    entry->a = req->a;
    entry->b = req->b;
    entry->c = req->c;
    entry->d = req->d;
    entry->e = req->e;
    return 1;
}

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

typedef struct {
    s32 value;
    u8 kind;
    u8 pad5[0x2B];
    s32 handle;
} Entry_00246340;

s32 func_00246340(s32 arg0) {
    extern s32 D_00350FC0;
    extern s32 func_002460F0();
    extern s32 func_00202E00();
    Entry_00246340 *entry;
    s32 i;
    s32 base;

    D_00350FC0 = arg0;
    for (i = 0; i < 8; i++) {
        if (((Entry_00246340 *)D_00350FD0)[i].value != 0) {
            ((Entry_00246340 *)D_00350FD0)[i].handle = func_00202BF0(7, ((Entry_00246340 *)D_00350FD0)[i].kind);
        }
    }
    base = func_00209E50();
    base += func_00202E00(base, 2);
    D_00350FC0 = func_00202B00(D_00350FC0, 7, base, NULL);
    D_00350FC0 = func_0020F290(D_00350FC0);
    func_00202D60(7, -1);
    entry = (Entry_00246340 *)D_00350FD0;
    for (i = 0; i < 8; i++, entry++) {
        if (entry->value != 0 && entry->handle != 0) {
            func_002460F0(entry);
        }
    }
    return D_00350FC0;
}

void func_00246450(s32 arg0) {
    extern s32 D_00350FC0;
    s32 i;
    Entry_00245D80 *entry;

    D_00351170 = arg0;
    entry = D_00350FD0;
    i = 0;
    do {
        i += 1;
        entry->value = 0;
        entry++;
    } while (i < 8);
    D_00350FC0 = 0;
}

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

s32 func_001E1E70(s32, s32, s32, s32);

typedef struct Flags_00246810 {
    u8 bit0 : 1;
    u8 bit1 : 1;
    u8 bit2 : 1;
    u8 bit3 : 1;
    u8 bit4 : 1;
    u8 bit5 : 1;
    u8 bit6 : 1;
    u8 bit7 : 1;
} Flags_00246810;

typedef struct Status_00246810 {
    Flags_00246810 mode;
    s32 value1;
    s32 value2;
    s32 value3;
    Flags_00246810 flags;
} Status_00246810;

static inline s32 encode_00246810(s32 value) {
    return ((value < 0 ? 1 : 0) << 15) | (value >= 0 ? value : -value);
}

s32 func_00246810(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, void *arg6) {
    extern s32 func_001E08F0();
    extern s32 func_001E1030();
    extern s32 func_001E1580();
    Status_00246810 status;
    Status_00246810 *p = &status;
    s32 *out = arg6;
    s32 sp120;
    s32 sp138;
    s32 sp13C;
    s32 sp140;
    s32 sp144;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_s0;
    s32 temp_s0_10;
    s32 temp_s0_11;
    s32 temp_s0_2;
    s32 temp_s0_3;
    s32 temp_s0_4;
    s32 temp_s0_5;
    s32 temp_s0_6;
    s32 temp_s0_7;
    s32 temp_s0_8;
    s32 temp_s0_9;
    s32 temp_s1;
    s32 temp_s1_2;
    s32 temp_s1_3;
    s32 temp_s5;
    s32 temp_s5_2;
    s32 temp_v0_20;
    s32 temp_v0_21;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v0_7;
    s32 var_fp;
    s32 var_s7;

    p->value1 = 0;
    p->value2 = 0;
    p->value3 = 0;
    p->flags.bit0 = 0;
    p->flags.bit1 = 0;
    p->flags.bit2 = 0;
    p->flags.bit3 = 0;
    p->flags.bit4 = 0;
    p->mode.bit1 = 0;
    p->mode.bit2 = 0;
    p->mode.bit0 = 1;
    p->flags.bit5 = 0;
    p->flags.bit6 = 0;
    temp_s1 = func_001E0700(arg0, arg1) >> 5;
    temp_a0 = func_001E0700(arg2, arg3) >> 5;
    sp120 = 0;
    var_fp = 0;
    var_s7 = 0;
    if ((temp_s1 == 0) && (temp_a0 == 0)) {
        if (arg1 == 0) {
            temp_s1_2 = func_00261F20(arg0, arg1, arg2, arg3, p);
            temp_s5 = func_002660E0(func_001DF540(arg2, arg3), arg4, arg5, 1);
            temp_s5_2 = p->value2 + func_001E0290(arg2, arg3, 0);
            temp_s5_2 = func_002508D0(temp_s5_2 + temp_s5);
            func_001E0450(arg2, arg3, 0, p->value2);
            func_001E0570(arg2, arg3, 0, p->value2);
            p->value2 = encode_00246810(p->value2);
            if (func_00271740(6, arg0) != 0) {
                out[0] = 0x5D;
                out[1] = (s32) ((p->value2 << 0x10) | ((arg2 << 8) | arg3));
                out[2] = arg0;
                out[3] = (((p->flags.bit6 << 1) | ((temp_s1_2 >> 0x18) & 1)) << 0x16) | ((temp_s5_2 >> 1) | (((p->flags.bit5 << 1) | ((temp_s1_2 >> 0x10) & 1)) << 0x14));
            } else {
                out[0] = 0x5D;
                out[1] = (s32) ((arg2 << 8) | arg3);
                out[2] = arg0;
                out[3] = (((p->flags.bit6 << 1) | ((temp_s1_2 >> 0x18) & 1)) << 0x16) | (temp_s5_2 | (((p->flags.bit5 << 1) | ((temp_s1_2 >> 0x10) & 1)) << 0x14));
            }
            return 1;
        }
        temp_s1_3 = func_001E0830(arg2, arg3);
        temp_v0_4 = func_0024EA70(temp_s1_3, func_001E0830(arg0, arg1));
        switch (temp_v0_4) {                        /* switch 1; irregular */
        case 1:                                     /* switch 1 */
            if (func_001E1580(arg0, arg1) == 0) {
                var_fp = 1;
            }
            break;
        case -1:                                    /* switch 1 */
            if (func_001E1580(arg2, arg3) == 0) {
                var_s7 = 1;
            }
            break;
        }
        temp_v0_5 = func_00261F20(arg0, arg1, arg2, arg3, p);
        if ((temp_v0_5 & 0xFF) == 1) {
            temp_a0_2 = (temp_v0_5 >> 0x18) & 1;
            if ((temp_a0_2 == 1) && (((temp_v0_5 >> 0x10) & 1) == 1)) {
                out[0] = 0x5E;
                out[1] = (s32) ((arg2 << 8) | arg3);
                out[2] = (s32) ((arg0 << 8) | arg1);
                out[3] = (s32) ((p->flags.bit2 << 0x1B) | ((var_s7 << 0x1A) | ((var_fp << 0x19) | ((((p->flags.bit6 << 1) | 1) << 0x16) | ((((p->flags.bit5 << 1) | 1) << 0x14) | 0xCFFFF)))) | 0x10000000);
                temp_s0 = func_001E1030(arg0, arg1);
                                func_00215B10(arg0, temp_s0, 0, (func_001E08F0(arg2, arg3, 0) + 2) * 2);
                temp_s0_2 = func_001E1030(arg2, arg3);
                                func_00215B10(arg2, temp_s0_2, 0, (func_001E08F0(arg0, arg1, 0) + 2) * 2);
                return 1;
            }
            if (temp_a0_2 == 1) {
                out[0] = 0x5E;
                out[1] = (s32) ((arg2 << 8) | arg3);
                out[2] = (s32) ((arg0 << 8) | arg1);
                out[3] = (s32) ((p->flags.bit2 << 0x1B) | ((var_s7 << 0x1A) | ((var_fp << 0x19) | ((((p->flags.bit6 << 1) | 1) << 0x16) | (((p->flags.bit5 << 1) << 0x14) | 0x8FFFF)))) | 0x10000000);
                temp_s0_3 = func_001E1030(arg0, arg1);
                                func_00215B10(arg0, temp_s0_3, 0, (func_001E08F0(arg2, arg3, 0) + 2) * 2);
                return 1;
            }
            if (((temp_v0_5 >> 0x10) & 1) == 1) {
                out[0] = 0x5E;
                out[1] = (s32) ((arg2 << 8) | arg3);
                out[2] = (s32) ((arg0 << 8) | arg1);
                out[3] = (s32) ((p->flags.bit2 << 0x1B) | ((var_s7 << 0x1A) | ((var_fp << 0x19) | ((p->flags.bit6 << 0x17) | ((((p->flags.bit5 << 1) | 1) << 0x14) | 0x4FFFF)))));
                temp_s0_4 = func_001E1030(arg2, arg3);
                                func_00215B10(arg2, temp_s0_4, 0, (func_001E08F0(arg0, arg1, 0) + 2) * 2);
                return 1;
            }

        }
        temp_v0_7 = func_001E2100(arg0, arg1, 3);
        switch (temp_v0_7) {                        /* switch 2; irregular */
        case 1:                                     /* switch 2 */
            if (p->flags.bit3 == 1) {
                func_001E0450(arg0, arg1, 4, 0);
                func_001E0570(arg0, arg1, 4, 0);
                sp13C = func_002508D0(func_001E0370(arg0, arg1, 0) + func_002660E0(func_001DF540(arg0, arg1), arg4, arg5, 0));
            } else {
                sp13C = func_002508D0(p->value1 + func_001E0370(arg0, arg1, 0) + func_002660E0(func_001DF540(arg0, arg1), arg4, arg5, 0));
                func_001E0450(arg0, arg1, 0, p->value1);
                func_001E0570(arg0, arg1, 0, p->value1);
                p->value1 = encode_00246810(p->value1);
            }
            if (p->flags.bit4 == 1) {
                func_001E0450(arg2, arg3, 4, 0);
                func_001E0570(arg2, arg3, 4, 0);
                sp138 = func_002508D0(func_001E0290(arg2, arg3, 0) + func_002660E0(func_001DF540(arg2, arg3), arg4, arg5, 1));
            } else {
                sp138 = func_002508D0(p->value2 + func_001E0290(arg2, arg3, 0) + func_002660E0(func_001DF540(arg2, arg3), arg4, arg5, 1));
                func_001E0450(arg2, arg3, 0, p->value2);
                func_001E0570(arg2, arg3, 0, p->value2);
                p->value2 = encode_00246810(p->value2);
            }
            if (sp13C > sp138) {

                if (p->flags.bit1 == 0) {
                    sp120 += sp13C - sp138;

                }
                out[0] = 0x5E;
                out[1] = (s32) ((p->value2 << 0x10) | ((arg2 << 8) | arg3));
                out[2] = (s32) ((p->value1 << 0x10) | ((arg0 << 8) | arg1));
                out[3] = (s32) ((p->flags.bit2 << 0x1B) | ((var_s7 << 0x1A) | ((var_fp << 0x19) | ((((p->flags.bit6 << 1) | ((temp_v0_5 >> 0x18) & 1)) << 0x16) | (sp120 | 0x20000 | (((p->flags.bit5 << 1) | ((temp_v0_5 >> 0x10) & 1)) << 0x14)) | 0x01000000))) | 0x10000000);
                return 1;
            }
            if (sp13C == sp138) {
                out[0] = 0x5E;
                out[1] = (s32) ((p->value2 << 0x10) | ((arg2 << 8) | arg3));
                out[2] = (s32) ((p->value1 << 0x10) | ((arg0 << 8) | arg1));
                out[3] = (s32) ((p->flags.bit2 << 0x1B) | ((var_s7 << 0x1A) | ((var_fp << 0x19) | ((((p->flags.bit6 << 1) | ((temp_v0_5 >> 0x18) & 1)) << 0x16) | (((p->flags.bit5 << 1) | ((temp_v0_5 >> 0x10) & 1)) << 0x14) | 0x01000000))));
                return 1;
            }
            if (sp13C < sp138) {
                out[0] = 0x5E;
                out[1] = (s32) ((p->value2 << 0x10) | ((arg2 << 8) | arg3));
                out[2] = (s32) ((p->value1 << 0x10) | ((arg0 << 8) | arg1));
                out[3] = (s32) ((p->flags.bit2 << 0x1B) | ((var_s7 << 0x1A) | ((var_fp << 0x19) | ((((p->flags.bit6 << 1) | ((temp_v0_5 >> 0x18) & 1)) << 0x16) | ((((p->flags.bit5 << 1) | ((temp_v0_5 >> 0x10) & 1)) << 0x14) | 0x40000)))));
                temp_s0_5 = func_001E1030(arg2, arg3);
                                func_00215B10(arg2, temp_s0_5, 0, (func_001E08F0(arg0, arg1, 0) + 2) * 2);
                return 1;
            }
            break;
        case 0:                                     /* switch 2 */
            if (p->flags.bit3 == 1) {
                func_001E0450(arg0, arg1, 4, 0);
                func_001E0570(arg0, arg1, 4, 0);
                sp140 = func_002508D0(func_001E0290(arg0, arg1, 0) + func_002660E0(func_001DF540(arg0, arg1), arg4, arg5, 1));
            } else {
                sp140 = func_002508D0(p->value1 + func_001E0290(arg0, arg1, 0) + func_002660E0(func_001DF540(arg0, arg1), arg4, arg5, 1));
                func_001E0450(arg0, arg1, 0, p->value1);
                func_001E0570(arg0, arg1, 0, p->value1);
                p->value1 = encode_00246810(p->value1);
            }
            if (p->flags.bit4 == 1) {
                func_001E0450(arg2, arg3, 4, 0);
                func_001E0570(arg2, arg3, 4, 0);
                sp144 = func_002508D0(func_001E0290(arg2, arg3, 0) + func_002660E0(func_001DF540(arg2, arg3), arg4, arg5, 1));
            } else {
                sp144 = func_002508D0(p->value2 + func_001E0290(arg2, arg3, 0) + func_002660E0(func_001DF540(arg2, arg3), arg4, arg5, 1));
                func_001E0450(arg2, arg3, 0, p->value2);
                func_001E0570(arg2, arg3, 0, p->value2);
                p->value2 = encode_00246810(p->value2);
            }
            if (sp140 > sp144) {
                if (p->flags.bit1 == 0) {
                    sp120 = sp140 - sp144;
                }
                out[0] = 0x5E;
                out[1] = (s32) ((p->value2 << 0x10) | ((arg2 << 8) | arg3));
                out[2] = (s32) ((p->value1 << 0x10) | ((arg0 << 8) | arg1));
                out[3] = (s32) ((p->flags.bit2 << 0x1B) | ((var_s7 << 0x1A) | ((var_fp << 0x19) | ((((p->flags.bit6 << 1) | ((temp_v0_5 >> 0x18) & 1)) << 0x16) | (sp120 | 0xA0000 | (((p->flags.bit5 << 1) | ((temp_v0_5 >> 0x10) & 1)) << 0x14))))) | 0x10000000);
                if (sp120 <= 0) {
                    temp_s0_6 = func_001E1030(arg0, arg1);
                                        func_00215B10(arg0, temp_s0_6, 0, (func_001E08F0(arg2, arg3, 0) + 2) * 2);
                } else {
                    temp_s0_7 = func_001E1030(arg0, arg1);
                                        func_00215B10(arg0, temp_s0_7, 0, func_001E08F0(arg2, arg3, 0) * 4);
                }
                return 1;
            }
            if (sp140 == sp144) {
                out[0] = 0x5E;
                out[1] = (s32) ((p->value2 << 0x10) | ((arg2 << 8) | arg3));
                out[2] = (s32) ((p->value1 << 0x10) | ((arg0 << 8) | arg1));
                out[3] = (s32) ((p->flags.bit2 << 0x1B) | ((var_s7 << 0x1A) | ((var_fp << 0x19) | ((((p->flags.bit6 << 1) | ((temp_v0_5 >> 0x18) & 1)) << 0x16) | ((((p->flags.bit5 << 1) | ((temp_v0_5 >> 0x10) & 1)) << 0x14) | 0xC0000)))) | 0x10000000);
                temp_s0_8 = func_001E1030(arg0, arg1);
                                func_00215B10(arg0, temp_s0_8, 0, (func_001E08F0(arg2, arg3, 0) + 2) * 2);
                temp_s0_9 = func_001E1030(arg2, arg3);
                                func_00215B10(arg2, temp_s0_9, 0, (func_001E08F0(arg0, arg1, 0) + 2) * 2);
                return 1;
            }
            if (sp140 < sp144) {
                if (!(p->flags.bit0)) {
                    sp120 = sp144 - sp140;
                }
                out[0] = 0x5E;
                out[1] = (s32) ((p->value2 << 0x10) | ((arg2 << 8) | arg3));
                out[2] = (s32) ((p->value1 << 0x10) | ((arg0 << 8) | arg1));
                out[3] = (s32) ((p->flags.bit2 << 0x1B) | ((var_s7 << 0x1A) | ((var_fp << 0x19) | ((((p->flags.bit6 << 1) | ((temp_v0_5 >> 0x18) & 1)) << 0x16) | (sp120 | 0x50000 | (((p->flags.bit5 << 1) | ((temp_v0_5 >> 0x10) & 1)) << 0x14))))));
                if (sp120 <= 0) {
                    temp_s0_10 = func_001E1030(arg2, arg3);
                                        func_00215B10(arg2, temp_s0_10, 0, (func_001E08F0(arg0, arg1, 0) + 2) * 2);
                } else {
                    temp_s0_11 = func_001E1030(arg2, arg3);
                                        func_00215B10(arg2, temp_s0_11, 0, func_001E08F0(arg0, arg1, 0) * 4);
                }
                return 1;
            }
            break;
        }
    } else {
        if ((temp_s1 == 0) && ((temp_a0 == 1) || ((u32)(temp_a0 - 3) < 3U))) {
            out[0] = 0x5F;
            out[1] = (s32) ((arg0 << 8) | arg1);
            out[2] = (s32) ((arg2 << 8) | arg3);
            out[3] = 1;
            return 1;
        }
        if (temp_s1 == 0) {
            if (temp_a0 == 2) {
                if (func_00271E40(arg0, arg1, 0xB) == 1) {
                    out[0] = 0x5F;
                    out[1] = (s32) ((arg0 << 8) | arg1);
                    out[2] = (s32) ((arg2 << 8) | arg3);
                    out[3] = 3;
                    return 0x10001;
                }
                if (func_00267700(arg0, arg1) != 0) {
                    out[0] = 0x5F;
                    out[1] = (s32) ((arg0 << 8) | arg1);
                    out[2] = (s32) ((arg2 << 8) | arg3);
                    out[3] = 1;
                    return 0x10001;
                }
                temp_v0_20 = func_00248AF0(arg0, arg1, func_001E1030(arg2, arg3));
                if (temp_v0_20 == 0x3E7) {
                    out[0] = 0x5F;
                    out[1] = (s32) ((arg0 << 8) | arg1);
                    out[2] = (s32) ((arg2 << 8) | arg3);
                    out[3] = 1;
                    return 0x10001;
                }
                if (((temp_v0_20 >> 0x1E) & 1) == 1) {
                    func_001E1E70(arg2, arg3, 2, 1);
                    out[0] = 0x2B;
                    out[1] = (s32) ((arg2 << 8) | arg3);
                    out[2] = (s32) ((arg0 << 8) | arg1);
                    out[3] = (s32) ((temp_v0_20 >> 0xE) & 0x3FFF);
                    return 0x10001;
                }
                if ((temp_v0_20 >> 0xE) == 0x219) {
                    func_001E1E70(arg2, arg3, 2, 1);
                    out[0] = 0x25;
                    out[1] = (s32) ((arg0 << 8) | arg1);
                    out[2] = (s32) ((arg2 << 8) | arg3);
                    out[3] = (s32) ((temp_v0_20 & 0x3FFF) | (func_0024DE70(arg2, arg3) << 0x10));
                } else {
                    func_001E1E70(arg2, arg3, 2, 1);
                    out[0] = 0x24;
                    out[1] = (s32) ((arg0 << 8) | arg1);
                    out[2] = (s32) ((arg2 << 8) | arg3);
                    out[3] = temp_v0_20;
                }
                return 0x10001;
            }
        }

        if (temp_s1 == 2) {
            if (temp_a0 == 0) {
                func_00215B10(arg2, func_001E1030(arg2, arg3), 0, 6);
                if (func_00271E40(arg2, arg3, 0xB) == 1) {
                    out[0] = 0x5F;
                    out[1] = (s32) ((arg0 << 8) | arg1);
                    out[2] = (s32) ((arg2 << 8) | arg3);
                    out[3] = 2;
                    return 1;
                }
                if (func_00267700(arg2, arg3) != 0) {
                    out[0] = 0x5F;
                    out[1] = (s32) ((arg0 << 8) | arg1);
                    out[2] = (s32) ((arg2 << 8) | arg3);
                    out[3] = 0;
                    return 1;
                }
                temp_v0_21 = func_00248AF0(arg2, arg3, func_001E1030(arg0, arg1));
                if (temp_v0_21 == 0x3E7) {
                    out[0] = 0x5F;
                    out[1] = (s32) ((arg0 << 8) | arg1);
                    out[2] = (s32) ((arg2 << 8) | arg3);
                    out[3] = 0;
                    return 1;
                }
                if (((temp_v0_21 >> 0x1E) & 1) == 1) {
                    func_001E1E70(arg0, arg1, 2, 1);
                    out[0] = 0x2B;
                    out[1] = (s32) ((arg0 << 8) | arg1);
                    out[2] = (s32) ((arg2 << 8) | arg3);
                    out[3] = (s32) ((temp_v0_21 >> 0xE) & 0x3FFF);
                    return 1;
                }
                if ((temp_v0_21 >> 0xE) == 0x219) {
                    func_001E1E70(arg0, arg1, 2, 1);
                    out[0] = 0x25;
                    out[1] = (s32) ((arg0 << 8) | arg1);
                    out[2] = (s32) ((arg2 << 8) | arg3);
                    out[3] = (s32) ((temp_v0_21 & 0x3FFF) | (func_0024DE70(arg0, arg1) << 0x10));
                } else {
                    func_001E1E70(arg0, arg1, 2, 1);
                    out[0] = 0x24;
                    out[1] = (s32) ((arg0 << 8) | arg1);
                    out[2] = (s32) ((arg2 << 8) | arg3);
                    out[3] = temp_v0_21;
                }
                return 1;
            }

        }
        if (((u32)(temp_s1 - 1) < 5U) && ((u32) temp_a0 < 6U)) {
            out[0] = 0x5F;
            out[1] = (s32) ((arg0 << 8) | arg1);
            out[2] = (s32) ((arg2 << 8) | arg3);
            out[3] = 0;
            if (temp_a0 == 0) {
                func_00215B10(arg2, func_001E1030(arg2, arg3), 0, 6);
            }
            return 1;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_070", func_00247F40);

s32 func_00248370(u32 arg0, s32 arg1, s32 arg2) {
    extern s32 func_001E1030();
    s32 offset;
    s32 row;

    if (arg0 < 2U) {
        if (arg1 == 0) {
            return 0;
        }
    }

    if (arg2 == 0x304) {
        if ((func_001E0700((s32)arg0, arg1) >> 5) == 0) {
            if ((func_001E0700((s32)arg0, arg1) & 0x1F) == 2) {
                return 1;
            }
        }
        return 0;
    }

    row = func_001E1030(arg0, arg1) * 7;
    offset = arg2 - 0x2F0;
    return ((D_0029D580 + (offset >> 3))[row] >> (offset % 8)) & 1;
}

INCLUDE_ASM("asm/nonmatchings/main_070", func_00248460);

s32 func_002487A0(s32 arg0, s32 arg1) {
    s32 bit;

    bit = arg1 - 0x2F0;
    if ((D_0029D580[arg0 * 7 + (bit >> 3)] >> (bit % 8)) & 1) {
        switch (D_0029D1F0[arg1]) {
        case 4:
            switch (D_0029CF32[arg1]) {
            case 6:
                return arg1 | 0x40444000;
            case 7:
                return arg1 | 0x406AC000;
            case 8:
                switch (arg0) {
                case 0x156:
                    return arg1 | 0x407A0000;
                case 7:
                    return arg1 | 0x407D4000;
                }
                break;
            case 9:
                switch (arg0) {
                case 0x10:
                    return arg1 | (((func_0019A5C8() % 5 + 0xD) << 14) | 0x40000000);
                case 0x11:
                    return arg1 | (((func_0019A5C8() % 5 + 0xD) << 14) | 0x40000000);
                case 0xA7:
                    return arg1 | (((func_0019A5C8() % 15 + 0xD1) << 14) | 0x40000000);
                case 0x14C:
                    return arg1 | (((func_0019A5C8() % 32 + 0x65) << 14) | 0x40000000);
                case 0x17B:
                    return arg1 | (((u16)func_002494D0() << 14) | 0x40000000);
                }
                break;
            }
            break;
        case 0:
            switch (D_0029CF32[arg1]) {
            case 0:
                return arg1 | 0x864000;
            default:
                return arg1 | 0x860000;
            }
        case 3:
            return arg1 | 0x874000;
        case 2:
            return arg1 | 0x878000;
        case 1:
            switch (D_0029CF32[arg1]) {
            case 5:
                return arg1 | 0x870000;
            default:
                return arg1 | 0x860000;
            }
        default:
            return arg1 | 0x860000;
        }
    } else {
        return 0x3E7;
    }
    return 0x3E7;
}

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

s64 func_002493A0(s32 arg0) {
    switch (D_0029D1F0[arg0]) {
    case 0:
        return D_0029CF32[arg0];
    case 1:
    case 4:
        return 0x3E8;
    default:
        return 0;
    }
}

s32 func_00249410(u16 arg0, u16 *arg1) {
    s32 i;
    u16 card;
    s32 count;
    u8 *flags;

    card = 0x2F0;
    count = 0;
    i = 0;
    flags = D_0029D580 + arg0 * 7;

    do {
        s32 offset;

        if (count >= 0xC) {
            return count;
        }
        offset = card - 0x2F0;
        if ((flags[offset >> 3] >> (offset % 8)) & 1) {
            if (card != 0x315 && card != 0x30C && card != 0x31C) {
                *arg1++ = card;
                count++;
            }
        }
        card++;
        i++;
    } while (i < 0x31);

    return count;
}

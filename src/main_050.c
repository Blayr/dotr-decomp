#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F3790);

typedef struct Entry_001F3870 {
    u64 state : 3;
    u64 source : 3;
    u64 target : 10;
    u64 reserved : 48;
} Entry_001F3870;

void func_001F3870(void) {
    extern Entry_001F3870 D_0031BB50[];
    Entry_001F3870 *entry;
    s32 i;

    entry = D_0031BB50;
    for (i = 0; (s64)i < 32; i++, entry++) {
        if (entry->state == 2 && func_001F5240(entry->source, entry->target) == 0) {
            entry->state = 3;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F3910);

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F3CB0);

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F3E40);

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F3EA0);

typedef struct Entry_001F3F20 {
    u64 kind : 3;
    u64 time : 13;
    u64 source : 3;
    u64 target : 10;
    u64 rest : 35;
    u8 pad[0x10];
} Entry_001F3F20;

typedef struct Link_001F3F20 {
    u64 status : 3;
    u64 from : 3;
    u64 to : 10;
    u64 extra : 48;
} Link_001F3F20;

typedef struct Cue_001F3F20 {
    u16 end : 4;
    u16 time : 12;
    u16 id;
} Cue_001F3F20;

static inline Link_001F3F20 *find_001F3F20(s32 source, s32 target) {
    extern Link_001F3F20 D_0031BB50[];
    Link_001F3F20 *slot;
    s32 i;

    slot = D_0031BB50;
    for (i = 0; (s64)i < 32; i++, slot++) {
        if ((source < 0 || slot->from == source) && (target < 0 || slot->to == target)) {
            return slot;
        }
    }
    return NULL;
}

void func_001F3F20(void) {
    extern Entry_001F3F20 D_0031BC50[];
    extern s32 func_001A8760();
    Entry_001F3F20 *entry;
    s32 i;
    s32 j;
    s32 start;
    s32 now;
    Link_001F3F20 *slot;
    s32 delta;
    Cue_001F3F20 *cue;

    entry = D_0031BC50;
    for (i = 0; i < 24; i++, entry++) {
        if (entry->source != 0) {
            continue;
        }
        if (entry->kind != 1) {
            continue;
        }
        slot = find_001F3F20(entry->source, entry->target);
        if (slot == NULL || slot->status != 2) {
            continue;
        }
        cue = *(Cue_001F3F20 **)((u8 *)slot + 4);
        if (cue == NULL) {
            continue;
        }
        delta = func_001A8760();
        now = (u16)entry->time;
        start = (u16)(now - delta);
        for (j = 0; j < 64; j++) {
            if (cue[j].end == 0xF) {
                break;
            }
            if (cue[j].time >= start && cue[j].time < now) {
                func_00217710(1, cue[j].id);
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F40D0);

void func_001F48F0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_001F4900(arg0, arg1, arg2, arg3, arg4, 0, 0);
}

typedef struct Slot_001F4900 {
    u16 state : 3;
    u16 counter : 13;
    u16 group : 3;
    u16 entry : 10;
    s16 flagA : 1;
    s16 flagB : 1;
    s16 flagC : 1;
    s16 arg3;
    s16 arg4;
    s32 arg5;
    s32 arg6;
    s32 timer;
    s32 arg2;
} Slot_001F4900;

typedef struct Cache_001F4900 {
    u8 data[0x340];
    s32 group;
    s32 entry;
} Cache_001F4900;

typedef struct Dispatch_001F4900 {
    s32 (**handlers)(void *, s32);
    s32 unused;
    s32 count;
} Dispatch_001F4900;

extern s32 D_0031BE90;
extern Dispatch_001F4900 D_00292FF0[];
extern s32 D_00292FF8[];
void func_0017BB90(s32);
void func_0017B410(s32, s32);

s32 func_001F4900(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    extern Cache_001F4900 D_0031BB50;
    extern Slot_001F4900 D_0031BC50[];
    Slot_001F4900 *slot;
    void *source;
    u8 *buffer;
    s32 index;
    void *destination;
    s32 result;
    extern s32 func_001F3910();

    buffer = (u8 *)&D_0031BB50;
    slot = D_0031BC50;
    source = 0;
    if (arg0 < 0 || arg0 >= 3) {
        return -1;
    }
    if (arg1 < 0 || arg1 >= D_00292FF8[arg0 * 3]) {
        return -1;
    }
    if (arg0 == 1 && func_001F5240(1, -1) != 0) {
        return -1;
    }
    switch (arg0) {
    case 1:
        source = (void *)func_001F1130(func_001E1360(arg4 >> 8, arg4 & 0xFF));
        break;
    case 2:
        source = (void *)func_001F0FF0(func_001E1360(arg4 >> 8, arg4 & 0xFF));
        break;
    }
    if (source == 0) {
        s32 allocation = func_001F3910(arg0, arg1, 1);
        if (allocation == 0) {
            return -1;
        }
        source = (void *)(((s64)(((u8 *)allocation - buffer) >> 3) << 15) + 0x01EE0000);
    }
    index = 0;
    do {
        destination = (void *)0x01ED0000;
        if (slot->state == 0) {
            Cache_001F4900 *cache = &D_0031BB50;
            if (D_0031BE90 != arg0 || cache->entry != arg1) {
                func_0020B380((void *)0x01E00000, (void *)source, 0x800);
                func_0017BB90(0);
                func_0017B410(0x01E00000, *(s32 *)0x01E0001C + 0xFE200000);
                cache->group = arg0;
                cache->entry = arg1;
            }
            func_001F5370(arg3);
            func_001F5390(arg4);
            func_0020BAF0(0);
            if (arg0 != 1) {
                destination = (void *)(((s64)index << 15) + 0x01E10000);
            }
            result = D_00292FF0[arg0].handlers[arg1](destination, arg2);
            func_0020BB50();
            slot->state = 1;
            slot->group = arg0;
            slot->entry = arg1;
            slot->arg2 = arg2;
            slot->arg3 = arg3;
            slot->arg4 = arg4;
            slot->flagA = 0;
            slot->flagB = 0;
            slot->flagC = 0;
            slot->counter = 0;
            slot->timer = 0;
            slot->arg5 = arg5;
            slot->arg6 = arg6;
            if (result == 8) {
                func_001F4CB0(index);
                index = -1;
            }
            return index;
        }
        index++;
        slot++;
    } while (index < 24);
    return -1;
}

typedef struct {
    u64 state : 3;
    u64 source : 3;
    u64 target : 10;
    u64 reserved : 48;
} Entry_001F4CB0;

typedef struct {
    u8 state : 3;
    u8 : 5;
    u8 unk1;
    u16 kind : 3;
    u16 value : 10;
    u16 : 3;
    u16 unk4;
    u16 unk6;
    void (*callback)(s32);
    s32 arg;
    s32 unk10;
    s32 unk14;
} Slot_001F4CB0;

typedef struct {
    Entry_001F4CB0 entries[32];
    Slot_001F4CB0 slots[24];
} Data_001F4CB0;


static inline void *find_001F4CB0(s32 source, s32 target) {
    extern Data_001F4CB0 D_0031BB50;
    Entry_001F4CB0 *entry;
    s32 i;

    entry = D_0031BB50.entries;
    for (i = 0; (s64)i < 32; i++, entry++) {
        if ((source < 0 || entry->source == source) && (target < 0 || entry->target == target)) {
            return entry;
        }
    }
    return NULL;
}

s32 func_001F4CB0(s32 arg0) {
    extern Data_001F4CB0 D_0031BB50;
    Slot_001F4CB0 *slot = &D_0031BB50.slots[arg0];
    Entry_001F4CB0 *entry;

    if (arg0 < 0 || arg0 >= 24) {
        return 0;
    }
    if (slot->kind == 1 || slot->kind == 2) {
        func_001F56D0(slot->unk6, slot->kind);
        func_001F56D0(slot->unk4, slot->kind);
    }
    slot->state = 0;
    if (slot->callback != NULL) {
        slot->callback(slot->arg);
    }
    entry = find_001F4CB0(slot->kind, slot->value);
    if (entry == NULL) {
        return 1;
    }
    if (entry->state == 2 && func_001F5240(entry->source, entry->target) == 0) {
        entry->state = 3;
    }
    return 1;
}

typedef struct Entry_001F4E50 {
    u8 pad0[2];
    u16 category : 3;
    u16 kind : 10;
    u16 reserved : 3;
    u8 pad4[0x14];
} Entry_001F4E50;

extern struct Entry_001F5240 D_0031BC50[];

s32 func_001F4E50(s32 arg0, s32 arg1) {
    Entry_001F4E50 *var_s0;
    s32 var_s1;
    s32 var_s2;

    var_s0 = (Entry_001F4E50 *)D_0031BC50;
    var_s1 = 0;
    var_s2 = 0;
    do {
        if ((arg0 < 0 || var_s0->category == arg0) &&
            (arg1 < 0 || var_s0->kind == arg1)) {
            var_s1 |= func_001F4CB0(var_s2);
        }
        var_s2 += 1;
        var_s0++;
    } while (var_s2 < 0x18);
    return var_s1;
}

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F4F10);

typedef struct Entry_001F4FD0 {
    u16 unk0;
    u16 category : 3;
    u16 group : 10;
    u16 unused : 3;
    u8 unk4[0x14];
} Entry_001F4FD0;

s32 func_001F4F10(s32, s32);
extern struct Entry_001F5240 D_0031BC50[];

s32 func_001F4FD0(s32 arg0, s32 arg1, s32 arg2) {
    Entry_001F4FD0 *var_s0;
    s32 var_s1;
    s32 var_s2;

    var_s0 = (Entry_001F4FD0 *)D_0031BC50;
    var_s1 = 0;
    var_s2 = 0;
    do {
        if (arg0 < 0 || var_s0->category == arg0) {
            if (arg1 < 0 || var_s0->group == arg1) {
                var_s1 |= func_001F4F10(var_s2, arg2);
            }
        }
        var_s2 += 1;
        var_s0++;
    } while (var_s2 < 0x18);
    return var_s1;
}

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F5090);

typedef struct Entry_001F51D0 {
    u8 flags;
    u8 pad[0x17];
} Entry_001F51D0;

typedef struct State_001F51D0 {
    u8 pad[0x100];
    Entry_001F51D0 entries[0x18];
} State_001F51D0;

s32 func_001F51D0(s32 arg0) {
    extern State_001F51D0 D_0031BB50;
    Entry_001F51D0 *entry;
    s32 temp_a0;
    s32 var_v0;

    entry = &D_0031BB50.entries[arg0];
    var_v0 = 0;
    if ((arg0 < 0) || (arg0 >= 0x18)) {
        return 0;
    }
    temp_a0 = entry->flags & 7;
    if (temp_a0 == 1) {
        var_v0 |= 1;
    }
    if (temp_a0 == 2) {
        var_v0 |= 2;
    }
    return var_v0;
}

typedef struct Entry_001F5240 {
    u8 state : 3;
    u8 : 5;
    u8 unk1;
    u16 kind : 3;
    u16 value : 10;
    u16 : 3;
    u8 padding[0x14];
} Entry_001F5240;

extern Entry_001F5240 D_0031BC50[];

s32 func_001F5240(s32 arg0, s32 arg1) {
    Entry_001F5240 *entry;
    s32 result;
    s32 i;
    s32 state;

    entry = D_0031BC50;
    result = 0;
    i = 0;
    do {
        if (arg0 < 0 || entry->kind == arg0) {
            if (arg1 < 0 || entry->value == arg1) {
                state = entry->state;
                if (state == 1) {
                    result |= 1;
                }
                if (state == 2) {
                    result |= 2;
                }
            }
        }
        i++;
        entry++;
    } while (i < 0x18);
    return result;
}

typedef struct {
    u8 unk00[0x10];
    s32 unk10;
    s32 unk14;
} Entry_001F52D0;

typedef struct {
    u8 unk00[0x100];
    Entry_001F52D0 entries[0x18];
} Data_001F52D0;

extern Data_001F52D0 D_0031BB50;

s32 func_001F52D0(s32 arg0) {
    Entry_001F52D0 *entry = &D_0031BB50.entries[arg0];
    s32 ret;

    if ((arg0 < 0) || (arg0 >= 0x18)) {
        ret = -1;
    } else {
        ret = entry->unk10;
    }
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F5320);

void func_001F5370(s32 arg0) {
    D_0031BE98 = arg0;
}

s32 func_001F5380(u8 arg0) {
    return D_0031BE98;
}

void func_001F5390(s32 arg0) {
    D_0031BE9C = arg0;
}

s32 func_001F53A0(u8 arg0) {
    return D_0031BE9C;
}

void func_001F53B0(s32 arg0, s32 arg1) {
    func_001F53C0(arg0, D_0031BE98, arg1);
}

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F53C0);

s32 func_001F54E0(s32 arg0) {
    extern s32 func_001E1360(s32, s32);
    s32 hi;
    s32 lo;

    hi = arg0 >> 8;
    lo = arg0 & 0xFF;
    if (hi < 0 || hi >= 3 || lo < 0 || lo >= 0xB) {
        return -1;
    }
    arg0 = func_001E1360(hi, lo);
    if (arg0 < 0) {
        return -1;
    }
    return func_001F2B30(arg0);
}

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F5560);

s32 func_001F5620(s32 arg0, s32 arg1, s32 arg2) {
    extern s32 func_001E1360(s32, s32);
    s32 hi = arg0 >> 8;
    s32 lo = arg0 & 0xFF;
    f32 *vec = (f32 *)arg2;

    vec[2] = 0.0f;
    vec[1] = 0.0f;
    vec[0] = 0.0f;
    vec[3] = 1.0f;
    if (hi < 0 || hi >= 3 || lo < 0 || lo >= 0xB) {
        return 0;
    }
    arg0 = func_001E1360(hi, lo);
    if (arg0 < 0) {
        return 0;
    }
    return func_001F2EC0(arg0, arg1, arg2);
}

s32 func_001F56D0(s32 arg0, s32 arg1) {
    extern s32 func_001E1360(s32, s32);
    s32 hi;
    s32 lo;
    s32 i;
    s32 value;

    hi = arg0 >> 8;
    lo = arg0 & 0xFF;
    if (hi < 0 || hi >= 3 || lo < 0 || lo >= 0xB) {
        return 0;
    }
    arg0 = func_001E1360(hi, lo);
    if (arg0 < 0) {
        return 0;
    }
    for (i = 0; i < 8; i++) {
        value = func_001F2BE0(arg0, i);
        if (value >= 0 && value < 8 && ((value & 0x7F00) >> 8) == arg1) {
            func_001F2DD0(arg0, -1, i);
        }
    }
    return 1;
}

void func_001F57B0(s32 arg0) {
    func_001F57C0(D_0031BE9C, arg0);
}

s32 func_001F57C0(s32 arg0, s32 arg1) {
    s32 func_001E1360(s32, s32);
    s32 func_001F2FF0(s32, s32);
    s32 row;
    s32 column;

    row = arg0 >> 8;
    column = arg0 & 0xFF;
    if (row < 0 || row >= 3 || column < 0 || column >= 0xB) {
        return 0;
    }
    arg0 = func_001E1360(row, column);
    if (arg0 < 0) {
        return 0;
    }
    return func_001F2FF0(arg0, arg1);
}

void func_001F5850(void) {
    func_001F5860(D_0031BE98);
}

f32 func_001F5860(s32 arg0) {
    extern s32 func_001E1360(s32, s32);
    s32 hi;
    s32 lo;

    hi = arg0 >> 8;
    lo = arg0 & 0xFF;
    if (hi < 0 || hi >= 3 || lo < 0 || lo >= 0xB) {
        return 0.0f;
    }
    arg0 = func_001E1360(hi, lo);
    if (arg0 < 0) {
        return 0.0f;
    }
    return func_001F0F40(arg0);
}

s32 func_001F58E0(s32 arg0) {
    extern s32 func_001E1360(s32, s32);
    extern s32 func_001F2920(s32);
    s32 hi;
    s32 lo;

    hi = arg0 >> 8;
    lo = arg0 & 0xFF;
    if (hi < 0 || hi >= 3 || lo < 0 || lo >= 0xB) {
        return -1;
    }
    arg0 = func_001E1360(hi, lo);
    if (arg0 < 0) {
        return -1;
    }
    return func_001DE260(func_001DE130(func_001F2920(arg0)));
}

s32 func_001F5970(s32 arg0, s32 arg1) {
    s32 temp_a1;
    s32 temp_v1;

    temp_v1 = arg0 >> 8;
    temp_a1 = arg0 & 0xFF;
    if ((temp_v1 < 0) || (temp_v1 >= 3) ||
        (temp_a1 < 0) || (temp_a1 >= 0xB)) {
        return 0;
    }
    return func_001E3850(temp_v1, temp_a1, arg1);
}

s32 func_001F59D0(s32 arg0, s32 arg1) {
    s32 column;
    s32 row;

    row = arg0 >> 8;
    column = arg0 & 0xFF;
    if (row < 0 || row >= 3 || column < 0 || column >= 11) {
        return 0;
    }
    return func_001E3900(row, column, arg1);
}

s32 func_001F5A30(s32 arg0, s32 arg1) {
    s32 row;
    s32 column;

    row = arg0 >> 8;
    column = arg0 & 0xFF;
    if (row < 0 || row >= 3 || column < 0 || column >= 11) {
        return 0;
    }
    return func_001E3990(row, column, arg1);
}

s32 func_001F5A90(s32 arg0, s32 arg1) {
    s32 column;
    s32 row;

    row = arg0 >> 8;
    column = arg0 & 0xFF;
    if (row < 0 || row >= 3 || column < 0 || column >= 11) {
        return 0;
    }
    return func_001E3A20(row, column, arg1);
}

s32 func_001F5AF0(s32 arg0) {
    s32 temp_v0;

    temp_v0 = func_001DF540(arg0 >> 8, arg0 & 0xFF);
    if (temp_v0 == 0) {
        return 0;
    }
    return (*(s32 *)((u8 *)temp_v0 + 4) != 0) ? 1 : 0;
}

s32 func_001F5B30(s32 arg0) {
    s32 *temp_v0;

    temp_v0 = (s32 *)func_001DF540(arg0 >> 8, arg0 & 0xFF);
    if (temp_v0 == 0) {
        return 0;
    }
    return temp_v0[1];
}

s32 func_001F5B70(s32 arg0, s32 arg1) {
    s32 temp_a1;
    s32 temp_v1;

    temp_v1 = arg0 >> 8;
    temp_a1 = arg0 & 0xFF;
    if (temp_v1 < 0 || temp_v1 >= 3 || temp_a1 < 0 || temp_a1 >= 0xB) {
        return 0;
    }
    return func_001E3AB0(temp_v1, temp_a1, arg1);
}

typedef struct Vec4_001F5BD0 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4_001F5BD0;


s32 func_001F5BD0(s32 arg0, void *arg1) {
    s32 index;
    s32 group;
    Vec4_001F5BD0 *out = arg1;

    group = arg0 >> 8;
    index = arg0 & 0xFF;
    out->z = 0.0f;
    out->y = 0.0f;
    out->x = 0.0f;
    out->w = 1.0f;
    if (group < 0 || group >= 3 || index < 0 || index >= 11) {
        return 0;
    }
    return func_001E3B50(group, index, out);
}

s32 func_001F5C40(s32 arg0, s32 arg1) {
    s32 column;
    s32 row;

    row = arg0 >> 8;
    column = arg0 & 0xFF;
    if ((row < 0) || (row >= 3) || (column < 0) || (column >= 11)) {
        return 0;
    }
    return func_001E3BF0(row, column, arg1);
}

s32 func_001F5CA0(s32 arg0, void *arg1) {
    s32 row = arg0 >> 8;
    s32 column = arg0 & 0xFF;
    s32 *out = arg1;

    out[3] = 0;
    out[2] = 0;
    out[1] = 0;
    out[0] = 0;
    if (row < 0 || row >= 3 || column < 0 || column >= 11) {
        return 0;
    }
    return func_001E3C90(row, column, arg1);
}

s32 func_001F5D10(s32 arg0, s32 arg1) {
    s32 temp_a1;
    s32 temp_v1;

    temp_v1 = arg0 >> 8;
    temp_a1 = arg0 & 0xFF;
    if (temp_v1 < 0 || temp_v1 >= 3 || temp_a1 < 0 || temp_a1 >= 0xB) {
        return 0;
    }
    return func_001E3D30(temp_v1, temp_a1, arg1);
}

typedef struct {
    f32 x, y, z, w;
} Vec4_001F5D70;


s32 func_001F5D70(s32 arg0, void *arg1) {
    Vec4_001F5D70 *out = (Vec4_001F5D70 *)arg1;
    s32 a = arg0 >> 8;
    s32 b = arg0 & 0xFF;

    out->z = 0.0f;
    out->y = 0.0f;
    out->x = 0.0f;
    out->w = 1.0f;
    if (a < 0 || a >= 3 || b < 0 || b >= 0xB) {
        return 0;
    }
    return func_001E3DD0(a, b, out);
}

s32 func_001F5DE0(s32 arg0, s32 arg1) {
    s32 row;
    s32 column;

    row = arg0 >> 8;
    column = arg0 & 0xFF;
    if (row < 0 || row >= 3 || column < 0 || column >= 11) {
        return 0;
    }
    return func_001E3E70(row, column, arg1);
}

s32 func_001F5E40(s32 arg0, u8 *arg1) {
    s32 index;
    s32 bank;

    bank = arg0 >> 8;
    index = arg0 & 0xFF;
    arg1[3] = 0x80;
    arg1[0] = 0x80;
    arg1[1] = 0x80;
    arg1[2] = 0x80;
    if (bank < 0 || bank >= 3 || index < 0 || index >= 11) {
        return 0;
    }
    return func_001E3F10(bank, index, arg1);
}

s32 func_001F5EB0(void) {
    return func_001F5EC0(D_0031BE98);
}

s32 func_001F5EC0(s32 arg0) {
    s32 temp_v0;

    temp_v0 = func_001DF540(arg0 >> 8, arg0 & 0xFF);
    if (temp_v0 != 0) {
        return func_001F1370(*((u8 *)temp_v0 + 0x46));
    }
    return 0;
}

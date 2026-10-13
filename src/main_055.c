#include "common.h"

typedef struct Entry_00202220 {
    s32 state;
    char *name;
    s8 flag0 : 1;
    s8 flag1 : 1;
    s8 flag2 : 1;
    s16 group : 13;
    s16 index;
} Entry_00202220;

extern s8 D_002BD0C1[];
extern char D_002D074B[];
extern char D_002D0760[];
extern s32 func_002024D0();

static inline Entry_00202220 *find_00202220(s32 group, s32 index) {
    extern Entry_00202220 D_003229A0[];
    Entry_00202220 *entry = D_003229A0;
    s32 i;

    if (group < 0 || group >= 10) {
        return NULL;
    }
    if (index < 0) {
        return NULL;
    }
    i = 0;
    do {
        if (entry->state != 0 && entry->group == group && entry->index == index) {
            return entry;
        }
        i++;
        entry++;
    } while (i < 1024);
    return NULL;
}

static inline Entry_00202220 *empty_00202220(void) {
    extern Entry_00202220 D_003229A0[];
    Entry_00202220 *entry = D_003229A0;
    s32 i = 0;

    do {
        if (entry->state == 0) {
            return entry;
        }
        i++;
        entry++;
    } while (i < 1024);
    return NULL;
}

s32 func_00202220(s32 arg0, s32 arg1, char *arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    Entry_00202220 *entry;
    char path[128];
    extern s32 func_001FECB0();
    extern void func_0019B648();

    if (arg0 < 0 || arg0 >= 10) {
        return 0;
    }
    if (arg1 < 0) {
        return 0;
    }
    if (find_00202220(arg0, arg1) != NULL) {
        return 0;
    }
    entry = empty_00202220();
    if (entry == NULL) {
        return 0;
    }
    if ((D_002BD0C1[*(s8 *)arg2] & 3) && ((s8 *)arg2)[1] == ':') {
        func_0019BDD8(path, arg2);
    } else {
        func_0019B648(path, D_002D0760, func_001FFF90((s32)D_002D074B), arg2);
    }
    if (func_001FECB0(arg0 | 0x1000, 0, (s32)path, arg3, arg4, arg5, arg6,
                     (s32)func_002024D0, entry) == 0) {
        return 0;
    }
    entry->name = func_00217B60(arg2);
    entry->state = 0x80000000;
    entry->flag0 = 0;
    entry->flag1 = 0;
    entry->flag2 = (s8)(arg3 != 0 ? 0 : 1);
    entry->group = (s16)arg0;
    entry->index = arg1;
    return 1;
}

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

typedef struct {
    s32 data;
    char *name;
    s8 flag0 : 1;
    s8 flag1 : 1;
    s8 flag2 : 1;
    s16 category : 13;
    s16 id;
} Slot_002029B0;

s32 func_002029B0(s32 arg0, s32 arg1) {
    extern Slot_002029B0 D_003229A0[];
    Slot_002029B0 *entry;
    s32 i;
    s32 result;

    entry = D_003229A0;
    result = 0;
    i = 0;
    do {
        if (entry->data != 0 && (arg0 < 0 || entry->category == arg0) &&
            (arg1 < 0 || entry->id == arg1) && !(entry->data & 0x80000000)) {
            if (entry->name != NULL) {
                func_00217B50((s32)entry->name);
                entry->name = NULL;
            }
            if (entry->data != 0) {
                if (entry->flag2) {
                    func_00217B50(entry->data);
                }
                entry->data = 0;
            }
            result = 1;
        }
        i++;
        entry++;
    } while (i < 0x400);
    return result;
}

s32 func_00202AB0(s32 arg0, s32 arg1) {
    s32 sp3C;

    func_00209D30(func_00202B00(func_00209D20(), arg0, arg1, &sp3C));
    return sp3C;
}

typedef struct Record_00202B00 {
    s32 data;
    s32 unused;
    union {
        struct {
            s8 active : 1;
            s8 excluded : 1;
            s8 unused : 6;
        } flags;
        struct {
            s16 unused : 3;
            s16 category : 13;
        } category;
    } state;
    s16 padding;
} Record_00202B00;

s32 func_00202B00(s32 arg0, s32 arg1, s32 arg2, s32 *arg3) {
    extern Record_00202B00 D_003229A0[];
    Record_00202B00 *entry;
    s32 start;
    s32 i;
    s32 size;

    entry = D_003229A0;
    start = arg2;
    i = 0;
    do {
        if (entry->data != 0 && entry->state.flags.active && !entry->state.flags.excluded &&
            (arg1 < 0 || entry->state.category.category == arg1)) {
            arg0 = func_00202FB0(arg0, entry->data, arg2, (s32) &size);
            arg2 += size;
        }
        i++;
        entry++;
    } while (i < 0x400);
    if (arg3 != NULL) {
        *arg3 = arg2 - start;
    }
    return arg0;
}

typedef struct Entry_00202BF0 {
    s32 value;
    s32 unk4;
    s8 enabled : 1;
    s8 pending : 1;
    s8 other : 6;
} Entry_00202BF0;

static inline Entry_00202BF0 *lookup_00202BF0(s32 arg0, s32 arg1) {
    Entry_00202BF0 *entry;

    entry = func_002008A0(arg0, arg1);
    if ((entry != NULL) && !(entry->value & 0x80000000)) {
        return entry;
    }
    return NULL;
}

s32 func_00202BF0(s32 arg0, s32 arg1) {
    Entry_00202BF0 *entry;

    if ((arg0 < 0) || (arg0 >= 0xA)) {
        return 0;
    }
    if (arg1 < 0) {
        return 0;
    }
    entry = lookup_00202BF0(arg0, arg1);
    if (entry == NULL) {
        return 0;
    }
    entry->enabled = 1;
    entry->pending = 0;
    return entry->value;
}

typedef struct Flags_00202CB0 {
    s8 active : 1;
    s8 enabled : 1;
    s8 unused : 6;
} Flags_00202CB0;

typedef struct Filter_00202CB0 {
    s16 unused : 3;
    s16 category : 13;
} Filter_00202CB0;

typedef struct Entry_00202CB0 {
    s32 handle;
    s32 unused;
    union {
        Flags_00202CB0 flags;
        Filter_00202CB0 filter;
    } state;
    s16 id;
} Entry_00202CB0;

s32 func_00202CB0(s32 category, s32 id, s32 enabled) {
    extern Entry_00202CB0 D_003229A0[];
    Entry_00202CB0 *entry;
    s32 i;
    s32 result;

    entry = D_003229A0;
    result = 0;
    i = 0;
    do {
        if (entry->handle != 0 && entry->state.flags.active != 0 &&
            (category < 0 || entry->state.filter.category == category) &&
            (id < 0 || entry->id == id)) {
            entry->state.flags.enabled = (s8)(enabled ? 1 : 0);
            result = 1;
        }
        i++;
        entry++;
    } while (i < 0x400);
    return result;
}

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

typedef struct Tex0_00202FB0 {
    u64 base : 14;
    u64 reserved0 : 23;
    u64 clut : 14;
    u64 reserved1 : 13;
} Tex0_00202FB0;

typedef struct Header_00202FB0 {
    s32 dataOffset;
    s32 dataSize;
    u8 reserved0[0x18];
    Tex0_00202FB0 tex0;
    u8 reserved1[0x20];
    s32 packetCount;
} Header_00202FB0;

typedef struct Packet_00202FB0 {
    u8 reserved0[0x24];
    u16 base : 14;
    u16 reserved1 : 2;
    u8 reserved2[0xA];
} Packet_00202FB0;

typedef struct Range_00202FB0 {
    u16 base;
    u16 size;
    u16 used;
} Range_00202FB0;

/* D_00322990 starts a {base, size, used} record of three shorts. */
static inline s32 allocate_00202FB0(s32 size) {
    Range_00202FB0 *range = (Range_00202FB0 *)&D_00322990;
    s32 base;

    if ((u16)(&D_00322990)[2] + size > (u16)(&D_00322990)[1]) {
        return -1;
    }
    base = range->base + range->used;
    range->used += size;
    return base;
}

static inline u16 reset_00202FB0(s16 base) {
    D_00322990 = base;
    (&D_00322990)[1] = 0x20;
    (&D_00322990)[2] = 0;
    return (u16)(&D_00322990)[1];
}

s32 func_00202FB0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    extern s32 func_0020B380();
    Header_00202FB0 *header = (Header_00202FB0 *)(arg1 + 0x10);
    Packet_00202FB0 *packet = (Packet_00202FB0 *)arg0;
    s32 clutSize;
    s32 clutBase;
    s32 start = arg2;
    s32 count;

    clutBase = 0;
    if (arg3 != 0) {
        *(s32 *)arg3 = 0;
    }
    if (arg1 == 0) {
        return arg0;
    }

    if ((clutSize = func_00202E30(header)) > 0) {
        clutBase = allocate_00202FB0(clutSize);
        if (clutBase < 0) {
            arg2 += reset_00202FB0(arg2);
            clutBase = allocate_00202FB0(clutSize);
        }
    }

    arg0 = func_0020B380((void *)arg0, (void *)(arg1 + header->dataOffset), header->dataSize >> 4);
    header->tex0.base = arg2;
    header->tex0.clut = clutBase;
    count = header->packetCount;
    if (clutSize != 0) {
        count--;
        packet->base = clutBase;
        packet++;
    }
    while (count--) {
        packet->base = arg2;
        arg2 += 0x20;
        packet++;
    }
    if (arg3 != 0) {
        *(s32 *)arg3 = arg2 - start;
    }
    return arg0;
}

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

typedef struct Flags_00203CD0 {
    s8 flag0 : 1;
    s8 flag1 : 1;
    s8 flag2 : 1;
    s8 unused3 : 5;
} Flags_00203CD0;

typedef struct State_00203CD0 {
    s32 f00;
    s32 f04;
    s32 f08;
    s32 f0C;
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
    s32 f20;
    s32 f24;
    s32 f28;
    Flags_00203CD0 flags;
} State_00203CD0;

extern State_00203CD0 D_00325C80;

INCLUDE_ASM("asm/nonmatchings/main_055", func_00203CD0);

INCLUDE_ASM("asm/nonmatchings/main_055", func_00203E20);

INCLUDE_ASM("asm/nonmatchings/main_055", func_002047F0);

s32 func_00205150(void) {
    return D_00325C80.f00;
}

s32 func_00205160(void) {
    return D_00325C80.f04;
}

typedef struct Flags_00205170 {
    s8 flag0 : 1;
    s8 unused1 : 1;
    s8 flag2 : 1;
    s8 unused3 : 5;
} Flags_00205170;

typedef struct State_00205170 {
    u8 padding[0x2C];
    Flags_00205170 flags;
} State_00205170;

s32 func_00205170(void) {
    extern Flags_00205170 D_00325CAC;
    State_00205170 *state = (State_00205170 *)&D_00325C80;

    if (D_00325CAC.flag2 != 0) {
        return 1;
    }
    return state->flags.flag0 != 0 ? 1 : 0;
}

typedef struct {
    s8 enabled : 1;
} Flags_002051C0;

void func_002051C0(s64 arg0) {
    extern Flags_002051C0 D_00325CAC;

    D_00325CAC.enabled = (s8)arg0;
}

typedef struct {
    s8 : 2;
    s8 flag : 1;
} Flags_002051F0;

extern Flags_002051F0 D_00325CAC;

s32 func_002051F0(void) {
    return D_00325CAC.flag ? 1 : 0;
}

#pragma pack(2)
typedef struct BitmapFileHeader_00205210 {
    s16 type;
    u16 sizeLow;
    u16 sizeHigh;
    s16 reserved1;
    s16 reserved2;
    u16 offsetLow;
    u16 offsetHigh;
} BitmapFileHeader_00205210;
#pragma pack()

typedef struct BitmapInfo_00205210 {
    s32 size;
    s32 width;
    s32 height;
    s16 planes;
    s16 bits;
    s32 compression;
    s32 imageSize;
    s32 horizontalResolution;
    s32 verticalResolution;
    s32 colorsUsed;
    s32 colorsImportant;
} BitmapInfo_00205210;

s32 func_0017FA98(void *, s32);
s32 func_0017FD20(s32);
s32 func_00180348(s32, void *, s32);
extern u8 D_002D07FA[];
extern u8 D_002D0806[];
extern s32 D_00325CB0;

void func_00205210(void) {
    u8 buffer[0x780];
    BitmapInfo_00205210 info;
    BitmapFileHeader_00205210 fileHeader;
    s32 fd;
    u32 fileSize;
    extern s32 func_0019B648();

    while (func_001FF350(-1) != 0) {
        func_001FF420();
    }
    func_0020A3B0(0x04000000);
    fileHeader.type = 0x4D42;
    fileSize = 0x280 * 0x1C0 * 3 + 0x36;
    fileHeader.sizeLow = fileSize;
    fileHeader.sizeHigh = fileSize >> 16;
    fileHeader.reserved1 = 0;
    fileHeader.reserved2 = 0;
    fileHeader.offsetLow = 0x36;
    fileHeader.offsetHigh = 0;
    info.size = 0x28;
    info.width = 0x280;
    info.height = 0x1C0;
    info.planes = 1;
    info.bits = 0x18;
    info.compression = 0;
    info.imageSize = 0xD2000;
    info.horizontalResolution = 1;
    info.verticalResolution = 1;
    info.colorsUsed = 0;
    info.colorsImportant = 0;

    for (;;) {
        func_0019B648(buffer, D_002D0806,
                     func_001FFF90((s32)D_002D07FA), D_00325CB0);
        fd = func_0017FA98(buffer, 1);
        if (fd < 0) {
            break;
        }
        func_0017FD20(fd);
        D_00325CB0 += 1;
    }
    D_00325CB0 += 1;
    fd = func_0017FA98(buffer, 0x202);
    if (fd >= 0) {
        s32 y;
        u16 *row;

        func_00180348(fd, &fileHeader, 0xE);
        func_00180348(fd, &info, 0x28);
        y = 0x1BF;
        row = (u16 *)0x0408BB00;
        do {
            s32 x;
            u16 *src;
            u8 *dst;

            dst = buffer;
            x = 0;
            src = row;
            do {
                x += 1;
                dst[0] = ((*src >> 7) & 0xF8) | ((*src >> 12) & 7);
                dst[1] = ((*src >> 2) & 0xF8) | ((*src >> 7) & 7);
                dst[2] = ((*src << 3) & 0xF8) | ((*src >> 2) & 7);
                src++;
                dst += 3;
            } while (x < 0x280);
            func_00180348(fd, buffer, 0x780);
            y -= 1;
            row -= 0x280;
        } while (y >= 0);
        func_0017FD20(fd);
    }
}

typedef struct {
    f32 x, y, z, w;
} Vec4_00205440;

typedef union {
    struct {
        u16 x;
        u16 y;
    } xy;
    struct {
        u64 xy : 32;
        u64 z : 24;
        u64 f : 8;
    } bits;
} Xyz_00205440;


s32 func_00205440(s32 arg0, void *arg1, u16 *arg2, s32 *arg3) {
    extern s64 func_001A23B0(f32);
    f32 mtx[16];
    Vec4_00205440 v;
    f32 inv;

    v = *(Vec4_00205440 *)arg0;
    if (arg1 == NULL) {
        func_0020EB40(mtx);
        arg1 = mtx;
    }
    func_0020BAF0((s32)arg1);
    v.w = 1.0f;
    func_0020CDD0(&v, NULL, &v);
    func_0020BB50();
    inv = 1.0f / v.w;
    v.x *= inv;
    v.y *= inv;
    v.z *= inv;
    if (v.z < 1.0f || !(v.z <= 16777215.0f) || v.x < 0.0f || !(v.x <= 4095.0f) ||
        v.y < 0.0f || !(v.y <= 4095.0f)) {
        return 0;
    }
    ((Xyz_00205440 *)arg2)->xy.x = func_001A23B0(16.0f * v.x);
    ((Xyz_00205440 *)arg2)->xy.y = func_001A23B0(16.0f * v.y);
    ((Xyz_00205440 *)arg2)->bits.z = func_001A23B0(v.z);
    if (arg3 != NULL) {
        *(f32 *)arg3 = v.w;
    }
    return 1;
}

typedef union Vertex_00205630 {
    struct {
        u16 x;
        u16 y;
        u32 zflags;
    } coords;
    struct {
        u64 x : 16;
        u64 y : 16;
        u64 z : 24;
        u64 flags : 8;
    } bits;
} Vertex_00205630;

void func_0020CF00(s32, s32, s32, s32);

s32 func_00205630(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 *arg4) {
    extern s64 func_001A23B0(f32);
    f32 matrix[4][4];
    f32 *input = (f32 *)arg0;
    Vertex_00205630 *vertex = (Vertex_00205630 *)(arg3 + 0x10);
    u64 *tags = (u64 *)(arg3 + 8);
    u64 flags = *tags;
    s32 count = 0;
    u16 length = *(u16 *)arg3;
    f32 sum = 0.0f;
    s32 i;

    if (arg2 == 0) {
        func_0020EB40(matrix);
        arg2 = (s32)matrix;
    }
    for (i = 0; i < length; i++, flags >>= 4) {
        if ((flags & 0xF) == 4) {
            input[3] = 1.0f;
            input += 4;
            count++;
        }
    }
    func_0020BAF0(arg2);
    func_0020CF00(arg1, 0, arg0, count);
    func_0020BB50();

    flags = *tags;
    for (i = 0; i < length; i++, vertex++, flags >>= 4) {
        if ((flags & 0xF) == 4) {
            f32 *output = (f32 *)arg1;
            f32 reciprocal = 1.0f / output[3];
            output[0] *= reciprocal;
            output[1] *= reciprocal;
            output[2] *= reciprocal;
            if (output[2] < 1.0f || !(output[2] <= 16777215.0f) ||
                output[0] < 0.0f || !(output[0] <= 4095.0f) ||
                output[1] < 0.0f || !(output[1] <= 4095.0f)) {
                return 0;
            }
            vertex->coords.x = func_001A23B0(16.0f * output[0]);
            vertex->coords.y = func_001A23B0(16.0f * output[1]);
            vertex->bits.z = func_001A23B0(output[2]);
            sum += output[3];
            arg1 += 0x10;
        }
    }
    if (arg4 != NULL) {
        *arg4 = sum / (f32)count;
    }
    return 1;
}

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

typedef struct Vec4_00205E70 {
    f32 x, y, z, w;
} Vec4_00205E70;

extern Vec4_00205E70 D_00293D60;
extern Vec4_00205E70 D_00293D70;

s32 func_00205E70(s32 count, void *arg1, f32 *normal) {
    Vec4_00205E70 *points = arg1;
    s32 i;
    Vec4_00205E70 *p0;
    Vec4_00205E70 *p1;
    Vec4_00205E70 *p2;
    Vec4_00205E70 a;
    Vec4_00205E70 b;
    Vec4_00205E70 c;

    normal[0] = 0.0f;
    normal[1] = 0.0f;
    normal[2] = 0.0f;
    normal[3] = 0.0f;
    if (count < 3) {
        return 0;
    }
    for (i = 0; i < count; i++) {
        p0 = &points[i % count];
        p1 = &points[(i + 1) % count];
        p2 = &points[(i + 2) % count];
        a = D_00293D60;
        a.x = p1->x - p0->x;
        a.y = p1->y - p0->y;
        a.z = p1->z - p0->z;
        b = D_00293D70;
        b.x = p2->x - p1->x;
        b.y = p2->y - p1->y;
        b.z = p2->z - p1->z;
        func_0020D140(&c.x, &a.x, &b.x);
        normal[0] += c.x;
        normal[1] += c.y;
        normal[2] += c.z;
    }
    normal[0] /= (f32)count;
    normal[1] /= (f32)count;
    normal[2] /= (f32)count;
    func_0020D070(normal);
    return 1;
}

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

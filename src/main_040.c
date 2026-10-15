#include "common.h"

s32 func_001BA3B0(s32 arg0, s32 arg1) {
    s32 count;
    s32 card;

    count = func_00215F90(arg0, arg1);
    card = func_002159D0(arg0, arg1);
    return (count >= 0x28 && card != 0x3E7) ? 1 : 0;
}

typedef struct Data_001BA420 {
    u8 padding0[9];
    u8 unused0 : 6;
    u8 valid : 1;
    u8 unused1 : 1;
    u8 paddingA[2];
    u8 bytes[8];
} Data_001BA420;

extern s8 D_002BEF79[];

s32 func_001BA420(u8 *arg0) {
    s8 *offsets = D_002BEF79;
    s32 index;
    u8 decoded[8];
    s32 byte;
    Data_001BA420 *entry;
    u8 *out;

    index = 0;
    do {
        entry = (Data_001BA420 *)func_001DD0E0(index);
        if (entry != NULL && entry->valid) {
            out = decoded;
            byte = 0;
            do {
                *out = (entry->bytes[byte] + offsets[(index + byte) % 8] + 256) % 256;
                if (*out != arg0[byte]) {
                    break;
                }
                byte++;
                out++;
            } while (byte < 8);
            if (byte >= 8) {
                return index;
            }
        }
        index++;
    } while (index < 0x356);
    return -1;
}

typedef struct Entry_001BA520 {
    s16 id;
    u8 state;
    u8 value : 5;
    s8 flag5 : 1;
    s8 flag6 : 1;
    s8 flag7 : 1;
} Entry_001BA520;

extern Entry_001BA520 *D_00317B60;

s32 func_001BA520(s32 arg0, s32 arg1, s64 arg2, s64 arg3, s64 arg4) {
    Entry_001BA520 *entry;
    s32 i;

    entry = D_00317B60;
    i = 0;
    do {
        if (entry->state == 0) {
            entry->id = arg0;
            entry->value = arg1;
            entry->flag5 = (s8)arg2;
            entry->flag6 = (s8)arg3;
            entry->flag7 = (s8)arg4;
            entry->state = 0x80;
            return 1;
        }
        i++;
        entry++;
    } while (i < 8);
    return 0;
}

void func_001BA5F0(void) {
    func_00199BC0(D_00317B68, 0x356, 2, func_001BA630);
}

void func_001BA610(void) {
    func_00199BC0(D_00317B6C + 2, 0x28, 2, func_001BA710);
}

extern s32 (*D_00291330[])(s32, s32);

static inline s32 check_001BA630(u8 *data, s32 i) {
    s32 j;

    for (j = 0; j < i; j++) {
        if (data[i + 0xCB6] == data[j + 0xCB6]) {
            break;
        }
    }
    return j < i;
}

s32 func_001BA630(s32 arg0, s32 arg1) {
    u8 *data = D_00317490.b;
    s32 i;
    s32 result = 0;

    i = 0;
    do {
        if (i == 0 || !check_001BA630(data, i)) {
            result = D_00291330[data[i + 0xCB6]](arg0, arg1);
            if (result != 0) {
                break;
            }
        }
        i++;
    } while (i < 3);
    return result;
}

s32 func_001BA710(s32 arg0, s32 arg1) {
    u8 *base = D_00317490.b;
    s32 i;
    s32 j;
    s32 result = 0;

    i = 0;
    do {
        if (i != 0) {
            for (j = 0; j < i; j++) {
                if ((base + i)[0xCB9] == (base + j)[0xCB9]) {
                    break;
                }
            }
            if (j < i) {
                continue;
            }
        }
        result = D_00291330[(base + i)[0xCB9]](arg0, arg1);
        if (result != 0) {
            break;
        }
    } while (++i < 3);
    return result;
}

s32 func_001BA7F0(u16 *arg0, u16 *arg1) {
    s32 temp_s0;
    s32 temp_s1;
    s32 var_s2;
    s32 var_a0;
    s32 temp_v1;
    s32 ret;

    temp_v1 = *arg0;
    temp_s0 = D_003181EC;
    temp_s1 = *arg1;
    if (temp_v1 == 0x3E7) {
        var_s2 = 2;
    } else {
        var_s2 = func_00216920(temp_s0, temp_v1) ? 0 : 1;
    }
    if (temp_s1 == 0x3E7) {
        var_a0 = 2;
    } else {
        var_a0 = func_00216920(temp_s0, temp_s1) ? 0 : 1;
    }
    if (var_a0 < var_s2) {
        ret = 1;
    } else {
        ret = (var_s2 < var_a0) ? -1 : 0;
    }
    return ret;
}

static inline s64 value_001BA8A0(u8 *entry) {
    if (entry != NULL) {
        return (s32)*entry;
    }
    return 0x7FFFFFFF;
}

s32 func_001BA8A0(u16 *arg0, u16 *arg1) {
    s64 var_v0;
    s64 var_v1;
    s32 temp_s0;
    u8 *temp_s0_2;
    u8 *temp_v0;

    temp_s0 = *arg1;
    temp_s0_2 = func_001DD0E0(*arg0);
    temp_v0 = func_001DD0E0(temp_s0);
    var_v1 = value_001BA8A0(temp_s0_2);
    var_v0 = value_001BA8A0(temp_v0);
    if (var_v0 < var_v1) {
        return 1;
    }
    return (var_v1 < var_v0) ? -1 : 0;
}

typedef struct {
    u8 pad[0x6D4];
    u16 *values;
} Data_001BA930;

s32 func_001BA930(u16 *arg0, u16 *arg1) {
    Data_001BA930 *data = (Data_001BA930 *)D_00317490.b;
    s32 temp_a1;
    s64 var_a2;
    s64 var_v0;
    s32 temp_v1;
    s32 ret;

    temp_v1 = *arg0;
    temp_a1 = *arg1;
    if (temp_v1 == 0x3E7) {
        var_a2 = 0x7FFFFFFF;
    } else {
        var_a2 = (s32) data->values[temp_v1];
    }
    if (temp_a1 == 0x3E7) {
        var_v0 = 0x7FFFFFFF;
    } else {
        var_v0 = (s32) data->values[temp_a1];
    }
    if (var_v0 < var_a2) {
        ret = 1;
    } else {
        ret = (var_a2 < var_v0) ? -1 : 0;
    }
    return ret;
}

s32 func_001BA9C0(u16 *arg0, u16 *arg1) {
    s32 var_v0;
    s32 var_v1;
    s32 temp_s0;
    u8 *temp_s0_2;
    u8 *temp_v0;

    temp_s0 = *arg1;
    temp_s0_2 = func_001DD0E0(*arg0);
    temp_v0 = func_001DD0E0(temp_s0);
    var_v1 = -1;
    if (temp_s0_2 != NULL) {
        var_v1 = *(u16 *)(temp_s0_2 + 8) & 0x1FFF;
    }
    var_v0 = (temp_v0 != NULL) ? (*(u16 *)(temp_v0 + 8) & 0x1FFF) : -1;
    if (var_v1 < var_v0) {
        var_v0 = 1;
    } else {
        var_v0 = (var_v0 < var_v1) ? -1 : 0;
    }
    return var_v0;
}

s32 func_001BAA30(u16 *arg0, u16 *arg1) {
    s32 var_v0;
    s32 var_v1;
    s32 result;
    s32 temp_s0;
    u8 *temp_s0_2;
    u8 *temp_v0;

    temp_s0 = *arg1;
    temp_s0_2 = func_001DD0E0(*arg0);
    temp_v0 = func_001DD0E0(temp_s0);
    var_v1 = -1;
    if (temp_s0_2 != NULL) {
        var_v1 = *(u16 *)(temp_s0_2 + 0xA) & 0x1FFF;
    }
    if (temp_v0 != NULL) {
        var_v0 = *(u16 *)(temp_v0 + 0xA) & 0x1FFF;
    } else {
        var_v0 = -1;
    }
    if (var_v1 < var_v0) {
        result = 1;
    } else {
        result = (var_v0 < var_v1) ? -1 : 0;
    }
    return result;
}

s32 func_001BAAA0(u16 *arg0, u16 *arg1) {
    u8 *card0;
    u8 *card1;
    s32 rank0;
    s32 rank1;
    s32 cardId1;

    cardId1 = *arg1;
    card0 = func_001DD0E0(*arg0);
    card1 = func_001DD0E0(cardId1);
    rank0 = 0x7FFFFFFF;
    rank1 = 0x7FFFFFFF;
    if (card0 != NULL) {
        rank0 = func_001DE0B0((s32) card0[0] >> 5, card0[2] & 0xF);
    }
    if (card1 != NULL) {
        rank1 = func_001DE0B0((s32) card1[0] >> 5, card1[2] & 0xF);
    }
    if (rank1 < rank0) {
        return 1;
    }
    return (rank0 < rank1) ? -1 : 0;
}

typedef struct Info_001BAB60 {
    u8 padding[2];
    u8 low : 4;
    u8 rank : 4;
} Info_001BAB60;

static inline s64 rank_001BAB60(void *entry) {
    if (entry != NULL) {
        return (s32)((Info_001BAB60 *)entry)->rank;
    }
    return 0x7FFFFFFF;
}

s32 func_001BAB60(u16 *arg0, u16 *arg1) {
    s64 var_v0;
    s64 var_v1;
    s32 temp_s0;
    u8 *temp_s0_2;
    u8 *temp_v0;
    s32 result;

    temp_s0 = *arg1;
    temp_s0_2 = func_001DD0E0(*arg0);
    temp_v0 = func_001DD0E0(temp_s0);
    var_v1 = rank_001BAB60(temp_s0_2);
    var_v0 = rank_001BAB60(temp_v0);
    if (var_v0 < var_v1) {
        result = 1;
    } else if (var_v1 < var_v0) {
        result = -1;
    } else {
        result = 0;
    }
    return result;
}

s32 func_001BAC00(u16 *arg0, u16 *arg1) {
    s64 var_v0;
    s64 var_v1;
    s32 temp_s0;
    u8 *temp_s0_2;
    u8 *temp_v0;

    temp_s0 = *arg1;
    temp_s0_2 = func_001DD0E0(*arg0);
    temp_v0 = func_001DD0E0(temp_s0);
    if (temp_s0_2 != NULL) {
        var_v1 = (s32) temp_s0_2[3];
    } else {
        var_v1 = 0x7FFFFFFF;
    }
    if (temp_v0 != NULL) {
        var_v0 = (s32) temp_v0[3];
    } else {
        var_v0 = 0x7FFFFFFF;
    }
    if (var_v0 < var_v1) {
        return 1;
    }
    return (var_v1 < var_v0) ? -1 : 0;
}

s32 func_001BAC90(u16 *arg0, u16 *arg1) {
    extern s64 func_00215D30(u8, s32);
    u8 temp_s0;
    s32 temp_s1;
    s32 var_s2;
    s32 var_v0;
    s32 temp_v1;

    temp_v1 = *arg0;
    temp_s0 = D_003181EC;
    temp_s1 = *arg1;
    if ((s32) temp_v1 >= 0x2AB) {
        var_s2 = 0x7FFFFFFF;
    } else {
        var_s2 = (s32) func_00215D30(temp_s0, temp_v1);
    }
    if ((s32) temp_s1 >= 0x2AB) {
        var_v0 = 0x7FFFFFFF;
    } else {
        var_v0 = (s32) func_00215D30(temp_s0, temp_s1);
    }
    if (var_v0 < var_s2) {
        return 1;
    }
    return (var_s2 < var_v0) ? -1 : 0;
}

s32 func_001BAD40(u16 *arg0, u16 *arg1) {
    s32 type0;
    s32 type1;
    s32 id1;
    u8 *card0;
    u8 *card1;
    s32 result;

    id1 = *arg1;
    card0 = func_001DD0E0(*arg0);
    card1 = func_001DD0E0(id1);

    type0 = card0 != NULL ? card0[0] >> 5 : 0x7FFFFFFFLL;
    type1 = card1 != NULL ? card1[0] >> 5 : 0x7FFFFFFFLL;

    if (type0 != 0x7FFFFFFFLL) {
        if (type0 != 0 || *(u16 *)(card0 + 4) == 0xFFFF) {
            type0 += 6;
        }
    }
    if (type1 != 0x7FFFFFFFLL) {
        if (type1 != 0 || *(u16 *)(card1 + 4) == 0xFFFF) {
            type1 += 6;
        }
    }
    if (type1 < type0) {
        result = 1;
    } else {
        result = type0 < type1 ? -1 : 0;
    }
    return result;
}

s32 func_001BAE40(u16 *arg0, u16 *arg1) {
    u16 temp_v1;
    u16 temp_v0;
    s32 result;

    temp_v1 = *arg0;
    temp_v0 = *arg1;
    if ((s32) temp_v1 > (s32) temp_v0) {
        result = 1;
    } else {
        result = ((s32) temp_v1 < (s32) temp_v0) ? -1 : 0;
    }
    return result;
}

void func_001BAE70(void) {
    func_00209D30(func_001BAEA0(func_00209D20()));
}

s32 func_001BAEA0(s32 arg0) {
    extern s16 D_00318122;
    extern void func_0020A470();
    extern s32 func_001BB6D0();
    extern s32 func_001BF710();
    extern s32 func_001BDAF0();
    extern s32 func_001BB940();
    extern s32 func_001BC350();
    extern s32 func_001C02E0();
    extern s32 func_001C05F0();
    extern s32 func_001C0A30();
    extern s32 func_001C0EE0();
    extern s32 func_001C0F70();
    extern s32 func_001C1000();
    u8 *state;
    s32 player;
    s32 flag;
    s32 value;
    s32 position;
    s32 result;

    player = D_003181EC;
    state = D_00317490.b;
    func_0020A470(5, 2, 0x32);
    arg0 = (s32)func_0020A610((void *)arg0);
    value = func_001BB6D0(
        func_00209F70((void *)func_001BB260((s32)func_00209F70(
                          (void *)func_001AEFD0((s32)func_0020A760(func_0020A870((u8 *)arg0, NULL)), 2),
                          0xFF000000)),
                      0),
        D_00318122, 0);
    if (D_00318122 > 0x140) {
        value = func_001BF710(value, *(s16 *)(state + 0xC92), 0);
    }
    if (*(s16 *)(state + 0xC92) > 0) {
        if (state[0xD5D] == 0) {
            flag = 0;
            position = state[0xD61] + (state[0xD60] + state[0xD62]) * 10;
            if (func_00216AC0(player, position, -1) > 0) {
                flag = 1;
            }
            if (func_00216BC0(player, position) != 0) {
                flag = 1;
            }
            if (flag != 0) {
                value = func_001BDAF0(value, position, *(s16 *)(state + 0xC92), 0, 0, 0, 0, 1);
            }
        } else {
            value = func_001BDAF0(value,
                                   (*(u16 **)(state + 0x6D8))[*(u16 *)(state + 0xC8A) + state[0xD5E]],
                                   *(s16 *)(state + 0xC92), 0, 0, (state[0xD5D] == 1) ? 1 : 0, 0, 1);
        }
    }
    if (*(s16 *)(state + 0xC92) > -0x140 && *(s16 *)(state + 0xC92) < 0x280) {
        value = func_001BB940(value, *(s16 *)(state + 0xC92), 0);
    }
    if (*(s16 *)(state + 0xC92) < 0x140) {
        value = func_001BC350(value, *(s16 *)(state + 0xC92), 0);
    }
    if (*(s16 *)(state + 0xC92) < 0) {
        value = func_001BDAF0(value,
                               (*(u16 **)(state + 0x6DC))[*(u16 *)(state + 0xC8E) + state[0xD5F]],
                               *(s16 *)(state + 0xC92), 0, 1, (state[0xD5D] == 6) ? 1 : 0, 0, 0);
    }
    result = func_001BCCE0(value, *(s16 *)(state + 0xC92), 0);
    switch (state[0xD5D]) {
    case 2:
    case 3:
        result = func_001BFF00(result, *(s16 *)(state + 0xC92), 0, state[0xD5E]);
        break;
    case 4:
    case 5:
        result = func_001C02E0(result, *(s16 *)(state + 0xC92), 0, state[0xD5F]);
        break;
    case 7:
        result = func_001C05F0(result, 0, 0);
        break;
    case 8:
        result = func_001C07E0(result, 0, 0);
        break;
    case 9:
        result = func_001C0A30(result, 0, 0);
        break;
    case 10:
        result = func_001C0CE0(result, 0, 0);
        break;
    case 11:
        result = func_001C0EE0(result, 0, 0);
        break;
    case 12:
        result = func_001C0F70(result, 0, 0);
        break;
    case 13:
        result = func_001C1000(result, 0, 0);
        break;
    }
    func_001FEAF0(0);
    func_0020A9E0();
    return result;
}

typedef struct {
    u16 count;
    u16 flags;
    u32 padding;
    u64 registers;
} Tag_001BB260;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Color_001BB260;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Vertex_001BB260;

typedef struct {
    Color_001BB260 color;
    Vertex_001BB260 xyz;
} Point_001BB260;

typedef struct {
    u64 tag[2];
    Point_001BB260 points[4];
    u64 end;
} Packet_001BB260;

typedef struct {
    u8 b, g, r, a;
} Source_001BB260;

static inline void set_color_001BB260(Color_001BB260 *a, Color_001BB260 *b,
                                      Source_001BB260 *src) {
    a->r = b->r = src->r;
    a->g = b->g = src->g;
    a->b = b->b = src->b;
    a->a = b->a = src->a;
    a->q = b->q = 1.0f;
}

static inline void set_xyz_001BB260(Vertex_001BB260 *v, s32 x, s32 y) {
    v->x = (x + 0x6C0) << 4;
    v->y = (y + 0x720) << 4;
    v->z = D_003180E8;
    v->fog = 0;
}

s32 func_001BB260(s32 arg0) {
    extern u8 D_002BE850[];
    Source_001BB260 *colors = (Source_001BB260 *)D_002BE850;
    s32 width = 0x140;
    s32 height = 0x1C0;
    Packet_001BB260 packet __attribute__((aligned(8)));

    ((Tag_001BB260 *)packet.tag)->flags = 0x14;
    ((Tag_001BB260 *)packet.tag)->count = 8;
    ((Tag_001BB260 *)packet.tag)->registers = 0x41414141;
    ((Tag_001BB260 *)packet.tag)->padding = 0;
    set_color_001BB260(&packet.points[0].color, &packet.points[2].color, &colors[0]);
    set_color_001BB260(&packet.points[1].color, &packet.points[3].color, &colors[1]);
    set_xyz_001BB260(&packet.points[0].xyz, 0, 0);
    set_xyz_001BB260(&packet.points[1].xyz, width, 0);
    set_xyz_001BB260(&packet.points[2].xyz, 0, height);
    set_xyz_001BB260(&packet.points[3].xyz, width, height);
    arg0 = func_00207650(arg0, (s32)packet.tag, 0, 0);
    set_color_001BB260(&packet.points[0].color, &packet.points[2].color, &colors[1]);
    set_color_001BB260(&packet.points[1].color, &packet.points[3].color, &colors[0]);
    set_xyz_001BB260(&packet.points[0].xyz, width, 0);
    set_xyz_001BB260(&packet.points[1].xyz, width * 2, 0);
    set_xyz_001BB260(&packet.points[2].xyz, width, height);
    set_xyz_001BB260(&packet.points[3].xyz, width * 2, height);
    return func_00207650(arg0, (s32)packet.tag, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/main_040", func_001BB6D0);

INCLUDE_ASM("asm/nonmatchings/main_040", func_001BB940);

INCLUDE_ASM("asm/nonmatchings/main_040", func_001BC350);

typedef struct Entry_001BCCE0 {
    u16 id;
    u8 progress;
    struct {
        u8 index : 5;
        s8 swap : 1;
        s8 mode : 1;
        s8 reverse : 1;
    } flags;
} Entry_001BCCE0;

extern struct Entry_001BA520 *D_00317B60;

s32 func_001BCCE0(s32 arg0, s32 arg1, s32 arg2) {
    Entry_001BCCE0 *entry;
    s32 lower;
    s32 upper;
    s32 i;
    s32 result;
    s32 to;
    s32 from;
    s32 remaining;
    u8 progress;
    u8 amount;

    result = arg0;
    entry = (Entry_001BCCE0 *)D_00317B60;
    lower = arg1 + 8;
    upper = arg1 + 0x148;
    i = 0;
    do {
        progress = entry->progress;
        if (progress != 0) {
            amount = progress;
            if (entry->flags.reverse != 0) {
                amount = 0x80 - progress;
            }
            if (entry->flags.swap != 0) {
                to = lower;
                from = upper;
            } else {
                to = upper;
                from = lower;
            }
            result = func_001BD8A0(result, entry->id,
                from + (((progress & 0xFF) * (to - from)) >> 7),
                arg2 + 0x70 + entry->flags.index * 0x36,
                entry->flags.mode, amount);
            remaining = entry->progress - 0x10;
            entry->progress = remaining > 0 ? remaining : 0;
        }
        i++;
        entry++;
    } while (i < 8);
    return result;
}

typedef struct {
    u16 count;
    u16 flags;
    u32 padding;
    u64 registers;
} Tag_001BCE20;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Color_001BCE20;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Vertex_001BCE20;

typedef struct {
    u64 tag[2];
    Color_001BCE20 color;
    Vertex_001BCE20 vertex0;
    Vertex_001BCE20 vertex1;
    u64 end;
} Box_001BCE20;

typedef struct {
    u8 kind;
    u8 pad1;
    u8 attribute : 4;
    u8 level : 4;
    u8 stars;
    u16 link;
    u8 pad6[2];
    u16 attack;
    u16 defense;
} Card_001BCE20;

void *func_001BCE20(void *arg0, s32 card, s32 x, s32 y, s32 flag, s32 flag2) {
    extern s32 *func_001FEAB0(s32);
    extern s32 func_001FE660(s32, s32, s32, s32, f32, f32, s32, void (*)(void));
    extern s32 func_001B6F70(s32, s32, s32, s32, s32, s32, s8 *, s32);
    extern s32 func_001B6EA0(s32, s32, s32, s32, s32, s32, s32);
    extern s32 func_001B65F0(s32, s32, s32, s32, s32, s32, s32, s32);
    extern s32 func_001B4540(s32, s32, s32, s32, s32, s32);
    extern s32 func_001B3CC0(s32, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
    extern s32 func_001DE090(s32, s32);
    extern s32 func_001B4780(s32, s32, s32, s32, s32, s32, s32, s32, s32);
    extern s32 func_00215D30();
    extern u8 D_00290080[];
    extern u8 D_00290020[];
    extern char D_002BEFB7[];
    extern char D_002BE940[];
    extern char D_002BE948[];
    extern s32 D_00290A12;
    extern s32 D_002908E6;
    extern s32 D_002908BE;
    extern s32 D_002908C8;
    extern s32 D_002908F0;
    extern s32 D_0029086E;
    extern s32 D_00290878;
    extern s32 D_0029097C;
    extern s32 D_00290986;
    extern s32 D_00290990;
    s32 player = D_003181EC;
    u8 *state = D_00317490.b;
    s32 id = (s32)arg0;
    Card_001BCE20 *data;
    s32 level;
    s32 rank;
    s32 w;
    u8 *sprite;
    s32 kind;
    s32 attr;
    s32 hint = 0;
    s8 *text;
    s32 px;
    s32 py;
    f32 scale;
    Box_001BCE20 box __attribute__((aligned(8)));
    s8 digit;

    data = (Card_001BCE20 *)func_001DD0E0(card);
    level = func_002158B0(player);
    scale = 1.0f;
    if (data == NULL) {
        return (void *)func_001B4780(id, flag ? 6 : -1, -1, 9, x, y, -0x130, -0x36, flag);
    }
    kind = data->kind >> 5;
    attr = data->kind & 0x1F;
    if (kind == 0) {
        sprite = D_00290080 + attr * 10;
    } else {
        sprite = D_00290080 + (kind + 0x14) * 10;
    }
    attr = func_001DE020(kind);
    rank = func_001DE090(attr, data->attribute);
    if (attr == 0 && data->link != 0xFFFF) {
        attr = 4;
    }
    id = func_0020F290(func_001FD680(id, 1, func_001DE210(card), 0, 0x16));
    id = func_001B4780(id, flag ? 6 : attr + 7, -1, 9, x, y, -0x130, -0x36, flag);
    if (func_00216920(player, card) != 0) {
        id = func_001B3CC0(id, &D_00290A12, x + 0x6C8, y + 0x727, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    } else {
        id = func_001B6EA0(id, x + 8, y + 7, 1, 0, 3, card);
    }
    if (kind == 0) {
        id = func_001B4540(id, x + 0x28, y + 3, func_00215D30(player, card), 0, 0);
    }
    id = func_001B3CC0(id, sprite, x + 0x6C4, y + 0x73A, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    id = func_001B3CC0(id, D_00290020 + rank * 10, x + 0x6DE, y + 0x73A, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    if (flag) {
        text = D_002BEFB7;
        px = x + 0xA0;
        py = y + 0x25;
        id = func_001B6F70(id, px, py, 0, 2, func_0019BEF0((char *)text), text, hint != 0 ? (s32)D_002BE944 : 0);
        id = func_001B3CC0(id, D_00290080 + (level + 0xE3) * 10, x + 0x7C7, y + 0x730, 0, 1,
                           0, 0, 0, 0, 1, 0, -1, 0x80);
    } else {
        if (kind == 0) {
            id = func_001B3CC0(id, &D_002908E6, x + 0x6F8, y + 0x743, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
            id = func_001B6EA0(id, x + 0x4E, y + 0x25, 1, 0, 2, data->level);
            id = func_001B3CC0(id, &D_002908BE, x + 0x7B8, y + 0x723, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
            id = func_001B6EA0(id, x + 0x108, y + 5, 1, 0, 4, data->attack & 0x1FFF);
            id = func_001B3CC0(id, &D_002908C8, x + 0x7B8, y + 0x733, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
            id = func_001B6EA0(id, x + 0x108, y + 0x15, 1, 0, 4, data->defense & 0x1FFF);
        }
        id = func_001B3CC0(id, &D_002908F0, x + 0x728, y + 0x743, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
        id = func_001B6EA0(id, x + 0x7E, y + 0x25, 1, 0, 3, data->stars);
        px = x + 0x76D;
        py = y + 0x743;
        if (func_00216AC0(player, card, -1) < 9) {
            id = func_001B3CC0(id, &D_0029086E, px, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
        } else {
            id = func_001B3CC0(id, &D_00290878, px, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
        }
        px = x + 0xC0;
        py = y + 0x25;
        id = func_001B6EA0(id, px, py, 1, 0, 1, func_00216AC0(player, card, hint != 0 ? -1 : 3));
        id = func_001B3CC0(id, &D_0029097C, x + 0x78D, y + 0x743, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
        px = x + 0xE0;
        py = y + 0x25;
        digit = func_00216AC0(player, card, 0) + '0';
        id = func_001B6F70(id, px, py, 1, 0, 1, &digit, hint != 0 ? (s32)D_002BE944 : 0);
        id = func_001B3CC0(id, &D_00290986, x + 0x7AD, y + 0x743, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
        px = x + 0x100;
        py = y + 0x25;
        digit = func_00216AC0(player, card, 1) + '0';
        id = func_001B6F70(id, px, py, 1, 0, 1, &digit, hint != 0 ? (s32)D_002BE944 : 0);
        id = func_001B3CC0(id, &D_00290990, x + 0x7CD, y + 0x743, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
        px = x + 0x120;
        py = y + 0x25;
        digit = func_00216AC0(player, card, 2) + '0';
        id = func_001B6F70(id, px, py, 1, 0, 1, &digit, hint != 0 ? (s32)D_002BE944 : 0);
    }
    px = x + 0x48;
    py = y + 3;
    id = func_001B65F0(id, flag ? 6 : attr + 7, px, py, -0xB0, -0x20, -1, 0);
    w = func_001FEAB0(1)[3];
    if (w > 0xA8) {
        scale = 168.0f / (f32)w;
    }
    id = func_001FE660(id, 1, x + 0x4E, y + 9, scale, 1.0f, (s32)D_002BE940, func_001FDFE0);
    id = func_001FE660(id, 1, x + 0x4D, y + 8, scale, 1.0f, (s32)D_002BE944, func_001FDFE0);
    id = func_001FE660(id, 1, x + 0x4C, y + 7, scale, 1.0f, (s32)D_002BE948, func_001FDFE0);
    func_001FEAF0(1);
    if (flag2 != 0 && func_00216AC0(player, card, 3) <= 0) {
        ((Tag_001BCE20 *)box.tag)->flags = 6;
        ((Tag_001BCE20 *)box.tag)->count = 3;
        ((Tag_001BCE20 *)box.tag)->registers = 0x441;
        ((Tag_001BCE20 *)box.tag)->padding = 0;
        func_002086D0(box.tag, func_00208D00(2));
        box.color.r = 0x80;
        box.color.g = 0x80;
        box.color.b = 0x80;
        box.color.a = 0x40;
        box.color.q = 1.0f;
        box.vertex0.x = (x + 0x6C0) << 4;
        box.vertex0.y = (y + 0x720) << 4;
        box.vertex0.z = *(s32 *)(state + 0xC58);
        box.vertex0.fog = 0;
        box.vertex1.x = (x + 0x7F0) << 4;
        box.vertex1.y = (y + 0x756) << 4;
        box.vertex1.z = *(s32 *)(state + 0xC58);
        box.vertex1.fog = 0;
        id = func_00207650(id, (s32)box.tag, 0, 0);
    }
    return (void *)id;
}

typedef struct {
    u16 count;
    u16 flags;
    u32 padding;
    u64 registers;
} Tag_001BD8A0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Color_001BD8A0;

typedef struct {
    u64 u : 14;
    u64 pad0 : 2;
    u64 v : 14;
    u64 pad1 : 34;
} UV_001BD8A0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Vertex_001BD8A0;

typedef struct {
    u64 tag[2];
    Color_001BD8A0 color;
    u64 uv0;
    Vertex_001BD8A0 vertex0;
    u64 uv1;
    Vertex_001BD8A0 vertex1;
    u64 test;
    s64 texture0;
    s64 texture1;
    u64 clamp;
} Packet_001BD8A0;

static inline void set_uv_001BD8A0(UV_001BD8A0 *p, s32 u, s32 v) {
    p->u = u;
    p->v = v;
}


s32 func_001BD8A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8 arg5) {
    Packet_001BD8A0 packet __attribute__((aligned(8)));
    s32 width = 0x130;
    s32 height = 0x36;
    s32 x;
    s32 y;
    void *texture;
    s32 output;

    ((Tag_001BD8A0 *)packet.tag)->flags = 0x26;
    ((Tag_001BD8A0 *)packet.tag)->count = 5;
    ((Tag_001BD8A0 *)packet.tag)->registers = 0x42421;
    ((Tag_001BD8A0 *)packet.tag)->padding = 0;
    ((Tag_001BD8A0 *)packet.tag)->flags |= 0x800;
    func_002086D0(packet.tag, 0x44 | ((s64)0x80 << 32));
    packet.color.r = 0x80;
    packet.color.g = 0x80;
    packet.color.b = 0x80;
    packet.color.a = arg5;
    packet.color.q = 1.0f;

    arg0 = (s32)func_0020A610((void *)arg0);
    texture = func_001BCE20(func_0020A870((u8 *)arg0, 0), arg1, 0, 0, arg4, 0);
    func_0020AA30(&packet.texture0, &packet.texture1);
    output = func_0020F290((s32)func_0020A760(texture));

    x = arg2 + 0x6C0;
    y = arg3 + 0x720;
    set_uv_001BD8A0((UV_001BD8A0 *)&packet.uv0, 0, 0);
    set_uv_001BD8A0((UV_001BD8A0 *)&packet.uv1, width << 4, height << 4);
    packet.vertex0.x = (x << 4) - 8;
    packet.vertex0.y = (y << 4) - 8;
    packet.vertex0.z = D_003180E8;
    packet.vertex0.fog = 0;
    packet.vertex1.x = ((x + width) << 4) - 8;
    packet.vertex1.y = ((y + height) << 4) - 8;
    packet.vertex1.z = D_003180E8;
    packet.vertex1.fog = 0;
    return func_00207650(output, (s32)packet.tag, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/main_040", func_001BDAF0);

INCLUDE_ASM("asm/nonmatchings/main_040", func_001BE5F0);

s32 func_001BF180(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    extern s32 func_001FE660(s32, s32, s32, s32, f32, f32, s32, void (*)(void));
    extern char D_002BE940[];
    s32 offset;
    s32 id;
    s32 *size;
    s32 x;
    s32 y;
    s32 result;
    f32 scaleX;
    f32 scaleY;

    if (arg4 != 0) {
        offset = 0x280;
    } else {
        offset = -0x140;
    }
    scaleX = 1.0f;
    scaleY = 1.0f;
    id = func_0020F290(func_001FD680(arg0, 1, arg1 + 0x496, 0, 0x16));
    size = func_001FEAB0(1);
    x = arg2 + offset + 0x1C;
    y = arg3 + 0x30;
    if (size[3] > 0x106) {
        scaleX = 262.0f / size[3];
    }
    if (size[4] > 0x100) {
        scaleY = 256.0f / size[4];
    }
    result = func_001FE660(id, 1, x, y, scaleX, scaleY, (s32)D_002BE940, func_001FDFE0);
    func_001FEAF0(1);
    return result;
}

INCLUDE_ASM("asm/nonmatchings/main_040", func_001BF2A0);

INCLUDE_ASM("asm/nonmatchings/main_040", func_001BF470);

INCLUDE_ASM("asm/nonmatchings/main_040", func_001BF710);

s32 func_001BFF00(s32 id, s32 arg1, s32 arg2, s32 arg3) {
    extern s32 func_001B6F70(s32, s32, s32, s32, s32, s32, s8 *, s32);
    extern s32 func_001B3CC0(s32, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
    extern char D_002BEFE7[];
    extern char D_002BEFEC[];
    extern char D_002BEFF3[];
    extern char D_002BEFFB[];
    extern s32 D_00290A62;
    extern s32 D_00290A58;
    extern s32 D_00290A4E;
    extern s32 D_00290A76;
    extern s32 D_00290864;
    extern u8 D_003181ED;
    u8 *state = D_00317490.b;
    s32 flag = (D_003181ED == 3) ? 1 : 0;
    s8 *text1 = D_002BEFE7;
    s8 *text2 = D_002BEFEC;
    s8 *text3 = D_002BEFF3;
    s8 *text4 = D_002BEFFB;
    s32 hint = 0;
    s32 x;
    s32 y;
    s32 sx;
    s32 sy;
    s32 px;
    s32 py;

    x = arg1 + 8;
    y = arg2 + 0x70 + arg3 * 0x36;
    sx = x + 0x6C0;
    sy = y + 0x720;
    id = func_001B4780(id, -1, 4, 6, x - 2, y - 2, -0x130, -0x36, 1);
    if (*(u16 *)(state + 0xC96) != 0) {
        return id;
    }
    id = func_001B4780(id, 0xD, -1, 7, x, y + 0x36, -0x130, -0x14, 1);
    px = sx + 5;
    py = sy + 0x38;
    id = func_001B3CC0(id, &D_00290A62, px, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    id = func_001B3CC0(id, &D_00290A58, px + 0x11, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    px = x + 0x2C;
    py = y + 0x3B;
    id = func_001B6F70(id, px, py, 1, 0, func_0019BEF0((char *)text1), text1,
                       hint != 0 ? (s32)D_002BE944 : 0);
    if (flag) {
        id = func_001B3CC0(id, &D_00290A4E, sx + 0x6B, sy + 0x38, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
        px = x + 0x81;
        id = func_001B6F70(id, px, py, 1, 0, func_0019BEF0((char *)text2), text2,
                           hint != 0 ? (s32)D_002BE944 : 0);
    } else {
        id = func_001B3CC0(id, &D_00290A4E, sx + 0x5B, sy + 0x38, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
        px = x + 0x71;
        id = func_001B6F70(id, px, py, 1, 0, func_0019BEF0((char *)text3), text3,
                           hint != 0 ? (s32)D_002BE944 : 0);
    }
    id = func_001B3CC0(id, &D_00290A76, sx + 0xC9, sy + 0x38, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    px = x + 0xDF;
    py = y + 0x3B;
    id = func_001B6F70(id, px, py, 1, 0, func_0019BEF0((char *)text4), text4,
                       hint != 0 ? (s32)D_002BE944 : 0);
    return func_001B3CC0(id, &D_00290864, sx + 0x11B, sy + 0x38, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
}

s32 func_001C02E0(s32 id, s32 arg1, s32 arg2, s32 arg3) {
    extern s32 func_001B6F70(s32, s32, s32, s32, s32, s32, s8 *, s32);
    extern s32 func_001B3CC0(s32, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
    extern char D_002BEFE7[];
    extern char D_002BEFEC[];
    extern char D_002BEFF3[];
    extern s32 D_00290A62;
    extern s32 D_00290A58;
    extern s32 D_00290A4E;
    extern u8 D_003181ED;
    u8 *state = D_00317490.b;
    s32 flag = (D_003181ED == 4) ? 1 : 0;
    s8 *text1 = D_002BEFE7;
    s8 *text2 = D_002BEFEC;
    s8 *text3 = D_002BEFF3;
    s32 hint = 0;
    s32 x;
    s32 y;
    s32 sx;
    s32 sy;
    s32 px;
    s32 py;

    x = arg1 + 0x148;
    y = arg2 + 0x70 + arg3 * 0x36;
    sx = x + 0x6C0;
    sy = y + 0x720;
    id = func_001B4780(id, -1, 4, 6, x - 2, y - 2, -0x130, -0x36, 1);
    if (*(u16 *)(state + 0xC96) != 0) {
        return id;
    }
    id = func_001B4780(id, 0xD, -1, 7, x, y + 0x36, -0x130, -0x14, 1);
    px = sx + 5;
    py = sy + 0x38;
    id = func_001B3CC0(id, &D_00290A62, px, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    id = func_001B3CC0(id, &D_00290A58, px + 0x11, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    px = x + 0x2C;
    py = y + 0x3B;
    id = func_001B6F70(id, px, py, 1, 0, func_0019BEF0((char *)text1), text1,
                       hint != 0 ? (s32)D_002BE944 : 0);
    if (flag) {
        id = func_001B3CC0(id, &D_00290A4E, sx + 0x6B, sy + 0x38, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
        px = x + 0x81;
        py = y + 0x3B;
        return func_001B6F70(id, px, py, 1, 0, func_0019BEF0((char *)text2), text2,
                             hint != 0 ? (s32)D_002BE944 : 0);
    } else {
        id = func_001B3CC0(id, &D_00290A4E, sx + 0x5B, sy + 0x38, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
        px = x + 0x71;
        py = y + 0x3B;
        return func_001B6F70(id, px, py, 1, 0, func_0019BEF0((char *)text3), text3,
                             hint != 0 ? (s32)D_002BE944 : 0);
    }
}

void func_001C05F0(s32 arg0, s32 arg1, s32 arg2) {
    extern s32 func_001B0CE0();
    extern s32 func_001B6F70();
    extern s32 func_001FE7D0();
    extern char D_002BEF9D[];
    extern u16 D_0031811A;
    extern u8 D_003181EE;
    s32 text0;
    char *text1;
    char *text2;
    s32 table;
    u8 *state;
    s32 icon;
    s32 res;
    s32 *info;

    state = D_00317490.b;
    text0 = (s32)D_002BEF9D;
    text1 = D_002BEF6F;
    text2 = D_002BEF73;
    table = *(u16 *)((u8 *)D_00317B68 + (D_0031811A + D_003181EE) * 2);
    icon = func_001DE210(table);
    arg0 = func_001B0CE0(arg0, 2, table, icon, arg1 + 0x140, arg2 + 0x48, -0x1CC, 0x130,
                         func_0019BEF0((char *)text0), text0, 0);
    res = func_0020F290(func_001FD680(arg0, 1, 0x92, 0, 0x16));
    info = func_001FEAB0(1);
    res = func_001FE7D0(res, 1, (arg1 + 0x140) - (info[3] >> 1), (arg2 + 0x154) - (info[4] + 0xC), 0,
                        func_001FDFE0);
    func_001FEAF0(1);
    res = func_001B6F70(res, arg1 + 0xCD, arg2 + 0x154, 2, 3, func_0019BEF0(text1), text1,
                        D_003181C6 != 0 ? 0 : (s32)D_002BE944);
    func_001B6F70(res, arg1 + 0x1B3, arg2 + 0x154, 2, 3, func_0019BEF0(text2), text2,
                  state[0xD36] != 0 ? (s32)D_002BE944 : 0);
}

s32 func_001C07E0(s32 arg0, s32 arg1, s32 arg2) {
    u8 *state;
    char *text;
    u16 *cards;
    s32 icon;
    s32 color0;
    s32 color1;
    s32 result;
    extern char D_002BEF9D;
    extern struct Entry_001BA520 *D_00317B60;
    extern s32 func_001B0CE0();
    extern s32 func_001B7D60();
    extern s32 func_002084D0();
    extern s64 func_00208680();

    state = D_00317490.b;
    text = &D_002BEF9D;
    cards = (u16 *)((u8 *)D_00317B60 + 0x20);
    icon = -1;
    if ((s32) D_003181C6 >= 0x80) {
        icon = 0x93;
        if ((s32)state[0xD57] < 3) {
            icon = func_001DE210(cards[(u8)state[0xD57]]);
        }
    }
    arg0 = func_001B0CE0(arg0, 2, -1, icon, arg1 + 0x140, arg2 + 0x5D,
                         -0x1CC, 0x106, func_0019BEF0(text),
                         text, (s32)state[0xD36] < 0x80 ? 0 : 1);
    if (state[0xD57] == 0) {
        arg0 = func_002084D0(arg0, ((s64)state[0xD36] << 14) | 0xA |
                                   ((s64)state[0xD36] << 34));
        color0 = color1 = state[0xD36];
    } else {
        color1 = color0 = 0x80;
    }
    arg0 = func_001B7D60(arg0, cards[0], arg1 + 0x74, arg2 + 0xBB,
                         color0, color1, *(s32 *)(state + 0xC58));
    if ((s32)state[0xD57] <= 0) {
        color0 = color1 = 0;
    } else if (state[0xD57] == 1) {
        arg0 = func_002084D0(arg0, ((s64)state[0xD36] << 14) | 0xA |
                                   ((s64)state[0xD36] << 34));
        color0 = color1 = state[0xD36];
    } else {
        color1 = color0 = 0x80;
    }
    arg0 = func_001B7D60(arg0, cards[1], arg1 + 0x100, arg2 + 0xBB,
                         color0, color1, *(s32 *)(state + 0xC58));
    if ((s32)state[0xD57] < 2) {
        color0 = color1 = 0;
    } else if (state[0xD57] == 2) {
        arg0 = func_002084D0(arg0, ((s64)state[0xD36] << 14) | 0xA |
                                   ((s64)state[0xD36] << 34));
        color0 = color1 = state[0xD36];
    } else {
        color1 = color0 = 0x80;
    }
    result = func_001B7D60(arg0, cards[2], arg1 + 0x18C, arg2 + 0xBB,
                           color0, color1, *(s32 *)(state + 0xC58));
    if ((s32)state[0xD57] < 3) {
        result = func_002084D0(result, func_00208680(0, 4));
    }
    return result;
}

INCLUDE_ASM("asm/nonmatchings/main_040", func_001C0A30);

s32 func_001C0CE0(s32 arg0, s32 arg1, s32 arg2) {
    s32 text;
    u16 *cards;
    s32 name;
    s32 width;
    s32 result;
    f32 scale;
    extern struct Entry_001BA520 *D_00317B60;
    extern s32 func_001B0CE0();
    extern s32 func_001B7D60();
    extern s32 func_001FE7D0();
    extern s32 func_001FE660(s32, s32, s32, s32, f32, f32, s32, void (*)(void));

    text = (s32)D_002BF002;
    cards = (u16 *)((u8 *)D_00317B60 + 0x20);
    name = func_001DE210(cards[0]);
    scale = 1.0f;
    arg0 = func_001B0CE0(arg0, 2, -1, -1, arg1 + 0x140, arg2 + 0x41, 0x1CC, 0x13E,
                         func_0019BEF0((char *)text), text, 1);
    result = func_0020F290(func_001FD680(func_001FD680(
        func_001B7D60(arg0, cards[0], arg1 + 0x100, arg2 + 0xB5, 0x80, 0x80, D_003180E8),
        1, 0x95, 0, 0x16), 2, name, 0, 0x42));
    result = func_001FE7D0(result, 1, (arg1 + 0x140) - (((s32 *)func_001FEAB0(1))[3] >> 1),
                           arg2 + 0x7D, 0, func_001FDFE0);
    width = ((s32 *)func_001FEAB0(2))[3];
    if (width > 0x1B4) {
        scale = 436.0f / (f32)width;
    }
    result = func_001FE660(result, 2, (arg1 + 0x140) - (s32)(((f32)width * scale) / 2.0f),
                           arg2 + 0x141, scale, 1.0f, 0, func_001FDFE0);
    func_001FEAF0(1);
    func_001FEAF0(2);
    return result;
}

void func_001C0EE0(s32 arg0, s32 arg1, s32 arg2) {
    s32 text = (s32)D_002BF002;

    func_001B0CE0(arg0, 2, -1, 0x96, arg1 + 0x140, arg2 + 0x8D,
                  0x1CC, 0xA6, func_0019BEF0((char *)text), text, 1);
}

void func_001C0F70(s32 arg0, s32 arg1, s32 arg2) {
    s32 text = (s32)D_002BF002;

    func_001B0CE0(arg0, 2, -1, 0x97, arg1 + 0x140, arg2 + 0x8D,
                  0x1CC, 0xA6, func_0019BEF0((char *)text), text, 1);
}

void func_001C1000(s32 arg0, s32 arg1, s32 arg2) {
    s32 text = (s32)D_002BEF67;

    func_001B0CE0(arg0, 2, -1, 0x7C, arg1 + 0x140, arg2 + 0xA3,
                  0x140, 0x7A, func_0019BEF0((char *)text), text, 1);
}

typedef struct {
    f32 x, y, z, w;
} Quad_001C1090;

typedef struct {
    Quad_001C1090 v[9];
} Block_001C1090;

typedef struct {
    f32 x, y, z;
} Vec3_001C1090;

extern Quad_001C1090 D_00291370;
extern Block_001C1090 D_00291380;
extern Quad_001C1090 D_00291410;
extern Vec3_001C1090 D_00291420;


void func_001C1090(s32 arg0) {
    u8 *duel = D_00317490.b;
    s32 i;
    Quad_001C1090 a;
    Block_001C1090 b;
    Quad_001C1090 c;
    Vec3_001C1090 d;
    extern s32 func_001F1A80(s32, f32);
    extern s32 func_001F9770();

    if (arg0 >= 0) {
        s32 id = func_001DE1A0(arg0);

        func_001E8780(0x1D, -1, id, 1);
        func_00217590(2, id, 0);
        return;
    }
    a = D_00291370;
    b = D_00291380;
    c = D_00291410;
    d = D_00291420;
    for (i = 0; i < 0x54; i++) {
        func_001F30B0(i, 0);
    }
    for (i = 0; i < 0x28; i++) {
        func_001F30B0(i + 0x22, 1);
    }
    func_001F30B0(0x1D, 1);
    func_001F25D0(0x1D, NULL);
    func_001F2430(0x1D, &a);
    func_001F24C0(0x1D, &a);
    func_001F22B0(0x1D, &c);
    func_001F29E0(0x1D, 0);
    func_001F2AD0(0x1D, 0);
    func_001F1830(0x1D, 0);
    func_001F1A00(0x1D, 1);
    func_001F1A80(0x1D, 1.0f);
    func_001F26E0(0x1D, 0, NULL);
    func_001F2860(0x1D, 1, NULL);
    func_001F1EE0(0x1D, &d.x);
    func_001F9770(0, 4, &b);
    func_001F9D80(0, &c);
    duel[0xD35] = 0;
}

void func_001C1270(void) {
    func_001E7E70(0x1D, -1, 0x3E7);
    func_001F9940(0, 4, 0);
}

typedef struct Vec4_001C12B0 {
    f32 x, y, z, w;
} Vec4_001C12B0;

void func_001EDA40(s32, s32);

static inline s32 abs_001C12B0(s32 value) {
    return value >= 0 ? value : -value;
}

static inline s32 deadzone_001C12B0(s32 value) {
    if (abs_001C12B0(value) >= 48) {
        value -= value > 0 ? 48 : -48;
    } else {
        value = 0;
    }
    return value;
}

static inline f32 absf_001C12B0(f32 value) {
    return value >= 0.0f ? value : -value;
}

static inline f32 max_001C12B0(f32 a, f32 b) {
    return a > b ? a : b;
}

static inline f32 clamp_001C12B0(f32 value, f32 minimum, f32 maximum) {
    return max_001C12B0(value, minimum) < maximum ?
           max_001C12B0(value, minimum) : maximum;
}

void func_001C12B0(void) {
    extern u32 func_00203CA0();
    extern s32 func_001F2920();
    extern Vec4_001C12B0 D_00291440;
    extern f32 D_00291430[];
    f32 yaw = 0.0f;
    f32 pitch = 0.0f;
    f32 distance = 0.0f;
    Vec4_001C12B0 camera;

    func_001EDA40(2, 0x1D);
    if (func_00203A40(0, 0, 0x20)) {
        func_00217710(0, 5);
        func_001A8920();
    }
    if (func_00203BC0(0)) {
        s32 x = (u8)func_00203C40(0, 3) - 128;
        s32 y = (u8)func_00203C40(0, 2) - 128;
        s32 z = (u8)func_00203C40(0, 1) - 128;
        func_00203C40(0, 0);
        x = deadzone_001C12B0(x);
        y = deadzone_001C12B0(y);
        z = deadzone_001C12B0(z);
        yaw -= 0.024543693f * (f32)y / 40.0f;
        pitch -= 0.024543693f * (f32)x / 40.0f;
        distance += 2.0f * (f32)z / 40.0f;
    }
    if (func_00203C00(0)) {
        yaw += 0.024543693f * (f32)func_00203CA0(0, 1) / 64.0f;
        yaw -= 0.024543693f * (f32)func_00203CA0(0, 0) / 64.0f;
        pitch += 0.024543693f * (f32)func_00203CA0(0, 2) / 64.0f;
        pitch -= 0.024543693f * (f32)func_00203CA0(0, 3) / 64.0f;
        distance += 2.0f * (f32)func_00203CA0(0, 8) / 64.0f;
        distance -= 2.0f * (f32)func_00203CA0(0, 9) / 64.0f;
    } else {
        if (func_00203A40(0, 1, 0x8000)) {
            yaw += 0.024543693f;
        }
        if (func_00203A40(0, 1, 0x2000)) {
            yaw -= 0.024543693f;
        }
        if (func_00203A40(0, 1, 0x1000)) {
            pitch += 0.024543693f;
        }
        if (func_00203A40(0, 1, 0x4000)) {
            pitch -= 0.024543693f;
        }
        if (func_00203A40(0, 1, 4)) {
            distance += 2.0f;
        }
        if (func_00203A40(0, 1, 8)) {
            distance -= 2.0f;
        }
    }
    if (!(absf_001C12B0(yaw) <= 0.000001f &&
          absf_001C12B0(pitch) <= 0.000001f &&
          absf_001C12B0(distance) <= 0.000001f)) {
        f32 minimum;
        camera = *(Vec4_001C12B0 *)func_001FAF60(0);
        minimum = (f32)func_001DE260(func_001DE130(func_001F2920(0x1D)));
        camera.x = clamp_001C12B0(camera.x + distance, minimum, 300.0f);
        camera.y = func_001A6C30(6.2831855f + (camera.y + yaw), 6.2831855f);
        camera.z = clamp_001C12B0(camera.z + pitch, -0.3926991f, 1.3744469f);
        func_001FB360(0, (f32 *)&camera);
        D_00291440 = *(Vec4_001C12B0 *)func_001F9AD0(0);
        func_001F9940(0, 4, (s32)D_00291430);
    }
}

void func_001C1AD0(void) {
    func_00209D30(func_001C1B00(func_00209D20()));
}

INCLUDE_ASM("asm/nonmatchings/main_040", func_001C1B00);

typedef struct Vertex_001C1FE0 {
    f32 x, y, z;
    u8 pad0C[0xC];
    u8 r, g, b, a;
    f32 q;
    u8 pad20[0x10];
} Vertex_001C1FE0;

typedef struct Prim_001C1FE0 {
    u16 flags;
    u16 kind;
    u32 pad;
    u64 value;
    u64 alpha;
    u64 tex0;
    u64 tex1;
    u64 clamp;
} Prim_001C1FE0;

static inline void initPrim_001C1FE0(s32 kind, void *prim) {
    ((Prim_001C1FE0 *)prim)->kind = kind;
    ((Prim_001C1FE0 *)prim)->flags = 0;
    ((Prim_001C1FE0 *)prim)->value = 0;
    ((Prim_001C1FE0 *)prim)->pad = 0;
}

void func_001C1FE0(s32 arg0, f32 *position, u8 alpha, f32 width, f32 height) {
    extern s32 func_00207AA0(s32, void *, s32, s32, s32, s32);
    void *scratchpad = (void *)0x70000000;
    Vertex_001C1FE0 *vertices = (Vertex_001C1FE0 *)((u8 *)scratchpad + 0x2000);
    s32 count;
    Prim_001C1FE0 prim;

    vertices[0].r = 0x80;
    vertices[0].g = 0x80;
    vertices[0].b = 0x80;
    vertices[0].a = alpha;
    vertices[0].q = 1.0f;
    vertices[0].x = position[0] - width;
    vertices[0].y = position[1];
    vertices[0].z = position[2] - height;
    vertices[1].x = position[0] + width;
    vertices[1].y = position[1];
    vertices[1].z = position[2] - height;
    vertices[2].x = position[0] + width;
    vertices[2].y = position[1];
    vertices[2].z = position[2] + height;
    vertices[3].x = position[0] - width;
    vertices[3].y = position[1];
    vertices[3].z = position[2] + height;
    vertices[4].x = position[0] - width;
    vertices[4].y = position[1];
    vertices[4].z = position[2] - height;
    count = func_002070F0(0, 5, vertices, 0xAA, scratchpad, 0, 0);
    func_00207230(NULL, count, vertices);
    initPrim_001C1FE0(5, &prim);
    func_002086D0(&prim, func_00208D00(2));
    func_00207AA0(arg0, &prim, count, (s32)vertices, 0, 0);
}

extern u8 D_002CCB48[];
extern u8 D_002CD1F4[];
extern s32 D_003180E8;

#pragma opt_propagation off

void func_001C21A0(void) {
    u8 *state;
    s16 *var_s1;
    s16 *var_s2;
    s8 *var_s3;
    s8 *var_s4;
    s32 var_a0;
    s32 result;
    u8 *var_v0;

    state = D_00317490.b;
    var_s1 = (s16 *)0x01ED0000;
    var_s2 = (s16 *)0x01ED06AC;
    var_s3 = (s8 *)0x01ED0D58;
    var_s4 = (s8 *)0x01ED10AE;
    result = func_00214D00(0, 0);
    D_003180E8 = 0xFFFFF8;
    if (result != 0) {
        var_v0 = D_002CD1F4;
    } else {
        var_v0 = D_002CCB48;
    }
    *(u8 **)(state + 0x6D4) = var_v0;
    *(s32 *)(state + 0x6D8) = 0x01ED0000;
    *(s32 *)(state + 0x6DC) = 0x01ED06AC;
    *(s32 *)(state + 0x6E0) = 0x01ED0D58;
    *(s32 *)(state + 0x6E4) = (s32)var_s4;
    var_a0 = 0;
    do {
        var_a0 += 1;
        *var_s1 = 0x3E7;
        *var_s3 = 0;
        var_s1 += 1;
        var_s3 += 1;
    } while (var_a0 < 0x356);
    var_a0 = 0;
    do {
        var_a0 += 1;
        *var_s2 = 0x3E7;
        *var_s4 = 0;
        var_s2 += 1;
        var_s4 += 1;
    } while (var_a0 < 0x356);
    *(s16 *)(state + 0xC92) = 0;
    *(s16 *)(state + 0xC94) = 0;
    *(s8 *)(state + 0xCB6) = 0;
    *(s8 *)(state + 0xCB7) = 4;
    *(s8 *)(state + 0xCB8) = 0xA;
    *(s8 *)(state + 0xCB9) = 0;
    *(s8 *)(state + 0xCBA) = 4;
    *(s8 *)(state + 0xCBB) = 0xA;
    *(s8 *)(state + 0xCBE) = 1;
    *(s8 *)(state + 0xCBF) = 1;
    *(s8 *)(state + 0xCC0) = 0;
    *(s8 *)(state + 0xCC1) = 0;
    *(s8 *)(state + 0xD5E) = 0;
    *(s8 *)(state + 0xD5F) = 0;
    *(s16 *)(state + 0xC8A) = 0;
    *(s16 *)(state + 0xC8E) = 0;
    *(s16 *)(state + 0xC96) = 0;
    *(s16 *)(state + 0xC98) = 0;
    *(s8 *)(state + 0xCBC) = 0;
    *(s8 *)(state + 0xCBD) = 0;
    func_001C2300(0);
    func_001C2300(1);
}
#pragma opt_propagation reset

void func_001C2300(s32 arg0) {
    extern s32 func_00216AC0();
    u8 *base;
    s16 *var_s0;
    u8 *var_a0;
    u8 *var_a1;
    s32 var_a0_2;
    s32 var_a1_2;
    s32 var_s1;
    s32 var_v0;
    u16 temp_a0;
    u16 *var_s2;
    u16 *var_s3;
    u8 *var_s4;
    u8 temp_v1;

    base = D_00317490.b;
    if (arg0 != 0) {
        var_s2 = (u16 *)(base + 0xC8E);
    } else {
        var_s2 = (u16 *)(base + 0xC8A);
    }
    if (arg0 != 0) {
        var_s3 = (u16 *)(base + 0xC90);
    } else {
        var_s3 = (u16 *)(base + 0xC8C);
    }
    if (arg0 != 0) {
        var_s0 = *(s16 **)(base + 0x6DC);
    } else {
        var_s0 = *(s16 **)(base + 0x6D8);
    }
    if (arg0 != 0) {
        var_a0 = *(u8 **)(base + 0x6E4);
    } else {
        var_a0 = *(u8 **)(base + 0x6E0);
    }
    if (arg0 != 0) {
        var_a1 = *(u8 **)(base + 0x6E0);
    } else {
        var_a1 = *(u8 **)(base + 0x6E4);
    }
    if (arg0 != 0) {
        var_s4 = base + 0xD5F;
    } else {
        var_s4 = base + 0xD5E;
    }
    *var_s3 = 0;
    temp_v1 = *(u8 *)(arg0 + (s32)base + 0xCC0);
    if (temp_v1 != 2) {
        switch (temp_v1) {
            case 0:
                var_s1 = 0;
                do {
                    if (func_00216AC0(arg0, var_s1, 3) > 0) {
                        *var_s0 = var_s1;
                        *var_s3 = (u16)(*var_s3 + 1);
                    } else {
                        *var_s0 = 0x3E7;
                    }
                    var_s1 += 1;
                    var_s0 += 1;
                } while (var_s1 < 0x356);
                break;
            case 1:
                var_a1_2 = 0;
                do {
                    if ((s32)*var_a0 > 0) {
                        *var_s0 = var_a1_2;
                        *var_s3 = (u16)(*var_s3 + 1);
                    } else {
                        *var_s0 = 0x3E7;
                    }
                    var_a1_2 += 1;
                    var_s0 += 1;
                    var_a0 += 1;
                } while (var_a1_2 < 0x356);
                break;
        }
    } else {
        var_a0_2 = 0;
        do {
            if ((s32)*var_a1 > 0) {
                *var_s0 = var_a0_2;
                *var_s3 = (u16)(*var_s3 + 1);
            } else {
                *var_s0 = 0x3E7;
            }
            var_a0_2 += 1;
            var_s0 += 1;
            var_a1 += 1;
        } while (var_a0_2 < 0x356);
    }
    temp_a0 = *var_s3;
    if ((s32)temp_a0 < (*var_s2 + *var_s4)) {
        var_v0 = temp_a0 - 5;
        *var_s2 = (u16)(var_v0 > 0 ? var_v0 : 0);
    }
    func_001C3520(arg0);
}

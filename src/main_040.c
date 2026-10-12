#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_040", func_001BA3B0);

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

s32 func_001BA520(s16 arg0, s32 arg1, s64 arg2, s64 arg3, s64 arg4) {
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
    u8 *data = D_00317490;
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
    u8 *base = D_00317490;
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
    Data_001BA930 *data = (Data_001BA930 *)D_00317490;
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

INCLUDE_ASM("asm/nonmatchings/main_040", func_001BAEA0);

INCLUDE_ASM("asm/nonmatchings/main_040", func_001BB260);

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

s32 func_001BD8A0(s32, s32, s32, s32, s32, u8);
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

INCLUDE_ASM("asm/nonmatchings/main_040", func_001BCE20);

INCLUDE_ASM("asm/nonmatchings/main_040", func_001BD8A0);

INCLUDE_ASM("asm/nonmatchings/main_040", func_001BDAF0);

INCLUDE_ASM("asm/nonmatchings/main_040", func_001BE5F0);

INCLUDE_ASM("asm/nonmatchings/main_040", func_001BF180);

INCLUDE_ASM("asm/nonmatchings/main_040", func_001BF2A0);

INCLUDE_ASM("asm/nonmatchings/main_040", func_001BF470);

INCLUDE_ASM("asm/nonmatchings/main_040", func_001BF710);

INCLUDE_ASM("asm/nonmatchings/main_040", func_001BFF00);

INCLUDE_ASM("asm/nonmatchings/main_040", func_001C02E0);

INCLUDE_ASM("asm/nonmatchings/main_040", func_001C05F0);

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

    state = D_00317490;
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

INCLUDE_ASM("asm/nonmatchings/main_040", func_001C0CE0);

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

void func_00217590(s32, s32, s32);

void func_001C1090(s32 arg0) {
    u8 *duel = D_00317490;
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
f32 func_001A6C30(f32, f32);

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

INCLUDE_ASM("asm/nonmatchings/main_040", func_001C1FE0);

INCLUDE_ASM("asm/nonmatchings/main_040", func_001C21A0);

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

    base = D_00317490;
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

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

INCLUDE_ASM("asm/nonmatchings/main_040", func_001BA630);

INCLUDE_ASM("asm/nonmatchings/main_040", func_001BA710);

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

INCLUDE_ASM("asm/nonmatchings/main_040", func_001C07E0);

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

INCLUDE_ASM("asm/nonmatchings/main_040", func_001C1090);

void func_001C1270(void) {
    func_001E7E70(0x1D, -1, 0x3E7);
    func_001F9940(0, 4, 0);
}

INCLUDE_ASM("asm/nonmatchings/main_040", func_001C12B0);

void func_001C1AD0(void) {
    func_00209D30(func_001C1B00(func_00209D20()));
}

INCLUDE_ASM("asm/nonmatchings/main_040", func_001C1B00);

INCLUDE_ASM("asm/nonmatchings/main_040", func_001C1FE0);

INCLUDE_ASM("asm/nonmatchings/main_040", func_001C21A0);

INCLUDE_ASM("asm/nonmatchings/main_040", func_001C2300);

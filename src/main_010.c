#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_010", func_0013D3D0);

static inline s32 max_0013D880(s32 a, s32 b) {
    if (b < a) {
        return a;
    }
    return b;
}

s32 func_0013D880(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 min_y;
    s32 min_x;

    min_y = arg3 < arg5 ? arg3 : arg5;
    arg5 = max_0013D880(arg3, arg5);
    min_x = arg2 < arg4 ? arg2 : arg4;
    arg4 = max_0013D880(arg2, arg4);
    if ((arg4 - min_x) + (arg5 - min_y) != 2) {
        return 0;
    }
    if (func_001DF540(arg0, arg1) == 0) {
        return 0;
    }
    if (func_001E2100(arg0, arg1, 0) == 0) {
        return func_0024DF00(func_001E22B0(arg2, arg3), arg0, arg1) != 1 ? 0 : 1;
    }
    return 0;
}

s32 func_0013D980(s32 arg0, s32 arg1) {
    s32 sp50[4];
    s32 var_s0;
    s32 temp_v0;
    s32 temp_s2;
    s32 temp_s3;
    s32 temp_v0_2;
    s32 temp_v0_3;

    func_00254C90(sp50, *(s32 *)((u8 *)func_0026FC90(arg1, 0) + 4));
    if ((temp_v0 = func_00254890(sp50, arg0)) < 0) {
        return 0;
    }
    var_s0 = 0;
    if (var_s0 < func_0024E910(temp_v0)) {
        do {
            temp_v0_2 = func_0024EC50(temp_v0, var_s0);
            temp_s3 = temp_v0_2 >> 8;
            temp_s2 = temp_v0_2 & 0xFF;
            temp_v0_3 = func_001E1090(temp_s3, temp_s2);
            if (func_002509E0(temp_s3, temp_s2, temp_v0_3 & 0xFF, temp_v0_3 >> 8) >= 0xBB8) {
                return 0;
            }
            var_s0++;
        } while (var_s0 < func_0024E910(temp_v0));
    }
    return 1;
}

s32 func_0013DA70(s32 arg0) {
    if (func_001DF470(arg0) > 1000) {
        if (func_001E0150(arg0) >= 5) {
            return 0;
        }
        return 0;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_010", func_0013DAD0);

INCLUDE_ASM("asm/nonmatchings/main_010", func_0013DCA0);

INCLUDE_ASM("asm/nonmatchings/main_010", func_0013E1D0);

INCLUDE_ASM("asm/nonmatchings/main_010", func_0013E3D0);

INCLUDE_ASM("asm/nonmatchings/main_010", func_0013E7B0);

void func_0013EA20(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28) {
    func_0027DE20(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
                  arg_sp0, arg_sp8, arg_sp10, arg_sp18, arg_sp20,
                  0, 0x708, arg_sp28);
}


typedef struct {
    u16 code;
    u16 unknown2;
    u16 state;
    u16 unknown6;
    u32 data;
} Entry_0013EA80;

void func_0013EA80(void *arg0) {
    Entry_0013EA80 *entry = arg0;
    s32 packed;
    s32 result;

    packed = func_001E1090(entry->code >> 8, entry->code & 0xFF);
    func_00250360(entry->code >> 8, entry->code & 0xFF);
    result = func_0013EB20(func_001DF540(entry->code >> 8, entry->code & 0xFF), packed & 0xFF, packed >> 8);
    if (result >= 0) {
        entry->state = 0x6FF;
        entry->data = (result << 16) | (entry->data & 0xFFFF);
    } else {
        entry->state = 0x5FF;
    }
}

s32 func_0013EB20(s32 arg0, s32 arg1, s32 arg2) {
    s32 x;
    s32 y;
    s32 card;
    s32 best;
    s32 dist;
    s32 result;
    extern s32 func_00278510();

    best = 14;
    for (x = 0; x < 7; x++) {
        for (y = 0; y < 7; y++) {
            if (func_001E22B0(x, y) == 2) {
                if ((card = func_001E3790(x, y)) < 0) {
                    dist = (((arg1 < x) ? x : arg1) - ((x < arg1) ? x : arg1)) + (((arg2 < y) ? y : arg2) - ((y < arg2) ? y : arg2));
                    if (dist >= 0 && dist < best) {
                        best = dist;
                        result = (y << 8) | x;
                    }
                } else if (func_00250360(card >> 8, card & 0xFF) != func_00250370((void *)arg0)) {
                    if (func_00278510(arg0, card, func_00141B30(func_00250370((void *)arg0)), x, y, 0) > 0) {
                        dist = (((arg1 < x) ? x : arg1) - ((x < arg1) ? x : arg1)) + (((arg2 < y) ? y : arg2) - ((y < arg2) ? y : arg2));
                        if (dist >= 0 && dist < best) {
                            best = dist;
                            result = (y << 8) | x;
                        }
                    }
                }
            }
        }
    }
    return result;
}

INCLUDE_ASM("asm/nonmatchings/main_010", func_0013ECF0);

INCLUDE_ASM("asm/nonmatchings/main_010", func_0013EEE0);

INCLUDE_ASM("asm/nonmatchings/main_010", func_0013F170);

s32 func_0013F3B0(s32 arg0, void *arg1, void *arg2) {
    s32 cards[8];
    s32 index;
    s32 found;
    s32 *first;
    s32 *second;
    s32 secondIndex;

    found = 0;
    func_0026FD30(arg0, cards);
    index = 0;
    if (index < func_0026FE20(arg0)) {
        first = cards;
        do {
            if (*first == 0x320) {
                *((s8 *)arg1 + 7) = index;
                func_001DCD70(arg2, *first);
                found = 1;
            }
            first++;
            index++;
        } while (index < func_0026FE20(arg0));
    }
    if (found == 1) {
        secondIndex = 0;
        if (secondIndex < func_0026FE20(arg0)) {
            second = cards;
            do {
                if (((func_0026FCE0(*second) >> 5) == 0) &&
                    (func_00248F60(*second, 0x320) >= 0) &&
                    (func_0026FB60(arg0, *second) == 1)) {
                    if ((*second != 0x31B) && (*second != 0x31C)) {
                        *((s8 *)arg1 + 6) = secondIndex;
                        func_001DCD70(arg2, cards[secondIndex]);
                        return func_0026FCE0(cards[secondIndex]) >> 5;
                    }
                }
                second++;
                secondIndex++;
            } while (secondIndex < func_0026FE20(arg0));
        }
    }
    return -1;
}

s32 func_0013F540(s32 arg0, s32 *arg1, void *arg2, void *arg3, s32 arg4) {
    s32 i;

    for (i = 0; i < func_0026FE20(arg0); i++) {
        if (func_0026FB10(arg0, arg1[i]) == 1 &&
            (arg4 & 0xFFFF) == arg1[i] &&
            func_0026FB10(arg0, arg1[i]) == 1) {
            *((s8 *)arg3 + 6) = i;
            func_001DCD70(arg2, arg1[i]);
            return func_0026FCE0(arg1[i]) >> 5;
        }
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/main_010", func_0013F640);

INCLUDE_ASM("asm/nonmatchings/main_010", func_0013F850);

typedef struct {
    u16 id;
    u8 values[5];
} Info_0013FA90;

void func_0013FA90(s32 arg0, void *arg1, s32 *arg2) {
    Info_0013FA90 *info = arg1;
    u8 buf[5];
    s32 count;
    s32 i;
    s32 card;
    u8 level;
    u32 cost;
    extern u32 func_0026FBB0();

    if (info != NULL) {
        level = func_0026FA80(info->id, arg0);
        for (i = 0; i < 5; i++) {
            buf[i] = 0xFF;
        }
        for (i = 0, count = 0; i < func_0026FE20(arg0); i++) {
            if ((u8)func_00278E00(i, info->values) == 0) {
                buf[count++] = i;
            }
        }
        if (count != 0) {
            for (i = 0; i < (u8)func_00278D90(buf); i++) {
                card = arg2[buf[i]];
                if (card != 0x3E7 && func_0013FC70(card) == 0 && level >= func_0026FA80(card, arg0)) {
                    cost = func_0026FBB0(card);
                    if ((cost & 0xFFFF) + (cost >> 16) * 2 < 0xC1D && func_0026FC10(card) == 2 &&
                        (u16)func_002789F0(info->id, (u16)card) == 0x3E7) {
                        func_00278D20(info->values, buf[i]);
                    }
                }
            }
        }
    }
}

s32 func_0013FC70(s32 arg0) {
    if ((func_0026FCE0(arg0) >> 5) != 0) {
        return 1;
    }
    return (func_0026FC10(arg0) != 0) ? 1 : 0;
}

INCLUDE_ASM("asm/nonmatchings/main_010", func_0013FCC0);

INCLUDE_ASM("asm/nonmatchings/main_010", func_0013FEB0);

INCLUDE_ASM("asm/nonmatchings/main_010", func_001402F0);

INCLUDE_ASM("asm/nonmatchings/main_010", func_00140830);

INCLUDE_ASM("asm/nonmatchings/main_010", func_00140E10);

INCLUDE_ASM("asm/nonmatchings/main_010", func_001415F0);

s32 func_00141B30(s32 arg0) {
    if (func_001DF470(arg0) > 2000) {
        if (func_001E0150(arg0) >= 4) {
            return 0;
        }
        return 0;
    }
    return 0;
}

s32 func_00141B90(s32 arg0, s32 arg1) {
    s32 id;
    s32 val;
    u32 *p;

    id = func_001E1030();
    val = func_00250360(arg0, arg1);
    if (func_001E2100(arg0, arg1, 4) != 0) {
        return 0;
    }
    switch (func_001E0700(arg0, arg1) >> 5) {
    case 0:
        switch (id) {
        case 0x184:
            if (func_001DF470(arg0) < func_001DF470(arg0 == 0 ? 1 : 0)) {
                return 1;
            }
            break;
        case 0x170:
            if (func_00142280(val) == 1) {
                return 1;
            }
            break;
        case 0x17F:
            if (func_0024E910(func_0024CA40(0, 0, arg0, 1, 0x14, 0xE)) >= 3) {
                return 1;
            }
            break;
        case 0x182:
            if (func_00141F30(val) == 1) {
                return 1;
            }
            break;
        }
        return 2;
    case 1:
        if (func_0027D830(arg0, arg1, 0, 0, 6, 0) == 5) {
            return 2;
        }
        p = func_00250740(arg0, arg1, 0);
        if (p == NULL) {
            return 2;
        }
        switch (*p >> 8) {
        case 0xD:
            if (func_001DF470(val) < 2000) {
                return 1;
            }
            break;
        case 0x12:
            if (func_0024E910(func_0024CA40(0, 0, arg0, 1, 8, 0xE)) >= 4) {
                return 1;
            }
            break;
        case 0x25:
            if (func_0027BBC0(val, 0, 0) == 1) {
                return 1;
            }
            break;
        }
        return 2;
    }
    return 2;
}

static inline s32 max_00141E30(s32 a, s32 b) {
    if (a < b) {
        return b;
    }
    return a;
}

s32 func_00141E30(s32 arg0, s32 arg1, s32 arg2, s32 arg3,
                  s32 arg4, s32 arg5) {
    s32 min_y;
    s32 min_x;

    min_y = arg3 < arg5 ? arg3 : arg5;
    arg5 = max_00141E30(arg5, arg3);
    min_x = arg2 < arg4 ? arg2 : arg4;
    arg4 = max_00141E30(arg4, arg2);
    if ((arg4 - min_x) + (arg5 - min_y) != 2) {
        return 0;
    }
    if (func_001DF540(arg0, arg1) == 0) {
        return 0;
    }
    if (func_001E2100(arg0, arg1, 0) == 0) {
        if (func_0024DF00(func_001E22B0(arg2, arg3), arg0, arg1) != 1) {
            return 0;
        }
        return 1;
    }
    return 0;
}

s32 func_00141F30(s32 arg0) {
    s32 index;
    u8 count;
    s32 list;
    s32 low;
    s32 high;
    s32 entry;

    count = 0;
    list = func_0024CA40(0, 0, arg0, 3, 3, 14);
    for (index = 0; index < func_0024E910(list); index++) {
        entry = func_0024EC50(list, index);
        high = entry >> 8;
        low = entry & 0xFF;
        if (arg0 == func_00250360(high, low)) {
            return 0;
        }
        if (func_002781B0(high, low, 0) == 1) {
            count++;
        }
    }
    if (count > 0) {
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_010", func_00142040);

s32 func_00142220(s32 arg0) {
    if (func_001DF470(arg0) < 0x4B0) {
        /* Duplicate return node #6. Try simplifying control flow for better match */
        return 0;
    }
    if (func_001E0150(arg0) >= 4) {
        return 1;
    }
    return 0;
}

s32 func_00142280(s32 arg0) {
    if (func_0024E910(func_0024CA40(0, 0, arg0, 1, 0x3E80025, 0xE)) >= 3) {
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_010", func_001422E0);

INCLUDE_ASM("asm/nonmatchings/main_010", func_001424B0);

INCLUDE_ASM("asm/nonmatchings/main_010", func_001429B0);

INCLUDE_ASM("asm/nonmatchings/main_010", func_00142B70);

INCLUDE_ASM("asm/nonmatchings/main_010", func_00142F50);

INCLUDE_ASM("asm/nonmatchings/main_010", func_00143540);

void func_00143790(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28) {
    func_0027DE20(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
                  arg_sp0, arg_sp8, arg_sp10, arg_sp18, arg_sp20,
                  0, 0x708, arg_sp28);
}

s32 func_001437F0(s16 *output, s32 arg1, s32 arg2, s32 flags) {
    s32 i;
    u8 count;
    s32 entry;
    s32 include_same;
    s32 include_other;

    count = 0;
    i = 0;
    include_same = flags & 1;
    include_other = (flags >> 1) & 1;
    do {
        if ((entry = func_001E3790(i, arg1)) >= 0) {
            if (include_same == 1) {
                if (arg2 == func_00250360(entry >> 8, entry & 0xFF)) {
                    output[count] = entry;
                    count++;
                }
            }
            if (include_other == 1) {
                if (arg2 != func_00250360(entry >> 8, entry & 0xFF)) {
                    output[count] = entry;
                    count++;
                }
            }
        }
        i++;
    } while (i < 7);
    return count;
}

s32 func_00143900(void *arg0) {
    s32 i;

    for (i = 1; i <= 5; i++) {
        if (func_0024DEB0(func_001E22B0(0, i), arg0) == 1) {
            return i;
        }
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/main_010", func_00143970);

s32 func_00143A80(s32 arg0, s32 arg1) {
    u8 data[0x60];
    u8 flags;
    s32 key;
    u8 count;
    s32 i;
    s32 value;
    s32 delay;

    flags = func_0026FCE0(arg0);
    func_001DCD70(data, arg0);
    if (((s32) flags >> 5) != 0) {
        return 0;
    }
    key = func_001DE540();
    delay = 0;
    do {
        delay++;
    } while (delay < 7);
    count = 0;
    i = 0;
    do {
        value = func_001E3790(i, arg1);
        if ((value >= 0) && (key == func_00250360(value >> 8, value & 0xFF))) {
            count++;
        }
        i++;
    } while (i < 7);
    if (count == 0) {
        if (func_0024DEB0(func_001E22B0(0, arg1), data) == 1) {
            return 1;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_010", func_00143BA0);

INCLUDE_ASM("asm/nonmatchings/main_010", func_00143DE0);

s32 func_00144150(s32 arg0, s32 *arg1, void *arg2, void *arg3, s32 arg4) {
    s32 index;
    s32 *entry;
    s32 key;
    s32 *selected;

    index = 0;
    if (index < func_0026FE20(arg0)) {
        key = (u16)arg4;
        entry = arg1;
        do {
            if (func_0026FB10(arg0, *entry) == 1) {
                if (key == *entry && func_0026FB10(arg0, *entry) == 1) {
                    *((s8 *)arg3 + 6) = index;
                    selected = &arg1[index];
                    func_001DCD70(arg2, *selected);
                    return func_0026FCE0(*selected) >> 5;
                }
            }
            ++entry;
            ++index;
        } while (index < func_0026FE20(arg0));
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/main_010", func_00144250);

INCLUDE_ASM("asm/nonmatchings/main_010", func_00144450);

#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_072", func_0024B310);

INCLUDE_ASM("asm/nonmatchings/main_072", func_0024C330);

void func_0024C450(s32 *arg0, s32 arg1, s32 arg2) {
    s32 temp_a0;
    s32 *temp_a1;
    s32 *temp_a2;

    temp_a1 = arg0 + arg1;
    temp_a2 = arg0 + arg2;
    temp_a0 = *temp_a1;
    *temp_a1 = *temp_a2;
    *temp_a2 = temp_a0;
}

INCLUDE_ASM("asm/nonmatchings/main_072", func_0024C480);

s32 func_0024C780(u32 arg0, s32 arg1, s32 arg2) {
    if (arg1 == 0) {
        return (arg0 & 0x7FF) | (((arg0 >> 0xB) | (1 << (0xA - arg2))) << 0xB);
    }
    return arg0 | (1 << (0xA - arg2));
}

s32 func_0024C7D0(u32 arg0, s32 arg1, s32 arg2) {
    s32 temp_a0;
    s32 temp_s2;

    if (arg1 == 0) {
        temp_a0 = 0x15 - arg2;
        return ((((u32) (arg0 >> 0xB) >> (0xA - arg2)) & ~1) << temp_a0) | (arg0 & func_0024C870(temp_a0));
    }
    temp_s2 = arg0 & ~func_0024C870(0xB - arg2);
    return temp_s2 | (arg0 & func_0024C870(0xA - arg2));
}

s32 func_0024C870(s32 arg0) {
    s32 temp_s0;
    s32 var_s0;
    s32 var_s1;

    var_s1 = 0;
    var_s0 = 0;
    for (; var_s1 < arg0; var_s1++) {
        temp_s0 = func_001A6BE8(0x4000000000000000LL, func_001A2EB0(var_s1));
        var_s0 = func_001A2F68(func_001A2858(func_001A2EB0(var_s0), temp_s0));
    }
    return var_s0;
}

void func_0024C910(s32 arg0, s32 arg1, s16 *arg2) {
    s16 *var_s0;
    s32 criteria;
    s32 player;
    s32 var_s3;
    u16 player_bits;
    s32 var_v1;

    var_s3 = 1;
    var_s0 = arg2;
    criteria = arg1;
    player = arg0;
    player_bits = (u16)(player << 8);
    do {
        if ((func_001DF540(player, var_s3) != 0) && (func_0024DD80(player, func_0024DE70(player, var_s3), criteria) == 1)) {
            *var_s0 = player_bits | var_s3;
            var_s0++;
        }
        var_s3 += 1;
    } while (var_s3 < 0xB);
    var_s3 = 1;
    do {
        if (func_001DF540((player == 0) ? 1 : 0, var_s3) != 0) {
            if (func_0024DD80(player, func_0024DE70((player == 0) ? 1 : 0, var_s3), criteria) == 1) {
                if (player == 0) {
                    var_v1 = 1;
                } else {
                    var_v1 = 0;
                }
                *var_s0 = var_s3 | (var_v1 << 8);
                var_s0++;
            }
        }
        var_s3 += 1;
    } while (var_s3 < 0xB);
}

INCLUDE_ASM("asm/nonmatchings/main_072", func_0024CA40);

s32 func_0024DD80(s32 arg0, s32 arg1, s32 arg2) {
    switch (arg2) {
    case 0:
        return 0;
    case 1:
        return (arg0 == arg1) ? 1 : 0;
    case 2:
        if (arg0 == ((arg1 == 0) ? 1 : 0)) {
            return 1;
        }
        return 0;
    case 3:
        return 1;
    default:
        return 0;
    }
}

s32 func_0024DE20(s32 arg0, s32 arg1) {
    switch (arg1) {
    case 1:
        return arg0;
    case 2:
        return (arg0 == 0) ? 1 : 0;
    default:
        return -1;
    }
}

s32 func_0024DE70(s32 arg0, s32 arg1) {
    if (func_001E2100(arg0, arg1, 1) != 0) {
        return (arg0 == 0) ? 1 : 0;
    }
    return arg0;
}

s32 func_0024DEB0(s32 arg0, void *arg1) {
    if (((s32) *((u8 *)arg1 + 0x3E) >> 5) != 0 ||
        *((u8 *)arg1 + 0x45) == 0) {
        return 0;
    }
    return func_0024DF80(arg0, arg1);
}

s32 func_0024DF00(s32 arg0, s32 arg1, s32 arg2) {
    if ((func_001E0700(arg1, arg2) >> 5) != 0 || arg2 == 0) {
        return 0;
    }
    return func_0024DF80(arg0, (void *)func_001DF540(arg1, arg2));
}

INCLUDE_ASM("asm/nonmatchings/main_072", func_0024DF80);

s32 func_0024E220(s32 arg0, s32 arg1) {
    s32 index;
    s32 result;
    u8 filter;
    s32 high;
    s32 low;

    filter = arg1;
    for (index = 0; index < 8; index++) {
        if ((result = func_0024E410(arg0, index)) < 0) {
            continue;
        }
        if (!filter) {
            if (func_001E3790(result & 0xFF, result >> 8) < 0) {
                return result;
            }
        } else {
            low = result & 0xFF;
            high = result >> 8;
            if (func_001E22B0(low, high) != 8 &&
                func_001E3790(low, high) < 0) {
                return result;
            }
        }
    }
    return -1;
}

s32 func_0024E300(s32 arg0, s32 arg1, s32 arg2) {
    s32 index;
    s32 count;
    s32 value;
    s32 mode;
    s32 high;
    s32 low;

    mode = arg2 & 0xFF;
    index = 0;
    count = 0;
    do {
        if ((value = func_0024E410(arg0, index)) < 0) {
            continue;
        }
        if (mode == 0) {
            if (func_001E3790(value & 0xFF, value >> 8) >= 0) {
                continue;
            }
            if (arg1 == count) {
                return value;
            }
            count++;
        } else {
            low = value & 0xFF;
            high = value >> 8;
            if ((func_001E22B0(low, high) != 8) && (func_001E3790(low, high) < 0)) {
                if (arg1 == count) {
                    return value;
                }
                count++;
            }
        }
    } while (++index < 8);
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/main_072", func_0024E410);

s32 func_0024E780(s32 arg0, u8 arg1) {
    s32 count = 0;
    s32 index;
    s32 end;

    switch (arg1) {
    case 0:
        index = 0;
        end = 11;
        break;
    case 1:
        index = 0;
        end = 6;
        break;
    case 2:
        index = 6;
        end = 11;
        break;
    case 3:
        index = 1;
        end = 11;
        break;
    case 4:
        index = 1;
        end = 6;
        break;
    default:
        return -1;
    }

    for (; index < end; index++) {
        if (func_001DF540(arg0, index) != 0) {
            count++;
        }
    }
    return count;
}

typedef struct {
    s32 unused;
    s32 first;
    s32 second;
} Masks_0024E880;

void func_0024E880(void *arg0, s32 *arg1) {
    Masks_0024E880 *masks = arg0;
    s32 temp_v1;
    s32 var_t3;

    masks->first = 0;
    masks->second = 0;
    var_t3 = 0;
    while ((temp_v1 = *arg1) < 0) {
        if (((temp_v1 & 0xFF) + ((temp_v1 >> 8) * 7)) < 0x1D) {
            masks->first |= 1 << (0x1C - var_t3);
        } else {
            masks->second |= 1 << (0x15 - (var_t3 - 0x1D));
        }
        arg1++;
        var_t3 += 1;
    }
}

s32 func_0024E910(s32 arg0) {
    s32 count = 0;
    s32 bit = 0;

    do {
        if ((((u32) arg0 >> bit) & 1) == 1) {
            count += 1;
        }
        bit += 1;
    } while (bit < 0x16);
    return count;
}

s32 func_0024E950(s32 arg0, s32 arg1, s32 arg2) {
    s32 x;
    s32 y;
    s32 nextY;

    x = arg0 & 0xFF;
    y = arg0 >> 8;
    switch (arg2) {
    case 0:
        x -= arg1;
        if (x >= 0) {
            return (y << 8) | x;
        }
        break;
    case 1:
        nextY = y - arg1;
        if (nextY < 0) {
            break;
        }
        return x | (nextY << 8);
    case 2:
        x += arg1;
        if (x >= 7) {
            break;
        }
        return (y << 8) | x;
    case 3:
        nextY = y + arg1;
        if (nextY >= 7) {
            break;
        }
        return x | (nextY << 8);
    default:
        return -1;
    }
    return -1;
}

s32 func_0024EA10(s32 arg0, u32 arg1) {
    u32 var_v0;

    if ((arg0 >> 8) == 0) {
        var_v0 = ((arg1 >> 0xB) >> (0xA - (arg0 & 0xFF))) & 1;
    } else {
        var_v0 = (arg1 >> (0xA - (arg0 & 0xFF))) & 1;
    }
    return var_v0;
}

s32 func_0024EA60(void) {
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_072", func_0024EA70);

s32 func_0024EBD0(s32 arg0) {
    s32 count;
    s32 result;

    count = func_0024E910(arg0);
    if (count == 0) {
        return -1;
    }
    result = func_0024EC50(arg0, func_0019A5C8() % count);
    if (result >= 0) {
        return result;
    }
    return -1;
}

s32 func_0024EC50(s32 mask, s32 ordinal) {
    s32 index;
    s32 count;

    index = 0;
    count = 0;
    do {
        if (((mask >> (21 - index)) & 1) == 1) {
            if (count == ordinal) {
                if (index < 11) {
                    return index;
                } else {
                    return (index - 11) | 0x100;
                }
            }
            count++;
        }
        index++;
    } while (index < 22);
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/main_072", func_0024ECD0);

s32 func_0024EFB0(s32 mask) {
    extern s32 func_001E13C0(s32, s32);
    s32 i;
    s32 best;
    s32 bestPair;
    s32 pair;
    s32 value;

    best = 0xFF;
    bestPair = -1;
    for (i = 0; i < func_0024E910(mask); i++) {
        pair = func_0024EC50(mask, i);
        value = func_001E13C0(pair >> 8, pair & 0xFF);
        if (value < best) {
            bestPair = pair;
            best = value;
        }
    }
    return bestPair;
}

INCLUDE_ASM("asm/nonmatchings/main_072", func_0024F060);

s32 func_0024F150(s32 mask) {
    extern s32 func_001E13C0(s32, s32);
    s32 i;
    s32 best;
    s32 bestPair;
    s32 pair;
    s32 value;

    best = -1;
    bestPair = -1;
    for (i = 0; i < func_0024E910(mask); i++) {
        pair = func_0024EC50(mask, i);
        value = func_001E13C0(pair >> 8, pair & 0xFF);
        if (best < value) {
            bestPair = pair;
            best = value;
        }
    }
    return bestPair;
}

u32 func_0024F200(s32 arg0) {
    s32 i;
    s32 best;
    s32 mask;
    s32 score;
    s32 low;
    s32 high;
    s32 value;

    best = 0xFFFF;
    mask = 0;
    i = 0;
    if (i < func_0024E910(arg0)) {
        do {
            value = func_0024EC50(arg0, i);
            high = value >> 8;
            low = value & 0xFF;
            if ((score = func_0024F2F0(high, low)) < best) {
                mask = func_0024C780(0U, high, low);
                best = score;
            } else if (score == best) {
                mask = func_0024C780((u32) mask, high, low);
            }
            i += 1;
        } while (i < func_0024E910(arg0));
    }
    return (u32) mask;
}

s32 func_0024F2F0(s32 arg0, s32 arg1) {
    s32 temp_v0;
    s32 temp_s1;
    s32 temp_s0;

    temp_v0 = func_001E1090(arg0, arg1);
    temp_s1 = temp_v0 & 0xFF;
    temp_s0 = func_002509E0(arg0, arg1, temp_s1, temp_s1);
    return temp_s0 + func_00250B40(arg0, arg1, temp_s1, temp_v0 >> 8);
}

INCLUDE_ASM("asm/nonmatchings/main_072", func_0024F370);

INCLUDE_ASM("asm/nonmatchings/main_072", func_0024F430);

INCLUDE_ASM("asm/nonmatchings/main_072", func_0024F520);

s32 func_0024F780(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    if (func_001E22B0(arg2, arg3) == 9) {
        if (func_0024FD10(arg0, arg1, arg4) == 1) {
            return 0x10001;
        }
    }
    return func_0024F830(arg0, arg1, arg2, arg3, arg4);
}

INCLUDE_ASM("asm/nonmatchings/main_072", func_0024F830);

INCLUDE_ASM("asm/nonmatchings/main_072", func_0024FD10);

void func_0024FDA0(void) {
    func_0024FDD0(func_001DF540());
}

s32 func_0024FDD0(s32 arg0) {
    u8 temp_v1;

    if (arg0 == 0) {
        return 0;
    }
    temp_v1 = *(u8 *)((u8 *)arg0 + 0x3E);
    if ((((s32) temp_v1 >> 5) != 0) ||
        (*(u8 *)((u8 *)arg0 + 0x45) == 0) ||
        ((temp_v1 & 0x1F) == 0x14)) {
        return 0;
    }
    return (func_00250A60(arg0, *(u8 *)((u8 *)arg0 + 0x40), *(u8 *)((u8 *)arg0 + 0x41)) < 0x5DC) ? 0 : 1;
}

INCLUDE_ASM("asm/nonmatchings/main_072", func_0024FE40);

INCLUDE_ASM("asm/nonmatchings/main_072", func_0024FEB0);

INCLUDE_ASM("asm/nonmatchings/main_072", func_00250000);

INCLUDE_ASM("asm/nonmatchings/main_072", func_002500C0);

s32 func_00250300(u16 arg0, s32 arg1, s32 arg2) {
    if (arg2 > 0) {
        arg0 += arg1;
        if (arg0 > 0x80) {
            arg0 = 0x80;
        }
        return arg0;
    }
    if (arg1 < arg0) {
        arg0 -= arg1;
    } else {
        arg0 = 0;
    }
    return arg0;
}

s32 func_00250360(s32 arg0, s32 arg1) {
    return func_0024DE70(arg0, arg1);
}

typedef struct {
    s8 unused : 1;
    s8 inverted : 1;
    s8 reserved : 6;
} Flags_00250370;

typedef struct {
    u8 pad_00[0x44];
    u8 value;
    u8 pad_45[0x12];
    Flags_00250370 flags;
} Data_00250370;

s32 func_00250370(void *arg0) {
    Data_00250370 *data = arg0;

    if (arg0 == NULL) {
        return -1;
    }
    if (data->flags.inverted == 0) {
        return data->value;
    }
    return (data->value == 0) ? 1 : 0;
}

void func_002503B0(s32 arg0, s32 arg1, s32 arg2) {
    /* called unprototyped: the byte goes out zero-extended, not as s8 */
    s32 func_001E1520();
    u8 value = arg2;

    if (value > 0) {
        if (func_001E1580() <= value) {
            func_001E1520(arg0, arg1, value);
            func_001E1420(arg0, arg1, 1);
        }
    } else {
        func_001E1520(arg0, arg1, value);
    }
}

typedef struct {
    u8 kind;
    u8 pad1[2];
    u8 level;
    u8 pad4[5];
    u8 pad9 : 7;
    u8 flag : 1;
} Card_00250430;

s32 func_00250620(s32, s32);

s32 func_00250430(s32 arg0, s32 arg1) {
    s32 list[0x356];
    Card_00250430 *card;
    s32 count;
    s32 level;
    s32 flag;
    s32 done;
    s32 i;

    for (i = 0; i < 0x356; i++) {
        list[i] = 999;
    }
    card = (Card_00250430 *)func_001DD0E0(arg1);
    if ((card->kind >> 5) == 0) {
        flag = (func_0019A5C8() % 10 < 8) ? 1 : 0;
    } else {
        flag = (func_0019A5C8() % 10 < 4) ? 0 : 1;
    }
    done = 0;
    count = 0;
    level = func_00250620(arg0, card->level);
    if (level > 0) {
        do {
            for (i = flag ? 0 : 0x2AB; i < (flag ? 0x2AB : 0x356); i++) {
                if (i != arg1) {
                    card = (Card_00250430 *)func_001DD0E0(i);
                    if (card != NULL && card->level == level && card->flag) {
                        list[count++] = i;
                    }
                }
            }
            if (count > 0 || --level == 0) {
                done = 1;
            } else {
                count = 0;
            }
        } while (!done);
    }
    if (count == 0) {
        return 0x334;
    }
    return list[func_0019A5C8() % count];
}

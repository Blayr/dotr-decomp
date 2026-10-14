#include "common.h"

typedef struct Node_0027AF20 {
    u8 value;
    u8 padding[0x33];
    struct Node_0027AF20 *next;
} Node_0027AF20;

u8 func_0027AF20(void *arg0, u8 depth) {
    Node_0027AF20 *node = arg0;
    Node_0027AF20 *next;

    if (depth >= 7) {
        return 0xFFU;
    }
    next = node->next;
    if (next == NULL) {
        return 0xFFU;
    }
    if (next->next == NULL) {
        return node->value;
    }
    return func_0027AF20(next, depth + 1);
}

void func_0027AF80(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 var_a2;
    s32 *var_a3;

    *(s8 *)arg0 = (s8) ((arg3 << 4) | arg2);
    var_a2 = 0;
    var_a3 = arg0;
    do {
        var_a2 += 1;
        var_a3[1] = 0;
        var_a3++;
    } while (var_a2 < 0xC);
    *(s32 *)((u8 *)arg0 + 0x34) = arg1;
}

typedef struct {
    u8 low : 4;
    u8 high : 4;
} Nibbles_0027AFC0;

s32 func_0027AFC0(u8 *arg0) {
    s32 i;
    s32 count;
    Nibbles_0027AFC0 *entries = (Nibbles_0027AFC0 *)arg0;

    i = 0;
    count = 0;
    do {
        if (entries[i].low != 0xF && entries[i].high != 0xF) {
            count++;
        }
        i++;
    } while (i < 0xC);
    return count;
}

static inline s32 absolute_0027B010(s32 value) {
    if (value >= 0) {
        return value;
    }
    return -value;
}

s32 func_0027B010(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8 arg5) {
    s32 var_t1;
    s32 var_t2;
    s32 var_t3;
    s32 min_x;
    s32 max_x;
    u8 temp_t4;

    if (arg5 <= 0) {
        return 0;
    }
    if (arg0 == NULL) {
        return 0;
    }
    temp_t4 = *(u8 *)arg0;
    if (arg1 == (temp_t4 & 0xF)) {
        if (arg2 == ((s32) temp_t4 >> 4)) {
            return 1;
        }
    }
    var_t2 = (arg2 < arg4) ? arg2 : arg4;
    var_t3 = (arg4 < arg2) ? arg2 : arg4;
    min_x = (arg1 < arg3) ? arg1 : arg3;
    max_x = (arg3 < arg1) ? arg1 : arg3;
    if (((max_x - min_x) + (var_t3 - var_t2)) == 2) {
        var_t1 = absolute_0027B010(arg1 - arg3);
        switch (var_t1) {
        case 0:
            if ((arg1 == (temp_t4 & 0xF)) && (((s32) temp_t4 >> 4) == ((arg2 + arg4) >> 1))) {
                return 1;
            }
            break;
        case 1:
            if ((arg3 == (temp_t4 & 0xF)) || (arg4 == ((s32) temp_t4 >> 4))) {
                return 1;
            }
            break;
        case 2:
            if (((temp_t4 & 0xF) == ((arg1 + arg3) >> 1)) && (arg2 == ((s32) temp_t4 >> 4))) {
                return 1;
            }
            break;
        }
    }
    return func_0027B010(*(void **)((u8 *)arg0 + 0x34), arg1, arg2, arg3, arg4, arg5 - 1);
}

u8 *func_0027B150(u16 *arg0, u16 *arg1) {
    u16 temp_a2;

    if ((s64) (u32) (*arg0 + 0x38) > 0x10000) {
        return 0;
    }
    temp_a2 = *arg1;
    *arg1 = temp_a2 + 1;
    *arg0 += 0x38;
    return (u8 *) 0x01ED0000 + temp_a2 * 0x38;
}

void func_0027B1B0(void *arg0, u8 arg1) {
    if (arg1 < 2) {
        if (arg1 == 1) {
            *(u32 *)((u8 *)arg0 + 8) =
                (*(u32 *)((u8 *)arg0 + 8) & 0xFFFF) | 0xFFFF0000;
        } else {
            *(u32 *)((u8 *)arg0 + 8) =
                (*(u32 *)((u8 *)arg0 + 8) & 0xFFFF0000) | 0xFFFF;
        }
    }
}

void func_0027B200(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4,
                   s32 arg5, s32 arg6, s32 arg7, u8 arg8) {
    func_0027B290(func_001DF540(arg0, arg1), arg2, arg3, arg4, arg5,
                  arg6, arg7, arg8);
}

typedef struct {
    u8 low : 4;
    u8 high : 4;
} Nibbles_0027B290;

s32 func_0027B290(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, u8 arg7) {
    extern s32 func_002792C0(s32, void *, s32, s32, s32, s32, u16, u8);
    Nibbles_0027B290 entries[12];
    s32 i;
    s32 pos;
    s32 cost;

    for (i = 0; i < 12; i++) {
        entries[i].low = entries[i].high = 15;
    }
    if (arg4 == -1) {
        pos = -1;
    } else {
        pos = (arg3 << 8) | arg4;
    }
    cost = func_002792C0(arg0, entries, arg1, arg2, arg5, arg6, pos, arg7);
    if (func_0027AFC0((u8 *)entries) > 0) {
        return cost;
    }
    return 0;
}

typedef struct Entry_0027B360 {
    u16 id;
    u16 pad2;
    u16 kind;
    u16 pad6;
    u8 pad8[8];
} Entry_0027B360;


s32 func_0027B360(s32 arg0, u16 *arg1, u16 *arg2) {
    u16 cards[22];
    s32 count;
    s32 found;
    s32 i;
    s32 index;
    Entry_0027B360 *entry;

    found = 0;
    for (i = 0; i < 22; i++) {
        cards[i] = 0xFFFF;
    }
    for (i = 0, count = 0; i < func_0027C670(arg1); i++) {
        if (func_001DF540(arg1[i] >> 8, arg1[i] & 0xFF) == 0) {
            continue;
        }
        if (func_001E2100(arg1[i] >> 8, arg1[i] & 0xFF, 0) != 0) {
            continue;
        }
        index = func_00276C80(arg2, arg1[i]);
        if (index < 0) {
            continue;
        }
        entry = (Entry_0027B360 *)arg2 + index;
        if (((entry->kind >> 8) & 0xFF) == 2 && func_0027B520(entry, 1) == 1) {
            found = 1;
            cards[count++] = arg1[i];
        } else if ((entry->kind & 0xFF) == 2 && func_0027B520(entry, 0) == 1) {
            found = 1;
            cards[count++] = arg1[i];
        }
    }
    if (found == 1) {
        return func_0027B650(cards);
    }
    return -1;
}

typedef union {
    u32 word;
    struct {
        u16 low;
        u16 high;
    } halves;
} Data_0027B520;

typedef struct {
    u16 id;
    u16 pad2;
    u16 kind;
    u16 pad6;
    Data_0027B520 data;
} Entry_0027B520;

#define TARGET_0027B520(entry, high) \
    ((high) == 1 ? (entry)->data.word >> 16 & 0xFFFF : (entry)->data.halves.low)

s32 func_0027B520(void *arg0, u8 arg1) {
    extern s32 func_00279850();
    extern s32 func_002464F0(s32, s32, s32);
    Entry_0027B520 *entry = arg0;
    u16 target;
    s32 pos;
    s32 other;

    target = TARGET_0027B520(entry, arg1);
    pos = func_001E1090(entry->id >> 8, entry->id & 0xFF);
    other = func_001E1090(TARGET_0027B520(entry, arg1) >> 8, TARGET_0027B520(entry, arg1) & 0xFF);
    func_002464F0(func_001DF540(entry->id >> 8, entry->id & 0xFF), pos & 0xFF, pos >> 8);
    return (func_00279850(entry->id >> 8, entry->id & 0xFF, pos & 0xFF, pos >> 8,
                          other & 0xFF, other >> 8, &target) == 1) ? 1 : 0;
}

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027B650);

s32 func_0027B740(void *arg0, s32 arg1) {
    s32 index;
    s32 best;
    s32 selected;
    s32 packed;
    u16 *entry;
    s32 score;
    u16 value;

    best = -1;
    index = 1;
    selected = -1;
    if (index < func_0027C670(arg0)) {
        entry = (u16 *)arg0 + 1;
        do {
            value = *entry;
            packed = func_001E1090((s32)value >> 8, value & 0xFF);
            value = *entry;
            if (func_001E2100((s32)value >> 8, value & 0xFF, 4) != 0 ||
                (value = *entry, arg1 == func_00250360((s32)value >> 8, value & 0xFF))) {
                value = *entry;
                score = func_002509E0((s32)value >> 8, value & 0xFF, packed & 0xFF, packed >> 8);
                if (best < score) {
                    selected = *entry;
                    best = score;
                }
            }
            entry++;
            index++;
        } while (index < func_0027C670(arg0));
    }
    return selected;
}

s32 func_0027B860(u16 *arg0, s32 arg1) {
    extern s32 func_001E1580(s32, s32);
    extern s32 func_001E1640(s32, s32);
    s32 i;
    s32 best;
    s32 bestPos;
    s32 cur;
    u16 *p;
    s32 score;

    best = -1;
    bestPos = best;
    i = 1;
    if (i < func_0027C670(arg0)) {
        p = &arg0[1];
        do {
            cur = func_001E1090(*p >> 8, *p & 0xFF);
            if (func_001E2100(*p >> 8, *p & 0xFF, 4) != 0 ||
                (arg1 == func_00250360(*p >> 8, *p & 0xFF) &&
                 func_001E1580(*p >> 8, *p & 0xFF) == 0 &&
                 func_001E1640(*p >> 8, *p & 0xFF) == 0)) {
                score = func_002509E0(*p >> 8, *p & 0xFF, cur & 0xFF, cur >> 8);
                if (best < score) {
                    bestPos = *p;
                    best = score;
                }
            }
            p++;
            i++;
        } while (i < func_0027C670(arg0));
    }
    return bestPos;
}


static inline s32 min_0027B9B0(s32 a, s32 b) {
    return (a >= b + 1) ? b : a;
}

s32 func_0027B9B0(s32 arg0) {
    s32 i;
    s32 j;
    s32 yMax;
    s32 x;
    s32 y;
    s32 pos;
    s32 flags;
    s32 xMax;
    s32 yMin;

    x = arg0 & 0xFF;
    y = (arg0 & 0xFFFF) >> 8;
    if ((pos = func_001E1090(y, x)) < 0) {
        return 0;
    }
    if (func_001E2100(y, x, 0) != 0) {
        return 0;
    }
    flags = func_002464F0(func_001DF540(y, x), (pos & 0xFF), (pos >> 8));
    i = func_00250860(0, (pos & 0xFF) - 1);
    yMin = (pos >> 8) - 1;
    yMax = (pos >> 8) + 1;
    xMax = (pos & 0xFF) + 1;
    for (; i <= min_0027B9B0(xMax, 6); i++) {
        for (j = func_00250860(0, yMin); j <= min_0027B9B0(yMax, 6); j++) {
            if ((((pos & 0xFF) > i ? (pos & 0xFF) : i) - ((pos & 0xFF) < i ? (pos & 0xFF) : i)) + (((pos >> 8) > j ? (pos >> 8) : j) - ((pos >> 8) < j ? (pos >> 8) : j)) == 1 &&
                func_001E36E0(i, j) == 0) {
                if (func_001E22B0(i, j) != 8 || (flags & 0x10)) {
                    if (func_001E22B0(i, j) != 9 || func_0024FE40((void *)func_001DF540(y, x), i, j) != 1) {
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

s32 func_0027BBC0(s32 arg0, s32 arg1, s32 arg2) {
    s32 count;
    s32 distance;
    s32 index;
    s32 y;
    u16 values[22];
    s32 packed;
    s32 targetY;
    s32 targetX;
    s32 coords;
    s32 origin;
    u16 *p;
    u16 *current;
    u16 position;
    s32 unit;
    s32 x;
    s32 range;

    extern s32 func_00279850();
    extern s32 func_001E1580();
    extern s32 func_001E1640();
    extern void func_0027C070();

    if (func_001DF540(arg0, arg1) == 0) {
        return 0;
    }
    position = (arg0 << 8) | arg1;
    current = values;
    count = 0;
    p = current;
    do {
        count++;
        *p++ = 0xFFFF;
    } while (count < 22);
    func_0027C070(func_00250360(arg0, arg1) == 0 ? 1 : 0, values, 31, arg2);
    packed = func_001E1090(arg0, arg1);
    index = 0;
    if (index < func_0027C670(values)) {
        origin = (arg0 << 8) | arg1;
        targetY = packed >> 8;
        targetX = packed & 0xFF;
        do {
            coords = func_001E1090(*current >> 8, *current & 0xFF);
            unit = func_001DF540(*current >> 8, *current & 0xFF);
            x = coords & 0xFF;
            y = coords >> 8;
            range = func_002464F0(unit, x, y);
            distance = ((x < targetX ? targetX : x) - (targetX < x ? targetX : x)) +
                       ((y < targetY ? targetY : y) - (targetY < y ? targetY : y));
            if ((u32)distance <= (u32)(range & 0xF)) {
                if (func_00279850(*current >> 8, *current & 0xFF, x, y,
                                  targetX, targetY, &position) == 1 &&
                    func_002781F0(position, *current, targetX, targetY) <= 0 &&
                    func_001E1580(*current >> 8, *current & 0xFF) == 0 &&
                    func_001E1640(*current >> 8, *current & 0xFF) == 0 &&
                    func_0027E5B0(origin, targetX, targetY) == 0) {
                    return 1;
                }
            }
            current++;
            index++;
        } while (index < func_0027C670(values));
    }
    return 0;
}

s32 func_0027BE10(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 distance;
    s32 origin;
    s32 count;
    u16 *p;
    s32 coords;
    s32 targetY;
    s32 targetX;
    s32 packed;
    u16 *current;
    s32 range;
    u16 position;
    s32 unit;
    s32 y;
    u16 values[22];
    s32 x;
    s32 index;

    extern s32 func_00279850();
    extern s32 func_001E1580();
    extern s32 func_001E1640();
    extern void func_0027C070();

    if (func_001DF540(arg0, arg1) == 0) {
        return 0;
    }
    position = (arg0 << 8) | arg1;
    current = values;
    count = 0;
    p = current;
    do {
        count++;
        *p++ = 0xFFFF;
    } while (count < 22);
    func_0027C070(func_00250360(arg0, arg1) == 0 ? 1 : 0, values, 31, arg4);
    packed = (arg3 << 8) | arg2;
    index = 0;
    if (index < func_0027C670(values)) {
        origin = (arg0 << 8) | arg1;
        targetY = packed >> 8;
        targetX = packed & 0xFF;
        do {
            coords = func_001E1090(*current >> 8, *current & 0xFF);
            unit = func_001DF540(*current >> 8, *current & 0xFF);
            x = coords & 0xFF;
            y = coords >> 8;
            range = func_002464F0(unit, x, y);
            distance = ((x < targetX ? targetX : x) - (targetX < x ? targetX : x)) +
                       ((y < targetY ? targetY : y) - (targetY < y ? targetY : y));
            if ((u32)distance <= (u32)(range & 0xF)) {
                if (func_00279850(*current >> 8, *current & 0xFF, x, y,
                                  targetX, targetY, &position) == 1 &&
                    func_002781F0(position, *current, targetX, targetY) <= 0 &&
                    func_001E1580(*current >> 8, *current & 0xFF) == 0 &&
                    func_001E1640(*current >> 8, *current & 0xFF) == 0 &&
                    func_0027E5B0(origin, arg2, arg3) == 0) {
                    return 1;
                }
            }
            current++;
            index++;
        } while (index < func_0027C670(values));
    }
    return 0;
}

void func_0027C070(s32 arg0, u16 *arg1, s32 arg2, u8 arg3) {
    void *card;
    s32 i;
    s32 end;
    u8 count;
    s32 start;

    count = 0;
    switch (arg2) {
    case 0x22:
        end = 1;
        start = 0;
        break;
    case 0x1F:
        end = 11;
        start = 0;
        break;
    case 0x34:
        start = 1;
        end = 11;
        break;
    default:
        start = 1;
        end = 6;
        break;
    }
    for (i = start; i < end; i++) {
        if (count >= 22) {
            return;
        }
        if ((card = (void *)func_001DF540(arg0, i)) != 0 && arg0 == func_00250370(card)) {
            if (func_002781B0(arg0, i, arg3) != 0 || func_0027C5A0(arg0, i, arg2) == 1) {
                arg1[count] = (u16)(arg0 << 8) | i;
                count++;
            }
        }
    }
    for (i = start; i < end; i++) {
        if (count >= 22) {
            return;
        }
        if ((card = (void *)func_001DF540((arg0 == 0) ? 1 : 0, i)) != 0 && arg0 == func_00250370(card)) {
            if (func_002781B0((arg0 == 0) ? 1 : 0, i, arg3) != 0 || func_0027C5A0((arg0 == 0) ? 1 : 0, i, arg2) == 1) {
                arg1[count] = i | (((arg0 == 0) ? 1 : 0) << 8);
                count++;
            }
        }
    }
}

void func_0027C2C0(s32 arg0, u16 *arg1, s32 arg2, s32 arg3, u8 arg4) {
    void *card;
    s32 i;
    s32 end;
    u8 count;
    s32 start;

    count = 0;
    switch (arg2) {
    case 0x22:
        end = 1;
        start = 0;
        break;
    case 0x1F:
        end = 11;
        start = 0;
        break;
    case 0x34:
        start = 1;
        end = 11;
        break;
    case 0x1D:
        start = 1;
        end = 6;
        break;
    default:
        start = 1;
        end = 11;
        break;
    }
    for (i = start; i < end; i++) {
        if (count >= 22) {
            return;
        }
        if ((card = (void *)func_001DF540(arg0, i)) != 0 && arg0 == func_00250370(card)) {
            if (func_002781B0(arg0, i, arg4) != 0) {
                if (func_0027C5A0(arg0, i, arg2) == 1) {
                    arg1[count] = (u16)(arg0 << 8) | i;
                    count++;
                }
            } else if (arg3 == 1) {
                arg1[count] = (u16)(arg0 << 8) | i;
                count++;
            }
        }
    }
    for (; start < end; start++) {
        if (count >= 22) {
            return;
        }
        if ((card = (void *)func_001DF540((arg0 == 0) ? 1 : 0, start)) != 0 && arg0 == func_00250370(card)) {
            if (func_002781B0((arg0 == 0) ? 1 : 0, start, arg4) != 0) {
                if (func_0027C5A0((arg0 == 0) ? 1 : 0, start, arg2) == 1) {
                    arg1[count] = start | (((arg0 == 0) ? 1 : 0) << 8);
                    count++;
                }
            } else if (arg3 == 1) {
                arg1[count] = start | (((arg0 == 0) ? 1 : 0) << 8);
                count++;
            }
        }
    }
}

s32 func_0027C5A0(s32 arg0, s32 arg1, s32 arg2) {
    switch (arg2) {
    case 0x22:
        if (arg1 != 0) {
            break;
        }
        return 1;
    case 0x1D:
        if ((arg1 > 0) && (arg1 < 6)) {
            return 1;
        }
        break;
    case 0x1E:
        if ((arg1 > 5) && (arg1 < 0xC)) {
            return 1;
        }
        break;
    case 0x1F:
        return 1;
    case 0x34:
        if (arg1 != 0) {
            return 1;
        }
        break;
    default:
        if (arg1 != 0) {
            return 1;
        }
        break;
    }
    return 0;
}

s32 func_0027C670(u16 *values) {
    s32 count;
    s32 iteration;
    s32 index;

    count = 0;
    index = 0;
    iteration = 0;

    do {
        if (index >= 22) {
            return count;
        }
        if (values[index++] < 0xFFFF) {
            count++;
        }
        iteration++;
    } while (iteration < 22);

    return count;
}

s32 func_0027C6D0(s32 arg0) {
    s32 column;
    s32 row;
    s32 terrain;

    column = arg0 & 0xFF;
    row = arg0 >> 8;
    if (func_001E2100(row, column, 0) != 0) {
        return 1;
    }
    terrain = func_001E0700(row, column) >> 5;
    switch (terrain) {
    case 3:
    case 4:
        if (func_001E2100(row, column, 4) != 0) {
            return 0;
        }
        break;
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027C770);

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027CA50);

typedef struct Position_0027D020 {
    u8 x : 4;
    u8 y : 4;
} Position_0027D020;

typedef struct Source_0027D020 {
    u16 position;
    u8 pad2[6];
    u32 targets;
} Source_0027D020;

typedef struct Result_0027D020 {
    u16 position;
    u8 action;
    u8 pad3;
    u16 destination;
    u8 pad6[6];
    s32 type;
    u8 flags;
} Result_0027D020;

s32 func_00276CC0(s32, s32, s32, u8, u16, u8);

static inline u32 target_word_0027D020(void *src) {
    return ((Source_0027D020 *)src)->targets;
}

static inline u32 target_half_0027D020(void *src) {
    return (u16)((Source_0027D020 *)src)->targets;
}

#define target_0027D020(src, side) \
    ((side) == 1 ? (u32)(u16)(target_word_0027D020(src) >> 16) : target_half_0027D020(src))

s32 func_0027D020(void *arg0, s32 arg1, void *arg2, u8 arg3,
                  s32 arg4, s32 cost, s32 arg6, u8 arg7) {
    extern void func_0027A090();
    Position_0027D020 positions[12];
    s32 origin;
    s32 destination;
    s32 count;
    s32 best;
    s32 side;
    Position_0027D020 *p;
    s32 index;

    origin = func_001E1090(((Source_0027D020 *)arg0)->position >> 8, ((Source_0027D020 *)arg0)->position & 0xFF);
    side = arg3;
    destination = func_001E1090(target_0027D020(((Source_0027D020 *)arg0), side) >> 8,
                               target_0027D020(((Source_0027D020 *)arg0), side) & 0xFF);
    if (target_0027D020(((Source_0027D020 *)arg0), side) == 0xFFFF &&
        origin == target_0027D020(((Source_0027D020 *)arg0), side)) {
        ((Result_0027D020 *)arg2)->position = ((Source_0027D020 *)arg0)->position;
        ((Result_0027D020 *)arg2)->action = 6;
        ((Result_0027D020 *)arg2)->destination = origin;
        ((Result_0027D020 *)arg2)->flags = 2;
        ((Result_0027D020 *)arg2)->type = 2;
        func_0027B1B0(((Source_0027D020 *)arg0), arg3);
        return 0;
    }

    p = positions;
    {
        s32 i = 0;
        Position_0027D020 *q = p;
        do {
            q->x = q->y = 0xF;
            i++;
            q++;
        } while (i < 12);
    }
    func_0027A090(((Source_0027D020 *)arg0)->position >> 8, ((Source_0027D020 *)arg0)->position & 0xFF,
                  positions, origin & 0xFF, origin >> 8,
                  destination & 0xFF, destination >> 8, ((Source_0027D020 *)arg0)->targets,
                  (u8)arg4, 3, (u16)cost);
    count = func_0027AFC0((u8 *)positions);
    if (count > 0) {
        best = 0xFF;
        cost = 0xFFFF;
        index = 0;

        for (; index < count; index++, p++) {
            if (func_001E36E0(p->x, p->y) == 0) {
                s32 value;
                value = func_00276CC0(p->x, p->y, arg1,
                                      (u8)cost, (u16)arg7, (u8)cost);
                if (value < cost) {
                    cost = value;
                    best = index;
                } else if (value == cost) {
                    u32 bestMinY;
                    u32 bestY;
                    u32 bestMinX;
                    u32 bestX;
                    u32 currentMinY;
                    u32 currentY;
                    u32 currentMinX;
                    u32 currentX;

                    bestMinY = (u8)positions[best].y < (target_0027D020(((Source_0027D020 *)arg0), side) >> 8)
                        ? (u8)positions[best].y : (target_0027D020(((Source_0027D020 *)arg0), side) >> 8);
                    bestY = (target_0027D020(((Source_0027D020 *)arg0), side) >> 8) < (u8)positions[best].y
                        ? (u8)positions[best].y : (target_0027D020(((Source_0027D020 *)arg0), side) >> 8);
                    bestMinX = (u8)positions[best].x < (target_0027D020(((Source_0027D020 *)arg0), side) & 0xFF)
                        ? (u8)positions[best].x : (target_0027D020(((Source_0027D020 *)arg0), side) & 0xFF);
                    bestX = (target_0027D020(((Source_0027D020 *)arg0), side) & 0xFF) < (u8)positions[best].x
                        ? (u8)positions[best].x : (target_0027D020(((Source_0027D020 *)arg0), side) & 0xFF);
                    currentMinY = (u8)(*p).y < (target_0027D020(((Source_0027D020 *)arg0), side) >> 8)
                        ? (u8)(*p).y : (target_0027D020(((Source_0027D020 *)arg0), side) >> 8);
                    currentY = (target_0027D020(((Source_0027D020 *)arg0), side) >> 8) < (u8)(*p).y
                        ? (u8)(*p).y : (target_0027D020(((Source_0027D020 *)arg0), side) >> 8);
                    currentMinX = (u8)(*p).x < (target_0027D020(((Source_0027D020 *)arg0), side) & 0xFF)
                        ? (u8)(*p).x : (target_0027D020(((Source_0027D020 *)arg0), side) & 0xFF);
                    currentX = (target_0027D020(((Source_0027D020 *)arg0), side) & 0xFF) < (u8)(*p).x
                        ? (u8)(*p).x : (target_0027D020(((Source_0027D020 *)arg0), side) & 0xFF);
                    if ((currentX - currentMinX) + (currentY - currentMinY) <
                        (bestX - bestMinX) + (bestY - bestMinY)) {
                        cost = value;
                        best = index;
                    }
                }
            }
        }
    } else {
        ((Result_0027D020 *)arg2)->position = ((Source_0027D020 *)arg0)->position;
        ((Result_0027D020 *)arg2)->action = 6;
        ((Result_0027D020 *)arg2)->destination = origin;
        ((Result_0027D020 *)arg2)->flags = 2;
        ((Result_0027D020 *)arg2)->type = 2;
        func_0027B1B0(((Source_0027D020 *)arg0), arg3);
        return 0;
    }
    if (best != 0xFF) {
        ((Result_0027D020 *)arg2)->position = ((Source_0027D020 *)arg0)->position;
        ((Result_0027D020 *)arg2)->action = 6;
        ((Result_0027D020 *)arg2)->destination = (positions[best].y << 8) | positions[best].x;
        ((Result_0027D020 *)arg2)->flags = 2;
        ((Result_0027D020 *)arg2)->type = 2;
    } else {
        ((Result_0027D020 *)arg2)->position = ((Source_0027D020 *)arg0)->position;
        ((Result_0027D020 *)arg2)->action = 6;
        ((Result_0027D020 *)arg2)->destination = origin;
        ((Result_0027D020 *)arg2)->flags = 2;
        ((Result_0027D020 *)arg2)->type = 2;
    }
    func_0027B1B0(((Source_0027D020 *)arg0), arg3);
    return 0;
}

s32 func_0027D720(u16 *arg0, s32 arg1) {
    u16 candidates[22];
    s32 side;
    s32 target;
    s32 i;
    u16 *p;
    u16 position;

    position = *arg0;
    side = func_0024DE70((s32) position >> 8, position & 0xFF);
    p = candidates;
    i = 0;
    do {
        i += 1;
        *p++ = 0xFFFF;
    } while (i < 22);
    position = *arg0;
    switch (func_001E0700((s32) position >> 8, position & 0xFF) >> 5) {
    case 0:
        position = *arg0;
        if (func_001E2100((s32) position >> 8, position & 0xFF, 4) != 0) {
            return 0;
        }
        break;
    }
    func_0027C2C0((side == 0) ? 1 : 0, candidates, 0x34, 0, 0);
    target = func_0027B860(candidates, (side == 0) ? 1 : 0);
    if (target < 0) {
        return 0;
    }
    func_0027E780(arg0, target, arg1);
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027D830);

s32 func_0027DA40(s32 arg0, s32 arg1) {
    extern s32 func_001DEE50(s32);
    s32 best;
    s32 index;
    s32 owner;
    s32 i;
    s32 j;
    s32 value;

    owner = -1;
    index = -1;
    best = -1;
    if (arg1 & 1) {
        for (i = 0; i < func_001DEE50(arg0); i++) {
            if ((func_0026FCE0(func_001DEE00(arg0, i)) >> 5) == 0) {
                value = func_0026FBB0(func_001DEE00(arg0, i)) >> 16;
                if (best < value) {
                    best = value;
                    index = i;
                    owner = arg0;
                }
            }
        }
    }
    if (arg1 >> 1) {
        for (j = 0; j < func_001DEE50(arg0 == 0 ? 1 : 0); j++) {
            if ((func_0026FCE0(func_001DEE00(arg0 == 0 ? 1 : 0, j)) >> 5) == 0) {
                value = func_0026FBB0(func_001DEE00(arg0 == 0 ? 1 : 0, j)) >> 16;
                if (best < value) {
                    best = value;
                    index = j;
                    owner = arg0 == 0 ? 1 : 0;
                }
            }
        }
    }
    return best | ((owner << 24) | (index << 16));
}

s32 func_0027DBC0(s32 arg0, s32 arg1, s32 arg2) {
    extern s32 func_001DEE50(s32);
    u8 count;
    s32 i;
    s32 mode;

    mode = arg2 & 0xFF;
    count = 0;
    if (mode == 31) {
        return arg1 & 0xFF;
    }
    if (mode == 29) {
        for (i = 0; i < func_001DEE50(arg0); i++) {
            if (i == (arg1 & 0xFF)) {
                return count;
            }
            if ((func_0026FCE0(func_001DEE00(arg0, i)) >> 5) == 0) {
                count++;
            }
        }
    } else if (mode == 30) {
        for (i = 0; i < func_001DEE50(arg0); i++) {
            if (i == (arg1 & 0xFF)) {
                return count;
            }
            if ((func_0026FCE0(func_001DEE00(arg0, i)) >> 5) != 0) {
                count++;
            }
        }
    }
    return arg1 & 0xFF;
}

s32 func_0027DD20(s32 arg0, s32 arg1, s32 arg2) {
    extern s32 func_001DEE50();
    extern s32 func_001DEE00();
    s32 i;
    u8 count;

    count = 0;
    if (arg1 & 1) {
        for (i = 0; i < func_001DEE50(arg0); i++) {
            if (arg2 == func_001DEE00(arg0, i)) {
                count++;
            }
        }
    }
    if (arg1 >> 1) {
        for (i = 0; i < func_001DEE50(arg0 == 0 ? 1 : 0); i++) {
            if (arg2 == func_001DEE00(arg0 == 0 ? 1 : 0, i)) {
                count++;
            }
        }
    }
    return count;
}

s32 func_0027DE20(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4,
                  s32 arg5, s32 arg6, s32 arg7, s32 arg8, u16 arg9,
                  s32 arg10, s32 arg11, s32 arg12, s32 arg13,
                  s32 arg14, s32 arg15) {
    extern s32 func_00277160();
    extern s32 func_002785D0();
    extern s32 func_00278510();
    extern s32 func_001E1580();
    extern s32 func_001E1640();
    s32 candidate;

    arg12 = (u8)arg12;
    arg13 = (u8)arg13;
    func_002770E0(arg1, arg2, arg3, arg4, arg5, arg6, arg13, arg7,
                  arg8, (s32)&arg9, arg10, arg11, arg15);
    if ((candidate = func_00277160(arg2, arg3, arg4, arg8, arg12, 30, 1, 2,
                                  arg13, arg7, arg9)) >= 0 &&
        func_00250A60(arg2, arg3, arg4) <= arg14) {
        *(s16 *)((u8 *)arg0 + 4) = 0x2FF;
        *(u32 *)((u8 *)arg0 + 8) = (candidate << 16) | *(u16 *)((u8 *)arg0 + 8);
        return 1;
    }
    if ((candidate = func_00277160(arg2, arg3, arg4, arg8, arg12, 29, 1, 2,
                                  arg13, arg7, arg9)) >= 0) {
        s32 y;
        s32 x;
        s32 position;
        s32 row;
        s32 column;

        x = candidate >> 8;
        y = candidate & 0xFF;
        position = func_001E1090(x, y);
        *(u32 *)((u8 *)arg0 + 8) = (candidate << 16) | *(u16 *)((u8 *)arg0 + 8);
        row = position >> 8;
        column = position & 0xFF;
        if (func_00278510(arg2, candidate, arg7, column, row, arg13) > 0) {
            func_0027E780((void *)arg0, candidate, arg13);
            return 1;
        }
        if (func_001E1580(x, y) < 2) {
            if (func_001E1640(x, y) == 0) {
                return func_002785D0(arg2, candidate, arg7, column, row, arg13);
            }
        }
    } else {
        s32 y;
        s32 x;
        s32 row;
        s32 column;
        s32 alternate;
        s32 position;
        if ((alternate = func_00277160(arg2, arg3, arg4, arg8, arg12, 52, 0, 2,
                                      arg13, arg7, arg9)) >= 0) {
            x = alternate >> 8;
            y = alternate & 0xFF;
            position = func_001E1090(x, y);

            *(u32 *)((u8 *)arg0 + 8) = (alternate << 16) | *(u16 *)((u8 *)arg0 + 8);
            row = position >> 8;
            column = position & 0xFF;
            if (func_00278510(arg2, alternate, arg7, column, row, arg13) > 0) {
                func_0027E780((void *)arg0, alternate, arg13);
                return 1;
            }
            if (func_001E1580(x, y) < 2 && func_001E1640(x, y) == 0) {
                return func_002785D0(arg2, alternate, arg7, column, row, arg13);
            }
        }
    }
    return -1;
}

s32 func_0027E150(s32 arg0) {
    s32 index;
    s32 count;
    s32 result;
    s32 low;
    s32 high;
    s32 value;

    count = func_0024E910(arg0);
    result = arg0;
    for (index = 0; index < count; index++) {
        value = func_0024EC50(arg0, index);
        high = value >> 8;
        low = value & 0xFF;
        if (func_001E2100(high, low, 4) == 0) {
            result = func_0024C7D0((u32) high, low, result);
        }
    }
    return result;
}


typedef struct Entry_0027E210 {
    u16 id;
    u16 unused2;
    s16 status;
    u16 unused6;
    u32 position;
} Entry_0027E210;

void func_0027E210(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    Entry_0027E210 *entry = arg0;
    u16 id;

    id = entry->id;
    if (func_0027BBC0((s32) id >> 8, id & 0xFF, arg3) == 1) {
        if (func_001DE6D0((s32) entry->id >> 8) == 1) {
            entry->status = 0x50A;
        } else {
            entry->status = 0x5FF;
        }
    } else {
        id = entry->id;
        if (func_0027BE10((s32) id >> 8, id & 0xFF, arg1, arg2, arg3) == 0) {
            if (func_001DE6D0((s32) entry->id >> 8) == 1) {
                entry->status = 0x60A;
                entry->position = *(u16 *)&entry->position | (((arg2 << 8) | arg1) << 16);
            } else {
                entry->status = 0x6FF;
                entry->position = *(u16 *)&entry->position | (((arg2 << 8) | arg1) << 16);
            }
        } else {
            if (func_001DE6D0((s32) entry->id >> 8) == 1) {
                entry->status = 0x50A;
            } else {
                entry->status = 0x5FF;
            }
        }
    }
}

s32 func_0027E360(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 pos;
    s32 result;
    s32 y;
    s32 x;
    s32 count;

    if (arg1 == 0) {
        return 2;
    }
    pos = arg2 & 0xFFFF;
    if (pos != func_001E1090(arg0, arg1)) {
        return 2;
    }
    x = pos & 0xFF;
    y = pos >> 8;
    result = func_0027D830(arg0, arg1, x, y, 4, arg4);
    func_0027D830(arg0, arg1, x, y, 5, arg4);
    if (func_001E2100(arg0, arg1, 5) != 0) {
        if ((func_001E0700(arg0, arg1) >> 5) != 0) {
            if (result != 2 && result != 5) {
                return 2;
            }
            return 0;
        }
        count = func_001E0290(arg0, arg1, 0);
        if (func_001E0370(arg0, arg1, 0) < count && (arg3 & 0xFF) == 0) {
            if (result != 2 && result != 5) {
                return 2;
            }
            return 0;
        }
        if (result != 2 && result != 5) {
            return 2;
        }
        return 0;
    }
    if ((func_001E0700(arg0, arg1) >> 5) != 0) {
        if (result != 2 && result != 5) {
            return 1;
        }
    }
    count = func_001E0290(arg0, arg1, 0);
    if (count < func_001E0370(arg0, arg1, 0) || (arg3 & 0xFF) == 1) {
        if (result != 2 && result != 5) {
            return 1;
        }
    }
    return 2;
}

s32 func_0027E5B0(s32 arg0, s32 arg1, s32 arg2) {
    extern s32 func_001E1030();
    s32 x;
    s32 y;
    s32 kind;
    s32 lo;
    s32 hi;
    s32 pos;

    kind = func_00250360(arg0 >> 8, arg0 & 0xFF);
    if (func_0026AB80(kind, 4) >= 0) {
        return 1;
    }
    for (x = func_00250860(0, arg1 - 1); x <= func_00250860(0, arg1 + 1); x++) {
        for (y = func_00250860(0, arg2 - 1); y <= func_00250860(0, arg2 + 1); y++) {
            if (((((x < arg1) ? arg1 : x) - ((arg1 < x) ? arg1 : x)) + (((y < arg2) ? arg2 : y) - ((arg2 < y) ? arg2 : y))) == 1) {
                pos = func_001E3790(x, y);
                hi = pos >> 8;
                if (pos >= 0) {
                    lo = pos & 0xFF;
                    if ((func_001E0700(hi, lo) >> 5) == 3 && func_001E1030(hi, lo) != 0x32D && kind == func_00250360(hi, lo)) {
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

void func_0027E770(void) {

}

typedef struct State_0027E780 {
    u16 position;
    u16 pad2;
    u16 flags;
    u16 pad6;
    u32 destination;
} State_0027E780;

s32 func_0027D830(s32, s32, s32, s32, s32, s32);

void func_0027E780(void *arg0, s32 arg1, s32 arg2) {
    State_0027E780 *state = arg0;
    s32 destination;
    s32 result;
    u32 packed_destination;
    u16 position;

    destination = func_001E1090(arg1 >> 8, arg1 & 0xFF);
    position = state->position;
    result = func_0027D830(position >> 8, position & 0xFF,
                         destination & 0xFF, destination >> 8, 0, arg2);
    switch (result) {
    case 1:
    case 2:
        state->flags = 0x6FF;
        packed_destination = state->destination & 0xFFFF;
        state->destination = (destination << 16) | packed_destination;
        break;
    default:
        state->flags = 0x2FF;
        packed_destination = state->destination & 0xFFFF;
        state->destination = (arg1 << 16) | packed_destination;
        break;
    }
}

typedef struct State_0027E840 {
    u16 value;
    u8 pad2[2];
    u16 state;
    u8 id;
    u8 pad7[0xFB];
    u16 ticks;
} State_0027E840;

typedef struct Message_0027E840 {
    s32 code;
    s32 kind;
    s32 text;
    s32 flags;
} Message_0027E840;


s32 func_0027E840(void *arg0, void *arg1, s32 arg2) {
    Message_0027E840 messageData;
    State_0027E840 *state = arg1;
    u16 value;
    Message_0027E840 *message;

    messageData.code = 999;
    messageData.kind = 0;
    messageData.text = 0;
    messageData.flags = 0;
    message = &messageData;

    if (arg2 >= 0) {
        func_00255960(arg1);
        state->value = 0x80;
        func_00255AC0(arg1, 0x271);
        func_001E3FE0();
        func_002608F0(0);
        func_001F5970(*(s32 *)((u8 *)arg0 + 4) << 8, 1);
        return 1;
    }

    func_001DE7E0(0);
    switch (state->state) {
    case 0:
        value = func_00250300(state->value, 15, -1);
        state->value = value;
        if (value > 0) {
            func_001F6D00(*(u8 *)state);
            func_001F6CF0(*(u8 *)state);
        } else {
            func_001F6D00(*(u8 *)state);
            func_001F6CF0(*(u8 *)state);
            if (func_00255B50(arg1) == 1) {
                state->state++;
            }
        }
        break;
    case 1:
        func_001E42C0(0, -120, 80, 0x115);
        message->code = 0x271;
        message->kind = 0;
        message->text = func_001E1090(*(s32 *)((u8 *)arg0 + 4), 0);
        message->flags = 0;
        state->id = func_00255A30((s32 *)message, arg1);
        state->state++;
        break;
    case 2:
        if (func_001F51D0(state->id) != 0) {
            if (state->ticks == 0) {
                func_00217710(0, 0x22);
            }
            if (state->ticks++ == 19) {
                func_002610D0(0, *(s32 *)((u8 *)arg0 + 4) << 8, 300, 300);
                func_00217710(0, 0x25);
                func_00217710(0, 0x24);
            }
            return 1;
        } else {
            func_001E4530();
            func_00260A70(arg1, 16);
            state->ticks = 0;
            state->value = 0;
            state->state++;
        }
        break;
    default:
        state->ticks++;
        value = func_00250300(state->value, 15, 1);
        state->value = value;
        if (value < 128) {
            func_001F6D00(*(u8 *)state);
            func_001F6CF0(*(u8 *)state);
        } else if ((s32)state->ticks > 16) {
            func_001F5970(*(s32 *)((u8 *)arg0 + 4) << 8, 0);
            if (func_001DE780() != 0) {
                func_001DE7E0(1);
            }
            func_001E4530();
            return 0;
        }
        break;
    }
    return 1;
}

typedef struct Vec4_0027EB00 {
    f32 x, y, z, w;
} Vec4_0027EB00;

typedef union Scale_0027EB00 {
    Vec4_0027EB00 vector;
    struct { s32 x, y, z, w; } fixed;
} Scale_0027EB00;

typedef struct Flags_0027EB00 {
    s8 low : 5;
    s8 bit5 : 1;
    s8 bit6 : 1;
    s8 high : 1;
} Flags_0027EB00;

typedef union Record_0027EB00 {
    __int128 data[10];
    struct {
        Vec4_0027EB00 position;
        Scale_0027EB00 scale;
        Vec4_0027EB00 transform;
        Vec4_0027EB00 rotation;
        u8 pad40[0x41];
        Flags_0027EB00 flags;
        u8 pad82[0x1E];
    } fields;
} Record_0027EB00;

typedef struct History_0027EB00 {
    Vec4_0027EB00 rotation;
    Vec4_0027EB00 scale;
    Vec4_0027EB00 position;
    u8 pad30[0x40];
} History_0027EB00;

typedef struct State_0027EB00 {
    History_0027EB00 history[5];
    Record_0027EB00 first;
    Record_0027EB00 second;
    Vec4_0027EB00 firstPosition;
    Vec4_0027EB00 firstScale;
    s32 firstAngles[3];
    s32 pad39C;
    f32 firstSpeedX;
    f32 firstSpeedY;
    u8 pad3A8[8];
    f32 firstX;
    f32 firstY;
    s32 firstActive;
    s32 pad3BC;
    Vec4_0027EB00 secondPosition;
    Vec4_0027EB00 secondScale;
    s32 secondAngles[3];
    s32 pad3EC;
    f32 secondSpeedX;
    f32 secondSpeedY;
    u8 pad3F8[8];
    f32 secondX;
    f32 secondY;
    s32 secondActive;
    s32 pad40C;
    s32 timer;
    s32 mode;
    s32 flags;
    s32 firstAlpha;
    s32 secondAlpha;
    s32 finish;
    u8 pad428[8];
} State_0027EB00;


s32 func_0027EB00(void *arg0, void *arg1, s32 arg2) {
    s32 firstId;
    s32 secondId;
    Record_0027EB00 *first;
    Record_0027EB00 *second;
    s32 result;

    func_00207500();
    firstId = *(s32 *) ((u8 *) arg1 + 4);
    secondId = *(s32 *) ((u8 *) arg1 + 8);
    first = (Record_0027EB00 *) func_001F5B30(firstId);
    second = (Record_0027EB00 *) func_001F5B30(secondId);
    if (first == 0 && second == 0) {
        return 8;
    }
    {
        State_0027EB00 *state = (State_0027EB00 *) arg0;

        if (arg2 >= 0) {
            func_00195108((s32) state, 0x430);
            func_0027F0D0(state);
            if (first != 0) {
                state->first = *first;
            }
            if (second != 0) {
                state->second = *second;
            }
            if (first != 0) {
                func_001F5970(firstId, 1);
                state->first.fields.flags.bit6 = 1;
                state->first.fields.flags.bit5 = 1;
            }
            if (second != 0) {
                func_001F5970(secondId, 1);
                state->second.fields.flags.bit6 = 1;
                state->second.fields.flags.bit5 = 1;
            }
            state->flags = 0;
            state->mode = arg2;
            state->timer = 14;
            state->finish = 0;
            if (first != 0) {
                *((u8 *) first + 0x43) = 0;
            }
            if (second != 0) {
                *((u8 *) second + 0x43) = 0;
            }
            state->secondAlpha = 128;
            state->firstAlpha = 128;
            state->firstX = -125.0f;
            state->firstY = -8.0f;
            state->secondX = 125.0f;
            state->secondY = -8.0f;
            if (first != 0) {
                state->flags |= 1;
                state->firstActive = 1;
                func_00205CB0(&state->first, state->firstX, state->firstY);
                state->firstPosition = first->fields.position;
                func_00205C40((s32) &state->first.fields.transform);
                state->firstAngles[2] = 0;
                state->firstAngles[1] = 0;
                state->firstAngles[0] = 0;
                state->first.fields.scale.fixed.x = 0;
                state->first.fields.scale.fixed.y = 0x10000;
                state->first.fields.scale.fixed.z = 0x10000;
                state->firstScale = first->fields.scale.vector;
                state->firstSpeedY = 0.1f;
                state->firstSpeedX = 0.1f;
                state->first.fields.rotation.x = 0.46875f;
                state->first.fields.rotation.y = 0.4891299903392792f;
            }
            if (second != 0) {
                s32 i;
                History_0027EB00 *history;

                state->flags |= 2;
                state->secondActive = 1;
                func_00205CB0(&state->second, state->secondX, state->secondY);
                state->secondPosition = second->fields.position;
                func_00205C40((s32) &state->second.fields.transform);
                state->secondAngles[2] = 0;
                state->secondAngles[1] = 0;
                state->secondAngles[0] = 0;
                state->second.fields.scale.fixed.x = 0;
                state->second.fields.scale.fixed.y = 0x10000;
                state->second.fields.scale.fixed.z = 0x10000;
                state->secondScale = second->fields.scale.vector;
                state->secondSpeedY = 0.1f;
                state->secondSpeedX = 0.1f;
                state->second.fields.rotation.x = 0.46875f;
                state->second.fields.rotation.y = 0.4891299903392792f;
                i = 0;
                history = state->history;
                do {
                    ++i;
                    history[1].position = state->second.fields.position;
                    history[1].scale = state->second.fields.scale.vector;
                    history[1].rotation = state->second.fields.rotation;
                    ++history;
                } while (i < 4);
            }
        }
        result = 0;
        func_0027F110((u8 *) state);
        func_001D99F0();
        if (state->mode == 0 && first != 0) {
            func_0027F180(&state->first, state->firstAlpha, 0);
        }
        if (second != 0) {
            func_0027F180(&state->second, state->secondAlpha, 0);
        }
        if (state->mode == 1) {
            func_00205CB0(&state->first, state->firstX, state->firstY);
            if (state->timer < 7) {
                func_0027F290(&state->second, &state->first, state->timer);
            }
            if (state->timer != 0) {
                --state->timer;
            } else {
                if (func_0027F160(state->flags, 31) == 0) {
                    state->flags |= 0x80000000;
                }
                state->timer = 27;
            }
        }
        func_001D9DD0();
        {
            History_0027EB00 *history;
            s32 i;

            i = 3;
            history = &state->history[3];
            do {
                if (i != 0) {
                    history[1].position = history->position;
                    history[1].scale = history->scale;
                    history[1].rotation = history->rotation;
                } else {
                    history[1].position = state->second.fields.position;
                    history[1].scale = state->second.fields.scale.vector;
                    history[1].rotation = state->second.fields.rotation;
                }
                --i;
                --history;
            } while (i >= 0);
        }
        if (func_0027F160(state->flags, 31) != 0) {
            ++state->finish;
            if (state->finish == 4) {
                result = 2;
            } else if (state->finish > 4) {
                state->finish = 999;
            }
        }
        return result;
    }
}

void func_0027F0D0(void *arg0) {
    f32 *values = arg0;

    values[0] = values[1] = values[2] = values[3] = 1.0f;
    values[4] = values[5] = values[6] = values[7] = 0.0f;
    values[8] = values[9] = values[10] = values[11] = 0.0f;
}


typedef struct {
    f32 values[4][4];
} Matrix_0027F110;

void func_0027F110(u8 *arg0) {
    Matrix_0027F110 matrix;

    func_0020EB40(arg0 + 0x30);
    func_0020C940(&matrix, arg0, arg0 + 0x10, arg0 + 0x20);
    func_0020BC00((s32)(arg0 + 0x30), &matrix);
}

s32 func_0027F160(s32 arg0, s32 arg1) {
    return !(arg0 & (1 << arg1)) ? 0 : 1;
}

typedef struct Vertex_0027F180 {
    u8 pad0[0x10];
    u64 lower : 32;
    u64 color : 24;
    u64 upper : 8;
    u8 pad18[3];
    u8 alpha;
    u8 pad1C[0x14];
} Vertex_0027F180;

typedef struct Count_0027F180 {
    s16 count : 12;
    s16 reserved : 4;
} Count_0027F180;

typedef struct Object_0027F180 {
    u8 pad0[0x78];
    Vertex_0027F180 *vertices;
    s32 field7C;
    s16 field80;
    Count_0027F180 field82;
    u8 pad84[0xC];
    s32 field90;
} Object_0027F180;

s32 func_0027F180(void *arg0, s32 arg1, f32 *arg2) {
    Object_0027F180 *object = arg0;
    s32 result;
    s32 i;

    if (arg2 != NULL) {
        result = func_001DA2B0(object, 0, arg2[0], arg2[1]);
    } else {
        result = func_001D9F00(object, 1);
    }
    for (i = 0; i < object->field82.count; i++) {
        object->vertices[i].color = 0xFFFFFF;
        object->vertices[i].alpha = arg1;
    }
    if (result != 0) {
        func_001DA7A0(object->field90, (s32) object);
    } else {
        func_001DA7A0(0, (s32) object);
    }
    func_001DBCF0((s32) object);
    return 0;
}

typedef struct Vec3_0027F290 {
    f32 x;
    f32 y;
    f32 z;
} Vec3_0027F290;

void func_0027F290(void *arg0, void *arg1, s32 arg2) {
    Vec3_0027F290 vec;
    f32 temp_f1;

    if (arg2 != 0) {
        vec.x = ((Vec3_0027F290 *)arg1)->x;
        vec.y = ((Vec3_0027F290 *)arg1)->y;
        vec.z = ((Vec3_0027F290 *)arg1)->z;
        func_0027F3A0(&vec, arg0);
        temp_f1 = (f32) arg2;
        vec.x /= temp_f1;
        vec.y /= temp_f1;
        vec.z /= temp_f1;
        func_0027F360(arg0, &vec);
        return;
    }
    ((Vec3_0027F290 *)arg0)->x = ((Vec3_0027F290 *)arg1)->x;
    ((Vec3_0027F290 *)arg0)->y = ((Vec3_0027F290 *)arg1)->y;
    ((Vec3_0027F290 *)arg0)->z = ((Vec3_0027F290 *)arg1)->z;
}

void func_0027F360(void *arg0, void *arg1) {
    f32 *dst = arg0;
    f32 *src = arg1;

    dst[0] += src[0];
    dst[1] += src[1];
    dst[2] += src[2];
}

void func_0027F3A0(void *arg0, void *arg1) {
    f32 *dst = arg0;
    f32 *src = arg1;

    dst[0] -= src[0];
    dst[1] -= src[1];
    dst[2] -= src[2];
}

void func_0027F3E0(u8 arg0, s32 arg1) {
    func_0027F480(arg1);
    switch (arg0) {
    case 32:
        func_0027F5A0();
        break;
    case 35:
        func_001DE5E0(0, 4, 8);
        func_001DE5E0(1, 4, 8);
        break;
    case 36:
        func_0027F5B0();
        break;
    }
}

typedef struct Entry_0027F480 {
    u16 field_0;
    u16 field_2;
    u16 field_4;
    u16 field_6;
    s32 field_8;
    u8 flags : 2;
    u8 reserved : 6;
    u8 padding[3];
} Entry_0027F480;

typedef struct State_0027F480 {
    Entry_0027F480 entries[22];
    u16 indices[32];
    u8 flags : 5;
    u8 reserved : 3;
    u8 padding_1a1;
    u16 field_1a2;
    u16 field_1a4;
    u8 padding_1a6[10];
    f32 position[4];
    f32 rotation[4];
} State_0027F480;

void func_0027F480(s32 arg0) {
    f32 *rotation;
    f32 *position;
    u8 *cursor;
    s32 j;
    s32 i;
    Entry_0027F480 *entry;
    State_0027F480 *state = (State_0027F480 *)arg0;

    position = (f32 *)func_001F9D30(0);
    rotation = func_001FAF60(0);
    if (state != 0) {
        state->field_1a2 = 0;
        state->field_1a4 = 0;
        i = 0;
        entry = state->entries;
        do {
            entry->field_0 = 0xFFFF;
            entry->field_2 = 0xFF;
            entry->field_8 = -1;
            entry->field_4 = 0xFFFF;
            i += 1;
            entry->flags = 0;
            entry++;
        } while (i < 22);
        j = 0;
        cursor = (u8 *)state;
        do {
            j += 1;
            *(u16 *)(cursor + 0x160) = 0xFFFF;
            cursor += 2;
        } while (j < 32);
        state->flags = 0;
        state->position[0] = position[0];
        state->position[1] = position[1];
        state->position[2] = position[2];
        state->position[3] = position[3];
        state->rotation[0] = rotation[0];
        state->rotation[1] = rotation[1];
        state->rotation[2] = rotation[2];
        state->rotation[3] = rotation[3];
        state->indices[1] = 0;
    }
}

void func_0027F5A0(void) {

}

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027F5B0);

INCLUDE_ASM("asm/nonmatchings/main_079", func_0027F630);

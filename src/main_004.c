#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_004", func_0010C940);

INCLUDE_ASM("asm/nonmatchings/main_004", func_0010CE20);

s32 func_0010D080(u16 *arg0, s32 arg1, s32 arg2) {
    s32 i;
    s32 pos;
    s32 ret;
    s32 idx;
    u16 list[22];

    for (i = 0; i < 22; i++) {
        list[i] = 0xFFFF;
    }
    func_0027C070(arg1, list, 0x1D, 1);
    ret = func_0027B360(arg1, list, arg0);
    if (ret >= 0) {
        return ret;
    }
    for (i = 0; i < 22; i++) {
        list[i] = 0xFFFF;
    }
    func_0027C070(arg1, list, 0x1E, 1);
    for (i = 0; i < func_0027C670(list); i++) {
        if (((func_001E0700(list[i] >> 8, list[i] & 0xFF) >> 5) == 3 ||
             (func_001E0700(list[i] >> 8, list[i] & 0xFF) >> 5) == 4) &&
            func_0027B9B0(list[i]) == 1 && func_0027C6D0(list[i]) == 1) {
            return list[i];
        }
    }
    pos = arg1 << 8;
    idx = func_00276C80(arg0, pos);
    func_0010CE20(arg0, arg0 + idx * 8);
    if (((arg0[idx * 8 + 2] >> 8) & 0xFF) == 10) {
        if (func_001DE6D0(arg1) == 1 && func_0010DD50(pos, arg1, arg2) >= 0) {
            return pos | 0x10000;
        }
        if (func_0027B9B0(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (func_001E2100(arg1, 0, 0) == 0) {
        if (func_0027B9B0(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (func_001DE6D0(arg1) == 1 && func_0010DD50(pos, arg1, arg2) >= 0) {
        return pos | 0x10000;
    }
    for (i = 0; i < 22; i++) {
        list[i] = 0xFFFF;
    }
    func_0027C070(arg1, list, 0x1F, 1);
    for (i = 0; i < func_0027C670(list); i++) {
        if (func_0027B9B0(list[i]) == 1 && func_0027C6D0(list[i]) == 1) {
            return list[i];
        }
    }
    for (i = 0; i < 22; i++) {
        list[i] = 0xFFFF;
    }
    func_0027C070(arg1, list, 0x1F, 1);
    for (i = 0; i < func_0027C670(list); i++) {
        if (func_001E2100(list[i] >> 8, list[i] & 0xFF, 0) == 0 && func_0027C6D0(list[i]) == 1) {
            return list[i];
        }
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/main_004", func_0010D490);

void func_0010D820(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28) {
    func_0027DE20(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
                  arg_sp0, arg_sp8, arg_sp10, arg_sp18, arg_sp20,
                  0, 0x960, arg_sp28);
}

typedef struct Entry_0010D880 {
    u16 id;
    u8 index;
    u8 pad;
} Entry_0010D880;

void func_0010D490(void *, s32, s32);

void func_0010D880(void *arg0, s32 arg1, s32 arg2) {
    extern s32 func_001E1030();
    extern void func_0027E770();
    extern s32 func_0027DE20();
    u8 context[0x70];
    Entry_0010D880 entries[23];
    s16 count;
    s16 otherCount;
    s32 i;
    Entry_0010D880 *entry;
    s32 owner;
    s32 location;
    s32 data;
    s32 type;
    s32 x;
    s32 y;
    s32 attempt;
    s32 result;
    u16 id;

    id = *(u16 *)arg0;
    if ((data = func_001DF540(id >> 8, id & 0xFF)) != 0) {
        id = *(u16 *)arg0;
        owner = func_0024DE70(id >> 8, id & 0xFF);
        id = *(u16 *)arg0;
        location = func_001E1090(id >> 8, id & 0xFF);
        otherCount = 0;
        count = 0;
        entry = entries;
        i = 0;
        do {
            i++;
            entry->id = 0xFFFF;
            entry->index = 0xFF;
            entry++;
        } while (i < 22);
        func_0027E770(context);
        id = *(u16 *)arg0;
        type = func_001E1030(id >> 8, id & 0xFF);
        switch (type) {
        case 0x192:
        case 0x193:
            attempt = 1;
            x = location >> 8;
            y = location & 0xFF;
            while (1) {
                result = func_0027DE20(arg0, 0, data, y, x,
                    owner == 0 ? 1 : 0, (u8)attempt, func_0010EDA0(owner),
                    entries, 0, &count, &otherCount, 2, 0, 0x960, context);
                switch (result) {
                case 3:
                case 2:
                    *(u16 *)((u8 *)arg0 + 4) = 0x3FF;
                    *(u32 *)((u8 *)arg0 + 8) = (location << 16) | *(u16 *)((u8 *)arg0 + 8);
                    return;
                case 1:
                    return;
                case 0:
                    *(u16 *)((u8 *)arg0 + 4) = 0x3FF;
                    *(u32 *)((u8 *)arg0 + 8) = (location << 16) | *(u16 *)((u8 *)arg0 + 8);
                    return;
                }
                attempt++;
                if (attempt > 2) {
                    break;
                }
            }
            *(u16 *)((u8 *)arg0 + 4) = 0x3FF;
            *(u32 *)((u8 *)arg0 + 8) = (location << 16) | *(u16 *)((u8 *)arg0 + 8);
            break;
        case 0x1A1:
            if (func_0027D720(arg0, 0) != 1) {
                func_0010D490(arg0, 1, arg2);
            }
            break;
        case 0x198:
            if (func_001DF470(owner) < 1000) {
                func_0010DB00(arg0, 0, 0);
            }
            func_0010D490(arg0, 1, arg2);
            break;
        default:
            func_0010D490(arg0, 1, arg2);
            break;
        }
    }
}

void func_0010DB00(void *arg0, s32 arg1, s32 arg2) {
    s32 i;
    s32 position;
    s32 occupant;
    s32 count;
    s32 mode;
    u16 *record = arg0;

    if (func_001DF540((s32) record[0] >> 8, record[0] & 0xFF) != 0) {
        func_0024DE70((s32) record[0] >> 8, record[0] & 0xFF);
        func_001E1090((s32) record[0] >> 8, record[0] & 0xFF);
        func_001DF540((s32) record[0] >> 8, record[0] & 0xFF);
        if ((arg2 & 0xFF) == 1) {
            mode = 3;
        } else {
            mode = 6;
        }
        record[2] = (mode << 8) | 0xFF;
        if ((arg1 & 0xFF) == 1) {
            count = 6;
        } else {
            count = 4;
        }
        for (i = 0; i < count; i++) {
            position = (u16) func_0010F850(arg1, i & 0xFF);
            occupant = func_001E3790(position & 0xFF, position >> 8);
            if (occupant == record[0] || occupant < 0) {
                *(u32 *) (record + 4) = (position << 16) | record[4];
                return;
            }
        }
    }
}

typedef struct {
    u16 coordinate;
    u16 pad2;
    u16 status;
    u16 pad6;
    u32 value;
} State_0010DC40;

s32 func_0027C770(s32, s32, s32, s32, s32, s32);

void func_0010DC40(void *arg0) {
    State_0010DC40 *state = arg0;
    s32 coordinate;
    s32 result;
    u32 *record;

    if (func_001DF540((s32) state->coordinate >> 8, state->coordinate & 0xFF) != 0) {
        record = func_00250740((s32) state->coordinate >> 8, state->coordinate & 0xFF, 0);
        if (record != NULL) {
            switch (*record >> 8) {
        case 13:
            state->status = 0x5FF;
            return;
        case 2:
            coordinate = func_001E1090((s32) state->coordinate >> 8, state->coordinate & 0xFF) & 0xFFFF;
            result = func_0027C770(func_001DF540((s32) state->coordinate >> 8, state->coordinate & 0xFF), coordinate & 0xFF, coordinate >> 8, 0, 6, 2) & 0xFFFF;
            state->status = 0x6FF;
            if (result < 0) {
                state->value = ((coordinate & 0xFFFF) << 16) | *(u16 *) &state->value;
                return;
            }
            state->value = ((result & 0xFFFF) << 16) | *(u16 *) &state->value;
            break;
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/main_004", func_0010DD50);

s32 func_0010DFC0(s32 arg0, void *arg1) {
    extern s32 func_00278890();
    extern s32 func_0010F290();
    s32 entries[8];
    u8 buffer[32];
    u8 first;
    u8 second;
    s32 first_index;
    s32 *first_entry;
    s32 *zero_entry;
    s32 zero_index;
    s32 *check_entry;
    s32 check_index;
    s32 *last_entry;
    s32 last_index;
    s32 result;

    first = func_00278890(arg0, 0);
    second = func_00278890(arg0, 1);
    if (arg1 == NULL) {
        return -1;
    }
    func_0026FD30(arg0, entries);
    if (first == 5) {
        if (func_0010F450(arg0, buffer, arg1) >= 0) {
            return 1;
        } else {
            return -1;
        }
    }
    if (second == 5) {
        first_index = 0;
        if (0 < func_0026FE20(arg0)) {
            first_entry = entries;
            do {
                if ((func_0026FCE0(*first_entry) >> 5) == 0 &&
                    func_0026FB10(arg0, *first_entry) == 1) {
                    func_001DCD70(arg1, entries[first_index]);
                    return 0;
                }
                first_entry++;
                first_index++;
            } while (first_index < func_0026FE20(arg0));
        }
        return -1;
    }
    if (func_0010F290(arg0, buffer, arg1, 0) >= 0) {
        return 2;
    }
    if (first == 0) {
        zero_index = 0;
        if (0 < func_0026FE20(arg0)) {
            zero_entry = entries;
            do {
                if ((func_0026FCE0(*zero_entry) >> 5) == 0 &&
                    func_0026FB10(arg0, *zero_entry) == 1) {
                    return 0;
                }
                zero_entry++;
                zero_index++;
            } while (zero_index < func_0026FE20(arg0));
        }
        return func_0010F450(arg0, buffer, arg1);
    }
    if (func_0010F6F0(1) == 0) {
        check_index = 0;
        if (0 < func_0026FE20(arg0)) {
            check_entry = entries;
            do {
                if ((func_0026FCE0(*check_entry) >> 5) == 0 &&
                    func_0026FB10(arg0, *check_entry) == 1) {
                    return 0;
                }
                check_entry++;
                check_index++;
            } while (check_index < func_0026FE20(arg0));
        }
    }
    if (func_0010F6F0(2) == 0) {
        result = func_0010F450(arg0, buffer, arg1);
        if (result >= 0) {
            return result;
        }
    }
    last_index = 0;
    if (0 < func_0026FE20(arg0)) {
        last_entry = entries;
        do {
            if ((func_0026FCE0(*last_entry) >> 5) == 0 &&
                func_0026FB10(arg0, *last_entry) == 1) {
                func_001DCD70(arg1, entries[last_index]);
                return 0;
            }
            last_entry++;
            last_index++;
        } while (last_index < func_0026FE20(arg0));
    }
    result = func_0010F450(arg0, buffer, arg1);
    if (result >= 0) {
        return result;
    }
    return -1;
}

typedef struct Info_0010E320 {
    u8 pad00[8];
    u16 x;
    s16 y;
} Info_0010E320;

typedef struct Sprite_0010E320 {
    Info_0010E320 *info;
    u8 pad04[0x34];
    s16 x;
    s16 y;
} Sprite_0010E320;

u16 *func_00278A90(s32, u16 *, s32, s32, s32, s16 *, s16 *);
s32 func_00278F10(s32, u16 *, s32, s32);

s32 func_0010E320(s32 arg0, u8 *arg1, void *arg2) {
    u16 *nodes[8];
    s32 entries[7];
    s16 a;
    s16 b;
    s32 i;
    s32 card;
    s32 value;
    s32 best;
    extern s32 func_00279130();

    if (arg2 == NULL) {
        return -1;
    } else {
        s32 top;
        s32 *entry;
        u16 **node;

        func_0026FD30(arg0, entries);
        best = -1;
        top = -1;
        i = 0;
        if (i < func_0026FE20(arg0)) {
            entry = entries;
            node = nodes;
            do {
                b = 0;
                a = 0;
                card = *entry;
                *node = NULL;
                if ((func_0026FCE0(card) >> 5) == 0) {
                    *node = func_00278A90(arg0, *node, i & 0xFF, card & 0xFFFF, 0, &a, &b);
                    *node = func_00278E40(*node);
                    if (func_0023C160() < 3) {
                        value = func_00279130(arg0, *node, 0, 0);
                    } else {
                        value = func_00278F10(arg0, *node, 0, 0);
                    }
                    if (func_0026FB10(arg0, card) == 1) {
                        if (best < value) {
                            func_0010E6B0(arg0, *node, entries);
                            func_00278DD0((u8 *)*node + 2, arg1 + 6);
                            func_001DCD70(arg2, **node);
                            ((Sprite_0010E320 *)arg2)->x = (value >> 16) - (((Sprite_0010E320 *)arg2)->info->x & 0x1FFF);
                            ((Sprite_0010E320 *)arg2)->y = (value & 0xFFFF) - (((Sprite_0010E320 *)arg2)->info->y & 0x1FFF);
                            best = value;
                            if (top < value) {
                                top = value;
                            }
                        }
                    } else if (top < value) {
                        top = value;
                    }
                }
                entry++;
                node++;
                i++;
            } while (i < func_0026FE20(arg0));
        }
        return top;
    }
}

s32 func_0010E540(s32 arg0, void *arg1, s32 arg2, s32 arg3) {
    s32 count;
    s32 *p;
    s32 i;
    s32 values[8];
    s32 j;
    s32 value;
    u8 *slot;
    u8 *out = (u8 *)arg1;

    if (arg2 == 0) return -1;
    j = 0;
    do {
        out[j + 6] = 255;
        j++;
    } while (j < 5);
    func_0026FD30(arg0, values);
    if (!(arg3 & 255)) {
        func_0010F290(arg0, arg1, arg2, 0);
        count = 2;
        if (func_0023C160() > 3) {
            i = 0;
            if (i < func_0026FE20(arg0)) {
                p = values;
                do {
                    if (i != out[6] && i != out[7] && func_00248F60(427, *p) >= 0 && (func_0026FCE0(*p) >> 5) == 2) {
                        value = *p;
                        if (value != 795 && value != 796) {
                            slot = out + count;
                            count++;
                            slot[6] = i;
                        }
                    }
                    p++;
                    i++;
                } while (i < func_0026FE20(arg0));
            }
        }
    }
    return 0;
}

typedef struct {
    u16 id;
    u8 values[5];
} Info_0010E6B0;

void func_0010E6B0(s32 arg0, void *arg1, s32 *arg2) {
    Info_0010E6B0 *info = arg1;
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
                if (card != 0x3E7 && func_0010F220(card) == 0 && level >= func_0026FA80(card, arg0)) {
                    cost = func_0026FBB0(card);
                    if ((cost & 0xFFFF) + (cost >> 16) * 2 < 0xDAD && func_0026FC10(card) == 2 &&
                        (u16)func_002789F0(info->id, (u16)card) == 0x3E7) {
                        func_00278D20(info->values, buf[i]);
                    }
                }
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/main_004", func_0010E890);

void func_0010ED90(void) {
    func_0024E410();
}

s32 func_0010EDA0(s32 arg0) {
    if (func_001DF470(arg0) > 0x5DC) {
        if (func_001E0150(arg0) >= 4) {
            return 0;
        }
        return 0;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_004", func_0010EE00);

s32 func_0010F030(void) {
    extern s32 func_001E1030();
    u16 buf[22];
    s32 id;
    s32 i;
    u16 kind;

    id = func_001DE540();
    for (i = 0; i < 22; i++) {
        buf[i] = 0xFFFF;
    }
    func_0024C910(id, 1, buf);
    for (i = 0; i < 22; i++) {
        if (buf[i] != 0xFFFF) {
            kind = func_001E1030(buf[i] >> 8, buf[i] & 0xFF);
            if (kind == 0x192 || kind == 0x193 || kind == 0x1A6) {
                return 1;
            }
        }
    }
    for (i = 0; i < 22; i++) {
        if (buf[i] != 0xFFFF) {
            kind = func_001E1030(buf[i] >> 8, buf[i] & 0xFF);
            if (kind == 0x350 || kind == 0x31E) {
                return 0;
            }
        }
    }
    for (i = 0; i < 5; i++) {
        kind = func_001DF0C0(id, i) & 0xFFF;
        if (kind == 0x350 || kind == 0x31E) {
            return 0;
        }
    }
    for (i = 0; i < func_001DE9C0(id); i++) {
        kind = func_001DE9E0(id, i);
        if (kind == 0x350 || kind == 0x31E) {
            return 0;
        }
    }
    return 1;
}

s32 func_0010F220(s32 arg0) {
    if ((func_0026FCE0(arg0) >> 5) != 0) {
        return 0;
    }
    if (func_00248F60(arg0, 0x31E) >= 0) {
        return 1;
    }
    if (arg0 == 0x18E) {
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_004", func_0010F290);

s32 func_0010F450(s32 arg0, u8 *arg1, void *arg2) {
    s32 entries[5];
    s32 i;

    func_0026FD30(arg0, entries);
    if (arg2 == NULL) {
        return -1;
    }
    for (i = 0; i < 5; i++) {
        arg1[i + 6] = 0xFF;
    }

    for (i = 0; i < func_0026FE20(arg0); i++) {
        if ((func_0026FCE0(entries[i]) >> 5) == 5 && func_0010F940(arg0, entries[i]) == 1) {
            arg1[6] = i;
            func_001DCD70(arg2, entries[i]);
            return 1;
        }
    }

    for (i = 0; i < func_0026FE20(arg0); i++) {
        if ((func_0026FCE0(entries[i]) >> 5) == 3 || (func_0026FCE0(entries[i]) >> 5) == 4) {
            arg1[6] = i;
            func_001DCD70(arg2, entries[i]);
            return 1;
        }
    }

    for (i = 0; i < func_0026FE20(arg0); i++) {
        if ((func_0026FCE0(entries[i]) >> 5) != 0 && (func_0026FCE0(entries[i]) >> 5) != 2) {
            arg1[6] = i;
            func_001DCD70(arg2, entries[i]);
            return 1;
        }
    }

    for (i = 0; i < func_0026FE20(arg0); i++) {
        if ((func_0026FCE0(entries[i]) >> 5) != 0) {
            arg1[6] = i;
            func_001DCD70(arg2, entries[i]);
            return 1;
        }
    }
    return -1;
}

s32 func_0010F6F0(s32 arg0) {
    s32 temp_s2;
    s32 temp_s2_2;
    s32 var_s3;
    s32 temp_s3;
    s32 temp_s4;
    u16 temp_v0;
    s32 temp_v0_2;
    u16 temp_v0_3;
    s32 temp_v0_4;
    s32 var_s0;
    s32 var_s4;

    var_s0 = 0;
    if ((arg0 & 0xFF) == 1) {
        var_s3 = 0;
        do {
            temp_v0 = func_0010F850(arg0, var_s3 & 0xFF);
            temp_v0_2 = func_001E3790(temp_v0 & 0xFF, temp_v0 >> 8);
            if (temp_v0_2 >= 0) {
                temp_s4 = temp_v0_2 & 0xFF;
                temp_s2 = func_00250360(temp_v0_2 >> 8, temp_s4);
                if ((temp_s2 == func_001DE540()) && (temp_s4 != 0)) {
                    var_s0 += 1;
                }
            }
            var_s3 += 1;
        } while (var_s3 < 6);
        if (var_s0 >= 2) {
            return 1;
        } else {
            return 0;
        }
    }
    var_s4 = 0;
    do {
        temp_v0_3 = func_0010F850(arg0, var_s4 & 0xFF);
        temp_v0_4 = func_001E3790(temp_v0_3 & 0xFF, temp_v0_3 >> 8);
        if (temp_v0_4 >= 0) {
            temp_s3 = temp_v0_4 & 0xFF;
            temp_s2_2 = func_00250360(temp_v0_4 >> 8, temp_s3);
            if ((temp_s2_2 == func_001DE540()) && (temp_s3 != 0)) {
                var_s0 += 1;
            }
        }
        var_s4 += 1;
    } while (var_s4 < 4);
    if (var_s0 > 0) {
        return 1;
    } else {
        return 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_004", func_0010F850);

INCLUDE_ASM("asm/nonmatchings/main_004", func_0010F940);

typedef struct {
    u8 low : 4;
    u8 high : 4;
} Flags_0010FA60;

typedef struct {
    u16 id;
    u8 action;
    u8 pad3;
    u16 position;
    u8 pad6[6];
    s32 value;
    u8 mode;
} Output_0010FA60;

s32 func_002464F0(s32, s32, s32);
s32 func_0027BE10(s32, s32, s32, s32, s32);

static inline s32 score_0010FA60(s32 arg0) {
    if (func_001DF470(arg0) > 0x5DC) {
        if (func_001E0150(arg0) >= 4) {
            return 0;
        }
        return 0;
    }
    return 0;
}

s32 func_0010FA60(u16 *arg0, s32 arg1, void *arg2, u8 arg3) {
    extern s32 func_00276CC0(s32, s32, s32, s32, s32, u8);
    extern s32 func_00279C40(s32, s32, s32, s32, s32, s32, void *, u8);
    extern s32 func_0010EE00();
    s32 position;
    u8 upperX;
    u8 flag;
    Flags_0010FA60 cells[12];
    s32 i;
    s32 result;
    s32 y;
    s32 score;
    s32 packedY;
    s32 originalY;
    s32 originalX;
    s32 x;
    s32 bestPosition;
    s32 bestScore;
    Output_0010FA60 *out = arg2;

    position = func_001E1090(*arg0 >> 8, *arg0 & 0xFF);
    i = 0;
    do {
        cells[i].low = cells[i].high = 15;
        i++;
    } while (i < 12);

    {
        u16 value = (u16)score_0010FA60(arg1);
        originalX = position & 0xFF;
        originalY = position >> 8;
        if (func_00276CC0(originalX, originalY, *arg0, 3, value, 0) == 0) {
            out->id = *arg0;
            out->action = 6;
            out->position = position;
            out->mode = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, out->position, 1, 0);
            out->value = func_0010EE00(*arg0 >> 8, *arg0 & 0xFF, arg0);
            func_0027B1B0(arg0, arg3);
            return 0;
        } else {
            result = func_002464F0(func_001DF540(*arg0 >> 8, *arg0 & 0xFF), originalX, originalY);
            if (result == 0) {
                out->id = *arg0;
                out->action = 6;
                out->position = position;
                out->mode = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, out->position, 1, 0);
                out->value = func_0010EE00(*arg0 >> 8, *arg0 & 0xFF, arg0);
                func_0027B1B0(arg0, arg3);
                return 0;
            } else {
                u8 startY;
                u8 endY;
                u8 startX;
                s32 end;
                bestPosition = 0xFF;
                bestScore = 0xFFFF;
                startX = func_00250860(0, originalX - (result & 15)) & 0xFF;
                if (originalX + (result & 15) >= 7) {
                    end = 6;
                } else {
                    end = originalX + (result & 15);
                }
                upperX = end & 0xFF;
                startY = func_00250860(0, originalY - (result & 15)) & 0xFF;
                end = originalY + (result & 15);
                if (end >= 7) {
                    end = 6;
                }
                endY = end & 0xFF;
                if ((*arg0 & 0xFF) == 0) {
                    flag = func_0027BBC0(*arg0 >> 8, *arg0 & 0xFF, 0) & 0xFF;
                } else {
                    flag = 0;
                }
                for (x = startX; x <= upperX; x++) {
                    y = startY;
                    packedY = y << 8;
                    for (; y <= endY; packedY += 0x100, y++) {
                        if ((((x < originalX ? originalX : x) -
                              (originalX < x ? originalX : x)) +
                             ((y < originalY ? originalY : y) -
                              (originalY < y ? originalY : y))) <= (result & 15)) {
                            if (func_00279C40(*arg0 >> 8, *arg0 & 0xFF, originalX, originalY, x, y, arg0, flag) == 1 &&
                                (func_0027BE10(*arg0 >> 8, *arg0 & 0xFF, x, y, 0) == 0 || (u8)*arg0 == 0)) {
                                value = (u16)score_0010FA60(arg1);
                                score = func_00276CC0(x, y, *arg0, 3, value, 0);
                                if (score < bestScore) {
                                    bestScore = score;
                                    bestPosition = packedY | x;
                                } else if (score == bestScore &&
                                           func_001E36E0(x, y) == 0 &&
                                           func_001E36E0(bestPosition & 0xFF, bestPosition >> 8) != 0) {
                                    bestScore = score;
                                    bestPosition = packedY | x;
                                }
                            }
                        }
                    }
                }
                if (bestPosition != 0xFF) {
                    out->id = *arg0;
                    out->action = 6;
                    out->position = bestPosition;
                    if (bestPosition == position) {
                        out->mode = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, out->position, 1, 0);
                    } else {
                        out->mode = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, out->position, 1, 0);
                    }
                    out->value = func_0010EE00(*arg0 >> 8, *arg0 & 0xFF, arg0);
                } else {
                    out->id = *arg0;
                    out->action = 6;
                    out->position = position;
                    out->mode = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, out->position, 1, 0);
                    out->value = func_0010EE00(*arg0 >> 8, *arg0 & 0xFF, arg0);
                }
                func_0027B1B0(arg0, arg3);
            }
        }
    }
    return 0;
}

typedef struct Source_0010FFF0 {
    u16 position;
    u8 pad2[6];
    u32 targets;
} Source_0010FFF0;

typedef struct Result_0010FFF0 {
    u16 position;
    u8 kind;
    u8 pad3;
    u16 destination;
    u8 pad6[6];
    s32 action;
    u8 valid;
} Result_0010FFF0;

typedef struct Coord_0010FFF0 {
    u8 x : 4;
    u8 y : 4;
} Coord_0010FFF0;

s32 func_0010EE00(s32, s32, void *);
s32 func_002464F0(s32, s32, s32);
s32 func_00276CC0(s32, s32, s32, s32, s32, u8);

static inline u32 target_0010FFF0(void *src, u8 mode) {
    if (mode == 1) {
        return (u16)(((Source_0010FFF0 *)src)->targets >> 16);
    }
    return *(u16 *)((u8 *)src + 8);
}

static inline s32 flag_0010FFF0(s32 card) {
    if (func_001DF470(card) > 0x5DC) {
        if (func_001E0150(card) >= 4) {
            return 0;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}

static inline s32 distance_0010FFF0(s32 x1, s32 y1, s32 x2, s32 y2) {
    return ((x2 < x1 ? x1 : x2) - (x1 < x2 ? x1 : x2)) +
           ((y2 < y1 ? y1 : y2) - (y1 < y2 ? y1 : y2));
}

static inline s32 closer_0010FFF0(Coord_0010FFF0 *candidate, Coord_0010FFF0 *best, s32 x, s32 y) {
    s32 bestMinY = best->y < y ? best->y : y;
    s32 bestMaxY = y < best->y ? best->y : y;
    s32 bestMinX = best->x < x ? best->x : x;
    s32 bestMaxX = x < best->x ? best->x : x;
    s32 candidateMinY = candidate->y < y ? candidate->y : y;
    s32 candidateMaxY = y < candidate->y ? candidate->y : y;
    s32 candidateMinX = candidate->x < x ? candidate->x : x;
    s32 candidateMaxX = x < candidate->x ? candidate->x : x;

    return (candidateMaxX - candidateMinX) + (candidateMaxY - candidateMinY) <
           (bestMaxX - bestMinX) + (bestMaxY - bestMinY);
}

static inline s32 special_0010FFF0(void *src, s32 x1, s32 y1, s32 x2, s32 y2) {
    s32 x;
    s32 y;
    extern s32 func_001E1030();

    x = ((Source_0010FFF0 *)src)->position & 0xFF;
    y = (s32)((Source_0010FFF0 *)src)->position >> 8;
    if (distance_0010FFF0(x1, y1, x2, y2) != 2) {
        return 0;
    } else if (func_001DF540(y, x) == 0) {
        return 0;
    } else if (func_001E1030(y, x) == 0x1A1) {
        return 0;
    } else if (func_001E2100(y, x, 0) == 0 &&
               func_0024DF00(func_001E22B0(x1, y1), y, x) == 1) {
    } else {
        return 0;
    }
    return 1;
}

s32 func_0010FFF0(void *arg0, s32 arg1, void *arg2, u8 arg3) {
    s32 start;
    s32 best;
    s32 count;
    s32 action;
    s32 bestCost;
    Coord_0010FFF0 coords[12];
    s32 initial;
    s32 end;
    s32 i;
    Coord_0010FFF0 *p;
    u32 targetPosition;
    extern void func_0027A090();
    extern s32 func_0027AFC0();

    targetPosition = target_0010FFF0(arg0, arg3);
    if (func_001DF540(target_0010FFF0(arg0, arg3) >> 8,
                     targetPosition & 0xFF) == 0) {
        func_0027B1B0(arg0, 1);
        return -1;
    }
    initial = func_0010EE00((s32)((Source_0010FFF0 *)arg0)->position >> 8,
                          ((Source_0010FFF0 *)arg0)->position & 0xFF, arg0);
    start = func_001E1090((s32)((Source_0010FFF0 *)arg0)->position >> 8,
                         ((Source_0010FFF0 *)arg0)->position & 0xFF);
    targetPosition = target_0010FFF0(arg0, arg3);
    end = func_001E1090(target_0010FFF0(arg0, arg3) >> 8,
                       targetPosition & 0xFF);
    p = coords;
    i = 0;
    do {
        p->x = p->y = 15;
        i++;
        p++;
    } while (i < 12);
    if (func_002464F0(func_001DF540((s32)((Source_0010FFF0 *)arg0)->position >> 8,
                                   ((Source_0010FFF0 *)arg0)->position & 0xFF),
                     (start & 0xFF), (start >> 8)) == 0) {
        s32 cost;
        ((Result_0010FFF0 *)arg2)->position = ((Source_0010FFF0 *)arg0)->position;
        ((Result_0010FFF0 *)arg2)->kind = 6;
        ((Result_0010FFF0 *)arg2)->destination = start;
        cost = func_00276CC0((start & 0xFF), (start >> 8), arg1, 3, 1, (u8)flag_0010FFF0(arg1));
        if (cost >= func_002509E0((s32)((Source_0010FFF0 *)arg0)->position >> 8,
                                 ((Source_0010FFF0 *)arg0)->position & 0xFF, (start & 0xFF), (start >> 8))) {
            ((Result_0010FFF0 *)arg2)->valid = 1;
        } else {
            ((Result_0010FFF0 *)arg2)->valid = 0;
        }
        return 0;
    } else {
        s32 flag;
        flag = flag_0010FFF0(arg1);
        func_0027A090((s32)((Source_0010FFF0 *)arg0)->position >> 8,
                     ((Source_0010FFF0 *)arg0)->position & 0xFF, coords,
                     (start & 0xFF), (start >> 8), (end & 0xFF), (end >> 8), target_0010FFF0(arg0, arg3),
                     0, 30, (u16)flag);
        count = func_0027AFC0(coords);
        if (count > 0) {
            bestCost = 0xFFFF;
            best = 0xFF;
            action = 0;
            for (i = 0; i < count; i++) {
                if (special_0010FFF0(arg0, (start & 0xFF), (start >> 8), (end & 0xFF), (end >> 8)) == 1) {
                    action = 1;
                    p = &coords[i];
                    best = i;
                    i = count;
                    p->x = (end & 0xFF);
                    p->y = (end >> 8);
                } else {
                    s32 cost;
                    cost = func_00276CC0(coords[i].x, coords[i].y, arg1, 2, 1,
                                        (u8)flag_0010FFF0(arg1));
                    if (cost < bestCost) {
                        bestCost = cost;
                        best = i;
                    } else if (cost == bestCost) {
                        if (closer_0010FFF0(&coords[i], &coords[best], (end & 0xFF), (end >> 8))) {
                            bestCost = cost;
                            best = i;
                        }
                    }
                }
            }
        } else {
            ((Result_0010FFF0 *)arg2)->position = ((Source_0010FFF0 *)arg0)->position;
            ((Result_0010FFF0 *)arg2)->kind = 6;
            ((Result_0010FFF0 *)arg2)->destination = start;
            ((Result_0010FFF0 *)arg2)->action = initial;
            ((Result_0010FFF0 *)arg2)->valid = func_0027E360(
                (s32)((Source_0010FFF0 *)arg0)->position >> 8,
                ((Source_0010FFF0 *)arg0)->position & 0xFF,
                ((Result_0010FFF0 *)arg2)->destination, 0, 0);
            return 0;
        }
        if (best != 0xFF) {
            ((Result_0010FFF0 *)arg2)->position = ((Source_0010FFF0 *)arg0)->position;
            ((Result_0010FFF0 *)arg2)->kind = 6;
            ((Result_0010FFF0 *)arg2)->destination = (coords[best].y << 8) | coords[best].x;
            ((Result_0010FFF0 *)arg2)->action = action;
            ((Result_0010FFF0 *)arg2)->valid = func_0027E360(
                (s32)((Source_0010FFF0 *)arg0)->position >> 8,
                ((Source_0010FFF0 *)arg0)->position & 0xFF,
                ((Result_0010FFF0 *)arg2)->destination, 0, 0);
        } else {
            ((Result_0010FFF0 *)arg2)->position = ((Source_0010FFF0 *)arg0)->position;
            ((Result_0010FFF0 *)arg2)->kind = 6;
            ((Result_0010FFF0 *)arg2)->destination = start;
            ((Result_0010FFF0 *)arg2)->action = action;
            ((Result_0010FFF0 *)arg2)->valid = func_0027E360(
                (s32)((Source_0010FFF0 *)arg0)->position >> 8,
                ((Source_0010FFF0 *)arg0)->position & 0xFF,
                ((Result_0010FFF0 *)arg2)->destination, 0, 0);
            return 0;
        }
    }
    return 0;
}

typedef struct Position_001106F0 {
    u8 x : 4;
    u8 y : 4;
} Position_001106F0;

typedef struct Source_001106F0 {
    u16 id;
    u8 pad2[6];
    u32 target;
} Source_001106F0;

typedef struct Result_001106F0 {
    u16 id;
    u8 kind;
    u8 pad3;
    u16 target;
    u8 pad6[6];
    s32 value;
    u8 flags;
} Result_001106F0;

s32 func_0010EE00(s32, s32, void *);
s32 func_00276CC0(s32, s32, s32, s32, s32, u8);

#define target_001106F0(src, side) ((side) == 1 ? ((((Source_001106F0 *)(src))->target >> 16) & 0xFFFF) : (u32)(u16)((Source_001106F0 *)(src))->target)

#define min_001106F0(a, b) ((a) < (b) ? (a) : (b))
#define max_001106F0(a, b) ((b) < (a) ? (a) : (b))
#define distance_001106F0(pos, src, side) \
    ((max_001106F0((u8)(pos).x, (u32)(u8)target_001106F0(src, side)) - \
      min_001106F0((u8)(pos).x, (u32)(u8)target_001106F0(src, side))) + \
     (max_001106F0((u8)(pos).y, (u32)target_001106F0(src, side) >> 8) - \
      min_001106F0((u8)(pos).y, (u32)target_001106F0(src, side) >> 8)))

static inline s32 scoreflag_001106F0(s32 id) {
    if (func_001DF470(id) > 0x5DC) {
        if (func_001E0150(id) >= 4) {
            return 0;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}

s32 func_001106F0(void *arg0, s32 arg1, void *arg2, u8 arg3, u8 arg4) {
    extern void func_00279230();
    extern s32 func_0027E360(s32, s32, s32, u8, s32);
    Position_001106F0 positions[12];
    s32 start;
    s32 count;

    start = func_001E1090(((Source_001106F0 *)arg0)->id >> 8, ((Source_001106F0 *)arg0)->id & 0xFF);
    {
        s32 score;
        s32 best;
        s32 side = arg3;
        Position_001106F0 *p;
        s32 i;
        if (target_001106F0(arg0, side) == 0xFFFF && start == target_001106F0(arg0, side)) {
            ((Result_001106F0 *)arg2)->id = ((Source_001106F0 *)arg0)->id;
            ((Result_001106F0 *)arg2)->kind = 6;
            ((Result_001106F0 *)arg2)->target = start;
            ((Result_001106F0 *)arg2)->flags = func_0027E360(((Source_001106F0 *)arg0)->id >> 8, ((Source_001106F0 *)arg0)->id & 0xFF, ((Result_001106F0 *)arg2)->target, arg4, 0);
            ((Result_001106F0 *)arg2)->value = func_0010EE00(((Source_001106F0 *)arg0)->id >> 8, ((Source_001106F0 *)arg0)->id & 0xFF, arg0);
            func_0027B1B0(arg0, arg3);
            return 0;
        }
        p = positions;
        {
            s32 clear_count = 0;
            Position_001106F0 *clear = p;
            s32 terrain;
            do {
                clear->x = clear->y = 15;
                clear_count++;
                clear++;
            } while (clear_count < 12);

            terrain = func_001E3790(target_001106F0(arg0, side) & 0xFF, (u32)target_001106F0(arg0, side) >> 8);
            if (terrain < 0) {
                terrain = 0xFFFF;
            }
            func_00279230(((Source_001106F0 *)arg0)->id >> 8, ((Source_001106F0 *)arg0)->id & 0xFF, positions,
                          start & 0xFF, start >> 8, target_001106F0(arg0, side) & 0xFF,
                          (u32)target_001106F0(arg0, side) >> 8, (u16)terrain, 7);
            count = func_0027AFC0((u8 *)positions);
        }
        if (count > 0) {
            best = 0xFF;
            score = 0xFFFF;
            for (i = 0; i < count; i++, p++) {
                if (func_001E36E0(p->x, p->y) == 0) {
                    s32 value = func_00276CC0(p->x, p->y, arg1, 2, 1, (u8)scoreflag_001106F0(arg1));
                    if (value < score) {
                        score = value;
                        best = i;
                    } else if (value == score) {
                        if (distance_001106F0(*p, arg0, side) < distance_001106F0(positions[best], arg0, side)) {
                            score = value;
                            best = i;
                        }
                    }
                }
            }
        } else {
            ((Result_001106F0 *)arg2)->id = ((Source_001106F0 *)arg0)->id;
            ((Result_001106F0 *)arg2)->kind = 6;
            ((Result_001106F0 *)arg2)->target = start;
            ((Result_001106F0 *)arg2)->flags = func_0027E360(((Source_001106F0 *)arg0)->id >> 8, ((Source_001106F0 *)arg0)->id & 0xFF, ((Result_001106F0 *)arg2)->target, arg4, 0);
            ((Result_001106F0 *)arg2)->value = func_0010EE00(((Source_001106F0 *)arg0)->id >> 8, ((Source_001106F0 *)arg0)->id & 0xFF, arg0);
            func_0027B1B0(arg0, arg3);
            return 0;
        }
        if (best != 0xFF) {
            ((Result_001106F0 *)arg2)->id = ((Source_001106F0 *)arg0)->id;
            ((Result_001106F0 *)arg2)->kind = 6;
            ((Result_001106F0 *)arg2)->target = (positions[best].y << 8) | positions[best].x;
            ((Result_001106F0 *)arg2)->flags = func_0027E360(((Source_001106F0 *)arg0)->id >> 8, ((Source_001106F0 *)arg0)->id & 0xFF, ((Result_001106F0 *)arg2)->target, arg4, 0);
            ((Result_001106F0 *)arg2)->value = func_0010EE00(((Source_001106F0 *)arg0)->id >> 8, ((Source_001106F0 *)arg0)->id & 0xFF, arg0);
        } else {
            ((Result_001106F0 *)arg2)->id = ((Source_001106F0 *)arg0)->id;
            ((Result_001106F0 *)arg2)->kind = 6;
            ((Result_001106F0 *)arg2)->target = start;
            ((Result_001106F0 *)arg2)->flags = func_0027E360(((Source_001106F0 *)arg0)->id >> 8, ((Source_001106F0 *)arg0)->id & 0xFF, ((Result_001106F0 *)arg2)->target, arg4, 0);
            ((Result_001106F0 *)arg2)->value = func_0010EE00(((Source_001106F0 *)arg0)->id >> 8, ((Source_001106F0 *)arg0)->id & 0xFF, arg0);
        }
        func_0027B1B0(arg0, arg3);
    }
    return 0;
}

typedef struct {
    u16 unk0;
    u8 unk2;
    u8 pad3;
    u16 unk4;
    u8 unk6[5];
    u8 padB;
    s32 unkC;
    u8 unk10;
} Req_00110F00;

typedef struct {
    u8 pad0[0x160];
    u16 list[32];    /* 0x160 */
    u8 idx : 5;      /* 0x1A0 */
    u8 pad1A0 : 3;
    u8 pad1A1;
    u16 count;       /* 0x1A2 */
} Work_00110F00;

s32 func_0010C940(void *, void *, s32);
s32 func_00276290(void *, void *, s32);

s32 func_00110F00(s32 arg0, void *arg1) {
    Req_00110F00 req;
    Work_00110F00 *w;
    s32 i;
    s32 ret;

    w = arg1;
    req.unk0 = 0xFFFF;
    req.unk2 = 0xFF;
    req.unk4 = 0xFFFF;
    req.unkC = 0;
    req.unk10 = 0xFF;
    if (w == NULL) {
        return 0x800;
    }
    for (i = 0; i < 5; i++) {
        req.unk6[i] = 0xFF;
    }
    w->count++;
    if (w->count == 600) {
        return 0x20;
    }
    if (w->count == 601) {
        return 0x20;
    }
    if (w->count == 602) {
        return 0x20;
    }
    if (!(w->count < 603)) {
        return 0x800;
    }
    if (w->idx == 0) {
        func_00275E80(w);
        if (func_0010C940(w, &req, arg0) == 0) {
            return 0x800;
        }
        if (func_00276290(w, &req, arg0) < 0) {
            return 0;
        }
    }
    ret = w->list[w->idx - 1];
    if (ret == 0xFFFF) {
        return 0;
    }
    if (w->list[w->idx] == 0xFFFF) {
        w->idx = 0;
        for (i = 0; i < 32; i++) {
            w->list[i] = 0xFFFF;
        }
    } else {
        w->idx++;
    }
    return (u16)ret;
}

#define MAX_001110D0(a, b) ((a) > (b) ? (a) : (b))
#define MIN_001110D0(a, b) ((a) < (b) ? (a) : (b))

s32 func_001110D0(s32 arg0) {
    extern s32 func_001E1580(s32, s32);
    extern s32 func_001E1640(s32, s32);
    s32 pos;
    s32 x0;
    s32 y0;
    u16 *p;
    s32 x;
    s32 y;
    s32 bestPos;
    s32 i;
    s32 best;
    u32 obj;
    s32 score;
    s32 cur;
    s32 found;
    u16 list[22];

    pos = func_001E1090(arg0 == 0 ? 1 : 0, 0);
    if (func_00266DF0(0x39) > 0) {
        return -1;
    }
    obj = func_00272210(func_0024CA40(0, 0, arg0, 2, 0x21, 0xE), arg0);
    p = list;
    for (i = 0; i < 22; i++) {
        p[i] = 0xFFFF;
    }
    func_0027C070(arg0 == 0 ? 1 : 0, list, 0x34, 0);
    found = -1;
    bestPos = found;
    best = 1;
    i = 0;
    if (i < func_0027C670(list)) {
        x0 = pos >> 8;
        y0 = pos & 0xFF;
        do {
            cur = func_001E1090(*p >> 8, *p & 0xFF);
            x = cur >> 8;
            y = cur & 0xFF;
            if (MAX_001110D0(y0, y) - MIN_001110D0(y0, y) + (MAX_001110D0(x0, x) - MIN_001110D0(x0, x)) == 1) {
                if (func_001E2100(*p >> 8, *p & 0xFF, 1) == 0 &&
                    func_001E1580(*p >> 8, *p & 0xFF) == 0 &&
                    func_001E1640(*p >> 8, *p & 0xFF) == 0) {
                    if ((score = func_002509E0(*p >> 8, *p & 0xFF, y, x)) >= best) {
                        bestPos = *p;
                        if (bestPos == func_0024EC50(obj, 0)) {
                            found = bestPos;
                        }
                        best = score;
                    }
                }
            }
            p++;
            i++;
        } while (i < func_0027C670(list));
    }
    if (bestPos < 0) {
        return -1;
    }
    return ((u16)bestPos << 16) | (u16)found;
}

s32 func_00111320(s32 arg0, s32 arg1) {
    s16 buffer[24];
    s32 mask;
    s32 count;
    s32 owner;
    u32 *effect;
    s32 card;
    s32 position;
    s32 unit;
    extern s32 func_001E1030();
    extern s32 func_001E1580();
    extern s32 func_001DEE50();
    extern s32 func_00215D30();

    mask = 0;
    count = 0;
    card = func_001E1030();
    position = func_001E1090(arg0, arg1);
    owner = func_00250360(arg0, arg1);
    effect = func_001E0B70(arg0, arg1, 0);
    func_0024C910(owner, 2, buffer);
    if (func_001E2100(arg0, arg1, 4) != 0) {
        return 0;
    }
    if (func_00112960(card) == 1) {
        if (func_00112980(owner) == 1 && func_00112A40(owner) == 4) {
            return 1;
        }
    }
    switch (func_001E0700(arg0, arg1) >> 5) {
    case 5:
        if (func_0027D830(arg0, arg1, 0, 0, 6, 0) == 5) {
            return 2;
        }
        if (func_00112850(func_00250360(arg0, arg1), card) == 1 &&
            func_001E22B0(position & 0xFF, position >> 8) != 9) {
            return 1;
        }
        break;
    case 1:
        if (func_0027D830(arg0, arg1, 0, 0, 6, 0) == 5) {
            return 2;
        }
        if (effect == NULL) {
            return 2;
        }
        switch (effect[0] >> 8) {
        case 0x17:
        case 0x49:
            if (func_001123C0(owner, (effect[0] >> 6) & 3, effect[0] & 0x3F) == 1) {
                return 1;
            }
            break;
        case 0x18:
        {
            s32 index;
            mask = func_0024CA40(0, 0, owner, 2, 0x34, 0xE);
            for (index = 0; index < func_0024E910(mask); index++) {
                unit = func_0024EC50(mask, index);
                if (func_001E2100(unit >> 8, unit & 0xFF, 4) == 1) {
                    count++;
                }
            }
            if (count > 5) {
                return 1;
            }
            break;
        }
        case 2:
            unit = func_0027C770(func_001DF540(arg0, arg1), position & 0xFF,
                                position >> 8, *((u8 *)effect + 4), 8, 2);
            if (unit >= 0 && unit == position) {
                return 1;
            }
            break;
        case 4:
            switch (effect[1] >> 16) {
            case 0x12:
                unit = func_00112600(arg0, (s32 *)effect);
                if (unit >= 0 && ((position & 0xFF) == (unit & 0xFF) ||
                                  (position >> 8) == (unit >> 8))) {
                    return 1;
                }
                break;
            case 0x13:
            default:
                if (func_001123C0(owner, (effect[0] >> 6) & 3, effect[0] & 0x3F) == 1) {
                    return 1;
                }
                break;
            }
            break;
        case 0xD:
            if (((effect[0] >> 6) & 3) == 1) {
                if ((effect[1] >> 16) == 4) {
                    if (func_001DF470(owner) <= 1200) {
                        return 1;
                    }
                    break;
                }
                return 1;
            }
            if ((effect[0] & 0x3F) == 0x32) {
                if (func_0024E780(owner == 0 ? 1 : 0, 3) > 3) {
                    return 1;
                }
                break;
            }
            return 1;
        case 0x1F:
            if (card == 0x2DD && func_001110D0(owner) >= 0) {
                return 1;
            }
            break;
        case 0x20:
            mask = 0;
            do {
                if (func_001E1580(arg0, mask) == 0xFF) {
                    return 1;
                }
                mask++;
            } while (mask < 11);
            break;
        case 0x12:
            if (func_0024E910(func_0024CA40(0, 0, owner, 1, effect[0] & 0x3F, 0xE)) > 2) {
                return 1;
            }
            break;
        case 0x21:
            {
                s32 targetPosition;
                s32 sourcePosition;
                s32 targetY;

                func_0027C2C0(owner == 0 ? 1 : 0, (u16 *)buffer, 0x1D, 0, 0);
                unit = func_0027B650((u16 *)buffer);
                arg0 = unit >> 8;
                arg1 = unit & 0xFF;
                sourcePosition = func_001E1090(arg0, arg1);
                func_0027C070(owner, (u16 *)buffer, 0x1D, 1);
                unit = func_0027B650((u16 *)buffer);
                card = unit >> 8;
                targetY = unit & 0xFF;
                targetPosition = func_001E1090(card, targetY);
                func_0024C910(owner, 1, buffer);
                owner = sourcePosition & 0xFF;
                count = sourcePosition >> 8;
                if (func_002509E0(arg0, arg1, owner, count) >= 3000) {
                    count = func_002509E0(arg0, arg1, owner, count);
                    if (func_002509E0(card, targetY, targetPosition & 0xFF, targetPosition >> 8) < count) {
                        return 1;
                    }
                }
            }
            break;
        case 0x36:
            return 1;
        case 0x25:
            switch (effect[0] & 0x3F) {
            case 0x21:
                if (func_0027BBC0(arg0, arg1, 0) == 1) {
                    return 1;
                }
                break;
            case 0x22:
                if (func_0027BBC0(owner, 0, 0) == 1) {
                    return 1;
                }
                break;
            case 0x34:
            default:
                if (func_0027BBC0(owner, 0, 0) == 1) {
                    return 1;
                }
                break;
            }
            break;
        case 0x26:
            if (func_001DE6D0(owner) == 0) {
                return 1;
            }
            break;
        case 0x27:
            if (func_001DE5C0(owner) < 4) {
                return 1;
            }
            break;
        case 0x28:
            if (func_0027BBC0(owner, 0, 0) == 1) {
                return 1;
            }
            break;
        }
        break;
    case 0:
        if (func_002507D0(arg0, arg1) == 0) {
            return 2;
        }
        effect = func_00250740(arg0, arg1, 2);
        if (effect == NULL) {
            return 2;
        }
        switch (effect[0] >> 8) {
        case 0xC:
        case 0x34:
        case 0xD:
        case 0xE:
        case 0x22:
        case 0x3B:
        case 0x56:
        case 0x43:
        case 0xF:
            return 1;
        case 0xB:
        case 0x4E:
        case 0x12:
        case 0x4D:
        case 6:
            mask = func_0024CA40(0, 0, arg0, 1, effect[0] & 0x3F, 0xE);
            if ((u32)mask > 1) {
                return 1;
            }
            break;
        case 0x13:
        case 0x17:
            if (((effect[0] >> 6) & 1) && func_0024CA40(0, 0, arg0, 1, effect[0] & 0x3F, 0xE)) {
                return 2;
            }
            mask = func_0027E150(func_0024CA40(0, 0, arg0, 2, effect[0] & 0x3F, 0xE));
            if ((u32)mask > 2) {
                return 1;
            }
            break;
        case 0x47:
        {
            s32 y;
            s32 x;
            s32 index;
            mask = func_0024CA40(0, 0, arg0, 2, 0x34, 0xE);
            for (index = 0; index < func_0024E910(mask); index++) {
                unit = func_0024EC50(mask, index);
                x = unit >> 8;
                y = unit & 0xFF;
                if (func_001E1580(x, y) > 0 && func_001E1580(x, y) != 0xFF) {
                    return 1;
                }
            }
            break;
        }
        case 0x53:
        {
            s32 index;
            for (index = 0; index < func_001DEE50(arg0); index++) {
                if ((func_0026FCE0(func_001DEE00(arg0, index)) >> 5) == 0) {
                    count++;
                }
            }
            for (index = 0; index < func_001DEE50(arg0 == 0 ? 1 : 0); index++) {
                if ((func_0026FCE0(func_001DEE00(arg0 == 0 ? 1 : 0, index)) >> 5) == 0) {
                    count++;
                }
            }
            if (count > 5) {
                return 1;
            }
            break;
        }
        case 0x54:
            mask = func_0024CA40(0, 0, arg0, 3, 0x21, 0xE);
            unit = func_0024EC50(mask, 0);
            if (arg0 == func_00250360(unit >> 8, unit & 0xFF) && unit != ((arg0 << 8) | arg1)) {
                return 1;
            }
            break;
        case 0x55:
        {
            s32 y;
            s32 x;
            s32 index;
            mask = func_0024CA40(0, 0, arg0, 1, 0x34, 0xE);
            for (index = 0; index < func_0024E910(mask); index++) {
                unit = func_0024EC50(mask, index);
                x = unit >> 8;
                y = unit & 0xFF;
                if (func_001E1580(x, y) > 0 && func_001E1580(x, y) != 0xFF) {
                    return 1;
                }
            }
            break;
        }
        case 0x58:
            if (func_00215D30(arg0 == 0 ? 1 : 0, func_001E1030(arg0 == 0 ? 1 : 0, 0)) >= 6) {
                return 1;
            }
            break;
        }
        effect = func_00250740(arg0, arg1, 3);
        if (effect == NULL) {
            return 2;
        }
        switch (effect[0] >> 8) {
        case 0x12:
            if ((effect[1] >> 16) == 0x16) {
                unit = func_0024CA40(0, 0, owner, 1, effect[0] & 0x3F, 0x16);
            } else {
                unit = func_0024CA40(0, 0, owner, 1, ((effect[1] >> 16) << 16) | (effect[0] & 0x3F), 0xE);
            }
            if (func_0024E910(unit) > 2) {
                return 1;
            }
            break;
        case 0x33:
            if (func_0024E910(func_0024CA40(0, 0, owner, 1, ((effect[1] >> 16) << 16) | (effect[0] & 0x3F), 0xE)) > 2) {
                return 1;
            }
            break;
        case 0x17:
            if ((effect[0] & 0x3F) == 0x1A) {
                return 2;
            }
            if (func_001123C0(owner, (effect[0] >> 6) & 3, effect[0] & 0x3F) == 1) {
                return 1;
            }
            break;
        case 0xD:
            return 1;
        case 0x23:
            if (func_001123C0(owner, (effect[0] >> 6) & 3, effect[0] & 0x3F) == 1) {
                return 1;
            }
            break;
        case 0x18:
        {
            s32 targets;
            s32 index;

            targets = func_0024CA40(0, 0, owner, 1, effect[0] & 0x3F, 0xE);
            for (index = 0; index < func_0024E910(targets); index++) {
                unit = func_0024EC50(targets, index);
                if (func_001E2100(unit >> 8, unit & 0xFF, 4) == 1) {
                    count++;
                }
            }
            if (count > 2) {
                return 2;
            }
            {
                s32 unavailable;
                s32 others;
                s32 otherIndex;

                unavailable = 0;
                others = func_0024CA40(0, 0, owner, 2, effect[0] & 0x3F, 0xE);
                for (otherIndex = 0; otherIndex < func_0024E910(others); otherIndex++) {
                    unit = func_0024EC50(others, otherIndex);
                    if (func_001E2100(unit >> 8, unit & 0xFF, 4) == 1) {
                        unavailable++;
                    }
                }
                if (unavailable > 5) {
                    return 1;
                }
            }
            break;
        }
        case 4:
        {
            s32 y;
            s32 x;
            s32 index;
            if ((effect[0] & 0x3F) == 0x1A) {
                return 2;
            }
            if ((effect[0] & 0x3F) == 0x30) {
                if (func_001123C0(owner, (effect[0] >> 6) & 3, effect[0] & 0x3F) == 1) {
                    return 1;
                }
            } else {
                if ((effect[1] >> 16) != 0) {
                    unit = func_001E1090(arg0, arg1);
                    mask = func_0024CA40(unit & 0xFF, unit >> 8, owner, (effect[0] >> 6) & 3,
                                        effect[0] & 0x3F, effect[1] >> 16);
                } else {
                    mask = func_0024CA40(0, 0, owner, (effect[0] >> 6) & 3, effect[0] & 0x3F, 0xE);
                }
            }
            for (index = 0; index < func_0024E910(mask); index++) {
                unit = func_0024EC50(mask, index);
                x = unit >> 8;
                y = unit & 0xFF;
                if (owner == func_00250360(x, y)) {
                    return 2;
                }
                if (func_001E2100(x, y, 4) != 0) {
                    count++;
                }
            }
            if (count > 1) {
                return 1;
            }
            break;
        }
        case 0x1A:
            if (func_001DE5C0(arg0) < 4) {
                return 1;
            }
            break;
        case 0x26:
            if (func_001DE6D0(owner) == 0) {
                return 1;
            }
            break;
        case 0x1F:
            if (func_00266DF0(0x39) > 0) {
                return 2;
            }
            if ((effect[0] & 0x3F) == 0x1A) {
                return 2;
            }
            if (func_0024E910(func_0024CA40(0, 0, owner, (effect[0] >> 6) & 3, effect[0] & 0x3F, 0xE)) > 2) {
                return 1;
            }
            break;
        case 0x3C:
            if (func_0024CA40(position & 0xFF, position >> 8, owner, 1,
                             ((u32)*((u16 *)effect + 2) << 16) | (effect[0] & 0x3F), 1) &&
                func_0024E220(owner == 0 ? 1 : 0, 1) >= 0) {
                return 1;
            }
            break;
        case 0x46:
            if (func_0027BBC0(owner, 0, 0) == 1) {
                return 1;
            }
            break;
        case 0xC:
            return 1;
        case 0x57:
            if (func_001DF110(owner) == 0) {
                return 1;
            }
            break;
        }
        break;
    default:
        break;
    }
    return 2;
}

s32 func_001123C0(s32 arg0, s32 arg1, s32 arg2) {
    s32 best_other;
    s32 best_own;
    s32 list;
    s32 i;
    s32 card;
    s32 lo;
    s32 hi;
    s32 value;

    for (i = 0; i < 22; i++) {
    }
    best_own = -1;
    best_other = -1;
    list = func_0024CA40(0, 0, arg0, arg1, arg2, 14);
    for (i = 0; i < func_0024E910(list); i++) {
        card = func_0024EC50(list, i);
        hi = card >> 8;
        lo = card & 0xFF;
        if (arg0 == func_00250360(hi, lo)) {
            value = func_002509E0(hi, lo, func_001E1090(hi, lo) & 0xFF, func_001E1090(hi, lo) >> 8);
            if (best_own < value) {
                best_own = value;
            }
        } else {
            value = func_002509E0(hi, lo, func_001E1090(hi, lo) & 0xFF, func_001E1090(hi, lo) >> 8);
            if (best_other < value) {
                best_other = value;
            }
        }
    }
    if (best_own < best_other && best_other > 3000) {
        return 1;
    }
    if (arg1 & 1) {
        if (func_0024E910(func_0024CA40(0, 0, arg0, 1, arg2, 14)) > 0) {
            return 0;
        }
    }
    if (arg1 >> 1) {
        if (func_0024E910(func_0024CA40(0, 0, arg0, 2, arg2, 14)) > 3) {
            return 1;
        }
    }
    return 0;
}

s32 func_00112600(s32 arg0, s32 *arg1) {
    u16 cells[0x16];
    s32 first;
    s32 second;
    s32 pos;
    s32 y;
    s32 i;
    s32 list;
    s32 x;
    u8 count;
    s32 cell;
    s32 col;
    s32 row;
    s32 j;

    for (j = 0; j < 0x16; j++) {
        cells[j] = 0xFFFF;
    }
    switch (*arg1 & 0x3F) {
    case 0x1D:
        func_0027C2C0((arg0 == 0) ? 1 : 0, cells, 0x1D, 0, 0);
        first = func_0027B650(cells);
        for (j = 0; j < 0x16; j++) {
            cells[j] = 0xFFFF;
        }
        func_0027C070(arg0, cells, 0x1D, 1);
        second = func_0027B650(cells);
        if (first >= 0 && second >= 0) {
            pos = func_001E1090(first >> 8, first & 0xFF);
            if (func_002781F0(first, second, pos & 0xFF, pos >> 8) >= 0) {
                return pos;
            }
        }
        break;
    case 0x1E:
        for (x = 0; x < 7; x++) {
            for (y = 0; y < 7; y++) {
                count = 0;
                list = func_0024CA40(x, y, arg0, 1, 0x34, 0x12);
                for (i = 0; i < func_0024E910(list); i++) {
                    cell = func_0024EC50(list, i);
                    row = cell >> 8;
                    col = cell & 0xFF;
                    if (func_001E2100(row, col, 4) == 0) {
                        count++;
                    } else if ((func_001E0700(row, col) >> 5) != 0) {
                        count++;
                    }
                }
                if (count > 2) {
                    return (y << 8) | x;
                }
            }
        }
        break;
    }
    return -1;
}

typedef struct {
    s32 unk0;
    s32 value;
} Data_00112850;

s32 func_00112850(s32 arg0, s32 arg1) {
    extern u32 func_0026FBB0();
    s32 state[4];
    s32 index;
    s32 mask;
    u32 limit;
    s32 low;
    s32 high;
    s32 encoded;
    s32 position;
    Data_00112850 *data;

    data = func_0026FC90(arg1, 0);
    func_00254C90(state, data->value);
    limit = func_0026FBB0(data->value) >> 16;
    if ((mask = func_00254890(state, arg0)) < 0) {
        return 0;
    } else {
        for (index = 0; index < func_0024E910(mask); index++) {
            encoded = func_0024EC50(mask, index);
            high = encoded >> 8;
            low = encoded & 0xFF;
            position = func_001E1090(high, low);
            if (func_002509E0(high, low, position & 0xFF, position >> 8) >= limit) {
                return 0;
            }
        }
        return 1;
    }
}

s32 func_00112960(s32 arg0) {
    s32 result;

    result = (u32) (arg0 - 0x36) < 4U ? 1 : 0;
    return result;
}

s32 func_00112980(s32 arg0) {
    extern s32 func_001E1030();

    if (func_001E1030(arg0, 0) == 0x3A) {
        if (func_002151D0(arg0, func_002158B0(arg0), 0x36) >= 0 && func_002151D0(arg0, func_002158B0(arg0), 0x37) >= 0 && func_002151D0(arg0, func_002158B0(arg0), 0x38) >= 0 && func_002151D0(arg0, func_002158B0(arg0), 0x39) >= 0) {
            return 1;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_004", func_00112A40);

INCLUDE_ASM("asm/nonmatchings/main_004", func_00112B90);

typedef struct {
    u16 card;       /* 0x0 */
    u8 pad2[2];
    s16 target;     /* 0x4 */
    u8 pad6[2];
    s32 f8;         /* 0x8 */
} Action_00113140;

s32 func_00113140(void *arg0, s32 arg1) {
    extern s32 func_00113760();
    extern s32 func_00113BB0();
    extern s32 func_00113ED0();
    Action_00113140 *act = arg0;
    u16 card;
    s32 low;
    s32 temp_s0;
    s32 type;

    card = act->card;
    func_001E1090(card >> 8, card & 0xFF);
    card = act->card;
    temp_s0 = func_00250360(card >> 8, card & 0xFF);
    card = act->card;
    if (func_001DF540(card >> 8, card & 0xFF) != 0) {
        card = act->card;
        if (func_001E2100(card >> 8, card & 0xFF, 0) == 0) {
            card = act->card;
            if (card != 0xFFFF) {
                low = card & 0xFF;
                if (low == 0) {
                    if (act->f8 == -1) {
                        if (func_0027BBC0(card >> 8, low, 0) == 1) {
                            if (func_001DE6D0(act->card >> 8) == 1) {
                                act->target = 0x50A;
                            } else {
                                act->target = 0x5FF;
                            }
                        } else {
                            if (func_001DE6D0(act->card >> 8) == 1) {
                                act->target = 0xA06;
                                act->f8 = (act->f8 & 0xFFFF0000) | 0x101;
                            } else {
                                act->target = 0x6FF;
                                act->f8 = (act->f8 & 0xFFFF) | 0x01010000;
                            }
                        }
                    }
                } else {
                    type = func_001E0700(card >> 8, low) >> 5;
                    switch (type) {
                    case 0:
                        card = act->card;
                        if (func_002507D0(card >> 8, card & 0xFF) == 1) {
                            func_00113BB0(arg0, arg1);
                        } else {
                            func_00113760(arg0, 1, arg1);
                        }
                        break;
                    case 2:
                        func_0027CA50(arg0, 5, 0, func_00117C30(temp_s0) & 0xFF);
                        break;
                    case 1:
                    case 3:
                        func_00113ED0(arg0, arg1);
                        break;
                    default:
                        act->target = 0x5FF;
                        break;
                    }
                }
                return 1;
            }
        }
    }
    return 0;
}

s32 func_00113370(u16 *arg0, s32 arg1, s32 arg2, void *arg3) {
    s32 i;
    s32 pos;
    s32 ret;
    s32 idx;
    u16 list[22];

    for (i = 0; i < 22; i++) {
        list[i] = 0xFFFF;
    }
    func_0027C070(arg1, list, 0x1D, 1);
    ret = func_0027B360(arg1, list, arg0);
    if (ret >= 0) {
        return ret;
    }
    for (i = 0; i < 22; i++) {
        list[i] = 0xFFFF;
    }
    func_0027C070(arg1, list, 0x1E, 1);
    for (i = 0; i < func_0027C670(list); i++) {
        if ((func_001E0700(list[i] >> 8, list[i] & 0xFF) >> 5) == 3 &&
            func_0027B9B0(list[i]) == 1 && func_0027C6D0(list[i]) == 1) {
            return list[i];
        }
    }
    pos = arg1 << 8;
    idx = func_00276C80(arg0, pos);
    func_00113140(arg0 + idx * 8, arg2);
    if (((arg0[idx * 8 + 2] >> 8) & 0xFF) == 10) {
        if (func_001DE6D0(arg1) == 1 && func_00114080(pos, arg1, arg3) >= 0) {
            return pos | 0x10000;
        }
        if (func_0027B9B0(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (func_001E2100(arg1, 0, 0) == 0) {
        if (func_0027B9B0(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (func_001DE6D0(arg1) == 1 && func_00114080(pos, arg1, arg3) >= 0) {
        return pos | 0x10000;
    }
    for (i = 0; i < 22; i++) {
        list[i] = 0xFFFF;
    }
    func_0027C070(arg1, list, 0x1F, 1);
    for (i = 0; i < func_0027C670(list); i++) {
        if (func_0027B9B0(list[i]) == 1 && func_0027C6D0(list[i]) == 1) {
            return list[i];
        }
    }
    for (i = 0; i < 22; i++) {
        list[i] = 0xFFFF;
    }
    func_0027C070(arg1, list, 0x1F, 1);
    for (i = 0; i < func_0027C670(list); i++) {
        if (func_001E2100(list[i] >> 8, list[i] & 0xFF, 0) == 0 && func_0027C6D0(list[i]) == 1) {
            return list[i];
        }
    }
    return -1;
}

typedef struct Event_00113760 {
    u16 id;
    u16 pad2;
    u16 state;
    u16 pad6;
    union {
        u32 word;
        u16 low;
    } data;
} Event_00113760;

typedef struct Entry_00113760 {
    u16 id;
    u8 state;
    u8 pad;
} Entry_00113760;

void func_00113760(void *arg0, s32 arg1, s32 arg2) {
    extern void func_0027E770();
    extern s32 func_0027B200();
    extern s32 func_00113A00();
    extern void func_00113A60();
    s32 position;
    u8 buffer[0x70];
    Entry_00113760 entries[22];
    s16 countA;
    s16 countB;

    if (func_001DF540(((Event_00113760 *)arg0)->id >> 8,
                       ((Event_00113760 *)arg0)->id & 0xFF) != 0) {
        s32 player;
        s32 other;
        s32 step;
        s32 card;
        s32 i;
        Entry_00113760 *p;

        player = func_0024DE70(((Event_00113760 *)arg0)->id >> 8,
                              ((Event_00113760 *)arg0)->id & 0xFF);
        other = (player == 0 ? 1 : 0) << 8;
        position = func_001E1090(((Event_00113760 *)arg0)->id >> 8,
                                ((Event_00113760 *)arg0)->id & 0xFF);
        step = func_001E1090(other >> 8, other & 0xFF);
        card = func_001DF540(((Event_00113760 *)arg0)->id >> 8,
                            ((Event_00113760 *)arg0)->id & 0xFF);
        p = entries;
        i = 0;
        do {
            ++i;
            p->id = 0xFFFF;
            p->state = 0xFF;
            ++p;
        } while (i < 22);
        func_0027E770(buffer);
        if (arg1 != 0) {
            if (func_0027B200(((Event_00113760 *)arg0)->id >> 8,
                             ((Event_00113760 *)arg0)->id & 0xFF,
                             position & 0xFF, position >> 8,
                             other >> 8, other & 0xFF,
                             step & 0xFF, step >> 8, 2) > 0) {
                ((Event_00113760 *)arg0)->state = 0x2FF;
                ((Event_00113760 *)arg0)->data.word = (other << 16) |
                    ((Event_00113760 *)arg0)->data.low;
                return;
            }
        }
        step = 1;
        countB = 0;
        countA = 0;
        for (; step <= (arg2 != 0 ? 5 : 2); ++step) {
            s32 limit = arg2 != 0 ? 5 : 2;
            s32 side;
            s32 result;

            side = func_0024DE70(((Event_00113760 *)arg0)->id >> 8,
                                ((Event_00113760 *)arg0)->id & 0xFF) == 0 ? 1 : 0;
            result = func_00113A00(arg0, 0, card, position & 0xFF, position >> 8,
                                  side, step & 0xFF, func_00117C30(player),
                                  entries, 0, &countA, &countB, limit & 0xFF, buffer);
            switch (result) {
                case 3:
                    ((Event_00113760 *)arg0)->state = 0x6FF;
                    ((Event_00113760 *)arg0)->data.word = (position << 16) |
                        ((Event_00113760 *)arg0)->data.low;
                    return;
                case 2:
                    ((Event_00113760 *)arg0)->state = 0x3FF;
                    ((Event_00113760 *)arg0)->data.word = (position << 16) |
                        ((Event_00113760 *)arg0)->data.low;
                    return;
                case 1:
                    return;
                case 0:
                    ((Event_00113760 *)arg0)->state = 0x5FF;
                    return;
            }
        }
        func_00113A60(arg0, arg2);
    }
}

void func_00113A00(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28) {
    func_0027DE20(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
                  arg_sp0, arg_sp8, arg_sp10, arg_sp18, arg_sp20,
                  0, 3000, arg_sp28);
}

typedef struct {
    u16 position;
    u8 pad2[2];
    u16 state;
    u8 pad6[2];
    union {
        u16 low;
        u32 value;
    } flags;
} Data_00113A60;

void func_00113A60(void *arg0) {
    Data_00113A60 *data = arg0;
    s32 pair;
    s32 low;

    func_00250360(data->position >> 8, data->position & 0xFF);
    pair = func_001E1090(data->position >> 8, data->position & 0xFF);
    if (func_0024DF00(3, data->position >> 8, data->position & 0xFF) == 1) {
        data->state = 0x6FF;
        data->flags.value = data->flags.low | (func_00113B60(pair & 0xFF, pair >> 8) << 16);
    } else {
        low = pair & 0xFF;
        data->state = 0x6FF;
        if (low < 3 && (pair >> 8) < 3) {
            data->flags.value = data->flags.low | 0x03030000;
        } else if (low >= (pair >> 8)) {
            data->flags.value = data->flags.low | 0x03050000;
        } else {
            data->flags.value = data->flags.low | 0x05030000;
        }
    }
}

s32 func_00113B60(s32 arg0, s32 arg1) {
    s32 result;

    if (arg1 >= 5) {
        result = 0x602;
    } else if (arg0 >= 5) {
        result = 0x206;
    } else if (arg0 >= arg1) {
        result = 0x105;
    } else {
        result = 0x501;
    }
    return result;
}

INCLUDE_ASM("asm/nonmatchings/main_004", func_00113BB0);

typedef struct {
    u16 key;
    u16 unk2;
    s16 status;
    u16 unk6;
    union {
        u16 low;
        u32 word;
    } value;
} Data_00113ED0;


void func_00113ED0(void *arg0) {
    Data_00113ED0 *arg;
    s32 search_key;
    s32 compare_key;
    s32 *object;
    s32 result;
    u32 kind;
    s32 status;

    arg = (Data_00113ED0 *)arg0;
    search_key = func_00250360(arg->key >> 8, arg->key & 0xFF);
    compare_key = func_001E1090(arg->key >> 8, arg->key & 0xFF);
    object = func_00250740(arg->key >> 8, arg->key & 0xFF, 0);
    if (object == NULL) {
        arg->status = 0x5FF;
        return;
    }
    switch (func_001E0700(arg->key >> 8, arg->key & 0xFF) >> 5) {
    case 1:
        kind = (u32)*object >> 8;
        if (kind != 4) {
            status = 0xCFF;
            switch (kind) {
            case 2:
                arg->status = 0x6FF;
                arg->value.word = arg->value.low | 0x03030000;
                return;
            case 20:
                arg->status = 0xCFF;
                return;
            }
        } else {
            result = func_00112600(search_key, object);
            if (result >= 0) {
                arg->status = 0x6FF;
                if ((*object & 0x3F) == 0) {
                    arg->value.word = arg->value.low | (((compare_key >> 8) << 8 | (result & 0xFF)) << 16);
                } else {
                    arg->value.word = (result << 16) | arg->value.low;
                }
                return;
            }
        }
        goto fail_status;
    case 3:
        if (func_0027D720(arg0, 0) == 1) {
            arg->status = 0xBFF;
            return;
        }
        goto fail_status;
    default:
fail_status:
        status = 0x5FF;
        goto store_status;
    }
store_status:
    arg->status = status;
    return;
}

typedef struct {
    s16 id;
    u8 unk2;
    u8 pad3;
    s16 unk4;
    u8 pad6[6];
    s32 unkC;
} Ctx_00114080;

typedef struct {
    u8 pad0[0x3C];
    u16 unk3C;
    u8 pad3E[0x22];
} Work_00114080;

s32 func_00115340(s32 arg0, u8 arg1, void *arg2, s32 arg3);
s32 func_00276F10(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8,
                  s32 arg9);

s32 func_00114080(s32 arg0, s32 arg1, void *arg2) {
    extern s32 func_00278890(s32, s32);
    Work_00114080 work;
    s32 ret;
    s32 res;
    s32 pos;
    s32 kind;
    Ctx_00114080 *ctx = arg2;

    ctx->id = arg0;
    if (func_001DE6D0(arg1) == 0) {
        return -1;
    }
    if (func_00278890(arg1, 0) == 5 && func_00278890(arg1, 1) == 5) {
        return -1;
    }
    kind = func_00114310(arg1, &work);
    if (kind < 0) {
        return -1;
    }
    ctx->unk2 = 10;
    ctx->unkC = 0;
    pos = func_001E1090(arg0 >> 8, arg0 & 0xFF);
    if (kind == 0) {
        if (func_00114D40(arg1, (u8 *)ctx, &work) >= 0) {
            ret = func_00276F10(&work, pos & 0xFF, pos >> 8, arg1 == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, func_00117C30(arg1));
            if (ret < 0) {
                if (func_001E0150(arg1) < 4) {
                    res = func_00115340(arg1, kind, &work, ret);
                    if (res < 0) {
                        return -1;
                    }
                    ctx->unk4 = res;
                    return 1;
                }
            } else {
                res = func_00115340(arg1, kind, &work, ret);
                if (res < 0) {
                    return -1;
                }
                ctx->unk4 = res;
                return 1;
            }
        }
    } else {
        ret = func_00276F10(&work, pos & 0xFF, pos >> 8, arg1 == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, func_00117C30(arg1));
    }
    if (kind == 2) {
        func_00115160(arg1, ctx, &work);
        res = func_00115340(arg1, kind, &work, ret);
        if (res < 0) {
            return -1;
        }
        ctx->unk4 = res;
        return 1;
    }
    if (func_00114B40(arg1, (u8 *)ctx, &work, work.unk3C) < 0) {
        return -1;
    }
    res = func_00115340(arg1, kind, &work, ret);
    if (res < 0) {
        return -1;
    }
    ctx->unk4 = res;
    return 1;
}

s32 func_00114310(s32 arg0, void *arg1) {
    extern s32 func_00278890();
    extern s32 func_001E1580();
    s32 cards[8];
    u8 buffer[32];
    u8 primary;
    u8 secondary;
    s32 i;
    s32 result;

    primary = (u8)func_00278890(arg0, 0);
    secondary = (u8)func_00278890(arg0, 1);
    if (arg1 == NULL) {
        return -1;
    }
    func_0026FD30(arg0, cards);
    if (primary == 5) {
        if (func_00114B40(arg0, buffer, arg1, 999) >= 0) {
            return 1;
        }
        return -1;
    }
    if (secondary == 5) {
        s32 index = 0;
        s32 *p;
        if (index < func_0026FE20(arg0)) {
            p = cards;
            do {
                if ((func_0026FCE0(*p) >> 5) == 0 && func_0026FB10(arg0, *p) == 1) {
                    func_001DCD70(arg1, cards[index]);
                    return 0;
                }
                p++;
                index++;
            } while (index < func_0026FE20(arg0));
        }
        return -1;
    }
    if (func_001146C0(arg0, buffer, arg1, 0x345) >= 0) {
        if (func_00117BD0(arg0, 0x345) == 1) {
            return 2;
        }
    }
    if (func_00117600(arg0) == 1) {
        if (func_0024CA40(0, 0, arg0, 1, 0x53001C, 14) == 0) {
            if (func_001146C0(arg0, buffer, arg1, 0x53) >= 0) {
                return 2;
            }
            if (func_001147B0(arg0, buffer, arg1) >= 0) {
                return 2;
            }
        }
    }
    if (func_001173E0(arg0) == 1) {
        if (func_001146C0(arg0, buffer, arg1, 0x179) >= 0) {
            return 2;
        }
    }
    if (func_00117550(arg0) == 1) {
        if (func_001146C0(arg0, buffer, arg1, 0x186) >= 0) {
            return 2;
        }
    }
    if (func_00117680(arg0) >= 0) {
        if (func_001146C0(arg0, buffer, arg1, 0x2AD) >= 0) {
            return 2;
        }
    }
    for (i = 0; i < 11; i++) {
        if (func_001E1580(arg0, i) != 0 && func_001146C0(arg0, buffer, arg1, 0x31C) >= 0) {
            return 2;
        }
    }
    {
        s32 *p;
        s32 index = 0;
        if (index < func_0026FE20(arg0)) {
            p = cards;
            do {
                if ((func_0026FCE0(*p) >> 5) == 0 && func_0026FB10(arg0, *p) == 1) {
                    func_001DCD70(arg1, cards[index]);
                    return 0;
                }
                p++;
                index++;
            } while (index < func_0026FE20(arg0));
        }
    }
    result = func_00114B40(arg0, buffer, arg1, 999);
    if (result >= 0) {
        return result;
    }
    return -1;
}

s32 func_001146C0(s32 arg0, void *arg1, void *arg2, s32 arg3) {
    s32 entries[8];
    s32 i;

    func_0026FD30(arg0, entries);
    for (i = 0; i < func_0026FE20(arg0); i++) {
        if ((arg3 & 0xFFFF) == entries[i] && func_0026FB10(arg0, entries[i]) == 1) {
            *((s8 *)arg1 + 6) = i;
            func_001DCD70(arg2, entries[i]);
            return func_0026FCE0(entries[i]) >> 5;
        }
    }
    return -1;
}

static inline s32 search_001147B0(s32 arg0, void *arg1, void *arg2, s32 card) {
    s32 cards[8];
    s32 i;

    func_0026FD30(arg0, cards);
    for (i = 0; i < func_0026FE20(arg0); i++) {
        if (cards[i] == card && func_0026FB10(arg0, cards[i]) == 1) {
            *((s8 *)arg1 + 6) = i;
            func_001DCD70(arg2, cards[i]);
            return func_0026FCE0(cards[i]) >> 5;
        }
    }
    return -1;
}

s32 func_001147B0(s32 arg0, void *arg1, void *arg2) {
    s32 result;

    result = search_001147B0(arg0, arg1, arg2, 0x337);
    if (result >= 0) {
        return result;
    }
    result = search_001147B0(arg0, arg1, arg2, 0x335);
    if (result >= 0) {
        return result;
    }
    result = search_001147B0(arg0, arg1, arg2, 0x338);
    if (result >= 0) {
        return result;
    }
    result = search_001147B0(arg0, arg1, arg2, 0x33C);
    if (result >= 0) {
        return result;
    }
    result = search_001147B0(arg0, arg1, arg2, 0x339);
    if (result >= 0) {
        return result;
    }
    return -1;
}

s32 func_00114B40(s32 arg0, u8 *arg1, void *arg2, s32 arg3) {
    s32 buf[8];
    s32 i;

    func_0026FD30(arg0, buf);
    if (arg2 == NULL) {
        return -1;
    }
    for (i = 0; i < 5; i++) {
        arg1[i + 6] = 0xFF;
    }
    for (i = 0; i < func_0026FE20(arg0); i++) {
        if (arg3 == buf[i] && arg3 != 999) {
            arg1[6] = i;
            func_001DCD70(arg2, buf[i]);
            return 1;
        }
    }
    for (i = 0; i < func_0026FE20(arg0); i++) {
        if ((func_0026FCE0(buf[i]) >> 5) != 0 && (func_0026FCE0(buf[i]) >> 5) != 2) {
            arg1[6] = i;
            func_001DCD70(arg2, buf[i]);
            return 1;
        }
    }
    for (i = 0; i < func_0026FE20(arg0); i++) {
        if ((func_0026FCE0(buf[i]) >> 5) != 0) {
            arg1[6] = i;
            func_001DCD70(arg2, buf[i]);
            return 1;
        }
    }
    return -1;
}

#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_009", func_00135790);

s32 func_00135970(u16 *arg0, s32 arg1, s32 arg2) {
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
    func_00135790(arg0 + idx * 8);
    if (((arg0[idx * 8 + 2] >> 8) & 0xFF) == 10) {
        if (func_001DE6D0(arg1) == 1 && func_00136210(pos, arg1, arg2) >= 0) {
            return pos | 0x10000;
        }
        if (func_0027B9B0(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (func_001E2100(arg1, 0, 0) == 0) {
        if (func_0027B9B0(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (func_001DE6D0(arg1) == 1 && func_00136210(pos, arg1, arg2) >= 0) {
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

INCLUDE_ASM("asm/nonmatchings/main_009", func_00135D50);

void func_00135FB0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28) {
    func_0027DE20(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
                  arg_sp0, arg_sp8, arg_sp10, arg_sp18, arg_sp20,
                  1, 0x898, arg_sp28);
}

void func_00136010(void *arg0) {
    s32 temp_v0;

    temp_v0 = func_00136060(arg0);
    if (temp_v0 >= 0) {
        *(s16 *)((u8 *)arg0 + 4) = 0x3FF;
        *(u32 *)((u8 *)arg0 + 8) = (temp_v0 << 16) | *(u16 *)((u8 *)arg0 + 8);
        return;
    }
    *(s16 *)((u8 *)arg0 + 4) = 0x5FF;
}

s32 func_00136060(void *arg0) {
    if (func_001E36E0(2, 2) == 0 && func_001E22B0(2, 2) != 8) {
        return 0x202;
    }
    if (func_001E36E0(5, 2) == 0 && func_001E22B0(5, 2) != 8) {
        return 0x205;
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/main_009", func_001360E0);

INCLUDE_ASM("asm/nonmatchings/main_009", func_00136210);

INCLUDE_ASM("asm/nonmatchings/main_009", func_00136490);

s32 func_00136890(s32 arg0, void *arg1, void *arg2, s32 arg3) {
    s32 entries[8];
    s32 i;
    s32 *entry;
    s32 wanted;

    func_0026FD30(arg0, entries);
    i = 0;
    if (i < func_0026FE20(arg0)) {
        wanted = arg3 & 0xFFFF;
        entry = entries;
        do {
            if (wanted == *entry && func_0026FB10(arg0, *entry) == 1) {
                *((s8 *)arg1 + 6) = i;
                func_001DCD70(arg2, entries[i]);
                return func_0026FCE0(entries[i]) >> 5;
            }
            entry++;
            i++;
        } while (i < func_0026FE20(arg0));
    }
    return -1;
}

s32 func_00136980(s32 arg0, u8 *arg1, void *arg2, s32 arg3) {
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

INCLUDE_ASM("asm/nonmatchings/main_009", func_00136B80);

typedef struct {
    u16 id;
    u8 values[5];
} Info_00136D60;

void func_00136D60(s32 arg0, void *arg1, s32 *arg2) {
    Info_00136D60 *info = arg1;
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
                if (card != 0x3E7 && level >= func_0026FA80(card, arg0)) {
                    cost = func_0026FBB0(card);
                    if ((cost & 0xFFFF) + (cost >> 16) * 2 < 0x3E9 && func_0026FC10(card) == 2 &&
                        (u16)func_002789F0(info->id, (u16)card) == 0x3E7) {
                        func_00278D20(info->values, buf[i]);
                    }
                }
            }
        }
    }
}

typedef struct {
    u8 pad0[6];
    u8 slot[5];
} Obj1_00136F30;

typedef struct {
    u8 pad0[0x3C];
    u16 id;
} Obj2_00136F30;

s32 func_00136F30(s32 arg0, void *arg1, void *arg2) {
    Obj1_00136F30 *o1 = arg1;
    Obj2_00136F30 *o2 = arg2;
    s32 list[8];
    s32 i;
    u8 k;

    for (i = 0; i < 5; i++) {
        o1->slot[i] = 0xFF;
    }
    func_0026FD30(arg0, list);
    if (o2 == NULL) {
        return -1;
    }
    for (i = 0; i < func_0026FE20(arg0); i++) {
        if (i != o1->slot[0] && i != o1->slot[1]) {
            if (o2->id == list[i] && func_0026FB10(arg0, list[i]) == 1) {
                o1->slot[0] = i;
            }
        }
    }
    k = 1;
    if ((func_0026FCE0(list[o1->slot[0]]) >> 5) == 0) {
        for (i = 0; i < func_0026FE20(arg0); i++) {
            if (i != o1->slot[0] && i != o1->slot[1]) {
                if (func_00248F60(list[o1->slot[0]], list[i]) >= 0 && (func_0026FCE0(list[i]) >> 5) == 2) {
                    if (list[i] != 0x31B && list[i] != 0x31C) {
                        o1->slot[k] = i;
                        k++;
                    }
                }
            }
        }
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_009", func_00137120);

INCLUDE_ASM("asm/nonmatchings/main_009", func_001374D0);

INCLUDE_ASM("asm/nonmatchings/main_009", func_001379F0);

INCLUDE_ASM("asm/nonmatchings/main_009", func_00137FB0);

INCLUDE_ASM("asm/nonmatchings/main_009", func_00138780);

INCLUDE_ASM("asm/nonmatchings/main_009", func_00138950);

s32 func_00138B60(s32 arg0) {
    extern s32 func_001E1580(s32, s32);
    extern s32 func_001E1640(s32, s32);
    u16 cells[0x16];
    s32 target;
    s32 row;
    s32 col;
    u16 *p;
    s32 y;
    s32 x;
    s32 best;
    s32 i;
    s32 bestScore;
    u32 handle;
    s32 pos;
    s32 score;
    s32 j;

    pos = func_001E1090((arg0 == 0) ? 1 : 0, 0);
    if (func_00266DF0(0x39) > 0) {
        return -1;
    }
    handle = func_00272210(func_0024CA40(0, 0, arg0, 2, 0x21, 0xE), arg0);
    p = cells;
    for (j = 0; j < 0x16; j++) {
        cells[j] = 0xFFFF;
    }
    func_0027C070((arg0 == 0) ? 1 : 0, cells, 0x34, 1);
    target = -1;
    best = target;
    bestScore = 1;
    i = 0;
    if (i < func_0027C670(cells)) {
        row = pos >> 8;
        col = pos & 0xFF;
        do {
        pos = func_001E1090(*p >> 8, *p & 0xFF);
        y = pos >> 8;
        x = pos & 0xFF;
        if ((((x < col) ? col : x) - ((col < x) ? col : x)) +
                (((y < row) ? row : y) - ((row < y) ? row : y)) == 1 &&
            func_001E2100(*p >> 8, *p & 0xFF, 1) == 0 &&
            func_001E1580(*p >> 8, *p & 0xFF) == 0 &&
            func_001E1640(*p >> 8, *p & 0xFF) == 0) {
            if ((score = func_002509E0(*p >> 8, *p & 0xFF, x, y)) >= bestScore) {
                best = *p;
                if (best == func_0024EC50(handle, 0)) {
                    target = best;
                }
                bestScore = score;
            }
        }
        p++;
        } while (++i < func_0027C670(cells));
    }
    if (best < 0) {
        return -1;
    }
    return ((best & 0xFFFF) << 16) | (target & 0xFFFF);
}

s32 func_00138DB0(s32 arg0) {
    s32 temp_s0;
    s32 temp_s1;
    s32 temp_v0;

    if (func_0024E910(func_0024CA40(0, 0, arg0, 2, 0, 14)) >= 2) {
        return 1;
    }
    temp_v0 = func_0024EC50(func_0024CA40(0, 0, arg0, 3, 33, 14), 0);
    temp_s1 = temp_v0 >> 8;
    temp_s0 = temp_v0 & 0xFF;
    if (arg0 != func_00250360(temp_s1, temp_s0)) {
        if (((func_001E0700(temp_s1, temp_s0) >> 5) == 0) && !(func_001E0700(temp_s1, temp_s0) & 0x1F)) {
            return 1;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_009", func_00138EA0);

s32 func_00138F90(s32 arg0, s32 arg1) {
    s32 index;
    s32 mask;
    s32 low;
    s32 high;
    s32 packed;
    s32 value;
    s32 data[4];

    func_00254C90(data, *(s32 *)((u8 *)func_0026FC90(arg1, 0) + 4));
    if ((mask = func_00254890(data, arg0)) < 0) {
        return 0;
    }
    index = 0;
    if (index < func_0024E910(mask)) {
        do {
            packed = func_0024EC50(mask, index);
            high = packed >> 8;
            low = packed & 0xFF;
            value = func_001E1090(high, low);
            if (func_002509E0(high, low, value & 0xFF, value >> 8) >= 0xA28) {
                return 0;
            }
            index++;
        } while (index < func_0024E910(mask));
    }
    return 1;
}

static inline s32 max_00139080(s32 a, s32 b) {
    if (a < b) {
        return b;
    }
    return a;
}

s32 func_00139080(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 min_y;
    s32 min_x;

    min_y = arg3 < arg5 ? arg3 : arg5;
    arg5 = max_00139080(arg5, arg3);
    min_x = arg2 < arg4 ? arg2 : arg4;
    arg4 = max_00139080(arg4, arg2);
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

INCLUDE_ASM("asm/nonmatchings/main_009", func_00139180);

INCLUDE_ASM("asm/nonmatchings/main_009", func_001396C0);

INCLUDE_ASM("asm/nonmatchings/main_009", func_00139890);

INCLUDE_ASM("asm/nonmatchings/main_009", func_00139D90);

INCLUDE_ASM("asm/nonmatchings/main_009", func_0013A010);

INCLUDE_ASM("asm/nonmatchings/main_009", func_0013A400);

void func_0013A6B0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28) {
    func_0027DE20(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
                  arg_sp0, arg_sp8, arg_sp10, arg_sp18, arg_sp20,
                  0, 2500, arg_sp28);
}

typedef struct Packet_0013A710 {
    u16 location;
    u16 unk2;
    s16 mode;
    u16 unk6;
    union {
        u32 word;
        u16 lower;
    } value;
} Packet_0013A710;

void func_0013A710(void *arg0, s32 arg1) {
    Packet_0013A710 *packet = arg0;
    s32 item;
    s32 encoded;
    s32 result;
    u16 location;

    location = packet->location;
    item = func_00250360(location >> 8, location & 0xFF);
    location = packet->location;
    encoded = func_001E1090(location >> 8, location & 0xFF);
    if ((arg1 & 0xFF) == 1) {
        item = encoded & 0xFF;
        encoded = (encoded >> 8) + 1;
        result = func_001E3790(item, encoded);
        if (result >= 0) {
            packet->mode = 0x2FF;
            packet->value.word = (result << 16) | packet->value.lower;
        } else {
            packet->mode = 0x6FF;
            packet->value.word = packet->value.lower | (((encoded << 8) | item) << 16);
        }
        return;
    } else {
        arg1 = encoded >> 8;
        if (arg1 != func_0013A9A0(item)) {
            result = func_0013A870(item);
            if (result >= 0) {
                packet->mode = 0x6FF;
                packet->value.word = (result << 16) | packet->value.lower;
            } else {
                packet->mode = 0x6FF;
                packet->value.word = packet->value.lower | ((((arg1 + 1) << 8) | (encoded & 0xFF)) << 16);
            }
        } else {
            packet->mode = 0x6FF;
            packet->value.word = (encoded << 16) | packet->value.lower;
        }
    }
}

s32 func_0013A870(s32 arg0) {
    s32 var_s0;
    s32 temp_s1;

    temp_s1 = func_0013A9A0(arg0) & 0xFF;
    var_s0 = 0;
    do {
        switch (var_s0) {
        case 0:
            if (func_001E36E0(3, temp_s1) == 0) {
                return (temp_s1 << 8) | 3;
            }
            break;
        case 1:
            if (func_001E36E0(4, temp_s1) == 0) {
                return (temp_s1 << 8) | 4;
            }
            break;
        case 2:
            if (func_001E36E0(2, temp_s1) == 0) {
                return (temp_s1 << 8) | 2;
            }
            break;
        case 3:
            if (func_001E36E0(5, temp_s1) == 0) {
                return (temp_s1 << 8) | 5;
            }
            break;
        case 4:
            if (func_001E36E0(1, temp_s1) == 0) {
                return (temp_s1 << 8) | 1;
            }
            break;
        }
        var_s0++;
    } while (var_s0 < 5);
    return -1;
}

s32 func_0013A9A0(s32 arg0) {
    s32 i;
    u8 maximum;
    s32 value;

    maximum = 0;
    for (i = 1; i <= 5; i++) {
        if (func_001DF540(arg0, i) != 0) {
            value = (func_001E1090(arg0, i) >> 8) & 0xFF;
            if (maximum < value) {
                maximum = value;
            }
        }
    }
    if (maximum < 2) {
        maximum = 2;
    }
    return maximum;
}

typedef struct State_0013AA40 {
    u16 position;
    u16 unk2;
    s16 mode;
    u16 unk6;
    union {
        u16 halves[2];
        u32 word;
    } info;
} State_0013AA40;

static inline s32 decode_0013AA40(s32 position) {
    return func_001E1090(position >> 8, position & 0xFF);
}

void func_0013AA40(void *arg0) {
    State_0013AA40 *state = arg0;
    s32 temp_s0;
    s32 temp_s2;
    s32 temp_a0;
    s32 temp_v0_4;
    u16 temp_v0;
    u16 temp_v0_2;
    u16 temp_v0_3;

    temp_v0 = state->position;
    temp_s2 = func_00250360((s32) temp_v0 >> 8, temp_v0 & 0xFF);
    temp_v0_2 = state->position;
    temp_s0 = decode_0013AA40(temp_v0_2);
    temp_v0_3 = state->position;
    temp_a0 = func_001E0700((s32) temp_v0_3 >> 8, temp_v0_3 & 0xFF) >> 5;
    switch (temp_a0) {
    case 1:
        temp_v0_4 = func_0013D2C0(temp_s2);
        if (temp_v0_4 >= 0) {
            state->mode = 0x6FF;
            state->info.word = state->info.halves[0] | ((((temp_s0 >> 8) << 8) | (func_001E1090(temp_v0_4 >> 8, temp_v0_4 & 0xFF) & 0xFF)) << 0x10);
            return;
        }
        state->mode = 0x5FF;
        break;
    case 3:
        state->mode = 0x3FF;
        state->info.word = state->info.halves[0] | (((temp_s0 & 0xFF) | ((func_001E1090(temp_s2, 0) >> 8) << 8)) << 0x10);
        return;
    }
    state->mode = 0x5FF;
}

INCLUDE_ASM("asm/nonmatchings/main_009", func_0013AB70);

INCLUDE_ASM("asm/nonmatchings/main_009", func_0013AE00);

s32 func_0013B130(s32 arg0, void *arg1, void *arg2, s32 arg3) {
    s32 entries[8];
    s32 i;
    s32 *entry;

    func_0026FD30(arg0, entries);
    i = 0;
    if (0 < func_0026FE20(arg0)) {
        entry = entries;
        do {
            if ((arg3 & 0xFFFF) == *entry && func_0026FB10(arg0, *entry) == 1) {
                *((u8 *)arg1 + 6) = i;
                func_001DCD70(arg2, entries[i]);
                return func_0026FCE0(entries[i]) >> 5;
            }
            entry++;
            i++;
        } while (i < func_0026FE20(arg0));
    }
    return -1;
}

s32 func_0013B220(s32 arg0, u8 *arg1, void *arg2, s32 arg3) {
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

INCLUDE_ASM("asm/nonmatchings/main_009", func_0013B420);

typedef struct {
    u16 id;
    u8 values[5];
} Info_0013B600;

void func_0013B600(s32 arg0, void *arg1, s32 *arg2) {
    Info_0013B600 *info = arg1;
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
                if (card != 0x3E7 && func_0013B7E0(card) == 0 && level >= func_0026FA80(card, arg0)) {
                    cost = func_0026FBB0(card);
                    if ((cost & 0xFFFF) + (cost >> 16) * 2 < 0xFA1 && func_0026FC10(card) == 2 &&
                        (u16)func_002789F0(info->id, (u16)card) == 0x3E7) {
                        func_00278D20(info->values, buf[i]);
                    }
                }
            }
        }
    }
}

s32 func_0013B7E0(s32 arg0) {
    if ((func_0026FCE0(arg0) >> 5) != 0) {
        return 1;
    }
    if (func_0026FC10(arg0) == 1) {
        return 1;
    }
    return 0;
}

typedef struct {
    u8 pad0[6];
    u8 slot[5];
} Obj1_0013B840;

typedef struct {
    u8 pad0[0x3C];
    u16 id;
} Obj2_0013B840;

s32 func_0013B840(s32 arg0, void *arg1, void *arg2) {
    Obj1_0013B840 *o1 = arg1;
    Obj2_0013B840 *o2 = arg2;
    s32 list[8];
    s32 i;
    u8 k;

    for (i = 0; i < 5; i++) {
        o1->slot[i] = 0xFF;
    }
    func_0026FD30(arg0, list);
    if (o2 == NULL) {
        return -1;
    }
    for (i = 0; i < func_0026FE20(arg0); i++) {
        if (i != o1->slot[0] && i != o1->slot[1]) {
            if (o2->id == list[i] && func_0026FB10(arg0, list[i]) == 1) {
                o1->slot[0] = i;
            }
        }
    }
    k = 1;
    if ((func_0026FCE0(list[o1->slot[0]]) >> 5) == 0) {
        for (i = 0; i < func_0026FE20(arg0); i++) {
            if (i != o1->slot[0] && i != o1->slot[1]) {
                if (func_00248F60(list[o1->slot[0]], list[i]) >= 0 && (func_0026FCE0(list[i]) >> 5) == 2) {
                    if (list[i] != 0x31B && list[i] != 0x31C) {
                        o1->slot[k] = i;
                        k++;
                    }
                }
            }
        }
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_009", func_0013BA30);

INCLUDE_ASM("asm/nonmatchings/main_009", func_0013BE60);

INCLUDE_ASM("asm/nonmatchings/main_009", func_0013C430);

INCLUDE_ASM("asm/nonmatchings/main_009", func_0013CA10);

s32 func_0013D280(void) {
    if (func_0013A870(func_001DE540()) < 0) {
        return 1;
    }
    return 0;
}

s32 func_0013D2C0(s32 arg0) {
    u16 buf[0x16];
    s32 i;
    s32 a;
    s32 b;
    s32 r;

    for (i = 0; i < 0x16; i++) {
        buf[i] = 0xFFFF;
    }
    func_0027C2C0(arg0 == 0 ? 1 : 0, buf, 0x1D, 0, 0);
    a = func_0027B650(buf);
    for (i = 0; i < 0x16; i++) {
        buf[i] = 0xFFFF;
    }
    func_0027C070(arg0, buf, 0x1D, 1);
    b = func_0027B650(buf);
    if (a >= 0) {
        if (b >= 0) {
            r = func_001E1090(a >> 8, a & 0xFF);
            if (func_002781F0(a, b, r & 0xFF, r >> 8) > 0) {
                return a;
            }
        }
    }
    return -1;
}

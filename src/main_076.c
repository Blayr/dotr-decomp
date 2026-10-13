#include "common.h"

typedef struct Input_00265890 {
    s32 unk0;
    u32 position;
    u32 target;
    s32 mode;
} Input_00265890;

typedef struct State_00265890 {
    u16 value;
    u16 count;
    u16 phase;
    u8 effects[26];
    s32 entries[44];
    s32 frame;
    u8 effectCount;
    u8 padD5[0x2D];
    u16 timer;
} State_00265890;

typedef struct Request_00265890 {
    s32 command;
    s32 unk4;
    s32 argument;
    s32 flag;
} Request_00265890;



static inline s32 absolute_00265890(s32 value) {
    return value >= 0 ? value : -value;
}

#pragma opt_strength_reduction off

s32 func_00265890(void *arg0, void *arg1, s32 arg2) {
    extern void func_001E1E70(u32, s32, s32, s32);
    extern void func_0024F370(s32, s32);
    extern void func_002516D0(u32, s32, s32);
    extern void func_00260A70(void *, s32);
    Input_00265890 *input = arg0;
    State_00265890 *state = arg1;
    s32 packet[4];
    Request_00265890 *request = (Request_00265890 *)packet;
    s32 found;
    extern s32 func_001E1E10();

    packet[0] = 999;
    packet[1] = 0;
    packet[2] = 0;
    packet[3] = 0;
    found = 0;
    func_001DE7E0(0);
    if (arg2 >= 0) {
        func_00255960(state);
        state->value = 0x80;
        func_002516D0(input->position >> 8, input->position & 0xFF, 1);
        func_00260AF0(0, input->position, 100, 180);
        func_00255AC0(state, 0x25A);
        func_00255AC0(state, 0x25B);
        func_00255AC0(state, 0x222);
        return 1;
    }

    switch (state->phase) {
    case 0:
        if (state->value > 0x30) {
            state->value -= 15;
        } else {
            state->value = 0x30;
            if (func_001E1E10(input->position >> 8, input->position & 0xFF) == 0xFF &&
                func_00255B50(state) == 1) {
                if (input->mode == 1) {
                    func_001E42C0(0, -120, 80, 0x104);
                } else {
                    func_001E42C0(0, -120, 80, 0x103);
                }
                request->command = 0x25A;
                request->unk4 = 0;
                request->argument = input->position;
                request->flag = 0;
                state->effects[0] = func_00255A30(request, state);
                state->phase++;
            }
        }
        if (state->value < 0x30) {
            state->value = 0x30;
        }
        func_001F6CF0((u8)state->value);
        break;
    case 1:
        {
            __int128 owner;
            s32 inner;
            s32 entry;
            s32 y;
            s32 x;
            s32 outer;
            s32 centerHigh;
            s32 distance;
            s32 center;
            extern __int128 func_00250360();

            if (func_001F51D0(state->effects[0]) != 0) {
                return 1;
            }
            func_001E1E70(input->position >> 8, input->position & 0xFF, 0, 1);
            func_00260AF0(0x10, input->position, 500, 500);
            state->value = 0;
            center = func_001E1090(input->position >> 8, input->position & 0xFF);
            request->command = 0x222;
            request->unk4 = 0;
            request->argument = center;
            request->flag = 1;
            state->effects[0] = func_00255A30(request, state);
            state->entries[0] = input->position;
            outer = -1;
            x = (center & 0xFF) - 1;
            centerHigh = center >> 8;
            state->value++;
            state->effectCount++;
            while (1) {
                inner = -1;
                y = centerHigh - 1;
                while (1) {
                    if (x >= 0 && x < 7 && y >= 0 && y < 7) {
                        distance = outer + inner;
                        distance = absolute_00265890(distance);
                        if (distance < 3 && (outer != 0 || inner != 0)) {
                            request->command = 0x222;
                            request->unk4 = 0;
                            request->argument = (y << 8) | x;
                            request->flag = 0;
                            state->effects[state->effectCount] = func_00255A30(request, state);
                            if (func_001E36E0(x, y) != 0) {
                                entry = func_001E3790(x, y);
                                if (input->mode == 1) {
                                    state->entries[state->effectCount] = entry;
                                    state->value++;
                                } else {
                                    s32 low;
                                    s32 high;

                                    high = entry >> 8;
                                    low = entry & 0xFF;
                                    owner = func_00250360(high, low);
                                    if (owner != func_00250360(input->position >> 8, input->position & 0xFF)) {
                                        if (func_00271E40(high, low, 11) == 0 && func_00267700(high, low) != 1) {
                                            state->entries[state->effectCount] = entry;
                                            state->value++;
                                            if (input->mode == 0 && entry == input->target) {
                                                found++;
                                            }
                                        }
                                    } else {
                                        state->entries[state->effectCount] = entry;
                                        state->value++;
                                        if (input->mode == 0 && entry == input->target) {
                                            found++;
                                        }
                                    }
                                }
                            } else {
                                state->entries[state->effectCount] = -1;
                            }
                            state->effectCount++;
                        }
                    }
                    inner++;
                    y++;
                    if (inner > 1) {
                        break;
                    }
                }
                outer++;
                x++;
                if (outer > 1) {
                    break;
                }
            }
            if (found == 0 && input->mode == 0) {
                request->command = 0x25B;
                request->unk4 = 0;
                request->argument = input->target;
                request->flag = 1;
                state->effects[state->effectCount] = func_00255A30(request, state);
                state->entries[state->effectCount] = -1;
                state->effectCount++;
            }
            state->phase++;
            return 1;
        }
    case 2:
        {
            s32 *entry;
            s32 i;
            u8 *effect;

            state->frame++;
            i = 0;
            entry = (s32 *)state;
            for (; i < state->effectCount; entry++, i++) {
                switch (state->frame) {
                case 1:
                    func_00217710(1, 0x31);
                    break;
                case 5:
                    func_00217710(1, 0x31);
                    func_00217710(1, 0x31);
                    func_00217710(1, 0x31);
                    func_00217710(1, 0x31);
                    break;
                }
                effect = &state->effects[i];
                if (func_001F51D0(*effect) != 0 && func_001F52D0(*effect) == 2 && entry[8] >= 0) {
                    if ((entry[8] & 0xFF) > 0) {
                        func_002500C0(entry[8] >> 8, entry[8] & 0xFF, -1, 1, 3);
                        state->entries[state->effectCount + state->count] = entry[8];
                        entry[8] = -1;
                    }
                    state->count++;
                }
            }
            if (state->value <= state->count) {
                state->phase++;
            }
            break;
        }
    case 3:
        if (func_0025FD90() != 0) {
            s32 i;
            s32 *entry;

            i = state->effectCount;
            entry = (s32 *)state + i;
            for (; i < state->effectCount + state->count; entry++, i++) {
                if (entry[8] >= 0 && (entry[8] & 0xFF) > 0) {
                    func_0024F370(entry[8] >> 8, entry[8] & 0xFF);
                }
            }
            if (input->target != 0) {
                func_0024F370(input->target >> 8, input->target & 0xFF);
            }
            state->value = 0x30;
            state->phase++;
        }
        break;
    case 4:
        state->value += 15;
        if (state->value > 0x80) {
            state->value = 0x80;
        }
        func_001F6CF0((u8)state->value);
        if (state->value == 0x80) {
            state->phase++;
            func_001E4530();
            func_00260A70(state, 0x10);
            state->timer = 0;
        }
        break;
    default:
        if (state->timer++ > 16 && func_0025F390(state) == 1 && func_0025FD90() == 1) {
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

#pragma opt_strength_reduction reset

typedef struct Stats_002660E0 {
    u8 pad[8];
    u16 attack;
    u16 defense;
} Stats_002660E0;

typedef struct Flags_002660E0 {
    s8 unused : 3;
    s8 side : 1;
    s8 remaining : 4;
} Flags_002660E0;

typedef struct Card_002660E0 {
    Stats_002660E0 *stats;
    u8 pad04[0x34];
    s16 attack;
    s16 defense;
    u16 id;
    u8 pad3E[0x19];
    Flags_002660E0 flags;
} Card_002660E0;

typedef struct Effect_002660E0 {
    u32 flags;
    u16 amount;
} Effect_002660E0;

static inline s32 attack_002660E0(Card_002660E0 *card) {
    s32 value = card->attack + (card->stats->attack & 0x1FFF);
    if (value > 9999) {
        return 9999;
    }
    return value;
}

static inline s32 defense_002660E0(Card_002660E0 *card) {
    s32 value = card->defense + (card->stats->defense & 0x1FFF);
    if (value > 9999) {
        return 9999;
    }
    return value;
}

s32 func_002660E0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 i;
    s32 side;
    s32 total;
    Effect_002660E0 *effect;
    u32 flags;
    u32 otherFlags;
    Effect_002660E0 *otherEffect;
    s32 j;
    s32 result;

    if (arg0 == 0) {
        return 0;
    }
    total = 0;
    side = func_00250370((void *)arg0);
    i = 1;
    if (((Card_002660E0 *)arg0)->id == 0x2A3) {
        if (arg3 == 0) {
            total -= defense_002660E0((Card_002660E0 *)arg0);
        } else {
            total -= attack_002660E0((Card_002660E0 *)arg0);
        }
        if (((Card_002660E0 *)arg0)->flags.side) {
            if (arg3 == 0) {
                total += func_001E0370(side, 0, 1);
            } else {
                total += func_001E0290(side, 0, 1);
            }
        } else {
            if (arg3 == 0) {
                total += func_001E0370(side == 0 ? 1 : 0, 0, 1);
            } else {
                total += func_001E0290(side == 0 ? 1 : 0, 0, 1);
            }
        }
        i = 1;
    }
    while (1) {
        if (func_001DF540(side, i) != 0 &&
            func_001E2100(side, i, 4) != 0 &&
            func_001E2100(side, i, 3) != 0 &&
            func_001E2100(side, i, 5) != 0) {
            if ((effect = func_00250740(side, i, 2)) != NULL) {
                flags = effect->flags;
                if (func_0024ECD0((void *)arg0, func_00250360(side, i),
                                 (flags >> 6) & 3, flags & 0x3F) != 0) {
                    switch (effect->flags >> 8) {
                    case 19:
                        total -= effect->amount;
                        break;
                    case 18:
                        total += effect->amount;
                        break;
                    case 34:
                        if (arg3 == 0) {
                            total += effect->amount;
                        }
                        break;
                    }
                }
            }
        }
        i++;
        if (i > 5) {
            break;
        }
    }
    j = 1;
    while (1) {
        if (func_001DF540(side == 0 ? 1 : 0, j) != 0 &&
            func_001E2100(side == 0 ? 1 : 0, j, 4) != 0 &&
            func_001E2100(side == 0 ? 1 : 0, j, 3) != 0 &&
            func_001E2100(side == 0 ? 1 : 0, j, 5) != 0) {
            if ((otherEffect = func_00250740(side == 0 ? 1 : 0, j, 2)) != NULL) {
                otherFlags = otherEffect->flags;
                if (func_0024ECD0((void *)arg0,
                                 func_00250360(side == 0 ? 1 : 0, j),
                                 (otherFlags >> 6) & 3, otherFlags & 0x3F) != 0) {
                    switch (otherEffect->flags >> 8) {
                    case 19:
                        total -= otherEffect->amount;
                        break;
                    case 18:
                        total += otherEffect->amount;
                        break;
                    case 34:
                        if (arg3 == 0) {
                            total += otherEffect->amount;
                        }
                        break;
                    }
                }
            }
        }
        j++;
        if (j > 5) {
            break;
        }
    }
    result = func_0024DEB0(func_001E22B0(arg1, arg2), (void *)arg0);
    switch (result) {
    case 1:
        total += 500;
        break;
    case 2:
        total -= 500;
        break;
    }
    total += func_00271AF0((void *)arg0, arg1, arg2);
    return total;
}

s32 func_00266500(s32 arg0, s32 arg1, void *output) {
    extern s32 func_001E1700();
    extern s32 func_001DEE50();
    s32 count;
    void *data;
    s32 target;
    s32 value;
    s32 index0;
    s32 length0;
    s32 length1;
    s32 index1;
    u32 packed;
    u32 word;
    s32 *out = output;

    if ((data = func_00250740(arg0, arg1, 2)) == NULL) {
        return 0;
    }
    word = *(u32 *)data;
    switch (word >> 8) {
    case 0xD:
        out[0] = 8;
        out[1] = 0;
        out[2] = func_0024DE70(arg0, arg1);
        packed = *(u32 *)((u8 *)data + 4);
        out[3] = ((packed >> 16) << 16) | (packed & 0xFFFF);
        return 1;
    case 0x4D:
        value = func_0024CA40(0, 0, func_0024DE70(arg0, arg1),
                             (word >> 6) & 3, word & 0x3F, 0xE);
        if (value == 0) {
            return 0;
        }
        out[0] = 0x39;
        out[1] = 0;
        out[2] = value;
        out[3] = *(u16 *)((u8 *)data + 4);
        return 1;
    case 0x4E:
        value = func_0024CA40(0, 0, func_0024DE70(arg0, arg1),
                             (word >> 6) & 3, word & 0x3F, 0xE);
        if (value == 0) {
            return 0;
        }
        out[0] = 0x1D;
        out[1] = 1;
        out[2] = value;
        out[3] = *(u16 *)((u8 *)data + 4);
        return 1;
    case 0xC:
        if (func_001E1700(arg0, arg1) == 1) {
            func_001E16A0(arg0, arg1, 0);
            value = func_0024C780(0, arg0, arg1);
            out[0] = 0x3C;
            out[1] = 0;
            out[2] = value;
            out[3] = *(u16 *)((u8 *)data + 4);
            return 1;
        }
        return 0;
    case 0x46:
        if (func_001E1700(arg0, arg1) == 1) {
            func_001E16A0(arg0, arg1, 0);
            out[0] = 0x2E;
            out[1] = (arg0 << 8) | arg1;
            out[2] = 0;
            out[3] = 1;
            return 1;
        }
        return 0;
    case 0x53:
        target = func_0024C780(0, arg0, arg1);
        count = 0;
        length0 = func_001DEE50(0);
        for (index0 = 0; index0 < length0; index0++) {
            if ((func_0026FCE0(func_001DEE00(0, index0)) >> 5) == 0) {
                func_001DF000(0, index0);
                count++;
            }
        }
        func_001DEF20(0);
        length1 = func_001DEE50(1);
        for (index1 = 0; index1 < length1; index1++) {
            if ((func_0026FCE0(func_001DEE00(1, index1)) >> 5) == 0) {
                func_001DF000(1, index1);
                count++;
            }
        }
        func_001DEF20(1);
        out[0] = 0x1D;
        out[1] = 1;
        out[2] = target;
        out[3] = count * *(u16 *)((u8 *)data + 4);
        return 1;
    case 0x54:
        value = func_0024C7D0(func_0024CA40(0, 0, func_0024DE70(arg0, arg1),
                                         (word >> 6) & 3, word & 0x3F, 0xE),
                             arg0, arg1);
        if (value == 0) {
            return 0;
        }
        out[0] = 0x48;
        out[1] = func_001E1090(arg0, arg1);
        out[2] = value;
        out[3] = func_0024DE70(arg0, arg1);
        return 1;
    }
    return 0;
}

s32 func_00266910(s32 arg0, s32 arg1, void *arg2) {
    extern s32 func_001E1640();
    s32 var_s3;
    u32 temp_s3;
    u32 var_s0;
    void *temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_s6;
    s32 temp_s7;

    temp_v0 = func_00250740(arg0, arg1, 2);
    temp_s3 = *(u32 *)temp_v0;
    var_s0 = 0;
    switch (temp_s3 >> 8) {
    case 0x17:
        temp_v0_2 = func_0024CA40(0, 0, func_0024DE70(arg0, arg1), (temp_s3 >> 6) & 3, temp_s3 & 0x3F, 0xE);
        if (temp_v0_2 == 0) {
            return 0;
        }
        temp_v0_3 = func_0024E910(temp_v0_2);
        var_s3 = 0;
        if (0 < temp_v0_3) {
            do {
                temp_v0_4 = func_0024EC50(temp_v0_2, var_s3);
                temp_s7 = temp_v0_4 >> 8;
                temp_s6 = temp_v0_4 & 0xFF;
                if (func_001E1640(temp_s7, temp_s6) == 0) {
                    var_s0 = func_0024C780(var_s0, temp_s7, temp_s6);
                }
                var_s3 += 1;
            } while (var_s3 < temp_v0_3);
        }
        if (func_0024E910((s32) var_s0) == 0) {
            return 0;
        }
        ((s32 *)arg2)[0] = 0;
        ((s32 *)arg2)[1] = 1;
        ((u32 *)arg2)[2] = var_s0;
        ((s32 *)arg2)[3] = *(u16 *)((u8 *)temp_v0 + 4);
        return 1;
    }
    return 0;
}

s32 func_00266A80(s32 arg0, s32 arg1) {
    s32 i;
    s32 key;
    u32 *p;
    u32 v;

    key = (arg0 << 8) | arg1;
    for (i = 0; i < 11; i++) {
        if (func_001DF540(0, i)) {
            if ((p = func_00250740(0, i, 2)) != NULL && func_001E2100(0, i, 4) && func_001E2100(0, i, 3) && func_001E2100(0, i, 5)) {
                v = *p;
                if ((v >> 8) == 0x17 && func_0024EA10(key, func_0024CA40(0, 0, func_0024DE70(0, i), (v >> 6) & 3, v & 0x3F, 0xE))) {
                    return 1;
                }
            }
        }
        if (func_001DF540(1, i)) {
            if ((p = func_00250740(1, i, 2)) != NULL && func_001E2100(1, i, 4) && func_001E2100(1, i, 3) && func_001E2100(1, i, 5)) {
                v = *p;
                if ((v >> 8) == 0x17 && func_0024EA10(key, func_0024CA40(0, 0, func_0024DE70(1, i), (v >> 6) & 3, v & 0x3F, 0xE))) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

s32 func_00266C70(s32 arg0, s32 arg1) {
    s32 count;
    s32 index;
    u32 *data;

    index = 1;
    count = 0;
    do {
        if (func_001E2100(0, index, 4) != 0 &&
            func_001E2100(0, index, 3) != 0 &&
            func_001E2100(0, index, 5) != 0) {
            data = func_00250740(0, index, 2);
            if (data != NULL && (*data >> 8) == arg0) {
                if (count++ == arg1) {
                    return index;
                }
            }
        }
        index++;
    } while (index < 11);

    index = 1;
    do {
        if (func_001E2100(1, index, 4) != 0 &&
            func_001E2100(1, index, 3) != 0 &&
            func_001E2100(1, index, 5) != 0) {
            data = func_00250740(1, index, 2);
            if (data != NULL && (*data >> 8) == arg0) {
                if (count++ == arg1) {
                    return index | 0x100;
                }
            }
        }
        index++;
    } while (index < 11);
    return -1;
}

s32 func_00266DF0(s32 arg0) {
    s32 var_s2;
    s32 var_s0;
    u32 *temp_v0;
    u32 *temp_v0_2;

    var_s2 = 1;
    var_s0 = 0;
    do {
        if ((func_001DF540(0, var_s2) != 0) && ((temp_v0 = func_00250740(0, var_s2, 2)) != NULL) && (func_001E2100(0, var_s2, 4) != 0) && (func_001E2100(0, var_s2, 3) != 0) && (func_001E2100(0, var_s2, 5) != 0) && (((u32) *temp_v0 >> 8) == arg0)) {
            var_s0 += 1;
        }
        var_s2 += 1;
    } while (var_s2 < 0xB);
    var_s2 = 1;
    do {
        if ((func_001DF540(1, var_s2) != 0) && ((temp_v0_2 = func_00250740(1, var_s2, 2)) != NULL) && (func_001E2100(1, var_s2, 4) != 0) && (func_001E2100(1, var_s2, 3) != 0) && (func_001E2100(1, var_s2, 5) != 0) && (((u32) *temp_v0_2 >> 8) == arg0)) {
            var_s0 += 1;
        }
        var_s2 += 1;
    } while (var_s2 < 0xB);
    return var_s0;
}

s32 func_00266F70(s32 arg0, s32 arg1) {
    s32 var_s0;
    s32 var_s3;
    u32 *temp_v0;
    u32 *temp_v0_2;

    var_s3 = 1;
    var_s0 = 0;
    do {
        if ((func_001E2100(0, var_s3, 4) != 0) && (func_001E2100(0, var_s3, 3) != 0) && (func_001E2100(0, var_s3, 5) != 0) && (arg1 == func_0024DE70(0, var_s3))) {
            temp_v0 = func_00250740(0, var_s3, 2);
            if ((temp_v0 != NULL) && (((u32) *temp_v0 >> 8) == arg0)) {
                var_s0 += 1;
            }
        }
        var_s3 += 1;
    } while (var_s3 < 0xB);
    var_s3 = 1;
    do {
        if ((func_001E2100(1, var_s3, 4) != 0) && (func_001E2100(1, var_s3, 3) != 0) && (func_001E2100(1, var_s3, 5) != 0) && (arg1 == func_0024DE70(1, var_s3))) {
            temp_v0_2 = func_00250740(1, var_s3, 2);
            if ((temp_v0_2 != NULL) && (((u32) *temp_v0_2 >> 8) == arg0)) {
                var_s0 += 1;
            }
        }
        var_s3 += 1;
    } while (var_s3 < 0xB);
    return var_s0;
}

typedef struct Effect_002670F0 {
    u32 flags;
    union {
        u32 word;
        struct {
            u16 amount;
            u16 operation;
        } parts;
    } data;
} Effect_002670F0;

s32 func_002670F0(s32 arg0, s32 arg1) {
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s1;
    u32 temp_a0;
    u32 temp_a0_2;
    u32 temp_a1;
    u32 temp_a1_2;
    u32 temp_a1_3;
    u32 temp_a1_4;
    u32 temp_v0_2;
    u32 temp_v0_4;
    Effect_002670F0 *temp_v0;
    Effect_002670F0 *temp_v0_3;

    var_s1 = arg1;
    if (arg1 == 0) {
        return 0;
    }
    var_s0 = 0;
    do {
        if ((func_001E2100(0, var_s0, 4) != 0) && (func_001E2100(0, var_s0, 3) != 0) && (func_001E2100(0, var_s0, 5) != 0)) {
            temp_v0 = func_00250740(0, var_s0, 2);
            if (temp_v0 != NULL) {
                temp_a1 = temp_v0->flags;
                if (((temp_a1 >> 8) == 0x3B) && ((temp_a1 & 0x3F) == arg0)) {
                    temp_a1_2 = temp_v0->data.word;
                    temp_a0 = temp_a1_2 >> 0x10;
                    switch (temp_a0) {
                    case 0:
                        var_s1 += temp_v0->data.parts.amount;
                        break;
                    case 1:
                        var_s1 -= temp_v0->data.parts.amount;
                        break;
                    case 2:
                        var_s1 += var_s1 * (temp_v0->data.parts.amount - 1);
                        break;
                    case 3:
                        temp_v0_2 = temp_a1_2 & 0xFFFF;
                        if (temp_v0_2 != 0) {
                            var_s1 -= (u32) var_s1 / temp_v0_2;
                        }
                        break;
                    }
                }
            }
        }
        var_s0 += 1;
    } while (var_s0 < 0xB);
    var_s0_2 = 1;
    do {
        if ((func_001E2100(1, var_s0_2, 4) != 0) && (func_001E2100(1, var_s0_2, 3) != 0) && (func_001E2100(1, var_s0_2, 5) != 0)) {
            temp_v0_3 = func_00250740(1, var_s0_2, 2);
            if (temp_v0_3 != NULL) {
                temp_a1_3 = temp_v0_3->flags;
                if (((temp_a1_3 >> 8) == 0x3B) && ((temp_a1_3 & 0x3F) == arg0)) {
                    temp_a1_4 = temp_v0_3->data.word;
                    temp_a0_2 = temp_a1_4 >> 0x10;
                    switch (temp_a0_2) {
                    case 0:
                        var_s1 += temp_v0_3->data.parts.amount;
                        break;
                    case 1:
                        var_s1 -= temp_v0_3->data.parts.amount;
                        break;
                    case 2:
                        var_s1 += var_s1 * (temp_v0_3->data.parts.amount - 1);
                        break;
                    case 3:
                        temp_v0_4 = temp_a1_4 & 0xFFFF;
                        if (temp_v0_4 != 0) {
                            var_s1 -= (u32) var_s1 / temp_v0_4;
                        }
                        break;
                    }
                }
            }
        }
        var_s0_2 += 1;
    } while (var_s0_2 < 0xB);
    return func_002508D0(var_s1);
}

typedef struct {
    u8 pad00[0x3E];
    u8 value3E;
    u8 pad3F[5];
    u8 side;
    u8 active;
    u8 pad46[0x11];
    s8 flag0 : 1;
    s8 swapped : 1;
    s8 linked : 1;
} Obj_00267380;

s32 func_00267380(s32 arg0, s32 arg1) {
    s32 i;
    s32 count;
    Obj_00267380 *obj = (Obj_00267380 *)arg0;
    s32 x;
    s32 y;
    s32 pos;
    u32 *card;

    if (obj == NULL) {
        return 0;
    }
    if (arg1 == ((obj->swapped == 0) ? obj->side : ((obj->side == 0) ? 1 : 0))) {
        return 0;
    }
    if (obj->active == 0) {
        return 0;
    }
    if (obj->linked == 0) {
        return 1;
    }
    if ((count = func_00266DF0(0x44)) > 0) {
        for (i = 0; i < count; i++) {
            pos = func_00266C70(0x44, i);
            y = pos >> 8;
            x = pos & 0xFF;
            if (func_001E2100(y, x, 4) && func_001E2100(y, x, 3) && func_001E2100(y, x, 5) &&
                func_00250360(y, x) == func_00250370(obj) &&
                (card = func_00250740(y, x, 2)) != NULL) {
                switch (*card & 0x3F) {
                case 29:
                    return ((obj->value3E >> 5) == 0) ? 1 : 0;
                case 30:
                    return ((obj->value3E >> 5) != 0) ? 1 : 0;
                }
            }
        }
    }
    return 0;
}

typedef struct {
    u8 pad00[0x3E];
    u8 value3E;
    u8 pad3F[5];
    u8 side;
    u8 active;
    u8 pad46[0x11];
    s8 flag0 : 1;
    s8 swapped : 1;
} Obj_00267560;

s32 func_00267560(s32 arg0) {
    Obj_00267560 *obj = (Obj_00267560 *)arg0;
    s32 player;
    s32 i;
    s32 count;
    s32 x;
    s32 y;
    s32 pos;
    u32 *card;

    if (obj == NULL) {
        return 0;
    }
    player = func_001DE540();
    if (player == ((obj->swapped == 0) ? obj->side : ((obj->side == 0) ? 1 : 0))) {
        return 0;
    }
    if (obj->active == 0) {
        return 0;
    }
    if ((count = func_00266DF0(0x44)) > 0) {
        for (i = 0; i < count; i++) {
            pos = func_00266C70(0x44, i);
            y = pos >> 8;
            x = pos & 0xFF;
            if (func_001E2100(y, x, 4) && func_001E2100(y, x, 3) && func_001E2100(y, x, 5) &&
                (card = func_00250740(y, x, 2)) != NULL) {
                switch (*card & 0x3F) {
                case 29:
                    return ((obj->value3E >> 5) == 0) ? 1 : 0;
                case 30:
                    return ((obj->value3E >> 5) != 0) ? 1 : 0;
                }
            }
        }
    }
    return 0;
}

s32 func_00267700(s32 arg0, s32 arg1) {
    s32 index;
    s32 count;
    s32 column;
    s32 row;
    s32 value;
    s32 *data;

    if (arg1 == 0) {
        return 0;
    }
    if ((count = func_00266DF0(0xB)) > 0) {
            for (index = 0; index < count; index++) {
            value = func_00266C70(0xB, index);
            row = value >> 8;
            column = value & 0xFF;
            if ((func_001E2100(row, column, 4) != 0) &&
                (func_001E2100(row, column, 3) != 0) &&
                (func_001E2100(row, column, 5) != 0)) {
                data = func_00250740(row, column, 2);
                if (data != NULL) {
                    switch (*data & 0x3F) {
                    case 0:
                        if (!(func_001E0700(arg0, arg1) & 0x1F)) {
                            if ((func_001E0700(arg0, arg1) >> 5) == 0) {
                                return 1;
                            }
                        }
                        return 0;
                    }
                }
            }
            }
    }
    return 0;
}

s32 func_00267860(s32 arg0, s32 arg1) {
    s32 i;
    s32 count;
    s32 entry;
    s32 low;
    s32 high;
    s32 *info;

    if (arg1 == 0) {
        return 0;
    }
    if ((count = func_00266DF0(0xB)) > 0) {
        for (i = 0; i < count; i++) {
            entry = func_00266C70(0xB, i);
            high = entry >> 8;
            low = entry & 0xFF;
            if ((func_001E2100(high, low, 4) != 0) &&
                (func_001E2100(high, low, 3) != 0) &&
                (func_001E2100(high, low, 5) != 0)) {
                info = func_00250740(high, low, 2);
                if (info != NULL) {
                    switch (*info & 0x3F) {
                    case 0:
                        if (!(func_001E0700(arg0, arg1) & 0x1F) &&
                            ((func_001E0700(arg0, arg1) >> 5) == 0)) {
                            return entry;
                        }
                        break;
                    }
                }
            }
        }
    }
    return 0;
}

s32 func_002679C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 state;
    s32 first;

    state = func_001DE540();
    if ((state == func_0024DE70(arg2, arg3)) ||
        ((func_001E0700(arg0, arg1) >> 5) != 0) ||
        ((func_001E0700(arg2, arg3) >> 5) != 0) ||
        (arg1 == 0) || (arg3 == 0)) {
        return -1;
    }
    if (func_00267560(func_001DF540(arg2, arg3)) != 0) {
        return -1;
    }
    if (func_001E2100(arg2, arg3, 4) != 0) {
        first = func_001E0830(arg0, arg1);
        return func_0024EA70(first, func_001E0830(arg2, arg3)) + 1;
    }
    if (func_00266DF0(0x3D) > 0) {
        first = func_001E0830(arg0, arg1);
        return func_0024EA70(first, func_001E0830(arg2, arg3)) + 1;
    }
    return -1;
}

s32 func_00267B30(s32 arg0) {
    s32 var_s0;
    s32 temp_v0;
    s32 var_s2;
    s32 temp_s3;
    s32 temp_s4;
    s32 temp_v0_2;
    s32 temp_v1;
    u32 *temp_v0_3;
    u32 temp_a0;

    temp_v0 = func_00266DF0(0x56);
    var_s2 = 0;
    for (var_s0 = 0; var_s0 < temp_v0; var_s0++) {
            temp_v0_2 = func_00266C70(0x56, var_s0);
            temp_s4 = temp_v0_2 >> 8;
            temp_s3 = temp_v0_2 & 0xFF;
            temp_v0_3 = func_00250740(temp_s4, temp_s3, 2);
            if (temp_v0_3 != NULL) {
                temp_a0 = *temp_v0_3;
                if ((temp_a0 >> 8) == 0x56) {
                    temp_v1 = (temp_a0 >> 6) & 3;
                    if (temp_v1 == 2) {
                        if (arg0 != func_0024DE70(temp_s4, temp_s3)) {
                            var_s2 -= 1;
                        }
                    } else if (temp_v1 == 3) {
                        var_s2 += 1;
                    }
                }
            }
    }
    if (var_s2 > 0) {
        var_s2 = 1;
    } else if (var_s2 < 0) {
        var_s2 = -1;
    }
    return var_s2;
}

INCLUDE_ASM("asm/nonmatchings/main_076", func_00267C50);

INCLUDE_ASM("asm/nonmatchings/main_076", func_00268460);

s32 func_00268600(s32 arg0, s32 arg1) {
    extern s32 func_001E1030();
    s32 type;
    s32 i;
    s32 v;
    s32 min;
    s32 best;
    s32 pos;
    s32 dist;

    best = -1;
    min = 0xFF;
    for (i = 0; i < 8; i++) {
        pos = func_0024E410(arg0, i);
        if ((v = func_001E3790(pos & 0xFF, pos >> 8)) >= 0) {
            type = func_001E1030(v >> 8, v & 0xFF);
            if (type == func_002686F0(arg1)) {
                dist = func_001E13C0(v >> 8, v & 0xFF);
                if (dist < min) {
                    min = dist;
                    best = v;
                }
            }
        }
    }
    return best;
}

s32 func_002686F0(s32 arg0) {
    s32 result;

    switch (arg0) {
    case 0:
        result = 0x38;
        break;
    case 1:
        result = 0x39;
        break;
    case 2:
        result = 0x36;
        break;
    case 3:
        result = 0x37;
        break;
    default:
        result = 0;
        break;
    }

    return result;
}

typedef struct Command_00268760 {
    s32 unused;
    s32 kind;
    u32 flags;
    u16 value;
    u16 unusedE;
} Command_00268760;

typedef struct State_00268760 {
    u16 value;
    u16 unused2;
    u16 stage;
    u8 ids[0xCE];
    u8 count;
    u8 padding[0x2D];
    u16 timer;
} State_00268760;


s32 func_00268760(void *arg0, void *arg1, s32 arg2) {
    s32 stackData[4];
    s32 count;
    s32 *data = stackData;
    s32 i;
    Command_00268760 *command = arg0;
    State_00268760 *state = arg1;

    data[0] = 999;
    data[1] = 0;
    data[2] = 0;
    data[3] = 0;
    count = 0;
    func_001DE7E0(0);
    if (arg2 >= 0) {
        func_00255960(arg1);
        state->value = 0x80;
        if (func_0024E910(command->flags) == 1) {
            func_00260AF0(0x10, func_0024EC50(command->flags, 0), 100, 180);
        } else {
            func_00260740(0x10);
        }
        func_00260020(arg0, arg1, arg2, -1, 1, 1);
        func_00255AC0(arg1, 0x22D);
        return 1;
    }

    switch (state->stage) {
    case 0:
        if (state->value > 0x30) {
            state->value -= 15;
        } else {
            state->value = 0x30;
            if (func_00255B50(arg1) == 1) {
                func_001E42C0(0, -120, 80, 0x107);
                func_0025F720(arg0, arg1, data, 0x22D);
                state->stage++;
            }
        }
        if (state->value < 0x30) {
            state->value = 0x30;
        }
        func_001F6CF0((u8)state->value);
        break;

    case 1:
        for (i = 0; i < state->count; i++) {
            if (func_001F51D0(state->ids[i]) == 0) {
                count++;
            }
        }
        if (count < state->count) {
            return 1;
        }
        func_001E4530();
        count = 0;
        do {
            if ((command->flags >> (21 - count)) & 1) {
                if (count < 11) {
                    func_00250E80(0, count, 1, command->value);
                    func_00250CA0(0, count, 1, command->value);
                } else {
                    func_00250E80(1, count - 11, 1, command->value);
                    func_00250CA0(1, count - 11, 1, command->value);
                }
            }
            count++;
        } while (count < 22);
        func_00260020(arg0, arg1, arg2, 1, 0, 1);
        func_00260A70(arg1, 0x10);
        state->stage++;
        break;

    default:
        state->value += 15;
        if (state->value > 0x80) {
            state->value = 0x80;
        }
        func_001F6CF0((u8)state->value);
        if (state->value == 0x80 && state->timer++ > 16 && func_0025FD90() == 1) {
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

INCLUDE_ASM("asm/nonmatchings/main_076", func_00268AD0);

typedef struct {
    u8 pad00[4];
    s32 f4;
    u32 f8;
    u32 fC;
} Src_00268FA0;

typedef struct {
    u8 pad00[4];
    u16 state;
    u8 ids[0x1A];
    s32 f20;
    u8 pad24[0xD4 - 0x24];
    u8 nids;
    u8 padD5[0x102 - 0xD5];
    u16 timer;
} Work_00268FA0;

typedef struct {
    s32 w0;
    s32 w4;
    s32 w8;
    s32 wC;
} Req_00268FA0;


s32 func_00268FA0(void *arg0, void *arg1, s32 arg2) {
    Src_00268FA0 *src = (Src_00268FA0 *)arg0;
    Work_00268FA0 *w = (Work_00268FA0 *)arg1;
    Req_00268FA0 req;
    s32 count;
    Req_00268FA0 *p;
    s32 i;
    s32 j;

    req.w0 = 0x3E7;
    req.w4 = 0;
    req.w8 = 0;
    req.wC = 0;
    p = &req;
    count = 0;
    func_001DE7E0(0);
    if (arg2 >= 0) {
        func_00255960(arg1);
        func_00260740(0x10);
        func_00255AC0(arg1, 0x1FC);
        func_00255AC0(arg1, 0x211);
        func_00260740(0x10);
        return 1;
    }
    switch (w->state) {
    case 0:
        if (func_00255B50(arg1) == 1) {
            p->w0 = 0x1FC;
            p->w4 = 0;
            p->w8 = 1;
            p->wC = func_002670F0(0x2C, (u16)src->fC);
            w->ids[0] = func_00255A30(p, arg1);
            w->f20 = 0xFFFF;
            w->nids++;
            w->state++;
        }
        break;
    case 1:
        if (func_001F51D0(w->ids[0]) == 1) {
            return 1;
        }
        func_001DF490(src->f4, 1, func_002670F0(0x2C, (u16)src->fC));
        w->state++;
        break;
    case 2:
        func_001E42C0(0, -0x78, 0x50, 0x106);
        func_0025F720(arg0, arg1, p, 0x211);
        w->state++;
        break;
    case 3:
        for (i = 0; i < w->nids; i++) {
            if (func_001F51D0(w->ids[i]) == 0) {
                count++;
            }
        }
        if (count < w->nids) {
            return 1;
        }
        func_001E4530();
        for (j = 0; j < 0x16; j++) {
            if ((src->f8 >> (0x15 - j)) & 1) {
                if (j < 0xB) {
                    func_00250E80(0, j, 0, src->fC >> 16);
                    func_00250CA0(0, j, 0, src->fC >> 16);
                } else {
                    func_00250E80(1, j - 0xB, 0, src->fC >> 16);
                    func_00250CA0(1, j - 0xB, 0, src->fC >> 16);
                }
            }
        }
        func_00260A70(arg1, 0x10);
        w->state++;
        break;
    default:
        if (w->timer++ > 0x10) {
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

typedef struct {
    u16 alpha;
    u16 id;
    u16 state;
    u8 handle;
    u8 pad07[0x19];
    s32 processed;
    u8 pad24[0xDE];
    u16 timer;
} State_002692D0;

typedef struct {
    u8 pad00[8];
    s32 mask;
    s32 value;
} Context_002692D0;

void func_0024F370(s32, s32);

s32 func_002692D0(void *arg0, void *arg1, s32 arg2) {
    s32 data[4];
    s32 *params = data;
    State_002692D0 *state = (State_002692D0 *)arg1;
    Context_002692D0 *context = (Context_002692D0 *)arg0;

    params[0] = 999;
    params[1] = 0;
    params[2] = 0;
    params[3] = 0;
    func_001DE7E0(0);
    if (arg2 >= 0) {
        func_00255960(arg1);
        state->alpha = 0x80;
        state->id = func_0024EFB0(context->mask);
        func_00260020(arg0, arg1, arg2, -1, 1, 1);
        func_00260AF0(0x1E, state->id, 0x64, 0xB4);
        func_00255AC0(arg1, 0x230);
    } else {
        switch (state->state) {
        case 0:
            state->timer++;
            if (state->alpha > 0x30) {
                state->alpha -= 0xF;
            } else {
                state->alpha = 0x30;
                if (func_00255B50(arg1) == 1 && state->timer >= 0x1E) {
                    params[0] = 0x230;
                    params[1] = 0;
                    params[2] = state->id;
                    params[3] = 0;
                    state->handle = func_00255A30(params, arg1);
                    state->processed = 0;
                    state->state++;
                }
            }
            if (state->alpha < 0x30) {
                state->alpha = 0x30;
            }
            func_001F6CF0((u8)state->alpha);
            return 1;
        case 1:
            if (func_001F51D0(state->handle) == 1) {
                if (func_001F52D0(state->handle) == 2 && state->processed == 0) {
                    s32 position;

                    position = func_001E1090(state->id >> 8, state->id & 0xFF);
                    func_0024F370(state->id >> 8, state->id & 0xFF);
                    func_001DF580(func_00250360(state->id >> 8, state->id & 0xFF),
                                 position & 0xFF, position >> 8, context->value, 0);
                    func_001F5970(state->id, 0);
                    state->processed = 1;
                }
            } else {
                func_00260020(arg0, arg1, arg2, 1, 0, 1);
                func_00260A70(arg1, 0x10);
                state->timer = 0;
                state->state++;
            }
            break;
        default:
            state->alpha += 0xF;
            if (state->alpha > 0x80) {
                state->alpha = 0x80;
            }
            func_001F6CF0((u8)state->alpha);
            if (state->alpha == 0x80) {
                if (state->timer++ > 0x10 && func_0025FD90() == 1) {
                    if (func_001DE780() != 0) {
                        func_001DE7E0(1);
                    }
                    func_001E4530();
                    return 0;
                }
            }
            break;
        }
    }
    return 1;
}

typedef struct Command_002695D0 {
    s32 id;
    u32 source;
    u32 target;
    s32 value;
} Command_002695D0;

typedef struct State_002695D0 {
    u16 flag;
    u16 position;
    u16 mode;
    u8 handles[0x16];
    union {
        s32 flags[0x19];
        u8 flagBytes[0x64];
        struct {
            s32 pad;
            s32 timers[0x18];
        } delayed;
    } entries;
    u8 pad80[2];
    u16 ids[0x25];
    s32 side;
    u8 padD0[4];
    u8 cursor;
} State_002695D0;

void func_00248460(s32, s32, s32, s32);
void func_0024F370(s32, s32);

s32 func_002695D0(void *arg0, void *arg1, s32 arg2) {
    extern s32 func_001E1030();
    extern s32 func_001E1E10();
    Command_002695D0 storage;
    Command_002695D0 *command = &storage;
    Command_002695D0 *src = arg0;
    State_002695D0 *state = arg1;

    storage.id = 999;
    storage.source = 0;
    storage.target = 0;
    storage.value = 0;
    if (arg2 >= 0) {
        s32 source;
        s32 first;
        s32 target;
        s32 second;

        func_00255960(state);
        if (func_001E2100(src->target >> 8, src->target & 0xFF, 2)) {
            func_001E1E70(src->target >> 8, src->target & 0xFF, 4, 1);
        }
        if (func_001E2100(src->source >> 8, src->source & 0xFF, 2)) {
            func_001E1E70(src->source >> 8, src->source & 0xFF, 4, 1);
        }
        if ((func_001E0700(src->source >> 8, src->source & 0xFF) >> 5) == 0) {
            state->side = 1;
            func_001E1E70(src->target >> 8, src->target & 0xFF, 2, 1);
        } else {
            state->side = 2;
            func_001E1E70(src->target >> 8, src->target & 0xFF, 2, 1);
        }
        if (src->value == 999) {
            func_00255AC0(state, 0x21A);
            state->side = 1;
        } else {
            if (state->side == 1) {
                source = src->source;
            } else {
                source = src->target;
            }
            if (state->side == 1) {
                target = src->target;
            } else {
                target = src->source;
            }
            if ((first = func_0026AB80(src->source >> 8, 0x2B)) < 0 ||
                !func_00249560(func_001E1030(target >> 8, target & 0xFF) & 0xFFFF) ||
                func_00271F90(source >> 8, source & 0xFF,
                    func_001E1090(source >> 8, source & 0xFF) & 0xFF,
                    func_001E1090(source >> 8, source & 0xFF) >> 8, 0xB) == 1) {
                state->flag = 0;
                func_00269D60(src, state);
            } else {
                func_00255AC0(state, 0x25A);
                if ((second = func_0026AB80(src->target >> 8, 0x2E)) >= 0) {
                    func_00260AF0(0, second, 0xB4, 0xB4);
                    func_001F5970(second, 0);
                    func_002516D0(second >> 8, second & 0xFF, 1);
                    state->mode = 16;
                    state->flag = 0;
                    state->position = second;
                    return 1;
                }
                func_00260AF0(0, first, 0xB4, 0xB4);
                func_001F5970(first, 0);
                func_002516D0(first >> 8, first & 0xFF, 1);
                state->mode = 16;
                state->flag = 1;
                state->position = first;
                return 1;
            }
        }
        return 1;
    }

    switch (state->mode) {
    case 0:
        if (func_00255B50(state) == 1) {
            if (src->value == 999) {
                command->id = 0x21A;
                command->source = src->source;
                command->target = src->target;
                command->value = 1;
            }
            if (state->flag != 0) {
                func_001E42C0(0, 0, -0xA0, func_001DE210(0x330));
            } else {
                s32 target;
                if (state->side == 1) {
                    target = src->target;
                } else {
                    target = src->source;
                }
                if (func_00249560(func_001E1030(target >> 8, target & 0xFF) & 0xFFFF)) {
                    func_001E42C0(0, 0, -0xA0, 0x106);
                }
            }
            command->id = state->ids[state->cursor];
            command->source = src->source;
            command->target = src->target;
            command->value = state->side;
            state->handles[state->cursor] = func_00255A30(command, state);
            state->entries.delayed.timers[state->cursor] = 0;
            state->cursor++;
            state->mode++;
        }
        break;
    case 1:
        if (func_001F51D0(state->handles[state->cursor - 1])) {
            func_00269EC0(src, state);
            if (func_001F52D0(state->handles[state->cursor - 1]) == 2) {
                if (state->entries.flagBytes[state->cursor * 4] == 0 && src->value != 999) {
                    if ((func_001E0700(src->source >> 8, src->source & 0xFF) >> 5) == 0) {
                        func_00248460(src->source >> 8, src->source & 0xFF, (state->flag << 16) | (src->value & 0x3FFF), 0);
                        func_0024F370(src->target >> 8, src->target & 0xFF);
                        if (!func_001E2100(src->source >> 8, src->source & 0xFF, 4)) {
                            func_001E1E70(src->source >> 8, src->source & 0xFF, 2, 0);
                        }
                    } else {
                        func_00248460(src->target >> 8, src->target & 0xFF, (state->flag << 16) | (src->value & 0x3FFF), 0);
                        func_0024F370(src->source >> 8, src->source & 0xFF);
                        if (!func_001E2100(src->target >> 8, src->target & 0xFF, 4)) {
                            func_001E1E70(src->target >> 8, src->target & 0xFF, 2, 0);
                        }
                    }
                    state->entries.flags[state->cursor] = 0xFFFF;
                }
            }
            return 1;
        }
        func_001E4530();
        if (src->value == 999) {
            func_0024F370(src->source >> 8, src->source & 0xFF);
            if (!func_001E2100(src->target >> 8, src->target & 0xFF, 4)) {
                func_001E1E70(src->target >> 8, src->target & 0xFF, 2, 0);
            }
        }
        func_00217710(0, 2);
        func_001E4530();
        return 0;
    case 16:
        if (func_001E1E10((s32)state->position >> 8, state->position & 0xFF) == 0xFF && func_00255B50(state) == 1) {
            if (state->flag != 0) {
                func_001E42C0(0, -0x78, 0x50, 0x103);
            } else {
                func_001E42C0(0, -0x78, 0x50, func_001DE210(0x339));
            }
            command->id = 0x25A;
            command->source = 0;
            command->target = state->position;
            command->value = 0;
            state->mode++;
            state->handles[state->cursor] = func_00255A30(command, state);
            state->entries.delayed.timers[state->cursor] = 0;
            state->cursor++;
        }
        break;
    case 17:
        if (func_001F51D0(state->handles[state->cursor - 1]) == 1) {
            return 1;
        }
        func_001E1E70((s32)state->position >> 8, state->position & 0xFF, 0, 1);
        func_00269D60(src, state);
        func_00260A70(state, 0);
        state->mode = 0;
        break;
    default:
        return 1;
    }
    return 1;
}

void func_00269D60(void *arg0, void *arg1) {
    u32 temp_v1;

    temp_v1 = *(u32 *)((u8 *)arg0 + 0xC) >> 14;
    switch (temp_v1) {
    case 0x218:
        func_00255AC0(arg1, 0x218);
        return;
    case 0x21C:
        func_00255AC0(arg1, 0x21C);
        return;
    case 0x21D:
        func_00255AC0(arg1, 0x21D);
        return;
    case 0x21E:
        func_00255AC0(arg1, 0x21E);
        return;
    default:
        func_00255AC0(arg1, 0x218);
        return;
    }
}

void func_00269E10(void *arg0) {
    u32 temp_v1;

    temp_v1 = *(u32 *)((u8 *)arg0 + 0xC) >> 0xE;
    switch (temp_v1) {
    case 0x218:
        func_00217710(1, 0x3B);
        return;
    case 0x21C:
        func_00217710(1, 0x4B);
        return;
    case 0x21D:
        func_00217710(1, 0x4E);
        return;
    case 0x21E:
        func_00217710(1, 0x4F);
        return;
    default:
        func_00217710(1, 0x4A);
        return;
    }
}

void func_00269EC0(void *arg0, void *arg1) {
    u32 *p0;
    s32 *p1;
    u32 temp_a2;
    u32 temp_a3;
    s32 var_t0;
    s32 temp_v0;

    p0 = arg0;
    p1 = arg1;
    temp_a3 = p0[3];
    temp_a2 = temp_a3 >> 0xE;
    switch (temp_a2) {
    case 0x218:
        var_t0 = 0x40;
        break;
    case 0x21C:
        var_t0 = 0x42;
        break;
    case 0x21D:
        var_t0 = 0x40;
        break;
    case 0x21E:
        var_t0 = 0x48;
        break;
    default:
        var_t0 = 0x30;
        break;
    }
    if (temp_a3 == 0x3E7) {
        temp_v0 = p1[0x34];
        p1[0x34] = temp_v0 + 1;
        switch (temp_v0) {
        case 0:
            func_00217710(1, 0x38);
            break;
        case 0x14:
            func_00217710(1, 0x39);
            break;
        case 0x1E:
            func_00217710(1, 0x4C);
            break;
        case 0x24:
            func_00269E10(arg0);
            break;
        default:
            if (p1[0x34] == var_t0) {
                func_00217710(1, 0x3C);
            }
            break;
        }
        return;
    } else {
        temp_v0 = p1[0x34];
        p1[0x34] = temp_v0 + 1;
        switch (temp_v0) {
        case 0:
            func_00217710(1, 0x38);
            return;
        case 0x14:
            func_00217710(1, 0x39);
            return;
        case 0x1E:
            func_00217710(1, 0x4C);
            return;
        case 0x24:
            func_00269E10(arg0);
            return;
        case 0x25:
            if ((p0[3] >> 0xE) == 0x21D || (p0[3] >> 0xE) == 0x21E) {
                func_00217710(1, 0x3B);
            }
            return;
        default:
            if (p1[0x34] == var_t0) {
                func_00217710(1, 0x3C);
            }
            return;
        }
    }
}

typedef struct Packet_0026A0A0 {
    u32 command;
    u32 source;
    u32 target;
    u32 data;
} Packet_0026A0A0;

typedef struct State_0026A0A0 {
    u16 id;
    u16 mode;
    u16 phase;
    u8 handle;
    u8 pad07[0x19];
    u32 done;
    u8 pad24[0xA8];
    s32 card;
    s32 frame;
    u8 children;
    u8 padD5[0x2D];
    u16 ticks;
} State_0026A0A0;

void func_00248460(s32, s32, s32, s32);
void func_0024F370(s32, s32);

s32 func_0026A0A0(void *arg0, void *arg1, s32 arg2) {
    Packet_0026A0A0 packet_data;
    Packet_0026A0A0 *packet = &packet_data;
    Packet_0026A0A0 *request = arg0;
    State_0026A0A0 *state = arg1;
    s32 temp_a0_2;
    s32 temp_s3;
    s32 temp_s4;
    s32 temp_s5;
    s32 temp_v0_10;
    s32 temp_v0_11;
    s32 temp_v0_12;
    s32 temp_v0_26;
    s32 temp_v0_27;
    s32 temp_v0_9;
    s32 var_a2;
    s32 var_s0;
    s32 var_v0_2;
    u16 temp_a0;
    u16 temp_v1;
    u16 temp_v1_2;
    u32 temp_a1;
    u32 temp_a1_2;
    u32 temp_v0;
    u32 temp_v0_13;
    u32 temp_v0_14;
    u32 temp_v0_15;
    u32 temp_v0_16;
    u32 temp_v0_17;
    u32 temp_v0_18;
    u32 temp_v0_19;
    u32 temp_v0_20;
    u32 temp_v0_21;
    u32 temp_v0_22;
    u32 temp_v0_23;
    u32 temp_v0_24;
    u32 temp_v0_25;
    u32 temp_v0_2;
    u32 temp_v0_3;
    u32 temp_v0_4;
    u32 temp_v0_5;
    u32 temp_v0_6;
    u32 temp_v0_7;
    u32 temp_v0_8;
    u32 var_v0;

    extern s32 func_001E1E10();

    packet_data.command = 0x3E7;
    packet_data.source = 0;
    packet_data.target = 0;
    packet_data.data = 0;
    if (arg2 >= 0) {
        func_00255960(arg1);
        temp_v0 = request->target;
        if (func_001E2100((s32) (temp_v0 >> 8), temp_v0 & 0xFF, 2) != 0) {
            temp_v0_2 = request->target;
            func_001E1E70(temp_v0_2 >> 8, temp_v0_2 & 0xFF, 4, 1);
        }
        temp_v0_3 = request->source;
        if (func_001E2100((s32) (temp_v0_3 >> 8), temp_v0_3 & 0xFF, 2) != 0) {
            temp_v0_4 = request->source;
            func_001E1E70(temp_v0_4 >> 8, temp_v0_4 & 0xFF, 4, 1);
        }
        temp_v0_5 = request->source;
        if ((func_001E0700((s32) (temp_v0_5 >> 8), temp_v0_5 & 0xFF) >> 5) == 0) {
            state->card = 1;
            temp_v0_6 = request->target;
            func_001E1E70(temp_v0_6 >> 8, temp_v0_6 & 0xFF, 2, 1);
        } else {
            state->card = 2;
            temp_v0_7 = request->target;
            func_001E1E70(temp_v0_7 >> 8, temp_v0_7 & 0xFF, 2, 1);
        }
        var_s0 = func_00248E30((s32) ((u32) request->source >> 8), func_00248EA0());
        temp_v0_8 = request->source;
        if ((((func_001E0700((s32) (temp_v0_8 >> 8), temp_v0_8 & 0xFF) >> 5) == 0) ? 1 : 2) == 1) {
            var_v0 = request->source;
        } else {
            var_v0 = request->target;
        }
        temp_s4 = var_v0 & 0xFF;
        temp_s5 = (s32) var_v0 >> 8;
        temp_s3 = func_001E1090(temp_s5, temp_s4) & 0xFF;
        if (func_00271F90(temp_s5, temp_s4, temp_s3, func_001E1090(temp_s5, temp_s4) >> 8, 0xB) == 0) {
            if ((temp_v0_9 = func_0026AB80((s32) ((u32) request->data >> 0x10), 0x29)) >= 0) {
                func_00255AC0(arg1, 0x25A);
                if ((temp_v0_10 = func_0026AB80((s32) request->target, 0x2E)) >= 0) {
                    func_00255AC0(arg1, 0x219);
                    func_00260AF0(0, temp_v0_10, 0xB4, 0xB4);
                    func_001F5970(temp_v0_10, 0);
                    func_002516D0(temp_v0_10 >> 8, temp_v0_10 & 0xFF, 1);
                    state->card = temp_v0_10;
                    state->phase = 0x10U;
                    state->mode = 0U;
                    state->id = (u16) var_s0;
                    return 1;
                }
                func_00255AC0(arg1, 0x223);
                func_001DE7E0(0);
                func_00260AF0(0, temp_v0_9, 0xB4, 0xB4);
                state->phase = 0x20U;
                func_001F5970(temp_v0_9, 0);
                func_002516D0(temp_v0_9 >> 8, temp_v0_9 & 0xFF, 1);
                state->card = temp_v0_9;
                state->mode = 0U;
                state->id = (u16) var_s0;
                return 1;
            }
            if ((temp_v0_11 = func_0026AB80((s32) ((u32) request->target >> 8), 0x2B)) >= 0) {
                func_00255AC0(arg1, 0x219);
                func_00255AC0(arg1, 0x25A);
                if ((temp_v0_12 = func_0026AB80((s32) request->target, 0x2E)) >= 0) {
                    func_00260AF0(0, temp_v0_12, 0xB4, 0xB4);
                    func_001F5970(temp_v0_12, 0);
                    func_002516D0(temp_v0_12 >> 8, temp_v0_12 & 0xFF, 1);
                    state->card = temp_v0_12;
                    state->phase = 0x10U;
                    state->mode = 0U;
                    state->id = (u16) var_s0;
                    return 1;
                }
                func_00260AF0(0, temp_v0_11, 0xB4, 0xB4);
                func_001F5970(temp_v0_11, 0);
                func_002516D0(temp_v0_11 >> 8, temp_v0_11 & 0xFF, 1);
                state->card = temp_v0_11;
                state->phase = 0x10U;
                state->mode = 1U;
                state->id = (u16) var_s0;
                return 1;
            }
        }
        func_00255AC0(arg1, 0x219);
        if (var_s0 < 0) {
            var_s0 = 0;
        }
        state->phase = 2U;
        state->id = (u16) var_s0;
        state->mode = 0U;
        return 1;
    }
    if (func_00255B50(arg1) != 1) {
        return 1;
    }
    temp_v1 = state->phase;
    switch (temp_v1) {
    case 0:
        func_001DE7E0(0);
        func_001E42C0(0, -0x78, 0x50, 0x10B);
        packet->command = 0x223;
        if (((u32) request->target >> 8) == 0) {
            var_v0_2 = 1;
        } else {
            var_v0_2 = 0;
        }
        packet->source = (u32) (var_v0_2 << 8);
        packet->target = (u32) (((u32) request->target >> 8) << 8);
        packet->data = (s32) state->id;
        state->handle = func_00255A30(packet, arg1);
        state->children = (u8) (state->children + 1);
        state->phase = (u16) (state->phase + 1);
        return 1;
    case 1:
        func_001DE7E0(0);
        if (func_001F51D0((s32) state->handle) != 0) {
            temp_a0 = state->ticks;
            state->ticks = (u16) (temp_a0 + 1);
            if (temp_a0 == 6) {
                func_00261570(0x1E, ((request->target == 0) ? 1 : 0) << 8, 0x64U, 0xB4U);
            }
        } else {
            func_001E4530();
            temp_v0_13 = request->source;
            if ((func_001E0700((s32) (temp_v0_13 >> 8), temp_v0_13 & 0xFF) >> 5) == 0) {
                temp_v0_14 = request->target;
                func_0024F370(temp_v0_14 >> 8, temp_v0_14 & 0xFF);
            } else {
                temp_v0_15 = request->source;
                func_0024F370(temp_v0_15 >> 8, temp_v0_15 & 0xFF);
            }
            func_001DF490((s32) ((u32) request->source >> 8), 1, (s32) state->id);
            func_00260A70(arg1, 0x10);
            state->ticks = 0U;
            if (func_001DE780() != 0) {
                func_001DE7E0(1);
            }
            state->phase = 0x40U;
        }
        return 1;
    case 2:
        if (state->mode == 1) {
            func_001E42C0(0, 0, -0xA0, func_001DE210(0x330));
        } else {
            func_001E42C0(0, 0, -0xA0, 0x10C);
        }
        packet->command = 0x219;
        packet->source = (u32) request->source;
        packet->target = (u32) request->target;
        temp_v0_16 = request->source;
        if ((func_001E0700((s32) (temp_v0_16 >> 8), temp_v0_16 & 0xFF) >> 5) == 0) {
            var_a2 = 1;
        } else {
            var_a2 = 2;
        }
        packet->data = (s32) ((state->id << 0x10) | ((state->mode << 8) | var_a2));
        state->handle = func_00255A30(packet, arg1);
        state->phase = (u16) (state->phase + 1);
        break;
    case 3:
        if (func_001F51D0((s32) state->handle) != 0) {
            temp_a0_2 = state->frame;
            state->frame = (s32) (temp_a0_2 + 1);
            switch (temp_a0_2) {
            case 0x0:
                func_00217710(1, 0x38);
                break;
            case 0x14:
                func_00217710(1, 0x39);
                break;
            case 0x1E:
                func_00217710(1, 0x4C);
                break;
            case 0x24:
                func_00217710(1, 0x4D);
                break;
            case 0x25:
                func_00217710(1, 0x3B);
                break;
            case 0x40:
                func_00217710(1, 0x3C);
                break;
            }
            if (func_001F52D0((s32) state->handle) == 2) {
                if (*(u8 *)&state->done != 0xFFFF) {
                    temp_v0_17 = request->source;
                    if ((func_001E0700((s32) (temp_v0_17 >> 8), temp_v0_17 & 0xFF) >> 5) == 0) {
                        temp_v0_18 = request->data;
                        temp_a1 = request->source;
                        func_00248460(temp_a1 >> 8, temp_a1 & 0xFF, (state->mode << 0x10) | (temp_v0_18 & 0x3FFF), (temp_v0_18 >> 0x10) & 0xFF);
                        temp_v0_19 = request->target;
                        func_0024F370(temp_v0_19 >> 8, temp_v0_19 & 0xFF);
                        temp_v0_20 = request->source;
                        if (func_001E2100((s32) (temp_v0_20 >> 8), temp_v0_20 & 0xFF, 4) == 0) {
                            temp_v0_21 = request->source;
                            func_001E1E70(temp_v0_21 >> 8, temp_v0_21 & 0xFF, 2, 0);
                        }
                    } else {
                        temp_v0_22 = request->data;
                        temp_a1_2 = request->target;
                        func_00248460(temp_a1_2 >> 8, temp_a1_2 & 0xFF, (state->mode << 0x10) | (temp_v0_22 & 0x3FFF), (temp_v0_22 >> 0x10) & 0xFF);
                        temp_v0_23 = request->source;
                        func_0024F370(temp_v0_23 >> 8, temp_v0_23 & 0xFF);
                        temp_v0_24 = request->target;
                        if (func_001E2100((s32) (temp_v0_24 >> 8), temp_v0_24 & 0xFF, 4) == 0) {
                            temp_v0_25 = request->target;
                            func_001E1E70(temp_v0_25 >> 8, temp_v0_25 & 0xFF, 2, 0);
                        }
                    }
                    state->done = 0xFFFF;
                }
            }
            return 1;
        }
        func_001E4530();
        func_00217710(0, 2);
        func_001E4530();
        return 0;
    case 16:
        if (func_001E1E10((u32)state->card >> 8, state->card & 0xFF) == 0xFF) {
            if (state->mode == 1) {
                func_001E42C0(0, -0x78, 0x50, 0x103);
            } else {
                func_001E42C0(0, -0x78, 0x50, func_001DE210(0x339));
            }
            packet->command = 0x25A;
            packet->source = 0U;
            packet->target = (u32) state->card;
            packet->data = 0;
            state->handle = func_00255A30(packet, arg1);
            state->done = 0;
            state->children = (u8) (state->children + 1);
            state->phase = 0x11U;
        }

        break;
    case 17:
        if (func_001F51D0((s32) state->handle) == 1) {
            return 1;
        }
        temp_v0_26 = state->card;
        func_001E1E70((u32) temp_v0_26 >> 8, temp_v0_26 & 0xFF, 0, 1);
        func_001E4530();
        func_00260A70(arg1, 0);
        state->phase = 2U;
        break;
    case 32:
        func_001DE7E0(0);
        if (func_001E1E10((u32)state->card >> 8, state->card & 0xFF) == 0xFF) {
            func_001E42C0(0, -0x78, 0x50, 0x32E);
            packet->command = 0x25A;
            packet->source = 0U;
            packet->target = (u32) state->card;
            packet->data = 0;
            state->handle = func_00255A30(packet, arg1);
            state->done = 0;
            state->children = (u8) (state->children + 1);
            state->phase = (u16) (state->phase + 1);
            break;
        }
        break;
    case 33:
        func_001DE7E0(0);
        if (func_001F51D0((s32) state->handle) != 0) {
            return 1;
        }
        temp_v0_27 = state->card;
        func_001E1E70((u32) temp_v0_27 >> 8, temp_v0_27 & 0xFF, 0, 1);
        func_002610D0(0, ((u32) state->card >> 8) << 8, 0x64, 0xB4);
        state->phase = 0U;
        break;
    default:
        temp_v1_2 = state->ticks;
        state->ticks = (u16) (temp_v1_2 + 1);
        if ((s32) temp_v1_2 > 0x10) {
            func_00217710(0, 2);
            func_001E4530();
            return 0;
        }
        break;
    }
    return 1;
}

s32 func_0026AB80(s32 arg0, s32 arg1) {
    switch (arg1) {
    case 0x29:
    case 0x2A:
    case 0x2C:
    case 0x23:
    case 0x4A:
    case 0x4B:
    case 0xE:
    case 0x4:
    case 0x30:
    case 0x31:
        return func_0026AC90(arg0, 2, arg1);
    case 0x50:
    case 0x4C:
    case 0x2D:
    case 0x11:
    case 0x2E:
    case 0x2B:
        return func_0026AC90(arg0, 3, arg1);
    default:
        return -1;
    }
}

s32 func_0026AC90(s32 arg0, s32 arg1, s32 arg2) {
    s32 i;
    s32 best;
    s32 result;
    u32 *entry;

    best = 0xFF;
    result = 0xFF;
    if (func_00266DF0(0xF) > 0) {
        return -1;
    }
    if (arg1 & 1) {
        for (i = 6; i < 11; i++) {
            if ((entry = func_00250740(arg0, i, 0)) != NULL) {
                if ((func_001E0700(arg0, i) >> 5) == 4 && (*entry >> 8) == arg2 &&
                    func_001E13C0(arg0, i) < best) {
                    best = func_001E13C0(arg0, i);
                    result = (arg0 << 8) | i;
                }
            }
        }
    }
    if (arg1 >> 1) {
        for (i = 6; i < 11; i++) {
            if ((entry = func_00250740(arg0 == 0 ? 1 : 0, i, 0)) != NULL) {
                if ((func_001E0700(arg0 == 0 ? 1 : 0, i) >> 5) == 4 && (*entry >> 8) == arg2 &&
                    func_001E13C0(arg0 == 0 ? 1 : 0, i) < best) {
                    best = func_001E13C0(arg0 == 0 ? 1 : 0, i);
                    result = i | ((arg0 == 0 ? 1 : 0) << 8);
                }
            }
        }
    }
    if (result != 0xFF) {
        return result;
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/main_076", func_0026AE70);

s32 func_0026B1F0(s32 arg0, s32 arg1, s32 arg2, u8 arg3) {
    s32 s1;
    s32 card;
    s32 pos;

    s1 = func_001E1090(arg0, arg1);
    card = func_0024DE70(arg0, arg1);
    if (arg1 == 0) {
        return 0;
    }
    if (func_00271F90(arg0, arg1, s1 & 0xFF, s1 >> 8, 0xB) != 0) {
        s1 = func_00250360(arg0, arg1) == 0 ? 1 : 0;
        if (func_00267380(func_001DF540(arg0, arg1), s1) == 0) {
            return 1;
        }
    }
    if (func_00267700(arg0, arg1) != 0) {
        return 0;
    }
    switch (arg2) {
    case 0:
        pos = func_0026AB80(card, 0x2C);
        if (pos >= 0 && (arg3 != 0 || func_001E2100(pos >> 8, pos & 0xFF, 4) != 0)) {
            if (func_0026AB80(arg0 == 0 ? 1 : 0, 0x2E) >= 0) {
                return 0;
            }
            return 0x10001;
        }
        return 0;
    default:
        pos = func_0026AB80(card, 0x4A);
        if (pos >= 0) {
            if (arg3 != 0 || func_001E2100(pos >> 8, pos & 0xFF, 4) != 0) {
                if (func_0026AB80(arg0 == 0 ? 1 : 0, 0x2E) >= 0) {
                    return 0;
                }
                return 0x10001;
            }
        } else {
            pos = func_0026AB80(card, 0x23);
            if (pos >= 0 && (arg3 != 0 || func_001E2100(pos >> 8, pos & 0xFF, 4) != 0)) {
                if (func_0026AB80(arg0 == 0 ? 1 : 0, 0x2E) >= 0) {
                    return 0;
                }
                return 1;
            }
        }
        return 0;
    }
}

s32 func_0026B430(void *arg0) {
    ((s32 *)arg0)[0] = 0x66;
    ((s32 *)arg0)[1] = 1;
    ((s32 *)arg0)[2] = func_0026AB80(0, 0x2E);
    ((s32 *)arg0)[3] = 0;
    return 1;
}

typedef struct Request_0026B480 {
    u32 unused;
    u32 position;
    u32 result;
    u32 command;
} Request_0026B480;

typedef struct State_0026B480 {
    u8 pad0[4];
    u16 phase;
    u8 handles[26];
    s32 slots[45];
    u8 count;
    u8 padD5[0x2D];
    u16 timer;
} State_0026B480;

void func_0024F370(s32, s32);

s32 func_0026B480(void *arg0, void *arg1, s32 arg2) {
    extern s32 func_001E1030();
    extern s32 func_001E1E10();
    extern s32 func_0025F670();
    s32 buffer[4];
    s32 *command = buffer;
    Request_0026B480 *request = arg0;
    State_0026B480 *state = arg1;
    s32 card;
    s32 i;
    u32 position;
    u32 value;
    u16 timer;

    buffer[0] = 999;
    buffer[1] = 0;
    buffer[2] = 0;
    buffer[3] = 0;
    func_001DE7E0(0);
    if (arg2 >= 0) {
        func_00255960(state);
        value = request->command;
        func_002516D0((value & 0xFFFF) >> 8, value & 0xFF, 1);
        func_00255AC0(state, 0x22);
        func_00255AC0(state, 0x22B);
        func_00255AC0(state, 0x22D);
        func_00255AC0(state, 0x25A);
        func_00255AC0(state, 0x25B);
        func_00260D10(0, (u16)request->command, 180, 180);
        state->phase = 16;
        return 1;
    }

    switch (state->phase) {
    case 0:
        if (func_001F51D0(state->handles[0]) == 1) {
            return 1;
        }
        value = request->command;
        func_001E1E70((value & 0xFFFF) >> 8, value & 0xFF, 0, 1);
        value = request->command;
        func_001E42C0(0, -120, 80,
            func_001DE210(func_001E1030((value & 0xFFFF) >> 8, value & 0xFF)));
        value = request->command;
        if ((value >> 16) != 49) {
            func_0024F370((value & 0xFFFF) >> 8, value & 0xFF);
        }
        func_00260AF0(0, request->position, 100, 180);
        command[0] = 0x22;
        command[1] = 0;
        command[2] = request->position;
        command[3] = 0;
        state->handles[0] = func_00255A30(command, state);
        state->phase++;
        return 1;

    case 1:
        if (func_001F51D0(state->handles[0]) == 1) {
            return 1;
        }
        switch (request->command >> 16) {
        case 4:
            position = request->position;
            card = func_0024CA40(0, 0,
                func_0024DE70(position >> 8, position & 0xFF), 2, 0x35, 14);
            value = request->command;
            value = func_00272330(card,
                func_00250360((value & 0xFFFF) >> 8, value & 0xFF));
            request->result = value;
            if (value == 0) {
                timer = state->timer++;
                if (timer > 16) {
                    func_001E4530();
                    return 0;
                }
                return 1;
            }
            if (func_0024E910(request->result) == 1) {
                func_00260AF0(0, func_0024EC50(request->result, 0), 100, 180);
            } else {
                func_00260740(0);
            }
            func_0025F720(request, state, command, 0x22B);
            state->phase = 2;
            return 1;

        case 48:
            state->phase = 4;
            func_001E4530();
            func_00260A70(state, 16);
            break;

        case 49:
            func_00260AF0(0, request->result, 100, 180);
            command[0] = 0x22B;
            command[1] = 0;
            command[2] = request->result;
            command[3] = 0;
            state->handles[state->count] = func_00255A30(command, state);
            state->slots[state->count] = 1;
            state->phase = 2;
            state->count++;
            return 1;
        }
        return 1;

    case 2:
        switch (request->command >> 16) {
        case 4:
            if (func_0025F400(request, state, command) != 0) {
                state->phase++;
            }
            break;

        case 49:
            if (func_001F51D0(state->handles[state->count - 1]) == 1 &&
                func_001F52D0(state->handles[state->count - 1]) == 2 &&
                state->slots[state->count - 1] >= 0) {
                command[0] = 0x22D;
                command[1] = 0;
                command[2] = request->result;
                command[3] = 0;
                state->handles[state->count] = func_00255A30(command, state);
                state->slots[state->count] = 1;
                state->phase++;
                state->count++;
            }
            break;

        default:
            func_001E4530();
            return 0;
        }
        break;

    case 3:
        switch (request->command >> 16) {
        case 4:
            if (func_0025F670(request, state, command) != 0) {
                func_001E4530();
                func_00260A70(state, 16);
                state->phase++;
            }
            break;

        case 49:
            for (i = 0; i < state->count; i++) {
                if (func_001F51D0(state->handles[i]) == 1) {
                    return 1;
                }
            }
            position = request->result;
            card = func_001E0290(position / 256, position & 0xFF, 0);
            func_00250CA0(position >> 8, (u8)position, 1, card >> 1);
            func_001E4530();
            func_00260A70(state, 16);
            state->phase++;
            break;

        default:
            func_001E4530();
            return 0;
        }
        break;

    case 4:
        timer = state->timer++;
        if (timer > 16) {
            if (func_001DE780() != 0) {
                func_001DE7E0(1);
            }
            func_001E4530();
            return 0;
        }
        break;

    case 16:
        value = request->command;
        if (func_001E1E10((value & 0xFFFF) >> 8, value & 0xFF) == 0xFF &&
            func_00255B50(state) == 1) {
            switch (request->command >> 16) {
            case 49:
                command[0] = 0x25A;
                command[1] = 0;
                command[2] = (u16)request->command;
                command[3] = 0;
                break;
            default:
                command[0] = 0x25A;
                command[1] = 0;
                command[2] = (u16)request->command;
                command[3] = 1;
                break;
            }
            state->handles[0] = func_00255A30(command, state);
            state->phase = 0;
            func_001E42C0(0, -120, 80, 0x103);
            return 1;
        }
        break;

    default:
        return 1;
    }
    return 1;
}

typedef struct Command_0026BB80 {
    s32 id;
    s32 mask;
    s32 x;
    s32 y;
} Command_0026BB80;

typedef struct State_0026BB80 {
    u8 pad0[4];
    u16 state;
    u8 handle;
    u8 pad7[0xFB];
    u16 timer;
} State_0026BB80;

void func_0024F370(s32, s32);

s32 func_0026BB80(void *arg0, void *arg1, s32 arg2) {
    extern s32 func_001E1E10();
    Command_0026BB80 request;
    Command_0026BB80 *command = &request;
    State_0026BB80 *state = arg1;
    Command_0026BB80 *source = arg0;
    s32 count;
    s32 i;
    s32 index;
    s32 position;

    request.id = 999;
    request.mask = 0;
    request.x = 0;
    request.y = 0;
    count = 0;
    func_001DE7E0(0);
    if (arg2 >= 0) {
        func_00255960(arg1);
        for (i = 0; i < func_0024E910(source->mask); i++) {
            position = func_0024EC50(source->mask, i);
            func_002516D0(position >> 8, position & 0xFF, 1);
        }
        func_00255AC0(arg1, 0x3B);
        func_00260740(0x10);
        return 1;
    }

    switch (state->state) {
    case 0:
        for (index = 0; index < func_0024E910(source->mask); index++) {
            position = func_0024EC50(source->mask, index);
            if (func_001E1E10(position >> 8, position & 0xFF) == 0xFF) {
                count++;
            }
        }
        if (count >= 3) {
            if (func_00255B50(arg1) == 1) {
                state->state = 1;
                func_001E42C0(0, -0x78, 0x50, 0x105);
                command->id = 0x3B;
                command->mask = source->mask;
                command->x = source->x;
                command->y = source->y;
                state->handle = func_00255A30(command, arg1);
            }
        }
        return 1;
    case 1:
        if (func_001F51D0(state->handle) == 1) {
            if (func_001F52D0(state->handle) == 2) {
                for (i = 0; i < func_0024E910(source->mask); i++) {
                    position = func_0024EC50(source->mask, i);
                    func_0024F370(position >> 8, position & 0xFF);
                }
            }
            return 1;
        }
        func_001E4530();
        func_00260A70(arg1, 0x10);
        state->state++;
        break;
    default:
        if (state->timer++ > 0x10) {
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

typedef struct {
    u8 pad0[4];
    s32 field_4;
    u32 field_8;
    s32 field_C;
} Object_0026BE20;

typedef struct {
    u8 pad0[4];
    u16 state;
    u8 id;
} State_0026BE20;

typedef struct {
    s32 field_0;
    s32 field_4;
    u32 field_8;
    s32 field_C;
} Temp_0026BE20;

s32 func_0026BE20(void *arg0, void *arg1, s32 arg2) {
    extern s32 func_001E1E10();
    Temp_0026BE20 tempStorage;
    Temp_0026BE20 *temp = &tempStorage;
    State_0026BE20 *state;
    Object_0026BE20 *obj = (Object_0026BE20 *)arg0;

    temp->field_0 = 0x3E7;
    temp->field_4 = 0;
    temp->field_8 = 0;
    temp->field_C = 0;

    state = (State_0026BE20 *)arg1;

    if (arg2 >= 0) {
        func_00255960(state);
        func_00255AC0(state, 0x259);
        func_002516D0(obj->field_8 >> 8, obj->field_8 & 0xFF, 1);
        return 1;
    }

    if (func_00255B50(state) == 1) {
        if (func_001E1E10(obj->field_8 >> 8, obj->field_8 & 0xFF) == 0xFF) {
            if (state->state == 0) {
                temp->field_0 = 0x259;
                temp->field_4 = 0;
                temp->field_8 = obj->field_8;
                temp->field_C = obj->field_C;
                state->id = func_00255A30(temp, state);
                state->state++;
            } else {
                if (func_001F51D0(state->id) == 1) {
                    return 1;
                }
                func_001E4530();
                return 0;
            }
        }
    }
    return 1;
}

typedef struct {
    u8 pad0[4];
    s32 field_4;
    u32 field_8;
    s32 field_C;
} Object_0026BF50;

typedef struct {
    u8 pad0[4];
    u16 state;
    u8 id;
    u8 pad7;
    u8 pad8[0xFA];
    u16 counter;
} State_0026BF50;

typedef struct {
    s32 field_0;
    s32 field_4;
    u32 field_8;
    s32 field_C;
} Temp_0026BF50;

void func_0024F370();

s32 func_0026BF50(void *arg0, void *arg1, s32 arg2) {
    extern s32 func_001E1030();
    extern s32 func_001E1E10();
    Temp_0026BF50 tempStorage;
    Temp_0026BF50 *temp = &tempStorage;
    State_0026BF50 *state;
    Object_0026BF50 *obj = (Object_0026BF50 *)arg0;

    temp->field_0 = 0x3E7;
    temp->field_4 = 0;
    temp->field_8 = 0;
    temp->field_C = 0;

    state = (State_0026BF50 *)arg1;

    if (arg2 >= 0) {
        func_00255960(state);
        func_002516D0(obj->field_8 >> 8, obj->field_8 & 0xFF, 1);
        func_00260AF0(0, obj->field_8, 0xB4, 0xB4);
        func_00255AC0(state, 0x25A);
        return 1;
    }

    switch (state->state) {
    case 0:
        if (func_001E1E10(obj->field_8 >> 8, obj->field_8 & 0xFF) == 0xFF) {
            if (func_00255B50(state) == 1) {
                if (obj->field_4 == 1) {
                    s32 value = func_001E1030(obj->field_8 >> 8, obj->field_8 & 0xFF);
                    func_001E42C0(0, -0x78, 0x50, func_001DE210(value));
                } else {
                    func_001E42C0(0, -0x78, 0x50, 0x10D);
                }
                temp->field_0 = 0x25A;
                temp->field_4 = 0;
                temp->field_8 = obj->field_8;
                temp->field_C = 0;
                state->id = func_00255A30((s32 *)temp, state);
                state->state++;
            }
        }
        break;
    case 1:
        if (func_001F51D0(state->id) != 0) {
            return 1;
        }
        func_001E1E70(obj->field_8 >> 8, obj->field_8 & 0xFF, 0, 1);
        func_001E4530();
        func_00260A70(state, 0x10);
        if (obj->field_C != 0) {
            func_0024F370(obj->field_8 >> 8, obj->field_8 & 0xFF);
        } else {
            func_001F5970(obj->field_8, 0);
        }
        state->state++;
        return 1;
    default:
        if (state->counter++ > 0x10) {
            func_001E4530();
            return 0;
        }
        break;
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_076", func_0026C170);

void func_0026CD80(s32 arg0) {
    f32 v[4];
    f32 *p;

    if (arg0 < 0) {
        func_001F1E10(1, v);
        if (v[0] - 0.08f < 0.0f) {
            v[0] = 0.0f;
        } else {
            v[0] -= 0.08f;
        }
        p = &v[1];
        if (*p - 0.08f < 0.0f) {
            *p = 0.0f;
        } else {
            *p -= 0.08f;
        }
        func_001F1EE0(1, v);
        func_001F1E10(5, v);
        if (v[0] - 0.08f < 0.0f) {
            v[0] = 0.0f;
        } else {
            v[0] -= 0.08f;
        }
        if (*p - 0.08f < 0.0f) {
            *p = 0.0f;
        } else {
            *p -= 0.08f;
        }
        func_001F1EE0(5, v);
        func_001F1E10(6, v);
        if (v[0] - 0.08f < 0.0f) {
            v[0] = 0.0f;
        } else {
            v[0] -= 0.08f;
        }
        if (*p - 0.08f < 0.0f) {
            *p = 0.0f;
        } else {
            *p -= 0.08f;
        }
        func_001F1EE0(6, v);
    } else {
        func_001F1E10(1, v);
        v[0] = 0.8f;
        p = &v[1];
        *p = 0.8f;
        func_001F1EE0(1, v);
        func_001F1E10(5, v);
        v[0] = 0.8f;
        *p = 0.8f;
        func_001F1EE0(5, v);
        func_001F1E10(6, v);
        v[0] = 0.8f;
        *p = 0.8f;
        func_001F1EE0(6, v);
    }
}

typedef struct {
    u16 fade;
    u16 phase;
    u16 state;
    u8 handles[0x1A];
    s32 values[45];
    u8 count;
    u8 padding[0x2D];
    u16 timer;
} State_0026CFC0;

typedef struct {
    s32 kind;
    s32 flags;
    s32 value;
    s32 extra;
} Command_0026CFC0;

typedef struct {
    s32 unused;
    s32 value;
} Input_0026CFC0;

s32 func_0026D3C0(void *, void *, u16);

s32 func_0026CFC0(void *arg0, void *arg1, s32 arg2) {
    Command_0026CFC0 command;
    Command_0026CFC0 *cmd = &command;
    Input_0026CFC0 *input = arg0;
    State_0026CFC0 *state = arg1;
    s32 i;

    cmd->kind = 999;
    cmd->flags = 0;
    cmd->value = 0;
    cmd->extra = 0;
    func_001DE7E0(0);
    if (arg2 >= 0) {
        func_00255960(state);
        state->fade = 0x80;
        i = 0;
        do {
            func_001F5970(i, 1);
            func_001F5970(i | 0x100, 1);
            i++;
        } while (i < 11);
        func_00260AF0(30, input->value, 100, 180);
        func_00255AC0(state, 0x201);
        func_00255AC0(state, 0x23C);
        func_00260740(30);
        state->phase = 2;
        func_001A86A0(4);
    } else {
    switch (state->state) {
    case 0:
        state->timer++;
        if (state->fade > 0x30) {
            state->fade -= 15;
        } else {
            state->fade = 0x30;
            if (state->timer >= 30 && func_00255B50(state) == 1) {
                cmd->kind = 0x201;
                cmd->flags = 0;
                cmd->value = input->value;
                cmd->extra = 0;
                state->handles[0] = func_00255A30((s32 *)cmd, state);
                state->values[0] = input->value;
                state->state++;
            }
        }
        if (state->fade < 0x30) {
            state->fade = 0x30;
        }
        func_001F6CF0((u8)state->fade);
        break;
    case 1:
        if (func_001F51D0(state->handles[0]) != 0) {
            return 1;
        }
        func_00260740(0);
        state->state++;
        break;
    case 2: {
        u16 phase;
        state->count = 0;
        phase = state->phase;
        if (phase >= 14) {
            func_00260A70(state, 16);
            func_001A86A0(0);
            state->timer = 0;
            state->state = 4;
        } else if (func_0026D3C0(input, state, phase) > 0) {
            state->state++;
        } else {
            state->phase++;
        }
        break;
    }
    case 3: {
        u8 *cursor;
        s32 j;
        for (i = 0; i < state->count; i++) {
            if (func_001F51D0(state->handles[i]) != 0) {
                return 1;
            }
        }
        j = 0;
        cursor = (u8 *)state;
        for (; j < state->count; j++) {
            s32 value = *(s32 *)(cursor + 0x20);
            func_001DFD50(value >> 24, (value >> 16) & 0xFF,
                         value & 0xFF, (value & 0xFFFF) >> 8);
            cursor += 4;
        }
        if (state->phase >= 14) {
            state->state++;
            break;
        }
        state->state = 2;
        state->phase++;
        return 1;
    }
    case 4:
        state->fade += 15;
        if (state->fade > 0x80) {
            state->fade = 0x80;
        }
        func_001F6CF0((u8)state->fade);
        if (state->fade == 0x80 && state->timer++ > 16) {
            i = 0;
            do {
                func_001F5970(i, 0);
                func_001F5970(i | 0x100, 0);
                i++;
            } while (i < 11);
            if (func_001DE780() != 0) {
                func_001DE7E0(1);
            }
            func_001E4530();
            return 0;
        }
        break;
    default:
        break;
    }
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_076", func_0026D3C0);

s32 func_0026D600(s32 arg0, s32 arg1, s32 arg2, s32 *arg3) {
    s32 i;
    s32 *p;
    s32 result;
    s32 retry;
    s32 j;

    result = func_0026D6E0(arg0, arg1, arg2, 0);
    if (result >= 0) {
        i = 0;
        p = arg3;
        do {
            if (result == *p) {
                retry = func_0026D6E0(arg0, arg1, arg2, 1);
                if (retry >= 0) {
                    j = 0;
                    do {
                        if (retry == *arg3) {
                            return -1;
                        }
                        j++;
                        arg3++;
                    } while (j < 22);
                    return retry;
                }
                return -1;
            }
            i++;
            p++;
        } while (i < 22);
        return result;
    }
    return -1;
}

s32 func_0026D6E0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_s0;
    s32 temp_s1;
    s32 temp_s1_2;
    s32 temp_s2;
    s32 temp_s2_2;
    s32 temp_v0;
    s32 var_v0;
    s32 var_v0_2;

    temp_v0 = func_001E1090(arg2 >> 8, arg2 & 0xFF);
    temp_s0 = temp_v0 & 0xFF;
    if (arg0 < temp_s0) {
        temp_s1 = temp_s0 - 1;
        temp_s2_2 = temp_v0 >> 8;
        if (func_001E3790(temp_s1, temp_s2_2) < 0) {
            if (arg3 == 0) {
                var_v0_2 = (temp_s2_2 << 8) | temp_s1;
            } else {
                var_v0_2 = func_0026D840(arg0, arg1, temp_s0, temp_s2_2);
            }
            return var_v0_2;
        }
        return func_0026D840(arg0, arg1, temp_s0, temp_s2_2);
    }
    if (temp_s0 < arg0) {
        temp_s1_2 = temp_s0 + 1;
        temp_s2 = temp_v0 >> 8;
        if (func_001E3790(temp_s1_2, temp_s2) < 0) {
            if (arg3 == 0) {
                var_v0 = (temp_s2 << 8) | temp_s1_2;
            } else {
                var_v0 = func_0026D840(arg0, arg1, temp_s0, temp_s2);
            }
            return var_v0;
        }
        return func_0026D840(arg0, arg1, temp_s0, temp_s2);
    }
    return func_0026D840(arg0, arg1, temp_s0, temp_v0 >> 8);
}

s32 func_0026D840(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg3 < arg1) {
        if (func_001E3790(arg2, arg3 + 1) < 0) {
            return ((arg3 + 1) << 8) | arg2;
        } else {
            return -1;
        }
    } else if (arg1 < arg3) {
        if (func_001E3790(arg2, arg3 - 1) < 0) {
            return ((arg3 - 1) << 8) | arg2;
        } else {
            return -1;
        }
    } else {
        return -1;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_076", func_0026D8F0);

typedef struct Context_0026DCC0 {
    s32 unk0;
    u32 source;
    u32 destination;
    s32 mode;
} Context_0026DCC0;

typedef struct State_0026DCC0 {
    u8 pad0[4];
    u16 state;
    u8 handles[0xCE];
    u8 count;
    u8 padD5[0x2D];
    u16 timer;
} State_0026DCC0;

typedef struct Command_0026DCC0 {
    s32 command;
    u32 source;
    u32 destination;
    s32 flags;
} Command_0026DCC0;


s32 func_0026DCC0(void *arg0, void *arg1, s32 arg2) {
    Command_0026DCC0 storage;
    Command_0026DCC0 *command = &storage;
    Context_0026DCC0 *context = arg0;
    State_0026DCC0 *state = arg1;
    s32 i;
    extern void func_001E1E70();
    extern s32 func_001E1D10();
    extern s32 func_001E1A90();
    extern s32 func_001E1580();
    extern s32 func_001E1640();

    storage.command = 999;
    storage.source = 0;
    storage.destination = 0;
    storage.flags = 0;
    func_001DE7E0(0);
    if (arg2 >= 0) {
        func_00255960(state);
        func_00255AC0(state, 0x201);
        if (context->mode == 0) {
            func_00260020(context, state, arg2, -1, 1, 1);
            if (func_0024E910(context->destination) == 1) {
                func_00260AF0(30, func_0024EC50(context->destination, 0), 100, 180);
            } else {
                func_00260740(30);
            }
        } else {
            func_00255AC0(state, 0x262);
            func_00255AC0(state, 0x23C);
        }
        return 1;
    }

    switch (state->state) {
    case 0:
        if (func_00255B50(state) == 1) {
            if (context->mode == 0) {
                if (state->timer++ >= 30) {
                    func_001E42C0(0, -120, 80, 0x113);
                    func_0025F720(context, state, command, 0x201);
                    state->state++;
                }
            } else {
                command->command = 0x201;
                command->source = 0;
                command->destination = context->source;
                command->flags = 0;
                state->handles[state->count] = func_00255A30(command, state);
                state->count++;
                state->state++;
            }
        }
        break;
    case 1:
        for (i = 0; i < state->count; i++) {
            if (func_001F51D0(state->handles[i]) != 0) {
                return 1;
            }
        }
        if (context->mode == 1) {
            s32 value = func_001E1D10(context->source >> 8, context->source & 0xFF);
            if (value != func_001E1A90(context->source >> 8, context->source & 0xFF)) {
                return 1;
            }
            func_001E42C0(0, -120, 80, 0x112);
            command->command = 0x262;
            command->source = context->source;
            command->destination = context->destination;
            command->flags = 0;
            state->handles[state->count] = func_00255A30(command, state);
            state->count++;
            state->state++;
            return 1;
        }
        state->state = 4;
        state->timer = 0;
        func_001E4530();
        func_00260A70(state, 16);
        func_00260020(context, state, arg2, 1, 0, 1);
        break;
    case 2:
        if (func_001F51D0(state->handles[state->count - 1]) == 1) {
            return 1;
        }
        func_001F5970(context->source, 0);
        func_002500C0(context->source >> 8, context->source & 0xFF, -1, 1, 1);
        func_001E1970(context->source >> 8, context->source & 0xFF, 0);
        func_001E1B70(context->source >> 8, context->source & 0xFF, -1, 0);
        func_002500C0(context->source >> 8, context->source & 0xFF, -1, 1, 1);
        state->state++;
        break;
    case 3:
        if (func_0025FD90() != 1) {
            return 1;
        }
        func_001DFBB0(context->source >> 8, context->source & 0xFF);
        if (func_001E2100(context->destination >> 8, context->destination & 0xFF, 1) != 0) {
            func_001E1E70(context->destination >> 8, context->destination & 0xFF, 1, 0);
        } else {
            func_001E1E70(context->destination >> 8, context->destination & 0xFF, 1, 1);
        }
        if (func_001E1580(context->destination >> 8, context->destination & 0xFF) == 0) {
            if (func_001E1640(context->destination >> 8, context->destination & 0xFF) == 0) {
                func_001E1E70(context->destination >> 8, context->destination & 0xFF, 0, 0);
            }
        }
        state->timer = 0;
        func_00260A70(state, 16);
        func_001E4530();
        state->state++;
        break;
    default:
        if (state->timer++ > 16 && func_0025FD90() == 1) {
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

void func_0024F370(u32, s32);

typedef struct Context_0026E1F0 {
    u32 unk0;
    u32 source;
    u32 target;
    s32 cleanup_source;
} Context_0026E1F0;

typedef struct State_0026E1F0 {
    u8 unk0[4];
    u16 step;
    u8 handles[0x1A];
    s32 flags[0x2D];
    u8 count;
    u8 unkD5[0x2D];
    u16 timer;
} State_0026E1F0;

s32 func_0026E1F0(void *arg0, void *arg1, s32 arg2) {
    s32 completed;
    s32 command[4];
    s32 *request = command;
    s32 i;
    Context_0026E1F0 *context = arg0;
    State_0026E1F0 *state = arg1;
    extern s32 func_001E1030();

    command[0] = 999;
    command[1] = 0;
    command[2] = 0;
    command[3] = 0;
    completed = 0;
    func_001DE7E0(0);
    if (arg2 >= 0) {
        func_00255960(state);
        func_00260AF0(0, context->source, 180, 180);
        func_00255AC0(state, 0x25A);
        func_00255AC0(state, 0x33);
        return 1;
    }

    switch (state->step) {
    case 0:
        if (func_00255B50(state) == 1) {
            func_001E42C0(0, -120, 80, 0x103);
            request[0] = 0x25A;
            request[1] = 0;
            request[2] = context->source;
            request[3] = 0;
            state->handles[state->count] = func_00255A30(request, state);
            state->flags[state->count] = 0;
            state->count++;
            state->step++;
        }
        break;
    case 1:
        if (func_001F51D0(state->handles[0]) == 0) {
            func_001E1E70(context->source >> 8, context->source & 0xFF, 0, 1);
            func_001E42C0(0, -120, 80,
                func_001DE210(func_001E1030(context->source >> 8, context->source & 0xFF)));
            request[0] = 0x33;
            request[1] = 0;
            request[2] = context->source;
            request[3] = 0;
            state->handles[state->count] = func_00255A30(request, state);
            state->flags[state->count] = 0;
            state->count++;
            state->step++;
        }
        break;
    case 2:
        if (func_001F51D0(state->handles[state->count - 1]) != 0) {
            if (func_001F52D0(state->handles[state->count - 1]) == 2 &&
                state->flags[state->count - 1] == 0) {
                func_00260AF0(0, context->target, 100, 180);
                request[0] = 0x33;
                request[1] = 0;
                request[2] = context->target;
                request[3] = 0;
                state->handles[state->count] = func_00255A30(request, state);
                state->flags[state->count] = 0;
                state->flags[state->count - 1] = 1;
                state->step++;
                state->count++;
            }
        }
        return 1;
    case 3:
        func_00260AF0(16, context->target, 300, 300);
        state->step++;
        break;
    case 4:
        for (i = 0; i < state->count; i++) {
            if (func_001F51D0(state->handles[i]) == 0) {
                completed++;
            }
        }
        if (completed >= state->count) {
            if (context->cleanup_source == 1) {
                func_0024F370(context->source >> 8, context->source & 0xFF);
            }
            func_0024F370(context->target >> 8, context->target & 0xFF);
            func_001E4530();
            func_00260A70(state, 16);
            state->step++;
            break;
        }
        return 1;
    default:
        if (state->timer++ > 16) {
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

INCLUDE_ASM("asm/nonmatchings/main_076", func_0026E610);

s32 func_0026E950(void) {
    s32 var_s0;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_s3;
    s32 temp_v0_3;
    s32 temp_v0_4;

    temp_v0 = func_001DE540();
    temp_v0_2 = func_001DF110(temp_v0);
    var_s3 = 0;
    for (var_s0 = 0; var_s0 < temp_v0_2; var_s0++) {
            temp_v0_3 = func_001DF0C0(temp_v0, var_s0);
            if (((s32) (temp_v0_3 & 0xF000) >> 0xC) > 0) {
                temp_v0_4 = func_0026FA70(temp_v0_3, temp_v0);
                if (var_s3 < temp_v0_4) {
                    var_s3 = temp_v0_4;
                }
            }
    }
    return var_s3;
}

s32 func_0026EA00(s32 *arg0) {
    extern s32 func_00270030();
    extern s32 func_00270260();
    s32 temp_v1;

    temp_v1 = *arg0;
    switch (temp_v1) {
    case 0:
        return func_00270030();
    case 1:
        return func_00270260();
    case 2:
        return func_0026FE70();
    default:
        return 0;
    }
}

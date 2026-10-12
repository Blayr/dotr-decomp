#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_076", func_00265890);

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

INCLUDE_ASM("asm/nonmatchings/main_076", func_00266500);

INCLUDE_ASM("asm/nonmatchings/main_076", func_00266910);

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

INCLUDE_ASM("asm/nonmatchings/main_076", func_00268600);

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

INCLUDE_ASM("asm/nonmatchings/main_076", func_00268760);

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

void func_001E42C0(s32, s32, s32, s32);
u8 func_00255A30(void *, void *);
void func_00255AC0(void *, s32);
void func_00260740(s32);
void func_00260A70(void *, s32);

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
u8 func_00255A30(void *, void *);
void func_00255AC0(void *, s32);
void func_00260A70(void *, s32);

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

INCLUDE_ASM("asm/nonmatchings/main_076", func_002695D0);

INCLUDE_ASM("asm/nonmatchings/main_076", func_00269D60);

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

INCLUDE_ASM("asm/nonmatchings/main_076", func_00269EC0);

INCLUDE_ASM("asm/nonmatchings/main_076", func_0026A0A0);

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

INCLUDE_ASM("asm/nonmatchings/main_076", func_0026B480);

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
void func_002516D0(s32, s32, s32);
u8 func_00255A30(void *, void *);
void func_00255AC0(void *, s32);
void func_00260740(s32);
void func_00260A70(void *, s32);

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

INCLUDE_ASM("asm/nonmatchings/main_076", func_0026BE20);

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

void func_001E1E70();
void func_0024F370();
void func_002516D0();
u8 func_00255A30(void *, void *);
void func_00255AC0(void *, s32);
void func_00260A70(void *, s32);

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

u8 func_00255A30(void *, void *);
void func_00255AC0(void *, s32);
void func_00260740(s32);
void func_00260A70(void *, s32);
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

INCLUDE_ASM("asm/nonmatchings/main_076", func_0026DCC0);

void func_001E1E70(u32, s32, s32, s32);
void func_0024F370(u32, s32);
u8 func_00255A30(void *, void *);
void func_00255AC0(void *, s32);
void func_00260A70(void *, s32);

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

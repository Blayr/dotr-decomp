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
s32 func_0027D720(void *, s32);

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

INCLUDE_ASM("asm/nonmatchings/main_004", func_0010DFC0);

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

INCLUDE_ASM("asm/nonmatchings/main_004", func_0010FA60);

INCLUDE_ASM("asm/nonmatchings/main_004", func_0010FFF0);

INCLUDE_ASM("asm/nonmatchings/main_004", func_001106F0);

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

INCLUDE_ASM("asm/nonmatchings/main_004", func_00111320);

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

INCLUDE_ASM("asm/nonmatchings/main_004", func_00112850);

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

INCLUDE_ASM("asm/nonmatchings/main_004", func_00113140);

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

INCLUDE_ASM("asm/nonmatchings/main_004", func_00113760);

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

INCLUDE_ASM("asm/nonmatchings/main_004", func_00113ED0);

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

s32 func_00114310(s32 arg0, void *arg1);
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

INCLUDE_ASM("asm/nonmatchings/main_004", func_00114310);

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

INCLUDE_ASM("asm/nonmatchings/main_004", func_001147B0);

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

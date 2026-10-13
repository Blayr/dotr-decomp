#include "common.h"

typedef struct {
    s16 id;
    u8 unk2;
    u8 pad3;
    s16 unk4;
    u8 pad6[6];
    s32 unkC;
} Ctx_0015A360;

typedef struct {
    u8 pad0[0x3C];
    u16 unk3C;
    u8 pad3E[0x22];
} Work_0015A360;

s32 func_0015AB10(s32 arg0, u8 *arg1, void *arg2);
s32 func_00276F10(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8,
                  s32 arg9);

s32 func_0015A360(s32 arg0, s32 arg1, s32 arg2) {
    s32 ret;
    s32 kind;
    Ctx_0015A360 *ctx = (Ctx_0015A360 *)arg2;
    Work_0015A360 work;
    s32 res;
    extern s32 func_00278890();

    ctx->id = arg0;
    if (func_001DE6D0(arg1) == 0) {
        return -1;
    }
    if (func_00278890(arg1, 0) == 5 && func_00278890(arg1, 1) == 5) {
        return -1;
    }
    kind = func_0015A5F0(arg1, &work);
    if (kind < 0) {
        return -1;
    }
    ctx->unk2 = 10;
    ctx->unkC = 2;
    arg0 = func_001E1090(arg0 >> 8, arg0 & 0xFF);
    if (kind == 0) {
        if (func_0015AB10(arg1, (u8 *)ctx, &work) >= 0) {
            ret = func_00276F10(&work, arg0 & 0xFF, arg0 >> 8, arg1 == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, func_0015D120(arg1));
            if (ret < 0) {
                if (func_001E0150(arg1) < 6) {
                    res = func_0015AF30(arg1, (u8)kind, &work, ret);
                    if (res < 0) {
                        return -1;
                    }
                    ctx->unk4 = res;
                    return 1;
                }
            } else {
                res = func_0015AF30(arg1, (u8)kind, &work, ret);
                if (res < 0) {
                    return -1;
                }
                ctx->unk4 = res;
                return 1;
            }
        }
    } else {
        ret = func_00276F10(&work, arg0 & 0xFF, arg0 >> 8, arg1 == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, func_0015D120(arg1));
    }
    if (kind == 2) {
        func_0015AD00(arg1, ctx, &work);
        res = func_0015AF30(arg1, (u8)kind, &work, ret);
        if (res < 0) {
            return -1;
        }
        ctx->unk4 = res;
        return 1;
    }
    if (func_0015A910(arg1, (u8 *)ctx, &work, work.unk3C) < 0) {
        return -1;
    }
    res = func_0015AF30(arg1, (u8)kind, &work, ret);
    if (res < 0) {
        return -1;
    }
    ctx->unk4 = res;
    return 1;
}

s32 func_0015A5F0(s32 arg0, void *arg1) {
    extern s32 func_00278890();
    s32 ids[8];
    s32 data[8];
    u8 type = (u8)func_00278890(arg0, 0);
    u8 attr = (u8)func_00278890(arg0, 1);

    if (arg1 == NULL) {
        return -1;
    }
    func_0026FD30(arg0, ids);
    if (type == 5) {
        s32 result = func_0015A910(arg0, (u8 *)data, arg1, 0x3E7);
        if (result >= 0) {
            result = 1;
        } else {
            result = -1;
        }
        return result;
    }
    if (attr == 5) {
        s32 i;
        s32 *p;
        s32 count;

        i = 0;
        count = func_0026FE20(arg0);
        if (i < count) {
            p = ids;
            do {
                if ((func_0026FCE0(*p) >> 5) == 0 && func_0026FB10(arg0, *p) == 1) {
                    func_001DCD70(arg1, ids[i]);
                    return 0;
                }
                p++;
                i++;
                count = func_0026FE20(arg0);
            } while (i < count);
        }
        return -1;
    }
    if (func_0015A820(arg0, data, arg1, 0x343) >= 0 && func_0015D030(arg0, 0x343) == 1) {
        return 2;
    }
    {
        s32 *p;
        s32 i;
        s32 count;

        i = 0;
        count = func_0026FE20(arg0);
        if (i < count) {
            p = ids;
            do {
                if ((func_0026FCE0(*p) >> 5) == 0 && func_0026FB10(arg0, *p) == 1) {
                    func_001DCD70(arg1, ids[i]);
                    return 0;
                }
                p++;
                i++;
                count = func_0026FE20(arg0);
            } while (i < count);
        }
    }
    {
        s32 result = func_0015A910(arg0, (u8 *)data, arg1, 0x3E7);
        if (result >= 0) {
            return result;
        } else {
            return -1;
        }
    }
}

s32 func_0015A820(s32 arg0, void *arg1, void *arg2, s32 arg3) {
    s32 entries[8];
    s32 index;
    s32 *entry;
    s32 key;

    func_0026FD30(arg0, entries);
    index = 0;
    if (index < func_0026FE20(arg0)) {
        key = arg3 & 0xFFFF;
        entry = entries;
        do {
            if (key == *entry && func_0026FB10(arg0, *entry) == 1) {
                *((s8 *)arg1 + 6) = index;
                func_001DCD70(arg2, entries[index]);
                return func_0026FCE0(entries[index]) >> 5;
            }
            entry++;
            index++;
        } while (index < func_0026FE20(arg0));
    }
    return -1;
}

s32 func_0015A910(s32 arg0, u8 *arg1, void *arg2, s32 arg3) {
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

INCLUDE_ASM("asm/nonmatchings/main_014", func_0015AB10);


typedef struct {
    u8 pad0[6];
    u8 slot[5];
} Obj1_0015AD00;

typedef struct {
    u8 pad0[0x38];
    s16 f38;
    s16 f3A;
    u16 id;
} Obj2_0015AD00;

s32 func_0015AD00(s32 arg0, void *arg1, void *arg2) {
    Obj1_0015AD00 *o1 = arg1;
    Obj2_0015AD00 *o2 = arg2;
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
                        o2->f38 += (s16)func_002493A0(list[i]);
                        o2->f3A += (s16)func_002493A0(list[i]);
                    }
                }
            }
        }
    }
    return 1;
}

typedef struct {
    u8 low : 4;
    u8 high : 4;
} Nibbles_0015AF30;

typedef struct {
    u8 pad[0x3E];
    u8 f3E;
} Card_0015AF30;

s32 func_0024FE40(void *, s32, s32);

s32 func_0015AF30(s32 arg0, s32 arg1, void *arg2, s32 arg3) {
    extern s32 func_00278510();
    extern s32 func_0027A130(s32, void *, s32, s32, s32, s32, s32, s32, u8, u16);
    extern s32 func_002792C0(s32, void *, s32, s32, s32, s32, u16, u8);
    Card_0015AF30 *card = arg2;
    Nibbles_0015AF30 entries[12];
    s32 id;
    s32 hi;
    s32 lo;
    s32 i;
    Nibbles_0015AF30 *entry;
    s32 pos;
    s32 cost;
    s32 bestId;
    s32 best;
    s32 y;
    s32 x;
    s32 j;
    s32 slot;

    if (card == NULL) {
        return -1;
    }
    entry = entries;
    i = 0;
    do {
        entry->low = entry->high = 15;
        entry++;
        i++;
    } while (i < 12);
    if ((u8)(card->f3E >> 5) == 0 && arg3 >= 0) {
        best = 0xFF;
        bestId = 0xFFFF;
        pos = func_001E1090(arg3 >> 8, arg3 & 0xFF);
        for (i = 0; i < 8; i++) {
            id = func_0024E410(arg0, i);
            if (id < 0) {
                continue;
            }
            lo = id & 0xFF;
            hi = id >> 8;
            if (func_001E22B0(lo, hi) == 8) {
                continue;
            }
            if (func_001E22B0(lo, hi) == 9 && func_0024FE40(card, lo, hi) == 1) {
                continue;
            }
            if (func_001E36E0(lo, hi) != 0) {
                continue;
            }
            if (func_00278510(card, arg3, func_0015D120(arg0), pos & 0xFF, pos >> 8, 0) > 0) {
                cost = func_0027A130((s32)card, entries, lo, hi, pos & 0xFF, pos >> 8, arg3, 0, 3,
                                     func_0015D120(arg0));
            } else {
                cost = func_002792C0((s32)card, entries, lo, hi, pos & 0xFF, pos >> 8, arg3, 3);
            }
            if (func_0027AFC0((u8 *)entries) > 0 && cost < best) {
                best = cost;
                bestId = id;
            }
        }
        if (bestId != 0xFFFF) {
            return bestId;
        }
    }
    for (j = 0; j < 8; j++) {
        slot = func_0024E410(arg0, j);
        if (slot < 0) {
            continue;
        }
        x = slot & 0xFF;
        y = slot >> 8;
        if (func_001E22B0(x, y) == 8) {
            continue;
        }
        if (func_001E22B0(x, y) == 9 && func_0024FE40(card, x, y) == 1) {
            continue;
        }
        if (func_001E3790(x, y) < 0) {
            return slot;
        }
    }
    return -1;
}

typedef struct Nibbles_0015B250 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_0015B250;

typedef struct Output_0015B250 {
    u16 position;
    u8 action;
    u8 pad3;
    u16 destination;
    u8 pad6[6];
    s32 special;
    u8 result;
} Output_0015B250;

s32 func_001E1E70(s32, s32, s32, s32);
s32 func_002464F0(s32, s32, s32);
s32 func_00276CC0(s32, s32, s32, s32, s32, s32);
s32 func_0027BE10(s32, s32, s32, s32, s32);

s32 func_0015B250(u16 *arg0, s32 arg1, void *arg2, u8 arg3) {
    Output_0015B250 *output = arg2;
    s32 target;
    u8 endX;
    u8 extra;
    Nibbles_0015B250 nibbles[12];
    s32 bestScore;
    s32 best;
    s32 i;
    Nibbles_0015B250 *p;
    extern s32 func_0015CBB0();
    extern s32 func_00279C40(s32, s32, s32, s32, s32, s32, void *, u8);

    target = func_001E1090(*arg0 >> 8, *arg0 & 0xFF);
    p = nibbles;
    i = 0;
    do {
        i++;
        p->low = p->high = 0xF;
        p++;
    } while (i < 12);
    {
        s32 range;
        s32 y;
        u8 minY;
        u8 minX;
        s32 candidateScore;
        u8 maxY;
        s32 packedY;
        s32 centerY;
        s32 centerX;
        s32 x;
        s32 limit;
        u16 initialScore;

        initialScore = func_0015D120(arg1);
        centerX = target & 0xFF;
        centerY = target >> 8;
        if (func_00276CC0(centerX, centerY, *arg0, 3, initialScore, 0) == 0) {
            output->position = *arg0;
            output->action = 6;
            output->destination = target;
            output->result = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, output->destination, 1, 0);
            output->special = func_0015CBB0(*arg0 >> 8, *arg0 & 0xFF, arg0);
            func_0027B1B0(arg0, arg3);
            return 0;
        }
        if ((range = func_002464F0(func_001DF540(*arg0 >> 8, *arg0 & 0xFF), centerX, centerY)) == 0) {
            output->position = *arg0;
            output->action = 6;
            output->destination = target;
            output->result = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, output->destination, 1, 0);
            output->special = func_0015CBB0(*arg0 >> 8, *arg0 & 0xFF, arg0);
            func_0027B1B0(arg0, arg3);
            return 0;
        }
        if (func_001E2100(*arg0 >> 8, *arg0 & 0xFF, 4) != 0) {
            if ((func_001E0700(*arg0 >> 8, *arg0 & 0xFF) >> 5) == 1 ||
                (func_001E0700(*arg0 >> 8, *arg0 & 0xFF) >> 5) == 5) {
                func_001E1E70(*arg0 >> 8, *arg0 & 0xFF, 0, 1);
                output->position = *arg0;
                output->action = 0xE;
                return 0;
            }
        }
        best = 0xFF;
        bestScore = 0xFFFF;
        minX = (u8)func_00250860(0, centerX - (range & 0xF));
        limit = centerX + (range & 0xF);
        endX = limit >= 7 ? 6 : limit;
        minY = (u8)func_00250860(0, centerY - (range & 0xF));
        limit = centerY + (range & 0xF);
        if (limit >= 7) {
            limit = 6;
        }
        maxY = (u8)limit;
        if ((*arg0 & 0xFF) == 0) {
            extra = (u8)func_0027BBC0(*arg0 >> 8, *arg0 & 0xFF, 0);
        } else {
            extra = 0;
        }
        for (x = minX; x <= endX; x++) {
            y = minY;
            packedY = y << 8;
            for (; y <= maxY; packedY += 0x100, y++) {
                if ((((x < centerX ? centerX : x) - (centerX < x ? centerX : x)) +
                    ((y < centerY ? centerY : y) - (centerY < y ? centerY : y))) > (range & 0xF)) {
                    continue;
                }
                if (func_00279C40(*arg0 >> 8, *arg0 & 0xFF, centerX, centerY, x, y, arg0, extra) == 1) {
                    if (func_0027BE10(*arg0 >> 8, *arg0 & 0xFF, x, y, 0) == 0 || (u8)*arg0 == 0) {
                        candidateScore = func_00276CC0(x, y, *arg0, 3, (u16)func_0015D120(arg1), 0);
                        if (candidateScore < bestScore) {
                            bestScore = candidateScore;
                            best = packedY | x;
                        } else if (candidateScore == bestScore && func_001E36E0(x, y) == 0 &&
                            func_001E36E0(best & 0xFF, best >> 8) != 0) {
                            bestScore = candidateScore;
                            best = packedY | x;
                        }
                    }
                }
            }
        }
        if (best != 0xFF) {
            output->position = *arg0;
            output->action = 6;
            output->destination = best;
            if (best == target) {
                output->result = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, output->destination, 1, 0);
            } else {
                output->result = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, output->destination, 0, 0);
            }
            output->special = func_0015CBB0(*arg0 >> 8, *arg0 & 0xFF, arg0);
        } else {
            output->position = *arg0;
            output->action = 6;
            output->destination = target;
            output->result = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, output->destination, 1, 0);
            output->special = func_0015CBB0(*arg0 >> 8, *arg0 & 0xFF, arg0);
        }
        func_0027B1B0(arg0, arg3);
        return 0;
    }
}

typedef struct Input_0015B820 {
    u16 pos;
    u8 pad2[6];
    u32 target;
} Input_0015B820;

typedef struct Output_0015B820 {
    u16 pos;
    u8 command;
    u8 pad3;
    u16 target;
    u8 pad6[6];
    s32 special;
    u8 result;
} Output_0015B820;

typedef struct Cell_0015B820 {
    u8 x : 4;
    u8 y : 4;
} Cell_0015B820;

s32 func_002464F0(s32, s32, s32);
s32 func_00276CC0(s32, s32, s32, s32, s32, s32);

static inline u32 target_0015B820(Input_0015B820 *input, u8 mode) {
    if (mode == 1) {
        return (u16)(input->target >> 16);
    }
    return (u16)input->target;
}

s32 func_0015B820(void *arg0, s32 arg1, void *arg2, u8 arg3) {
    extern s32 func_0015CBB0();
    extern void func_0027A090();
    s32 source;
    s32 count;
    s32 source_y;
    s32 source_x;
    s32 special;
    u8 mode;
    Cell_0015B820 cells[12];
    s32 target;
    s32 pos;
    s32 target_y;
    s32 target_x;
    Cell_0015B820 *candidate;
    s32 initial_special;
    s32 i;
    s32 best_cost;
    s32 best;
    s32 cost;
    s32 unit;
    s32 init_i;
    u32 target_low;
    u32 target_high;
    Cell_0015B820 *cell;
    Input_0015B820 *input = arg0;
    Output_0015B820 *output = arg2;

    mode = arg3;
    target_low = target_0015B820(input, arg3);
    target_high = target_0015B820(input, arg3);
    if (func_001DF540(target_high >> 8, target_low & 0xFF) == 0) {
        func_0027B1B0(input, 1);
        return -1;
    }

    initial_special = func_0015CBB0(input->pos >> 8, input->pos & 0xFF, input);
    source = func_001E1090(input->pos >> 8, input->pos & 0xFF);
    target_low = target_0015B820(input, arg3);
    target_high = target_0015B820(input, arg3);
    target = func_001E1090(target_high >> 8, target_low & 0xFF);
    cell = cells;
    init_i = 0;
    do {
        init_i++;
        cell->x = cell->y = 0xF;
        cell++;
    } while (init_i < 12);

    unit = func_001DF540(input->pos >> 8, input->pos & 0xFF);
    source_x = source & 0xFF;
    source_y = source >> 8;
    if (func_002464F0(unit, source_x, source_y) == 0) {
        output->pos = input->pos;
        output->command = 6;
        output->target = source;
        cost = func_00276CC0(source_x, source_y, arg1, 3, 1,
                            (u8)func_0015D120(arg1));
        if (cost >= func_001E0290(input->pos >> 8, input->pos & 0xFF, 0)) {
            output->result = func_0027E360(input->pos >> 8, input->pos & 0xFF,
                                         output->target, 1, 0);
        } else {
            output->result = func_0027E360(input->pos >> 8, input->pos & 0xFF,
                                         output->target, 0, 0);
        }
        func_0027B1B0(input, mode);
        return 0;
    } else {
        u16 limit;
        pos = input->pos;
        limit = func_0015D120(arg1);
        func_0027A090(pos >> 8, pos & 0xFF, cells, source_x, source_y,
                     target_x = target & 0xFF, target_y = target >> 8,
                     target_0015B820(input, arg3), 0, 30, limit);
        count = func_0027AFC0((u8 *)cells);
        best = 0xFF;
        if (count > 0) {
            special = 0;
            best_cost = 0xFFFF;
            for (i = 0; i < count; i++) {
                if (func_0015CF30(input->pos >> 8, input->pos & 0xFF,
                                 source_x, source_y, target_x, target_y) == 1) {
                    Cell_0015B820 *chosen = &cells[i];
                    best = i;
                    special = 1;
                    i = count;
                    chosen->x = target_x;
                    chosen->y = target_y;
                } else {
                    u8 limit;
                    candidate = &cells[i];
                    limit = func_0015D120(arg1);
                    cost = func_00276CC0(candidate->x, candidate->y, arg1, 3, 1, limit);
                    if (cost < best_cost) {
                        best_cost = cost;
                        best = i;
                    } else if (cost == best_cost) {
                        Cell_0015B820 *chosen = &cells[best];
                        s32 old_y_min;
                        s32 old_y_max;
                        s32 old_x_min;
                        s32 old_x_max;
                        s32 new_y_min;
                        s32 new_y_max;
                        s32 new_x_min;
                        s32 new_x_max;

                        old_y_min = chosen->y < target_y ? chosen->y : target_y;
                        old_y_max = target_y < chosen->y ? chosen->y : target_y;
                        old_x_min = chosen->x < target_x ? chosen->x : target_x;
                        old_x_max = target_x < chosen->x ? chosen->x : target_x;
                        new_y_min = candidate->y < target_y ? candidate->y : target_y;
                        new_y_max = target_y < candidate->y ? candidate->y : target_y;
                        new_x_min = candidate->x < target_x ? candidate->x : target_x;
                        new_x_max = target_x < candidate->x ? candidate->x : target_x;
                        if ((new_x_max - new_x_min) + (new_y_max - new_y_min) <
                            (old_x_max - old_x_min) + (old_y_max - old_y_min)) {
                            best_cost = cost;
                            best = i;
                        }
                    }
                }
            }
        } else {
            output->pos = input->pos;
            output->command = 6;
            output->target = source;
            output->special = initial_special;
            output->result = func_0027E360(input->pos >> 8, input->pos & 0xFF,
                                         output->target, 0, 0);
            func_0027B1B0(input, mode);
            return 0;
        }
        if (best != 0xFF) {
            output->pos = input->pos;
            output->command = 6;
            output->target = (cells[best].y << 8) | cells[best].x;
            output->special = special;
            output->result = func_0027E360(input->pos >> 8, input->pos & 0xFF,
                                         output->target, 0, 0);
        } else {
            output->pos = input->pos;
            output->command = 6;
            output->target = source;
            output->special = special;
            output->result = func_0027E360(input->pos >> 8, input->pos & 0xFF,
                                         output->target, 0, 0);
            func_0027B1B0(input, mode);
            return 0;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_014", func_0015BE00);

typedef struct {
    u16 position;
    u8 pad2[6];
    union {
        u32 both;
        u16 half[2];
    } target;
} Source_0015C670;

typedef struct {
    u16 position;
    u8 action;
    u8 pad3;
    u16 target;
    u8 pad6[10];
    s8 result;
} Action_0015C670;

typedef struct {
    u8 x : 4;
    u8 y : 4;
} Point_0015C670;

#define MIN_0015C670(a, b) ((a) < (b) ? (a) : (b))
#define MAX_0015C670(a, b) ((b) < (a) ? (a) : (b))

s32 func_002464F0(s32, s32, s32);
s32 func_00276CC0(s32, s32, s32, s32, s32, s32);

static inline u32 target_0015C670(void *arg0, s32 mode) {
    Source_0015C670 *source = arg0;
    if (mode == 1) {
        return (u16)(source->target.both >> 16);
    }
    return source->target.half[0];
}

static inline void fill_0015C670(void *arg0, void *arg2, s32 target, s32 flag) {
    Source_0015C670 *source = arg0;
    Action_0015C670 *action = arg2;
    action->position = source->position;
    action->action = 6;
    action->target = target;
    action->result = func_0027E360(source->position >> 8,
        source->position & 0xFF, action->target, flag, 0);
}

s32 func_0015C670(void *arg0, s32 arg1, void *arg2, s32 arg3) {
    s32 start;
    s32 count;
    s32 startY;
    Point_0015C670 points[16];
    s32 bestScore;
    Point_0015C670 *p;
    s32 targetY;
    s32 targetX;
    s32 i;
    s32 bestIndex;
    s32 mode;
    s32 target;
    s32 startX;
    u32 xPosition;
    u32 yPosition;
    Source_0015C670 *source = arg0;
    Action_0015C670 *action = arg2;
    extern void func_0027A090();

    mode = arg3 & 0xFF;
    xPosition = target_0015C670(arg0, mode);
    yPosition = target_0015C670(arg0, mode);
    if (func_001DF540(yPosition >> 8, xPosition & 0xFF) == 0) {
        func_0027B1B0(arg0, 1);
        return -1;
    }
    start = func_001E1090(source->position >> 8, source->position & 0xFF);
    xPosition = target_0015C670(arg0, mode);
    yPosition = target_0015C670(arg0, mode);
    target = func_001E1090(yPosition >> 8, xPosition & 0xFF);
    if (target_0015C670(arg0, mode) == 0xFFFF) {
        fill_0015C670(arg0, arg2, start, 1);
        return 0;
    } else {
        s32 unit = func_001DF540(source->position >> 8, source->position & 0xFF);
        startX = start & 0xFF;
        startY = start >> 8;
        if (func_002464F0(unit, startX, startY) == 0 ||
                func_0027BBC0(source->position >> 8, source->position & 0xFF, 0) == 1) {
            fill_0015C670(arg0, arg2, start, 1);
            return 0;
        } else {
            p = points;
            {
                s32 n = 0;
                Point_0015C670 *q = p;
                do {
                    q->x = q->y = 0xF;
                    q++;
                    n++;
                } while (n < 12);
            }
            {
                s32 position = source->position;
                u16 card = (u16)func_0015D120(arg1);
                func_0027A090(position >> 8, position & 0xFF, points,
                    startX, startY, targetX = target & 0xFF,
                    targetY = target >> 8, target_0015C670(arg0, mode),
                    0, 30, card);
            }
            count = func_0027AFC0((u8 *)points);
            bestIndex = 0xFF;
            if (count > 0) {
                bestScore = 0;
                for (i = 0; i < count; i++, p++) {
                    if (func_001E36E0(p->x, p->y) == 0) {
                        s32 score = func_00276CC0(p->x, p->y, arg1, 3, 1,
                            func_0015D120(arg1) & 0xFF);
                        if (bestScore < score) {
                            bestScore = score;
                            bestIndex = i;
                        } else if (score == bestScore) {
                            if (MAX_0015C670(p->x, targetX) - MIN_0015C670(p->x, targetX)
                                    + (MAX_0015C670(p->y, targetY) - MIN_0015C670(p->y, targetY))
                                    < MAX_0015C670(points[bestIndex].x, targetX) - MIN_0015C670(points[bestIndex].x, targetX)
                                    + (MAX_0015C670(points[bestIndex].y, targetY) - MIN_0015C670(points[bestIndex].y, targetY))) {
                                bestScore = score;
                                bestIndex = i;
                            }
                        }
                    }
                }
            } else {
                fill_0015C670(arg0, arg2, start, 1);
                return 0;
            }
            if (bestIndex != 0xFF) {
                action->position = source->position;
                action->action = 6;
                action->target = (points[bestIndex].y << 8) | points[bestIndex].x;
                action->result = func_0027E360(source->position >> 8,
                    source->position & 0xFF, action->target, 0, 0);
            } else {
                fill_0015C670(arg0, arg2, start, 1);
                return 0;
            }
        }
    }
    return 0;
}

s32 func_0015CBB0(s32 arg0, s32 arg1) {
    s32 kind;
    s32 pos;
    s32 slot;
    u32 *card;

    kind = func_001E1030();
    pos = func_001E1090(arg0, arg1);
    slot = func_00250360(arg0, arg1);
    card = func_001E0B70(arg0, arg1, 0);
    if (func_001E2100(arg0, arg1, 4) != 0) {
        return 0;
    }
    switch (func_001E0700(arg0, arg1) >> 5) {
    case 0:
        switch (kind) {
        case 0xE0:
            if (func_001DE5C0(slot) < 2) {
                return 1;
            }
            break;
        case 0x28C:
            if (func_0024E910(func_0024CA40(pos & 0xFF, pos >> 8, slot, 1, 0x34, 0x14)) > 1) {
                return 2;
            }
            if (func_0024E910(func_0024CA40(pos & 0xFF, pos >> 8, slot, 2, 0x34, 0x14)) > 5) {
                return 1;
            }
            break;
        case 0x28F:
            if (func_0024E910(func_0024CA40(0, 0, arg0, 2, 0x34, 0xE)) > 5) {
                return 1;
            }
            break;
        }
        return 2;
    case 5:
        if (func_0027D830(arg0, arg1, 0, 0, 6, 0) == 5) {
            return 2;
        }
        if (func_0015D030(func_00250360(arg0, arg1), kind) == 1 &&
            func_001E22B0(pos & 0xFF, pos >> 8) != 9) {
            return 1;
        }
        break;
    case 1:
        if (func_0027D830(arg0, arg1, 0, 0, 6, 0) == 5) {
            return 2;
        }
        if (card == NULL) {
            return 2;
        }
        switch (*card >> 8) {
        case 0x18:
            if (func_0024E910(func_0024CA40(0, 0, arg0, 2, 0x34, 0xE)) > 5) {
                return 1;
            }
            break;
        case 0x12:
            if (func_0024E910(func_0024CA40(pos & 0xFF, pos >> 8, slot, 1, 0x1D, 0x1D)) > 0) {
                return 2;
            }
            if (func_0024E910(func_0024CA40(0, 0, slot, 1, 0x13, 0xE)) > 2) {
                return 1;
            }
            break;
        }
        break;
    default:
        return 2;
    }
    return 2;
}

static inline s32 max_0015CF30(s32 a, s32 b) {
    if (b < a) {
        return a;
    }
    return b;
}

s32 func_0015CF30(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 minY;
    s32 minX;

    minY = (arg3 < arg5) ? arg3 : arg5;
    arg5 = max_0015CF30(arg3, arg5);
    minX = (arg2 < arg4) ? arg2 : arg4;
    arg4 = max_0015CF30(arg2, arg4);

    if (((arg4 - minX) + (arg5 - minY)) != 2) {
        return 0;
    }
    if (func_001DF540(arg0, arg1) == 0) {
        return 0;
    }
    if (func_001E2100(arg0, arg1, 0) == 0) {
        return (func_0024DF00(func_001E22B0(arg2, arg3), arg0, arg1) != 1) ? 0 : 1;
    }
    return 0;
}

s32 func_0015D030(s32 arg0, s32 arg1) {
    s32 data[4];
    s32 index;
    s32 mask;
    s32 low;
    s32 high;
    s32 value;

    func_00254C90(data, *(s32 *)((u8 *)func_0026FC90(arg1, 0) + 4));
    if ((mask = func_00254890(data, arg0)) < 0) {
        return 0;
    }
    for (index = 0; index < func_0024E910(mask); index++) {
        value = func_0024EC50(mask, index);
        high = value >> 8;
        low = value & 0xFF;
        value = func_001E1090(high, low);
        if (func_002509E0(high, low, value & 0xFF, value >> 8) >= 0) {
            return 0;
        }
    }
    return 1;
}

s32 func_0015D120(s32 arg0) {
    if (func_001DF470(arg0) > 0x4B0) {
        if (func_001E0150(arg0) >= 5) {
            return 0x2EE;
        } else {
            return 0x5DC;
        }
    } else {
        return 0x7D0;
    }
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
} Req_0015D180;

typedef struct {
    u8 pad0[0x160];
    u16 list[32];    /* 0x160 */
    u8 idx : 5;      /* 0x1A0 */
    u8 pad1A0 : 3;
    u8 pad1A1;
    u16 count;       /* 0x1A2 */
} Work_0015D180;

s32 func_00158C80(void *, void *, s32);
s32 func_00276290(void *, void *, s32);

s32 func_0015D180(s32 arg0, void *arg1) {
    Req_0015D180 req;
    Work_0015D180 *w;
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
        if (func_00158C80(w, &req, arg0) == 0) {
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

INCLUDE_ASM("asm/nonmatchings/main_014", func_0015D350);

s32 func_0015D8E0(void *arg0) {
    u16 card;
    s32 low;
    s32 temp_s0;
    s32 type;

    card = *(u16 *)arg0;
    func_001E1090(card >> 8, card & 0xFF);
    card = *(u16 *)arg0;
    temp_s0 = func_00250360(card >> 8, card & 0xFF);
    card = *(u16 *)arg0;
    if (func_001DF540(card >> 8, card & 0xFF) != 0) {
        card = *(u16 *)arg0;
        if (func_001E2100(card >> 8, card & 0xFF, 0) == 0) {
            card = *(u16 *)arg0;
            if (card != 0xFFFF) {
                low = card & 0xFF;
                if (low == 0) {
                    if (*(s32 *)((u8 *)arg0 + 8) == -1) {
                        if (func_0027BBC0(card >> 8, low, 0) == 1) {
                            if (func_001DE6D0(*(u16 *)arg0 >> 8) == 1) {
                                *(s16 *)((u8 *)arg0 + 4) = 0x50A;
                            } else {
                                *(s16 *)((u8 *)arg0 + 4) = 0x5FF;
                            }
                        } else {
                            if (func_001DE6D0(*(u16 *)arg0 >> 8) == 1) {
                                *(s16 *)((u8 *)arg0 + 4) = 0xA05;
                            } else {
                                *(s16 *)((u8 *)arg0 + 4) = 0x5FF;
                            }
                        }
                    }
                } else {
                    type = func_001E0700(card >> 8, low) >> 5;
                    switch (type) {
                    case 0:
                        card = *(u16 *)arg0;
                        if (func_002507D0(card >> 8, card & 0xFF) == 1) {
                            func_0015E950(arg0);
                        } else {
                            func_0015DED0(arg0);
                        }
                        break;
                    case 2:
                        func_0027CA50(arg0, 5, 0, func_00162580(temp_s0) & 0xFF);
                        break;
                    case 1:
                    case 3:
                    case 4:
                        func_0015EF40(arg0);
                        break;
                    default:
                        *(s16 *)((u8 *)arg0 + 4) = 0x5FF;
                        break;
                    }
                }
                return 1;
            }
        }
    }
    return 0;
}

s32 func_0015DAF0(u16 *arg0, s32 arg1, s32 arg2) {
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
    func_0015D8E0(arg0 + idx * 8);
    if (((arg0[idx * 8 + 2] >> 8) & 0xFF) == 10) {
        if (func_001DE6D0(arg1) == 1 && func_0015F300(pos, arg1, arg2) >= 0) {
            return pos | 0x10000;
        }
        if (func_0027B9B0(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (func_001E2100(arg1, 0, 0) == 0) {
        if (func_0027B9B0(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (func_001DE6D0(arg1) == 1 && func_0015F300(pos, arg1, arg2) >= 0) {
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

typedef struct Action_0015DED0 {
    u16 location;
    u16 unk2;
    s16 state;
    u16 unk6;
    union {
        u32 value;
        u16 low;
    } data;
} Action_0015DED0;


void func_0015DED0(void *arg0) {
    s32 other;
    s32 result;
    Action_0015DED0 *action = arg0;

    if (func_001DF540(action->location >> 8, action->location & 0xFF) != 0) {
        other = (func_0024DE70(action->location >> 8, action->location & 0xFF) == 0 ? 1 : 0) << 8;
        func_001E1090(action->location >> 8, action->location & 0xFF);
        func_001E1090(other >> 8, other & 0xFF);
        func_001DF540(action->location >> 8, action->location & 0xFF);
        if (func_001E0290(action->location >> 8, action->location & 0xFF, 0) >= 2500) {
            func_0015E030(arg0);
            return;
        }
        if (func_0015E440(action->location >> 8, action->location & 0xFF, 1) == 1) {
            func_0015E520(arg0, 1);
            return;
        }
        result = func_0015E2E0(action->location >> 8, action->location & 0xFF);
        if (result >= 0) {
            action->state = 0x6FF;
            action->data.value = (result << 16) | action->data.low;
            return;
        }
        if (func_0015E440(action->location >> 8, action->location & 0xFF, 2) == 1) {
            func_0015E520(arg0, 2);
            return;
        }
        func_0015E030(arg0);
    }
}

typedef struct Command_0015E030 {
    u16 position;
    u16 pad2;
    u16 action;
    u16 pad6;
    union {
        u32 value;
        struct {
            u16 low;
            u16 high;
        } halves;
    } data;
} Command_0015E030;

typedef struct Entry_0015E030 {
    u16 position;
    u8 state;
    u8 pad;
} Entry_0015E030;

void func_0015E030(void *arg0) {
    u8 scratch[0x70];
    Entry_0015E030 entries[23];
    s16 count;
    s16 otherCount;
    Command_0015E030 *command = arg0;
    s32 position;
    s32 destination;
    s32 side;
    s32 card;
    s32 destinationColumn;
    s32 destinationRow;
    s32 row;
    s32 column;
    s32 otherPosition;
    s32 otherRow;
    s32 attempt;
    s32 i;
    Entry_0015E030 *entry;

    extern void func_0027E770();
    extern s32 func_0027B200();
    extern s32 func_0015E8F0();

    if (func_001DF540(command->position >> 8, command->position & 0xFF) == 0) {
        return;
    }

    side = func_0024DE70(command->position >> 8, command->position & 0xFF);
    destination = (side == 0 ? 1 : 0) << 8;
    position = func_001E1090(command->position >> 8, command->position & 0xFF);
    destinationRow = destination >> 8;
    destinationColumn = destination & 0xFF;
    otherPosition = func_001E1090(destinationRow, destinationColumn);
    card = func_001DF540(command->position >> 8, command->position & 0xFF);
    func_0027E770(scratch);

    entry = entries;
    i = 0;
    do {
        i++;
        entry->position = 0xFFFF;
        entry->state = 0xFF;
        entry++;
    } while (i < 22);

    if (func_0027B200(command->position >> 8, command->position & 0xFF,
                     column = position & 0xFF, row = position >> 8,
                     destinationRow, destinationColumn,
                     otherPosition & 0xFF, otherRow = otherPosition >> 8, 5) > 0) {
        command->action = 0x2FF;
        command->data.value = (destination << 16) | command->data.halves.low;
        return;
    }

    attempt = 1;
    otherCount = 0;
    count = 0;
    while (1) {
        switch (func_0015E8F0(command, 0, card, column, row,
                             side == 0 ? 1 : 0, (u8) attempt,
                             func_00162580(side), entries, 0,
                             &count, &otherCount, 5, scratch)) {
        case 3:
            command->action = 0x6FF;
            command->data.value = (position << 16) | command->data.halves.low;
            return;
        case 2:
            command->action = 0x3FF;
            command->data.value = (position << 16) | command->data.halves.low;
            return;
        case 1:
            return;
        case 0:
            command->action = 0x3FF;
            command->data.value = (position << 16) | command->data.halves.low;
            return;
        }
        attempt++;
        if (attempt > 5) {
            break;
        }
    }

    command->action = 0x6FF;
    if (((row <= 3) && (otherRow <= 3)) || ((row > 3) && (otherRow > 3))) {
        command->data.value = (otherPosition << 16) | command->data.halves.low;
    } else {
        command->data.value = (((position & 0xFF) | 0x300) << 16) |
                              command->data.halves.low;
    }
}

s32 func_0015E2E0(s32 arg0, s32 arg1) {
    s32 temp_s0;
    s32 temp_s2;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;

    temp_v0 = func_00250360(arg0, arg1);
    if (func_0024CA40(0, 0, temp_v0, 1, 0x033B001C, 14) != 0) {
        temp_v0_2 = func_001E3790(0, 5);
        if (temp_v0_2 >= 0) {
            if (temp_v0_2 == ((arg0 << 8) | arg1)) {
                return 0x500;
            }
            temp_s2 = func_00250360(temp_v0_2 >> 8, temp_v0_2 & 0xFF);
            if (temp_s2 != func_00250360(arg0, arg1)) {
                return 0x500;
            }
        } else {
            return 0x500;
        }
    }
    if (func_0024CA40(0, 0, temp_v0, 1, 0x02ED001C, 14) != 0) {
        temp_v0_3 = func_001E3790(6, 3);
        if (temp_v0_3 >= 0) {
            if (temp_v0_3 == ((arg0 << 8) | arg1)) {
                return 0x306;
            }
            temp_s0 = func_00250360(temp_v0_3 >> 8, temp_v0_3 & 0xFF);
            if (temp_s0 != func_00250360(arg0, arg1)) {
                return 0x306;
            }
        } else {
            return 0x306;
        }
    }
    return -1;
}

s32 func_0015E440(s32 arg0, s32 arg1, s32 arg2) {
    s32 otherType;
    s32 card;
    s32 i;
    s32 mode;
    s32 key;

    if ((arg2 & 0xFF) == 1) {
        mode = 3;
    } else {
        mode = 4;
    }
    key = (arg0 << 8) | arg1;
    i = 1;
    do {
        card = func_001E3790(i, mode);
        if (card != 0) {
            if (card == key) {
                return 1;
            }
            otherType = func_00250360(card >> 8, card & 0xFF);
            if (otherType == func_00250360(arg0, arg1)) {
                return 0;
            }
        }
        i++;
        if (i > 5) {
            return 1;
        }
    } while (1);
}

typedef struct {
    u16 position;
    u8 flag;
    u8 pad;
} Slot_0015E520;

void func_0015E520(void *arg0, s32 arg1) {
    u8 work[112];
    Slot_0015E520 slots[22];
    s16 b;
    s16 a;
    s32 i;
    s32 target;
    s32 player;
    s32 enemy;
    s32 position;
    s32 enemyPos;
    s32 owner;
    u16 *record = arg0;
    extern s32 func_0027B200();
    extern s32 func_0015E8F0();
    extern void func_0027E770();

    if ((arg1 & 0xFF) == 1) {
        target = 3;
    } else {
        target = 4;
    }
    func_001E1090((s32) record[0] >> 8, record[0] & 0xFF);
    if (func_001DF540((s32) record[0] >> 8, record[0] & 0xFF) != 0) {
        player = func_0024DE70((s32) record[0] >> 8, record[0] & 0xFF);
        enemy = (player == 0 ? 1 : 0) << 8;
        position = func_001E1090((s32) record[0] >> 8, record[0] & 0xFF);
        enemyPos = func_001E1090(enemy >> 8, enemy & 0xFF);
        owner = func_001DF540((s32) record[0] >> 8, record[0] & 0xFF);
        func_0027E770(work);
        for (i = 0; i < 22; i++) {
            slots[i].position = 0xFFFF;
            slots[i].flag = 0xFF;
        }
        if (func_0027B200((s32) record[0] >> 8, record[0] & 0xFF, position & 0xFF, position >> 8,
                          enemy >> 8, enemy & 0xFF, enemyPos & 0xFF, enemyPos >> 8, 2) > 0) {
            record[2] = 0x2FF;
            *(u32 *) (record + 4) = (enemy << 16) | record[4];
            return;
        }
        a = 0;
        b = 0;
        i = 1;
        while (1) {
            switch (func_0015E8F0(record, 0, owner, position & 0xFF, position >> 8,
                                  func_0024DE70((s32) record[0] >> 8, record[0] & 0xFF) == 0 ? 1 : 0, (u8) i,
                                  func_00162580(player), slots, 0, &b, &a, 2, work)) {
            case 3:
                record[2] = 0x6FF;
                *(u32 *) (record + 4) = (position << 16) | record[4];
                return;
            case 2:
                record[2] = 0x3FF;
                *(u32 *) (record + 4) = (position << 16) | record[4];
                return;
            case 1:
                return;
            case 0:
                record[2] = 0x3FF;
                *(u32 *) (record + 4) = (position << 16) | record[4];
                return;
            }
            i++;
            if (i > 2) {
                break;
            }
        }
        if ((position >> 8) == target) {
            switch ((u8) (record[2] >> 8)) {
            case 16:
                if ((position & 0xFF) > 1) {
                    *(u32 *) (record + 4) = ((position >> 8) << 24) | record[4];
                } else {
                    record[2] = 0xFFF;
                    *(u32 *) (record + 4) = ((((position >> 8) << 8) | 5) << 16) | record[4];
                }
                break;
            case 15:
                if ((position & 0xFF) < 5) {
                    *(u32 *) (record + 4) = ((((position >> 8) << 8) | 5) << 16) | record[4];
                } else {
                    record[2] = 0x10FF;
                    *(u32 *) (record + 4) = ((((position >> 8) << 8) | 1) << 16) | record[4];
                }
                break;
            default:
                if (func_0019A5C8() % 2 == 0) {
                    record[2] = 0x10FF;
                    *(u32 *) (record + 4) = ((((position >> 8) << 8) | 1) << 16) | record[4];
                } else {
                    record[2] = 0xFFF;
                    *(u32 *) (record + 4) = ((((position >> 8) << 8) | 5) << 16) | record[4];
                }
                break;
            }
            return;
        }
        record[2] = 0x6FF;
        *(u32 *) (record + 4) = record[4] | (((target << 8) | (position & 0xFF)) << 16);
    }
}

void func_0015E8F0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28) {
    func_0027DE20(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
                  arg_sp0, arg_sp8, arg_sp10, arg_sp18, arg_sp20,
                  0, 2500, arg_sp28);
}

typedef struct Entry_0015E950 {
    u16 position;
    u8 kind;
    u8 pad;
} Entry_0015E950;

s32 func_00277160(s32, s32, s32, void *, s32, s32, s32, s32, s32, s32, u16);

void func_0015E950(void *arg0) {
    extern s32 func_001E1030();
    extern s32 func_002770E0();
    extern void func_0027E770();
    s32 destination;
    u8 buffer[112];
    Entry_0015E950 entries[22];
    u16 outputA;
    u16 outputB;
    u16 count;
    s32 checkOwner;
    s32 retryX;
    s32 value;
    s32 owner;
    s32 card;
    s32 cursor;
    s32 index;
    s32 retryY;
    s32 attempt;
    s32 x;
    s32 y;
    s32 position;
    s32 other;
    s32 same;
    s32 i;
    s32 result;
    Entry_0015E950 *entry;
    u16 location;

    location = *(u16 *)arg0;
    owner = func_00250360(location >> 8, location & 0xFF);
    location = *(u16 *)arg0;
    value = func_001E1030(location >> 8, location & 0xFF);
    location = *(u16 *)arg0;
    card = func_001DF540(location >> 8, location & 0xFF);
    location = *(u16 *)arg0;
    destination = func_001E1090(location >> 8, location & 0xFF);
    entry = entries;
    count = 0;
    outputB = 0;
    outputA = 0;
    i = 0;
    do {
        i++;
        entry->position = 0xFFFF;
        entry->kind = 0xFF;
        entry++;
    } while (i < 22);
    func_0027E770(buffer);
    cursor = 0;
    switch (value) {
    case 0x2B:
        location = *(u16 *)arg0;
        if (func_001E2100(location >> 8, location & 0xFF, 4) != 0) {
            break;
        }
        *(u16 *)((u8 *)arg0 + 4) = 0xCFF;
        *(u32 *)((u8 *)arg0 + 8) = (destination << 16) | *(u16 *)((u8 *)arg0 + 8);
        return;
    case 0x57:
        func_0015E030(arg0);
        return;
    case 0x129:
        location = *(u16 *)arg0;
        index = 1;
        y = location & 0xFF;
        x = location >> 8;
        position = (x << 8) | y;
        while (1) {
            other = func_001E3790(index, 3);
            if (other != 0) {
                if (other == position) {
                    same = 1;
                    break;
                }
                checkOwner = func_00250360(other >> 8, other & 0xFF);
                if (checkOwner == func_00250360(x, y)) {
                    same = 0;
                    break;
                }
            }
            index++;
            if (index > 5) {
                same = 1;
                break;
            }
        }
        if (same == 1) {
            func_0015E520(arg0, 1);
            return;
        }
        retryX = destination >> 8;
        retryY = destination & 0xFF;
        attempt = 1;
        while (1) {
            result = func_00162580(owner);
            cursor = func_002770E0(cursor, card, retryY, retryX, owner == 0 ? 1 : 0, (u8)attempt, 0, result,
                                  entries, &count, &outputA, &outputB, buffer);
            result = func_00277160(card, retryY, retryX, entries, 2, 0x34, 0, 2, 0,
                                  func_00162580(owner), count);
            if (result >= 0) {
                *(u16 *)((u8 *)arg0 + 4) = 0x2FF;
                *(u32 *)((u8 *)arg0 + 8) = (result << 16) | *(u16 *)((u8 *)arg0 + 8);
                return;
            }
            attempt++;
            if (attempt > 2) {
                break;
            }
        }
        location = *(u16 *)arg0;
        func_0015EC60(location >> 8, location & 0xFF, arg0);
        return;
    }
    func_0015DED0(arg0);
}

typedef struct {
    u32 field0;
    u16 field4;
    u16 field6;
    union {
        u32 word;
        struct {
            u32 lower : 16;
            u32 upper : 16;
        } bits;
    } field8;
} Item_0015EC60;

s32 func_0015EE40(void);

static inline void set_index_0015EC60(void *arg, s32 index) {
    Item_0015EC60 *item = arg;

    item->field4 = 0x3FF;
    item->field8.word = (index << 16) | item->field8.bits.lower;
}

void func_0015EC60(s32 arg0, s32 arg1, void *arg2) {
    Item_0015EC60 *item = arg2;
    s32 index;
    s32 next;

    func_00250360(arg0, arg1);
    index = func_001E1090(arg0, arg1);
    if (func_0015ED30(index & 0xFF, index >> 8) == 1) {
        set_index_0015EC60(item, index);
    } else {
        set_index_0015EC60(item, index);
    }
    next = func_0015EE40();
    if (next >= 0) {
        set_index_0015EC60(item, next);
    } else {
        func_0015DED0(item);
    }
}

s32 func_0015ED30(s32 arg0, s32 arg1) {
    s32 var_s0;

    var_s0 = 0;
loop_1:
    if (((arg1 << 8) | arg0) == func_0015ED90(var_s0)) {
        return 1;
    }
    var_s0 += 1;
    if (var_s0 >= 4) {
        return 0;
    }
    goto loop_1;
}

s32 func_0015ED90(s32 arg0) {
    extern s32 func_001604A0();
    s32 temp;

    temp = func_001DE540();
    switch (arg0) {
    case 0:
        return func_001604A0(temp, 0);
    case 1:
        return func_001604A0(temp, 3);
    case 2:
        return func_001604A0(temp, 4);
    case 3:
        return func_001604A0(temp, 5);
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/main_014", func_0015EE40);

typedef struct {
    u16 id;
    u16 unk2;
    s16 action;
    u16 unk6;
    u32 data;
} Command_0015EF40;


static inline s32 check_0015EF40(u16 source, s32 mode) {
    s32 id;
    s32 low;
    s32 high;
    s32 i;
    s32 other_card;
    s32 other;

    i = 1;
    low = source & 0xFF;
    high = (s32)source >> 8;
    id = (high << 8) | low;
    while (1) {
        other = func_001E3790(i, mode);
        if (other != 0) {
            if (other == id) {
                return 1;
            }
            other_card = func_00250360(other >> 8, other & 0xFF);
            if (other_card == func_00250360(high, low)) {
                return 0;
            }
        }
        i++;
        if (i > 5) {
            break;
        }
    }
    return 1;
}

void func_0015EF40(void *arg0) {
    extern s32 func_001E1030();
    Command_0015EF40 *cmd = arg0;
    s32 flags;
    s32 card_id;
    s32 card;
    u32 *effect;
    s32 position;
    s32 result;

    flags = func_001E0700((s32)cmd->id >> 8, cmd->id & 0xFF) & 0xFF;
    card_id = func_001E1030((s32)cmd->id >> 8, cmd->id & 0xFF);
    card = func_00250360((s32)cmd->id >> 8, cmd->id & 0xFF);
    effect = func_00250740((s32)cmd->id >> 8, cmd->id & 0xFF, 0);
    position = func_001E1090((s32)cmd->id >> 8, cmd->id & 0xFF);
    if (effect == NULL) {
        cmd->action = 0x5FF;
        return;
    }

    switch ((flags & 0xFF) >> 5) {
    case 1:
        switch (*effect >> 8) {
        case 20:
            cmd->action = 0xCFF;
            return;
        case 4:
            result = func_001625E0(card);
            if (result >= 0) {
                cmd->action = 0x6FF;
                cmd->data = *(u16 *)&cmd->data |
                    ((((position >> 8) << 8) |
                      (func_001E1090(result >> 8, result & 0xFF) & 0xFF)) << 16);
                return;
            }
            cmd->action = 0x5FF;
            return;
        case 37:
            if (card_id == 0x2ED) {
                cmd->action = 0x6FF;
                cmd->data = *(u16 *)&cmd->data | 0x04060000;
                return;
            }
            if (func_0027D720(arg0, 0) == 1) {
                cmd->action = 0xBFF;
                return;
            }
            break;
        case 31:
            if (card_id == 0x2DC) {
                cmd->action = 0xDFF;
                return;
            }
            break;
        }
        break;
    case 3:
    case 4:
        if (card_id == 0x2ED) {
            cmd->action = 0x6FF;
            cmd->data = *(u16 *)&cmd->data | 0x06000000;
            return;
        }
        if (check_0015EF40(cmd->id, 3) == 1) {
            func_0015E520(arg0, 1);
            return;
        }
        result = func_0015E2E0((s32)cmd->id >> 8, cmd->id & 0xFF);
        if (result >= 0) {
            u32 low;
            cmd->action = 0x6FF;
            low = *(u16 *)&cmd->data;
            cmd->data = (result << 16) | low;
            return;
        }
        if (check_0015EF40(cmd->id, 4) == 1) {
            func_0015E520(arg0, 2);
            return;
        }
        if (func_0027D720(arg0, 0) == 1) {
            cmd->action = 0xBFF;
            return;
        }
        break;
    }
    cmd->action = 0x5FF;
}

typedef struct {
    s16 card;
    u8 f2;
    u8 pad3;
    s16 f4;
    u8 pad6[6];
    s32 fC;
} Act_0015F300;

typedef struct {
    u8 pad0[0x3C];
    u16 id;
    u8 pad3E[0x22];
} Card_0015F300;


s32 func_0015F300(s32 arg0, s32 arg1, s32 arg2) {
    extern s32 func_00278890();
    Card_0015F300 buf;
    s32 res;
    s32 type;
    Act_0015F300 *act = (Act_0015F300 *)arg2;
    s32 card;
    s32 r;

    act->card = arg0;
    if (func_001DE6D0(arg1) == 0) {
        return -1;
    }
    if (func_00278890(arg1, 0) == 5 && func_00278890(arg1, 1) == 5) {
        return -1;
    }
    type = func_0015F5E0(arg1, &buf);
    if (type < 0) {
        return -1;
    }
    act->f2 = 10;
    act->fC = 2;
    card = func_001E1090(arg0 >> 8, arg0 & 0xFF);
    if (type == 0) {
        if (func_0015FE50(arg1, (u8 *)act, &buf) >= 0) {
            res = func_00276F10(&buf, card & 0xFF, card >> 8, arg1 == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, func_00162580(arg1));
            if (res < 0) {
                if (func_001E0150(arg1) < 5) {
                    r = func_001604B0(arg1, (u8)type, &buf, res);
                    if (r < 0) {
                        return -1;
                    }
                    act->f4 = r;
                    return 1;
                }
            } else {
                r = func_001604B0(arg1, (u8)type, &buf, res);
                if (r < 0) {
                    return -1;
                }
                act->f4 = r;
                return 1;
            }
        }
    } else {
        res = func_00276F10(&buf, card & 0xFF, card >> 8, arg1 == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, func_00162580(arg1));
    }
    if (type == 2) {
        func_00160270(arg1, act, &buf);
        r = func_001604B0(arg1, (u8)type, &buf, res);
        if (r < 0) {
            return -1;
        }
        act->f4 = r;
        return 1;
    } else if (type == 3) {
        func_0015FA00(arg1, act, &buf);
        r = func_001604B0(arg1, (u8)type, &buf, res);
        if (r < 0) {
            return -1;
        }
        act->f4 = r;
        return 1;
    } else {
        if (func_0015FC50(arg1, (u8 *)act, &buf, buf.id) < 0) {
            return -1;
        }
        r = func_001604B0(arg1, (u8)type, &buf, res);
        if (r < 0) {
            return -1;
        }
        act->f4 = r;
        return 1;
    }
}

s32 func_0015F5E0(s32 arg0, void *arg1) {
    extern s32 func_00278890();
    extern s32 func_001E1580();
    s32 cards[8];
    u8 buffer[32];
    u8 type0;
    u8 type1;
    s32 result;

    type0 = func_00278890(arg0, 0);
    type1 = func_00278890(arg0, 1);
    if (arg1 == NULL) {
        return -1;
    }
    func_0026FD30(arg0, cards);
    if (type0 == 5) {
        if (func_0015FC50(arg0, buffer, arg1, 999) >= 0) {
            return 1;
        } else {
            return -1;
        }
    } else if (type1 == 5) {
        s32 i;
        s32 *p;

        i = 0;
        if (i < func_0026FE20(arg0)) {
            p = cards;
            do {
                if ((func_0026FCE0(*p) >> 5) == 0 &&
                    func_0026FB10(arg0, *p) == 1) {
                    func_001DCD70(arg1, cards[i]);
                    return 0;
                }
                p++;
                i++;
            } while (i < func_0026FE20(arg0));
        }
        return -1;
    }

    if (func_0015FB60(arg0, buffer, arg1, 0x341) >= 0) {
        if (func_00162490(arg0, 0x341) == 1) {
            return 2;
        }
    }
    if (func_0015FB60(arg0, buffer, arg1, 0x355) >= 0) {
        if (func_00162490(arg0, 0x355) == 1) {
            return 2;
        }
    }
    if (func_001625E0(arg0) >= 0) {
        if (func_0015FB60(arg0, buffer, arg1, 0x2BC) >= 0) {
            return 2;
        }
    }
    if (func_001626F0(arg0) >= 0) {
        if (func_0015FB60(arg0, buffer, arg1, 0x2CB) >= 0) {
            return 2;
        }
    }
    if (func_001627D0(arg0) >= 0) {
        if (func_0015FB60(arg0, buffer, arg1, 0x2AD) >= 0) {
            return 2;
        }
    }
    if (func_00162A70(arg0) >= 0) {
        if (func_0015FB60(arg0, buffer, arg1, 0x2B) >= 0) {
            return 2;
        }
    }
    if (func_0015FA00(arg0, buffer, arg1) == 1) {
        return 3;
    }
    {
        s32 i;
        i = 0;
        do {
            if (func_001E1580(arg0, i) != 0 &&
                func_0015FB60(arg0, buffer, arg1, 0x31C) >= 0) {
                return 2;
            }
            i++;
        } while (i < 11);
    }
    {
        s32 i;
        i = 0;
        do {
            if (func_001E1580(arg0, i) != 0 &&
                func_0015FB60(arg0, buffer, arg1, 0x31B) >= 0) {
                return 2;
            }
            i++;
        } while (i < 11);
    }
    {
        s32 *p;
        s32 i;
        i = 0;
        if (i < func_0026FE20(arg0)) {
            p = cards;
            do {
                if ((func_0026FCE0(*p) >> 5) == 0 &&
                    func_0026FB10(arg0, *p) == 1 && *p != 0x129) {
                    func_001DCD70(arg1, cards[i]);
                    return 0;
                }
                p++;
                i++;
            } while (i < func_0026FE20(arg0));
        }
    }
    result = func_0015FC50(arg0, buffer, arg1, 999);
    if (result >= 0) {
        return result;
    }
    return -1;
}

s32 func_0015FA00(s32 arg0, void *arg1, void *arg2) {
    s32 cards[8];
    s32 i;
    s32 found;
    s32 *entry;
    s32 *entry2;
    s32 j;
    s32 found2;
    s32 card;

    func_0026FD30(arg0, cards);
    i = 0;
    found = 0;
    if (0 < func_0026FE20(arg0)) {
        entry = cards;
        do {
            if (*entry == 0x316) {
                found = 1;
                ((u8 *)arg1)[6] = i;
            }
            entry++;
            i++;
        } while (i < func_0026FE20(arg0));
    }
    if (found == 0) {
        return -1;
    }
    j = 0;
    found2 = 0;
    if (0 < func_0026FE20(arg0)) {
        entry2 = cards;
        do {
            card = *entry2;
            if ((card == 0x129) && (func_0026FB10(arg0, card) == 1)) {
                ((u8 *)arg1)[7] = j;
                found2 = 1;
            }
            entry2++;
            j++;
        } while (j < func_0026FE20(arg0));
    }
    if (found2 == 0) {
        return -1;
    }
    func_001DCD70(arg2, 0x129);
    return 1;
}

s32 func_0015FB60(s32 arg0, void *arg1, void *arg2, s32 arg3) {
    s32 entries[8];
    s32 index;
    s32 *entry;

    func_0026FD30(arg0, entries);
    index = 0;
    if (index < func_0026FE20(arg0)) {
        entry = entries;
        do {
            if (((arg3 & 0xFFFF) == *entry) && (func_0026FB10(arg0, *entry) == 1)) {
                *((s8 *)arg1 + 6) = index;
                func_001DCD70(arg2, entries[index]);
                return func_0026FCE0(entries[index]) >> 5;
            }
            entry++;
            index++;
        } while (index < func_0026FE20(arg0));
    }
    return -1;
}

s32 func_0015FC50(s32 arg0, u8 *arg1, void *arg2, s32 arg3) {
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

typedef struct Info_0015FE50 {
    u8 pad00[8];
    u16 x;
    s16 y;
} Info_0015FE50;

typedef struct Sprite_0015FE50 {
    Info_0015FE50 *info;
    u8 pad04[0x34];
    s16 x;
    s16 y;
} Sprite_0015FE50;

u16 *func_00278A90(s32, u16 *, s32, s32, s32, s16 *, s16 *);
s32 func_00278F10(s32, u16 *, s32, s32);

s32 func_0015FE50(s32 arg0, u8 *arg1, void *arg2) {
    u16 *nodes[8];
    s32 entries[7];
    s16 a;
    s16 b;
    s32 i;
    s32 card;
    s32 value;
    s32 best;

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
                    value = func_00278F10(arg0, *node, 0, 0);
                    if (func_0026FB10(arg0, card) == 1) {
                        if (best < value) {
                            func_00160030(arg0, *node, entries);
                            func_00278DD0((u8 *)*node + 2, arg1 + 6);
                            func_001DCD70(arg2, **node);
                            ((Sprite_0015FE50 *)arg2)->x = (value >> 16) - (((Sprite_0015FE50 *)arg2)->info->x & 0x1FFF);
                            ((Sprite_0015FE50 *)arg2)->y = (value & 0xFFFF) - (((Sprite_0015FE50 *)arg2)->info->y & 0x1FFF);
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

typedef struct {
    u16 id;
    u8 values[5];
} Info_00160030;

void func_00160030(s32 arg0, void *arg1, s32 *arg2) {
    Info_00160030 *info = arg1;
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
                if (card != 0x3E7 && func_00160210(card) == 0 && level >= func_0026FA80(card, arg0)) {
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

s32 func_00160210(s32 arg0) {
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
} Obj1_00160270;

typedef struct {
    u8 pad0[0x38];
    s16 f38;
    s16 f3A;
    u16 id;
} Obj2_00160270;

s32 func_00160270(s32 arg0, void *arg1, void *arg2) {
    Obj1_00160270 *o1 = arg1;
    Obj2_00160270 *o2 = arg2;
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
                        o2->f38 += (s16)func_002493A0(list[i]);
                        o2->f3A += (s16)func_002493A0(list[i]);
                    }
                }
            }
        }
    }
    return 1;
}

void func_001604A0(s32 unused0, s32 unused1) {
    func_0024E410(unused0, unused1);
}

typedef struct {
    u8 low : 4;
    u8 high : 4;
} Nibbles_001604B0;

typedef struct {
    u8 pad[0x3E];
    u8 f3E;
} Card_001604B0;

s32 func_0024FE40(void *, s32, s32);

s32 func_001604B0(s32 arg0, s32 arg1, void *arg2, s32 arg3) {
    extern s32 func_00278510();
    extern s32 func_0027A130(s32, void *, s32, s32, s32, s32, s32, s32, u8, u16);
    extern s32 func_002792C0(s32, void *, s32, s32, s32, s32, u16, u8);
    Card_001604B0 *card = arg2;
    Nibbles_001604B0 entries[12];
    s32 id;
    s32 hi;
    s32 lo;
    s32 i;
    Nibbles_001604B0 *entry;
    s32 pos;
    s32 cost;
    s32 bestId;
    s32 best;
    s32 y;
    s32 x;
    s32 j;
    s32 slot;

    if (card == NULL) {
        return -1;
    }
    entry = entries;
    i = 0;
    do {
        entry->low = entry->high = 15;
        entry++;
        i++;
    } while (i < 12);
    if ((u8)(card->f3E >> 5) == 0 && arg3 >= 0) {
        best = 0xFF;
        bestId = 0xFFFF;
        pos = func_001E1090(arg3 >> 8, arg3 & 0xFF);
        for (i = 0; i < 8; i++) {
            id = func_0024E410(arg0, i);
            if (id < 0) {
                continue;
            }
            lo = id & 0xFF;
            hi = id >> 8;
            if (func_001E22B0(lo, hi) == 8) {
                continue;
            }
            if (func_001E22B0(lo, hi) == 9 && func_0024FE40(card, lo, hi) == 1) {
                continue;
            }
            if (func_001E36E0(lo, hi) != 0) {
                continue;
            }
            if (func_00278510(card, arg3, func_00162580(arg0), pos & 0xFF, pos >> 8, 0) > 0) {
                cost = func_0027A130((s32)card, entries, lo, hi, pos & 0xFF, pos >> 8, arg3, 0, 3,
                                     func_00162580(arg0));
            } else {
                cost = func_002792C0((s32)card, entries, lo, hi, pos & 0xFF, pos >> 8, arg3, 3);
            }
            if (func_0027AFC0((u8 *)entries) > 0 && cost < best) {
                best = cost;
                bestId = id;
            }
        }
        if (bestId != 0xFFFF) {
            return bestId;
        }
    }
    for (j = 0; j < 8; j++) {
        slot = func_0024E410(arg0, j);
        if (slot < 0) {
            continue;
        }
        x = slot & 0xFF;
        y = slot >> 8;
        if (func_001E22B0(x, y) == 8) {
            continue;
        }
        if (func_001E22B0(x, y) == 9 && func_0024FE40(card, x, y) == 1) {
            continue;
        }
        if (func_001E3790(x, y) < 0) {
            return slot;
        }
    }
    return -1;
}

typedef struct Nibbles_001607D0 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_001607D0;

typedef struct Output_001607D0 {
    u16 position;
    u8 action;
    u8 pad3;
    u16 destination;
    u8 pad6[6];
    s32 special;
    u8 result;
} Output_001607D0;

s32 func_001E1E70(s32, s32, s32, s32);
s32 func_002464F0(s32, s32, s32);
s32 func_00276CC0(s32, s32, s32, s32, s32, s32);
s32 func_0027BE10(s32, s32, s32, s32, s32);

s32 func_001607D0(u16 *arg0, s32 arg1, void *arg2, u8 arg3) {
    Output_001607D0 *output = arg2;
    s32 target;
    u8 endX;
    u8 extra;
    Nibbles_001607D0 nibbles[12];
    s32 bestScore;
    s32 best;
    s32 i;
    Nibbles_001607D0 *p;
    extern s32 func_001620B0();
    extern s32 func_00279C40(s32, s32, s32, s32, s32, s32, void *, u8);

    target = func_001E1090(*arg0 >> 8, *arg0 & 0xFF);
    p = nibbles;
    i = 0;
    do {
        i++;
        p->low = p->high = 0xF;
        p++;
    } while (i < 12);
    {
        s32 range;
        s32 y;
        u8 minY;
        u8 minX;
        s32 candidateScore;
        u8 maxY;
        s32 packedY;
        s32 centerY;
        s32 centerX;
        s32 x;
        s32 limit;
        u16 initialScore;

        initialScore = func_00162580(arg1);
        centerX = target & 0xFF;
        centerY = target >> 8;
        if (func_00276CC0(centerX, centerY, *arg0, 3, initialScore, 0) == 0) {
            output->position = *arg0;
            output->action = 6;
            output->destination = target;
            output->result = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, output->destination, 1, 0);
            output->special = func_001620B0(*arg0 >> 8, *arg0 & 0xFF, arg0);
            func_0027B1B0(arg0, arg3);
            return 0;
        }
        if ((range = func_002464F0(func_001DF540(*arg0 >> 8, *arg0 & 0xFF), centerX, centerY)) == 0) {
            output->position = *arg0;
            output->action = 6;
            output->destination = target;
            output->result = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, output->destination, 1, 0);
            output->special = func_001620B0(*arg0 >> 8, *arg0 & 0xFF, arg0);
            func_0027B1B0(arg0, arg3);
            return 0;
        }
        if (func_001E2100(*arg0 >> 8, *arg0 & 0xFF, 4) != 0) {
            if ((func_001E0700(*arg0 >> 8, *arg0 & 0xFF) >> 5) == 1 ||
                (func_001E0700(*arg0 >> 8, *arg0 & 0xFF) >> 5) == 5) {
                func_001E1E70(*arg0 >> 8, *arg0 & 0xFF, 0, 1);
                output->position = *arg0;
                output->action = 0xE;
                return 0;
            }
        }
        best = 0xFF;
        bestScore = 0xFFFF;
        minX = (u8)func_00250860(0, centerX - (range & 0xF));
        limit = centerX + (range & 0xF);
        endX = limit >= 7 ? 6 : limit;
        minY = (u8)func_00250860(0, centerY - (range & 0xF));
        limit = centerY + (range & 0xF);
        if (limit >= 7) {
            limit = 6;
        }
        maxY = (u8)limit;
        if ((*arg0 & 0xFF) == 0) {
            extra = (u8)func_0027BBC0(*arg0 >> 8, *arg0 & 0xFF, 0);
        } else {
            extra = 0;
        }
        for (x = minX; x <= endX; x++) {
            y = minY;
            packedY = y << 8;
            for (; y <= maxY; packedY += 0x100, y++) {
                if ((((x < centerX ? centerX : x) - (centerX < x ? centerX : x)) +
                    ((y < centerY ? centerY : y) - (centerY < y ? centerY : y))) > (range & 0xF)) {
                    continue;
                }
                if (func_00279C40(*arg0 >> 8, *arg0 & 0xFF, centerX, centerY, x, y, arg0, extra) == 1) {
                    if (func_0027BE10(*arg0 >> 8, *arg0 & 0xFF, x, y, 0) == 0 || (u8)*arg0 == 0) {
                        candidateScore = func_00276CC0(x, y, *arg0, 3, (u16)func_00162580(arg1), 0);
                        if (candidateScore < bestScore) {
                            bestScore = candidateScore;
                            best = packedY | x;
                        } else if (candidateScore == bestScore && func_001E36E0(x, y) == 0 &&
                            func_001E36E0(best & 0xFF, best >> 8) != 0) {
                            bestScore = candidateScore;
                            best = packedY | x;
                        }
                    }
                }
            }
        }
        if (best != 0xFF) {
            output->position = *arg0;
            output->action = 6;
            output->destination = best;
            if (best == target) {
                output->result = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, output->destination, 1, 0);
            } else {
                output->result = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, output->destination, 0, 0);
            }
            output->special = func_001620B0(*arg0 >> 8, *arg0 & 0xFF, arg0);
        } else {
            output->position = *arg0;
            output->action = 6;
            output->destination = target;
            output->result = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, output->destination, 1, 0);
            output->special = func_001620B0(*arg0 >> 8, *arg0 & 0xFF, arg0);
        }
        func_0027B1B0(arg0, arg3);
        return 0;
    }
}

typedef struct Input_00160DA0 {
    u16 position;
    u8 pad[6];
    u32 destinations;
} Input_00160DA0;

typedef struct Output_00160DA0 {
    u16 position;
    u8 action;
    u8 pad3;
    u16 destination;
    u8 pad6[6];
    s32 direct;
    u8 result;
} Output_00160DA0;

typedef struct Coord_00160DA0 {
    u8 x : 4;
    u8 y : 4;
} Coord_00160DA0;

s32 func_002464F0(s32, s32, s32);
s32 func_00276CC0(s32, s32, s32, s32, s32, s32);

static inline u32 destination_00160DA0(void *src, s32 which) {
    if (which == 1) {
        return (u16)(((Input_00160DA0 *)src)->destinations >> 16);
    }
    return (u16)((Input_00160DA0 *)src)->destinations;
}

static inline s32 closer_00160DA0(Coord_00160DA0 *best, Coord_00160DA0 *current,
                                  s32 targetX, s32 targetY) {
    s32 minBestY = best->y < targetY ? best->y : targetY;
    s32 maxBestY = targetY < best->y ? best->y : targetY;
    s32 minBestX = best->x < targetX ? best->x : targetX;
    s32 maxBestX = targetX < best->x ? best->x : targetX;
    s32 minCurrentY = current->y < targetY ? current->y : targetY;
    s32 maxCurrentY = targetY < current->y ? current->y : targetY;
    s32 minCurrentX = current->x < targetX ? current->x : targetX;
    s32 maxCurrentX = targetX < current->x ? current->x : targetX;

    return (maxCurrentX - minCurrentX) + (maxCurrentY - minCurrentY) <
           (maxBestX - minBestX) + (maxBestY - minBestY);
}

s32 func_00160DA0(void *arg0, s32 arg1, void *arg2, u8 arg3) {
    extern s32 func_001620B0();
    extern void func_0027A090();
    Coord_00160DA0 coords[12];
    s32 original;
    s32 count;
    s32 originalY;
    s32 originalX;
    s32 direct;
    s32 target;
    s32 targetX;
    Coord_00160DA0 *current;
    s32 fallback;
    s32 sourcePosition;
    s32 mode;
    s32 i;
    s32 bestCost;
    s32 bestIndex;
    u32 destinationForX;
    u32 destinationForY;
    Input_00160DA0 *input = arg0;
    Output_00160DA0 *output = arg2;

    mode = arg3;
    destinationForX = destination_00160DA0(arg0, mode);
    destinationForY = destination_00160DA0(arg0, mode);
    if (func_001DF540(destinationForY >> 8, destinationForX & 0xFF) == 0) {
        func_0027B1B0(arg0, 1);
        return -1;
    }
    fallback = func_001620B0(input->position >> 8,
                            input->position & 0xFF, arg0);
    original = func_001E1090(input->position >> 8,
                            input->position & 0xFF);
    destinationForX = destination_00160DA0(arg0, mode);
    destinationForY = destination_00160DA0(arg0, mode);
    target = func_001E1090(destinationForY >> 8, destinationForX & 0xFF);
    {
        s32 j = 0;
        do {
            coords[j].x = coords[j].y = 15;
            j++;
        } while (j < 12);
    }
    {
        s32 card = func_001DF540(input->position >> 8,
                                input->position & 0xFF);
        originalX = original & 0xFF;
        originalY = original >> 8;
        if (func_002464F0(card, originalX, originalY) == 0) {
            s32 cost;
            output->position = input->position;
            output->action = 6;
            output->destination = original;
            cost = func_00276CC0(originalX, originalY, arg1, 3, 1,
                                (u8)func_00162580(arg1));
            if (cost >= func_001E0290(input->position >> 8,
                                     input->position & 0xFF, 0)) {
                output->result = func_0027E360(
                    input->position >> 8,
                    input->position & 0xFF,
                    output->destination, 1, 0);
            } else {
                output->result = func_0027E360(
                    input->position >> 8,
                    input->position & 0xFF,
                    output->destination, 0, 0);
            }
            func_0027B1B0(arg0, arg3);
            return 0;
        } else {
            s32 sourceY;
            s32 sourceX;
            u16 leader;
            sourcePosition = input->position;
            leader = (u16)func_00162580(arg1);
            sourceY = sourcePosition >> 8;
            sourceX = sourcePosition & 0xFF;
            targetX = target & 0xFF;
            func_0027A090(sourceY, sourceX,
                          coords, originalX, originalY, targetX, target >>= 8,
                          destination_00160DA0(arg0, mode), 0, 30,
                          leader);
            count = func_0027AFC0((u8 *)coords);
            bestIndex = 0xFF;
            if (count > 0) {
                direct = 0;
                bestCost = 0xFFFF;
                for (i = 0; i < count; i++) {
                    if (func_00162390(input->position >> 8,
                                      input->position & 0xFF,
                                      originalX, originalY, targetX, target) == 1) {
                        bestIndex = i;
                        direct = 1;
                        coords[i].x = targetX;
                        coords[i].y = target;
                        i = count;
                    } else {
                        s32 cost;
                        current = &coords[i];
                        cost = func_00276CC0(current->x, current->y, arg1, 2, 1,
                                             (u8)func_00162580(arg1));
                        if (cost < bestCost) {
                            bestCost = cost;
                            bestIndex = i;
                        } else if (cost == bestCost) {
                            if (closer_00160DA0(&coords[bestIndex], current, targetX, target)) {
                                bestCost = cost;
                                bestIndex = i;
                            }
                        }
                    }
                }
            } else {
                output->position = input->position;
                output->action = 6;
                output->destination = original;
                output->direct = fallback;
                output->result = func_0027E360(
                    input->position >> 8,
                    input->position & 0xFF,
                    output->destination, 0, 0);
                func_0027B1B0(arg0, arg3);
                return 0;
            }
            if (bestIndex != 0xFF) {
                output->position = input->position;
                output->action = 6;
                output->destination = (coords[bestIndex].y << 8) | coords[bestIndex].x;
                output->direct = direct;
                output->result = func_0027E360(
                    input->position >> 8,
                    input->position & 0xFF,
                    output->destination, 0, 0);
            } else {
                output->position = input->position;
                output->action = 6;
                output->destination = original;
                output->direct = direct;
                output->result = func_0027E360(
                    input->position >> 8,
                    input->position & 0xFF,
                    output->destination, 0, 0);
                func_0027B1B0(arg0, arg3);
                return 0;
            }

        }
    }
    return 0;
}

typedef struct Coord_00161380 {
    u8 x : 4;
    u8 y : 4;
} Coord_00161380;

typedef struct Unit_00161380 {
    u16 position;
    u8 pad2[6];
    union {
        u32 packed;
        u16 low;
    } target;
} Unit_00161380;

typedef struct Output_00161380 {
    u16 position;
    u8 kind;
    u8 pad3;
    u16 target;
    u8 pad6[6];
    s32 value;
    u8 flag;
} Output_00161380;

s32 func_001E1E70(s32, s32, s32, s32);

static inline u32 target_00161380(void *unit, s32 side) {
    return side == 1 ? (u32)(u16)(((Unit_00161380 *)unit)->target.packed >> 16) : (u32)((Unit_00161380 *)unit)->target.low;
}

static inline u32 minY_00161380(void *unit, s32 side, u8 coord) {
    return coord < (target_00161380(unit, side) >> 8) ? coord : (target_00161380(unit, side) >> 8);
}

static inline u32 maxY_00161380(void *unit, s32 side, u8 coord) {
    return (target_00161380(unit, side) >> 8) < coord ? coord : (target_00161380(unit, side) >> 8);
}

static inline u32 minX_00161380(void *unit, s32 side, u8 coord) {
    return coord < (target_00161380(unit, side) & 0xFF) ? coord : (target_00161380(unit, side) & 0xFF);
}

static inline u32 maxX_00161380(void *unit, s32 side, u8 coord) {
    return (target_00161380(unit, side) & 0xFF) < coord ? coord : (target_00161380(unit, side) & 0xFF);
}

s32 func_00161380(void *arg0, s32 arg1, void *arg2, u8 arg3, u8 arg4) {
    extern s32 func_001620B0();
    extern s32 func_00276CC0();
    extern void func_00279230();
    extern s32 func_0027E360(s32, s32, s32, u8, s32);
    Coord_00161380 coords[12];
    s32 initial;
    s32 cell;
    s32 count;

    initial = func_001E1090(((Unit_00161380 *)arg0)->position >> 8, ((Unit_00161380 *)arg0)->position & 0xFF);
    {
    s32 bestScore;
    s32 best;
    s32 side = arg3;
    Coord_00161380 *candidate;
    s32 index;
    if (target_00161380(arg0, side) == 0xFFFF) {
        if (initial == target_00161380(arg0, side)) {
            ((Output_00161380 *)arg2)->position = ((Unit_00161380 *)arg0)->position;
            ((Output_00161380 *)arg2)->kind = 6;
            ((Output_00161380 *)arg2)->target = initial;
            ((Output_00161380 *)arg2)->flag = func_0027E360(((Unit_00161380 *)arg0)->position >> 8, ((Unit_00161380 *)arg0)->position & 0xFF, ((Output_00161380 *)arg2)->target, arg4, 0);
            ((Output_00161380 *)arg2)->value = func_001620B0(((Unit_00161380 *)arg0)->position >> 8, ((Unit_00161380 *)arg0)->position & 0xFF, arg0);
            func_0027B1B0(arg0, arg3);
            return 0;
        }
    }

    if (func_001E2100(((Unit_00161380 *)arg0)->position >> 8,
                      ((Unit_00161380 *)arg0)->position & 0xFF, 4) != 0) {
        if ((func_001E0700(((Unit_00161380 *)arg0)->position >> 8,
                          ((Unit_00161380 *)arg0)->position & 0xFF) >> 5) == 1 ||
            (func_001E0700(((Unit_00161380 *)arg0)->position >> 8,
                          ((Unit_00161380 *)arg0)->position & 0xFF) >> 5) == 5) {
            func_001E1E70(((Unit_00161380 *)arg0)->position >> 8,
                          ((Unit_00161380 *)arg0)->position & 0xFF, 0, 1);
            ((Output_00161380 *)arg2)->position = ((Unit_00161380 *)arg0)->position;
            ((Output_00161380 *)arg2)->kind = 0xE;
            return 0;
        }
    }

    candidate = coords;
    {
        s32 i = 0;
        Coord_00161380 *entry = candidate;
        do {
            entry->x = entry->y = 0xF;
            i++;
            entry++;
        } while (i < 12);
    }

    cell = func_001E3790(target_00161380(arg0, side) & 0xFF, ((u32)target_00161380(arg0, side)) >> 8);
    if (cell < 0) {
        cell = 0xFFFF;
    }
    func_00279230(((Unit_00161380 *)arg0)->position >> 8, ((Unit_00161380 *)arg0)->position & 0xFF,
                 coords, initial & 0xFF, initial >> 8, target_00161380(arg0, side) & 0xFF,
                 ((u32)target_00161380(arg0, side)) >> 8, (u16)cell, 7);
    count = func_0027AFC0((u8 *)coords);
    {
        if (count > 0) {
        best = 0xFF;
        bestScore = 0xFFFF;
        for (index = 0; index < count; index++) {
                if (func_001E36E0(candidate->x, candidate->y) == 0) {
                    s32 score = func_00276CC0(candidate->x, candidate->y, arg1, 2, 1, (u8)func_00162580(arg1));
                    if (score < bestScore) {
                        bestScore = score;
                        best = index;
                    } else if (score == bestScore) {
                        u32 bestMinY;
                        u32 bestMaxY;
                        u32 bestMinX;
                        u32 bestMaxX;
                        u32 currentMinY;
                        u32 currentMaxY;
                        u32 currentMinX;
                        u32 currentMaxX;
                        u32 bestY;
                        u32 bestX;
                        u32 currentY;
                        u32 currentX;
                        bestY = (u8)(&coords[best])->y;
                        bestMinY = minY_00161380(arg0, side, bestY);
                        bestMaxY = maxY_00161380(arg0, side, bestY);
                        bestX = (&coords[best])->x;
                        bestMinX = minX_00161380(arg0, side, bestX);
                        bestMaxX = maxX_00161380(arg0, side, bestX);
                        currentY = (u8)candidate->y;
                        currentMinY = minY_00161380(arg0, side, currentY);
                        currentMaxY = maxY_00161380(arg0, side, currentY);
                        currentX = candidate->x;
                        currentMinX = minX_00161380(arg0, side, currentX);
                        currentMaxX = maxX_00161380(arg0, side, currentX);
                        if ((currentMaxX - currentMinX) + (currentMaxY - currentMinY) < (bestMaxX - bestMinX) + (bestMaxY - bestMinY)) {
                            bestScore = score;
                            best = index;
                        }
                    }
                }
            candidate++;
        }
    } else {
        ((Output_00161380 *)arg2)->position = ((Unit_00161380 *)arg0)->position;
            ((Output_00161380 *)arg2)->kind = 6;
            ((Output_00161380 *)arg2)->target = initial;
            ((Output_00161380 *)arg2)->flag = func_0027E360(((Unit_00161380 *)arg0)->position >> 8, ((Unit_00161380 *)arg0)->position & 0xFF, ((Output_00161380 *)arg2)->target, arg4, 0);
            ((Output_00161380 *)arg2)->value = func_001620B0(((Unit_00161380 *)arg0)->position >> 8, ((Unit_00161380 *)arg0)->position & 0xFF, arg0);
        func_0027B1B0(arg0, arg3);
        return 0;
    }

        if (best != 0xFF) {
            ((Output_00161380 *)arg2)->position = ((Unit_00161380 *)arg0)->position;
            ((Output_00161380 *)arg2)->kind = 6;
            ((Output_00161380 *)arg2)->target = (coords[best].y << 8) | coords[best].x;
            ((Output_00161380 *)arg2)->flag = func_0027E360(((Unit_00161380 *)arg0)->position >> 8, ((Unit_00161380 *)arg0)->position & 0xFF, ((Output_00161380 *)arg2)->target, arg4, 0);
            ((Output_00161380 *)arg2)->value = func_001620B0(((Unit_00161380 *)arg0)->position >> 8, ((Unit_00161380 *)arg0)->position & 0xFF, arg0);
        } else {
            ((Output_00161380 *)arg2)->position = ((Unit_00161380 *)arg0)->position;
            ((Output_00161380 *)arg2)->kind = 6;
            ((Output_00161380 *)arg2)->target = initial;
            ((Output_00161380 *)arg2)->flag = func_0027E360(((Unit_00161380 *)arg0)->position >> 8, ((Unit_00161380 *)arg0)->position & 0xFF, ((Output_00161380 *)arg2)->target, arg4, 0);
            ((Output_00161380 *)arg2)->value = func_001620B0(((Unit_00161380 *)arg0)->position >> 8, ((Unit_00161380 *)arg0)->position & 0xFF, arg0);
        }
        func_0027B1B0(arg0, arg3);
    }
    }
    return 0;
}

typedef struct Nibbles_00161BF0 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_00161BF0;

typedef struct Result_00161BF0 {
    u16 id;
    u8 type;
    u8 pad3;
    u16 target;
    u8 pad6[6];
    s32 state;
    u8 outcome;
} Result_00161BF0;

s32 func_001E1E70(s32, s32, s32, s32);
s32 func_0027DBC0(s32, s32, s32);

s32 func_00161BF0(u16 *arg0, s32 arg1, void *arg2, s32 arg3) {
    extern void func_0027B1B0();
    extern s32 func_001607D0();
    Nibbles_00161BF0 entries[12];
    s32 value;
    s32 selection;
    s32 index;
    Result_00161BF0 *result = arg2;

    {
        u32 *card;
        s32 mode;

        mode = (u8)(func_001E0700(*arg0 >> 8, *arg0 & 0xFF) >> 5);
        if (mode == 0) {
            card = func_001E0B70(*arg0 >> 8, *arg0 & 0xFF, 3);
        } else {
            card = func_001E0B70(*arg0 >> 8, *arg0 & 0xFF, 0);
        }
        value = func_001E1090(*arg0 >> 8, *arg0 & 0xFF);
        index = 0;
        do {
            entries[index].low = entries[index].high = -1;
            index++;
        } while (index < 12);

        if (card != NULL) {
            if (mode != 0) {
                selection = func_001627D0(arg1);
                if (func_001E22B0(value & 0xFF, value >> 8) == 9) {
                    selection = -1;
                }
                if (func_0027D830(*arg0 >> 8, *arg0 & 0xFF, 0, 0, 6, 0) == 5) {
                    selection = -1;
                }
            } else {
                selection = func_00162A70(arg1);
            }
            if (selection >= 0) {
                value = (selection >> 16) & 0xFFFF;
                mode = func_0027DBC0(value, selection & 0xFF, *card & 0x3F);
                result->id = *arg0;
                result->type = 12;
                result->outcome = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, result->target, 1, 0);
                result->state = 1;
                if (((*card >> 6) & 3) != 3) {
                    result->target = (arg1 << 8) | mode;
                } else {
                    result->target = (value << 8) | mode;
                }
                func_0027B1B0(arg0, arg3);
                return 0;
            }
        }
        if (mode != 0) {
            if (func_001E2100(*arg0 >> 8, *arg0 & 0xFF, 4) != 0) {
                func_001E1E70(*arg0 >> 8, *arg0 & 0xFF, 0, 1);
                result->id = *arg0;
                result->type = 14;
                return 0;
            }
        }
        return func_001607D0(arg0, arg1, arg2, arg3);
    }
}

INCLUDE_ASM("asm/nonmatchings/main_014", func_00161EA0);

s32 func_001620B0(s32 arg0, s32 arg1) {
    s32 s0;
    s32 s1;
    s32 s2;
    u32 *s3;
    s32 a;
    s32 b;

    s0 = func_001E1030();
    s1 = func_001E1090(arg0, arg1);
    s2 = func_00250360(arg0, arg1);
    s3 = func_001E0B70(arg0, arg1, 0);
    if (func_001E2100(arg0, arg1, 4) != 0) {
        return 0;
    }
    switch (func_001E0700(arg0, arg1) >> 5) {
    case 5:
        if (func_0027D830(arg0, arg1, 0, 0, 6, 0) == 5) {
            return 2;
        }
        if (func_00162490(func_00250360(arg0, arg1), s0) == 1) {
            if (func_001E22B0(s1 & 0xFF, s1 >> 8) != 9) {
                return 1;
            }
        }
        break;
    case 1:
        if (func_0027D830(arg0, arg1, 0, 0, 6, 0) == 5) {
            return 2;
        }
        if (s3 == NULL) {
            return 2;
        }
        switch (*s3 >> 8) {
        case 4:
            a = func_001625E0(s2);
            s1 = func_001E1090(arg0, arg1);
            b = func_001E1090(a >> 8, a & 0xFF);
            if ((s1 & 0xFF) == (b & 0xFF) || (s1 >> 8) == (b >> 8)) {
                return 1;
            }
            break;
        case 0x49:
            if (func_001626F0(s2) == 1) {
                return 1;
            }
            break;
        case 0x25:
            if (s0 == 0x2ED && func_0027BBC0(arg0, 0, 0) == 1) {
                return 1;
            }
            if (s0 == 0x2EA && func_0027BBC0(arg0, arg1, 0) == 1) {
                return 1;
            }
            break;
        case 0x1F:
            if (s0 == 0x2DD && func_00162D10(s2) == 1) {
                return 1;
            }
            break;
        }
        break;
    default:
        return 2;
    }
    return 2;
}

static inline s32 max_00162390(s32 a, s32 b) {
    if (a < b) {
        return b;
    }
    return a;
}

s32 func_00162390(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 min_y;
    s32 min_x;

    min_y = (arg3 < arg5) ? arg3 : arg5;
    arg5 = max_00162390(arg5, arg3);
    min_x = (arg2 < arg4) ? arg2 : arg4;
    arg4 = max_00162390(arg4, arg2);
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

s32 func_00162490(s32 arg0, s32 arg1) {
    s32 i;
    s32 mask;
    s32 low;
    s32 high;
    s32 packed;
    s32 position;
    s32 sp50[4];

    func_00254C90(sp50, *(s32 *)((u8 *)func_0026FC90(arg1, 0) + 4));
    if ((mask = func_00254890(sp50, arg0)) < 0) {
        return 0;
    }

    i = 0;
    if (i < func_0024E910(mask)) {
        do {
            packed = func_0024EC50(mask, i);
            high = packed >> 8;
            low = packed & 0xFF;
            position = func_001E1090(high, low);
            if (func_002509E0(high, low, position & 0xFF, position >> 8) >= 0xBB8) {
                return 0;
            }
            i++;
        } while (i < func_0024E910(mask));
    }
    return 1;
}

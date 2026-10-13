#include "common.h"

typedef struct Info_00114D40 {
    u8 pad00[8];
    u16 x;
    s16 y;
} Info_00114D40;

typedef struct Sprite_00114D40 {
    Info_00114D40 *info;
    u8 pad04[0x34];
    s16 x;
    s16 y;
} Sprite_00114D40;

u16 *func_00278A90(s32, u16 *, s32, s32, s32, s16 *, s16 *);
s32 func_00278F10(s32, u16 *, s32, s32);

s32 func_00114D40(s32 arg0, u8 *arg1, void *arg2) {
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
                            func_00114F20(arg0, *node, entries);
                            func_00278DD0((u8 *)*node + 2, arg1 + 6);
                            func_001DCD70(arg2, **node);
                            ((Sprite_00114D40 *)arg2)->x = (value >> 16) - (((Sprite_00114D40 *)arg2)->info->x & 0x1FFF);
                            ((Sprite_00114D40 *)arg2)->y = (value & 0xFFFF) - (((Sprite_00114D40 *)arg2)->info->y & 0x1FFF);
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
} Info_00114F20;

void func_00114F20(s32 arg0, void *arg1, s32 *arg2) {
    Info_00114F20 *info = arg1;
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
                if (card != 0x3E7 && func_00115100(card) == 0 && level >= func_0026FA80(card, arg0)) {
                    cost = func_0026FBB0(card);
                    if ((cost & 0xFFFF) + (cost >> 16) * 2 < 0x1389 && func_0026FC10(card) == 2 &&
                        (u16)func_002789F0(info->id, (u16)card) == 0x3E7) {
                        func_00278D20(info->values, buf[i]);
                    }
                }
            }
        }
    }
}

s32 func_00115100(s32 arg0) {
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
} Obj1_00115160;

typedef struct {
    u8 pad0[0x3C];
    u16 id;
} Obj2_00115160;

s32 func_00115160(s32 arg0, void *arg1, void *arg2) {
    Obj1_00115160 *o1 = arg1;
    Obj2_00115160 *o2 = arg2;
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
            if (o2->id == list[i]) {
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

INCLUDE_ASM("asm/nonmatchings/main_005", func_00115340);

typedef struct Nibbles_00115850 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_00115850;

typedef struct Output_00115850 {
    u16 position;
    u8 action;
    u8 pad3;
    u16 destination;
    u8 pad6[6];
    s32 special;
    u8 result;
} Output_00115850;

void func_001E1E70(s32, s32, s32, s32);
s32 func_002464F0(s32, s32, s32);
s32 func_00276CC0(s32, s32, s32, s32, s32, s32);
s32 func_0027BE10(s32, s32, s32, s32, s32);

s32 func_00115850(u16 *arg0, s32 arg1, void *arg2, u8 arg3) {
    Output_00115850 *output = arg2;
    s32 target;
    u8 endX;
    u8 extra;
    Nibbles_00115850 nibbles[12];
    s32 bestScore;
    s32 best;
    s32 i;
    Nibbles_00115850 *p;
    extern s32 func_00117870();
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

        initialScore = func_00117C30(arg1);
        centerX = target & 0xFF;
        centerY = target >> 8;
        if (func_00276CC0(centerX, centerY, *arg0, 3, initialScore, 0) == 0) {
            output->position = *arg0;
            output->action = 6;
            output->destination = target;
            output->result = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, output->destination, 1, 0);
            output->special = func_00117870(*arg0 >> 8, *arg0 & 0xFF, arg0);
            func_0027B1B0(arg0, arg3);
            return 0;
        }
        if ((range = func_002464F0(func_001DF540(*arg0 >> 8, *arg0 & 0xFF), centerX, centerY)) == 0) {
            output->position = *arg0;
            output->action = 6;
            output->destination = target;
            output->result = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, output->destination, 1, 0);
            output->special = func_00117870(*arg0 >> 8, *arg0 & 0xFF, arg0);
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
                        candidateScore = func_00276CC0(x, y, *arg0, 3, (u16)func_00117C30(arg1), 0);
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
                output->result = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, output->destination, 1, 0);
            }
            output->special = func_00117870(*arg0 >> 8, *arg0 & 0xFF, arg0);
        } else {
            output->position = *arg0;
            output->action = 6;
            output->destination = target;
            output->result = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, output->destination, 1, 0);
            output->special = func_00117870(*arg0 >> 8, *arg0 & 0xFF, arg0);
        }
        func_0027B1B0(arg0, arg3);
        return 0;
    }
}

typedef struct Input_00115E20 {
    u16 position;
    u8 pad2[6];
    u32 targets;
} Input_00115E20;

typedef struct Output_00115E20 {
    u16 position;
    s8 action;
    u8 pad3;
    s16 target;
    u8 pad6[6];
    s32 kind;
    s8 result;
} Output_00115E20;

typedef struct Candidate_00115E20 {
    u8 x : 4;
    u8 y : 4;
} Candidate_00115E20;

static inline u32 target_00115E20(void *src, u8 mode) {
    Input_00115E20 *input = src;
    if (mode == 1) {
        return (input->targets >> 16) & 0xFFFF;
    }
    return (u16)input->targets;
}

void func_00117870(s32, s32, void *);
s32 func_002464F0(s32, s32, s32);
s32 func_00276CC0(s32, s32, s32, s32, s32, s32);

s32 func_00115E20(void *arg0, s32 arg1, void *arg2, u8 arg3) {
    extern void func_0027A090();
    s32 origin;
    s32 destination;
    s32 count;
    Candidate_00115E20 candidates[12];
    Candidate_00115E20 *point;
    s32 originY;
    s32 originX;
    s32 i;
    u32 selected;
    Input_00115E20 *input = arg0;
    Output_00115E20 *output = arg2;

    selected = target_00115E20(input, arg3);
    if (func_001DF540(target_00115E20(input, arg3) >> 8,
                     selected & 0xFF) == 0) {
        func_0027B1B0(input, 1);
        return -1;
    }
    func_00117870(input->position >> 8, input->position & 0xFF, input);
    origin = func_001E1090(input->position >> 8, input->position & 0xFF);
    selected = target_00115E20(input, arg3);
    destination = func_001E1090(target_00115E20(input, arg3) >> 8,
                               selected & 0xFF);
    point = candidates;
    for (i = 0; i < 12; i++) {
        candidates[i].x = candidates[i].y = 15;
    }
    if (func_002464F0(func_001DF540(input->position >> 8, input->position & 0xFF),
                      originX = origin & 0xFF, originY = origin >> 8) == 0) {
        s32 score;
        output->position = input->position;
        output->action = 6;
        output->target = origin;
        score = func_00276CC0(originX, originY, arg1, 3, 1,
                             (u8)func_00117C30(arg1));
        if (score >= func_001E0290(input->position >> 8, input->position & 0xFF, 0)) {
            output->result = 1;
        } else {
            output->result = 0;
        }
        func_0027B1B0(input, arg3);
        return 0;
    } else {
        s32 position;
        s32 destinationY;
        s32 destinationX;
        s32 index;
        s32 bestScore;
        s32 bestIndex;
        u16 random;

        position = input->position;
        random = func_00117C30(arg1);
        func_0027A090(position >> 8, position & 0xFF, candidates,
                      originX, originY, destinationX = destination & 0xFF,
                      destinationY = destination >> 8,
                      target_00115E20(input, arg3), (s64)0, (s64)30,
                      (s64)random);
        count = func_0027AFC0((u8 *)candidates);
        bestIndex = 255;
        if (count > 0) {
            bestScore = 65535;
            for (index = 0; index < count; index++, point++) {
                s32 score = func_00276CC0(point->x, point->y, arg1, 2, 1,
                                         (u8)func_00117C30(arg1));
                if (score < bestScore) {
                    bestScore = score;
                    bestIndex = index;
                } else if (score == bestScore) {
                    Candidate_00115E20 *best = &candidates[bestIndex];
                    if (((destinationX < point->x ? point->x : destinationX) -
                         (point->x < destinationX ? point->x : destinationX)) +
                        ((destinationY < point->y ? point->y : destinationY) -
                         (point->y < destinationY ? point->y : destinationY)) <
                        ((destinationX < best->x ? best->x : destinationX) -
                         (best->x < destinationX ? best->x : destinationX)) +
                        ((destinationY < best->y ? best->y : destinationY) -
                         (best->y < destinationY ? best->y : destinationY))) {
                        bestScore = score;
                        bestIndex = index;
                    }
                }
            }
        } else {
            output->position = input->position;
            output->action = 6;
            output->target = origin;
            output->kind = 2;
            output->result = 2;
            func_0027B1B0(input, arg3);
            return -1;
        }
        if (bestIndex != 255) {
            output->position = input->position;
            output->action = 6;
            output->target = (candidates[bestIndex].y << 8) | candidates[bestIndex].x;
            output->kind = 2;
            output->result = 2;
        } else {
            output->position = input->position;
            output->action = 6;
            output->target = origin;
            output->kind = 2;
            output->result = 2;
            func_0027B1B0(input, arg3);
            return -1;
        }
    }
    return 0;
}

typedef struct Coord_001162F0 {
    u8 x : 4;
    u8 y : 4;
} Coord_001162F0;

typedef struct Unit_001162F0 {
    u16 position;
    u8 pad2[6];
    union {
        u32 packed;
        u16 low;
    } target;
} Unit_001162F0;

typedef struct Output_001162F0 {
    u16 position;
    u8 kind;
    u8 pad3;
    u16 target;
    u8 pad6[6];
    s32 value;
    u8 flag;
} Output_001162F0;

void func_001E1E70(s32, s32, s32, s32);

static inline u32 target_001162F0(void *unit, s32 side) {
    return side == 1 ? (u32)(u16)(((Unit_001162F0 *)unit)->target.packed >> 16) : (u32)((Unit_001162F0 *)unit)->target.low;
}

static inline u32 minY_001162F0(void *unit, s32 side, u8 coord) {
    return coord < (target_001162F0(unit, side) >> 8) ? coord : (target_001162F0(unit, side) >> 8);
}

static inline u32 maxY_001162F0(void *unit, s32 side, u8 coord) {
    return (target_001162F0(unit, side) >> 8) < coord ? coord : (target_001162F0(unit, side) >> 8);
}

static inline u32 minX_001162F0(void *unit, s32 side, u8 coord) {
    return coord < (target_001162F0(unit, side) & 0xFF) ? coord : (target_001162F0(unit, side) & 0xFF);
}

static inline u32 maxX_001162F0(void *unit, s32 side, u8 coord) {
    return (target_001162F0(unit, side) & 0xFF) < coord ? coord : (target_001162F0(unit, side) & 0xFF);
}

s32 func_001162F0(void *arg0, s32 arg1, void *arg2, u8 arg3, u8 arg4) {
    extern s32 func_00117870();
    extern s32 func_00276CC0();
    extern void func_00279230();
    extern s32 func_0027E360(s32, s32, s32, u8, s32);
    Coord_001162F0 coords[12];
    s32 initial;
    s32 cell;
    s32 count;

    initial = func_001E1090(((Unit_001162F0 *)arg0)->position >> 8, ((Unit_001162F0 *)arg0)->position & 0xFF);
    {
        s32 bestScore;
        s32 best;
        s32 side = arg3;
        Coord_001162F0 *candidate;
        s32 index;
        if (target_001162F0(arg0, side) == 0xFFFF) {
            if (initial == target_001162F0(arg0, side)) {
                ((Output_001162F0 *)arg2)->position = ((Unit_001162F0 *)arg0)->position;
                ((Output_001162F0 *)arg2)->kind = 6;
                ((Output_001162F0 *)arg2)->target = initial;
                ((Output_001162F0 *)arg2)->flag = func_0027E360(((Unit_001162F0 *)arg0)->position >> 8, ((Unit_001162F0 *)arg0)->position & 0xFF, ((Output_001162F0 *)arg2)->target, arg4, 0);
                ((Output_001162F0 *)arg2)->value = func_00117870(((Unit_001162F0 *)arg0)->position >> 8, ((Unit_001162F0 *)arg0)->position & 0xFF, arg0);
                func_0027B1B0(arg0, arg3);
                return 0;
            }
        }

        if (func_001E2100(((Unit_001162F0 *)arg0)->position >> 8, ((Unit_001162F0 *)arg0)->position & 0xFF, 4) != 0) {
            if ((func_001E0700(((Unit_001162F0 *)arg0)->position >> 8, ((Unit_001162F0 *)arg0)->position & 0xFF) >> 5) == 1 ||
                (func_001E0700(((Unit_001162F0 *)arg0)->position >> 8, ((Unit_001162F0 *)arg0)->position & 0xFF) >> 5) == 5) {
                func_001E1E70(((Unit_001162F0 *)arg0)->position >> 8, ((Unit_001162F0 *)arg0)->position & 0xFF, 0, 1);
                ((Output_001162F0 *)arg2)->position = ((Unit_001162F0 *)arg0)->position;
                ((Output_001162F0 *)arg2)->kind = 14;
                return 0;
            }
        }

        candidate = coords;
        {
            s32 i = 0;
            Coord_001162F0 *entry = candidate;
            do {
                entry->x = entry->y = 0xF;
                i++;
                entry++;
            } while (i < 12);
        }

        cell = func_001E3790(target_001162F0(arg0, side) & 0xFF, target_001162F0(arg0, side) >> 8);
        if (cell < 0) {
            cell = 0xFFFF;
        }
        func_00279230(((Unit_001162F0 *)arg0)->position >> 8, ((Unit_001162F0 *)arg0)->position & 0xFF,
                     coords, initial & 0xFF, initial >> 8, target_001162F0(arg0, side) & 0xFF,
                     target_001162F0(arg0, side) >> 8, (u16)cell, 7);
        count = func_0027AFC0((u8 *)coords);
        {
            if (count > 0) {
                best = 0xFF;
                bestScore = 0xFFFF;
                for (index = 0; index < count; index++) {
                    if (func_001E36E0(candidate->x, candidate->y) == 0) {
                        s32 score = func_00276CC0(candidate->x, candidate->y, arg1, 2, 1, (u8)func_00117C30(arg1));
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
                            bestMinY = minY_001162F0(arg0, side, bestY);
                            bestMaxY = maxY_001162F0(arg0, side, bestY);
                            bestX = (&coords[best])->x;
                            bestMinX = minX_001162F0(arg0, side, bestX);
                            bestMaxX = maxX_001162F0(arg0, side, bestX);
                            currentY = (u8)candidate->y;
                            currentMinY = minY_001162F0(arg0, side, currentY);
                            currentMaxY = maxY_001162F0(arg0, side, currentY);
                            currentX = candidate->x;
                            currentMinX = minX_001162F0(arg0, side, currentX);
                            currentMaxX = maxX_001162F0(arg0, side, currentX);
                            if ((currentMaxX - currentMinX) + (currentMaxY - currentMinY) < (bestMaxX - bestMinX) + (bestMaxY - bestMinY)) {
                                bestScore = score;
                                best = index;
                            }
                        }
                    }
                    candidate++;
                }
            } else {
                ((Output_001162F0 *)arg2)->position = ((Unit_001162F0 *)arg0)->position;
                ((Output_001162F0 *)arg2)->kind = 6;
                ((Output_001162F0 *)arg2)->target = initial;
                ((Output_001162F0 *)arg2)->flag = func_0027E360(((Unit_001162F0 *)arg0)->position >> 8, ((Unit_001162F0 *)arg0)->position & 0xFF, ((Output_001162F0 *)arg2)->target, arg4, 0);
                ((Output_001162F0 *)arg2)->value = func_00117870(((Unit_001162F0 *)arg0)->position >> 8, ((Unit_001162F0 *)arg0)->position & 0xFF, arg0);
                func_0027B1B0(arg0, arg3);
                return 0;
            }

            if (best != 0xFF) {
                ((Output_001162F0 *)arg2)->position = ((Unit_001162F0 *)arg0)->position;
                ((Output_001162F0 *)arg2)->kind = 6;
                ((Output_001162F0 *)arg2)->target = (coords[best].y << 8) | coords[best].x;
                ((Output_001162F0 *)arg2)->flag = func_0027E360(((Unit_001162F0 *)arg0)->position >> 8, ((Unit_001162F0 *)arg0)->position & 0xFF, ((Output_001162F0 *)arg2)->target, arg4, 0);
                ((Output_001162F0 *)arg2)->value = func_00117870(((Unit_001162F0 *)arg0)->position >> 8, ((Unit_001162F0 *)arg0)->position & 0xFF, arg0);
            } else {
                ((Output_001162F0 *)arg2)->position = ((Unit_001162F0 *)arg0)->position;
                ((Output_001162F0 *)arg2)->kind = 6;
                ((Output_001162F0 *)arg2)->target = initial;
                ((Output_001162F0 *)arg2)->flag = func_0027E360(((Unit_001162F0 *)arg0)->position >> 8, ((Unit_001162F0 *)arg0)->position & 0xFF, ((Output_001162F0 *)arg2)->target, arg4, 0);
                ((Output_001162F0 *)arg2)->value = func_00117870(((Unit_001162F0 *)arg0)->position >> 8, ((Unit_001162F0 *)arg0)->position & 0xFF, arg0);
            }
            func_0027B1B0(arg0, arg3);
        }
    }
    return 0;
}

typedef struct {
    u16 position;
    u8 pad2[6];
    union {
        u32 both;
        u16 half[2];
    } target;
} Source_00116B60;

typedef struct {
    u16 position;
    u8 action;
    u8 pad3;
    u16 target;
    u8 pad6[10];
    s8 result;
} Action_00116B60;

typedef struct {
    u8 x : 4;
    u8 y : 4;
} Point_00116B60;

#define MIN_00116B60(a, b) ((a) < (b) ? (a) : (b))
#define MAX_00116B60(a, b) ((b) < (a) ? (a) : (b))

s32 func_002464F0(s32, s32, s32);
s32 func_00276CC0(s32, s32, s32, s32, s32, s32);

static inline u32 target_00116B60(void *arg0, s32 mode) {
    Source_00116B60 *source = arg0;
    if (mode == 1) {
        return (u16)(source->target.both >> 16);
    }
    return source->target.half[0];
}

static inline void fill_00116B60(void *arg0, void *arg2, s32 target, s32 flag) {
    Source_00116B60 *source = arg0;
    Action_00116B60 *action = arg2;
    action->position = source->position;
    action->action = 6;
    action->target = target;
    action->result = func_0027E360(source->position >> 8,
        source->position & 0xFF, action->target, flag, 0);
}

s32 func_00116B60(void *arg0, s32 arg1, void *arg2, s32 arg3) {
    s32 start;
    s32 count;
    s32 startY;
    Point_00116B60 points[16];
    s32 bestScore;
    Point_00116B60 *p;
    s32 targetY;
    s32 targetX;
    s32 i;
    s32 bestIndex;
    s32 mode;
    s32 target;
    s32 startX;
    u32 xPosition;
    u32 yPosition;
    Source_00116B60 *source = arg0;
    Action_00116B60 *action = arg2;
    extern void func_0027A090();

    mode = arg3 & 0xFF;
    xPosition = target_00116B60(arg0, mode);
    yPosition = target_00116B60(arg0, mode);
    if (func_001DF540(yPosition >> 8, xPosition & 0xFF) == 0) {
        func_0027B1B0(arg0, 1);
        return -1;
    }
    start = func_001E1090(source->position >> 8, source->position & 0xFF);
    xPosition = target_00116B60(arg0, mode);
    yPosition = target_00116B60(arg0, mode);
    target = func_001E1090(yPosition >> 8, xPosition & 0xFF);
    if (target_00116B60(arg0, mode) == 0xFFFF) {
        fill_00116B60(arg0, arg2, start, 1);
        return 0;
    } else {
        s32 unit = func_001DF540(source->position >> 8, source->position & 0xFF);
        startX = start & 0xFF;
        startY = start >> 8;
        if (func_002464F0(unit, startX, startY) == 0 ||
                func_0027BBC0(source->position >> 8, source->position & 0xFF, 0) == 1) {
            fill_00116B60(arg0, arg2, start, 1);
            return 0;
        } else {
            p = points;
            {
                s32 n = 0;
                Point_00116B60 *q = p;
                do {
                    q->x = q->y = 0xF;
                    q++;
                    n++;
                } while (n < 12);
            }
            {
                s32 position = source->position;
                u16 card = (u16)func_00117C30(arg1);
                func_0027A090(position >> 8, position & 0xFF, points,
                    startX, startY, targetX = target & 0xFF,
                    targetY = target >> 8, target_00116B60(arg0, mode),
                    0, 30, card);
            }
            count = func_0027AFC0((u8 *)points);
            bestIndex = 0xFF;
            if (count > 0) {
                bestScore = 0;
                for (i = 0; i < count; i++, p++) {
                    if (func_001E36E0(p->x, p->y) == 0) {
                        s32 score = func_00276CC0(p->x, p->y, arg1, 3, 1,
                            func_00117C30(arg1) & 0xFF);
                        if (bestScore < score) {
                            bestScore = score;
                            bestIndex = i;
                        } else if (score == bestScore) {
                            if (MAX_00116B60(p->x, targetX) - MIN_00116B60(p->x, targetX)
                                    + (MAX_00116B60(p->y, targetY) - MIN_00116B60(p->y, targetY))
                                    < MAX_00116B60(points[bestIndex].x, targetX) - MIN_00116B60(points[bestIndex].x, targetX)
                                    + (MAX_00116B60(points[bestIndex].y, targetY) - MIN_00116B60(points[bestIndex].y, targetY))) {
                                bestScore = score;
                                bestIndex = i;
                            }
                        }
                    }
                }
            } else {
                fill_00116B60(arg0, arg2, start, 1);
                return 0;
            }
            if (bestIndex != 0xFF) {
                action->position = source->position;
                action->action = 6;
                action->target = (points[bestIndex].y << 8) | points[bestIndex].x;
                action->result = func_0027E360(source->position >> 8,
                    source->position & 0xFF, action->target, 0, 0);
            } else {
                fill_00116B60(arg0, arg2, start, 1);
                return 0;
            }
        }
    }
    return 0;
}

typedef struct Nibbles_001170A0 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_001170A0;

typedef struct Output_001170A0 {
    u16 position;
    s8 command;
    u8 pad3;
    u16 value;
    u8 pad6[6];
    s32 count;
    s8 result;
} Output_001170A0;

void func_001E1E70(s32, s32, s32, s32);
s32 func_0027DBC0(s32, s32, s32);

s32 func_001170A0(u16 *arg0, s32 arg1, void *arg2, u8 arg3) {
    Nibbles_001170A0 flags[12];
    s32 card;
    s32 selected;
    s32 index;
    Output_001170A0 *output = arg2;

    {
        s32 state;
        u32 *data;

        if ((func_001E0700(*arg0 >> 8, *arg0 & 0xFF) >> 5) == 0) {
            data = func_001E0B70(*arg0 >> 8, *arg0 & 0xFF, 3);
        } else {
            data = func_001E0B70(*arg0 >> 8, *arg0 & 0xFF, 0);
        }
        card = func_001E1090(*arg0 >> 8, *arg0 & 0xFF);
        state = func_001E0700(*arg0 >> 8, *arg0 & 0xFF) >> 5;
        index = 0;
        do {
            flags[index].low = flags[index].high = 15;
            index++;
        } while (index < 12);

        if (data != NULL) {
            selected = func_00117680(arg1);
            if (state != 0) {
                if (func_001E22B0(card & 0xFF, card >> 8) == 9) {
                    selected = -1;
                }
                if (func_0027D830(*arg0 >> 8, *arg0 & 0xFF, 0, 0, 6, 0) == 5) {
                    selected = -1;
                }
            }
            if (selected >= 0) {
                state = (selected >> 16) & 0xFFFF;
                card = func_0027DBC0(state, selected & 0xFF, *data & 0x3F);
                output->position = *arg0;
                output->command = 12;
                output->result = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, output->value, 1, 0);
                output->count = 1;
                if (((*data >> 6) & 3) != 3) {
                    output->value = (arg1 << 8) | card;
                } else {
                    output->value = (state << 8) | card;
                }
                func_0027B1B0(arg0, arg3);
                return 0;
            }
        }
        if (func_001E2100(*arg0 >> 8, *arg0 & 0xFF, 4) != 0) {
            func_001E1E70(*arg0 >> 8, *arg0 & 0xFF, 0, 1);
            output->position = *arg0;
            output->command = 14;
            return 0;
        }
        return func_00115850(arg0, arg1, arg2, arg3);
    }
}

s32 func_00117340(void) {
    if (func_0027DD20(func_001DE540(), 3, 2) != 0 ||
        func_0027DD20(func_001DE540(), 3, 0x345) != 0 ||
        func_0024CA40(0, 0, func_001DE540(), 1, 0x2001C, 14) != 0) {
        return 1;
    }
    return 0;
}

s32 func_001173E0(s32 arg0) {
    s32 i;
    u8 n = 0;
    s32 need;
    u8 m;
    s32 j;

    if (func_001DF470(arg0) < 0x5DC) {
        return 0;
    }
    need = func_0027DD20(arg0, 3, 2) & 0xFF;
    if (need > 0) {
        for (i = 0; i < 8; i++) {
            if (func_0024E300(arg0, i, 1) >= 0) {
                n++;
            }
        }
        if (n >= need && 5 - func_001E0150(arg0) >= need) {
            return 1;
        }
    }
    m = 0;
    need = func_0027DD20(arg0, 3, 0) & 0xFF;
    if (need > 0) {
        for (j = 0; j < 8; j++) {
            if (func_0024E300(arg0, j, 1) >= 0) {
                m++;
            }
        }
        if (m >= need && 5 - func_001E0150(arg0) >= need) {
            return 1;
        }
    }
    return 0;
}

s32 func_00117550(s32 arg0) {
    s32 count;

    if (func_001DF470(arg0) < 0x5DC) {
        return 0;
    }
    count = func_0024CA40(0, 0, arg0, 1, 0x2001C, 14);
    count += func_0024CA40(0, 0, arg0, 1, 0x2001C, 14);
    if (count != 0) {
        if (func_001E0150(arg0) >= 4) {
            return 1;
        }
    }
    return 0;
}

s32 func_00117600(s32 arg0) {
    if (func_0024CA40(0, 0, arg0, 1, 0x2001C, 0xE) != 0) {
        return 1;
    }
    return (func_0024CA40(0, 0, arg0, 1, 0x1C, 0xE) != 0) ? 1 : 0;
}

s32 func_00117680(s32 arg0) {
    extern s32 func_001DEE50(s32);
    s32 i;

    if (func_001E0150(arg0) >= 5) {
        return -1;
    }
    if ((func_0027DD20(arg0, 3, 0) > 0 || func_0027DD20(arg0, 3, 2) > 0) &&
        func_0024CA40(0, 0, arg0, 1, 0x179001C, 0xE) == 0) {
        for (i = 0; i < func_001DEE50(arg0); i++) {
            if (func_001DEE00(arg0, i) == 2) {
                return (arg0 << 16) | i;
            }
        }
        for (i = 0; i < func_001DEE50(arg0 == 0 ? 1 : 0); i++) {
            if (func_001DEE00(arg0 == 0 ? 1 : 0, i) == 2) {
                return i | ((arg0 == 0 ? 1 : 0) << 16);
            }
        }
        for (i = 0; i < func_001DEE50(arg0); i++) {
            if (func_001DEE00(arg0, i) == 0) {
                return (arg0 << 16) | i;
            }
        }
        for (i = 0; i < func_001DEE50(arg0 == 0 ? 1 : 0); i++) {
            if (func_001DEE00(arg0 == 0 ? 1 : 0, i) == 0) {
                return i | ((arg0 == 0 ? 1 : 0) << 16);
            }
        }
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/main_005", func_00117870);

static inline s32 min_00117B10(s32 a, s32 b) {
    return (a < b) ? a : b;
}

static inline s32 max_00117B10(s32 a, s32 b) {
    return (a > b) ? a : b;
}

static inline s32 distance_00117B10(s32 x, s32 y) {
    return (max_00117B10(y, 3) - min_00117B10(y, 3)) +
           (max_00117B10(x, 3) - min_00117B10(x, 3));
}

s32 func_00117B10(s32 arg0) {
    s32 temp_s0;
    s32 temp_v0;

    if (arg0 == 0x303) {
        return 1;
    }
    temp_v0 = func_001E36E0(3, 3);
    if (temp_v0 != 0) {
        temp_s0 = func_00250370((void *) temp_v0);
        if (temp_s0 != func_001DE540()) {
            if (distance_00117B10(arg0 >> 8, arg0 & 0xFF) == 1) {
                return 1;
            }
        }
    }
    return 0;
}

s32 func_00117BD0(s32 arg0, s32 arg1) {
    s32 sp20[3];

    func_00254C90(sp20, *(s32 *)((u8 *)func_0026FC90(arg1, 0) + 4));
    if (func_00254890(sp20, arg0) < 0) {
        return 0;
    }
    return 1;
}

s32 func_00117C30(s32 arg0) {
    if (func_001DF470(arg0) > 0x4B0) {
        if (func_001E0150(arg0) >= 4) {
            return 0x2EE;
        } else {
            return 0x5DC;
        }
    } else {
        return 0x9C4;
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
} Req_00117C90;

typedef struct {
    u8 pad0[0x160];
    u16 list[32];    /* 0x160 */
    u8 idx : 5;      /* 0x1A0 */
    u8 pad1A0 : 3;
    u8 pad1A1;
    u16 count;       /* 0x1A2 */
} Work_00117C90;

s32 func_00112B90(void *, void *, s32);
s32 func_00276290(void *, void *, s32);

s32 func_00117C90(s32 arg0, void *arg1) {
    Req_00117C90 req;
    Work_00117C90 *w;
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
        if (func_00112B90(w, &req, arg0) == 0) {
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

INCLUDE_ASM("asm/nonmatchings/main_005", func_00117E60);

s32 func_00118330(void *arg0) {
    u16 key;
    s32 temp_s1;
    s32 kind;

    key = *(u16 *)arg0;
    temp_s1 = func_00250360((s32)key >> 8, key & 0xFF);

    key = *(u16 *)arg0;
    if (func_001DF540((s32)key >> 8, key & 0xFF) != 0) {
        key = *(u16 *)arg0;
        if (func_001E2100((s32)key >> 8, key & 0xFF, 0) == 0) {
            key = *(u16 *)arg0;
            if (key != 0xFFFF) {
                if ((key & 0xFF) == 0) {
                    if (*(s32 *)((u8 *)arg0 + 8) == -1) {
                        if (func_0027BBC0((s32)key >> 8, key & 0xFF, 0) == 1) {
                            if (func_001DE6D0((s32)(*(u16 *)arg0) >> 8) == 1) {
                                *(u16 *)((u8 *)arg0 + 4) = 0x50A;
                            } else {
                                *(u16 *)((u8 *)arg0 + 4) = 0x5FF;
                            }
                        } else {
                            if (func_001DE6D0((s32)(*(u16 *)arg0) >> 8) == 1) {
                                *(u16 *)((u8 *)arg0 + 4) = 0xA05;
                            } else {
                                *(u16 *)((u8 *)arg0 + 4) = 0xFF05;
                            }
                        }
                    }
                } else {
                    kind = func_001E0700((s32)key >> 8, key & 0xFF) >> 5;
                    switch (kind) {
                    case 0:
                        func_001188F0(arg0, 1);
                        break;
                    case 3:
                        func_00118F50(arg0);
                        break;
                    case 4:
                    case 5:
                        *(u16 *)((u8 *)arg0 + 4) = 0x5FF;
                        break;
                    case 2:
                        func_0027CA50(arg0, 3, 0, func_0011AA10(temp_s1) & 0xFF);
                        break;
                    default:
                        *(u16 *)((u8 *)arg0 + 4) = 0x5FF;
                        break;
                    }
                }
                return 1;
            }
        }
    }
    return 0;
}

s32 func_00118510(u16 *arg0, s32 arg1, s32 arg2) {
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
    func_00118330(arg0 + idx * 8);
    if (((arg0[idx * 8 + 2] >> 8) & 0xFF) == 10) {
        if (func_001DE6D0(arg1) == 1 && func_00119300(pos, arg1, arg2) >= 0) {
            return pos | 0x10000;
        }
        if (func_0027B9B0(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (func_001E2100(arg1, 0, 0) == 0) {
        if (func_0027B9B0(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (func_001DE6D0(arg1) == 1 && func_00119300(pos, arg1, arg2) >= 0) {
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

typedef struct {
    u16 card;
    u8 flag;
    u8 pad;
} Slot_001188F0;

typedef struct {
    u16 coordinates;
    u8 pad2[2];
    u16 state;
    u8 pad6[2];
    union {
        u32 word;
        struct {
            u16 low;
            u16 high;
        } halves;
    } data;
} Entry_001188F0;

void func_001188F0(void *arg0, s32 arg1) {
    extern s32 func_0027B200();
    extern void func_0027E770();
    extern s32 func_00118B60();
    Entry_001188F0 *entry = arg0;
    s32 side;
    s32 player;
    s32 other;
    s32 pos;
    s32 otherPos;
    s32 i;
    u8 work[0x70];
    Slot_001188F0 list[22];
    s16 countA;
    s16 countB;

    if (func_001DF540(entry->coordinates >> 8, entry->coordinates & 0xFF) != 0) {
        side = func_0024DE70(entry->coordinates >> 8, entry->coordinates & 0xFF);
        other = (side == 0 ? 1 : 0) << 8;
        pos = func_001E1090(entry->coordinates >> 8, entry->coordinates & 0xFF);
        otherPos = func_001E1090(other >> 8, other & 0xFF);
        player = func_001DF540(entry->coordinates >> 8, entry->coordinates & 0xFF);
        for (i = 0; i < 22; i++) {
            list[i].card = 0xFFFF;
            list[i].flag = 0xFF;
        }
        if (arg1 != 0) {
            if (func_0027B200(entry->coordinates >> 8, entry->coordinates & 0xFF,
                              pos & 0xFF, pos >> 8, other >> 8, other & 0xFF,
                              otherPos & 0xFF, otherPos >> 8, (u8)3) > 0) {
                entry->state = 0x2FF;
                entry->data.word = (other << 16) | entry->data.halves.low;
                return;
            }
        }
        func_0027E770(work);
        countB = 0;
        countA = 0;
        i = 1;
        while (1) {
            switch (func_00118B60(entry, 0, player, pos & 0xFF, pos >> 8,
                                  func_0024DE70(entry->coordinates >> 8, entry->coordinates & 0xFF) == 0 ? 1 : 0,
                                  (u8)i, func_0011AA10(side), list, (u16)0, &countA, &countB, (u8)3, work)) {
            case 3:
                entry->state = 0x6FF;
                entry->data.word = (pos << 16) | entry->data.halves.low;
                return;
            case 2:
                entry->state = 0x3FF;
                entry->data.word = (pos << 16) | entry->data.halves.low;
                return;
            case 1:
                return;
            case 0:
                entry->state = 0x5FF;
                return;
            default:
                i++;
                break;
            }
            if (i > 3) {
                break;
            }
        }
        func_00118BC0(arg0);
    }
}

void func_00118B60(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28) {
    func_0027DE20(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
                 arg_sp0, arg_sp8, arg_sp10, arg_sp18, arg_sp20,
                 0, 0x5DC, arg_sp28);
}

typedef struct {
    u16 id;
    u16 pad2;
    u16 state;
    u16 pad6;
    union {
        u32 word;
        u16 low;
    } data;
} State_00118BC0;

void func_00118BC0(void *arg0) {
    State_00118BC0 *state = arg0;
    s32 new_type;
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_s1;
    s32 temp_s1_2;
    s32 temp_s2;
    s32 temp_v0_2;
    u16 temp_v0;

    temp_s1 = func_001DE540();
    temp_v0 = state->id;
    temp_s2 = func_001E1090((s32) temp_v0 >> 8, temp_v0 & 0xFF);
    temp_s1_2 = func_00118DD0(temp_s1);
    temp_v0_2 = func_00118E90(temp_s1);
    temp_a2 = temp_s2 >> 8;
    switch (temp_a2) {
    case 0:
        if (temp_s2 == temp_s1_2) {
            state->state = 0xFFF;
        } else {
            state->state = 0x6FF;
            state->data.word = (temp_s1_2 << 16) | state->data.low;
        }
        break;
    case 6:
        if (temp_s2 == temp_v0_2) {
            state->state = 0x10FF;
        } else {
            state->state = 0x6FF;
            state->data.word = (temp_v0_2 << 16) | state->data.low;
        }
        break;
    default:
        temp_a1 = ((s32) state->state >> 8) & 0xFF;
        if ((temp_a1 != 0xF) && (temp_a1 != 0x10)) {
            new_type = (temp_a2 < 4) ? 0xF : 0x10;
            state->state = (new_type << 8) | 0xFF;
            state->data.word = state->data.low | 0xFFFF0000;
        }
        break;
    }
}

s32 func_00118CE0(s32 arg0, s32 arg1) {
    s32 index;
    s32 row;
    s32 low;
    s32 high;
    s32 slot;

    switch ((u8)arg1) {
    case 0:
        row = 2;
        break;
    case 1:
        row = 4;
        break;
    case 2:
        row = 0;
        break;
    case 3:
    default:
        row = 6;
        break;
    }
    index = 1;
    while (1) {
        slot = func_001E3790(row, index);
        if (slot >= 0) {
            high = slot >> 8;
            low = slot & 0xFF;
            if (arg0 == func_00250360(high, low) &&
                (func_001E0700(high, low) >> 5) == 0) {
                return 0;
            }
        }
        index++;
        if (index > 5) {
            return 1;
        }
    }
}

s32 func_00118DD0(s32 arg0) {
    s32 i;

    i = 0;
    do {
        if (func_00118CE0(arg0, (u8)i) != 0) {
            switch (i) {
            case 0:
                return 0x102;
            case 1:
                return 0x104;
            case 2:
                return 0x100;
            case 3:
            default:
                return 0x106;
            }
        }
        i++;
    } while (i < 4);
    return -1;
}

s32 func_00118E90(s32 arg0) {
    s32 i = 0;

    do {
        if (func_00118CE0(arg0, (u8)i) == 0) {
            switch (i) {
            case 0:
                return 0x602;
            case 1:
                return 0x604;
            case 2:
                return 0x600;
            case 3:
            default:
                return 0x606;
            }
        }
        i++;
    } while (i < 4);

    return -1;
}

typedef struct {
    u16 position;
    u8 flag;
    u8 pad;
} Slot_00118F50;


void func_00118F50(void *arg0) {
    u8 work[112];
    Slot_00118F50 slots[22];
    s16 c;
    s16 b;
    u16 a;
    s32 i;
    s32 player;
    s32 position;
    s32 owner;
    s32 state;
    s32 result;
    u16 *record = arg0;
    extern s32 func_002770E0();
    extern void func_0027E770();

    if (func_001DF540((s32) record[0] >> 8, record[0] & 0xFF) != 0) {
        player = func_0024DE70((s32) record[0] >> 8, record[0] & 0xFF);
        position = func_001E1090((s32) record[0] >> 8, record[0] & 0xFF);
        owner = func_001DF540((s32) record[0] >> 8, record[0] & 0xFF);
        record[2] = 0xBFF;
        for (i = 0; i < 22; i++) {
            slots[i].position = 0xFFFF;
            slots[i].flag = 0xFF;
        }
        func_0027E770(work);
        a = 0;
        b = 0;
        c = 0;
        state = 0;
        for (i = 1; i < 3; i++) {
            state = func_002770E0(state, owner, position & 0xFF, position >> 8,
                                  func_0024DE70((s32) record[0] >> 8, record[0] & 0xFF) == 0 ? 1 : 0, (u8) i, 0,
                                  func_0011AA10(player), slots, &a, &c, &b, work);
            result = func_00277CD0((s32) record[0] >> 8, record[0] & 0xFF, position & 0xFF, position >> 8,
                                   slots, 3, 0x1F, 1, 2, 0, func_0011AA10(player), a, 1);
            if (result >= 0) {
                *(u32 *) (record + 4) = (result << 16) | record[4];
                return;
            }
            result = func_00277CD0((s32) record[0] >> 8, record[0] & 0xFF, position & 0xFF, position >> 8,
                                   slots, 3, 0x1F, 0, 2, 0, func_0011AA10(player), a, 1);
            if (result >= 0) {
                *(u32 *) (record + 4) = (result << 16) | record[4];
                return;
            }
        }
        a = 0;
        b = 0;
        c = 0;
        state = 0;
        for (i = 1; i < 3; i++) {
            state = func_002770E0(state, owner, position & 0xFF, position >> 8,
                                  func_0024DE70((s32) record[0] >> 8, record[0] & 0xFF), (u8) i, 0,
                                  func_0011AA10(player), slots, &a, &c, &b, work);
            result = func_002774F0(position & 0xFF, position >> 8, slots, 3, 0x22, 2, 2, a);
            if (result >= 0) {
                *(u32 *) (record + 4) = (result << 16) | record[4];
                return;
            }
            result = func_002774F0(position & 0xFF, position >> 8, slots, 3, 0x1F, 1, 2, a);
            if (result >= 0) {
                *(u32 *) (record + 4) = (result << 16) | record[4];
                return;
            }
            result = func_002774F0(position & 0xFF, position >> 8, slots, 3, 0x1F, 0, 2, a);
            if (result >= 0) {
                *(u32 *) (record + 4) = (result << 16) | record[4];
                return;
            }
        }
        record[2] = 0x5FF;
    }
}

typedef struct Temp_00119300 {
    u8 data[0x3C];
    u16 value;
    u8 padding[0x20];
} Temp_00119300;


s32 func_00119300(s32 arg0, s32 arg1, s32 arg2) {
    extern s32 func_00278890();
    Temp_00119300 temp;
    s32 color;
    s32 index;

    *(s16 *) (u8 *) arg2 = (s16) arg0;
    if (func_001DE6D0(arg1) == 0) {
        return -1;
    }

    if (func_00278890(arg1, 0) == 5 && func_00278890(arg1, 1) == 5) {
        return -1;
    }

    if ((index = func_00119A40(arg1, &temp)) < 0) {
        return -1;
    } else {
        ((u8 *) arg2)[2] = 10;
        *(s32 *) ((u8 *) arg2 + 0xC) = 0;
        color = func_001E1090(arg0 >> 8, arg0 & 0xFF);

        if (index == 0) {
            if (func_0011A0D0(arg1, (u8 *) arg2, &temp) >= 0) {
                if (func_00276F10(&temp, color & 0xFF, color >> 8,
                        arg1 == 0 ? 1 : 0,
                        3, 0x1F, 2, 2, 0, func_0011AA10(arg1)) < 0) {
                    if (func_001E0150(arg1) >= 6) {
                        goto fallback;
                    }
                    index = func_00119520(arg1, index & 0xFF, &temp);
                    if (index < 0) {
                        return -1;
                    }
                    *(s16 *) ((u8 *) arg2 + 4) = (s16) index;
                    return 1;
                }

                index = func_00119520(arg1, index & 0xFF, &temp);
                if (index < 0) {
                    return -1;
                }
                *(s16 *) ((u8 *) arg2 + 4) = (s16) index;
                return 1;
            }
        } else {
            func_00276F10(&temp, color & 0xFF, color >> 8,
                    arg1 == 0 ? 1 : 0,
                    3, 0x1F, 2, 2, 0, func_0011AA10(arg1));
        }

    fallback:
        if (func_00119D30(arg1, (u8 *) arg2, &temp, temp.value) < 0) {
            return -1;
        }
        index = func_00119520(arg1, index & 0xFF, &temp);
        if (index < 0) {
            return -1;
        }
        *(s16 *) ((u8 *) arg2 + 4) = (s16) index;
        return 1;
    }
}

typedef struct Nibbles_00119520 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_00119520;


static inline s32 direction_00119520(s32 player) {
    s32 i = 0;
    do {
        if (func_00118CE0(player, (u8)i) != 0) {
            switch (i) {
            case 0: return 0x102;
            case 1: return 0x104;
            case 2: return 0x100;
            case 3:
            default: return 0x106;
            }
        }
        i++;
    } while (i < 4);
    return -1;
}

s32 func_00119520(s32 arg0, s32 arg1, void *arg2) {
    extern s32 func_0011A4C0();
    extern s32 func_00278510();
    extern s32 func_0027A130();
    extern s32 func_002792C0(s32, s32, s32, s32, s32, s32, u16, u8);
    Nibbles_00119520 path[12];
    s32 init;
    Nibbles_00119520 *p;

    if (arg2 == NULL) {
        return -1;
    }
    p = path;
    init = 0;
    do {
        p->low = p->high = 15;
        init++;
        p++;
    } while (init < 12);
    if ((u8)(*((u8 *)arg2 + 0x3E) >> 5) == 0) {
        s32 candidate;
        s32 target;
        s32 y;
        s32 x;
        s32 i;
        s32 ref_y;
        s32 ref_x;
        s32 best_candidate;
        s32 best_cost;
        s32 cost;
        s32 position;

        position = func_001E1090(arg0, 0);
        target = func_00276F10(arg2, position & 0xFF, position >> 8,
                             arg0 == 0 ? 1 : 0, 3, 31, 2, 2, 0,
                             func_0011AA10(arg0));
        if (target >= 0) {
            best_cost = 255;
            best_candidate = 65535;
            position = func_001E1090(target >> 8, target & 0xFF);
            i = 0;
            ref_y = position >> 8;
            ref_x = position & 0xFF;
            do {
                if ((candidate = func_0011A4C0(arg0, i)) >= 0) {
                    x = candidate & 0xFF;
                    y = candidate >> 8;
                    if (func_001E22B0(x, y) != 8 &&
                        (func_001E22B0(x, y) != 9 ||
                         func_0024FE40(arg2, x, y) != 1) &&
                        func_001E36E0(x, y) == 0) {
                        if (func_00278510(arg2, target, func_0011AA10(arg0),
                                          ref_x, ref_y, 0) > 0) {
                            cost = func_0027A130(arg2, path, x, y,
                                                ref_x, ref_y, target, 0, 3,
                                                (u16)func_0011AA10(arg0));
                        } else {
                            cost = func_002792C0((s32)arg2, (s32)path, x, y,
                                                ref_x, ref_y, target, 3);
                        }
                        if (func_0027AFC0((u8 *)path) > 0 &&
                            cost < best_cost && cost >= 0) {
                            best_cost = cost;
                            best_candidate = candidate;
                        }
                    }
                }
                i++;
            } while (i < 8);
            if (best_candidate != 65535) {
                return best_candidate;
            }
            best_candidate = -1;
            return best_candidate;
        } else {
            s32 y2;
            s32 x2;
            s32 i2;
            s32 best_cost2;
            s32 candidate2;
            s32 best_candidate2;
            s32 direction;
            s32 occupied;
            s32 cost2;
            s32 ref_y2;
            s32 ref_x2;

            direction = direction_00119520(arg0);
            best_cost2 = 14;
            best_candidate2 = -1;
            i2 = 0;
            ref_y2 = direction >> 8;
            ref_x2 = direction & 0xFF;
            do {
                if ((candidate2 = func_0011A4C0(arg0, i2)) >= 0) {
                    x2 = candidate2 & 0xFF;
                    y2 = candidate2 >> 8;
                    if (func_001E22B0(x2, y2) != 8 &&
                        (func_001E22B0(x2, y2) != 9 ||
                         func_0024FE40(arg2, x2, y2) != 1) &&
                        func_001E3790(x2, y2) < 0) {
                        occupied = func_001E3790(x2, y2);
                        if (occupied < 0) {
                            occupied = 65535;
                        }
                        cost2 = func_002792C0((s32)arg2, (s32)path, x2, y2,
                                             ref_x2, ref_y2, occupied, 7);
                        if (cost2 < best_cost2 && cost2 >= 0) {
                            best_candidate2 = candidate2;
                            best_cost2 = cost2;
                        }
                    }
                }
                i2++;
            } while (i2 < 8);
            if (best_cost2 < 14) {
                return best_candidate2;
            }
        }
    } else {
        s32 y3;
        s32 x3;
        s32 i3;
        s32 selected;
        s32 candidate3;

        selected = -1;
        i3 = 0;
        do {
            if ((candidate3 = func_0011A4C0(arg0, i3)) >= 0) {
                x3 = candidate3 & 0xFF;
                y3 = candidate3 >> 8;
                if (func_001E22B0(x3, y3) != 8 &&
                    func_001E22B0(x3, y3) != 9 &&
                    func_001E3790(x3, y3) < 0 && y3 < 8) {
                    selected = candidate3;
                }
            }
            i3++;
        } while (i3 < 8);
        if (selected >= 0) {
            return selected;
        }
    }
    return -1;
}

static inline s32 find_slot_00119A40(s32 arg0) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (func_00118CE0(arg0, (u8)i) == 0) {
            return i;
        }
    }
    return -1;
}

s32 func_00119A40(s32 arg0, void *arg1) {
    s32 cards[8];
    u8 scratch[32];
    u8 type0;
    u8 type1;
    s32 i;
    s32 result;

    extern s32 func_00278890();

    type0 = func_00278890(arg0, 0);
    type1 = func_00278890(arg0, 1);
    if (arg1 == NULL) {
        return -1;
    }

    func_0026FD30(arg0, cards);
    if (type0 == 5) {
        if (func_00119D30(arg0, scratch, arg1, 999) >= 0) {
            return 1;
        } else {
            return -1;
        }
    } else if (type1 == 5) {
        for (i = 0; i < func_0026FE20(arg0); i++) {
            if ((func_0026FCE0(cards[i]) >> 5) == 0 &&
                func_0026FB10(arg0, cards[i]) == 1) {
                func_001DCD70(arg1, cards[i]);
                return 0;
            }
        }
        return -1;
    } else {
        result = func_00119F30(arg0, scratch, (s32)arg1);
        if (result >= 0) {
            return func_00119D30(arg0, scratch, arg1, result);
        }

        i = find_slot_00119A40(arg0);

        if (i >= 0) {
            for (i = 0; i < func_0026FE20(arg0); i++) {
                if ((func_0026FCE0(cards[i]) >> 5) == 0 &&
                    func_0026FB10(arg0, cards[i]) == 1) {
                    return 0;
                }
            }
            return func_00119D30(arg0, scratch, arg1, 999);
        } else {
            for (i = 0; i < func_0026FE20(arg0); i++) {
                if ((func_0026FCE0(cards[i]) >> 5) == 0 &&
                    func_0026FB10(arg0, cards[i]) == 1) {
                    func_001DCD70(arg1, cards[i]);
                    return 0;
                }
            }
            result = func_00119D30(arg0, scratch, arg1, 999);
            if (result >= 0) {
                return result;
            }
            return -1;
        }
    }
}

s32 func_00119D30(s32 arg0, u8 *arg1, void *arg2, s32 arg3) {
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

typedef struct Info_00119F30 {
    u8 pad0[6];
    u8 slots[5];
} Info_00119F30;

s32 func_00119F30(s32 arg0, void *arg1, s32 arg2) {
    Info_00119F30 *info = arg1;
    u16 cards[22];
    s32 ids[8];
    s32 i;
    s32 card;
    s32 type;

    for (i = 0; i < 22; i++) {
        cards[i] = 0xFFFF;
    }
    func_0024C910(arg0, 2, cards);
    func_0026FD30(arg0, ids);
    if (arg2 == 0) {
        return -1;
    }
    for (i = 0; i < 5; i++) {
        info->slots[i] = 0xFF;
    }
    card = func_0027B650(cards);
    if (card >= 0) {
        switch (func_001E0700(card >> 8, card & 0xFF) & 0x1F) {
        case 0xE:
            type = 0x2D2;
            break;
        case 2:
            type = 0x2D1;
            break;
        case 0x12:
            type = 0x2D4;
            break;
        default:
            type = 0x3E7;
            break;
        }
        if (type != 0x3E7) {
            for (i = 0; i < func_0026FE20(arg0); i++) {
                if (type == ids[i]) {
                    info->slots[0] = i;
                }
            }
            return type;
        }
    }
    return -1;
}

typedef struct Info_0011A0D0 {
    u8 pad00[8];
    u16 x;
    s16 y;
} Info_0011A0D0;

typedef struct Sprite_0011A0D0 {
    Info_0011A0D0 *info;
    u8 pad04[0x34];
    s16 x;
    s16 y;
} Sprite_0011A0D0;

u16 *func_00278A90(s32, u16 *, s32, s32, s32, s16 *, s16 *);
s32 func_00278F10(s32, u16 *, s32, s32);

s32 func_0011A0D0(s32 arg0, u8 *arg1, void *arg2) {
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
                            func_0011A2F0(arg0, *node, entries);
                            func_00278DD0((u8 *)*node + 2, arg1 + 6);
                            func_001DCD70(arg2, **node);
                            ((Sprite_0011A0D0 *)arg2)->x = (value >> 16) - (((Sprite_0011A0D0 *)arg2)->info->x & 0x1FFF);
                            ((Sprite_0011A0D0 *)arg2)->y = (value & 0xFFFF) - (((Sprite_0011A0D0 *)arg2)->info->y & 0x1FFF);
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
} Info_0011A2F0;

void func_0011A2F0(s32 arg0, void *arg1, s32 *arg2) {
    Info_0011A2F0 *info = arg1;
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
                    if ((cost & 0xFFFF) + (cost >> 16) * 2 < 0xDAD && func_0026FC10(card) == 2 &&
                        (u16)func_002789F0(info->id, (u16)card) == 0x3E7) {
                        func_00278D20(info->values, buf[i]);
                    }
                }
            }
        }
    }
}

void func_0011A4C0(void) {
    func_0024E410();
}

typedef struct {
    u8 low : 4;
    u8 high : 4;
} Flags_0011A4D0;

typedef struct {
    u16 id;
    u8 action;
    u8 pad3;
    u16 position;
    u8 pad6[6];
    s32 value;
    u8 mode;
} Output_0011A4D0;

s32 func_002464F0(s32, s32, s32);
s32 func_00276CC0(s32, s32, s32, s32, s32, s32);
s32 func_0027BE10(s32, s32, s32, s32, s32);

s32 func_0011A4D0(u16 *arg0, s32 arg1, void *arg2, u8 arg3) {
    extern s32 func_00279C40(s32, s32, s32, s32, s32, s32, void *, u8);
    s32 position;
    u8 upperX;
    u8 flag;
    Flags_0011A4D0 cells[12];
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
    Output_0011A4D0 *out = arg2;

    position = func_001E1090(*arg0 >> 8, *arg0 & 0xFF);
    i = 0;
    do {
        cells[i].low = cells[i].high = 15;
        i++;
    } while (i < 12);

    {
        u16 value = (u16)func_0011AA10(arg1);
        originalX = position & 0xFF;
        originalY = position >> 8;
        if (func_00276CC0(originalX, originalY, *arg0, 3, value, 0) == 0) {
            out->id = *arg0;
            out->action = 6;
            out->position = position;
            out->mode = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, out->position, 1, 0);
            out->value = func_0011C140(*arg0 >> 8, *arg0 & 0xFF, (u32 *)arg0);
            func_0011C3E0(arg0, arg3);
            return 0;
        } else {
            result = func_002464F0(func_001DF540(*arg0 >> 8, *arg0 & 0xFF), originalX, originalY);
            if (result == 0) {
                out->id = *arg0;
                out->action = 6;
                out->position = position;
                out->mode = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, out->position, 1, 0);
                out->value = func_0011C140(*arg0 >> 8, *arg0 & 0xFF, (u32 *)arg0);
                func_0011C3E0(arg0, arg3);
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
                                value = (u16)func_0011AA10(arg1);
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
                    out->value = func_0011C140(*arg0 >> 8, *arg0 & 0xFF, (u32 *)arg0);
                } else {
                    out->id = *arg0;
                    out->action = 6;
                    out->position = position;
                    out->mode = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, out->position, 1, 0);
                    out->value = func_0011C140(*arg0 >> 8, *arg0 & 0xFF, (u32 *)arg0);
                }
                func_0011C3E0(arg0, arg3);
            }
        }
    }
    return 0;
}

s32 func_0011AA10(s32 arg0) {
    if (func_001DF470(arg0) > 0x5DC) {
        if (func_001E0150(arg0) >= 3) {
            return 0;
        } else {
            return 0;
        }
    }
    return 0;
}

typedef struct Source_0011AA70 {
    u16 position;
    u8 pad2[6];
    u32 targets;
} Source_0011AA70;

typedef struct Output_0011AA70 {
    u16 position;
    u8 mode;
    u8 pad3;
    u16 target;
    u8 pad6[6];
    s32 flag;
    u8 value;
} Output_0011AA70;

typedef struct Position_0011AA70 {
    u8 x : 4;
    u8 y : 4;
} Position_0011AA70;

s32 func_002464F0(s32, s32, s32);
s32 func_00276CC0(s32, s32, s32, s32, s32, s32);

static inline u32 target_0011AA70(void *arg0, u8 which) {
    Source_0011AA70 *source = arg0;
    if (which == 1) {
        return (u16)(source->targets >> 16);
    }
    return *(u16 *)&source->targets;
}

static inline s32 penalty_0011AA70(s32 object) {
    if (func_001DF470(object) > 0x5DC) {
        if (func_001E0150(object) >= 3) {
            return 0;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}

s32 func_0011AA70(void *arg0, s32 arg1, void *arg2, u8 arg3) {
    extern void func_0027A090();
    s32 sourceTarget;
    s32 count;
    s32 sourceY;
    s32 sourceX;
    s32 selectedFlag;
    Position_0011AA70 positions[12];
    s32 flag;
    s32 otherTarget;
    s32 j;
    Position_0011AA70 *walk;
    s32 object;
    u32 targetXWord;
    u32 targetYWord;
    Source_0011AA70 *source = arg0;
    Output_0011AA70 *output = arg2;

    targetXWord = target_0011AA70(arg0, arg3);
    targetYWord = target_0011AA70(arg0, arg3);
    if (func_001DF540(targetYWord >> 8, targetXWord & 0xFF) == 0) {
        func_0027B1B0(arg0, 1);
        return -1;
    }

    flag = func_0011C140(source->position >> 8, source->position & 0xFF, arg0);
    sourceTarget = func_001E1090(source->position >> 8, source->position & 0xFF);
    targetXWord = target_0011AA70(arg0, arg3);
    targetYWord = target_0011AA70(arg0, arg3);
    otherTarget = func_001E1090(targetYWord >> 8, targetXWord & 0xFF);
    walk = positions;
    j = 0;
    do {
        walk->x = walk->y = 15;
        j++;
        walk++;
    } while (j < 12);

    object = func_001DF540(source->position >> 8, source->position & 0xFF);
    sourceX = sourceTarget & 0xFF;
    sourceY = sourceTarget >> 8;
    if (func_002464F0(object, sourceX, sourceY) == 0) {
        s32 cost;
        output->position = source->position;
        output->mode = 6;
        output->target = sourceTarget;
        cost = func_00276CC0(sourceX, sourceY, arg1, 3, 1,
                            (u8)penalty_0011AA70(arg1));
        if (cost >= func_001E0290(source->position >> 8, source->position & 0xFF, 0)) {
            output->value = func_0027E360(source->position >> 8, source->position & 0xFF,
                                        output->target, 1, 0);
        } else {
            output->value = func_0027E360(source->position >> 8, source->position & 0xFF,
                                        output->target, 0, 0);
        }
        func_0011C3E0(arg0, arg3);
    } else {
        s32 targetY;
        s32 targetX;
        Position_0011AA70 *current;
        s32 i;
        s32 bestCost;
        s32 selected;
        s32 penalty;
        u16 position;

        penalty = penalty_0011AA70(arg1);
        position = source->position;
        func_0027A090(position >> 8, position & 0xFF, positions,
                      sourceX, sourceY, targetX = otherTarget & 0xFF,
                      targetY = otherTarget >> 8,
                      target_0011AA70(arg0, arg3), 0, 30, (u16)penalty);
        count = func_0027AFC0((u8 *)positions);
        selected = 0xFF;
        if (count > 0) {
            selectedFlag = 0;
            bestCost = 0xFFFF;
            for (i = 0; i < count; i++) {
                s32 state = func_0011C2E0(source->position >> 8, source->position & 0xFF,
                                          sourceX, sourceY, targetX, targetY);
                if (state == 1) {
                    Position_0011AA70 *forcedPosition = &positions[i];
                    selected = i;
                    selectedFlag = 1;
                    i = count;
                    forcedPosition->x = targetX;
                    forcedPosition->y = targetY;
                } else {
                    s32 cost;
                    s32 penalty = penalty_0011AA70(arg1);
                    current = &positions[i];
                    cost = func_00276CC0(current->x, current->y, arg1, 3, 1,
                                        (u8)penalty);
                    if (cost < bestCost) {
                        bestCost = cost;
                        selected = i;
                    } else if (cost == bestCost) {
                        if (((targetX < current->x ? current->x : targetX) -
                             (current->x < targetX ? current->x : targetX)) +
                            ((targetY < current->y ? current->y : targetY) -
                             (current->y < targetY ? current->y : targetY)) <
                            ((targetX < positions[selected].x ? positions[selected].x : targetX) -
                             (positions[selected].x < targetX ? positions[selected].x : targetX)) +
                            ((targetY < positions[selected].y ? positions[selected].y : targetY) -
                             (positions[selected].y < targetY ? positions[selected].y : targetY))) {
                            bestCost = cost;
                            selected = i;
                        }
                    }
                }
            }
        } else {
            output->position = source->position;
            output->mode = 6;
            output->target = sourceTarget;
            output->flag = flag;
            output->value = func_0027E360(source->position >> 8, source->position & 0xFF,
                                        output->target, 0, 0);
            func_0027B1B0(arg0, arg3);
            return 0;
        }
        if (selected != 0xFF) {
            output->position = source->position;
            output->mode = 6;
            output->target = (positions[selected].y << 8) | positions[selected].x;
            output->flag = selectedFlag;
            output->value = func_0027E360(source->position >> 8, source->position & 0xFF,
                                        output->target, 0, 0);
            func_0011C3E0(arg0, arg3);
            return 0;
        } else {
            output->position = source->position;
            output->mode = 6;
            output->target = sourceTarget;
            output->flag = selectedFlag;
            output->value = func_0027E360(source->position >> 8, source->position & 0xFF,
                                        output->target, 0, 0);
            func_0011C3E0(arg0, arg3);
            return 0;
        }
    }
    return 0;
}

typedef struct Input_0011B0E0 {
    u16 position;
    u8 pad2[6];
    u32 destination;
} Input_0011B0E0;

typedef struct Output_0011B0E0 {
    u16 position;
    u8 action;
    u8 pad3;
    u16 destination;
    u8 pad6[10];
    s8 result;
} Output_0011B0E0;

typedef struct Position_0011B0E0 {
    u8 y : 4;
    u8 x : 4;
} Position_0011B0E0;

s32 func_002464F0(s32, s32, s32);
s32 func_00276CC0(s32, s32, s32, s32, s32, s32);

static inline u32 destination_0011B0E0(Input_0011B0E0 *input, u8 mode) {
    return mode == 1 ? (u32)(u16)(input->destination >> 16) :
                      (u32)*(u16 *)&input->destination;
}

static inline u16 flags_0011B0E0(s32 card) {
    if (func_001DF470(card) > 0x5DC) {
        if (func_001E0150(card) >= 3) {
            return 0;
        }
        return 0;
    }
    return 0;
}

static inline s32 closer_0011B0E0(Position_0011B0E0 *position,
                                 Position_0011B0E0 *previous, s32 x, s32 y) {
    s32 oldMinX = previous->x < x ? previous->x : x;
    s32 oldMaxX = x < previous->x ? previous->x : x;
    s32 oldMinY = previous->y < y ? previous->y : y;
    s32 oldMaxY = y < previous->y ? previous->y : y;
    s32 minX = position->x < x ? position->x : x;
    s32 maxX = x < position->x ? position->x : x;
    s32 minY = position->y < y ? position->y : y;
    s32 maxY = y < position->y ? position->y : y;
    return (maxY - minY) + (maxX - minX) <
           (oldMaxY - oldMinY) + (oldMaxX - oldMinX);
}

static inline void fallback_0011B0E0(Input_0011B0E0 *input, Output_0011B0E0 *output, s32 position) {
    output->position = input->position;
    output->action = 6;
    output->destination = position;
    output->result = func_0027E360(input->position >> 8, input->position & 0xFF,
                                 output->destination, 1, 0);
}

s32 func_0011B0E0(void *arg0, s32 arg1, void *arg2, u8 arg3) {
    extern void func_0027A090();
    Position_0011B0E0 positions[12];
    Position_0011B0E0 *position;
    Input_0011B0E0 *input = arg0;
    Output_0011B0E0 *output = arg2;
    s32 origin;
    s32 target;
    s32 targetY;
    s32 originX;
    s32 originY;
    s32 sourceCard;
    s32 count;
    s32 best;
    s32 bestScore;
    s32 i;

    if (func_001DF540(destination_0011B0E0(input, arg3) >> 8,
                     destination_0011B0E0(input, arg3) & 0xFF) == 0) {
        func_0027B1B0(input, 1);
        return -1;
    }
    origin = func_001E1090(input->position >> 8, input->position & 0xFF);
    target = func_001E1090(destination_0011B0E0(input, arg3) >> 8,
                          destination_0011B0E0(input, arg3) & 0xFF);
    if (destination_0011B0E0(input, arg3) == 0xFFFF) {
        fallback_0011B0E0(input, output, origin);
        return 0;
    }
    sourceCard = func_001DF540(input->position >> 8, input->position & 0xFF);
    originY = origin & 0xFF;
    originX = origin >> 8;
    if (func_002464F0(sourceCard, originY, originX) == 0 ||
        func_0027BBC0(input->position >> 8, input->position & 0xFF, 0) == 1) {
        fallback_0011B0E0(input, output, origin);
        return 0;
    }
    position = positions;
    {
        s32 j = 0;
        Position_0011B0E0 *p = position;
        for (; j < 12; j++) {
            p->y = p->x = 15;
            p++;
        }
    }
    {
        u16 flags = flags_0011B0E0(arg1);
        targetY = target & 0xFF;
        target >>= 8;
        func_0027A090(input->position >> 8, input->position & 0xFF, positions,
                     originY, originX, targetY, target,
                     destination_0011B0E0(input, arg3), 0, 30, flags);
    }
    count = func_0027AFC0((u8 *)positions);
    best = 0xFF;
    if (count > 0) {
        bestScore = 0;
        for (i = 0; i < count; i++, position++) {
            if (func_001E36E0(position->y, position->x) == 0) {
                s32 score = func_00276CC0(position->y, position->x, arg1,
                                         3, 1, (u8)flags_0011B0E0(arg1));
                if (bestScore < score) {
                    bestScore = score;
                    best = i;
                } else if (score == bestScore &&
                           closer_0011B0E0(position, &positions[best], target, targetY)) {
                    bestScore = score;
                    best = i;
                }
            }
        }
    } else {
        fallback_0011B0E0(input, output, origin);
        return 0;
    }
    if (best != 0xFF) {
        output->position = input->position;
        output->action = 6;
        output->destination = (positions[best].x << 8) | positions[best].y;
        output->result = func_0027E360(input->position >> 8, input->position & 0xFF,
                                     output->destination, 0, 0);
    } else {
        fallback_0011B0E0(input, output, origin);
        return 0;
    }
    return 0;
}

typedef struct Input_0011B680 {
    u16 position;
    u16 unk2;
    u16 command;
    u16 unk6;
    union {
        u32 word;
        u16 low;
    } targets;
} Input_0011B680;

typedef struct Output_0011B680 {
    u16 position;
    u8 action;
    u8 unk3;
    u16 destination;
    u8 unk6[6];
    s32 value;
    u8 state;
} Output_0011B680;

typedef struct Position_0011B680 {
    u8 x : 4;
    u8 y : 4;
} Position_0011B680;

s32 func_002464F0(s32, s32, s32);
s32 func_00276CC0(s32, s32, s32, s32, s32, s32);

#define target_0011B680(src, mode) ((mode) == 1 ? \
    (u32)(u16)((src)->targets.word >> 16) : (u32)(src)->targets.low)

static inline s32 option_0011B680(s32 card) {
    if (func_001DF470(card) > 0x5DC) {
        if (func_001E0150(card) >= 3) {
            return 0;
        }
        return 0;
    }
    return 0;
}

#define min_0011B680(a, b) ((a) < (b) ? (u8)(a) : (b))
#define max_0011B680(a, b) ((b) < (a) ? (u8)(a) : (b))
#define distance_0011B680(pos, src, mode) ( \
    (max_0011B680((pos)->x, target_0011B680(src, mode) & 0xFF) - \
     min_0011B680((pos)->x, target_0011B680(src, mode) & 0xFF)) + \
    (max_0011B680((u8)(pos)->y, target_0011B680(src, mode) >> 8) - \
     min_0011B680((u8)(pos)->y, target_0011B680(src, mode) >> 8)))

s32 func_0011B680(u32 *arg0, s32 arg1, u16 *arg2, u8 arg3, u8 arg4) {
    extern s32 func_0027E360(s32, s32, s32, u8, s32);
    extern void func_00279230(s32, s32, void *, s32, s32, s32, s32, s32, u8);
    Position_0011B680 positions[12];
    s32 y;
    s32 bestScore;
    s32 mode;
    s32 current;
    s32 command;

    current = func_001E1090(((Input_0011B680 *)arg0)->position >> 8, ((Input_0011B680 *)arg0)->position & 0xFF);
    mode = arg3;
    if (target_0011B680((Input_0011B680 *)arg0, mode) == 0xFFFF && current == target_0011B680((Input_0011B680 *)arg0, mode)) {
        arg2[0] = ((Input_0011B680 *)arg0)->position;
        ((Output_0011B680 *)arg2)->action = 6;
        arg2[2] = current;
        ((Output_0011B680 *)arg2)->state = func_0027E360(((Input_0011B680 *)arg0)->position >> 8, ((Input_0011B680 *)arg0)->position & 0xFF,
            arg2[2], arg4, 0);
        ((Output_0011B680 *)arg2)->value = func_0011C140(((Input_0011B680 *)arg0)->position >> 8, ((Input_0011B680 *)arg0)->position & 0xFF, arg0);
        func_0011C3E0(arg0, arg3);
        return 0;
    } else {
        command = (((Input_0011B680 *)arg0)->command >> 8) & 0xFF;
        if (command == 15) {
            s32 x = current & 0xFF;
            s32 target;

            y = current >> 8;
            arg2[0] = ((Input_0011B680 *)arg0)->position;
            ((Output_0011B680 *)arg2)->action = 6;
            target = x | (func_00250860(7, y +
                (func_002464F0(func_001DF540(((Input_0011B680 *)arg0)->position >> 8, ((Input_0011B680 *)arg0)->position & 0xFF), x, y) & 15)) << 8);
            arg2[2] = target;
            target = func_001E3790(target_0011B680((Input_0011B680 *)arg0, mode) & 0xFF,
                target_0011B680((Input_0011B680 *)arg0, mode) >> 8);
            if (target < 0) {
                target = 0xFFFF;
            }
            func_00279230(((Input_0011B680 *)arg0)->position >> 8, ((Input_0011B680 *)arg0)->position & 0xFF, positions, x, y,
                arg2[2] & 0xFF, arg2[2] >> 8, (u16)target, 2);
            if (func_0027AFC0((u8 *)positions) == 0) {
                arg2[2] = current;
            }
            ((Output_0011B680 *)arg2)->state = func_0027E360(((Input_0011B680 *)arg0)->position >> 8, ((Input_0011B680 *)arg0)->position & 0xFF,
                arg2[2], arg4, 0);
            ((Output_0011B680 *)arg2)->value = func_0011C140(((Input_0011B680 *)arg0)->position >> 8, ((Input_0011B680 *)arg0)->position & 0xFF, arg0);
            func_0011C3E0(arg0, arg3);
            return 0;
        } else {
            if (command == 16) {
                s32 y2;
                s32 x = current & 0xFF;
                s32 target;

                y2 = current >> 8;
                arg2[0] = ((Input_0011B680 *)arg0)->position;
                ((Output_0011B680 *)arg2)->action = 6;
                target = x | (func_00250860(0, y2 -
                    (func_002464F0(func_001DF540(((Input_0011B680 *)arg0)->position >> 8, ((Input_0011B680 *)arg0)->position & 0xFF), x, y2) & 15)) << 8);
                arg2[2] = target;
                target = func_001E3790(target_0011B680((Input_0011B680 *)arg0, mode) & 0xFF,
                    target_0011B680((Input_0011B680 *)arg0, mode) >> 8);
                if (target < 0) {
                    target = 0xFFFF;
                }
                func_00279230(((Input_0011B680 *)arg0)->position >> 8, ((Input_0011B680 *)arg0)->position & 0xFF, positions, x, y2,
                    arg2[2] & 0xFF, arg2[2] >> 8, (u16)target, 2);
                if (func_0027AFC0((u8 *)positions) == 0) {
                    arg2[2] = current;
                }
                ((Output_0011B680 *)arg2)->state = func_0027E360(((Input_0011B680 *)arg0)->position >> 8, ((Input_0011B680 *)arg0)->position & 0xFF,
                    arg2[2], arg4, 0);
                ((Output_0011B680 *)arg2)->value = func_0011C140(((Input_0011B680 *)arg0)->position >> 8, ((Input_0011B680 *)arg0)->position & 0xFF, arg0);
                func_0011C3E0(arg0, arg3);
                return 0;
            } else {
                Position_0011B680 *p = positions;
                s32 count;
                s32 i;
                s32 best;
                s32 target;
                s32 j;
                Position_0011B680 *init;

                j = 0;
                init = p;
                do {
                    init->x = init->y = 15;
                    init++;
                    j++;
                } while (j < 12);
                target = func_001E3790(target_0011B680((Input_0011B680 *)arg0, mode) & 0xFF,
                    target_0011B680((Input_0011B680 *)arg0, mode) >> 8);
                if (target < 0) {
                    target = 0xFFFF;
                }
                func_00279230(((Input_0011B680 *)arg0)->position >> 8, ((Input_0011B680 *)arg0)->position & 0xFF, positions,
                    current & 0xFF, current >> 8, target_0011B680((Input_0011B680 *)arg0, mode) & 0xFF,
                    target_0011B680((Input_0011B680 *)arg0, mode) >> 8, (u16)target, 7);
                count = func_0027AFC0((u8 *)positions);
                if (count > 0) {
                    best = 0xFF;
                    bestScore = 0xFFFF;
                    for (i = 0; i < count; i++, p++) {
                        s32 score;
                        if (func_001E36E0(p->x, p->y) == 0) {
                            score = func_00276CC0(p->x, p->y, arg1, 3, 1, (u8)option_0011B680(arg1));
                            if (score < bestScore) {
                                bestScore = score;
                                best = i;
                            } else if (score == bestScore) {
                                if (distance_0011B680(p, (Input_0011B680 *)arg0, mode) <
                                    distance_0011B680(&positions[best], (Input_0011B680 *)arg0, mode)) {
                                    bestScore = score;
                                    best = i;
                                }
                            }
                        }
                    }
} else {
                    arg2[0] = ((Input_0011B680 *)arg0)->position;
                    ((Output_0011B680 *)arg2)->action = 6;
                    arg2[2] = current;
                    ((Output_0011B680 *)arg2)->state = func_0027E360(((Input_0011B680 *)arg0)->position >> 8, ((Input_0011B680 *)arg0)->position & 0xFF,
                        arg2[2], arg4, 0);
                    ((Output_0011B680 *)arg2)->value = func_0011C140(((Input_0011B680 *)arg0)->position >> 8, ((Input_0011B680 *)arg0)->position & 0xFF, arg0);
                    func_0011C3E0(arg0, arg3);
                    return 0;
                }
                    if (best != 0xFF) {
                        arg2[0] = ((Input_0011B680 *)arg0)->position;
                        ((Output_0011B680 *)arg2)->action = 6;
                        arg2[2] = (positions[best].y << 8) | positions[best].x;
                        ((Output_0011B680 *)arg2)->state = func_0027E360(((Input_0011B680 *)arg0)->position >> 8, ((Input_0011B680 *)arg0)->position & 0xFF,
                            arg2[2], arg4, 0);
                        ((Output_0011B680 *)arg2)->value = func_0011C140(((Input_0011B680 *)arg0)->position >> 8, ((Input_0011B680 *)arg0)->position & 0xFF, arg0);
                    } else {
                        arg2[0] = ((Input_0011B680 *)arg0)->position;
                        ((Output_0011B680 *)arg2)->action = 6;
                        arg2[2] = current;
                        ((Output_0011B680 *)arg2)->state = func_0027E360(((Input_0011B680 *)arg0)->position >> 8, ((Input_0011B680 *)arg0)->position & 0xFF,
                            arg2[2], arg4, 0);
                        ((Output_0011B680 *)arg2)->value = func_0011C140(((Input_0011B680 *)arg0)->position >> 8, ((Input_0011B680 *)arg0)->position & 0xFF, arg0);
                    }
                    func_0011C3E0(arg0, arg3);
                
            }
        }
    }
    return 0;
}

s32 func_0011C140(s32 arg0, s32 arg1, u32 *arg2) {
    /* really takes (arg0, arg1); the header says (void) */
    s32 func_001E1030();
    u8 info[32];
    u32 *entry;

    if (func_001E2100(arg0, arg1, 4) != 0) {
        return 0;
    }
    switch (func_001E0700(arg0, arg1) >> 5) {
    case 0:
        return 2;
    case 1:
        if (func_0027D830(arg0, arg1, 0, 0, 6, 0) == 5) {
            return 2;
        }
        entry = func_00250740(arg0, arg1, 0);
        if (entry == NULL) {
            return 2;
        }
        switch (*entry >> 8) {
        case 2:
            if ((u16)(arg2[2] >> 16) == func_001E1090(arg0, arg1)) {
                return 1;
            }
            break;
        case 0xD:
            return 1;
        default:
            if (func_001E1030(arg0, arg1) ==
                func_00119F30(func_00250360(arg0, arg1), info, func_001DF540(arg0, arg1))) {
                return 1;
            }
            break;
        }
        return 2;
    }
    return 2;
}

static inline s32 max_0011C2E0(s32 a, s32 b) {
    if (a < b) {
        return b;
    }
    return a;
}

s32 func_0011C2E0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 minY;
    s32 minX;

    minY = arg3 < arg5 ? arg3 : arg5;
    arg5 = max_0011C2E0(arg5, arg3);
    minX = arg2 < arg4 ? arg2 : arg4;
    arg4 = max_0011C2E0(arg4, arg2);
    if ((arg4 - minX) + (arg5 - minY) != 2) {
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

typedef struct {
    u8 pad[8];
    u32 value;
} Data_0011C3E0;

void func_0011C3E0(void *arg0, u8 arg1) {
    Data_0011C3E0 *data = arg0;

    if (arg1 < 2) {
        if (arg1 == 1) {
            data->value = (data->value & 0xFFFF) | 0xFFFF0000;
        } else {
            data->value = (data->value & 0xFFFF0000) | 0xFFFF;
        }
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
} Req_0011C430;

typedef struct {
    u8 pad0[0x160];
    u16 list[32];    /* 0x160 */
    u8 idx : 5;      /* 0x1A0 */
    u8 pad1A0 : 3;
    u8 pad1A1;
    u16 count;       /* 0x1A2 */
} Work_0011C430;

s32 func_00117E60(void *, void *, s32);
s32 func_00276290(void *, void *, s32);

s32 func_0011C430(s32 arg0, void *arg1) {
    Req_0011C430 req;
    Work_0011C430 *w;
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
        if (func_00117E60(w, &req, arg0) == 0) {
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

INCLUDE_ASM("asm/nonmatchings/main_005", func_0011C600);

s32 func_0011CB20(void *arg0) {
    s32 result;

    result = func_00250360(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF);
    if (func_001DF540(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF) != 0) {
        if (func_001E2100(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF, 0) == 0) {
            if (*(u16 *)arg0 != 0xFFFF) {
                if ((*(u16 *)arg0 & 0xFF) == 0) {
                    if (*(s32 *)((u8 *)arg0 + 8) == -1) {
                        if (func_0027BBC0(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF, 0) == 1) {
                            if (func_001DE6D0(*(u16 *)arg0 >> 8) == 1) {
                                *(u16 *)((u8 *)arg0 + 4) = 0x50A;
                            } else {
                                *(u16 *)((u8 *)arg0 + 4) = 0x5FF;
                            }
                        } else {
                            if (func_001DE6D0(*(u16 *)arg0 >> 8) == 1) {
                                *(u16 *)((u8 *)arg0 + 4) = 0xA05;
                            } else {
                                *(u16 *)((u8 *)arg0 + 4) = 0xFF05;
                            }
                        }
                    }
                } else {
                    s32 subtype = func_001E0700(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF) >> 5;

                    switch (subtype) {
                    case 0:
                        if (func_002507D0(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF) == 1) {
                            func_0011D9B0(arg0, 1);
                        } else {
                            func_0011D110(arg0, 1);
                        }
                        break;
                    case 3:
                        func_0011DC00(arg0);
                        break;
                    case 4:
                    case 5:
                        *(u16 *)((u8 *)arg0 + 4) = 0x5FF;
                        break;
                    case 2:
                        func_0027CA50(arg0, 4, 0, (u8)func_0011FA80(result));
                        break;
                    default:
                        *(u16 *)((u8 *)arg0 + 4) = 0x5FF;
                        break;
                    }
                }
                return 1;
            }
        }
    }
    return 0;
}

s32 func_0011CD30(u16 *arg0, s32 arg1, s32 arg2) {
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
    func_0011CB20(arg0 + idx * 8);
    if (((arg0[idx * 8 + 2] >> 8) & 0xFF) == 10) {
        if (func_001DE6D0(arg1) == 1 && func_0011DFB0(pos, arg1, arg2) >= 0) {
            return pos | 0x10000;
        }
        if (func_0027B9B0(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (func_001E2100(arg1, 0, 0) == 0) {
        if (func_0027B9B0(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (func_001DE6D0(arg1) == 1 && func_0011DFB0(pos, arg1, arg2) >= 0) {
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

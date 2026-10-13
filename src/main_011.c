#include "common.h"

typedef struct {
    u16 id;
    u8 values[5];
} Info_00144630;

void func_00144630(s32 arg0, void *arg1, s32 *arg2) {
    Info_00144630 *info = arg1;
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
                if (card != 0x3E7 && func_00144810(card) == 0 && level >= func_0026FA80(card, arg0)) {
                    cost = func_0026FBB0(card);
                    if ((cost & 0xFFFF) + (cost >> 16) * 2 < 0xAF1 && func_0026FC10(card) == 2 &&
                        (u16)func_002789F0(info->id, (u16)card) == 0x3E7) {
                        func_00278D20(info->values, buf[i]);
                    }
                }
            }
        }
    }
}

s32 func_00144810(s32 arg0) {
    if ((func_0026FCE0(arg0) >> 5) != 0) {
        return 1;
    }
    return (func_0026FC10(arg0) != 0) ? 1 : 0;
}

typedef struct {
    u8 pad0[6];
    u8 slot[5];
} Obj1_00144860;

typedef struct {
    u8 pad0[0x3C];
    u16 id;
    u8 f3E;
} Obj2_00144860;

s32 func_00144860(s32 arg0, void *arg1, void *arg2) {
    Obj1_00144860 *o1 = arg1;
    Obj2_00144860 *o2 = arg2;
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
    return o2->f3E >> 5;
}

typedef struct Nibbles_00144A60 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_00144A60;


static inline s32 findrow_00144A60(void *arg2) {
    s32 row = 1;

    while (1) {
        if (func_0024DEB0(func_001E22B0(0, row), arg2) == 1) {
            return row;
        }
        row++;
        if (row > 5) {
            break;
        }
    }
    return -1;
}

s32 func_00144A60(s32 arg0, s32 arg1, void *arg2, s32 arg3) {
    extern s32 func_00278510();
    extern s32 func_0027A130();
    extern s32 func_002792C0(s32, s32, s32, s32, s32, s32, u16, u8);
    s32 bestPosition;
    s32 bestScore;
    Nibbles_00144A60 path[12];
    s32 initIndex;
    Nibbles_00144A60 *p;
    u8 type;

    if (arg2 == NULL) {
        return -1;
    }
    p = path;
    initIndex = 0;
    do {
        p->low = p->high = 15;
        initIndex++;
        p++;
    } while (initIndex < 12);
    type = (u8)(((u8 *)arg2)[0x3E] >> 5);
    if (type == 0 || type == 3) {
        if (arg3 >= 0) {
            s32 position;
            s32 y;
            s32 x;
            s32 i;
            s32 targetY;
            s32 targetX;
            s32 target;
            s32 score;

            bestScore = 255;
            bestPosition = 65535;
            target = func_001E1090(arg3 >> 8, arg3 & 255);
            i = 0;
            targetY = target >> 8;
            targetX = target & 255;
            do {
                position = func_0024E410(arg0, i);
                if (position >= 0) {
                    x = position & 255;
                    y = position >> 8;
                    if (func_001E22B0(x, y) != 8 &&
                        (func_001E22B0(x, y) != 9 || func_0024FE40(arg2, x, y) != 1) &&
                        func_001E36E0(x, y) == 0) {
                        if (func_00278510((s32)arg2, arg3, func_001461C0(arg0), targetX, targetY, 0) > 0) {
                            score = func_0027A130((s32)arg2, (s32)path, x, y, targetX, targetY,
                                                 arg3, 0, 3, (u16)func_001461C0(arg0));
                        } else {
                            score = func_002792C0((s32)arg2, (s32)path, x, y, targetX, targetY, arg3, 3);
                        }
                        if (func_0027AFC0((u8 *)path) > 0 && score < bestScore) {
                            bestScore = score;
                            bestPosition = position;
                        }
                    }
                }
                i++;
            } while (i < 8);
            if (bestPosition != 65535) {
                return bestPosition;
            }
            bestPosition = -1;
            return bestPosition;
        } else {
            s32 i;
            s32 bestDistance;
            s32 best;
            s32 position;
            s32 x;
            s32 y;
            s32 row;
            s32 lower;
            s32 distance;

            bestDistance = 14;
            best = -1;
            i = 0;
            do {
                position = func_0024E410(arg0, i);
                if (position >= 0) {
                    x = position & 255;
                    y = position >> 8;
                    if (func_001E22B0(x, y) != 8 &&
                        (func_001E22B0(x, y) != 9 || func_0024FE40(arg2, x, y) != 1) &&
                        func_001E3790(x, y) < 0) {
                        row = findrow_00144A60(arg2);
                        lower = y < row ? y : row;
                        y = row < y ? y : row;
                        distance = y - lower;
                        if (distance < bestDistance && distance >= 0) {
                            best = position;
                            bestDistance = distance;
                        }
                    }
                }
                i++;
            } while (i < 8);
            if (bestDistance < 14) {
                return best;
            }
            goto failure;
        }
    } else {
        s32 y;
        s32 x;
        s32 i;
        s32 best;
        s32 position;

        best = -1;
        i = 0;
        do {
            position = func_0024E410(arg0, i);
            if (position >= 0) {
                x = position & 255;
                y = position >> 8;
                if (func_001E22B0(x, y) != 8 &&
                    (func_001E22B0(x, y) != 9 || func_0024FE40(arg2, x, y) != 1) &&
                    func_001E3790(x, y) < 0 && y < 8) {
                    best = position;
                }
            }
            i++;
        } while (i < 8);
        if (best >= 0) {
            return best;
        }
    }
failure:
    return -1;
}

typedef struct {
    u8 low : 4;
    u8 high : 4;
} Flags_00144EC0;

typedef struct {
    u16 id;
    u8 action;
    u8 pad3;
    u16 position;
    u8 pad6[6];
    s32 value;
    u8 mode;
} Output_00144EC0;

s32 func_002464F0(s32, s32, s32);
s32 func_00276CC0(s32, s32, u16, s32, u16, s32);
s32 func_0027BE10(s32, s32, s32, s32, s32);

s32 func_00144EC0(u16 *arg0, s32 arg1, void *arg2, u8 arg3) {
    extern s32 func_00279C40(s32, s32, s32, s32, s32, s32, void *, u8);
    extern s32 func_00146220();
    s32 position;
    u8 upperX;
    u8 flag;
    Flags_00144EC0 cells[12];
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
    Output_00144EC0 *out = arg2;

    position = func_001E1090(*arg0 >> 8, *arg0 & 0xFF);
    i = 0;
    do {
        cells[i].low = cells[i].high = 15;
        i++;
    } while (i < 12);

    {
        u16 value = (u16)func_001461C0(arg1);
        originalX = position & 0xFF;
        originalY = position >> 8;
        if (func_00276CC0(originalX, originalY, *arg0, 3, value, 0) == 0) {
            out->id = *arg0;
            out->action = 6;
            out->position = position;
            out->mode = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, out->position, 1, 0);
            out->value = func_00146220(*arg0 >> 8, *arg0 & 0xFF, arg0);
            func_0027B1B0(arg0, arg3);
            return 0;
        } else {
            result = func_002464F0(func_001DF540(*arg0 >> 8, *arg0 & 0xFF), originalX, originalY);
            if (result == 0) {
                out->id = *arg0;
                out->action = 6;
                out->position = position;
                out->mode = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, out->position, 1, 0);
                out->value = func_00146220(*arg0 >> 8, *arg0 & 0xFF, arg0);
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
                                value = (u16)func_001461C0(arg1);
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
                        out->mode = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, out->position, 0, 0);
                    }
                    out->value = func_00146220(*arg0 >> 8, *arg0 & 0xFF, arg0);
                } else {
                    out->id = *arg0;
                    out->action = 6;
                    out->position = position;
                    out->mode = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, out->position, 1, 0);
                    out->value = func_00146220(*arg0 >> 8, *arg0 & 0xFF, arg0);
                }
                func_0027B1B0(arg0, arg3);
            }
        }
    }
    return 0;
}

typedef struct Input_00145400 {
    u16 position;
    u8 pad2[6];
    u32 targets;
} Input_00145400;

typedef struct Output_00145400 {
    u16 position;
    u8 action;
    u8 pad3;
    u16 destination;
    u8 pad6[6];
    s32 special;
    u8 result;
} Output_00145400;

typedef struct Coord_00145400 {
    u8 x : 4;
    u8 y : 4;
} Coord_00145400;

static inline u32 target_00145400(void *src, u8 side) {
    Input_00145400 *input = src;
    if (side == 1) {
        return (u16)(input->targets >> 16);
    }
    return (u16)input->targets;
}

#define MIN_00145400(a, b) ((a) < (b) ? (a) : (b))
#define MAX_00145400(a, b) ((a) > (b) ? (a) : (b))

s32 func_00145400(void *arg0, s32 arg1, void *arg2, u8 arg3) {
    extern s32 func_00146220();
    extern s32 func_002464F0();
    extern s32 func_00276CC0();
    extern void func_0027A090();
    Input_00145400 *input = arg0;
    Output_00145400 *output = arg2;
    s32 targetPosition;
    s32 targetX;
    Coord_00145400 *candidate;
    s32 fallback;
    s32 origin;
    s32 count;
    s32 originY;
    s32 originX;
    s32 special;
    s32 index;
    s32 bestCost;
    s32 bestIndex;
    s32 i;
    s32 card;
    u32 targetLow;
    u32 targetHigh;
    Coord_00145400 candidates[12];

    targetLow = target_00145400(arg0, arg3);
    targetHigh = target_00145400(arg0, arg3);
    if (func_001DF540(targetHigh >> 8, targetLow & 0xFF) == 0) {
        func_0027B1B0(arg0, 1);
        return -1;
    }
    fallback = func_00146220((s32)input->position >> 8, input->position & 0xFF, arg0);
    origin = func_001E1090((s32)input->position >> 8, input->position & 0xFF);
    targetLow = target_00145400(arg0, arg3);
    targetHigh = target_00145400(arg0, arg3);
    targetPosition = func_001E1090(targetHigh >> 8, targetLow & 0xFF);
    i = 0;
    do {
        candidates[i].x = candidates[i].y = 15;
        i++;
    } while (i < 12);
    card = func_001DF540((s32)input->position >> 8, input->position & 0xFF);
    originX = origin & 0xFF;
    originY = origin >> 8;
    if (func_002464F0(card, originX, originY) == 0) {
        s32 cost;
        output->position = input->position;
        output->action = 6;
        output->destination = origin;
        cost = func_00276CC0(originX, originY, arg1, 3, 1, (u8)func_001461C0(arg1));
        if (cost >= func_001E0290((s32)input->position >> 8, input->position & 0xFF, 0)) {
            output->result = func_0027E360((s32)input->position >> 8,
                                         input->position & 0xFF, output->destination, 1, 0);
        } else {
            output->result = func_0027E360((s32)input->position >> 8,
                                         input->position & 0xFF, output->destination, 0, 0);
        }
        func_0027B1B0(arg0, arg3);
    } else {
        s32 position = input->position;
        u16 kind = func_001461C0(arg1);
        s32 positionY = position >> 8;
        s32 positionX = position & 0xFF;

        func_0027A090(positionY, positionX, candidates,
                     originX, originY, targetX = targetPosition & 0xFF, targetPosition >>= 8,
                     target_00145400(arg0, arg3), (s64)0, (s64)30, (s64)kind);
        count = func_0027AFC0((u8 *)candidates);
        bestIndex = 255;
        if (count > 0) {
            special = 0;
            bestCost = 65535;
            for (index = 0; index < count; index++) {
                if (func_001464A0((s32)input->position >> 8, input->position & 0xFF,
                                 originX, originY, targetX, targetPosition) == 1) {
                    Coord_00145400 *candidate = &candidates[index];
                    bestIndex = index;
                    special = 1;
                    index = count;
                    candidate->x = targetX;
                    candidate->y = targetPosition;
                } else {
                    s32 cost;
                    candidate = &candidates[index];
                    cost = func_00276CC0(candidate->x, candidate->y, arg1,
                                         3, 1, (u8)func_001461C0(arg1));
                    if (cost < bestCost) {
                        bestCost = cost;
                        bestIndex = index;
                    } else if (cost == bestCost) {
                        if ((MAX_00145400(candidate->x, targetX) - MIN_00145400(candidate->x, targetX)) +
                                (MAX_00145400(candidate->y, targetPosition) - MIN_00145400(candidate->y, targetPosition)) <
                            (MAX_00145400(candidates[bestIndex].x, targetX) - MIN_00145400(candidates[bestIndex].x, targetX)) +
                                (MAX_00145400(candidates[bestIndex].y, targetPosition) - MIN_00145400(candidates[bestIndex].y, targetPosition))) {
                            bestCost = cost;
                            bestIndex = index;
                        }
                    }
                }
            }
        } else {
            output->position = input->position;
            output->action = 6;
            output->destination = origin;
            output->special = fallback;
            output->result = func_0027E360((s32)input->position >> 8,
                                         input->position & 0xFF, output->destination, 0, 0);
            func_0027B1B0(arg0, arg3);
            return 0;
        }
        if (bestIndex != 255) {
            output->position = input->position;
            output->action = 6;
            output->destination = (candidates[bestIndex].y << 8) | candidates[bestIndex].x;
            output->special = special;
            output->result = func_0027E360((s32)input->position >> 8,
                                         input->position & 0xFF, output->destination, 0, 0);
        } else {
            output->position = input->position;
            output->action = 6;
            output->destination = origin;
            output->special = special;
            output->result = func_0027E360((s32)input->position >> 8,
                                         input->position & 0xFF, output->destination, 0, 0);
            func_0027B1B0(arg0, arg3);
            return 0;
        }
    }
    return 0;
}

typedef struct Coord_001459E0 {
    u8 x : 4;
    u8 y : 4;
} Coord_001459E0;

typedef struct Unit_001459E0 {
    u16 pos;
    u8 pad2[6];
    u32 target;
} Unit_001459E0;

typedef struct Result_001459E0 {
    u16 pos;
    s8 kind;
    u8 pad3;
    u16 target;
    u8 pad6[6];
    s32 action;
    s8 value;
} Result_001459E0;

#define selected_001459E0(unit, mode) \
    ((mode) == 1 ? (u32)(u16)(((Unit_001459E0 *)(unit))->target >> 16) \
                 : (u32)(u16)((Unit_001459E0 *)(unit))->target)

static inline u32 minY_001459E0(u32 value, void *unit, s32 mode) {
    return value < (selected_001459E0(unit, mode) >> 8) ? (u8)value : (selected_001459E0(unit, mode) >> 8);
}

static inline u32 maxY_001459E0(u32 value, void *unit, s32 mode) {
    return (selected_001459E0(unit, mode) >> 8) < value ? (u8)value : (selected_001459E0(unit, mode) >> 8);
}

static inline u32 minX_001459E0(u32 value, void *unit, s32 mode) {
    return value < (selected_001459E0(unit, mode) & 0xFF) ? (u8)value : (selected_001459E0(unit, mode) & 0xFF);
}

static inline u32 maxX_001459E0(u32 value, void *unit, s32 mode) {
    return (selected_001459E0(unit, mode) & 0xFF) < value ? (u8)value : (selected_001459E0(unit, mode) & 0xFF);
}

s32 func_001459E0(void *arg0, s32 arg1, void *arg2, u8 arg3, u8 arg4) {
    s32 target;
    s32 leader;
    s32 count;
    Coord_001459E0 coords[12];
    extern s32 func_00146220();
    extern s32 func_00276CC0();
    extern void func_00279230();
    extern s32 func_0027E360(s32, s32, s32, u8, s32);

    {
        s32 bestCost;
        s32 bestIndex;
        s32 mode;
        Coord_001459E0 *p;
        s32 i;
        target = func_001E1090(((Unit_001459E0 *)arg0)->pos >> 8, ((Unit_001459E0 *)arg0)->pos & 0xFF);
        mode = arg3;
        if (selected_001459E0(arg0, mode) == 0xFFFF &&
            target == selected_001459E0(arg0, mode)) {
            ((Result_001459E0 *)arg2)->pos = ((Unit_001459E0 *)arg0)->pos;
            ((Result_001459E0 *)arg2)->kind = 6;
            ((Result_001459E0 *)arg2)->target = target;
            ((Result_001459E0 *)arg2)->value = func_0027E360(
                ((Unit_001459E0 *)arg0)->pos >> 8, ((Unit_001459E0 *)arg0)->pos & 0xFF,
                ((Result_001459E0 *)arg2)->target, arg4, 0);
            ((Result_001459E0 *)arg2)->action = func_00146220(
                ((Unit_001459E0 *)arg0)->pos >> 8, ((Unit_001459E0 *)arg0)->pos & 0xFF, arg0);
            func_0027B1B0(arg0, arg3);
            return 0;
        }

        p = coords;
        {
            s32 i = 0;
            Coord_001459E0 *q = p;
            do {
                q->x = q->y = 15;
                ++i;
                ++q;
            } while (i < 12);
        }

        leader = func_001E3790(selected_001459E0(arg0, mode) & 0xFF,
                             selected_001459E0(arg0, mode) >> 8);
        if (leader < 0) {
            leader = 0xFFFF;
        }
        func_00279230(((Unit_001459E0 *)arg0)->pos >> 8, ((Unit_001459E0 *)arg0)->pos & 0xFF,
                     coords, target & 0xFF, target >> 8,
                     selected_001459E0(arg0, mode) & 0xFF,
                     selected_001459E0(arg0, mode) >> 8, (u16)leader, 7);
        count = func_0027AFC0((u8 *)coords);
        if (count > 0) {
            s32 cost;
            bestIndex = 0xFF;
            bestCost = 0xFFFF;
            for (i = 0; i < count; ++i, ++p) {
                if (func_001E36E0(p->x, p->y) == 0) {
                    cost = func_00276CC0(p->x, p->y, arg1, 3, 1,
                                        (u8)func_001461C0(arg1));
                    if (cost < bestCost) {
                        bestCost = cost;
                        bestIndex = i;
                    } else if (cost == bestCost) {
                        if ((maxX_001459E0(p->x, arg0, mode) -
                             minX_001459E0(p->x, arg0, mode)) +
                            (maxY_001459E0((u8)p->y, arg0, mode) -
                             minY_001459E0((u8)p->y, arg0, mode)) <
                            (maxX_001459E0(coords[bestIndex].x, arg0, mode) -
                             minX_001459E0(coords[bestIndex].x, arg0, mode)) +
                            (maxY_001459E0((u8)coords[bestIndex].y, arg0, mode) -
                             minY_001459E0((u8)coords[bestIndex].y, arg0, mode))) {
                            bestCost = cost;
                            bestIndex = i;
                        }
                    }
                }
            }
        } else {
            ((Result_001459E0 *)arg2)->pos = ((Unit_001459E0 *)arg0)->pos;
            ((Result_001459E0 *)arg2)->kind = 6;
            ((Result_001459E0 *)arg2)->target = target;
            ((Result_001459E0 *)arg2)->value = func_0027E360(
                ((Unit_001459E0 *)arg0)->pos >> 8, ((Unit_001459E0 *)arg0)->pos & 0xFF,
                ((Result_001459E0 *)arg2)->target, arg4, 0);
            ((Result_001459E0 *)arg2)->action = func_00146220(
                ((Unit_001459E0 *)arg0)->pos >> 8, ((Unit_001459E0 *)arg0)->pos & 0xFF, arg0);
            func_0027B1B0(arg0, arg3);
            return 0;
        }
            if (bestIndex != 0xFF) {
                ((Result_001459E0 *)arg2)->pos = ((Unit_001459E0 *)arg0)->pos;
                ((Result_001459E0 *)arg2)->kind = 6;
                ((Result_001459E0 *)arg2)->target =
                    (coords[bestIndex].y << 8) | coords[bestIndex].x;
                ((Result_001459E0 *)arg2)->value = func_0027E360(
                    ((Unit_001459E0 *)arg0)->pos >> 8, ((Unit_001459E0 *)arg0)->pos & 0xFF,
                    ((Result_001459E0 *)arg2)->target, arg4, 0);
                ((Result_001459E0 *)arg2)->action = func_00146220(
                    ((Unit_001459E0 *)arg0)->pos >> 8, ((Unit_001459E0 *)arg0)->pos & 0xFF, arg0);
            } else {
                ((Result_001459E0 *)arg2)->pos = ((Unit_001459E0 *)arg0)->pos;
                ((Result_001459E0 *)arg2)->kind = 6;
                ((Result_001459E0 *)arg2)->target = target;
                ((Result_001459E0 *)arg2)->value = func_0027E360(
                    ((Unit_001459E0 *)arg0)->pos >> 8, ((Unit_001459E0 *)arg0)->pos & 0xFF,
                    ((Result_001459E0 *)arg2)->target, arg4, 0);
                ((Result_001459E0 *)arg2)->action = func_00146220(
                    ((Unit_001459E0 *)arg0)->pos >> 8, ((Unit_001459E0 *)arg0)->pos & 0xFF, arg0);
            }
            func_0027B1B0(arg0, arg3);
        return 0;
    }
}

s32 func_001461C0(s32 arg0) {
    if (func_001DF470(arg0) > 2000) {
        if (func_001E0150(arg0) >= 4) {
            return 0;
        }
        return 0;
    }
    return 0;
}

s32 func_00146220(s32 arg0, s32 arg1) {
    s32 pos;
    s32 kind;
    s32 slot;
    u8 count;
    s32 i;
    s32 list;
    s32 pair;
    extern s32 func_001E1030();

    pos = func_001E1090(arg0, arg1);
    kind = func_001E1030(arg0, arg1);
    slot = func_00250360(arg0, arg1);
    count = 0;
    if (func_001E2100(arg0, arg1, 4) != 0) {
        return 0;
    }
    switch (kind) {
    case 0x145:
        list = func_0024CA40(0, 0, arg0, 2, 0x34, 0xE);
        for (i = 0; i < func_0024E910(list); i++) {
            pair = func_0024EC50(list, i);
            if (func_001E2100(pair >> 8, pair & 0xFF, 3) != 0) {
                count++;
            }
        }
        if (count >= 3) {
            return 1;
        }
        break;
    case 0xC0:
        if (func_0024E910(func_0024CA40(0, 0, arg0, 1, 5, 0xE)) >= 3) {
            return 1;
        }
        break;
    case 0x2DB:
    case 0x2EF:
        if (func_0027D830(arg0, arg1, 0, 0, 6, 0) == 5) {
            return 2;
        }
        if (func_001465A0(slot) == 1) {
            return 1;
        }
        break;
    case 0x34E:
        if (func_0027D830(arg0, arg1, 0, 0, 6, 0) == 5) {
            return 2;
        }
        if (func_001466A0(func_00250360(arg0, arg1), 0x34E) == 1 &&
            func_001E22B0(pos & 0xFF, pos >> 8) != 9) {
            return 1;
        }
        break;
    }
    return 2;
}

static inline s32 max_001464A0(s32 a, s32 b) {
    if (a < b) {
        return b;
    }
    return a;
}

s32 func_001464A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 min_y;
    s32 min_x;

    min_y = arg3 < arg5 ? arg3 : arg5;
    arg5 = max_001464A0(arg5, arg3);
    min_x = arg2 < arg4 ? arg2 : arg4;
    arg4 = max_001464A0(arg4, arg2);

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

s32 func_001465A0(s32 arg0)
{
    s32 i;
    s32 mask;
    s32 entry;

    if (func_0024E910(func_0024CA40(0, 0, arg0, 1, 0x34, 0xE)) > 2) {
        return 0;
    }

    mask = func_0024CA40(0, 0, arg0, 2, 0x34, 0xE);
    if (func_0024E910(mask) < 5) {
        return 0;
    }

    for (i = 0; i < func_0024E910(mask); i++) {
        entry = func_0024EC50(mask, i);
        if ((func_001E1090(entry >> 8, entry & 0xFF) >> 8) < 3) {
            return 1;
        }
    }

    return 0;
}

s32 func_001466A0(s32 arg0, s32 arg1) {
    s32 data[4];
    s32 index;
    s32 mask;
    s32 low;
    s32 high;
    s32 pair;
    s32 value;

    func_00254C90(data, *(s32 *)((u8 *)func_0026FC90(arg1, 0) + 4));
    if ((mask = func_00254890(data, arg0)) < 0) {
        return 0;
    }
    for (index = 0; index < func_0024E910(mask); index++) {
        pair = func_0024EC50(mask, index);
        high = pair >> 8;
        low = pair & 0xFF;
        value = func_001E1090(high, low);
        if (func_002509E0(high, low, value & 0xFF, value >> 8) >= 0x9C4) {
            return 0;
        }
    }
    return 1;
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
} Req_00146790;

typedef struct {
    u8 pad0[0x160];
    u16 list[32];    /* 0x160 */
    u8 idx : 5;      /* 0x1A0 */
    u8 pad1A0 : 3;
    u8 pad1A1;
    u16 count;       /* 0x1A2 */
} Work_00146790;

s32 func_001424B0(void *, void *, s32);
s32 func_00276290(void *, void *, s32);

s32 func_00146790(s32 arg0, void *arg1) {
    Req_00146790 req;
    Work_00146790 *w;
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
        if (func_001424B0(w, &req, arg0) == 0) {
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

INCLUDE_ASM("asm/nonmatchings/main_011", func_00146960);

s32 func_00146EC0(void *arg0, s32 arg1) {
    extern s32 func_0014B390();
    s32 temp_s0;

    func_001E1090(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF);
    temp_s0 = func_00250360(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF);
    if (func_001DF540(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF) != 0) {
        if (func_001E2100(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF, 0) == 0) {
            if (*(u16 *)arg0 != 0xFFFF) {
                if ((*(u16 *)arg0 & 0xFF) == 0) {
                    if (*(s32 *)((u8 *)arg0 + 8) == -1) {
                        if (func_0027BBC0(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF, 0) == 1) {
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
                    switch (func_001E0700(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF) >> 5) {
                    case 0:
                        if (func_0014B390(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF) == 1) {
                            func_00147830(arg0);
                        } else if (func_002507D0(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF) == 1) {
                            func_00147AC0(arg0);
                        } else {
                            func_001474F0(arg0);
                        }
                        break;
                    case 2:
                        func_0027CA50(arg0, 5, 0, (u8)func_0014B330(temp_s0));
                        break;
                    case 1:
                    case 3:
                        func_00147B90(arg0, arg1);
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

s32 func_00147100(u16 *arg0, s32 arg1, s32 arg2, void *arg3) {
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
    func_00146EC0(arg0 + idx * 8, arg2);
    if (((arg0[idx * 8 + 2] >> 8) & 0xFF) == 10) {
        if (func_001DE6D0(arg1) == 1 && func_00148020(pos, arg1, arg3) >= 0) {
            return pos | 0x10000;
        }
        if (func_0027B9B0(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (func_001E2100(arg1, 0, 0) == 0) {
        if (func_0027B9B0(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (func_001DE6D0(arg1) == 1 && func_00148020(pos, arg1, arg3) >= 0) {
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

INCLUDE_ASM("asm/nonmatchings/main_011", func_001474F0);

void func_001477D0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, u16 arg9, s32 arg10, s32 arg11, u8 arg12, s32 arg13) {
    func_0027DE20(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, 0, 0x960, arg13);
}

INCLUDE_ASM("asm/nonmatchings/main_011", func_00147830);

typedef struct {
    u16 id;
    u16 unk2;
    u16 target;
    u16 unk6;
    union {
        u32 word;
        u16 low;
    } info;
} Action_00147AC0;

void func_00147AC0(void *arg0) {
    extern s32 func_001E1030();
    Action_00147AC0 *action = arg0;
    s32 owner;
    u16 id;

    id = action->id;
    owner = func_00250360(id >> 8, id & 0xFF);
    id = action->id;
    switch (func_001E1030(id >> 8, id & 0xFF)) {
    case 0x123:
        if (func_0024E910(func_0024CA40(0, 0, owner, 1, 6, 14)) >= 3) {
            action->target = 0x3FF;
            id = action->id;
            action->info.word = (func_001E1090(id >> 8, id & 0xFF) << 16) | action->info.low;
            return;
        }
        break;
    }
    func_001474F0(action);
}

INCLUDE_ASM("asm/nonmatchings/main_011", func_00147B90);

s32 func_00147E00(s32 arg0, s32 arg1, s32 arg2) {
    if (arg2 < 3) {
        return (arg1 >= 3) ? 0x306 : 0x300;
    }
    return func_001E1090((arg0 == 0) ? 1 : 0, 0);
}

s32 func_00147E50(s32 arg0, s32 arg1) {
    s32 var_s0;

    var_s0 = 0;
loop_1:
    if (((arg1 << 8) | arg0) == func_00147EB0(var_s0)) {
        return 1;
    }
    var_s0 += 1;
    if (var_s0 >= 5) {
        return 0;
    }
    goto loop_1;
}

s32 func_00147EB0(s32 arg0) {
    switch (arg0) {
    case 0:
        return 0x403;
    case 1:
        return 0x402;
    case 2:
        return 0x404;
    case 3:
        return 0x401;
    case 4:
        return 0x405;
    default:
        return -1;
    }
}

s32 func_00147F40(void) {
    s32 i;
    s32 value;
    s32 result;

    i = 0;
    do {
        value = func_00147EB0(i);
        if (((func_001E36E0(value & 0xFF, value >> 8) == 0) ? 1 : 0) == 1) {
            switch (i) {
            case 0:
                result = 0x403;
                break;
            case 1:
                result = 0x402;
                break;
            case 2:
                result = 0x404;
                break;
            case 3:
                result = 0x401;
                break;
            case 4:
                result = 0x405;
                break;
            default:
                result = -1;
                break;
            }
            return result;
        }
        i++;
    } while (i < 5);
    return -1;
}

typedef struct {
    s16 card;
    u8 f2;
    u8 pad3;
    s16 f4;
    u8 pad6[6];
    s32 fC;
} Act_00148020;

typedef struct {
    u8 pad0[0x3C];
    u16 id;
    u8 pad3E[0x22];
} Card_00148020;

s32 func_001491B0(s32 arg0, u8 arg1, void *arg2, s32 arg3);
s32 func_00276F10(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8,
                  s32 arg9);

s32 func_00148020(s32 arg0, s32 arg1, void *arg2) {
    extern s32 func_00278890(s32, s32);
    Act_00148020 *act = arg2;
    Card_00148020 buf;
    s32 res;
    s32 type;
    s32 card;
    s32 r;

    act->card = arg0;
    if (func_001DE6D0(arg1) == 0) {
        return -1;
    }
    if (func_00278890(arg1, 0) == 5 && func_00278890(arg1, 1) == 5) {
        return -1;
    }
    type = func_001482F0(arg1, &buf);
    if (type < 0) {
        return -1;
    }
    act->f2 = 10;
    act->fC = 0;
    card = func_001E1090(arg0 >> 8, arg0 & 0xFF);
    if (type == 0) {
        if (func_00148B60(arg1, arg2, &buf) >= 0) {
            res = func_00276F10(&buf, card & 0xFF, card >> 8, arg1 == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, func_0014B330(arg1));
            if (res < 0) {
                if (func_001E0150(arg1) < 4) {
                    r = func_001491B0(arg1, type, &buf, res);
                    if (r < 0) {
                        return -1;
                    }
                    act->f4 = r;
                    return 1;
                }
            } else {
                r = func_001491B0(arg1, type, &buf, res);
                if (r < 0) {
                    return -1;
                }
                act->f4 = r;
                return 1;
            }
        }
    } else {
        res = func_00276F10(&buf, card & 0xFF, card >> 8, arg1 == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, func_0014B330(arg1));
    }
    if (type == 2) {
        func_00148F80(arg1, arg2, &buf);
        r = func_001491B0(arg1, type, &buf, res);
        if (r < 0) {
            return -1;
        }
        act->f4 = r;
        return 1;
    } else if (type == 3) {
        func_00148630(arg1, arg2, &buf);
        r = func_001491B0(arg1, type, &buf, res);
        if (r < 0) {
            return -1;
        }
        act->f4 = r;
        return 1;
    } else {
        if (func_00148960(arg1, arg2, &buf, buf.id) < 0) {
            return -1;
        }
        r = func_001491B0(arg1, type, &buf, res);
        if (r < 0) {
            return -1;
        }
        act->f4 = r;
        return 1;
    }
}

s32 func_001482F0(s32 arg0, void *arg1) {
    extern s32 func_00278890();
    extern s32 func_001E1580();
    s32 entries[8];
    u8 scratch[32];
    u8 kind0;
    u8 kind1;

    kind0 = (u8)func_00278890(arg0, 0);
    kind1 = (u8)func_00278890(arg0, 1);
    if (arg1 == NULL) {
        return -1;
    }
    func_0026FD30(arg0, entries);
    if (kind0 == 5) {
        if (func_00148960(arg0, scratch, arg1, 999) >= 0) {
            return 1;
        }
        return -1;
    }
    if (kind1 == 5) {
        s32 i = 0;
        s32 *entry;

        if (i < func_0026FE20(arg0)) {
            entry = entries;
            do {
                if ((func_0026FCE0(*entry) >> 5) == 0 &&
                    func_0026FB10(arg0, *entry) == 1) {
                    func_001DCD70(arg1, entries[i]);
                    return 0;
                }
                entry++;
                i++;
            } while (i < func_0026FE20(arg0));
        }
        return -1;
    }
    if (func_00148870(arg0, scratch, arg1, 0x34B) >= 0) {
        if (func_0014B240(arg0, 0x34B) == 1) {
            return 2;
        }
    }
    if (func_00148630(arg0, scratch, arg1) == 1) {
        return 3;
    }
    if (func_0024E910(func_0024CA40(0, 0, arg0, 1, 0x1E001C, 14)) > 0) {
        if (func_00148870(arg0, scratch, arg1, 30) >= 0) {
            return 2;
        }
    }
    if (func_0014B490(arg0) >= 0) {
        if (func_00148870(arg0, scratch, arg1, 0x2AD) >= 0) {
            return 2;
        }
    }
    {
        s32 i = 0;
        do {
            if (func_001E1580(arg0, i) != 0 &&
                func_00148870(arg0, scratch, arg1, 0x31C) >= 0) {
                return 2;
            }
            i++;
        } while (i < 11);
    }
    {
        s32 *entry;
        s32 i = 0;

        if (i < func_0026FE20(arg0)) {
            entry = entries;
            do {
                if ((func_0026FCE0(*entry) >> 5) == 0 &&
                    func_0026FB10(arg0, *entry) == 1 && *entry != 0x110) {
                    func_001DCD70(arg1, entries[i]);
                    return 0;
                }
                entry++;
                i++;
            } while (i < func_0026FE20(arg0));
        }
    }
    {
        s32 result = func_00148960(arg0, scratch, arg1, 999);
        if (result >= 0) {
            return result;
        }
    }
    return -1;
}

typedef struct {
    u8 pad0[6];
    u8 slot[5];
} Obj1_00148630;

typedef struct {
    u8 pad0[0x38];
    s16 attack;
    s16 defense;
} Obj2_00148630;


s32 func_00148630(s32 arg0, void *arg1, void *arg2) {
    Obj2_00148630 *o2 = arg2;
    Obj1_00148630 *o1 = arg1;
    s32 list[8];
    s32 i;
    s32 found;
    u8 k;

    func_0026FD30(arg0, list);
    for (i = 0, found = 0; i < func_0026FE20(arg0); i++) {
        if (list[i] == 0x31D) {
            found = 1;
            o1->slot[0] = i;
        }
    }
    if (found == 0) {
        return -1;
    }
    for (i = 0, found = 0; i < func_0026FE20(arg0); i++) {
        if (list[i] == 0x110 && func_0026FB10(arg0, list[i]) == 1) {
            o1->slot[1] = i;
            found = 1;
        }
    }
    if (found == 0) {
        return -1;
    }
    k = 2;
    func_001DCD70(o2, 0x111);
    for (i = 0; i < func_0026FE20(arg0); i++) {
        if (i != o1->slot[0] && i != o1->slot[1]) {
            if (func_00248F60(0x111, list[i]) >= 0 && (func_0026FCE0(list[i]) >> 5) == 2) {
                if (list[i] != 0x31B && list[i] != 0x31C) {
                    o1->slot[k] = i;
                    k++;
                    o2->attack += (s16)func_002493A0(list[i]);
                    o2->defense += (s16)func_002493A0(list[i]);
                }
            }
        }
    }
    return 1;
}

s32 func_00148870(s32 arg0, void *arg1, void *arg2, s32 arg3) {
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

s32 func_00148960(s32 arg0, u8 *arg1, void *arg2, s32 arg3) {
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

typedef struct Info_00148B60 {
    u8 pad00[8];
    u16 x;
    s16 y;
} Info_00148B60;

typedef struct Sprite_00148B60 {
    Info_00148B60 *info;
    u8 pad04[0x34];
    s16 x;
    s16 y;
} Sprite_00148B60;

u16 *func_00278A90(s32, u16 *, s32, s32, s32, s16 *, s16 *);

s32 func_00148B60(s32 arg0, u8 *arg1, void *arg2) {
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
                            func_00148D40(arg0, *node, entries);
                            func_00278DD0((u8 *)*node + 2, arg1 + 6);
                            func_001DCD70(arg2, **node);
                            ((Sprite_00148B60 *)arg2)->x = (value >> 16) - (((Sprite_00148B60 *)arg2)->info->x & 0x1FFF);
                            ((Sprite_00148B60 *)arg2)->y = (value & 0xFFFF) - (((Sprite_00148B60 *)arg2)->info->y & 0x1FFF);
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
} Info_00148D40;

void func_00148D40(s32 arg0, void *arg1, s32 *arg2) {
    Info_00148D40 *info = arg1;
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
                if (card != 0x3E7 && func_00148F20(card) == 0 && level >= func_0026FA80(card, arg0)) {
                    cost = func_0026FBB0(card);
                    if ((cost & 0xFFFF) + (cost >> 16) * 2 < 0x1069 && func_0026FC10(card) == 2 &&
                        (u16)func_002789F0(info->id, (u16)card) == 0x3E7) {
                        func_00278D20(info->values, buf[i]);
                    }
                }
            }
        }
    }
}

s32 func_00148F20(s32 arg0) {
    if ((func_0026FCE0(arg0) >> 5) != 0) {
        return 1;
    } else if (func_0026FC10(arg0) == 1) {
        return 1;
    } else {
        return 0;
    }
}


typedef struct {
    u8 pad0[6];
    u8 slot[5];
} Obj1_00148F80;

typedef struct {
    u8 pad0[0x38];
    s16 f38;
    s16 f3A;
    u16 id;
} Obj2_00148F80;

s32 func_00148F80(s32 arg0, void *arg1, void *arg2) {
    Obj1_00148F80 *o1 = arg1;
    Obj2_00148F80 *o2 = arg2;
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

INCLUDE_ASM("asm/nonmatchings/main_011", func_001491B0);

typedef struct Nibbles_00149690 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_00149690;

typedef struct Output_00149690 {
    u16 position;
    u8 action;
    u8 pad3;
    u16 destination;
    u8 pad6[6];
    s32 special;
    u8 result;
} Output_00149690;

void func_001E1E70(s32, s32, s32, s32);
s32 func_002464F0(s32, s32, s32);
s32 func_00276CC0(s32, s32, u16, s32, u16, s32);
s32 func_0027BE10(s32, s32, s32, s32, s32);

s32 func_00149690(u16 *arg0, s32 arg1, void *arg2, u8 arg3) {
    Output_00149690 *output = arg2;
    s32 target;
    u8 endX;
    u8 extra;
    Nibbles_00149690 nibbles[12];
    s32 bestScore;
    s32 best;
    s32 i;
    Nibbles_00149690 *p;
    extern s32 func_0014AE60();
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

        initialScore = func_0014B330(arg1);
        centerX = target & 0xFF;
        centerY = target >> 8;
        if (func_00276CC0(centerX, centerY, *arg0, 3, initialScore, 0) == 0) {
            output->position = *arg0;
            output->action = 6;
            output->destination = target;
            output->result = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, output->destination, 1, 0);
            output->special = func_0014AE60(*arg0 >> 8, *arg0 & 0xFF, arg0);
            func_0027B1B0(arg0, arg3);
            return 0;
        }
        if ((range = func_002464F0(func_001DF540(*arg0 >> 8, *arg0 & 0xFF), centerX, centerY)) == 0) {
            output->position = *arg0;
            output->action = 6;
            output->destination = target;
            output->result = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, output->destination, 1, 0);
            output->special = func_0014AE60(*arg0 >> 8, *arg0 & 0xFF, arg0);
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
                        candidateScore = func_00276CC0(x, y, *arg0, 3, (u16)func_0014B330(arg1), 0);
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
            output->special = func_0014AE60(*arg0 >> 8, *arg0 & 0xFF, arg0);
        } else {
            output->position = *arg0;
            output->action = 6;
            output->destination = target;
            output->result = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, output->destination, 1, 0);
            output->special = func_0014AE60(*arg0 >> 8, *arg0 & 0xFF, arg0);
        }
        func_0027B1B0(arg0, arg3);
        return 0;
    }
}

typedef struct Input_00149C60 {
    u16 position;
    u8 pad2[6];
    u32 targets;
} Input_00149C60;

typedef struct Output_00149C60 {
    u16 position;
    u8 action;
    u8 pad3;
    u16 destination;
    u8 pad6[6];
    s32 special;
    u8 result;
} Output_00149C60;

typedef struct Coord_00149C60 {
    u8 x : 4;
    u8 y : 4;
} Coord_00149C60;

static inline u32 target_00149C60(void *src, u8 side) {
    Input_00149C60 *input = src;
    if (side == 1) {
        return (u16)(input->targets >> 16);
    }
    return (u16)input->targets;
}

#define MIN_00149C60(a, b) ((a) < (b) ? (a) : (b))
#define MAX_00149C60(a, b) ((a) > (b) ? (a) : (b))

s32 func_00149C60(void *arg0, s32 arg1, void *arg2, u8 arg3) {
    extern s32 func_0014AE60();
    extern s32 func_002464F0();
    extern s32 func_00276CC0();
    extern void func_0027A090();
    Input_00149C60 *input = arg0;
    Output_00149C60 *output = arg2;
    s32 targetPosition;
    s32 targetX;
    Coord_00149C60 *candidate;
    s32 fallback;
    s32 origin;
    s32 count;
    s32 originY;
    s32 originX;
    s32 special;
    s32 index;
    s32 bestCost;
    s32 bestIndex;
    s32 i;
    s32 card;
    u32 targetLow;
    u32 targetHigh;
    Coord_00149C60 candidates[12];

    targetLow = target_00149C60(arg0, arg3);
    targetHigh = target_00149C60(arg0, arg3);
    if (func_001DF540(targetHigh >> 8, targetLow & 0xFF) == 0) {
        func_0027B1B0(arg0, 1);
        return -1;
    }
    fallback = func_0014AE60((s32)input->position >> 8, input->position & 0xFF, arg0);
    origin = func_001E1090((s32)input->position >> 8, input->position & 0xFF);
    targetLow = target_00149C60(arg0, arg3);
    targetHigh = target_00149C60(arg0, arg3);
    targetPosition = func_001E1090(targetHigh >> 8, targetLow & 0xFF);
    i = 0;
    do {
        candidates[i].x = candidates[i].y = 15;
        i++;
    } while (i < 12);
    card = func_001DF540((s32)input->position >> 8, input->position & 0xFF);
    originX = origin & 0xFF;
    originY = origin >> 8;
    if (func_002464F0(card, originX, originY) == 0) {
        s32 cost;
        output->position = input->position;
        output->action = 6;
        output->destination = origin;
        cost = func_00276CC0(originX, originY, arg1, 3, 1, (u8)func_0014B330(arg1));
        if (cost >= func_001E0290((s32)input->position >> 8, input->position & 0xFF, 0)) {
            output->result = func_0027E360((s32)input->position >> 8,
                                         input->position & 0xFF, output->destination, 1, 0);
        } else {
            output->result = func_0027E360((s32)input->position >> 8,
                                         input->position & 0xFF, output->destination, 0, 0);
        }
        func_0027B1B0(arg0, arg3);
    } else {
        s32 position = input->position;
        u16 kind = func_0014B330(arg1);
        s32 positionY = position >> 8;
        s32 positionX = position & 0xFF;

        func_0027A090(positionY, positionX, candidates,
                     originX, originY, targetX = targetPosition & 0xFF, targetPosition >>= 8,
                     target_00149C60(arg0, arg3), (s64)0, (s64)30, (s64)kind);
        count = func_0027AFC0((u8 *)candidates);
        bestIndex = 255;
        if (count > 0) {
            special = 0;
            bestCost = 65535;
            for (index = 0; index < count; index++) {
                if (func_0014B140((s32)input->position >> 8, input->position & 0xFF,
                                 originX, originY, targetX, targetPosition) == 1) {
                    Coord_00149C60 *candidate = &candidates[index];
                    bestIndex = index;
                    special = 1;
                    index = count;
                    candidate->x = targetX;
                    candidate->y = targetPosition;
                } else {
                    s32 cost;
                    candidate = &candidates[index];
                    cost = func_00276CC0(candidate->x, candidate->y, arg1,
                                         2, 1, (u8)func_0014B330(arg1));
                    if (cost < bestCost) {
                        bestCost = cost;
                        bestIndex = index;
                    } else if (cost == bestCost) {
                        if ((MAX_00149C60(candidate->x, targetX) - MIN_00149C60(candidate->x, targetX)) +
                                (MAX_00149C60(candidate->y, targetPosition) - MIN_00149C60(candidate->y, targetPosition)) <
                            (MAX_00149C60(candidates[bestIndex].x, targetX) - MIN_00149C60(candidates[bestIndex].x, targetX)) +
                                (MAX_00149C60(candidates[bestIndex].y, targetPosition) - MIN_00149C60(candidates[bestIndex].y, targetPosition))) {
                            bestCost = cost;
                            bestIndex = index;
                        }
                    }
                }
            }
        } else {
            output->position = input->position;
            output->action = 6;
            output->destination = origin;
            output->special = fallback;
            output->result = func_0027E360((s32)input->position >> 8,
                                         input->position & 0xFF, output->destination, 0, 0);
            func_0027B1B0(arg0, arg3);
            return 0;
        }
        if (bestIndex != 255) {
            output->position = input->position;
            output->action = 6;
            output->destination = (candidates[bestIndex].y << 8) | candidates[bestIndex].x;
            output->special = special;
            output->result = func_0027E360((s32)input->position >> 8,
                                         input->position & 0xFF, output->destination, 0, 0);
        } else {
            output->position = input->position;
            output->action = 6;
            output->destination = origin;
            output->special = special;
            output->result = func_0027E360((s32)input->position >> 8,
                                         input->position & 0xFF, output->destination, 0, 0);
            func_0027B1B0(arg0, arg3);
            return 0;
        }
    }
    return 0;
}

typedef struct Coord_0014A240 {
    u8 x : 4;
    u8 y : 4;
} Coord_0014A240;

typedef struct Unit_0014A240 {
    u16 position;
    u8 pad2[6];
    union {
        u32 packed;
        u16 low;
    } target;
} Unit_0014A240;

typedef struct Output_0014A240 {
    u16 position;
    u8 kind;
    u8 pad3;
    u16 target;
    u8 pad6[6];
    s32 value;
    u8 flag;
} Output_0014A240;

void func_001E1E70(s32, s32, s32, s32);

static inline u32 target_0014A240(void *unit, s32 side) {
    return side == 1 ? (u32)(u16)(((Unit_0014A240 *)unit)->target.packed >> 16) : (u32)((Unit_0014A240 *)unit)->target.low;
}

static inline u32 minY_0014A240(void *unit, s32 side, u8 coord) {
    return coord < (target_0014A240(unit, side) >> 8) ? coord : (target_0014A240(unit, side) >> 8);
}

static inline u32 maxY_0014A240(void *unit, s32 side, u8 coord) {
    return (target_0014A240(unit, side) >> 8) < coord ? coord : (target_0014A240(unit, side) >> 8);
}

static inline u32 minX_0014A240(void *unit, s32 side, u8 coord) {
    return coord < (target_0014A240(unit, side) & 0xFF) ? coord : (target_0014A240(unit, side) & 0xFF);
}

static inline u32 maxX_0014A240(void *unit, s32 side, u8 coord) {
    return (target_0014A240(unit, side) & 0xFF) < coord ? coord : (target_0014A240(unit, side) & 0xFF);
}

s32 func_0014A240(void *arg0, s32 arg1, void *arg2, u8 arg3, u8 arg4) {
    extern s32 func_0014AE60();
    extern s32 func_00276CC0();
    extern void func_00279230();
    extern s32 func_0027E360(s32, s32, s32, u8, s32);
    Coord_0014A240 coords[12];
    s32 initial;
    s32 cell;
    s32 count;

    initial = func_001E1090(((Unit_0014A240 *)arg0)->position >> 8, ((Unit_0014A240 *)arg0)->position & 0xFF);
    {
    s32 bestScore;
    s32 best;
    s32 side = arg3;
    Coord_0014A240 *candidate;
    s32 index;
    if (target_0014A240(arg0, side) == 0xFFFF) {
        if (initial == target_0014A240(arg0, side)) {
            ((Output_0014A240 *)arg2)->position = ((Unit_0014A240 *)arg0)->position;
            ((Output_0014A240 *)arg2)->kind = 6;
            ((Output_0014A240 *)arg2)->target = initial;
            ((Output_0014A240 *)arg2)->flag = func_0027E360(((Unit_0014A240 *)arg0)->position >> 8, ((Unit_0014A240 *)arg0)->position & 0xFF, ((Output_0014A240 *)arg2)->target, arg4, 0);
            ((Output_0014A240 *)arg2)->value = func_0014AE60(((Unit_0014A240 *)arg0)->position >> 8, ((Unit_0014A240 *)arg0)->position & 0xFF, arg0);
            func_0027B1B0(arg0, arg3);
            return 0;
        }
    }

    if (func_001E2100(((Unit_0014A240 *)arg0)->position >> 8,
                      ((Unit_0014A240 *)arg0)->position & 0xFF, 4) != 0) {
        if ((func_001E0700(((Unit_0014A240 *)arg0)->position >> 8,
                          ((Unit_0014A240 *)arg0)->position & 0xFF) >> 5) == 1 ||
            (func_001E0700(((Unit_0014A240 *)arg0)->position >> 8,
                          ((Unit_0014A240 *)arg0)->position & 0xFF) >> 5) == 5) {
            func_001E1E70(((Unit_0014A240 *)arg0)->position >> 8,
                          ((Unit_0014A240 *)arg0)->position & 0xFF, 0, 1);
            ((Output_0014A240 *)arg2)->position = ((Unit_0014A240 *)arg0)->position;
            ((Output_0014A240 *)arg2)->kind = 0xE;
            return 0;
        }
    }

    candidate = coords;
    {
        s32 i = 0;
        Coord_0014A240 *entry = candidate;
        do {
            entry->x = entry->y = 0xF;
            i++;
            entry++;
        } while (i < 12);
    }

    cell = func_001E3790(target_0014A240(arg0, side) & 0xFF, ((u32)target_0014A240(arg0, side)) >> 8);
    if (cell < 0) {
        cell = 0xFFFF;
    }
    func_00279230(((Unit_0014A240 *)arg0)->position >> 8, ((Unit_0014A240 *)arg0)->position & 0xFF,
                 coords, initial & 0xFF, initial >> 8, target_0014A240(arg0, side) & 0xFF,
                 ((u32)target_0014A240(arg0, side)) >> 8, (u16)cell, 7);
    count = func_0027AFC0((u8 *)coords);
    {
        if (count > 0) {
        best = 0xFF;
        bestScore = 0xFFFF;
        for (index = 0; index < count; index++) {
                if (func_001E36E0(candidate->x, candidate->y) == 0) {
                    s32 score = func_00276CC0(candidate->x, candidate->y, arg1, 2, 1, (u8)func_0014B330(arg1));
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
                        bestMinY = minY_0014A240(arg0, side, bestY);
                        bestMaxY = maxY_0014A240(arg0, side, bestY);
                        bestX = (&coords[best])->x;
                        bestMinX = minX_0014A240(arg0, side, bestX);
                        bestMaxX = maxX_0014A240(arg0, side, bestX);
                        currentY = (u8)candidate->y;
                        currentMinY = minY_0014A240(arg0, side, currentY);
                        currentMaxY = maxY_0014A240(arg0, side, currentY);
                        currentX = candidate->x;
                        currentMinX = minX_0014A240(arg0, side, currentX);
                        currentMaxX = maxX_0014A240(arg0, side, currentX);
                        if ((currentMaxX - currentMinX) + (currentMaxY - currentMinY) < (bestMaxX - bestMinX) + (bestMaxY - bestMinY)) {
                            bestScore = score;
                            best = index;
                        }
                    }
                }
            candidate++;
        }
    } else {
        ((Output_0014A240 *)arg2)->position = ((Unit_0014A240 *)arg0)->position;
            ((Output_0014A240 *)arg2)->kind = 6;
            ((Output_0014A240 *)arg2)->target = initial;
            ((Output_0014A240 *)arg2)->flag = func_0027E360(((Unit_0014A240 *)arg0)->position >> 8, ((Unit_0014A240 *)arg0)->position & 0xFF, ((Output_0014A240 *)arg2)->target, arg4, 0);
            ((Output_0014A240 *)arg2)->value = func_0014AE60(((Unit_0014A240 *)arg0)->position >> 8, ((Unit_0014A240 *)arg0)->position & 0xFF, arg0);
        func_0027B1B0(arg0, arg3);
        return 0;
    }

        if (best != 0xFF) {
            ((Output_0014A240 *)arg2)->position = ((Unit_0014A240 *)arg0)->position;
            ((Output_0014A240 *)arg2)->kind = 6;
            ((Output_0014A240 *)arg2)->target = (coords[best].y << 8) | coords[best].x;
            ((Output_0014A240 *)arg2)->flag = func_0027E360(((Unit_0014A240 *)arg0)->position >> 8, ((Unit_0014A240 *)arg0)->position & 0xFF, ((Output_0014A240 *)arg2)->target, arg4, 0);
            ((Output_0014A240 *)arg2)->value = func_0014AE60(((Unit_0014A240 *)arg0)->position >> 8, ((Unit_0014A240 *)arg0)->position & 0xFF, arg0);
        } else {
            ((Output_0014A240 *)arg2)->position = ((Unit_0014A240 *)arg0)->position;
            ((Output_0014A240 *)arg2)->kind = 6;
            ((Output_0014A240 *)arg2)->target = initial;
            ((Output_0014A240 *)arg2)->flag = func_0027E360(((Unit_0014A240 *)arg0)->position >> 8, ((Unit_0014A240 *)arg0)->position & 0xFF, ((Output_0014A240 *)arg2)->target, arg4, 0);
            ((Output_0014A240 *)arg2)->value = func_0014AE60(((Unit_0014A240 *)arg0)->position >> 8, ((Unit_0014A240 *)arg0)->position & 0xFF, arg0);
        }
        func_0027B1B0(arg0, arg3);
    }
    }
    return 0;
}

typedef struct {
    u8 low : 4;
    u8 high : 4;
} Nibbles_0014AAB0;

typedef struct {
    u16 pos;
} Unit_0014AAB0;

typedef struct {
    u16 pos;
    u8 kind;
    u8 pad3;
    u16 target;
    u8 pad6[6];
    s32 flag;
    u8 result;
} Out_0014AAB0;

void func_001E1E70(s32, s32, s32, s32);

s32 func_0014AAB0(void *arg0, s32 arg1, void *arg2, u8 arg3) {
    Unit_0014AAB0 *unit = arg0;
    s32 pos;
    s32 card;
    s32 col;
    u16 row;
    Out_0014AAB0 *out = arg2;
    Nibbles_0014AAB0 entries[12];
    s32 i;
    Nibbles_0014AAB0 *entry;

    pos = func_001E1090(unit->pos >> 8, unit->pos & 0xFF);
    entry = entries;
    i = 0;
    do {
        entry->low = entry->high = 15;
        entry++;
        i++;
    } while (i < 12);
    card = func_0014B490(arg1);
    if (func_001E22B0(pos & 0xFF, pos >> 8) == 9) {
        card = -1;
    }
    if (func_0027D830(unit->pos >> 8, unit->pos & 0xFF, 0, 0, 6, 0) == 5) {
        card = -1;
    }
    if (card >= 0) {
        row = card >> 16;
        col = func_0027DBC0(row, card & 0xFF, 1);
        out->pos = unit->pos;
        out->kind = 12;
        out->result = func_0027E360(unit->pos >> 8, unit->pos & 0xFF, out->target, 1, 0);
        out->flag = 1;
        out->target = (row << 8) | col;
        func_0027B1B0(unit, arg3);
        return 0;
    }
    if (func_001E2100(unit->pos >> 8, unit->pos & 0xFF, 4) != 0) {
        func_001E1E70(unit->pos >> 8, unit->pos & 0xFF, 0, 1);
        out->pos = unit->pos;
        out->kind = 14;
        return 0;
    }
    return func_00149690(unit, arg1, out, arg3);
}

s32 func_0014ACA0(void) {
    s32 player;
    s32 i;
    s32 list;
    s32 pair;

    player = func_001DE540();
    list = func_0024CA40(0, 0, player, 1, 0x111001C, 0xE);
    for (i = 0; i < func_0024E910(list); i++) {
        pair = func_0024EC50(list, i);
        if (func_001E0290(pair >> 8, pair & 0xFF, 0) > func_001E0290(pair >> 8, pair & 0xFF, 1)) {
            return 1;
        }
    }
    list = func_0024CA40(0, 0, player, 1, 0x1E001C, 0xE);
    for (i = 0; i < func_0024E910(list); i++) {
        pair = func_0024EC50(list, i);
        if (func_001E0290(pair >> 8, pair & 0xFF, 0) > func_001E0290(pair >> 8, pair & 0xFF, 1)) {
            return 1;
        }
    }
    return func_0024CA40(0, 0, player, 1, 0xB001C, 0xE) != 0 ? 1 : 0;
}

s32 func_0014AE60(s32 arg0, s32 arg1) {
    s32 kind;
    s32 pos;
    s32 slot;
    u32 *card;
    s32 found;

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
        case 0x123:
            if (func_0024E910(func_0024CA40(0, 0, arg0, 1, 6, 0xE)) >= 3) {
                return 1;
            }
            break;
        case 0x110:
        case 0x111:
            if (func_0024E910(func_0024CA40(0, 0, arg0, 1, 0x1E001C, 0xE)) > 0) {
                return 1;
            }
            break;
        }
        return 2;
    case 5:
        if (func_0027D830(arg0, arg1, 0, 0, 6, 0) == 5) {
            return 2;
        }
        if (func_0014B240(func_00250360(arg0, arg1), kind) == 1 &&
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
        case 0xD:
            return 1;
        case 2:
            found = func_0027C770(func_001DF540(arg0, arg1), pos & 0xFF, pos >> 8, 2, 6, 2);
            if (found >= 0 && found == pos) {
                return 1;
            }
            break;
        case 4:
            if (func_0014B3E0(arg0, pos & 0xFF, pos >> 8) == 1) {
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

static inline s32 max_0014B140(s32 a, s32 b) {
    if (a < b) {
        return b;
    }
    return a;
}

static inline s32 check_0014B140(s32 status) {
    if (status != 1) {
        return 0;
    }
    return 1;
}

s32 func_0014B140(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 min_y;
    s32 min_x;

    min_y = arg3 < arg5 ? arg3 : arg5;
    arg5 = max_0014B140(arg5, arg3);
    min_x = arg2 < arg4 ? arg2 : arg4;
    arg4 = max_0014B140(arg4, arg2);
    if ((arg4 - min_x) + (arg5 - min_y) != 2) {
        return 0;
    }
    if (func_001DF540(arg0, arg1) == 0) {
        return 0;
    }
    if (func_001E2100(arg0, arg1, 0) == 0) {
        return check_0014B140(func_0024DF00(func_001E22B0(arg2, arg3), arg0, arg1));
    }
    return 0;
}

s32 func_0014B240(s32 arg0, s32 arg1) {
    s32 sp50[4];
    s32 i;
    s32 mask;
    s32 low;
    s32 high;
    s32 value;
    s32 result;

    func_00254C90(sp50, *(s32 *)((u8 *)func_0026FC90(arg1, 0) + 4));
    if ((mask = func_00254890(sp50, arg0)) < 0) {
        return 0;
    }
    for (i = 0; i < func_0024E910(mask); i++) {
        value = func_0024EC50(mask, i);
        high = value >> 8;
        low = value & 0xFF;
        result = func_001E1090(high, low);
        if (func_002509E0(high, low, result & 0xFF, result >> 8) >= 0x960) {
            return 0;
        }
    }
    return 1;
}

s32 func_0014B330(s32 arg0) {
    return func_001DF470(arg0) > 0x5DC
        ? (func_001E0150(arg0) >= 4 ? 0x2EE : 0x5DC)
        : 0x7D0;
}

s32 func_0014B390(void) {
    s32 value;

    value = func_001E1030();
    if (value == 0x111 || value == 0x1E || value == 0xB) {
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_011", func_0014B3E0);

s32 func_0014B490(s32 arg0) {
    extern s32 func_001DEE50(s32);
    s32 i;

    if (func_001E0150(arg0) >= 5) {
        return -1;
    }
    if (func_0027DD20(arg0, 3, 0x111) > 0 || func_0027DD20(arg0, 3, 0x1E) > 0 ||
        func_0027DD20(arg0, 3, 0xB) > 0) {
        for (i = 0; i < func_001DEE50(arg0); i++) {
            if (func_001DEE00(arg0, i) == 0xB) {
                return (arg0 << 16) | i;
            }
        }
        for (i = 0; i < func_001DEE50(arg0 == 0 ? 1 : 0); i++) {
            if (func_001DEE00(arg0 == 0 ? 1 : 0, i) == 0xB) {
                return ((arg0 == 0 ? 1 : 0) << 16) | i;
            }
        }
        for (i = 0; i < func_001DEE50(arg0); i++) {
            if (func_001DEE00(arg0, i) == 0x1E) {
                return (arg0 << 16) | i;
            }
        }
        for (i = 0; i < func_001DEE50(arg0 == 0 ? 1 : 0); i++) {
            if (func_001DEE00(arg0 == 0 ? 1 : 0, i) == 0x1E) {
                return ((arg0 == 0 ? 1 : 0) << 16) | i;
            }
        }
        for (i = 0; i < func_001DEE50(arg0); i++) {
            if (func_001DEE00(arg0, i) == 0x111) {
                return (arg0 << 16) | i;
            }
        }
        for (i = 0; i < func_001DEE50(arg0 == 0 ? 1 : 0); i++) {
            if (func_001DEE00(arg0 == 0 ? 1 : 0, i) == 0x111) {
                return ((arg0 == 0 ? 1 : 0) << 16) | i;
            }
        }
    }
    return -1;
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
} Req_0014B730;

typedef struct {
    u8 pad0[0x160];
    u16 list[32];    /* 0x160 */
    u8 idx : 5;      /* 0x1A0 */
    u8 pad1A0 : 3;
    u8 pad1A1;
    u16 count;       /* 0x1A2 */
} Work_0014B730;

s32 func_00146960(void *, void *, s32);
s32 func_00276290(void *, void *, s32);

s32 func_0014B730(s32 arg0, void *arg1) {
    Req_0014B730 req;
    Work_0014B730 *w;
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
        if (func_00146960(w, &req, arg0) == 0) {
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

INCLUDE_ASM("asm/nonmatchings/main_011", func_0014B900);

s32 func_0014BDE0(void *arg0) {
    u16 card;
    s32 low;
    s32 type;
    s32 temp_s0;

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
                            func_0014C720(arg0);
                        } else {
                            func_0014C3B0(arg0);
                        }
                        break;
                    case 2:
                        func_0027CA50(arg0, 5, 0, func_0014F9B0(temp_s0) & 0xFF);
                        break;
                    case 1:
                        func_0014C870(arg0);
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

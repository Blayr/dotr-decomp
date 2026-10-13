#include "common.h"

typedef struct {
    u8 pad0[6];
    u8 slot[5];
} Obj1_00169420;

typedef struct {
    u8 pad0[0x3C];
    u16 id;
} Obj2_00169420;

s32 func_00169420(s32 arg0, void *arg1, void *arg2) {
    Obj1_00169420 *o1 = arg1;
    Obj2_00169420 *o2 = arg2;
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

typedef struct Nibbles_00169610 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_00169610;


s32 func_00169610(s32 arg0, u8 arg1, void *arg2, s32 arg3) {
    s32 bestPosition;
    s32 bestScore;
    Nibbles_00169610 cells[12];
    s32 targetY;
    s32 targetX;
    s32 kind;
    s32 j;
    Nibbles_00169610 *cell;

    extern s32 func_0016B0E0();
    extern s32 func_00278510();
    extern s32 func_0027A130();
    extern s32 func_002792C0(s32, s32, s32, s32, s32, s32, u16, u8);

    if (arg2 == NULL) {
        return -1;
    }
    cell = cells;
    j = 0;
    do {
        cell->low = cell->high = 15;
        j++;
        cell++;
    } while (j < 12);
    kind = (u8)(*((u8 *)arg2 + 0x3E) >> 5);
    if (kind == 0 || kind == 5) {
        if (arg3 >= 0) {
            s32 position;
            s32 y;
            s32 x;
            s32 i;
            s32 score;
            s32 target;
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
                        if (func_00278510(arg2, arg3, func_0016B0E0(arg0), targetX, targetY, 1) > 0) {
                            score = func_0027A130(arg2, cells, x, y, targetX, targetY,
                                                arg3, 1, 4, (u16)func_0016B0E0(arg0));
                        } else {
                            score = func_002792C0((s32)arg2, (s32)cells, x, y, targetX, targetY, arg3, 4);
                        }
                        if (func_0027AFC0((u8 *)cells) > 0 && score < bestScore) {
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
        }
        {
        s32 y;
        s32 x;
        s32 i;
        s32 position;
        func_001E1090(arg3 >> 8, arg3 & 255);
        i = 0;
        do {
            position = func_0024E410(arg0, i);
            if (position >= 0) {
                x = position & 255;
                y = position >> 8;
                if (func_001E22B0(x, y) != 8 &&
                    (func_001E22B0(x, y) != 9 || func_0024FE40(arg2, x, y) != 1) &&
                    func_001E3790(x, y) < 0) {
                    return position;
                }
            }
            i++;
        } while (i < 8);
        return -1;
        }
    } else {
        s32 y;
        s32 x;
        s32 i;
        s32 result;
        s32 position;
        result = -1;
        i = 0;
        do {
            position = func_0024E410(arg0, i);
            if (position >= 0) {
                x = position & 255;
                y = position >> 8;
                if (func_001E22B0(x, y) != 8 &&
                    (func_001E22B0(x, y) != 9 || func_0024FE40(arg2, x, y) != 1) &&
                    func_001E3790(x, y) < 0 && y < 8) {
                    result = position;
                }
            }
            i++;
        } while (i < 8);
        if (result >= 0) {
            return result;
        }
        result = -1;
        return result;
    }
}

typedef struct Nibbles_00169A10 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_00169A10;

typedef struct Output_00169A10 {
    u16 position;
    u8 action;
    u8 pad3;
    u16 destination;
    u8 pad6[6];
    s32 special;
    u8 result;
} Output_00169A10;

void func_001E1E70(s32, s32, s32, s32);
s32 func_00276CC0(s32, s32, s32, s32, s32, u8);
s32 func_0027BE10(s32, s32, s32, s32, s32);

s32 func_00169A10(u16 *arg0, s32 arg1, void *arg2, u8 arg3) {
    Output_00169A10 *output = arg2;
    s32 target;
    u8 endX;
    u8 extra;
    Nibbles_00169A10 nibbles[12];
    s32 bestScore;
    s32 best;
    s32 i;
    Nibbles_00169A10 *p;
    extern s32 func_0016AE30();
    extern s32 func_0016B0E0();
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

        initialScore = func_0016B0E0(arg1);
        centerX = target & 0xFF;
        centerY = target >> 8;
        if (func_00276CC0(centerX, centerY, *arg0, 2, initialScore, 1) == 0) {
            output->position = *arg0;
            output->action = 6;
            output->destination = target;
            output->result = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, output->destination, 1, 1);
            output->special = func_0016AE30(*arg0 >> 8, *arg0 & 0xFF, arg0);
            func_0027B1B0(arg0, arg3);
            return 0;
        }
        if ((range = func_002464F0(func_001DF540(*arg0 >> 8, *arg0 & 0xFF), centerX, centerY)) == 0) {
            output->position = *arg0;
            output->action = 6;
            output->destination = target;
            output->result = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, output->destination, 1, 1);
            output->special = func_0016AE30(*arg0 >> 8, *arg0 & 0xFF, arg0);
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
            extra = (u8)func_0027BBC0(*arg0 >> 8, *arg0 & 0xFF, 1);
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
                    if (func_0027BE10(*arg0 >> 8, *arg0 & 0xFF, x, y, 1) == 0 || (u8)*arg0 == 0) {
                        candidateScore = func_00276CC0(x, y, *arg0, 2, (u16)func_0016B0E0(arg1), 1);
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
                output->result = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, output->destination, 1, 1);
            } else {
                output->result = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, output->destination, 0, 1);
            }
            output->special = func_0016AE30(*arg0 >> 8, *arg0 & 0xFF, arg0);
        } else {
            output->position = *arg0;
            output->action = 6;
            output->destination = target;
            output->result = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, output->destination, 1, 1);
            output->special = func_0016AE30(*arg0 >> 8, *arg0 & 0xFF, arg0);
        }
        func_0027B1B0(arg0, arg3);
        return 0;
    }
}

typedef struct Input_00169FE0 {
    u16 position;
    u8 pad2[6];
    u32 destinations;
} Input_00169FE0;

typedef struct Output_00169FE0 {
    u16 position;
    u8 command;
    u8 pad3;
    u16 destination;
    u8 pad6[6];
    s32 state;
    u8 result;
} Output_00169FE0;

typedef struct Point_00169FE0 {
    u8 x : 4;
    u8 y : 4;
} Point_00169FE0;

static inline u32 destination_00169FE0(void *src, u8 mode) {
    if (mode == 1) {
        return (u16)(((Input_00169FE0 *)src)->destinations >> 16);
    }
    return *(u16 *)((u8 *)src + 8);
}

s32 func_00276CC0(s32, s32, s32, s32, s32, u8);

s32 func_00169FE0(void *src, s32 arg1, u16 *out, u8 arg3) {
    extern s32 func_0016AE30();
    extern s32 func_0016B0E0();
    extern void func_0027A090();
    s32 state;
    s32 current;
    s32 count;
    s32 target;
    s32 currentY;
    s32 currentX;
    s32 forced;
    s32 i;
    s32 unit;
    u32 destinationX;
    u32 destinationY;
    Point_00169FE0 points[12];

    destinationX = destination_00169FE0(src, arg3);
    destinationY = destination_00169FE0(src, arg3);
    if (func_001DF540(destinationY >> 8, destinationX & 0xFF) == 0) {
        func_0027B1B0(src, 1);
        return -1;
    }
    state = func_0016AE30(((Input_00169FE0 *)src)->position >> 8, ((Input_00169FE0 *)src)->position & 0xFF, src);
    current = func_001E1090(((Input_00169FE0 *)src)->position >> 8, ((Input_00169FE0 *)src)->position & 0xFF);
    destinationX = destination_00169FE0(src, arg3);
    destinationY = destination_00169FE0(src, arg3);
    target = func_001E1090(destinationY >> 8, destinationX & 0xFF);
    for (i = 0; i < 12; i++) {
        points[i].x = points[i].y = 0xF;
    }
    unit = func_001DF540(((Input_00169FE0 *)src)->position >> 8, ((Input_00169FE0 *)src)->position & 0xFF);
    currentX = current & 0xFF;
    currentY = current >> 8;
    if (func_002464F0(unit, currentX, currentY) == 0) {
        s32 cost;
        ((Output_00169FE0 *)out)->position = ((Input_00169FE0 *)src)->position;
        ((Output_00169FE0 *)out)->command = 6;
        ((Output_00169FE0 *)out)->destination = current;
        cost = func_00276CC0(currentX, currentY, arg1, 2, 0,
                            (u8)func_0016B0E0(arg1));
        if (cost >= func_001E0290(((Input_00169FE0 *)src)->position >> 8, ((Input_00169FE0 *)src)->position & 0xFF, 0)) {
            ((Output_00169FE0 *)out)->result = func_0027E360(((Input_00169FE0 *)src)->position >> 8, ((Input_00169FE0 *)src)->position & 0xFF,
                                       out[2], 1, 1);
        } else {
            ((Output_00169FE0 *)out)->result = func_0027E360(((Input_00169FE0 *)src)->position >> 8, ((Input_00169FE0 *)src)->position & 0xFF,
                                       out[2], 0, 1);
        }
        func_0027B1B0(src, arg3);
    } else {
        s32 y;
        s32 x;
        Point_00169FE0 *point;
        s32 index;
        s32 bestCost;
        s32 selected;
        s32 position = ((Input_00169FE0 *)src)->position;
        func_0027A090(position >> 8, position & 0xFF, points, currentX, currentY,
                      x = target & 0xFF, y = target >> 8,
                      destination_00169FE0(src, arg3), 1, 30,
                      (u16)func_0016B0E0(arg1));
        count = func_0027AFC0((u8 *)points);
        selected = 0xFF;
        if (count > 0) {
            forced = 0;
            bestCost = 0xFFFF;
            for (index = 0; index < count; index++) {
                s32 hit = func_0016AFE0(((Input_00169FE0 *)src)->position >> 8, ((Input_00169FE0 *)src)->position & 0xFF,
                                  currentX, currentY, x, y);
                if (hit == 1) {
                    Point_00169FE0 *forcedPoint = &points[index];
                    selected = index;
                    forced = 1;
                    index = count;
                    forcedPoint->x = x;
                    forcedPoint->y = y;
                } else {
                    s32 cost;
                    point = &points[index];
                    cost = func_00276CC0(point->x, point->y, arg1, 4, 0,
                                             (u8)func_0016B0E0(arg1));
                    if (cost < bestCost) {
                        bestCost = cost;
                        selected = index;
                    } else if (cost == bestCost) {
                        if (((x < point->x ? point->x : x) -
                             (point->x < x ? point->x : x)) +
                            ((y < point->y ? point->y : y) -
                             (point->y < y ? point->y : y)) <
                            ((x < points[selected].x ? points[selected].x : x) -
                             (points[selected].x < x ? points[selected].x : x)) +
                            ((y < points[selected].y ? points[selected].y : y) -
                             (points[selected].y < y ? points[selected].y : y))) {
                            bestCost = cost;
                            selected = index;
                        }
                    }
                }
            }
        } else {
            ((Output_00169FE0 *)out)->position = ((Input_00169FE0 *)src)->position;
            ((Output_00169FE0 *)out)->command = 6;
            ((Output_00169FE0 *)out)->destination = current;
            ((Output_00169FE0 *)out)->state = state;
            ((Output_00169FE0 *)out)->result = func_0027E360(((Input_00169FE0 *)src)->position >> 8, ((Input_00169FE0 *)src)->position & 0xFF,
                                       ((Output_00169FE0 *)out)->destination, 0, 1);
            func_0027B1B0(src, arg3);
            return 0;
        }
            if (selected != 0xFF) {
                ((Output_00169FE0 *)out)->position = ((Input_00169FE0 *)src)->position;
                ((Output_00169FE0 *)out)->command = 6;
                ((Output_00169FE0 *)out)->destination = (points[selected].y << 8) | points[selected].x;
                ((Output_00169FE0 *)out)->state = forced;
                ((Output_00169FE0 *)out)->result = func_0027E360(((Input_00169FE0 *)src)->position >> 8, ((Input_00169FE0 *)src)->position & 0xFF,
                                           ((Output_00169FE0 *)out)->destination, 0, 1);
            } else {
                ((Output_00169FE0 *)out)->position = ((Input_00169FE0 *)src)->position;
                ((Output_00169FE0 *)out)->command = 6;
                ((Output_00169FE0 *)out)->destination = current;
                ((Output_00169FE0 *)out)->state = forced;
                ((Output_00169FE0 *)out)->result = func_0027E360(((Input_00169FE0 *)src)->position >> 8, ((Input_00169FE0 *)src)->position & 0xFF,
                                           ((Output_00169FE0 *)out)->destination, 0, 1);
                func_0027B1B0(src, arg3);
                return 0;
            }
    }
    return 0;
}

typedef struct Coord_0016A5C0 {
    u8 x : 4;
    u8 y : 4;
} Coord_0016A5C0;

typedef struct Unit_0016A5C0 {
    u16 position;
    u8 pad2[6];
    union {
        u32 packed;
        u16 low;
    } target;
} Unit_0016A5C0;

typedef struct Output_0016A5C0 {
    u16 position;
    u8 kind;
    u8 pad3;
    u16 target;
    u8 pad6[6];
    s32 value;
    u8 flag;
} Output_0016A5C0;

void func_001E1E70(s32, s32, s32, s32);

static inline u32 target_0016A5C0(void *unit, s32 side) {
    return side == 1 ? (u32)(u16)(((Unit_0016A5C0 *)unit)->target.packed >> 16) : (u32)((Unit_0016A5C0 *)unit)->target.low;
}

static inline u32 minY_0016A5C0(void *unit, s32 side, u8 coord) {
    return coord < (target_0016A5C0(unit, side) >> 8) ? coord : (target_0016A5C0(unit, side) >> 8);
}

static inline u32 maxY_0016A5C0(void *unit, s32 side, u8 coord) {
    return (target_0016A5C0(unit, side) >> 8) < coord ? coord : (target_0016A5C0(unit, side) >> 8);
}

static inline u32 minX_0016A5C0(void *unit, s32 side, u8 coord) {
    return coord < (target_0016A5C0(unit, side) & 0xFF) ? coord : (target_0016A5C0(unit, side) & 0xFF);
}

static inline u32 maxX_0016A5C0(void *unit, s32 side, u8 coord) {
    return (target_0016A5C0(unit, side) & 0xFF) < coord ? coord : (target_0016A5C0(unit, side) & 0xFF);
}

s32 func_0016A5C0(void *arg0, s32 arg1, void *arg2, u8 arg3, u8 arg4) {
    extern s32 func_0016AE30();
    extern s32 func_0016B0E0();
    extern s32 func_00276CC0();
    extern void func_00279230();
    extern s32 func_0027E360(s32, s32, s32, u8, s32);
    Coord_0016A5C0 coords[12];
    s32 initial;
    s32 cell;
    s32 count;

    initial = func_001E1090(((Unit_0016A5C0 *)arg0)->position >> 8, ((Unit_0016A5C0 *)arg0)->position & 0xFF);
    {
    s32 bestScore;
    s32 best;
    s32 side = arg3;
    Coord_0016A5C0 *candidate;
    s32 index;
    if (target_0016A5C0(arg0, side) == 0xFFFF) {
        if (initial == target_0016A5C0(arg0, side)) {
            ((Output_0016A5C0 *)arg2)->position = ((Unit_0016A5C0 *)arg0)->position;
            ((Output_0016A5C0 *)arg2)->kind = 6;
            ((Output_0016A5C0 *)arg2)->target = initial;
            ((Output_0016A5C0 *)arg2)->flag = func_0027E360(((Unit_0016A5C0 *)arg0)->position >> 8, ((Unit_0016A5C0 *)arg0)->position & 0xFF, ((Output_0016A5C0 *)arg2)->target, arg4, 1);
            ((Output_0016A5C0 *)arg2)->value = func_0016AE30(((Unit_0016A5C0 *)arg0)->position >> 8, ((Unit_0016A5C0 *)arg0)->position & 0xFF, arg0);
            func_0027B1B0(arg0, arg3);
            return 0;
        }
    }

    if (func_001E2100(((Unit_0016A5C0 *)arg0)->position >> 8,
                      ((Unit_0016A5C0 *)arg0)->position & 0xFF, 4) != 0) {
        if ((func_001E0700(((Unit_0016A5C0 *)arg0)->position >> 8,
                          ((Unit_0016A5C0 *)arg0)->position & 0xFF) >> 5) == 1 ||
            (func_001E0700(((Unit_0016A5C0 *)arg0)->position >> 8,
                          ((Unit_0016A5C0 *)arg0)->position & 0xFF) >> 5) == 5) {
            func_001E1E70(((Unit_0016A5C0 *)arg0)->position >> 8,
                          ((Unit_0016A5C0 *)arg0)->position & 0xFF, 0, 1);
            ((Output_0016A5C0 *)arg2)->position = ((Unit_0016A5C0 *)arg0)->position;
            ((Output_0016A5C0 *)arg2)->kind = 14;
            return 0;
        }
    }

    candidate = coords;
    {
        s32 i = 0;
        Coord_0016A5C0 *entry = candidate;
        do {
            entry->x = entry->y = 0xF;
            i++;
            entry++;
        } while (i < 12);
    }

    cell = func_001E3790(target_0016A5C0(arg0, side) & 0xFF, ((u32)target_0016A5C0(arg0, side)) >> 8);
    if (cell < 0) {
        cell = 0xFFFF;
    }
    func_00279230(((Unit_0016A5C0 *)arg0)->position >> 8, ((Unit_0016A5C0 *)arg0)->position & 0xFF,
                 coords, initial & 0xFF, initial >> 8, target_0016A5C0(arg0, side) & 0xFF,
                 ((u32)target_0016A5C0(arg0, side)) >> 8, (u16)cell, 7);
    count = func_0027AFC0((u8 *)coords);
    {
        if (count > 0) {
        best = 0xFF;
        bestScore = 0xFFFF;
        for (index = 0; index < count; index++) {
                if (func_001E36E0(candidate->x, candidate->y) == 0) {
                    s32 score = func_00276CC0(candidate->x, candidate->y, arg1, 4, 0, (u8)func_0016B0E0(arg1));
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
                        bestMinY = minY_0016A5C0(arg0, side, bestY);
                        bestMaxY = maxY_0016A5C0(arg0, side, bestY);
                        bestX = (&coords[best])->x;
                        bestMinX = minX_0016A5C0(arg0, side, bestX);
                        bestMaxX = maxX_0016A5C0(arg0, side, bestX);
                        currentY = (u8)candidate->y;
                        currentMinY = minY_0016A5C0(arg0, side, currentY);
                        currentMaxY = maxY_0016A5C0(arg0, side, currentY);
                        currentX = candidate->x;
                        currentMinX = minX_0016A5C0(arg0, side, currentX);
                        currentMaxX = maxX_0016A5C0(arg0, side, currentX);
                        if ((currentMaxX - currentMinX) + (currentMaxY - currentMinY) < (bestMaxX - bestMinX) + (bestMaxY - bestMinY)) {
                            bestScore = score;
                            best = index;
                        }
                    }
                }
            candidate++;
        }
    } else {
        ((Output_0016A5C0 *)arg2)->position = ((Unit_0016A5C0 *)arg0)->position;
            ((Output_0016A5C0 *)arg2)->kind = 6;
            ((Output_0016A5C0 *)arg2)->target = initial;
            ((Output_0016A5C0 *)arg2)->flag = func_0027E360(((Unit_0016A5C0 *)arg0)->position >> 8, ((Unit_0016A5C0 *)arg0)->position & 0xFF, ((Output_0016A5C0 *)arg2)->target, arg4, 1);
            ((Output_0016A5C0 *)arg2)->value = func_0016AE30(((Unit_0016A5C0 *)arg0)->position >> 8, ((Unit_0016A5C0 *)arg0)->position & 0xFF, arg0);
        func_0027B1B0(arg0, arg3);
        return 0;
    }

        if (best != 0xFF) {
            ((Output_0016A5C0 *)arg2)->position = ((Unit_0016A5C0 *)arg0)->position;
            ((Output_0016A5C0 *)arg2)->kind = 6;
            ((Output_0016A5C0 *)arg2)->target = (coords[best].y << 8) | coords[best].x;
            ((Output_0016A5C0 *)arg2)->flag = func_0027E360(((Unit_0016A5C0 *)arg0)->position >> 8, ((Unit_0016A5C0 *)arg0)->position & 0xFF, ((Output_0016A5C0 *)arg2)->target, arg4, 1);
            ((Output_0016A5C0 *)arg2)->value = func_0016AE30(((Unit_0016A5C0 *)arg0)->position >> 8, ((Unit_0016A5C0 *)arg0)->position & 0xFF, arg0);
        } else {
            ((Output_0016A5C0 *)arg2)->position = ((Unit_0016A5C0 *)arg0)->position;
            ((Output_0016A5C0 *)arg2)->kind = 6;
            ((Output_0016A5C0 *)arg2)->target = initial;
            ((Output_0016A5C0 *)arg2)->flag = func_0027E360(((Unit_0016A5C0 *)arg0)->position >> 8, ((Unit_0016A5C0 *)arg0)->position & 0xFF, ((Output_0016A5C0 *)arg2)->target, arg4, 1);
            ((Output_0016A5C0 *)arg2)->value = func_0016AE30(((Unit_0016A5C0 *)arg0)->position >> 8, ((Unit_0016A5C0 *)arg0)->position & 0xFF, arg0);
        }
        func_0027B1B0(arg0, arg3);
    }
    }
    return 0;
}

s32 func_0016AE30(s32 arg0, s32 arg1) {
    s32 kind;
    u32 *info;

    kind = func_001E1030();
    func_00250360(arg0, arg1);
    info = func_001E0B70(arg0, arg1, 0);
    func_001E1090(arg0, arg1);
    if (func_001E2100(arg0, arg1, 4) != 0) {
        return 0;
    }
    switch (func_001E0700(arg0, arg1) >> 5) {
    case 1:
        if (func_0027D830(arg0, arg1, 0, 0, 6, 1) == 5) {
            return 2;
        }
        if (info == NULL) {
            return 2;
        }
        switch (*info >> 8) {
        case 0x27:
            if (func_001DE5C0(arg0) < 4) {
                return 1;
            }
            break;
        case 4:
            if (func_0016B0F0(arg0) == 1) {
                return 1;
            }
            break;
        }
        break;
    case 0:
        switch (kind) {
        case 0xE0:
        case 0x16C:
            if (func_001DE5C0(arg0) < 4) {
                return 1;
            }
            break;
        }
        break;
    }
    return 2;
}

s32 func_0016AFE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 minY;
    s32 maxY;
    s32 minX;
    s32 maxX;
    s32 result;

    minY = arg3 < arg5 ? arg3 : arg5;
    if (arg5 < arg3) {
        maxY = arg3;
    } else {
        maxY = arg5;
    }
    minX = arg2 < arg4 ? arg2 : arg4;
    if (arg4 < arg2) {
        maxX = arg2;
    } else {
        maxX = arg4;
    }
    if ((maxX - minX) + (maxY - minY) != 2) {
        return 0;
    }
    if (func_001DF540(arg0, arg1) == 0) {
        return 0;
    }
    if (func_001E2100(arg0, arg1, 0) == 0) {
        result = func_0024DF00(func_001E22B0(arg2, arg3), arg0, arg1);
        return result != 1 ? 0 : 1;
    }
    return 0;
}

s32 func_0016B0E0(void) {
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_016", func_0016B0F0);

typedef struct {
    u16 unk0;
    u8 unk2;
    u8 pad3;
    u16 unk4;
    u8 unk6[5];
    u8 padB;
    s32 unkC;
    u8 unk10;
} Req_0016B1F0;

typedef struct {
    u8 pad0[0x160];
    u16 list[32];    /* 0x160 */
    u8 idx : 5;      /* 0x1A0 */
    u8 pad1A0 : 3;
    u8 pad1A1;
    u16 count;       /* 0x1A2 */
} Work_0016B1F0;

s32 func_001678B0(void *, void *, s32);
s32 func_00276290(void *, void *, s32);

s32 func_0016B1F0(s32 arg0, void *arg1) {
    Req_0016B1F0 req;
    Work_0016B1F0 *w;
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
        if (func_001678B0(w, &req, arg0) == 0) {
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

#define MAX_0016B3C0(a, b) ((a) > (b) ? (a) : (b))
#define MIN_0016B3C0(a, b) ((a) < (b) ? (a) : (b))

s32 func_0016B3C0(s32 arg0) {
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
            if (MAX_0016B3C0(y0, y) - MIN_0016B3C0(y0, y) + (MAX_0016B3C0(x0, x) - MIN_0016B3C0(x0, x)) == 1) {
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

s32 func_0016B610(s32 arg0, s32 arg1, void *arg2) {
    s32 mask = 0;
    s32 count = 0;
    s32 owner;
    s32 *effect;
    s32 card;
    s32 position;
    s32 i;
    s32 y;
    s32 x;
    s32 y55;
    s32 x55;
    s32 index55;
    s32 value;
    s32 otherCount;
    s32 otherMask;
    s32 otherIndex;
    s32 handIndex;
    u32 word;
    s16 buffer[24];
    extern s32 func_001E1030();
    extern s32 func_001E1580();
    extern s32 func_001DEE50();
    extern s32 func_00215D30();

    card = func_001E1030();
    position = func_001E1090(arg0, arg1);
    owner = func_00250360(arg0, arg1);
    effect = func_001E0B70(arg0, arg1, 0);
    func_0024C910(owner, 2, buffer);
    if (func_001E2100(arg0, arg1, 4)) {
        return 0;
    }
    if (func_0016CF10(card) == 1) {
        if (func_0016CF30(owner) == 1 && func_0016CFF0(owner) == 4) {
            return 1;
        }
    }

    switch (func_001E0700(arg0, arg1) >> 5) {
    case 5:
        if (func_0027D830(arg0, arg1, 0, 0, 6, 0) == 5) {
            return 2;
        }
        if (func_0016CE00(func_00250360(arg0, arg1), card) == 1 &&
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
        word = (u32)effect[0];
        switch (word >> 8) {
        case 0x17:
        case 0x49:
            if (func_0016C6B0(owner, (word >> 6) & 3, word & 0x3F) == 1) {
                return 1;
            }
            break;
        case 0x18:
            mask = func_0024CA40(0, 0, owner, 2, 0x34, 0xE);
            for (i = 0; i < func_0024E910(mask); i++) {
                value = func_0024EC50(mask, i);
                if (func_001E2100(value >> 8, value & 0xFF, 4) == 1) {
                    count++;
                }
            }
            if (count > 5) {
                return 1;
            }
            break;
        case 2:
            value = func_0027C770(func_001DF540(arg0, arg1), position & 0xFF,
                                 position >> 8, *(u8 *)(effect + 1), 8, 2);
            if (value >= 0 && value == position) {
                return 1;
            }
            break;
        case 4:
            switch ((u32)effect[1] >> 16) {
            case 0x12:
                value = func_0016CBB0(arg0, effect);
                if (value >= 0 && ((position & 0xFF) == (value & 0xFF) ||
                                  (position >> 8) == (value >> 8))) {
                    return 1;
                }
                break;
            case 0x13:
            default:
                if (func_0016C6B0(owner, (word >> 6) & 3, word & 0x3F) == 1) {
                    return 1;
                }
                break;
            }
            break;
        case 0xD:
            if (((word >> 6) & 3) == 1) {
                if (((u32)effect[1] >> 16) == 4) {
                    if (func_001DF470(owner) < 1201) {
                        return 1;
                    }
                    break;
                }
                return 1;
            }
            if ((word & 0x3F) == 0x32) {
                if (func_0024E780(owner == 0 ? 1 : 0, 3) > 3) {
                    return 1;
                }
                break;
            }
            return 1;
        case 0x1F:
            if (card == 0x2DD && func_0016B3C0(owner) >= 0) {
                return 1;
            }
            break;
        case 0x20:
            for (mask = 0; mask < 11; mask++) {
                if (func_001E1580(arg0, mask) == 0xFF) {
                    return 1;
                }
            }
            break;
        case 0x12:
            mask = func_0024CA40(0, 0, owner, 1, word & 0x3F, 0xE);
            if (func_0024E910(mask) > 2) {
                return 1;
            }
            break;
        case 0x21:
            {
                s32 targetPosition;
                s32 sourcePosition;
                s32 targetY;

                func_0027C2C0(owner == 0 ? 1 : 0, (u16 *)buffer, 0x1D, 0, 0);
                value = func_0027B650((u16 *)buffer);
                arg0 = value >> 8;
                arg1 = value & 0xFF;
                sourcePosition = func_001E1090(arg0, arg1);
                func_0027C070(owner, (u16 *)buffer, 0x1D, 1);
                value = func_0027B650((u16 *)buffer);
                card = value >> 8;
                targetY = value & 0xFF;
                targetPosition = func_001E1090(card, targetY);
                func_0024C910(owner, 1, buffer);
                owner = sourcePosition & 0xFF;
                count = sourcePosition >> 8;
                if (func_002509E0(arg0, arg1, owner, count) >= 2500) {
                    count = func_002509E0(arg0, arg1, owner, count);
                    if (func_002509E0(card, targetY, targetPosition & 0xFF,
                                     targetPosition >> 8) < count) {
                        return 1;
                    }
                }
            }
            break;
        case 0x36:
            return 1;
        case 0x25:
            switch (word & 0x3F) {
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
        word = (u32)effect[0];
        switch (word >> 8) {
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
            mask = func_0024CA40(0, 0, arg0, 1, word & 0x3F, 0xE);
            if ((u32)mask > 1) {
                return 1;
            }
            break;
        case 0x13:
        case 0x17:
            if (((word >> 6) & 1) &&
                func_0024CA40(0, 0, arg0, 1, word & 0x3F, 0xE) != 0) {
                return 2;
            }
            mask = func_0027E150(func_0024CA40(0, 0, arg0, 2,
                                            (u32)effect[0] & 0x3F, 0xE));
            if ((u32)mask > 2) {
                return 1;
            }
            break;
        case 0x47:
            mask = func_0024CA40(0, 0, arg0, 2, 0x34, 0xE);
            for (i = 0; i < func_0024E910(mask); i++) {
                value = func_0024EC50(mask, i);
                x = value >> 8;
                y = value & 0xFF;
                if (func_001E1580(x, y) > 0 && func_001E1580(x, y) != 0xFF) {
                    return 1;
                }
            }
            break;
        case 0x53:
            for (handIndex = 0; handIndex < func_001DEE50(arg0); handIndex++) {
                if ((func_0026FCE0(func_001DEE00(arg0, handIndex)) >> 5) == 0) {
                    count++;
                }
            }
            for (handIndex = 0; handIndex < func_001DEE50(arg0 == 0 ? 1 : 0); handIndex++) {
                if ((func_0026FCE0(func_001DEE00(arg0 == 0 ? 1 : 0, handIndex)) >> 5) == 0) {
                    count++;
                }
            }
            if (count > 5) {
                return 1;
            }
            break;
        case 0x54:
            mask = func_0024CA40(0, 0, arg0, 3, 0x21, 0xE);
            value = func_0024EC50(mask, 0);
            if (arg0 == func_00250360(value >> 8, value & 0xFF) &&
                value != ((arg0 << 8) | arg1)) {
                return 1;
            }
            break;
        case 0x55:
            mask = func_0024CA40(0, 0, arg0, 1, 0x34, 0xE);
            for (index55 = 0; index55 < func_0024E910(mask); index55++) {
                value = func_0024EC50(mask, index55);
                x55 = value >> 8;
                y55 = value & 0xFF;
                if (func_001E1580(x55, y55) > 0 && func_001E1580(x55, y55) != 0xFF) {
                    return 1;
                }
            }
            break;
        case 0x58:
            if (func_00215D30(arg0 == 0 ? 1 : 0,
                            func_001E1030(arg0 == 0 ? 1 : 0, 0)) >= 6) {
                return 1;
            }
            break;
        }
        effect = func_00250740(arg0, arg1, 3);
        if (effect == NULL) {
            return 2;
        }
        word = (u32)effect[0];
        switch (word >> 8) {
        case 0x12:
            if (((u32)effect[1] >> 16) == 0x16) {
                mask = func_0024CA40(0, 0, owner, 1, word & 0x3F, 0x16);
            } else {
                mask = func_0024CA40(0, 0, owner, 1,
                                    (((u32)effect[1] >> 16) << 16) | (word & 0x3F), 0xE);
            }
            if (func_0024E910(mask) > 2) {
                return 1;
            }
            break;
        case 0x33:
            mask = func_0024CA40(0, 0, owner, 1,
                                (((u32)effect[1] >> 16) << 16) | (word & 0x3F), 0xE);
            if (func_0024E910(mask) > 2) {
                return 1;
            }
            break;
        case 0x17:
            if ((word & 0x3F) == 0x1A) {
                return 2;
            }
            if (func_0016C6B0(owner, (word >> 6) & 3, word & 0x3F) == 1) {
                return 1;
            }
            break;
        case 0xD:
            return 1;
        case 0x23:
            if (func_0016C6B0(owner, (word >> 6) & 3, word & 0x3F) == 1) {
                return 1;
            }
            break;
        case 0x18:
            mask = func_0024CA40(0, 0, owner, 1, word & 0x3F, 0xE);
            for (i = 0; i < func_0024E910(mask); i++) {
                value = func_0024EC50(mask, i);
                if (func_001E2100(value >> 8, value & 0xFF, 4) == 1) {
                    count++;
                }
            }
            if (count > 2) {
                return 2;
            }
            otherCount = 0;
            otherMask = func_0024CA40(0, 0, owner, 2, (u32)effect[0] & 0x3F, 0xE);
            for (otherIndex = 0; otherIndex < func_0024E910(otherMask); otherIndex++) {
                value = func_0024EC50(otherMask, otherIndex);
                if (func_001E2100(value >> 8, value & 0xFF, 4) == 1) {
                    otherCount++;
                }
            }
            if (otherCount > 5) {
                return 1;
            }
            break;
        case 4:
            if ((word & 0x3F) == 0x1A) {
                return 2;
            }
            if ((word & 0x3F) == 0x30) {
                if (func_0016C6B0(owner, (word >> 6) & 3, word & 0x3F) == 1) {
                    return 1;
                }
            } else if (((u32)effect[1] >> 16) != 0) {
                value = func_001E1090(arg0, arg1);
                mask = func_0024CA40(value & 0xFF, value >> 8, owner,
                                    ((u32)effect[0] >> 6) & 3, (u32)effect[0] & 0x3F,
                                    (u32)effect[1] >> 16);
            } else {
                mask = func_0024CA40(0, 0, owner, (word >> 6) & 3, word & 0x3F, 0xE);
            }
            for (i = 0; i < func_0024E910(mask); i++) {
                value = func_0024EC50(mask, i);
                arg0 = value >> 8;
                arg1 = value & 0xFF;
                if (owner == func_00250360(arg0, arg1)) {
                    return 2;
                }
                if (func_001E2100(arg0, arg1, 4)) {
                    count++;
                }
            }
            if (count > 1) {
                return 1;
            }
            break;
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
            word = (u32)effect[0];
            if ((word & 0x3F) == 0x1A) {
                return 2;
            }
            mask = func_0024CA40(0, 0, owner, (word >> 6) & 3, word & 0x3F, 0xE);
            if (func_0024E910(mask) > 2) {
                return 1;
            }
            break;
        case 0x3C:
            if (func_0024CA40(position & 0xFF, position >> 8, owner, 1,
                              ((u32)*(u16 *)(effect + 1) << 16) | (word & 0x3F), 1) &&
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
    }
    return 2;
}

s32 func_0016C6B0(s32 arg0, s32 arg1, s32 arg2) {
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
    if (best_own < best_other && best_other > 2500) {
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

INCLUDE_ASM("asm/nonmatchings/main_016", func_0016C8F0);

s32 func_0016CBB0(s32 arg0, s32 *arg1) {
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
} Data_0016CE00;

s32 func_0016CE00(s32 arg0, s32 arg1) {
    extern u32 func_0026FBB0();
    s32 state[4];
    s32 index;
    s32 mask;
    u32 limit;
    s32 low;
    s32 high;
    s32 encoded;
    s32 position;
    Data_0016CE00 *data;

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

s32 func_0016CF10(s32 arg0) {
    return ((u32) (arg0 - 0x36) < 4U) ? 1 : 0;
}

s32 func_0016CF30(s32 arg0) {
    extern s32 func_001E1030();

    if (func_001E1030(arg0, 0) == 0x3A) {
        if (func_002151D0(arg0, func_002158B0(arg0), 0x36) >= 0 && func_002151D0(arg0, func_002158B0(arg0), 0x37) >= 0 && func_002151D0(arg0, func_002158B0(arg0), 0x38) >= 0 && func_002151D0(arg0, func_002158B0(arg0), 0x39) >= 0) {
            return 1;
        }
    }
    return 0;
}

s32 func_0016CFF0(s32 arg0) {
    extern s32 func_001E1030();
    extern s32 func_001E1580();
    extern s32 func_001E1640();
    s32 i;
    s32 count;
    s32 j;
    s32 type;
    s32 v;
    s32 found[4];

    count = 0;
    if (func_001E1030(arg0, 0) == 0x3A) {
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 8; j++) {
                v = func_0024E410(arg0, j);
                if (func_001E36E0(v & 0xFF, v >> 8) != 0) {
                    v = func_001E3790(v & 0xFF, v >> 8);
                    if (v >= 0) {
                        type = func_001E1030(v >> 8, v & 0xFF);
                        if (type == func_002686F0(i) &&
                            func_001E1580(v >> 8, v & 0xFF) == 0 &&
                            func_001E1640(v >> 8, v & 0xFF) == 0 &&
                            (v >> 8) == arg0) {
                            found[i] = 1;
                        }
                    }
                }
            }
            count += found[i];
        }
        return count;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_016", func_0016D140);

static inline s32 check_0016D6A0(s32 value) {
    s32 result = 1;

    result = ((u32)(value - 0x36) < 4) ? result : 0;
    return result;
}

s32 func_0016D6A0(void *arg0) {
    s32 result0;
    s32 result1;

    extern s32 func_001E1030();
    extern s32 func_0016E510(void *arg0);

    result0 = func_001E1030(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF);
    func_001E1090(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF);
    result1 = func_00250360(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF);
    if (func_001DF540(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF) != 0 &&
        func_001E2100(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF, 0) == 0) {
        u16 code = *(u16 *)arg0;

        if (code != 0xFFFF) {
            if ((code & 0xFF) == 0) {
                if (((s32 *)arg0)[2] == -1) {
                    if (func_0027BBC0(code >> 8, code & 0xFF, 0) == 1) {
                        if (func_001DE6D0(*(u16 *)arg0 >> 8) == 1) {
                            ((u16 *)arg0)[2] = 0x50A;
                        } else {
                            ((u16 *)arg0)[2] = 0x5FF;
                        }
                    } else {
                        if (func_001DE6D0(*(u16 *)arg0 >> 8) == 1) {
                            ((u16 *)arg0)[2] = 0xA05;
                        } else {
                            ((u16 *)arg0)[2] = 0x5FF;
                        }
                    }
                }
            } else {
                s32 type = func_001E0700(code >> 8, code & 0xFF) >> 5;

                switch (type) {
                case 0:
                    if (func_002507D0(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF) == 1 ||
                        check_0016D6A0(result0) == 1) {
                        func_0016E510(arg0);
                    } else {
                        func_0016DCA0((u16 *)arg0);
                    }
                    break;
                case 2:
                    func_0027CA50(arg0, 5, 0, (u8)func_00172310(result1));
                    break;
                case 1:
                case 3:
                case 4:
                    func_0016F240((u16 *)arg0);
                    break;
                default:
                    ((u16 *)arg0)[2] = 0x5FF;
                    break;
                }
            }
            return 1;
        }
    }
    return 0;
}

s32 func_0016D8C0(u16 *arg0, s32 arg1, s32 arg2) {
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
    func_0016D6A0(arg0 + idx * 8);
    if (((arg0[idx * 8 + 2] >> 8) & 0xFF) == 10) {
        if (func_001DE6D0(arg1) == 1 && func_0016F4D0(pos, arg1, arg2) >= 0) {
            return pos | 0x10000;
        }
        if (func_0027B9B0(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (func_001E2100(arg1, 0, 0) == 0) {
        if (func_0027B9B0(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (func_001DE6D0(arg1) == 1 && func_0016F4D0(pos, arg1, arg2) >= 0) {
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

void func_0016DCA0(u16 *arg0) {
    extern s32 func_0016DDA0();
    s32 temp_s1;
    u16 temp_v0;
    u16 temp_v0_2;
    u16 temp_v0_3;
    u16 temp_v0_4;
    u16 temp_v0_5;
    u16 temp_v1;

    temp_v0 = *arg0;
    if (func_001DF540((s32) temp_v0 >> 8, temp_v0 & 0xFF) != 0) {
        temp_v0_2 = *arg0;
        temp_s1 = ((func_0024DE70((s32) temp_v0_2 >> 8, temp_v0_2 & 0xFF) == 0) ? 1 : 0) << 8;
        temp_v1 = *arg0;
        func_001E1090((s32) temp_v1 >> 8, temp_v1 & 0xFF);
        func_001E1090(temp_s1 >> 8, temp_s1 & 0xFF);
        temp_v0_3 = *arg0;
        func_001DF540((s32) temp_v0_3 >> 8, temp_v0_3 & 0xFF);
        temp_v0_4 = *arg0;
        if (func_001E0290((s32) temp_v0_4 >> 8, temp_v0_4 & 0xFF, 0) >= 0x9C4) {
            func_0016DDA0(arg0);
            return;
        }
        temp_v0_5 = *arg0;
        if (func_0016E000((s32) temp_v0_5 >> 8, temp_v0_5 & 0xFF, 1) == 1) {
            func_0016E0E0(arg0, 1);
            return;
        }
        func_0016DDA0(arg0, 1);
    }
}

typedef struct {
    u16 card;
    u8 flag;
    u8 pad3;
} Slot_0016DDA0;

typedef struct {
    u16 low;
    u16 high;
} DataHalves_0016DDA0;

typedef struct {
    u16 coordinates;
    u8 pad2[2];
    u16 state;
    u8 pad6[2];
    union {
        u32 word;
        DataHalves_0016DDA0 halves;
    } data;
} Entry_0016DDA0;

void func_0016DDA0(void *arg0) {
    extern s32 func_0027B200();
    extern void func_0027E770();
    extern s32 func_0016E4B0();
    Entry_0016DDA0 *entry = arg0;
    s32 pos;
    s32 other;
    s32 side;
    s32 player;
    s32 otherPos;
    s32 i;
    u8 work[0x70];
    Slot_0016DDA0 list[22];
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
        func_0027E770(work);
        if (func_0027B200(entry->coordinates >> 8, entry->coordinates & 0xFF, pos & 0xFF, pos >> 8,
                          other >> 8, other & 0xFF, otherPos & 0xFF, otherPos >> 8, 5) > 0) {
            entry->state = 0x2FF;
            entry->data.word = (other << 16) | entry->data.halves.low;
            return;
        }
        countB = 0;
        countA = 0;
        i = 1;
        while (1) {
            switch (func_0016E4B0(entry, 0, player, pos & 0xFF, pos >> 8,
                                  side == 0 ? 1 : 0,
                                  (u8)i, func_00172310(side), list, 0,
                                  &countA, &countB, 5, work)) {
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
                entry->state = 0x3FF;
                entry->data.word = (pos << 16) | entry->data.halves.low;
                return;
            default:
                break;
            }
            i++;
            if (i > 5) {
                break;
            }
        }
        entry->state = 0x6FF;
        entry->data.word = (otherPos << 16) | entry->data.halves.low;
    }
}

s32 func_0016E000(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_s2;
    s32 temp_v0;
    s32 var_s3;
    s32 var_s4;
    s32 packed;

    if ((arg2 & 0xFF) == 1) {
        var_s4 = 3;
    } else {
        var_s4 = 4;
    }
    packed = (arg0 << 8) | arg1;
    var_s3 = 1;
    for (;;) {
        temp_v0 = func_001E3790(var_s3, var_s4);
        if (temp_v0 != 0) {
            if (temp_v0 == packed) {
                return 1;
            }
            temp_s2 = func_00250360(temp_v0 >> 8, temp_v0 & 0xFF);
            if (temp_s2 == func_00250360(arg0, arg1)) {
                return 0;
            }
        }
        var_s3++;
        if (var_s3 > 5) {
            break;
        }
    }
    return 1;
}

typedef struct {
    u16 position;
    u8 flag;
    u8 pad;
} Slot_0016E0E0;

void func_0016E0E0(u16 *arg0, s32 arg1) {
    u8 work[112];
    Slot_0016E0E0 slots[22];
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
    extern s32 func_0016E4B0();
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
            switch (func_0016E4B0(record, 0, owner, position & 0xFF, position >> 8,
                                  func_0024DE70((s32) record[0] >> 8, record[0] & 0xFF) == 0 ? 1 : 0, (u8) i,
                                  func_00172310(player), slots, 0, &b, &a, 2, work)) {
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

void func_0016E4B0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28) {
    func_0027DE20(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
                  arg_sp0, arg_sp8, arg_sp10, arg_sp18, arg_sp20,
                  0, 2500, arg_sp28);
}

typedef struct Candidate_0016E510 {
    u16 card;
    u8 index;
    u8 flags;
} Candidate_0016E510;

static inline s32 max_0016E510(s32 a, s32 b) {
    if (a < b) {
        return b;
    }
    return a;
}

static inline s32 ready_0016E510(s32 player) {
    extern s32 func_001E1030();

    if (func_001E1030(player, 0) == 0x3A &&
        func_002151D0(player, func_002158B0(player), 0x36) >= 0 &&
        func_002151D0(player, func_002158B0(player), 0x37) >= 0 &&
        func_002151D0(player, func_002158B0(player), 0x38) >= 0 &&
        func_002151D0(player, func_002158B0(player), 0x39) >= 0) {
        return 1;
    }
    return 0;
}

void func_0016E510(u16 *arg0) {
    u8 work[112];
    Candidate_0016E510 list[22];
    s16 first;
    s16 second;
    u16 length;
    s32 player;
    s32 position;
    s32 distance;
    s32 count;
    s32 type;
    s32 x;
    s32 y;
    s32 x55;
    s32 y55;
    s32 retry_y;
    s32 retry_x;
    s32 nearest_y;
    s32 nearest_x;
    s32 mask;
    s32 mask55;
    s32 nearest_mask;
    s32 i;
    s32 i55;
    s32 nearest_i;
    s32 attempt;
    s32 card;
    s32 cursor;
    u32 *effect;
    u32 *action;
    s32 ready;
    s32 nearest;
    s32 maxy;
    s32 miny;
    s32 maxx;
    s32 minx;
    s32 other;
    s32 result;
    s32 result55;
    s32 nearest_card;
    s32 nearest_position;
    s32 nearest_delta;
    s32 n;
    Candidate_0016E510 *p;
    extern s32 func_001E1030();
    extern s32 func_00170610();
    extern s32 func_001E1580();
    extern s32 func_001DEE50();
    extern s32 func_00215D30();
    extern s32 func_002770E0();
    extern s32 func_00277160();
    extern void func_0027E770();

    count = 0;
    player = func_00250360(arg0[0] >> 8, arg0[0] & 0xFF);
    type = func_001E1030(arg0[0] >> 8, arg0[0] & 0xFF);
    func_001DF540(arg0[0] >> 8, arg0[0] & 0xFF);
    position = func_001E1090(arg0[0] >> 8, arg0[0] & 0xFF);
    if ((card = func_001DF540(arg0[0] >> 8, arg0[0] & 0xFF)) != 0) {
        p = list;
        length = 0;
        second = 0;
        first = 0;
        cursor = 0;
        n = 0;
        do {
            n++;
            p->card = 0xFFFF;
            p->index = 0xFF;
            p++;
        } while (n < 22);
        func_0027E770(work);
        if (((u32)(type - 0x36) < 4 ? 1 : 0) == 1) {
            ready = ready_0016E510(player);
            i = 0;
            if (ready == 1) {
                do {
                    if (position == func_00170610(player, i)) {
                        arg0[2] = 0x6FF;
                        *(u32 *)&arg0[4] = (position << 16) | arg0[4];
                    }
                    i++;
                } while (i < 9);
                arg0[2] = 0x6FF;
                *(u32 *)&arg0[4] = arg0[4] | (func_001E1090(player, 0) << 16);
                return;
            }
        }
        effect = func_00250740(arg0[0] >> 8, arg0[0] & 0xFF, 2);
        if (effect != NULL) {
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
                arg0[2] = 0x3FF;
                *(u32 *)&arg0[4] = (position << 16) | arg0[4];
                return;
            case 0xB:
            case 0x4E:
            case 0x12:
            case 0x4D:
            case 0x6:
                if ((u32)func_0024CA40(0, 0, player, 1, effect[0] & 0x3F, 14) > 1U) {
                    arg0[2] = 0x3FF;
                    *(u32 *)&arg0[4] = (position << 16) | arg0[4];
                    return;
                }
                break;
            case 0x13:
            case 0x17:
                if (((effect[0] >> 6) & 1) && func_0024CA40(0, 0, player, 1, effect[0] & 0x3F, 14) != 0) {
                    if (func_001DF540(arg0[0] >> 8, arg0[0] & 0xFF) != 0) {
                        other = (func_0024DE70(arg0[0] >> 8, arg0[0] & 0xFF) == 0 ? 1 : 0) << 8;
                        func_001E1090(arg0[0] >> 8, arg0[0] & 0xFF);
                        func_001E1090(other >> 8, other & 0xFF);
                        func_001DF540(arg0[0] >> 8, arg0[0] & 0xFF);
                        if (func_001E0290(arg0[0] >> 8, arg0[0] & 0xFF, 0) >= 2500) {
                            func_0016DDA0(arg0);
                        } else if (func_0016E000(arg0[0] >> 8, arg0[0] & 0xFF, 1) == 1) {
                            func_0016E0E0(arg0, 1);
                        } else {
                            func_0016DDA0(arg0);
                        }
                    }
                    return;
                }
                if ((u32)func_0027E150(func_0024CA40(0, 0, player, 2, effect[0] & 0x3F, 14)) > 2U) {
                    arg0[2] = 0x3FF;
                    *(u32 *)&arg0[4] = (position << 16) | arg0[4];
                    return;
                }
                break;
            case 0x47:
                mask = func_0024CA40(0, 0, player, 2, 0x34, 14);
                i = 0;
                if (0 < func_0024E910(mask)) {
                    do {
                        result = func_0024EC50(mask, i);
                        y = result >> 8;
                        x = result & 0xFF;
                        if (func_001E1580(y, x) > 0 && func_001E1580(y, x) != 0xFF) {
                            arg0[2] = 0x3FF;
                            *(u32 *)&arg0[4] = (position << 16) | arg0[4];
                            return;
                        }
                        i++;
                    } while (i < func_0024E910(mask));
                }
                break;
            case 0x53:
                i = 0;
                if (0 < func_001DEE50(player)) {
                    do {
                        if ((func_0026FCE0(func_001DEE00(player, i)) >> 5) == 0) {
                            count++;
                        }
                        i++;
                    } while (i < func_001DEE50(player));
                }
                i = 0;
                while (i < func_001DEE50((player == 0 ? 1 : 0))) {
                    if ((func_0026FCE0(func_001DEE00((player == 0 ? 1 : 0), i)) >> 5) == 0) {
                        count++;
                    }
                    i++;
                }
                if (count > 5) {
                    arg0[2] = 0x3FF;
                    *(u32 *)&arg0[4] = (position << 16) | arg0[4];
                    return;
                }
                break;
            case 0x54:
                result = func_0024EC50(func_0024CA40(0, 0, player, 3, 0x21, 14), 0);
                if (player == func_00250360(result >> 8, result & 0xFF) && result != arg0[0]) {
                    arg0[2] = 0x3FF;
                    *(u32 *)&arg0[4] = (position << 16) | arg0[4];
                    return;
                }
                break;
            case 0x55:
                mask55 = func_0024CA40(0, 0, player, 1, 0x34, 14);
                i55 = 0;
                if (0 < func_0024E910(mask55)) {
                    do {
                        result55 = func_0024EC50(mask55, i55);
                        y55 = result55 >> 8;
                        x55 = result55 & 0xFF;
                        if (func_001E1580(y55, x55) > 0 && func_001E1580(y55, x55) != 0xFF) {
                            arg0[2] = 0x3FF;
                            *(u32 *)&arg0[4] = (position << 16) | arg0[4];
                            return;
                        }
                        i55++;
                    } while (i55 < func_0024E910(mask55));
                }
                break;
            case 0x58:
                if (func_00215D30((player == 0 ? 1 : 0), func_001E1030((player == 0 ? 1 : 0), 0)) >= 6) {
                    arg0[2] = 0x3FF;
                    *(u32 *)&arg0[4] = (position << 16) | arg0[4];
                    return;
                }
                break;
            }
        }
        action = func_00250740(arg0[0] >> 8, arg0[0] & 0xFF, 3);
        if (func_001E2100(arg0[0] >> 8, arg0[0] & 0xFF, 4) == 0 && action != NULL) {
            switch (action[0] >> 8) {
            case 0x17:
                if ((action[0] & 0x3F) == 0x1A && func_0027D720(arg0, 0) == 1) {
                    arg0[2] = 0xBFF;
                    return;
                }
                break;
            case 0x14:
                arg0[2] = 0xCFF;
                return;
            case 0x4:
                if ((action[0] & 0x3F) == 0x1A && func_0027D720(arg0, 0) == 1) {
                    arg0[2] = 0xBFF;
                    if ((action[1] >> 16) != 2) {
                        return;
                    }
                    result = (u16)func_001E0700((u32)(u16)(*(u32 *)&arg0[4] >> 16) >> 8, (*(u32 *)&arg0[4] >> 16) & 0xFF);
                    if ((result >> 5) == 0 && (result & 0x1F) == 2) {
                        return;
                    }
                }
                break;
            case 0x16:
                if (func_0027D720(arg0, 0) == 1) {
                    arg0[2] = 0xBFF;
                    return;
                }
                break;
            case 0x24:
                if (((action[0] & 0x3F) == 0x1A || (action[0] & 0x3F) == 0x1B) && func_0027D720(arg0, 0) == 1) {
                    arg0[2] = 0xBFF;
                    return;
                }
                break;
            case 0x1F:
                if (func_00266DF0(0x39) <= 0 && (action[0] & 0x3F) == 0x1A && func_0027D720(arg0, 0) == 1) {
                    arg0[2] = 0xBFF;
                    if ((action[1] >> 16) != 14) {
                        return;
                    }
                    result = (u16)func_001E0700((u32)(u16)(*(u32 *)&arg0[4] >> 16) >> 8, (*(u32 *)&arg0[4] >> 16) & 0xFF);
                    if ((result >> 5) == 0 && (result & 0x1F) == 14) {
                        return;
                    }
                }
                break;
            case 0x25:
                attempt = 1;
                retry_y = position >> 8;
                retry_x = position & 0xFF;
                while (1) {
                    cursor = func_002770E0(cursor, card, retry_x, retry_y, (player == 0 ? 1 : 0), (u8)attempt, 0, func_00172310(player), list, &length, &first, &second, work);
                    result = func_00277160(card, retry_x, retry_y, list, 5, 0x34, 0, 2, 0, func_00172310(player), length);
                    if (result >= 0) {
                        arg0[2] = 0x2FF;
                        *(u32 *)&arg0[4] = (result << 16) | arg0[4];
                        return;
                    }
                    attempt++;
                    if (attempt <= 5) {
                        continue;
                    }
                    break;
                }
                break;
            case 0x3C:
                nearest_mask = func_0024CA40(0, 0, player, 3, 0x26D, 14);
                distance = 7;
                nearest = -1;
                if (nearest_mask != 0) {
                    nearest_i = 0;
                    if (0 < func_0024E910(nearest_mask)) {
                        nearest_y = position >> 8;
                        nearest_x = position & 0xFF;
                        do {
                            nearest_card = func_0024EC50(nearest_mask, nearest_i);
                            nearest_position = func_001E1090(nearest_card >> 8, nearest_card & 0xFF);
                            miny = nearest_y < (nearest_position >> 8) ? nearest_y : (nearest_position >> 8);
                            maxy = max_0016E510(nearest_position >> 8, nearest_y);
                            minx = nearest_x < (nearest_position & 0xFF) ? nearest_x : (nearest_position & 0xFF);
                            maxx = max_0016E510(nearest_position & 0xFF, nearest_x);
                            nearest_delta = (maxx - minx) + (maxy - miny);
                            if (nearest_delta < distance) {
                                distance = nearest_delta;
                                nearest = nearest_card;
                            }
                            nearest_i++;
                        } while (nearest_i < func_0024E910(nearest_mask));
                    }
                    if (nearest >= 0) {
                        arg0[2] = 0xBFF;
                        *(u32 *)&arg0[4] = (nearest << 16) | arg0[4];
                        return;
                    }
                }
                break;
            case 0xC:
                arg0[2] = 0x3FF;
                *(u32 *)&arg0[4] = (position << 16) | arg0[4];
                return;
            case 0x46:
                if (func_0027D720(arg0, 0) == 1) {
                    arg0[2] = 0xBFF;
                }
                return;
            case 0x51:
                if (func_0027D720(arg0, 0) == 1) {
                    return;
                }
                break;
            }
        }
        action = func_00250740(arg0[0] >> 8, arg0[0] & 0xFF, 1);
        if (action != NULL) {
            switch (action[0] >> 8) {
            case 0x42:
                if (((action[0] >> 6) & 3) == 1) {
                    arg0[2] = 0x6FF;
                    *(u32 *)&arg0[4] = (position << 16) | arg0[4];
                }
                break;
            }
        }
        if (func_001DF540(arg0[0] >> 8, arg0[0] & 0xFF) != 0) {
            other = (func_0024DE70(arg0[0] >> 8, arg0[0] & 0xFF) == 0 ? 1 : 0) << 8;
            func_001E1090(arg0[0] >> 8, arg0[0] & 0xFF);
            func_001E1090(other >> 8, other & 0xFF);
            func_001DF540(arg0[0] >> 8, arg0[0] & 0xFF);
            if (func_001E0290(arg0[0] >> 8, arg0[0] & 0xFF, 0) >= 2500) {
                func_0016DDA0(arg0);
            } else if (func_0016E000(arg0[0] >> 8, arg0[0] & 0xFF, 1) == 1) {
                func_0016E0E0(arg0, 1);
            } else {
                func_0016DDA0(arg0);
            }
        }
    }
}

void func_0016F240(u16 *arg0) {
    extern s32 func_001E1030();
    extern s32 func_001F9FE0();
    s32 id;
    s32 value;
    s32 *effect;
    s32 position;
    s32 result;
    u32 action;

    func_001E0700(arg0[0] >> 8, arg0[0] & 0xFF);
    id = func_001E1030(arg0[0] >> 8, arg0[0] & 0xFF);
    value = func_00250360(arg0[0] >> 8, arg0[0] & 0xFF);
    effect = func_00250740(arg0[0] >> 8, arg0[0] & 0xFF, 0);
    position = func_001E1090(arg0[0] >> 8, arg0[0] & 0xFF);
    action = *(u32 *)effect;
    switch (action >> 8) {
    case 0x14:
        arg0[2] = 0xCFF;
        return;
    case 4:
        result = func_0016CBB0(value, effect);
        if (result >= 0) {
            arg0[2] = 0x6FF;
            if (!(effect[0] & 0x3F)) {
                *(u32 *)&arg0[4] = arg0[4] | ((((position >> 8) << 8) | (result & 0xFF)) << 16);
            } else {
                *(u32 *)&arg0[4] = (result << 16) | arg0[4];
            }
            return;
        }
        break;
    case 2:
        result = func_0027C770(func_001DF540(arg0[0] >> 8, arg0[0] & 0xFF),
            position & 0xFF, position >> 8, *((u8 *)effect + 4), 8, 2);
        if (result >= 0) {
            arg0[2] = 0x6FF;
            *(u32 *)&arg0[4] = (result << 16) | arg0[4];
            return;
        }
        break;
    case 0x25:
        if ((action & 0x3F) == 0x21) {
            if (func_001DF540(arg0[0] >> 8, arg0[0] & 0xFF) != 0) {
                id = ((func_0024DE70(arg0[0] >> 8, arg0[0] & 0xFF) == 0) ? 1 : 0) << 8;
                func_001E1090(arg0[0] >> 8, arg0[0] & 0xFF);
                func_001E1090(id >> 8, id & 0xFF);
                func_001DF540(arg0[0] >> 8, arg0[0] & 0xFF);
                if (func_001E0290(arg0[0] >> 8, arg0[0] & 0xFF, 0) >= 0x9C4) {
                    func_0016DDA0(arg0);
                } else {
                    if (func_0016E000(arg0[0] >> 8, arg0[0] & 0xFF, 1) == 1) {
                        func_0016E0E0(arg0, 1);
                    } else {
                        func_0016DDA0(arg0);
                    }
                }
            }
            return;
        }
        break;
    case 0x1F:
        if (id == 0x2DC) {
            arg0[2] = 0xDFF;
            return;
        }
        break;
    default:
        break;
    }
    arg0[2] = 0x5FF;
}

typedef struct {
    s16 id;
    u8 unk2;
    u8 pad3;
    s16 unk4;
    u8 pad6[6];
    s32 unkC;
} Ctx_0016F4D0;

typedef struct {
    u8 pad0[0x3C];
    u16 unk3C;
    u8 pad3E[0x22];
} Work_0016F4D0;

s32 func_00276F10(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8,
                  s32 arg9);

s32 func_0016F4D0(s32 arg0, s32 arg1, s32 arg2) {
    s32 ret;
    s32 kind;
    Ctx_0016F4D0 *ctx = (Ctx_0016F4D0 *)arg2;
    Work_0016F4D0 work;
    s32 res;
    extern s32 func_00278890();

    ctx->id = arg0;
    if (func_001DE6D0(arg1) == 0) {
        return -1;
    }
    if (func_00278890(arg1, 0) == 5 && func_00278890(arg1, 1) == 5) {
        return -1;
    }
    kind = func_0016F760(arg1, &work);
    if (kind < 0) {
        return -1;
    }
    ctx->unk2 = 10;
    ctx->unkC = 2;
    arg0 = func_001E1090(arg0 >> 8, arg0 & 0xFF);
    if (kind == 0) {
        if (func_0016FEF0(arg1, (u8 *)ctx, &work) >= 0) {
            ret = func_00276F10(&work, arg0 & 0xFF, arg0 >> 8, arg1 == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, func_00172310(arg1));
            if (ret < 0) {
                if (func_001E0150(arg1) < 5) {
                    res = func_00170620(arg1, (u8)kind, &work, ret);
                    if (res < 0) {
                        return -1;
                    }
                    ctx->unk4 = res;
                    return 1;
                }
            } else {
                res = func_00170620(arg1, (u8)kind, &work, ret);
                if (res < 0) {
                    return -1;
                }
                ctx->unk4 = res;
                return 1;
            }
        }
    } else {
        ret = func_00276F10(&work, arg0 & 0xFF, arg0 >> 8, arg1 == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, func_00172310(arg1));
    }
    if (kind == 2) {
        func_001703E0(arg1, ctx, &work);
        res = func_00170620(arg1, (u8)kind, &work, ret);
        if (res < 0) {
            return -1;
        }
        ctx->unk4 = res;
        return 1;
    }
    if (func_0016FCF0(arg1, (u8 *)ctx, &work, work.unk3C) < 0) {
        return -1;
    }
    res = func_00170620(arg1, (u8)kind, &work, ret);
    if (res < 0) {
        return -1;
    }
    ctx->unk4 = res;
    return 1;
}

static inline s32 check_0016F760(s32 mask, u32 threshold) {
    s32 high;
    s32 low;
    s32 j;
    s32 packed;
    s32 target;

    for (j = 0; j < func_0024E910(mask); j++) {
            packed = func_0024EC50(mask, j);
            high = packed >> 8;
            low = packed & 0xFF;
            target = func_001E1090(high, low);
            if ((u32)func_002509E0(high, low, target & 0xFF, target >> 8) >= threshold) {
                return 0;
            }
    }
    return 1;
}

s32 func_0016F760(s32 arg0, void *arg1) {
    extern s32 func_00278890();
    extern u32 func_0026FBB0();
    extern s32 func_001E1580();
    s32 cards[8];
    u8 scratch[32];
    s32 criteria[4];
    u8 mode0;
    u8 mode1;
    s32 outer;
    s32 *p;
    s32 *q;
    s32 scan;
    s32 i;
    s32 *last;
    s32 last_index;
    s32 ret;

    mode0 = func_00278890(arg0, 0);
    mode1 = func_00278890(arg0, 1);
    if (arg1 == NULL) {
        return -1;
    }
    func_0026FD30(arg0, cards);
    if (mode0 == 5) {
        if (func_0016FCF0(arg0, scratch, arg1, 999) >= 0) {
            ret = 1;
        } else {
            ret = -1;
        }
        return ret;
    }
    if (mode1 == 5) {
        s32 index;
        s32 *card;

        index = 0;
        if (index < func_0026FE20(arg0)) {
            card = cards;
            do {
                if ((func_0026FCE0(*card) >> 5) == 0 &&
                    func_0026FB10(arg0, *card) == 1) {
                    func_001DCD70(arg1, cards[index]);
                    return 0;
                }
                card++;
                index++;
            } while (index < func_0026FE20(arg0));
        }
        return -1;
    }

    outer = 0;
    if (outer < func_0026FE20(arg0)) {
        p = cards;
        do {
            if ((func_0026FCE0(*p) >> 5) == 5) {
                s32 *record;
                u32 threshold;
                s32 mask;
                s32 ok;

                record = func_0026FC90(*p, 0);
                func_00254C90(criteria, record[1]);
                threshold = func_0026FBB0(record[1]) >> 16;
                if ((mask = func_00254890(criteria, arg0)) < 0) {
                    ok = 0;
                } else {
                    ok = check_0016F760(mask, threshold);
                }
                if (ok == 1 &&
                    func_0016FC00(arg0, scratch, arg1, (u16)*p) >= 0) {
                    return 2;
                }
            }
            p++;
            outer++;
        } while (outer < func_0026FE20(arg0));
    }

    scan = 0;
    if (scan < func_0026FE20(arg0)) {
        q = cards;
        do {
            if (*q == 700 || *q == 702) {
                if (func_0016CBB0(arg0, func_0026FC90(*q, 0)) >= 0 &&
                    func_0016FC00(arg0, scratch, arg1, (u16)*q) >= 0) {
                    return 2;
                }
            }
            q++;
            scan++;
        } while (scan < func_0026FE20(arg0));
    }

    i = 0;
    do {
        if (func_001E1580(arg0, i) != 0 &&
            func_0016FC00(arg0, scratch, arg1, 796) >= 0) {
            return 2;
        }
        i++;
    } while (i < 11);

    i = 0;
    do {
        if (func_001E1580(arg0, i) != 0 &&
            func_0016FC00(arg0, scratch, arg1, 795) >= 0) {
            return 2;
        }
        i++;
    } while (i < 11);

    last_index = 0;
    if (last_index < func_0026FE20(arg0)) {
        last = cards;
        do {
            if ((func_0026FCE0(*last) >> 5) == 0 &&
                func_0026FB10(arg0, *last) == 1) {
                func_001DCD70(arg1, cards[last_index]);
                return 0;
            }
            last++;
            last_index++;
        } while (last_index < func_0026FE20(arg0));
    }
    ret = func_0016FCF0(arg0, scratch, arg1, 999);
    if (ret >= 0) {
        return ret;
    }
    return -1;
}

s32 func_0016FC00(s32 arg0, void *arg1, void *arg2, s32 arg3) {
    s32 entries[8];
    s32 i;

    func_0026FD30(arg0, entries);
    for (i = 0; i < func_0026FE20(arg0); i++) {
        if (((arg3 & 0xFFFF) == entries[i]) && (func_0026FB10(arg0, entries[i]) == 1)) {
            *((s8 *)arg1 + 6) = i;
            func_001DCD70(arg2, entries[i]);
            return func_0026FCE0(entries[i]) >> 5;
        }
    }
    return -1;
}

s32 func_0016FCF0(s32 arg0, u8 *arg1, void *arg2, s32 arg3) {
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

typedef struct Info_0016FEF0 {
    u8 pad00[8];
    u16 x;
    s16 y;
} Info_0016FEF0;

typedef struct Sprite_0016FEF0 {
    Info_0016FEF0 *info;
    u8 pad04[0x34];
    s16 x;
    s16 y;
} Sprite_0016FEF0;

u16 *func_00278A90(s32, u16 *, s32, s32, s32, s16 *, s16 *);

s32 func_0016FEF0(s32 arg0, u8 *arg1, void *arg2) {
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
                            func_001700D0(arg0, *node, entries);
                            func_00278DD0((u8 *)*node + 2, arg1 + 6);
                            func_001DCD70(arg2, **node);
                            ((Sprite_0016FEF0 *)arg2)->x = (value >> 16) - (((Sprite_0016FEF0 *)arg2)->info->x & 0x1FFF);
                            ((Sprite_0016FEF0 *)arg2)->y = (value & 0xFFFF) - (((Sprite_0016FEF0 *)arg2)->info->y & 0x1FFF);
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
} Info_001700D0;

void func_001700D0(s32 arg0, void *arg1, s32 *arg2) {
    Info_001700D0 *info = arg1;
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
                if (card != 0x3E7 && func_001702B0(card) == 0 && level >= func_0026FA80(card, arg0)) {
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

static inline s32 isSpecial_001702B0(s32 card) {
    return ((u32)(card - 0x36) < 4) ? 1 : 0;
}

static inline s32 hasAll_001702B0(void) {
    extern s32 func_001E1030();
    s32 player = func_001DE540();

    if (func_001E1030(player, 0) == 0x3A &&
        func_002151D0(player, func_002158B0(player), 0x36) >= 0 &&
        func_002151D0(player, func_002158B0(player), 0x37) >= 0 &&
        func_002151D0(player, func_002158B0(player), 0x38) >= 0 &&
        func_002151D0(player, func_002158B0(player), 0x39) >= 0) {
        return 1;
    }
    return 0;
}

s32 func_001702B0(s32 arg0) {
    if (func_0026FCE0(arg0) >> 5 != 0) {
        return 1;
    }
    if (func_0026FC10(arg0) == 1) {
        return 1;
    }
    if (isSpecial_001702B0(arg0) == 1) {
        if (hasAll_001702B0() == 1) {
            return 1;
        }
    }
    return 0;
}


typedef struct {
    u8 pad0[6];
    u8 slot[5];
} Obj1_001703E0;

typedef struct {
    u8 pad0[0x38];
    s16 f38;
    s16 f3A;
    u16 id;
} Obj2_001703E0;

s32 func_001703E0(s32 arg0, void *arg1, void *arg2) {
    Obj1_001703E0 *o1 = arg1;
    Obj2_001703E0 *o2 = arg2;
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

void func_00170610(void) {
    func_0024E410();
}

typedef struct {
    u8 low : 4;
    u8 high : 4;
} Nibbles_00170620;

typedef struct {
    u8 pad[0x3E];
    u8 f3E;
} Card_00170620;


s32 func_00170620(s32 arg0, s32 arg1, void *arg2, s32 arg3) {
    extern s32 func_00278510();
    extern s32 func_0027A130(s32, void *, s32, s32, s32, s32, s32, s32, u8, u16);
    extern s32 func_002792C0(s32, void *, s32, s32, s32, s32, u16, u8);
    Card_00170620 *card = arg2;
    Nibbles_00170620 entries[12];
    s32 id;
    s32 hi;
    s32 lo;
    s32 i;
    Nibbles_00170620 *entry;
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
            if (func_00278510(card, arg3, func_00172310(arg0), pos & 0xFF, pos >> 8, 0) > 0) {
                cost = func_0027A130((s32)card, entries, lo, hi, pos & 0xFF, pos >> 8, arg3, 0, 3,
                                     func_00172310(arg0));
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

void func_001E1E70(s32, s32, s32, s32);
s32 func_00276CC0(s32, s32, s32, s32, s32, u8);
s32 func_0027BE10(s32, s32, s32, s32, s32);

typedef struct Nibbles_00170940 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_00170940;

typedef struct Result_00170940 {
    u16 source;
    u8 action;
    u8 pad3;
    u16 destination;
    u8 pad6[6];
    s32 value;
    u8 flags;
} Result_00170940;

static inline s32 moveFlags_00170940(u16 *unit, u16 *move, s32 exact) {
    return func_0027E360(*unit >> 8, *unit & 0xFF, move[2], exact, 0);
}

s32 func_00170940(u16 *unit, s32 arg1, void *out, u8 arg3) {
    extern s32 func_00279C40(s32, s32, s32, s32, s32, s32, void *, u8);
    s32 destination;
    s32 chosen;
    s32 bestScore;
    Nibbles_00170940 positions[12];
    s32 i;
    Nibbles_00170940 *p;

    destination = func_001E1090(*unit >> 8, *unit & 0xFF);
    p = positions;
    i = 0;
    do {
        p->low = p->high = 15;
        p++;
        i++;
    } while (i < 12);
    {
        s32 rawRange;
        s32 currentY;
        s32 score;
        s32 shiftedY;
        s32 targetY;
        s32 targetX;
        s32 currentX;
        u8 lowerX;
        u8 upperX;
        u8 lowerY;
        u8 upperY;
        u8 ability;
        u8 range;
        u16 unitFlags;

        unitFlags = func_00172310(arg1);
        targetX = destination & 0xFF;
        targetY = destination >> 8;
        if (func_00276CC0(targetX, targetY, *unit, 3, unitFlags, 0) == 0) {
            ((Result_00170940 *)out)->source = *unit;
            ((Result_00170940 *)out)->action = 6;
            ((Result_00170940 *)out)->destination = destination;
            ((Result_00170940 *)out)->flags = moveFlags_00170940(unit, out, 1);
            ((Result_00170940 *)out)->value = func_0016B610(*unit >> 8, *unit & 0xFF, unit);
            func_0027B1B0(unit, arg3);
            return 0;
        }
        if ((rawRange = func_002464F0(func_001DF540(*unit >> 8, *unit & 0xFF), targetX, targetY)) == 0) {
            ((Result_00170940 *)out)->source = *unit;
            ((Result_00170940 *)out)->action = 6;
            ((Result_00170940 *)out)->destination = destination;
            ((Result_00170940 *)out)->flags = moveFlags_00170940(unit, out, 1);
            ((Result_00170940 *)out)->value = func_0016B610(*unit >> 8, *unit & 0xFF, unit);
            func_0027B1B0(unit, arg3);
            return 0;
        }
        if (func_001E2100(*unit >> 8, *unit & 0xFF, 4) != 0) {
            if ((func_001E0700(*unit >> 8, *unit & 0xFF) >> 5) == 1 ||
                (func_001E0700(*unit >> 8, *unit & 0xFF) >> 5) == 5) {
                func_001E1E70(*unit >> 8, *unit & 0xFF, 0, 1);
                ((Result_00170940 *)out)->source = *unit;
                ((Result_00170940 *)out)->action = 14;
                return 0;
            }
        }
        range = rawRange & 15;
        chosen = 0xFF;
        bestScore = 0xFFFF;
        lowerX = func_00250860(0, targetX - range);
        upperX = (targetX + range >= 7) ? 6 : targetX + range;
        lowerY = func_00250860(0, targetY - range);
        upperY = (targetY + range >= 7) ? 6 : targetY + range;
        if ((*unit & 0xFF) == 0) {
            ability = func_0027BBC0(*unit >> 8, *unit & 0xFF, 0);
        } else {
            ability = 0;
        }
        for (currentX = lowerX; currentX <= (s32)upperX; currentX++) {
            for (currentY = lowerY, shiftedY = currentY << 8; currentY <= (s32)upperY; shiftedY += 0x100, currentY++) {
                if ((((currentX < targetX ? targetX : currentX) -
                      (targetX < currentX ? targetX : currentX)) +
                     ((currentY < targetY ? targetY : currentY) -
                      (targetY < currentY ? targetY : currentY))) <= range) {
                    if (func_00279C40(*unit >> 8, *unit & 0xFF, targetX, targetY, currentX, currentY, unit, ability) == 1) {
                        if (func_0027BE10(*unit >> 8, *unit & 0xFF, currentX, currentY, 0) == 0 || *(u8 *)unit == 0) {
                            score = func_00276CC0(currentX, currentY, *unit, 3, (u16)func_00172310(arg1), 0);
                            if (score < bestScore) {
                                bestScore = score;
                                chosen = shiftedY | currentX;
                            } else if (score == bestScore && func_001E36E0(currentX, currentY) == 0 &&
                                       func_001E36E0(chosen & 0xFF, chosen >> 8) != 0) {
                                bestScore = score;
                                chosen = shiftedY | currentX;
                            }
                        }
                    }
                }
            }
        }
        if (chosen != 0xFF) {
            ((Result_00170940 *)out)->source = *unit;
            ((Result_00170940 *)out)->action = 6;
            ((Result_00170940 *)out)->destination = chosen;
            if (chosen == destination) {
                ((Result_00170940 *)out)->flags = moveFlags_00170940(unit, out, 1);
            } else {
                ((Result_00170940 *)out)->flags = moveFlags_00170940(unit, out, 0);
            }
            ((Result_00170940 *)out)->value = func_0016B610(*unit >> 8, *unit & 0xFF, unit);
        } else {
            ((Result_00170940 *)out)->source = *unit;
            ((Result_00170940 *)out)->action = 6;
            ((Result_00170940 *)out)->destination = destination;
            ((Result_00170940 *)out)->flags = moveFlags_00170940(unit, out, 1);
            ((Result_00170940 *)out)->value = func_0016B610(*unit >> 8, *unit & 0xFF, unit);
        }
        func_0027B1B0(unit, arg3);
    }
    return 0;
}

typedef struct Source_00170F10 {
    u16 position;
    u8 pad2[6];
    u32 targets;
} Source_00170F10;

typedef struct Output_00170F10 {
    u16 position;
    u8 mode;
    u8 pad3;
    u16 target;
    u8 pad6[6];
    s32 flag;
    u8 value;
} Output_00170F10;

typedef struct Position_00170F10 {
    u8 x : 4;
    u8 y : 4;
} Position_00170F10;

s32 func_00276CC0(s32, s32, s32, s32, s32, u8);

static inline u32 target_00170F10(void *arg0, u8 which) {
    Source_00170F10 *source = arg0;
    if (which == 1) {
        return (u16)(source->targets >> 16);
    }
    return *(u16 *)&source->targets;
}

s32 func_00170F10(void *arg0, s32 arg1, void *arg2, u8 arg3) {
    extern void func_0027A090();
    s32 sourceTarget;
    s32 count;
    s32 sourceY;
    s32 sourceX;
    s32 selectedFlag;
    Position_00170F10 positions[12];
    s32 flag;
    s32 otherTarget;
    s32 j;
    Position_00170F10 *walk;
    s32 object;
    u32 targetXWord;
    u32 targetYWord;
    Source_00170F10 *source = arg0;
    Output_00170F10 *output = arg2;

    targetXWord = target_00170F10(arg0, arg3);
    targetYWord = target_00170F10(arg0, arg3);
    if (func_001DF540(targetYWord >> 8, targetXWord & 0xFF) == 0) {
        func_0027B1B0(arg0, 1);
        return -1;
    }

    flag = func_0016B610(source->position >> 8, source->position & 0xFF, arg0);
    sourceTarget = func_001E1090(source->position >> 8, source->position & 0xFF);
    targetXWord = target_00170F10(arg0, arg3);
    targetYWord = target_00170F10(arg0, arg3);
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
                            (u8)func_00172310(arg1));
        if (cost >= func_001E0290(source->position >> 8, source->position & 0xFF, 0)) {
            output->value = func_0027E360(source->position >> 8, source->position & 0xFF,
                                        output->target, 1, 0);
        } else {
            output->value = func_0027E360(source->position >> 8, source->position & 0xFF,
                                        output->target, 0, 0);
        }
        func_0027B1B0(arg0, arg3);
    } else {
        s32 targetY;
        s32 targetX;
        Position_00170F10 *current;
        s32 i;
        s32 bestCost;
        s32 selected;
        u16 position = source->position;

        func_0027A090(position >> 8, position & 0xFF, positions,
                      sourceX, sourceY, targetX = otherTarget & 0xFF,
                      targetY = otherTarget >> 8,
                      target_00170F10(arg0, arg3), 0, 30, (u16)func_00172310(arg1));
        count = func_0027AFC0((u8 *)positions);
        selected = 0xFF;
        if (count > 0) {
            selectedFlag = 0;
            bestCost = 0xFFFF;
            for (i = 0; i < count; i++) {
                s32 state = func_00172210(source->position >> 8, source->position & 0xFF,
                                          sourceX, sourceY, targetX, targetY);
                if (state == 1) {
                    Position_00170F10 *forcedPosition = &positions[i];
                    selected = i;
                    selectedFlag = 1;
                    i = count;
                    forcedPosition->x = targetX;
                    forcedPosition->y = targetY;
                } else {
                    s32 cost;
                    current = &positions[i];
                    cost = func_00276CC0(current->x, current->y, arg1, 2, 1,
                                        (u8)func_00172310(arg1));
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
        } else {
            output->position = source->position;
            output->mode = 6;
            output->target = sourceTarget;
            output->flag = selectedFlag;
            output->value = func_0027E360(source->position >> 8, source->position & 0xFF,
                                        output->target, 0, 0);
            func_0027B1B0(arg0, arg3);
            return 0;
        }
    }
    return 0;
}

typedef struct Coord_001714F0 {
    u8 x : 4;
    u8 y : 4;
} Coord_001714F0;

typedef struct Unit_001714F0 {
    u16 position;
    u8 pad2[6];
    union {
        u32 packed;
        u16 low;
    } target;
} Unit_001714F0;

typedef struct Output_001714F0 {
    u16 position;
    u8 kind;
    u8 pad3;
    u16 target;
    u8 pad6[6];
    s32 value;
    u8 flag;
} Output_001714F0;

void func_001E1E70(s32, s32, s32, s32);

static inline u32 target_001714F0(void *unit, s32 side) {
    return side == 1 ? (u32)(u16)(((Unit_001714F0 *)unit)->target.packed >> 16) : (u32)((Unit_001714F0 *)unit)->target.low;
}

static inline u32 minY_001714F0(void *unit, s32 side, u8 coord) {
    return coord < (target_001714F0(unit, side) >> 8) ? coord : (target_001714F0(unit, side) >> 8);
}

static inline u32 maxY_001714F0(void *unit, s32 side, u8 coord) {
    return (target_001714F0(unit, side) >> 8) < coord ? coord : (target_001714F0(unit, side) >> 8);
}

static inline u32 minX_001714F0(void *unit, s32 side, u8 coord) {
    return coord < (target_001714F0(unit, side) & 0xFF) ? coord : (target_001714F0(unit, side) & 0xFF);
}

static inline u32 maxX_001714F0(void *unit, s32 side, u8 coord) {
    return (target_001714F0(unit, side) & 0xFF) < coord ? coord : (target_001714F0(unit, side) & 0xFF);
}

s32 func_001714F0(void *arg0, s32 arg1, void *arg2, u8 arg3, u8 arg4) {
    extern s32 func_0016B610();
    extern s32 func_00276CC0();
    extern void func_00279230();
    extern s32 func_0027E360(s32, s32, s32, u8, s32);
    Coord_001714F0 coords[12];
    s32 initial;
    s32 cell;
    s32 count;

    initial = func_001E1090(((Unit_001714F0 *)arg0)->position >> 8, ((Unit_001714F0 *)arg0)->position & 0xFF);
    {
    s32 bestScore;
    s32 best;
    s32 side = arg3;
    Coord_001714F0 *candidate;
    s32 index;
    if (target_001714F0(arg0, side) == 0xFFFF) {
        if (initial == target_001714F0(arg0, side)) {
            ((Output_001714F0 *)arg2)->position = ((Unit_001714F0 *)arg0)->position;
            ((Output_001714F0 *)arg2)->kind = 6;
            ((Output_001714F0 *)arg2)->target = initial;
            ((Output_001714F0 *)arg2)->flag = func_0027E360(((Unit_001714F0 *)arg0)->position >> 8, ((Unit_001714F0 *)arg0)->position & 0xFF, ((Output_001714F0 *)arg2)->target, arg4, 0);
            ((Output_001714F0 *)arg2)->value = func_0016B610(((Unit_001714F0 *)arg0)->position >> 8, ((Unit_001714F0 *)arg0)->position & 0xFF, arg0);
            func_0027B1B0(arg0, arg3);
            return 0;
        }
    }

    if (func_001E2100(((Unit_001714F0 *)arg0)->position >> 8,
                      ((Unit_001714F0 *)arg0)->position & 0xFF, 4) != 0) {
        if ((func_001E0700(((Unit_001714F0 *)arg0)->position >> 8,
                          ((Unit_001714F0 *)arg0)->position & 0xFF) >> 5) == 1 ||
            (func_001E0700(((Unit_001714F0 *)arg0)->position >> 8,
                          ((Unit_001714F0 *)arg0)->position & 0xFF) >> 5) == 5) {
            func_001E1E70(((Unit_001714F0 *)arg0)->position >> 8,
                          ((Unit_001714F0 *)arg0)->position & 0xFF, 0, 1);
            ((Output_001714F0 *)arg2)->position = ((Unit_001714F0 *)arg0)->position;
            ((Output_001714F0 *)arg2)->kind = 0xE;
            return 0;
        }
    }

    candidate = coords;
    {
        s32 i = 0;
        Coord_001714F0 *entry = candidate;
        do {
            entry->x = entry->y = 0xF;
            i++;
            entry++;
        } while (i < 12);
    }

    cell = func_001E3790(target_001714F0(arg0, side) & 0xFF, ((u32)target_001714F0(arg0, side)) >> 8);
    if (cell < 0) {
        cell = 0xFFFF;
    }
    func_00279230(((Unit_001714F0 *)arg0)->position >> 8, ((Unit_001714F0 *)arg0)->position & 0xFF,
                 coords, initial & 0xFF, initial >> 8, target_001714F0(arg0, side) & 0xFF,
                 ((u32)target_001714F0(arg0, side)) >> 8, (u16)cell, 7);
    count = func_0027AFC0((u8 *)coords);
    {
        if (count > 0) {
        best = 0xFF;
        bestScore = 0xFFFF;
        for (index = 0; index < count; index++) {
                if (func_001E36E0(candidate->x, candidate->y) == 0) {
                    s32 score = func_00276CC0(candidate->x, candidate->y, arg1, 2, 1, (u8)func_00172310(arg1));
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
                        bestMinY = minY_001714F0(arg0, side, bestY);
                        bestMaxY = maxY_001714F0(arg0, side, bestY);
                        bestX = (&coords[best])->x;
                        bestMinX = minX_001714F0(arg0, side, bestX);
                        bestMaxX = maxX_001714F0(arg0, side, bestX);
                        currentY = (u8)candidate->y;
                        currentMinY = minY_001714F0(arg0, side, currentY);
                        currentMaxY = maxY_001714F0(arg0, side, currentY);
                        currentX = candidate->x;
                        currentMinX = minX_001714F0(arg0, side, currentX);
                        currentMaxX = maxX_001714F0(arg0, side, currentX);
                        if ((currentMaxX - currentMinX) + (currentMaxY - currentMinY) < (bestMaxX - bestMinX) + (bestMaxY - bestMinY)) {
                            bestScore = score;
                            best = index;
                        }
                    }
                }
            candidate++;
        }
    } else {
        ((Output_001714F0 *)arg2)->position = ((Unit_001714F0 *)arg0)->position;
            ((Output_001714F0 *)arg2)->kind = 6;
            ((Output_001714F0 *)arg2)->target = initial;
            ((Output_001714F0 *)arg2)->flag = func_0027E360(((Unit_001714F0 *)arg0)->position >> 8, ((Unit_001714F0 *)arg0)->position & 0xFF, ((Output_001714F0 *)arg2)->target, arg4, 0);
            ((Output_001714F0 *)arg2)->value = func_0016B610(((Unit_001714F0 *)arg0)->position >> 8, ((Unit_001714F0 *)arg0)->position & 0xFF, arg0);
        func_0027B1B0(arg0, arg3);
        return 0;
    }

        if (best != 0xFF) {
            ((Output_001714F0 *)arg2)->position = ((Unit_001714F0 *)arg0)->position;
            ((Output_001714F0 *)arg2)->kind = 6;
            ((Output_001714F0 *)arg2)->target = (coords[best].y << 8) | coords[best].x;
            ((Output_001714F0 *)arg2)->flag = func_0027E360(((Unit_001714F0 *)arg0)->position >> 8, ((Unit_001714F0 *)arg0)->position & 0xFF, ((Output_001714F0 *)arg2)->target, arg4, 0);
            ((Output_001714F0 *)arg2)->value = func_0016B610(((Unit_001714F0 *)arg0)->position >> 8, ((Unit_001714F0 *)arg0)->position & 0xFF, arg0);
        } else {
            ((Output_001714F0 *)arg2)->position = ((Unit_001714F0 *)arg0)->position;
            ((Output_001714F0 *)arg2)->kind = 6;
            ((Output_001714F0 *)arg2)->target = initial;
            ((Output_001714F0 *)arg2)->flag = func_0027E360(((Unit_001714F0 *)arg0)->position >> 8, ((Unit_001714F0 *)arg0)->position & 0xFF, ((Output_001714F0 *)arg2)->target, arg4, 0);
            ((Output_001714F0 *)arg2)->value = func_0016B610(((Unit_001714F0 *)arg0)->position >> 8, ((Unit_001714F0 *)arg0)->position & 0xFF, arg0);
        }
        func_0027B1B0(arg0, arg3);
    }
    }
    return 0;
}

typedef struct {
    u8 low : 4;
    u8 high : 4;
} Nibbles_00171D60;

typedef struct {
    u16 source;
    s8 command;
    u8 pad3;
    u16 target;
    u8 pad6[6];
    s32 count;
    s8 value;
} Output_00171D60;

s32 func_0016C8F0(s32, s32, s32);
void func_001E1E70(s32, s32, s32, s32);

s32 func_00171D60(u16 *arg0, s32 arg1, void *arg2, s32 arg3) {
    extern void func_0027B1B0();
    extern s32 func_00170940();
    s32 address;
    s32 result;
    s32 index;
    Nibbles_00171D60 buffer[12];
    Nibbles_00171D60 *p;
    Output_00171D60 *out = arg2;

    {
    u32 *item;
    s32 state;

    state = (func_001E0700(*arg0 >> 8, *arg0 & 0xFF) >> 5) & 0xFF;
    if (state == 0) {
        item = func_001E0B70(*arg0 >> 8, *arg0 & 0xFF, 3);
    } else {
        item = func_001E0B70(*arg0 >> 8, *arg0 & 0xFF, 0);
    }
    address = func_001E1090(*arg0 >> 8, *arg0 & 0xFF);
    p = buffer;
    index = 0;
    do {
        p->low = p->high = 15;
        p++;
        index++;
    } while (index < 12);

    if (item != NULL) {
        result = func_0016C8F0(arg1, (*item >> 6) & 3, *item & 0x3F);
        if (state != 0) {
            if (func_001E22B0(address & 0xFF, address >> 8) == 9) {
                result = -1;
            }
            if (func_0027D830(*arg0 >> 8, *arg0 & 0xFF, 0, 0, 6, 0) == 5) {
                result = -1;
            }
        }
        if (result >= 0) {
            address = (result >> 16) & 0xFFFF;
            state = func_0027DBC0(address, result & 0xFF, *item & 0x3F);
            out->source = *arg0;
            out->command = 12;
            out->value = func_0027E360(*arg0 >> 8, *arg0 & 0xFF,
                out->target, 1, 0);
            out->count = 1;
            if (((*item >> 6) & 3) != 3) {
                out->target = (arg1 << 8) | state;
            } else {
                out->target = (address << 8) | state;
            }
            func_0027B1B0(arg0, arg3);
            return 0;
        }
    }
    if (state != 0) {
        if (func_001E2100(*arg0 >> 8, *arg0 & 0xFF, 4) != 0) {
            func_001E1E70(*arg0 >> 8, *arg0 & 0xFF, 0, 1);
            out->source = *arg0;
            out->command = 14;
            return 0;
        }
    }
    return func_00170940(arg0, arg1, arg2, arg3);
    }
}

typedef struct Nibbles_00172000 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_00172000;

typedef struct Out_00172000 {
    u16 pos;
    u8 kind;
    u8 unk03;
    u16 target;
    u8 pad06[6];
    s32 flag;
    u8 result;
} Out_00172000;

static inline s32 slot_00172000(u16 *unit, s32 arg1) {
    s32 card = func_0016B3C0(arg1);
    if (func_0027D830(*unit >> 8, *unit & 0xFF, 0, 0, 6, 0) == 5) {
        card = -1;
    }
    return card;
}

s32 func_00172000(u16 *arg0, s32 arg1, void *arg2, u8 arg3) {
    extern void func_001E1E70(s32, s32, s32, s32);
    u16 *unit = arg0;
    s32 count;
    s32 card;
    s32 k;
    Out_00172000 *out = arg2;
    Nibbles_00172000 entries[12];
    s32 i;
    Nibbles_00172000 *entry;

    func_001E1090(*unit >> 8, *unit & 0xFF);
    entry = entries;
    i = 0;
    do {
        entry->low = entry->high = 15;
        entry++;
        i++;
    } while (i < 12);
    count = 0;
    card = slot_00172000(unit, arg1);
    if (card >= 0) {
        card = (card >> 16) & 0xFFFF;
        if (card != 0xFFFF) {
            k = 1;
            do {
                if (func_001DF540(arg1 == 0 ? 1 : 0, k) != 0) {
                    count++;
                }
                if (k == card) {
                    k = 11;
                }
                k++;
            } while (k < 11);
            out->pos = *unit;
            out->kind = 13;
            out->result = func_0027E360(*unit >> 8, *unit & 0xFF, out->target, 1, 0);
            out->flag = 1;
            out->target = count - 1;
            func_0027B1B0(unit, arg3);
            return 0;
        }
    }
    if (func_001E2100(*unit >> 8, *unit & 0xFF, 4) != 0) {
        func_001E1E70(*unit >> 8, *unit & 0xFF, 0, 1);
        out->pos = *unit;
        out->kind = 14;
        return 0;
    }
    return func_00170940(unit, arg1, out, arg3);
}

static inline s32 max_00172210(s32 a, s32 b) {
    if (a < b) {
        return b;
    }
    return a;
}

s32 func_00172210(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 min_y;
    s32 min_x;

    min_y = arg3 < arg5 ? arg3 : arg5;
    arg5 = max_00172210(arg5, arg3);
    min_x = arg2 < arg4 ? arg2 : arg4;
    arg4 = max_00172210(arg4, arg2);
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

s32 func_00172310(s32 arg0) {
    if (func_001DF470(arg0) > 0x4B0) {
        if (func_001E0150(arg0) >= 4) {
            return 0x3E8;
        } else {
            return 0x7D0;
        }
    } else {
        return 0x960;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_016", func_00172370);

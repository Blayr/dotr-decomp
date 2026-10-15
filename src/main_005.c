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

u16 *TaLogic_GetFusionTree(s32, u16 *, s32, s32, s32, s16 *, s16 *);

s32 TaLogic001_SetComboQue(s32 arg0, u8 *arg1, void *arg2) {
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

        TaHand_GetNextHand(arg0, entries);
        best = -1;
        top = -1;
        i = 0;
        if (i < TaHand_GetNextHandNum(arg0)) {
            entry = entries;
            node = nodes;
            do {
                b = 0;
                a = 0;
                card = *entry;
                *node = NULL;
                if ((TaHand_GetCardKind(card) >> 5) == 0) {
                    *node = TaLogic_GetFusionTree(arg0, *node, i & 0xFF, card & 0xFFFF, 0, &a, &b);
                    *node = TaLogic_GetFusionRes(*node);
                    value = TaLogic_GetEnchantQue(arg0, *node, 0, 0);
                    if (TaHand_IsCardSummon2(arg0, card) == 1) {
                        if (best < value) {
                            TaLogic_ConvEmptyCombo_00114F20(arg0, *node, entries);
                            TaLogic_CopyArray((u8 *)*node + 2, arg1 + 6);
                            SzDuel_InitCardInfo(arg2, **node);
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
            } while (i < TaHand_GetNextHandNum(arg0));
        }
        return top;
    }
}

typedef struct {
    u16 id;
    u8 values[5];
} Info_00114F20;

void TaLogic_ConvEmptyCombo_00114F20(s32 arg0, void *arg1, s32 *arg2) {
    Info_00114F20 *info = arg1;
    u8 buf[5];
    s32 count;
    s32 i;
    s32 card;
    u8 level;
    u32 cost;
    extern u32 TaHand_GetCardAPDP();

    if (info != NULL) {
        level = TaHand_GetCardSummonCost2(info->id, arg0);
        for (i = 0; i < 5; i++) {
            buf[i] = 0xFF;
        }
        for (i = 0, count = 0; i < TaHand_GetNextHandNum(arg0); i++) {
            if ((u8)TaLogic_IsUseHandInCombo(i, info->values) == 0) {
                buf[count++] = i;
            }
        }
        if (count != 0) {
            for (i = 0; i < (u8)TaLogic_GetArrayLength(buf); i++) {
                card = arg2[buf[i]];
                if (card != 0x3E7 && TaLogic001_IsRefuseEmptyCombo(card) == 0 && level >= TaHand_GetCardSummonCost2(card, arg0)) {
                    cost = TaHand_GetCardAPDP(card);
                    if ((cost & 0xFFFF) + (cost >> 16) * 2 < 0x1389 && TaHand_IsCardEffect(card) == 2 &&
                        (u16)TaLogic_GetHandFusion(info->id, (u16)card) == 0x3E7) {
                        TaLogic_AddEmptyCombo(info->values, buf[i]);
                    }
                }
            }
        }
    }
}

s32 TaLogic001_IsRefuseEmptyCombo(s32 arg0) {
    if ((TaHand_GetCardKind(arg0) >> 5) != 0) {
        return 1;
    }
    if (TaHand_IsCardEffect(arg0) == 1) {
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

s32 TaLogic001_SetSpecialComboQue(s32 arg0, void *arg1, void *arg2) {
    Obj1_00115160 *o1 = arg1;
    Obj2_00115160 *o2 = arg2;
    s32 list[8];
    s32 i;
    u8 k;

    for (i = 0; i < 5; i++) {
        o1->slot[i] = 0xFF;
    }
    TaHand_GetNextHand(arg0, list);
    if (o2 == NULL) {
        return -1;
    }
    for (i = 0; i < TaHand_GetNextHandNum(arg0); i++) {
        if (i != o1->slot[0] && i != o1->slot[1]) {
            if (o2->id == list[i]) {
                o1->slot[0] = i;
            }
        }
    }
    k = 1;
    if ((TaHand_GetCardKind(list[o1->slot[0]]) >> 5) == 0) {
        for (i = 0; i < TaHand_GetNextHandNum(arg0); i++) {
            if (i != o1->slot[0] && i != o1->slot[1]) {
                if (Ta_GetHandEnchant(list[o1->slot[0]], list[i]) >= 0 && (TaHand_GetCardKind(list[i]) >> 5) == 2) {
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

typedef struct {
    u8 low : 4;
    u8 high : 4;
} Cell_00115340;


s32 TaLogic001_GetSummonPiece(s32 arg0, u8 arg1, void *arg2, s32 arg3) {
    extern s32 TaLogic_IsUnitWin4();
    extern s32 TaLogic_GetInvadeRoot2();
    extern s32 TaLogic_GetRoot2(void *, void *, s32, s32, s32, s32, u16, s32);
    s32 best_position;
    s32 best_cost;
    s32 fallback_position;
    Cell_00115340 cells[12];
    s32 y;
    s32 x;
    s32 i;
    s32 best;
    s32 position;
    s32 target_y;
    s32 target_x;
    s32 target;
    s32 result;
    s32 j;
    Cell_00115340 *p;

    if (arg2 == NULL) {
        return -1;
    }
    p = cells;
    j = 0;
    do {
        p->low = p->high = 15;
        j++;
        p++;
    } while (j < 12);

    if ((u8)(*((u8 *)arg2 + 0x3E) >> 5) == 0 &&
        *(u16 *)((u8 *)arg2 + 0x3C) != 0x53) {
        best = 14;
        if (arg3 >= 0) {
            s32 candidate;
            s32 candidate_y;
            s32 candidate_x;
            s32 n;
            s32 cost;

            best_cost = 255;
            best_position = 65535;
            target = SzDuel_GetUnitLoc(arg3 >> 8, arg3 & 255);
            n = 0;
            target_y = target >> 8;
            target_x = target & 255;
            do {
                candidate = Ta_GetSommonPiecePreference(arg0, n);
                if (candidate >= 0) {
                    candidate_x = candidate & 255;
                    candidate_y = candidate >> 8;
                    if (SzDuel_GetField(candidate_x, candidate_y) != 8 &&
                        (SzDuel_GetField(candidate_x, candidate_y) != 9 ||
                         Ta_IsVirus_Chk3(arg2, candidate_x, candidate_y) != 1) &&
                        SzDuel_GetMapUnit(candidate_x, candidate_y) == 0) {
                        if (TaLogic_IsUnitWin4(arg2, arg3, TaLogic_GetWarnHideLvl_00117C30(arg0),
                                         target_x, target_y, 0) > 0) {
                            cost = TaLogic_GetInvadeRoot2(arg2, cells, candidate_x, candidate_y,
                                                target_x, target_y, arg3, 0, 5,
                                                (u16)TaLogic_GetWarnHideLvl_00117C30(arg0));
                        } else {
                            cost = TaLogic_GetRoot2(arg2, cells, candidate_x, candidate_y,
                                                target_x, target_y, arg3, 5);
                        }
                        if (TaLogic_GetMinGoalCount((u8 *)cells) > 0 && cost < best_cost) {
                            best_cost = cost;
                            best_position = candidate;
                        }
                    }
                }
                n++;
            } while (n < 8);
            if (best_position != 65535) {
                return best_position;
            }
        }
        best = 14;

        fallback_position = 0;
        i = 0;
        do {
            position = Ta_GetSommonPiecePreference(arg0, i);
            if (position >= 0) {
                x = position & 255;
                y = position >> 8;
                if (SzDuel_GetField(x, y) != 8 &&
                    (SzDuel_GetField(x, y) != 9 || Ta_IsVirus_Chk3(arg2, x, y) != 1) &&
                    SzDuel_GetMapUnitID(x, y) < 0) {
                    if (CheckLandAgreement(3, arg2) == 1) {
                        if (y >= 5) {
                            target = 0x602;
                        } else if (x >= 5) {
                            target = 0x206;
                        } else if (x >= y) {
                            target = 0x105;
                        } else {
                            target = 0x501;
                        }
                        target_x = target & 255;
                        target_y = target >> 8;
                        result = SzDuel_GetMapUnitID(target_x, target_y);
                        if (result < 0) {
                            result = 65535;
                        }
                        result = TaLogic_GetRoot2(arg2, cells, x, y, target_x, target_y,
                                              (u16)result, 7);
                        if (result < best && result >= 0) {
                            fallback_position = position;
                            best = result;
                        }
                    } else {
                        result = SzDuel_GetMapUnitID(3, 3);
                        if (result < 0) {
                            result = 65535;
                        }
                        result = TaLogic_GetRoot2(arg2, cells, x, y, 3, 3, (u16)result, 7);
                        if (result < best && result >= 0) {
                            fallback_position = position;
                            best = result;
                        }
                    }
                }
            }
            i++;
        } while (i < 8);
        if (best < 14) {
            return fallback_position;
        } else {
            fallback_position = -1;
        }
        return fallback_position;
    } else {
        s32 y;
        s32 x;
        s32 i;
        s32 best;
        s32 position;

        best = -1;
        i = 0;
        do {
            position = Ta_GetSommonPiecePreference(arg0, i);
            if (position >= 0) {
                x = position & 255;
                y = position >> 8;
                if (SzDuel_GetField(x, y) != 8 && SzDuel_GetField(x, y) != 9 &&
                    SzDuel_GetMapUnitID(x, y) < 0 && y < 8) {
                    best = position;
                }
            }
            i++;
        } while (i < 8);
        if (best >= 0) {
            return best;
        } else {
            best = -1;
        }
        return best;
    }
}

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


s32 TaLogic_GetMinimumTask_RunMission_00115850(u16 *arg0, s32 arg1, void *arg2, u8 arg3) {
    Output_00115850 *output = arg2;
    s32 target;
    u8 endX;
    u8 extra;
    Nibbles_00115850 nibbles[12];
    s32 bestScore;
    s32 best;
    s32 i;
    Nibbles_00115850 *p;
    extern s32 TaLogic_IsOpenUnit_00117870();
    extern s32 TaLogic_IsRunPassRoot(s32, s32, s32, s32, s32, s32, void *, u8);

    target = SzDuel_GetUnitLoc(*arg0 >> 8, *arg0 & 0xFF);
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

        initialScore = TaLogic_GetWarnHideLvl_00117C30(arg1);
        centerX = target & 0xFF;
        centerY = target >> 8;
        if (TaLogic_GetUnitWarning(centerX, centerY, *arg0, 3, initialScore, 0) == 0) {
            output->position = *arg0;
            output->action = 6;
            output->destination = target;
            output->result = TaLogic_IsDefStyleUnit(*arg0 >> 8, *arg0 & 0xFF, output->destination, 1, 0);
            output->special = TaLogic_IsOpenUnit_00117870(*arg0 >> 8, *arg0 & 0xFF, arg0);
            TaLogic_InitRogicControl(arg0, arg3);
            return 0;
        }
        if ((range = GetMoveRev(SzDuel_GetUnit(*arg0 >> 8, *arg0 & 0xFF), centerX, centerY)) == 0) {
            output->position = *arg0;
            output->action = 6;
            output->destination = target;
            output->result = TaLogic_IsDefStyleUnit(*arg0 >> 8, *arg0 & 0xFF, output->destination, 1, 0);
            output->special = TaLogic_IsOpenUnit_00117870(*arg0 >> 8, *arg0 & 0xFF, arg0);
            TaLogic_InitRogicControl(arg0, arg3);
            return 0;
        }
        if (SzDuel_GetUnitStatus(*arg0 >> 8, *arg0 & 0xFF, 4) != 0) {
            if ((SzDuel_GetUnitKind(*arg0 >> 8, *arg0 & 0xFF) >> 5) == 1 ||
                (SzDuel_GetUnitKind(*arg0 >> 8, *arg0 & 0xFF) >> 5) == 5) {
                SzDuel_SetUnitStatus(*arg0 >> 8, *arg0 & 0xFF, 0, 1);
                output->position = *arg0;
                output->action = 0xE;
                return 0;
            }
        }
        best = 0xFF;
        bestScore = 0xFFFF;
        minX = (u8)GetCap(0, centerX - (range & 0xF));
        limit = centerX + (range & 0xF);
        endX = limit >= 7 ? 6 : limit;
        minY = (u8)GetCap(0, centerY - (range & 0xF));
        limit = centerY + (range & 0xF);
        if (limit >= 7) {
            limit = 6;
        }
        maxY = (u8)limit;
        if ((*arg0 & 0xFF) == 0) {
            extra = (u8)TaLogic_IsAttackedNow(*arg0 >> 8, *arg0 & 0xFF, 0);
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
                if (TaLogic_IsRunPassRoot(*arg0 >> 8, *arg0 & 0xFF, centerX, centerY, x, y, arg0, extra) == 1) {
                    if (TaLogic_IsAttackedNow2(*arg0 >> 8, *arg0 & 0xFF, x, y, 0) == 0 || (u8)*arg0 == 0) {
                        candidateScore = TaLogic_GetUnitWarning(x, y, *arg0, 3, (u16)TaLogic_GetWarnHideLvl_00117C30(arg1), 0);
                        if (candidateScore < bestScore) {
                            bestScore = candidateScore;
                            best = packedY | x;
                        } else if (candidateScore == bestScore && SzDuel_GetMapUnit(x, y) == 0 &&
                            SzDuel_GetMapUnit(best & 0xFF, best >> 8) != 0) {
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
                output->result = TaLogic_IsDefStyleUnit(*arg0 >> 8, *arg0 & 0xFF, output->destination, 1, 0);
            } else {
                output->result = TaLogic_IsDefStyleUnit(*arg0 >> 8, *arg0 & 0xFF, output->destination, 1, 0);
            }
            output->special = TaLogic_IsOpenUnit_00117870(*arg0 >> 8, *arg0 & 0xFF, arg0);
        } else {
            output->position = *arg0;
            output->action = 6;
            output->destination = target;
            output->result = TaLogic_IsDefStyleUnit(*arg0 >> 8, *arg0 & 0xFF, output->destination, 1, 0);
            output->special = TaLogic_IsOpenUnit_00117870(*arg0 >> 8, *arg0 & 0xFF, arg0);
        }
        TaLogic_InitRogicControl(arg0, arg3);
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


s32 TaLogic_GetMinimumTask_AtkMission_00115E20(void *arg0, s32 arg1, void *arg2, u8 arg3) {
    extern void TaLogic_GetInvadeRoot();
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
    if (SzDuel_GetUnit(target_00115E20(input, arg3) >> 8,
                     selected & 0xFF) == 0) {
        TaLogic_InitRogicControl(input, 1);
        return -1;
    }
    TaLogic_IsOpenUnit_00117870(input->position >> 8, input->position & 0xFF, (s32)input);
    origin = SzDuel_GetUnitLoc(input->position >> 8, input->position & 0xFF);
    selected = target_00115E20(input, arg3);
    destination = SzDuel_GetUnitLoc(target_00115E20(input, arg3) >> 8,
                               selected & 0xFF);
    point = candidates;
    for (i = 0; i < 12; i++) {
        candidates[i].x = candidates[i].y = 15;
    }
    if (GetMoveRev(SzDuel_GetUnit(input->position >> 8, input->position & 0xFF),
                      originX = origin & 0xFF, originY = origin >> 8) == 0) {
        s32 score;
        output->position = input->position;
        output->action = 6;
        output->target = origin;
        score = TaLogic_GetUnitWarning(originX, originY, arg1, 3, 1,
                             (u8)TaLogic_GetWarnHideLvl_00117C30(arg1));
        if (score >= SzDuel_GetUnitAP(input->position >> 8, input->position & 0xFF, 0)) {
            output->result = 1;
        } else {
            output->result = 0;
        }
        TaLogic_InitRogicControl(input, arg3);
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
        random = TaLogic_GetWarnHideLvl_00117C30(arg1);
        TaLogic_GetInvadeRoot(position >> 8, position & 0xFF, candidates,
                      originX, originY, destinationX = destination & 0xFF,
                      destinationY = destination >> 8,
                      target_00115E20(input, arg3), (s64)0, (s64)30,
                      (s64)random);
        count = TaLogic_GetMinGoalCount((u8 *)candidates);
        bestIndex = 255;
        if (count > 0) {
            bestScore = 65535;
            for (index = 0; index < count; index++, point++) {
                s32 score = TaLogic_GetUnitWarning(point->x, point->y, arg1, 2, 1,
                                         (u8)TaLogic_GetWarnHideLvl_00117C30(arg1));
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
            TaLogic_InitRogicControl(input, arg3);
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
            TaLogic_InitRogicControl(input, arg3);
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

s32 TaLogic_GetMinimumTask_MoveMission_001162F0(void *arg0, s32 arg1, void *arg2, u8 arg3, u8 arg4) {
    extern s32 TaLogic_IsOpenUnit_00117870();
    extern s32 TaLogic_GetUnitWarning();
    extern void TaLogic_GetRoot();
    extern s32 TaLogic_IsDefStyleUnit(s32, s32, s32, u8, s32);
    Coord_001162F0 coords[12];
    s32 initial;
    s32 cell;
    s32 count;

    initial = SzDuel_GetUnitLoc(((Unit_001162F0 *)arg0)->position >> 8, ((Unit_001162F0 *)arg0)->position & 0xFF);
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
                ((Output_001162F0 *)arg2)->flag = TaLogic_IsDefStyleUnit(((Unit_001162F0 *)arg0)->position >> 8, ((Unit_001162F0 *)arg0)->position & 0xFF, ((Output_001162F0 *)arg2)->target, arg4, 0);
                ((Output_001162F0 *)arg2)->value = TaLogic_IsOpenUnit_00117870(((Unit_001162F0 *)arg0)->position >> 8, ((Unit_001162F0 *)arg0)->position & 0xFF, arg0);
                TaLogic_InitRogicControl(arg0, arg3);
                return 0;
            }
        }

        if (SzDuel_GetUnitStatus(((Unit_001162F0 *)arg0)->position >> 8, ((Unit_001162F0 *)arg0)->position & 0xFF, 4) != 0) {
            if ((SzDuel_GetUnitKind(((Unit_001162F0 *)arg0)->position >> 8, ((Unit_001162F0 *)arg0)->position & 0xFF) >> 5) == 1 ||
                (SzDuel_GetUnitKind(((Unit_001162F0 *)arg0)->position >> 8, ((Unit_001162F0 *)arg0)->position & 0xFF) >> 5) == 5) {
                SzDuel_SetUnitStatus(((Unit_001162F0 *)arg0)->position >> 8, ((Unit_001162F0 *)arg0)->position & 0xFF, 0, 1);
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

        cell = SzDuel_GetMapUnitID(target_001162F0(arg0, side) & 0xFF, target_001162F0(arg0, side) >> 8);
        if (cell < 0) {
            cell = 0xFFFF;
        }
        TaLogic_GetRoot(((Unit_001162F0 *)arg0)->position >> 8, ((Unit_001162F0 *)arg0)->position & 0xFF,
                     coords, initial & 0xFF, initial >> 8, target_001162F0(arg0, side) & 0xFF,
                     target_001162F0(arg0, side) >> 8, (u16)cell, 7);
        count = TaLogic_GetMinGoalCount((u8 *)coords);
        {
            if (count > 0) {
                best = 0xFF;
                bestScore = 0xFFFF;
                for (index = 0; index < count; index++) {
                    if (SzDuel_GetMapUnit(candidate->x, candidate->y) == 0) {
                        s32 score = TaLogic_GetUnitWarning(candidate->x, candidate->y, arg1, 2, 1, (u8)TaLogic_GetWarnHideLvl_00117C30(arg1));
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
                ((Output_001162F0 *)arg2)->flag = TaLogic_IsDefStyleUnit(((Unit_001162F0 *)arg0)->position >> 8, ((Unit_001162F0 *)arg0)->position & 0xFF, ((Output_001162F0 *)arg2)->target, arg4, 0);
                ((Output_001162F0 *)arg2)->value = TaLogic_IsOpenUnit_00117870(((Unit_001162F0 *)arg0)->position >> 8, ((Unit_001162F0 *)arg0)->position & 0xFF, arg0);
                TaLogic_InitRogicControl(arg0, arg3);
                return 0;
            }

            if (best != 0xFF) {
                ((Output_001162F0 *)arg2)->position = ((Unit_001162F0 *)arg0)->position;
                ((Output_001162F0 *)arg2)->kind = 6;
                ((Output_001162F0 *)arg2)->target = (coords[best].y << 8) | coords[best].x;
                ((Output_001162F0 *)arg2)->flag = TaLogic_IsDefStyleUnit(((Unit_001162F0 *)arg0)->position >> 8, ((Unit_001162F0 *)arg0)->position & 0xFF, ((Output_001162F0 *)arg2)->target, arg4, 0);
                ((Output_001162F0 *)arg2)->value = TaLogic_IsOpenUnit_00117870(((Unit_001162F0 *)arg0)->position >> 8, ((Unit_001162F0 *)arg0)->position & 0xFF, arg0);
            } else {
                ((Output_001162F0 *)arg2)->position = ((Unit_001162F0 *)arg0)->position;
                ((Output_001162F0 *)arg2)->kind = 6;
                ((Output_001162F0 *)arg2)->target = initial;
                ((Output_001162F0 *)arg2)->flag = TaLogic_IsDefStyleUnit(((Unit_001162F0 *)arg0)->position >> 8, ((Unit_001162F0 *)arg0)->position & 0xFF, ((Output_001162F0 *)arg2)->target, arg4, 0);
                ((Output_001162F0 *)arg2)->value = TaLogic_IsOpenUnit_00117870(((Unit_001162F0 *)arg0)->position >> 8, ((Unit_001162F0 *)arg0)->position & 0xFF, arg0);
            }
            TaLogic_InitRogicControl(arg0, arg3);
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
    action->result = TaLogic_IsDefStyleUnit(source->position >> 8,
        source->position & 0xFF, action->target, flag, 0);
}

s32 TaLogic_GetMinimumTask_TrapMission_00116B60(void *arg0, s32 arg1, void *arg2, s32 arg3) {
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
    extern void TaLogic_GetInvadeRoot();

    mode = arg3 & 0xFF;
    xPosition = target_00116B60(arg0, mode);
    yPosition = target_00116B60(arg0, mode);
    if (SzDuel_GetUnit(yPosition >> 8, xPosition & 0xFF) == 0) {
        TaLogic_InitRogicControl(arg0, 1);
        return -1;
    }
    start = SzDuel_GetUnitLoc(source->position >> 8, source->position & 0xFF);
    xPosition = target_00116B60(arg0, mode);
    yPosition = target_00116B60(arg0, mode);
    target = SzDuel_GetUnitLoc(yPosition >> 8, xPosition & 0xFF);
    if (target_00116B60(arg0, mode) == 0xFFFF) {
        fill_00116B60(arg0, arg2, start, 1);
        return 0;
    } else {
        s32 unit = SzDuel_GetUnit(source->position >> 8, source->position & 0xFF);
        startX = start & 0xFF;
        startY = start >> 8;
        if (GetMoveRev(unit, startX, startY) == 0 ||
                TaLogic_IsAttackedNow(source->position >> 8, source->position & 0xFF, 0) == 1) {
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
                u16 card = (u16)TaLogic_GetWarnHideLvl_00117C30(arg1);
                TaLogic_GetInvadeRoot(position >> 8, position & 0xFF, points,
                    startX, startY, targetX = target & 0xFF,
                    targetY = target >> 8, target_00116B60(arg0, mode),
                    0, 30, card);
            }
            count = TaLogic_GetMinGoalCount((u8 *)points);
            bestIndex = 0xFF;
            if (count > 0) {
                bestScore = 0;
                for (i = 0; i < count; i++, p++) {
                    if (SzDuel_GetMapUnit(p->x, p->y) == 0) {
                        s32 score = TaLogic_GetUnitWarning(p->x, p->y, arg1, 3, 1,
                            TaLogic_GetWarnHideLvl_00117C30(arg1) & 0xFF);
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
                action->result = TaLogic_IsDefStyleUnit(source->position >> 8,
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


s32 TaLogic_GetMinimumTask_ReviveMission_001170A0(u16 *arg0, s32 arg1, void *arg2, u8 arg3) {
    Nibbles_001170A0 flags[12];
    s32 card;
    s32 selected;
    s32 index;
    Output_001170A0 *output = arg2;

    {
        s32 state;
        u32 *data;

        if ((SzDuel_GetUnitKind(*arg0 >> 8, *arg0 & 0xFF) >> 5) == 0) {
            data = SzDuel_GetUnitEffect(*arg0 >> 8, *arg0 & 0xFF, 3);
        } else {
            data = SzDuel_GetUnitEffect(*arg0 >> 8, *arg0 & 0xFF, 0);
        }
        card = SzDuel_GetUnitLoc(*arg0 >> 8, *arg0 & 0xFF);
        state = SzDuel_GetUnitKind(*arg0 >> 8, *arg0 & 0xFF) >> 5;
        index = 0;
        do {
            flags[index].low = flags[index].high = 15;
            index++;
        } while (index < 12);

        if (data != NULL) {
            selected = TaLogic001_IsUseRevive(arg1);
            if (state != 0) {
                if (SzDuel_GetField(card & 0xFF, card >> 8) == 9) {
                    selected = -1;
                }
                if (TaLogic_GetActionReaction(*arg0 >> 8, *arg0 & 0xFF, 0, 0, 6, 0) == 5) {
                    selected = -1;
                }
            }
            if (selected >= 0) {
                state = (selected >> 16) & 0xFFFF;
                card = TaLogic_GetGraveEntryAfterScreen(state, selected & 0xFF, *data & 0x3F);
                output->position = *arg0;
                output->command = 12;
                output->result = TaLogic_IsDefStyleUnit(*arg0 >> 8, *arg0 & 0xFF, output->value, 1, 0);
                output->count = 1;
                if (((*data >> 6) & 3) != 3) {
                    output->value = (arg1 << 8) | card;
                } else {
                    output->value = (state << 8) | card;
                }
                TaLogic_InitRogicControl(arg0, arg3);
                return 0;
            }
        }
        if (SzDuel_GetUnitStatus(*arg0 >> 8, *arg0 & 0xFF, 4) != 0) {
            SzDuel_SetUnitStatus(*arg0 >> 8, *arg0 & 0xFF, 0, 1);
            output->position = *arg0;
            output->command = 14;
            return 0;
        }
        return TaLogic_GetMinimumTask_RunMission_00115850(arg0, arg1, arg2, arg3);
    }
}

s32 TaLogic001_IsActiveMode(void) {
    if (TaLogic_GetGraveCardCount(SzDuel_GetTurnOwner(), 3, 2) != 0 ||
        TaLogic_GetGraveCardCount(SzDuel_GetTurnOwner(), 3, 0x345) != 0 ||
        SearchUnitByRange(0, 0, SzDuel_GetTurnOwner(), 1, 0x2001C, 14) != 0) {
        return 1;
    }
    return 0;
}

s32 TaLogic001_IsUseLifeHourGlass(s32 arg0) {
    s32 i;
    u8 n = 0;
    s32 need;
    u8 m;
    s32 j;

    if (SzDuel_GetLP(arg0) < 0x5DC) {
        return 0;
    }
    need = TaLogic_GetGraveCardCount(arg0, 3, 2) & 0xFF;
    if (need > 0) {
        for (i = 0; i < 8; i++) {
            if (Ta_GetSummonablePieceWithOrder(arg0, i, 1) >= 0) {
                n++;
            }
        }
        if (n >= need && 5 - SzDuel_GetUnitMonsterCount(arg0) >= need) {
            return 1;
        }
    }
    m = 0;
    need = TaLogic_GetGraveCardCount(arg0, 3, 0) & 0xFF;
    if (need > 0) {
        for (j = 0; j < 8; j++) {
            if (Ta_GetSummonablePieceWithOrder(arg0, j, 1) >= 0) {
                m++;
            }
        }
        if (m >= need && 5 - SzDuel_GetUnitMonsterCount(arg0) >= need) {
            return 1;
        }
    }
    return 0;
}

s32 TaLogic001_IsUseBraveHourGlass(s32 arg0) {
    s32 count;

    if (SzDuel_GetLP(arg0) < 0x5DC) {
        return 0;
    }
    count = SearchUnitByRange(0, 0, arg0, 1, 0x2001C, 14);
    count += SearchUnitByRange(0, 0, arg0, 1, 0x2001C, 14);
    if (count != 0) {
        if (SzDuel_GetUnitMonsterCount(arg0) >= 4) {
            return 1;
        }
    }
    return 0;
}

s32 TaLogic001_IsUseLordOfDragon(s32 arg0) {
    if (SearchUnitByRange(0, 0, arg0, 1, 0x2001C, 0xE) != 0) {
        return 1;
    }
    return (SearchUnitByRange(0, 0, arg0, 1, 0x1C, 0xE) != 0) ? 1 : 0;
}

s32 TaLogic001_IsUseRevive(s32 arg0) {
    extern s32 SzDuel_GetGraveCount(s32);
    s32 i;

    if (SzDuel_GetUnitMonsterCount(arg0) >= 5) {
        return -1;
    }
    if ((TaLogic_GetGraveCardCount(arg0, 3, 0) > 0 || TaLogic_GetGraveCardCount(arg0, 3, 2) > 0) &&
        SearchUnitByRange(0, 0, arg0, 1, 0x179001C, 0xE) == 0) {
        for (i = 0; i < SzDuel_GetGraveCount(arg0); i++) {
            if (SzDuel_InqGrave(arg0, i) == 2) {
                return (arg0 << 16) | i;
            }
        }
        for (i = 0; i < SzDuel_GetGraveCount(arg0 == 0 ? 1 : 0); i++) {
            if (SzDuel_InqGrave(arg0 == 0 ? 1 : 0, i) == 2) {
                return i | ((arg0 == 0 ? 1 : 0) << 16);
            }
        }
        for (i = 0; i < SzDuel_GetGraveCount(arg0); i++) {
            if (SzDuel_InqGrave(arg0, i) == 0) {
                return (arg0 << 16) | i;
            }
        }
        for (i = 0; i < SzDuel_GetGraveCount(arg0 == 0 ? 1 : 0); i++) {
            if (SzDuel_InqGrave(arg0 == 0 ? 1 : 0, i) == 0) {
                return i | ((arg0 == 0 ? 1 : 0) << 16);
            }
        }
    }
    return -1;
}

extern int func_001E1030_b(int a, int b);
extern unsigned *func_001E0B70_b(int a, int b, int n);
extern int func_00111320_b(int x, int y, int z);
static inline int func_00117870_either(int side)
{
    if (SearchUnitByRange(0, 0, side, 1, 0x2001C, 14) != 0) {
        return 1;
    }
    if (SearchUnitByRange(0, 0, side, 1, 28, 14) != 0) {
        return 1;
    }
    return 0;
}

int TaLogic_IsOpenUnit_00117870(int x, int y, int z)
{
    int kind;
    int side;
    unsigned *p;
    SzDuel_GetUnitLoc(x, y);
    kind = func_001E1030_b(x, y);
    side = Ta_IsUnitControl(x, y);
    p = func_001E0B70_b(x, y, 0);
    if (SzDuel_GetUnitStatus(x, y, 4)) {
        return 0;
    }
    switch (SzDuel_GetUnitKind(x, y) >> 5) {
    case 0:
        switch (kind) {
        case 83:
            if (func_00117870_either(side) == 1) {
                return 1;
            }
            break;
        case 146:
            if (TaUtil_GetGraveCardNum(side, 0) >= 6) {
                return 1;
            }
            break;
        }
        return 2;
    case 5:
        if (TaLogic_GetActionReaction(x, y, 0, 0, 6, 0) == 5) {
            return 2;
        }
        if (TaLogic001_IsDoCerem(Ta_IsUnitControl(x, y), kind) == 1) {
            if (SzDuel_GetField(x, y) != 9) {
                return 1;
            }
        }
        break;
    case 1:
        if (TaLogic_GetActionReaction(x, y, 0, 0, 6, 0) == 5) {
            return 2;
        }
        switch (*p >> 8) {
        case 13:
            return 1;
        case 2:
            if (TaLogic001_IsLandNearCntr(SzDuel_GetUnitLoc(x, y)) == 1) {
                return 1;
            }
            break;
        case 20:
            return 2;
        default:
            return func_00111320_b(x, y, z);
        }
        break;
    default:
        return 2;
    }
    return 2;
}

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

s32 TaLogic001_IsLandNearCntr(s32 arg0) {
    s32 temp_s0;
    s32 temp_v0;

    if (arg0 == 0x303) {
        return 1;
    }
    temp_v0 = SzDuel_GetMapUnit(3, 3);
    if (temp_v0 != 0) {
        temp_s0 = Ta_IsUnitControl2((void *) temp_v0);
        if (temp_s0 != SzDuel_GetTurnOwner()) {
            if (distance_00117B10(arg0 >> 8, arg0 & 0xFF) == 1) {
                return 1;
            }
        }
    }
    return 0;
}

s32 TaLogic001_IsDoCerem(s32 arg0, s32 arg1) {
    s32 sp20[3];

    Ta_GetCeremSacrifice(sp20, *(s32 *)((u8 *)TaHand_GetCardEffect(arg1, 0) + 4));
    if (Ta_GetSacrificeUnit(sp20, arg0) < 0) {
        return 0;
    }
    return 1;
}

s32 TaLogic_GetWarnHideLvl_00117C30(s32 arg0) {
    if (SzDuel_GetLP(arg0) > 0x4B0) {
        if (SzDuel_GetUnitMonsterCount(arg0) >= 4) {
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

s32 TaLogic_GetInputQueFromMinimumTask_b(void *, void *, s32);

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
        TaLogic_DoAdjustLogicData(w);
        if (TaLogic_GetMinimumTask_00112B90(w, &req, arg0) == 0) {
            return 0x800;
        }
        if (TaLogic_GetInputQueFromMinimumTask_b(w, &req, arg0) < 0) {
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

#pragma conditional_move off

s32 TaLogic_GetMinimumTask_00117E60(void *work, void *arg1, s32 arg2) {
    u16 *arg0 = work;
    s32 side;
    s32 found;
    s32 result;
    s32 index;

    side = SzDuel_GetTurnOwner();
    found = 0;
    if ((result = TaLogic_GetNextActiveUnit_00118510(arg0, side, (s32)arg1)) < 0) {
        return 0;
    }
    index = TaLogic_GetActionUnitFromOwnerID(arg0, result & 0xFFFF);
    if (index < 0) {
        return 0;
    }
    if ((result >> 16) == 1) {
        if (((arg0[index * 8 + 2] >> 8) & 0xFF) == 10) {
            TaLogic_InitRogicControl(arg0 + index * 8, 1);
        } else {
            TaLogic_InitRogicControl(arg0 + index * 8, 0);
        }
        return 1;
    }
    TaLogic_CommandUnit_00118330(arg0 + index * 8);
    switch ((arg0[index * 8 + 2] >> 8) & 0xFF) {
    case 5:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_RunMission_0011A4D0(arg0 + index * 8, side, arg1, 1);
            found = 1;
        }
        break;
    case 2:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            if (TaLogic_GetMinimumTask_AtkMission_0011AA70(arg0 + index * 8, side, arg1, 1) < 0) {
                TaLogic003_InitRogicControl(arg0 + index * 8, 1);
                return 1;
            }
            found = 1;
        }
        break;
    case 10:
        if (TaLogic_GetMinimumTask_Summon_00119300(arg0[index * 8], side, (s32)arg1) < 0) {
            TaLogic003_InitRogicControl(arg0 + index * 8, 1);
            *(u8 *)((u8 *)arg1 + 2) = 0xFF;
            *(s32 *)((u8 *)arg1 + 0xC) = 0;
        } else {
            TaLogic003_InitRogicControl(arg0 + index * 8, 1);
            found = 1;
        }
        break;
    case 11:
        TaLogic_GetMinimumTask_TrapMission_0011B0E0(arg0 + index * 8, side, arg1, 1);
        found = 1;
        break;
    case 6:
    case 15:
    case 16:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_MoveMission_0011B680(arg0 + index * 8, side, arg1, 1, 0);
            found = 1;
        }
        break;
    case 9:
        TaLogic_GetMinimumTask_EncMission(arg0 + index * 8, side, arg1, 1, 0, TaLogic_GetWarnHideLvl_0011AA10(side), 3, 1);
        found = 1;
        break;
    case 14:
        TaLogic_GetMinimumTask_DoNone(arg0 + index * 8, side, arg1);
        found = 1;
        break;
    default:
        found = 0;
        break;
    }
    if (found == 1) {
        return 1;
    }
    found = 0;
    switch (arg0[index * 8 + 2] & 0xFF) {
    case 5:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_RunMission_0011A4D0(arg0 + index * 8, side, arg1, 0);
            found = 1;
        }
        break;
    case 2:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            if (TaLogic_GetMinimumTask_AtkMission_0011AA70(arg0 + index * 8, side, arg1, 0) < 0) {
                TaLogic_GetMinimumTask_RunMission_0011A4D0(arg0 + index * 8, side, arg1, 0);
            }
            found = 1;
        }
        break;
    case 10:
        if (TaLogic_GetMinimumTask_Summon_00119300(arg0[index * 8], side, (s32)arg1) < 0) {
            TaLogic003_InitRogicControl(arg0 + index * 8, 0);
            *(u8 *)((u8 *)arg1 + 2) = 0xFF;
            found = 1;
            *(s32 *)((u8 *)arg1 + 0xC) = 0;
        } else {
            TaLogic_InitRogicControl(arg0 + index * 8, 0);
            found = 1;
        }
        break;
    case 11:
        TaLogic_GetMinimumTask_TrapMission_0011B0E0(arg0 + index * 8, side, arg1, 0);
        found = 1;
        break;
    case 6:
    case 15:
    case 16:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_MoveMission_0011B680(arg0 + index * 8, side, arg1, 0, 0);
            found = 1;
        }
        break;
    case 9:
        TaLogic_GetMinimumTask_EncMission(arg0 + index * 8, side, arg1, 0, 0, TaLogic_GetWarnHideLvl_0011AA10(side), 3, 1);
        found = 1;
        break;
    case 14:
        TaLogic_GetMinimumTask_DoNone(arg0 + index * 8, side, arg1);
        found = 1;
        break;
    default:
        return 0;
    }
    if (found == 1) {
        return 1;
    }
    return 0;
}
#pragma conditional_move reset

s32 TaLogic_CommandUnit_00118330(void *arg0) {
    u16 key;
    s32 temp_s1;
    s32 kind;

    key = *(u16 *)arg0;
    temp_s1 = Ta_IsUnitControl((s32)key >> 8, key & 0xFF);

    key = *(u16 *)arg0;
    if (SzDuel_GetUnit((s32)key >> 8, key & 0xFF) != 0) {
        key = *(u16 *)arg0;
        if (SzDuel_GetUnitStatus((s32)key >> 8, key & 0xFF, 0) == 0) {
            key = *(u16 *)arg0;
            if (key != 0xFFFF) {
                if ((key & 0xFF) == 0) {
                    if (*(s32 *)((u8 *)arg0 + 8) == -1) {
                        if (TaLogic_IsAttackedNow((s32)key >> 8, key & 0xFF, 0) == 1) {
                            if (SzDuel_InqHandPhase((s32)(*(u16 *)arg0) >> 8) == 1) {
                                *(u16 *)((u8 *)arg0 + 4) = 0x50A;
                            } else {
                                *(u16 *)((u8 *)arg0 + 4) = 0x5FF;
                            }
                        } else {
                            if (SzDuel_InqHandPhase((s32)(*(u16 *)arg0) >> 8) == 1) {
                                *(u16 *)((u8 *)arg0 + 4) = 0xA05;
                            } else {
                                *(u16 *)((u8 *)arg0 + 4) = 0xFF05;
                            }
                        }
                    }
                } else {
                    kind = SzDuel_GetUnitKind((s32)key >> 8, key & 0xFF) >> 5;
                    switch (kind) {
                    case 0:
                        TaLogic_CommandBtlUnit_001188F0(arg0, 1);
                        break;
                    case 3:
                        TaLogic_CommandTrapUnit_00118F50(arg0);
                        break;
                    case 4:
                    case 5:
                        *(u16 *)((u8 *)arg0 + 4) = 0x5FF;
                        break;
                    case 2:
                        TaLogic_CommandEncUnit(arg0, 3, 0, TaLogic_GetWarnHideLvl_0011AA10(temp_s1) & 0xFF);
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

s32 TaLogic_GetNextActiveUnit_00118510(u16 *arg0, s32 arg1, s32 arg2) {
    s32 i;
    s32 pos;
    s32 ret;
    s32 idx;
    u16 list[22];

    for (i = 0; i < 22; i++) {
        list[i] = 0xFFFF;
    }
    TaLogic_GetUnitCtlLst(arg1, list, 0x1D, 1);
    ret = TaLogic_GetAtkUnitNow(arg1, list, arg0);
    if (ret >= 0) {
        return ret;
    }
    for (i = 0; i < 22; i++) {
        list[i] = 0xFFFF;
    }
    TaLogic_GetUnitCtlLst(arg1, list, 0x1E, 1);
    for (i = 0; i < TaLogic_GetUnitCtlLstLen(list); i++) {
        if ((SzDuel_GetUnitKind(list[i] >> 8, list[i] & 0xFF) >> 5) == 3 &&
            TaLogic_IsUnitReadyMove(list[i]) == 1 && TaLogic_IsPickUp(list[i]) == 1) {
            return list[i];
        }
    }
    pos = arg1 << 8;
    idx = TaLogic_GetActionUnitFromOwnerID(arg0, pos);
    TaLogic_CommandUnit_00118330(arg0 + idx * 8);
    if (((arg0[idx * 8 + 2] >> 8) & 0xFF) == 10) {
        if (SzDuel_InqHandPhase(arg1) == 1 && TaLogic_GetMinimumTask_Summon_00119300(pos, arg1, arg2) >= 0) {
            return pos | 0x10000;
        }
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_GetUnitStatus(arg1, 0, 0) == 0) {
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_InqHandPhase(arg1) == 1 && TaLogic_GetMinimumTask_Summon_00119300(pos, arg1, arg2) >= 0) {
        return pos | 0x10000;
    }
    for (i = 0; i < 22; i++) {
        list[i] = 0xFFFF;
    }
    TaLogic_GetUnitCtlLst(arg1, list, 0x1F, 1);
    for (i = 0; i < TaLogic_GetUnitCtlLstLen(list); i++) {
        if (TaLogic_IsUnitReadyMove(list[i]) == 1 && TaLogic_IsPickUp(list[i]) == 1) {
            return list[i];
        }
    }
    for (i = 0; i < 22; i++) {
        list[i] = 0xFFFF;
    }
    TaLogic_GetUnitCtlLst(arg1, list, 0x1F, 1);
    for (i = 0; i < TaLogic_GetUnitCtlLstLen(list); i++) {
        if (SzDuel_GetUnitStatus(list[i] >> 8, list[i] & 0xFF, 0) == 0 && TaLogic_IsPickUp(list[i]) == 1) {
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

void TaLogic_CommandBtlUnit_001188F0(void *arg0, s32 arg1) {
    extern s32 TaLogic_IsRootOpen();
    extern void TaLogic_InitIgnoreLst();
    extern s32 TaLogic003_GetNearUnit();
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

    if (SzDuel_GetUnit(entry->coordinates >> 8, entry->coordinates & 0xFF) != 0) {
        side = Ta_GetCurrentSide(entry->coordinates >> 8, entry->coordinates & 0xFF);
        other = (side == 0 ? 1 : 0) << 8;
        pos = SzDuel_GetUnitLoc(entry->coordinates >> 8, entry->coordinates & 0xFF);
        otherPos = SzDuel_GetUnitLoc(other >> 8, other & 0xFF);
        player = SzDuel_GetUnit(entry->coordinates >> 8, entry->coordinates & 0xFF);
        for (i = 0; i < 22; i++) {
            list[i].card = 0xFFFF;
            list[i].flag = 0xFF;
        }
        if (arg1 != 0) {
            if (TaLogic_IsRootOpen(entry->coordinates >> 8, entry->coordinates & 0xFF,
                              pos & 0xFF, pos >> 8, other >> 8, other & 0xFF,
                              otherPos & 0xFF, otherPos >> 8, (u8)3) > 0) {
                entry->state = 0x2FF;
                entry->data.word = (other << 16) | entry->data.halves.low;
                return;
            }
        }
        TaLogic_InitIgnoreLst(work);
        countB = 0;
        countA = 0;
        i = 1;
        while (1) {
            switch (TaLogic003_GetNearUnit(entry, 0, player, pos & 0xFF, pos >> 8,
                                  Ta_GetCurrentSide(entry->coordinates >> 8, entry->coordinates & 0xFF) == 0 ? 1 : 0,
                                  (u8)i, TaLogic_GetWarnHideLvl_0011AA10(side), list, (u16)0, &countA, &countB, (u8)3, work)) {
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
        TaLogic003_CommandAtkLineUnit(arg0);
    }
}

void TaLogic003_GetNearUnit(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28) {
    TaLogic_GetNearUnit(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
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

void TaLogic003_CommandAtkLineUnit(void *arg0) {
    State_00118BC0 *state = arg0;
    s32 new_type;
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_s1;
    s32 temp_s1_2;
    s32 temp_s2;
    s32 temp_v0_2;
    u16 temp_v0;

    temp_s1 = SzDuel_GetTurnOwner();
    temp_v0 = state->id;
    temp_s2 = SzDuel_GetUnitLoc((s32) temp_v0 >> 8, temp_v0 & 0xFF);
    temp_s1_2 = TaLogic003_GetEmptyAtkLineStart(temp_s1);
    temp_v0_2 = TaLogic003_GetEmptyAtkLineEnd(temp_s1);
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

s32 TaLogic003_IsEmptyAtkLine(s32 arg0, s32 arg1) {
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
        slot = SzDuel_GetMapUnitID(row, index);
        if (slot >= 0) {
            high = slot >> 8;
            low = slot & 0xFF;
            if (arg0 == Ta_IsUnitControl(high, low) &&
                (SzDuel_GetUnitKind(high, low) >> 5) == 0) {
                return 0;
            }
        }
        index++;
        if (index > 5) {
            return 1;
        }
    }
}

s32 TaLogic003_GetEmptyAtkLineStart(s32 arg0) {
    s32 i;

    i = 0;
    do {
        if (TaLogic003_IsEmptyAtkLine(arg0, (u8)i) != 0) {
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

s32 TaLogic003_GetEmptyAtkLineEnd(s32 arg0) {
    s32 i = 0;

    do {
        if (TaLogic003_IsEmptyAtkLine(arg0, (u8)i) == 0) {
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


void TaLogic_CommandTrapUnit_00118F50(void *arg0) {
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
    extern s32 TaLogic_GetNearUnitL2();
    extern void TaLogic_InitIgnoreLst();

    if (SzDuel_GetUnit((s32) record[0] >> 8, record[0] & 0xFF) != 0) {
        player = Ta_GetCurrentSide((s32) record[0] >> 8, record[0] & 0xFF);
        position = SzDuel_GetUnitLoc((s32) record[0] >> 8, record[0] & 0xFF);
        owner = SzDuel_GetUnit((s32) record[0] >> 8, record[0] & 0xFF);
        record[2] = 0xBFF;
        for (i = 0; i < 22; i++) {
            slots[i].position = 0xFFFF;
            slots[i].flag = 0xFF;
        }
        TaLogic_InitIgnoreLst(work);
        a = 0;
        b = 0;
        c = 0;
        state = 0;
        for (i = 1; i < 3; i++) {
            state = TaLogic_GetNearUnitL2(state, owner, position & 0xFF, position >> 8,
                                  Ta_GetCurrentSide((s32) record[0] >> 8, record[0] & 0xFF) == 0 ? 1 : 0, (u8) i, 0,
                                  TaLogic_GetWarnHideLvl_0011AA10(player), slots, &a, &c, &b, work);
            result = TaLogic_GetTrapNearCard((s32) record[0] >> 8, record[0] & 0xFF, position & 0xFF, position >> 8,
                                   slots, 3, 0x1F, 1, 2, 0, TaLogic_GetWarnHideLvl_0011AA10(player), a, 1);
            if (result >= 0) {
                *(u32 *) (record + 4) = (result << 16) | record[4];
                return;
            }
            result = TaLogic_GetTrapNearCard((s32) record[0] >> 8, record[0] & 0xFF, position & 0xFF, position >> 8,
                                   slots, 3, 0x1F, 0, 2, 0, TaLogic_GetWarnHideLvl_0011AA10(player), a, 1);
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
            state = TaLogic_GetNearUnitL2(state, owner, position & 0xFF, position >> 8,
                                  Ta_GetCurrentSide((s32) record[0] >> 8, record[0] & 0xFF), (u8) i, 0,
                                  TaLogic_GetWarnHideLvl_0011AA10(player), slots, &a, &c, &b, work);
            result = TaLogic_GetFollowNearUnit(position & 0xFF, position >> 8, slots, 3, 0x22, 2, 2, a);
            if (result >= 0) {
                *(u32 *) (record + 4) = (result << 16) | record[4];
                return;
            }
            result = TaLogic_GetFollowNearUnit(position & 0xFF, position >> 8, slots, 3, 0x1F, 1, 2, a);
            if (result >= 0) {
                *(u32 *) (record + 4) = (result << 16) | record[4];
                return;
            }
            result = TaLogic_GetFollowNearUnit(position & 0xFF, position >> 8, slots, 3, 0x1F, 0, 2, a);
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


s32 TaLogic_GetMinimumTask_Summon_00119300(s32 arg0, s32 arg1, s32 arg2) {
    extern s32 TaLogic_GetUnitNum();
    Temp_00119300 temp;
    s32 color;
    s32 index;

    *(s16 *) (u8 *) arg2 = (s16) arg0;
    if (SzDuel_InqHandPhase(arg1) == 0) {
        return -1;
    }

    if (TaLogic_GetUnitNum(arg1, 0) == 5 && TaLogic_GetUnitNum(arg1, 1) == 5) {
        return -1;
    }

    if ((index = TaLogic_IsHandPlay_00119A40(arg1, &temp)) < 0) {
        return -1;
    } else {
        ((u8 *) arg2)[2] = 10;
        *(s32 *) ((u8 *) arg2 + 0xC) = 0;
        color = SzDuel_GetUnitLoc(arg0 >> 8, arg0 & 0xFF);

        if (index == 0) {
            if (TaLogic_SetComboQue_0011A0D0(arg1, (u8 *) arg2, &temp) >= 0) {
                if (TaLogic_GetNearCard2(&temp, color & 0xFF, color >> 8,
                        arg1 == 0 ? 1 : 0,
                        3, 0x1F, 2, 2, 0, TaLogic_GetWarnHideLvl_0011AA10(arg1)) < 0) {
                    if (SzDuel_GetUnitMonsterCount(arg1) >= 6) {
                        goto fallback;
                    }
                    index = TaLogic003_GetSummonPiece(arg1, index & 0xFF, &temp);
                    if (index < 0) {
                        return -1;
                    }
                    *(s16 *) ((u8 *) arg2 + 4) = (s16) index;
                    return 1;
                }

                index = TaLogic003_GetSummonPiece(arg1, index & 0xFF, &temp);
                if (index < 0) {
                    return -1;
                }
                *(s16 *) ((u8 *) arg2 + 4) = (s16) index;
                return 1;
            }
        } else {
            TaLogic_GetNearCard2(&temp, color & 0xFF, color >> 8,
                    arg1 == 0 ? 1 : 0,
                    3, 0x1F, 2, 2, 0, TaLogic_GetWarnHideLvl_0011AA10(arg1));
        }

    fallback:
        if (TaLogic003_GetSpellPlay(arg1, (u8 *) arg2, &temp, temp.value) < 0) {
            return -1;
        }
        index = TaLogic003_GetSummonPiece(arg1, index & 0xFF, &temp);
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
        if (TaLogic003_IsEmptyAtkLine(player, (u8)i) != 0) {
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

s32 TaLogic003_GetSummonPiece(s32 arg0, s32 arg1, void *arg2) {
    extern s32 TaLogic_GetSommonPiecePreference_0011A4C0();
    extern s32 TaLogic_IsUnitWin4();
    extern s32 TaLogic_GetInvadeRoot2();
    extern s32 TaLogic_GetRoot2(s32, s32, s32, s32, s32, s32, u16, u8);
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

        position = SzDuel_GetUnitLoc(arg0, 0);
        target = TaLogic_GetNearCard2(arg2, position & 0xFF, position >> 8,
                             arg0 == 0 ? 1 : 0, 3, 31, 2, 2, 0,
                             TaLogic_GetWarnHideLvl_0011AA10(arg0));
        if (target >= 0) {
            best_cost = 255;
            best_candidate = 65535;
            position = SzDuel_GetUnitLoc(target >> 8, target & 0xFF);
            i = 0;
            ref_y = position >> 8;
            ref_x = position & 0xFF;
            do {
                if ((candidate = TaLogic_GetSommonPiecePreference_0011A4C0(arg0, i)) >= 0) {
                    x = candidate & 0xFF;
                    y = candidate >> 8;
                    if (SzDuel_GetField(x, y) != 8 &&
                        (SzDuel_GetField(x, y) != 9 ||
                         Ta_IsVirus_Chk3(arg2, x, y) != 1) &&
                        SzDuel_GetMapUnit(x, y) == 0) {
                        if (TaLogic_IsUnitWin4(arg2, target, TaLogic_GetWarnHideLvl_0011AA10(arg0),
                                          ref_x, ref_y, 0) > 0) {
                            cost = TaLogic_GetInvadeRoot2(arg2, path, x, y,
                                                ref_x, ref_y, target, 0, 3,
                                                (u16)TaLogic_GetWarnHideLvl_0011AA10(arg0));
                        } else {
                            cost = TaLogic_GetRoot2((s32)arg2, (s32)path, x, y,
                                                ref_x, ref_y, target, 3);
                        }
                        if (TaLogic_GetMinGoalCount((u8 *)path) > 0 &&
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
                if ((candidate2 = TaLogic_GetSommonPiecePreference_0011A4C0(arg0, i2)) >= 0) {
                    x2 = candidate2 & 0xFF;
                    y2 = candidate2 >> 8;
                    if (SzDuel_GetField(x2, y2) != 8 &&
                        (SzDuel_GetField(x2, y2) != 9 ||
                         Ta_IsVirus_Chk3(arg2, x2, y2) != 1) &&
                        SzDuel_GetMapUnitID(x2, y2) < 0) {
                        occupied = SzDuel_GetMapUnitID(x2, y2);
                        if (occupied < 0) {
                            occupied = 65535;
                        }
                        cost2 = TaLogic_GetRoot2((s32)arg2, (s32)path, x2, y2,
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
            if ((candidate3 = TaLogic_GetSommonPiecePreference_0011A4C0(arg0, i3)) >= 0) {
                x3 = candidate3 & 0xFF;
                y3 = candidate3 >> 8;
                if (SzDuel_GetField(x3, y3) != 8 &&
                    SzDuel_GetField(x3, y3) != 9 &&
                    SzDuel_GetMapUnitID(x3, y3) < 0 && y3 < 8) {
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
        if (TaLogic003_IsEmptyAtkLine(arg0, (u8)i) == 0) {
            return i;
        }
    }
    return -1;
}

s32 TaLogic_IsHandPlay_00119A40(s32 arg0, void *arg1) {
    s32 cards[8];
    u8 scratch[32];
    u8 type0;
    u8 type1;
    s32 i;
    s32 result;

    extern s32 TaLogic_GetUnitNum();

    type0 = TaLogic_GetUnitNum(arg0, 0);
    type1 = TaLogic_GetUnitNum(arg0, 1);
    if (arg1 == NULL) {
        return -1;
    }

    TaHand_GetNextHand(arg0, cards);
    if (type0 == 5) {
        if (TaLogic003_GetSpellPlay(arg0, scratch, arg1, 999) >= 0) {
            return 1;
        } else {
            return -1;
        }
    } else if (type1 == 5) {
        for (i = 0; i < TaHand_GetNextHandNum(arg0); i++) {
            if ((TaHand_GetCardKind(cards[i]) >> 5) == 0 &&
                TaHand_IsCardSummon2(arg0, cards[i]) == 1) {
                SzDuel_InitCardInfo(arg1, cards[i]);
                return 0;
            }
        }
        return -1;
    } else {
        result = TaLogic003_IsSpellPlay(arg0, scratch, (s32)arg1);
        if (result >= 0) {
            return TaLogic003_GetSpellPlay(arg0, scratch, arg1, result);
        }

        i = find_slot_00119A40(arg0);

        if (i >= 0) {
            for (i = 0; i < TaHand_GetNextHandNum(arg0); i++) {
                if ((TaHand_GetCardKind(cards[i]) >> 5) == 0 &&
                    TaHand_IsCardSummon2(arg0, cards[i]) == 1) {
                    return 0;
                }
            }
            return TaLogic003_GetSpellPlay(arg0, scratch, arg1, 999);
        } else {
            for (i = 0; i < TaHand_GetNextHandNum(arg0); i++) {
                if ((TaHand_GetCardKind(cards[i]) >> 5) == 0 &&
                    TaHand_IsCardSummon2(arg0, cards[i]) == 1) {
                    SzDuel_InitCardInfo(arg1, cards[i]);
                    return 0;
                }
            }
            result = TaLogic003_GetSpellPlay(arg0, scratch, arg1, 999);
            if (result >= 0) {
                return result;
            }
            return -1;
        }
    }
}

s32 TaLogic003_GetSpellPlay(s32 arg0, u8 *arg1, void *arg2, s32 arg3) {
    s32 buf[8];
    s32 i;

    TaHand_GetNextHand(arg0, buf);
    if (arg2 == NULL) {
        return -1;
    }
    for (i = 0; i < 5; i++) {
        arg1[i + 6] = 0xFF;
    }
    for (i = 0; i < TaHand_GetNextHandNum(arg0); i++) {
        if (arg3 == buf[i] && arg3 != 999) {
            arg1[6] = i;
            SzDuel_InitCardInfo(arg2, buf[i]);
            return 1;
        }
    }
    for (i = 0; i < TaHand_GetNextHandNum(arg0); i++) {
        if ((TaHand_GetCardKind(buf[i]) >> 5) != 0 && (TaHand_GetCardKind(buf[i]) >> 5) != 2) {
            arg1[6] = i;
            SzDuel_InitCardInfo(arg2, buf[i]);
            return 1;
        }
    }
    for (i = 0; i < TaHand_GetNextHandNum(arg0); i++) {
        if ((TaHand_GetCardKind(buf[i]) >> 5) != 0) {
            arg1[6] = i;
            SzDuel_InitCardInfo(arg2, buf[i]);
            return 1;
        }
    }
    return -1;
}

typedef struct Info_00119F30 {
    u8 pad0[6];
    u8 slots[5];
} Info_00119F30;

s32 TaLogic003_IsSpellPlay(s32 arg0, void *arg1, s32 arg2) {
    Info_00119F30 *info = arg1;
    u16 cards[22];
    s32 ids[8];
    s32 i;
    s32 card;
    s32 type;

    for (i = 0; i < 22; i++) {
        cards[i] = 0xFFFF;
    }
    TaUtil_GetUnitLst(arg0, 2, cards);
    TaHand_GetNextHand(arg0, ids);
    if (arg2 == 0) {
        return -1;
    }
    for (i = 0; i < 5; i++) {
        info->slots[i] = 0xFF;
    }
    card = TaLogic_GetMaxApUnit(cards);
    if (card >= 0) {
        switch (SzDuel_GetUnitKind(card >> 8, card & 0xFF) & 0x1F) {
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
            for (i = 0; i < TaHand_GetNextHandNum(arg0); i++) {
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

u16 *TaLogic_GetFusionTree(s32, u16 *, s32, s32, s32, s16 *, s16 *);

s32 TaLogic_SetComboQue_0011A0D0(s32 arg0, u8 *arg1, void *arg2) {
    u16 *nodes[8];
    s32 entries[7];
    s16 a;
    s16 b;
    s32 i;
    s32 card;
    s32 value;
    s32 best;
    extern s32 TaLogic_GetEnchantQue2();

    if (arg2 == NULL) {
        return -1;
    } else {
        s32 top;
        s32 *entry;
        u16 **node;

        TaHand_GetNextHand(arg0, entries);
        best = -1;
        top = -1;
        i = 0;
        if (i < TaHand_GetNextHandNum(arg0)) {
            entry = entries;
            node = nodes;
            do {
                b = 0;
                a = 0;
                card = *entry;
                *node = NULL;
                if ((TaHand_GetCardKind(card) >> 5) == 0) {
                    *node = TaLogic_GetFusionTree(arg0, *node, i & 0xFF, card & 0xFFFF, 0, &a, &b);
                    *node = TaLogic_GetFusionRes(*node);
                    if (Taku_Get_WinCount() < 3) {
                        value = TaLogic_GetEnchantQue2(arg0, *node, 0, 0);
                    } else {
                        value = TaLogic_GetEnchantQue(arg0, *node, 0, 0);
                    }
                    if (TaHand_IsCardSummon2(arg0, card) == 1) {
                        if (best < value) {
                            TaLogic_ConvEmptyCombo_0011A2F0(arg0, *node, entries);
                            TaLogic_CopyArray((u8 *)*node + 2, arg1 + 6);
                            SzDuel_InitCardInfo(arg2, **node);
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
            } while (i < TaHand_GetNextHandNum(arg0));
        }
        return top;
    }
}

typedef struct {
    u16 id;
    u8 values[5];
} Info_0011A2F0;

void TaLogic_ConvEmptyCombo_0011A2F0(s32 arg0, void *arg1, s32 *arg2) {
    Info_0011A2F0 *info = arg1;
    u8 buf[5];
    s32 count;
    s32 i;
    s32 card;
    u8 level;
    u32 cost;
    extern u32 TaHand_GetCardAPDP();

    if (info != NULL) {
        level = TaHand_GetCardSummonCost2(info->id, arg0);
        for (i = 0; i < 5; i++) {
            buf[i] = 0xFF;
        }
        for (i = 0, count = 0; i < TaHand_GetNextHandNum(arg0); i++) {
            if ((u8)TaLogic_IsUseHandInCombo(i, info->values) == 0) {
                buf[count++] = i;
            }
        }
        if (count != 0) {
            for (i = 0; i < (u8)TaLogic_GetArrayLength(buf); i++) {
                card = arg2[buf[i]];
                if (card != 0x3E7 && level >= TaHand_GetCardSummonCost2(card, arg0)) {
                    cost = TaHand_GetCardAPDP(card);
                    if ((cost & 0xFFFF) + (cost >> 16) * 2 < 0xDAD && TaHand_IsCardEffect(card) == 2 &&
                        (u16)TaLogic_GetHandFusion(info->id, (u16)card) == 0x3E7) {
                        TaLogic_AddEmptyCombo(info->values, buf[i]);
                    }
                }
            }
        }
    }
}

s32 TaLogic_GetSommonPiecePreference_0011A4C0(s32 arg0, u32 arg1) {
    return Ta_GetSommonPiecePreference(arg0, arg1);
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


s32 TaLogic_GetMinimumTask_RunMission_0011A4D0(u16 *arg0, s32 arg1, void *arg2, u8 arg3) {
    extern s32 TaLogic_IsRunPassRoot(s32, s32, s32, s32, s32, s32, void *, u8);
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

    position = SzDuel_GetUnitLoc(*arg0 >> 8, *arg0 & 0xFF);
    i = 0;
    do {
        cells[i].low = cells[i].high = 15;
        i++;
    } while (i < 12);

    {
        u16 value = (u16)TaLogic_GetWarnHideLvl_0011AA10(arg1);
        originalX = position & 0xFF;
        originalY = position >> 8;
        if (TaLogic_GetUnitWarning(originalX, originalY, *arg0, 3, value, 0) == 0) {
            out->id = *arg0;
            out->action = 6;
            out->position = position;
            out->mode = TaLogic_IsDefStyleUnit(*arg0 >> 8, *arg0 & 0xFF, out->position, 1, 0);
            out->value = TaLogic_IsOpenUnit_0011C140(*arg0 >> 8, *arg0 & 0xFF, (u32 *)arg0);
            TaLogic003_InitRogicControl(arg0, arg3);
            return 0;
        } else {
            result = GetMoveRev(SzDuel_GetUnit(*arg0 >> 8, *arg0 & 0xFF), originalX, originalY);
            if (result == 0) {
                out->id = *arg0;
                out->action = 6;
                out->position = position;
                out->mode = TaLogic_IsDefStyleUnit(*arg0 >> 8, *arg0 & 0xFF, out->position, 1, 0);
                out->value = TaLogic_IsOpenUnit_0011C140(*arg0 >> 8, *arg0 & 0xFF, (u32 *)arg0);
                TaLogic003_InitRogicControl(arg0, arg3);
                return 0;
            } else {
                u8 startY;
                u8 endY;
                u8 startX;
                s32 end;
                bestPosition = 0xFF;
                bestScore = 0xFFFF;
                startX = GetCap(0, originalX - (result & 15)) & 0xFF;
                if (originalX + (result & 15) >= 7) {
                    end = 6;
                } else {
                    end = originalX + (result & 15);
                }
                upperX = end & 0xFF;
                startY = GetCap(0, originalY - (result & 15)) & 0xFF;
                end = originalY + (result & 15);
                if (end >= 7) {
                    end = 6;
                }
                endY = end & 0xFF;
                if ((*arg0 & 0xFF) == 0) {
                    flag = TaLogic_IsAttackedNow(*arg0 >> 8, *arg0 & 0xFF, 0) & 0xFF;
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
                            if (TaLogic_IsRunPassRoot(*arg0 >> 8, *arg0 & 0xFF, originalX, originalY, x, y, arg0, flag) == 1 &&
                                (TaLogic_IsAttackedNow2(*arg0 >> 8, *arg0 & 0xFF, x, y, 0) == 0 || (u8)*arg0 == 0)) {
                                value = (u16)TaLogic_GetWarnHideLvl_0011AA10(arg1);
                                score = TaLogic_GetUnitWarning(x, y, *arg0, 3, value, 0);
                                if (score < bestScore) {
                                    bestScore = score;
                                    bestPosition = packedY | x;
                                } else if (score == bestScore &&
                                           SzDuel_GetMapUnit(x, y) == 0 &&
                                           SzDuel_GetMapUnit(bestPosition & 0xFF, bestPosition >> 8) != 0) {
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
                        out->mode = TaLogic_IsDefStyleUnit(*arg0 >> 8, *arg0 & 0xFF, out->position, 1, 0);
                    } else {
                        out->mode = TaLogic_IsDefStyleUnit(*arg0 >> 8, *arg0 & 0xFF, out->position, 1, 0);
                    }
                    out->value = TaLogic_IsOpenUnit_0011C140(*arg0 >> 8, *arg0 & 0xFF, (u32 *)arg0);
                } else {
                    out->id = *arg0;
                    out->action = 6;
                    out->position = position;
                    out->mode = TaLogic_IsDefStyleUnit(*arg0 >> 8, *arg0 & 0xFF, out->position, 1, 0);
                    out->value = TaLogic_IsOpenUnit_0011C140(*arg0 >> 8, *arg0 & 0xFF, (u32 *)arg0);
                }
                TaLogic003_InitRogicControl(arg0, arg3);
            }
        }
    }
    return 0;
}

s32 TaLogic_GetWarnHideLvl_0011AA10(s32 arg0) {
    if (SzDuel_GetLP(arg0) > 0x5DC) {
        if (SzDuel_GetUnitMonsterCount(arg0) >= 3) {
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


static inline u32 target_0011AA70(void *arg0, u8 which) {
    Source_0011AA70 *source = arg0;
    if (which == 1) {
        return (u16)(source->targets >> 16);
    }
    return *(u16 *)&source->targets;
}

static inline s32 penalty_0011AA70(s32 object) {
    if (SzDuel_GetLP(object) > 0x5DC) {
        if (SzDuel_GetUnitMonsterCount(object) >= 3) {
            return 0;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}

s32 TaLogic_GetMinimumTask_AtkMission_0011AA70(void *arg0, s32 arg1, void *arg2, u8 arg3) {
    extern void TaLogic_GetInvadeRoot();
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
    if (SzDuel_GetUnit(targetYWord >> 8, targetXWord & 0xFF) == 0) {
        TaLogic_InitRogicControl(arg0, 1);
        return -1;
    }

    flag = TaLogic_IsOpenUnit_0011C140(source->position >> 8, source->position & 0xFF, arg0);
    sourceTarget = SzDuel_GetUnitLoc(source->position >> 8, source->position & 0xFF);
    targetXWord = target_0011AA70(arg0, arg3);
    targetYWord = target_0011AA70(arg0, arg3);
    otherTarget = SzDuel_GetUnitLoc(targetYWord >> 8, targetXWord & 0xFF);
    walk = positions;
    j = 0;
    do {
        walk->x = walk->y = 15;
        j++;
        walk++;
    } while (j < 12);

    object = SzDuel_GetUnit(source->position >> 8, source->position & 0xFF);
    sourceX = sourceTarget & 0xFF;
    sourceY = sourceTarget >> 8;
    if (GetMoveRev(object, sourceX, sourceY) == 0) {
        s32 cost;
        output->position = source->position;
        output->mode = 6;
        output->target = sourceTarget;
        cost = TaLogic_GetUnitWarning(sourceX, sourceY, arg1, 3, 1,
                            (u8)penalty_0011AA70(arg1));
        if (cost >= SzDuel_GetUnitAP(source->position >> 8, source->position & 0xFF, 0)) {
            output->value = TaLogic_IsDefStyleUnit(source->position >> 8, source->position & 0xFF,
                                        output->target, 1, 0);
        } else {
            output->value = TaLogic_IsDefStyleUnit(source->position >> 8, source->position & 0xFF,
                                        output->target, 0, 0);
        }
        TaLogic003_InitRogicControl(arg0, arg3);
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
        TaLogic_GetInvadeRoot(position >> 8, position & 0xFF, positions,
                      sourceX, sourceY, targetX = otherTarget & 0xFF,
                      targetY = otherTarget >> 8,
                      target_0011AA70(arg0, arg3), 0, 30, (u16)penalty);
        count = TaLogic_GetMinGoalCount((u8 *)positions);
        selected = 0xFF;
        if (count > 0) {
            selectedFlag = 0;
            bestCost = 0xFFFF;
            for (i = 0; i < count; i++) {
                s32 state = TaLogic003_IsOpenMoveUnit(source->position >> 8, source->position & 0xFF,
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
                    cost = TaLogic_GetUnitWarning(current->x, current->y, arg1, 3, 1,
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
            output->value = TaLogic_IsDefStyleUnit(source->position >> 8, source->position & 0xFF,
                                        output->target, 0, 0);
            TaLogic_InitRogicControl(arg0, arg3);
            return 0;
        }
        if (selected != 0xFF) {
            output->position = source->position;
            output->mode = 6;
            output->target = (positions[selected].y << 8) | positions[selected].x;
            output->flag = selectedFlag;
            output->value = TaLogic_IsDefStyleUnit(source->position >> 8, source->position & 0xFF,
                                        output->target, 0, 0);
            TaLogic003_InitRogicControl(arg0, arg3);
            return 0;
        } else {
            output->position = source->position;
            output->mode = 6;
            output->target = sourceTarget;
            output->flag = selectedFlag;
            output->value = TaLogic_IsDefStyleUnit(source->position >> 8, source->position & 0xFF,
                                        output->target, 0, 0);
            TaLogic003_InitRogicControl(arg0, arg3);
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


static inline u32 destination_0011B0E0(Input_0011B0E0 *input, u8 mode) {
    return mode == 1 ? (u32)(u16)(input->destination >> 16) :
                      (u32)*(u16 *)&input->destination;
}

static inline u16 flags_0011B0E0(s32 card) {
    if (SzDuel_GetLP(card) > 0x5DC) {
        if (SzDuel_GetUnitMonsterCount(card) >= 3) {
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
    output->result = TaLogic_IsDefStyleUnit(input->position >> 8, input->position & 0xFF,
                                 output->destination, 1, 0);
}

s32 TaLogic_GetMinimumTask_TrapMission_0011B0E0(void *arg0, s32 arg1, void *arg2, u8 arg3) {
    extern void TaLogic_GetInvadeRoot();
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

    if (SzDuel_GetUnit(destination_0011B0E0(input, arg3) >> 8,
                     destination_0011B0E0(input, arg3) & 0xFF) == 0) {
        TaLogic_InitRogicControl(input, 1);
        return -1;
    }
    origin = SzDuel_GetUnitLoc(input->position >> 8, input->position & 0xFF);
    target = SzDuel_GetUnitLoc(destination_0011B0E0(input, arg3) >> 8,
                          destination_0011B0E0(input, arg3) & 0xFF);
    if (destination_0011B0E0(input, arg3) == 0xFFFF) {
        fallback_0011B0E0(input, output, origin);
        return 0;
    }
    sourceCard = SzDuel_GetUnit(input->position >> 8, input->position & 0xFF);
    originY = origin & 0xFF;
    originX = origin >> 8;
    if (GetMoveRev(sourceCard, originY, originX) == 0 ||
        TaLogic_IsAttackedNow(input->position >> 8, input->position & 0xFF, 0) == 1) {
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
        TaLogic_GetInvadeRoot(input->position >> 8, input->position & 0xFF, positions,
                     originY, originX, targetY, target,
                     destination_0011B0E0(input, arg3), 0, 30, flags);
    }
    count = TaLogic_GetMinGoalCount((u8 *)positions);
    best = 0xFF;
    if (count > 0) {
        bestScore = 0;
        for (i = 0; i < count; i++, position++) {
            if (SzDuel_GetMapUnit(position->y, position->x) == 0) {
                s32 score = TaLogic_GetUnitWarning(position->y, position->x, arg1,
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
        output->result = TaLogic_IsDefStyleUnit(input->position >> 8, input->position & 0xFF,
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


#define target_0011B680(src, mode) ((mode) == 1 ? \
    (u32)(u16)((src)->targets.word >> 16) : (u32)(src)->targets.low)

static inline s32 option_0011B680(s32 card) {
    if (SzDuel_GetLP(card) > 0x5DC) {
        if (SzDuel_GetUnitMonsterCount(card) >= 3) {
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

s32 TaLogic_GetMinimumTask_MoveMission_0011B680(u32 *arg0, s32 arg1, u16 *arg2, u8 arg3, u8 arg4) {
    extern s32 TaLogic_IsDefStyleUnit(s32, s32, s32, u8, s32);
    extern void TaLogic_GetRoot(s32, s32, void *, s32, s32, s32, s32, s32, u8);
    Position_0011B680 positions[12];
    s32 y;
    s32 bestScore;
    s32 mode;
    s32 current;
    s32 command;

    current = SzDuel_GetUnitLoc(((Input_0011B680 *)arg0)->position >> 8, ((Input_0011B680 *)arg0)->position & 0xFF);
    mode = arg3;
    if (target_0011B680((Input_0011B680 *)arg0, mode) == 0xFFFF && current == target_0011B680((Input_0011B680 *)arg0, mode)) {
        arg2[0] = ((Input_0011B680 *)arg0)->position;
        ((Output_0011B680 *)arg2)->action = 6;
        arg2[2] = current;
        ((Output_0011B680 *)arg2)->state = TaLogic_IsDefStyleUnit(((Input_0011B680 *)arg0)->position >> 8, ((Input_0011B680 *)arg0)->position & 0xFF,
            arg2[2], arg4, 0);
        ((Output_0011B680 *)arg2)->value = TaLogic_IsOpenUnit_0011C140(((Input_0011B680 *)arg0)->position >> 8, ((Input_0011B680 *)arg0)->position & 0xFF, arg0);
        TaLogic003_InitRogicControl(arg0, arg3);
        return 0;
    } else {
        command = (((Input_0011B680 *)arg0)->command >> 8) & 0xFF;
        if (command == 15) {
            s32 x = current & 0xFF;
            s32 target;

            y = current >> 8;
            arg2[0] = ((Input_0011B680 *)arg0)->position;
            ((Output_0011B680 *)arg2)->action = 6;
            target = x | (GetCap(7, y +
                (GetMoveRev(SzDuel_GetUnit(((Input_0011B680 *)arg0)->position >> 8, ((Input_0011B680 *)arg0)->position & 0xFF), x, y) & 15)) << 8);
            arg2[2] = target;
            target = SzDuel_GetMapUnitID(target_0011B680((Input_0011B680 *)arg0, mode) & 0xFF,
                target_0011B680((Input_0011B680 *)arg0, mode) >> 8);
            if (target < 0) {
                target = 0xFFFF;
            }
            TaLogic_GetRoot(((Input_0011B680 *)arg0)->position >> 8, ((Input_0011B680 *)arg0)->position & 0xFF, positions, x, y,
                arg2[2] & 0xFF, arg2[2] >> 8, (u16)target, 2);
            if (TaLogic_GetMinGoalCount((u8 *)positions) == 0) {
                arg2[2] = current;
            }
            ((Output_0011B680 *)arg2)->state = TaLogic_IsDefStyleUnit(((Input_0011B680 *)arg0)->position >> 8, ((Input_0011B680 *)arg0)->position & 0xFF,
                arg2[2], arg4, 0);
            ((Output_0011B680 *)arg2)->value = TaLogic_IsOpenUnit_0011C140(((Input_0011B680 *)arg0)->position >> 8, ((Input_0011B680 *)arg0)->position & 0xFF, arg0);
            TaLogic003_InitRogicControl(arg0, arg3);
            return 0;
        } else {
            if (command == 16) {
                s32 y2;
                s32 x = current & 0xFF;
                s32 target;

                y2 = current >> 8;
                arg2[0] = ((Input_0011B680 *)arg0)->position;
                ((Output_0011B680 *)arg2)->action = 6;
                target = x | (GetCap(0, y2 -
                    (GetMoveRev(SzDuel_GetUnit(((Input_0011B680 *)arg0)->position >> 8, ((Input_0011B680 *)arg0)->position & 0xFF), x, y2) & 15)) << 8);
                arg2[2] = target;
                target = SzDuel_GetMapUnitID(target_0011B680((Input_0011B680 *)arg0, mode) & 0xFF,
                    target_0011B680((Input_0011B680 *)arg0, mode) >> 8);
                if (target < 0) {
                    target = 0xFFFF;
                }
                TaLogic_GetRoot(((Input_0011B680 *)arg0)->position >> 8, ((Input_0011B680 *)arg0)->position & 0xFF, positions, x, y2,
                    arg2[2] & 0xFF, arg2[2] >> 8, (u16)target, 2);
                if (TaLogic_GetMinGoalCount((u8 *)positions) == 0) {
                    arg2[2] = current;
                }
                ((Output_0011B680 *)arg2)->state = TaLogic_IsDefStyleUnit(((Input_0011B680 *)arg0)->position >> 8, ((Input_0011B680 *)arg0)->position & 0xFF,
                    arg2[2], arg4, 0);
                ((Output_0011B680 *)arg2)->value = TaLogic_IsOpenUnit_0011C140(((Input_0011B680 *)arg0)->position >> 8, ((Input_0011B680 *)arg0)->position & 0xFF, arg0);
                TaLogic003_InitRogicControl(arg0, arg3);
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
                target = SzDuel_GetMapUnitID(target_0011B680((Input_0011B680 *)arg0, mode) & 0xFF,
                    target_0011B680((Input_0011B680 *)arg0, mode) >> 8);
                if (target < 0) {
                    target = 0xFFFF;
                }
                TaLogic_GetRoot(((Input_0011B680 *)arg0)->position >> 8, ((Input_0011B680 *)arg0)->position & 0xFF, positions,
                    current & 0xFF, current >> 8, target_0011B680((Input_0011B680 *)arg0, mode) & 0xFF,
                    target_0011B680((Input_0011B680 *)arg0, mode) >> 8, (u16)target, 7);
                count = TaLogic_GetMinGoalCount((u8 *)positions);
                if (count > 0) {
                    best = 0xFF;
                    bestScore = 0xFFFF;
                    for (i = 0; i < count; i++, p++) {
                        s32 score;
                        if (SzDuel_GetMapUnit(p->x, p->y) == 0) {
                            score = TaLogic_GetUnitWarning(p->x, p->y, arg1, 3, 1, (u8)option_0011B680(arg1));
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
                    ((Output_0011B680 *)arg2)->state = TaLogic_IsDefStyleUnit(((Input_0011B680 *)arg0)->position >> 8, ((Input_0011B680 *)arg0)->position & 0xFF,
                        arg2[2], arg4, 0);
                    ((Output_0011B680 *)arg2)->value = TaLogic_IsOpenUnit_0011C140(((Input_0011B680 *)arg0)->position >> 8, ((Input_0011B680 *)arg0)->position & 0xFF, arg0);
                    TaLogic003_InitRogicControl(arg0, arg3);
                    return 0;
                }
                    if (best != 0xFF) {
                        arg2[0] = ((Input_0011B680 *)arg0)->position;
                        ((Output_0011B680 *)arg2)->action = 6;
                        arg2[2] = (positions[best].y << 8) | positions[best].x;
                        ((Output_0011B680 *)arg2)->state = TaLogic_IsDefStyleUnit(((Input_0011B680 *)arg0)->position >> 8, ((Input_0011B680 *)arg0)->position & 0xFF,
                            arg2[2], arg4, 0);
                        ((Output_0011B680 *)arg2)->value = TaLogic_IsOpenUnit_0011C140(((Input_0011B680 *)arg0)->position >> 8, ((Input_0011B680 *)arg0)->position & 0xFF, arg0);
                    } else {
                        arg2[0] = ((Input_0011B680 *)arg0)->position;
                        ((Output_0011B680 *)arg2)->action = 6;
                        arg2[2] = current;
                        ((Output_0011B680 *)arg2)->state = TaLogic_IsDefStyleUnit(((Input_0011B680 *)arg0)->position >> 8, ((Input_0011B680 *)arg0)->position & 0xFF,
                            arg2[2], arg4, 0);
                        ((Output_0011B680 *)arg2)->value = TaLogic_IsOpenUnit_0011C140(((Input_0011B680 *)arg0)->position >> 8, ((Input_0011B680 *)arg0)->position & 0xFF, arg0);
                    }
                    TaLogic003_InitRogicControl(arg0, arg3);
                
            }
        }
    }
    return 0;
}

s32 TaLogic_IsOpenUnit_0011C140(s32 arg0, s32 arg1, u32 *arg2) {
    /* really takes (arg0, arg1); the header says (void) */
    s32 SzDuel_GetUnitCardNo();
    u8 info[32];
    u32 *entry;

    if (SzDuel_GetUnitStatus(arg0, arg1, 4) != 0) {
        return 0;
    }
    switch (SzDuel_GetUnitKind(arg0, arg1) >> 5) {
    case 0:
        return 2;
    case 1:
        if (TaLogic_GetActionReaction(arg0, arg1, 0, 0, 6, 0) == 5) {
            return 2;
        }
        entry = Ta_GetUnitEffect(arg0, arg1, 0);
        if (entry == NULL) {
            return 2;
        }
        switch (*entry >> 8) {
        case 2:
            if ((u16)(arg2[2] >> 16) == SzDuel_GetUnitLoc(arg0, arg1)) {
                return 1;
            }
            break;
        case 0xD:
            return 1;
        default:
            if (SzDuel_GetUnitCardNo(arg0, arg1) ==
                TaLogic003_IsSpellPlay(Ta_IsUnitControl(arg0, arg1), info, SzDuel_GetUnit(arg0, arg1))) {
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

s32 TaLogic003_IsOpenMoveUnit(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 minY;
    s32 minX;

    minY = arg3 < arg5 ? arg3 : arg5;
    arg5 = max_0011C2E0(arg5, arg3);
    minX = arg2 < arg4 ? arg2 : arg4;
    arg4 = max_0011C2E0(arg4, arg2);
    if ((arg4 - minX) + (arg5 - minY) != 2) {
        return 0;
    }
    if (SzDuel_GetUnit(arg0, arg1) == 0) {
        return 0;
    }
    if (SzDuel_GetUnitStatus(arg0, arg1, 0) == 0) {
        if (CheckLandAgreement2(SzDuel_GetField(arg2, arg3), arg0, arg1) != 1) {
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

void TaLogic003_InitRogicControl(void *arg0, u8 arg1) {
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

s32 TaLogic_GetInputQueFromMinimumTask_b(void *, void *, s32);

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
        TaLogic_DoAdjustLogicData(w);
        if (TaLogic_GetMinimumTask_00117E60(w, &req, arg0) == 0) {
            return 0x800;
        }
        if (TaLogic_GetInputQueFromMinimumTask_b(w, &req, arg0) < 0) {
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

#pragma conditional_move off

s32 TaLogic_GetMinimumTask_0011C600(void *work, void *arg1, s32 arg2) {
    u16 *arg0 = work;
    s32 side;
    s32 found;
    s32 result;
    s32 index;

    side = SzDuel_GetTurnOwner();
    found = 0;
    if ((result = TaLogic_GetNextActiveUnit_0011CD30(arg0, side, (s32)arg1)) < 0) {
        return 0;
    }
    index = TaLogic_GetActionUnitFromOwnerID(arg0, result & 0xFFFF);
    if (index < 0) {
        return 0;
    }
    if ((result >> 16) == 1) {
        if (((arg0[index * 8 + 2] >> 8) & 0xFF) == 10) {
            TaLogic_InitRogicControl(arg0 + index * 8, 1);
        } else {
            TaLogic_InitRogicControl(arg0 + index * 8, 0);
        }
        return 1;
    }
    TaLogic_CommandUnit_0011CB20(arg0 + index * 8);
    switch ((arg0[index * 8 + 2] >> 8) & 0xFF) {
    case 5:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_RunMission_0011F540(arg0 + index * 8, side, arg1, 1);
            found = 1;
        }
        break;
    case 2:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            if (TaLogic_GetMinimumTask_AtkMission_0011FAE0(arg0 + index * 8, side, arg1, 1) < 0) {
                TaLogic004_InitRogicControl(arg0 + index * 8, 1);
                return 1;
            }
            found = 1;
        }
        break;
    case 10:
        if (TaLogic_GetMinimumTask_Summon_0011DFB0(arg0[index * 8], side, (s32)arg1) < 0) {
            TaLogic004_InitRogicControl(arg0 + index * 8, 1);
            *(u8 *)((u8 *)arg1 + 2) = 0xFF;
            *(s32 *)((u8 *)arg1 + 0xC) = 0;
        } else {
            TaLogic004_InitRogicControl(arg0 + index * 8, 1);
            found = 1;
        }
        break;
    case 11:
        TaLogic_GetMinimumTask_TrapMission_00120150(arg0 + index * 8, side, arg1, 1);
        found = 1;
        break;
    case 6:
    case 15:
    case 16:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_MoveMission_001206F0(arg0 + index * 8, side, arg1, 1, 0);
            found = 1;
        }
        break;
    case 3:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_MoveMission_001206F0(arg0 + index * 8, side, arg1, 1, 1);
            found = 1;
        }
        break;
    case 9:
        TaLogic_GetMinimumTask_EncMission(arg0 + index * 8, side, arg1, 1, 0, TaLogic_GetWarnHideLvl_0011FA80(side), 4, 1);
        found = 1;
        break;
    case 14:
        TaLogic_GetMinimumTask_DoNone(arg0 + index * 8, side, arg1);
        found = 1;
        break;
    default:
        found = 0;
        break;
    }
    if (found == 1) {
        return 1;
    }
    found = 0;

    switch (arg0[index * 8 + 2] & 0xFF) {
    case 5:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_RunMission_0011F540(arg0 + index * 8, side, arg1, 0);
            found = 1;
        }
        break;
    case 2:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            if (TaLogic_GetMinimumTask_AtkMission_0011FAE0(arg0 + index * 8, side, arg1, 0) < 0) {
                TaLogic_GetMinimumTask_RunMission_0011F540(arg0 + index * 8, side, arg1, 0);
            }
            found = 1;
        }
        break;
    case 10:
        if (TaLogic_GetMinimumTask_Summon_0011DFB0(arg0[index * 8], side, (s32)arg1) < 0) {
            TaLogic_InitRogicControl(arg0 + index * 8, 0);
            *(u8 *)((u8 *)arg1 + 2) = 0xFF;
            found = 1;
            *(s32 *)((u8 *)arg1 + 0xC) = 0;
        } else {
            TaLogic_InitRogicControl(arg0 + index * 8, 0);
            found = 1;
        }
        break;
    case 6:
    case 15:
    case 16:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_MoveMission_001206F0(arg0 + index * 8, side, arg1, 0, 0);
            found = 1;
        }
        break;
    case 3:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_MoveMission_001206F0(arg0 + index * 8, side, arg1, 0, 1);
            found = 1;
        }
        break;
    case 14:
        TaLogic_GetMinimumTask_DoNone(arg0 + index * 8, side, arg1);
        found = 1;
        break;
    case 9:
        TaLogic_GetMinimumTask_EncMission(arg0 + index * 8, side, arg1, 0, 0, TaLogic_GetWarnHideLvl_0011FA80(side), 4, 1);
        found = 1;
        break;
    default:
        return 0;
    }
    if (found == 1) {
        return 1;
    }
    return 0;
}
#pragma conditional_move reset

s32 TaLogic_CommandUnit_0011CB20(void *arg0) {
    s32 result;

    result = Ta_IsUnitControl(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF);
    if (SzDuel_GetUnit(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF) != 0) {
        if (SzDuel_GetUnitStatus(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF, 0) == 0) {
            if (*(u16 *)arg0 != 0xFFFF) {
                if ((*(u16 *)arg0 & 0xFF) == 0) {
                    if (*(s32 *)((u8 *)arg0 + 8) == -1) {
                        if (TaLogic_IsAttackedNow(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF, 0) == 1) {
                            if (SzDuel_InqHandPhase(*(u16 *)arg0 >> 8) == 1) {
                                *(u16 *)((u8 *)arg0 + 4) = 0x50A;
                            } else {
                                *(u16 *)((u8 *)arg0 + 4) = 0x5FF;
                            }
                        } else {
                            if (SzDuel_InqHandPhase(*(u16 *)arg0 >> 8) == 1) {
                                *(u16 *)((u8 *)arg0 + 4) = 0xA05;
                            } else {
                                *(u16 *)((u8 *)arg0 + 4) = 0xFF05;
                            }
                        }
                    }
                } else {
                    s32 subtype = SzDuel_GetUnitKind(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF) >> 5;

                    switch (subtype) {
                    case 0:
                        if (TaUtil_IsExMonster(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF) == 1) {
                            TaLogic_CommandEfcMonster_0011D9B0(arg0, 1);
                        } else {
                            TaLogic_CommandBtlUnit_0011D110(arg0, 1);
                        }
                        break;
                    case 3:
                        TaLogic_CommandTrapUnit_0011DC00(arg0);
                        break;
                    case 4:
                    case 5:
                        *(u16 *)((u8 *)arg0 + 4) = 0x5FF;
                        break;
                    case 2:
                        TaLogic_CommandEncUnit(arg0, 4, 0, (u8)TaLogic_GetWarnHideLvl_0011FA80(result));
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

s32 TaLogic_GetNextActiveUnit_0011CD30(u16 *arg0, s32 arg1, s32 arg2) {
    s32 i;
    s32 pos;
    s32 ret;
    s32 idx;
    u16 list[22];

    for (i = 0; i < 22; i++) {
        list[i] = 0xFFFF;
    }
    TaLogic_GetUnitCtlLst(arg1, list, 0x1D, 1);
    ret = TaLogic_GetAtkUnitNow(arg1, list, arg0);
    if (ret >= 0) {
        return ret;
    }
    for (i = 0; i < 22; i++) {
        list[i] = 0xFFFF;
    }
    TaLogic_GetUnitCtlLst(arg1, list, 0x1E, 1);
    for (i = 0; i < TaLogic_GetUnitCtlLstLen(list); i++) {
        if ((SzDuel_GetUnitKind(list[i] >> 8, list[i] & 0xFF) >> 5) == 3 &&
            TaLogic_IsUnitReadyMove(list[i]) == 1 && TaLogic_IsPickUp(list[i]) == 1) {
            return list[i];
        }
    }
    pos = arg1 << 8;
    idx = TaLogic_GetActionUnitFromOwnerID(arg0, pos);
    TaLogic_CommandUnit_0011CB20(arg0 + idx * 8);
    if (((arg0[idx * 8 + 2] >> 8) & 0xFF) == 10) {
        if (SzDuel_InqHandPhase(arg1) == 1 && TaLogic_GetMinimumTask_Summon_0011DFB0(pos, arg1, arg2) >= 0) {
            return pos | 0x10000;
        }
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_GetUnitStatus(arg1, 0, 0) == 0) {
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_InqHandPhase(arg1) == 1 && TaLogic_GetMinimumTask_Summon_0011DFB0(pos, arg1, arg2) >= 0) {
        return pos | 0x10000;
    }
    for (i = 0; i < 22; i++) {
        list[i] = 0xFFFF;
    }
    TaLogic_GetUnitCtlLst(arg1, list, 0x1F, 1);
    for (i = 0; i < TaLogic_GetUnitCtlLstLen(list); i++) {
        if (TaLogic_IsUnitReadyMove(list[i]) == 1 && TaLogic_IsPickUp(list[i]) == 1) {
            return list[i];
        }
    }
    for (i = 0; i < 22; i++) {
        list[i] = 0xFFFF;
    }
    TaLogic_GetUnitCtlLst(arg1, list, 0x1F, 1);
    for (i = 0; i < TaLogic_GetUnitCtlLstLen(list); i++) {
        if (SzDuel_GetUnitStatus(list[i] >> 8, list[i] & 0xFF, 0) == 0 && TaLogic_IsPickUp(list[i]) == 1) {
            return list[i];
        }
    }
    return -1;
}

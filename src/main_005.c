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


/* Fills hand combination `bCombo` for side `nSide`: the best fusion or equip chain, its card into `pCardInfo`. */
s32 TaLogic001_SetComboQue(s32 nSide, u8 *bCombo, void *pCardInfo) {
    u16 *nodes[8];
    s32 entries[7];
    s16 a;
    s16 b;
    s32 i;
    s32 card;
    s32 value;
    s32 best;

    if (pCardInfo == NULL) {
        return -1;
    } else {
        s32 top;
        s32 *entry;
        u16 **node;

        TaHand_GetNextHand(nSide, entries);
        best = -1;
        top = -1;
        i = 0;
        if (i < TaHand_GetNextHandNum(nSide)) {
            entry = entries;
            node = nodes;
            do {
                b = 0;
                a = 0;
                card = *entry;
                *node = NULL;
                if ((TaHand_GetCardKind(card) >> 5) == 0) {
                    *node = TaLogic_GetFusionTree(nSide, (struct TreeTag *)*node, i & 0xFF, card & 0xFFFF, 0, (u16 *)&a, (u16 *)&b);
                    *node = TaLogic_GetFusionRes(*node);
                    value = TaLogic_GetEnchantQue(nSide, *node, 0, 0);
                    if (TaHand_IsCardSummon2(nSide, card) == 1) {
                        if (best < value) {
                            TaLogic_ConvEmptyCombo_00114F20(nSide, *node, entries);
                            TaLogic_CopyArray((u8 *)*node + 2, bCombo + 6);
                            SzDuel_InitCardInfo(pCardInfo, **node);
                            ((Sprite_00114D40 *)pCardInfo)->x = (value >> 16) - (((Sprite_00114D40 *)pCardInfo)->info->x & 0x1FFF);
                            ((Sprite_00114D40 *)pCardInfo)->y = (value & 0xFFFF) - (((Sprite_00114D40 *)pCardInfo)->info->y & 0x1FFF);
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
            } while (i < TaHand_GetNextHandNum(nSide));
        }
        return top;
    }
}

typedef struct {
    u16 id;
    u8 values[5];
} Info_00114F20;

/* Fills an empty combination: the hand card side `nSide` can summon with the best attack plus defence. */
void TaLogic_ConvEmptyCombo_00114F20(s32 nSide, void *pCardInfo, s32 *pResult) {
    Info_00114F20 *info = pCardInfo;
    u8 buf[5];
    s32 count;
    s32 i;
    s32 card;
    u8 level;
    u32 cost;
    extern u32 TaHand_GetCardAPDP();

    if (info != NULL) {
        level = TaHand_GetCardSummonCost2(info->id, nSide);
        for (i = 0; i < 5; i++) {
            buf[i] = 0xFF;
        }
        for (i = 0, count = 0; i < TaHand_GetNextHandNum(nSide); i++) {
            if ((u8)TaLogic_IsUseHandInCombo(i, info->values) == 0) {
                buf[count++] = i;
            }
        }
        if (count != 0) {
            for (i = 0; i < (u8)TaLogic_GetArrayLength(buf); i++) {
                card = pResult[buf[i]];
                if (card != 0x3E7 && TaLogic001_IsRefuseEmptyCombo(card) == 0 && level >= TaHand_GetCardSummonCost2(card, nSide)) {
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

/* Whether this duelist keeps card `nCardNo` out of a summon (it is wanted for an equip). */
s32 TaLogic001_IsRefuseEmptyCombo(s32 nCardNo) {
    if ((TaHand_GetCardKind(nCardNo) >> 5) != 0) {
        return 1;
    }
    if (TaHand_IsCardEffect(nCardNo) == 1) {
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

/* Fills hand combination `bCombo` for side `nSide` with this duelist's special combination, its card into
   `pCardInfo`. */
s32 TaLogic001_SetSpecialComboQue(s32 nSide, void *bCombo, void *pCardInfo) {
    Obj1_00115160 *o1 = bCombo;
    Obj2_00115160 *o2 = pCardInfo;
    s32 list[8];
    s32 i;
    u8 k;

    for (i = 0; i < 5; i++) {
        o1->slot[i] = 0xFF;
    }
    TaHand_GetNextHand(nSide, list);
    if (o2 == NULL) {
        return -1;
    }
    for (i = 0; i < TaHand_GetNextHandNum(nSide); i++) {
        if (i != o1->slot[0] && i != o1->slot[1]) {
            if (o2->id == list[i]) {
                o1->slot[0] = i;
            }
        }
    }
    k = 1;
    if ((TaHand_GetCardKind(list[o1->slot[0]]) >> 5) == 0) {
        for (i = 0; i < TaHand_GetNextHandNum(nSide); i++) {
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


/* The square side `nSide` summons a card of kind `sKind` to. */
s32 TaLogic001_GetSummonPiece(s32 nSide, u8 sKind, void *pInput, s32 nMode) {
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

    if (pInput == NULL) {
        return -1;
    }
    p = cells;
    j = 0;
    do {
        p->low = p->high = 15;
        j++;
        p++;
    } while (j < 12);

    if ((u8)(*((u8 *)pInput + 0x3E) >> 5) == 0 &&
        *(u16 *)((u8 *)pInput + 0x3C) != 0x53) {
        best = 14;
        if (nMode >= 0) {
            s32 candidate;
            s32 candidate_y;
            s32 candidate_x;
            s32 n;
            s32 cost;

            best_cost = 255;
            best_position = 65535;
            target = SzDuel_GetUnitLoc(nMode >> 8, nMode & 255);
            n = 0;
            target_y = target >> 8;
            target_x = target & 255;
            do {
                candidate = Ta_GetSommonPiecePreference(nSide, n);
                if (candidate >= 0) {
                    candidate_x = candidate & 255;
                    candidate_y = candidate >> 8;
                    if (SzDuel_GetField(candidate_x, candidate_y) != 8 &&
                        (SzDuel_GetField(candidate_x, candidate_y) != 9 ||
                         Ta_IsVirus_Chk3(pInput, candidate_x, candidate_y) != 1) &&
                        SzDuel_GetMapUnit(candidate_x, candidate_y) == 0) {
                        if (TaLogic_IsUnitWin4(pInput, nMode, TaLogic_GetWarnHideLvl_00117C30(nSide),
                                         target_x, target_y, 0) > 0) {
                            cost = TaLogic_GetInvadeRoot2(pInput, cells, candidate_x, candidate_y,
                                                target_x, target_y, nMode, 0, 5,
                                                (u16)TaLogic_GetWarnHideLvl_00117C30(nSide));
                        } else {
                            cost = TaLogic_GetRoot2(pInput, cells, candidate_x, candidate_y,
                                                target_x, target_y, nMode, 5);
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
            position = Ta_GetSommonPiecePreference(nSide, i);
            if (position >= 0) {
                x = position & 255;
                y = position >> 8;
                if (SzDuel_GetField(x, y) != 8 &&
                    (SzDuel_GetField(x, y) != 9 || Ta_IsVirus_Chk3(pInput, x, y) != 1) &&
                    SzDuel_GetMapUnitID(x, y) < 0) {
                    if (CheckLandAgreement(3, pInput) == 1) {
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
                        result = TaLogic_GetRoot2(pInput, cells, x, y, target_x, target_y,
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
                        result = TaLogic_GetRoot2(pInput, cells, x, y, 3, 3, (u16)result, 7);
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
            position = Ta_GetSommonPiecePreference(nSide, i);
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


/* The task of a unit running from danger (task `pTask`): the safest square in reach, into `pInput` (`fFirst` = 1
   for the unit's first-choice task). */
s32 TaLogic_GetMinimumTask_RunMission_00115850(u16 *pTask, s32 nSide, void *pInput, u8 fFirst) {
    Output_00115850 *output = pInput;
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

    target = SzDuel_GetUnitLoc(*pTask >> 8, *pTask & 0xFF);
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

        initialScore = TaLogic_GetWarnHideLvl_00117C30(nSide);
        centerX = target & 0xFF;
        centerY = target >> 8;
        if (TaLogic_GetUnitWarning(centerX, centerY, *pTask, 3, initialScore, 0) == 0) {
            output->position = *pTask;
            output->action = 6;
            output->destination = target;
            output->result = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, output->destination, 1, 0);
            output->special = TaLogic_IsOpenUnit_00117870(*pTask >> 8, *pTask & 0xFF, pTask);
            TaLogic_InitRogicControl(pTask, fFirst);
            return 0;
        }
        if ((range = GetMoveRev(SzDuel_GetUnit(*pTask >> 8, *pTask & 0xFF), centerX, centerY)) == 0) {
            output->position = *pTask;
            output->action = 6;
            output->destination = target;
            output->result = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, output->destination, 1, 0);
            output->special = TaLogic_IsOpenUnit_00117870(*pTask >> 8, *pTask & 0xFF, pTask);
            TaLogic_InitRogicControl(pTask, fFirst);
            return 0;
        }
        if (SzDuel_GetUnitStatus(*pTask >> 8, *pTask & 0xFF, 4) != 0) {
            if ((SzDuel_GetUnitKind(*pTask >> 8, *pTask & 0xFF) >> 5) == 1 ||
                (SzDuel_GetUnitKind(*pTask >> 8, *pTask & 0xFF) >> 5) == 5) {
                SzDuel_SetUnitStatus(*pTask >> 8, *pTask & 0xFF, 0, 1);
                output->position = *pTask;
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
        if ((*pTask & 0xFF) == 0) {
            extra = (u8)TaLogic_IsAttackedNow(*pTask >> 8, *pTask & 0xFF, 0);
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
                if (TaLogic_IsRunPassRoot(*pTask >> 8, *pTask & 0xFF, centerX, centerY, x, y, pTask, extra) == 1) {
                    if (TaLogic_IsAttackedNow2(*pTask >> 8, *pTask & 0xFF, x, y, 0) == 0 || (u8)*pTask == 0) {
                        candidateScore = TaLogic_GetUnitWarning(x, y, *pTask, 3, (u16)TaLogic_GetWarnHideLvl_00117C30(nSide), 0);
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
            output->position = *pTask;
            output->action = 6;
            output->destination = best;
            if (best == target) {
                output->result = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, output->destination, 1, 0);
            } else {
                output->result = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, output->destination, 1, 0);
            }
            output->special = TaLogic_IsOpenUnit_00117870(*pTask >> 8, *pTask & 0xFF, pTask);
        } else {
            output->position = *pTask;
            output->action = 6;
            output->destination = target;
            output->result = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, output->destination, 1, 0);
            output->special = TaLogic_IsOpenUnit_00117870(*pTask >> 8, *pTask & 0xFF, pTask);
        }
        TaLogic_InitRogicControl(pTask, fFirst);
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

/* The task's target square: the second half-word when the second argument is 1, else the first. */
static inline u32 target_00115E20(void *src, u8 mode) {
    Input_00115E20 *input = src;
    if (mode == 1) {
        return (input->targets >> 16) & 0xFFFF;
    }
    return (u16)input->targets;
}


/* The task of a unit attacking (task `pTask`): its path to the goal, into `pInput`; -1 when it has none (`fFirst`
   = 1 for the unit's first-choice task). */
s32 TaLogic_GetMinimumTask_AtkMission_00115E20(void *pTask, s32 nSide, void *pInput, u8 fFirst) {
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
    Input_00115E20 *input = pTask;
    Output_00115E20 *output = pInput;

    selected = target_00115E20(input, fFirst);
    if (SzDuel_GetUnit(target_00115E20(input, fFirst) >> 8,
                     selected & 0xFF) == 0) {
        TaLogic_InitRogicControl(input, 1);
        return -1;
    }
    TaLogic_IsOpenUnit_00117870(input->position >> 8, input->position & 0xFF, (s32)input);
    origin = SzDuel_GetUnitLoc(input->position >> 8, input->position & 0xFF);
    selected = target_00115E20(input, fFirst);
    destination = SzDuel_GetUnitLoc(target_00115E20(input, fFirst) >> 8,
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
        score = TaLogic_GetUnitWarning(originX, originY, nSide, 3, 1,
                             (u8)TaLogic_GetWarnHideLvl_00117C30(nSide));
        if (score >= SzDuel_GetUnitAP(input->position >> 8, input->position & 0xFF, 0)) {
            output->result = 1;
        } else {
            output->result = 0;
        }
        TaLogic_InitRogicControl(input, fFirst);
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
        random = TaLogic_GetWarnHideLvl_00117C30(nSide);
        TaLogic_GetInvadeRoot(position >> 8, position & 0xFF, candidates,
                      originX, originY, destinationX = destination & 0xFF,
                      destinationY = destination >> 8,
                      target_00115E20(input, fFirst), (s64)0, (s64)30,
                      (s64)random);
        count = TaLogic_GetMinGoalCount((u8 *)candidates);
        bestIndex = 255;
        if (count > 0) {
            bestScore = 65535;
            for (index = 0; index < count; index++, point++) {
                s32 score = TaLogic_GetUnitWarning(point->x, point->y, nSide, 2, 1,
                                         (u8)TaLogic_GetWarnHideLvl_00117C30(nSide));
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
            TaLogic_InitRogicControl(input, fFirst);
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
            TaLogic_InitRogicControl(input, fFirst);
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


/* The task's target square: the second half-word when the second argument is 1, else the first. */
static inline u32 target_001162F0(void *unit, s32 side) {
    return side == 1 ? (u32)(u16)(((Unit_001162F0 *)unit)->target.packed >> 16) : (u32)((Unit_001162F0 *)unit)->target.low;
}

/* The smaller of the two values. */
static inline u32 minY_001162F0(void *unit, s32 side, u8 coord) {
    return coord < (target_001162F0(unit, side) >> 8) ? coord : (target_001162F0(unit, side) >> 8);
}

/* The larger of the two values. */
static inline u32 maxY_001162F0(void *unit, s32 side, u8 coord) {
    return (target_001162F0(unit, side) >> 8) < coord ? coord : (target_001162F0(unit, side) >> 8);
}

/* The smaller of the two values. */
static inline u32 minX_001162F0(void *unit, s32 side, u8 coord) {
    return coord < (target_001162F0(unit, side) & 0xFF) ? coord : (target_001162F0(unit, side) & 0xFF);
}

/* The larger of the two values. */
static inline u32 maxX_001162F0(void *unit, s32 side, u8 coord) {
    return (target_001162F0(unit, side) & 0xFF) < coord ? coord : (target_001162F0(unit, side) & 0xFF);
}

/* The task of a unit moving to its goal (task `pTask`), into `pInput` (`fFirst` = 1 for the unit's first-choice
   task). */
s32 TaLogic_GetMinimumTask_MoveMission_001162F0(void *pTask, s32 nSide, void *pInput, u8 fFirst, u8 nKind) {
    extern s32 TaLogic_IsOpenUnit_00117870();
    extern s32 TaLogic_GetUnitWarning();
    extern void TaLogic_GetRoot();
    extern s32 TaLogic_IsDefStyleUnit(s32, s32, s32, u8, s32);
    Coord_001162F0 coords[12];
    s32 initial;
    s32 cell;
    s32 count;

    initial = SzDuel_GetUnitLoc(((Unit_001162F0 *)pTask)->position >> 8, ((Unit_001162F0 *)pTask)->position & 0xFF);
    {
        s32 bestScore;
        s32 best;
        s32 side = fFirst;
        Coord_001162F0 *candidate;
        s32 index;
        if (target_001162F0(pTask, side) == 0xFFFF) {
            if (initial == target_001162F0(pTask, side)) {
                ((Output_001162F0 *)pInput)->position = ((Unit_001162F0 *)pTask)->position;
                ((Output_001162F0 *)pInput)->kind = 6;
                ((Output_001162F0 *)pInput)->target = initial;
                ((Output_001162F0 *)pInput)->flag = TaLogic_IsDefStyleUnit(((Unit_001162F0 *)pTask)->position >> 8, ((Unit_001162F0 *)pTask)->position & 0xFF, ((Output_001162F0 *)pInput)->target, nKind, 0);
                ((Output_001162F0 *)pInput)->value = TaLogic_IsOpenUnit_00117870(((Unit_001162F0 *)pTask)->position >> 8, ((Unit_001162F0 *)pTask)->position & 0xFF, pTask);
                TaLogic_InitRogicControl(pTask, fFirst);
                return 0;
            }
        }

        if (SzDuel_GetUnitStatus(((Unit_001162F0 *)pTask)->position >> 8, ((Unit_001162F0 *)pTask)->position & 0xFF, 4) != 0) {
            if ((SzDuel_GetUnitKind(((Unit_001162F0 *)pTask)->position >> 8, ((Unit_001162F0 *)pTask)->position & 0xFF) >> 5) == 1 ||
                (SzDuel_GetUnitKind(((Unit_001162F0 *)pTask)->position >> 8, ((Unit_001162F0 *)pTask)->position & 0xFF) >> 5) == 5) {
                SzDuel_SetUnitStatus(((Unit_001162F0 *)pTask)->position >> 8, ((Unit_001162F0 *)pTask)->position & 0xFF, 0, 1);
                ((Output_001162F0 *)pInput)->position = ((Unit_001162F0 *)pTask)->position;
                ((Output_001162F0 *)pInput)->kind = 14;
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

        cell = SzDuel_GetMapUnitID(target_001162F0(pTask, side) & 0xFF, target_001162F0(pTask, side) >> 8);
        if (cell < 0) {
            cell = 0xFFFF;
        }
        TaLogic_GetRoot(((Unit_001162F0 *)pTask)->position >> 8, ((Unit_001162F0 *)pTask)->position & 0xFF,
                     coords, initial & 0xFF, initial >> 8, target_001162F0(pTask, side) & 0xFF,
                     target_001162F0(pTask, side) >> 8, (u16)cell, 7);
        count = TaLogic_GetMinGoalCount((u8 *)coords);
        {
            if (count > 0) {
                best = 0xFF;
                bestScore = 0xFFFF;
                for (index = 0; index < count; index++) {
                    if (SzDuel_GetMapUnit(candidate->x, candidate->y) == 0) {
                        s32 score = TaLogic_GetUnitWarning(candidate->x, candidate->y, nSide, 2, 1, (u8)TaLogic_GetWarnHideLvl_00117C30(nSide));
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
                            bestMinY = minY_001162F0(pTask, side, bestY);
                            bestMaxY = maxY_001162F0(pTask, side, bestY);
                            bestX = (&coords[best])->x;
                            bestMinX = minX_001162F0(pTask, side, bestX);
                            bestMaxX = maxX_001162F0(pTask, side, bestX);
                            currentY = (u8)candidate->y;
                            currentMinY = minY_001162F0(pTask, side, currentY);
                            currentMaxY = maxY_001162F0(pTask, side, currentY);
                            currentX = candidate->x;
                            currentMinX = minX_001162F0(pTask, side, currentX);
                            currentMaxX = maxX_001162F0(pTask, side, currentX);
                            if ((currentMaxX - currentMinX) + (currentMaxY - currentMinY) < (bestMaxX - bestMinX) + (bestMaxY - bestMinY)) {
                                bestScore = score;
                                best = index;
                            }
                        }
                    }
                    candidate++;
                }
            } else {
                ((Output_001162F0 *)pInput)->position = ((Unit_001162F0 *)pTask)->position;
                ((Output_001162F0 *)pInput)->kind = 6;
                ((Output_001162F0 *)pInput)->target = initial;
                ((Output_001162F0 *)pInput)->flag = TaLogic_IsDefStyleUnit(((Unit_001162F0 *)pTask)->position >> 8, ((Unit_001162F0 *)pTask)->position & 0xFF, ((Output_001162F0 *)pInput)->target, nKind, 0);
                ((Output_001162F0 *)pInput)->value = TaLogic_IsOpenUnit_00117870(((Unit_001162F0 *)pTask)->position >> 8, ((Unit_001162F0 *)pTask)->position & 0xFF, pTask);
                TaLogic_InitRogicControl(pTask, fFirst);
                return 0;
            }

            if (best != 0xFF) {
                ((Output_001162F0 *)pInput)->position = ((Unit_001162F0 *)pTask)->position;
                ((Output_001162F0 *)pInput)->kind = 6;
                ((Output_001162F0 *)pInput)->target = (coords[best].y << 8) | coords[best].x;
                ((Output_001162F0 *)pInput)->flag = TaLogic_IsDefStyleUnit(((Unit_001162F0 *)pTask)->position >> 8, ((Unit_001162F0 *)pTask)->position & 0xFF, ((Output_001162F0 *)pInput)->target, nKind, 0);
                ((Output_001162F0 *)pInput)->value = TaLogic_IsOpenUnit_00117870(((Unit_001162F0 *)pTask)->position >> 8, ((Unit_001162F0 *)pTask)->position & 0xFF, pTask);
            } else {
                ((Output_001162F0 *)pInput)->position = ((Unit_001162F0 *)pTask)->position;
                ((Output_001162F0 *)pInput)->kind = 6;
                ((Output_001162F0 *)pInput)->target = initial;
                ((Output_001162F0 *)pInput)->flag = TaLogic_IsDefStyleUnit(((Unit_001162F0 *)pTask)->position >> 8, ((Unit_001162F0 *)pTask)->position & 0xFF, ((Output_001162F0 *)pInput)->target, nKind, 0);
                ((Output_001162F0 *)pInput)->value = TaLogic_IsOpenUnit_00117870(((Unit_001162F0 *)pTask)->position >> 8, ((Unit_001162F0 *)pTask)->position & 0xFF, pTask);
            }
            TaLogic_InitRogicControl(pTask, fFirst);
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


/* The task's target square: the second half-word when the second argument is 1, else the first. */
static inline u32 target_00116B60(void *arg0, s32 mode) {
    Source_00116B60 *source = arg0;
    if (mode == 1) {
        return (u16)(source->target.both >> 16);
    }
    return source->target.half[0];
}

/* Sets a move task (action 6) to the given square, and whether the unit should stay in defence there. */
static inline void fill_00116B60(void *arg0, void *arg2, s32 target, s32 flag) {
    Source_00116B60 *source = arg0;
    Action_00116B60 *action = arg2;
    action->position = source->position;
    action->action = 6;
    action->target = target;
    action->result = TaLogic_IsDefStyleUnit(source->position >> 8,
        source->position & 0xFF, action->target, flag, 0);
}

/* The task of setting a trap (task `pTask`), into `pInput`. */
s32 TaLogic_GetMinimumTask_TrapMission_00116B60(void *pTask, s32 nSide, void *pInput, s32 fFirst) {
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
    Source_00116B60 *source = pTask;
    Action_00116B60 *action = pInput;
    extern void TaLogic_GetInvadeRoot();

    mode = fFirst & 0xFF;
    xPosition = target_00116B60(pTask, mode);
    yPosition = target_00116B60(pTask, mode);
    if (SzDuel_GetUnit(yPosition >> 8, xPosition & 0xFF) == 0) {
        TaLogic_InitRogicControl(pTask, 1);
        return -1;
    }
    start = SzDuel_GetUnitLoc(source->position >> 8, source->position & 0xFF);
    xPosition = target_00116B60(pTask, mode);
    yPosition = target_00116B60(pTask, mode);
    target = SzDuel_GetUnitLoc(yPosition >> 8, xPosition & 0xFF);
    if (target_00116B60(pTask, mode) == 0xFFFF) {
        fill_00116B60(pTask, pInput, start, 1);
        return 0;
    } else {
        s32 unit = SzDuel_GetUnit(source->position >> 8, source->position & 0xFF);
        startX = start & 0xFF;
        startY = start >> 8;
        if (GetMoveRev(unit, startX, startY) == 0 ||
                TaLogic_IsAttackedNow(source->position >> 8, source->position & 0xFF, 0) == 1) {
            fill_00116B60(pTask, pInput, start, 1);
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
                u16 card = (u16)TaLogic_GetWarnHideLvl_00117C30(nSide);
                TaLogic_GetInvadeRoot(position >> 8, position & 0xFF, points,
                    startX, startY, targetX = target & 0xFF,
                    targetY = target >> 8, target_00116B60(pTask, mode),
                    0, 30, card);
            }
            count = TaLogic_GetMinGoalCount((u8 *)points);
            bestIndex = 0xFF;
            if (count > 0) {
                bestScore = 0;
                for (i = 0; i < count; i++, p++) {
                    if (SzDuel_GetMapUnit(p->x, p->y) == 0) {
                        s32 score = TaLogic_GetUnitWarning(p->x, p->y, nSide, 3, 1,
                            TaLogic_GetWarnHideLvl_00117C30(nSide) & 0xFF);
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
                fill_00116B60(pTask, pInput, start, 1);
                return 0;
            }
            if (bestIndex != 0xFF) {
                action->position = source->position;
                action->action = 6;
                action->target = (points[bestIndex].y << 8) | points[bestIndex].x;
                action->result = TaLogic_IsDefStyleUnit(source->position >> 8,
                    source->position & 0xFF, action->target, 0, 0);
            } else {
                fill_00116B60(pTask, pInput, start, 1);
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


/* The task of reviving a monster from the graveyard (task `pTask`), into `pInput` (`fFirst` = 1 for the unit's
   first-choice task). */
s32 TaLogic_GetMinimumTask_ReviveMission_001170A0(u16 *pTask, s32 nSide, void *pInput, u8 fFirst) {
    Nibbles_001170A0 flags[12];
    s32 card;
    s32 selected;
    s32 index;
    Output_001170A0 *output = pInput;

    {
        s32 state;
        u32 *data;

        if ((SzDuel_GetUnitKind(*pTask >> 8, *pTask & 0xFF) >> 5) == 0) {
            data = SzDuel_GetUnitEffect(*pTask >> 8, *pTask & 0xFF, 3);
        } else {
            data = SzDuel_GetUnitEffect(*pTask >> 8, *pTask & 0xFF, 0);
        }
        card = SzDuel_GetUnitLoc(*pTask >> 8, *pTask & 0xFF);
        state = SzDuel_GetUnitKind(*pTask >> 8, *pTask & 0xFF) >> 5;
        index = 0;
        do {
            flags[index].low = flags[index].high = 15;
            index++;
        } while (index < 12);

        if (data != NULL) {
            selected = TaLogic001_IsUseRevive(nSide);
            if (state != 0) {
                if (SzDuel_GetField(card & 0xFF, card >> 8) == 9) {
                    selected = -1;
                }
                if (TaLogic_GetActionReaction(*pTask >> 8, *pTask & 0xFF, 0, 0, 6, 0) == 5) {
                    selected = -1;
                }
            }
            if (selected >= 0) {
                state = (selected >> 16) & 0xFFFF;
                card = TaLogic_GetGraveEntryAfterScreen(state, selected & 0xFF, *data & 0x3F);
                output->position = *pTask;
                output->command = 12;
                output->result = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, output->value, 1, 0);
                output->count = 1;
                if (((*data >> 6) & 3) != 3) {
                    output->value = (nSide << 8) | card;
                } else {
                    output->value = (state << 8) | card;
                }
                TaLogic_InitRogicControl(pTask, fFirst);
                return 0;
            }
        }
        if (SzDuel_GetUnitStatus(*pTask >> 8, *pTask & 0xFF, 4) != 0) {
            SzDuel_SetUnitStatus(*pTask >> 8, *pTask & 0xFF, 0, 1);
            output->position = *pTask;
            output->command = 14;
            return 0;
        }
        return TaLogic_GetMinimumTask_RunMission_00115850(pTask, nSide, pInput, fFirst);
    }
}

/* Whether this duelist plays in its attacking mode this turn. */
s32 TaLogic001_IsActiveMode(void) {
    if (TaLogic_GetGraveCardCount(SzDuel_GetTurnOwner(), 3, 2) != 0 ||
        TaLogic_GetGraveCardCount(SzDuel_GetTurnOwner(), 3, 0x345) != 0 ||
        SearchUnitByRange(0, 0, SzDuel_GetTurnOwner(), 1, 0x2001C, 14) != 0) {
        return 1;
    }
    return 0;
}

/* Whether side `nSide` should use the life hourglass now (enough life points, graveyard monsters and free
   squares). */
s32 TaLogic001_IsUseLifeHourGlass(s32 nSide) {
    s32 i;
    u8 n = 0;
    s32 need;
    u8 m;
    s32 j;

    if (SzDuel_GetLP(nSide) < 0x5DC) {
        return 0;
    }
    need = TaLogic_GetGraveCardCount(nSide, 3, 2) & 0xFF;
    if (need > 0) {
        for (i = 0; i < 8; i++) {
            if (Ta_GetSummonablePieceWithOrder(nSide, i, 1) >= 0) {
                n++;
            }
        }
        if (n >= need && 5 - SzDuel_GetUnitMonsterCount(nSide) >= need) {
            return 1;
        }
    }
    m = 0;
    need = TaLogic_GetGraveCardCount(nSide, 3, 0) & 0xFF;
    if (need > 0) {
        for (j = 0; j < 8; j++) {
            if (Ta_GetSummonablePieceWithOrder(nSide, j, 1) >= 0) {
                m++;
            }
        }
        if (m >= need && 5 - SzDuel_GetUnitMonsterCount(nSide) >= need) {
            return 1;
        }
    }
    return 0;
}

/* Whether side `nSide` should use the brave hourglass now (enough life points, a target in range, 4+ monsters). */
s32 TaLogic001_IsUseBraveHourGlass(s32 nSide) {
    s32 count;

    if (SzDuel_GetLP(nSide) < 0x5DC) {
        return 0;
    }
    count = SearchUnitByRange(0, 0, nSide, 1, 0x2001C, 14);
    count += SearchUnitByRange(0, 0, nSide, 1, 0x2001C, 14);
    if (count != 0) {
        if (SzDuel_GetUnitMonsterCount(nSide) >= 4) {
            return 1;
        }
    }
    return 0;
}

/* Whether side `nSide` has a dragon in range for Lord of Dragons. */
s32 TaLogic001_IsUseLordOfDragon(s32 nSide) {
    if (SearchUnitByRange(0, 0, nSide, 1, 0x2001C, 0xE) != 0) {
        return 1;
    }
    return (SearchUnitByRange(0, 0, nSide, 1, 0x1C, 0xE) != 0) ? 1 : 0;
}

/* Whether side `nSide` should use a revive card now. */
s32 TaLogic001_IsUseRevive(s32 nSide) {
    extern s32 SzDuel_GetGraveCount(s32);
    s32 i;

    if (SzDuel_GetUnitMonsterCount(nSide) >= 5) {
        return -1;
    }
    if ((TaLogic_GetGraveCardCount(nSide, 3, 0) > 0 || TaLogic_GetGraveCardCount(nSide, 3, 2) > 0) &&
        SearchUnitByRange(0, 0, nSide, 1, 0x179001C, 0xE) == 0) {
        for (i = 0; i < SzDuel_GetGraveCount(nSide); i++) {
            if (SzDuel_InqGrave(nSide, i) == 2) {
                return (nSide << 16) | i;
            }
        }
        for (i = 0; i < SzDuel_GetGraveCount(nSide == 0 ? 1 : 0); i++) {
            if (SzDuel_InqGrave(nSide == 0 ? 1 : 0, i) == 2) {
                return i | ((nSide == 0 ? 1 : 0) << 16);
            }
        }
        for (i = 0; i < SzDuel_GetGraveCount(nSide); i++) {
            if (SzDuel_InqGrave(nSide, i) == 0) {
                return (nSide << 16) | i;
            }
        }
        for (i = 0; i < SzDuel_GetGraveCount(nSide == 0 ? 1 : 0); i++) {
            if (SzDuel_InqGrave(nSide == 0 ? 1 : 0, i) == 0) {
                return i | ((nSide == 0 ? 1 : 0) << 16);
            }
        }
    }
    return -1;
}

extern int func_001E1030_b(int a, int b);
extern unsigned *func_001E0B70_b(int a, int b, int n);
extern int func_00111320_b(int x, int y, int z);
/* Whether side `side` has a dragon in range (either search key). */
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

/* Whether this duelist opens (turns face up) unit (nSide, nID) now: 0 no, 1 or 2 by its kind. */
int TaLogic_IsOpenUnit_00117870(int nSide, int nID, int pInfo)
{
    int kind;
    int side;
    unsigned *p;
    SzDuel_GetUnitLoc(nSide, nID);
    kind = func_001E1030_b(nSide, nID);
    side = Ta_IsUnitControl(nSide, nID);
    p = func_001E0B70_b(nSide, nID, 0);
    if (SzDuel_GetUnitStatus(nSide, nID, 4)) {
        return 0;
    }
    switch (SzDuel_GetUnitKind(nSide, nID) >> 5) {
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
        if (TaLogic_GetActionReaction(nSide, nID, 0, 0, 6, 0) == 5) {
            return 2;
        }
        if (TaLogic001_IsDoCerem(Ta_IsUnitControl(nSide, nID), kind) == 1) {
            if (SzDuel_GetField(nSide, nID) != 9) {
                return 1;
            }
        }
        break;
    case 1:
        if (TaLogic_GetActionReaction(nSide, nID, 0, 0, 6, 0) == 5) {
            return 2;
        }
        switch (*p >> 8) {
        case 13:
            return 1;
        case 2:
            if (TaLogic001_IsLandNearCntr(SzDuel_GetUnitLoc(nSide, nID)) == 1) {
                return 1;
            }
            break;
        case 20:
            return 2;
        default:
            return func_00111320_b(nSide, nID, pInfo);
        }
        break;
    default:
        return 2;
    }
    return 2;
}

/* The smaller of the two values. */
static inline s32 min_00117B10(s32 a, s32 b) {
    return (a < b) ? a : b;
}

/* The larger of the two values. */
static inline s32 max_00117B10(s32 a, s32 b) {
    return (a > b) ? a : b;
}

/* The board distance (steps across plus steps along). */
static inline s32 distance_00117B10(s32 x, s32 y) {
    return (max_00117B10(y, 3) - min_00117B10(y, 3)) +
           (max_00117B10(x, 3) - min_00117B10(x, 3));
}

/* Whether square `nLoc` is the centre, or next to a centre held by the opponent. */
s32 TaLogic001_IsLandNearCntr(s32 nLoc) {
    s32 controller;
    s32 mapUnit;

    if (nLoc == 0x303) {
        return 1;
    }
    mapUnit = SzDuel_GetMapUnit(3, 3);
    if (mapUnit != 0) {
        controller = Ta_IsUnitControl2((void *) mapUnit);
        if (controller != SzDuel_GetTurnOwner()) {
            if (distance_00117B10(nLoc >> 8, nLoc & 0xFF) == 1) {
                return 1;
            }
        }
    }
    return 0;
}

/* Whether side `nSide` can play ritual card `nCardNo` now (it has the units to give up). */
s32 TaLogic001_IsDoCerem(s32 nSide, s32 nCardNo) {
    s32 sp20[3];

    Ta_GetCeremSacrifice(sp20, *(s32 *)((u8 *)TaHand_GetCardEffect(nCardNo, 0) + 4));
    if (Ta_GetSacrificeUnit(sp20, nSide) < 0) {
        return 0;
    }
    return 1;
}

/* How careful this duelist is about hidden cards (by its life points and monster count). */
s32 TaLogic_GetWarnHideLvl_00117C30(s32 nSide) {
    if (SzDuel_GetLP(nSide) > 0x4B0) {
        if (SzDuel_GetUnitMonsterCount(nSide) >= 4) {
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

/* This computer duelist's controller (one entry of duelistControllers): the buttons it presses this frame. With an empty
   input queue it plans its next task and turns it into buttons, then plays the queue back one button per frame;
   after 600 frames it gives up the turn (0x20, then 0x800). */
s32 func_00117C90(s32 wCursorPos, void *pCtl) {
    Req_00117C90 req;
    Work_00117C90 *w;
    s32 i;
    s32 ret;

    w = pCtl;
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
        if (TaLogic_GetMinimumTask_00112B90(w, &req, wCursorPos) == 0) {
            return 0x800;
        }
        if (TaLogic_GetInputQueFromMinimumTask_b(w, &req, wCursorPos) < 0) {
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

/* This duelist's move: picks the next unit to act, gives it a task and turns that into input `pInput`; returns 1
   when it set one. */
s32 TaLogic_GetMinimumTask_00117E60(void *pCtl, void *pInput, s32 wCursorPos) {
    u16 *arg0 = pCtl;
    s32 side;
    s32 found;
    s32 result;
    s32 index;

    side = SzDuel_GetTurnOwner();
    found = 0;
    if ((result = TaLogic_GetNextActiveUnit_00118510(arg0, side, (s32)pInput)) < 0) {
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
            TaLogic_GetMinimumTask_RunMission_0011A4D0(arg0 + index * 8, side, pInput, 1);
            found = 1;
        }
        break;
    case 2:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            if (TaLogic_GetMinimumTask_AtkMission_0011AA70(arg0 + index * 8, side, pInput, 1) < 0) {
                TaLogic003_InitRogicControl(arg0 + index * 8, 1);
                return 1;
            }
            found = 1;
        }
        break;
    case 10:
        if (TaLogic_GetMinimumTask_Summon_00119300(arg0[index * 8], side, (s32)pInput) < 0) {
            TaLogic003_InitRogicControl(arg0 + index * 8, 1);
            *(u8 *)((u8 *)pInput + 2) = 0xFF;
            *(s32 *)((u8 *)pInput + 0xC) = 0;
        } else {
            TaLogic003_InitRogicControl(arg0 + index * 8, 1);
            found = 1;
        }
        break;
    case 11:
        TaLogic_GetMinimumTask_TrapMission_0011B0E0(arg0 + index * 8, side, pInput, 1);
        found = 1;
        break;
    case 6:
    case 15:
    case 16:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_MoveMission_0011B680(arg0 + index * 8, side, pInput, 1, 0);
            found = 1;
        }
        break;
    case 9:
        TaLogic_GetMinimumTask_EncMission(arg0 + index * 8, side, pInput, 1, 0, TaLogic_GetWarnHideLvl_0011AA10(side), 3, 1);
        found = 1;
        break;
    case 14:
        TaLogic_GetMinimumTask_DoNone(arg0 + index * 8, side, pInput);
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
            TaLogic_GetMinimumTask_RunMission_0011A4D0(arg0 + index * 8, side, pInput, 0);
            found = 1;
        }
        break;
    case 2:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            if (TaLogic_GetMinimumTask_AtkMission_0011AA70(arg0 + index * 8, side, pInput, 0) < 0) {
                TaLogic_GetMinimumTask_RunMission_0011A4D0(arg0 + index * 8, side, pInput, 0);
            }
            found = 1;
        }
        break;
    case 10:
        if (TaLogic_GetMinimumTask_Summon_00119300(arg0[index * 8], side, (s32)pInput) < 0) {
            TaLogic003_InitRogicControl(arg0 + index * 8, 0);
            *(u8 *)((u8 *)pInput + 2) = 0xFF;
            found = 1;
            *(s32 *)((u8 *)pInput + 0xC) = 0;
        } else {
            TaLogic_InitRogicControl(arg0 + index * 8, 0);
            found = 1;
        }
        break;
    case 11:
        TaLogic_GetMinimumTask_TrapMission_0011B0E0(arg0 + index * 8, side, pInput, 0);
        found = 1;
        break;
    case 6:
    case 15:
    case 16:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_MoveMission_0011B680(arg0 + index * 8, side, pInput, 0, 0);
            found = 1;
        }
        break;
    case 9:
        TaLogic_GetMinimumTask_EncMission(arg0 + index * 8, side, pInput, 0, 0, TaLogic_GetWarnHideLvl_0011AA10(side), 3, 1);
        found = 1;
        break;
    case 14:
        TaLogic_GetMinimumTask_DoNone(arg0 + index * 8, side, pInput);
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

/* Gives a unit of this duelist its order for this turn (attack, run, move, summon, guard). */
s32 TaLogic_CommandUnit_00118330(void *pCtl) {
    u16 key;
    s32 controller;
    s32 kind;

    key = *(u16 *)pCtl;
    controller = Ta_IsUnitControl((s32)key >> 8, key & 0xFF);

    key = *(u16 *)pCtl;
    if (SzDuel_GetUnit((s32)key >> 8, key & 0xFF) != 0) {
        key = *(u16 *)pCtl;
        if (SzDuel_GetUnitStatus((s32)key >> 8, key & 0xFF, 0) == 0) {
            key = *(u16 *)pCtl;
            if (key != 0xFFFF) {
                if ((key & 0xFF) == 0) {
                    if (*(s32 *)((u8 *)pCtl + 8) == -1) {
                        if (TaLogic_IsAttackedNow((s32)key >> 8, key & 0xFF, 0) == 1) {
                            if (SzDuel_InqHandPhase((s32)(*(u16 *)pCtl) >> 8) == 1) {
                                *(u16 *)((u8 *)pCtl + 4) = 0x50A;
                            } else {
                                *(u16 *)((u8 *)pCtl + 4) = 0x5FF;
                            }
                        } else {
                            if (SzDuel_InqHandPhase((s32)(*(u16 *)pCtl) >> 8) == 1) {
                                *(u16 *)((u8 *)pCtl + 4) = 0xA05;
                            } else {
                                *(u16 *)((u8 *)pCtl + 4) = 0xFF05;
                            }
                        }
                    }
                } else {
                    kind = SzDuel_GetUnitKind((s32)key >> 8, key & 0xFF) >> 5;
                    switch (kind) {
                    case 0:
                        TaLogic_CommandBtlUnit_001188F0(pCtl, 1);
                        break;
                    case 3:
                        TaLogic_CommandTrapUnit_00118F50(pCtl);
                        break;
                    case 4:
                    case 5:
                        *(u16 *)((u8 *)pCtl + 4) = 0x5FF;
                        break;
                    case 2:
                        TaLogic_CommandEncUnit(pCtl, 3, 0, TaLogic_GetWarnHideLvl_0011AA10(controller) & 0xFF);
                        break;
                    default:
                        *(u16 *)((u8 *)pCtl + 4) = 0x5FF;
                        break;
                    }
                }
                return 1;
            }
        }
    }
    return 0;
}

/* The next unit of side `nSide` to act: first one that can attack now, then the others by task. */
s32 TaLogic_GetNextActiveUnit_00118510(u16 *pCtl, s32 nSide, s32 pInput) {
    s32 i;
    s32 pos;
    s32 ret;
    s32 idx;
    u16 list[22];

    for (i = 0; i < 22; i++) {
        list[i] = 0xFFFF;
    }
    TaLogic_GetUnitCtlLst(nSide, list, 0x1D, 1);
    ret = TaLogic_GetAtkUnitNow(nSide, list, pCtl);
    if (ret >= 0) {
        return ret;
    }
    for (i = 0; i < 22; i++) {
        list[i] = 0xFFFF;
    }
    TaLogic_GetUnitCtlLst(nSide, list, 0x1E, 1);
    for (i = 0; i < TaLogic_GetUnitCtlLstLen(list); i++) {
        if ((SzDuel_GetUnitKind(list[i] >> 8, list[i] & 0xFF) >> 5) == 3 &&
            TaLogic_IsUnitReadyMove(list[i]) == 1 && TaLogic_IsPickUp(list[i]) == 1) {
            return list[i];
        }
    }
    pos = nSide << 8;
    idx = TaLogic_GetActionUnitFromOwnerID(pCtl, pos);
    TaLogic_CommandUnit_00118330(pCtl + idx * 8);
    if (((pCtl[idx * 8 + 2] >> 8) & 0xFF) == 10) {
        if (SzDuel_InqHandPhase(nSide) == 1 && TaLogic_GetMinimumTask_Summon_00119300(pos, nSide, pInput) >= 0) {
            return pos | 0x10000;
        }
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_GetUnitStatus(nSide, 0, 0) == 0) {
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_InqHandPhase(nSide) == 1 && TaLogic_GetMinimumTask_Summon_00119300(pos, nSide, pInput) >= 0) {
        return pos | 0x10000;
    }
    for (i = 0; i < 22; i++) {
        list[i] = 0xFFFF;
    }
    TaLogic_GetUnitCtlLst(nSide, list, 0x1F, 1);
    for (i = 0; i < TaLogic_GetUnitCtlLstLen(list); i++) {
        if (TaLogic_IsUnitReadyMove(list[i]) == 1 && TaLogic_IsPickUp(list[i]) == 1) {
            return list[i];
        }
    }
    for (i = 0; i < 22; i++) {
        list[i] = 0xFFFF;
    }
    TaLogic_GetUnitCtlLst(nSide, list, 0x1F, 1);
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

/* Orders a fighting unit (task `pTask`): straight at its goal when `fGoalFirst` and the path is open, else the
   nearest enemy it can beat. */
void TaLogic_CommandBtlUnit_001188F0(void *pTask, s32 fGoalFirst) {
    extern s32 TaLogic_IsRootOpen();
    extern void TaLogic_InitIgnoreLst();
    extern s32 TaLogic003_GetNearUnit();
    Entry_001188F0 *entry = pTask;
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
        if (fGoalFirst != 0) {
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
        TaLogic003_CommandAtkLineUnit(pTask);
    }
}

/* TaLogic_GetNearUnit with this duelist's view and strength settings. */
void TaLogic003_GetNearUnit(s32 pTask, s32 pTree, s32 pVarInfo, s32 nX, s32 nZ, s32 eSide, s32 bDist, s32 WarnLvl, s32 nUnitLst, u16 wUnitNum, s32 wSize, s32 wNodeCount, u8 bChase, s32 wIgnoreLst) {
    TaLogic_GetNearUnit(pTask, pTree, pVarInfo, nX, nZ, eSide, bDist, WarnLvl,
                 nUnitLst, wUnitNum, wSize, wNodeCount, bChase,
                 0, 0x5DC, wIgnoreLst);
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

/* Orders a unit (task `pTask`) along this duelist's attack line. */
void TaLogic003_CommandAtkLineUnit(void *pTask) {
    State_00118BC0 *state = pTask;
    s32 new_type;
    s32 temp_a1;
    s32 locHi;
    s32 turnOwner;
    s32 emptyAtkLineStart;
    s32 loc;
    s32 emptyAtkLineEnd;
    u16 id;

    turnOwner = SzDuel_GetTurnOwner();
    id = state->id;
    loc = SzDuel_GetUnitLoc((s32) id >> 8, id & 0xFF);
    emptyAtkLineStart = TaLogic003_GetEmptyAtkLineStart(turnOwner);
    emptyAtkLineEnd = TaLogic003_GetEmptyAtkLineEnd(turnOwner);
    locHi = loc >> 8;
    switch (locHi) {
    case 0:
        if (loc == emptyAtkLineStart) {
            state->state = 0xFFF;
        } else {
            state->state = 0x6FF;
            state->data.word = (emptyAtkLineStart << 16) | state->data.low;
        }
        break;
    case 6:
        if (loc == emptyAtkLineEnd) {
            state->state = 0x10FF;
        } else {
            state->state = 0x6FF;
            state->data.word = (emptyAtkLineEnd << 16) | state->data.low;
        }
        break;
    default:
        temp_a1 = ((s32) state->state >> 8) & 0xFF;
        if ((temp_a1 != 0xF) && (temp_a1 != 0x10)) {
            new_type = (locHi < 4) ? 0xF : 0x10;
            state->state = (new_type << 8) | 0xFF;
            state->data.word = state->data.low | 0xFFFF0000;
        }
        break;
    }
}

/* Whether attack line `nLine` (0..3) of side `nSide` is free of enemy monsters. */
s32 TaLogic003_IsEmptyAtkLine(s32 nSide, s32 nLine) {
    s32 index;
    s32 row;
    s32 low;
    s32 high;
    s32 slot;

    switch ((u8)nLine) {
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
            if (nSide == Ta_IsUnitControl(high, low) &&
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

/* The start square of side `nSide`'s first free attack line, or -1. */
s32 TaLogic003_GetEmptyAtkLineStart(s32 nSide) {
    s32 i;

    i = 0;
    do {
        if (TaLogic003_IsEmptyAtkLine(nSide, (u8)i) != 0) {
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

/* The end square of side `nSide`'s first blocked attack line, or -1. */
s32 TaLogic003_GetEmptyAtkLineEnd(s32 nSide) {
    s32 i = 0;

    do {
        if (TaLogic003_IsEmptyAtkLine(nSide, (u8)i) == 0) {
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


/* Orders a trap card (task `pTask`): where to set it. */
void TaLogic_CommandTrapUnit_00118F50(void *pTask) {
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
    u16 *record = pTask;
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


/* The summon task for side `nSide`: which hand cards to play and where, into `pInput`; -1 when it plays none. */
s32 TaLogic_GetMinimumTask_Summon_00119300(s32 wUnit, s32 nSide, s32 pInput) {
    extern s32 TaLogic_GetUnitNum();
    Temp_00119300 temp;
    s32 color;
    s32 index;

    *(s16 *) (u8 *) pInput = (s16) wUnit;
    if (SzDuel_InqHandPhase(nSide) == 0) {
        return -1;
    }

    if (TaLogic_GetUnitNum(nSide, 0) == 5 && TaLogic_GetUnitNum(nSide, 1) == 5) {
        return -1;
    }

    if ((index = TaLogic_IsHandPlay_00119A40(nSide, &temp)) < 0) {
        return -1;
    } else {
        ((u8 *) pInput)[2] = 10;
        *(s32 *) ((u8 *) pInput + 0xC) = 0;
        color = SzDuel_GetUnitLoc(wUnit >> 8, wUnit & 0xFF);

        if (index == 0) {
            if (TaLogic_SetComboQue_0011A0D0(nSide, (u8 *) pInput, &temp) >= 0) {
                if (TaLogic_GetNearCard2(&temp, color & 0xFF, color >> 8,
                        nSide == 0 ? 1 : 0,
                        3, 0x1F, 2, 2, 0, TaLogic_GetWarnHideLvl_0011AA10(nSide)) < 0) {
                    if (SzDuel_GetUnitMonsterCount(nSide) >= 6) {
                        goto fallback;
                    }
                    index = TaLogic003_GetSummonPiece(nSide, index & 0xFF, &temp);
                    if (index < 0) {
                        return -1;
                    }
                    *(s16 *) ((u8 *) pInput + 4) = (s16) index;
                    return 1;
                }

                index = TaLogic003_GetSummonPiece(nSide, index & 0xFF, &temp);
                if (index < 0) {
                    return -1;
                }
                *(s16 *) ((u8 *) pInput + 4) = (s16) index;
                return 1;
            }
        } else {
            TaLogic_GetNearCard2(&temp, color & 0xFF, color >> 8,
                    nSide == 0 ? 1 : 0,
                    3, 0x1F, 2, 2, 0, TaLogic_GetWarnHideLvl_0011AA10(nSide));
        }

    fallback:
        if (TaLogic003_GetSpellPlay(nSide, (u8 *) pInput, &temp, temp.value) < 0) {
            return -1;
        }
        index = TaLogic003_GetSummonPiece(nSide, index & 0xFF, &temp);
        if (index < 0) {
            return -1;
        }
        *(s16 *) ((u8 *) pInput + 4) = (s16) index;
        return 1;
    }
}

typedef struct Nibbles_00119520 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_00119520;


/* The start square of side `player`'s first free attack line, or -1. */
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

/* The square side `nSide` summons a card of kind `sKind` to. */
s32 TaLogic003_GetSummonPiece(s32 nSide, s32 sKind, void *pInput) {
    extern s32 TaLogic_GetSommonPiecePreference_0011A4C0();
    extern s32 TaLogic_IsUnitWin4();
    extern s32 TaLogic_GetInvadeRoot2();
    extern s32 TaLogic_GetRoot2(s32, s32, s32, s32, s32, s32, u16, u8);
    Nibbles_00119520 path[12];
    s32 init;
    Nibbles_00119520 *p;

    if (pInput == NULL) {
        return -1;
    }
    p = path;
    init = 0;
    do {
        p->low = p->high = 15;
        init++;
        p++;
    } while (init < 12);
    if ((u8)(*((u8 *)pInput + 0x3E) >> 5) == 0) {
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

        position = SzDuel_GetUnitLoc(nSide, 0);
        target = TaLogic_GetNearCard2(pInput, position & 0xFF, position >> 8,
                             nSide == 0 ? 1 : 0, 3, 31, 2, 2, 0,
                             TaLogic_GetWarnHideLvl_0011AA10(nSide));
        if (target >= 0) {
            best_cost = 255;
            best_candidate = 65535;
            position = SzDuel_GetUnitLoc(target >> 8, target & 0xFF);
            i = 0;
            ref_y = position >> 8;
            ref_x = position & 0xFF;
            do {
                if ((candidate = TaLogic_GetSommonPiecePreference_0011A4C0(nSide, i)) >= 0) {
                    x = candidate & 0xFF;
                    y = candidate >> 8;
                    if (SzDuel_GetField(x, y) != 8 &&
                        (SzDuel_GetField(x, y) != 9 ||
                         Ta_IsVirus_Chk3(pInput, x, y) != 1) &&
                        SzDuel_GetMapUnit(x, y) == 0) {
                        if (TaLogic_IsUnitWin4(pInput, target, TaLogic_GetWarnHideLvl_0011AA10(nSide),
                                          ref_x, ref_y, 0) > 0) {
                            cost = TaLogic_GetInvadeRoot2(pInput, path, x, y,
                                                ref_x, ref_y, target, 0, 3,
                                                (u16)TaLogic_GetWarnHideLvl_0011AA10(nSide));
                        } else {
                            cost = TaLogic_GetRoot2((s32)pInput, (s32)path, x, y,
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

            direction = direction_00119520(nSide);
            best_cost2 = 14;
            best_candidate2 = -1;
            i2 = 0;
            ref_y2 = direction >> 8;
            ref_x2 = direction & 0xFF;
            do {
                if ((candidate2 = TaLogic_GetSommonPiecePreference_0011A4C0(nSide, i2)) >= 0) {
                    x2 = candidate2 & 0xFF;
                    y2 = candidate2 >> 8;
                    if (SzDuel_GetField(x2, y2) != 8 &&
                        (SzDuel_GetField(x2, y2) != 9 ||
                         Ta_IsVirus_Chk3(pInput, x2, y2) != 1) &&
                        SzDuel_GetMapUnitID(x2, y2) < 0) {
                        occupied = SzDuel_GetMapUnitID(x2, y2);
                        if (occupied < 0) {
                            occupied = 65535;
                        }
                        cost2 = TaLogic_GetRoot2((s32)pInput, (s32)path, x2, y2,
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
            if ((candidate3 = TaLogic_GetSommonPiecePreference_0011A4C0(nSide, i3)) >= 0) {
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

/* The first blocked attack line of side `nSide`, or -1. */
static inline s32 find_slot_00119A40(s32 nSide) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (TaLogic003_IsEmptyAtkLine(nSide, (u8)i) == 0) {
            return i;
        }
    }
    return -1;
}

/* Whether side `nSide` should play from its hand this turn (and what, into `pInput`). */
s32 TaLogic_IsHandPlay_00119A40(s32 nSide, void *pInput) {
    s32 cards[8];
    u8 scratch[32];
    u8 type0;
    u8 type1;
    s32 i;
    s32 result;

    extern s32 TaLogic_GetUnitNum();

    type0 = TaLogic_GetUnitNum(nSide, 0);
    type1 = TaLogic_GetUnitNum(nSide, 1);
    if (pInput == NULL) {
        return -1;
    }

    TaHand_GetNextHand(nSide, cards);
    if (type0 == 5) {
        if (TaLogic003_GetSpellPlay(nSide, scratch, pInput, 999) >= 0) {
            return 1;
        } else {
            return -1;
        }
    } else if (type1 == 5) {
        for (i = 0; i < TaHand_GetNextHandNum(nSide); i++) {
            if ((TaHand_GetCardKind(cards[i]) >> 5) == 0 &&
                TaHand_IsCardSummon2(nSide, cards[i]) == 1) {
                SzDuel_InitCardInfo(pInput, cards[i]);
                return 0;
            }
        }
        return -1;
    } else {
        result = TaLogic003_IsSpellPlay(nSide, scratch, (s32)pInput);
        if (result >= 0) {
            return TaLogic003_GetSpellPlay(nSide, scratch, pInput, result);
        }

        i = find_slot_00119A40(nSide);

        if (i >= 0) {
            for (i = 0; i < TaHand_GetNextHandNum(nSide); i++) {
                if ((TaHand_GetCardKind(cards[i]) >> 5) == 0 &&
                    TaHand_IsCardSummon2(nSide, cards[i]) == 1) {
                    return 0;
                }
            }
            return TaLogic003_GetSpellPlay(nSide, scratch, pInput, 999);
        } else {
            for (i = 0; i < TaHand_GetNextHandNum(nSide); i++) {
                if ((TaHand_GetCardKind(cards[i]) >> 5) == 0 &&
                    TaHand_IsCardSummon2(nSide, cards[i]) == 1) {
                    SzDuel_InitCardInfo(pInput, cards[i]);
                    return 0;
                }
            }
            result = TaLogic003_GetSpellPlay(nSide, scratch, pInput, 999);
            if (result >= 0) {
                return result;
            }
            return -1;
        }
    }
}

/* Whether side `nSide` plays a magic or ritual card from its hand now (its slot into `bCombo`, the card into
   `pCardInfo`). */
s32 TaLogic003_GetSpellPlay(s32 nSide, u8 *bCombo, void *pCardInfo, s32 nMode) {
    s32 buf[8];
    s32 i;

    TaHand_GetNextHand(nSide, buf);
    if (pCardInfo == NULL) {
        return -1;
    }
    for (i = 0; i < 5; i++) {
        bCombo[i + 6] = 0xFF;
    }
    for (i = 0; i < TaHand_GetNextHandNum(nSide); i++) {
        if (nMode == buf[i] && nMode != 999) {
            bCombo[6] = i;
            SzDuel_InitCardInfo(pCardInfo, buf[i]);
            return 1;
        }
    }
    for (i = 0; i < TaHand_GetNextHandNum(nSide); i++) {
        if ((TaHand_GetCardKind(buf[i]) >> 5) != 0 && (TaHand_GetCardKind(buf[i]) >> 5) != 2) {
            bCombo[6] = i;
            SzDuel_InitCardInfo(pCardInfo, buf[i]);
            return 1;
        }
    }
    for (i = 0; i < TaHand_GetNextHandNum(nSide); i++) {
        if ((TaHand_GetCardKind(buf[i]) >> 5) != 0) {
            bCombo[6] = i;
            SzDuel_InitCardInfo(pCardInfo, buf[i]);
            return 1;
        }
    }
    return -1;
}

typedef struct Info_00119F30 {
    u8 pad0[6];
    u8 slots[5];
} Info_00119F30;

/* Whether side `nSide` plays a magic card now (against the opponent's strongest unit); its card into `pCardInfo`. */
s32 TaLogic003_IsSpellPlay(s32 nSide, void *bCombo, s32 pCardInfo) {
    Info_00119F30 *info = bCombo;
    u16 cards[22];
    s32 ids[8];
    s32 i;
    s32 card;
    s32 type;

    for (i = 0; i < 22; i++) {
        cards[i] = 0xFFFF;
    }
    TaUtil_GetUnitLst(nSide, 2, cards);
    TaHand_GetNextHand(nSide, ids);
    if (pCardInfo == 0) {
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
            for (i = 0; i < TaHand_GetNextHandNum(nSide); i++) {
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


/* Fills hand combination `bCombo` for side `nSide`: the best fusion or equip chain, its card into `pCardInfo`. */
s32 TaLogic_SetComboQue_0011A0D0(s32 nSide, u8 *bCombo, void *pCardInfo) {
    u16 *nodes[8];
    s32 entries[7];
    s16 a;
    s16 b;
    s32 i;
    s32 card;
    s32 value;
    s32 best;
    extern s32 TaLogic_GetEnchantQue2();

    if (pCardInfo == NULL) {
        return -1;
    } else {
        s32 top;
        s32 *entry;
        u16 **node;

        TaHand_GetNextHand(nSide, entries);
        best = -1;
        top = -1;
        i = 0;
        if (i < TaHand_GetNextHandNum(nSide)) {
            entry = entries;
            node = nodes;
            do {
                b = 0;
                a = 0;
                card = *entry;
                *node = NULL;
                if ((TaHand_GetCardKind(card) >> 5) == 0) {
                    *node = TaLogic_GetFusionTree(nSide, (struct TreeTag *)*node, i & 0xFF, card & 0xFFFF, 0, (u16 *)&a, (u16 *)&b);
                    *node = TaLogic_GetFusionRes(*node);
                    if (Taku_Get_WinCount() < 3) {
                        value = TaLogic_GetEnchantQue2(nSide, *node, 0, 0);
                    } else {
                        value = TaLogic_GetEnchantQue(nSide, *node, 0, 0);
                    }
                    if (TaHand_IsCardSummon2(nSide, card) == 1) {
                        if (best < value) {
                            TaLogic_ConvEmptyCombo_0011A2F0(nSide, *node, entries);
                            TaLogic_CopyArray((u8 *)*node + 2, bCombo + 6);
                            SzDuel_InitCardInfo(pCardInfo, **node);
                            ((Sprite_0011A0D0 *)pCardInfo)->x = (value >> 16) - (((Sprite_0011A0D0 *)pCardInfo)->info->x & 0x1FFF);
                            ((Sprite_0011A0D0 *)pCardInfo)->y = (value & 0xFFFF) - (((Sprite_0011A0D0 *)pCardInfo)->info->y & 0x1FFF);
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
            } while (i < TaHand_GetNextHandNum(nSide));
        }
        return top;
    }
}

typedef struct {
    u16 id;
    u8 values[5];
} Info_0011A2F0;

/* Fills an empty combination: the hand card side `nSide` can summon with the best attack plus defence. */
void TaLogic_ConvEmptyCombo_0011A2F0(s32 nSide, void *pCardInfo, s32 *pResult) {
    Info_0011A2F0 *info = pCardInfo;
    u8 buf[5];
    s32 count;
    s32 i;
    s32 card;
    u8 level;
    u32 cost;
    extern u32 TaHand_GetCardAPDP();

    if (info != NULL) {
        level = TaHand_GetCardSummonCost2(info->id, nSide);
        for (i = 0; i < 5; i++) {
            buf[i] = 0xFF;
        }
        for (i = 0, count = 0; i < TaHand_GetNextHandNum(nSide); i++) {
            if ((u8)TaLogic_IsUseHandInCombo(i, info->values) == 0) {
                buf[count++] = i;
            }
        }
        if (count != 0) {
            for (i = 0; i < (u8)TaLogic_GetArrayLength(buf); i++) {
                card = pResult[buf[i]];
                if (card != 0x3E7 && level >= TaHand_GetCardSummonCost2(card, nSide)) {
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

/* Ta_GetSommonPiecePreference for this duelist. */
s32 TaLogic_GetSommonPiecePreference_0011A4C0(s32 nSide, u32 nPr) {
    return Ta_GetSommonPiecePreference(nSide, nPr);
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


/* The task of a unit running from danger (task `pTask`): the safest square in reach, into `pInput` (`fFirst` = 1
   for the unit's first-choice task). */
s32 TaLogic_GetMinimumTask_RunMission_0011A4D0(u16 *pTask, s32 nSide, void *pInput, u8 fFirst) {
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
    Output_0011A4D0 *out = pInput;

    position = SzDuel_GetUnitLoc(*pTask >> 8, *pTask & 0xFF);
    i = 0;
    do {
        cells[i].low = cells[i].high = 15;
        i++;
    } while (i < 12);

    {
        u16 value = (u16)TaLogic_GetWarnHideLvl_0011AA10(nSide);
        originalX = position & 0xFF;
        originalY = position >> 8;
        if (TaLogic_GetUnitWarning(originalX, originalY, *pTask, 3, value, 0) == 0) {
            out->id = *pTask;
            out->action = 6;
            out->position = position;
            out->mode = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, out->position, 1, 0);
            out->value = TaLogic_IsOpenUnit_0011C140(*pTask >> 8, *pTask & 0xFF, (u32 *)pTask);
            TaLogic003_InitRogicControl(pTask, fFirst);
            return 0;
        } else {
            result = GetMoveRev(SzDuel_GetUnit(*pTask >> 8, *pTask & 0xFF), originalX, originalY);
            if (result == 0) {
                out->id = *pTask;
                out->action = 6;
                out->position = position;
                out->mode = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, out->position, 1, 0);
                out->value = TaLogic_IsOpenUnit_0011C140(*pTask >> 8, *pTask & 0xFF, (u32 *)pTask);
                TaLogic003_InitRogicControl(pTask, fFirst);
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
                if ((*pTask & 0xFF) == 0) {
                    flag = TaLogic_IsAttackedNow(*pTask >> 8, *pTask & 0xFF, 0) & 0xFF;
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
                            if (TaLogic_IsRunPassRoot(*pTask >> 8, *pTask & 0xFF, originalX, originalY, x, y, pTask, flag) == 1 &&
                                (TaLogic_IsAttackedNow2(*pTask >> 8, *pTask & 0xFF, x, y, 0) == 0 || (u8)*pTask == 0)) {
                                value = (u16)TaLogic_GetWarnHideLvl_0011AA10(nSide);
                                score = TaLogic_GetUnitWarning(x, y, *pTask, 3, value, 0);
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
                    out->id = *pTask;
                    out->action = 6;
                    out->position = bestPosition;
                    if (bestPosition == position) {
                        out->mode = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, out->position, 1, 0);
                    } else {
                        out->mode = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, out->position, 1, 0);
                    }
                    out->value = TaLogic_IsOpenUnit_0011C140(*pTask >> 8, *pTask & 0xFF, (u32 *)pTask);
                } else {
                    out->id = *pTask;
                    out->action = 6;
                    out->position = position;
                    out->mode = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, out->position, 1, 0);
                    out->value = TaLogic_IsOpenUnit_0011C140(*pTask >> 8, *pTask & 0xFF, (u32 *)pTask);
                }
                TaLogic003_InitRogicControl(pTask, fFirst);
            }
        }
    }
    return 0;
}

/* How careful this duelist is about hidden cards (by its life points and monster count). */
s32 TaLogic_GetWarnHideLvl_0011AA10(s32 nSide) {
    if (SzDuel_GetLP(nSide) > 0x5DC) {
        if (SzDuel_GetUnitMonsterCount(nSide) >= 3) {
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


/* The task's target square: the second half-word when the second argument is 1, else the first. */
static inline u32 target_0011AA70(void *arg0, u8 which) {
    Source_0011AA70 *source = arg0;
    if (which == 1) {
        return (u16)(source->targets >> 16);
    }
    return *(u16 *)&source->targets;
}

/* This duelist's caution about hidden cards (an inline copy of its GetWarnHideLvl: by life points and monster
   count). */
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

/* The task of a unit attacking (task `pTask`): its path to the goal, into `pInput`; -1 when it has none (`fFirst`
   = 1 for the unit's first-choice task). */
s32 TaLogic_GetMinimumTask_AtkMission_0011AA70(void *pTask, s32 nSide, void *pInput, u8 fFirst) {
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
    Source_0011AA70 *source = pTask;
    Output_0011AA70 *output = pInput;

    targetXWord = target_0011AA70(pTask, fFirst);
    targetYWord = target_0011AA70(pTask, fFirst);
    if (SzDuel_GetUnit(targetYWord >> 8, targetXWord & 0xFF) == 0) {
        TaLogic_InitRogicControl(pTask, 1);
        return -1;
    }

    flag = TaLogic_IsOpenUnit_0011C140(source->position >> 8, source->position & 0xFF, pTask);
    sourceTarget = SzDuel_GetUnitLoc(source->position >> 8, source->position & 0xFF);
    targetXWord = target_0011AA70(pTask, fFirst);
    targetYWord = target_0011AA70(pTask, fFirst);
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
        cost = TaLogic_GetUnitWarning(sourceX, sourceY, nSide, 3, 1,
                            (u8)penalty_0011AA70(nSide));
        if (cost >= SzDuel_GetUnitAP(source->position >> 8, source->position & 0xFF, 0)) {
            output->value = TaLogic_IsDefStyleUnit(source->position >> 8, source->position & 0xFF,
                                        output->target, 1, 0);
        } else {
            output->value = TaLogic_IsDefStyleUnit(source->position >> 8, source->position & 0xFF,
                                        output->target, 0, 0);
        }
        TaLogic003_InitRogicControl(pTask, fFirst);
    } else {
        s32 targetY;
        s32 targetX;
        Position_0011AA70 *current;
        s32 i;
        s32 bestCost;
        s32 selected;
        s32 penalty;
        u16 position;

        penalty = penalty_0011AA70(nSide);
        position = source->position;
        TaLogic_GetInvadeRoot(position >> 8, position & 0xFF, positions,
                      sourceX, sourceY, targetX = otherTarget & 0xFF,
                      targetY = otherTarget >> 8,
                      target_0011AA70(pTask, fFirst), 0, 30, (u16)penalty);
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
                    s32 penalty = penalty_0011AA70(nSide);
                    current = &positions[i];
                    cost = TaLogic_GetUnitWarning(current->x, current->y, nSide, 3, 1,
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
            TaLogic_InitRogicControl(pTask, fFirst);
            return 0;
        }
        if (selected != 0xFF) {
            output->position = source->position;
            output->mode = 6;
            output->target = (positions[selected].y << 8) | positions[selected].x;
            output->flag = selectedFlag;
            output->value = TaLogic_IsDefStyleUnit(source->position >> 8, source->position & 0xFF,
                                        output->target, 0, 0);
            TaLogic003_InitRogicControl(pTask, fFirst);
            return 0;
        } else {
            output->position = source->position;
            output->mode = 6;
            output->target = sourceTarget;
            output->flag = selectedFlag;
            output->value = TaLogic_IsDefStyleUnit(source->position >> 8, source->position & 0xFF,
                                        output->target, 0, 0);
            TaLogic003_InitRogicControl(pTask, fFirst);
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


/* The task's target square: the second half-word when the second argument is 1, else the first. */
static inline u32 destination_0011B0E0(Input_0011B0E0 *input, u8 mode) {
    return mode == 1 ? (u32)(u16)(input->destination >> 16) :
                      (u32)*(u16 *)&input->destination;
}

/* This duelist's caution about hidden cards (an inline copy of its GetWarnHideLvl: by life points and monster
   count). */
static inline u16 flags_0011B0E0(s32 card) {
    if (SzDuel_GetLP(card) > 0x5DC) {
        if (SzDuel_GetUnitMonsterCount(card) >= 3) {
            return 0;
        }
        return 0;
    }
    return 0;
}

/* Whether the first square is nearer to (x, y) than the second. */
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

/* Sets a move task (action 6) to the given square, and whether the unit should stay in defence there. */
static inline void fallback_0011B0E0(Input_0011B0E0 *input, Output_0011B0E0 *output, s32 position) {
    output->position = input->position;
    output->action = 6;
    output->destination = position;
    output->result = TaLogic_IsDefStyleUnit(input->position >> 8, input->position & 0xFF,
                                 output->destination, 1, 0);
}

/* The task of setting a trap (task `pTask`), into `pInput`. */
s32 TaLogic_GetMinimumTask_TrapMission_0011B0E0(void *pTask, s32 nSide, void *pInput, u8 fFirst) {
    extern void TaLogic_GetInvadeRoot();
    Position_0011B0E0 positions[12];
    Position_0011B0E0 *position;
    Input_0011B0E0 *input = pTask;
    Output_0011B0E0 *output = pInput;
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

    if (SzDuel_GetUnit(destination_0011B0E0(input, fFirst) >> 8,
                     destination_0011B0E0(input, fFirst) & 0xFF) == 0) {
        TaLogic_InitRogicControl(input, 1);
        return -1;
    }
    origin = SzDuel_GetUnitLoc(input->position >> 8, input->position & 0xFF);
    target = SzDuel_GetUnitLoc(destination_0011B0E0(input, fFirst) >> 8,
                          destination_0011B0E0(input, fFirst) & 0xFF);
    if (destination_0011B0E0(input, fFirst) == 0xFFFF) {
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
        u16 flags = flags_0011B0E0(nSide);
        targetY = target & 0xFF;
        target >>= 8;
        TaLogic_GetInvadeRoot(input->position >> 8, input->position & 0xFF, positions,
                     originY, originX, targetY, target,
                     destination_0011B0E0(input, fFirst), 0, 30, flags);
    }
    count = TaLogic_GetMinGoalCount((u8 *)positions);
    best = 0xFF;
    if (count > 0) {
        bestScore = 0;
        for (i = 0; i < count; i++, position++) {
            if (SzDuel_GetMapUnit(position->y, position->x) == 0) {
                s32 score = TaLogic_GetUnitWarning(position->y, position->x, nSide,
                                         3, 1, (u8)flags_0011B0E0(nSide));
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

/* This duelist's caution about hidden cards (an inline copy of its GetWarnHideLvl: by life points and monster
   count). */
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

/* The task of a unit moving to its goal (task `pTask`), into `pInput` (`fFirst` = 1 for the unit's first-choice
   task). */
s32 TaLogic_GetMinimumTask_MoveMission_0011B680(u32 *pTask, s32 nSide, u16 *pInput, u8 fFirst, u8 nKind) {
    extern s32 TaLogic_IsDefStyleUnit(s32, s32, s32, u8, s32);
    extern void TaLogic_GetRoot(s32, s32, void *, s32, s32, s32, s32, s32, u8);
    Position_0011B680 positions[12];
    s32 y;
    s32 bestScore;
    s32 mode;
    s32 current;
    s32 command;

    current = SzDuel_GetUnitLoc(((Input_0011B680 *)pTask)->position >> 8, ((Input_0011B680 *)pTask)->position & 0xFF);
    mode = fFirst;
    if (target_0011B680((Input_0011B680 *)pTask, mode) == 0xFFFF && current == target_0011B680((Input_0011B680 *)pTask, mode)) {
        pInput[0] = ((Input_0011B680 *)pTask)->position;
        ((Output_0011B680 *)pInput)->action = 6;
        pInput[2] = current;
        ((Output_0011B680 *)pInput)->state = TaLogic_IsDefStyleUnit(((Input_0011B680 *)pTask)->position >> 8, ((Input_0011B680 *)pTask)->position & 0xFF,
            pInput[2], nKind, 0);
        ((Output_0011B680 *)pInput)->value = TaLogic_IsOpenUnit_0011C140(((Input_0011B680 *)pTask)->position >> 8, ((Input_0011B680 *)pTask)->position & 0xFF, pTask);
        TaLogic003_InitRogicControl(pTask, fFirst);
        return 0;
    } else {
        command = (((Input_0011B680 *)pTask)->command >> 8) & 0xFF;
        if (command == 15) {
            s32 x = current & 0xFF;
            s32 target;

            y = current >> 8;
            pInput[0] = ((Input_0011B680 *)pTask)->position;
            ((Output_0011B680 *)pInput)->action = 6;
            target = x | (GetCap(7, y +
                (GetMoveRev(SzDuel_GetUnit(((Input_0011B680 *)pTask)->position >> 8, ((Input_0011B680 *)pTask)->position & 0xFF), x, y) & 15)) << 8);
            pInput[2] = target;
            target = SzDuel_GetMapUnitID(target_0011B680((Input_0011B680 *)pTask, mode) & 0xFF,
                target_0011B680((Input_0011B680 *)pTask, mode) >> 8);
            if (target < 0) {
                target = 0xFFFF;
            }
            TaLogic_GetRoot(((Input_0011B680 *)pTask)->position >> 8, ((Input_0011B680 *)pTask)->position & 0xFF, positions, x, y,
                pInput[2] & 0xFF, pInput[2] >> 8, (u16)target, 2);
            if (TaLogic_GetMinGoalCount((u8 *)positions) == 0) {
                pInput[2] = current;
            }
            ((Output_0011B680 *)pInput)->state = TaLogic_IsDefStyleUnit(((Input_0011B680 *)pTask)->position >> 8, ((Input_0011B680 *)pTask)->position & 0xFF,
                pInput[2], nKind, 0);
            ((Output_0011B680 *)pInput)->value = TaLogic_IsOpenUnit_0011C140(((Input_0011B680 *)pTask)->position >> 8, ((Input_0011B680 *)pTask)->position & 0xFF, pTask);
            TaLogic003_InitRogicControl(pTask, fFirst);
            return 0;
        } else {
            if (command == 16) {
                s32 y2;
                s32 x = current & 0xFF;
                s32 target;

                y2 = current >> 8;
                pInput[0] = ((Input_0011B680 *)pTask)->position;
                ((Output_0011B680 *)pInput)->action = 6;
                target = x | (GetCap(0, y2 -
                    (GetMoveRev(SzDuel_GetUnit(((Input_0011B680 *)pTask)->position >> 8, ((Input_0011B680 *)pTask)->position & 0xFF), x, y2) & 15)) << 8);
                pInput[2] = target;
                target = SzDuel_GetMapUnitID(target_0011B680((Input_0011B680 *)pTask, mode) & 0xFF,
                    target_0011B680((Input_0011B680 *)pTask, mode) >> 8);
                if (target < 0) {
                    target = 0xFFFF;
                }
                TaLogic_GetRoot(((Input_0011B680 *)pTask)->position >> 8, ((Input_0011B680 *)pTask)->position & 0xFF, positions, x, y2,
                    pInput[2] & 0xFF, pInput[2] >> 8, (u16)target, 2);
                if (TaLogic_GetMinGoalCount((u8 *)positions) == 0) {
                    pInput[2] = current;
                }
                ((Output_0011B680 *)pInput)->state = TaLogic_IsDefStyleUnit(((Input_0011B680 *)pTask)->position >> 8, ((Input_0011B680 *)pTask)->position & 0xFF,
                    pInput[2], nKind, 0);
                ((Output_0011B680 *)pInput)->value = TaLogic_IsOpenUnit_0011C140(((Input_0011B680 *)pTask)->position >> 8, ((Input_0011B680 *)pTask)->position & 0xFF, pTask);
                TaLogic003_InitRogicControl(pTask, fFirst);
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
                target = SzDuel_GetMapUnitID(target_0011B680((Input_0011B680 *)pTask, mode) & 0xFF,
                    target_0011B680((Input_0011B680 *)pTask, mode) >> 8);
                if (target < 0) {
                    target = 0xFFFF;
                }
                TaLogic_GetRoot(((Input_0011B680 *)pTask)->position >> 8, ((Input_0011B680 *)pTask)->position & 0xFF, positions,
                    current & 0xFF, current >> 8, target_0011B680((Input_0011B680 *)pTask, mode) & 0xFF,
                    target_0011B680((Input_0011B680 *)pTask, mode) >> 8, (u16)target, 7);
                count = TaLogic_GetMinGoalCount((u8 *)positions);
                if (count > 0) {
                    best = 0xFF;
                    bestScore = 0xFFFF;
                    for (i = 0; i < count; i++, p++) {
                        s32 score;
                        if (SzDuel_GetMapUnit(p->x, p->y) == 0) {
                            score = TaLogic_GetUnitWarning(p->x, p->y, nSide, 3, 1, (u8)option_0011B680(nSide));
                            if (score < bestScore) {
                                bestScore = score;
                                best = i;
                            } else if (score == bestScore) {
                                if (distance_0011B680(p, (Input_0011B680 *)pTask, mode) <
                                    distance_0011B680(&positions[best], (Input_0011B680 *)pTask, mode)) {
                                    bestScore = score;
                                    best = i;
                                }
                            }
                        }
                    }
} else {
                    pInput[0] = ((Input_0011B680 *)pTask)->position;
                    ((Output_0011B680 *)pInput)->action = 6;
                    pInput[2] = current;
                    ((Output_0011B680 *)pInput)->state = TaLogic_IsDefStyleUnit(((Input_0011B680 *)pTask)->position >> 8, ((Input_0011B680 *)pTask)->position & 0xFF,
                        pInput[2], nKind, 0);
                    ((Output_0011B680 *)pInput)->value = TaLogic_IsOpenUnit_0011C140(((Input_0011B680 *)pTask)->position >> 8, ((Input_0011B680 *)pTask)->position & 0xFF, pTask);
                    TaLogic003_InitRogicControl(pTask, fFirst);
                    return 0;
                }
                    if (best != 0xFF) {
                        pInput[0] = ((Input_0011B680 *)pTask)->position;
                        ((Output_0011B680 *)pInput)->action = 6;
                        pInput[2] = (positions[best].y << 8) | positions[best].x;
                        ((Output_0011B680 *)pInput)->state = TaLogic_IsDefStyleUnit(((Input_0011B680 *)pTask)->position >> 8, ((Input_0011B680 *)pTask)->position & 0xFF,
                            pInput[2], nKind, 0);
                        ((Output_0011B680 *)pInput)->value = TaLogic_IsOpenUnit_0011C140(((Input_0011B680 *)pTask)->position >> 8, ((Input_0011B680 *)pTask)->position & 0xFF, pTask);
                    } else {
                        pInput[0] = ((Input_0011B680 *)pTask)->position;
                        ((Output_0011B680 *)pInput)->action = 6;
                        pInput[2] = current;
                        ((Output_0011B680 *)pInput)->state = TaLogic_IsDefStyleUnit(((Input_0011B680 *)pTask)->position >> 8, ((Input_0011B680 *)pTask)->position & 0xFF,
                            pInput[2], nKind, 0);
                        ((Output_0011B680 *)pInput)->value = TaLogic_IsOpenUnit_0011C140(((Input_0011B680 *)pTask)->position >> 8, ((Input_0011B680 *)pTask)->position & 0xFF, pTask);
                    }
                    TaLogic003_InitRogicControl(pTask, fFirst);
                
            }
        }
    }
    return 0;
}

/* Whether this duelist opens (turns face up) unit (nSide, nID) now: 0 no, 1 or 2 by its kind. */
s32 TaLogic_IsOpenUnit_0011C140(s32 nSide, s32 nID, u32 *pInfo) {
    /* really takes (nSide, nID); the header says (void) */
    s32 SzDuel_GetUnitCardNo();
    u8 info[32];
    u32 *entry;

    if (SzDuel_GetUnitStatus(nSide, nID, 4) != 0) {
        return 0;
    }
    switch (SzDuel_GetUnitKind(nSide, nID) >> 5) {
    case 0:
        return 2;
    case 1:
        if (TaLogic_GetActionReaction(nSide, nID, 0, 0, 6, 0) == 5) {
            return 2;
        }
        entry = Ta_GetUnitEffect(nSide, nID, 0);
        if (entry == NULL) {
            return 2;
        }
        switch (*entry >> 8) {
        case 2:
            if ((u16)(pInfo[2] >> 16) == SzDuel_GetUnitLoc(nSide, nID)) {
                return 1;
            }
            break;
        case 0xD:
            return 1;
        default:
            if (SzDuel_GetUnitCardNo(nSide, nID) ==
                TaLogic003_IsSpellPlay(Ta_IsUnitControl(nSide, nID), info, SzDuel_GetUnit(nSide, nID))) {
                return 1;
            }
            break;
        }
        return 2;
    }
    return 2;
}

/* The larger of the two values. */
static inline s32 max_0011C2E0(s32 a, s32 b) {
    if (a < b) {
        return b;
    }
    return a;
}

/* Whether unit (nSide, nID) may open while moving from (nX, nZ) to the square next to it, (gX, gZ). */
s32 TaLogic003_IsOpenMoveUnit(s32 nSide, s32 nID, s32 nX, s32 nZ, s32 gX, s32 gZ) {
    s32 minY;
    s32 minX;

    minY = nZ < gZ ? nZ : gZ;
    gZ = max_0011C2E0(gZ, nZ);
    minX = nX < gX ? nX : gX;
    gX = max_0011C2E0(gX, nX);
    if ((gX - minX) + (gZ - minY) != 2) {
        return 0;
    }
    if (SzDuel_GetUnit(nSide, nID) == 0) {
        return 0;
    }
    if (SzDuel_GetUnitStatus(nSide, nID, 0) == 0) {
        if (CheckLandAgreement2(SzDuel_GetField(nX, nZ), nSide, nID) != 1) {
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

/* Clears a unit's task (`Is1st` on its first turn). */
void TaLogic003_InitRogicControl(void *pUnit, u8 Is1st) {
    Data_0011C3E0 *data = pUnit;

    if (Is1st < 2) {
        if (Is1st == 1) {
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

/* This computer duelist's controller (one entry of duelistControllers): the buttons it presses this frame. With an empty
   input queue it plans its next task and turns it into buttons, then plays the queue back one button per frame;
   after 600 frames it gives up the turn (0x20, then 0x800). */
s32 func_0011C430(s32 wCursorPos, void *pCtl) {
    Req_0011C430 req;
    Work_0011C430 *w;
    s32 i;
    s32 ret;

    w = pCtl;
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
        if (TaLogic_GetMinimumTask_00117E60(w, &req, wCursorPos) == 0) {
            return 0x800;
        }
        if (TaLogic_GetInputQueFromMinimumTask_b(w, &req, wCursorPos) < 0) {
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

/* This duelist's move: picks the next unit to act, gives it a task and turns that into input `pInput`; returns 1
   when it set one. */
s32 TaLogic_GetMinimumTask_0011C600(void *pCtl, void *pInput, s32 wCursorPos) {
    u16 *arg0 = pCtl;
    s32 side;
    s32 found;
    s32 result;
    s32 index;

    side = SzDuel_GetTurnOwner();
    found = 0;
    if ((result = TaLogic_GetNextActiveUnit_0011CD30(arg0, side, (s32)pInput)) < 0) {
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
            TaLogic_GetMinimumTask_RunMission_0011F540(arg0 + index * 8, side, pInput, 1);
            found = 1;
        }
        break;
    case 2:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            if (TaLogic_GetMinimumTask_AtkMission_0011FAE0(arg0 + index * 8, side, pInput, 1) < 0) {
                TaLogic004_InitRogicControl(arg0 + index * 8, 1);
                return 1;
            }
            found = 1;
        }
        break;
    case 10:
        if (TaLogic_GetMinimumTask_Summon_0011DFB0(arg0[index * 8], side, (s32)pInput) < 0) {
            TaLogic004_InitRogicControl(arg0 + index * 8, 1);
            *(u8 *)((u8 *)pInput + 2) = 0xFF;
            *(s32 *)((u8 *)pInput + 0xC) = 0;
        } else {
            TaLogic004_InitRogicControl(arg0 + index * 8, 1);
            found = 1;
        }
        break;
    case 11:
        TaLogic_GetMinimumTask_TrapMission_00120150(arg0 + index * 8, side, pInput, 1);
        found = 1;
        break;
    case 6:
    case 15:
    case 16:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_MoveMission_001206F0(arg0 + index * 8, side, pInput, 1, 0);
            found = 1;
        }
        break;
    case 3:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_MoveMission_001206F0(arg0 + index * 8, side, pInput, 1, 1);
            found = 1;
        }
        break;
    case 9:
        TaLogic_GetMinimumTask_EncMission(arg0 + index * 8, side, pInput, 1, 0, TaLogic_GetWarnHideLvl_0011FA80(side), 4, 1);
        found = 1;
        break;
    case 14:
        TaLogic_GetMinimumTask_DoNone(arg0 + index * 8, side, pInput);
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
            TaLogic_GetMinimumTask_RunMission_0011F540(arg0 + index * 8, side, pInput, 0);
            found = 1;
        }
        break;
    case 2:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            if (TaLogic_GetMinimumTask_AtkMission_0011FAE0(arg0 + index * 8, side, pInput, 0) < 0) {
                TaLogic_GetMinimumTask_RunMission_0011F540(arg0 + index * 8, side, pInput, 0);
            }
            found = 1;
        }
        break;
    case 10:
        if (TaLogic_GetMinimumTask_Summon_0011DFB0(arg0[index * 8], side, (s32)pInput) < 0) {
            TaLogic_InitRogicControl(arg0 + index * 8, 0);
            *(u8 *)((u8 *)pInput + 2) = 0xFF;
            found = 1;
            *(s32 *)((u8 *)pInput + 0xC) = 0;
        } else {
            TaLogic_InitRogicControl(arg0 + index * 8, 0);
            found = 1;
        }
        break;
    case 6:
    case 15:
    case 16:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_MoveMission_001206F0(arg0 + index * 8, side, pInput, 0, 0);
            found = 1;
        }
        break;
    case 3:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_MoveMission_001206F0(arg0 + index * 8, side, pInput, 0, 1);
            found = 1;
        }
        break;
    case 14:
        TaLogic_GetMinimumTask_DoNone(arg0 + index * 8, side, pInput);
        found = 1;
        break;
    case 9:
        TaLogic_GetMinimumTask_EncMission(arg0 + index * 8, side, pInput, 0, 0, TaLogic_GetWarnHideLvl_0011FA80(side), 4, 1);
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

/* Gives a unit of this duelist its order for this turn (attack, run, move, summon, guard). */
s32 TaLogic_CommandUnit_0011CB20(void *pCtl) {
    s32 result;

    result = Ta_IsUnitControl(*(u16 *)pCtl >> 8, *(u16 *)pCtl & 0xFF);
    if (SzDuel_GetUnit(*(u16 *)pCtl >> 8, *(u16 *)pCtl & 0xFF) != 0) {
        if (SzDuel_GetUnitStatus(*(u16 *)pCtl >> 8, *(u16 *)pCtl & 0xFF, 0) == 0) {
            if (*(u16 *)pCtl != 0xFFFF) {
                if ((*(u16 *)pCtl & 0xFF) == 0) {
                    if (*(s32 *)((u8 *)pCtl + 8) == -1) {
                        if (TaLogic_IsAttackedNow(*(u16 *)pCtl >> 8, *(u16 *)pCtl & 0xFF, 0) == 1) {
                            if (SzDuel_InqHandPhase(*(u16 *)pCtl >> 8) == 1) {
                                *(u16 *)((u8 *)pCtl + 4) = 0x50A;
                            } else {
                                *(u16 *)((u8 *)pCtl + 4) = 0x5FF;
                            }
                        } else {
                            if (SzDuel_InqHandPhase(*(u16 *)pCtl >> 8) == 1) {
                                *(u16 *)((u8 *)pCtl + 4) = 0xA05;
                            } else {
                                *(u16 *)((u8 *)pCtl + 4) = 0xFF05;
                            }
                        }
                    }
                } else {
                    s32 subtype = SzDuel_GetUnitKind(*(u16 *)pCtl >> 8, *(u16 *)pCtl & 0xFF) >> 5;

                    switch (subtype) {
                    case 0:
                        if (TaUtil_IsExMonster(*(u16 *)pCtl >> 8, *(u16 *)pCtl & 0xFF) == 1) {
                            TaLogic_CommandEfcMonster_0011D9B0(pCtl, 1);
                        } else {
                            TaLogic_CommandBtlUnit_0011D110(pCtl, 1);
                        }
                        break;
                    case 3:
                        TaLogic_CommandTrapUnit_0011DC00(pCtl);
                        break;
                    case 4:
                    case 5:
                        *(u16 *)((u8 *)pCtl + 4) = 0x5FF;
                        break;
                    case 2:
                        TaLogic_CommandEncUnit(pCtl, 4, 0, (u8)TaLogic_GetWarnHideLvl_0011FA80(result));
                        break;
                    default:
                        *(u16 *)((u8 *)pCtl + 4) = 0x5FF;
                        break;
                    }
                }
                return 1;
            }
        }
    }
    return 0;
}

/* The next unit of side `nSide` to act: first one that can attack now, then the others by task. */
s32 TaLogic_GetNextActiveUnit_0011CD30(u16 *pCtl, s32 nSide, s32 pInput) {
    s32 i;
    s32 pos;
    s32 ret;
    s32 idx;
    u16 list[22];

    for (i = 0; i < 22; i++) {
        list[i] = 0xFFFF;
    }
    TaLogic_GetUnitCtlLst(nSide, list, 0x1D, 1);
    ret = TaLogic_GetAtkUnitNow(nSide, list, pCtl);
    if (ret >= 0) {
        return ret;
    }
    for (i = 0; i < 22; i++) {
        list[i] = 0xFFFF;
    }
    TaLogic_GetUnitCtlLst(nSide, list, 0x1E, 1);
    for (i = 0; i < TaLogic_GetUnitCtlLstLen(list); i++) {
        if ((SzDuel_GetUnitKind(list[i] >> 8, list[i] & 0xFF) >> 5) == 3 &&
            TaLogic_IsUnitReadyMove(list[i]) == 1 && TaLogic_IsPickUp(list[i]) == 1) {
            return list[i];
        }
    }
    pos = nSide << 8;
    idx = TaLogic_GetActionUnitFromOwnerID(pCtl, pos);
    TaLogic_CommandUnit_0011CB20(pCtl + idx * 8);
    if (((pCtl[idx * 8 + 2] >> 8) & 0xFF) == 10) {
        if (SzDuel_InqHandPhase(nSide) == 1 && TaLogic_GetMinimumTask_Summon_0011DFB0(pos, nSide, pInput) >= 0) {
            return pos | 0x10000;
        }
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_GetUnitStatus(nSide, 0, 0) == 0) {
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_InqHandPhase(nSide) == 1 && TaLogic_GetMinimumTask_Summon_0011DFB0(pos, nSide, pInput) >= 0) {
        return pos | 0x10000;
    }
    for (i = 0; i < 22; i++) {
        list[i] = 0xFFFF;
    }
    TaLogic_GetUnitCtlLst(nSide, list, 0x1F, 1);
    for (i = 0; i < TaLogic_GetUnitCtlLstLen(list); i++) {
        if (TaLogic_IsUnitReadyMove(list[i]) == 1 && TaLogic_IsPickUp(list[i]) == 1) {
            return list[i];
        }
    }
    for (i = 0; i < 22; i++) {
        list[i] = 0xFFFF;
    }
    TaLogic_GetUnitCtlLst(nSide, list, 0x1F, 1);
    for (i = 0; i < TaLogic_GetUnitCtlLstLen(list); i++) {
        if (SzDuel_GetUnitStatus(list[i] >> 8, list[i] & 0xFF, 0) == 0 && TaLogic_IsPickUp(list[i]) == 1) {
            return list[i];
        }
    }
    return -1;
}

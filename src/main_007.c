#include "common.h"

s32 func_0016B0F0_b(); /* TaLogic021_IsUseBlackHole, which this file calls without its argument */

/* Whether side `nSide` plays a magic or ritual card from its hand now (its slot into `bCombo`, the card into
   `pCardInfo`). */
s32 TaLogic005_GetSpellPlay(s32 nSide, u8 *bCombo, void *pCardInfo, s32 nMode) {
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

typedef struct {
    u8 pad[8];
    u16 x;
    s16 y;
} Info_00124810;

typedef struct {
    Info_00124810 *info;
    u8 pad[0x34];
    s16 x;
    s16 y;
} Sprite_00124810;


/* Fills hand combination `bCombo` for side `nSide`: the best fusion or equip chain, its card into `pCardInfo`. */
s32 TaLogic005_SetComboQue(s32 nSide, u8 *bCombo, void *pCardInfo) {
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
                    if (**node != 0x217) {
                        value = TaHand_GetCardAPDP(**node);
                        if ((value >> 16) >= 0x5DC) {
                            value = TaLogic_GetEnchantQue(nSide, *node, 0, 0);
                        }
                        if (TaHand_IsCardSummon2(nSide, card) == 1) {
                            if (best < value) {
                                TaLogic_ConvEmptyCombo_00124A30(nSide, *node, entries);
                                TaLogic_CopyArray((u8 *)*node + 2, bCombo + 6);
                                SzDuel_InitCardInfo(pCardInfo, **node);
                                ((Sprite_00124810 *)pCardInfo)->x = (value >> 16) - (((Sprite_00124810 *)pCardInfo)->info->x & 0x1FFF);
                                ((Sprite_00124810 *)pCardInfo)->y = (value & 0xFFFF) - (((Sprite_00124810 *)pCardInfo)->info->y & 0x1FFF);
                                best = value;
                                if (top < value) {
                                    top = value;
                                }
                            }
                        } else if (top < value) {
                            top = value;
                        }
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
} Info_00124A30;

/* Fills an empty combination: the hand card side `nSide` can summon with the best attack plus defence. */
void TaLogic_ConvEmptyCombo_00124A30(s32 nSide, void *pCardInfo, s32 *pResult) {
    Info_00124A30 *info = pCardInfo;
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
                if (card != 0x3E7 && TaLogic005_IsRefuseEmptyCombo(card) == 0 && level >= TaHand_GetCardSummonCost2(card, nSide)) {
                    cost = TaHand_GetCardAPDP(card);
                    if ((cost & 0xFFFF) + (cost >> 16) * 2 < 0xFA1 && TaHand_IsCardEffect(card) == 2 &&
                        (u16)TaLogic_GetHandFusion(info->id, (u16)card) == 0x3E7) {
                        TaLogic_AddEmptyCombo(info->values, buf[i]);
                    }
                }
            }
        }
    }
}

/* Whether this duelist keeps card `nCardNo` out of a summon (it is wanted for an equip). */
s32 TaLogic005_IsRefuseEmptyCombo(s32 nCardNo) {
    s32 value;

    if ((TaHand_GetCardKind(nCardNo) >> 5) != 0) {
        return 1;
    }
    value = TaHand_GetCardKind(nCardNo) & 0x1F;
    if ((value == 0) || (value == 0xF) || (value == 0x12)) {
        return 1;
    }
    return 0;
}


typedef struct {
    u8 pad0[6];
    u8 slot[5];
} Obj1_00124C90;

typedef struct {
    u8 pad0[0x3C];
    u16 id;
} Obj2_00124C90;

/* Fills hand combination `bCombo` for side `nSide` with this duelist's special combination, its card into
   `pCardInfo`. */
s32 TaLogic_SetSpecialComboQue_00124C90(s32 nSide, void *bCombo, void *pCardInfo, s32 nOpt) {
    Obj1_00124C90 *o1 = bCombo;
    Obj2_00124C90 *o2 = pCardInfo;
    s32 list[8];
    s32 i;
    u8 t;

    for (i = 0; i < 5; i++) {
        o1->slot[i] = 0xFF;
    }
    TaHand_GetNextHand(nSide, list);
    if (o2 == NULL) {
        return -1;
    }
    if ((nOpt & 0xFF) == 0) {
        for (i = 0; i < TaHand_GetNextHandNum(nSide); i++) {
            if (i != o1->slot[0] && i != o1->slot[1]) {
                if (o2->id == list[i] && TaHand_IsCardSummon2(nSide, list[i]) == 1) {
                    o1->slot[0] = i;
                }
            }
        }
        return 0;
    }
    TaLogic005_Is2Head_ThunderDragon(nSide, list);
    for (i = 0; i < TaHand_GetNextHandNum(nSide); i++) {
        t = TaHand_GetCardKind(list[i]);
        if ((t >> 5) == 0 && (t & 0x1F) == 0 && TaHand_IsCardSummon2(nSide, list[i]) == 1) {
            o1->slot[0] = i;
        }
    }
    for (i = 0; i < TaHand_GetNextHandNum(nSide); i++) {
        t = TaHand_GetCardKind(list[i]);
        if ((t >> 5) == 0 && (t & 0x1F) == 0x12 && TaHand_IsCardSummon2(nSide, list[i]) == 1) {
            o1->slot[1] = i;
        }
    }
    for (i = 0; i < TaHand_GetNextHandNum(nSide); i++) {
        t = TaHand_GetCardKind(list[i]);
        if ((t >> 5) == 0 && (t & 0x1F) == 0xF && TaHand_IsCardSummon2(nSide, list[i]) == 1) {
            o1->slot[2] = i;
        }
    }
    return 0;
}

/* Ta_GetSommonPiecePreference for this duelist. */
s32 TaLogic_GetSommonPiecePreference_00124F50(s32 nSide, u32 nPr) {
    return Ta_GetSommonPiecePreference(nSide, nPr);
}

typedef struct {
    u8 low : 4;
    u8 high : 4;
} Flags_00124F60;

typedef struct {
    u16 id;
    u8 action;
    u8 pad3;
    u16 position;
    u8 pad6[6];
    s32 value;
    u8 mode;
} Output_00124F60;


/* The task of a unit running from danger (task `pTask`): the safest square in reach, into `pInput` (`fFirst` = 1
   for the unit's first-choice task). */
s32 TaLogic_GetMinimumTask_RunMission_00124F60(u16 *pTask, s32 nSide, void *pInput, u8 fFirst) {
    extern s32 TaLogic_IsRunPassRoot(s32, s32, s32, s32, s32, s32, void *, u8);
    extern s32 TaLogic_IsOpenUnit_00126380();
    s32 position;
    u8 upperX;
    u8 flag;
    Flags_00124F60 cells[12];
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
    Output_00124F60 *out = pInput;

    position = SzDuel_GetUnitLoc(*pTask >> 8, *pTask & 0xFF);
    i = 0;
    do {
        cells[i].low = cells[i].high = 15;
        i++;
    } while (i < 12);

    {
        u16 value = (u16)TaLogic_GetWarnHideLvl_001254A0(nSide);
        originalX = position & 0xFF;
        originalY = position >> 8;
        if (TaLogic_GetUnitWarning(originalX, originalY, *pTask, 2, value, 0) == 0) {
            out->id = *pTask;
            out->action = 6;
            out->position = position;
            out->mode = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, out->position, 1, 0);
            out->value = TaLogic_IsOpenUnit_00126380(*pTask >> 8, *pTask & 0xFF, pTask);
            TaLogic005_InitRogicControl(pTask, fFirst);
            return 0;
        } else {
            result = GetMoveRev(SzDuel_GetUnit(*pTask >> 8, *pTask & 0xFF), originalX, originalY);
            if (result == 0) {
                out->id = *pTask;
                out->action = 6;
                out->position = position;
                out->mode = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, out->position, 1, 0);
                out->value = TaLogic_IsOpenUnit_00126380(*pTask >> 8, *pTask & 0xFF, pTask);
                TaLogic005_InitRogicControl(pTask, fFirst);
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
                                value = (u16)TaLogic_GetWarnHideLvl_001254A0(nSide);
                                score = TaLogic_GetUnitWarning(x, y, *pTask, 2, value, 0);
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
                        out->mode = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, out->position, 0, 0);
                    }
                    out->value = TaLogic_IsOpenUnit_00126380(*pTask >> 8, *pTask & 0xFF, pTask);
                } else {
                    out->id = *pTask;
                    out->action = 6;
                    out->position = position;
                    out->mode = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, out->position, 1, 0);
                    out->value = TaLogic_IsOpenUnit_00126380(*pTask >> 8, *pTask & 0xFF, pTask);
                }
                TaLogic005_InitRogicControl(pTask, fFirst);
            }
        }
    }
    return 0;
}

/* How careful this duelist is about hidden cards (by its life points and monster count). */
s32 TaLogic_GetWarnHideLvl_001254A0(s32 nSide) {
    if (SzDuel_GetLP(nSide) > 0x3E8) {
        if (SzDuel_GetUnitMonsterCount(nSide) >= 3) {
            return 0x1F4;
        } else {
            return 0x3E8;
        }
    } else {
        return 0x7D0;
    }
}

typedef struct Source_00125500 {
    u16 position;
    u8 pad2[6];
    u32 targets;
} Source_00125500;

typedef struct Output_00125500 {
    u16 position;
    u8 mode;
    u8 pad3;
    u16 target;
    u8 pad6[6];
    s32 flag;
    u8 value;
} Output_00125500;

typedef struct Position_00125500 {
    u8 x : 4;
    u8 y : 4;
} Position_00125500;


/* The task's target square: the second half-word when the second argument is 1, else the first. */
static inline u32 target_00125500(void *arg0, u8 which) {
    Source_00125500 *source = arg0;
    if (which == 1) {
        return (u16)(source->targets >> 16);
    }
    return *(u16 *)&source->targets;
}

/* This duelist's caution about hidden cards (an inline copy of its GetWarnHideLvl: by life points and monster
   count). */
static inline s32 penalty_00125500(s32 object) {
    if (SzDuel_GetLP(object) > 1000) {
        if (SzDuel_GetUnitMonsterCount(object) >= 3) {
            return 500;
        } else {
            return 1000;
        }
    } else {
        return 2000;
    }
}

/* The task of a unit attacking (task `pTask`): its path to the goal, into `pInput`; -1 when it has none (`fFirst`
   = 1 for the unit's first-choice task). */
s32 TaLogic_GetMinimumTask_AtkMission_00125500(void *pTask, s32 nSide, void *pInput, u8 fFirst) {
    extern void TaLogic_GetInvadeRoot();
    s32 sourceTarget;
    s32 count;
    s32 sourceY;
    s32 sourceX;
    s32 selectedFlag;
    Position_00125500 positions[12];
    s32 flag;
    s32 otherTarget;
    s32 j;
    Position_00125500 *walk;
    s32 object;
    u32 targetXWord;
    u32 targetYWord;
    Source_00125500 *source = pTask;
    Output_00125500 *output = pInput;

    targetXWord = target_00125500(pTask, fFirst);
    targetYWord = target_00125500(pTask, fFirst);
    if (SzDuel_GetUnit(targetYWord >> 8, targetXWord & 0xFF) == 0) {
        TaLogic_InitRogicControl(pTask, 1);
        return -1;
    }

    flag = TaLogic_IsOpenUnit_00126380(source->position >> 8, source->position & 0xFF, pTask);
    sourceTarget = SzDuel_GetUnitLoc(source->position >> 8, source->position & 0xFF);
    targetXWord = target_00125500(pTask, fFirst);
    targetYWord = target_00125500(pTask, fFirst);
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
        cost = TaLogic_GetUnitWarning(sourceX, sourceY, nSide, 2, 1,
                            (u8)penalty_00125500(nSide));
        if (cost >= SzDuel_GetUnitAP(source->position >> 8, source->position & 0xFF, 0)) {
            output->value = TaLogic_IsDefStyleUnit(source->position >> 8, source->position & 0xFF,
                                        output->target, 1, 0);
        } else {
            output->value = TaLogic_IsDefStyleUnit(source->position >> 8, source->position & 0xFF,
                                        output->target, 0, 0);
        }
        TaLogic005_InitRogicControl(pTask, fFirst);
    } else {
        s32 targetY;
        s32 targetX;
        Position_00125500 *current;
        s32 i;
        s32 bestCost;
        s32 selected;
        s32 penalty;
        u16 position;

        penalty = penalty_00125500(nSide);
        position = source->position;
        TaLogic_GetInvadeRoot(position >> 8, position & 0xFF, positions,
                      sourceX, sourceY, targetX = otherTarget & 0xFF,
                      targetY = otherTarget >> 8,
                      target_00125500(pTask, fFirst), 0, 30, (u16)penalty);
        count = TaLogic_GetMinGoalCount((u8 *)positions);
        selected = 0xFF;
        if (count > 0) {
            selectedFlag = 0;
            bestCost = 0xFFFF;
            for (i = 0; i < count; i++) {
                s32 state = TaLogic005_IsOpenMoveUnit(source->position >> 8, source->position & 0xFF,
                                          sourceX, sourceY, targetX, targetY);
                if (state == 1) {
                    Position_00125500 *forcedPosition = &positions[i];
                    selected = i;
                    selectedFlag = 1;
                    i = count;
                    forcedPosition->x = targetX;
                    forcedPosition->y = targetY;
                } else {
                    s32 cost;
                    s32 penalty = penalty_00125500(nSide);
                    current = &positions[i];
                    cost = TaLogic_GetUnitWarning(current->x, current->y, nSide, 2, 1,
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
            TaLogic005_InitRogicControl(pTask, fFirst);
            return 0;
        } else {
            output->position = source->position;
            output->mode = 6;
            output->target = sourceTarget;
            output->flag = selectedFlag;
            output->value = TaLogic_IsDefStyleUnit(source->position >> 8, source->position & 0xFF,
                                        output->target, 0, 0);
            TaLogic_InitRogicControl(pTask, fFirst);
            return 0;
        }
    }
    return 0;
}

typedef struct Coord_00125B70 {
    u8 x : 4;
    u8 y : 4;
} Coord_00125B70;

typedef struct Unit_00125B70 {
    u16 position;
    u8 pad2[6];
    union {
        u32 packed;
        u16 low;
    } target;
} Unit_00125B70;

typedef struct Output_00125B70 {
    u16 position;
    u8 kind;
    u8 pad3;
    u16 target;
    u8 pad6[6];
    s32 value;
    u8 flag;
} Output_00125B70;


/* The task's target square: the second half-word when the second argument is 1, else the first. */
static inline u32 target_00125B70(void *unit, s32 side) {
    return side == 1 ? (u32)(u16)(((Unit_00125B70 *)unit)->target.packed >> 16) : (u32)((Unit_00125B70 *)unit)->target.low;
}

/* The smaller of the two values. */
static inline u32 minY_00125B70(void *unit, s32 side, u8 coord) {
    return coord < (target_00125B70(unit, side) >> 8) ? coord : (target_00125B70(unit, side) >> 8);
}

/* The larger of the two values. */
static inline u32 maxY_00125B70(void *unit, s32 side, u8 coord) {
    return (target_00125B70(unit, side) >> 8) < coord ? coord : (target_00125B70(unit, side) >> 8);
}

/* The smaller of the two values. */
static inline u32 minX_00125B70(void *unit, s32 side, u8 coord) {
    return coord < (target_00125B70(unit, side) & 0xFF) ? coord : (target_00125B70(unit, side) & 0xFF);
}

/* The larger of the two values. */
static inline u32 maxX_00125B70(void *unit, s32 side, u8 coord) {
    return (target_00125B70(unit, side) & 0xFF) < coord ? coord : (target_00125B70(unit, side) & 0xFF);
}

/* This duelist's caution about hidden cards (an inline copy of its GetWarnHideLvl: by life points and monster
   count). */
static inline s32 scoreLimit_00125B70(s32 unit) {
    if (SzDuel_GetLP(unit) > 1000) {
        if (SzDuel_GetUnitMonsterCount(unit) >= 3) {
            return 500;
        }
        return 1000;
    }
    return 2000;
}

/* The task of a unit moving to its goal (task `pTask`), into `pInput` (`fFirst` = 1 for the unit's first-choice
   task). */
s32 TaLogic_GetMinimumTask_MoveMission_00125B70(void *pTask, s32 nSide, void *pInput, u8 fFirst, u8 nKind) {
    extern s32 TaLogic_GetUnitWarning();
    extern void TaLogic_GetRoot();
    extern s32 TaLogic_IsDefStyleUnit(s32, s32, s32, u8, s32);
    Coord_00125B70 coords[12];
    s32 initial;
    s32 cell;
    s32 count;

    initial = SzDuel_GetUnitLoc(((Unit_00125B70 *)pTask)->position >> 8, ((Unit_00125B70 *)pTask)->position & 0xFF);
    {
    s32 bestScore;
    s32 best;
    s32 side = fFirst;
    Coord_00125B70 *candidate;
    s32 index;
    if (target_00125B70(pTask, side) == 0xFFFF) {
        if (initial == target_00125B70(pTask, side)) {
            ((Output_00125B70 *)pInput)->position = ((Unit_00125B70 *)pTask)->position;
            ((Output_00125B70 *)pInput)->kind = 6;
            ((Output_00125B70 *)pInput)->target = initial;
            ((Output_00125B70 *)pInput)->flag = TaLogic_IsDefStyleUnit(((Unit_00125B70 *)pTask)->position >> 8, ((Unit_00125B70 *)pTask)->position & 0xFF, ((Output_00125B70 *)pInput)->target, nKind, 0);
            ((Output_00125B70 *)pInput)->value = TaLogic_IsOpenUnit_00126380(((Unit_00125B70 *)pTask)->position >> 8, ((Unit_00125B70 *)pTask)->position & 0xFF, pTask);
            TaLogic005_InitRogicControl(pTask, fFirst);
            return 0;
        }
    }

    candidate = coords;
    {
        s32 i = 0;
        Coord_00125B70 *entry = candidate;
        do {
            entry->x = entry->y = 0xF;
            i++;
            entry++;
        } while (i < 12);
    }

    cell = SzDuel_GetMapUnitID(target_00125B70(pTask, side) & 0xFF, ((u32)target_00125B70(pTask, side)) >> 8);
    if (cell < 0) {
        cell = 0xFFFF;
    }
    TaLogic_GetRoot(((Unit_00125B70 *)pTask)->position >> 8, ((Unit_00125B70 *)pTask)->position & 0xFF,
                 coords, initial & 0xFF, initial >> 8, target_00125B70(pTask, side) & 0xFF,
                 ((u32)target_00125B70(pTask, side)) >> 8, (u16)cell, 7);
    count = TaLogic_GetMinGoalCount((u8 *)coords);
    {
        if (count > 0) {
        best = 0xFF;
        bestScore = 0xFFFF;
        for (index = 0; index < count; index++) {
                if (SzDuel_GetMapUnit(candidate->x, candidate->y) == 0) {
                    s32 score = TaLogic_GetUnitWarning(candidate->x, candidate->y, nSide, 2, 1, (u8)scoreLimit_00125B70(nSide));
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
                        bestMinY = minY_00125B70(pTask, side, bestY);
                        bestMaxY = maxY_00125B70(pTask, side, bestY);
                        bestX = (&coords[best])->x;
                        bestMinX = minX_00125B70(pTask, side, bestX);
                        bestMaxX = maxX_00125B70(pTask, side, bestX);
                        currentY = (u8)candidate->y;
                        currentMinY = minY_00125B70(pTask, side, currentY);
                        currentMaxY = maxY_00125B70(pTask, side, currentY);
                        currentX = candidate->x;
                        currentMinX = minX_00125B70(pTask, side, currentX);
                        currentMaxX = maxX_00125B70(pTask, side, currentX);
                        if ((currentMaxX - currentMinX) + (currentMaxY - currentMinY) < (bestMaxX - bestMinX) + (bestMaxY - bestMinY)) {
                            bestScore = score;
                            best = index;
                        }
                    }
                }
            candidate++;
        }
    } else {
        ((Output_00125B70 *)pInput)->position = ((Unit_00125B70 *)pTask)->position;
            ((Output_00125B70 *)pInput)->kind = 6;
            ((Output_00125B70 *)pInput)->target = initial;
            ((Output_00125B70 *)pInput)->flag = TaLogic_IsDefStyleUnit(((Unit_00125B70 *)pTask)->position >> 8, ((Unit_00125B70 *)pTask)->position & 0xFF, ((Output_00125B70 *)pInput)->target, nKind, 0);
            ((Output_00125B70 *)pInput)->value = TaLogic_IsOpenUnit_00126380(((Unit_00125B70 *)pTask)->position >> 8, ((Unit_00125B70 *)pTask)->position & 0xFF, pTask);
        TaLogic005_InitRogicControl(pTask, fFirst);
        return 0;
    }

        if (best != 0xFF) {
            ((Output_00125B70 *)pInput)->position = ((Unit_00125B70 *)pTask)->position;
            ((Output_00125B70 *)pInput)->kind = 6;
            ((Output_00125B70 *)pInput)->target = (coords[best].y << 8) | coords[best].x;
            ((Output_00125B70 *)pInput)->flag = TaLogic_IsDefStyleUnit(((Unit_00125B70 *)pTask)->position >> 8, ((Unit_00125B70 *)pTask)->position & 0xFF, ((Output_00125B70 *)pInput)->target, nKind, 0);
            ((Output_00125B70 *)pInput)->value = TaLogic_IsOpenUnit_00126380(((Unit_00125B70 *)pTask)->position >> 8, ((Unit_00125B70 *)pTask)->position & 0xFF, pTask);
        } else {
            ((Output_00125B70 *)pInput)->position = ((Unit_00125B70 *)pTask)->position;
            ((Output_00125B70 *)pInput)->kind = 6;
            ((Output_00125B70 *)pInput)->target = initial;
            ((Output_00125B70 *)pInput)->flag = TaLogic_IsDefStyleUnit(((Unit_00125B70 *)pTask)->position >> 8, ((Unit_00125B70 *)pTask)->position & 0xFF, ((Output_00125B70 *)pInput)->target, nKind, 0);
            ((Output_00125B70 *)pInput)->value = TaLogic_IsOpenUnit_00126380(((Unit_00125B70 *)pTask)->position >> 8, ((Unit_00125B70 *)pTask)->position & 0xFF, pTask);
        }
        TaLogic005_InitRogicControl(pTask, fFirst);
    }
    }
    return 0;
}

/* Whether this duelist opens (turns face up) unit (nSide, nID) now: 0 no, 1 or 2 by its kind. */
s32 TaLogic_IsOpenUnit_00126380(s32 nSide, s32 nID, void *pInfo) {
    extern s32 SzDuel_GetUnitCardNo();
    s32 card;
    s32 position;
    s32 owner;
    s32 *info;
    u8 count;
    s32 i;

    card = SzDuel_GetUnitCardNo(nSide, nID);
    position = SzDuel_GetUnitLoc(nSide, nID);
    owner = Ta_IsUnitControl(nSide, nID);
    info = SzDuel_GetUnitEffect(nSide, nID, 0);
    count = 0;
    if (SzDuel_GetUnitStatus(nSide, nID, 4) != 0) {
        return 0;
    }
    switch (SzDuel_GetUnitKind(nSide, nID) >> 5) {
    case 0:
        switch (SzDuel_GetUnitCardNo(nSide, nID)) {
        case 0x230:
            for (card = 1; card <= 5; card++) {
                if (SzDuel_GetUnitCardNo(nSide, card) == 0x258 && nSide == Ta_IsUnitControl(nSide, card)) {
                    count++;
                }
                if (SzDuel_GetUnitCardNo((nSide == 0) ? 1 : 0, card) == 0x258 &&
                    nSide == Ta_IsUnitControl((nSide == 0) ? 1 : 0, card)) {
                    count++;
                }
            }
            if (count >= 2) {
                return 1;
            }
            break;
        case 0x258:
            for (card = 1; card <= 5; card++) {
                if (SzDuel_GetUnitCardNo(nSide, card) == 0x230 && nSide == Ta_IsUnitControl(nSide, card)) {
                    count++;
                }
                if (SzDuel_GetUnitCardNo((nSide == 0) ? 1 : 0, card) == 0x230 &&
                    nSide == Ta_IsUnitControl((nSide == 0) ? 1 : 0, card)) {
                    count++;
                }
            }
            if (count >= 2) {
                return 1;
            }
            break;
        case 0x251:
            for (card = 1; card <= 5; card++) {
                if ((SzDuel_GetUnitKind(nSide, card) & 0x1F) == 0x10 && nSide == Ta_IsUnitControl(nSide, card)) {
                    count++;
                }
                if ((SzDuel_GetUnitKind((nSide == 0) ? 1 : 0, card) & 0x1F) == 0x10 &&
                    nSide == Ta_IsUnitControl((nSide == 0) ? 1 : 0, card)) {
                    count++;
                }
            }
            if (count >= 3) {
                return 1;
            }
            break;
        case 0x235:
            for (card = 6; card < 11; card++) {
                if (SzDuel_GetUnitStatus(nSide, nID, 4) != 0 && nSide == Ta_IsUnitControl(nSide, card)) {
                    count++;
                }
                if (SzDuel_GetUnitStatus((nSide == 0) ? 1 : 0, nID, 4) != 0 &&
                    nSide == Ta_IsUnitControl((nSide == 0) ? 1 : 0, card)) {
                    count++;
                }
            }
            if (count > 0) {
                return 1;
            }
            break;
        }
        return 2;
    case 5:
        if (TaLogic_GetActionReaction(nSide, nID, 0, 0, 6, 0) == 5) {
            return 2;
        }
        if (TaLogic005_IsDoCerem(Ta_IsUnitControl(nSide, nID), card) == 1 &&
            SzDuel_GetField(position & 0xFF, position >> 8) != 9) {
            return 1;
        }
        break;
    case 1:
        if (info == NULL) {
            return 2;
        }
        if (TaLogic_GetActionReaction(nSide, nID, 0, 0, 6, 0) == 5) {
            return 2;
        }
        if (Ta_GetUnitNumFrom22bitFlagList(SearchUnitByRange(0, 0, owner, 1, *info & 0x3F, 0xE)) > 2) {
            return 1;
        }
        break;
    case 2:
    case 3:
    case 4:
    default:
        return 2;
    }
    return 2;
}

/* The larger of the two values. */
static inline s32 max_00126840(s32 a, s32 b) {
    if (a < b) {
        return b;
    }
    return a;
}

/* Whether unit (nSide, nID) may open while moving from (nX, nZ) to the square next to it, (gX, gZ). */
s32 TaLogic005_IsOpenMoveUnit(s32 nSide, s32 nID, s32 nX, s32 nZ, s32 gX, s32 gZ) {
    s32 min_y;
    s32 min_x;

    min_y = nZ < gZ ? nZ : gZ;
    gZ = max_00126840(gZ, nZ);
    min_x = nX < gX ? nX : gX;
    gX = max_00126840(gX, nX);
    if ((gX - min_x) + (gZ - min_y) != 2) {
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

typedef struct State_00126940 {
    u8 pad0[4];
    u16 field4;
    u16 pad6;
    u32 field8;
} State_00126940;

/* Clears a unit's task (`Is1st` on its first turn). */
void TaLogic005_InitRogicControl(void *pUnit, u8 Is1st) {
    State_00126940 *state = (State_00126940 *)pUnit;

    if (Is1st < 2) {
        if (Is1st == 1) {
            state->field4 = (state->field4 & 0xFF) | 0xFF00;
        } else {
            state->field4 = (state->field4 & 0xFF00) | 0xFF;
        }
        if (Is1st == 1) {
            state->field8 = (state->field8 & 0xFFFF) | 0xFFFF0000;
        } else {
            state->field8 = (state->field8 & 0xFFFF0000) | 0xFFFF;
        }
    }
}

/* Whether side `nSide` can play ritual card `nCardNo` now (it has the units to give up). */
s32 TaLogic005_IsDoCerem(s32 nSide, s32 nCardNo) {
    s32 data[4];
    s32 i;
    s32 mask;
    s32 y;
    s32 x;
    s32 cell;
    s32 coords;

    Ta_GetCeremSacrifice(data, *(s32 *)((u8 *)TaHand_GetCardEffect(nCardNo, 0) + 4));
    if ((mask = Ta_GetSacrificeUnit(data, nSide)) < 0) {
        return 0;
    }
    for (i = 0; i < Ta_GetUnitNumFrom22bitFlagList(mask); i++) {
        cell = Ta_GetUnitOwnerIDFromLstCount(mask, i);
        x = cell >> 8;
        y = cell & 0xFF;
        coords = SzDuel_GetUnitLoc(x, y);
        if (TaUtil_GetUnitAP(x, y, coords & 0xFF, coords >> 8) >= 0xA28) {
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
} Req_00126AB0;

typedef struct {
    u8 pad0[0x160];
    u16 list[32];    /* 0x160 */
    u8 idx : 5;      /* 0x1A0 */
    u8 pad1A0 : 3;
    u8 pad1A1;
    u16 count;       /* 0x1A2 */
} Work_00126AB0;

s32 TaLogic_GetInputQueFromMinimumTask_b(void *, void *, s32);

/* This computer duelist's controller (one entry of duelistControllers): the buttons it presses this frame. With an empty
   input queue it plans its next task and turns it into buttons, then plays the queue back one button per frame;
   after 600 frames it gives up the turn (0x20, then 0x800). */
s32 func_00126AB0(s32 wCursorPos, void *pCtl) {
    Req_00126AB0 req;
    Work_00126AB0 *w;
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
        if (TaLogic_GetMinimumTask_00121800(w, &req, wCursorPos) == 0) {
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
s32 TaLogic_GetMinimumTask_00126C80(void *pCtl, void *pInput, s32 wCursorPos) {
    u16 *tasks = pCtl;
    s32 side;
    s32 found;
    s32 result;
    s32 index;

    side = SzDuel_GetTurnOwner();
    found = 0;
    if ((result = TaLogic_GetNextActiveUnit_001273E0(tasks, side, (s32)pInput)) < 0) {
        return 0;
    }
    index = TaLogic_GetActionUnitFromOwnerID(tasks, result & 0xFFFF);
    if (index < 0) {
        return 0;
    }
    if ((result >> 16) == 1) {
        if (((tasks[index * 8 + 2] >> 8) & 0xFF) == 10) {
            TaLogic_InitRogicControl(tasks + index * 8, 1);
        } else {
            TaLogic_InitRogicControl(tasks + index * 8, 0);
        }
        return 1;
    }
    TaLogic_CommandUnit_001271F0(tasks + index * 8);
    switch ((tasks[index * 8 + 2] >> 8) & 0xFF) {
    case 5:
        if (SzDuel_GetUnitStatus(tasks[index * 8] >> 8, tasks[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_RunMission_001291C0(tasks + index * 8, side, pInput, 1);
            found = 1;
        }
        break;
    case 2:
        if (SzDuel_GetUnitStatus(tasks[index * 8] >> 8, tasks[index * 8] & 0xFF, 0) == 0) {
            if (TaLogic_GetMinimumTask_AtkMission_00129D00(tasks + index * 8, side, pInput, 1) < 0) {
                TaLogic006_InitRogicControl(tasks + index * 8, 1);
                return 1;
            }
            found = 1;
        }
        break;
    case 10:
        if (TaLogic_GetMinimumTask_Summon_00127E30(tasks[index * 8], side, (s32)pInput) < 0) {
            TaLogic006_InitRogicControl(tasks + index * 8, 1);
            *(u8 *)((u8 *)pInput + 2) = 0xFF;
            *(s32 *)((u8 *)pInput + 0xC) = 0;
        } else {
            TaLogic006_InitRogicControl(tasks + index * 8, 1);
            found = 1;
        }
        break;
    case 6:
        if (SzDuel_GetUnitStatus(tasks[index * 8] >> 8, tasks[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_MoveMission_0012A2E0(tasks + index * 8, side, pInput, 1, 0);
            found = 1;
        }
        break;
    case 3:
        if (SzDuel_GetUnitStatus(tasks[index * 8] >> 8, tasks[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_MoveMission_0012A2E0(tasks + index * 8, side, pInput, 1, 1);
            found = 1;
        }
        break;
    case 9:
        TaLogic_GetMinimumTask_EncMission(tasks + index * 8, side, pInput, 1, 0, TaLogic_GetWarnHideLvl_0012B1B0(side), 5, 1);
        found = 1;
        break;
    case 11:
        TaLogic_GetMinimumTask_TrapMission_0012AAC0(tasks + index * 8, side, pInput, 1);
        found = 1;
        break;
    case 12:
        TaLogic_GetMinimumTask_ReviveMission_00129700(tasks + index * 8, side, (s32)pInput, 1);
        found = 1;
        break;
    case 14:
        TaLogic_GetMinimumTask_DoNone(tasks + index * 8, side, pInput);
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
    switch (tasks[index * 8 + 2] & 0xFF) {
    case 5:
        if (SzDuel_GetUnitStatus(tasks[index * 8] >> 8, tasks[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_RunMission_001291C0(tasks + index * 8, side, pInput, 0);
            found = 1;
        }
        break;
    case 2:
        if (SzDuel_GetUnitStatus(tasks[index * 8] >> 8, tasks[index * 8] & 0xFF, 0) == 0) {
            if (TaLogic_GetMinimumTask_AtkMission_00129D00(tasks + index * 8, side, pInput, 0) < 0) {
                TaLogic_GetMinimumTask_RunMission_001291C0(tasks + index * 8, side, pInput, 0);
            }
            found = 1;
        }
        break;
    case 10:
        if (TaLogic_GetMinimumTask_Summon_00127E30(tasks[index * 8], side, (s32)pInput) < 0) {
            TaLogic006_InitRogicControl(tasks + index * 8, 0);
            *(u8 *)((u8 *)pInput + 2) = 0xFF;
            found = 1;
            *(s32 *)((u8 *)pInput + 0xC) = 0;
        } else {
            TaLogic_InitRogicControl(tasks + index * 8, 0);
            found = 1;
        }
        break;
    case 6:
        if (SzDuel_GetUnitStatus(tasks[index * 8] >> 8, tasks[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_MoveMission_0012A2E0(tasks + index * 8, side, pInput, 0, 0);
            found = 1;
        }
        break;
    case 3:
        if (SzDuel_GetUnitStatus(tasks[index * 8] >> 8, tasks[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_MoveMission_0012A2E0(tasks + index * 8, side, pInput, 0, 1);
            found = 1;
        }
        break;
    case 11:
        TaLogic_GetMinimumTask_TrapMission_0012AAC0(tasks + index * 8, side, pInput, 0);
        found = 1;
        break;
    case 9:
        TaLogic_GetMinimumTask_EncMission(tasks + index * 8, side, pInput, 0, 0, TaLogic_GetWarnHideLvl_0012B1B0(side), 5, 1);
        found = 1;
        break;
    case 12:
        TaLogic_GetMinimumTask_ReviveMission_00129700(tasks + index * 8, side, (s32)pInput, 0);
        found = 1;
        break;
    case 14:
        TaLogic_GetMinimumTask_DoNone(tasks + index * 8, side, pInput);
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

typedef struct Entry_001271F0 {
    u16 unitId; /* (side << 8) | unit */
    u16 pad2;
    s16 action;
    u16 pad6;
    s32 target;
} Entry_001271F0;

/* Gives a unit of this duelist its order for this turn (attack, run, move, summon, guard). */
s32 TaLogic_CommandUnit_001271F0(void *pCtl) {
    Entry_001271F0 *entry = pCtl;
    s32 card;
    u16 unitId;

    card = Ta_IsUnitControl(entry->unitId >> 8, entry->unitId & 0xFF);
    if (SzDuel_GetUnit(entry->unitId >> 8, entry->unitId & 0xFF) != 0) {
        if (SzDuel_GetUnitStatus(entry->unitId >> 8, entry->unitId & 0xFF, 0) == 0) {
            unitId = entry->unitId;
            if (unitId != 0xFFFF) {
                if ((unitId & 0xFF) == 0) {
                    if (entry->target == -1) {
                        if (TaLogic_IsAttackedNow(unitId >> 8, unitId & 0xFF, 0) == 1) {
                            if (SzDuel_InqHandPhase(entry->unitId >> 8) == 1) {
                                entry->action = 0x50A;
                            } else {
                                entry->action = 0x5FF;
                            }
                        } else if (SzDuel_InqHandPhase(entry->unitId >> 8) == 1) {
                            entry->action = 0xA06;
                            entry->target &= 0xFFFF0000;
                        } else {
                            entry->action = 0x6FF;
                            entry->target = (u16)entry->target;
                        }
                    }
                } else {
                    switch (SzDuel_GetUnitKind(unitId >> 8, unitId & 0xFF) >> 5) {
                    case 0:
                        if (TaUtil_IsExMonster(entry->unitId >> 8, entry->unitId & 0xFF) == 1) {
                            TaLogic006_CommandEfcMonster(entry);
                        } else {
                            TaLogic006_CommandBtlUnit(entry, 1);
                        }
                        break;
                    case 2:
                        TaLogic_CommandEncUnit(entry, 5, 0, TaLogic_GetWarnHideLvl_0012B1B0(card) & 0xFF);
                        break;
                    case 1:
                    case 3:
                    case 4:
                    case 5:
                        TaLogic006_CommandSpellUnit(entry);
                        break;
                    default:
                        entry->action = 0x5FF;
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
s32 TaLogic_GetNextActiveUnit_001273E0(u16 *pCtl, s32 nSide, s32 pInput) {
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
    TaLogic_CommandUnit_001271F0(pCtl + idx * 8);
    if (((pCtl[idx * 8 + 2] >> 8) & 0xFF) == 10) {
        if (SzDuel_InqHandPhase(nSide) == 1 && TaLogic_GetMinimumTask_Summon_00127E30(pos, nSide, pInput) >= 0) {
            return pos | 0x10000;
        }
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_GetUnitStatus(nSide, 0, 0) == 0) {
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_InqHandPhase(nSide) == 1 && TaLogic_GetMinimumTask_Summon_00127E30(pos, nSide, pInput) >= 0) {
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
    u16 unitId; /* (side << 8) | unit */
    u16 unk02;
    s16 state;
    u16 unk06;
    union {
        u32 word;
        struct {
            u16 low;
            u16 high;
        } halves;
    } data;
} Entry_001277C0;

typedef struct {
    u16 card;
    u8 flag;
    u8 pad;
} Slot_001277C0;


/* Orders a fighting unit (task `pTask`): straight at the enemy leader when `fGoalFirst` and the path is open,
   else at the nearest enemy it can beat. */
void TaLogic006_CommandBtlUnit(void *pTask, s32 fGoalFirst) {
    extern void TaLogic_InitIgnoreLst();
    extern s32 TaLogic_IsRootOpen();
    extern s32 TaLogic006_GetNearUnit();
    Entry_001277C0 *entry = pTask;
    s32 side;
    s32 player;
    s32 other;
    s32 pos;
    s32 otherPos;
    s32 i;
    u8 work[0x70];
    Slot_001277C0 list[22];
    s16 countA;
    s16 countB;

    if (SzDuel_GetUnit(entry->unitId >> 8, entry->unitId & 0xFF) != 0) {
        side = Ta_GetCurrentSide(entry->unitId >> 8, entry->unitId & 0xFF);
        other = (side == 0 ? 1 : 0) << 8;
        pos = SzDuel_GetUnitLoc(entry->unitId >> 8, entry->unitId & 0xFF);
        otherPos = SzDuel_GetUnitLoc(other >> 8, other & 0xFF);
        player = SzDuel_GetUnit(entry->unitId >> 8, entry->unitId & 0xFF);
        for (i = 0; i < 22; i++) {
            list[i].card = 0xFFFF;
            list[i].flag = 0xFF;
        }
        TaLogic_InitIgnoreLst(work);
        if (fGoalFirst != 0) {
            if (TaLogic_IsRootOpen(entry->unitId >> 8, entry->unitId & 0xFF, pos & 0xFF, pos >> 8,
                              other >> 8, other & 0xFF, otherPos & 0xFF, otherPos >> 8, 5) > 0) {
                entry->state = 0x2FF;
                entry->data.word = (other << 16) | entry->data.halves.low;
                return;
            }
        }
        countB = 0;
        countA = 0;
        i = 1;
        while (1) {
            switch (TaLogic006_GetNearUnit(entry, 0, player, pos & 0xFF, pos >> 8,
                                  Ta_GetCurrentSide(entry->unitId >> 8, entry->unitId & 0xFF) == 0 ? 1 : 0,
                                  i & 0xFF, TaLogic_GetWarnHideLvl_0012B1B0(side), list, 0, &countA, &countB, 5, work)) {
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
            }
            i++;
            if (i > 5) {
                break;
            }
        }
        TaLogic006_CommandInvadeUnit(entry);
    }
}

/* TaLogic_GetNearUnit with this duelist's view and strength settings. */
void TaLogic006_GetNearUnit(s32 pTask, s32 pTree, s32 pVarInfo, s32 nX, s32 nZ, s32 eSide, s32 bDist, s32 WarnLvl, s32 nUnitLst, u16 wUnitNum, s32 wSize, s32 wNodeCount, u8 bChase, s32 wIgnoreLst) {
    TaLogic_GetNearUnit(pTask, pTree, pVarInfo, nX, nZ, eSide, bDist, WarnLvl,
                  nUnitLst, wUnitNum, wSize, wNodeCount, bChase,
                  0, 2000, wIgnoreLst);
}

/* Orders a unit (task `pTask`) to push into the opponent's side of the board. */
void TaLogic006_CommandInvadeUnit(void *pTask) {
    s32 loc;
    u16 temp_v0;

    temp_v0 = *(u16 *)pTask;
    loc = SzDuel_GetUnitLoc((s32) temp_v0 >> 8, temp_v0 & 0xFF);
    *(s16 *)((u8 *)pTask + 4) = 0x6FF;
    if ((loc >> 8) < 3) {
        *(u32 *)((u8 *)pTask + 8) = *(u16 *)((u8 *)pTask + 8) | 0x03010000;
    } else {
        *(u32 *)((u8 *)pTask + 8) = *(u16 *)((u8 *)pTask + 8) | 0x05020000;
    }
}

typedef struct {
    u16 value;
    u8 flag;
} Entry_00127B00;


/* Orders an effect monster (task `pTask`): where its effect does most. */
void TaLogic006_CommandEfcMonster(void *pTask) {
    extern void TaLogic_InitIgnoreLst();
    extern s32 SzDuel_GetUnitCardNo();
    extern s32 TaLogic_GetNearUnit();
    u8 scratch[0x70];
    Entry_00127B00 entries[0x17];
    s16 result_a;
    s16 result_b;
    s32 i;
    Entry_00127B00 *entry;
    s32 side;
    s32 loc;
    s32 temp_v0_2;
    s32 result;
    s32 high;
    s32 low;
    s32 i2;
    s32 code;

    if ((temp_v0_2 = SzDuel_GetUnit(*(u16 *)pTask >> 8, *(u16 *)pTask & 0xFF)) != 0) {
        side = Ta_GetCurrentSide(*(u16 *)pTask >> 8, *(u16 *)pTask & 0xFF);
        loc = SzDuel_GetUnitLoc(*(u16 *)pTask >> 8, *(u16 *)pTask & 0xFF);
        result_b = 0;
        result_a = 0;
        entry = entries;
        i = 0;
        do {
            i++;
            entry->value = 0xFFFF;
            entry->flag = 0xFF;
            entry++;
        } while (i < 0x16);
        TaLogic_InitIgnoreLst(scratch);
        code = SzDuel_GetUnitCardNo(*(u16 *)pTask >> 8, *(u16 *)pTask & 0xFF);
        switch (code) {
        case 0x6F:
            if (TaLogic_CommandGunnerUnit(pTask, 0) == 1) {
                *(s16 *)((u8 *)pTask + 4) = 0xBFF;
                return;
            }
            goto fallback_00127B00;
        case 0x6C:
            i2 = 1;
            high = loc >> 8;
            low = loc & 0xFF;
            goto loop_00127B00;
        default:
            goto fallback_00127B00;
        }
loop_00127B00:
                result = TaLogic_GetWarnHideLvl_0012B1B0(side);
                entry = entries;
                result = TaLogic_GetNearUnit((s32)pTask, 0, temp_v0_2, low, high,
                                      side == 0 ? 1 : 0,
                                      i2 & 0xFF, result, (s32)entry, 0,
                                      (s32)&result_a, (s32)&result_b, 2, 0, 0x7D0,
                                      (s32)scratch);
                if (result != 0) {
                    if (result != 1) {
                        if (result != 2) {
                            if (result != 3) {
                                i2++;
                                goto retry_00127B00;
                            }
                        }
                        *(s16 *)((u8 *)pTask + 4) = 0x3FF;
                        *(u32 *)((u8 *)pTask + 8) = (loc << 16) | *(u16 *)((u8 *)pTask + 8);
                        return;
                    }
                } else {
                    *(s16 *)((u8 *)pTask + 4) = 0x3FF;
                    *(u32 *)((u8 *)pTask + 8) = (loc << 16) | *(u16 *)((u8 *)pTask + 8);
                    return;
                }
                return;
retry_00127B00:
        if (i2 <= 2) {
            goto loop_00127B00;
        }
        *(s16 *)((u8 *)pTask + 4) = 0x3FF;
        *(u32 *)((u8 *)pTask + 8) = (loc << 16) | *(u16 *)((u8 *)pTask + 8);
        return;
fallback_00127B00:
        TaLogic006_CommandBtlUnit(pTask, 1);
        return;
    }
}

typedef struct {
    u16 card;
    u16 pad2;
    s16 state;
    u16 pad6;
    union {
        u32 word;
        struct {
            u32 lower : 16;
            u32 upper : 16;
        } bits;
    } target;
} Obj_00127D20;

/* Orders a face-down magic card (task `pTask`): whether and where to open it. */
void TaLogic006_CommandSpellUnit(void *pTask) {
    extern s32 SzDuel_GetUnitCardNo();
    Obj_00127D20 *obj = pTask;
    s32 pos;

    Ta_IsUnitControl(obj->card >> 8, obj->card & 0xFF);
    SzDuel_GetUnitLoc(obj->card >> 8, obj->card & 0xFF);
    switch (SzDuel_GetUnitCardNo(obj->card >> 8, obj->card & 0xFF)) {
    case 0x2E9:
        pos = SzDuel_GetUnitLoc(obj->card >> 8, obj->card & 0xFF);
        obj->state = 0x6FF;
        if ((pos >> 8) < 3) {
            obj->target.word = obj->target.bits.lower | 0x03010000;
        } else {
            obj->target.word = obj->target.bits.lower | 0x05020000;
        }
        break;
    case 0x2B2:
        obj->state = 0x6FF;
        obj->target.word = obj->target.bits.lower | 0x04050000;
        break;
    case 0x2AD:
        obj->state = 0xCFF;
        obj->target.word = obj->target.bits.lower | 0xFFFF0000;
        break;
    default:
        obj->state = 0x5FF;
        break;
    }
}

typedef struct {
    s16 id;
    u8 unk2;
    u8 pad3;
    s16 unk4;
    u8 pad6[6];
    s32 unkC;
} Ctx_00127E30;

typedef struct {
    u8 pad0[0x3C];
    u16 unk3C;
    u8 pad3E[0x22];
} Work_00127E30;

s32 TaLogic_GetNearCard2(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8,
                  s32 arg9);

/* The summon task for side `nSide`: which hand cards to play and where, into `pInput`; -1 when it plays none. */
s32 TaLogic_GetMinimumTask_Summon_00127E30(s32 wUnit, s32 nSide, s32 pInput) {
    extern s32 TaLogic_GetUnitNum(s32, s32);
    Work_00127E30 work;
    s32 ret;
    s32 res;
    s32 pos;
    s32 kind;
    Ctx_00127E30 *ctx = (Ctx_00127E30 *)pInput;

    ctx->id = wUnit;
    if (SzDuel_InqHandPhase(nSide) == 0) {
        return -1;
    }
    if (TaLogic_GetUnitNum(nSide, 0) == 5 && TaLogic_GetUnitNum(nSide, 1) == 5) {
        return -1;
    }
    kind = TaLogic006_IsHandPlay(nSide, &work);
    if (kind < 0) {
        return -1;
    }
    ctx->unk2 = 10;
    ctx->unkC = 0;
    pos = SzDuel_GetUnitLoc(wUnit >> 8, wUnit & 0xFF);
    if (kind == 0) {
        if (TaLogic006_SetComboQue(nSide, (u8 *)ctx, &work) >= 0) {
            ret = TaLogic_GetNearCard2(&work, pos & 0xFF, pos >> 8, nSide == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, TaLogic_GetWarnHideLvl_0012B1B0(nSide));
            if (ret < 0) {
                if (SzDuel_GetUnitMonsterCount(nSide) < 5) {
                    res = TaLogic006_GetSummonPiece(nSide, kind, &work, ret);
                    if (res < 0) {
                        return -1;
                    }
                    ctx->unk4 = res;
                    return 1;
                }
            } else {
                res = TaLogic006_GetSummonPiece(nSide, kind, &work, ret);
                if (res < 0) {
                    return -1;
                }
                ctx->unk4 = res;
                return 1;
            }
        }
    } else {
        ret = TaLogic_GetNearCard2(&work, pos & 0xFF, pos >> 8, nSide == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, TaLogic_GetWarnHideLvl_0012B1B0(nSide));
    }
    if (kind == 2) {
        TaLogic006_SetSpecialComboQue(nSide, ctx, &work);
        res = TaLogic006_GetSummonPiece(nSide, kind, &work, ret);
        if (res < 0) {
            return -1;
        }
        ctx->unk4 = res;
        return 1;
    }
    if (TaLogic006_GetSpellPlay(nSide, (u8 *)ctx, &work, work.unk3C) < 0) {
        return -1;
    }
    res = TaLogic006_GetSummonPiece(nSide, kind, &work, ret);
    if (res < 0) {
        return -1;
    }
    ctx->unk4 = res;
    return 1;
}

/* Whether side `nSide` should play from its hand this turn (and what, into `pInput`). */
s32 TaLogic006_IsHandPlay(s32 nSide, void *pInput) {
    extern s32 TaLogic_GetUnitNum();
    extern s32 func_0012B000();
    s32 cards[8];
    u8 buffer[32];
    u8 type0;
    u8 type1;
    s32 result;
    s32 value;

    type0 = TaLogic_GetUnitNum(nSide, 0);
    type1 = TaLogic_GetUnitNum(nSide, 1);
    if (pInput == NULL) {
        return -1;
    }
    TaHand_GetNextHand(nSide, cards);
    if (type0 == 5) {
        if (TaLogic006_GetSpellPlay(nSide, buffer, pInput, 999) >= 0) {
            return 1;
        }
        return -1;
    }
    if (type1 == 5) {
        s32 i = 0;
        s32 *p;
        if (i < TaHand_GetNextHandNum(nSide)) {
            p = cards;
            do {
                if ((TaHand_GetCardKind(*p) >> 5) == 0 && TaHand_IsCardSummon2(nSide, *p) == 1) {
                    SzDuel_InitCardInfo(pInput, cards[i]);
                    return 0;
                }
                p++;
                i++;
            } while (i < TaHand_GetNextHandNum(nSide));
        }
        return -1;
    }
    if (TaLogic006_GetSpecCardPlay(nSide, buffer, pInput, 699) >= 0) {
        if (TaLogic_IsAttackedNow(nSide, 0, 0) == 1 || func_0012B000(nSide) == 1) {
            return 2;
        }
    }
    if (TaLogic006_GetSpecCardPlay(nSide, buffer, pInput, 108) >= 0) {
        return 2;
    }
    value = TaLogic_GetMaxAPGraveCard(nSide, 3);
    if (value >= 0) {
        if ((u16)value >= 2400 && TaLogic006_GetSpecCardPlay(nSide, buffer, pInput, 685) >= 0) {
            return 2;
        }
    }
    if (TaLogic006_GetSpecCardPlay(nSide, buffer, pInput, 851) >= 0 && TaLogic006_IsDoCerem(nSide, 851) == 1) {
        return 2;
    }
    if (type0 == 0) {
        s32 *p;
        s32 i = 0;
        if (i < TaHand_GetNextHandNum(nSide)) {
            p = cards;
            do {
                if ((TaHand_GetCardKind(*p) >> 5) == 0 && TaHand_IsCardSummon2(nSide, *p) == 1) {
                    return 0;
                }
                p++;
                i++;
            } while (i < TaHand_GetNextHandNum(nSide));
        }
    }
    {
        s32 *p;
        s32 i = 0;
        if (i < TaHand_GetNextHandNum(nSide)) {
            p = cards;
            do {
                if ((TaHand_GetCardKind(*p) >> 5) == 0 && TaHand_IsCardSummon2(nSide, *p) == 1) {
                    SzDuel_InitCardInfo(pInput, cards[i]);
                    return 0;
                }
                p++;
                i++;
            } while (i < TaHand_GetNextHandNum(nSide));
        }
    }
    result = TaLogic006_GetSpellPlay(nSide, buffer, pInput, 999);
    if (result >= 0) {
        return result;
    }
    return -1;
}

/* Whether side `nSide` holds card `nCardNo` and can summon it (its slot into `bCombo`, the card into `pCardInfo`);
   returns its kind group or -1. */
s32 TaLogic006_GetSpecCardPlay(s32 nSide, void *bCombo, void *pCardInfo, s32 nCardNo) {
    s32 index;
    s32 *entry;
    s32 target;
    s32 entries[8];

    TaHand_GetNextHand(nSide, entries);
    index = 0;
    if (index < TaHand_GetNextHandNum(nSide)) {
        target = nCardNo & 0xFFFF;
        entry = entries;
        do {
            if (target == *entry && TaHand_IsCardSummon2(nSide, *entry) == 1) {
                *((s8 *)bCombo + 6) = index;
                SzDuel_InitCardInfo(pCardInfo, entries[index]);
                return TaHand_GetCardKind(entries[index]) >> 5;
            }
            entry++;
            index++;
        } while (index < TaHand_GetNextHandNum(nSide));
    }
    return -1;
}

/* Whether side `nSide` plays a magic or ritual card from its hand now (its slot into `bCombo`, the card into
   `pCardInfo`). */
s32 TaLogic006_GetSpellPlay(s32 nSide, u8 *bCombo, void *pCardInfo, s32 nMode) {
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

typedef struct Info_00128720 {
    u8 pad00[8];
    u16 x;
    s16 y;
} Info_00128720;

typedef struct Sprite_00128720 {
    Info_00128720 *info;
    u8 pad04[0x34];
    s16 x;
    s16 y;
} Sprite_00128720;


/* Fills hand combination `bCombo` for side `nSide`: the best fusion or equip chain, its card into `pCardInfo`. */
s32 TaLogic006_SetComboQue(s32 nSide, u8 *bCombo, void *pCardInfo) {
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
                            TaLogic_ConvEmptyCombo_00128900(nSide, *node, entries);
                            TaLogic_CopyArray((u8 *)*node + 2, bCombo + 6);
                            SzDuel_InitCardInfo(pCardInfo, **node);
                            ((Sprite_00128720 *)pCardInfo)->x = (value >> 16) - (((Sprite_00128720 *)pCardInfo)->info->x & 0x1FFF);
                            ((Sprite_00128720 *)pCardInfo)->y = (value & 0xFFFF) - (((Sprite_00128720 *)pCardInfo)->info->y & 0x1FFF);
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
} Info_00128900;

/* Fills an empty combination: the hand card side `nSide` can summon with the best attack plus defence. */
void TaLogic_ConvEmptyCombo_00128900(s32 nSide, void *pCardInfo, s32 *pResult) {
    Info_00128900 *info = pCardInfo;
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
                if (card != 0x3E7 && TaLogic006_IsRefuseEmptyCombo(card) == 0 && level >= TaHand_GetCardSummonCost2(card, nSide)) {
                    cost = TaHand_GetCardAPDP(card);
                    if ((cost & 0xFFFF) + (cost >> 16) * 2 < 0xCE5 && TaHand_IsCardEffect(card) == 2 &&
                        (u16)TaLogic_GetHandFusion(info->id, (u16)card) == 0x3E7) {
                        TaLogic_AddEmptyCombo(info->values, buf[i]);
                    }
                }
            }
        }
    }
}

/* Whether this duelist keeps card `nCardNo` out of a summon (it is wanted for an equip). */
s32 TaLogic006_IsRefuseEmptyCombo(s32 nCardNo) {
    if ((TaHand_GetCardKind(nCardNo) >> 5) != 0) {
        return 1;
    }
    if (nCardNo == 0x6C || nCardNo == 0x6F || nCardNo == 0x68) {
        return 1;
    }
    return 0;
}

typedef struct {
    u8 pad0[6];
    u8 slot[5];
} Obj1_00128B50;

typedef struct {
    u8 pad0[0x3C];
    u16 id;
} Obj2_00128B50;

/* Fills hand combination `bCombo` for side `nSide` with this duelist's special combination, its card into
   `pCardInfo`. */
s32 TaLogic006_SetSpecialComboQue(s32 nSide, void *bCombo, void *pCardInfo) {
    Obj1_00128B50 *o1 = bCombo;
    Obj2_00128B50 *o2 = pCardInfo;
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
            if (o2->id == list[i] && TaHand_IsCardSummon2(nSide, list[i]) == 1) {
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

typedef struct Nibbles_00128D40 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_00128D40;

/* The square side `nSide` summons a card of kind `sKind` to. */
s32 TaLogic006_GetSummonPiece(s32 nSide, u8 sKind, void *pInput, s32 nMode) {
    extern s32 TaLogic_IsUnitWin4();
    extern s32 TaLogic_GetInvadeRoot2();
    extern s32 TaLogic_GetRoot2(s32, s32, s32, s32, s32, s32, u16, u8);
    s32 best;
    s32 bestCost;
    s32 candidate;
    Nibbles_00128D40 flags[12];
    s32 i;
    Nibbles_00128D40 *p;
    u8 kind;

    if (pInput == NULL) {
        return -1;
    }
    p = flags;
    i = 0;
    do {
        p->low = p->high = 15;
        p++;
        i++;
    } while (i < 12);

    kind = *(u8 *)((u8 *)pInput + 0x3E) >> 5;
    if (kind == 0) {
        if (nMode >= 0) {
            s32 y;
            s32 x;
            s32 index;
            s32 originY;
            s32 originX;
            s32 origin;
            s32 cost;

            bestCost = 255;
            best = 65535;
            origin = SzDuel_GetUnitLoc(nMode >> 8, nMode & 255);
            index = 0;
            originY = origin >> 8;
            originX = origin & 255;
            do {
                candidate = Ta_GetSommonPiecePreference(nSide, index);
                if (candidate >= 0) {
                    x = candidate & 255;
                    y = candidate >> 8;
                    if (SzDuel_GetField(x, y) != 8 &&
                        (SzDuel_GetField(x, y) != 9 ||
                         Ta_IsVirus_Chk3(pInput, x, y) != 1) &&
                        SzDuel_GetMapUnit(x, y) == 0) {
                        if (TaLogic_IsUnitWin4(pInput, nMode, TaLogic_GetWarnHideLvl_0012B1B0(nSide),
                                         originX, originY, 0) > 0) {
                            cost = TaLogic_GetInvadeRoot2(pInput, flags, x, y,
                                                originX, originY, nMode, 0,
                                                5, (u16)TaLogic_GetWarnHideLvl_0012B1B0(nSide));
                        } else {
                            cost = TaLogic_GetRoot2((s32)pInput, (s32)flags, x, y,
                                                originX, originY, nMode, 5);
                        }
                        if (TaLogic_GetMinGoalCount((u8 *)flags) > 0 && cost < bestCost) {
                            bestCost = cost;
                            best = candidate;
                        }
                    }
                }
                index++;
            } while (index < 8);
            if (best != 65535) {
                return best;
            }
            best = -1;
            return best;
        }
        {
            s32 maxY;
            s32 maxX;
            s32 y;
            s32 x;
            s32 minY;
            s32 minX;
            s32 origin;

            bestCost = 14;
            best = -1;
            i = 0;
            do {
                candidate = Ta_GetSommonPiecePreference(nSide, i);
                if (candidate >= 0) {
                    x = candidate & 255;
                    y = candidate >> 8;
                    if (SzDuel_GetField(x, y) != 8 &&
                        (SzDuel_GetField(x, y) != 9 ||
                         Ta_IsVirus_Chk3(pInput, x, y) != 1) &&
                        SzDuel_GetMapUnitID(x, y) < 0) {
                        if (y < 3) {
                            minY = y < 3 ? y : 3;
                            maxY = y > 3 ? y : 3;
                            minX = x < 1 ? x : 1;
                            maxX = x > 1 ? x : 1;
                            (void)maxX; /* a use between the clamp and the distance keeps maxX's temp, so y and x take s0/s1 as in the original */
                            origin = (maxX - minX) + (maxY - minY);
                        } else {
                            minY = y < 5 ? y : 5;
                            maxY = y > 5 ? y : 5;
                            minX = x < 2 ? x : 2;
                            maxX = x > 2 ? x : 2;
                            (void)maxX; /* a use between the clamp and the distance keeps maxX's temp, so y and x take s0/s1 as in the original */
                            origin = (maxX - minX) + (maxY - minY);
                        }
                        if (origin < bestCost && origin >= 0) {
                            best = candidate;
                            bestCost = origin;
                        }
                    }
                }
                i++;
            } while (i < 8);
            if (bestCost < 14) {
                return best;
            }
        }
    } else {
        s32 y;
        s32 x;
        s32 index;
        s32 last;
        s32 candidate;

        last = -1;
        index = 0;
        do {
            candidate = Ta_GetSommonPiecePreference(nSide, index);
            if (candidate >= 0) {
                x = candidate & 255;
                y = candidate >> 8;
                if (SzDuel_GetField(x, y) != 8 &&
                    (SzDuel_GetField(x, y) != 9 ||
                     Ta_IsVirus_Chk3(pInput, x, y) != 1) &&
                    SzDuel_GetMapUnitID(x, y) < 0 && y < 8) {
                    last = candidate;
                }
            }
            index++;
        } while (index < 8);
        if (last >= 0) {
            return last;
        }
    }
    return -1;
}

typedef struct {
    u8 low : 4;
    u8 high : 4;
} Flags_001291C0;

typedef struct {
    u16 id;
    u8 action;
    u8 pad3;
    u16 position;
    u8 pad6[6];
    s32 value;
    u8 mode;
} Output_001291C0;


/* The task of a unit running from danger (task `pTask`): the safest square in reach, into `pInput` (`fFirst` = 1
   for the unit's first-choice task). */
s32 TaLogic_GetMinimumTask_RunMission_001291C0(u16 *pTask, s32 nSide, void *pInput, u8 fFirst) {
    extern s32 TaLogic_IsRunPassRoot(s32, s32, s32, s32, s32, s32, void *, u8);
    extern s32 TaLogic_IsOpenUnit_0012B210();
    s32 position;
    u8 upperX;
    u8 flag;
    Flags_001291C0 cells[12];
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
    Output_001291C0 *out = pInput;

    position = SzDuel_GetUnitLoc(*pTask >> 8, *pTask & 0xFF);
    i = 0;
    do {
        cells[i].low = cells[i].high = 15;
        i++;
    } while (i < 12);

    {
        u16 value = (u16)TaLogic_GetWarnHideLvl_0012B1B0(nSide);
        originalX = position & 0xFF;
        originalY = position >> 8;
        if (TaLogic_GetUnitWarning(originalX, originalY, *pTask, 3, value, 0) == 0) {
            out->id = *pTask;
            out->action = 6;
            out->position = position;
            out->mode = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, out->position, 1, 0);
            out->value = TaLogic_IsOpenUnit_0012B210(*pTask >> 8, *pTask & 0xFF, pTask);
            TaLogic006_InitRogicControl(pTask, fFirst);
            return 0;
        } else {
            result = GetMoveRev(SzDuel_GetUnit(*pTask >> 8, *pTask & 0xFF), originalX, originalY);
            if (result == 0) {
                out->id = *pTask;
                out->action = 6;
                out->position = position;
                out->mode = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, out->position, 1, 0);
                out->value = TaLogic_IsOpenUnit_0012B210(*pTask >> 8, *pTask & 0xFF, pTask);
                TaLogic006_InitRogicControl(pTask, fFirst);
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
                                value = (u16)TaLogic_GetWarnHideLvl_0012B1B0(nSide);
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
                        out->mode = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, out->position, 0, 0);
                    }
                    out->value = TaLogic_IsOpenUnit_0012B210(*pTask >> 8, *pTask & 0xFF, pTask);
                } else {
                    out->id = *pTask;
                    out->action = 6;
                    out->position = position;
                    out->mode = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, out->position, 1, 0);
                    out->value = TaLogic_IsOpenUnit_0012B210(*pTask >> 8, *pTask & 0xFF, pTask);
                }
                TaLogic006_InitRogicControl(pTask, fFirst);
            }
        }
    }
    return 0;
}

typedef struct Coord_00129700 {
    u8 x : 4;
    u8 y : 4;
} Coord_00129700;

typedef struct Result_00129700 {
    u16 card;
    u8 action;
    u8 pad03;
    u16 position;
    u8 pad06[6];
    s32 count;
    u8 flags;
} Result_00129700;


/* The task of reviving a monster from the graveyard (task `pTask`), into `pInput` (`fFirst` = 1 for the unit's
   first-choice task). */
s32 TaLogic_GetMinimumTask_ReviveMission_00129700(void *pTask, s32 nSide, s32 pInput, u8 fFirst) {
    extern s32 TaLogic_IsRunPassRoot(s32, s32, s32, s32, s32, s32, void *, u8);
    Coord_00129700 positions[12];
    s32 i;
    Coord_00129700 *p;
    s32 position;

    position = SzDuel_GetUnitLoc(*(u16 *)pTask >> 8, *(u16 *)pTask & 0xFF);
    p = positions;
    i = 0;
    do {
        p->x = p->y = 15;
        i++;
        p++;
    } while (i < 12);
    if (TaLogic_IsOpenUnit_0012B210(*(u16 *)pTask >> 8, *(u16 *)pTask & 0xFF, pTask) == 1) {
        s32 data;
        s32 card;
        s32 player;

        data = TaLogic_GetMaxAPGraveCard(nSide, 3);
        player = data >> 24;
        card = TaLogic_GetGraveEntryAfterScreen(player & 0xFF, (data >> 16) & 0xFF, 29);
        ((Result_00129700 *)pInput)->card = *(u16 *)pTask;
        ((Result_00129700 *)pInput)->action = 12;
        ((Result_00129700 *)pInput)->flags = TaLogic_IsDefStyleUnit(*(u16 *)pTask >> 8, *(u16 *)pTask & 0xFF, *(u16 *)(pInput + 4), 1, 0);
        ((Result_00129700 *)pInput)->count = 1;
        *(u16 *)(pInput + 4) = ((player & 15) << 8) | card;
        TaLogic006_InitRogicControl(pTask, fFirst);
        return 0;
    }
    if (SzDuel_GetUnitStatus(*(u16 *)pTask >> 8, *(u16 *)pTask & 0xFF, 4) != 0) {
        SzDuel_SetUnitStatus(*(u16 *)pTask >> 8, *(u16 *)pTask & 0xFF, 0, 1);
        ((Result_00129700 *)pInput)->card = *(u16 *)pTask;
        ((Result_00129700 *)pInput)->action = 14;
        return 0;
    }
    {
        s32 y;
        s32 cost;
        s32 packedY;
        s32 minY;
        s32 minX;
        s32 maxY;
        s32 centerY;
        s32 centerX;
        s32 x;
        s32 bestPosition;
        s32 bestCost;
        u8 maxX;
        u8 flags;
        s32 bound;
        s32 rangeResult;
        u16 card;

        card = TaLogic_GetWarnHideLvl_0012B1B0(nSide);
        centerX = position & 0xFF;
        centerY = position >> 8;
        if (TaLogic_GetUnitWarning(centerX, centerY, *(u16 *)pTask, 3, card, 0) == 0) {
            ((Result_00129700 *)pInput)->card = *(u16 *)pTask;
            ((Result_00129700 *)pInput)->action = 6;
            *(u16 *)(pInput + 4) = position;
            ((Result_00129700 *)pInput)->flags = TaLogic_IsDefStyleUnit(*(u16 *)pTask >> 8, *(u16 *)pTask & 0xFF, *(u16 *)(pInput + 4), 1, 0);
            ((Result_00129700 *)pInput)->count = 2;
            TaLogic006_InitRogicControl(pTask, fFirst);
        } else {
            rangeResult = GetMoveRev(SzDuel_GetUnit(*(u16 *)pTask >> 8, *(u16 *)pTask & 0xFF), centerX, centerY);
            if (rangeResult == 0) {
                ((Result_00129700 *)pInput)->card = *(u16 *)pTask;
                ((Result_00129700 *)pInput)->action = 6;
                *(u16 *)(pInput + 4) = position;
                ((Result_00129700 *)pInput)->flags = TaLogic_IsDefStyleUnit(*(u16 *)pTask >> 8, *(u16 *)pTask & 0xFF, *(u16 *)(pInput + 4), 1, 0);
                ((Result_00129700 *)pInput)->count = 2;
                TaLogic006_InitRogicControl(pTask, fFirst);
                return 0;
            } else {
                bestPosition = 0xFF;
                bestCost = 0xFFFF;
                minX = (u8)GetCap(0, centerX - (rangeResult & 15));
                bound = centerX + (rangeResult & 15);
                if (bound >= 7) {
                    maxX = 6;
                } else {
                    maxX = (u8)bound;
                }
                minY = (u8)GetCap(0, centerY - (rangeResult & 15));
                bound = centerY + (rangeResult & 15);
                if (bound >= 7) {
                    bound = 6;
                }
                maxY = (u8)bound;
                if ((*(u16 *)pTask & 0xFF) == 0) {
                    flags = (u8)TaLogic_IsAttackedNow(*(u16 *)pTask >> 8, *(u16 *)pTask & 0xFF, 0);
                } else {
                    flags = 0;
                }
                for (x = (u8)minX; x <= (u8)maxX; x++) {
                    for (y = (u8)minY, packedY = y << 8; y <= (u8)maxY; packedY += 0x100, y++) {
                        if (((x < centerX ? centerX : x) - (centerX < x ? centerX : x)) +
                            ((y < centerY ? centerY : y) - (centerY < y ? centerY : y)) <= (rangeResult & 15)) {
                            if (TaLogic_IsRunPassRoot(*(u16 *)pTask >> 8, *(u16 *)pTask & 0xFF, centerX, centerY, x, y, pTask, (u8)flags) == 1 &&
                                (TaLogic_IsAttackedNow2(*(u16 *)pTask >> 8, *(u16 *)pTask & 0xFF, x, y, 0) == 0 || (u8)*(u16 *)pTask == 0)) {
                                card = TaLogic_GetWarnHideLvl_0012B1B0(nSide);
                                cost = TaLogic_GetUnitWarning(x, y, *(u16 *)pTask, 3, card, 0);
                                if (cost < bestCost) {
                                    bestCost = cost;
                                    bestPosition = packedY | x;
                                } else if (cost == bestCost && SzDuel_GetMapUnit(x, y) == 0 &&
                                           SzDuel_GetMapUnit(bestPosition & 0xFF, bestPosition >> 8) != 0) {
                                    bestCost = cost;
                                    bestPosition = packedY | x;
                                }
                            }
                        }
                    }
                }
                if (bestPosition != 0xFF) {
                    ((Result_00129700 *)pInput)->card = *(u16 *)pTask;
                    ((Result_00129700 *)pInput)->action = 6;
                    *(u16 *)(pInput + 4) = bestPosition;
                    if (bestPosition == position) {
                        ((Result_00129700 *)pInput)->flags = TaLogic_IsDefStyleUnit(*(u16 *)pTask >> 8, *(u16 *)pTask & 0xFF, *(u16 *)(pInput + 4), 1, 0);
                    } else {
                        ((Result_00129700 *)pInput)->flags = TaLogic_IsDefStyleUnit(*(u16 *)pTask >> 8, *(u16 *)pTask & 0xFF, *(u16 *)(pInput + 4), 0, 0);
                    }
                    ((Result_00129700 *)pInput)->count = 2;
                } else {
                    ((Result_00129700 *)pInput)->card = *(u16 *)pTask;
                    ((Result_00129700 *)pInput)->action = 6;
                    *(u16 *)(pInput + 4) = position;
                    ((Result_00129700 *)pInput)->flags = TaLogic_IsDefStyleUnit(*(u16 *)pTask >> 8, *(u16 *)pTask & 0xFF, *(u16 *)(pInput + 4), 1, 0);
                    ((Result_00129700 *)pInput)->count = 2;
                }
                TaLogic006_InitRogicControl(pTask, fFirst);

            }
        }
    }
    return 0;
}

typedef struct {
    u16 position;
    u8 pad2[6];
    u32 targets;
} Input_00129D00;

typedef struct {
    u16 position;
    s8 action;
    u8 pad3;
    u16 destination;
    u8 pad6[6];
    s32 result;
    s8 status;
} Output_00129D00;

typedef struct {
    u8 x : 4;
    u8 y : 4;
} Point_00129D00;


#define TARGET_00129D00(in, mode) ((mode) == 1 ? (u16)((in)->targets >> 16) : (in)->targets & 0xFFFF)

/* The task of a unit attacking (task `pTask`): its path to the goal, into `pInput`; -1 when it has none (`fFirst`
   = 1 for the unit's first-choice task). */
s32 TaLogic_GetMinimumTask_AtkMission_00129D00(void *pTask, s32 nSide, void *pInput, u8 fFirst) {
    extern void TaLogic_GetInvadeRoot();
    Input_00129D00 *in = pTask;
    Output_00129D00 *out = pInput;
    s32 sourcePosition;
    s32 count;
    s32 sourceY;
    s32 sourceX;
    s32 found;
    Point_00129D00 points[12];
    s32 targetPosition;
    s32 i;
    Point_00129D00 *p;

    if (SzDuel_GetUnit(TARGET_00129D00(in, fFirst) >> 8, TARGET_00129D00(in, fFirst) & 0xFF) == 0) {
        TaLogic_InitRogicControl(pTask, 1);
        return -1;
    } else {
        s32 initialResult;
        initialResult = TaLogic_IsOpenUnit_0012B210(in->position >> 8, in->position & 0xFF, pTask);
        sourcePosition = SzDuel_GetUnitLoc(in->position >> 8, in->position & 0xFF);
        targetPosition = SzDuel_GetUnitLoc(TARGET_00129D00(in, fFirst) >> 8, TARGET_00129D00(in, fFirst) & 0xFF);
        p = points;
        i = 0;
        do {
            p->x = p->y = 15;
            p++;
            i++;
        } while (i < 12);
        if (GetMoveRev(SzDuel_GetUnit(in->position >> 8, in->position & 0xFF),
                          sourceX = sourcePosition & 0xFF, sourceY = sourcePosition >> 8) == 0) {
            s32 score;
            out->position = in->position;
            out->action = 6;
            out->destination = sourcePosition;
            score = TaLogic_GetUnitWarning(sourceX, sourceY, nSide, 3, 1, (u8)TaLogic_GetWarnHideLvl_0012B1B0(nSide));
            if (score >= SzDuel_GetUnitAP(in->position >> 8, in->position & 0xFF, 0)) {
                out->status = TaLogic_IsDefStyleUnit(in->position >> 8, in->position & 0xFF, out->destination, 1, 0);
            } else {
                out->status = TaLogic_IsDefStyleUnit(in->position >> 8, in->position & 0xFF, out->destination, 0, 0);
            }
            TaLogic006_InitRogicControl(pTask, fFirst);
            return 0;
        } else {
            s32 targetY;
            s32 targetX;
            Point_00129D00 *candidate;
            s32 index;
            s32 bestScore;
            s32 bestIndex;
            s32 position = in->position;
            u16 value = TaLogic_GetWarnHideLvl_0012B1B0(nSide);
            TaLogic_GetInvadeRoot(position >> 8, position & 0xFF, points, sourceX, sourceY,
                           targetX = targetPosition & 0xFF, targetY = targetPosition >> 8,
                           TARGET_00129D00(in, fFirst), 0, 30, value);
            count = TaLogic_GetMinGoalCount((u8 *)points);
            bestIndex = 0xFF;
            if (count > 0) {
                found = 0;
                bestScore = 0xFFFF;
                for (index = 0; index < count; index++) {
                    if (TaLogic006_IsOpenMoveUnit(in->position >> 8, in->position & 0xFF,
                                      sourceX, sourceY, targetX, targetY) == 1) {
                        bestIndex = index;
                        found = 1;
                        points[index].x = targetX;
                        points[index].y = targetY;
                        index = count;
                    } else {
                        s32 score;
                        candidate = &points[index];
                        score = TaLogic_GetUnitWarning(candidate->x, candidate->y, nSide, 5, 1,
                                              (u8)TaLogic_GetWarnHideLvl_0012B1B0(nSide));
                        if (score < bestScore) {
                            bestScore = score;
                            bestIndex = index;
                        } else if (score == bestScore) {
                            if ((((targetX < candidate->x ? candidate->x : targetX) - (candidate->x < targetX ? candidate->x : targetX)) +
                                 ((targetY < candidate->y ? candidate->y : targetY) - (candidate->y < targetY ? candidate->y : targetY))) <
                                (((targetX < points[bestIndex].x ? points[bestIndex].x : targetX) - (points[bestIndex].x < targetX ? points[bestIndex].x : targetX)) +
                                 ((targetY < points[bestIndex].y ? points[bestIndex].y : targetY) - (points[bestIndex].y < targetY ? points[bestIndex].y : targetY)))) {
                                bestScore = score;
                                bestIndex = index;
                            }
                        }
                    }
                }
            } else {
                out->position = in->position;
                out->action = 6;
                out->destination = sourcePosition;
                out->result = initialResult;
                out->status = TaLogic_IsDefStyleUnit(in->position >> 8, in->position & 0xFF, out->destination, 0, 0);
                TaLogic_InitRogicControl(pTask, fFirst);
                return 0;
            }
            if (bestIndex != 0xFF) {
                out->position = in->position;
                out->action = 6;
                out->destination = (points[bestIndex].y << 8) | points[bestIndex].x;
                out->result = found;
                out->status = TaLogic_IsDefStyleUnit(in->position >> 8, in->position & 0xFF, out->destination, 0, 0);
            } else {
                out->position = in->position;
                out->action = 6;
                out->destination = sourcePosition;
                out->result = found;
                out->status = TaLogic_IsDefStyleUnit(in->position >> 8, in->position & 0xFF, out->destination, 0, 0);
                TaLogic_InitRogicControl(pTask, fFirst);
                return 0;
            }
        }
    }
    return 0;
}

typedef struct Coord_0012A2E0 {
    u8 x : 4;
    u8 y : 4;
} Coord_0012A2E0;

typedef struct Unit_0012A2E0 {
    u16 position;
    u8 pad2[6];
    union {
        u32 packed;
        u16 low;
    } target;
} Unit_0012A2E0;

typedef struct Output_0012A2E0 {
    u16 position;
    u8 kind;
    u8 pad3;
    u16 target;
    u8 pad6[6];
    s32 value;
    u8 flag;
} Output_0012A2E0;


/* The task's target square: the second half-word when the second argument is 1, else the first. */
static inline u32 target_0012A2E0(void *unit, s32 side) {
    return side == 1 ? (u32)(u16)(((Unit_0012A2E0 *)unit)->target.packed >> 16) : (u32)((Unit_0012A2E0 *)unit)->target.low;
}

/* The smaller of the two values. */
static inline u32 minY_0012A2E0(void *unit, s32 side, u8 coord) {
    return coord < (target_0012A2E0(unit, side) >> 8) ? coord : (target_0012A2E0(unit, side) >> 8);
}

/* The larger of the two values. */
static inline u32 maxY_0012A2E0(void *unit, s32 side, u8 coord) {
    return (target_0012A2E0(unit, side) >> 8) < coord ? coord : (target_0012A2E0(unit, side) >> 8);
}

/* The smaller of the two values. */
static inline u32 minX_0012A2E0(void *unit, s32 side, u8 coord) {
    return coord < (target_0012A2E0(unit, side) & 0xFF) ? coord : (target_0012A2E0(unit, side) & 0xFF);
}

/* The larger of the two values. */
static inline u32 maxX_0012A2E0(void *unit, s32 side, u8 coord) {
    return (target_0012A2E0(unit, side) & 0xFF) < coord ? coord : (target_0012A2E0(unit, side) & 0xFF);
}

/* The task of a unit moving to its goal (task `pTask`), into `pInput` (`fFirst` = 1 for the unit's first-choice
   task). */
s32 TaLogic_GetMinimumTask_MoveMission_0012A2E0(void *pTask, s32 nSide, void *pInput, u8 fFirst, u8 nKind) {
    extern s32 TaLogic_GetUnitWarning();
    extern void TaLogic_GetRoot();
    extern s32 TaLogic_IsDefStyleUnit(s32, s32, s32, u8, s32);
    Coord_0012A2E0 coords[12];
    s32 initial;
    s32 cell;
    s32 count;

    initial = SzDuel_GetUnitLoc(((Unit_0012A2E0 *)pTask)->position >> 8, ((Unit_0012A2E0 *)pTask)->position & 0xFF);
    {
    s32 bestScore;
    s32 best;
    s32 side = fFirst;
    Coord_0012A2E0 *candidate;
    s32 index;
    if (target_0012A2E0(pTask, side) == 0xFFFF) {
        if (initial == target_0012A2E0(pTask, side)) {
            ((Output_0012A2E0 *)pInput)->position = ((Unit_0012A2E0 *)pTask)->position;
            ((Output_0012A2E0 *)pInput)->kind = 6;
            ((Output_0012A2E0 *)pInput)->target = initial;
            ((Output_0012A2E0 *)pInput)->flag = TaLogic_IsDefStyleUnit(((Unit_0012A2E0 *)pTask)->position >> 8, ((Unit_0012A2E0 *)pTask)->position & 0xFF, ((Output_0012A2E0 *)pInput)->target, nKind, 0);
            ((Output_0012A2E0 *)pInput)->value = TaLogic_IsOpenUnit_0012B210(((Unit_0012A2E0 *)pTask)->position >> 8, ((Unit_0012A2E0 *)pTask)->position & 0xFF, pTask);
            TaLogic006_InitRogicControl(pTask, fFirst);
            return 0;
        }
    }

    candidate = coords;
    {
        s32 i = 0;
        Coord_0012A2E0 *entry = candidate;
        do {
            entry->x = entry->y = 0xF;
            i++;
            entry++;
        } while (i < 12);
    }

    cell = SzDuel_GetMapUnitID(target_0012A2E0(pTask, side) & 0xFF, ((u32)target_0012A2E0(pTask, side)) >> 8);
    if (cell < 0) {
        cell = 0xFFFF;
    }
    TaLogic_GetRoot(((Unit_0012A2E0 *)pTask)->position >> 8, ((Unit_0012A2E0 *)pTask)->position & 0xFF,
                 coords, initial & 0xFF, initial >> 8, target_0012A2E0(pTask, side) & 0xFF,
                 ((u32)target_0012A2E0(pTask, side)) >> 8, (u16)cell, 7);
    count = TaLogic_GetMinGoalCount((u8 *)coords);
    {
        if (count > 0) {
        best = 0xFF;
        bestScore = 0xFFFF;
        for (index = 0; index < count; index++) {
                if (SzDuel_GetMapUnit(candidate->x, candidate->y) == 0) {
                    s32 score = TaLogic_GetUnitWarning(candidate->x, candidate->y, nSide, 5, 1, (u8)TaLogic_GetWarnHideLvl_0012B1B0(nSide));
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
                        bestMinY = minY_0012A2E0(pTask, side, bestY);
                        bestMaxY = maxY_0012A2E0(pTask, side, bestY);
                        bestX = (&coords[best])->x;
                        bestMinX = minX_0012A2E0(pTask, side, bestX);
                        bestMaxX = maxX_0012A2E0(pTask, side, bestX);
                        currentY = (u8)candidate->y;
                        currentMinY = minY_0012A2E0(pTask, side, currentY);
                        currentMaxY = maxY_0012A2E0(pTask, side, currentY);
                        currentX = candidate->x;
                        currentMinX = minX_0012A2E0(pTask, side, currentX);
                        currentMaxX = maxX_0012A2E0(pTask, side, currentX);
                        if ((currentMaxX - currentMinX) + (currentMaxY - currentMinY) < (bestMaxX - bestMinX) + (bestMaxY - bestMinY)) {
                            bestScore = score;
                            best = index;
                        }
                    }
                }
            candidate++;
        }
    } else {
        ((Output_0012A2E0 *)pInput)->position = ((Unit_0012A2E0 *)pTask)->position;
            ((Output_0012A2E0 *)pInput)->kind = 6;
            ((Output_0012A2E0 *)pInput)->target = initial;
            ((Output_0012A2E0 *)pInput)->flag = TaLogic_IsDefStyleUnit(((Unit_0012A2E0 *)pTask)->position >> 8, ((Unit_0012A2E0 *)pTask)->position & 0xFF, ((Output_0012A2E0 *)pInput)->target, nKind, 0);
            ((Output_0012A2E0 *)pInput)->value = TaLogic_IsOpenUnit_0012B210(((Unit_0012A2E0 *)pTask)->position >> 8, ((Unit_0012A2E0 *)pTask)->position & 0xFF, pTask);
        TaLogic006_InitRogicControl(pTask, fFirst);
        return 0;
    }

        if (best != 0xFF) {
            ((Output_0012A2E0 *)pInput)->position = ((Unit_0012A2E0 *)pTask)->position;
            ((Output_0012A2E0 *)pInput)->kind = 6;
            ((Output_0012A2E0 *)pInput)->target = (coords[best].y << 8) | coords[best].x;
            ((Output_0012A2E0 *)pInput)->flag = TaLogic_IsDefStyleUnit(((Unit_0012A2E0 *)pTask)->position >> 8, ((Unit_0012A2E0 *)pTask)->position & 0xFF, ((Output_0012A2E0 *)pInput)->target, nKind, 0);
            ((Output_0012A2E0 *)pInput)->value = TaLogic_IsOpenUnit_0012B210(((Unit_0012A2E0 *)pTask)->position >> 8, ((Unit_0012A2E0 *)pTask)->position & 0xFF, pTask);
        } else {
            ((Output_0012A2E0 *)pInput)->position = ((Unit_0012A2E0 *)pTask)->position;
            ((Output_0012A2E0 *)pInput)->kind = 6;
            ((Output_0012A2E0 *)pInput)->target = initial;
            ((Output_0012A2E0 *)pInput)->flag = TaLogic_IsDefStyleUnit(((Unit_0012A2E0 *)pTask)->position >> 8, ((Unit_0012A2E0 *)pTask)->position & 0xFF, ((Output_0012A2E0 *)pInput)->target, nKind, 0);
            ((Output_0012A2E0 *)pInput)->value = TaLogic_IsOpenUnit_0012B210(((Unit_0012A2E0 *)pTask)->position >> 8, ((Unit_0012A2E0 *)pTask)->position & 0xFF, pTask);
        }
        TaLogic006_InitRogicControl(pTask, fFirst);
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
} Source_0012AAC0;

typedef struct {
    u16 position;
    u8 action;
    u8 pad3;
    u16 target;
    u8 pad6[10];
    s8 result;
} Action_0012AAC0;

typedef struct {
    u8 x : 4;
    u8 y : 4;
} Point_0012AAC0;

#define MIN_0012AAC0(a, b) ((a) < (b) ? (a) : (b))
#define MAX_0012AAC0(a, b) ((b) < (a) ? (a) : (b))


/* The task's target square: the second half-word when the second argument is 1, else the first. */
static inline u32 target_0012AAC0(void *arg0, s32 mode) {
    Source_0012AAC0 *source = arg0;
    if (mode == 1) {
        return (u16)(source->target.both >> 16);
    }
    return source->target.half[0];
}

/* Sets a move task (action 6) to the given square, and whether the unit should stay in defence there. */
static inline void fill_0012AAC0(void *arg0, void *arg2, s32 target, s32 flag) {
    Source_0012AAC0 *source = arg0;
    Action_0012AAC0 *action = arg2;
    action->position = source->position;
    action->action = 6;
    action->target = target;
    action->result = TaLogic_IsDefStyleUnit(source->position >> 8,
        source->position & 0xFF, action->target, flag, 0);
}

/* The task of setting a trap (task `pTask`), into `pInput`. */
s32 TaLogic_GetMinimumTask_TrapMission_0012AAC0(void *pTask, s32 nSide, void *pInput, s32 fFirst) {
    s32 start;
    s32 count;
    s32 startY;
    Point_0012AAC0 points[16];
    s32 bestScore;
    Point_0012AAC0 *p;
    s32 targetY;
    s32 targetX;
    s32 i;
    s32 bestIndex;
    s32 mode;
    s32 target;
    s32 startX;
    u32 xPosition;
    u32 yPosition;
    Source_0012AAC0 *source = pTask;
    Action_0012AAC0 *action = pInput;
    extern void TaLogic_GetInvadeRoot();

    mode = fFirst & 0xFF;
    xPosition = target_0012AAC0(pTask, mode);
    yPosition = target_0012AAC0(pTask, mode);
    if (SzDuel_GetUnit(yPosition >> 8, xPosition & 0xFF) == 0) {
        TaLogic_InitRogicControl(pTask, 1);
        return -1;
    }
    start = SzDuel_GetUnitLoc(source->position >> 8, source->position & 0xFF);
    xPosition = target_0012AAC0(pTask, mode);
    yPosition = target_0012AAC0(pTask, mode);
    target = SzDuel_GetUnitLoc(yPosition >> 8, xPosition & 0xFF);
    if (target_0012AAC0(pTask, mode) == 0xFFFF) {
        fill_0012AAC0(pTask, pInput, start, 1);
        return 0;
    } else {
        s32 unit = SzDuel_GetUnit(source->position >> 8, source->position & 0xFF);
        startX = start & 0xFF;
        startY = start >> 8;
        if (GetMoveRev(unit, startX, startY) == 0 ||
                TaLogic_IsAttackedNow(source->position >> 8, source->position & 0xFF, 0) == 1) {
            fill_0012AAC0(pTask, pInput, start, 1);
            return 0;
        } else {
            p = points;
            {
                s32 n = 0;
                Point_0012AAC0 *q = p;
                do {
                    q->x = q->y = 0xF;
                    q++;
                    n++;
                } while (n < 12);
            }
            {
                s32 position = source->position;
                u16 card = (u16)TaLogic_GetWarnHideLvl_0012B1B0(nSide);
                TaLogic_GetInvadeRoot(position >> 8, position & 0xFF, points,
                    startX, startY, targetX = target & 0xFF,
                    targetY = target >> 8, target_0012AAC0(pTask, mode),
                    0, 30, card);
            }
            count = TaLogic_GetMinGoalCount((u8 *)points);
            bestIndex = 0xFF;
            if (count > 0) {
                bestScore = 0;
                for (i = 0; i < count; i++, p++) {
                    if (SzDuel_GetMapUnit(p->x, p->y) == 0) {
                        s32 score = TaLogic_GetUnitWarning(p->x, p->y, nSide, 5, 1,
                            TaLogic_GetWarnHideLvl_0012B1B0(nSide) & 0xFF);
                        if (bestScore < score) {
                            bestScore = score;
                            bestIndex = i;
                        } else if (score == bestScore) {
                            if (MAX_0012AAC0(p->x, targetX) - MIN_0012AAC0(p->x, targetX)
                                    + (MAX_0012AAC0(p->y, targetY) - MIN_0012AAC0(p->y, targetY))
                                    < MAX_0012AAC0(points[bestIndex].x, targetX) - MIN_0012AAC0(points[bestIndex].x, targetX)
                                    + (MAX_0012AAC0(points[bestIndex].y, targetY) - MIN_0012AAC0(points[bestIndex].y, targetY))) {
                                bestScore = score;
                                bestIndex = i;
                            }
                        }
                    }
                }
            } else {
                fill_0012AAC0(pTask, pInput, start, 1);
                return 0;
            }
            if (bestIndex != 0xFF) {
                action->position = source->position;
                action->action = 6;
                action->target = (points[bestIndex].y << 8) | points[bestIndex].x;
                action->result = TaLogic_IsDefStyleUnit(source->position >> 8,
                    source->position & 0xFF, action->target, 0, 0);
            } else {
                fill_0012AAC0(pTask, pInput, start, 1);
                return 0;
            }
        }
    }
    return 0;
}

/* The opponent's strongest unit that side `side`'s strongest unit cannot beat, or -1. */
s32 func_0012B000(s32 side) {
    s32 i;
    s32 n;
    s32 ownLow;
    s32 enemyAP;
    s32 enemy;
    s32 low;
    s32 own;
    s32 ownCol;
    s32 col;
    u16 list[22];

    n = 0;
    for (i = 0; i < 22; i++) {
        list[i] = 0xFFFF;
    }
    TaLogic_GetUnitCtlLst2(side == 0 ? 1 : 0, list, 0x1D, 0, 0);
    enemy = TaLogic_GetMaxApUnit(list);
    for (i = 0; i < 22; i++) {
        list[i] = 0xFFFF;
    }
    TaLogic_GetUnitCtlLst2(side, list, 0x1D, 1, 1);
    own = TaLogic_GetMaxApUnit(list);
    col = enemy & 0xFF;
    enemy = enemy >> 8;
    low = SzDuel_GetUnitLoc(enemy, col) & 0xFF;
    enemyAP = TaUtil_GetUnitAP(enemy, col, low, SzDuel_GetUnitLoc(enemy, col) >> 8);
    ownCol = own & 0xFF;
    own = own >> 8;
    ownLow = SzDuel_GetUnitLoc(own, ownCol) & 0xFF;
    if (TaUtil_GetUnitAP(own, ownCol, ownLow, SzDuel_GetUnitLoc(own, ownCol) >> 8) < enemyAP) {
        if (enemyAP >= 3000) {
            for (i = 1; i < 11; i++) {
                if (SzDuel_GetUnit(side, i) != 0) {
                    n++;
                }
            }
        }
    }
    return n < 3 ? 1 : 0;
}

/* How careful this duelist is about hidden cards (by its life points and monster count). */
s32 TaLogic_GetWarnHideLvl_0012B1B0(s32 nSide) {
    if (SzDuel_GetLP(nSide) > 0x4B0) {
        if (SzDuel_GetUnitMonsterCount(nSide) >= 4) {
            return 0x3E8;
        }
        return 0x7D0;
    }
    return 0x960;
}

/* Whether this duelist opens (turns face up) unit (nSide, nID) now: 0 no, 1 or 2 by its kind. */
s32 TaLogic_IsOpenUnit_0012B210(s32 nSide, s32 nID, void *pInfo) {
    extern s32 SzDuel_GetUnitCardNo();
    extern s32 func_0012B000();
    s32 card;
    s32 position;
    s32 owner;
    s32 value;
    u8 count;

    card = SzDuel_GetUnitCardNo(nSide, nID);
    owner = Ta_IsUnitControl(nSide, nID);
    position = SzDuel_GetUnitLoc(nSide, nID);
    count = 0;
    if (SzDuel_GetUnitStatus(nSide, nID, 4) != 0) {
        return 0;
    }
    switch (SzDuel_GetUnitKind(nSide, nID) >> 5) {
    case 0:
        switch (card) {
        case 0x65:
            for (card = 1; card <= 5; card++) {
                if (SzDuel_GetUnitCardNo(nSide, card) == 0x65 && nSide == Ta_IsUnitControl(nSide, card)) {
                    count++;
                }
                if (SzDuel_GetUnitCardNo((nSide == 0) ? 1 : 0, card) == 0x65 &&
                    nSide == Ta_IsUnitControl((nSide == 0) ? 1 : 0, card)) {
                    count++;
                }
            }
            if (count >= 2) {
                return 1;
            }
            break;
        case 0x66:
            for (card = 1; card <= 5; card++) {
                if (SzDuel_GetUnitCardNo(nSide, card) == 0x66 && nSide == Ta_IsUnitControl(nSide, card)) {
                    count++;
                }
                if (SzDuel_GetUnitCardNo((nSide == 0) ? 1 : 0, card) == 0x66 &&
                    nSide == Ta_IsUnitControl((nSide == 0) ? 1 : 0, card)) {
                    count++;
                }
            }
            if (count >= 2) {
                return 1;
            }
            break;
        case 0x6C:
            return 1;
        case 0x77:
            for (card = 1; card <= 5; card++) {
                if (SzDuel_GetUnitCardNo(nSide, card) == 0x77 && nSide == Ta_IsUnitControl(nSide, card)) {
                    count++;
                }
                if (SzDuel_GetUnitCardNo((nSide == 0) ? 1 : 0, card) == 0x77 &&
                    nSide == Ta_IsUnitControl((nSide == 0) ? 1 : 0, card)) {
                    count++;
                }
            }
            if (count >= 2) {
                return 1;
            }
            break;
        }
        return 2;
    case 5:
        if (TaLogic006_IsDoCerem(Ta_IsUnitControl(nSide, nID), card) == 1 &&
            SzDuel_GetField(position & 0xFF, position >> 8) != 9) {
            return 1;
        }
        break;
    case 1:
        if (TaLogic_GetActionReaction(nSide, nID, 0, 0, 6, 0) == 5) {
            return 2;
        }
        switch (SzDuel_GetUnitCardNo(nSide, nID)) {
        case 0x2BB:
            if (TaLogic_IsAttackedNow(nSide, 0, 0) == 1 || func_0012B000(nSide) == 1) {
                return 1;
            }
            break;
        case 0x2AD:
            value = TaLogic_GetMaxAPGraveCard(nSide, 3);
            if (value >= 0 && (u16)value >= 0x960 && SzDuel_GetUnitMonsterCount(nSide) < 5 &&
                SzDuel_GetField(position & 0xFF, position >> 8) != 9) {
                return 1;
            }
            break;
        case 0x2E9:
            for (card = 1; card <= 5; card++) {
                if (SzDuel_GetUnit(nSide, card) != 0 && (SzDuel_GetUnitKind(nSide, card) & 0x1F) != 2 &&
                    nSide == Ta_IsUnitControl(nSide, card)) {
                    count++;
                }
                if (SzDuel_GetUnit((nSide == 0) ? 1 : 0, card) != 0 &&
                    (SzDuel_GetUnitKind((nSide == 0) ? 1 : 0, card) & 0x1F) != 2 &&
                    nSide == Ta_IsUnitControl((nSide == 0) ? 1 : 0, card)) {
                    count++;
                }
            }
            if (count >= 3) {
                return 1;
            }
            break;
        }
        break;
    case 2:
    case 3:
    case 4:
    default:
        return 2;
    }
    return 2;
}

/* The larger of the two values. */
static inline s32 max_0012B730(s32 a, s32 b) {
    s32 maximum;

    if (a < b) {
        maximum = b;
    } else {
        maximum = a;
    }
    return maximum;
}

/* Whether unit (nSide, nID) may open while moving from (nX, nZ) to the square next to it, (gX, gZ). */
s32 TaLogic006_IsOpenMoveUnit(s32 nSide, s32 nID, s32 nX, s32 nZ, s32 gX, s32 gZ) {
    s32 min_y;
    s32 min_x;
    s32 result;
    s32 status;

    min_y = nZ < gZ ? nZ : gZ;
    gZ = max_0012B730(gZ, nZ);
    min_x = nX < gX ? nX : gX;
    gX = max_0012B730(gX, nX);
    if ((gX - min_x) + (gZ - min_y) != 2) {
        return 0;
    }
    if (SzDuel_GetUnit(nSide, nID) == 0) {
        return 0;
    }
    if (SzDuel_GetUnitStatus(nSide, nID, 0) == 0) {
        status = CheckLandAgreement2(SzDuel_GetField(nX, nZ), nSide, nID);
        result = 1;
        if (status != 1) {
            return 0;
        }
        return result;
    }
    return 0;
}

typedef struct {
    u8 pad0[4];
    u16 value4;
    u8 pad6[2];
    u32 value8;
} Data_0012B830;

/* Clears a unit's task (`Is1st` on its first turn). */
void TaLogic006_InitRogicControl(void *pUnit, u8 Is1st) {
    Data_0012B830 *data = pUnit;

    if (Is1st < 2) {
        if (Is1st == 1) {
            data->value4 = (data->value4 & 0xFF) | 0xFF00;
        } else {
            data->value4 = (data->value4 & 0xFF00) | 0xFF;
        }
        if (Is1st == 1) {
            data->value8 = (data->value8 & 0xFFFF) | 0xFFFF0000;
        } else {
            data->value8 = (data->value8 & 0xFFFF0000) | 0xFFFF;
        }
    }
}

/* Whether side `nSide` can play ritual card `nCardNo` now (it has the units to give up). */
s32 TaLogic006_IsDoCerem(s32 nSide, s32 nCardNo) {
    s32 sp50[3];
    s32 i;
    s32 temp_v0;
    s32 unitIdLo;
    s32 unitIdHi;
    s32 unitId;
    s32 loc;

    Ta_GetCeremSacrifice(sp50, *(s32 *)((u8 *)TaHand_GetCardEffect(nCardNo, 0) + 4));
    if ((temp_v0 = Ta_GetSacrificeUnit(sp50, nSide)) < 0) {
        return 0;
    }
    i = 0;
    if (i < Ta_GetUnitNumFrom22bitFlagList(temp_v0)) {
        do {
            unitId = Ta_GetUnitOwnerIDFromLstCount(temp_v0, i);
            unitIdHi = unitId >> 8;
            unitIdLo = unitId & 0xFF;
            loc = SzDuel_GetUnitLoc(unitIdHi, unitIdLo);
            if (TaUtil_GetUnitAP(unitIdHi, unitIdLo, loc & 0xFF, loc >> 8) >= 0x7D0) {
                return 0;
            }
            i++;
        } while (i < Ta_GetUnitNumFrom22bitFlagList(temp_v0));
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
} Req_0012B9A0;

typedef struct {
    u8 pad0[0x160];
    u16 list[32];    /* 0x160 */
    u8 idx : 5;      /* 0x1A0 */
    u8 pad1A0 : 3;
    u8 pad1A1;
    u16 count;       /* 0x1A2 */
} Work_0012B9A0;

s32 TaLogic_GetInputQueFromMinimumTask_b(void *, void *, s32);

/* This computer duelist's controller (one entry of duelistControllers): the buttons it presses this frame. With an empty
   input queue it plans its next task and turns it into buttons, then plays the queue back one button per frame;
   after 600 frames it gives up the turn (0x20, then 0x800). */
s32 func_0012B9A0(s32 wCursorPos, void *pCtl) {
    Req_0012B9A0 req;
    Work_0012B9A0 *w;
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
        if (TaLogic_GetMinimumTask_00126C80(w, &req, wCursorPos) == 0) {
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

typedef struct {
    u8 pad0[0x1A1];
    u8 lvl : 4;      /* 0x1A1 */
    u8 pad1A1 : 4;
} Ai_0012BB70;

#pragma conditional_move off

/* This duelist's move: picks the next unit to act, gives it a task and turns that into input `pInput`; returns 1
   when it set one. */
s32 TaLogic_GetMinimumTask_0012BB70(void *pCtl, void *pInput, s32 wCursorPos) {
    extern s32 TaLogic_GetMinimumTask_ReviveMission_0012ED70(void *, s32, void *, u8, u8);
    extern s32 TaLogic_GetMinimumTask_TrapMission_00130120(void *, s32, void *, u8, u8);
    u16 *tasks = pCtl;
    Ai_0012BB70 *ai = pCtl;
    s32 side;
    s32 found;
    s32 result;
    s32 index;

    side = SzDuel_GetTurnOwner();
    found = 0;
    ai->lvl = TaLogic007_IsActiveMode();
    if ((result = TaLogic_GetNextActiveUnit_0012C3F0(tasks, side, (s32)pInput)) < 0) {
        return 0;
    }
    index = TaLogic_GetActionUnitFromOwnerID(tasks, result & 0xFFFF);
    if (index < 0) {
        return 0;
    }
    if ((result >> 16) == 1) {
        if (((tasks[index * 8 + 2] >> 8) & 0xFF) == 10) {
            TaLogic_InitRogicControl(tasks + index * 8, 1);
        } else {
            TaLogic_InitRogicControl(tasks + index * 8, 0);
        }
        return 1;
    }
    TaLogic_CommandUnit_0012C1A0(tasks + index * 8, ai->lvl);
    switch ((tasks[index * 8 + 2] >> 8) & 0xFF) {
    case 5:
        if (SzDuel_GetUnitStatus(tasks[index * 8] >> 8, tasks[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_RunMission_0012E820(tasks + index * 8, side, pInput, 1, ai->lvl);
            found = 1;
        }
        break;
    case 2:
        if (SzDuel_GetUnitStatus(tasks[index * 8] >> 8, tasks[index * 8] & 0xFF, 0) == 0) {
            if (TaLogic_GetMinimumTask_AtkMission_0012F350(tasks + index * 8, side, pInput, 1, ai->lvl) < 0) {
                TaLogic_InitRogicControl(tasks + index * 8, 1);
                return 1;
            }
            found = 1;
        }
        break;
    case 10:
        if (TaLogic_GetMinimumTask_Summon_0012D270(tasks[index * 8], side, (s32)pInput, ai->lvl) < 0) {
            TaLogic_InitRogicControl(tasks + index * 8, 1);
            *(u8 *)((u8 *)pInput + 2) = 0xFF;
            *(s32 *)((u8 *)pInput + 0xC) = 0;
        } else {
            TaLogic_InitRogicControl(tasks + index * 8, 1);
            found = 1;
        }
        break;
    case 6:
        if (SzDuel_GetUnitStatus(tasks[index * 8] >> 8, tasks[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_MoveMission_0012F930(tasks + index * 8, side, pInput, 1, 0, ai->lvl);
            found = 1;
        }
        break;
    case 3:
        if (SzDuel_GetUnitStatus(tasks[index * 8] >> 8, tasks[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_MoveMission_0012F930(tasks + index * 8, side, pInput, 1, 1, ai->lvl);
            found = 1;
        }
        break;
    case 9:
        TaLogic_GetMinimumTask_EncMission(tasks + index * 8, side, pInput, 1, 0, TaLogic_GetWarnHideLvl_00130780(side), 5, 1);
        found = 1;
        break;
    case 11:
        TaLogic_GetMinimumTask_TrapMission_00130120(tasks + index * 8, side, pInput, 1, ai->lvl);
        found = 1;
        break;
    case 12:
        TaLogic_GetMinimumTask_ReviveMission_0012ED70(tasks + index * 8, side, pInput, 1, ai->lvl);
        found = 1;
        break;
    case 14:
        TaLogic_GetMinimumTask_DoNone(tasks + index * 8, side, pInput);
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
    switch (tasks[index * 8 + 2] & 0xFF) {
    case 5:
        if (SzDuel_GetUnitStatus(tasks[index * 8] >> 8, tasks[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_RunMission_0012E820(tasks + index * 8, side, pInput, 0, ai->lvl);
            found = 1;
        }
        break;
    case 2:
        if (SzDuel_GetUnitStatus(tasks[index * 8] >> 8, tasks[index * 8] & 0xFF, 0) == 0) {
            if (TaLogic_GetMinimumTask_AtkMission_0012F350(tasks + index * 8, side, pInput, 0, ai->lvl) < 0) {
                TaLogic_GetMinimumTask_RunMission_0012E820(tasks + index * 8, side, pInput, 0, ai->lvl);
            }
            found = 1;
        }
        break;
    case 10:
        if (TaLogic_GetMinimumTask_Summon_0012D270(tasks[index * 8], side, (s32)pInput, ai->lvl) < 0) {
            TaLogic_InitRogicControl(tasks + index * 8, 0);
            *(u8 *)((u8 *)pInput + 2) = 0xFF;
            found = 1;
            *(s32 *)((u8 *)pInput + 0xC) = 0;
        } else {
            TaLogic_InitRogicControl(tasks + index * 8, 0);
            found = 1;
        }
        break;
    case 6:
        if (SzDuel_GetUnitStatus(tasks[index * 8] >> 8, tasks[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_MoveMission_0012F930(tasks + index * 8, side, pInput, 0, 0, ai->lvl);
            found = 1;
        }
        break;
    case 3:
        if (SzDuel_GetUnitStatus(tasks[index * 8] >> 8, tasks[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_MoveMission_0012F930(tasks + index * 8, side, pInput, 0, 1, ai->lvl);
            found = 1;
        }
        break;
    case 11:
        TaLogic_GetMinimumTask_TrapMission_00130120(tasks + index * 8, side, pInput, 0, ai->lvl);
        found = 1;
        break;
    case 9:
        TaLogic_GetMinimumTask_EncMission(tasks + index * 8, side, pInput, 0, 0, TaLogic_GetWarnHideLvl_00130780(side), 5, 1);
        found = 1;
        break;
    case 12:
        TaLogic_GetMinimumTask_ReviveMission_0012ED70(tasks + index * 8, side, pInput, 0, ai->lvl);
        found = 1;
        break;
    case 14:
        TaLogic_GetMinimumTask_DoNone(tasks + index * 8, side, pInput);
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

typedef struct {
    u16 id;
    u8 pad2[2];
    s16 status;
    u8 pad6[2];
    s32 flags;
} Object_0012C1A0;


/* Gives the unit of task `pTask` its order for this turn (attack, run, move, summon, guard). */
s32 TaLogic_CommandUnit_0012C1A0(void *pCtl, s32 pTask) {
    Object_0012C1A0 *obj = pCtl;
    s32 controllingSide;
    s32 kind;
    u16 id;

    id = obj->id;
    controllingSide = Ta_IsUnitControl((s32)(id >> 8), id & 0xFF);
    id = obj->id;
    if (SzDuel_GetUnit((s32)(id >> 8), id & 0xFF) != 0) {
        id = obj->id;
        if (SzDuel_GetUnitStatus((s32)(id >> 8), id & 0xFF, 0) == 0) {
            id = obj->id;
            if (id != 0xFFFF) {
                if ((id & 0xFF) == 0) {
                    if (obj->flags == -1) {
                    if ((TaLogic_IsAttackedNow((s32)(id >> 8), id & 0xFF, 0) == 1) ||
                        ((SzDuel_GetUnitLoc((s32)(obj->id >> 8), obj->id & 0xFF) >> 8) >= 2)) {
                        if (SzDuel_InqHandPhase((s32)(obj->id >> 8)) == 1) {
                            obj->status = 0x50A;
                        } else {
                            obj->status = 0x5FF;
                        }
                    } else {
                        if (SzDuel_InqHandPhase((s32)(obj->id >> 8)) == 1) {
                            obj->status = 0x60A;
                            obj->flags = (u16)obj->flags | (SzDuel_GetUnitLoc((controllingSide == 0) ? 1 : 0, 0) << 16);
                        } else {
                            obj->status = 0x6FF;
                            obj->flags = (u16)obj->flags | (SzDuel_GetUnitLoc((controllingSide == 0) ? 1 : 0, 0) << 16);
                        }
                    }
                    }
                } else {
                    kind = SzDuel_GetUnitKind((s32)(id >> 8), id & 0xFF) >> 5;
                    switch (kind) {
                    case 0:
                        id = obj->id;
                        if (TaUtil_IsExMonster((s32)(id >> 8), id & 0xFF) == 1) {
                            TaLogic007_CommandEfcMonster(obj, pTask);
                        } else {
                            TaLogic007_CommandBtlUnit(obj, 1, pTask);
                        }
                        break;
                    case 2:
                        TaLogic_CommandEncUnit(obj, 5, 0, TaLogic_GetWarnHideLvl_00130780(controllingSide) & 0xFF);
                        break;
                    case 3:
                        TaLogic_CommandTrapUnit_0012CE50(obj);
                        break;
                    default:
                        obj->status = 0x5FF;
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
s32 TaLogic_GetNextActiveUnit_0012C3F0(u16 *pCtl, s32 nSide, s32 pInput) {
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
    TaLogic_CommandUnit_0012C1A0(pCtl + idx * 8, ((u8 *)pCtl)[0x1A1] & 0xF);
    if (((pCtl[idx * 8 + 2] >> 8) & 0xFF) == 10) {
        if (SzDuel_InqHandPhase(nSide) == 1 && TaLogic_GetMinimumTask_Summon_0012D270(pos, nSide, pInput, TaLogic007_IsActiveMode()) >= 0) {
            return pos | 0x10000;
        }
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_GetUnitStatus(nSide, 0, 0) == 0) {
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_InqHandPhase(nSide) == 1 && TaLogic_GetMinimumTask_Summon_0012D270(pos, nSide, pInput, TaLogic007_IsActiveMode()) >= 0) {
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

typedef struct Command_0012C7F0 {
    u16 position;
    u16 pad2;
    u16 action;
    u16 pad6;
    u16 target;
    u16 padA;
} Command_0012C7F0;

typedef struct Entry_0012C7F0 {
    u16 position;
    u8 value;
    u8 pad;
} Entry_0012C7F0;

/* Orders a fighting unit (task `pTask`): straight at the enemy leader when `fGoalFirst` and the path is open,
   else at the nearest enemy it can beat within 2 squares (5 with `bActive`); else it pushes in. */
void TaLogic007_CommandBtlUnit(void *pTask, s32 fGoalFirst, s32 bActive) {
    extern void TaLogic_InitIgnoreLst();
    extern s32 TaLogic_IsRootOpen();
    extern s32 TaLogic007_GetNearUnit();
    Command_0012C7F0 *command = pTask;

    if (SzDuel_GetUnit(command->position >> 8, command->position & 0xFF) != 0) {
        s32 position;
        s32 side;
        s32 data;
        s32 other;
        s32 otherPosition;
        u8 workspace[112];
        Entry_0012C7F0 entries[23];
        s16 count;
        s16 total;
        s32 i;
        Entry_0012C7F0 *entry;

        side = Ta_GetCurrentSide(command->position >> 8, command->position & 0xFF);
        other = (side == 0 ? 1 : 0) << 8;
        position = SzDuel_GetUnitLoc(command->position >> 8, command->position & 0xFF);
        otherPosition = SzDuel_GetUnitLoc(other >> 8, other & 0xFF);
        data = SzDuel_GetUnit(command->position >> 8, command->position & 0xFF);
        TaLogic_InitIgnoreLst(workspace);
        entry = entries;
        i = 0;
        do {
            i++;
            entry->position = 0xFFFF;
            entry->value = 0xFF;
            entry++;
        } while (i < 22);

        if (fGoalFirst != 0) {
            u8 mode;
            if ((bActive & 0xFF) == 1) {
                mode = 5;
            } else {
                mode = 2;
            }
            if (TaLogic_IsRootOpen(command->position >> 8, command->position & 0xFF,
                    position & 0xFF, position >> 8, other >> 8, other & 0xFF,
                    otherPosition & 0xFF, otherPosition >> 8, mode) > 0) {
                command->action = 0x2FF;
                *(u32 *)&command->target = (other << 16) | command->target;
                return;
            }
        }

        total = 0;
        count = 0;
        if ((bActive & 0xFF) == 0) {
            bActive = 1;
            while (1) {
                s32 result;
                other = Ta_GetCurrentSide(command->position >> 8, command->position & 0xFF) == 0 ? 1 : 0;
                result = TaLogic007_GetNearUnit(command, 0, data, position & 0xFF, position >> 8,
                    other, (u8)bActive, TaLogic_GetWarnHideLvl_00130780(side), entries, 0,
                    &count, &total, 2, workspace);
                switch (result) {
                case 3:
                    command->action = 0x6FF;
                    *(u32 *)&command->target = (position << 16) | command->target;
                    return;
                case 2:
                    command->action = 0x3FF;
                    *(u32 *)&command->target = (position << 16) | command->target;
                    return;
                case 1:
                    return;
                case 0:
                    command->action = 0x5FF;
                    return;
                }
                bActive++;
                if (bActive > 2) {
                    break;
                }
            }
            command->action = 0x5FF;
        } else {
            bActive = 1;
            do {
                s32 result;
                other = Ta_GetCurrentSide(command->position >> 8, command->position & 0xFF) == 0 ? 1 : 0;
                result = TaLogic007_GetNearUnit(command, 0, data, position & 0xFF, position >> 8,
                    other, (u8)bActive, TaLogic_GetWarnHideLvl_00130780(side), entries, 0,
                    &count, &total, 5, workspace);
                switch (result) {
                case 3:
                    command->action = 0x6FF;
                    *(u32 *)&command->target = (position << 16) | command->target;
                    return;
                case 2:
                    command->action = 0x3FF;
                    *(u32 *)&command->target = (position << 16) | command->target;
                    return;
                case 1:
                    return;
                case 0:
                    command->action = 0x5FF;
                    return;
                }
                bActive++;
            } while (bActive < 5);
            command->action = 0x5FF;
        }
    }
}

/* TaLogic_GetNearUnit with this duelist's view and strength settings. */
void TaLogic007_GetNearUnit(s32 pTask, s32 pTree, s32 pVarInfo, s32 nX, s32 nZ, s32 eSide, s32 bDist, s32 WarnLvl, s32 nUnitLst, u16 wUnitNum, s32 wSize, s32 wNodeCount, u8 bChase, s32 wIgnoreLst) {
    TaLogic_GetNearUnit(pTask, pTree, pVarInfo, nX, nZ, eSide, bDist, WarnLvl,
                  nUnitLst, wUnitNum, wSize, wNodeCount, bChase,
                  0, 2500, wIgnoreLst);
}

typedef struct State_0012CBE0 {
    u16 id;
    u16 pad2;
    u16 flags;
    u16 pad6;
    u32 position;
} State_0012CBE0;

typedef struct Entry_0012CBE0 {
    u16 id;
    u8 kind;
    u8 pad;
} Entry_0012CBE0;

/* Sets a task's action `flags` and its target square `position`. */
static inline void update_state_0012CBE0(void *arg0, u16 flags, s32 position) {
    State_0012CBE0 *state = arg0;
    u32 value;

    state->flags = flags;
    value = state->position & 0xFFFF;
    state->position = (position << 16) | value;
}


/* Orders an effect monster (task `pTask`): where its effect does most (`fGoalFirst`: try its goal first). */
void TaLogic007_CommandEfcMonster(void *pTask, s32 fGoalFirst) {
    extern s32 SzDuel_GetUnitCardNo();
    extern void TaLogic_InitIgnoreLst();
    extern s32 TaLogic_GetNearUnit();
    u8 buffer[0x70];
    Entry_0012CBE0 entries[23];
    s16 count;
    s16 limit;
    State_0012CBE0 *state = pTask;
    s32 owner;
    s32 position;
    s32 unitInfo;
    s32 row;
    s32 column;
    s32 attempt;
    s32 i;
    Entry_0012CBE0 *entry;
    s32 type;
    s32 result;

    if ((unitInfo = SzDuel_GetUnit(state->id >> 8, state->id & 0xFF)) != 0) {
        owner = Ta_GetCurrentSide(state->id >> 8, state->id & 0xFF);
        position = SzDuel_GetUnitLoc(state->id >> 8, state->id & 0xFF);
        entry = entries;
        limit = 0;
        count = 0;
        i = 0;
        do {
            i++;
            entry->id = 0xFFFF;
            entry->kind = 0xFF;
            entry++;
        } while (i < 22);
        TaLogic_InitIgnoreLst(buffer);
        type = SzDuel_GetUnitCardNo(state->id >> 8, state->id & 0xFF);
        switch (type) {
        case 0x12A:
        case 0x142: {
            row = position >> 8;
            column = position & 0xFF;

            attempt = 1;
            while (1) {
                result = TaLogic_GetNearUnit(state, 0, unitInfo, column, row, owner == 0 ? 1 : 0,
                                      (u8)attempt, TaLogic_GetWarnHideLvl_00130780(owner), entries, 0,
                                      &count, &limit, 2, 0, 2500, buffer);
                switch (result) {
                case 3:
                case 2:
                    update_state_0012CBE0(state, 0x3FF, position);
                    return;
                case 1:
                    return;
                case 0:
                    update_state_0012CBE0(state, 0x3FF, position);
                    return;
                }
                attempt++;
                if (attempt > 2) {
                    break;
                }
            }
            update_state_0012CBE0(state, 0x3FF, position);
            return;
        }
        case 0x131:
            if (SzDuel_GetUnitStatus(state->id >> 8, state->id & 0xFF, 4) == 0) {
                update_state_0012CBE0(state, 0xCFF, position);
                return;
            }
            break;
        case 0x146:
            update_state_0012CBE0(state, 0x3FF, position);
            return;
        }
        TaLogic007_CommandBtlUnit(state, 1, fGoalFirst);
    }
}

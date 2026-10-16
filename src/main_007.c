#include "common.h"

s32 func_0016B0F0_b(); /* TaLogic021_IsUseBlackHole, which this file calls without its argument */

s32 TaLogic005_GetSpellPlay(s32 arg0, u8 *arg1, void *arg2, s32 arg3) {
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


s32 TaLogic005_SetComboQue(s32 arg0, u8 *arg1, void *arg2) {
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
                    *node = TaLogic_GetFusionTree(arg0, (struct TreeTag *)*node, i & 0xFF, card & 0xFFFF, 0, (u16 *)&a, (u16 *)&b);
                    *node = TaLogic_GetFusionRes(*node);
                    if (**node != 0x217) {
                        value = TaHand_GetCardAPDP(**node);
                        if ((value >> 16) >= 0x5DC) {
                            value = TaLogic_GetEnchantQue(arg0, *node, 0, 0);
                        }
                        if (TaHand_IsCardSummon2(arg0, card) == 1) {
                            if (best < value) {
                                TaLogic_ConvEmptyCombo_00124A30(arg0, *node, entries);
                                TaLogic_CopyArray((u8 *)*node + 2, arg1 + 6);
                                SzDuel_InitCardInfo(arg2, **node);
                                ((Sprite_00124810 *)arg2)->x = (value >> 16) - (((Sprite_00124810 *)arg2)->info->x & 0x1FFF);
                                ((Sprite_00124810 *)arg2)->y = (value & 0xFFFF) - (((Sprite_00124810 *)arg2)->info->y & 0x1FFF);
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
            } while (i < TaHand_GetNextHandNum(arg0));
        }
        return top;
    }
}

typedef struct {
    u16 id;
    u8 values[5];
} Info_00124A30;

void TaLogic_ConvEmptyCombo_00124A30(s32 arg0, void *arg1, s32 *arg2) {
    Info_00124A30 *info = arg1;
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
                if (card != 0x3E7 && TaLogic005_IsRefuseEmptyCombo(card) == 0 && level >= TaHand_GetCardSummonCost2(card, arg0)) {
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

s32 TaLogic005_IsRefuseEmptyCombo(s32 arg0) {
    s32 value;

    if ((TaHand_GetCardKind(arg0) >> 5) != 0) {
        return 1;
    }
    value = TaHand_GetCardKind(arg0) & 0x1F;
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

s32 TaLogic_SetSpecialComboQue_00124C90(s32 arg0, void *arg1, void *arg2, s32 arg3) {
    Obj1_00124C90 *o1 = arg1;
    Obj2_00124C90 *o2 = arg2;
    s32 list[8];
    s32 i;
    u8 t;

    for (i = 0; i < 5; i++) {
        o1->slot[i] = 0xFF;
    }
    TaHand_GetNextHand(arg0, list);
    if (o2 == NULL) {
        return -1;
    }
    if ((arg3 & 0xFF) == 0) {
        for (i = 0; i < TaHand_GetNextHandNum(arg0); i++) {
            if (i != o1->slot[0] && i != o1->slot[1]) {
                if (o2->id == list[i] && TaHand_IsCardSummon2(arg0, list[i]) == 1) {
                    o1->slot[0] = i;
                }
            }
        }
        return 0;
    }
    TaLogic005_Is2Head_ThunderDragon(arg0, list);
    for (i = 0; i < TaHand_GetNextHandNum(arg0); i++) {
        t = TaHand_GetCardKind(list[i]);
        if ((t >> 5) == 0 && (t & 0x1F) == 0 && TaHand_IsCardSummon2(arg0, list[i]) == 1) {
            o1->slot[0] = i;
        }
    }
    for (i = 0; i < TaHand_GetNextHandNum(arg0); i++) {
        t = TaHand_GetCardKind(list[i]);
        if ((t >> 5) == 0 && (t & 0x1F) == 0x12 && TaHand_IsCardSummon2(arg0, list[i]) == 1) {
            o1->slot[1] = i;
        }
    }
    for (i = 0; i < TaHand_GetNextHandNum(arg0); i++) {
        t = TaHand_GetCardKind(list[i]);
        if ((t >> 5) == 0 && (t & 0x1F) == 0xF && TaHand_IsCardSummon2(arg0, list[i]) == 1) {
            o1->slot[2] = i;
        }
    }
    return 0;
}

s32 TaLogic_GetSommonPiecePreference_00124F50(s32 arg0, u32 arg1) {
    return Ta_GetSommonPiecePreference(arg0, arg1);
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


s32 TaLogic_GetMinimumTask_RunMission_00124F60(u16 *arg0, s32 arg1, void *arg2, u8 arg3) {
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
    Output_00124F60 *out = arg2;

    position = SzDuel_GetUnitLoc(*arg0 >> 8, *arg0 & 0xFF);
    i = 0;
    do {
        cells[i].low = cells[i].high = 15;
        i++;
    } while (i < 12);

    {
        u16 value = (u16)TaLogic_GetWarnHideLvl_001254A0(arg1);
        originalX = position & 0xFF;
        originalY = position >> 8;
        if (TaLogic_GetUnitWarning(originalX, originalY, *arg0, 2, value, 0) == 0) {
            out->id = *arg0;
            out->action = 6;
            out->position = position;
            out->mode = TaLogic_IsDefStyleUnit(*arg0 >> 8, *arg0 & 0xFF, out->position, 1, 0);
            out->value = TaLogic_IsOpenUnit_00126380(*arg0 >> 8, *arg0 & 0xFF, arg0);
            TaLogic005_InitRogicControl(arg0, arg3);
            return 0;
        } else {
            result = GetMoveRev(SzDuel_GetUnit(*arg0 >> 8, *arg0 & 0xFF), originalX, originalY);
            if (result == 0) {
                out->id = *arg0;
                out->action = 6;
                out->position = position;
                out->mode = TaLogic_IsDefStyleUnit(*arg0 >> 8, *arg0 & 0xFF, out->position, 1, 0);
                out->value = TaLogic_IsOpenUnit_00126380(*arg0 >> 8, *arg0 & 0xFF, arg0);
                TaLogic005_InitRogicControl(arg0, arg3);
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
                                value = (u16)TaLogic_GetWarnHideLvl_001254A0(arg1);
                                score = TaLogic_GetUnitWarning(x, y, *arg0, 2, value, 0);
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
                        out->mode = TaLogic_IsDefStyleUnit(*arg0 >> 8, *arg0 & 0xFF, out->position, 0, 0);
                    }
                    out->value = TaLogic_IsOpenUnit_00126380(*arg0 >> 8, *arg0 & 0xFF, arg0);
                } else {
                    out->id = *arg0;
                    out->action = 6;
                    out->position = position;
                    out->mode = TaLogic_IsDefStyleUnit(*arg0 >> 8, *arg0 & 0xFF, out->position, 1, 0);
                    out->value = TaLogic_IsOpenUnit_00126380(*arg0 >> 8, *arg0 & 0xFF, arg0);
                }
                TaLogic005_InitRogicControl(arg0, arg3);
            }
        }
    }
    return 0;
}

s32 TaLogic_GetWarnHideLvl_001254A0(s32 arg0) {
    if (SzDuel_GetLP(arg0) > 0x3E8) {
        if (SzDuel_GetUnitMonsterCount(arg0) >= 3) {
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


static inline u32 target_00125500(void *arg0, u8 which) {
    Source_00125500 *source = arg0;
    if (which == 1) {
        return (u16)(source->targets >> 16);
    }
    return *(u16 *)&source->targets;
}

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

s32 TaLogic_GetMinimumTask_AtkMission_00125500(void *arg0, s32 arg1, void *arg2, u8 arg3) {
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
    Source_00125500 *source = arg0;
    Output_00125500 *output = arg2;

    targetXWord = target_00125500(arg0, arg3);
    targetYWord = target_00125500(arg0, arg3);
    if (SzDuel_GetUnit(targetYWord >> 8, targetXWord & 0xFF) == 0) {
        TaLogic_InitRogicControl(arg0, 1);
        return -1;
    }

    flag = TaLogic_IsOpenUnit_00126380(source->position >> 8, source->position & 0xFF, arg0);
    sourceTarget = SzDuel_GetUnitLoc(source->position >> 8, source->position & 0xFF);
    targetXWord = target_00125500(arg0, arg3);
    targetYWord = target_00125500(arg0, arg3);
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
        cost = TaLogic_GetUnitWarning(sourceX, sourceY, arg1, 2, 1,
                            (u8)penalty_00125500(arg1));
        if (cost >= SzDuel_GetUnitAP(source->position >> 8, source->position & 0xFF, 0)) {
            output->value = TaLogic_IsDefStyleUnit(source->position >> 8, source->position & 0xFF,
                                        output->target, 1, 0);
        } else {
            output->value = TaLogic_IsDefStyleUnit(source->position >> 8, source->position & 0xFF,
                                        output->target, 0, 0);
        }
        TaLogic005_InitRogicControl(arg0, arg3);
    } else {
        s32 targetY;
        s32 targetX;
        Position_00125500 *current;
        s32 i;
        s32 bestCost;
        s32 selected;
        s32 penalty;
        u16 position;

        penalty = penalty_00125500(arg1);
        position = source->position;
        TaLogic_GetInvadeRoot(position >> 8, position & 0xFF, positions,
                      sourceX, sourceY, targetX = otherTarget & 0xFF,
                      targetY = otherTarget >> 8,
                      target_00125500(arg0, arg3), 0, 30, (u16)penalty);
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
                    s32 penalty = penalty_00125500(arg1);
                    current = &positions[i];
                    cost = TaLogic_GetUnitWarning(current->x, current->y, arg1, 2, 1,
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
            TaLogic005_InitRogicControl(arg0, arg3);
            return 0;
        } else {
            output->position = source->position;
            output->mode = 6;
            output->target = sourceTarget;
            output->flag = selectedFlag;
            output->value = TaLogic_IsDefStyleUnit(source->position >> 8, source->position & 0xFF,
                                        output->target, 0, 0);
            TaLogic_InitRogicControl(arg0, arg3);
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


static inline u32 target_00125B70(void *unit, s32 side) {
    return side == 1 ? (u32)(u16)(((Unit_00125B70 *)unit)->target.packed >> 16) : (u32)((Unit_00125B70 *)unit)->target.low;
}

static inline u32 minY_00125B70(void *unit, s32 side, u8 coord) {
    return coord < (target_00125B70(unit, side) >> 8) ? coord : (target_00125B70(unit, side) >> 8);
}

static inline u32 maxY_00125B70(void *unit, s32 side, u8 coord) {
    return (target_00125B70(unit, side) >> 8) < coord ? coord : (target_00125B70(unit, side) >> 8);
}

static inline u32 minX_00125B70(void *unit, s32 side, u8 coord) {
    return coord < (target_00125B70(unit, side) & 0xFF) ? coord : (target_00125B70(unit, side) & 0xFF);
}

static inline u32 maxX_00125B70(void *unit, s32 side, u8 coord) {
    return (target_00125B70(unit, side) & 0xFF) < coord ? coord : (target_00125B70(unit, side) & 0xFF);
}

static inline s32 scoreLimit_00125B70(s32 unit) {
    if (SzDuel_GetLP(unit) > 1000) {
        if (SzDuel_GetUnitMonsterCount(unit) >= 3) {
            return 500;
        }
        return 1000;
    }
    return 2000;
}

s32 TaLogic_GetMinimumTask_MoveMission_00125B70(void *arg0, s32 arg1, void *arg2, u8 arg3, u8 arg4) {
    extern s32 TaLogic_GetUnitWarning();
    extern void TaLogic_GetRoot();
    extern s32 TaLogic_IsDefStyleUnit(s32, s32, s32, u8, s32);
    Coord_00125B70 coords[12];
    s32 initial;
    s32 cell;
    s32 count;

    initial = SzDuel_GetUnitLoc(((Unit_00125B70 *)arg0)->position >> 8, ((Unit_00125B70 *)arg0)->position & 0xFF);
    {
    s32 bestScore;
    s32 best;
    s32 side = arg3;
    Coord_00125B70 *candidate;
    s32 index;
    if (target_00125B70(arg0, side) == 0xFFFF) {
        if (initial == target_00125B70(arg0, side)) {
            ((Output_00125B70 *)arg2)->position = ((Unit_00125B70 *)arg0)->position;
            ((Output_00125B70 *)arg2)->kind = 6;
            ((Output_00125B70 *)arg2)->target = initial;
            ((Output_00125B70 *)arg2)->flag = TaLogic_IsDefStyleUnit(((Unit_00125B70 *)arg0)->position >> 8, ((Unit_00125B70 *)arg0)->position & 0xFF, ((Output_00125B70 *)arg2)->target, arg4, 0);
            ((Output_00125B70 *)arg2)->value = TaLogic_IsOpenUnit_00126380(((Unit_00125B70 *)arg0)->position >> 8, ((Unit_00125B70 *)arg0)->position & 0xFF, arg0);
            TaLogic005_InitRogicControl(arg0, arg3);
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

    cell = SzDuel_GetMapUnitID(target_00125B70(arg0, side) & 0xFF, ((u32)target_00125B70(arg0, side)) >> 8);
    if (cell < 0) {
        cell = 0xFFFF;
    }
    TaLogic_GetRoot(((Unit_00125B70 *)arg0)->position >> 8, ((Unit_00125B70 *)arg0)->position & 0xFF,
                 coords, initial & 0xFF, initial >> 8, target_00125B70(arg0, side) & 0xFF,
                 ((u32)target_00125B70(arg0, side)) >> 8, (u16)cell, 7);
    count = TaLogic_GetMinGoalCount((u8 *)coords);
    {
        if (count > 0) {
        best = 0xFF;
        bestScore = 0xFFFF;
        for (index = 0; index < count; index++) {
                if (SzDuel_GetMapUnit(candidate->x, candidate->y) == 0) {
                    s32 score = TaLogic_GetUnitWarning(candidate->x, candidate->y, arg1, 2, 1, (u8)scoreLimit_00125B70(arg1));
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
                        bestMinY = minY_00125B70(arg0, side, bestY);
                        bestMaxY = maxY_00125B70(arg0, side, bestY);
                        bestX = (&coords[best])->x;
                        bestMinX = minX_00125B70(arg0, side, bestX);
                        bestMaxX = maxX_00125B70(arg0, side, bestX);
                        currentY = (u8)candidate->y;
                        currentMinY = minY_00125B70(arg0, side, currentY);
                        currentMaxY = maxY_00125B70(arg0, side, currentY);
                        currentX = candidate->x;
                        currentMinX = minX_00125B70(arg0, side, currentX);
                        currentMaxX = maxX_00125B70(arg0, side, currentX);
                        if ((currentMaxX - currentMinX) + (currentMaxY - currentMinY) < (bestMaxX - bestMinX) + (bestMaxY - bestMinY)) {
                            bestScore = score;
                            best = index;
                        }
                    }
                }
            candidate++;
        }
    } else {
        ((Output_00125B70 *)arg2)->position = ((Unit_00125B70 *)arg0)->position;
            ((Output_00125B70 *)arg2)->kind = 6;
            ((Output_00125B70 *)arg2)->target = initial;
            ((Output_00125B70 *)arg2)->flag = TaLogic_IsDefStyleUnit(((Unit_00125B70 *)arg0)->position >> 8, ((Unit_00125B70 *)arg0)->position & 0xFF, ((Output_00125B70 *)arg2)->target, arg4, 0);
            ((Output_00125B70 *)arg2)->value = TaLogic_IsOpenUnit_00126380(((Unit_00125B70 *)arg0)->position >> 8, ((Unit_00125B70 *)arg0)->position & 0xFF, arg0);
        TaLogic005_InitRogicControl(arg0, arg3);
        return 0;
    }

        if (best != 0xFF) {
            ((Output_00125B70 *)arg2)->position = ((Unit_00125B70 *)arg0)->position;
            ((Output_00125B70 *)arg2)->kind = 6;
            ((Output_00125B70 *)arg2)->target = (coords[best].y << 8) | coords[best].x;
            ((Output_00125B70 *)arg2)->flag = TaLogic_IsDefStyleUnit(((Unit_00125B70 *)arg0)->position >> 8, ((Unit_00125B70 *)arg0)->position & 0xFF, ((Output_00125B70 *)arg2)->target, arg4, 0);
            ((Output_00125B70 *)arg2)->value = TaLogic_IsOpenUnit_00126380(((Unit_00125B70 *)arg0)->position >> 8, ((Unit_00125B70 *)arg0)->position & 0xFF, arg0);
        } else {
            ((Output_00125B70 *)arg2)->position = ((Unit_00125B70 *)arg0)->position;
            ((Output_00125B70 *)arg2)->kind = 6;
            ((Output_00125B70 *)arg2)->target = initial;
            ((Output_00125B70 *)arg2)->flag = TaLogic_IsDefStyleUnit(((Unit_00125B70 *)arg0)->position >> 8, ((Unit_00125B70 *)arg0)->position & 0xFF, ((Output_00125B70 *)arg2)->target, arg4, 0);
            ((Output_00125B70 *)arg2)->value = TaLogic_IsOpenUnit_00126380(((Unit_00125B70 *)arg0)->position >> 8, ((Unit_00125B70 *)arg0)->position & 0xFF, arg0);
        }
        TaLogic005_InitRogicControl(arg0, arg3);
    }
    }
    return 0;
}

s32 TaLogic_IsOpenUnit_00126380(s32 arg0, s32 arg1, void *arg2) {
    extern s32 SzDuel_GetUnitCardNo();
    s32 card;
    s32 position;
    s32 owner;
    s32 *info;
    u8 count;
    s32 i;

    card = SzDuel_GetUnitCardNo(arg0, arg1);
    position = SzDuel_GetUnitLoc(arg0, arg1);
    owner = Ta_IsUnitControl(arg0, arg1);
    info = SzDuel_GetUnitEffect(arg0, arg1, 0);
    count = 0;
    if (SzDuel_GetUnitStatus(arg0, arg1, 4) != 0) {
        return 0;
    }
    switch (SzDuel_GetUnitKind(arg0, arg1) >> 5) {
    case 0:
        switch (SzDuel_GetUnitCardNo(arg0, arg1)) {
        case 0x230:
            for (card = 1; card <= 5; card++) {
                if (SzDuel_GetUnitCardNo(arg0, card) == 0x258 && arg0 == Ta_IsUnitControl(arg0, card)) {
                    count++;
                }
                if (SzDuel_GetUnitCardNo((arg0 == 0) ? 1 : 0, card) == 0x258 &&
                    arg0 == Ta_IsUnitControl((arg0 == 0) ? 1 : 0, card)) {
                    count++;
                }
            }
            if (count >= 2) {
                return 1;
            }
            break;
        case 0x258:
            for (card = 1; card <= 5; card++) {
                if (SzDuel_GetUnitCardNo(arg0, card) == 0x230 && arg0 == Ta_IsUnitControl(arg0, card)) {
                    count++;
                }
                if (SzDuel_GetUnitCardNo((arg0 == 0) ? 1 : 0, card) == 0x230 &&
                    arg0 == Ta_IsUnitControl((arg0 == 0) ? 1 : 0, card)) {
                    count++;
                }
            }
            if (count >= 2) {
                return 1;
            }
            break;
        case 0x251:
            for (card = 1; card <= 5; card++) {
                if ((SzDuel_GetUnitKind(arg0, card) & 0x1F) == 0x10 && arg0 == Ta_IsUnitControl(arg0, card)) {
                    count++;
                }
                if ((SzDuel_GetUnitKind((arg0 == 0) ? 1 : 0, card) & 0x1F) == 0x10 &&
                    arg0 == Ta_IsUnitControl((arg0 == 0) ? 1 : 0, card)) {
                    count++;
                }
            }
            if (count >= 3) {
                return 1;
            }
            break;
        case 0x235:
            for (card = 6; card < 11; card++) {
                if (SzDuel_GetUnitStatus(arg0, arg1, 4) != 0 && arg0 == Ta_IsUnitControl(arg0, card)) {
                    count++;
                }
                if (SzDuel_GetUnitStatus((arg0 == 0) ? 1 : 0, arg1, 4) != 0 &&
                    arg0 == Ta_IsUnitControl((arg0 == 0) ? 1 : 0, card)) {
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
        if (TaLogic_GetActionReaction(arg0, arg1, 0, 0, 6, 0) == 5) {
            return 2;
        }
        if (TaLogic005_IsDoCerem(Ta_IsUnitControl(arg0, arg1), card) == 1 &&
            SzDuel_GetField(position & 0xFF, position >> 8) != 9) {
            return 1;
        }
        break;
    case 1:
        if (info == NULL) {
            return 2;
        }
        if (TaLogic_GetActionReaction(arg0, arg1, 0, 0, 6, 0) == 5) {
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

static inline s32 max_00126840(s32 a, s32 b) {
    if (a < b) {
        return b;
    }
    return a;
}

s32 TaLogic005_IsOpenMoveUnit(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 min_y;
    s32 min_x;

    min_y = arg3 < arg5 ? arg3 : arg5;
    arg5 = max_00126840(arg5, arg3);
    min_x = arg2 < arg4 ? arg2 : arg4;
    arg4 = max_00126840(arg4, arg2);
    if ((arg4 - min_x) + (arg5 - min_y) != 2) {
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

typedef struct State_00126940 {
    u8 pad0[4];
    u16 field4;
    u16 pad6;
    u32 field8;
} State_00126940;

void TaLogic005_InitRogicControl(void *arg0, u8 arg1) {
    State_00126940 *state = (State_00126940 *)arg0;

    if (arg1 < 2) {
        if (arg1 == 1) {
            state->field4 = (state->field4 & 0xFF) | 0xFF00;
        } else {
            state->field4 = (state->field4 & 0xFF00) | 0xFF;
        }
        if (arg1 == 1) {
            state->field8 = (state->field8 & 0xFFFF) | 0xFFFF0000;
        } else {
            state->field8 = (state->field8 & 0xFFFF0000) | 0xFFFF;
        }
    }
}

s32 TaLogic005_IsDoCerem(s32 arg0, s32 arg1) {
    s32 data[4];
    s32 i;
    s32 mask;
    s32 y;
    s32 x;
    s32 cell;
    s32 coords;

    Ta_GetCeremSacrifice(data, *(s32 *)((u8 *)TaHand_GetCardEffect(arg1, 0) + 4));
    if ((mask = Ta_GetSacrificeUnit(data, arg0)) < 0) {
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

s32 func_00126AB0(s32 arg0, void *arg1) {
    Req_00126AB0 req;
    Work_00126AB0 *w;
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
        if (TaLogic_GetMinimumTask_00121800(w, &req, arg0) == 0) {
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

s32 TaLogic_GetMinimumTask_00126C80(void *work, void *arg1, s32 arg2) {
    u16 *arg0 = work;
    s32 side;
    s32 found;
    s32 result;
    s32 index;

    side = SzDuel_GetTurnOwner();
    found = 0;
    if ((result = TaLogic_GetNextActiveUnit_001273E0(arg0, side, (s32)arg1)) < 0) {
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
    TaLogic_CommandUnit_001271F0(arg0 + index * 8);
    switch ((arg0[index * 8 + 2] >> 8) & 0xFF) {
    case 5:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_RunMission_001291C0(arg0 + index * 8, side, arg1, 1);
            found = 1;
        }
        break;
    case 2:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            if (TaLogic_GetMinimumTask_AtkMission_00129D00(arg0 + index * 8, side, arg1, 1) < 0) {
                TaLogic006_InitRogicControl(arg0 + index * 8, 1);
                return 1;
            }
            found = 1;
        }
        break;
    case 10:
        if (TaLogic_GetMinimumTask_Summon_00127E30(arg0[index * 8], side, (s32)arg1) < 0) {
            TaLogic006_InitRogicControl(arg0 + index * 8, 1);
            *(u8 *)((u8 *)arg1 + 2) = 0xFF;
            *(s32 *)((u8 *)arg1 + 0xC) = 0;
        } else {
            TaLogic006_InitRogicControl(arg0 + index * 8, 1);
            found = 1;
        }
        break;
    case 6:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_MoveMission_0012A2E0(arg0 + index * 8, side, arg1, 1, 0);
            found = 1;
        }
        break;
    case 3:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_MoveMission_0012A2E0(arg0 + index * 8, side, arg1, 1, 1);
            found = 1;
        }
        break;
    case 9:
        TaLogic_GetMinimumTask_EncMission(arg0 + index * 8, side, arg1, 1, 0, TaLogic_GetWarnHideLvl_0012B1B0(side), 5, 1);
        found = 1;
        break;
    case 11:
        TaLogic_GetMinimumTask_TrapMission_0012AAC0(arg0 + index * 8, side, arg1, 1);
        found = 1;
        break;
    case 12:
        TaLogic_GetMinimumTask_ReviveMission_00129700(arg0 + index * 8, side, (s32)arg1, 1);
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
            TaLogic_GetMinimumTask_RunMission_001291C0(arg0 + index * 8, side, arg1, 0);
            found = 1;
        }
        break;
    case 2:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            if (TaLogic_GetMinimumTask_AtkMission_00129D00(arg0 + index * 8, side, arg1, 0) < 0) {
                TaLogic_GetMinimumTask_RunMission_001291C0(arg0 + index * 8, side, arg1, 0);
            }
            found = 1;
        }
        break;
    case 10:
        if (TaLogic_GetMinimumTask_Summon_00127E30(arg0[index * 8], side, (s32)arg1) < 0) {
            TaLogic006_InitRogicControl(arg0 + index * 8, 0);
            *(u8 *)((u8 *)arg1 + 2) = 0xFF;
            found = 1;
            *(s32 *)((u8 *)arg1 + 0xC) = 0;
        } else {
            TaLogic_InitRogicControl(arg0 + index * 8, 0);
            found = 1;
        }
        break;
    case 6:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_MoveMission_0012A2E0(arg0 + index * 8, side, arg1, 0, 0);
            found = 1;
        }
        break;
    case 3:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_MoveMission_0012A2E0(arg0 + index * 8, side, arg1, 0, 1);
            found = 1;
        }
        break;
    case 11:
        TaLogic_GetMinimumTask_TrapMission_0012AAC0(arg0 + index * 8, side, arg1, 0);
        found = 1;
        break;
    case 9:
        TaLogic_GetMinimumTask_EncMission(arg0 + index * 8, side, arg1, 0, 0, TaLogic_GetWarnHideLvl_0012B1B0(side), 5, 1);
        found = 1;
        break;
    case 12:
        TaLogic_GetMinimumTask_ReviveMission_00129700(arg0 + index * 8, side, (s32)arg1, 0);
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

typedef struct Entry_001271F0 {
    u16 coordinates;
    u16 pad2;
    s16 action;
    u16 pad6;
    s32 target;
} Entry_001271F0;

s32 TaLogic_CommandUnit_001271F0(void *arg0) {
    Entry_001271F0 *entry = arg0;
    s32 card;
    u16 coordinates;

    card = Ta_IsUnitControl(entry->coordinates >> 8, entry->coordinates & 0xFF);
    if (SzDuel_GetUnit(entry->coordinates >> 8, entry->coordinates & 0xFF) != 0) {
        if (SzDuel_GetUnitStatus(entry->coordinates >> 8, entry->coordinates & 0xFF, 0) == 0) {
            coordinates = entry->coordinates;
            if (coordinates != 0xFFFF) {
                if ((coordinates & 0xFF) == 0) {
                    if (entry->target == -1) {
                        if (TaLogic_IsAttackedNow(coordinates >> 8, coordinates & 0xFF, 0) == 1) {
                            if (SzDuel_InqHandPhase(entry->coordinates >> 8) == 1) {
                                entry->action = 0x50A;
                            } else {
                                entry->action = 0x5FF;
                            }
                        } else if (SzDuel_InqHandPhase(entry->coordinates >> 8) == 1) {
                            entry->action = 0xA06;
                            entry->target &= 0xFFFF0000;
                        } else {
                            entry->action = 0x6FF;
                            entry->target = (u16)entry->target;
                        }
                    }
                } else {
                    switch (SzDuel_GetUnitKind(coordinates >> 8, coordinates & 0xFF) >> 5) {
                    case 0:
                        if (TaUtil_IsExMonster(entry->coordinates >> 8, entry->coordinates & 0xFF) == 1) {
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

s32 TaLogic_GetNextActiveUnit_001273E0(u16 *arg0, s32 arg1, s32 arg2) {
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
    TaLogic_CommandUnit_001271F0(arg0 + idx * 8);
    if (((arg0[idx * 8 + 2] >> 8) & 0xFF) == 10) {
        if (SzDuel_InqHandPhase(arg1) == 1 && TaLogic_GetMinimumTask_Summon_00127E30(pos, arg1, arg2) >= 0) {
            return pos | 0x10000;
        }
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_GetUnitStatus(arg1, 0, 0) == 0) {
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_InqHandPhase(arg1) == 1 && TaLogic_GetMinimumTask_Summon_00127E30(pos, arg1, arg2) >= 0) {
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
    u16 coordinates;
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


void TaLogic006_CommandBtlUnit(void *arg0, s32 arg1) {
    extern void TaLogic_InitIgnoreLst();
    extern s32 TaLogic_IsRootOpen();
    extern s32 TaLogic006_GetNearUnit();
    Entry_001277C0 *entry = arg0;
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
        TaLogic_InitIgnoreLst(work);
        if (arg1 != 0) {
            if (TaLogic_IsRootOpen(entry->coordinates >> 8, entry->coordinates & 0xFF, pos & 0xFF, pos >> 8,
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
                                  Ta_GetCurrentSide(entry->coordinates >> 8, entry->coordinates & 0xFF) == 0 ? 1 : 0,
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

void TaLogic006_GetNearUnit(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28) {
    TaLogic_GetNearUnit(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
                  arg_sp0, arg_sp8, arg_sp10, arg_sp18, arg_sp20,
                  0, 2000, arg_sp28);
}

void TaLogic006_CommandInvadeUnit(void *arg0) {
    s32 temp_v0_2;
    u16 temp_v0;

    temp_v0 = *(u16 *)arg0;
    temp_v0_2 = SzDuel_GetUnitLoc((s32) temp_v0 >> 8, temp_v0 & 0xFF);
    *(s16 *)((u8 *)arg0 + 4) = 0x6FF;
    if ((temp_v0_2 >> 8) < 3) {
        *(u32 *)((u8 *)arg0 + 8) = *(u16 *)((u8 *)arg0 + 8) | 0x03010000;
    } else {
        *(u32 *)((u8 *)arg0 + 8) = *(u16 *)((u8 *)arg0 + 8) | 0x05020000;
    }
}

typedef struct {
    u16 value;
    u8 flag;
} Entry_00127B00;


void TaLogic006_CommandEfcMonster(void *arg0) {
    extern void TaLogic_InitIgnoreLst();
    extern s32 SzDuel_GetUnitCardNo();
    extern s32 TaLogic_GetNearUnit();
    u8 scratch[0x70];
    Entry_00127B00 entries[0x17];
    s16 result_a;
    s16 result_b;
    s32 i;
    Entry_00127B00 *entry;
    s32 temp_s0;
    s32 temp_s1;
    s32 temp_v0_2;
    s32 result;
    s32 high;
    s32 low;
    s32 var_s5;
    s32 code;

    if ((temp_v0_2 = SzDuel_GetUnit(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF)) != 0) {
        temp_s0 = Ta_GetCurrentSide(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF);
        temp_s1 = SzDuel_GetUnitLoc(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF);
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
        code = SzDuel_GetUnitCardNo(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF);
        switch (code) {
        case 0x6F:
            if (TaLogic_CommandGunnerUnit(arg0, 0) == 1) {
                *(s16 *)((u8 *)arg0 + 4) = 0xBFF;
                return;
            }
            goto fallback_00127B00;
        case 0x6C:
            var_s5 = 1;
            high = temp_s1 >> 8;
            low = temp_s1 & 0xFF;
            goto loop_00127B00;
        default:
            goto fallback_00127B00;
        }
loop_00127B00:
                result = TaLogic_GetWarnHideLvl_0012B1B0(temp_s0);
                entry = entries;
                result = TaLogic_GetNearUnit((s32)arg0, 0, temp_v0_2, low, high,
                                      temp_s0 == 0 ? 1 : 0,
                                      var_s5 & 0xFF, result, (s32)entry, 0,
                                      (s32)&result_a, (s32)&result_b, 2, 0, 0x7D0,
                                      (s32)scratch);
                if (result != 0) {
                    if (result != 1) {
                        if (result != 2) {
                            if (result != 3) {
                                var_s5++;
                                goto retry_00127B00;
                            }
                        }
                        *(s16 *)((u8 *)arg0 + 4) = 0x3FF;
                        *(u32 *)((u8 *)arg0 + 8) = (temp_s1 << 16) | *(u16 *)((u8 *)arg0 + 8);
                        return;
                    }
                } else {
                    *(s16 *)((u8 *)arg0 + 4) = 0x3FF;
                    *(u32 *)((u8 *)arg0 + 8) = (temp_s1 << 16) | *(u16 *)((u8 *)arg0 + 8);
                    return;
                }
                return;
retry_00127B00:
        if (var_s5 <= 2) {
            goto loop_00127B00;
        }
        *(s16 *)((u8 *)arg0 + 4) = 0x3FF;
        *(u32 *)((u8 *)arg0 + 8) = (temp_s1 << 16) | *(u16 *)((u8 *)arg0 + 8);
        return;
fallback_00127B00:
        TaLogic006_CommandBtlUnit(arg0, 1);
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

void TaLogic006_CommandSpellUnit(void *arg0) {
    extern s32 SzDuel_GetUnitCardNo();
    Obj_00127D20 *obj = arg0;
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

s32 TaLogic006_GetSummonPiece(s32 arg0, u8 arg1, void *arg2, s32 arg3);
s32 TaLogic_GetNearCard2(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8,
                  s32 arg9);

s32 TaLogic_GetMinimumTask_Summon_00127E30(s32 arg0, s32 arg1, s32 arg2) {
    extern s32 TaLogic_GetUnitNum(s32, s32);
    Work_00127E30 work;
    s32 ret;
    s32 res;
    s32 pos;
    s32 kind;
    Ctx_00127E30 *ctx = (Ctx_00127E30 *)arg2;

    ctx->id = arg0;
    if (SzDuel_InqHandPhase(arg1) == 0) {
        return -1;
    }
    if (TaLogic_GetUnitNum(arg1, 0) == 5 && TaLogic_GetUnitNum(arg1, 1) == 5) {
        return -1;
    }
    kind = TaLogic006_IsHandPlay(arg1, &work);
    if (kind < 0) {
        return -1;
    }
    ctx->unk2 = 10;
    ctx->unkC = 0;
    pos = SzDuel_GetUnitLoc(arg0 >> 8, arg0 & 0xFF);
    if (kind == 0) {
        if (TaLogic006_SetComboQue(arg1, (u8 *)ctx, &work) >= 0) {
            ret = TaLogic_GetNearCard2(&work, pos & 0xFF, pos >> 8, arg1 == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, TaLogic_GetWarnHideLvl_0012B1B0(arg1));
            if (ret < 0) {
                if (SzDuel_GetUnitMonsterCount(arg1) < 5) {
                    res = TaLogic006_GetSummonPiece(arg1, kind, &work, ret);
                    if (res < 0) {
                        return -1;
                    }
                    ctx->unk4 = res;
                    return 1;
                }
            } else {
                res = TaLogic006_GetSummonPiece(arg1, kind, &work, ret);
                if (res < 0) {
                    return -1;
                }
                ctx->unk4 = res;
                return 1;
            }
        }
    } else {
        ret = TaLogic_GetNearCard2(&work, pos & 0xFF, pos >> 8, arg1 == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, TaLogic_GetWarnHideLvl_0012B1B0(arg1));
    }
    if (kind == 2) {
        TaLogic006_SetSpecialComboQue(arg1, ctx, &work);
        res = TaLogic006_GetSummonPiece(arg1, kind, &work, ret);
        if (res < 0) {
            return -1;
        }
        ctx->unk4 = res;
        return 1;
    }
    if (TaLogic006_GetSpellPlay(arg1, (u8 *)ctx, &work, work.unk3C) < 0) {
        return -1;
    }
    res = TaLogic006_GetSummonPiece(arg1, kind, &work, ret);
    if (res < 0) {
        return -1;
    }
    ctx->unk4 = res;
    return 1;
}

s32 TaLogic006_IsHandPlay(s32 arg0, void *arg1) {
    extern s32 TaLogic_GetUnitNum();
    extern s32 func_0012B000();
    s32 cards[8];
    u8 buffer[32];
    u8 type0;
    u8 type1;
    s32 result;
    s32 value;

    type0 = TaLogic_GetUnitNum(arg0, 0);
    type1 = TaLogic_GetUnitNum(arg0, 1);
    if (arg1 == NULL) {
        return -1;
    }
    TaHand_GetNextHand(arg0, cards);
    if (type0 == 5) {
        if (TaLogic006_GetSpellPlay(arg0, buffer, arg1, 999) >= 0) {
            return 1;
        }
        return -1;
    }
    if (type1 == 5) {
        s32 i = 0;
        s32 *p;
        if (i < TaHand_GetNextHandNum(arg0)) {
            p = cards;
            do {
                if ((TaHand_GetCardKind(*p) >> 5) == 0 && TaHand_IsCardSummon2(arg0, *p) == 1) {
                    SzDuel_InitCardInfo(arg1, cards[i]);
                    return 0;
                }
                p++;
                i++;
            } while (i < TaHand_GetNextHandNum(arg0));
        }
        return -1;
    }
    if (TaLogic006_GetSpecCardPlay(arg0, buffer, arg1, 699) >= 0) {
        if (TaLogic_IsAttackedNow(arg0, 0, 0) == 1 || func_0012B000(arg0) == 1) {
            return 2;
        }
    }
    if (TaLogic006_GetSpecCardPlay(arg0, buffer, arg1, 108) >= 0) {
        return 2;
    }
    value = TaLogic_GetMaxAPGraveCard(arg0, 3);
    if (value >= 0) {
        if ((u16)value >= 2400 && TaLogic006_GetSpecCardPlay(arg0, buffer, arg1, 685) >= 0) {
            return 2;
        }
    }
    if (TaLogic006_GetSpecCardPlay(arg0, buffer, arg1, 851) >= 0 && TaLogic006_IsDoCerem(arg0, 851) == 1) {
        return 2;
    }
    if (type0 == 0) {
        s32 *p;
        s32 i = 0;
        if (i < TaHand_GetNextHandNum(arg0)) {
            p = cards;
            do {
                if ((TaHand_GetCardKind(*p) >> 5) == 0 && TaHand_IsCardSummon2(arg0, *p) == 1) {
                    return 0;
                }
                p++;
                i++;
            } while (i < TaHand_GetNextHandNum(arg0));
        }
    }
    {
        s32 *p;
        s32 i = 0;
        if (i < TaHand_GetNextHandNum(arg0)) {
            p = cards;
            do {
                if ((TaHand_GetCardKind(*p) >> 5) == 0 && TaHand_IsCardSummon2(arg0, *p) == 1) {
                    SzDuel_InitCardInfo(arg1, cards[i]);
                    return 0;
                }
                p++;
                i++;
            } while (i < TaHand_GetNextHandNum(arg0));
        }
    }
    result = TaLogic006_GetSpellPlay(arg0, buffer, arg1, 999);
    if (result >= 0) {
        return result;
    }
    return -1;
}

s32 TaLogic006_GetSpecCardPlay(s32 arg0, void *arg1, void *arg2, s32 arg3) {
    s32 index;
    s32 *entry;
    s32 target;
    s32 entries[8];

    TaHand_GetNextHand(arg0, entries);
    index = 0;
    if (index < TaHand_GetNextHandNum(arg0)) {
        target = arg3 & 0xFFFF;
        entry = entries;
        do {
            if (target == *entry && TaHand_IsCardSummon2(arg0, *entry) == 1) {
                *((s8 *)arg1 + 6) = index;
                SzDuel_InitCardInfo(arg2, entries[index]);
                return TaHand_GetCardKind(entries[index]) >> 5;
            }
            entry++;
            index++;
        } while (index < TaHand_GetNextHandNum(arg0));
    }
    return -1;
}

s32 TaLogic006_GetSpellPlay(s32 arg0, u8 *arg1, void *arg2, s32 arg3) {
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


s32 TaLogic006_SetComboQue(s32 arg0, u8 *arg1, void *arg2) {
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
                    *node = TaLogic_GetFusionTree(arg0, (struct TreeTag *)*node, i & 0xFF, card & 0xFFFF, 0, (u16 *)&a, (u16 *)&b);
                    *node = TaLogic_GetFusionRes(*node);
                    value = TaLogic_GetEnchantQue(arg0, *node, 0, 0);
                    if (TaHand_IsCardSummon2(arg0, card) == 1) {
                        if (best < value) {
                            TaLogic_ConvEmptyCombo_00128900(arg0, *node, entries);
                            TaLogic_CopyArray((u8 *)*node + 2, arg1 + 6);
                            SzDuel_InitCardInfo(arg2, **node);
                            ((Sprite_00128720 *)arg2)->x = (value >> 16) - (((Sprite_00128720 *)arg2)->info->x & 0x1FFF);
                            ((Sprite_00128720 *)arg2)->y = (value & 0xFFFF) - (((Sprite_00128720 *)arg2)->info->y & 0x1FFF);
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
} Info_00128900;

void TaLogic_ConvEmptyCombo_00128900(s32 arg0, void *arg1, s32 *arg2) {
    Info_00128900 *info = arg1;
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
                if (card != 0x3E7 && TaLogic006_IsRefuseEmptyCombo(card) == 0 && level >= TaHand_GetCardSummonCost2(card, arg0)) {
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

s32 TaLogic006_IsRefuseEmptyCombo(s32 arg0) {
    if ((TaHand_GetCardKind(arg0) >> 5) != 0) {
        return 1;
    }
    if (arg0 == 0x6C || arg0 == 0x6F || arg0 == 0x68) {
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

s32 TaLogic006_SetSpecialComboQue(s32 arg0, void *arg1, void *arg2) {
    Obj1_00128B50 *o1 = arg1;
    Obj2_00128B50 *o2 = arg2;
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
            if (o2->id == list[i] && TaHand_IsCardSummon2(arg0, list[i]) == 1) {
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

INCLUDE_ASM("asm/nonmatchings/main_007", TaLogic006_GetSummonPiece);

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


s32 TaLogic_GetMinimumTask_RunMission_001291C0(u16 *arg0, s32 arg1, void *arg2, u8 arg3) {
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
    Output_001291C0 *out = arg2;

    position = SzDuel_GetUnitLoc(*arg0 >> 8, *arg0 & 0xFF);
    i = 0;
    do {
        cells[i].low = cells[i].high = 15;
        i++;
    } while (i < 12);

    {
        u16 value = (u16)TaLogic_GetWarnHideLvl_0012B1B0(arg1);
        originalX = position & 0xFF;
        originalY = position >> 8;
        if (TaLogic_GetUnitWarning(originalX, originalY, *arg0, 3, value, 0) == 0) {
            out->id = *arg0;
            out->action = 6;
            out->position = position;
            out->mode = TaLogic_IsDefStyleUnit(*arg0 >> 8, *arg0 & 0xFF, out->position, 1, 0);
            out->value = TaLogic_IsOpenUnit_0012B210(*arg0 >> 8, *arg0 & 0xFF, arg0);
            TaLogic006_InitRogicControl(arg0, arg3);
            return 0;
        } else {
            result = GetMoveRev(SzDuel_GetUnit(*arg0 >> 8, *arg0 & 0xFF), originalX, originalY);
            if (result == 0) {
                out->id = *arg0;
                out->action = 6;
                out->position = position;
                out->mode = TaLogic_IsDefStyleUnit(*arg0 >> 8, *arg0 & 0xFF, out->position, 1, 0);
                out->value = TaLogic_IsOpenUnit_0012B210(*arg0 >> 8, *arg0 & 0xFF, arg0);
                TaLogic006_InitRogicControl(arg0, arg3);
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
                                value = (u16)TaLogic_GetWarnHideLvl_0012B1B0(arg1);
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
                        out->mode = TaLogic_IsDefStyleUnit(*arg0 >> 8, *arg0 & 0xFF, out->position, 0, 0);
                    }
                    out->value = TaLogic_IsOpenUnit_0012B210(*arg0 >> 8, *arg0 & 0xFF, arg0);
                } else {
                    out->id = *arg0;
                    out->action = 6;
                    out->position = position;
                    out->mode = TaLogic_IsDefStyleUnit(*arg0 >> 8, *arg0 & 0xFF, out->position, 1, 0);
                    out->value = TaLogic_IsOpenUnit_0012B210(*arg0 >> 8, *arg0 & 0xFF, arg0);
                }
                TaLogic006_InitRogicControl(arg0, arg3);
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


s32 TaLogic_GetMinimumTask_ReviveMission_00129700(void *arg0, s32 arg1, s32 arg2, u8 arg3) {
    extern s32 TaLogic_IsRunPassRoot(s32, s32, s32, s32, s32, s32, void *, u8);
    Coord_00129700 positions[12];
    s32 i;
    Coord_00129700 *p;
    s32 position;

    position = SzDuel_GetUnitLoc(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF);
    p = positions;
    i = 0;
    do {
        p->x = p->y = 15;
        i++;
        p++;
    } while (i < 12);
    if (TaLogic_IsOpenUnit_0012B210(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF, arg0) == 1) {
        s32 data;
        s32 card;
        s32 player;

        data = TaLogic_GetMaxAPGraveCard(arg1, 3);
        player = data >> 24;
        card = TaLogic_GetGraveEntryAfterScreen(player & 0xFF, (data >> 16) & 0xFF, 29);
        ((Result_00129700 *)arg2)->card = *(u16 *)arg0;
        ((Result_00129700 *)arg2)->action = 12;
        ((Result_00129700 *)arg2)->flags = TaLogic_IsDefStyleUnit(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF, *(u16 *)(arg2 + 4), 1, 0);
        ((Result_00129700 *)arg2)->count = 1;
        *(u16 *)(arg2 + 4) = ((player & 15) << 8) | card;
        TaLogic006_InitRogicControl(arg0, arg3);
        return 0;
    }
    if (SzDuel_GetUnitStatus(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF, 4) != 0) {
        SzDuel_SetUnitStatus(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF, 0, 1);
        ((Result_00129700 *)arg2)->card = *(u16 *)arg0;
        ((Result_00129700 *)arg2)->action = 14;
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

        card = TaLogic_GetWarnHideLvl_0012B1B0(arg1);
        centerX = position & 0xFF;
        centerY = position >> 8;
        if (TaLogic_GetUnitWarning(centerX, centerY, *(u16 *)arg0, 3, card, 0) == 0) {
            ((Result_00129700 *)arg2)->card = *(u16 *)arg0;
            ((Result_00129700 *)arg2)->action = 6;
            *(u16 *)(arg2 + 4) = position;
            ((Result_00129700 *)arg2)->flags = TaLogic_IsDefStyleUnit(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF, *(u16 *)(arg2 + 4), 1, 0);
            ((Result_00129700 *)arg2)->count = 2;
            TaLogic006_InitRogicControl(arg0, arg3);
        } else {
            rangeResult = GetMoveRev(SzDuel_GetUnit(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF), centerX, centerY);
            if (rangeResult == 0) {
                ((Result_00129700 *)arg2)->card = *(u16 *)arg0;
                ((Result_00129700 *)arg2)->action = 6;
                *(u16 *)(arg2 + 4) = position;
                ((Result_00129700 *)arg2)->flags = TaLogic_IsDefStyleUnit(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF, *(u16 *)(arg2 + 4), 1, 0);
                ((Result_00129700 *)arg2)->count = 2;
                TaLogic006_InitRogicControl(arg0, arg3);
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
                if ((*(u16 *)arg0 & 0xFF) == 0) {
                    flags = (u8)TaLogic_IsAttackedNow(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF, 0);
                } else {
                    flags = 0;
                }
                for (x = (u8)minX; x <= (u8)maxX; x++) {
                    for (y = (u8)minY, packedY = y << 8; y <= (u8)maxY; packedY += 0x100, y++) {
                        if (((x < centerX ? centerX : x) - (centerX < x ? centerX : x)) +
                            ((y < centerY ? centerY : y) - (centerY < y ? centerY : y)) <= (rangeResult & 15)) {
                            if (TaLogic_IsRunPassRoot(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF, centerX, centerY, x, y, arg0, (u8)flags) == 1 &&
                                (TaLogic_IsAttackedNow2(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF, x, y, 0) == 0 || (u8)*(u16 *)arg0 == 0)) {
                                card = TaLogic_GetWarnHideLvl_0012B1B0(arg1);
                                cost = TaLogic_GetUnitWarning(x, y, *(u16 *)arg0, 3, card, 0);
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
                    ((Result_00129700 *)arg2)->card = *(u16 *)arg0;
                    ((Result_00129700 *)arg2)->action = 6;
                    *(u16 *)(arg2 + 4) = bestPosition;
                    if (bestPosition == position) {
                        ((Result_00129700 *)arg2)->flags = TaLogic_IsDefStyleUnit(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF, *(u16 *)(arg2 + 4), 1, 0);
                    } else {
                        ((Result_00129700 *)arg2)->flags = TaLogic_IsDefStyleUnit(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF, *(u16 *)(arg2 + 4), 0, 0);
                    }
                    ((Result_00129700 *)arg2)->count = 2;
                } else {
                    ((Result_00129700 *)arg2)->card = *(u16 *)arg0;
                    ((Result_00129700 *)arg2)->action = 6;
                    *(u16 *)(arg2 + 4) = position;
                    ((Result_00129700 *)arg2)->flags = TaLogic_IsDefStyleUnit(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF, *(u16 *)(arg2 + 4), 1, 0);
                    ((Result_00129700 *)arg2)->count = 2;
                }
                TaLogic006_InitRogicControl(arg0, arg3);

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

s32 TaLogic_GetMinimumTask_AtkMission_00129D00(void *arg0, s32 arg1, void *arg2, u8 arg3) {
    extern void TaLogic_GetInvadeRoot();
    Input_00129D00 *in = arg0;
    Output_00129D00 *out = arg2;
    s32 sourcePosition;
    s32 count;
    s32 sourceY;
    s32 sourceX;
    s32 found;
    Point_00129D00 points[12];
    s32 targetPosition;
    s32 i;
    Point_00129D00 *p;

    if (SzDuel_GetUnit(TARGET_00129D00(in, arg3) >> 8, TARGET_00129D00(in, arg3) & 0xFF) == 0) {
        TaLogic_InitRogicControl(arg0, 1);
        return -1;
    } else {
        s32 initialResult;
        initialResult = TaLogic_IsOpenUnit_0012B210(in->position >> 8, in->position & 0xFF, arg0);
        sourcePosition = SzDuel_GetUnitLoc(in->position >> 8, in->position & 0xFF);
        targetPosition = SzDuel_GetUnitLoc(TARGET_00129D00(in, arg3) >> 8, TARGET_00129D00(in, arg3) & 0xFF);
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
            score = TaLogic_GetUnitWarning(sourceX, sourceY, arg1, 3, 1, (u8)TaLogic_GetWarnHideLvl_0012B1B0(arg1));
            if (score >= SzDuel_GetUnitAP(in->position >> 8, in->position & 0xFF, 0)) {
                out->status = TaLogic_IsDefStyleUnit(in->position >> 8, in->position & 0xFF, out->destination, 1, 0);
            } else {
                out->status = TaLogic_IsDefStyleUnit(in->position >> 8, in->position & 0xFF, out->destination, 0, 0);
            }
            TaLogic006_InitRogicControl(arg0, arg3);
            return 0;
        } else {
            s32 targetY;
            s32 targetX;
            Point_00129D00 *candidate;
            s32 index;
            s32 bestScore;
            s32 bestIndex;
            s32 position = in->position;
            u16 value = TaLogic_GetWarnHideLvl_0012B1B0(arg1);
            TaLogic_GetInvadeRoot(position >> 8, position & 0xFF, points, sourceX, sourceY,
                           targetX = targetPosition & 0xFF, targetY = targetPosition >> 8,
                           TARGET_00129D00(in, arg3), 0, 30, value);
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
                        score = TaLogic_GetUnitWarning(candidate->x, candidate->y, arg1, 5, 1,
                                              (u8)TaLogic_GetWarnHideLvl_0012B1B0(arg1));
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
                TaLogic_InitRogicControl(arg0, arg3);
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
                TaLogic_InitRogicControl(arg0, arg3);
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


static inline u32 target_0012A2E0(void *unit, s32 side) {
    return side == 1 ? (u32)(u16)(((Unit_0012A2E0 *)unit)->target.packed >> 16) : (u32)((Unit_0012A2E0 *)unit)->target.low;
}

static inline u32 minY_0012A2E0(void *unit, s32 side, u8 coord) {
    return coord < (target_0012A2E0(unit, side) >> 8) ? coord : (target_0012A2E0(unit, side) >> 8);
}

static inline u32 maxY_0012A2E0(void *unit, s32 side, u8 coord) {
    return (target_0012A2E0(unit, side) >> 8) < coord ? coord : (target_0012A2E0(unit, side) >> 8);
}

static inline u32 minX_0012A2E0(void *unit, s32 side, u8 coord) {
    return coord < (target_0012A2E0(unit, side) & 0xFF) ? coord : (target_0012A2E0(unit, side) & 0xFF);
}

static inline u32 maxX_0012A2E0(void *unit, s32 side, u8 coord) {
    return (target_0012A2E0(unit, side) & 0xFF) < coord ? coord : (target_0012A2E0(unit, side) & 0xFF);
}

s32 TaLogic_GetMinimumTask_MoveMission_0012A2E0(void *arg0, s32 arg1, void *arg2, u8 arg3, u8 arg4) {
    extern s32 TaLogic_GetUnitWarning();
    extern void TaLogic_GetRoot();
    extern s32 TaLogic_IsDefStyleUnit(s32, s32, s32, u8, s32);
    Coord_0012A2E0 coords[12];
    s32 initial;
    s32 cell;
    s32 count;

    initial = SzDuel_GetUnitLoc(((Unit_0012A2E0 *)arg0)->position >> 8, ((Unit_0012A2E0 *)arg0)->position & 0xFF);
    {
    s32 bestScore;
    s32 best;
    s32 side = arg3;
    Coord_0012A2E0 *candidate;
    s32 index;
    if (target_0012A2E0(arg0, side) == 0xFFFF) {
        if (initial == target_0012A2E0(arg0, side)) {
            ((Output_0012A2E0 *)arg2)->position = ((Unit_0012A2E0 *)arg0)->position;
            ((Output_0012A2E0 *)arg2)->kind = 6;
            ((Output_0012A2E0 *)arg2)->target = initial;
            ((Output_0012A2E0 *)arg2)->flag = TaLogic_IsDefStyleUnit(((Unit_0012A2E0 *)arg0)->position >> 8, ((Unit_0012A2E0 *)arg0)->position & 0xFF, ((Output_0012A2E0 *)arg2)->target, arg4, 0);
            ((Output_0012A2E0 *)arg2)->value = TaLogic_IsOpenUnit_0012B210(((Unit_0012A2E0 *)arg0)->position >> 8, ((Unit_0012A2E0 *)arg0)->position & 0xFF, arg0);
            TaLogic006_InitRogicControl(arg0, arg3);
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

    cell = SzDuel_GetMapUnitID(target_0012A2E0(arg0, side) & 0xFF, ((u32)target_0012A2E0(arg0, side)) >> 8);
    if (cell < 0) {
        cell = 0xFFFF;
    }
    TaLogic_GetRoot(((Unit_0012A2E0 *)arg0)->position >> 8, ((Unit_0012A2E0 *)arg0)->position & 0xFF,
                 coords, initial & 0xFF, initial >> 8, target_0012A2E0(arg0, side) & 0xFF,
                 ((u32)target_0012A2E0(arg0, side)) >> 8, (u16)cell, 7);
    count = TaLogic_GetMinGoalCount((u8 *)coords);
    {
        if (count > 0) {
        best = 0xFF;
        bestScore = 0xFFFF;
        for (index = 0; index < count; index++) {
                if (SzDuel_GetMapUnit(candidate->x, candidate->y) == 0) {
                    s32 score = TaLogic_GetUnitWarning(candidate->x, candidate->y, arg1, 5, 1, (u8)TaLogic_GetWarnHideLvl_0012B1B0(arg1));
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
                        bestMinY = minY_0012A2E0(arg0, side, bestY);
                        bestMaxY = maxY_0012A2E0(arg0, side, bestY);
                        bestX = (&coords[best])->x;
                        bestMinX = minX_0012A2E0(arg0, side, bestX);
                        bestMaxX = maxX_0012A2E0(arg0, side, bestX);
                        currentY = (u8)candidate->y;
                        currentMinY = minY_0012A2E0(arg0, side, currentY);
                        currentMaxY = maxY_0012A2E0(arg0, side, currentY);
                        currentX = candidate->x;
                        currentMinX = minX_0012A2E0(arg0, side, currentX);
                        currentMaxX = maxX_0012A2E0(arg0, side, currentX);
                        if ((currentMaxX - currentMinX) + (currentMaxY - currentMinY) < (bestMaxX - bestMinX) + (bestMaxY - bestMinY)) {
                            bestScore = score;
                            best = index;
                        }
                    }
                }
            candidate++;
        }
    } else {
        ((Output_0012A2E0 *)arg2)->position = ((Unit_0012A2E0 *)arg0)->position;
            ((Output_0012A2E0 *)arg2)->kind = 6;
            ((Output_0012A2E0 *)arg2)->target = initial;
            ((Output_0012A2E0 *)arg2)->flag = TaLogic_IsDefStyleUnit(((Unit_0012A2E0 *)arg0)->position >> 8, ((Unit_0012A2E0 *)arg0)->position & 0xFF, ((Output_0012A2E0 *)arg2)->target, arg4, 0);
            ((Output_0012A2E0 *)arg2)->value = TaLogic_IsOpenUnit_0012B210(((Unit_0012A2E0 *)arg0)->position >> 8, ((Unit_0012A2E0 *)arg0)->position & 0xFF, arg0);
        TaLogic006_InitRogicControl(arg0, arg3);
        return 0;
    }

        if (best != 0xFF) {
            ((Output_0012A2E0 *)arg2)->position = ((Unit_0012A2E0 *)arg0)->position;
            ((Output_0012A2E0 *)arg2)->kind = 6;
            ((Output_0012A2E0 *)arg2)->target = (coords[best].y << 8) | coords[best].x;
            ((Output_0012A2E0 *)arg2)->flag = TaLogic_IsDefStyleUnit(((Unit_0012A2E0 *)arg0)->position >> 8, ((Unit_0012A2E0 *)arg0)->position & 0xFF, ((Output_0012A2E0 *)arg2)->target, arg4, 0);
            ((Output_0012A2E0 *)arg2)->value = TaLogic_IsOpenUnit_0012B210(((Unit_0012A2E0 *)arg0)->position >> 8, ((Unit_0012A2E0 *)arg0)->position & 0xFF, arg0);
        } else {
            ((Output_0012A2E0 *)arg2)->position = ((Unit_0012A2E0 *)arg0)->position;
            ((Output_0012A2E0 *)arg2)->kind = 6;
            ((Output_0012A2E0 *)arg2)->target = initial;
            ((Output_0012A2E0 *)arg2)->flag = TaLogic_IsDefStyleUnit(((Unit_0012A2E0 *)arg0)->position >> 8, ((Unit_0012A2E0 *)arg0)->position & 0xFF, ((Output_0012A2E0 *)arg2)->target, arg4, 0);
            ((Output_0012A2E0 *)arg2)->value = TaLogic_IsOpenUnit_0012B210(((Unit_0012A2E0 *)arg0)->position >> 8, ((Unit_0012A2E0 *)arg0)->position & 0xFF, arg0);
        }
        TaLogic006_InitRogicControl(arg0, arg3);
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


static inline u32 target_0012AAC0(void *arg0, s32 mode) {
    Source_0012AAC0 *source = arg0;
    if (mode == 1) {
        return (u16)(source->target.both >> 16);
    }
    return source->target.half[0];
}

static inline void fill_0012AAC0(void *arg0, void *arg2, s32 target, s32 flag) {
    Source_0012AAC0 *source = arg0;
    Action_0012AAC0 *action = arg2;
    action->position = source->position;
    action->action = 6;
    action->target = target;
    action->result = TaLogic_IsDefStyleUnit(source->position >> 8,
        source->position & 0xFF, action->target, flag, 0);
}

s32 TaLogic_GetMinimumTask_TrapMission_0012AAC0(void *arg0, s32 arg1, void *arg2, s32 arg3) {
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
    Source_0012AAC0 *source = arg0;
    Action_0012AAC0 *action = arg2;
    extern void TaLogic_GetInvadeRoot();

    mode = arg3 & 0xFF;
    xPosition = target_0012AAC0(arg0, mode);
    yPosition = target_0012AAC0(arg0, mode);
    if (SzDuel_GetUnit(yPosition >> 8, xPosition & 0xFF) == 0) {
        TaLogic_InitRogicControl(arg0, 1);
        return -1;
    }
    start = SzDuel_GetUnitLoc(source->position >> 8, source->position & 0xFF);
    xPosition = target_0012AAC0(arg0, mode);
    yPosition = target_0012AAC0(arg0, mode);
    target = SzDuel_GetUnitLoc(yPosition >> 8, xPosition & 0xFF);
    if (target_0012AAC0(arg0, mode) == 0xFFFF) {
        fill_0012AAC0(arg0, arg2, start, 1);
        return 0;
    } else {
        s32 unit = SzDuel_GetUnit(source->position >> 8, source->position & 0xFF);
        startX = start & 0xFF;
        startY = start >> 8;
        if (GetMoveRev(unit, startX, startY) == 0 ||
                TaLogic_IsAttackedNow(source->position >> 8, source->position & 0xFF, 0) == 1) {
            fill_0012AAC0(arg0, arg2, start, 1);
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
                u16 card = (u16)TaLogic_GetWarnHideLvl_0012B1B0(arg1);
                TaLogic_GetInvadeRoot(position >> 8, position & 0xFF, points,
                    startX, startY, targetX = target & 0xFF,
                    targetY = target >> 8, target_0012AAC0(arg0, mode),
                    0, 30, card);
            }
            count = TaLogic_GetMinGoalCount((u8 *)points);
            bestIndex = 0xFF;
            if (count > 0) {
                bestScore = 0;
                for (i = 0; i < count; i++, p++) {
                    if (SzDuel_GetMapUnit(p->x, p->y) == 0) {
                        s32 score = TaLogic_GetUnitWarning(p->x, p->y, arg1, 5, 1,
                            TaLogic_GetWarnHideLvl_0012B1B0(arg1) & 0xFF);
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
                fill_0012AAC0(arg0, arg2, start, 1);
                return 0;
            }
            if (bestIndex != 0xFF) {
                action->position = source->position;
                action->action = 6;
                action->target = (points[bestIndex].y << 8) | points[bestIndex].x;
                action->result = TaLogic_IsDefStyleUnit(source->position >> 8,
                    source->position & 0xFF, action->target, 0, 0);
            } else {
                fill_0012AAC0(arg0, arg2, start, 1);
                return 0;
            }
        }
    }
    return 0;
}

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

s32 TaLogic_GetWarnHideLvl_0012B1B0(s32 arg0) {
    if (SzDuel_GetLP(arg0) > 0x4B0) {
        if (SzDuel_GetUnitMonsterCount(arg0) >= 4) {
            return 0x3E8;
        }
        return 0x7D0;
    }
    return 0x960;
}

s32 TaLogic_IsOpenUnit_0012B210(s32 arg0, s32 arg1, void *arg2) {
    extern s32 SzDuel_GetUnitCardNo();
    extern s32 func_0012B000();
    s32 card;
    s32 position;
    s32 owner;
    s32 value;
    u8 count;

    card = SzDuel_GetUnitCardNo(arg0, arg1);
    owner = Ta_IsUnitControl(arg0, arg1);
    position = SzDuel_GetUnitLoc(arg0, arg1);
    count = 0;
    if (SzDuel_GetUnitStatus(arg0, arg1, 4) != 0) {
        return 0;
    }
    switch (SzDuel_GetUnitKind(arg0, arg1) >> 5) {
    case 0:
        switch (card) {
        case 0x65:
            for (card = 1; card <= 5; card++) {
                if (SzDuel_GetUnitCardNo(arg0, card) == 0x65 && arg0 == Ta_IsUnitControl(arg0, card)) {
                    count++;
                }
                if (SzDuel_GetUnitCardNo((arg0 == 0) ? 1 : 0, card) == 0x65 &&
                    arg0 == Ta_IsUnitControl((arg0 == 0) ? 1 : 0, card)) {
                    count++;
                }
            }
            if (count >= 2) {
                return 1;
            }
            break;
        case 0x66:
            for (card = 1; card <= 5; card++) {
                if (SzDuel_GetUnitCardNo(arg0, card) == 0x66 && arg0 == Ta_IsUnitControl(arg0, card)) {
                    count++;
                }
                if (SzDuel_GetUnitCardNo((arg0 == 0) ? 1 : 0, card) == 0x66 &&
                    arg0 == Ta_IsUnitControl((arg0 == 0) ? 1 : 0, card)) {
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
                if (SzDuel_GetUnitCardNo(arg0, card) == 0x77 && arg0 == Ta_IsUnitControl(arg0, card)) {
                    count++;
                }
                if (SzDuel_GetUnitCardNo((arg0 == 0) ? 1 : 0, card) == 0x77 &&
                    arg0 == Ta_IsUnitControl((arg0 == 0) ? 1 : 0, card)) {
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
        if (TaLogic006_IsDoCerem(Ta_IsUnitControl(arg0, arg1), card) == 1 &&
            SzDuel_GetField(position & 0xFF, position >> 8) != 9) {
            return 1;
        }
        break;
    case 1:
        if (TaLogic_GetActionReaction(arg0, arg1, 0, 0, 6, 0) == 5) {
            return 2;
        }
        switch (SzDuel_GetUnitCardNo(arg0, arg1)) {
        case 0x2BB:
            if (TaLogic_IsAttackedNow(arg0, 0, 0) == 1 || func_0012B000(arg0) == 1) {
                return 1;
            }
            break;
        case 0x2AD:
            value = TaLogic_GetMaxAPGraveCard(arg0, 3);
            if (value >= 0 && (u16)value >= 0x960 && SzDuel_GetUnitMonsterCount(arg0) < 5 &&
                SzDuel_GetField(position & 0xFF, position >> 8) != 9) {
                return 1;
            }
            break;
        case 0x2E9:
            for (card = 1; card <= 5; card++) {
                if (SzDuel_GetUnit(arg0, card) != 0 && (SzDuel_GetUnitKind(arg0, card) & 0x1F) != 2 &&
                    arg0 == Ta_IsUnitControl(arg0, card)) {
                    count++;
                }
                if (SzDuel_GetUnit((arg0 == 0) ? 1 : 0, card) != 0 &&
                    (SzDuel_GetUnitKind((arg0 == 0) ? 1 : 0, card) & 0x1F) != 2 &&
                    arg0 == Ta_IsUnitControl((arg0 == 0) ? 1 : 0, card)) {
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

static inline s32 max_0012B730(s32 a, s32 b) {
    s32 maximum;

    if (a < b) {
        maximum = b;
    } else {
        maximum = a;
    }
    return maximum;
}

s32 TaLogic006_IsOpenMoveUnit(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 min_y;
    s32 min_x;
    s32 result;
    s32 status;

    min_y = arg3 < arg5 ? arg3 : arg5;
    arg5 = max_0012B730(arg5, arg3);
    min_x = arg2 < arg4 ? arg2 : arg4;
    arg4 = max_0012B730(arg4, arg2);
    if ((arg4 - min_x) + (arg5 - min_y) != 2) {
        return 0;
    }
    if (SzDuel_GetUnit(arg0, arg1) == 0) {
        return 0;
    }
    if (SzDuel_GetUnitStatus(arg0, arg1, 0) == 0) {
        status = CheckLandAgreement2(SzDuel_GetField(arg2, arg3), arg0, arg1);
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

void TaLogic006_InitRogicControl(void *arg0, u8 arg1) {
    Data_0012B830 *data = arg0;

    if (arg1 < 2) {
        if (arg1 == 1) {
            data->value4 = (data->value4 & 0xFF) | 0xFF00;
        } else {
            data->value4 = (data->value4 & 0xFF00) | 0xFF;
        }
        if (arg1 == 1) {
            data->value8 = (data->value8 & 0xFFFF) | 0xFFFF0000;
        } else {
            data->value8 = (data->value8 & 0xFFFF0000) | 0xFFFF;
        }
    }
}

s32 TaLogic006_IsDoCerem(s32 arg0, s32 arg1) {
    s32 sp50[3];
    s32 var_s0;
    s32 temp_v0;
    s32 temp_s2;
    s32 temp_s3;
    s32 temp_v0_2;
    s32 temp_v0_3;

    Ta_GetCeremSacrifice(sp50, *(s32 *)((u8 *)TaHand_GetCardEffect(arg1, 0) + 4));
    if ((temp_v0 = Ta_GetSacrificeUnit(sp50, arg0)) < 0) {
        return 0;
    }
    var_s0 = 0;
    if (var_s0 < Ta_GetUnitNumFrom22bitFlagList(temp_v0)) {
        do {
            temp_v0_2 = Ta_GetUnitOwnerIDFromLstCount(temp_v0, var_s0);
            temp_s3 = temp_v0_2 >> 8;
            temp_s2 = temp_v0_2 & 0xFF;
            temp_v0_3 = SzDuel_GetUnitLoc(temp_s3, temp_s2);
            if (TaUtil_GetUnitAP(temp_s3, temp_s2, temp_v0_3 & 0xFF, temp_v0_3 >> 8) >= 0x7D0) {
                return 0;
            }
            var_s0++;
        } while (var_s0 < Ta_GetUnitNumFrom22bitFlagList(temp_v0));
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

s32 func_0012B9A0(s32 arg0, void *arg1) {
    Req_0012B9A0 req;
    Work_0012B9A0 *w;
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
        if (TaLogic_GetMinimumTask_00126C80(w, &req, arg0) == 0) {
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

typedef struct {
    u8 pad0[0x1A1];
    u8 lvl : 4;      /* 0x1A1 */
    u8 pad1A1 : 4;
} Ai_0012BB70;

#pragma conditional_move off

s32 TaLogic_GetMinimumTask_0012BB70(void *work, void *arg1, s32 arg2) {
    extern s32 TaLogic_GetMinimumTask_ReviveMission_0012ED70(void *, s32, void *, u8, u8);
    extern s32 TaLogic_GetMinimumTask_TrapMission_00130120(void *, s32, void *, u8, u8);
    u16 *arg0 = work;
    Ai_0012BB70 *ai = work;
    s32 side;
    s32 found;
    s32 result;
    s32 index;

    side = SzDuel_GetTurnOwner();
    found = 0;
    ai->lvl = TaLogic007_IsActiveMode();
    if ((result = TaLogic_GetNextActiveUnit_0012C3F0(arg0, side, (s32)arg1)) < 0) {
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
    TaLogic_CommandUnit_0012C1A0(arg0 + index * 8, ai->lvl);
    switch ((arg0[index * 8 + 2] >> 8) & 0xFF) {
    case 5:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_RunMission_0012E820(arg0 + index * 8, side, arg1, 1, ai->lvl);
            found = 1;
        }
        break;
    case 2:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            if (TaLogic_GetMinimumTask_AtkMission_0012F350(arg0 + index * 8, side, arg1, 1, ai->lvl) < 0) {
                TaLogic_InitRogicControl(arg0 + index * 8, 1);
                return 1;
            }
            found = 1;
        }
        break;
    case 10:
        if (TaLogic_GetMinimumTask_Summon_0012D270(arg0[index * 8], side, (s32)arg1, ai->lvl) < 0) {
            TaLogic_InitRogicControl(arg0 + index * 8, 1);
            *(u8 *)((u8 *)arg1 + 2) = 0xFF;
            *(s32 *)((u8 *)arg1 + 0xC) = 0;
        } else {
            TaLogic_InitRogicControl(arg0 + index * 8, 1);
            found = 1;
        }
        break;
    case 6:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_MoveMission_0012F930(arg0 + index * 8, side, arg1, 1, 0, ai->lvl);
            found = 1;
        }
        break;
    case 3:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_MoveMission_0012F930(arg0 + index * 8, side, arg1, 1, 1, ai->lvl);
            found = 1;
        }
        break;
    case 9:
        TaLogic_GetMinimumTask_EncMission(arg0 + index * 8, side, arg1, 1, 0, TaLogic_GetWarnHideLvl_00130780(side), 5, 1);
        found = 1;
        break;
    case 11:
        TaLogic_GetMinimumTask_TrapMission_00130120(arg0 + index * 8, side, arg1, 1, ai->lvl);
        found = 1;
        break;
    case 12:
        TaLogic_GetMinimumTask_ReviveMission_0012ED70(arg0 + index * 8, side, arg1, 1, ai->lvl);
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
            TaLogic_GetMinimumTask_RunMission_0012E820(arg0 + index * 8, side, arg1, 0, ai->lvl);
            found = 1;
        }
        break;
    case 2:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            if (TaLogic_GetMinimumTask_AtkMission_0012F350(arg0 + index * 8, side, arg1, 0, ai->lvl) < 0) {
                TaLogic_GetMinimumTask_RunMission_0012E820(arg0 + index * 8, side, arg1, 0, ai->lvl);
            }
            found = 1;
        }
        break;
    case 10:
        if (TaLogic_GetMinimumTask_Summon_0012D270(arg0[index * 8], side, (s32)arg1, ai->lvl) < 0) {
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
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_MoveMission_0012F930(arg0 + index * 8, side, arg1, 0, 0, ai->lvl);
            found = 1;
        }
        break;
    case 3:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_MoveMission_0012F930(arg0 + index * 8, side, arg1, 0, 1, ai->lvl);
            found = 1;
        }
        break;
    case 11:
        TaLogic_GetMinimumTask_TrapMission_00130120(arg0 + index * 8, side, arg1, 0, ai->lvl);
        found = 1;
        break;
    case 9:
        TaLogic_GetMinimumTask_EncMission(arg0 + index * 8, side, arg1, 0, 0, TaLogic_GetWarnHideLvl_00130780(side), 5, 1);
        found = 1;
        break;
    case 12:
        TaLogic_GetMinimumTask_ReviveMission_0012ED70(arg0 + index * 8, side, arg1, 0, ai->lvl);
        found = 1;
        break;
    case 14:
        TaLogic_GetMinimumTask_DoNone(arg0 + index * 8, side, arg1);
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


s32 TaLogic_CommandUnit_0012C1A0(void *arg0, s32 arg1) {
    Object_0012C1A0 *obj = arg0;
    s32 temp_s0;
    s32 kind;
    u16 id;

    id = obj->id;
    temp_s0 = Ta_IsUnitControl((s32)(id >> 8), id & 0xFF);
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
                            obj->flags = (u16)obj->flags | (SzDuel_GetUnitLoc((temp_s0 == 0) ? 1 : 0, 0) << 16);
                        } else {
                            obj->status = 0x6FF;
                            obj->flags = (u16)obj->flags | (SzDuel_GetUnitLoc((temp_s0 == 0) ? 1 : 0, 0) << 16);
                        }
                    }
                    }
                } else {
                    kind = SzDuel_GetUnitKind((s32)(id >> 8), id & 0xFF) >> 5;
                    switch (kind) {
                    case 0:
                        id = obj->id;
                        if (TaUtil_IsExMonster((s32)(id >> 8), id & 0xFF) == 1) {
                            TaLogic007_CommandEfcMonster(obj, arg1);
                        } else {
                            TaLogic007_CommandBtlUnit(obj, 1, arg1);
                        }
                        break;
                    case 2:
                        TaLogic_CommandEncUnit(obj, 5, 0, TaLogic_GetWarnHideLvl_00130780(temp_s0) & 0xFF);
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

s32 TaLogic_GetNextActiveUnit_0012C3F0(u16 *arg0, s32 arg1, s32 arg2) {
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
    TaLogic_CommandUnit_0012C1A0(arg0 + idx * 8, ((u8 *)arg0)[0x1A1] & 0xF);
    if (((arg0[idx * 8 + 2] >> 8) & 0xFF) == 10) {
        if (SzDuel_InqHandPhase(arg1) == 1 && TaLogic_GetMinimumTask_Summon_0012D270(pos, arg1, arg2, TaLogic007_IsActiveMode()) >= 0) {
            return pos | 0x10000;
        }
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_GetUnitStatus(arg1, 0, 0) == 0) {
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_InqHandPhase(arg1) == 1 && TaLogic_GetMinimumTask_Summon_0012D270(pos, arg1, arg2, TaLogic007_IsActiveMode()) >= 0) {
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

void TaLogic007_CommandBtlUnit(void *arg0, s32 arg1, s32 arg2) {
    extern void TaLogic_InitIgnoreLst();
    extern s32 TaLogic_IsRootOpen();
    extern s32 TaLogic007_GetNearUnit();
    Command_0012C7F0 *command = arg0;

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

        if (arg1 != 0) {
            u8 mode;
            if ((arg2 & 0xFF) == 1) {
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
        if ((arg2 & 0xFF) == 0) {
            arg2 = 1;
            while (1) {
                s32 result;
                other = Ta_GetCurrentSide(command->position >> 8, command->position & 0xFF) == 0 ? 1 : 0;
                result = TaLogic007_GetNearUnit(command, 0, data, position & 0xFF, position >> 8,
                    other, (u8)arg2, TaLogic_GetWarnHideLvl_00130780(side), entries, 0,
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
                arg2++;
                if (arg2 > 2) {
                    break;
                }
            }
            command->action = 0x5FF;
        } else {
            arg2 = 1;
            do {
                s32 result;
                other = Ta_GetCurrentSide(command->position >> 8, command->position & 0xFF) == 0 ? 1 : 0;
                result = TaLogic007_GetNearUnit(command, 0, data, position & 0xFF, position >> 8,
                    other, (u8)arg2, TaLogic_GetWarnHideLvl_00130780(side), entries, 0,
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
                arg2++;
            } while (arg2 < 5);
            command->action = 0x5FF;
        }
    }
}

void TaLogic007_GetNearUnit(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28) {
    TaLogic_GetNearUnit(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
                  arg_sp0, arg_sp8, arg_sp10, arg_sp18, arg_sp20,
                  0, 2500, arg_sp28);
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

static inline void update_state_0012CBE0(void *arg0, u16 flags, s32 position) {
    State_0012CBE0 *state = arg0;
    u32 value;

    state->flags = flags;
    value = state->position & 0xFFFF;
    state->position = (position << 16) | value;
}


void TaLogic007_CommandEfcMonster(void *arg0, s32 arg1) {
    extern s32 SzDuel_GetUnitCardNo();
    extern void TaLogic_InitIgnoreLst();
    extern s32 TaLogic_GetNearUnit();
    u8 buffer[0x70];
    Entry_0012CBE0 entries[23];
    s16 count;
    s16 limit;
    State_0012CBE0 *state = arg0;
    s32 owner;
    s32 position;
    s32 card;
    s32 row;
    s32 column;
    s32 attempt;
    s32 i;
    Entry_0012CBE0 *entry;
    s32 type;
    s32 result;

    if ((card = SzDuel_GetUnit(state->id >> 8, state->id & 0xFF)) != 0) {
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
                result = TaLogic_GetNearUnit(state, 0, card, column, row, owner == 0 ? 1 : 0,
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
        TaLogic007_CommandBtlUnit(state, 1, arg1);
    }
}

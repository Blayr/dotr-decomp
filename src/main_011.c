#include "common.h"

typedef struct {
    u16 id;
    u8 values[5];
} Info_00144630;

void TaLogic_ConvEmptyCombo_00144630(s32 arg0, void *arg1, s32 *arg2) {
    Info_00144630 *info = arg1;
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
                if (card != 0x3E7 && TaLogic012_IsRefuseEmptyCombo(card) == 0 && level >= TaHand_GetCardSummonCost2(card, arg0)) {
                    cost = TaHand_GetCardAPDP(card);
                    if ((cost & 0xFFFF) + (cost >> 16) * 2 < 0xAF1 && TaHand_IsCardEffect(card) == 2 &&
                        (u16)TaLogic_GetHandFusion(info->id, (u16)card) == 0x3E7) {
                        TaLogic_AddEmptyCombo(info->values, buf[i]);
                    }
                }
            }
        }
    }
}

s32 TaLogic012_IsRefuseEmptyCombo(s32 arg0) {
    if ((TaHand_GetCardKind(arg0) >> 5) != 0) {
        return 1;
    }
    return (TaHand_IsCardEffect(arg0) != 0) ? 1 : 0;
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

s32 TaLogic012_SetSpecialComboQue(s32 arg0, void *arg1, void *arg2) {
    Obj1_00144860 *o1 = arg1;
    Obj2_00144860 *o2 = arg2;
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
    return o2->f3E >> 5;
}

typedef struct Nibbles_00144A60 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_00144A60;


static inline s32 findrow_00144A60(void *arg2) {
    s32 row = 1;

    while (1) {
        if (CheckLandAgreement(SzDuel_GetField(0, row), arg2) == 1) {
            return row;
        }
        row++;
        if (row > 5) {
            break;
        }
    }
    return -1;
}

s32 TaLogic012_GetSummonPiece(s32 arg0, s32 arg1, void *arg2, s32 arg3) {
    extern s32 TaLogic_IsUnitWin4();
    extern s32 TaLogic_GetInvadeRoot2();
    extern s32 TaLogic_GetRoot2(s32, s32, s32, s32, s32, s32, u16, u8);
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
            target = SzDuel_GetUnitLoc(arg3 >> 8, arg3 & 255);
            i = 0;
            targetY = target >> 8;
            targetX = target & 255;
            do {
                position = Ta_GetSommonPiecePreference(arg0, i);
                if (position >= 0) {
                    x = position & 255;
                    y = position >> 8;
                    if (SzDuel_GetField(x, y) != 8 &&
                        (SzDuel_GetField(x, y) != 9 || Ta_IsVirus_Chk3(arg2, x, y) != 1) &&
                        SzDuel_GetMapUnit(x, y) == 0) {
                        if (TaLogic_IsUnitWin4((s32)arg2, arg3, TaLogic_GetWarnHideLvl_001461C0(arg0), targetX, targetY, 0) > 0) {
                            score = TaLogic_GetInvadeRoot2((s32)arg2, (s32)path, x, y, targetX, targetY,
                                                 arg3, 0, 3, (u16)TaLogic_GetWarnHideLvl_001461C0(arg0));
                        } else {
                            score = TaLogic_GetRoot2((s32)arg2, (s32)path, x, y, targetX, targetY, arg3, 3);
                        }
                        if (TaLogic_GetMinGoalCount((u8 *)path) > 0 && score < bestScore) {
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
                position = Ta_GetSommonPiecePreference(arg0, i);
                if (position >= 0) {
                    x = position & 255;
                    y = position >> 8;
                    if (SzDuel_GetField(x, y) != 8 &&
                        (SzDuel_GetField(x, y) != 9 || Ta_IsVirus_Chk3(arg2, x, y) != 1) &&
                        SzDuel_GetMapUnitID(x, y) < 0) {
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
            position = Ta_GetSommonPiecePreference(arg0, i);
            if (position >= 0) {
                x = position & 255;
                y = position >> 8;
                if (SzDuel_GetField(x, y) != 8 &&
                    (SzDuel_GetField(x, y) != 9 || Ta_IsVirus_Chk3(arg2, x, y) != 1) &&
                    SzDuel_GetMapUnitID(x, y) < 0 && y < 8) {
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


s32 TaLogic_GetMinimumTask_RunMission_00144EC0(u16 *arg0, s32 arg1, void *arg2, u8 arg3) {
    extern s32 TaLogic_IsRunPassRoot(s32, s32, s32, s32, s32, s32, void *, u8);
    extern s32 TaLogic_IsOpenUnit_00146220();
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

    position = SzDuel_GetUnitLoc(*arg0 >> 8, *arg0 & 0xFF);
    i = 0;
    do {
        cells[i].low = cells[i].high = 15;
        i++;
    } while (i < 12);

    {
        u16 value = (u16)TaLogic_GetWarnHideLvl_001461C0(arg1);
        originalX = position & 0xFF;
        originalY = position >> 8;
        if (TaLogic_GetUnitWarning(originalX, originalY, *arg0, 3, value, 0) == 0) {
            out->id = *arg0;
            out->action = 6;
            out->position = position;
            out->mode = TaLogic_IsDefStyleUnit(*arg0 >> 8, *arg0 & 0xFF, out->position, 1, 0);
            out->value = TaLogic_IsOpenUnit_00146220(*arg0 >> 8, *arg0 & 0xFF, arg0);
            TaLogic_InitRogicControl(arg0, arg3);
            return 0;
        } else {
            result = GetMoveRev(SzDuel_GetUnit(*arg0 >> 8, *arg0 & 0xFF), originalX, originalY);
            if (result == 0) {
                out->id = *arg0;
                out->action = 6;
                out->position = position;
                out->mode = TaLogic_IsDefStyleUnit(*arg0 >> 8, *arg0 & 0xFF, out->position, 1, 0);
                out->value = TaLogic_IsOpenUnit_00146220(*arg0 >> 8, *arg0 & 0xFF, arg0);
                TaLogic_InitRogicControl(arg0, arg3);
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
                                value = (u16)TaLogic_GetWarnHideLvl_001461C0(arg1);
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
                    out->value = TaLogic_IsOpenUnit_00146220(*arg0 >> 8, *arg0 & 0xFF, arg0);
                } else {
                    out->id = *arg0;
                    out->action = 6;
                    out->position = position;
                    out->mode = TaLogic_IsDefStyleUnit(*arg0 >> 8, *arg0 & 0xFF, out->position, 1, 0);
                    out->value = TaLogic_IsOpenUnit_00146220(*arg0 >> 8, *arg0 & 0xFF, arg0);
                }
                TaLogic_InitRogicControl(arg0, arg3);
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

s32 TaLogic_GetMinimumTask_AtkMission_00145400(void *arg0, s32 arg1, void *arg2, u8 arg3) {
    extern s32 TaLogic_IsOpenUnit_00146220();
    extern s32 GetMoveRev();
    extern s32 TaLogic_GetUnitWarning();
    extern void TaLogic_GetInvadeRoot();
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
    if (SzDuel_GetUnit(targetHigh >> 8, targetLow & 0xFF) == 0) {
        TaLogic_InitRogicControl(arg0, 1);
        return -1;
    }
    fallback = TaLogic_IsOpenUnit_00146220((s32)input->position >> 8, input->position & 0xFF, arg0);
    origin = SzDuel_GetUnitLoc((s32)input->position >> 8, input->position & 0xFF);
    targetLow = target_00145400(arg0, arg3);
    targetHigh = target_00145400(arg0, arg3);
    targetPosition = SzDuel_GetUnitLoc(targetHigh >> 8, targetLow & 0xFF);
    i = 0;
    do {
        candidates[i].x = candidates[i].y = 15;
        i++;
    } while (i < 12);
    card = SzDuel_GetUnit((s32)input->position >> 8, input->position & 0xFF);
    originX = origin & 0xFF;
    originY = origin >> 8;
    if (GetMoveRev(card, originX, originY) == 0) {
        s32 cost;
        output->position = input->position;
        output->action = 6;
        output->destination = origin;
        cost = TaLogic_GetUnitWarning(originX, originY, arg1, 3, 1, (u8)TaLogic_GetWarnHideLvl_001461C0(arg1));
        if (cost >= SzDuel_GetUnitAP((s32)input->position >> 8, input->position & 0xFF, 0)) {
            output->result = TaLogic_IsDefStyleUnit((s32)input->position >> 8,
                                         input->position & 0xFF, output->destination, 1, 0);
        } else {
            output->result = TaLogic_IsDefStyleUnit((s32)input->position >> 8,
                                         input->position & 0xFF, output->destination, 0, 0);
        }
        TaLogic_InitRogicControl(arg0, arg3);
    } else {
        s32 position = input->position;
        u16 kind = TaLogic_GetWarnHideLvl_001461C0(arg1);
        s32 positionY = position >> 8;
        s32 positionX = position & 0xFF;

        TaLogic_GetInvadeRoot(positionY, positionX, candidates,
                     originX, originY, targetX = targetPosition & 0xFF, targetPosition >>= 8,
                     target_00145400(arg0, arg3), (s64)0, (s64)30, (s64)kind);
        count = TaLogic_GetMinGoalCount((u8 *)candidates);
        bestIndex = 255;
        if (count > 0) {
            special = 0;
            bestCost = 65535;
            for (index = 0; index < count; index++) {
                if (TaLogic012_IsOpenMoveUnit((s32)input->position >> 8, input->position & 0xFF,
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
                    cost = TaLogic_GetUnitWarning(candidate->x, candidate->y, arg1,
                                         3, 1, (u8)TaLogic_GetWarnHideLvl_001461C0(arg1));
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
            output->result = TaLogic_IsDefStyleUnit((s32)input->position >> 8,
                                         input->position & 0xFF, output->destination, 0, 0);
            TaLogic_InitRogicControl(arg0, arg3);
            return 0;
        }
        if (bestIndex != 255) {
            output->position = input->position;
            output->action = 6;
            output->destination = (candidates[bestIndex].y << 8) | candidates[bestIndex].x;
            output->special = special;
            output->result = TaLogic_IsDefStyleUnit((s32)input->position >> 8,
                                         input->position & 0xFF, output->destination, 0, 0);
        } else {
            output->position = input->position;
            output->action = 6;
            output->destination = origin;
            output->special = special;
            output->result = TaLogic_IsDefStyleUnit((s32)input->position >> 8,
                                         input->position & 0xFF, output->destination, 0, 0);
            TaLogic_InitRogicControl(arg0, arg3);
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

s32 TaLogic_GetMinimumTask_MoveMission_001459E0(void *arg0, s32 arg1, void *arg2, u8 arg3, u8 arg4) {
    s32 target;
    s32 leader;
    s32 count;
    Coord_001459E0 coords[12];
    extern s32 TaLogic_IsOpenUnit_00146220();
    extern s32 TaLogic_GetUnitWarning();
    extern void TaLogic_GetRoot();
    extern s32 TaLogic_IsDefStyleUnit(s32, s32, s32, u8, s32);

    {
        s32 bestCost;
        s32 bestIndex;
        s32 mode;
        Coord_001459E0 *p;
        s32 i;
        target = SzDuel_GetUnitLoc(((Unit_001459E0 *)arg0)->pos >> 8, ((Unit_001459E0 *)arg0)->pos & 0xFF);
        mode = arg3;
        if (selected_001459E0(arg0, mode) == 0xFFFF &&
            target == selected_001459E0(arg0, mode)) {
            ((Result_001459E0 *)arg2)->pos = ((Unit_001459E0 *)arg0)->pos;
            ((Result_001459E0 *)arg2)->kind = 6;
            ((Result_001459E0 *)arg2)->target = target;
            ((Result_001459E0 *)arg2)->value = TaLogic_IsDefStyleUnit(
                ((Unit_001459E0 *)arg0)->pos >> 8, ((Unit_001459E0 *)arg0)->pos & 0xFF,
                ((Result_001459E0 *)arg2)->target, arg4, 0);
            ((Result_001459E0 *)arg2)->action = TaLogic_IsOpenUnit_00146220(
                ((Unit_001459E0 *)arg0)->pos >> 8, ((Unit_001459E0 *)arg0)->pos & 0xFF, arg0);
            TaLogic_InitRogicControl(arg0, arg3);
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

        leader = SzDuel_GetMapUnitID(selected_001459E0(arg0, mode) & 0xFF,
                             selected_001459E0(arg0, mode) >> 8);
        if (leader < 0) {
            leader = 0xFFFF;
        }
        TaLogic_GetRoot(((Unit_001459E0 *)arg0)->pos >> 8, ((Unit_001459E0 *)arg0)->pos & 0xFF,
                     coords, target & 0xFF, target >> 8,
                     selected_001459E0(arg0, mode) & 0xFF,
                     selected_001459E0(arg0, mode) >> 8, (u16)leader, 7);
        count = TaLogic_GetMinGoalCount((u8 *)coords);
        if (count > 0) {
            s32 cost;
            bestIndex = 0xFF;
            bestCost = 0xFFFF;
            for (i = 0; i < count; ++i, ++p) {
                if (SzDuel_GetMapUnit(p->x, p->y) == 0) {
                    cost = TaLogic_GetUnitWarning(p->x, p->y, arg1, 3, 1,
                                        (u8)TaLogic_GetWarnHideLvl_001461C0(arg1));
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
            ((Result_001459E0 *)arg2)->value = TaLogic_IsDefStyleUnit(
                ((Unit_001459E0 *)arg0)->pos >> 8, ((Unit_001459E0 *)arg0)->pos & 0xFF,
                ((Result_001459E0 *)arg2)->target, arg4, 0);
            ((Result_001459E0 *)arg2)->action = TaLogic_IsOpenUnit_00146220(
                ((Unit_001459E0 *)arg0)->pos >> 8, ((Unit_001459E0 *)arg0)->pos & 0xFF, arg0);
            TaLogic_InitRogicControl(arg0, arg3);
            return 0;
        }
            if (bestIndex != 0xFF) {
                ((Result_001459E0 *)arg2)->pos = ((Unit_001459E0 *)arg0)->pos;
                ((Result_001459E0 *)arg2)->kind = 6;
                ((Result_001459E0 *)arg2)->target =
                    (coords[bestIndex].y << 8) | coords[bestIndex].x;
                ((Result_001459E0 *)arg2)->value = TaLogic_IsDefStyleUnit(
                    ((Unit_001459E0 *)arg0)->pos >> 8, ((Unit_001459E0 *)arg0)->pos & 0xFF,
                    ((Result_001459E0 *)arg2)->target, arg4, 0);
                ((Result_001459E0 *)arg2)->action = TaLogic_IsOpenUnit_00146220(
                    ((Unit_001459E0 *)arg0)->pos >> 8, ((Unit_001459E0 *)arg0)->pos & 0xFF, arg0);
            } else {
                ((Result_001459E0 *)arg2)->pos = ((Unit_001459E0 *)arg0)->pos;
                ((Result_001459E0 *)arg2)->kind = 6;
                ((Result_001459E0 *)arg2)->target = target;
                ((Result_001459E0 *)arg2)->value = TaLogic_IsDefStyleUnit(
                    ((Unit_001459E0 *)arg0)->pos >> 8, ((Unit_001459E0 *)arg0)->pos & 0xFF,
                    ((Result_001459E0 *)arg2)->target, arg4, 0);
                ((Result_001459E0 *)arg2)->action = TaLogic_IsOpenUnit_00146220(
                    ((Unit_001459E0 *)arg0)->pos >> 8, ((Unit_001459E0 *)arg0)->pos & 0xFF, arg0);
            }
            TaLogic_InitRogicControl(arg0, arg3);
        return 0;
    }
}

s32 TaLogic_GetWarnHideLvl_001461C0(s32 arg0) {
    if (SzDuel_GetLP(arg0) > 2000) {
        if (SzDuel_GetUnitMonsterCount(arg0) >= 4) {
            return 0;
        }
        return 0;
    }
    return 0;
}

s32 TaLogic_IsOpenUnit_00146220(s32 arg0, s32 arg1) {
    s32 pos;
    s32 kind;
    s32 slot;
    u8 count;
    s32 i;
    s32 list;
    s32 pair;
    extern s32 SzDuel_GetUnitCardNo();

    pos = SzDuel_GetUnitLoc(arg0, arg1);
    kind = SzDuel_GetUnitCardNo(arg0, arg1);
    slot = Ta_IsUnitControl(arg0, arg1);
    count = 0;
    if (SzDuel_GetUnitStatus(arg0, arg1, 4) != 0) {
        return 0;
    }
    switch (kind) {
    case 0x145:
        list = SearchUnitByRange(0, 0, arg0, 2, 0x34, 0xE);
        for (i = 0; i < Ta_GetUnitNumFrom22bitFlagList(list); i++) {
            pair = Ta_GetUnitOwnerIDFromLstCount(list, i);
            if (SzDuel_GetUnitStatus(pair >> 8, pair & 0xFF, 3) != 0) {
                count++;
            }
        }
        if (count >= 3) {
            return 1;
        }
        break;
    case 0xC0:
        if (Ta_GetUnitNumFrom22bitFlagList(SearchUnitByRange(0, 0, arg0, 1, 5, 0xE)) >= 3) {
            return 1;
        }
        break;
    case 0x2DB:
    case 0x2EF:
        if (TaLogic_GetActionReaction(arg0, arg1, 0, 0, 6, 0) == 5) {
            return 2;
        }
        if (TaLogic012_IsPinch(slot) == 1) {
            return 1;
        }
        break;
    case 0x34E:
        if (TaLogic_GetActionReaction(arg0, arg1, 0, 0, 6, 0) == 5) {
            return 2;
        }
        if (TaLogic012_IsDoCerem(Ta_IsUnitControl(arg0, arg1), 0x34E) == 1 &&
            SzDuel_GetField(pos & 0xFF, pos >> 8) != 9) {
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

s32 TaLogic012_IsOpenMoveUnit(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 min_y;
    s32 min_x;

    min_y = arg3 < arg5 ? arg3 : arg5;
    arg5 = max_001464A0(arg5, arg3);
    min_x = arg2 < arg4 ? arg2 : arg4;
    arg4 = max_001464A0(arg4, arg2);

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

s32 TaLogic012_IsPinch(s32 arg0)
{
    s32 i;
    s32 mask;
    s32 entry;

    if (Ta_GetUnitNumFrom22bitFlagList(SearchUnitByRange(0, 0, arg0, 1, 0x34, 0xE)) > 2) {
        return 0;
    }

    mask = SearchUnitByRange(0, 0, arg0, 2, 0x34, 0xE);
    if (Ta_GetUnitNumFrom22bitFlagList(mask) < 5) {
        return 0;
    }

    for (i = 0; i < Ta_GetUnitNumFrom22bitFlagList(mask); i++) {
        entry = Ta_GetUnitOwnerIDFromLstCount(mask, i);
        if ((SzDuel_GetUnitLoc(entry >> 8, entry & 0xFF) >> 8) < 3) {
            return 1;
        }
    }

    return 0;
}

s32 TaLogic012_IsDoCerem(s32 arg0, s32 arg1) {
    s32 data[4];
    s32 index;
    s32 mask;
    s32 low;
    s32 high;
    s32 pair;
    s32 value;

    Ta_GetCeremSacrifice(data, *(s32 *)((u8 *)TaHand_GetCardEffect(arg1, 0) + 4));
    if ((mask = Ta_GetSacrificeUnit(data, arg0)) < 0) {
        return 0;
    }
    for (index = 0; index < Ta_GetUnitNumFrom22bitFlagList(mask); index++) {
        pair = Ta_GetUnitOwnerIDFromLstCount(mask, index);
        high = pair >> 8;
        low = pair & 0xFF;
        value = SzDuel_GetUnitLoc(high, low);
        if (TaUtil_GetUnitAP(high, low, value & 0xFF, value >> 8) >= 0x9C4) {
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

s32 TaLogic_GetInputQueFromMinimumTask_b(void *, void *, s32);

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
        TaLogic_DoAdjustLogicData(w);
        if (TaLogic_GetMinimumTask_001424B0(w, &req, arg0) == 0) {
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
} Ai_00146960;

#pragma conditional_move off

s32 TaLogic_GetMinimumTask_00146960(void *work, void *arg1, s32 arg2) {
    u16 *arg0 = work;
    Ai_00146960 *ai = work;
    s32 side;
    s32 found;
    s32 result;
    s32 index;

    side = SzDuel_GetTurnOwner();
    found = 0;
    ai->lvl = TaLogic013_IsActiveMode();
    if ((result = TaLogic_GetNextActiveUnit_00147100(arg0, side, ai->lvl, arg1)) < 0) {
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
    TaLogic_CommandUnit_00146EC0(arg0 + index * 8, ai->lvl);
    switch ((arg0[index * 8 + 2] >> 8) & 0xFF) {
    case 5:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_RunMission_00149690(arg0 + index * 8, side, arg1, 1);
            found = 1;
        }
        break;
    case 2:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            if (TaLogic_GetMinimumTask_AtkMission_00149C60(arg0 + index * 8, side, arg1, 1) < 0) {
                TaLogic_InitRogicControl(arg0 + index * 8, 1);
                return 1;
            }
            found = 1;
        }
        break;
    case 10:
        if (TaLogic_GetMinimumTask_Summon_00148020(arg0[index * 8], side, arg1) < 0) {
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
            TaLogic_GetMinimumTask_MoveMission_0014A240(arg0 + index * 8, side, arg1, 1, 0);
            found = 1;
        }
        break;
    case 3:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_MoveMission_0014A240(arg0 + index * 8, side, arg1, 1, 1);
            found = 1;
        }
        break;
    case 9:
        TaLogic_GetMinimumTask_EncMission(arg0 + index * 8, side, arg1, 1, 0, TaLogic_GetWarnHideLvl_0014B330(side), 5, 1);
        found = 1;
        break;
    case 12:
        TaLogic_GetMinimumTask_ReviveMission_0014AAB0(arg0 + index * 8, side, arg1, 1);
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
            TaLogic_GetMinimumTask_RunMission_00149690(arg0 + index * 8, side, arg1, 0);
            found = 1;
        }
        break;
    case 2:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            if (TaLogic_GetMinimumTask_AtkMission_00149C60(arg0 + index * 8, side, arg1, 0) < 0) {
                TaLogic_GetMinimumTask_RunMission_00149690(arg0 + index * 8, side, arg1, 0);
            }
            found = 1;
        }
        break;
    case 10:
        if (TaLogic_GetMinimumTask_Summon_00148020(arg0[index * 8], side, arg1) < 0) {
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
            TaLogic_GetMinimumTask_MoveMission_0014A240(arg0 + index * 8, side, arg1, 0, 0);
            found = 1;
        }
        break;
    case 3:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_MoveMission_0014A240(arg0 + index * 8, side, arg1, 0, 1);
            found = 1;
        }
        break;
    case 9:
        TaLogic_GetMinimumTask_EncMission(arg0 + index * 8, side, arg1, 0, 0, TaLogic_GetWarnHideLvl_0014B330(side), 5, 1);
        found = 1;
        break;
    case 12:
        TaLogic_GetMinimumTask_ReviveMission_0014AAB0(arg0 + index * 8, side, arg1, 0);
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

s32 TaLogic_CommandUnit_00146EC0(void *arg0, s32 arg1) {
    extern s32 TaLogic013_IsUnitInvader();
    s32 temp_s0;

    SzDuel_GetUnitLoc(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF);
    temp_s0 = Ta_IsUnitControl(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF);
    if (SzDuel_GetUnit(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF) != 0) {
        if (SzDuel_GetUnitStatus(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF, 0) == 0) {
            if (*(u16 *)arg0 != 0xFFFF) {
                if ((*(u16 *)arg0 & 0xFF) == 0) {
                    if (*(s32 *)((u8 *)arg0 + 8) == -1) {
                        if (TaLogic_IsAttackedNow(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF, 0) == 1) {
                            if (SzDuel_InqHandPhase(*(u16 *)arg0 >> 8) == 1) {
                                *(s16 *)((u8 *)arg0 + 4) = 0x50A;
                            } else {
                                *(s16 *)((u8 *)arg0 + 4) = 0x5FF;
                            }
                        } else {
                            if (SzDuel_InqHandPhase(*(u16 *)arg0 >> 8) == 1) {
                                *(s16 *)((u8 *)arg0 + 4) = 0xA05;
                            } else {
                                *(s16 *)((u8 *)arg0 + 4) = 0x5FF;
                            }
                        }
                    }
                } else {
                    switch (SzDuel_GetUnitKind(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF) >> 5) {
                    case 0:
                        if (TaLogic013_IsUnitInvader(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF) == 1) {
                            TaLogic013_CommandInvadeUnit(arg0);
                        } else if (TaUtil_IsExMonster(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF) == 1) {
                            TaLogic013_CommandEfcMonster(arg0);
                        } else {
                            TaLogic013_CommandBtlUnit(arg0);
                        }
                        break;
                    case 2:
                        TaLogic_CommandEncUnit(arg0, 5, 0, (u8)TaLogic_GetWarnHideLvl_0014B330(temp_s0));
                        break;
                    case 1:
                    case 3:
                        TaLogic013_CommandSpellUnit(arg0, arg1);
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

s32 TaLogic_GetNextActiveUnit_00147100(u16 *arg0, s32 arg1, s32 arg2, void *arg3) {
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
    TaLogic_CommandUnit_00146EC0(arg0 + idx * 8, arg2);
    if (((arg0[idx * 8 + 2] >> 8) & 0xFF) == 10) {
        if (SzDuel_InqHandPhase(arg1) == 1 && TaLogic_GetMinimumTask_Summon_00148020(pos, arg1, arg3) >= 0) {
            return pos | 0x10000;
        }
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_GetUnitStatus(arg1, 0, 0) == 0) {
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_InqHandPhase(arg1) == 1 && TaLogic_GetMinimumTask_Summon_00148020(pos, arg1, arg3) >= 0) {
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
    u8 pad3;
} Slot_001474F0;

typedef struct {
    u16 low;
    u16 high;
} DataHalves_001474F0;

typedef struct {
    u16 coordinates;
    u8 pad2[2];
    u16 state;
    u8 pad6[2];
    union {
        u32 word;
        DataHalves_001474F0 halves;
    } data;
} Entry_001474F0;

void TaLogic013_CommandBtlUnit(void *arg0) {
    extern s32 TaLogic_IsRootOpen();
    extern void TaLogic_InitIgnoreLst();
    extern s32 TaLogic013_GetNearUnit();
    Entry_001474F0 *entry = arg0;
    s32 side;
    s32 player;
    s32 pos;
    s32 other;
    s32 otherPos;
    s32 i;
    s32 result;
    u8 work[0x70];
    Slot_001474F0 list[22];
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
        if (TaLogic_IsRootOpen(entry->coordinates >> 8, entry->coordinates & 0xFF, pos & 0xFF, pos >> 8,
                          other >> 8, other & 0xFF, otherPos & 0xFF, otherPos >> 8, 2) > 0) {
            entry->state = 0x2FF;
            entry->data.word = (other << 16) | entry->data.halves.low;
            return;
        }
        countB = 0;
        countA = 0;
        i = 1;
        while (1) {
            switch (TaLogic013_GetNearUnit(entry, 0, player, pos & 0xFF, pos >> 8,
                                  Ta_GetCurrentSide(entry->coordinates >> 8, entry->coordinates & 0xFF) == 0 ? 1 : 0,
                                  (u8)i, TaLogic_GetWarnHideLvl_0014B330(side), list, 0,
                                  &countA, &countB, 2, work)) {
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
            }
            i++;
            if (i > 2) {
                break;
            }
        }
        if (TaLogic013_IsDefensePoint(pos & 0xFF, pos >> 8) == 1) {
            entry->state = 0x6FF;
            entry->data.word = (pos << 16) | entry->data.halves.low;
            return;
        }
        result = TaLogic013_GetEmptyLine();
        if (result >= 0) {
            entry->state = 0x6FF;
            entry->data.word = (result << 16) | entry->data.halves.low;
        } else {
            entry->state = 0x6FF;
            entry->data.word = entry->data.halves.low | (TaLogic013_GetInvadePoint(side, pos & 0xFF, pos >> 8) << 16);
        }
    }
}

void TaLogic013_GetNearUnit(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, u16 arg9, s32 arg10, s32 arg11, u8 arg12, s32 arg13) {
    TaLogic_GetNearUnit(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, 0, 0x960, arg13);
}

typedef struct {
    u16 card;
    u8 flag;
    u8 pad3;
} Slot_00147830;

typedef struct {
    u16 low;
    u16 high;
} DataHalves_00147830;

typedef struct {
    u16 coordinates;
    u8 pad2[2];
    u16 state;
    u8 pad6[2];
    union {
        u32 word;
        DataHalves_00147830 halves;
    } data;
} Entry_00147830;

static inline s32 other_00147830(s32 side) {
    return side == 0 ? 1 : 0;
}

#pragma opt_dead_assignments off

void TaLogic013_CommandInvadeUnit(void *arg0) {
    extern s32 TaLogic_IsRootOpen();
    extern void TaLogic_InitIgnoreLst();
    extern s32 TaLogic_GetNearUnit();
    Entry_00147830 *entry = arg0;
    s32 side;
    s32 player;
    s32 pos;
    s32 other;
    s32 otherPos;
    s32 i;
    s32 selection;
    u8 work[0x70];
    Slot_00147830 list[22];
    s16 countA;
    s16 countB;

    if (SzDuel_GetUnit(entry->coordinates >> 8, entry->coordinates & 0xFF) != 0) {
        side = Ta_GetCurrentSide(entry->coordinates >> 8, entry->coordinates & 0xFF);
        other = other_00147830(side) << 8;
        pos = SzDuel_GetUnitLoc(entry->coordinates >> 8, entry->coordinates & 0xFF);
        otherPos = SzDuel_GetUnitLoc(other >> 8, other & 0xFF);
        player = SzDuel_GetUnit(entry->coordinates >> 8, entry->coordinates & 0xFF);
        TaLogic_InitIgnoreLst(work);
        for (i = 0; i < 22; i++) {
            list[i].card = 0xFFFF;
            list[i].flag = 0xFF;
        }
        if (TaLogic_IsRootOpen(entry->coordinates >> 8, entry->coordinates & 0xFF, pos & 0xFF, pos >> 8,
                          other >> 8, other & 0xFF, otherPos & 0xFF, otherPos >> 8, 2) > 0) {
            entry->state = 0x2FF;
            entry->data.word = (other << 16) | entry->data.halves.low;
            return;
        }
        countB = 0;
        countA = 0;
        i = 1;
        while (1) {
            selection = TaLogic_GetWarnHideLvl_0014B330(side);
            switch (TaLogic_GetNearUnit(entry, 0, player, pos & 0xFF, pos >> 8,
                                  other_00147830(Ta_GetCurrentSide(entry->coordinates >> 8, entry->coordinates & 0xFF)),
                                  (u8)i, selection, list, 0,
                                  &countA, &countB, 5, 0, 0x960, work)) {
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
        entry->data.word = entry->data.halves.low | (TaLogic013_GetInvadePoint(side, pos & 0xFF, pos >> 8) << 16);
    }
}
#pragma opt_dead_assignments reset

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

void TaLogic013_CommandEfcMonster(void *arg0) {
    extern s32 SzDuel_GetUnitCardNo();
    Action_00147AC0 *action = arg0;
    s32 owner;
    u16 id;

    id = action->id;
    owner = Ta_IsUnitControl(id >> 8, id & 0xFF);
    id = action->id;
    switch (SzDuel_GetUnitCardNo(id >> 8, id & 0xFF)) {
    case 0x123:
        if (Ta_GetUnitNumFrom22bitFlagList(SearchUnitByRange(0, 0, owner, 1, 6, 14)) >= 3) {
            action->target = 0x3FF;
            id = action->id;
            action->info.word = (SzDuel_GetUnitLoc(id >> 8, id & 0xFF) << 16) | action->info.low;
            return;
        }
        break;
    }
    TaLogic013_CommandBtlUnit(action);
}

struct DotrSlotOrder {
    unsigned short position;
    unsigned short unknown_02;
    unsigned short unknown_04;
    unsigned short unknown_06;
    union {
        unsigned short half;
        int word;
    } flags;
};
extern unsigned *func_00250740_b(int a, int b, int n);

void TaLogic013_CommandSpellUnit(void *order_v, int flag)
{
    struct DotrSlotOrder * order = order_v;
    int here;
    int side;
    unsigned *p;
    int set;
    int i;
    int r;
    int cell;

    side = Ta_IsUnitControl(order->position >> 8, order->position & 0xff);
    p = func_00250740_b(order->position >> 8, order->position & 0xff, 0);
    here = SzDuel_GetUnitLoc(order->position >> 8, order->position & 0xff);
    if (p == 0) {
        order->unknown_04 = 0x5ff;
        return;
    }
    switch (*p >> 8) {
    case 20:
        order->unknown_04 = 0xcff;
        return;
    case 2:
        if ((unsigned char)flag == 1) {
            r = TaLogic_GetLandChange(SzDuel_GetUnit(order->position >> 8, order->position & 0xff), here & 0xff, here >> 8, 2, 6, 2);
            if (r >= 0) {
                order->unknown_04 = 0x6ff;
                order->flags.word = (r << 16) | order->flags.half;
            }
        }
        break;
    case 4:
        if ((unsigned char)flag == 1) {
            set = SearchUnitByRange(0, 0, side, 2, 30, 14);
            for (i = 0; i < Ta_GetUnitNumFrom22bitFlagList(set); i++) {
                r = Ta_GetUnitOwnerIDFromLstCount(set, i);
                cell = SzDuel_GetUnitLoc(r >> 8, r & 0xff);
                if (TaLogic013_IsUseHarpySweaper(side, here & 0xff, cell >> 8) == 1) {
                    order->unknown_04 = 0x6ff;
                    order->flags.word = order->flags.half | ((((cell >> 8) << 8) | (here & 0xff)) << 16);
                    return;
                }
                if (TaLogic013_IsUseHarpySweaper(side, cell & 0xff, here >> 8) == 1) {
                    order->unknown_04 = 0x6ff;
                    order->flags.word = order->flags.half | ((((here >> 8) << 8) | (cell & 0xff)) << 16);
                    return;
                }
            }
        }
        break;
    }
    order->unknown_04 = 0x5ff;
}

s32 TaLogic013_GetInvadePoint(s32 arg0, s32 arg1, s32 arg2) {
    if (arg2 < 3) {
        return (arg1 >= 3) ? 0x306 : 0x300;
    }
    return SzDuel_GetUnitLoc((arg0 == 0) ? 1 : 0, 0);
}

s32 TaLogic013_IsDefensePoint(s32 arg0, s32 arg1) {
    s32 var_s0;

    var_s0 = 0;
loop_1:
    if (((arg1 << 8) | arg0) == TaLogic013_GetDefensePoint(var_s0)) {
        return 1;
    }
    var_s0 += 1;
    if (var_s0 >= 5) {
        return 0;
    }
    goto loop_1;
}

s32 TaLogic013_GetDefensePoint(s32 arg0) {
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

s32 TaLogic013_GetEmptyLine(void) {
    s32 i;
    s32 value;
    s32 result;

    i = 0;
    do {
        value = TaLogic013_GetDefensePoint(i);
        if (((SzDuel_GetMapUnit(value & 0xFF, value >> 8) == 0) ? 1 : 0) == 1) {
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

s32 TaLogic_GetNearCard2(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8,
                  s32 arg9);

s32 TaLogic_GetMinimumTask_Summon_00148020(s32 arg0, s32 arg1, void *arg2) {
    extern s32 TaLogic_GetUnitNum(s32, s32);
    Act_00148020 *act = arg2;
    Card_00148020 buf;
    s32 res;
    s32 type;
    s32 card;
    s32 r;

    act->card = arg0;
    if (SzDuel_InqHandPhase(arg1) == 0) {
        return -1;
    }
    if (TaLogic_GetUnitNum(arg1, 0) == 5 && TaLogic_GetUnitNum(arg1, 1) == 5) {
        return -1;
    }
    type = TaLogic013_IsHandPlay(arg1, &buf);
    if (type < 0) {
        return -1;
    }
    act->f2 = 10;
    act->fC = 0;
    card = SzDuel_GetUnitLoc(arg0 >> 8, arg0 & 0xFF);
    if (type == 0) {
        if (TaLogic013_SetComboQue(arg1, arg2, &buf) >= 0) {
            res = TaLogic_GetNearCard2(&buf, card & 0xFF, card >> 8, arg1 == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, TaLogic_GetWarnHideLvl_0014B330(arg1));
            if (res < 0) {
                if (SzDuel_GetUnitMonsterCount(arg1) < 4) {
                    r = TaLogic013_GetSummonPiece(arg1, type, &buf, res);
                    if (r < 0) {
                        return -1;
                    }
                    act->f4 = r;
                    return 1;
                }
            } else {
                r = TaLogic013_GetSummonPiece(arg1, type, &buf, res);
                if (r < 0) {
                    return -1;
                }
                act->f4 = r;
                return 1;
            }
        }
    } else {
        res = TaLogic_GetNearCard2(&buf, card & 0xFF, card >> 8, arg1 == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, TaLogic_GetWarnHideLvl_0014B330(arg1));
    }
    if (type == 2) {
        TaLogic013_SetSpecialComboQue(arg1, arg2, &buf);
        r = TaLogic013_GetSummonPiece(arg1, type, &buf, res);
        if (r < 0) {
            return -1;
        }
        act->f4 = r;
        return 1;
    } else if (type == 3) {
        TaLogic013_GetSpecialComboPlay(arg1, arg2, &buf);
        r = TaLogic013_GetSummonPiece(arg1, type, &buf, res);
        if (r < 0) {
            return -1;
        }
        act->f4 = r;
        return 1;
    } else {
        if (TaLogic013_GetSpellPlay(arg1, arg2, &buf, buf.id) < 0) {
            return -1;
        }
        r = TaLogic013_GetSummonPiece(arg1, type, &buf, res);
        if (r < 0) {
            return -1;
        }
        act->f4 = r;
        return 1;
    }
}

s32 TaLogic013_IsHandPlay(s32 arg0, void *arg1) {
    extern s32 TaLogic_GetUnitNum();
    extern s32 SzDuel_GetUnitCurseRest();
    s32 entries[8];
    u8 scratch[32];
    u8 kind0;
    u8 kind1;

    kind0 = (u8)TaLogic_GetUnitNum(arg0, 0);
    kind1 = (u8)TaLogic_GetUnitNum(arg0, 1);
    if (arg1 == NULL) {
        return -1;
    }
    TaHand_GetNextHand(arg0, entries);
    if (kind0 == 5) {
        if (TaLogic013_GetSpellPlay(arg0, scratch, arg1, 999) >= 0) {
            return 1;
        }
        return -1;
    }
    if (kind1 == 5) {
        s32 i = 0;
        s32 *entry;

        if (i < TaHand_GetNextHandNum(arg0)) {
            entry = entries;
            do {
                if ((TaHand_GetCardKind(*entry) >> 5) == 0 &&
                    TaHand_IsCardSummon2(arg0, *entry) == 1) {
                    SzDuel_InitCardInfo(arg1, entries[i]);
                    return 0;
                }
                entry++;
                i++;
            } while (i < TaHand_GetNextHandNum(arg0));
        }
        return -1;
    }
    if (TaLogic013_GetSpecCardPlay(arg0, scratch, arg1, 0x34B) >= 0) {
        if (TaLogic013_IsDoCerem(arg0, 0x34B) == 1) {
            return 2;
        }
    }
    if (TaLogic013_GetSpecialComboPlay(arg0, scratch, arg1) == 1) {
        return 3;
    }
    if (Ta_GetUnitNumFrom22bitFlagList(SearchUnitByRange(0, 0, arg0, 1, 0x1E001C, 14)) > 0) {
        if (TaLogic013_GetSpecCardPlay(arg0, scratch, arg1, 30) >= 0) {
            return 2;
        }
    }
    if (TaLogic013_IsUseRevive(arg0) >= 0) {
        if (TaLogic013_GetSpecCardPlay(arg0, scratch, arg1, 0x2AD) >= 0) {
            return 2;
        }
    }
    {
        s32 i = 0;
        do {
            if (SzDuel_GetUnitCurseRest(arg0, i) != 0 &&
                TaLogic013_GetSpecCardPlay(arg0, scratch, arg1, 0x31C) >= 0) {
                return 2;
            }
            i++;
        } while (i < 11);
    }
    {
        s32 *entry;
        s32 i = 0;

        if (i < TaHand_GetNextHandNum(arg0)) {
            entry = entries;
            do {
                if ((TaHand_GetCardKind(*entry) >> 5) == 0 &&
                    TaHand_IsCardSummon2(arg0, *entry) == 1 && *entry != 0x110) {
                    SzDuel_InitCardInfo(arg1, entries[i]);
                    return 0;
                }
                entry++;
                i++;
            } while (i < TaHand_GetNextHandNum(arg0));
        }
    }
    {
        s32 result = TaLogic013_GetSpellPlay(arg0, scratch, arg1, 999);
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


s32 TaLogic013_GetSpecialComboPlay(s32 arg0, void *arg1, void *arg2) {
    Obj2_00148630 *o2 = arg2;
    Obj1_00148630 *o1 = arg1;
    s32 list[8];
    s32 i;
    s32 found;
    u8 k;

    TaHand_GetNextHand(arg0, list);
    for (i = 0, found = 0; i < TaHand_GetNextHandNum(arg0); i++) {
        if (list[i] == 0x31D) {
            found = 1;
            o1->slot[0] = i;
        }
    }
    if (found == 0) {
        return -1;
    }
    for (i = 0, found = 0; i < TaHand_GetNextHandNum(arg0); i++) {
        if (list[i] == 0x110 && TaHand_IsCardSummon2(arg0, list[i]) == 1) {
            o1->slot[1] = i;
            found = 1;
        }
    }
    if (found == 0) {
        return -1;
    }
    k = 2;
    SzDuel_InitCardInfo(o2, 0x111);
    for (i = 0; i < TaHand_GetNextHandNum(arg0); i++) {
        if (i != o1->slot[0] && i != o1->slot[1]) {
            if (Ta_GetHandEnchant(0x111, list[i]) >= 0 && (TaHand_GetCardKind(list[i]) >> 5) == 2) {
                if (list[i] != 0x31B && list[i] != 0x31C) {
                    o1->slot[k] = i;
                    k++;
                    o2->attack += (s16)TaEnc_GetEncScore(list[i]);
                    o2->defense += (s16)TaEnc_GetEncScore(list[i]);
                }
            }
        }
    }
    return 1;
}

s32 TaLogic013_GetSpecCardPlay(s32 arg0, void *arg1, void *arg2, s32 arg3) {
    s32 entries[8];
    s32 index;
    s32 *entry;

    TaHand_GetNextHand(arg0, entries);
    index = 0;
    if (index < TaHand_GetNextHandNum(arg0)) {
        entry = entries;
        do {
            if (((arg3 & 0xFFFF) == *entry) && (TaHand_IsCardSummon2(arg0, *entry) == 1)) {
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

s32 TaLogic013_GetSpellPlay(s32 arg0, u8 *arg1, void *arg2, s32 arg3) {
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


s32 TaLogic013_SetComboQue(s32 arg0, u8 *arg1, void *arg2) {
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
                            TaLogic_ConvEmptyCombo_00148D40(arg0, *node, entries);
                            TaLogic_CopyArray((u8 *)*node + 2, arg1 + 6);
                            SzDuel_InitCardInfo(arg2, **node);
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
            } while (i < TaHand_GetNextHandNum(arg0));
        }
        return top;
    }
}

typedef struct {
    u16 id;
    u8 values[5];
} Info_00148D40;

void TaLogic_ConvEmptyCombo_00148D40(s32 arg0, void *arg1, s32 *arg2) {
    Info_00148D40 *info = arg1;
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
                if (card != 0x3E7 && TaLogic013_IsRefuseEmptyCombo(card) == 0 && level >= TaHand_GetCardSummonCost2(card, arg0)) {
                    cost = TaHand_GetCardAPDP(card);
                    if ((cost & 0xFFFF) + (cost >> 16) * 2 < 0x1069 && TaHand_IsCardEffect(card) == 2 &&
                        (u16)TaLogic_GetHandFusion(info->id, (u16)card) == 0x3E7) {
                        TaLogic_AddEmptyCombo(info->values, buf[i]);
                    }
                }
            }
        }
    }
}

s32 TaLogic013_IsRefuseEmptyCombo(s32 arg0) {
    if ((TaHand_GetCardKind(arg0) >> 5) != 0) {
        return 1;
    } else if (TaHand_IsCardEffect(arg0) == 1) {
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

s32 TaLogic013_SetSpecialComboQue(s32 arg0, void *arg1, void *arg2) {
    Obj1_00148F80 *o1 = arg1;
    Obj2_00148F80 *o2 = arg2;
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
                        o2->f38 += (s16)TaEnc_GetEncScore(list[i]);
                        o2->f3A += (s16)TaEnc_GetEncScore(list[i]);
                    }
                }
            }
        }
    }
    return 1;
}

typedef struct Nibbles_001491B0 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_001491B0;

static inline s32 find_target_001491B0(void) {
    s32 index = 0;
    s32 target;
    do {
        target = TaLogic013_GetDefensePoint(index);
        if ((SzDuel_GetMapUnit(target & 255, target >> 8) == 0 ? 1 : 0) == 1) {
            return TaLogic013_GetDefensePoint(index);
        }
        index++;
    } while (index < 5);
    return -1;
}

s32 TaLogic013_GetSummonPiece(s32 arg0, u8 arg1, void *arg2, s32 arg3) {
    s32 best;
    s32 min;
    s32 fallback;
    Nibbles_001491B0 path[12];
    s32 i;
    Nibbles_001491B0 *p;
    s32 y;
    s32 x;
    s32 target_y;
    s32 target_x;
    s32 lowest;
    s32 result;
    s32 target;
    s32 kind;
    s32 type;

    extern s32 TaLogic_IsUnitWin4();
    extern s32 SzDuel_Kind2Type();
    extern s32 TaLogic_GetInvadeRoot2();
    extern s32 TaLogic_GetRoot2(void *, void *, s32, s32, s32, s32, u16, u8);

    if (arg2 == NULL) {
        return -1;
    }
    p = path;
    i = 0;
    do {
        p->low = p->high = 15;
        p++;
        i++;
    } while (i < 12);

    kind = (type = (u8)(*((u8 *)arg2 + 0x3E) >> 5));
    if (kind != 0) {
        if (SzDuel_Kind2Type(kind, type) != 2) {
            goto other_kind;
        }
    }
    {
        s32 first_coord;
        s32 first_y;
        s32 first_x;
        s32 index;
        if (arg3 >= 0) {
            s32 result;
            s32 dest_y;
            s32 dest_x;
            min = 255;
            best = 65535;
            result = SzDuel_GetUnitLoc(arg3 >> 8, arg3 & 255);
            index = 0;
            dest_y = result >> 8;
            dest_x = result & 255;
            do {
                first_coord = Ta_GetSommonPiecePreference(arg0, index);
                if (first_coord >= 0) {
                    first_x = first_coord & 255;
                    first_y = first_coord >> 8;
                    if (SzDuel_GetField(first_x, first_y) != 8 &&
                        (SzDuel_GetField(first_x, first_y) != 9 || Ta_IsVirus_Chk3(arg2, first_x, first_y) != 1) &&
                        SzDuel_GetMapUnit(first_x, first_y) == 0) {
                        result = TaLogic_IsUnitWin4(arg2, arg3, TaLogic_GetWarnHideLvl_0014B330(arg0), dest_x, dest_y, 0) > 0
                            ? TaLogic_GetInvadeRoot2(arg2, path, first_x, first_y, dest_x, dest_y, arg3, 0, 3, (u16)TaLogic_GetWarnHideLvl_0014B330(arg0))
                            : TaLogic_GetRoot2(arg2, path, first_x, first_y, dest_x, dest_y, arg3, 3);
                        if (TaLogic_GetMinGoalCount((u8 *)path) > 0 && result < min) {
                            min = result;
                            best = first_coord;
                        }
                    }
                }
                index++;
            } while (index < 8);
            if (best != 65535) {
                return best;
            }
        }
        {
            lowest = 14;
            fallback = -1;
            index = 0;
            do {
                arg3 = Ta_GetSommonPiecePreference(arg0, index);
                if (arg3 >= 0) {
                    x = arg3 & 255;
                    y = arg3 >> 8;
                    if (SzDuel_GetField(x, y) != 8 &&
                        (SzDuel_GetField(x, y) != 9 || Ta_IsVirus_Chk3(arg2, x, y) != 1) &&
                        SzDuel_GetMapUnitID(x, y) < 0) {
                        target = find_target_001491B0();
                        target_x = target & 255;
                        target_y = target >> 8;
                        result = SzDuel_GetMapUnitID(target_x, target_y);
                        if (result < 0) {
                            result = 65535;
                        }
                        result = TaLogic_GetRoot2(arg2, path, x, y, target_x, target_y, result, 7);
                        if (result < lowest && result >= 0) {
                            fallback = arg3;
                            lowest = result;
                        }
                    }
                }
                index++;
            } while (index < 8);
            if (lowest < 14) {
                return fallback;
            } else {
                fallback = -1;
            }
        }
        return fallback;
    }
other_kind:
    {
        s32 y;
        s32 x;
        s32 index;
        s32 result;
        s32 coord;
        result = -1;
        index = 0;
        do {
            coord = Ta_GetSommonPiecePreference(arg0, index);
            if (coord >= 0) {
                x = coord & 255;
                y = coord >> 8;
                if (SzDuel_GetField(x, y) != 8 &&
                    (SzDuel_GetField(x, y) != 9 || Ta_IsVirus_Chk3(arg2, x, y) != 1) &&
                    SzDuel_GetMapUnitID(x, y) < 0 && y < 8) {
                    result = coord;
                }
            }
            index++;
        } while (index < 8);
        if (result >= 0) {
            return result;
        } else {
            result = -1;
        }
        return result;
    }
}

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


s32 TaLogic_GetMinimumTask_RunMission_00149690(u16 *arg0, s32 arg1, void *arg2, u8 arg3) {
    Output_00149690 *output = arg2;
    s32 target;
    u8 endX;
    u8 extra;
    Nibbles_00149690 nibbles[12];
    s32 bestScore;
    s32 best;
    s32 i;
    Nibbles_00149690 *p;
    extern s32 TaLogic_IsOpenUnit_0014AE60();
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

        initialScore = TaLogic_GetWarnHideLvl_0014B330(arg1);
        centerX = target & 0xFF;
        centerY = target >> 8;
        if (TaLogic_GetUnitWarning(centerX, centerY, *arg0, 3, initialScore, 0) == 0) {
            output->position = *arg0;
            output->action = 6;
            output->destination = target;
            output->result = TaLogic_IsDefStyleUnit(*arg0 >> 8, *arg0 & 0xFF, output->destination, 1, 0);
            output->special = TaLogic_IsOpenUnit_0014AE60(*arg0 >> 8, *arg0 & 0xFF, arg0);
            TaLogic_InitRogicControl(arg0, arg3);
            return 0;
        }
        if ((range = GetMoveRev(SzDuel_GetUnit(*arg0 >> 8, *arg0 & 0xFF), centerX, centerY)) == 0) {
            output->position = *arg0;
            output->action = 6;
            output->destination = target;
            output->result = TaLogic_IsDefStyleUnit(*arg0 >> 8, *arg0 & 0xFF, output->destination, 1, 0);
            output->special = TaLogic_IsOpenUnit_0014AE60(*arg0 >> 8, *arg0 & 0xFF, arg0);
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
                        candidateScore = TaLogic_GetUnitWarning(x, y, *arg0, 3, (u16)TaLogic_GetWarnHideLvl_0014B330(arg1), 0);
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
                output->result = TaLogic_IsDefStyleUnit(*arg0 >> 8, *arg0 & 0xFF, output->destination, 0, 0);
            }
            output->special = TaLogic_IsOpenUnit_0014AE60(*arg0 >> 8, *arg0 & 0xFF, arg0);
        } else {
            output->position = *arg0;
            output->action = 6;
            output->destination = target;
            output->result = TaLogic_IsDefStyleUnit(*arg0 >> 8, *arg0 & 0xFF, output->destination, 1, 0);
            output->special = TaLogic_IsOpenUnit_0014AE60(*arg0 >> 8, *arg0 & 0xFF, arg0);
        }
        TaLogic_InitRogicControl(arg0, arg3);
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

s32 TaLogic_GetMinimumTask_AtkMission_00149C60(void *arg0, s32 arg1, void *arg2, u8 arg3) {
    extern s32 TaLogic_IsOpenUnit_0014AE60();
    extern s32 GetMoveRev();
    extern s32 TaLogic_GetUnitWarning();
    extern void TaLogic_GetInvadeRoot();
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
    if (SzDuel_GetUnit(targetHigh >> 8, targetLow & 0xFF) == 0) {
        TaLogic_InitRogicControl(arg0, 1);
        return -1;
    }
    fallback = TaLogic_IsOpenUnit_0014AE60((s32)input->position >> 8, input->position & 0xFF, arg0);
    origin = SzDuel_GetUnitLoc((s32)input->position >> 8, input->position & 0xFF);
    targetLow = target_00149C60(arg0, arg3);
    targetHigh = target_00149C60(arg0, arg3);
    targetPosition = SzDuel_GetUnitLoc(targetHigh >> 8, targetLow & 0xFF);
    i = 0;
    do {
        candidates[i].x = candidates[i].y = 15;
        i++;
    } while (i < 12);
    card = SzDuel_GetUnit((s32)input->position >> 8, input->position & 0xFF);
    originX = origin & 0xFF;
    originY = origin >> 8;
    if (GetMoveRev(card, originX, originY) == 0) {
        s32 cost;
        output->position = input->position;
        output->action = 6;
        output->destination = origin;
        cost = TaLogic_GetUnitWarning(originX, originY, arg1, 3, 1, (u8)TaLogic_GetWarnHideLvl_0014B330(arg1));
        if (cost >= SzDuel_GetUnitAP((s32)input->position >> 8, input->position & 0xFF, 0)) {
            output->result = TaLogic_IsDefStyleUnit((s32)input->position >> 8,
                                         input->position & 0xFF, output->destination, 1, 0);
        } else {
            output->result = TaLogic_IsDefStyleUnit((s32)input->position >> 8,
                                         input->position & 0xFF, output->destination, 0, 0);
        }
        TaLogic_InitRogicControl(arg0, arg3);
    } else {
        s32 position = input->position;
        u16 kind = TaLogic_GetWarnHideLvl_0014B330(arg1);
        s32 positionY = position >> 8;
        s32 positionX = position & 0xFF;

        TaLogic_GetInvadeRoot(positionY, positionX, candidates,
                     originX, originY, targetX = targetPosition & 0xFF, targetPosition >>= 8,
                     target_00149C60(arg0, arg3), (s64)0, (s64)30, (s64)kind);
        count = TaLogic_GetMinGoalCount((u8 *)candidates);
        bestIndex = 255;
        if (count > 0) {
            special = 0;
            bestCost = 65535;
            for (index = 0; index < count; index++) {
                if (TaLogic013_IsOpenMoveUnit((s32)input->position >> 8, input->position & 0xFF,
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
                    cost = TaLogic_GetUnitWarning(candidate->x, candidate->y, arg1,
                                         2, 1, (u8)TaLogic_GetWarnHideLvl_0014B330(arg1));
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
            output->result = TaLogic_IsDefStyleUnit((s32)input->position >> 8,
                                         input->position & 0xFF, output->destination, 0, 0);
            TaLogic_InitRogicControl(arg0, arg3);
            return 0;
        }
        if (bestIndex != 255) {
            output->position = input->position;
            output->action = 6;
            output->destination = (candidates[bestIndex].y << 8) | candidates[bestIndex].x;
            output->special = special;
            output->result = TaLogic_IsDefStyleUnit((s32)input->position >> 8,
                                         input->position & 0xFF, output->destination, 0, 0);
        } else {
            output->position = input->position;
            output->action = 6;
            output->destination = origin;
            output->special = special;
            output->result = TaLogic_IsDefStyleUnit((s32)input->position >> 8,
                                         input->position & 0xFF, output->destination, 0, 0);
            TaLogic_InitRogicControl(arg0, arg3);
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

s32 TaLogic_GetMinimumTask_MoveMission_0014A240(void *arg0, s32 arg1, void *arg2, u8 arg3, u8 arg4) {
    extern s32 TaLogic_IsOpenUnit_0014AE60();
    extern s32 TaLogic_GetUnitWarning();
    extern void TaLogic_GetRoot();
    extern s32 TaLogic_IsDefStyleUnit(s32, s32, s32, u8, s32);
    Coord_0014A240 coords[12];
    s32 initial;
    s32 cell;
    s32 count;

    initial = SzDuel_GetUnitLoc(((Unit_0014A240 *)arg0)->position >> 8, ((Unit_0014A240 *)arg0)->position & 0xFF);
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
            ((Output_0014A240 *)arg2)->flag = TaLogic_IsDefStyleUnit(((Unit_0014A240 *)arg0)->position >> 8, ((Unit_0014A240 *)arg0)->position & 0xFF, ((Output_0014A240 *)arg2)->target, arg4, 0);
            ((Output_0014A240 *)arg2)->value = TaLogic_IsOpenUnit_0014AE60(((Unit_0014A240 *)arg0)->position >> 8, ((Unit_0014A240 *)arg0)->position & 0xFF, arg0);
            TaLogic_InitRogicControl(arg0, arg3);
            return 0;
        }
    }

    if (SzDuel_GetUnitStatus(((Unit_0014A240 *)arg0)->position >> 8,
                      ((Unit_0014A240 *)arg0)->position & 0xFF, 4) != 0) {
        if ((SzDuel_GetUnitKind(((Unit_0014A240 *)arg0)->position >> 8,
                          ((Unit_0014A240 *)arg0)->position & 0xFF) >> 5) == 1 ||
            (SzDuel_GetUnitKind(((Unit_0014A240 *)arg0)->position >> 8,
                          ((Unit_0014A240 *)arg0)->position & 0xFF) >> 5) == 5) {
            SzDuel_SetUnitStatus(((Unit_0014A240 *)arg0)->position >> 8,
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

    cell = SzDuel_GetMapUnitID(target_0014A240(arg0, side) & 0xFF, ((u32)target_0014A240(arg0, side)) >> 8);
    if (cell < 0) {
        cell = 0xFFFF;
    }
    TaLogic_GetRoot(((Unit_0014A240 *)arg0)->position >> 8, ((Unit_0014A240 *)arg0)->position & 0xFF,
                 coords, initial & 0xFF, initial >> 8, target_0014A240(arg0, side) & 0xFF,
                 ((u32)target_0014A240(arg0, side)) >> 8, (u16)cell, 7);
    count = TaLogic_GetMinGoalCount((u8 *)coords);
    {
        if (count > 0) {
        best = 0xFF;
        bestScore = 0xFFFF;
        for (index = 0; index < count; index++) {
                if (SzDuel_GetMapUnit(candidate->x, candidate->y) == 0) {
                    s32 score = TaLogic_GetUnitWarning(candidate->x, candidate->y, arg1, 2, 1, (u8)TaLogic_GetWarnHideLvl_0014B330(arg1));
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
            ((Output_0014A240 *)arg2)->flag = TaLogic_IsDefStyleUnit(((Unit_0014A240 *)arg0)->position >> 8, ((Unit_0014A240 *)arg0)->position & 0xFF, ((Output_0014A240 *)arg2)->target, arg4, 0);
            ((Output_0014A240 *)arg2)->value = TaLogic_IsOpenUnit_0014AE60(((Unit_0014A240 *)arg0)->position >> 8, ((Unit_0014A240 *)arg0)->position & 0xFF, arg0);
        TaLogic_InitRogicControl(arg0, arg3);
        return 0;
    }

        if (best != 0xFF) {
            ((Output_0014A240 *)arg2)->position = ((Unit_0014A240 *)arg0)->position;
            ((Output_0014A240 *)arg2)->kind = 6;
            ((Output_0014A240 *)arg2)->target = (coords[best].y << 8) | coords[best].x;
            ((Output_0014A240 *)arg2)->flag = TaLogic_IsDefStyleUnit(((Unit_0014A240 *)arg0)->position >> 8, ((Unit_0014A240 *)arg0)->position & 0xFF, ((Output_0014A240 *)arg2)->target, arg4, 0);
            ((Output_0014A240 *)arg2)->value = TaLogic_IsOpenUnit_0014AE60(((Unit_0014A240 *)arg0)->position >> 8, ((Unit_0014A240 *)arg0)->position & 0xFF, arg0);
        } else {
            ((Output_0014A240 *)arg2)->position = ((Unit_0014A240 *)arg0)->position;
            ((Output_0014A240 *)arg2)->kind = 6;
            ((Output_0014A240 *)arg2)->target = initial;
            ((Output_0014A240 *)arg2)->flag = TaLogic_IsDefStyleUnit(((Unit_0014A240 *)arg0)->position >> 8, ((Unit_0014A240 *)arg0)->position & 0xFF, ((Output_0014A240 *)arg2)->target, arg4, 0);
            ((Output_0014A240 *)arg2)->value = TaLogic_IsOpenUnit_0014AE60(((Unit_0014A240 *)arg0)->position >> 8, ((Unit_0014A240 *)arg0)->position & 0xFF, arg0);
        }
        TaLogic_InitRogicControl(arg0, arg3);
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


s32 TaLogic_GetMinimumTask_ReviveMission_0014AAB0(void *arg0, s32 arg1, void *arg2, u8 arg3) {
    Unit_0014AAB0 *unit = arg0;
    s32 pos;
    s32 card;
    s32 col;
    u16 row;
    Out_0014AAB0 *out = arg2;
    Nibbles_0014AAB0 entries[12];
    s32 i;
    Nibbles_0014AAB0 *entry;

    pos = SzDuel_GetUnitLoc(unit->pos >> 8, unit->pos & 0xFF);
    entry = entries;
    i = 0;
    do {
        entry->low = entry->high = 15;
        entry++;
        i++;
    } while (i < 12);
    card = TaLogic013_IsUseRevive(arg1);
    if (SzDuel_GetField(pos & 0xFF, pos >> 8) == 9) {
        card = -1;
    }
    if (TaLogic_GetActionReaction(unit->pos >> 8, unit->pos & 0xFF, 0, 0, 6, 0) == 5) {
        card = -1;
    }
    if (card >= 0) {
        row = card >> 16;
        col = TaLogic_GetGraveEntryAfterScreen(row, card & 0xFF, 1);
        out->pos = unit->pos;
        out->kind = 12;
        out->result = TaLogic_IsDefStyleUnit(unit->pos >> 8, unit->pos & 0xFF, out->target, 1, 0);
        out->flag = 1;
        out->target = (row << 8) | col;
        TaLogic_InitRogicControl(unit, arg3);
        return 0;
    }
    if (SzDuel_GetUnitStatus(unit->pos >> 8, unit->pos & 0xFF, 4) != 0) {
        SzDuel_SetUnitStatus(unit->pos >> 8, unit->pos & 0xFF, 0, 1);
        out->pos = unit->pos;
        out->kind = 14;
        return 0;
    }
    return TaLogic_GetMinimumTask_RunMission_00149690(unit, arg1, out, arg3);
}

s32 TaLogic013_IsActiveMode(void) {
    s32 player;
    s32 i;
    s32 list;
    s32 pair;

    player = SzDuel_GetTurnOwner();
    list = SearchUnitByRange(0, 0, player, 1, 0x111001C, 0xE);
    for (i = 0; i < Ta_GetUnitNumFrom22bitFlagList(list); i++) {
        pair = Ta_GetUnitOwnerIDFromLstCount(list, i);
        if (SzDuel_GetUnitAP(pair >> 8, pair & 0xFF, 0) > SzDuel_GetUnitAP(pair >> 8, pair & 0xFF, 1)) {
            return 1;
        }
    }
    list = SearchUnitByRange(0, 0, player, 1, 0x1E001C, 0xE);
    for (i = 0; i < Ta_GetUnitNumFrom22bitFlagList(list); i++) {
        pair = Ta_GetUnitOwnerIDFromLstCount(list, i);
        if (SzDuel_GetUnitAP(pair >> 8, pair & 0xFF, 0) > SzDuel_GetUnitAP(pair >> 8, pair & 0xFF, 1)) {
            return 1;
        }
    }
    return SearchUnitByRange(0, 0, player, 1, 0xB001C, 0xE) != 0 ? 1 : 0;
}

s32 TaLogic_IsOpenUnit_0014AE60(s32 arg0, s32 arg1) {
    s32 kind;
    s32 pos;
    s32 slot;
    u32 *card;
    s32 found;

    kind = SzDuel_GetUnitCardNo();
    pos = SzDuel_GetUnitLoc(arg0, arg1);
    slot = Ta_IsUnitControl(arg0, arg1);
    card = SzDuel_GetUnitEffect(arg0, arg1, 0);
    if (SzDuel_GetUnitStatus(arg0, arg1, 4) != 0) {
        return 0;
    }
    switch (SzDuel_GetUnitKind(arg0, arg1) >> 5) {
    case 0:
        switch (kind) {
        case 0x123:
            if (Ta_GetUnitNumFrom22bitFlagList(SearchUnitByRange(0, 0, arg0, 1, 6, 0xE)) >= 3) {
                return 1;
            }
            break;
        case 0x110:
        case 0x111:
            if (Ta_GetUnitNumFrom22bitFlagList(SearchUnitByRange(0, 0, arg0, 1, 0x1E001C, 0xE)) > 0) {
                return 1;
            }
            break;
        }
        return 2;
    case 5:
        if (TaLogic_GetActionReaction(arg0, arg1, 0, 0, 6, 0) == 5) {
            return 2;
        }
        if (TaLogic013_IsDoCerem(Ta_IsUnitControl(arg0, arg1), kind) == 1 &&
            SzDuel_GetField(pos & 0xFF, pos >> 8) != 9) {
            return 1;
        }
        break;
    case 1:
        if (TaLogic_GetActionReaction(arg0, arg1, 0, 0, 6, 0) == 5) {
            return 2;
        }
        if (card == NULL) {
            return 2;
        }
        switch (*card >> 8) {
        case 0xD:
            return 1;
        case 2:
            found = TaLogic_GetLandChange(SzDuel_GetUnit(arg0, arg1), pos & 0xFF, pos >> 8, 2, 6, 2);
            if (found >= 0 && found == pos) {
                return 1;
            }
            break;
        case 4:
            if (TaLogic013_IsUseHarpySweaper(arg0, pos & 0xFF, pos >> 8) == 1) {
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

s32 TaLogic013_IsOpenMoveUnit(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 min_y;
    s32 min_x;

    min_y = arg3 < arg5 ? arg3 : arg5;
    arg5 = max_0014B140(arg5, arg3);
    min_x = arg2 < arg4 ? arg2 : arg4;
    arg4 = max_0014B140(arg4, arg2);
    if ((arg4 - min_x) + (arg5 - min_y) != 2) {
        return 0;
    }
    if (SzDuel_GetUnit(arg0, arg1) == 0) {
        return 0;
    }
    if (SzDuel_GetUnitStatus(arg0, arg1, 0) == 0) {
        return check_0014B140(CheckLandAgreement2(SzDuel_GetField(arg2, arg3), arg0, arg1));
    }
    return 0;
}

s32 TaLogic013_IsDoCerem(s32 arg0, s32 arg1) {
    s32 sp50[4];
    s32 i;
    s32 mask;
    s32 low;
    s32 high;
    s32 value;
    s32 result;

    Ta_GetCeremSacrifice(sp50, *(s32 *)((u8 *)TaHand_GetCardEffect(arg1, 0) + 4));
    if ((mask = Ta_GetSacrificeUnit(sp50, arg0)) < 0) {
        return 0;
    }
    for (i = 0; i < Ta_GetUnitNumFrom22bitFlagList(mask); i++) {
        value = Ta_GetUnitOwnerIDFromLstCount(mask, i);
        high = value >> 8;
        low = value & 0xFF;
        result = SzDuel_GetUnitLoc(high, low);
        if (TaUtil_GetUnitAP(high, low, result & 0xFF, result >> 8) >= 0x960) {
            return 0;
        }
    }
    return 1;
}

s32 TaLogic_GetWarnHideLvl_0014B330(s32 arg0) {
    return SzDuel_GetLP(arg0) > 0x5DC
        ? (SzDuel_GetUnitMonsterCount(arg0) >= 4 ? 0x2EE : 0x5DC)
        : 0x7D0;
}

s32 TaLogic013_IsUnitInvader(void) {
    s32 value;

    value = SzDuel_GetUnitCardNo();
    if (value == 0x111 || value == 0x1E || value == 0xB) {
        return 1;
    }
    return 0;
}

/* From the dotr-decomp CC0 bundle (commit 88c32bb2), chatC/imp/conv.py. */

extern unsigned char func_0014ACA0_b(int, int, int);

int TaLogic013_IsUseHarpySweaper(int a, int b, int c)
{
    if (func_0014ACA0_b(a, b, c) == 0) {
        return 0;
    }
    if (SearchUnitByRange(b, c, a, 1, 30, 18) != 0) {
        return 0;
    }
    return SearchUnitByRange(b, c, a, 2, 30, 18) != 0 ? 1 : 0;
}

s32 TaLogic013_IsUseRevive(s32 arg0) {
    extern s32 SzDuel_GetGraveCount(s32);
    s32 i;

    if (SzDuel_GetUnitMonsterCount(arg0) >= 5) {
        return -1;
    }
    if (TaLogic_GetGraveCardCount(arg0, 3, 0x111) > 0 || TaLogic_GetGraveCardCount(arg0, 3, 0x1E) > 0 ||
        TaLogic_GetGraveCardCount(arg0, 3, 0xB) > 0) {
        for (i = 0; i < SzDuel_GetGraveCount(arg0); i++) {
            if (SzDuel_InqGrave(arg0, i) == 0xB) {
                return (arg0 << 16) | i;
            }
        }
        for (i = 0; i < SzDuel_GetGraveCount(arg0 == 0 ? 1 : 0); i++) {
            if (SzDuel_InqGrave(arg0 == 0 ? 1 : 0, i) == 0xB) {
                return ((arg0 == 0 ? 1 : 0) << 16) | i;
            }
        }
        for (i = 0; i < SzDuel_GetGraveCount(arg0); i++) {
            if (SzDuel_InqGrave(arg0, i) == 0x1E) {
                return (arg0 << 16) | i;
            }
        }
        for (i = 0; i < SzDuel_GetGraveCount(arg0 == 0 ? 1 : 0); i++) {
            if (SzDuel_InqGrave(arg0 == 0 ? 1 : 0, i) == 0x1E) {
                return ((arg0 == 0 ? 1 : 0) << 16) | i;
            }
        }
        for (i = 0; i < SzDuel_GetGraveCount(arg0); i++) {
            if (SzDuel_InqGrave(arg0, i) == 0x111) {
                return (arg0 << 16) | i;
            }
        }
        for (i = 0; i < SzDuel_GetGraveCount(arg0 == 0 ? 1 : 0); i++) {
            if (SzDuel_InqGrave(arg0 == 0 ? 1 : 0, i) == 0x111) {
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

s32 TaLogic_GetInputQueFromMinimumTask_b(void *, void *, s32);

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
        TaLogic_DoAdjustLogicData(w);
        if (TaLogic_GetMinimumTask_00146960(w, &req, arg0) == 0) {
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

s32 TaLogic_GetMinimumTask_0014B900(void *work, void *arg1, s32 arg2) {
    u16 *arg0 = work;
    s32 side;
    s32 found;
    s32 result;
    s32 index;

    side = SzDuel_GetTurnOwner();
    found = 0;
    if ((result = TaLogic_GetNextActiveUnit_0014BFD0(arg0, side, (s32)arg1)) < 0) {
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
    TaLogic_CommandUnit_0014BDE0(arg0 + index * 8);
    switch ((arg0[index * 8 + 2] >> 8) & 0xFF) {
    case 5:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_RunMission_0014DF80(arg0 + index * 8, side, arg1, 1);
            found = 1;
        }
        break;
    case 2:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            if (TaLogic_GetMinimumTask_AtkMission_0014E550(arg0 + index * 8, side, arg1, 1) < 0) {
                TaLogic_InitRogicControl(arg0 + index * 8, 1);
                return 1;
            }
            found = 1;
        }
        break;
    case 10:
        if (TaLogic_GetMinimumTask_Summon_0014CBA0(arg0[index * 8], side, (s32)arg1) < 0) {
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
            TaLogic_GetMinimumTask_MoveMission_0014EB30(arg0 + index * 8, side, arg1, 1, 0);
            found = 1;
        }
        break;
    case 3:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_MoveMission_0014EB30(arg0 + index * 8, side, arg1, 1, 1);
            found = 1;
        }
        break;
    case 9:
        TaLogic_GetMinimumTask_EncMission(arg0 + index * 8, side, arg1, 1, 0, TaLogic_GetWarnHideLvl_0014F9B0(side), 5, 1);
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
            TaLogic_GetMinimumTask_RunMission_0014DF80(arg0 + index * 8, side, arg1, 0);
            found = 1;
        }
        break;
    case 2:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            if (TaLogic_GetMinimumTask_AtkMission_0014E550(arg0 + index * 8, side, arg1, 0) < 0) {
                TaLogic_GetMinimumTask_RunMission_0014DF80(arg0 + index * 8, side, arg1, 0);
            }
            found = 1;
        }
        break;
    case 10:
        if (TaLogic_GetMinimumTask_Summon_0014CBA0(arg0[index * 8], side, (s32)arg1) < 0) {
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
            TaLogic_GetMinimumTask_MoveMission_0014EB30(arg0 + index * 8, side, arg1, 0, 0);
            found = 1;
        }
        break;
    case 3:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_MoveMission_0014EB30(arg0 + index * 8, side, arg1, 0, 1);
            found = 1;
        }
        break;
    case 9:
        TaLogic_GetMinimumTask_EncMission(arg0 + index * 8, side, arg1, 0, 0, TaLogic_GetWarnHideLvl_0014F9B0(side), 5, 1);
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

s32 TaLogic_CommandUnit_0014BDE0(void *arg0) {
    u16 card;
    s32 low;
    s32 type;
    s32 temp_s0;

    card = *(u16 *)arg0;
    SzDuel_GetUnitLoc(card >> 8, card & 0xFF);
    card = *(u16 *)arg0;
    temp_s0 = Ta_IsUnitControl(card >> 8, card & 0xFF);
    card = *(u16 *)arg0;
    if (SzDuel_GetUnit(card >> 8, card & 0xFF) != 0) {
        card = *(u16 *)arg0;
        if (SzDuel_GetUnitStatus(card >> 8, card & 0xFF, 0) == 0) {
            card = *(u16 *)arg0;
            if (card != 0xFFFF) {
                low = card & 0xFF;
                if (low == 0) {
                    if (*(s32 *)((u8 *)arg0 + 8) == -1) {
                        if (TaLogic_IsAttackedNow(card >> 8, low, 0) == 1) {
                            if (SzDuel_InqHandPhase(*(u16 *)arg0 >> 8) == 1) {
                                *(s16 *)((u8 *)arg0 + 4) = 0x50A;
                            } else {
                                *(s16 *)((u8 *)arg0 + 4) = 0x5FF;
                            }
                        } else {
                            if (SzDuel_InqHandPhase(*(u16 *)arg0 >> 8) == 1) {
                                *(s16 *)((u8 *)arg0 + 4) = 0xA05;
                            } else {
                                *(s16 *)((u8 *)arg0 + 4) = 0x5FF;
                            }
                        }
                    }
                } else {
                    type = SzDuel_GetUnitKind(card >> 8, low) >> 5;
                    switch (type) {
                    case 0:
                        card = *(u16 *)arg0;
                        if (TaUtil_IsExMonster(card >> 8, card & 0xFF) == 1) {
                            TaLogic014_CommandEfcMonster(arg0);
                        } else {
                            TaLogic014_CommandBtlUnit(arg0);
                        }
                        break;
                    case 2:
                        TaLogic_CommandEncUnit(arg0, 5, 0, TaLogic_GetWarnHideLvl_0014F9B0(temp_s0) & 0xFF);
                        break;
                    case 1:
                        TaLogic014_CommandSpellUnit(arg0);
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

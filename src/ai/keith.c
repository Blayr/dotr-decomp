/* Computer AI of Keith (duelist 4, duelistController04). */

#include "common.h"
#pragma conditional_move off

/* This duelist's move: picks the next unit to act, gives it a task and turns that into input `pInput`; returns 1
   when it set one. */
s32 TaLogic_Keith_GetMinimumTask(void *pCtl, void *pInput, s32 wCursorPos) {
    UnitTask *tasks = pCtl;
    s32 side;
    s32 found;
    s32 result;
    s32 index;

    side = SzDuel_GetTurnOwner();
    found = 0;
    if ((result = TaLogic_Keith_GetNextActiveUnit(tasks, side, (s32)pInput)) < 0) {
        return 0;
    }
    index = TaLogic_GetActionUnitFromOwnerID(tasks, result & 0xFFFF);
    if (index < 0) {
        return 0;
    }
    if ((result >> 16) == 1) {
        if (((tasks[index].mission >> 8) & 0xFF) == TASK_SUMMON) {
            TaLogic_InitRogicControl(&tasks[index], 1);
        } else {
            TaLogic_InitRogicControl(&tasks[index], 0);
        }
        return 1;
    }
    TaLogic_Keith_CommandUnit(&tasks[index]);
    switch ((tasks[index].mission >> 8) & 0xFF) {
    case TASK_RUN:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            TaLogic_Keith_GetMinimumTask_RunMission(&tasks[index], side, pInput, 1);
            found = 1;
        }
        break;
    case TASK_ATTACK:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            if (TaLogic_Keith_GetMinimumTask_AtkMission(&tasks[index], side, pInput, 1) < 0) {
                TaLogic004_InitRogicControl(&tasks[index], 1);
                return 1;
            }
            found = 1;
        }
        break;
    case TASK_SUMMON:
        if (TaLogic_Keith_GetMinimumTask_Summon(tasks[index].ownerId, side, (s32)pInput) < 0) {
            TaLogic004_InitRogicControl(&tasks[index], 1);
            *(u8 *)((u8 *)pInput + 2) = 0xFF;
            *(s32 *)((u8 *)pInput + 0xC) = 0;
        } else {
            TaLogic004_InitRogicControl(&tasks[index], 1);
            found = 1;
        }
        break;
    case TASK_TRAP:
        TaLogic_Keith_GetMinimumTask_TrapMission(&tasks[index], side, pInput, 1);
        found = 1;
        break;
    case TASK_MOVETOLOCATION:
    case 15:
    case 16:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            TaLogic_Keith_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 1, 0);
            found = 1;
        }
        break;
    case TASK_CONFIRMUNIT:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            TaLogic_Keith_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 1, 1);
            found = 1;
        }
        break;
    case TASK_ENCHANT:
        TaLogic_GetMinimumTask_EncMission(&tasks[index], side, pInput, 1, 0, TaLogic_Keith_GetWarnHideLvl(side), 4, 1);
        found = 1;
        break;
    case TASK_DO_NOTHING:
        TaLogic_GetMinimumTask_DoNone(&tasks[index], side, pInput);
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

    switch (tasks[index].mission & 0xFF) {
    case 5:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            TaLogic_Keith_GetMinimumTask_RunMission(&tasks[index], side, pInput, 0);
            found = 1;
        }
        break;
    case 2:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            if (TaLogic_Keith_GetMinimumTask_AtkMission(&tasks[index], side, pInput, 0) < 0) {
                TaLogic_Keith_GetMinimumTask_RunMission(&tasks[index], side, pInput, 0);
            }
            found = 1;
        }
        break;
    case 10:
        if (TaLogic_Keith_GetMinimumTask_Summon(tasks[index].ownerId, side, (s32)pInput) < 0) {
            TaLogic_InitRogicControl(&tasks[index], 0);
            *(u8 *)((u8 *)pInput + 2) = 0xFF;
            found = 1;
            *(s32 *)((u8 *)pInput + 0xC) = 0;
        } else {
            TaLogic_InitRogicControl(&tasks[index], 0);
            found = 1;
        }
        break;
    case 6:
    case 15:
    case 16:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            TaLogic_Keith_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 0, 0);
            found = 1;
        }
        break;
    case 3:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            TaLogic_Keith_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 0, 1);
            found = 1;
        }
        break;
    case 14:
        TaLogic_GetMinimumTask_DoNone(&tasks[index], side, pInput);
        found = 1;
        break;
    case 9:
        TaLogic_GetMinimumTask_EncMission(&tasks[index], side, pInput, 0, 0, TaLogic_Keith_GetWarnHideLvl(side), 4, 1);
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
s32 TaLogic_Keith_CommandUnit(UnitTask *pCtl) {
    s32 result;

    result = Ta_IsUnitControl(pCtl->ownerId >> 8, pCtl->ownerId & 0xFF);
    if (SzDuel_GetUnit(pCtl->ownerId >> 8, pCtl->ownerId & 0xFF) != 0) {
        if (SzDuel_GetUnitStatus(pCtl->ownerId >> 8, pCtl->ownerId & 0xFF, 0) == 0) {
            if (pCtl->ownerId != 0xFFFF) {
                if ((pCtl->ownerId & 0xFF) == 0) {
                    if ((s32)pCtl->goal.dwGoal == -1) {
                        if (TaLogic_IsAttackedNow(pCtl->ownerId >> 8, pCtl->ownerId & 0xFF, 0) == 1) {
                            if (SzDuel_InqHandPhase(pCtl->ownerId >> 8) == 1) {
                                pCtl->mission = 0x50A;
                            } else {
                                pCtl->mission = 0x5FF;
                            }
                        } else {
                            if (SzDuel_InqHandPhase(pCtl->ownerId >> 8) == 1) {
                                pCtl->mission = 0xA05;
                            } else {
                                pCtl->mission = 0xFF05;
                            }
                        }
                    }
                } else {
                    s32 subtype = SzDuel_GetUnitKind(pCtl->ownerId >> 8, pCtl->ownerId & 0xFF) >> 5;

                    switch (subtype) {
                    case 0:
                        if (TaUtil_IsExMonster(pCtl->ownerId >> 8, pCtl->ownerId & 0xFF) == 1) {
                            TaLogic_Keith_CommandEfcMonster(pCtl, 1);
                        } else {
                            TaLogic_Keith_CommandBtlUnit(pCtl, 1);
                        }
                        break;
                    case 3:
                        TaLogic_Keith_CommandTrapUnit(pCtl);
                        break;
                    case 4:
                    case 5:
                        pCtl->mission = 0x5FF;
                        break;
                    case 2:
                        TaLogic_CommandEncUnit(pCtl, 4, 0, (u8)TaLogic_Keith_GetWarnHideLvl(result));
                        break;
                    default:
                        pCtl->mission = 0x5FF;
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
s32 TaLogic_Keith_GetNextActiveUnit(u16 *pCtl, s32 nSide, s32 pInput) {
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
    TaLogic_Keith_CommandUnit(pCtl + idx * 8);
    if (((pCtl[idx * 8 + 2] >> 8) & 0xFF) == 10) {
        if (SzDuel_InqHandPhase(nSide) == 1 && TaLogic_Keith_GetMinimumTask_Summon(pos, nSide, pInput) >= 0) {
            return pos | 0x10000;
        }
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_GetUnitStatus(nSide, 0, 0) == 0) {
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_InqHandPhase(nSide) == 1 && TaLogic_Keith_GetMinimumTask_Summon(pos, nSide, pInput) >= 0) {
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
} Entry_0011D110;

typedef struct {
    u16 card;
    u8 flag;
    u8 pad;
} Slot_0011D110;

/* Orders a fighting unit (task `pTask`): straight at the enemy leader when `fGoalFirst` and the path is open,
   else at the nearest enemy it can beat. */
void TaLogic_Keith_CommandBtlUnit(void *pTask, s32 fGoalFirst) {
    extern void TaLogic_InitIgnoreLst();
    extern s32 TaLogic_IsRootOpen();
    extern s32 TaLogic004_GetNearUnit();
    Entry_0011D110 *entry = pTask;
    s32 side;
    s32 player;
    s32 other;
    s32 pos;
    s32 otherPos;
    s32 i;
    u8 work[0x70];
    Slot_0011D110 list[22];
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
                              other >> 8, other & 0xFF, otherPos & 0xFF, otherPos >> 8, 4) > 0) {
                entry->state = 0x2FF;
                entry->data.word = (other << 16) | entry->data.halves.low;
                return;
            }
        }
        countB = 0;
        countA = 0;
        i = 1;
        while (1) {
            switch (TaLogic004_GetNearUnit(entry, 0, player, pos & 0xFF, pos >> 8,
                                  Ta_GetCurrentSide(entry->unitId >> 8, entry->unitId & 0xFF) == 0 ? 1 : 0,
                                  i & 0xFF, TaLogic_Keith_GetWarnHideLvl(side), list, 0, &countA, &countB, 4, work)) {
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
            if (i > 4) {
                break;
            }
        }
        TaLogic004_CommandAtkLineUnit(entry);
    }
}

/* TaLogic_GetNearUnit with this duelist's view and strength settings. */
s32 TaLogic004_GetNearUnit(s32 pTask, s32 pTree, s32 pVarInfo, s32 nX, s32 nZ, s32 eSide, s32 bDist, s32 WarnLvl, s32 nUnitLst, u16 wUnitNum, s32 wSize, s32 wNodeCount, u8 bChase, s32 wIgnoreLst) {
    return TaLogic_GetNearUnit(pTask, pTree, pVarInfo, nX, nZ, eSide, bDist, WarnLvl,
                  nUnitLst, wUnitNum, wSize, wNodeCount, bChase,
                  0, 1500, wIgnoreLst);
}

typedef struct {
    u16 unitId; /* (side << 8) | unit */
    u16 pad2;
    u16 state;
    u16 pad6;
    u32 value;
} Entry_0011D3E0;

/* Orders a unit (task `pTask`) along this duelist's attack line. */
void TaLogic004_CommandAtkLineUnit(void *pTask) {
    Entry_0011D3E0 *entry = pTask;
    s32 value;
    s32 index[2];
    s32 state;
    u16 unitId;

    SzDuel_GetTurnOwner();
    unitId = entry->unitId;
    value = SzDuel_GetUnitLoc((s32) unitId >> 8, unitId & 0xFF);
    unitId = entry->unitId;
    if (TaLogic004_IsUnitOnLine((s32) unitId >> 8, unitId & 0xFF) < 0) {
        unitId = entry->unitId;
        TaLogic004_GetNearAtkLineEdge(SzDuel_GetUnit((s32) unitId >> 8, unitId & 0xFF), value & 0xFF, value >> 8, index);
        if (index[0] >= 0) {
            entry->state = 0x6FF;
            entry->value = (index[0] << 16) | (entry->value & 0xFFFF);
        } else {
            entry->state = 0x5FF;
        }
    } else {
        state = ((s32) entry->state >> 8) & 0xFF;
        if (state != 0xF && state != 0x10) {
            entry->state = (((value >> 8) < 4 ? 0xF : 0x10) << 8) | 0xFF;
            entry->value = *(u16 *)&entry->value | 0xFFFF0000;
        }
    }
}

typedef struct Pick_0011D4E0 {
    s32 value;
    u8 score;
} Pick_0011D4E0;

typedef struct Nibbles_0011D4E0 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_0011D4E0;

/* Tries square `value` as a goal: keeps it in `pick` when the path is shorter than the best so far. */
static inline void try_0011D4E0(s32 pVarInfo, s32 nX, s32 nZ, Pick_0011D4E0 *pick, Nibbles_0011D4E0 *entries, s32 value) {
    extern s32 TaLogic_GetRoot2(s32, s32, s32, s32, s32, s32, u16, u8);
    s32 score;
    s32 cost;

    score = SzDuel_GetMapUnitID(value & 0xFF, value >> 8);
    if (score < 0) {
        score = 0xFFFF;
    }
    cost = TaLogic_GetRoot2(pVarInfo, (s32)entries, nX, nZ, value & 0xFF, value >> 8, score, 7);
    if (cost < pick->score && cost >= 0) {
        pick->score = cost;
        pick->value = value;
    }
}

/* The nearest end of a free attack line a unit (record `pVarInfo`) on (nX, nZ) can reach, into `pPick`. */
void TaLogic004_GetNearAtkLineEdge(s32 pVarInfo, s32 nX, s32 nZ, void *pPick) {
    Nibbles_0011D4E0 entries[12];
    s32 i;
    Nibbles_0011D4E0 *entry;
    Pick_0011D4E0 *pick = pPick;

    pick->value = -1;
    pick->score = 0xFF;
    entry = entries;
    i = 0;
    do {
        entry->low = entry->high = 15;
        entry++;
        i++;
    } while (i < 12);
    i = 0;
    do {
        if (TaLogic004_IsEmptyAtkLine(0, i) == 1) {
            try_0011D4E0(pVarInfo, nX, nZ, pick, entries, TaLogic004_GetAtkLineStart(0, i));
            try_0011D4E0(pVarInfo, nX, nZ, pick, entries, TaLogic004_GetAtkLineEnd(0, i));
        }
        i++;
    } while (i < 4);
}

/* Which attack line (0..3) unit (nSide, nID) stands on, or -1. */
s32 TaLogic004_IsUnitOnLine(s32 nSide, s32 nID) {
    s32 value;

    value = SzDuel_GetUnitLoc(nSide, nID);
    switch (value & 0xFF) {
    case 0:
        value >>= 8;
        if ((value >= 0) && (value < 7)) {
            return 3;
        }
        break;
    case 2:
        value >>= 8;
        if ((value > 1) && (value < 5)) {
            return 0;
        }
        break;
    case 4:
        value >>= 8;
        if ((value > 1) && (value < 5)) {
            return 1;
        }
        break;
    case 6:
        value >>= 8;
        if ((value >= 0) && (value < 7)) {
            return 4;
        }
        break;
    }
    return -1;
}

/* Whether attack line `nLine` (0..3) of side `nSide` is free of enemy monsters. */
s32 TaLogic004_IsEmptyAtkLine(s32 nSide, u8 nLine) {
    s32 row;
    s32 column;
    s32 last_column;
    s32 low;
    s32 high;
    s32 value;

    switch (nLine) {
    case 0:
        column = 2;
        last_column = 4;
        row = 2;
        break;
    case 1:
        column = 2;
        row = 4;
        last_column = 4;
        break;
    case 2:
        column = 1;
        last_column = 5;
        row = 0;
        break;
    case 3:
    default:
        row = 6;
        column = 1;
        last_column = 5;
        break;
    }
    for (; column <= last_column; column++) {
        value = SzDuel_GetMapUnitID(row, column);
        if (value >= 0) {
            high = value >> 8;
            low = value & 0xFF;
            if ((nSide == Ta_IsUnitControl(high, low)) &&
                ((SzDuel_GetUnitKind(high, low) >> 5) == 0)) {
                return 0;
            }
        }
    }
    return 1;
}

/* The start square of attack line `nLine`. */
s32 TaLogic004_GetAtkLineStart(s32 nSide, s32 nLine) {
    s32 result;

    switch (nLine) {
    case 0:
        result = 0x204;
        break;
    case 1:
        result = 0x202;
        break;
    case 2:
        result = 0;
        break;
    default:
    case 3:
        result = 6;
        break;
    }

    return result;
}

/* The end square of attack line `nLine`. */
s32 TaLogic004_GetAtkLineEnd(s32 nSide, s32 nLine) {
    switch (nLine) {
    case 0:
        return 0x402;
    case 1:
        return 0x404;
    case 2:
        return 0x600;
    default:
    case 3:
        return 0x606;
    }
}

typedef struct Data_0011D9B0 {
    u16 position;
    u16 unk2;
    u16 state;
    u16 unk6;
    u32 details;
} Data_0011D9B0;

typedef struct Entry_0011D9B0 {
    u16 id;
    u8 kind;
    u8 padding;
} Entry_0011D9B0;

/* Orders an effect monster (task `pTask`): where its effect does most (`fGoalFirst`: try its goal first). */
void TaLogic_Keith_CommandEfcMonster(void *pTask, s32 fGoalFirst) {
    u8 context[112];
    Entry_0011D9B0 entries[23];
    s16 count;
    s16 total;
    s32 card;
    s32 position;
    s32 available;
    s32 row;
    s32 column;
    s32 attempt;
    Data_0011D9B0 *data = pTask;
    s32 i;
    Entry_0011D9B0 *entry;
    s32 type;
    s32 result;
    u16 packed;
    extern void TaLogic_InitIgnoreLst();
    extern s32 SzDuel_GetUnitCardNo();
    extern s32 TaLogic_GetNearUnit();

    packed = data->position;
    if ((available = SzDuel_GetUnit((s32) packed >> 8, packed & 0xFF)) != 0) {
        packed = data->position;
        card = Ta_GetCurrentSide((s32) packed >> 8, packed & 0xFF);
        packed = data->position;
        position = SzDuel_GetUnitLoc((s32) packed >> 8, packed & 0xFF);
        entry = entries;
        total = 0;
        count = 0;
        i = 0;
        do {
            i++;
            entry->id = 0xFFFF;
            entry->kind = 0xFF;
            entry++;
        } while (i < 22);
        TaLogic_InitIgnoreLst(context);
        packed = data->position;
        type = SzDuel_GetUnitCardNo((s32) packed >> 8, packed & 0xFF);
        if (type != 0x1FD) {
            attempt = 1;
            switch (type) {
            case 0x1F0:
            case 0x1FE:
                row = position >> 8;
                column = position & 0xFF;
                while (1) {
                    result = TaLogic_GetNearUnit(data, 0, available, column, row,
                        card == 0 ? 1 : 0, (u8) attempt, TaLogic_Keith_GetWarnHideLvl(card), entries, 0,
                        &count, &total, 2, 0, 1500, context);
                    switch (result) {
                    case 3:
                    case 2:
                        data->state = 0x3FF;
                        data->details = (position << 16) | (data->details & 0xFFFF);
                        return;
                    case 1:
                        return;
                    case 0:
                        data->state = 0x3FF;
                        data->details = (position << 16) | (data->details & 0xFFFF);
                        return;
                    }
                    attempt++;
                    if (attempt > 2) {
                        break;
                    }
                }
                if (Ta_GetUnitNumFrom22bitFlagList(SearchUnitByRange(0, 0, card, 1, 14, 14)) > 3) {
                    data->state = 0x3FF;
                    data->details = (position << 16) | (data->details & 0xFFFF);
                    return;
                }
                break;
            }
        } else {
            if (TaLogic_CommandGunnerUnit(data, 0) == 1) {
                data->state = 0xBFF;
                return;
            }
        }
        TaLogic_Keith_CommandBtlUnit(data, 0);
    }
}

typedef struct {
    u16 position;
    u8 flag;
    u8 pad;
} Slot_0011DC00;

/* Orders a trap card (task `pTask`): where to set it. */
void TaLogic_Keith_CommandTrapUnit(void *pTask) {
    u8 work[112];
    Slot_0011DC00 slots[22];
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
        for (i = 1; i < 4; i++) {
            state = TaLogic_GetNearUnitL2(state, owner, position & 0xFF, position >> 8,
                                  Ta_GetCurrentSide((s32) record[0] >> 8, record[0] & 0xFF) == 0 ? 1 : 0, (u8) i, 0,
                                  TaLogic_Keith_GetWarnHideLvl(player), slots, &a, &c, &b, work);
            result = TaLogic_GetTrapNearCard((s32) record[0] >> 8, record[0] & 0xFF, position & 0xFF, position >> 8,
                                   slots, 4, 0x1F, 1, 2, 0, TaLogic_Keith_GetWarnHideLvl(player), a, 1);
            if (result >= 0) {
                *(u32 *) (record + 4) = (result << 16) | record[4];
                return;
            }
            result = TaLogic_GetTrapNearCard((s32) record[0] >> 8, record[0] & 0xFF, position & 0xFF, position >> 8,
                                   slots, 4, 0x1F, 0, 2, 0, TaLogic_Keith_GetWarnHideLvl(player), a, 1);
            if (result >= 0) {
                *(u32 *) (record + 4) = (result << 16) | record[4];
                return;
            }
        }
        a = 0;
        b = 0;
        c = 0;
        state = 0;
        for (i = 1; i < 4; i++) {
            state = TaLogic_GetNearUnitL2(state, owner, position & 0xFF, position >> 8,
                                  Ta_GetCurrentSide((s32) record[0] >> 8, record[0] & 0xFF), (u8) i, 0,
                                  TaLogic_Keith_GetWarnHideLvl(player), slots, &a, &c, &b, work);
            result = TaLogic_GetFollowNearUnit(position & 0xFF, position >> 8, slots, 4, 0x22, 2, 2, a);
            if (result >= 0) {
                *(u32 *) (record + 4) = (result << 16) | record[4];
                return;
            }
            result = TaLogic_GetFollowNearUnit(position & 0xFF, position >> 8, slots, 4, 0x1F, 1, 2, a);
            if (result >= 0) {
                *(u32 *) (record + 4) = (result << 16) | record[4];
                return;
            }
            result = TaLogic_GetFollowNearUnit(position & 0xFF, position >> 8, slots, 4, 0x1F, 0, 2, a);
            if (result >= 0) {
                *(u32 *) (record + 4) = (result << 16) | record[4];
                return;
            }
        }
        record[2] = 0x5FF;
    }
}

typedef struct {
    s16 card;
    u8 f2;
    u8 pad3;
    s16 f4;
    u8 pad6[6];
    s32 fC;
} Act_0011DFB0;

typedef struct {
    u8 pad0[0x3C];
    u16 id;
    u8 pad3E[0x22];
} Card_0011DFB0;

/* The summon task for side `nSide`: which hand cards to play and where, into `pInput`; -1 when it plays none. */
s32 TaLogic_Keith_GetMinimumTask_Summon(s32 wUnit, s32 nSide, s32 pInput) {
    extern s32 TaLogic_GetUnitNum(s32, s32);
    Act_0011DFB0 *act = (Act_0011DFB0 *)pInput;
    Card_0011DFB0 buf;
    s32 res;
    s32 card;
    s32 type;
    s32 r;

    act->card = wUnit;
    if (SzDuel_InqHandPhase(nSide) == 0) {
        return -1;
    }
    if (TaLogic_GetUnitNum(nSide, 0) == 5 && TaLogic_GetUnitNum(nSide, 1) == 5) {
        return -1;
    }
    type = TaLogic_Keith_IsHandPlay(nSide, &buf);
    if (type < 0) {
        return -1;
    }
    act->f2 = 10;
    act->fC = 0;
    card = SzDuel_GetUnitLoc(wUnit >> 8, wUnit & 0xFF);
    if (type == 0) {
        if (TaLogic_Keith_SetComboQue(nSide, (u8 *)act, &buf) >= 0) {
            res = TaLogic_GetNearCard2(&buf, card & 0xFF, card >> 8, nSide == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, TaLogic_Keith_GetWarnHideLvl(nSide));
            if (res < 0) {
                if (SzDuel_GetUnitMonsterCount(nSide) < 4) {
                    r = TaLogic004_GetSummonPiece(nSide, type, &buf);
                    if (r < 0) {
                        return -1;
                    }
                    act->f4 = r;
                    return 1;
                }
            } else {
                r = TaLogic004_GetSummonPiece(nSide, type, &buf);
                if (r < 0) {
                    return -1;
                }
                act->f4 = r;
                return 1;
            }
        }
    } else {
        res = TaLogic_GetNearCard2(&buf, card & 0xFF, card >> 8, nSide == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, TaLogic_Keith_GetWarnHideLvl(nSide));
    }
    if (type == 2) {
        TaLogic_Keith_SetSpecialComboQue(nSide, pInput, (s32)&buf, 0);
        r = TaLogic004_GetSummonPiece(nSide, type, &buf);
        if (r < 0) {
            return -1;
        }
        act->f4 = r;
        return 1;
    } else if (type == 3) {
        TaLogic_Keith_SetSpecialComboQue(nSide, pInput, (s32)&buf, 1);
        r = TaLogic004_GetSummonPiece(nSide, type, &buf);
        if (r < 0) {
            return -1;
        }
        act->f4 = r;
        return 1;
    } else {
        if (TaLogic004_GetSpellPlay(nSide, (u8 *)act, &buf, buf.id) < 0) {
            return -1;
        }
        r = TaLogic004_GetSummonPiece(nSide, type, &buf);
        if (r < 0) {
            return -1;
        }
        act->f4 = r;
        return 1;
    }
}

typedef struct Nibbles_0011E270 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_0011E270;

/* The square side `nSide` summons a card of kind `sKind` to. */
s32 TaLogic004_GetSummonPiece(s32 nSide, u8 sKind, void *pInput) {
    s32 bestLocation;
    s32 bestCost;
    Nibbles_0011E270 buffer[12];
    u8 result[8];
    s32 initIndex;
    Nibbles_0011E270 *p;

    extern s32 TaLogic_Keith_GetSommonPiecePreference();
    extern s32 TaLogic_IsUnitWin4();
    extern s32 TaLogic_GetInvadeRoot2();
    extern s32 TaLogic_GetRoot2(s32, s32, s32, s32, s32, s32, u16, u8);

    if (pInput == NULL) {
        return -1;
    }
    p = buffer;
    initIndex = 0;
    do {
        p->low = p->high = 0xF;
        initIndex++;
        p++;
    } while (initIndex < 12);

    if (!((u8)(*((u8 *)pInput + 0x3E) >> 5))) {
        s32 candidate;
        s32 target;
        s32 y;
        s32 x;
        s32 index;
        s32 destY;
        s32 destX;
        s32 cost;
        s32 location;
        location = SzDuel_GetUnitLoc(nSide, 0);
        target = TaLogic_GetNearCard2(pInput, location & 0xFF, location >> 8,
            nSide == 0 ? 1 : 0, 4, 31, 2, 2, 0, TaLogic_Keith_GetWarnHideLvl(nSide));
        if (target >= 0) {
            bestCost = 255;
            bestLocation = 65535;
            location = SzDuel_GetUnitLoc(target >> 8, target & 0xFF);
            index = 0;
            destY = location >> 8;
            destX = location & 0xFF;
            do {
                if ((candidate = TaLogic_Keith_GetSommonPiecePreference(nSide, index)) >= 0) {
                    x = candidate & 0xFF;
                    y = candidate >> 8;
                    if (SzDuel_GetField(x, y) != 8 &&
                        (SzDuel_GetField(x, y) != 9 || Ta_IsVirus_Chk3(pInput, x, y) != 1) &&
                        SzDuel_GetMapUnit(x, y) == 0) {
                        if (TaLogic_IsUnitWin4(pInput, target, TaLogic_Keith_GetWarnHideLvl(nSide), destX, destY, 0) > 0) {
                            cost = TaLogic_GetInvadeRoot2(pInput, buffer, x, y, destX, destY,
                                target, 0, 4, (u16)TaLogic_Keith_GetWarnHideLvl(nSide));
                        } else {
                            cost = TaLogic_GetRoot2((s32)pInput, (s32)buffer, x, y, destX, destY,
                                target, 4);
                        }
                        if (TaLogic_GetMinGoalCount((u8 *)buffer) > 0 && cost < bestCost) {
                            bestCost = cost;
                            bestLocation = candidate;
                        }
                    }
                }
                index++;
            } while (index < 8);
            if (bestLocation != 65535) {
                return bestLocation;
            }
            bestLocation = -1;
            return bestLocation;
        }
        {
        s32 y;
        s32 x;
        s32 fallbackIndex;
        s32 limit;
        s32 candidate;
        s32 fallback;
        limit = 14;
        fallback = -1;
        fallbackIndex = 0;
        do {
            if ((candidate = TaLogic_Keith_GetSommonPiecePreference(nSide, fallbackIndex)) >= 0) {
                x = candidate & 0xFF;
                y = candidate >> 8;
                if (SzDuel_GetField(x, y) != 8 &&
                    (SzDuel_GetField(x, y) != 9 || Ta_IsVirus_Chk3(pInput, x, y) != 1) &&
                    SzDuel_GetMapUnitID(x, y) < 0) {
                    TaLogic004_GetNearAtkLineEdge((s32)pInput, x, y, (s32 *)result);
                    if ((s32)result[4] < limit && (s32)result[4] >= 0) {
                        fallback = candidate;
                        limit = (s32)result[4];
                    }
                }
            }
            fallbackIndex++;
        } while (fallbackIndex < 8);
        if (limit < 14) {
            return fallback;
        }
        }
    } else {
    s32 y;
    s32 x;
    s32 specialIndex;
    s32 best;
    s32 candidate;
    best = -1;
    specialIndex = 0;
    do {
        if ((candidate = TaLogic_Keith_GetSommonPiecePreference(nSide, specialIndex)) >= 0) {
            x = candidate & 0xFF;
            y = candidate >> 8;
            if (SzDuel_GetField(x, y) != 8 &&
                (SzDuel_GetField(x, y) != 9 || Ta_IsVirus_Chk3(pInput, x, y) != 1) &&
                SzDuel_GetMapUnitID(x, y) < 0 && y < 8) {
                best = candidate;
            }
        }
        specialIndex++;
    } while (specialIndex < 8);
    if (best >= 0) {
        return best;
    }
    }
    return -1;
}

/* Whether side `nSide` should play from its hand this turn (and what, into `pInput`). */
s32 TaLogic_Keith_IsHandPlay(s32 nSide, void *pInput) {
    s32 cards[8];
    u8 scratch[32];
    s32 count;
    s32 index;
    s32 result;
    u8 status0;
    u8 status1;
    extern s32 TaLogic_GetUnitNum();
    extern s32 SzDuel_GetUnitCardNo();
    extern s32 TaLogic004_GetSpecialComboPlay();

    status0 = TaLogic_GetUnitNum(nSide, 0);
    status1 = TaLogic_GetUnitNum(nSide, 1);
    count = 0;
    if (pInput == NULL) {
        return -1;
    }
    TaHand_GetNextHand(nSide, cards);
    if (status0 == 5) {
        if (TaLogic004_GetSpellPlay(nSide, scratch, pInput, 999) >= 0) {
            return 1;
        }
        return -1;
    }
    if (status1 == 5) {
        if (count < TaHand_GetNextHandNum(nSide)) {
            s32 *card = cards;
            do {
                if ((TaHand_GetCardKind(*card) >> 5) == 0 &&
                    TaHand_CanAffordSummonCost(nSide, *card) == 1) {
                    SzDuel_InitCardInfo(pInput, cards[count]);
                    return 0;
                }
                card++;
                count++;
            } while (count < TaHand_GetNextHandNum(nSide));
        }
        return -1;
    }
    if (TaLogic004_GetSpecialComboPlay(nSide, scratch, pInput, 0) >= 0) {
        return 2;
    }
    index = 1;
    do {
        if ((SzDuel_GetUnitKind(nSide, index) & 0x1F) == 14 &&
            nSide == Ta_IsUnitControl(nSide, index)) {
            count = (u8)(count + 1);
        }
        if ((SzDuel_GetUnitKind(nSide == 0 ? 1 : 0, index) & 0x1F) == 14 &&
            nSide == Ta_IsUnitControl(nSide == 0 ? 1 : 0, index)) {
            count = (u8)(count + 1);
        }
        index++;
    } while (index < 5);
    if ((u8)count >= 3) {
        if (TaLogic004_GetSpecialComboPlay(nSide, scratch, pInput, 1) >= 0) {
            return 3;
        }
        result = TaLogic004_GetSpellPlay(nSide, scratch, pInput, 0x2E2);
        if (result >= 0) {
            return result;
        }
    }
    if ((result = TaLogic004_GetSpellPlay(nSide, scratch, pInput, 0x337)) >= 0) {
        index = 1;
        count = 0;
        do {
            if (nSide == Ta_IsUnitControl(nSide, index)) {
                if (SzDuel_GetUnitCardNo(nSide, index) == 0x337) {
                    index = 11;
                    count = 0;
                }
            } else if (SzDuel_GetUnitStatus(nSide, index, 4) == 0) {
                count = (u8)(count + 1);
            }
            if (nSide != Ta_IsUnitControl(nSide == 0 ? 1 : 0, index)) {
                if (SzDuel_GetUnitCardNo(nSide == 0 ? 1 : 0, index) == 0x337) {
                    index = 11;
                    count = 0;
                }
            } else if (SzDuel_GetUnitStatus(nSide == 0 ? 1 : 0, index, 4) == 0) {
                count = (u8)(count + 1);
            }
            index++;
        } while (index < 11);
        if ((u8)count >= 6) {
            return result;
        }
    }
    {
        s32 *card;
        s32 i = 0;
        if (i < TaHand_GetNextHandNum(nSide)) {
            card = cards;
            do {
                if ((TaHand_GetCardKind(*card) >> 5) == 0 &&
                    TaHand_CanAffordSummonCost(nSide, *card) == 1 && *card != 0x156) {
                    SzDuel_InitCardInfo(pInput, cards[i]);
                    return 0;
                }
                card++;
                i++;
            } while (i < TaHand_GetNextHandNum(nSide));
        }
    }
    result = TaLogic004_GetSpellPlay(nSide, scratch, pInput, 999);
    if (result >= 0) {
        return result;
    }
    return -1;
}

/* Whether side `nSide` can play this duelist's special combination now. */
s32 TaLogic004_GetSpecialComboPlay(s32 nSide, s32 bCombo, s32 pCardInfo, s32 nMode) {
    s32 values[8];
    s32 i;
    s32 found;
    s32 *firstPtr;
    s32 *scanPtr;
    s32 *modePtr;

    found = 0;
    TaHand_GetNextHand(nSide, values);
    switch (nMode & 0xFF) {
    case 0:
        i = 0;
        if (0 < TaHand_GetNextHandNum(nSide)) {
            firstPtr = values;
            do {
                if (*firstPtr == 0x31F) {
                    found = 1;
                    ((u8 *)bCombo)[6] = i;
                }
                firstPtr++;
                i++;
            } while (i < TaHand_GetNextHandNum(nSide));
        }
        if (found == 1) {
            found = 0;
            if (0 < TaHand_GetNextHandNum(nSide)) {
                scanPtr = values;
                do {
                    if (((TaHand_GetCardKind(*scanPtr) >> 5) == 0) &&
                        (Ta_GetHandEnchant(*scanPtr, 0x31F) >= 0) &&
                        (TaHand_CanAffordSummonCost(nSide, *scanPtr) == 1) &&
                        (*scanPtr != 0x31B) && (*scanPtr != 0x31C)) {
                        ((u8 *)bCombo)[7] = found;
                        SzDuel_InitCardInfo((void *)pCardInfo, values[found]);
                        return TaHand_GetCardKind(values[found]) >> 5;
                    }
                    scanPtr++;
                    found++;
                } while (found < TaHand_GetNextHandNum(nSide));
            }
        }
        break;
    case 1:
        if (0 < TaHand_GetNextHandNum(nSide)) {
            found = 0;
            modePtr = values;
            do {
                if ((*modePtr == 0x202) && (TaHand_CanAffordSummonCost(nSide, *modePtr) == 1)) {
                    ((u8 *)bCombo)[6] = found;
                    SzDuel_InitCardInfo((void *)pCardInfo, values[found]);
                    return TaHand_GetCardKind(values[found]) >> 5;
                }
                modePtr++;
                found++;
            } while (found < TaHand_GetNextHandNum(nSide));
        }
        break;
    default:
        break;
    }
    return -1;
}

/* Whether side `nSide` plays a magic or ritual card from its hand now (its slot into `bCombo`, the card into
   `pCardInfo`). */
s32 TaLogic004_GetSpellPlay(s32 nSide, u8 *bCombo, void *pCardInfo, s32 nMode) {
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
        if ((TaHand_GetCardKind(buf[i]) >> 5) != 0 && buf[i] != 0x31F) {
            bCombo[6] = i;
            SzDuel_InitCardInfo(pCardInfo, buf[i]);
            return 1;
        }
    }
    return -1;
}

typedef struct Info_0011EF60 {
    u8 pad00[8];
    u16 x;
    s16 y;
} Info_0011EF60;

typedef struct Sprite_0011EF60 {
    Info_0011EF60 *info;
    u8 pad04[0x34];
    s16 x;
    s16 y;
} Sprite_0011EF60;

/* Fills hand combination `bCombo` for side `nSide`: the best fusion or equip chain, its card into `pCardInfo`. */
s32 TaLogic_Keith_SetComboQue(s32 nSide, u8 *bCombo, void *pCardInfo) {
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
                if ((TaHand_GetCardKind(card) >> 5) == 0 && card != 0x156) {
                    *node = TaLogic_GetFusionTree(nSide, (struct TreeTag *)*node, i & 0xFF, card & 0xFFFF, 0, (u16 *)&a, (u16 *)&b);
                    *node = TaLogic_GetFusionRes(*node);
                    value = TaLogic_GetEnchantQue(nSide, *node, 0, 0);
                    if (TaHand_CanAffordSummonCost(nSide, card) == 1) {
                        if (best < value) {
                            TaLogic_Keith_ConvEmptyCombo(nSide, *node, entries);
                            TaLogic_CopyArray((u8 *)*node + 2, bCombo + 6);
                            SzDuel_InitCardInfo(pCardInfo, **node);
                            ((Sprite_0011EF60 *)pCardInfo)->x = (value >> 16) - (((Sprite_0011EF60 *)pCardInfo)->info->x & 0x1FFF);
                            ((Sprite_0011EF60 *)pCardInfo)->y = (value & 0xFFFF) - (((Sprite_0011EF60 *)pCardInfo)->info->y & 0x1FFF);
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
} Info_0011F150;

/* Fills an empty combination: the hand card side `nSide` can summon with the best attack plus defence. */
void TaLogic_Keith_ConvEmptyCombo(s32 nSide, void *pCardInfo, s32 *pResult) {
    Info_0011F150 *info = pCardInfo;
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
                if (card != 0x3E7 && TaLogic004_IsRefuseEmptyCombo(card) == 0 && level >= TaHand_GetCardSummonCost2(card, nSide)) {
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

/* Whether this duelist keeps card `nCardNo` out of a summon (it is wanted for an equip). */
s32 TaLogic004_IsRefuseEmptyCombo(s32 nCardNo) {
    if ((TaHand_GetCardKind(nCardNo) >> 5) != 0) {
        return 1;
    }
    if ((nCardNo == 0x1F0) || (nCardNo == 0x1FD) || (nCardNo == 0x1FE) ||
        (nCardNo == 0x202) || (nCardNo == 0x1F6) || (nCardNo == 0x20B)) {
        return 1;
    }
    return 0;
}

typedef struct {
    u8 pad[6];
    u8 indices[5];
} CardState_0011F3C0;

/* Fills hand combination `bCombo` for side `nSide` with this duelist's special combination, its card into
   `pCardInfo`. */
s32 TaLogic_Keith_SetSpecialComboQue(s32 nSide, s32 bCombo, s32 pCardInfo, s32 nOpt) {
    s32 cards[5];
    s32 *card;
    s32 i;
    s32 card_id;

    if (pCardInfo == 0) {
        return -1;
    }
    for (i = 0; i < 5; i++) {
        ((CardState_0011F3C0 *)(bCombo + i))->indices[0] = 0xFF;
    }
    TaHand_GetNextHand(nSide, cards);
    if ((nOpt & 0xFF) == 0) {
        TaLogic004_GetSpecialComboPlay(nSide, bCombo, pCardInfo, 0);
        i = 0;
        if (0 < TaHand_GetNextHandNum(nSide)) {
            card = cards;
            do {
                if ((i != ((CardState_0011F3C0 *)bCombo)->indices[0]) && (i != ((CardState_0011F3C0 *)bCombo)->indices[1]) && (Ta_GetHandEnchant(0x1E8, *card) >= 0) && ((TaHand_GetCardKind(*card) >> 5) == 2)) {
                    card_id = *card;
                    if ((card_id != 0x31B) && (card_id != 0x31C)) {
                        ((CardState_0011F3C0 *)bCombo)->indices[2] = i;
                    }
                }
                card++;
                i++;
            } while (i < TaHand_GetNextHandNum(nSide));
        }
    } else if ((nOpt & 0xFF) == 1) {
        TaLogic004_GetSpecialComboPlay(nSide, bCombo, pCardInfo, 0);
    }
    return 0;
}

/* Ta_GetSommonPiecePreference for this duelist. */
s32 TaLogic_Keith_GetSommonPiecePreference(s32 nSide, u32 nPr) {
    return Ta_GetSommonPiecePreference(nSide, nPr);
}

typedef struct {
    u8 low : 4;
    u8 high : 4;
} Flags_0011F540;

typedef struct {
    u16 id;
    u8 action;
    u8 pad3;
    u16 position;
    u8 pad6[6];
    s32 value;
    u8 mode;
} Output_0011F540;

/* The task of a unit running from danger (task `pTask`): the safest square in reach, into `pInput` (`fFirst` = 1
   for the unit's first-choice task). */
s32 TaLogic_Keith_GetMinimumTask_RunMission(UnitTask *pTask, s32 nSide, void *pInput, u8 fFirst) {
    extern s32 TaLogic_IsRunPassRoot(s32, s32, s32, s32, s32, s32, void *, u8);
    extern s32 TaLogic_Keith_IsOpenUnit();
    s32 position;
    u8 upperX;
    u8 flag;
    Flags_0011F540 cells[12];
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
    Output_0011F540 *out = pInput;

    position = SzDuel_GetUnitLoc(pTask->ownerId >> 8, pTask->ownerId & 0xFF);
    i = 0;
    do {
        cells[i].low = cells[i].high = 15;
        i++;
    } while (i < 12);

    {
        u16 value = (u16)TaLogic_Keith_GetWarnHideLvl(nSide);
        originalX = position & 0xFF;
        originalY = position >> 8;
        if (TaLogic_GetUnitWarning(originalX, originalY, pTask->ownerId, 3, value, 0) == 0) {
            out->id = pTask->ownerId;
            out->action = 6;
            out->position = position;
            out->mode = TaLogic_IsDefStyleUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, out->position, 1, 0);
            out->value = TaLogic_Keith_IsOpenUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, pTask);
            TaLogic004_InitRogicControl(pTask, fFirst);
            return 0;
        } else {
            result = GetMoveRange(SzDuel_GetUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF), originalX, originalY);
            if (result == 0) {
                out->id = pTask->ownerId;
                out->action = 6;
                out->position = position;
                out->mode = TaLogic_IsDefStyleUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, out->position, 1, 0);
                out->value = TaLogic_Keith_IsOpenUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, pTask);
                TaLogic004_InitRogicControl(pTask, fFirst);
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
                if ((pTask->ownerId & 0xFF) == 0) {
                    flag = TaLogic_IsAttackedNow(pTask->ownerId >> 8, pTask->ownerId & 0xFF, 0) & 0xFF;
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
                            if (TaLogic_IsRunPassRoot(pTask->ownerId >> 8, pTask->ownerId & 0xFF, originalX, originalY, x, y, pTask, flag) == 1 &&
                                (TaLogic_IsAttackedNow2(pTask->ownerId >> 8, pTask->ownerId & 0xFF, x, y, 0) == 0 || (u8)pTask->ownerId == 0)) {
                                value = (u16)TaLogic_Keith_GetWarnHideLvl(nSide);
                                score = TaLogic_GetUnitWarning(x, y, pTask->ownerId, 3, value, 0);
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
                    out->id = pTask->ownerId;
                    out->action = 6;
                    out->position = bestPosition;
                    if (bestPosition == position) {
                        out->mode = TaLogic_IsDefStyleUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, out->position, 1, 0);
                    } else {
                        out->mode = TaLogic_IsDefStyleUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, out->position, 0, 0);
                    }
                    out->value = TaLogic_Keith_IsOpenUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, pTask);
                } else {
                    out->id = pTask->ownerId;
                    out->action = 6;
                    out->position = position;
                    out->mode = TaLogic_IsDefStyleUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, out->position, 1, 0);
                    out->value = TaLogic_Keith_IsOpenUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, pTask);
                }
                TaLogic004_InitRogicControl(pTask, fFirst);
            }
        }
    }
    return 0;
}

/* How careful this duelist is about hidden cards (by its life points and monster count). */
s32 TaLogic_Keith_GetWarnHideLvl(s32 nSide) {
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

typedef struct Source_0011FAE0 {
    u16 position;
    u8 pad2[6];
    u32 targets;
} Source_0011FAE0;

typedef struct Output_0011FAE0 {
    u16 position;
    u8 mode;
    u8 pad3;
    u16 target;
    u8 pad6[6];
    s32 flag;
    u8 value;
} Output_0011FAE0;

typedef struct Position_0011FAE0 {
    u8 x : 4;
    u8 y : 4;
} Position_0011FAE0;

/* The task's target square: the second half-word when the second argument is 1, else the first. */
static inline u32 target_0011FAE0(void *arg0, u8 which) {
    Source_0011FAE0 *source = arg0;
    if (which == 1) {
        return (u16)(source->targets >> 16);
    }
    return *(u16 *)&source->targets;
}

/* The task of a unit attacking (task `pTask`): its path to the goal, into `pInput`; -1 when it has none (`fFirst`
   = 1 for the unit's first-choice task). */
s32 TaLogic_Keith_GetMinimumTask_AtkMission(void *pTask, s32 nSide, void *pInput, u8 fFirst) {
    extern s32 TaLogic_GetInvadeRoot();
    s32 sourceTarget;
    s32 count;
    s32 pathResult;
    s32 sourceY;
    s32 sourceX;
    s32 selectedFlag;
    Position_0011FAE0 positions[12];
    s32 flag;
    s32 otherTarget;
    s32 j;
    Position_0011FAE0 *walk;
    s32 object;
    u32 targetXWord;
    u32 targetYWord;
    Source_0011FAE0 *source = pTask;
    Output_0011FAE0 *output = pInput;

    targetXWord = target_0011FAE0(pTask, fFirst);
    targetYWord = target_0011FAE0(pTask, fFirst);
    if (SzDuel_GetUnit(targetYWord >> 8, targetXWord & 0xFF) == 0) {
        TaLogic_InitRogicControl(pTask, 1);
        return -1;
    }

    flag = TaLogic_Keith_IsOpenUnit(source->position >> 8, source->position & 0xFF, pTask);
    sourceTarget = SzDuel_GetUnitLoc(source->position >> 8, source->position & 0xFF);
    targetXWord = target_0011FAE0(pTask, fFirst);
    targetYWord = target_0011FAE0(pTask, fFirst);
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
    if (GetMoveRange(object, sourceX, sourceY) == 0) {
        s32 cost;
        output->position = source->position;
        output->mode = 6;
        output->target = sourceTarget;
        cost = TaLogic_GetUnitWarning(sourceX, sourceY, nSide, 3, 1,
                            (u8)TaLogic_LifePenalty(nSide));
        if (cost >= SzDuel_GetUnitAP(source->position >> 8, source->position & 0xFF, 0)) {
            output->value = TaLogic_IsDefStyleUnit(source->position >> 8, source->position & 0xFF,
                                        output->target, 1, 0);
        } else {
            output->value = TaLogic_IsDefStyleUnit(source->position >> 8, source->position & 0xFF,
                                        output->target, 0, 0);
        }
        TaLogic004_InitRogicControl(pTask, fFirst);
    } else {
        s32 targetY;
        s32 targetX;
        Position_0011FAE0 *current;
        s32 i;
        s32 bestCost;
        s32 selected;
        s32 penalty;
        u16 position;

        penalty = TaLogic_LifePenalty(nSide);
        position = source->position;
        pathResult = TaLogic_GetInvadeRoot(position >> 8, position & 0xFF, positions,
                      sourceX, sourceY, targetX = otherTarget & 0xFF,
                      targetY = otherTarget >> 8,
                      target_0011FAE0(pTask, fFirst), 0, 30, (u16)penalty);
        count = TaLogic_GetMinGoalCount((u8 *)positions);
        selected = 0xFF;
        if (count > 0) {
            selectedFlag = 0;
            bestCost = 0xFFFF;
            for (i = 0; i < count; i++) {
                s32 state = TaLogic004_IsOpenMoveUnit(source->position >> 8, source->position & 0xFF,
                                          sourceX, sourceY, targetX, targetY, pathResult);
                if (state == 1) {
                    Position_0011FAE0 *forcedPosition = &positions[i];
                    selected = i;
                    selectedFlag = 1;
                    i = count;
                    forcedPosition->x = targetX;
                    forcedPosition->y = targetY;
                } else {
                    s32 cost;
                    s32 penalty = TaLogic_LifePenalty(nSide);
                    current = &positions[i];
                    cost = TaLogic_GetUnitWarning(current->x, current->y, nSide, 4, 1,
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
            TaLogic004_InitRogicControl(pTask, fFirst);
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

typedef struct Input_00120150 {
    u16 position;
    u16 pad2;
    u32 pad4;
    union {
        u32 pair;
        u16 position;
    } target;
} Input_00120150;

typedef struct Output_00120150 {
    u16 position;
    u8 type;
    u8 pad3;
    u16 target;
    u8 pad6[10];
    u8 value;
} Output_00120150;

typedef struct Position_00120150 {
    u8 x : 4;
    u8 y : 4;
} Position_00120150;

/* The task's target square: the second half-word when the second argument is 1, else the first. */
static inline u32 target_00120150(Input_00120150 *src, u8 kind) {
    u32 target;
    if (kind == 1) {
        target = (u16)(src->target.pair >> 16);
    } else {
        target = src->target.position;
    }
    return target;
}

/* This duelist's caution about hidden cards (an inline copy of its GetWarnHideLvl: by life points and monster
   count). */
static inline s32 power_00120150(s32 card) {
    if (SzDuel_GetLP(card) > 1000) {
        if (SzDuel_GetUnitMonsterCount(card) >= 3) {
            return 500;
        } else {
            return 1000;
        }
    } else {
        return 2000;
    }
}

/* Sets a move task (action 6) to the given square, and whether the unit should stay in defence there. */
static inline void output_00120150(Input_00120150 *src, Output_00120150 *out, s32 target, s32 flag) {
    out->position = src->position;
    out->type = 6;
    out->target = target;
    out->value = TaLogic_IsDefStyleUnit(src->position >> 8, src->position & 0xFF,
                             out->target, flag, 0);
}

/* The task of setting a trap (task `pTask`), into `pInput`. */
s32 TaLogic_Keith_GetMinimumTask_TrapMission(void *pTask, s32 nSide, void *pInput, u8 fFirst) {
    extern void TaLogic_GetInvadeRoot();
    Position_00120150 positions[12];
    s32 start;
    Input_00120150 *src = pTask;
    Output_00120150 *out = pInput;
    u32 lowTarget;
    u32 highTarget;

    lowTarget = target_00120150(src, fFirst);
    highTarget = target_00120150(src, fFirst);
    if (SzDuel_GetUnit(highTarget >> 8, lowTarget & 0xFF) == 0) {
        TaLogic_InitRogicControl(src, 1);
        return -1;
    }
    start = SzDuel_GetUnitLoc(src->position >> 8, src->position & 0xFF);
    {
        Position_00120150 *p;
        s32 target;
        s32 targetY;
        s32 targetX;
        s32 startY;
        s32 startX;
        s32 count;
        s32 best;
        s32 score;
        s32 i;
        s32 value;
        s32 power;
        Position_00120150 *q;

        lowTarget = target_00120150(src, fFirst);
        highTarget = target_00120150(src, fFirst);
        target = SzDuel_GetUnitLoc(highTarget >> 8, lowTarget & 0xFF);
        if (target_00120150(src, fFirst) == 0xFFFF) {
            output_00120150(src, out, start, 1);
            return 0;
        }
        value = SzDuel_GetUnit(src->position >> 8, src->position & 0xFF);
        startX = start & 0xFF;
        startY = start >> 8;
        if (GetMoveRange(value, startX, startY) == 0 ||
            TaLogic_IsAttackedNow(src->position >> 8, src->position & 0xFF, 0) == 1) {
            output_00120150(src, out, start, 1);
            return 0;
        }
        p = positions;
        i = 0;
        q = p;
        do {
            q->x = q->y = 15;
            ++i;
            ++q;
        } while (i < 12);
        power = power_00120150(nSide);
        targetX = target & 0xFF;
        targetY = target >> 8;
        TaLogic_GetInvadeRoot(src->position >> 8, src->position & 0xFF, positions,
                     startX, startY, targetX, targetY, target_00120150(src, fFirst),
                     0, 30, (u16)power);
        count = TaLogic_GetMinGoalCount((u8 *)positions);
        best = 0xFF;
        if (count > 0) {
            score = 0;
            for (i = 0; i < count; ++i, ++p) {
                if (SzDuel_GetMapUnit(p->x, p->y) == 0) {
                    value = TaLogic_GetUnitWarning(p->x, p->y, nSide, 4, 1,
                                          (u8)power_00120150(nSide));
                    if (score < value) {
                        score = value;
                        best = i;
                    } else if (value == score) {
                        if (((targetX < p->x ? p->x : targetX) -
                             (p->x < targetX ? p->x : targetX)) +
                            ((targetY < p->y ? p->y : targetY) -
                             (p->y < targetY ? p->y : targetY)) <
                            ((targetX < positions[best].x ? positions[best].x : targetX) -
                             (positions[best].x < targetX ? positions[best].x : targetX)) +
                            ((targetY < positions[best].y ? positions[best].y : targetY) -
                             (positions[best].y < targetY ? positions[best].y : targetY))) {
                            score = value;
                            best = i;
                        }
                    }
                }
            }
        } else {
            output_00120150(src, out, start, 1);
            return 0;
        }
        if (best != 0xFF) {
            out->position = src->position;
            out->type = 6;
            out->target = (positions[best].y << 8) | positions[best].x;
            out->value = TaLogic_IsDefStyleUnit(src->position >> 8, src->position & 0xFF,
                                      out->target, 0, 0);
        } else {
            output_00120150(src, out, start, 0);
            return 0;
        }
    }
    return 0;
}

typedef struct Input_001206F0 {
    u16 position;
    u16 unk2;
    u16 command;
    u16 unk6;
    union {
        u32 word;
        u16 low;
    } targets;
} Input_001206F0;

typedef struct Output_001206F0 {
    u16 position;
    u8 action;
    u8 unk3;
    u16 destination;
    u8 unk6[6];
    s32 value;
    u8 state;
} Output_001206F0;

typedef struct Position_001206F0 {
    u8 x : 4;
    u8 y : 4;
} Position_001206F0;

#define target_001206F0(src, mode) ((mode) == 1 ? \
    (u32)(u16)((src)->targets.word >> 16) : (u32)(src)->targets.low)

/* This duelist's caution about hidden cards (an inline copy of its GetWarnHideLvl: by life points and monster
   count). */
static inline s32 option_001206F0(s32 card) {
    if (SzDuel_GetLP(card) > 1000) {
        if (SzDuel_GetUnitMonsterCount(card) >= 3) {
            return 500;
        }
        return 1000;
    }
    return 2000;
}

#define min_001206F0(a, b) ((a) < (b) ? (u8)(a) : (b))
#define max_001206F0(a, b) ((b) < (a) ? (u8)(a) : (b))
#define distance_001206F0(pos, src, mode) ( \
    (max_001206F0((pos)->x, target_001206F0(src, mode) & 0xFF) - \
     min_001206F0((pos)->x, target_001206F0(src, mode) & 0xFF)) + \
    (max_001206F0((u8)(pos)->y, target_001206F0(src, mode) >> 8) - \
     min_001206F0((u8)(pos)->y, target_001206F0(src, mode) >> 8)))

/* The task of a unit moving to its goal (task `pTask`), into `pInput` (`fFirst` = 1 for the unit's first-choice
   task). */
s32 TaLogic_Keith_GetMinimumTask_MoveMission(u32 *pTask, s32 nSide, u16 *pInput, u8 fFirst, u8 nKind) {
    extern s32 TaLogic_GetUnitWarning(s32, s32, s32, s32, s32, s32);
    extern s32 TaLogic_IsDefStyleUnit(s32, s32, s32, u8, s32);
    extern void TaLogic_GetRoot(s32, s32, void *, s32, s32, s32, s32, s32, u8);
    Position_001206F0 positions[12];
    s32 y;
    s32 bestScore;
    s32 mode;
    s32 current;
    s32 command;

    current = SzDuel_GetUnitLoc(((Input_001206F0 *)pTask)->position >> 8, ((Input_001206F0 *)pTask)->position & 0xFF);
    mode = fFirst;
    if (target_001206F0((Input_001206F0 *)pTask, mode) == 0xFFFF && current == target_001206F0((Input_001206F0 *)pTask, mode)) {
        pInput[0] = ((Input_001206F0 *)pTask)->position;
        ((Output_001206F0 *)pInput)->action = 6;
        pInput[2] = current;
        ((Output_001206F0 *)pInput)->state = TaLogic_IsDefStyleUnit(((Input_001206F0 *)pTask)->position >> 8, ((Input_001206F0 *)pTask)->position & 0xFF,
            pInput[2], nKind, 0);
        ((Output_001206F0 *)pInput)->value = TaLogic_Keith_IsOpenUnit(((Input_001206F0 *)pTask)->position >> 8, ((Input_001206F0 *)pTask)->position & 0xFF, pTask);
        TaLogic004_InitRogicControl(pTask, fFirst);
        return 0;
    } else {
        command = (((Input_001206F0 *)pTask)->command >> 8) & 0xFF;
        if (command == 15) {
            s32 x = current & 0xFF;
            s32 target;

            y = current >> 8;
            pInput[0] = ((Input_001206F0 *)pTask)->position;
            ((Output_001206F0 *)pInput)->action = 6;
            target = x | (GetCap(7, y +
                (GetMoveRange(SzDuel_GetUnit(((Input_001206F0 *)pTask)->position >> 8, ((Input_001206F0 *)pTask)->position & 0xFF), x, y) & 15)) << 8);
            pInput[2] = target;
            target = SzDuel_GetMapUnitID(target_001206F0((Input_001206F0 *)pTask, mode) & 0xFF,
                target_001206F0((Input_001206F0 *)pTask, mode) >> 8);
            if (target < 0) {
                target = 0xFFFF;
            }
            TaLogic_GetRoot(((Input_001206F0 *)pTask)->position >> 8, ((Input_001206F0 *)pTask)->position & 0xFF, positions, x, y,
                pInput[2] & 0xFF, pInput[2] >> 8, (u16)target, 2);
            if (TaLogic_GetMinGoalCount((u8 *)positions) == 0) {
                pInput[2] = current;
            }
            ((Output_001206F0 *)pInput)->state = TaLogic_IsDefStyleUnit(((Input_001206F0 *)pTask)->position >> 8, ((Input_001206F0 *)pTask)->position & 0xFF,
                pInput[2], nKind, 0);
            ((Output_001206F0 *)pInput)->value = TaLogic_Keith_IsOpenUnit(((Input_001206F0 *)pTask)->position >> 8, ((Input_001206F0 *)pTask)->position & 0xFF, pTask);
            TaLogic004_InitRogicControl(pTask, fFirst);
            return 0;
        } else {
            if (command == 16) {
                s32 y2;
                s32 x = current & 0xFF;
                s32 target;

                y2 = current >> 8;
                pInput[0] = ((Input_001206F0 *)pTask)->position;
                ((Output_001206F0 *)pInput)->action = 6;
                target = x | (GetCap(0, y2 -
                    (GetMoveRange(SzDuel_GetUnit(((Input_001206F0 *)pTask)->position >> 8, ((Input_001206F0 *)pTask)->position & 0xFF), x, y2) & 15)) << 8);
                pInput[2] = target;
                target = SzDuel_GetMapUnitID(target_001206F0((Input_001206F0 *)pTask, mode) & 0xFF,
                    target_001206F0((Input_001206F0 *)pTask, mode) >> 8);
                if (target < 0) {
                    target = 0xFFFF;
                }
                TaLogic_GetRoot(((Input_001206F0 *)pTask)->position >> 8, ((Input_001206F0 *)pTask)->position & 0xFF, positions, x, y2,
                    pInput[2] & 0xFF, pInput[2] >> 8, (u16)target, 2);
                if (TaLogic_GetMinGoalCount((u8 *)positions) == 0) {
                    pInput[2] = current;
                }
                ((Output_001206F0 *)pInput)->state = TaLogic_IsDefStyleUnit(((Input_001206F0 *)pTask)->position >> 8, ((Input_001206F0 *)pTask)->position & 0xFF,
                    pInput[2], nKind, 0);
                ((Output_001206F0 *)pInput)->value = TaLogic_Keith_IsOpenUnit(((Input_001206F0 *)pTask)->position >> 8, ((Input_001206F0 *)pTask)->position & 0xFF, pTask);
                TaLogic004_InitRogicControl(pTask, fFirst);
                return 0;
            } else {
                Position_001206F0 *p = positions;
                s32 count;
                s32 i;
                s32 best;
                s32 target;
                s32 j;
                Position_001206F0 *init;

                j = 0;
                init = p;
                do {
                    init->x = init->y = 15;
                    init++;
                    j++;
                } while (j < 12);
                target = SzDuel_GetMapUnitID(target_001206F0((Input_001206F0 *)pTask, mode) & 0xFF,
                    target_001206F0((Input_001206F0 *)pTask, mode) >> 8);
                if (target < 0) {
                    target = 0xFFFF;
                }
                TaLogic_GetRoot(((Input_001206F0 *)pTask)->position >> 8, ((Input_001206F0 *)pTask)->position & 0xFF, positions,
                    current & 0xFF, current >> 8, target_001206F0((Input_001206F0 *)pTask, mode) & 0xFF,
                    target_001206F0((Input_001206F0 *)pTask, mode) >> 8, (u16)target, 7);
                count = TaLogic_GetMinGoalCount((u8 *)positions);
                if (count > 0) {
                    best = 0xFF;
                    bestScore = 0xFFFF;
                    for (i = 0; i < count; i++, p++) {
                        s32 score;
                        if (SzDuel_GetMapUnit(p->x, p->y) == 0) {
                            score = TaLogic_GetUnitWarning(p->x, p->y, nSide, 4, 1, (u8)option_001206F0(nSide));
                            if (score < bestScore) {
                                bestScore = score;
                                best = i;
                            } else if (score == bestScore) {
                                if (distance_001206F0(p, (Input_001206F0 *)pTask, mode) <
                                    distance_001206F0(&positions[best], (Input_001206F0 *)pTask, mode)) {
                                    bestScore = score;
                                    best = i;
                                }
                            }
                        }
                    }
} else {
                    pInput[0] = ((Input_001206F0 *)pTask)->position;
                    ((Output_001206F0 *)pInput)->action = 6;
                    pInput[2] = current;
                    ((Output_001206F0 *)pInput)->state = TaLogic_IsDefStyleUnit(((Input_001206F0 *)pTask)->position >> 8, ((Input_001206F0 *)pTask)->position & 0xFF,
                        pInput[2], nKind, 0);
                    ((Output_001206F0 *)pInput)->value = TaLogic_Keith_IsOpenUnit(((Input_001206F0 *)pTask)->position >> 8, ((Input_001206F0 *)pTask)->position & 0xFF, pTask);
                    TaLogic004_InitRogicControl(pTask, fFirst);
                    return 0;
                }
                    if (best != 0xFF) {
                        pInput[0] = ((Input_001206F0 *)pTask)->position;
                        ((Output_001206F0 *)pInput)->action = 6;
                        pInput[2] = (positions[best].y << 8) | positions[best].x;
                        ((Output_001206F0 *)pInput)->state = TaLogic_IsDefStyleUnit(((Input_001206F0 *)pTask)->position >> 8, ((Input_001206F0 *)pTask)->position & 0xFF,
                            pInput[2], nKind, 0);
                        ((Output_001206F0 *)pInput)->value = TaLogic_Keith_IsOpenUnit(((Input_001206F0 *)pTask)->position >> 8, ((Input_001206F0 *)pTask)->position & 0xFF, pTask);
                    } else {
                        pInput[0] = ((Input_001206F0 *)pTask)->position;
                        ((Output_001206F0 *)pInput)->action = 6;
                        pInput[2] = current;
                        ((Output_001206F0 *)pInput)->state = TaLogic_IsDefStyleUnit(((Input_001206F0 *)pTask)->position >> 8, ((Input_001206F0 *)pTask)->position & 0xFF,
                            pInput[2], nKind, 0);
                        ((Output_001206F0 *)pInput)->value = TaLogic_Keith_IsOpenUnit(((Input_001206F0 *)pTask)->position >> 8, ((Input_001206F0 *)pTask)->position & 0xFF, pTask);
                    }
                    TaLogic004_InitRogicControl(pTask, fFirst);
                
            }
        }
    }
    return 0;
}

/* Whether this duelist opens (turns face up) unit (nSide, nID) now: 0 no, 1 or 2 by its kind. */
s32 TaLogic_Keith_IsOpenUnit(s32 nSide, s32 nID, void *pInfo) {
    extern s32 SzDuel_GetUnitCardNo();
    s32 i;
    s32 free;
    s32 owner;
    u8 count;
    u32 *info;

    free = 0;
    owner = Ta_IsUnitControl(nSide, nID);
    count = 0;
    if (SzDuel_GetUnitStatus(nSide, nID, 4) != 0) {
        return 0;
    }
    for (i = 1; i < 5; i++) {
        if ((SzDuel_GetUnitKind(nSide, i) & 0x1F) == 0xE && nSide == Ta_IsUnitControl(nSide, i)) {
            count++;
        }
        if ((SzDuel_GetUnitKind((nSide == 0) ? 1 : 0, i) & 0x1F) == 0xE &&
            nSide == Ta_IsUnitControl((nSide == 0) ? 1 : 0, i)) {
            count++;
        }
    }
    switch (SzDuel_GetUnitKind(nSide, nID) >> 5) {
    case 0:
        switch (SzDuel_GetUnitCardNo(nSide, nID)) {
        case 0x202:
            if (count >= 3) {
                return 1;
            }
            break;
        case 0x1F6: {
            s16 list[16];
            u16 *p;
            s32 j;
            s32 position;

            p = (u16 *)list;
            for (j = 0; j < 22; j++) {
                *p++ = 0xFFFF;
            }
            TaUtil_GetUnitLst((owner == 0) ? 1 : 0, 3, list);
            position = TaLogic_GetMaxApUnit((u16 *)list);
            if (owner != Ta_IsUnitControl(position >> 8, position & 0xFF)) {
                return 1;
            }
            break;
        }
        case 0x20B:
            for (i = 1; i < 11; i++) {
                if (owner != Ta_IsUnitControl(owner, i) && SzDuel_GetUnitStatus(owner, i, 4) == 0) {
                    free++;
                }
                if (owner != Ta_IsUnitControl((owner == 0) ? 1 : 0, i) &&
                    SzDuel_GetUnitStatus((owner == 0) ? 1 : 0, i, 4) == 0) {
                    free++;
                }
            }
            if (free >= 6) {
                return 1;
            }
            break;
        }
        return 2;
    case 1:
        if (TaLogic_GetActionReaction(nSide, nID, 0, 0, 6, 0) == 5) {
            return 2;
        }
        info = Ta_GetUnitEffect(nSide, nID, 0);
        if (info == NULL) {
            return 2;
        }
        switch (*info >> 8) {
        case 0x12:
            if (count >= 3) {
                return 1;
            }
            break;
        }
        return 2;
    case 2:
    case 3:
    case 4:
    case 5:
    default:
        return 0;
    }
}

/* Whether unit (nSide, nID) may open while moving from (nX, nZ) to the square next to it, (gX, gZ). */
s32 TaLogic004_IsOpenMoveUnit(s32 nSide, s32 nID, s32 nX, s32 nZ,
                  s32 gX, s32 gZ, s32 arg6) {
    s32 min_y;
    s32 min_x;

    min_y = nZ < gZ ? nZ : gZ;
    gZ = Max(gZ, nZ);
    min_x = nX < gX ? nX : gX;
    gX = Max(gX, nX);
    if ((gX - min_x) + (gZ - min_y) != 2 || arg6 != 2) {
        return 0;
    }
    if (SzDuel_GetUnit(nSide, nID) == 0) {
        return 0;
    }
    if (SzDuel_GetUnitStatus(nSide, nID, 0) == 0) {
        return CheckLandAgreement2(SzDuel_GetField(nX, nZ), nSide, nID) != 1 ? 0 : 1;
    }
    return 0;
}

/* Clears a unit's task (`Is1st` on its first turn). */
void TaLogic004_InitRogicControl(void *pUnit, u8 Is1st) {
    if (Is1st < 2) {
        if (Is1st == 1) {
            *(u32 *)((u8 *)pUnit + 8) =
                (*(u32 *)((u8 *)pUnit + 8) & 0xFFFF) | 0xFFFF0000;
        } else {
            *(u32 *)((u8 *)pUnit + 8) =
                (*(u32 *)((u8 *)pUnit + 8) & 0xFFFF0000) | 0xFFFF;
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
} Req_00121630;

typedef struct {
    u8 pad0[0x160];
    u16 list[32];    /* 0x160 */
    u8 idx : 5;      /* 0x1A0 */
    u8 pad1A0 : 3;
    u8 pad1A1;
    u16 count;       /* 0x1A2 */
} Work_00121630;

s32 TaLogic_GetInputQueFromMinimumTask_b(void *, void *, s32);

/* Computer duelist 4's controller (duelistControllers[4]): the buttons it presses this frame. With an empty input
   queue it plans its next task and turns it into buttons, then plays the queue back one button per frame; after
   600 frames it gives up the turn (0x20, then 0x800). */
s32 duelistController04(s32 wCursorPos, void *pCtl) {
    Req_00121630 req;
    Work_00121630 *w;
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
        if (TaLogic_Keith_GetMinimumTask(w, &req, wCursorPos) == 0) {
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

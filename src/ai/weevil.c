/* Computer AI of Weevil Underwood (duelist 2, duelistController02). Each AI duelist is its own original file with its own copy of the shared routines. */

#include "common.h"
#pragma conditional_move off

/* This duelist's move: picks the next unit to act, gives it a task and turns that into input `pInput`; returns 1
   when it set one. */
s32 TaLogic_Weevil_GetMinimumTask(void *pCtl, void *pInput, s32 wCursorPos) {
    UnitTask *tasks = pCtl;
    s32 side;
    s32 found;
    s32 result;
    s32 index;

    side = SzDuel_GetTurnOwner();
    found = 0;
    if ((result = TaLogic_Weevil_GetNextActiveUnit(tasks, side, (s32)pInput)) < 0) {
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
    TaLogic_Weevil_CommandUnit(tasks, &tasks[index]);
    switch ((tasks[index].mission >> 8) & 0xFF) {
    case TASK_RUN:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            TaLogic_Weevil_GetMinimumTask_RunMission(&tasks[index], side, pInput, 1);
            found = 1;
        }
        break;
    case TASK_ATTACK:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            if (TaLogic_Weevil_GetMinimumTask_AtkMission(&tasks[index], side, pInput, 1) < 0) {
                TaLogic_InitRogicControl(&tasks[index], 1);
                return 1;
            }
            found = 1;
        }
        break;
    case TASK_SUMMON:
        if (TaLogic_Weevil_GetMinimumTask_Summon(tasks[index].ownerId, side, (s32)pInput) < 0) {
            TaLogic_InitRogicControl(&tasks[index], 1);
            *(u8 *)((u8 *)pInput + 2) = 0xFF;
            *(s32 *)((u8 *)pInput + 0xC) = 0;
        } else {
            TaLogic_InitRogicControl(&tasks[index], 1);
            found = 1;
        }
        break;
    case TASK_MOVETOLOCATION:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            TaLogic_Weevil_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 1, 0);
            found = 1;
        }
        break;
    case TASK_CONFIRMUNIT:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            TaLogic_Weevil_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 1, 1);
            found = 1;
        }
        break;
    case TASK_DO_NOTHING:
        TaLogic_GetMinimumTask_DoNone(&tasks[index], side, pInput);
        found = 1;
        break;
    case TASK_ENCHANT:
        TaLogic_GetMinimumTask_EncMission(&tasks[index], side, pInput, 1, 0, TaLogic_Weevil_GetWarnHideLvl(side), 2, 1);
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
            TaLogic_Weevil_GetMinimumTask_RunMission(&tasks[index], side, pInput, 0);
            found = 1;
        }
        break;
    case 2:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            if (TaLogic_Weevil_GetMinimumTask_AtkMission(&tasks[index], side, pInput, 0) < 0) {
                TaLogic_Weevil_GetMinimumTask_RunMission(&tasks[index], side, pInput, 0);
            }
            found = 1;
        }
        break;
    case 10:
        if (TaLogic_Weevil_GetMinimumTask_Summon(tasks[index].ownerId, side, (s32)pInput) < 0) {
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
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            TaLogic_Weevil_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 0, 0);
            found = 1;
        }
        break;
    case 3:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            TaLogic_Weevil_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 0, 1);
            found = 1;
        }
        break;
    case 14:
        TaLogic_GetMinimumTask_DoNone(&tasks[index], side, pInput);
        break;
    case 9:
        TaLogic_GetMinimumTask_EncMission(&tasks[index], side, pInput, 0, 0, TaLogic_Weevil_GetWarnHideLvl(side), 2, 1);
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

typedef struct Entry_0010CE20 {
    u16 unitId; /* (side << 8) | unit */
    u16 pad2;
    s16 action;
    u16 pad6;
    s32 target;
} Entry_0010CE20;

typedef struct State_0010CE20 {
    u8 pad0[0x1A1];
    u8 level : 4;
    u8 high : 4;
} State_0010CE20;
#pragma conditional_move reset

/* Gives the unit of task `pTask` its order for this turn (attack, run, move, summon, guard). */
s32 TaLogic_Weevil_CommandUnit(u16 *pCtl, u16 *pTask) {
    s32 card;
    Entry_0010CE20 *entry;
    State_0010CE20 *state;
    u16 unitId;

    state = (State_0010CE20 *)pCtl;
    entry = (Entry_0010CE20 *)pTask;
    card = Ta_IsUnitControl(entry->unitId >> 8, entry->unitId & 0xFF);
    state->level = TaLogic002_IsActiveMode();
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
                            entry->target = (entry->target & 0xFFFF0000) | 1;
                        } else {
                            entry->action = 0x6FF;
                            entry->target = (u16)entry->target | 0x10000;
                        }
                    }
                } else {
                    switch (SzDuel_GetUnitKind(unitId >> 8, unitId & 0xFF) >> 5) {
                    case 0:
                        if (TaUtil_IsExMonster(entry->unitId >> 8, entry->unitId & 0xFF) == 1) {
                            TaLogic_Weevil_CommandEfcMonster(entry, 1, state->level);
                        } else {
                            TaLogic_Weevil_CommandBtlUnit(entry, 1, state->level);
                        }
                        break;
                    case 3:
                    case 4:
                        TaLogic_CommandDefenseUnit(entry, 2, 0);
                        break;
                    case 5:
                        TaLogic_CommandDefenseUnit(entry, 1, 0);
                        break;
                    case 1:
                        TaLogic002_CommandMagicUnit(entry);
                        break;
                    case 2:
                        TaLogic_CommandEncUnit(entry, 2, 0, TaLogic_Weevil_GetWarnHideLvl(card) & 0xFF);
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
s32 TaLogic_Weevil_GetNextActiveUnit(DuelPlayer *pCtl, s32 nSide, s32 pInput) {
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
        if (((SzDuel_GetUnitKind(list[i] >> 8, list[i] & 0xFF) >> 5) == 3 ||
             (SzDuel_GetUnitKind(list[i] >> 8, list[i] & 0xFF) >> 5) == 4) &&
            TaLogic_IsUnitReadyMove(list[i]) == 1 && TaLogic_IsPickUp(list[i]) == 1) {
            return list[i];
        }
    }
    pos = nSide << 8;
    idx = TaLogic_GetActionUnitFromOwnerID(pCtl, pos);
    TaLogic_Weevil_CommandUnit(pCtl, &pCtl->taskList[idx]);
    if (((pCtl->taskList[idx].mission >> 8) & 0xFF) == 10) {
        if (SzDuel_InqHandPhase(nSide) == 1 && TaLogic_Weevil_GetMinimumTask_Summon(pos, nSide, pInput) >= 0) {
            return pos | 0x10000;
        }
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_GetUnitStatus(nSide, 0, 0) == 0) {
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_InqHandPhase(nSide) == 1 && TaLogic_Weevil_GetMinimumTask_Summon(pos, nSide, pInput) >= 0) {
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

typedef struct Command_0010D490 {
    u16 position;
    u16 pad2;
    u16 action;
    u16 pad6;
    u16 target;
    u16 padA;
} Command_0010D490;

typedef struct Entry_0010D490 {
    u16 position;
    u8 value;
    u8 pad;
} Entry_0010D490;

/* Orders a fighting unit (task `pTask`): straight at the enemy leader when `fGoalFirst` and the path is open,
   else at the nearest enemy it can beat within 2 squares (5 with `bActive`); else it pushes in. */
void TaLogic_Weevil_CommandBtlUnit(void *pTask, s32 fGoalFirst, u8 bActive) {
    extern void TaLogic_InitIgnoreLst();
    extern s32 TaLogic_IsRootOpen();
    extern s32 TaLogic002_GetNearUnit();
    Command_0010D490 *command = pTask;

    if (SzDuel_GetUnit(command->position >> 8, command->position & 0xFF) != 0) {
        s32 position;
        s32 side;
        s32 data;
        s32 other;
        s32 otherPosition;
        u8 workspace[112];
        Entry_0010D490 entries[23];
        s16 count;
        s16 total;
        s32 i;
        Entry_0010D490 *entry;

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
            if (TaLogic_IsRootOpen(command->position >> 8, command->position & 0xFF,
                    position & 0xFF, position >> 8, other >> 8, other & 0xFF,
                    otherPosition & 0xFF, otherPosition >> 8, 2) > 0) {
                command->action = 0x2FF;
                *(u32 *)&command->target = (other << 16) | command->target;
                return;
            }
        }

        total = 0;
        count = 0;
        if (bActive == 0) {
            i = 1;
            while (1) {
                s32 result;
                other = Ta_GetCurrentSide(command->position >> 8, command->position & 0xFF) == 0 ? 1 : 0;
                result = TaLogic002_GetNearUnit(command, 0, data, position & 0xFF, position >> 8,
                    other, (u8)i, TaLogic_Weevil_GetWarnHideLvl(side), entries, 0,
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
                    TaLogic_CommandDefenseUnit(command, 1, 1);
                    return;
                }
                i++;
                if (i > 2) {
                    break;
                }
            }
            TaLogic_CommandDefenseUnit(command, 1, 0);
        } else {
            i = 1;
            do {
                s32 result;
                other = Ta_GetCurrentSide(command->position >> 8, command->position & 0xFF) == 0 ? 1 : 0;
                result = TaLogic002_GetNearUnit(command, 0, data, position & 0xFF, position >> 8,
                    other, (u8)i, TaLogic_Weevil_GetWarnHideLvl(side), entries, 0,
                    &count, &total, 6, workspace);
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
                    TaLogic_CommandDefenseUnit(command, 1, 1);
                    return;
                }
                i++;
            } while (i < 6);
            TaLogic_CommandDefenseUnit(command, 1, 0);
        }
    }
}

/* TaLogic_GetNearUnit with this duelist's view and strength settings. */
s32 TaLogic002_GetNearUnit(s32 pTask, s32 pTree, s32 pVarInfo, s32 nX, s32 nZ, s32 eSide, s32 bDist, s32 WarnLvl, s32 nUnitLst, u16 wUnitNum, s32 wSize, s32 wNodeCount, u8 bChase, s32 wIgnoreLst) {
    return TaLogic_GetNearUnit(pTask, pTree, pVarInfo, nX, nZ, eSide, bDist, WarnLvl,
                  nUnitLst, wUnitNum, wSize, wNodeCount, bChase,
                  0, 0x960, wIgnoreLst);
}

typedef struct Entry_0010D880 {
    u16 id;
    u8 index;
    u8 pad;
} Entry_0010D880;

/* Orders an effect monster (task `pTask`): where its effect does most (`fGoalFirst`, `bActive` as for fighting
   units). */
void TaLogic_Weevil_CommandEfcMonster(void *pTask, s32 fGoalFirst, u8 bActive) {
    extern s32 SzDuel_GetUnitCardNo();
    extern void TaLogic_InitIgnoreLst();
    extern s32 TaLogic_GetNearUnit();
    u8 context[0x70];
    Entry_0010D880 entries[23];
    s16 count;
    s16 otherCount;
    s32 i;
    Entry_0010D880 *entry;
    s32 owner;
    s32 location;
    s32 data;
    s32 type;
    s32 x;
    s32 y;
    s32 attempt;
    s32 result;
    u16 id;

    id = *(u16 *)pTask;
    if ((data = SzDuel_GetUnit(id >> 8, id & 0xFF)) != 0) {
        id = *(u16 *)pTask;
        owner = Ta_GetCurrentSide(id >> 8, id & 0xFF);
        id = *(u16 *)pTask;
        location = SzDuel_GetUnitLoc(id >> 8, id & 0xFF);
        otherCount = 0;
        count = 0;
        entry = entries;
        i = 0;
        do {
            i++;
            entry->id = 0xFFFF;
            entry->index = 0xFF;
            entry++;
        } while (i < 22);
        TaLogic_InitIgnoreLst(context);
        id = *(u16 *)pTask;
        type = SzDuel_GetUnitCardNo(id >> 8, id & 0xFF);
        switch (type) {
        case 0x192:
        case 0x193:
            attempt = 1;
            x = location >> 8;
            y = location & 0xFF;
            while (1) {
                result = TaLogic_GetNearUnit(pTask, 0, data, y, x,
                    owner == 0 ? 1 : 0, (u8)attempt, TaLogic_Weevil_GetWarnHideLvl(owner),
                    entries, 0, &count, &otherCount, 2, 0, 0x960, context);
                switch (result) {
                case 3:
                case 2:
                    *(u16 *)((u8 *)pTask + 4) = 0x3FF;
                    *(u32 *)((u8 *)pTask + 8) = (location << 16) | *(u16 *)((u8 *)pTask + 8);
                    return;
                case 1:
                    return;
                case 0:
                    *(u16 *)((u8 *)pTask + 4) = 0x3FF;
                    *(u32 *)((u8 *)pTask + 8) = (location << 16) | *(u16 *)((u8 *)pTask + 8);
                    return;
                }
                attempt++;
                if (attempt > 2) {
                    break;
                }
            }
            *(u16 *)((u8 *)pTask + 4) = 0x3FF;
            *(u32 *)((u8 *)pTask + 8) = (location << 16) | *(u16 *)((u8 *)pTask + 8);
            break;
        case 0x1A1:
            if (TaLogic_CommandGunnerUnit(pTask, 0) != 1) {
                TaLogic_Weevil_CommandBtlUnit(pTask, 1, bActive);
            }
            break;
        case 0x198:
            if (SzDuel_GetLP(owner) < 1000) {
                TaLogic_CommandDefenseUnit(pTask, 0, 0);
            }
            TaLogic_Weevil_CommandBtlUnit(pTask, 1, bActive);
            break;
        default:
            TaLogic_Weevil_CommandBtlUnit(pTask, 1, bActive);
            break;
        }
    }
}

/* Orders a unit (task `pTask`) to guard line `nLine` near its leader. */
void TaLogic_CommandDefenseUnit(void *pTask, s32 nLine, s32 fHold) {
    s32 i;
    s32 position;
    s32 occupant;
    s32 count;
    s32 mode;
    u16 *record = pTask;

    if (SzDuel_GetUnit((s32) record[0] >> 8, record[0] & 0xFF) != 0) {
        Ta_GetCurrentSide((s32) record[0] >> 8, record[0] & 0xFF);
        SzDuel_GetUnitLoc((s32) record[0] >> 8, record[0] & 0xFF);
        SzDuel_GetUnit((s32) record[0] >> 8, record[0] & 0xFF);
        if ((fHold & 0xFF) == 1) {
            mode = 3;
        } else {
            mode = 6;
        }
        record[2] = (mode << 8) | 0xFF;
        if ((nLine & 0xFF) == 1) {
            count = 6;
        } else {
            count = 4;
        }
        for (i = 0; i < count; i++) {
            position = (u16) TaLogic002_GetLinePiece(nLine, i & 0xFF);
            occupant = SzDuel_GetMapUnitID(position & 0xFF, position >> 8);
            if (occupant == record[0] || occupant < 0) {
                *(u32 *) (record + 4) = (position << 16) | record[4];
                return;
            }
        }
    }
}

typedef struct {
    u16 coordinate;
    u16 pad2;
    u16 status;
    u16 pad6;
    u32 value;
} State_0010DC40;

/* Orders a face-down magic card (task `pTask`): a field-changing card opens where it changes most squares. */
void TaLogic002_CommandMagicUnit(void *pTask) {
    State_0010DC40 *state = pTask;
    s32 coordinate;
    s32 result;
    u32 *record;

    if (SzDuel_GetUnit((s32) state->coordinate >> 8, state->coordinate & 0xFF) != 0) {
        record = Ta_GetUnitEffect((s32) state->coordinate >> 8, state->coordinate & 0xFF, 0);
        if (record != NULL) {
            switch (*record >> 8) {
        case 13:
            state->status = 0x5FF;
            return;
        case 2:
            coordinate = SzDuel_GetUnitLoc((s32) state->coordinate >> 8, state->coordinate & 0xFF) & 0xFFFF;
            result = TaLogic_GetLandChange(SzDuel_GetUnit((s32) state->coordinate >> 8, state->coordinate & 0xFF), coordinate & 0xFF, coordinate >> 8, 0, 6, 2) & 0xFFFF;
            state->status = 0x6FF;
            if (result < 0) {
                state->value = ((coordinate & 0xFFFF) << 16) | *(u16 *) &state->value;
                return;
            }
            state->value = ((result & 0xFFFF) << 16) | *(u16 *) &state->value;
            break;
            }
        }
    }
}

/* The summon task for side `nSide`: which hand cards to play and where, into `pInput`; -1 when it plays none. */
s32 TaLogic_Weevil_GetMinimumTask_Summon(s32 wUnit, s32 nSide, s32 pInput) {
    extern s32 TaLogic_Weevil_IsHandPlay();
    extern s32 TaLogic002_GetSummonPiece();
    extern s32 TaLogic002_GetSpellPlay();
    extern s32 TaLogic_GetUnitNum();
    u8 work[0x60];
    s32 ret;
    s32 res;
    s32 pos;
    s32 kind;
    u8 *ctx = (u8 *)pInput;

    *(s16 *)ctx = wUnit;
    if (SzDuel_InqHandPhase(nSide) == 0) {
        return -1;
    }
    if (TaLogic_GetUnitNum(nSide, 0) == 5 && TaLogic_GetUnitNum(nSide, 1) == 5) {
        return -1;
    }
    kind = TaLogic_Weevil_IsHandPlay(nSide, work);
    if (kind == -1) {
        return -1;
    }
    *(u8 *)(ctx + 2) = 10;
    *(s32 *)(ctx + 0xC) = 0;
    pos = SzDuel_GetUnitLoc(wUnit >> 8, wUnit & 0xFF);
    if (kind == 0) {
        if (TaLogic_Weevil_SetComboQue(nSide, ctx, work) >= 0) {
            ret = TaLogic_GetNearCard2(work, pos & 0xFF, pos >> 8,
                                nSide == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0,
                                TaLogic_Weevil_GetWarnHideLvl(nSide));
            if (ret < 0) {
                if (SzDuel_GetUnitMonsterCount(nSide) < 6) {
                    res = TaLogic002_GetSummonPiece(nSide, kind & 0xFF, work, ret);
                    if (res < 0) {
                        return -1;
                    }
                    *(s16 *)(ctx + 4) = res;
                    return 1;
                }
            } else {
                res = TaLogic002_GetSummonPiece(nSide, kind & 0xFF, work, ret);
                if (res < 0) {
                    return -1;
                }
                *(s16 *)(ctx + 4) = res;
                return 1;
            }
        }
    } else {
        ret = TaLogic_GetNearCard2(work, pos & 0xFF, pos >> 8,
                            nSide == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0,
                            TaLogic_Weevil_GetWarnHideLvl(nSide));
    }
    if (kind == 2) {
        TaLogic_Weevil_SetSpecialComboQue(nSide, ctx, (s32)work, 0);
        *(s16 *)(ctx + 4) = 0;
        return 1;
    }
    if (TaLogic002_GetSpellPlay(nSide, ctx, work) < 0) {
        return -1;
    }
    res = TaLogic002_GetSummonPiece(nSide, kind & 0xFF, work, ret);
    if (res < 0) {
        return -1;
    }
    *(s16 *)(ctx + 4) = res;
    return 1;
}

/* Whether side `nSide` should play from its hand this turn (and what, into `pInput`). */
s32 TaLogic_Weevil_IsHandPlay(s32 nSide, void *pInput) {
    extern s32 TaLogic_GetUnitNum();
    extern s32 TaLogic002_GetSpecialComboPlay();
    s32 entries[8];
    u8 buffer[32];
    u8 first;
    u8 second;
    s32 first_index;
    s32 *first_entry;
    s32 *zero_entry;
    s32 zero_index;
    s32 *check_entry;
    s32 check_index;
    s32 *last_entry;
    s32 last_index;
    s32 result;

    first = TaLogic_GetUnitNum(nSide, 0);
    second = TaLogic_GetUnitNum(nSide, 1);
    if (pInput == NULL) {
        return -1;
    }
    TaHand_GetNextHand(nSide, entries);
    if (first == 5) {
        if (TaLogic002_GetSpellPlay(nSide, buffer, pInput) >= 0) {
            return 1;
        } else {
            return -1;
        }
    }
    if (second == 5) {
        first_index = 0;
        if (0 < TaHand_GetNextHandNum(nSide)) {
            first_entry = entries;
            do {
                if ((TaHand_GetCardKind(*first_entry) >> 5) == 0 &&
                    TaHand_CanAffordSummonCost(nSide, *first_entry) == 1) {
                    SzDuel_InitCardInfo(pInput, entries[first_index]);
                    return 0;
                }
                first_entry++;
                first_index++;
            } while (first_index < TaHand_GetNextHandNum(nSide));
        }
        return -1;
    }
    if (TaLogic002_GetSpecialComboPlay(nSide, buffer, pInput, 0) >= 0) {
        return 2;
    }
    if (first == 0) {
        zero_index = 0;
        if (0 < TaHand_GetNextHandNum(nSide)) {
            zero_entry = entries;
            do {
                if ((TaHand_GetCardKind(*zero_entry) >> 5) == 0 &&
                    TaHand_CanAffordSummonCost(nSide, *zero_entry) == 1) {
                    return 0;
                }
                zero_entry++;
                zero_index++;
            } while (zero_index < TaHand_GetNextHandNum(nSide));
        }
        return TaLogic002_GetSpellPlay(nSide, buffer, pInput);
    }
    if (TaLogic002_IsMakeDefense(1) == 0) {
        check_index = 0;
        if (0 < TaHand_GetNextHandNum(nSide)) {
            check_entry = entries;
            do {
                if ((TaHand_GetCardKind(*check_entry) >> 5) == 0 &&
                    TaHand_CanAffordSummonCost(nSide, *check_entry) == 1) {
                    return 0;
                }
                check_entry++;
                check_index++;
            } while (check_index < TaHand_GetNextHandNum(nSide));
        }
    }
    if (TaLogic002_IsMakeDefense(2) == 0) {
        result = TaLogic002_GetSpellPlay(nSide, buffer, pInput);
        if (result >= 0) {
            return result;
        }
    }
    last_index = 0;
    if (0 < TaHand_GetNextHandNum(nSide)) {
        last_entry = entries;
        do {
            if ((TaHand_GetCardKind(*last_entry) >> 5) == 0 &&
                TaHand_CanAffordSummonCost(nSide, *last_entry) == 1) {
                SzDuel_InitCardInfo(pInput, entries[last_index]);
                return 0;
            }
            last_entry++;
            last_index++;
        } while (last_index < TaHand_GetNextHandNum(nSide));
    }
    result = TaLogic002_GetSpellPlay(nSide, buffer, pInput);
    if (result >= 0) {
        return result;
    }
    return -1;
}

typedef struct Info_0010E320 {
    u8 pad00[8];
    u16 x;
    s16 y;
} Info_0010E320;

typedef struct Sprite_0010E320 {
    Info_0010E320 *info;
    u8 pad04[0x34];
    s16 x;
    s16 y;
} Sprite_0010E320;

/* Fills hand combination `bCombo` for side `nSide`: the best fusion or equip chain, its card into `pCardInfo`. */
s32 TaLogic_Weevil_SetComboQue(s32 nSide, u8 *bCombo, void *pCardInfo) {
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
                    if (TaHand_CanAffordSummonCost(nSide, card) == 1) {
                        if (best < value) {
                            TaLogic_Weevil_ConvEmptyCombo(nSide, *node, entries);
                            TaLogic_CopyArray((u8 *)*node + 2, bCombo + 6);
                            SzDuel_InitCardInfo(pCardInfo, **node);
                            ((Sprite_0010E320 *)pCardInfo)->x = (value >> 16) - (((Sprite_0010E320 *)pCardInfo)->info->x & 0x1FFF);
                            ((Sprite_0010E320 *)pCardInfo)->y = (value & 0xFFFF) - (((Sprite_0010E320 *)pCardInfo)->info->y & 0x1FFF);
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

/* Fills hand combination `bCombo` for side `nSide` with this duelist's special combination, its card into
   `pCardInfo`. */
s32 TaLogic_Weevil_SetSpecialComboQue(s32 nSide, void *bCombo, s32 pCardInfo, s32 nOpt) {
    s32 count;
    s32 *p;
    s32 i;
    s32 values[8];
    s32 j;
    s32 value;
    u8 *slot;
    u8 *out = (u8 *)bCombo;

    if (pCardInfo == 0) return -1;
    j = 0;
    do {
        out[j + 6] = 255;
        j++;
    } while (j < 5);
    TaHand_GetNextHand(nSide, values);
    if (!(nOpt & 255)) {
        TaLogic002_GetSpecialComboPlay(nSide, (u8 *)bCombo, (void *)pCardInfo, 0);
        count = 2;
        if (Taku_Get_WinCount() > 3) {
            i = 0;
            if (i < TaHand_GetNextHandNum(nSide)) {
                p = values;
                do {
                    if (i != out[6] && i != out[7] && Ta_GetHandEnchant(427, *p) >= 0 && (TaHand_GetCardKind(*p) >> 5) == 2) {
                        value = *p;
                        if (value != 795 && value != 796) {
                            slot = out + count;
                            count++;
                            slot[6] = i;
                        }
                    }
                    p++;
                    i++;
                } while (i < TaHand_GetNextHandNum(nSide));
            }
        }
    }
    return 0;
}

typedef struct {
    u16 id;
    u8 values[5];
} Info_0010E6B0;

/* Fills an empty combination: the hand card side `nSide` can summon with the best attack plus defence. */
void TaLogic_Weevil_ConvEmptyCombo(s32 nSide, void *pCardInfo, s32 *pResult) {
    Info_0010E6B0 *info = pCardInfo;
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
                if (card != 0x3E7 && TaLogic002_IsRefuseEmptyCombo(card) == 0 && level >= TaHand_GetCardSummonCost2(card, nSide)) {
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

struct DotrFreeBlock {
    unsigned char unknown_00[0x3c];
    unsigned short unknown_3c;
    unsigned char unknown_3e;
};
struct DotrFreeNibbles {
    unsigned char low : 4;
    unsigned char high : 4;
};
struct DotrStateItem;
extern struct DotrStateItem *func_001E36E0_b(int x, int y);
extern int func_00278510_b(struct DotrFreeBlock *block, int packed, int c, int d, int e, int skip);
extern int func_0027A130_b(struct DotrFreeBlock *block, struct DotrFreeNibbles *bytes, int column, int row, int x, int y,
                              int g, int h, unsigned char i, unsigned short key);
extern int func_002792C0_b(struct DotrFreeBlock *block, struct DotrFreeNibbles *bytes, int column, int row, int x, int y,
                              unsigned short id, int n);
extern int func_0010F850_b(unsigned char mode, unsigned char index);

/* The square side `nSide` summons a card of kind `sKind` to. */
int TaLogic002_GetSummonPiece(int nSide, int sKind, void *pInput, int nMode)
{
    struct DotrFreeBlock * block = pInput;
    struct DotrFreeNibbles bytes[12];
    int i;
    int inv;
    int id;
    int last_y;
    int last_x;
    int here;
    int lvl;
    int best_spot;
    int ny;
    struct DotrFreeNibbles *p;
    int cost;
    int best;
    int spot;
    int nx;
    int j;
    int m;
    int mode;
    int y;
    int last;
    int here_y;
    int field;
    int round;
    int near_spot;
    int near;
    int to_y;
    int near_at;
    int here_x;
    int to_x;
    int line;
    int x;
    int free_spot;
    int near_cost;

    if (block == 0) {
        return -1;
    }
    for (i = 0, p = bytes; i < 12; i++, p++) p->low = p->high = 0xf;
    SzDuel_GetUnitLoc(nSide, 0);
    

    if ((mode = (sKind = (unsigned char)(block->unknown_3e >> 5))) != 0 && sKind != 3) {
        if (sKind != 4) goto tail;
    }
    {
        if (nMode >= 0) {
            best = 0xff;
            best_spot = 0xffff;
            here = SzDuel_GetUnitLoc(nMode >> 8, nMode & 0xff);
            lvl = TaLogic_Weevil_GetWarnHideLvl(nSide);
            here_y = here >> 8;
            here_x = here & 0xff;
            inv = func_00278510_b(block, nMode, lvl, here_x, here_y, 0);
            for (i = 0; i < 8; i++) {
                if ((spot = TaLogic_Weevil_GetSommonPiecePreference(nSide, i)) >= 0) {
                    x = spot & 0xff;
                    y = spot >> 8;
                    field = SzDuel_GetField(x, y);
                    if (field != 8) {
                        if (func_001E36E0_b(x, y) == 0) {
                            if (field != 9 || Ta_IsVirus_Chk3(block, x, y) != 1) {
                                for (j = 0, p = bytes; j < 12; j++, p++) p->low = p->high = 0xf;
                                if (inv >= 0) {
                                    cost = func_0027A130_b(block, bytes, x, y, here_x, here_y, nMode, 0, 2, (unsigned short)TaLogic_Weevil_GetWarnHideLvl(nSide));
                                } else {
                                    cost = func_002792C0_b(block, bytes, x, y, here_x, here_y, (unsigned short)nMode, 2);
                                }
                                if (TaLogic_GetMinGoalCount(bytes) > 0 && cost < best && cost >= 0) {
                                    best = cost;
                                    best_spot = spot;
                                }
                            }
                        }
                    }
                }
            }
            if (best_spot != 0xffff) {
                return best_spot;
            }
            best_spot = -1;
            return best_spot;
        }
        for (round = 0; round < (mode == 0 ? 6 : 4); round++) {
            line = (unsigned short)func_0010F850_b(mode == 0 ? 1 : 2, round);
            near_spot = 0xffff;
            near = 14;
            if (line >= 0) {
                for (j = 0, to_y = line >> 8, to_x = line & 0xff; j < 8; j++) {
                    if ((near_at = TaLogic_Weevil_GetSommonPiecePreference(nSide, j)) >= 0) {
                        nx = near_at & 0xff;
                        ny = near_at >> 8;
                        if (SzDuel_GetField(nx, ny) != 8) {
                            if (SzDuel_GetField(nx, ny) != 9) {
                                if (SzDuel_GetMapUnitID(nx, ny) < 0) {
                                    id = SzDuel_GetMapUnitID(nx, ny);
                                    if (id < 0) {
                                        id = 0xffff;
                                    }
                                    near_cost = func_002792C0_b(block, bytes, nx, ny, to_x, to_y, (unsigned short)id, 7);
                                    if (near_cost < near && near_cost >= 0) {
                                        near_spot = near_at;
                                        near = near_cost;
                                    }
                                }
                            }
                        }
                    }
                }
                if (near < 14) {
                    return near_spot;
                }
            }
        }
        goto none;
    }
tail:
    last = 0xffff;
    for (m = 0; m < 8; m++) {
        if ((free_spot = TaLogic_Weevil_GetSommonPiecePreference(nSide, m)) >= 0) {
            last_x = free_spot & 0xff;
            last_y = free_spot >> 8;
            if (SzDuel_GetField(last_x, last_y) != 8) {
                if (SzDuel_GetField(last_x, last_y) != 9) {
                    if (SzDuel_GetMapUnitID(last_x, last_y) < 0) {
                        if (last_x >= 0) {
                            last = free_spot;
                        }
                    }
                }
            }
        }
    }
    if (last != 0xffff) {
        return last;
    }
none:
    return -1;
}

/* Ta_GetSommonPiecePreference for this duelist. */
s32 TaLogic_Weevil_GetSommonPiecePreference(s32 nSide, u32 nPr) {
    return Ta_GetSommonPiecePreference(nSide, nPr);
}

/* How careful this duelist is about hidden cards (by its life points and monster count). */
s32 TaLogic_Weevil_GetWarnHideLvl(s32 nSide) {
    if (SzDuel_GetLP(nSide) > 0x5DC) {
        if (SzDuel_GetUnitMonsterCount(nSide) >= 4) {
            return 0;
        }
        return 0;
    }
    return 0;
}

/* Whether this duelist opens (turns face up) unit (nSide, nID) now: 0 no, 1 or 2 by its kind. */
s32 TaLogic_Weevil_IsOpenUnit(s32 nSide, s32 nID, u32 *pInfo) {
    extern s32 SzDuel_GetUnitCardNo();
    s32 card;
    s32 position;
    u32 *info;

    position = SzDuel_GetUnitLoc(nSide, nID);
    if (SzDuel_GetUnitStatus(nSide, nID, 4) != 0) {
        return 0;
    }
    card = SzDuel_GetUnitCardNo(nSide, nID);
    switch (SzDuel_GetUnitKind(nSide, nID) >> 5) {
    case 0:
        if (card == 0x1AB || card == 0x1AC || card == 0x192 || card == 0x193) {
            return 1;
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
        case 13:
            return 1;
        case 2:
            card = (pInfo[2] >> 16) & 0xFFFF;
            if (card == SzDuel_GetUnitLoc(nSide, nID)) {
                return 1;
            }
        default:
            return 2;
        }
    case 5:
        if (TaLogic_GetActionReaction(nSide, nID, 0, 0, 6, 0) == 5) {
            return 2;
        }
        if (TaLogic002_IsDoCerem(Ta_IsUnitControl(nSide, nID), card) == 1) {
            if (SzDuel_GetField(position & 0xFF, position >> 8) != 9) {
                return 1;
            }
        }
        return 2;
    case 2:
    case 3:
    case 4:
    default:
        return 2;
    }
}

/* Whether this duelist plays in its attacking mode this turn. */
s32 TaLogic002_IsActiveMode(void) {
    extern s32 SzDuel_GetUnitCardNo();
    u16 buf[22];
    s32 id;
    s32 i;
    u16 kind;

    id = SzDuel_GetTurnOwner();
    for (i = 0; i < 22; i++) {
        buf[i] = 0xFFFF;
    }
    TaUtil_GetUnitLst(id, 1, buf);
    for (i = 0; i < 22; i++) {
        if (buf[i] != 0xFFFF) {
            kind = SzDuel_GetUnitCardNo(buf[i] >> 8, buf[i] & 0xFF);
            if (kind == 0x192 || kind == 0x193 || kind == 0x1A6) {
                return 1;
            }
        }
    }
    for (i = 0; i < 22; i++) {
        if (buf[i] != 0xFFFF) {
            kind = SzDuel_GetUnitCardNo(buf[i] >> 8, buf[i] & 0xFF);
            if (kind == 0x350 || kind == 0x31E) {
                return 0;
            }
        }
    }
    for (i = 0; i < 5; i++) {
        kind = SzDuel_InqHand(id, i) & 0xFFF;
        if (kind == 0x350 || kind == 0x31E) {
            return 0;
        }
    }
    for (i = 0; i < SzDuel_GetDeckCount(id); i++) {
        kind = SzDuel_InqDeck(id, i);
        if (kind == 0x350 || kind == 0x31E) {
            return 0;
        }
    }
    return 1;
}

/* Whether this duelist keeps card `nCardNo` out of a summon (it is wanted for an equip). */
s32 TaLogic002_IsRefuseEmptyCombo(s32 nCardNo) {
    if ((TaHand_GetCardKind(nCardNo) >> 5) != 0) {
        return 0;
    }
    if (Ta_GetHandEnchant(nCardNo, 0x31E) >= 0) {
        return 1;
    }
    if (nCardNo == 0x18E) {
        return 1;
    }
    return 0;
}

struct DotrStateBlock;
struct DotrStateItem_10f290;
extern struct DotrStateItem_10f290 *func_001E36E0_10f290(int x, int y);
struct DotrPickTarget {
    unsigned char unknown_00[8];
    unsigned short unknown_08;
    short unknown_0a;
};
struct DotrPickBlock {
    struct DotrPickTarget *target;
    unsigned char unknown_04[0x34];
    short unknown_38;
    short unknown_3a;
    unsigned short unknown_3c; 
    unsigned char unknown_3e;
};

/* Whether side `nSide` can play this duelist's special combination now. */
int TaLogic002_GetSpecialComboPlay(int nSide, unsigned char *bCombo, void *pCardInfo, unsigned char nMode)
{
    struct DotrPickBlock * block = pCardInfo;
    int ids[8];
    int i;
    int found;

    found = 0;
    TaHand_GetNextHand(nSide, ids);
    switch (nMode) {
    case 0:
        if (func_001E36E0_10f290(0, 0) || SzDuel_GetUnitLoc(nSide, 0) != 1) {
            return -1;
        }
        i = 0;
        if (0 < TaHand_GetNextHandNum(nSide)) {
            do {
                if (ids[i] == 798) {
                    found = 1;
                    bCombo[6] = i;
                }
                i++;
            } while (i < TaHand_GetNextHandNum(nSide));
        }
        if (found == 1) {
            i = 0;
            if (0 < TaHand_GetNextHandNum(nSide)) {
                do {
                    if ((TaHand_GetCardKind(ids[i]) >> 5) == 0) {
                        if (Ta_GetHandEnchant(ids[i], 798) >= 0) {
                            if (TaHand_IsCardSummon(nSide, ids[i]) == 1) {
                                bCombo[7] = i;
                                SzDuel_InitCardInfo((struct DotrStateBlock *)block, ids[i]);
                                return TaHand_GetCardKind(ids[i]) >> 5;
                            }
                        }
                    }
                    i++;
                } while (i < TaHand_GetNextHandNum(nSide));
            }
        }
        break;
    }
    return -1;
}

/* Whether side `nSide` plays a magic or ritual card from its hand now (its slot into `bCombo`, the card into
   `pCardInfo`). */
s32 TaLogic002_GetSpellPlay(s32 nSide, u8 *bCombo, void *pCardInfo) {
    s32 entries[5];
    s32 i;

    TaHand_GetNextHand(nSide, entries);
    if (pCardInfo == NULL) {
        return -1;
    }
    for (i = 0; i < 5; i++) {
        bCombo[i + 6] = 0xFF;
    }

    for (i = 0; i < TaHand_GetNextHandNum(nSide); i++) {
        if ((TaHand_GetCardKind(entries[i]) >> 5) == 5 && TaLogic002_IsDoCerem(nSide, entries[i]) == 1) {
            bCombo[6] = i;
            SzDuel_InitCardInfo(pCardInfo, entries[i]);
            return 1;
        }
    }

    for (i = 0; i < TaHand_GetNextHandNum(nSide); i++) {
        if ((TaHand_GetCardKind(entries[i]) >> 5) == 3 || (TaHand_GetCardKind(entries[i]) >> 5) == 4) {
            bCombo[6] = i;
            SzDuel_InitCardInfo(pCardInfo, entries[i]);
            return 1;
        }
    }

    for (i = 0; i < TaHand_GetNextHandNum(nSide); i++) {
        if ((TaHand_GetCardKind(entries[i]) >> 5) != 0 && (TaHand_GetCardKind(entries[i]) >> 5) != 2) {
            bCombo[6] = i;
            SzDuel_InitCardInfo(pCardInfo, entries[i]);
            return 1;
        }
    }

    for (i = 0; i < TaHand_GetNextHandNum(nSide); i++) {
        if ((TaHand_GetCardKind(entries[i]) >> 5) != 0) {
            bCombo[6] = i;
            SzDuel_InitCardInfo(pCardInfo, entries[i]);
            return 1;
        }
    }
    return -1;
}

/* Whether this duelist should build a defence line for side `nSide` now. */
s32 TaLogic002_IsMakeDefense(s32 nSide) {
    s32 controllingSide;
    s32 controllingSide2;
    s32 i;
    s32 unitId2Lo;
    s32 unitSlot;
    u16 linePiece;
    s32 unitId;
    u16 linePiece2;
    s32 unitId2;
    s32 var_s0;
    s32 j;

    var_s0 = 0;
    if ((nSide & 0xFF) == 1) {
        i = 0;
        do {
            linePiece = TaLogic002_GetLinePiece(nSide, i & 0xFF);
            unitId = SzDuel_GetMapUnitID(linePiece & 0xFF, linePiece >> 8);
            if (unitId >= 0) {
                unitSlot = unitId & 0xFF;
                controllingSide = Ta_IsUnitControl(unitId >> 8, unitSlot);
                if ((controllingSide == SzDuel_GetTurnOwner()) && (unitSlot != 0)) {
                    var_s0 += 1;
                }
            }
            i += 1;
        } while (i < 6);
        if (var_s0 >= 2) {
            return 1;
        } else {
            return 0;
        }
    }
    j = 0;
    do {
        linePiece2 = TaLogic002_GetLinePiece(nSide, j & 0xFF);
        unitId2 = SzDuel_GetMapUnitID(linePiece2 & 0xFF, linePiece2 >> 8);
        if (unitId2 >= 0) {
            unitId2Lo = unitId2 & 0xFF;
            controllingSide2 = Ta_IsUnitControl(unitId2 >> 8, unitId2Lo);
            if ((controllingSide2 == SzDuel_GetTurnOwner()) && (unitId2Lo != 0)) {
                var_s0 += 1;
            }
        }
        j += 1;
    } while (j < 4);
    if (var_s0 > 0) {
        return 1;
    } else {
        return 0;
    }
}

/* The square on line `nLine` this duelist's unit goes to. */
s32 TaLogic002_GetLinePiece(s32 nSide, s32 nLine) {
    s32 nLineLo2;
    u32 nLineLo;

    if ((nSide & 0xFF) == 1) {
        nLineLo = nLine & 0xFF;
        switch (nLineLo) {                          /* switch 1 */
        case 0:                                     /* switch 1 */
            return 0x203;
        case 1:                                     /* switch 1 */
            return 0x302;
        case 2:                                     /* switch 1 */
            return 0x301;
        case 3:                                     /* switch 1 */
            return 0x300;
        case 4:                                     /* switch 1 */
            return 0x104;
        case 6:                                     /* switch 1 */
            return 4;
        default:                                    /* switch 1 */
            return 0x203;
        }
    } else {
        nLineLo2 = nLine & 0xFF;
        switch (nLineLo2) {                          /* switch 2; irregular */
        case 0:                                     /* switch 2 */
            return 0x102;
        case 1:                                     /* switch 2 */
            return 0x201;
        case 2:                                     /* switch 2 */
            return 0x200;
        case 3:                                     /* switch 2 */
            return 2;
        default:                                    /* switch 2 */
            return 0x102;
        }
    }
}

/* Whether side `nSide` can play ritual card `nCardNo` now (it has the units to give up). */
s32 TaLogic002_IsDoCerem(s32 nSide, s32 nCardNo) {
    extern s32 SzDuel_GetUnitCardNo();
    s32 sp50[4];
    s32 i;
    s32 mask;
    s32 low;
    s32 high;
    s32 value;
    s32 kind;
    s32 result;

    Ta_GetCeremSacrifice(sp50, *(s32 *)((u8 *)TaHand_GetCardEffect(nCardNo, 0) + 4));
    if ((mask = Ta_GetSacrificeUnit(sp50, nSide)) < 0) {
        return 0;
    }
    for (i = 0; i < Ta_GetUnitNumFrom22bitFlagList(mask); i++) {
        value = Ta_GetUnitOwnerIDFromLstCount(mask, i);
        high = value >> 8;
        low = value & 0xFF;
        kind = SzDuel_GetUnitCardNo(high, low);
        if (kind == 0x1AB || kind == 0x1AC || kind == 0x192 || kind == 0x193) {
            return 0;
        }
        result = SzDuel_GetUnitLoc(high, low);
        if (TaUtil_GetUnitAP(high, low, result & 0xFF, result >> 8) >= 0xBB8) {
            return 0;
        }
    }
    return 1;
}

typedef struct {
    u8 low : 4;
    u8 high : 4;
} Flags_0010FA60;

typedef struct {
    u16 id;
    u8 action;
    u8 pad3;
    u16 position;
    u8 pad6[6];
    s32 value;
    u8 mode;
} Output_0010FA60;

/* This duelist's caution about hidden cards (an inline copy of its GetWarnHideLvl: by life points and monster
   count). */
static inline s32 score_0010FA60(s32 arg0) {
    if (SzDuel_GetLP(arg0) > 0x5DC) {
        if (SzDuel_GetUnitMonsterCount(arg0) >= 4) {
            return 0;
        }
        return 0;
    }
    return 0;
}

/* The task of a unit running from danger (task `pTask`): the safest square in reach, into `pInput` (`fFirst` = 1
   for the unit's first-choice task). */
s32 TaLogic_Weevil_GetMinimumTask_RunMission(UnitTask *pTask, s32 nSide, void *pInput, u8 fFirst) {
    extern s32 TaLogic_GetUnitWarning(s32, s32, s32, s32, s32, u8);
    extern s32 TaLogic_IsRunPassRoot(s32, s32, s32, s32, s32, s32, void *, u8);
    extern s32 TaLogic_Weevil_IsOpenUnit();
    s32 position;
    u8 upperX;
    u8 flag;
    Flags_0010FA60 cells[12];
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
    Output_0010FA60 *out = pInput;

    position = SzDuel_GetUnitLoc(pTask->ownerId >> 8, pTask->ownerId & 0xFF);
    i = 0;
    do {
        cells[i].low = cells[i].high = 15;
        i++;
    } while (i < 12);

    {
        u16 value = (u16)score_0010FA60(nSide);
        originalX = position & 0xFF;
        originalY = position >> 8;
        if (TaLogic_GetUnitWarning(originalX, originalY, pTask->ownerId, 3, value, 0) == 0) {
            out->id = pTask->ownerId;
            out->action = 6;
            out->position = position;
            out->mode = TaLogic_IsDefStyleUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, out->position, 1, 0);
            out->value = TaLogic_Weevil_IsOpenUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, pTask);
            TaLogic_InitRogicControl(pTask, fFirst);
            return 0;
        } else {
            result = GetMoveRange(SzDuel_GetUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF), originalX, originalY);
            if (result == 0) {
                out->id = pTask->ownerId;
                out->action = 6;
                out->position = position;
                out->mode = TaLogic_IsDefStyleUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, out->position, 1, 0);
                out->value = TaLogic_Weevil_IsOpenUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, pTask);
                TaLogic_InitRogicControl(pTask, fFirst);
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
                                value = (u16)score_0010FA60(nSide);
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
                        out->mode = TaLogic_IsDefStyleUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, out->position, 1, 0);
                    }
                    out->value = TaLogic_Weevil_IsOpenUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, pTask);
                } else {
                    out->id = pTask->ownerId;
                    out->action = 6;
                    out->position = position;
                    out->mode = TaLogic_IsDefStyleUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, out->position, 1, 0);
                    out->value = TaLogic_Weevil_IsOpenUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, pTask);
                }
                TaLogic_InitRogicControl(pTask, fFirst);
            }
        }
    }
    return 0;
}

typedef struct Result_0010FFF0 {
    u16 position;
    u8 kind;
    u8 pad3;
    u16 destination;
    u8 pad6[6];
    s32 action;
    u8 valid;
} Result_0010FFF0;

typedef struct Coord_0010FFF0 {
    u8 x : 4;
    u8 y : 4;
} Coord_0010FFF0;

/* The task's target square: the second half-word when the second argument is 1, else the first. */
static inline u32 target_0010FFF0(void *src, u8 mode) {
    if (mode == 1) {
        return (u16)(((UnitTask *)src)->goal.dwGoal >> 16);
    }
    return *(u16 *)((u8 *)src + 8);
}

/* This duelist's caution about hidden cards (an inline copy of its GetWarnHideLvl: by life points and monster
   count). */
static inline s32 flag_0010FFF0(s32 card) {
    if (SzDuel_GetLP(card) > 0x5DC) {
        if (SzDuel_GetUnitMonsterCount(card) >= 4) {
            return 0;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}

/* The board distance (steps across plus steps along). */
static inline s32 distance_0010FFF0(s32 x1, s32 y1, s32 x2, s32 y2) {
    return ((x2 < x1 ? x1 : x2) - (x1 < x2 ? x1 : x2)) +
           ((y2 < y1 ? y1 : y2) - (y1 < y2 ? y1 : y2));
}

/* Whether the first square is nearer to (x, y) than the second. */
static inline s32 closer_0010FFF0(Coord_0010FFF0 *candidate, Coord_0010FFF0 *best, s32 x, s32 y) {
    s32 bestMinY = best->y < y ? best->y : y;
    s32 bestMaxY = y < best->y ? best->y : y;
    s32 bestMinX = best->x < x ? best->x : x;
    s32 bestMaxX = x < best->x ? best->x : x;
    s32 candidateMinY = candidate->y < y ? candidate->y : y;
    s32 candidateMaxY = y < candidate->y ? candidate->y : y;
    s32 candidateMinX = candidate->x < x ? candidate->x : x;
    s32 candidateMaxX = x < candidate->x ? candidate->x : x;

    return (candidateMaxX - candidateMinX) + (candidateMaxY - candidateMinY) <
           (bestMaxX - bestMinX) + (bestMaxY - bestMinY);
}

/* Whether the unit of `src` can attack from (x1, y1) to (x2, y2) two steps away on a field that helps it. */
static inline s32 special_0010FFF0(void *src, s32 x1, s32 y1, s32 x2, s32 y2) {
    s32 x;
    s32 y;
    extern s32 SzDuel_GetUnitCardNo();

    x = ((UnitTask *)src)->ownerId & 0xFF;
    y = (s32)((UnitTask *)src)->ownerId >> 8;
    if (distance_0010FFF0(x1, y1, x2, y2) != 2) {
        return 0;
    } else if (SzDuel_GetUnit(y, x) == 0) {
        return 0;
    } else if (SzDuel_GetUnitCardNo(y, x) == 0x1A1) {
        return 0;
    } else if (SzDuel_GetUnitStatus(y, x, 0) == 0 &&
               CheckLandAgreement2(SzDuel_GetField(x1, y1), y, x) == 1) {
    } else {
        return 0;
    }
    return 1;
}

/* The task of a unit attacking (task `pTask`): its path to the goal, into `pInput`; -1 when it has none (`fFirst`
   = 1 for the unit's first-choice task). */
s32 TaLogic_Weevil_GetMinimumTask_AtkMission(void *pTask, s32 nSide, void *pInput, u8 fFirst) {
    s32 start;
    s32 best;
    s32 count;
    s32 action;
    s32 bestCost;
    Coord_0010FFF0 coords[12];
    s32 initial;
    s32 end;
    s32 i;
    Coord_0010FFF0 *p;
    u32 targetPosition;
    extern void TaLogic_GetInvadeRoot();
    extern s32 TaLogic_GetMinGoalCount();

    targetPosition = target_0010FFF0(pTask, fFirst);
    if (SzDuel_GetUnit(target_0010FFF0(pTask, fFirst) >> 8,
                     targetPosition & 0xFF) == 0) {
        TaLogic_InitRogicControl(pTask, 1);
        return -1;
    }
    initial = TaLogic_Weevil_IsOpenUnit((s32)((UnitTask *)pTask)->ownerId >> 8,
                          ((UnitTask *)pTask)->ownerId & 0xFF, pTask);
    start = SzDuel_GetUnitLoc((s32)((UnitTask *)pTask)->ownerId >> 8,
                         ((UnitTask *)pTask)->ownerId & 0xFF);
    targetPosition = target_0010FFF0(pTask, fFirst);
    end = SzDuel_GetUnitLoc(target_0010FFF0(pTask, fFirst) >> 8,
                       targetPosition & 0xFF);
    p = coords;
    i = 0;
    do {
        p->x = p->y = 15;
        i++;
        p++;
    } while (i < 12);
    if (GetMoveRange(SzDuel_GetUnit((s32)((UnitTask *)pTask)->ownerId >> 8,
                                   ((UnitTask *)pTask)->ownerId & 0xFF),
                     (start & 0xFF), (start >> 8)) == 0) {
        s32 cost;
        ((Result_0010FFF0 *)pInput)->position = ((UnitTask *)pTask)->ownerId;
        ((Result_0010FFF0 *)pInput)->kind = 6;
        ((Result_0010FFF0 *)pInput)->destination = start;
        cost = TaLogic_GetUnitWarning((start & 0xFF), (start >> 8), nSide, 3, 1, (u8)flag_0010FFF0(nSide));
        if (cost >= TaUtil_GetUnitAP((s32)((UnitTask *)pTask)->ownerId >> 8,
                                 ((UnitTask *)pTask)->ownerId & 0xFF, (start & 0xFF), (start >> 8))) {
            ((Result_0010FFF0 *)pInput)->valid = 1;
        } else {
            ((Result_0010FFF0 *)pInput)->valid = 0;
        }
        return 0;
    } else {
        s32 flag;
        flag = flag_0010FFF0(nSide);
        TaLogic_GetInvadeRoot((s32)((UnitTask *)pTask)->ownerId >> 8,
                     ((UnitTask *)pTask)->ownerId & 0xFF, coords,
                     (start & 0xFF), (start >> 8), (end & 0xFF), (end >> 8), target_0010FFF0(pTask, fFirst),
                     0, 30, (u16)flag);
        count = TaLogic_GetMinGoalCount(coords);
        if (count > 0) {
            bestCost = 0xFFFF;
            best = 0xFF;
            action = 0;
            for (i = 0; i < count; i++) {
                if (special_0010FFF0(pTask, (start & 0xFF), (start >> 8), (end & 0xFF), (end >> 8)) == 1) {
                    action = 1;
                    p = &coords[i];
                    best = i;
                    i = count;
                    p->x = (end & 0xFF);
                    p->y = (end >> 8);
                } else {
                    s32 cost;
                    cost = TaLogic_GetUnitWarning(coords[i].x, coords[i].y, nSide, 2, 1,
                                        (u8)flag_0010FFF0(nSide));
                    if (cost < bestCost) {
                        bestCost = cost;
                        best = i;
                    } else if (cost == bestCost) {
                        if (closer_0010FFF0(&coords[i], &coords[best], (end & 0xFF), (end >> 8))) {
                            bestCost = cost;
                            best = i;
                        }
                    }
                }
            }
        } else {
            ((Result_0010FFF0 *)pInput)->position = ((UnitTask *)pTask)->ownerId;
            ((Result_0010FFF0 *)pInput)->kind = 6;
            ((Result_0010FFF0 *)pInput)->destination = start;
            ((Result_0010FFF0 *)pInput)->action = initial;
            ((Result_0010FFF0 *)pInput)->valid = TaLogic_IsDefStyleUnit(
                (s32)((UnitTask *)pTask)->ownerId >> 8,
                ((UnitTask *)pTask)->ownerId & 0xFF,
                ((Result_0010FFF0 *)pInput)->destination, 0, 0);
            return 0;
        }
        if (best != 0xFF) {
            ((Result_0010FFF0 *)pInput)->position = ((UnitTask *)pTask)->ownerId;
            ((Result_0010FFF0 *)pInput)->kind = 6;
            ((Result_0010FFF0 *)pInput)->destination = (coords[best].y << 8) | coords[best].x;
            ((Result_0010FFF0 *)pInput)->action = action;
            ((Result_0010FFF0 *)pInput)->valid = TaLogic_IsDefStyleUnit(
                (s32)((UnitTask *)pTask)->ownerId >> 8,
                ((UnitTask *)pTask)->ownerId & 0xFF,
                ((Result_0010FFF0 *)pInput)->destination, 0, 0);
        } else {
            ((Result_0010FFF0 *)pInput)->position = ((UnitTask *)pTask)->ownerId;
            ((Result_0010FFF0 *)pInput)->kind = 6;
            ((Result_0010FFF0 *)pInput)->destination = start;
            ((Result_0010FFF0 *)pInput)->action = action;
            ((Result_0010FFF0 *)pInput)->valid = TaLogic_IsDefStyleUnit(
                (s32)((UnitTask *)pTask)->ownerId >> 8,
                ((UnitTask *)pTask)->ownerId & 0xFF,
                ((Result_0010FFF0 *)pInput)->destination, 0, 0);
            return 0;
        }
    }
    return 0;
}

typedef struct Position_001106F0 {
    u8 x : 4;
    u8 y : 4;
} Position_001106F0;

typedef struct Source_001106F0 {
    u16 id;
    u8 pad2[6];
    u32 target;
} Source_001106F0;

typedef struct Result_001106F0 {
    u16 id;
    u8 kind;
    u8 pad3;
    u16 target;
    u8 pad6[6];
    s32 value;
    u8 flags;
} Result_001106F0;

#define target_001106F0(src, side) ((side) == 1 ? ((((Source_001106F0 *)(src))->target >> 16) & 0xFFFF) : (u32)(u16)((Source_001106F0 *)(src))->target)

#define min_001106F0(a, b) ((a) < (b) ? (a) : (b))
#define max_001106F0(a, b) ((b) < (a) ? (a) : (b))
#define distance_001106F0(pos, src, side) \
    ((max_001106F0((u8)(pos).x, (u32)(u8)target_001106F0(src, side)) - \
      min_001106F0((u8)(pos).x, (u32)(u8)target_001106F0(src, side))) + \
     (max_001106F0((u8)(pos).y, (u32)target_001106F0(src, side) >> 8) - \
      min_001106F0((u8)(pos).y, (u32)target_001106F0(src, side) >> 8)))

/* This duelist's caution about hidden cards (an inline copy of its GetWarnHideLvl: by life points and monster
   count). */
static inline s32 scoreflag_001106F0(s32 id) {
    if (SzDuel_GetLP(id) > 0x5DC) {
        if (SzDuel_GetUnitMonsterCount(id) >= 4) {
            return 0;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}

/* The task of a unit moving to its goal (task `pTask`), into `pInput` (`fFirst` = 1 for the unit's first-choice
   task). */
s32 TaLogic_Weevil_GetMinimumTask_MoveMission(void *pTask, s32 nSide, void *pInput, u8 fFirst, u8 nKind) {
    extern void TaLogic_GetRoot();
    extern s32 TaLogic_IsDefStyleUnit(s32, s32, s32, u8, s32);
    Position_001106F0 positions[12];
    s32 start;
    s32 count;

    start = SzDuel_GetUnitLoc(((Source_001106F0 *)pTask)->id >> 8, ((Source_001106F0 *)pTask)->id & 0xFF);
    {
        s32 score;
        s32 best;
        s32 side = fFirst;
        Position_001106F0 *p;
        s32 i;
        if (target_001106F0(pTask, side) == 0xFFFF && start == target_001106F0(pTask, side)) {
            ((Result_001106F0 *)pInput)->id = ((Source_001106F0 *)pTask)->id;
            ((Result_001106F0 *)pInput)->kind = 6;
            ((Result_001106F0 *)pInput)->target = start;
            ((Result_001106F0 *)pInput)->flags = TaLogic_IsDefStyleUnit(((Source_001106F0 *)pTask)->id >> 8, ((Source_001106F0 *)pTask)->id & 0xFF, ((Result_001106F0 *)pInput)->target, nKind, 0);
            ((Result_001106F0 *)pInput)->value = TaLogic_Weevil_IsOpenUnit(((Source_001106F0 *)pTask)->id >> 8, ((Source_001106F0 *)pTask)->id & 0xFF, pTask);
            TaLogic_InitRogicControl(pTask, fFirst);
            return 0;
        }
        p = positions;
        {
            s32 clear_count = 0;
            Position_001106F0 *clear = p;
            s32 terrain;
            do {
                clear->x = clear->y = 15;
                clear_count++;
                clear++;
            } while (clear_count < 12);

            terrain = SzDuel_GetMapUnitID(target_001106F0(pTask, side) & 0xFF, (u32)target_001106F0(pTask, side) >> 8);
            if (terrain < 0) {
                terrain = 0xFFFF;
            }
            TaLogic_GetRoot(((Source_001106F0 *)pTask)->id >> 8, ((Source_001106F0 *)pTask)->id & 0xFF, positions,
                          start & 0xFF, start >> 8, target_001106F0(pTask, side) & 0xFF,
                          (u32)target_001106F0(pTask, side) >> 8, (u16)terrain, 7);
            count = TaLogic_GetMinGoalCount((u8 *)positions);
        }
        if (count > 0) {
            best = 0xFF;
            score = 0xFFFF;
            for (i = 0; i < count; i++, p++) {
                if (SzDuel_GetMapUnit(p->x, p->y) == 0) {
                    s32 value = TaLogic_GetUnitWarning(p->x, p->y, nSide, 2, 1, (u8)scoreflag_001106F0(nSide));
                    if (value < score) {
                        score = value;
                        best = i;
                    } else if (value == score) {
                        if (distance_001106F0(*p, pTask, side) < distance_001106F0(positions[best], pTask, side)) {
                            score = value;
                            best = i;
                        }
                    }
                }
            }
        } else {
            ((Result_001106F0 *)pInput)->id = ((Source_001106F0 *)pTask)->id;
            ((Result_001106F0 *)pInput)->kind = 6;
            ((Result_001106F0 *)pInput)->target = start;
            ((Result_001106F0 *)pInput)->flags = TaLogic_IsDefStyleUnit(((Source_001106F0 *)pTask)->id >> 8, ((Source_001106F0 *)pTask)->id & 0xFF, ((Result_001106F0 *)pInput)->target, nKind, 0);
            ((Result_001106F0 *)pInput)->value = TaLogic_Weevil_IsOpenUnit(((Source_001106F0 *)pTask)->id >> 8, ((Source_001106F0 *)pTask)->id & 0xFF, pTask);
            TaLogic_InitRogicControl(pTask, fFirst);
            return 0;
        }
        if (best != 0xFF) {
            ((Result_001106F0 *)pInput)->id = ((Source_001106F0 *)pTask)->id;
            ((Result_001106F0 *)pInput)->kind = 6;
            ((Result_001106F0 *)pInput)->target = (positions[best].y << 8) | positions[best].x;
            ((Result_001106F0 *)pInput)->flags = TaLogic_IsDefStyleUnit(((Source_001106F0 *)pTask)->id >> 8, ((Source_001106F0 *)pTask)->id & 0xFF, ((Result_001106F0 *)pInput)->target, nKind, 0);
            ((Result_001106F0 *)pInput)->value = TaLogic_Weevil_IsOpenUnit(((Source_001106F0 *)pTask)->id >> 8, ((Source_001106F0 *)pTask)->id & 0xFF, pTask);
        } else {
            ((Result_001106F0 *)pInput)->id = ((Source_001106F0 *)pTask)->id;
            ((Result_001106F0 *)pInput)->kind = 6;
            ((Result_001106F0 *)pInput)->target = start;
            ((Result_001106F0 *)pInput)->flags = TaLogic_IsDefStyleUnit(((Source_001106F0 *)pTask)->id >> 8, ((Source_001106F0 *)pTask)->id & 0xFF, ((Result_001106F0 *)pInput)->target, nKind, 0);
            ((Result_001106F0 *)pInput)->value = TaLogic_Weevil_IsOpenUnit(((Source_001106F0 *)pTask)->id >> 8, ((Source_001106F0 *)pTask)->id & 0xFF, pTask);
        }
        TaLogic_InitRogicControl(pTask, fFirst);
    }
    return 0;
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
} Req_00110F00;

typedef struct {
    u8 pad0[0x160];
    u16 list[32];    /* 0x160 */
    u8 idx : 5;      /* 0x1A0 */
    u8 pad1A0 : 3;
    u8 pad1A1;
    u16 count;       /* 0x1A2 */
} Work_00110F00;

s32 TaLogic_GetInputQueFromMinimumTask_b(void *, void *, s32);

/* Computer duelist 2's controller (duelistControllers[2]): the buttons it presses this frame. With an empty input
   queue it plans its next task and turns it into buttons, then plays the queue back one button per frame; after
   600 frames it gives up the turn (0x20, then 0x800). */
s32 duelistController02(s32 wCursorPos, void *pCtl) {
    Req_00110F00 req;
    Work_00110F00 *w;
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
        if (TaLogic_Weevil_GetMinimumTask(w, &req, wCursorPos) == 0) {
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

s32 TaLogic_GetNearCard2(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8,
                  s32 arg9);

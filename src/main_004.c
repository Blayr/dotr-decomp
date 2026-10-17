#include "common.h"

#pragma conditional_move off

/* This duelist's move: picks the next unit to act, gives it a task and turns that into input `pInput`; returns 1
   when it set one. */
s32 TaLogic_GetMinimumTask_0010C940(void *pCtl, void *pInput, s32 wCursorPos) {
    u16 *tasks = pCtl;
    s32 side;
    s32 found;
    s32 result;
    s32 index;

    side = SzDuel_GetTurnOwner();
    found = 0;
    if ((result = TaLogic_GetNextActiveUnit_0010D080(tasks, side, (s32)pInput)) < 0) {
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
    TaLogic_CommandUnit_0010CE20(tasks, tasks + index * 8);
    switch ((tasks[index * 8 + 2] >> 8) & 0xFF) {
    case 5:
        if (SzDuel_GetUnitStatus(tasks[index * 8] >> 8, tasks[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_RunMission_0010FA60(tasks + index * 8, side, pInput, 1);
            found = 1;
        }
        break;
    case 2:
        if (SzDuel_GetUnitStatus(tasks[index * 8] >> 8, tasks[index * 8] & 0xFF, 0) == 0) {
            if (TaLogic_GetMinimumTask_AtkMission_0010FFF0(tasks + index * 8, side, pInput, 1) < 0) {
                TaLogic_InitRogicControl(tasks + index * 8, 1);
                return 1;
            }
            found = 1;
        }
        break;
    case 10:
        if (TaLogic_GetMinimumTask_Summon_0010DD50(tasks[index * 8], side, (s32)pInput) < 0) {
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
            TaLogic_GetMinimumTask_MoveMission_001106F0(tasks + index * 8, side, pInput, 1, 0);
            found = 1;
        }
        break;
    case 3:
        if (SzDuel_GetUnitStatus(tasks[index * 8] >> 8, tasks[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_MoveMission_001106F0(tasks + index * 8, side, pInput, 1, 1);
            found = 1;
        }
        break;
    case 14:
        TaLogic_GetMinimumTask_DoNone(tasks + index * 8, side, pInput);
        found = 1;
        break;
    case 9:
        TaLogic_GetMinimumTask_EncMission(tasks + index * 8, side, pInput, 1, 0, TaLogic_GetWarnHideLvl_0010EDA0(side), 2, 1);
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
            TaLogic_GetMinimumTask_RunMission_0010FA60(tasks + index * 8, side, pInput, 0);
            found = 1;
        }
        break;
    case 2:
        if (SzDuel_GetUnitStatus(tasks[index * 8] >> 8, tasks[index * 8] & 0xFF, 0) == 0) {
            if (TaLogic_GetMinimumTask_AtkMission_0010FFF0(tasks + index * 8, side, pInput, 0) < 0) {
                TaLogic_GetMinimumTask_RunMission_0010FA60(tasks + index * 8, side, pInput, 0);
            }
            found = 1;
        }
        break;
    case 10:
        if (TaLogic_GetMinimumTask_Summon_0010DD50(tasks[index * 8], side, (s32)pInput) < 0) {
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
            TaLogic_GetMinimumTask_MoveMission_001106F0(tasks + index * 8, side, pInput, 0, 0);
            found = 1;
        }
        break;
    case 3:
        if (SzDuel_GetUnitStatus(tasks[index * 8] >> 8, tasks[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_MoveMission_001106F0(tasks + index * 8, side, pInput, 0, 1);
            found = 1;
        }
        break;
    case 14:
        TaLogic_GetMinimumTask_DoNone(tasks + index * 8, side, pInput);
        break;
    case 9:
        TaLogic_GetMinimumTask_EncMission(tasks + index * 8, side, pInput, 0, 0, TaLogic_GetWarnHideLvl_0010EDA0(side), 2, 1);
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

/* Gives the unit of task `pTask` its order for this turn (attack, run, move, summon, guard). */
s32 TaLogic_CommandUnit_0010CE20(u16 *pCtl, u16 *pTask) {
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
                            TaLogic_CommandEfcMonster_0010D880(entry, 1, state->level);
                        } else {
                            TaLogic_CommandBtlUnit_0010D490(entry, 1, state->level);
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
                        TaLogic_CommandEncUnit(entry, 2, 0, TaLogic_GetWarnHideLvl_0010EDA0(card) & 0xFF);
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
s32 TaLogic_GetNextActiveUnit_0010D080(u16 *pCtl, s32 nSide, s32 pInput) {
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
    TaLogic_CommandUnit_0010CE20(pCtl, pCtl + idx * 8);
    if (((pCtl[idx * 8 + 2] >> 8) & 0xFF) == 10) {
        if (SzDuel_InqHandPhase(nSide) == 1 && TaLogic_GetMinimumTask_Summon_0010DD50(pos, nSide, pInput) >= 0) {
            return pos | 0x10000;
        }
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_GetUnitStatus(nSide, 0, 0) == 0) {
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_InqHandPhase(nSide) == 1 && TaLogic_GetMinimumTask_Summon_0010DD50(pos, nSide, pInput) >= 0) {
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
void TaLogic_CommandBtlUnit_0010D490(void *pTask, s32 fGoalFirst, u8 bActive) {
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
                    other, (u8)i, TaLogic_GetWarnHideLvl_0010EDA0(side), entries, 0,
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
                    other, (u8)i, TaLogic_GetWarnHideLvl_0010EDA0(side), entries, 0,
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
void TaLogic002_GetNearUnit(s32 pTask, s32 pTree, s32 pVarInfo, s32 nX, s32 nZ, s32 eSide, s32 bDist, s32 WarnLvl, s32 nUnitLst, u16 wUnitNum, s32 wSize, s32 wNodeCount, u8 bChase, s32 wIgnoreLst) {
    TaLogic_GetNearUnit(pTask, pTree, pVarInfo, nX, nZ, eSide, bDist, WarnLvl,
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
void TaLogic_CommandEfcMonster_0010D880(void *pTask, s32 fGoalFirst, u8 bActive) {
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
                    owner == 0 ? 1 : 0, (u8)attempt, TaLogic_GetWarnHideLvl_0010EDA0(owner),
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
                TaLogic_CommandBtlUnit_0010D490(pTask, 1, bActive);
            }
            break;
        case 0x198:
            if (SzDuel_GetLP(owner) < 1000) {
                TaLogic_CommandDefenseUnit(pTask, 0, 0);
            }
            TaLogic_CommandBtlUnit_0010D490(pTask, 1, bActive);
            break;
        default:
            TaLogic_CommandBtlUnit_0010D490(pTask, 1, bActive);
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
s32 TaLogic_GetMinimumTask_Summon_0010DD50(s32 wUnit, s32 nSide, s32 pInput) {
    extern s32 TaLogic_IsHandPlay_0010DFC0();
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
    kind = TaLogic_IsHandPlay_0010DFC0(nSide, work);
    if (kind == -1) {
        return -1;
    }
    *(u8 *)(ctx + 2) = 10;
    *(s32 *)(ctx + 0xC) = 0;
    pos = SzDuel_GetUnitLoc(wUnit >> 8, wUnit & 0xFF);
    if (kind == 0) {
        if (TaLogic_SetComboQue_0010E320(nSide, ctx, work) >= 0) {
            ret = TaLogic_GetNearCard2(work, pos & 0xFF, pos >> 8,
                                nSide == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0,
                                TaLogic_GetWarnHideLvl_0010EDA0(nSide));
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
                            TaLogic_GetWarnHideLvl_0010EDA0(nSide));
    }
    if (kind == 2) {
        TaLogic_SetSpecialComboQue_0010E540(nSide, ctx, (s32)work, 0);
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
s32 TaLogic_IsHandPlay_0010DFC0(s32 nSide, void *pInput) {
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
                    TaHand_IsCardSummon2(nSide, *first_entry) == 1) {
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
                    TaHand_IsCardSummon2(nSide, *zero_entry) == 1) {
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
                    TaHand_IsCardSummon2(nSide, *check_entry) == 1) {
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
                TaHand_IsCardSummon2(nSide, *last_entry) == 1) {
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
s32 TaLogic_SetComboQue_0010E320(s32 nSide, u8 *bCombo, void *pCardInfo) {
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
                            TaLogic_ConvEmptyCombo_0010E6B0(nSide, *node, entries);
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
s32 TaLogic_SetSpecialComboQue_0010E540(s32 nSide, void *bCombo, s32 pCardInfo, s32 nOpt) {
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
void TaLogic_ConvEmptyCombo_0010E6B0(s32 nSide, void *pCardInfo, s32 *pResult) {
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
            lvl = TaLogic_GetWarnHideLvl_0010EDA0(nSide);
            here_y = here >> 8;
            here_x = here & 0xff;
            inv = func_00278510_b(block, nMode, lvl, here_x, here_y, 0);
            for (i = 0; i < 8; i++) {
                if ((spot = TaLogic_GetSommonPiecePreference_0010ED90(nSide, i)) >= 0) {
                    x = spot & 0xff;
                    y = spot >> 8;
                    field = SzDuel_GetField(x, y);
                    if (field != 8) {
                        if (func_001E36E0_b(x, y) == 0) {
                            if (field != 9 || Ta_IsVirus_Chk3(block, x, y) != 1) {
                                for (j = 0, p = bytes; j < 12; j++, p++) p->low = p->high = 0xf;
                                if (inv >= 0) {
                                    cost = func_0027A130_b(block, bytes, x, y, here_x, here_y, nMode, 0, 2, (unsigned short)TaLogic_GetWarnHideLvl_0010EDA0(nSide));
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
                    if ((near_at = TaLogic_GetSommonPiecePreference_0010ED90(nSide, j)) >= 0) {
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
        if ((free_spot = TaLogic_GetSommonPiecePreference_0010ED90(nSide, m)) >= 0) {
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
s32 TaLogic_GetSommonPiecePreference_0010ED90(s32 nSide, u32 nPr) {
    return Ta_GetSommonPiecePreference(nSide, nPr);
}

/* How careful this duelist is about hidden cards (by its life points and monster count). */
s32 TaLogic_GetWarnHideLvl_0010EDA0(s32 nSide) {
    if (SzDuel_GetLP(nSide) > 0x5DC) {
        if (SzDuel_GetUnitMonsterCount(nSide) >= 4) {
            return 0;
        }
        return 0;
    }
    return 0;
}

/* Whether this duelist opens (turns face up) unit (nSide, nID) now: 0 no, 1 or 2 by its kind. */
s32 TaLogic_IsOpenUnit_0010EE00(s32 nSide, s32 nID, u32 *pInfo) {
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
s32 TaLogic_GetMinimumTask_RunMission_0010FA60(u16 *pTask, s32 nSide, void *pInput, u8 fFirst) {
    extern s32 TaLogic_GetUnitWarning(s32, s32, s32, s32, s32, u8);
    extern s32 TaLogic_IsRunPassRoot(s32, s32, s32, s32, s32, s32, void *, u8);
    extern s32 TaLogic_IsOpenUnit_0010EE00();
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

    position = SzDuel_GetUnitLoc(*pTask >> 8, *pTask & 0xFF);
    i = 0;
    do {
        cells[i].low = cells[i].high = 15;
        i++;
    } while (i < 12);

    {
        u16 value = (u16)score_0010FA60(nSide);
        originalX = position & 0xFF;
        originalY = position >> 8;
        if (TaLogic_GetUnitWarning(originalX, originalY, *pTask, 3, value, 0) == 0) {
            out->id = *pTask;
            out->action = 6;
            out->position = position;
            out->mode = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, out->position, 1, 0);
            out->value = TaLogic_IsOpenUnit_0010EE00(*pTask >> 8, *pTask & 0xFF, pTask);
            TaLogic_InitRogicControl(pTask, fFirst);
            return 0;
        } else {
            result = GetMoveRev(SzDuel_GetUnit(*pTask >> 8, *pTask & 0xFF), originalX, originalY);
            if (result == 0) {
                out->id = *pTask;
                out->action = 6;
                out->position = position;
                out->mode = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, out->position, 1, 0);
                out->value = TaLogic_IsOpenUnit_0010EE00(*pTask >> 8, *pTask & 0xFF, pTask);
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
                                value = (u16)score_0010FA60(nSide);
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
                    out->value = TaLogic_IsOpenUnit_0010EE00(*pTask >> 8, *pTask & 0xFF, pTask);
                } else {
                    out->id = *pTask;
                    out->action = 6;
                    out->position = position;
                    out->mode = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, out->position, 1, 0);
                    out->value = TaLogic_IsOpenUnit_0010EE00(*pTask >> 8, *pTask & 0xFF, pTask);
                }
                TaLogic_InitRogicControl(pTask, fFirst);
            }
        }
    }
    return 0;
}

typedef struct Source_0010FFF0 {
    u16 position;
    u8 pad2[6];
    u32 targets;
} Source_0010FFF0;

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
        return (u16)(((Source_0010FFF0 *)src)->targets >> 16);
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

    x = ((Source_0010FFF0 *)src)->position & 0xFF;
    y = (s32)((Source_0010FFF0 *)src)->position >> 8;
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
s32 TaLogic_GetMinimumTask_AtkMission_0010FFF0(void *pTask, s32 nSide, void *pInput, u8 fFirst) {
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
    initial = TaLogic_IsOpenUnit_0010EE00((s32)((Source_0010FFF0 *)pTask)->position >> 8,
                          ((Source_0010FFF0 *)pTask)->position & 0xFF, pTask);
    start = SzDuel_GetUnitLoc((s32)((Source_0010FFF0 *)pTask)->position >> 8,
                         ((Source_0010FFF0 *)pTask)->position & 0xFF);
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
    if (GetMoveRev(SzDuel_GetUnit((s32)((Source_0010FFF0 *)pTask)->position >> 8,
                                   ((Source_0010FFF0 *)pTask)->position & 0xFF),
                     (start & 0xFF), (start >> 8)) == 0) {
        s32 cost;
        ((Result_0010FFF0 *)pInput)->position = ((Source_0010FFF0 *)pTask)->position;
        ((Result_0010FFF0 *)pInput)->kind = 6;
        ((Result_0010FFF0 *)pInput)->destination = start;
        cost = TaLogic_GetUnitWarning((start & 0xFF), (start >> 8), nSide, 3, 1, (u8)flag_0010FFF0(nSide));
        if (cost >= TaUtil_GetUnitAP((s32)((Source_0010FFF0 *)pTask)->position >> 8,
                                 ((Source_0010FFF0 *)pTask)->position & 0xFF, (start & 0xFF), (start >> 8))) {
            ((Result_0010FFF0 *)pInput)->valid = 1;
        } else {
            ((Result_0010FFF0 *)pInput)->valid = 0;
        }
        return 0;
    } else {
        s32 flag;
        flag = flag_0010FFF0(nSide);
        TaLogic_GetInvadeRoot((s32)((Source_0010FFF0 *)pTask)->position >> 8,
                     ((Source_0010FFF0 *)pTask)->position & 0xFF, coords,
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
            ((Result_0010FFF0 *)pInput)->position = ((Source_0010FFF0 *)pTask)->position;
            ((Result_0010FFF0 *)pInput)->kind = 6;
            ((Result_0010FFF0 *)pInput)->destination = start;
            ((Result_0010FFF0 *)pInput)->action = initial;
            ((Result_0010FFF0 *)pInput)->valid = TaLogic_IsDefStyleUnit(
                (s32)((Source_0010FFF0 *)pTask)->position >> 8,
                ((Source_0010FFF0 *)pTask)->position & 0xFF,
                ((Result_0010FFF0 *)pInput)->destination, 0, 0);
            return 0;
        }
        if (best != 0xFF) {
            ((Result_0010FFF0 *)pInput)->position = ((Source_0010FFF0 *)pTask)->position;
            ((Result_0010FFF0 *)pInput)->kind = 6;
            ((Result_0010FFF0 *)pInput)->destination = (coords[best].y << 8) | coords[best].x;
            ((Result_0010FFF0 *)pInput)->action = action;
            ((Result_0010FFF0 *)pInput)->valid = TaLogic_IsDefStyleUnit(
                (s32)((Source_0010FFF0 *)pTask)->position >> 8,
                ((Source_0010FFF0 *)pTask)->position & 0xFF,
                ((Result_0010FFF0 *)pInput)->destination, 0, 0);
        } else {
            ((Result_0010FFF0 *)pInput)->position = ((Source_0010FFF0 *)pTask)->position;
            ((Result_0010FFF0 *)pInput)->kind = 6;
            ((Result_0010FFF0 *)pInput)->destination = start;
            ((Result_0010FFF0 *)pInput)->action = action;
            ((Result_0010FFF0 *)pInput)->valid = TaLogic_IsDefStyleUnit(
                (s32)((Source_0010FFF0 *)pTask)->position >> 8,
                ((Source_0010FFF0 *)pTask)->position & 0xFF,
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
s32 TaLogic_GetMinimumTask_MoveMission_001106F0(void *pTask, s32 nSide, void *pInput, u8 fFirst, u8 nKind) {
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
            ((Result_001106F0 *)pInput)->value = TaLogic_IsOpenUnit_0010EE00(((Source_001106F0 *)pTask)->id >> 8, ((Source_001106F0 *)pTask)->id & 0xFF, pTask);
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
            ((Result_001106F0 *)pInput)->value = TaLogic_IsOpenUnit_0010EE00(((Source_001106F0 *)pTask)->id >> 8, ((Source_001106F0 *)pTask)->id & 0xFF, pTask);
            TaLogic_InitRogicControl(pTask, fFirst);
            return 0;
        }
        if (best != 0xFF) {
            ((Result_001106F0 *)pInput)->id = ((Source_001106F0 *)pTask)->id;
            ((Result_001106F0 *)pInput)->kind = 6;
            ((Result_001106F0 *)pInput)->target = (positions[best].y << 8) | positions[best].x;
            ((Result_001106F0 *)pInput)->flags = TaLogic_IsDefStyleUnit(((Source_001106F0 *)pTask)->id >> 8, ((Source_001106F0 *)pTask)->id & 0xFF, ((Result_001106F0 *)pInput)->target, nKind, 0);
            ((Result_001106F0 *)pInput)->value = TaLogic_IsOpenUnit_0010EE00(((Source_001106F0 *)pTask)->id >> 8, ((Source_001106F0 *)pTask)->id & 0xFF, pTask);
        } else {
            ((Result_001106F0 *)pInput)->id = ((Source_001106F0 *)pTask)->id;
            ((Result_001106F0 *)pInput)->kind = 6;
            ((Result_001106F0 *)pInput)->target = start;
            ((Result_001106F0 *)pInput)->flags = TaLogic_IsDefStyleUnit(((Source_001106F0 *)pTask)->id >> 8, ((Source_001106F0 *)pTask)->id & 0xFF, ((Result_001106F0 *)pInput)->target, nKind, 0);
            ((Result_001106F0 *)pInput)->value = TaLogic_IsOpenUnit_0010EE00(((Source_001106F0 *)pTask)->id >> 8, ((Source_001106F0 *)pTask)->id & 0xFF, pTask);
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
        if (TaLogic_GetMinimumTask_0010C940(w, &req, wCursorPos) == 0) {
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

#define MAX_001110D0(a, b) ((a) > (b) ? (a) : (b))
#define MIN_001110D0(a, b) ((a) < (b) ? (a) : (b))

/* The unit of side `nSide` controlled by the opponent that this duelist wants back. */
s32 TaLogicCom_GetRevoltObj_001110D0(s32 nSide) {
    extern s32 SzDuel_GetUnitCurseRest(s32, s32);
    extern s32 SzDuel_GetUnitSpellRest(s32, s32);
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

    pos = SzDuel_GetUnitLoc(nSide == 0 ? 1 : 0, 0);
    if (Ta_SearchUncTypeNaturalEffectUserNum(0x39) > 0) {
        return -1;
    }
    obj = Ta_RemoveObjFromFlagLst(SearchUnitByRange(0, 0, nSide, 2, 0x21, 0xE), nSide);
    p = list;
    for (i = 0; i < 22; i++) {
        p[i] = 0xFFFF;
    }
    TaLogic_GetUnitCtlLst(nSide == 0 ? 1 : 0, list, 0x34, 0);
    found = -1;
    bestPos = found;
    best = 1;
    i = 0;
    if (i < TaLogic_GetUnitCtlLstLen(list)) {
        x0 = pos >> 8;
        y0 = pos & 0xFF;
        do {
            cur = SzDuel_GetUnitLoc(*p >> 8, *p & 0xFF);
            x = cur >> 8;
            y = cur & 0xFF;
            if (MAX_001110D0(y0, y) - MIN_001110D0(y0, y) + (MAX_001110D0(x0, x) - MIN_001110D0(x0, x)) == 1) {
                if (SzDuel_GetUnitStatus(*p >> 8, *p & 0xFF, 1) == 0 &&
                    SzDuel_GetUnitCurseRest(*p >> 8, *p & 0xFF) == 0 &&
                    SzDuel_GetUnitSpellRest(*p >> 8, *p & 0xFF) == 0) {
                    if ((score = TaUtil_GetUnitAP(*p >> 8, *p & 0xFF, y, x)) >= best) {
                        bestPos = *p;
                        if (bestPos == Ta_GetUnitOwnerIDFromLstCount(obj, 0)) {
                            found = bestPos;
                        }
                        best = score;
                    }
                }
            }
            p++;
            i++;
        } while (i < TaLogic_GetUnitCtlLstLen(list));
    }
    if (bestPos < 0) {
        return -1;
    }
    return ((u16)bestPos << 16) | (u16)found;
}

/* Whether this duelist opens (turns face up) unit (nSide, nID) now: 0 no, 1 or 2 by its kind. */
s32 TaLogicCom_IsOpenUnit_00111320(s32 nSide, s32 nID) {
    s16 buffer[24];
    s32 mask;
    s32 count;
    s32 owner;
    u32 *effect;
    s32 card;
    s32 position;
    s32 unit;
    extern s32 SzDuel_GetUnitCardNo();
    extern s32 SzDuel_GetUnitCurseRest();
    extern s32 SzDuel_GetGraveCount();
    extern s32 SzData_GetRank();

    mask = 0;
    count = 0;
    card = SzDuel_GetUnitCardNo();
    position = SzDuel_GetUnitLoc(nSide, nID);
    owner = Ta_IsUnitControl(nSide, nID);
    effect = SzDuel_GetUnitEffect(nSide, nID, 0);
    TaUtil_GetUnitLst(owner, 2, buffer);
    if (SzDuel_GetUnitStatus(nSide, nID, 4) != 0) {
        return 0;
    }
    if (TaLogicCom_IsExzParts_00112960(card) == 1) {
        if (TaLogic_IsTactixExz_00112980(owner) == 1 && TaLogic_IsExzodia_00112A40(owner) == 4) {
            return 1;
        }
    }
    switch (SzDuel_GetUnitKind(nSide, nID) >> 5) {
    case 5:
        if (TaLogic_GetActionReaction(nSide, nID, 0, 0, 6, 0) == 5) {
            return 2;
        }
        if (TaLogicCom_IsDoCerem_00112850(Ta_IsUnitControl(nSide, nID), card) == 1 &&
            SzDuel_GetField(position & 0xFF, position >> 8) != 9) {
            return 1;
        }
        break;
    case 1:
        if (TaLogic_GetActionReaction(nSide, nID, 0, 0, 6, 0) == 5) {
            return 2;
        }
        if (effect == NULL) {
            return 2;
        }
        switch (effect[0] >> 8) {
        case 0x17:
        case 0x49:
            if (TaLogicCom_IsUseObjEffect_001123C0(owner, (effect[0] >> 6) & 3, effect[0] & 0x3F) == 1) {
                return 1;
            }
            break;
        case 0x18:
        {
            s32 index;
            mask = SearchUnitByRange(0, 0, owner, 2, 0x34, 0xE);
            for (index = 0; index < Ta_GetUnitNumFrom22bitFlagList(mask); index++) {
                unit = Ta_GetUnitOwnerIDFromLstCount(mask, index);
                if (SzDuel_GetUnitStatus(unit >> 8, unit & 0xFF, 4) == 1) {
                    count++;
                }
            }
            if (count > 5) {
                return 1;
            }
            break;
        }
        case 2:
            unit = TaLogic_GetLandChange(SzDuel_GetUnit(nSide, nID), position & 0xFF,
                                position >> 8, *((u8 *)effect + 4), 8, 2);
            if (unit >= 0 && unit == position) {
                return 1;
            }
            break;
        case 4:
            switch (effect[1] >> 16) {
            case 0x12:
                unit = TaLogicCom_GetUseXYRangeSpell_00112600(nSide, (s32 *)effect);
                if (unit >= 0 && ((position & 0xFF) == (unit & 0xFF) ||
                                  (position >> 8) == (unit >> 8))) {
                    return 1;
                }
                break;
            case 0x13:
            default:
                if (TaLogicCom_IsUseObjEffect_001123C0(owner, (effect[0] >> 6) & 3, effect[0] & 0x3F) == 1) {
                    return 1;
                }
                break;
            }
            break;
        case 0xD:
            if (((effect[0] >> 6) & 3) == 1) {
                if ((effect[1] >> 16) == 4) {
                    if (SzDuel_GetLP(owner) <= 1200) {
                        return 1;
                    }
                    break;
                }
                return 1;
            }
            if ((effect[0] & 0x3F) == 0x32) {
                if (Ta_GetUnitNum(owner == 0 ? 1 : 0, 3) > 3) {
                    return 1;
                }
                break;
            }
            return 1;
        case 0x1F:
            if (card == 0x2DD && TaLogicCom_GetRevoltObj_001110D0(owner) >= 0) {
                return 1;
            }
            break;
        case 0x20:
            mask = 0;
            do {
                if (SzDuel_GetUnitCurseRest(nSide, mask) == 0xFF) {
                    return 1;
                }
                mask++;
            } while (mask < 11);
            break;
        case 0x12:
            if (Ta_GetUnitNumFrom22bitFlagList(SearchUnitByRange(0, 0, owner, 1, effect[0] & 0x3F, 0xE)) > 2) {
                return 1;
            }
            break;
        case 0x21:
            {
                s32 targetPosition;
                s32 sourcePosition;
                s32 targetY;

                TaLogic_GetUnitCtlLst2(owner == 0 ? 1 : 0, (u16 *)buffer, 0x1D, 0, 0);
                unit = TaLogic_GetMaxApUnit((u16 *)buffer);
                nSide = unit >> 8;
                nID = unit & 0xFF;
                sourcePosition = SzDuel_GetUnitLoc(nSide, nID);
                TaLogic_GetUnitCtlLst(owner, (u16 *)buffer, 0x1D, 1);
                unit = TaLogic_GetMaxApUnit((u16 *)buffer);
                card = unit >> 8;
                targetY = unit & 0xFF;
                targetPosition = SzDuel_GetUnitLoc(card, targetY);
                TaUtil_GetUnitLst(owner, 1, buffer);
                owner = sourcePosition & 0xFF;
                count = sourcePosition >> 8;
                if (TaUtil_GetUnitAP(nSide, nID, owner, count) >= 3000) {
                    count = TaUtil_GetUnitAP(nSide, nID, owner, count);
                    if (TaUtil_GetUnitAP(card, targetY, targetPosition & 0xFF, targetPosition >> 8) < count) {
                        return 1;
                    }
                }
            }
            break;
        case 0x36:
            return 1;
        case 0x25:
            switch (effect[0] & 0x3F) {
            case 0x21:
                if (TaLogic_IsAttackedNow(nSide, nID, 0) == 1) {
                    return 1;
                }
                break;
            case 0x22:
                if (TaLogic_IsAttackedNow(owner, 0, 0) == 1) {
                    return 1;
                }
                break;
            case 0x34:
            default:
                if (TaLogic_IsAttackedNow(owner, 0, 0) == 1) {
                    return 1;
                }
                break;
            }
            break;
        case 0x26:
            if (SzDuel_InqHandPhase(owner) == 0) {
                return 1;
            }
            break;
        case 0x27:
            if (SzDuel_GetSummonPower(owner) < 4) {
                return 1;
            }
            break;
        case 0x28:
            if (TaLogic_IsAttackedNow(owner, 0, 0) == 1) {
                return 1;
            }
            break;
        }
        break;
    case 0:
        if (TaUtil_IsExMonster(nSide, nID) == 0) {
            return 2;
        }
        effect = Ta_GetUnitEffect(nSide, nID, 2);
        if (effect == NULL) {
            return 2;
        }
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
            return 1;
        case 0xB:
        case 0x4E:
        case 0x12:
        case 0x4D:
        case 6:
            mask = SearchUnitByRange(0, 0, nSide, 1, effect[0] & 0x3F, 0xE);
            if ((u32)mask > 1) {
                return 1;
            }
            break;
        case 0x13:
        case 0x17:
            if (((effect[0] >> 6) & 1) && SearchUnitByRange(0, 0, nSide, 1, effect[0] & 0x3F, 0xE)) {
                return 2;
            }
            mask = TaLogic_RemoveHideUnit(SearchUnitByRange(0, 0, nSide, 2, effect[0] & 0x3F, 0xE));
            if ((u32)mask > 2) {
                return 1;
            }
            break;
        case 0x47:
        {
            s32 y;
            s32 x;
            s32 index;
            mask = SearchUnitByRange(0, 0, nSide, 2, 0x34, 0xE);
            for (index = 0; index < Ta_GetUnitNumFrom22bitFlagList(mask); index++) {
                unit = Ta_GetUnitOwnerIDFromLstCount(mask, index);
                x = unit >> 8;
                y = unit & 0xFF;
                if (SzDuel_GetUnitCurseRest(x, y) > 0 && SzDuel_GetUnitCurseRest(x, y) != 0xFF) {
                    return 1;
                }
            }
            break;
        }
        case 0x53:
        {
            s32 index;
            for (index = 0; index < SzDuel_GetGraveCount(nSide); index++) {
                if ((TaHand_GetCardKind(SzDuel_InqGrave(nSide, index)) >> 5) == 0) {
                    count++;
                }
            }
            for (index = 0; index < SzDuel_GetGraveCount(nSide == 0 ? 1 : 0); index++) {
                if ((TaHand_GetCardKind(SzDuel_InqGrave(nSide == 0 ? 1 : 0, index)) >> 5) == 0) {
                    count++;
                }
            }
            if (count > 5) {
                return 1;
            }
            break;
        }
        case 0x54:
            mask = SearchUnitByRange(0, 0, nSide, 3, 0x21, 0xE);
            unit = Ta_GetUnitOwnerIDFromLstCount(mask, 0);
            if (nSide == Ta_IsUnitControl(unit >> 8, unit & 0xFF) && unit != ((nSide << 8) | nID)) {
                return 1;
            }
            break;
        case 0x55:
        {
            s32 y;
            s32 x;
            s32 index;
            mask = SearchUnitByRange(0, 0, nSide, 1, 0x34, 0xE);
            for (index = 0; index < Ta_GetUnitNumFrom22bitFlagList(mask); index++) {
                unit = Ta_GetUnitOwnerIDFromLstCount(mask, index);
                x = unit >> 8;
                y = unit & 0xFF;
                if (SzDuel_GetUnitCurseRest(x, y) > 0 && SzDuel_GetUnitCurseRest(x, y) != 0xFF) {
                    return 1;
                }
            }
            break;
        }
        case 0x58:
            if (SzData_GetRank(nSide == 0 ? 1 : 0, SzDuel_GetUnitCardNo(nSide == 0 ? 1 : 0, 0)) >= 6) {
                return 1;
            }
            break;
        }
        effect = Ta_GetUnitEffect(nSide, nID, 3);
        if (effect == NULL) {
            return 2;
        }
        switch (effect[0] >> 8) {
        case 0x12:
            if ((effect[1] >> 16) == 0x16) {
                unit = SearchUnitByRange(0, 0, owner, 1, effect[0] & 0x3F, 0x16);
            } else {
                unit = SearchUnitByRange(0, 0, owner, 1, ((effect[1] >> 16) << 16) | (effect[0] & 0x3F), 0xE);
            }
            if (Ta_GetUnitNumFrom22bitFlagList(unit) > 2) {
                return 1;
            }
            break;
        case 0x33:
            if (Ta_GetUnitNumFrom22bitFlagList(SearchUnitByRange(0, 0, owner, 1, ((effect[1] >> 16) << 16) | (effect[0] & 0x3F), 0xE)) > 2) {
                return 1;
            }
            break;
        case 0x17:
            if ((effect[0] & 0x3F) == 0x1A) {
                return 2;
            }
            if (TaLogicCom_IsUseObjEffect_001123C0(owner, (effect[0] >> 6) & 3, effect[0] & 0x3F) == 1) {
                return 1;
            }
            break;
        case 0xD:
            return 1;
        case 0x23:
            if (TaLogicCom_IsUseObjEffect_001123C0(owner, (effect[0] >> 6) & 3, effect[0] & 0x3F) == 1) {
                return 1;
            }
            break;
        case 0x18:
        {
            s32 targets;
            s32 index;

            targets = SearchUnitByRange(0, 0, owner, 1, effect[0] & 0x3F, 0xE);
            for (index = 0; index < Ta_GetUnitNumFrom22bitFlagList(targets); index++) {
                unit = Ta_GetUnitOwnerIDFromLstCount(targets, index);
                if (SzDuel_GetUnitStatus(unit >> 8, unit & 0xFF, 4) == 1) {
                    count++;
                }
            }
            if (count > 2) {
                return 2;
            }
            {
                s32 unavailable;
                s32 others;
                s32 otherIndex;

                unavailable = 0;
                others = SearchUnitByRange(0, 0, owner, 2, effect[0] & 0x3F, 0xE);
                for (otherIndex = 0; otherIndex < Ta_GetUnitNumFrom22bitFlagList(others); otherIndex++) {
                    unit = Ta_GetUnitOwnerIDFromLstCount(others, otherIndex);
                    if (SzDuel_GetUnitStatus(unit >> 8, unit & 0xFF, 4) == 1) {
                        unavailable++;
                    }
                }
                if (unavailable > 5) {
                    return 1;
                }
            }
            break;
        }
        case 4:
        {
            s32 y;
            s32 x;
            s32 index;
            if ((effect[0] & 0x3F) == 0x1A) {
                return 2;
            }
            if ((effect[0] & 0x3F) == 0x30) {
                if (TaLogicCom_IsUseObjEffect_001123C0(owner, (effect[0] >> 6) & 3, effect[0] & 0x3F) == 1) {
                    return 1;
                }
            } else {
                if ((effect[1] >> 16) != 0) {
                    unit = SzDuel_GetUnitLoc(nSide, nID);
                    mask = SearchUnitByRange(unit & 0xFF, unit >> 8, owner, (effect[0] >> 6) & 3,
                                        effect[0] & 0x3F, effect[1] >> 16);
                } else {
                    mask = SearchUnitByRange(0, 0, owner, (effect[0] >> 6) & 3, effect[0] & 0x3F, 0xE);
                }
            }
            for (index = 0; index < Ta_GetUnitNumFrom22bitFlagList(mask); index++) {
                unit = Ta_GetUnitOwnerIDFromLstCount(mask, index);
                x = unit >> 8;
                y = unit & 0xFF;
                if (owner == Ta_IsUnitControl(x, y)) {
                    return 2;
                }
                if (SzDuel_GetUnitStatus(x, y, 4) != 0) {
                    count++;
                }
            }
            if (count > 1) {
                return 1;
            }
            break;
        }
        case 0x1A:
            if (SzDuel_GetSummonPower(nSide) < 4) {
                return 1;
            }
            break;
        case 0x26:
            if (SzDuel_InqHandPhase(owner) == 0) {
                return 1;
            }
            break;
        case 0x1F:
            if (Ta_SearchUncTypeNaturalEffectUserNum(0x39) > 0) {
                return 2;
            }
            if ((effect[0] & 0x3F) == 0x1A) {
                return 2;
            }
            if (Ta_GetUnitNumFrom22bitFlagList(SearchUnitByRange(0, 0, owner, (effect[0] >> 6) & 3, effect[0] & 0x3F, 0xE)) > 2) {
                return 1;
            }
            break;
        case 0x3C:
            if (SearchUnitByRange(position & 0xFF, position >> 8, owner, 1,
                             ((u32)*((u16 *)effect + 2) << 16) | (effect[0] & 0x3F), 1) &&
                Ta_GetSummonablePiece(owner == 0 ? 1 : 0, 1) >= 0) {
                return 1;
            }
            break;
        case 0x46:
            if (TaLogic_IsAttackedNow(owner, 0, 0) == 1) {
                return 1;
            }
            break;
        case 0xC:
            return 1;
        case 0x57:
            if (SzDuel_GetHandCount(owner) == 0) {
                return 1;
            }
            break;
        }
        break;
    default:
        break;
    }
    return 2;
}

/* Whether using unit (nSide, nID)'s effect now hits enough targets (`sKey`). */
s32 TaLogicCom_IsUseObjEffect_001123C0(s32 nSide, s32 nID, s32 sKey) {
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
    list = SearchUnitByRange(0, 0, nSide, nID, sKey, 14);
    for (i = 0; i < Ta_GetUnitNumFrom22bitFlagList(list); i++) {
        card = Ta_GetUnitOwnerIDFromLstCount(list, i);
        hi = card >> 8;
        lo = card & 0xFF;
        if (nSide == Ta_IsUnitControl(hi, lo)) {
            value = TaUtil_GetUnitAP(hi, lo, SzDuel_GetUnitLoc(hi, lo) & 0xFF, SzDuel_GetUnitLoc(hi, lo) >> 8);
            if (best_own < value) {
                best_own = value;
            }
        } else {
            value = TaUtil_GetUnitAP(hi, lo, SzDuel_GetUnitLoc(hi, lo) & 0xFF, SzDuel_GetUnitLoc(hi, lo) >> 8);
            if (best_other < value) {
                best_other = value;
            }
        }
    }
    if (best_own < best_other && best_other > 3000) {
        return 1;
    }
    if (nID & 1) {
        if (Ta_GetUnitNumFrom22bitFlagList(SearchUnitByRange(0, 0, nSide, 1, sKey, 14)) > 0) {
            return 0;
        }
    }
    if (nID >> 1) {
        if (Ta_GetUnitNumFrom22bitFlagList(SearchUnitByRange(0, 0, nSide, 2, sKey, 14)) > 3) {
            return 1;
        }
    }
    return 0;
}

/* The square where side `nSide`'s range magic hits most, into `pLoc`. */
s32 TaLogicCom_GetUseXYRangeSpell_00112600(s32 nSide, s32 *pLoc) {
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
    switch (*pLoc & 0x3F) {
    case 0x1D:
        TaLogic_GetUnitCtlLst2((nSide == 0) ? 1 : 0, cells, 0x1D, 0, 0);
        first = TaLogic_GetMaxApUnit(cells);
        for (j = 0; j < 0x16; j++) {
            cells[j] = 0xFFFF;
        }
        TaLogic_GetUnitCtlLst(nSide, cells, 0x1D, 1);
        second = TaLogic_GetMaxApUnit(cells);
        if (first >= 0 && second >= 0) {
            pos = SzDuel_GetUnitLoc(first >> 8, first & 0xFF);
            if (TaLogic_IsUnitWin(first, second, pos & 0xFF, pos >> 8) >= 0) {
                return pos;
            }
        }
        break;
    case 0x1E:
        for (x = 0; x < 7; x++) {
            for (y = 0; y < 7; y++) {
                count = 0;
                list = SearchUnitByRange(x, y, nSide, 1, 0x34, 0x12);
                for (i = 0; i < Ta_GetUnitNumFrom22bitFlagList(list); i++) {
                    cell = Ta_GetUnitOwnerIDFromLstCount(list, i);
                    row = cell >> 8;
                    col = cell & 0xFF;
                    if (SzDuel_GetUnitStatus(row, col, 4) == 0) {
                        count++;
                    } else if ((SzDuel_GetUnitKind(row, col) >> 5) != 0) {
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
} Data_00112850;

/* Whether side `nSide` can play ritual card `nCardNo` now (it has the units to give up). */
s32 TaLogicCom_IsDoCerem_00112850(s32 nSide, s32 nCardNo) {
    extern u32 TaHand_GetCardAPDP();
    s32 state[4];
    s32 index;
    s32 mask;
    u32 limit;
    s32 low;
    s32 high;
    s32 encoded;
    s32 position;
    Data_00112850 *data;

    data = TaHand_GetCardEffect(nCardNo, 0);
    Ta_GetCeremSacrifice(state, data->value);
    limit = TaHand_GetCardAPDP(data->value) >> 16;
    if ((mask = Ta_GetSacrificeUnit(state, nSide)) < 0) {
        return 0;
    } else {
        for (index = 0; index < Ta_GetUnitNumFrom22bitFlagList(mask); index++) {
            encoded = Ta_GetUnitOwnerIDFromLstCount(mask, index);
            high = encoded >> 8;
            low = encoded & 0xFF;
            position = SzDuel_GetUnitLoc(high, low);
            if (TaUtil_GetUnitAP(high, low, position & 0xFF, position >> 8) >= limit) {
                return 0;
            }
        }
        return 1;
    }
}

/* Whether card `nCardNo` is an Exodia part. */
s32 TaLogicCom_IsExzParts_00112960(s32 nCardNo) {
    s32 result;

    result = (u32) (nCardNo - 0x36) < 4U ? 1 : 0;
    return result;
}

/* Whether side `nSide`'s deck plays the Exodia tactic. */
s32 TaLogic_IsTactixExz_00112980(s32 nSide) {
    extern s32 SzDuel_GetUnitCardNo();

    if (SzDuel_GetUnitCardNo(nSide, 0) == 0x3A) {
        if (SzData_CheckDeck(nSide, SzData_GetCurrentDeck(nSide), 0x36) >= 0 && SzData_CheckDeck(nSide, SzData_GetCurrentDeck(nSide), 0x37) >= 0 && SzData_CheckDeck(nSide, SzData_GetCurrentDeck(nSide), 0x38) >= 0 && SzData_CheckDeck(nSide, SzData_GetCurrentDeck(nSide), 0x39) >= 0) {
            return 1;
        }
    }
    return 0;
}

/* How many Exodia limbs side `nSide` has ready on its summon squares (0..4; 0 unless its leader is Exodia's
   head). found[] is not cleared before the count, as in the original. */
s32 TaLogic_IsExzodia_00112A40(s32 nSide) {
    extern s32 SzDuel_GetUnitCardNo();
    extern s32 SzDuel_GetUnitCurseRest();
    extern s32 SzDuel_GetUnitSpellRest();
    s32 i;
    s32 count;
    s32 j;
    s32 type;
    s32 v;
    s32 found[4];

    count = 0;
    if (SzDuel_GetUnitCardNo(nSide, 0) == 0x3A) {
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 8; j++) {
                v = Ta_GetSommonPiecePreference(nSide, j);
                if (SzDuel_GetMapUnit(v & 0xFF, v >> 8) != 0) {
                    v = SzDuel_GetMapUnitID(v & 0xFF, v >> 8);
                    if (v >= 0) {
                        type = SzDuel_GetUnitCardNo(v >> 8, v & 0xFF);
                        if (type == Ta_GetExzodiaPartsCardNo(i) &&
                            SzDuel_GetUnitCurseRest(v >> 8, v & 0xFF) == 0 &&
                            SzDuel_GetUnitSpellRest(v >> 8, v & 0xFF) == 0 &&
                            (v >> 8) == nSide) {
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

typedef struct {
    u8 pad0[0x1A1];
    u8 lvl : 4;      /* 0x1A1 */
    u8 pad1A1 : 4;
} Ai_00112B90;

#pragma conditional_move off

/* This duelist's move: picks the next unit to act, gives it a task and turns that into input `pInput`; returns 1
   when it set one. */
s32 TaLogic_GetMinimumTask_00112B90(void *pCtl, void *pInput, s32 wCursorPos) {
    u16 *tasks = pCtl;
    Ai_00112B90 *ai = pCtl;
    s32 side;
    s32 found;
    s32 result;
    s32 index;

    side = SzDuel_GetTurnOwner();
    found = 0;
    ai->lvl = TaLogic001_IsActiveMode();
    if ((result = TaLogic_GetNextActiveUnit_00113370(tasks, side, ai->lvl, pInput)) < 0) {
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
    TaLogic_CommandUnit_00113140(tasks + index * 8, ai->lvl);
    switch ((tasks[index * 8 + 2] >> 8) & 0xFF) {
    case 5:
        if (SzDuel_GetUnitStatus(tasks[index * 8] >> 8, tasks[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_RunMission_00115850(tasks + index * 8, side, pInput, 1);
            found = 1;
        }
        break;
    case 2:
        if (SzDuel_GetUnitStatus(tasks[index * 8] >> 8, tasks[index * 8] & 0xFF, 0) == 0) {
            if (TaLogic_GetMinimumTask_AtkMission_00115E20(tasks + index * 8, side, pInput, 1) < 0) {
                TaLogic_InitRogicControl(tasks + index * 8, 1);
                return 1;
            }
            found = 1;
        }
        break;
    case 10:
        if (TaLogic_GetMinimumTask_Summon_00114080(tasks[index * 8], side, pInput) < 0) {
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
            TaLogic_GetMinimumTask_MoveMission_001162F0(tasks + index * 8, side, pInput, 1, 0);
            found = 1;
        }
        break;
    case 3:
        if (SzDuel_GetUnitStatus(tasks[index * 8] >> 8, tasks[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_MoveMission_001162F0(tasks + index * 8, side, pInput, 1, 1);
            found = 1;
        }
        break;
    case 9:
        TaLogic_GetMinimumTask_EncMission(tasks + index * 8, side, pInput, 1, 0, TaLogic_GetWarnHideLvl_00117C30(side), 5, 1);
        found = 1;
        break;
    case 11:
        TaLogic_GetMinimumTask_TrapMission_00116B60(tasks + index * 8, side, pInput, 1);
        found = 1;
        break;
    case 12:
        TaLogic_GetMinimumTask_ReviveMission_001170A0(tasks + index * 8, side, pInput, 1);
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
            TaLogic_GetMinimumTask_RunMission_00115850(tasks + index * 8, side, pInput, 0);
            found = 1;
        }
        break;
    case 2:
        if (SzDuel_GetUnitStatus(tasks[index * 8] >> 8, tasks[index * 8] & 0xFF, 0) == 0) {
            if (TaLogic_GetMinimumTask_AtkMission_00115E20(tasks + index * 8, side, pInput, 0) < 0) {
                TaLogic_GetMinimumTask_RunMission_00115850(tasks + index * 8, side, pInput, 0);
            }
            found = 1;
        }
        break;
    case 10:
        if (TaLogic_GetMinimumTask_Summon_00114080(tasks[index * 8], side, pInput) < 0) {
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
            TaLogic_GetMinimumTask_MoveMission_001162F0(tasks + index * 8, side, pInput, 0, 0);
            found = 1;
        }
        break;
    case 3:
        if (SzDuel_GetUnitStatus(tasks[index * 8] >> 8, tasks[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_MoveMission_001162F0(tasks + index * 8, side, pInput, 0, 1);
            found = 1;
        }
        break;
    case 9:
        found = 1;
        TaLogic_GetMinimumTask_EncMission(tasks + index * 8, side, pInput, 0, 0, TaLogic_GetWarnHideLvl_00117C30(side), 5, 1);
        break;
    case 11:
        found = 1;
        TaLogic_GetMinimumTask_TrapMission_00116B60(tasks + index * 8, side, pInput, 0);
        break;
    case 12:
        found = 1;
        TaLogic_GetMinimumTask_ReviveMission_001170A0(tasks + index * 8, side, pInput, 0);
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
    u16 card;       /* 0x0 */
    u8 pad2[2];
    s16 target;     /* 0x4 */
    u8 pad6[2];
    s32 f8;         /* 0x8 */
} Action_00113140;

/* Gives the unit of task `pTask` its order for this turn (attack, run, move, summon, guard). */
s32 TaLogic_CommandUnit_00113140(void *pCtl, s32 pTask) {
    extern s32 TaLogic001_CommandBtlUnit();
    extern s32 TaLogic001_CommandEfcMonster();
    extern s32 TaLogic001_CommandSpellUnit();
    Action_00113140 *act = pCtl;
    u16 card;
    s32 low;
    s32 controllingSide;
    s32 type;

    card = act->card;
    SzDuel_GetUnitLoc(card >> 8, card & 0xFF);
    card = act->card;
    controllingSide = Ta_IsUnitControl(card >> 8, card & 0xFF);
    card = act->card;
    if (SzDuel_GetUnit(card >> 8, card & 0xFF) != 0) {
        card = act->card;
        if (SzDuel_GetUnitStatus(card >> 8, card & 0xFF, 0) == 0) {
            card = act->card;
            if (card != 0xFFFF) {
                low = card & 0xFF;
                if (low == 0) {
                    if (act->f8 == -1) {
                        if (TaLogic_IsAttackedNow(card >> 8, low, 0) == 1) {
                            if (SzDuel_InqHandPhase(act->card >> 8) == 1) {
                                act->target = 0x50A;
                            } else {
                                act->target = 0x5FF;
                            }
                        } else {
                            if (SzDuel_InqHandPhase(act->card >> 8) == 1) {
                                act->target = 0xA06;
                                act->f8 = (act->f8 & 0xFFFF0000) | 0x101;
                            } else {
                                act->target = 0x6FF;
                                act->f8 = (act->f8 & 0xFFFF) | 0x01010000;
                            }
                        }
                    }
                } else {
                    type = SzDuel_GetUnitKind(card >> 8, low) >> 5;
                    switch (type) {
                    case 0:
                        card = act->card;
                        if (TaUtil_IsExMonster(card >> 8, card & 0xFF) == 1) {
                            TaLogic001_CommandEfcMonster(pCtl, pTask);
                        } else {
                            TaLogic001_CommandBtlUnit(pCtl, 1, pTask);
                        }
                        break;
                    case 2:
                        TaLogic_CommandEncUnit(pCtl, 5, 0, TaLogic_GetWarnHideLvl_00117C30(controllingSide) & 0xFF);
                        break;
                    case 1:
                    case 3:
                        TaLogic001_CommandSpellUnit(pCtl, pTask);
                        break;
                    default:
                        act->target = 0x5FF;
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
s32 TaLogic_GetNextActiveUnit_00113370(u16 *pCtl, s32 nSide, s32 pInput, void *nMode) {
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
    TaLogic_CommandUnit_00113140(pCtl + idx * 8, pInput);
    if (((pCtl[idx * 8 + 2] >> 8) & 0xFF) == 10) {
        if (SzDuel_InqHandPhase(nSide) == 1 && TaLogic_GetMinimumTask_Summon_00114080(pos, nSide, nMode) >= 0) {
            return pos | 0x10000;
        }
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_GetUnitStatus(nSide, 0, 0) == 0) {
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_InqHandPhase(nSide) == 1 && TaLogic_GetMinimumTask_Summon_00114080(pos, nSide, nMode) >= 0) {
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

typedef struct Event_00113760 {
    u16 id;
    u16 pad2;
    u16 state;
    u16 pad6;
    union {
        u32 word;
        u16 low;
    } data;
} Event_00113760;

typedef struct Entry_00113760 {
    u16 id;
    u8 state;
    u8 pad;
} Entry_00113760;

/* Orders a fighting unit (task `pTask`): straight at the enemy leader when `fGoalFirst` and the path is open,
   else at the nearest enemy it can beat within 2 squares (5 with `bActive`); else it pushes in. */
void TaLogic001_CommandBtlUnit(void *pTask, s32 fGoalFirst, s32 bActive) {
    extern void TaLogic_InitIgnoreLst();
    extern s32 TaLogic_IsRootOpen();
    extern s32 TaLogic001_GetNearUnit();
    extern void TaLogic001_CommandInvadeUnit();
    s32 position;
    u8 buffer[0x70];
    Entry_00113760 entries[22];
    s16 countA;
    s16 countB;

    if (SzDuel_GetUnit(((Event_00113760 *)pTask)->id >> 8,
                       ((Event_00113760 *)pTask)->id & 0xFF) != 0) {
        s32 player;
        s32 other;
        s32 step;
        s32 unitInfo;
        s32 i;
        Entry_00113760 *p;

        player = Ta_GetCurrentSide(((Event_00113760 *)pTask)->id >> 8,
                              ((Event_00113760 *)pTask)->id & 0xFF);
        other = (player == 0 ? 1 : 0) << 8;
        position = SzDuel_GetUnitLoc(((Event_00113760 *)pTask)->id >> 8,
                                ((Event_00113760 *)pTask)->id & 0xFF);
        step = SzDuel_GetUnitLoc(other >> 8, other & 0xFF);
        unitInfo = SzDuel_GetUnit(((Event_00113760 *)pTask)->id >> 8,
                            ((Event_00113760 *)pTask)->id & 0xFF);
        p = entries;
        i = 0;
        do {
            ++i;
            p->id = 0xFFFF;
            p->state = 0xFF;
            ++p;
        } while (i < 22);
        TaLogic_InitIgnoreLst(buffer);
        if (fGoalFirst != 0) {
            if (TaLogic_IsRootOpen(((Event_00113760 *)pTask)->id >> 8,
                             ((Event_00113760 *)pTask)->id & 0xFF,
                             position & 0xFF, position >> 8,
                             other >> 8, other & 0xFF,
                             step & 0xFF, step >> 8, 2) > 0) {
                ((Event_00113760 *)pTask)->state = 0x2FF;
                ((Event_00113760 *)pTask)->data.word = (other << 16) |
                    ((Event_00113760 *)pTask)->data.low;
                return;
            }
        }
        step = 1;
        countB = 0;
        countA = 0;
        for (; step <= (bActive != 0 ? 5 : 2); ++step) {
            s32 limit = bActive != 0 ? 5 : 2;
            s32 side;
            s32 result;

            side = Ta_GetCurrentSide(((Event_00113760 *)pTask)->id >> 8,
                                ((Event_00113760 *)pTask)->id & 0xFF) == 0 ? 1 : 0;
            result = TaLogic001_GetNearUnit(pTask, 0, unitInfo, position & 0xFF, position >> 8,
                                  side, step & 0xFF, TaLogic_GetWarnHideLvl_00117C30(player),
                                  entries, 0, &countA, &countB, limit & 0xFF, buffer);
            switch (result) {
                case 3:
                    ((Event_00113760 *)pTask)->state = 0x6FF;
                    ((Event_00113760 *)pTask)->data.word = (position << 16) |
                        ((Event_00113760 *)pTask)->data.low;
                    return;
                case 2:
                    ((Event_00113760 *)pTask)->state = 0x3FF;
                    ((Event_00113760 *)pTask)->data.word = (position << 16) |
                        ((Event_00113760 *)pTask)->data.low;
                    return;
                case 1:
                    return;
                case 0:
                    ((Event_00113760 *)pTask)->state = 0x5FF;
                    return;
            }
        }
        TaLogic001_CommandInvadeUnit(pTask, bActive);
    }
}

/* TaLogic_GetNearUnit with this duelist's view and strength settings. */
void TaLogic001_GetNearUnit(s32 pTask, s32 pTree, s32 pVarInfo, s32 nX, s32 nZ, s32 eSide, s32 bDist, s32 WarnLvl, s32 nUnitLst, u16 wUnitNum, s32 wSize, s32 wNodeCount, u8 bChase, s32 wIgnoreLst) {
    TaLogic_GetNearUnit(pTask, pTree, pVarInfo, nX, nZ, eSide, bDist, WarnLvl,
                  nUnitLst, wUnitNum, wSize, wNodeCount, bChase,
                  0, 3000, wIgnoreLst);
}

typedef struct {
    u16 position;
    u8 pad2[2];
    u16 state;
    u8 pad6[2];
    union {
        u16 low;
        u32 value;
    } flags;
} Data_00113A60;

/* Orders a unit (task `pTask`) to push into the opponent's side of the board. */
void TaLogic001_CommandInvadeUnit(void *pTask) {
    Data_00113A60 *data = pTask;
    s32 pair;
    s32 low;

    Ta_IsUnitControl(data->position >> 8, data->position & 0xFF);
    pair = SzDuel_GetUnitLoc(data->position >> 8, data->position & 0xFF);
    if (CheckLandAgreement2(3, data->position >> 8, data->position & 0xFF) == 1) {
        data->state = 0x6FF;
        data->flags.value = data->flags.low | (TaLogic001_GetNextGrassPoint(pair & 0xFF, pair >> 8) << 16);
    } else {
        low = pair & 0xFF;
        data->state = 0x6FF;
        if (low < 3 && (pair >> 8) < 3) {
            data->flags.value = data->flags.low | 0x03030000;
        } else if (low >= (pair >> 8)) {
            data->flags.value = data->flags.low | 0x03050000;
        } else {
            data->flags.value = data->flags.low | 0x05030000;
        }
    }
}

/* The next forest square toward the opponent from (nX, nZ). */
s32 TaLogic001_GetNextGrassPoint(s32 nX, s32 nZ) {
    s32 result;

    if (nZ >= 5) {
        result = 0x602;
    } else if (nX >= 5) {
        result = 0x206;
    } else if (nX >= nZ) {
        result = 0x105;
    } else {
        result = 0x501;
    }
    return result;
}

typedef struct Entry_00113BB0 {
    u16 value;
    u8 flag;
    u8 pad;
} Entry_00113BB0;

/* Orders an effect monster (task `pTask`): where its effect does most (`fGoalFirst`: try its goal first). */
void TaLogic001_CommandEfcMonster(void *pTask, s32 fGoalFirst) {
    u8 buffer[0x70];
    Entry_00113BB0 entries[22];
    u16 out_a;
    u16 out_b;
    u16 count;
    s32 attempt;
    u16 *command = (u16 *)pTask;
    s32 owner;
    s32 position;
    s32 state;
    s32 object;
    s32 high;
    s32 i;
    Entry_00113BB0 *entry;
    s32 result;
    u16 id;
    u32 mode = fGoalFirst;
    extern s32 SzDuel_GetUnitCardNo();
    extern s32 TaLogic_GetNearUnitL3(s32, s32, s32, void *, s32, s32, s32, s32, s32, s32, s32);
    extern s32 TaLogic_GetNearUnitL2();
    extern void TaLogic_InitIgnoreLst();

    id = command[0];
    if (SzDuel_GetUnit(id >> 8, id & 0xFF) != 0) {
        id = command[0];
        owner = Ta_GetCurrentSide(id >> 8, id & 0xFF);
        id = command[0];
        position = SzDuel_GetUnitLoc(id >> 8, id & 0xFF);
        count = 0;
        out_b = 0;
        out_a = 0;
        id = command[0];
        object = SzDuel_GetUnit(id >> 8, id & 0xFF);
        entry = entries;
        i = 0;
        do {
            i++;
            entry->value = 0xFFFF;
            entry->flag = 0xFF;
            entry++;
        } while (i < 22);
        TaLogic_InitIgnoreLst(buffer);
        state = 0;
        id = command[0];
        switch (SzDuel_GetUnitCardNo(id >> 8, id & 0xFF)) {
        case 0x53:
            if (TaLogic001_IsUseLordOfDragon(owner) == 1) {
                command[2] = 0x3FF;
                *(u32 *)&command[4] = (position << 16) | command[4];
            } else {
                command[2] = 0x5FF;
            }
            return;
        case 0x89: {
            high = position >> 8;
            attempt = 1;
            position &= 0xFF;
            while (1) {
                state = TaLogic_GetNearUnitL2(state, object, position, high, owner == 0 ? 1 : 0,
                                     (u8)attempt, 0, TaLogic_GetWarnHideLvl_00117C30(owner),
                                     entries, &count, &out_a, &out_b, buffer);
                result = TaLogic_GetNearUnitL3(object, position, high, entries, 5, 0x34,
                                      0, 2, 0, TaLogic_GetWarnHideLvl_00117C30(owner), count);
                if (result >= 0) {
                    command[2] = 0x2FF;
                    *(u32 *)&command[4] = (result << 16) | command[4];
                    return;
                }
                attempt++;
                if (attempt <= 5) {
                    continue;
                }
                break;
            }
            break;
        }
        case 0xBF:
            if (TaLogic_CommandGunnerUnit(command, 0) == 1) {
                command[2] = 0xBFF;
                return;
            }
            break;
        case 0x179:
            if (TaLogic001_IsUseLifeHourGlass(owner) == 1 && TaLogic_CommandGunnerUnit(command, 0) == 1) {
                command[2] = 0xBFF;
                return;
            }
            break;
        case 0x186:
            if (TaLogic001_IsUseBraveHourGlass(owner) == 1 && TaLogic_CommandGunnerUnit(command, 0) == 1) {
                command[2] = 0xBFF;
                return;
            }
            break;
        }
        TaLogic001_CommandBtlUnit(command, 1, mode);
    }
}

typedef struct {
    u16 key;
    u16 unk2;
    s16 status;
    u16 unk6;
    union {
        u16 low;
        u32 word;
    } value;
} Data_00113ED0;


/* Orders a face-down magic card (task `pTask`): whether and where to open it. */
void TaLogic001_CommandSpellUnit(void *pTask) {
    Data_00113ED0 *arg;
    s32 search_key;
    s32 compare_key;
    s32 *object;
    s32 result;
    u32 kind;
    s32 status;

    arg = (Data_00113ED0 *)pTask;
    search_key = Ta_IsUnitControl(arg->key >> 8, arg->key & 0xFF);
    compare_key = SzDuel_GetUnitLoc(arg->key >> 8, arg->key & 0xFF);
    object = Ta_GetUnitEffect(arg->key >> 8, arg->key & 0xFF, 0);
    if (object == NULL) {
        arg->status = 0x5FF;
        return;
    }
    switch (SzDuel_GetUnitKind(arg->key >> 8, arg->key & 0xFF) >> 5) {
    case 1:
        kind = (u32)*object >> 8;
        if (kind != 4) {
            status = 0xCFF;
            switch (kind) {
            case 2:
                arg->status = 0x6FF;
                arg->value.word = arg->value.low | 0x03030000;
                return;
            case 20:
                arg->status = 0xCFF;
                return;
            }
        } else {
            result = TaLogicCom_GetUseXYRangeSpell_00112600(search_key, object);
            if (result >= 0) {
                arg->status = 0x6FF;
                if ((*object & 0x3F) == 0) {
                    arg->value.word = arg->value.low | (((compare_key >> 8) << 8 | (result & 0xFF)) << 16);
                } else {
                    arg->value.word = (result << 16) | arg->value.low;
                }
                return;
            }
        }
        goto fail_status;
    case 3:
        if (TaLogic_CommandGunnerUnit(pTask, 0) == 1) {
            arg->status = 0xBFF;
            return;
        }
        goto fail_status;
    default:
fail_status:
        status = 0x5FF;
        goto store_status;
    }
store_status:
    arg->status = status;
    return;
}

typedef struct {
    s16 id;
    u8 unk2;
    u8 pad3;
    s16 unk4;
    u8 pad6[6];
    s32 unkC;
} Ctx_00114080;

typedef struct {
    u8 pad0[0x3C];
    u16 unk3C;
    u8 pad3E[0x22];
} Work_00114080;

s32 TaLogic_GetNearCard2(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8,
                  s32 arg9);

/* The summon task for side `nSide`: which hand cards to play and where, into `pInput`; -1 when it plays none. */
s32 TaLogic_GetMinimumTask_Summon_00114080(s32 wUnit, s32 nSide, void *pInput) {
    extern s32 TaLogic_GetUnitNum(s32, s32);
    Work_00114080 work;
    s32 ret;
    s32 res;
    s32 pos;
    s32 kind;
    Ctx_00114080 *ctx = pInput;

    ctx->id = wUnit;
    if (SzDuel_InqHandPhase(nSide) == 0) {
        return -1;
    }
    if (TaLogic_GetUnitNum(nSide, 0) == 5 && TaLogic_GetUnitNum(nSide, 1) == 5) {
        return -1;
    }
    kind = TaLogic001_IsHandPlay(nSide, &work);
    if (kind < 0) {
        return -1;
    }
    ctx->unk2 = 10;
    ctx->unkC = 0;
    pos = SzDuel_GetUnitLoc(wUnit >> 8, wUnit & 0xFF);
    if (kind == 0) {
        if (TaLogic001_SetComboQue(nSide, (u8 *)ctx, &work) >= 0) {
            ret = TaLogic_GetNearCard2(&work, pos & 0xFF, pos >> 8, nSide == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, TaLogic_GetWarnHideLvl_00117C30(nSide));
            if (ret < 0) {
                if (SzDuel_GetUnitMonsterCount(nSide) < 4) {
                    res = TaLogic001_GetSummonPiece(nSide, kind, &work, ret);
                    if (res < 0) {
                        return -1;
                    }
                    ctx->unk4 = res;
                    return 1;
                }
            } else {
                res = TaLogic001_GetSummonPiece(nSide, kind, &work, ret);
                if (res < 0) {
                    return -1;
                }
                ctx->unk4 = res;
                return 1;
            }
        }
    } else {
        ret = TaLogic_GetNearCard2(&work, pos & 0xFF, pos >> 8, nSide == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, TaLogic_GetWarnHideLvl_00117C30(nSide));
    }
    if (kind == 2) {
        TaLogic001_SetSpecialComboQue(nSide, ctx, &work);
        res = TaLogic001_GetSummonPiece(nSide, kind, &work, ret);
        if (res < 0) {
            return -1;
        }
        ctx->unk4 = res;
        return 1;
    }
    if (TaLogic001_GetSpellPlay(nSide, (u8 *)ctx, &work, work.unk3C) < 0) {
        return -1;
    }
    res = TaLogic001_GetSummonPiece(nSide, kind, &work, ret);
    if (res < 0) {
        return -1;
    }
    ctx->unk4 = res;
    return 1;
}

/* Whether side `nSide` should play from its hand this turn (and what, into `pInput`). */
s32 TaLogic001_IsHandPlay(s32 nSide, void *pInput) {
    extern s32 TaLogic_GetUnitNum();
    extern s32 SzDuel_GetUnitCurseRest();
    s32 cards[8];
    u8 buffer[32];
    u8 primary;
    u8 secondary;
    s32 i;
    s32 result;

    primary = (u8)TaLogic_GetUnitNum(nSide, 0);
    secondary = (u8)TaLogic_GetUnitNum(nSide, 1);
    if (pInput == NULL) {
        return -1;
    }
    TaHand_GetNextHand(nSide, cards);
    if (primary == 5) {
        if (TaLogic001_GetSpellPlay(nSide, buffer, pInput, 999) >= 0) {
            return 1;
        }
        return -1;
    }
    if (secondary == 5) {
        s32 index = 0;
        s32 *p;
        if (index < TaHand_GetNextHandNum(nSide)) {
            p = cards;
            do {
                if ((TaHand_GetCardKind(*p) >> 5) == 0 && TaHand_IsCardSummon2(nSide, *p) == 1) {
                    SzDuel_InitCardInfo(pInput, cards[index]);
                    return 0;
                }
                p++;
                index++;
            } while (index < TaHand_GetNextHandNum(nSide));
        }
        return -1;
    }
    if (TaLogic001_GetSpecCardPlay(nSide, buffer, pInput, 0x345) >= 0) {
        if (TaLogic001_IsDoCerem(nSide, 0x345) == 1) {
            return 2;
        }
    }
    if (TaLogic001_IsUseLordOfDragon(nSide) == 1) {
        if (SearchUnitByRange(0, 0, nSide, 1, 0x53001C, 14) == 0) {
            if (TaLogic001_GetSpecCardPlay(nSide, buffer, pInput, 0x53) >= 0) {
                return 2;
            }
            if (TaLogic001_GetProtectCardPlay(nSide, buffer, pInput) >= 0) {
                return 2;
            }
        }
    }
    if (TaLogic001_IsUseLifeHourGlass(nSide) == 1) {
        if (TaLogic001_GetSpecCardPlay(nSide, buffer, pInput, 0x179) >= 0) {
            return 2;
        }
    }
    if (TaLogic001_IsUseBraveHourGlass(nSide) == 1) {
        if (TaLogic001_GetSpecCardPlay(nSide, buffer, pInput, 0x186) >= 0) {
            return 2;
        }
    }
    if (TaLogic001_IsUseRevive(nSide) >= 0) {
        if (TaLogic001_GetSpecCardPlay(nSide, buffer, pInput, 0x2AD) >= 0) {
            return 2;
        }
    }
    for (i = 0; i < 11; i++) {
        if (SzDuel_GetUnitCurseRest(nSide, i) != 0 && TaLogic001_GetSpecCardPlay(nSide, buffer, pInput, 0x31C) >= 0) {
            return 2;
        }
    }
    {
        s32 *p;
        s32 index = 0;
        if (index < TaHand_GetNextHandNum(nSide)) {
            p = cards;
            do {
                if ((TaHand_GetCardKind(*p) >> 5) == 0 && TaHand_IsCardSummon2(nSide, *p) == 1) {
                    SzDuel_InitCardInfo(pInput, cards[index]);
                    return 0;
                }
                p++;
                index++;
            } while (index < TaHand_GetNextHandNum(nSide));
        }
    }
    result = TaLogic001_GetSpellPlay(nSide, buffer, pInput, 999);
    if (result >= 0) {
        return result;
    }
    return -1;
}

/* Whether side `nSide` holds card `nCardNo` and can summon it (its slot into `bCombo`, the card into `pCardInfo`);
   returns its kind group or -1. */
s32 TaLogic001_GetSpecCardPlay(s32 nSide, void *bCombo, void *pCardInfo, s32 nCardNo) {
    s32 entries[8];
    s32 i;

    TaHand_GetNextHand(nSide, entries);
    for (i = 0; i < TaHand_GetNextHandNum(nSide); i++) {
        if ((nCardNo & 0xFFFF) == entries[i] && TaHand_IsCardSummon2(nSide, entries[i]) == 1) {
            *((s8 *)bCombo + 6) = i;
            SzDuel_InitCardInfo(pCardInfo, entries[i]);
            return TaHand_GetCardKind(entries[i]) >> 5;
        }
    }
    return -1;
}

/* Whether side `nSide` holds card `card` and can summon it (its slot into `bCombo`, the card into `pCardInfo`). */
static inline s32 search_001147B0(s32 nSide, void *bCombo, void *pCardInfo, s32 card) {
    s32 cards[8];
    s32 i;

    TaHand_GetNextHand(nSide, cards);
    for (i = 0; i < TaHand_GetNextHandNum(nSide); i++) {
        if (cards[i] == card && TaHand_IsCardSummon2(nSide, cards[i]) == 1) {
            *((s8 *)bCombo + 6) = i;
            SzDuel_InitCardInfo(pCardInfo, cards[i]);
            return TaHand_GetCardKind(cards[i]) >> 5;
        }
    }
    return -1;
}

/* The first protecting card (0x337, 0x335, 0x338, 0x33C, 0x339) side `nSide` can play now, or -1. */
s32 TaLogic001_GetProtectCardPlay(s32 nSide, void *bCombo, void *pCardInfo) {
    s32 result;

    result = search_001147B0(nSide, bCombo, pCardInfo, 0x337);
    if (result >= 0) {
        return result;
    }
    result = search_001147B0(nSide, bCombo, pCardInfo, 0x335);
    if (result >= 0) {
        return result;
    }
    result = search_001147B0(nSide, bCombo, pCardInfo, 0x338);
    if (result >= 0) {
        return result;
    }
    result = search_001147B0(nSide, bCombo, pCardInfo, 0x33C);
    if (result >= 0) {
        return result;
    }
    result = search_001147B0(nSide, bCombo, pCardInfo, 0x339);
    if (result >= 0) {
        return result;
    }
    return -1;
}

/* Whether side `nSide` plays a magic or ritual card from its hand now (its slot into `bCombo`, the card into
   `pCardInfo`). */
s32 TaLogic001_GetSpellPlay(s32 nSide, u8 *bCombo, void *pCardInfo, s32 nMode) {
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

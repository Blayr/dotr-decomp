/* Computer AI of the Darkness-ruler (duelist 7, duelistController07). */

#include "common.h"

typedef struct {
    u8 pad0[0x1A1];
    u8 lvl : 4;      /* 0x1A1 */
    u8 pad1A1 : 4;
} Ai_0012BB70;
#pragma conditional_move off

/* This duelist's move: picks the next unit to act, gives it a task and turns that into input `pInput`; returns 1
   when it set one. */
s32 TaLogic_DarknessRuler_GetMinimumTask(void *pCtl, void *pInput, s32 wCursorPos) {
    extern s32 TaLogic_DarknessRuler_GetMinimumTask_ReviveMission(UnitTask *, s32, void *, u8, u8);
    extern s32 TaLogic_DarknessRuler_GetMinimumTask_TrapMission(void *, s32, void *, u8, u8);
    UnitTask *tasks = pCtl;
    Ai_0012BB70 *ai = pCtl;
    s32 side;
    s32 found;
    s32 result;
    s32 index;

    side = SzDuel_GetTurnOwner();
    found = 0;
    ai->lvl = TaLogic007_IsActiveMode();
    if ((result = TaLogic_DarknessRuler_GetNextActiveUnit(tasks, side, (s32)pInput)) < 0) {
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
    TaLogic_DarknessRuler_CommandUnit(&tasks[index], ai->lvl);
    switch ((tasks[index].mission >> 8) & 0xFF) {
    case TASK_RUN:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            TaLogic_DarknessRuler_GetMinimumTask_RunMission(&tasks[index], side, pInput, 1, ai->lvl);
            found = 1;
        }
        break;
    case TASK_ATTACK:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            if (TaLogic_DarknessRuler_GetMinimumTask_AtkMission(&tasks[index], side, pInput, 1, ai->lvl) < 0) {
                TaLogic_InitRogicControl(&tasks[index], 1);
                return 1;
            }
            found = 1;
        }
        break;
    case TASK_SUMMON:
        if (TaLogic_DarknessRuler_GetMinimumTask_Summon(tasks[index].ownerId, side, (s32)pInput, ai->lvl) < 0) {
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
            TaLogic_DarknessRuler_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 1, 0, ai->lvl);
            found = 1;
        }
        break;
    case TASK_CONFIRMUNIT:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            TaLogic_DarknessRuler_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 1, 1, ai->lvl);
            found = 1;
        }
        break;
    case TASK_ENCHANT:
        TaLogic_GetMinimumTask_EncMission(&tasks[index], side, pInput, 1, 0, TaLogic_DarknessRuler_GetWarnHideLvl(side), 5, 1);
        found = 1;
        break;
    case TASK_TRAP:
        TaLogic_DarknessRuler_GetMinimumTask_TrapMission(&tasks[index], side, pInput, 1, ai->lvl);
        found = 1;
        break;
    case TASK_REVIVE:
        TaLogic_DarknessRuler_GetMinimumTask_ReviveMission(&tasks[index], side, pInput, 1, ai->lvl);
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
            TaLogic_DarknessRuler_GetMinimumTask_RunMission(&tasks[index], side, pInput, 0, ai->lvl);
            found = 1;
        }
        break;
    case 2:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            if (TaLogic_DarknessRuler_GetMinimumTask_AtkMission(&tasks[index], side, pInput, 0, ai->lvl) < 0) {
                TaLogic_DarknessRuler_GetMinimumTask_RunMission(&tasks[index], side, pInput, 0, ai->lvl);
            }
            found = 1;
        }
        break;
    case 10:
        if (TaLogic_DarknessRuler_GetMinimumTask_Summon(tasks[index].ownerId, side, (s32)pInput, ai->lvl) < 0) {
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
            TaLogic_DarknessRuler_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 0, 0, ai->lvl);
            found = 1;
        }
        break;
    case 3:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            TaLogic_DarknessRuler_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 0, 1, ai->lvl);
            found = 1;
        }
        break;
    case 11:
        TaLogic_DarknessRuler_GetMinimumTask_TrapMission(&tasks[index], side, pInput, 0, ai->lvl);
        found = 1;
        break;
    case 9:
        TaLogic_GetMinimumTask_EncMission(&tasks[index], side, pInput, 0, 0, TaLogic_DarknessRuler_GetWarnHideLvl(side), 5, 1);
        found = 1;
        break;
    case 12:
        TaLogic_DarknessRuler_GetMinimumTask_ReviveMission(&tasks[index], side, pInput, 0, ai->lvl);
        found = 1;
        break;
    case 14:
        TaLogic_GetMinimumTask_DoNone(&tasks[index], side, pInput);
        break;
    default:
        return 0;
    }
    if (found == 1) {
        return 1;
    }
    return 0;
}

typedef struct {
    u16 id;
    u8 pad2[2];
    s16 status;
    u8 pad6[2];
    s32 flags;
} Object_0012C1A0;
#pragma conditional_move reset

/* Gives the unit of task `pTask` its order for this turn (attack, run, move, summon, guard). */
s32 TaLogic_DarknessRuler_CommandUnit(void *pCtl, s32 pTask) {
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
                        TaLogic_CommandEncUnit(obj, 5, 0, TaLogic_DarknessRuler_GetWarnHideLvl(controllingSide) & 0xFF);
                        break;
                    case 3:
                        TaLogic_DarknessRuler_CommandTrapUnit(obj);
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
s32 TaLogic_DarknessRuler_GetNextActiveUnit(DuelPlayer *pCtl, s32 nSide, s32 pInput) {
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
    TaLogic_DarknessRuler_CommandUnit(&pCtl->taskList[idx], pCtl->AiActiveRelated & 0xF);
    if (((pCtl->taskList[idx].mission >> 8) & 0xFF) == 10) {
        if (SzDuel_InqHandPhase(nSide) == 1 && TaLogic_DarknessRuler_GetMinimumTask_Summon(pos, nSide, pInput, TaLogic007_IsActiveMode()) >= 0) {
            return pos | 0x10000;
        }
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_GetUnitStatus(nSide, 0, 0) == 0) {
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_InqHandPhase(nSide) == 1 && TaLogic_DarknessRuler_GetMinimumTask_Summon(pos, nSide, pInput, TaLogic007_IsActiveMode()) >= 0) {
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
                    other, (u8)bActive, TaLogic_DarknessRuler_GetWarnHideLvl(side), entries, 0,
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
                    other, (u8)bActive, TaLogic_DarknessRuler_GetWarnHideLvl(side), entries, 0,
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
s32 TaLogic007_GetNearUnit(s32 pTask, s32 pTree, s32 pVarInfo, s32 nX, s32 nZ, s32 eSide, s32 bDist, s32 WarnLvl, s32 nUnitLst, u16 wUnitNum, s32 wSize, s32 wNodeCount, u8 bChase, s32 wIgnoreLst) {
    return TaLogic_GetNearUnit(pTask, pTree, pVarInfo, nX, nZ, eSide, bDist, WarnLvl,
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
                                      (u8)attempt, TaLogic_DarknessRuler_GetWarnHideLvl(owner), entries, 0,
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

typedef struct {
    u16 position;
    u8 flag;
    u8 pad;
} Slot_0012CE50;

/* Orders a trap card (task `pTask`): where to set it. */
void TaLogic_DarknessRuler_CommandTrapUnit(void *pTask) {
    u8 work[112];
    Slot_0012CE50 slots[22];
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
    extern s32 SzDuel_GetUnitCurseRest();
    extern s32 SzDuel_GetUnitSpellRest();

    if (SzDuel_GetUnit((s32) record[0] >> 8, record[0] & 0xFF) != 0) {
        player = Ta_GetCurrentSide((s32) record[0] >> 8, record[0] & 0xFF);
        position = SzDuel_GetUnitLoc((s32) record[0] >> 8, record[0] & 0xFF);
        owner = SzDuel_GetUnit((s32) record[0] >> 8, record[0] & 0xFF);
        record[2] = 0xBFF;
        TaLogic_InitIgnoreLst(work);
        for (i = 0; i < 22; i++) {
            slots[i].position = 0xFFFF;
            slots[i].flag = 0xFF;
        }
        a = 0;
        b = 0;
        c = 0;
        state = 0;
        for (i = 1; i < 3; i++) {
            state = TaLogic_GetNearUnitL2(state, owner, position & 0xFF, position >> 8,
                                  Ta_GetCurrentSide((s32) record[0] >> 8, record[0] & 0xFF) == 0 ? 1 : 0, (u8) i, 0,
                                  TaLogic_DarknessRuler_GetWarnHideLvl(player), slots, &a, &c, &b, work);
            if ((result = TaLogic_GetTrapNearCard((s32) record[0] >> 8, record[0] & 0xFF, position & 0xFF, position >> 8,
                                        slots, 5, 0x1F, 1, 2, 0, TaLogic_DarknessRuler_GetWarnHideLvl(player), a, 1)) >= 0) {
                if (SzDuel_GetUnitCurseRest(result >> 8, result & 0xFF) == 0 &&
                    SzDuel_GetUnitSpellRest(result >> 8, result & 0xFF) == 0) {
                    *(u32 *) (record + 4) = (result << 16) | record[4];
                    return;
                }
            }
            if ((result = TaLogic_GetTrapNearCard((s32) record[0] >> 8, record[0] & 0xFF, position & 0xFF, position >> 8,
                                        slots, 5, 0x1F, 0, 2, 0, TaLogic_DarknessRuler_GetWarnHideLvl(player), a, 1)) >= 0) {
                if (SzDuel_GetUnitCurseRest(result >> 8, result & 0xFF) == 0 &&
                    SzDuel_GetUnitSpellRest(result >> 8, result & 0xFF) == 0) {
                    *(u32 *) (record + 4) = (result << 16) | record[4];
                    return;
                }
            }
        }
        a = 0;
        b = 0;
        c = 0;
        state = 0;
        for (i = 1; i < 3; i++) {
            state = TaLogic_GetNearUnitL2(state, owner, position & 0xFF, position >> 8,
                                  Ta_GetCurrentSide((s32) record[0] >> 8, record[0] & 0xFF), (u8) i, 0,
                                  TaLogic_DarknessRuler_GetWarnHideLvl(player), slots, &a, &c, &b, work);
            result = TaLogic_GetFollowNearUnit(position & 0xFF, position >> 8, slots, 5, 0x22, 2, 2, a);
            if (result >= 0) {
                *(u32 *) (record + 4) = (result << 16) | record[4];
                return;
            }
            result = TaLogic_GetFollowNearUnit(position & 0xFF, position >> 8, slots, 5, 0x1F, 1, 2, a);
            if (result >= 0) {
                *(u32 *) (record + 4) = (result << 16) | record[4];
                return;
            }
            result = TaLogic_GetFollowNearUnit(position & 0xFF, position >> 8, slots, 5, 0x1F, 0, 2, a);
            if (result >= 0) {
                *(u32 *) (record + 4) = (result << 16) | record[4];
                return;
            }
        }
        *(u32 *) (record + 4) = (player << 24) | record[4];
    }
}

typedef struct Result_0012D270 {
    s16 position;
    s8 kind;
    u8 pad3;
    s16 value;
    u8 pad6[6];
    s32 flags;
} Result_0012D270;

typedef struct Work_0012D270 {
    u8 pad0[0x3C];
    u16 field3C;
    u8 pad3E[0x22];
} Work_0012D270;

/* The summon task for side `nSide`: which hand cards to play and where, into `pInput`; -1 when it plays none. */
s32 TaLogic_DarknessRuler_GetMinimumTask_Summon(s32 wUnit, s32 nSide, s32 pInput, s32 nMode) {
    extern s32 TaLogic_GetUnitNum();
    extern s32 TaLogic_GetNearCard2();
    extern s64 TaLogic_DarknessRuler_GetWarnHideLvl();
    Work_0012D270 work;
    s32 packed;
    s32 x;
    s32 mode;
    s32 selection;
    s32 value;

    ((Result_0012D270 *)pInput)->position = wUnit;
    if (SzDuel_InqHandPhase(nSide) == 0) {
        return -1;
    }
    if (TaLogic_GetUnitNum(nSide, 0) == 5) {
        if (TaLogic_GetUnitNum(nSide, 1) == 5) {
            return -1;
        }
    }
    mode = TaLogic007_IsHandPlay(nSide, &work, nMode);
    if (mode < 0) {
        return -1;
    }
    {
        s32 y = wUnit >> 8;
        x = wUnit & 0xFF;
        ((Result_0012D270 *)pInput)->kind = 10;
        ((Result_0012D270 *)pInput)->flags = 0;
        packed = SzDuel_GetUnitLoc(y, x);
        selection = TaLogic_GetNearCard2(&work, packed & 0xFF, packed >> 8,
                                nSide == 0 ? 1 : 0, 3, 31, 2, 2,
                                (s64)0, (s64)TaLogic_DarknessRuler_GetWarnHideLvl(nSide));
        if (mode == 0) {
            if (TaLogic007_SetComboQue(nSide, (u8 *)pInput, &work) >= 0) {
                s32 packed2 = SzDuel_GetUnitLoc(y, x);
                selection = TaLogic_GetNearCard2(&work, packed2 & 0xFF, packed2 >> 8,
                                        nSide == 0 ? 1 : 0, 3, 31, 2, 2,
                                        (s64)0, (s64)TaLogic_DarknessRuler_GetWarnHideLvl(nSide));
                if (selection < 0) {
                    if (SzDuel_GetUnitMonsterCount(nSide) < 6) {
                        value = TaLogic007_GetSummonPiece(nSide, 0, &work, selection);
                        if (value < 0) {
                            return -1;
                        }
                        ((Result_0012D270 *)pInput)->value = value;
                        return 1;
                    }
                } else {
                    value = TaLogic007_GetSummonPiece(nSide, 0, &work, selection);
                    if (value < 0) {
                        return -1;
                    }
                    ((Result_0012D270 *)pInput)->value = value;
                    return 1;
                }
            }
        } else if (mode == 2) {
            TaLogic007_SetSpecialComboQue(nSide, (void *)pInput, &work);
            value = TaLogic007_GetSummonPiece(nSide, mode & 0xFF, &work, selection);
            if (value < 0) {
                return -1;
            }
            ((Result_0012D270 *)pInput)->value = value;
            return 1;
        }
        value = TaLogic007_GetSpellPlay(nSide, (u8 *)pInput, &work, work.field3C);
        if (value < 0) {
            return -1;
        }
        value = TaLogic007_GetSummonPiece(nSide, value & 0xFF, &work, selection);
        if (value < 0) {
            return -1;
        }
        ((Result_0012D270 *)pInput)->value = value;
        return 1;
    }
}

/* Whether side `nSide` should play from its hand this turn (and what, into `pInput`). */
s32 TaLogic007_IsHandPlay(s32 nSide, void *pInput, s32 nMode) {
    s32 cards[8];
    u8 scratch[32];
    s32 result;
    u8 status0;
    u8 status1;
    u8 count;
    extern s32 TaLogic_GetUnitNum();

    status0 = TaLogic_GetUnitNum(nSide, 0);
    status1 = TaLogic_GetUnitNum(nSide, 1);
    count = 0;
    if (pInput == NULL) {
        return -1;
    }
    TaHand_GetNextHand(nSide, cards);
    if (status0 == 5) {
        if (TaLogic007_GetSpellPlay(nSide, scratch, pInput, 999) >= 0) {
            return 1;
        }
        return -1;
    }
    if (status1 == 5) {
        s32 i;
        s32 *p;

        i = 0;
        if (i < TaHand_GetNextHandNum(nSide)) {
            p = cards;
            do {
                if ((TaHand_GetCardKind(*p) >> 5) == 0 && TaHand_CanAffordSummonCost(nSide, *p) == 1) {
                    SzDuel_InitCardInfo(pInput, cards[i]);
                    return 0;
                }
                p++;
                i++;
            } while (i < TaHand_GetNextHandNum(nSide));
        }
        return -1;
    }
    if ((u8)nMode == 0) {
        s32 i;

        if ((result = TaLogic007_GetCurseCardPlay(nSide, cards, pInput, scratch)) >= 0) {
            return 2;
        }
        if (TaLogic007_IsDoCerem(nSide, 0x342) == 1) {
            if ((result = TaLogic007_GetSpecCardPlay(nSide, cards, pInput, scratch, 0x342)) >= 0) {
                return 2;
            }
        }
        i = 0;
        do {
            if (SzDuel_GetUnit(0, i) != 0) {
                if (nSide != Ta_IsUnitControl(0, i)) {
                    count++;
                }
            }
            if (SzDuel_GetUnit(1, i) != 0 && nSide != Ta_IsUnitControl(1, i)) {
                count++;
            }
            i++;
        } while (i < 11);
        if (result >= 4) {
            if (TaLogic007_GetSpecCardPlay(nSide, cards, pInput, scratch, 0x146) >= 0) {
                return 2;
            }
        }
        if (TaLogic007_IsRevivePlay(nSide) >= 0) {
            if (TaLogic007_GetSpecCardPlay(nSide, cards, pInput, scratch, 0x131) >= 0) {
                return 2;
            }
        }
    } else {
        s32 i;

        if (TaLogic007_IsDoCerem(nSide, 0x342) == 1) {
            if ((result = TaLogic007_GetSpecCardPlay(nSide, cards, pInput, scratch, 0x342)) >= 0) {
                return 2;
            }
        }
        i = 0;
        do {
            if (SzDuel_GetUnit(0, i) != 0) {
                if (nSide != Ta_IsUnitControl(0, i)) {
                    count++;
                }
            }
            if (SzDuel_GetUnit(1, i) != 0 && nSide != Ta_IsUnitControl(1, i)) {
                count++;
            }
            i++;
        } while (i < 11);
        if (result >= 4 && TaLogic007_GetSpecCardPlay(nSide, cards, pInput, scratch, 0x146) >= 0) {
            return 2;
        }
    }
    {
        s32 *p;
        s32 i;

        i = 0;
        if (i < TaHand_GetNextHandNum(nSide)) {
            p = cards;
            do {
                if ((TaHand_GetCardKind(*p) >> 5) == 0 && TaHand_CanAffordSummonCost(nSide, *p) == 1) {
                    return 0;
                }
                p++;
                i++;
            } while (i < TaHand_GetNextHandNum(nSide));
        }
    }
    result = TaLogic007_GetSpellPlay(nSide, scratch, pInput, 999);
    if (result >= 0) {
        return result;
    }
    return -1;
}

/* The curse (magic) card side `nSide` plays from hand `arNextHand` now, its slot into `bCombo`, the card into
   `pCardInfo`. */
s32 TaLogic007_GetCurseCardPlay(s32 nSide, s32 *arNextHand, void *pCardInfo, void *bCombo) {
    s32 i;
    s32 *p;
    s32 *q;
    s32 j;
    s32 value;

    i = 0;
    if (i < TaHand_GetNextHandNum(nSide)) {
        p = arNextHand;
        do {
            if (SzDuel_Kind2Type(TaHand_GetCardKind(*p) >> 5) == 2) {
                *((s8 *)bCombo + 6) = i;
                SzDuel_InitCardInfo(pCardInfo, arNextHand[i]);
                return TaHand_GetCardKind(arNextHand[i]) >> 5;
            }
            p++;
            i++;
        } while (i < TaHand_GetNextHandNum(nSide));
    }

    j = 0;
    if (j < TaHand_GetNextHandNum(nSide)) {
        q = arNextHand;
        do {
            if (TaHand_CanAffordSummonCost(nSide, *q) == 1) {
                value = *q;
                if (value == 0x31B || value == 0x2AC || value == 0x137) {
                    *((s8 *)bCombo + 6) = j;
                    SzDuel_InitCardInfo(pCardInfo, arNextHand[j]);
                    return TaHand_GetCardKind(arNextHand[j]) >> 5;
                }
            }
            q++;
            j++;
        } while (j < TaHand_GetNextHandNum(nSide));
    }
    return -1;
}

/* Whether side `nSide` holds card `nCardNo` and can summon it (its slot into `bCombo`, the card into `pCardInfo`);
   returns its kind group or -1. */
s32 TaLogic007_GetSpecCardPlay(s32 nSide, s32 *bCombo, void *pCardInfo, void *nCardNo, s32 arg4) {
    s32 i;
    s32 *entry;
    s32 wanted;

    i = 0;
    if (i < TaHand_GetNextHandNum(nSide)) {
        wanted = arg4 & 0xFFFF;
        entry = bCombo;
        do {
            if (TaHand_CanAffordSummonCost(nSide, *entry) == 1) {
                if (wanted == *entry && TaHand_CanAffordSummonCost(nSide, *entry) == 1) {
                    *((u8 *)nCardNo + 6) = i;
                    SzDuel_InitCardInfo(pCardInfo, bCombo[i]);
                    return TaHand_GetCardKind(bCombo[i]) >> 5;
                }
            }
            entry++;
            i++;
        } while (i < TaHand_GetNextHandNum(nSide));
    }
    return -1;
}

/* Whether side `nSide` plays a magic or ritual card from its hand now (its slot into `bCombo`, the card into
   `pCardInfo`). */
s32 TaLogic007_GetSpellPlay(s32 nSide, u8 *bCombo, void *pCardInfo, s32 nMode) {
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

typedef struct Info_0012DDE0 {
    u8 pad00[8];
    u16 x;
    s16 y;
} Info_0012DDE0;

typedef struct Sprite_0012DDE0 {
    Info_0012DDE0 *info;
    u8 pad04[0x34];
    s16 x;
    s16 y;
} Sprite_0012DDE0;

/* Fills hand combination `bCombo` for side `nSide`: the best fusion or equip chain, its card into `pCardInfo`. */
s32 TaLogic007_SetComboQue(s32 nSide, u8 *bCombo, void *pCardInfo) {
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
                    if (TaHand_CanAffordSummonCost(nSide, card) == 1) {
                        if (best < value) {
                            TaLogic_DarknessRuler_ConvEmptyCombo(nSide, *node, entries);
                            TaLogic_CopyArray((u8 *)*node + 2, bCombo + 6);
                            SzDuel_InitCardInfo(pCardInfo, **node);
                            ((Sprite_0012DDE0 *)pCardInfo)->x = (value >> 16) - (((Sprite_0012DDE0 *)pCardInfo)->info->x & 0x1FFF);
                            ((Sprite_0012DDE0 *)pCardInfo)->y = (value & 0xFFFF) - (((Sprite_0012DDE0 *)pCardInfo)->info->y & 0x1FFF);
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
} Info_0012DFC0;

/* Fills an empty combination: the hand card side `nSide` can summon with the best attack plus defence. */
void TaLogic_DarknessRuler_ConvEmptyCombo(s32 nSide, void *pCardInfo, s32 *pResult) {
    Info_0012DFC0 *info = pCardInfo;
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
                if (card != 0x3E7 && TaLogic007_IsRefuseEmptyCombo(card) == 0 && level >= TaHand_GetCardSummonCost2(card, nSide)) {
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

/* Whether this duelist keeps card `nCardNo` out of a summon (it is wanted for an equip). */
s32 TaLogic007_IsRefuseEmptyCombo(s32 nCardNo) {
    if ((TaHand_GetCardKind(nCardNo) >> 5) != 0) {
        return 1;
    }
    return TaHand_IsCardEffect(nCardNo) != 0 ? 1 : 0;
}

typedef struct {
    u8 pad0[6];
    u8 slot[5];
} Obj1_0012E1F0;

typedef struct {
    u8 pad0[0x3C];
    u16 id;
    u8 f3E;
} Obj2_0012E1F0;

/* Fills hand combination `bCombo` for side `nSide` with this duelist's special combination, its card into
   `pCardInfo`. */
s32 TaLogic007_SetSpecialComboQue(s32 nSide, void *bCombo, void *pCardInfo) {
    Obj1_0012E1F0 *o1 = bCombo;
    Obj2_0012E1F0 *o2 = pCardInfo;
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
            if (o2->id == list[i] && TaHand_CanAffordSummonCost(nSide, list[i]) == 1) {
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
    return o2->f3E >> 5;
}

typedef struct Nibbles_0012E3F0 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_0012E3F0;

/* The square side `nSide` summons a card of kind `sKind` to. */
s32 TaLogic007_GetSummonPiece(s32 nSide, s32 sKind, void *pInput, s32 nMode) {
    extern s32 TaLogic_IsUnitWin4();
    extern s32 TaLogic_GetInvadeRoot2();
    extern s32 TaLogic_GetRoot2(s32, s32, s32, s32, s32, s32, u16, u8);
    s32 best;
    s32 bestCost;
    s32 nearest;
    Nibbles_0012E3F0 flags[12];
    s32 i;
    Nibbles_0012E3F0 *p;
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
    if (kind == 0U || kind == 3U || kind == 2U) {
        if (nMode >= 0) {
            s32 candidate;
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
                        if (TaLogic_IsUnitWin4(pInput, nMode, TaLogic_DarknessRuler_GetWarnHideLvl(nSide),
                                         originX, originY, 0) > 0) {
                            cost = TaLogic_GetInvadeRoot2(pInput, flags, x, y,
                                                originX, originY, nMode, 0,
                                                5, (u16)TaLogic_DarknessRuler_GetWarnHideLvl(nSide));
                        } else {
                            cost = TaLogic_GetRoot2((s32)pInput, (s32)flags, x, y,
                                                originX, originY, nMode, 2);
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
            s32 originY;
            s32 originX;
            s32 maxY;
            s32 maxX;
            s32 y;
            s32 x;
            s32 index;
            s32 distance;
            s32 candidate;
            s32 minY;
            s32 minX;
            s32 origin;

            distance = 14;
            nearest = -1;
            origin = SzDuel_GetUnitLoc(nSide == 0 ? 1 : 0, 0);
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
                        SzDuel_GetMapUnitID(x, y) < 0) {
                        if (y < originY) {
                            minY = y;
                        } else {
                            minY = originY;
                        }
                        if (y > originY) {
                            maxY = y;
                        } else {
                            maxY = originY;
                        }
                        if (x < originX) {
                            minX = x;
                        } else {
                            minX = originX;
                        }
                        if (x > originX) {
                            maxX = x;
                        } else {
                            maxX = originX;
                        }
                        origin = (maxX - minX) + (maxY - minY);
                        if (origin < distance && origin >= 0) {
                            nearest = candidate;
                            distance = origin;
                        }
                    }
                }
                index++;
            } while (index < 8);
            if (distance < 14) {
                return nearest;
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
                    SzDuel_GetField(x, y) != 9 &&
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

typedef struct Nibbles_0012E820 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_0012E820;

typedef struct Output_0012E820 {
    u16 position;
    u8 action;
    u8 pad3;
    u16 destination;
    u8 pad6[6];
    s32 special;
    u8 result;
} Output_0012E820;

/* The task of a unit running from danger (task `pTask`): the safest square in reach, into `pInput` (`fFirst` = 1
   for the unit's first-choice task). */
s32 TaLogic_DarknessRuler_GetMinimumTask_RunMission(UnitTask *pTask, s32 nSide, void *pInput, u8 fFirst, u8 nMode) {
    Output_0012E820 *output = pInput;
    s32 target;
    u8 endX;
    u8 extra;
    Nibbles_0012E820 nibbles[12];
    s32 bestScore;
    s32 best;
    s32 i;
    Nibbles_0012E820 *p;
    extern s32 TaLogic_DarknessRuler_IsOpenUnit(s32, s32, void *, u8);
    extern s32 TaLogic_IsRunPassRoot(s32, s32, s32, s32, s32, s32, void *, u8);

    target = SzDuel_GetUnitLoc(pTask->ownerId >> 8, pTask->ownerId & 0xFF);
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

        initialScore = TaLogic_DarknessRuler_GetWarnHideLvl(nSide);
        centerX = target & 0xFF;
        centerY = target >> 8;
        if (TaLogic_GetUnitWarning(centerX, centerY, pTask->ownerId, 3, initialScore, 0) == 0) {
            output->position = pTask->ownerId;
            output->action = 6;
            output->destination = target;
            output->result = TaLogic_IsDefStyleUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, output->destination, 1, 0);
            output->special = TaLogic_DarknessRuler_IsOpenUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, pTask, nMode);
            TaLogic_InitRogicControl(pTask, fFirst);
            return 0;
        }
        if ((range = GetMoveRange(SzDuel_GetUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF), centerX, centerY)) == 0) {
            output->position = pTask->ownerId;
            output->action = 6;
            output->destination = target;
            output->result = TaLogic_IsDefStyleUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, output->destination, 1, 0);
            output->special = TaLogic_DarknessRuler_IsOpenUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, pTask, nMode);
            TaLogic_InitRogicControl(pTask, fFirst);
            return 0;
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
        if ((pTask->ownerId & 0xFF) == 0) {
            extra = (u8)TaLogic_IsAttackedNow(pTask->ownerId >> 8, pTask->ownerId & 0xFF, 0);
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
                if (TaLogic_IsRunPassRoot(pTask->ownerId >> 8, pTask->ownerId & 0xFF, centerX, centerY, x, y, pTask, extra) == 1) {
                    if (TaLogic_IsAttackedNow2(pTask->ownerId >> 8, pTask->ownerId & 0xFF, x, y, 0) == 0 || (u8)pTask->ownerId == 0) {
                        candidateScore = TaLogic_GetUnitWarning(x, y, pTask->ownerId, 3, (u16)TaLogic_DarknessRuler_GetWarnHideLvl(nSide), 0);
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
            output->position = pTask->ownerId;
            output->action = 6;
            output->destination = best;
            if (best == target) {
                output->result = TaLogic_IsDefStyleUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, output->destination, 1, 0);
            } else {
                output->result = TaLogic_IsDefStyleUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, output->destination, 0, 0);
            }
            output->special = TaLogic_DarknessRuler_IsOpenUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, pTask, nMode);
        } else {
            output->position = pTask->ownerId;
            output->action = 6;
            output->destination = target;
            output->result = TaLogic_IsDefStyleUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, output->destination, 1, 0);
            output->special = TaLogic_DarknessRuler_IsOpenUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, pTask, nMode);
        }
        TaLogic_InitRogicControl(pTask, fFirst);
        return 0;
    }
}

typedef struct Coord_0012ED70 {
    u8 x : 4;
    u8 y : 4;
} Coord_0012ED70;

typedef struct Result_0012ED70 {
    u16 card;
    u8 action;
    u8 pad03;
    u16 position;
    u8 pad06[6];
    s32 count;
    u8 flags;
} Result_0012ED70;

/* The task of reviving a monster from the graveyard (task `pTask`), into `pInput` (`fFirst` = 1 for the unit's
   first-choice task). */
s32 TaLogic_DarknessRuler_GetMinimumTask_ReviveMission(UnitTask *pTask, s32 nSide, s32 pInput, u8 fFirst) {
    extern s32 TaLogic_IsRunPassRoot(s32, s32, s32, s32, s32, s32, void *, u8);
    Coord_0012ED70 positions[12];
    s32 i;
    Coord_0012ED70 *p;
    s32 position;

    position = SzDuel_GetUnitLoc(pTask->ownerId >> 8, pTask->ownerId & 0xFF);
    p = positions;
    i = 0;
    do {
        p->x = p->y = 15;
        i++;
        p++;
    } while (i < 12);
    {
        s32 data;
        s32 card;
        s32 player;

        data = TaLogic007_IsRevivePlay(nSide);
        if (data >= 0) {
            player = (u16)(data >> 16);
            card = TaLogic_GetGraveEntryAfterScreen(player, data & 0xFF, 30);
            ((Result_0012ED70 *)pInput)->card = pTask->ownerId;
            ((Result_0012ED70 *)pInput)->action = 12;
            ((Result_0012ED70 *)pInput)->flags = TaLogic_IsDefStyleUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, *(u16 *)(pInput + 4), 1, 0);
            ((Result_0012ED70 *)pInput)->count = 1;
            *(u16 *)(pInput + 4) = (player << 8) | card;
            TaLogic_InitRogicControl(pTask, fFirst);
            return 0;
        }
    }
    if (SzDuel_GetUnitStatus(pTask->ownerId >> 8, pTask->ownerId & 0xFF, 4) != 0) {
        SzDuel_SetUnitStatus(pTask->ownerId >> 8, pTask->ownerId & 0xFF, 0, 1);
        ((Result_0012ED70 *)pInput)->card = pTask->ownerId;
        ((Result_0012ED70 *)pInput)->action = 14;
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

        card = TaLogic_DarknessRuler_GetWarnHideLvl(nSide);
        centerX = position & 0xFF;
        centerY = position >> 8;
        if (TaLogic_GetUnitWarning(centerX, centerY, pTask->ownerId, 3, card, 0) == 0) {
            ((Result_0012ED70 *)pInput)->card = pTask->ownerId;
            ((Result_0012ED70 *)pInput)->action = 6;
            *(u16 *)(pInput + 4) = position;
            ((Result_0012ED70 *)pInput)->flags = TaLogic_IsDefStyleUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, *(u16 *)(pInput + 4), 1, 0);
            ((Result_0012ED70 *)pInput)->count = 2;
            TaLogic_InitRogicControl(pTask, fFirst);
        } else {
            rangeResult = GetMoveRange(SzDuel_GetUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF), centerX, centerY);
            if (rangeResult == 0) {
                ((Result_0012ED70 *)pInput)->card = pTask->ownerId;
                ((Result_0012ED70 *)pInput)->action = 6;
                *(u16 *)(pInput + 4) = position;
                ((Result_0012ED70 *)pInput)->flags = TaLogic_IsDefStyleUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, *(u16 *)(pInput + 4), 1, 0);
                ((Result_0012ED70 *)pInput)->count = 2;
                TaLogic_InitRogicControl(pTask, fFirst);
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
                if ((pTask->ownerId & 0xFF) == 0) {
                    flags = (u8)TaLogic_IsAttackedNow(pTask->ownerId >> 8, pTask->ownerId & 0xFF, 0);
                } else {
                    flags = 0;
                }
                for (x = (u8)minX; x <= (u8)maxX; x++) {
                    for (y = (u8)minY, packedY = y << 8; y <= (u8)maxY; packedY += 0x100, y++) {
                        if (((x < centerX ? centerX : x) - (centerX < x ? centerX : x)) +
                            ((y < centerY ? centerY : y) - (centerY < y ? centerY : y)) <= (rangeResult & 15)) {
                            if (TaLogic_IsRunPassRoot(pTask->ownerId >> 8, pTask->ownerId & 0xFF, centerX, centerY, x, y, pTask, (u8)flags) == 1 &&
                                (TaLogic_IsAttackedNow2(pTask->ownerId >> 8, pTask->ownerId & 0xFF, x, y, 0) == 0 || (u8)pTask->ownerId == 0)) {
                                card = TaLogic_DarknessRuler_GetWarnHideLvl(nSide);
                                cost = TaLogic_GetUnitWarning(x, y, pTask->ownerId, 3, card, 0);
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
                    ((Result_0012ED70 *)pInput)->card = pTask->ownerId;
                    ((Result_0012ED70 *)pInput)->action = 6;
                    *(u16 *)(pInput + 4) = bestPosition;
                    if (bestPosition == position) {
                        ((Result_0012ED70 *)pInput)->flags = TaLogic_IsDefStyleUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, *(u16 *)(pInput + 4), 1, 0);
                    } else {
                        ((Result_0012ED70 *)pInput)->flags = TaLogic_IsDefStyleUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, *(u16 *)(pInput + 4), 0, 0);
                    }
                    ((Result_0012ED70 *)pInput)->count = 2;
                } else {
                    ((Result_0012ED70 *)pInput)->card = pTask->ownerId;
                    ((Result_0012ED70 *)pInput)->action = 6;
                    *(u16 *)(pInput + 4) = position;
                    ((Result_0012ED70 *)pInput)->flags = TaLogic_IsDefStyleUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, *(u16 *)(pInput + 4), 1, 0);
                    ((Result_0012ED70 *)pInput)->count = 2;
                }
                TaLogic_InitRogicControl(pTask, fFirst);

            }
        }
    }
    return 0;
}

typedef struct Source_0012F350 {
    u16 position;
    u8 pad2[6];
    u32 targets;
} Source_0012F350;

typedef struct Output_0012F350 {
    u16 position;
    u8 mode;
    u8 pad3;
    u16 target;
    u8 pad6[6];
    s32 flag;
    u8 value;
} Output_0012F350;

typedef struct Position_0012F350 {
    u8 x : 4;
    u8 y : 4;
} Position_0012F350;

/* The task's target square: the second half-word when the second argument is 1, else the first. */
static inline u32 target_0012F350(void *arg0, u8 which) {
    Source_0012F350 *source = arg0;
    if (which == 1) {
        return (u16)(source->targets >> 16);
    }
    return *(u16 *)&source->targets;
}

/* The task of a unit attacking (task `pTask`): its path to the goal, into `pInput`; -1 when it has none (`fFirst`
   = 1 for the unit's first-choice task). */
s32 TaLogic_DarknessRuler_GetMinimumTask_AtkMission(void *pTask, s32 nSide, void *pInput, u8 fFirst, s32 nMode) {
    extern void TaLogic_GetInvadeRoot();
    s32 sourceTarget;
    s32 count;
    s32 sourceY;
    s32 sourceX;
    s32 selectedFlag;
    Position_0012F350 positions[12];
    s32 flag;
    s32 otherTarget;
    s32 j;
    Position_0012F350 *walk;
    s32 object;
    u32 targetXWord;
    u32 targetYWord;
    Source_0012F350 *source = pTask;
    Output_0012F350 *output = pInput;

    targetXWord = target_0012F350(pTask, fFirst);
    targetYWord = target_0012F350(pTask, fFirst);
    if (SzDuel_GetUnit(targetYWord >> 8, targetXWord & 0xFF) == 0) {
        TaLogic_InitRogicControl(pTask, 1);
        return -1;
    }

    flag = TaLogic_DarknessRuler_IsOpenUnit(source->position >> 8, source->position & 0xFF, pTask, nMode);
    sourceTarget = SzDuel_GetUnitLoc(source->position >> 8, source->position & 0xFF);
    targetXWord = target_0012F350(pTask, fFirst);
    targetYWord = target_0012F350(pTask, fFirst);
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
                            (u8)TaLogic_DarknessRuler_GetWarnHideLvl(nSide));
        if (cost >= SzDuel_GetUnitAP(source->position >> 8, source->position & 0xFF, 0)) {
            output->value = TaLogic_IsDefStyleUnit(source->position >> 8, source->position & 0xFF,
                                        output->target, 1, 0);
        } else {
            output->value = TaLogic_IsDefStyleUnit(source->position >> 8, source->position & 0xFF,
                                        output->target, 0, 0);
        }
        TaLogic_InitRogicControl(pTask, fFirst);
    } else {
        s32 targetY;
        s32 targetX;
        Position_0012F350 *current;
        s32 i;
        s32 bestCost;
        s32 selected;
        u16 position = source->position;

        TaLogic_GetInvadeRoot(position >> 8, position & 0xFF, positions,
                      sourceX, sourceY, targetX = otherTarget & 0xFF,
                      targetY = otherTarget >> 8,
                      target_0012F350(pTask, fFirst), 0, 30, (u16)TaLogic_DarknessRuler_GetWarnHideLvl(nSide));
        count = TaLogic_GetMinGoalCount((u8 *)positions);
        selected = 0xFF;
        if (count > 0) {
            selectedFlag = 0;
            bestCost = 0xFFFF;
            for (i = 0; i < count; i++) {
                s32 state = TaLogic007_IsOpenMoveUnit(source->position >> 8, source->position & 0xFF,
                                          sourceX, sourceY, targetX, targetY);
                if (state == 1) {
                    Position_0012F350 *forcedPosition = &positions[i];
                    selected = i;
                    selectedFlag = 1;
                    i = count;
                    forcedPosition->x = targetX;
                    forcedPosition->y = targetY;
                } else {
                    s32 cost;
                    current = &positions[i];
                    cost = TaLogic_GetUnitWarning(current->x, current->y, nSide, 3, 1,
                                        (u8)TaLogic_DarknessRuler_GetWarnHideLvl(nSide));
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

typedef struct Unit_0012F930 {
    u16 position;
    u8 pad2[6];
    union {
        u32 packed;
        u16 halves[2];
    } destination;
} Unit_0012F930;

typedef struct Order_0012F930 {
    u16 position;
    u8 kind;
    u8 pad3;
    u16 destination;
    u8 pad6[6];
    s32 value;
    u8 flags;
} Order_0012F930;

typedef struct Point_0012F930 {
    u8 x : 4;
    u8 y : 4;
} Point_0012F930;

/* The task's target square: the second half-word when the second argument is 1, else the first. */
static inline u32 destination_0012F930(void *unit, s32 side) {
    if (side == 1) {
        return (u16)(((Unit_0012F930 *)unit)->destination.packed >> 16);
    }
    return ((Unit_0012F930 *)unit)->destination.halves[0];
}

/* The task of a unit moving to its goal (task `pTask`), into `pInput` (`fFirst` = 1 for the unit's first-choice
   task). */
s32 TaLogic_DarknessRuler_GetMinimumTask_MoveMission(void *pTask, s32 nSide, void *pInput, u8 fFirst, u8 nKind, u8 nMode) {
    extern s32 TaLogic_DarknessRuler_IsOpenUnit(s32, s32, void *, u8);
    extern s32 TaLogic_IsDefStyleUnit(s32, s32, s32, u8, s32);
    extern void TaLogic_GetRoot(s32, s32, void *, s32, s32, s32, s32, s32, u8);
    s32 count;
    s32 position;
    Point_0012F930 points[12];
    s32 id;
    s32 score;
    u32 destinationValue;
    Unit_0012F930 *unit = pTask;
    Order_0012F930 *order = pInput;

    {
    s32 bestScore;
    s32 bestIndex;
    s32 side;
    Point_0012F930 *point;
    s32 index;

    position = SzDuel_GetUnitLoc((s32)unit->position >> 8, unit->position & 0xFF);
    side = fFirst;
    if (destination_0012F930(unit, side) == 0xFFFF) {
        if (position == destination_0012F930(unit, side)) {
            order->position = unit->position;
            order->kind = 6;
            order->destination = position;
            order->flags = TaLogic_IsDefStyleUnit((s32)unit->position >> 8, unit->position & 0xFF,
                                       order->destination, nKind, 0);
            order->value = TaLogic_DarknessRuler_IsOpenUnit((s32)unit->position >> 8, unit->position & 0xFF, unit, nMode);
            TaLogic_InitRogicControl(unit, fFirst);
            return 0;
        }
    }

    point = points;
    {
        s32 i = 0;
        Point_0012F930 *p = point;
        do {
            p->x = p->y = 15;
            i++;
            p++;
        } while (i < 12);
    }

    destinationValue = destination_0012F930(unit, side);
    id = SzDuel_GetMapUnitID(destination_0012F930(unit, side) & 0xFF,
                       destinationValue >> 8);
    if (id < 0) {
        id = 0xFFFF;
    }
    destinationValue = destination_0012F930(unit, side);
    TaLogic_GetRoot((s32)unit->position >> 8, unit->position & 0xFF, points,
                  position & 0xFF, position >> 8,
                  destination_0012F930(unit, side) & 0xFF,
                  destinationValue >> 8, (u16)id, 7);
    count = TaLogic_GetMinGoalCount((u8 *)points);
    if (count > 0) {
        bestIndex = 0xFF;
        bestScore = 0xFFFF;
        for (index = 0; index < count; index++, point++) {
            if (SzDuel_GetMapUnit(point->x, point->y) == 0) {
                score = TaLogic_GetUnitWarning(point->x, point->y, nSide, 3, 1, (u8)TaLogic_DarknessRuler_GetWarnHideLvl(nSide));
                if (score < bestScore) {
                    bestScore = score;
                    bestIndex = index;
                } else if (score == bestScore) {
                    u32 oldYMin;
                    u32 oldYMax;
                    u32 oldXMin;
                    u32 oldXMax;
                    u8 oldY;
                    u8 oldX;
                    u32 currentYMin;
                    u32 currentYMax;
                    u32 currentXMin;
                    u32 currentXMax;
                    u8 currentY;
                    u8 currentX;
                    Point_0012F930 *best = &points[bestIndex];

                    oldY = best->y;
                    if (oldY < (destination_0012F930(unit, side) >> 8)) {
                        oldYMin = (u8)oldY;
                    } else {
                        oldYMin = destination_0012F930(unit, side) >> 8;
                    }
                    if ((destination_0012F930(unit, side) >> 8) < oldY) {
                        oldYMax = (u8)oldY;
                    } else {
                        oldYMax = destination_0012F930(unit, side) >> 8;
                    }
                    oldX = best->x;
                    if (oldX < (destination_0012F930(unit, side) & 0xFF)) {
                        oldXMin = (u8)oldX;
                    } else {
                        oldXMin = destination_0012F930(unit, side) & 0xFF;
                    }
                    if ((destination_0012F930(unit, side) & 0xFF) < oldX) {
                        oldXMax = (u8)oldX;
                    } else {
                        oldXMax = destination_0012F930(unit, side) & 0xFF;
                    }

                    currentY = point->y;
                    if (currentY < (destination_0012F930(unit, side) >> 8)) {
                        currentYMin = (u8)currentY;
                    } else {
                        currentYMin = destination_0012F930(unit, side) >> 8;
                    }
                    if ((destination_0012F930(unit, side) >> 8) < currentY) {
                        currentYMax = (u8)currentY;
                    } else {
                        currentYMax = destination_0012F930(unit, side) >> 8;
                    }
                    currentX = point->x;
                    if (currentX < (destination_0012F930(unit, side) & 0xFF)) {
                        currentXMin = (u8)currentX;
                    } else {
                        currentXMin = destination_0012F930(unit, side) & 0xFF;
                    }
                    if ((destination_0012F930(unit, side) & 0xFF) < currentX) {
                        currentXMax = (u8)currentX;
                    } else {
                        currentXMax = destination_0012F930(unit, side) & 0xFF;
                    }
                    if ((currentXMax - currentXMin) + (currentYMax - currentYMin) <
                        (oldXMax - oldXMin) + (oldYMax - oldYMin)) {
                        bestScore = score;
                        bestIndex = index;
                    }
                }
            }
        }
    } else {
        order->position = unit->position;
        order->kind = 6;
        order->destination = position;
        order->flags = TaLogic_IsDefStyleUnit((s32)unit->position >> 8, unit->position & 0xFF,
                                   order->destination, nKind, 0);
        order->value = TaLogic_DarknessRuler_IsOpenUnit((s32)unit->position >> 8, unit->position & 0xFF, unit, nMode);
        TaLogic_InitRogicControl(unit, fFirst);
        return 0;
    }
        if (bestIndex != 0xFF) {
            order->position = unit->position;
            order->kind = 6;
            order->destination = (points[bestIndex].y << 8) | points[bestIndex].x;
            order->flags = TaLogic_IsDefStyleUnit((s32)unit->position >> 8, unit->position & 0xFF,
                                       order->destination, nKind, 0);
            order->value = TaLogic_DarknessRuler_IsOpenUnit((s32)unit->position >> 8, unit->position & 0xFF, unit, nMode);
        } else {
            order->position = unit->position;
            order->kind = 6;
            order->destination = position;
            order->flags = TaLogic_IsDefStyleUnit((s32)unit->position >> 8, unit->position & 0xFF,
                                       order->destination, nKind, 0);
            order->value = TaLogic_DarknessRuler_IsOpenUnit((s32)unit->position >> 8, unit->position & 0xFF, unit, nMode);
        }
        TaLogic_InitRogicControl(unit, fFirst);
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
} Source_00130120;

typedef struct {
    u16 position;
    u8 action;
    u8 pad3;
    u16 target;
    u8 pad6[10];
    s8 result;
} Action_00130120;

typedef struct {
    u8 x : 4;
    u8 y : 4;
} Point_00130120;

#define MIN_00130120(a, b) ((a) < (b) ? (a) : (b))
#define MAX_00130120(a, b) ((b) < (a) ? (a) : (b))

/* The task's target square: the second half-word when the second argument is 1, else the first. */
static inline u32 target_00130120(void *arg0, s32 mode) {
    Source_00130120 *source = arg0;
    if (mode == 1) {
        return (u16)(source->target.both >> 16);
    }
    return source->target.half[0];
}

/* Sets a move task (action 6) to the given square, and whether the unit should stay in defence there. */
static inline void fill_00130120(void *arg0, void *arg2, s32 target, s32 flag) {
    Source_00130120 *source = arg0;
    Action_00130120 *action = arg2;
    action->position = source->position;
    action->action = 6;
    action->target = target;
    action->result = TaLogic_IsDefStyleUnit(source->position >> 8,
        source->position & 0xFF, action->target, flag, 0);
}

/* The task of setting a trap (task `pTask`), into `pInput`. */
s32 TaLogic_DarknessRuler_GetMinimumTask_TrapMission(void *pTask, s32 nSide, void *pInput, s32 fFirst) {
    s32 start;
    s32 count;
    s32 startY;
    Point_00130120 points[16];
    s32 bestScore;
    Point_00130120 *p;
    s32 targetY;
    s32 targetX;
    s32 i;
    s32 bestIndex;
    s32 mode;
    s32 target;
    s32 startX;
    u32 xPosition;
    u32 yPosition;
    Source_00130120 *source = pTask;
    Action_00130120 *action = pInput;
    extern void TaLogic_GetInvadeRoot();

    mode = fFirst & 0xFF;
    xPosition = target_00130120(pTask, mode);
    yPosition = target_00130120(pTask, mode);
    if (SzDuel_GetUnit(yPosition >> 8, xPosition & 0xFF) == 0) {
        TaLogic_InitRogicControl(pTask, 1);
        return -1;
    }
    start = SzDuel_GetUnitLoc(source->position >> 8, source->position & 0xFF);
    xPosition = target_00130120(pTask, mode);
    yPosition = target_00130120(pTask, mode);
    target = SzDuel_GetUnitLoc(yPosition >> 8, xPosition & 0xFF);
    if (target_00130120(pTask, mode) == 0xFFFF) {
        fill_00130120(pTask, pInput, start, 1);
        return 0;
    } else {
        s32 unit = SzDuel_GetUnit(source->position >> 8, source->position & 0xFF);
        startX = start & 0xFF;
        startY = start >> 8;
        if (GetMoveRange(unit, startX, startY) == 0 ||
                TaLogic_IsAttackedNow(source->position >> 8, source->position & 0xFF, 0) == 1) {
            fill_00130120(pTask, pInput, start, 1);
            return 0;
        } else {
            p = points;
            {
                s32 n = 0;
                Point_00130120 *q = p;
                do {
                    q->x = q->y = 0xF;
                    q++;
                    n++;
                } while (n < 12);
            }
            {
                s32 position = source->position;
                u16 card = (u16)TaLogic_DarknessRuler_GetWarnHideLvl(nSide);
                TaLogic_GetInvadeRoot(position >> 8, position & 0xFF, points,
                    startX, startY, targetX = target & 0xFF,
                    targetY = target >> 8, target_00130120(pTask, mode),
                    0, 30, card);
            }
            count = TaLogic_GetMinGoalCount((u8 *)points);
            bestIndex = 0xFF;
            if (count > 0) {
                bestScore = 0;
                for (i = 0; i < count; i++, p++) {
                    if (SzDuel_GetMapUnit(p->x, p->y) == 0) {
                        s32 score = TaLogic_GetUnitWarning(p->x, p->y, nSide, 3, 1,
                            TaLogic_DarknessRuler_GetWarnHideLvl(nSide) & 0xFF);
                        if (bestScore < score) {
                            bestScore = score;
                            bestIndex = i;
                        } else if (score == bestScore) {
                            if (MAX_00130120(p->x, targetX) - MIN_00130120(p->x, targetX)
                                    + (MAX_00130120(p->y, targetY) - MIN_00130120(p->y, targetY))
                                    < MAX_00130120(points[bestIndex].x, targetX) - MIN_00130120(points[bestIndex].x, targetX)
                                    + (MAX_00130120(points[bestIndex].y, targetY) - MIN_00130120(points[bestIndex].y, targetY))) {
                                bestScore = score;
                                bestIndex = i;
                            }
                        }
                    }
                }
            } else {
                fill_00130120(pTask, pInput, start, 1);
                return 0;
            }
            if (bestIndex != 0xFF) {
                action->position = source->position;
                action->action = 6;
                action->target = (points[bestIndex].y << 8) | points[bestIndex].x;
                action->result = TaLogic_IsDefStyleUnit(source->position >> 8,
                    source->position & 0xFF, action->target, 0, 0);
            } else {
                fill_00130120(pTask, pInput, start, 1);
                return 0;
            }
        }
    }
    return 0;
}

/* The graveyard card side `nSide` can revive now ((side << 16) | index), or -1. */
s32 TaLogic007_IsRevivePlay(s32 nSide) {
    extern s32 SzDuel_GetGraveCount();
    s32 i;
    s32 entry;
    CardConstInfo *state;
    u32 *info;

    if (SzDuel_GetUnitSpellCount(nSide) >= 5) {
        return -1;
    }
    for (i = 0; i < SzDuel_GetGraveCount(nSide); i++) {
        entry = SzDuel_InqGrave(nSide, i);
        if ((TaHand_GetCardKind(entry) >> 5) != 0) {
            state = SzDuel_GetCardConstInfo(entry);
            info = TaHand_GetCardEffect(entry, 0);
            if ((info != NULL) && (state == NULL) && (state->deckCost >= 0xF) &&
                (SzDuel_GetUnitSpellCount(nSide) < 5) && ((*info >> 8) != 0x14)) {
                return (nSide << 0x10) | i;
            }
        }
    }
    return -1;
}

/* How careful this duelist is about hidden cards (by its life points and monster count). */
s32 TaLogic_DarknessRuler_GetWarnHideLvl(s32 nSide) {
    if (SzDuel_GetLP(nSide) > 0x7D0) {
        if (SzDuel_GetUnitMonsterCount(nSide) >= 4) {
            return 0x2EE;
        } else {
            return 0x5DC;
        }
    } else {
        return 0x960;
    }
}

/* Whether side `nSide` can play ritual card `nCardNo` now (it has the units to give up). */
s32 TaLogic007_IsDoCerem(s32 nSide, s32 nCardNo) {
    extern s32 SzDuel_GetUnitCardNo();
    s32 data[4];
    s32 i;
    s32 mask;
    s32 coords;
    s32 card;
    s32 y;
    s32 x;
    s32 cell;

    Ta_GetCeremSacrifice(data, *(s32 *) ((u8 *) TaHand_GetCardEffect(nCardNo, 0) + 4));
    if ((mask = Ta_GetSacrificeUnit(data, nSide)) < 0) {
        return 0;
    }
    for (i = 0; i < Ta_GetUnitNumFrom22bitFlagList(mask); i++) {
        cell = Ta_GetUnitOwnerIDFromLstCount(mask, i);
        x = cell >> 8;
        y = cell & 0xFF;
        coords = SzDuel_GetUnitLoc(x, y);
        card = SzDuel_GetUnitCardNo(x, y);
        if (TaUtil_GetUnitAP(x, y, coords & 0xFF, coords >> 8) >= 3000 || card == 0x12A ||
            (card == 0x131 && SzDuel_GetUnitStatus(x, y, 4) == 0) || card == 0x146) {
            return 0;
        }
    }
    return 1;
}

/* Whether this duelist opens (turns face up) unit (nSide, nID) now: 0 no, 1 or 2 by its kind. */
s32 TaLogic_DarknessRuler_IsOpenUnit(s32 nSide, s32 nID, void *pInfo, s32 nMode) {
    extern s32 SzDuel_GetUnitCardNo();
    s32 card;
    s32 position;
    u8 count;

    card = SzDuel_GetUnitCardNo(nSide, nID);
    Ta_IsUnitControl(nSide, nID);
    position = SzDuel_GetUnitLoc(nSide, nID);
    count = 0;
    if (SzDuel_GetUnitStatus(nSide, nID, 4) != 0) {
        return 0;
    }
    switch (SzDuel_GetUnitKind(nSide, nID) >> 5) {
    case 0:
        switch (card) {
        case 0x12A:
            return 1;
        case 0x142:
            if ((nMode & 0xFF) == 1) {
                return 1;
            }
            break;
        case 0x146:
            for (card = 0; card < 11; card++) {
                if (SzDuel_GetUnit(0, card) != 0 && nSide != Ta_IsUnitControl(0, card)) {
                    count++;
                }
                if (SzDuel_GetUnit(1, card) != 0 && nSide != Ta_IsUnitControl(1, card)) {
                    count++;
                }
            }
            if (count >= 4) {
                return 1;
            }
            break;
        }
        return 2;
    case 5:
        if (TaLogic_GetActionReaction(nSide, nID, 0, 0, 6, 0) == 5) {
            return 2;
        }
        if (TaLogic007_IsDoCerem(Ta_IsUnitControl(nSide, nID), card) == 1 &&
            SzDuel_GetField(position & 0xFF, position >> 8) != 9) {
            return 1;
        }
        break;
    case 1:
        return (TaLogic_GetActionReaction(nSide, nID, 0, 0, 6, 0) == 5) ? 2 : 1;
    case 2:
    case 3:
    case 4:
        break;
    }
    return 2;
}

/* Whether unit (nSide, nID) may open while moving from (nX, nZ) to the square next to it, (gX, gZ). */
s32 TaLogic007_IsOpenMoveUnit(s32 nSide, s32 nID, s32 nX, s32 nZ,
                  s32 gX, s32 gZ) {
    s32 min_y;
    s32 min_x;

    min_y = nZ < gZ ? nZ : gZ;
    gZ = Max(gZ, nZ);
    min_x = nX < gX ? nX : gX;
    gX = Max(gX, nX);
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

/* Whether this duelist plays in its attacking mode this turn. */
s32 TaLogic007_IsActiveMode(void) {
    /* both really take (player, slot); the headers say (void) */
    s32 SzDuel_GetUnitCurseRest();
    s32 SzDuel_GetUnitSpellRest();
    s32 player;
    u8 count3;
    s32 i;
    u8 count1;
    u8 count2;
    s32 j;

    player = SzDuel_GetTurnOwner();
    count1 = 0;
    count3 = 0;
    for (i = 0; i < 11; i++) {
        if (SzDuel_GetUnitCurseRest(player, i) > 0 || SzDuel_GetUnitSpellRest(player, i) > 0 ||
            Ta_IsUnitControl(player, i) != player) {
            count1++;
        }
        if (SzDuel_GetUnitCurseRest(player == 0 ? 1 : 0, i) > 0 || SzDuel_GetUnitSpellRest(player == 0 ? 1 : 0, i) > 0 ||
            Ta_IsUnitControl(player == 0 ? 1 : 0, i) != player) {
            count1++;
        }
    }
    if (count1 >= 4) {
        return 0;
    }
    count2 = 0;
    for (j = 0; j < 11; j++) {
        if (Ta_IsUnitControl(player, j) != player) {
            count2++;
        }
        if (Ta_IsUnitControl(player == 0 ? 1 : 0, j) != player) {
            count2++;
        }
    }
    for (j = 0; j < 11; j++) {
        if (Ta_IsUnitControl(player, j) == player) {
            count3++;
        }
        if (Ta_IsUnitControl(player == 0 ? 1 : 0, j) == player) {
            count3++;
        }
    }
    if (count2 < 2 && count3 >= 4) {
        return 1;
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
} Req_00130E90;

typedef struct {
    u8 pad0[0x160];
    u16 list[32];    /* 0x160 */
    u8 idx : 5;      /* 0x1A0 */
    u8 pad1A0 : 3;
    u8 pad1A1;
    u16 count;       /* 0x1A2 */
} Work_00130E90;

s32 TaLogic_GetInputQueFromMinimumTask_b(void *, void *, s32);

/* Computer duelist 7's controller (duelistControllers[7]): the buttons it presses this frame. With an empty input
   queue it plans its next task and turns it into buttons, then plays the queue back one button per frame; after
   600 frames it gives up the turn (0x20, then 0x800). */
s32 duelistController07(s32 wCursorPos, void *pCtl) {
    Req_00130E90 req;
    Work_00130E90 *w;
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
        if (TaLogic_DarknessRuler_GetMinimumTask(w, &req, wCursorPos) == 0) {
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

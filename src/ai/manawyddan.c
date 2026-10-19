/* Computer AI of Manawyddan fab Llyr (duelist 20, duelistController20). */

#include "common.h"

s32 TaLogic_GetInputQueFromMinimumTask_b(void *, void *, s32);
#pragma conditional_move off

/* This duelist's move: picks the next unit to act, gives it a task and turns that into input `pInput`; returns 1
   when it set one. */
s32 TaLogic_Manawyddan_GetMinimumTask(void *pCtl, void *pInput, s32 wCursorPos) {
    extern s32 TaLogic_Manawyddan_GetWarnHideLvl(s32);
    UnitTask *tasks = pCtl;
    s32 side;
    s32 found;
    s32 result;
    s32 index;

    side = SzDuel_GetTurnOwner();
    found = 0;
    if ((result = TaLogic_Manawyddan_GetNextActiveUnit(tasks, side, (s32)pInput)) < 0) {
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
    TaLogic_Manawyddan_CommandUnit(&tasks[index]);
    switch ((tasks[index].mission >> 8) & 0xFF) {
    case TASK_RUN:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            TaLogic_Manawyddan_GetMinimumTask_RunMission(&tasks[index], side, pInput, 1);
            found = 1;
        }
        break;
    case TASK_ATTACK:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            if (TaLogic_Manawyddan_GetMinimumTask_AtkMission(&tasks[index], side, pInput, 1) < 0) {
                TaLogic_InitRogicControl(&tasks[index], 1);
                return 1;
            }
            found = 1;
        }
        break;
    case TASK_SUMMON:
        if (TaLogic_Manawyddan_GetMinimumTask_Summon(tasks[index].ownerId, side, (s32)pInput) < 0) {
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
            TaLogic_Manawyddan_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 1, 0);
            found = 1;
        }
        break;
    case TASK_CONFIRMUNIT:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            TaLogic_Manawyddan_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 1, 1);
            found = 1;
        }
        break;
    case TASK_ENCHANT:
        TaLogic_GetMinimumTask_EncMission(&tasks[index], side, pInput, 1, 1, TaLogic_Manawyddan_GetWarnHideLvl(side), 5, 1);
        found = 1;
        break;
    case TASK_REVIVE:
        TaLogic_Manawyddan_GetMinimumTask_ReviveMission(&tasks[index], side, pInput, 1);
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
            TaLogic_Manawyddan_GetMinimumTask_RunMission(&tasks[index], side, pInput, 0);
            found = 1;
        }
        break;
    case 2:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            if (TaLogic_Manawyddan_GetMinimumTask_AtkMission(&tasks[index], side, pInput, 0) < 0) {
                TaLogic_Manawyddan_GetMinimumTask_RunMission(&tasks[index], side, pInput, 0);
            }
            found = 1;
        }
        break;
    case 10:
        if (TaLogic_Manawyddan_GetMinimumTask_Summon(tasks[index].ownerId, side, (s32)pInput) < 0) {
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
            TaLogic_Manawyddan_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 0, 0);
            found = 1;
        }
        break;
    case 3:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            TaLogic_Manawyddan_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 0, 1);
            found = 1;
        }
        break;
    case 9:
        TaLogic_GetMinimumTask_EncMission(&tasks[index], side, pInput, 0, 1, TaLogic_Manawyddan_GetWarnHideLvl(side), 5, 1);
        found = 1;
        break;
    case 12:
        TaLogic_Manawyddan_GetMinimumTask_ReviveMission(&tasks[index], side, pInput, 0);
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

typedef struct Entry_00163660 {
    u16 unitId; /* (side << 8) | unit */
    u16 pad2;
    s16 action;
    u16 pad6;
    s32 target;
} Entry_00163660;
#pragma conditional_move reset

/* Gives a unit of this duelist its order for this turn (attack, run, move, summon, guard). */
s32 TaLogic_Manawyddan_CommandUnit(void *pCtl) {
    extern s32 TaLogic_Manawyddan_GetWarnHideLvl();
    Entry_00163660 *entry = pCtl;
    s32 card;
    u16 unitId;

    SzDuel_GetUnitLoc(entry->unitId >> 8, entry->unitId & 0xFF);
    card = Ta_IsUnitControl(entry->unitId >> 8, entry->unitId & 0xFF);
    if (SzDuel_GetUnit(entry->unitId >> 8, entry->unitId & 0xFF) != 0) {
        if (SzDuel_GetUnitStatus(entry->unitId >> 8, entry->unitId & 0xFF, 0) == 0) {
            unitId = entry->unitId;
            if (unitId != 0xFFFF) {
                if ((unitId & 0xFF) == 0) {
                    if (entry->target == -1) {
                        if (TaLogic_IsAttackedNow(unitId >> 8, unitId & 0xFF, 1) == 1) {
                            if (SzDuel_InqHandPhase(entry->unitId >> 8) == 1) {
                                entry->action = 0x50A;
                            } else {
                                entry->action = 0x5FF;
                            }
                        } else if (SzDuel_InqHandPhase(entry->unitId >> 8) == 1) {
                            entry->action = 0xA06;
                            entry->target = (entry->target & 0xFFFF0000) | 0x103;
                        } else {
                            entry->action = 0x6FF;
                            entry->target = (u16)entry->target | 0x1030000;
                        }
                    }
                } else {
                    switch (SzDuel_GetUnitKind(unitId >> 8, unitId & 0xFF) >> 5) {
                    case 0:
                    case 5:
                        if (TaUtil_IsExMonster(entry->unitId >> 8, entry->unitId & 0xFF) == 1) {
                            TaLogic020_CommandEfcMonster((s32)entry);
                        } else {
                            TaLogic020_CommandBtlUnit(entry, 1);
                        }
                        break;
                    case 2:
                        TaLogic_CommandEncUnit(entry, 5, 1, TaLogic_Manawyddan_GetWarnHideLvl(card) & 0xFF);
                        break;
                    case 1:
                    case 3:
                    case 4:
                        TaLogic020_CommandSpellUnit(entry);
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
s32 TaLogic_Manawyddan_GetNextActiveUnit(DuelPlayer *pCtl, s32 nSide, s32 pInput) {
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
    TaLogic_Manawyddan_CommandUnit(&pCtl->taskList[idx]);
    if (((pCtl->taskList[idx].mission >> 8) & 0xFF) == 10) {
        if (SzDuel_InqHandPhase(nSide) == 1 && TaLogic_Manawyddan_GetMinimumTask_Summon(pos, nSide, pInput) >= 0) {
            return pos | 0x10000;
        }
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_GetUnitStatus(nSide, 0, 0) == 0) {
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_InqHandPhase(nSide) == 1 && TaLogic_Manawyddan_GetMinimumTask_Summon(pos, nSide, pInput) >= 0) {
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
} Entry_00163C50;

typedef struct {
    u16 card;
    u8 flag;
    u8 pad;
} Slot_00163C50;

/* Orders a fighting unit (task `pTask`): straight at the enemy leader when `fGoalFirst` and the path is open,
   else at the nearest enemy it can beat. */
void TaLogic020_CommandBtlUnit(void *pTask, s32 fGoalFirst) {
    extern void TaLogic_InitIgnoreLst();
    extern s32 TaLogic_IsRootOpen();
    extern s32 TaLogic020_GetNearUnit();
    extern s32 TaLogic_Manawyddan_GetWarnHideLvl(s32);
    extern void TaLogic020_CommandInvadeUnit(void *);
    Entry_00163C50 *entry = pTask;
    s32 side;
    s32 player;
    s32 other;
    s32 pos;
    s32 otherPos;
    s32 i;
    u8 work[0x70];
    Slot_00163C50 list[22];
    s16 countA;
    s16 countB;

    if (SzDuel_GetUnit(entry->unitId >> 8, entry->unitId & 0xFF) != 0) {
        side = Ta_GetCurrentSide(entry->unitId >> 8, entry->unitId & 0xFF);
        other = (side == 0 ? 1 : 0) << 8;
        pos = SzDuel_GetUnitLoc(entry->unitId >> 8, entry->unitId & 0xFF);
        otherPos = SzDuel_GetUnitLoc(other >> 8, other & 0xFF);
        player = SzDuel_GetUnit(entry->unitId >> 8, entry->unitId & 0xFF);
        TaLogic_InitIgnoreLst(work);
        for (i = 0; i < 22; i++) {
            list[i].card = 0xFFFF;
            list[i].flag = 0xFF;
        }
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
            switch (TaLogic020_GetNearUnit(entry, 0, player, pos & 0xFF, pos >> 8,
                                  Ta_GetCurrentSide(entry->unitId >> 8, entry->unitId & 0xFF) == 0 ? 1 : 0,
                                  i & 0xFF, TaLogic_Manawyddan_GetWarnHideLvl(side), list, 0, &countA, &countB, 5, work)) {
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
        TaLogic020_CommandInvadeUnit(entry);
    }
}

/* TaLogic_GetNearUnit with this duelist's view and strength settings. */
s32 TaLogic020_GetNearUnit(s32 pTask, s32 pTree, s32 pVarInfo, s32 nX, s32 nZ, s32 eSide, s32 bDist, s32 WarnLvl, s32 nUnitLst, u16 wUnitNum, s32 wSize, s32 wNodeCount, u8 bChase, s32 wIgnoreLst) {
    return TaLogic_GetNearUnit(pTask, pTree, pVarInfo, nX, nZ, eSide, bDist, WarnLvl,
                 nUnitLst, wUnitNum, wSize, wNodeCount, bChase,
                 1, 3000, wIgnoreLst);
}

typedef struct {
    u16 location;
    u16 padding2;
    s16 field4;
    u16 padding6;
    union {
        u16 low;
        u32 word;
    } field8;
} State_00163F20;

/* Orders a unit (task `pTask`) to push into the opponent's side of the board. */
void TaLogic020_CommandInvadeUnit(void *pTask) {
    State_00163F20 *state = pTask;
    s32 loc;
    u16 location;
    u16 location2;

    location = state->location;
    Ta_IsUnitControl((s32) location >> 8, location & 0xFF);
    location2 = state->location;
    loc = SzDuel_GetUnitLoc((s32) location2 >> 8, location2 & 0xFF);
    state->field4 = 0x6FF;
    state->field8.word = state->field8.low |
        (TaLogic020_GetNextGrassPoint(loc & 0xFF, loc >> 8) << 16);
}

/* The next forest square toward the opponent from (nX, nZ). */
s32 TaLogic020_GetNextGrassPoint(s32 nX, s32 nZ) {
    if (nZ == 0) {
        if (nX >= 3) {
            return 0x106;
        }
        if (nX < 3) {
            return 0x100;
        }
    }
    if (nZ < 6) {
        if (nX >= 3) {
            return 0x605;
        }
        if (nX < 3) {
            return 0x601;
        }
    }
    if (nX >= 3) {
        return 0x601;
    }
    return 0x605;
}

typedef struct Entry_00164020 {
    u16 position;
    u8 flag;
    u8 padding;
} Entry_00164020;

/* Orders an effect monster (task `pTask`): where its effect does most. */
void TaLogic020_CommandEfcMonster(s32 pTask) {
    extern void TaLogic_InitIgnoreLst();
    extern s32 SzDuel_GetUnitCardNo();
    extern s32 TaLogic_Manawyddan_GetWarnHideLvl();
    extern s32 TaLogic_GetNearUnitL2();
    u8 work[112];
    Entry_00164020 entries[22];
    u16 first;
    u16 second;
    u16 count;
    s32 attempt;
    UnitTask *record = (UnitTask *)pTask;
    s32 kind;
    u16 coordinate;

    coordinate = record->ownerId;
    if (SzDuel_GetUnit((s32)coordinate >> 8, coordinate & 0xFF) != 0) {
        s32 owner;
        s32 position;
        s32 state;
        s32 unitInfo;
        s32 x;
        coordinate = record->ownerId;
        owner = Ta_GetCurrentSide((s32)coordinate >> 8, coordinate & 0xFF);
        coordinate = record->ownerId;
        position = SzDuel_GetUnitLoc((s32)coordinate >> 8, coordinate & 0xFF);
        count = 0;
        second = 0;
        first = 0;
        coordinate = record->ownerId;
        unitInfo = SzDuel_GetUnit((s32)coordinate >> 8, coordinate & 0xFF);
        {
            s32 i = 0;
            Entry_00164020 *entry = entries;
            do {
                i++;
                entry->position = 0xFFFF;
                entry->flag = 0xFF;
                entry++;
            } while (i < 22);
        }
        TaLogic_InitIgnoreLst(work);
        state = 0;
        coordinate = record->ownerId;
        kind = SzDuel_GetUnitCardNo((s32)coordinate >> 8, coordinate & 0xFF);
        switch (kind) {
        case 0x129:
            x = position >> 8;
                attempt = 1;
                position &= 0xFF;
                while (1) {
                    s32 result;
                    result = TaLogic_Manawyddan_GetWarnHideLvl(owner);
                    state = TaLogic_GetNearUnitL2(state, unitInfo, position, x, owner == 0 ? 1 : 0,
                                         (u8)attempt, 1, result, entries, &count,
                                         &first, &second, work);
                    result = TaLogic_GetNearUnitL3((void *)unitInfo, position, x, entries, 5, 0x34, 0, 2,
                                          1, TaLogic_Manawyddan_GetWarnHideLvl(owner), count);
                    if (result >= 0) {
                        record->mission = 0x2FF;
                        record->goal.dwGoal = (result << 16) | record->goal.wGoal[0];
                        return;
                    }
                    attempt++;
                    if (attempt <= 5) {
                        continue;
                    }
                    break;
                }
            break;
        case 0x4F:
            if (SzDuel_GetLP(owner) < 2000) {
                record->mission = 0x2FF;
                record->goal.dwGoal = (position << 16) | record->goal.wGoal[0];
            }
            break;
        }
        TaLogic020_CommandBtlUnit(record, 1);
    }
}

typedef struct {
    u16 location;
    u16 unk02;
    u16 flags;
    u16 unk06;
    union {
        u32 word;
        u16 low;
    } destination;
} Entry_00164260;

/* Orders a face-down magic card (task `pTask`): whether and where to open it. */
void TaLogic020_CommandSpellUnit(void *pTask) {
    Entry_00164260 *entry = pTask;
    s32 i;
    s32 location;
    s32 result;

    if (SzDuel_GetUnit(entry->location >> 8, entry->location & 0xFF) == 0) {
        return;
    }
    Ta_GetCurrentSide(entry->location >> 8, entry->location & 0xFF);
    SzDuel_GetUnitLoc(entry->location >> 8, entry->location & 0xFF);
    if (*(u16 *)((u8 *)SzDuel_GetUnit(entry->location >> 8, entry->location & 0xFF) + 0x3C) == 0x2B0) {
        entry->flags = 0xCFF;
    } else {
        entry->flags = 0x3FF;
    }
    i = 0;
    do {
        result = TaLogic020_GetLinePiece(i & 0xFF);
        location = result & 0xFFFF;
        result = SzDuel_GetMapUnitID(result & 0xFF, location >> 8);
        if (result == entry->location || result < 0) {
            entry->destination.word = (location << 16) | entry->destination.low;
            return;
        }
    } while (++i < 5);
    return;
}

/* The square this duelist's unit goes to on its line. */
s32 TaLogic020_GetLinePiece(s32 nSide) {
    s32 nSideLo;

    nSideLo = nSide & 0xFF;
    switch (nSideLo) {
    case 0:
        return 0x203;
    case 1:
        return 0x301;
    case 2:
        return 0x305;
    case 3:
        return 0x202;
    case 4:
        return 0x204;
    default:
        return 0x203;
    }
}

typedef struct {
    s16 id;
    u8 unk2;
    u8 pad3;
    s16 unk4;
    u8 pad6[6];
    s32 unkC;
} Ctx_001643F0;

typedef struct {
    u8 pad0[0x3C];
    u16 unk3C;
    u8 pad3E[0x22];
} Work_001643F0;

/* The summon task for side `nSide`: which hand cards to play and where, into `pInput`; -1 when it plays none. */
s32 TaLogic_Manawyddan_GetMinimumTask_Summon(s32 wUnit, s32 nSide, s32 pInput) {
    extern s32 TaLogic_GetUnitNum(s32, s32);
    extern s32 TaLogic_Manawyddan_GetWarnHideLvl();
    Work_001643F0 work;
    s32 ret;
    s32 res;
    s32 pos;
    s32 kind;
    Ctx_001643F0 *ctx = (Ctx_001643F0 *)pInput;

    ctx->id = wUnit;
    if (SzDuel_InqHandPhase(nSide) == 0) {
        return -1;
    }
    if (TaLogic_GetUnitNum(nSide, 0) == 5 && TaLogic_GetUnitNum(nSide, 1) == 5) {
        return -1;
    }
    kind = TaLogic020_IsHandPlay(nSide, &work);
    if (kind < 0) {
        return -1;
    }
    ctx->unk2 = 10;
    ctx->unkC = 0;
    pos = SzDuel_GetUnitLoc(wUnit >> 8, wUnit & 0xFF);
    if (kind == 0) {
        if (TaLogic020_SetComboQue(nSide, (u8 *)ctx, &work) >= 0) {
            ret = TaLogic_GetNearCard2(&work, pos & 0xFF, pos >> 8, nSide == 0 ? 1 : 0,
                                2, 0x1F, 2, 2, 1, TaLogic_Manawyddan_GetWarnHideLvl(nSide));
            if (ret < 0) {
                if (SzDuel_GetUnitMonsterCount(nSide) < 6) {
                    res = TaLogic020_GetSummonPiece(nSide, kind, &work, ret);
                    if (res < 0) {
                        return -1;
                    }
                    ctx->unk4 = res;
                    return 1;
                }
            } else {
                res = TaLogic020_GetSummonPiece(nSide, kind, &work, ret);
                if (res < 0) {
                    return -1;
                }
                ctx->unk4 = res;
                return 1;
            }
        }
    } else {
        ret = TaLogic_GetNearCard2(&work, pos & 0xFF, pos >> 8, nSide == 0 ? 1 : 0,
                            2, 0x1F, 2, 2, 1, TaLogic_Manawyddan_GetWarnHideLvl(nSide));
    }
    if (kind == 2) {
        TaLogic020_SetSpecialComboQue(nSide, ctx, &work);
        res = TaLogic020_GetSummonPiece(nSide, kind, &work, ret);
        if (res < 0) {
            return -1;
        }
        ctx->unk4 = res;
        return 1;
    }
    if (TaLogic020_GetSpellPlay(nSide, (u8 *)ctx, &work, work.unk3C) < 0) {
        return -1;
    }
    res = TaLogic020_GetSummonPiece(nSide, kind, &work, ret);
    if (res < 0) {
        return -1;
    }
    ctx->unk4 = res;
    return 1;
}

/* Whether side `nSide` should play from its hand this turn (and what, into `pInput`). */
s32 TaLogic020_IsHandPlay(s32 nSide, void *pInput) {
    extern s32 TaLogic_GetUnitNum();
    s32 ids[8];
    s32 data[8];
    u8 type = (u8)TaLogic_GetUnitNum(nSide, 0);
    u8 attr = (u8)TaLogic_GetUnitNum(nSide, 1);

    if (pInput == NULL) {
        return -1;
    }
    TaHand_GetNextHand(nSide, ids);
    if (type == 5) {
        s32 result = TaLogic020_GetSpellPlay(nSide, (u8 *)data, pInput, 0x3E7);
        if (result >= 0) {
            result = 1;
        } else {
            result = -1;
        }
        return result;
    }
    if (attr == 5) {
        s32 i;
        s32 *p;
        s32 count;

        i = 0;
        count = TaHand_GetNextHandNum(nSide);
        if (i < count) {
            p = ids;
            do {
                if ((TaHand_GetCardKind(*p) >> 5) == 0 && TaHand_CanAffordSummonCost(nSide, *p) == 1) {
                    SzDuel_InitCardInfo(pInput, ids[i]);
                    return 0;
                }
                p++;
                i++;
                count = TaHand_GetNextHandNum(nSide);
            } while (i < count);
        }
        return -1;
    }
    if (TaLogic020_GetSpecCardPlay(nSide, (u8 *)data, pInput, 0x34A) >= 0) {
        if (TaLogic020_IsDoCerem(nSide, 0x34A) == 1) {
            return 2;
        }
    }
    if (TaLogic020_GetSpecCardPlay(nSide, (u8 *)data, pInput, 0x352) >= 0) {
        if (TaLogic020_IsDoCerem(nSide, 0x352) == 1) {
            return 2;
        }
    }
    if (TaLogic020_GetTrapCardPlay(nSide, (u8 *)data, pInput) >= 0) {
        return 2;
    }
    {
        s32 *p;
        s32 i;
        s32 count;

        i = 0;
        count = TaHand_GetNextHandNum(nSide);
        if (i < count) {
            p = ids;
            do {
                if ((TaHand_GetCardKind(*p) >> 5) == 0 && TaHand_CanAffordSummonCost(nSide, *p) == 1) {
                    SzDuel_InitCardInfo(pInput, ids[i]);
                    return 0;
                }
                p++;
                i++;
                count = TaHand_GetNextHandNum(nSide);
            } while (i < count);
        }
    }
    {
        s32 result = TaLogic020_GetSpellPlay(nSide, (u8 *)data, pInput, 0x3E7);
        if (result >= 0) {
            return result;
        }
        return -1;
    }
}

/* Whether side `nSide` holds card `nCardNo` and can summon it (its slot into `bCombo`, the card into `pCardInfo`);
   returns its kind group or -1. */
s32 TaLogic020_GetSpecCardPlay(s32 nSide, void *bCombo, void *pCardInfo, s32 nCardNo) {
    s32 i;
    s32 ids[8];

    TaHand_GetNextHand(nSide, ids);
    for (i = 0; i < TaHand_GetNextHandNum(nSide); i++) {
        if ((nCardNo & 0xFFFF) == ids[i] && TaHand_CanAffordSummonCost(nSide, ids[i]) == 1) {
            *((s8 *)bCombo + 6) = i;
            SzDuel_InitCardInfo(pCardInfo, ids[i]);
            return TaHand_GetCardKind(ids[i]) >> 5;
        }
    }
    return -1;
}

/* The trap card side `nSide` plays from its hand now, its slot into `bCombo`, the card into `pCardInfo`; -1 if
   none. */
s32 TaLogic020_GetTrapCardPlay(s32 nSide, void *bCombo, void *pCardInfo) {
    s32 values[8];
    s32 index;
    s32 *p;

    TaHand_GetNextHand(nSide, values);
    index = 0;
    if (index < TaHand_GetNextHandNum(nSide)) {
        p = values;
        do {
            if (SzDuel_Kind2Type(TaHand_GetCardKind(*p) >> 5) == 2) {
                *((s8 *)bCombo + 6) = index;
                SzDuel_InitCardInfo(pCardInfo, values[index]);
                return TaHand_GetCardKind(values[index]) >> 5;
            }
            p++;
            index++;
        } while (index < TaHand_GetNextHandNum(nSide));
    }
    return -1;
}

/* Whether side `nSide` plays a magic or ritual card from its hand now (its slot into `bCombo`, the card into
   `pCardInfo`). */
s32 TaLogic020_GetSpellPlay(s32 nSide, u8 *bCombo, void *pCardInfo, s32 nMode) {
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

typedef struct Info_00164CE0 {
    u8 pad00[8];
    u16 x;
    s16 y;
} Info_00164CE0;

typedef struct Sprite_00164CE0 {
    Info_00164CE0 *info;
    u8 pad04[0x34];
    s16 x;
    s16 y;
} Sprite_00164CE0;

/* Fills hand combination `bCombo` for side `nSide`: the best fusion or equip chain, its card into `pCardInfo`. */
s32 TaLogic020_SetComboQue(s32 nSide, u8 *bCombo, void *pCardInfo) {
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
                            TaLogic_Manawyddan_ConvEmptyCombo(nSide, *node, entries);
                            TaLogic_CopyArray((u8 *)*node + 2, bCombo + 6);
                            SzDuel_InitCardInfo(pCardInfo, **node);
                            ((Sprite_00164CE0 *)pCardInfo)->x = (value >> 16) - (((Sprite_00164CE0 *)pCardInfo)->info->x & 0x1FFF);
                            ((Sprite_00164CE0 *)pCardInfo)->y = (value & 0xFFFF) - (((Sprite_00164CE0 *)pCardInfo)->info->y & 0x1FFF);
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
} Info_00164EC0;

/* Fills an empty combination: the hand card side `nSide` can summon with the best attack plus defence. */
void TaLogic_Manawyddan_ConvEmptyCombo(s32 nSide, void *pCardInfo, s32 *pResult) {
    Info_00164EC0 *info = pCardInfo;
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
                if (card != 0x3E7 && TaLogic020_IsRefuseEmptyCombo(card) == 0 && level >= TaHand_GetCardSummonCost2(card, nSide)) {
                    cost = TaHand_GetCardAPDP(card);
                    if ((cost & 0xFFFF) + (cost >> 16) * 2 == 0 && TaHand_IsCardEffect(card) == 2 &&
                        (u16)TaLogic_GetHandFusion(info->id, (u16)card) == 0x3E7) {
                        TaLogic_AddEmptyCombo(info->values, buf[i]);
                    }
                }
            }
        }
    }
}

/* Whether this duelist keeps card `nCardNo` out of a summon (it is wanted for an equip). */
s32 TaLogic020_IsRefuseEmptyCombo(s32 nCardNo) {
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
} Obj1_00165100;

typedef struct {
    u8 pad0[0x3C];
    u16 id;
} Obj2_00165100;

/* Fills hand combination `bCombo` for side `nSide` with this duelist's special combination, its card into
   `pCardInfo`. */
s32 TaLogic020_SetSpecialComboQue(s32 nSide, void *bCombo, void *pCardInfo) {
    Obj1_00165100 *o1 = bCombo;
    Obj2_00165100 *o2 = pCardInfo;
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
    return 1;
}

typedef struct Nibbles_001652F0 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_001652F0;

/* The task's target square: the second half-word when the second argument is 1, else the first. */
static inline u16 target_001652F0(u8 index) {
    switch (index) {
        case 0: return (u16)0x203;
        case 1: return (u16)0x301;
        case 2: return (u16)0x305;
        case 3: return (u16)0x202;
        case 4: return (u16)0x204;
        default: return (u16)0x203;
    }
}

/* The fallback square for (x, y): a corner of the near or far row. */
static inline s32 fallback_001652F0(s32 x, s32 y) {
    if (y == 0) {
        if (x >= 3) return 0x106;
        if (x < 3) return 0x100;
    }
    if (y < 6) {
        if (x >= 3) return 0x605;
        if (x < 3) return 0x601;
    }
    if (x >= 3) return 0x601;
    return 0x605;
}

/* The square side `nSide` summons a card of kind `sKind` to. */
s32 TaLogic020_GetSummonPiece(s32 nSide, u8 sKind, void *pInput, s32 nMode) {
    extern s32 TaLogic_Manawyddan_GetWarnHideLvl();
    extern s32 TaLogic_IsUnitWin4();
    extern s32 TaLogic_GetInvadeRoot2();
    extern s32 TaLogic_GetRoot2(void *, void *, s32, s32, s32, s32, u16, u8);
    s32 bestCandidate;
    s32 bestScore;
    s32 index;
    s32 searchCandidate;
    s32 fallbackCandidate;
    Nibbles_001652F0 path[12];
    s32 targetY1;
    s32 targetX1;
    s32 targetY2;
    s32 targetY;
    s32 targetX;
    s32 score;
    s32 target;
    s32 occupied;
    s32 limit;
    u8 kind;
    s32 count;
    Nibbles_001652F0 *p;

    if (pInput == NULL) {
        return -1;
    }
    p = path;
    count = 0;
    do {
        count++;
        p->low = p->high = 15;
        p++;
    } while (count < 12);

    kind = *(u8 *)((u8 *)pInput + 0x3E) >> 5;
    if (kind == 0 || kind == 5) {
        if (nMode >= 0) {
            s32 candidate;
            s32 y;
            s32 x;
            s32 i;
            bestScore = 255;
            bestCandidate = 65535;
            target = SzDuel_GetUnitLoc(nMode >> 8, nMode & 255);
            i = 0;
            targetY1 = target >> 8;
            targetX1 = target & 255;
            do {
                candidate = Ta_GetSommonPiecePreference(nSide, i);
                if (candidate >= 0) {
                    x = candidate & 255;
                    y = candidate >> 8;
                    if (SzDuel_GetField(x, y) != 8 &&
                        (SzDuel_GetField(x, y) != 9 || Ta_IsVirus_Chk3(pInput, x, y) != 1) &&
                        SzDuel_GetMapUnit(x, y) == 0) {
                        if (TaLogic_IsUnitWin4(pInput, nMode, TaLogic_Manawyddan_GetWarnHideLvl(nSide), targetX1, targetY1, 1) > 0) {
                            score = TaLogic_GetInvadeRoot2(pInput, path, x, y, targetX1, targetY1, nMode, 1, 5, (u16)TaLogic_Manawyddan_GetWarnHideLvl(nSide));
                        } else {
                            score = TaLogic_GetRoot2(pInput, path, x, y, targetX1, targetY1, nMode, 5);
                        }
                        if (TaLogic_GetMinGoalCount((u8 *)path) > 0 && score < bestScore) {
                            bestScore = score;
                            bestCandidate = candidate;
                        }
                    }
                }
                i++;
            } while (i < 8);
            if (bestCandidate != 65535) {
                return bestCandidate;
            }
        }
        {
            s32 y2;
            s32 x2;
            s32 targetX2;
            s32 j;
            s32 candidate2;
        limit = 14;
        fallbackCandidate = -1;
        j = 0;
        do {
            candidate2 = Ta_GetSommonPiecePreference(nSide, j);
            if (candidate2 >= 0) {
                x2 = candidate2 & 255;
                y2 = candidate2 >> 8;
                if (SzDuel_GetField(x2, y2) != 8 &&
                    (SzDuel_GetField(x2, y2) != 9 || Ta_IsVirus_Chk3(pInput, x2, y2) != 1) &&
                    SzDuel_GetMapUnitID(x2, y2) < 0) {
                    target = fallback_001652F0(x2, y2);
                    targetX2 = target & 255;
                    targetY2 = target >> 8;
                    occupied = SzDuel_GetMapUnitID(targetX2, targetY2);
                    if (occupied < 0) {
                        occupied = 65535;
                    }
                    score = TaLogic_GetRoot2(pInput, path, x2, y2, targetX2, targetY2, occupied, 7);
                    if (score < limit && score >= 0) {
                        fallbackCandidate = candidate2;
                        limit = score;
                    }
                }
            }
            j++;
        } while (j < 8);
        if (limit < 14) {
            return fallbackCandidate;
        } else {
            fallbackCandidate = -1;
        }
        return fallbackCandidate;
        }
    } else {
        s32 k;
        s32 y3;
        s32 x3;
        s32 limit3;
        s32 candidate3;
        index = 0;
        do {
            target = (u16)target_001652F0((u8)index);
            limit3 = 14;
            searchCandidate = -1;
            if (target >= 0) {
                k = 0;
                targetY = target >> 8;
                targetX = target & 255;
                do {
                    candidate3 = Ta_GetSommonPiecePreference(nSide, k);
                    if (candidate3 >= 0) {
                        x3 = candidate3 & 255;
                        y3 = candidate3 >> 8;
                        if (SzDuel_GetField(x3, y3) != 8 &&
                            (SzDuel_GetField(x3, y3) != 9 || Ta_IsVirus_Chk3(pInput, x3, y3) != 1) &&
                            SzDuel_GetMapUnitID(x3, y3) < 0) {
                            occupied = SzDuel_GetMapUnitID(x3, y3);
                            if (occupied < 0) {
                                occupied = 65535;
                            }
                            score = TaLogic_GetRoot2(pInput, path, x3, y3, targetX, targetY, occupied, 7);
                            if (score < limit3 && score >= 0) {
                                searchCandidate = candidate3;
                                limit3 = score;
                            }
                        }
                    }
                    k++;
                } while (k < 8);
                if (limit3 < 14) {
                    return searchCandidate;
                }
            }
            index++;
        } while (index < 5);
    }
    return -1;
}

typedef struct Nibbles_001658F0 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_001658F0;

typedef struct Output_001658F0 {
    u16 position;
    u8 action;
    u8 pad3;
    u16 destination;
    u8 pad6[6];
    s32 special;
    u8 result;
} Output_001658F0;

/* The task of a unit running from danger (task `pTask`): the safest square in reach, into `pInput` (`fFirst` = 1
   for the unit's first-choice task). */
s32 TaLogic_Manawyddan_GetMinimumTask_RunMission(UnitTask *pTask, s32 nSide, void *pInput, u8 fFirst) {
    Output_001658F0 *output = pInput;
    s32 target;
    u8 endX;
    u8 extra;
    Nibbles_001658F0 nibbles[12];
    s32 bestScore;
    s32 best;
    s32 i;
    Nibbles_001658F0 *p;
    extern s32 TaLogic_Manawyddan_IsOpenUnit();
    extern s32 TaLogic_Manawyddan_GetWarnHideLvl();
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

        initialScore = TaLogic_Manawyddan_GetWarnHideLvl(nSide);
        centerX = target & 0xFF;
        centerY = target >> 8;
        if (TaLogic_GetUnitWarning(centerX, centerY, pTask->ownerId, 2, initialScore, 1) == 0) {
            output->position = pTask->ownerId;
            output->action = 6;
            output->destination = target;
            output->result = TaLogic_IsDefStyleUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, output->destination, 1, 1);
            output->special = TaLogic_Manawyddan_IsOpenUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, pTask);
            TaLogic_InitRogicControl(pTask, fFirst);
            return 0;
        }
        if ((range = GetMoveRange(SzDuel_GetUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF), centerX, centerY)) == 0) {
            output->position = pTask->ownerId;
            output->action = 6;
            output->destination = target;
            output->result = TaLogic_IsDefStyleUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, output->destination, 1, 1);
            output->special = TaLogic_Manawyddan_IsOpenUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, pTask);
            TaLogic_InitRogicControl(pTask, fFirst);
            return 0;
        }
        if (SzDuel_GetUnitStatus(pTask->ownerId >> 8, pTask->ownerId & 0xFF, 4) != 0) {
            if ((SzDuel_GetUnitKind(pTask->ownerId >> 8, pTask->ownerId & 0xFF) >> 5) == 1 ||
                (SzDuel_GetUnitKind(pTask->ownerId >> 8, pTask->ownerId & 0xFF) >> 5) == 5) {
                SzDuel_SetUnitStatus(pTask->ownerId >> 8, pTask->ownerId & 0xFF, 0, 1);
                output->position = pTask->ownerId;
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
        if ((pTask->ownerId & 0xFF) == 0) {
            extra = (u8)TaLogic_IsAttackedNow(pTask->ownerId >> 8, pTask->ownerId & 0xFF, 1);
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
                    if (TaLogic_IsAttackedNow2(pTask->ownerId >> 8, pTask->ownerId & 0xFF, x, y, 1) == 0 || (u8)pTask->ownerId == 0) {
                        candidateScore = TaLogic_GetUnitWarning(x, y, pTask->ownerId, 2, (u16)TaLogic_Manawyddan_GetWarnHideLvl(nSide), 1);
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
                output->result = TaLogic_IsDefStyleUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, output->destination, 1, 1);
            } else {
                output->result = TaLogic_IsDefStyleUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, output->destination, 0, 1);
            }
            output->special = TaLogic_Manawyddan_IsOpenUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, pTask);
        } else {
            output->position = pTask->ownerId;
            output->action = 6;
            output->destination = target;
            output->result = TaLogic_IsDefStyleUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, output->destination, 1, 1);
            output->special = TaLogic_Manawyddan_IsOpenUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, pTask);
        }
        TaLogic_InitRogicControl(pTask, fFirst);
        return 0;
    }
}

typedef struct Coord_00165EC0 {
    u8 x : 4;
    u8 y : 4;
} Coord_00165EC0;

typedef struct Input_00165EC0 {
    u16 position;
    u8 pad[6];
    u32 targets;
} Input_00165EC0;

typedef struct Output_00165EC0 {
    u16 position;
    u8 command;
    u8 pad3;
    u16 destination;
    u8 pad6[6];
    s32 flag;
    u8 result;
} Output_00165EC0;

/* The task's target square: the second half-word when the second argument is 1, else the first. */
static inline u32 target_00165EC0(void *input, u8 mode) {
    Input_00165EC0 *p = input;
    if (mode == 1) {
        return (u16)(p->targets >> 16);
    }
    return *(u16 *)&p->targets;
}

/* The task of a unit attacking (task `pTask`): its path to the goal, into `pInput`; -1 when it has none (`fFirst`
   = 1 for the unit's first-choice task). */
s32 TaLogic_Manawyddan_GetMinimumTask_AtkMission(void *pTask, s32 nSide, void *pInput, u8 fFirst) {
    extern s32 TaLogic_Manawyddan_IsOpenUnit();
    extern s32 TaLogic_Manawyddan_GetWarnHideLvl();
    extern void TaLogic_GetInvadeRoot();
    Input_00165EC0 *input = pTask;
    Output_00165EC0 *output = pInput;
    s32 fallback;
    s32 source;
    s32 count;
    s32 target;
    s32 sourceY;
    s32 sourceX;
    s32 targetY;
    s32 targetX;
    Coord_00165EC0 *candidate;
    s32 flag;
    s32 i;
    s32 bestCost;
    s32 bestIndex;
    Coord_00165EC0 coords[12];
    s32 cost;
    s32 position;
    u32 low;
    u32 high;

    low = target_00165EC0(input, fFirst);
    high = target_00165EC0(input, fFirst);
    if (SzDuel_GetUnit((u32)high >> 8, low & 0xFF) == 0) {
        TaLogic_InitRogicControl(input, 1);
        return -1;
    }
    fallback = TaLogic_Manawyddan_IsOpenUnit(input->position >> 8, input->position & 0xFF, input);
    source = SzDuel_GetUnitLoc(input->position >> 8, input->position & 0xFF);
    low = target_00165EC0(input, fFirst);
    high = target_00165EC0(input, fFirst);
    target = SzDuel_GetUnitLoc((u32)high >> 8, low & 0xFF);
    {
        s32 j = 0;
        Coord_00165EC0 *cursor = coords;
        do {
            cursor->x = cursor->y = 15;
            cursor++;
            j++;
        } while (j < 12);
    }
    cost = SzDuel_GetUnit(input->position >> 8, input->position & 0xFF);
    sourceX = source & 0xFF;
    sourceY = source >> 8;
    if (GetMoveRange(cost, sourceX, sourceY) == 0) {
        output->position = input->position;
        output->command = 6;
        output->destination = source;
        cost = TaLogic_GetUnitWarning(sourceX, sourceY, nSide, 2, 0,
                           (u8)TaLogic_Manawyddan_GetWarnHideLvl(nSide));
        if (cost >= SzDuel_GetUnitAP(input->position >> 8, input->position & 0xFF, 0)) {
            output->result = TaLogic_IsDefStyleUnit(input->position >> 8, input->position & 0xFF,
                                         output->destination, 1, 1);
        } else {
            output->result = TaLogic_IsDefStyleUnit(input->position >> 8, input->position & 0xFF,
                                         output->destination, 0, 1);
        }
        TaLogic_InitRogicControl(input, fFirst);
    } else {
        position = input->position;
        cost = (u16)TaLogic_Manawyddan_GetWarnHideLvl(nSide);
        TaLogic_GetInvadeRoot(position >> 8, position & 0xFF, coords, sourceX, sourceY,
                     targetX = target & 0xFF, targetY = target >> 8,
                     target_00165EC0(input, fFirst), 1, 30, cost);
        count = TaLogic_GetMinGoalCount((u8 *)coords);
        bestIndex = 0xFF;
        if (count > 0) {
            flag = 0;
            bestCost = 0xFFFF;
            for (i = 0; i < count; i++) {
                if (TaLogic020_IsOpenMoveUnit(input->position >> 8, input->position & 0xFF,
                                 sourceX, sourceY, targetX, targetY) == 1) {
                    bestIndex = i;
                    flag = 1;
                    coords[i].x = targetX;
                    coords[i].y = targetY;
                    i = count;
                } else {
                    candidate = &coords[i];
                    cost = TaLogic_GetUnitWarning(candidate->x, candidate->y, nSide, 5, 0,
                                       (u8)TaLogic_Manawyddan_GetWarnHideLvl(nSide));
                    if (cost < bestCost) {
                        bestCost = cost;
                        bestIndex = i;
                    } else if (cost == bestCost) {
                        Coord_00165EC0 *selected = &coords[bestIndex];
                        s32 oldMinY;
                        s32 oldMaxY;
                        s32 oldMinX;
                        s32 oldMaxX;
                        s32 newMinY;
                        s32 newMaxY;
                        s32 newMinX;
                        s32 newMaxX;
                        oldMinY = selected->y < targetY ? selected->y : targetY;
                        oldMaxY = targetY < selected->y ? selected->y : targetY;
                        oldMinX = selected->x < targetX ? selected->x : targetX;
                        oldMaxX = targetX < selected->x ? selected->x : targetX;
                        newMinY = candidate->y < targetY ? candidate->y : targetY;
                        newMaxY = targetY < candidate->y ? candidate->y : targetY;
                        newMinX = candidate->x < targetX ? candidate->x : targetX;
                        newMaxX = targetX < candidate->x ? candidate->x : targetX;
                        if ((newMaxX - newMinX) + (newMaxY - newMinY) <
                            (oldMaxX - oldMinX) + (oldMaxY - oldMinY)) {
                            bestCost = cost;
                            bestIndex = i;
                        }
                    }
                }
            }

        } else {
            output->position = input->position;
            output->command = 6;
            output->destination = source;
            output->flag = fallback;
            output->result = TaLogic_IsDefStyleUnit(input->position >> 8, input->position & 0xFF,
                                         output->destination, 0, 1);
            TaLogic_InitRogicControl(input, fFirst);
            return 0;
        }
        if (bestIndex != 0xFF) {
            output->position = input->position;
            output->command = 6;
            output->destination = (coords[bestIndex].y << 8) | coords[bestIndex].x;
            output->flag = flag;
            output->result = TaLogic_IsDefStyleUnit(input->position >> 8, input->position & 0xFF,
                                         output->destination, 0, 1);
        } else {
            output->position = input->position;
            output->command = 6;
            output->destination = source;
            output->flag = flag;
            output->result = TaLogic_IsDefStyleUnit(input->position >> 8, input->position & 0xFF,
                                         output->destination, 0, 1);
            TaLogic_InitRogicControl(input, fFirst);
            return 0;
        }
    }
    return 0;
}

typedef struct Coord_001664A0 {
    u8 x : 4;
    u8 y : 4;
} Coord_001664A0;

typedef struct Output_001664A0 {
    u16 position;
    u8 kind;
    u8 pad3;
    u16 target;
    u8 pad6[6];
    s32 value;
    u8 flag;
} Output_001664A0;

/* The task's target square: the second half-word when the second argument is 1, else the first. */
static inline u32 target_001664A0(void *unit, s32 side) {
    return side == 1 ? (u32)(u16)(((UnitTask *)unit)->goal.dwGoal >> 16) : (u32)((UnitTask *)unit)->goal.wGoal[0];
}

/* The smaller of the two values. */
static inline u32 minY_001664A0(void *unit, s32 side, u8 coord) {
    return coord < (target_001664A0(unit, side) >> 8) ? coord : (target_001664A0(unit, side) >> 8);
}

/* The larger of the two values. */
static inline u32 maxY_001664A0(void *unit, s32 side, u8 coord) {
    return (target_001664A0(unit, side) >> 8) < coord ? coord : (target_001664A0(unit, side) >> 8);
}

/* The smaller of the two values. */
static inline u32 minX_001664A0(void *unit, s32 side, u8 coord) {
    return coord < (target_001664A0(unit, side) & 0xFF) ? coord : (target_001664A0(unit, side) & 0xFF);
}

/* The larger of the two values. */
static inline u32 maxX_001664A0(void *unit, s32 side, u8 coord) {
    return (target_001664A0(unit, side) & 0xFF) < coord ? coord : (target_001664A0(unit, side) & 0xFF);
}

/* The task of a unit moving to its goal (task `pTask`), into `pInput` (`fFirst` = 1 for the unit's first-choice
   task). */
s32 TaLogic_Manawyddan_GetMinimumTask_MoveMission(void *pTask, s32 nSide, void *pInput, u8 fFirst, u8 nKind) {
    extern s32 TaLogic_Manawyddan_IsOpenUnit();
    extern s32 TaLogic_Manawyddan_GetWarnHideLvl();
    extern s32 TaLogic_GetUnitWarning();
    extern void TaLogic_GetRoot();
    extern s32 TaLogic_IsDefStyleUnit(s32, s32, s32, u8, s32);
    Coord_001664A0 coords[12];
    s32 initial;
    s32 cell;
    s32 count;

    initial = SzDuel_GetUnitLoc(((UnitTask *)pTask)->ownerId >> 8, ((UnitTask *)pTask)->ownerId & 0xFF);
    {
    s32 bestScore;
    s32 best;
    s32 side = fFirst;
    Coord_001664A0 *candidate;
    s32 index;
    if (target_001664A0(pTask, side) == 0xFFFF) {
        if (initial == target_001664A0(pTask, side)) {
            ((Output_001664A0 *)pInput)->position = ((UnitTask *)pTask)->ownerId;
            ((Output_001664A0 *)pInput)->kind = 6;
            ((Output_001664A0 *)pInput)->target = initial;
            ((Output_001664A0 *)pInput)->flag = TaLogic_IsDefStyleUnit(((UnitTask *)pTask)->ownerId >> 8, ((UnitTask *)pTask)->ownerId & 0xFF, ((Output_001664A0 *)pInput)->target, nKind, 1);
            ((Output_001664A0 *)pInput)->value = TaLogic_Manawyddan_IsOpenUnit(((UnitTask *)pTask)->ownerId >> 8, ((UnitTask *)pTask)->ownerId & 0xFF, pTask);
            TaLogic_InitRogicControl(pTask, fFirst);
            return 0;
        }
    }

    if (SzDuel_GetUnitStatus(((UnitTask *)pTask)->ownerId >> 8,
                      ((UnitTask *)pTask)->ownerId & 0xFF, 4) != 0) {
        if ((SzDuel_GetUnitKind(((UnitTask *)pTask)->ownerId >> 8,
                          ((UnitTask *)pTask)->ownerId & 0xFF) >> 5) == 1 ||
            (SzDuel_GetUnitKind(((UnitTask *)pTask)->ownerId >> 8,
                          ((UnitTask *)pTask)->ownerId & 0xFF) >> 5) == 5) {
            SzDuel_SetUnitStatus(((UnitTask *)pTask)->ownerId >> 8,
                          ((UnitTask *)pTask)->ownerId & 0xFF, 0, 1);
            ((Output_001664A0 *)pInput)->position = ((UnitTask *)pTask)->ownerId;
            ((Output_001664A0 *)pInput)->kind = 14;
            return 0;
        }
    }

    candidate = coords;
    {
        s32 i = 0;
        Coord_001664A0 *entry = candidate;
        do {
            entry->x = entry->y = 0xF;
            i++;
            entry++;
        } while (i < 12);
    }

    cell = SzDuel_GetMapUnitID(target_001664A0(pTask, side) & 0xFF, ((u32)target_001664A0(pTask, side)) >> 8);
    if (cell < 0) {
        cell = 0xFFFF;
    }
    TaLogic_GetRoot(((UnitTask *)pTask)->ownerId >> 8, ((UnitTask *)pTask)->ownerId & 0xFF,
                 coords, initial & 0xFF, initial >> 8, target_001664A0(pTask, side) & 0xFF,
                 ((u32)target_001664A0(pTask, side)) >> 8, (u16)cell, 7);
    count = TaLogic_GetMinGoalCount((u8 *)coords);
    {
        if (count > 0) {
        best = 0xFF;
        bestScore = 0xFFFF;
        for (index = 0; index < count; index++) {
                if (SzDuel_GetMapUnit(candidate->x, candidate->y) == 0) {
                    s32 score = TaLogic_GetUnitWarning(candidate->x, candidate->y, nSide, 5, 0, (u8)TaLogic_Manawyddan_GetWarnHideLvl(nSide));
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
                        bestMinY = minY_001664A0(pTask, side, bestY);
                        bestMaxY = maxY_001664A0(pTask, side, bestY);
                        bestX = (&coords[best])->x;
                        bestMinX = minX_001664A0(pTask, side, bestX);
                        bestMaxX = maxX_001664A0(pTask, side, bestX);
                        currentY = (u8)candidate->y;
                        currentMinY = minY_001664A0(pTask, side, currentY);
                        currentMaxY = maxY_001664A0(pTask, side, currentY);
                        currentX = candidate->x;
                        currentMinX = minX_001664A0(pTask, side, currentX);
                        currentMaxX = maxX_001664A0(pTask, side, currentX);
                        if ((currentMaxX - currentMinX) + (currentMaxY - currentMinY) < (bestMaxX - bestMinX) + (bestMaxY - bestMinY)) {
                            bestScore = score;
                            best = index;
                        }
                    }
                }
            candidate++;
        }
    } else {
        ((Output_001664A0 *)pInput)->position = ((UnitTask *)pTask)->ownerId;
            ((Output_001664A0 *)pInput)->kind = 6;
            ((Output_001664A0 *)pInput)->target = initial;
            ((Output_001664A0 *)pInput)->flag = TaLogic_IsDefStyleUnit(((UnitTask *)pTask)->ownerId >> 8, ((UnitTask *)pTask)->ownerId & 0xFF, ((Output_001664A0 *)pInput)->target, nKind, 1);
            ((Output_001664A0 *)pInput)->value = TaLogic_Manawyddan_IsOpenUnit(((UnitTask *)pTask)->ownerId >> 8, ((UnitTask *)pTask)->ownerId & 0xFF, pTask);
        TaLogic_InitRogicControl(pTask, fFirst);
        return 0;
    }

        if (best != 0xFF) {
            ((Output_001664A0 *)pInput)->position = ((UnitTask *)pTask)->ownerId;
            ((Output_001664A0 *)pInput)->kind = 6;
            ((Output_001664A0 *)pInput)->target = (coords[best].y << 8) | coords[best].x;
            ((Output_001664A0 *)pInput)->flag = TaLogic_IsDefStyleUnit(((UnitTask *)pTask)->ownerId >> 8, ((UnitTask *)pTask)->ownerId & 0xFF, ((Output_001664A0 *)pInput)->target, nKind, 1);
            ((Output_001664A0 *)pInput)->value = TaLogic_Manawyddan_IsOpenUnit(((UnitTask *)pTask)->ownerId >> 8, ((UnitTask *)pTask)->ownerId & 0xFF, pTask);
        } else {
            ((Output_001664A0 *)pInput)->position = ((UnitTask *)pTask)->ownerId;
            ((Output_001664A0 *)pInput)->kind = 6;
            ((Output_001664A0 *)pInput)->target = initial;
            ((Output_001664A0 *)pInput)->flag = TaLogic_IsDefStyleUnit(((UnitTask *)pTask)->ownerId >> 8, ((UnitTask *)pTask)->ownerId & 0xFF, ((Output_001664A0 *)pInput)->target, nKind, 1);
            ((Output_001664A0 *)pInput)->value = TaLogic_Manawyddan_IsOpenUnit(((UnitTask *)pTask)->ownerId >> 8, ((UnitTask *)pTask)->ownerId & 0xFF, pTask);
        }
        TaLogic_InitRogicControl(pTask, fFirst);
    }
    }
    return 0;
}

typedef struct {
    u8 low : 4;
    u8 high : 4;
} Nibbles_00166D10;

typedef struct {
    u16 pos;
    u8 kind;
    u8 pad3;
    u16 target;
    u8 pad6[6];
    s32 flag;
    u8 result;
} Out_00166D10;

/* The task of reviving a monster from the graveyard (task `pTask`), into `pInput` (`fFirst` = 1 for the unit's
   first-choice task). */
s32 TaLogic_Manawyddan_GetMinimumTask_ReviveMission(u16 *pTask, s32 nSide, void *pInput, u8 fFirst) {
    u16 *unit = pTask;
    s32 card;
    s32 col;
    u16 row;
    Out_00166D10 *out = pInput;
    Nibbles_00166D10 entries[12];
    s32 i;
    Nibbles_00166D10 *entry;

    SzDuel_GetUnitLoc(*unit >> 8, *unit & 0xFF);
    entry = entries;
    i = 0;
    do {
        entry->low = entry->high = 15;
        entry++;
        i++;
    } while (i < 12);
    card = TaLogic020_IsUseRevive(nSide);
    if (TaLogic_GetActionReaction(*unit >> 8, *unit & 0xFF, 0, 0, 6, 1) == 5) {
        card = -1;
    }
    if (card >= 0) {
        row = card >> 16;
        col = TaLogic_GetGraveEntryAfterScreen(row, card & 0xFF, 0x1E);
        out->pos = *unit;
        out->kind = 12;
        out->result = TaLogic_IsDefStyleUnit(*unit >> 8, *unit & 0xFF, out->target, 1, 1);
        out->flag = 1;
        out->target = (row << 8) | col;
        TaLogic_InitRogicControl(unit, fFirst);
        return 0;
    }
    if (SzDuel_GetUnitStatus(*unit >> 8, *unit & 0xFF, 4) != 0) {
        SzDuel_SetUnitStatus(*unit >> 8, *unit & 0xFF, 0, 1);
        out->pos = *unit;
        out->kind = 14;
        return 0;
    }
    return TaLogic_Manawyddan_GetMinimumTask_MoveMission(unit, nSide, out, fFirst, 1);
}

/* From the dotr-decomp CC0 bundle (commit 88c32bb2), chatC/imp/conv.py. */

extern int func_001DEE50_b(int index);
struct DotrScanEntry {
    unsigned char unknown_00[3];
    unsigned char unknown_03;
};
struct DotrScanPair {
    unsigned word;
};
struct DotrScanHeld {
    struct DotrScanEntry *entry;
    int unknown_04[23];
};
extern struct DotrScanPair *func_001E09E0_b(struct DotrScanHeld *held, int n);

/* Whether side `nSide` should use a revive card now. */
int TaLogic020_IsUseRevive(int nSide)
{
    struct DotrScanHeld held;
    int i;
    int best;
    int result;
    int id;
    struct DotrScanPair *pair;
    int n;

    best = 40;
    result = -1;
    if (SzDuel_GetUnitSpellCount(nSide) >= 5) {
        return result;
    }
    for (i = 0; i < func_001DEE50_b(nSide); i++) {
        id = SzDuel_InqGrave(nSide, i);
        if (TaHand_GetCardKind(id) >> 5 != 0) {
            SzDuel_InitCardInfo((int *)&held, id);
            pair = func_001E09E0_b(&held, 0);
            n = held.entry->unknown_03;
            if (n >= best && pair->word >> 8 != 20) {
                best = n;
                result = nSide << 16 | i;
            }
        }
    }
    for (i = 0; i < func_001DEE50_b(nSide == 0 ? 1 : 0); i++) {
        id = SzDuel_InqGrave(nSide == 0 ? 1 : 0, i);
        if (TaHand_GetCardKind(id) >> 5 != 0) {
            SzDuel_InitCardInfo((int *)&held, id);
            pair = func_001E09E0_b(&held, 0);
            n = held.entry->unknown_03;
            if (n >= best && pair->word >> 8 != 20) {
                best = n;
                result = i | (nSide == 0 ? 1 : 0) << 16;
            }
        }
    }
    return result;
}

/* Whether this duelist opens (turns face up) unit (nSide, nID) now: 0 no, 1 or 2 by its kind. */
s32 TaLogic_Manawyddan_IsOpenUnit(s32 nSide, s32 nID) {
    extern s32 SzDuel_GetUnitCardNo();
    extern s32 TaLogic_GetActionReaction();
    extern s32 SearchUnitByRange();
    u8 count;
    s32 card;
    s32 side;
    u32 *effect;
    s32 location;
    s32 i;
    s32 mask;
    s32 mask2;
    s32 j;
    s32 position;
    u32 fields;

    count = 0;
    card = SzDuel_GetUnitCardNo();
    side = Ta_IsUnitControl(nSide, nID);
    effect = SzDuel_GetUnitEffect(nSide, nID, 0);
    location = SzDuel_GetUnitLoc(nSide, nID);
    if (SzDuel_GetUnitStatus(nSide, nID, 4) != 0) {
        return 0;
    }
    switch (SzDuel_GetUnitKind(nSide, nID) >> 5) {
    case 5:
        if (TaLogic020_IsDoCerem(Ta_IsUnitControl(nSide, nID), card) == 1 &&
            SzDuel_GetField(location & 0xFF, location >> 8) != 9) {
            return 1;
        }
        break;
    case 1:
        if (TaLogic_GetActionReaction(nSide, nID, 0, 0, 6, 1) == 5) {
            return 2;
        }
        if (effect == NULL) {
            return 2;
        }
        fields = effect[0];
        switch (fields >> 8) {
        case 23:
            position = Ta_GetUnitOwnerIDFromLstCount(Ta_RemoveObjFromFlagLst(ConvUnitIDtoFlagList_OFF(
                SearchUnitByRange(0, 0, side, (fields >> 6) & 3, fields & 0x3F, 14),
                nSide, nID), side), 0);
            if (position >= 0 && side != Ta_IsUnitControl(position >> 8, position & 0xFF)) {
                return 1;
            }
            break;
        case 4:
            switch (effect[1] >> 16) {
            case 18:
                mask = ConvUnitIDtoFlagList_OFF(ConvUnitIDtoFlagList_OFF(ConvUnitIDtoFlagList_OFF(
                    SearchUnitByRange(location & 0xFF, location >> 8, side,
                        (fields >> 6) & 3, fields & 0x3F, 18),
                    nSide, nID), nSide, 0), nSide == 0 ? 1 : 0, 0);
                for (i = 0; i < Ta_GetUnitNumFrom22bitFlagList(mask); i++) {
                    position = Ta_GetUnitOwnerIDFromLstCount(mask, i);
                    if (position >= 0) {
                        if (side == Ta_IsUnitControl(position >> 8, position & 0xFF)) {
                            return 2;
                        }
                        count++;
                    }
                }
                if ((s32)(u8)count >= 0) {
                    return 1;
                }
                break;
            default:
                mask2 = Ta_RemoveObjFromFlagLst(ConvUnitIDtoFlagList_OFF(
                    SearchUnitByRange(0, 0, side, (fields >> 6) & 3, fields & 0x3F, 14),
                    nSide, nID), side);
                for (j = 0; j < Ta_GetUnitNumFrom22bitFlagList(mask2); j++) {
                    position = Ta_GetUnitOwnerIDFromLstCount(mask2, j);
                    if (position >= 0) {
                        if (side == Ta_IsUnitControl(position >> 8, position & 0xFF)) {
                            return 2;
                        }
                        count++;
                    }
                }
                if ((s32)(u8)count >= 0) {
                    return (u8)count;
                }
                break;
            }
            break;
        case 13:
            switch (SzDuel_GetUnitCardNo(nSide, nID)) {
            case 0x2C3:
                if (SzDuel_GetLP(side) < 2000) {
                    return 1;
                }
                break;
            case 0x2C9:
                return 1;
            case 0x2CA:
                if (SzDuel_GetUnitCount(side == 0 ? 1 : 0) >= 3) {
                    return 1;
                }
                break;
            }
            break;
        case 24:
            if (Ta_GetUnitNumFrom22bitFlagList(Ta_RemoveObjFromFlagLst(ConvUnitIDtoFlagList_OFF(
                SearchUnitByRange(0, 0, side, (fields >> 6) & 3, fields & 0x3F, 14),
                nSide, nID), side)) >= 5) {
                return 1;
            }
            break;
        case 38:
            if (SzDuel_InqHandPhase(side) == 0) {
                return 1;
            }
            break;
        }
        break;
    }
    return 2;
}

/* Whether unit (nSide, nID) may open while moving from (nX, nZ) to the square next to it, (gX, gZ). */
s32 TaLogic020_IsOpenMoveUnit(s32 nSide, s32 nID, s32 nX, s32 nZ,
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

/* Whether side `nSide` can play ritual card `nCardNo` now (it has the units to give up). */
s32 TaLogic020_IsDoCerem(s32 nSide, s32 nCardNo) {
    s32 sp20[4];

    Ta_GetCeremSacrifice(sp20, *(s32 *)((u8 *)TaHand_GetCardEffect(nCardNo, 0) + 4));
    if (Ta_GetSacrificeUnit(sp20, nSide) < 0) {
        return 0;
    }
    return 1;
}

/* How careful this duelist is about hidden cards (by its life points and monster count). */
s32 TaLogic_Manawyddan_GetWarnHideLvl(void) {
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
} Req_001676E0;

typedef struct {
    u8 pad0[0x160];
    u16 list[32];    /* 0x160 */
    u8 idx : 5;      /* 0x1A0 */
    u8 pad1A0 : 3;
    u8 pad1A1;
    u16 count;       /* 0x1A2 */
} Work_001676E0;

/* Computer duelist 20's controller (duelistControllers[20]): the buttons it presses this frame. With an empty
   input queue it plans its next task and turns it into buttons, then plays the queue back one button per frame;
   after 600 frames it gives up the turn (0x20, then 0x800). */
s32 duelistController20(s32 wCursorPos, void *pCtl) {
    Req_001676E0 req;
    Work_001676E0 *w;
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
        if (TaLogic_Manawyddan_GetMinimumTask(w, &req, wCursorPos) == 0) {
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

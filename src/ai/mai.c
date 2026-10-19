/* Computer AI of Margaret Mai Beaufort (duelist 13, duelistController13). */

#include "common.h"

s32 TaLogic_GetInputQueFromMinimumTask_b(void *, void *, s32);

typedef struct {
    u8 pad0[0x1A1];
    u8 lvl : 4;      /* 0x1A1 */
    u8 pad1A1 : 4;
} Ai_00146960;
#pragma conditional_move off

/* This duelist's move: picks the next unit to act, gives it a task and turns that into input `pInput`; returns 1
   when it set one. */
s32 TaLogic_Mai_GetMinimumTask(void *pCtl, void *pInput, s32 wCursorPos) {
    UnitTask *tasks = pCtl;
    Ai_00146960 *ai = pCtl;
    s32 side;
    s32 found;
    s32 result;
    s32 index;

    side = SzDuel_GetTurnOwner();
    found = 0;
    ai->lvl = TaLogic013_IsActiveMode();
    if ((result = TaLogic_Mai_GetNextActiveUnit(tasks, side, ai->lvl, pInput)) < 0) {
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
    TaLogic_Mai_CommandUnit(&tasks[index], ai->lvl);
    switch ((tasks[index].mission >> 8) & 0xFF) {
    case TASK_RUN:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            TaLogic_Mai_GetMinimumTask_RunMission(&tasks[index], side, pInput, 1);
            found = 1;
        }
        break;
    case TASK_ATTACK:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            if (TaLogic_Mai_GetMinimumTask_AtkMission(&tasks[index], side, pInput, 1) < 0) {
                TaLogic_InitRogicControl(&tasks[index], 1);
                return 1;
            }
            found = 1;
        }
        break;
    case TASK_SUMMON:
        if (TaLogic_Mai_GetMinimumTask_Summon(tasks[index].ownerId, side, pInput) < 0) {
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
            TaLogic_Mai_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 1, 0);
            found = 1;
        }
        break;
    case TASK_CONFIRMUNIT:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            TaLogic_Mai_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 1, 1);
            found = 1;
        }
        break;
    case TASK_ENCHANT:
        TaLogic_GetMinimumTask_EncMission(&tasks[index], side, pInput, 1, 0, TaLogic_Mai_GetWarnHideLvl(side), 5, 1);
        found = 1;
        break;
    case TASK_REVIVE:
        TaLogic_Mai_GetMinimumTask_ReviveMission(&tasks[index], side, pInput, 1);
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
            TaLogic_Mai_GetMinimumTask_RunMission(&tasks[index], side, pInput, 0);
            found = 1;
        }
        break;
    case 2:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            if (TaLogic_Mai_GetMinimumTask_AtkMission(&tasks[index], side, pInput, 0) < 0) {
                TaLogic_Mai_GetMinimumTask_RunMission(&tasks[index], side, pInput, 0);
            }
            found = 1;
        }
        break;
    case 10:
        if (TaLogic_Mai_GetMinimumTask_Summon(tasks[index].ownerId, side, pInput) < 0) {
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
            TaLogic_Mai_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 0, 0);
            found = 1;
        }
        break;
    case 3:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            TaLogic_Mai_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 0, 1);
            found = 1;
        }
        break;
    case 9:
        TaLogic_GetMinimumTask_EncMission(&tasks[index], side, pInput, 0, 0, TaLogic_Mai_GetWarnHideLvl(side), 5, 1);
        found = 1;
        break;
    case 12:
        TaLogic_Mai_GetMinimumTask_ReviveMission(&tasks[index], side, pInput, 0);
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
#pragma conditional_move reset

/* Gives the unit of task `pTask` its order for this turn (attack, run, move, summon, guard). */
s32 TaLogic_Mai_CommandUnit(UnitTask *pCtl, s32 pTask) {
    extern s32 TaLogic013_IsUnitInvader();
    s32 controllingSide;

    SzDuel_GetUnitLoc(pCtl->ownerId >> 8, pCtl->ownerId & 0xFF);
    controllingSide = Ta_IsUnitControl(pCtl->ownerId >> 8, pCtl->ownerId & 0xFF);
    if (SzDuel_GetUnit(pCtl->ownerId >> 8, pCtl->ownerId & 0xFF) != 0) {
        if (SzDuel_GetUnitStatus(pCtl->ownerId >> 8, pCtl->ownerId & 0xFF, 0) == 0) {
            if (pCtl->ownerId != 0xFFFF) {
                if ((pCtl->ownerId & 0xFF) == 0) {
                    if ((s32)pCtl->dwGoal == -1) {
                        if (TaLogic_IsAttackedNow(pCtl->ownerId >> 8, pCtl->ownerId & 0xFF, 0) == 1) {
                            if (SzDuel_InqHandPhase(pCtl->ownerId >> 8) == 1) {
                                *(s16 *)&pCtl->mission = 0x50A;
                            } else {
                                *(s16 *)&pCtl->mission = 0x5FF;
                            }
                        } else {
                            if (SzDuel_InqHandPhase(pCtl->ownerId >> 8) == 1) {
                                *(s16 *)&pCtl->mission = 0xA05;
                            } else {
                                *(s16 *)&pCtl->mission = 0x5FF;
                            }
                        }
                    }
                } else {
                    switch (SzDuel_GetUnitKind(pCtl->ownerId >> 8, pCtl->ownerId & 0xFF) >> 5) {
                    case 0:
                        if (TaLogic013_IsUnitInvader(pCtl->ownerId >> 8, pCtl->ownerId & 0xFF) == 1) {
                            TaLogic013_CommandInvadeUnit(pCtl);
                        } else if (TaUtil_IsExMonster(pCtl->ownerId >> 8, pCtl->ownerId & 0xFF) == 1) {
                            TaLogic013_CommandEfcMonster(pCtl);
                        } else {
                            TaLogic013_CommandBtlUnit(pCtl);
                        }
                        break;
                    case 2:
                        TaLogic_CommandEncUnit(pCtl, 5, 0, (u8)TaLogic_Mai_GetWarnHideLvl(controllingSide));
                        break;
                    case 1:
                    case 3:
                        TaLogic013_CommandSpellUnit(pCtl, pTask);
                        break;
                    default:
                        *(s16 *)&pCtl->mission = 0x5FF;
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
s32 TaLogic_Mai_GetNextActiveUnit(u16 *pCtl, s32 nSide, s32 pInput, void *nMode) {
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
    TaLogic_Mai_CommandUnit(pCtl + idx * 8, pInput);
    if (((pCtl[idx * 8 + 2] >> 8) & 0xFF) == 10) {
        if (SzDuel_InqHandPhase(nSide) == 1 && TaLogic_Mai_GetMinimumTask_Summon(pos, nSide, nMode) >= 0) {
            return pos | 0x10000;
        }
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_GetUnitStatus(nSide, 0, 0) == 0) {
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_InqHandPhase(nSide) == 1 && TaLogic_Mai_GetMinimumTask_Summon(pos, nSide, nMode) >= 0) {
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
    u8 pad3;
} Slot_001474F0;

typedef struct {
    u16 low;
    u16 high;
} DataHalves_001474F0;

typedef struct {
    u16 unitId; /* (side << 8) | unit */
    u8 pad2[2];
    u16 state;
    u8 pad6[2];
    union {
        u32 word;
        DataHalves_001474F0 halves;
    } data;
} Entry_001474F0;

/* Orders a fighting unit (task `pTask`): straight at its goal when the path is open, else the nearest enemy it can
   beat. */
void TaLogic013_CommandBtlUnit(void *pTask) {
    extern s32 TaLogic_IsRootOpen();
    extern void TaLogic_InitIgnoreLst();
    extern s32 TaLogic013_GetNearUnit();
    Entry_001474F0 *entry = pTask;
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
        if (TaLogic_IsRootOpen(entry->unitId >> 8, entry->unitId & 0xFF, pos & 0xFF, pos >> 8,
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
                                  Ta_GetCurrentSide(entry->unitId >> 8, entry->unitId & 0xFF) == 0 ? 1 : 0,
                                  (u8)i, TaLogic_Mai_GetWarnHideLvl(side), list, 0,
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

/* TaLogic_GetNearUnit with this duelist's view and strength settings. */
s32 TaLogic013_GetNearUnit(s32 pTask, s32 pTree, s32 pVarInfo, s32 nX, s32 nZ, s32 eSide, s32 bDist, s32 WarnLvl, s32 nUnitLst, u16 wUnitNum, s32 wSize, s32 wNodeCount, u8 bChase, s32 wIgnoreLst) {
    return TaLogic_GetNearUnit(pTask, pTree, pVarInfo, nX, nZ, eSide, bDist, WarnLvl, nUnitLst, wUnitNum, wSize, wNodeCount, bChase, 0, 0x960, wIgnoreLst);
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
    u16 unitId; /* (side << 8) | unit */
    u8 pad2[2];
    u16 state;
    u8 pad6[2];
    union {
        u32 word;
        DataHalves_00147830 halves;
    } data;
} Entry_00147830;

/* The other side. */
static inline s32 other_00147830(s32 side) {
    return side == 0 ? 1 : 0;
}
#pragma opt_dead_assignments off

/* Orders a unit (task `pTask`) to push into the opponent's side of the board. */
void TaLogic013_CommandInvadeUnit(void *pTask) {
    extern s32 TaLogic_IsRootOpen();
    extern void TaLogic_InitIgnoreLst();
    extern s32 TaLogic_GetNearUnit();
    Entry_00147830 *entry = pTask;
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

    if (SzDuel_GetUnit(entry->unitId >> 8, entry->unitId & 0xFF) != 0) {
        side = Ta_GetCurrentSide(entry->unitId >> 8, entry->unitId & 0xFF);
        other = other_00147830(side) << 8;
        pos = SzDuel_GetUnitLoc(entry->unitId >> 8, entry->unitId & 0xFF);
        otherPos = SzDuel_GetUnitLoc(other >> 8, other & 0xFF);
        player = SzDuel_GetUnit(entry->unitId >> 8, entry->unitId & 0xFF);
        TaLogic_InitIgnoreLst(work);
        for (i = 0; i < 22; i++) {
            list[i].card = 0xFFFF;
            list[i].flag = 0xFF;
        }
        if (TaLogic_IsRootOpen(entry->unitId >> 8, entry->unitId & 0xFF, pos & 0xFF, pos >> 8,
                          other >> 8, other & 0xFF, otherPos & 0xFF, otherPos >> 8, 2) > 0) {
            entry->state = 0x2FF;
            entry->data.word = (other << 16) | entry->data.halves.low;
            return;
        }
        countB = 0;
        countA = 0;
        i = 1;
        while (1) {
            selection = TaLogic_Mai_GetWarnHideLvl(side);
            switch (TaLogic_GetNearUnit(entry, 0, player, pos & 0xFF, pos >> 8,
                                  other_00147830(Ta_GetCurrentSide(entry->unitId >> 8, entry->unitId & 0xFF)),
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
#pragma opt_dead_assignments reset

/* Orders an effect monster (task `pTask`): where its effect does most. */
void TaLogic013_CommandEfcMonster(void *pTask) {
    extern s32 SzDuel_GetUnitCardNo();
    Action_00147AC0 *action = pTask;
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

/* Orders a face-down magic card (task `pTask`): whether and where to open it. */
void TaLogic013_CommandSpellUnit(void *pTask, int nMode)
{
    struct DotrSlotOrder * order = pTask;
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
        if ((unsigned char)nMode == 1) {
            r = TaLogic_GetLandChange(SzDuel_GetUnit(order->position >> 8, order->position & 0xff), here & 0xff, here >> 8, 2, 6, 2);
            if (r >= 0) {
                order->unknown_04 = 0x6ff;
                order->flags.word = (r << 16) | order->flags.half;
            }
        }
        break;
    case 4:
        if ((unsigned char)nMode == 1) {
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

/* The square to invade toward from (nX, nZ): a side square while still near home, else the enemy leader's square. */
s32 TaLogic013_GetInvadePoint(s32 nSide, s32 nX, s32 nZ) {
    if (nZ < 3) {
        return (nX >= 3) ? 0x306 : 0x300;
    }
    return SzDuel_GetUnitLoc((nSide == 0) ? 1 : 0, 0);
}

/* Whether (nX, nZ) is one of this duelist's five defence points. */
s32 TaLogic013_IsDefensePoint(s32 nX, s32 nZ) {
    s32 var_s0;

    var_s0 = 0;
loop_1:
    if (((nZ << 8) | nX) == TaLogic013_GetDefensePoint(var_s0)) {
        return 1;
    }
    var_s0 += 1;
    if (var_s0 >= 5) {
        return 0;
    }
    goto loop_1;
}

/* Defence point `nNo` (0..4) of this duelist, or -1. */
s32 TaLogic013_GetDefensePoint(s32 nNo) {
    switch (nNo) {
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

/* The free line of the board this duelist's units fill next. */
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

/* The summon task for side `nSide`: which hand cards to play and where, into `pInput`; -1 when it plays none. */
s32 TaLogic_Mai_GetMinimumTask_Summon(s32 wUnit, s32 nSide, void *pInput) {
    extern s32 TaLogic_GetUnitNum(s32, s32);
    Act_00148020 *act = pInput;
    Card_00148020 buf;
    s32 res;
    s32 type;
    s32 card;
    s32 r;

    act->card = wUnit;
    if (SzDuel_InqHandPhase(nSide) == 0) {
        return -1;
    }
    if (TaLogic_GetUnitNum(nSide, 0) == 5 && TaLogic_GetUnitNum(nSide, 1) == 5) {
        return -1;
    }
    type = TaLogic013_IsHandPlay(nSide, &buf);
    if (type < 0) {
        return -1;
    }
    act->f2 = 10;
    act->fC = 0;
    card = SzDuel_GetUnitLoc(wUnit >> 8, wUnit & 0xFF);
    if (type == 0) {
        if (TaLogic013_SetComboQue(nSide, pInput, &buf) >= 0) {
            res = TaLogic_GetNearCard2(&buf, card & 0xFF, card >> 8, nSide == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, TaLogic_Mai_GetWarnHideLvl(nSide));
            if (res < 0) {
                if (SzDuel_GetUnitMonsterCount(nSide) < 4) {
                    r = TaLogic013_GetSummonPiece(nSide, type, &buf, res);
                    if (r < 0) {
                        return -1;
                    }
                    act->f4 = r;
                    return 1;
                }
            } else {
                r = TaLogic013_GetSummonPiece(nSide, type, &buf, res);
                if (r < 0) {
                    return -1;
                }
                act->f4 = r;
                return 1;
            }
        }
    } else {
        res = TaLogic_GetNearCard2(&buf, card & 0xFF, card >> 8, nSide == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, TaLogic_Mai_GetWarnHideLvl(nSide));
    }
    if (type == 2) {
        TaLogic013_SetSpecialComboQue(nSide, pInput, &buf);
        r = TaLogic013_GetSummonPiece(nSide, type, &buf, res);
        if (r < 0) {
            return -1;
        }
        act->f4 = r;
        return 1;
    } else if (type == 3) {
        TaLogic013_GetSpecialComboPlay(nSide, pInput, &buf);
        r = TaLogic013_GetSummonPiece(nSide, type, &buf, res);
        if (r < 0) {
            return -1;
        }
        act->f4 = r;
        return 1;
    } else {
        if (TaLogic013_GetSpellPlay(nSide, pInput, &buf, buf.id) < 0) {
            return -1;
        }
        r = TaLogic013_GetSummonPiece(nSide, type, &buf, res);
        if (r < 0) {
            return -1;
        }
        act->f4 = r;
        return 1;
    }
}

/* Whether side `nSide` should play from its hand this turn (and what, into `pInput`). */
s32 TaLogic013_IsHandPlay(s32 nSide, void *pInput) {
    extern s32 TaLogic_GetUnitNum();
    extern s32 SzDuel_GetUnitCurseRest();
    s32 entries[8];
    u8 scratch[32];
    u8 kind0;
    u8 kind1;

    kind0 = (u8)TaLogic_GetUnitNum(nSide, 0);
    kind1 = (u8)TaLogic_GetUnitNum(nSide, 1);
    if (pInput == NULL) {
        return -1;
    }
    TaHand_GetNextHand(nSide, entries);
    if (kind0 == 5) {
        if (TaLogic013_GetSpellPlay(nSide, scratch, pInput, 999) >= 0) {
            return 1;
        }
        return -1;
    }
    if (kind1 == 5) {
        s32 i = 0;
        s32 *entry;

        if (i < TaHand_GetNextHandNum(nSide)) {
            entry = entries;
            do {
                if ((TaHand_GetCardKind(*entry) >> 5) == 0 &&
                    TaHand_CanAffordSummonCost(nSide, *entry) == 1) {
                    SzDuel_InitCardInfo(pInput, entries[i]);
                    return 0;
                }
                entry++;
                i++;
            } while (i < TaHand_GetNextHandNum(nSide));
        }
        return -1;
    }
    if (TaLogic013_GetSpecCardPlay(nSide, scratch, pInput, 0x34B) >= 0) {
        if (TaLogic013_IsDoCerem(nSide, 0x34B) == 1) {
            return 2;
        }
    }
    if (TaLogic013_GetSpecialComboPlay(nSide, scratch, pInput) == 1) {
        return 3;
    }
    if (Ta_GetUnitNumFrom22bitFlagList(SearchUnitByRange(0, 0, nSide, 1, 0x1E001C, 14)) > 0) {
        if (TaLogic013_GetSpecCardPlay(nSide, scratch, pInput, 30) >= 0) {
            return 2;
        }
    }
    if (TaLogic013_IsUseRevive(nSide) >= 0) {
        if (TaLogic013_GetSpecCardPlay(nSide, scratch, pInput, 0x2AD) >= 0) {
            return 2;
        }
    }
    {
        s32 i = 0;
        do {
            if (SzDuel_GetUnitCurseRest(nSide, i) != 0 &&
                TaLogic013_GetSpecCardPlay(nSide, scratch, pInput, 0x31C) >= 0) {
                return 2;
            }
            i++;
        } while (i < 11);
    }
    {
        s32 *entry;
        s32 i = 0;

        if (i < TaHand_GetNextHandNum(nSide)) {
            entry = entries;
            do {
                if ((TaHand_GetCardKind(*entry) >> 5) == 0 &&
                    TaHand_CanAffordSummonCost(nSide, *entry) == 1 && *entry != 0x110) {
                    SzDuel_InitCardInfo(pInput, entries[i]);
                    return 0;
                }
                entry++;
                i++;
            } while (i < TaHand_GetNextHandNum(nSide));
        }
    }
    {
        s32 result = TaLogic013_GetSpellPlay(nSide, scratch, pInput, 999);
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

/* Whether side `nSide` can play this duelist's special combination now. */
s32 TaLogic013_GetSpecialComboPlay(s32 nSide, void *bCombo, void *pCardInfo) {
    Obj2_00148630 *o2 = pCardInfo;
    Obj1_00148630 *o1 = bCombo;
    s32 list[8];
    s32 i;
    s32 found;
    u8 k;

    TaHand_GetNextHand(nSide, list);
    for (i = 0, found = 0; i < TaHand_GetNextHandNum(nSide); i++) {
        if (list[i] == 0x31D) {
            found = 1;
            o1->slot[0] = i;
        }
    }
    if (found == 0) {
        return -1;
    }
    for (i = 0, found = 0; i < TaHand_GetNextHandNum(nSide); i++) {
        if (list[i] == 0x110 && TaHand_CanAffordSummonCost(nSide, list[i]) == 1) {
            o1->slot[1] = i;
            found = 1;
        }
    }
    if (found == 0) {
        return -1;
    }
    k = 2;
    SzDuel_InitCardInfo(o2, 0x111);
    for (i = 0; i < TaHand_GetNextHandNum(nSide); i++) {
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

/* Whether side `nSide` holds card `nCardNo` and can summon it (its slot into `bCombo`, the card into `pCardInfo`);
   returns its kind group or -1. */
s32 TaLogic013_GetSpecCardPlay(s32 nSide, void *bCombo, void *pCardInfo, s32 nCardNo) {
    s32 entries[8];
    s32 index;
    s32 *entry;

    TaHand_GetNextHand(nSide, entries);
    index = 0;
    if (index < TaHand_GetNextHandNum(nSide)) {
        entry = entries;
        do {
            if (((nCardNo & 0xFFFF) == *entry) && (TaHand_CanAffordSummonCost(nSide, *entry) == 1)) {
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
s32 TaLogic013_GetSpellPlay(s32 nSide, u8 *bCombo, void *pCardInfo, s32 nMode) {
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

/* Fills hand combination `bCombo` for side `nSide`: the best fusion or equip chain, its card into `pCardInfo`. */
s32 TaLogic013_SetComboQue(s32 nSide, u8 *bCombo, void *pCardInfo) {
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
                            TaLogic_Mai_ConvEmptyCombo(nSide, *node, entries);
                            TaLogic_CopyArray((u8 *)*node + 2, bCombo + 6);
                            SzDuel_InitCardInfo(pCardInfo, **node);
                            ((Sprite_00148B60 *)pCardInfo)->x = (value >> 16) - (((Sprite_00148B60 *)pCardInfo)->info->x & 0x1FFF);
                            ((Sprite_00148B60 *)pCardInfo)->y = (value & 0xFFFF) - (((Sprite_00148B60 *)pCardInfo)->info->y & 0x1FFF);
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
} Info_00148D40;

/* Fills an empty combination: the hand card side `nSide` can summon with the best attack plus defence. */
void TaLogic_Mai_ConvEmptyCombo(s32 nSide, void *pCardInfo, s32 *pResult) {
    Info_00148D40 *info = pCardInfo;
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
                if (card != 0x3E7 && TaLogic013_IsRefuseEmptyCombo(card) == 0 && level >= TaHand_GetCardSummonCost2(card, nSide)) {
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
s32 TaLogic013_IsRefuseEmptyCombo(s32 nCardNo) {
    if ((TaHand_GetCardKind(nCardNo) >> 5) != 0) {
        return 1;
    } else if (TaHand_IsCardEffect(nCardNo) == 1) {
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

/* Fills hand combination `bCombo` for side `nSide` with this duelist's special combination, its card into
   `pCardInfo`. */
s32 TaLogic013_SetSpecialComboQue(s32 nSide, void *bCombo, void *pCardInfo) {
    Obj1_00148F80 *o1 = bCombo;
    Obj2_00148F80 *o2 = pCardInfo;
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

/* The first free defence point, or -1. */
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

/* The square side `nSide` summons a card of kind `sKind` to. */
s32 TaLogic013_GetSummonPiece(s32 nSide, u8 sKind, void *pInput, s32 nMode) {
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

    if (pInput == NULL) {
        return -1;
    }
    p = path;
    i = 0;
    do {
        p->low = p->high = 15;
        p++;
        i++;
    } while (i < 12);

    kind = (type = (u8)(*((u8 *)pInput + 0x3E) >> 5));
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
        if (nMode >= 0) {
            s32 result;
            s32 dest_y;
            s32 dest_x;
            min = 255;
            best = 65535;
            result = SzDuel_GetUnitLoc(nMode >> 8, nMode & 255);
            index = 0;
            dest_y = result >> 8;
            dest_x = result & 255;
            do {
                first_coord = Ta_GetSommonPiecePreference(nSide, index);
                if (first_coord >= 0) {
                    first_x = first_coord & 255;
                    first_y = first_coord >> 8;
                    if (SzDuel_GetField(first_x, first_y) != 8 &&
                        (SzDuel_GetField(first_x, first_y) != 9 || Ta_IsVirus_Chk3(pInput, first_x, first_y) != 1) &&
                        SzDuel_GetMapUnit(first_x, first_y) == 0) {
                        result = TaLogic_IsUnitWin4(pInput, nMode, TaLogic_Mai_GetWarnHideLvl(nSide), dest_x, dest_y, 0) > 0
                            ? TaLogic_GetInvadeRoot2(pInput, path, first_x, first_y, dest_x, dest_y, nMode, 0, 3, (u16)TaLogic_Mai_GetWarnHideLvl(nSide))
                            : TaLogic_GetRoot2(pInput, path, first_x, first_y, dest_x, dest_y, nMode, 3);
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
                nMode = Ta_GetSommonPiecePreference(nSide, index);
                if (nMode >= 0) {
                    x = nMode & 255;
                    y = nMode >> 8;
                    if (SzDuel_GetField(x, y) != 8 &&
                        (SzDuel_GetField(x, y) != 9 || Ta_IsVirus_Chk3(pInput, x, y) != 1) &&
                        SzDuel_GetMapUnitID(x, y) < 0) {
                        target = find_target_001491B0();
                        target_x = target & 255;
                        target_y = target >> 8;
                        result = SzDuel_GetMapUnitID(target_x, target_y);
                        if (result < 0) {
                            result = 65535;
                        }
                        result = TaLogic_GetRoot2(pInput, path, x, y, target_x, target_y, result, 7);
                        if (result < lowest && result >= 0) {
                            fallback = nMode;
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
            coord = Ta_GetSommonPiecePreference(nSide, index);
            if (coord >= 0) {
                x = coord & 255;
                y = coord >> 8;
                if (SzDuel_GetField(x, y) != 8 &&
                    (SzDuel_GetField(x, y) != 9 || Ta_IsVirus_Chk3(pInput, x, y) != 1) &&
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

/* The task of a unit running from danger (task `pTask`): the safest square in reach, into `pInput` (`fFirst` = 1
   for the unit's first-choice task). */
s32 TaLogic_Mai_GetMinimumTask_RunMission(UnitTask *pTask, s32 nSide, void *pInput, u8 fFirst) {
    Output_00149690 *output = pInput;
    s32 target;
    u8 endX;
    u8 extra;
    Nibbles_00149690 nibbles[12];
    s32 bestScore;
    s32 best;
    s32 i;
    Nibbles_00149690 *p;
    extern s32 TaLogic_Mai_IsOpenUnit();
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

        initialScore = TaLogic_Mai_GetWarnHideLvl(nSide);
        centerX = target & 0xFF;
        centerY = target >> 8;
        if (TaLogic_GetUnitWarning(centerX, centerY, pTask->ownerId, 3, initialScore, 0) == 0) {
            output->position = pTask->ownerId;
            output->action = 6;
            output->destination = target;
            output->result = TaLogic_IsDefStyleUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, output->destination, 1, 0);
            output->special = TaLogic_Mai_IsOpenUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, pTask);
            TaLogic_InitRogicControl(pTask, fFirst);
            return 0;
        }
        if ((range = GetMoveRange(SzDuel_GetUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF), centerX, centerY)) == 0) {
            output->position = pTask->ownerId;
            output->action = 6;
            output->destination = target;
            output->result = TaLogic_IsDefStyleUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, output->destination, 1, 0);
            output->special = TaLogic_Mai_IsOpenUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, pTask);
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
                        candidateScore = TaLogic_GetUnitWarning(x, y, pTask->ownerId, 3, (u16)TaLogic_Mai_GetWarnHideLvl(nSide), 0);
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
            output->special = TaLogic_Mai_IsOpenUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, pTask);
        } else {
            output->position = pTask->ownerId;
            output->action = 6;
            output->destination = target;
            output->result = TaLogic_IsDefStyleUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, output->destination, 1, 0);
            output->special = TaLogic_Mai_IsOpenUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, pTask);
        }
        TaLogic_InitRogicControl(pTask, fFirst);
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

/* The task's target square: the second half-word when the second argument is 1, else the first. */
static inline u32 target_00149C60(void *src, u8 side) {
    Input_00149C60 *input = src;
    if (side == 1) {
        return (u16)(input->targets >> 16);
    }
    return (u16)input->targets;
}

#define MIN_00149C60(a, b) ((a) < (b) ? (a) : (b))
#define MAX_00149C60(a, b) ((a) > (b) ? (a) : (b))

/* The task of a unit attacking (task `pTask`): its path to the goal, into `pInput`; -1 when it has none (`fFirst`
   = 1 for the unit's first-choice task). */
s32 TaLogic_Mai_GetMinimumTask_AtkMission(void *pTask, s32 nSide, void *pInput, u8 fFirst) {
    extern s32 TaLogic_Mai_IsOpenUnit();
    extern s32 GetMoveRange();
    extern s32 TaLogic_GetUnitWarning();
    extern void TaLogic_GetInvadeRoot();
    Input_00149C60 *input = pTask;
    Output_00149C60 *output = pInput;
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
    s32 unitInfo;
    u32 targetLow;
    u32 targetHigh;
    Coord_00149C60 candidates[12];

    targetLow = target_00149C60(pTask, fFirst);
    targetHigh = target_00149C60(pTask, fFirst);
    if (SzDuel_GetUnit(targetHigh >> 8, targetLow & 0xFF) == 0) {
        TaLogic_InitRogicControl(pTask, 1);
        return -1;
    }
    fallback = TaLogic_Mai_IsOpenUnit((s32)input->position >> 8, input->position & 0xFF, pTask);
    origin = SzDuel_GetUnitLoc((s32)input->position >> 8, input->position & 0xFF);
    targetLow = target_00149C60(pTask, fFirst);
    targetHigh = target_00149C60(pTask, fFirst);
    targetPosition = SzDuel_GetUnitLoc(targetHigh >> 8, targetLow & 0xFF);
    i = 0;
    do {
        candidates[i].x = candidates[i].y = 15;
        i++;
    } while (i < 12);
    unitInfo = SzDuel_GetUnit((s32)input->position >> 8, input->position & 0xFF);
    originX = origin & 0xFF;
    originY = origin >> 8;
    if (GetMoveRange(unitInfo, originX, originY) == 0) {
        s32 cost;
        output->position = input->position;
        output->action = 6;
        output->destination = origin;
        cost = TaLogic_GetUnitWarning(originX, originY, nSide, 3, 1, (u8)TaLogic_Mai_GetWarnHideLvl(nSide));
        if (cost >= SzDuel_GetUnitAP((s32)input->position >> 8, input->position & 0xFF, 0)) {
            output->result = TaLogic_IsDefStyleUnit((s32)input->position >> 8,
                                         input->position & 0xFF, output->destination, 1, 0);
        } else {
            output->result = TaLogic_IsDefStyleUnit((s32)input->position >> 8,
                                         input->position & 0xFF, output->destination, 0, 0);
        }
        TaLogic_InitRogicControl(pTask, fFirst);
    } else {
        s32 position = input->position;
        u16 kind = TaLogic_Mai_GetWarnHideLvl(nSide);
        s32 positionY = position >> 8;
        s32 positionX = position & 0xFF;

        TaLogic_GetInvadeRoot(positionY, positionX, candidates,
                     originX, originY, targetX = targetPosition & 0xFF, targetPosition >>= 8,
                     target_00149C60(pTask, fFirst), (s64)0, (s64)30, (s64)kind);
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
                    cost = TaLogic_GetUnitWarning(candidate->x, candidate->y, nSide,
                                         2, 1, (u8)TaLogic_Mai_GetWarnHideLvl(nSide));
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
            TaLogic_InitRogicControl(pTask, fFirst);
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
            TaLogic_InitRogicControl(pTask, fFirst);
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

/* The task's target square: the second half-word when the second argument is 1, else the first. */
static inline u32 target_0014A240(void *unit, s32 side) {
    return side == 1 ? (u32)(u16)(((Unit_0014A240 *)unit)->target.packed >> 16) : (u32)((Unit_0014A240 *)unit)->target.low;
}

/* The smaller of the two values. */
static inline u32 minY_0014A240(void *unit, s32 side, u8 coord) {
    return coord < (target_0014A240(unit, side) >> 8) ? coord : (target_0014A240(unit, side) >> 8);
}

/* The larger of the two values. */
static inline u32 maxY_0014A240(void *unit, s32 side, u8 coord) {
    return (target_0014A240(unit, side) >> 8) < coord ? coord : (target_0014A240(unit, side) >> 8);
}

/* The smaller of the two values. */
static inline u32 minX_0014A240(void *unit, s32 side, u8 coord) {
    return coord < (target_0014A240(unit, side) & 0xFF) ? coord : (target_0014A240(unit, side) & 0xFF);
}

/* The larger of the two values. */
static inline u32 maxX_0014A240(void *unit, s32 side, u8 coord) {
    return (target_0014A240(unit, side) & 0xFF) < coord ? coord : (target_0014A240(unit, side) & 0xFF);
}

/* The task of a unit moving to its goal (task `pTask`), into `pInput` (`fFirst` = 1 for the unit's first-choice
   task). */
s32 TaLogic_Mai_GetMinimumTask_MoveMission(void *pTask, s32 nSide, void *pInput, u8 fFirst, u8 nKind) {
    extern s32 TaLogic_Mai_IsOpenUnit();
    extern s32 TaLogic_GetUnitWarning();
    extern void TaLogic_GetRoot();
    extern s32 TaLogic_IsDefStyleUnit(s32, s32, s32, u8, s32);
    Coord_0014A240 coords[12];
    s32 initial;
    s32 cell;
    s32 count;

    initial = SzDuel_GetUnitLoc(((Unit_0014A240 *)pTask)->position >> 8, ((Unit_0014A240 *)pTask)->position & 0xFF);
    {
    s32 bestScore;
    s32 best;
    s32 side = fFirst;
    Coord_0014A240 *candidate;
    s32 index;
    if (target_0014A240(pTask, side) == 0xFFFF) {
        if (initial == target_0014A240(pTask, side)) {
            ((Output_0014A240 *)pInput)->position = ((Unit_0014A240 *)pTask)->position;
            ((Output_0014A240 *)pInput)->kind = 6;
            ((Output_0014A240 *)pInput)->target = initial;
            ((Output_0014A240 *)pInput)->flag = TaLogic_IsDefStyleUnit(((Unit_0014A240 *)pTask)->position >> 8, ((Unit_0014A240 *)pTask)->position & 0xFF, ((Output_0014A240 *)pInput)->target, nKind, 0);
            ((Output_0014A240 *)pInput)->value = TaLogic_Mai_IsOpenUnit(((Unit_0014A240 *)pTask)->position >> 8, ((Unit_0014A240 *)pTask)->position & 0xFF, pTask);
            TaLogic_InitRogicControl(pTask, fFirst);
            return 0;
        }
    }

    if (SzDuel_GetUnitStatus(((Unit_0014A240 *)pTask)->position >> 8,
                      ((Unit_0014A240 *)pTask)->position & 0xFF, 4) != 0) {
        if ((SzDuel_GetUnitKind(((Unit_0014A240 *)pTask)->position >> 8,
                          ((Unit_0014A240 *)pTask)->position & 0xFF) >> 5) == 1 ||
            (SzDuel_GetUnitKind(((Unit_0014A240 *)pTask)->position >> 8,
                          ((Unit_0014A240 *)pTask)->position & 0xFF) >> 5) == 5) {
            SzDuel_SetUnitStatus(((Unit_0014A240 *)pTask)->position >> 8,
                          ((Unit_0014A240 *)pTask)->position & 0xFF, 0, 1);
            ((Output_0014A240 *)pInput)->position = ((Unit_0014A240 *)pTask)->position;
            ((Output_0014A240 *)pInput)->kind = 0xE;
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

    cell = SzDuel_GetMapUnitID(target_0014A240(pTask, side) & 0xFF, ((u32)target_0014A240(pTask, side)) >> 8);
    if (cell < 0) {
        cell = 0xFFFF;
    }
    TaLogic_GetRoot(((Unit_0014A240 *)pTask)->position >> 8, ((Unit_0014A240 *)pTask)->position & 0xFF,
                 coords, initial & 0xFF, initial >> 8, target_0014A240(pTask, side) & 0xFF,
                 ((u32)target_0014A240(pTask, side)) >> 8, (u16)cell, 7);
    count = TaLogic_GetMinGoalCount((u8 *)coords);
    {
        if (count > 0) {
        best = 0xFF;
        bestScore = 0xFFFF;
        for (index = 0; index < count; index++) {
                if (SzDuel_GetMapUnit(candidate->x, candidate->y) == 0) {
                    s32 score = TaLogic_GetUnitWarning(candidate->x, candidate->y, nSide, 2, 1, (u8)TaLogic_Mai_GetWarnHideLvl(nSide));
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
                        bestMinY = minY_0014A240(pTask, side, bestY);
                        bestMaxY = maxY_0014A240(pTask, side, bestY);
                        bestX = (&coords[best])->x;
                        bestMinX = minX_0014A240(pTask, side, bestX);
                        bestMaxX = maxX_0014A240(pTask, side, bestX);
                        currentY = (u8)candidate->y;
                        currentMinY = minY_0014A240(pTask, side, currentY);
                        currentMaxY = maxY_0014A240(pTask, side, currentY);
                        currentX = candidate->x;
                        currentMinX = minX_0014A240(pTask, side, currentX);
                        currentMaxX = maxX_0014A240(pTask, side, currentX);
                        if ((currentMaxX - currentMinX) + (currentMaxY - currentMinY) < (bestMaxX - bestMinX) + (bestMaxY - bestMinY)) {
                            bestScore = score;
                            best = index;
                        }
                    }
                }
            candidate++;
        }
    } else {
        ((Output_0014A240 *)pInput)->position = ((Unit_0014A240 *)pTask)->position;
            ((Output_0014A240 *)pInput)->kind = 6;
            ((Output_0014A240 *)pInput)->target = initial;
            ((Output_0014A240 *)pInput)->flag = TaLogic_IsDefStyleUnit(((Unit_0014A240 *)pTask)->position >> 8, ((Unit_0014A240 *)pTask)->position & 0xFF, ((Output_0014A240 *)pInput)->target, nKind, 0);
            ((Output_0014A240 *)pInput)->value = TaLogic_Mai_IsOpenUnit(((Unit_0014A240 *)pTask)->position >> 8, ((Unit_0014A240 *)pTask)->position & 0xFF, pTask);
        TaLogic_InitRogicControl(pTask, fFirst);
        return 0;
    }

        if (best != 0xFF) {
            ((Output_0014A240 *)pInput)->position = ((Unit_0014A240 *)pTask)->position;
            ((Output_0014A240 *)pInput)->kind = 6;
            ((Output_0014A240 *)pInput)->target = (coords[best].y << 8) | coords[best].x;
            ((Output_0014A240 *)pInput)->flag = TaLogic_IsDefStyleUnit(((Unit_0014A240 *)pTask)->position >> 8, ((Unit_0014A240 *)pTask)->position & 0xFF, ((Output_0014A240 *)pInput)->target, nKind, 0);
            ((Output_0014A240 *)pInput)->value = TaLogic_Mai_IsOpenUnit(((Unit_0014A240 *)pTask)->position >> 8, ((Unit_0014A240 *)pTask)->position & 0xFF, pTask);
        } else {
            ((Output_0014A240 *)pInput)->position = ((Unit_0014A240 *)pTask)->position;
            ((Output_0014A240 *)pInput)->kind = 6;
            ((Output_0014A240 *)pInput)->target = initial;
            ((Output_0014A240 *)pInput)->flag = TaLogic_IsDefStyleUnit(((Unit_0014A240 *)pTask)->position >> 8, ((Unit_0014A240 *)pTask)->position & 0xFF, ((Output_0014A240 *)pInput)->target, nKind, 0);
            ((Output_0014A240 *)pInput)->value = TaLogic_Mai_IsOpenUnit(((Unit_0014A240 *)pTask)->position >> 8, ((Unit_0014A240 *)pTask)->position & 0xFF, pTask);
        }
        TaLogic_InitRogicControl(pTask, fFirst);
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

/* The task of reviving a monster from the graveyard (task `pTask`), into `pInput` (`fFirst` = 1 for the unit's
   first-choice task). */
s32 TaLogic_Mai_GetMinimumTask_ReviveMission(void *pTask, s32 nSide, void *pInput, u8 fFirst) {
    Unit_0014AAB0 *unit = pTask;
    s32 pos;
    s32 card;
    s32 col;
    u16 row;
    Out_0014AAB0 *out = pInput;
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
    card = TaLogic013_IsUseRevive(nSide);
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
        TaLogic_InitRogicControl(unit, fFirst);
        return 0;
    }
    if (SzDuel_GetUnitStatus(unit->pos >> 8, unit->pos & 0xFF, 4) != 0) {
        SzDuel_SetUnitStatus(unit->pos >> 8, unit->pos & 0xFF, 0, 1);
        out->pos = unit->pos;
        out->kind = 14;
        return 0;
    }
    return TaLogic_Mai_GetMinimumTask_RunMission(unit, nSide, out, fFirst);
}

/* Whether this duelist plays in its attacking mode this turn. */
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

/* Whether this duelist opens (turns face up) unit (nSide, nID) now: 0 no, 1 or 2 by its kind. */
s32 TaLogic_Mai_IsOpenUnit(s32 nSide, s32 nID) {
    s32 kind;
    s32 pos;
    s32 slot;
    u32 *card;
    s32 found;

    kind = SzDuel_GetUnitCardNo();
    pos = SzDuel_GetUnitLoc(nSide, nID);
    slot = Ta_IsUnitControl(nSide, nID);
    card = SzDuel_GetUnitEffect(nSide, nID, 0);
    if (SzDuel_GetUnitStatus(nSide, nID, 4) != 0) {
        return 0;
    }
    switch (SzDuel_GetUnitKind(nSide, nID) >> 5) {
    case 0:
        switch (kind) {
        case 0x123:
            if (Ta_GetUnitNumFrom22bitFlagList(SearchUnitByRange(0, 0, nSide, 1, 6, 0xE)) >= 3) {
                return 1;
            }
            break;
        case 0x110:
        case 0x111:
            if (Ta_GetUnitNumFrom22bitFlagList(SearchUnitByRange(0, 0, nSide, 1, 0x1E001C, 0xE)) > 0) {
                return 1;
            }
            break;
        }
        return 2;
    case 5:
        if (TaLogic_GetActionReaction(nSide, nID, 0, 0, 6, 0) == 5) {
            return 2;
        }
        if (TaLogic013_IsDoCerem(Ta_IsUnitControl(nSide, nID), kind) == 1 &&
            SzDuel_GetField(pos & 0xFF, pos >> 8) != 9) {
            return 1;
        }
        break;
    case 1:
        if (TaLogic_GetActionReaction(nSide, nID, 0, 0, 6, 0) == 5) {
            return 2;
        }
        if (card == NULL) {
            return 2;
        }
        switch (*card >> 8) {
        case 0xD:
            return 1;
        case 2:
            found = TaLogic_GetLandChange(SzDuel_GetUnit(nSide, nID), pos & 0xFF, pos >> 8, 2, 6, 2);
            if (found >= 0 && found == pos) {
                return 1;
            }
            break;
        case 4:
            if (TaLogic013_IsUseHarpySweaper(nSide, pos & 0xFF, pos >> 8) == 1) {
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

/* Whether `status` is 1. */
static inline s32 check_0014B140(s32 status) {
    if (status != 1) {
        return 0;
    }
    return 1;
}

/* Whether unit (nSide, nID) may open while moving from (nX, nZ) to the square next to it, (gX, gZ). */
s32 TaLogic013_IsOpenMoveUnit(s32 nSide, s32 nID, s32 nX, s32 nZ, s32 gX, s32 gZ) {
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
        return check_0014B140(CheckLandAgreement2(SzDuel_GetField(nX, nZ), nSide, nID));
    }
    return 0;
}

/* Whether side `nSide` can play ritual card `nCardNo` now (it has the units to give up). */
s32 TaLogic013_IsDoCerem(s32 nSide, s32 nCardNo) {
    s32 sp50[4];
    s32 i;
    s32 mask;
    s32 low;
    s32 high;
    s32 value;
    s32 result;

    Ta_GetCeremSacrifice(sp50, *(s32 *)((u8 *)TaHand_GetCardEffect(nCardNo, 0) + 4));
    if ((mask = Ta_GetSacrificeUnit(sp50, nSide)) < 0) {
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

/* How careful this duelist is about hidden cards (by its life points and monster count). */
s32 TaLogic_Mai_GetWarnHideLvl(s32 nSide) {
    return SzDuel_GetLP(nSide) > 0x5DC
        ? (SzDuel_GetUnitMonsterCount(nSide) >= 4 ? 0x2EE : 0x5DC)
        : 0x7D0;
}

/* Whether the unit passed through in a0/a1 (side, unit; SzDuel_GetUnitCardNo is called without arguments) is an
   invader card (0x111, 0x1E or 0xB). */
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

/* Whether side `nSide` should use the sweeping card on (nX, nZ): no own magic in its range, some of the
   opponent's. */
int TaLogic013_IsUseHarpySweaper(int nSide, int nX, int nZ)
{
    if (func_0014ACA0_b(nSide, nX, nZ) == 0) {
        return 0;
    }
    if (SearchUnitByRange(nX, nZ, nSide, 1, 30, 18) != 0) {
        return 0;
    }
    return SearchUnitByRange(nX, nZ, nSide, 2, 30, 18) != 0 ? 1 : 0;
}

/* Whether side `nSide` should use a revive card now. */
s32 TaLogic013_IsUseRevive(s32 nSide) {
    extern s32 SzDuel_GetGraveCount(s32);
    s32 i;

    if (SzDuel_GetUnitMonsterCount(nSide) >= 5) {
        return -1;
    }
    if (TaLogic_GetGraveCardCount(nSide, 3, 0x111) > 0 || TaLogic_GetGraveCardCount(nSide, 3, 0x1E) > 0 ||
        TaLogic_GetGraveCardCount(nSide, 3, 0xB) > 0) {
        for (i = 0; i < SzDuel_GetGraveCount(nSide); i++) {
            if (SzDuel_InqGrave(nSide, i) == 0xB) {
                return (nSide << 16) | i;
            }
        }
        for (i = 0; i < SzDuel_GetGraveCount(nSide == 0 ? 1 : 0); i++) {
            if (SzDuel_InqGrave(nSide == 0 ? 1 : 0, i) == 0xB) {
                return ((nSide == 0 ? 1 : 0) << 16) | i;
            }
        }
        for (i = 0; i < SzDuel_GetGraveCount(nSide); i++) {
            if (SzDuel_InqGrave(nSide, i) == 0x1E) {
                return (nSide << 16) | i;
            }
        }
        for (i = 0; i < SzDuel_GetGraveCount(nSide == 0 ? 1 : 0); i++) {
            if (SzDuel_InqGrave(nSide == 0 ? 1 : 0, i) == 0x1E) {
                return ((nSide == 0 ? 1 : 0) << 16) | i;
            }
        }
        for (i = 0; i < SzDuel_GetGraveCount(nSide); i++) {
            if (SzDuel_InqGrave(nSide, i) == 0x111) {
                return (nSide << 16) | i;
            }
        }
        for (i = 0; i < SzDuel_GetGraveCount(nSide == 0 ? 1 : 0); i++) {
            if (SzDuel_InqGrave(nSide == 0 ? 1 : 0, i) == 0x111) {
                return ((nSide == 0 ? 1 : 0) << 16) | i;
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

/* Computer duelist 13's controller (duelistControllers[13]): the buttons it presses this frame. With an empty
   input queue it plans its next task and turns it into buttons, then plays the queue back one button per frame;
   after 600 frames it gives up the turn (0x20, then 0x800). */
s32 duelistController13(s32 wCursorPos, void *pCtl) {
    Req_0014B730 req;
    Work_0014B730 *w;
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
        if (TaLogic_Mai_GetMinimumTask(w, &req, wCursorPos) == 0) {
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

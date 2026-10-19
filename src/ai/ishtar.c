/* Computer AI of Ishtar (duelist 5, duelistController05). */

#include "common.h"
#pragma conditional_move off

/* This duelist's move: picks the next unit to act, gives it a task and turns that into input `pInput`; returns 1
   when it set one. */
s32 TaLogic_Ishtar_GetMinimumTask(void *pCtl, void *pInput, s32 wCursorPos) {
    UnitTask *tasks = pCtl;
    s32 side;
    s32 found;
    s32 result;
    s32 index;

    side = SzDuel_GetTurnOwner();
    found = 0;
    if ((result = TaLogic_Ishtar_GetNextActiveUnit(tasks, side, (s32)pInput)) < 0) {
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
    TaLogic_Ishtar_CommandUnit(&tasks[index]);
    switch ((tasks[index].mission >> 8) & 0xFF) {
    case TASK_RUN:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            TaLogic_Ishtar_GetMinimumTask_RunMission(&tasks[index], side, pInput, 1);
            found = 1;
        }
        break;
    case TASK_ATTACK:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            if (TaLogic_Ishtar_GetMinimumTask_AtkMission(&tasks[index], side, pInput, 1) < 0) {
                TaLogic005_InitRogicControl(&tasks[index], 1);
                return 1;
            }
            found = 1;
        }
        break;
    case TASK_SUMMON:
        if (TaLogic_Ishtar_GetMinimumTask_Summon(tasks[index].ownerId, side, (s32)pInput) < 0) {
            TaLogic005_InitRogicControl(&tasks[index], 1);
            *(u8 *)((u8 *)pInput + 2) = 0xFF;
            *(s32 *)((u8 *)pInput + 0xC) = 0;
        } else {
            TaLogic005_InitRogicControl(&tasks[index], 1);
            found = 1;
        }
        break;
    case TASK_MOVETOLOCATION:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            TaLogic_Ishtar_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 1, 0);
            found = 1;
        }
        break;
    case TASK_CONFIRMUNIT:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            TaLogic_Ishtar_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 1, 1);
            found = 1;
        }
        break;
    case TASK_ENCHANT:
        TaLogic_GetMinimumTask_EncMission(&tasks[index], side, pInput, 1, 0, TaLogic_Ishtar_GetWarnHideLvl(side), 2, 1);
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
            TaLogic_Ishtar_GetMinimumTask_RunMission(&tasks[index], side, pInput, 0);
            found = 1;
        }
        break;
    case 2:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            if (TaLogic_Ishtar_GetMinimumTask_AtkMission(&tasks[index], side, pInput, 0) < 0) {
                TaLogic_Ishtar_GetMinimumTask_RunMission(&tasks[index], side, pInput, 0);
            }
            found = 1;
        }
        break;
    case 10:
        if (TaLogic_Ishtar_GetMinimumTask_Summon(tasks[index].ownerId, side, (s32)pInput) < 0) {
            TaLogic005_InitRogicControl(&tasks[index], 0);
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
            TaLogic_Ishtar_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 0, 0);
            found = 1;
        }
        break;
    case 3:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            TaLogic_Ishtar_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 0, 1);
            found = 1;
        }
        break;
    case 9:
        TaLogic_GetMinimumTask_EncMission(&tasks[index], side, pInput, 0, 0, TaLogic_Ishtar_GetWarnHideLvl(side), 2, 1);
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

typedef struct Unit_00121CE0 {
    u16 pos;
    u16 unk2;
    u16 unk4;
    u16 unk6;
    s32 unk8;
} Unit_00121CE0;
#pragma conditional_move reset

/* Gives a unit of this duelist its order for this turn (attack, run, move, summon, guard). */
s32 TaLogic_Ishtar_CommandUnit(void *pCtl) {
    Unit_00121CE0 *unit = pCtl;
    s32 handle;

    handle = Ta_IsUnitControl(unit->pos >> 8, unit->pos & 0xFF);
    if (SzDuel_GetUnit(unit->pos >> 8, unit->pos & 0xFF) != 0 &&
        SzDuel_GetUnitStatus(unit->pos >> 8, unit->pos & 0xFF, 0) == 0 && unit->pos != 0xFFFF) {
    if ((unit->pos & 0xFF) == 0) {
        if (unit->unk8 == -1) {
            TaLogic_CommandStdLDUnit(unit, 3, 2, 0);
        }
    } else {
        switch (SzDuel_GetUnitKind(unit->pos >> 8, unit->pos & 0xFF) >> 5) {
        case 0:
            if (TaUtil_IsExMonster(unit->pos >> 8, unit->pos & 0xFF) == 1) {
                TaLogic_Ishtar_CommandEfcMonster(unit, 1);
            } else {
                TaLogic_Ishtar_CommandBtlUnit(unit, 1);
            }
            break;
        case 1:
        case 5:
            unit->unk4 = 0x5FF;
            break;
        case 2:
            TaLogic_CommandEncUnit(unit, 2, 0, (u8)TaLogic_Ishtar_GetWarnHideLvl(handle));
            break;
        case 4:
            TaLogic005_CommandTrapBUnit(unit);
            break;
        default:
            unit->unk4 = 0x5FF;
            break;
        }
    }
    return 1;
    }
    return 0;
}

/* The next unit of side `nSide` to act: first one that can attack now, then the others by task. */
s32 TaLogic_Ishtar_GetNextActiveUnit(u16 *pCtl, s32 nSide, s32 pInput) {
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
    TaLogic_Ishtar_CommandUnit(pCtl + idx * 8);
    if (((pCtl[idx * 8 + 2] >> 8) & 0xFF) == 10) {
        if (SzDuel_InqHandPhase(nSide) == 1 && TaLogic_Ishtar_GetMinimumTask_Summon(pos, nSide, pInput) >= 0) {
            return pos | 0x10000;
        }
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_GetUnitStatus(nSide, 0, 0) == 0) {
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_InqHandPhase(nSide) == 1 && TaLogic_Ishtar_GetMinimumTask_Summon(pos, nSide, pInput) >= 0) {
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
} Entry_00122270;

typedef struct {
    u16 card;
    u8 flag;
    u8 pad;
} Slot_00122270;

/* Orders a fighting unit (task `pTask`): straight at the enemy leader when `fGoalFirst` and the path is open,
   else at the nearest enemy it can beat. */
void TaLogic_Ishtar_CommandBtlUnit(void *pTask, s32 fGoalFirst) {
    extern void TaLogic_InitIgnoreLst();
    extern s32 TaLogic_IsRootOpen();
    extern s32 TaLogic005_GetNearUnit();
    extern s32 TaLogic_Ishtar_GetWarnHideLvl(s32);
    extern void TaLogic005_CommandRoutineUnit(void *);
    Entry_00122270 *entry = pTask;
    s32 side;
    s32 player;
    s32 other;
    s32 pos;
    s32 otherPos;
    s32 i;
    u8 work[0x70];
    Slot_00122270 list[22];
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
                              other >> 8, other & 0xFF, otherPos & 0xFF, otherPos >> 8, 2) > 0) {
                entry->state = 0x2FF;
                entry->data.word = (other << 16) | entry->data.halves.low;
                return;
            }
        }
        countB = 0;
        countA = 0;
        i = 1;
        while (1) {
            switch (TaLogic005_GetNearUnit(entry, 0, player, pos & 0xFF, pos >> 8,
                                  Ta_GetCurrentSide(entry->unitId >> 8, entry->unitId & 0xFF) == 0 ? 1 : 0,
                                  i & 0xFF, TaLogic_Ishtar_GetWarnHideLvl(side), list, 0, &countA, &countB, 3, work)) {
            case 3:
                entry->state = 0x2FF;
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
            if (i > 3) {
                break;
            }
        }
        TaLogic005_CommandRoutineUnit(entry);
    }
}

/* TaLogic_GetNearUnit with this duelist's view and strength settings. */
s32 TaLogic005_GetNearUnit(s32 pTask, s32 pTree, s32 pVarInfo, s32 nX, s32 nZ, s32 eSide, s32 bDist, s32 WarnLvl, s32 nUnitLst, u16 wUnitNum, s32 wSize, s32 wNodeCount, u8 bChase, s32 wIgnoreLst) {
    return TaLogic_GetNearUnit(pTask, pTree, pVarInfo, nX, nZ, eSide, bDist, WarnLvl,
                  nUnitLst, wUnitNum, wSize, wNodeCount, bChase,
                  0, 1500, wIgnoreLst);
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
} Entry_00122530;

/* Orders a unit (task `pTask`) round this duelist's patrol loop (its cycle points), or to a defence point. */
void TaLogic005_CommandRoutineUnit(void *pTask) {
    Entry_00122530 *entry = pTask;
    s32 packed;
    s32 position;
    s32 result[2];
    u16 unitId;

    unitId = entry->unitId;
    if (SzDuel_GetUnit((s32) unitId >> 8, unitId & 0xFF) != 0) {
        unitId = entry->unitId;
        Ta_GetCurrentSide((s32) unitId >> 8, unitId & 0xFF);
        unitId = entry->unitId;
        packed = SzDuel_GetUnitLoc((s32) unitId >> 8, unitId & 0xFF);
        entry->state = 0x6FF;
        unitId = entry->unitId;
        if (SzDuel_GetUnitAP((s32) unitId >> 8, unitId & 0xFF, 0) >= 0x5DC) {
            unitId = entry->unitId;
            position = TaLogic005_GetUnitOnCycleRoot((s32) unitId >> 8, unitId & 0xFF);
            if (position >= 0) {
                entry->data.word = entry->data.halves.low | (TaLogic_GetCyclePoint((position + 1) % 8) << 16);
                return;
            }
            entry->data.word = entry->data.halves.low | (TaLogic005_GetNearCyclePoint(packed & 0xFF, packed >> 8) << 16);
            return;
        }
        unitId = entry->unitId;
        TaLogic005_GetNearDefensePoint(SzDuel_GetUnit((s32) unitId >> 8, unitId & 0xFF), packed & 0xFF, packed >> 8, result);
        if (result[0] >= 0) {
            entry->data.word = (result[0] << 16) | entry->data.halves.low;
            return;
        }
        entry->state = 0x5FF;
    }
}

/* Which leg (0..) of the patrol loop unit (nSide, nID) stands on, or -1. */
s32 TaLogic005_GetUnitOnCycleRoot(s32 nSide, s32 nID) {
    s32 x;
    s32 y;

    x = SzDuel_GetUnitLoc(nSide, nID) & 0xFF;
    y = SzDuel_GetUnitLoc(nSide, nID) >> 8;
    if ((x >= 2) && (x < 6) && (y == 0)) {
        return 0;
    }
    if ((x == 6) && (y >= 0) && (y < 4)) {
        return 1;
    }
    if ((x > 4) && (x < 7) && (y == 4)) {
        return 2;
    }
    if ((x == 4) && (y >= 4) && (y < 6)) {
        return 3;
    }
    if ((x > 0) && (x < 5) && (y == 6)) {
        return 4;
    }
    if ((x == 0) && (y > 2) && (y < 7)) {
        return 5;
    }
    if ((x >= 0) && (x < 2) && (y == 2)) {
        return 6;
    }
    if ((x == 2) && (y > 0) && (y < 3)) {
        return 7;
    }
    return -1;
}

/* The patrol point nearest to (nX, nZ). */
s32 TaLogic005_GetNearCyclePoint(s32 nX, s32 nZ) {
    s32 i;
    s32 cyclePoint;
    s32 var_s2;
    s32 var_s3;
    s32 var_s6;
    s32 var_v0;

    cyclePoint = -1;
    i = 0;
    do {
        if (nZ < (TaLogic_GetCyclePoint(i) >> 8)) {
            var_s2 = nZ;
        } else {
            var_s2 = TaLogic_GetCyclePoint(i) >> 8;
        }
        if ((TaLogic_GetCyclePoint(i) >> 8) < nZ) {
            var_s3 = nZ;
        } else {
            var_s3 = TaLogic_GetCyclePoint(i) >> 8;
        }
        if (nX < (TaLogic_GetCyclePoint(i) & 0xFF)) {
            var_s6 = nX;
        } else {
            var_s6 = TaLogic_GetCyclePoint(i) & 0xFF;
        }
        if ((TaLogic_GetCyclePoint(i) & 0xFF) < nX) {
            var_v0 = nX;
        } else {
            var_v0 = TaLogic_GetCyclePoint(i) & 0xFF;
        }
        if (((var_v0 - var_s6) + (var_s3 - var_s2)) >= -1) {
            cyclePoint = TaLogic_GetCyclePoint(i);
        }
        i += 1;
    } while (i < 8);
    return cyclePoint;
}

/* Patrol point `nNo` (0..7) of this duelist's loop. */
s32 TaLogic_GetCyclePoint(s32 nNo) {
    switch (nNo) {
    case 0:
        return 2;
    case 1:
        return 6;
    case 2:
        return 0x406;
    case 3:
        return 0x404;
    case 4:
        return 0x604;
    case 5:
        return 0x600;
    case 6:
        return 0x200;
    case 7:
        return 0x202;
    default:
        return 2;
    }
}

typedef struct Unit_001229F0 {
    u16 id;
    u8 pad02[2];
    s16 field04;
    u8 pad06[2];
    u16 field08;
    u16 field0A;
} Unit_001229F0;

/* Orders an effect monster (task `pTask`): where its effect does most (`fGoalFirst`: try its goal first). */
void TaLogic_Ishtar_CommandEfcMonster(void *pTask, s32 fGoalFirst) {
    extern s32 SzDuel_GetUnitCardNo();
    extern void TaLogic_Ishtar_CommandBtlUnit();
    s32 side;
    s32 value;
    u8 count = 0;
    Unit_001229F0 *unit = pTask;
    s32 i;

    if (SzDuel_GetUnit(unit->id >> 8, unit->id & 0xFF) != 0) {
        side = Ta_GetCurrentSide(unit->id >> 8, unit->id & 0xFF);
        value = SzDuel_GetUnitLoc(unit->id >> 8, unit->id & 0xFF);
        switch (SzDuel_GetUnitCardNo(unit->id >> 8, unit->id & 0xFF)) {
        case 0x235:
            i = 6;
            do {
                if (SzDuel_GetUnitStatus(side, i, 4) != 0) {
                    if (side == Ta_IsUnitControl(side, i)) {
                        count++;
                    }
                }
                if (SzDuel_GetUnitStatus(side == 0 ? 1 : 0, i, 4) != 0) {
                    if (side == Ta_IsUnitControl(side == 0 ? 1 : 0, i)) {
                        count++;
                    }
                }
                i++;
            } while (i < 11);
            if (count > 0) {
                unit->field04 = 0x3FF;
                *(u32 *)&unit->field08 = (value << 16) | unit->field08;
            }
            break;
        }
        TaLogic_Ishtar_CommandBtlUnit(unit, 0);
    }
}

typedef struct Data_00122B50 {
    u16 id;
    u16 pad2;
    s16 field4;
    u16 pad6;
    u32 field8;
} Data_00122B50;

/* Orders a trap card (task `pTask`): where to set it near the opponent's path. */
void TaLogic005_CommandTrapBUnit(void *pTask) {
    Data_00122B50 *p;
    s32 i;
    s32 loc;
    s32 var_s3;
    s32 cardNo;
    s32 var_s4;
    u16 id;

    extern s32 SzDuel_GetUnitCardNo();

    p = pTask;
    id = p->id;
    if (SzDuel_GetUnit((s32)id >> 8, id & 0xFF) != 0) {
        Ta_GetCurrentSide((s32)p->id >> 8, p->id & 0xFF);
        loc = SzDuel_GetUnitLoc((s32)p->id >> 8, p->id & 0xFF);
        cardNo = SzDuel_GetUnitCardNo((s32)p->id >> 8, p->id & 0xFF);
        var_s4 = -1;
        switch (cardNo) {
        case 0x33D:
            p->field4 = 0x3FF;
            p->field8 = (s32)(u16)p->field8;
            break;
        case 0x332:
            p->field4 = 0x3FF;
            p->field8 = (s32)((u16)p->field8 | 0x01000000);
            break;
        case 0x334:
            {
                s32 var_s5;
                s32 var_s2;

                var_s3 = var_s4;
                p->field4 = 0x3FF;
                for (i = 0; i < 7; i++) {
                    for (var_s5 = 0, var_s2 = 0; var_s5 < 7; var_s5++, var_s2 += 0x100) {
                        if ((SzDuel_GetField(i, var_s5) == 1) &&
                            (SzDuel_GetMapUnit(i, var_s5) == 0) &&
                            (((((i < (loc & 0xFF)) ? (loc & 0xFF) : i) -
                               (((loc & 0xFF) < i) ? (loc & 0xFF) : i)) +
                              (((var_s5 < (loc >> 8)) ? (loc >> 8) : var_s5) -
                               (((loc >> 8) < var_s5) ? (loc >> 8) : var_s5))) > var_s3)) {
                            var_s4 = var_s2 | i;
                        }
                    }
                }
                if (var_s4 >= 0) {
                    p->field8 = (s32)((u16)p->field8 | 0x01000000);
                } else {
                    p->field4 = 0x5FF;
                }
            }
            break;
        }
        p->field4 = 0x5FF;
    }
}

typedef struct {
    s16 card;
    u8 f2;
    u8 pad3;
    s16 f4;
    u8 pad6[6];
    s32 fC;
} Act_00122D30;

typedef struct {
    u8 pad0[0x3C];
    u16 id;
    u8 pad3E[0x22];
} Card_00122D30;

/* The summon task for side `nSide`: which hand cards to play and where, into `pInput`; -1 when it plays none. */
s32 TaLogic_Ishtar_GetMinimumTask_Summon(s32 wUnit, s32 nSide, s32 pInput) {
    extern s32 TaLogic_GetUnitNum(s32, s32);
    Card_00122D30 buf;
    s32 res;
    s32 type;
    Act_00122D30 *act = (Act_00122D30 *)pInput;
    s32 card;
    s32 r;

    act->card = wUnit;
    if (SzDuel_InqHandPhase(nSide) == 0) {
        return -1;
    }
    if (TaLogic_GetUnitNum(nSide, 0) == 5 && TaLogic_GetUnitNum(nSide, 1) == 5) {
        return -1;
    }
    if ((type = TaLogic_Ishtar_IsHandPlay(nSide, &buf)) < 0) {
        return -1;
    }
    act->f2 = 10;
    act->fC = 0;
    card = SzDuel_GetUnitLoc(wUnit >> 8, wUnit & 0xFF);
    if (type == 0) {
        if (TaLogic005_SetComboQue(nSide, (u8 *)act, &buf) >= 0) {
            res = TaLogic_GetNearCard2(&buf, card & 0xFF, card >> 8, nSide == 0 ? 1 : 0, 2, 0x1F, 2, 2, 0, TaLogic_Ishtar_GetWarnHideLvl(nSide));
            if (res < 0) {
                if (SzDuel_GetUnitMonsterCount(nSide) < 4) {
                    r = TaLogic005_GetSummonPiece(nSide, type, &buf, res);
                    if (r < 0) {
                        return -1;
                    }
                    act->f4 = r;
                    return 1;
                }
            } else {
                r = TaLogic005_GetSummonPiece(nSide, type, &buf, res);
                if (r < 0) {
                    return -1;
                }
                act->f4 = r;
                return 1;
            }
        }
    } else {
        res = TaLogic_GetNearCard2(&buf, card & 0xFF, card >> 8, nSide == 0 ? 1 : 0, 2, 0x1F, 2, 2, 0, TaLogic_Ishtar_GetWarnHideLvl(nSide));
    }
    if (type == 3) {
        TaLogic_Ishtar_SetSpecialComboQue(nSide, act, &buf, 1);
        r = TaLogic005_GetSummonPiece(nSide, type, &buf, res);
        if (r < 0) {
            return -1;
        }
        act->f4 = r;
        return 1;
    } else if (type == 2) {
        TaLogic_Ishtar_SetSpecialComboQue(nSide, act, &buf, 0);
        r = TaLogic005_GetSummonPiece(nSide, type, &buf, res);
        if (r < 0) {
            return -1;
        }
        act->f4 = r;
        return 1;
    } else {
        if (TaLogic005_GetSpellPlay(nSide, (u8 *)act, &buf, buf.id) < 0) {
            return -1;
        }
        r = TaLogic005_GetSummonPiece(nSide, type, &buf, -1);
        if (r < 0) {
            return -1;
        }
        act->f4 = r;
        return 1;
    }
}

typedef struct Nibbles_00123010 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_00123010;

/* The square side `nSide` summons a card of kind `sKind` to. */
s32 TaLogic005_GetSummonPiece(s32 nSide, u8 sKind, void *pInput, s32 nMode) {
    Nibbles_00123010 path[12];
    u8 info[8];
    s32 n;
    Nibbles_00123010 *p;
    u8 kind;

    extern s32 TaLogic_Ishtar_GetSommonPiecePreference();
    extern s32 TaLogic_IsUnitWin4();
    extern s32 TaLogic_GetInvadeRoot2();
    extern s32 TaLogic_GetRoot2(s32, s32, s32, s32, s32, s32, u16, u8);

    if (pInput == NULL) {
        return -1;
    }
    p = path;
    n = 0;
    do {
        p->low = p->high = 15;
        n++;
        p++;
    } while (n < 12);

    kind = *((u8 *)pInput + 0x3E) >> 5;
    if (kind == 0 || kind == 3) {
        if (nMode >= 0) {
            s32 position;
            s32 y;
            s32 x;
            s32 i;
            s32 target_y;
            s32 target_x;
            s32 best_position;
            s32 best_distance;
            s32 target;
            s32 distance;

            best_distance = 255;
            best_position = 65535;
            target = SzDuel_GetUnitLoc(nMode >> 8, nMode & 255);
            i = 0;
            target_y = target >> 8;
            target_x = target & 255;
            do {
                if ((position = TaLogic_Ishtar_GetSommonPiecePreference(nSide, i)) >= 0) {
                    x = position & 255;
                    y = position >> 8;
                    if (SzDuel_GetField(x, y) != 8 &&
                        (SzDuel_GetField(x, y) != 9 || Ta_IsVirus_Chk3(pInput, x, y) != 1) &&
                        SzDuel_GetMapUnit(x, y) == 0) {
                        if (TaLogic_IsUnitWin4(pInput, nMode, TaLogic_Ishtar_GetWarnHideLvl(nSide), target_x, target_y, 0) > 0) {
                            distance = TaLogic_GetInvadeRoot2(pInput, path, x, y, target_x, target_y, nMode, 0, 3,
                                                    (u16)TaLogic_Ishtar_GetWarnHideLvl(nSide));
                        } else {
                            distance = TaLogic_GetRoot2((s32)pInput, (s32)path, x, y, target_x, target_y, nMode, 3);
                        }
                        if (TaLogic_GetMinGoalCount((u8 *)path) > 0 && distance < best_distance) {
                            best_distance = distance;
                            best_position = position;
                        }
                    }
                }
                i++;
            } while (i < 8);
            if (best_position != 65535) {
                return best_position;
            }
            best_position = -1;
            return best_position;
        } else {
            s32 y;
            s32 x;
            s32 i;
            s32 best_distance;
            s32 best_position;
            s32 distance;

            best_distance = 14;
            best_position = -1;
            i = 0;
            do {
                if ((nMode = TaLogic_Ishtar_GetSommonPiecePreference(nSide, i)) >= 0) {
                    x = nMode & 255;
                    y = nMode >> 8;
                    if (SzDuel_GetField(x, y) != 8 &&
                        (SzDuel_GetField(x, y) != 9 || Ta_IsVirus_Chk3(pInput, x, y) != 1) &&
                        SzDuel_GetMapUnitID(x, y) < 0) {
                        TaLogic005_GetNearDefensePoint((s32)pInput, x, y, (s32 *)info);
                        distance = info[4];
                        if (distance < best_distance && distance >= 0) {
                            best_position = nMode;
                            best_distance = distance;
                        }
                    }
                }
                i++;
            } while (i < 8);
            if (best_distance < 14) {
                return best_position;
            }
            {
                s32 fallback_y;
                s32 fallback_x;
                s32 fallback_i = 0;
                s32 fallback_position;
                do {
                    if ((fallback_position = TaLogic_Ishtar_GetSommonPiecePreference(nSide, fallback_i)) >= 0) {
                        fallback_x = fallback_position & 255;
                        fallback_y = fallback_position >> 8;
                        if (SzDuel_GetField(fallback_x, fallback_y) != 8 &&
                            (SzDuel_GetField(fallback_x, fallback_y) != 9 ||
                             Ta_IsVirus_Chk3(pInput, fallback_x, fallback_y) != 1) &&
                            SzDuel_GetMapUnitID(fallback_x, fallback_y) < 0 &&
                            SzDuel_GetField(fallback_x, fallback_y) == 4) {
                            return fallback_position;
                        }
                    }
                    fallback_i++;
                } while (fallback_i < 8);
            }
        }
    } else {
        s32 y;
        s32 x;
        s32 i;
        s32 best_position;

        best_position = -1;
        i = 0;
        do {
            if ((nMode = TaLogic_Ishtar_GetSommonPiecePreference(nSide, i)) >= 0) {
                x = nMode & 255;
                y = nMode >> 8;
                if (SzDuel_GetField(x, y) != 8 &&
                    (SzDuel_GetField(x, y) != 9 || Ta_IsVirus_Chk3(pInput, x, y) != 1) &&
                    SzDuel_GetMapUnitID(x, y) < 0 && y < 8) {
                    best_position = nMode;
                }
            }
            i++;
        } while (i < 8);
        if (best_position >= 0) {
            return best_position;
        }
    }
    return -1;
}

typedef struct Nibbles_00123500 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_00123500;

typedef struct Result_00123500 {
    s32 packed;
    u8 best;
} Result_00123500;

/* The nearest free defence point a unit (record `pVarInfo`) on (nX, nZ) can reach, into `pPick`. */
void TaLogic005_GetNearDefensePoint(s32 pVarInfo, s32 nX, s32 nZ, void *pPick) {
    extern s32 TaLogic_GetRoot2();
    Result_00123500 *result = pPick;
    Nibbles_00123500 buffer[12];
    s32 j;
    s32 value;
    s32 hi;
    s32 lo;
    s32 score;
    s32 i;

    result->packed = -1;
    result->best = 0xFF;
    for (j = 0; j < 12; j++) {
        buffer[j].low = buffer[j].high = 0xF;
    }
    i = 0;
    do {
        if (TaLogic005_IsEmptyDefensePoint(i) == 1) {
            value = TaLogic005_GetDefensePoint(i);
            lo = value & 0xFF;
            hi = value >> 8;
            score = SzDuel_GetMapUnitID(lo, hi);
            if (score < 0) {
                score = 0xFFFF;
            }
            score = TaLogic_GetRoot2(pVarInfo, buffer, nX, nZ, lo, hi, (u16)score, 7);
            if (score < result->best && score >= 0) {
                result->best = score;
                result->packed = value;
                return;
            }
        }
        i++;
    } while (i < 3);
}

/* Defence point `nNo` (0..2) in front of the leader. */
s32 TaLogic005_GetDefensePoint(s32 nNo) {
    switch (nNo) {                                 /* irregular */
    case 0:
        return 0x303;
    case 1:
        return 0x304;
    default:
    case 2:
        return 0x302;
    }
}

/* Whether defence point `nNo` is free. */
s32 TaLogic005_IsEmptyDefensePoint(s32 nNo) {
    s32 var_v0;

    switch (nNo) {
        case 0:
            var_v0 = 0x303;
            break;
        case 1:
            var_v0 = 0x304;
            break;
        case 2:
        default:
            var_v0 = 0x302;
            break;
    }
    if ((var_v0 >= 0) && (SzDuel_GetMapUnit(var_v0 & 0xFF, var_v0 >> 8) == 0)) {
        return 1;
    }
    return 0;
}

/* Whether side `nSide` should play from its hand this turn (and what, into `pInput`). */
s32 TaLogic_Ishtar_IsHandPlay(s32 nSide, void *pInput) {
    s32 cards[8];
    u8 scratch[32];
    s32 count;
    u8 state0;
    u8 state1;
    s32 *card;
    s32 *card2;
    s32 index;
    s32 slot;
    u8 count2;
    s32 slot2;
    u8 count3;
    s32 slot3;
    u8 count4;
    s32 slot4;
    s32 *finalCard;
    s32 finalIndex;
    s32 result;
    extern s32 TaLogic_GetUnitNum();
    extern s32 SzDuel_GetUnitCardNo();

    state0 = (u8)TaLogic_GetUnitNum(nSide, 0);
    state1 = (u8)TaLogic_GetUnitNum(nSide, 1);
    count = 0;
    if (pInput == NULL) {
        return -1;
    }
    TaHand_GetNextHand(nSide, cards);
    if (state0 == 5) {
        if (TaLogic005_GetSpellPlay(nSide, scratch, pInput, 999) >= 0) {
            return 1;
        }
        return -1;
    }
    if (state1 == 5) {
        if (count < TaHand_GetNextHandNum(nSide)) {
            card = cards;
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
    if (Ta_GetUnitNumFrom22bitFlagList((u8)TaLogic005_Is2Head_ThunderDragon(nSide, cards)) == 3) {
        if (TaLogic_Ishtar_SetSpecialComboQue(nSide, scratch, pInput, 1) >= 0) {
            return 3;
        }
    }
    if (TaLogic005_GetSpecialSpellPlay(nSide, scratch, pInput) >= 0) {
        return 2;
    }
    if (state0 == 0) {
        index = 0;
        if (index < TaHand_GetNextHandNum(nSide)) {
            card2 = cards;
            do {
                if ((TaHand_GetCardKind(*card2) >> 5) == 0 &&
                    TaHand_CanAffordSummonCost(nSide, *card2) == 1 &&
                    TaLogic005_IsKeepHandCombo(nSide, cards, (u16)*card2) == 0) {
                    return 0;
                }
                card2++;
                index++;
            } while (index < TaHand_GetNextHandNum(nSide));
        }
    }
    slot = 6;
    do {
        if (SzDuel_GetUnitStatus(nSide, slot, 4) != 0) {
            if (nSide == Ta_IsUnitControl(nSide, slot)) {
                count = (u8)(count + 1);
            }
        }
        if (SzDuel_GetUnitStatus((nSide == 0) ? 1 : 0, slot, 4) != 0 &&
            nSide == Ta_IsUnitControl((nSide == 0) ? 1 : 0, slot)) {
            count = (u8)(count + 1);
        }
        slot++;
    } while (slot < 11);
    if ((u8)count > 0) {
        if (TaLogic005_GetSpecialCardPlay(nSide, scratch, pInput, 0x235) >= 0) {
            return 2;
        }
    }
    slot2 = 1;
    count2 = 0;
    while (1) {
        if ((SzDuel_GetUnitKind(nSide, slot2) & 0x1F) == 0x10) {
            if (nSide == Ta_IsUnitControl(nSide, slot2)) {
                count2++;
            }
        }
        if ((SzDuel_GetUnitKind((nSide == 0) ? 1 : 0, slot2) & 0x1F) == 0x10 &&
            nSide == Ta_IsUnitControl((nSide == 0) ? 1 : 0, slot2)) {
            count2++;
        }
        slot2++;
        if (slot2 > 5) {
            break;
        }
    }
    if (count2 >= 3) {
        if (TaLogic005_GetSpecialCardPlay(nSide, scratch, pInput, 0x251) >= 0) {
            return 2;
        }
    }
    slot3 = 1;
    count3 = 0;
    while (1) {
        if (SzDuel_GetUnitCardNo(nSide, slot3) == 0x258) {
            if (nSide == Ta_IsUnitControl(nSide, slot3)) {
                count3++;
            }
        }
        if (SzDuel_GetUnitCardNo((nSide == 0) ? 1 : 0, slot3) == 0x258 &&
            nSide == Ta_IsUnitControl((nSide == 0) ? 1 : 0, slot3)) {
            count3++;
        }
        slot3++;
        if (slot3 > 5) {
            break;
        }
    }
    if (count3 >= 2) {
        if (TaLogic005_GetSpecialCardPlay(nSide, scratch, pInput, 0x230) >= 0) {
            return 2;
        }
    }
    slot4 = 1;
    count4 = 0;
    while (1) {
        if (SzDuel_GetUnitCardNo(nSide, slot4) == 0x230) {
            if (nSide == Ta_IsUnitControl(nSide, slot4)) {
                count4++;
            }
        }
        if (SzDuel_GetUnitCardNo((nSide == 0) ? 1 : 0, slot4) == 0x230 &&
            nSide == Ta_IsUnitControl((nSide == 0) ? 1 : 0, slot4)) {
            count4++;
        }
        slot4++;
        if (slot4 > 5) {
            break;
        }
    }
    if (count4 >= 2) {
        if (TaLogic005_GetSpecialCardPlay(nSide, scratch, pInput, 0x258) >= 0) {
            return 2;
        }
    }
    if (TaLogic_IsAttackedNow(nSide, 0, 0) == 1) {
        if (TaLogic005_GetSpecialCardPlay(nSide, scratch, pInput, 0x54) >= 0) {
            return 2;
        }
    }
    finalIndex = 0;
    if (finalIndex < TaHand_GetNextHandNum(nSide)) {
        finalCard = cards;
        do {
            if ((TaHand_GetCardKind(*finalCard) >> 5) == 0 &&
                TaHand_CanAffordSummonCost(nSide, *finalCard) == 1) {
                SzDuel_InitCardInfo(pInput, cards[finalIndex]);
                return 0;
            }
            finalCard++;
            finalIndex++;
        } while (finalIndex < TaHand_GetNextHandNum(nSide));
    }
    result = TaLogic005_GetSpellPlay(nSide, scratch, pInput, 999);
    if (result >= 0) {
        return result;
    }
    return -1;
}

/* Which hand cards of side `nSide` (`arNextHand`) make Twin-Headed Thunder Dragon, as a bit list. */
s32 TaLogic005_Is2Head_ThunderDragon(s32 nSide, s32 *arNextHand) {
    s32 i;
    s32 result;
    s32 *entry;

    result = 0;
    i = 0;
    if (0 < TaHand_GetNextHandNum(nSide)) {
        do {
            entry = &arNextHand[i];
            if ((TaHand_CanAffordSummonCost(nSide, *entry) == 1) && ((TaHand_GetCardKind(*entry) >> 5) == 0)) {
                result = (result + (1 << (4 - i))) & 0xFF;
                i = TaHand_GetNextHandNum(nSide);
            }
            i++;
        } while (i < TaHand_GetNextHandNum(nSide));
    }
    {
        s32 resultCheck;
        resultCheck = result & 0xFF;
        if (resultCheck == 0) {
            return 0;
        }
    }
    i = 0;
    if (0 < TaHand_GetNextHandNum(nSide)) {
        do {
            entry = &arNextHand[i];
            if ((TaHand_CanAffordSummonCost(nSide, *entry) == 1) && ((TaHand_GetCardKind(*entry) >> 5) == 0x12)) {
                result = (result + (1 << (4 - i))) & 0xFF;
                i = TaHand_GetNextHandNum(nSide);
            }
            i++;
        } while (i < TaHand_GetNextHandNum(nSide));
    }
    {
        s32 resultCheck;
        resultCheck = result & 0xFF;
        if (resultCheck == 2) {
            i = 0;
            if (0 < TaHand_GetNextHandNum(nSide)) {
                do {
                    entry = &arNextHand[i];
                    if ((TaHand_CanAffordSummonCost(nSide, *entry) == 1) && ((TaHand_GetCardKind(*entry) >> 5) == 0xF)) {
                        result = (result + (1 << (4 - i))) & 0xFF;
                        i = TaHand_GetNextHandNum(nSide);
                    }
                    i++;
                } while (i < TaHand_GetNextHandNum(nSide));
            }
            return result & 0xFF;
        }
    }
    return 0;
}

/* Whether this duelist keeps card `nCardNo` in the hand for the Twin-Headed Thunder Dragon combination. */
s32 TaLogic005_IsKeepHandCombo(s32 nSide, s32 *arNextHand, s32 nCardNo) {
    s32 temp_s0;

    temp_s0 = TaHand_GetCardKind(nCardNo & 0xFFFF) >> 5;
    if (Ta_GetUnitNumFrom22bitFlagList(TaLogic005_Is2Head_ThunderDragon(nSide, arNextHand) & 0xFF) == 3) {
        return 0;
    }
    switch (temp_s0) {
    case 18:
    case 15:
        return 1;
    case 0:
        return 1;
    }
    return 0;
}

/* The magic card side `nSide` plays now by this duelist's own rules (card 0x33D first), its slot into `bCombo`,
   the card into `pCardInfo`. */
s32 TaLogic005_GetSpecialSpellPlay(s32 nSide, void *bCombo, void *pCardInfo) {
    s32 cards[8];
    s32 i;
    s32 count;
    extern s32 SzDuel_GetUnitCurseRest();
    extern s32 SzDuel_GetUnitCardNo();

    count = 0;
    TaHand_GetNextHand(nSide, cards);
    for (i = 0; i < TaHand_GetNextHandNum(nSide); i++) {
        if (cards[i] == 0x33D) {
            *((s8 *)bCombo + 6) = i;
            SzDuel_InitCardInfo(pCardInfo, cards[i]);
            return TaHand_GetCardKind(cards[i]) >> 5;
        }
    }

    if (TaLogic005_IsDoCerem(nSide, 0x34C) == 1) {
        for (i = 0; i < TaHand_GetNextHandNum(nSide); i++) {
            if (cards[i] == 0x34C) {
                *((s8 *)bCombo + 6) = i;
                SzDuel_InitCardInfo(pCardInfo, cards[i]);
                return TaHand_GetCardKind(cards[i]) >> 5;
            }
        }
    }

    for (i = 0; i < TaHand_GetNextHandNum(nSide); i++) {
        if (cards[i] == 0x332) {
            *((s8 *)bCombo + 6) = i;
            SzDuel_InitCardInfo(pCardInfo, cards[i]);
            return TaHand_GetCardKind(cards[i]) >> 5;
        }
    }

    i = 0;
    while (1) {
        if (nSide == Ta_IsUnitControl(nSide, i)) {
            if (SzDuel_GetUnitAttr(nSide, i) == 4) {
                count++;
            }
        }
        if (nSide == Ta_IsUnitControl(nSide == 0 ? 1 : 0, i)) {
            if (SzDuel_GetUnitAttr(nSide == 0 ? 1 : 0, i) == 4) {
                count++;
            }
        }
        i++;
        if (i > 5) {
            break;
        }
    }

    if (count >= 3) {
        for (count = 0; count < TaHand_GetNextHandNum(nSide); count++) {
            if (cards[count] == 0x2E6) {
                *((s8 *)bCombo + 6) = count;
                SzDuel_InitCardInfo(pCardInfo, cards[count]);
                return TaHand_GetCardKind(cards[count]) >> 5;
            }
        }
    }

    {
        s32 facedown;
        s32 slot;

        facedown = 0;
        slot = 0;
        do {
            if (nSide == Ta_IsUnitControl(nSide, slot)) {
                if (SzDuel_GetUnitCurseRest(nSide, slot) == 0xFF) {
                    facedown++;
                }
            }
            if (nSide == Ta_IsUnitControl(nSide == 0 ? 1 : 0, slot)) {
                if (SzDuel_GetUnitCurseRest(nSide == 0 ? 1 : 0, slot) == 0xFF) {
                    facedown++;
                }
            }
            slot++;
        } while (slot < 11);

        if (facedown > 0) {
            for (count = 0; count < TaHand_GetNextHandNum(nSide); count++) {
                if (cards[count] == 0x31C) {
                    *((s8 *)bCombo + 6) = count;
                    SzDuel_InitCardInfo(pCardInfo, cards[count]);
                    return TaHand_GetCardKind(cards[count]) >> 5;
                }
            }
        }
    }

    {
        s32 special;
        s32 slot;

        slot = 6;
        special = 0;
        do {
            if (nSide == Ta_IsUnitControl(nSide, slot)) {
                if (SzDuel_GetUnitCardNo(nSide, slot) == 0x33D) {
                    special++;
                }
            }
            if (nSide == Ta_IsUnitControl(nSide == 0 ? 1 : 0, slot)) {
                if (SzDuel_GetUnitCardNo(nSide == 0 ? 1 : 0, slot) == 0x33D) {
                    special++;
                }
            }
            slot++;
        } while (slot < 11);

        if (special > 0) {
            for (count = 0; count < TaHand_GetNextHandNum(nSide); count++) {
                if (cards[count] == 0x334) {
                    *((s8 *)bCombo + 6) = count;
                    SzDuel_InitCardInfo(pCardInfo, cards[count]);
                    return TaHand_GetCardKind(cards[count]) >> 5;
                }
            }
        }
    }
    return -1;
}

/* Whether side `nSide` holds card `nCardNo` and can summon it (its slot into `bCombo`, the card into `pCardInfo`). */
s32 TaLogic005_GetSpecialCardPlay(s32 nSide, void *bCombo, void *pCardInfo, s32 nCardNo) {
    s32 entries[8];
    s32 i;

    TaHand_GetNextHand(nSide, entries);
    for (i = 0; i < TaHand_GetNextHandNum(nSide); i++) {
        if (((nCardNo & 0xFFFF) == entries[i]) && (TaHand_CanAffordSummonCost(nSide, entries[i]) == 1)) {
            ((s8 *)bCombo)[6] = i;
            SzDuel_InitCardInfo(pCardInfo, entries[i]);
            return TaHand_GetCardKind(entries[i]) >> 5;
        }
    }
    return -1;
}

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
                        if (TaHand_CanAffordSummonCost(nSide, card) == 1) {
                            if (best < value) {
                                TaLogic_Ishtar_ConvEmptyCombo(nSide, *node, entries);
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
void TaLogic_Ishtar_ConvEmptyCombo(s32 nSide, void *pCardInfo, s32 *pResult) {
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
s32 TaLogic_Ishtar_SetSpecialComboQue(s32 nSide, void *bCombo, void *pCardInfo, s32 nOpt) {
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
                if (o2->id == list[i] && TaHand_CanAffordSummonCost(nSide, list[i]) == 1) {
                    o1->slot[0] = i;
                }
            }
        }
        return 0;
    }
    TaLogic005_Is2Head_ThunderDragon(nSide, list);
    for (i = 0; i < TaHand_GetNextHandNum(nSide); i++) {
        t = TaHand_GetCardKind(list[i]);
        if ((t >> 5) == 0 && (t & 0x1F) == 0 && TaHand_CanAffordSummonCost(nSide, list[i]) == 1) {
            o1->slot[0] = i;
        }
    }
    for (i = 0; i < TaHand_GetNextHandNum(nSide); i++) {
        t = TaHand_GetCardKind(list[i]);
        if ((t >> 5) == 0 && (t & 0x1F) == 0x12 && TaHand_CanAffordSummonCost(nSide, list[i]) == 1) {
            o1->slot[1] = i;
        }
    }
    for (i = 0; i < TaHand_GetNextHandNum(nSide); i++) {
        t = TaHand_GetCardKind(list[i]);
        if ((t >> 5) == 0 && (t & 0x1F) == 0xF && TaHand_CanAffordSummonCost(nSide, list[i]) == 1) {
            o1->slot[2] = i;
        }
    }
    return 0;
}

/* Ta_GetSommonPiecePreference for this duelist. */
s32 TaLogic_Ishtar_GetSommonPiecePreference(s32 nSide, u32 nPr) {
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
s32 TaLogic_Ishtar_GetMinimumTask_RunMission(UnitTask *pTask, s32 nSide, void *pInput, u8 fFirst) {
    extern s32 TaLogic_IsRunPassRoot(s32, s32, s32, s32, s32, s32, void *, u8);
    extern s32 TaLogic_Ishtar_IsOpenUnit();
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

    position = SzDuel_GetUnitLoc(pTask->ownerId >> 8, pTask->ownerId & 0xFF);
    i = 0;
    do {
        cells[i].low = cells[i].high = 15;
        i++;
    } while (i < 12);

    {
        u16 value = (u16)TaLogic_Ishtar_GetWarnHideLvl(nSide);
        originalX = position & 0xFF;
        originalY = position >> 8;
        if (TaLogic_GetUnitWarning(originalX, originalY, pTask->ownerId, 2, value, 0) == 0) {
            out->id = pTask->ownerId;
            out->action = 6;
            out->position = position;
            out->mode = TaLogic_IsDefStyleUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, out->position, 1, 0);
            out->value = TaLogic_Ishtar_IsOpenUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, pTask);
            TaLogic005_InitRogicControl(pTask, fFirst);
            return 0;
        } else {
            result = GetMoveRange(SzDuel_GetUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF), originalX, originalY);
            if (result == 0) {
                out->id = pTask->ownerId;
                out->action = 6;
                out->position = position;
                out->mode = TaLogic_IsDefStyleUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, out->position, 1, 0);
                out->value = TaLogic_Ishtar_IsOpenUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, pTask);
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
                                value = (u16)TaLogic_Ishtar_GetWarnHideLvl(nSide);
                                score = TaLogic_GetUnitWarning(x, y, pTask->ownerId, 2, value, 0);
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
                    out->value = TaLogic_Ishtar_IsOpenUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, pTask);
                } else {
                    out->id = pTask->ownerId;
                    out->action = 6;
                    out->position = position;
                    out->mode = TaLogic_IsDefStyleUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, out->position, 1, 0);
                    out->value = TaLogic_Ishtar_IsOpenUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, pTask);
                }
                TaLogic005_InitRogicControl(pTask, fFirst);
            }
        }
    }
    return 0;
}

/* How careful this duelist is about hidden cards (by its life points and monster count). */
s32 TaLogic_Ishtar_GetWarnHideLvl(s32 nSide) {
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

/* The task of a unit attacking (task `pTask`): its path to the goal, into `pInput`; -1 when it has none (`fFirst`
   = 1 for the unit's first-choice task). */
s32 TaLogic_Ishtar_GetMinimumTask_AtkMission(void *pTask, s32 nSide, void *pInput, u8 fFirst) {
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

    flag = TaLogic_Ishtar_IsOpenUnit(source->position >> 8, source->position & 0xFF, pTask);
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
    if (GetMoveRange(object, sourceX, sourceY) == 0) {
        s32 cost;
        output->position = source->position;
        output->mode = 6;
        output->target = sourceTarget;
        cost = TaLogic_GetUnitWarning(sourceX, sourceY, nSide, 2, 1,
                            (u8)TaLogic_LifePenalty(nSide));
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

        penalty = TaLogic_LifePenalty(nSide);
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
                    s32 penalty = TaLogic_LifePenalty(nSide);
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
s32 TaLogic_Ishtar_GetMinimumTask_MoveMission(void *pTask, s32 nSide, void *pInput, u8 fFirst, u8 nKind) {
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
            ((Output_00125B70 *)pInput)->value = TaLogic_Ishtar_IsOpenUnit(((Unit_00125B70 *)pTask)->position >> 8, ((Unit_00125B70 *)pTask)->position & 0xFF, pTask);
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
            ((Output_00125B70 *)pInput)->value = TaLogic_Ishtar_IsOpenUnit(((Unit_00125B70 *)pTask)->position >> 8, ((Unit_00125B70 *)pTask)->position & 0xFF, pTask);
        TaLogic005_InitRogicControl(pTask, fFirst);
        return 0;
    }

        if (best != 0xFF) {
            ((Output_00125B70 *)pInput)->position = ((Unit_00125B70 *)pTask)->position;
            ((Output_00125B70 *)pInput)->kind = 6;
            ((Output_00125B70 *)pInput)->target = (coords[best].y << 8) | coords[best].x;
            ((Output_00125B70 *)pInput)->flag = TaLogic_IsDefStyleUnit(((Unit_00125B70 *)pTask)->position >> 8, ((Unit_00125B70 *)pTask)->position & 0xFF, ((Output_00125B70 *)pInput)->target, nKind, 0);
            ((Output_00125B70 *)pInput)->value = TaLogic_Ishtar_IsOpenUnit(((Unit_00125B70 *)pTask)->position >> 8, ((Unit_00125B70 *)pTask)->position & 0xFF, pTask);
        } else {
            ((Output_00125B70 *)pInput)->position = ((Unit_00125B70 *)pTask)->position;
            ((Output_00125B70 *)pInput)->kind = 6;
            ((Output_00125B70 *)pInput)->target = initial;
            ((Output_00125B70 *)pInput)->flag = TaLogic_IsDefStyleUnit(((Unit_00125B70 *)pTask)->position >> 8, ((Unit_00125B70 *)pTask)->position & 0xFF, ((Output_00125B70 *)pInput)->target, nKind, 0);
            ((Output_00125B70 *)pInput)->value = TaLogic_Ishtar_IsOpenUnit(((Unit_00125B70 *)pTask)->position >> 8, ((Unit_00125B70 *)pTask)->position & 0xFF, pTask);
        }
        TaLogic005_InitRogicControl(pTask, fFirst);
    }
    }
    return 0;
}

/* Whether this duelist opens (turns face up) unit (nSide, nID) now: 0 no, 1 or 2 by its kind. */
s32 TaLogic_Ishtar_IsOpenUnit(s32 nSide, s32 nID, void *pInfo) {
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

/* Whether unit (nSide, nID) may open while moving from (nX, nZ) to the square next to it, (gX, gZ). */
s32 TaLogic005_IsOpenMoveUnit(s32 nSide, s32 nID, s32 nX, s32 nZ, s32 gX, s32 gZ) {
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

/* Computer duelist 5's controller (duelistControllers[5]): the buttons it presses this frame. With an empty input
   queue it plans its next task and turns it into buttons, then plays the queue back one button per frame; after
   600 frames it gives up the turn (0x20, then 0x800). */
s32 duelistController05(s32 wCursorPos, void *pCtl) {
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
        if (TaLogic_Ishtar_GetMinimumTask(w, &req, wCursorPos) == 0) {
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

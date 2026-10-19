/* Computer AI of Bakura (duelist 18, duelistController18). */

#include "common.h"
#pragma conditional_move off

/* This duelist's move: picks the next unit to act, gives it a task and turns that into input `pInput`; returns 1
   when it set one. */
s32 TaLogic_Bakura_GetMinimumTask(void *pCtl, void *pInput, s32 wCursorPos) {
    UnitTask *tasks = pCtl;
    s32 side;
    s32 found;
    s32 result;
    s32 index;

    side = SzDuel_GetTurnOwner();
    found = 0;
    if ((result = TaLogic_Bakura_GetNextActiveUnit(tasks, side, (s32)pInput)) < 0) {
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
    TaLogic_Bakura_CommandUnit(&tasks[index]);
    switch ((tasks[index].mission >> 8) & 0xFF) {
    case TASK_RUN:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            TaLogic_Bakura_GetMinimumTask_RunMission(&tasks[index], side, pInput, 1);
            found = 1;
        }
        break;
    case TASK_ATTACK:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            if (TaLogic_Bakura_GetMinimumTask_AtkMission(&tasks[index], side, pInput, 1) < 0) {
                TaLogic_InitRogicControl(&tasks[index], 1);
                return 1;
            }
            found = 1;
        }
        break;
    case TASK_SUMMON:
        if (TaLogic_Bakura_GetMinimumTask_Summon(tasks[index].ownerId, side, (s32)pInput) < 0) {
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
            TaLogic_Bakura_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 1, 0);
            found = 1;
        }
        break;
    case TASK_CONFIRMUNIT:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            TaLogic_Bakura_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 1, 1);
            found = 1;
        }
        break;
    case TASK_ENCHANT:
        TaLogic_GetMinimumTask_EncMission(&tasks[index], side, pInput, 1, 0, TaLogic_Bakura_GetWarnHideLvl(side), 3, 1);
        found = 1;
        break;
    case TASK_TRAP:
        TaLogic_Bakura_GetMinimumTask_TrapMission(&tasks[index], side, pInput, 1);
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
            TaLogic_Bakura_GetMinimumTask_RunMission(&tasks[index], side, pInput, 0);
            found = 1;
        }
        break;
    case 2:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            if (TaLogic_Bakura_GetMinimumTask_AtkMission(&tasks[index], side, pInput, 0) < 0) {
                TaLogic_Bakura_GetMinimumTask_RunMission(&tasks[index], side, pInput, 0);
            }
            found = 1;
        }
        break;
    case 10:
        if (TaLogic_Bakura_GetMinimumTask_Summon(tasks[index].ownerId, side, (s32)pInput) < 0) {
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
            TaLogic_Bakura_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 0, 0);
            found = 1;
        }
        break;
    case 3:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            TaLogic_Bakura_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 0, 1);
            found = 1;
        }
        break;
    case 9:
        TaLogic_GetMinimumTask_EncMission(&tasks[index], side, pInput, 0, 0, TaLogic_Bakura_GetWarnHideLvl(side), 3, 1);
        found = 1;
        break;
    case 11:
        TaLogic_Bakura_GetMinimumTask_TrapMission(&tasks[index], side, pInput, 0);
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

/* Gives a unit of this duelist its order for this turn (attack, run, move, summon, guard). */
s32 TaLogic_Bakura_CommandUnit(u16 *pCtl) {
    extern void TaLogic018_CommandLDUnit();
    s32 temp_a1;
    s32 temp_v1_2;
    s32 temp_v1_4;
    u32 temp_v1_3;
    u16 temp_v1;
    s32 controllingSide;

    SzDuel_GetUnitLoc((s32) pCtl[0] >> 8, pCtl[0] & 0xFF);
    controllingSide = Ta_IsUnitControl((s32) pCtl[0] >> 8, pCtl[0] & 0xFF);
    if (SzDuel_GetUnit((s32) pCtl[0] >> 8, pCtl[0] & 0xFF) != 0) {
        if (SzDuel_GetUnitStatus((s32) pCtl[0] >> 8, pCtl[0] & 0xFF, 0) == 0) {
            temp_v1 = pCtl[0];
            if (temp_v1 != 0xFFFF) {
                temp_a1 = temp_v1 & 0xFF;
                if (temp_a1 == 0) {
                    if (*(s32 *)(pCtl + 4) == -1) {
                        TaLogic018_CommandLDUnit(pCtl, temp_a1);
                    }
                } else {
                    temp_v1_2 = SzDuel_GetUnitKind((s32) temp_v1 >> 8, temp_a1) >> 5;
                    switch (temp_v1_2) {
                    case 0:
                        if (TaUtil_IsExMonster((s32) pCtl[0] >> 8, pCtl[0] & 0xFF) == 1) {
                            TaLogic018_CommandEfcMonster(pCtl);
                        } else {
                            TaLogic018_CommandBtlUnit(pCtl);
                        }
                        break;
                    case 2:
                        TaLogic_CommandEncUnit(pCtl, 3, 0, TaLogic_Bakura_GetWarnHideLvl(controllingSide) & 0xFF);
                        break;
                    case 5:
                        TaLogic018_CommandBtlUnit(pCtl);
                        if ((((s32) pCtl[2] >> 8) & 0xFF) == 2) {
                            temp_v1_3 = (u32) *(s32 *)(pCtl + 4) >> 0x10;
                            temp_v1_4 = SzDuel_GetUnitLoc((s32) ((temp_v1_3 & 0xFFFF) >> 8), temp_v1_3 & 0xFF) << 0x10;
                            pCtl[2] = 0x6FF;
                            *(s32 *)(pCtl + 4) = temp_v1_4 | pCtl[4];
                        }
                        break;
                    default:
                        pCtl[2] = 0x5FF;
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
s32 TaLogic_Bakura_GetNextActiveUnit(u16 *pCtl, s32 nSide, s32 pInput) {
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
    TaLogic_Bakura_CommandUnit(pCtl + idx * 8);
    if (((pCtl[idx * 8 + 2] >> 8) & 0xFF) == 10) {
        if (SzDuel_InqHandPhase(nSide) == 1 && TaLogic_Bakura_GetMinimumTask_Summon(pos, nSide, pInput) >= 0) {
            return pos | 0x10000;
        }
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_GetUnitStatus(nSide, 0, 0) == 0) {
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_InqHandPhase(nSide) == 1 && TaLogic_Bakura_GetMinimumTask_Summon(pos, nSide, pInput) >= 0) {
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

s32 TaLogic018_GetVirusMove(s32, s32); /* extern */
s32 TaLogic018_GetSummonPoint(s32, s32, s32); /* extern */
s32 TaLogic018_IsHandPlay(s32, void *); /* extern */

typedef struct {
    u16 id;
    u16 pad2;
    s16 status;
    u16 pad6;
    u32 code;
} Object_00159760;

/* Orders this duelist's leader (task `pTask`): play from the hand, then move away from the virus zone. */
void TaLogic018_CommandLDUnit(void *pTask) {
    u8 sp40[0x20];
    u8 sp60[0x60];
    Object_00159760 *obj;
    s32 kind;
    s32 pos;
    s32 result;
    u16 id;

    obj = pTask;
    id = obj->id;
    kind = id >> 8;
    pos = SzDuel_GetUnitLoc(id >> 8, id & 0xFF);
    if (TaLogic_IsAttackedNow(obj->id >> 8, obj->id & 0xFF, 0) == 1) {
        if (SzDuel_InqHandPhase(kind) == 1) {
            obj->status = 0x50A;
        } else {
            obj->status = 0x5FF;
        }
        return;
    }
    result = TaLogic018_IsHandPlay(kind, sp60);
    if (result < 0) {
        if (SzDuel_InqHandPhase(kind) == 1) {
            obj->status = 0x60A;
        } else {
            obj->status = 0x6FF;
        }
        obj->code = (u16)obj->code | (TaLogic018_GetVirusMove(obj->id >> 8, obj->id & 0xFF) << 16);
    } else {
        if (result == 0) {
            TaLogic018_SetComboQue(kind, sp40, sp60);
        }
        if ((sp60[0x3E] >> 5) == 0 && SzDuel_GetUnitAP2(sp60, 0) > 0x5DC) {
            if (SzDuel_InqHandPhase(kind) == 1) {
                obj->status = 0x60A;
            } else {
                obj->status = 0x6FF;
            }
            obj->code = (u16)obj->code | (TaLogic018_GetSummonPoint(kind, pos & 0xFF, pos >> 8) << 16);
        }
        if (SzDuel_InqHandPhase(kind) == 1) {
            obj->status = 0x60A;
        } else {
            obj->status = 0x6FF;
        }
        obj->code = (u16)obj->code | (TaLogic018_GetVirusMove(obj->id >> 8, obj->id & 0xFF) << 16);
    }
}

#pragma opt_propagation off

/* Where unit (nSide, nID) moves to keep out of the virus squares. */
s32 TaLogic018_GetVirusMove(s32 nSide, s32 nID) {
    extern s32 TaLogic_IsPassRoot();
    s32 best;
    s16 tmp;
    s32 pos;
    s32 range;
    u8 xMin;
    u8 xMax;
    u8 yMin;
    u8 yMax;
    s32 i;
    s32 j;
    s32 d;
    s32 result;

    best = 0xFFFF;
    result = 0xFF;
    tmp = best;
    pos = SzDuel_GetUnitLoc(nSide, nID);
    range = GetMoveRange(SzDuel_GetUnit(nSide, nID), pos & 0xFF, pos >> 8);
    xMin = GetCap(0, (pos & 0xFF) - (range & 0xF));
    xMax = MinSel((pos & 0xFF) + (range & 0xF), 6);
    yMin = GetCap(0, (pos >> 8) - (range & 0xF));
    yMax = MinSel((pos >> 8) + (range & 0xF), 6);
    for (i = xMin; i <= xMax; i++) {
        for (j = yMin; j <= yMax; j++) {
            if (((pos & 0xFF) > i ? (pos & 0xFF) : i) - ((pos & 0xFF) < i ? (pos & 0xFF) : i) +
                    (((pos >> 8) > j ? (pos >> 8) : j) - ((pos >> 8) < j ? (pos >> 8) : j)) > (range & 0xF)) {
                continue;
            }
            if (SzDuel_GetField(i, j) != 9) {
                continue;
            }
            if (TaLogic_IsPassRoot(nSide, nID, pos & 0xFF, pos >> 8, i, j, &tmp) != 1) {
                continue;
            }
            if (TaLogic_IsAttackedNow2(nSide, nID, i, j, 0) != 0 && nID != 0) {
                continue;
            }
            d = TaLogic_GetUnitWarning(i, j, (nSide << 8) | nID, 3, (u16)TaLogic_Bakura_GetWarnHideLvl(nSide), 0);
            if (d < best) {
                best = d;
                result = (j << 8) | i;
            } else if (d == best && SzDuel_GetMapUnit(i, j) == 0 && SzDuel_GetMapUnit(result & 0xFF, result >> 8) != 0) {
                best = d;
                result = (j << 8) | i;
            }
        }
    }
    if (result != 0xFF) {
        return result;
    }
    return 0x303;
}
#pragma opt_propagation reset

/* The free square of the virus field round the enemy leader that is nearest to (nX, nZ); -1 when the enemy
   leader is not on a virus field. */
s32 TaLogic018_GetSummonPoint(s32 nSide, s32 nX, s32 nZ) {
    extern s32 TaLogic018_GetOutVirusZone();
    u16 buf[0x31];
    s32 i;
    s32 best;
    s32 result;
    u16 *p;
    u8 count;
    s32 dist;

    result = SzDuel_GetUnitLoc(nSide == 0 ? 1 : 0, 0);
    count = TaLogic018_GetOutVirusZone(result & 0xFF, result >> 8, buf);
    best = 0xE;
    if (count == 0) {
        return -1;
    }
    for (p = buf, i = 0; i < count; p++, i++) {
        if (SzDuel_GetUnit(*p & 0xFF, *p >> 8) == 0) {
            dist = (((nX < (*p & 0xFF)) ? (*p & 0xFF) : nX) - (((*p & 0xFF) < nX) ? (*p & 0xFF) : nX)) +
                   (((nZ < (*p >> 8)) ? (*p >> 8) : nZ) - (((*p >> 8) < nZ) ? (*p >> 8) : nZ));
            if (dist < best) {
                best = dist;
                result = *p;
            }
        }
    }
    return result;
}

typedef struct {
    u16 card;
    u8 flag;
    u8 pad3;
} Slot_00159D00;

typedef struct {
    u16 low;
    u16 high;
} DataHalves_00159D00;

typedef struct {
    u16 unitId; /* (side << 8) | unit */
    u8 pad2[2];
    u16 state;
    u8 pad6[2];
    union {
        u32 word;
        DataHalves_00159D00 halves;
    } data;
} Entry_00159D00;

/* Orders a fighting unit (task `pTask`): straight at its goal when the path is open, else the nearest enemy it can
   beat. */
void TaLogic018_CommandBtlUnit(void *pTask) {
    extern s32 TaLogic_IsRootOpen();
    extern void TaLogic_InitIgnoreLst();
    extern s32 TaLogic018_GetNearUnit();
    Entry_00159D00 *entry = pTask;
    s32 side;
    s32 player;
    s32 pos;
    s32 other;
    s32 otherPos;
    s32 i;
    u8 work[0x70];
    Slot_00159D00 list[22];
    s16 countA;
    s16 countB;

    if (SzDuel_GetUnit(entry->unitId >> 8, entry->unitId & 0xFF) != 0) {
        TaLogic_InitIgnoreLst(work);
        side = Ta_GetCurrentSide(entry->unitId >> 8, entry->unitId & 0xFF);
        other = (side == 0 ? 1 : 0) << 8;
        pos = SzDuel_GetUnitLoc(entry->unitId >> 8, entry->unitId & 0xFF);
        otherPos = SzDuel_GetUnitLoc(other >> 8, other & 0xFF);
        player = SzDuel_GetUnit(entry->unitId >> 8, entry->unitId & 0xFF);
        for (i = 0; i < 22; i++) {
            list[i].card = 0xFFFF;
            list[i].flag = 0xFF;
        }
        if (TaLogic_IsRootOpen(entry->unitId >> 8, entry->unitId & 0xFF, pos & 0xFF, pos >> 8,
                          other >> 8, other & 0xFF, otherPos & 0xFF, otherPos >> 8, 3) > 0) {
            entry->state = 0x2FF;
            entry->data.word = (other << 16) | entry->data.halves.low;
            return;
        }
        countB = 0;
        countA = 0;
        i = 1;
        while (1) {
            switch (TaLogic018_GetNearUnit(entry, 0, player, pos & 0xFF, pos >> 8,
                                  Ta_GetCurrentSide(entry->unitId >> 8, entry->unitId & 0xFF) == 0 ? 1 : 0,
                                  (u8)i, TaLogic_Bakura_GetWarnHideLvl(side), list, 0,
                                  &countA, &countB, 3, work)) {
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
            if (i > 3) {
                break;
            }
        }
        entry->state = 0x6FF;
        entry->data.word = (otherPos << 16) | entry->data.halves.low;
    }
}

/* TaLogic_GetNearUnit with this duelist's view and strength settings. */
void TaLogic018_GetNearUnit(s32 pTask, s32 pTree, s32 pVarInfo, s32 nX, s32 nZ, s32 eSide, s32 bDist, s32 WarnLvl, s32 nUnitLst, u16 wUnitNum, s32 wSize, s32 wNodeCount, u8 bChase, s32 wIgnoreLst) {
    TaLogic_GetNearUnit(pTask, pTree, pVarInfo, nX, nZ, eSide, bDist, WarnLvl,
                  nUnitLst, wUnitNum, wSize, wNodeCount, bChase,
                  0, 2500, wIgnoreLst);
}

/* Orders an effect monster (task `pTask`): where its effect does most. */
void TaLogic018_CommandEfcMonster(void *pTask) {
    extern s32 SzDuel_GetUnitCardNo();
    Entry_00159D00 *entry = pTask;
    s32 slot;

    slot = Ta_IsUnitControl(entry->unitId >> 8, entry->unitId & 0xFF);
    switch (SzDuel_GetUnitCardNo(entry->unitId >> 8, entry->unitId & 0xFF)) {
    case 0x293:
        if (SzDuel_GetUnitStatus(entry->unitId >> 8, entry->unitId & 0xFF, 4) == 0 && TaLogic_CommandGunnerUnit(entry, 0) == 1) {
            return;
        }
        break;
    case 0x287:
        if (TaLogic_CommandGunnerUnit(entry, 0) == 1) {
            entry->state = 0xBFF;
            return;
        }
        break;
    case 0x28F:
        if (Ta_GetUnitNumFrom22bitFlagList(SearchUnitByRange(0, 0, slot, 2, 0x34, 0xE)) > 5) {
            entry->state = 0x3FF;
            entry->data.word = (SzDuel_GetUnitLoc(entry->unitId >> 8, entry->unitId & 0xFF) << 16) | entry->data.halves.low;
            return;
        }
        break;
    }
    TaLogic018_CommandBtlUnit(entry);
}

/* The virus-field squares joined to (nX, nZ), into `buf` (49 entries). */
void TaLogic018_GetOutVirusZone(s32 nX, s32 nZ, u16 *buf) {
    s32 i;

    for (i = 0; i < 0x31; i++) {
        buf[i] = 0xFFFF;
    }
    TaLogic018_GetZoneSide(nX, nZ, buf);
    TaLogic018_GetZoneSize(buf);
}

/* `value`, at most 6. */
static inline s32 upper_0015A180(s32 value) {
    if (value >= 7) {
        return 6;
    }
    return value;
}

/* Adds (nX, nZ) and every virus-field square joined to it to zone list `buf` (recursive). */
void TaLogic018_GetZoneSide(s32 nX, s32 nZ, u16 *buf) {
    s32 cap;
    s32 cap2;

    if ((TaLogic018_IsZonePast((nZ << 8) | nX, buf) != 1) && (SzDuel_GetField(nX, nZ) == 9)) {
        buf[TaLogic018_GetZoneSize(buf)] = (nZ << 8) | nX;
        for (cap = GetCap(0, nX - 1); cap <= upper_0015A180(nX + 1); cap++) {
            for (cap2 = GetCap(0, nZ - 1); cap2 <= upper_0015A180(nZ + 1); cap2++) {
                if (((((nX < cap) ? cap : nX) - ((cap < nX) ? cap : nX)) + (((nZ < cap2) ? cap2 : nZ) - ((cap2 < nZ) ? cap2 : nZ))) == 1) {
                    TaLogic018_GetZoneSide(cap, cap2, buf);
                }
            }
        }
    }
}

/* Whether square `nLoc` is already in zone list `buf`. */
s32 TaLogic018_IsZonePast(s32 nLoc, u16 *buf) {
    s32 i;

    i = 0;
    do {
        if (nLoc == *buf) {
            return 1;
        }
        i++;
        buf++;
    } while (i < 0x31);
    return 0;
}

/* How many squares zone list `buf` holds. */
s32 TaLogic018_GetZoneSize(u16 *buf) {
    s32 i;
    u8 count;

    count = 0;
    i = 0;
    do {
        if (*buf != 0xFFFF) {
            count++;
        }
        i++;
        buf++;
    } while (i < 0x31);
    return count;
}

typedef struct {
    s16 id;
    u8 unk2;
    u8 pad3;
    s16 unk4;
    u8 pad6[6];
    s32 unkC;
} Ctx_0015A360;

typedef struct {
    u8 pad0[0x3C];
    u16 unk3C;
    u8 pad3E[0x22];
} Work_0015A360;

s32 TaLogic_GetNearCard2(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8,
                  s32 arg9);

/* The summon task for side `nSide`: which hand cards to play and where, into `pInput`; -1 when it plays none. */
s32 TaLogic_Bakura_GetMinimumTask_Summon(s32 wUnit, s32 nSide, s32 pInput) {
    s32 ret;
    s32 kind;
    Ctx_0015A360 *ctx = (Ctx_0015A360 *)pInput;
    Work_0015A360 work;
    s32 res;
    extern s32 TaLogic_GetUnitNum();

    ctx->id = wUnit;
    if (SzDuel_InqHandPhase(nSide) == 0) {
        return -1;
    }
    if (TaLogic_GetUnitNum(nSide, 0) == 5 && TaLogic_GetUnitNum(nSide, 1) == 5) {
        return -1;
    }
    kind = TaLogic018_IsHandPlay(nSide, &work);
    if (kind < 0) {
        return -1;
    }
    ctx->unk2 = 10;
    ctx->unkC = 2;
    wUnit = SzDuel_GetUnitLoc(wUnit >> 8, wUnit & 0xFF);
    if (kind == 0) {
        if (TaLogic018_SetComboQue(nSide, (u8 *)ctx, &work) >= 0) {
            ret = TaLogic_GetNearCard2(&work, wUnit & 0xFF, wUnit >> 8, nSide == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, TaLogic_Bakura_GetWarnHideLvl(nSide));
            if (ret < 0) {
                if (SzDuel_GetUnitMonsterCount(nSide) < 6) {
                    res = TaLogic018_GetSummonPiece(nSide, (u8)kind, &work, ret);
                    if (res < 0) {
                        return -1;
                    }
                    ctx->unk4 = res;
                    return 1;
                }
            } else {
                res = TaLogic018_GetSummonPiece(nSide, (u8)kind, &work, ret);
                if (res < 0) {
                    return -1;
                }
                ctx->unk4 = res;
                return 1;
            }
        }
    } else {
        ret = TaLogic_GetNearCard2(&work, wUnit & 0xFF, wUnit >> 8, nSide == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, TaLogic_Bakura_GetWarnHideLvl(nSide));
    }
    if (kind == 2) {
        TaLogic018_SetSpecialComboQue(nSide, ctx, &work);
        res = TaLogic018_GetSummonPiece(nSide, (u8)kind, &work, ret);
        if (res < 0) {
            return -1;
        }
        ctx->unk4 = res;
        return 1;
    }
    if (TaLogic018_GetSpellPlay(nSide, (u8 *)ctx, &work, work.unk3C) < 0) {
        return -1;
    }
    res = TaLogic018_GetSummonPiece(nSide, (u8)kind, &work, ret);
    if (res < 0) {
        return -1;
    }
    ctx->unk4 = res;
    return 1;
}

/* Whether side `nSide` should play from its hand this turn (and what, into `pInput`). */
s32 TaLogic018_IsHandPlay(s32 nSide, void *pInput) {
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
        s32 result = TaLogic018_GetSpellPlay(nSide, (u8 *)data, pInput, 0x3E7);
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
    if (TaLogic018_GetSpecCardPlay(nSide, data, pInput, 0x343) >= 0 && TaLogic018_IsDoCerem(nSide, 0x343) == 1) {
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
        s32 result = TaLogic018_GetSpellPlay(nSide, (u8 *)data, pInput, 0x3E7);
        if (result >= 0) {
            return result;
        } else {
            return -1;
        }
    }
}

/* Whether side `nSide` holds card `nCardNo` and can summon it (its slot into `bCombo`, the card into `pCardInfo`);
   returns its kind group or -1. */
s32 TaLogic018_GetSpecCardPlay(s32 nSide, void *bCombo, void *pCardInfo, s32 nCardNo) {
    s32 entries[8];
    s32 index;
    s32 *entry;
    s32 key;

    TaHand_GetNextHand(nSide, entries);
    index = 0;
    if (index < TaHand_GetNextHandNum(nSide)) {
        key = nCardNo & 0xFFFF;
        entry = entries;
        do {
            if (key == *entry && TaHand_CanAffordSummonCost(nSide, *entry) == 1) {
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
s32 TaLogic018_GetSpellPlay(s32 nSide, u8 *bCombo, void *pCardInfo, s32 nMode) {
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

extern int func_002493A0_b(int index);
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

/* Fills hand combination `bCombo` for side `nSide`: the best fusion or equip chain, its card into `pCardInfo`. */
int TaLogic018_SetComboQue(int nSide, unsigned char *bCombo, void *pCardInfo)
{
    struct DotrPickBlock * block = pCardInfo;
    int list[8];
    int n;
    int id;
    int i;
    int *p;
    int *q;
    int v;
    int j;

    n = 1;
    if (block == 0) {
        return -1;
    }
    TaHand_GetNextHand(nSide, list);
    id = block->unknown_3c;
    i = 0;
    if (0 < TaHand_GetNextHandNum(nSide)) {
        p = list;
        do {
            if (id == *p && TaHand_GetCardKind(*p) >> 5 == 0) {
                bCombo[6] = i;
            }
            p++;
            i++;
        } while (i < TaHand_GetNextHandNum(nSide));
    }
    j = 0;
    if (0 < TaHand_GetNextHandNum(nSide)) {
        do {
            q = &list[j];
            if (Ta_GetHandEnchant(id, *q) >= 0 && TaHand_GetCardKind(*q) >> 5 == 2 && (v = *q) != 795 && v != 796) {
                if (SzDuel_GetUnitAP2(block, 0) + func_002493A0_b(v) < 1400) {
                    block->unknown_38 += (short)func_002493A0_b(*q);
                    block->unknown_3a += (short)func_002493A0_b(*q);
                    bCombo[n + 6] = j;
                    n++;
                } else {
                    j = TaHand_GetNextHandNum(nSide);
                }
            }
            j++;
        } while (j < TaHand_GetNextHandNum(nSide));
    }
    return 1;
}

typedef struct {
    u8 pad0[6];
    u8 slot[5];
} Obj1_0015AD00;

typedef struct {
    u8 pad0[0x38];
    s16 f38;
    s16 f3A;
    u16 id;
} Obj2_0015AD00;

/* Fills hand combination `bCombo` for side `nSide` with this duelist's special combination, its card into
   `pCardInfo`. */
s32 TaLogic018_SetSpecialComboQue(s32 nSide, void *bCombo, void *pCardInfo) {
    Obj1_0015AD00 *o1 = bCombo;
    Obj2_0015AD00 *o2 = pCardInfo;
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

typedef struct {
    u8 low : 4;
    u8 high : 4;
} Nibbles_0015AF30;

typedef struct {
    u8 pad[0x3E];
    u8 f3E;
} Card_0015AF30;

/* The square side `nSide` summons a card of kind `sKind` to. */
s32 TaLogic018_GetSummonPiece(s32 nSide, s32 sKind, void *pInput, s32 nMode) {
    extern s32 TaLogic_IsUnitWin4();
    extern s32 TaLogic_GetInvadeRoot2(s32, void *, s32, s32, s32, s32, s32, s32, u8, u16);
    extern s32 TaLogic_GetRoot2(s32, void *, s32, s32, s32, s32, u16, u8);
    Card_0015AF30 *card = pInput;
    Nibbles_0015AF30 entries[12];
    s32 id;
    s32 hi;
    s32 lo;
    s32 i;
    Nibbles_0015AF30 *entry;
    s32 pos;
    s32 cost;
    s32 bestId;
    s32 best;
    s32 y;
    s32 x;
    s32 j;
    s32 slot;

    if (card == NULL) {
        return -1;
    }
    entry = entries;
    i = 0;
    do {
        entry->low = entry->high = 15;
        entry++;
        i++;
    } while (i < 12);
    if ((u8)(card->f3E >> 5) == 0 && nMode >= 0) {
        best = 0xFF;
        bestId = 0xFFFF;
        pos = SzDuel_GetUnitLoc(nMode >> 8, nMode & 0xFF);
        for (i = 0; i < 8; i++) {
            id = Ta_GetSommonPiecePreference(nSide, i);
            if (id < 0) {
                continue;
            }
            lo = id & 0xFF;
            hi = id >> 8;
            if (SzDuel_GetField(lo, hi) == 8) {
                continue;
            }
            if (SzDuel_GetField(lo, hi) == 9 && Ta_IsVirus_Chk3(card, lo, hi) == 1) {
                continue;
            }
            if (SzDuel_GetMapUnit(lo, hi) != 0) {
                continue;
            }
            if (TaLogic_IsUnitWin4(card, nMode, TaLogic_Bakura_GetWarnHideLvl(nSide), pos & 0xFF, pos >> 8, 0) > 0) {
                cost = TaLogic_GetInvadeRoot2((s32)card, entries, lo, hi, pos & 0xFF, pos >> 8, nMode, 0, 3,
                                     TaLogic_Bakura_GetWarnHideLvl(nSide));
            } else {
                cost = TaLogic_GetRoot2((s32)card, entries, lo, hi, pos & 0xFF, pos >> 8, nMode, 3);
            }
            if (TaLogic_GetMinGoalCount((u8 *)entries) > 0 && cost < best) {
                best = cost;
                bestId = id;
            }
        }
        if (bestId != 0xFFFF) {
            return bestId;
        }
    }
    for (j = 0; j < 8; j++) {
        slot = Ta_GetSommonPiecePreference(nSide, j);
        if (slot < 0) {
            continue;
        }
        x = slot & 0xFF;
        y = slot >> 8;
        if (SzDuel_GetField(x, y) == 8) {
            continue;
        }
        if (SzDuel_GetField(x, y) == 9 && Ta_IsVirus_Chk3(card, x, y) == 1) {
            continue;
        }
        if (SzDuel_GetMapUnitID(x, y) < 0) {
            return slot;
        }
    }
    return -1;
}

typedef struct Nibbles_0015B250 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_0015B250;

typedef struct Output_0015B250 {
    u16 position;
    u8 action;
    u8 pad3;
    u16 destination;
    u8 pad6[6];
    s32 special;
    u8 result;
} Output_0015B250;

/* The task of a unit running from danger (task `pTask`): the safest square in reach, into `pInput` (`fFirst` = 1
   for the unit's first-choice task). */
s32 TaLogic_Bakura_GetMinimumTask_RunMission(u16 *pTask, s32 nSide, void *pInput, u8 fFirst) {
    Output_0015B250 *output = pInput;
    s32 target;
    u8 endX;
    u8 extra;
    Nibbles_0015B250 nibbles[12];
    s32 bestScore;
    s32 best;
    s32 i;
    Nibbles_0015B250 *p;
    extern s32 TaLogic_Bakura_IsOpenUnit();
    extern s32 TaLogic_IsRunPassRoot(s32, s32, s32, s32, s32, s32, void *, u8);

    target = SzDuel_GetUnitLoc(*pTask >> 8, *pTask & 0xFF);
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

        initialScore = TaLogic_Bakura_GetWarnHideLvl(nSide);
        centerX = target & 0xFF;
        centerY = target >> 8;
        if (TaLogic_GetUnitWarning(centerX, centerY, *pTask, 3, initialScore, 0) == 0) {
            output->position = *pTask;
            output->action = 6;
            output->destination = target;
            output->result = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, output->destination, 1, 0);
            output->special = TaLogic_Bakura_IsOpenUnit(*pTask >> 8, *pTask & 0xFF, pTask);
            TaLogic_InitRogicControl(pTask, fFirst);
            return 0;
        }
        if ((range = GetMoveRange(SzDuel_GetUnit(*pTask >> 8, *pTask & 0xFF), centerX, centerY)) == 0) {
            output->position = *pTask;
            output->action = 6;
            output->destination = target;
            output->result = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, output->destination, 1, 0);
            output->special = TaLogic_Bakura_IsOpenUnit(*pTask >> 8, *pTask & 0xFF, pTask);
            TaLogic_InitRogicControl(pTask, fFirst);
            return 0;
        }
        if (SzDuel_GetUnitStatus(*pTask >> 8, *pTask & 0xFF, 4) != 0) {
            if ((SzDuel_GetUnitKind(*pTask >> 8, *pTask & 0xFF) >> 5) == 1 ||
                (SzDuel_GetUnitKind(*pTask >> 8, *pTask & 0xFF) >> 5) == 5) {
                SzDuel_SetUnitStatus(*pTask >> 8, *pTask & 0xFF, 0, 1);
                output->position = *pTask;
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
        if ((*pTask & 0xFF) == 0) {
            extra = (u8)TaLogic_IsAttackedNow(*pTask >> 8, *pTask & 0xFF, 0);
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
                if (TaLogic_IsRunPassRoot(*pTask >> 8, *pTask & 0xFF, centerX, centerY, x, y, pTask, extra) == 1) {
                    if (TaLogic_IsAttackedNow2(*pTask >> 8, *pTask & 0xFF, x, y, 0) == 0 || (u8)*pTask == 0) {
                        candidateScore = TaLogic_GetUnitWarning(x, y, *pTask, 3, (u16)TaLogic_Bakura_GetWarnHideLvl(nSide), 0);
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
            output->position = *pTask;
            output->action = 6;
            output->destination = best;
            if (best == target) {
                output->result = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, output->destination, 1, 0);
            } else {
                output->result = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, output->destination, 0, 0);
            }
            output->special = TaLogic_Bakura_IsOpenUnit(*pTask >> 8, *pTask & 0xFF, pTask);
        } else {
            output->position = *pTask;
            output->action = 6;
            output->destination = target;
            output->result = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, output->destination, 1, 0);
            output->special = TaLogic_Bakura_IsOpenUnit(*pTask >> 8, *pTask & 0xFF, pTask);
        }
        TaLogic_InitRogicControl(pTask, fFirst);
        return 0;
    }
}

typedef struct Input_0015B820 {
    u16 pos;
    u8 pad2[6];
    u32 target;
} Input_0015B820;

typedef struct Output_0015B820 {
    u16 pos;
    u8 command;
    u8 pad3;
    u16 target;
    u8 pad6[6];
    s32 special;
    u8 result;
} Output_0015B820;

typedef struct Cell_0015B820 {
    u8 x : 4;
    u8 y : 4;
} Cell_0015B820;

/* The task's target square: the second half-word when the second argument is 1, else the first. */
static inline u32 target_0015B820(Input_0015B820 *input, u8 mode) {
    if (mode == 1) {
        return (u16)(input->target >> 16);
    }
    return (u16)input->target;
}

/* The task of a unit attacking (task `pTask`): its path to the goal, into `pInput`; -1 when it has none (`fFirst`
   = 1 for the unit's first-choice task). */
s32 TaLogic_Bakura_GetMinimumTask_AtkMission(void *pTask, s32 nSide, void *pInput, u8 fFirst) {
    extern s32 TaLogic_Bakura_IsOpenUnit();
    extern void TaLogic_GetInvadeRoot();
    s32 source;
    s32 count;
    s32 source_y;
    s32 source_x;
    s32 special;
    u8 mode;
    Cell_0015B820 cells[12];
    s32 target;
    s32 pos;
    s32 target_y;
    s32 target_x;
    Cell_0015B820 *candidate;
    s32 initial_special;
    s32 i;
    s32 best_cost;
    s32 best;
    s32 cost;
    s32 unit;
    s32 init_i;
    u32 target_low;
    u32 target_high;
    Cell_0015B820 *cell;
    Input_0015B820 *input = pTask;
    Output_0015B820 *output = pInput;

    mode = fFirst;
    target_low = target_0015B820(input, fFirst);
    target_high = target_0015B820(input, fFirst);
    if (SzDuel_GetUnit(target_high >> 8, target_low & 0xFF) == 0) {
        TaLogic_InitRogicControl(input, 1);
        return -1;
    }

    initial_special = TaLogic_Bakura_IsOpenUnit(input->pos >> 8, input->pos & 0xFF, input);
    source = SzDuel_GetUnitLoc(input->pos >> 8, input->pos & 0xFF);
    target_low = target_0015B820(input, fFirst);
    target_high = target_0015B820(input, fFirst);
    target = SzDuel_GetUnitLoc(target_high >> 8, target_low & 0xFF);
    cell = cells;
    init_i = 0;
    do {
        init_i++;
        cell->x = cell->y = 0xF;
        cell++;
    } while (init_i < 12);

    unit = SzDuel_GetUnit(input->pos >> 8, input->pos & 0xFF);
    source_x = source & 0xFF;
    source_y = source >> 8;
    if (GetMoveRange(unit, source_x, source_y) == 0) {
        output->pos = input->pos;
        output->command = 6;
        output->target = source;
        cost = TaLogic_GetUnitWarning(source_x, source_y, nSide, 3, 1,
                            (u8)TaLogic_Bakura_GetWarnHideLvl(nSide));
        if (cost >= SzDuel_GetUnitAP(input->pos >> 8, input->pos & 0xFF, 0)) {
            output->result = TaLogic_IsDefStyleUnit(input->pos >> 8, input->pos & 0xFF,
                                         output->target, 1, 0);
        } else {
            output->result = TaLogic_IsDefStyleUnit(input->pos >> 8, input->pos & 0xFF,
                                         output->target, 0, 0);
        }
        TaLogic_InitRogicControl(input, mode);
        return 0;
    } else {
        u16 limit;
        pos = input->pos;
        limit = TaLogic_Bakura_GetWarnHideLvl(nSide);
        TaLogic_GetInvadeRoot(pos >> 8, pos & 0xFF, cells, source_x, source_y,
                     target_x = target & 0xFF, target_y = target >> 8,
                     target_0015B820(input, fFirst), 0, 30, limit);
        count = TaLogic_GetMinGoalCount((u8 *)cells);
        best = 0xFF;
        if (count > 0) {
            special = 0;
            best_cost = 0xFFFF;
            for (i = 0; i < count; i++) {
                if (TaLogic018_IsOpenMoveUnit(input->pos >> 8, input->pos & 0xFF,
                                 source_x, source_y, target_x, target_y) == 1) {
                    Cell_0015B820 *chosen = &cells[i];
                    best = i;
                    special = 1;
                    i = count;
                    chosen->x = target_x;
                    chosen->y = target_y;
                } else {
                    u8 limit;
                    candidate = &cells[i];
                    limit = TaLogic_Bakura_GetWarnHideLvl(nSide);
                    cost = TaLogic_GetUnitWarning(candidate->x, candidate->y, nSide, 3, 1, limit);
                    if (cost < best_cost) {
                        best_cost = cost;
                        best = i;
                    } else if (cost == best_cost) {
                        Cell_0015B820 *chosen = &cells[best];
                        s32 old_y_min;
                        s32 old_y_max;
                        s32 old_x_min;
                        s32 old_x_max;
                        s32 new_y_min;
                        s32 new_y_max;
                        s32 new_x_min;
                        s32 new_x_max;

                        old_y_min = chosen->y < target_y ? chosen->y : target_y;
                        old_y_max = target_y < chosen->y ? chosen->y : target_y;
                        old_x_min = chosen->x < target_x ? chosen->x : target_x;
                        old_x_max = target_x < chosen->x ? chosen->x : target_x;
                        new_y_min = candidate->y < target_y ? candidate->y : target_y;
                        new_y_max = target_y < candidate->y ? candidate->y : target_y;
                        new_x_min = candidate->x < target_x ? candidate->x : target_x;
                        new_x_max = target_x < candidate->x ? candidate->x : target_x;
                        if ((new_x_max - new_x_min) + (new_y_max - new_y_min) <
                            (old_x_max - old_x_min) + (old_y_max - old_y_min)) {
                            best_cost = cost;
                            best = i;
                        }
                    }
                }
            }
        } else {
            output->pos = input->pos;
            output->command = 6;
            output->target = source;
            output->special = initial_special;
            output->result = TaLogic_IsDefStyleUnit(input->pos >> 8, input->pos & 0xFF,
                                         output->target, 0, 0);
            TaLogic_InitRogicControl(input, mode);
            return 0;
        }
        if (best != 0xFF) {
            output->pos = input->pos;
            output->command = 6;
            output->target = (cells[best].y << 8) | cells[best].x;
            output->special = special;
            output->result = TaLogic_IsDefStyleUnit(input->pos >> 8, input->pos & 0xFF,
                                         output->target, 0, 0);
        } else {
            output->pos = input->pos;
            output->command = 6;
            output->target = source;
            output->special = special;
            output->result = TaLogic_IsDefStyleUnit(input->pos >> 8, input->pos & 0xFF,
                                         output->target, 0, 0);
            TaLogic_InitRogicControl(input, mode);
            return 0;
        }
    }
    return 0;
}

typedef struct Coord_0015BE00 {
    u8 x : 4;
    u8 y : 4;
} Coord_0015BE00;

typedef struct Unit_0015BE00 {
    u16 position;
    u8 pad2[6];
    union {
        u32 packed;
        u16 low;
    } target;
} Unit_0015BE00;

typedef struct Output_0015BE00 {
    u16 position;
    u8 kind;
    u8 pad3;
    u16 target;
    u8 pad6[6];
    s32 value;
    u8 flag;
} Output_0015BE00;

/* The task's target square: the second half-word when the second argument is 1, else the first. */
static inline u32 target_0015BE00(void *unit, s32 side) {
    return side == 1 ? (u32)(u16)(((Unit_0015BE00 *)unit)->target.packed >> 16) : (u32)((Unit_0015BE00 *)unit)->target.low;
}

/* The smaller of the two values. */
static inline u32 minY_0015BE00(void *unit, s32 side, u8 coord) {
    return coord < (target_0015BE00(unit, side) >> 8) ? coord : (target_0015BE00(unit, side) >> 8);
}

/* The larger of the two values. */
static inline u32 maxY_0015BE00(void *unit, s32 side, u8 coord) {
    return (target_0015BE00(unit, side) >> 8) < coord ? coord : (target_0015BE00(unit, side) >> 8);
}

/* The smaller of the two values. */
static inline u32 minX_0015BE00(void *unit, s32 side, u8 coord) {
    return coord < (target_0015BE00(unit, side) & 0xFF) ? coord : (target_0015BE00(unit, side) & 0xFF);
}

/* The larger of the two values. */
static inline u32 maxX_0015BE00(void *unit, s32 side, u8 coord) {
    return (target_0015BE00(unit, side) & 0xFF) < coord ? coord : (target_0015BE00(unit, side) & 0xFF);
}

/* The task of a unit moving to its goal (task `pTask`), into `pInput` (`fFirst` = 1 for the unit's first-choice
   task). */
s32 TaLogic_Bakura_GetMinimumTask_MoveMission(void *pTask, s32 nSide, void *pInput, u8 fFirst, u8 nKind) {
    extern s32 TaLogic_Bakura_IsOpenUnit();
    extern s32 TaLogic_GetUnitWarning();
    extern void TaLogic_GetRoot();
    extern s32 TaLogic_IsDefStyleUnit(s32, s32, s32, u8, s32);
    Coord_0015BE00 coords[12];
    s32 initial;
    s32 cell;
    s32 count;

    initial = SzDuel_GetUnitLoc(((Unit_0015BE00 *)pTask)->position >> 8, ((Unit_0015BE00 *)pTask)->position & 0xFF);
    {
    s32 bestScore;
    s32 best;
    s32 side = fFirst;
    Coord_0015BE00 *candidate;
    s32 index;
    if (target_0015BE00(pTask, side) == 0xFFFF) {
        if (initial == target_0015BE00(pTask, side)) {
            ((Output_0015BE00 *)pInput)->position = ((Unit_0015BE00 *)pTask)->position;
            ((Output_0015BE00 *)pInput)->kind = 6;
            ((Output_0015BE00 *)pInput)->target = initial;
            ((Output_0015BE00 *)pInput)->flag = TaLogic_IsDefStyleUnit(((Unit_0015BE00 *)pTask)->position >> 8, ((Unit_0015BE00 *)pTask)->position & 0xFF, ((Output_0015BE00 *)pInput)->target, nKind, 0);
            ((Output_0015BE00 *)pInput)->value = TaLogic_Bakura_IsOpenUnit(((Unit_0015BE00 *)pTask)->position >> 8, ((Unit_0015BE00 *)pTask)->position & 0xFF, pTask);
            TaLogic_InitRogicControl(pTask, fFirst);
            return 0;
        }
    }

    if (SzDuel_GetUnitStatus(((Unit_0015BE00 *)pTask)->position >> 8,
                      ((Unit_0015BE00 *)pTask)->position & 0xFF, 4) != 0) {
        if ((SzDuel_GetUnitKind(((Unit_0015BE00 *)pTask)->position >> 8,
                          ((Unit_0015BE00 *)pTask)->position & 0xFF) >> 5) == 1 ||
            (SzDuel_GetUnitKind(((Unit_0015BE00 *)pTask)->position >> 8,
                          ((Unit_0015BE00 *)pTask)->position & 0xFF) >> 5) == 5) {
            SzDuel_SetUnitStatus(((Unit_0015BE00 *)pTask)->position >> 8,
                          ((Unit_0015BE00 *)pTask)->position & 0xFF, 0, 1);
            ((Output_0015BE00 *)pInput)->position = ((Unit_0015BE00 *)pTask)->position;
            ((Output_0015BE00 *)pInput)->kind = 0xE;
            return 0;
        }
    }

    candidate = coords;
    {
        s32 i = 0;
        Coord_0015BE00 *entry = candidate;
        do {
            entry->x = entry->y = 0xF;
            i++;
            entry++;
        } while (i < 12);
    }

    cell = SzDuel_GetMapUnitID(target_0015BE00(pTask, side) & 0xFF, ((u32)target_0015BE00(pTask, side)) >> 8);
    if (cell < 0) {
        cell = 0xFFFF;
    }
    TaLogic_GetRoot(((Unit_0015BE00 *)pTask)->position >> 8, ((Unit_0015BE00 *)pTask)->position & 0xFF,
                 coords, initial & 0xFF, initial >> 8, target_0015BE00(pTask, side) & 0xFF,
                 ((u32)target_0015BE00(pTask, side)) >> 8, (u16)cell, 7);
    count = TaLogic_GetMinGoalCount((u8 *)coords);
    {
        if (count > 0) {
        best = 0xFF;
        bestScore = 0xFFFF;
        for (index = 0; index < count; index++) {
                if (SzDuel_GetMapUnit(candidate->x, candidate->y) == 0) {
                    s32 score = TaLogic_GetUnitWarning(candidate->x, candidate->y, nSide, 3, 1, (u8)TaLogic_Bakura_GetWarnHideLvl(nSide));
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
                        bestMinY = minY_0015BE00(pTask, side, bestY);
                        bestMaxY = maxY_0015BE00(pTask, side, bestY);
                        bestX = (&coords[best])->x;
                        bestMinX = minX_0015BE00(pTask, side, bestX);
                        bestMaxX = maxX_0015BE00(pTask, side, bestX);
                        currentY = (u8)candidate->y;
                        currentMinY = minY_0015BE00(pTask, side, currentY);
                        currentMaxY = maxY_0015BE00(pTask, side, currentY);
                        currentX = candidate->x;
                        currentMinX = minX_0015BE00(pTask, side, currentX);
                        currentMaxX = maxX_0015BE00(pTask, side, currentX);
                        if ((currentMaxX - currentMinX) + (currentMaxY - currentMinY) < (bestMaxX - bestMinX) + (bestMaxY - bestMinY)) {
                            bestScore = score;
                            best = index;
                        }
                    }
                }
            candidate++;
        }
    } else {
        ((Output_0015BE00 *)pInput)->position = ((Unit_0015BE00 *)pTask)->position;
            ((Output_0015BE00 *)pInput)->kind = 6;
            ((Output_0015BE00 *)pInput)->target = initial;
            ((Output_0015BE00 *)pInput)->flag = TaLogic_IsDefStyleUnit(((Unit_0015BE00 *)pTask)->position >> 8, ((Unit_0015BE00 *)pTask)->position & 0xFF, ((Output_0015BE00 *)pInput)->target, nKind, 0);
            ((Output_0015BE00 *)pInput)->value = TaLogic_Bakura_IsOpenUnit(((Unit_0015BE00 *)pTask)->position >> 8, ((Unit_0015BE00 *)pTask)->position & 0xFF, pTask);
        TaLogic_InitRogicControl(pTask, fFirst);
        return 0;
    }

        if (best != 0xFF) {
            ((Output_0015BE00 *)pInput)->position = ((Unit_0015BE00 *)pTask)->position;
            ((Output_0015BE00 *)pInput)->kind = 6;
            ((Output_0015BE00 *)pInput)->target = (coords[best].y << 8) | coords[best].x;
            ((Output_0015BE00 *)pInput)->flag = TaLogic_IsDefStyleUnit(((Unit_0015BE00 *)pTask)->position >> 8, ((Unit_0015BE00 *)pTask)->position & 0xFF, ((Output_0015BE00 *)pInput)->target, nKind, 0);
            ((Output_0015BE00 *)pInput)->value = TaLogic_Bakura_IsOpenUnit(((Unit_0015BE00 *)pTask)->position >> 8, ((Unit_0015BE00 *)pTask)->position & 0xFF, pTask);
        } else {
            ((Output_0015BE00 *)pInput)->position = ((Unit_0015BE00 *)pTask)->position;
            ((Output_0015BE00 *)pInput)->kind = 6;
            ((Output_0015BE00 *)pInput)->target = initial;
            ((Output_0015BE00 *)pInput)->flag = TaLogic_IsDefStyleUnit(((Unit_0015BE00 *)pTask)->position >> 8, ((Unit_0015BE00 *)pTask)->position & 0xFF, ((Output_0015BE00 *)pInput)->target, nKind, 0);
            ((Output_0015BE00 *)pInput)->value = TaLogic_Bakura_IsOpenUnit(((Unit_0015BE00 *)pTask)->position >> 8, ((Unit_0015BE00 *)pTask)->position & 0xFF, pTask);
        }
        TaLogic_InitRogicControl(pTask, fFirst);
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
} Source_0015C670;

typedef struct {
    u16 position;
    u8 action;
    u8 pad3;
    u16 target;
    u8 pad6[10];
    s8 result;
} Action_0015C670;

typedef struct {
    u8 x : 4;
    u8 y : 4;
} Point_0015C670;

#define MIN_0015C670(a, b) ((a) < (b) ? (a) : (b))
#define MAX_0015C670(a, b) ((b) < (a) ? (a) : (b))

/* The task's target square: the second half-word when the second argument is 1, else the first. */
static inline u32 target_0015C670(void *arg0, s32 mode) {
    Source_0015C670 *source = arg0;
    if (mode == 1) {
        return (u16)(source->target.both >> 16);
    }
    return source->target.half[0];
}

/* Sets a move task (action 6) to the given square, and whether the unit should stay in defence there. */
static inline void fill_0015C670(void *arg0, void *arg2, s32 target, s32 flag) {
    Source_0015C670 *source = arg0;
    Action_0015C670 *action = arg2;
    action->position = source->position;
    action->action = 6;
    action->target = target;
    action->result = TaLogic_IsDefStyleUnit(source->position >> 8,
        source->position & 0xFF, action->target, flag, 0);
}

/* The task of setting a trap (task `pTask`), into `pInput`. */
s32 TaLogic_Bakura_GetMinimumTask_TrapMission(void *pTask, s32 nSide, void *pInput, s32 fFirst) {
    s32 start;
    s32 count;
    s32 startY;
    Point_0015C670 points[16];
    s32 bestScore;
    Point_0015C670 *p;
    s32 targetY;
    s32 targetX;
    s32 i;
    s32 bestIndex;
    s32 mode;
    s32 target;
    s32 startX;
    u32 xPosition;
    u32 yPosition;
    Source_0015C670 *source = pTask;
    Action_0015C670 *action = pInput;
    extern void TaLogic_GetInvadeRoot();

    mode = fFirst & 0xFF;
    xPosition = target_0015C670(pTask, mode);
    yPosition = target_0015C670(pTask, mode);
    if (SzDuel_GetUnit(yPosition >> 8, xPosition & 0xFF) == 0) {
        TaLogic_InitRogicControl(pTask, 1);
        return -1;
    }
    start = SzDuel_GetUnitLoc(source->position >> 8, source->position & 0xFF);
    xPosition = target_0015C670(pTask, mode);
    yPosition = target_0015C670(pTask, mode);
    target = SzDuel_GetUnitLoc(yPosition >> 8, xPosition & 0xFF);
    if (target_0015C670(pTask, mode) == 0xFFFF) {
        fill_0015C670(pTask, pInput, start, 1);
        return 0;
    } else {
        s32 unit = SzDuel_GetUnit(source->position >> 8, source->position & 0xFF);
        startX = start & 0xFF;
        startY = start >> 8;
        if (GetMoveRange(unit, startX, startY) == 0 ||
                TaLogic_IsAttackedNow(source->position >> 8, source->position & 0xFF, 0) == 1) {
            fill_0015C670(pTask, pInput, start, 1);
            return 0;
        } else {
            p = points;
            {
                s32 n = 0;
                Point_0015C670 *q = p;
                do {
                    q->x = q->y = 0xF;
                    q++;
                    n++;
                } while (n < 12);
            }
            {
                s32 position = source->position;
                u16 card = (u16)TaLogic_Bakura_GetWarnHideLvl(nSide);
                TaLogic_GetInvadeRoot(position >> 8, position & 0xFF, points,
                    startX, startY, targetX = target & 0xFF,
                    targetY = target >> 8, target_0015C670(pTask, mode),
                    0, 30, card);
            }
            count = TaLogic_GetMinGoalCount((u8 *)points);
            bestIndex = 0xFF;
            if (count > 0) {
                bestScore = 0;
                for (i = 0; i < count; i++, p++) {
                    if (SzDuel_GetMapUnit(p->x, p->y) == 0) {
                        s32 score = TaLogic_GetUnitWarning(p->x, p->y, nSide, 3, 1,
                            TaLogic_Bakura_GetWarnHideLvl(nSide) & 0xFF);
                        if (bestScore < score) {
                            bestScore = score;
                            bestIndex = i;
                        } else if (score == bestScore) {
                            if (MAX_0015C670(p->x, targetX) - MIN_0015C670(p->x, targetX)
                                    + (MAX_0015C670(p->y, targetY) - MIN_0015C670(p->y, targetY))
                                    < MAX_0015C670(points[bestIndex].x, targetX) - MIN_0015C670(points[bestIndex].x, targetX)
                                    + (MAX_0015C670(points[bestIndex].y, targetY) - MIN_0015C670(points[bestIndex].y, targetY))) {
                                bestScore = score;
                                bestIndex = i;
                            }
                        }
                    }
                }
            } else {
                fill_0015C670(pTask, pInput, start, 1);
                return 0;
            }
            if (bestIndex != 0xFF) {
                action->position = source->position;
                action->action = 6;
                action->target = (points[bestIndex].y << 8) | points[bestIndex].x;
                action->result = TaLogic_IsDefStyleUnit(source->position >> 8,
                    source->position & 0xFF, action->target, 0, 0);
            } else {
                fill_0015C670(pTask, pInput, start, 1);
                return 0;
            }
        }
    }
    return 0;
}

/* Whether this duelist opens (turns face up) unit (nSide, nID) now: 0 no, 1 or 2 by its kind. */
s32 TaLogic_Bakura_IsOpenUnit(s32 nSide, s32 nID) {
    s32 kind;
    s32 pos;
    s32 slot;
    u32 *card;

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
        case 0xE0:
            if (SzDuel_GetSummonPower(slot) < 2) {
                return 1;
            }
            break;
        case 0x28C:
            if (Ta_GetUnitNumFrom22bitFlagList(SearchUnitByRange(pos & 0xFF, pos >> 8, slot, 1, 0x34, 0x14)) > 1) {
                return 2;
            }
            if (Ta_GetUnitNumFrom22bitFlagList(SearchUnitByRange(pos & 0xFF, pos >> 8, slot, 2, 0x34, 0x14)) > 5) {
                return 1;
            }
            break;
        case 0x28F:
            if (Ta_GetUnitNumFrom22bitFlagList(SearchUnitByRange(0, 0, nSide, 2, 0x34, 0xE)) > 5) {
                return 1;
            }
            break;
        }
        return 2;
    case 5:
        if (TaLogic_GetActionReaction(nSide, nID, 0, 0, 6, 0) == 5) {
            return 2;
        }
        if (TaLogic018_IsDoCerem(Ta_IsUnitControl(nSide, nID), kind) == 1 &&
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
        case 0x18:
            if (Ta_GetUnitNumFrom22bitFlagList(SearchUnitByRange(0, 0, nSide, 2, 0x34, 0xE)) > 5) {
                return 1;
            }
            break;
        case 0x12:
            if (Ta_GetUnitNumFrom22bitFlagList(SearchUnitByRange(pos & 0xFF, pos >> 8, slot, 1, 0x1D, 0x1D)) > 0) {
                return 2;
            }
            if (Ta_GetUnitNumFrom22bitFlagList(SearchUnitByRange(0, 0, slot, 1, 0x13, 0xE)) > 2) {
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

/* Whether unit (nSide, nID) may open while moving from (nX, nZ) to the square next to it, (gX, gZ). */
s32 TaLogic018_IsOpenMoveUnit(s32 nSide, s32 nID, s32 nX, s32 nZ, s32 gX, s32 gZ) {
    s32 minY;
    s32 minX;

    minY = (nZ < gZ) ? nZ : gZ;
    gZ = Max(gZ, nZ);
    minX = (nX < gX) ? nX : gX;
    gX = Max(gX, nX);

    if (((gX - minX) + (gZ - minY)) != 2) {
        return 0;
    }
    if (SzDuel_GetUnit(nSide, nID) == 0) {
        return 0;
    }
    if (SzDuel_GetUnitStatus(nSide, nID, 0) == 0) {
        return (CheckLandAgreement2(SzDuel_GetField(nX, nZ), nSide, nID) != 1) ? 0 : 1;
    }
    return 0;
}

/* Whether side `nSide` can play ritual card `nCardNo` now (it has the units to give up). */
s32 TaLogic018_IsDoCerem(s32 nSide, s32 nCardNo) {
    s32 data[4];
    s32 index;
    s32 mask;
    s32 low;
    s32 high;
    s32 value;

    Ta_GetCeremSacrifice(data, *(s32 *)((u8 *)TaHand_GetCardEffect(nCardNo, 0) + 4));
    if ((mask = Ta_GetSacrificeUnit(data, nSide)) < 0) {
        return 0;
    }
    for (index = 0; index < Ta_GetUnitNumFrom22bitFlagList(mask); index++) {
        value = Ta_GetUnitOwnerIDFromLstCount(mask, index);
        high = value >> 8;
        low = value & 0xFF;
        value = SzDuel_GetUnitLoc(high, low);
        if (TaUtil_GetUnitAP(high, low, value & 0xFF, value >> 8) >= 0) {
            return 0;
        }
    }
    return 1;
}

/* How careful this duelist is about hidden cards (by its life points and monster count). */
s32 TaLogic_Bakura_GetWarnHideLvl(s32 nSide) {
    if (SzDuel_GetLP(nSide) > 0x4B0) {
        if (SzDuel_GetUnitMonsterCount(nSide) >= 5) {
            return 0x2EE;
        } else {
            return 0x5DC;
        }
    } else {
        return 0x7D0;
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
} Req_0015D180;

typedef struct {
    u8 pad0[0x160];
    u16 list[32];    /* 0x160 */
    u8 idx : 5;      /* 0x1A0 */
    u8 pad1A0 : 3;
    u8 pad1A1;
    u16 count;       /* 0x1A2 */
} Work_0015D180;

s32 TaLogic_GetInputQueFromMinimumTask_b(void *, void *, s32);

/* Computer duelist 18's controller (duelistControllers[18]): the buttons it presses this frame. With an empty
   input queue it plans its next task and turns it into buttons, then plays the queue back one button per frame;
   after 600 frames it gives up the turn (0x20, then 0x800). */
s32 duelistController18(s32 wCursorPos, void *pCtl) {
    Req_0015D180 req;
    Work_0015D180 *w;
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
        if (TaLogic_Bakura_GetMinimumTask(w, &req, wCursorPos) == 0) {
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

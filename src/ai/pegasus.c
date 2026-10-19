/* Computer AI of Pegasus Crawford (duelist 9, duelistController09). */

#include "common.h"
#pragma conditional_move off

/* This duelist's move: picks the next unit to act, gives it a task and turns that into input `pInput`; returns 1
   when it set one. */
s32 TaLogic_Pegasus_GetMinimumTask(void *pCtl, void *pInput, s32 wCursorPos) {
    UnitTask *tasks = pCtl;
    s32 side;
    s32 found;
    s32 result;
    s32 index;

    side = SzDuel_GetTurnOwner();
    found = 0;
    if ((result = TaLogic_Pegasus_GetNextActiveUnit(tasks, side, (s32)pInput)) < 0) {
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
    TaLogic_Pegasus_CommandUnit(&tasks[index]);
    switch ((tasks[index].mission >> 8) & 0xFF) {
    case TASK_RUN:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            TaLogic_Pegasus_GetMinimumTask_RunMission(&tasks[index], side, pInput, 1);
            found = 1;
        }
        break;
    case TASK_ATTACK:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            if (TaLogic_Pegasus_GetMinimumTask_AtkMission(&tasks[index], side, pInput, 1) < 0) {
                TaLogic_InitRogicControl(&tasks[index], 1);
                return 1;
            }
            found = 1;
        }
        break;
    case TASK_SUMMON:
        if (TaLogic_Pegasus_GetMinimumTask_Summon(tasks[index].ownerId, side, (s32)pInput) < 0) {
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
            TaLogic_Pegasus_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 1, 0);
            found = 1;
        }
        break;
    case TASK_CONFIRMUNIT:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            TaLogic_Pegasus_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 1, 1);
            found = 1;
        }
        break;
    case TASK_ENCHANT:
        TaLogic_GetMinimumTask_EncMission(&tasks[index], side, pInput, 1, 1, 0, 2, 1);
        found = 1;
        break;
    case TASK_REVIVE:
        TaLogic_Pegasus_GetMinimumTask_ReviveMission(&tasks[index], side, pInput, 1);
        found = 1;
        break;
    case TASK_REVOLT:
        TaLogic_Pegasus_GetMinimumTask_RevoltMission(&tasks[index], side, pInput, 1);
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
            TaLogic_Pegasus_GetMinimumTask_RunMission(&tasks[index], side, pInput, 0);
            found = 1;
        }
        break;
    case 2:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            if (TaLogic_Pegasus_GetMinimumTask_AtkMission(&tasks[index], side, pInput, 0) < 0) {
                TaLogic_Pegasus_GetMinimumTask_RunMission(&tasks[index], side, pInput, 0);
            }
            found = 1;
        }
        break;
    case 10:
        if (TaLogic_Pegasus_GetMinimumTask_Summon(tasks[index].ownerId, side, (s32)pInput) < 0) {
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
            TaLogic_Pegasus_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 0, 0);
            found = 1;
        }
        break;
    case 3:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            TaLogic_Pegasus_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 0, 1);
            found = 1;
        }
        break;
    case 9:
        TaLogic_GetMinimumTask_EncMission(&tasks[index], side, pInput, 0, 1, 0, 2, 1);
        found = 1;
        break;
    case 12:
        TaLogic_Pegasus_GetMinimumTask_ReviveMission(&tasks[index], side, pInput, 0);
        found = 1;
        break;
    case 13:
        TaLogic_Pegasus_GetMinimumTask_RevoltMission(&tasks[index], side, pInput, 0);
        found = 1;
        break;
    case 14:
        TaLogic_GetMinimumTask_DoNone(&tasks[index], side, pInput);
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

typedef struct {
    u16 pos;
    u16 unk2;
    u16 unk4;
    u16 unk6;
    s32 unk8;
} Unit_00135790;
#pragma conditional_move reset

/* Gives a unit of this duelist its order for this turn (attack, run, move, summon, guard). */
s32 TaLogic_Pegasus_CommandUnit(void *pCtl) {
    extern s32 SzDuel_GetUnitCardNo();
    Unit_00135790 *unit = pCtl;

    Ta_IsUnitControl(unit->pos >> 8, unit->pos & 0xFF);
    if (SzDuel_GetUnit(unit->pos >> 8, unit->pos & 0xFF) != 0 &&
        SzDuel_GetUnitStatus(unit->pos >> 8, unit->pos & 0xFF, 0) == 0 && unit->pos != 0xFFFF) {
        if ((unit->pos & 0xFF) == 0) {
            if (unit->unk8 == -1) {
                if (TaLogic_IsAttackedNow(unit->pos >> 8, unit->pos & 0xFF, 1) == 1) {
                    if (SzDuel_InqHandPhase(unit->pos >> 8) == 1) {
                        unit->unk4 = 0x50A;
                    } else {
                        unit->unk4 = 0x5FF;
                    }
                } else {
                    if (SzDuel_InqHandPhase(unit->pos >> 8) == 1) {
                        unit->unk4 = 0xA05;
                    } else {
                        unit->unk4 = 0x5FF;
                    }
                }
            }
        } else {
            switch (SzDuel_GetUnitKind(unit->pos >> 8, unit->pos & 0xFF) >> 5) {
            case 0:
                if (SzDuel_GetUnitCardNo(unit->pos >> 8, unit->pos & 0xFF) == 0xBD) {
                    TaLogic009_CommandDefenseUnit(unit);
                } else {
                    TaLogic009_CommandBtlUnit(unit, 1);
                }
                break;
            case 2:
                TaLogic_CommandEncUnit(unit, 2, 1, 0);
                break;
            case 1:
                TaLogic009_CommandSpellUnit(unit);
                break;
            case 3:
                TaLogic009_CommandDefenseUnit(unit);
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
s32 TaLogic_Pegasus_GetNextActiveUnit(u16 *pCtl, s32 nSide, s32 pInput) {
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
    TaLogic_Pegasus_CommandUnit(pCtl + idx * 8);
    if (((pCtl[idx * 8 + 2] >> 8) & 0xFF) == 10) {
        if (SzDuel_InqHandPhase(nSide) == 1 && TaLogic_Pegasus_GetMinimumTask_Summon(pos, nSide, pInput) >= 0) {
            return pos | 0x10000;
        }
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_GetUnitStatus(nSide, 0, 0) == 0) {
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_InqHandPhase(nSide) == 1 && TaLogic_Pegasus_GetMinimumTask_Summon(pos, nSide, pInput) >= 0) {
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

typedef union {
    u32 word;
    struct {
        u16 low;
        u16 high;
    } halves;
} Data_00135D50;

typedef struct {
    u16 unitId; /* (side << 8) | unit */
    u16 unk2;
    s16 state;
    u16 unk6;
    Data_00135D50 data;
} Entry_00135D50;

typedef struct {
    u16 card;
    u8 flag;
    u8 pad;
} Slot_00135D50;

/* Orders a fighting unit (task `pTask`): straight at the enemy leader when `fGoalFirst` and the path is open,
   else at the nearest enemy it can beat. */
void TaLogic009_CommandBtlUnit(void *pTask, s32 fGoalFirst) {
    extern void TaLogic_InitIgnoreLst();
    extern s32 TaLogic_IsRootOpen();
    extern s32 TaLogic009_GetNearUnit();
    Entry_00135D50 *entry = pTask;
    s32 pos;
    s32 otherPos;
    s32 other;
    s32 player;
    s32 i;
    u8 work[0x70];
    Slot_00135D50 list[22];
    s16 countA;
    s16 countB;
    Slot_00135D50 *slot;

    if (SzDuel_GetUnit(entry->unitId >> 8, entry->unitId & 0xFF) != 0) {
        other = (Ta_GetCurrentSide(entry->unitId >> 8, entry->unitId & 0xFF) == 0 ? 1 : 0) << 8;
        pos = SzDuel_GetUnitLoc(entry->unitId >> 8, entry->unitId & 0xFF);
        otherPos = SzDuel_GetUnitLoc(other >> 8, other & 0xFF);
        player = SzDuel_GetUnit(entry->unitId >> 8, entry->unitId & 0xFF);
        slot = list;
        i = 0;
        do {
            i++;
            slot->card = 0xFFFF;
            slot->flag = 0xFF;
            slot++;
        } while (i < 22);
        TaLogic_InitIgnoreLst(work);
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
            switch (TaLogic009_GetNearUnit(entry, 0, player, pos & 0xFF, pos >> 8,
                                  Ta_GetCurrentSide(entry->unitId >> 8, entry->unitId & 0xFF) == 0 ? 1 : 0,
                                  i & 0xFF, 0, list, 0, &countA, &countB, 2, work)) {
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
            if (i > 2) {
                break;
            }
        }
        entry->state = 0x5FF;
        return;
    }
}

/* TaLogic_GetNearUnit with this duelist's view and strength settings. */
void TaLogic009_GetNearUnit(s32 pTask, s32 pTree, s32 pVarInfo, s32 nX, s32 nZ, s32 eSide, s32 bDist, s32 WarnLvl, s32 nUnitLst, u16 wUnitNum, s32 wSize, s32 wNodeCount, u8 bChase, s32 wIgnoreLst) {
    TaLogic_GetNearUnit(pTask, pTree, pVarInfo, nX, nZ, eSide, bDist, WarnLvl,
                  nUnitLst, wUnitNum, wSize, wNodeCount, bChase,
                  1, 0x898, wIgnoreLst);
}

/* Orders a unit (task `pTask`) to guard its leader. */
void TaLogic009_CommandDefenseUnit(void *pTask) {
    s32 emptyDefensePoint;

    emptyDefensePoint = TaLogic009_GetEmptyDefensePoint(pTask);
    if (emptyDefensePoint >= 0) {
        *(s16 *)((u8 *)pTask + 4) = 0x3FF;
        *(u32 *)((u8 *)pTask + 8) = (emptyDefensePoint << 16) | *(u16 *)((u8 *)pTask + 8);
        return;
    }
    *(s16 *)((u8 *)pTask + 4) = 0x5FF;
}

/* The free defence square (2, 2) or (5, 2), or -1. */
s32 TaLogic009_GetEmptyDefensePoint(void *arg0) {
    if (SzDuel_GetMapUnit(2, 2) == 0 && SzDuel_GetField(2, 2) != 8) {
        return 0x202;
    }
    if (SzDuel_GetMapUnit(5, 2) == 0 && SzDuel_GetField(5, 2) != 8) {
        return 0x205;
    }
    return -1;
}

typedef union {
    u32 word;
    struct {
        u16 low;
        u16 high;
    } halves;
} Data_001360E0;

typedef struct {
    u16 unitId; /* (side << 8) | unit */
    u16 unk2;
    s16 state;
    u16 unk6;
    Data_001360E0 data;
} Entry_001360E0;

/* Orders a face-down magic card (task `pTask`): whether and where to open it. */
void TaLogic009_CommandSpellUnit(void *pTask) {
    extern s32 SzDuel_GetUnitCardNo();
    Entry_001360E0 *entry = pTask;
    s32 pos;
    s32 ret;

    Ta_IsUnitControl(entry->unitId >> 8, entry->unitId & 0xFF);
    pos = SzDuel_GetUnitLoc(entry->unitId >> 8, entry->unitId & 0xFF);
    switch (SzDuel_GetUnitCardNo(entry->unitId >> 8, entry->unitId & 0xFF)) {
    case 0x2B7:
        ret = TaLogic_GetLandChange(SzDuel_GetUnit(entry->unitId >> 8, entry->unitId & 0xFF),
                            pos & 0xFF, pos >> 8, 6, 5, 2);
        if (ret >= 0 && (ret >> 8) < 4) {
            entry->state = 0x6FF;
            entry->data.word = (ret << 16) | entry->data.halves.low;
            return;
        }
        break;
    case 0x2AF:
        entry->state = 0xCFF;
        entry->data.word = entry->data.halves.low | 0xFFFF0000;
        return;
    case 0x2DC:
        entry->state = 0xDFF;
        entry->data.word = entry->data.halves.low | 0xFFFF0000;
        return;
    }
    entry->state = 0x5FF;
}

typedef struct {
    u8 data[0x3C];
    u16 unk3C;
    u8 pad3E[0x22];
} Work_00136210;

typedef struct {
    s16 id;
    u8 kind;
    u8 pad3;
    s16 value;
    u8 pad6[6];
    s32 unkC;
} Ctx_00136210;

/* The summon task for side `nSide`: which hand cards to play and where, into `pInput`; -1 when it plays none. */
s32 TaLogic_Pegasus_GetMinimumTask_Summon(s32 wUnit, s32 nSide, s32 pInput) {
    extern s32 TaLogic_GetUnitNum();
    Work_00136210 work;
    s32 ret;
    s32 res;
    s32 pos;
    s32 kind;
    Ctx_00136210 *ctx = (Ctx_00136210 *)pInput;

    ctx->id = wUnit;
    if (SzDuel_InqHandPhase(nSide) == 0) {
        return -1;
    }
    if (TaLogic_GetUnitNum(nSide, 0) == 5 && TaLogic_GetUnitNum(nSide, 1) == 5) {
        return -1;
    }
    kind = TaLogic009_IsHandPlay(nSide, &work);
    if (kind < 0) {
        return -1;
    }
    ctx->kind = 10;
    ctx->unkC = 0;
    pos = SzDuel_GetUnitLoc(wUnit >> 8, wUnit & 0xFF);
    if (kind == 0) {
        if (TaLogic009_SetComboQue(nSide, ctx, &work) >= 0) {
            ret = TaLogic_GetNearCard2(&work, pos & 0xFF, pos >> 8,
                                nSide == 0 ? 1 : 0, 3, 0x1F, 2, 2, 1, 0);
            if (ret < 0) {
                if (SzDuel_GetUnitMonsterCount(nSide) < 4) {
                    res = TaLogic009_GetSummonPiece(nSide, kind & 0xFF, &work, ret);
                    if (res < 0) {
                        return -1;
                    }
                    ctx->value = res;
                    return 1;
                }
            } else {
                res = TaLogic009_GetSummonPiece(nSide, kind & 0xFF, &work, ret);
                if (res < 0) {
                    return -1;
                }
                ctx->value = res;
                return 1;
            }
        }
    } else {
        ret = TaLogic_GetNearCard2(&work, pos & 0xFF, pos >> 8,
                            nSide == 0 ? 1 : 0, 3, 0x1F, 2, 2, 1, 0);
    }
    if (kind == 2) {
        TaLogic009_SetSpecialComboQue(nSide, ctx, &work);
        res = TaLogic009_GetSummonPiece(nSide, kind & 0xFF, &work, ret);
        if (res < 0) {
            return -1;
        }
        ctx->value = res;
        return 1;
    }
    if (TaLogic009_GetSpellPlay(nSide, (u8 *)ctx, &work, work.unk3C) < 0) {
        return -1;
    }
    res = TaLogic009_GetSummonPiece(nSide, kind & 0xFF, &work, ret);
    if (res < 0) {
        return -1;
    }
    ctx->value = res;
    return 1;
}

/* Whether side `nSide` should play from its hand this turn (and what, into `pInput`). */
s32 TaLogic009_IsHandPlay(s32 nSide, void *pInput) {
    s32 cards[8];
    u8 scratch[32];
    u8 first;
    u8 second;
    s32 i;
    s32 *p;
    s32 *p2;
    s32 i2;
    s32 *p3;
    s32 i3;
    s32 value;
    s32 result;
    extern s32 TaLogic_GetUnitNum();

    first = TaLogic_GetUnitNum(nSide, 0);
    second = TaLogic_GetUnitNum(nSide, 1);
    if (pInput == NULL) {
        return -1;
    }
    TaHand_GetNextHand(nSide, cards);
    if (first == 5) {
        if (TaLogic009_GetSpellPlay(nSide, scratch, pInput, 999) >= 0) {
            return 1;
        } else {
            return -1;
        }
    }
    if (second == 5) {
        for (i = 0; i < TaHand_GetNextHandNum(nSide); i++) {
            p = &cards[i];
            if ((TaHand_GetCardKind(*p) >> 5) == 0 && TaHand_CanAffordSummonCost(nSide, *p) == 1) {
                SzDuel_InitCardInfo(pInput, cards[i]);
                return 0;
            }
        }
        return -1;
    }
    if (TaLogic009_GetSpecCardPlay(nSide, scratch, pInput, 0x33E) >= 0) {
        if (TaLogic009_IsDoCerem(nSide, 0x33E) == 1) {
            return 2;
        }
    }
    if (TaLogic009_GetSpecCardPlay(nSide, scratch, pInput, 0x351) >= 0) {
        if (TaLogic009_IsDoCerem(nSide, 0x351) == 1) {
            return 2;
        }
    }
    value = TaLogic009_GetRevoltObj(nSide);
    if (value >= 0) {
        if (((value >> 16) & 0xFFFF) != 0xFFFF) {
            value = TaLogic009_GetSpecCardPlay(nSide, scratch, pInput, 0x2DC);
            if (value >= 0) {
                return 2;
            }
        }
        if ((value & 0xFFFF) != 0xFFFF && TaLogic009_GetSpecCardPlay(nSide, scratch, pInput, 0x2DD) >= 0) {
            return 2;
        }
    }
    if (TaLogic009_IsUseCurseDragonPot(nSide) == 1) {
        if (TaLogic009_GetSpecCardPlay(nSide, scratch, pInput, 0x2AB) >= 0) {
            return 2;
        }
    }
    i2 = 0;
    if (i2 < TaHand_GetNextHandNum(nSide)) {
        p2 = cards;
        do {
            if (SzDuel_Kind2Type(TaHand_GetCardKind(*p2) >> 5) == 2) {
                SzDuel_InitCardInfo(pInput, cards[i2]);
                return 1;
            }
            p2++;
            i2++;
        } while (i2 < TaHand_GetNextHandNum(nSide));
    }
    if (TaLogic009_GetSpecCardPlay(nSide, scratch, pInput, 0x2C9) >= 0) {
        return 2;
    }
    if (TaLogic009_IsUseCopyCat(nSide) >= 0) {
        if (TaLogic009_GetSpecCardPlay(nSide, scratch, pInput, 0x2AF) >= 0) {
            return 2;
        }
    }
    i3 = 0;
    if (i3 < TaHand_GetNextHandNum(nSide)) {
        p3 = cards;
        do {
            if ((TaHand_GetCardKind(*p3) >> 5) == 0 && TaHand_CanAffordSummonCost(nSide, *p3) == 1) {
                SzDuel_InitCardInfo(pInput, cards[i3]);
                return 0;
            }
            p3++;
            i3++;
        } while (i3 < TaHand_GetNextHandNum(nSide));
    }
    result = TaLogic009_GetSpellPlay(nSide, scratch, pInput, 999);
    if (result >= 0) {
        return result;
    }
    return -1;
}

/* Whether side `nSide` holds card `nCardNo` and can summon it (its slot into `bCombo`, the card into `pCardInfo`);
   returns its kind group or -1. */
s32 TaLogic009_GetSpecCardPlay(s32 nSide, void *bCombo, void *pCardInfo, s32 nCardNo) {
    s32 entries[8];
    s32 i;
    s32 *entry;
    s32 wanted;

    TaHand_GetNextHand(nSide, entries);
    i = 0;
    if (i < TaHand_GetNextHandNum(nSide)) {
        wanted = nCardNo & 0xFFFF;
        entry = entries;
        do {
            if (wanted == *entry && TaHand_CanAffordSummonCost(nSide, *entry) == 1) {
                *((s8 *)bCombo + 6) = i;
                SzDuel_InitCardInfo(pCardInfo, entries[i]);
                return TaHand_GetCardKind(entries[i]) >> 5;
            }
            entry++;
            i++;
        } while (i < TaHand_GetNextHandNum(nSide));
    }
    return -1;
}

/* Whether side `nSide` plays a magic or ritual card from its hand now (its slot into `bCombo`, the card into
   `pCardInfo`). */
s32 TaLogic009_GetSpellPlay(s32 nSide, u8 *bCombo, void *pCardInfo, s32 nMode) {
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

typedef struct Info_00136B80 {
    u8 pad00[8];
    u16 x;
    s16 y;
} Info_00136B80;

typedef struct Sprite_00136B80 {
    Info_00136B80 *info;
    u8 pad04[0x34];
    s16 x;
    s16 y;
} Sprite_00136B80;

/* Fills hand combination `bCombo` for side `nSide`: the best fusion or equip chain, its card into `pCardInfo`. */
s32 TaLogic009_SetComboQue(s32 nSide, u8 *bCombo, void *pCardInfo) {
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
                            TaLogic_Pegasus_ConvEmptyCombo(nSide, *node, entries);
                            TaLogic_CopyArray((u8 *)*node + 2, bCombo + 6);
                            SzDuel_InitCardInfo(pCardInfo, **node);
                            ((Sprite_00136B80 *)pCardInfo)->x = (value >> 16) - (((Sprite_00136B80 *)pCardInfo)->info->x & 0x1FFF);
                            ((Sprite_00136B80 *)pCardInfo)->y = (value & 0xFFFF) - (((Sprite_00136B80 *)pCardInfo)->info->y & 0x1FFF);
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
} Info_00136D60;

/* Fills an empty combination: the hand card side `nSide` can summon with the best attack plus defence. */
void TaLogic_Pegasus_ConvEmptyCombo(s32 nSide, void *pCardInfo, s32 *pResult) {
    Info_00136D60 *info = pCardInfo;
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
                if (card != 0x3E7 && level >= TaHand_GetCardSummonCost2(card, nSide)) {
                    cost = TaHand_GetCardAPDP(card);
                    if ((cost & 0xFFFF) + (cost >> 16) * 2 < 0x3E9 && TaHand_IsCardEffect(card) == 2 &&
                        (u16)TaLogic_GetHandFusion(info->id, (u16)card) == 0x3E7) {
                        TaLogic_AddEmptyCombo(info->values, buf[i]);
                    }
                }
            }
        }
    }
}

typedef struct {
    u8 pad0[6];
    u8 slot[5];
} Obj1_00136F30;

typedef struct {
    u8 pad0[0x3C];
    u16 id;
} Obj2_00136F30;

/* Fills hand combination `bCombo` for side `nSide` with this duelist's special combination, its card into
   `pCardInfo`. */
s32 TaLogic009_SetSpecialComboQue(s32 nSide, void *bCombo, void *pCardInfo) {
    Obj1_00136F30 *o1 = bCombo;
    Obj2_00136F30 *o2 = pCardInfo;
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

typedef struct {
    u8 low : 4;
    u8 high : 4;
} Nibbles_00137120;

/* The square side `nSide` summons a card of kind `sKind` to. */
s32 TaLogic009_GetSummonPiece(s32 nSide, u8 sKind, void *pInput, s32 nMode) {
    extern s32 TaLogic_IsUnitWin4();
    extern s32 TaLogic_GetInvadeRoot2();
    extern s32 TaLogic_GetRoot2(s32, s32, s32, s32, s32, s32, u16, u8);
    Nibbles_00137120 path[12];
    s32 n;
    Nibbles_00137120 *p;
    s32 originY;
    s32 originX;

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
    if ((u8)(*((u8 *)pInput + 0x3E) >> 5) == 0) {
        s32 y;
        s32 x;
        s32 i;
        s32 result;
        s32 position;
        if (nMode >= 0) {
            s32 position;
            s32 y;
            s32 cost;
            s32 x;
            s32 i;
            s32 bestPosition;
            s32 bestCost;
            s32 origin;

            bestCost = 255;
            bestPosition = 65535;
            origin = SzDuel_GetUnitLoc(nMode >> 8, nMode & 255);
            i = 0;
            originY = origin >> 8;
            originX = origin & 255;
            do {
                position = Ta_GetSommonPiecePreference(nSide, i);
                if (position >= 0) {
                    x = position & 255;
                    y = position >> 8;
                    if (SzDuel_GetField(x, y) != 8 &&
                        (SzDuel_GetField(x, y) != 9 || Ta_IsVirus_Chk3(pInput, x, y) != 1) &&
                        SzDuel_GetMapUnit(x, y) == 0) {
                        if (TaLogic_IsUnitWin4(pInput, nMode, 0, originX, originY, 1) > 0) {
                            cost = TaLogic_GetInvadeRoot2(pInput, path, x, y, originX, originY, nMode, 1, (s64)2, (s64)0);
                        } else {
                            cost = TaLogic_GetRoot2((s32)pInput, (s32)path, x, y, originX, originY, nMode, 2);
                        }
                        if (TaLogic_GetMinGoalCount((u8 *)path) > 0 && cost < bestCost) {
                            bestCost = cost;
                            bestPosition = position;
                        }
                    }
                }
                i++;
            } while (i < 8);
            if (bestPosition != 65535) {
                return bestPosition;
            }
        }
        result = -1;
        {
            i = 0;
            do {
                position = Ta_GetSommonPiecePreference(nSide, i);
                if (position >= 0) {
                    x = position & 255;
                    y = position >> 8;
                    if (SzDuel_GetField(x, y) != 8 &&
                        (SzDuel_GetField(x, y) != 9 || Ta_IsVirus_Chk3(pInput, x, y) != 1) &&
                        SzDuel_GetMapUnitID(x, y) < 0) {
                        result = position;
                    }
                }
                i++;
            } while (i < 8);
        }
        return result;
    } else {
        s32 y;
        s32 x;
        s32 i;
        s32 result;
        s32 position;
        result = -1;
        i = 0;
        do {
            position = Ta_GetSommonPiecePreference(nSide, i);
            if (position >= 0) {
                x = position & 255;
                y = position >> 8;
                if (SzDuel_GetField(x, y) != 8 &&
                    (SzDuel_GetField(x, y) != 9 || Ta_IsVirus_Chk3(pInput, x, y) != 1) &&
                    SzDuel_GetMapUnitID(x, y) < 0) {
                    result = position;
                }
            }
            i++;
        } while (i < 8);
        return result;
    }
}

typedef struct {
    u8 low : 4;
    u8 high : 4;
} Flags_001374D0;

typedef struct {
    u16 id;
    u8 action;
    u8 pad3;
    u16 position;
    u8 pad6[6];
    s32 value;
    u8 mode;
} Output_001374D0;

/* The task of a unit running from danger (task `pTask`): the safest square in reach, into `pInput` (`fFirst` = 1
   for the unit's first-choice task). */
s32 TaLogic_Pegasus_GetMinimumTask_RunMission(u16 *pTask, s32 nSide, void *pInput, u8 fFirst) {
    extern s32 TaLogic_IsRunPassRoot(s32, s32, s32, s32, s32, s32, void *, u8);
    s32 position;
    u8 upperX;
    u8 flag;
    Flags_001374D0 cells[12];
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
    Output_001374D0 *out = pInput;

    position = SzDuel_GetUnitLoc(*pTask >> 8, *pTask & 0xFF);
    i = 0;
    do {
        cells[i].low = cells[i].high = 15;
        i++;
    } while (i < 12);

    originalX = position & 0xFF;
    originalY = position >> 8;
    if (TaLogic_GetUnitWarning(originalX, originalY, *pTask, 3, 0, 1) == 0) {
        out->id = *pTask;
        out->action = 6;
        out->position = position;
        out->mode = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, out->position, 1, 1);
        out->value = TaLogic_Pegasus_IsOpenUnit(*pTask >> 8, *pTask & 0xFF, pTask);
        TaLogic_InitRogicControl(pTask, fFirst);
        return 0;
    } else {
        result = GetMoveRange(SzDuel_GetUnit(*pTask >> 8, *pTask & 0xFF), originalX, originalY);
        if (result == 0) {
            out->id = *pTask;
            out->action = 6;
            out->position = position;
            out->mode = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, out->position, 1, 1);
            out->value = TaLogic_Pegasus_IsOpenUnit(*pTask >> 8, *pTask & 0xFF, pTask);
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
                flag = TaLogic_IsAttackedNow(*pTask >> 8, *pTask & 0xFF, 1) & 0xFF;
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
                            (TaLogic_IsAttackedNow2(*pTask >> 8, *pTask & 0xFF, x, y, 1) == 0 || (u8)*pTask == 0)) {
                            score = TaLogic_GetUnitWarning(x, y, *pTask, 3, 0, 1);
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
                    out->mode = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, out->position, 1, 1);
                } else {
                    out->mode = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, out->position, 0, 1);
                }
                out->value = TaLogic_Pegasus_IsOpenUnit(*pTask >> 8, *pTask & 0xFF, pTask);
            } else {
                out->id = *pTask;
                out->action = 6;
                out->position = position;
                out->mode = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, out->position, 1, 1);
                out->value = TaLogic_Pegasus_IsOpenUnit(*pTask >> 8, *pTask & 0xFF, pTask);
            }
            TaLogic_InitRogicControl(pTask, fFirst);
        }
    }
    return 0;
}

typedef struct Input_001379F0 {
    u16 position;
    u8 pad2[6];
    u32 destinations;
} Input_001379F0;

typedef struct Output_001379F0 {
    u16 position;
    s8 action;
    u8 pad3;
    u16 destination;
    u8 pad6[6];
    s32 flag;
    s8 result;
} Output_001379F0;

typedef struct Coordinate_001379F0 {
    u8 x : 4;
    u8 y : 4;
} Coordinate_001379F0;

/* The task's target square: the second half-word when the second argument is 1, else the first. */
static inline s32 destination_001379F0(void *src, u8 mode) {
    Input_001379F0 *input = src;
    if (mode == 1) {
        return (u16)(input->destinations >> 16);
    }
    return (u16)input->destinations;
}

/* The task of a unit attacking (task `pTask`): its path to the goal, into `pInput`; -1 when it has none (`fFirst`
   = 1 for the unit's first-choice task). */
s32 TaLogic_Pegasus_GetMinimumTask_AtkMission(void *pTask, s32 nSide, void *pInput, u8 fFirst) {
    extern void TaLogic_GetInvadeRoot();
    Coordinate_001379F0 candidates[12];
    s32 targetPosition;
    s32 initialFlag;
    s32 i;
    s32 bestIndex;
    s32 count;
    s32 originalPosition;
    s32 originalY;
    s32 originalX;
    s32 found;
    s32 originalCard;
    s32 lowDestination;
    s32 highDestination;
    Input_001379F0 *input = pTask;
    Output_001379F0 *output = pInput;

    lowDestination = destination_001379F0(pTask, fFirst);
    highDestination = destination_001379F0(pTask, fFirst);
    if (SzDuel_GetUnit((u32)highDestination >> 8, lowDestination & 0xFF) == 0) {
        TaLogic_InitRogicControl(pTask, 1);
        return -1;
    }
    initialFlag = TaLogic_Pegasus_IsOpenUnit((s32)input->position >> 8, input->position & 0xFF, pTask);
    originalPosition = SzDuel_GetUnitLoc((s32)input->position >> 8, input->position & 0xFF);
    lowDestination = destination_001379F0(pTask, fFirst);
    highDestination = destination_001379F0(pTask, fFirst);
    targetPosition = SzDuel_GetUnitLoc((u32)highDestination >> 8, lowDestination & 0xFF);
    i = 0;
    do {
        candidates[i].x = candidates[i].y = 15;
        i++;
    } while (i < 12);
    originalCard = SzDuel_GetUnit((s32)input->position >> 8, input->position & 0xFF);
    originalX = originalPosition & 0xFF;
    originalY = originalPosition >> 8;
    if (GetMoveRange(originalCard, originalX, originalY) == 0) {
        s32 score;
        output->position = input->position;
        output->action = 6;
        output->destination = originalPosition;
        score = TaLogic_GetUnitWarning(originalX, originalY, nSide, 3, 0, 0);
        if (score >= SzDuel_GetUnitAP((s32)input->position >> 8, input->position & 0xFF, 0)) {
            output->result = TaLogic_IsDefStyleUnit((s32)input->position >> 8, input->position & 0xFF,
                                          output->destination, 1, 1);
        } else {
            output->result = TaLogic_IsDefStyleUnit((s32)input->position >> 8, input->position & 0xFF,
                                          output->destination, 0, 1);
        }
        TaLogic_InitRogicControl(pTask, fFirst);
        return 0;
    } else {
        s32 targetY;
        s32 targetX;
        Coordinate_001379F0 *candidate;
        s32 candidateIndex;
        s32 bestScore;

        TaLogic_GetInvadeRoot((s32)input->position >> 8, input->position & 0xFF,
                     candidates, originalX, originalY, targetX = targetPosition & 0xFF,
                     targetY = targetPosition >> 8,
                     destination_001379F0(pTask, fFirst), 1, 30, 0);
        count = TaLogic_GetMinGoalCount((u8 *)candidates);
        bestIndex = 255;
        if (count > 0) {
            found = 0;
            bestScore = 65535;
            for (candidateIndex = 0; candidateIndex < count; candidateIndex++) {
                if (TaLogic009_IsOpenMoveUnit((s32)input->position >> 8, input->position & 0xFF,
                                  originalX, originalY, targetX, targetY) == 1) {
                    bestIndex = candidateIndex;
                    found = 1;
                    candidates[candidateIndex].x = targetX;
                    candidates[candidateIndex].y = targetY;
                    candidateIndex = count;
                } else {
                    s32 score;
                    candidate = &candidates[candidateIndex];
                    score = TaLogic_GetUnitWarning(candidate->x, candidate->y, nSide, 2, 0, 0);
                    if (score < bestScore) {
                        bestScore = score;
                        bestIndex = candidateIndex;
                    } else if (score == bestScore) {
                        Coordinate_001379F0 *best = &candidates[bestIndex];
                        s32 minBestY;
                        s32 maxBestY;
                        s32 minBestX;
                        s32 maxBestX;
                        s32 minNextY;
                        s32 maxNextY;
                        s32 minNextX;
                        s32 maxNextX;

                        minBestY = best->y < targetY ? best->y : targetY;
                        maxBestY = targetY < best->y ? best->y : targetY;
                        minBestX = best->x < targetX ? best->x : targetX;
                        maxBestX = targetX < best->x ? best->x : targetX;
                        minNextY = candidate->y < targetY ? candidate->y : targetY;
                        maxNextY = targetY < candidate->y ? candidate->y : targetY;
                        minNextX = candidate->x < targetX ? candidate->x : targetX;
                        maxNextX = targetX < candidate->x ? candidate->x : targetX;
                        if ((maxNextX - minNextX) + (maxNextY - minNextY) <
                            (maxBestX - minBestX) + (maxBestY - minBestY)) {
                            bestScore = score;
                            bestIndex = candidateIndex;
                        }
                    }
                }
            }
        } else {
            output->position = input->position;
            output->action = 6;
            output->destination = originalPosition;
            output->flag = initialFlag;
            output->result = TaLogic_IsDefStyleUnit((s32)input->position >> 8, input->position & 0xFF,
                                          output->destination, 0, 1);
            TaLogic_InitRogicControl(pTask, fFirst);
            return 0;
        }
        if (bestIndex != 255) {
            output->position = input->position;
            output->action = 6;
            output->destination = (candidates[bestIndex].y << 8) | candidates[bestIndex].x;
            output->flag = found;
            output->result = TaLogic_IsDefStyleUnit((s32)input->position >> 8, input->position & 0xFF,
                                          output->destination, 0, 1);
        } else {
            output->position = input->position;
            output->action = 6;
            output->destination = originalPosition;
            output->flag = found;
            output->result = TaLogic_IsDefStyleUnit((s32)input->position >> 8, input->position & 0xFF,
                                          output->destination, 0, 1);
            TaLogic_InitRogicControl(pTask, fFirst);
            return 0;
        }
    }
    return 0;
}

typedef struct Unit_00137FB0 {
    u16 position;
    u8 pad2[6];
    union {
        u32 packed;
        u16 halves[2];
    } destination;
} Unit_00137FB0;

typedef struct Order_00137FB0 {
    u16 position;
    u8 kind;
    u8 pad3;
    u16 destination;
    u8 pad6[6];
    s32 value;
    u8 flags;
} Order_00137FB0;

typedef struct Point_00137FB0 {
    u8 x : 4;
    u8 y : 4;
} Point_00137FB0;

/* The task's target square: the second half-word when the second argument is 1, else the first. */
static inline u32 destination_00137FB0(void *unit, s32 side) {
    if (side == 1) {
        return (u16)(((Unit_00137FB0 *)unit)->destination.packed >> 16);
    }
    return ((Unit_00137FB0 *)unit)->destination.halves[0];
}

/* The task of a unit moving to its goal (task `pTask`), into `pInput` (`fFirst` = 1 for the unit's first-choice
   task). */
s32 TaLogic_Pegasus_GetMinimumTask_MoveMission(void *pTask, s32 nSide, void *pInput, u8 fFirst, u8 nKind) {
    extern s32 TaLogic_IsDefStyleUnit(s32, s32, s32, u8, s32);
    extern void TaLogic_GetRoot(s32, s32, void *, s32, s32, s32, s32, s32, u8);
    s32 count;
    s32 position;
    Point_00137FB0 points[12];
    s32 id;
    s32 score;
    u32 destinationValue;
    Unit_00137FB0 *unit = pTask;
    Order_00137FB0 *order = pInput;

    {
    s32 bestScore;
    s32 bestIndex;
    s32 side;
    Point_00137FB0 *point;
    s32 index;

    position = SzDuel_GetUnitLoc((s32)unit->position >> 8, unit->position & 0xFF);
    side = fFirst;
    if (destination_00137FB0(unit, side) == 0xFFFF) {
        if (position == destination_00137FB0(unit, side)) {
            order->position = unit->position;
            order->kind = 6;
            order->destination = position;
            order->flags = TaLogic_IsDefStyleUnit((s32)unit->position >> 8, unit->position & 0xFF,
                                       order->destination, nKind, 1);
            order->value = TaLogic_Pegasus_IsOpenUnit((s32)unit->position >> 8, unit->position & 0xFF, unit);
            TaLogic_InitRogicControl(unit, fFirst);
            return 0;
        }
    }

    point = points;
    {
        s32 i = 0;
        Point_00137FB0 *p = point;
        do {
            p->x = p->y = 15;
            i++;
            p++;
        } while (i < 12);
    }

    destinationValue = destination_00137FB0(unit, side);
    id = SzDuel_GetMapUnitID(destination_00137FB0(unit, side) & 0xFF,
                       destinationValue >> 8);
    if (id < 0) {
        id = 0xFFFF;
    }
    destinationValue = destination_00137FB0(unit, side);
    TaLogic_GetRoot((s32)unit->position >> 8, unit->position & 0xFF, points,
                  position & 0xFF, position >> 8,
                  destination_00137FB0(unit, side) & 0xFF,
                  destinationValue >> 8, (u16)id, 7);
    count = TaLogic_GetMinGoalCount((u8 *)points);
    if (count > 0) {
        bestIndex = 0xFF;
        bestScore = 0xFFFF;
        for (index = 0; index < count; index++, point++) {
            if (SzDuel_GetMapUnit(point->x, point->y) == 0) {
                score = TaLogic_GetUnitWarning(point->x, point->y, nSide, 2, 0, 0);
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
                    Point_00137FB0 *best = &points[bestIndex];

                    oldY = best->y;
                    if (oldY < (destination_00137FB0(unit, side) >> 8)) {
                        oldYMin = (u8)oldY;
                    } else {
                        oldYMin = destination_00137FB0(unit, side) >> 8;
                    }
                    if ((destination_00137FB0(unit, side) >> 8) < oldY) {
                        oldYMax = (u8)oldY;
                    } else {
                        oldYMax = destination_00137FB0(unit, side) >> 8;
                    }
                    oldX = best->x;
                    if (oldX < (destination_00137FB0(unit, side) & 0xFF)) {
                        oldXMin = (u8)oldX;
                    } else {
                        oldXMin = destination_00137FB0(unit, side) & 0xFF;
                    }
                    if ((destination_00137FB0(unit, side) & 0xFF) < oldX) {
                        oldXMax = (u8)oldX;
                    } else {
                        oldXMax = destination_00137FB0(unit, side) & 0xFF;
                    }

                    currentY = point->y;
                    if (currentY < (destination_00137FB0(unit, side) >> 8)) {
                        currentYMin = (u8)currentY;
                    } else {
                        currentYMin = destination_00137FB0(unit, side) >> 8;
                    }
                    if ((destination_00137FB0(unit, side) >> 8) < currentY) {
                        currentYMax = (u8)currentY;
                    } else {
                        currentYMax = destination_00137FB0(unit, side) >> 8;
                    }
                    currentX = point->x;
                    if (currentX < (destination_00137FB0(unit, side) & 0xFF)) {
                        currentXMin = (u8)currentX;
                    } else {
                        currentXMin = destination_00137FB0(unit, side) & 0xFF;
                    }
                    if ((destination_00137FB0(unit, side) & 0xFF) < currentX) {
                        currentXMax = (u8)currentX;
                    } else {
                        currentXMax = destination_00137FB0(unit, side) & 0xFF;
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
                                   order->destination, nKind, 1);
        order->value = TaLogic_Pegasus_IsOpenUnit((s32)unit->position >> 8, unit->position & 0xFF, unit);
        TaLogic_InitRogicControl(unit, fFirst);
        return 0;
    }
        if (bestIndex != 0xFF) {
            order->position = unit->position;
            order->kind = 6;
            order->destination = (points[bestIndex].y << 8) | points[bestIndex].x;
            order->flags = TaLogic_IsDefStyleUnit((s32)unit->position >> 8, unit->position & 0xFF,
                                       order->destination, nKind, 1);
            order->value = TaLogic_Pegasus_IsOpenUnit((s32)unit->position >> 8, unit->position & 0xFF, unit);
        } else {
            order->position = unit->position;
            order->kind = 6;
            order->destination = position;
            order->flags = TaLogic_IsDefStyleUnit((s32)unit->position >> 8, unit->position & 0xFF,
                                       order->destination, nKind, 1);
            order->value = TaLogic_Pegasus_IsOpenUnit((s32)unit->position >> 8, unit->position & 0xFF, unit);
        }
        TaLogic_InitRogicControl(unit, fFirst);
    }
    return 0;
}

typedef struct {
    u8 low : 4;
    u8 high : 4;
} Nibbles_00138780;

typedef struct {
    u16 pos;
    u8 kind;
    u8 unk03;
    u16 target;
    u8 pad06[6];
    s32 flag;
    u8 result;
} Out_00138780;

/* The task of reviving a monster from the graveyard (task `pTask`), into `pInput` (`fFirst` = 1 for the unit's
   first-choice task). */
s32 TaLogic_Pegasus_GetMinimumTask_ReviveMission(u16 *pTask, s32 nSide, void *pInput, u8 fFirst) {
    s32 card;
    s32 col;
    u16 row;
    Out_00138780 *out = pInput;
    Nibbles_00138780 entries[12];
    s32 i;
    Nibbles_00138780 *entry;

    SzDuel_GetUnitLoc(*pTask >> 8, *pTask & 0xFF);
    entry = entries;
    i = 0;
    do {
        entry->low = entry->high = 15;
        entry++;
        i++;
    } while (i < 12);

    card = TaLogic009_IsUseCopyCat(nSide);
    if (TaLogic_GetActionReaction(*pTask >> 8, *pTask & 0xFF, 0, 0, 6, 1) == 5) {
        card = -1;
    }
    if (card >= 0) {
        row = card >> 16;
        col = TaLogic_GetGraveEntryAfterScreen(row, card & 0xFF, 0);
        out->pos = *pTask;
        out->kind = 12;
        out->result = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, out->target, 1, 1);
        out->flag = 1;
        out->target = (row << 8) | col;
        TaLogic_InitRogicControl(pTask, fFirst);
        return 0;
    }
    if (SzDuel_GetUnitStatus(*pTask >> 8, *pTask & 0xFF, 4) != 0) {
        SzDuel_SetUnitStatus(*pTask >> 8, *pTask & 0xFF, 0, 1);
        out->pos = *pTask;
        out->kind = 14;
        return 0;
    }
    return TaLogic_Pegasus_GetMinimumTask_RunMission(pTask, nSide, pInput, fFirst);
}

typedef struct Nibbles_00138950 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_00138950;

typedef struct Out_00138950 {
    u16 pos;
    u8 kind;
    u8 unk03;
    u16 target;
    u8 pad06[6];
    s32 flag;
    u8 result;
} Out_00138950;

/* The controlled unit this duelist wants back, unless a trap waits on the way (-1). */
static inline s32 slot_00138950(u16 *unit, s32 arg1) {
    s32 card = TaLogic009_GetRevoltObj(arg1);
    if (TaLogic_GetActionReaction(*unit >> 8, *unit & 0xFF, 0, 0, 6, 1) == 5) {
        card = -1;
    }
    return card;
}

/* The task of taking back a controlled unit (task `pTask`), into `pInput`. */
s32 TaLogic_Pegasus_GetMinimumTask_RevoltMission(u16 *pTask, s32 nSide, void *pInput, u8 fFirst) {
    extern void SzDuel_SetUnitStatus(s32, s32, s32, s32);
    u16 *unit = pTask;
    s32 count;
    s32 card;
    s32 k;
    Out_00138950 *out = pInput;
    Nibbles_00138950 entries[12];
    s32 i;
    Nibbles_00138950 *entry;

    SzDuel_GetUnitLoc(*unit >> 8, *unit & 0xFF);
    entry = entries;
    i = 0;
    do {
        entry->low = entry->high = 15;
        entry++;
        i++;
    } while (i < 12);
    count = 0;
    card = slot_00138950(unit, nSide);
    if (card >= 0) {
        card = (card >> 16) & 0xFFFF;
        if (card != 0xFFFF) {
            k = 1;
            do {
                if (SzDuel_GetUnit(nSide == 0 ? 1 : 0, k) != 0) {
                    count++;
                }
                if (k == card) {
                    k = 11;
                }
                k++;
            } while (k < 11);
            out->pos = *unit;
            out->kind = 13;
            out->result = TaLogic_IsDefStyleUnit(*unit >> 8, *unit & 0xFF, out->target, 1, 1);
            out->flag = 1;
            out->target = count - 1;
            TaLogic_InitRogicControl(unit, fFirst);
            return 0;
        }
    }
    if (SzDuel_GetUnitStatus(*unit >> 8, *unit & 0xFF, 4) != 0) {
        SzDuel_SetUnitStatus(*unit >> 8, *unit & 0xFF, 0, 1);
        out->pos = *unit;
        out->kind = 14;
        return 0;
    }
    return TaLogic_Pegasus_GetMinimumTask_RunMission(unit, nSide, out, fFirst);
}

/* The unit of side `nSide` controlled by the opponent that this duelist wants back. */
s32 TaLogic009_GetRevoltObj(s32 nSide) {
    extern s32 SzDuel_GetUnitCurseRest(s32, s32);
    extern s32 SzDuel_GetUnitSpellRest(s32, s32);
    u16 cells[0x16];
    s32 target;
    s32 row;
    s32 col;
    u16 *p;
    s32 y;
    s32 x;
    s32 best;
    s32 i;
    s32 bestScore;
    u32 handle;
    s32 pos;
    s32 score;
    s32 j;

    pos = SzDuel_GetUnitLoc((nSide == 0) ? 1 : 0, 0);
    if (Ta_SearchUncTypeNaturalEffectUserNum(0x39) > 0) {
        return -1;
    }
    handle = Ta_RemoveObjFromFlagLst(SearchUnitByRange(0, 0, nSide, 2, 0x21, 0xE), nSide);
    p = cells;
    for (j = 0; j < 0x16; j++) {
        cells[j] = 0xFFFF;
    }
    TaLogic_GetUnitCtlLst((nSide == 0) ? 1 : 0, cells, 0x34, 1);
    target = -1;
    best = target;
    bestScore = 1;
    i = 0;
    if (i < TaLogic_GetUnitCtlLstLen(cells)) {
        row = pos >> 8;
        col = pos & 0xFF;
        do {
        pos = SzDuel_GetUnitLoc(*p >> 8, *p & 0xFF);
        y = pos >> 8;
        x = pos & 0xFF;
        if ((((x < col) ? col : x) - ((col < x) ? col : x)) +
                (((y < row) ? row : y) - ((row < y) ? row : y)) == 1 &&
            SzDuel_GetUnitStatus(*p >> 8, *p & 0xFF, 1) == 0 &&
            SzDuel_GetUnitCurseRest(*p >> 8, *p & 0xFF) == 0 &&
            SzDuel_GetUnitSpellRest(*p >> 8, *p & 0xFF) == 0) {
            if ((score = TaUtil_GetUnitAP(*p >> 8, *p & 0xFF, x, y)) >= bestScore) {
                best = *p;
                if (best == Ta_GetUnitOwnerIDFromLstCount(handle, 0)) {
                    target = best;
                }
                bestScore = score;
            }
        }
        p++;
        } while (++i < TaLogic_GetUnitCtlLstLen(cells));
    }
    if (best < 0) {
        return -1;
    }
    return ((best & 0xFFFF) << 16) | (target & 0xFFFF);
}

/* Whether side `nSide` should use the curse pot now (two or more targets, or a plain enemy monster in reach). */
s32 TaLogic009_IsUseCurseDragonPot(s32 nSide) {
    s32 unitSlot;
    s32 unitSide;
    s32 unitId;

    if (Ta_GetUnitNumFrom22bitFlagList(SearchUnitByRange(0, 0, nSide, 2, 0, 14)) >= 2) {
        return 1;
    }
    unitId = Ta_GetUnitOwnerIDFromLstCount(SearchUnitByRange(0, 0, nSide, 3, 33, 14), 0);
    unitSide = unitId >> 8;
    unitSlot = unitId & 0xFF;
    if (nSide != Ta_IsUnitControl(unitSide, unitSlot)) {
        if (((SzDuel_GetUnitKind(unitSide, unitSlot) >> 5) == 0) && !(SzDuel_GetUnitKind(unitSide, unitSlot) & 0x1F)) {
            return 1;
        }
    }
    return 0;
}

/* The Copycat card (0x2C9) in either graveyard side `nSide` can revive ((side << 16) | index), or -1. */
s32 TaLogic009_IsUseCopyCat(s32 nSide) {
    extern s32 SzDuel_GetGraveCount(s32);
    s32 i;

    if (SzDuel_GetUnitSpellCount(nSide) < 5) {
        for (i = 0; i < SzDuel_GetGraveCount(nSide); i++) {
            if (SzDuel_InqGrave(nSide, i) == 0x2C9) {
                return (nSide << 16) | i;
            }
        }
        for (i = 0; i < SzDuel_GetGraveCount(nSide == 0 ? 1 : 0); i++) {
            if (SzDuel_InqGrave(nSide == 0 ? 1 : 0, i) == 0x2C9) {
                return i | ((nSide == 0 ? 1 : 0) << 16);
            }
        }
    }
    return -1;
}

/* Whether side `nSide` can play ritual card `nCardNo` now (it has the units to give up). */
s32 TaLogic009_IsDoCerem(s32 nSide, s32 nCardNo) {
    s32 index;
    s32 mask;
    s32 low;
    s32 high;
    s32 packed;
    s32 value;
    s32 data[4];

    Ta_GetCeremSacrifice(data, *(s32 *)((u8 *)TaHand_GetCardEffect(nCardNo, 0) + 4));
    if ((mask = Ta_GetSacrificeUnit(data, nSide)) < 0) {
        return 0;
    }
    index = 0;
    if (index < Ta_GetUnitNumFrom22bitFlagList(mask)) {
        do {
            packed = Ta_GetUnitOwnerIDFromLstCount(mask, index);
            high = packed >> 8;
            low = packed & 0xFF;
            value = SzDuel_GetUnitLoc(high, low);
            if (TaUtil_GetUnitAP(high, low, value & 0xFF, value >> 8) >= 0xA28) {
                return 0;
            }
            index++;
        } while (index < Ta_GetUnitNumFrom22bitFlagList(mask));
    }
    return 1;
}

/* Whether unit (nSide, nID) may open while moving from (nX, nZ) to the square next to it, (gX, gZ). */
s32 TaLogic009_IsOpenMoveUnit(s32 nSide, s32 nID, s32 nX, s32 nZ, s32 gX, s32 gZ) {
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

/* Whether the units side `owner` would give up for a ritual are all weaker than 2600. */
static inline s32 check_list_00139180(s32 *buffer, s32 owner) {
    s32 player;
    s32 slot;
    s32 index;
    s32 list;
    s32 packed;

    if ((list = Ta_GetSacrificeUnit(buffer, owner)) < 0) {
        return 0;
    }
    for (index = 0; index < Ta_GetUnitNumFrom22bitFlagList(list); index++) {
        packed = Ta_GetUnitOwnerIDFromLstCount(list, index);
        player = packed >> 8;
        slot = packed & 0xFF;
        packed = SzDuel_GetUnitLoc(player, slot);
        if (TaUtil_GetUnitAP(player, slot, packed & 0xFF, packed >> 8) >= 0xA28) {
            return 0;
        }
    }
    return 1;
}

/* Whether side `arg0` has the targets for its curse card (as TaLogic009_IsUseCurseDragonPot). */
static inline s32 check_target_00139180(s32 arg0) {
    s32 player;
    s32 slot;
    s32 packed;

    if (Ta_GetUnitNumFrom22bitFlagList(SearchUnitByRange(0, 0, arg0, 2, 0, 14)) >= 2) {
        return 1;
    }
    packed = Ta_GetUnitOwnerIDFromLstCount(SearchUnitByRange(0, 0, arg0, 3, 33, 14), 0);
    player = packed >> 8;
    slot = packed & 0xFF;
    if (arg0 != Ta_IsUnitControl(player, slot)) {
        if ((SzDuel_GetUnitKind(player, slot) >> 5) == 0 &&
            (SzDuel_GetUnitKind(player, slot) & 0x1F) == 0) {
            return 1;
        }
    }
    return 0;
}

/* Whether this duelist opens (turns face up) unit (nSide, nID) now: 0 no, 1 or 2 by its kind. */
s32 TaLogic_Pegasus_IsOpenUnit(s32 nSide, s32 nID, void *pInfo) {
    extern s32 SzDuel_GetUnitCurseRest();
    s32 buffer[4];
    s32 i;
    s32 card;
    u32 *info;
    s32 position;
    u8 count;
    s32 owner;
    s32 target;
    s32 valid;
    s32 state;

    card = SzDuel_GetUnitCardNo();
    Ta_IsUnitControl(nSide, nID);
    info = SzDuel_GetUnitEffect(nSide, nID, 0);
    position = SzDuel_GetUnitLoc(nSide, nID);
    count = 0;
    if (SzDuel_GetUnitStatus(nSide, nID, 4) != 0) {
        return 0;
    }
    state = SzDuel_GetUnitKind(nSide, nID) >> 5;
    switch (state) {
    case 0:
        switch (card) {
        case 0x265:
            i = 1;
            while (1) {
                if (SzDuel_GetUnitCurseRest(nSide, i) > 0 &&
                    nSide == Ta_IsUnitControl(nSide, i)) {
                    count++;
                }
                if (SzDuel_GetUnitCurseRest(nSide == 0 ? 1 : 0, i) > 0 &&
                    nSide == Ta_IsUnitControl(nSide == 0 ? 1 : 0, i)) {
                    count++;
                }
                i++;
                if (i > 11) {
                    break;
                }
            }
            if ((u8)count >= 2) {
                return 1;
            }
        }
        return 2;
    case 5:
        if (TaLogic_GetActionReaction(nSide, nID, 0, 0, 6, 1) == 5) {
            return 2;
        }
        owner = Ta_IsUnitControl(nSide, nID);
        Ta_GetCeremSacrifice(buffer, *(s32 *)((u8 *)TaHand_GetCardEffect(card, 0) + 4));
        valid = check_list_00139180(buffer, owner);
        if (valid == 1) {
            if (SzDuel_GetField(position & 0xFF, position >> 8) != 9) {
                return 1;
            }
        }
        break;
    case 1:
        if (TaLogic_GetActionReaction(nSide, nID, 0, 0, 6, 1) == 5) {
            return 2;
        }
        if (info == NULL) {
            return 2;
        }
        switch (*info >> 8) {
        case 2:
            target = TaLogic_GetLandChange(SzDuel_GetUnit(nSide, nID),
                position & 0xFF, position >> 8, 6, 5, 2);
            if (target >= 0 && (target >> 8) < 4 && position == target) {
                return 1;
            }
            break;
        case 13:
            return 1;
        case 23:
            valid = check_target_00139180(nSide);
            if (valid == 1) {
                return 1;
            }
            break;
        case 31:
            if (card == 0x2DD) {
                target = TaLogic009_GetRevoltObj(nSide);
                if (target >= 0 && (target & 0xFFFF) != 0xFFFF) {
                    return 1;
                }
            }
            break;
        case 32:
            i = 1;
            while (1) {
                if (SzDuel_GetUnitCurseRest(nSide, i) != 0 &&
                    nSide == Ta_IsUnitControl(nSide, i)) {
                    count++;
                }
                if (SzDuel_GetUnitCurseRest(nSide == 0 ? 1 : 0, i) != 0 &&
                    nSide == Ta_IsUnitControl(nSide == 0 ? 1 : 0, i)) {
                    count++;
                }
                i++;
                if (i > 11) {
                    break;
                }
            }
            if ((u8)count >= 2) {
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

typedef struct {
    u16 unk0;
    u8 unk2;
    u8 pad3;
    u16 unk4;
    u8 unk6[5];
    u8 padB;
    s32 unkC;
    u8 unk10;
} Req_001396C0;

typedef struct {
    u8 pad0[0x160];
    u16 list[32];    /* 0x160 */
    u8 idx : 5;      /* 0x1A0 */
    u8 pad1A0 : 3;
    u8 pad1A1;
    u16 count;       /* 0x1A2 */
} Work_001396C0;

s32 TaLogic_GetInputQueFromMinimumTask_b(void *, void *, s32);

/* Computer duelist 9's controller (duelistControllers[9]): the buttons it presses this frame. With an empty input
   queue it plans its next task and turns it into buttons, then plays the queue back one button per frame; after
   600 frames it gives up the turn (0x20, then 0x800). */
s32 duelistController09(s32 wCursorPos, void *pCtl) {
    Req_001396C0 req;
    Work_001396C0 *w;
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
        if (TaLogic_Pegasus_GetMinimumTask(w, &req, wCursorPos) == 0) {
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

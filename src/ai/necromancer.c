/* Computer AI of the Necromancer (duelist 6, duelistController06). */

#include "common.h"

s32 TaLogic_GetInputQueFromMinimumTask_b(void *, void *, s32);
#pragma conditional_move off

/* This duelist's move: picks the next unit to act, gives it a task and turns that into input `pInput`; returns 1
   when it set one. */
s32 TaLogic_Necromancer_GetMinimumTask(void *pCtl, void *pInput, s32 wCursorPos) {
    UnitTask *tasks = pCtl;
    s32 side;
    s32 found;
    s32 result;
    s32 index;

    side = SzDuel_GetTurnOwner();
    found = 0;
    if ((result = TaLogic_Necromancer_GetNextActiveUnit(tasks, side, (s32)pInput)) < 0) {
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
    TaLogic_Necromancer_CommandUnit(&tasks[index]);
    switch ((tasks[index].mission >> 8) & 0xFF) {
    case TASK_RUN:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            TaLogic_Necromancer_GetMinimumTask_RunMission(&tasks[index], side, pInput, 1);
            found = 1;
        }
        break;
    case TASK_ATTACK:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            if (TaLogic_Necromancer_GetMinimumTask_AtkMission(&tasks[index], side, pInput, 1) < 0) {
                TaLogic006_InitRogicControl(&tasks[index], 1);
                return 1;
            }
            found = 1;
        }
        break;
    case TASK_SUMMON:
        if (TaLogic_Necromancer_GetMinimumTask_Summon(tasks[index].ownerId, side, (s32)pInput) < 0) {
            TaLogic006_InitRogicControl(&tasks[index], 1);
            *(u8 *)((u8 *)pInput + 2) = 0xFF;
            *(s32 *)((u8 *)pInput + 0xC) = 0;
        } else {
            TaLogic006_InitRogicControl(&tasks[index], 1);
            found = 1;
        }
        break;
    case TASK_MOVETOLOCATION:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            TaLogic_Necromancer_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 1, 0);
            found = 1;
        }
        break;
    case TASK_CONFIRMUNIT:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            TaLogic_Necromancer_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 1, 1);
            found = 1;
        }
        break;
    case TASK_ENCHANT:
        TaLogic_GetMinimumTask_EncMission(&tasks[index], side, pInput, 1, 0, TaLogic_Necromancer_GetWarnHideLvl(side), 5, 1);
        found = 1;
        break;
    case TASK_TRAP:
        TaLogic_Necromancer_GetMinimumTask_TrapMission(&tasks[index], side, pInput, 1);
        found = 1;
        break;
    case TASK_REVIVE:
        TaLogic_Necromancer_GetMinimumTask_ReviveMission(&tasks[index], side, (s32)pInput, 1);
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
            TaLogic_Necromancer_GetMinimumTask_RunMission(&tasks[index], side, pInput, 0);
            found = 1;
        }
        break;
    case 2:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            if (TaLogic_Necromancer_GetMinimumTask_AtkMission(&tasks[index], side, pInput, 0) < 0) {
                TaLogic_Necromancer_GetMinimumTask_RunMission(&tasks[index], side, pInput, 0);
            }
            found = 1;
        }
        break;
    case 10:
        if (TaLogic_Necromancer_GetMinimumTask_Summon(tasks[index].ownerId, side, (s32)pInput) < 0) {
            TaLogic006_InitRogicControl(&tasks[index], 0);
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
            TaLogic_Necromancer_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 0, 0);
            found = 1;
        }
        break;
    case 3:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            TaLogic_Necromancer_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 0, 1);
            found = 1;
        }
        break;
    case 11:
        TaLogic_Necromancer_GetMinimumTask_TrapMission(&tasks[index], side, pInput, 0);
        found = 1;
        break;
    case 9:
        TaLogic_GetMinimumTask_EncMission(&tasks[index], side, pInput, 0, 0, TaLogic_Necromancer_GetWarnHideLvl(side), 5, 1);
        found = 1;
        break;
    case 12:
        TaLogic_Necromancer_GetMinimumTask_ReviveMission(&tasks[index], side, (s32)pInput, 0);
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

typedef struct Entry_001271F0 {
    u16 unitId; /* (side << 8) | unit */
    u16 pad2;
    s16 action;
    u16 pad6;
    s32 target;
} Entry_001271F0;
#pragma conditional_move reset

/* Gives a unit of this duelist its order for this turn (attack, run, move, summon, guard). */
s32 TaLogic_Necromancer_CommandUnit(void *pCtl) {
    Entry_001271F0 *entry = pCtl;
    s32 card;
    u16 unitId;

    card = Ta_IsUnitControl(entry->unitId >> 8, entry->unitId & 0xFF);
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
                            entry->target &= 0xFFFF0000;
                        } else {
                            entry->action = 0x6FF;
                            entry->target = (u16)entry->target;
                        }
                    }
                } else {
                    switch (SzDuel_GetUnitKind(unitId >> 8, unitId & 0xFF) >> 5) {
                    case 0:
                        if (TaUtil_IsExMonster(entry->unitId >> 8, entry->unitId & 0xFF) == 1) {
                            TaLogic006_CommandEfcMonster(entry);
                        } else {
                            TaLogic006_CommandBtlUnit(entry, 1);
                        }
                        break;
                    case 2:
                        TaLogic_CommandEncUnit(entry, 5, 0, TaLogic_Necromancer_GetWarnHideLvl(card) & 0xFF);
                        break;
                    case 1:
                    case 3:
                    case 4:
                    case 5:
                        TaLogic006_CommandSpellUnit(entry);
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
s32 TaLogic_Necromancer_GetNextActiveUnit(u16 *pCtl, s32 nSide, s32 pInput) {
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
    TaLogic_Necromancer_CommandUnit(pCtl + idx * 8);
    if (((pCtl[idx * 8 + 2] >> 8) & 0xFF) == 10) {
        if (SzDuel_InqHandPhase(nSide) == 1 && TaLogic_Necromancer_GetMinimumTask_Summon(pos, nSide, pInput) >= 0) {
            return pos | 0x10000;
        }
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_GetUnitStatus(nSide, 0, 0) == 0) {
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_InqHandPhase(nSide) == 1 && TaLogic_Necromancer_GetMinimumTask_Summon(pos, nSide, pInput) >= 0) {
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
} Entry_001277C0;

typedef struct {
    u16 card;
    u8 flag;
    u8 pad;
} Slot_001277C0;

/* Orders a fighting unit (task `pTask`): straight at the enemy leader when `fGoalFirst` and the path is open,
   else at the nearest enemy it can beat. */
void TaLogic006_CommandBtlUnit(void *pTask, s32 fGoalFirst) {
    extern void TaLogic_InitIgnoreLst();
    extern s32 TaLogic_IsRootOpen();
    extern s32 TaLogic006_GetNearUnit();
    Entry_001277C0 *entry = pTask;
    s32 side;
    s32 player;
    s32 other;
    s32 pos;
    s32 otherPos;
    s32 i;
    u8 work[0x70];
    Slot_001277C0 list[22];
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
            switch (TaLogic006_GetNearUnit(entry, 0, player, pos & 0xFF, pos >> 8,
                                  Ta_GetCurrentSide(entry->unitId >> 8, entry->unitId & 0xFF) == 0 ? 1 : 0,
                                  i & 0xFF, TaLogic_Necromancer_GetWarnHideLvl(side), list, 0, &countA, &countB, 5, work)) {
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
        TaLogic006_CommandInvadeUnit(entry);
    }
}

/* TaLogic_GetNearUnit with this duelist's view and strength settings. */
s32 TaLogic006_GetNearUnit(s32 pTask, s32 pTree, s32 pVarInfo, s32 nX, s32 nZ, s32 eSide, s32 bDist, s32 WarnLvl, s32 nUnitLst, u16 wUnitNum, s32 wSize, s32 wNodeCount, u8 bChase, s32 wIgnoreLst) {
    return TaLogic_GetNearUnit(pTask, pTree, pVarInfo, nX, nZ, eSide, bDist, WarnLvl,
                  nUnitLst, wUnitNum, wSize, wNodeCount, bChase,
                  0, 2000, wIgnoreLst);
}

/* Orders a unit (task `pTask`) to push into the opponent's side of the board. */
void TaLogic006_CommandInvadeUnit(UnitTask *pTask) {
    s32 loc;
    u16 temp_v0;

    temp_v0 = pTask->ownerId;
    loc = SzDuel_GetUnitLoc((s32) temp_v0 >> 8, temp_v0 & 0xFF);
    *(s16 *)&pTask->mission = 0x6FF;
    if ((loc >> 8) < 3) {
        pTask->dwGoal = *(u16 *)&pTask->dwGoal | 0x03010000;
    } else {
        pTask->dwGoal = *(u16 *)&pTask->dwGoal | 0x05020000;
    }
}

typedef struct {
    u16 value;
    u8 flag;
} Entry_00127B00;

/* Orders an effect monster (task `pTask`): where its effect does most. */
void TaLogic006_CommandEfcMonster(void *pTask) {
    extern void TaLogic_InitIgnoreLst();
    extern s32 SzDuel_GetUnitCardNo();
    extern s32 TaLogic_GetNearUnit();
    u8 scratch[0x70];
    Entry_00127B00 entries[0x17];
    s16 result_a;
    s16 result_b;
    s32 i;
    Entry_00127B00 *entry;
    s32 side;
    s32 loc;
    s32 temp_v0_2;
    s32 result;
    s32 high;
    s32 low;
    s32 i2;
    s32 code;

    if ((temp_v0_2 = SzDuel_GetUnit(*(u16 *)pTask >> 8, *(u16 *)pTask & 0xFF)) != 0) {
        side = Ta_GetCurrentSide(*(u16 *)pTask >> 8, *(u16 *)pTask & 0xFF);
        loc = SzDuel_GetUnitLoc(*(u16 *)pTask >> 8, *(u16 *)pTask & 0xFF);
        result_b = 0;
        result_a = 0;
        entry = entries;
        i = 0;
        do {
            i++;
            entry->value = 0xFFFF;
            entry->flag = 0xFF;
            entry++;
        } while (i < 0x16);
        TaLogic_InitIgnoreLst(scratch);
        code = SzDuel_GetUnitCardNo(*(u16 *)pTask >> 8, *(u16 *)pTask & 0xFF);
        switch (code) {
        case 0x6F:
            if (TaLogic_CommandGunnerUnit(pTask, 0) == 1) {
                *(s16 *)((u8 *)pTask + 4) = 0xBFF;
                return;
            }
            goto fallback_00127B00;
        case 0x6C:
            i2 = 1;
            high = loc >> 8;
            low = loc & 0xFF;
            goto loop_00127B00;
        default:
            goto fallback_00127B00;
        }
loop_00127B00:
                result = TaLogic_Necromancer_GetWarnHideLvl(side);
                entry = entries;
                result = TaLogic_GetNearUnit((s32)pTask, 0, temp_v0_2, low, high,
                                      side == 0 ? 1 : 0,
                                      i2 & 0xFF, result, (s32)entry, 0,
                                      (s32)&result_a, (s32)&result_b, 2, 0, 0x7D0,
                                      (s32)scratch);
                if (result != 0) {
                    if (result != 1) {
                        if (result != 2) {
                            if (result != 3) {
                                i2++;
                                goto retry_00127B00;
                            }
                        }
                        *(s16 *)((u8 *)pTask + 4) = 0x3FF;
                        *(u32 *)((u8 *)pTask + 8) = (loc << 16) | *(u16 *)((u8 *)pTask + 8);
                        return;
                    }
                } else {
                    *(s16 *)((u8 *)pTask + 4) = 0x3FF;
                    *(u32 *)((u8 *)pTask + 8) = (loc << 16) | *(u16 *)((u8 *)pTask + 8);
                    return;
                }
                return;
retry_00127B00:
        if (i2 <= 2) {
            goto loop_00127B00;
        }
        *(s16 *)((u8 *)pTask + 4) = 0x3FF;
        *(u32 *)((u8 *)pTask + 8) = (loc << 16) | *(u16 *)((u8 *)pTask + 8);
        return;
fallback_00127B00:
        TaLogic006_CommandBtlUnit(pTask, 1);
        return;
    }
}

typedef struct {
    u16 card;
    u16 pad2;
    s16 state;
    u16 pad6;
    union {
        u32 word;
        struct {
            u32 lower : 16;
            u32 upper : 16;
        } bits;
    } target;
} Obj_00127D20;

/* Orders a face-down magic card (task `pTask`): whether and where to open it. */
void TaLogic006_CommandSpellUnit(void *pTask) {
    extern s32 SzDuel_GetUnitCardNo();
    Obj_00127D20 *obj = pTask;
    s32 pos;

    Ta_IsUnitControl(obj->card >> 8, obj->card & 0xFF);
    SzDuel_GetUnitLoc(obj->card >> 8, obj->card & 0xFF);
    switch (SzDuel_GetUnitCardNo(obj->card >> 8, obj->card & 0xFF)) {
    case 0x2E9:
        pos = SzDuel_GetUnitLoc(obj->card >> 8, obj->card & 0xFF);
        obj->state = 0x6FF;
        if ((pos >> 8) < 3) {
            obj->target.word = obj->target.bits.lower | 0x03010000;
        } else {
            obj->target.word = obj->target.bits.lower | 0x05020000;
        }
        break;
    case 0x2B2:
        obj->state = 0x6FF;
        obj->target.word = obj->target.bits.lower | 0x04050000;
        break;
    case 0x2AD:
        obj->state = 0xCFF;
        obj->target.word = obj->target.bits.lower | 0xFFFF0000;
        break;
    default:
        obj->state = 0x5FF;
        break;
    }
}

typedef struct {
    s16 id;
    u8 unk2;
    u8 pad3;
    s16 unk4;
    u8 pad6[6];
    s32 unkC;
} Ctx_00127E30;

typedef struct {
    u8 pad0[0x3C];
    u16 unk3C;
    u8 pad3E[0x22];
} Work_00127E30;

s32 TaLogic_GetNearCard2(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8,
                  s32 arg9);

/* The summon task for side `nSide`: which hand cards to play and where, into `pInput`; -1 when it plays none. */
s32 TaLogic_Necromancer_GetMinimumTask_Summon(s32 wUnit, s32 nSide, s32 pInput) {
    extern s32 TaLogic_GetUnitNum(s32, s32);
    Work_00127E30 work;
    s32 ret;
    s32 res;
    s32 pos;
    s32 kind;
    Ctx_00127E30 *ctx = (Ctx_00127E30 *)pInput;

    ctx->id = wUnit;
    if (SzDuel_InqHandPhase(nSide) == 0) {
        return -1;
    }
    if (TaLogic_GetUnitNum(nSide, 0) == 5 && TaLogic_GetUnitNum(nSide, 1) == 5) {
        return -1;
    }
    kind = TaLogic006_IsHandPlay(nSide, &work);
    if (kind < 0) {
        return -1;
    }
    ctx->unk2 = 10;
    ctx->unkC = 0;
    pos = SzDuel_GetUnitLoc(wUnit >> 8, wUnit & 0xFF);
    if (kind == 0) {
        if (TaLogic006_SetComboQue(nSide, (u8 *)ctx, &work) >= 0) {
            ret = TaLogic_GetNearCard2(&work, pos & 0xFF, pos >> 8, nSide == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, TaLogic_Necromancer_GetWarnHideLvl(nSide));
            if (ret < 0) {
                if (SzDuel_GetUnitMonsterCount(nSide) < 5) {
                    res = TaLogic006_GetSummonPiece(nSide, kind, &work, ret);
                    if (res < 0) {
                        return -1;
                    }
                    ctx->unk4 = res;
                    return 1;
                }
            } else {
                res = TaLogic006_GetSummonPiece(nSide, kind, &work, ret);
                if (res < 0) {
                    return -1;
                }
                ctx->unk4 = res;
                return 1;
            }
        }
    } else {
        ret = TaLogic_GetNearCard2(&work, pos & 0xFF, pos >> 8, nSide == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, TaLogic_Necromancer_GetWarnHideLvl(nSide));
    }
    if (kind == 2) {
        TaLogic006_SetSpecialComboQue(nSide, ctx, &work);
        res = TaLogic006_GetSummonPiece(nSide, kind, &work, ret);
        if (res < 0) {
            return -1;
        }
        ctx->unk4 = res;
        return 1;
    }
    if (TaLogic006_GetSpellPlay(nSide, (u8 *)ctx, &work, work.unk3C) < 0) {
        return -1;
    }
    res = TaLogic006_GetSummonPiece(nSide, kind, &work, ret);
    if (res < 0) {
        return -1;
    }
    ctx->unk4 = res;
    return 1;
}

/* Whether side `nSide` should play from its hand this turn (and what, into `pInput`). */
s32 TaLogic006_IsHandPlay(s32 nSide, void *pInput) {
    extern s32 TaLogic_GetUnitNum();
    extern s32 func_0012B000();
    s32 cards[8];
    u8 buffer[32];
    u8 type0;
    u8 type1;
    s32 result;
    s32 value;

    type0 = TaLogic_GetUnitNum(nSide, 0);
    type1 = TaLogic_GetUnitNum(nSide, 1);
    if (pInput == NULL) {
        return -1;
    }
    TaHand_GetNextHand(nSide, cards);
    if (type0 == 5) {
        if (TaLogic006_GetSpellPlay(nSide, buffer, pInput, 999) >= 0) {
            return 1;
        }
        return -1;
    }
    if (type1 == 5) {
        s32 i = 0;
        s32 *p;
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
    if (TaLogic006_GetSpecCardPlay(nSide, buffer, pInput, 699) >= 0) {
        if (TaLogic_IsAttackedNow(nSide, 0, 0) == 1 || func_0012B000(nSide) == 1) {
            return 2;
        }
    }
    if (TaLogic006_GetSpecCardPlay(nSide, buffer, pInput, 108) >= 0) {
        return 2;
    }
    value = TaLogic_GetMaxAPGraveCard(nSide, 3);
    if (value >= 0) {
        if ((u16)value >= 2400 && TaLogic006_GetSpecCardPlay(nSide, buffer, pInput, 685) >= 0) {
            return 2;
        }
    }
    if (TaLogic006_GetSpecCardPlay(nSide, buffer, pInput, 851) >= 0 && TaLogic006_IsDoCerem(nSide, 851) == 1) {
        return 2;
    }
    if (type0 == 0) {
        s32 *p;
        s32 i = 0;
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
    {
        s32 *p;
        s32 i = 0;
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
    }
    result = TaLogic006_GetSpellPlay(nSide, buffer, pInput, 999);
    if (result >= 0) {
        return result;
    }
    return -1;
}

/* Whether side `nSide` holds card `nCardNo` and can summon it (its slot into `bCombo`, the card into `pCardInfo`);
   returns its kind group or -1. */
s32 TaLogic006_GetSpecCardPlay(s32 nSide, void *bCombo, void *pCardInfo, s32 nCardNo) {
    s32 index;
    s32 *entry;
    s32 target;
    s32 entries[8];

    TaHand_GetNextHand(nSide, entries);
    index = 0;
    if (index < TaHand_GetNextHandNum(nSide)) {
        target = nCardNo & 0xFFFF;
        entry = entries;
        do {
            if (target == *entry && TaHand_CanAffordSummonCost(nSide, *entry) == 1) {
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
s32 TaLogic006_GetSpellPlay(s32 nSide, u8 *bCombo, void *pCardInfo, s32 nMode) {
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

typedef struct Info_00128720 {
    u8 pad00[8];
    u16 x;
    s16 y;
} Info_00128720;

typedef struct Sprite_00128720 {
    Info_00128720 *info;
    u8 pad04[0x34];
    s16 x;
    s16 y;
} Sprite_00128720;

/* Fills hand combination `bCombo` for side `nSide`: the best fusion or equip chain, its card into `pCardInfo`. */
s32 TaLogic006_SetComboQue(s32 nSide, u8 *bCombo, void *pCardInfo) {
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
                            TaLogic_Necromancer_ConvEmptyCombo(nSide, *node, entries);
                            TaLogic_CopyArray((u8 *)*node + 2, bCombo + 6);
                            SzDuel_InitCardInfo(pCardInfo, **node);
                            ((Sprite_00128720 *)pCardInfo)->x = (value >> 16) - (((Sprite_00128720 *)pCardInfo)->info->x & 0x1FFF);
                            ((Sprite_00128720 *)pCardInfo)->y = (value & 0xFFFF) - (((Sprite_00128720 *)pCardInfo)->info->y & 0x1FFF);
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
} Info_00128900;

/* Fills an empty combination: the hand card side `nSide` can summon with the best attack plus defence. */
void TaLogic_Necromancer_ConvEmptyCombo(s32 nSide, void *pCardInfo, s32 *pResult) {
    Info_00128900 *info = pCardInfo;
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
                if (card != 0x3E7 && TaLogic006_IsRefuseEmptyCombo(card) == 0 && level >= TaHand_GetCardSummonCost2(card, nSide)) {
                    cost = TaHand_GetCardAPDP(card);
                    if ((cost & 0xFFFF) + (cost >> 16) * 2 < 0xCE5 && TaHand_IsCardEffect(card) == 2 &&
                        (u16)TaLogic_GetHandFusion(info->id, (u16)card) == 0x3E7) {
                        TaLogic_AddEmptyCombo(info->values, buf[i]);
                    }
                }
            }
        }
    }
}

/* Whether this duelist keeps card `nCardNo` out of a summon (it is wanted for an equip). */
s32 TaLogic006_IsRefuseEmptyCombo(s32 nCardNo) {
    if ((TaHand_GetCardKind(nCardNo) >> 5) != 0) {
        return 1;
    }
    if (nCardNo == 0x6C || nCardNo == 0x6F || nCardNo == 0x68) {
        return 1;
    }
    return 0;
}

typedef struct {
    u8 pad0[6];
    u8 slot[5];
} Obj1_00128B50;

typedef struct {
    u8 pad0[0x3C];
    u16 id;
} Obj2_00128B50;

/* Fills hand combination `bCombo` for side `nSide` with this duelist's special combination, its card into
   `pCardInfo`. */
s32 TaLogic006_SetSpecialComboQue(s32 nSide, void *bCombo, void *pCardInfo) {
    Obj1_00128B50 *o1 = bCombo;
    Obj2_00128B50 *o2 = pCardInfo;
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

typedef struct Nibbles_00128D40 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_00128D40;

/* The square side `nSide` summons a card of kind `sKind` to. */
s32 TaLogic006_GetSummonPiece(s32 nSide, u8 sKind, void *pInput, s32 nMode) {
    extern s32 TaLogic_IsUnitWin4();
    extern s32 TaLogic_GetInvadeRoot2();
    extern s32 TaLogic_GetRoot2(s32, s32, s32, s32, s32, s32, u16, u8);
    s32 best;
    s32 bestCost;
    s32 candidate;
    Nibbles_00128D40 flags[12];
    s32 i;
    Nibbles_00128D40 *p;
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
    if (kind == 0) {
        if (nMode >= 0) {
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
                        if (TaLogic_IsUnitWin4(pInput, nMode, TaLogic_Necromancer_GetWarnHideLvl(nSide),
                                         originX, originY, 0) > 0) {
                            cost = TaLogic_GetInvadeRoot2(pInput, flags, x, y,
                                                originX, originY, nMode, 0,
                                                5, (u16)TaLogic_Necromancer_GetWarnHideLvl(nSide));
                        } else {
                            cost = TaLogic_GetRoot2((s32)pInput, (s32)flags, x, y,
                                                originX, originY, nMode, 5);
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
            s32 maxY;
            s32 maxX;
            s32 y;
            s32 x;
            s32 minY;
            s32 minX;
            s32 origin;

            bestCost = 14;
            best = -1;
            i = 0;
            do {
                candidate = Ta_GetSommonPiecePreference(nSide, i);
                if (candidate >= 0) {
                    x = candidate & 255;
                    y = candidate >> 8;
                    if (SzDuel_GetField(x, y) != 8 &&
                        (SzDuel_GetField(x, y) != 9 ||
                         Ta_IsVirus_Chk3(pInput, x, y) != 1) &&
                        SzDuel_GetMapUnitID(x, y) < 0) {
                        if (y < 3) {
                            minY = y < 3 ? y : 3;
                            maxY = y > 3 ? y : 3;
                            minX = x < 1 ? x : 1;
                            maxX = x > 1 ? x : 1;
                            (void)maxX; /* a use between the clamp and the distance keeps maxX's temp, so y and x take s0/s1 as in the original */
                            origin = (maxX - minX) + (maxY - minY);
                        } else {
                            minY = y < 5 ? y : 5;
                            maxY = y > 5 ? y : 5;
                            minX = x < 2 ? x : 2;
                            maxX = x > 2 ? x : 2;
                            (void)maxX; /* a use between the clamp and the distance keeps maxX's temp, so y and x take s0/s1 as in the original */
                            origin = (maxX - minX) + (maxY - minY);
                        }
                        if (origin < bestCost && origin >= 0) {
                            best = candidate;
                            bestCost = origin;
                        }
                    }
                }
                i++;
            } while (i < 8);
            if (bestCost < 14) {
                return best;
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
                    (SzDuel_GetField(x, y) != 9 ||
                     Ta_IsVirus_Chk3(pInput, x, y) != 1) &&
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

typedef struct {
    u8 low : 4;
    u8 high : 4;
} Flags_001291C0;

typedef struct {
    u16 id;
    u8 action;
    u8 pad3;
    u16 position;
    u8 pad6[6];
    s32 value;
    u8 mode;
} Output_001291C0;

/* The task of a unit running from danger (task `pTask`): the safest square in reach, into `pInput` (`fFirst` = 1
   for the unit's first-choice task). */
s32 TaLogic_Necromancer_GetMinimumTask_RunMission(UnitTask *pTask, s32 nSide, void *pInput, u8 fFirst) {
    extern s32 TaLogic_IsRunPassRoot(s32, s32, s32, s32, s32, s32, void *, u8);
    extern s32 TaLogic_Necromancer_IsOpenUnit();
    s32 position;
    u8 upperX;
    u8 flag;
    Flags_001291C0 cells[12];
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
    Output_001291C0 *out = pInput;

    position = SzDuel_GetUnitLoc(pTask->ownerId >> 8, pTask->ownerId & 0xFF);
    i = 0;
    do {
        cells[i].low = cells[i].high = 15;
        i++;
    } while (i < 12);

    {
        u16 value = (u16)TaLogic_Necromancer_GetWarnHideLvl(nSide);
        originalX = position & 0xFF;
        originalY = position >> 8;
        if (TaLogic_GetUnitWarning(originalX, originalY, pTask->ownerId, 3, value, 0) == 0) {
            out->id = pTask->ownerId;
            out->action = 6;
            out->position = position;
            out->mode = TaLogic_IsDefStyleUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, out->position, 1, 0);
            out->value = TaLogic_Necromancer_IsOpenUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, pTask);
            TaLogic006_InitRogicControl(pTask, fFirst);
            return 0;
        } else {
            result = GetMoveRange(SzDuel_GetUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF), originalX, originalY);
            if (result == 0) {
                out->id = pTask->ownerId;
                out->action = 6;
                out->position = position;
                out->mode = TaLogic_IsDefStyleUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, out->position, 1, 0);
                out->value = TaLogic_Necromancer_IsOpenUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, pTask);
                TaLogic006_InitRogicControl(pTask, fFirst);
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
                                value = (u16)TaLogic_Necromancer_GetWarnHideLvl(nSide);
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
                    out->value = TaLogic_Necromancer_IsOpenUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, pTask);
                } else {
                    out->id = pTask->ownerId;
                    out->action = 6;
                    out->position = position;
                    out->mode = TaLogic_IsDefStyleUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, out->position, 1, 0);
                    out->value = TaLogic_Necromancer_IsOpenUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, pTask);
                }
                TaLogic006_InitRogicControl(pTask, fFirst);
            }
        }
    }
    return 0;
}

typedef struct Coord_00129700 {
    u8 x : 4;
    u8 y : 4;
} Coord_00129700;

typedef struct Result_00129700 {
    u16 card;
    u8 action;
    u8 pad03;
    u16 position;
    u8 pad06[6];
    s32 count;
    u8 flags;
} Result_00129700;

/* The task of reviving a monster from the graveyard (task `pTask`), into `pInput` (`fFirst` = 1 for the unit's
   first-choice task). */
s32 TaLogic_Necromancer_GetMinimumTask_ReviveMission(UnitTask *pTask, s32 nSide, s32 pInput, u8 fFirst) {
    extern s32 TaLogic_IsRunPassRoot(s32, s32, s32, s32, s32, s32, void *, u8);
    Coord_00129700 positions[12];
    s32 i;
    Coord_00129700 *p;
    s32 position;

    position = SzDuel_GetUnitLoc(pTask->ownerId >> 8, pTask->ownerId & 0xFF);
    p = positions;
    i = 0;
    do {
        p->x = p->y = 15;
        i++;
        p++;
    } while (i < 12);
    if (TaLogic_Necromancer_IsOpenUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, pTask) == 1) {
        s32 data;
        s32 card;
        s32 player;

        data = TaLogic_GetMaxAPGraveCard(nSide, 3);
        player = data >> 24;
        card = TaLogic_GetGraveEntryAfterScreen(player & 0xFF, (data >> 16) & 0xFF, 29);
        ((Result_00129700 *)pInput)->card = pTask->ownerId;
        ((Result_00129700 *)pInput)->action = 12;
        ((Result_00129700 *)pInput)->flags = TaLogic_IsDefStyleUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, *(u16 *)(pInput + 4), 1, 0);
        ((Result_00129700 *)pInput)->count = 1;
        *(u16 *)(pInput + 4) = ((player & 15) << 8) | card;
        TaLogic006_InitRogicControl(pTask, fFirst);
        return 0;
    }
    if (SzDuel_GetUnitStatus(pTask->ownerId >> 8, pTask->ownerId & 0xFF, 4) != 0) {
        SzDuel_SetUnitStatus(pTask->ownerId >> 8, pTask->ownerId & 0xFF, 0, 1);
        ((Result_00129700 *)pInput)->card = pTask->ownerId;
        ((Result_00129700 *)pInput)->action = 14;
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

        card = TaLogic_Necromancer_GetWarnHideLvl(nSide);
        centerX = position & 0xFF;
        centerY = position >> 8;
        if (TaLogic_GetUnitWarning(centerX, centerY, pTask->ownerId, 3, card, 0) == 0) {
            ((Result_00129700 *)pInput)->card = pTask->ownerId;
            ((Result_00129700 *)pInput)->action = 6;
            *(u16 *)(pInput + 4) = position;
            ((Result_00129700 *)pInput)->flags = TaLogic_IsDefStyleUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, *(u16 *)(pInput + 4), 1, 0);
            ((Result_00129700 *)pInput)->count = 2;
            TaLogic006_InitRogicControl(pTask, fFirst);
        } else {
            rangeResult = GetMoveRange(SzDuel_GetUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF), centerX, centerY);
            if (rangeResult == 0) {
                ((Result_00129700 *)pInput)->card = pTask->ownerId;
                ((Result_00129700 *)pInput)->action = 6;
                *(u16 *)(pInput + 4) = position;
                ((Result_00129700 *)pInput)->flags = TaLogic_IsDefStyleUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, *(u16 *)(pInput + 4), 1, 0);
                ((Result_00129700 *)pInput)->count = 2;
                TaLogic006_InitRogicControl(pTask, fFirst);
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
                                card = TaLogic_Necromancer_GetWarnHideLvl(nSide);
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
                    ((Result_00129700 *)pInput)->card = pTask->ownerId;
                    ((Result_00129700 *)pInput)->action = 6;
                    *(u16 *)(pInput + 4) = bestPosition;
                    if (bestPosition == position) {
                        ((Result_00129700 *)pInput)->flags = TaLogic_IsDefStyleUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, *(u16 *)(pInput + 4), 1, 0);
                    } else {
                        ((Result_00129700 *)pInput)->flags = TaLogic_IsDefStyleUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, *(u16 *)(pInput + 4), 0, 0);
                    }
                    ((Result_00129700 *)pInput)->count = 2;
                } else {
                    ((Result_00129700 *)pInput)->card = pTask->ownerId;
                    ((Result_00129700 *)pInput)->action = 6;
                    *(u16 *)(pInput + 4) = position;
                    ((Result_00129700 *)pInput)->flags = TaLogic_IsDefStyleUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, *(u16 *)(pInput + 4), 1, 0);
                    ((Result_00129700 *)pInput)->count = 2;
                }
                TaLogic006_InitRogicControl(pTask, fFirst);

            }
        }
    }
    return 0;
}

typedef struct {
    u16 position;
    u8 pad2[6];
    u32 targets;
} Input_00129D00;

typedef struct {
    u16 position;
    s8 action;
    u8 pad3;
    u16 destination;
    u8 pad6[6];
    s32 result;
    s8 status;
} Output_00129D00;

typedef struct {
    u8 x : 4;
    u8 y : 4;
} Point_00129D00;

#define TARGET_00129D00(in, mode) ((mode) == 1 ? (u16)((in)->targets >> 16) : (in)->targets & 0xFFFF)

/* The task of a unit attacking (task `pTask`): its path to the goal, into `pInput`; -1 when it has none (`fFirst`
   = 1 for the unit's first-choice task). */
s32 TaLogic_Necromancer_GetMinimumTask_AtkMission(void *pTask, s32 nSide, void *pInput, u8 fFirst) {
    extern void TaLogic_GetInvadeRoot();
    Input_00129D00 *in = pTask;
    Output_00129D00 *out = pInput;
    s32 sourcePosition;
    s32 count;
    s32 sourceY;
    s32 sourceX;
    s32 found;
    Point_00129D00 points[12];
    s32 targetPosition;
    s32 i;
    Point_00129D00 *p;

    if (SzDuel_GetUnit(TARGET_00129D00(in, fFirst) >> 8, TARGET_00129D00(in, fFirst) & 0xFF) == 0) {
        TaLogic_InitRogicControl(pTask, 1);
        return -1;
    } else {
        s32 initialResult;
        initialResult = TaLogic_Necromancer_IsOpenUnit(in->position >> 8, in->position & 0xFF, pTask);
        sourcePosition = SzDuel_GetUnitLoc(in->position >> 8, in->position & 0xFF);
        targetPosition = SzDuel_GetUnitLoc(TARGET_00129D00(in, fFirst) >> 8, TARGET_00129D00(in, fFirst) & 0xFF);
        p = points;
        i = 0;
        do {
            p->x = p->y = 15;
            p++;
            i++;
        } while (i < 12);
        if (GetMoveRange(SzDuel_GetUnit(in->position >> 8, in->position & 0xFF),
                          sourceX = sourcePosition & 0xFF, sourceY = sourcePosition >> 8) == 0) {
            s32 score;
            out->position = in->position;
            out->action = 6;
            out->destination = sourcePosition;
            score = TaLogic_GetUnitWarning(sourceX, sourceY, nSide, 3, 1, (u8)TaLogic_Necromancer_GetWarnHideLvl(nSide));
            if (score >= SzDuel_GetUnitAP(in->position >> 8, in->position & 0xFF, 0)) {
                out->status = TaLogic_IsDefStyleUnit(in->position >> 8, in->position & 0xFF, out->destination, 1, 0);
            } else {
                out->status = TaLogic_IsDefStyleUnit(in->position >> 8, in->position & 0xFF, out->destination, 0, 0);
            }
            TaLogic006_InitRogicControl(pTask, fFirst);
            return 0;
        } else {
            s32 targetY;
            s32 targetX;
            Point_00129D00 *candidate;
            s32 index;
            s32 bestScore;
            s32 bestIndex;
            s32 position = in->position;
            u16 value = TaLogic_Necromancer_GetWarnHideLvl(nSide);
            TaLogic_GetInvadeRoot(position >> 8, position & 0xFF, points, sourceX, sourceY,
                           targetX = targetPosition & 0xFF, targetY = targetPosition >> 8,
                           TARGET_00129D00(in, fFirst), 0, 30, value);
            count = TaLogic_GetMinGoalCount((u8 *)points);
            bestIndex = 0xFF;
            if (count > 0) {
                found = 0;
                bestScore = 0xFFFF;
                for (index = 0; index < count; index++) {
                    if (TaLogic006_IsOpenMoveUnit(in->position >> 8, in->position & 0xFF,
                                      sourceX, sourceY, targetX, targetY) == 1) {
                        bestIndex = index;
                        found = 1;
                        points[index].x = targetX;
                        points[index].y = targetY;
                        index = count;
                    } else {
                        s32 score;
                        candidate = &points[index];
                        score = TaLogic_GetUnitWarning(candidate->x, candidate->y, nSide, 5, 1,
                                              (u8)TaLogic_Necromancer_GetWarnHideLvl(nSide));
                        if (score < bestScore) {
                            bestScore = score;
                            bestIndex = index;
                        } else if (score == bestScore) {
                            if ((((targetX < candidate->x ? candidate->x : targetX) - (candidate->x < targetX ? candidate->x : targetX)) +
                                 ((targetY < candidate->y ? candidate->y : targetY) - (candidate->y < targetY ? candidate->y : targetY))) <
                                (((targetX < points[bestIndex].x ? points[bestIndex].x : targetX) - (points[bestIndex].x < targetX ? points[bestIndex].x : targetX)) +
                                 ((targetY < points[bestIndex].y ? points[bestIndex].y : targetY) - (points[bestIndex].y < targetY ? points[bestIndex].y : targetY)))) {
                                bestScore = score;
                                bestIndex = index;
                            }
                        }
                    }
                }
            } else {
                out->position = in->position;
                out->action = 6;
                out->destination = sourcePosition;
                out->result = initialResult;
                out->status = TaLogic_IsDefStyleUnit(in->position >> 8, in->position & 0xFF, out->destination, 0, 0);
                TaLogic_InitRogicControl(pTask, fFirst);
                return 0;
            }
            if (bestIndex != 0xFF) {
                out->position = in->position;
                out->action = 6;
                out->destination = (points[bestIndex].y << 8) | points[bestIndex].x;
                out->result = found;
                out->status = TaLogic_IsDefStyleUnit(in->position >> 8, in->position & 0xFF, out->destination, 0, 0);
            } else {
                out->position = in->position;
                out->action = 6;
                out->destination = sourcePosition;
                out->result = found;
                out->status = TaLogic_IsDefStyleUnit(in->position >> 8, in->position & 0xFF, out->destination, 0, 0);
                TaLogic_InitRogicControl(pTask, fFirst);
                return 0;
            }
        }
    }
    return 0;
}

typedef struct Coord_0012A2E0 {
    u8 x : 4;
    u8 y : 4;
} Coord_0012A2E0;

typedef struct Unit_0012A2E0 {
    u16 position;
    u8 pad2[6];
    union {
        u32 packed;
        u16 low;
    } target;
} Unit_0012A2E0;

typedef struct Output_0012A2E0 {
    u16 position;
    u8 kind;
    u8 pad3;
    u16 target;
    u8 pad6[6];
    s32 value;
    u8 flag;
} Output_0012A2E0;

/* The task's target square: the second half-word when the second argument is 1, else the first. */
static inline u32 target_0012A2E0(void *unit, s32 side) {
    return side == 1 ? (u32)(u16)(((Unit_0012A2E0 *)unit)->target.packed >> 16) : (u32)((Unit_0012A2E0 *)unit)->target.low;
}

/* The smaller of the two values. */
static inline u32 minY_0012A2E0(void *unit, s32 side, u8 coord) {
    return coord < (target_0012A2E0(unit, side) >> 8) ? coord : (target_0012A2E0(unit, side) >> 8);
}

/* The larger of the two values. */
static inline u32 maxY_0012A2E0(void *unit, s32 side, u8 coord) {
    return (target_0012A2E0(unit, side) >> 8) < coord ? coord : (target_0012A2E0(unit, side) >> 8);
}

/* The smaller of the two values. */
static inline u32 minX_0012A2E0(void *unit, s32 side, u8 coord) {
    return coord < (target_0012A2E0(unit, side) & 0xFF) ? coord : (target_0012A2E0(unit, side) & 0xFF);
}

/* The larger of the two values. */
static inline u32 maxX_0012A2E0(void *unit, s32 side, u8 coord) {
    return (target_0012A2E0(unit, side) & 0xFF) < coord ? coord : (target_0012A2E0(unit, side) & 0xFF);
}

/* The task of a unit moving to its goal (task `pTask`), into `pInput` (`fFirst` = 1 for the unit's first-choice
   task). */
s32 TaLogic_Necromancer_GetMinimumTask_MoveMission(void *pTask, s32 nSide, void *pInput, u8 fFirst, u8 nKind) {
    extern s32 TaLogic_GetUnitWarning();
    extern void TaLogic_GetRoot();
    extern s32 TaLogic_IsDefStyleUnit(s32, s32, s32, u8, s32);
    Coord_0012A2E0 coords[12];
    s32 initial;
    s32 cell;
    s32 count;

    initial = SzDuel_GetUnitLoc(((Unit_0012A2E0 *)pTask)->position >> 8, ((Unit_0012A2E0 *)pTask)->position & 0xFF);
    {
    s32 bestScore;
    s32 best;
    s32 side = fFirst;
    Coord_0012A2E0 *candidate;
    s32 index;
    if (target_0012A2E0(pTask, side) == 0xFFFF) {
        if (initial == target_0012A2E0(pTask, side)) {
            ((Output_0012A2E0 *)pInput)->position = ((Unit_0012A2E0 *)pTask)->position;
            ((Output_0012A2E0 *)pInput)->kind = 6;
            ((Output_0012A2E0 *)pInput)->target = initial;
            ((Output_0012A2E0 *)pInput)->flag = TaLogic_IsDefStyleUnit(((Unit_0012A2E0 *)pTask)->position >> 8, ((Unit_0012A2E0 *)pTask)->position & 0xFF, ((Output_0012A2E0 *)pInput)->target, nKind, 0);
            ((Output_0012A2E0 *)pInput)->value = TaLogic_Necromancer_IsOpenUnit(((Unit_0012A2E0 *)pTask)->position >> 8, ((Unit_0012A2E0 *)pTask)->position & 0xFF, pTask);
            TaLogic006_InitRogicControl(pTask, fFirst);
            return 0;
        }
    }

    candidate = coords;
    {
        s32 i = 0;
        Coord_0012A2E0 *entry = candidate;
        do {
            entry->x = entry->y = 0xF;
            i++;
            entry++;
        } while (i < 12);
    }

    cell = SzDuel_GetMapUnitID(target_0012A2E0(pTask, side) & 0xFF, ((u32)target_0012A2E0(pTask, side)) >> 8);
    if (cell < 0) {
        cell = 0xFFFF;
    }
    TaLogic_GetRoot(((Unit_0012A2E0 *)pTask)->position >> 8, ((Unit_0012A2E0 *)pTask)->position & 0xFF,
                 coords, initial & 0xFF, initial >> 8, target_0012A2E0(pTask, side) & 0xFF,
                 ((u32)target_0012A2E0(pTask, side)) >> 8, (u16)cell, 7);
    count = TaLogic_GetMinGoalCount((u8 *)coords);
    {
        if (count > 0) {
        best = 0xFF;
        bestScore = 0xFFFF;
        for (index = 0; index < count; index++) {
                if (SzDuel_GetMapUnit(candidate->x, candidate->y) == 0) {
                    s32 score = TaLogic_GetUnitWarning(candidate->x, candidate->y, nSide, 5, 1, (u8)TaLogic_Necromancer_GetWarnHideLvl(nSide));
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
                        bestMinY = minY_0012A2E0(pTask, side, bestY);
                        bestMaxY = maxY_0012A2E0(pTask, side, bestY);
                        bestX = (&coords[best])->x;
                        bestMinX = minX_0012A2E0(pTask, side, bestX);
                        bestMaxX = maxX_0012A2E0(pTask, side, bestX);
                        currentY = (u8)candidate->y;
                        currentMinY = minY_0012A2E0(pTask, side, currentY);
                        currentMaxY = maxY_0012A2E0(pTask, side, currentY);
                        currentX = candidate->x;
                        currentMinX = minX_0012A2E0(pTask, side, currentX);
                        currentMaxX = maxX_0012A2E0(pTask, side, currentX);
                        if ((currentMaxX - currentMinX) + (currentMaxY - currentMinY) < (bestMaxX - bestMinX) + (bestMaxY - bestMinY)) {
                            bestScore = score;
                            best = index;
                        }
                    }
                }
            candidate++;
        }
    } else {
        ((Output_0012A2E0 *)pInput)->position = ((Unit_0012A2E0 *)pTask)->position;
            ((Output_0012A2E0 *)pInput)->kind = 6;
            ((Output_0012A2E0 *)pInput)->target = initial;
            ((Output_0012A2E0 *)pInput)->flag = TaLogic_IsDefStyleUnit(((Unit_0012A2E0 *)pTask)->position >> 8, ((Unit_0012A2E0 *)pTask)->position & 0xFF, ((Output_0012A2E0 *)pInput)->target, nKind, 0);
            ((Output_0012A2E0 *)pInput)->value = TaLogic_Necromancer_IsOpenUnit(((Unit_0012A2E0 *)pTask)->position >> 8, ((Unit_0012A2E0 *)pTask)->position & 0xFF, pTask);
        TaLogic006_InitRogicControl(pTask, fFirst);
        return 0;
    }

        if (best != 0xFF) {
            ((Output_0012A2E0 *)pInput)->position = ((Unit_0012A2E0 *)pTask)->position;
            ((Output_0012A2E0 *)pInput)->kind = 6;
            ((Output_0012A2E0 *)pInput)->target = (coords[best].y << 8) | coords[best].x;
            ((Output_0012A2E0 *)pInput)->flag = TaLogic_IsDefStyleUnit(((Unit_0012A2E0 *)pTask)->position >> 8, ((Unit_0012A2E0 *)pTask)->position & 0xFF, ((Output_0012A2E0 *)pInput)->target, nKind, 0);
            ((Output_0012A2E0 *)pInput)->value = TaLogic_Necromancer_IsOpenUnit(((Unit_0012A2E0 *)pTask)->position >> 8, ((Unit_0012A2E0 *)pTask)->position & 0xFF, pTask);
        } else {
            ((Output_0012A2E0 *)pInput)->position = ((Unit_0012A2E0 *)pTask)->position;
            ((Output_0012A2E0 *)pInput)->kind = 6;
            ((Output_0012A2E0 *)pInput)->target = initial;
            ((Output_0012A2E0 *)pInput)->flag = TaLogic_IsDefStyleUnit(((Unit_0012A2E0 *)pTask)->position >> 8, ((Unit_0012A2E0 *)pTask)->position & 0xFF, ((Output_0012A2E0 *)pInput)->target, nKind, 0);
            ((Output_0012A2E0 *)pInput)->value = TaLogic_Necromancer_IsOpenUnit(((Unit_0012A2E0 *)pTask)->position >> 8, ((Unit_0012A2E0 *)pTask)->position & 0xFF, pTask);
        }
        TaLogic006_InitRogicControl(pTask, fFirst);
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
} Source_0012AAC0;

typedef struct {
    u16 position;
    u8 action;
    u8 pad3;
    u16 target;
    u8 pad6[10];
    s8 result;
} Action_0012AAC0;

typedef struct {
    u8 x : 4;
    u8 y : 4;
} Point_0012AAC0;

#define MIN_0012AAC0(a, b) ((a) < (b) ? (a) : (b))
#define MAX_0012AAC0(a, b) ((b) < (a) ? (a) : (b))

/* The task's target square: the second half-word when the second argument is 1, else the first. */
static inline u32 target_0012AAC0(void *arg0, s32 mode) {
    Source_0012AAC0 *source = arg0;
    if (mode == 1) {
        return (u16)(source->target.both >> 16);
    }
    return source->target.half[0];
}

/* Sets a move task (action 6) to the given square, and whether the unit should stay in defence there. */
static inline void fill_0012AAC0(void *arg0, void *arg2, s32 target, s32 flag) {
    Source_0012AAC0 *source = arg0;
    Action_0012AAC0 *action = arg2;
    action->position = source->position;
    action->action = 6;
    action->target = target;
    action->result = TaLogic_IsDefStyleUnit(source->position >> 8,
        source->position & 0xFF, action->target, flag, 0);
}

/* The task of setting a trap (task `pTask`), into `pInput`. */
s32 TaLogic_Necromancer_GetMinimumTask_TrapMission(void *pTask, s32 nSide, void *pInput, s32 fFirst) {
    s32 start;
    s32 count;
    s32 startY;
    Point_0012AAC0 points[16];
    s32 bestScore;
    Point_0012AAC0 *p;
    s32 targetY;
    s32 targetX;
    s32 i;
    s32 bestIndex;
    s32 mode;
    s32 target;
    s32 startX;
    u32 xPosition;
    u32 yPosition;
    Source_0012AAC0 *source = pTask;
    Action_0012AAC0 *action = pInput;
    extern void TaLogic_GetInvadeRoot();

    mode = fFirst & 0xFF;
    xPosition = target_0012AAC0(pTask, mode);
    yPosition = target_0012AAC0(pTask, mode);
    if (SzDuel_GetUnit(yPosition >> 8, xPosition & 0xFF) == 0) {
        TaLogic_InitRogicControl(pTask, 1);
        return -1;
    }
    start = SzDuel_GetUnitLoc(source->position >> 8, source->position & 0xFF);
    xPosition = target_0012AAC0(pTask, mode);
    yPosition = target_0012AAC0(pTask, mode);
    target = SzDuel_GetUnitLoc(yPosition >> 8, xPosition & 0xFF);
    if (target_0012AAC0(pTask, mode) == 0xFFFF) {
        fill_0012AAC0(pTask, pInput, start, 1);
        return 0;
    } else {
        s32 unit = SzDuel_GetUnit(source->position >> 8, source->position & 0xFF);
        startX = start & 0xFF;
        startY = start >> 8;
        if (GetMoveRange(unit, startX, startY) == 0 ||
                TaLogic_IsAttackedNow(source->position >> 8, source->position & 0xFF, 0) == 1) {
            fill_0012AAC0(pTask, pInput, start, 1);
            return 0;
        } else {
            p = points;
            {
                s32 n = 0;
                Point_0012AAC0 *q = p;
                do {
                    q->x = q->y = 0xF;
                    q++;
                    n++;
                } while (n < 12);
            }
            {
                s32 position = source->position;
                u16 card = (u16)TaLogic_Necromancer_GetWarnHideLvl(nSide);
                TaLogic_GetInvadeRoot(position >> 8, position & 0xFF, points,
                    startX, startY, targetX = target & 0xFF,
                    targetY = target >> 8, target_0012AAC0(pTask, mode),
                    0, 30, card);
            }
            count = TaLogic_GetMinGoalCount((u8 *)points);
            bestIndex = 0xFF;
            if (count > 0) {
                bestScore = 0;
                for (i = 0; i < count; i++, p++) {
                    if (SzDuel_GetMapUnit(p->x, p->y) == 0) {
                        s32 score = TaLogic_GetUnitWarning(p->x, p->y, nSide, 5, 1,
                            TaLogic_Necromancer_GetWarnHideLvl(nSide) & 0xFF);
                        if (bestScore < score) {
                            bestScore = score;
                            bestIndex = i;
                        } else if (score == bestScore) {
                            if (MAX_0012AAC0(p->x, targetX) - MIN_0012AAC0(p->x, targetX)
                                    + (MAX_0012AAC0(p->y, targetY) - MIN_0012AAC0(p->y, targetY))
                                    < MAX_0012AAC0(points[bestIndex].x, targetX) - MIN_0012AAC0(points[bestIndex].x, targetX)
                                    + (MAX_0012AAC0(points[bestIndex].y, targetY) - MIN_0012AAC0(points[bestIndex].y, targetY))) {
                                bestScore = score;
                                bestIndex = i;
                            }
                        }
                    }
                }
            } else {
                fill_0012AAC0(pTask, pInput, start, 1);
                return 0;
            }
            if (bestIndex != 0xFF) {
                action->position = source->position;
                action->action = 6;
                action->target = (points[bestIndex].y << 8) | points[bestIndex].x;
                action->result = TaLogic_IsDefStyleUnit(source->position >> 8,
                    source->position & 0xFF, action->target, 0, 0);
            } else {
                fill_0012AAC0(pTask, pInput, start, 1);
                return 0;
            }
        }
    }
    return 0;
}

/* The opponent's strongest unit that side `side`'s strongest unit cannot beat, or -1. */
s32 func_0012B000(s32 side) {
    s32 i;
    s32 n;
    s32 ownLow;
    s32 enemyAP;
    s32 enemy;
    s32 low;
    s32 own;
    s32 ownCol;
    s32 col;
    u16 list[22];

    n = 0;
    for (i = 0; i < 22; i++) {
        list[i] = 0xFFFF;
    }
    TaLogic_GetUnitCtlLst2(side == 0 ? 1 : 0, list, 0x1D, 0, 0);
    enemy = TaLogic_GetMaxApUnit(list);
    for (i = 0; i < 22; i++) {
        list[i] = 0xFFFF;
    }
    TaLogic_GetUnitCtlLst2(side, list, 0x1D, 1, 1);
    own = TaLogic_GetMaxApUnit(list);
    col = enemy & 0xFF;
    enemy = enemy >> 8;
    low = SzDuel_GetUnitLoc(enemy, col) & 0xFF;
    enemyAP = TaUtil_GetUnitAP(enemy, col, low, SzDuel_GetUnitLoc(enemy, col) >> 8);
    ownCol = own & 0xFF;
    own = own >> 8;
    ownLow = SzDuel_GetUnitLoc(own, ownCol) & 0xFF;
    if (TaUtil_GetUnitAP(own, ownCol, ownLow, SzDuel_GetUnitLoc(own, ownCol) >> 8) < enemyAP) {
        if (enemyAP >= 3000) {
            for (i = 1; i < 11; i++) {
                if (SzDuel_GetUnit(side, i) != 0) {
                    n++;
                }
            }
        }
    }
    return n < 3 ? 1 : 0;
}

/* How careful this duelist is about hidden cards (by its life points and monster count). */
s32 TaLogic_Necromancer_GetWarnHideLvl(s32 nSide) {
    if (SzDuel_GetLP(nSide) > 0x4B0) {
        if (SzDuel_GetUnitMonsterCount(nSide) >= 4) {
            return 0x3E8;
        }
        return 0x7D0;
    }
    return 0x960;
}

/* Whether this duelist opens (turns face up) unit (nSide, nID) now: 0 no, 1 or 2 by its kind. */
s32 TaLogic_Necromancer_IsOpenUnit(s32 nSide, s32 nID, void *pInfo) {
    extern s32 SzDuel_GetUnitCardNo();
    extern s32 func_0012B000();
    s32 card;
    s32 position;
    s32 owner;
    s32 value;
    u8 count;

    card = SzDuel_GetUnitCardNo(nSide, nID);
    owner = Ta_IsUnitControl(nSide, nID);
    position = SzDuel_GetUnitLoc(nSide, nID);
    count = 0;
    if (SzDuel_GetUnitStatus(nSide, nID, 4) != 0) {
        return 0;
    }
    switch (SzDuel_GetUnitKind(nSide, nID) >> 5) {
    case 0:
        switch (card) {
        case 0x65:
            for (card = 1; card <= 5; card++) {
                if (SzDuel_GetUnitCardNo(nSide, card) == 0x65 && nSide == Ta_IsUnitControl(nSide, card)) {
                    count++;
                }
                if (SzDuel_GetUnitCardNo((nSide == 0) ? 1 : 0, card) == 0x65 &&
                    nSide == Ta_IsUnitControl((nSide == 0) ? 1 : 0, card)) {
                    count++;
                }
            }
            if (count >= 2) {
                return 1;
            }
            break;
        case 0x66:
            for (card = 1; card <= 5; card++) {
                if (SzDuel_GetUnitCardNo(nSide, card) == 0x66 && nSide == Ta_IsUnitControl(nSide, card)) {
                    count++;
                }
                if (SzDuel_GetUnitCardNo((nSide == 0) ? 1 : 0, card) == 0x66 &&
                    nSide == Ta_IsUnitControl((nSide == 0) ? 1 : 0, card)) {
                    count++;
                }
            }
            if (count >= 2) {
                return 1;
            }
            break;
        case 0x6C:
            return 1;
        case 0x77:
            for (card = 1; card <= 5; card++) {
                if (SzDuel_GetUnitCardNo(nSide, card) == 0x77 && nSide == Ta_IsUnitControl(nSide, card)) {
                    count++;
                }
                if (SzDuel_GetUnitCardNo((nSide == 0) ? 1 : 0, card) == 0x77 &&
                    nSide == Ta_IsUnitControl((nSide == 0) ? 1 : 0, card)) {
                    count++;
                }
            }
            if (count >= 2) {
                return 1;
            }
            break;
        }
        return 2;
    case 5:
        if (TaLogic006_IsDoCerem(Ta_IsUnitControl(nSide, nID), card) == 1 &&
            SzDuel_GetField(position & 0xFF, position >> 8) != 9) {
            return 1;
        }
        break;
    case 1:
        if (TaLogic_GetActionReaction(nSide, nID, 0, 0, 6, 0) == 5) {
            return 2;
        }
        switch (SzDuel_GetUnitCardNo(nSide, nID)) {
        case 0x2BB:
            if (TaLogic_IsAttackedNow(nSide, 0, 0) == 1 || func_0012B000(nSide) == 1) {
                return 1;
            }
            break;
        case 0x2AD:
            value = TaLogic_GetMaxAPGraveCard(nSide, 3);
            if (value >= 0 && (u16)value >= 0x960 && SzDuel_GetUnitMonsterCount(nSide) < 5 &&
                SzDuel_GetField(position & 0xFF, position >> 8) != 9) {
                return 1;
            }
            break;
        case 0x2E9:
            for (card = 1; card <= 5; card++) {
                if (SzDuel_GetUnit(nSide, card) != 0 && (SzDuel_GetUnitKind(nSide, card) & 0x1F) != 2 &&
                    nSide == Ta_IsUnitControl(nSide, card)) {
                    count++;
                }
                if (SzDuel_GetUnit((nSide == 0) ? 1 : 0, card) != 0 &&
                    (SzDuel_GetUnitKind((nSide == 0) ? 1 : 0, card) & 0x1F) != 2 &&
                    nSide == Ta_IsUnitControl((nSide == 0) ? 1 : 0, card)) {
                    count++;
                }
            }
            if (count >= 3) {
                return 1;
            }
            break;
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

/* The larger of the two values. */
static inline s32 max_0012B730(s32 a, s32 b) {
    s32 maximum;

    if (a < b) {
        maximum = b;
    } else {
        maximum = a;
    }
    return maximum;
}

/* Whether unit (nSide, nID) may open while moving from (nX, nZ) to the square next to it, (gX, gZ). */
s32 TaLogic006_IsOpenMoveUnit(s32 nSide, s32 nID, s32 nX, s32 nZ, s32 gX, s32 gZ) {
    s32 min_y;
    s32 min_x;
    s32 result;
    s32 status;

    min_y = nZ < gZ ? nZ : gZ;
    gZ = max_0012B730(gZ, nZ);
    min_x = nX < gX ? nX : gX;
    gX = max_0012B730(gX, nX);
    if ((gX - min_x) + (gZ - min_y) != 2) {
        return 0;
    }
    if (SzDuel_GetUnit(nSide, nID) == 0) {
        return 0;
    }
    if (SzDuel_GetUnitStatus(nSide, nID, 0) == 0) {
        status = CheckLandAgreement2(SzDuel_GetField(nX, nZ), nSide, nID);
        result = 1;
        if (status != 1) {
            return 0;
        }
        return result;
    }
    return 0;
}

typedef struct {
    u8 pad0[4];
    u16 value4;
    u8 pad6[2];
    u32 value8;
} Data_0012B830;

/* Clears a unit's task (`Is1st` on its first turn). */
void TaLogic006_InitRogicControl(void *pUnit, u8 Is1st) {
    Data_0012B830 *data = pUnit;

    if (Is1st < 2) {
        if (Is1st == 1) {
            data->value4 = (data->value4 & 0xFF) | 0xFF00;
        } else {
            data->value4 = (data->value4 & 0xFF00) | 0xFF;
        }
        if (Is1st == 1) {
            data->value8 = (data->value8 & 0xFFFF) | 0xFFFF0000;
        } else {
            data->value8 = (data->value8 & 0xFFFF0000) | 0xFFFF;
        }
    }
}

/* Whether side `nSide` can play ritual card `nCardNo` now (it has the units to give up). */
s32 TaLogic006_IsDoCerem(s32 nSide, s32 nCardNo) {
    s32 sp50[3];
    s32 i;
    s32 temp_v0;
    s32 unitSlot;
    s32 unitSide;
    s32 unitId;
    s32 loc;

    Ta_GetCeremSacrifice(sp50, *(s32 *)((u8 *)TaHand_GetCardEffect(nCardNo, 0) + 4));
    if ((temp_v0 = Ta_GetSacrificeUnit(sp50, nSide)) < 0) {
        return 0;
    }
    i = 0;
    if (i < Ta_GetUnitNumFrom22bitFlagList(temp_v0)) {
        do {
            unitId = Ta_GetUnitOwnerIDFromLstCount(temp_v0, i);
            unitSide = unitId >> 8;
            unitSlot = unitId & 0xFF;
            loc = SzDuel_GetUnitLoc(unitSide, unitSlot);
            if (TaUtil_GetUnitAP(unitSide, unitSlot, loc & 0xFF, loc >> 8) >= 0x7D0) {
                return 0;
            }
            i++;
        } while (i < Ta_GetUnitNumFrom22bitFlagList(temp_v0));
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
} Req_0012B9A0;

typedef struct {
    u8 pad0[0x160];
    u16 list[32];    /* 0x160 */
    u8 idx : 5;      /* 0x1A0 */
    u8 pad1A0 : 3;
    u8 pad1A1;
    u16 count;       /* 0x1A2 */
} Work_0012B9A0;

/* Computer duelist 6's controller (duelistControllers[6]): the buttons it presses this frame. With an empty input
   queue it plans its next task and turns it into buttons, then plays the queue back one button per frame; after
   600 frames it gives up the turn (0x20, then 0x800). */
s32 duelistController06(s32 wCursorPos, void *pCtl) {
    Req_0012B9A0 req;
    Work_0012B9A0 *w;
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
        if (TaLogic_Necromancer_GetMinimumTask(w, &req, wCursorPos) == 0) {
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

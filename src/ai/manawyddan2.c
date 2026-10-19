/* Computer AI of Manawyddan fab Llyr, second form (duelist 21, duelistController21). */

#include "common.h"
#pragma conditional_move off

/* This duelist's move: picks the next unit to act, gives it a task and turns that into input `pInput`; returns 1
   when it set one. */
s32 TaLogic_Manawyddan2_GetMinimumTask(void *pCtl, void *pInput, s32 wCursorPos) {
    extern s32 TaLogic_Manawyddan2_GetWarnHideLvl(s32);
    UnitTask *tasks = pCtl;
    s32 side;
    s32 found;
    s32 result;
    s32 index;

    side = SzDuel_GetTurnOwner();
    found = 0;
    if ((result = TaLogic_Manawyddan2_GetNextActiveUnit(tasks, side, (s32)pInput)) < 0) {
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
    TaLogic_Manawyddan2_CommandUnit(&tasks[index]);
    switch ((tasks[index].mission >> 8) & 0xFF) {
    case TASK_RUN:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            TaLogic_Manawyddan2_GetMinimumTask_RunMission(&tasks[index], side, pInput, 1);
            found = 1;
        }
        break;
    case TASK_ATTACK:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            if (TaLogic_Manawyddan2_GetMinimumTask_AtkMission(&tasks[index], side, pInput, 1) < 0) {
                TaLogic_InitRogicControl(&tasks[index], 1);
                return 1;
            }
            found = 1;
        }
        break;
    case TASK_SUMMON:
        if (TaLogic_Manawyddan2_GetMinimumTask_Summon(tasks[index].ownerId, side, (s32)pInput) < 0) {
            TaLogic_InitRogicControl(&tasks[index], 1);
            *(u8 *)((u8 *)pInput + 2) = 0xFF;
            *(s32 *)((u8 *)pInput + 0xC) = 0;
        } else {
            TaLogic_InitRogicControl(&tasks[index], 1);
            found = 1;
        }
        break;
    case TASK_MOVETOLOCATION:
    case 16:
    case 15:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            TaLogic_Manawyddan2_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 1, 0);
            found = 1;
        }
        break;
    case TASK_ENCHANT:
        TaLogic_GetMinimumTask_EncMission(&tasks[index], side, pInput, 1, 1, TaLogic_Manawyddan2_GetWarnHideLvl(side), 4, 1);
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
    switch (tasks[index].mission & 0xFF) {
    case 5:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            TaLogic_Manawyddan2_GetMinimumTask_RunMission(&tasks[index], side, pInput, 0);
            found = 1;
        }
        break;
    case 2:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            if (TaLogic_Manawyddan2_GetMinimumTask_AtkMission(&tasks[index], side, pInput, 0) < 0) {
                TaLogic_Manawyddan2_GetMinimumTask_RunMission(&tasks[index], side, pInput, 0);
            }
            found = 1;
        }
        break;
    case 10:
        if (TaLogic_Manawyddan2_GetMinimumTask_Summon(tasks[index].ownerId, side, (s32)pInput) < 0) {
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
    case 16:
    case 15:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            TaLogic_Manawyddan2_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 0, 0);
            found = 1;
        }
        break;
    case 9:
        TaLogic_GetMinimumTask_EncMission(&tasks[index], side, pInput, 0, 1, TaLogic_Manawyddan2_GetWarnHideLvl(side), 4, 1);
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
    u16 unitId; /* (side << 8) | unit */
    u8 pad2[2];
    u16 state;
    u8 pad6[2];
    union {
        u32 word;
        struct {
            u16 low;
            u16 high;
        } halves;
    } data;
} Entry_00167D30;
#pragma conditional_move reset

/* Gives a unit of this duelist its order for this turn (attack, run, move, summon, guard). */
s32 TaLogic_Manawyddan2_CommandUnit(void *pCtl) {
    extern s32 TaLogic_Manawyddan2_GetWarnHideLvl(s32);
    Entry_00167D30 *entry = pCtl;
    u16 coord;
    s32 slot;
    s32 kind;

    SzDuel_GetUnitLoc(entry->unitId >> 8, entry->unitId & 0xFF);
    slot = Ta_IsUnitControl(entry->unitId >> 8, entry->unitId & 0xFF);
    if (SzDuel_GetUnit(entry->unitId >> 8, entry->unitId & 0xFF) != 0) {
        if (SzDuel_GetUnitStatus(entry->unitId >> 8, entry->unitId & 0xFF, 0) == 0) {
            coord = entry->unitId;
            if (coord != 0xFFFF) {
                if ((coord & 0xFF) == 0) {
                    if (entry->data.word == -1) {
                        TaLogic_CommandStdLDUnit(entry, 3, 1, 1);
                    }
                } else {
                    kind = SzDuel_GetUnitKind(coord >> 8, coord & 0xFF) >> 5;
                    switch (kind) {
                    case 0:
                        TaLogic021_CommandBtlUnit(entry, 1);
                        break;
                    case 2:
                        TaLogic_CommandEncUnit(entry, 4, 1, TaLogic_Manawyddan2_GetWarnHideLvl(slot) & 0xFF);
                        break;
                    default:
                        entry->state = 0x5FF;
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
s32 TaLogic_Manawyddan2_GetNextActiveUnit(u16 *pCtl, s32 nSide, s32 pInput) {
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
    for (i = 0; i < 22; i++) {
        list[i] = 0xFFFF;
    }
    TaLogic_GetUnitCtlLst(nSide, list, 0x1F, 1);
    for (i = 0; i < TaLogic_GetUnitCtlLstLen(list); i++) {
        if (TaLogic_IsUnitReadyMove(list[i]) == 1 && TaLogic_IsPickUp(list[i]) == 1) {
            return list[i];
        }
    }
    pos = nSide << 8;
    idx = TaLogic_GetActionUnitFromOwnerID(pCtl, pos);
    TaLogic_Manawyddan2_CommandUnit(pCtl + idx * 8);
    if (((pCtl[idx * 8 + 2] >> 8) & 0xFF) == 10) {
        if (SzDuel_InqHandPhase(nSide) == 1 && TaLogic_Manawyddan2_GetMinimumTask_Summon(pos, nSide, pInput) >= 0) {
            return pos | 0x10000;
        }
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_GetUnitStatus(nSide, 0, 0) == 0) {
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_InqHandPhase(nSide) == 1 && TaLogic_Manawyddan2_GetMinimumTask_Summon(pos, nSide, pInput) >= 0) {
        return pos | 0x10000;
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
} Entry_00168260;

typedef struct {
    u16 card;
    u8 flag;
    u8 pad;
} Slot_00168260;

/* Orders a fighting unit (task `pTask`): straight at the enemy leader when `fGoalFirst` and the path is open,
   else at the nearest enemy it can beat. */
void TaLogic021_CommandBtlUnit(void *pTask, s32 fGoalFirst) {
    extern void TaLogic_InitIgnoreLst();
    extern s32 TaLogic_IsRootOpen();
    extern s32 TaLogic021_GetNearUnit();
    extern s32 TaLogic_Manawyddan2_GetWarnHideLvl();
    Entry_00168260 *entry = pTask;
    s32 side;
    s32 player;
    s32 other;
    s32 pos;
    s32 otherPos;
    s32 i;
    u8 work[0x70];
    Slot_00168260 list[22];
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
            switch (TaLogic021_GetNearUnit(entry, 0, player, pos & 0xFF, pos >> 8,
                                  Ta_GetCurrentSide(entry->unitId >> 8, entry->unitId & 0xFF) == 0 ? 1 : 0,
                                  i & 0xFF, TaLogic_Manawyddan2_GetWarnHideLvl(side), list, 0, &countA, &countB, 4, work)) {
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
        TaLogic021_CommandInvadeUnit(entry);
    }
}

/* TaLogic_GetNearUnit with this duelist's view and strength settings. */
s32 TaLogic021_GetNearUnit(s32 pTask, s32 pTree, s32 pVarInfo, s32 nX, s32 nZ, s32 eSide, s32 bDist, s32 WarnLvl, s32 nUnitLst, u16 wUnitNum, s32 wSize, s32 wNodeCount, u8 bChase, s32 wIgnoreLst) {
    return TaLogic_GetNearUnit(pTask, pTree, pVarInfo, nX, nZ, eSide, bDist, WarnLvl,
                  nUnitLst, wUnitNum, wSize, wNodeCount, bChase,
                  1, 3000, wIgnoreLst);
}

/* Orders a unit (task `pTask`) to push into the opponent's side of the board. */
void TaLogic021_CommandInvadeUnit(u16 *pTask) {
    s32 owner;
    s32 result;
    s32 mode;
    s32 index;
    u16 id;

    id = pTask[0];
    owner = Ta_IsUnitControl(id >> 8, id & 0xFF);
    id = pTask[0];
    result = SzDuel_GetUnitLoc(id >> 8, id & 0xFF);
    mode = (pTask[2] >> 8) & 0xFF;
    if (mode == 0x10) {
        if ((result >> 8) == 6) {
            pTask[2] = 0xFFF;
            *(u32 *)(pTask + 4) = ((result & 0xFF) << 16) | pTask[4];
        } else {
            pTask[2] = 0x10FF;
            *(u32 *)(pTask + 4) = (((result & 0xFF) | 0x600) << 16) | pTask[4];
        }
    } else {
        if (mode == 0xF) {
            if ((result >> 8) == 0) {
                pTask[2] = 0x10FF;
                *(u32 *)(pTask + 4) = (((result & 0xFF) | 0x600) << 16) | pTask[4];
            } else {
                pTask[2] = 0xFFF;
                *(u32 *)(pTask + 4) = ((result & 0xFF) << 16) | pTask[4];
            }
        } else if ((result >> 8) < 4) {
            if ((result >> 8) == 0) {
                pTask[2] = 0x10FF;
                *(u32 *)(pTask + 4) = ((result & 0xFF) << 16) | pTask[4];
            } else {
                index = result & 0xFF;
                if (index == 3) {
                    pTask[2] = 0x6FF;
                    *(u32 *)(pTask + 4) = pTask[4] | 0x30000;
                } else if (index > 3) {
                    pTask[2] = 0x6FF;
                    *(u32 *)(pTask + 4) = pTask[4] | 0x60000;
                } else {
                    pTask[2] = 0x6FF;
                    *(u32 *)(pTask + 4) = pTask[4];
                }
            }
        } else if (SzDuel_GetMapUnit(3, 3) == 0) {
            pTask[2] = 0x6FF;
            *(u32 *)(pTask + 4) = pTask[4] | 0x03030000;
        } else if (SzDuel_GetMapUnit(2, 3) == 0) {
            pTask[2] = 0x6FF;
            *(u32 *)(pTask + 4) = pTask[4] | 0x03020000;
        } else if (SzDuel_GetMapUnit(2, 3) == 0) {
            pTask[2] = 0x6FF;
            *(u32 *)(pTask + 4) = pTask[4] | 0x03040000;
        } else {
            pTask[2] = 0x6FF;
            *(u32 *)(pTask + 4) = pTask[4] | (SzDuel_GetUnitLoc((owner == 0) ? 1 : 0, 0) << 16);
        }
    }
}

typedef struct {
    u8 pad00[0x3C];
    u16 unk3C;
    u8 pad3E[0x22];
} Work_001687A0;

typedef struct {
    u16 id;
    u8 unk2;
    u8 pad3;
    s16 unk4;
    u8 pad6[6];
    s32 unkC;
} Ctx_001687A0;

/* The summon task for side `nSide`: which hand cards to play and where, into `pInput`; -1 when it plays none. */
s32 TaLogic_Manawyddan2_GetMinimumTask_Summon(s32 wUnit, s32 nSide, s32 pInput) {
    extern s32 TaLogic_GetUnitNum();
    extern s32 TaLogic_Manawyddan2_GetWarnHideLvl();
    Work_001687A0 work;
    s32 ret;
    s32 res;
    s32 pos;
    s32 kind;
    Ctx_001687A0 *ctx = (Ctx_001687A0 *)pInput;

    ctx->id = wUnit;
    if (SzDuel_InqHandPhase(nSide) == 0) {
        return -1;
    }
    if (TaLogic_GetUnitNum(nSide, 0) == 5 && TaLogic_GetUnitNum(nSide, 1) == 5) {
        return -1;
    }
    kind = TaLogic021_IsHandPlay(nSide, &work);
    if (kind < 0) {
        return -1;
    }
    ctx->unk2 = 10;
    ctx->unkC = 0;
    pos = SzDuel_GetUnitLoc(wUnit >> 8, wUnit & 0xFF);
    if (kind == 0) {
        if (TaLogic021_SetComboQue(nSide, (u8 *)ctx, &work) >= 0) {
            ret = TaLogic_GetNearCard2(&work, pos & 0xFF, pos >> 8,
                                nSide == 0 ? 1 : 0, 2, 0x1F, 2, 2,
                                1, TaLogic_Manawyddan2_GetWarnHideLvl(nSide));
            if (ret < 0) {
                if (SzDuel_GetUnitMonsterCount(nSide) < 6) {
                    res = TaLogic021_GetSummonPiece(nSide, kind, &work, ret);
                    if (res < 0) {
                        return -1;
                    }
                    ctx->unk4 = res;
                    return 1;
                }
            } else {
                res = TaLogic021_GetSummonPiece(nSide, kind, &work, ret);
                if (res < 0) {
                    return -1;
                }
                ctx->unk4 = res;
                return 1;
            }
        }
    } else {
        ret = TaLogic_GetNearCard2(&work, pos & 0xFF, pos >> 8,
                            nSide == 0 ? 1 : 0, 2, 0x1F, 2, 2,
                            1, TaLogic_Manawyddan2_GetWarnHideLvl(nSide));
    }
    if (kind == 2) {
        TaLogic021_SetSpecialComboQue(nSide, ctx, &work);
        res = TaLogic021_GetSummonPiece(nSide, kind, &work, ret);
        if (res < 0) {
            return -1;
        }
        ctx->unk4 = res;
        return 1;
    }
    if (TaLogic021_GetSpellPlay(nSide, (u8 *)ctx, &work, work.unk3C) < 0) {
        return -1;
    }
    res = TaLogic021_GetSummonPiece(nSide, kind, &work, ret);
    if (res < 0) {
        return -1;
    }
    ctx->unk4 = res;
    return 1;
}

/* Whether side `nSide` should play from its hand this turn (and what, into `pInput`). */
s32 TaLogic021_IsHandPlay(s32 nSide, void *pInput) {
    extern s32 TaLogic_GetUnitNum();
    s32 cards[8];
    u8 buffer[32];
    u8 first;
    u8 second;

    first = (u8)TaLogic_GetUnitNum(nSide, 0);
    second = (u8)TaLogic_GetUnitNum(nSide, 1);
    if (pInput == NULL) {
        return -1;
    }
    TaHand_GetNextHand(nSide, cards);
    if (first == 5) {
        if (TaLogic021_GetSpellPlay(nSide, buffer, pInput, 0x3E7) >= 0) {
            return 1;
        }
        return -1;
    }
    if (second == 5) {
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
    if (TaLogic021_IsUseBlackHole(nSide) == 1) {
        if (TaLogic021_GetSpecCardPlay(nSide, buffer, pInput, 0x2BB) >= 0) {
            return 2;
        }
    }
    if (TaLogic021_GetSpecCardPlay(nSide, buffer, pInput, 0x339) >= 0) {
        return 2;
    }
    if (SzDuel_GetSummonPower(nSide) < 4) {
        if (TaLogic021_GetSpecCardPlay(nSide, buffer, pInput, 0x2EC) >= 0) {
            return 2;
        }
        if (TaLogic021_GetSpecCardPlay(nSide, buffer, pInput, 0xE0) >= 0) {
            return 2;
        }
        if (TaLogic021_GetSpecCardPlay(nSide, buffer, pInput, 0x16C) >= 0) {
            return 2;
        }
    }
    {
        s32 *p;
        s32 i = 0;
        s32 result;
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
        result = TaLogic021_GetSpellPlay(nSide, buffer, pInput, 0x3E7);
        if (result >= 0) {
            return result;
        }
    }
    return -1;
}

/* Whether side `nSide` holds card `nCardNo` and can summon it (its slot into `bCombo`, the card into `pCardInfo`);
   returns its kind group or -1. */
s32 TaLogic021_GetSpecCardPlay(s32 nSide, void *bCombo, void *pCardInfo, s32 nCardNo) {
    s32 values[8];
    s32 index;

    TaHand_GetNextHand(nSide, values);
    for (index = 0; index < TaHand_GetNextHandNum(nSide); index++) {
        if (((nCardNo & 0xFFFF) == values[index]) && (TaHand_CanAffordSummonCost(nSide, values[index]) == 1)) {
            ((u8 *)bCombo)[6] = index;
            SzDuel_InitCardInfo(pCardInfo, values[index]);
            return TaHand_GetCardKind(values[index]) >> 5;
        }
    }
    return -1;
}

/* Whether side `nSide` plays a magic or ritual card from its hand now (its slot into `bCombo`, the card into
   `pCardInfo`). */
s32 TaLogic021_GetSpellPlay(s32 nSide, u8 *bCombo, void *pCardInfo, s32 nMode) {
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

typedef struct Info_00169000 {
    u8 pad00[8];
    u16 x;
    s16 y;
} Info_00169000;

typedef struct Sprite_00169000 {
    Info_00169000 *info;
    u8 pad04[0x34];
    s16 x;
    s16 y;
} Sprite_00169000;

/* Fills hand combination `bCombo` for side `nSide`: the best fusion or equip chain, its card into `pCardInfo`. */
s32 TaLogic021_SetComboQue(s32 nSide, u8 *bCombo, void *pCardInfo) {
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
                            TaLogic_Manawyddan2_ConvEmptyCombo(nSide, *node, entries);
                            TaLogic_CopyArray((u8 *)*node + 2, bCombo + 6);
                            SzDuel_InitCardInfo(pCardInfo, **node);
                            ((Sprite_00169000 *)pCardInfo)->x = (value >> 16) - (((Sprite_00169000 *)pCardInfo)->info->x & 0x1FFF);
                            ((Sprite_00169000 *)pCardInfo)->y = (value & 0xFFFF) - (((Sprite_00169000 *)pCardInfo)->info->y & 0x1FFF);
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
} Info_001691E0;

/* Fills an empty combination: the hand card side `nSide` can summon with the best attack plus defence. */
void TaLogic_Manawyddan2_ConvEmptyCombo(s32 nSide, void *pCardInfo, s32 *pResult) {
    Info_001691E0 *info = pCardInfo;
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
                if (card != 0x3E7 && TaLogic021_IsRefuseEmptyCombo(card) == 0 && level >= TaHand_GetCardSummonCost2(card, nSide)) {
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
s32 TaLogic021_IsRefuseEmptyCombo(s32 nCardNo) {
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
} Obj1_00169420;

typedef struct {
    u8 pad0[0x3C];
    u16 id;
} Obj2_00169420;

/* Fills hand combination `bCombo` for side `nSide` with this duelist's special combination, its card into
   `pCardInfo`. */
s32 TaLogic021_SetSpecialComboQue(s32 nSide, void *bCombo, void *pCardInfo) {
    Obj1_00169420 *o1 = bCombo;
    Obj2_00169420 *o2 = pCardInfo;
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

typedef struct Nibbles_00169610 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_00169610;

/* The square side `nSide` summons a card of kind `sKind` to. */
s32 TaLogic021_GetSummonPiece(s32 nSide, u8 sKind, void *pInput, s32 nMode) {
    s32 bestPosition;
    s32 bestScore;
    Nibbles_00169610 cells[12];
    s32 targetY;
    s32 targetX;
    s32 kind;
    s32 j;
    Nibbles_00169610 *cell;

    extern s32 TaLogic_Manawyddan2_GetWarnHideLvl();
    extern s32 TaLogic_IsUnitWin4();
    extern s32 TaLogic_GetInvadeRoot2();
    extern s32 TaLogic_GetRoot2(s32, s32, s32, s32, s32, s32, u16, u8);

    if (pInput == NULL) {
        return -1;
    }
    cell = cells;
    j = 0;
    do {
        cell->low = cell->high = 15;
        j++;
        cell++;
    } while (j < 12);
    kind = (u8)(*((u8 *)pInput + 0x3E) >> 5);
    if (kind == 0 || kind == 5) {
        if (nMode >= 0) {
            s32 position;
            s32 y;
            s32 x;
            s32 i;
            s32 score;
            s32 target;
            bestScore = 255;
            bestPosition = 65535;
            target = SzDuel_GetUnitLoc(nMode >> 8, nMode & 255);
            i = 0;
            targetY = target >> 8;
            targetX = target & 255;
            do {
                position = Ta_GetSommonPiecePreference(nSide, i);
                if (position >= 0) {
                    x = position & 255;
                    y = position >> 8;
                    if (SzDuel_GetField(x, y) != 8 &&
                        (SzDuel_GetField(x, y) != 9 || Ta_IsVirus_Chk3(pInput, x, y) != 1) &&
                        SzDuel_GetMapUnit(x, y) == 0) {
                        if (TaLogic_IsUnitWin4(pInput, nMode, TaLogic_Manawyddan2_GetWarnHideLvl(nSide), targetX, targetY, 1) > 0) {
                            score = TaLogic_GetInvadeRoot2(pInput, cells, x, y, targetX, targetY,
                                                nMode, 1, 4, (u16)TaLogic_Manawyddan2_GetWarnHideLvl(nSide));
                        } else {
                            score = TaLogic_GetRoot2((s32)pInput, (s32)cells, x, y, targetX, targetY, nMode, 4);
                        }
                        if (TaLogic_GetMinGoalCount((u8 *)cells) > 0 && score < bestScore) {
                            bestScore = score;
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
        {
        s32 y;
        s32 x;
        s32 i;
        s32 position;
        SzDuel_GetUnitLoc(nMode >> 8, nMode & 255);
        i = 0;
        do {
            position = Ta_GetSommonPiecePreference(nSide, i);
            if (position >= 0) {
                x = position & 255;
                y = position >> 8;
                if (SzDuel_GetField(x, y) != 8 &&
                    (SzDuel_GetField(x, y) != 9 || Ta_IsVirus_Chk3(pInput, x, y) != 1) &&
                    SzDuel_GetMapUnitID(x, y) < 0) {
                    return position;
                }
            }
            i++;
        } while (i < 8);
        return -1;
        }
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
                    SzDuel_GetMapUnitID(x, y) < 0 && y < 8) {
                    result = position;
                }
            }
            i++;
        } while (i < 8);
        if (result >= 0) {
            return result;
        }
        result = -1;
        return result;
    }
}

typedef struct Nibbles_00169A10 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_00169A10;

typedef struct Output_00169A10 {
    u16 position;
    u8 action;
    u8 pad3;
    u16 destination;
    u8 pad6[6];
    s32 special;
    u8 result;
} Output_00169A10;

/* The task of a unit running from danger (task `pTask`): the safest square in reach, into `pInput` (`fFirst` = 1
   for the unit's first-choice task). */
s32 TaLogic_Manawyddan2_GetMinimumTask_RunMission(u16 *pTask, s32 nSide, void *pInput, u8 fFirst) {
    Output_00169A10 *output = pInput;
    s32 target;
    u8 endX;
    u8 extra;
    Nibbles_00169A10 nibbles[12];
    s32 bestScore;
    s32 best;
    s32 i;
    Nibbles_00169A10 *p;
    extern s32 TaLogic_Manawyddan2_IsOpenUnit();
    extern s32 TaLogic_Manawyddan2_GetWarnHideLvl();
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

        initialScore = TaLogic_Manawyddan2_GetWarnHideLvl(nSide);
        centerX = target & 0xFF;
        centerY = target >> 8;
        if (TaLogic_GetUnitWarning(centerX, centerY, *pTask, 2, initialScore, 1) == 0) {
            output->position = *pTask;
            output->action = 6;
            output->destination = target;
            output->result = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, output->destination, 1, 1);
            output->special = TaLogic_Manawyddan2_IsOpenUnit(*pTask >> 8, *pTask & 0xFF, pTask);
            TaLogic_InitRogicControl(pTask, fFirst);
            return 0;
        }
        if ((range = GetMoveRange(SzDuel_GetUnit(*pTask >> 8, *pTask & 0xFF), centerX, centerY)) == 0) {
            output->position = *pTask;
            output->action = 6;
            output->destination = target;
            output->result = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, output->destination, 1, 1);
            output->special = TaLogic_Manawyddan2_IsOpenUnit(*pTask >> 8, *pTask & 0xFF, pTask);
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
            extra = (u8)TaLogic_IsAttackedNow(*pTask >> 8, *pTask & 0xFF, 1);
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
                    if (TaLogic_IsAttackedNow2(*pTask >> 8, *pTask & 0xFF, x, y, 1) == 0 || (u8)*pTask == 0) {
                        candidateScore = TaLogic_GetUnitWarning(x, y, *pTask, 2, (u16)TaLogic_Manawyddan2_GetWarnHideLvl(nSide), 1);
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
                output->result = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, output->destination, 1, 1);
            } else {
                output->result = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, output->destination, 0, 1);
            }
            output->special = TaLogic_Manawyddan2_IsOpenUnit(*pTask >> 8, *pTask & 0xFF, pTask);
        } else {
            output->position = *pTask;
            output->action = 6;
            output->destination = target;
            output->result = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, output->destination, 1, 1);
            output->special = TaLogic_Manawyddan2_IsOpenUnit(*pTask >> 8, *pTask & 0xFF, pTask);
        }
        TaLogic_InitRogicControl(pTask, fFirst);
        return 0;
    }
}

typedef struct Input_00169FE0 {
    u16 position;
    u8 pad2[6];
    u32 destinations;
} Input_00169FE0;

typedef struct Output_00169FE0 {
    u16 position;
    u8 command;
    u8 pad3;
    u16 destination;
    u8 pad6[6];
    s32 state;
    u8 result;
} Output_00169FE0;

typedef struct Point_00169FE0 {
    u8 x : 4;
    u8 y : 4;
} Point_00169FE0;

/* The task's target square: the second half-word when the second argument is 1, else the first. */
static inline u32 destination_00169FE0(void *src, u8 mode) {
    if (mode == 1) {
        return (u16)(((Input_00169FE0 *)src)->destinations >> 16);
    }
    return *(u16 *)((u8 *)src + 8);
}

/* The task of a unit attacking (task `pTask`): its path to the goal, into `pInput`; -1 when it has none (`fFirst`
   = 1 for the unit's first-choice task). */
s32 TaLogic_Manawyddan2_GetMinimumTask_AtkMission(void *pTask, s32 nSide, u16 *pInput, u8 fFirst) {
    extern s32 TaLogic_Manawyddan2_IsOpenUnit();
    extern s32 TaLogic_Manawyddan2_GetWarnHideLvl();
    extern void TaLogic_GetInvadeRoot();
    s32 state;
    s32 current;
    s32 count;
    s32 target;
    s32 currentY;
    s32 currentX;
    s32 forced;
    s32 i;
    s32 unit;
    u32 destinationX;
    u32 destinationY;
    Point_00169FE0 points[12];

    destinationX = destination_00169FE0(pTask, fFirst);
    destinationY = destination_00169FE0(pTask, fFirst);
    if (SzDuel_GetUnit(destinationY >> 8, destinationX & 0xFF) == 0) {
        TaLogic_InitRogicControl(pTask, 1);
        return -1;
    }
    state = TaLogic_Manawyddan2_IsOpenUnit(((Input_00169FE0 *)pTask)->position >> 8, ((Input_00169FE0 *)pTask)->position & 0xFF, pTask);
    current = SzDuel_GetUnitLoc(((Input_00169FE0 *)pTask)->position >> 8, ((Input_00169FE0 *)pTask)->position & 0xFF);
    destinationX = destination_00169FE0(pTask, fFirst);
    destinationY = destination_00169FE0(pTask, fFirst);
    target = SzDuel_GetUnitLoc(destinationY >> 8, destinationX & 0xFF);
    for (i = 0; i < 12; i++) {
        points[i].x = points[i].y = 0xF;
    }
    unit = SzDuel_GetUnit(((Input_00169FE0 *)pTask)->position >> 8, ((Input_00169FE0 *)pTask)->position & 0xFF);
    currentX = current & 0xFF;
    currentY = current >> 8;
    if (GetMoveRange(unit, currentX, currentY) == 0) {
        s32 cost;
        ((Output_00169FE0 *)pInput)->position = ((Input_00169FE0 *)pTask)->position;
        ((Output_00169FE0 *)pInput)->command = 6;
        ((Output_00169FE0 *)pInput)->destination = current;
        cost = TaLogic_GetUnitWarning(currentX, currentY, nSide, 2, 0,
                            (u8)TaLogic_Manawyddan2_GetWarnHideLvl(nSide));
        if (cost >= SzDuel_GetUnitAP(((Input_00169FE0 *)pTask)->position >> 8, ((Input_00169FE0 *)pTask)->position & 0xFF, 0)) {
            ((Output_00169FE0 *)pInput)->result = TaLogic_IsDefStyleUnit(((Input_00169FE0 *)pTask)->position >> 8, ((Input_00169FE0 *)pTask)->position & 0xFF,
                                       pInput[2], 1, 1);
        } else {
            ((Output_00169FE0 *)pInput)->result = TaLogic_IsDefStyleUnit(((Input_00169FE0 *)pTask)->position >> 8, ((Input_00169FE0 *)pTask)->position & 0xFF,
                                       pInput[2], 0, 1);
        }
        TaLogic_InitRogicControl(pTask, fFirst);
    } else {
        s32 y;
        s32 x;
        Point_00169FE0 *point;
        s32 index;
        s32 bestCost;
        s32 selected;
        s32 position = ((Input_00169FE0 *)pTask)->position;
        TaLogic_GetInvadeRoot(position >> 8, position & 0xFF, points, currentX, currentY,
                      x = target & 0xFF, y = target >> 8,
                      destination_00169FE0(pTask, fFirst), 1, 30,
                      (u16)TaLogic_Manawyddan2_GetWarnHideLvl(nSide));
        count = TaLogic_GetMinGoalCount((u8 *)points);
        selected = 0xFF;
        if (count > 0) {
            forced = 0;
            bestCost = 0xFFFF;
            for (index = 0; index < count; index++) {
                s32 hit = TaLogic021_IsOpenMoveUnit(((Input_00169FE0 *)pTask)->position >> 8, ((Input_00169FE0 *)pTask)->position & 0xFF,
                                  currentX, currentY, x, y);
                if (hit == 1) {
                    Point_00169FE0 *forcedPoint = &points[index];
                    selected = index;
                    forced = 1;
                    index = count;
                    forcedPoint->x = x;
                    forcedPoint->y = y;
                } else {
                    s32 cost;
                    point = &points[index];
                    cost = TaLogic_GetUnitWarning(point->x, point->y, nSide, 4, 0,
                                             (u8)TaLogic_Manawyddan2_GetWarnHideLvl(nSide));
                    if (cost < bestCost) {
                        bestCost = cost;
                        selected = index;
                    } else if (cost == bestCost) {
                        if (((x < point->x ? point->x : x) -
                             (point->x < x ? point->x : x)) +
                            ((y < point->y ? point->y : y) -
                             (point->y < y ? point->y : y)) <
                            ((x < points[selected].x ? points[selected].x : x) -
                             (points[selected].x < x ? points[selected].x : x)) +
                            ((y < points[selected].y ? points[selected].y : y) -
                             (points[selected].y < y ? points[selected].y : y))) {
                            bestCost = cost;
                            selected = index;
                        }
                    }
                }
            }
        } else {
            ((Output_00169FE0 *)pInput)->position = ((Input_00169FE0 *)pTask)->position;
            ((Output_00169FE0 *)pInput)->command = 6;
            ((Output_00169FE0 *)pInput)->destination = current;
            ((Output_00169FE0 *)pInput)->state = state;
            ((Output_00169FE0 *)pInput)->result = TaLogic_IsDefStyleUnit(((Input_00169FE0 *)pTask)->position >> 8, ((Input_00169FE0 *)pTask)->position & 0xFF,
                                       ((Output_00169FE0 *)pInput)->destination, 0, 1);
            TaLogic_InitRogicControl(pTask, fFirst);
            return 0;
        }
            if (selected != 0xFF) {
                ((Output_00169FE0 *)pInput)->position = ((Input_00169FE0 *)pTask)->position;
                ((Output_00169FE0 *)pInput)->command = 6;
                ((Output_00169FE0 *)pInput)->destination = (points[selected].y << 8) | points[selected].x;
                ((Output_00169FE0 *)pInput)->state = forced;
                ((Output_00169FE0 *)pInput)->result = TaLogic_IsDefStyleUnit(((Input_00169FE0 *)pTask)->position >> 8, ((Input_00169FE0 *)pTask)->position & 0xFF,
                                           ((Output_00169FE0 *)pInput)->destination, 0, 1);
            } else {
                ((Output_00169FE0 *)pInput)->position = ((Input_00169FE0 *)pTask)->position;
                ((Output_00169FE0 *)pInput)->command = 6;
                ((Output_00169FE0 *)pInput)->destination = current;
                ((Output_00169FE0 *)pInput)->state = forced;
                ((Output_00169FE0 *)pInput)->result = TaLogic_IsDefStyleUnit(((Input_00169FE0 *)pTask)->position >> 8, ((Input_00169FE0 *)pTask)->position & 0xFF,
                                           ((Output_00169FE0 *)pInput)->destination, 0, 1);
                TaLogic_InitRogicControl(pTask, fFirst);
                return 0;
            }
    }
    return 0;
}

typedef struct Coord_0016A5C0 {
    u8 x : 4;
    u8 y : 4;
} Coord_0016A5C0;

typedef struct Unit_0016A5C0 {
    u16 position;
    u8 pad2[6];
    union {
        u32 packed;
        u16 low;
    } target;
} Unit_0016A5C0;

typedef struct Output_0016A5C0 {
    u16 position;
    u8 kind;
    u8 pad3;
    u16 target;
    u8 pad6[6];
    s32 value;
    u8 flag;
} Output_0016A5C0;

/* The task's target square: the second half-word when the second argument is 1, else the first. */
static inline u32 target_0016A5C0(void *unit, s32 side) {
    return side == 1 ? (u32)(u16)(((Unit_0016A5C0 *)unit)->target.packed >> 16) : (u32)((Unit_0016A5C0 *)unit)->target.low;
}

/* The smaller of the two values. */
static inline u32 minY_0016A5C0(void *unit, s32 side, u8 coord) {
    return coord < (target_0016A5C0(unit, side) >> 8) ? coord : (target_0016A5C0(unit, side) >> 8);
}

/* The larger of the two values. */
static inline u32 maxY_0016A5C0(void *unit, s32 side, u8 coord) {
    return (target_0016A5C0(unit, side) >> 8) < coord ? coord : (target_0016A5C0(unit, side) >> 8);
}

/* The smaller of the two values. */
static inline u32 minX_0016A5C0(void *unit, s32 side, u8 coord) {
    return coord < (target_0016A5C0(unit, side) & 0xFF) ? coord : (target_0016A5C0(unit, side) & 0xFF);
}

/* The larger of the two values. */
static inline u32 maxX_0016A5C0(void *unit, s32 side, u8 coord) {
    return (target_0016A5C0(unit, side) & 0xFF) < coord ? coord : (target_0016A5C0(unit, side) & 0xFF);
}

/* The task of a unit moving to its goal (task `pTask`), into `pInput` (`fFirst` = 1 for the unit's first-choice
   task). */
s32 TaLogic_Manawyddan2_GetMinimumTask_MoveMission(void *pTask, s32 nSide, void *pInput, u8 fFirst, u8 nKind) {
    extern s32 TaLogic_Manawyddan2_IsOpenUnit();
    extern s32 TaLogic_Manawyddan2_GetWarnHideLvl();
    extern s32 TaLogic_GetUnitWarning();
    extern void TaLogic_GetRoot();
    extern s32 TaLogic_IsDefStyleUnit(s32, s32, s32, u8, s32);
    Coord_0016A5C0 coords[12];
    s32 initial;
    s32 cell;
    s32 count;

    initial = SzDuel_GetUnitLoc(((Unit_0016A5C0 *)pTask)->position >> 8, ((Unit_0016A5C0 *)pTask)->position & 0xFF);
    {
    s32 bestScore;
    s32 best;
    s32 side = fFirst;
    Coord_0016A5C0 *candidate;
    s32 index;
    if (target_0016A5C0(pTask, side) == 0xFFFF) {
        if (initial == target_0016A5C0(pTask, side)) {
            ((Output_0016A5C0 *)pInput)->position = ((Unit_0016A5C0 *)pTask)->position;
            ((Output_0016A5C0 *)pInput)->kind = 6;
            ((Output_0016A5C0 *)pInput)->target = initial;
            ((Output_0016A5C0 *)pInput)->flag = TaLogic_IsDefStyleUnit(((Unit_0016A5C0 *)pTask)->position >> 8, ((Unit_0016A5C0 *)pTask)->position & 0xFF, ((Output_0016A5C0 *)pInput)->target, nKind, 1);
            ((Output_0016A5C0 *)pInput)->value = TaLogic_Manawyddan2_IsOpenUnit(((Unit_0016A5C0 *)pTask)->position >> 8, ((Unit_0016A5C0 *)pTask)->position & 0xFF, pTask);
            TaLogic_InitRogicControl(pTask, fFirst);
            return 0;
        }
    }

    if (SzDuel_GetUnitStatus(((Unit_0016A5C0 *)pTask)->position >> 8,
                      ((Unit_0016A5C0 *)pTask)->position & 0xFF, 4) != 0) {
        if ((SzDuel_GetUnitKind(((Unit_0016A5C0 *)pTask)->position >> 8,
                          ((Unit_0016A5C0 *)pTask)->position & 0xFF) >> 5) == 1 ||
            (SzDuel_GetUnitKind(((Unit_0016A5C0 *)pTask)->position >> 8,
                          ((Unit_0016A5C0 *)pTask)->position & 0xFF) >> 5) == 5) {
            SzDuel_SetUnitStatus(((Unit_0016A5C0 *)pTask)->position >> 8,
                          ((Unit_0016A5C0 *)pTask)->position & 0xFF, 0, 1);
            ((Output_0016A5C0 *)pInput)->position = ((Unit_0016A5C0 *)pTask)->position;
            ((Output_0016A5C0 *)pInput)->kind = 14;
            return 0;
        }
    }

    candidate = coords;
    {
        s32 i = 0;
        Coord_0016A5C0 *entry = candidate;
        do {
            entry->x = entry->y = 0xF;
            i++;
            entry++;
        } while (i < 12);
    }

    cell = SzDuel_GetMapUnitID(target_0016A5C0(pTask, side) & 0xFF, ((u32)target_0016A5C0(pTask, side)) >> 8);
    if (cell < 0) {
        cell = 0xFFFF;
    }
    TaLogic_GetRoot(((Unit_0016A5C0 *)pTask)->position >> 8, ((Unit_0016A5C0 *)pTask)->position & 0xFF,
                 coords, initial & 0xFF, initial >> 8, target_0016A5C0(pTask, side) & 0xFF,
                 ((u32)target_0016A5C0(pTask, side)) >> 8, (u16)cell, 7);
    count = TaLogic_GetMinGoalCount((u8 *)coords);
    {
        if (count > 0) {
        best = 0xFF;
        bestScore = 0xFFFF;
        for (index = 0; index < count; index++) {
                if (SzDuel_GetMapUnit(candidate->x, candidate->y) == 0) {
                    s32 score = TaLogic_GetUnitWarning(candidate->x, candidate->y, nSide, 4, 0, (u8)TaLogic_Manawyddan2_GetWarnHideLvl(nSide));
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
                        bestMinY = minY_0016A5C0(pTask, side, bestY);
                        bestMaxY = maxY_0016A5C0(pTask, side, bestY);
                        bestX = (&coords[best])->x;
                        bestMinX = minX_0016A5C0(pTask, side, bestX);
                        bestMaxX = maxX_0016A5C0(pTask, side, bestX);
                        currentY = (u8)candidate->y;
                        currentMinY = minY_0016A5C0(pTask, side, currentY);
                        currentMaxY = maxY_0016A5C0(pTask, side, currentY);
                        currentX = candidate->x;
                        currentMinX = minX_0016A5C0(pTask, side, currentX);
                        currentMaxX = maxX_0016A5C0(pTask, side, currentX);
                        if ((currentMaxX - currentMinX) + (currentMaxY - currentMinY) < (bestMaxX - bestMinX) + (bestMaxY - bestMinY)) {
                            bestScore = score;
                            best = index;
                        }
                    }
                }
            candidate++;
        }
    } else {
        ((Output_0016A5C0 *)pInput)->position = ((Unit_0016A5C0 *)pTask)->position;
            ((Output_0016A5C0 *)pInput)->kind = 6;
            ((Output_0016A5C0 *)pInput)->target = initial;
            ((Output_0016A5C0 *)pInput)->flag = TaLogic_IsDefStyleUnit(((Unit_0016A5C0 *)pTask)->position >> 8, ((Unit_0016A5C0 *)pTask)->position & 0xFF, ((Output_0016A5C0 *)pInput)->target, nKind, 1);
            ((Output_0016A5C0 *)pInput)->value = TaLogic_Manawyddan2_IsOpenUnit(((Unit_0016A5C0 *)pTask)->position >> 8, ((Unit_0016A5C0 *)pTask)->position & 0xFF, pTask);
        TaLogic_InitRogicControl(pTask, fFirst);
        return 0;
    }

        if (best != 0xFF) {
            ((Output_0016A5C0 *)pInput)->position = ((Unit_0016A5C0 *)pTask)->position;
            ((Output_0016A5C0 *)pInput)->kind = 6;
            ((Output_0016A5C0 *)pInput)->target = (coords[best].y << 8) | coords[best].x;
            ((Output_0016A5C0 *)pInput)->flag = TaLogic_IsDefStyleUnit(((Unit_0016A5C0 *)pTask)->position >> 8, ((Unit_0016A5C0 *)pTask)->position & 0xFF, ((Output_0016A5C0 *)pInput)->target, nKind, 1);
            ((Output_0016A5C0 *)pInput)->value = TaLogic_Manawyddan2_IsOpenUnit(((Unit_0016A5C0 *)pTask)->position >> 8, ((Unit_0016A5C0 *)pTask)->position & 0xFF, pTask);
        } else {
            ((Output_0016A5C0 *)pInput)->position = ((Unit_0016A5C0 *)pTask)->position;
            ((Output_0016A5C0 *)pInput)->kind = 6;
            ((Output_0016A5C0 *)pInput)->target = initial;
            ((Output_0016A5C0 *)pInput)->flag = TaLogic_IsDefStyleUnit(((Unit_0016A5C0 *)pTask)->position >> 8, ((Unit_0016A5C0 *)pTask)->position & 0xFF, ((Output_0016A5C0 *)pInput)->target, nKind, 1);
            ((Output_0016A5C0 *)pInput)->value = TaLogic_Manawyddan2_IsOpenUnit(((Unit_0016A5C0 *)pTask)->position >> 8, ((Unit_0016A5C0 *)pTask)->position & 0xFF, pTask);
        }
        TaLogic_InitRogicControl(pTask, fFirst);
    }
    }
    return 0;
}

/* Whether this duelist opens (turns face up) unit (nSide, nID) now: 0 no, 1 or 2 by its kind. */
s32 TaLogic_Manawyddan2_IsOpenUnit(s32 nSide, s32 nID) {
    s32 kind;
    u32 *info;

    kind = SzDuel_GetUnitCardNo();
    Ta_IsUnitControl(nSide, nID);
    info = SzDuel_GetUnitEffect(nSide, nID, 0);
    SzDuel_GetUnitLoc(nSide, nID);
    if (SzDuel_GetUnitStatus(nSide, nID, 4) != 0) {
        return 0;
    }
    switch (SzDuel_GetUnitKind(nSide, nID) >> 5) {
    case 1:
        if (TaLogic_GetActionReaction(nSide, nID, 0, 0, 6, 1) == 5) {
            return 2;
        }
        if (info == NULL) {
            return 2;
        }
        switch (*info >> 8) {
        case 0x27:
            if (SzDuel_GetSummonPower(nSide) < 4) {
                return 1;
            }
            break;
        case 4:
            if (TaLogic021_IsUseBlackHole(nSide) == 1) {
                return 1;
            }
            break;
        }
        break;
    case 0:
        switch (kind) {
        case 0xE0:
        case 0x16C:
            if (SzDuel_GetSummonPower(nSide) < 4) {
                return 1;
            }
            break;
        }
        break;
    }
    return 2;
}

/* Whether unit (nSide, nID) may open while moving from (nX, nZ) to the square next to it, (gX, gZ). */
s32 TaLogic021_IsOpenMoveUnit(s32 nSide, s32 nID, s32 nX, s32 nZ, s32 gX, s32 gZ) {
    s32 minY;
    s32 maxY;
    s32 minX;
    s32 maxX;
    s32 result;

    minY = nZ < gZ ? nZ : gZ;
    if (gZ < nZ) {
        maxY = nZ;
    } else {
        maxY = gZ;
    }
    minX = nX < gX ? nX : gX;
    if (gX < nX) {
        maxX = nX;
    } else {
        maxX = gX;
    }
    if ((maxX - minX) + (maxY - minY) != 2) {
        return 0;
    }
    if (SzDuel_GetUnit(nSide, nID) == 0) {
        return 0;
    }
    if (SzDuel_GetUnitStatus(nSide, nID, 0) == 0) {
        result = CheckLandAgreement2(SzDuel_GetField(nX, nZ), nSide, nID);
        return result != 1 ? 0 : 1;
    }
    return 0;
}

/* How careful this duelist is about hidden cards (by its life points and monster count). */
s32 TaLogic_Manawyddan2_GetWarnHideLvl(void) {
    return 0;
}

/* From the dotr-decomp CC0 bundle (commit 88c32bb2), chatC/imp/conv.py. */

int TaLogic021_IsUseBlackHole(int side)
{
    int i;
    int n;
    int low;
    int col;
    int pos;
    int row;
    n = 0;
    pos = Ta_GetUnitOwnerIDFromLstCount(SearchUnitByRange(0, 0, side, 3, 33, 14), 0);
    row = pos >> 8;
    col = pos & 0xff;
    if (side != Ta_IsUnitControl(row, col)) {
        low = SzDuel_GetUnitLoc(row, col) & 0xff;
        if (TaUtil_GetUnitAP(row, col, low, SzDuel_GetUnitLoc(row, col) >> 8) >= 3000) {
            for (i = 1; i < 11; i++) {
                if (SzDuel_GetUnit(side, i) != 0) {
                    n++;
                }
            }
        }
    }
    return n < 3 ? 1 : 0;
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
} Req_0016B1F0;

typedef struct {
    u8 pad0[0x160];
    u16 list[32];    /* 0x160 */
    u8 idx : 5;      /* 0x1A0 */
    u8 pad1A0 : 3;
    u8 pad1A1;
    u16 count;       /* 0x1A2 */
} Work_0016B1F0;

s32 TaLogic_GetInputQueFromMinimumTask_b(void *, void *, s32);

/* Computer duelist 21's controller (duelistControllers[21]): the buttons it presses this frame. With an empty
   input queue it plans its next task and turns it into buttons, then plays the queue back one button per frame;
   after 600 frames it gives up the turn (0x20, then 0x800). */
s32 duelistController21(s32 wCursorPos, void *pCtl) {
    Req_0016B1F0 req;
    Work_0016B1F0 *w;
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
        if (TaLogic_Manawyddan2_GetMinimumTask(w, &req, wCursorPos) == 0) {
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

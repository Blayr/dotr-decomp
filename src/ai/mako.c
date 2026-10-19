/* Computer AI of Mako (duelist 14, duelistController14). */

#include "common.h"
#pragma conditional_move off

/* This duelist's move: picks the next unit to act, gives it a task and turns that into input `pInput`; returns 1
   when it set one. */
s32 TaLogic_Mako_GetMinimumTask(void *pCtl, void *pInput, s32 wCursorPos) {
    UnitTask *tasks = pCtl;
    s32 side;
    s32 found;
    s32 result;
    s32 index;

    side = SzDuel_GetTurnOwner();
    found = 0;
    if ((result = TaLogic_Mako_GetNextActiveUnit(tasks, side, (s32)pInput)) < 0) {
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
    TaLogic_Mako_CommandUnit(&tasks[index]);
    switch ((tasks[index].mission >> 8) & 0xFF) {
    case TASK_RUN:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            TaLogic_Mako_GetMinimumTask_RunMission(&tasks[index], side, pInput, 1);
            found = 1;
        }
        break;
    case TASK_ATTACK:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            if (TaLogic_Mako_GetMinimumTask_AtkMission(&tasks[index], side, pInput, 1) < 0) {
                TaLogic_InitRogicControl(&tasks[index], 1);
                return 1;
            }
            found = 1;
        }
        break;
    case TASK_SUMMON:
        if (TaLogic_Mako_GetMinimumTask_Summon(tasks[index].ownerId, side, (s32)pInput) < 0) {
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
            TaLogic_Mako_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 1, 0);
            found = 1;
        }
        break;
    case TASK_CONFIRMUNIT:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            TaLogic_Mako_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 1, 1);
            found = 1;
        }
        break;
    case TASK_ENCHANT:
        TaLogic_GetMinimumTask_EncMission(&tasks[index], side, pInput, 1, 0, TaLogic_Mako_GetWarnHideLvl(side), 5, 1);
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
            TaLogic_Mako_GetMinimumTask_RunMission(&tasks[index], side, pInput, 0);
            found = 1;
        }
        break;
    case 2:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            if (TaLogic_Mako_GetMinimumTask_AtkMission(&tasks[index], side, pInput, 0) < 0) {
                TaLogic_Mako_GetMinimumTask_RunMission(&tasks[index], side, pInput, 0);
            }
            found = 1;
        }
        break;
    case 10:
        if (TaLogic_Mako_GetMinimumTask_Summon(tasks[index].ownerId, side, (s32)pInput) < 0) {
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
            TaLogic_Mako_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 0, 0);
            found = 1;
        }
        break;
    case 3:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            TaLogic_Mako_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 0, 1);
            found = 1;
        }
        break;
    case 9:
        TaLogic_GetMinimumTask_EncMission(&tasks[index], side, pInput, 0, 0, TaLogic_Mako_GetWarnHideLvl(side), 5, 1);
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
s32 TaLogic_Mako_CommandUnit(void *pCtl) {
    u16 card;
    s32 low;
    s32 type;
    s32 controllingSide;

    card = *(u16 *)pCtl;
    SzDuel_GetUnitLoc(card >> 8, card & 0xFF);
    card = *(u16 *)pCtl;
    controllingSide = Ta_IsUnitControl(card >> 8, card & 0xFF);
    card = *(u16 *)pCtl;
    if (SzDuel_GetUnit(card >> 8, card & 0xFF) != 0) {
        card = *(u16 *)pCtl;
        if (SzDuel_GetUnitStatus(card >> 8, card & 0xFF, 0) == 0) {
            card = *(u16 *)pCtl;
            if (card != 0xFFFF) {
                low = card & 0xFF;
                if (low == 0) {
                    if (*(s32 *)((u8 *)pCtl + 8) == -1) {
                        if (TaLogic_IsAttackedNow(card >> 8, low, 0) == 1) {
                            if (SzDuel_InqHandPhase(*(u16 *)pCtl >> 8) == 1) {
                                *(s16 *)((u8 *)pCtl + 4) = 0x50A;
                            } else {
                                *(s16 *)((u8 *)pCtl + 4) = 0x5FF;
                            }
                        } else {
                            if (SzDuel_InqHandPhase(*(u16 *)pCtl >> 8) == 1) {
                                *(s16 *)((u8 *)pCtl + 4) = 0xA05;
                            } else {
                                *(s16 *)((u8 *)pCtl + 4) = 0x5FF;
                            }
                        }
                    }
                } else {
                    type = SzDuel_GetUnitKind(card >> 8, low) >> 5;
                    switch (type) {
                    case 0:
                        card = *(u16 *)pCtl;
                        if (TaUtil_IsExMonster(card >> 8, card & 0xFF) == 1) {
                            TaLogic014_CommandEfcMonster(pCtl);
                        } else {
                            TaLogic014_CommandBtlUnit(pCtl);
                        }
                        break;
                    case 2:
                        TaLogic_CommandEncUnit(pCtl, 5, 0, TaLogic_Mako_GetWarnHideLvl(controllingSide) & 0xFF);
                        break;
                    case 1:
                        TaLogic014_CommandSpellUnit(pCtl);
                        break;
                    default:
                        *(s16 *)((u8 *)pCtl + 4) = 0x5FF;
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
s32 TaLogic_Mako_GetNextActiveUnit(u16 *pCtl, s32 nSide, s32 pInput) {
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
    TaLogic_Mako_CommandUnit(pCtl + idx * 8);
    if (((pCtl[idx * 8 + 2] >> 8) & 0xFF) == 10) {
        if (SzDuel_InqHandPhase(nSide) == 1 && TaLogic_Mako_GetMinimumTask_Summon(pos, nSide, pInput) >= 0) {
            return pos | 0x10000;
        }
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_GetUnitStatus(nSide, 0, 0) == 0) {
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_InqHandPhase(nSide) == 1 && TaLogic_Mako_GetMinimumTask_Summon(pos, nSide, pInput) >= 0) {
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
} Slot_0014C3B0;

typedef struct {
    u16 low;
    u16 high;
} DataHalves_0014C3B0;

typedef struct {
    u16 unitId; /* (side << 8) | unit */
    u8 pad2[2];
    u16 state;
    u8 pad6[2];
    union {
        u32 word;
        DataHalves_0014C3B0 halves;
    } data;
} Entry_0014C3B0;

/* Orders a fighting unit (task `pTask`): straight at its goal when the path is open, else the nearest enemy it can
   beat. */
void TaLogic014_CommandBtlUnit(void *pTask) {
    extern s32 TaLogic_IsRootOpen();
    extern void TaLogic_InitIgnoreLst();
    extern s32 TaLogic014_GetNearUnit();
    Entry_0014C3B0 *entry = pTask;
    s32 side;
    s32 player;
    s32 pos;
    s32 other;
    s32 otherPos;
    s32 i;
    s32 result;
    u8 work[0x70];
    Slot_0014C3B0 list[22];
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
            switch (TaLogic014_GetNearUnit(entry, 0, player, pos & 0xFF, pos >> 8,
                                  Ta_GetCurrentSide(entry->unitId >> 8, entry->unitId & 0xFF) == 0 ? 1 : 0,
                                  (u8)i, TaLogic_Mako_GetWarnHideLvl(side), list, 0,
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
            }
            i++;
            if (i > 3) {
                break;
            }
        }
        if (TaLogic014_IsLinePoint(pos & 0xFF, pos >> 8) == 1) {
            if (TaLogic014_IsActiveMode() == 1) {
                entry->state = 0x2FF;
                entry->data.word = (other << 16) | entry->data.halves.low;
            } else {
                entry->state = 0x6FF;
                entry->data.word = (pos << 16) | entry->data.halves.low;
            }
            return;
        }
        result = TaLogic014_GetEmptyLine();
        if (result >= 0) {
            entry->state = 0x6FF;
            entry->data.word = (result << 16) | entry->data.halves.low;
        } else {
            entry->state = 0x2FF;
            entry->data.word = (other << 16) | entry->data.halves.low;
        }
    }
}

/* TaLogic_GetNearUnit with this duelist's view and strength settings. */
void TaLogic014_GetNearUnit(s32 pTask, s32 pTree, s32 pVarInfo, s32 nX, s32 nZ, s32 eSide, s32 bDist, s32 WarnLvl, s32 nUnitLst, u16 wUnitNum, s32 wSize, s32 wNodeCount, u8 bChase, s32 wIgnoreLst) {
    TaLogic_GetNearUnit(pTask, pTree, pVarInfo, nX, nZ, eSide, bDist, WarnLvl,
        nUnitLst, wUnitNum, wSize, wNodeCount, bChase, 0, 2500, wIgnoreLst);
}

/* Orders an effect monster (task `pTask`): where its effect does most. */
void TaLogic014_CommandEfcMonster(void *pTask) {
    extern s32 SzDuel_GetUnitCardNo();
    Entry_0014C3B0 *entry = pTask;
    s32 slot;
    s32 kind;

    slot = Ta_IsUnitControl(entry->unitId >> 8, entry->unitId & 0xFF);
    kind = SzDuel_GetUnitCardNo(entry->unitId >> 8, entry->unitId & 0xFF);
    switch (kind) {
    case 0x264:
    case 0x227:
        if (TaLogic014_IsUnitNaturalEffectUse(slot, kind) == 1) {
            entry->state = 0x3FF;
            entry->data.word = (SzDuel_GetUnitLoc(entry->unitId >> 8, entry->unitId & 0xFF) << 16) | entry->data.halves.low;
            return;
        }
        break;
    case 0x23A:
        if (TaLogic014_IsActiveMode() == 1 && TaLogic_CommandGunnerUnit(entry, 0) == 1) {
            return;
        }
        break;
    case 0x23F:
        if (TaLogic014_IsActiveMode() == 1 && SzDuel_GetUnitStatus(entry->unitId >> 8, entry->unitId & 0xFF, 4) == 0 && TaLogic_CommandGunnerUnit(entry, 0) == 1) {
            return;
        }
        break;
    }
    TaLogic014_CommandBtlUnit(entry);
}

typedef struct Entry_0014C870 {
    u16 position;
    u16 unk2;
    u16 state;
    u16 unk6;
    u32 data;
} Entry_0014C870;

/* Orders a face-down magic card (task `pTask`): whether and where to open it. */
void TaLogic014_CommandSpellUnit(void *pTask) {
    Entry_0014C870 *entry = pTask;
    u32 *card;
    s32 position;
    s32 result;

    Ta_IsUnitControl((s32)entry->position >> 8, entry->position & 0xFF);
    card = Ta_GetUnitEffect((s32)entry->position >> 8, entry->position & 0xFF, 0);
    position = SzDuel_GetUnitLoc((s32)entry->position >> 8, entry->position & 0xFF);
    if (card == NULL) {
        entry->state = 0x5FF;
    } else {
        switch (*card >> 8) {
        case 2:
            if (TaLogic014_IsActiveMode() == 1) {
                result = TaLogic_GetLandChange(SzDuel_GetUnit((s32)entry->position >> 8, entry->position & 0xFF),
                                      position & 0xFF, position >> 8, 4, 9, 2);
                if (result >= 0) {
                    entry->state = 0x6FF;
                    entry->data = (result << 16) | (entry->data & 0xFFFF);
                }
            }
            break;
        }
        entry->state = 0x5FF;
    }
}

/* Whether (nX, nZ) is one of this duelist's three line squares. */
s32 TaLogic014_IsLinePoint(s32 nX, s32 nZ) {
    s32 var_s0;

    var_s0 = 0;
loop_1:
    if (((nZ << 8) | nX) == TaLogic014_GetLine(var_s0)) {
        return 1;
    }
    var_s0 += 1;
    if (var_s0 >= 3) {
        return 0;
    }
    goto loop_1;
}

/* Line square `nNo` (0..2) of this duelist (from its summon preferences), or -1. */
s32 TaLogic014_GetLine(s32 nNo) {
    s32 TaLogic_Mako_GetSommonPiecePreference(s32, s32);
    s32 id;

    id = SzDuel_GetTurnOwner();
    switch (nNo) {
    case 0:
        return TaLogic_Mako_GetSommonPiecePreference(id, 0);
    case 1:
        return TaLogic_Mako_GetSommonPiecePreference(id, 3);
    case 2:
        return TaLogic_Mako_GetSommonPiecePreference(id, 4);
    default:
        return -1;
    }
}

/* Line square `index` (0..2) of this duelist, or -1. */
static inline s32 slot_0014CA60(s32 index) {
    s32 TaLogic_Mako_GetSommonPiecePreference(s32, s32);
    s32 id;

    id = SzDuel_GetTurnOwner();
    switch (index) {
    case 0:
        return TaLogic_Mako_GetSommonPiecePreference(id, 0);
    case 1:
        return TaLogic_Mako_GetSommonPiecePreference(id, 3);
    case 2:
        return TaLogic_Mako_GetSommonPiecePreference(id, 4);
    default:
        return -1;
    }
}

/* The free line of the board this duelist's units fill next. */
s32 TaLogic014_GetEmptyLine(void) {
    s32 index;
    s32 position;

    index = 0;
    do {
        position = slot_0014CA60(index);
        if (((SzDuel_GetMapUnit(position & 0xFF, position >> 8) == 0) ? 1 : 0) == 1) {
            return slot_0014CA60(index);
        }
        index++;
    } while (index < 3);
    return -1;
}

typedef struct {
    s16 id;
    u8 unk2;
    u8 pad3;
    s16 unk4;
    u8 pad6[6];
    s32 unkC;
} Ctx_0014CBA0;

typedef struct {
    u8 pad0[0x3C];
    u16 unk3C;
    u8 pad3E[0x22];
} Work_0014CBA0;

s32 TaLogic_GetNearCard2(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8,
                  s32 arg9);

/* The summon task for side `nSide`: which hand cards to play and where, into `pInput`; -1 when it plays none. */
s32 TaLogic_Mako_GetMinimumTask_Summon(s32 wUnit, s32 nSide, s32 pInput) {
    s32 ret;
    s32 kind;
    Ctx_0014CBA0 *ctx = (Ctx_0014CBA0 *)pInput;
    Work_0014CBA0 work;
    s32 res;
    extern s32 TaLogic_GetUnitNum();

    ctx->id = wUnit;
    if (SzDuel_InqHandPhase(nSide) == 0) {
        return -1;
    }
    if (TaLogic_GetUnitNum(nSide, 0) == 5 && TaLogic_GetUnitNum(nSide, 1) == 5) {
        return -1;
    }
    kind = TaLogic014_IsHandPlay(nSide, &work);
    if (kind < 0) {
        return -1;
    }
    ctx->unk2 = 10;
    ctx->unkC = 2;
    wUnit = SzDuel_GetUnitLoc(wUnit >> 8, wUnit & 0xFF);
    if (kind == 0) {
        if (TaLogic014_SetComboQue(nSide, (u8 *)ctx, &work) >= 0) {
            ret = TaLogic_GetNearCard2(&work, wUnit & 0xFF, wUnit >> 8, nSide == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, TaLogic_Mako_GetWarnHideLvl(nSide));
            if (ret < 0) {
                if (SzDuel_GetUnitMonsterCount(nSide) < 6) {
                    res = TaLogic014_GetSummonPiece(nSide, kind, &work, ret);
                    if (res < 0) {
                        return -1;
                    }
                    ctx->unk4 = res;
                    return 1;
                }
            } else {
                res = TaLogic014_GetSummonPiece(nSide, kind, &work, ret);
                if (res < 0) {
                    return -1;
                }
                ctx->unk4 = res;
                return 1;
            }
        }
    } else {
        ret = TaLogic_GetNearCard2(&work, wUnit & 0xFF, wUnit >> 8, nSide == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, TaLogic_Mako_GetWarnHideLvl(nSide));
    }
    if (kind == 2) {
        TaLogic014_SetSpecialComboQue(nSide, ctx, &work);
        res = TaLogic014_GetSummonPiece(nSide, kind, &work, ret);
        if (res < 0) {
            return -1;
        }
        ctx->unk4 = res;
        return 1;
    }
    if (TaLogic014_GetSpellPlay(nSide, (u8 *)ctx, &work, work.unk3C) < 0) {
        return -1;
    }
    res = TaLogic014_GetSummonPiece(nSide, kind, &work, ret);
    if (res < 0) {
        return -1;
    }
    ctx->unk4 = res;
    return 1;
}

/* Whether side `nSide` should play from its hand this turn (and what, into `pInput`). */
s32 TaLogic014_IsHandPlay(s32 nSide, void *pInput) {
    extern s32 TaLogic_GetUnitNum();
    extern s32 SzView_SetCamera();
    s32 ids[8];
    s32 data[8];
    u8 type = (u8)TaLogic_GetUnitNum(nSide, 0);
    u8 attr = (u8)TaLogic_GetUnitNum(nSide, 1);

    if (pInput == NULL) {
        return -1;
    }
    TaHand_GetNextHand(nSide, ids);
    if (type == 5) {
        s32 result = TaLogic014_GetSpellPlay(nSide, (u8 *)data, pInput, 0x3E7);
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
    if (TaLogic014_GetSpecCardPlay(nSide, (u8 *)data, pInput, 0x354) >= 0) {
        if (TaLogic014_IsDoCerem(nSide, 0x354) == 1) {
            return 2;
        }
    }
    if (TaLogic014_IsActiveMode() == 1) {
        if (SzDuel_GetUnitSpellCount(nSide) == 0) {
            if (TaLogic014_GetSpecCardPlay(nSide, (u8 *)data, pInput, 0x2BD) >= 0) {
                return 2;
            }
        }
    }
    if (SzDuel_GetUnitMonsterCount(nSide) >= 4) {
        if (TaLogic014_GetSpecCardPlay(nSide, (u8 *)data, pInput, 0x2E6) >= 0) {
            return 2;
        }
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
        s32 result = TaLogic014_GetSpellPlay(nSide, (u8 *)data, pInput, 0x3E7);
        if (result >= 0) {
            return result;
        }
        return -1;
    }
}

/* Whether side `nSide` holds card `nCardNo` and can summon it (its slot into `bCombo`, the card into `pCardInfo`);
   returns its kind group or -1. */
s32 TaLogic014_GetSpecCardPlay(s32 nSide, void *bCombo, void *pCardInfo, s32 nCardNo) {
    s32 entries[8];
    s32 i;
    s32 *p;
    s32 key;

    TaHand_GetNextHand(nSide, entries);
    i = 0;
    if (0 < TaHand_GetNextHandNum(nSide)) {
        key = nCardNo & 0xFFFF;
        p = entries;
        do {
            if (key == *p && TaHand_CanAffordSummonCost(nSide, *p) == 1) {
                ((s8 *)bCombo)[6] = i;
                SzDuel_InitCardInfo(pCardInfo, entries[i]);
                return TaHand_GetCardKind(entries[i]) >> 5;
            }
            p++;
            i++;
        } while (i < TaHand_GetNextHandNum(nSide));
    }
    return -1;
}

/* Whether side `nSide` plays a magic or ritual card from its hand now (its slot into `bCombo`, the card into
   `pCardInfo`). */
s32 TaLogic014_GetSpellPlay(s32 nSide, u8 *bCombo, void *pCardInfo, s32 nMode) {
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

typedef struct Info_0014D3E0 {
    u8 pad00[8];
    u16 x;
    s16 y;
} Info_0014D3E0;

typedef struct Sprite_0014D3E0 {
    Info_0014D3E0 *info;
    u8 pad04[0x34];
    s16 x;
    s16 y;
} Sprite_0014D3E0;

/* Fills hand combination `bCombo` for side `nSide`: the best fusion or equip chain, its card into `pCardInfo`. */
s32 TaLogic014_SetComboQue(s32 nSide, u8 *bCombo, void *pCardInfo) {
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
                            TaLogic_Mako_ConvEmptyCombo(nSide, *node, entries);
                            TaLogic_CopyArray((u8 *)*node + 2, bCombo + 6);
                            SzDuel_InitCardInfo(pCardInfo, **node);
                            ((Sprite_0014D3E0 *)pCardInfo)->x = (value >> 16) - (((Sprite_0014D3E0 *)pCardInfo)->info->x & 0x1FFF);
                            ((Sprite_0014D3E0 *)pCardInfo)->y = (value & 0xFFFF) - (((Sprite_0014D3E0 *)pCardInfo)->info->y & 0x1FFF);
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
} Info_0014D5C0;

/* Fills an empty combination: the hand card side `nSide` can summon with the best attack plus defence. */
void TaLogic_Mako_ConvEmptyCombo(s32 nSide, void *pCardInfo, s32 *pResult) {
    Info_0014D5C0 *info = pCardInfo;
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
                if (card != 0x3E7 && TaLogic014_IsRefuseEmptyCombo(card) == 0 && level >= TaHand_GetCardSummonCost2(card, nSide)) {
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
s32 TaLogic014_IsRefuseEmptyCombo(s32 nCardNo) {
    if (TaHand_GetCardKind(nCardNo) >> 5) {
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
} Obj1_0014D800;

typedef struct {
    u8 pad0[0x38];
    s16 f38;
    s16 f3A;
    u16 id;
} Obj2_0014D800;

/* Fills hand combination `bCombo` for side `nSide` with this duelist's special combination, its card into
   `pCardInfo`. */
s32 TaLogic014_SetSpecialComboQue(s32 nSide, void *bCombo, void *pCardInfo) {
    Obj1_0014D800 *o1 = bCombo;
    Obj2_0014D800 *o2 = pCardInfo;
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

/* Ta_GetSommonPiecePreference for this duelist. */
void TaLogic_Mako_GetSommonPiecePreference(s32 nSide, s32 nPr) {
    Ta_GetSommonPiecePreference(nSide, nPr);
}

typedef struct {
    u8 low : 4;
    u8 high : 4;
} Nibbles_0014DA40;

/* The first free line square, or -1. */
static inline s32 find_0014DA40(void) {
    s32 i;
    s32 position;
    s32 owner;

    i = 0;
    do {
        position = TaLogic014_GetLine(i);
        if ((SzDuel_GetMapUnit(position & 0xFF, position >> 8) == 0 ? 1 : 0) == 1) {
            owner = SzDuel_GetTurnOwner();
            switch (i) {
            case 0:
                position = Ta_GetSommonPiecePreference(owner, 0);
                break;
            case 1:
                position = Ta_GetSommonPiecePreference(owner, 3);
                break;
            case 2:
                position = Ta_GetSommonPiecePreference(owner, 4);
                break;
            default:
                position = -1;
                break;
            }
            return position;
        }
        i++;
    } while (i < 3);
    return -1;
}

/* The square side `nSide` summons a card of kind `sKind` to. */
s32 TaLogic014_GetSummonPiece(s32 nSide, u8 sKind, void *pInput, s32 nMode) {
    s32 bestPosition;
    s32 bestScore;
    s32 fallbackPosition;
    Nibbles_0014DA40 buffer[12];
    s32 initCount;
    Nibbles_0014DA40 *p;
    s32 kind;
    s32 type;
    s32 position;
    s32 y;
    s32 x;
    s32 i;
    s32 targetY;
    s32 targetX;
    s32 target;
    s32 score;
    extern s32 TaLogic_IsUnitWin4();
    extern s32 SzDuel_Kind2Type();
    extern s32 TaLogic_GetInvadeRoot2();
    extern s32 TaLogic_GetRoot2(s32, s32, s32, s32, s32, s32, u16, u8);

    if (pInput == NULL) {
        return -1;
    }
    p = buffer;
    initCount = 0;
    do {
        initCount++;
        p->low = p->high = 15;
        p++;
    } while (initCount < 12);

    kind = (type = (u8)(*((u8 *)pInput + 0x3E) >> 5));
    if (kind == 0 || SzDuel_Kind2Type(kind, type) == 2) {
        if (nMode >= 0) {
            bestScore = 0xFF;
            bestPosition = 0xFFFF;
            target = SzDuel_GetUnitLoc(nMode >> 8, nMode & 0xFF);
            i = 0;
            targetY = target >> 8;
            targetX = target & 0xFF;
            do {
                position = Ta_GetSommonPiecePreference(nSide, i);
                if (position >= 0) {
                    x = position & 0xFF;
                    y = position >> 8;
                    if (SzDuel_GetField(x, y) != 8 &&
                        (SzDuel_GetField(x, y) != 9 || Ta_IsVirus_Chk3(pInput, x, y) != 1) &&
                        SzDuel_GetMapUnit(x, y) == 0) {
                        if (TaLogic_IsUnitWin4((s32)pInput, nMode, TaLogic_Mako_GetWarnHideLvl(nSide),
                                         targetX, targetY, 0) > 0) {
                            score = TaLogic_GetInvadeRoot2((s32)pInput, (s32)buffer, x, y,
                                                 targetX, targetY, nMode, 0, 3,
                                                 (u16)TaLogic_Mako_GetWarnHideLvl(nSide));
                        } else {
                            score = TaLogic_GetRoot2((s32)pInput, (s32)buffer, x, y,
                                                 targetX, targetY, nMode, 3);
                        }
                        if (TaLogic_GetMinGoalCount((u8 *)buffer) > 0 && score < bestScore) {
                            bestScore = score;
                            bestPosition = position;
                        }
                    }
                }
                i++;
            } while (i < 8);
            if (bestPosition != 0xFFFF) {
                return bestPosition;
            }
        }
        {
            s32 y;
            s32 x;
            s32 targetY;
            s32 targetX;
            s32 target;
            s32 score;
            s32 limit;

            limit = 14;
            fallbackPosition = -1;
            i = 0;
            do {
                nMode = Ta_GetSommonPiecePreference(nSide, i);
                if (nMode >= 0) {
                    x = nMode & 0xFF;
                    y = nMode >> 8;
                    if (SzDuel_GetField(x, y) != 8 &&
                        (SzDuel_GetField(x, y) != 9 || Ta_IsVirus_Chk3(pInput, x, y) != 1) &&
                        SzDuel_GetMapUnitID(x, y) < 0) {
                        target = find_0014DA40();
                        targetX = target & 0xFF;
                        targetY = target >> 8;
                        SzDuel_GetMapUnitID(targetX, targetY);
                        score = TaLogic_GetRoot2((s32)pInput, (s32)buffer, x, y,
                                             targetX, targetY, 0, 7);
                        if (score < limit && score >= 0) {
                            fallbackPosition = nMode;
                            limit = score;
                        }
                    }
                }
                i++;
            } while (i < 8);
            if (limit < 14) {
                return fallbackPosition;
            }
            fallbackPosition = -1;
            return fallbackPosition;
        }
    } else {
        s32 y;
        s32 x;
        s32 i;
        s32 selected;
        s32 position;

        selected = -1;
        i = 0;
        do {
            position = Ta_GetSommonPiecePreference(nSide, i);
            if (position >= 0) {
                x = position & 0xFF;
                y = position >> 8;
                if (SzDuel_GetField(x, y) != 8 &&
                    (SzDuel_GetField(x, y) != 9 || Ta_IsVirus_Chk3(pInput, x, y) != 1) &&
                    SzDuel_GetMapUnitID(x, y) < 0 && y < 8) {
                    selected = position;
                }
            }
            i++;
        } while (i < 8);
        if (selected >= 0) {
            return selected;
        }
        selected = -1;
        return selected;
    }
}

typedef struct Nibbles_0014DF80 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_0014DF80;

typedef struct Output_0014DF80 {
    u16 position;
    u8 action;
    u8 pad3;
    u16 destination;
    u8 pad6[6];
    s32 special;
    u8 result;
} Output_0014DF80;

/* The task of a unit running from danger (task `pTask`): the safest square in reach, into `pInput` (`fFirst` = 1
   for the unit's first-choice task). */
s32 TaLogic_Mako_GetMinimumTask_RunMission(u16 *pTask, s32 nSide, void *pInput, u8 fFirst) {
    Output_0014DF80 *output = pInput;
    s32 target;
    u8 endX;
    u8 extra;
    Nibbles_0014DF80 nibbles[12];
    s32 bestScore;
    s32 best;
    s32 i;
    Nibbles_0014DF80 *p;
    extern s32 TaLogic_Mako_IsOpenUnit();
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

        initialScore = TaLogic_Mako_GetWarnHideLvl(nSide);
        centerX = target & 0xFF;
        centerY = target >> 8;
        if (TaLogic_GetUnitWarning(centerX, centerY, *pTask, 3, initialScore, 0) == 0) {
            output->position = *pTask;
            output->action = 6;
            output->destination = target;
            output->result = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, output->destination, 1, 0);
            output->special = TaLogic_Mako_IsOpenUnit(*pTask >> 8, *pTask & 0xFF, pTask);
            TaLogic_InitRogicControl(pTask, fFirst);
            return 0;
        }
        if ((range = GetMoveRange(SzDuel_GetUnit(*pTask >> 8, *pTask & 0xFF), centerX, centerY)) == 0) {
            output->position = *pTask;
            output->action = 6;
            output->destination = target;
            output->result = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, output->destination, 1, 0);
            output->special = TaLogic_Mako_IsOpenUnit(*pTask >> 8, *pTask & 0xFF, pTask);
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
                        candidateScore = TaLogic_GetUnitWarning(x, y, *pTask, 3, (u16)TaLogic_Mako_GetWarnHideLvl(nSide), 0);
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
            output->special = TaLogic_Mako_IsOpenUnit(*pTask >> 8, *pTask & 0xFF, pTask);
        } else {
            output->position = *pTask;
            output->action = 6;
            output->destination = target;
            output->result = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, output->destination, 1, 0);
            output->special = TaLogic_Mako_IsOpenUnit(*pTask >> 8, *pTask & 0xFF, pTask);
        }
        TaLogic_InitRogicControl(pTask, fFirst);
        return 0;
    }
}

typedef struct {
    u16 position;
    u8 pad2[6];
    u32 targets;
} Input_0014E550;

typedef struct {
    u16 position;
    u8 action;
    u8 pad3;
    u16 destination;
    u8 pad6[6];
    s32 flag;
    u8 result;
} Output_0014E550;

typedef struct {
    u8 x : 4;
    u8 y : 4;
} Point_0014E550;

/* The task's target square: the second half-word when the second argument is 1, else the first. */
static inline u32 target_0014E550(void *src, u8 mode) {
    Input_0014E550 *input = src;
    if (mode == 1) {
        return (input->targets >> 16) & 0xFFFF;
    }
    return *(u16 *)&input->targets;
}

/* The task of a unit attacking (task `pTask`): its path to the goal, into `pInput`; -1 when it has none (`fFirst`
   = 1 for the unit's first-choice task). */
s32 TaLogic_Mako_GetMinimumTask_AtkMission(void *pTask, s32 nSide, void *pInput, u8 fFirst) {
    extern s32 TaLogic_Mako_IsOpenUnit();
    extern void TaLogic_GetInvadeRoot();
    extern s32 GetMoveRange(s32, s32, s32);
    extern s32 TaLogic_GetUnitWarning(s32, s32, s32, s32, s32, u8);
    s32 sourcePosition;
    s32 count;
    s32 sourceY;
    s32 sourceX;
    s32 flag;
    Point_0014E550 points[12];
    s32 destination;
    s32 oldFlag;
    s32 i;
    s32 best;
    u32 targetX;
    u32 targetY;
    Point_0014E550 *p;
    Input_0014E550 *input = pTask;
    Output_0014E550 *output = pInput;

    targetX = target_0014E550(input, fFirst);
    targetY = target_0014E550(input, fFirst);
    if (SzDuel_GetUnit(targetY >> 8, targetX & 0xFF) == 0) {
        TaLogic_InitRogicControl(input, 1);
        return -1;
    }
    oldFlag = TaLogic_Mako_IsOpenUnit(input->position >> 8, input->position & 0xFF, input);
    sourcePosition = SzDuel_GetUnitLoc(input->position >> 8, input->position & 0xFF);
    targetX = target_0014E550(input, fFirst);
    targetY = target_0014E550(input, fFirst);
    destination = SzDuel_GetUnitLoc(targetY >> 8, targetX & 0xFF);
    p = points;
    i = 0;
    do {
        i++;
        p->x = p->y = 15;
        p++;
    } while (i < 12);
    {
        s32 unitInfo = SzDuel_GetUnit(input->position >> 8, input->position & 0xFF);
        sourceX = sourcePosition & 0xFF;
        sourceY = sourcePosition >> 8;
        if (GetMoveRange(unitInfo, sourceX, sourceY) == 0) {
            s32 cost;
            output->position = input->position;
            output->action = 6;
            output->destination = sourcePosition;
            cost = TaLogic_GetUnitWarning(sourceX, sourceY, nSide, 3, 1, (u8)TaLogic_Mako_GetWarnHideLvl(nSide));
            if (cost >= SzDuel_GetUnitAP(input->position >> 8, input->position & 0xFF, 0)) {
                output->result = TaLogic_IsDefStyleUnit(input->position >> 8, input->position & 0xFF,
                                             output->destination, 1, 0);
            } else {
                output->result = TaLogic_IsDefStyleUnit(input->position >> 8, input->position & 0xFF,
                                             output->destination, 0, 0);
            }
            TaLogic_InitRogicControl(input, fFirst);
            return 0;
        } else {
            s32 position = input->position;
            s32 destinationX;
            Point_0014E550 *candidate;
            s32 n;
            s32 minCost;
            s32 identity;
            s32 positionY;
            s32 positionX;

            identity = (u16)TaLogic_Mako_GetWarnHideLvl(nSide);
            positionY = position >> 8;
            positionX = position & 0xFF;
            destinationX = destination & 0xFF;

            TaLogic_GetInvadeRoot(positionY, positionX, points,
                         sourceX, sourceY, destinationX, destination >>= 8,
                         target_0014E550(input, fFirst), 0, 30, identity);
            count = TaLogic_GetMinGoalCount((u8 *)points);
            best = 0xFF;
            if (count > 0) {
                flag = 0;
                minCost = 0xFFFF;
                for (n = 0; n < count; n++) {
                    if (TaLogic014_IsOpenMoveUnit(input->position >> 8, input->position & 0xFF,
                                     sourceX, sourceY, destinationX, destination) == 1) {
                        best = n;
                        flag = 1;
                        points[n].x = destinationX;
                        points[n].y = destination;
                        n = count;
                    } else {
                        s32 cost;
                        candidate = &points[n];
                        cost = TaLogic_GetUnitWarning(candidate->x, candidate->y, nSide,
                                                3, 1, (u8)TaLogic_Mako_GetWarnHideLvl(nSide));
                        if (cost < minCost) {
                            minCost = cost;
                            best = n;
                        } else if (cost == minCost) {
                            if ((MaxSel(candidate->x, destinationX) -
                                 (candidate->x < destinationX ? candidate->x : destinationX)) +
                                (MaxSel(candidate->y, destination) -
                                 (candidate->y < destination ? candidate->y : destination)) <
                                (MaxSel(points[best].x, destinationX) -
                                 (points[best].x < destinationX ? points[best].x : destinationX)) +
                                (MaxSel(points[best].y, destination) -
                                 (points[best].y < destination ? points[best].y : destination))) {
                                minCost = cost;
                                best = n;
                            }
                        }
                    }
                }
            } else {
                output->position = input->position;
                output->action = 6;
                output->destination = sourcePosition;
                output->flag = oldFlag;
                output->result = TaLogic_IsDefStyleUnit(input->position >> 8, input->position & 0xFF,
                                             output->destination, 0, 0);
                TaLogic_InitRogicControl(input, fFirst);
                return 0;
            }
                if (best != 0xFF) {
                    output->position = input->position;
                    output->action = 6;
                    output->destination = (points[best].y << 8) | points[best].x;
                    output->flag = flag;
                    output->result = TaLogic_IsDefStyleUnit(input->position >> 8, input->position & 0xFF,
                                                 output->destination, 0, 0);
                } else {
                    output->position = input->position;
                    output->action = 6;
                    output->destination = sourcePosition;
                    output->flag = flag;
                    output->result = TaLogic_IsDefStyleUnit(input->position >> 8, input->position & 0xFF,
                                                 output->destination, 0, 0);
                    TaLogic_InitRogicControl(input, fFirst);
                    return 0;
                }

        }
    }
    return 0;
}

typedef struct Coord_0014EB30 {
    u8 x : 4;
    u8 y : 4;
} Coord_0014EB30;

typedef struct Unit_0014EB30 {
    u16 position;
    u8 pad2[6];
    union {
        u32 packed;
        u16 low;
    } target;
} Unit_0014EB30;

typedef struct Output_0014EB30 {
    u16 position;
    u8 kind;
    u8 pad3;
    u16 target;
    u8 pad6[6];
    s32 value;
    u8 flag;
} Output_0014EB30;

/* The task's target square: the second half-word when the second argument is 1, else the first. */
static inline u32 target_0014EB30(void *unit, s32 side) {
    return side == 1 ? (u32)(u16)(((Unit_0014EB30 *)unit)->target.packed >> 16) : (u32)((Unit_0014EB30 *)unit)->target.low;
}

/* The smaller of the two values. */
static inline u32 minY_0014EB30(void *unit, s32 side, u8 coord) {
    return coord < (target_0014EB30(unit, side) >> 8) ? coord : (target_0014EB30(unit, side) >> 8);
}

/* The larger of the two values. */
static inline u32 maxY_0014EB30(void *unit, s32 side, u8 coord) {
    return (target_0014EB30(unit, side) >> 8) < coord ? coord : (target_0014EB30(unit, side) >> 8);
}

/* The smaller of the two values. */
static inline u32 minX_0014EB30(void *unit, s32 side, u8 coord) {
    return coord < (target_0014EB30(unit, side) & 0xFF) ? coord : (target_0014EB30(unit, side) & 0xFF);
}

/* The larger of the two values. */
static inline u32 maxX_0014EB30(void *unit, s32 side, u8 coord) {
    return (target_0014EB30(unit, side) & 0xFF) < coord ? coord : (target_0014EB30(unit, side) & 0xFF);
}

/* The task of a unit moving to its goal (task `pTask`), into `pInput` (`fFirst` = 1 for the unit's first-choice
   task). */
s32 TaLogic_Mako_GetMinimumTask_MoveMission(void *pTask, s32 nSide, void *pInput, u8 fFirst, u8 nKind) {
    extern s32 TaLogic_Mako_IsOpenUnit();
    extern s32 TaLogic_GetUnitWarning();
    extern void TaLogic_GetRoot();
    extern s32 TaLogic_IsDefStyleUnit(s32, s32, s32, u8, s32);
    Coord_0014EB30 coords[12];
    s32 initial;
    s32 cell;
    s32 count;

    initial = SzDuel_GetUnitLoc(((Unit_0014EB30 *)pTask)->position >> 8, ((Unit_0014EB30 *)pTask)->position & 0xFF);
    {
    s32 bestScore;
    s32 best;
    s32 side = fFirst;
    Coord_0014EB30 *candidate;
    s32 index;
    if (target_0014EB30(pTask, side) == 0xFFFF) {
        if (initial == target_0014EB30(pTask, side)) {
            ((Output_0014EB30 *)pInput)->position = ((Unit_0014EB30 *)pTask)->position;
            ((Output_0014EB30 *)pInput)->kind = 6;
            ((Output_0014EB30 *)pInput)->target = initial;
            ((Output_0014EB30 *)pInput)->flag = TaLogic_IsDefStyleUnit(((Unit_0014EB30 *)pTask)->position >> 8, ((Unit_0014EB30 *)pTask)->position & 0xFF, ((Output_0014EB30 *)pInput)->target, nKind, 0);
            ((Output_0014EB30 *)pInput)->value = TaLogic_Mako_IsOpenUnit(((Unit_0014EB30 *)pTask)->position >> 8, ((Unit_0014EB30 *)pTask)->position & 0xFF, pTask);
            TaLogic_InitRogicControl(pTask, fFirst);
            return 0;
        }
    }

    if (SzDuel_GetUnitStatus(((Unit_0014EB30 *)pTask)->position >> 8,
                      ((Unit_0014EB30 *)pTask)->position & 0xFF, 4) != 0) {
        if ((SzDuel_GetUnitKind(((Unit_0014EB30 *)pTask)->position >> 8,
                          ((Unit_0014EB30 *)pTask)->position & 0xFF) >> 5) == 1 ||
            (SzDuel_GetUnitKind(((Unit_0014EB30 *)pTask)->position >> 8,
                          ((Unit_0014EB30 *)pTask)->position & 0xFF) >> 5) == 5) {
            SzDuel_SetUnitStatus(((Unit_0014EB30 *)pTask)->position >> 8,
                          ((Unit_0014EB30 *)pTask)->position & 0xFF, 0, 1);
            ((Output_0014EB30 *)pInput)->position = ((Unit_0014EB30 *)pTask)->position;
            ((Output_0014EB30 *)pInput)->kind = 0xE;
            return 0;
        }
    }

    candidate = coords;
    {
        s32 i = 0;
        Coord_0014EB30 *entry = candidate;
        do {
            entry->x = entry->y = 0xF;
            i++;
            entry++;
        } while (i < 12);
    }

    cell = SzDuel_GetMapUnitID(target_0014EB30(pTask, side) & 0xFF, ((u32)target_0014EB30(pTask, side)) >> 8);
    if (cell < 0) {
        cell = 0xFFFF;
    }
    TaLogic_GetRoot(((Unit_0014EB30 *)pTask)->position >> 8, ((Unit_0014EB30 *)pTask)->position & 0xFF,
                 coords, initial & 0xFF, initial >> 8, target_0014EB30(pTask, side) & 0xFF,
                 ((u32)target_0014EB30(pTask, side)) >> 8, (u16)cell, 7);
    count = TaLogic_GetMinGoalCount((u8 *)coords);
    {
        if (count > 0) {
        best = 0xFF;
        bestScore = 0xFFFF;
        for (index = 0; index < count; index++) {
                if (SzDuel_GetMapUnit(candidate->x, candidate->y) == 0) {
                    s32 score = TaLogic_GetUnitWarning(candidate->x, candidate->y, nSide, 3, 1, (u8)TaLogic_Mako_GetWarnHideLvl(nSide));
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
                        bestMinY = minY_0014EB30(pTask, side, bestY);
                        bestMaxY = maxY_0014EB30(pTask, side, bestY);
                        bestX = (&coords[best])->x;
                        bestMinX = minX_0014EB30(pTask, side, bestX);
                        bestMaxX = maxX_0014EB30(pTask, side, bestX);
                        currentY = (u8)candidate->y;
                        currentMinY = minY_0014EB30(pTask, side, currentY);
                        currentMaxY = maxY_0014EB30(pTask, side, currentY);
                        currentX = candidate->x;
                        currentMinX = minX_0014EB30(pTask, side, currentX);
                        currentMaxX = maxX_0014EB30(pTask, side, currentX);
                        if ((currentMaxX - currentMinX) + (currentMaxY - currentMinY) < (bestMaxX - bestMinX) + (bestMaxY - bestMinY)) {
                            bestScore = score;
                            best = index;
                        }
                    }
                }
            candidate++;
        }
    } else {
        ((Output_0014EB30 *)pInput)->position = ((Unit_0014EB30 *)pTask)->position;
            ((Output_0014EB30 *)pInput)->kind = 6;
            ((Output_0014EB30 *)pInput)->target = initial;
            ((Output_0014EB30 *)pInput)->flag = TaLogic_IsDefStyleUnit(((Unit_0014EB30 *)pTask)->position >> 8, ((Unit_0014EB30 *)pTask)->position & 0xFF, ((Output_0014EB30 *)pInput)->target, nKind, 0);
            ((Output_0014EB30 *)pInput)->value = TaLogic_Mako_IsOpenUnit(((Unit_0014EB30 *)pTask)->position >> 8, ((Unit_0014EB30 *)pTask)->position & 0xFF, pTask);
        TaLogic_InitRogicControl(pTask, fFirst);
        return 0;
    }

        if (best != 0xFF) {
            ((Output_0014EB30 *)pInput)->position = ((Unit_0014EB30 *)pTask)->position;
            ((Output_0014EB30 *)pInput)->kind = 6;
            ((Output_0014EB30 *)pInput)->target = (coords[best].y << 8) | coords[best].x;
            ((Output_0014EB30 *)pInput)->flag = TaLogic_IsDefStyleUnit(((Unit_0014EB30 *)pTask)->position >> 8, ((Unit_0014EB30 *)pTask)->position & 0xFF, ((Output_0014EB30 *)pInput)->target, nKind, 0);
            ((Output_0014EB30 *)pInput)->value = TaLogic_Mako_IsOpenUnit(((Unit_0014EB30 *)pTask)->position >> 8, ((Unit_0014EB30 *)pTask)->position & 0xFF, pTask);
        } else {
            ((Output_0014EB30 *)pInput)->position = ((Unit_0014EB30 *)pTask)->position;
            ((Output_0014EB30 *)pInput)->kind = 6;
            ((Output_0014EB30 *)pInput)->target = initial;
            ((Output_0014EB30 *)pInput)->flag = TaLogic_IsDefStyleUnit(((Unit_0014EB30 *)pTask)->position >> 8, ((Unit_0014EB30 *)pTask)->position & 0xFF, ((Output_0014EB30 *)pInput)->target, nKind, 0);
            ((Output_0014EB30 *)pInput)->value = TaLogic_Mako_IsOpenUnit(((Unit_0014EB30 *)pTask)->position >> 8, ((Unit_0014EB30 *)pTask)->position & 0xFF, pTask);
        }
        TaLogic_InitRogicControl(pTask, fFirst);
    }
    }
    return 0;
}

/* Line square `index` (0..2) for side `id`, or -1. */
static inline s32 dispatch_0014F3A0(s32 index, s32 id) {
    switch (index) {
    case 0:
        return Ta_GetSommonPiecePreference(id, 0);
    case 1:
        return Ta_GetSommonPiecePreference(id, 3);
    case 2:
        return Ta_GetSommonPiecePreference(id, 4);
    default:
        return -1;
    }
}

/* The first free line square, or -1. */
static inline s32 select_0014F3A0(void) {
    s32 index;
    s32 position;
    s32 id;

    index = 0;
    do {
        position = TaLogic014_GetLine(index);
        if (((SzDuel_GetMapUnit(position & 0xFF, position >> 8) == 0) ? 1 : 0) == 1) {
            id = SzDuel_GetTurnOwner();
            return dispatch_0014F3A0(index, id);
        }
        index++;
    } while (index < 3);
    return -1;
}

/* Whether this duelist plays in its attacking mode this turn. */
s32 TaLogic014_IsActiveMode(void) {
    s32 result;

    result = select_0014F3A0();
    if (result < 0) {
        return 1;
    }
    return 0;
}

/* From the dotr-decomp CC0 bundle (commit 88c32bb2), chatC/imp/conv.py. */

extern int func_0027D830_b(int, int, int, int, int, int);
extern int func_001E1030_b(int a, int b);
extern unsigned *func_001E0B70_b(int a, int b, int n);
struct DotrStateItem;
extern struct DotrStateItem *func_001E36E0_b(int x, int y);
/* The first free line square, or -1. */
static inline int spot_find(void)
{
    int i;
    int spot;

    for (i = 0; i < 3; i++) {
        spot = TaLogic014_GetLine(i);
        if ((func_001E36E0_b(spot & 0xff, spot >> 8) == 0 ? 1 : 0) == 1) {
            return TaLogic014_GetLine(i);
        }
    }
    return -1;
}

/* Whether this duelist opens (turns face up) unit (nSide, nID) now: 0 no, 1 or 2 by its kind. */
int TaLogic_Mako_IsOpenUnit(int nSide, int nID)
{
    int kind;
    int pos;
    int side;
    unsigned *p;
    int r;
    kind = func_001E1030_b(nSide, nID);
    pos = SzDuel_GetUnitLoc(nSide, nID);
    side = Ta_IsUnitControl(nSide, nID);
    p = func_001E0B70_b(nSide, nID, 0);
    if (SzDuel_GetUnitStatus(nSide, nID, 4)) {
        return 0;
    }
    switch (SzDuel_GetUnitKind(nSide, nID) >> 5) {
    case 0:
        switch (kind) {
        case 612:
        case 551:
            if (TaLogic014_IsUnitNaturalEffectUse(side, kind) == 1) {
                return 1;
            }
            break;
        }
        return 2;
    case 5:
        if (func_0027D830_b(nSide, nID, 0, 0, 6, 0) == 5) {
            return 2;
        }
        if (TaLogic014_IsDoCerem(Ta_IsUnitControl(nSide, nID), kind) == 1) {
            if (SzDuel_GetField(pos & 0xFF, pos >> 8) != 9) {
                return 1;
            }
        }
        break;
    case 1:
        if (func_0027D830_b(nSide, nID, 0, 0, 6, 0) == 5) {
            return 2;
        }
        if (p == 0) {
            return 2;
        }
        switch (*p >> 8) {
        case 13:
            return 1;
        case 2:
            r = TaLogic_GetLandChange(SzDuel_GetUnit(nSide, nID), pos & 0xFF, pos >> 8, 4, 9, 2);
            if (r >= 0 && r == pos) {
                return 1;
            }
            break;
        case 4:
            if ((spot_find() < 0 ? 1 : 0) == 1) {
                if (SzDuel_GetUnitSpellCount(nSide) == 0) {
                    return 1;
                }
            }
            break;
        case 18:
            if (SzDuel_GetUnitMonsterCount(nSide) >= 4) {
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
s32 TaLogic014_IsOpenMoveUnit(s32 nSide, s32 nID, s32 nX, s32 nZ, s32 gX, s32 gZ) {
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
s32 TaLogic014_IsDoCerem(s32 nSide, s32 nCardNo) {
    s32 sp50[4];
    s32 i;
    s32 mask;
    s32 low;
    s32 high;
    s32 cell;
    s32 value;

    Ta_GetCeremSacrifice(sp50, *(s32 *)((u8 *)TaHand_GetCardEffect(nCardNo, 0) + 4));
    if ((mask = Ta_GetSacrificeUnit(sp50, nSide)) < 0) {
        return 0;
    }
    for (i = 0; i < Ta_GetUnitNumFrom22bitFlagList(mask); i++) {
        cell = Ta_GetUnitOwnerIDFromLstCount(mask, i);
        high = cell >> 8;
        low = cell & 0xFF;
        value = SzDuel_GetUnitLoc(high, low);
        if (TaUtil_GetUnitAP(high, low, value & 0xFF, value >> 8) >= 0x9C4) {
            return 0;
        }
    }
    return 1;
}

/* How careful this duelist is about hidden cards (by its life points and monster count). */
s32 TaLogic_Mako_GetWarnHideLvl(s32 nSide) {
    if (SzDuel_GetLP(nSide) > 0x4B0) {
        if (SzDuel_GetUnitMonsterCount(nSide) >= 5) {
            return 0x2EE;
        } else {
            return 0x5DC;
        }
    } else {
        return 0x960;
    }
}

/* Whether side `nSide` should use the standing effect of card `nCardNo` now (enough targets in range). */
s32 TaLogic014_IsUnitNaturalEffectUse(s32 nSide, s32 nCardNo) {
    s32 index;
    u8 count;
    s32 mask;
    s32 entry;

    count = 0;
    switch (nCardNo) {
    case 0x264:
        if (Ta_GetUnitNumFrom22bitFlagList(SearchUnitByRange(0, 0, nSide, 1, 0x10, 0xE)) <= 3) {
            break;
        }
        return 1;
    case 0x227:
        if (Ta_GetUnitNumFrom22bitFlagList(SearchUnitByRange(0, 0, nSide, 1, 0xF, 0xE)) > 0) {
            return 0;
        }
        mask = SearchUnitByRange(0, 0, nSide, 2, 0xF, 0xE);
        for (index = 0; index < Ta_GetUnitNumFrom22bitFlagList(mask); index++) {
            entry = Ta_GetUnitOwnerIDFromLstCount(mask, index);
            if (TaLogic_CanSeeUnit(entry >> 8, entry & 0xFF, 0) == 1) {
                count++;
            }
        }
        if (count >= 2) {
            return 1;
        }
        break;
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
} Req_0014FB70;

typedef struct {
    u8 pad0[0x160];
    u16 list[32];    /* 0x160 */
    u8 idx : 5;      /* 0x1A0 */
    u8 pad1A0 : 3;
    u8 pad1A1;
    u16 count;       /* 0x1A2 */
} Work_0014FB70;

s32 TaLogic_GetInputQueFromMinimumTask_b(void *, void *, s32);

/* Computer duelist 14's controller (duelistControllers[14]): the buttons it presses this frame. With an empty
   input queue it plans its next task and turns it into buttons, then plays the queue back one button per frame;
   after 600 frames it gives up the turn (0x20, then 0x800). */
s32 duelistController14(s32 wCursorPos, void *pCtl) {
    Req_0014FB70 req;
    Work_0014FB70 *w;
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
        if (TaLogic_Mako_GetMinimumTask(w, &req, wCursorPos) == 0) {
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

/* Computer AI of Tea (duelist 11, duelistController11). */

#include "common.h"

s32 TaLogic_GetInputQueFromMinimumTask_b(void *, void *, s32);
#pragma conditional_move off

/* This duelist's move: picks the next unit to act, gives it a task and turns that into input `pInput`; returns 1
   when it set one. */
s32 TaLogic_Tea_GetMinimumTask(void *pCtl, void *pInput, s32 wCursorPos) {
    UnitTask *tasks = pCtl;
    s32 side;
    s32 found;
    s32 result;
    s32 index;

    side = SzDuel_GetTurnOwner();
    found = 0;
    if ((result = TaLogic_Tea_GetNextActiveUnit(tasks, side, (s32)pInput)) < 0) {
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
    TaLogic_Tea_CommandUnit(&tasks[index]);
    switch ((tasks[index].mission >> 8) & 0xFF) {
    case TASK_RUN:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            TaLogic_Tea_GetMinimumTask_RunMission(&tasks[index], side, pInput, 1);
            found = 1;
        }
        break;
    case TASK_ATTACK:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            if (TaLogic_Tea_GetMinimumTask_AtkMission(&tasks[index], side, pInput, 1) < 0) {
                TaLogic_InitRogicControl(&tasks[index], 1);
                return 1;
            }
            found = 1;
        }
        break;
    case TASK_SUMMON:
        if (TaLogic_Tea_GetMinimumTask_Summon(tasks[index].ownerId, side, (s32)pInput) < 0) {
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
            TaLogic_Tea_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 1, 0);
            found = 1;
        }
        break;
    case TASK_CONFIRMUNIT:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            TaLogic_Tea_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 1, 1);
            found = 1;
        }
        break;
    case TASK_ENCHANT:
        TaLogic_GetMinimumTask_EncMission(&tasks[index], side, pInput, 1, 0, TaLogic_Tea_GetWarnHideLvl(side), 2, 1);
        found = 1;
        break;
    case TASK_TRAP:
        TaLogic_Tea_GetMinimumTask_TrapMission(&tasks[index], side, pInput, 1);
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
            TaLogic_Tea_GetMinimumTask_RunMission(&tasks[index], side, pInput, 0);
            found = 1;
        }
        break;
    case 2:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            if (TaLogic_Tea_GetMinimumTask_AtkMission(&tasks[index], side, pInput, 0) < 0) {
                TaLogic_Tea_GetMinimumTask_RunMission(&tasks[index], side, pInput, 0);
            }
            found = 1;
        }
        break;
    case 10:
        if (TaLogic_Tea_GetMinimumTask_Summon(tasks[index].ownerId, side, (s32)pInput) < 0) {
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
            TaLogic_Tea_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 0, 0);
            found = 1;
        }
        break;
    case 3:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            TaLogic_Tea_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 0, 1);
            found = 1;
        }
        break;
    case 11:
        found = 1;
        TaLogic_Tea_GetMinimumTask_TrapMission(&tasks[index], side, pInput, 0);
        break;
    case 9:
        TaLogic_GetMinimumTask_EncMission(&tasks[index], side, pInput, 0, 0, TaLogic_Tea_GetWarnHideLvl(side), 2, 1);
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
s32 TaLogic_Tea_CommandUnit(u8 *pCtl) {
    s32 category;
    s32 controllingSide;

    controllingSide = Ta_IsUnitControl(((UnitTask *)pCtl)->ownerId >> 8, ((UnitTask *)pCtl)->ownerId & 0xFF);
    if (SzDuel_GetUnit(((UnitTask *)pCtl)->ownerId >> 8, ((UnitTask *)pCtl)->ownerId & 0xFF) != 0) {
        if (SzDuel_GetUnitStatus(((UnitTask *)pCtl)->ownerId >> 8, ((UnitTask *)pCtl)->ownerId & 0xFF, 0) == 0) {
            if (((UnitTask *)pCtl)->ownerId != 0xFFFF) {
                if ((((UnitTask *)pCtl)->ownerId & 0xFF) == 0) {
                    if (*(s32 *)&((UnitTask *)pCtl)->goal.dwGoal == -1) {
                        if (TaLogic_IsAttackedNow(((UnitTask *)pCtl)->ownerId >> 8, ((UnitTask *)pCtl)->ownerId & 0xFF, 0) == 1) {
                            if (SzDuel_InqHandPhase(((UnitTask *)pCtl)->ownerId >> 8) == 1) {
                                ((UnitTask *)pCtl)->mission = 0x50A;
                            } else {
                                ((UnitTask *)pCtl)->mission = 0x5FF;
                            }
                        } else {
                            if (SzDuel_InqHandPhase(((UnitTask *)pCtl)->ownerId >> 8) == 1) {
                                ((UnitTask *)pCtl)->mission = 0xA05;
                            } else {
                                ((UnitTask *)pCtl)->mission = 0x5FF;
                            }
                        }
                    }
                } else {
                    category = SzDuel_GetUnitKind(((UnitTask *)pCtl)->ownerId >> 8, ((UnitTask *)pCtl)->ownerId & 0xFF) >> 5;
                    switch (category) {
                    case 0:
                        if (TaUtil_IsExMonster(((UnitTask *)pCtl)->ownerId >> 8, ((UnitTask *)pCtl)->ownerId & 0xFF) == 1) {
                            TaLogic011_CommandEfcMonster(pCtl);
                        } else {
                            TaLogic011_CommandBtlUnit(pCtl, 1);
                        }
                        break;
                    case 2:
                        TaLogic_CommandEncUnit(pCtl, 2, 0, TaLogic_Tea_GetWarnHideLvl(controllingSide) & 0xFF);
                        break;
                    case 3:
                        if (TaLogic_CommandGunnerUnit(pCtl, 0) == 1) {
                            ((UnitTask *)pCtl)->mission = 0xBFF;
                        } else {
                            ((UnitTask *)pCtl)->mission = 0x5FF;
                        }
                        break;
                    default:
                        ((UnitTask *)pCtl)->mission = 0x5FF;
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
s32 TaLogic_Tea_GetNextActiveUnit(DuelPlayer *pCtl, s32 nSide, s32 pInput) {
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
    TaLogic_Tea_CommandUnit(&pCtl->taskList[idx]);
    if (((pCtl->taskList[idx].mission >> 8) & 0xFF) == 10) {
        if (SzDuel_InqHandPhase(nSide) == 1 && TaLogic_Tea_GetMinimumTask_Summon(pos, nSide, pInput) >= 0) {
            return pos | 0x10000;
        }
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_GetUnitStatus(nSide, 0, 0) == 0) {
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_InqHandPhase(nSide) == 1 && TaLogic_Tea_GetMinimumTask_Summon(pos, nSide, pInput) >= 0) {
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
} Entry_0013E7B0;

typedef struct {
    u16 card;
    u8 flag;
    u8 pad;
} Slot_0013E7B0;

/* Orders a fighting unit (task `pTask`): straight at the enemy leader when `fGoalFirst` and the path is open,
   else at the nearest enemy it can beat. */
void TaLogic011_CommandBtlUnit(void *pTask, s32 fGoalFirst) {
    extern void TaLogic_InitIgnoreLst();
    extern s32 TaLogic_IsRootOpen();
    extern s32 TaLogic011_GetNearUnit();
    Entry_0013E7B0 *entry = pTask;
    s32 side;
    s32 player;
    s32 other;
    s32 pos;
    s32 otherPos;
    s32 i;
    u8 work[0x70];
    Slot_0013E7B0 list[22];
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
            switch (TaLogic011_GetNearUnit(entry, 0, player, pos & 0xFF, pos >> 8,
                                  Ta_GetCurrentSide(entry->unitId >> 8, entry->unitId & 0xFF) == 0 ? 1 : 0,
                                  i & 0xFF, TaLogic_Tea_GetWarnHideLvl(side), list, 0, &countA, &countB, 2, work)) {
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
        TaLogic011_CommandDefenseUnit(entry);
    }
}

/* TaLogic_GetNearUnit with this duelist's view and strength settings. */
s32 TaLogic011_GetNearUnit(s32 pTask, s32 pTree, s32 pVarInfo, s32 nX, s32 nZ, s32 eSide, s32 bDist, s32 WarnLvl, s32 nUnitLst, u16 wUnitNum, s32 wSize, s32 wNodeCount, u8 bChase, s32 wIgnoreLst) {
    return TaLogic_GetNearUnit(pTask, pTree, pVarInfo, nX, nZ, eSide, bDist, WarnLvl,
                  nUnitLst, wUnitNum, wSize, wNodeCount, bChase,
                  0, 0x708, wIgnoreLst);
}

typedef struct {
    u16 code;
    u16 unknown2;
    u16 state;
    u16 unknown6;
    u32 data;
} Entry_0013EA80;

/* Orders a unit (task `pTask`) to guard its leader. */
void TaLogic011_CommandDefenseUnit(void *pTask) {
    Entry_0013EA80 *entry = pTask;
    s32 packed;
    s32 result;

    packed = SzDuel_GetUnitLoc(entry->code >> 8, entry->code & 0xFF);
    Ta_IsUnitControl(entry->code >> 8, entry->code & 0xFF);
    result = TaLogic011_GetNearMountain(SzDuel_GetUnit(entry->code >> 8, entry->code & 0xFF), packed & 0xFF, packed >> 8);
    if (result >= 0) {
        entry->state = 0x6FF;
        entry->data = (result << 16) | (entry->data & 0xFFFF);
    } else {
        entry->state = 0x5FF;
    }
}

/* The nearest free mountain square to (nX, nZ) a unit (record `pVarInfo`) can hold. */
s32 TaLogic011_GetNearMountain(s32 pVarInfo, s32 nX, s32 nZ) {
    s32 x;
    s32 y;
    s32 card;
    s32 best;
    s32 dist;
    s32 result;
    extern s32 TaLogic_IsUnitWin4();

    best = 14;
    for (x = 0; x < 7; x++) {
        for (y = 0; y < 7; y++) {
            if (SzDuel_GetField(x, y) == 2) {
                if ((card = SzDuel_GetMapUnitID(x, y)) < 0) {
                    dist = (((nX < x) ? x : nX) - ((x < nX) ? x : nX)) + (((nZ < y) ? y : nZ) - ((y < nZ) ? y : nZ));
                    if (dist >= 0 && dist < best) {
                        best = dist;
                        result = (y << 8) | x;
                    }
                } else if (Ta_IsUnitControl(card >> 8, card & 0xFF) != Ta_IsUnitControl2((void *)pVarInfo)) {
                    if (TaLogic_IsUnitWin4(pVarInfo, card, TaLogic_Tea_GetWarnHideLvl(Ta_IsUnitControl2((void *)pVarInfo)), x, y, 0) > 0) {
                        dist = (((nX < x) ? x : nX) - ((x < nX) ? x : nX)) + (((nZ < y) ? y : nZ) - ((y < nZ) ? y : nZ));
                        if (dist >= 0 && dist < best) {
                            best = dist;
                            result = (y << 8) | x;
                        }
                    }
                }
            }
        }
    }
    return result;
}

struct InitEntry_0013ECF0 {
    u16 value;
    u8 flag;
    u8 pad;
};

/* Orders an effect monster (task `pTask`): where its effect does most. */
void TaLogic011_CommandEfcMonster(void *pTask) {
    extern s32 SzDuel_GetUnitCardNo();
    extern void TaLogic_InitIgnoreLst();
    u8 scratch[112];
    struct InitEntry_0013ECF0 entries[22];
    s32 i;
    struct InitEntry_0013ECF0 *entry;
    s32 card;
    s32 color;
    s32 code;
    s32 value;

    if (SzDuel_GetUnit((s32)*(u16 *)pTask >> 8, *(u16 *)pTask & 0xFF) == 0) {
        return;
    }

    card = Ta_GetCurrentSide((s32)*(u16 *)pTask >> 8, *(u16 *)pTask & 0xFF);
    color = SzDuel_GetUnitLoc((s32)*(u16 *)pTask >> 8, *(u16 *)pTask & 0xFF);
    entry = entries;
    i = 0;
    do {
        i++;
        entry->value = 0xFFFF;
        entry->flag = 0xFF;
        entry++;
    } while (i < 22);

    TaLogic_InitIgnoreLst(scratch);
    code = SzDuel_GetUnitCardNo((s32)*(u16 *)pTask >> 8, *(u16 *)pTask & 0xFF);
    switch (code) {
    case 0x182:
        if (TaLogic011_IsUseBindChain(card) == 1) {
            *(u16 *)((u8 *)pTask + 4) = 0x6FF;
            *(u32 *)((u8 *)pTask + 8) = (color << 16) | *(u16 *)((u8 *)pTask + 8);
            return;
        }
        break;
    case 0x184:
        value = SzDuel_GetLP(card);
        if (value < SzDuel_GetLP(card == 0 ? 1 : 0)) {
            *(u16 *)((u8 *)pTask + 4) = 0x6FF;
            *(u32 *)((u8 *)pTask + 8) = (color << 16) | *(u16 *)((u8 *)pTask + 8);
            return;
        }
        break;
    case 0x179:
        if ((TaLogic011_IsUseLifeHourGlass(card) == 1) && (TaLogic_CommandGunnerUnit(pTask, 0) == 1)) {
            *(u16 *)((u8 *)pTask + 4) = 0xBFF;
            return;
        }
        break;
    case 0x186:
        if ((TaLogic011_IsUseBraveHourGlass(card) == 1) && (TaLogic_CommandGunnerUnit(pTask, 0) == 1)) {
            *(u16 *)((u8 *)pTask + 4) = 0xBFF;
            return;
        }
        break;
    }
    TaLogic011_CommandBtlUnit(pTask, 1);
}

typedef struct {
    u8 data[0x3C];
    u16 unk3C;
    u8 pad3E[0x22];
} Work_0013EEE0;

typedef struct {
    s16 id;
    u8 kind;
    u8 pad3;
    s16 value;
    u8 pad6[6];
    s32 unkC;
} Ctx_0013EEE0;

/* The summon task for side `nSide`: which hand cards to play and where, into `pInput`; -1 when it plays none. */
s32 TaLogic_Tea_GetMinimumTask_Summon(s32 wUnit, s32 nSide, s32 pInput) {
    extern s32 TaLogic_GetUnitNum();
    Work_0013EEE0 work;
    s32 ret;
    s32 res;
    s32 pos;
    s32 kind;
    Ctx_0013EEE0 *ctx = (Ctx_0013EEE0 *)pInput;

    ctx->id = wUnit;
    if (SzDuel_InqHandPhase(nSide) == 0) {
        return -1;
    }
    if (TaLogic_GetUnitNum(nSide, 0) == 5 && TaLogic_GetUnitNum(nSide, 1) == 5) {
        return -1;
    }
    kind = TaLogic011_IsHandPlay(nSide, &work);
    if (kind < 0) {
        return -1;
    }
    ctx->kind = 10;
    ctx->unkC = 0;
    pos = SzDuel_GetUnitLoc(wUnit >> 8, wUnit & 0xFF);
    ret = TaLogic_GetNearCard2(&work, pos & 0xFF, pos >> 8, nSide == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, TaLogic_Tea_GetWarnHideLvl(nSide));
    if (kind == 0) {
        if (TaLogic011_SetComboQue(nSide, ctx, &work) >= 0) {
            if (ret < 0) {
                if (SzDuel_GetUnitMonsterCount(nSide) < 4) {
                    res = TaLogic011_GetSummonPiece(nSide, 0, &work, ret);
                    if (res < 0) {
                        return -1;
                    }
                    ctx->value = res;
                    return 1;
                }
            } else {
                res = TaLogic011_GetSummonPiece(nSide, 0, &work, ret);
                if (res < 0) {
                    return -1;
                }
                ctx->value = res;
                return 1;
            }
        }
    } else if (kind == 2) {
        TaLogic011_SetSpecialComboQue(nSide, ctx, &work);
        res = TaLogic011_GetSummonPiece(nSide, kind & 0xFF, &work, ret);
        if (res < 0) {
            return -1;
        }
        ctx->value = res;
        return 1;
    }
    if (kind == 3) {
        TaLogic011_GetSpecComboPlay(nSide, ctx, &work);
        res = TaLogic011_GetSummonPiece(nSide, kind & 0xFF, &work, ret);
        if (res < 0) {
            return -1;
        }
        ctx->value = res;
        return 1;
    }
    res = TaLogic011_GetSpellPlay(nSide, (u8 *)ctx, &work, work.unk3C);
    if (res < 0) {
        return -1;
    }
    res = TaLogic011_GetSummonPiece(nSide, res & 0xFF, &work, -1);
    if (res < 0) {
        return -1;
    }
    ctx->value = res;
    return 1;
}

/* Whether side `nSide` should play from its hand this turn (and what, into `pInput`). */
s32 TaLogic011_IsHandPlay(s32 nSide, void *pInput) {
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
        s32 result = TaLogic011_GetSpellPlay(nSide, (u8 *)data, pInput, 0x3E7);
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
    if (TaLogic011_IsUseReversalGoddess(nSide) == 1) {
        if (TaLogic011_GetSpecCardPlay(nSide, ids, pInput, data, 0x170) >= 0) {
            return 2;
        }
    }
    if (TaLogic011_GetSpecComboPlay(nSide, (u8 *)data, pInput) >= 0) {
        return 3;
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
                    return 0;
                }
                p++;
                i++;
                count = TaHand_GetNextHandNum(nSide);
            } while (i < count);
        }
    }
    {
        s32 result = TaLogic011_GetSpellPlay(nSide, (u8 *)data, pInput, 0x3E7);
        if (result >= 0) {
            return result;
        } else {
            return -1;
        }
    }
}

/* Whether side `nSide` can play this duelist's special combination (card 0x320 with its partner), into `bCombo`,
   `pCardInfo`. */
s32 TaLogic011_GetSpecComboPlay(s32 nSide, void *bCombo, void *pCardInfo) {
    s32 cards[8];
    s32 index;
    s32 found;
    s32 *first;
    s32 *second;
    s32 secondIndex;

    found = 0;
    TaHand_GetNextHand(nSide, cards);
    index = 0;
    if (index < TaHand_GetNextHandNum(nSide)) {
        first = cards;
        do {
            if (*first == 0x320) {
                *((s8 *)bCombo + 7) = index;
                SzDuel_InitCardInfo(pCardInfo, *first);
                found = 1;
            }
            first++;
            index++;
        } while (index < TaHand_GetNextHandNum(nSide));
    }
    if (found == 1) {
        secondIndex = 0;
        if (secondIndex < TaHand_GetNextHandNum(nSide)) {
            second = cards;
            do {
                if (((TaHand_GetCardKind(*second) >> 5) == 0) &&
                    (Ta_GetHandEnchant(*second, 0x320) >= 0) &&
                    (TaHand_IsCardSummon(nSide, *second) == 1)) {
                    if ((*second != 0x31B) && (*second != 0x31C)) {
                        *((s8 *)bCombo + 7) = secondIndex;
                        SzDuel_InitCardInfo(pCardInfo, cards[secondIndex]);
                        return TaHand_GetCardKind(cards[secondIndex]) >> 5;
                    }
                }
                second++;
                secondIndex++;
            } while (secondIndex < TaHand_GetNextHandNum(nSide));
        }
    }
    return -1;
}

/* Whether side `nSide` holds card `nCardNo` and can summon it (its slot into `bCombo`, the card into `pCardInfo`);
   returns its kind group or -1. */
s32 TaLogic011_GetSpecCardPlay(s32 nSide, s32 *bCombo, void *pCardInfo, void *nCardNo, s32 arg4) {
    s32 i;

    for (i = 0; i < TaHand_GetNextHandNum(nSide); i++) {
        if (TaHand_CanAffordSummonCost(nSide, bCombo[i]) == 1 &&
            (arg4 & 0xFFFF) == bCombo[i] &&
            TaHand_CanAffordSummonCost(nSide, bCombo[i]) == 1) {
            *((s8 *)nCardNo + 6) = i;
            SzDuel_InitCardInfo(pCardInfo, bCombo[i]);
            return TaHand_GetCardKind(bCombo[i]) >> 5;
        }
    }
    return -1;
}

/* Whether side `nSide` plays a magic or ritual card from its hand now (its slot into `bCombo`, the card into
   `pCardInfo`). */
s32 TaLogic011_GetSpellPlay(s32 nSide, u8 *bCombo, void *pCardInfo, s32 nMode) {
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
        if ((TaHand_GetCardKind(buf[i]) >> 5) != 0 && buf[i] != 0x320) {
            bCombo[6] = i;
            SzDuel_InitCardInfo(pCardInfo, buf[i]);
            return 1;
        }
    }
    return -1;
}

/* Fills hand combination `bCombo` for side `nSide`: the best fusion or equip chain, its card into `pCardInfo`. */
s32 TaLogic011_SetComboQue(s32 nSide, u8 *bCombo, u8 *pCardInfo) {
    extern s32 TaLogic_GetEnchantQue();
    s32 spA0[8];
    s32 spC0[7];
    s16 spDC;
    s16 spDE;
    s32 i;
    s32 temp_s6;
    s32 enchantQue;
    s32 var_s0;
    s32 var_s7;

    if (pCardInfo == NULL) {
        return -1;
    }
    TaHand_GetNextHand(nSide, spC0);
    var_s7 = -1;
    var_s0 = -1;
    i = 0;
    if (0 < TaHand_GetNextHandNum(nSide)) {
        s32 *var_s1;
        s32 *var_s2;

        var_s1 = spC0;
        var_s2 = spA0;
        do {
            spDE = 0;
            spDC = 0;
            temp_s6 = *var_s1;
            *var_s2 = 0;
            if ((TaHand_GetCardKind(temp_s6) >> 5) == 0) {
                if (Taku_Get_WinCount() < 3) {
                    *var_s2 = (s32)TaLogic_GetFusionTree2(
                        nSide, *var_s2, i & 0xFF, temp_s6 & 0xFFFF,
                        0, (u16 *)&spDC, (u16 *)&spDE);
                } else {
                    *var_s2 = (s32)TaLogic_GetFusionTree(
                        nSide, (struct TreeTag *)*var_s2, i & 0xFF, temp_s6 & 0xFFFF,
                        0, (u16 *)&spDC, (u16 *)&spDE);
                }
                *var_s2 = (s32)TaLogic_GetFusionRes((u16 *)*var_s2);
                enchantQue = TaLogic_GetEnchantQue(nSide, *var_s2, 0, 0);
                if (TaHand_CanAffordSummonCost(nSide, temp_s6) == 1) {
                    if (var_s7 < enchantQue) {
                        if (Taku_Get_WinCount() > 3) {
                            TaLogic_Tea_ConvEmptyCombo(nSide, (void *)*var_s2, spC0);
                        }
                        TaLogic_CopyArray((u8 *)*var_s2 + 2, bCombo + 6);
                        SzDuel_InitCardInfo(pCardInfo, *(u16 *)*var_s2);
                        var_s7 = enchantQue;
                        *(s16 *)(pCardInfo + 0x38) = (s16)((enchantQue >> 16)
                            - (*(u16 *)(*(u8 **)pCardInfo + 8) & 0x1FFF));
                        *(s16 *)(pCardInfo + 0x3A) = (s16)((enchantQue & 0xFFFF)
                            - (*(s16 *)(*(u8 **)pCardInfo + 0xA) & 0x1FFF));
                        if (var_s0 < enchantQue) {
                            var_s0 = enchantQue;
                        }
                    }
                } else if (var_s0 < enchantQue) {
                    var_s0 = enchantQue;
                }
            }
            var_s1 += 1;
            var_s2 += 1;
            i += 1;
        } while (i < TaHand_GetNextHandNum(nSide));
    }
    return var_s0;
}

typedef struct {
    u16 id;
    u8 values[5];
} Info_0013FA90;

/* Fills an empty combination: the hand card side `nSide` can summon with the best attack plus defence. */
void TaLogic_Tea_ConvEmptyCombo(s32 nSide, void *pCardInfo, s32 *pResult) {
    Info_0013FA90 *info = pCardInfo;
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
                if (card != 0x3E7 && TaLogic011_IsRefuseEmptyCombo(card) == 0 && level >= TaHand_GetCardSummonCost2(card, nSide)) {
                    cost = TaHand_GetCardAPDP(card);
                    if ((cost & 0xFFFF) + (cost >> 16) * 2 < 0xC1D && TaHand_IsCardEffect(card) == 2 &&
                        (u16)TaLogic_GetHandFusion(info->id, (u16)card) == 0x3E7) {
                        TaLogic_AddEmptyCombo(info->values, buf[i]);
                    }
                }
            }
        }
    }
}

/* Whether this duelist keeps card `nCardNo` out of a summon (it is wanted for an equip). */
s32 TaLogic011_IsRefuseEmptyCombo(s32 nCardNo) {
    if ((TaHand_GetCardKind(nCardNo) >> 5) != 0) {
        return 1;
    }
    return (TaHand_IsCardEffect(nCardNo) != 0) ? 1 : 0;
}

typedef struct {
    u8 pad0[6];
    u8 slot[5];
} Obj1_0013FCC0;

typedef struct {
    u8 pad0[0x3C];
    u16 id;
    u8 f3E;
} Obj2_0013FCC0;

/* Fills hand combination `bCombo` for side `nSide` with this duelist's special combination, its card into
   `pCardInfo`. */
s32 TaLogic011_SetSpecialComboQue(s32 nSide, void *bCombo, void *pCardInfo) {
    Obj1_0013FCC0 *o1 = bCombo;
    Obj2_0013FCC0 *o2 = pCardInfo;
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
            if (o2->id == list[i]) {
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

typedef struct Nibbles_0013FEB0 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_0013FEB0;

/* The square side `nSide` summons a card of kind `sKind` to. */
s32 TaLogic011_GetSummonPiece(s32 nSide, s32 sKind, void *pInput, s32 nMode) {
    extern s32 TaLogic_IsUnitWin4();
    extern s32 TaLogic_GetInvadeRoot2(s32, s32, s32, s32, s32, s32, s32, s32, u8, u16);
    extern s32 TaLogic_GetRoot2(s32, s32, s32, s32, s32, s32, u16, u8);
    s32 bestPosition;
    s32 bestScore;
    Nibbles_0013FEB0 path[12];
    s32 transformedY;
    s32 transformedX;
    s32 value;
    u8 mode;

    if (pInput == NULL) {
        return -1;
    }
    {
    s32 initIndex;
    Nibbles_0013FEB0 *p;
    p = path;
    initIndex = 0;
    do {
        p->low = p->high = 15;
        p++;
        initIndex++;
    } while (initIndex < 12);
    }
    mode = *((u8 *)pInput + 0x3E) >> 5;
    if (mode == 0 || mode == 3) {
        if (nMode >= 0) {
            s32 candidate;
            s32 candidateY;
            s32 candidateX;
            s32 index;
            s32 score;
            bestScore = 255;
            bestPosition = 65535;
            value = SzDuel_GetUnitLoc(nMode >> 8, nMode & 255);
            index = 0;
            transformedY = value >> 8;
            transformedX = value & 255;
            do {
                candidate = Ta_GetSommonPiecePreference(nSide, index);
                if (candidate >= 0) {
                    candidateX = candidate & 255;
                    candidateY = candidate >> 8;
                    if (SzDuel_GetField(candidateX, candidateY) != 8 &&
                        (SzDuel_GetField(candidateX, candidateY) != 9 ||
                         Ta_IsVirus_Chk3(pInput, candidateX, candidateY) != 1) &&
                        SzDuel_GetMapUnit(candidateX, candidateY) == 0) {
                        if (TaLogic_IsUnitWin4((s32)pInput, nMode, TaLogic_Tea_GetWarnHideLvl(nSide),
                                         transformedX, transformedY, 0) > 0) {
                            score = TaLogic_GetInvadeRoot2((s32)pInput, (s32)path,
                                                       candidateX, candidateY,
                                                       transformedX, transformedY,
                                                       nMode, 0, 2,
                                                       TaLogic_Tea_GetWarnHideLvl(nSide));
                        } else {
                            score = TaLogic_GetRoot2((s32)pInput, (s32)path,
                                                       candidateX, candidateY,
                                                       transformedX, transformedY,
                                                       nMode, 2);
                        }
                        if (TaLogic_GetMinGoalCount((u8 *)path) > 0 && score < bestScore) {
                            bestScore = score;
                            bestPosition = candidate;
                        }
                    }
                }
                index++;
            } while (index < 8);
            if (bestPosition != 65535) {
                return bestPosition;
            }
            bestPosition = -1;
            return bestPosition;
        } else {
        s32 maxY;
        s32 maxX;
        s32 y;
        s32 x;
        s32 i;
        s32 bestDistance;
        s32 position;
        s32 minY;
        s32 minX;
        bestDistance = 14;
        nMode = 0;
        i = 0;
        do {
            position = Ta_GetSommonPiecePreference(nSide, i);
            if (position >= 0) {
                x = position & 255;
                y = position >> 8;
                if (SzDuel_GetField(x, y) != 8 &&
                    (SzDuel_GetField(x, y) != 9 || Ta_IsVirus_Chk3(pInput, x, y) != 1) &&
                    SzDuel_GetMapUnitID(x, y) < 0) {
                    value = TaLogic011_GetNearMountain((s32)pInput, x, y);
                    if (y < (value >> 8)) {
                        minY = y;
                    } else {
                        minY = value >> 8;
                    }
                    if (y > (value >> 8)) {
                        maxY = y;
                    } else {
                        maxY = value >> 8;
                    }
                    if (x < (value & 255)) {
                        minX = x;
                    } else {
                        minX = value & 255;
                    }
                    if (x > (value & 255)) {
                        maxX = x;
                    } else {
                        maxX = value & 255;
                    }
                    value = (maxX - minX) + (maxY - minY);
                    if (value < bestDistance && value >= 0) {
                        nMode = position;
                        bestDistance = value;
                    }
                }
            }
            i++;
        } while (i < 8);
        if (bestDistance < 14) {
            return nMode;
        }
        goto failure;
        }
    }
    {
    s32 y;
    s32 x;
    s32 i;
    s32 best;
    best = -1;
    i = 0;
    do {
        nMode = Ta_GetSommonPiecePreference(nSide, i);
        if (nMode >= 0) {
            x = nMode & 255;
            y = nMode >> 8;
            if (SzDuel_GetField(x, y) != 8 &&
                (SzDuel_GetField(x, y) != 9 || Ta_IsVirus_Chk3(pInput, x, y) != 1) &&
                SzDuel_GetMapUnitID(x, y) < 0 && y < 8) {
                best = nMode;
            }
        }
        i++;
    } while (i < 8);
    if (best >= 0) {
        return best;
    }
    }
failure:
    return -1;
}

typedef struct {
    u8 low : 4;
    u8 high : 4;
} Flags_001402F0;

typedef struct {
    u16 id;
    u8 action;
    u8 pad3;
    u16 position;
    u8 pad6[6];
    s32 value;
    u8 mode;
} Output_001402F0;

/* The task of a unit running from danger (task `pTask`): the safest square in reach, into `pInput` (`fFirst` = 1
   for the unit's first-choice task). */
s32 TaLogic_Tea_GetMinimumTask_RunMission(UnitTask *pTask, s32 nSide, void *pInput, u8 fFirst) {
    extern s32 TaLogic_GetUnitWarning(s32, s32, s32, s32, s32, u8);
    extern s32 TaLogic_IsRunPassRoot(s32, s32, s32, s32, s32, s32, void *, u8);
    extern s32 TaLogic_Tea_IsOpenUnit();
    s32 position;
    u8 upperX;
    u8 flag;
    Flags_001402F0 cells[12];
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
    Output_001402F0 *out = pInput;

    position = SzDuel_GetUnitLoc(pTask->ownerId >> 8, pTask->ownerId & 0xFF);
    i = 0;
    do {
        cells[i].low = cells[i].high = 15;
        i++;
    } while (i < 12);

    {
        u16 value = (u16)TaLogic_Tea_GetWarnHideLvl(nSide);
        originalX = position & 0xFF;
        originalY = position >> 8;
        if (TaLogic_GetUnitWarning(originalX, originalY, pTask->ownerId, 3, value, 0) == 0) {
            out->id = pTask->ownerId;
            out->action = 6;
            out->position = position;
            out->mode = TaLogic_IsDefStyleUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, out->position, 1, 0);
            out->value = TaLogic_Tea_IsOpenUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, pTask);
            TaLogic_InitRogicControl(pTask, fFirst);
            return 0;
        } else {
            result = GetMoveRange(SzDuel_GetUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF), originalX, originalY);
            if (result == 0) {
                out->id = pTask->ownerId;
                out->action = 6;
                out->position = position;
                out->mode = TaLogic_IsDefStyleUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, out->position, 1, 0);
                out->value = TaLogic_Tea_IsOpenUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, pTask);
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
                                value = (u16)TaLogic_Tea_GetWarnHideLvl(nSide);
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
                    out->value = TaLogic_Tea_IsOpenUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, pTask);
                } else {
                    out->id = pTask->ownerId;
                    out->action = 6;
                    out->position = position;
                    out->mode = TaLogic_IsDefStyleUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, out->position, 1, 0);
                    out->value = TaLogic_Tea_IsOpenUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, pTask);
                }
                TaLogic_InitRogicControl(pTask, fFirst);
            }
        }
    }
    return 0;
}

typedef struct {
    u16 position;
    u8 pad2[6];
    u32 targets;
} Input_00140830;

typedef struct {
    u16 position;
    u8 action;
    u8 pad3;
    u16 destination;
    u8 pad6[6];
    s32 flag;
    u8 result;
} Output_00140830;

typedef struct {
    u8 x : 4;
    u8 y : 4;
} Point_00140830;

/* The task's target square: the second half-word when the second argument is 1, else the first. */
static inline u32 target_00140830(void *src, u8 mode) {
    Input_00140830 *input = src;
    if (mode == 1) {
        return (input->targets >> 16) & 0xFFFF;
    }
    return *(u16 *)&input->targets;
}

/* The task of a unit attacking (task `pTask`): its path to the goal, into `pInput`; -1 when it has none (`fFirst`
   = 1 for the unit's first-choice task). */
s32 TaLogic_Tea_GetMinimumTask_AtkMission(void *pTask, s32 nSide, void *pInput, u8 fFirst) {
    extern s32 TaLogic_Tea_IsOpenUnit();
    extern void TaLogic_GetInvadeRoot();
    s32 sourcePosition;
    s32 count;
    s32 sourceY;
    s32 sourceX;
    s32 flag;
    Point_00140830 points[12];
    s32 destination;
    s32 oldFlag;
    s32 i;
    s32 best;
    u32 targetX;
    u32 targetY;
    Point_00140830 *p;
    Input_00140830 *input = pTask;
    Output_00140830 *output = pInput;

    targetX = target_00140830(input, fFirst);
    targetY = target_00140830(input, fFirst);
    if (SzDuel_GetUnit(targetY >> 8, targetX & 0xFF) == 0) {
        TaLogic_InitRogicControl(input, 1);
        return -1;
    }
    oldFlag = TaLogic_Tea_IsOpenUnit(input->position >> 8, input->position & 0xFF, input);
    sourcePosition = SzDuel_GetUnitLoc(input->position >> 8, input->position & 0xFF);
    targetX = target_00140830(input, fFirst);
    targetY = target_00140830(input, fFirst);
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
            cost = TaLogic_GetUnitWarning(sourceX, sourceY, nSide, 3, 1, (u8)TaLogic_Tea_GetWarnHideLvl(nSide));
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
            Point_00140830 *candidate;
            s32 n;
            s32 minCost;
            s32 identity;
            s32 positionY;
            s32 positionX;

            identity = (u16)TaLogic_Tea_GetWarnHideLvl(nSide);
            positionY = position >> 8;
            positionX = position & 0xFF;
            destinationX = destination & 0xFF;

            TaLogic_GetInvadeRoot(positionY, positionX, points,
                         sourceX, sourceY, destinationX, destination >>= 8,
                         target_00140830(input, fFirst), 0, 30, identity);
            count = TaLogic_GetMinGoalCount((u8 *)points);
            best = 0xFF;
            if (count > 0) {
                flag = 0;
                minCost = 0xFFFF;
                for (n = 0; n < count; n++) {
                    if (TaLogic011_IsOpenMoveUnit(input->position >> 8, input->position & 0xFF,
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
                                                3, 1, (u8)TaLogic_Tea_GetWarnHideLvl(nSide));
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

typedef struct Coord_00140E10 {
    u8 x : 4;
    u8 y : 4;
} Coord_00140E10;

typedef struct Unit_00140E10 {
    u16 pos;
    u8 pad2[6];
    u32 target;
} Unit_00140E10;

typedef struct Result_00140E10 {
    u16 pos;
    s8 kind;
    u8 pad3;
    u16 target;
    u8 pad6[6];
    s32 action;
    s8 value;
} Result_00140E10;

#define selected_00140E10(unit, mode) \
    ((mode) == 1 ? (u32)(u16)(((Unit_00140E10 *)(unit))->target >> 16) \
                 : (u32)(u16)((Unit_00140E10 *)(unit))->target)

/* The smaller of the two values. */
static inline u32 minY_00140E10(u32 value, void *unit, s32 mode) {
    return value < (selected_00140E10(unit, mode) >> 8) ? (u8)value : (selected_00140E10(unit, mode) >> 8);
}

/* The larger of the two values. */
static inline u32 maxY_00140E10(u32 value, void *unit, s32 mode) {
    return (selected_00140E10(unit, mode) >> 8) < value ? (u8)value : (selected_00140E10(unit, mode) >> 8);
}

/* The smaller of the two values. */
static inline u32 minX_00140E10(u32 value, void *unit, s32 mode) {
    return value < (selected_00140E10(unit, mode) & 0xFF) ? (u8)value : (selected_00140E10(unit, mode) & 0xFF);
}

/* The larger of the two values. */
static inline u32 maxX_00140E10(u32 value, void *unit, s32 mode) {
    return (selected_00140E10(unit, mode) & 0xFF) < value ? (u8)value : (selected_00140E10(unit, mode) & 0xFF);
}

/* The task of a unit moving to its goal (task `pTask`), into `pInput` (`fFirst` = 1 for the unit's first-choice
   task). */
s32 TaLogic_Tea_GetMinimumTask_MoveMission(void *pTask, s32 nSide, void *pInput, u8 fFirst, u8 nKind) {
    s32 target;
    s32 leader;
    s32 count;
    Coord_00140E10 coords[12];
    extern s32 TaLogic_Tea_IsOpenUnit();
    extern s32 TaLogic_GetUnitWarning();
    extern void TaLogic_GetRoot();
    extern s32 TaLogic_IsDefStyleUnit(s32, s32, s32, u8, s32);

    {
        s32 bestCost;
        s32 bestIndex;
        s32 mode;
        Coord_00140E10 *p;
        s32 i;
        target = SzDuel_GetUnitLoc(((Unit_00140E10 *)pTask)->pos >> 8, ((Unit_00140E10 *)pTask)->pos & 0xFF);
        mode = fFirst;
        if (selected_00140E10(pTask, mode) == 0xFFFF &&
            target == selected_00140E10(pTask, mode)) {
            ((Result_00140E10 *)pInput)->pos = ((Unit_00140E10 *)pTask)->pos;
            ((Result_00140E10 *)pInput)->kind = 6;
            ((Result_00140E10 *)pInput)->target = target;
            ((Result_00140E10 *)pInput)->value = TaLogic_IsDefStyleUnit(
                ((Unit_00140E10 *)pTask)->pos >> 8, ((Unit_00140E10 *)pTask)->pos & 0xFF,
                ((Result_00140E10 *)pInput)->target, nKind, 0);
            ((Result_00140E10 *)pInput)->action = TaLogic_Tea_IsOpenUnit(
                ((Unit_00140E10 *)pTask)->pos >> 8, ((Unit_00140E10 *)pTask)->pos & 0xFF, pTask);
            TaLogic_InitRogicControl(pTask, fFirst);
            return 0;
        }

        p = coords;
        {
            s32 i = 0;
            Coord_00140E10 *q = p;
            do {
                q->x = q->y = 15;
                ++i;
                ++q;
            } while (i < 12);
        }

        leader = SzDuel_GetMapUnitID(selected_00140E10(pTask, mode) & 0xFF,
                             selected_00140E10(pTask, mode) >> 8);
        if (leader < 0) {
            leader = 0xFFFF;
        }
        TaLogic_GetRoot(((Unit_00140E10 *)pTask)->pos >> 8, ((Unit_00140E10 *)pTask)->pos & 0xFF,
                     coords, target & 0xFF, target >> 8,
                     selected_00140E10(pTask, mode) & 0xFF,
                     selected_00140E10(pTask, mode) >> 8, (u16)leader, 7);
        count = TaLogic_GetMinGoalCount((u8 *)coords);
        if (count > 0) {
            s32 cost;
            bestIndex = 0xFF;
            bestCost = 0xFFFF;
            for (i = 0; i < count; ++i, ++p) {
                if (SzDuel_GetMapUnit(p->x, p->y) == 0) {
                    cost = TaLogic_GetUnitWarning(p->x, p->y, nSide, 3, 1,
                                        (u8)TaLogic_Tea_GetWarnHideLvl(nSide));
                    if (cost < bestCost) {
                        bestCost = cost;
                        bestIndex = i;
                    } else if (cost == bestCost) {
                        if ((maxX_00140E10(p->x, pTask, mode) -
                             minX_00140E10(p->x, pTask, mode)) +
                            (maxY_00140E10((u8)p->y, pTask, mode) -
                             minY_00140E10((u8)p->y, pTask, mode)) <
                            (maxX_00140E10(coords[bestIndex].x, pTask, mode) -
                             minX_00140E10(coords[bestIndex].x, pTask, mode)) +
                            (maxY_00140E10((u8)coords[bestIndex].y, pTask, mode) -
                             minY_00140E10((u8)coords[bestIndex].y, pTask, mode))) {
                            bestCost = cost;
                            bestIndex = i;
                        }
                    }
                }
            }
        } else {
            ((Result_00140E10 *)pInput)->pos = ((Unit_00140E10 *)pTask)->pos;
            ((Result_00140E10 *)pInput)->kind = 6;
            ((Result_00140E10 *)pInput)->target = target;
            ((Result_00140E10 *)pInput)->value = TaLogic_IsDefStyleUnit(
                ((Unit_00140E10 *)pTask)->pos >> 8, ((Unit_00140E10 *)pTask)->pos & 0xFF,
                ((Result_00140E10 *)pInput)->target, nKind, 0);
            ((Result_00140E10 *)pInput)->action = TaLogic_Tea_IsOpenUnit(
                ((Unit_00140E10 *)pTask)->pos >> 8, ((Unit_00140E10 *)pTask)->pos & 0xFF, pTask);
            TaLogic_InitRogicControl(pTask, fFirst);
            return 0;
        }
            if (bestIndex != 0xFF) {
                ((Result_00140E10 *)pInput)->pos = ((Unit_00140E10 *)pTask)->pos;
                ((Result_00140E10 *)pInput)->kind = 6;
                ((Result_00140E10 *)pInput)->target =
                    (coords[bestIndex].y << 8) | coords[bestIndex].x;
                ((Result_00140E10 *)pInput)->value = TaLogic_IsDefStyleUnit(
                    ((Unit_00140E10 *)pTask)->pos >> 8, ((Unit_00140E10 *)pTask)->pos & 0xFF,
                    ((Result_00140E10 *)pInput)->target, nKind, 0);
                ((Result_00140E10 *)pInput)->action = TaLogic_Tea_IsOpenUnit(
                    ((Unit_00140E10 *)pTask)->pos >> 8, ((Unit_00140E10 *)pTask)->pos & 0xFF, pTask);
            } else {
                ((Result_00140E10 *)pInput)->pos = ((Unit_00140E10 *)pTask)->pos;
                ((Result_00140E10 *)pInput)->kind = 6;
                ((Result_00140E10 *)pInput)->target = target;
                ((Result_00140E10 *)pInput)->value = TaLogic_IsDefStyleUnit(
                    ((Unit_00140E10 *)pTask)->pos >> 8, ((Unit_00140E10 *)pTask)->pos & 0xFF,
                    ((Result_00140E10 *)pInput)->target, nKind, 0);
                ((Result_00140E10 *)pInput)->action = TaLogic_Tea_IsOpenUnit(
                    ((Unit_00140E10 *)pTask)->pos >> 8, ((Unit_00140E10 *)pTask)->pos & 0xFF, pTask);
            }
            TaLogic_InitRogicControl(pTask, fFirst);
        return 0;
    }
}

typedef struct {
    u16 position;
    u8 pad2[6];
    union {
        u32 both;
        u16 half[2];
    } target;
} Source_001415F0;

typedef struct {
    u16 position;
    u8 action;
    u8 pad3;
    u16 target;
    u8 pad6[10];
    s8 result;
} Action_001415F0;

typedef struct {
    u8 x : 4;
    u8 y : 4;
} Point_001415F0;

#define MIN_001415F0(a, b) ((a) < (b) ? (a) : (b))
#define MAX_001415F0(a, b) ((b) < (a) ? (a) : (b))

/* The task's target square: the second half-word when the second argument is 1, else the first. */
static inline u32 target_001415F0(void *arg0, s32 mode) {
    Source_001415F0 *source = arg0;
    if (mode == 1) {
        return (u16)(source->target.both >> 16);
    }
    return source->target.half[0];
}

/* Sets a move task (action 6) to the given square, and whether the unit should stay in defence there. */
static inline void fill_001415F0(void *arg0, void *arg2, s32 target, s32 flag) {
    Source_001415F0 *source = arg0;
    Action_001415F0 *action = arg2;
    action->position = source->position;
    action->action = 6;
    action->target = target;
    action->result = TaLogic_IsDefStyleUnit(source->position >> 8,
        source->position & 0xFF, action->target, flag, 0);
}

/* The task of setting a trap (task `pTask`), into `pInput`. */
s32 TaLogic_Tea_GetMinimumTask_TrapMission(void *pTask, s32 nSide, void *pInput, s32 fFirst) {
    s32 start;
    s32 count;
    s32 startY;
    Point_001415F0 points[16];
    s32 bestScore;
    Point_001415F0 *p;
    s32 targetY;
    s32 targetX;
    s32 i;
    s32 bestIndex;
    s32 mode;
    s32 target;
    s32 startX;
    u32 xPosition;
    u32 yPosition;
    Source_001415F0 *source = pTask;
    Action_001415F0 *action = pInput;
    extern void TaLogic_GetInvadeRoot();

    mode = fFirst & 0xFF;
    xPosition = target_001415F0(pTask, mode);
    yPosition = target_001415F0(pTask, mode);
    if (SzDuel_GetUnit(yPosition >> 8, xPosition & 0xFF) == 0) {
        TaLogic_InitRogicControl(pTask, 1);
        return -1;
    }
    start = SzDuel_GetUnitLoc(source->position >> 8, source->position & 0xFF);
    xPosition = target_001415F0(pTask, mode);
    yPosition = target_001415F0(pTask, mode);
    target = SzDuel_GetUnitLoc(yPosition >> 8, xPosition & 0xFF);
    if (target_001415F0(pTask, mode) == 0xFFFF) {
        fill_001415F0(pTask, pInput, start, 1);
        return 0;
    } else {
        s32 unit = SzDuel_GetUnit(source->position >> 8, source->position & 0xFF);
        startX = start & 0xFF;
        startY = start >> 8;
        if (GetMoveRange(unit, startX, startY) == 0 ||
                TaLogic_IsAttackedNow(source->position >> 8, source->position & 0xFF, 0) == 1) {
            fill_001415F0(pTask, pInput, start, 1);
            return 0;
        } else {
            p = points;
            {
                s32 n = 0;
                Point_001415F0 *q = p;
                do {
                    q->x = q->y = 0xF;
                    q++;
                    n++;
                } while (n < 12);
            }
            {
                s32 position = source->position;
                u16 card = (u16)TaLogic_Tea_GetWarnHideLvl(nSide);
                TaLogic_GetInvadeRoot(position >> 8, position & 0xFF, points,
                    startX, startY, targetX = target & 0xFF,
                    targetY = target >> 8, target_001415F0(pTask, mode),
                    0, 30, card);
            }
            count = TaLogic_GetMinGoalCount((u8 *)points);
            bestIndex = 0xFF;
            if (count > 0) {
                bestScore = 0;
                for (i = 0; i < count; i++, p++) {
                    if (SzDuel_GetMapUnit(p->x, p->y) == 0) {
                        s32 score = TaLogic_GetUnitWarning(p->x, p->y, nSide, 3, 1,
                            TaLogic_Tea_GetWarnHideLvl(nSide) & 0xFF);
                        if (bestScore < score) {
                            bestScore = score;
                            bestIndex = i;
                        } else if (score == bestScore) {
                            if (MAX_001415F0(p->x, targetX) - MIN_001415F0(p->x, targetX)
                                    + (MAX_001415F0(p->y, targetY) - MIN_001415F0(p->y, targetY))
                                    < MAX_001415F0(points[bestIndex].x, targetX) - MIN_001415F0(points[bestIndex].x, targetX)
                                    + (MAX_001415F0(points[bestIndex].y, targetY) - MIN_001415F0(points[bestIndex].y, targetY))) {
                                bestScore = score;
                                bestIndex = i;
                            }
                        }
                    }
                }
            } else {
                fill_001415F0(pTask, pInput, start, 1);
                return 0;
            }
            if (bestIndex != 0xFF) {
                action->position = source->position;
                action->action = 6;
                action->target = (points[bestIndex].y << 8) | points[bestIndex].x;
                action->result = TaLogic_IsDefStyleUnit(source->position >> 8,
                    source->position & 0xFF, action->target, 0, 0);
            } else {
                fill_001415F0(pTask, pInput, start, 1);
                return 0;
            }
        }
    }
    return 0;
}

/* How careful this duelist is about hidden cards (by its life points and monster count). */
s32 TaLogic_Tea_GetWarnHideLvl(s32 nSide) {
    if (SzDuel_GetLP(nSide) > 2000) {
        if (SzDuel_GetUnitMonsterCount(nSide) >= 4) {
            return 0;
        }
        return 0;
    }
    return 0;
}

/* Whether this duelist opens (turns face up) unit (nSide, nID) now: 0 no, 1 or 2 by its kind. */
s32 TaLogic_Tea_IsOpenUnit(s32 nSide, s32 nID) {
    s32 id;
    s32 val;
    u32 *p;

    id = SzDuel_GetUnitCardNo();
    val = Ta_IsUnitControl(nSide, nID);
    if (SzDuel_GetUnitStatus(nSide, nID, 4) != 0) {
        return 0;
    }
    switch (SzDuel_GetUnitKind(nSide, nID) >> 5) {
    case 0:
        switch (id) {
        case 0x184:
            if (SzDuel_GetLP(nSide) < SzDuel_GetLP(nSide == 0 ? 1 : 0)) {
                return 1;
            }
            break;
        case 0x170:
            if (TaLogic011_IsUseReversalGoddess(val) == 1) {
                return 1;
            }
            break;
        case 0x17F:
            if (Ta_GetUnitNumFrom22bitFlagList(SearchUnitByRange(0, 0, nSide, 1, 0x14, 0xE)) >= 3) {
                return 1;
            }
            break;
        case 0x182:
            if (TaLogic011_IsUseBindChain(val) == 1) {
                return 1;
            }
            break;
        }
        return 2;
    case 1:
        if (TaLogic_GetActionReaction(nSide, nID, 0, 0, 6, 0) == 5) {
            return 2;
        }
        p = Ta_GetUnitEffect(nSide, nID, 0);
        if (p == NULL) {
            return 2;
        }
        switch (*p >> 8) {
        case 0xD:
            if (SzDuel_GetLP(val) < 2000) {
                return 1;
            }
            break;
        case 0x12:
            if (Ta_GetUnitNumFrom22bitFlagList(SearchUnitByRange(0, 0, nSide, 1, 8, 0xE)) >= 4) {
                return 1;
            }
            break;
        case 0x25:
            if (TaLogic_IsAttackedNow(val, 0, 0) == 1) {
                return 1;
            }
            break;
        }
        return 2;
    }
    return 2;
}

/* Whether unit (nSide, nID) may open while moving from (nX, nZ) to the square next to it, (gX, gZ). */
s32 TaLogic011_IsOpenMoveUnit(s32 nSide, s32 nID, s32 nX, s32 nZ,
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

/* Whether side `nSide` should use the binding chain now (a dangerous enemy in reach, none of its own). */
s32 TaLogic011_IsUseBindChain(s32 nSide) {
    s32 index;
    u8 count;
    s32 list;
    s32 low;
    s32 high;
    s32 entry;

    count = 0;
    list = SearchUnitByRange(0, 0, nSide, 3, 3, 14);
    for (index = 0; index < Ta_GetUnitNumFrom22bitFlagList(list); index++) {
        entry = Ta_GetUnitOwnerIDFromLstCount(list, index);
        high = entry >> 8;
        low = entry & 0xFF;
        if (nSide == Ta_IsUnitControl(high, low)) {
            return 0;
        }
        if (TaLogic_CanSeeUnit(high, low, 0) == 1) {
            count++;
        }
    }
    if (count > 0) {
        return 1;
    }
    return 0;
}
#pragma opt_lifetimes off

/* Whether side `nSide` should use the life hourglass now (enough life points, strong graveyard monsters, free
   squares). */
s32 TaLogic011_IsUseLifeHourGlass(s32 nSide) {
    extern s32 SzDuel_GetGraveCount(s32);
    u8 slots;
    u32 side;
    s32 i;
    u8 count;

    side = nSide;
    count = 0;
    slots = 0;
    if (SzDuel_GetLP(side) < 0x4B0) {
        return 0;
    }
    for (i = 0; i < SzDuel_GetGraveCount(side); i++) {
        if ((s32)(TaHand_GetCardAPDP(SzDuel_InqGrave(side, i)) >> 16) > 2000) {
            if ((TaHand_GetCardKind(SzDuel_InqGrave(side, i)) >> 5) == 0) {
                count++;
            }
        }
    }
    for (i = 0; i < SzDuel_GetGraveCount(side == 0 ? 1 : 0); i++) {
        if ((s32)(TaHand_GetCardAPDP(SzDuel_InqGrave(side == 0 ? 1 : 0, i)) >> 16) > 2000) {
            if ((TaHand_GetCardKind(SzDuel_InqGrave(side == 0 ? 1 : 0, i)) >> 5) == 0) {
                count++;
            }
        }
    }
    if (count >= 3) {
        for (i = 0; i < 8; i++) {
            if (Ta_GetSummonablePieceWithOrder(side, i, 1) >= 0) {
                slots++;
            }
        }
        if (slots >= 3 && 5 - SzDuel_GetUnitMonsterCount(side) >= 3) {
            return 1;
        }
    }
    return 0;
}
#pragma opt_lifetimes reset

/* Whether side `nSide` should use the brave hourglass now (enough life points, 4+ monsters). */
s32 TaLogic011_IsUseBraveHourGlass(s32 nSide) {
    if (SzDuel_GetLP(nSide) < 0x4B0) {
        /* Duplicate return node #6. Try simplifying control flow for better match */
        return 0;
    }
    if (SzDuel_GetUnitMonsterCount(nSide) >= 4) {
        return 1;
    }
    return 0;
}

/* Whether side `nSide` has three or more targets in range for the reversal card. */
s32 TaLogic011_IsUseReversalGoddess(s32 nSide) {
    if (Ta_GetUnitNumFrom22bitFlagList(SearchUnitByRange(0, 0, nSide, 1, 0x3E80025, 0xE)) >= 3) {
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
} Req_001422E0;

typedef struct {
    u8 pad0[0x160];
    u16 list[32];    /* 0x160 */
    u8 idx : 5;      /* 0x1A0 */
    u8 pad1A0 : 3;
    u8 pad1A1;
    u16 count;       /* 0x1A2 */
} Work_001422E0;

/* Computer duelist 11's controller (duelistControllers[11]): the buttons it presses this frame. With an empty
   input queue it plans its next task and turns it into buttons, then plays the queue back one button per frame;
   after 600 frames it gives up the turn (0x20, then 0x800). */
s32 duelistController11(s32 wCursorPos, void *pCtl) {
    Req_001422E0 req;
    Work_001422E0 *w;
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
        if (TaLogic_Tea_GetMinimumTask(w, &req, wCursorPos) == 0) {
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

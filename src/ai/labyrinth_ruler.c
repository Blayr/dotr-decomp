/* Computer AI of the Labyrinth-ruler (duelist 8, duelistController08). */

#include "common.h"

s32 TaLogic_GetInputQueFromMinimumTask_b(void *, void *, s32);
#pragma conditional_move off

/* This duelist's move: picks the next unit to act, gives it a task and turns that into input `pInput`; returns 1
   when it set one. */
s32 TaLogic_LabyrinthRuler_GetMinimumTask(void *pCtl, void *pInput, s32 wCursorPos) {
    UnitTask *tasks = pCtl;
    s32 side;
    s32 found;
    s32 result;
    s32 index;

    side = SzDuel_GetTurnOwner();
    found = 0;
    if ((result = TaLogic_LabyrinthRuler_GetNextActiveUnit(tasks, side, (s32)pInput)) < 0) {
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
    TaLogic_LabyrinthRuler_CommandUnit(&tasks[index]);
    switch ((tasks[index].mission >> 8) & 0xFF) {
    case TASK_RUN:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            TaLogic_LabyrinthRuler_GetMinimumTask_RunMission(&tasks[index], side, pInput, 1);
            found = 1;
        }
        break;
    case TASK_ATTACK:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            if (TaLogic_LabyrinthRuler_GetMinimumTask_AtkMission(&tasks[index], side, pInput, 1) < 0) {
                TaLogic_InitRogicControl(&tasks[index], 1);
                return 1;
            }
            found = 1;
        }
        break;
    case TASK_SUMMON:
        if (TaLogic_LabyrinthRuler_GetMinimumTask_Summon(tasks[index].ownerId, side, (s32)pInput) < 0) {
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
            TaLogic_LabyrinthRuler_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 1, 0);
            found = 1;
        }
        break;
    case TASK_CONFIRMUNIT:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            TaLogic_LabyrinthRuler_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 1, 1);
            found = 1;
        }
        break;
    case TASK_ENCHANT:
        TaLogic_GetMinimumTask_EncMission(&tasks[index], side, pInput, 1, 0, TaLogic_LabyrinthRuler_GetWarnHideLvl(side), 4, 1);
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
            TaLogic_LabyrinthRuler_GetMinimumTask_RunMission(&tasks[index], side, pInput, 0);
            found = 1;
        }
        break;
    case 2:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            if (TaLogic_LabyrinthRuler_GetMinimumTask_AtkMission(&tasks[index], side, pInput, 0) < 0) {
                TaLogic_LabyrinthRuler_GetMinimumTask_RunMission(&tasks[index], side, pInput, 0);
            }
            found = 1;
        }
        break;
    case 10:
        if (TaLogic_LabyrinthRuler_GetMinimumTask_Summon(tasks[index].ownerId, side, (s32)pInput) < 0) {
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
            TaLogic_LabyrinthRuler_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 0, 0);
            found = 1;
        }
        break;
    case 3:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            TaLogic_LabyrinthRuler_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 0, 1);
            found = 1;
        }
        break;
    case 9:
        TaLogic_GetMinimumTask_EncMission(&tasks[index], side, pInput, 0, 0, TaLogic_LabyrinthRuler_GetWarnHideLvl(side), 4, 1);
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
    u16 card;
    u8 pad2[2];
    u16 result;
    u8 pad6[2];
    s32 flags;
} Data_00131540;
#pragma conditional_move reset

/* Gives a unit of this duelist its order for this turn (attack, run, move, summon, guard). */
s32 TaLogic_LabyrinthRuler_CommandUnit(void *pCtl) {
    Data_00131540 *data = (Data_00131540 *)pCtl;
    s32 temp = Ta_IsUnitControl((s32)data->card >> 8, data->card & 0xFF);
    u16 value = data->card;

    if (SzDuel_GetUnit((s32)value >> 8, value & 0xFF) != 0) {
        value = data->card;
        if (SzDuel_GetUnitStatus((s32)value >> 8, value & 0xFF, 0) == 0) {
            value = data->card;
            if (value != 0xFFFF) {
                if ((value & 0xFF) == 0) {
                    if (data->flags == -1) {
                        if (TaLogic_IsAttackedNow((s32)value >> 8, value & 0xFF, 0) == 1) {
                            if (SzDuel_InqHandPhase((s32)data->card >> 8) == 1) {
                                data->result = 0x50A;
                            } else {
                                data->result = 0x5FF;
                            }
                        } else if (SzDuel_InqHandPhase((s32)data->card >> 8) == 1) {
                            data->result = 0xA06;
                            data->flags = (data->flags & 0xFFFF0000) |
                                (SzDuel_GetUnitLoc(temp == 0 ? 1 : 0, 0) & 0xFF);
                        } else {
                            data->result = 0x6FF;
                            data->flags = *(u16 *)&data->flags |
                                ((SzDuel_GetUnitLoc(temp == 0 ? 1 : 0, 0) & 0xFF) << 16);
                        }
                    }
                } else {
                    s32 type = SzDuel_GetUnitKind((s32)value >> 8, value & 0xFF) >> 5;

                    switch (type) {
                    case 0:
                        TaLogic008_CommandBtlUnit(pCtl, 1);
                        break;
                    case 2:
                        TaLogic_CommandEncUnit(pCtl, 4, 0, TaLogic_LabyrinthRuler_GetWarnHideLvl(temp) & 0xFF);
                        break;
                    case 1:
                    case 3:
                        TaLogic008_CommandSpellUnit(pCtl);
                        break;
                    default:
                        data->result = 0x5FF;
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
s32 TaLogic_LabyrinthRuler_GetNextActiveUnit(u16 *pCtl, s32 nSide, s32 pInput) {
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
    TaLogic_LabyrinthRuler_CommandUnit(pCtl + idx * 8);
    if (((pCtl[idx * 8 + 2] >> 8) & 0xFF) == 10) {
        if (SzDuel_InqHandPhase(nSide) == 1 && TaLogic_LabyrinthRuler_GetMinimumTask_Summon(pos, nSide, pInput) >= 0) {
            return pos | 0x10000;
        }
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_GetUnitStatus(nSide, 0, 0) == 0) {
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_InqHandPhase(nSide) == 1 && TaLogic_LabyrinthRuler_GetMinimumTask_Summon(pos, nSide, pInput) >= 0) {
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
} Entry_00131B30;

typedef struct {
    u16 card;
    u8 flag;
    u8 pad;
} Slot_00131B30;

/* Orders a fighting unit (task `pTask`): straight at the enemy leader when `fGoalFirst` and the path is open,
   else at the nearest enemy it can beat. */
void TaLogic008_CommandBtlUnit(void *pTask, s32 fGoalFirst) {
    extern void TaLogic_InitIgnoreLst();
    extern s32 TaLogic_IsRootOpen();
    extern s32 TaLogic008_GetNearUnit();
    extern s32 SzDuel_GetUnitCardNo();
    Entry_00131B30 *entry = pTask;
    s32 side;
    s32 player;
    s32 other;
    s32 pos;
    s32 otherPos;
    s32 i;
    u8 work[0x70];
    Slot_00131B30 list[22];
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
        if (SzDuel_GetUnitCardNo(entry->unitId >> 8, entry->unitId & 0xFF) == 0x198 &&
            SzDuel_GetLP(side) <= 1000) {
            entry->state = 0x3FF;
            entry->data.word = (pos << 16) | entry->data.halves.low;
        }
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
            switch (TaLogic008_GetNearUnit(entry, 0, player, pos & 0xFF, pos >> 8,
                                  Ta_GetCurrentSide(entry->unitId >> 8, entry->unitId & 0xFF) == 0 ? 1 : 0,
                                  i & 0xFF, TaLogic_LabyrinthRuler_GetWarnHideLvl(side), list, 0, &countA, &countB, 4, work)) {
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
        TaLogic008_CommandInvadeUnit(entry);
    }
}

/* TaLogic_GetNearUnit with this duelist's view and strength settings. */
void TaLogic008_GetNearUnit(s32 pTask, s32 pTree, s32 pVarInfo, s32 nX, s32 nZ, s32 eSide, s32 bDist, s32 WarnLvl, s32 nUnitLst, u16 wUnitNum, s32 wSize, s32 wNodeCount, u8 bChase, s32 wIgnoreLst) {
    TaLogic_GetNearUnit(pTask, pTree, pVarInfo, nX, nZ, eSide, bDist, WarnLvl,
                  nUnitLst, wUnitNum, wSize, wNodeCount, bChase,
                  0, 0x708, wIgnoreLst);
}

typedef struct {
    u8 low : 4;
    u8 high : 4;
} Nibbles_00131E40;

typedef struct {
    u16 position;
    u16 pad2;
    u16 state;
    u16 pad6;
    union {
        u32 value;
        u16 low;
    } data;
} State_00131E40;

/* Orders a unit (task `pTask`) to push into the opponent's side of the board. */
void TaLogic008_CommandInvadeUnit(void *pTask) {
    s32 occupied;
    s32 destination;
    State_00131E40 *state = pTask;
    Nibbles_00131E40 entries[12];
    s32 i;
    Nibbles_00131E40 *entry;
    u32 *kind;
    s32 result;
    u16 position;

    position = state->position;
    occupied = Ta_IsUnitControl(position >> 8, position & 0xFF);
    position = state->position;
    destination = SzDuel_GetUnitLoc(position >> 8, position & 0xFF);
    position = state->position;
    kind = SzDuel_GetUnitEffect(position >> 8, position & 0xFF, 1);
    entry = entries;
    i = 0;
    do {
        entry->low = entry->high = 15;
        entry++;
        i++;
    } while (i < 12);
    if (kind != NULL && (*kind >> 8) == 8) {
        state->state = 0x2FF;
        state->data.value = state->data.low | ((occupied != 0 ? 0 : 1) << 24);
    } else {
        state->state = 0x6FF;
        position = state->position;
        result = TaLogic008_GetNextInvadePoint(SzDuel_GetUnit(position >> 8, position & 0xFF),
                              destination & 0xFF, destination >> 8);
        if (result >= 0) {
            state->data.value = (result << 16) | state->data.low;
        } else {
            state->state = 0x5FF;
        }
    }
}

typedef struct {
    u8 low : 4;
    u8 high : 4;
} Nibbles_00131F80;

/* The next square a unit (record `pVarInfo`) on (nX, nZ) invades toward. */
s32 TaLogic008_GetNextInvadePoint(s32 pVarInfo, s32 nX, s32 nZ) {
    Nibbles_00131F80 buffer[12];
    s32 result;
    s32 owner;
    s32 i;
    Nibbles_00131F80 *p;
    extern s32 TaLogic_GetInvadeRoot2();
    extern s32 TaUtil_GetUnitAP2();

    result = -1;
    owner = Ta_IsUnitControl2((void *)pVarInfo);
    p = buffer;
    i = 0;
    do {
        i++;
        p->low = p->high = 15;
        p++;
    } while (i < 12);

    if (pVarInfo == 0) {
        return -1;
    }
    if (nX >= 3 && (nZ == 0 || nZ == 1 || (u32)(nZ - 4) < 2)) {
        result = ((nZ % 2 == 0 ? nZ + 2 : nZ + 1) << 8) | 6;
    } else if (nX < 3 && (u32)(nZ - 2) < 2) {
        result = 0x400;
    }
    if (result >= 0) {
        if (TaLogic_GetInvadeRoot2(pVarInfo, buffer, nX, nZ, result & 0xFF,
                         result >> 8, -1, 0, 7, (u16)TaLogic_LabyrinthRuler_GetWarnHideLvl(owner)) >= 0) {
            return result;
        }
    }

    if (nX < 3 && (nZ == 0 || nZ == 1 || (u32)(nZ - 4) < 2) &&
        TaUtil_GetUnitAP2(pVarInfo, 0, nZ % 2 ? nZ + 1 : nZ) < 1500) {
        result = (nZ % 2 == 0 ? nZ + 2 : nZ + 1) << 8;
    } else if (nX >= 3 && nZ == 2 && TaUtil_GetUnitAP2(pVarInfo, 6, 3) < 1500) {
        result = 0x406;
    }
    if (result >= 0) {
        if (TaLogic_GetInvadeRoot2(pVarInfo, buffer, nX, nZ, result & 0xFF,
                         result >> 8, -1, 0, 7, (u16)TaLogic_LabyrinthRuler_GetWarnHideLvl(owner)) >= 0) {
            return result;
        }
    }

    result = SzDuel_GetUnitLoc(Ta_IsUnitControl2((void *)pVarInfo) == 0 ? 1 : 0, 0);
    if (result >= 0) {
        if (TaLogic_GetInvadeRoot2(pVarInfo, buffer, nX, nZ, result & 0xFF,
                         result >> 8, -1, 0, 7, (u16)TaLogic_LabyrinthRuler_GetWarnHideLvl(owner)) >= 0) {
            return result;
        }
    }
    return ((result >> 8) << 8) | nX;
}

/* Orders a face-down magic card (task `pTask`): whether and where to open it. */
void TaLogic008_CommandSpellUnit(u16 *pTask) {
    u16 value;
    s32 controllingSide;
    s32 temp_s3;
    s32 loc;
    void *unitEffect;
    s32 result;

    value = pTask[0];
    controllingSide = Ta_IsUnitControl(value >> 8, value & 0xFF);
    value = pTask[0];
    temp_s3 = (SzDuel_GetUnitKind(value >> 8, value & 0xFF) >> 5) & 0xFF;
    value = pTask[0];
    loc = SzDuel_GetUnitLoc(value >> 8, value & 0xFF);
    value = pTask[0];
    unitEffect = SzDuel_GetUnitEffect(value >> 8, value & 0xFF, 0);

    switch (temp_s3 & 0xFF) {
    case 3:
        pTask[2] = 0x3FF;
        value = pTask[0];
        result = TaLogic008_GetNextInvadePoint(SzDuel_GetUnit(value >> 8, value & 0xFF), loc & 0xFF, loc >> 8);
        if (result >= 0) {
            *(u32 *)((u8 *)pTask + 8) = (result << 16) | *(u16 *)((u8 *)pTask + 8);
            return;
        }
        pTask[2] = 0x5FF;
        return;
    case 1:
        if (unitEffect == NULL) {
            return;
        }
        switch (*(u32 *)unitEffect >> 8) {
        case 2:
        case 0x48:
            pTask[2] = 0x6FF;
            result = TaLogic008_GetWallEmpty(controllingSide);
            if (result >= 0) {
            *(u32 *)(pTask + 4) = (result << 16) | pTask[4];
                return;
            }
            *(u32 *)(pTask + 4) = pTask[4] | 0x60000;
            return;
        case 0x25:
            pTask[2] = 0x3FF;
            value = pTask[0];
            result = TaLogic008_GetNextInvadePoint(SzDuel_GetUnit(value >> 8, value & 0xFF), loc & 0xFF, loc >> 8);
            if (result >= 0) {
                *(u32 *)(pTask + 4) = (result << 16) | pTask[4];
                return;
            }
            pTask[2] = 0x5FF;
            return;
        }
        break;
    }
    pTask[2] = 0x5FF;
}

typedef struct {
    s16 id;
    u8 unk2;
    u8 pad3;
    s16 unk4;
    u8 pad6[6];
    s32 unkC;
} Ctx_00132460;

typedef struct {
    u8 pad0[0x3C];
    u16 unk3C;
    u8 pad3E[0x22];
} Work_00132460;

s32 TaLogic_GetNearCard2(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8,
                  s32 arg9);

/* The summon task for side `nSide`: which hand cards to play and where, into `pInput`; -1 when it plays none. */
s32 TaLogic_LabyrinthRuler_GetMinimumTask_Summon(s32 wUnit, s32 nSide, s32 pInput) {
    extern s32 TaLogic_GetUnitNum(s32, s32);
    Work_00132460 work;
    s32 ret;
    s32 res;
    s32 pos;
    s32 kind;
    Ctx_00132460 *ctx = (Ctx_00132460 *)pInput;

    ctx->id = wUnit;
    if (SzDuel_InqHandPhase(nSide) == 0) {
        return -1;
    }
    if (TaLogic_GetUnitNum(nSide, 0) == 5 && TaLogic_GetUnitNum(nSide, 1) == 5) {
        return -1;
    }
    kind = TaLogic008_IsHandPlay(nSide, &work);
    if (kind < 0) {
        return -1;
    }
    ctx->unk2 = 10;
    ctx->unkC = 0;
    pos = SzDuel_GetUnitLoc(wUnit >> 8, wUnit & 0xFF);
    if (kind == 0) {
        if (TaLogic008_SetComboQue(nSide, (u8 *)ctx, &work) >= 0) {
            ret = TaLogic_GetNearCard2(&work, pos & 0xFF, pos >> 8, nSide == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, TaLogic_LabyrinthRuler_GetWarnHideLvl(nSide));
            if (ret < 0) {
                if (SzDuel_GetUnitMonsterCount(nSide) < 5) {
                    res = TaLogic008_GetSummonPiece(nSide, kind, &work, ret);
                    if (res < 0) {
                        return -1;
                    }
                    ctx->unk4 = res;
                    return 1;
                }
            } else {
                res = TaLogic008_GetSummonPiece(nSide, kind, &work, ret);
                if (res < 0) {
                    return -1;
                }
                ctx->unk4 = res;
                return 1;
            }
        }
    } else {
        ret = TaLogic_GetNearCard2(&work, pos & 0xFF, pos >> 8, nSide == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, TaLogic_LabyrinthRuler_GetWarnHideLvl(nSide));
    }
    if (kind == 2) {
        TaLogic008_SetSpecialComboQue(nSide, ctx, &work);
        res = TaLogic008_GetSummonPiece(nSide, kind, &work, ret);
        if (res < 0) {
            return -1;
        }
        ctx->unk4 = res;
        return 1;
    }
    if (TaLogic008_GetSpellPlay(nSide, (u8 *)ctx, &work, work.unk3C) < 0) {
        return -1;
    }
    res = TaLogic008_GetSummonPiece(nSide, kind, &work, ret);
    if (res < 0) {
        return -1;
    }
    ctx->unk4 = res;
    return 1;
}

/* Whether side `nSide` should play from its hand this turn (and what, into `pInput`). */
s32 TaLogic008_IsHandPlay(s32 nSide, void *pInput) {
    s32 cards[8];
    u8 work[32];
    u8 first;
    u8 second;
    s32 i;
    s32 slot;
    s32 *q;
    s32 j;
    s32 ret;
    extern s32 TaLogic_GetUnitNum();
    extern s32 SzDuel_GetUnitCardNo();

    first = TaLogic_GetUnitNum(nSide, 0);
    second = TaLogic_GetUnitNum(nSide, 1);
    if (pInput == NULL) {
        return -1;
    }
    TaHand_GetNextHand(nSide, cards);
    if (first == 5) {
        if (TaLogic008_GetSpellPlay(nSide, work, pInput, 999) >= 0) {
            return 1;
        }
        return -1;
    }
    if (second == 5) {
        for (i = 0; i < TaHand_GetNextHandNum(nSide); i++) {
            if ((TaHand_GetCardKind(cards[i]) >> 5) == 0 && TaHand_CanAffordSummonCost(nSide, cards[i]) == 1) {
                SzDuel_InitCardInfo(pInput, cards[i]);
                return 0;
            }
        }
        return -1;
    }
    if (TaLogic008_GetSpecCardPlay(nSide, work, pInput, 0x340) >= 0) {
        if (TaLogic008_IsDoCerem(nSide, 0x340) == 1) {
            return 2;
        }
    }
    slot = 1;
    while (1) {
        if (SzDuel_GetUnit(nSide, slot) != 0 &&
            SzDuel_GetUnitCardNo(nSide, slot) == 0x91 &&
            nSide == Ta_IsUnitControl(nSide, slot) &&
            TaLogic008_GetSpecCardPlay(nSide, work, pInput, 0x2EA) >= 0) {
            return 2;
        }
        if (SzDuel_GetUnit(nSide == 0 ? 1 : 0, slot) != 0 &&
            SzDuel_GetUnitCardNo(nSide == 0 ? 1 : 0, slot) == 0x91 &&
            nSide == Ta_IsUnitControl(nSide == 0 ? 1 : 0, slot) &&
            TaLogic008_GetSpecCardPlay(nSide == 0 ? 1 : 0, work, pInput, 0x2EA) >= 0) {
            return 2;
        }
        slot++;
        if (slot > 5) {
            break;
        }
    }
    j = 0;
    if (j < TaHand_GetNextHandNum(nSide)) {
        q = cards;
        do {
            if ((TaHand_GetCardKind(*q) >> 5) == 0 && TaHand_CanAffordSummonCost(nSide, *q) == 1) {
                SzDuel_InitCardInfo(pInput, cards[j]);
                return 0;
            }
            q++;
            j++;
        } while (j < TaHand_GetNextHandNum(nSide));
    }
    ret = TaLogic008_GetSpellPlay(nSide, work, pInput, 999);
    if (ret >= 0) {
        return ret;
    }
    return -1;
}

/* Whether side `nSide` holds card `nCardNo` and can summon it (its slot into `bCombo`, the card into `pCardInfo`);
   returns its kind group or -1. */
s32 TaLogic008_GetSpecCardPlay(s32 nSide, void *bCombo, void *pCardInfo, s32 nCardNo) {
    s32 values[8];
    s32 index;
    s32 *value;

    TaHand_GetNextHand(nSide, values);
    index = 0;
    if (index < TaHand_GetNextHandNum(nSide)) {
        value = values;
        do {
            if (((nCardNo & 0xFFFF) == *value) && (TaHand_CanAffordSummonCost(nSide, *value) == 1)) {
                *((s8 *)bCombo + 6) = index;
                SzDuel_InitCardInfo(pCardInfo, values[index]);
                return TaHand_GetCardKind(values[index]) >> 5;
            }
            value++;
            index++;
        } while (index < TaHand_GetNextHandNum(nSide));
    }
    return -1;
}

/* Whether side `nSide` plays a magic or ritual card from its hand now (its slot into `bCombo`, the card into
   `pCardInfo`). */
s32 TaLogic008_GetSpellPlay(s32 nSide, u8 *bCombo, void *pCardInfo, s32 nMode) {
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

typedef struct Info_00132D00 {
    u8 pad00[8];
    u16 x;
    s16 y;
} Info_00132D00;

typedef struct Sprite_00132D00 {
    Info_00132D00 *info;
    u8 pad04[0x34];
    s16 x;
    s16 y;
} Sprite_00132D00;

/* Fills hand combination `bCombo` for side `nSide`: the best fusion or equip chain, its card into `pCardInfo`. */
s32 TaLogic008_SetComboQue(s32 nSide, u8 *bCombo, void *pCardInfo) {
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
                            TaLogic_LabyrinthRuler_ConvEmptyCombo(nSide, *node, entries);
                            TaLogic_CopyArray((u8 *)*node + 2, bCombo + 6);
                            SzDuel_InitCardInfo(pCardInfo, **node);
                            ((Sprite_00132D00 *)pCardInfo)->x = (value >> 16) - (((Sprite_00132D00 *)pCardInfo)->info->x & 0x1FFF);
                            ((Sprite_00132D00 *)pCardInfo)->y = (value & 0xFFFF) - (((Sprite_00132D00 *)pCardInfo)->info->y & 0x1FFF);
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
} Info_00132EE0;

/* Fills an empty combination: the hand card side `nSide` can summon with the best attack plus defence. */
void TaLogic_LabyrinthRuler_ConvEmptyCombo(s32 nSide, void *pCardInfo, s32 *pResult) {
    Info_00132EE0 *info = pCardInfo;
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
                if (card != 0x3E7 && TaLogic008_IsRefuseEmptyCombo(card) == 0 && level >= TaHand_GetCardSummonCost2(card, nSide)) {
                    cost = TaHand_GetCardAPDP(card);
                    if ((cost & 0xFFFF) + (cost >> 16) * 2 < 0x10CD && TaHand_IsCardEffect(card) == 2 &&
                        (u16)TaLogic_GetHandFusion(info->id, (u16)card) == 0x3E7) {
                        TaLogic_AddEmptyCombo(info->values, buf[i]);
                    }
                }
            }
        }
    }
}

/* Whether this duelist keeps card `nCardNo` out of a summon (it is wanted for an equip). */
s32 TaLogic008_IsRefuseEmptyCombo(s32 nCardNo) {
    if ((TaHand_GetCardKind(nCardNo) >> 5) != 0) {
        return 1;
    }
    if ((nCardNo == 0x23D) || (nCardNo == 0x216) || (nCardNo == 0x63)) {
        return 1;
    }
    return 0;
}

typedef struct {
    u8 pad0[6];
    u8 slot[5];
} Obj1_00133130;

typedef struct {
    u8 pad0[0x3C];
    u16 id;
} Obj2_00133130;

/* Fills hand combination `bCombo` for side `nSide` with this duelist's special combination, its card into
   `pCardInfo`. */
s32 TaLogic008_SetSpecialComboQue(s32 nSide, void *bCombo, void *pCardInfo) {
    Obj1_00133130 *o1 = bCombo;
    Obj2_00133130 *o2 = pCardInfo;
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

typedef struct Nibbles_00133320 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_00133320;

typedef struct Object_00133320 {
    u8 pad[0x3E];
    u8 flags;
} Object_00133320;

/* The square side `nSide` summons a card of kind `sKind` to. */
s32 TaLogic008_GetSummonPiece(s32 nSide, u8 sKind, void *pInput, s32 nMode) {
    s32 bestCell;
    s32 bestCost;
    Nibbles_00133320 path[12];
    s32 i;
    Nibbles_00133320 *p;

    extern s32 TaLogic_IsUnitWin4();
    extern s32 TaLogic_GetInvadeRoot2();
    extern s32 TaLogic_GetRoot2(s32, s32, s32, s32, s32, s32, u16, u8);

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

    if ((u8)(((Object_00133320 *)pInput)->flags >> 5) == 0 && nMode >= 0) {
        s32 cell;
        s32 y;
        s32 x;
        s32 index;
        s32 targetY;
        s32 targetX;
        s32 target;
        s32 cost;

        bestCost = 255;
        bestCell = 0xFFFF;
        target = SzDuel_GetUnitLoc(nMode >> 8, nMode & 0xFF);
        index = 0;
        targetY = target >> 8;
        targetX = target & 0xFF;
        do {
            cell = Ta_GetSommonPiecePreference(nSide, index);
            if (cell >= 0) {
                x = cell & 0xFF;
                y = cell >> 8;
                if (SzDuel_GetField(x, y) != 8 &&
                    (SzDuel_GetField(x, y) != 9 || Ta_IsVirus_Chk3(pInput, x, y) != 1) &&
                    SzDuel_GetMapUnit(x, y) == 0) {
                    if (TaLogic_IsUnitWin4((s32)pInput, nMode, TaLogic_LabyrinthRuler_GetWarnHideLvl(nSide), targetX, targetY, 0) > 0) {
                        cost = TaLogic_GetInvadeRoot2((s32)pInput, (s32)path, x, y, targetX, targetY, nMode, 0, 4,
                                            TaLogic_LabyrinthRuler_GetWarnHideLvl(nSide) & 0xFFFF);
                    } else {
                        cost = TaLogic_GetRoot2((s32)pInput, (s32)path, x, y, targetX, targetY, nMode, 4);
                    }
                    if (TaLogic_GetMinGoalCount((u8 *)path) > 0 && cost < bestCost) {
                        bestCost = cost;
                        bestCell = cell;
                    }
                }
            }
            index++;
        } while (index < 8);
        if (bestCell != 0xFFFF) {
            return bestCell;
        } else {
            bestCell = -1;
            return bestCell;
        }
    } else {
        s32 maxY;
        s32 maxX;
        s32 y;
        s32 x;
        s32 index;
        s32 bestDistance;
        s32 cell;
        s32 target;
        s32 targetY;
        s32 distance;
        s32 minY;
        s32 minX;

        bestDistance = 14;
        nMode = -1;
        index = 0;
        do {
            cell = Ta_GetSommonPiecePreference(nSide, index);
            if (cell >= 0) {
                x = cell & 0xFF;
                y = cell >> 8;
                if (SzDuel_GetField(x, y) != 8 &&
                    (SzDuel_GetField(x, y) != 9 || Ta_IsVirus_Chk3(pInput, x, y) != 1) &&
                    SzDuel_GetMapUnitID(x, y) < 0) {
                    target = TaLogic008_GetNextInvadePoint((s32)pInput, x, y);
                    targetY = target >> 8;
                    minY = y < targetY ? y : targetY;
                    if (targetY < y) {
                        maxY = y;
                    } else {
                        maxY = targetY;
                    }
                    minX = x < (target & 0xFF) ? x : (target & 0xFF);
                    if ((target & 0xFF) < x) {
                        maxX = x;
                    } else {
                        maxX = target & 0xFF;
                    }
                    distance = (maxX - minX) + (maxY - minY);
                    if (distance < bestDistance && distance >= 0) {
                        nMode = cell;
                        bestDistance = distance;
                    }
                }
            }
            index++;
        } while (index < 8);
        nMode = bestDistance < 14 ? nMode : -1;
    }
    return nMode;
}

typedef struct {
    u8 low : 4;
    u8 high : 4;
} Flags_001336A0;

typedef struct {
    u16 id;
    u8 action;
    u8 pad3;
    u16 position;
    u8 pad6[6];
    s32 value;
    u8 mode;
} Output_001336A0;

/* The task of a unit running from danger (task `pTask`): the safest square in reach, into `pInput` (`fFirst` = 1
   for the unit's first-choice task). */
s32 TaLogic_LabyrinthRuler_GetMinimumTask_RunMission(u16 *pTask, s32 nSide, void *pInput, u8 fFirst) {
    extern s32 TaLogic_IsRunPassRoot(s32, s32, s32, s32, s32, s32, void *, u8);
    extern s32 TaLogic_LabyrinthRuler_IsOpenUnit();
    s32 position;
    u8 upperX;
    u8 flag;
    Flags_001336A0 cells[12];
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
    Output_001336A0 *out = pInput;

    position = SzDuel_GetUnitLoc(*pTask >> 8, *pTask & 0xFF);
    i = 0;
    do {
        cells[i].low = cells[i].high = 15;
        i++;
    } while (i < 12);

    {
        u16 value = (u16)TaLogic_LabyrinthRuler_GetWarnHideLvl(nSide);
        originalX = position & 0xFF;
        originalY = position >> 8;
        if (TaLogic_GetUnitWarning(originalX, originalY, *pTask, 3, value, 0) == 0) {
            out->id = *pTask;
            out->action = 6;
            out->position = position;
            out->mode = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, out->position, 1, 0);
            out->value = TaLogic_LabyrinthRuler_IsOpenUnit(*pTask >> 8, *pTask & 0xFF, pTask);
            TaLogic_InitRogicControl(pTask, fFirst);
            return 0;
        } else {
            result = GetMoveRange(SzDuel_GetUnit(*pTask >> 8, *pTask & 0xFF), originalX, originalY);
            if (result == 0) {
                out->id = *pTask;
                out->action = 6;
                out->position = position;
                out->mode = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, out->position, 1, 0);
                out->value = TaLogic_LabyrinthRuler_IsOpenUnit(*pTask >> 8, *pTask & 0xFF, pTask);
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
                    flag = TaLogic_IsAttackedNow(*pTask >> 8, *pTask & 0xFF, 0) & 0xFF;
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
                                (TaLogic_IsAttackedNow2(*pTask >> 8, *pTask & 0xFF, x, y, 0) == 0 || (u8)*pTask == 0)) {
                                value = (u16)TaLogic_LabyrinthRuler_GetWarnHideLvl(nSide);
                                score = TaLogic_GetUnitWarning(x, y, *pTask, 3, value, 0);
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
                        out->mode = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, out->position, 1, 0);
                    } else {
                        out->mode = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, out->position, 0, 0);
                    }
                    out->value = TaLogic_LabyrinthRuler_IsOpenUnit(*pTask >> 8, *pTask & 0xFF, pTask);
                } else {
                    out->id = *pTask;
                    out->action = 6;
                    out->position = position;
                    out->mode = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, out->position, 1, 0);
                    out->value = TaLogic_LabyrinthRuler_IsOpenUnit(*pTask >> 8, *pTask & 0xFF, pTask);
                }
                TaLogic_InitRogicControl(pTask, fFirst);
            }
        }
    }
    return 0;
}

typedef struct Input_00133BE0 {
    u16 position;
    u8 pad2[6];
    u32 destinations;
} Input_00133BE0;

typedef struct Output_00133BE0 {
    u16 position;
    u8 action;
    u8 pad3;
    u16 destination;
    u8 pad6[6];
    s32 flag;
    u8 result;
} Output_00133BE0;

typedef struct Position_00133BE0 {
    u8 x : 4;
    u8 y : 4;
} Position_00133BE0;

/* The task's target square: the second half-word when the second argument is 1, else the first. */
static inline u32 destination_00133BE0(void *input, s32 mode) {
    if (mode == 1) {
        return (u16)(((Input_00133BE0 *)input)->destinations >> 16);
    }
    return (u16)((Input_00133BE0 *)input)->destinations;
}

/* The task of a unit attacking (task `pTask`): its path to the goal, into `pInput`; -1 when it has none (`fFirst`
   = 1 for the unit's first-choice task). */
s32 TaLogic_LabyrinthRuler_GetMinimumTask_AtkMission(void *pTask, s32 nSide, void *pInput, u8 fFirst) {
    extern void TaLogic_GetInvadeRoot();
    Position_00133BE0 positions[12];
    s32 start;
    s32 unitInfo;
    s32 count;
    s32 startY;
    s32 startX;
    s32 flag;
    s32 target;
    s32 targetX;
    Position_00133BE0 *current;
    s32 initialFlag;
    s32 sourcePosition;
    s32 mode = fFirst;
    s32 candidate;
    s32 i;
    s32 bestScore;
    s32 bestIndex;
    u32 positionX;
    u32 positionY;
    Input_00133BE0 *input = pTask;
    Output_00133BE0 *output = pInput;

    positionX = destination_00133BE0(pTask, mode);
    positionY = destination_00133BE0(pTask, mode);
    if (SzDuel_GetUnit(positionY >> 8, positionX & 0xFF) == 0) {
        TaLogic_InitRogicControl(pTask, 1);
        return -1;
    }
    initialFlag = TaLogic_LabyrinthRuler_IsOpenUnit(input->position >> 8, input->position & 0xFF, pTask);
    start = SzDuel_GetUnitLoc(input->position >> 8, input->position & 0xFF);
    positionX = destination_00133BE0(pTask, mode);
    positionY = destination_00133BE0(pTask, mode);
    target = SzDuel_GetUnitLoc(positionY >> 8, positionX & 0xFF);
    for (i = 0; i < 12; i++) {
        positions[i].x = positions[i].y = 15;
    }
    unitInfo = SzDuel_GetUnit(input->position >> 8, input->position & 0xFF);
    startX = start & 0xFF;
    startY = start >> 8;
    if (GetMoveRange(unitInfo, startX, startY) == 0) {
        s32 score;
        output->position = input->position;
        output->action = 6;
        output->destination = start;
        score = TaLogic_GetUnitWarning(startX, startY, nSide, 3, 1, (u8)TaLogic_LabyrinthRuler_GetWarnHideLvl(nSide));
        if (score >= SzDuel_GetUnitAP(input->position >> 8, input->position & 0xFF, 0)) {
            output->result = TaLogic_IsDefStyleUnit(input->position >> 8, input->position & 0xFF, output->destination, 1, 0);
        } else {
            output->result = TaLogic_IsDefStyleUnit(input->position >> 8, input->position & 0xFF, output->destination, 0, 0);
        }
        TaLogic_InitRogicControl(pTask, fFirst);
    } else {
        s32 sourceX;
        s32 sourceY;
        u16 leader;
        sourcePosition = input->position;
        leader = (u16)TaLogic_LabyrinthRuler_GetWarnHideLvl(nSide);
        sourceY = sourcePosition >> 8;
        sourceX = sourcePosition & 0xFF;
        targetX = target & 0xFF;
        TaLogic_GetInvadeRoot(sourceY, sourceX, positions,
                     startX, startY, targetX, target >>= 8, destination_00133BE0(pTask, mode),
                     0, 30, leader);
        count = TaLogic_GetMinGoalCount((u8 *)positions);
        bestIndex = 0xFF;
        if (count > 0) {
            flag = 0;
            bestScore = 0xFFFF;
            for (candidate = 0; candidate < count; candidate++) {
                if (TaLogic008_IsOpenMoveUnit(input->position >> 8, input->position & 0xFF,
                                 startX, startY, targetX, target) == 1) {
                    bestIndex = candidate;
                    flag = 1;
                    positions[candidate].x = targetX;
                    positions[candidate].y = target;
                    candidate = count;
                } else {
                    s32 score;
                    current = &positions[candidate];
                    score = TaLogic_GetUnitWarning(current->x, current->y, nSide,
                                         4, 1, (u8)TaLogic_LabyrinthRuler_GetWarnHideLvl(nSide));
                    if (score < bestScore) {
                        bestScore = score;
                        bestIndex = candidate;
                    } else if (score == bestScore) {
                        Position_00133BE0 *best = &positions[bestIndex];
                        s32 bestMinY = (best->y < target ? best->y : target);
                        s32 bestMaxY = MaxSel(best->y, target);
                        s32 bestMinX = (best->x < targetX ? best->x : targetX);
                        s32 bestMaxX = MaxSel(best->x, targetX);
                        s32 currentMinY = (current->y < target ? current->y : target);
                        s32 currentMaxY = MaxSel(current->y, target);
                        s32 currentMinX = (current->x < targetX ? current->x : targetX);
                        s32 currentMaxX = MaxSel(current->x, targetX);
                        if ((currentMaxX - currentMinX) + (currentMaxY - currentMinY) <
                            (bestMaxX - bestMinX) + (bestMaxY - bestMinY)) {
                            bestScore = score;
                            bestIndex = candidate;
                        }
                    }
                }
            }
        } else {
            output->position = input->position;
            output->action = 6;
            output->destination = start;
            output->flag = initialFlag;
            output->result = TaLogic_IsDefStyleUnit(input->position >> 8, input->position & 0xFF,
                                          output->destination, 0, 0);
            TaLogic_InitRogicControl(pTask, fFirst);
            return 0;
        }
        if (bestIndex != 0xFF) {
            output->position = input->position;
            output->action = 6;
            output->destination = (positions[bestIndex].y << 8) | positions[bestIndex].x;
            output->flag = flag;
            output->result = TaLogic_IsDefStyleUnit(input->position >> 8, input->position & 0xFF,
                                          output->destination, 0, 0);
        } else {
            output->position = input->position;
            output->action = 6;
            output->destination = start;
            output->flag = flag;
            output->result = TaLogic_IsDefStyleUnit(input->position >> 8, input->position & 0xFF,
                                          output->destination, 0, 0);
            TaLogic_InitRogicControl(pTask, fFirst);
            return 0;
        }
    }
    return 0;
}

typedef struct Position_001341C0 {
    u8 x : 4;
    u8 y : 4;
} Position_001341C0;

typedef struct Source_001341C0 {
    u16 id;
    u8 pad2[6];
    u32 target;
} Source_001341C0;

typedef struct Result_001341C0 {
    u16 id;
    u8 kind;
    u8 pad3;
    u16 target;
    u8 pad6[6];
    s32 value;
    u8 flags;
} Result_001341C0;

#define target_001341C0(src, side) ((side) == 1 ? ((((Source_001341C0 *)(src))->target >> 16) & 0xFFFF) : (u32)(u16)((Source_001341C0 *)(src))->target)

#define min_001341C0(a, b) ((a) < (b) ? (a) : (b))
#define max_001341C0(a, b) ((b) < (a) ? (a) : (b))
#define distance_001341C0(pos, src, side) \
    ((max_001341C0((u8)(pos).x, (u32)(u8)target_001341C0(src, side)) - \
      min_001341C0((u8)(pos).x, (u32)(u8)target_001341C0(src, side))) + \
     (max_001341C0((u8)(pos).y, (u32)target_001341C0(src, side) >> 8) - \
      min_001341C0((u8)(pos).y, (u32)target_001341C0(src, side) >> 8)))

/* The task of a unit moving to its goal (task `pTask`), into `pInput` (`fFirst` = 1 for the unit's first-choice
   task). */
s32 TaLogic_LabyrinthRuler_GetMinimumTask_MoveMission(void *pTask, s32 nSide, void *pInput, u8 fFirst, u8 nKind) {
    extern void TaLogic_GetRoot();
    extern s32 TaLogic_IsDefStyleUnit(s32, s32, s32, u8, s32);
    Position_001341C0 positions[12];
    s32 start;
    s32 count;

    start = SzDuel_GetUnitLoc(((Source_001341C0 *)pTask)->id >> 8, ((Source_001341C0 *)pTask)->id & 0xFF);
    {
        s32 score;
        s32 best;
        s32 side = fFirst;
        Position_001341C0 *p;
        s32 i;
        if (target_001341C0(pTask, side) == 0xFFFF && start == target_001341C0(pTask, side)) {
            ((Result_001341C0 *)pInput)->id = ((Source_001341C0 *)pTask)->id;
            ((Result_001341C0 *)pInput)->kind = 6;
            ((Result_001341C0 *)pInput)->target = start;
            ((Result_001341C0 *)pInput)->flags = TaLogic_IsDefStyleUnit(((Source_001341C0 *)pTask)->id >> 8, ((Source_001341C0 *)pTask)->id & 0xFF, ((Result_001341C0 *)pInput)->target, nKind, 0);
            ((Result_001341C0 *)pInput)->value = TaLogic_LabyrinthRuler_IsOpenUnit(((Source_001341C0 *)pTask)->id >> 8, ((Source_001341C0 *)pTask)->id & 0xFF, pTask);
            TaLogic_InitRogicControl(pTask, fFirst);
            return 0;
        }
        p = positions;
        {
            s32 clear_count = 0;
            Position_001341C0 *clear = p;
            s32 terrain;
            do {
                clear->x = clear->y = 15;
                clear_count++;
                clear++;
            } while (clear_count < 12);

            terrain = SzDuel_GetMapUnitID(target_001341C0(pTask, side) & 0xFF, (u32)target_001341C0(pTask, side) >> 8);
            if (terrain < 0) {
                terrain = 0xFFFF;
            }
            TaLogic_GetRoot(((Source_001341C0 *)pTask)->id >> 8, ((Source_001341C0 *)pTask)->id & 0xFF, positions,
                          start & 0xFF, start >> 8, target_001341C0(pTask, side) & 0xFF,
                          (u32)target_001341C0(pTask, side) >> 8, (u16)terrain, 7);
            count = TaLogic_GetMinGoalCount((u8 *)positions);
        }
        if (count > 0) {
            best = 0xFF;
            score = 0xFFFF;
            for (i = 0; i < count; i++, p++) {
                if (SzDuel_GetMapUnit(p->x, p->y) == 0) {
                    s32 value = TaLogic_GetUnitWarning(p->x, p->y, nSide, 4, 1, (u8)TaLogic_LabyrinthRuler_GetWarnHideLvl(nSide));
                    if (value < score) {
                        score = value;
                        best = i;
                    } else if (value == score) {
                        if (distance_001341C0(*p, pTask, side) < distance_001341C0(positions[best], pTask, side)) {
                            score = value;
                            best = i;
                        }
                    }
                }
            }
        } else {
            ((Result_001341C0 *)pInput)->id = ((Source_001341C0 *)pTask)->id;
            ((Result_001341C0 *)pInput)->kind = 6;
            ((Result_001341C0 *)pInput)->target = start;
            ((Result_001341C0 *)pInput)->flags = TaLogic_IsDefStyleUnit(((Source_001341C0 *)pTask)->id >> 8, ((Source_001341C0 *)pTask)->id & 0xFF, ((Result_001341C0 *)pInput)->target, nKind, 0);
            ((Result_001341C0 *)pInput)->value = TaLogic_LabyrinthRuler_IsOpenUnit(((Source_001341C0 *)pTask)->id >> 8, ((Source_001341C0 *)pTask)->id & 0xFF, pTask);
            TaLogic_InitRogicControl(pTask, fFirst);
            return 0;
        }
        if (best != 0xFF) {
            ((Result_001341C0 *)pInput)->id = ((Source_001341C0 *)pTask)->id;
            ((Result_001341C0 *)pInput)->kind = 6;
            ((Result_001341C0 *)pInput)->target = (positions[best].y << 8) | positions[best].x;
            ((Result_001341C0 *)pInput)->flags = TaLogic_IsDefStyleUnit(((Source_001341C0 *)pTask)->id >> 8, ((Source_001341C0 *)pTask)->id & 0xFF, ((Result_001341C0 *)pInput)->target, nKind, 0);
            ((Result_001341C0 *)pInput)->value = TaLogic_LabyrinthRuler_IsOpenUnit(((Source_001341C0 *)pTask)->id >> 8, ((Source_001341C0 *)pTask)->id & 0xFF, pTask);
        } else {
            ((Result_001341C0 *)pInput)->id = ((Source_001341C0 *)pTask)->id;
            ((Result_001341C0 *)pInput)->kind = 6;
            ((Result_001341C0 *)pInput)->target = start;
            ((Result_001341C0 *)pInput)->flags = TaLogic_IsDefStyleUnit(((Source_001341C0 *)pTask)->id >> 8, ((Source_001341C0 *)pTask)->id & 0xFF, ((Result_001341C0 *)pInput)->target, nKind, 0);
            ((Result_001341C0 *)pInput)->value = TaLogic_LabyrinthRuler_IsOpenUnit(((Source_001341C0 *)pTask)->id >> 8, ((Source_001341C0 *)pTask)->id & 0xFF, pTask);
        }
        TaLogic_InitRogicControl(pTask, fFirst);
    }
    return 0;
}

/* The first wall gap (a square of the wall rows that is not a wall) side `nSide` can use, or -1. */
s32 TaLogic008_GetWallEmpty(s32 nSide) {
    s32 row;
    s32 column;
    s32 position;

    for (row = 0; row < 7; row++) {
        if (row % 2 == 1) {
            column = 1;
            do {
                if (SzDuel_GetField(column, row) != 8) {
                    return (row << 8) | column;
                }
                column++;
            } while (column <= 5);
        }
    }

    for (row = 0; row < 7; row++) {
        column = 0;
        do {
            position = SzDuel_GetMapUnitID(row, column);
            if (position >= 0 &&
                nSide != Ta_IsUnitControl(position >> 8, position & 0xFF) &&
                column < 3 &&
                SzDuel_GetField(6, 0) != 8 &&
                SzDuel_GetField(5, 0) != 8) {
                return 6;
            }
            column++;
        } while (column <= 6);
    }

    return -1;
}

/* How careful this duelist is about hidden cards (by its life points and monster count). */
s32 TaLogic_LabyrinthRuler_GetWarnHideLvl(s32 nSide) {
    if (SzDuel_GetLP(nSide) > 0x3E8) {
        if (SzDuel_GetUnitMonsterCount(nSide) >= 4) {
            return 0x2EE;
        } else {
            return 0x5DC;
        }
    } else {
        return 0x6A4;
    }
}

/* Whether this duelist opens (turns face up) unit (nSide, nID) now: 0 no, 1 or 2 by its kind. */
s32 TaLogic_LabyrinthRuler_IsOpenUnit(s32 nSide, s32 nID, void *pInfo) {
    extern s32 SzDuel_GetUnitCardNo();
    s32 i;
    s32 card;
    s32 position;
    u32 *effect;
    u8 count;

    card = SzDuel_GetUnitCardNo();
    Ta_IsUnitControl(nSide, nID);
    position = SzDuel_GetUnitLoc(nSide, nID);
    effect = SzDuel_GetUnitEffect(nSide, nID, 0);
    count = 0;
    if (SzDuel_GetUnitStatus(nSide, nID, 4) != 0) {
        return 0;
    }
    switch (SzDuel_GetUnitKind(nSide, nID) >> 5) {
    case 0:
        switch (card) {
        case 0xBE:
            i = 1;
            while (1) {
                if ((SzDuel_GetUnitKind(nSide, i) & 0x1F) == 9) {
                    if (nSide == Ta_IsUnitControl(nSide, i)) {
                        count++;
                    }
                }
                if ((SzDuel_GetUnitKind(nSide == 0 ? 1 : 0, i) & 0x1F) == 9) {
                    if (nSide == Ta_IsUnitControl(nSide == 0 ? 1 : 0, i)) {
                        count++;
                    }
                }
                i++;
                if (i > 5) {
                    break;
                }
            }
            if (count >= 3) {
                return 1;
            }
            break;
        }
        return 2;
    case 5:
        if (TaLogic_GetActionReaction(nSide, nID, 0, 0, 6, 0) == 5) {
            return 2;
        }
        if (TaLogic008_IsDoCerem(Ta_IsUnitControl(nSide, nID), card) == 1) {
            if (SzDuel_GetField(position & 0xFF, position >> 8) != 9) {
                return 1;
            }
        }
        break;
    case 1:
        if (TaLogic_GetActionReaction(nSide, nID, 0, 0, 6, 0) == 5) {
            return 2;
        }
        if (effect == NULL) {
            return 2;
        }
        switch (*effect >> 8) {
        case 2:
        case 0x48: {
            i = TaLogic008_GetWallEmpty(nSide);
            if (i >= 0 && i == SzDuel_GetUnitLoc(nSide, nID)) {
                return 1;
            }
            break;
        }
        case 0xD:
            return 1;
        case 0x25: {
            i = 1;
            while (1) {
                if (SzDuel_GetUnit(nSide, i) != 0) {
                    if (SzDuel_GetUnitCardNo(nSide, i) != 0x91) {
                        if (nSide == Ta_IsUnitControl(nSide, i)) {
                            count++;
                        }
                    }
                }
                if (SzDuel_GetUnit(nSide == 0 ? 1 : 0, i) != 0) {
                    if (SzDuel_GetUnitCardNo(nSide == 0 ? 1 : 0, i) != 0x91) {
                        if (nSide == Ta_IsUnitControl(nSide == 0 ? 1 : 0, i)) {
                            count++;
                        }
                    }
                }
                i++;
                if (i > 5) {
                    break;
                }
            }
            if (count > 0) {
                return 1;
            }
            break;
        }
        }
        break;
    default:
        return 2;
    }
    return 2;
}

/* Whether unit (nSide, nID) may open while moving from (nX, nZ) to the square next to it, (gX, gZ). */
s32 TaLogic008_IsOpenMoveUnit(s32 nSide, s32 nID, s32 nX, s32 nZ, s32 gX, s32 gZ) {
    s32 min_y;
    s32 min_x;

    min_y = Min(nZ, gZ);
    gZ = Max(gZ, nZ);
    min_x = Min(nX, gX);
    gX = Max(gX, nX);
    if ((gX - min_x) + (gZ - min_y) != 2) {
        return 0;
    }
    if (SzDuel_GetUnit(nSide, nID) == 0) {
        return 0;
    }
    if (SzDuel_GetUnitStatus(nSide, nID, 0) == 0) {
        return CheckLandAgreement2(SzDuel_GetField(nX, nZ), nSide, nID) != 1 ? 0 : 1;
    }
    return 0;
}

/* Whether side `nSide` can play ritual card `nCardNo` now (it has the units to give up). */
s32 TaLogic008_IsDoCerem(s32 nSide, s32 nCardNo) {
    s32 sp20[4];

    Ta_GetCeremSacrifice(sp20, *(s32 *)((u8 *)TaHand_GetCardEffect(nCardNo, 0) + 4));
    if (Ta_GetSacrificeUnit(sp20, nSide) < 0) {
        return 0;
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
} Req_00135060;

typedef struct {
    u8 pad0[0x160];
    u16 list[32];    /* 0x160 */
    u8 idx : 5;      /* 0x1A0 */
    u8 pad1A0 : 3;
    u8 pad1A1;
    u16 count;       /* 0x1A2 */
} Work_00135060;

/* Computer duelist 8's controller (duelistControllers[8]): the buttons it presses this frame. With an empty input
   queue it plans its next task and turns it into buttons, then plays the queue back one button per frame; after
   600 frames it gives up the turn (0x20, then 0x800). */
s32 duelistController08(s32 wCursorPos, void *pCtl) {
    Req_00135060 req;
    Work_00135060 *w;
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
        if (TaLogic_LabyrinthRuler_GetMinimumTask(w, &req, wCursorPos) == 0) {
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

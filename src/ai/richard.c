/* Computer AI of Richard Slysheen of York (duelist 10, duelistController10). */

#include "common.h"

typedef struct {
    u8 pad0[0x1A1];
    u8 lvl : 4;      /* 0x1A1 */
    u8 pad1A1 : 4;
} Ai_00139890;
#pragma conditional_move off

/* This duelist's move: picks the next unit to act, gives it a task and turns that into input `pInput`; returns 1
   when it set one. */
s32 TaLogic_Richard_GetMinimumTask(void *pCtl, void *pInput, s32 wCursorPos) {
    UnitTask *tasks = pCtl;
    Ai_00139890 *ai = pCtl;
    s32 side;
    s32 found;
    s32 result;
    s32 index;

    side = SzDuel_GetTurnOwner();
    found = 0;
    ai->lvl = TaLogic010_IsActiveMode();
    if ((result = TaLogic_Richard_GetNextActiveUnit(tasks, side, ai->lvl, pInput)) < 0) {
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
    TaLogic_Richard_CommandUnit(&tasks[index], ai->lvl);
    switch ((tasks[index].mission >> 8) & 0xFF) {
    case TASK_RUN:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            TaLogic_Richard_GetMinimumTask_RunMission(&tasks[index], side, pInput, 1);
            found = 1;
        }
        break;
    case TASK_ATTACK:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            if (TaLogic_Richard_GetMinimumTask_AtkMission(&tasks[index], side, pInput, 1) < 0) {
                TaLogic_InitRogicControl(&tasks[index], 1);
                return 1;
            }
            found = 1;
        }
        break;
    case TASK_SUMMON:
        if (TaLogic_Richard_GetMinimumTask_Summon(tasks[index].ownerId, side, pInput) < 0) {
            TaLogic_InitRogicControl(&tasks[index], 1);
            *(u8 *)((u8 *)pInput + 2) = 0xFF;
            *(s32 *)((u8 *)pInput + 0xC) = 0;
        } else {
            TaLogic_InitRogicControl(&tasks[index], 1);
            found = 1;
        }
        break;
    case TASK_MOVETOLOCATION:
        TaLogic_Richard_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 1, 0);
        found = 1;
        break;
    case TASK_CONFIRMUNIT:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            TaLogic_Richard_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 1, 1);
            found = 1;
        }
        break;
    case TASK_ENCHANT:
        TaLogic_GetMinimumTask_EncMission(&tasks[index], side, pInput, 1, 0, TaLogic_Richard_GetWarnHideLvl(side), 2, 1);
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
            TaLogic_Richard_GetMinimumTask_RunMission(&tasks[index], side, pInput, 0);
            found = 1;
        }
        break;
    case 2:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            if (TaLogic_Richard_GetMinimumTask_AtkMission(&tasks[index], side, pInput, 0) < 0) {
                TaLogic_Richard_GetMinimumTask_RunMission(&tasks[index], side, pInput, 0);
            }
            found = 1;
        }
        break;
    case 10:
        if (TaLogic_Richard_GetMinimumTask_Summon(tasks[index].ownerId, side, pInput) < 0) {
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
            TaLogic_Richard_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 0, 0);
            found = 1;
        }
        break;
    case 3:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            TaLogic_Richard_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 0, 1);
            found = 1;
        }
        break;
    case 9:
        TaLogic_GetMinimumTask_EncMission(&tasks[index], side, pInput, 0, 0, TaLogic_Richard_GetWarnHideLvl(side), 2, 1);
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

typedef struct Halves_00139D90 {
    u16 low;
    u16 high;
} Halves_00139D90;

typedef struct Record_00139D90 {
    u16 id;
    u16 pad2;
    s16 code;
    u16 pad6;
    union {
        s32 word;
        Halves_00139D90 halves;
    } data;
} Record_00139D90;
#pragma conditional_move reset

/* Gives the unit of task `pTask` its order for this turn (attack, run, move, summon, guard). */
s32 TaLogic_Richard_CommandUnit(void *pCtl, s32 pTask) {
    extern void TaLogic010_CommandSpellUnit();
    Record_00139D90 *record = pCtl;
    s32 value;
    s32 state;

    value = SzDuel_GetUnitLoc((s32) record->id >> 8, record->id & 0xFF);
    state = Ta_IsUnitControl((s32) record->id >> 8, record->id & 0xFF);
    if (SzDuel_GetUnit((s32) record->id >> 8, record->id & 0xFF) != 0) {
        if (SzDuel_GetUnitStatus((s32) record->id >> 8, record->id & 0xFF, 0) == 0) {
            if (record->id != 0xFFFF) {

                if ((record->id & 0xFF) == 0) {
                    if (record->data.word == -1) {
                        if (TaLogic_IsAttackedNow((s32) record->id >> 8, record->id & 0xFF, 0) == 1) {
                            if (SzDuel_InqHandPhase((s32) record->id >> 8) == 1) {
                                record->code = 0x50A;
                            } else {
                                record->code = 0x5FF;
                            }
                        } else if (SzDuel_InqHandPhase((s32) record->id >> 8) == 1) {
                            record->code = 0xA06;
                            if ((pTask & 0xFF) == 1) {
                                record->data.word = (record->data.word & 0xFFFF0000) |
                                    (((((value >> 8) + 1) << 8) | (value & 0xFF)) & 0xFFFF);
                            } else {
                                record->data.word = (record->data.word & 0xFFFF0000) | (value & 0xFFFF);
                            }
                        } else {
                            record->code = 0x6FF;
                            if ((pTask & 0xFF) == 1) {
                                record->data.word = (u16) record->data.word |
                                    (((((value >> 8) + 1) << 8) | (value & 0xFF)) << 16);
                            } else {
                                record->data.word = (value << 16) | record->data.halves.low;
                            }
                        }
                    }
                } else {
                    switch (SzDuel_GetUnitKind((s32) record->id >> 8, record->id & 0xFF) >> 5) {
                    case 0:
                        TaLogic010_CommandBtlUnit(pCtl, 1, pTask);
                        break;
                    case 2:
                        TaLogic_CommandEncUnit(pCtl, 2, 0, TaLogic_Richard_GetWarnHideLvl(state) & 0xFF);
                        break;
                    case 1:
                    case 3:
                        TaLogic010_CommandSpellUnit(pCtl, pTask);
                        break;
                    default:
                        record->code = 0x5FF;
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
s32 TaLogic_Richard_GetNextActiveUnit(DuelPlayer *pCtl, s32 nSide, s32 pInput, void *nMode) {
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
    TaLogic_Richard_CommandUnit(&pCtl->taskList[idx], pInput);
    if (((pCtl->taskList[idx].mission >> 8) & 0xFF) == 10) {
        if (SzDuel_InqHandPhase(nSide) == 1 && TaLogic_Richard_GetMinimumTask_Summon(pos, nSide, nMode) >= 0) {
            return pos | 0x10000;
        }
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_GetUnitStatus(nSide, 0, 0) == 0) {
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_InqHandPhase(nSide) == 1 && TaLogic_Richard_GetMinimumTask_Summon(pos, nSide, nMode) >= 0) {
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

typedef struct Entry_0013A400 {
    u16 id;
    u8 flag;
    u8 pad;
} Entry_0013A400;

/* Orders a fighting unit (task `pTask`): straight at the enemy leader when `fGoalFirst` and the path is open,
   else at the nearest enemy it can beat within 2 squares (5 with `bActive`); else it pushes in. */
void TaLogic010_CommandBtlUnit(void *pTask, s32 fGoalFirst, s32 bActive) {
    extern s32 TaLogic_IsRootOpen();
    extern s32 TaLogic010_GetNearUnit();
    extern void TaLogic_InitIgnoreLst();
    s32 position;
    u8 workspace[0x70];
    Entry_0013A400 entries[23];
    s16 count;
    s16 result;
    u16 id;

    id = *(u16 *)pTask;
    if (SzDuel_GetUnit(id >> 8, id & 0xFF) != 0) {
        s32 side;
        s32 target;
        s32 otherPosition;
        s32 targetLow;
        s32 targetHigh;
        s32 data;
        s32 i;
        Entry_0013A400 *entry;

        id = *(u16 *)pTask;
        side = Ta_GetCurrentSide(id >> 8, id & 0xFF);
        target = (side == 0 ? 1 : 0) << 8;
        position = SzDuel_GetUnitLoc(*(u16 *)pTask >> 8, *(u16 *)pTask & 0xFF);
        targetHigh = target >> 8;
        targetLow = target & 0xFF;
        otherPosition = SzDuel_GetUnitLoc(targetHigh, targetLow);
        id = *(u16 *)pTask;
        data = SzDuel_GetUnit(id >> 8, id & 0xFF);
        TaLogic_InitIgnoreLst(workspace);
        entry = entries;
        i = 0;
        do {
            i++;
            entry->id = 0xFFFF;
            entry->flag = 0xFF;
            entry++;
        } while (i < 22);

        if (fGoalFirst != 0) {
            id = *(u16 *)pTask;
            if (TaLogic_IsRootOpen(id >> 8, id & 0xFF, position & 0xFF,
                    position >> 8, targetHigh, targetLow, otherPosition & 0xFF,
                    otherPosition >> 8, 2) > 0) {
                *(u16 *)((u8 *)pTask + 4) = 0x2FF;
                *(u32 *)((u8 *)pTask + 8) =
                    (target << 16) | *(u16 *)((u8 *)pTask + 8);
                return;
            }
        }

        result = 0;
        count = 0;
        for (i = 1; i <= (bActive ? 1 : 3); i++) {
            s32 limit;
            s32 opposite;
            s32 value;

            limit = bActive ? 1 : 3;
            opposite = Ta_GetCurrentSide(*(u16 *)pTask >> 8, *(u16 *)pTask & 0xFF) == 0 ? 1 : 0;
            value = TaLogic_Richard_GetWarnHideLvl(side);
            switch (TaLogic010_GetNearUnit((s32)pTask, 0, data, position & 0xFF,
                        position >> 8, opposite, (u8)i, value,
                        (s32)entries, 0, (s32)&count, (s32)&result,
                        (u8)limit, (s32)workspace)) {
            case 3:
                *(u16 *)((u8 *)pTask + 4) = 0x6FF;
                *(u32 *)((u8 *)pTask + 8) =
                    (position << 16) | *(u16 *)((u8 *)pTask + 8);
                return;
            case 2:
                *(u16 *)((u8 *)pTask + 4) = 0x3FF;
                *(u32 *)((u8 *)pTask + 8) =
                    (position << 16) | *(u16 *)((u8 *)pTask + 8);
                return;
            case 1:
                return;
            case 0:
                *(u16 *)((u8 *)pTask + 4) = 0x3FF;
                *(u32 *)((u8 *)pTask + 8) =
                    (position << 16) | *(u16 *)((u8 *)pTask + 8);
                return;
            }
        }
        TaLogic010_CommandInvadeUnit(pTask, bActive);
    }
}

/* TaLogic_GetNearUnit with this duelist's view and strength settings. */
s32 TaLogic010_GetNearUnit(s32 pTask, s32 pTree, s32 pVarInfo, s32 nX, s32 nZ, s32 eSide, s32 bDist, s32 WarnLvl, s32 nUnitLst, u16 wUnitNum, s32 wSize, s32 wNodeCount, u8 bChase, s32 wIgnoreLst) {
    return TaLogic_GetNearUnit(pTask, pTree, pVarInfo, nX, nZ, eSide, bDist, WarnLvl,
                  nUnitLst, wUnitNum, wSize, wNodeCount, bChase,
                  0, 2500, wIgnoreLst);
}

typedef struct Packet_0013A710 {
    u16 location;
    u16 unk2;
    s16 mode;
    u16 unk6;
    union {
        u32 word;
        u16 lower;
    } value;
} Packet_0013A710;

/* Orders a unit (task `pTask`) to push into the opponent's side of the board. */
void TaLogic010_CommandInvadeUnit(void *pTask, s32 nMode) {
    Packet_0013A710 *packet = pTask;
    s32 item;
    s32 encoded;
    s32 result;
    u16 location;

    location = packet->location;
    item = Ta_IsUnitControl(location >> 8, location & 0xFF);
    location = packet->location;
    encoded = SzDuel_GetUnitLoc(location >> 8, location & 0xFF);
    if ((nMode & 0xFF) == 1) {
        item = encoded & 0xFF;
        encoded = (encoded >> 8) + 1;
        result = SzDuel_GetMapUnitID(item, encoded);
        if (result >= 0) {
            packet->mode = 0x2FF;
            packet->value.word = (result << 16) | packet->value.lower;
        } else {
            packet->mode = 0x6FF;
            packet->value.word = packet->value.lower | (((encoded << 8) | item) << 16);
        }
        return;
    } else {
        nMode = encoded >> 8;
        if (nMode != TaLogic010_GetLineHeight(item)) {
            result = TaLogic010_GetEmptyLine(item);
            if (result >= 0) {
                packet->mode = 0x6FF;
                packet->value.word = (result << 16) | packet->value.lower;
            } else {
                packet->mode = 0x6FF;
                packet->value.word = packet->value.lower | ((((nMode + 1) << 8) | (encoded & 0xFF)) << 16);
            }
        } else {
            packet->mode = 0x6FF;
            packet->value.word = (encoded << 16) | packet->value.lower;
        }
    }
}

/* The free line of the board this duelist's units fill next. */
s32 TaLogic010_GetEmptyLine(s32 nSide) {
    s32 i;
    s32 lineRow;

    lineRow = TaLogic010_GetLineHeight(nSide) & 0xFF;
    i = 0;
    do {
        switch (i) {
        case 0:
            if (SzDuel_GetMapUnit(3, lineRow) == 0) {
                return (lineRow << 8) | 3;
            }
            break;
        case 1:
            if (SzDuel_GetMapUnit(4, lineRow) == 0) {
                return (lineRow << 8) | 4;
            }
            break;
        case 2:
            if (SzDuel_GetMapUnit(2, lineRow) == 0) {
                return (lineRow << 8) | 2;
            }
            break;
        case 3:
            if (SzDuel_GetMapUnit(5, lineRow) == 0) {
                return (lineRow << 8) | 5;
            }
            break;
        case 4:
            if (SzDuel_GetMapUnit(1, lineRow) == 0) {
                return (lineRow << 8) | 1;
            }
            break;
        }
        i++;
    } while (i < 5);
    return -1;
}

/* How far forward side `nSide`'s units stand (the highest row of its cards, at least 2). */
s32 TaLogic010_GetLineHeight(s32 nSide) {
    s32 i;
    u8 maximum;
    s32 value;

    maximum = 0;
    for (i = 1; i <= 5; i++) {
        if (SzDuel_GetUnit(nSide, i) != 0) {
            value = (SzDuel_GetUnitLoc(nSide, i) >> 8) & 0xFF;
            if (maximum < value) {
                maximum = value;
            }
        }
    }
    if (maximum < 2) {
        maximum = 2;
    }
    return maximum;
}

typedef struct State_0013AA40 {
    u16 position;
    u16 unk2;
    s16 mode;
    u16 unk6;
    union {
        u16 halves[2];
        u32 word;
    } info;
} State_0013AA40;

/* The square of unit id `position`. */
static inline s32 decode_0013AA40(s32 position) {
    return SzDuel_GetUnitLoc(position >> 8, position & 0xFF);
}

/* Orders a face-down magic card (task `pTask`): whether and where to open it. */
void TaLogic010_CommandSpellUnit(void *pTask) {
    State_0013AA40 *state = pTask;
    s32 temp_s0;
    s32 controllingSide;
    s32 temp_a0;
    s32 useThunderBolt;
    u16 position;
    u16 position2;
    u16 position3;

    position = state->position;
    controllingSide = Ta_IsUnitControl((s32) position >> 8, position & 0xFF);
    position2 = state->position;
    temp_s0 = decode_0013AA40(position2);
    position3 = state->position;
    temp_a0 = SzDuel_GetUnitKind((s32) position3 >> 8, position3 & 0xFF) >> 5;
    switch (temp_a0) {
    case 1:
        useThunderBolt = TaLogic010_GetUseThunderBolt(controllingSide);
        if (useThunderBolt >= 0) {
            state->mode = 0x6FF;
            state->info.word = state->info.halves[0] | ((((temp_s0 >> 8) << 8) | (SzDuel_GetUnitLoc(useThunderBolt >> 8, useThunderBolt & 0xFF) & 0xFF)) << 0x10);
            return;
        }
        state->mode = 0x5FF;
        break;
    case 3:
        state->mode = 0x3FF;
        state->info.word = state->info.halves[0] | (((temp_s0 & 0xFF) | ((SzDuel_GetUnitLoc(controllingSide, 0) >> 8) << 8)) << 0x10);
        return;
    }
    state->mode = 0x5FF;
}

typedef struct {
    u8 pad00[0x3C];
    u16 unk3C;
    u8 pad3E[0x22];
} Work_0013AB70;

typedef struct {
    u16 id;
    u8 unk2;
    u8 pad3;
    s16 unk4;
    u8 pad6[6];
    s32 unkC;
} Ctx_0013AB70;

/* The summon task for side `nSide`: which hand cards to play and where, into `pInput`; -1 when it plays none. */
s32 TaLogic_Richard_GetMinimumTask_Summon(s32 wUnit, s32 nSide, void *pInput) {
    extern s32 TaLogic_GetUnitNum();
    Work_0013AB70 work;
    s32 ret;
    s32 res;
    s32 pos;
    s32 kind;
    Ctx_0013AB70 *ctx = (Ctx_0013AB70 *)pInput;

    ctx->id = wUnit;
    if (SzDuel_InqHandPhase(nSide) == 0) {
        return -1;
    }
    if (TaLogic_GetUnitNum(nSide, 0) == 5 && TaLogic_GetUnitNum(nSide, 1) == 5) {
        return -1;
    }
    kind = TaLogic010_IsHandPlay(nSide, &work);
    if (kind < 0) {
        return -1;
    }
    ctx->unk2 = 10;
    ctx->unkC = 0;
    pos = SzDuel_GetUnitLoc(wUnit >> 8, wUnit & 0xFF);
    if (kind == 0) {
        if (TaLogic010_SetComboQue(nSide, (u8 *)ctx, &work) >= 0) {
            ret = TaLogic_GetNearCard2(&work, pos & 0xFF, pos >> 8,
                                nSide == 0 ? 1 : 0, 2, 0x1F, 2, 2,
                                0, TaLogic_Richard_GetWarnHideLvl(nSide));
            if (ret < 0) {
                if (SzDuel_GetUnitMonsterCount(nSide) < 6) {
                    res = TaLogic010_GetSummonPiece(nSide, kind, &work, ret);
                    if (res < 0) {
                        return -1;
                    }
                    ctx->unk4 = res;
                    return 1;
                }
            } else {
                res = TaLogic010_GetSummonPiece(nSide, kind, &work, ret);
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
                            0, TaLogic_Richard_GetWarnHideLvl(nSide));
    }
    if (kind == 2) {
        TaLogic010_SetSpecialComboQue(nSide, ctx, &work);
        res = TaLogic010_GetSummonPiece(nSide, kind, &work, ret);
        if (res < 0) {
            return -1;
        }
        ctx->unk4 = res;
        return 1;
    }
    if (TaLogic010_GetSpellPlay(nSide, (u8 *)ctx, &work, work.unk3C) < 0) {
        return -1;
    }
    res = TaLogic010_GetSummonPiece(nSide, kind, &work, ret);
    if (res < 0) {
        return -1;
    }
    ctx->unk4 = res;
    return 1;
}

/* Whether side `nSide` should play from its hand this turn (and what, into `pInput`). */
s32 TaLogic010_IsHandPlay(s32 nSide, void *pInput) {
    extern s32 TaLogic_GetUnitNum();
    extern s32 SzDuel_GetUnitCurseRest();
    s32 cards[8];
    u8 work[32];
    u8 status0;
    u8 status1;
    s32 *categoryCard;
    s32 categoryIndex;
    s32 i;
    s32 result;

    status0 = TaLogic_GetUnitNum(nSide, 0);
    status1 = TaLogic_GetUnitNum(nSide, 1);
    if (pInput == NULL) {
        return -1;
    }
    TaHand_GetNextHand(nSide, cards);
    if (status0 == 5) {
        if (TaLogic010_GetSpellPlay(nSide, work, pInput, 999) >= 0) {
            return 1;
        }
        return -1;
    }
    if (status1 == 5) {
        s32 j;
        for (j = 0; j < TaHand_GetNextHandNum(nSide); j++) {
            if ((TaHand_GetCardKind(cards[j]) >> 5) == 0 &&
                TaHand_CanAffordSummonCost(nSide, cards[j]) == 1) {
                SzDuel_InitCardInfo(pInput, cards[j]);
                return 0;
            }
        }
        return -1;
    }
    if (TaLogic010_GetSpecCardPlay(nSide, work, pInput, 0x348) >= 0) {
        if (TaLogic010_IsDoCerem(nSide, 0x348) == 1) {
            return 2;
        }
    }
    if (TaLogic010_GetUseThunderBolt(nSide) >= 0) {
        if (TaLogic010_GetSpecCardPlay(nSide, work, pInput, 0x2BC) >= 0) {
            return 2;
        }
    }
    categoryIndex = 0;
    if (categoryIndex < TaHand_GetNextHandNum(nSide)) {
        categoryCard = cards;
        do {
            if (SzDuel_Kind2Type(TaHand_GetCardKind(*categoryCard) >> 5) == 2) {
                SzDuel_InitCardInfo(pInput, cards[categoryIndex]);
                return 1;
            }
            categoryCard++;
            categoryIndex++;
        } while (categoryIndex < TaHand_GetNextHandNum(nSide));
    }
    for (i = 0; i < 11; i++) {
        if (SzDuel_GetUnitCurseRest(nSide, i) != 0 &&
            TaLogic010_GetSpecCardPlay(nSide, work, pInput, 0x31C) >= 0) {
            return 2;
        }
    }
    for (i = 0; i < TaHand_GetNextHandNum(nSide); i++) {
        if ((TaHand_GetCardKind(cards[i]) >> 5) == 0 &&
            TaHand_CanAffordSummonCost(nSide, cards[i]) == 1) {
            SzDuel_InitCardInfo(pInput, cards[i]);
            return 0;
        }
    }
    result = TaLogic010_GetSpellPlay(nSide, work, pInput, 999);
    if (result >= 0) {
        return result;
    }
    return -1;
}

/* Whether side `nSide` holds card `nCardNo` and can summon it (its slot into `bCombo`, the card into `pCardInfo`);
   returns its kind group or -1. */
s32 TaLogic010_GetSpecCardPlay(s32 nSide, void *bCombo, void *pCardInfo, s32 nCardNo) {
    s32 entries[8];
    s32 i;
    s32 *entry;

    TaHand_GetNextHand(nSide, entries);
    i = 0;
    if (0 < TaHand_GetNextHandNum(nSide)) {
        entry = entries;
        do {
            if ((nCardNo & 0xFFFF) == *entry && TaHand_CanAffordSummonCost(nSide, *entry) == 1) {
                *((u8 *)bCombo + 6) = i;
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
s32 TaLogic010_GetSpellPlay(s32 nSide, u8 *bCombo, void *pCardInfo, s32 nMode) {
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

typedef struct Info_0013B420 {
    u8 pad00[8];
    u16 x;
    s16 y;
} Info_0013B420;

typedef struct Sprite_0013B420 {
    Info_0013B420 *info;
    u8 pad04[0x34];
    s16 x;
    s16 y;
} Sprite_0013B420;

/* Fills hand combination `bCombo` for side `nSide`: the best fusion or equip chain, its card into `pCardInfo`. */
s32 TaLogic010_SetComboQue(s32 nSide, u8 *bCombo, void *pCardInfo) {
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
                            TaLogic_Richard_ConvEmptyCombo(nSide, *node, entries);
                            TaLogic_CopyArray((u8 *)*node + 2, bCombo + 6);
                            SzDuel_InitCardInfo(pCardInfo, **node);
                            ((Sprite_0013B420 *)pCardInfo)->x = (value >> 16) - (((Sprite_0013B420 *)pCardInfo)->info->x & 0x1FFF);
                            ((Sprite_0013B420 *)pCardInfo)->y = (value & 0xFFFF) - (((Sprite_0013B420 *)pCardInfo)->info->y & 0x1FFF);
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
} Info_0013B600;

/* Fills an empty combination: the hand card side `nSide` can summon with the best attack plus defence. */
void TaLogic_Richard_ConvEmptyCombo(s32 nSide, void *pCardInfo, s32 *pResult) {
    Info_0013B600 *info = pCardInfo;
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
                if (card != 0x3E7 && TaLogic010_IsRefuseEmptyCombo(card) == 0 && level >= TaHand_GetCardSummonCost2(card, nSide)) {
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
s32 TaLogic010_IsRefuseEmptyCombo(s32 nCardNo) {
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
} Obj1_0013B840;

typedef struct {
    u8 pad0[0x3C];
    u16 id;
} Obj2_0013B840;

/* Fills hand combination `bCombo` for side `nSide` with this duelist's special combination, its card into
   `pCardInfo`. */
s32 TaLogic010_SetSpecialComboQue(s32 nSide, void *bCombo, void *pCardInfo) {
    Obj1_0013B840 *o1 = bCombo;
    Obj2_0013B840 *o2 = pCardInfo;
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

typedef struct Nibbles_0013BA30 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_0013BA30;

/* The square side `nSide` summons a card of kind `sKind` to. */
s32 TaLogic010_GetSummonPiece(s32 nSide, u8 sKind, void *pInput, s32 nMode) {
    extern s32 TaLogic_IsUnitWin4();
    extern s32 TaLogic_GetInvadeRoot2(s32, s32, s32, s32, s32, s32, s32, s32, u8, u16);
    extern s32 TaLogic_GetRoot2(s32, s32, s32, s32, s32, s32, u16, u8);
    s32 bestPosition;
    s32 bestScore;
    Nibbles_0013BA30 path[12];
    s32 transformedY;
    s32 transformedX;
    s32 value;
    u8 mode;

    if (pInput == NULL) {
        return -1;
    }
    {
    s32 initIndex;
    Nibbles_0013BA30 *p;
    p = path;
    initIndex = 0;
    do {
        p->low = p->high = 15;
        p++;
        initIndex++;
    } while (initIndex < 12);
    }
    mode = *((u8 *)pInput + 0x3E) >> 5;
    if (mode == 0) {
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
                        if (TaLogic_IsUnitWin4((s32)pInput, nMode, TaLogic_Richard_GetWarnHideLvl(nSide),
                                         transformedX, transformedY, 0) > 0) {
                            score = TaLogic_GetInvadeRoot2((s32)pInput, (s32)path,
                                                       candidateX, candidateY,
                                                       transformedX, transformedY,
                                                       nMode, 0, 2,
                                                       TaLogic_Richard_GetWarnHideLvl(nSide));
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
        }
        {
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
                    value = TaLogic010_GetEmptyLine(nSide);
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
        nMode = -1;
        return nMode;
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
    best = -1;
    return best;
    }
}

typedef struct Nibbles_0013BE60 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_0013BE60;

typedef struct Output_0013BE60 {
    u16 position;
    u8 action;
    u8 pad3;
    u16 destination;
    u8 pad6[6];
    s32 special;
    u8 result;
} Output_0013BE60;

/* The task of a unit running from danger (task `pTask`): the safest square in reach, into `pInput` (`fFirst` = 1
   for the unit's first-choice task). */
s32 TaLogic_Richard_GetMinimumTask_RunMission(UnitTask *pTask, s32 nSide, void *pInput, u8 fFirst) {
    Output_0013BE60 *output = pInput;
    s32 target;
    u8 endX;
    u8 extra;
    Nibbles_0013BE60 nibbles[12];
    s32 bestScore;
    s32 best;
    s32 i;
    Nibbles_0013BE60 *p;
    extern s32 TaLogic_Richard_IsOpenUnit();
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

        initialScore = TaLogic_Richard_GetWarnHideLvl(nSide);
        centerX = target & 0xFF;
        centerY = target >> 8;
        if (TaLogic_GetUnitWarning(centerX, centerY, pTask->ownerId, 2, initialScore, 0) == 0) {
            output->position = pTask->ownerId;
            output->action = 6;
            output->destination = target;
            output->result = TaLogic_IsDefStyleUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, output->destination, 1, 0);
            output->special = TaLogic_Richard_IsOpenUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, pTask);
            TaLogic_InitRogicControl(pTask, fFirst);
            return 0;
        }
        if ((range = GetMoveRange(SzDuel_GetUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF), centerX, centerY)) == 0) {
            output->position = pTask->ownerId;
            output->action = 6;
            output->destination = target;
            output->result = TaLogic_IsDefStyleUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, output->destination, 1, 0);
            output->special = TaLogic_Richard_IsOpenUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, pTask);
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
                        candidateScore = TaLogic_GetUnitWarning(x, y, pTask->ownerId, 2, (u16)TaLogic_Richard_GetWarnHideLvl(nSide), 0);
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
            output->special = TaLogic_Richard_IsOpenUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, pTask);
        } else {
            output->position = pTask->ownerId;
            output->action = 6;
            output->destination = target;
            output->result = TaLogic_IsDefStyleUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, output->destination, 1, 0);
            output->special = TaLogic_Richard_IsOpenUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, pTask);
        }
        TaLogic_InitRogicControl(pTask, fFirst);
        return 0;
    }
}

typedef struct Coord_0013C430 {
    u8 x : 4;
    u8 y : 4;
} Coord_0013C430;

typedef struct Input_0013C430 {
    u16 position;
    u8 pad02[6];
    u32 destination;
} Input_0013C430;

typedef struct Output_0013C430 {
    u16 position;
    u8 action;
    u8 pad03;
    u16 destination;
    u8 pad06[6];
    s32 flag;
    u8 result;
} Output_0013C430;

/* The task's target square: the second half-word when the second argument is 1, else the first. */
static inline u32 destination_0013C430(void *src, s32 mode) {
    if (mode == 1) {
        return (u16)(((Input_0013C430 *)src)->destination >> 16);
    }
    return *(u16 *)((u8 *)src + 8);
}

/* Whether the first square is nearer to (x, y) than the second. */
static inline s32 closer_0013C430(Coord_0013C430 *current, Coord_0013C430 *best, s32 x, s32 y) {
    s32 bestLowY = best->y < y ? best->y : y;
    s32 bestHighY = MaxSel(best->y, y);
    s32 bestLowX = best->x < x ? best->x : x;
    s32 bestHighX = MaxSel(best->x, x);
    s32 nextLowY = current->y < y ? current->y : y;
    s32 nextHighY = MaxSel(current->y, y);
    s32 nextLowX = current->x < x ? current->x : x;
    s32 nextHighX = MaxSel(current->x, x);
    return (nextHighX - nextLowX) + (nextHighY - nextLowY) <
           (bestHighX - bestLowX) + (bestHighY - bestLowY);
}

/* The task of a unit attacking (task `pTask`): its path to the goal, into `pInput`; -1 when it has none (`fFirst`
   = 1 for the unit's first-choice task). */
s32 TaLogic_Richard_GetMinimumTask_AtkMission(void *pTask, s32 nSide, void *pInput, u8 fFirst) {
    extern s32 TaLogic_Richard_IsOpenUnit();
    extern void TaLogic_GetInvadeRoot();
    s32 source;
    s32 count;
    s32 sourceY;
    s32 sourceX;
    s32 flag;
    Coord_0013C430 points[12];
    s32 packedDestination;
    s32 originalFlag;
    s32 selected;
    Input_0013C430 *input = pTask;
    Output_0013C430 *output = pInput;

    {
    u32 low = destination_0013C430(pTask, fFirst);
    u32 high = destination_0013C430(pTask, fFirst);
    if (SzDuel_GetUnit(high >> 8, low & 0xFF) == 0) {
        TaLogic_InitRogicControl(pTask, 1);
        return -1;
    } else {
    originalFlag = TaLogic_Richard_IsOpenUnit(input->position >> 8, input->position & 0xFF, pTask);
    source = SzDuel_GetUnitLoc(input->position >> 8, input->position & 0xFF);
    {
        u32 low = destination_0013C430(pTask, fFirst);
        u32 high = destination_0013C430(pTask, fFirst);
        packedDestination = SzDuel_GetUnitLoc(high >> 8, low & 0xFF);
    }
    {
        s32 j = 0;
        Coord_0013C430 *iter = points;
        do {
            iter->x = iter->y = 0xF;
            iter++;
            j++;
        } while (j < 12);
    }
    {
    s32 owner = SzDuel_GetUnit(input->position >> 8, input->position & 0xFF);
    sourceX = source & 0xFF;
    sourceY = source >> 8;
    if (GetMoveRange(owner, sourceX, sourceY) == 0) {
        s32 pathCost;
        output->position = input->position;
        output->action = 6;
        output->destination = source;
        pathCost = TaLogic_GetUnitWarning(sourceX, sourceY, nSide, 2, 0, (u8)TaLogic_Richard_GetWarnHideLvl(nSide));
        if (pathCost >= SzDuel_GetUnitAP(input->position >> 8, input->position & 0xFF, 0)) {
            output->result = TaLogic_IsDefStyleUnit(input->position >> 8, input->position & 0xFF,
                                          output->destination, 1, 0);
        } else {
            output->result = TaLogic_IsDefStyleUnit(input->position >> 8, input->position & 0xFF,
                                          output->destination, 0, 0);
        }
        TaLogic_InitRogicControl(pTask, fFirst);
    } else {
        s32 position = input->position;
        s32 destinationX;
        Coord_0013C430 *point;
        s32 i;
        s32 score;
        u16 limit;
        s32 positionY;
        s32 positionX;

        limit = (u16)TaLogic_Richard_GetWarnHideLvl(nSide);
        positionY = position >> 8;
        positionX = position & 0xFF;
        destinationX = packedDestination & 0xFF;
        TaLogic_GetInvadeRoot(positionY, positionX, points, sourceX, sourceY,
                      destinationX, packedDestination >>= 8, destination_0013C430(pTask, fFirst),
                      0, 30, limit);
        count = TaLogic_GetMinGoalCount((u8 *)points);
        selected = 0xFF;
        if (count > 0) {
            flag = 0;
            score = 0xFFFF;
            for (i = 0; i < count; i++) {
                if (TaLogic010_IsOpenMoveUnit(input->position >> 8, input->position & 0xFF,
                                  sourceX, sourceY, destinationX, packedDestination) == 1) {
                    selected = i;
                    flag = 1;
                    points[i].x = destinationX;
                    points[i].y = packedDestination;
                    i = count;
                } else {
                    s32 candidate;
                    point = &points[i];
                    candidate = TaLogic_GetUnitWarning(point->x, point->y, nSide, 2, 0,
                                              (u8)TaLogic_Richard_GetWarnHideLvl(nSide));
                    if (candidate < score) {
                        score = candidate;
                        selected = i;
                    } else if (candidate == score) {
                        if (closer_0013C430(point, &points[selected], destinationX, packedDestination)) {
                            score = candidate;
                            selected = i;
                        }
                    }
                }
            }
        } else {
            output->position = input->position;
            output->action = 6;
            output->destination = source;
            output->flag = originalFlag;
            output->result = TaLogic_IsDefStyleUnit(input->position >> 8, input->position & 0xFF,
                                          output->destination, 0, 0);
            TaLogic_InitRogicControl(pTask, fFirst);
            return 0;
        }
            if (selected != 0xFF) {
                output->position = input->position;
                output->action = 6;
                output->destination = (points[selected].y << 8) | points[selected].x;
                output->flag = flag;
                output->result = TaLogic_IsDefStyleUnit(input->position >> 8, input->position & 0xFF,
                                              output->destination, 0, 0);
            } else {
                output->position = input->position;
                output->action = 6;
                output->destination = source;
                output->flag = flag;
                output->result = TaLogic_IsDefStyleUnit(input->position >> 8, input->position & 0xFF,
                                              output->destination, 0, 0);
                TaLogic_InitRogicControl(pTask, fFirst);
                return 0;
            }
    }
    }
    }
    }
    return 0;
}

typedef struct Coord_0013CA10 {
    u8 x : 4;
    u8 y : 4;
} Coord_0013CA10;

typedef struct Output_0013CA10 {
    u16 position;
    u8 kind;
    u8 pad3;
    u16 target;
    u8 pad6[6];
    s32 value;
    u8 flag;
} Output_0013CA10;

/* The task's target square: the second half-word when the second argument is 1, else the first. */
static inline u32 target_0013CA10(void *unit, s32 side) {
    return side == 1 ? (u32)(u16)(((UnitTask *)unit)->goal.dwGoal >> 16) : (u32)((UnitTask *)unit)->goal.wGoal[0];
}

/* The smaller of the two values. */
static inline u32 minY_0013CA10(void *unit, s32 side, u8 coord) {
    return coord < (target_0013CA10(unit, side) >> 8) ? coord : (target_0013CA10(unit, side) >> 8);
}

/* The larger of the two values. */
static inline u32 maxY_0013CA10(void *unit, s32 side, u8 coord) {
    return (target_0013CA10(unit, side) >> 8) < coord ? coord : (target_0013CA10(unit, side) >> 8);
}

/* The smaller of the two values. */
static inline u32 minX_0013CA10(void *unit, s32 side, u8 coord) {
    return coord < (target_0013CA10(unit, side) & 0xFF) ? coord : (target_0013CA10(unit, side) & 0xFF);
}

/* The larger of the two values. */
static inline u32 maxX_0013CA10(void *unit, s32 side, u8 coord) {
    return (target_0013CA10(unit, side) & 0xFF) < coord ? coord : (target_0013CA10(unit, side) & 0xFF);
}

/* The task of a unit moving to its goal (task `pTask`), into `pInput` (`fFirst` = 1 for the unit's first-choice
   task). */
s32 TaLogic_Richard_GetMinimumTask_MoveMission(void *pTask, s32 nSide, void *pInput, u8 fFirst, u8 nKind) {
    extern s32 TaLogic_Richard_IsOpenUnit();
    extern s32 TaLogic_GetUnitWarning();
    extern void TaLogic_GetRoot();
    extern s32 TaLogic_IsDefStyleUnit(s32, s32, s32, u8, s32);
    Coord_0013CA10 coords[12];
    s32 initial;
    s32 cell;
    s32 count;

    initial = SzDuel_GetUnitLoc(((UnitTask *)pTask)->ownerId >> 8, ((UnitTask *)pTask)->ownerId & 0xFF);
    {
    s32 bestScore;
    s32 best;
    s32 side = fFirst;
    Coord_0013CA10 *candidate;
    s32 index;
    if (target_0013CA10(pTask, side) == 0xFFFF) {
        if (initial == target_0013CA10(pTask, side)) {
            ((Output_0013CA10 *)pInput)->position = ((UnitTask *)pTask)->ownerId;
            ((Output_0013CA10 *)pInput)->kind = 6;
            ((Output_0013CA10 *)pInput)->target = initial;
            ((Output_0013CA10 *)pInput)->flag = TaLogic_IsDefStyleUnit(((UnitTask *)pTask)->ownerId >> 8, ((UnitTask *)pTask)->ownerId & 0xFF, ((Output_0013CA10 *)pInput)->target, nKind, 0);
            ((Output_0013CA10 *)pInput)->value = TaLogic_Richard_IsOpenUnit(((UnitTask *)pTask)->ownerId >> 8, ((UnitTask *)pTask)->ownerId & 0xFF, pTask);
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
            ((Output_0013CA10 *)pInput)->position = ((UnitTask *)pTask)->ownerId;
            ((Output_0013CA10 *)pInput)->kind = 14;
            return 0;
        }
    }

    candidate = coords;
    {
        s32 i = 0;
        Coord_0013CA10 *entry = candidate;
        do {
            entry->x = entry->y = 0xF;
            i++;
            entry++;
        } while (i < 12);
    }

    cell = SzDuel_GetMapUnitID(target_0013CA10(pTask, side) & 0xFF, ((u32)target_0013CA10(pTask, side)) >> 8);
    if (cell < 0) {
        cell = 0xFFFF;
    }
    TaLogic_GetRoot(((UnitTask *)pTask)->ownerId >> 8, ((UnitTask *)pTask)->ownerId & 0xFF,
                 coords, initial & 0xFF, initial >> 8, target_0013CA10(pTask, side) & 0xFF,
                 ((u32)target_0013CA10(pTask, side)) >> 8, (u16)cell, 7);
    count = TaLogic_GetMinGoalCount((u8 *)coords);
    {
        if (count > 0) {
        best = 0xFF;
        bestScore = 0xFFFF;
        for (index = 0; index < count; index++) {
                if (SzDuel_GetMapUnit(candidate->x, candidate->y) == 0) {
                    s32 score = TaLogic_GetUnitWarning(candidate->x, candidate->y, nSide, 2, 0, (u8)TaLogic_Richard_GetWarnHideLvl(nSide));
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
                        bestMinY = minY_0013CA10(pTask, side, bestY);
                        bestMaxY = maxY_0013CA10(pTask, side, bestY);
                        bestX = (&coords[best])->x;
                        bestMinX = minX_0013CA10(pTask, side, bestX);
                        bestMaxX = maxX_0013CA10(pTask, side, bestX);
                        currentY = (u8)candidate->y;
                        currentMinY = minY_0013CA10(pTask, side, currentY);
                        currentMaxY = maxY_0013CA10(pTask, side, currentY);
                        currentX = candidate->x;
                        currentMinX = minX_0013CA10(pTask, side, currentX);
                        currentMaxX = maxX_0013CA10(pTask, side, currentX);
                        if ((currentMaxX - currentMinX) + (currentMaxY - currentMinY) < (bestMaxX - bestMinX) + (bestMaxY - bestMinY)) {
                            bestScore = score;
                            best = index;
                        }
                    }
                }
            candidate++;
        }
    } else {
        ((Output_0013CA10 *)pInput)->position = ((UnitTask *)pTask)->ownerId;
            ((Output_0013CA10 *)pInput)->kind = 6;
            ((Output_0013CA10 *)pInput)->target = initial;
            ((Output_0013CA10 *)pInput)->flag = TaLogic_IsDefStyleUnit(((UnitTask *)pTask)->ownerId >> 8, ((UnitTask *)pTask)->ownerId & 0xFF, ((Output_0013CA10 *)pInput)->target, nKind, 0);
            ((Output_0013CA10 *)pInput)->value = TaLogic_Richard_IsOpenUnit(((UnitTask *)pTask)->ownerId >> 8, ((UnitTask *)pTask)->ownerId & 0xFF, pTask);
        TaLogic_InitRogicControl(pTask, fFirst);
        return 0;
    }

        if (best != 0xFF) {
            ((Output_0013CA10 *)pInput)->position = ((UnitTask *)pTask)->ownerId;
            ((Output_0013CA10 *)pInput)->kind = 6;
            ((Output_0013CA10 *)pInput)->target = (coords[best].y << 8) | coords[best].x;
            ((Output_0013CA10 *)pInput)->flag = TaLogic_IsDefStyleUnit(((UnitTask *)pTask)->ownerId >> 8, ((UnitTask *)pTask)->ownerId & 0xFF, ((Output_0013CA10 *)pInput)->target, nKind, 0);
            ((Output_0013CA10 *)pInput)->value = TaLogic_Richard_IsOpenUnit(((UnitTask *)pTask)->ownerId >> 8, ((UnitTask *)pTask)->ownerId & 0xFF, pTask);
        } else {
            ((Output_0013CA10 *)pInput)->position = ((UnitTask *)pTask)->ownerId;
            ((Output_0013CA10 *)pInput)->kind = 6;
            ((Output_0013CA10 *)pInput)->target = initial;
            ((Output_0013CA10 *)pInput)->flag = TaLogic_IsDefStyleUnit(((UnitTask *)pTask)->ownerId >> 8, ((UnitTask *)pTask)->ownerId & 0xFF, ((Output_0013CA10 *)pInput)->target, nKind, 0);
            ((Output_0013CA10 *)pInput)->value = TaLogic_Richard_IsOpenUnit(((UnitTask *)pTask)->ownerId >> 8, ((UnitTask *)pTask)->ownerId & 0xFF, pTask);
        }
        TaLogic_InitRogicControl(pTask, fFirst);
    }
    }
    return 0;
}

/* Whether this duelist plays in its attacking mode this turn. */
s32 TaLogic010_IsActiveMode(void) {
    if (TaLogic010_GetEmptyLine(SzDuel_GetTurnOwner()) < 0) {
        return 1;
    }
    return 0;
}

/* The opponent's strongest unit when it beats side `nSide`'s strongest (a Thunderbolt target), or -1. */
s32 TaLogic010_GetUseThunderBolt(s32 nSide) {
    u16 buf[0x16];
    s32 i;
    s32 a;
    s32 b;
    s32 r;

    for (i = 0; i < 0x16; i++) {
        buf[i] = 0xFFFF;
    }
    TaLogic_GetUnitCtlLst2(nSide == 0 ? 1 : 0, buf, 0x1D, 0, 0);
    a = TaLogic_GetMaxApUnit(buf);
    for (i = 0; i < 0x16; i++) {
        buf[i] = 0xFFFF;
    }
    TaLogic_GetUnitCtlLst(nSide, buf, 0x1D, 1);
    b = TaLogic_GetMaxApUnit(buf);
    if (a >= 0) {
        if (b >= 0) {
            r = SzDuel_GetUnitLoc(a >> 8, a & 0xFF);
            if (TaLogic_IsUnitWin(a, b, r & 0xFF, r >> 8) > 0) {
                return a;
            }
        }
    }
    return -1;
}

/* Whether this duelist opens (turns face up) unit (nSide, nID) now: 0 no, 1 or 2 by its kind. */
s32 TaLogic_Richard_IsOpenUnit(s32 nSide, s32 nID) {
    extern s32 SzDuel_GetUnitCardNo();
    s32 card;
    s32 owner;
    s32 position;
    u8 count;
    s32 slot;
    s32 other;
    s32 otherPosition;

    card = SzDuel_GetUnitCardNo(nSide, nID);
    owner = Ta_IsUnitControl(nSide, nID);
    position = SzDuel_GetUnitLoc(nSide, nID);
    SzDuel_GetUnitEffect(nSide, nID, 0);
    count = 0;
    if (SzDuel_GetUnitStatus(nSide, nID, 4) != 0) {
        return 0;
    }
    switch (SzDuel_GetUnitKind(nSide, nID) >> 5) {
    case 0:
        switch (card) {
        case 0xC5:
            slot = 1;
            while (1) {
                if (SzDuel_GetUnitCardNo(nSide, slot) == 0x99) {
                    if (nSide == Ta_IsUnitControl(nSide, slot)) {
                        count++;
                    }
                }
                if (SzDuel_GetUnitCardNo(nSide == 0 ? 1 : 0, slot) == 0x99) {
                    if (nSide == Ta_IsUnitControl(nSide == 0 ? 1 : 0, slot)) {
                        count++;
                    }
                }
                slot++;
                if (slot > 5) {
                    break;
                }
            }
            if (count >= 2) {
                return 1;
            }
            break;
        case 0x99:
            slot = 1;
            while (1) {
                if (SzDuel_GetUnitCardNo(nSide, slot) == 0xC5) {
                    if (nSide == Ta_IsUnitControl(nSide, slot)) {
                        count++;
                    }
                }
                if (SzDuel_GetUnitCardNo(nSide == 0 ? 1 : 0, slot) == 0xC5) {
                    if (nSide == Ta_IsUnitControl(nSide == 0 ? 1 : 0, slot)) {
                        count++;
                    }
                }
                slot++;
                if (slot > 5) {
                    break;
                }
            }
            if (count >= 2) {
                return 1;
            }
            break;
        case 0xAA:
            slot = 1;
            while (1) {
                if (SzDuel_GetUnitCardNo(nSide, slot) == 0xAB) {
                    if (nSide == Ta_IsUnitControl(nSide, slot)) {
                        count++;
                    }
                }
                if (SzDuel_GetUnitCardNo(nSide == 0 ? 1 : 0, slot) == 0xAB) {
                    if (nSide == Ta_IsUnitControl(nSide == 0 ? 1 : 0, slot)) {
                        count++;
                    }
                }
                slot++;
                if (slot > 5) {
                    break;
                }
            }
            if (count >= 2) {
                return 1;
            }
            break;
        case 0xAB:
            slot = 1;
            while (1) {
                if (SzDuel_GetUnitCardNo(nSide, slot) == 0xAA) {
                    if (nSide == Ta_IsUnitControl(nSide, slot)) {
                        count++;
                    }
                }
                if (SzDuel_GetUnitCardNo(nSide == 0 ? 1 : 0, slot) == 0xAA) {
                    if (nSide == Ta_IsUnitControl(nSide == 0 ? 1 : 0, slot)) {
                        count++;
                    }
                }
                slot++;
                if (slot > 5) {
                    break;
                }
            }
            if (count >= 2) {
                return 1;
            }
            break;
        }
        return 2;
    case 5:
        if (TaLogic_GetActionReaction(nSide, nID, 0, 0, 6, 0) == 5) {
            return 2;
        }
        if (TaLogic010_IsDoCerem(Ta_IsUnitControl(nSide, nID), card) == 1) {
            if (SzDuel_GetField(position & 0xFF, position >> 8) != 9) {
                return 1;
            }
        }
        break;
    case 1:
        if (TaLogic_GetActionReaction(nSide, nID, 0, 0, 6, 0) == 5) {
            return 2;
        }
        other = TaLogic010_GetUseThunderBolt(owner);
        otherPosition = SzDuel_GetUnitLoc(other >> 8, other & 0xFF);
        if ((position & 0xFF) == (otherPosition & 0xFF) ||
            (position >> 8) == (otherPosition >> 8)) {
            return 1;
        }
        break;
    default:
        return 2;
    }
    return 2;
}

/* Whether unit (nSide, nID) may open while moving from (nX, nZ) to the square next to it, (gX, gZ). */
s32 TaLogic010_IsOpenMoveUnit(s32 nSide, s32 nID, s32 nX, s32 nZ, s32 gX, s32 gZ) {
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
        return CheckLandAgreement2(SzDuel_GetField(nX, nZ), nSide, nID) != 1 ? 0 : 1;
    }
    return 0;
}

/* Whether side `nSide` can play ritual card `nCardNo` now (it has the units to give up). */
s32 TaLogic010_IsDoCerem(s32 nSide, s32 nCardNo) {
    s32 sp50[4];
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
            if (TaUtil_GetUnitAP(unitSide, unitSlot, loc & 0xFF, loc >> 8) >= 0xBB8) {
                return 0;
            }
            i++;
        } while (i < Ta_GetUnitNumFrom22bitFlagList(temp_v0));
    }
    return 1;
}

/* How careful this duelist is about hidden cards (by its life points and monster count). */
s32 TaLogic_Richard_GetWarnHideLvl(s32 nSide) {
    if (SzDuel_GetLP(nSide) > 1000) {
        if (SzDuel_GetUnitMonsterCount(nSide) >= 5) {
            return 0;
        }
        return 0;
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
} Req_0013DAD0;

typedef struct {
    u8 pad0[0x160];
    u16 list[32];    /* 0x160 */
    u8 idx : 5;      /* 0x1A0 */
    u8 pad1A0 : 3;
    u8 pad1A1;
    u16 count;       /* 0x1A2 */
} Work_0013DAD0;

s32 TaLogic_GetInputQueFromMinimumTask_b(void *, void *, s32);

/* Computer duelist 10's controller (duelistControllers[10]): the buttons it presses this frame. With an empty
   input queue it plans its next task and turns it into buttons, then plays the queue back one button per frame;
   after 600 frames it gives up the turn (0x20, then 0x800). */
s32 duelistController10(s32 wCursorPos, void *pCtl) {
    Req_0013DAD0 req;
    Work_0013DAD0 *w;
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
        if (TaLogic_Richard_GetMinimumTask(w, &req, wCursorPos) == 0) {
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

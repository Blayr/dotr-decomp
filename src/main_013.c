#include "common.h"

/* How careful this duelist is about hidden cards (by its life points and monster count). */
s32 TaLogic_GetWarnHideLvl_00153ED0(s32 nSide) {
    if (SzDuel_GetLP(nSide) > 1200) {
        if (SzDuel_GetUnitMonsterCount(nSide) >= 4) {
            return 500;
        } else {
            return 1000;
        }
    } else {
        return 1500;
    }
}

typedef struct Entry_00153F30 {
    u8 *data;
    u8 rest[0x5C];
} Entry_00153F30;

/* Whether side `nSide` should use a revive card now. */
s32 TaLogic015_IsUseRevive(s32 nSide) {
    extern s32 SzDuel_GetGraveCount(s32);
    s32 i;
    s32 bestScore;
    s32 result;
    s32 card;
    Entry_00153F30 entry;
    u32 *effect;
    u8 score;

    bestScore = 0x28;
    result = -1;
    if (SzDuel_GetUnitSpellCount(nSide) >= 5) {
        return result;
    }

    for (i = 0; i < SzDuel_GetGraveCount(nSide == 0 ? 1 : 0); i++) {
        card = SzDuel_InqGrave(nSide == 0 ? 1 : 0, i);
        if ((TaHand_GetCardKind(card) >> 5) != 0) {
            SzDuel_InitCardInfo(&entry, card);
            effect = (u32 *)SzDuel_GetUnitConstEffect2(&entry, 0);
            score = entry.data[3];
            if (score >= bestScore && (*effect >> 8) != 0x14) {
                bestScore = score;
                result = i | ((nSide == 0 ? 1 : 0) << 16);
            }
        }
    }
    return result;
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
} Req_00154040;

typedef struct {
    u8 pad0[0x160];
    u16 list[32];    /* 0x160 */
    u8 idx : 5;      /* 0x1A0 */
    u8 pad1A0 : 3;
    u8 pad1A1;
    u16 count;       /* 0x1A2 */
} Work_00154040;

s32 TaLogic_GetInputQueFromMinimumTask_b(void *, void *, s32);

/* Computer duelist 15's controller (duelistControllers[15]): the buttons it presses this frame. With an empty
   input queue it plans its next task and turns it into buttons, then plays the queue back one button per frame;
   after 600 frames it gives up the turn (0x20, then 0x800). */
s32 duelistController15(s32 wCursorPos, void *pCtl) {
    Req_00154040 req;
    Work_00154040 *w;
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
        if (TaLogic_GetMinimumTask_0014FD40(w, &req, wCursorPos) == 0) {
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

/* Computer duelist 16's controller (duelistControllers[16]): the default controller. */
void duelistController16(void) {
    extern s32 duelistControllerDefault();

    duelistControllerDefault();
}

#pragma conditional_move off

/* This duelist's move: picks the next unit to act, gives it a task and turns that into input `pInput`; returns 1
   when it set one. */
s32 TaLogic_GetMinimumTask_00154220(void *pCtl, void *pInput, s32 wCursorPos) {
    u16 *tasks = pCtl;
    s32 side;
    s32 found;
    s32 result;
    s32 index;

    side = SzDuel_GetTurnOwner();
    found = 0;
    if ((result = TaLogic_GetNextActiveUnit_00154AD0(tasks, side, (s32)pInput)) < 0) {
        return 0;
    }
    index = TaLogic_GetActionUnitFromOwnerID(tasks, result & 0xFFFF);
    if (index < 0) {
        return 0;
    }
    if ((result >> 16) == 1) {
        if (((tasks[index * 8 + 2] >> 8) & 0xFF) == 10) {
            TaLogic_InitRogicControl(tasks + index * 8, 1);
        } else {
            TaLogic_InitRogicControl(tasks + index * 8, 0);
        }
        return 1;
    }
    TaLogic_CommandUnit_001547A0(tasks + index * 8);
    switch ((tasks[index * 8 + 2] >> 8) & 0xFF) {
    case 2:
        if (SzDuel_GetUnitStatus(tasks[index * 8] >> 8, tasks[index * 8] & 0xFF, 0) == 0) {
            if (TaLogic_GetMinimumTask_AtkMission_00156FC0(tasks + index * 8, side, pInput, 1) < 0) {
                TaLogic_InitRogicControl(tasks + index * 8, 1);
                return 1;
            }
            found = 1;
        }
        break;
    case 5:
        if (SzDuel_GetUnitStatus(tasks[index * 8] >> 8, tasks[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_RunMission_00157480(tasks + index * 8, side, pInput, 1);
            found = 1;
        }
        break;
    case 10:
        if (TaLogic_GetMinimumTask_Summon_00155770(tasks[index * 8], side, (s32)pInput) < 0) {
            TaLogic_InitRogicControl(tasks + index * 8, 1);
            *(u8 *)((u8 *)pInput + 2) = 0xFF;
            *(s32 *)((u8 *)pInput + 0xC) = 0;
        } else {
            TaLogic_InitRogicControl(tasks + index * 8, 1);
            found = 1;
        }
        break;
    case 6:
        if (SzDuel_GetUnitStatus(tasks[index * 8] >> 8, tasks[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_MoveMission_00157A50(tasks + index * 8, side, pInput, 1, 0, 0);
            found = 1;
        }
        break;
    case 7:
        if (SzDuel_GetUnitStatus(tasks[index * 8] >> 8, tasks[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_MoveMission_00157A50(tasks + index * 8, side, pInput, 1, 0, 1);
            found = 1;
        }
        break;
    case 3:
        if (SzDuel_GetUnitStatus(tasks[index * 8] >> 8, tasks[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_MoveMission_00157A50(tasks + index * 8, side, pInput, 1, 1, 0);
            found = 1;
        }
        break;
    case 9:
        TaLogic_GetMinimumTask_EncMission(tasks + index * 8, side, pInput, 1, 0, TaLogic_GetWarnHideLvl_00158780(side), 5, 1);
        found = 1;
        break;
    case 14:
        TaLogic_GetMinimumTask_DoNone(tasks + index * 8, side, pInput);
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
    switch (tasks[index * 8 + 2] & 0xFF) {
    case 2:
        if (SzDuel_GetUnitStatus(tasks[index * 8] >> 8, tasks[index * 8] & 0xFF, 0) == 0) {
            if (TaLogic_GetMinimumTask_AtkMission_00156FC0(tasks + index * 8, side, pInput, 0) < 0) {
                TaLogic_GetMinimumTask_RunMission_00157480(tasks + index * 8, side, pInput, 0);
            }
            found = 1;
        }
        break;
    case 5:
        if (SzDuel_GetUnitStatus(tasks[index * 8] >> 8, tasks[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_RunMission_00157480(tasks + index * 8, side, pInput, 0);
            found = 1;
        }
        break;
    case 10:
        if (TaLogic_GetMinimumTask_Summon_00155770(tasks[index * 8], side, (s32)pInput) < 0) {
            TaLogic_InitRogicControl(tasks + index * 8, 0);
            *(u8 *)((u8 *)pInput + 2) = 0xFF;
            found = 1;
            *(s32 *)((u8 *)pInput + 0xC) = 0;
        } else {
            TaLogic_InitRogicControl(tasks + index * 8, 0);
            found = 1;
        }
        break;
    case 6:
        if (SzDuel_GetUnitStatus(tasks[index * 8] >> 8, tasks[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_MoveMission_00157A50(tasks + index * 8, side, pInput, 0, 0, 0);
            found = 1;
        }
        break;
    case 7:
        if (SzDuel_GetUnitStatus(tasks[index * 8] >> 8, tasks[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_MoveMission_00157A50(tasks + index * 8, side, pInput, 0, 0, 1);
            found = 1;
        }
        break;
    case 3:
        if (SzDuel_GetUnitStatus(tasks[index * 8] >> 8, tasks[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_MoveMission_00157A50(tasks + index * 8, side, pInput, 0, 1, 0);
            found = 1;
        }
        break;
    case 9:
        TaLogic_GetMinimumTask_EncMission(tasks + index * 8, side, pInput, 0, 0, TaLogic_GetWarnHideLvl_00158780(side), 5, 1);
        found = 1;
        break;
    case 14:
        TaLogic_GetMinimumTask_DoNone(tasks + index * 8, side, pInput);
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

typedef struct State_001547A0 {
    u16 id;
    u16 pad2;
    u16 action;
    u16 pad6;
    union {
        s32 all;
        struct {
            u16 lo;
            u16 hi;
        } h;
    } data;
} State_001547A0;


/* Gives a unit of this duelist its order for this turn (attack, run, move, summon, guard). */
s32 TaLogic_CommandUnit_001547A0(void *pCtl) {
    extern s32 SzDuel_GetUnitCardNo();
    State_001547A0 *state = pCtl;
    s32 card;
    s32 other;

    SzDuel_GetUnitLoc((s32)state->id >> 8, state->id & 0xFF);
    card = Ta_IsUnitControl((s32)state->id >> 8, state->id & 0xFF);
    if (SzDuel_GetUnit((s32)state->id >> 8, state->id & 0xFF) != 0) {
        if (SzDuel_GetUnitStatus((s32)state->id >> 8, state->id & 0xFF, 0) == 0) {
            if (state->id != 0xFFFF) {
                if ((state->id & 0xFF) == 0) {
                    if (state->data.all == -1) {
                        if (TaLogic_IsAttackedNow((s32)state->id >> 8, state->id & 0xFF, 0) == 1) {
                            if (SzDuel_InqHandPhase((s32)state->id >> 8) == 1) {
                                state->action = 0x50A;
                            } else {
                                state->action = 0x5FF;
                            }
                        } else {
                            if ((other = SzDuel_GetMapUnitID(3, 5)) < 0) {
                                if (SzDuel_InqHandPhase((s32)state->id >> 8) == 1) {
                                    state->action = 0xA06;
                                    state->data.all = (state->data.all & 0xFFFF0000) | 0x403;
                                } else {
                                    state->action = 0x6FF;
                                    state->data.all = (u16)state->data.all | 0x04030000;
                                }
                            } else {
                                if (SzDuel_GetUnitLoc((s32)state->id >> 8, state->id & 0xFF) == 0x403 &&
                                    card == Ta_IsUnitControl(other >> 8, other & 0xFF) && other != state->id) {
                                    if (SzDuel_InqHandPhase((s32)state->id >> 8) == 1) {
                                        state->action = 0x20A;
                                        state->data.all = (other << 16) | state->data.h.lo;
                                    } else {
                                        state->action = 0x2FF;
                                        state->data.all = (other << 16) | state->data.h.lo;
                                    }
                                } else {
                                    if (SzDuel_InqHandPhase((s32)state->id >> 8) == 1) {
                                        state->action = 0xA06;
                                        state->data.all = (state->data.all & 0xFFFF0000) | 0x403;
                                    } else {
                                        state->action = 0x6FF;
                                        state->data.all = (u16)state->data.all | 0x04030000;
                                    }
                                }
                            }
                        }
                    }
                } else {
                    other = SzDuel_GetUnitKind((s32)state->id >> 8, state->id & 0xFF);
                    card = SzDuel_GetUnitCardNo((s32)state->id >> 8, state->id & 0xFF);
                    switch (other >> 5) {
                    case 0:
                        if (TaUtil_IsExMonster((s32)state->id >> 8, state->id & 0xFF) == 1 ||
                            TaLogic017_IsExzParts(card) == 1) {
                            TaLogic017_CommandEfcMonster(pCtl);
                        } else {
                            TaLogic017_CommandBtlUnit(pCtl);
                        }
                        break;
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                        TaLogic017_CommandSpellUnit(pCtl);
                        break;
                    default:
                        state->action = 0x5FF;
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
s32 TaLogic_GetNextActiveUnit_00154AD0(u16 *pCtl, s32 nSide, s32 pInput) {
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
    TaLogic_CommandUnit_001547A0(pCtl + idx * 8);
    if (((pCtl[idx * 8 + 2] >> 8) & 0xFF) == 10) {
        if (SzDuel_InqHandPhase(nSide) == 1 && TaLogic_GetMinimumTask_Summon_00155770(pos, nSide, pInput) >= 0) {
            return pos | 0x10000;
        }
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_GetUnitStatus(nSide, 0, 0) == 0) {
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_InqHandPhase(nSide) == 1 && TaLogic_GetMinimumTask_Summon_00155770(pos, nSide, pInput) >= 0) {
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

typedef struct State_00154EB0 {
    u16 position;
    u16 pad2;
    u16 flags;
    u16 pad6;
    u16 destination;
    u16 destination_high;
} State_00154EB0;

/* Orders a fighting unit (task `pTask`): straight at its goal when the path is open, else the nearest enemy it can
   beat. */
void TaLogic017_CommandBtlUnit(void *pTask) {
    s32 position;
    u8 kind;
    State_00154EB0 *state = pTask;
    s32 other;
    s32 destination;

    if (SzDuel_GetUnit(state->position >> 8, state->position & 0xFF) == 0) {
        return;
    }
    other = (Ta_GetCurrentSide(state->position >> 8, state->position & 0xFF) == 0 ? 1 : 0) << 8;
    position = SzDuel_GetUnitLoc(state->position >> 8, state->position & 0xFF);
    SzDuel_GetUnitLoc(other >> 8, other & 0xFF);
    SzDuel_GetUnit(state->position >> 8, state->position & 0xFF);
    kind = (SzDuel_GetUnitKind(state->position >> 8, state->position & 0xFF) >> 5) & 0xFF;
    state->flags = 0x7FF;
    if (TaLogic017_IsLineTop(state->position >> 8, state->position & 0xFF) == 1) {
        *(u32 *)&state->destination = (position << 16) | state->destination;
        return;
    }
    {
        s32 y;
        s32 x;

        x = position & 0xFF;
        y = position >> 8;
        if (TaLogic017_IsLinePoint(x, y, kind) == 0 && TaLogic017_IsLinePoint(x, y, 0) == 0 && y < 6) {
            *(u32 *)&state->destination = (((position & 0xFF) | 0x600) << 16) | state->destination;
            return;
        }
    }
    destination = TaLogic017_GetEmptyLine(kind);
    if (destination >= 0) {
        *(u32 *)&state->destination = (destination << 16) | state->destination;
        return;
    }
    destination = TaLogic017_GetEmptyLine(0);
    if (destination >= 0) {
        *(u32 *)&state->destination = (destination << 16) | state->destination;
        return;
    }
    state->flags = 0x6FF;
    *(u32 *)&state->destination = state->destination | 0x05030000;
}

typedef struct Action_00155070 {
    u16 location;
    u16 unk2;
    s16 state;
    u16 unk6;
    union {
        s32 value;
        u16 low;
    } data;
} Action_00155070;


/* Orders an effect monster (task `pTask`): where its effect does most. */
void TaLogic017_CommandEfcMonster(void *pTask) {
    extern s32 SzDuel_GetUnitCardNo();
    s32 owner;
    s32 i;
    s32 kind;
    s32 list;
    s32 pair;
    u8 count;
    Action_00155070 *action;

    action = pTask;
    owner = Ta_IsUnitControl(action->location >> 8, action->location & 0xFF);
    kind = SzDuel_GetUnitCardNo(action->location >> 8, action->location & 0xFF);
    count = 0;
    switch (kind) {
    case 0x38:
    case 0x39:
    case 0x36:
    case 0x37:
        action->state = 0x6FF;
        action->data.value = action->data.low | (SzDuel_GetUnitLoc(action->location >> 8, action->location & 0xFF) << 16);
        return;
    case 0x40:
        list = SearchUnitByRange(0, 0, owner, 2, 3, 0xE);
        for (i = 0; i < Ta_GetUnitNumFrom22bitFlagList(list); i++) {
            pair = Ta_GetUnitOwnerIDFromLstCount(list, i);
            if (TaLogic_IsJudgeUnitDanger(pair >> 8, pair & 0xFF, 0) == 1) {
                count++;
            }
        }
        if (count > 1) {
            TaLogic017_CommandBtlUnit(action);
            action->state = 0x3FF;
            return;
        }
        break;
    case 0x5F:
        if (SzDuel_GetLP(owner) < 0x4B0) {
            TaLogic017_CommandBtlUnit(action);
            action->state = 0x3FF;
            return;
        }
        break;
    }
    TaLogic017_CommandBtlUnit(action);
}

typedef struct State_00155230 {
    u16 position;
    u16 pad2;
    u16 flags;
    u16 pad6;
    u16 destination;
    u16 destination_high;
} State_00155230;

/* Orders a face-down magic card (task `pTask`): whether and where to open it. */
void TaLogic017_CommandSpellUnit(void *pTask) {
    s32 position;
    u8 kind;
    State_00155230 *state = pTask;
    s32 card;
    s32 destination;

    extern s32 SzDuel_GetUnitCardNo();

    Ta_IsUnitControl(state->position >> 8, state->position & 0xFF);
    kind = (SzDuel_GetUnitKind(state->position >> 8, state->position & 0xFF) >> 5) & 0xFF;
    position = SzDuel_GetUnitLoc(state->position >> 8, state->position & 0xFF);
    card = SzDuel_GetUnitCardNo(state->position >> 8, state->position & 0xFF);
    switch (kind) {
    case 1:
    case 3:
    case 2: {
        s32 y;
        s32 x;

        state->flags = 0x7FF;
        if (TaLogic017_IsLineTop(state->position >> 8, state->position & 0xFF) == 1) {
            *(u32 *)&state->destination = (position << 16) | state->destination;
            break;
        }
        x = position & 0xFF;
        y = position >> 8;
        if (TaLogic017_IsLinePoint(x, y, kind) == 0 &&
            TaLogic017_IsLinePoint(x, y, 0) == 0 && y < 6) {
            *(u32 *)&state->destination = (((position & 0xFF) | 0x600) << 16) | state->destination;
            break;
        }
        destination = TaLogic017_GetEmptyLine(kind);
        if (destination >= 0) {
            *(u32 *)&state->destination = (destination << 16) | state->destination;
            break;
        }
        destination = TaLogic017_GetEmptyLine(0);
        if (destination >= 0) {
            *(u32 *)&state->destination = (destination << 16) | state->destination;
            break;
        }
        state->flags = 0x6FF;
        *(u32 *)&state->destination = state->destination | 0x05030000;
        break;
    }
    case 4:
        if (card != 0x334 && card != 0x337) {
            state->flags = 0x3FF;
            *(u32 *)&state->destination = (position << 16) | state->destination;
            break;
        }
        state->flags = 0x6FF;
        destination = TaLogic017_GetEmptyLine(kind);
        if (destination >= 0) {
            *(u32 *)&state->destination = (destination << 16) | state->destination;
            break;
        }
        destination = TaLogic017_GetEmptyLine(0);
        if (destination >= 0) {
            *(u32 *)&state->destination = (destination << 16) | state->destination;
            break;
        }
        state->flags = 0x6FF;
        *(u32 *)&state->destination = state->destination | 0x05030000;
        break;
    default:
        state->flags = 0x5FF;
        break;
    }
}

/* Whether (nX, nZ) is one of the seven line squares of side `nSide`'s half. */
s32 TaLogic017_IsLinePoint(s32 nX, s32 nZ, s32 nSide) {
    s32 i = 0;

    do {
        if (TaLogic017_GetLine(i, nSide) == ((nZ << 8) | nX)) {
            return 1;
        }
        i++;
    } while (i < 7);
    return 0;
}

/* Line square `nNo` (0..6) for side `nSide` (left edge for side 0, right edge for side 1), or -1. */
s32 TaLogic017_GetLine(s32 nNo, s32 nSide) {
    SzDuel_GetTurnOwner();
    switch (nNo) {
    case 0:
        return (nSide == 0) ? 0x200 : 0x206;
    case 1:
        return (nSide == 0) ? 0x300 : 0x306;
    case 2:
        return (nSide == 0) ? 0x400 : 0x406;
    case 3:
        return (nSide == 0) ? 0x500 : 0x506;
    case 4:
        return (nSide == 0) ? 0x600 : 0x606;
    case 5:
        return (nSide == 0) ? 0x601 : 0x605;
    case 6:
        return (nSide == 0) ? 0x602 : 0x604;
    default:
        return -1;
    }
}

/* The free line of the board this duelist's units fill next. */
s32 TaLogic017_GetEmptyLine(s32 nSide) {
    s32 i;
    s32 line;

    i = 0;
    do {
        line = TaLogic017_GetLine(i, nSide);
        if (((SzDuel_GetMapUnit(line & 0xFF, line >> 8) == 0) ? 1 : 0) == 1) {
            return TaLogic017_GetLine(i, nSide);
        }
        i++;
    } while (i < 7);
    return -1;
}

/* Whether unit (nSide, nID) is at the head of its line. */
s32 TaLogic017_IsLineTop(s32 nSide, s32 nID) {
    s32 i;
    s32 side;
    s32 otherSide;
    s32 position;
    s32 candidate;

    SzDuel_GetUnitLoc(nSide, nID);
    Ta_IsUnitControl(nSide, nID);
    side = SzDuel_GetUnitKind(nSide, nID) >> 5;
    otherSide = side != 0 ? 0 : side + 1;
    nSide = (nSide << 8) | nID;

    i = 0;
    do {
        position = TaLogic017_GetLine(i, side);
        candidate = SzDuel_GetMapUnitID(position & 0xFF, position >> 8);
        if (candidate < 0) {
            return 0;
        }
        if (candidate == nSide) {
            return 1;
        }
    } while (++i < 7);

    i = 0;
    do {
        position = TaLogic017_GetLine(i, otherSide);
        candidate = SzDuel_GetMapUnitID(position & 0xFF, position >> 8);
        if (candidate < 0) {
            return 0;
        }
        if (candidate == nSide) {
            return 1;
        }
    } while (++i < 7);

    return 0;
}

typedef struct {
    u8 data[0x3C];
    u16 unk3C;
    u8 pad3E[0x22];
} Work_00155770;

typedef struct {
    s16 id;
    u8 kind;
    u8 pad3;
    s16 value;
    u8 pad6[6];
    s32 unkC;
} Ctx_00155770;

/* The summon task for side `nSide`: which hand cards to play and where, into `pInput`; -1 when it plays none. */
s32 TaLogic_GetMinimumTask_Summon_00155770(s32 wUnit, s32 nSide, s32 pInput) {
    extern s32 TaLogic_GetUnitNum();
    Work_00155770 work;
    s32 ret;
    s32 res;
    s32 pos;
    s32 kind;
    Ctx_00155770 *ctx = (Ctx_00155770 *)pInput;

    ctx->id = wUnit;
    if (SzDuel_InqHandPhase(nSide) == 0) {
        return -1;
    }
    if (TaLogic_GetUnitNum(nSide, 0) == 5 && TaLogic_GetUnitNum(nSide, 1) == 5) {
        return -1;
    }
    kind = TaLogic017_IsHandPlay(nSide, &work);
    if (kind < 0) {
        return -1;
    }
    ctx->kind = 10;
    ctx->unkC = 0;
    pos = SzDuel_GetUnitLoc(wUnit >> 8, wUnit & 0xFF);
    ret = TaLogic_GetNearCard2(&work, pos & 0xFF, pos >> 8, nSide == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, TaLogic_GetWarnHideLvl_00158780(nSide));
    if (kind == 0) {
        if (TaLogic017_SetComboQue(nSide, ctx, &work) < 0) {
            goto fallback;
        }
        if (ret < 0) {
            if (SzDuel_GetUnitMonsterCount(nSide) >= 6) {
                goto fallback;
            }
            res = TaLogic017_GetSummonPiece(nSide, kind & 0xFF, &work, ret);
            if (res < 0) {
                return -1;
            }
            ctx->value = res;
            return 1;
        }
        res = TaLogic017_GetSummonPiece(nSide, kind & 0xFF, &work, ret);
        if (res < 0) {
            return -1;
        }
        ctx->value = res;
        return 1;
    }
    if (kind == 2) {
        TaLogic017_SetSpecialComboQue(nSide, ctx, &work);
        res = TaLogic017_GetSummonPiece(nSide, kind & 0xFF, &work, ret);
        if (res < 0) {
            return -1;
        }
        ctx->value = res;
        return 1;
    }
    if (kind == 3) {
        TaLogic017_PlayExzCombo(nSide, ctx, &work);
        res = TaLogic017_GetSummonPiece(nSide, kind & 0xFF, &work, ret);
        if (res < 0) {
            return -1;
        }
        ctx->value = res;
        return 1;
    }
fallback:
    if (TaLogic017_GetSpellPlay(nSide, (u8 *)ctx, &work, work.unk3C) < 0) {
        return -1;
    }
    res = TaLogic017_GetSummonPiece(nSide, kind & 0xFF, &work, ret);
    if (res < 0) {
        return -1;
    }
    ctx->value = res;
    return 1;
}

/* Whether side `nSide` should play from its hand this turn (and what, into `pInput`). */
s32 TaLogic017_IsHandPlay(s32 nSide, void *pInput) {
    extern s32 TaLogic_GetUnitNum();
    extern s32 TaLogic017_IsExzSafe();
    s32 entries[8];
    u8 work[32];
    u8 kind0;
    u8 kind1;
    s32 i;
    s32 ret;

    kind0 = (u8)TaLogic_GetUnitNum(nSide, 0);
    kind1 = (u8)TaLogic_GetUnitNum(nSide, 1);
    if (pInput == NULL) {
        return -1;
    }
    TaHand_GetNextHand(nSide, entries);
    if (kind0 == 5) {
        if (TaLogic017_GetSpellPlay(nSide, work, pInput, 999) >= 0) {
            return 1;
        }
        return -1;
    }
    if (kind1 == 5) {
        for (i = 0; i < TaHand_GetNextHandNum(nSide); i++) {
            if ((TaHand_GetCardKind(entries[i]) >> 5) == 0 &&
                TaHand_IsCardSummon2(nSide, entries[i]) == 1) {
                SzDuel_InitCardInfo(pInput, entries[i]);
                return 0;
            }
        }
        return -1;
    }
    for (i = 0; i < TaHand_GetNextHandNum(nSide); i++) {
        if (SzDuel_Kind2Type(TaHand_GetCardKind(entries[i]) >> 5) == 2) {
            SzDuel_InitCardInfo(pInput, entries[i]);
            return 2;
        }
    }
    if (TaLogic017_IsExzSafe(nSide) == 1) {
        if (TaLogic017_PlayExzCombo(nSide, work, pInput) >= 0) {
            return 3;
        }
    }
    for (i = 0; i < TaHand_GetNextHandNum(nSide); i++) {
        if ((TaHand_GetCardKind(entries[i]) >> 5) == 0 &&
            TaHand_IsCardSummon2(nSide, entries[i]) == 1) {
            return 0;
        }
    }
    ret = TaLogic017_GetSpellPlay(nSide, work, pInput, 999);
    if (ret >= 0) {
        return ret;
    }
    return -1;
}

typedef struct {
    u8 pad[0x38];
    s16 attack;
    s16 defense;
} Stats_00155C90;


/* The Exodia plan for side `nSide`: which hand cards to play (Exodia parts first, then equips), into `bCombo`,
   `pCardInfo`. */
s32 TaLogic017_PlayExzCombo(s32 nSide, u8 *bCombo, void *pCardInfo) {
    s32 sortCount;
    s32 cards[5];
    u8 selected[5];
    u16 order[5];
    s32 selectedCount;
    u8 *selectedCursor;
    s32 *cardCursor;
    s32 *sortCards;
    u8 *selectedBase;
    u16 *orderBase;
    s32 i;
    u16 *orderCursor;
    s32 j;
    u8 *appendCursor;
    s32 appendIndex;
    s32 remaining;
    s32 copyIndex;

    selectedBase = selected;
    orderBase = order;
    selectedCount = 0;
    sortCount = 0;
    {
        s32 n = 0;
        do {
            selected[n] = order[n] = 0xFF;
            n++;
        } while (n < 5);
    }
    TaHand_GetNextHand(nSide, cards);
    i = 0;
    if (0 < TaHand_GetNextHandNum(nSide)) {
        selectedCursor = selectedBase;
        do {
            if (TaLogic017_IsExzParts(cards[i]) == 1) {
                *selectedCursor++ = i;
                selectedCount++;
                i = TaHand_GetNextHandNum(nSide);
            }
            i++;
        } while (i < TaHand_GetNextHandNum(nSide));
    }
    if (selectedCount == 0) {
        return -1;
    }
    SzDuel_InitCardInfo(pCardInfo, cards[selected[0]]);
    i = 0;
    if (0 < TaHand_GetNextHandNum(nSide)) {
        cardCursor = cards;
        appendCursor = selected + selectedCount;
        do {
            if (Ta_GetHandEnchant(cards[selected[0]], *cardCursor) >= 0 &&
                (TaHand_GetCardKind(*cardCursor) >> 5) == 2) {
                s32 card = *cardCursor;
                if (card != 0x31B && card != 0x31C) {
                    ((Stats_00155C90 *)pCardInfo)->attack += (s16)TaEnc_GetEncScore(card);
                    ((Stats_00155C90 *)pCardInfo)->defense += (s16)TaEnc_GetEncScore(*cardCursor);
                    selectedCount++;
                    *appendCursor++ = i;
                }
            }
            cardCursor++;
            i++;
        } while (i < TaHand_GetNextHandNum(nSide));
    }
    j = 0;
    if (0 < TaHand_GetNextHandNum(nSide)) {
            sortCards = cards;
            orderCursor = orderBase;
            do {
                if (TaLogic017_IsRefuseEmptyCombo(*sortCards) == 0) {
                    *orderCursor++ = j;
                    sortCount++;
                }
                sortCards++;
                j++;
            } while (j < TaHand_GetNextHandNum(nSide));
    }
    TaLogic017_SortTempArray(order, 0, sortCount - 1, nSide, cards);
    remaining = TaHand_GetNextHandNum(nSide) - selectedCount;
    copyIndex = 0;
    if (0 < remaining) {
        do {
            bCombo[copyIndex + 6] = *(u8 *)orderBase;
            copyIndex++;
            orderBase++;
        } while (copyIndex < remaining);
    }
    appendIndex = 0;
    if (0 < selectedCount) {
        do {
            bCombo[remaining + 6] = *selectedBase;
            appendIndex++;
            remaining++;
            selectedBase++;
        } while (appendIndex < selectedCount);
    }
    return 1;
}

/* Sorts `indices[first..last]` by the summon cost of `values` (quicksort). */
void TaLogic017_SortTempArray(u16 *indices, s32 first, s32 last, s32 key, s32 *values) {
    s32 pivot;
    s32 i;
    u16 *scan;
    s32 score;

    if (first < last) {
        TaLogic017_SortSwap((s32 *)indices, first, (first + last) >> 1);
        i = first + 1;
        pivot = first;
        if (i <= last) {
            scan = &indices[i];
            do {
                score = TaHand_GetCardSummonCost2(values[*scan], key);
                if (TaHand_GetCardSummonCost2(values[indices[first]], key) < score) {
                    pivot++;
                    TaLogic017_SortSwap((s32 *)indices, pivot, i);
                }
                i++;
                scan++;
            } while (i <= last);
        }
        TaLogic017_SortSwap((s32 *)indices, first, pivot);
        if (first < pivot) {
            s32 leftPivot;
            s32 j;
            u16 *leftScan;

            TaLogic017_SortSwap((s32 *)indices, first, (first + pivot) >> 1);
            j = first + 1;
            leftPivot = first;
            if (j <= pivot) {
                leftScan = &indices[j];
                do {
                    if (TaHand_GetCardSummonCost2(values[*leftScan], key) >
                        TaHand_GetCardSummonCost2(values[indices[first]], key)) {
                        leftPivot++;
                        TaLogic017_SortSwap((s32 *)indices, leftPivot, j);
                    }
                    j++;
                    leftScan++;
                } while (j <= pivot);
            }
            TaLogic017_SortSwap((s32 *)indices, first, leftPivot);
            TaLogic017_SortTempArray(indices, first, leftPivot, key, values);
            TaLogic017_SortTempArray(indices, leftPivot + 1, pivot, key, values);
        }
        if (pivot + 1 < last) {
            s32 rightPivot;
            s32 k;
            u16 *rightScan;
            s32 rightScore;

            TaLogic017_SortSwap((s32 *)indices, pivot + 1, (pivot + 1 + last) >> 1);
            k = pivot + 2;
            rightPivot = pivot + 1;
            if (k <= last) {
                rightScan = &indices[k];
                do {
                    rightScore = TaHand_GetCardSummonCost2(values[*rightScan], key);
                    if (TaHand_GetCardSummonCost2(values[indices[pivot + 1]], key) < rightScore) {
                        rightPivot++;
                        TaLogic017_SortSwap((s32 *)indices, rightPivot, k);
                    }
                    k++;
                    rightScan++;
                } while (k <= last);
            }
            TaLogic017_SortSwap((s32 *)indices, pivot + 1, rightPivot);
            TaLogic017_SortTempArray(indices, pivot + 1, rightPivot, key, values);
            TaLogic017_SortTempArray(indices, rightPivot + 1, last, key, values);
        }
    }
}

/* Swaps entries `i` and `j` of `list`. */
void TaLogic017_SortSwap(s32 *list, s32 i, s32 j) {
    s32 temp_a0;
    s32 *temp_a1;
    s32 *temp_a2;

    temp_a1 = &list[i];
    temp_a2 = &list[j];
    temp_a0 = *temp_a1;
    *temp_a1 = *temp_a2;
    *temp_a2 = temp_a0;
}

/* Whether side `nSide` plays a magic or ritual card from its hand now (its slot into `bCombo`, the card into
   `pCardInfo`). */
s32 TaLogic017_GetSpellPlay(s32 nSide, u8 *bCombo, void *pCardInfo, s32 nMode) {
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


typedef struct Info_001564E0 {
    u8 pad[8];
    u16 x;
    s16 y;
} Info_001564E0;

typedef struct Sprite_001564E0 {
    Info_001564E0 *info;
    u8 pad[0x34];
    s16 x;
    s16 y;
} Sprite_001564E0;

/* Fills hand combination `bCombo` for side `nSide`: the best fusion or equip chain, its card into `pCardInfo`. */
s32 TaLogic017_SetComboQue(s32 nSide, u8 *bCombo, void *pCardInfo) {
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
                if ((TaHand_GetCardKind(card) >> 5) == 0 && TaHand_IsCardSummon2(nSide, card) == 1) {
                    *node = TaLogic_GetFusionTree(nSide, (struct TreeTag *)*node, i & 0xFF, card & 0xFFFF, 0, (u16 *)&a, (u16 *)&b);
                    *node = TaLogic_GetFusionRes(*node);
                    value = TaLogic_GetEnchantQue(nSide, *node, 0, 0);
                    if (best < (value & 0xFFFF)) {
                        TaLogic_ConvEmptyCombo_001566D0(nSide, *node, entries);
                        TaLogic_CopyArray((u8 *)*node + 2, bCombo + 6);
                        SzDuel_InitCardInfo(pCardInfo, (s32)**node);
                        ((Sprite_001564E0 *)pCardInfo)->x = (value >> 16) - (((Sprite_001564E0 *)pCardInfo)->info->x & 0x1FFF);
                        ((Sprite_001564E0 *)pCardInfo)->y = (value & 0xFFFF) - (((Sprite_001564E0 *)pCardInfo)->info->y & 0x1FFF);
                        best = value;
                        if (top < (value & 0xFFFF)) {
                            top = value & 0xFFFF;
                        }
                    } else if (top < (value & 0xFFFF)) {
                        top = value & 0xFFFF;
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

/* Fills an empty combination: the hand card side `nSide` can summon with the best attack plus defence. */
void TaLogic_ConvEmptyCombo_001566D0(s32 nSide, u16 *pCardInfo, s32 *pResult) {
    s32 count;
    s32 i;
    s32 id;
    u8 limit;
    u8 buf[5];

    if (pCardInfo == NULL) {
        return;
    }
    limit = TaHand_GetCardSummonCost2(*pCardInfo, nSide);
    for (i = 0; i < 5; i++) {
        buf[i] = 0xFF;
    }
    for (i = 0, count = 0; i < TaHand_GetNextHandNum(nSide); i++) {
        if ((u8)TaLogic_IsUseHandInCombo(i, (u8 *)(pCardInfo + 1)) == 0) {
            buf[count++] = i;
        }
    }
    if (count != 0) {
        for (i = 0; i < (u8)TaLogic_GetArrayLength(buf); i++) {
            id = pResult[buf[i]];
            if (id != 999 && TaLogic017_IsRefuseEmptyCombo(id) == 0 && limit >= TaHand_GetCardSummonCost2(id, nSide) &&
                (u16)TaLogic_GetHandFusion(*pCardInfo, (u16)id) == 999) {
                TaLogic_AddEmptyCombo((u8 *)(pCardInfo + 1), buf[i]);
            }
        }
    }
}

/* Whether this duelist keeps card `nCardNo` out of a summon (it is wanted for an equip). */
s32 TaLogic017_IsRefuseEmptyCombo(s32 nCardNo) {
    extern u32 TaHand_GetCardAPDP();
    s32 cost;

    cost = TaHand_GetCardAPDP(nCardNo);
    if ((TaHand_GetCardKind(nCardNo) >> 5) != 0) {
        return 1;
    }
    if ((cost & 0xFFFF) + (cost >> 16) * 2 > 0x1194) {
        return 1;
    }
    if (TaLogic017_IsExzParts(nCardNo) == 1) {
        return 1;
    }
    return 0;
}


typedef struct {
    u8 pad0[6];
    u8 slot[5];
} Obj1_00156910;

typedef struct {
    u8 pad0[0x38];
    s16 f38;
    s16 f3A;
    u16 id;
} Obj2_00156910;

/* Fills hand combination `bCombo` for side `nSide` with this duelist's special combination, its card into
   `pCardInfo`. */
s32 TaLogic017_SetSpecialComboQue(s32 nSide, void *bCombo, void *pCardInfo) {
    Obj1_00156910 *o1 = bCombo;
    Obj2_00156910 *o2 = pCardInfo;
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
            if (o2->id == list[i] && TaHand_IsCardSummon2(nSide, list[i]) == 1) {
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

struct DotrLogic017SummonBlock {
    unsigned char unknown_00[0x3c];
    unsigned short unknown_3c;
    unsigned char unknown_3e;
    unsigned char unknown_3f[0x21];
};
struct DotrStateItem;
extern struct DotrStateItem *func_001E36E0_b(int x, int y);
extern int func_00156EA0_b(int side);
extern int func_00156F70_b(int side);
#define MAXI(a, b) ((a) < (b) ? (b) : (a))
#define MINI(a, b) ((b) < (a) ? (b) : (a))
/* The first free line square for side `c`, or -1. */
static inline int empty_line(int c)
{
    int i;
    for (i = 0; i < 7; i++) {
        int pos = TaLogic017_GetLine(i, c);
        if ((func_001E36E0_b(pos & 0xFF, pos >> 8) == 0 ? 1 : 0) == 1) {
            return TaLogic017_GetLine(i, c);
        }
    }
    return -1;
}

/* The square side `nSide` summons a card of kind `sKind` to. */
int TaLogic017_GetSummonPiece(int nSide, int sKind, void *pInput, int nMode)
{
    struct DotrLogic017SummonBlock * block = pInput;
    int loc;
    int row;
    int i;
    int best;
    int spot;
    int ty;
    int best_spot;
    unsigned char far;
    int tx;
    int y;
    int x;
    int pos;

    (void)sKind;
    loc = SzDuel_GetUnitLoc(nSide, 0);
    if (block == 0) {
        return -1;
    }
    far = block->unknown_3e >> 5;
    if (TaLogic017_IsExzParts(block->unknown_3c) == 1) {
        if (loc == 0x403) {
            return func_00156EA0_b(nSide);
        }
        return -1;
    }
    if (block->unknown_3c == 821 || block->unknown_3c == 824) {
        if (loc == 0x403) {
            return func_00156F70_b(nSide);
        }
        return -1;
    }
    best = 7;
    best_spot = -1;
    row = SzDuel_GetUnitLoc(nSide, 0) >> 8;
    pos = empty_line(far);
    if (pos < 0) {
        if (far != 0) {
            pos = empty_line(0);
            if (pos < 0) {
                pos = 0x503;
            }
        } else {
            pos = empty_line(far + 1);
            if (pos < 0) {
                pos = 0x503;
            }
        }
    }
    for (i = 0, ty = pos >> 8, tx = pos & 0xff; i < 8; i++) {
        spot = Ta_GetSommonPiecePreference(nSide, i);
        if (spot >= 0) {
            x = spot & 0xff;
            y = spot >> 8;
            if (SzDuel_GetField(x, y) != 8 && SzDuel_GetField(x, y) != 9 && SzDuel_GetMapUnitID(x, y) < 0) {
                if ((MAXI(tx, x) - MINI(tx, x)) + (MAXI(ty, y) - MINI(ty, y)) <= best && y >= row) {
                    best_spot = spot;
                    best = (MAXI(tx, x) - MINI(tx, x)) + (MAXI(ty, y) - MINI(ty, y));
                    row = y;
                }
            }
        }
    }
    if (best_spot >= 0) {
        return best_spot;
    }
    best_spot = -1;
    return best_spot;
}
#undef MAXI
#undef MINI

/* The first free square of the four Exodia squares (3,3), (4,4), (2,4), (3,5) as (z << 8) | x, or -1. */
s32 TaLogic017_GetEmptyExzPiece(void) {
    s32 i;
    s32 value;

    for (i = 0; i < 4; i++) {
        switch ((u8)i) {
        case 0:
            value = 0x303;
            break;
        case 1:
            value = 0x404;
            break;
        case 2:
            value = 0x402;
            break;
        case 3:
            value = 0x503;
            break;
        default:
            value = 0x503;
            break;
        }
        if (SzDuel_GetMapUnit(value & 0xFF, value >> 8) == 0) {
            return value;
        }
    }
    return -1;
}

/* The free trap square (2, 3) or (4, 3), or -1. */
s32 TaLogic017_GetEmptyTrapPiece(void) {
    if (SzDuel_GetMapUnit(2, 3) == 0) {
        return 0x302;
    }
    return (SzDuel_GetMapUnit(4, 3) == 0) ? 0x304 : -1;
}

typedef struct {
    u16 id;
    u8 pad2[6];
    u32 position;
} Record_00156FC0;

typedef struct {
    u16 id;
    u8 kind;
    u8 pad3;
    u16 position;
    u8 pad6[6];
    s32 action;
    u8 status;
} Result_00156FC0;

typedef struct {
    u8 x : 4;
    u8 y : 4;
} Position_00156FC0;


/* The task's target square: the second half-word when `mode` is 1, else the first. */
static inline u32 position_00156FC0(void *src, u8 mode) {
    if (mode == 1) {
        return (u16)(((Record_00156FC0 *)src)->position >> 16);
    }
    return (u16)((Record_00156FC0 *)src)->position;
}

/* Whether the first square is nearer to (x, y) than the second. */
static inline s32 closer_00156FC0(Position_00156FC0 *best, Position_00156FC0 *current,
                                 s32 x, s32 y) {
    s32 bestLowY = best->y < y ? best->y : y;
    s32 bestHighY = y < best->y ? best->y : y;
    s32 bestLowX = best->x < x ? best->x : x;
    s32 bestHighX = x < best->x ? best->x : x;
    s32 currentLowY = current->y < y ? current->y : y;
    s32 currentHighY = y < current->y ? current->y : y;
    s32 currentLowX = current->x < x ? current->x : x;
    s32 currentHighX = x < current->x ? current->x : x;
    return ((currentHighX - currentLowX) + (currentHighY - currentLowY)) <
           ((bestHighX - bestLowX) + (bestHighY - bestLowY));
}

/* The task of a unit attacking (task `pTask`): its path to the goal, into `pInput`; -1 when it has none (`fFirst`
   = 1 for the unit's first-choice task). */
s32 TaLogic_GetMinimumTask_AtkMission_00156FC0(void *pTask, s32 nSide, void *pInput, u8 fFirst) {
    extern void TaLogic_GetInvadeRoot();
    s32 sourcePosition;
    s32 targetPosition;
    s32 count;
    Position_00156FC0 positions[12];
    s32 i;
    Position_00156FC0 *p;
    Position_00156FC0 *candidate;
    s32 sourceY;
    s32 sourceX;
    u32 lowPosition;
    u32 highPosition;
    s32 unitInfo;

    lowPosition = position_00156FC0(pTask, fFirst);
    highPosition = position_00156FC0(pTask, fFirst);
    if (SzDuel_GetUnit(highPosition >> 8, lowPosition & 0xFF) == 0) {
        TaLogic_InitRogicControl(pTask, 1);
        return -1;
    }
    sourcePosition = SzDuel_GetUnitLoc(((Record_00156FC0 *)pTask)->id >> 8, ((Record_00156FC0 *)pTask)->id & 0xFF);
    lowPosition = position_00156FC0(pTask, fFirst);
    highPosition = position_00156FC0(pTask, fFirst);
    targetPosition = SzDuel_GetUnitLoc(highPosition >> 8, lowPosition & 0xFF);
    candidate = positions;
    i = 0;
    p = candidate;
    do {
        p->x = p->y = 15;
        i++;
        p++;
    } while (i < 12);

    unitInfo = SzDuel_GetUnit(((Record_00156FC0 *)pTask)->id >> 8, ((Record_00156FC0 *)pTask)->id & 0xFF);
    sourceX = sourcePosition & 0xFF;
    sourceY = sourcePosition >> 8;
    if (GetMoveRev(unitInfo, sourceX, sourceY) == 0) {
        s32 value;
        ((Result_00156FC0 *)pInput)->id = ((Record_00156FC0 *)pTask)->id;
        ((Result_00156FC0 *)pInput)->kind = 6;
        ((Result_00156FC0 *)pInput)->position = sourcePosition;
        value = TaLogic_GetUnitWarning(sourceX, sourceY, nSide, 3, 1,
                             (u8)TaLogic_GetWarnHideLvl_00158780(nSide));
        if (value >= SzDuel_GetUnitAP(((Record_00156FC0 *)pTask)->id >> 8, ((Record_00156FC0 *)pTask)->id & 0xFF, 0)) {
            ((Result_00156FC0 *)pInput)->status = 1;
        } else {
            ((Result_00156FC0 *)pInput)->status = 0;
        }
        TaLogic_InitRogicControl(pTask, fFirst);
        return 0;
    } else {
        s32 id;
        u16 flags;
        s32 targetY;
        s32 targetX;
        s32 bestIndex;
        s32 index;
        s32 bestValue;

        id = ((Record_00156FC0 *)pTask)->id;
        flags = (u16)TaLogic_GetWarnHideLvl_00158780(nSide);
        TaLogic_GetInvadeRoot(id >> 8, id & 0xFF, positions, sourceX, sourceY,
                     targetX = targetPosition & 0xFF, targetY = targetPosition >> 8,
                     position_00156FC0(pTask, fFirst),
                     (s64)0, (s64)30, (s64)flags);
        count = TaLogic_GetMinGoalCount((u8 *)positions);
        bestIndex = 0xFF;
        if (count > 0) {
            bestValue = 0xFFFF;
            index = 0;
            if (index < count) {
            do {
                s32 value;
                value = TaLogic_GetUnitWarning(candidate->x, candidate->y, nSide, 2, 1,
                                     (u8)TaLogic_GetWarnHideLvl_00158780(nSide));
                if (value < bestValue) {
                    bestValue = value;
                    bestIndex = index;
                } else if (value == bestValue) {
                    if (closer_00156FC0(&positions[bestIndex], candidate, targetX, targetY)) {
                        bestValue = value;
                        bestIndex = index;
                    }
                }
                index++;
                candidate++;
            } while (index < count);
            }
        } else {
            ((Result_00156FC0 *)pInput)->id = ((Record_00156FC0 *)pTask)->id;
            ((Result_00156FC0 *)pInput)->kind = 6;
            ((Result_00156FC0 *)pInput)->position = sourcePosition;
            ((Result_00156FC0 *)pInput)->action = 2;
            ((Result_00156FC0 *)pInput)->status = 2;
            TaLogic_InitRogicControl(pTask, fFirst);
            return -1;
        }
        if (bestIndex != 0xFF) {
            ((Result_00156FC0 *)pInput)->id = ((Record_00156FC0 *)pTask)->id;
            ((Result_00156FC0 *)pInput)->kind = 6;
            ((Result_00156FC0 *)pInput)->position = (positions[bestIndex].y << 8) | positions[bestIndex].x;
            ((Result_00156FC0 *)pInput)->action = 2;
            ((Result_00156FC0 *)pInput)->status = 2;
        } else {
            ((Result_00156FC0 *)pInput)->id = ((Record_00156FC0 *)pTask)->id;
            ((Result_00156FC0 *)pInput)->kind = 6;
            ((Result_00156FC0 *)pInput)->position = sourcePosition;
            ((Result_00156FC0 *)pInput)->action = 2;
            ((Result_00156FC0 *)pInput)->status = 2;
            TaLogic_InitRogicControl(pTask, fFirst);
            return -1;
        }
    }
    return 0;
}

typedef struct Nibbles_00157480 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_00157480;

typedef struct Output_00157480 {
    u16 position;
    u8 action;
    u8 pad3;
    u16 destination;
    u8 pad6[6];
    s32 special;
    u8 result;
} Output_00157480;


/* The task of a unit running from danger (task `pTask`): the safest square in reach, into `pInput` (`fFirst` = 1
   for the unit's first-choice task). */
s32 TaLogic_GetMinimumTask_RunMission_00157480(u16 *pTask, s32 nSide, void *pInput, u8 fFirst) {
    Output_00157480 *output = pInput;
    s32 target;
    u8 endX;
    u8 extra;
    Nibbles_00157480 nibbles[12];
    s32 bestScore;
    s32 best;
    s32 i;
    Nibbles_00157480 *p;
    extern s32 TaLogic_IsOpenUnit_00158360();
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

        initialScore = TaLogic_GetWarnHideLvl_00158780(nSide);
        centerX = target & 0xFF;
        centerY = target >> 8;
        if (TaLogic_GetUnitWarning(centerX, centerY, *pTask, 3, initialScore, 0) == 0) {
            output->position = *pTask;
            output->action = 6;
            output->destination = target;
            output->result = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, output->destination, 1, 0);
            output->special = TaLogic_IsOpenUnit_00158360(*pTask >> 8, *pTask & 0xFF, pTask);
            TaLogic_InitRogicControl(pTask, fFirst);
            return 0;
        }
        if ((range = GetMoveRev(SzDuel_GetUnit(*pTask >> 8, *pTask & 0xFF), centerX, centerY)) == 0) {
            output->position = *pTask;
            output->action = 6;
            output->destination = target;
            output->result = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, output->destination, 1, 0);
            output->special = TaLogic_IsOpenUnit_00158360(*pTask >> 8, *pTask & 0xFF, pTask);
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
                        candidateScore = TaLogic_GetUnitWarning(x, y, *pTask, 3, (u16)TaLogic_GetWarnHideLvl_00158780(nSide), 0);
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
            output->special = TaLogic_IsOpenUnit_00158360(*pTask >> 8, *pTask & 0xFF, pTask);
        } else {
            output->position = *pTask;
            output->action = 6;
            output->destination = target;
            output->result = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, output->destination, 1, 0);
            output->special = TaLogic_IsOpenUnit_00158360(*pTask >> 8, *pTask & 0xFF, pTask);
        }
        TaLogic_InitRogicControl(pTask, fFirst);
        return 0;
    }
}

typedef struct Coord_00157A50 {
    u8 x : 4;
    u8 y : 4;
} Coord_00157A50;

typedef struct Unit_00157A50 {
    u16 position;
    u8 pad2[6];
    union {
        u32 packed;
        u16 low;
    } target;
} Unit_00157A50;

typedef struct Output_00157A50 {
    u16 position;
    u8 kind;
    u8 pad3;
    u16 target;
    u8 pad6[6];
    s32 value;
    u8 flag;
} Output_00157A50;


/* The task's target square: the second half-word when the second argument is 1, else the first. */
static inline u32 target_00157A50(void *unit, s32 side) {
    return side == 1 ? (u32)(u16)(((Unit_00157A50 *)unit)->target.packed >> 16) : (u32)((Unit_00157A50 *)unit)->target.low;
}

/* The smaller of the two values. */
static inline u32 minY_00157A50(void *unit, s32 side, u8 coord) {
    return coord < (target_00157A50(unit, side) >> 8) ? coord : (target_00157A50(unit, side) >> 8);
}

/* The larger of the two values. */
static inline u32 maxY_00157A50(void *unit, s32 side, u8 coord) {
    return (target_00157A50(unit, side) >> 8) < coord ? coord : (target_00157A50(unit, side) >> 8);
}

/* The smaller of the two values. */
static inline u32 minX_00157A50(void *unit, s32 side, u8 coord) {
    return coord < (target_00157A50(unit, side) & 0xFF) ? coord : (target_00157A50(unit, side) & 0xFF);
}

/* The larger of the two values. */
static inline u32 maxX_00157A50(void *unit, s32 side, u8 coord) {
    return (target_00157A50(unit, side) & 0xFF) < coord ? coord : (target_00157A50(unit, side) & 0xFF);
}

/* The task of a unit moving to its goal (task `pTask`), into `pInput` (`fFirst` = 1 for the unit's first-choice
   task). */
s32 TaLogic_GetMinimumTask_MoveMission_00157A50(void *pTask, s32 nSide, void *pInput, u8 fFirst, u8 nKind, u8 nMode) {
    extern s32 TaLogic_IsOpenUnit_00158360();
    extern s32 TaLogic_GetUnitWarning();
    extern void TaLogic_GetRoot();
    extern void TaLogic_GetInvadeRoot();
    extern s32 TaLogic_IsDefStyleUnit(s32, s32, s32, u8, s32);
    Coord_00157A50 coords[12];
    s32 initial;
    s32 cell;
    s32 count;

    initial = SzDuel_GetUnitLoc(((Unit_00157A50 *)pTask)->position >> 8, ((Unit_00157A50 *)pTask)->position & 0xFF);
    {
        s32 bestScore;
        s32 best;
        s32 side = fFirst;
        Coord_00157A50 *candidate;
        s32 index;
        if (target_00157A50(pTask, side) == 0xFFFF) {
            if (initial == target_00157A50(pTask, side)) {
                ((Output_00157A50 *)pInput)->position = ((Unit_00157A50 *)pTask)->position;
                ((Output_00157A50 *)pInput)->kind = 6;
                ((Output_00157A50 *)pInput)->target = initial;
                ((Output_00157A50 *)pInput)->flag = TaLogic_IsDefStyleUnit(((Unit_00157A50 *)pTask)->position >> 8, ((Unit_00157A50 *)pTask)->position & 0xFF, ((Output_00157A50 *)pInput)->target, nKind, 0);
                ((Output_00157A50 *)pInput)->value = TaLogic_IsOpenUnit_00158360(((Unit_00157A50 *)pTask)->position >> 8, ((Unit_00157A50 *)pTask)->position & 0xFF, pTask);
                TaLogic_InitRogicControl(pTask, fFirst);
                return 0;
            }
        }

        if (SzDuel_GetUnitStatus(((Unit_00157A50 *)pTask)->position >> 8, ((Unit_00157A50 *)pTask)->position & 0xFF, 4) != 0) {
            if ((SzDuel_GetUnitKind(((Unit_00157A50 *)pTask)->position >> 8, ((Unit_00157A50 *)pTask)->position & 0xFF) >> 5) == 1 ||
                (SzDuel_GetUnitKind(((Unit_00157A50 *)pTask)->position >> 8, ((Unit_00157A50 *)pTask)->position & 0xFF) >> 5) == 5) {
                SzDuel_SetUnitStatus(((Unit_00157A50 *)pTask)->position >> 8, ((Unit_00157A50 *)pTask)->position & 0xFF, 0, 1);
                ((Output_00157A50 *)pInput)->position = ((Unit_00157A50 *)pTask)->position;
                ((Output_00157A50 *)pInput)->kind = 14;
                return 0;
            }
        }

        candidate = coords;
        {
            s32 i = 0;
            Coord_00157A50 *entry = candidate;
            do {
                entry->x = entry->y = 0xF;
                i++;
                entry++;
            } while (i < 12);
        }

        cell = SzDuel_GetMapUnitID(target_00157A50(pTask, side) & 0xFF, target_00157A50(pTask, side) >> 8);
        if (cell < 0) {
            cell = 0xFFFF;
        }
        if (nMode == 1) {
            TaLogic_GetInvadeRoot(((Unit_00157A50 *)pTask)->position >> 8, ((Unit_00157A50 *)pTask)->position & 0xFF,
                         coords, initial & 0xFF, initial >> 8, target_00157A50(pTask, side) & 0xFF,
                         target_00157A50(pTask, side) >> 8, 0xFFFF, 0, 30, (u16)TaLogic_GetWarnHideLvl_00158780(nSide));
        } else {
            TaLogic_GetRoot(((Unit_00157A50 *)pTask)->position >> 8, ((Unit_00157A50 *)pTask)->position & 0xFF,
                         coords, initial & 0xFF, initial >> 8, target_00157A50(pTask, side) & 0xFF,
                         target_00157A50(pTask, side) >> 8, (u16)cell, 7);
        }
        count = TaLogic_GetMinGoalCount((u8 *)coords);
        {
            if (count > 0) {
                best = 0xFF;
                bestScore = 0xFFFF;
                for (index = 0; index < count; index++) {
                    if (SzDuel_GetMapUnit(candidate->x, candidate->y) == 0) {
                        s32 score = TaLogic_GetUnitWarning(candidate->x, candidate->y, nSide, 3, 1, (u8)TaLogic_GetWarnHideLvl_00158780(nSide));
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
                            bestMinY = minY_00157A50(pTask, side, bestY);
                            bestMaxY = maxY_00157A50(pTask, side, bestY);
                            bestX = (&coords[best])->x;
                            bestMinX = minX_00157A50(pTask, side, bestX);
                            bestMaxX = maxX_00157A50(pTask, side, bestX);
                            currentY = (u8)candidate->y;
                            currentMinY = minY_00157A50(pTask, side, currentY);
                            currentMaxY = maxY_00157A50(pTask, side, currentY);
                            currentX = candidate->x;
                            currentMinX = minX_00157A50(pTask, side, currentX);
                            currentMaxX = maxX_00157A50(pTask, side, currentX);
                            if ((currentMaxX - currentMinX) + (currentMaxY - currentMinY) < (bestMaxX - bestMinX) + (bestMaxY - bestMinY)) {
                                bestScore = score;
                                best = index;
                            }
                        }
                    }
                    candidate++;
                }
            } else {
                ((Output_00157A50 *)pInput)->position = ((Unit_00157A50 *)pTask)->position;
                ((Output_00157A50 *)pInput)->kind = 6;
                ((Output_00157A50 *)pInput)->target = initial;
                ((Output_00157A50 *)pInput)->flag = TaLogic_IsDefStyleUnit(((Unit_00157A50 *)pTask)->position >> 8, ((Unit_00157A50 *)pTask)->position & 0xFF, ((Output_00157A50 *)pInput)->target, nKind, 0);
                ((Output_00157A50 *)pInput)->value = TaLogic_IsOpenUnit_00158360(((Unit_00157A50 *)pTask)->position >> 8, ((Unit_00157A50 *)pTask)->position & 0xFF, pTask);
                TaLogic_InitRogicControl(pTask, fFirst);
                return 0;
            }

            if (best != 0xFF) {
                ((Output_00157A50 *)pInput)->position = ((Unit_00157A50 *)pTask)->position;
                ((Output_00157A50 *)pInput)->kind = 6;
                ((Output_00157A50 *)pInput)->target = (coords[best].y << 8) | coords[best].x;
                ((Output_00157A50 *)pInput)->flag = TaLogic_IsDefStyleUnit(((Unit_00157A50 *)pTask)->position >> 8, ((Unit_00157A50 *)pTask)->position & 0xFF, ((Output_00157A50 *)pInput)->target, nKind, 0);
                ((Output_00157A50 *)pInput)->value = TaLogic_IsOpenUnit_00158360(((Unit_00157A50 *)pTask)->position >> 8, ((Unit_00157A50 *)pTask)->position & 0xFF, pTask);
            } else {
                ((Output_00157A50 *)pInput)->position = ((Unit_00157A50 *)pTask)->position;
                ((Output_00157A50 *)pInput)->kind = 6;
                ((Output_00157A50 *)pInput)->target = initial;
                ((Output_00157A50 *)pInput)->flag = TaLogic_IsDefStyleUnit(((Unit_00157A50 *)pTask)->position >> 8, ((Unit_00157A50 *)pTask)->position & 0xFF, ((Output_00157A50 *)pInput)->target, nKind, 0);
                ((Output_00157A50 *)pInput)->value = TaLogic_IsOpenUnit_00158360(((Unit_00157A50 *)pTask)->position >> 8, ((Unit_00157A50 *)pTask)->position & 0xFF, pTask);
            }
            TaLogic_InitRogicControl(pTask, fFirst);
        }
    }
    return 0;
}

/* Whether this duelist opens (turns face up) unit (nSide, nID) now: 0 no, 1 or 2 by its kind. */
s32 TaLogic_IsOpenUnit_00158360(s32 nSide, s32 nID) {
    u8 sp70[0x20];
    u8 sp90[0x60];
    s32 spF0[8];
    u8 count;
    s32 state;
    s32 mask;
    u32 *data;

    extern s32 TaLogic017_IsExzSafe();

    count = 0;
    state = SzDuel_GetUnitCardNo();
    SzDuel_GetUnitLoc(nSide, nID);
    mask = Ta_IsUnitControl(nSide, nID);
    data = SzDuel_GetUnitEffect(nSide, nID, 0);
    TaHand_GetNextHand(nSide, spF0);
    if (SzDuel_GetUnitStatus(nSide, nID, 4) != 0) {
        return 0;
    }
    if (TaLogic017_IsExzParts(state) == 1) {
        if (TaLogic017_IsExzodia(mask) == 4) {
            return 1;
        }
    }
    switch (SzDuel_GetUnitKind(nSide, nID) >> 5) {
    case 0:
        switch (state) {
        case 0x5F:
            if (SzDuel_GetLP(nSide) < 0x4B0) {
                return 1;
            }
            break;
        case 0x40: {
            s32 i;
            s32 position;

            mask = SearchUnitByRange(0, 0, mask, 2, 3, 14);
            for (i = 0; i < Ta_GetUnitNumFrom22bitFlagList(mask); i++) {
                position = Ta_GetUnitOwnerIDFromLstCount(mask, i);
                if (TaLogic_IsJudgeUnitDanger(position >> 8, position & 0xFF, 0) == 1) {
                    count++;
                }
            }
            if ((u8)count > 1) {
                return 1;
            }
            break;
        }
        }
        return 2;
    case 1:
        if (TaLogic_GetActionReaction(nSide, nID, 0, 0, 6, 0) == 5) {
            return 2;
        }
        if (data == NULL) {
            return 2;
        }
        switch (*data >> 8) {
        case 0x22:
            if (Ta_GetUnitNumFrom22bitFlagList(SearchUnitByRange(0, 0, mask, 2, 0x1D, 14)) > 3) {
                return 1;
            }
            break;
        case 0x17: {
            s32 list;
            s32 i;
            s32 position;

            list = SearchUnitByRange(0, 0, mask, 2, 0x34, 14);
            for (i = 0; i < Ta_GetUnitNumFrom22bitFlagList(list); i++) {
                position = Ta_GetUnitOwnerIDFromLstCount(list, i);
                if ((SzDuel_GetUnitLoc(position >> 8, position & 0xFF) >> 8) >= 2) {
                    return 1;
                }
            }
            break;
        }
        case 0x26: {
            s32 *p;
            s32 i;

            i = 0;
            if (i < TaHand_GetNextHandNum(mask)) {
                p = spF0;
                do {
                    if (SzDuel_Kind2Type(TaHand_GetCardKind(*p) >> 5) == 2) {
                        return 1;
                    }
                    p++;
                    i++;
                } while (i < TaHand_GetNextHandNum(mask));
            }
            if (TaLogic017_IsExzSafe(mask) == 1 && TaLogic017_PlayExzCombo(mask, sp70, sp90) >= 0) {
                return 1;
            }
            break;
        }
        case 0xD:
            if ((*data & 0x3F) == 0x32) {
                if (Ta_GetUnitNum(mask == 0 ? 1 : 0, 3) >= 3) {
                    return 1;
                }
            } else {
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

/* How careful this duelist is about hidden cards (by its life points and monster count). */
s32 TaLogic_GetWarnHideLvl_00158780(s32 nSide) {
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

/* Whether card `nCardNo` is an Exodia part. */
s32 TaLogic017_IsExzParts(s32 nCardNo) {
    s32 result;

    result = (u32) (nCardNo - 0x36) < 4U ? 1 : 0;
    return result;
}

/* Whether side `nSide`'s Exodia plan is safe (its protecting traps are set or in the graveyard). */
s32 TaLogic017_IsExzSafe(s32 nSide) {
    return TaLogic017_IsSetTrap(nSide);
}

/* Whether side `nSide` has each of its four protecting cards (0x32B, 0x325, 0x335, 0x338) on the board or in the
   graveyard. */
s32 TaLogic017_IsSetTrap(s32 nSide) {
    if (SearchUnitByRange(0, 0, nSide, 1, 0x032B001C, 14) == 0) {
        if (TaLogic_GetGraveCardCount(nSide, 1, 0x32B) == 0) {
            return 0;
        }
    }
    if (SearchUnitByRange(0, 0, nSide, 1, 0x0325001C, 14) == 0) {
        if (TaLogic_GetGraveCardCount(nSide, 1, 0x325) == 0) {
            return 0;
        }
    }
    if (SearchUnitByRange(0, 0, nSide, 1, 0x0335001C, 14) == 0) {
        if (TaLogic_GetGraveCardCount(nSide, 1, 0x335) == 0) {
            return 0;
        }
    }
    if (SearchUnitByRange(0, 0, nSide, 1, 0x0338001C, 14) == 0) {
        if (TaLogic_GetGraveCardCount(nSide, 1, 0x338) == 0) {
            return 0;
        }
    }
    return 1;
}

/* How many Exodia limbs side `nSide` has ready on its summon squares (0..4; 0 unless its leader is Exodia's
   head). found[] is not cleared before the count, as in the original. */
s32 TaLogic017_IsExzodia(s32 nSide) {
    extern s32 SzDuel_GetUnitCardNo();
    extern s32 SzDuel_GetUnitCurseRest();
    extern s32 SzDuel_GetUnitSpellRest();
    s32 i;
    s32 count;
    s32 j;
    s32 type;
    s32 v;
    s32 found[4];

    count = 0;
    if (SzDuel_GetUnitCardNo(nSide, 0) == 0x3A) {
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 8; j++) {
                v = Ta_GetSommonPiecePreference(nSide, j);
                if (SzDuel_GetMapUnit(v & 0xFF, v >> 8) != 0) {
                    v = SzDuel_GetMapUnitID(v & 0xFF, v >> 8);
                    if (v >= 0) {
                        type = SzDuel_GetUnitCardNo(v >> 8, v & 0xFF);
                        if (type == Ta_GetExzodiaPartsCardNo(i) &&
                            SzDuel_GetUnitCurseRest(v >> 8, v & 0xFF) == 0 &&
                            SzDuel_GetUnitSpellRest(v >> 8, v & 0xFF) == 0 &&
                            (v >> 8) == nSide) {
                            found[i] = 1;
                        }
                    }
                }
            }
            count += found[i];
        }
        return count;
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
} Req_00158AB0;

typedef struct {
    u8 pad0[0x160];
    u16 list[32];    /* 0x160 */
    u8 idx : 5;      /* 0x1A0 */
    u8 pad1A0 : 3;
    u8 pad1A1;
    u16 count;       /* 0x1A2 */
} Work_00158AB0;

s32 TaLogic_GetInputQueFromMinimumTask_b(void *, void *, s32);

/* Computer duelist 17's controller (duelistControllers[17]): the buttons it presses this frame. With an empty
   input queue it plans its next task and turns it into buttons, then plays the queue back one button per frame;
   after 600 frames it gives up the turn (0x20, then 0x800). */
s32 duelistController17(s32 wCursorPos, void *pCtl) {
    Req_00158AB0 req;
    Work_00158AB0 *w;
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
        if (TaLogic_GetMinimumTask_00154220(w, &req, wCursorPos) == 0) {
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

#pragma conditional_move off

/* This duelist's move: picks the next unit to act, gives it a task and turns that into input `pInput`; returns 1
   when it set one. */
s32 TaLogic_GetMinimumTask_00158C80(void *pCtl, void *pInput, s32 wCursorPos) {
    u16 *tasks = pCtl;
    s32 side;
    s32 found;
    s32 result;
    s32 index;

    side = SzDuel_GetTurnOwner();
    found = 0;
    if ((result = TaLogic_GetNextActiveUnit_00159380(tasks, side, (s32)pInput)) < 0) {
        return 0;
    }
    index = TaLogic_GetActionUnitFromOwnerID(tasks, result & 0xFFFF);
    if (index < 0) {
        return 0;
    }
    if ((result >> 16) == 1) {
        if (((tasks[index * 8 + 2] >> 8) & 0xFF) == 10) {
            TaLogic_InitRogicControl(tasks + index * 8, 1);
        } else {
            TaLogic_InitRogicControl(tasks + index * 8, 0);
        }
        return 1;
    }
    TaLogic_CommandUnit_001591B0(tasks + index * 8);
    switch ((tasks[index * 8 + 2] >> 8) & 0xFF) {
    case 5:
        if (SzDuel_GetUnitStatus(tasks[index * 8] >> 8, tasks[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_RunMission_0015B250(tasks + index * 8, side, pInput, 1);
            found = 1;
        }
        break;
    case 2:
        if (SzDuel_GetUnitStatus(tasks[index * 8] >> 8, tasks[index * 8] & 0xFF, 0) == 0) {
            if (TaLogic_GetMinimumTask_AtkMission_0015B820(tasks + index * 8, side, pInput, 1) < 0) {
                TaLogic_InitRogicControl(tasks + index * 8, 1);
                return 1;
            }
            found = 1;
        }
        break;
    case 10:
        if (TaLogic_GetMinimumTask_Summon_0015A360(tasks[index * 8], side, (s32)pInput) < 0) {
            TaLogic_InitRogicControl(tasks + index * 8, 1);
            *(u8 *)((u8 *)pInput + 2) = 0xFF;
            *(s32 *)((u8 *)pInput + 0xC) = 0;
        } else {
            TaLogic_InitRogicControl(tasks + index * 8, 1);
            found = 1;
        }
        break;
    case 6:
        if (SzDuel_GetUnitStatus(tasks[index * 8] >> 8, tasks[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_MoveMission_0015BE00(tasks + index * 8, side, pInput, 1, 0);
            found = 1;
        }
        break;
    case 3:
        if (SzDuel_GetUnitStatus(tasks[index * 8] >> 8, tasks[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_MoveMission_0015BE00(tasks + index * 8, side, pInput, 1, 1);
            found = 1;
        }
        break;
    case 9:
        TaLogic_GetMinimumTask_EncMission(tasks + index * 8, side, pInput, 1, 0, TaLogic_GetWarnHideLvl_0015D120(side), 3, 1);
        found = 1;
        break;
    case 11:
        TaLogic_GetMinimumTask_TrapMission_0015C670(tasks + index * 8, side, pInput, 1);
        found = 1;
        break;
    case 14:
        TaLogic_GetMinimumTask_DoNone(tasks + index * 8, side, pInput);
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
    switch (tasks[index * 8 + 2] & 0xFF) {
    case 5:
        if (SzDuel_GetUnitStatus(tasks[index * 8] >> 8, tasks[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_RunMission_0015B250(tasks + index * 8, side, pInput, 0);
            found = 1;
        }
        break;
    case 2:
        if (SzDuel_GetUnitStatus(tasks[index * 8] >> 8, tasks[index * 8] & 0xFF, 0) == 0) {
            if (TaLogic_GetMinimumTask_AtkMission_0015B820(tasks + index * 8, side, pInput, 0) < 0) {
                TaLogic_GetMinimumTask_RunMission_0015B250(tasks + index * 8, side, pInput, 0);
            }
            found = 1;
        }
        break;
    case 10:
        if (TaLogic_GetMinimumTask_Summon_0015A360(tasks[index * 8], side, (s32)pInput) < 0) {
            TaLogic_InitRogicControl(tasks + index * 8, 0);
            *(u8 *)((u8 *)pInput + 2) = 0xFF;
            found = 1;
            *(s32 *)((u8 *)pInput + 0xC) = 0;
        } else {
            TaLogic_InitRogicControl(tasks + index * 8, 0);
            found = 1;
        }
        break;
    case 6:
        if (SzDuel_GetUnitStatus(tasks[index * 8] >> 8, tasks[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_MoveMission_0015BE00(tasks + index * 8, side, pInput, 0, 0);
            found = 1;
        }
        break;
    case 3:
        if (SzDuel_GetUnitStatus(tasks[index * 8] >> 8, tasks[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_MoveMission_0015BE00(tasks + index * 8, side, pInput, 0, 1);
            found = 1;
        }
        break;
    case 9:
        TaLogic_GetMinimumTask_EncMission(tasks + index * 8, side, pInput, 0, 0, TaLogic_GetWarnHideLvl_0015D120(side), 3, 1);
        found = 1;
        break;
    case 11:
        TaLogic_GetMinimumTask_TrapMission_0015C670(tasks + index * 8, side, pInput, 0);
        found = 1;
        break;
    case 14:
        TaLogic_GetMinimumTask_DoNone(tasks + index * 8, side, pInput);
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
s32 TaLogic_CommandUnit_001591B0(u16 *pCtl) {
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
                        TaLogic_CommandEncUnit(pCtl, 3, 0, TaLogic_GetWarnHideLvl_0015D120(controllingSide) & 0xFF);
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
s32 TaLogic_GetNextActiveUnit_00159380(u16 *pCtl, s32 nSide, s32 pInput) {
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
    TaLogic_CommandUnit_001591B0(pCtl + idx * 8);
    if (((pCtl[idx * 8 + 2] >> 8) & 0xFF) == 10) {
        if (SzDuel_InqHandPhase(nSide) == 1 && TaLogic_GetMinimumTask_Summon_0015A360(pos, nSide, pInput) >= 0) {
            return pos | 0x10000;
        }
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_GetUnitStatus(nSide, 0, 0) == 0) {
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_InqHandPhase(nSide) == 1 && TaLogic_GetMinimumTask_Summon_0015A360(pos, nSide, pInput) >= 0) {
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

/* The smaller of the two values. */
static inline s32 min_00159930(s32 a, s32 b) {
    return (a >= b + 1) ? b : a;
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
    range = GetMoveRev(SzDuel_GetUnit(nSide, nID), pos & 0xFF, pos >> 8);
    xMin = GetCap(0, (pos & 0xFF) - (range & 0xF));
    xMax = min_00159930((pos & 0xFF) + (range & 0xF), 6);
    yMin = GetCap(0, (pos >> 8) - (range & 0xF));
    yMax = min_00159930((pos >> 8) + (range & 0xF), 6);
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
            d = TaLogic_GetUnitWarning(i, j, (nSide << 8) | nID, 3, (u16)TaLogic_GetWarnHideLvl_0015D120(nSide), 0);
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
                                  (u8)i, TaLogic_GetWarnHideLvl_0015D120(side), list, 0,
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

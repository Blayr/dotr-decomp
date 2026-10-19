/* Computer AI of T. Tristan Grey (duelist 12, duelistController12). */

#include "common.h"
#pragma conditional_move off

/* This duelist's move: picks the next unit to act, gives it a task and turns that into input `pInput`; returns 1
   when it set one. */
s32 TaLogic_Tristan_GetMinimumTask(void *pCtl, void *pInput, s32 wCursorPos) {
    UnitTask *tasks = pCtl;
    s32 side;
    s32 found;
    s32 result;
    s32 index;

    side = SzDuel_GetTurnOwner();
    found = 0;
    if ((result = TaLogic_Tristan_GetNextActiveUnit(tasks, side, (s32)pInput)) < 0) {
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
    TaLogic_Tristan_CommandUnit(&tasks[index]);
    switch ((tasks[index].mission >> 8) & 0xFF) {
    case TASK_RUN:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            TaLogic_Tristan_GetMinimumTask_RunMission(&tasks[index], side, pInput, 1);
            found = 1;
        }
        break;
    case TASK_ATTACK:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            if (TaLogic_Tristan_GetMinimumTask_AtkMission(&tasks[index], side, pInput, 1) < 0) {
                TaLogic_InitRogicControl(&tasks[index], 1);
                return 1;
            }
            found = 1;
        }
        break;
    case TASK_SUMMON:
        if (TaLogic_Tristan_GetMinimumTask_Summon(tasks[index].ownerId, side, (s32)pInput) < 0) {
            TaLogic_InitRogicControl(&tasks[index], 1);
            *(u8 *)((u8 *)pInput + 2) = 0xFF;
            *(s32 *)((u8 *)pInput + 0xC) = 0;
        } else {
            TaLogic_InitRogicControl(&tasks[index], 1);
            found = 1;
        }
        break;
    case TASK_MOVETOLOCATION:
    case 15:
    case 16:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            TaLogic_Tristan_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 1, 0);
            found = 1;
        }
        break;
    case TASK_CONFIRMUNIT:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            TaLogic_Tristan_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 1, 1);
            found = 1;
        }
        break;
    case TASK_ENCHANT:
        TaLogic_GetMinimumTask_EncMission(&tasks[index], side, pInput, 1, 0, TaLogic_Tristan_GetWarnHideLvl(side), 2, 1);
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
            TaLogic_Tristan_GetMinimumTask_RunMission(&tasks[index], side, pInput, 0);
            found = 1;
        }
        break;
    case 2:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            if (TaLogic_Tristan_GetMinimumTask_AtkMission(&tasks[index], side, pInput, 0) < 0) {
                TaLogic_Tristan_GetMinimumTask_RunMission(&tasks[index], side, pInput, 0);
            }
            found = 1;
        }
        break;
    case 10:
        if (TaLogic_Tristan_GetMinimumTask_Summon(tasks[index].ownerId, side, (s32)pInput) < 0) {
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
    case 15:
    case 16:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            TaLogic_Tristan_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 0, 0);
            found = 1;
        }
        break;
    case 3:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            TaLogic_Tristan_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 0, 1);
            found = 1;
        }
        break;
    case 9:
        TaLogic_GetMinimumTask_EncMission(&tasks[index], side, pInput, 0, 0, TaLogic_Tristan_GetWarnHideLvl(side), 2, 1);
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
s32 TaLogic_Tristan_CommandUnit(void *pCtl) {
    extern s32 SzDuel_GetUnitCardNo();
    u16 key;
    s32 controllingSide;
    s32 kind;

    key = *(u16 *)pCtl;
    controllingSide = Ta_IsUnitControl((s32)key >> 8, key & 0xFF);

    key = *(u16 *)pCtl;
    if (SzDuel_GetUnit((s32)key >> 8, key & 0xFF) != 0) {
        key = *(u16 *)pCtl;
        if (SzDuel_GetUnitStatus((s32)key >> 8, key & 0xFF, 0) == 0) {
            key = *(u16 *)pCtl;
            if (key != 0xFFFF) {
                if ((key & 0xFF) == 0) {
                    if (*(s32 *)((u8 *)pCtl + 8) == -1) {
                        if (TaLogic_IsAttackedNow((s32)key >> 8, key & 0xFF, 0) == 1) {
                            if (SzDuel_InqHandPhase((s32)(*(u16 *)pCtl) >> 8) == 1) {
                                *(u16 *)((u8 *)pCtl + 4) = 0x50A;
                            } else {
                                *(u16 *)((u8 *)pCtl + 4) = 0x5FF;
                            }
                        } else {
                            if (SzDuel_InqHandPhase((s32)(*(u16 *)pCtl) >> 8) == 1) {
                                *(u16 *)((u8 *)pCtl + 4) = 0xA05;
                            } else {
                                *(u16 *)((u8 *)pCtl + 4) = 0x5FF;
                            }
                        }
                    }
                } else {
                    kind = SzDuel_GetUnitKind((s32)key >> 8, key & 0xFF) >> 5;
                    switch (kind) {
                    case 0:
                        key = *(u16 *)pCtl;
                        if (SzDuel_GetUnitCardNo((s32)key >> 8, key & 0xFF) == 0x160) {
                            TaLogic012_CommandBtlUnit(pCtl);
                        } else {
                            TaLogic012_CommandLineUnit(pCtl);
                        }
                        break;
                    case 2:
                        TaLogic_CommandEncUnit(pCtl, 2, 0, TaLogic_Tristan_GetWarnHideLvl(controllingSide) & 0xFF);
                        break;
                    default:
                        *(u16 *)((u8 *)pCtl + 4) = 0x5FF;
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
s32 TaLogic_Tristan_GetNextActiveUnit(u16 *pCtl, s32 nSide, s32 pInput) {
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
    TaLogic_Tristan_CommandUnit(pCtl + idx * 8);
    if (((pCtl[idx * 8 + 2] >> 8) & 0xFF) == 10) {
        if (SzDuel_InqHandPhase(nSide) == 1 && TaLogic_Tristan_GetMinimumTask_Summon(pos, nSide, pInput) >= 0) {
            return pos | 0x10000;
        }
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_GetUnitStatus(nSide, 0, 0) == 0) {
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_InqHandPhase(nSide) == 1 && TaLogic_Tristan_GetMinimumTask_Summon(pos, nSide, pInput) >= 0) {
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
    u8 low : 4;
    u8 high : 4;
} Nibbles_00142F50;

typedef struct {
    u16 id;
    u8 value;
    u8 unused;
} Entry_00142F50;

typedef struct {
    u16 low;
    u16 high;
} Halves_00142F50;

typedef struct {
    u16 id;
    u16 unused2;
    u16 action;
    u16 unused6;
    union {
        u32 word;
        Halves_00142F50 halves;
    } data;
} State_00142F50;

/* Orders a unit (task `pTask`) to hold its line of the board. */
void TaLogic012_CommandLineUnit(void *pTask) {
    extern s32 TaLogic_IsRootOpen();
    extern s32 TaLogic_IsUnitWin4();
    extern s32 TaLogic_GetInvadeRoot2();
    State_00142F50 *st = pTask;
    s32 otherPosition;
    s32 position;
    s32 side;
    s32 bestScore;
    s32 other;
    s32 bestId;
    s32 result;
    u16 *walk;
    s32 lowY;
    s32 y;
    s32 count;
    s32 lowX;
    s32 x;
    s32 otherY;
    s32 otherX;
    s32 i;
    s32 owner;
    u16 *list;
    s32 candidateX;
    s32 secondCount;
    Entry_00142F50 *entry;
    s32 candidateY;
    s32 maximum;
    Nibbles_00142F50 *tile;
    s32 candidatePosition;
    Entry_00142F50 entries[22];
    u16 candidates[7];
    Nibbles_00142F50 tiles[12];

    if (SzDuel_GetUnit(st->id >> 8, st->id & 0xFF) != 0) {
        tile = tiles;
        i = 0;
        do {
            tile->low = tile->high = 15;
            i++;
            tile++;
        } while (i < 12);
        side = Ta_GetCurrentSide(st->id >> 8, st->id & 0xFF);
        other = (side == 0 ? 1 : 0) << 8;
        position = SzDuel_GetUnitLoc(st->id >> 8, st->id & 0xFF);
        otherX = other >> 8;
        otherY = other & 0xFF;
        otherPosition = SzDuel_GetUnitLoc(otherX, otherY);
        owner = SzDuel_GetUnit(st->id >> 8, st->id & 0xFF);
        bestId = -1;
        bestScore = 7;
        entry = entries;
        i = 0;
        do {
            i++;
            entry->id = 0xFFFF;
            entry->value = 0xFF;
            entry++;
        } while (i < 22);
        if (TaLogic_IsRootOpen(st->id >> 8, st->id & 0xFF, x = position & 0xFF, y = position >> 8, otherX, otherY,
                               otherPosition & 0xFF, otherPosition >> 8, 2) > 0) {
            st->action = 0x2FF;
            st->data.word = (other << 16) | st->data.halves.low;
        } else {
            list = candidates;
            i = 0;
            {
                u16 *fill = list;
                do {
                    i++;
                    *fill = 0xFFFF;
                    fill++;
                } while (i < 7);
            }
            if (CheckLandAgreement(SzDuel_GetField(x, y), (void *)owner) != 1) {
                st->action = 0x6FF;
                result = TaLogic012_GetAgreeLineZ((void *)owner);
                if (result >= 0) {
                    st->data.word = st->data.halves.low | (((result << 8) | (position & 0xFF)) << 16);
                } else {
                    TaLogic012_CommandBtlUnit(st);
                    return;
                }
                return;
            } else {
                count = TaLogic012_GetLineUnitLst((s16 *)candidates, y, side, 2) & 0xFF;
                i = 0;
                walk = list;
                goto test1;
            loop1:
                candidatePosition = SzDuel_GetUnitLoc(*walk >> 8, *walk & 0xFF);
                candidateX = candidatePosition & 0xFF;
                if (TaLogic_IsUnitWin4(owner, *walk, TaLogic_Tristan_GetWarnHideLvl(side),
                                       candidateX, candidateX, 0) >= 0) {
                    result = TaLogic_GetInvadeRoot2(owner, tiles, x, y, candidateX, candidatePosition >> 8,
                                                    *walk, 0, 5, (u16)TaLogic_Tristan_GetWarnHideLvl(side));
                    if (result > 0 && bestScore < result) {
                        bestId = *walk;
                        bestScore = result;
                    }
                } else {
                    candidateY = candidatePosition >> 8;
                    lowY = Min(y, candidateY);
                    candidateY = Max(candidateY, y);
                    lowX = Min(x, candidateX);
                    candidateX = Max(candidateX, x);
                    if ((candidateX - lowX) + (candidateY - lowY) < 3) {
                        st->action = 0x3FF;
                        st->data.word = (position << 16) | st->data.halves.low;
                        return;
                    }
                }
                walk++;
                i++;
            test1:
                if (i < count) {
                    goto loop1;
                }
                if (bestId >= 0) {
                    st->action = 0x2FF;
                    st->data.word = (bestId << 16) | st->data.halves.low;
                }
                secondCount = TaLogic012_GetLineUnitLst((s16 *)candidates, GetCap(6, y - 1), side, 2) & 0xFF;
                maximum = -1;
                i = 0;
                goto test2;
            loop2:
                candidateX = SzDuel_GetUnitLoc(*list >> 8, *list & 0xFF) & 0xFF;
                result = TaLogic_IsUnitWin4(owner, *list, TaLogic_Tristan_GetWarnHideLvl(side),
                                            candidateX, candidateX, 0);
                if (result >= 0 && maximum < result) {
                    maximum = result;
                }
                list++;
                i++;
            test2:
                if (i < secondCount) {
                    goto loop2;
                }
                if ((TaLogic012_GetLineUnitLst((s16 *)candidates, y, side, 1) & 0xFF) > 1) {
                    result = TaLogic012_GetEmptyLine((void *)owner);
                    if (result >= 0) {
                        st->action = 0x6FF;
                        st->data.word = st->data.halves.low | (((result << 8) | (position & 0xFF)) << 16);
                    } else {
                        TaLogic012_CommandBtlUnit(st);
                    }
                } else {
                    switch ((st->action >> 8) & 0xFF) {
                    case 16:
                        if (x > 0) {
                            st->data.word = (y << 24) | st->data.halves.low;
                        } else {
                            st->action = 0xFFF;
                            st->data.word = (((y << 8) | 6) << 16) | st->data.halves.low;
                        }
                        break;
                    case 15:
                        if (x < 6) {
                            st->data.word = (((y << 8) | 6) << 16) | st->data.halves.low;
                        } else {
                            st->action = 0x10FF;
                            st->data.word = (y << 24) | st->data.halves.low;
                        }
                        break;
                    default:
                        if (func_0019A5C8() % 2 == 0) {
                            st->action = 0x10FF;
                            st->data.word = (y << 24) | st->data.halves.low;
                        } else {
                            st->action = 0xFFF;
                            st->data.word = (((y << 8) | 6) << 16) | st->data.halves.low;
                        }
                        break;
                    }
                }
            }
        }
    }
}

typedef struct {
    u16 card;
    u8 flag;
    u8 pad3;
} Slot_00143540;

typedef struct {
    u16 low;
    u16 high;
} DataHalves_00143540;

typedef struct {
    u16 unitId; /* (side << 8) | unit */
    u8 pad2[2];
    u16 state;
    u8 pad6[2];
    union {
        u32 word;
        DataHalves_00143540 halves;
    } data;
} Entry_00143540;

/* Orders a fighting unit (task `pTask`): straight at its goal when the path is open, else the nearest enemy it can
   beat. */
void TaLogic012_CommandBtlUnit(void *pTask) {
    extern s32 TaLogic_IsRootOpen();
    extern void TaLogic_InitIgnoreLst();
    extern s32 TaLogic012_GetNearUnit();
    Entry_00143540 *entry = pTask;
    s32 side;
    s32 player;
    s32 pos;
    s32 other;
    s32 otherPos;
    s32 i;
    u8 work[0x70];
    Slot_00143540 list[22];
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
                          other >> 8, other & 0xFF, otherPos & 0xFF, otherPos >> 8, 2) > 0) {
            entry->state = 0x2FF;
            entry->data.word = (other << 16) | entry->data.halves.low;
            return;
        }
        countB = 0;
        countA = 0;
        i = 1;
        while (1) {
            switch (TaLogic012_GetNearUnit(entry, 0, player, pos & 0xFF, pos >> 8,
                                  Ta_GetCurrentSide(entry->unitId >> 8, entry->unitId & 0xFF) == 0 ? 1 : 0,
                                  (u8)i, TaLogic_Tristan_GetWarnHideLvl(side), list, 0,
                                  &countA, &countB, 5, work)) {
            case 3:
                entry->state = 0x6FF;
                entry->data.word = (pos << 16) | entry->data.halves.low;
                break;
            case 2:
                entry->state = 0x3FF;
                entry->data.word = (pos << 16) | entry->data.halves.low;
                return;
            case 1:
                return;
            case 0:
                entry->state = 0x5FF;
                return;
            default:
                break;
            }
            i++;
            if (i > 5) {
                break;
            }
        }
        *(u16 *)((u8 *)pTask + 4) = 0x5FF;
    }
}

/* TaLogic_GetNearUnit with this duelist's view and strength settings. */
s32 TaLogic012_GetNearUnit(s32 pTask, s32 pTree, s32 pVarInfo, s32 nX, s32 nZ, s32 eSide, s32 bDist, s32 WarnLvl, s32 nUnitLst, u16 wUnitNum, s32 wSize, s32 wNodeCount, u8 bChase, s32 wIgnoreLst) {
    return TaLogic_GetNearUnit(pTask, pTree, pVarInfo, nX, nZ, eSide, bDist, WarnLvl,
                  nUnitLst, wUnitNum, wSize, wNodeCount, bChase,
                  0, 0x708, wIgnoreLst);
}

/* The units on row `nZ` (`flags` bit 0: side `nSide`'s, bit 1: the opponent's), into `output`; returns how many. */
s32 TaLogic012_GetLineUnitLst(s16 *output, s32 nZ, s32 nSide, s32 flags) {
    s32 i;
    u8 count;
    s32 entry;
    s32 include_same;
    s32 include_other;

    count = 0;
    i = 0;
    include_same = flags & 1;
    include_other = (flags >> 1) & 1;
    do {
        if ((entry = SzDuel_GetMapUnitID(i, nZ)) >= 0) {
            if (include_same == 1) {
                if (nSide == Ta_IsUnitControl(entry >> 8, entry & 0xFF)) {
                    output[count] = entry;
                    count++;
                }
            }
            if (include_other == 1) {
                if (nSide != Ta_IsUnitControl(entry >> 8, entry & 0xFF)) {
                    output[count] = entry;
                    count++;
                }
            }
        }
        i++;
    } while (i < 7);
    return count;
}

/* The first row (1..5) whose edge field helps a unit (record `vInfo`), or -1. */
s32 TaLogic012_GetAgreeLineZ(void *vInfo) {
    s32 i;

    for (i = 1; i <= 5; i++) {
        if (CheckLandAgreement(SzDuel_GetField(0, i), vInfo) == 1) {
            return i;
        }
    }
    return -1;
}

/* How many units of side `key` stand on row `line`. */
static inline u8 TaLogic012_CountLine_00143970(s32 line, s32 key) {
    s32 i;
    u8 count;
    s32 card;

    count = 0;
    i = 0;
    do {
        card = SzDuel_GetMapUnitID(i, line);
        if (card >= 0) {
            if (key == Ta_IsUnitControl(card >> 8, card & 0xFF)) {
                count++;
            }
        }
        i++;
    } while (i < 7);
    return count;
}

/* The free line of the board this duelist's units fill next. */
s32 TaLogic012_GetEmptyLine(void *nSide) {
    s32 row;
    s32 delay;
    s32 category;
    s32 n;

    category = Ta_IsUnitControl2(nSide);
    row = 0;
    do {
        delay = 0;
        do {
            delay++;
        } while (delay < 7);
        if ((n = TaLogic012_CountLine_00143970(row, category)) == 0) {
            if (CheckLandAgreement(SzDuel_GetField(0, row), nSide) == 1) {
                return row;
            }
        }
        row++;
    } while (row < 7);
    return -1;
}

/* Whether monster card `nCardNo` has a row where the turn owner holds none and the field helps it. */
s32 TaLogic012_IsLineEmpty(s32 nCardNo, s32 arg1) {
    u8 data[0x60];
    u8 flags;
    s32 key;
    u8 count;
    s32 i;
    s32 value;
    s32 delay;

    flags = TaHand_GetCardKind(nCardNo);
    SzDuel_InitCardInfo(data, nCardNo);
    if (((s32) flags >> 5) != 0) {
        return 0;
    }
    key = SzDuel_GetTurnOwner();
    delay = 0;
    do {
        delay++;
    } while (delay < 7);
    count = 0;
    i = 0;
    do {
        value = SzDuel_GetMapUnitID(i, arg1);
        if ((value >= 0) && (key == Ta_IsUnitControl(value >> 8, value & 0xFF))) {
            count++;
        }
        i++;
    } while (i < 7);
    if (count == 0) {
        if (CheckLandAgreement(SzDuel_GetField(0, arg1), data) == 1) {
            return 1;
        }
    }
    return 0;
}

/* The summon task for side `nSide`: which hand cards to play and where, into `pInput`; -1 when it plays none. */
s32 TaLogic_Tristan_GetMinimumTask_Summon(s32 wUnit, s32 nSide, s32 pInput) {
    extern s32 TaLogic_GetUnitNum();
    struct Data_00143BA0 {
        u8 bytes[0x3C];
        u16 value;
        u8 pad[0x22];
    } data;
    s32 coordinate;
    s32 status;
    s32 value;

    *(s16 *)pInput = (s16)wUnit;
    coordinate = wUnit;
    if (SzDuel_InqHandPhase(nSide) == 0) {
        return -1;
    }
    if (TaLogic_GetUnitNum(nSide, 0) == 5 && TaLogic_GetUnitNum(nSide, 1) == 5) {
        return -1;
    }
    status = TaLogic012_IsHandPlay(nSide, &data);
    if (status < 0) {
        return -1;
    }
    *(u8 *)((u8 *)pInput + 2) = 10;
    *(s32 *)((u8 *)pInput + 0xC) = 0;
    coordinate = SzDuel_GetUnitLoc(coordinate >> 8, coordinate & 0xFF);
    value = TaLogic_Tristan_GetWarnHideLvl(nSide);
    coordinate = TaLogic_GetNearCard2(&data, coordinate & 0xFF, coordinate >> 8,
                                (nSide == 0 ? 1 : 0), 3, 0x1F, 2, 2, 0,
                                value);
    if (status == 0) {
        if (TaLogic012_SetComboQue(nSide, (u8 *)pInput, &data) < 0) {
            goto fallback;
        }
        if (coordinate < 0) {
            if (SzDuel_GetUnitMonsterCount(nSide) >= 4) {
                goto fallback;
            }
            coordinate = TaLogic012_GetSummonPiece(nSide, 0, &data, coordinate);
            if (coordinate < 0) {
                return -1;
            }
            *(s16 *)((u8 *)pInput + 4) = (s16)coordinate;
            return 1;
        }
        coordinate = TaLogic012_GetSummonPiece(nSide, 0, &data, coordinate);
        if (coordinate < 0) {
            return -1;
        }
        *(s16 *)((u8 *)pInput + 4) = (s16)coordinate;
        return 1;
    }
    if (status == 2) {
        TaLogic012_SetSpecialComboQue(nSide, (void *)pInput, &data);
        coordinate = TaLogic012_GetSummonPiece(nSide, status & 0xFF, &data, coordinate);
        if (coordinate < 0) {
            return -1;
        }
        *(s16 *)((u8 *)pInput + 4) = (s16)coordinate;
        return 1;
    }
fallback:
    coordinate = TaLogic012_GetSpellPlay(nSide, (u8 *)pInput, &data, data.value);
    if (coordinate < 0) {
        return -1;
    }
    coordinate = TaLogic012_GetSummonPiece(nSide, coordinate & 0xFF, &data, -1);
    if (coordinate < 0) {
        return -1;
    }
    *(s16 *)((u8 *)pInput + 4) = (s16)coordinate;
    return 1;
}

/* Whether side `nSide` should play from its hand this turn (and what, into `pInput`). */
s32 TaLogic012_IsHandPlay(s32 nSide, void *pInput) {
    s32 cards[8];
    u8 scratch[32];
    s32 *fallback;
    s32 result;
    s32 score;
    s32 firstIndex;
    s32 *first;
    s32 level;
    s32 selected;
    s32 fallbackIndex;
    s32 best;
    u8 firstType;
    s32 *entry;
    s32 index;
    u8 secondType;
    extern s32 TaLogic_GetUnitNum();

    firstType = TaLogic_GetUnitNum(nSide, 0);
    secondType = TaLogic_GetUnitNum(nSide, 1);
    best = -1;
    if (pInput == NULL) {
        return -1;
    }
    TaHand_GetNextHand(nSide, cards);
    if (firstType == 5) {
        if (TaLogic012_GetSpellPlay(nSide, scratch, pInput, 999) >= 0) {
            return 1;
        } else {
            return -1;
        }
    }
    if (secondType == 5) {
        firstIndex = 0;
        if (firstIndex < TaHand_GetNextHandNum(nSide)) {
            first = cards;
            do {
                if ((TaHand_GetCardKind(*first) >> 5) == 0 &&
                    TaHand_CanAffordSummonCost(nSide, *first) == 1) {
                    SzDuel_InitCardInfo(pInput, cards[firstIndex]);
                    return 0;
                }
                first++;
                firstIndex++;
            } while (firstIndex < TaHand_GetNextHandNum(nSide));
        }
        return -1;
    }
    if (TaLogic012_GetSpecCardPlay(nSide, cards, pInput, scratch, 0x34E) >= 0) {
        if (TaLogic012_IsDoCerem(nSide, 0x34E) == 1) {
            return 2;
        }
    }
    if (TaLogic012_IsPinch(nSide) == 1) {
        if (TaLogic012_GetSpecCardPlay(nSide, cards, pInput, scratch, 0x2DB) >= 0) {
            return 2;
        }
        if (TaLogic012_GetSpecCardPlay(nSide, cards, pInput, scratch, 0x2EF) >= 0) {
            return 2;
        }
    }
    index = 0;
    if (index < TaHand_GetNextHandNum(nSide)) {
        entry = cards;
        do {
            level = 1;
            while (1) {
                if (TaLogic012_IsLineEmpty(*entry, level) == 1 &&
                    TaLogic012_GetSpecCardPlay(nSide, cards, pInput, scratch, *(u16 *)entry) >= 0) {
                    score = SzDuel_GetUnitAP2(pInput, 0);
                    if (best < score) {
                        selected = *entry;
                        best = score;
                    }
                }
                level++;
                if (level > 5) {
                    break;
                }
            }
            entry++;
            index++;
        } while (index < TaHand_GetNextHandNum(nSide));
    }
    if (best >= 0) {
        SzDuel_InitCardInfo(pInput, selected);
        return 2;
    }
    fallbackIndex = 0;
    if (fallbackIndex < TaHand_GetNextHandNum(nSide)) {
        fallback = cards;
        do {
            if ((TaHand_GetCardKind(*fallback) >> 5) == 0 &&
                TaHand_CanAffordSummonCost(nSide, *fallback) == 1) {
                return 0;
            }
            fallback++;
            fallbackIndex++;
        } while (fallbackIndex < TaHand_GetNextHandNum(nSide));
    }
    result = TaLogic012_GetSpellPlay(nSide, scratch, pInput, 999);
    if (result >= 0) {
        return result;
    }
    return -1;
}

/* Whether side `nSide` holds card `nCardNo` and can summon it (its slot into `bCombo`, the card into `pCardInfo`);
   returns its kind group or -1. */
s32 TaLogic012_GetSpecCardPlay(s32 nSide, s32 *bCombo, void *pCardInfo, void *nCardNo, s32 arg4) {
    s32 index;
    s32 *entry;
    s32 key;
    s32 *selected;

    index = 0;
    if (index < TaHand_GetNextHandNum(nSide)) {
        key = (u16)arg4;
        entry = bCombo;
        do {
            if (TaHand_CanAffordSummonCost(nSide, *entry) == 1) {
                if (key == *entry && TaHand_CanAffordSummonCost(nSide, *entry) == 1) {
                    *((s8 *)nCardNo + 6) = index;
                    selected = &bCombo[index];
                    SzDuel_InitCardInfo(pCardInfo, *selected);
                    return TaHand_GetCardKind(*selected) >> 5;
                }
            }
            ++entry;
            ++index;
        } while (index < TaHand_GetNextHandNum(nSide));
    }
    return -1;
}

/* Whether side `nSide` plays a magic or ritual card from its hand now (its slot into `bCombo`, the card into
   `pCardInfo`). */
s32 TaLogic012_GetSpellPlay(s32 nSide, u8 *bCombo, void *pCardInfo, s32 nMode) {
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

typedef struct Info_00144450 {
    u8 pad00[8];
    u16 x;
    s16 y;
} Info_00144450;

typedef struct Sprite_00144450 {
    Info_00144450 *info;
    u8 pad04[0x34];
    s16 x;
    s16 y;
} Sprite_00144450;

/* Fills hand combination `bCombo` for side `nSide`: the best fusion or equip chain, its card into `pCardInfo`. */
s32 TaLogic012_SetComboQue(s32 nSide, u8 *bCombo, void *pCardInfo) {
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
                            TaLogic_Tristan_ConvEmptyCombo(nSide, *node, entries);
                            TaLogic_CopyArray((u8 *)*node + 2, bCombo + 6);
                            SzDuel_InitCardInfo(pCardInfo, **node);
                            ((Sprite_00144450 *)pCardInfo)->x = (value >> 16) - (((Sprite_00144450 *)pCardInfo)->info->x & 0x1FFF);
                            ((Sprite_00144450 *)pCardInfo)->y = (value & 0xFFFF) - (((Sprite_00144450 *)pCardInfo)->info->y & 0x1FFF);
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
} Info_00144630;

/* Fills an empty combination: the hand card side `nSide` can summon with the best attack plus defence. */
void TaLogic_Tristan_ConvEmptyCombo(s32 nSide, void *pCardInfo, s32 *pResult) {
    Info_00144630 *info = pCardInfo;
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
                if (card != 0x3E7 && TaLogic012_IsRefuseEmptyCombo(card) == 0 && level >= TaHand_GetCardSummonCost2(card, nSide)) {
                    cost = TaHand_GetCardAPDP(card);
                    if ((cost & 0xFFFF) + (cost >> 16) * 2 < 0xAF1 && TaHand_IsCardEffect(card) == 2 &&
                        (u16)TaLogic_GetHandFusion(info->id, (u16)card) == 0x3E7) {
                        TaLogic_AddEmptyCombo(info->values, buf[i]);
                    }
                }
            }
        }
    }
}

/* Whether this duelist keeps card `nCardNo` out of a summon (it is wanted for an equip). */
s32 TaLogic012_IsRefuseEmptyCombo(s32 nCardNo) {
    if ((TaHand_GetCardKind(nCardNo) >> 5) != 0) {
        return 1;
    }
    return (TaHand_IsCardEffect(nCardNo) != 0) ? 1 : 0;
}

typedef struct {
    u8 pad0[6];
    u8 slot[5];
} Obj1_00144860;

typedef struct {
    u8 pad0[0x3C];
    u16 id;
    u8 f3E;
} Obj2_00144860;

/* Fills hand combination `bCombo` for side `nSide` with this duelist's special combination, its card into
   `pCardInfo`. */
s32 TaLogic012_SetSpecialComboQue(s32 nSide, void *bCombo, void *pCardInfo) {
    Obj1_00144860 *o1 = bCombo;
    Obj2_00144860 *o2 = pCardInfo;
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
    return o2->f3E >> 5;
}

typedef struct Nibbles_00144A60 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_00144A60;

/* The first row (1..5) whose edge field helps a unit (record `arg2`), or -1. */
static inline s32 findrow_00144A60(void *arg2) {
    s32 row = 1;

    while (1) {
        if (CheckLandAgreement(SzDuel_GetField(0, row), arg2) == 1) {
            return row;
        }
        row++;
        if (row > 5) {
            break;
        }
    }
    return -1;
}

/* The square side `nSide` summons a card of kind `sKind` to. */
s32 TaLogic012_GetSummonPiece(s32 nSide, s32 sKind, void *pInput, s32 nMode) {
    extern s32 TaLogic_IsUnitWin4();
    extern s32 TaLogic_GetInvadeRoot2();
    extern s32 TaLogic_GetRoot2(s32, s32, s32, s32, s32, s32, u16, u8);
    s32 bestPosition;
    s32 bestScore;
    Nibbles_00144A60 path[12];
    s32 initIndex;
    Nibbles_00144A60 *p;
    u8 type;

    if (pInput == NULL) {
        return -1;
    }
    p = path;
    initIndex = 0;
    do {
        p->low = p->high = 15;
        initIndex++;
        p++;
    } while (initIndex < 12);
    type = (u8)(((u8 *)pInput)[0x3E] >> 5);
    if (type == 0 || type == 3) {
        if (nMode >= 0) {
            s32 position;
            s32 y;
            s32 x;
            s32 i;
            s32 targetY;
            s32 targetX;
            s32 target;
            s32 score;

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
                        if (TaLogic_IsUnitWin4((s32)pInput, nMode, TaLogic_Tristan_GetWarnHideLvl(nSide), targetX, targetY, 0) > 0) {
                            score = TaLogic_GetInvadeRoot2((s32)pInput, (s32)path, x, y, targetX, targetY,
                                                 nMode, 0, 3, (u16)TaLogic_Tristan_GetWarnHideLvl(nSide));
                        } else {
                            score = TaLogic_GetRoot2((s32)pInput, (s32)path, x, y, targetX, targetY, nMode, 3);
                        }
                        if (TaLogic_GetMinGoalCount((u8 *)path) > 0 && score < bestScore) {
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
            bestPosition = -1;
            return bestPosition;
        } else {
            s32 i;
            s32 bestDistance;
            s32 best;
            s32 position;
            s32 x;
            s32 y;
            s32 row;
            s32 lower;
            s32 distance;

            bestDistance = 14;
            best = -1;
            i = 0;
            do {
                position = Ta_GetSommonPiecePreference(nSide, i);
                if (position >= 0) {
                    x = position & 255;
                    y = position >> 8;
                    if (SzDuel_GetField(x, y) != 8 &&
                        (SzDuel_GetField(x, y) != 9 || Ta_IsVirus_Chk3(pInput, x, y) != 1) &&
                        SzDuel_GetMapUnitID(x, y) < 0) {
                        row = findrow_00144A60(pInput);
                        lower = y < row ? y : row;
                        y = row < y ? y : row;
                        distance = y - lower;
                        if (distance < bestDistance && distance >= 0) {
                            best = position;
                            bestDistance = distance;
                        }
                    }
                }
                i++;
            } while (i < 8);
            if (bestDistance < 14) {
                return best;
            }
            goto failure;
        }
    } else {
        s32 y;
        s32 x;
        s32 i;
        s32 best;
        s32 position;

        best = -1;
        i = 0;
        do {
            position = Ta_GetSommonPiecePreference(nSide, i);
            if (position >= 0) {
                x = position & 255;
                y = position >> 8;
                if (SzDuel_GetField(x, y) != 8 &&
                    (SzDuel_GetField(x, y) != 9 || Ta_IsVirus_Chk3(pInput, x, y) != 1) &&
                    SzDuel_GetMapUnitID(x, y) < 0 && y < 8) {
                    best = position;
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
} Flags_00144EC0;

typedef struct {
    u16 id;
    u8 action;
    u8 pad3;
    u16 position;
    u8 pad6[6];
    s32 value;
    u8 mode;
} Output_00144EC0;

/* The task of a unit running from danger (task `pTask`): the safest square in reach, into `pInput` (`fFirst` = 1
   for the unit's first-choice task). */
s32 TaLogic_Tristan_GetMinimumTask_RunMission(u16 *pTask, s32 nSide, void *pInput, u8 fFirst) {
    extern s32 TaLogic_IsRunPassRoot(s32, s32, s32, s32, s32, s32, void *, u8);
    extern s32 TaLogic_Tristan_IsOpenUnit();
    s32 position;
    u8 upperX;
    u8 flag;
    Flags_00144EC0 cells[12];
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
    Output_00144EC0 *out = pInput;

    position = SzDuel_GetUnitLoc(*pTask >> 8, *pTask & 0xFF);
    i = 0;
    do {
        cells[i].low = cells[i].high = 15;
        i++;
    } while (i < 12);

    {
        u16 value = (u16)TaLogic_Tristan_GetWarnHideLvl(nSide);
        originalX = position & 0xFF;
        originalY = position >> 8;
        if (TaLogic_GetUnitWarning(originalX, originalY, *pTask, 3, value, 0) == 0) {
            out->id = *pTask;
            out->action = 6;
            out->position = position;
            out->mode = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, out->position, 1, 0);
            out->value = TaLogic_Tristan_IsOpenUnit(*pTask >> 8, *pTask & 0xFF, pTask);
            TaLogic_InitRogicControl(pTask, fFirst);
            return 0;
        } else {
            result = GetMoveRange(SzDuel_GetUnit(*pTask >> 8, *pTask & 0xFF), originalX, originalY);
            if (result == 0) {
                out->id = *pTask;
                out->action = 6;
                out->position = position;
                out->mode = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, out->position, 1, 0);
                out->value = TaLogic_Tristan_IsOpenUnit(*pTask >> 8, *pTask & 0xFF, pTask);
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
                                value = (u16)TaLogic_Tristan_GetWarnHideLvl(nSide);
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
                    out->value = TaLogic_Tristan_IsOpenUnit(*pTask >> 8, *pTask & 0xFF, pTask);
                } else {
                    out->id = *pTask;
                    out->action = 6;
                    out->position = position;
                    out->mode = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, out->position, 1, 0);
                    out->value = TaLogic_Tristan_IsOpenUnit(*pTask >> 8, *pTask & 0xFF, pTask);
                }
                TaLogic_InitRogicControl(pTask, fFirst);
            }
        }
    }
    return 0;
}

typedef struct Input_00145400 {
    u16 position;
    u8 pad2[6];
    u32 targets;
} Input_00145400;

typedef struct Output_00145400 {
    u16 position;
    u8 action;
    u8 pad3;
    u16 destination;
    u8 pad6[6];
    s32 special;
    u8 result;
} Output_00145400;

typedef struct Coord_00145400 {
    u8 x : 4;
    u8 y : 4;
} Coord_00145400;

/* The task's target square: the second half-word when the second argument is 1, else the first. */
static inline u32 target_00145400(void *src, u8 side) {
    Input_00145400 *input = src;
    if (side == 1) {
        return (u16)(input->targets >> 16);
    }
    return (u16)input->targets;
}

#define MIN_00145400(a, b) ((a) < (b) ? (a) : (b))
#define MAX_00145400(a, b) ((a) > (b) ? (a) : (b))

/* The task of a unit attacking (task `pTask`): its path to the goal, into `pInput`; -1 when it has none (`fFirst`
   = 1 for the unit's first-choice task). */
s32 TaLogic_Tristan_GetMinimumTask_AtkMission(void *pTask, s32 nSide, void *pInput, u8 fFirst) {
    extern s32 TaLogic_Tristan_IsOpenUnit();
    extern s32 GetMoveRange();
    extern s32 TaLogic_GetUnitWarning();
    extern void TaLogic_GetInvadeRoot();
    Input_00145400 *input = pTask;
    Output_00145400 *output = pInput;
    s32 targetPosition;
    s32 targetX;
    Coord_00145400 *candidate;
    s32 fallback;
    s32 origin;
    s32 count;
    s32 originY;
    s32 originX;
    s32 special;
    s32 index;
    s32 bestCost;
    s32 bestIndex;
    s32 i;
    s32 unitInfo;
    u32 targetLow;
    u32 targetHigh;
    Coord_00145400 candidates[12];

    targetLow = target_00145400(pTask, fFirst);
    targetHigh = target_00145400(pTask, fFirst);
    if (SzDuel_GetUnit(targetHigh >> 8, targetLow & 0xFF) == 0) {
        TaLogic_InitRogicControl(pTask, 1);
        return -1;
    }
    fallback = TaLogic_Tristan_IsOpenUnit((s32)input->position >> 8, input->position & 0xFF, pTask);
    origin = SzDuel_GetUnitLoc((s32)input->position >> 8, input->position & 0xFF);
    targetLow = target_00145400(pTask, fFirst);
    targetHigh = target_00145400(pTask, fFirst);
    targetPosition = SzDuel_GetUnitLoc(targetHigh >> 8, targetLow & 0xFF);
    i = 0;
    do {
        candidates[i].x = candidates[i].y = 15;
        i++;
    } while (i < 12);
    unitInfo = SzDuel_GetUnit((s32)input->position >> 8, input->position & 0xFF);
    originX = origin & 0xFF;
    originY = origin >> 8;
    if (GetMoveRange(unitInfo, originX, originY) == 0) {
        s32 cost;
        output->position = input->position;
        output->action = 6;
        output->destination = origin;
        cost = TaLogic_GetUnitWarning(originX, originY, nSide, 3, 1, (u8)TaLogic_Tristan_GetWarnHideLvl(nSide));
        if (cost >= SzDuel_GetUnitAP((s32)input->position >> 8, input->position & 0xFF, 0)) {
            output->result = TaLogic_IsDefStyleUnit((s32)input->position >> 8,
                                         input->position & 0xFF, output->destination, 1, 0);
        } else {
            output->result = TaLogic_IsDefStyleUnit((s32)input->position >> 8,
                                         input->position & 0xFF, output->destination, 0, 0);
        }
        TaLogic_InitRogicControl(pTask, fFirst);
    } else {
        s32 position = input->position;
        u16 kind = TaLogic_Tristan_GetWarnHideLvl(nSide);
        s32 positionY = position >> 8;
        s32 positionX = position & 0xFF;

        TaLogic_GetInvadeRoot(positionY, positionX, candidates,
                     originX, originY, targetX = targetPosition & 0xFF, targetPosition >>= 8,
                     target_00145400(pTask, fFirst), (s64)0, (s64)30, (s64)kind);
        count = TaLogic_GetMinGoalCount((u8 *)candidates);
        bestIndex = 255;
        if (count > 0) {
            special = 0;
            bestCost = 65535;
            for (index = 0; index < count; index++) {
                if (TaLogic012_IsOpenMoveUnit((s32)input->position >> 8, input->position & 0xFF,
                                 originX, originY, targetX, targetPosition) == 1) {
                    Coord_00145400 *candidate = &candidates[index];
                    bestIndex = index;
                    special = 1;
                    index = count;
                    candidate->x = targetX;
                    candidate->y = targetPosition;
                } else {
                    s32 cost;
                    candidate = &candidates[index];
                    cost = TaLogic_GetUnitWarning(candidate->x, candidate->y, nSide,
                                         3, 1, (u8)TaLogic_Tristan_GetWarnHideLvl(nSide));
                    if (cost < bestCost) {
                        bestCost = cost;
                        bestIndex = index;
                    } else if (cost == bestCost) {
                        if ((MAX_00145400(candidate->x, targetX) - MIN_00145400(candidate->x, targetX)) +
                                (MAX_00145400(candidate->y, targetPosition) - MIN_00145400(candidate->y, targetPosition)) <
                            (MAX_00145400(candidates[bestIndex].x, targetX) - MIN_00145400(candidates[bestIndex].x, targetX)) +
                                (MAX_00145400(candidates[bestIndex].y, targetPosition) - MIN_00145400(candidates[bestIndex].y, targetPosition))) {
                            bestCost = cost;
                            bestIndex = index;
                        }
                    }
                }
            }
        } else {
            output->position = input->position;
            output->action = 6;
            output->destination = origin;
            output->special = fallback;
            output->result = TaLogic_IsDefStyleUnit((s32)input->position >> 8,
                                         input->position & 0xFF, output->destination, 0, 0);
            TaLogic_InitRogicControl(pTask, fFirst);
            return 0;
        }
        if (bestIndex != 255) {
            output->position = input->position;
            output->action = 6;
            output->destination = (candidates[bestIndex].y << 8) | candidates[bestIndex].x;
            output->special = special;
            output->result = TaLogic_IsDefStyleUnit((s32)input->position >> 8,
                                         input->position & 0xFF, output->destination, 0, 0);
        } else {
            output->position = input->position;
            output->action = 6;
            output->destination = origin;
            output->special = special;
            output->result = TaLogic_IsDefStyleUnit((s32)input->position >> 8,
                                         input->position & 0xFF, output->destination, 0, 0);
            TaLogic_InitRogicControl(pTask, fFirst);
            return 0;
        }
    }
    return 0;
}

typedef struct Coord_001459E0 {
    u8 x : 4;
    u8 y : 4;
} Coord_001459E0;

typedef struct Unit_001459E0 {
    u16 pos;
    u8 pad2[6];
    u32 target;
} Unit_001459E0;

typedef struct Result_001459E0 {
    u16 pos;
    s8 kind;
    u8 pad3;
    u16 target;
    u8 pad6[6];
    s32 action;
    s8 value;
} Result_001459E0;

#define selected_001459E0(unit, mode) \
    ((mode) == 1 ? (u32)(u16)(((Unit_001459E0 *)(unit))->target >> 16) \
                 : (u32)(u16)((Unit_001459E0 *)(unit))->target)

/* The smaller of the two values. */
static inline u32 minY_001459E0(u32 value, void *unit, s32 mode) {
    return value < (selected_001459E0(unit, mode) >> 8) ? (u8)value : (selected_001459E0(unit, mode) >> 8);
}

/* The larger of the two values. */
static inline u32 maxY_001459E0(u32 value, void *unit, s32 mode) {
    return (selected_001459E0(unit, mode) >> 8) < value ? (u8)value : (selected_001459E0(unit, mode) >> 8);
}

/* The smaller of the two values. */
static inline u32 minX_001459E0(u32 value, void *unit, s32 mode) {
    return value < (selected_001459E0(unit, mode) & 0xFF) ? (u8)value : (selected_001459E0(unit, mode) & 0xFF);
}

/* The larger of the two values. */
static inline u32 maxX_001459E0(u32 value, void *unit, s32 mode) {
    return (selected_001459E0(unit, mode) & 0xFF) < value ? (u8)value : (selected_001459E0(unit, mode) & 0xFF);
}

/* The task of a unit moving to its goal (task `pTask`), into `pInput` (`fFirst` = 1 for the unit's first-choice
   task). */
s32 TaLogic_Tristan_GetMinimumTask_MoveMission(void *pTask, s32 nSide, void *pInput, u8 fFirst, u8 nKind) {
    s32 target;
    s32 leader;
    s32 count;
    Coord_001459E0 coords[12];
    extern s32 TaLogic_Tristan_IsOpenUnit();
    extern s32 TaLogic_GetUnitWarning();
    extern void TaLogic_GetRoot();
    extern s32 TaLogic_IsDefStyleUnit(s32, s32, s32, u8, s32);

    {
        s32 bestCost;
        s32 bestIndex;
        s32 mode;
        Coord_001459E0 *p;
        s32 i;
        target = SzDuel_GetUnitLoc(((Unit_001459E0 *)pTask)->pos >> 8, ((Unit_001459E0 *)pTask)->pos & 0xFF);
        mode = fFirst;
        if (selected_001459E0(pTask, mode) == 0xFFFF &&
            target == selected_001459E0(pTask, mode)) {
            ((Result_001459E0 *)pInput)->pos = ((Unit_001459E0 *)pTask)->pos;
            ((Result_001459E0 *)pInput)->kind = 6;
            ((Result_001459E0 *)pInput)->target = target;
            ((Result_001459E0 *)pInput)->value = TaLogic_IsDefStyleUnit(
                ((Unit_001459E0 *)pTask)->pos >> 8, ((Unit_001459E0 *)pTask)->pos & 0xFF,
                ((Result_001459E0 *)pInput)->target, nKind, 0);
            ((Result_001459E0 *)pInput)->action = TaLogic_Tristan_IsOpenUnit(
                ((Unit_001459E0 *)pTask)->pos >> 8, ((Unit_001459E0 *)pTask)->pos & 0xFF, pTask);
            TaLogic_InitRogicControl(pTask, fFirst);
            return 0;
        }

        p = coords;
        {
            s32 i = 0;
            Coord_001459E0 *q = p;
            do {
                q->x = q->y = 15;
                ++i;
                ++q;
            } while (i < 12);
        }

        leader = SzDuel_GetMapUnitID(selected_001459E0(pTask, mode) & 0xFF,
                             selected_001459E0(pTask, mode) >> 8);
        if (leader < 0) {
            leader = 0xFFFF;
        }
        TaLogic_GetRoot(((Unit_001459E0 *)pTask)->pos >> 8, ((Unit_001459E0 *)pTask)->pos & 0xFF,
                     coords, target & 0xFF, target >> 8,
                     selected_001459E0(pTask, mode) & 0xFF,
                     selected_001459E0(pTask, mode) >> 8, (u16)leader, 7);
        count = TaLogic_GetMinGoalCount((u8 *)coords);
        if (count > 0) {
            s32 cost;
            bestIndex = 0xFF;
            bestCost = 0xFFFF;
            for (i = 0; i < count; ++i, ++p) {
                if (SzDuel_GetMapUnit(p->x, p->y) == 0) {
                    cost = TaLogic_GetUnitWarning(p->x, p->y, nSide, 3, 1,
                                        (u8)TaLogic_Tristan_GetWarnHideLvl(nSide));
                    if (cost < bestCost) {
                        bestCost = cost;
                        bestIndex = i;
                    } else if (cost == bestCost) {
                        if ((maxX_001459E0(p->x, pTask, mode) -
                             minX_001459E0(p->x, pTask, mode)) +
                            (maxY_001459E0((u8)p->y, pTask, mode) -
                             minY_001459E0((u8)p->y, pTask, mode)) <
                            (maxX_001459E0(coords[bestIndex].x, pTask, mode) -
                             minX_001459E0(coords[bestIndex].x, pTask, mode)) +
                            (maxY_001459E0((u8)coords[bestIndex].y, pTask, mode) -
                             minY_001459E0((u8)coords[bestIndex].y, pTask, mode))) {
                            bestCost = cost;
                            bestIndex = i;
                        }
                    }
                }
            }
        } else {
            ((Result_001459E0 *)pInput)->pos = ((Unit_001459E0 *)pTask)->pos;
            ((Result_001459E0 *)pInput)->kind = 6;
            ((Result_001459E0 *)pInput)->target = target;
            ((Result_001459E0 *)pInput)->value = TaLogic_IsDefStyleUnit(
                ((Unit_001459E0 *)pTask)->pos >> 8, ((Unit_001459E0 *)pTask)->pos & 0xFF,
                ((Result_001459E0 *)pInput)->target, nKind, 0);
            ((Result_001459E0 *)pInput)->action = TaLogic_Tristan_IsOpenUnit(
                ((Unit_001459E0 *)pTask)->pos >> 8, ((Unit_001459E0 *)pTask)->pos & 0xFF, pTask);
            TaLogic_InitRogicControl(pTask, fFirst);
            return 0;
        }
            if (bestIndex != 0xFF) {
                ((Result_001459E0 *)pInput)->pos = ((Unit_001459E0 *)pTask)->pos;
                ((Result_001459E0 *)pInput)->kind = 6;
                ((Result_001459E0 *)pInput)->target =
                    (coords[bestIndex].y << 8) | coords[bestIndex].x;
                ((Result_001459E0 *)pInput)->value = TaLogic_IsDefStyleUnit(
                    ((Unit_001459E0 *)pTask)->pos >> 8, ((Unit_001459E0 *)pTask)->pos & 0xFF,
                    ((Result_001459E0 *)pInput)->target, nKind, 0);
                ((Result_001459E0 *)pInput)->action = TaLogic_Tristan_IsOpenUnit(
                    ((Unit_001459E0 *)pTask)->pos >> 8, ((Unit_001459E0 *)pTask)->pos & 0xFF, pTask);
            } else {
                ((Result_001459E0 *)pInput)->pos = ((Unit_001459E0 *)pTask)->pos;
                ((Result_001459E0 *)pInput)->kind = 6;
                ((Result_001459E0 *)pInput)->target = target;
                ((Result_001459E0 *)pInput)->value = TaLogic_IsDefStyleUnit(
                    ((Unit_001459E0 *)pTask)->pos >> 8, ((Unit_001459E0 *)pTask)->pos & 0xFF,
                    ((Result_001459E0 *)pInput)->target, nKind, 0);
                ((Result_001459E0 *)pInput)->action = TaLogic_Tristan_IsOpenUnit(
                    ((Unit_001459E0 *)pTask)->pos >> 8, ((Unit_001459E0 *)pTask)->pos & 0xFF, pTask);
            }
            TaLogic_InitRogicControl(pTask, fFirst);
        return 0;
    }
}

/* How careful this duelist is about hidden cards (by its life points and monster count). */
s32 TaLogic_Tristan_GetWarnHideLvl(s32 nSide) {
    if (SzDuel_GetLP(nSide) > 2000) {
        if (SzDuel_GetUnitMonsterCount(nSide) >= 4) {
            return 0;
        }
        return 0;
    }
    return 0;
}

/* Whether this duelist opens (turns face up) unit (nSide, nID) now: 0 no, 1 or 2 by its kind. */
s32 TaLogic_Tristan_IsOpenUnit(s32 nSide, s32 nID) {
    s32 pos;
    s32 kind;
    s32 slot;
    u8 count;
    s32 i;
    s32 list;
    s32 pair;
    extern s32 SzDuel_GetUnitCardNo();

    pos = SzDuel_GetUnitLoc(nSide, nID);
    kind = SzDuel_GetUnitCardNo(nSide, nID);
    slot = Ta_IsUnitControl(nSide, nID);
    count = 0;
    if (SzDuel_GetUnitStatus(nSide, nID, 4) != 0) {
        return 0;
    }
    switch (kind) {
    case 0x145:
        list = SearchUnitByRange(0, 0, nSide, 2, 0x34, 0xE);
        for (i = 0; i < Ta_GetUnitNumFrom22bitFlagList(list); i++) {
            pair = Ta_GetUnitOwnerIDFromLstCount(list, i);
            if (SzDuel_GetUnitStatus(pair >> 8, pair & 0xFF, 3) != 0) {
                count++;
            }
        }
        if (count >= 3) {
            return 1;
        }
        break;
    case 0xC0:
        if (Ta_GetUnitNumFrom22bitFlagList(SearchUnitByRange(0, 0, nSide, 1, 5, 0xE)) >= 3) {
            return 1;
        }
        break;
    case 0x2DB:
    case 0x2EF:
        if (TaLogic_GetActionReaction(nSide, nID, 0, 0, 6, 0) == 5) {
            return 2;
        }
        if (TaLogic012_IsPinch(slot) == 1) {
            return 1;
        }
        break;
    case 0x34E:
        if (TaLogic_GetActionReaction(nSide, nID, 0, 0, 6, 0) == 5) {
            return 2;
        }
        if (TaLogic012_IsDoCerem(Ta_IsUnitControl(nSide, nID), 0x34E) == 1 &&
            SzDuel_GetField(pos & 0xFF, pos >> 8) != 9) {
            return 1;
        }
        break;
    }
    return 2;
}

/* Whether unit (nSide, nID) may open while moving from (nX, nZ) to the square next to it, (gX, gZ). */
s32 TaLogic012_IsOpenMoveUnit(s32 nSide, s32 nID, s32 nX, s32 nZ, s32 gX, s32 gZ) {
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

/* Whether side `nSide` is in a pinch: few monsters of its own and five or more enemies, one past row 3. */
s32 TaLogic012_IsPinch(s32 nSide)
{
    s32 i;
    s32 mask;
    s32 entry;

    if (Ta_GetUnitNumFrom22bitFlagList(SearchUnitByRange(0, 0, nSide, 1, 0x34, 0xE)) > 2) {
        return 0;
    }

    mask = SearchUnitByRange(0, 0, nSide, 2, 0x34, 0xE);
    if (Ta_GetUnitNumFrom22bitFlagList(mask) < 5) {
        return 0;
    }

    for (i = 0; i < Ta_GetUnitNumFrom22bitFlagList(mask); i++) {
        entry = Ta_GetUnitOwnerIDFromLstCount(mask, i);
        if ((SzDuel_GetUnitLoc(entry >> 8, entry & 0xFF) >> 8) < 3) {
            return 1;
        }
    }

    return 0;
}

/* Whether side `nSide` can play ritual card `nCardNo` now (it has the units to give up). */
s32 TaLogic012_IsDoCerem(s32 nSide, s32 nCardNo) {
    s32 data[4];
    s32 index;
    s32 mask;
    s32 low;
    s32 high;
    s32 pair;
    s32 value;

    Ta_GetCeremSacrifice(data, *(s32 *)((u8 *)TaHand_GetCardEffect(nCardNo, 0) + 4));
    if ((mask = Ta_GetSacrificeUnit(data, nSide)) < 0) {
        return 0;
    }
    for (index = 0; index < Ta_GetUnitNumFrom22bitFlagList(mask); index++) {
        pair = Ta_GetUnitOwnerIDFromLstCount(mask, index);
        high = pair >> 8;
        low = pair & 0xFF;
        value = SzDuel_GetUnitLoc(high, low);
        if (TaUtil_GetUnitAP(high, low, value & 0xFF, value >> 8) >= 0x9C4) {
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
} Req_00146790;

typedef struct {
    u8 pad0[0x160];
    u16 list[32];    /* 0x160 */
    u8 idx : 5;      /* 0x1A0 */
    u8 pad1A0 : 3;
    u8 pad1A1;
    u16 count;       /* 0x1A2 */
} Work_00146790;

s32 TaLogic_GetInputQueFromMinimumTask_b(void *, void *, s32);

/* Computer duelist 12's controller (duelistControllers[12]): the buttons it presses this frame. With an empty
   input queue it plans its next task and turns it into buttons, then plays the queue back one button per frame;
   after 600 frames it gives up the turn (0x20, then 0x800). */
s32 duelistController12(s32 wCursorPos, void *pCtl) {
    Req_00146790 req;
    Work_00146790 *w;
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
        if (TaLogic_Tristan_GetMinimumTask(w, &req, wCursorPos) == 0) {
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

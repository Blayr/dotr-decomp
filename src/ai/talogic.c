/* Computer AI: the logic every AI duelist shares (TaLogic_*). */

#include "common.h"

typedef struct Entry_00275D00 {
    u16 id;
    u16 value;
    u16 other;
    u16 pad6;
    s32 index;
    u8 flags : 2;
    u8 rest : 6;
    u8 padD[3];
} Entry_00275D00;

typedef struct Data_00275D00 {
    Entry_00275D00 entries[22];
    u16 list[32];
    u8 idx : 5;
    u8 pad1A0 : 3;
    u8 sel : 4;
    u8 pad1A1 : 4;
    u16 count;
} Data_00275D00;

/* Sets up side `nSide`'s computer-opponent data `pCtl` (the tutorial has its own). */
s32 TaLogic_InitLogicData(s32 nSide, void *pCtl) {
    Data_00275D00 *data = pCtl;
    s32 i;

    if (TaTuto_IsTuto(nSide) == 1) {
        TaTuto_InitTutorial(SzDuel_GetPlayer(nSide) & 0xFF, (s32) pCtl);
        return 1;
    }
    if (data != NULL) {
        for (i = 0; i < 22; i++) {
            data->entries[i].id = 0xFFFF;
            data->entries[i].value = 0xFF;
            data->entries[i].index = -1;
            data->entries[i].other = 0xFFFF;
            data->entries[i].flags = 0;
        }
        for (i = 0; i < 32; i++) {
            data->list[i] = 0xFFFF;
        }
        data->idx = 0;
        data->sel = 0;
        data->count = 0;
        data->entries[0].id = nSide << 8;
        data->entries[0].value = SzDuel_GetUnitSummonOrder(nSide, 0);
        return 1;
    }
    return -1;
}

/* Updates the computer opponent's data `pCtl` for this turn. */
s32 TaLogic_AdjustLogicData(void *pCtl) {
    if (TaTuto_IsTuto(SzDuel_GetTurnOwner()) == 1) {
        return 1;
    }
    *(s16 *)((u8 *)pCtl + 0x1A2) = 0;
    return TaLogic_DoAdjustLogicData(pCtl);
}

typedef struct Entry_00275E80 {
    u16 id;
    u16 value;
    u16 other;
    u16 pad6;
    s32 index;
    u8 flags : 2;
    u8 rest : 6;
    u8 padD[3];
} Entry_00275E80;

typedef struct Data_00275E80 {
    Entry_00275E80 entries[22];
    u16 list[32];
    u8 idx : 5;
    u8 pad1A0 : 3;
} Data_00275E80;

/* Assigns the computer opponent's units to tasks and sorts the task list. */
s32 TaLogic_DoAdjustLogicData(void *pCtl) {
    Data_00275E80 *data = pCtl;
    s32 owner;
    s32 i;

    owner = SzDuel_GetTurnOwner();
    if (TaTuto_IsTuto(owner) == 1) {
        return 1;
    }
    if (data != NULL) {
        data->idx = 0;
        for (i = 0; i < 32; i++) {
            data->list[i] = 0xFFFF;
        }
        for (i = 0; i < 22; i++) {
            if (data->entries[i].id < 0xFFFF) {
                if (SzDuel_GetUnit(data->entries[i].id >> 8, data->entries[i].id & 0xFF) == 0 ||
                    owner != Ta_GetCurrentSide(data->entries[i].id >> 8, data->entries[i].id & 0xFF)) {
                    data->entries[i].id = 0xFFFF;
                    data->entries[i].value = 0xFF;
                    data->entries[i].index = -1;
                    data->entries[i].other = 0xFFFF;
                    data->entries[i].flags = 0;
                } else if (SzDuel_GetUnitSummonOrder(data->entries[i].id >> 8,
                                         (data->entries[i].id & 0xFF) != data->entries[i].value) != 0) {
                    data->entries[i].value = SzDuel_GetUnitSummonOrder(data->entries[i].id >> 8, data->entries[i].id & 0xFF);
                    data->entries[i].index = -1;
                    data->entries[i].other = 0xFFFF;
                    data->entries[i].flags = 0;
                }
            }
        }
        for (i = 0; i < 11; i++) {
            if (owner == Ta_GetCurrentSide(0, i)) {
                if (TaLogic_IsUnitAssign(i, (u16 *)data) == 0 && SzDuel_GetUnit(0, i) != 0) {
                    TaLogic_DoUnitAssign(i, data);
                }
            }
            if (owner == Ta_GetCurrentSide(1, i)) {
                if (TaLogic_IsUnitAssign(i | 0x100, (u16 *)data) == 0 && SzDuel_GetUnit(1, i) != 0) {
                    TaLogic_DoUnitAssign(i | 0x100, data);
                }
            }
        }
        TaLogic_DoSortTaskList(data);
        return 1;
    }
    return -1;
}

/* Whether unit `value` is already in task list `entries`. */
s32 TaLogic_IsUnitAssign(u16 value, u16 *entries) {
    s32 i = 0;

    do {
        if (value == *entries) {
            return 1;
        }
        i++;
        entries += 8;
    } while (i < 22);

    return 0;
}

typedef struct Entry_00276120 {
    u16 id;
    s16 field_02;
    u16 field_04;
    u16 field_06;
    s32 field_08;
    u8 state : 2;
    u8 flags : 6;
    u8 padding[3];
} Entry_00276120;

/* Adds unit `uID` to the computer opponent's task list in `pCtl` (by summon order). */
s32 TaLogic_DoUnitAssign(u16 uID, void *pCtl) {
    Entry_00276120 *entries = pCtl;
    s32 i;

    for (i = 0; i < 22; i++) {
        if (entries[i].id == 0xFFFF) {
            entries[i].id = uID;
            entries[i].field_02 = SzDuel_GetUnitSummonOrder(uID >> 8, uID & 0xFF);
            entries[i].field_08 = -1;
            entries[i].field_04 = 0xFFFF;
            entries[i].state = 0;
            return 1;
        }
    }
    return 0;
}

typedef struct {
    u16 id;
    s16 field_02;
    u16 field_04;
    u16 field_06;
    s32 field_08;
    u8 state : 2;
    u8 flags : 6;
    u8 padding[3];
} Entry_002761D0;

/* Sorts the computer opponent's task list in `pCtl` by distance to each task's goal. */
void TaLogic_DoSortTaskList(void *pCtl) {
    s32 i;
    s32 j;
    Entry_002761D0 *dst;
    Entry_002761D0 *src;

    i = 0;
    dst = pCtl;
    do {
        if (dst->id == 0xFFFF) {
            for (j = i + 1; j < 22; j++) {
                src = &((Entry_002761D0 *)pCtl)[j];
                if (src->id != 0xFFFF) {
                    j = 22;
                    *dst = *src;
                    src->id = 0xFFFF;
                    src->field_02 = 0xFF;
                    src->field_08 = -1;
                    src->field_04 = 0xFFFF;
                    src->state = 0;
                }
            }
        }
        i++;
        dst++;
    } while (i < 22);
}

/* From the dotr-decomp CC0 bundle (commit 88c32bb2), chatC/imp/conv.py. */

struct DotrInputQueueCtl {
    unsigned char unknown_000[0x160];
    unsigned short ids[32];
    unsigned char mode : 5;
    unsigned char unknown_1a0_5 : 3;
    unsigned char unknown_1a1;
    unsigned short count_1a2;
};
typedef char DotrInputQueueCtlSizeMustBe420[(sizeof(struct DotrInputQueueCtl) == 0x1a4) ? 1 : -1];
struct DotrInputQueueTask {
    unsigned short position;
    unsigned char kind;
    unsigned short target;
    unsigned char slots[5];
    int unknown_0c;
    unsigned char unknown_10;
};
typedef char DotrInputQueueTaskSizeMustBe20[(sizeof(struct DotrInputQueueTask) == 0x14) ? 1 : -1];
#define ABS(x) ((x) >= 0 ? (x) : -(x))
#define MOVE_X(d) \
    for (i = 0; i < ABS(d); i++) { \
        pCtl->ids[QueCount++] = (d) > 0 ? (tSide == 0 ? 0x8000 : 0x2000) : (tSide == 1 ? 0x8000 : 0x2000); \
    }
#define MOVE_Z(d) \
    for (i = 0; i < ABS(d); i++) { \
        pCtl->ids[QueCount++] = (d) > 0 ? (tSide == 0 ? 0x1000 : 0x4000) : (tSide == 1 ? 0x1000 : 0x4000); \
    }

/* Turns the cheapest task `pTask_v` into cursor and button inputs for the computer opponent, from cursor square
   `wCursorPos`. */
int TaLogic_GetInputQueFromMinimumTask(void *pCtl_v, void *pTask_v, unsigned short wCursorPos)
{
    struct DotrInputQueueCtl * pCtl = pCtl_v;
    struct DotrInputQueueTask * pTask = pTask_v;
    int i;
    int j;
    int tSide;
    int LOC;
    int HandCursor;
    int PadKey;
    int QueCount;
    int sX;
    int sZ;

    tSide = SzDuel_GetTurnOwner();
    QueCount = 0;
    if (pTask->kind == 255 || pTask->kind == 14) {
        return -1;
    }
    LOC = SzDuel_GetUnitLoc(pTask->position >> 8, pTask->position & 0xff);
    sX = (wCursorPos & 0xff) - (LOC & 0xff);
    MOVE_X(sX)
    sZ = (wCursorPos >> 8) - (LOC >> 8);
    MOVE_Z(sZ)
    switch (pTask->kind) {
    case 6:
        pCtl->ids[QueCount++] = 64;
        sX = (LOC & 0xff) - (pTask->target & 0xff);
        sZ = (LOC >> 8) - (pTask->target >> 8);
        if (pTask->position & 0xff) {
            if (pTask->unknown_0c == 1) {
                pCtl->ids[QueCount++] = 2;
            }
            if (ABS(sX) == 0 && ABS(sZ) == 0) {
                if (pTask->unknown_10 == 0 && SzDuel_GetUnitStatus(pTask->position >> 8, pTask->position & 0xff, 5)
                    && SzDuel_GetUnitStatus(pTask->position >> 8, pTask->position & 0xff, 5)) {
                    pCtl->ids[QueCount++] = 4;
                } else if (pTask->unknown_10 == 1 && !SzDuel_GetUnitStatus(pTask->position >> 8, pTask->position & 0xff, 5)
                           && !SzDuel_GetUnitStatus(pTask->position >> 8, pTask->position & 0xff, 5)) {
                    pCtl->ids[QueCount++] = 8;
                }
            }
        }
        switch (TaLogic_GetQueueXY_Move1(pTask->position >> 8, pTask->position >> 8, LOC & 0xff, LOC >> 8, pTask->target & 0xff,
                                         pTask->target >> 8)) {
        case 1:
            MOVE_X(sX)
            MOVE_Z(sZ)
            break;
        default:
            MOVE_Z(sZ)
            MOVE_X(sX)
            break;
        }
        pCtl->ids[QueCount] = 64;
        break;
    case 10:
        if (SzDuel_InqHandPhase(tSide)) {
            pCtl->ids[QueCount++] = 128;
            sX = (LOC & 0xff) - (pTask->target & 0xff);
            MOVE_X(sX)
            sZ = (LOC >> 8) - (pTask->target >> 8);
            MOVE_Z(sZ)
            pCtl->ids[QueCount++] = 64;
            HandCursor = 0;
            for (i = 0; i < 5; i++) {
                if (pTask->slots[i] < 255) {
                    if (pTask->slots[i] - HandCursor >= 0) {
                        PadKey = 0x2000;
                    } else {
                        PadKey = 0x8000;
                    }
                    for (j = 0; j < ABS(pTask->slots[i] - HandCursor); j++) {
                        pCtl->ids[QueCount++] = PadKey;
                    }
                    pCtl->ids[QueCount++] = 0x1000;
                    HandCursor = pTask->slots[i];
                }
            }
            pCtl->ids[QueCount++] = 64;
            pCtl->ids[QueCount++] = 64;
        }
        break;
    case 12:
        pCtl->ids[QueCount++] = 64;
        pCtl->ids[QueCount++] = 2;
        pCtl->ids[QueCount++] = 64;
        if (pTask->target >> 8 != SzDuel_GetTurnOwner()) {
            pCtl->ids[QueCount++] = SzDuel_GetTurnOwner() == 0 ? 0x2000 : 0x8000;
        }
        for (i = 0; i < (pTask->target & 0xf); i++) {
            pCtl->ids[QueCount++] = 0x4000;
        }
        pCtl->ids[QueCount] = 64;
        break;
    case 13:
        pCtl->ids[QueCount++] = 64;
        pCtl->ids[QueCount++] = 2;
        pCtl->ids[QueCount++] = 64;
        for (i = 0; i < pTask->target; i++) {
            pCtl->ids[QueCount++] = 0x4000;
        }
        pCtl->ids[QueCount] = 64;
        break;
    default:
        pCtl->ids[QueCount] = 64;
        break;
    }
    pCtl->mode++;
    return 1;
}
#undef ABS
#undef MOVE_X
#undef MOVE_Z

/* The absolute value of `value`. */
static inline s32 absolute_00276B60(s32 value) {
    if (value >= 0) {
        return value;
    }
    return -value;
}

/* The first step for unit (nSide, nID) on (nX, nZ) toward goal (gX, gZ). */
s32 TaLogic_GetQueueXY_Move1(s32 nSide, s32 nID, s32 nX, s32 nZ, s32 gX, s32 gZ) {
    extern s32 TaLogic_IsPassRoot();
    s16 cell;

    cell = SzDuel_GetMapUnitID(gX, gZ);
    if ((((gX < nX) ? nX : gX) - ((nX < gX) ? nX : gX)) +
        (((gZ < nZ) ? nZ : gZ) - ((nZ < gZ) ? nZ : gZ)) == 1) {
        return 1;
    }
    switch (absolute_00276B60(nX - gX)) {
    case 0:
        return 1;
    case 2:
        return 1;
    case 1:
        if (TaLogic_IsPassRoot(nSide, nID, nX, nZ, gX, nZ, &cell) == 1) {
            return 1;
        }
        return 0;
    }
    return 1;
}

/* The computer opponent's task entry for unit `OwnerID`. */
s32 TaLogic_GetActionUnitFromOwnerID(u16 *pCtl, s32 OwnerID) {
    s32 i = 0;

    do {
        if (OwnerID == *pCtl) {
            return i;
        }
        i++;
        pCtl += 8;
    } while (i < 0x16);
    return -1;
}

struct jp_9a533;
extern struct jp_9a533 *func_001DF540_b(int a, int b);
extern int func_00278510_b(struct jp_9a533 *pVarInfo, int wUnit, int bWarnLvl, int x, int z,
                              unsigned char fView);
#define LO(a, b) ((a) < (b) ? (a) : (b))
#define HI(a, b) ((b) < (a) ? (a) : (b))

/* How dangerous square (nX, nZ) is for unit `nOwnerID`: enemies within `bWarnRange` that beat it at level
   `bWarnLvl`. */
int TaLogic_GetUnitWarning(int nX, int nZ, int nOwnerID, unsigned char bWarnRange, unsigned short bWarnLvl, unsigned char fView)
{
    struct jp_9a533 *pVarInfo;
    unsigned short wUnitLst[22];
    int Dist;
    int Danger;
    int i;
    int v1;
    int Loc;

    for (i = 0; i < 22; i++) {
        wUnitLst[i] = 0xffff;
    }
    pVarInfo = func_001DF540_b(nOwnerID >> 8, nOwnerID & 0xff);
    TaLogic_GetUnitCtlLst(Ta_IsUnitControl2(pVarInfo) == 0 ? 1 : 0, wUnitLst, 29, fView);
    Danger = 0;
    for (i = 0; i < TaLogic_GetUnitCtlLstLen(wUnitLst); i++) {
        if (func_001DF540_b(wUnitLst[i] >> 8, wUnitLst[i] & 0xff) != 0) {
            Loc = SzDuel_GetUnitLoc(wUnitLst[i] >> 8, wUnitLst[i] & 0xff);
            Dist = (HI(nX, Loc & 0xff) - LO(nX, Loc & 0xff)) + (HI(nZ, Loc >> 8) - LO(nZ, Loc >> 8));
            if (Dist <= bWarnRange && Dist > 0) {
                if (Dist < bWarnRange && Dist > 0) {
                    v1 = func_00278510_b(pVarInfo, wUnitLst[i], bWarnLvl, Loc & 0xff, Loc >> 8, fView);
                    if (v1 > 0) {
                        v1 = 0;
                    } else {
                        v1 = -v1;
                    }
                    Danger += v1 / Dist;
                }
            }
        }
    }
    return Danger;
}
#undef LO
#undef HI

typedef struct {
    u16 field_0;
    u8 field_2;
    u8 pad_3;
    s16 field_4;
    u8 pad_6[10];
    u8 field_10;
} Data_00276EC0;

/* The cheapest "do nothing" task: the unit stays where it is. */
void TaLogic_GetMinimumTask_DoNone(u16 *arg0, s32 arg1, void *arg2) {
    Data_00276EC0 *dest = arg2;
    u16 temp_v0;

    dest->field_0 = *arg0;
    dest->field_2 = 6;
    temp_v0 = *arg0;
    dest->field_4 = SzDuel_GetUnitLoc((s32) temp_v0 >> 8, temp_v0 & 0xFF);
    dest->field_10 = 2;
}

typedef struct {
    u16 position;
    u8 flag;
    u8 pad;
} Slot_00276F10;

s32 func_00277160_b(void *arg0, s32 arg1, s32 arg2, void *arg3, s32 arg4, s32 arg5, u8 arg6, u8 arg7, u8 arg8,
                  s32 arg9, s32 arg10);

/* The nearest card a unit (record `pVarInfo`) on (nX, nZ) can reach that matches the kind and face filters. */
s32 TaLogic_GetNearCard2(void *pVarInfo, s32 nX, s32 nZ, s32 nSide, s32 bChase, s32 sKind, s32 fOpen, s32 fDef, s32 fView,
                  s32 bWarnLvl) {
    s32 state;
    s32 i;
    s32 result;
    u8 work[112];
    Slot_00276F10 slots[22];
    s16 c;
    s16 b;
    u16 a;
    extern s32 TaLogic_GetNearUnitL2();
    extern void TaLogic_InitIgnoreLst();

    if ((u32)SzGame_GetHSyncCount() > 12000) {
        return -1;
    }
    for (i = 0; i < 22; i++) {
        slots[i].position = 0xFFFF;
        slots[i].flag = 0xFF;
    }
    TaLogic_InitIgnoreLst(work);
    a = 0;
    b = 0;
    c = 0;
    state = 0;
    for (i = 1; i <= (u8)bChase; i++) {
        state = TaLogic_GetNearUnitL2(state, pVarInfo, nX, nZ, nSide, (u8)i, fView, bWarnLvl, slots, &a, &c, &b, work);
        result = func_00277160_b(pVarInfo, nX, nZ, slots, bChase, sKind, fOpen, fDef, fView, bWarnLvl, a);
        if (result >= 0) {
            return result;
        }
        if ((u32)SzGame_GetHSyncCount() > 12000) {
            return -1;
        }
    }
    return -1;
}

/* The nearest enemy unit a unit (record `pVarInfo`) on (nX, nZ) can reach and beat, searched by a move tree. */
void TaLogic_GetNearUnitL2(s32 pTree, s32 pVarInfo, s32 nX, s32 nZ,
                   s32 nSide, s32 bChase, s32 fView, s32 bWarnLvl,
                   s32 nUnitLst, s32 wUnitNum, s32 wSize, s32 wNodeCount, s32 wIgnoreLst) {
    extern u8 *TaLogic_GetNearUnitPickUpTree();

    TaLogic_GetNearUnitPickUpTree(pTree, 0, pVarInfo, nX, nZ, nSide, bChase, fView,
                   (u16) bWarnLvl, 0, (s64) wSize, (s64) wNodeCount,
                   (s64) nUnitLst, (s64) wUnitNum, (s64) wIgnoreLst);
}

/* From the dotr-decomp CC0 bundle (commit 88c32bb2), chatC/imp/conv.py. */

struct jp_9a533_277160;
struct jp_9b50e {
    unsigned short nUnitID;
    unsigned char bDist;
};
extern void *func_001DF540_277160(int a, int b);
extern int func_00278510_277160(struct jp_9a533_277160 *pVarInfo, int wUnit, int bWarnLvl, int x, int z, unsigned char fView);
#define MIN(a, b) ((b) < (a) ? (b) : (a))
#define MAX(a, b) ((a) < (b) ? (b) : (a))
#define ID_277160(w) (w) >> 8, (w) & 0xFF

/* The nearest unit of list `nUnitLst_v` to square (nX, nZ) matching `sKey`. */
int TaLogic_GetNearUnitL3(void *pVarInfo_v, int nX, int nZ, void *nUnitLst_v, unsigned char bChase, int sKey, unsigned char fOpen, unsigned char fDef, unsigned char fView, int bWarnLvl, unsigned short wUnitNum)
{
    struct jp_9a533_277160 * pVarInfo = pVarInfo_v;
    struct jp_9b50e * nUnitLst = nUnitLst_v;
    int i;
    int Loc;
    int Dist;
    int v1;
    int v2;
    unsigned char bMin;
    unsigned short wUnit;
    unsigned short wLoc;
    struct jp_9b50e *p;

    p = nUnitLst;
    bMin = 7;
    wUnit = 0xFFFF;
    wLoc = wUnit;
    for (i = 0; i < wUnitNum; i++) {
        if (func_001DF540_277160(ID_277160(p->nUnitID)) != 0) {
            Loc = SzDuel_GetUnitLoc(ID_277160(p->nUnitID));
            if ((MAX(Loc & 0xFF, nX) - MIN(Loc & 0xFF, nX)) + (MAX(Loc >> 8, nZ) - MIN(Loc >> 8, nZ)) <= bChase
                && TaLogic_IsStatusMatch(SzDuel_GetUnitStatus(ID_277160(p->nUnitID), 2), fOpen) == 1
                && TaLogic_IsStatusMatch(SzDuel_GetUnitStatus(ID_277160(p->nUnitID), 5), fDef) == 1
                && TaLogic_IsUnitCategory(ID_277160(p->nUnitID), sKey) == 1) {
                Dist = p->bDist;
                if (Dist <= bChase && Dist > 0) {
                    if (Dist < bMin) {
                        bMin = (MAX(Loc & 0xFF, nX) - MIN(Loc & 0xFF, nX)) + (MAX(Loc >> 8, nZ) - MIN(Loc >> 8, nZ));
                        wUnit = p->nUnitID;
                        wLoc = Loc;
                        bChase = Dist;
                    } else if (Dist == bMin) {
                        v1 = func_00278510_277160(pVarInfo, p->nUnitID, bWarnLvl, Loc & 0xFF, Loc >> 8, fView);
                        v2 = func_00278510_277160(pVarInfo, wUnit, bWarnLvl, wLoc & 0xFF, wLoc >> 8, fView);
                        if ((v1 > 0 && v2 > 0 && v1 > v2) || (v1 > 0 && v2 <= 0)) {
                        wUnit = p->nUnitID;
                        bMin = (MAX(Loc & 0xFF, nX) - MIN(Loc & 0xFF, nX)) + (MAX(Loc >> 8, nZ) - MIN(Loc >> 8, nZ));
                        wLoc = Loc;
                        bChase = Dist;
                        }
                    }
                }
            }
        }
        p++;
    }
    if (wUnit == 0xFFFF) {
        return -1;
    }
    return wUnit;
}
#undef MIN
#undef MAX
#undef ID_277160

/* The nearest unit of list `nUnitLst` to (nX, nZ) to follow (key `sKey`, face filters `fOpen`, `fDef`). */
s32 TaLogic_GetFollowNearUnit(s32 nX, s32 nZ, void *nUnitLst, s32 bChase, s32 sKey, u8 fOpen, u8 fDef, u16 wUnitNum) {
    extern s32 SzDuel_GetUnitCardNo();
    s32 i;
    s32 loc;
    s32 temp_s2;
    u16 var_s3;
    u8 *var_s4;
    s32 spA0;
    s32 temp_v0_6;

    u8 var_fp;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v1;
    s32 var_a0;
    s32 var_a1;
    s32 var_v0_3;
    s32 var_v1_2;
    s32 var_a0_2;
    s32 var_a1_2;
    s32 y;
    s32 x;
    s32 y2;
    s32 x2;
    u16 temp_v0;
    u16 temp_v0_2;
    u16 temp_v0_3;
    u16 temp_v0_4;
    u16 temp_v0_5;
    s32 temp_v0_7;

    var_s4 = nUnitLst;
    var_fp = 7;
    var_s3 = 0xFFFF & 0xFFFF;
    for (i = 0; i < wUnitNum; i++) {
        temp_v0 = *(u16 *)var_s4;
        if (SzDuel_GetUnit((s32) temp_v0 >> 8, temp_v0 & 0xFF) != 0) {
            temp_v0_2 = *(u16 *)var_s4;
            loc = SzDuel_GetUnitLoc((s32) temp_v0_2 >> 8, temp_v0_2 & 0xFF);
            temp_v0_3 = *(u16 *)var_s4;
            if (TaLogic_IsStatusMatch(SzDuel_GetUnitStatus((s32) temp_v0_3 >> 8, temp_v0_3 & 0xFF, 2), fOpen) == 1) {
                temp_v0_4 = *(u16 *)var_s4;
                if (TaLogic_IsStatusMatch(SzDuel_GetUnitStatus((s32) temp_v0_4 >> 8, temp_v0_4 & 0xFF, 5), fDef) == 1) {
                    temp_v0_5 = *(u16 *)var_s4;
                    if (TaLogic_IsUnitCategory((s32) temp_v0_5 >> 8, temp_v0_5 & 0xFF, sKey) == 1) {
                        temp_s2 = var_s4[2];
                        if (temp_s2 <= (u8) bChase) {
                          if ((s32) temp_s2 > 0) {
                            temp_v0_6 = var_fp & 0xFF;
                            if ((s32) temp_s2 < temp_v0_6) {
                                y = loc >> 8;
                                if (nZ < y) {
                                    var_v0_2 = nZ;
                                } else {
                                    var_v0_2 = y;
                                }
                                if (y < nZ) {
                                    var_a0 = nZ;
                                } else {
                                    var_a0 = y;
                                }
                                x = loc & 0xFF;
                                if (nX < x) {
                                    var_v1 = nX;
                                } else {
                                    var_v1 = x;
                                }
                                if (x < nX) {
                                    var_a1 = nX;
                                } else {
                                    var_a1 = x;
                                }
                                var_s3 = *(u16 *)var_s4;
                                var_fp = ((var_a1 - var_v1) + (var_a0 - var_v0_2)) & 0xFF;
                                bChase = temp_s2 & 0xFF;
                            } else if (temp_s2 == temp_v0_6) {
                                temp_v0_7 = SzDuel_GetCardConstInfo(SzDuel_GetUnitCardNo(*(u16 *)var_s4 >> 8, *(u16 *)var_s4 & 0xFF))[3];
                                spA0 = (s32) temp_v0_7;
                                if ((s32) SzDuel_GetCardConstInfo(SzDuel_GetUnitCardNo(var_s3 >> 8, var_s3 & 0xFF))[3] < spA0) {
                                    y2 = loc >> 8;
                                    var_s3 = *(u16 *)var_s4;
                                    if (nZ < y2) {
                                        var_v0_3 = nZ;
                                    } else {
                                        var_v0_3 = y2;
                                    }
                                    if (y2 < nZ) {
                                        var_a0_2 = nZ;
                                    } else {
                                        var_a0_2 = y2;
                                    }
                                    x2 = loc & 0xFF;
                                    if (nX < x2) {
                                        var_v1_2 = nX;
                                    } else {
                                        var_v1_2 = x2;
                                    }
                                    if (x2 < nX) {
                                        var_a1_2 = nX;
                                    } else {
                                        var_a1_2 = x2;
                                    }
                                    var_fp = ((var_a1_2 - var_v1_2) + (var_a0_2 - var_v0_3)) & 0xFF;
                                    bChase = temp_s2 & 0xFF;
                                }
                            }
                          }
                        }
                    }
                }
            }
        }
        var_s4 += 4;
    }
    var_v0 = var_s3 & 0xFFFF;
    if (var_v0 == 0xFFFF) {
        var_v0 = -1;
    }
    return var_v0;
}

typedef struct Visit_002777F0 {
    u16 id;
    u8 depth;
    u8 pad;
} Visit_002777F0;

/* Grows the move tree from a node, noting enemies the moving card can beat. */
u8 *TaLogic_GetNearUnitPickUpTree(u8 *node, s32 parent, s32 card, s32 x, s32 y,
                  s32 owner, u8 limit, s32 flags, u16 value, u8 depth,
                  u16 *pool, u16 *poolCount, void *visited, u16 *visitCount,
                  s32 context) {
    s32 count;
    s32 minY;
    u8 initial;
    u32 maxX;
    u32 maxY;
    u8 *next;
    u32 range;
    s32 nextDepth;
    s32 radius;
    s32 col;
    s32 row;
    s32 reach;
    u8 **child;
    s32 allocated;

    extern s32 TaLogic_IsUnitWin4();
    extern s32 TaLogic_RootTreeAloc();

    reach = GetMoveRange(card, x, y);
    if (card == 0) {
        return NULL;
    }
    if ((u32)SzGame_GetHSyncCount() > 0x2EE0U) {
        return NULL;
    }
    if (node == NULL) {
        radius = depth;
        if ((s32)limit < radius) {
            return NULL;
        }
        allocated = TaLogic_RootTreeAloc(pool, poolCount);
        if (allocated == 0) {
            return NULL;
        }
        node = (u8 *)allocated;
        TaLogic_SetRootTreeDat(node, parent, x, y);
        if (SzDuel_GetMapUnit(x, y) != 0 &&
            owner == Ta_IsUnitControl2((void *)SzDuel_GetMapUnit(x, y))) {
            radius = SzDuel_GetMapUnitID(x, y);
            if (TaLogic_IsAdjustUnitLst(visited, radius, (s32)depth) == 0) {
                if ((s32)*visitCount < 0x16) {
                    ((Visit_002777F0 *)visited)[*visitCount].id = SzDuel_GetMapUnitID(x, y);
                    ((Visit_002777F0 *)(((u32)*visitCount << 2) + (u32)visited))->depth = depth;
                    *visitCount = *visitCount + 1;
                }
            }
            if (TaLogic_IsUnitWin4(card, radius, value & 0xFFFF, x, y,
                              flags & 0xFF) < 0) {
                return node;
            }
        }
    }
    radius = reach & 0xF;
    count = 0;
    row = GetCap(0, x - radius);
    if ((u32)(x + radius) >= 7U) {
        maxX = 6;
    } else {
        maxX = x + radius;
    }
    minY = GetCap(0, y - radius);
    maxY = y + radius;
    if (maxY >= 7U) {
        maxY = 6;
    }
    initial = depth != 0 ? 0U : 1U;
    if (row <= (s32)maxX) {
        range = radius + 1;
        nextDepth = depth + 1;
        next = node;
        do {
            col = minY;
            if (col <= (s32)maxY) {
                child = (u8 **)next;
                do {
                    if (row >= 0 && col >= 0 && row < 7 && col < 7 &&
                        (u32)((((row < x) ? x : row) - ((x < row) ? x : row)) +
                              (((col < y) ? y : col) - ((y < col) ? y : col))) < range &&
                        ((((row < x) ? x : row) - ((x < row) ? x : row)) +
                         (((col < y) ? y : col) - ((y < col) ? y : col))) != 0 &&
                        TaLogic_IsPassInvadeRoot2((void *)card, x, y, row, col, NULL, flags,
                                     initial, value) != 0 &&
                        TaLogic_IsRootPast2(node, row, col, x, y, depth) == 0) {
                        child[1] = TaLogic_GetNearUnitPickUpTree(child[1], (s32)node, card, row, col,
                                                owner, limit, flags, value,
                                                (u8)nextDepth, pool, poolCount,
                                                visited, visitCount, context);
                        child++;
                        next += 4;
                        count++;
                    }
                    col++;
                } while ((s32)maxY >= col);
            }
            row++;
        } while ((s32)maxX >= row);
    }
    return node;
}

typedef struct Entry_00277C60 {
    u16 key;
    u8 value;
    u8 pad;
} Entry_00277C60;

/* Whether unit `nUnitID` of list `nUnitLst` is within distance `Dist`. */
s32 TaLogic_IsAdjustUnitLst(void *nUnitLst, s32 nUnitID, s32 Dist) {
    s32 i;
    s32 result;
    Entry_00277C60 *entry;
    u16 key;
    u8 *value;

    i = 0;
    result = 0;
    do {
        entry = &((Entry_00277C60 *)nUnitLst)[i];
        key = entry->key;
        if (nUnitID == key) {
            value = &entry->value;
            if (Dist < *value) {
                *value = Dist;
            }
            result = 1;
        } else if (key == 0xFFFF) {
            i = 0x16;
        }
        i++;
    } while (i < 0x16);
    return result;
}

typedef struct Entry_00277CD0 {
    u16 id;
    u8 cost;
    u8 pad;
} Entry_00277CD0;

/* The nearest card a trap unit (tSide, tID) can catch within `range` of (nX, nZ). */
s32 TaLogic_GetTrapNearCard(s32 tSide, s32 tID, s32 nX, s32 nZ, void *nUnitLst,
                  u8 range, s32 sKey, u8 fOpen, u8 fDef, s32 fView,
                  s32 fallback, u16 count, u8 fTrap) {
    s32 cost;
    Entry_00277CD0 *p = nUnitLst;
    u8 mode = (u8)fView;
    s32 i;
    s32 newScore;
    u8 bestDistance = 7;
    u16 best = 0xFFFF;
    u16 bestPos = best;

    i = 0;

    while (i < count) {
        s32 pos;
        s32 minY;
        s32 minX;
        s32 oldScore;

        if (SzDuel_GetUnit(p->id >> 8, p->id & 0xFF) != 0) {
            pos = SzDuel_GetUnitLoc(p->id >> 8, p->id & 0xFF);
            if ((((pos & 0xFF) < nX ? nX : (pos & 0xFF)) - (nX < (pos & 0xFF) ? nX : (pos & 0xFF))) +
                (((pos >> 8) < nZ ? nZ : (pos >> 8)) - (nZ < (pos >> 8) ? nZ : (pos >> 8))) <= range &&
                TaLogic_IsStatusMatch(SzDuel_GetUnitStatus(p->id >> 8, p->id & 0xFF, 2), fOpen) == 1 &&
                TaLogic_IsStatusMatch(SzDuel_GetUnitStatus(p->id >> 8, p->id & 0xFF, 5), fDef) == 1 &&
                TaLogic_IsUnitCategory(p->id >> 8, p->id & 0xFF, sKey) == 1 &&
                ((TaLogic_CanSeeUnit(p->id >> 8, p->id & 0xFF, mode) == 1 &&
                  TaTrapA_IsTrapAct(tSide, tID, p->id >> 8, p->id & 0xFF, (pos & 0xFF), (pos >> 8)) == 1) ||
                 (TaLogic_CanSeeUnit(p->id >> 8, p->id & 0xFF, mode) == 1 && fTrap == 1))) {
                cost = p->cost;
                if (cost <= range && cost > 0) {
                    if (cost < bestDistance) {
                        s32 maxY;
                        s32 maxX;
                        if (nZ < (pos >> 8)) minY = nZ;
                        else minY = pos >> 8;
                        if ((pos >> 8) < nZ) maxY = nZ;
                        else maxY = pos >> 8;
                        if (nX < (pos & 0xFF)) minX = nX;
                        else minX = pos & 0xFF;
                        if ((pos & 0xFF) < nX) maxX = nX;
                        else maxX = pos & 0xFF;
                        best = p->id;
                        bestDistance = (maxX - minX) + (maxY - minY);
                        bestPos = (u16)pos;
                        range = (u8)cost;
                    } else if (cost == bestDistance) {
                        if (TaLogic_CanSeeUnit(p->id >> 8, p->id & 0xFF, mode) == 1) {
                            newScore = TaLogic_IsUnitWin2(SzDuel_GetUnit(tSide, tID), p->id, (pos & 0xFF), (pos >> 8));
                        } else {
                            newScore = fallback;
                        }
                        if (TaLogic_CanSeeUnit(best >> 8, best & 0xFF, mode) == 1) {
                            oldScore = TaLogic_IsUnitWin2(SzDuel_GetUnit(tSide, tID), best, bestPos & 0xFF, bestPos >> 8);
                        } else {
                            oldScore = fallback;
                        }
                        if (newScore < oldScore) {
                            s32 maxY;
                            s32 maxX;
                            best = p->id;
                            if (nZ < (pos >> 8)) minY = nZ;
                            else minY = pos >> 8;
                            if ((pos >> 8) < nZ) maxY = nZ;
                            else maxY = pos >> 8;
                            if (nX < (pos & 0xFF)) minX = nX;
                            else minX = pos & 0xFF;
                            if ((pos & 0xFF) < nX) maxX = nX;
                            else maxX = pos & 0xFF;
                            bestDistance = (maxX - minX) + (maxY - minY);
                            bestPos = (u16)pos;
                            range = (u8)cost;
                        }
                    }
                }
            }
        }
        p++;
        i++;
    }
    return best == 0xFFFF ? -1 : best;
}

/* Whether a unit's status `Status` matches face filter `fOpen`. */
s32 TaLogic_IsStatusMatch(s32 Status, s32 fOpen) {
    switch (fOpen) {
    case 0:
        if (Status == 0) {
            return 1;
        }
        break;
    case 1:
        if (Status == 1) {
            return 1;
        }
        break;
    case 2:
    default:
        return 1;
    }
    return 0;
}

/* Whether the computer opponent can judge unit (nSide, nID) (face up, or `fView` lets it look). (original: TaLogic_IsJudgeUnitDanger) */
s32 TaLogic_CanSeeUnit(s32 nSide, s32 nID, s32 fView) {
    if (fView != 0) {
        return 1;
    }
    if (SzDuel_GetUnitStatus(nSide, nID, 2) == 1) {
        return 1;
    }
    return 0;
}

/* Whether unit `Unit1` beats unit `Unit2` on square (nX, nZ). */
s32 TaLogic_IsUnitWin(s32 Unit1, s32 Unit2, s32 nX, s32 nZ) {
    return TaLogic_IsUnitWin2(SzDuel_GetUnit(Unit1 >> 8, Unit1 & 0xFF), Unit2, nX, nZ);
}

typedef struct {
    u8 pad0[0x3E];
    u8 unk3E;
    u8 pad3F;
    u8 unk40;
    u8 unk41;
    u8 pad42[0x15];
    s8 low : 3;
    s8 flag : 1;
    s8 high : 4;
} Obj_00278250;

/* Whether a unit (record `pVarInfo`) beats unit `Unit2` on square (nX, nZ): attack against attack or defence,
   bonuses. */
s32 TaLogic_IsUnitWin2(s32 pVarInfo, s32 Unit2, s32 nX, s32 nZ) {
    extern s32 TaUtil_GetUnitDP2(s32, s32, s32);
    extern s32 TaUtil_GetUnitAP2();
    extern s32 TaLogic_GetActOfs(void *, void *);
    Obj_00278250 *obj = (Obj_00278250 *)pVarInfo;
    s32 mine;
    s32 theirs;

    if (obj == NULL) {
        return 0;
    }
    if (TaUtil_IsUnitLeader(obj) == 1) {
        mine = 0;
    } else if ((obj->unk3E >> 5) != 0) {
        mine = 0;
    } else if (obj->unk40 == nX && obj->unk41 == nZ && obj->flag) {
        mine = TaUtil_GetUnitDP2(pVarInfo, nX, nZ);
    } else {
        mine = TaUtil_GetUnitAP2(pVarInfo, nX, nZ);
    }
    mine += TaLogic_GetActOfs(obj, (void *)SzDuel_GetUnit(Unit2 >> 8, Unit2 & 0xFF));
    if (TaUtil_IsUnitLeader((void *)SzDuel_GetUnit(Unit2 >> 8, Unit2 & 0xFF)) == 1) {
        theirs = 0;
    } else if ((SzDuel_GetUnitKind(Unit2 >> 8, Unit2 & 0xFF) >> 5) != 0) {
        theirs = 0;
    } else if (SzDuel_GetUnitStatus(Unit2 >> 8, Unit2 & 0xFF, 5) != 0) {
        theirs = TaUtil_GetUnitDP(Unit2 >> 8, Unit2 & 0xFF, nX, nZ);
    } else {
        theirs = TaUtil_GetUnitAP(Unit2 >> 8, Unit2 & 0xFF, nX, nZ);
    }
    theirs += TaLogic_GetActOfs((void *)SzDuel_GetUnit(Unit2 >> 8, Unit2 & 0xFF), obj);
    return mine - theirs;
}

/* Whether a unit (record `pVarInfo`) on (nX, nZ) is strong enough for warning level `bWarnLvl`. */
s32 TaLogic_IsUnitWin3(s32 pVarInfo, s32 bWarnLvl, s32 nX, s32 nZ) {
    extern s32 TaUtil_GetUnitDP2(s32, s32, s32);
    Obj_00278250 *obj = (Obj_00278250 *)pVarInfo;
    s32 mine;

    if (obj == NULL) {
        return 0;
    }
    if (TaUtil_IsUnitLeader(obj) == 1) {
        mine = 0;
    } else if (obj->unk40 == nX && obj->unk41 == nZ && obj->flag) {
        mine = TaUtil_GetUnitDP2(pVarInfo, nX, nZ);
    } else {
        mine = TaUtil_GetUnitAP2(pVarInfo, nX, nZ);
    }
    if (SzDuel_GetField(nX, nZ) == 9) {
        bWarnLvl = GetCap(0x5DC, bWarnLvl);
    }
    return mine - bWarnLvl;
}

/* Whether a unit (record `pVarInfo`) beats enemy `nEnemyID` on (nX, nZ), judging hidden cards by level `bWarnLvl`. */
void TaLogic_IsUnitWin4(s32 pVarInfo, s32 nEnemyID, s32 bWarnLvl, s32 nX, s32 nZ, s32 fView) {
    if (nEnemyID == -1) {
        TaLogic_IsUnitWin3(pVarInfo, bWarnLvl, nX, nZ);
        return;
    }
    if (TaLogic_CanSeeUnit(nEnemyID >> 8, nEnemyID & 0xFF, fView & 0xFF) == 0) {
        TaLogic_IsUnitWin3(pVarInfo, bWarnLvl, nX, nZ);
        return;
    }
    TaLogic_IsUnitWin2(pVarInfo, nEnemyID, nX, nZ);
}

/* Whether a unit (record `pVarInfo`) beats enemy `nEnemyID` on (nX, nZ), with attribute and effect bonuses. */
s32 TaLogic_IsUnitWin5(s32 pVarInfo, s32 nEnemyID, s32 bWarnLvl, s32 nX, s32 nZ, s32 fView) {
    extern s32 TaLogic_IsUnitWin3();
    extern s32 TaUtil_GetUnitAP2();
    extern s32 TaUtil_GetUnitDP2();
    extern s32 TaLogic_GetActOfs();
    s32 damage;
    s32 defense;
    s32 item;
    s32 card;

    if (pVarInfo == 0) {
        return 0;
    }
    card = nEnemyID >> 8;
    if (nEnemyID == -1) {
        return TaLogic_IsUnitWin3(pVarInfo, bWarnLvl, nX, nZ);
    }
    item = nEnemyID & 0xFF;
    if (TaLogic_CanSeeUnit(card, item, fView & 0xFF) == 0) {
        damage = TaUtil_GetUnitAP2(pVarInfo, nX, nZ);
        defense = TaUtil_GetUnitDP2(pVarInfo, nX, nZ);
    } else {
        if (TaUtil_IsUnitLeader((void *)pVarInfo) == 1) {
            defense = 0;
            damage = 0;
        } else if ((*(u8 *)((u8 *)pVarInfo + 0x3E) >> 5) != 0) {
            defense = 0;
            damage = 0;
        } else {
            damage = TaUtil_GetUnitAP2(pVarInfo, nX, nZ);
            defense = TaUtil_GetUnitDP2(pVarInfo, nX, nZ);
            damage += TaLogic_GetActOfs((void *)pVarInfo, (void *)SzDuel_GetUnit(card, item));
            defense += TaLogic_GetActOfs((void *)pVarInfo, (void *)SzDuel_GetUnit(card, item));
        }

        if (TaUtil_IsUnitLeader((void *)SzDuel_GetUnit(card, item)) == 1) {
            bWarnLvl = 0;
        } else if ((SzDuel_GetUnitKind(card, item) >> 5) != 0) {
            bWarnLvl = 0;
        } else {
            bWarnLvl = TaUtil_GetUnitAP(card, item, nX, nZ);
            bWarnLvl += TaLogic_GetActOfs((void *)SzDuel_GetUnit(card, item), (void *)pVarInfo);
        }
    }

    if (defense < damage) {
        if (damage >= bWarnLvl) {
            return 3;
        }
        return 0;
    }
    if (damage <= defense) {
        return (bWarnLvl < defense) ? 2 : 0;
    }
    return 0;
}

typedef struct Info_002787F0 {
    u32 packed;
    u16 value;
} Info_002787F0;

typedef struct Object_002787F0 {
    u8 pad00[8];
    Info_002787F0 info;
    u8 pad10[0x2E];
    u8 flags;
} Object_002787F0;

/* The attack change a unit (record `pVarInfo`) gets against another (`pVarInfo2`), from attributes. */
u16 TaLogic_GetActOfs(void *pVarInfo, void *pVarInfo2) {
    Object_002787F0 *first = pVarInfo;
    Object_002787F0 *second = pVarInfo2;
    Info_002787F0 *info = &second->info;
    u32 packed = info->packed;
    u8 flags;

    switch (packed >> 8) {
    case 0x1B:
        flags = first->flags;
        if (((packed & 0x3F) == (flags & 0x1F)) && (((s32) flags >> 5) == 0)) {
            return info->value;
        }
        break;
    }
    info = &first->info;
    packed = info->packed;
    switch (packed >> 8) {
    case 0x1B:
        flags = second->flags;
        if (((packed & 0x3F) == (flags & 0x1F)) && (((s32) flags >> 5) == 0)) {
            return info->value;
        }
        break;
    }
    return 0;
}

/* How many monsters (or spells, `fSpell`) side `nSide` has. */
void TaLogic_GetUnitNum(s32 nSide, s32 fSpell) {
    if (fSpell == 1) {
        SzDuel_GetUnitSpellCount(nSide);
        return;
    }
    SzDuel_GetUnitMonsterCount(nSide);
}

typedef struct {
    u8 b[0x18];
} Ent_002788D0;

/* Takes the next node of the fusion tree (`wSize` free, `NodeCount` used). */
void *TaLogic_TreeAloc(u16 *wSize, u16 *NodeCount) {
    u16 idx;

    if ((s64)(u32)(*wSize + 0x38) > 0x10000) {
        return 0;
    }
    idx = *NodeCount;
    *NodeCount = idx + 1;
    *wSize += 0x18;
    return &((Ent_002788D0 *)CAMPAIGN_WORK_ADDR)[idx]; /* the search tree lives in the campaign work area */
}

typedef struct Entry_00278930 {
    s16 id;
    u8 slots[5];
    u8 pad;
    s32 values[4];
} Entry_00278930;

/* Sets up a fusion-tree node for root card `nRoot`, combination `pCombo` and order `nOrder`. */
void TaLogic_InitTree(void *p_fTree, s32 nRoot, s32 pCombo, s32 nOrder) {
    Entry_00278930 *entry = p_fTree;
    s32 i;
    u8 *p;

    entry->id = nRoot;
    i = 0;
    do {
        entry->slots[i] = 0xFF;
        i++;
    } while (i < 5);
    i = 0;
    p = p_fTree;
    do {
        i++;
        *(s32 *)(p + 8) = 0;
        p += 4;
    } while (i < 4);
    if (pCombo == 0) {
        ((u8 *)p_fTree)[2] = nOrder;
        return;
    }
    TaLogic_CopyArray((u8 *)pCombo, (u8 *)p_fTree + 2);
    entry->slots[(u8)TaLogic_GetArrayLength((u8 *)pCombo)] = nOrder;
}

/* The result of combining card `nRoot` with card `nHeap` (fusion or equip), or none. */
s32 TaLogic_GetHandFusion(s32 nRoot, s32 nHeap) {
    s32 handEnchant;
    s32 temp_s1;
    s32 temp_s2;

    temp_s2 = nRoot & 0xFFFF;
    if ((temp_s2 == 0x3E7) || (temp_s1 = nHeap & 0xFFFF, (temp_s1 == 0x3E7))) {
        return 0x3E7;
    }
    handEnchant = Ta_GetHandEnchant(temp_s2, temp_s1);
    if ((handEnchant >> 0x10) == 0) {
        if (TaEnc_IsEncDo(temp_s1) == 1) {
            return handEnchant & 0xFFFF;
        }
    }
    return Fusion(temp_s2, temp_s1) & 0xFFFF;
}

/* From the dotr-decomp CC0 bundle (commit 88c32bb2), chatC/imp/conv.py. */

extern int TaLogic_GetHandFusion_b(unsigned short a, unsigned short b);
extern struct TreeTag *TaLogic_TreeAloc_b(unsigned short *wSize, unsigned short *wCount);
extern void TaLogic_InitTree_b(struct TreeTag *pTree, unsigned short nRoot, unsigned char *pCombo, unsigned char nOrder);

/* Builds the tree of hand combinations side `nSide` can make from root `pRoot`. */
void * TaLogic_GetFusionTree(int nSide, struct TreeTag *p_fTree, unsigned char nOrder, unsigned short pRoot, unsigned char *pCombo, unsigned short *wSize, unsigned short *wCount)
{
    int arNextHand[5];
    int i;
    int j;
    int Res;
    int nCardNo;

    TaHand_GetNextHand(nSide, arNextHand);
    if (pCombo != 0) {
        nCardNo = arNextHand[nOrder];
        if (TaHand_CanAffordSummonCost(nSide, nCardNo) == 0) {
            return 0;
        }
        Res = (unsigned short)TaLogic_GetHandFusion_b(pRoot, nCardNo);
        if (Res == 999) {
            return 0;
        }
        if ((p_fTree = TaLogic_TreeAloc_b(wSize, wCount)) == 0) {
            return 0;
        }
        TaLogic_InitTree_b(p_fTree, Res, pCombo, nOrder);
    } else {
        if ((p_fTree = TaLogic_TreeAloc_b(wSize, wCount)) == 0) {
            return 0;
        }
        Res = pRoot;
        TaLogic_InitTree_b(p_fTree, Res, pCombo, nOrder);
    }
    if ((unsigned char)TaLogic_GetArrayLength(p_fTree->nComboLink) == 5) {
        return p_fTree;
    }
    i = j = 0;
    while (i < 5) {
        if (TaLogic_IsUseHandInCombo(i, p_fTree->nComboLink) != 0 || p_fTree->nRoot == 999) {
            i++;
            continue;
        }
        if ((p_fTree->pNextLink[j] = TaLogic_GetFusionTree(nSide, p_fTree->pNextLink[j], i, Res, p_fTree->nComboLink, wSize, wCount)) != 0) {
            j++;
        }
        i++;
    }
    return p_fTree;
}

/* Builds the combination tree for side `nSide` from root `pRoot` and combination `pCombo`. */
void *TaLogic_GetFusionTree2(s32 nSide, s32 p_fTree, s32 nOrder, s32 pRoot,
                    s32 pCombo, u16 *wSize, u16 *wCount) {
    s32 sp60[8];
    void *temp_v0;

    TaHand_GetNextHand(nSide, sp60);
    if (pCombo != 0) {
        return NULL;
    }
    if ((temp_v0 = TaLogic_TreeAloc(wSize, wCount)) == NULL) {
        return NULL;
    }
    TaLogic_InitTree(temp_v0, pRoot & 0xFFFF, pCombo, nOrder);
    return temp_v0;
}

/* Adds hand order `bOrder` to combination `bCombo`. */
void TaLogic_AddEmptyCombo(u8 *bCombo, u8 bOrder) {
    s32 var_a0;
    u8 *temp_a1;
    u8 temp_v1;

    if ((TaLogic_GetArrayLength(bCombo) & 0xFF) != 5) {
        var_a0 = 3;
        do {
            temp_a1 = &bCombo[var_a0];
            temp_v1 = temp_a1[0];
            var_a0 -= 1;
            temp_a1[1] = temp_v1;
        } while (var_a0 >= 0);
        *bCombo = bOrder;
    }
}

/* How many entries a byte list ending in 0xFF holds. */
s32 TaLogic_GetArrayLength(u8 *bArray) {
    s32 index;
    s32 count;

    index = 0;
    count = 0;
    do {
        if (bArray[index] == 0xFF) {
            return count;
        }
        index++;
        count++;
    } while (index < 5);
    return count;
}

/* Copies a byte list ending in 0xFF. */
void TaLogic_CopyArray(u8 *src, u8 *dst) {
    s32 i;

    i = 0;
    do {
        dst[i] = src[i];
        i++;
    } while (i < 5);
}

/* Whether hand card `value` is already in combination `values`. */
s32 TaLogic_IsUseHandInCombo(u8 value, u8 *values) {
    s32 i;

    i = 0;
    do {
        if (value == values[i]) {
            return 1;
        }
        i++;
    } while (i < 5);
    return 0;
}

/* The best result (attack plus defence) of a combination tree. */
u16 *TaLogic_GetFusionRes(u16 *p_fTree) {
    s32 i;
    u16 *fusionRes;
    s32 var_s5;
    u8 *var_s0;
    u16 *var_s1;

    var_s1 = p_fTree;
    if (var_s1 != NULL) {
        var_s5 = (TaHand_GetCardAPDP(*var_s1) >> 0x10) & 0xFFFF;
        i = 0;
        var_s0 = (u8 *) var_s1;
        do {
            fusionRes = TaLogic_GetFusionRes(*(u16 **)(var_s0 + 8));
            if ((fusionRes != NULL) && ((u32) (var_s5 & 0xFFFF) < (u32) (TaHand_GetCardAPDP(*fusionRes) >> 0x10))) {
                var_s5 = (TaHand_GetCardAPDP(*fusionRes) >> 0x10) & 0xFFFF;
                var_s1 = fusionRes;
            }
            i += 1;
            var_s0 += 4;
        } while (i < 4);
    } else {
        return NULL;
    }
    return var_s1;
}

/* The best equip to use for side `nSide` from the tree, kept in `pKeep` (`nKeepDepth` deep). */
s32 TaLogic_GetEnchantQue(s32 nSide, u16 *p_fTree, void **pKeep, s32 nKeepDepth) {
    extern s32 TaLogic_IsKeepEnchant();
    extern s32 TaEnc_GetEncScore();
    s32 entries[8];
    u32 totalHigh;
    u32 totalLow;
    s32 i;
    s32 j;
    s32 id;
    void **target;
    s32 *entry;
    s32 count;
    s32 status;

    totalHigh = (u32)TaHand_GetCardAPDP(*p_fTree) >> 16;
    totalLow = TaHand_GetCardAPDP(*p_fTree) & 0xFFFF;
    TaHand_GetNextHand(nSide, entries);
    status = Ta_IsActiveTrapB(nSide, 0x2B);
    if ((status >= 0) && (SzDuel_GetUnitStatus(status >> 8, status & 0xFF, 4) != 0)) {
        return 0;
    }

    i = 0;
    if (i < TaHand_GetNextHandNum(nSide)) {
        entry = entries;
        count = nKeepDepth & 0xFF;
        do {
            if ((TaLogic_IsUseHandInCombo(i & 0xFF, p_fTree + 1) & 0xFF) == 0) {
                id = *entry;
                if (((TaHand_GetCardKind(*entry) >> 5) == 2) && (*entry != 0x31C) && (*entry != 0x31B) &&
                    ((Ta_GetHandEnchant(*p_fTree, id) >> 16) == 1) &&
                    (TaEnc_IsEncDo(id) == 1)) {
                    if (pKeep != NULL) {
                        j = 0;
                        target = pKeep;
                        goto targets_test_00278F10;
                    targets_body_00278F10:
                        TaLogic_IsKeepEnchant(*target, id, *p_fTree);
                        target++;
                        j++;
                    targets_test_00278F10:
                        if (j < count) {
                            goto targets_body_00278F10;
                        }
                    } else {
                        ((u8 *)p_fTree)[2 + (TaLogic_GetArrayLength(p_fTree + 1) & 0xFF)] = i;
                        totalHigh += TaEnc_GetEncScore(id);
                        totalLow += TaEnc_GetEncScore(id);
                    }
                }
            }
            entry++;
            i++;
        } while (i < TaHand_GetNextHandNum(nSide));
    }
    return (totalHigh << 16) | (totalLow & 0xFFFF);
}

/* The equip result's score of a tree node. */
s32 TaLogic_GetEnchantQue2(s32 arg0, u16 *arg1) {
    u32 temp_s0;

    temp_s0 = TaHand_GetCardAPDP(*arg1) >> 0x10;
    return (temp_s0 << 0x10) | (TaHand_GetCardAPDP(*arg1) & 0xFFFF);
}

typedef struct Condition_00279170 {
    u16 id;
    u16 operation;
    u32 value;
} Condition_00279170;

/* Whether equip card `nEncCardNo` on card `nObjCardNo` is better than the one kept in `pKeep`. */
s32 TaLogic_IsKeepEnchant(void *pKeep, s32 nEncCardNo, s32 nObjCardNo) {
    Condition_00279170 *condition = pKeep;

    if (condition == NULL) {
        return 1;
    }
    if (nEncCardNo != condition->id) {
        return 1;
    }
    switch (condition->operation) {
    case 36:
        if ((TaHand_GetCardAPDP(nObjCardNo) >> 16) >= condition->value) {
            return 1;
        }
        break;
    case 37:
        if ((TaHand_GetCardAPDP(nObjCardNo) >> 16) <= condition->value) {
            return 1;
        }
        break;
    }
    return 0;
}

/* The path for unit (nSide, nID) from (nX, nZ) to goal (gX, gZ), into `pMovePiece`. */
void TaLogic_GetRoot(s32 nSide, s32 nID, s32 pMovePiece, s32 nX,
                   s32 nZ, s32 gX, s32 gZ, s32 gUnitID, u8 bAbort) {
    extern s32 TaLogic_GetRoot2(s32, s32, s32, s32, s32, s32, s32, u8);

    TaLogic_GetRoot2(SzDuel_GetUnit(nSide, nID), pMovePiece, nX, nZ,
                  gX, gZ, gUnitID, bAbort);
}

/* The path for a unit (record `pVarInfo`) from (nX, nZ) to goal (gX, gZ), into `pMovePiece` (`bAbort` stops
   early). */
s32 TaLogic_GetRoot2(s32 pVarInfo, s32 pMovePiece, s32 nX, s32 nZ, s32 gX, s32 gZ, s16 gUnitID, u8 bAbort) {
    extern void TaLogic_InitIgnoreLst();
    u8 scratch[0x6A];
    s16 x;
    s16 y;
    u8 flag_pad;
    u8 flag;
    s32 result;
    u8 level;
    s32 previous;

    flag = 0;
    y = 0;
    x = 0;
    level = 1;
    result = 0;
    if (pVarInfo == 0) {
        return -1;
    }
    TaLogic_InitIgnoreLst(scratch);
    if (SzGame_GetHSyncCount() > 0x2EE0U) {
        return -1;
    }
    if (GetMoveRange(pVarInfo, nX, nZ) == 0) {
        return 0;
    }
    if ((((gX < nX) ? nX : gX) - ((nX < gX) ? nX : gX)) + (((gZ < nZ) ? nZ : gZ) - ((nZ < gZ) ? nZ : gZ)) > (s32)bAbort) {
        return -1;
    }
    while (flag == 0 && (previous = (u8)level, bAbort >= previous)) {
        result = (s32)TaLogic_GetRootTree2((u8 *)result, 0, pVarInfo, nX, nZ, gX, gZ, level, (s8 *)&flag, (s32)&gUnitID, 0, (u16 *)&x, (u16 *)&y, (s32)scratch);
        if (flag == 1) {
            TaLogic_GetShortRoot(pMovePiece, result, gX, gZ);
            return previous;
        }
        if (TaLogic_IsConnectRoot((void *)result, 0, level) == 1) {
            level = (level + 1) & 0xFF;
        } else {
            return -1;
        }
        if (SzGame_GetHSyncCount() > 0x2EE0U) {
            return -1;
        }
    }
    return -1;
}

typedef struct Node_002794E0 {
    s32 parent;
    u8 *children[48];
} Node_002794E0;

/* Grows the path tree from a node toward the goal square. */
u8 *TaLogic_GetRootTree2(u8 *node, s32 parent, s32 card, s32 x, s32 y,
                  s32 targetX, s32 targetY, u8 limit, s8 *found, s32 mode,
                  u8 depth, u16 *pool, u16 *poolEnd, s32 wIgnoreLst) {
    s32 count;
    s32 minY;
    u32 maxX;
    u32 maxY;
    u32 distanceLimit;
    s32 nextDepth;
    s32 range;
    s32 iy;
    s32 ix;
    extern s32 TaLogic_IsPassRoot2();

    range = GetMoveRange(card, x, y);
    if (card == 0) {
        return NULL;
    }
    if (node == NULL) {
        if ((s32)depth > (s32)limit) {
            return NULL;
        }
        if ((node = TaLogic_RootTreeAloc(pool, poolEnd)) == NULL) {
            return NULL;
        }
        TaLogic_SetRootTreeDat(node, parent, x, y);
        if (x == targetX && y == targetY) {
            *found = 1;
            return node;
        }
    }
    range &= 0xF;
    count = 0;
    ix = GetCap(0, x - range);
    if ((u32)(x + range) >= 7U) {
        maxX = 6;
    } else {
        maxX = x + range;
    }
    minY = GetCap(0, y - range);
    maxY = y + range;
    if (maxY >= 7U) {
        maxY = 6;
    }
    if (ix <= (s32)maxX) {
        distanceLimit = range + 1;
        nextDepth = depth + 1;
        while (1) {
            iy = minY;
            if (iy <= (s32)maxY) {
                while (1) {
                    if (ix >= 0 && iy >= 0 && ix < 7 && iy < 7 &&
                        (u32)(((ix < x ? x : ix) - (x < ix ? x : ix)) +
                              ((iy < y ? y : iy) - (y < iy ? y : iy))) < distanceLimit &&
                        (((ix < x ? x : ix) - (x < ix ? x : ix)) +
                         ((iy < y ? y : iy) - (y < iy ? y : iy))) != 0 &&
                        TaLogic_IsPassRoot2(card, x, y, ix, iy, mode) == 1 &&
                        TaLogic_IsRootPast2(node, ix, iy, x, y, depth) == 0) {
                        ((Node_002794E0 *)node)->children[count] =
                            TaLogic_GetRootTree2(((Node_002794E0 *)node)->children[count],
                                         (s32)node, card, ix, iy, targetX, targetY,
                                         limit, found, mode, (u8)nextDepth,
                                         pool, poolEnd, wIgnoreLst);
                        count++;
                    }
                    iy++;
                    if (iy > (s32)maxY) {
                        break;
                    }
                }
            }
            ix++;
            if (ix > (s32)maxX) {
                break;
            }
        }
    }
    return node;
}

/* Whether unit (nSide, nID) can move from (nX, nZ) to (gX, gZ) this turn. */
void TaLogic_IsPassRoot(s32 nSide, s32 nID, s32 nX, s32 nZ,
                   s32 gX, s32 gZ, s32 gUnitID) {
    TaLogic_IsPassRoot2(SzDuel_GetUnit(nSide, nID), nX, nZ, gX, gZ, gUnitID);
}

/* The board distance between (x1, y1) and (x2, y2). */
static inline s32 distance_002798C0(s32 y1, s32 x1, s32 y2, s32 x2) {
    return (((y2 < y1) ? y1 : y2) - ((y1 < y2) ? y1 : y2)) +
           (((x2 < x1) ? x1 : x2) - ((x1 < x2) ? x1 : x2));
}

/* The absolute value of `value`. */
static inline s32 absolute_002798C0(s32 value) {
    if (value >= 0) {
        return value;
    }
    return -value;
}

/* Whether a unit (record `pVarInfo`) can move from (nX, nZ) to (gX, gZ) this turn (fields, units in the way). */
s32 TaLogic_IsPassRoot2(s32 pVarInfo, s32 nX, s32 nZ, s32 gX, s32 gZ, s32 gUnitID) {
    extern s32 Ta_IsVirus_Chk3();
    s32 flags;
    s32 delta;

    flags = GetMoveRange(pVarInfo, nX, nZ);
    if (pVarInfo == 0) {
        return 0;
    }
    if (distance_002798C0(nX, nZ, gX, gZ) == 0) {
        return 1;
    }
    if (distance_002798C0(nX, nZ, gX, gZ) == 1) {
        if ((SzDuel_GetField(gX, gZ) == 8 && !(flags & 0x10)) ||
            (SzDuel_GetField(gX, gZ) == 9 && Ta_IsVirus_Chk3(pVarInfo, gX, gZ) == 1)) {
            return 0;
        }
        if (SzDuel_GetMapUnit(gX, gZ) != 0) {
            u16 tile = *(u16 *)gUnitID;
            if (tile != SzDuel_GetMapUnitID(gX, gZ)) {
                return 0;
            }
        }
        return 1;
    } else if (distance_002798C0(nX, nZ, gX, gZ) == 2) {
        delta = absolute_002798C0(nX - gX);
        switch (delta) {
        case 0: {
            s32 midpoint = (nZ + gZ) >> 1;
            if (TaLogic_IsPassRoot2(pVarInfo, nX, nZ, gX, midpoint, gUnitID) == 1) {
                return TaLogic_IsPassRoot2(pVarInfo, nX, midpoint, gX, gZ, gUnitID);
            }
            break;
        }
        case 2: {
            s32 midpoint = (nX + gX) >> 1;
            if (TaLogic_IsPassRoot2(pVarInfo, nX, nZ, midpoint, gZ, gUnitID) == 1) {
                return TaLogic_IsPassRoot2(pVarInfo, midpoint, nZ, gX, gZ, gUnitID);
            }
            break;
        }
        case 1:
            if (TaLogic_IsPassRoot2(pVarInfo, nX, nZ, gX, nZ, gUnitID) == 1 &&
                TaLogic_IsPassRoot2(pVarInfo, gX, nZ, gX, gZ, gUnitID) == 1) {
                return 1;
            }
            if (TaLogic_IsPassRoot2(pVarInfo, nX, nZ, nX, gZ, gUnitID) == 1 &&
                TaLogic_IsPassRoot2(pVarInfo, nX, gZ, gX, gZ, gUnitID) == 1) {
                return 1;
            }
            return 0;
        default:
            return 0;
        }
    }
    return 0;
}

/* Whether unit (nSide, nID) can run from (nX, nZ) to (gX, gZ) (`fFoot` counts its moves). */
void TaLogic_IsRunPassRoot(s32 nSide, s32 nID, s32 nX, s32 nZ,
                   s32 gX, s32 gZ, s32 gUnitID, s32 fFoot) {
    TaLogic_IsRunPassRoot2(SzDuel_GetUnit(nSide, nID), nX, nZ,
                  gX, gZ, gUnitID, fFoot);
}

/* Whether a unit (record `pVarInfo`) can run from (nX, nZ) to (gX, gZ) (`fFoot` counts its moves). */
s32 TaLogic_IsRunPassRoot2(s32 pVarInfo, s32 nX, s32 nZ, s32 gX, s32 gZ, s32 gUnitID, s32 fFoot) {
    extern s32 Ta_IsVirus_Chk3();
    s32 flags;
    s32 delta;
    s32 tile;
    s32 owner;
    s32 middle;
    u16 current;

    flags = GetMoveRange(pVarInfo, nX, nZ);
    if (pVarInfo == 0) {
        return 0;
    }
    if (distance_002798C0(nX, nZ, gX, gZ) == 0) {
        return 1;
    }
    if (distance_002798C0(nX, nZ, gX, gZ) == 1) {
        if ((SzDuel_GetField(gX, gZ) == 8 && !(flags & 0x10)) ||
            (SzDuel_GetField(gX, gZ) == 9 && Ta_IsVirus_Chk3(pVarInfo, gX, gZ) == 1)) {
            return 0;
        } else {
            if (SzDuel_GetMapUnit(gX, gZ) != 0) {
                current = *(u16 *)gUnitID;
                if (current == SzDuel_GetMapUnitID(gX, gZ)) {
                    return 1;
                }
                if (!(fFoot & 0xFF)) {
                    return 0;
                }
                tile = SzDuel_GetMapUnitID(gX, gZ);
                owner = Ta_IsUnitControl(tile >> 8, tile & 0xFF);
                if (owner == Ta_IsUnitControl2((void *)pVarInfo)) {
                    return 1;
                }
                return 0;
            }
            return 1;
        }
    } else if (distance_002798C0(nX, nZ, gX, gZ) == 2) {
        delta = absolute_002798C0(nX - gX);
        switch (delta) {
        case 0:
            middle = (nZ + gZ) >> 1;
            if (TaLogic_IsPassRoot2(pVarInfo, nX, nZ, gX, middle, gUnitID) == 1) {
                return TaLogic_IsPassRoot2(pVarInfo, nX, middle, gX, gZ, gUnitID);
            }
            break;
        case 2:
            middle = (nX + gX) >> 1;
            if (TaLogic_IsPassRoot2(pVarInfo, nX, nZ, middle, gZ, gUnitID) == 1) {
                return TaLogic_IsPassRoot2(pVarInfo, middle, nZ, gX, gZ, gUnitID);
            }
            break;
        case 1:
            if (TaLogic_IsPassRoot2(pVarInfo, nX, nZ, gX, nZ, gUnitID) == 1 &&
                TaLogic_IsPassRoot2(pVarInfo, gX, nZ, gX, gZ, gUnitID) == 1) {
                return 1;
            }
            if (TaLogic_IsPassRoot2(pVarInfo, nX, nZ, nX, gZ, gUnitID) == 1 &&
                TaLogic_IsPassRoot2(pVarInfo, nX, gZ, gX, gZ, gUnitID) == 1) {
                return 1;
            }
            return 0;
        default:
            return 0;
        }
    }
    return 0;
}

/* The attack path for unit (nSide, nID) from (nX, nZ) to (gX, gZ), into `pMovePiece`. */
void TaLogic_GetInvadeRoot(s32 nSide, s32 nID, s32 pMovePiece, s32 nX, s32 nZ,
                   s32 gX, s32 gZ, s32 gUnitID, s32 fView, u8 bAbort, u16 bWarnLvl) {
    TaLogic_GetInvadeRoot2(SzDuel_GetUnit(nSide, nID), pMovePiece, nX, nZ, gX,
                  gZ, gUnitID, fView, bAbort, bWarnLvl);
}

/* The attack path for a unit (record `pVarInfo`) from (nX, nZ) to (gX, gZ), into `pMovePiece`. */
s32 TaLogic_GetInvadeRoot2(s32 pVarInfo, s32 pMovePiece, s32 nX, s32 nZ, s32 gX, s32 gZ, s32 gUnitID, s32 fView, u8 bAbort, u16 bWarnLvl) {
    extern s32 GetMoveRange(s32, s32, s32);
    extern s32 TaLogic_GetInvadeRootTree2(s32, s32, s32, s32, s32, s32, s32, u8, u8 *, s32 *, s32, u16, s32, s16 *, s16 *, void *);
    extern void TaLogic_InitIgnoreLst();
    u8 scratch[0x6A];
    s16 x;
    s16 y;
    u8 flag_pad;
    u8 flag;
    s32 result;
    u8 level;
    s32 previous;

    flag = 0;
    y = 0;
    x = 0;
    level = 1;
    result = 0;
    if (SzGame_GetHSyncCount() > 0x2EE0U) {
        return -1;
    }
    if (pVarInfo == 0) {
        return -1;
    }
    if (GetMoveRange(pVarInfo, nX, nZ) == 0) {
        return 0;
    }
    if ((((gX < nX) ? nX : gX) - ((nX < gX) ? nX : gX)) + (((gZ < nZ) ? nZ : gZ) - ((nZ < gZ) ? nZ : gZ)) > (s32)bAbort) {
        return -1;
    }
    TaLogic_InitIgnoreLst(scratch);
    while (flag != 1 && (previous = (u8)level, bAbort >= previous)) {
        result = TaLogic_GetInvadeRootTree2(result, 0, pVarInfo, nX, nZ, gX, gZ, level, &flag, &gUnitID, fView, bWarnLvl, 0, &x, &y, scratch);
        if (flag == 1) {
            TaLogic_GetShortRoot(pMovePiece, result, gX, gZ);
            return previous;
        }
        if (TaLogic_IsConnectRoot((void *)result, 0, level) == 1) {
            level = (level + 1) & 0xFF;
        } else {
            return -1;
        }
        if (SzGame_GetHSyncCount() > 0x2EE0U) {
            return -1;
        }
    }
    return -1;
}

/* Grows the attack-path tree from node `pPrev`. */
u8 *TaLogic_GetInvadeRootTree2(u8 *pTree, s32 pPrev, void *pVarInfo, s32 nX, s32 nZ, s32 gX, s32 gZ, u8 bDist, u8 *arg_sp0, s32 *arg_sp8, s32 arg_sp10, u16 arg_sp18, u8 arg_sp20, u16 *arg_sp28, u16 *arg_sp30, s32 arg_sp38) {
    extern s32 GetMoveRange();
    s32 spE0;
    s32 spFC;
    u8 sp100;
    u32 sp110;
    u32 sp120;
    u8 *sp130;
    u32 sp140;
    s32 sp150;
    u8 sp167;
    s32 sp168;
    s32 sp16C;
    s32 temp_s0;
    s32 moveRev;
    s32 var_s0;
    s32 cap;
    u8 *var_s2;
    u8 *var_s6;

    var_s6 = pTree;
    sp16C = gX;
    sp168 = gZ;
    sp167 = bDist;
    moveRev = GetMoveRange(pVarInfo, nX, nZ);
    if (pVarInfo == NULL) {
        return NULL;
    }
    if (var_s6 == NULL) {
        if ((s32) arg_sp20 > (s32) sp167) {
            return NULL;
        }
        if ((var_s6 = TaLogic_RootTreeAloc(arg_sp28, arg_sp30)) == NULL) {
            return NULL;
        }
        TaLogic_SetRootTreeDat(var_s6, pPrev, nX, nZ);
        if ((nX == sp16C) && (nZ == sp168)) {
            *arg_sp0 = 1;
            return var_s6;
        }
    }
    temp_s0 = moveRev & 0xF;
    spE0 = 0;
    cap = GetCap(0, nX - temp_s0);
    if ((u32)(nX + temp_s0) >= 7U) {
        sp110 = 6;
    } else {
        sp110 = nX + temp_s0;
    }
    spFC = GetCap(0, nZ - temp_s0);
    sp120 = nZ + temp_s0;
    if (sp120 >= 7U) {
        sp120 = 6;
    }
    sp100 = (arg_sp20 != 0) ? 0U : 1U;
    if (cap <= (s32) sp110) {
        sp140 = temp_s0 + 1;
        sp150 = arg_sp20 + 1;
        sp130 = var_s6;
        do {
            var_s0 = spFC;
            if (var_s0 <= (s32) sp120) {
                var_s2 = sp130;
                do {
                    if ((cap >= 0) && (var_s0 >= 0) && (cap < 7) && (var_s0 < 7) && ((u32) ((((cap < nX) ? nX : cap) - ((nX < cap) ? nX : cap)) + (((var_s0 < nZ) ? nZ : var_s0) - ((nZ < var_s0) ? nZ : var_s0))) < sp140) && (((((cap < nX) ? nX : cap) - ((nX < cap) ? nX : cap)) + (((var_s0 < nZ) ? nZ : var_s0) - ((nZ < var_s0) ? nZ : var_s0))) != 0)) {
                        if ((TaLogic_IsPassInvadeRoot2(pVarInfo, nX, nZ, cap, var_s0, arg_sp8, arg_sp10, sp100, arg_sp18) == 1) && (TaLogic_IsRootPast2(var_s6, cap, var_s0, nX, nZ, arg_sp20) == 0)) {
                            *(u8 **)(var_s2 + 4) = TaLogic_GetInvadeRootTree2(*(u8 **)(var_s2 + 4), (s32)var_s6, pVarInfo, cap, var_s0, sp16C, sp168, sp167, arg_sp0, arg_sp8, arg_sp10, arg_sp18, (u8)sp150, arg_sp28, arg_sp30, arg_sp38);
                        }
                        var_s2 += 4;
                        sp130 += 4;
                        spE0 += 1;
                    }
                    var_s0 += 1;
                } while (var_s0 <= (s32) sp120);
            }
            cap += 1;
        } while (cap <= (s32) sp110);
    }
    return var_s6;
}

/* The board distance between (x1, y1) and (x2, y2). */
static inline s32 distance_0027A710(s32 y1, s32 x1, s32 y2, s32 x2) {
    return (((y2 < y1) ? y1 : y2) - ((y1 < y2) ? y1 : y2)) +
           (((x2 < x1) ? x1 : x2) - ((x1 < x2) ? x1 : x2));
}

/* Whether a unit (record `pVarInfo`) can attack its way from (nX, nZ) to (gX, gZ). */
s32 TaLogic_IsPassInvadeRoot2(void *pVarInfo, s32 nX, s32 nZ, s32 gX, s32 gZ,
                  s32 *gUnitID, s32 fView, u8 Node0, u16 bWarnLvl) {
    s32 flags;
    s32 dy;
    extern s32 TaLogic_IsUnitWin3();

    flags = GetMoveRange((s32)pVarInfo, nX, nZ);
    if (pVarInfo == NULL) {
        return 0;
    }
    if (distance_0027A710(nX, nZ, gX, gZ) == 0) {
        return 1;
    }
    if (distance_0027A710(nX, nZ, gX, gZ) == 1) {
        s32 cell;
        s32 y;
        s32 x;
        s32 result;

        if ((SzDuel_GetField(gX, gZ) == 8 && !(flags & 0x10)) ||
            (SzDuel_GetField(gX, gZ) == 9 &&
             Ta_IsVirus_Chk3(pVarInfo, gX, gZ) == 1)) {
            return 0;
        }
        if (SzDuel_GetMapUnit(gX, gZ) == 0) {
            return 1;
        }
        cell = SzDuel_GetMapUnitID(gX, gZ);
        if (gUnitID != NULL && cell == *gUnitID) {
            return 1;
        }
        y = cell >> 8;
        x = cell & 0xFF;
        if (Ta_IsUnitControl(y, x) != Ta_IsUnitControl2(pVarInfo)) {
            if (TaLogic_CanSeeUnit(y, x, fView) != 0) {
                result = TaLogic_IsUnitWin2((s32)pVarInfo, cell, gX, gZ) > 0;
            } else {
                result = TaLogic_IsUnitWin3((s32)pVarInfo, bWarnLvl, gX, gZ) > 0;
            }
            if (result) {
                return 1;
            }
            return 2;
        } else {
            if (x != 0) {
                return Node0 == 1 ? 0 : 1;
            }
            return 0;
        }
    }
    if (distance_0027A710(nX, nZ, gX, gZ) == 2) {
        dy = nX - gX;
        dy = dy >= 0 ? dy : -dy;
        switch (dy) {
        case 0: {
            s32 midX = (nZ + gZ) >> 1;
            if (TaLogic_IsPassInvadeRoot2(pVarInfo, nX, nZ, gX, midX, gUnitID, fView, Node0, bWarnLvl) == 1) {
                return TaLogic_IsPassInvadeRoot2(pVarInfo, nX, midX, gX, gZ, gUnitID, fView, Node0, bWarnLvl);
            }
            goto failed;
        }
        case 2: {
            s32 midY = (nX + gX) >> 1;
            if (TaLogic_IsPassInvadeRoot2(pVarInfo, nX, nZ, midY, gZ, gUnitID, fView, Node0, bWarnLvl) == 1) {
                return TaLogic_IsPassInvadeRoot2(pVarInfo, midY, nZ, gX, gZ, gUnitID, fView, Node0, bWarnLvl);
            }
            goto failed;
        }
        case 1:
            if (TaLogic_IsPassInvadeRoot2(pVarInfo, nX, nZ, gX, nZ, gUnitID, fView, Node0, bWarnLvl) == 1 &&
                TaLogic_IsPassInvadeRoot2(pVarInfo, gX, nZ, gX, gZ, gUnitID, fView, Node0, bWarnLvl) == 1) {
                return 1;
            }
            if (TaLogic_IsPassInvadeRoot2(pVarInfo, nX, nZ, nX, gZ, gUnitID, fView, Node0, bWarnLvl) == 1 &&
                TaLogic_IsPassInvadeRoot2(pVarInfo, nX, gZ, gX, gZ, gUnitID, fView, Node0, bWarnLvl) == 1) {
                return 1;
            }
            return 0;
        default:
            return 0;
        }
    }
failed:
    return 0;
}

/* Whether a path tree reaches depth `bDepth` within distance `Dist`. */
s32 TaLogic_IsConnectRoot(void *pTree, u8 bDepth, u8 Dist) {
    s32 i;
    void **children;
    s32 nextDepth;
    s32 result;

    if (pTree != NULL) {
        if (bDepth == Dist) {
            return 1;
        }
        nextDepth = bDepth + 1;
        children = pTree;
        i = 0;
        do {
            result = TaLogic_IsConnectRoot(children[1], nextDepth, Dist);
            if (result == 1) {
                return result;
            }
            i++;
            children++;
        } while (i < 12);
    }
    return 0;
}

/* The shortest path in tree `pTree` to goal (gX, gZ), into `pMovePiece`. */
void TaLogic_GetShortRoot(s32 pMovePiece, s32 pTree, s32 gX, s32 gZ) {
    s32 sp18;
    u8 sp1F;

    sp1F = 0xFF;
    sp18 = 0;
    TaLogic_DoGetShortRoot(pMovePiece, &sp18, &sp1F, pTree, gX, gZ, pMovePiece, 0);
}

typedef struct Position_0027ACB0 {
    u8 x : 4;
    u8 y : 4;
    u8 nextX : 4;
    u8 nextY : 4;
} Position_0027ACB0;

/* Walks the path tree for the shortest path to the goal (recursive). */
void TaLogic_DoGetShortRoot(s32 first, s32 *count, u8 *bestDepth, s32 node,
                   s32 x, s32 y, s32 closest, u8 depth) {
    s32 i;

    if (node != 0) {
        if (((Position_0027ACB0 *)node)->x == x &&
            (*(u8 *)node >> 4) == y) {
            s32 currentDepth = (u8)depth;

            if (currentDepth < *bestDepth) {
                s32 position;

                *count = 0;
                *bestDepth = depth;
                position = (u8)TaLogic_GetNextPiece((void *)node, 0);
                if (position < 0) {
                    ((Position_0027ACB0 *)closest)->x = x;
                    ((Position_0027ACB0 *)closest)->y = y;
                } else {
                    ((Position_0027ACB0 *)closest)->x = (u8)position & 0xF;
                    ((Position_0027ACB0 *)closest)->y = (u8)position >> 4;
                }
                ((Position_0027ACB0 *)closest)->nextX = 0xF;
                ((Position_0027ACB0 *)closest)->nextY = 0xF;
            } else if (*bestDepth == currentDepth) {
                s32 position;

                *count += 1;
                position = (u8)TaLogic_GetNextPiece((void *)node, 0);
                if (position < 0) {
                    ((Position_0027ACB0 *)first)->nextX = x;
                    ((Position_0027ACB0 *)first)->nextY = y;
                } else {
                    ((Position_0027ACB0 *)first)->nextX = (u8)position & 0xF;
                    ((Position_0027ACB0 *)first)->nextY = (u8)position >> 4;
                }
            }
            return;
        } else {
            s32 *child = (s32 *)node;
            s32 nextDepth = (u8)depth + 1;

            i = 0;
            do {
                TaLogic_DoGetShortRoot(first, count, bestDepth, child[1], x, y,
                              closest, nextDepth);
                i++;
                child++;
            } while (i < 12);
        }
    }
}

typedef struct Node_0027AF20 {
    u8 value;
    u8 padding[0x33];
    struct Node_0027AF20 *next;
} Node_0027AF20;

/* The next square of a path tree at `depth`. */
u8 TaLogic_GetNextPiece(void *pTree, u8 depth) {
    Node_0027AF20 *node = pTree;
    Node_0027AF20 *next;

    if (depth >= 7) {
        return 0xFFU;
    }
    next = node->next;
    if (next == NULL) {
        return 0xFFU;
    }
    if (next->next == NULL) {
        return node->value;
    }
    return TaLogic_GetNextPiece(next, depth + 1);
}

/* Fills path-tree node `pTree` for square (nX, nZ) after node `pPrev`. */
void TaLogic_SetRootTreeDat(void *pTree, s32 pPrev, s32 nX, s32 nZ) {
    s32 i;
    s32 *var_a3;

    *(s8 *)pTree = (s8) ((nZ << 4) | nX);
    i = 0;
    var_a3 = pTree;
    do {
        i += 1;
        var_a3[1] = 0;
        var_a3++;
    } while (i < 0xC);
    *(s32 *)((u8 *)pTree + 0x34) = pPrev;
}

typedef struct {
    u8 low : 4;
    u8 high : 4;
} Nibbles_0027AFC0;

/* How many steps the shortest path holds. */
s32 TaLogic_GetMinGoalCount(u8 *pntNext) {
    s32 i;
    s32 count;
    Nibbles_0027AFC0 *entries = (Nibbles_0027AFC0 *)pntNext;

    i = 0;
    count = 0;
    do {
        if (entries[i].low != 0xF && entries[i].high != 0xF) {
            count++;
        }
        i++;
    } while (i < 0xC);
    return count;
}

/* The absolute value of `value`. */
static inline s32 absolute_0027B010(s32 value) {
    if (value >= 0) {
        return value;
    }
    return -value;
}

/* Whether square (nX, nZ) is already on the path tree before depth `bDepth`. */
s32 TaLogic_IsRootPast2(void *pTree, s32 nX, s32 nZ, s32 cX, s32 cZ, u8 bDepth) {
    s32 var_t1;
    s32 var_t2;
    s32 var_t3;
    s32 min_x;
    s32 max_x;
    u8 temp_t4;

    if (bDepth <= 0) {
        return 0;
    }
    if (pTree == NULL) {
        return 0;
    }
    temp_t4 = *(u8 *)pTree;
    if (nX == (temp_t4 & 0xF)) {
        if (nZ == ((s32) temp_t4 >> 4)) {
            return 1;
        }
    }
    var_t2 = (nZ < cZ) ? nZ : cZ;
    var_t3 = (cZ < nZ) ? nZ : cZ;
    min_x = (nX < cX) ? nX : cX;
    max_x = (cX < nX) ? nX : cX;
    if (((max_x - min_x) + (var_t3 - var_t2)) == 2) {
        var_t1 = absolute_0027B010(nX - cX);
        switch (var_t1) {
        case 0:
            if ((nX == (temp_t4 & 0xF)) && (((s32) temp_t4 >> 4) == ((nZ + cZ) >> 1))) {
                return 1;
            }
            break;
        case 1:
            if ((cX == (temp_t4 & 0xF)) || (cZ == ((s32) temp_t4 >> 4))) {
                return 1;
            }
            break;
        case 2:
            if (((temp_t4 & 0xF) == ((nX + cX) >> 1)) && (nZ == ((s32) temp_t4 >> 4))) {
                return 1;
            }
            break;
        }
    }
    return TaLogic_IsRootPast2(*(void **)((u8 *)pTree + 0x34), nX, nZ, cX, cZ, bDepth - 1);
}

/* Takes the next node of the path tree (`wSize` free, `NodeCount` used). */
u8 *TaLogic_RootTreeAloc(u16 *wSize, u16 *NodeCount) {
    u16 temp_a2;

    if ((s64) (u32) (*wSize + 0x38) > 0x10000) {
        return 0;
    }
    temp_a2 = *NodeCount;
    *NodeCount = temp_a2 + 1;
    *wSize += 0x38;
    return (u8 *)CAMPAIGN_WORK_ADDR + temp_a2 * 0x38; /* the search tree lives in the campaign work area */
}

/* Clears a unit's computer-opponent task (`Is1st` on its first turn). */
void TaLogic_InitRogicControl(void *pUnit, u8 Is1st) {
    if (Is1st < 2) {
        if (Is1st == 1) {
            *(u32 *)((u8 *)pUnit + 8) =
                (*(u32 *)((u8 *)pUnit + 8) & 0xFFFF) | 0xFFFF0000;
        } else {
            *(u32 *)((u8 *)pUnit + 8) =
                (*(u32 *)((u8 *)pUnit + 8) & 0xFFFF0000) | 0xFFFF;
        }
    }
}

/* Whether unit (nSide, nID) on (nX, nZ) has an open path to unit (gSide, gID) on (gX, gZ). */
void TaLogic_IsRootOpen(s32 nSide, s32 nID, s32 nX, s32 nZ, s32 gSide,
                   s32 gID, s32 gX, s32 gZ, u8 bAbort) {
    TaLogic_IsRootOpen2(SzDuel_GetUnit(nSide, nID), nX, nZ, gSide, gID,
                  gX, gZ, bAbort);
}

typedef struct {
    u8 low : 4;
    u8 high : 4;
} Nibbles_0027B290;

/* Whether a unit (record `pVarInfo`) on (nX, nZ) has an open path to (gX, gZ). */
s32 TaLogic_IsRootOpen2(s32 pVarInfo, s32 nX, s32 nZ, s32 gSide, s32 gID, s32 gX, s32 gZ, u8 bAbort) {
    extern s32 TaLogic_GetRoot2(s32, void *, s32, s32, s32, s32, u16, u8);
    Nibbles_0027B290 entries[12];
    s32 i;
    s32 pos;
    s32 cost;

    for (i = 0; i < 12; i++) {
        entries[i].low = entries[i].high = 15;
    }
    if (gID == -1) {
        pos = -1;
    } else {
        pos = (gSide << 8) | gID;
    }
    cost = TaLogic_GetRoot2(pVarInfo, entries, nX, nZ, gX, gZ, pos, bAbort);
    if (TaLogic_GetMinGoalCount((u8 *)entries) > 0) {
        return cost;
    }
    return 0;
}

typedef struct Entry_0027B360 {
    u16 id;
    u16 pad2;
    u16 kind;
    u16 pad6;
    u8 pad8[8];
} Entry_0027B360;

/* The computer opponent's unit that can attack its goal right now. */
s32 TaLogic_GetAtkUnitNow(s32 arg0, u16 *arg1, u16 *arg2) {
    u16 cards[22];
    s32 count;
    s32 found;
    s32 i;
    s32 index;
    Entry_0027B360 *entry;

    found = 0;
    for (i = 0; i < 22; i++) {
        cards[i] = 0xFFFF;
    }
    for (i = 0, count = 0; i < TaLogic_GetUnitCtlLstLen(arg1); i++) {
        if (SzDuel_GetUnit(arg1[i] >> 8, arg1[i] & 0xFF) == 0) {
            continue;
        }
        if (SzDuel_GetUnitStatus(arg1[i] >> 8, arg1[i] & 0xFF, 0) != 0) {
            continue;
        }
        index = TaLogic_GetActionUnitFromOwnerID(arg2, arg1[i]);
        if (index < 0) {
            continue;
        }
        entry = (Entry_0027B360 *)arg2 + index;
        if (((entry->kind >> 8) & 0xFF) == 2 && TaLogic_IsAtkNowToGoal(entry, 1) == 1) {
            found = 1;
            cards[count++] = arg1[i];
        } else if ((entry->kind & 0xFF) == 2 && TaLogic_IsAtkNowToGoal(entry, 0) == 1) {
            found = 1;
            cards[count++] = arg1[i];
        }
    }
    if (found == 1) {
        return TaLogic_GetMaxApUnit(cards);
    }
    return -1;
}

typedef union {
    u32 word;
    struct {
        u16 low;
        u16 high;
    } halves;
} Data_0027B520;

typedef struct {
    u16 id;
    u16 pad2;
    u16 kind;
    u16 pad6;
    Data_0027B520 data;
} Entry_0027B520;

#define TARGET_0027B520(entry, high) \
    ((high) == 1 ? (entry)->data.word >> 16 & 0xFFFF : (entry)->data.halves.low)

/* Whether a unit can reach and attack its goal this turn. */
s32 TaLogic_IsAtkNowToGoal(void *pUnit, u8 Is1st) {
    extern s32 TaLogic_IsPassRoot();
    extern s32 GetMoveRange(s32, s32, s32);
    Entry_0027B520 *entry = pUnit;
    u16 target;
    s32 pos;
    s32 other;

    target = TARGET_0027B520(entry, Is1st);
    pos = SzDuel_GetUnitLoc(entry->id >> 8, entry->id & 0xFF);
    other = SzDuel_GetUnitLoc(TARGET_0027B520(entry, Is1st) >> 8, TARGET_0027B520(entry, Is1st) & 0xFF);
    GetMoveRange(SzDuel_GetUnit(entry->id >> 8, entry->id & 0xFF), pos & 0xFF, pos >> 8);
    return (TaLogic_IsPassRoot(entry->id >> 8, entry->id & 0xFF, pos & 0xFF, pos >> 8,
                          other & 0xFF, other >> 8, &target) == 1) ? 1 : 0;
}

/* The unit of list `wUnitLst` with the highest attack. */
s32 TaLogic_GetMaxApUnit(u16 *wUnitLst) {
    s32 Loc;
    s32 i;
    s32 curAP;
    s32 tempAP;
    s32 temp;

    temp = curAP = -1;
    for (i = 1; i < TaLogic_GetUnitCtlLstLen(wUnitLst); i++) {
        Loc = SzDuel_GetUnitLoc(wUnitLst[i] >> 8, wUnitLst[i] & 0xFF);
        if (SzDuel_GetUnitStatus(wUnitLst[i] >> 8, wUnitLst[i] & 0xFF, 4) != 0) {
            tempAP = TaUtil_GetUnitAP(wUnitLst[i] >> 8, wUnitLst[i] & 0xFF, Loc & 0xFF, Loc >> 8);
            if (curAP < tempAP) {
                temp = wUnitLst[i];
                curAP = tempAP;
            }
        }
    }
    return temp;
}

/* The unit of list `wUnitLst` with the highest attack that side `nSide` controls. */
s32 TaLogic_GetMaxApUnit2(void *wUnitLst, s32 nSide) {
    s32 index;
    s32 best;
    s32 selected;
    s32 packed;
    u16 *entry;
    s32 score;
    u16 value;

    best = -1;
    index = 1;
    selected = -1;
    if (index < TaLogic_GetUnitCtlLstLen(wUnitLst)) {
        entry = (u16 *)wUnitLst + 1;
        do {
            value = *entry;
            packed = SzDuel_GetUnitLoc((s32)value >> 8, value & 0xFF);
            value = *entry;
            if (SzDuel_GetUnitStatus((s32)value >> 8, value & 0xFF, 4) != 0 ||
                (value = *entry, nSide == Ta_IsUnitControl((s32)value >> 8, value & 0xFF))) {
                value = *entry;
                score = TaUtil_GetUnitAP((s32)value >> 8, value & 0xFF, packed & 0xFF, packed >> 8);
                if (best < score) {
                    selected = *entry;
                    best = score;
                }
            }
            entry++;
            index++;
        } while (index < TaLogic_GetUnitCtlLstLen(wUnitLst));
    }
    return selected;
}

/* The unit of list `wUnitLst` with the highest attack that side `nSide` controls and is free to act. */
s32 TaLogic_GetMaxApUnit3(u16 *wUnitLst, s32 nSide) {
    extern s32 SzDuel_GetUnitCurseRest(s32, s32);
    extern s32 SzDuel_GetUnitSpellRest(s32, s32);
    s32 i;
    s32 best;
    s32 bestPos;
    s32 cur;
    u16 *p;
    s32 score;

    best = -1;
    bestPos = best;
    i = 1;
    if (i < TaLogic_GetUnitCtlLstLen(wUnitLst)) {
        p = &wUnitLst[1];
        do {
            cur = SzDuel_GetUnitLoc(*p >> 8, *p & 0xFF);
            if (SzDuel_GetUnitStatus(*p >> 8, *p & 0xFF, 4) != 0 ||
                (nSide == Ta_IsUnitControl(*p >> 8, *p & 0xFF) &&
                 SzDuel_GetUnitCurseRest(*p >> 8, *p & 0xFF) == 0 &&
                 SzDuel_GetUnitSpellRest(*p >> 8, *p & 0xFF) == 0)) {
                score = TaUtil_GetUnitAP(*p >> 8, *p & 0xFF, cur & 0xFF, cur >> 8);
                if (best < score) {
                    bestPos = *p;
                    best = score;
                }
            }
            p++;
            i++;
        } while (i < TaLogic_GetUnitCtlLstLen(wUnitLst));
    }
    return bestPos;
}

/* The smaller of `a` and `b`. */
static inline s32 min_0027B9B0(s32 a, s32 b) {
    return (a >= b + 1) ? b : a;
}

/* Whether unit `wUnit` can move at all (not bound, a free square nearby). */
s32 TaLogic_IsUnitReadyMove(s32 wUnit) {
    s32 i;
    s32 j;
    s32 yMax;
    s32 x;
    s32 y;
    s32 pos;
    s32 flags;
    s32 xMax;
    s32 yMin;

    x = wUnit & 0xFF;
    y = (wUnit & 0xFFFF) >> 8;
    if ((pos = SzDuel_GetUnitLoc(y, x)) < 0) {
        return 0;
    }
    if (SzDuel_GetUnitStatus(y, x, 0) != 0) {
        return 0;
    }
    flags = GetMoveRange(SzDuel_GetUnit(y, x), (pos & 0xFF), (pos >> 8));
    i = GetCap(0, (pos & 0xFF) - 1);
    yMin = (pos >> 8) - 1;
    yMax = (pos >> 8) + 1;
    xMax = (pos & 0xFF) + 1;
    for (; i <= min_0027B9B0(xMax, 6); i++) {
        for (j = GetCap(0, yMin); j <= min_0027B9B0(yMax, 6); j++) {
            if ((((pos & 0xFF) > i ? (pos & 0xFF) : i) - ((pos & 0xFF) < i ? (pos & 0xFF) : i)) + (((pos >> 8) > j ? (pos >> 8) : j) - ((pos >> 8) < j ? (pos >> 8) : j)) == 1 &&
                SzDuel_GetMapUnit(i, j) == 0) {
                if (SzDuel_GetField(i, j) != 8 || (flags & 0x10)) {
                    if (SzDuel_GetField(i, j) != 9 || Ta_IsVirus_Chk3((void *)SzDuel_GetUnit(y, x), i, j) != 1) {
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

/* Whether an enemy can attack unit (nSide, nID) this turn. */
s32 TaLogic_IsAttackedNow(s32 nSide, s32 nID, s32 fView) {
    s32 count;
    s32 distance;
    s32 index;
    s32 y;
    u16 values[22];
    s32 packed;
    s32 targetY;
    s32 targetX;
    s32 coords;
    s32 origin;
    u16 *p;
    u16 *current;
    u16 position;
    s32 unit;
    s32 x;
    s32 range;

    extern s32 TaLogic_IsPassRoot();
    extern s32 SzDuel_GetUnitCurseRest();
    extern s32 SzDuel_GetUnitSpellRest();
    extern void TaLogic_GetUnitCtlLst();

    if (SzDuel_GetUnit(nSide, nID) == 0) {
        return 0;
    }
    position = (nSide << 8) | nID;
    current = values;
    count = 0;
    p = current;
    do {
        count++;
        *p++ = 0xFFFF;
    } while (count < 22);
    TaLogic_GetUnitCtlLst(Ta_IsUnitControl(nSide, nID) == 0 ? 1 : 0, values, 31, fView);
    packed = SzDuel_GetUnitLoc(nSide, nID);
    index = 0;
    if (index < TaLogic_GetUnitCtlLstLen(values)) {
        origin = (nSide << 8) | nID;
        targetY = packed >> 8;
        targetX = packed & 0xFF;
        do {
            coords = SzDuel_GetUnitLoc(*current >> 8, *current & 0xFF);
            unit = SzDuel_GetUnit(*current >> 8, *current & 0xFF);
            x = coords & 0xFF;
            y = coords >> 8;
            range = GetMoveRange(unit, x, y);
            distance = ((x < targetX ? targetX : x) - (targetX < x ? targetX : x)) +
                       ((y < targetY ? targetY : y) - (targetY < y ? targetY : y));
            if ((u32)distance <= (u32)(range & 0xF)) {
                if (TaLogic_IsPassRoot(*current >> 8, *current & 0xFF, x, y,
                                  targetX, targetY, &position) == 1 &&
                    TaLogic_IsUnitWin(position, *current, targetX, targetY) <= 0 &&
                    SzDuel_GetUnitCurseRest(*current >> 8, *current & 0xFF) == 0 &&
                    SzDuel_GetUnitSpellRest(*current >> 8, *current & 0xFF) == 0 &&
                    TaLogic_IsSafeTrap(origin, targetX, targetY) == 0) {
                    return 1;
                }
            }
            current++;
            index++;
        } while (index < TaLogic_GetUnitCtlLstLen(values));
    }
    return 0;
}

/* Whether an enemy could attack unit (nSide, nID) on square (nX, nZ) this turn. */
s32 TaLogic_IsAttackedNow2(s32 nSide, s32 nID, s32 nX, s32 nZ, s32 fView) {
    s32 distance;
    s32 origin;
    s32 count;
    u16 *p;
    s32 coords;
    s32 targetY;
    s32 targetX;
    s32 packed;
    u16 *current;
    s32 range;
    u16 position;
    s32 unit;
    s32 y;
    u16 values[22];
    s32 x;
    s32 index;

    extern s32 TaLogic_IsPassRoot();
    extern s32 SzDuel_GetUnitCurseRest();
    extern s32 SzDuel_GetUnitSpellRest();
    extern void TaLogic_GetUnitCtlLst();

    if (SzDuel_GetUnit(nSide, nID) == 0) {
        return 0;
    }
    position = (nSide << 8) | nID;
    current = values;
    count = 0;
    p = current;
    do {
        count++;
        *p++ = 0xFFFF;
    } while (count < 22);
    TaLogic_GetUnitCtlLst(Ta_IsUnitControl(nSide, nID) == 0 ? 1 : 0, values, 31, fView);
    packed = (nZ << 8) | nX;
    index = 0;
    if (index < TaLogic_GetUnitCtlLstLen(values)) {
        origin = (nSide << 8) | nID;
        targetY = packed >> 8;
        targetX = packed & 0xFF;
        do {
            coords = SzDuel_GetUnitLoc(*current >> 8, *current & 0xFF);
            unit = SzDuel_GetUnit(*current >> 8, *current & 0xFF);
            x = coords & 0xFF;
            y = coords >> 8;
            range = GetMoveRange(unit, x, y);
            distance = ((x < targetX ? targetX : x) - (targetX < x ? targetX : x)) +
                       ((y < targetY ? targetY : y) - (targetY < y ? targetY : y));
            if ((u32)distance <= (u32)(range & 0xF)) {
                if (TaLogic_IsPassRoot(*current >> 8, *current & 0xFF, x, y,
                                  targetX, targetY, &position) == 1 &&
                    TaLogic_IsUnitWin(position, *current, targetX, targetY) <= 0 &&
                    SzDuel_GetUnitCurseRest(*current >> 8, *current & 0xFF) == 0 &&
                    SzDuel_GetUnitSpellRest(*current >> 8, *current & 0xFF) == 0 &&
                    TaLogic_IsSafeTrap(origin, nX, nZ) == 0) {
                    return 1;
                }
            }
            current++;
            index++;
        } while (index < TaLogic_GetUnitCtlLstLen(values));
    }
    return 0;
}

/* The units of side `nSide` of category `sKind`, into `wUnitLst`; returns how many. */
void TaLogic_GetUnitCtlLst(s32 nSide, u16 *wUnitLst, s32 sKind, u8 fView) {
    void *card;
    s32 i;
    s32 end;
    u8 count;
    s32 start;

    count = 0;
    switch (sKind) {
    case 0x22:
        end = 1;
        start = 0;
        break;
    case 0x1F:
        end = 11;
        start = 0;
        break;
    case 0x34:
        start = 1;
        end = 11;
        break;
    default:
        start = 1;
        end = 11;
        break;
    }
    for (i = start; i < end; i++) {
        if (count >= 22) {
            return;
        }
        if ((card = (void *)SzDuel_GetUnit(nSide, i)) != 0 && nSide == Ta_IsUnitControl2(card)) {
            if (TaLogic_CanSeeUnit(nSide, i, fView) != 0 || TaLogic_IsUnitCategory(nSide, i, sKind) == 1) {
                wUnitLst[count] = (u16)(nSide << 8) | i;
                count++;
            }
        }
    }
    for (i = start; i < end; i++) {
        if (count >= 22) {
            return;
        }
        if ((card = (void *)SzDuel_GetUnit((nSide == 0) ? 1 : 0, i)) != 0 && nSide == Ta_IsUnitControl2(card)) {
            if (TaLogic_CanSeeUnit((nSide == 0) ? 1 : 0, i, fView) != 0 || TaLogic_IsUnitCategory((nSide == 0) ? 1 : 0, i, sKind) == 1) {
                wUnitLst[count] = i | (((nSide == 0) ? 1 : 0) << 8);
                count++;
            }
        }
    }
}

/* The units of side `nSide` of category `sKind` matching view condition `sCondView`, into `wUnitLst`. */
void TaLogic_GetUnitCtlLst2(s32 nSide, u16 *wUnitLst, s32 sKind, s32 sCondView, u8 fView) {
    void *card;
    s32 i;
    s32 end;
    u8 count;
    s32 start;

    count = 0;
    switch (sKind) {
    case 0x22:
        end = 1;
        start = 0;
        break;
    case 0x1F:
        end = 11;
        start = 0;
        break;
    case 0x34:
        start = 1;
        end = 11;
        break;
    case 0x1D:
        start = 1;
        end = 6;
        break;
    default:
        start = 1;
        end = 11;
        break;
    }
    for (i = start; i < end; i++) {
        if (count >= 22) {
            return;
        }
        if ((card = (void *)SzDuel_GetUnit(nSide, i)) != 0 && nSide == Ta_IsUnitControl2(card)) {
            if (TaLogic_CanSeeUnit(nSide, i, fView) != 0) {
                if (TaLogic_IsUnitCategory(nSide, i, sKind) == 1) {
                    wUnitLst[count] = (u16)(nSide << 8) | i;
                    count++;
                }
            } else if (sCondView == 1) {
                wUnitLst[count] = (u16)(nSide << 8) | i;
                count++;
            }
        }
    }
    for (; start < end; start++) {
        if (count >= 22) {
            return;
        }
        if ((card = (void *)SzDuel_GetUnit((nSide == 0) ? 1 : 0, start)) != 0 && nSide == Ta_IsUnitControl2(card)) {
            if (TaLogic_CanSeeUnit((nSide == 0) ? 1 : 0, start, fView) != 0) {
                if (TaLogic_IsUnitCategory((nSide == 0) ? 1 : 0, start, sKind) == 1) {
                    wUnitLst[count] = start | (((nSide == 0) ? 1 : 0) << 8);
                    count++;
                }
            } else if (sCondView == 1) {
                wUnitLst[count] = start | (((nSide == 0) ? 1 : 0) << 8);
                count++;
            }
        }
    }
}

/* Whether a unit is of a computer-opponent category (monster, magic, leader...). */
s32 TaLogic_IsUnitCategory(s32 arg0, s32 arg1, s32 arg2) {
    switch (arg2) {
    case 0x22:
        if (arg1 != 0) {
            break;
        }
        return 1;
    case 0x1D:
        if ((arg1 > 0) && (arg1 < 6)) {
            return 1;
        }
        break;
    case 0x1E:
        if ((arg1 > 5) && (arg1 < 0xC)) {
            return 1;
        }
        break;
    case 0x1F:
        return 1;
    case 0x34:
        if (arg1 != 0) {
            return 1;
        }
        break;
    default:
        if (arg1 != 0) {
            return 1;
        }
        break;
    }
    return 0;
}

/* How many units a unit list ending in 0xFFFF holds. */
s32 TaLogic_GetUnitCtlLstLen(u16 *values) {
    s32 count;
    s32 iteration;
    s32 index;

    count = 0;
    index = 0;
    iteration = 0;

    do {
        if (index >= 22) {
            return count;
        }
        if (values[index++] < 0xFFFF) {
            count++;
        }
        iteration++;
    } while (iteration < 22);

    return count;
}

/* Whether unit `nOwnerID` is a card worth picking up (face down, not a leader). */
s32 TaLogic_IsPickUp(s32 nOwnerID) {
    s32 column;
    s32 row;
    s32 terrain;

    column = nOwnerID & 0xFF;
    row = nOwnerID >> 8;
    if (SzDuel_GetUnitStatus(row, column, 0) != 0) {
        return 1;
    }
    terrain = SzDuel_GetUnitKind(row, column) >> 5;
    switch (terrain) {
    case 3:
    case 4:
        if (SzDuel_GetUnitStatus(row, column, 4) != 0) {
            return 0;
        }
        break;
    }
    return 1;
}

typedef struct Nibbles_0027C770 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_0027C770;

/* How many squares around (nX, nZ) within `bRange` a field change to `bFieldKind` would help (up to `bCngNum`). */
s32 TaLogic_GetLandChange(s32 pVarInfo, s32 nX, s32 nZ, s32 bFieldKind, s32 bCngNum, s32 bRange) {
    extern s32 func_002792C0();
    s32 x;
    s32 cy;
    u8 x1;
    s32 i;
    s32 bestCount;
    Nibbles_0027C770 * entry;
    s32 bestCost;
    u8 y0;
    s32 cost;
    u8 y1;
    s32 cx;
    u8 minCount;
    u8 x0;
    s32 best;
    u8 range;
    u8 kind;
    Nibbles_0027C770 entries[12];
    s32 count;
    s32 y;

    entry = entries;
    best = -1;
    bestCount = 0;
    i = 0;
    do {
        entry->low = entry->high = 15;
        entry++;
        i++;
    } while (i < 12);
    minCount = bCngNum;
    bestCost = 14;
    range = bRange;
    kind = bFieldKind;
    for (i = 0; i < 7; i++) {
        for (x = 0; x < 7; x++) {
            count = 0;
            y0 = func_00250860(0, i - range);
            y1 = i + range >= 7 ? 6 : i + range;
            x0 = func_00250860(0, x - range);
            x1 = x + range >= 7 ? 6 : x + range;
            for (cy = y0; cy <= y1; cy++) {
                for (cx = x0; cx <= x1; cx++) {
                    if (((cy < i ? i : cy) - (i < cy ? i : cy)) + ((cx < x ? x : cx) - (x < cx ? x : cx)) <= range &&
                        kind != func_001E22B0(cy, cx) && func_001E22B0(cy, cx) != 8) {
                        count++;
                    }
                }
            }
            if (count >= bestCount && minCount < count) {
                cost = func_002792C0(pVarInfo, entries, nX, nZ, i, x, 0, 30);
                if (cost < bestCost) {
                    bestCost = cost;
                    bestCount = count;
                    best = (x << 8) | i;
                }
            }
        }
    }
    return best;
}
struct PieceTreetag;
struct jp_9add8 {
    unsigned short wUnit;
    unsigned short wOrder;
    unsigned short wPurpose;
    unsigned int dwGoal;
    unsigned char bCond : 2;
};
extern int func_001E1580_b(int a, int b);
extern struct PieceTreetag *func_002770E0_b(struct PieceTreetag *pTree, struct jp_9a533 *pVarInfo, int nX, int nZ,
                                                  int nSide, unsigned char bChase, int fView, int bWarnLvl,
                                                  struct jp_9b50e *nUnitLst, unsigned short *wUnitNum,
                                                  unsigned short *wSize, unsigned short *wNodeCount,
                                                  unsigned short *wIgnoreLst);
extern struct jp_9a533 *func_001DF540_b_2(int a, int b);
extern int func_001E1030_b(int a, int b);
extern int func_00249580_b(int index);
extern void func_0027E770_b(unsigned short *wIgnoreLst);
extern int func_0027D720_b(struct jp_9add8 *pTask, unsigned char fView);

/* Gives an equip-carrying unit its task: go to the unit it equips. */
int TaLogic_CommandEncUnit(void *pTask_v, unsigned char bChaseRange, unsigned char bIsView, unsigned char WarLvl)
{
    struct jp_9add8 * pTask = pTask_v;
    struct PieceTreetag *pTree;
    struct jp_9a533 *pVarInfo;
    unsigned short wIgnoreLst[49];
    struct jp_9b50e nUnitLst[22];
    unsigned short wUnitLst[22];
    unsigned short wSize;
    unsigned short wNodeCount;
    unsigned short wUnitNum;
    int N4;
    int i;
    int j;
    int Loc;
    int nSide;
    int Unit;
    int R2;
    int F;
    int nCardNo;
    int tempAP;
    int bKind;

    if (func_001DF540_b_2(pTask->wUnit >> 8, pTask->wUnit & 0xFF) == 0) {
        return 0;
    }
    nCardNo = func_001E1030_b(pTask->wUnit >> 8, pTask->wUnit & 0xFF);
    nSide = Ta_IsUnitControl(pTask->wUnit >> 8, pTask->wUnit & 0xFF);
    for (i = 0; i < 22; i++) {
        nUnitLst[i].nUnitID = 0xFFFF;
        nUnitLst[i].bDist = 0xFF;
        wUnitLst[i] = 0xFFFF;
    }
    func_0027E770_b(wIgnoreLst);
    switch (func_00249580_b(nCardNo & 0xFFFF)) {
    case 3:
        if (func_0027D720_b(pTask, bIsView) == 1) {
            bKind = SzDuel_GetUnitKind(((pTask->dwGoal >> 16) & 0xFFFF) >> 8, (pTask->dwGoal >> 16) & 0xFF);
            if (bKind >> 5 == 0 && (bKind & 0x1F) != 14) {
                return 1;
            }
        }
        pTask->wPurpose = 0x5FF;
        return 1;
    case 2:
        Unit = -1;
        TaUtil_GetUnitLst(nSide, 1, wUnitLst);
        for (i = 0; i < TaLogic_GetUnitCtlLstLen(wUnitLst); i++) {
            if (func_001E1580_b(wUnitLst[i] >> 8, wUnitLst[i] & 0xFF) == 0xFF) {
                if (TaUtil_GetUnitAP(wUnitLst[i] >> 8, wUnitLst[i] & 0xFF, SzDuel_GetUnitLoc(wUnitLst[i] >> 8, wUnitLst[i] & 0xFF) & 0xFF, SzDuel_GetUnitLoc(wUnitLst[i] >> 8, wUnitLst[i] & 0xFF) >> 8) > -1) {
                    Unit = wUnitLst[i];
                }
            }
        }
        if (Unit > 0) {
            

            j = Unit << 16;
            pTask->wPurpose = 0x9FF;
            pTask->dwGoal = j | (pTask->dwGoal & 0xFFFF);
            return 1;
        }
        R2 = -1;
        for (j = 0; j < 22; j++) {
            wUnitLst[j] = 0xFFFF;
        }
        TaLogic_GetUnitCtlLst2(nSide == 0 ? 1 : 0, wUnitLst, 29, bIsView, bIsView);
        for (i = 0; i < TaLogic_GetUnitCtlLstLen(wUnitLst); i++) {
            tempAP = SzDuel_GetUnitAP(wUnitLst[i] >> 8, wUnitLst[i] & 0xFF, 0);
            if (tempAP - SzDuel_GetUnitAP(wUnitLst[i] >> 8, wUnitLst[i] & 0xFF, 1) > -1) {
                R2 = wUnitLst[i];
            }
        }
        if (R2 > 0) {
            pTask->wPurpose = 0x9FF;
            pTask->dwGoal = (R2 << 16) | (pTask->dwGoal & 0xFFFF);
            return 1;
        }
        R2 = -1;
        for (j = 0; j < 22; j++) {
            wUnitLst[j] = 0xFFFF;
        }
        TaLogic_GetUnitCtlLst2(nSide, wUnitLst, 52, 1, 1);
        for (i = 0; i < TaLogic_GetUnitCtlLstLen(wUnitLst); i++) {
            if (func_001E1580_b(wUnitLst[i] >> 8, wUnitLst[i] & 0xFF) > -1) {
                R2 = wUnitLst[i];
            }
        }
        if (R2 > 0) {
            pTask->wPurpose = 0x9FF;
            pTask->dwGoal = (R2 << 16) | (pTask->dwGoal & 0xFFFF);
            return 1;
        }
        pTask->wPurpose = 0x5FF;
        return 1;
    default:
        nSide = Ta_GetCurrentSide(pTask->wUnit >> 8, pTask->wUnit & 0xFF);
        Loc = SzDuel_GetUnitLoc(pTask->wUnit >> 8, pTask->wUnit & 0xFF);
        pVarInfo = func_001DF540_b_2(pTask->wUnit >> 8, pTask->wUnit & 0xFF);
        wUnitNum = 0;
        wNodeCount = 0;
        wSize = 0;
        pTree = 0;
        for (i = 0; i < bChaseRange; i++) {
            for (N4 = 0; N4 < 22; N4++) {
                wUnitLst[N4] = 0xFFFF;
            }
            F = 0;
            pTree = func_002770E0_b(pTree, pVarInfo, Loc & 0xFF, Loc >> 8, nSide, i, bIsView, WarLvl, nUnitLst, &wUnitNum, &wSize, &wNodeCount, wIgnoreLst);
            for (j = 0; j < 22; j++) {
                if (Do_ChkEncMatch(nUnitLst[j].nUnitID >> 8, nUnitLst[j].nUnitID & 0xFF, nCardNo) == 1) {
                    wUnitLst[F] = nUnitLst[j].nUnitID;
                    F++;
                }
            }
            Unit = TaLogic_GetMaxApUnit2(wUnitLst, nSide);
            if (Unit >= 0) {
                pTask->wPurpose = 0x9FF;
                pTask->dwGoal = (Unit << 16) | (pTask->dwGoal & 0xFFFF);
                return 1;
            }
        }
        pTask->wPurpose = 0x5FF;
        return 1;
    }
}

typedef struct Position_0027D020 {
    u8 x : 4;
    u8 y : 4;
} Position_0027D020;

typedef struct Source_0027D020 {
    u16 position;
    u8 pad2[6];
    u32 targets;
} Source_0027D020;

typedef struct Result_0027D020 {
    u16 position;
    u8 action;
    u8 pad3;
    u16 destination;
    u8 pad6[6];
    s32 type;
    u8 flags;
} Result_0027D020;

/* A task's goal word. */
static inline u32 target_word_0027D020(void *src) {
    return ((Source_0027D020 *)src)->targets;
}

/* A task's goal half-word. */
static inline u32 target_half_0027D020(void *src) {
    return (u16)((Source_0027D020 *)src)->targets;
}

#define target_0027D020(src, side) \
    ((side) == 1 ? (u32)(u16)(target_word_0027D020(src) >> 16) : target_half_0027D020(src))

/* The cheapest task for an equip mission. */
s32 TaLogic_GetMinimumTask_EncMission(void *arg0, s32 arg1, void *arg2, u8 arg3,
                  s32 arg4, s32 cost, s32 arg6, u8 arg7) {
    extern void TaLogic_GetInvadeRoot();
    Position_0027D020 positions[12];
    s32 origin;
    s32 destination;
    s32 count;
    s32 best;
    s32 side;
    Position_0027D020 *p;
    s32 index;

    origin = SzDuel_GetUnitLoc(((Source_0027D020 *)arg0)->position >> 8, ((Source_0027D020 *)arg0)->position & 0xFF);
    side = arg3;
    destination = SzDuel_GetUnitLoc(target_0027D020(((Source_0027D020 *)arg0), side) >> 8,
                               target_0027D020(((Source_0027D020 *)arg0), side) & 0xFF);
    if (target_0027D020(((Source_0027D020 *)arg0), side) == 0xFFFF &&
        origin == target_0027D020(((Source_0027D020 *)arg0), side)) {
        ((Result_0027D020 *)arg2)->position = ((Source_0027D020 *)arg0)->position;
        ((Result_0027D020 *)arg2)->action = 6;
        ((Result_0027D020 *)arg2)->destination = origin;
        ((Result_0027D020 *)arg2)->flags = 2;
        ((Result_0027D020 *)arg2)->type = 2;
        TaLogic_InitRogicControl(((Source_0027D020 *)arg0), arg3);
        return 0;
    }

    p = positions;
    {
        s32 i = 0;
        Position_0027D020 *q = p;
        do {
            q->x = q->y = 0xF;
            i++;
            q++;
        } while (i < 12);
    }
    TaLogic_GetInvadeRoot(((Source_0027D020 *)arg0)->position >> 8, ((Source_0027D020 *)arg0)->position & 0xFF,
                  positions, origin & 0xFF, origin >> 8,
                  destination & 0xFF, destination >> 8, ((Source_0027D020 *)arg0)->targets,
                  (u8)arg4, 3, (u16)cost);
    count = TaLogic_GetMinGoalCount((u8 *)positions);
    if (count > 0) {
        best = 0xFF;
        cost = 0xFFFF;
        index = 0;

        for (; index < count; index++, p++) {
            if (SzDuel_GetMapUnit(p->x, p->y) == 0) {
                s32 value;
                value = TaLogic_GetUnitWarning(p->x, p->y, arg1,
                                      (u8)cost, (u16)arg7, (u8)cost);
                if (value < cost) {
                    cost = value;
                    best = index;
                } else if (value == cost) {
                    u32 bestMinY;
                    u32 bestY;
                    u32 bestMinX;
                    u32 bestX;
                    u32 currentMinY;
                    u32 currentY;
                    u32 currentMinX;
                    u32 currentX;

                    bestMinY = (u8)positions[best].y < (target_0027D020(((Source_0027D020 *)arg0), side) >> 8)
                        ? (u8)positions[best].y : (target_0027D020(((Source_0027D020 *)arg0), side) >> 8);
                    bestY = (target_0027D020(((Source_0027D020 *)arg0), side) >> 8) < (u8)positions[best].y
                        ? (u8)positions[best].y : (target_0027D020(((Source_0027D020 *)arg0), side) >> 8);
                    bestMinX = (u8)positions[best].x < (target_0027D020(((Source_0027D020 *)arg0), side) & 0xFF)
                        ? (u8)positions[best].x : (target_0027D020(((Source_0027D020 *)arg0), side) & 0xFF);
                    bestX = (target_0027D020(((Source_0027D020 *)arg0), side) & 0xFF) < (u8)positions[best].x
                        ? (u8)positions[best].x : (target_0027D020(((Source_0027D020 *)arg0), side) & 0xFF);
                    currentMinY = (u8)(*p).y < (target_0027D020(((Source_0027D020 *)arg0), side) >> 8)
                        ? (u8)(*p).y : (target_0027D020(((Source_0027D020 *)arg0), side) >> 8);
                    currentY = (target_0027D020(((Source_0027D020 *)arg0), side) >> 8) < (u8)(*p).y
                        ? (u8)(*p).y : (target_0027D020(((Source_0027D020 *)arg0), side) >> 8);
                    currentMinX = (u8)(*p).x < (target_0027D020(((Source_0027D020 *)arg0), side) & 0xFF)
                        ? (u8)(*p).x : (target_0027D020(((Source_0027D020 *)arg0), side) & 0xFF);
                    currentX = (target_0027D020(((Source_0027D020 *)arg0), side) & 0xFF) < (u8)(*p).x
                        ? (u8)(*p).x : (target_0027D020(((Source_0027D020 *)arg0), side) & 0xFF);
                    if ((currentX - currentMinX) + (currentY - currentMinY) <
                        (bestX - bestMinX) + (bestY - bestMinY)) {
                        cost = value;
                        best = index;
                    }
                }
            }
        }
    } else {
        ((Result_0027D020 *)arg2)->position = ((Source_0027D020 *)arg0)->position;
        ((Result_0027D020 *)arg2)->action = 6;
        ((Result_0027D020 *)arg2)->destination = origin;
        ((Result_0027D020 *)arg2)->flags = 2;
        ((Result_0027D020 *)arg2)->type = 2;
        TaLogic_InitRogicControl(((Source_0027D020 *)arg0), arg3);
        return 0;
    }
    if (best != 0xFF) {
        ((Result_0027D020 *)arg2)->position = ((Source_0027D020 *)arg0)->position;
        ((Result_0027D020 *)arg2)->action = 6;
        ((Result_0027D020 *)arg2)->destination = (positions[best].y << 8) | positions[best].x;
        ((Result_0027D020 *)arg2)->flags = 2;
        ((Result_0027D020 *)arg2)->type = 2;
    } else {
        ((Result_0027D020 *)arg2)->position = ((Source_0027D020 *)arg0)->position;
        ((Result_0027D020 *)arg2)->action = 6;
        ((Result_0027D020 *)arg2)->destination = origin;
        ((Result_0027D020 *)arg2)->flags = 2;
        ((Result_0027D020 *)arg2)->type = 2;
    }
    TaLogic_InitRogicControl(((Source_0027D020 *)arg0), arg3);
    return 0;
}

/* Gives a ranged (gunner) unit its task: the strongest enemy in reach. */
s32 TaLogic_CommandGunnerUnit(u16 *pTask, s32 fView) {
    u16 candidates[22];
    s32 side;
    s32 target;
    s32 i;
    u16 *p;
    u16 position;

    position = *pTask;
    side = Ta_GetCurrentSide((s32) position >> 8, position & 0xFF);
    p = candidates;
    i = 0;
    do {
        i += 1;
        *p++ = 0xFFFF;
    } while (i < 22);
    position = *pTask;
    switch (SzDuel_GetUnitKind((s32) position >> 8, position & 0xFF) >> 5) {
    case 0:
        position = *pTask;
        if (SzDuel_GetUnitStatus((s32) position >> 8, position & 0xFF, 4) != 0) {
            return 0;
        }
        break;
    }
    TaLogic_GetUnitCtlLst2((side == 0) ? 1 : 0, candidates, 0x34, 0, 0);
    target = TaLogic_GetMaxApUnit3(candidates, (side == 0) ? 1 : 0);
    if (target < 0) {
        return 0;
    }
    TaLogic_SetTaskAtkOrMove(pTask, target, fView);
    return 1;
}

struct jp_7b52 {
    int eNO;
    unsigned int dwFrom;
    unsigned int dwTo;
    unsigned int dwPar;
};
extern int func_0026B1F0_b(int nSide, int nID, int stDefense, int IsView);

/* What happens if a unit moves to square (x, y): traps and standing effects that react. */
int TaLogic_GetActionReaction(int row, int column, int x, int y, unsigned char n, int last)
{
    struct jp_7b52 out;
    unsigned int *p;
    int r;

    out.eNO = -1;
    

    p = &out.dwFrom;
    *p = -1;
    p = &out.dwTo;
    *p = -1;
    p = &out.dwPar;
    *p = -1;
    switch (n) {
    case 4:
        r = func_0026B1F0_b(row, column, 1, last);
        if ((r & 0xffff) != 1) {
            break;
        }
        if (r >> 16 == 1) {
            return 2;
        }
        return 5;
    case 5:
        r = func_0026B1F0_b(row, column, 0, last);
        if ((r & 0xffff) != 1) {
            break;
        }
        return 5;
    case 0:
        r = func_0026B1F0_b(row, column, 0, last);
        if ((r & 0xffff) == 1) {
            return 5;
        }
        r = SzDuel_GetUnitLoc(x, y);
        if (r < 0) {
            break;
        }
        if ((Chk_TrapA(row, column, r & 0xff, r >> 8, &out, ((last & 0xff) + 1) << 16) & 0xff) != 1) {
            break;
        }
        switch (out.eNO) {
        case 113:
            return 1;
        case 44:
            return 2;
        case 45:
        case 46:
            return 1;
        }
        break;
    case 6:
        if (Ta_SearchUncTypeNaturalEffectUserNum(14) > 0) {
            return 5;
        }
        r = Ta_IsActiveTrapB(Ta_IsUnitControl(row, column) == 0 ? 1 : 0, 14);
        if (r < 0) {
            break;
        }
        if ((last & 0xff) != 1 && SzDuel_GetUnitStatus(r >> 8, r & 0xff, 4) == 0) {
            break;
        }
        return 5;
    }
    return 0;
}

/* The card with the highest attack in a graveyard (side `sSide` as seen by `nSide`). */
s32 TaLogic_GetMaxAPGraveCard(s32 nSide, s32 sSide) {
    extern s32 SzDuel_GetGraveCount(s32);
    s32 best;
    s32 index;
    s32 owner;
    s32 i;
    s32 j;
    s32 value;

    owner = -1;
    index = -1;
    best = -1;
    if (sSide & 1) {
        for (i = 0; i < SzDuel_GetGraveCount(nSide); i++) {
            if ((TaHand_GetCardKind(SzDuel_InqGrave(nSide, i)) >> 5) == 0) {
                value = TaHand_GetCardAPDP(SzDuel_InqGrave(nSide, i)) >> 16;
                if (best < value) {
                    best = value;
                    index = i;
                    owner = nSide;
                }
            }
        }
    }
    if (sSide >> 1) {
        for (j = 0; j < SzDuel_GetGraveCount(nSide == 0 ? 1 : 0); j++) {
            if ((TaHand_GetCardKind(SzDuel_InqGrave(nSide == 0 ? 1 : 0, j)) >> 5) == 0) {
                value = TaHand_GetCardAPDP(SzDuel_InqGrave(nSide == 0 ? 1 : 0, j)) >> 16;
                if (best < value) {
                    best = value;
                    index = j;
                    owner = nSide == 0 ? 1 : 0;
                }
            }
        }
    }
    return best | ((owner << 24) | (index << 16));
}

/* A graveyard card of kind `bEntry` after screen position `Screen`. */
s32 TaLogic_GetGraveEntryAfterScreen(s32 nSide, s32 bEntry, s32 Screen) {
    extern s32 SzDuel_GetGraveCount(s32);
    u8 count;
    s32 i;
    s32 mode;

    mode = Screen & 0xFF;
    count = 0;
    if (mode == 31) {
        return bEntry & 0xFF;
    }
    if (mode == 29) {
        for (i = 0; i < SzDuel_GetGraveCount(nSide); i++) {
            if (i == (bEntry & 0xFF)) {
                return count;
            }
            if ((TaHand_GetCardKind(SzDuel_InqGrave(nSide, i)) >> 5) == 0) {
                count++;
            }
        }
    } else if (mode == 30) {
        for (i = 0; i < SzDuel_GetGraveCount(nSide); i++) {
            if (i == (bEntry & 0xFF)) {
                return count;
            }
            if ((TaHand_GetCardKind(SzDuel_InqGrave(nSide, i)) >> 5) != 0) {
                count++;
            }
        }
    }
    return bEntry & 0xFF;
}

/* How many copies of card `nCardNo` a graveyard holds. */
s32 TaLogic_GetGraveCardCount(s32 nSide, s32 sSide, s32 nCardNo) {
    extern s32 SzDuel_GetGraveCount();
    extern s32 SzDuel_InqGrave();
    s32 i;
    u8 count;

    count = 0;
    if (sSide & 1) {
        for (i = 0; i < SzDuel_GetGraveCount(nSide); i++) {
            if (nCardNo == SzDuel_InqGrave(nSide, i)) {
                count++;
            }
        }
    }
    if (sSide >> 1) {
        for (i = 0; i < SzDuel_GetGraveCount(nSide == 0 ? 1 : 0); i++) {
            if (nCardNo == SzDuel_InqGrave(nSide == 0 ? 1 : 0, i)) {
                count++;
            }
        }
    }
    return count;
}

/* The nearest enemy of side `eSide` within `bDist` a unit (record `pVarInfo`) on (nX, nZ) can beat, into `pTask`. */
s32 TaLogic_GetNearUnit(s32 pTask, s32 pTree, s32 pVarInfo, s32 nX, s32 nZ,
                  s32 eSide, s32 bDist, s32 WarnLvl, s32 nUnitLst, u16 wUnitNum,
                  s32 wSize, s32 wNodeCount, s32 bChase, s32 fView,
                  s32 Powerful, s32 wIgnoreLst) {
    extern s32 TaLogic_GetNearUnitL3();
    extern s32 TaLogic_IsUnitWin5();
    extern s32 TaLogic_IsUnitWin4();
    extern s32 SzDuel_GetUnitCurseRest();
    extern s32 SzDuel_GetUnitSpellRest();
    s32 candidate;

    bChase = (u8)bChase;
    fView = (u8)fView;
    TaLogic_GetNearUnitL2(pTree, pVarInfo, nX, nZ, eSide, bDist, fView, WarnLvl,
                  nUnitLst, (s32)&wUnitNum, wSize, wNodeCount, wIgnoreLst);
    if ((candidate = TaLogic_GetNearUnitL3(pVarInfo, nX, nZ, nUnitLst, bChase, 30, 1, 2,
                                  fView, WarnLvl, wUnitNum)) >= 0 &&
        TaUtil_GetUnitAP2(pVarInfo, nX, nZ) <= Powerful) {
        *(s16 *)((u8 *)pTask + 4) = 0x2FF;
        *(u32 *)((u8 *)pTask + 8) = (candidate << 16) | *(u16 *)((u8 *)pTask + 8);
        return 1;
    }
    if ((candidate = TaLogic_GetNearUnitL3(pVarInfo, nX, nZ, nUnitLst, bChase, 29, 1, 2,
                                  fView, WarnLvl, wUnitNum)) >= 0) {
        s32 y;
        s32 x;
        s32 position;
        s32 row;
        s32 column;

        x = candidate >> 8;
        y = candidate & 0xFF;
        position = SzDuel_GetUnitLoc(x, y);
        *(u32 *)((u8 *)pTask + 8) = (candidate << 16) | *(u16 *)((u8 *)pTask + 8);
        row = position >> 8;
        column = position & 0xFF;
        if (TaLogic_IsUnitWin4(pVarInfo, candidate, WarnLvl, column, row, fView) > 0) {
            TaLogic_SetTaskAtkOrMove((void *)pTask, candidate, fView);
            return 1;
        }
        if (SzDuel_GetUnitCurseRest(x, y) < 2) {
            if (SzDuel_GetUnitSpellRest(x, y) == 0) {
                return TaLogic_IsUnitWin5(pVarInfo, candidate, WarnLvl, column, row, fView);
            }
        }
    } else {
        s32 y;
        s32 x;
        s32 row;
        s32 column;
        s32 alternate;
        s32 position;
        if ((alternate = TaLogic_GetNearUnitL3(pVarInfo, nX, nZ, nUnitLst, bChase, 52, 0, 2,
                                      fView, WarnLvl, wUnitNum)) >= 0) {
            x = alternate >> 8;
            y = alternate & 0xFF;
            position = SzDuel_GetUnitLoc(x, y);

            *(u32 *)((u8 *)pTask + 8) = (alternate << 16) | *(u16 *)((u8 *)pTask + 8);
            row = position >> 8;
            column = position & 0xFF;
            if (TaLogic_IsUnitWin4(pVarInfo, alternate, WarnLvl, column, row, fView) > 0) {
                TaLogic_SetTaskAtkOrMove((void *)pTask, alternate, fView);
                return 1;
            }
            if (SzDuel_GetUnitCurseRest(x, y) < 2 && SzDuel_GetUnitSpellRest(x, y) == 0) {
                return TaLogic_IsUnitWin5(pVarInfo, alternate, WarnLvl, column, row, fView);
            }
        }
    }
    return -1;
}

/* Takes hidden units out of target list `eObj`. */
s32 TaLogic_RemoveHideUnit(s32 eObj) {
    s32 index;
    s32 count;
    s32 result;
    s32 low;
    s32 high;
    s32 value;

    count = Ta_GetUnitNumFrom22bitFlagList(eObj);
    result = eObj;
    for (index = 0; index < count; index++) {
        value = Ta_GetUnitOwnerIDFromLstCount(eObj, index);
        high = value >> 8;
        low = value & 0xFF;
        if (SzDuel_GetUnitStatus(high, low, 4) == 0) {
            result = ConvUnitIDtoFlagList_OFF((u32) high, low, result);
        }
    }
    return result;
}

typedef struct Entry_0027E210 {
    u16 id;
    u16 unused2;
    s16 status;
    u16 unused6;
    u32 position;
} Entry_0027E210;

/* Gives the computer opponent's leader its task on (nX, nZ): hold back if it can be attacked. */
void TaLogic_CommandStdLDUnit(void *pTask, s32 nX, s32 nZ, s32 fView) {
    Entry_0027E210 *entry = pTask;
    u16 id;

    id = entry->id;
    if (TaLogic_IsAttackedNow((s32) id >> 8, id & 0xFF, fView) == 1) {
        if (SzDuel_InqHandPhase((s32) entry->id >> 8) == 1) {
            entry->status = 0x50A;
        } else {
            entry->status = 0x5FF;
        }
    } else {
        id = entry->id;
        if (TaLogic_IsAttackedNow2((s32) id >> 8, id & 0xFF, nX, nZ, fView) == 0) {
            if (SzDuel_InqHandPhase((s32) entry->id >> 8) == 1) {
                entry->status = 0x60A;
                entry->position = *(u16 *)&entry->position | (((nZ << 8) | nX) << 16);
            } else {
                entry->status = 0x6FF;
                entry->position = *(u16 *)&entry->position | (((nZ << 8) | nX) << 16);
            }
        } else {
            if (SzDuel_InqHandPhase((s32) entry->id >> 8) == 1) {
                entry->status = 0x50A;
            } else {
                entry->status = 0x5FF;
            }
        }
    }
}

/* Whether unit (nSide, nID) should stay in defence (`fDef`) instead of going to goal `wGoal`. */
s32 TaLogic_IsDefStyleUnit(s32 nSide, s32 nID, s32 wGoal, s32 fDef, s32 fView) {
    s32 pos;
    s32 result;
    s32 y;
    s32 x;
    s32 count;

    if (nID == 0) {
        return 2;
    }
    pos = wGoal & 0xFFFF;
    if (pos != SzDuel_GetUnitLoc(nSide, nID)) {
        return 2;
    }
    x = pos & 0xFF;
    y = pos >> 8;
    result = TaLogic_GetActionReaction(nSide, nID, x, y, 4, fView);
    TaLogic_GetActionReaction(nSide, nID, x, y, 5, fView);
    if (SzDuel_GetUnitStatus(nSide, nID, 5) != 0) {
        if ((SzDuel_GetUnitKind(nSide, nID) >> 5) != 0) {
            if (result != 2 && result != 5) {
                return 2;
            }
            return 0;
        }
        count = SzDuel_GetUnitAP(nSide, nID, 0);
        if (SzDuel_GetUnitDP(nSide, nID, 0) < count && (fDef & 0xFF) == 0) {
            if (result != 2 && result != 5) {
                return 2;
            }
            return 0;
        }
        if (result != 2 && result != 5) {
            return 2;
        }
        return 0;
    }
    if ((SzDuel_GetUnitKind(nSide, nID) >> 5) != 0) {
        if (result != 2 && result != 5) {
            return 1;
        }
    }
    count = SzDuel_GetUnitAP(nSide, nID, 0);
    if (count < SzDuel_GetUnitDP(nSide, nID, 0) || (fDef & 0xFF) == 1) {
        if (result != 2 && result != 5) {
            return 1;
        }
    }
    return 2;
}

/* Whether unit `nOwnerID` can step on (nX, nZ) without setting off a trap. */
s32 TaLogic_IsSafeTrap(s32 nOwnerID, s32 nX, s32 nZ) {
    extern s32 SzDuel_GetUnitCardNo();
    s32 x;
    s32 y;
    s32 kind;
    s32 lo;
    s32 hi;
    s32 pos;

    kind = Ta_IsUnitControl(nOwnerID >> 8, nOwnerID & 0xFF);
    if (Ta_IsActiveTrapB(kind, 4) >= 0) {
        return 1;
    }
    for (x = GetCap(0, nX - 1); x <= GetCap(0, nX + 1); x++) {
        for (y = GetCap(0, nZ - 1); y <= GetCap(0, nZ + 1); y++) {
            if (((((x < nX) ? nX : x) - ((nX < x) ? nX : x)) + (((y < nZ) ? nZ : y) - ((nZ < y) ? nZ : y))) == 1) {
                pos = SzDuel_GetMapUnitID(x, y);
                hi = pos >> 8;
                if (pos >= 0) {
                    lo = pos & 0xFF;
                    if ((SzDuel_GetUnitKind(hi, lo) >> 5) == 3 && SzDuel_GetUnitCardNo(hi, lo) != 0x32D && kind == Ta_IsUnitControl(hi, lo)) {
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

/* Clears the computer opponent's list of units to ignore. */
void TaLogic_InitIgnoreLst(void) {

}

typedef struct State_0027E780 {
    u16 position;
    u16 pad2;
    u16 flags;
    u16 pad6;
    u32 destination;
} State_0027E780;

/* Sets task `pTask` to attack enemy `nEnemyID` or move toward it. */
void TaLogic_SetTaskAtkOrMove(void *pTask, s32 nEnemyID, s32 fView) {
    State_0027E780 *state = pTask;
    s32 destination;
    s32 result;
    u32 packed_destination;
    u16 position;

    destination = SzDuel_GetUnitLoc(nEnemyID >> 8, nEnemyID & 0xFF);
    position = state->position;
    result = TaLogic_GetActionReaction(position >> 8, position & 0xFF,
                         destination & 0xFF, destination >> 8, 0, fView);
    switch (result) {
    case 1:
    case 2:
        state->flags = 0x6FF;
        packed_destination = state->destination & 0xFFFF;
        state->destination = (destination << 16) | packed_destination;
        break;
    default:
        state->flags = 0x2FF;
        packed_destination = state->destination & 0xFFFF;
        state->destination = (nEnemyID << 16) | packed_destination;
        break;
    }
}

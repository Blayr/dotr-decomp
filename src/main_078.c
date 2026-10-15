#include "common.h"

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

s32 TaLogic_DoUnitAssign(u16 arg0, void *arg1) {
    Entry_00276120 *entries = arg1;
    s32 i;

    for (i = 0; i < 22; i++) {
        if (entries[i].id == 0xFFFF) {
            entries[i].id = arg0;
            entries[i].field_02 = SzDuel_GetUnitSummonOrder(arg0 >> 8, arg0 & 0xFF);
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

void TaLogic_DoSortTaskList(void *arg0) {
    s32 i;
    s32 j;
    Entry_002761D0 *dst;
    Entry_002761D0 *src;

    i = 0;
    dst = arg0;
    do {
        if (dst->id == 0xFFFF) {
            for (j = i + 1; j < 22; j++) {
                src = &((Entry_002761D0 *)arg0)[j];
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
#define DX (sX - (pTask->target & 0xff))
#define DZ (sZ - (pTask->target >> 8))

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
#undef DX
#undef DZ

static inline s32 absolute_00276B60(s32 value) {
    if (value >= 0) {
        return value;
    }
    return -value;
}

s32 TaLogic_GetQueueXY_Move1(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    extern s32 TaLogic_IsPassRoot();
    s16 cell;

    cell = SzDuel_GetMapUnitID(arg4, arg5);
    if ((((arg4 < arg2) ? arg2 : arg4) - ((arg2 < arg4) ? arg2 : arg4)) +
        (((arg5 < arg3) ? arg3 : arg5) - ((arg3 < arg5) ? arg3 : arg5)) == 1) {
        return 1;
    }
    switch (absolute_00276B60(arg2 - arg4)) {
    case 0:
        return 1;
    case 2:
        return 1;
    case 1:
        if (TaLogic_IsPassRoot(arg0, arg1, arg2, arg3, arg4, arg3, &cell) == 1) {
            return 1;
        }
        return 0;
    }
    return 1;
}

s32 TaLogic_GetActionUnitFromOwnerID(u16 *arg0, s32 arg1) {
    s32 i = 0;

    do {
        if (arg1 == *arg0) {
            return i;
        }
        i++;
        arg0 += 8;
    } while (i < 0x16);
    return -1;
}

struct jp_9a533;
extern struct jp_9a533 *func_001DF540_b(int a, int b);
extern int func_00278510_b(struct jp_9a533 *pVarInfo, int wUnit, int bWarnLvl, int x, int z,
                              unsigned char fView);
#define LO(a, b) ((a) < (b) ? (a) : (b))
#define HI(a, b) ((b) < (a) ? (a) : (b))

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

s32 TaLogic_GetNearCard2(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8,
                  s32 arg9) {
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
    for (i = 1; i <= (u8)arg4; i++) {
        state = TaLogic_GetNearUnitL2(state, arg0, arg1, arg2, arg3, (u8)i, arg8, arg9, slots, &a, &c, &b, work);
        result = func_00277160_b(arg0, arg1, arg2, slots, arg4, arg5, arg6, arg7, arg8, arg9, a);
        if (result >= 0) {
            return result;
        }
        if ((u32)SzGame_GetHSyncCount() > 12000) {
            return -1;
        }
    }
    return -1;
}

void TaLogic_GetNearUnitL2(s32 arg0, s32 arg1, s32 arg2, s32 arg3,
                   s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                   s32 arg8, s32 arg9, s32 arg10, s32 arg11, s32 arg12) {
    extern u8 *TaLogic_GetNearUnitPickUpTree();

    TaLogic_GetNearUnitPickUpTree(arg0, 0, arg1, arg2, arg3, arg4, arg5, arg6,
                   (u16) arg7, 0, (s64) arg10, (s64) arg11,
                   (s64) arg8, (s64) arg9, (s64) arg12);
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

s32 TaLogic_GetFollowNearUnit(s32 arg0, s32 arg1, void *arg2, s32 arg3, s32 arg4, u8 arg5, u8 arg6, u16 arg7) {
    extern s32 SzDuel_GetUnitCardNo();
    s32 var_s0;
    s32 temp_s1;
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

    var_s4 = arg2;
    var_fp = 7;
    var_s3 = 0xFFFF & 0xFFFF;
    for (var_s0 = 0; var_s0 < arg7; var_s0++) {
        temp_v0 = *(u16 *)var_s4;
        if (SzDuel_GetUnit((s32) temp_v0 >> 8, temp_v0 & 0xFF) != 0) {
            temp_v0_2 = *(u16 *)var_s4;
            temp_s1 = SzDuel_GetUnitLoc((s32) temp_v0_2 >> 8, temp_v0_2 & 0xFF);
            temp_v0_3 = *(u16 *)var_s4;
            if (TaLogic_IsStatusMatch(SzDuel_GetUnitStatus((s32) temp_v0_3 >> 8, temp_v0_3 & 0xFF, 2), arg5) == 1) {
                temp_v0_4 = *(u16 *)var_s4;
                if (TaLogic_IsStatusMatch(SzDuel_GetUnitStatus((s32) temp_v0_4 >> 8, temp_v0_4 & 0xFF, 5), arg6) == 1) {
                    temp_v0_5 = *(u16 *)var_s4;
                    if (TaLogic_IsUnitCategory((s32) temp_v0_5 >> 8, temp_v0_5 & 0xFF, arg4) == 1) {
                        temp_s2 = var_s4[2];
                        if (temp_s2 <= (u8) arg3) {
                          if ((s32) temp_s2 > 0) {
                            temp_v0_6 = var_fp & 0xFF;
                            if ((s32) temp_s2 < temp_v0_6) {
                                y = temp_s1 >> 8;
                                if (arg1 < y) {
                                    var_v0_2 = arg1;
                                } else {
                                    var_v0_2 = y;
                                }
                                if (y < arg1) {
                                    var_a0 = arg1;
                                } else {
                                    var_a0 = y;
                                }
                                x = temp_s1 & 0xFF;
                                if (arg0 < x) {
                                    var_v1 = arg0;
                                } else {
                                    var_v1 = x;
                                }
                                if (x < arg0) {
                                    var_a1 = arg0;
                                } else {
                                    var_a1 = x;
                                }
                                var_s3 = *(u16 *)var_s4;
                                var_fp = ((var_a1 - var_v1) + (var_a0 - var_v0_2)) & 0xFF;
                                arg3 = temp_s2 & 0xFF;
                            } else if (temp_s2 == temp_v0_6) {
                                temp_v0_7 = SzDuel_GetCardConstInfo(SzDuel_GetUnitCardNo(*(u16 *)var_s4 >> 8, *(u16 *)var_s4 & 0xFF))[3];
                                spA0 = (s32) temp_v0_7;
                                if ((s32) SzDuel_GetCardConstInfo(SzDuel_GetUnitCardNo(var_s3 >> 8, var_s3 & 0xFF))[3] < spA0) {
                                    y2 = temp_s1 >> 8;
                                    var_s3 = *(u16 *)var_s4;
                                    if (arg1 < y2) {
                                        var_v0_3 = arg1;
                                    } else {
                                        var_v0_3 = y2;
                                    }
                                    if (y2 < arg1) {
                                        var_a0_2 = arg1;
                                    } else {
                                        var_a0_2 = y2;
                                    }
                                    x2 = temp_s1 & 0xFF;
                                    if (arg0 < x2) {
                                        var_v1_2 = arg0;
                                    } else {
                                        var_v1_2 = x2;
                                    }
                                    if (x2 < arg0) {
                                        var_a1_2 = arg0;
                                    } else {
                                        var_a1_2 = x2;
                                    }
                                    var_fp = ((var_a1_2 - var_v1_2) + (var_a0_2 - var_v0_3)) & 0xFF;
                                    arg3 = temp_s2 & 0xFF;
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

    reach = GetMoveRev(card, x, y);
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

s32 TaLogic_IsAdjustUnitLst(void *arg0, s32 arg1, s32 arg2) {
    s32 i;
    s32 result;
    Entry_00277C60 *entry;
    u16 key;
    u8 *value;

    i = 0;
    result = 0;
    do {
        entry = &((Entry_00277C60 *)arg0)[i];
        key = entry->key;
        if (arg1 == key) {
            value = &entry->value;
            if (arg2 < *value) {
                *value = arg2;
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

s32 TaLogic_GetTrapNearCard(s32 arg0, s32 arg1, s32 arg2, s32 arg3, void *arg4,
                  u8 range, s32 arg6, u8 arg7, u8 arg8, s32 arg9,
                  s32 fallback, u16 count, u8 arg12) {
    s32 cost;
    Entry_00277CD0 *p = arg4;
    u8 mode = (u8)arg9;
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
            if ((((pos & 0xFF) < arg2 ? arg2 : (pos & 0xFF)) - (arg2 < (pos & 0xFF) ? arg2 : (pos & 0xFF))) +
                (((pos >> 8) < arg3 ? arg3 : (pos >> 8)) - (arg3 < (pos >> 8) ? arg3 : (pos >> 8))) <= range &&
                TaLogic_IsStatusMatch(SzDuel_GetUnitStatus(p->id >> 8, p->id & 0xFF, 2), arg7) == 1 &&
                TaLogic_IsStatusMatch(SzDuel_GetUnitStatus(p->id >> 8, p->id & 0xFF, 5), arg8) == 1 &&
                TaLogic_IsUnitCategory(p->id >> 8, p->id & 0xFF, arg6) == 1 &&
                ((TaLogic_IsJudgeUnitDanger(p->id >> 8, p->id & 0xFF, mode) == 1 &&
                  TaTrapA_IsTrapAct(arg0, arg1, p->id >> 8, p->id & 0xFF, (pos & 0xFF), (pos >> 8)) == 1) ||
                 (TaLogic_IsJudgeUnitDanger(p->id >> 8, p->id & 0xFF, mode) == 1 && arg12 == 1))) {
                cost = p->cost;
                if (cost <= range && cost > 0) {
                    if (cost < bestDistance) {
                        s32 maxY;
                        s32 maxX;
                        if (arg3 < (pos >> 8)) minY = arg3;
                        else minY = pos >> 8;
                        if ((pos >> 8) < arg3) maxY = arg3;
                        else maxY = pos >> 8;
                        if (arg2 < (pos & 0xFF)) minX = arg2;
                        else minX = pos & 0xFF;
                        if ((pos & 0xFF) < arg2) maxX = arg2;
                        else maxX = pos & 0xFF;
                        best = p->id;
                        bestDistance = (maxX - minX) + (maxY - minY);
                        bestPos = (u16)pos;
                        range = (u8)cost;
                    } else if (cost == bestDistance) {
                        if (TaLogic_IsJudgeUnitDanger(p->id >> 8, p->id & 0xFF, mode) == 1) {
                            newScore = TaLogic_IsUnitWin2(SzDuel_GetUnit(arg0, arg1), p->id, (pos & 0xFF), (pos >> 8));
                        } else {
                            newScore = fallback;
                        }
                        if (TaLogic_IsJudgeUnitDanger(best >> 8, best & 0xFF, mode) == 1) {
                            oldScore = TaLogic_IsUnitWin2(SzDuel_GetUnit(arg0, arg1), best, bestPos & 0xFF, bestPos >> 8);
                        } else {
                            oldScore = fallback;
                        }
                        if (newScore < oldScore) {
                            s32 maxY;
                            s32 maxX;
                            best = p->id;
                            if (arg3 < (pos >> 8)) minY = arg3;
                            else minY = pos >> 8;
                            if ((pos >> 8) < arg3) maxY = arg3;
                            else maxY = pos >> 8;
                            if (arg2 < (pos & 0xFF)) minX = arg2;
                            else minX = pos & 0xFF;
                            if ((pos & 0xFF) < arg2) maxX = arg2;
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

s32 TaLogic_IsStatusMatch(s32 arg0, s32 arg1) {
    switch (arg1) {
    case 0:
        if (arg0 == 0) {
            return 1;
        }
        break;
    case 1:
        if (arg0 == 1) {
            return 1;
        }
        break;
    case 2:
    default:
        return 1;
    }
    return 0;
}

s32 TaLogic_IsJudgeUnitDanger(s32 arg0, s32 arg1, s32 arg2) {
    if (arg2 != 0) {
        return 1;
    }
    if (SzDuel_GetUnitStatus(arg0, arg1, 2) == 1) {
        return 1;
    }
    return 0;
}

s32 TaLogic_IsUnitWin(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return TaLogic_IsUnitWin2(SzDuel_GetUnit(arg0 >> 8, arg0 & 0xFF), arg1, arg2, arg3);
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

s32 TaLogic_IsUnitWin2(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    extern s32 TaUtil_GetUnitDP2(s32, s32, s32);
    extern s32 TaUtil_GetUnitAP2();
    extern s32 TaLogic_GetActOfs(void *, void *);
    Obj_00278250 *obj = (Obj_00278250 *)arg0;
    s32 mine;
    s32 theirs;

    if (obj == NULL) {
        return 0;
    }
    if (TaUtil_IsVarInfoLeader(obj) == 1) {
        mine = 0;
    } else if ((obj->unk3E >> 5) != 0) {
        mine = 0;
    } else if (obj->unk40 == arg2 && obj->unk41 == arg3 && obj->flag) {
        mine = TaUtil_GetUnitDP2(arg0, arg2, arg3);
    } else {
        mine = TaUtil_GetUnitAP2(arg0, arg2, arg3);
    }
    mine += TaLogic_GetActOfs(obj, (void *)SzDuel_GetUnit(arg1 >> 8, arg1 & 0xFF));
    if (TaUtil_IsVarInfoLeader((void *)SzDuel_GetUnit(arg1 >> 8, arg1 & 0xFF)) == 1) {
        theirs = 0;
    } else if ((SzDuel_GetUnitKind(arg1 >> 8, arg1 & 0xFF) >> 5) != 0) {
        theirs = 0;
    } else if (SzDuel_GetUnitStatus(arg1 >> 8, arg1 & 0xFF, 5) != 0) {
        theirs = TaUtil_GetUnitDP(arg1 >> 8, arg1 & 0xFF, arg2, arg3);
    } else {
        theirs = TaUtil_GetUnitAP(arg1 >> 8, arg1 & 0xFF, arg2, arg3);
    }
    theirs += TaLogic_GetActOfs((void *)SzDuel_GetUnit(arg1 >> 8, arg1 & 0xFF), obj);
    return mine - theirs;
}

s32 TaLogic_IsUnitWin3(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    extern s32 TaUtil_GetUnitDP2(s32, s32, s32);
    Obj_00278250 *obj = (Obj_00278250 *)arg0;
    s32 mine;

    if (obj == NULL) {
        return 0;
    }
    if (TaUtil_IsVarInfoLeader(obj) == 1) {
        mine = 0;
    } else if (obj->unk40 == arg2 && obj->unk41 == arg3 && obj->flag) {
        mine = TaUtil_GetUnitDP2(arg0, arg2, arg3);
    } else {
        mine = TaUtil_GetUnitAP2(arg0, arg2, arg3);
    }
    if (SzDuel_GetField(arg2, arg3) == 9) {
        arg1 = GetCap(0x5DC, arg1);
    }
    return mine - arg1;
}

void TaLogic_IsUnitWin4(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    if (arg1 == -1) {
        TaLogic_IsUnitWin3(arg0, arg2, arg3, arg4);
        return;
    }
    if (TaLogic_IsJudgeUnitDanger(arg1 >> 8, arg1 & 0xFF, arg5 & 0xFF) == 0) {
        TaLogic_IsUnitWin3(arg0, arg2, arg3, arg4);
        return;
    }
    TaLogic_IsUnitWin2(arg0, arg1, arg3, arg4);
}

s32 TaLogic_IsUnitWin5(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    extern s32 TaLogic_IsUnitWin3();
    extern s32 TaUtil_GetUnitAP2();
    extern s32 TaUtil_GetUnitDP2();
    extern s32 TaLogic_GetActOfs();
    s32 damage;
    s32 defense;
    s32 item;
    s32 card;

    if (arg0 == 0) {
        return 0;
    }
    card = arg1 >> 8;
    if (arg1 == -1) {
        return TaLogic_IsUnitWin3(arg0, arg2, arg3, arg4);
    }
    item = arg1 & 0xFF;
    if (TaLogic_IsJudgeUnitDanger(card, item, arg5 & 0xFF) == 0) {
        damage = TaUtil_GetUnitAP2(arg0, arg3, arg4);
        defense = TaUtil_GetUnitDP2(arg0, arg3, arg4);
    } else {
        if (TaUtil_IsVarInfoLeader((void *)arg0) == 1) {
            defense = 0;
            damage = 0;
        } else if ((*(u8 *)((u8 *)arg0 + 0x3E) >> 5) != 0) {
            defense = 0;
            damage = 0;
        } else {
            damage = TaUtil_GetUnitAP2(arg0, arg3, arg4);
            defense = TaUtil_GetUnitDP2(arg0, arg3, arg4);
            damage += TaLogic_GetActOfs((void *)arg0, (void *)SzDuel_GetUnit(card, item));
            defense += TaLogic_GetActOfs((void *)arg0, (void *)SzDuel_GetUnit(card, item));
        }

        if (TaUtil_IsVarInfoLeader((void *)SzDuel_GetUnit(card, item)) == 1) {
            arg2 = 0;
        } else if ((SzDuel_GetUnitKind(card, item) >> 5) != 0) {
            arg2 = 0;
        } else {
            arg2 = TaUtil_GetUnitAP(card, item, arg3, arg4);
            arg2 += TaLogic_GetActOfs((void *)SzDuel_GetUnit(card, item), (void *)arg0);
        }
    }

    if (defense < damage) {
        if (damage >= arg2) {
            return 3;
        }
        return 0;
    }
    if (damage <= defense) {
        return (arg2 < defense) ? 2 : 0;
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

u16 TaLogic_GetActOfs(void *arg0, void *arg1) {
    Object_002787F0 *first = arg0;
    Object_002787F0 *second = arg1;
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

void TaLogic_GetUnitNum(s32 arg0, s32 arg1) {
    if (arg1 == 1) {
        SzDuel_GetUnitSpellCount(arg0);
        return;
    }
    SzDuel_GetUnitMonsterCount(arg0);
}

typedef struct {
    u8 b[0x18];
} Ent_002788D0;

void *TaLogic_TreeAloc(u16 *arg0, u16 *arg1) {
    u16 idx;

    if ((s64)(u32)(*arg0 + 0x38) > 0x10000) {
        return 0;
    }
    idx = *arg1;
    *arg1 = idx + 1;
    *arg0 += 0x18;
    return &((Ent_002788D0 *)0x01ED0000)[idx];
}

typedef struct Entry_00278930 {
    s16 id;
    u8 slots[5];
    u8 pad;
    s32 values[4];
} Entry_00278930;

void TaLogic_InitTree(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    Entry_00278930 *entry = arg0;
    s32 i;
    u8 *p;

    entry->id = arg1;
    i = 0;
    do {
        entry->slots[i] = 0xFF;
        i++;
    } while (i < 5);
    i = 0;
    p = arg0;
    do {
        i++;
        *(s32 *)(p + 8) = 0;
        p += 4;
    } while (i < 4);
    if (arg2 == 0) {
        ((u8 *)arg0)[2] = arg3;
        return;
    }
    TaLogic_CopyArray((u8 *)arg2, (u8 *)arg0 + 2);
    entry->slots[(u8)TaLogic_GetArrayLength((u8 *)arg2)] = arg3;
}

s32 TaLogic_GetHandFusion(s32 arg0, s32 arg1) {
    s32 temp_v0;
    s32 temp_s1;
    s32 temp_s2;

    temp_s2 = arg0 & 0xFFFF;
    if ((temp_s2 == 0x3E7) || (temp_s1 = arg1 & 0xFFFF, (temp_s1 == 0x3E7))) {
        return 0x3E7;
    }
    temp_v0 = Ta_GetHandEnchant(temp_s2, temp_s1);
    if ((temp_v0 >> 0x10) == 0) {
        if (TaEnc_IsEncDo(temp_s1) == 1) {
            return temp_v0 & 0xFFFF;
        }
    }
    return Fusion(temp_s2, temp_s1) & 0xFFFF;
}

INCLUDE_ASM("asm/nonmatchings/main_078", TaLogic_GetFusionTree);

void *TaLogic_GetFusionTree2(s32 arg0, s32 arg1, s32 arg2, s32 arg3,
                    s32 arg4, u16 *arg5, u16 *arg6) {
    s32 sp60[8];
    void *temp_v0;

    TaHand_GetNextHand(arg0, sp60);
    if (arg4 != 0) {
        return NULL;
    }
    if ((temp_v0 = TaLogic_TreeAloc(arg5, arg6)) == NULL) {
        return NULL;
    }
    TaLogic_InitTree(temp_v0, arg3 & 0xFFFF, arg4, arg2);
    return temp_v0;
}

void TaLogic_AddEmptyCombo(u8 *arg0, u8 arg1) {
    s32 var_a0;
    u8 *temp_a1;
    u8 temp_v1;

    if ((TaLogic_GetArrayLength(arg0) & 0xFF) != 5) {
        var_a0 = 3;
        do {
            temp_a1 = &arg0[var_a0];
            temp_v1 = temp_a1[0];
            var_a0 -= 1;
            temp_a1[1] = temp_v1;
        } while (var_a0 >= 0);
        *arg0 = arg1;
    }
}

s32 TaLogic_GetArrayLength(u8 *arg0) {
    s32 index;
    s32 count;

    index = 0;
    count = 0;
    do {
        if (arg0[index] == 0xFF) {
            return count;
        }
        index++;
        count++;
    } while (index < 5);
    return count;
}

void TaLogic_CopyArray(u8 *src, u8 *dst) {
    s32 i;

    i = 0;
    do {
        dst[i] = src[i];
        i++;
    } while (i < 5);
}

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

u16 *TaLogic_GetFusionRes(u16 *arg0) {
    s32 var_s3;
    u16 *temp_v0;
    s32 var_s5;
    u8 *var_s0;
    u16 *var_s1;

    var_s1 = arg0;
    if (var_s1 != NULL) {
        var_s5 = (TaHand_GetCardAPDP(*var_s1) >> 0x10) & 0xFFFF;
        var_s3 = 0;
        var_s0 = (u8 *) var_s1;
        do {
            temp_v0 = TaLogic_GetFusionRes(*(u16 **)(var_s0 + 8));
            if ((temp_v0 != NULL) && ((u32) (var_s5 & 0xFFFF) < (u32) (TaHand_GetCardAPDP(*temp_v0) >> 0x10))) {
                var_s5 = (TaHand_GetCardAPDP(*temp_v0) >> 0x10) & 0xFFFF;
                var_s1 = temp_v0;
            }
            var_s3 += 1;
            var_s0 += 4;
        } while (var_s3 < 4);
    } else {
        return NULL;
    }
    return var_s1;
}

s32 TaLogic_GetEnchantQue(s32 arg0, u16 *arg1, void **arg2, s32 arg3) {
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

    totalHigh = (u32)TaHand_GetCardAPDP(*arg1) >> 16;
    totalLow = TaHand_GetCardAPDP(*arg1) & 0xFFFF;
    TaHand_GetNextHand(arg0, entries);
    status = Ta_IsActiveTrapB(arg0, 0x2B);
    if ((status >= 0) && (SzDuel_GetUnitStatus(status >> 8, status & 0xFF, 4) != 0)) {
        return 0;
    }

    i = 0;
    if (i < TaHand_GetNextHandNum(arg0)) {
        entry = entries;
        count = arg3 & 0xFF;
        do {
            if ((TaLogic_IsUseHandInCombo(i & 0xFF, arg1 + 1) & 0xFF) == 0) {
                id = *entry;
                if (((TaHand_GetCardKind(*entry) >> 5) == 2) && (*entry != 0x31C) && (*entry != 0x31B) &&
                    ((Ta_GetHandEnchant(*arg1, id) >> 16) == 1) &&
                    (TaEnc_IsEncDo(id) == 1)) {
                    if (arg2 != NULL) {
                        j = 0;
                        target = arg2;
                        goto targets_test_00278F10;
                    targets_body_00278F10:
                        TaLogic_IsKeepEnchant(*target, id, *arg1);
                        target++;
                        j++;
                    targets_test_00278F10:
                        if (j < count) {
                            goto targets_body_00278F10;
                        }
                    } else {
                        ((u8 *)arg1)[2 + (TaLogic_GetArrayLength(arg1 + 1) & 0xFF)] = i;
                        totalHigh += TaEnc_GetEncScore(id);
                        totalLow += TaEnc_GetEncScore(id);
                    }
                }
            }
            entry++;
            i++;
        } while (i < TaHand_GetNextHandNum(arg0));
    }
    return (totalHigh << 16) | (totalLow & 0xFFFF);
}

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

s32 TaLogic_IsKeepEnchant(void *arg0, s32 arg1, s32 arg2) {
    Condition_00279170 *condition = arg0;

    if (condition == NULL) {
        return 1;
    }
    if (arg1 != condition->id) {
        return 1;
    }
    switch (condition->operation) {
    case 36:
        if ((TaHand_GetCardAPDP(arg2) >> 16) >= condition->value) {
            return 1;
        }
        break;
    case 37:
        if ((TaHand_GetCardAPDP(arg2) >> 16) <= condition->value) {
            return 1;
        }
        break;
    }
    return 0;
}

void TaLogic_GetRoot(s32 arg0, s32 arg1, s32 arg2, s32 arg3,
                   s32 arg4, s32 arg5, s32 arg6, s32 arg7, u8 arg8) {
    extern s32 TaLogic_GetRoot2(s32, s32, s32, s32, s32, s32, s32, u8);

    TaLogic_GetRoot2(SzDuel_GetUnit(arg0, arg1), arg2, arg3, arg4,
                  arg5, arg6, arg7, arg8);
}

s32 TaLogic_GetRoot2(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s16 arg6, u8 arg7) {
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
    if (arg0 == 0) {
        return -1;
    }
    TaLogic_InitIgnoreLst(scratch);
    if (SzGame_GetHSyncCount() > 0x2EE0U) {
        return -1;
    }
    if (GetMoveRev(arg0, arg2, arg3) == 0) {
        return 0;
    }
    if ((((arg4 < arg2) ? arg2 : arg4) - ((arg2 < arg4) ? arg2 : arg4)) + (((arg5 < arg3) ? arg3 : arg5) - ((arg3 < arg5) ? arg3 : arg5)) > (s32)arg7) {
        return -1;
    }
    while (flag == 0 && (previous = (u8)level, arg7 >= previous)) {
        result = (s32)TaLogic_GetRootTree2((u8 *)result, 0, arg0, arg2, arg3, arg4, arg5, level, (s8 *)&flag, (s32)&arg6, 0, (u16 *)&x, (u16 *)&y, (s32)scratch);
        if (flag == 1) {
            TaLogic_GetShortRoot(arg1, result, arg4, arg5);
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


u8 *TaLogic_GetRootTree2(u8 *node, s32 parent, s32 card, s32 x, s32 y,
                  s32 targetX, s32 targetY, u8 limit, s8 *found, s32 mode,
                  u8 depth, u16 *pool, u16 *poolEnd, s32 arg13) {
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

    range = GetMoveRev(card, x, y);
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
                                         pool, poolEnd, arg13);
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

void TaLogic_IsPassRoot(s32 arg0, s32 arg1, s32 arg2, s32 arg3,
                   s32 arg4, s32 arg5, s32 arg6) {
    TaLogic_IsPassRoot2(SzDuel_GetUnit(arg0, arg1), arg2, arg3, arg4, arg5, arg6);
}


static inline s32 distance_002798C0(s32 y1, s32 x1, s32 y2, s32 x2) {
    return (((y2 < y1) ? y1 : y2) - ((y1 < y2) ? y1 : y2)) +
           (((x2 < x1) ? x1 : x2) - ((x1 < x2) ? x1 : x2));
}

static inline s32 absolute_002798C0(s32 value) {
    if (value >= 0) {
        return value;
    }
    return -value;
}

s32 TaLogic_IsPassRoot2(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    extern s32 Ta_IsVirus_Chk3();
    s32 flags;
    s32 delta;

    flags = GetMoveRev(arg0, arg1, arg2);
    if (arg0 == 0) {
        return 0;
    }
    if (distance_002798C0(arg1, arg2, arg3, arg4) == 0) {
        return 1;
    }
    if (distance_002798C0(arg1, arg2, arg3, arg4) == 1) {
        if ((SzDuel_GetField(arg3, arg4) == 8 && !(flags & 0x10)) ||
            (SzDuel_GetField(arg3, arg4) == 9 && Ta_IsVirus_Chk3(arg0, arg3, arg4) == 1)) {
            return 0;
        }
        if (SzDuel_GetMapUnit(arg3, arg4) != 0) {
            u16 tile = *(u16 *)arg5;
            if (tile != SzDuel_GetMapUnitID(arg3, arg4)) {
                return 0;
            }
        }
        return 1;
    } else if (distance_002798C0(arg1, arg2, arg3, arg4) == 2) {
        delta = absolute_002798C0(arg1 - arg3);
        switch (delta) {
        case 0: {
            s32 midpoint = (arg2 + arg4) >> 1;
            if (TaLogic_IsPassRoot2(arg0, arg1, arg2, arg3, midpoint, arg5) == 1) {
                return TaLogic_IsPassRoot2(arg0, arg1, midpoint, arg3, arg4, arg5);
            }
            break;
        }
        case 2: {
            s32 midpoint = (arg1 + arg3) >> 1;
            if (TaLogic_IsPassRoot2(arg0, arg1, arg2, midpoint, arg4, arg5) == 1) {
                return TaLogic_IsPassRoot2(arg0, midpoint, arg2, arg3, arg4, arg5);
            }
            break;
        }
        case 1:
            if (TaLogic_IsPassRoot2(arg0, arg1, arg2, arg3, arg2, arg5) == 1 &&
                TaLogic_IsPassRoot2(arg0, arg3, arg2, arg3, arg4, arg5) == 1) {
                return 1;
            }
            if (TaLogic_IsPassRoot2(arg0, arg1, arg2, arg1, arg4, arg5) == 1 &&
                TaLogic_IsPassRoot2(arg0, arg1, arg4, arg3, arg4, arg5) == 1) {
                return 1;
            }
            return 0;
        default:
            return 0;
        }
    }
    return 0;
}

void TaLogic_IsRunPassRoot(s32 arg0, s32 arg1, s32 arg2, s32 arg3,
                   s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    TaLogic_IsRunPassRoot2(SzDuel_GetUnit(arg0, arg1), arg2, arg3,
                  arg4, arg5, arg6, arg7);
}

s32 TaLogic_IsRunPassRoot2(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    extern s32 Ta_IsVirus_Chk3();
    s32 flags;
    s32 delta;
    s32 tile;
    s32 owner;
    s32 middle;
    u16 current;

    flags = GetMoveRev(arg0, arg1, arg2);
    if (arg0 == 0) {
        return 0;
    }
    if (distance_002798C0(arg1, arg2, arg3, arg4) == 0) {
        return 1;
    }
    if (distance_002798C0(arg1, arg2, arg3, arg4) == 1) {
        if ((SzDuel_GetField(arg3, arg4) == 8 && !(flags & 0x10)) ||
            (SzDuel_GetField(arg3, arg4) == 9 && Ta_IsVirus_Chk3(arg0, arg3, arg4) == 1)) {
            return 0;
        } else {
            if (SzDuel_GetMapUnit(arg3, arg4) != 0) {
                current = *(u16 *)arg5;
                if (current == SzDuel_GetMapUnitID(arg3, arg4)) {
                    return 1;
                }
                if (!(arg6 & 0xFF)) {
                    return 0;
                }
                tile = SzDuel_GetMapUnitID(arg3, arg4);
                owner = Ta_IsUnitControl(tile >> 8, tile & 0xFF);
                if (owner == Ta_IsUnitControl2((void *)arg0)) {
                    return 1;
                }
                return 0;
            }
            return 1;
        }
    } else if (distance_002798C0(arg1, arg2, arg3, arg4) == 2) {
        delta = absolute_002798C0(arg1 - arg3);
        switch (delta) {
        case 0:
            middle = (arg2 + arg4) >> 1;
            if (TaLogic_IsPassRoot2(arg0, arg1, arg2, arg3, middle, arg5) == 1) {
                return TaLogic_IsPassRoot2(arg0, arg1, middle, arg3, arg4, arg5);
            }
            break;
        case 2:
            middle = (arg1 + arg3) >> 1;
            if (TaLogic_IsPassRoot2(arg0, arg1, arg2, middle, arg4, arg5) == 1) {
                return TaLogic_IsPassRoot2(arg0, middle, arg2, arg3, arg4, arg5);
            }
            break;
        case 1:
            if (TaLogic_IsPassRoot2(arg0, arg1, arg2, arg3, arg2, arg5) == 1 &&
                TaLogic_IsPassRoot2(arg0, arg3, arg2, arg3, arg4, arg5) == 1) {
                return 1;
            }
            if (TaLogic_IsPassRoot2(arg0, arg1, arg2, arg1, arg4, arg5) == 1 &&
                TaLogic_IsPassRoot2(arg0, arg1, arg4, arg3, arg4, arg5) == 1) {
                return 1;
            }
            return 0;
        default:
            return 0;
        }
    }
    return 0;
}

void TaLogic_GetInvadeRoot(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4,
                   s32 arg5, s32 arg6, s32 arg7, s32 arg8, u8 arg9, u16 arg10) {
    TaLogic_GetInvadeRoot2(SzDuel_GetUnit(arg0, arg1), arg2, arg3, arg4, arg5,
                  arg6, arg7, arg8, arg9, arg10);
}

s32 TaLogic_GetInvadeRoot2(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, u8 arg8, u16 arg9) {
    extern s32 GetMoveRev(s32, s32, s32);
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
    if (arg0 == 0) {
        return -1;
    }
    if (GetMoveRev(arg0, arg2, arg3) == 0) {
        return 0;
    }
    if ((((arg4 < arg2) ? arg2 : arg4) - ((arg2 < arg4) ? arg2 : arg4)) + (((arg5 < arg3) ? arg3 : arg5) - ((arg3 < arg5) ? arg3 : arg5)) > (s32)arg8) {
        return -1;
    }
    TaLogic_InitIgnoreLst(scratch);
    while (flag != 1 && (previous = (u8)level, arg8 >= previous)) {
        result = TaLogic_GetInvadeRootTree2(result, 0, arg0, arg2, arg3, arg4, arg5, level, &flag, &arg6, arg7, arg9, 0, &x, &y, scratch);
        if (flag == 1) {
            TaLogic_GetShortRoot(arg1, result, arg4, arg5);
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

u8 *TaLogic_GetInvadeRootTree2(u8 *arg0, s32 arg1, void *arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, u8 arg7, u8 *arg_sp0, s32 *arg_sp8, s32 arg_sp10, u16 arg_sp18, u8 arg_sp20, u16 *arg_sp28, u16 *arg_sp30, s32 arg_sp38) {
    extern s32 GetMoveRev();
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
    s32 temp_s1;
    s32 var_s0;
    s32 var_s1;
    u8 *var_s2;
    u8 *var_s6;

    var_s6 = arg0;
    sp16C = arg5;
    sp168 = arg6;
    sp167 = arg7;
    temp_s1 = GetMoveRev(arg2, arg3, arg4);
    if (arg2 == NULL) {
        return NULL;
    }
    if (var_s6 == NULL) {
        if ((s32) arg_sp20 > (s32) sp167) {
            return NULL;
        }
        if ((var_s6 = TaLogic_RootTreeAloc(arg_sp28, arg_sp30)) == NULL) {
            return NULL;
        }
        TaLogic_SetRootTreeDat(var_s6, arg1, arg3, arg4);
        if ((arg3 == sp16C) && (arg4 == sp168)) {
            *arg_sp0 = 1;
            return var_s6;
        }
    }
    temp_s0 = temp_s1 & 0xF;
    spE0 = 0;
    var_s1 = GetCap(0, arg3 - temp_s0);
    if ((u32)(arg3 + temp_s0) >= 7U) {
        sp110 = 6;
    } else {
        sp110 = arg3 + temp_s0;
    }
    spFC = GetCap(0, arg4 - temp_s0);
    sp120 = arg4 + temp_s0;
    if (sp120 >= 7U) {
        sp120 = 6;
    }
    sp100 = (arg_sp20 != 0) ? 0U : 1U;
    if (var_s1 <= (s32) sp110) {
        sp140 = temp_s0 + 1;
        sp150 = arg_sp20 + 1;
        sp130 = var_s6;
        do {
            var_s0 = spFC;
            if (var_s0 <= (s32) sp120) {
                var_s2 = sp130;
                do {
                    if ((var_s1 >= 0) && (var_s0 >= 0) && (var_s1 < 7) && (var_s0 < 7) && ((u32) ((((var_s1 < arg3) ? arg3 : var_s1) - ((arg3 < var_s1) ? arg3 : var_s1)) + (((var_s0 < arg4) ? arg4 : var_s0) - ((arg4 < var_s0) ? arg4 : var_s0))) < sp140) && (((((var_s1 < arg3) ? arg3 : var_s1) - ((arg3 < var_s1) ? arg3 : var_s1)) + (((var_s0 < arg4) ? arg4 : var_s0) - ((arg4 < var_s0) ? arg4 : var_s0))) != 0)) {
                        if ((TaLogic_IsPassInvadeRoot2(arg2, arg3, arg4, var_s1, var_s0, arg_sp8, arg_sp10, sp100, arg_sp18) == 1) && (TaLogic_IsRootPast2(var_s6, var_s1, var_s0, arg3, arg4, arg_sp20) == 0)) {
                            *(u8 **)(var_s2 + 4) = TaLogic_GetInvadeRootTree2(*(u8 **)(var_s2 + 4), (s32)var_s6, arg2, var_s1, var_s0, sp16C, sp168, sp167, arg_sp0, arg_sp8, arg_sp10, arg_sp18, (u8)sp150, arg_sp28, arg_sp30, arg_sp38);
                        }
                        var_s2 += 4;
                        sp130 += 4;
                        spE0 += 1;
                    }
                    var_s0 += 1;
                } while (var_s0 <= (s32) sp120);
            }
            var_s1 += 1;
        } while (var_s1 <= (s32) sp110);
    }
    return var_s6;
}


static inline s32 distance_0027A710(s32 y1, s32 x1, s32 y2, s32 x2) {
    return (((y2 < y1) ? y1 : y2) - ((y1 < y2) ? y1 : y2)) +
           (((x2 < x1) ? x1 : x2) - ((x1 < x2) ? x1 : x2));
}

s32 TaLogic_IsPassInvadeRoot2(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4,
                  s32 *arg5, s32 arg6, u8 arg7, u16 arg8) {
    s32 flags;
    s32 dy;
    extern s32 TaLogic_IsUnitWin3();

    flags = GetMoveRev((s32)arg0, arg1, arg2);
    if (arg0 == NULL) {
        return 0;
    }
    if (distance_0027A710(arg1, arg2, arg3, arg4) == 0) {
        return 1;
    }
    if (distance_0027A710(arg1, arg2, arg3, arg4) == 1) {
        s32 cell;
        s32 y;
        s32 x;
        s32 result;

        if ((SzDuel_GetField(arg3, arg4) == 8 && !(flags & 0x10)) ||
            (SzDuel_GetField(arg3, arg4) == 9 &&
             Ta_IsVirus_Chk3(arg0, arg3, arg4) == 1)) {
            return 0;
        }
        if (SzDuel_GetMapUnit(arg3, arg4) == 0) {
            return 1;
        }
        cell = SzDuel_GetMapUnitID(arg3, arg4);
        if (arg5 != NULL && cell == *arg5) {
            return 1;
        }
        y = cell >> 8;
        x = cell & 0xFF;
        if (Ta_IsUnitControl(y, x) != Ta_IsUnitControl2(arg0)) {
            if (TaLogic_IsJudgeUnitDanger(y, x, arg6) != 0) {
                result = TaLogic_IsUnitWin2((s32)arg0, cell, arg3, arg4) > 0;
            } else {
                result = TaLogic_IsUnitWin3((s32)arg0, arg8, arg3, arg4) > 0;
            }
            if (result) {
                return 1;
            }
            return 2;
        } else {
            if (x != 0) {
                return arg7 == 1 ? 0 : 1;
            }
            return 0;
        }
    }
    if (distance_0027A710(arg1, arg2, arg3, arg4) == 2) {
        dy = arg1 - arg3;
        dy = dy >= 0 ? dy : -dy;
        switch (dy) {
        case 0: {
            s32 midX = (arg2 + arg4) >> 1;
            if (TaLogic_IsPassInvadeRoot2(arg0, arg1, arg2, arg3, midX, arg5, arg6, arg7, arg8) == 1) {
                return TaLogic_IsPassInvadeRoot2(arg0, arg1, midX, arg3, arg4, arg5, arg6, arg7, arg8);
            }
            goto failed;
        }
        case 2: {
            s32 midY = (arg1 + arg3) >> 1;
            if (TaLogic_IsPassInvadeRoot2(arg0, arg1, arg2, midY, arg4, arg5, arg6, arg7, arg8) == 1) {
                return TaLogic_IsPassInvadeRoot2(arg0, midY, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
            }
            goto failed;
        }
        case 1:
            if (TaLogic_IsPassInvadeRoot2(arg0, arg1, arg2, arg3, arg2, arg5, arg6, arg7, arg8) == 1 &&
                TaLogic_IsPassInvadeRoot2(arg0, arg3, arg2, arg3, arg4, arg5, arg6, arg7, arg8) == 1) {
                return 1;
            }
            if (TaLogic_IsPassInvadeRoot2(arg0, arg1, arg2, arg1, arg4, arg5, arg6, arg7, arg8) == 1 &&
                TaLogic_IsPassInvadeRoot2(arg0, arg1, arg4, arg3, arg4, arg5, arg6, arg7, arg8) == 1) {
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

s32 TaLogic_IsConnectRoot(void *arg0, u8 arg1, u8 arg2) {
    s32 i;
    void **children;
    s32 nextDepth;
    s32 result;

    if (arg0 != NULL) {
        if (arg1 == arg2) {
            return 1;
        }
        nextDepth = arg1 + 1;
        children = arg0;
        i = 0;
        do {
            result = TaLogic_IsConnectRoot(children[1], nextDepth, arg2);
            if (result == 1) {
                return result;
            }
            i++;
            children++;
        } while (i < 12);
    }
    return 0;
}

void TaLogic_GetShortRoot(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp18;
    u8 sp1F;

    sp1F = 0xFF;
    sp18 = 0;
    TaLogic_DoGetShortRoot(arg0, &sp18, &sp1F, arg1, arg2, arg3, arg0, 0);
}

typedef struct Position_0027ACB0 {
    u8 x : 4;
    u8 y : 4;
    u8 nextX : 4;
    u8 nextY : 4;
} Position_0027ACB0;

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

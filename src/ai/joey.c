/* Computer AI of Joey (duelist 15, duelistController15); also duelistController16, used by J. Shadi Morton (duelist 16). */

#include "common.h"

s32 TaLogic_GetNearCard2(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8,
                  s32 arg9);
extern int func_001E1030_b(int a, int b);

/* From the dotr-decomp CC0 bundle (commit 88c32bb2), chatC/imp/conv.py. */

struct DotrFinderUnit {
    unsigned short wUnit;
    unsigned short wOrder;
    unsigned short wPurpose;
    unsigned int dwGoal;
    unsigned char bCond : 2;
};
struct DotrFinderTask {
    unsigned short wUnit;
    unsigned char bPurpose;
    unsigned short wGoal;
    unsigned char bHand[5];
    int bOpen;
    unsigned char bDefense;
};
extern void func_0027B1B0_b(struct DotrFinderUnit *unit, int mode);
extern int func_0027D020_b(struct DotrFinderUnit *unit, int side, struct DotrFinderTask *task, int first, int view, int lvl, int g, int h);
extern int func_00150470_b(struct DotrFinderUnit *list, int side, struct DotrFinderTask *task);
extern void func_00150270_b(struct DotrFinderUnit *unit);
extern int func_00152100_b(struct DotrFinderUnit *unit, int side, struct DotrFinderTask *task, int first);
extern int func_001526D0_b(struct DotrFinderUnit *unit, int side, struct DotrFinderTask *task, int first);
extern int func_00152CD0_b(struct DotrFinderUnit *unit, int side, struct DotrFinderTask *task, int first, int e);
extern int func_00150C40_b(int pos, int side, struct DotrFinderTask *task);
/* Runs the run-away task for `unit` when it is face down; returns 1 if it did, else `done`. */
static inline int CRun_val(struct DotrFinderUnit *unit, int side, struct DotrFinderTask *task, int first, int done)
{
    if (SzDuel_GetUnitStatus(unit->wUnit >> 8, unit->wUnit & 0xff, 0) == 0) {
        func_00152100_b(unit, side, task, first);
        done = 1;
    }
    return done;
}
/* Runs the move task for `unit` when it is face down; returns 1 if it did, else `done`. */
static inline int CMove_val(struct DotrFinderUnit *unit, int side, struct DotrFinderTask *task, int first, int e, int done)
{
    if (SzDuel_GetUnitStatus(unit->wUnit >> 8, unit->wUnit & 0xff, 0) == 0) {
        func_00152CD0_b(unit, side, task, first, e);
        done = 1;
    }
    return done;
}
/* Runs the equip task for `unit`; returns 1. */
static inline int CEnc_val(struct DotrFinderUnit *unit, int side, struct DotrFinderTask *task, int first, int done)
{
    func_0027D020_b(unit, side, task, first, 0, TaLogic_Joey_GetWarnHideLvl(side), 5, 1);
    done = 1;
    return done;
}
/* Runs the run-away task for `unit` when it is face down (sets `*pd`). */
static inline void CRun_void(struct DotrFinderUnit *unit, int side, struct DotrFinderTask *task, int first, int *pd)
{
    if (SzDuel_GetUnitStatus(unit->wUnit >> 8, unit->wUnit & 0xff, 0) == 0) {
        func_00152100_b(unit, side, task, first);
        *pd = 1;
    }
}
/* Runs the move task for `unit` when it is face down (sets `*pd`). */
static inline void CMove_void(struct DotrFinderUnit *unit, int side, struct DotrFinderTask *task, int first, int e, int *pd)
{
    if (SzDuel_GetUnitStatus(unit->wUnit >> 8, unit->wUnit & 0xff, 0) == 0) {
        func_00152CD0_b(unit, side, task, first, e);
        *pd = 1;
    }
}
/* Runs the equip task for `unit` (sets `*pd`). */
static inline void CEnc_void(struct DotrFinderUnit *unit, int side, struct DotrFinderTask *task, int first, int *pd)
{
    func_0027D020_b(unit, side, task, first, 0, TaLogic_Joey_GetWarnHideLvl(side), 5, 1);
    *pd = 1;
}

/* This duelist's move: picks the next unit to act, gives it a task and turns that into input `pInput`; returns 1
   when it set one. */
int TaLogic_Joey_GetMinimumTask(void *pCtl, void *pInput, int wCursorPos)
{
    struct DotrFinderUnit * list = pCtl;
    struct DotrFinderTask * task = pInput;
    int side = SzDuel_GetTurnOwner();
    int done = 0;
    int r;
    int idx;

    (void)wCursorPos;
    if ((r = func_00150470_b(list, side, task)) < 0) {
        return 0;
    }
    idx = TaLogic_GetActionUnitFromOwnerID(list, r & 0xffff);
    if (idx < 0) {
        return 0;
    }
    if ((r >> 16) == 1) {
        if (((list[idx].wPurpose >> 8) & 0xff) == 10) {
            func_0027B1B0_b(&list[idx], 1);
        } else {
            func_0027B1B0_b(&list[idx], 0);
        }
        return 1;
    }
    func_00150270_b(&list[idx]);
    switch ((list[idx].wPurpose >> 8) & 0xff) {
    case 5:
        CRun_void(&list[idx], side, task, 1, &done);
        break;
    case 2:
        if (SzDuel_GetUnitStatus(list[idx].wUnit >> 8, list[idx].wUnit & 0xff, 0) == 0) {
            if (func_001526D0_b(&list[idx], side, task, 1) < 0) {
                func_0027B1B0_b(&list[idx], 1);
                return 1;
            }
            done = 1;
        }
        break;
    case 10:
        if (func_00150C40_b(list[idx].wUnit, side, task) < 0) {
            func_0027B1B0_b(&list[idx], 1);
            task->bPurpose = 255;
            task->bOpen = 0;
            break;
        }
        func_0027B1B0_b(&list[idx], 1);
        done = 1;
        break;
    case 6:
        CMove_void(&list[idx], side, task, 1, 0, &done);
        break;
    case 3:
        CMove_void(&list[idx], side, task, 1, 1, &done);
        break;
    case 11:
        TaLogic_Joey_GetMinimumTask_TrapMission(&list[idx], side, task, 1);
        done = 1;
        break;
    case 9:
        CEnc_void(&list[idx], side, task, 1, &done);
        break;
    case 14:
        TaLogic_GetMinimumTask_DoNone(&list[idx], side, task);
        done = 1;
        break;
    default:
        done = 0;
        break;
    }
    if (done == 1) {
        return 1;
    }
    done = 0;
    switch (list[idx].wPurpose & 0xff) {
    case 5:
        done = CRun_val(&list[idx], side, task, 0, done);
        break;
    case 2:
        if (SzDuel_GetUnitStatus(list[idx].wUnit >> 8, list[idx].wUnit & 0xff, 0) == 0) {
            if (func_001526D0_b(&list[idx], side, task, 0) < 0) {
                func_00152100_b(&list[idx], side, task, 0);
            }
            done = 1;
        }
        break;
    case 10:
        if (func_00150C40_b(list[idx].wUnit, side, task) < 0) {
            func_0027B1B0_b(&list[idx], 0);
            task->bPurpose = 255;
            done = 1;
            task->bOpen = 0;
            break;
        }
        func_0027B1B0_b(&list[idx], 0);
        done = 1;
        break;
    case 6:
        done = CMove_val(&list[idx], side, task, 0, 0, done);
        break;
    case 3:
        done = CMove_val(&list[idx], side, task, 0, 1, done);
        break;
    case 11:
        TaLogic_Joey_GetMinimumTask_TrapMission(&list[idx], side, task, 0);
        done = 1;
        break;
    case 9:
        done = CEnc_val(&list[idx], side, task, 0, done);
        break;
    case 14:
        TaLogic_GetMinimumTask_DoNone(&list[idx], side, task);
        break;
    default:
        return 0;
    }
    if (done == 1) {
        return 1;
    }
    return 0;
}

typedef struct {
    u16 pos;
    u16 unk2;
    u16 unk4;
    u16 unk6;
    s32 unk8;
} Unit_00150270;

/* Gives a unit of this duelist its order for this turn (attack, run, move, summon, guard). */
s32 TaLogic_Joey_CommandUnit(void *pCtl) {
    Unit_00150270 *unit = pCtl;
    s32 handle;

    SzDuel_GetUnitLoc(unit->pos >> 8, unit->pos & 0xFF);
    handle = Ta_IsUnitControl(unit->pos >> 8, unit->pos & 0xFF);
    if (SzDuel_GetUnit(unit->pos >> 8, unit->pos & 0xFF) != 0 &&
        SzDuel_GetUnitStatus(unit->pos >> 8, unit->pos & 0xFF, 0) == 0 && unit->pos != 0xFFFF) {
        if ((unit->pos & 0xFF) == 0) {
            if (unit->unk8 == -1) {
                if (TaLogic015_IsActiveMode() == 1) {
                    TaLogic_CommandStdLDUnit(unit, 3, 3, 0);
                } else if (TaLogic_IsAttackedNow(unit->pos >> 8, unit->pos & 0xFF, 0) == 1) {
                    if (SzDuel_InqHandPhase(unit->pos >> 8) == 1) {
                        unit->unk4 = 0x50A;
                    } else {
                        unit->unk4 = 0x5FF;
                    }
                } else {
                    if (SzDuel_InqHandPhase(unit->pos >> 8) == 1) {
                        unit->unk4 = 0xA05;
                    } else {
                        unit->unk4 = 0x5FF;
                    }
                }
            }
        } else {
            switch (SzDuel_GetUnitKind(unit->pos >> 8, unit->pos & 0xFF) >> 5) {
            case 0:
            case 1:
            case 3:
            case 4:
                TaLogic015_CommandBtlUnit(unit);
                break;
            case 2:
                TaLogic_CommandEncUnit(unit, 5, 0, (u8)TaLogic_Joey_GetWarnHideLvl(handle));
                break;
            default:
                unit->unk4 = 0x5FF;
                break;
            }
        }
        return 1;
    }
    return 0;
}

/* The next unit of side `nSide` to act: first one that can attack now, then the others by task. */
s32 TaLogic_Joey_GetNextActiveUnit(u16 *pCtl, s32 nSide, s32 pInput) {
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
    TaLogic_Joey_CommandUnit(pCtl + idx * 8);
    if (((pCtl[idx * 8 + 2] >> 8) & 0xFF) == 10) {
        if (SzDuel_InqHandPhase(nSide) == 1 && TaLogic_Joey_GetMinimumTask_Summon(pos, nSide, pInput) >= 0) {
            return pos | 0x10000;
        }
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_GetUnitStatus(nSide, 0, 0) == 0) {
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_InqHandPhase(nSide) == 1 && TaLogic_Joey_GetMinimumTask_Summon(pos, nSide, pInput) >= 0) {
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

struct DotrTryOrder {
    unsigned short position;
    unsigned short unknown_02;
    unsigned short unknown_04;
    unsigned short unknown_06;
    union {
        unsigned short half;
        int word;
    } flags;
};
struct DotrTryCell {
    unsigned short id;
    unsigned char kind;
};
extern void func_0027E770_b(void *buf);
extern int func_0027B200_b(int a, int b, int c, int d, int e, int f, int g, int h, unsigned char i);
extern int func_00150BE0_b(struct DotrTryOrder *order, int r1, int r2, int r3, int r4, int r5, int r6, int r7, struct DotrTryCell *cells, int s1, unsigned short *a, unsigned short *b, int n, void *buf);

/* Orders a fighting unit (task `pTask`): straight at its goal when the path is open, else the nearest enemy it can
   beat. */
void TaLogic015_CommandBtlUnit(void *pTask)
{
    struct DotrTryOrder * order = pTask;
    unsigned char buf[112];
    struct DotrTryCell cells[22];
    unsigned short a;
    unsigned short b;
    int here;
    int other;
    int side;
    int there;
    int word;
    int i;
    int r;
    unsigned char deep;

    deep = TaLogic015_IsActiveMode();
    if (SzDuel_GetUnit(order->position >> 8, order->position & 0xff) == 0) {
        return;
    }
    side = Ta_GetCurrentSide(order->position >> 8, order->position & 0xff);
    other = (side == 0 ? 1 : 0) << 8;
    here = SzDuel_GetUnitLoc(order->position >> 8, order->position & 0xff);
    there = SzDuel_GetUnitLoc(other >> 8, other & 0xff);
    word = SzDuel_GetUnit(order->position >> 8, order->position & 0xff);
    func_0027E770_b(buf);
    if (func_001E1030_b(order->position >> 8, order->position & 0xff) == 686) {
        order->unknown_04 = 0xcff;
        return;
    }
    for (i = 0; i < 22; i++) {
        cells[i].id = 0xffff;
        cells[i].kind = 0xff;
    }
    if (func_0027B200_b(order->position >> 8, order->position & 0xff, (unsigned char)here, here >> 8, other >> 8, other & 0xff, (unsigned char)there, there >> 8, 2) > 0) {
        if ((SzDuel_GetUnitKind(order->position >> 8, order->position & 0xff) >> 5) == 0) {
            order->unknown_04 = 0x2ff;
        } else {
            order->unknown_04 = 0xbff;
        }
        order->flags.word = (other << 16) | order->flags.half;
        return;
    }
    b = 0;
    a = 0;
    for (other = 1; other <= (deep ? 5 : 2); other++) {
        r = func_00150BE0_b(order, 0, word, (unsigned char)here, here >> 8, Ta_GetCurrentSide(order->position >> 8, order->position & 0xff) == 0 ? 1 : 0, other & 0xff, TaLogic_Joey_GetWarnHideLvl(side), cells, 0, &a, &b, (unsigned char)(deep ? 5 : 2), buf);
        switch (r) {
        case 3:
            order->unknown_04 = 0x6ff;
            order->flags.word = (here << 16) | order->flags.half;
            return;
        case 2:
            order->unknown_04 = 0x3ff;
            order->flags.word = (here << 16) | order->flags.half;
            return;
        case 1:
            if (SzDuel_GetUnitKind(order->position >> 8, order->position & 0xff) >> 5) {
                order->unknown_04 = 0xbff;
            }
            return;
        case 0:
            order->unknown_04 = 0x3ff;
            order->flags.word = (here << 16) | order->flags.half;
            return;
        }
    }
    order->unknown_04 = 0x6ff;
    if (((here >> 8) <= 3 && (there >> 8) <= 3) || ((here >> 8) > 3 && (there >> 8) > 3)) {
        order->flags.word = (there << 16) | order->flags.half;
    } else {
        order->flags.word = (((here & 0xff) | 0x300) << 16) | order->flags.half;
    }
}

/* TaLogic_GetNearUnit with this duelist's view and strength settings. */
void TaLogic015_GetNearUnit(s32 pTask, s32 pTree, s32 pVarInfo, s32 nX, s32 nZ, s32 eSide, s32 bDist, s32 WarnLvl,
                   s32 nUnitLst, u16 wUnitNum, s32 wSize, s32 wNodeCount, u8 bChase, s32 wIgnoreLst) {
    TaLogic_GetNearUnit(pTask, pTree, pVarInfo, nX, nZ, eSide, bDist, WarnLvl, nUnitLst, wUnitNum, wSize, wNodeCount, bChase, 0, 2000, wIgnoreLst);
}

typedef struct {
    s16 card;
    u8 f2;
    u8 pad3;
    s16 f4;
    u8 pad6[6];
    s32 fC;
} Act_00150C40;

typedef struct {
    u8 pad0[0x3C];
    u16 id;
    u8 pad3E[0x22];
} Card_00150C40;

/* The summon task for side `nSide`: which hand cards to play and where, into `pInput`; -1 when it plays none. */
s32 TaLogic_Joey_GetMinimumTask_Summon(s32 wUnit, s32 nSide, s32 pInput) {
    extern s32 TaLogic_GetUnitNum(s32, s32);
    Card_00150C40 buf;
    s32 res;
    s32 type;
    Act_00150C40 *act = (Act_00150C40 *)pInput;
    s32 card;
    s32 r;

    act->card = wUnit;
    if (SzDuel_InqHandPhase(nSide) == 0) {
        return -1;
    }
    if (TaLogic_GetUnitNum(nSide, 0) == 5 && TaLogic_GetUnitNum(nSide, 1) == 5) {
        return -1;
    }
    type = TaLogic015_IsHandPlay(nSide, &buf);
    if (type < 0) {
        return -1;
    }
    act->f2 = 10;
    act->fC = 0;
    card = SzDuel_GetUnitLoc(wUnit >> 8, wUnit & 0xFF);
    if (type == 0) {
        if (TaLogic015_SetComboQue(nSide, act, &buf) >= 0) {
            res = TaLogic_GetNearCard2(&buf, card & 0xFF, card >> 8, nSide == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, TaLogic_Joey_GetWarnHideLvl(nSide));
            if (res < 0) {
                if (SzDuel_GetUnitMonsterCount(nSide) < 6) {
                    r = TaLogic015_GetSummonPiece(nSide, type, &buf, res);
                    if (r < 0) {
                        return -1;
                    }
                    act->f4 = r;
                    return 1;
                }
            } else {
                r = TaLogic015_GetSummonPiece(nSide, type, &buf, res);
                if (r < 0) {
                    return -1;
                }
                act->f4 = r;
                return 1;
            }
        }
    } else {
        res = TaLogic_GetNearCard2(&buf, card & 0xFF, card >> 8, nSide == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, TaLogic_Joey_GetWarnHideLvl(nSide));
    }
    if (type == 2) {
        TaLogic015_SetSpecialComboQue(nSide, act, &buf);
        r = TaLogic015_GetSummonPiece(nSide, type, &buf, res);
        if (r < 0) {
            return -1;
        }
        act->f4 = r;
        return 1;
    } else if (type == 3) {
        TaLogic015_GetSpecialComboPlay(nSide, act, &buf);
        r = TaLogic015_GetSummonPiece(nSide, type, &buf, res);
        if (r < 0) {
            return -1;
        }
        act->f4 = r;
        return 1;
    } else {
        if (TaLogic015_GetSpellPlay(nSide, (u8 *)act, &buf, buf.id) < 0) {
            return -1;
        }
        r = TaLogic015_GetSummonPiece(nSide, type, &buf, res);
        if (r < 0) {
            return -1;
        }
        act->f4 = r;
        return 1;
    }
}

/* Whether side `nSide` should play from its hand this turn (and what, into `pInput`). */
s32 TaLogic015_IsHandPlay(s32 nSide, void *pInput) {
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
        s32 result = TaLogic015_GetSpellPlay(nSide, (u8 *)data, pInput, 0x3E7);
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
    if (TaLogic015_GetSpecialComboPlay(nSide, (u8 *)data, pInput) == 1) {
        return 3;
    }
    if (TaLogic015_IsUseRevive(nSide) == 1) {
        s32 result = TaLogic015_GetSpecCardPlay(nSide, (u8 *)data, pInput, 0x2AE);
        if (result >= 0) {
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
        s32 result = TaLogic015_GetSpellPlay(nSide, (u8 *)data, pInput, 0x3E7);
        if (result >= 0) {
            return result;
        }
        return -1;
    }
}

typedef struct {
    u8 pad0[6];
    u8 slot[5];
} Obj1_00151170;

typedef struct {
    u8 pad0[0x38];
    s16 attack;
    s16 defense;
} Obj2_00151170;

/* Whether side `nSide` can play this duelist's special combination now. */
s32 TaLogic015_GetSpecialComboPlay(s32 nSide, void *bCombo, void *pCardInfo) {
    Obj2_00151170 *o2 = pCardInfo;
    Obj1_00151170 *o1 = bCombo;
    s32 list[8];
    s32 i;
    s32 found;
    u8 k;

    TaHand_GetNextHand(nSide, list);
    for (i = 0, found = 0; i < TaHand_GetNextHandNum(nSide); i++) {
        if (list[i] == 0x31F) {
            found = 1;
            o1->slot[0] = i;
        }
    }
    if (found == 0) {
        return -1;
    }
    for (i = 0, found = 0; i < TaHand_GetNextHandNum(nSide); i++) {
        if (list[i] == 7 && TaHand_CanAffordSummonCost(nSide, list[i]) == 1) {
            o1->slot[1] = i;
            found = 1;
        }
    }
    if (found == 0) {
        return -1;
    }
    k = 2;
    SzDuel_InitCardInfo(o2, 0x1F5);
    for (i = 0; i < TaHand_GetNextHandNum(nSide); i++) {
        if (i != o1->slot[0] && i != o1->slot[1]) {
            if (Ta_GetHandEnchant(0x1F5, list[i]) >= 0 && (TaHand_GetCardKind(list[i]) >> 5) == 2) {
                if (list[i] != 0x31B && list[i] != 0x31C) {
                    o1->slot[k] = i;
                    k++;
                    o2->attack += (s16)TaEnc_GetEncScore(list[i]);
                    o2->defense += (s16)TaEnc_GetEncScore(list[i]);
                }
            }
        }
    }
    return 1;
}

/* Whether side `nSide` holds card `nCardNo` and can summon it (its slot into `bCombo`, the card into `pCardInfo`);
   returns its kind group or -1. */
s32 TaLogic015_GetSpecCardPlay(s32 nSide, void *bCombo, void *pCardInfo, s32 nCardNo) {
    s32 i;
    s32 ids[8];

    TaHand_GetNextHand(nSide, ids);
    for (i = 0; i < TaHand_GetNextHandNum(nSide); i++) {
        if (((nCardNo & 0xFFFF) == ids[i]) &&
            (TaHand_CanAffordSummonCost(nSide, ids[i]) == 1)) {
            ((u8 *)bCombo)[6] = i;
            SzDuel_InitCardInfo(pCardInfo, ids[i]);
            return TaHand_GetCardKind(ids[i]) >> 5;
        }
    }
    return -1;
}

/* Whether side `nSide` plays a magic or ritual card from its hand now (its slot into `bCombo`, the card into
   `pCardInfo`). */
s32 TaLogic015_GetSpellPlay(s32 nSide, u8 *bCombo, void *pCardInfo, s32 nMode) {
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

typedef struct Info_001516A0 {
    u8 pad00[8];
    u16 x;
    s16 y;
} Info_001516A0;

typedef struct Sprite_001516A0 {
    Info_001516A0 *info;
    u8 pad04[0x34];
    s16 x;
    s16 y;
} Sprite_001516A0;

/* Fills hand combination `bCombo` for side `nSide`: the best fusion or equip chain, its card into `pCardInfo`. */
s32 TaLogic015_SetComboQue(s32 nSide, u8 *bCombo, void *pCardInfo) {
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
                if ((TaHand_GetCardKind(card) >> 5) == 0 && TaHand_CanAffordSummonCost(nSide, card) == 1) {
                    *node = TaLogic_GetFusionTree(nSide, (struct TreeTag *)*node, i & 0xFF, card & 0xFFFF, 0, (u16 *)&a, (u16 *)&b);
                    *node = TaLogic_GetFusionRes(*node);
                    value = TaLogic_GetEnchantQue(nSide, *node, 0, 0);
                    if (best < value) {
                        SzDuel_InitCardInfo(pCardInfo, **node);
                        ((Sprite_001516A0 *)pCardInfo)->x = (value >> 16) - (((Sprite_001516A0 *)pCardInfo)->info->x & 0x1FFF);
                        ((Sprite_001516A0 *)pCardInfo)->y = (value & 0xFFFF) - (((Sprite_001516A0 *)pCardInfo)->info->y & 0x1FFF);
                        TaLogic_Joey_ConvEmptyCombo(nSide, *node, entries);
                        TaLogic_CopyArray((u8 *)*node + 2, bCombo + 6);
                        best = value;
                        if (top < value) {
                            top = value;
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
} Info_00151880;

/* Fills an empty combination: the hand card side `nSide` can summon with the best attack plus defence. */
void TaLogic_Joey_ConvEmptyCombo(s32 nSide, void *pCardInfo, s32 *pResult) {
    Info_00151880 *info = pCardInfo;
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
                if (card != 0x3E7 && TaLogic015_IsRefuseEmptyCombo(card) == 0 && level >= TaHand_GetCardSummonCost2(card, nSide)) {
                    cost = TaHand_GetCardAPDP(card);
                    if ((cost & 0xFFFF) + (cost >> 16) * 2 < 0xDAD && TaHand_IsCardEffect(card) == 2 &&
                        (u16)TaLogic_GetHandFusion(info->id, (u16)card) == 0x3E7) {
                        TaLogic_AddEmptyCombo(info->values, buf[i]);
                    }
                }
            }
        }
    }
}

/* Whether this duelist keeps card `nCardNo` out of a summon (it is wanted for an equip). */
s32 TaLogic015_IsRefuseEmptyCombo(s32 nCardNo) {
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
} Obj1_00151AC0;

typedef struct {
    u8 pad0[0x38];
    s16 f38;
    s16 f3A;
    u16 id;
} Obj2_00151AC0;

/* Fills hand combination `bCombo` for side `nSide` with this duelist's special combination, its card into
   `pCardInfo`. */
s32 TaLogic015_SetSpecialComboQue(s32 nSide, void *bCombo, void *pCardInfo) {
    Obj1_00151AC0 *o1 = bCombo;
    Obj2_00151AC0 *o2 = pCardInfo;
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

typedef struct Nibbles_00151CF0 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_00151CF0;

/* The square side `nSide` summons a card of kind `sKind` to. */
s32 TaLogic015_GetSummonPiece(s32 nSide, u8 sKind, void *pInput, s32 nMode) {
    s32 bestPosition;
    s32 bestScore;
    Nibbles_00151CF0 cells[12];
    s32 targetY;
    s32 targetX;
    s32 kind;
    s32 type;
    s32 j;
    Nibbles_00151CF0 *cell;

    extern s32 TaLogic_IsUnitWin4();
    extern s32 SzDuel_Kind2Type();
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
    kind = (type = (u8)(*((u8 *)pInput + 0x3E) >> 5));
    if (kind == 0 || SzDuel_Kind2Type(kind, type) == 2) {
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
                        if (TaLogic_IsUnitWin4(pInput, nMode, TaLogic_Joey_GetWarnHideLvl(nSide), targetX, targetY, 0) > 0) {
                            score = TaLogic_GetInvadeRoot2(pInput, cells, x, y, targetX, targetY,
                                                nMode, 0, 3, (u16)TaLogic_Joey_GetWarnHideLvl(nSide));
                        } else {
                            score = TaLogic_GetRoot2((s32)pInput, (s32)cells, x, y, targetX, targetY, nMode, 3);
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

typedef struct Nibbles_00152100 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_00152100;

typedef struct Output_00152100 {
    u16 position;
    u8 action;
    u8 pad3;
    u16 destination;
    u8 pad6[6];
    s32 special;
    u8 result;
} Output_00152100;

/* The task of a unit running from danger (task `pTask`): the safest square in reach, into `pInput` (`fFirst` = 1
   for the unit's first-choice task). */
s32 TaLogic_Joey_GetMinimumTask_RunMission(UnitTask *pTask, s32 nSide, void *pInput, u8 fFirst) {
    Output_00152100 *output = pInput;
    s32 target;
    u8 endX;
    u8 extra;
    Nibbles_00152100 nibbles[12];
    s32 bestScore;
    s32 best;
    s32 i;
    Nibbles_00152100 *p;
    extern s32 TaLogic_Joey_IsOpenUnit();
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

        initialScore = TaLogic_Joey_GetWarnHideLvl(nSide);
        centerX = target & 0xFF;
        centerY = target >> 8;
        if (TaLogic_GetUnitWarning(centerX, centerY, pTask->ownerId, 3, initialScore, 0) == 0) {
            output->position = pTask->ownerId;
            output->action = 6;
            output->destination = target;
            output->result = TaLogic_IsDefStyleUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, output->destination, 1, 0);
            output->special = TaLogic_Joey_IsOpenUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, pTask);
            TaLogic_InitRogicControl(pTask, fFirst);
            return 0;
        }
        if ((range = GetMoveRange(SzDuel_GetUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF), centerX, centerY)) == 0) {
            output->position = pTask->ownerId;
            output->action = 6;
            output->destination = target;
            output->result = TaLogic_IsDefStyleUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, output->destination, 1, 0);
            output->special = TaLogic_Joey_IsOpenUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, pTask);
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
                        candidateScore = TaLogic_GetUnitWarning(x, y, pTask->ownerId, 3, (u16)TaLogic_Joey_GetWarnHideLvl(nSide), 0);
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
            output->special = TaLogic_Joey_IsOpenUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, pTask);
        } else {
            output->position = pTask->ownerId;
            output->action = 6;
            output->destination = target;
            output->result = TaLogic_IsDefStyleUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, output->destination, 1, 0);
            output->special = TaLogic_Joey_IsOpenUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, pTask);
        }
        TaLogic_InitRogicControl(pTask, fFirst);
        return 0;
    }
}

typedef struct Output_001526D0 {
    u16 position;
    u8 command;
    u8 pad3;
    u16 destination;
    u8 pad6[6];
    s32 state;
    u8 result;
} Output_001526D0;

typedef struct Point_001526D0 {
    u8 x : 4;
    u8 y : 4;
} Point_001526D0;

/* The task's target square: the second half-word when the second argument is 1, else the first. */
static inline u32 destination_001526D0(void *src, u8 mode) {
    if (mode == 1) {
        return (u16)(((UnitTask *)src)->dwGoal >> 16);
    }
    return *(u16 *)((u8 *)src + 8);
}

/* The task of a unit attacking (task `pTask`): its path to the goal, into `pInput`; -1 when it has none (`fFirst`
   = 1 for the unit's first-choice task). */
s32 TaLogic_Joey_GetMinimumTask_AtkMission(void *pTask, s32 nSide, u16 *pInput, u8 fFirst) {
    extern s32 TaLogic_Joey_IsOpenUnit();
    extern void TaLogic_GetInvadeRoot();
    s32 state;
    s32 current;
    s32 count;
    u8 mode;
    s32 target;
    s32 currentY;
    s32 currentX;
    s32 forced;
    s32 i;
    s32 unit;
    u32 destinationX;
    u32 destinationY;
    Point_001526D0 points[12];

    mode = TaLogic015_IsActiveMode();
    destinationX = destination_001526D0(pTask, fFirst);
    destinationY = destination_001526D0(pTask, fFirst);
    if (SzDuel_GetUnit(destinationY >> 8, destinationX & 0xFF) == 0) {
        TaLogic_InitRogicControl(pTask, 1);
        return -1;
    }
    state = TaLogic_Joey_IsOpenUnit(((UnitTask *)pTask)->ownerId >> 8,
                         ((UnitTask *)pTask)->ownerId & 0xFF, pTask);
    current = SzDuel_GetUnitLoc(((UnitTask *)pTask)->ownerId >> 8,
                           ((UnitTask *)pTask)->ownerId & 0xFF);
    destinationX = destination_001526D0(pTask, fFirst);
    destinationY = destination_001526D0(pTask, fFirst);
    target = SzDuel_GetUnitLoc(destinationY >> 8, destinationX & 0xFF);
    for (i = 0; i < 12; i++) {
        points[i].x = points[i].y = 0xF;
    }
    unit = SzDuel_GetUnit(((UnitTask *)pTask)->ownerId >> 8,
                        ((UnitTask *)pTask)->ownerId & 0xFF);
    currentX = current & 0xFF;
    currentY = current >> 8;
    if (GetMoveRange(unit, currentX, currentY) == 0) {
        s32 cost;
        ((Output_001526D0 *)pInput)->position = ((UnitTask *)pTask)->ownerId;
        ((Output_001526D0 *)pInput)->command = 6;
        ((Output_001526D0 *)pInput)->destination = current;
        cost = TaLogic_GetUnitWarning(currentX, currentY, nSide, 3, 1,
                            (u8)TaLogic_Joey_GetWarnHideLvl(nSide));
        if (cost >= SzDuel_GetUnitAP(((UnitTask *)pTask)->ownerId >> 8,
                                 ((UnitTask *)pTask)->ownerId & 0xFF, 0)) {
            ((Output_001526D0 *)pInput)->result = TaLogic_IsDefStyleUnit(
                ((UnitTask *)pTask)->ownerId >> 8,
                ((UnitTask *)pTask)->ownerId & 0xFF,
                pInput[2], 1, 0);
        } else {
            ((Output_001526D0 *)pInput)->result = TaLogic_IsDefStyleUnit(
                ((UnitTask *)pTask)->ownerId >> 8,
                ((UnitTask *)pTask)->ownerId & 0xFF,
                pInput[2], 0, 0);
        }
        TaLogic_InitRogicControl(pTask, fFirst);
    } else {
        s32 y;
        s32 x;
        Point_001526D0 *point;
        s32 index;
        s32 bestCost;
        s32 selected;
        s32 position = ((UnitTask *)pTask)->ownerId;
        TaLogic_GetInvadeRoot(position >> 8, position & 0xFF, points, currentX, currentY,
                      x = target & 0xFF, y = target >> 8,
                      destination_001526D0(pTask, fFirst), 0, 30,
                      (u16)TaLogic_Joey_GetWarnHideLvl(nSide));
        count = TaLogic_GetMinGoalCount((u8 *)points);
        selected = 0xFF;
        if (count > 0) {
            forced = 0;
            bestCost = 0xFFFF;
            for (index = 0; index < count; index++) {
                s32 hit = TaLogic015_IsOpenMoveUnit(((UnitTask *)pTask)->ownerId >> 8,
                                      ((UnitTask *)pTask)->ownerId & 0xFF,
                                      currentX, currentY, x, y);
                if (hit == 1) {
                    Point_001526D0 *forcedPoint = &points[index];
                    selected = index;
                    forced = 1;
                    index = count;
                    forcedPoint->x = x;
                    forcedPoint->y = y;
                } else {
                    s32 cost;
                    point = &points[index];
                    cost = TaLogic_GetUnitWarning(point->x, point->y, nSide,
                                        (u8)(mode ? 5 : 2), 1,
                                        (u8)TaLogic_Joey_GetWarnHideLvl(nSide));
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
            ((Output_001526D0 *)pInput)->position = ((UnitTask *)pTask)->ownerId;
            ((Output_001526D0 *)pInput)->command = 6;
            ((Output_001526D0 *)pInput)->destination = current;
            ((Output_001526D0 *)pInput)->state = state;
            ((Output_001526D0 *)pInput)->result = TaLogic_IsDefStyleUnit(
                ((UnitTask *)pTask)->ownerId >> 8,
                ((UnitTask *)pTask)->ownerId & 0xFF,
                ((Output_001526D0 *)pInput)->destination, 0, 0);
            TaLogic_InitRogicControl(pTask, fFirst);
            return 0;
        }
        if (selected != 0xFF) {
            ((Output_001526D0 *)pInput)->position = ((UnitTask *)pTask)->ownerId;
            ((Output_001526D0 *)pInput)->command = 6;
            ((Output_001526D0 *)pInput)->destination = (points[selected].y << 8) | points[selected].x;
            ((Output_001526D0 *)pInput)->state = forced;
            ((Output_001526D0 *)pInput)->result = TaLogic_IsDefStyleUnit(
                ((UnitTask *)pTask)->ownerId >> 8,
                ((UnitTask *)pTask)->ownerId & 0xFF,
                ((Output_001526D0 *)pInput)->destination, 0, 0);
        } else {
            ((Output_001526D0 *)pInput)->position = ((UnitTask *)pTask)->ownerId;
            ((Output_001526D0 *)pInput)->command = 6;
            ((Output_001526D0 *)pInput)->destination = current;
            ((Output_001526D0 *)pInput)->state = forced;
            ((Output_001526D0 *)pInput)->result = TaLogic_IsDefStyleUnit(
                ((UnitTask *)pTask)->ownerId >> 8,
                ((UnitTask *)pTask)->ownerId & 0xFF,
                ((Output_001526D0 *)pInput)->destination, 0, 0);
            TaLogic_InitRogicControl(pTask, fFirst);
            return 0;
        }
    }
    return 0;
}

typedef struct Coord_00152CD0 {
    u8 x : 4;
    u8 y : 4;
} Coord_00152CD0;

typedef struct Unit_00152CD0 {
    u16 position;
    u8 pad2[6];
    union {
        u32 packed;
        u16 low;
    } target;
} Unit_00152CD0;

typedef struct Output_00152CD0 {
    u16 position;
    u8 kind;
    u8 pad3;
    u16 target;
    u8 pad6[6];
    s32 value;
    u8 flag;
} Output_00152CD0;

/* The task's target square: the second half-word when the second argument is 1, else the first. */
static inline u32 target_00152CD0(void *unit, s32 side) {
    return side == 1 ? (u32)(u16)(((Unit_00152CD0 *)unit)->target.packed >> 16) : (u32)((Unit_00152CD0 *)unit)->target.low;
}

/* The smaller of the two values. */
static inline u32 minY_00152CD0(void *unit, s32 side, u8 coord) {
    return coord < (target_00152CD0(unit, side) >> 8) ? coord : (target_00152CD0(unit, side) >> 8);
}

/* The larger of the two values. */
static inline u32 maxY_00152CD0(void *unit, s32 side, u8 coord) {
    return (target_00152CD0(unit, side) >> 8) < coord ? coord : (target_00152CD0(unit, side) >> 8);
}

/* The smaller of the two values. */
static inline u32 minX_00152CD0(void *unit, s32 side, u8 coord) {
    return coord < (target_00152CD0(unit, side) & 0xFF) ? coord : (target_00152CD0(unit, side) & 0xFF);
}

/* The larger of the two values. */
static inline u32 maxX_00152CD0(void *unit, s32 side, u8 coord) {
    return (target_00152CD0(unit, side) & 0xFF) < coord ? coord : (target_00152CD0(unit, side) & 0xFF);
}

/* The task of a unit moving to its goal (task `pTask`), into `pInput` (`fFirst` = 1 for the unit's first-choice
   task). */
s32 TaLogic_Joey_GetMinimumTask_MoveMission(void *pTask, s32 nSide, void *pInput, u8 fFirst, u8 nKind) {
    extern s32 TaLogic_Joey_IsOpenUnit();
    extern s32 TaLogic_GetUnitWarning();
    extern void TaLogic_GetRoot();
    extern s32 TaLogic_IsDefStyleUnit(s32, s32, s32, u8, s32);
    Coord_00152CD0 coords[12];
    s32 initial;
    s32 cell;
    s32 count;
    u8 status;

    status = TaLogic015_IsActiveMode();
    initial = SzDuel_GetUnitLoc(((Unit_00152CD0 *)pTask)->position >> 8, ((Unit_00152CD0 *)pTask)->position & 0xFF);
    {
        s32 bestScore;
        s32 best;
        s32 side = fFirst;
        Coord_00152CD0 *candidate;
        s32 index;
        if (target_00152CD0(pTask, side) == 0xFFFF) {
            if (initial == target_00152CD0(pTask, side)) {
                ((Output_00152CD0 *)pInput)->position = ((Unit_00152CD0 *)pTask)->position;
                ((Output_00152CD0 *)pInput)->kind = 6;
                ((Output_00152CD0 *)pInput)->target = initial;
                ((Output_00152CD0 *)pInput)->flag = TaLogic_IsDefStyleUnit(((Unit_00152CD0 *)pTask)->position >> 8, ((Unit_00152CD0 *)pTask)->position & 0xFF, ((Output_00152CD0 *)pInput)->target, nKind, 0);
                ((Output_00152CD0 *)pInput)->value = TaLogic_Joey_IsOpenUnit(((Unit_00152CD0 *)pTask)->position >> 8, ((Unit_00152CD0 *)pTask)->position & 0xFF, pTask);
                TaLogic_InitRogicControl(pTask, fFirst);
                return 0;
            }
        }

        if (SzDuel_GetUnitStatus(((Unit_00152CD0 *)pTask)->position >> 8, ((Unit_00152CD0 *)pTask)->position & 0xFF, 4) != 0) {
            if ((SzDuel_GetUnitKind(((Unit_00152CD0 *)pTask)->position >> 8, ((Unit_00152CD0 *)pTask)->position & 0xFF) >> 5) == 1 ||
                (SzDuel_GetUnitKind(((Unit_00152CD0 *)pTask)->position >> 8, ((Unit_00152CD0 *)pTask)->position & 0xFF) >> 5) == 5) {
                SzDuel_SetUnitStatus(((Unit_00152CD0 *)pTask)->position >> 8, ((Unit_00152CD0 *)pTask)->position & 0xFF, 0, 1);
                ((Output_00152CD0 *)pInput)->position = ((Unit_00152CD0 *)pTask)->position;
                ((Output_00152CD0 *)pInput)->kind = 14;
                return 0;
            }
        }

        candidate = coords;
        {
            s32 i = 0;
            Coord_00152CD0 *entry = candidate;
            do {
                entry->x = entry->y = 0xF;
                i++;
                entry++;
            } while (i < 12);
        }

        cell = SzDuel_GetMapUnitID(target_00152CD0(pTask, side) & 0xFF, target_00152CD0(pTask, side) >> 8);
        if (cell < 0) {
            cell = 0xFFFF;
        }
        TaLogic_GetRoot(((Unit_00152CD0 *)pTask)->position >> 8, ((Unit_00152CD0 *)pTask)->position & 0xFF,
                     coords, initial & 0xFF, initial >> 8, target_00152CD0(pTask, side) & 0xFF,
                     target_00152CD0(pTask, side) >> 8, (u16)cell, 7);
        count = TaLogic_GetMinGoalCount((u8 *)coords);
        {
            if (count > 0) {
                best = 0xFF;
                bestScore = 0xFFFF;
                for (index = 0; index < count; index++) {
                    if (SzDuel_GetMapUnit(candidate->x, candidate->y) == 0) {
                        s32 score = TaLogic_GetUnitWarning(candidate->x, candidate->y, nSide, (u8)(status ? 5 : 2), 1, (u8)TaLogic_Joey_GetWarnHideLvl(nSide));
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
                            bestMinY = minY_00152CD0(pTask, side, bestY);
                            bestMaxY = maxY_00152CD0(pTask, side, bestY);
                            bestX = (&coords[best])->x;
                            bestMinX = minX_00152CD0(pTask, side, bestX);
                            bestMaxX = maxX_00152CD0(pTask, side, bestX);
                            currentY = (u8)candidate->y;
                            currentMinY = minY_00152CD0(pTask, side, currentY);
                            currentMaxY = maxY_00152CD0(pTask, side, currentY);
                            currentX = candidate->x;
                            currentMinX = minX_00152CD0(pTask, side, currentX);
                            currentMaxX = maxX_00152CD0(pTask, side, currentX);
                            if ((currentMaxX - currentMinX) + (currentMaxY - currentMinY) < (bestMaxX - bestMinX) + (bestMaxY - bestMinY)) {
                                bestScore = score;
                                best = index;
                            }
                        }
                    }
                    candidate++;
                }
            } else {
                ((Output_00152CD0 *)pInput)->position = ((Unit_00152CD0 *)pTask)->position;
                ((Output_00152CD0 *)pInput)->kind = 6;
                ((Output_00152CD0 *)pInput)->target = initial;
                ((Output_00152CD0 *)pInput)->flag = TaLogic_IsDefStyleUnit(((Unit_00152CD0 *)pTask)->position >> 8, ((Unit_00152CD0 *)pTask)->position & 0xFF, ((Output_00152CD0 *)pInput)->target, nKind, 0);
                ((Output_00152CD0 *)pInput)->value = TaLogic_Joey_IsOpenUnit(((Unit_00152CD0 *)pTask)->position >> 8, ((Unit_00152CD0 *)pTask)->position & 0xFF, pTask);
                TaLogic_InitRogicControl(pTask, fFirst);
                return 0;
            }

            if (best != 0xFF) {
                ((Output_00152CD0 *)pInput)->position = ((Unit_00152CD0 *)pTask)->position;
                ((Output_00152CD0 *)pInput)->kind = 6;
                ((Output_00152CD0 *)pInput)->target = (coords[best].y << 8) | coords[best].x;
                ((Output_00152CD0 *)pInput)->flag = TaLogic_IsDefStyleUnit(((Unit_00152CD0 *)pTask)->position >> 8, ((Unit_00152CD0 *)pTask)->position & 0xFF, ((Output_00152CD0 *)pInput)->target, nKind, 0);
                ((Output_00152CD0 *)pInput)->value = TaLogic_Joey_IsOpenUnit(((Unit_00152CD0 *)pTask)->position >> 8, ((Unit_00152CD0 *)pTask)->position & 0xFF, pTask);
            } else {
                ((Output_00152CD0 *)pInput)->position = ((Unit_00152CD0 *)pTask)->position;
                ((Output_00152CD0 *)pInput)->kind = 6;
                ((Output_00152CD0 *)pInput)->target = initial;
                ((Output_00152CD0 *)pInput)->flag = TaLogic_IsDefStyleUnit(((Unit_00152CD0 *)pTask)->position >> 8, ((Unit_00152CD0 *)pTask)->position & 0xFF, ((Output_00152CD0 *)pInput)->target, nKind, 0);
                ((Output_00152CD0 *)pInput)->value = TaLogic_Joey_IsOpenUnit(((Unit_00152CD0 *)pTask)->position >> 8, ((Unit_00152CD0 *)pTask)->position & 0xFF, pTask);
            }
            TaLogic_InitRogicControl(pTask, fFirst);
        }
    }
    return 0;
}

typedef struct Input_00153550 {
    u16 position;
    u8 pad2[6];
    u32 target;
} Input_00153550;

typedef struct Output_00153550 {
    u16 position;
    u8 action;
    u8 pad3;
    u16 destination;
    u8 pad6[10];
    u8 result;
} Output_00153550;

typedef struct Point_00153550 {
    u8 x : 4;
    u8 y : 4;
} Point_00153550;

#define MIN_00153550(a, b) ((a) < (b) ? (a) : (b))
#define MAX_00153550(a, b) ((b) < (a) ? (a) : (b))

/* The task's target square: the second half-word when the second argument is 1, else the first. */
static inline u32 target_00153550(void *src, s32 mode) {
    if (mode == 1) {
        return (u16)(((Input_00153550 *)src)->target >> 16);
    } else {
        return *(u16 *)((u8 *)src + 8);
    }
}

/* Sets a move task (action 6) to the given square, and whether the unit should stay in defence there. */
static inline void stay_00153550(void *src, void *dst, s32 position, s32 flag) {
    Input_00153550 *source = src;
    Output_00153550 *out = dst;

    out->position = source->position;
    out->action = 6;
    out->destination = position;
    out->result = TaLogic_IsDefStyleUnit(source->position >> 8, source->position & 0xFF,
                                out->destination, flag, 0);
}

/* The task of setting a trap (task `pTask`), into `pInput`. */
s32 TaLogic_Joey_GetMinimumTask_TrapMission(void *pTask, s32 nSide, void *pInput, s32 fFirst) {
    s32 start;
    s32 count;
    u8 flag;
    s32 startY;
    Point_00153550 points[12];
    s32 bestScore;
    Point_00153550 *p;
    s32 targetY;
    s32 targetX;
    s32 i;
    s32 bestIndex;
    s32 mode;
    s32 target;
    s32 startX;
    u32 xPosition;
    u32 yPosition;
    Input_00153550 *source = pTask;
    Output_00153550 *out = pInput;
    extern void TaLogic_GetInvadeRoot();

    flag = TaLogic015_IsActiveMode();
    mode = fFirst & 0xFF;
    xPosition = target_00153550(pTask, mode);
    yPosition = target_00153550(pTask, mode);
    if (SzDuel_GetUnit(yPosition >> 8, xPosition & 0xFF) == 0) {
        TaLogic_InitRogicControl(pTask, 1);
        return -1;
    }
    start = SzDuel_GetUnitLoc(source->position >> 8, source->position & 0xFF);
    xPosition = target_00153550(pTask, mode);
    yPosition = target_00153550(pTask, mode);
    target = SzDuel_GetUnitLoc(yPosition >> 8, xPosition & 0xFF);
    if (target_00153550(pTask, mode) == 0xFFFF) {
        stay_00153550(pTask, pInput, start, 1);
        return 0;
    } else {
        s32 unit = SzDuel_GetUnit(source->position >> 8, source->position & 0xFF);
        startX = start & 0xFF;
        startY = start >> 8;
        if (GetMoveRange(unit, startX, startY) == 0 ||
                TaLogic_IsAttackedNow(source->position >> 8, source->position & 0xFF, 0) == 1) {
            stay_00153550(pTask, pInput, start, 1);
            return 0;
        } else {
            p = points;
            {
                s32 n = 0;
                Point_00153550 *q = p;
                do {
                    q->x = q->y = 0xF;
                    q++;
                    n++;
                } while (n < 12);
            }
            {
                s32 position = source->position;
                u16 card = (u16)TaLogic_Joey_GetWarnHideLvl(nSide);
                TaLogic_GetInvadeRoot(position >> 8, position & 0xFF, points,
                    startX, startY, targetX = target & 0xFF,
                    targetY = target >> 8, target_00153550(pTask, mode),
                    0, 30, card);
            }
            count = TaLogic_GetMinGoalCount((u8 *)points);
            bestIndex = 0xFF;
            if (count > 0) {
                bestScore = 0;
                for (i = 0; i < count; i++, p++) {
                    if (SzDuel_GetMapUnit(p->x, p->y) == 0) {
                        s32 score = TaLogic_GetUnitWarning(p->x, p->y, nSide, (u8)(flag ? 5 : 2), 1,
                            (u8)TaLogic_Joey_GetWarnHideLvl(nSide));
                        if (bestScore < score) {
                            bestScore = score;
                            bestIndex = i;
                        } else if (score == bestScore) {
                            if (MAX_00153550(p->x, targetX) - MIN_00153550(p->x, targetX)
                                    + (MAX_00153550(p->y, targetY) - MIN_00153550(p->y, targetY))
                                    < MAX_00153550(points[bestIndex].x, targetX) - MIN_00153550(points[bestIndex].x, targetX)
                                    + (MAX_00153550(points[bestIndex].y, targetY) - MIN_00153550(points[bestIndex].y, targetY))) {
                                bestScore = score;
                                bestIndex = i;
                            }
                        }
                    }
                }
            } else {
                stay_00153550(pTask, pInput, start, 1);
                return 0;
            }
            if (bestIndex != 0xFF) {
                out->position = source->position;
                out->action = 6;
                out->destination = (points[bestIndex].y << 8) | points[bestIndex].x;
                out->result = TaLogic_IsDefStyleUnit(source->position >> 8,
                    source->position & 0xFF, out->destination, 0, 0);
            } else {
                stay_00153550(pTask, pInput, start, 1);
                return 0;
            }
        }
    }
    return 0;
}

/* Whether this duelist plays in its attacking mode this turn. */
s32 TaLogic015_IsActiveMode(void) {
    return (SzDuel_GetUnitCount(SzDuel_GetTurnOwner()) < 3) ? 0 : 1;
}

/* Whether this duelist opens (turns face up) unit (nSide, nID) now: 0 no, 1 or 2 by its kind. */
s32 TaLogic_Joey_IsOpenUnit(s32 nSide, s32 nID) {
    extern s32 SzDuel_GetUnitCardNo();
    u16 buf[22];
    s32 kind;
    u32 *info;
    s32 c1;
    s32 c2;
    s32 player;
    s32 y1;
    s32 x1;
    s32 y2;
    s32 x2;
    s32 pos;
    s32 score;

    kind = SzDuel_GetUnitCardNo(nSide, nID);
    SzDuel_GetUnitLoc(nSide, nID);
    player = Ta_IsUnitControl(nSide, nID);
    info = SzDuel_GetUnitEffect(nSide, nID, 0);
    if (SzDuel_GetUnitStatus(nSide, nID, 4) != 0) {
        return 0;
    }
    TaUtil_GetUnitLst(player, 2, buf);
    switch (SzDuel_GetUnitKind(nSide, nID) >> 5) {
    case 0:
        switch (kind) {
        case 0x24:
            if (Ta_GetUnitNumFrom22bitFlagList(SearchUnitByRange(0, 0, player, 1, 0x95F0037, 0xE)) >= 2) {
                return 1;
            }
            break;
        case 0xD5:
            if (Ta_GetUnitNumFrom22bitFlagList(SearchUnitByRange(0, 0, player, 1, 0x1D, 0x16)) >= 2) {
                return 1;
            }
            break;
        }
        return 2;
    case 1:
        if (TaLogic_GetActionReaction(nSide, nID, 0, 0, 6, 0) == 5) {
            return 2;
        }
        if (info == NULL) {
            return 2;
        }
        switch (*info >> 8) {
        case 0xD:
            return 1;
        case 0x21:
            TaLogic_GetUnitCtlLst2((player == 0) ? 1 : 0, buf, 0x1D, 0, 0);
            pos = TaLogic_GetMaxApUnit(buf);
            x1 = pos >> 8;
            y1 = pos & 0xFF;
            c1 = SzDuel_GetUnitLoc(x1, y1);
            TaLogic_GetUnitCtlLst(player, buf, 0x1D, 1);
            pos = TaLogic_GetMaxApUnit(buf);
            x2 = pos >> 8;
            y2 = pos & 0xFF;
            c2 = SzDuel_GetUnitLoc(x2, y2);
            TaUtil_GetUnitLst(player, 1, buf);
            if (TaUtil_GetUnitAP(x1, y1, c1 & 0xFF, c1 >> 8) >= 2000) {
                score = TaUtil_GetUnitAP(x1, y1, c1 & 0xFF, c1 >> 8);
                if (TaUtil_GetUnitAP(x2, y2, c2 & 0xFF, c2 >> 8) < score) {
                    return 1;
                }
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
s32 TaLogic015_IsOpenMoveUnit(s32 nSide, s32 nID, s32 nX, s32 nZ, s32 gX, s32 gZ) {
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

/* How careful this duelist is about hidden cards (by its life points and monster count). */
s32 TaLogic_Joey_GetWarnHideLvl(s32 nSide) {
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
        if (TaLogic_Joey_GetMinimumTask(w, &req, wCursorPos) == 0) {
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

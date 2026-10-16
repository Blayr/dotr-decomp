#include "common.h"

struct DotrFinishMoveSub {
    short h;
    signed char open : 1;
};
struct DotrFinishMoveInfo {
    int eNO;
    unsigned int dwFrom;
    unsigned int dwTo;
    unsigned int dwPar;
    struct DotrFinishMoveSub sub;
};
extern int func_001E1580_b(int a, int b);
extern int func_001E1640_b(int a, int b);
extern int func_001E1970_b(int a, int b, int value);
extern int func_001E1CB0_b(int a, int b);
extern int func_001E1A30_b(int a, int b);
extern int func_001E1D10_b(int a, int b);
extern int func_001E1A90_b(int a, int b);
extern int func_001E1030_b(int a, int b);
extern unsigned *func_00250740_b(int a, int b, int n);
extern int func_0024F830_b(int a, int b, int x, int y, struct DotrFinishMoveInfo *info);
#define P8 ((PrNo >> 8) & 1)
#define P9 ((PrNo >> 9) & 1)
#define P10 ((PrNo >> 10) & 1)
#define P11 ((PrNo >> 11) & 3)
#define P12 ((PrNo >> 12) & 1)
#define OPP(s) ((s) == 0 ? 1 : 0)
#define OPENSE(S, I) \
    if ((I) != 0 && !SzDuel_GetUnitStatus(S, I, 4)) { \
        TaUtil_DoOpen(S, I, 1); \
        SzSound_PlaySE(0, 38); \
    }
#define FADE(S, I) \
    Ta_UnitFade(S, I, -1, 1, 3); \
    func_001E1970_b(S, I, 0); \
    SzDuel_SetUnitCtlRateC(S, I, -1, 0);
#define MOVING(S, I) \
    (func_001E1CB0_b(S, I) != func_001E1A30_b(S, I) \
     || func_001E1D10_b(S, I) != func_001E1A90_b(S, I))
#define KILL(S, I) \
    if (P10 == 0) { \
        SzDuel_AddGrave(S, func_001E1030_b(S, I)); \
    } \
    p = func_00250740_b(S, I, 4); \
    if (p != 0 && (*p >> 8) == 81) { \
        SzDuel_AddGrave(Ta_GetCurrentSide(S, I), 672); \
    } \
    SzDuel_DelUnit(S, I); \
    SzData_CalcExp(S, func_001E1030_b(S, I), 1, -4);
#define VISUAL \
    Ta_SetRangeVisual(loc2 & 0xff, loc2 >> 8, 0, Ta_IsLDAbl(9, side), 1, 1, 11); \
    eInfo->eNO = 254; \
    eInfo->dwFrom = 0; \
    eInfo->dwTo = side << 8; \
    eInfo->dwPar = 16; \
    return 0x10003;
#define TRAP46 \
    u = Ta_IsActiveTrapB(OPP(nSide), 46); \
    if (u >= 0) { \
        eInfo->eNO = 102; \
        eInfo->dwFrom = 1; \
        eInfo->dwTo = u; \
        eInfo->dwPar = 0; \
        return 0x10003; \
    }
#define SET54(T, K) \
    eInfo->eNO = 54; \
    eInfo->dwFrom = (tSide << 8) | tID; \
    eInfo->dwTo = (nSide << 8) | nID; \
    eInfo->dwPar = (T) | (K);
#define HI(v) (((v) & 0xff) << 16)
#define HW(v) (((v) & 0xffff) << 16)

int Ta_FinishMove(int nSide, int nID, int nX, int nZ, void *eInfo_v, int PrNo)
{
    extern int Ta_Manage_ActEfc();
    struct DotrFinishMoveInfo * eInfo = eInfo_v;
    




    
    int loc2;
    int f8;
    unsigned *p;
    int ret;
    int f9;
    int k;
    int m;
    int u;
    int side;
    int r;
    int g9;
    int g8;
    int tSide;
    int t;
    int v;
    int loc;
    int tID;
    int no;
    int t3;
    int t2;
    unsigned *e;
    struct DotrFinishMoveSub *sub;

    
    sub = &eInfo->sub;
    eInfo->eNO = 999;
    eInfo->dwFrom = 0;
    eInfo->dwTo = 0;
    eInfo->dwPar = 0;
    


    r = SzDuel_GetMapUnitID(nX, nZ);
    if (r >= 0) {
        tSide = r >> 8;
        tID = r & 0xff;
    }
    
    loc = SzDuel_GetUnitLoc(nSide, nID);
    no = PrNo & 0xff;
    switch (no) {
    case 0:
        if (!SzDuel_GetUnitStatus(nSide, nID, 4) && SzDuel_GetUnitStatus(nSide, nID, 2)) {
            

            eInfo->sub.open = -1;
        } else {
            eInfo->sub.open = 0;
        }
        return 1;
    case 1:
        if (Ta_IsUnitControl(nSide, nID) == Ta_IsUnitControl(tSide, tID)) {
            return 17;
        }
        side = Ta_GetCurrentSide(nSide, nID);
        loc2 = SzDuel_GetUnitLoc(side, 0);
        if ((t = Ta_IsActiveTrapB(Ta_GetCurrentSide(nSide, nID), 4)) >= 0) {
            if (Ta_IsLDRangeAvilityWithLocation(nSide, nID, nX, nZ, 11)) {
                VISUAL
            }
            TRAP46
            if (Ta_IsResistAll(nSide, nID)) {
                SET54(t, 0x40000)
                return 0x10003;
            }
            SET54(t, 0x40000)
            return 0x1010f;
        }
        if ((t2 = Ta_IsActiveTrapB(Ta_GetCurrentSide(nSide, nID), 48)) >= 0) {
            if (Ta_IsLDRangeAvilityWithLocation(nSide, nID, nX, nZ, 11)) {
                VISUAL
            }
            if (Ta_IsResistAll(nSide, nID)) {
                return 3;
            }
            TRAP46
            SET54(t2, 0x300000)
            return 0x1000f;
        }
        if ((t3 = Ta_IsActiveTrapB(Ta_GetCurrentSide(nSide, nID), 49)) >= 0) {
            if (Ta_IsLDRangeAvilityWithLocation(nSide, nID, nX, nZ, 11)) {
                VISUAL
            }
            if (Ta_IsResistAll(nSide, nID)) {
                return 3;
            }
            TRAP46
            SET54(t3, 0x310000)
            return 0x10003;
        }
        return 3;
    case 3:
        if (r >= 0) {
            if (Ta_IsUnitControl(nSide, nID) == Ta_IsUnitControl(tSide, tID)) {
                return 5;
            }
            if (SzDuel_GetUnitKind(tSide, tID) >> 5) {
                return 2;
            }
            if (SzDuel_GetUnitKind(nSide, nID) >> 5) {
                return 6;
            }
            if ((e = func_00250740_b(tSide, tID, 3)) == 0) {
                OPENSE(tSide, tID)
                return 2;
            }
            if (SzDuel_GetUnitStatus(tSide, tID, 4)) {
                if (tID != 0) {
                    TaUtil_DoOpen(tSide, tID, 1);
                }
                return 2;
            }
            m = 1;
            OPENSE(tSide, tID)
            v = Ta_Manage_ActEfc(e, tSide, tID, nSide, nID, nX, nZ, eInfo, sub, m);
            if ((v >> 8) > 0) {
                if ((v >> 11) & 1) {
                    return HI(v) | 14;
                }
                if ((v >> 8) & 1) {
                    return HI(v) | 14;
                }
                if ((v >> 9) & 1) {
                    return HI(v) | ((((v >> 10) & 1) << 9) | ((((v >> 9) & 1) << 8) | 15));
                }
                if ((v >> 10) & 1) {
                    ret = HI(v) | ((((v >> 10) & 1) << 9) | ((((v >> 9) & 1) << 8) | 11));
                } else {
                    ret = 14;
                }
                return ret;
            }
            return HI(v) | 2;
        }
        return 18;
    case 2:
        if (func_001E1580_b(nSide, nID) > 0 || func_001E1640_b(nSide, nID) > 0
            || (SzDuel_GetUnitStatus(nSide, nID, 5) && SzDuel_GetUnitStatus(nSide, nID, 3))) {
            return 14;
        }
        if (SzDuel_GetUnitKind(nSide, nID) >> 5) {
            return 6;
        }
        if (SzDuel_GetUnitStatus(nSide, nID, 4)) {
            if (!(SzDuel_GetUnitKind(tSide, tID) >> 5)) {
                OPENSE(nSide, nID)
            }
            return 6;
        }
        if ((e = func_00250740_b(nSide, nID, 3)) == 0) {
            if (!(SzDuel_GetUnitKind(tSide, tID) >> 5)) {
                OPENSE(nSide, nID)
            }
            return 6;
        }
        if (eInfo->sub.open == 0) {
            if (!(SzDuel_GetUnitKind(tSide, tID) >> 5)) {
                m = 1;
                OPENSE(nSide, nID)
                v = Ta_Manage_ActEfc(e, nSide, nID, tSide, tID, nX, nZ, eInfo, sub, m);
                if ((v >> 8) > 0) {
                    if ((v >> 11) & 1) {
                        return HI(v) | 14;
                    }
                    if ((v >> 8) & 1) {
                        return HI(v) | 0x20e;
                    }
                    if ((v >> 10) & 1) {
                        return HI(v) | ((((v >> 9) & 1) << 9) | ((((v >> 10) & 1) << 8) | 15));
                    }
                    if ((v >> 9) & 1) {
                        return HI(v) | ((((v >> 9) & 1) << 9) | ((((v >> 10) & 1) << 8) | 11));
                    }
                } else {
                    return HI(v) | 6;
                }
            }
            return 6;
        }
        m = 1;
        OPENSE(nSide, nID)
        v = Ta_Manage_ActEfc(e, nSide, nID, tSide, tID, nX, nZ, eInfo, sub, m);
        if ((v >> 8) > 0) {
            if ((v >> 11) & 1) {
                return HI(v) | 14;
            }
            if ((v >> 8) & 1) {
                return HI(v) | 14;
            }
            if ((v >> 10) & 1) {
                return HI(v) | ((((v >> 9) & 1) << 9) | ((((v >> 10) & 1) << 8) | 15));
            }
            if ((v >> 9) & 1) {
                ret = HI(v) | ((((v >> 9) & 1) << 9) | ((((v >> 10) & 1) << 8) | 11));
            } else {
                ret = 6;
            }
            return ret;
        }
        return HI(v) | 6;
    case 17:
        if (!(SzDuel_GetUnitKind(nSide, nID) >> 5)) {
            if (eInfo->sub.open != 0) {
                OPENSE(nSide, nID)
                if ((e = func_00250740_b(nSide, nID, 3)) != 0) {
                    v = Ta_Manage_ActEfc(e, nSide, nID, tSide, tID, nX, nZ, eInfo, sub, 2);
                    if ((v >> 8) > 0) {
                        if ((v >> 11) & 1) {
                            return HI(v) | 0x10e;
                        }
                        if ((v >> 10) & 1) {
                            return HI(v) | ((((v >> 9) & 1) << 9) | ((((v >> 10) & 1) << 8) | 15));
                        }
                        if ((v >> 9) & 1) {
                            return HI(v) | ((((v >> 9) & 1) << 9) | ((((v >> 10) & 1) << 8) | 11));
                        }
                    } else {
                        return HI(v) | 5;
                    }
                }
            }
            return 5;
        }
        return 5;
    case 6:
        v = Battle(tSide, tID, nSide, nID, nX, nZ, eInfo);
        switch (eInfo->eNO) {
        case 93:
            return (v << 16) | 16;
        case 94:
            if (((eInfo->dwPar >> 18) & 1) == 1) {
                return (((eInfo->dwPar >> 25) & 3) << 11) | ((((eInfo->dwPar >> 27) & 1) << 10) | ((((eInfo->dwPar >> 18) & 1) << 9) | ((((eInfo->dwPar >> 19) & 1) << 8) | 8))) | 0x70000;
            }
            if (((eInfo->dwPar >> 19) & 1) == 1) {
                ret = (((eInfo->dwPar >> 25) & 3) << 11) | ((((eInfo->dwPar >> 27) & 1) << 10) | ((((eInfo->dwPar >> 18) & 1) << 9) | ((((eInfo->dwPar >> 19) & 1) << 8) | 10))) | 0x70000;
            } else {
                ret = 0x70010;
            }
            return ret;
        case 95:
            if ((eInfo->dwPar & 1) == 1) {
                ret = (v << 16) | 0x110;
            } else {
                ret = (v << 16) | 0x20b;
            }
            return ret;
        case 36:
        case 37:
        case 43:
            if ((v >> 16) != 0) {
                ret = HW(v) | 0x110;
            } else {
                ret = HW(v) | 0x20b;
            }
            return ret;
        }
        return 15;
    case 5:
        v = SelfHeap(tSide, tID, nSide, nID, eInfo);
        switch (eInfo->eNO) {
        case 95:
            if (eInfo->dwPar == 1) {
                ret = (v << 16) | 0x10f;
            } else {
                ret = (v << 16) | 0x20b;
            }
            return ret;
        case 100:
            if (eInfo->dwPar == 999) {
                ret = (v << 16) | 11;
            } else {
                ret = (v << 16) | 11;
            }
            return ret;
        }
        if ((v >> 16) == 1) {
            ret = HW(v) | 0x110;
        } else {
            ret = HW(v) | 0x20b;
        }
        return ret;
    case 8:
        f8 = P8;
        v = Ta_Manage_DestEfc(tSide, tID, nSide, nID, nX, nZ, eInfo, f8);
        if (((v >> 10) & 1) == 1) {
            FADE(tSide, tID)
            if (f8) {
                ret = HI(v) | ((P11 << 11) | ((P10 << 10) | 0x309));
            } else {
                ret = HI(v) | ((P11 << 11) | ((P10 << 10) | 0x20f));
            }
            return ret;
        }
        if (((v >> 9) & 1) == 1) {
            FADE(tSide, tID)
            return HI(v) | ((P11 << 11) | ((P10 << 10) | 0x30f));
        }
        if (((v >> 8) & 1) == 1) {
            if (f8) {
                ret = HI(v) | ((P11 << 11) | ((P10 << 10) | 0x109));
            } else {
                ret = HI(v) | ((P11 << 11) | ((P10 << 10) | 11));
            }
            return ret;
        }
        if (f8) {
            FADE(tSide, tID)
            return HI(v) | ((P11 << 11) | ((P10 << 10) | 0x309));
        }
        FADE(tSide, tID)
        if (P12 == 1) {
            ret = HI(v) | ((P11 << 11) | ((P10 << 10) | 0x210));
        } else {
            ret = HI(v) | ((P11 << 11) | ((P10 << 10) | 0x20b));
        }
        return ret;
    case 9:
        f9 = P9;
        v = Ta_Manage_DestEfc(nSide, nID, -1, -1, nX, nZ, eInfo, f9);
        if (((v >> 8) & 1) != 1) {
            FADE(nSide, nID)
            return HI(v) | ((P11 << 11) | ((P10 << 10) | ((f9 << 9) | 0x10f)));
        }
        return HI(v) | ((P11 << 11) | ((P10 << 10) | ((f9 << 9) | 15)));
    case 10:
        f9 = P9;
        v = Ta_Manage_DestEfc(nSide, nID, tSide, tID, nX, nZ, eInfo, f9);
        if (((v >> 8) & 1) == 1) {
            return HI(v) | ((P11 << 11) | ((P10 << 10) | ((f9 << 9) | 16)));
        }
        FADE(nSide, nID)
        return HI(v) | ((P11 << 11) | ((P10 << 10) | ((f9 << 9) | 0x110)));
    case 11:
        g9 = P9;
        if (g9 == 1) {
            if (MOVING(tSide, tID)) {
                return (P11 << 11) | ((P10 << 10) | ((g9 << 9) | ((P8 << 8) | 11)));
            }
        }
        g8 = P8;
        if (g8 == 1) {
            if (MOVING(nSide, nID)) {
                return (P11 << 11) | ((P10 << 10) | ((g9 << 9) | ((g8 << 8) | 11)));
            }
        }
        if (g9 == 1) {
            KILL(tSide, tID)
        }
        if (g8 == 1) {
            KILL(nSide, nID)
        }
        if (SzDuel_GetUnit(nSide, nID) != 0 && func_001E1580_b(nSide, nID) == 0) {
            SzEffect_SetBusyFlag2((nSide << 8) | nID, 0);
            return (P11 << 11) | ((P10 << 10) | ((g9 << 9) | 12)) | 0x60000;
        }
        return (P11 << 11) | ((P10 << 10) | ((g9 << 9) | ((g8 << 8) | 14)));
    case 12:
        v = Ta_IsVirusAll(eInfo);
        if (Ta_GetAgreeOwnerIDon22bitFlagLst((nSide << 8) | nID, eInfo->dwTo)) {
            ret = HI(v) | ((P11 << 11) | ((P10 << 10) | ((P9 << 9) | 14)));
        } else {
            ret = HI(v) | ((P11 << 11) | ((P10 << 10) | ((P9 << 9) | 13)));
        }
        return ret;
    case 16:
        v = Ta_IsVirusAll(eInfo);
        return HI(v) | ((P11 << 11) | ((P10 << 10) | ((P9 << 9) | ((P8 << 8) | 15))));
    case 13:
        v = func_0024F830_b(nSide, nID, loc & 0xff, loc >> 8, eInfo);
        return HI(v) | ((P11 << 11) | ((P10 << 10) | ((P9 << 9) | 18)));
    case 14:
        return (P9 << 9) | ((P8 << 8) | 14);
    case 15:
        g9 = P9;
        if (g9 == 1) {
            if (MOVING(tSide, tID)) {
                return (P11 << 11) | ((P10 << 10) | ((g9 << 9) | ((P8 << 8) | 15)));
            }
        }
        SzEffect_SetBusyFlag2((nSide << 8) | nID, 0);
        g8 = P8;
        if (g8 == 1) {
            if (MOVING(nSide, nID)) {
                return (P11 << 11) | ((P10 << 10) | ((g9 << 9) | ((g8 << 8) | 15)));
            }
        }
        if (g9 == 1 || g8 == 1) {
            if (g9 == 1) {
                KILL(tSide, tID)
            }
            if (g8 == 1) {
                KILL(nSide, nID)
            }
            return 15;
        }
        return 14;
    case 4:
    case 7:
    case 18:
    default:
        k = SzDuel_GetUnitKind(nSide, nID) >> 5;
        if ((k != 1 && k != 5)
            || (!SzDuel_GetUnitStatus(nSide, nID, 4) && !SzDuel_GetUnitStatus(nSide, nID, 2))) {
            return (P9 << 9) | ((P8 << 8) | 14);
        }
        v = Ta_Open(nSide, nID, eInfo, no - 17);
        if ((v >> 16) == 0) {
            return HW(v) | ((P9 << 9) | 0x10e);
        }
        return HW(v) | ((P9 << 9) | (((v >> 16) + 17) | 0x100));
    }
}
#undef P8
#undef P9
#undef P10
#undef P11
#undef P12
#undef OPP
#undef OPENSE
#undef FADE
#undef MOVING
#undef KILL
#undef VISUAL
#undef TRAP46
#undef SET54
#undef HI
#undef HW

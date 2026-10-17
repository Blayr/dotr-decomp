#include "common.h"

/* The summon-cost change for card `cNo` of side `nSide` (the leader's level bonus). */
s32 Ta_GetSummonRev(s32 nSide, s32 cNo) {
    s32 temp_s0;
    u8 *temp_v0;
    u8 temp_s1;

    temp_v0 = SzDuel_GetCardConstInfo(cNo);
    if (temp_v0 == NULL) {
        return 0;
    }
    temp_s1 = *temp_v0;
    temp_s0 = temp_s1 & 0x1F;
    if (temp_s0 == (SzDuel_GetUnitKind(nSide, 0) & 0x1F)) {
        if (((s32) temp_s1 >> 5) == 0) {
            return Ta_GetLDLvRev(nSide);
        }
    }
    return 0;
}

struct jp_87592;
struct jp_87b56;
struct jp_88243 {
    unsigned int dwID;
    unsigned int dwParam;
};
struct jp_86d82 {
    struct jp_87592 *pConstInfo;
    struct jp_87b56 *pCardReq;
    struct jp_88243 aVarEffIdx[5];
    int nRotY;
    short sOfsX;
    short sOfsZ;
    short sVarAP;
    short sVarDP;
    unsigned short wCardNo;
    unsigned char bVarKind;
    unsigned char bVarAttr;
    unsigned char bMapX;
    unsigned char bMapZ;
    unsigned char bPosX;
    unsigned char bPosZ;
    unsigned char bOwner;
    unsigned char bID;
    unsigned char bModelID;
    unsigned char bSummonOrder;
    unsigned char bSummonCost;
    unsigned char bCurseRest;
    unsigned char bSpellRest;
    unsigned char bDelayCount;
    unsigned char bMovable;
    unsigned char bDarkRate;
    unsigned char bCtlModeC;
    unsigned char bCtlModeM;
    unsigned char bCtlGoalC;
    unsigned char bCtlGoalM;
    unsigned char bCtlRateC;
    unsigned char bCtlRateM;
    unsigned char bOpenRate;
    unsigned char bDefenseRate;
    int nCtlFlipC : 2;
    int nCtlFlipM : 2;
    int nOpenFlip : 2;
    int nDefenseFlip : 2;
    int fFinish : 1;
    int fRevolt : 1;
    int fOpen : 1;
    int fDefense : 1;
    int fOpenF : 1;
    int fDefenseF : 1;
    int fPickup : 1;
    int fCardBusy : 1;
    int fModelBusy : 1;
    int fCardColBusy : 1;
    int fHand : 1;
    int fCurse : 1;
    int nEffHandle : 6;
};

/* The result of combining hand cards `nCardNo` and `nCardNo2` of side `nSide` (fusion or equip). */
int Ta_GetComboResult(int nSide, int nCardNo, int nCardNo2)
{
    int Ret;
    int Num;
    int Combo[6];
    struct jp_86d82 nVarInfo;
    int temp;
    int bKind1;
    int bKind0;
    int cBuf;
    int Hand;
    int i;

    Hand = SzDuel_GetHandCount(nSide);
    for (i = 0; i < 6; i++) {
        Combo[i] = 999;
    }
    if (nCardNo != 999) {
        Combo[0] = nCardNo;
    }
    if (nCardNo != 999 && nCardNo2 != 999) {
        SzDuel_InitCardInfo(&nVarInfo, nCardNo);
        bKind0 = nVarInfo.bVarKind >> 5;
        SzDuel_InitCardInfo(&nVarInfo, nCardNo2);
        bKind1 = nVarInfo.bVarKind >> 5;
        if (bKind0 == 0 && bKind1 == 0) {
            Num = Fusion(nCardNo, nCardNo2);
            if (Num != 999) {
                temp = Num;
            } else {
                temp = nCardNo2;
            }
        } else if (bKind0 == 2 && bKind1 == 0) {
            Num = Do_Chk_Enc(nCardNo2, nCardNo);
            if (Num != 999) {
                if ((Num >> 30) & 1) {
                    temp = (Num >> 14) & 0x3FFF;
                } else {
                    temp = nCardNo2;
                }
            } else {
                temp = nCardNo2;
            }
        } else if (bKind1 == 2 && bKind0 == 0) {
            Num = Do_Chk_Enc(nCardNo, nCardNo2);
            if (Num != 999) {
                if ((Num >> 30) & 1) {
                    temp = (Num >> 14) & 0x3FFF;
                } else {
                    temp = nCardNo;
                }
            } else {
                temp = nCardNo2;
            }
        } else {
            temp = nCardNo2;
        }
        return temp;
    } else {
    for (i = 0; i < Hand; i++) {
        cBuf = SzDuel_InqHand(nSide, i);
        temp = (cBuf & 0xF000) >> 12;
        if (temp > 0) {
            Combo[temp] = cBuf & 0xFFF;
        }
    }
    Ret = Combo[0];
    for (i = 0; i < 5; i++) {
        if (Ret != 999) {
            SzDuel_InitCardInfo(&nVarInfo, Ret);
            bKind0 = nVarInfo.bVarKind >> 5;
        } else {
            bKind0 = -1;
        }
        if (Combo[i + 1] != 999) {
            SzDuel_InitCardInfo(&nVarInfo, Combo[i + 1]);
            bKind1 = nVarInfo.bVarKind >> 5;
        } else {
            return Ret;
        }
        if (bKind0 == 0 && bKind1 == 0) {
            Num = Fusion(Ret, Combo[i + 1]);
            if (Num != 999) {
                temp = Num;
            } else {
                temp = Combo[i + 1];
            }
        } else if (bKind0 == 2 && bKind1 == 0) {
            Num = Do_Chk_Enc(Combo[i + 1], Ret);
            if (Num != 999) {
                if ((Num >> 30) & 1) {
                    temp = (Num >> 14) & 0x3FFF;
                } else {
                    temp = Combo[i + 1];
                }
            } else {
                temp = Combo[i + 1];
            }
        } else if (bKind1 == 2 && bKind0 == 0) {
            Num = Do_Chk_Enc(Ret, Combo[i + 1]);
            if (Num != 999) {
                if ((Num >> 30) & 1) {
                    temp = (Num >> 14) & 0x3FFF;
                } else {
                    temp = Ret;
                }
            } else {
                temp = Combo[i + 1];
            }
        } else {
            temp = Combo[i + 1];
        }
        Ret = temp;
    }
    }
    return Ret;
}

/* The effect of a hand card being destroyed (none in this version). */
s32 Ta_Do_HandDestroyEfc(void *eInfo, s32 nSide, s32 nID) {
    ((s32 *)eInfo)[0] = 0x96;
    ((s32 *)eInfo)[1] = 0;
    ((s32 *)eInfo)[2] = (nSide << 8) | nID;
    ((s32 *)eInfo)[3] = 0;
    return 1;
}

/* The destiny-draw byte side `nSide` gets this turn (table entry | bonus level << 4), or -1: life points below
   1000, and only computer duelists 1 and 0x13 or a human whose leader has ability 3. */
s32 Ta_IsDestinyDraw(s32 nSide) {
    extern s32 SzDuel_GetPlayer();
    extern s32 SzData_GetRank();
    extern s32 TaHand_IsDestinyCondition(s32);
    s32 state;
    s32 value;

    state = SzDuel_GetPlayer(SzDuel_GetTurnOwner());
    if (state < 0x20 && state != 0x13 && state != 1) {
        return -1;
    }
    value = SzData_GetRank(nSide, SzData_GetLeader(nSide, SzData_GetCurrentDeck(nSide)));
    if (state > 99 && Ta_IsLDAbl(3, nSide) == 0) {
        return -1;
    }
    if (SzDuel_GetLP(nSide) < 1000) {
        if ((state = TaHand_IsDestinyCondition(nSide)) >= 0) {
            return state | (GetCap(0, value - 8) << 4);
        }
    }
    return -1;
}

struct jp_88243_26efd0 {
    unsigned int dwID;
    unsigned int dwParam;
};
extern int func_001DE4E0_b(int index);
extern unsigned *func_00250740_b(int a, int b, int n);
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

/* Whether side `nSide`'s board is bad enough for a destiny draw. */
int TaHand_IsDestinyCondition(int nSide)
{
    int i;
    int j;
    int Unit;
    int Loc;
    int Loc2;
    int Num;
    int Num2;
    int tempAP;
    int AP;
    int temp;
    struct jp_88243_26efd0 *eInfo;
    int Player;
    unsigned int eObj;

    Player = func_001DE4E0_b(SzDuel_GetTurnOwner());
    if (Player > 99) {
        eObj = SearchUnitByRange(0, 0, nSide, 3, 33, 14);
        Unit = Ta_GetUnitOwnerIDFromLstCount(eObj, 0);
        if (Ta_IsUnitControl(Unit >> 8, Unit & 0xff) != nSide) {
            if ((SzDuel_GetUnitKind(Unit >> 8, Unit & 0xff) == 7) & 0x1f) {
                Loc = SzDuel_GetUnitLoc(Unit >> 8, Unit & 0xff);
                Loc2 = SzDuel_GetUnitLoc(nSide, 0);
                if ((MAX(Loc & 0xff, Loc2 & 0xff) - MIN(Loc & 0xff, Loc2 & 0xff)) +
                        (MAX(Loc >> 8, Loc2 >> 8) - MIN(Loc >> 8, Loc2 >> 8)) <= 2) {
                    if (Ta_GetUnitNumFrom22bitFlagList(SearchUnitByRange(0, 0, nSide, 2, 7, 14)) >= 3) {
                        return 1;
                    }
                }
            }
        }
        eObj = SearchUnitByRange(0, 0, nSide, 2, 29, 14);
        Num = 0;
        if (Ta_GetUnitNumFrom22bitFlagList(eObj) >= 3) {
            if ((SzDuel_GetUnitKind(nSide, 0) == 9) & 0x1f) {
                for (i = 0; i < Ta_GetUnitNumFrom22bitFlagList(eObj); i++) {
                    Unit = Ta_GetUnitOwnerIDFromLstCount(eObj, i);
                    Loc = SzDuel_GetUnitLoc(Unit >> 8, Unit & 0xff);
                    if (CheckLandAgreement2(0, Unit >> 8, Unit & 0xff) != 1) {
                        if (TaUtil_GetUnitAP(Unit >> 8, Unit & 0xff, Loc & 0xff, Loc >> 8) >= 3000 &&
                            TaUtil_GetUnitAP(Unit >> 8, Unit & 0xff, Loc & 0xff, Loc >> 8) <= 3999) {
                            Num++;
                        }
                    }
                }
                if (Num >= 3) {
                    return 2;
                }
            }
        }
        eObj = SearchUnitByRange(0, 0, nSide, 3, 29, 14);
        Num2 = 0;
        Num = 0;
        if (Ta_GetUnitNumFrom22bitFlagList(eObj) >= 3) {
            for (i = 0; i < 7; i++) {
                for (j = 0; j < 7; j++) {
                    if (SzDuel_GetField(i, j) == 8) {
                        Num++;
                    }
                }
            }
            if (Num > 30) {
                i = 0;
                for (j = 0; j < Ta_GetUnitNumFrom22bitFlagList(eObj); j++) {
                    Unit = Ta_GetUnitOwnerIDFromLstCount(eObj, j);
                    eInfo = (struct jp_88243_26efd0 *)func_00250740_b(Unit >> 8, Unit & 0xff, 1);
                    if (eInfo != 0) {
                        if (eInfo->dwID >> 8 == 8 || eInfo->dwID >> 8 == 9 || eInfo->dwID >> 8 == 10) {
                            if (Ta_IsUnitControl(Unit >> 8, Unit & 0xff) == nSide) {
                                i++;
                            } else {
                                Num2++;
                            }
                        }
                    }
                }
                if (i == 0 && Num2 >= 3) {
                    return 3;
                }
            }
        }
        eObj = SearchUnitByRange(0, 0, nSide, 3, 33, 14);
        Unit = Ta_GetUnitOwnerIDFromLstCount(eObj, 0);
        if (Ta_IsUnitControl(Unit >> 8, Unit & 0xff) != nSide) {
            Loc = SzDuel_GetUnitLoc(Unit >> 8, Unit & 0xff);
            AP = -1;
            for (i = 0; i < 5; i++) {
                temp = SzDuel_InqHand(nSide, i);
                if (temp != 999) {
                    tempAP = (unsigned int)TaHand_GetCardAPDP(temp) >> 16;
                    if (tempAP > AP) {
                        AP = tempAP;
                    }
                }
            }
            if (TaUtil_GetUnitAP(Unit >> 8, Unit & 0xff, Loc & 0xff, Loc >> 8) > AP) {
                tempAP = TaUtil_GetUnitAP(Unit >> 8, Unit & 0xff, Loc & 0xff, Loc >> 8) - AP;
                if (SzDuel_GetLP(nSide == 0 ? 1 : 0) >> 1 > tempAP) {
                    return 4;
                }
            }
        }
        eObj = SearchUnitByRange(0, 0, nSide, 3, 33, 14);
        Unit = Ta_GetUnitOwnerIDFromLstCount(eObj, 0);
        Num = 0;
        if (Ta_IsUnitControl(Unit >> 8, Unit & 0xff) == nSide) {
            eObj = SearchUnitByRange(0, 0, nSide, 2, 30, 14);
            for (i = 0; i < Ta_GetUnitNumFrom22bitFlagList(eObj); i++) {
                Unit = Ta_GetUnitOwnerIDFromLstCount(eObj, i);
                if (SzDuel_Kind2Type(SzDuel_GetUnitKind(Unit >> 8, Unit & 0xff) >> 5) == 2) {
                    Num++;
                }
            }
            if (Num >= 4) {
                return 5;
            }
        }
    }
    if (Player > 99) {
        if (SzDuel_GetLP(nSide) <= 249) {
            return func_0019A5C8() % 2 == 0 ? 6 : 7;
        }
    } else {
        return func_0019A5C8() % 2 == 0 ? 6 : 7;
    }
    return -1;
}
#undef MAX
#undef MIN

/* Sets the destiny-draw effect for side `nSide`, into `eInfo`. */
s32 Ta_SetDestinyEffect(s32 nSide, s32 *eInfo) {
    extern s32 SzDuel_InqDestinyFlag(s32);
    s32 flags;

    flags = SzDuel_InqDestinyFlag(nSide);
    eInfo[0] = 0x3E7;
    eInfo[1] = 0;
    eInfo[2] = 0;
    eInfo[3] = 0;
    if (!(flags & 0x80) && SzDuel_GetHandCount(nSide) < 5) {
        if (eInfo != NULL) {
            eInfo[0] = 0x72;
            eInfo[1] = SzDuel_GetTurnOwner();
            eInfo[2] = 0;
            eInfo[3] = 0;
        }
        return 1;
    }
    return 0;
}

/* The three cards side `nSide`'s destiny draw can give into `wDrawCardNo`, and their chances in percent
   (summing to 100) into `wDestinyOfs`; marks the draw used. */
s32 Ta_GetDestinyDraw(s32 nSide, u16 *wDrawCardNo, s16 *wDestinyOfs, s32 eInfo) {
    extern u16 destinyDrawTable[];
    extern u16 D_002B8702[];
    extern u16 D_002B8704[];
    extern void SzDuel_SetDestinyFlag(s32, u8);
    extern s32 SzDuel_InqDestinyFlag(s32);
    s32 flags;
    s32 kind;
    s32 bonus;
    s32 index;

    flags = SzDuel_InqDestinyFlag(nSide);
    kind = SzDuel_GetUnitKind(nSide, 0) & 0x1F;
    bonus = (flags & 0xF0) * 5;
    wDrawCardNo[0] = 999;
    wDrawCardNo[1] = 999;
    wDrawCardNo[2] = 999;
    switch (kind) {
    case 0:
        wDestinyOfs[0] = 0;
        wDestinyOfs[1] = 0;
        wDestinyOfs[2] = 0;
        break;
    case 1:
        wDestinyOfs[0] = 2;
        wDestinyOfs[1] = 1;
        wDestinyOfs[2] = -3;
        break;
    case 2:
        wDestinyOfs[0] = 12;
        wDestinyOfs[1] = 6;
        wDestinyOfs[2] = -18;
        break;
    case 3:
        wDestinyOfs[0] = 2;
        wDestinyOfs[1] = 1;
        wDestinyOfs[2] = -3;
        break;
    case 4:
        wDestinyOfs[0] = 5;
        wDestinyOfs[1] = 3;
        wDestinyOfs[2] = -8;
        break;
    case 5:
        wDestinyOfs[0] = 8;
        wDestinyOfs[1] = 4;
        wDestinyOfs[2] = -12;
        break;
    case 6:
        wDestinyOfs[0] = 6;
        wDestinyOfs[1] = 3;
        wDestinyOfs[2] = -9;
        break;
    case 7:
        wDestinyOfs[0] = 0;
        wDestinyOfs[1] = 0;
        wDestinyOfs[2] = 0;
        break;
    case 8:
        wDestinyOfs[0] = 12;
        wDestinyOfs[1] = 6;
        wDestinyOfs[2] = -18;
        break;
    case 9:
        wDestinyOfs[0] = 10;
        wDestinyOfs[1] = 5;
        wDestinyOfs[2] = -15;
        break;
    case 10:
        wDestinyOfs[0] = 14;
        wDestinyOfs[1] = 7;
        wDestinyOfs[2] = -21;
        break;
    case 11:
        wDestinyOfs[0] = 15;
        wDestinyOfs[1] = 8;
        wDestinyOfs[2] = -23;
        break;
    case 12:
        wDestinyOfs[0] = 8;
        wDestinyOfs[1] = 4;
        wDestinyOfs[2] = -12;
        break;
    case 13:
        wDestinyOfs[0] = 14;
        wDestinyOfs[1] = 7;
        wDestinyOfs[2] = -21;
        break;
    case 14:
        wDestinyOfs[0] = 3;
        wDestinyOfs[1] = 1;
        wDestinyOfs[2] = -4;
        break;
    case 15:
        wDestinyOfs[0] = 10;
        wDestinyOfs[1] = 5;
        wDestinyOfs[2] = -15;
        break;
    case 16:
        wDestinyOfs[0] = 2;
        wDestinyOfs[1] = 1;
        wDestinyOfs[2] = -3;
        break;
    case 17:
        wDestinyOfs[0] = 13;
        wDestinyOfs[1] = 6;
        wDestinyOfs[2] = -19;
        break;
    case 18:
        wDestinyOfs[0] = 10;
        wDestinyOfs[1] = 5;
        wDestinyOfs[2] = -15;
        break;
    case 19:
        wDestinyOfs[0] = 10;
        wDestinyOfs[1] = 5;
        wDestinyOfs[2] = -15;
        break;
    case 20:
        wDestinyOfs[0] = -5;
        wDestinyOfs[1] = -2;
        wDestinyOfs[2] = 7;
        break;
    default:
        return -1;
    }
    if (!(flags & 0x80)) {
        index = (flags & 0xF) * 3;
        wDrawCardNo[0] = destinyDrawTable[index];
        wDrawCardNo[1] = D_002B8702[index];
        wDrawCardNo[2] = D_002B8704[index];
        wDestinyOfs[0] += bonus;
        wDestinyOfs[1] += (s16)(bonus >> 1);
        wDestinyOfs[2] = -(wDestinyOfs[0] + wDestinyOfs[1]);
        wDestinyOfs[0] += 10;
        wDestinyOfs[1] += 20;
        wDestinyOfs[2] += 70;
        flags |= 0x80;
        SzDuel_SetDestinyFlag(nSide, flags);
        if (eInfo != 0) {
            ((s32 *)eInfo)[0] = 0x72;
            ((s32 *)eInfo)[1] = SzDuel_GetTurnOwner();
            ((s32 *)eInfo)[2] = 0;
            ((s32 *)eInfo)[3] = 0;
        }
        return 1;
    }
    return -1;
}

/* The summon cost of hand card `nHand` of side `nSide`. */
s32 TaHand_GetCardSummonCost(s32 nHand, s32 nSide) {
    return TaHand_GetCardSummonCost2(nHand & 0xFFF, nSide);
}

typedef struct {
    u8 flags;
    u8 pad;
    u8 unused : 4;
    u8 value : 4;
} Flags_0026FA80;


/* The summon cost of card `nCardNo` for side `nSide` (its level, less the leader bonus when the card is of the
   leader's kind). */
s32 TaHand_GetCardSummonCost2(s32 nCardNo, s32 nSide) {
    s32 owner;
    s32 value;
    Flags_0026FA80 *data;

    data = (Flags_0026FA80 *)SzDuel_GetCardConstInfo(nCardNo);
    if (data == NULL) {
        return 0xFF;
    }
    value = data->value;
    if ((data->flags >> 5) == 0) {
        owner = data->flags & 0x1F;
        if (owner == (SzDuel_GetUnitKind(nSide, 0) & 0x1F)) {
            value -= Ta_GetLDLvRev(nSide);
        }
    }
    return value;
}

/* Whether side `nSide` has the summon power for card `nCardNo`. */
s32 TaHand_IsCardSummon2(s32 nSide, s32 nCardNo) {
    s32 temp_s0;

    temp_s0 = TaHand_GetCardSummonCost2(nCardNo, nSide);
    return (SzDuel_GetSummonPower(nSide) < temp_s0) ? 0 : 1;
}

/* Whether side `nSide` has the summon power for hand card `nHand`. */
s32 TaHand_IsCardSummon(s32 nSide, s32 nHand) {
    s32 temp_s0;

    temp_s0 = TaHand_GetCardSummonCost2(nHand & 0xFFF, nSide);
    return (SzDuel_GetSummonPower(nSide) < temp_s0) ? 0 : 1;
}

typedef struct CardStats_0026FBB0 {
    u8 padding[8];
    u16 attack;
    u16 defense;
} CardStats_0026FBB0;

/* Card `nCardNo`'s attack plus defence. */
u32 TaHand_GetCardAPDP(s32 nCardNo) {
    CardStats_0026FBB0 *card;

    if (nCardNo == 0x3E7) {
        return 0U;
    }
    card = (CardStats_0026FBB0 *)SzDuel_GetCardConstInfo(nCardNo);
    if (card == NULL) {
        return 0U;
    }
    return ((card->attack & 0x1FFF) << 16) | (card->defense & 0x1FFF);
}

/* Whether card `nCardNo` has an effect. */
s32 TaHand_IsCardEffect(s32 nCardNo) {
    u8 *p;

    if (nCardNo == 0x3E7) {
        return 0;
    }
    p = SzDuel_GetCardConstInfo(nCardNo);
    if (p == NULL) {
        return 0;
    }
    if ((p[0] >> 5) == 0) {
        if (*(u16 *)(p + 4) == 0xFFFF) {
            return 2;
        }
        return 1;
    }
    return 0;
}

/* Effect `EffIdxID` of card `nCardNo`. */
void *TaHand_GetCardEffect(s32 nCardNo, s32 EffIdxID) {
    u8 data[0x60];

    if (nCardNo == 0x3E7) {
        return NULL;
    }
    SzDuel_InitCardInfo(data, nCardNo);
    return data + 8 + EffIdxID * 8;
}

/* Card `nCardNo`'s kind. */
s32 TaHand_GetCardKind(s32 nCardNo) {
    u8 *temp_v0;

    if (nCardNo == 0x3E7) {
        return 0U;
    }
    temp_v0 = SzDuel_GetCardConstInfo(nCardNo);
    if (temp_v0 == NULL) {
        return 0U;
    }
    return *temp_v0;
}

/* Side `nSide`'s hand after the next draw, into `arNextHand`. */
void TaHand_GetNextHand(s32 nSide, s32 *arNextHand) {
    s32 index;
    s32 count;
    s32 value;

    index = 0;
    count = 0;
    do {
        value = SzDuel_InqHand(nSide, index) & 0xFFF;
        if (value != 0x3E7) {
            arNextHand[count] = value;
            count++;
        }
        index++;
    } while (index < 5);
    index = SzDuel_GetHandCount(nSide);
    count = 0;
    while (index < TaHand_GetNextHandNum(nSide)) {
        arNextHand[index] = SzDuel_InqDeck(nSide, count);
        index++;
        count++;
    }
}

/* How many cards side `nSide` will hold after the next draw. */
s32 TaHand_GetNextHandNum(s32 nSide) {
    s32 temp_s0;
    s32 var_v0;

    temp_s0 = SzDuel_GetHandCount(nSide);
    var_v0 = temp_s0 + SzDuel_GetDeckCount(nSide);
    if (var_v0 >= 5) {
        var_v0 = 5;
    }
    return var_v0;
}

typedef struct {
    u32 unused;
    u32 value1;
    u32 value2;
    s32 flags;
} Input_0026FE70;

typedef struct {
    u8 pad0[4];
    u16 state;
    u8 type;
    u8 pad7;
    u8 pad8[0x18];
    s32 once;
    u8 pad24[0xAC];
    s32 count;
} Object_0026FE70;

/* Effect script Hand_Fail, step `ID`: its camera, fades and effect module; it destroys units. */
/* Runs the animation of a failed hand combination: the card is lost. */
s32 Ta_Eff_Hand_Fail(void *src, void *obj, s32 mode) {
    extern void Ta_DelUnit2(u32, s32);
    s32 words[4];
    s32 *message = words;
    Input_0026FE70 *input = src;
    Object_0026FE70 *target = obj;
    s32 count;
    u32 color;

    message[0] = 0x3E7;
    message[1] = 0;
    message[2] = 0;
    message[3] = 0;

    if (mode >= 0) {
        InitEffectTemp(obj);
        TaEffect_LoadModule(obj, 0x21A);
        message[0] = 0x25A;
        message[1] = input->value1;
        message[2] = input->value2;
        message[3] = 0;
        TaLib_c615((u8 *)obj + 0x110, message, 0);
        goto common_return;
    }

    switch (target->state) {
    case 0:
        goto no_state;
    default:
        goto active;
    }

no_state:
    if (TaEffect_IsLoadModule(obj) == 1) {
        message[0] = 0x21A;
        message[1] = input->value1;
        message[2] = input->value2;
        message[3] = 0;
        *(u8 *)((u8 *)obj + 6) = Ta_Do_Effect(message, obj);
        target->once = 0;
        target->state = target->state + 1;
    }

    message[0] = 0x25A;
    message[1] = input->value1;
    message[2] = input->value2;
    message[3] = 0;
    TaLib_c615((u8 *)obj + 0x110, message, -1);
    return 1;

active:
    if (SzEffect_IsUse(target->type) != 0) {
        count = target->count;
        target->count = count + 1;
        switch (count) {
        case 1:
            SzSound_PlaySE(1, 0x4C);
            break;
        case 0xF:
            SzSound_PlaySE(1, 0x4A);
            break;
        }
        return 1;
    } else {
        color = input->value1;
        Ta_DelUnit2(color >> 8, color & 0xFF);
        SzDuel_CloseMsgPopup();
        return 0;
    }

common_return:
    return 1;
}

typedef struct {
    u32 unused;
    u32 value1;
    u32 value2;
    s32 flags;
} Input_00270030;

typedef struct {
    u8 pad0[4];
    u16 state;
    u8 type;
    u8 pad7;
    u8 pad8[0x18];
    s32 once;
    u8 pad24[0xAC];
    s32 count;
} Object_00270030;


/* Effect script Hand_Fusion, step `ID`: its camera, fades and effect module; it destroys units. */
/* Runs the hand-fusion animation. */
s32 Ta_Eff_Hand_Fusion(void *src, void *obj, s32 mode) {
    s32 words[4];
    s32 *message = words;
    Input_00270030 *input = src;
    Object_00270030 *target = obj;
    s32 count;
    u32 color;

    message[0] = 0x3E7;
    message[1] = 0;
    message[2] = 0;
    message[3] = 0;

    if (mode >= 0) {
        InitEffectTemp(obj);
        TaEffect_LoadModule(obj, 0x258);
        message[0] = 0x25A;
        message[1] = input->value1;
        message[2] = input->value2;
        message[3] = 0;
        TaLib_c615((u8 *)obj + 0x110, message, 0);
        goto common_return;
    }

    switch (target->state) {
    case 0:
        goto no_state;
    default:
        goto active;
    }

no_state:
    if (TaEffect_IsLoadModule(obj) == 1) {
        message[0] = 0x258;
        message[1] = input->value1;
        message[2] = input->value2;
        message[3] = 0;
        *(u8 *)((u8 *)obj + 6) = Ta_Do_Effect(message, obj);
        target->once = 0;
        target->state = target->state + 1;
    }

    message[0] = 0x25A;
    message[1] = input->value1;
    message[2] = input->value2;
    message[3] = 0;
    TaLib_c615((u8 *)obj + 0x110, message, -1);
    return 1;

active:
    if (SzEffect_IsUse(target->type) != 0) {
        count = target->count;
        target->count = count + 1;
        switch (count) {
        case 1:
            SzSound_PlaySE(1, 0x4C);
            break;
        case 0x12:
            SzSound_PlaySE(1, 0x3A);
            break;
        case 0x50:
            SzSound_PlaySE(1, 0x3B);
            break;
        }

        if (SzEffect_GetStatus(target->type) == 2 && target->once == 0) {
            target->once = 1;
            color = input->value1;
            Ta_DelUnit2(color >> 8, color & 0xFF);
            color = input->value2;
            Ta_DelUnit2(color >> 8, color & 0xFF);
            return (input->flags << 16) | 2;
        }
        return 1;
    } else {
        SzDuel_CloseMsgPopup();
        return 0;
    }

common_return:
    return 1;
}

typedef struct Source_00270260 {
    s32 unused;
    u32 position;
    s32 entries;
    s32 card;
} Source_00270260;

typedef struct State_00270260 {
    u16 flag;
    u16 position;
    u16 stage;
    u8 commands[0x16];
    u32 results[0x2D];
    s32 timer;
    u8 count;
    u8 padD5[0x3B];
    u8 queue[1];
} State_00270260;

typedef struct Event_00270260 {
    s32 id;
    s32 from;
    s32 to;
    s32 mode;
} Event_00270260;


/* The kind of the unit on board square `position`. */
static inline s32 mode_00270260(u32 position) {
    if ((SzDuel_GetUnitKind(position >> 24, (position >> 16) & 0xFF) >> 5) == 0) {
        return 0;
    } else {
        return 3;
    }
}

/* Effect script Hand_Enc, step `ID`: its camera, fades and effect module; it destroys units, turns cards face up. */
/* Runs the hand-equip animation: the unit's power changes. */
s32 Ta_Eff_Hand_Enc(void *src, void *state, s32 mode) {
    extern s32 SzDuel_GetUnitOpenRate();
    extern s32 SzDuel_GetUnitCardNo();
    extern s32 SzDuel_GetUnitCtlRateC();
    extern s32 SzDuel_GetUnitCtlGoalC();
    Event_00270260 event;
    Event_00270260 *message = &event;
    State_00270260 *temp_s1;
    Source_00270260 *temp_s2;
    s32 temp_s3;
    s32 temp_a1;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_s3_2;
    s32 temp_v0;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 temp_v1_4;
    s32 var_v0;
    u16 temp_v0_5;
    u16 temp_v0_6;
    u16 temp_v1;
    u32 temp_a1_2;
    u32 temp_a1_3;
    u32 temp_v0_10;
    u32 temp_v0_2;
    u32 temp_v0_7;
    u32 side;
    u32 temp_v0_8;
    u32 temp_v0_9;
    u32 temp_v1_5;
    s32 var_s3;

    event.id = 0x3E7;
    event.from = 0;
    event.to = 0;
    temp_s2 = src;
    event.mode = 0;
    temp_s1 = state;
    temp_s3 = mode;
    if ((Ta_GetEncEffect(((Source_00270260 *)src)->card) & 0xFFFF) == 0x219) {
        return Ta_Eff_Hand_Force(temp_s2, temp_s1, temp_s3);
    }
    if (temp_s3 >= 0) {
        InitEffectTemp(temp_s1);
        temp_v0 = Ta_GetEncEffect(temp_s2->card) & 0xFFFF;
        switch (temp_v0) {
        case 0x218:
            TaEffect_LoadModule(temp_s1, 0x218);
            break;
        case 0x21C:
            TaEffect_LoadModule(temp_s1, 0x21C);
            break;
        case 0x21D:
            TaEffect_LoadModule(temp_s1, 0x21D);
            break;
        case 0x21E:
            TaEffect_LoadModule(temp_s1, 0x21E);
            break;
        default:
            TaEffect_LoadModule(temp_s1, 0x218);
            break;
        }
        temp_v0_2 = temp_s2->position;
        if ((((SzDuel_GetUnitKind((s32) (temp_v0_2 >> 0x18), (temp_v0_2 >> 0x10) & 0xFF) >> 5) == 0) ? 0 : 3) == 0) {
            var_s3 = (u32) temp_s2->position >> 0x10;
        } else {
            var_s3 = (u32) (u16) temp_s2->position;
        }
        if ((temp_v0_3 = Ta_IsActiveTrapB(temp_s2->entries, 0x2B)) < 0 ||
            (TaEnc_IsActReflexEnc((s32)(u16)temp_s2->card) == 0 &&
             Ta_IsLDAbl(0xB, SzDuel_GetTurnOwner()) == 1 &&
             (temp_s3_2 = SzDuel_GetUnitKind((s32)var_s3 >> 8, var_s3 & 0xFF) & 0x1F) ==
             (SzDuel_GetUnitKind(SzDuel_GetTurnOwner(), 0) & 0x1F))) {
            temp_s1->stage = 2;
            temp_s1->flag = 0;
        } else {
            SzDuel_SetWindowDraw(0);
            TaEffect_LoadModule(temp_s1, 0x25A);
            temp_v0_4 = Ta_IsActiveTrapB(temp_s2->entries, 0x2E);
            if (temp_v0_4 >= 0) {
                temp_s1->stage = 0U;
                temp_s1->flag = 0U;
                temp_s1->position = (u16) temp_v0_4;
            } else {
                temp_s1->stage = 0U;
                temp_s1->flag = 1U;
                temp_s1->position = (u16) temp_v0_3;
            }
            temp_v0_5 = temp_s1->position;
            TaUtil_DoOpen((s32) temp_v0_5 >> 8, temp_v0_5 & 0xFF, 1);
        }
        message->id = 0x25A;
        message->from = (u32) ((u32) temp_s2->position >> 0x10);
        message->to = (s32) (u16) temp_s2->position;
        message->mode = 0;
        TaLib_c615(temp_s1->queue, message, 0);
        return 1;
    }
    if (TaEffect_IsLoadModule(temp_s1) != 1) {
        if ((s32) temp_s1->position > 0) {
            SzDuel_SetWindowDraw(0);
        }
        message->id = 0x25A;
        message->from = (u32) ((u32) temp_s2->position >> 0x10);
        message->to = (s32) (u16) temp_s2->position;
        message->mode = 0;
        TaLib_c615(temp_s1->queue, message, -1);
        return 1;
    }
    temp_v1 = temp_s1->stage;
    switch (temp_v1) {
    case 0:
        SzDuel_SetWindowDraw(0);
        message->id = 0x25A;
        message->from = (u32) ((u32) temp_s2->position >> 0x10);
        message->to = (s32) (u16) temp_s2->position;
        message->mode = 0;
        if (SzDuel_GetUnitOpenRate((s32)temp_s1->position >> 8, temp_s1->position & 0xFF) == 0xFF) {
            if (temp_s1->flag == 0) {
                SzDuel_OpenMsgPopup(0, -0x78, 0x50, SzDuel_GetMsgName(0x339));
            } else {
                SzDuel_OpenMsgPopup(0, -0x78, 0x50, 0x103);
            }
            SzDuel_SetWindowBusy(1);
            TaView_ReqFocusCamera(0, (s32) temp_s1->position, 0xB4, 0xB4);
            message->id = 0x25A;
            message->from = 0U;
            message->to = (s32) temp_s1->position;
            message->mode = 0;
            temp_s1->commands[temp_s1->count] = Ta_Do_Effect(message, temp_s1);
            temp_s1->count = (u8) (temp_s1->count + 1);
            temp_s1->stage = (u16) (temp_s1->stage + 1);
        } else {
            TaLib_c615(temp_s1->queue, message, -1);
        }
        break;
    case 1:
        if (SzEffect_IsUse((s32) ((u8 *)(temp_s1->count + (u32)temp_s1))[5]) != 0) {
            if ((s32) temp_s1->position > 0) {
                SzDuel_SetWindowDraw(0);
            }
            return 1;
        }
        temp_v0_6 = temp_s1->position;
        SzDuel_SetUnitStatus((s32) temp_v0_6 >> 8, temp_v0_6 & 0xFF, 0, 1);
        SzDuel_CloseMsgPopup();
        message->id = 5;
        message->from = (u32) ((u32) temp_s2->position >> 0x10);
        message->to = (s32) (u16) temp_s2->position;
        message->mode = 0;
        TaLib_c615(temp_s1->queue, message, -1);
        SzDuel_SetWindowBusy(0);
        TaView_RestoreOriginalView(temp_s1, 0);
        temp_s1->stage = (u16) (temp_s1->stage + 1);
        break;
    case 2:
        message->id = 5;
        message->from = (u32) ((u32) temp_s2->position >> 0x10);
        message->to = (s32) (u16) temp_s2->position;
        message->mode = 0;
        TaLib_c615(temp_s1->queue, message, -1);
        temp_v1_2 = Ta_GetEncEffect(temp_s2->card) & 0xFFFF;
        switch (temp_v1_2) {
        case 0x218:
            if (temp_s1->flag != 0) {
                SzDuel_OpenMsgPopup(0, 0, -0xA0, SzDuel_GetMsgName(SzDuel_GetUnitCardNo((s32)temp_s1->position >> 8, temp_s1->position & 0xFF)));
            } else {
                SzDuel_OpenMsgPopup(0, 0, -0xA0, 0x106);
            }
            message->id = 0x218;
            message->from = (u32) ((u32) temp_s2->position >> 0x10);
            message->to = (s32) (u16) temp_s2->position;
            message->mode = 0;
            break;
        case 0x21C:
            message->id = 0x21C;
            message->from = (u32) ((u32) temp_s2->position >> 0x10);
            message->to = (s32) (u16) temp_s2->position;
            message->mode = 0;
            break;
        case 0x21D:
            message->id = 0x21D;
            message->from = (u32) ((u32) temp_s2->position >> 0x10);
            message->to = (s32) (u16) temp_s2->position;
            message->mode = 0;
            break;
        case 0x21E:
            message->id = 0x21E;
            message->from = (u32) ((u32) temp_s2->position >> 0x10);
            message->to = (s32) (u16) temp_s2->position;
            message->mode = 0;
            break;
        default:
            message->id = 0x218;
            message->from = (u32) ((u32) temp_s2->position >> 0x10);
            message->to = (s32) (u16) temp_s2->position;
            message->mode = 0;
            break;
        }
        temp_v0_7 = temp_s2->position;
        if ((SzDuel_GetUnitKind(temp_v0_7 >> 24, (temp_v0_7 >> 16) & 0xFF) >> 5) == 0) {
            side = 0;
        } else {
            side = 3;
        }
        message->mode = side;
        temp_s1->commands[temp_s1->count] = Ta_Do_Effect(message, temp_s1);
        temp_s1->results[temp_s1->count + 1] = 0;
        temp_s1->count = (u8) (temp_s1->count + 1);
        temp_s1->stage = (u16) (temp_s1->stage + 1);
        break;
    case 3:
        if (SzEffect_IsUse((s32) ((u8 *)(temp_s1->count + (u32)temp_s1))[5]) != 0) {
            temp_a1 = temp_s1->timer;
            temp_s1->timer = (s32) (temp_a1 + 1);
            switch (temp_a1) {
            case 1:
                SzSound_PlaySE(1, 0x4C);
                break;
            case 15:
                temp_v1_3 = Ta_GetEncEffect(temp_s2->card) & 0xFFFF;
                switch (temp_v1_3) {
                case 0x218:
                    SzSound_PlaySE(1, 0x3B);
                    break;
                case 0x21C:
                    SzSound_PlaySE(1, 0x4B);
                    break;
                case 0x21D:
                    SzSound_PlaySE(1, 0x4E);
                    break;
                case 0x21E:
                    SzSound_PlaySE(1, 0x4F);
                    break;
                }
                break;
            case 16:
                temp_v1_4 = Ta_GetEncEffect(temp_s2->card) & 0xFFFF;
                switch (temp_v1_4) {
                case 0x21D:
                case 0x21E:
                    SzSound_PlaySE(1, 0x3B);
                    break;
                }
                break;
            }
            if (SzEffect_GetStatus((s32) ((u8 *)(temp_s1->count + (u32)temp_s1))[5]) == 2) {
                if (((u8 *)(((u32)temp_s1->count << 2) + (u32)temp_s1))[0x1C] == 0) {
                    temp_v0_8 = temp_s2->position;
                    if ((SzDuel_GetUnitKind((s32) (temp_v0_8 >> 0x18), (temp_v0_8 >> 0x10) & 0xFF) >> 5) == 0) {
                        temp_a1_2 = temp_s2->position;
                        Enchant(temp_a1_2 >> 0x18, (temp_a1_2 >> 0x10) & 0xFF, (temp_s1->flag << 0x10) | temp_s2->card, 0);
                    } else {
                        temp_a1_3 = temp_s2->position;
                        Enchant((u32) (temp_a1_3 & 0xFFFF) >> 8, temp_a1_3 & 0xFF, (temp_s1->flag << 0x10) | temp_s2->card, 0);
                    }
                    temp_s1->results[temp_s1->count] = 0xFFFF;
                }
            }
            return 1;
        }
        SzDuel_CloseMsgPopup();
        temp_v0_9 = temp_s2->position;
        if ((SzDuel_GetUnitKind((s32) (temp_v0_9 >> 0x18), (temp_v0_9 >> 0x10) & 0xFF) >> 5) == 0) {
            temp_v1_5 = temp_s2->position;
            temp_s0 = SzDuel_GetUnitCtlRateC((temp_v1_5 & 0xFFFF) >> 8, temp_v1_5 & 0xFF);
            if (temp_s0 != SzDuel_GetUnitCtlGoalC((temp_s2->position & 0xFFFF) >> 8, temp_s2->position & 0xFF)) {
                return 1;
            }
            temp_v1_5 = temp_s2->position;
            Ta_DelUnit2((u32) (temp_v1_5 & 0xFFFF) >> 8, temp_v1_5 & 0xFF);
        } else {
            temp_v0_10 = temp_s2->position;
            temp_s0_2 = SzDuel_GetUnitCtlRateC(temp_v0_10 >> 0x18, (temp_v0_10 >> 0x10) & 0xFF);
            if (temp_s0_2 != SzDuel_GetUnitCtlGoalC(temp_s2->position >> 0x18, (temp_s2->position >> 0x10) & 0xFF)) {
                return 1;
            }
            temp_v0_10 = temp_s2->position;
            Ta_DelUnit2(temp_v0_10 >> 0x18, (temp_v0_10 >> 0x10) & 0xFF);
        }
        if (SzDuel_GetWindowDisp() != 0) {
            SzDuel_SetWindowDraw(1);
        }
        SzDuel_CloseMsgPopup();
        return 0;
    default:
        return 1;
    }
    return 1;
}

struct jp_8b329 {
    int eNO;
    unsigned int dwFrom;
    unsigned int dwTo;
    unsigned int dwPar;
};
struct jp_8b5bb {
    int fLoad : 1;
    unsigned char bModNum : 5;
    unsigned short wModule[24];
    unsigned char bModCond[24];
};
struct jp_8b3ce {
    unsigned short wCount_1;
    unsigned short wCount_2;
    unsigned short wLvl;
    unsigned char eID[24];
    int ePos[24];
    struct jp_8b5bb eMod;
    unsigned int fObj;
    unsigned int fObj2;
    unsigned char oNum;
    unsigned char unknown_d5[0x2b];
    unsigned char bCamLvl;
    unsigned short wCamTime;
    unsigned char unknown_104[0xc];
    int nTasakiEfc[0x10c];
};
extern int func_00255AC0_270c30(struct jp_8b3ce *q, int id);
extern int func_0024F430_270c30(int a, int b);
extern int func_001E1E10_b(int a, int b);
extern int func_001E1030_b(int a, int b);
extern void func_00260AF0_b(unsigned char who, int packed, int add, int value);
extern void func_002610D0_b(unsigned char who, int packed, int add, int value);
extern void func_00260A70_270c30(struct jp_8b3ce *Temp, unsigned char b);
extern int func_00261570_b(int a, int b, unsigned char c, unsigned char d);

/* Effect script Hand_Force, step `ID`: its camera, fades and effect module; it changes life points, turns cards
   face up. */
/* Runs the power-change animation of a hand equip. */
int Ta_Eff_Hand_Force(void *eInfo_v, void *Temp_v, int ID)
{
    struct jp_8b329 * eInfo = eInfo_v;
    struct jp_8b3ce * Temp = Temp_v;
    int stored;
    struct jp_8b329 eCall;
    struct jp_8b329 *pCall = &eCall;
    int Unit2;
    int Unit;

    eCall.eNO = 999;
    eCall.dwFrom = 0;
    eCall.dwTo = 0;
    eCall.dwPar = 0;
    if (ID >= 0) {
        InitEffectTemp(Temp);
        Temp->wCount_1 = Ta_GetForceEffection(eInfo->dwTo, Ta_GetEnchantOfs());
        if ((SzDuel_GetUnitKind(eInfo->dwFrom >> 24, (eInfo->dwFrom >> 16) & 0xff) >> 5 == 0 ? 0 : 3) == 0) {
            Unit = eInfo->dwFrom >> 16;
        } else {
            Unit = eInfo->dwFrom & 0xffff;
        }
        if (Ta_IsLDAbl(11, SzDuel_GetTurnOwner()) == 1 &&
            (SzDuel_GetUnitKind(Unit >> 8, Unit & 0xff) & 0x1f) == (SzDuel_GetUnitKind(SzDuel_GetTurnOwner(), 0) & 0x1f)) {
            func_00255AC0_270c30(Temp, 537);
            Temp->wLvl = 2;
            Temp->wCount_2 = 0;
        } else if ((Unit = Ta_IsActiveTrapB(eInfo->dwTo, 41)) < 0) {
            if ((Unit = Ta_IsActiveTrapB(eInfo->dwTo, 43)) < 0) {
                func_00255AC0_270c30(Temp, 537);
                Temp->wLvl = 2;
                Temp->wCount_2 = 0;
            } else if ((Unit2 = Ta_IsActiveTrapB(eInfo->dwTo, 46)) >= 0) {
                func_00255AC0_270c30(Temp, 602);
                func_00255AC0_270c30(Temp, 537);
                SzEffect_SetBusyFlag2(Unit2, 0);
                TaUtil_DoOpen(Unit2 >> 8, Unit2 & 0xff, 1);
                Temp->fObj = Unit2;
                Temp->wLvl = 0;
                Temp->wCount_2 = 0;
            } else {
                func_00255AC0_270c30(Temp, 602);
                func_00255AC0_270c30(Temp, 537);
                SzEffect_SetBusyFlag2(Unit, 0);
                TaUtil_DoOpen(Unit >> 8, Unit & 0xff, 1);
                Temp->fObj = Unit;
                Temp->wLvl = 0;
                Temp->wCount_2 = 1;
            }
        } else if ((Unit2 = Ta_IsActiveTrapB(eInfo->dwTo, 46)) >= 0) {
            func_00255AC0_270c30(Temp, 602);
            func_00255AC0_270c30(Temp, 537);
            SzEffect_SetBusyFlag2(Unit2, 0);
            TaUtil_DoOpen(Unit2 >> 8, Unit2 & 0xff, 1);
            Temp->fObj = Unit2;
            Temp->wLvl = 0;
            Temp->wCount_2 = 0;
        } else {
            SzDuel_SetWindowDraw(0);
            func_00255AC0_270c30(Temp, 602);
            func_00255AC0_270c30(Temp, 547);
            SzEffect_SetBusyFlag2(Unit, 0);
            TaUtil_DoOpen(Unit >> 8, Unit & 0xff, 1);
            Temp->fObj = Unit;
            Temp->fObj2 = 1;
            Temp->wLvl = 0;
            Temp->wCount_2 = 0;
        }
        pCall->eNO = 602;
        pCall->dwFrom = eInfo->dwFrom >> 16;
        pCall->dwTo = eInfo->dwFrom & 0xffff;
        pCall->dwPar = 0;
        TaLib_c615(&Temp->nTasakiEfc, pCall, 0);
        return 1;
    }
    if (Temp->eMod.fLoad == 0) {
        pCall->eNO = 602;
        pCall->dwFrom = eInfo->dwFrom >> 16;
        pCall->dwTo = eInfo->dwFrom & 0xffff;
        pCall->dwPar = 0;
        TaLib_c615(&Temp->nTasakiEfc, pCall, -1);
        if (TaEffect_IsLoadModule(Temp) == 1) {
            Temp->eMod.fLoad = -1;
        }
        



        goto one;
    } else {
        switch (Temp->wLvl) {
        case 0:
            SzDuel_SetWindowDraw(0);
            pCall->eNO = 602;
            pCall->dwFrom = eInfo->dwFrom >> 16;
            pCall->dwTo = eInfo->dwFrom & 0xffff;
            pCall->dwPar = 0;
            if (func_001E1E10_b(Temp->fObj >> 8, Temp->fObj & 0xff) == 255) {
                if (Temp->wCount_2 == 0 && Temp->fObj2 == 0) {
                    SzDuel_OpenMsgPopup(0, -120, 80, SzDuel_GetMsgName(825));
                } else {
                    SzDuel_OpenMsgPopup(0, -120, 80, 259);
                }
                SzDuel_SetWindowBusy(1);
                func_00260AF0_b(0, Temp->fObj, 180, 180);
                pCall->eNO = 602;
                pCall->dwFrom = 0;
                pCall->dwTo = Temp->fObj;
                pCall->dwPar = 0;
                

                if ((stored = (Temp->eID[Temp->oNum] = Ta_Do_Effect(pCall, Temp))) >= 0) {
                    Temp->ePos[Temp->oNum] = 0;
                    Temp->oNum++;
                    Temp->wLvl++;
                } else {
                    SzDuel_CloseMsgPopup();
                    return 0;
                }
            } else {
                TaLib_c615(&Temp->nTasakiEfc, pCall, -1);
            }
            break;
        case 1:
            SzDuel_SetWindowDraw(0);
            if (SzEffect_IsUse(Temp->eID[Temp->oNum - 1]) != 0) {
                return 1;
            }
            SzDuel_SetUnitStatus(Temp->fObj >> 8, Temp->fObj & 0xff, 0, 1);
            if (Temp->fObj2 != 0) {
                SzDuel_SetWindowBusy(1);
                func_002610D0_b(0, (eInfo->dwTo == 0 ? 1 : 0) << 8, 180, 180);
                Temp->wLvl = 16;
            } else {
                SzDuel_SetWindowDraw(1);
                pCall->eNO = 5;
                pCall->dwFrom = eInfo->dwFrom >> 16;
                pCall->dwTo = eInfo->dwFrom & 0xffff;
                pCall->dwPar = 0;
                TaLib_c615(&Temp->nTasakiEfc, pCall, -1);
                SzDuel_SetWindowBusy(0);
                func_00260A70_270c30(Temp, 0);
                Temp->wLvl++;
            }
            break;
        case 2:
            pCall->eNO = 5;
            pCall->dwFrom = eInfo->dwFrom >> 16;
            pCall->dwTo = eInfo->dwFrom & 0xffff;
            pCall->dwPar = 0;
            TaLib_c615(&Temp->nTasakiEfc, pCall, -1);
            if (Temp->wCount_2 == 1) {
                SzDuel_OpenMsgPopup(0, 0, -160, SzDuel_GetMsgName(func_001E1030_b(Temp->fObj >> 8, Temp->fObj & 0xff)));
            } else {
                SzDuel_OpenMsgPopup(0, 0, -160, 268);
            }
            pCall->eNO = 537;
            pCall->dwFrom = eInfo->dwFrom >> 16;
            pCall->dwTo = eInfo->dwFrom & 0xffff;
            pCall->dwPar = Temp->wCount_1 << 16 | (Temp->wCount_2 << 8 | (SzDuel_GetUnitKind(eInfo->dwFrom >> 24, (eInfo->dwFrom >> 16) & 0xff) >> 5 ? 3 : 0));
            if ((stored = (Temp->eID[Temp->oNum] = Ta_Do_Effect(pCall, Temp))) >= 0) {
                Temp->ePos[Temp->oNum] = 0;
                Temp->oNum++;
                Temp->wLvl++;
            } else {
                SzDuel_CloseMsgPopup();
                return 0;
            }
            break;
        case 3:
            if (SzEffect_IsUse(Temp->eID[Temp->oNum - 1]) != 0) {
                switch (Temp->fObj2++) {
                case 1:
                    SzSound_PlaySE(1, 76);
                    break;
                case 15:
                    SzSound_PlaySE(1, 77);
                    break;
                case 16:
                    SzSound_PlaySE(1, 59);
                    break;
                }
                if (SzEffect_GetStatus(Temp->eID[Temp->oNum - 1]) == 2) {
                    if ((unsigned char)Temp->ePos[Temp->oNum - 1] == 0) {
                        if (SzDuel_GetUnitKind(eInfo->dwFrom >> 24, (eInfo->dwFrom >> 16) & 0xff) >> 5 == 0) {
                            Enchant(eInfo->dwFrom >> 24, (eInfo->dwFrom >> 16) & 0xff, Temp->wCount_2 << 16 | eInfo->dwPar, eInfo->dwTo & 0xff);
                            func_0024F430_270c30((eInfo->dwFrom & 0xffff) >> 8, eInfo->dwFrom & 0xff);
                        } else {
                            Enchant((eInfo->dwFrom & 0xffff) >> 8, eInfo->dwFrom & 0xff, Temp->wCount_2 << 16 | eInfo->dwPar, eInfo->dwTo & 0xff);
                            func_0024F430_270c30(eInfo->dwFrom >> 24, (eInfo->dwFrom >> 16) & 0xff);
                        }
                        Temp->ePos[Temp->oNum - 1] = 0xffff;
                    }
                }
                return 1;
            }
            SzDuel_CloseMsgPopup();
            return 0;
        case 16:
            SzDuel_SetWindowDraw(0);
            SzDuel_OpenMsgPopup(0, -120, 80, SzDuel_GetMsgName(814));
            pCall->eNO = 547;
            pCall->dwFrom = (eInfo->dwTo == 0 ? 1 : 0) << 8;
            pCall->dwTo = eInfo->dwTo << 8;
            pCall->dwPar = Temp->wCount_1;
            if ((stored = (Temp->eID[Temp->oNum] = Ta_Do_Effect(pCall, Temp))) >= 0) {
                Temp->oNum++;
                Temp->wLvl++;
            } else {
                SzDuel_CloseMsgPopup();
                return 0;
            }
            break;
        case 17:
            SzDuel_SetWindowDraw(0);
            if (SzEffect_IsUse(Temp->eID[Temp->oNum - 1]) != 0) {
                if (Temp->wCamTime++ == 6) {
                    func_00261570_b(30, eInfo->dwTo << 8, 100, 180);
                }
                break;
            }
            if (SzDuel_GetUnitKind(eInfo->dwFrom >> 24, (eInfo->dwFrom >> 16) & 0xff) >> 5 == 0) {
                func_0024F430_270c30((eInfo->dwFrom & 0xffff) >> 8, eInfo->dwFrom & 0xff);
            } else {
                func_0024F430_270c30(eInfo->dwFrom >> 24, (eInfo->dwFrom >> 16) & 0xff);
            }
            SzDuel_CalcLP(eInfo->dwTo, 1, Temp->wCount_1);
            SzDuel_CloseMsgPopup();
            SzDuel_SetWindowBusy(0);
            func_00260A70_270c30(Temp, 0);
            if (SzDuel_GetWindowDisp() != 0) {
                SzDuel_SetWindowDraw(1);
            }
            return 0;
        }
    one:
        return 1;
    }
}

typedef struct State_00271630 {
    u8 pad[4];
    u16 count;
    u8 handle;
} State_00271630;


/* Effect script Hand_Dest, step `ID`: its camera, fades and effect module; it destroys units, curses units, binds
   units with a spell. */
/* Runs the animation of a hand combination destroying a unit. */
s32 Ta_Eff_Hand_Dest(void *eInfo, void *Temp, s32 ID) {
    s32 values[4];
    State_00271630 *state = Temp;
    s32 *packet = values;
    u32 value;

    values[0] = 0x3E7;
    values[1] = 0;
    values[2] = 0;
    values[3] = 0;

    if (ID >= 0) {
        InitEffectTemp(state);
        TaEffect_LoadModule(state, 0x25B);
        return 1;
    }

    switch (state->count) {
    case 0:
        if (TaEffect_IsLoadModule(state) == 1) {
            packet[0] = 0x25B;
            packet[1] = 0;
            packet[2] = *(u32 *)((u8 *)eInfo + 8);
            packet[3] = 0;
            state->handle = Ta_Do_Effect(packet, state);
            state->count++;
        }
        break;
    default:
        if (SzEffect_IsUse(state->handle) != 0) {
            return 1;
        }
        value = *(u32 *)((u8 *)eInfo + 8);
        Ta_DelUnit2(value >> 8, value & 0xFF);
        SzDuel_CloseMsgPopup();
        return 0;
    }
    return 1;
}

/* Whether side `nSide`'s leader has ability `abID`. */
s32 Ta_IsLDAbl(s32 abID, s32 nSide) {
    if (Ta_SearchUncTypeNaturalEffectUserNumWithSide(0x58, (nSide == 0) ? 1 : 0) > 0) {
        return 0;
    }
    return SzDuel_GetUnitLeaderAbility(nSide, 0, abID, 0);
}

/* The field type a leader of race `Race` changes squares to. */
s32 Ta_GetLDChgLand(s32 Race) {
    s32 ret;

    switch (Race) {
    case 1:
    case 7:
        ret = 5;
        break;
    case 9:
        ret = 0;
        break;
    case 10:
        ret = 1;
        break;
    case 16:
        ret = 4;
        break;
    case 20:
        ret = 9;
        break;
    default:
        ret = 7;
        break;
    }

    return ret;
}

/* The summon-level bonus side `nSide`'s leader gives (by its level). */
s32 Ta_GetLDLvRev(s32 nSide) {
    extern s32 SzDuel_GetUnitLevel(s32, s32, s32);

    if (Ta_IsLDAbl(8, nSide) != 0) {
        switch (SzDuel_GetUnitConstKind(nSide, 0) & 0x1F) {
        case 0:
        case 6:
        case 12:
        case 14:
            return SzDuel_GetUnitLevel(nSide, 0, 0) > 6 ? 2 : 1;
        case 4:
        case 13:
            if (SzDuel_GetUnitLevel(nSide, 0, 0) > 5) {
                return 2;
            }
            return 1;
        case 20:
            return 1;
        default:
            return 0;
        }
    }
    return 0;
}

/* Whether square (nX, nZ) is within range `R` of square (mX, mZ). */
s32 Ta_IsSquareRange(s32 nX, s32 nZ, s32 mX, s32 mZ, s32 R) {
    s32 x;
    s32 half;
    s32 xEnd;
    s32 yStart;
    s32 yEnd;
    s32 y;

    half = R >> 1;
    x = GetCap(0, nX - half);
    if (nX + half >= 7) {
        xEnd = 6;
    } else {
        xEnd = nX + half;
    }
    yStart = GetCap(0, nZ - half);
    if (nZ + half >= 7) {
        yEnd = 6;
    } else {
        yEnd = nZ + half;
    }
    for (; x <= xEnd; x++) {
        for (y = yStart; y <= yEnd; y++) {
            if (x == mX && y == mZ) {
                return 1;
            }
        }
    }
    return 0;
}

/* Whether square (nX, nZ) is within side `LDSide`'s leader's range. */
s32 Ta_IsLDRange(s32 LDSide, s32 nX, s32 nZ) {
    s32 temp_s0;

    temp_s0 = SzDuel_GetUnitLoc(LDSide, 0);
    if (Ta_IsLDAbl(9, LDSide) != 0) {
        return (Ta_IsSquareRange(temp_s0 & 0xFF, temp_s0 >> 8, nX, nZ, 5) != 0) ? 1 : 0;
    } else {
        return (Ta_IsSquareRange(temp_s0 & 0xFF, temp_s0 >> 8, nX, nZ, 3) != 0) ? 1 : 0;
    }
}

/* The power change a unit (record `vInfo`) on (nX, nZ) gets from leaders' abilities. */
s32 Ta_GetLDParamOfs2(void *vInfo, s32 nX, s32 nZ) {
    extern s32 SzDuel_GetUnitLevel();
    s32 score;
    s32 kind;
    s32 player;
    s32 other;

    score = 0;
    if (vInfo == NULL) {
        return 0;
    }
    player = Ta_IsUnitControl2(vInfo);
    kind = ((u8 *)vInfo)[0x3E] & 0x1F;
    other = player == 0 ? 1 : 0;
    if (Ta_IsLDRangeAvilityFromLoc((nZ << 8) | nX, player, kind, 10)) {
        score += SzDuel_GetUnitLevel(player, 0, 0) * 100 >= 500 ? 500 : SzDuel_GetUnitLevel(player, 0, 0) * 100;
    }
    if (Ta_IsLDRange(other, nX, nZ)) {
        if (Ta_IsLDAbl(14, other) && Ta_IsLD_PDownObj(other, kind)) {
            score -= SzDuel_GetUnitLevel(other, 0, 0) * 100 >= 500 ? 500 : SzDuel_GetUnitLevel(other, 0, 0) * 100;
        }
    }
    return score;
}

/* Whether side `nSide`'s leader weakens units of race `bRace`. */
s32 Ta_IsLD_PDownObj(s32 nSide, s32 bRace) {
    s32 result;

    switch (SzDuel_GetUnitConstKind(nSide, 0) & 0x1F) {
    case 1:
        if (bRace == 7) {
            result = 1;
        } else {
            result = 0;
        }
        return result;
    case 2:
        if (bRace == 3) {
            result = 1;
        } else {
            result = 0;
        }
        return result;
    case 3:
        return ((u32)bRace < 2) ? 1 : 0;
    case 5:
        if (bRace == 12) {
            result = 1;
        } else {
            result = 0;
        }
        return result;
    case 6:
        if (bRace == 9 || bRace == 12) {
            return 1;
        }
        return 0;
    case 7:
        if (bRace == 1) {
            result = 1;
        } else {
            result = 0;
        }
        return result;
    case 9:
        if (bRace == 13) {
            result = 1;
        } else {
            result = 0;
        }
        return result;
    case 11:
        return ((u32)(bRace - 5) < 2) ? 1 : 0;
    case 12:
        if (bRace == 15) {
            result = 1;
        } else {
            result = 0;
        }
        return result;
    case 15:
        if (bRace == 2 || bRace == 14) {
            return 1;
        }
        return 0;
    case 16:
        if (bRace == 14 || bRace == 17) {
            return 1;
        }
        return 0;
    case 17:
        if (bRace == 4) {
            result = 1;
        } else {
            result = 0;
        }
        return result;
    default:
        return 0;
    }
    return result;
}

/* Whether unit (nSide, nID) is in a leader's range with ability `sKey` for it. */
s32 Ta_IsLDRangeAvility(s32 nSide, s32 nID, s32 sKey) {
    s32 temp_s0;
    s32 temp_s1;
    s32 temp_s2;

    temp_s0 = SzDuel_GetUnitLoc(nSide, nID);
    temp_s2 = Ta_GetCurrentSide(nSide, nID);
    temp_s1 = SzDuel_GetUnitKind(nSide, nID) & 0x1F;
    if (Ta_IsLDRange(temp_s2, temp_s0 & 0xFF, temp_s0 >> 8) != 0 && Ta_IsLDAbl(sKey, temp_s2) != 0 &&
        temp_s1 == (SzDuel_GetUnitConstKind(temp_s2, 0) & 0x1F)) {
        return 1;
    }
    return 0;
}

/* Whether square `LOC` is in a leader's range with ability `sKey` for race `bRace` (`Self` picks the side). */
s32 Ta_IsLDRangeAvilityFromLoc(s32 LOC, s32 Self, s32 bRace, s32 sKey) {

    if (Ta_IsLDRange(Self, LOC & 0xFF, LOC >> 8) != 0 && Ta_IsLDAbl(sKey, Self) != 0 &&
        bRace == (SzDuel_GetUnitConstKind(Self, 0) & 0x1F)) {
        return 1;
    }
    return 0;
}

/* Whether unit (nSide, nID) on square (nX, nZ) is in a leader's range with ability `sKey`. */
s32 Ta_IsLDRangeAvilityWithLocation(s32 nSide, s32 nID, s32 nX, s32 nZ, s32 sKey) {
    s32 temp_s0;
    s32 temp_s1;

    temp_s1 = Ta_GetCurrentSide(nSide, nID);
    temp_s0 = SzDuel_GetUnitKind(nSide, nID) & 0x1F;
    if (Ta_IsLDRange(temp_s1, nX, nZ) != 0 && Ta_IsLDAbl(sKey, temp_s1) != 0 &&
        temp_s0 == (SzDuel_GetUnitConstKind(temp_s1, 0) & 0x1F)) {
        return 1;
    }
    return 0;
}

/* Whether side `nSide`'s leader curses units of race `bRace`. */
s32 Ta_IsLD_CurseObj(s32 nSide, s32 bRace) {

    switch (SzDuel_GetUnitConstKind(nSide, 0) & 0x1F) {
    case 8:
        return (bRace == 2) ? 1 : 0;
    case 11:
        return (bRace == 0x10) ? 1 : 0;
    case 17:
        return ((u32)(bRace - 5) < 2U) ? 1 : 0;
    case 19:
        return (bRace == 0) ? 1 : 0;
    }
    return 0;
}

/* Whether side `nSide`'s leader destroys units of race `bRace`. */
s32 Ta_IsLD_DestObj(s32 nSide, s32 bRace) {
    s32 result;

    switch (SzDuel_GetUnitConstKind(nSide, 0) & 0x1F) {
    case 8:
        result = (bRace == 7) ? 1 : 0;
        break;
    case 11:
        result = (bRace == 9) ? 1 : 0;
        break;
    case 17:
        if (bRace == 2 || bRace == 19) {
            result = 1;
        } else {
            result = 0;
        }
        break;
    case 18:
        result = (bRace == 10) ? 1 : 0;
        break;
    case 19:
        result = (bRace == 18) ? 1 : 0;
        break;
    default:
        result = 0;
        break;
    }
    return result;
}

/* Takes the units a leader protects or that resist all effects out of target list `eObj` (owner `sOwner`). */
u32 Ta_RemoveObjFromFlagLst(s32 eObj, s32 sOwner) {
    s32 i;
    s32 count;
    s32 result;
    s32 owner;
    s32 y;
    s32 x;
    s32 position;

    count = Ta_GetUnitNumFrom22bitFlagList(eObj);
    result = eObj;
    for (i = 0; i < count; i++) {
            position = Ta_GetUnitOwnerIDFromLstCount(eObj, i);
            x = position >> 8;
            y = position & 0xFF;
            owner = Ta_GetCurrentSide(x, y);
            if ((Ta_IsLDRangeAvility(x, y, 0xB) != 0) && (owner != sOwner)) {
                result = ConvUnitIDtoFlagList_OFF((u32) result, x, y);
            } else if ((Ta_IsResistAll(x, y) != 0) && (owner != sOwner)) {
                result = ConvUnitIDtoFlagList_OFF((u32) result, x, y);
            }
    }
    return (u32) result;
}

/* Takes leader-protected units out of target list `eObj`, showing the message and range. */
u32 Ta_RemoveObjFromFlagLst2(s32 eObj, s32 sOwner) {
    s32 i;
    s32 remaining;
    s32 card;
    s32 position;
    s32 y;
    s32 x;
    s32 count;
    s32 packed;

    count = Ta_GetUnitNumFrom22bitFlagList(eObj);
    remaining = eObj;
    for (i = 0; i < count; i++) {
            packed = Ta_GetUnitOwnerIDFromLstCount(eObj, i);
            x = packed >> 8;
            y = packed & 0xFF;
            card = Ta_GetCurrentSide(x, y);
            position = SzDuel_GetUnitLoc(card, 0);
            if (Ta_IsLDRangeAvility(x, y, 0xB) != 0 && card != sOwner) {
                SzDuel_OpenMsgPopup(0, -0x78, 0x50, 0x10E);
                Ta_SetRangeVisual(position & 0xFF, position >> 8, 0,
                             Ta_IsLDAbl(9, card), 1, 1, 0xB);
                remaining = ConvUnitIDtoFlagList_OFF((u32) remaining, x, y);
            } else if (Ta_IsResistAll(x, y) != 0 && card != sOwner) {
                SzDuel_OpenMsgPopup(0, 0, 0x50, SzDuel_GetMsgName(0x53));
                remaining = ConvUnitIDtoFlagList_OFF((u32) remaining, x, y);
            }
    }
    return (u32) remaining;
}

/* Side `LDSide`'s leader's ability range. */
s32 Ta_GetLDRange(s32 LDSide) {
    return Ta_IsLDAbl(9, LDSide) ? 5 : 3;
}

/* Runs the end of a turn: curse and spell turns count down, into `res`. */
s32 Ta_Do_EndPhase(s32 phase, s32 *res) {
    extern s32 SzDuel_GetUnitSpellRest();
    extern s32 SzDuel_GetUnitCurseRest();
    extern s32 SzDuel_GetUnitCurseFlag();
    extern s32 SzDuel_GetUnitCardNo();
    extern s32 SzDuel_SetUnitCurseRest();
    extern s32 SzDuel_SetUnitSpellRest();
    extern s32 SzDuel_GetTurnFirst();
    extern s32 SzDuel_GetTurnCount();
    s32 row;
    s32 a;
    s32 v;
    s32 pos;
    s32 col;
    s32 player;
    s32 b;
    s32 c;
    s32 vy;
    s32 other;
    s32 hp;
    s32 hi;
    s32 lo;
    s32 n;
    s32 vx;
    s32 i;
    s32 mine;
    s32 w;

    player = SzDuel_GetTurnOwner();
    switch (phase) {
    case 0:
        if (Ta_IsLDAbl(5, player)) {
            res[0] = 8;
            res[1] = 0;
            res[2] = player;
            res[3] = 50;
            return ((phase + 1) << 16) | 1;
        }
        return (phase + 1) << 16;
    case 1:
        return ((phase + 1) << 16) | Ta_IsVirusAll(res);
    case 2:
        pos = SzDuel_GetUnitLoc(player, 0);
        row = 0;
        a = 0;
        b = 0;
        c = 0;
        hi = pos >> 8;
        lo = pos & 0xFF;
        for (; row < 7; row++) {
            for (col = 0; col < 7; col++) {
                v = SzDuel_GetMapUnitID(row, col);
                if (v < 0) {
                    continue;
                }
                vx = v >> 8;
                vy = v & 0xFF;
                if (player == Ta_GetCurrentSide(vx, vy)) {
                    continue;
                }
                if (Ta_IsSquareRange(lo, hi, row, col, Ta_GetLDRange(player)) == 0) {
                    continue;
                }
                if ((SzDuel_GetUnitKind(vx, vy) >> 5) == 0) {
                    if (Ta_IsLDAbl(0x10, player)) {
                        if (Ta_IsLD_DestObj(player, SzDuel_GetUnitKind(vx, vy) & 0x1F) && vy != 0) {
                            a = ConvUnitIDtoFlagList(a, vx, vy);
                        }
                    }
                    if (Ta_IsLDAbl(0xF, player) && Ta_IsLD_CurseObj(player, SzDuel_GetUnitKind(vx, vy) & 0x1F) &&
                        vy != 0 && SzDuel_GetUnitSpellRest(vx, vy) == 0) {
                        b = ConvUnitIDtoFlagList(b, vx, vy);
                    }
                }
                if (Ta_IsLDAbl(0xD, player) && SzDuel_GetUnitStatus(vx, vy, 4) == 0 && vy != 0) {
                    c = ConvUnitIDtoFlagList(c, vx, vy);
                }
            }
        }
        if (a > 0 || b > 0 || c > 0) {
            res[0] = 0x71;
            res[1] = a | 0x80000000;
            res[2] = b;
            res[3] = c;
            return ((phase + 1) << 16) | 1;
        }
        return (phase + 1) << 16;
    case 3:
        for (i = 1; i <= 5; i++) {
            if (SzDuel_GetUnitStatus(player, i, 4) == 1) {
                SzData_CalcExp(player, SzDuel_GetUnitCardNo(player, i), 0, 4);
            } else {
                SzData_CalcExp(player, SzDuel_GetUnitCardNo(player, i), 0, 2);
            }
        }
        n = Ta_SearchUncTypeNaturalEffectUserNum(0x55);
        for (i = 1; i <= 11; i++) {
            mine = SzDuel_GetUnitLoc(player, i);
            if (Ta_SearchUncTypeNaturalEffectUserNum(0x47) <= 0) {
                if ((hp = SzDuel_GetUnitCurseRest(player, i)) > 0 && player == Ta_IsUnitControl(player, i) && SzDuel_GetUnitCurseFlag(player, i) == 0 && hp < 0xFF) {
                    if (n > 0) {
                        SzDuel_SetUnitCurseRest(player, i, GetCap(0, hp - 2));
                    } else {
                        SzDuel_SetUnitCurseRest(player, i, hp - 1);
                    }
                }
                if ((hp = SzDuel_GetUnitCurseRest((player == 0) ? 1 : 0, i)) > 0 && player == Ta_IsUnitControl((player == 0) ? 1 : 0, i) &&
                    SzDuel_GetUnitCurseFlag((player == 0) ? 1 : 0, i) == 0 && hp < 0xFF) {
                    if (n > 0) {
                        SzDuel_SetUnitCurseRest((player == 0) ? 1 : 0, i, GetCap(0, hp - 2));
                    } else {
                        SzDuel_SetUnitCurseRest((player == 0) ? 1 : 0, i, hp - 1);
                    }
                }
            }
            other = SzDuel_GetUnitLoc((player == 0) ? 1 : 0, 0);
            if (SzDuel_GetUnit(player, i)) {
                if (!(Ta_IsLDAbl(0xF, (player == 0) ? 1 : 0) &&
                      Ta_IsLD_CurseObj((player == 0) ? 1 : 0, SzDuel_GetUnitKind(player, i) & 0x1F) &&
                      Ta_IsSquareRange(other & 0xFF, other >> 8, mine & 0xFF, mine >> 8,
                                    Ta_GetLDRange((player == 0) ? 1 : 0))) &&
                    TaPerm_IsPermCurseActive(player, i) == 0) {
                    SzDuel_SetUnitSpellRest(player, i, 0);
                }
            }
            mine = SzDuel_GetUnitLoc((player == 0) ? 1 : 0, i);
            other = SzDuel_GetUnitLoc(player, 0);
            if (SzDuel_GetUnit((player == 0) ? 1 : 0, i)) {
                if (!(Ta_IsLDAbl(0xF, player) &&
                      Ta_IsLD_CurseObj(player, SzDuel_GetUnitKind((player == 0) ? 1 : 0, i) & 0x1F) &&
                      Ta_IsSquareRange(other & 0xFF, other >> 8, mine & 0xFF, mine >> 8, Ta_GetLDRange(player))) &&
                    TaPerm_IsPermCurseActive((player == 0) ? 1 : 0, i) == 0) {
                    SzDuel_SetUnitSpellRest((player == 0) ? 1 : 0, i, 0);
                }
            }
        }
        for (i = 0; i <= 11; i++) {
            SzDuel_SetUnitCurseFlag(player, i, 0);
            SzDuel_SetUnitCurseFlag((player == 0) ? 1 : 0, i, 0);
        }
        return (phase + 1) << 16;
    case 4:
        for (i = 0; i < 8; i++) {
            v = Ta_GetSommonPiecePreference(player, i);
            if (v < 0) {
                continue;
            }
            vy = v & 0xFF;
            vx = v >> 8;
            w = SzDuel_GetMapUnitID(vy, vx);
            if (w >= 0) {
                if (player == Ta_IsUnitControl(w >> 8, w & 0xFF)) {
                    if (SzDuel_GetField(vy, vx) != 8) {
                        return (phase + 1) << 16;
                    }
                }
            } else {
                if (SzDuel_GetField(vy, vx) != 8) {
                    return (phase + 1) << 16;
                }
            }
        }
        return ((phase + 1) << 16) | 5;
    case 5:
        if (player != SzDuel_GetTurnFirst()) {
            if (SzDuel_GetTurnCount() >= 100) {
                return 0xFF0008;
            }
        }
        return 0xFF0000;
    }
    return 0xFF0000;
}

/* From the dotr-decomp CC0 bundle (commit 88c32bb2), chatC/imp/conv.py. */

extern int func_001DEE50_b(int index);
extern int func_001E1030_b(int a, int b);

/* Ends the duel for side `nSide` by condition `bCond`: experience and results. */
int Ta_Do_DuelEnd(int nSide, unsigned char bCond)
{
    int i;
    int gCount_1;
    int gCount_2;

    for (i = 1; i <= 5; i++) {
        if (SzDuel_GetUnitStatus(nSide, i, 4)) {
            SzData_CalcExp(nSide, func_001E1030_b(nSide, i), 0, 6);
        } else {
            SzData_CalcExp(nSide, func_001E1030_b(nSide, i), 0, 4);
        }
    }
    gCount_1 = func_001DEE50_b(nSide);
    gCount_2 = func_001DEE50_b(nSide == 0 ? 1 : 0);
    switch (bCond) {
    case 0:
        if (gCount_1 < 5) {
            SzData_CalcExp(nSide, func_001E1030_b(nSide, 0), 0, 40);
        } else if (gCount_1 < 10) {
            SzData_CalcExp(nSide, func_001E1030_b(nSide, 0), 0, 32);
        } else if (gCount_1 < 15) {
            SzData_CalcExp(nSide, func_001E1030_b(nSide, 0), 0, 24);
        } else {
            SzData_CalcExp(nSide, func_001E1030_b(nSide, 0), 0, 16);
        }
        if (gCount_2 < 5) {
            SzData_CalcExp(nSide == 0 ? 1 : 0, func_001E1030_b(nSide == 0 ? 1 : 0, 0), 0, -32);
        } else if (gCount_2 < 10) {
            SzData_CalcExp(nSide == 0 ? 1 : 0, func_001E1030_b(nSide == 0 ? 1 : 0, 0), 0, -24);
        } else if (gCount_2 < 15) {
            SzData_CalcExp(nSide == 0 ? 1 : 0, func_001E1030_b(nSide == 0 ? 1 : 0, 0), 0, -16);
        } else {
            SzData_CalcExp(nSide == 0 ? 1 : 0, func_001E1030_b(nSide == 0 ? 1 : 0, 0), 0, -8);
        }
        break;
    case 1:
        if (gCount_1 < 5) {
            SzData_CalcExp(nSide, func_001E1030_b(nSide, 0), 0, 32);
        } else if (gCount_1 < 10) {
            SzData_CalcExp(nSide, func_001E1030_b(nSide, 0), 0, 24);
        } else if (gCount_1 < 15) {
            SzData_CalcExp(nSide, func_001E1030_b(nSide, 0), 0, 16);
        } else {
            SzData_CalcExp(nSide, func_001E1030_b(nSide, 0), 0, 8);
        }
        if (gCount_2 < 5) {
            SzData_CalcExp(nSide == 0 ? 1 : 0, func_001E1030_b(nSide == 0 ? 1 : 0, 0), 0, -28);
        } else if (gCount_2 < 10) {
            SzData_CalcExp(nSide == 0 ? 1 : 0, func_001E1030_b(nSide == 0 ? 1 : 0, 0), 0, -20);
        } else if (gCount_2 < 15) {
            SzData_CalcExp(nSide == 0 ? 1 : 0, func_001E1030_b(nSide == 0 ? 1 : 0, 0), 0, -12);
        } else {
            SzData_CalcExp(nSide == 0 ? 1 : 0, func_001E1030_b(nSide == 0 ? 1 : 0, 0), 0, -4);
        }
        break;
    case 2:
        if (gCount_1 < 5) {
            SzData_CalcExp(nSide, func_001E1030_b(nSide, 0), 0, 44);
        } else if (gCount_1 < 10) {
            SzData_CalcExp(nSide, func_001E1030_b(nSide, 0), 0, 36);
        } else if (gCount_1 < 15) {
            SzData_CalcExp(nSide, func_001E1030_b(nSide, 0), 0, 28);
        } else {
            SzData_CalcExp(nSide, func_001E1030_b(nSide, 0), 0, 20);
        }
        if (gCount_2 < 5) {
            SzData_CalcExp(nSide == 0 ? 1 : 0, func_001E1030_b(nSide == 0 ? 1 : 0, 0), 0, -36);
        } else if (gCount_2 < 10) {
            SzData_CalcExp(nSide == 0 ? 1 : 0, func_001E1030_b(nSide == 0 ? 1 : 0, 0), 0, -28);
        } else if (gCount_2 < 15) {
            SzData_CalcExp(nSide == 0 ? 1 : 0, func_001E1030_b(nSide == 0 ? 1 : 0, 0), 0, -20);
        } else {
            SzData_CalcExp(nSide == 0 ? 1 : 0, func_001E1030_b(nSide == 0 ? 1 : 0, 0), 0, -12);
        }
        break;
    case 3:
        if (gCount_1 < 5) {
            SzData_CalcExp(nSide, func_001E1030_b(nSide, 0), 0, 48);
        } else if (gCount_1 < 10) {
            SzData_CalcExp(nSide, func_001E1030_b(nSide, 0), 0, 40);
        } else if (gCount_1 < 15) {
            SzData_CalcExp(nSide, func_001E1030_b(nSide, 0), 0, 32);
        } else {
            SzData_CalcExp(nSide, func_001E1030_b(nSide, 0), 0, 24);
        }
        if (gCount_2 < 5) {
            SzData_CalcExp(nSide == 0 ? 1 : 0, func_001E1030_b(nSide == 0 ? 1 : 0, 0), 0, -40);
        } else if (gCount_2 < 10) {
            SzData_CalcExp(nSide == 0 ? 1 : 0, func_001E1030_b(nSide == 0 ? 1 : 0, 0), 0, -32);
        } else if (gCount_2 < 15) {
            SzData_CalcExp(nSide == 0 ? 1 : 0, func_001E1030_b(nSide == 0 ? 1 : 0, 0), 0, -24);
        } else {
            SzData_CalcExp(nSide == 0 ? 1 : 0, func_001E1030_b(nSide == 0 ? 1 : 0, 0), 0, -16);
        }
        break;
    default:
        return -1;
    }
    return 1;
}

typedef struct Context_00273460 {
    u8 pad0[8];
    s32 cards;
} Context_00273460;

typedef struct State_00273460 {
    u16 alpha;
    u16 pad2;
    u16 phase;
    u8 ids[0x1A];
    s32 cards[45];
    u8 count;
    u8 padD5[0x2D];
    u16 timer;
} State_00273460;

typedef struct Setup_00273460 {
    s32 card;
    s32 x;
    s32 y;
    s32 z;
} Setup_00273460;


/* Effect script 112, step `ID`: its camera, fades and effect module; it destroys units, turns cards face up. */
s32 Ta_Eff_112(void *eInfo, void *Temp, s32 ID) {
    Setup_00273460 setup;
    s32 complete;
    Setup_00273460 *config = &setup;
    State_00273460 *walk;
    u8 *id;
    s32 index;
    s32 card;
    State_00273460 *state = Temp;
    Context_00273460 *context = eInfo;

    setup.card = 999;
    setup.x = 0;
    setup.y = 0;
    setup.z = 0;
    complete = 0;
    SzDuel_SetWindowDraw(0);
    if (ID >= 0) {
        InitEffectTemp(state);
        Ta_AllUnitFade(context, state, ID, -1, 1, 1);
        state->alpha = 128;
        TaEffect_LoadModule(state, 612);
        for (ID = 0; ID < Ta_GetUnitNumFrom22bitFlagList(context->cards); ID++) {
            card = Ta_GetUnitOwnerIDFromLstCount(context->cards, ID);
            SzEffect_SetBusyFlag2(card, 0);
            TaUtil_DoOpen(card >> 8, card & 255, 1);
        }
        TaView_ReqStdCompleteView(30);
        return 1;
    }
    switch (state->phase) {
    case 0:
        ID = 0;
        if (state->alpha > 48) {
            state->alpha -= 15;
        } else {
            for (ID = 0; ID < Ta_GetUnitNumFrom22bitFlagList(context->cards); ID++) {
                if (SzEffect_IsModelStandby2(Ta_GetUnitOwnerIDFromLstCount(context->cards, ID)) != 0) {
                    complete++;
                }
            }
            if (complete == Ta_GetUnitNumFrom22bitFlagList(context->cards)) {
                if (TaEffect_IsLoadModule(state) == 1) {
                    if (state->timer++ >= 46) {
                        if (complete == 1) {
                            TaView_ReqFocusCamera(0, Ta_GetUnitOwnerIDFromLstCount(context->cards, 0), 100, 180);
                        }
                        SzDuel_OpenMsgPopup(0, -120, 80, 276);
                        Ta_SetEffectDependOnFlagLst(context, state, config, 612);
                        state->timer = 0;
                        state->phase++;
                    }
                }
            }
            state->alpha = 48;
        }
        if (state->alpha < 48) {
            state->alpha = 48;
        }
        SzEffect_SetBlackOutForDuel((u8)state->alpha);
        break;
    case 1:
        index = 0;
        walk = state;
        for (; index < state->count; index++) {
            id = &state->ids[index];
            if (SzEffect_IsUse(*id) == 1) {
                TaEffect_SetOuchMotion((u16)walk->cards[0]);
                if ((walk->cards[0] >> 16) == 0) {
                    if (state->timer++ >= 32) {
                        card = walk->cards[0];
                        Ta_UnitFade((card & 65535) >> 8, card & 255, -1, 1, 3);
                        walk->cards[0] |= 0x10000;
                    }
                }
                if (SzEffect_GetStatus(*id) == 2) {
                    card = walk->cards[0];
                    if (card >= 0) {
                        SzEffect_SetBusyFlag2(card & 65535, 1);
                        card = walk->cards[0];
                        Ta_DelUnit((card & 65535) >> 8, card & 255);
                        walk->cards[0] = -1;
                    }
                }
            } else {
                complete++;
            }
            walk = (State_00273460 *)((u8 *)walk + 4);
        }
        if (complete >= state->count) {
            Ta_AllUnitFade(context, state, ID, 1, 0, 1);
            state->timer = 0;
            SzDuel_CloseMsgPopup();
            TaView_RestoreOriginalView(state, 16);
            state->phase++;
        }
        break;
    default:
        state->alpha += 15;
        if (state->alpha > 128) {
            state->alpha = 128;
        }
        SzEffect_SetBlackOutForDuel((u8)state->alpha);
        if (state->alpha == 128) {
            if (state->timer++ > 16 && Ta_IsFinishFade() == 1) {
                if (SzDuel_GetWindowDisp() != 0) {
                    SzDuel_SetWindowDraw(1);
                }
                SzDuel_CloseMsgPopup();
                return 0;
            }
        }
        break;
    }
    return 1;
}

typedef struct Masks_002738B0 {
    u32 unknown;
    u32 first : 22;
    u32 firstFlags : 10;
    s32 second;
    u32 third : 22;
    u32 thirdFlags : 9;
    u32 inverted : 1;
} Masks_002738B0;

typedef struct State_002738B0 {
    u16 player;
    u16 unknown02;
    u16 step;
    u8 handles[0x1A];
    s32 counter;
    u8 unknown24[0xB0];
    u8 count;
    u8 unknownD5[0x2D];
    u16 ticks;
} State_002738B0;

typedef struct Command_002738B0 {
    s32 id;
    s32 flags;
    s32 position;
    s32 argument;
} Command_002738B0;


/* Effect script 113, step `ID`: its camera, fades and effect module; it destroys units, binds units with a spell,
   turns cards face up. */
s32 Ta_Eff_113(void *eInfo, void *Temp, s32 ID) {
    extern s32 SzDuel_SetUnitSpellRest();
    Command_002738B0 command;
    Command_002738B0 *cmd = &command;
    Masks_002738B0 *masks = eInfo;
    State_002738B0 *state = Temp;
    s32 position;
    s32 player;
    s32 position0;
    s32 i;
    s32 ready;
    s32 column;
    s32 row;
    s32 secondIndex;
    s32 secondCount;
    s32 thirdIndex;
    s32 thirdCount;
    s32 firstCount;
    s32 firstIndex;
    s32 packed;

    command.id = 999;
    command.flags = 0;
    command.position = 0;
    command.argument = 0;
    SzDuel_SetWindowDraw(0);
    if (ID >= 0) {
        InitEffectTemp(state);
        if (((u32 *)masks)[3] >> 31) {
            player = (SzDuel_GetTurnOwner() == 0) ? 1 : 0;
        } else {
            player = SzDuel_GetTurnOwner();
        }
        state->player = player;
        position = SzDuel_GetUnitLoc(state->player, 0);
        TaView_ReqFocusCamera(0, state->player << 8, 300, 300);
        SzDuel_OpenMsgPopup(0, -120, 80, 270);
        if (masks->first) {
            Ta_SetRangeVisual(position & 0xFF, position >> 8, 0,
                         Ta_IsLDAbl(9, state->player), 1, 1, 16);
        } else if (masks->second) {
            Ta_SetRangeVisual(position & 0xFF, position >> 8, 0,
                         Ta_IsLDAbl(9, state->player), 1, 1, 15);
        } else if (masks->third) {
            Ta_SetRangeVisual(position & 0xFF, position >> 8, 0,
                         Ta_IsLDAbl(9, state->player), 1, 1, 13);
        }
        TaEffect_LoadModule(state, 0x265);
        if (masks->first) {
            TaEffect_LoadModule(state, 0x25B);
        }
        if (masks->second) {
            TaEffect_LoadModule(state, 0x1F4);
        }
        if (masks->third) {
            TaEffect_LoadModule(state, 0x201);
        }
        return 1;
    }

    switch (state->step) {
    case 0:
        if (TaEffect_IsLoadModule(state) == 1) {
            position0 = SzDuel_GetUnitLoc(state->player, 0);
            Ta_SetRangeVisual(position0 & 0xFF, position0 >> 8, 0,
                         Ta_IsLDAbl(9, state->player), 0, -1, 16);
            cmd->id = 0x265;
            cmd->flags = 0;
            cmd->position = state->player << 8;
            cmd->argument = 0;
            state->handles[0] = Ta_Do_Effect((s32 *)cmd, state);
            state->counter = 0;
            state->step++;
        }
        break;
    case 1:
        if (SzEffect_IsUse(state->handles[0]) == 1) {
            return 1;
        }
        TaView_ReqStdCompleteView(16);
        state->step++;
        return 1;
    case 2:
        if (state->ticks++ >= 16) {
            if (masks->first) {
                Ta_SetEffectDependOnFlagLst3(masks, state, (s32 *)cmd, 0x25B);
            }
            if (masks->second) {
                Ta_SetEffectDependOnFlagLst(masks, state, (s32 *)cmd, 0x1F4);
            }
            if (masks->third) {
                Ta_SetEffectDependOnFlagLst2(masks, state, (s32 *)cmd, 0x201);
            }
            state->step++;
        }
        return 1;
    case 3:
        i = 0;
        ready = 0;
        while (i < state->count) {
            if (SzEffect_IsUse(state->handles[i]) == 0) {
                ready++;
            }
            i++;
        }
        if (state->count == ready) {
            state->step++;
        }
        return 1;
    case 4:
        firstCount = Ta_GetUnitNumFrom22bitFlagList(masks->first);
        for (firstIndex = 0; firstIndex < firstCount; firstIndex++) {
            packed = Ta_GetUnitOwnerIDFromLstCount(masks->first, firstIndex);
            Ta_DelUnit(packed >> 8, packed & 0xFF);
        }
        secondCount = Ta_GetUnitNumFrom22bitFlagList(masks->second);
        for (secondIndex = 0; secondIndex < secondCount; secondIndex++) {
            packed = Ta_GetUnitOwnerIDFromLstCount(masks->second, secondIndex);
            row = packed >> 8;
            column = packed & 0xFF;
            SzDuel_SetUnitSpellRest(row, column, 255);
            SzDuel_SetUnitStatus(row, column, 0, 1);
        }
        thirdCount = Ta_GetUnitNumFrom22bitFlagList(masks->third);
        for (thirdIndex = 0; thirdIndex < thirdCount; thirdIndex++) {
            packed = Ta_GetUnitOwnerIDFromLstCount(masks->third, thirdIndex);
            TaUtil_DoOpen(packed >> 8, packed & 0xFF, 1);
        }
        SzDuel_CloseMsgPopup();
        TaView_RestoreOriginalView(state, 16);
        state->ticks = 0;
        state->step++;
        break;
    default:
        if (state->ticks++ > 16) {
            if (SzDuel_GetWindowDisp() != 0) {
                SzDuel_SetWindowDraw(1);
            }
            SzDuel_CloseMsgPopup();
            return 0;
        }
        break;
    }
    return 1;
}

/* From the dotr-decomp CC0 bundle (commit 88c32bb2), chatC/imp/conv.py. */

struct jp_6989c_273e60 {
    int eNO;
    unsigned int dwFrom;
    unsigned int dwTo;
    unsigned int dwPar;
};
struct jp_68cb4_273e60 {
    int fLoad : 1;
    unsigned char bModNum : 5;
    unsigned short wModule[24];
    unsigned char bModCond[24];
};
struct jp_69942_273e60 {
    unsigned short wCount_1;
    unsigned short wCount_2;
    unsigned short wLvl;
    unsigned char eID[24];
    int ePos[24];
    struct jp_68cb4_273e60 eMod;
    unsigned int fObj;
    unsigned int fObj2;
    unsigned char oNum;
    unsigned char unknown_d5[0xb];
    int camDat[8];
    unsigned char bCamLvl;
    unsigned short wCamTime;
    unsigned char unknown_104[0xc];
    int nTasakiEfc[0x10c];
};
extern int func_00255AC0_273e60(struct jp_69942_273e60 *q, int id);
extern void func_00260AF0_b(unsigned char who, int packed, int add, int value);
extern void func_00260A70_273e60(struct jp_69942_273e60 *Temp, unsigned char b);
extern int func_001E1030_b(int a, int b);
extern int func_001E1E10_b(int a, int b);
extern int func_001E1CB0_b(int a, int b);

/* Effect script BTL_000, step `ID`: its camera, fades and effect module; it changes attack or defence, changes
   life points. */
int Ta_Eff_BTL_000(void *eInfo_v, void *Temp_v, int ID)
{
    struct jp_6989c_273e60 * eInfo = eInfo_v;
    struct jp_69942_273e60 * Temp = Temp_v;
    int stored;
    struct jp_6989c_273e60 eCall;
    struct jp_6989c_273e60 *pCall = &eCall;
    int temp;
    int i;
    eCall.eNO = 999;
    eCall.dwFrom = 0;
    eCall.dwTo = 0;
    eCall.dwPar = 0;
    SzDuel_SetWindowDraw(0);
    if (eInfo == 0 || Temp == 0 || pCall == 0) {
        SzDuel_CloseMsgPopup();
        return 0;
    }
    if (ID >= 0) {
        InitEffectTemp(Temp);
        if (Ta_IsLDAbl(6, eInfo->dwTo) != 0) {
            func_00255AC0_273e60(Temp, 557);
            Temp->wLvl = 16;
        }
        if (((eInfo->dwPar >> 20) & 3) != 0 || ((eInfo->dwPar >> 22) & 3) != 0) {
            func_00255AC0_273e60(Temp, 513);
        }
        func_00255AC0_273e60(Temp, 604);
        func_00255AC0_273e60(Temp, 605);
        func_00260AF0_b(0, eInfo->dwFrom, 300, 280);
        Temp->wCount_1 = 128;
        return 1;
    }
    switch (Temp->bCamLvl) {
    case 0:
        if (Temp->wCamTime++ == 0) {
            SzSound_PlaySE(0, 39);
            SzGame_SetAutoBlur(6);
            func_00260AF0_b(12, eInfo->dwFrom, 100, 180);
            return 1;
        }
        if (Temp->wCamTime >= 12) {
            SzGame_SetAutoBlur(4);
        }
        if (Temp->wCamTime >= 24) {
            if (func_001E1E10_b(eInfo->dwFrom >> 8, eInfo->dwFrom & 0xFF) == 255) {
                if (func_001E1CB0_b(eInfo->dwFrom >> 8, eInfo->dwFrom & 0xFF) == 128) {
                    if (SzEffect_IsModelStandby2(eInfo->dwFrom) != 0) {
                        SzGame_SetAutoBlur(0);
                        func_00260AF0_b(0, eInfo->dwTo << 8, 300, 280);
                        Temp->wCamTime = 0;
                        Temp->bCamLvl++;
                    }
                }
            }
        }
        return 1;
    case 1:
        if (Temp->wCamTime++ == 0) {
            SzSound_PlaySE(0, 39);
            SzGame_SetAutoBlur(6);
            func_00260AF0_b(12, eInfo->dwTo << 8, 100, 180);
            return 1;
        }
        if (Temp->wCamTime >= 12) {
            SzGame_SetAutoBlur(4);
        }
        if (Temp->wCamTime >= 24) {
            if (SzEffect_IsModelStandby2(eInfo->dwTo << 8) != 0) {
                SzGame_SetAutoBlur(0);
                func_00260A70_273e60(Temp, 0);
                Temp->wCamTime = 0;
                Temp->bCamLvl++;
            }
        }
        return 1;
    default:
        break;
    }
    if (TaEffect_IsLoadModule(Temp) != 1) {
        return 1;
    }
    switch (Temp->wLvl) {
    case 0:
        if (TaEffect_IsLoadModule(Temp) == 1) {
            SzEffect_SetBusyFlag2(eInfo->dwFrom, 1);
            SzEffect_SetBusyFlag2(eInfo->dwTo << 8, 1);
            if (((eInfo->dwPar >> 20) & 3) != 0) {
                SzDuel_OpenMsgPopup(0, -120, 80, 260);
                pCall->eNO = 513;
                pCall->dwFrom = 0;
                pCall->dwTo = (unsigned short)eInfo->dwFrom;
                pCall->dwPar = 0;
                

                if ((stored = (Temp->eID[Temp->oNum] = Ta_Do_Effect(pCall, Temp))) >= 0) {
                    Temp->oNum++;
                }
            }
            if (((eInfo->dwPar >> 22) & 3) != 0) {
                SzDuel_OpenMsgPopup(0, -120, 80, 260);
                pCall->eNO = 513;
                pCall->dwFrom = 0;
                pCall->dwTo = (unsigned short)eInfo->dwTo;
                pCall->dwPar = 0;
                if ((stored = (Temp->eID[Temp->oNum] = Ta_Do_Effect(pCall, Temp))) > 0) {
                    Temp->oNum++;
                }
            }
            Temp->wLvl++;
        }
        return 1;
    case 1:
        if (Temp->oNum > 0) {
            for (i = 0; i < Temp->oNum; i++) {
                if (SzEffect_IsUse(Temp->eID[i]) != 0) {
                    return 1;
                }
            }
        }
        SzDuel_CloseMsgPopup();
        Temp->oNum = 0;
        Temp->wLvl++;
        return 1;
    case 2:
        if ((Temp->wCount_1 = Ta_CalcCtrlRate(Temp->wCount_1, 15, -1)) > 0) {
            SzEffect_SetBlackOutForDuel((unsigned char)Temp->wCount_1);
            SzEffect_SetBlackOutForMonster((unsigned char)Temp->wCount_1);
        } else {
            SzEffect_SetBlackOutForDuel((unsigned char)Temp->wCount_1);
            SzEffect_SetBlackOutForMonster((unsigned char)Temp->wCount_1);
            Temp->wLvl++;
        }
        return 1;
    case 3:
        temp = Ta_GetLPRevByNaturalEffect(44, (unsigned short)eInfo->dwPar);
        pCall->eNO = 604;
        pCall->dwFrom = eInfo->dwFrom;
        pCall->dwTo = 0;
        if (temp == 0) {
            temp = 0x30000;
        }
        pCall->dwPar = temp;
        Temp->eID[Temp->oNum] = Ta_Do_Effect(pCall, Temp);
        Temp->ePos[Temp->oNum] = 0;
        Temp->oNum++;
        Temp->wLvl++;
        return 1;
    case 4:
        if (SzEffect_IsUse(Temp->eID[Temp->oNum - 1]) != 0) {
            if (SzEffect_GetStatus(Temp->eID[Temp->oNum - 1]) == 2) {
                if (Temp->ePos[Temp->oNum - 1] == 1) {
                    SzSound_PlaySE(1, 65);
                }
                Temp->ePos[Temp->oNum - 1]++;
            }
            return 1;
        }
        pCall->eNO = 605;
        pCall->dwFrom = eInfo->dwFrom;
        pCall->dwTo = 0;
        pCall->dwPar = 0;
        Temp->eID[Temp->oNum] = Ta_Do_Effect(pCall, Temp);
        Temp->oNum++;
        SzDuel_CalcLP(eInfo->dwTo, 1, Ta_GetLPRevByNaturalEffect(44, (unsigned short)eInfo->dwPar));
        if (SzDuel_GetLP(eInfo->dwTo) > 0) {
            SzData_CalcExp(eInfo->dwFrom >> 8, func_001E1030_b(eInfo->dwFrom >> 8, eInfo->dwFrom & 0xFF), 0, 20);
        } else {
            SzData_CalcExp(eInfo->dwFrom >> 8, func_001E1030_b(eInfo->dwFrom >> 8, eInfo->dwFrom & 0xFF), 0, 24);
        }
        SzData_CalcExp(eInfo->dwTo, func_001E1030_b(eInfo->dwTo, 0), 0, -8);
        Temp->wLvl++;
        return 1;
    case 5:
        if ((Temp->wCount_1 = Ta_CalcCtrlRate(Temp->wCount_1, 15, 1)) < 128) {
            SzEffect_SetBlackOutForDuel((unsigned char)Temp->wCount_1);
            SzEffect_SetBlackOutForMonster((unsigned char)Temp->wCount_1);
        }
        if (SzEffect_IsUse(Temp->eID[Temp->oNum - 1]) != 0) {
            if (Temp->fObj2++ == 20) {
                SzSound_PlaySE(0, 2);
            }
            return 1;
        }
        Temp->wLvl++;
        break;
    case 16:
        SzDuel_OpenMsgPopup(0, -120, 80, 270);
        pCall->eNO = 557;
        pCall->dwFrom = 0;
        pCall->dwTo = eInfo->dwFrom;
        pCall->dwPar = 0;
        Temp->eID[0] = Ta_Do_Effect(pCall, Temp);
        Temp->wLvl++;
        break;
    case 17:
        if (SzEffect_IsUse(Temp->eID[0]) != 0) {
            return 1;
        }
        SzDuel_CloseMsgPopup();
        Temp->wLvl = 0;
        break;
    default:
        if ((Temp->wCount_1 = Ta_CalcCtrlRate(Temp->wCount_1, 15, 1)) < 128) {
            SzEffect_SetBlackOutForDuel((unsigned char)Temp->wCount_1);
            SzEffect_SetBlackOutForMonster((unsigned char)Temp->wCount_1);
            return 1;
        }
        if ((eInfo->dwFrom >> 16) != 0) {
            if ((eInfo->dwFrom >> 31) == 0) {
                TaUtil_CalcUnitAP((eInfo->dwFrom & 0xFFFF) >> 8, eInfo->dwFrom & 0xFF, 1, (eInfo->dwFrom >> 16) & 0x7FFF);
                TaUtil_CalcUnitDP((eInfo->dwFrom & 0xFFFF) >> 8, eInfo->dwFrom & 0xFF, 1, (eInfo->dwFrom >> 16) & 0x7FFF);
            } else {
                TaUtil_CalcUnitAP((eInfo->dwFrom & 0xFFFF) >> 8, eInfo->dwFrom & 0xFF, 0, (eInfo->dwFrom >> 16) & 0x7FFF);
                TaUtil_CalcUnitDP((eInfo->dwFrom & 0xFFFF) >> 8, eInfo->dwFrom & 0xFF, 0, (eInfo->dwFrom >> 16) & 0x7FFF);
            }
        }
        SzEffect_SetBlackOutForDuel(128);
        SzEffect_SetBlackOutForMonster(128);
        if (SzDuel_GetWindowDisp() != 0) {
            SzDuel_SetWindowDraw(1);
        }
        SzDuel_CloseMsgPopup();
        return 0;
    }
    return 1;
}

struct jp_6989c {
    int eNO;
    unsigned int dwFrom;
    unsigned int dwTo;
    unsigned int dwPar;
};
struct jp_68cb4 {
    int fLoad : 1;
    unsigned char bModNum : 5;
    unsigned short wModule[24];
    unsigned char bModCond[24];
};
struct jp_69942 {
    unsigned short wCount_1;
    unsigned short wCount_2;
    unsigned short wLvl;
    unsigned char eID[24];
    int ePos[24];
    struct jp_68cb4 eMod;
    unsigned int fObj;
    unsigned int fObj2;
    unsigned char oNum;
    unsigned char unknown_d5[0xb];
    int camDat[8];
    unsigned char bCamLvl;
    unsigned short wCamTime;
    unsigned char unknown_104[0xc];
    int nTasakiEfc[0x10c];
};
extern int func_00255AC0_b(struct jp_69942 *q, int id);
extern void func_00260AF0_b(unsigned char who, int packed, int add, int value);
extern void func_00260A70_b(struct jp_69942 *Temp, unsigned char b);
extern void func_002503B0_b(int a, int b, unsigned char n);
extern int func_001E1E10_b(int a, int b);
extern int func_001E1CB0_b(int a, int b);
extern int func_001DE2A0_b(int side);

/* Effect script BTL_001, step `ID`: its camera, fades and effect module; it destroys units, changes attack or
   defence, changes life points. */
int Ta_Eff_BTL_001(void *eInfo_v, void *Temp_v, int ID)
{
    struct jp_6989c * eInfo = eInfo_v;
    struct jp_69942 * Temp = Temp_v;
    int stored;
    struct jp_6989c eCall;
    struct jp_6989c *pCall = &eCall;
    int temp;
    int i;
    eCall.eNO = 999;
    eCall.dwFrom = 0;
    eCall.dwTo = 0;
    eCall.dwPar = 0;
    SzDuel_SetWindowDraw(0);
    if (eInfo == 0 || Temp == 0 || pCall == 0) {
        SzDuel_CloseMsgPopup();
        return 0;
    }
    if (ID >= 0) {
        InitEffectTemp(Temp);
        Temp->wCount_1 = 128;
        if (((eInfo->dwPar >> 20) & 3) != 0 || ((eInfo->dwPar >> 22) & 3) != 0) {
            func_00255AC0_b(Temp, 513);
        }
        func_00255AC0_b(Temp, 604);
        func_00255AC0_b(Temp, 605);
        func_00260AF0_b(0, (unsigned short)eInfo->dwFrom, 300, 280);
        return 1;
    }
    switch (Temp->bCamLvl) {
    case 0:
        if (Temp->wCamTime++ == 0) {
            SzSound_PlaySE(0, 39);
            SzGame_SetAutoBlur(6);
            func_00260AF0_b(12, (unsigned short)eInfo->dwFrom, 100, 180);
            return 1;
        }
        if (Temp->wCamTime >= 12) {
            SzGame_SetAutoBlur(4);
        }
        if (Temp->wCamTime >= 24) {
            if (func_001E1E10_b((eInfo->dwFrom & 0xFFFF) >> 8, eInfo->dwFrom & 0xFF) == 255) {
                if (func_001E1CB0_b((eInfo->dwFrom & 0xFFFF) >> 8, eInfo->dwFrom & 0xFF) == 128) {
                    if (SzEffect_IsModelStandby2((unsigned short)eInfo->dwFrom) != 0) {
                        SzGame_SetAutoBlur(0);
                        func_00260AF0_b(0, (unsigned short)eInfo->dwTo, 300, 280);
                        Temp->wCamTime = 0;
                        Temp->bCamLvl++;
                    }
                }
            }
        }
        return 1;
    case 1:
        if (Temp->wCamTime++ == 0) {
            SzSound_PlaySE(0, 39);
            SzGame_SetAutoBlur(6);
            func_00260AF0_b(12, (unsigned short)eInfo->dwTo, 100, 180);
            return 1;
        }
        if (Temp->wCamTime >= 12) {
            SzGame_SetAutoBlur(4);
        }
        if (Temp->wCamTime >= 24) {
            if (func_001E1E10_b((eInfo->dwTo & 0xFFFF) >> 8, eInfo->dwTo & 0xFF) == 255) {
                if (func_001E1CB0_b((eInfo->dwTo & 0xFFFF) >> 8, eInfo->dwTo & 0xFF) == 128) {
                    if (SzEffect_IsModelStandby2((unsigned short)eInfo->dwTo) != 0) {
                        SzGame_SetAutoBlur(0);
                        func_00260A70_b(Temp, 0);
                        Temp->wCamTime = 0;
                        Temp->bCamLvl++;
                    }
                }
            }
        }
        return 1;
    }
    switch (Temp->wLvl) {
    case 0:
        if (TaEffect_IsLoadModule(Temp) == 1) {
            SzEffect_SetBusyFlag2((unsigned short)eInfo->dwFrom, 1);
            SzEffect_SetBusyFlag2((unsigned short)eInfo->dwTo, 1);
            if (((eInfo->dwPar >> 20) & 3) != 0) {
                SzDuel_OpenMsgPopup(0, -120, 80, 260);
                pCall->eNO = 513;
                pCall->dwFrom = 0;
                pCall->dwTo = (unsigned short)eInfo->dwFrom;
                pCall->dwPar = 0;
                

                if ((stored = (Temp->eID[Temp->oNum] = Ta_Do_Effect(pCall, Temp))) >= 0) {
                    Temp->oNum++;
                }
            }
            if (((eInfo->dwPar >> 22) & 3) != 0) {
                SzDuel_OpenMsgPopup(0, -120, 80, 260);
                pCall->eNO = 513;
                pCall->dwFrom = 0;
                pCall->dwTo = (unsigned short)eInfo->dwTo;
                pCall->dwPar = 0;
                if ((stored = (Temp->eID[Temp->oNum] = Ta_Do_Effect(pCall, Temp))) > 0) {
                    Temp->oNum++;
                }
            }
            Temp->wLvl++;
        }
        return 1;
    case 1:
        if (Temp->oNum > 0) {
            for (i = 0; i < Temp->oNum; i++) {
                if (SzEffect_IsUse(Temp->eID[i]) != 0) {
                    return 1;
                }
            }
        }
        SzDuel_CloseMsgPopup();
        Temp->oNum = 0;
        Temp->wLvl++;
        return 1;
    case 2:
        Temp->wCamTime++;
        if ((Temp->wCount_1 = Ta_CalcCtrlRate(Temp->wCount_1, 15, -1)) > 0) {
            SzEffect_SetBlackOutForDuel((unsigned char)Temp->wCount_1);
            SzEffect_SetBlackOutForMonster((unsigned char)Temp->wCount_1);
        } else {
            SzEffect_SetBlackOutForDuel((unsigned char)Temp->wCount_1);
            SzEffect_SetBlackOutForMonster((unsigned char)Temp->wCount_1);
            if (Temp->wCamTime >= 8) {
                if ((unsigned short)eInfo->dwPar == 0xFFFF) {
                    temp = 0;
                } else {
                    temp = Ta_GetLPRevByNaturalEffect(44, (unsigned short)eInfo->dwPar);
                }
                if (temp == 0) {
                    if (((eInfo->dwPar >> 28) & 1) == 1) {
                        pCall->eNO = 604;
                        pCall->dwFrom = (unsigned short)eInfo->dwFrom;
                        pCall->dwTo = (unsigned short)eInfo->dwTo;
                        pCall->dwPar = (((eInfo->dwPar >> 20) & 1) << 19) | (temp | 0x20000) | (((eInfo->dwPar >> 22) & 1) << 20);
                    } else {
                        pCall->eNO = 604;
                        pCall->dwFrom = (unsigned short)eInfo->dwFrom;
                        pCall->dwTo = (unsigned short)eInfo->dwTo;
                        pCall->dwPar = (((eInfo->dwPar >> 20) & 1) << 19) | (temp | 0x30000) | (((eInfo->dwPar >> 22) & 1) << 20);
                    }
                } else {
                    if (((eInfo->dwPar >> 28) & 1) == 1) {
                        pCall->eNO = 604;
                        pCall->dwFrom = (unsigned short)eInfo->dwFrom;
                        pCall->dwTo = (unsigned short)eInfo->dwTo;
                        pCall->dwPar = (((eInfo->dwPar >> 20) & 1) << 19) | (temp | 0x10000) | (((eInfo->dwPar >> 22) & 1) << 20);
                    } else {
                        pCall->eNO = 604;
                        pCall->dwFrom = (unsigned short)eInfo->dwFrom;
                        pCall->dwTo = (unsigned short)eInfo->dwTo;
                        pCall->dwPar = (((eInfo->dwPar >> 20) & 1) << 19) | temp | (((eInfo->dwPar >> 22) & 1) << 20);
                    }
                }
                if ((stored = (Temp->eID[0] = Ta_Do_Effect(pCall, Temp))) >= 0) {
                    Temp->ePos[0] = 0;
                    Temp->oNum++;
                }
                pCall->eNO = 605;
                pCall->dwFrom = (unsigned short)eInfo->dwFrom;
                pCall->dwTo = (unsigned short)eInfo->dwTo;
                pCall->dwPar = (((eInfo->dwPar >> 19) & 1) << 1) | ((eInfo->dwPar >> 18) & 1);
                Temp->eID[Temp->oNum] = Ta_Do_Effect(pCall, Temp);
                Temp->ePos[Temp->oNum] = 0;
                SzEffect_Sleep(Temp->eID[Temp->oNum], 1);
                Temp->wLvl++;
            }
        }
        return 1;
    case 3:
        if (SzEffect_IsUse(Temp->eID[0]) != 0) {
            if (SzEffect_GetStatus(Temp->eID[0]) == 2) {
                switch (Temp->ePos[0]) {
                case 0:
                    Temp->ePos[0]++;
                    if (func_001DE2A0_b(SzDuel_GetTurnOwner()) != 0) {
                        if ((unsigned short)eInfo->dwPar != 0xFFFF) {
                            if (TaTuto_IsTuto(SzDuel_GetTurnOwner()) == 0) {
                                SzEffect_Sleep(Temp->eID[0], 1);
                                return 4;
                            }
                        }
                    }
                    break;
                case 1:
                case 2:
                    func_00255AC0_b(Temp, 500);
                    Temp->ePos[0]++;
                    SzSound_PlaySE(1, 65);
                    break;
                }
            }
            return 1;
        }
        Temp->wCount_1 = 0;
        SzEffect_SetBlackOutForDuel((unsigned char)Temp->wCount_1);
        SzEffect_SetBlackOutForMonster((unsigned char)Temp->wCount_1);
        if (((eInfo->dwPar >> 16) & 1) == 1 && (temp = (unsigned short)eInfo->dwPar) != 0xFFFF) {
            SzDuel_CalcLP(Ta_IsUnitControl((eInfo->dwTo & 0xFFFF) >> 8, eInfo->dwTo & 0xFF), 1, Ta_GetLPRevByNaturalEffect(44, temp));
        } else if (((eInfo->dwPar >> 17) & 1) == 1 && (temp = (unsigned short)eInfo->dwPar) != 0xFFFF) {
            SzDuel_CalcLP(Ta_IsUnitControl((eInfo->dwFrom & 0xFFFF) >> 8, eInfo->dwFrom & 0xFF), 1, Ta_GetLPRevByNaturalEffect(44, temp));
        }
        SzEffect_Sleep(Temp->eID[Temp->oNum++], 0);
        Temp->fObj2 = 0;
        Temp->wLvl++;
        return 1;
    case 4:
        if ((Temp->wCount_1 = Ta_CalcCtrlRate(Temp->wCount_1, 15, 1)) < 128) {
            SzEffect_SetBlackOutForDuel((unsigned char)Temp->wCount_1);
            SzEffect_SetBlackOutForMonster((unsigned char)Temp->wCount_1);
        }
        if (SzEffect_IsUse(Temp->eID[Temp->oNum - 1]) != 0) {
            switch (Temp->fObj2++) {
            case 0:
                if (((eInfo->dwPar >> 19) & 1) != 0) {
                    Temp->ePos[Temp->oNum - 1]++;
                    SzSound_PlaySE(1, 66);
                    SzSound_PlaySE(1, 45);
                }
                if (((eInfo->dwPar >> 18) & 1) != 0) {
                    Temp->ePos[Temp->oNum - 1]++;
                    SzSound_PlaySE(1, 66);
                    SzSound_PlaySE(1, 45);
                }
                break;
            case 20:
                if (Temp->ePos[Temp->oNum - 1] == 0) {
                    if (((eInfo->dwPar >> 19) & 1) == 0) {
                        SzSound_PlaySE(0, 2);
                    }
                    if (((eInfo->dwPar >> 18) & 1) == 0) {
                        SzSound_PlaySE(0, 2);
                    }
                }
                break;
            case 40:
                if (Temp->ePos[Temp->oNum - 1] > 0) {
                    if (((eInfo->dwPar >> 19) & 1) == 0) {
                        SzSound_PlaySE(0, 2);
                    }
                    if (((eInfo->dwPar >> 18) & 1) == 0) {
                        SzSound_PlaySE(0, 2);
                    }
                }
                break;
            }
            return 1;
        }
        if ((eInfo->dwPar >> 25) != 0) {
            if (((eInfo->dwPar >> 26) & 1) == 1 && ((eInfo->dwPar >> 19) & 1) == 0) {
                func_002503B0_b((eInfo->dwFrom & 0xFFFF) >> 8, eInfo->dwFrom & 0xFF, 1);
                func_00260AF0_b(0, (unsigned short)eInfo->dwFrom, 180, 180);
                SzDuel_OpenMsgPopup(0, -120, 80, 264);
                pCall->eNO = 500;
                pCall->dwFrom = 0;
                pCall->dwTo = (unsigned short)eInfo->dwFrom;
                pCall->dwPar = 0;
                Temp->eID[0] = Ta_Do_Effect(pCall, Temp);
            } else if (((eInfo->dwPar >> 25) & 1) == 1 && ((eInfo->dwPar >> 18) & 1) == 0) {
                SzDuel_OpenMsgPopup(0, -120, 80, 264);
                func_002503B0_b((eInfo->dwTo & 0xFFFF) >> 8, eInfo->dwTo & 0xFF, 1);
                pCall->eNO = 500;
                pCall->dwFrom = 0;
                pCall->dwTo = (unsigned short)eInfo->dwTo;
                pCall->dwPar = 0;
                func_00260AF0_b(0, (unsigned short)eInfo->dwTo, 180, 180);
                Temp->eID[0] = Ta_Do_Effect(pCall, Temp);
            }
            Temp->wLvl = 5;
        }
        Temp->wLvl = 16;
        return 1;
    case 5:
        if ((Temp->wCount_1 = Ta_CalcCtrlRate(Temp->wCount_1, 15, 1)) < 128) {
            SzEffect_SetBlackOutForDuel((unsigned char)Temp->wCount_1);
            SzEffect_SetBlackOutForMonster((unsigned char)Temp->wCount_1);
        }
        

        if (SzEffect_IsUse(Temp->eID[0]) == 0) {
            (void)Temp->wLvl;
        }
        break;
    default:
        if ((Temp->wCount_1 = Ta_CalcCtrlRate(Temp->wCount_1, 15, 1)) < 128) {
            SzEffect_SetBlackOutForDuel((unsigned char)Temp->wCount_1);
            SzEffect_SetBlackOutForMonster((unsigned char)Temp->wCount_1);
            return 1;
        }
        if (SzEffect_IsUse(Temp->eID[0]) == 1) {
            return 1;
        }
        SzDuel_CloseMsgPopup();
        func_00260A70_b(Temp, 0);
        if ((eInfo->dwFrom >> 16) != 0) {
            if ((eInfo->dwFrom >> 31) == 0) {
                TaUtil_CalcUnitAP((eInfo->dwFrom & 0xFFFF) >> 8, eInfo->dwFrom & 0xFF, 1, (eInfo->dwFrom >> 16) & 0x7FFF);
                TaUtil_CalcUnitDP((eInfo->dwFrom & 0xFFFF) >> 8, eInfo->dwFrom & 0xFF, 1, (eInfo->dwFrom >> 16) & 0x7FFF);
            } else {
                TaUtil_CalcUnitAP((eInfo->dwFrom & 0xFFFF) >> 8, eInfo->dwFrom & 0xFF, 0, (eInfo->dwFrom >> 16) & 0x7FFF);
                TaUtil_CalcUnitDP((eInfo->dwFrom & 0xFFFF) >> 8, eInfo->dwFrom & 0xFF, 0, (eInfo->dwFrom >> 16) & 0x7FFF);
            }
        }
        if ((eInfo->dwTo >> 16) != 0) {
            if ((eInfo->dwTo >> 31) == 0) {
                TaUtil_CalcUnitAP((eInfo->dwTo & 0xFFFF) >> 8, eInfo->dwTo & 0xFF, 1, (eInfo->dwTo >> 16) & 0x7FFF);
                TaUtil_CalcUnitDP((eInfo->dwTo & 0xFFFF) >> 8, eInfo->dwTo & 0xFF, 1, (eInfo->dwTo >> 16) & 0x7FFF);
            } else {
                TaUtil_CalcUnitAP((eInfo->dwTo & 0xFFFF) >> 8, eInfo->dwTo & 0xFF, 0, (eInfo->dwTo >> 16) & 0x7FFF);
                TaUtil_CalcUnitDP((eInfo->dwTo & 0xFFFF) >> 8, eInfo->dwTo & 0xFF, 0, (eInfo->dwTo >> 16) & 0x7FFF);
            }
        }
        if (SzDuel_GetWindowDisp() != 0) {
            SzDuel_SetWindowDraw(1);
        }
        SzDuel_CloseMsgPopup();
        return 0;
    }
    return 1;
}

typedef struct {
    u32 unknown;
    u16 first;
    u16 padding6;
    u16 second;
    u16 paddingA;
    u32 flags;
} Source_002755D0;

typedef struct {
    u16 first;
    u16 second;
    u8 padding[0xFE];
    u16 counter;
} State_002755D0;

typedef struct {
    s32 id;
    s32 x;
    s32 y;
    s32 z;
} Params_002755D0;


/* One frame of battle effect script 002. */
static inline s32 update_002755D0(void *arg0, void *arg1, void *params_arg, s32 arg2) {
    State_002755D0 *state = arg1;
    Source_002755D0 *source = arg0;
    Params_002755D0 *values = params_arg;
    s32 card;
    s32 position;
    u16 counter;

    if (source == NULL || state == NULL || values == NULL) {
        SzDuel_CloseMsgPopup();
        return 0;
    }
    if (arg2 >= 0) {
        InitEffectTemp(state);
        if ((source->flags & 1) == 1) {
            state->first = source->second;
            state->second = source->first;
        } else {
            state->first = source->first;
            state->second = source->second;
        }
        if ((source->flags >> 1) != 0) {
            card = Ta_GetCurrentSide((s32) state->second >> 8, state->second & 0xFF);
            position = SzDuel_GetUnitLoc(card, 0);
            Ta_SetRangeVisual(position & 0xFF, position >> 8, 0,
                         Ta_IsLDAbl(9, card), 1, 1, 11);
        }
        Ta_UnitFade((s32) state->first >> 8, state->first & 0xFF, -1, 1, 3);
        return 1;
    }
    counter = state->counter;
    state->counter = counter + 1;
    if ((s32) counter < 16) {
        return 1;
    }
    Ta_DelUnit((s32) state->first >> 8, state->first & 0xFF);
    SzDuel_CloseMsgPopup();
    return 0;
}

/* Clears battle effect script 002's work area. */
static inline void init_params_002755D0(void *params_arg) {
    Params_002755D0 *values = params_arg;

    values->id = 999;
    values->x = 0;
    values->y = 0;
    values->z = 0;
}

/* Effect script BTL_002, step `ID`: its camera, fades and effect module. */
s32 Ta_Eff_BTL_002(void *eInfo, void *Temp, s32 ID) {
    Params_002755D0 values;
    Params_002755D0 *params = &values;

    init_params_002755D0(params);
    return update_002755D0(eInfo, Temp, params, ID);
}

typedef struct State_00275740 {
    u8 pad0[4];
    u16 phase;
    u8 handle;
    u8 pad7[0xFB];
    u16 timer;
} State_00275740;

typedef struct Request_00275740 {
    s32 command;
    s32 value;
    u32 cell;
    s32 flag;
} Request_00275740;


/* Effect script 070, step `ID`: its camera, fades and effect module; it destroys units, turns cards face up. */
s32 Ta_Eff_070(u32 *eInfo, void *Temp, s32 ID) {
    extern s32 SzDuel_GetUnitOpenRate();
    extern s32 SzDuel_GetUnitCardNo();
    Request_00275740 data;
    Request_00275740 *request = &data;
    State_00275740 *state = Temp;
    u32 cell;

    data.command = 999;
    data.value = 0;
    data.cell = 0;
    data.flag = 0;
    SzDuel_SetWindowDraw(0);
    if (ID >= 0) {
        InitEffectTemp(Temp);
        TaEffect_LoadModule(Temp, 0x259);
        TaEffect_LoadModule(Temp, 0x25A);
        cell = eInfo[1];
        TaUtil_DoOpen(cell >> 8, cell & 0xFF, 1);
        TaView_ReqFocusCamera(0, eInfo[1], 100, 180);
        return 1;
    }

    switch (state->phase) {
    case 0:
        if (TaEffect_IsLoadModule(Temp) == 1) {
            cell = eInfo[1];
            if (SzDuel_GetUnitOpenRate(cell >> 8, cell & 0xFF) == 0xFF) {
                SzDuel_OpenMsgPopup(0, -120, 80, 0x103);
                request->command = 0x25A;
                request->value = 0;
                request->cell = eInfo[1];
                request->flag = 0;
                state->handle = Ta_Do_Effect((s32 *)request, Temp);
                state->phase++;
            }
        }
        break;
    case 1:
        if (SzEffect_IsUse(state->handle) == 1) {
            return 1;
        }
        cell = eInfo[1];
        SzDuel_SetUnitStatus(cell >> 8, cell & 0xFF, 0, 1);
        cell = eInfo[1];
        SzDuel_OpenMsgPopup(0, -120, 80, SzDuel_GetMsgName(SzDuel_GetUnitCardNo(cell >> 8, cell & 0xFF)));
        request->command = 0x259;
        request->value = 0;
        request->cell = eInfo[1];
        request->flag = 1;
        state->handle = Ta_Do_Effect((s32 *)request, Temp);
        state->phase++;
        break;
    case 2:
        if (SzEffect_IsUse(state->handle) == 1) {
            return 1;
        }
        cell = eInfo[1];
        Ta_DelUnit(cell >> 8, cell & 0xFF);
        state->phase++;
        SzDuel_CloseMsgPopup();
        TaView_RestoreOriginalView(Temp, 16);
        break;
    default:
        if (state->timer++ > 16) {
            if (SzDuel_GetWindowDisp() != 0) {
                SzDuel_SetWindowDraw(1);
            }
            SzDuel_CloseMsgPopup();
            return 0;
        }
        break;
    }
    return 1;
}

typedef struct {
    u32 unused;
    u32 source;
    u32 destination;
    s32 flag;
} Data_002759D0;

typedef struct {
    u8 unused[4];
    u16 phase;
    u8 id;
    u8 padding[0xFB];
    u16 timer;
} State_002759D0;

typedef struct {
    s32 code;
    s32 unused;
    s32 position;
    s32 flags;
} Command_002759D0;


/* Effect script 071, step `ID`: its camera, fades and effect module; it curses units, turns cards face up. */
s32 Ta_Eff_071(void *eInfo, void *Temp, s32 ID) {
    Command_002759D0 storage;
    Command_002759D0 *command = &storage;
    Data_002759D0 *data = eInfo;
    State_002759D0 *state = Temp;
    u32 position;
    u16 timer;
    extern s32 SzDuel_TrimUnitDir2();
    extern s32 SzDuel_GetUnitOpenRate();
    extern s32 SzDuel_GetUnitCardNo();

    command->code = 0x3E7;
    command->unused = 0;
    command->position = 0;
    command->flags = 0;
    SzDuel_SetWindowDraw(0);
    if (ID >= 0) {
        InitEffectTemp(Temp);
        position = data->source;
        TaUtil_DoOpen(position >> 8, position & 0xFF, 1);
        TaView_ReqFocusCamera(0, data->source, 0x64, 0xB4);
        TaEffect_LoadModule(Temp, 0x25A);
        if (data->flag != 0) {
            TaEffect_LoadModule(Temp, 0x1F4);
        } else {
            TaEffect_LoadModule(Temp, 0x201);
        }
        return 1;
    }
    switch (state->phase) {
    case 0:
        position = data->source;
        if (SzDuel_GetUnitOpenRate(position >> 8, position & 0xFF) == 0xFF) {
            if (TaEffect_IsLoadModule(Temp) == 1) {
                SzDuel_OpenMsgPopup(0, -0x78, 0x50, 0x103);
                command->code = 0x25A;
                command->unused = 0;
                command->position = data->source;
                command->flags = 0;
                state->id = Ta_Do_Effect((s32 *)command, Temp);
                state->phase++;
            }
        }
        break;
    case 1:
        if (SzEffect_IsUse(state->id) == 1) {
            return 1;
        }
        position = data->source;
        SzDuel_SetUnitStatus(position >> 8, position & 0xFF, 0, 1);
        TaView_ReqFocusCamera(0, data->destination, 0x64, 0xB4);
        if (data->flag != 0) {
            command->code = 0x1F4;
            command->unused = 0;
            command->position = data->destination;
            command->flags = 0;
        } else {
            command->code = 0x201;
            command->unused = 0;
            command->position = data->destination;
            command->flags = 0;
        }
        position = data->source;
        SzDuel_OpenMsgPopup(0, -0x78, 0x50,
            SzDuel_GetMsgName(SzDuel_GetUnitCardNo(position >> 8, position & 0xFF)));
        state->id = Ta_Do_Effect((s32 *)command, Temp);
        state->phase++;
        return 1;
    case 2:
        if (SzEffect_IsUse(state->id) == 1) {
            return 1;
        }
        if (data->flag != 0) {
            position = data->destination;
            Ta_SetUnitCurseRest(position >> 8, position & 0xFF, 0xFF);
        } else {
            position = data->destination;
            SzDuel_SetUnitStatus(position >> 8, position & 0xFF, 3, 0);
            position = data->destination;
            SzDuel_SetUnitStatus(position >> 8, position & 0xFF, 5, 0);
        }
        state->phase++;
        SzDuel_CloseMsgPopup();
        TaView_RestoreOriginalView(Temp, 0x10);
        break;
    default:
        timer = state->timer;
        state->timer = timer + 1;
        if (timer > 0x10) {
            if (SzDuel_GetWindowDisp() != 0) {
                SzDuel_SetWindowDraw(1);
            }
            SzDuel_CloseMsgPopup();
            return 0;
        }
        break;
    }
    return 1;
}

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

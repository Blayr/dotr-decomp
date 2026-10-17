#include "common.h"

/* The level of the card reincarnation gives for a card of level `SourceCost`: usually up to 10 below it, now and
   then 1..10 above it (more often the higher the best leader rank of side `nSide`'s decks 0 and 1). */
s32 Ta_GetRecycleRequestLvl(s32 nSide, s32 SourceCost) {
    extern s32 SzData_GetRank();
    s32 i;
    s32 id;
    s32 max;

    max = 0;
    for (i = 0; i < 2; i++) {
        if ((id = SzData_GetLeader(nSide, i)) != 999) {
            if (max < SzData_GetRank(nSide, id)) {
                max = SzData_GetRank(nSide, id);
            }
        }
    }
    if ((max - 1) * 2 + func_0019A5C8() % 100 >= 90) {
        return SourceCost + (func_0019A5C8() % 10 + 1);
    }
    return SourceCost - func_0019A5C8() % 12 + 1;
}

/* Effect `nNo` of unit (nSide, nID), or 0. */
void *Ta_GetUnitEffect(s32 nSide, s32 nID, s32 nNo) {
    void *var_v0;

    if (SzDuel_GetUnit(nSide, nID) == 0) {
        return NULL;
    }
    var_v0 = SzDuel_GetUnitEffect(nSide, nID, nNo);
    if (var_v0 == NULL) {
        return NULL;
    }
    if ((((s32 *)var_v0)[0] == -1) && (((s32 *)var_v0)[1] == -1)) {
        var_v0 = NULL;
    }
    return var_v0;
}

/* Whether unit (nSide, nID) is an extra (fusion or ritual) monster. */
s32 TaUtil_IsExMonster(s32 nSide, s32 nID) {
    s32 var_s0;

    if ((SzDuel_GetUnitKind(nSide, nID) >> 5) != 0) {
        return -1;
    }
    var_s0 = 0;
    do {
        if (Ta_GetUnitEffect(nSide, nID, var_s0) != NULL) {
            return 1;
        }
        var_s0++;
    } while (var_s0 <= 4);
    return 0;
}

/* `Expr` kept to cap `CapID`: 0 and 1 are lower bounds (at least `CapID`); 6, 7, 500, 1500 and 9999 upper bounds. */
s32 GetCap(s32 CapID, s32 Expr) {
    switch (CapID) {
    case 0:
    case 1:
        if (Expr < CapID) {
            return CapID;
        }
        return Expr;
    case 7:
    case 6:
    case 0x270F:
    case 0x1F4:
    case 0x5DC:
        return Expr >= CapID ? CapID : Expr;
    default:
        return 0;
    }
}

/* `Expr` kept within the attack/defence range (0..9999). */
s32 GetParCap(s32 Expr) {
    if (Expr < 0) {
        return 0;
    }
    Expr = Expr > 9999 ? 9999 : Expr;
    return Expr;
}

/* Whether a unit (record `pVarInfo`) is a leader. */
s32 TaUtil_IsVarInfoLeader(void *pVarInfo) {
    u8 state;

    if (*((u8 *)pVarInfo + 0x45) == 0) {
        state = *((u8 *)pVarInfo + 0x44);
        if (state == 0 || state == 1) {
            return 1;
        }
    }
    return 0;
}

/* How many cards of kind `nType` side `nSide`'s graveyard holds. */
s32 TaUtil_GetGraveCardNum(s32 nSide, s32 nType) {
    extern s32 SzDuel_GetGraveCount(s32);
    s32 i;
    s32 count;

    for (i = 0, count = 0; i < SzDuel_GetGraveCount(nSide); i++) {
        if (nType == (TaHand_GetCardKind(SzDuel_InqGrave(nSide, i)) >> 5)) {
            count += 1;
        }
    }
    return count;
}

/* Unit (nSide, nID)'s attack on square (nX, nZ), with the field bonus, kept in range. */
s32 TaUtil_GetUnitAP(s32 nSide, s32 nID, s32 nX, s32 nZ) {
    return GetParCap(SzDuel_GetUnitAP(nSide, nID, 0) +
                         Ta_GetParamOfs(SzDuel_GetUnit(nSide, nID), nX, nZ, 1));
}

/* A unit's (record `pVarInfo`) attack on square (nX, nZ), with the field bonus, kept in range. */
s32 TaUtil_GetUnitAP2(s32 pVarInfo, s32 nX, s32 nZ) {
    s32 temp_s0;

    temp_s0 = SzDuel_GetUnitAP2((void *)pVarInfo, 0);
    return GetParCap(temp_s0 + Ta_GetParamOfs(pVarInfo, nX, nZ, 1));
}

/* Unit (nSide, nID)'s attack on square (nX, nZ), with the field bonus. */
s32 TaUtil_GetUnitAP3(s32 nSide, s32 nID, s32 nX, s32 nZ) {
    s32 temp_s0;
    s32 result;

    temp_s0 = Ta_GetParamOfs(SzDuel_GetUnit(nSide, nID), nX, nZ, 1);
    result = SzDuel_GetUnitAP(nSide, nID, 0);
    result += temp_s0;
    return result;
}

/* Unit (nSide, nID)'s defence on square (nX, nZ), with the field bonus, kept in range. */
s32 TaUtil_GetUnitDP(s32 nSide, s32 nID, s32 nX, s32 nZ) {
    s32 value;
    s32 base;

    value = Ta_GetParamOfs(SzDuel_GetUnit(nSide, nID), nX, nZ, 0);
    base = SzDuel_GetUnitDP(nSide, nID, 0);
    return GetParCap(base + value);
}

/* A unit's (record `pVarInfo`) defence on square (nX, nZ), with the field bonus, kept in range. */
void TaUtil_GetUnitDP2(s32 pVarInfo, s32 nX, s32 nZ) {
    s32 temp_s0;

    temp_s0 = SzDuel_GetUnitDP2((void *)pVarInfo, 0);
    GetParCap(temp_s0 + Ta_GetParamOfs(pVarInfo, nX, nZ, 0));
}

/* Unit (nSide, nID)'s defence on square (nX, nZ), with the field bonus. */
s32 TaUtil_GetUnitDP3(s32 nSide, s32 nID, s32 nX, s32 nZ) {
    s32 temp_s0;
    s32 result;

    temp_s0 = Ta_GetParamOfs(SzDuel_GetUnit(nSide, nID), nX, nZ, 0);
    result = SzDuel_GetUnitDP(nSide, nID, 0);
    return result + temp_s0;
}

/* Changes unit (nSide, nID)'s attack by `Arg` in mode `nMode`, kept in range. */
s32 TaUtil_CalcUnitAP(s32 nSide, s32 nID, s32 nMode, s32 Arg) {
    switch (nMode) {
    case 0:
        if (Arg + SzDuel_GetUnitAP(nSide, nID, 0) > 9999) {
            SzDuel_CalcUnitAP(nSide, nID, 4, 9999 - SzDuel_GetUnitAP(nSide, nID, 1));
        } else {
            SzDuel_CalcUnitAP(nSide, nID, 0, Arg);
        }
        break;
    case 1:
        if (SzDuel_GetUnitAP(nSide, nID, 0) - Arg < 0) {
            SzDuel_CalcUnitAP(nSide, nID, 4, -SzDuel_GetUnitAP(nSide, nID, 1));
        } else {
            SzDuel_CalcUnitAP(nSide, nID, 1, Arg);
        }
        break;
    case 2:
        if (Arg * SzDuel_GetUnitAP(nSide, nID, 0) > 9999) {
            SzDuel_CalcUnitAP(nSide, nID, 4, 9999 - SzDuel_GetUnitAP(nSide, nID, 1));
        } else {
            SzDuel_CalcUnitAP(nSide, nID, 2, Arg);
        }
        break;
    case 3:
        if (Arg == 0) {
            return -1;
        }
        SzDuel_CalcUnitAP(nSide, nID, 3, Arg);
        break;
    case 4:
        SzDuel_CalcUnitAP(nSide, nID, 4, Arg);
        break;
    }
    return 1;
}

/* Changes unit (nSide, nID)'s defence by `Arg` in mode `nMode`, kept in range. */
s32 TaUtil_CalcUnitDP(s32 nSide, s32 nID, s32 nMode, s32 Arg) {
    switch (nMode) {
    case 0:
        if (Arg + SzDuel_GetUnitDP(nSide, nID, 0) > 9999) {
            SzDuel_CalcUnitDP(nSide, nID, 4, 9999 - SzDuel_GetUnitDP(nSide, nID, 1));
        } else {
            SzDuel_CalcUnitDP(nSide, nID, 0, Arg);
        }
        break;
    case 1:
        if (SzDuel_GetUnitDP(nSide, nID, 0) - Arg < 0) {
            SzDuel_CalcUnitDP(nSide, nID, 4, -SzDuel_GetUnitDP(nSide, nID, 1));
        } else {
            SzDuel_CalcUnitDP(nSide, nID, 1, Arg);
        }
        break;
    case 2:
        if (Arg * SzDuel_GetUnitDP(nSide, nID, 0) > 9999) {
            SzDuel_CalcUnitDP(nSide, nID, 4, 9999 - SzDuel_GetUnitDP(nSide, nID, 1));
        } else {
            SzDuel_CalcUnitDP(nSide, nID, 2, Arg);
        }
        break;
    case 3:
        if (Arg == 0) {
            return -1;
        }
        SzDuel_CalcUnitDP(nSide, nID, 3, Arg);
        break;
    case 4:
        SzDuel_CalcUnitDP(nSide, nID, 4, Arg);
        break;
    }
    return 1;
}

/* From the dotr-decomp CC0 bundle (commit 88c32bb2), chatC/imp/conv.py. */

struct jp_9a20 {
    unsigned char bCardMax;
    unsigned char bMode;
    unsigned char _pad[6];
    unsigned short wReelBuf[3][21];
    unsigned short wLine[5];
};
struct jp_8d5b_251060 {
    unsigned char bKind;
    unsigned char bKindOfs;
    unsigned char bAttr : 4;
    unsigned char bLevel : 4;
    unsigned char bDeckCost;
    unsigned short wEffIdx;
    unsigned short wEffNo;
    unsigned short wAP : 13;
    unsigned short fPermanent : 1;
    unsigned short fGetPasswd : 1;
    unsigned short fGetRecycle : 1;
    unsigned short wDP : 13;
    unsigned short fGetSlot : 1;
    unsigned short fGetFever : 1;
    unsigned short fAlternate : 1;
    unsigned char abPasswd[8];
};
extern int func_001DEE50_b(int index);
extern struct jp_8d5b_251060 *func_001DD0E0_251060(int id);
extern int func_001DE740_b(int index);
extern int func_00215D30_b(int side, int id);

/* Sets up the slot machine's reels for side `nSide` from its deck and graveyard into `pSlotOrder_v`. */
int TaSlot_SetSlotInitialDat(int nSide, void *pSlotOrder_v)
{
    struct jp_9a20 * pSlotOrder = pSlotOrder_v;
    unsigned short wGraveLst[120];
    struct jp_8d5b_251060 *pConstInfo;
    int bRank;
    int bKind;
    int nCardNo;
    int Count;
    int i;

    if (pSlotOrder == 0) {
        return -1;
    }
    for (i = 0; i < 120; i++) {
        wGraveLst[i] = 999;
    }
    SzDuel_AddGrave(nSide, SzData_GetLeader(nSide, SzData_GetCurrentDeck(nSide)));
    Count = func_001DEE50_b(nSide);
    if (Count <= 0) {
        return 0;
    }
    for (i = 0; i < Count; i++) {
        pConstInfo = func_001DD0E0_251060(SzDuel_InqGrave(nSide, i));
        if (!pConstInfo->fGetSlot) {
            SzDuel_DelGrave(nSide, i);
        }
    }
    SzDuel_PackGrave(nSide);
    Count = func_001DEE50_b(nSide);
    if (Count <= 0) {
        return 0;
    }
    for (i = 0; i < Count; i++) {
        wGraveLst[i] = SzDuel_InqGrave(nSide, i);
    }
    pSlotOrder->bCardMax = TaSlot_SetReelData(Count, wGraveLst, pSlotOrder);
    pSlotOrder->bMode = 2;
    if (func_001DE740_b(nSide == 0 ? 1 : 0) & 0x80) {
        pSlotOrder->bMode = 0;
    }
    nCardNo = SzData_GetLeader(nSide == 0 ? 1 : 0, SzData_GetCurrentDeck(nSide == 0 ? 1 : 0));
    bKind = TaHand_GetCardKind(nCardNo) & 0x1F;
    bRank = func_00215D30_b(nSide == 0 ? 1 : 0, nCardNo);
    for (i = 0; i < 5; i++) {
        pSlotOrder->wLine[i] = 0xFFFE;
    }
    switch (bKind) {
    case 0:
    case 2:
    case 5:
    case 6:
    case 7:
    case 9:
    case 12:
    case 16:
    case 19:
    case 20:
        pSlotOrder->wLine[0] = 0xFFFE;
        for (i = 1; i < 5; i++) {
            pSlotOrder->wLine[i] = 0xFFFF;
        }
        break;
    default:
        if (bRank <= 0) {
            pSlotOrder->wLine[0] = 0xFFFF;
        }
        if (bRank < 4) {
            pSlotOrder->wLine[1] = 0xFFFF;
        }
        if (bRank < 7) {
            pSlotOrder->wLine[2] = 0xFFFF;
        }
        if (bRank < 10) {
            pSlotOrder->wLine[3] = 0xFFFF;
        }
        if (bRank < 11) {
            pSlotOrder->wLine[4] = 0xFFFF;
        }
        break;
    }
    return 1;
}

/* Fills a slot-machine reel with `count` cards from `src`. */
s32 TaSlot_SetReelData(s32 count, u16 *src, void *dst) {
    u16 buffer[120];
    s32 row;
    s32 i;
    s32 result;
    u16 *read;
    u16 *write;

    for (i = 0; i < 120; i++) {
        buffer[i] = 999;
    }
    result = 0;
    if (count < 16) {
        if (count < 9) {
            for (; count < 8; count++) {
                src[count] = 820;
            }
        }
        for (i = 0; src[i] != 999; i++) {
            result++;
        }
        i = 0;
        do {
            row = 0;
            read = src;
            write = dst;
            do {
                write[4] = *read;
                row++;
                read++;
                write++;
            } while (row < 21);
            i++;
            dst = (u8 *)dst + 42;
        } while (i < 3);
    } else {
        result = 16;
        for (i = 0; i < 3; i++) {
            for (row = 0; row < count; row++) {
                buffer[row] = src[row];
            }
            for (row = 0; row < 16; row++) {
                ((u16 *)dst)[row + 4] = buffer[row];
            }
            dst = (u8 *)dst + 42;
        }
    }
    return result;
}

/* From the dotr-decomp CC0 bundle (commit 88c32bb2), chatC/imp/conv.py. */

struct jp_8d5b {
    unsigned char bKind;
    unsigned char bKindOfs;
    unsigned char bAttr : 4;
    unsigned char bLevel : 4;
    unsigned char bDeckCost;
    unsigned short wEffIdx;
    unsigned short wEffNo;
    unsigned short wAP : 13;
    unsigned short fPermanent : 1;
    unsigned short fGetPasswd : 1;
    unsigned short fGetRecycle : 1;
    unsigned short wDP : 13;
    unsigned short fGetSlot : 1;
    unsigned short fGetFever : 1;
    unsigned short fAlternate : 1;
    unsigned char abPasswd[8];
};
struct DotrStateEntry20;
struct DotrStateEntry20 *func_001DD0E0_b(int id);

/* The slot machine's fever bonus for card `nCardNo`. */
int TaSlot_GetFeverGain(unsigned short nCardNo)
{
    int i;
    int Count;
    unsigned short wCardNo[854];
    struct jp_8d5b *pConstInfo;

    switch (nCardNo) {
    case 60: return 87;
    case 837: return 83;
    case 754: return 699;
    case 716: return 715;
    case 272: return 702;
    case 539: return 700;
    case 722: return 811;
    case 61: return 733;
    }
    for (i = 0, Count = 0; i < 854; i++) {
        if (i == 87) continue;
        if (i == 83) continue;
        if (i == 699) continue;
        if (i == 715) continue;
        if (i == 702) continue;
        if (i == 700) continue;
        if (i == 733) continue;
        if (i == 811) continue;
        pConstInfo = (struct jp_8d5b *)func_001DD0E0_b(i);
        if (pConstInfo != 0 && pConstInfo->fGetFever) {
            wCardNo[Count++] = i;
        }
    }
    if (Count > 0) {
        return wCardNo[func_0019A5C8() % Count];
    }
    return 999;
}

/* Turns unit (nSide, nID)'s card face up (`Flip`) with its open motion. */
void TaUtil_DoOpen(s32 nSide, s32 nID, s32 Flip) {
    extern s32 SzDuel_SetUnitCtlGoal();
    extern s32 SzDuel_GetUnitCtlRateC();
    extern s32 SzDuel_GetUnitCtlRateM();
    extern void SzDuel_SetUnitStatus(s32, s32, s32, s32);

    if (Flip == 1) {
        SzDuel_SetUnitCtlGoal(nSide, nID, 0x80);
        SzDuel_SetUnitCtlRateC(nSide, nID, 1, SzDuel_GetUnitCtlRateC(nSide, nID));
        SzDuel_SetUnitCtlRateM(nSide, nID, 1, SzDuel_GetUnitCtlRateM(nSide, nID));
        SzDuel_SetUnitStatus(nSide, nID, 2, 1);
        SzDuel_SetUnitStatus(nSide, nID, 4, 1);
        return;
    }
    SzDuel_SetUnitCtlGoalM(nSide, nID, 0);
    SzDuel_SetUnitCtlRateM(nSide, nID, -1, SzDuel_GetUnitCtlRateM(nSide, nID));
    SzDuel_SetUnitStatus(nSide, nID, 2, 0);
    SzDuel_SetUnitStatus(nSide, nID, 4, 0);
}

typedef struct {
    u32 flags;
    u32 value;
} Script_002517D0;

/* The effects set off when unit (nSide_2, nID_2) is destroyed by unit (nSide_1, nID_1) on (nX, nZ), into `out`
   (`fRemove` takes the unit off). */
s32 Ta_Manage_DestEfc(s32 nSide_1, s32 nID_1, s32 nSide_2, s32 nID_2, s32 nX, s32 nZ, s32 *out, s32 fRemove) {
    Script_002517D0 *temp_v0;
    s32 spA8;
    s32 spAC;
    s32 temp_fp;
    s32 temp_s0;
    s32 temp_s1;
    s32 temp_s1_5;
    s32 temp_s1_6;
    s32 temp_s1_7;
    s32 temp_s1_8;
    s32 temp_s1_9;
    s32 temp_s3;
    s32 temp_s3_2;
    s32 temp_s3_4;
    s32 temp_s3_5;
    s32 temp_s4;
    s32 var_s4;
    s32 temp_s5;
    s32 temp_s7;
    s32 temp_v0_10;
    s32 temp_v0_11;
    s32 temp_v0_12;
    s32 temp_v0_13;
    s32 temp_v0_14;
    s32 temp_v0_15;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 temp_v0_7;
    s32 temp_v0_8;
    s32 temp_v0_9;
    s32 temp_v1;
    s32 temp_v1_3;
    s32 temp_v1_4;
    s32 var_s3;
    s32 var_s5;
    s32 var_s5_2;
    s32 var_s6;
    s32 var_s6_2;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v0_4;
    s32 var_v0_5;
    s32 var_v0_6;
    s32 var_v0_7;
    u32 temp_a1;
    u32 temp_a2;
    u32 temp_s1_2;
    u32 temp_s1_3;
    u32 temp_s1_4;
    u32 temp_v1_2;

    extern s32 SzDuel_GetUnitCardNo();

    temp_fp = nX;
    spAC = nZ;
    temp_s7 = fRemove;
    if (SzDuel_GetUnit(nSide_1, nID_1) == 0) {
        return 0;
    }
    if ((temp_v0 = Ta_GetUnitEffect(nSide_1, nID_1, 4)) == NULL) {
        return 0;
    }
    temp_s1 = Ta_GetCurrentSide(nSide_1, nID_1);
    if (temp_s1 == Ta_GetCurrentSide(nSide_2, nID_2)) {
        return 0;
    }
    temp_s1_2 = temp_v0->flags;
    temp_a1 = temp_s1_2 >> 8;
    switch (temp_a1) {                              /* switch 1; irregular */
    case 0x2:                                       /* switch 1 */
        switch (*(u16 *)&temp_v0->value) {
        case 8:
            out[0] = 2;
            out[1] = (s32) ((spAC << 8) | temp_fp);
            out[2] = (s32) (temp_v0->value >> 0x10);
            out[3] = (s32) *(u16 *)&temp_v0->value;
            break;
        default:
            out[0] = 2;
            out[1] = (s32) ((spAC << 8) | temp_fp);
            out[2] = (s32) (temp_v0->value >> 0x10);
            out[3] = (s32) *(u16 *)&temp_v0->value;
            break;
        }
        return 1;
    case 0x13:                                      /* switch 1 */
        if ((temp_s1_2 & 0x3F) == 0x1A) {
            if (nSide_2 >= 0 && nID_2 > 0 && temp_s7 == 0) {
                var_v0_2 = ConvUnitIDtoFlagList(0U, nSide_2, nID_2);
            } else {
                return 0;
            }
        } else {
        spA8 = SzDuel_GetUnitLoc(nSide_1, nID_1);
        temp_fp = temp_v0->value >> 0x10;
        if (temp_fp == 0) {
            temp_s1_3 = temp_v0->flags;
            var_v0_2 = SearchUnitByRange(0, 0, Ta_GetCurrentSide(nSide_1, nID_1), (temp_s1_3 >> 6) & 3, temp_s1_3 & 0x3F, 0xE);
        } else {
            temp_s1_4 = temp_v0->flags;
            var_v0_2 = SearchUnitByRange(spA8 & 0xFF, spA8 >> 8, Ta_GetCurrentSide(nSide_1, nID_1), (temp_s1_4 >> 6) & 3, temp_s1_4 & 0x3F, temp_fp);
        }
        }
        var_v0_3 = ConvUnitIDtoFlagList_OFF((u32) var_v0_2, nSide_1, nID_1);
        if (temp_s7 != 0) {
            var_v0_3 = ConvUnitIDtoFlagList_OFF((u32) var_v0_3, nSide_2, nID_2);
        }
        if (var_v0_3 == 0) {
            return 0;
        }
        out[0] = 0x39;
        out[1] = 0;
        out[2] = var_v0_3;
        out[3] = (s32) *(u16 *)&temp_v0->value;
        return 1;
    case 0x17:                                      /* switch 1 */
        temp_fp = temp_s1_2 & 0x3F;
        if (temp_fp == 0x1A) {
            if (nSide_2 >= 0 && nID_2 > 0 && temp_s7 == 0) {
                var_v0 = ConvUnitIDtoFlagList(0U, nSide_2, nID_2);
            } else {
                return 0;
            }
        } else {
        temp_fp = temp_s1_2 & 0x3F;
        var_v0 = SearchUnitByRange(0, 0, Ta_GetCurrentSide(nSide_1, nID_1), (temp_s1_2 >> 6) & 3, temp_fp, 0xE);
        }
        if (temp_s7 != 0) {
            var_v0 = ConvUnitIDtoFlagList_OFF((u32) var_v0, nSide_2, nID_2);
        }
        out[0] = 0;
        out[1] = 0;
        out[2] = var_v0;
        out[3] = (s32) *(u16 *)&temp_v0->value;
        if (var_v0 == 0) {
            return 0;
        }
        return 0x401;
    case 0x24:                                      /* switch 1 */
        temp_v0_2 = ConvUnitIDtoFlagList(0U, nSide_1, nID_1);
        out[0] = 0x1E;
        out[1] = 0;
        out[2] = temp_v0_2;
        out[3] = Ta_GetCurrentSide(nSide_1, nID_1);
        return 1;
    case 0xD:                                       /* switch 1 */
        temp_a2 = temp_v0->value;
        temp_v1 = (temp_s1_2 >> 6) & 3;
        temp_s1_5 = ((temp_a2 >> 0x10) << 0x10) | (temp_a2 & 0xFFFF);
        switch (temp_v1) {                          /* switch 2; irregular */
        case 1:                                     /* switch 2 */
            out[0] = 8;
            out[1] = 0;
            out[2] = Ta_GetEOwnerSide(Ta_GetCurrentSide(nSide_1, nID_1), ((u32) temp_v0->flags >> 6) & 3);
            out[3] = temp_s1_5;
            return 1;
        case 2:                                     /* switch 2 */
            out[0] = 9;
            out[1] = SzDuel_GetUnitLoc(nSide_1, nID_1);
            out[2] = Ta_GetEOwnerSide(Ta_GetCurrentSide(nSide_1, nID_1), ((u32) temp_v0->flags >> 6) & 3);
            out[3] = temp_s1_5;
            return 1;
        default:                                    /* switch 2 */
            return 0;
        }
        break;
    case 0x14:                                      /* switch 1 */
        if ((temp_v0_3 = Ta_IsActiveTrapB((nSide_1 == 0) ? 1 : 0, 0x4C)) >= 0) {
            if (Ta_IsActiveTrapB(0, 0x2E) < 0) {
                out[0] = 0x66;
                out[1] = 1;
                out[2] = temp_v0_3;
                out[3] = 0;
                return 1;
            }
            if ((temp_v0_4 = Ta_GetSummonablePiece(nSide_1, 1)) >= 0) {
                temp_v0_5 = ConvUnitIDtoFlagList(0U, nSide_1, nID_1);
                out[0] = 0x1F;
                out[1] = (s32) ((nSide_1 << 8) | nID_1 | 0x10000);
                out[2] = temp_v0_5;
                out[3] = temp_v0_4;
                return 0x103;
            }
            return 0;
        }
        if ((temp_v0_6 = Ta_GetSummonablePiece(nSide_1, 1)) >= 0) {
            temp_v0_7 = ConvUnitIDtoFlagList(0U, nSide_1, nID_1);
            out[0] = 0x1F;
            out[1] = (s32) ((nSide_1 << 8) | nID_1 | 0x10000);
            out[2] = temp_v0_7;
            out[3] = temp_v0_6;
            return 0x101;
        }
        return 0;
    case 0x3E:                                      /* switch 1 */
        if ((temp_v0_8 = Ta_IsActiveTrapB((nSide_1 == 0) ? 1 : 0, 0x4C)) >= 0) {
            if (Ta_IsActiveTrapB(0, 0x2E) >= 0) {
                temp_s1_6 = Ta_GetCurrentSide(nSide_1, nID_1);
                temp_s3 = SzDuel_GetLP(nSide_1);
                if (Ta_GetLPRevByNaturalEffect(0x2C, (s32) *(u16 *)&temp_v0->value) < temp_s3 && Ta_GetSummonablePiece(temp_s1_6, 1) >= 0) {
                    temp_s5 = 5 - Ta_GetUnitNum(temp_s1_6, 4U);
                    temp_s3_2 = TaUtil_GetGraveCardNum(temp_s1_6, 0) + TaUtil_GetGraveCardNum((temp_s1_6 == 0) ? 1 : 0, 0);
                    var_s6 = 0;
                    var_s4 = 0;
                    do {
                        if (Ta_GetSummonablePieceWithOrder(temp_s1_6, var_s6, 1) >= 0) {
                            var_s4 += 1;
                        }
                        var_s6 += 1;
                    } while (var_s6 < 8);
                    if (temp_s5 <= 0 || temp_s3_2 == 0 || var_s4 == 0) {
                        return 0;
                    }
                    out[0] = 0x3A;
                    if (Ta_GetLPRevByNaturalEffect(0x2C, (s32) *(u16 *)&temp_v0->value) >= 0) {
                        var_v0_4 = Ta_GetLPRevByNaturalEffect(0x2C, (s32) *(u16 *)&temp_v0->value);
                    } else {
                        var_v0_4 = -Ta_GetLPRevByNaturalEffect(0x2C, (s32) *(u16 *)&temp_v0->value);
                    }
                    out[1] = var_v0_4;
                    out[2] = temp_s1_6;
                    temp_s5 = ((temp_s5 < temp_s3_2 ? temp_s5 : temp_s3_2) < var_s4)
                        ? (temp_s5 < temp_s3_2 ? temp_s5 : temp_s3_2) : var_s4;
                    out[3] = temp_s5;
                    return 3;
                }
                return 0;
            }
            out[0] = 0x66;
            out[1] = 1;
            out[2] = temp_v0_8;
            out[3] = 0;
            return 1;
        }
        temp_s1_7 = Ta_GetCurrentSide(nSide_1, nID_1);
        temp_s3_4 = SzDuel_GetLP(nSide_1);
        if (Ta_GetLPRevByNaturalEffect(0x2C, (s32) *(u16 *)&temp_v0->value) < temp_s3_4 && Ta_GetSummonablePiece(temp_s1_7, 1) >= 0) {
            temp_s3_5 = 5 - Ta_GetUnitNum(temp_s1_7, 4U);
            temp_s4 = TaUtil_GetGraveCardNum(temp_s1_7, 0) + TaUtil_GetGraveCardNum((temp_s1_7 == 0) ? 1 : 0, 0);
            var_s6_2 = 0;
            var_s5_2 = 0;
            do {
                if (Ta_GetSummonablePieceWithOrder(temp_s1_7, var_s6_2, 1) >= 0) {
                    var_s5_2 += 1;
                }
                var_s6_2 += 1;
            } while (var_s6_2 < 8);
            if (temp_s3_5 <= 0 || temp_s4 == 0 || var_s5_2 == 0) {
                return 0;
            }
            out[0] = 0x3A;
            out[1] = Ta_GetLPRevByNaturalEffect(0x2C, (s32) *(u16 *)&temp_v0->value);
            out[2] = temp_s1_7;
            temp_s3_5 = ((temp_s3_5 < temp_s4 ? temp_s3_5 : temp_s4) < var_s5_2)
                ? (temp_s3_5 < temp_s4 ? temp_s3_5 : temp_s4) : var_s5_2;
            out[3] = temp_s3_5;
            return 1;
        }
        return 0;
    case 0x26:                                      /* switch 1 */
        out[0] = 0x21;
        out[1] = 0;
        out[2] = Ta_GetCurrentSide(nSide_1, nID_1);
        out[3] = 0;
        return 1;
    case 0x41:                                      /* switch 1 */
        if ((u32) SzDuel_GetLP(nSide_1) > (temp_v0->value >> 0x10)) {
            temp_v0_9 = Ta_GetCurrentSide(nSide_1, nID_1);
            temp_v0_10 = ConvUnitIDtoFlagList_OFF(SearchUnitByRange(0, 0, temp_v0_9, ((u32) temp_v0->flags >> 6) & 3, temp_v0->flags & 0x3F, 0xE), nSide_1, nID_1);
            if (temp_v0_10 == 0) {
                return 0;
            }
            out[0] = 0x3B;
            out[1] = temp_v0_9;
            out[2] = temp_v0_10;
            out[3] = (s32) temp_v0->value;
            return 1;
        }
        return 0;
    case 0x38:                                      /* switch 1 */
        temp_s1_8 = Ta_GetCurrentSide(nSide_1, nID_1);
        temp_v1_2 = temp_v0->value >> 0x10;
        switch (temp_v1_2) {                        /* switch 3; irregular */
        case 31:                                    /* switch 3 */
            temp_v0_11 = Ta_GetSummonablePiece(temp_s1_8, 1);
            if (temp_v0_11 >= 0) {
                out[0] = 1;
                out[1] = temp_s1_8;
                out[2] = temp_v0_11;
                out[3] = (s32) temp_v0->value;
                return 1;
            }
            return 0;
        case 30:                                    /* switch 3 */
            temp_v0_12 = Ta_GetSummonablePiece((temp_s1_8 == 0) ? 1 : 0, 1);
            if (temp_v0_12 >= 0) {
                out[0] = 1;
                out[1] = temp_s1_8;
                out[2] = temp_v0_12;
                out[3] = (s32) temp_v0->value;
                return 1;
            }
            return 0;
        default:                                    /* switch 3 */
            return 0;
        }
        break;
    case 0x51:                                      /* switch 1 */
        temp_s1_9 = Ta_GetCurrentSide(nSide_1, nID_1);
        temp_v1_3 = (temp_v0->value >> 0x10) & 0xFF;
        switch (temp_v1_3) {                        /* switch 4; irregular */
        case 31:                                    /* switch 4 */
            temp_v0_13 = Ta_GetSummonablePiece(temp_s1_9, 1);
            if (temp_v0_13 >= 0) {
                out[0] = 1;
                out[1] = (s32) (temp_s1_9 | 0x10000);
                out[2] = temp_v0_13;
                out[3] = (s32) temp_v0->value;
                temp_v0->flags = -1U;
                temp_v0->value = -1U;
                return 1;
            }
            return 0;
        case 30:                                    /* switch 4 */
            temp_v0_14 = Ta_GetSummonablePiece((temp_s1_9 == 0) ? 1 : 0, 1);
            if (temp_v0_14 >= 0) {
                out[0] = 1;
                out[1] = (s32) (temp_s1_9 | 0x10000);
                out[2] = temp_v0_14;
                out[3] = (s32) temp_v0->value;
                temp_v0->flags = -1U;
                temp_v0->value = -1U;
                return 1;
            }
            return 0;
        default:                                    /* switch 4 */
            return 0;
        }
        break;
    case 0x1A:                                      /* switch 1 */
        out[0] = 0x41;
        out[1] = 0;
        var_v0_5 = Ta_GetCurrentSide(nSide_1, nID_1);
        if (var_v0_5 == 0) {
            var_v0_5 = 1;
        } else {
            var_v0_5 = 0;
        }
        out[2] = var_v0_5;
        out[3] = (s32) *(u16 *)&temp_v0->value;
        return 1;
    case 0x4:                                       /* switch 1 */
        temp_v1_4 = temp_s1_2 & 0x3F;
        switch (temp_v1_4) {                        /* switch 5; irregular */
        case 26:                                    /* switch 5 */
            if (nSide_2 >= 0 && nID_2 > 0 && temp_s7 == 0) {
                temp_v0_15 = ConvUnitIDtoFlagList(0U, nSide_2, nID_2);
                out[0] = 0x15;
                out[1] = 0;
                out[2] = temp_v0_15;
                out[3] = 0;
                return 0x201;
            }
            return 0;
        case 30:                                    /* switch 5 */
            temp_s0 = SearchUnitByRange(temp_fp, spAC, Ta_GetCurrentSide(nSide_1, nID_1), (temp_s1_2 >> 6) & 3, 30, temp_v0->value >> 16);
            out[0] = 0x15;
            out[1] = 0;
            out[2] = temp_s0;
            out[3] = 0;
            if (SzDuel_GetUnitCardNo(nSide_1, nID_1) == 0x269) {
                out[0] = 0x17;
            }
            out[1] = 0;
            out[2] = temp_s0;
            out[3] = 0;
            return (temp_s0 != 0) ? 1 : 0;
        case 31:                                    /* switch 5 */
            var_v0_6 = ConvUnitIDtoFlagList_OFF(SearchUnitByRange(temp_fp, spAC, Ta_GetCurrentSide(nSide_1, nID_1), (temp_s1_2 >> 6) & 3, 31, temp_v0->value >> 16), nSide_1, nID_1);
            if (temp_s7 != 0) {
                var_v0_6 = ConvUnitIDtoFlagList_OFF((u32) var_v0_6, nSide_2, nID_2);
            }
            out[0] = 0x15;
            out[1] = 0;
            out[2] = var_v0_6;
            out[3] = 0;
            if (SzDuel_GetUnitCardNo(nSide_1, nID_1) == 0x1FD || SzDuel_GetUnitCardNo(nSide_1, nID_1) == 0x1FA) {
                out[0] = 0x2E;
            }
            var_v0_7 = nSide_1 << 8;
            out[1] = (s32) (var_v0_7 | nID_1);
            out[2] = 0;
            out[3] = 1;
            return 0x201;
        default:                                    /* switch 5 */
            return 0;
        }
        break;
    default:                                        /* switch 1 */
        return 0;
    }
}

typedef struct Result_00252440 {
    s32 kind;
    s32 value;
    s32 pos;
    s32 extra;
    u8 flag0;
    u8 flag1;
} Result_00252440;

/* Opens (turns face up) the card on square (x, y) in `phase`: its magic, trap or effect runs, into `pDat`. */
s32 Ta_Open(s32 x, s32 y, void *pDat, s32 phase) {
    extern s32 SzDuel_GetUnitOpenRate();
    extern s32 Ta_Manage_ActEfc();
    extern s32 Ta_Do_Magic();
    extern s32 Ta_DelUnit();
    s32 type;
    u32 *info;
    s32 pos;
    s32 card;
    s32 other;
    u8 *tail;
    Result_00252440 *res;
    s32 found;
    s32 target;

    res = pDat;
    tail = &res->flag0;
    type = SzDuel_GetUnitKind(x, y) >> 5;
    res->kind = 0;
    res->value = 0;
    res->pos = 0;
    res->extra = 0;
    res->flag0 = 0;
    res->flag1 = 0;
    info = Ta_GetUnitEffect(x, y, 0);
    switch (phase) {
    case 0:
        if (type == 0) {
            if ((card = (s32)Ta_GetUnitEffect(x, y, 3)) != 0 && SzDuel_GetUnitStatus(x, y, 4) == 0 && SzDuel_GetUnitStatus(x, y, 2) != 0) {
                pos = SzDuel_GetUnitLoc(x, y);
                TaUtil_DoOpen(x, y, 1);
                return Ta_Manage_ActEfc(card, x, y, -1, -1, pos & 0xFF, pos >> 8, res, tail, 0) | 0x100;
            }
            return 0x100;
        }
        if (type != 1 && type != 5) {
            return 0x100;
        }
        if ((type == 1 || type == 5) && SzDuel_GetUnitStatus(x, y, 2) == 0) {
            return 0x100;
        }
        return (phase + 1) << 16;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
        found = Ta_SearchUncTypeNaturalEffectUser(0xE, 0);
        if (found >= 0) {
        switch (phase) {
        case 1:
            res->kind = 0x65;
            res->value = 0;
            res->pos = (x << 8) | y;
            res->extra = 0;
            return 0x20001;
        case 2:
            res->kind = 0x66;
            res->value = 0;
            res->pos = found;
            res->extra = 0;
            return 0x30001;
        case 3:
            Ta_DelUnit(x, y);
            return 0;
        }
        return 0;
        }
        found = Ta_SearchUncTypeNaturalEffectUser(0x4C, 0);
        if (found >= 0 && (*info >> 8) == 0x14) {
        switch (phase) {
        case 1:
            res->kind = 0x65;
            res->value = 0;
            res->pos = (x << 8) | y;
            res->extra = 0;
            return 0x20001;
        case 2:
            res->kind = 0x66;
            res->value = 0;
            res->pos = found;
            res->extra = 0;
            return 0x30001;
        case 3:
            Ta_DelUnit(x, y);
            return 0;
        }
        return 0;
        }
        found = Ta_SearchUncTypeNaturalEffectUser(0x11, 0);
        if (found >= 0 && (*info >> 8) == 0x32) {
        switch (phase) {
        case 1:
            res->kind = 0x65;
            res->value = 0;
            res->pos = (x << 8) | y;
            res->extra = 0;
            return 0x20001;
        case 2:
            res->kind = 0x66;
            res->value = 0;
            res->pos = found;
            res->extra = 0;
            return 0x30001;
        case 3:
            Ta_DelUnit(x, y);
            return 0;
        }
        return 0;
        }
        if ((target = Ta_IsActiveTrapB(Ta_GetCurrentSide(x, y), 0xE)) >= 0) {
            if ((other = Ta_IsActiveTrapB(0, 0x2E)) < 0) {
                switch (phase) {
                case 1:
                    return (phase + 1) << 16;
                case 2:
                    res->kind = 0x65;
                    res->value = 0;
                    res->pos = (x << 8) | y;
                    res->extra = 0;
                    return 0x30001;
                case 3:
                    TaUtil_DoOpen(target >> 8, target & 0xFF, 1);
                    return 0x40000;
                case 4:
                    if (SzDuel_GetUnitOpenRate(target >> 8, target & 0xFF) == 0xFF) {
                        res->kind = 0x33;
                        res->value = target;
                        res->pos = (x << 8) | y;
                        res->extra = 1;
                        return 1;
                    }
                    return 0x40000;
                }
                return 0;
            }
            switch (phase) {
            case 1:
                return (phase + 1) << 16;
            case 2:
                res->kind = 0x65;
                res->value = 0;
                res->pos = (x << 8) | y;
                res->extra = 0;
                return 0x30001;
            case 3:
                TaUtil_DoOpen(other >> 8, other & 0xFF, 1);
                return 0x40000;
            case 4:
                if (SzDuel_GetUnitOpenRate(other >> 8, other & 0xFF) == 0xFF) {
                    res->kind = 0x66;
                    res->value = 1;
                    res->pos = other;
                    res->extra = 0;
                    return 0x50001;
                }
                return 0x40000;
            case 5:
                res->kind = 0x65;
                res->value = 0;
                res->pos = (x << 8) | y;
                res->extra = 2;
                return 0x70001;
            }
            return 0;
        }
        if ((target = Ta_IsActiveTrapB(Ta_GetCurrentSide(x, y), 0x4C)) >= 0 && (*info >> 8) == 0x14) {
            if ((other = Ta_IsActiveTrapB(0, 0x2E)) < 0) {
                switch (phase) {
                case 1:
                    return (phase + 1) << 16;
                case 2:
                    res->kind = 0x65;
                    res->value = 0;
                    res->pos = (x << 8) | y;
                    res->extra = 0;
                    return 0x30001;
                case 3:
                    TaUtil_DoOpen(target >> 8, target & 0xFF, 1);
                    return 0x40000;
                default:
                    if (SzDuel_GetUnitOpenRate(target >> 8, target & 0xFF) == 0xFF) {
                        res->kind = 0x33;
                        res->value = target;
                        res->pos = (x << 8) | y;
                        res->extra = 0;
                        return 1;
                    }
                    return 0x40000;
                }
            }
            switch (phase) {
            case 1:
                return (phase + 1) << 16;
            case 2:
                res->kind = 0x65;
                res->value = 0;
                res->pos = (x << 8) | y;
                res->extra = 0;
                return 0x30001;
            case 3:
                TaUtil_DoOpen(target >> 8, target & 0xFF, 1);
                return 0x40000;
            case 4:
                if (SzDuel_GetUnitOpenRate(other >> 8, other & 0xFF) == 0xFF) {
                    res->kind = 0x66;
                    res->value = 1;
                    res->pos = other;
                    res->extra = 0;
                    return 0x50001;
                }
                return 0x40000;
            case 5:
                res->kind = 0x65;
                res->value = 0;
                res->pos = (x << 8) | y;
                res->extra = 2;
                return 0x70001;
            }
            return 0;
        }
        if ((target = Ta_IsActiveTrapB(Ta_GetCurrentSide(x, y), 0x11)) >= 0 && (*info >> 8) == 0x32) {
            if ((other = Ta_IsActiveTrapB(0, 0x2E)) < 0) {
                switch (phase) {
                case 1:
                    return (phase + 1) << 16;
                case 2:
                    res->kind = 0x65;
                    res->value = 0;
                    res->pos = (x << 8) | y;
                    res->extra = 0;
                    return 0x30001;
                case 3:
                    TaUtil_DoOpen(target >> 8, target & 0xFF, 1);
                    return 0x40000;
                default:
                    if (SzDuel_GetUnitOpenRate(target >> 8, target & 0xFF) == 0xFF) {
                        res->kind = 0x33;
                        res->value = target;
                        res->pos = (x << 8) | y;
                        res->extra = 0;
                        return 1;
                    }
                    return 0x40000;
                }
            }
            switch (phase) {
            case 1:
                return (phase + 1) << 16;
            case 2:
                res->kind = 0x65;
                res->value = 0;
                res->pos = (x << 8) | y;
                res->extra = 0;
                return 0x30001;
            case 3:
                TaUtil_DoOpen(other >> 8, other & 0xFF, 1);
                return 0x40000;
            case 4:
                if (SzDuel_GetUnitOpenRate(other >> 8, other & 0xFF) == 0xFF) {
                    res->kind = 0x66;
                    res->value = 1;
                    res->pos = other;
                    res->extra = 0;
                    return 0x50001;
                }
                return 0x40000;
            case 5:
                res->kind = 0x65;
                res->value = 0;
                res->pos = (x << 8) | y;
                res->extra = 2;
                return 0x70001;
            }
            return 0;
        }
        res->kind = 0x65;
        res->value = 0;
        res->pos = (x << 8) | y;
        res->extra = 1;
        return 0x70001;
    }
    return Ta_Do_Magic(x, y, res, tail, phase, info);
}

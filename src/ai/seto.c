/* Computer AI of Seto (duelist 1, duelistController01). */

#include "common.h"

#define MAX_001110D0(a, b) ((a) > (b) ? (a) : (b))
#define MIN_001110D0(a, b) ((a) < (b) ? (a) : (b))

/* The unit of side `nSide` controlled by the opponent that this duelist wants back. */
s32 TaLogicCom_Seto_GetRevoltObj(s32 nSide) {
    extern s32 SzDuel_GetUnitCurseRest(s32, s32);
    extern s32 SzDuel_GetUnitSpellRest(s32, s32);
    s32 pos;
    s32 x0;
    s32 y0;
    u16 *p;
    s32 x;
    s32 y;
    s32 bestPos;
    s32 i;
    s32 best;
    u32 obj;
    s32 score;
    s32 cur;
    s32 found;
    u16 list[22];

    pos = SzDuel_GetUnitLoc(nSide == 0 ? 1 : 0, 0);
    if (Ta_SearchUncTypeNaturalEffectUserNum(0x39) > 0) {
        return -1;
    }
    obj = Ta_RemoveObjFromFlagLst(SearchUnitByRange(0, 0, nSide, 2, 0x21, 0xE), nSide);
    p = list;
    for (i = 0; i < 22; i++) {
        p[i] = 0xFFFF;
    }
    TaLogic_GetUnitCtlLst(nSide == 0 ? 1 : 0, list, 0x34, 0);
    found = -1;
    bestPos = found;
    best = 1;
    i = 0;
    if (i < TaLogic_GetUnitCtlLstLen(list)) {
        x0 = pos >> 8;
        y0 = pos & 0xFF;
        do {
            cur = SzDuel_GetUnitLoc(*p >> 8, *p & 0xFF);
            x = cur >> 8;
            y = cur & 0xFF;
            if (MAX_001110D0(y0, y) - MIN_001110D0(y0, y) + (MAX_001110D0(x0, x) - MIN_001110D0(x0, x)) == 1) {
                if (SzDuel_GetUnitStatus(*p >> 8, *p & 0xFF, 1) == 0 &&
                    SzDuel_GetUnitCurseRest(*p >> 8, *p & 0xFF) == 0 &&
                    SzDuel_GetUnitSpellRest(*p >> 8, *p & 0xFF) == 0) {
                    if ((score = TaUtil_GetUnitAP(*p >> 8, *p & 0xFF, y, x)) >= best) {
                        bestPos = *p;
                        if (bestPos == Ta_GetUnitOwnerIDFromLstCount(obj, 0)) {
                            found = bestPos;
                        }
                        best = score;
                    }
                }
            }
            p++;
            i++;
        } while (i < TaLogic_GetUnitCtlLstLen(list));
    }
    if (bestPos < 0) {
        return -1;
    }
    return ((u16)bestPos << 16) | (u16)found;
}

/* Whether this duelist opens (turns face up) unit (nSide, nID) now: 0 no, 1 or 2 by its kind. */
s32 TaLogicCom_Seto_IsOpenUnit(s32 nSide, s32 nID) {
    s16 buffer[24];
    s32 mask;
    s32 count;
    s32 owner;
    u32 *effect;
    s32 card;
    s32 position;
    s32 unit;
    extern s32 SzDuel_GetUnitCardNo();
    extern s32 SzDuel_GetUnitCurseRest();
    extern s32 SzDuel_GetGraveCount();
    extern s32 SzData_GetRank();

    mask = 0;
    count = 0;
    card = SzDuel_GetUnitCardNo();
    position = SzDuel_GetUnitLoc(nSide, nID);
    owner = Ta_IsUnitControl(nSide, nID);
    effect = SzDuel_GetUnitEffect(nSide, nID, 0);
    TaUtil_GetUnitLst(owner, 2, buffer);
    if (SzDuel_GetUnitStatus(nSide, nID, 4) != 0) {
        return 0;
    }
    if (TaLogicCom_Seto_IsExzParts(card) == 1) {
        if (TaLogic_Seto_IsTactixExz(owner) == 1 && TaLogic_Seto_IsExzodia(owner) == 4) {
            return 1;
        }
    }
    switch (SzDuel_GetUnitKind(nSide, nID) >> 5) {
    case 5:
        if (TaLogic_GetActionReaction(nSide, nID, 0, 0, 6, 0) == 5) {
            return 2;
        }
        if (TaLogicCom_Seto_IsDoCerem(Ta_IsUnitControl(nSide, nID), card) == 1 &&
            SzDuel_GetField(position & 0xFF, position >> 8) != 9) {
            return 1;
        }
        break;
    case 1:
        if (TaLogic_GetActionReaction(nSide, nID, 0, 0, 6, 0) == 5) {
            return 2;
        }
        if (effect == NULL) {
            return 2;
        }
        switch (effect[0] >> 8) {
        case 0x17:
        case 0x49:
            if (TaLogicCom_Seto_IsUseObjEffect(owner, (effect[0] >> 6) & 3, effect[0] & 0x3F) == 1) {
                return 1;
            }
            break;
        case 0x18:
        {
            s32 index;
            mask = SearchUnitByRange(0, 0, owner, 2, 0x34, 0xE);
            for (index = 0; index < Ta_GetUnitNumFrom22bitFlagList(mask); index++) {
                unit = Ta_GetUnitOwnerIDFromLstCount(mask, index);
                if (SzDuel_GetUnitStatus(unit >> 8, unit & 0xFF, 4) == 1) {
                    count++;
                }
            }
            if (count > 5) {
                return 1;
            }
            break;
        }
        case 2:
            unit = TaLogic_GetLandChange(SzDuel_GetUnit(nSide, nID), position & 0xFF,
                                position >> 8, *((u8 *)effect + 4), 8, 2);
            if (unit >= 0 && unit == position) {
                return 1;
            }
            break;
        case 4:
            switch (effect[1] >> 16) {
            case 0x12:
                unit = TaLogicCom_Seto_GetUseXYRangeSpell(nSide, (s32 *)effect);
                if (unit >= 0 && ((position & 0xFF) == (unit & 0xFF) ||
                                  (position >> 8) == (unit >> 8))) {
                    return 1;
                }
                break;
            case 0x13:
            default:
                if (TaLogicCom_Seto_IsUseObjEffect(owner, (effect[0] >> 6) & 3, effect[0] & 0x3F) == 1) {
                    return 1;
                }
                break;
            }
            break;
        case 0xD:
            if (((effect[0] >> 6) & 3) == 1) {
                if ((effect[1] >> 16) == 4) {
                    if (SzDuel_GetLP(owner) <= 1200) {
                        return 1;
                    }
                    break;
                }
                return 1;
            }
            if ((effect[0] & 0x3F) == 0x32) {
                if (Ta_GetUnitNum(owner == 0 ? 1 : 0, 3) > 3) {
                    return 1;
                }
                break;
            }
            return 1;
        case 0x1F:
            if (card == 0x2DD && TaLogicCom_Seto_GetRevoltObj(owner) >= 0) {
                return 1;
            }
            break;
        case 0x20:
            mask = 0;
            do {
                if (SzDuel_GetUnitCurseRest(nSide, mask) == 0xFF) {
                    return 1;
                }
                mask++;
            } while (mask < 11);
            break;
        case 0x12:
            if (Ta_GetUnitNumFrom22bitFlagList(SearchUnitByRange(0, 0, owner, 1, effect[0] & 0x3F, 0xE)) > 2) {
                return 1;
            }
            break;
        case 0x21:
            {
                s32 targetPosition;
                s32 sourcePosition;
                s32 targetY;

                TaLogic_GetUnitCtlLst2(owner == 0 ? 1 : 0, (u16 *)buffer, 0x1D, 0, 0);
                unit = TaLogic_GetMaxApUnit((u16 *)buffer);
                nSide = unit >> 8;
                nID = unit & 0xFF;
                sourcePosition = SzDuel_GetUnitLoc(nSide, nID);
                TaLogic_GetUnitCtlLst(owner, (u16 *)buffer, 0x1D, 1);
                unit = TaLogic_GetMaxApUnit((u16 *)buffer);
                card = unit >> 8;
                targetY = unit & 0xFF;
                targetPosition = SzDuel_GetUnitLoc(card, targetY);
                TaUtil_GetUnitLst(owner, 1, buffer);
                owner = sourcePosition & 0xFF;
                count = sourcePosition >> 8;
                if (TaUtil_GetUnitAP(nSide, nID, owner, count) >= 3000) {
                    count = TaUtil_GetUnitAP(nSide, nID, owner, count);
                    if (TaUtil_GetUnitAP(card, targetY, targetPosition & 0xFF, targetPosition >> 8) < count) {
                        return 1;
                    }
                }
            }
            break;
        case 0x36:
            return 1;
        case 0x25:
            switch (effect[0] & 0x3F) {
            case 0x21:
                if (TaLogic_IsAttackedNow(nSide, nID, 0) == 1) {
                    return 1;
                }
                break;
            case 0x22:
                if (TaLogic_IsAttackedNow(owner, 0, 0) == 1) {
                    return 1;
                }
                break;
            case 0x34:
            default:
                if (TaLogic_IsAttackedNow(owner, 0, 0) == 1) {
                    return 1;
                }
                break;
            }
            break;
        case 0x26:
            if (SzDuel_InqHandPhase(owner) == 0) {
                return 1;
            }
            break;
        case 0x27:
            if (SzDuel_GetSummonPower(owner) < 4) {
                return 1;
            }
            break;
        case 0x28:
            if (TaLogic_IsAttackedNow(owner, 0, 0) == 1) {
                return 1;
            }
            break;
        }
        break;
    case 0:
        if (TaUtil_IsExMonster(nSide, nID) == 0) {
            return 2;
        }
        effect = Ta_GetUnitEffect(nSide, nID, 2);
        if (effect == NULL) {
            return 2;
        }
        switch (effect[0] >> 8) {
        case 0xC:
        case 0x34:
        case 0xD:
        case 0xE:
        case 0x22:
        case 0x3B:
        case 0x56:
        case 0x43:
        case 0xF:
            return 1;
        case 0xB:
        case 0x4E:
        case 0x12:
        case 0x4D:
        case 6:
            mask = SearchUnitByRange(0, 0, nSide, 1, effect[0] & 0x3F, 0xE);
            if ((u32)mask > 1) {
                return 1;
            }
            break;
        case 0x13:
        case 0x17:
            if (((effect[0] >> 6) & 1) && SearchUnitByRange(0, 0, nSide, 1, effect[0] & 0x3F, 0xE)) {
                return 2;
            }
            mask = TaLogic_RemoveHideUnit(SearchUnitByRange(0, 0, nSide, 2, effect[0] & 0x3F, 0xE));
            if ((u32)mask > 2) {
                return 1;
            }
            break;
        case 0x47:
        {
            s32 y;
            s32 x;
            s32 index;
            mask = SearchUnitByRange(0, 0, nSide, 2, 0x34, 0xE);
            for (index = 0; index < Ta_GetUnitNumFrom22bitFlagList(mask); index++) {
                unit = Ta_GetUnitOwnerIDFromLstCount(mask, index);
                x = unit >> 8;
                y = unit & 0xFF;
                if (SzDuel_GetUnitCurseRest(x, y) > 0 && SzDuel_GetUnitCurseRest(x, y) != 0xFF) {
                    return 1;
                }
            }
            break;
        }
        case 0x53:
        {
            s32 index;
            for (index = 0; index < SzDuel_GetGraveCount(nSide); index++) {
                if ((TaHand_GetCardKind(SzDuel_InqGrave(nSide, index)) >> 5) == 0) {
                    count++;
                }
            }
            for (index = 0; index < SzDuel_GetGraveCount(nSide == 0 ? 1 : 0); index++) {
                if ((TaHand_GetCardKind(SzDuel_InqGrave(nSide == 0 ? 1 : 0, index)) >> 5) == 0) {
                    count++;
                }
            }
            if (count > 5) {
                return 1;
            }
            break;
        }
        case 0x54:
            mask = SearchUnitByRange(0, 0, nSide, 3, 0x21, 0xE);
            unit = Ta_GetUnitOwnerIDFromLstCount(mask, 0);
            if (nSide == Ta_IsUnitControl(unit >> 8, unit & 0xFF) && unit != ((nSide << 8) | nID)) {
                return 1;
            }
            break;
        case 0x55:
        {
            s32 y;
            s32 x;
            s32 index;
            mask = SearchUnitByRange(0, 0, nSide, 1, 0x34, 0xE);
            for (index = 0; index < Ta_GetUnitNumFrom22bitFlagList(mask); index++) {
                unit = Ta_GetUnitOwnerIDFromLstCount(mask, index);
                x = unit >> 8;
                y = unit & 0xFF;
                if (SzDuel_GetUnitCurseRest(x, y) > 0 && SzDuel_GetUnitCurseRest(x, y) != 0xFF) {
                    return 1;
                }
            }
            break;
        }
        case 0x58:
            if (SzData_GetRank(nSide == 0 ? 1 : 0, SzDuel_GetUnitCardNo(nSide == 0 ? 1 : 0, 0)) >= 6) {
                return 1;
            }
            break;
        }
        effect = Ta_GetUnitEffect(nSide, nID, 3);
        if (effect == NULL) {
            return 2;
        }
        switch (effect[0] >> 8) {
        case 0x12:
            if ((effect[1] >> 16) == 0x16) {
                unit = SearchUnitByRange(0, 0, owner, 1, effect[0] & 0x3F, 0x16);
            } else {
                unit = SearchUnitByRange(0, 0, owner, 1, ((effect[1] >> 16) << 16) | (effect[0] & 0x3F), 0xE);
            }
            if (Ta_GetUnitNumFrom22bitFlagList(unit) > 2) {
                return 1;
            }
            break;
        case 0x33:
            if (Ta_GetUnitNumFrom22bitFlagList(SearchUnitByRange(0, 0, owner, 1, ((effect[1] >> 16) << 16) | (effect[0] & 0x3F), 0xE)) > 2) {
                return 1;
            }
            break;
        case 0x17:
            if ((effect[0] & 0x3F) == 0x1A) {
                return 2;
            }
            if (TaLogicCom_Seto_IsUseObjEffect(owner, (effect[0] >> 6) & 3, effect[0] & 0x3F) == 1) {
                return 1;
            }
            break;
        case 0xD:
            return 1;
        case 0x23:
            if (TaLogicCom_Seto_IsUseObjEffect(owner, (effect[0] >> 6) & 3, effect[0] & 0x3F) == 1) {
                return 1;
            }
            break;
        case 0x18:
        {
            s32 targets;
            s32 index;

            targets = SearchUnitByRange(0, 0, owner, 1, effect[0] & 0x3F, 0xE);
            for (index = 0; index < Ta_GetUnitNumFrom22bitFlagList(targets); index++) {
                unit = Ta_GetUnitOwnerIDFromLstCount(targets, index);
                if (SzDuel_GetUnitStatus(unit >> 8, unit & 0xFF, 4) == 1) {
                    count++;
                }
            }
            if (count > 2) {
                return 2;
            }
            {
                s32 unavailable;
                s32 others;
                s32 otherIndex;

                unavailable = 0;
                others = SearchUnitByRange(0, 0, owner, 2, effect[0] & 0x3F, 0xE);
                for (otherIndex = 0; otherIndex < Ta_GetUnitNumFrom22bitFlagList(others); otherIndex++) {
                    unit = Ta_GetUnitOwnerIDFromLstCount(others, otherIndex);
                    if (SzDuel_GetUnitStatus(unit >> 8, unit & 0xFF, 4) == 1) {
                        unavailable++;
                    }
                }
                if (unavailable > 5) {
                    return 1;
                }
            }
            break;
        }
        case 4:
        {
            s32 y;
            s32 x;
            s32 index;
            if ((effect[0] & 0x3F) == 0x1A) {
                return 2;
            }
            if ((effect[0] & 0x3F) == 0x30) {
                if (TaLogicCom_Seto_IsUseObjEffect(owner, (effect[0] >> 6) & 3, effect[0] & 0x3F) == 1) {
                    return 1;
                }
            } else {
                if ((effect[1] >> 16) != 0) {
                    unit = SzDuel_GetUnitLoc(nSide, nID);
                    mask = SearchUnitByRange(unit & 0xFF, unit >> 8, owner, (effect[0] >> 6) & 3,
                                        effect[0] & 0x3F, effect[1] >> 16);
                } else {
                    mask = SearchUnitByRange(0, 0, owner, (effect[0] >> 6) & 3, effect[0] & 0x3F, 0xE);
                }
            }
            for (index = 0; index < Ta_GetUnitNumFrom22bitFlagList(mask); index++) {
                unit = Ta_GetUnitOwnerIDFromLstCount(mask, index);
                x = unit >> 8;
                y = unit & 0xFF;
                if (owner == Ta_IsUnitControl(x, y)) {
                    return 2;
                }
                if (SzDuel_GetUnitStatus(x, y, 4) != 0) {
                    count++;
                }
            }
            if (count > 1) {
                return 1;
            }
            break;
        }
        case 0x1A:
            if (SzDuel_GetSummonPower(nSide) < 4) {
                return 1;
            }
            break;
        case 0x26:
            if (SzDuel_InqHandPhase(owner) == 0) {
                return 1;
            }
            break;
        case 0x1F:
            if (Ta_SearchUncTypeNaturalEffectUserNum(0x39) > 0) {
                return 2;
            }
            if ((effect[0] & 0x3F) == 0x1A) {
                return 2;
            }
            if (Ta_GetUnitNumFrom22bitFlagList(SearchUnitByRange(0, 0, owner, (effect[0] >> 6) & 3, effect[0] & 0x3F, 0xE)) > 2) {
                return 1;
            }
            break;
        case 0x3C:
            if (SearchUnitByRange(position & 0xFF, position >> 8, owner, 1,
                             ((u32)*((u16 *)effect + 2) << 16) | (effect[0] & 0x3F), 1) &&
                Ta_GetSummonablePiece(owner == 0 ? 1 : 0, 1) >= 0) {
                return 1;
            }
            break;
        case 0x46:
            if (TaLogic_IsAttackedNow(owner, 0, 0) == 1) {
                return 1;
            }
            break;
        case 0xC:
            return 1;
        case 0x57:
            if (SzDuel_GetHandCount(owner) == 0) {
                return 1;
            }
            break;
        }
        break;
    default:
        break;
    }
    return 2;
}

/* Whether using unit (nSide, nID)'s effect now hits enough targets (`sKey`). */
s32 TaLogicCom_Seto_IsUseObjEffect(s32 nSide, s32 nID, s32 sKey) {
    s32 best_other;
    s32 best_own;
    s32 list;
    s32 i;
    s32 card;
    s32 lo;
    s32 hi;
    s32 value;

    for (i = 0; i < 22; i++) {
    }
    best_own = -1;
    best_other = -1;
    list = SearchUnitByRange(0, 0, nSide, nID, sKey, 14);
    for (i = 0; i < Ta_GetUnitNumFrom22bitFlagList(list); i++) {
        card = Ta_GetUnitOwnerIDFromLstCount(list, i);
        hi = card >> 8;
        lo = card & 0xFF;
        if (nSide == Ta_IsUnitControl(hi, lo)) {
            value = TaUtil_GetUnitAP(hi, lo, SzDuel_GetUnitLoc(hi, lo) & 0xFF, SzDuel_GetUnitLoc(hi, lo) >> 8);
            if (best_own < value) {
                best_own = value;
            }
        } else {
            value = TaUtil_GetUnitAP(hi, lo, SzDuel_GetUnitLoc(hi, lo) & 0xFF, SzDuel_GetUnitLoc(hi, lo) >> 8);
            if (best_other < value) {
                best_other = value;
            }
        }
    }
    if (best_own < best_other && best_other > 3000) {
        return 1;
    }
    if (nID & 1) {
        if (Ta_GetUnitNumFrom22bitFlagList(SearchUnitByRange(0, 0, nSide, 1, sKey, 14)) > 0) {
            return 0;
        }
    }
    if (nID >> 1) {
        if (Ta_GetUnitNumFrom22bitFlagList(SearchUnitByRange(0, 0, nSide, 2, sKey, 14)) > 3) {
            return 1;
        }
    }
    return 0;
}

/* The square where side `nSide`'s range magic hits most, into `pLoc`. */
s32 TaLogicCom_Seto_GetUseXYRangeSpell(s32 nSide, s32 *pLoc) {
    u16 cells[0x16];
    s32 first;
    s32 second;
    s32 pos;
    s32 y;
    s32 i;
    s32 list;
    s32 x;
    u8 count;
    s32 cell;
    s32 col;
    s32 row;
    s32 j;

    for (j = 0; j < 0x16; j++) {
        cells[j] = 0xFFFF;
    }
    switch (*pLoc & 0x3F) {
    case 0x1D:
        TaLogic_GetUnitCtlLst2((nSide == 0) ? 1 : 0, cells, 0x1D, 0, 0);
        first = TaLogic_GetMaxApUnit(cells);
        for (j = 0; j < 0x16; j++) {
            cells[j] = 0xFFFF;
        }
        TaLogic_GetUnitCtlLst(nSide, cells, 0x1D, 1);
        second = TaLogic_GetMaxApUnit(cells);
        if (first >= 0 && second >= 0) {
            pos = SzDuel_GetUnitLoc(first >> 8, first & 0xFF);
            if (TaLogic_IsUnitWin(first, second, pos & 0xFF, pos >> 8) >= 0) {
                return pos;
            }
        }
        break;
    case 0x1E:
        for (x = 0; x < 7; x++) {
            for (y = 0; y < 7; y++) {
                count = 0;
                list = SearchUnitByRange(x, y, nSide, 1, 0x34, 0x12);
                for (i = 0; i < Ta_GetUnitNumFrom22bitFlagList(list); i++) {
                    cell = Ta_GetUnitOwnerIDFromLstCount(list, i);
                    row = cell >> 8;
                    col = cell & 0xFF;
                    if (SzDuel_GetUnitStatus(row, col, 4) == 0) {
                        count++;
                    } else if ((SzDuel_GetUnitKind(row, col) >> 5) != 0) {
                        count++;
                    }
                }
                if (count > 2) {
                    return (y << 8) | x;
                }
            }
        }
        break;
    }
    return -1;
}

typedef struct {
    s32 unk0;
    s32 value;
} Data_00112850;

/* Whether side `nSide` can play ritual card `nCardNo` now (it has the units to give up). */
s32 TaLogicCom_Seto_IsDoCerem(s32 nSide, s32 nCardNo) {
    extern u32 TaHand_GetCardAPDP();
    s32 state[4];
    s32 index;
    s32 mask;
    u32 limit;
    s32 low;
    s32 high;
    s32 encoded;
    s32 position;
    Data_00112850 *data;

    data = TaHand_GetCardEffect(nCardNo, 0);
    Ta_GetCeremSacrifice(state, data->value);
    limit = TaHand_GetCardAPDP(data->value) >> 16;
    if ((mask = Ta_GetSacrificeUnit(state, nSide)) < 0) {
        return 0;
    } else {
        for (index = 0; index < Ta_GetUnitNumFrom22bitFlagList(mask); index++) {
            encoded = Ta_GetUnitOwnerIDFromLstCount(mask, index);
            high = encoded >> 8;
            low = encoded & 0xFF;
            position = SzDuel_GetUnitLoc(high, low);
            if (TaUtil_GetUnitAP(high, low, position & 0xFF, position >> 8) >= limit) {
                return 0;
            }
        }
        return 1;
    }
}

/* Whether card `nCardNo` is an Exodia part. */
s32 TaLogicCom_Seto_IsExzParts(s32 nCardNo) {
    s32 result;

    result = (u32) (nCardNo - 0x36) < 4U ? 1 : 0;
    return result;
}

/* Whether side `nSide`'s deck plays the Exodia tactic. */
s32 TaLogic_Seto_IsTactixExz(s32 nSide) {
    extern s32 SzDuel_GetUnitCardNo();

    if (SzDuel_GetUnitCardNo(nSide, 0) == 0x3A) {
        if (SzData_CheckDeck(nSide, SzData_GetCurrentDeck(nSide), 0x36) >= 0 && SzData_CheckDeck(nSide, SzData_GetCurrentDeck(nSide), 0x37) >= 0 && SzData_CheckDeck(nSide, SzData_GetCurrentDeck(nSide), 0x38) >= 0 && SzData_CheckDeck(nSide, SzData_GetCurrentDeck(nSide), 0x39) >= 0) {
            return 1;
        }
    }
    return 0;
}

/* How many Exodia limbs side `nSide` has ready on its summon squares (0..4; 0 unless its leader is Exodia's
   head). found[] is not cleared before the count, as in the original. */
s32 TaLogic_Seto_IsExzodia(s32 nSide) {
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
    u8 pad0[0x1A1];
    u8 lvl : 4;      /* 0x1A1 */
    u8 pad1A1 : 4;
} Ai_00112B90;
#pragma conditional_move off

/* This duelist's move: picks the next unit to act, gives it a task and turns that into input `pInput`; returns 1
   when it set one. */
s32 TaLogic_Seto_GetMinimumTask(void *pCtl, void *pInput, s32 wCursorPos) {
    UnitTask *tasks = pCtl;
    Ai_00112B90 *ai = pCtl;
    s32 side;
    s32 found;
    s32 result;
    s32 index;

    side = SzDuel_GetTurnOwner();
    found = 0;
    ai->lvl = TaLogic001_IsActiveMode();
    if ((result = TaLogic_Seto_GetNextActiveUnit(tasks, side, ai->lvl, pInput)) < 0) {
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
    TaLogic_Seto_CommandUnit(&tasks[index], ai->lvl);
    switch ((tasks[index].mission >> 8) & 0xFF) {
    case TASK_RUN:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            TaLogic_Seto_GetMinimumTask_RunMission(&tasks[index], side, pInput, 1);
            found = 1;
        }
        break;
    case TASK_ATTACK:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            if (TaLogic_Seto_GetMinimumTask_AtkMission(&tasks[index], side, pInput, 1) < 0) {
                TaLogic_InitRogicControl(&tasks[index], 1);
                return 1;
            }
            found = 1;
        }
        break;
    case TASK_SUMMON:
        if (TaLogic_Seto_GetMinimumTask_Summon(tasks[index].ownerId, side, pInput) < 0) {
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
            TaLogic_Seto_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 1, 0);
            found = 1;
        }
        break;
    case TASK_CONFIRMUNIT:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            TaLogic_Seto_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 1, 1);
            found = 1;
        }
        break;
    case TASK_ENCHANT:
        TaLogic_GetMinimumTask_EncMission(&tasks[index], side, pInput, 1, 0, TaLogic_Seto_GetWarnHideLvl(side), 5, 1);
        found = 1;
        break;
    case TASK_TRAP:
        TaLogic_Seto_GetMinimumTask_TrapMission(&tasks[index], side, pInput, 1);
        found = 1;
        break;
    case TASK_REVIVE:
        TaLogic_Seto_GetMinimumTask_ReviveMission(&tasks[index], side, pInput, 1);
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
            TaLogic_Seto_GetMinimumTask_RunMission(&tasks[index], side, pInput, 0);
            found = 1;
        }
        break;
    case 2:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            if (TaLogic_Seto_GetMinimumTask_AtkMission(&tasks[index], side, pInput, 0) < 0) {
                TaLogic_Seto_GetMinimumTask_RunMission(&tasks[index], side, pInput, 0);
            }
            found = 1;
        }
        break;
    case 10:
        if (TaLogic_Seto_GetMinimumTask_Summon(tasks[index].ownerId, side, pInput) < 0) {
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
            TaLogic_Seto_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 0, 0);
            found = 1;
        }
        break;
    case 3:
        if (SzDuel_GetUnitStatus(tasks[index].ownerId >> 8, tasks[index].ownerId & 0xFF, 0) == 0) {
            TaLogic_Seto_GetMinimumTask_MoveMission(&tasks[index], side, pInput, 0, 1);
            found = 1;
        }
        break;
    case 9:
        found = 1;
        TaLogic_GetMinimumTask_EncMission(&tasks[index], side, pInput, 0, 0, TaLogic_Seto_GetWarnHideLvl(side), 5, 1);
        break;
    case 11:
        found = 1;
        TaLogic_Seto_GetMinimumTask_TrapMission(&tasks[index], side, pInput, 0);
        break;
    case 12:
        found = 1;
        TaLogic_Seto_GetMinimumTask_ReviveMission(&tasks[index], side, pInput, 0);
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
    u16 card;       /* 0x0 */
    u8 pad2[2];
    s16 target;     /* 0x4 */
    u8 pad6[2];
    s32 f8;         /* 0x8 */
} Action_00113140;
#pragma conditional_move reset

/* Gives the unit of task `pTask` its order for this turn (attack, run, move, summon, guard). */
s32 TaLogic_Seto_CommandUnit(void *pCtl, s32 pTask) {
    extern s32 TaLogic001_CommandBtlUnit();
    extern s32 TaLogic001_CommandEfcMonster();
    extern s32 TaLogic001_CommandSpellUnit();
    Action_00113140 *act = pCtl;
    u16 card;
    s32 low;
    s32 controllingSide;
    s32 type;

    card = act->card;
    SzDuel_GetUnitLoc(card >> 8, card & 0xFF);
    card = act->card;
    controllingSide = Ta_IsUnitControl(card >> 8, card & 0xFF);
    card = act->card;
    if (SzDuel_GetUnit(card >> 8, card & 0xFF) != 0) {
        card = act->card;
        if (SzDuel_GetUnitStatus(card >> 8, card & 0xFF, 0) == 0) {
            card = act->card;
            if (card != 0xFFFF) {
                low = card & 0xFF;
                if (low == 0) {
                    if (act->f8 == -1) {
                        if (TaLogic_IsAttackedNow(card >> 8, low, 0) == 1) {
                            if (SzDuel_InqHandPhase(act->card >> 8) == 1) {
                                act->target = 0x50A;
                            } else {
                                act->target = 0x5FF;
                            }
                        } else {
                            if (SzDuel_InqHandPhase(act->card >> 8) == 1) {
                                act->target = 0xA06;
                                act->f8 = (act->f8 & 0xFFFF0000) | 0x101;
                            } else {
                                act->target = 0x6FF;
                                act->f8 = (act->f8 & 0xFFFF) | 0x01010000;
                            }
                        }
                    }
                } else {
                    type = SzDuel_GetUnitKind(card >> 8, low) >> 5;
                    switch (type) {
                    case 0:
                        card = act->card;
                        if (TaUtil_IsExMonster(card >> 8, card & 0xFF) == 1) {
                            TaLogic001_CommandEfcMonster(pCtl, pTask);
                        } else {
                            TaLogic001_CommandBtlUnit(pCtl, 1, pTask);
                        }
                        break;
                    case 2:
                        TaLogic_CommandEncUnit(pCtl, 5, 0, TaLogic_Seto_GetWarnHideLvl(controllingSide) & 0xFF);
                        break;
                    case 1:
                    case 3:
                        TaLogic001_CommandSpellUnit(pCtl, pTask);
                        break;
                    default:
                        act->target = 0x5FF;
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
s32 TaLogic_Seto_GetNextActiveUnit(u16 *pCtl, s32 nSide, s32 pInput, void *nMode) {
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
    TaLogic_Seto_CommandUnit(pCtl + idx * 8, pInput);
    if (((pCtl[idx * 8 + 2] >> 8) & 0xFF) == 10) {
        if (SzDuel_InqHandPhase(nSide) == 1 && TaLogic_Seto_GetMinimumTask_Summon(pos, nSide, nMode) >= 0) {
            return pos | 0x10000;
        }
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_GetUnitStatus(nSide, 0, 0) == 0) {
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_InqHandPhase(nSide) == 1 && TaLogic_Seto_GetMinimumTask_Summon(pos, nSide, nMode) >= 0) {
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

typedef struct Entry_00113760 {
    u16 id;
    u8 state;
    u8 pad;
} Entry_00113760;

/* Orders a fighting unit (task `pTask`): straight at the enemy leader when `fGoalFirst` and the path is open,
   else at the nearest enemy it can beat within 2 squares (5 with `bActive`); else it pushes in. */
void TaLogic001_CommandBtlUnit(void *pTask, s32 fGoalFirst, s32 bActive) {
    extern void TaLogic_InitIgnoreLst();
    extern s32 TaLogic_IsRootOpen();
    extern s32 TaLogic001_GetNearUnit();
    extern void TaLogic001_CommandInvadeUnit();
    s32 position;
    u8 buffer[0x70];
    Entry_00113760 entries[22];
    s16 countA;
    s16 countB;

    if (SzDuel_GetUnit(((UnitTask *)pTask)->ownerId >> 8,
                       ((UnitTask *)pTask)->ownerId & 0xFF) != 0) {
        s32 player;
        s32 other;
        s32 step;
        s32 unitInfo;
        s32 i;
        Entry_00113760 *p;

        player = Ta_GetCurrentSide(((UnitTask *)pTask)->ownerId >> 8,
                              ((UnitTask *)pTask)->ownerId & 0xFF);
        other = (player == 0 ? 1 : 0) << 8;
        position = SzDuel_GetUnitLoc(((UnitTask *)pTask)->ownerId >> 8,
                                ((UnitTask *)pTask)->ownerId & 0xFF);
        step = SzDuel_GetUnitLoc(other >> 8, other & 0xFF);
        unitInfo = SzDuel_GetUnit(((UnitTask *)pTask)->ownerId >> 8,
                            ((UnitTask *)pTask)->ownerId & 0xFF);
        p = entries;
        i = 0;
        do {
            ++i;
            p->id = 0xFFFF;
            p->state = 0xFF;
            ++p;
        } while (i < 22);
        TaLogic_InitIgnoreLst(buffer);
        if (fGoalFirst != 0) {
            if (TaLogic_IsRootOpen(((UnitTask *)pTask)->ownerId >> 8,
                             ((UnitTask *)pTask)->ownerId & 0xFF,
                             position & 0xFF, position >> 8,
                             other >> 8, other & 0xFF,
                             step & 0xFF, step >> 8, 2) > 0) {
                ((UnitTask *)pTask)->mission = 0x2FF;
                ((UnitTask *)pTask)->goal.dwGoal = (other << 16) |
                    *(u16 *)&((UnitTask *)pTask)->goal.dwGoal;
                return;
            }
        }
        step = 1;
        countB = 0;
        countA = 0;
        for (; step <= (bActive != 0 ? 5 : 2); ++step) {
            s32 limit = bActive != 0 ? 5 : 2;
            s32 side;
            s32 result;

            side = Ta_GetCurrentSide(((UnitTask *)pTask)->ownerId >> 8,
                                ((UnitTask *)pTask)->ownerId & 0xFF) == 0 ? 1 : 0;
            result = TaLogic001_GetNearUnit(pTask, 0, unitInfo, position & 0xFF, position >> 8,
                                  side, step & 0xFF, TaLogic_Seto_GetWarnHideLvl(player),
                                  entries, 0, &countA, &countB, limit & 0xFF, buffer);
            switch (result) {
                case 3:
                    ((UnitTask *)pTask)->mission = 0x6FF;
                    ((UnitTask *)pTask)->goal.dwGoal = (position << 16) |
                        *(u16 *)&((UnitTask *)pTask)->goal.dwGoal;
                    return;
                case 2:
                    ((UnitTask *)pTask)->mission = 0x3FF;
                    ((UnitTask *)pTask)->goal.dwGoal = (position << 16) |
                        *(u16 *)&((UnitTask *)pTask)->goal.dwGoal;
                    return;
                case 1:
                    return;
                case 0:
                    ((UnitTask *)pTask)->mission = 0x5FF;
                    return;
            }
        }
        TaLogic001_CommandInvadeUnit(pTask, bActive);
    }
}

/* TaLogic_GetNearUnit with this duelist's view and strength settings. */
s32 TaLogic001_GetNearUnit(s32 pTask, s32 pTree, s32 pVarInfo, s32 nX, s32 nZ, s32 eSide, s32 bDist, s32 WarnLvl, s32 nUnitLst, u16 wUnitNum, s32 wSize, s32 wNodeCount, u8 bChase, s32 wIgnoreLst) {
    return TaLogic_GetNearUnit(pTask, pTree, pVarInfo, nX, nZ, eSide, bDist, WarnLvl,
                  nUnitLst, wUnitNum, wSize, wNodeCount, bChase,
                  0, 3000, wIgnoreLst);
}

typedef struct {
    u16 position;
    u8 pad2[2];
    u16 state;
    u8 pad6[2];
    union {
        u16 low;
        u32 value;
    } flags;
} Data_00113A60;

/* Orders a unit (task `pTask`) to push into the opponent's side of the board. */
void TaLogic001_CommandInvadeUnit(void *pTask) {
    Data_00113A60 *data = pTask;
    s32 pair;
    s32 low;

    Ta_IsUnitControl(data->position >> 8, data->position & 0xFF);
    pair = SzDuel_GetUnitLoc(data->position >> 8, data->position & 0xFF);
    if (CheckLandAgreement2(3, data->position >> 8, data->position & 0xFF) == 1) {
        data->state = 0x6FF;
        data->flags.value = data->flags.low | (TaLogic001_GetNextGrassPoint(pair & 0xFF, pair >> 8) << 16);
    } else {
        low = pair & 0xFF;
        data->state = 0x6FF;
        if (low < 3 && (pair >> 8) < 3) {
            data->flags.value = data->flags.low | 0x03030000;
        } else if (low >= (pair >> 8)) {
            data->flags.value = data->flags.low | 0x03050000;
        } else {
            data->flags.value = data->flags.low | 0x05030000;
        }
    }
}

/* The next forest square toward the opponent from (nX, nZ). */
s32 TaLogic001_GetNextGrassPoint(s32 nX, s32 nZ) {
    s32 result;

    if (nZ >= 5) {
        result = 0x602;
    } else if (nX >= 5) {
        result = 0x206;
    } else if (nX >= nZ) {
        result = 0x105;
    } else {
        result = 0x501;
    }
    return result;
}

typedef struct Entry_00113BB0 {
    u16 value;
    u8 flag;
    u8 pad;
} Entry_00113BB0;

/* Orders an effect monster (task `pTask`): where its effect does most (`fGoalFirst`: try its goal first). */
void TaLogic001_CommandEfcMonster(void *pTask, s32 fGoalFirst) {
    u8 buffer[0x70];
    Entry_00113BB0 entries[22];
    u16 out_a;
    u16 out_b;
    u16 count;
    s32 attempt;
    u16 *command = (u16 *)pTask;
    s32 owner;
    s32 position;
    s32 state;
    s32 object;
    s32 high;
    s32 i;
    Entry_00113BB0 *entry;
    s32 result;
    u16 id;
    u32 mode = fGoalFirst;
    extern s32 SzDuel_GetUnitCardNo();
    extern s32 TaLogic_GetNearUnitL3(s32, s32, s32, void *, s32, s32, s32, s32, s32, s32, s32);
    extern s32 TaLogic_GetNearUnitL2();
    extern void TaLogic_InitIgnoreLst();

    id = command[0];
    if (SzDuel_GetUnit(id >> 8, id & 0xFF) != 0) {
        id = command[0];
        owner = Ta_GetCurrentSide(id >> 8, id & 0xFF);
        id = command[0];
        position = SzDuel_GetUnitLoc(id >> 8, id & 0xFF);
        count = 0;
        out_b = 0;
        out_a = 0;
        id = command[0];
        object = SzDuel_GetUnit(id >> 8, id & 0xFF);
        entry = entries;
        i = 0;
        do {
            i++;
            entry->value = 0xFFFF;
            entry->flag = 0xFF;
            entry++;
        } while (i < 22);
        TaLogic_InitIgnoreLst(buffer);
        state = 0;
        id = command[0];
        switch (SzDuel_GetUnitCardNo(id >> 8, id & 0xFF)) {
        case 0x53:
            if (TaLogic001_IsUseLordOfDragon(owner) == 1) {
                command[2] = 0x3FF;
                *(u32 *)&command[4] = (position << 16) | command[4];
            } else {
                command[2] = 0x5FF;
            }
            return;
        case 0x89: {
            high = position >> 8;
            attempt = 1;
            position &= 0xFF;
            while (1) {
                state = TaLogic_GetNearUnitL2(state, object, position, high, owner == 0 ? 1 : 0,
                                     (u8)attempt, 0, TaLogic_Seto_GetWarnHideLvl(owner),
                                     entries, &count, &out_a, &out_b, buffer);
                result = TaLogic_GetNearUnitL3(object, position, high, entries, 5, 0x34,
                                      0, 2, 0, TaLogic_Seto_GetWarnHideLvl(owner), count);
                if (result >= 0) {
                    command[2] = 0x2FF;
                    *(u32 *)&command[4] = (result << 16) | command[4];
                    return;
                }
                attempt++;
                if (attempt <= 5) {
                    continue;
                }
                break;
            }
            break;
        }
        case 0xBF:
            if (TaLogic_CommandGunnerUnit(command, 0) == 1) {
                command[2] = 0xBFF;
                return;
            }
            break;
        case 0x179:
            if (TaLogic001_IsUseLifeHourGlass(owner) == 1 && TaLogic_CommandGunnerUnit(command, 0) == 1) {
                command[2] = 0xBFF;
                return;
            }
            break;
        case 0x186:
            if (TaLogic001_IsUseBraveHourGlass(owner) == 1 && TaLogic_CommandGunnerUnit(command, 0) == 1) {
                command[2] = 0xBFF;
                return;
            }
            break;
        }
        TaLogic001_CommandBtlUnit(command, 1, mode);
    }
}

/* Orders a face-down magic card (task `pTask`): whether and where to open it. */
void TaLogic001_CommandSpellUnit(void *pTask) {
    UnitTask *arg;
    s32 search_key;
    s32 compare_key;
    s32 *object;
    s32 result;
    u32 kind;
    s32 status;

    arg = (UnitTask *)pTask;
    search_key = Ta_IsUnitControl(arg->ownerId >> 8, arg->ownerId & 0xFF);
    compare_key = SzDuel_GetUnitLoc(arg->ownerId >> 8, arg->ownerId & 0xFF);
    object = Ta_GetUnitEffect(arg->ownerId >> 8, arg->ownerId & 0xFF, 0);
    if (object == NULL) {
        arg->mission = 0x5FF;
        return;
    }
    switch (SzDuel_GetUnitKind(arg->ownerId >> 8, arg->ownerId & 0xFF) >> 5) {
    case 1:
        kind = (u32)*object >> 8;
        if (kind != 4) {
            status = 0xCFF;
            switch (kind) {
            case 2:
                arg->mission = 0x6FF;
                arg->goal.dwGoal = arg->goal.wGoal[0] | 0x03030000;
                return;
            case 20:
                arg->mission = 0xCFF;
                return;
            }
        } else {
            result = TaLogicCom_Seto_GetUseXYRangeSpell(search_key, object);
            if (result >= 0) {
                arg->mission = 0x6FF;
                if ((*object & 0x3F) == 0) {
                    arg->goal.dwGoal = arg->goal.wGoal[0] | (((compare_key >> 8) << 8 | (result & 0xFF)) << 16);
                } else {
                    arg->goal.dwGoal = (result << 16) | arg->goal.wGoal[0];
                }
                return;
            }
        }
        goto fail_status;
    case 3:
        if (TaLogic_CommandGunnerUnit(pTask, 0) == 1) {
            arg->mission = 0xBFF;
            return;
        }
        goto fail_status;
    default:
fail_status:
        status = 0x5FF;
        goto store_status;
    }
store_status:
    arg->mission = status;
    return;
}

typedef struct {
    s16 id;
    u8 unk2;
    u8 pad3;
    s16 unk4;
    u8 pad6[6];
    s32 unkC;
} Ctx_00114080;

typedef struct {
    u8 pad0[0x3C];
    u16 unk3C;
    u8 pad3E[0x22];
} Work_00114080;

s32 TaLogic_GetNearCard2(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8,
                  s32 arg9);

/* The summon task for side `nSide`: which hand cards to play and where, into `pInput`; -1 when it plays none. */
s32 TaLogic_Seto_GetMinimumTask_Summon(s32 wUnit, s32 nSide, void *pInput) {
    extern s32 TaLogic_GetUnitNum(s32, s32);
    Work_00114080 work;
    s32 ret;
    s32 res;
    s32 pos;
    s32 kind;
    Ctx_00114080 *ctx = pInput;

    ctx->id = wUnit;
    if (SzDuel_InqHandPhase(nSide) == 0) {
        return -1;
    }
    if (TaLogic_GetUnitNum(nSide, 0) == 5 && TaLogic_GetUnitNum(nSide, 1) == 5) {
        return -1;
    }
    kind = TaLogic001_IsHandPlay(nSide, &work);
    if (kind < 0) {
        return -1;
    }
    ctx->unk2 = 10;
    ctx->unkC = 0;
    pos = SzDuel_GetUnitLoc(wUnit >> 8, wUnit & 0xFF);
    if (kind == 0) {
        if (TaLogic001_SetComboQue(nSide, (u8 *)ctx, &work) >= 0) {
            ret = TaLogic_GetNearCard2(&work, pos & 0xFF, pos >> 8, nSide == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, TaLogic_Seto_GetWarnHideLvl(nSide));
            if (ret < 0) {
                if (SzDuel_GetUnitMonsterCount(nSide) < 4) {
                    res = TaLogic001_GetSummonPiece(nSide, kind, &work, ret);
                    if (res < 0) {
                        return -1;
                    }
                    ctx->unk4 = res;
                    return 1;
                }
            } else {
                res = TaLogic001_GetSummonPiece(nSide, kind, &work, ret);
                if (res < 0) {
                    return -1;
                }
                ctx->unk4 = res;
                return 1;
            }
        }
    } else {
        ret = TaLogic_GetNearCard2(&work, pos & 0xFF, pos >> 8, nSide == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, TaLogic_Seto_GetWarnHideLvl(nSide));
    }
    if (kind == 2) {
        TaLogic001_SetSpecialComboQue(nSide, ctx, &work);
        res = TaLogic001_GetSummonPiece(nSide, kind, &work, ret);
        if (res < 0) {
            return -1;
        }
        ctx->unk4 = res;
        return 1;
    }
    if (TaLogic001_GetSpellPlay(nSide, (u8 *)ctx, &work, work.unk3C) < 0) {
        return -1;
    }
    res = TaLogic001_GetSummonPiece(nSide, kind, &work, ret);
    if (res < 0) {
        return -1;
    }
    ctx->unk4 = res;
    return 1;
}

/* Whether side `nSide` should play from its hand this turn (and what, into `pInput`). */
s32 TaLogic001_IsHandPlay(s32 nSide, void *pInput) {
    extern s32 TaLogic_GetUnitNum();
    extern s32 SzDuel_GetUnitCurseRest();
    s32 cards[8];
    u8 buffer[32];
    u8 primary;
    u8 secondary;
    s32 i;
    s32 result;

    primary = (u8)TaLogic_GetUnitNum(nSide, 0);
    secondary = (u8)TaLogic_GetUnitNum(nSide, 1);
    if (pInput == NULL) {
        return -1;
    }
    TaHand_GetNextHand(nSide, cards);
    if (primary == 5) {
        if (TaLogic001_GetSpellPlay(nSide, buffer, pInput, 999) >= 0) {
            return 1;
        }
        return -1;
    }
    if (secondary == 5) {
        s32 index = 0;
        s32 *p;
        if (index < TaHand_GetNextHandNum(nSide)) {
            p = cards;
            do {
                if ((TaHand_GetCardKind(*p) >> 5) == 0 && TaHand_CanAffordSummonCost(nSide, *p) == 1) {
                    SzDuel_InitCardInfo(pInput, cards[index]);
                    return 0;
                }
                p++;
                index++;
            } while (index < TaHand_GetNextHandNum(nSide));
        }
        return -1;
    }
    if (TaLogic001_GetSpecCardPlay(nSide, buffer, pInput, 0x345) >= 0) {
        if (TaLogic001_IsDoCerem(nSide, 0x345) == 1) {
            return 2;
        }
    }
    if (TaLogic001_IsUseLordOfDragon(nSide) == 1) {
        if (SearchUnitByRange(0, 0, nSide, 1, 0x53001C, 14) == 0) {
            if (TaLogic001_GetSpecCardPlay(nSide, buffer, pInput, 0x53) >= 0) {
                return 2;
            }
            if (TaLogic001_GetProtectCardPlay(nSide, buffer, pInput) >= 0) {
                return 2;
            }
        }
    }
    if (TaLogic001_IsUseLifeHourGlass(nSide) == 1) {
        if (TaLogic001_GetSpecCardPlay(nSide, buffer, pInput, 0x179) >= 0) {
            return 2;
        }
    }
    if (TaLogic001_IsUseBraveHourGlass(nSide) == 1) {
        if (TaLogic001_GetSpecCardPlay(nSide, buffer, pInput, 0x186) >= 0) {
            return 2;
        }
    }
    if (TaLogic001_IsUseRevive(nSide) >= 0) {
        if (TaLogic001_GetSpecCardPlay(nSide, buffer, pInput, 0x2AD) >= 0) {
            return 2;
        }
    }
    for (i = 0; i < 11; i++) {
        if (SzDuel_GetUnitCurseRest(nSide, i) != 0 && TaLogic001_GetSpecCardPlay(nSide, buffer, pInput, 0x31C) >= 0) {
            return 2;
        }
    }
    {
        s32 *p;
        s32 index = 0;
        if (index < TaHand_GetNextHandNum(nSide)) {
            p = cards;
            do {
                if ((TaHand_GetCardKind(*p) >> 5) == 0 && TaHand_CanAffordSummonCost(nSide, *p) == 1) {
                    SzDuel_InitCardInfo(pInput, cards[index]);
                    return 0;
                }
                p++;
                index++;
            } while (index < TaHand_GetNextHandNum(nSide));
        }
    }
    result = TaLogic001_GetSpellPlay(nSide, buffer, pInput, 999);
    if (result >= 0) {
        return result;
    }
    return -1;
}

/* Whether side `nSide` holds card `nCardNo` and can summon it (its slot into `bCombo`, the card into `pCardInfo`);
   returns its kind group or -1. */
s32 TaLogic001_GetSpecCardPlay(s32 nSide, void *bCombo, void *pCardInfo, s32 nCardNo) {
    s32 entries[8];
    s32 i;

    TaHand_GetNextHand(nSide, entries);
    for (i = 0; i < TaHand_GetNextHandNum(nSide); i++) {
        if ((nCardNo & 0xFFFF) == entries[i] && TaHand_CanAffordSummonCost(nSide, entries[i]) == 1) {
            *((s8 *)bCombo + 6) = i;
            SzDuel_InitCardInfo(pCardInfo, entries[i]);
            return TaHand_GetCardKind(entries[i]) >> 5;
        }
    }
    return -1;
}

/* Whether side `nSide` holds card `card` and can summon it (its slot into `bCombo`, the card into `pCardInfo`). */
static inline s32 search_001147B0(s32 nSide, void *bCombo, void *pCardInfo, s32 card) {
    s32 cards[8];
    s32 i;

    TaHand_GetNextHand(nSide, cards);
    for (i = 0; i < TaHand_GetNextHandNum(nSide); i++) {
        if (cards[i] == card && TaHand_CanAffordSummonCost(nSide, cards[i]) == 1) {
            *((s8 *)bCombo + 6) = i;
            SzDuel_InitCardInfo(pCardInfo, cards[i]);
            return TaHand_GetCardKind(cards[i]) >> 5;
        }
    }
    return -1;
}

/* The first protecting card (0x337, 0x335, 0x338, 0x33C, 0x339) side `nSide` can play now, or -1. */
s32 TaLogic001_GetProtectCardPlay(s32 nSide, void *bCombo, void *pCardInfo) {
    s32 result;

    result = search_001147B0(nSide, bCombo, pCardInfo, 0x337);
    if (result >= 0) {
        return result;
    }
    result = search_001147B0(nSide, bCombo, pCardInfo, 0x335);
    if (result >= 0) {
        return result;
    }
    result = search_001147B0(nSide, bCombo, pCardInfo, 0x338);
    if (result >= 0) {
        return result;
    }
    result = search_001147B0(nSide, bCombo, pCardInfo, 0x33C);
    if (result >= 0) {
        return result;
    }
    result = search_001147B0(nSide, bCombo, pCardInfo, 0x339);
    if (result >= 0) {
        return result;
    }
    return -1;
}

/* Whether side `nSide` plays a magic or ritual card from its hand now (its slot into `bCombo`, the card into
   `pCardInfo`). */
s32 TaLogic001_GetSpellPlay(s32 nSide, u8 *bCombo, void *pCardInfo, s32 nMode) {
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

typedef struct Info_00114D40 {
    u8 pad00[8];
    u16 x;
    s16 y;
} Info_00114D40;

typedef struct Sprite_00114D40 {
    Info_00114D40 *info;
    u8 pad04[0x34];
    s16 x;
    s16 y;
} Sprite_00114D40;

/* Fills hand combination `bCombo` for side `nSide`: the best fusion or equip chain, its card into `pCardInfo`. */
s32 TaLogic001_SetComboQue(s32 nSide, u8 *bCombo, void *pCardInfo) {
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
                            TaLogic_Seto_ConvEmptyCombo(nSide, *node, entries);
                            TaLogic_CopyArray((u8 *)*node + 2, bCombo + 6);
                            SzDuel_InitCardInfo(pCardInfo, **node);
                            ((Sprite_00114D40 *)pCardInfo)->x = (value >> 16) - (((Sprite_00114D40 *)pCardInfo)->info->x & 0x1FFF);
                            ((Sprite_00114D40 *)pCardInfo)->y = (value & 0xFFFF) - (((Sprite_00114D40 *)pCardInfo)->info->y & 0x1FFF);
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
} Info_00114F20;

/* Fills an empty combination: the hand card side `nSide` can summon with the best attack plus defence. */
void TaLogic_Seto_ConvEmptyCombo(s32 nSide, void *pCardInfo, s32 *pResult) {
    Info_00114F20 *info = pCardInfo;
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
                if (card != 0x3E7 && TaLogic001_IsRefuseEmptyCombo(card) == 0 && level >= TaHand_GetCardSummonCost2(card, nSide)) {
                    cost = TaHand_GetCardAPDP(card);
                    if ((cost & 0xFFFF) + (cost >> 16) * 2 < 0x1389 && TaHand_IsCardEffect(card) == 2 &&
                        (u16)TaLogic_GetHandFusion(info->id, (u16)card) == 0x3E7) {
                        TaLogic_AddEmptyCombo(info->values, buf[i]);
                    }
                }
            }
        }
    }
}

/* Whether this duelist keeps card `nCardNo` out of a summon (it is wanted for an equip). */
s32 TaLogic001_IsRefuseEmptyCombo(s32 nCardNo) {
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
} Obj1_00115160;

typedef struct {
    u8 pad0[0x3C];
    u16 id;
} Obj2_00115160;

/* Fills hand combination `bCombo` for side `nSide` with this duelist's special combination, its card into
   `pCardInfo`. */
s32 TaLogic001_SetSpecialComboQue(s32 nSide, void *bCombo, void *pCardInfo) {
    Obj1_00115160 *o1 = bCombo;
    Obj2_00115160 *o2 = pCardInfo;
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
            if (o2->id == list[i]) {
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

typedef struct {
    u8 low : 4;
    u8 high : 4;
} Cell_00115340;

/* The square side `nSide` summons a card of kind `sKind` to. */
s32 TaLogic001_GetSummonPiece(s32 nSide, u8 sKind, void *pInput, s32 nMode) {
    extern s32 TaLogic_IsUnitWin4();
    extern s32 TaLogic_GetInvadeRoot2();
    extern s32 TaLogic_GetRoot2(void *, void *, s32, s32, s32, s32, u16, s32);
    s32 best_position;
    s32 best_cost;
    s32 fallback_position;
    Cell_00115340 cells[12];
    s32 y;
    s32 x;
    s32 i;
    s32 best;
    s32 position;
    s32 target_y;
    s32 target_x;
    s32 target;
    s32 result;
    s32 j;
    Cell_00115340 *p;

    if (pInput == NULL) {
        return -1;
    }
    p = cells;
    j = 0;
    do {
        p->low = p->high = 15;
        j++;
        p++;
    } while (j < 12);

    if ((u8)(*((u8 *)pInput + 0x3E) >> 5) == 0 &&
        *(u16 *)((u8 *)pInput + 0x3C) != 0x53) {
        best = 14;
        if (nMode >= 0) {
            s32 candidate;
            s32 candidate_y;
            s32 candidate_x;
            s32 n;
            s32 cost;

            best_cost = 255;
            best_position = 65535;
            target = SzDuel_GetUnitLoc(nMode >> 8, nMode & 255);
            n = 0;
            target_y = target >> 8;
            target_x = target & 255;
            do {
                candidate = Ta_GetSommonPiecePreference(nSide, n);
                if (candidate >= 0) {
                    candidate_x = candidate & 255;
                    candidate_y = candidate >> 8;
                    if (SzDuel_GetField(candidate_x, candidate_y) != 8 &&
                        (SzDuel_GetField(candidate_x, candidate_y) != 9 ||
                         Ta_IsVirus_Chk3(pInput, candidate_x, candidate_y) != 1) &&
                        SzDuel_GetMapUnit(candidate_x, candidate_y) == 0) {
                        if (TaLogic_IsUnitWin4(pInput, nMode, TaLogic_Seto_GetWarnHideLvl(nSide),
                                         target_x, target_y, 0) > 0) {
                            cost = TaLogic_GetInvadeRoot2(pInput, cells, candidate_x, candidate_y,
                                                target_x, target_y, nMode, 0, 5,
                                                (u16)TaLogic_Seto_GetWarnHideLvl(nSide));
                        } else {
                            cost = TaLogic_GetRoot2(pInput, cells, candidate_x, candidate_y,
                                                target_x, target_y, nMode, 5);
                        }
                        if (TaLogic_GetMinGoalCount((u8 *)cells) > 0 && cost < best_cost) {
                            best_cost = cost;
                            best_position = candidate;
                        }
                    }
                }
                n++;
            } while (n < 8);
            if (best_position != 65535) {
                return best_position;
            }
        }
        best = 14;

        fallback_position = 0;
        i = 0;
        do {
            position = Ta_GetSommonPiecePreference(nSide, i);
            if (position >= 0) {
                x = position & 255;
                y = position >> 8;
                if (SzDuel_GetField(x, y) != 8 &&
                    (SzDuel_GetField(x, y) != 9 || Ta_IsVirus_Chk3(pInput, x, y) != 1) &&
                    SzDuel_GetMapUnitID(x, y) < 0) {
                    if (CheckLandAgreement(3, pInput) == 1) {
                        if (y >= 5) {
                            target = 0x602;
                        } else if (x >= 5) {
                            target = 0x206;
                        } else if (x >= y) {
                            target = 0x105;
                        } else {
                            target = 0x501;
                        }
                        target_x = target & 255;
                        target_y = target >> 8;
                        result = SzDuel_GetMapUnitID(target_x, target_y);
                        if (result < 0) {
                            result = 65535;
                        }
                        result = TaLogic_GetRoot2(pInput, cells, x, y, target_x, target_y,
                                              (u16)result, 7);
                        if (result < best && result >= 0) {
                            fallback_position = position;
                            best = result;
                        }
                    } else {
                        result = SzDuel_GetMapUnitID(3, 3);
                        if (result < 0) {
                            result = 65535;
                        }
                        result = TaLogic_GetRoot2(pInput, cells, x, y, 3, 3, (u16)result, 7);
                        if (result < best && result >= 0) {
                            fallback_position = position;
                            best = result;
                        }
                    }
                }
            }
            i++;
        } while (i < 8);
        if (best < 14) {
            return fallback_position;
        } else {
            fallback_position = -1;
        }
        return fallback_position;
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
                if (SzDuel_GetField(x, y) != 8 && SzDuel_GetField(x, y) != 9 &&
                    SzDuel_GetMapUnitID(x, y) < 0 && y < 8) {
                    best = position;
                }
            }
            i++;
        } while (i < 8);
        if (best >= 0) {
            return best;
        } else {
            best = -1;
        }
        return best;
    }
}

typedef struct Nibbles_00115850 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_00115850;

typedef struct Output_00115850 {
    u16 position;
    u8 action;
    u8 pad3;
    u16 destination;
    u8 pad6[6];
    s32 special;
    u8 result;
} Output_00115850;

/* The task of a unit running from danger (task `pTask`): the safest square in reach, into `pInput` (`fFirst` = 1
   for the unit's first-choice task). */
s32 TaLogic_Seto_GetMinimumTask_RunMission(UnitTask *pTask, s32 nSide, void *pInput, u8 fFirst) {
    Output_00115850 *output = pInput;
    s32 target;
    u8 endX;
    u8 extra;
    Nibbles_00115850 nibbles[12];
    s32 bestScore;
    s32 best;
    s32 i;
    Nibbles_00115850 *p;
    extern s32 TaLogic_Seto_IsOpenUnit();
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

        initialScore = TaLogic_Seto_GetWarnHideLvl(nSide);
        centerX = target & 0xFF;
        centerY = target >> 8;
        if (TaLogic_GetUnitWarning(centerX, centerY, pTask->ownerId, 3, initialScore, 0) == 0) {
            output->position = pTask->ownerId;
            output->action = 6;
            output->destination = target;
            output->result = TaLogic_IsDefStyleUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, output->destination, 1, 0);
            output->special = TaLogic_Seto_IsOpenUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, pTask);
            TaLogic_InitRogicControl(pTask, fFirst);
            return 0;
        }
        if ((range = GetMoveRange(SzDuel_GetUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF), centerX, centerY)) == 0) {
            output->position = pTask->ownerId;
            output->action = 6;
            output->destination = target;
            output->result = TaLogic_IsDefStyleUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, output->destination, 1, 0);
            output->special = TaLogic_Seto_IsOpenUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, pTask);
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
                        candidateScore = TaLogic_GetUnitWarning(x, y, pTask->ownerId, 3, (u16)TaLogic_Seto_GetWarnHideLvl(nSide), 0);
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
                output->result = TaLogic_IsDefStyleUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, output->destination, 1, 0);
            }
            output->special = TaLogic_Seto_IsOpenUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, pTask);
        } else {
            output->position = pTask->ownerId;
            output->action = 6;
            output->destination = target;
            output->result = TaLogic_IsDefStyleUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, output->destination, 1, 0);
            output->special = TaLogic_Seto_IsOpenUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, pTask);
        }
        TaLogic_InitRogicControl(pTask, fFirst);
        return 0;
    }
}

typedef struct Input_00115E20 {
    u16 position;
    u8 pad2[6];
    u32 targets;
} Input_00115E20;

typedef struct Output_00115E20 {
    u16 position;
    s8 action;
    u8 pad3;
    s16 target;
    u8 pad6[6];
    s32 kind;
    s8 result;
} Output_00115E20;

typedef struct Candidate_00115E20 {
    u8 x : 4;
    u8 y : 4;
} Candidate_00115E20;

/* The task's target square: the second half-word when the second argument is 1, else the first. */
static inline u32 target_00115E20(void *src, u8 mode) {
    Input_00115E20 *input = src;
    if (mode == 1) {
        return (input->targets >> 16) & 0xFFFF;
    }
    return (u16)input->targets;
}

/* The task of a unit attacking (task `pTask`): its path to the goal, into `pInput`; -1 when it has none (`fFirst`
   = 1 for the unit's first-choice task). */
s32 TaLogic_Seto_GetMinimumTask_AtkMission(void *pTask, s32 nSide, void *pInput, u8 fFirst) {
    extern void TaLogic_GetInvadeRoot();
    s32 origin;
    s32 destination;
    s32 count;
    Candidate_00115E20 candidates[12];
    Candidate_00115E20 *point;
    s32 originY;
    s32 originX;
    s32 i;
    u32 selected;
    Input_00115E20 *input = pTask;
    Output_00115E20 *output = pInput;

    selected = target_00115E20(input, fFirst);
    if (SzDuel_GetUnit(target_00115E20(input, fFirst) >> 8,
                     selected & 0xFF) == 0) {
        TaLogic_InitRogicControl(input, 1);
        return -1;
    }
    TaLogic_Seto_IsOpenUnit(input->position >> 8, input->position & 0xFF, (s32)input);
    origin = SzDuel_GetUnitLoc(input->position >> 8, input->position & 0xFF);
    selected = target_00115E20(input, fFirst);
    destination = SzDuel_GetUnitLoc(target_00115E20(input, fFirst) >> 8,
                               selected & 0xFF);
    point = candidates;
    for (i = 0; i < 12; i++) {
        candidates[i].x = candidates[i].y = 15;
    }
    if (GetMoveRange(SzDuel_GetUnit(input->position >> 8, input->position & 0xFF),
                      originX = origin & 0xFF, originY = origin >> 8) == 0) {
        s32 score;
        output->position = input->position;
        output->action = 6;
        output->target = origin;
        score = TaLogic_GetUnitWarning(originX, originY, nSide, 3, 1,
                             (u8)TaLogic_Seto_GetWarnHideLvl(nSide));
        if (score >= SzDuel_GetUnitAP(input->position >> 8, input->position & 0xFF, 0)) {
            output->result = 1;
        } else {
            output->result = 0;
        }
        TaLogic_InitRogicControl(input, fFirst);
        return 0;
    } else {
        s32 position;
        s32 destinationY;
        s32 destinationX;
        s32 index;
        s32 bestScore;
        s32 bestIndex;
        u16 random;

        position = input->position;
        random = TaLogic_Seto_GetWarnHideLvl(nSide);
        TaLogic_GetInvadeRoot(position >> 8, position & 0xFF, candidates,
                      originX, originY, destinationX = destination & 0xFF,
                      destinationY = destination >> 8,
                      target_00115E20(input, fFirst), (s64)0, (s64)30,
                      (s64)random);
        count = TaLogic_GetMinGoalCount((u8 *)candidates);
        bestIndex = 255;
        if (count > 0) {
            bestScore = 65535;
            for (index = 0; index < count; index++, point++) {
                s32 score = TaLogic_GetUnitWarning(point->x, point->y, nSide, 2, 1,
                                         (u8)TaLogic_Seto_GetWarnHideLvl(nSide));
                if (score < bestScore) {
                    bestScore = score;
                    bestIndex = index;
                } else if (score == bestScore) {
                    Candidate_00115E20 *best = &candidates[bestIndex];
                    if (((destinationX < point->x ? point->x : destinationX) -
                         (point->x < destinationX ? point->x : destinationX)) +
                        ((destinationY < point->y ? point->y : destinationY) -
                         (point->y < destinationY ? point->y : destinationY)) <
                        ((destinationX < best->x ? best->x : destinationX) -
                         (best->x < destinationX ? best->x : destinationX)) +
                        ((destinationY < best->y ? best->y : destinationY) -
                         (best->y < destinationY ? best->y : destinationY))) {
                        bestScore = score;
                        bestIndex = index;
                    }
                }
            }
        } else {
            output->position = input->position;
            output->action = 6;
            output->target = origin;
            output->kind = 2;
            output->result = 2;
            TaLogic_InitRogicControl(input, fFirst);
            return -1;
        }
        if (bestIndex != 255) {
            output->position = input->position;
            output->action = 6;
            output->target = (candidates[bestIndex].y << 8) | candidates[bestIndex].x;
            output->kind = 2;
            output->result = 2;
        } else {
            output->position = input->position;
            output->action = 6;
            output->target = origin;
            output->kind = 2;
            output->result = 2;
            TaLogic_InitRogicControl(input, fFirst);
            return -1;
        }
    }
    return 0;
}

typedef struct Coord_001162F0 {
    u8 x : 4;
    u8 y : 4;
} Coord_001162F0;

typedef struct Output_001162F0 {
    u16 position;
    u8 kind;
    u8 pad3;
    u16 target;
    u8 pad6[6];
    s32 value;
    u8 flag;
} Output_001162F0;

/* The task's target square: the second half-word when the second argument is 1, else the first. */
static inline u32 target_001162F0(void *unit, s32 side) {
    return side == 1 ? (u32)(u16)(((UnitTask *)unit)->goal.dwGoal >> 16) : (u32)((UnitTask *)unit)->goal.wGoal[0];
}

/* The smaller of the two values. */
static inline u32 minY_001162F0(void *unit, s32 side, u8 coord) {
    return coord < (target_001162F0(unit, side) >> 8) ? coord : (target_001162F0(unit, side) >> 8);
}

/* The larger of the two values. */
static inline u32 maxY_001162F0(void *unit, s32 side, u8 coord) {
    return (target_001162F0(unit, side) >> 8) < coord ? coord : (target_001162F0(unit, side) >> 8);
}

/* The smaller of the two values. */
static inline u32 minX_001162F0(void *unit, s32 side, u8 coord) {
    return coord < (target_001162F0(unit, side) & 0xFF) ? coord : (target_001162F0(unit, side) & 0xFF);
}

/* The larger of the two values. */
static inline u32 maxX_001162F0(void *unit, s32 side, u8 coord) {
    return (target_001162F0(unit, side) & 0xFF) < coord ? coord : (target_001162F0(unit, side) & 0xFF);
}

/* The task of a unit moving to its goal (task `pTask`), into `pInput` (`fFirst` = 1 for the unit's first-choice
   task). */
s32 TaLogic_Seto_GetMinimumTask_MoveMission(void *pTask, s32 nSide, void *pInput, u8 fFirst, u8 nKind) {
    extern s32 TaLogic_Seto_IsOpenUnit();
    extern s32 TaLogic_GetUnitWarning();
    extern void TaLogic_GetRoot();
    extern s32 TaLogic_IsDefStyleUnit(s32, s32, s32, u8, s32);
    Coord_001162F0 coords[12];
    s32 initial;
    s32 cell;
    s32 count;

    initial = SzDuel_GetUnitLoc(((UnitTask *)pTask)->ownerId >> 8, ((UnitTask *)pTask)->ownerId & 0xFF);
    {
        s32 bestScore;
        s32 best;
        s32 side = fFirst;
        Coord_001162F0 *candidate;
        s32 index;
        if (target_001162F0(pTask, side) == 0xFFFF) {
            if (initial == target_001162F0(pTask, side)) {
                ((Output_001162F0 *)pInput)->position = ((UnitTask *)pTask)->ownerId;
                ((Output_001162F0 *)pInput)->kind = 6;
                ((Output_001162F0 *)pInput)->target = initial;
                ((Output_001162F0 *)pInput)->flag = TaLogic_IsDefStyleUnit(((UnitTask *)pTask)->ownerId >> 8, ((UnitTask *)pTask)->ownerId & 0xFF, ((Output_001162F0 *)pInput)->target, nKind, 0);
                ((Output_001162F0 *)pInput)->value = TaLogic_Seto_IsOpenUnit(((UnitTask *)pTask)->ownerId >> 8, ((UnitTask *)pTask)->ownerId & 0xFF, pTask);
                TaLogic_InitRogicControl(pTask, fFirst);
                return 0;
            }
        }

        if (SzDuel_GetUnitStatus(((UnitTask *)pTask)->ownerId >> 8, ((UnitTask *)pTask)->ownerId & 0xFF, 4) != 0) {
            if ((SzDuel_GetUnitKind(((UnitTask *)pTask)->ownerId >> 8, ((UnitTask *)pTask)->ownerId & 0xFF) >> 5) == 1 ||
                (SzDuel_GetUnitKind(((UnitTask *)pTask)->ownerId >> 8, ((UnitTask *)pTask)->ownerId & 0xFF) >> 5) == 5) {
                SzDuel_SetUnitStatus(((UnitTask *)pTask)->ownerId >> 8, ((UnitTask *)pTask)->ownerId & 0xFF, 0, 1);
                ((Output_001162F0 *)pInput)->position = ((UnitTask *)pTask)->ownerId;
                ((Output_001162F0 *)pInput)->kind = 14;
                return 0;
            }
        }

        candidate = coords;
        {
            s32 i = 0;
            Coord_001162F0 *entry = candidate;
            do {
                entry->x = entry->y = 0xF;
                i++;
                entry++;
            } while (i < 12);
        }

        cell = SzDuel_GetMapUnitID(target_001162F0(pTask, side) & 0xFF, target_001162F0(pTask, side) >> 8);
        if (cell < 0) {
            cell = 0xFFFF;
        }
        TaLogic_GetRoot(((UnitTask *)pTask)->ownerId >> 8, ((UnitTask *)pTask)->ownerId & 0xFF,
                     coords, initial & 0xFF, initial >> 8, target_001162F0(pTask, side) & 0xFF,
                     target_001162F0(pTask, side) >> 8, (u16)cell, 7);
        count = TaLogic_GetMinGoalCount((u8 *)coords);
        {
            if (count > 0) {
                best = 0xFF;
                bestScore = 0xFFFF;
                for (index = 0; index < count; index++) {
                    if (SzDuel_GetMapUnit(candidate->x, candidate->y) == 0) {
                        s32 score = TaLogic_GetUnitWarning(candidate->x, candidate->y, nSide, 2, 1, (u8)TaLogic_Seto_GetWarnHideLvl(nSide));
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
                            bestMinY = minY_001162F0(pTask, side, bestY);
                            bestMaxY = maxY_001162F0(pTask, side, bestY);
                            bestX = (&coords[best])->x;
                            bestMinX = minX_001162F0(pTask, side, bestX);
                            bestMaxX = maxX_001162F0(pTask, side, bestX);
                            currentY = (u8)candidate->y;
                            currentMinY = minY_001162F0(pTask, side, currentY);
                            currentMaxY = maxY_001162F0(pTask, side, currentY);
                            currentX = candidate->x;
                            currentMinX = minX_001162F0(pTask, side, currentX);
                            currentMaxX = maxX_001162F0(pTask, side, currentX);
                            if ((currentMaxX - currentMinX) + (currentMaxY - currentMinY) < (bestMaxX - bestMinX) + (bestMaxY - bestMinY)) {
                                bestScore = score;
                                best = index;
                            }
                        }
                    }
                    candidate++;
                }
            } else {
                ((Output_001162F0 *)pInput)->position = ((UnitTask *)pTask)->ownerId;
                ((Output_001162F0 *)pInput)->kind = 6;
                ((Output_001162F0 *)pInput)->target = initial;
                ((Output_001162F0 *)pInput)->flag = TaLogic_IsDefStyleUnit(((UnitTask *)pTask)->ownerId >> 8, ((UnitTask *)pTask)->ownerId & 0xFF, ((Output_001162F0 *)pInput)->target, nKind, 0);
                ((Output_001162F0 *)pInput)->value = TaLogic_Seto_IsOpenUnit(((UnitTask *)pTask)->ownerId >> 8, ((UnitTask *)pTask)->ownerId & 0xFF, pTask);
                TaLogic_InitRogicControl(pTask, fFirst);
                return 0;
            }

            if (best != 0xFF) {
                ((Output_001162F0 *)pInput)->position = ((UnitTask *)pTask)->ownerId;
                ((Output_001162F0 *)pInput)->kind = 6;
                ((Output_001162F0 *)pInput)->target = (coords[best].y << 8) | coords[best].x;
                ((Output_001162F0 *)pInput)->flag = TaLogic_IsDefStyleUnit(((UnitTask *)pTask)->ownerId >> 8, ((UnitTask *)pTask)->ownerId & 0xFF, ((Output_001162F0 *)pInput)->target, nKind, 0);
                ((Output_001162F0 *)pInput)->value = TaLogic_Seto_IsOpenUnit(((UnitTask *)pTask)->ownerId >> 8, ((UnitTask *)pTask)->ownerId & 0xFF, pTask);
            } else {
                ((Output_001162F0 *)pInput)->position = ((UnitTask *)pTask)->ownerId;
                ((Output_001162F0 *)pInput)->kind = 6;
                ((Output_001162F0 *)pInput)->target = initial;
                ((Output_001162F0 *)pInput)->flag = TaLogic_IsDefStyleUnit(((UnitTask *)pTask)->ownerId >> 8, ((UnitTask *)pTask)->ownerId & 0xFF, ((Output_001162F0 *)pInput)->target, nKind, 0);
                ((Output_001162F0 *)pInput)->value = TaLogic_Seto_IsOpenUnit(((UnitTask *)pTask)->ownerId >> 8, ((UnitTask *)pTask)->ownerId & 0xFF, pTask);
            }
            TaLogic_InitRogicControl(pTask, fFirst);
        }
    }
    return 0;
}

typedef struct {
    u16 position;
    u8 pad2[6];
    union {
        u32 both;
        u16 half[2];
    } target;
} Source_00116B60;

typedef struct {
    u16 position;
    u8 action;
    u8 pad3;
    u16 target;
    u8 pad6[10];
    s8 result;
} Action_00116B60;

typedef struct {
    u8 x : 4;
    u8 y : 4;
} Point_00116B60;

#define MIN_00116B60(a, b) ((a) < (b) ? (a) : (b))
#define MAX_00116B60(a, b) ((b) < (a) ? (a) : (b))

/* The task's target square: the second half-word when the second argument is 1, else the first. */
static inline u32 target_00116B60(void *arg0, s32 mode) {
    Source_00116B60 *source = arg0;
    if (mode == 1) {
        return (u16)(source->target.both >> 16);
    }
    return source->target.half[0];
}

/* Sets a move task (action 6) to the given square, and whether the unit should stay in defence there. */
static inline void fill_00116B60(void *arg0, void *arg2, s32 target, s32 flag) {
    Source_00116B60 *source = arg0;
    Action_00116B60 *action = arg2;
    action->position = source->position;
    action->action = 6;
    action->target = target;
    action->result = TaLogic_IsDefStyleUnit(source->position >> 8,
        source->position & 0xFF, action->target, flag, 0);
}

/* The task of setting a trap (task `pTask`), into `pInput`. */
s32 TaLogic_Seto_GetMinimumTask_TrapMission(void *pTask, s32 nSide, void *pInput, s32 fFirst) {
    s32 start;
    s32 count;
    s32 startY;
    Point_00116B60 points[16];
    s32 bestScore;
    Point_00116B60 *p;
    s32 targetY;
    s32 targetX;
    s32 i;
    s32 bestIndex;
    s32 mode;
    s32 target;
    s32 startX;
    u32 xPosition;
    u32 yPosition;
    Source_00116B60 *source = pTask;
    Action_00116B60 *action = pInput;
    extern void TaLogic_GetInvadeRoot();

    mode = fFirst & 0xFF;
    xPosition = target_00116B60(pTask, mode);
    yPosition = target_00116B60(pTask, mode);
    if (SzDuel_GetUnit(yPosition >> 8, xPosition & 0xFF) == 0) {
        TaLogic_InitRogicControl(pTask, 1);
        return -1;
    }
    start = SzDuel_GetUnitLoc(source->position >> 8, source->position & 0xFF);
    xPosition = target_00116B60(pTask, mode);
    yPosition = target_00116B60(pTask, mode);
    target = SzDuel_GetUnitLoc(yPosition >> 8, xPosition & 0xFF);
    if (target_00116B60(pTask, mode) == 0xFFFF) {
        fill_00116B60(pTask, pInput, start, 1);
        return 0;
    } else {
        s32 unit = SzDuel_GetUnit(source->position >> 8, source->position & 0xFF);
        startX = start & 0xFF;
        startY = start >> 8;
        if (GetMoveRange(unit, startX, startY) == 0 ||
                TaLogic_IsAttackedNow(source->position >> 8, source->position & 0xFF, 0) == 1) {
            fill_00116B60(pTask, pInput, start, 1);
            return 0;
        } else {
            p = points;
            {
                s32 n = 0;
                Point_00116B60 *q = p;
                do {
                    q->x = q->y = 0xF;
                    q++;
                    n++;
                } while (n < 12);
            }
            {
                s32 position = source->position;
                u16 card = (u16)TaLogic_Seto_GetWarnHideLvl(nSide);
                TaLogic_GetInvadeRoot(position >> 8, position & 0xFF, points,
                    startX, startY, targetX = target & 0xFF,
                    targetY = target >> 8, target_00116B60(pTask, mode),
                    0, 30, card);
            }
            count = TaLogic_GetMinGoalCount((u8 *)points);
            bestIndex = 0xFF;
            if (count > 0) {
                bestScore = 0;
                for (i = 0; i < count; i++, p++) {
                    if (SzDuel_GetMapUnit(p->x, p->y) == 0) {
                        s32 score = TaLogic_GetUnitWarning(p->x, p->y, nSide, 3, 1,
                            TaLogic_Seto_GetWarnHideLvl(nSide) & 0xFF);
                        if (bestScore < score) {
                            bestScore = score;
                            bestIndex = i;
                        } else if (score == bestScore) {
                            if (MAX_00116B60(p->x, targetX) - MIN_00116B60(p->x, targetX)
                                    + (MAX_00116B60(p->y, targetY) - MIN_00116B60(p->y, targetY))
                                    < MAX_00116B60(points[bestIndex].x, targetX) - MIN_00116B60(points[bestIndex].x, targetX)
                                    + (MAX_00116B60(points[bestIndex].y, targetY) - MIN_00116B60(points[bestIndex].y, targetY))) {
                                bestScore = score;
                                bestIndex = i;
                            }
                        }
                    }
                }
            } else {
                fill_00116B60(pTask, pInput, start, 1);
                return 0;
            }
            if (bestIndex != 0xFF) {
                action->position = source->position;
                action->action = 6;
                action->target = (points[bestIndex].y << 8) | points[bestIndex].x;
                action->result = TaLogic_IsDefStyleUnit(source->position >> 8,
                    source->position & 0xFF, action->target, 0, 0);
            } else {
                fill_00116B60(pTask, pInput, start, 1);
                return 0;
            }
        }
    }
    return 0;
}

typedef struct Nibbles_001170A0 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_001170A0;

typedef struct Output_001170A0 {
    u16 position;
    s8 command;
    u8 pad3;
    u16 value;
    u8 pad6[6];
    s32 count;
    s8 result;
} Output_001170A0;

/* The task of reviving a monster from the graveyard (task `pTask`), into `pInput` (`fFirst` = 1 for the unit's
   first-choice task). */
s32 TaLogic_Seto_GetMinimumTask_ReviveMission(UnitTask *pTask, s32 nSide, void *pInput, u8 fFirst) {
    Nibbles_001170A0 flags[12];
    s32 card;
    s32 selected;
    s32 index;
    Output_001170A0 *output = pInput;

    {
        s32 state;
        u32 *data;

        if ((SzDuel_GetUnitKind(pTask->ownerId >> 8, pTask->ownerId & 0xFF) >> 5) == 0) {
            data = SzDuel_GetUnitEffect(pTask->ownerId >> 8, pTask->ownerId & 0xFF, 3);
        } else {
            data = SzDuel_GetUnitEffect(pTask->ownerId >> 8, pTask->ownerId & 0xFF, 0);
        }
        card = SzDuel_GetUnitLoc(pTask->ownerId >> 8, pTask->ownerId & 0xFF);
        state = SzDuel_GetUnitKind(pTask->ownerId >> 8, pTask->ownerId & 0xFF) >> 5;
        index = 0;
        do {
            flags[index].low = flags[index].high = 15;
            index++;
        } while (index < 12);

        if (data != NULL) {
            selected = TaLogic001_IsUseRevive(nSide);
            if (state != 0) {
                if (SzDuel_GetField(card & 0xFF, card >> 8) == 9) {
                    selected = -1;
                }
                if (TaLogic_GetActionReaction(pTask->ownerId >> 8, pTask->ownerId & 0xFF, 0, 0, 6, 0) == 5) {
                    selected = -1;
                }
            }
            if (selected >= 0) {
                state = (selected >> 16) & 0xFFFF;
                card = TaLogic_GetGraveEntryAfterScreen(state, selected & 0xFF, *data & 0x3F);
                output->position = pTask->ownerId;
                output->command = 12;
                output->result = TaLogic_IsDefStyleUnit(pTask->ownerId >> 8, pTask->ownerId & 0xFF, output->value, 1, 0);
                output->count = 1;
                if (((*data >> 6) & 3) != 3) {
                    output->value = (nSide << 8) | card;
                } else {
                    output->value = (state << 8) | card;
                }
                TaLogic_InitRogicControl(pTask, fFirst);
                return 0;
            }
        }
        if (SzDuel_GetUnitStatus(pTask->ownerId >> 8, pTask->ownerId & 0xFF, 4) != 0) {
            SzDuel_SetUnitStatus(pTask->ownerId >> 8, pTask->ownerId & 0xFF, 0, 1);
            output->position = pTask->ownerId;
            output->command = 14;
            return 0;
        }
        return TaLogic_Seto_GetMinimumTask_RunMission(pTask, nSide, pInput, fFirst);
    }
}

/* Whether this duelist plays in its attacking mode this turn. */
s32 TaLogic001_IsActiveMode(void) {
    if (TaLogic_GetGraveCardCount(SzDuel_GetTurnOwner(), 3, 2) != 0 ||
        TaLogic_GetGraveCardCount(SzDuel_GetTurnOwner(), 3, 0x345) != 0 ||
        SearchUnitByRange(0, 0, SzDuel_GetTurnOwner(), 1, 0x2001C, 14) != 0) {
        return 1;
    }
    return 0;
}

/* Whether side `nSide` should use the life hourglass now (enough life points, graveyard monsters and free
   squares). */
s32 TaLogic001_IsUseLifeHourGlass(s32 nSide) {
    s32 i;
    u8 n = 0;
    s32 need;
    u8 m;
    s32 j;

    if (SzDuel_GetLP(nSide) < 0x5DC) {
        return 0;
    }
    need = TaLogic_GetGraveCardCount(nSide, 3, 2) & 0xFF;
    if (need > 0) {
        for (i = 0; i < 8; i++) {
            if (Ta_GetSummonablePieceWithOrder(nSide, i, 1) >= 0) {
                n++;
            }
        }
        if (n >= need && 5 - SzDuel_GetUnitMonsterCount(nSide) >= need) {
            return 1;
        }
    }
    m = 0;
    need = TaLogic_GetGraveCardCount(nSide, 3, 0) & 0xFF;
    if (need > 0) {
        for (j = 0; j < 8; j++) {
            if (Ta_GetSummonablePieceWithOrder(nSide, j, 1) >= 0) {
                m++;
            }
        }
        if (m >= need && 5 - SzDuel_GetUnitMonsterCount(nSide) >= need) {
            return 1;
        }
    }
    return 0;
}

/* Whether side `nSide` should use the brave hourglass now (enough life points, a target in range, 4+ monsters;
   the same search runs twice and the counts are added, as in the original). */
s32 TaLogic001_IsUseBraveHourGlass(s32 nSide) {
    s32 count;

    if (SzDuel_GetLP(nSide) < 0x5DC) {
        return 0;
    }
    count = SearchUnitByRange(0, 0, nSide, 1, 0x2001C, 14);
    count += SearchUnitByRange(0, 0, nSide, 1, 0x2001C, 14);
    if (count != 0) {
        if (SzDuel_GetUnitMonsterCount(nSide) >= 4) {
            return 1;
        }
    }
    return 0;
}

/* Whether side `nSide` has a dragon in range for Lord of Dragons. */
s32 TaLogic001_IsUseLordOfDragon(s32 nSide) {
    if (SearchUnitByRange(0, 0, nSide, 1, 0x2001C, 0xE) != 0) {
        return 1;
    }
    return (SearchUnitByRange(0, 0, nSide, 1, 0x1C, 0xE) != 0) ? 1 : 0;
}

/* Whether side `nSide` should use a revive card now. */
s32 TaLogic001_IsUseRevive(s32 nSide) {
    extern s32 SzDuel_GetGraveCount(s32);
    s32 i;

    if (SzDuel_GetUnitMonsterCount(nSide) >= 5) {
        return -1;
    }
    if ((TaLogic_GetGraveCardCount(nSide, 3, 0) > 0 || TaLogic_GetGraveCardCount(nSide, 3, 2) > 0) &&
        SearchUnitByRange(0, 0, nSide, 1, 0x179001C, 0xE) == 0) {
        for (i = 0; i < SzDuel_GetGraveCount(nSide); i++) {
            if (SzDuel_InqGrave(nSide, i) == 2) {
                return (nSide << 16) | i;
            }
        }
        for (i = 0; i < SzDuel_GetGraveCount(nSide == 0 ? 1 : 0); i++) {
            if (SzDuel_InqGrave(nSide == 0 ? 1 : 0, i) == 2) {
                return i | ((nSide == 0 ? 1 : 0) << 16);
            }
        }
        for (i = 0; i < SzDuel_GetGraveCount(nSide); i++) {
            if (SzDuel_InqGrave(nSide, i) == 0) {
                return (nSide << 16) | i;
            }
        }
        for (i = 0; i < SzDuel_GetGraveCount(nSide == 0 ? 1 : 0); i++) {
            if (SzDuel_InqGrave(nSide == 0 ? 1 : 0, i) == 0) {
                return i | ((nSide == 0 ? 1 : 0) << 16);
            }
        }
    }
    return -1;
}

extern int func_001E1030_b(int a, int b);
extern unsigned *func_001E0B70_b(int a, int b, int n);
extern int func_00111320_b(int x, int y, int z);
/* Whether side `side` has a dragon in range (either search key). */
static inline int func_00117870_either(int side)
{
    if (SearchUnitByRange(0, 0, side, 1, 0x2001C, 14) != 0) {
        return 1;
    }
    if (SearchUnitByRange(0, 0, side, 1, 28, 14) != 0) {
        return 1;
    }
    return 0;
}

/* Whether this duelist opens (turns face up) unit (nSide, nID) now: 0 no, 1 or 2 by its kind. */
int TaLogic_Seto_IsOpenUnit(int nSide, int nID, int pInfo)
{
    int kind;
    int side;
    unsigned *p;
    SzDuel_GetUnitLoc(nSide, nID);
    kind = func_001E1030_b(nSide, nID);
    side = Ta_IsUnitControl(nSide, nID);
    p = func_001E0B70_b(nSide, nID, 0);
    if (SzDuel_GetUnitStatus(nSide, nID, 4)) {
        return 0;
    }
    switch (SzDuel_GetUnitKind(nSide, nID) >> 5) {
    case 0:
        switch (kind) {
        case 83:
            if (func_00117870_either(side) == 1) {
                return 1;
            }
            break;
        case 146:
            if (TaUtil_GetGraveCardNum(side, 0) >= 6) {
                return 1;
            }
            break;
        }
        return 2;
    case 5:
        if (TaLogic_GetActionReaction(nSide, nID, 0, 0, 6, 0) == 5) {
            return 2;
        }
        if (TaLogic001_IsDoCerem(Ta_IsUnitControl(nSide, nID), kind) == 1) {
            if (SzDuel_GetField(nSide, nID) != 9) {
                return 1;
            }
        }
        break;
    case 1:
        if (TaLogic_GetActionReaction(nSide, nID, 0, 0, 6, 0) == 5) {
            return 2;
        }
        switch (*p >> 8) {
        case 13:
            return 1;
        case 2:
            if (TaLogic001_IsLandNearCntr(SzDuel_GetUnitLoc(nSide, nID)) == 1) {
                return 1;
            }
            break;
        case 20:
            return 2;
        default:
            return func_00111320_b(nSide, nID, pInfo);
        }
        break;
    default:
        return 2;
    }
    return 2;
}

/* The smaller of the two values. */
static inline s32 min_00117B10(s32 a, s32 b) {
    return (a < b) ? a : b;
}

/* The larger of the two values. */
static inline s32 max_00117B10(s32 a, s32 b) {
    return (a > b) ? a : b;
}

/* The board distance (steps across plus steps along). */
static inline s32 distance_00117B10(s32 x, s32 y) {
    return (max_00117B10(y, 3) - min_00117B10(y, 3)) +
           (max_00117B10(x, 3) - min_00117B10(x, 3));
}

/* Whether square `nLoc` is the centre, or next to a centre held by the opponent. */
s32 TaLogic001_IsLandNearCntr(s32 nLoc) {
    s32 controllingSide;
    s32 mapUnit;

    if (nLoc == 0x303) {
        return 1;
    }
    mapUnit = SzDuel_GetMapUnit(3, 3);
    if (mapUnit != 0) {
        controllingSide = Ta_IsUnitControl2((void *) mapUnit);
        if (controllingSide != SzDuel_GetTurnOwner()) {
            if (distance_00117B10(nLoc >> 8, nLoc & 0xFF) == 1) {
                return 1;
            }
        }
    }
    return 0;
}

/* Whether side `nSide` can play ritual card `nCardNo` now (it has the units to give up). */
s32 TaLogic001_IsDoCerem(s32 nSide, s32 nCardNo) {
    s32 sp20[3];

    Ta_GetCeremSacrifice(sp20, *(s32 *)((u8 *)TaHand_GetCardEffect(nCardNo, 0) + 4));
    if (Ta_GetSacrificeUnit(sp20, nSide) < 0) {
        return 0;
    }
    return 1;
}

/* How careful this duelist is about hidden cards (by its life points and monster count). */
s32 TaLogic_Seto_GetWarnHideLvl(s32 nSide) {
    if (SzDuel_GetLP(nSide) > 0x4B0) {
        if (SzDuel_GetUnitMonsterCount(nSide) >= 4) {
            return 0x2EE;
        } else {
            return 0x5DC;
        }
    } else {
        return 0x9C4;
    }
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
} Req_00117C90;

typedef struct {
    u8 pad0[0x160];
    u16 list[32];    /* 0x160 */
    u8 idx : 5;      /* 0x1A0 */
    u8 pad1A0 : 3;
    u8 pad1A1;
    u16 count;       /* 0x1A2 */
} Work_00117C90;

s32 TaLogic_GetInputQueFromMinimumTask_b(void *, void *, s32);

/* Computer duelist 1's controller (duelistControllers[1]): the buttons it presses this frame. With an empty input
   queue it plans its next task and turns it into buttons, then plays the queue back one button per frame; after
   600 frames it gives up the turn (0x20, then 0x800). */
s32 duelistController01(s32 wCursorPos, void *pCtl) {
    Req_00117C90 req;
    Work_00117C90 *w;
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
        if (TaLogic_Seto_GetMinimumTask(w, &req, wCursorPos) == 0) {
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

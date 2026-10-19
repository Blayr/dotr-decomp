/* Leader abilities: ranges and targets (Ta_IsLD*). */

#include "common.h"

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
    s32 loc;
    s32 temp_s1;
    s32 side;

    loc = SzDuel_GetUnitLoc(nSide, nID);
    side = Ta_GetCurrentSide(nSide, nID);
    temp_s1 = SzDuel_GetUnitKind(nSide, nID) & 0x1F;
    if (Ta_IsInLeaderRange(side, loc & 0xFF, loc >> 8) != 0 && Ta_IsLDAbl(sKey, side) != 0 &&
        temp_s1 == (SzDuel_GetUnitConstKind(side, 0) & 0x1F)) {
        return 1;
    }
    return 0;
}

/* Whether square `LOC` is in a leader's range with ability `sKey` for race `bRace` (`Self` picks the side). */
s32 Ta_IsLDRangeAvilityFromLoc(s32 LOC, s32 Self, s32 bRace, s32 sKey) {

    if (Ta_IsInLeaderRange(Self, LOC & 0xFF, LOC >> 8) != 0 && Ta_IsLDAbl(sKey, Self) != 0 &&
        bRace == (SzDuel_GetUnitConstKind(Self, 0) & 0x1F)) {
        return 1;
    }
    return 0;
}

/* Whether unit (nSide, nID) on square (nX, nZ) is in a leader's range with ability `sKey`. */
s32 Ta_IsLDRangeAvilityWithLocation(s32 nSide, s32 nID, s32 nX, s32 nZ, s32 sKey) {
    s32 temp_s0;
    s32 side;

    side = Ta_GetCurrentSide(nSide, nID);
    temp_s0 = SzDuel_GetUnitKind(nSide, nID) & 0x1F;
    if (Ta_IsInLeaderRange(side, nX, nZ) != 0 && Ta_IsLDAbl(sKey, side) != 0 &&
        temp_s0 == (SzDuel_GetUnitConstKind(side, 0) & 0x1F)) {
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

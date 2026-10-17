#include "common.h"

#define B310_ATTACK(kind, last)                                                              \
    if (Ta_IsLDRangeAvilityWithLocation(arg0, arg1, arg2, arg3, 0xB) != 0) {                                  \
        Ta_SetRangeVisual(pos & 0xFF, pos >> 8, 0, Ta_IsLDAbl(9, side), 1, 1, 0xB);          \
        arg4[0] = 0xFE;                                                                      \
        arg4[1] = 0;                                                                         \
        arg4[2] = side << 8;                                                                 \
        arg4[3] = 0x10;                                                                      \
        return 1;                                                                            \
    }                                                                                        \
    if (Ta_IsResistAll(arg0, arg1) != 0) {                                                    \
        return 0;                                                                            \
    }                                                                                        \
    arg4[0] = kind;                                                                          \
    arg4[1] = list[i];                                                                       \
    arg4[2] = (arg0 << 8) | arg1;                                                            \
    arg4[3] = last;                                                                          \
    return 0x101;

/* Checks whether a trap of side arg0 is set off by unit arg1 moving to square (arg2, arg3); the result into `arg4`
   (the names stay: a macro uses them). */
s32 Chk_TrapA(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 *arg4, s32 PrNo) {
    extern s32 SzDuel_GetUnitKindOfs();
    s32 side;
    s32 count;
    s32 maskA;
    u32 *info;
    s32 y;
    s32 pos;
    s32 maskB;
    s32 i;
    s32 ret;
    s32 list[5];
    s32 cell;
    s32 col;
    s32 row;
    s32 x;

    side = Ta_GetCurrentSide(arg0, arg1);
    maskA = 0;
    maskB = 0;
    if (arg1 == 0) {
        return 0;
    }
    if (!(PrNo & 0xFFFF)) {
        if (Ta_IsLDRange((side == 0) ? 1 : 0, arg2, arg3) != 0) {
            if ((SzDuel_GetUnitKind(arg0, arg1) >> 5) == 0) {
                if ((Ta_IsLDAbl(0x10, (side == 0) ? 1 : 0) != 0) && (Ta_IsLD_DestObj((side == 0) ? 1 : 0, SzDuel_GetUnitKind(arg0, arg1) & 0x1F) != 0)) {
                    maskA = ConvUnitIDtoFlagList(0U, arg0, arg1);
                }
                if ((Ta_IsLDAbl(0xF, (side == 0) ? 1 : 0) != 0) && (Ta_IsLD_CurseObj((side == 0) ? 1 : 0, SzDuel_GetUnitKind(arg0, arg1) & 0x1F) != 0)) {
                    maskB = ConvUnitIDtoFlagList(0U, arg0, arg1);
                }
                if (maskA > 0 || maskB > 0) {
                    arg4[0] = 0x71;
                    arg4[1] = maskA;
                    arg4[2] = maskB;
                    arg4[3] = 0x80000000;
                    return 0x101;
                }
            }
            maskA = 0;
            if ((Ta_IsLDAbl(0xD, (side == 0) ? 1 : 0) != 0) && (SzDuel_GetUnitStatus(arg0, arg1, 2) == 0) && (SzDuel_GetUnitStatus(arg0, arg1, 4) == 0)) {
                maskA = ConvUnitIDtoFlagList(0U, arg0, arg1);
            }
            if (maskA > 0) {
                arg4[0] = 0x71;
                arg4[1] = 0;
                arg4[2] = 0;
                arg4[3] = maskA | 0x80000000;
                return 0x10201;
            }
        }
    }
    info = Ta_GetUnitEffect(arg0, arg1, 1);
    if (info != NULL && (*info >> 8) == 7) {
        return 0;
    }
    if (Ta_SearchUncTypeNaturalEffectUserNum(0xF) > 0) {
        return 0;
    }
    count = 0;
    for (i = 0; i < 5; i++) {
        list[i] = -1;
    }
    for (x = 0; x < 7; x++) {
        for (y = 0; y < 7; y++) {
            cell = SzDuel_GetMapUnitID(x, y);
            if (cell >= 0) {
                row = cell >> 8;
                col = cell & 0xFF;
                if (side != Ta_GetCurrentSide(row, col)
                    && (((x < arg2) ? arg2 : x) - ((arg2 < x) ? arg2 : x)) + (((y < arg3) ? arg3 : y) - ((arg3 < y) ? arg3 : y)) < 2
                    && (SzDuel_GetUnitKind(row, col) >> 5) == 3) {
                    if (Ta_GetCurrentSide(arg0, arg1) != Ta_GetCurrentSide(row, col)) {
                        if (((PrNo >> 16) & 1) != 1 || SzDuel_GetUnitStatus(row, col, 4) != 0) {
                            list[count] = cell;
                            count++;
                        }
                    }
                }
            }
        }
    }
    if (count == 0) {
        return 0;
    }
    ret = Ta_IsActiveTrapB(0, 0x2E);
    if (ret >= 0) {
        arg4[0] = 0x66;
        arg4[1] = 1;
        arg4[2] = ret;
        arg4[3] = 0;
        return 1;
    }
    SortByOrder(list, 0, GetCap(0, count - 1));
    pos = SzDuel_GetUnitLoc(side, 0);
    for (i = 0; i < count; i++) {
        info = Ta_GetUnitEffect(list[i] >> 8, list[i] & 0xFF, 0);
        switch (SzDuel_GetUnitKindOfs(list[i] >> 8, list[i] & 0xFF)) {
        case 0:
            B310_ATTACK(0x2C, info[1])
        case 1:
            B310_ATTACK(0x2C, info[1])
        case 2:
            B310_ATTACK(0x2C, info[1])
        case 3:
            B310_ATTACK(0x2C, info[1])
        case 4:
            B310_ATTACK(0x2C, info[1])
        case 5:
            B310_ATTACK(0x2C, info[1])
        case 6:
            if ((SzDuel_GetUnitKind(arg0, arg1) >> 5) == 0 && TaUtil_GetUnitAP(arg0, arg1, arg2, arg3) < 0x3E9) {
                B310_ATTACK(0x2D, 0)
            }
            break;
        case 7:
            if ((SzDuel_GetUnitKind(arg0, arg1) >> 5) == 0 && TaUtil_GetUnitAP(arg0, arg1, arg2, arg3) < 0x5DD) {
                B310_ATTACK(0x2D, 0)
            }
            break;
        case 8:
            if ((SzDuel_GetUnitKind(arg0, arg1) >> 5) == 0 && TaUtil_GetUnitAP(arg0, arg1, arg2, arg3) < 0x7D1) {
                B310_ATTACK(0x2D, 0)
            }
            break;
        case 9:
            if ((SzDuel_GetUnitKind(arg0, arg1) >> 5) == 0 && TaUtil_GetUnitAP(arg0, arg1, arg2, arg3) < 0xBB9) {
                B310_ATTACK(0x2D, 0)
            }
            break;
        case 10:
            if ((SzDuel_GetUnitKind(arg0, arg1) >> 5) == 0 && TaUtil_GetUnitAP(arg0, arg1, arg2, arg3) < 0xFA1) {
                B310_ATTACK(0x2D, 0)
            }
            break;
        case 11:
            B310_ATTACK(0x2E, 0)
        case 12:
            if ((SzDuel_GetUnitKind(arg0, arg1) >> 5) != 0) {
                B310_ATTACK(0x2D, 0)
            }
            break;
        }
    }
    return 0;
}

/* Sorts units list[left..right] by summon order (quicksort). */
void SortByOrder(s32 *list, s32 left, s32 right) {
    s32 cost;
    s32 i;
    s32 last;

    if (left < right) {
        Swap(list, left, (left + right) >> 1);
        last = left;
        for (i = left + 1; i <= right; i++) {
            cost = SzDuel_GetUnitSummonOrder(list[i] >> 8, list[i] & 0xFF);
            if (cost > SzDuel_GetUnitSummonOrder(list[left] >> 8, list[left] & 0xFF)) {
                Swap(list, ++last, i);
            }
        }
        Swap(list, left, last);
        SortByOrder(list, left, last);
        SortByOrder(list, last + 1, right);
    }
}

/* Swaps Buf[i] and Buf[j]. */
void Swap(s32 *Buf, s32 i, s32 j) {
    s32 temp_a0;
    s32 *temp_a1;
    s32 *temp_a2;

    temp_a1 = Buf + i;
    temp_a2 = Buf + j;
    temp_a0 = *temp_a1;
    *temp_a1 = *temp_a2;
    *temp_a2 = temp_a0;
}

/* Whether trap unit (nTrapSide, nTrapID) goes off against unit (nSide, nID) on square (nX, nZ). */
s32 TaTrapA_IsTrapAct(s32 nTrapSide, s32 nTrapID, s32 nSide, s32 nID, s32 nX, s32 nZ) {
    switch (SzDuel_GetUnitKindOfs()) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        if ((SzDuel_GetUnitKind(nSide, nID) >> 5) == 0) {
            return (Ta_IsLDRangeAvilityWithLocation(nSide, nID, nX, nZ, 0xB) != 0) ? 0 : 1;
        }
        break;
    case 6:
        if ((SzDuel_GetUnitKind(nSide, nID) >> 5) == 0 && TaUtil_GetUnitAP(nSide, nID, nX, nZ) < 0x1F5) {
            return (Ta_IsLDRangeAvilityWithLocation(nSide, nID, nX, nZ, 0xB) != 0) ? 0 : 1;
        }
        break;
    case 7:
        if ((SzDuel_GetUnitKind(nSide, nID) >> 5) == 0 && TaUtil_GetUnitAP(nSide, nID, nX, nZ) < 0x3E9) {
            return (Ta_IsLDRangeAvilityWithLocation(nSide, nID, nX, nZ, 0xB) != 0) ? 0 : 1;
        }
        break;
    case 8:
        if ((SzDuel_GetUnitKind(nSide, nID) >> 5) == 0 && SzDuel_GetUnitAP(nSide, nID, 0) < 0x5DD) {
            return (Ta_IsLDRangeAvilityWithLocation(nSide, nID, nX, nZ, 0xB) != 0) ? 0 : 1;
        }
        break;
    case 9:
        if ((SzDuel_GetUnitKind(nSide, nID) >> 5) == 0 && TaUtil_GetUnitAP(nSide, nID, nX, nZ) < 0x7D1) {
            return (Ta_IsLDRangeAvilityWithLocation(nSide, nID, nX, nZ, 0xB) != 0) ? 0 : 1;
        }
        break;
    case 10:
        if ((SzDuel_GetUnitKind(nSide, nID) >> 5) == 0 && TaUtil_GetUnitAP(nSide, nID, nX, nZ) < 0xBB9) {
            return (Ta_IsLDRangeAvilityWithLocation(nSide, nID, nX, nZ, 0xB) != 0) ? 0 : 1;
        }
        break;
    case 11:
        return 1;
    case 12:
        if ((SzDuel_GetUnitKind(nSide, nID) >> 5) != 0) {
            return (Ta_IsLDRangeAvilityWithLocation(nSide, nID, nX, nZ, 0xB) != 0) ? 0 : 1;
        }
        break;
    default:
        return 0;
    }
    return 0;
}

/* Sets the bit of unit (nSide, nID) in unit flag list `FlagLst`. */
s32 ConvUnitIDtoFlagList(u32 FlagLst, s32 nSide, s32 nID) {
    if (nSide == 0) {
        return (FlagLst & 0x7FF) | (((FlagLst >> 0xB) | (1 << (0xA - nID))) << 0xB);
    }
    return FlagLst | (1 << (0xA - nID));
}

/* Clears the bit of unit (nSide, nID) in unit flag list `FlagLst`. */
s32 ConvUnitIDtoFlagList_OFF(u32 FlagLst, s32 nSide, s32 nID) {
    s32 temp_a0;
    s32 temp_s2;

    if (nSide == 0) {
        temp_a0 = 0x15 - nID;
        return ((((u32) (FlagLst >> 0xB) >> (0xA - nID)) & ~1) << temp_a0) | (FlagLst & Ta_ConvBitLengthToNumericLength(temp_a0));
    }
    temp_s2 = FlagLst & ~Ta_ConvBitLengthToNumericLength(0xB - nID);
    return temp_s2 | (FlagLst & Ta_ConvBitLengthToNumericLength(0xA - nID));
}

/* A mask of the low `bit` bits (2^bit - 1). */
s32 Ta_ConvBitLengthToNumericLength(s32 bit) {
    extern s32 func_001A2858(s32, s32);
    extern s32 func_001A2EB0(s32);
    extern s32 func_001A2F68(s32);
    s32 temp_s0;
    s32 var_s0;
    s32 i;

    i = 0;
    var_s0 = 0;
    for (; i < bit; i++) {
        temp_s0 = func_001A6BE8(0x4000000000000000LL, func_001A2EB0(i));
        var_s0 = func_001A2F68(func_001A2858(func_001A2EB0(var_s0), temp_s0));
    }
    return var_s0;
}

/* The units of side `sSide` as seen from side `rSide`, into `wUnitLst`; returns how many. */
void TaUtil_GetUnitLst(s32 rSide, s32 sSide, s16 *wUnitLst) {
    s16 *var_s0;
    s32 criteria;
    s32 player;
    s32 i;
    u16 player_bits;
    s32 var_v1;

    i = 1;
    var_s0 = wUnitLst;
    criteria = sSide;
    player = rSide;
    player_bits = (u16)(player << 8);
    do {
        if ((SzDuel_GetUnit(player, i) != 0) && (Ta_SideMatch(player, Ta_GetCurrentSide(player, i), criteria) == 1)) {
            *var_s0 = player_bits | i;
            var_s0++;
        }
        i += 1;
    } while (i < 0xB);
    i = 1;
    do {
        if (SzDuel_GetUnit((player == 0) ? 1 : 0, i) != 0) {
            if (Ta_SideMatch(player, Ta_GetCurrentSide((player == 0) ? 1 : 0, i), criteria) == 1) {
                if (player == 0) {
                    var_v1 = 1;
                } else {
                    var_v1 = 0;
                }
                *var_s0 = i | (var_v1 << 8);
                var_s0++;
            }
        }
        i += 1;
    } while (i < 0xB);
}

/* The units of side `sSide` (relative to `rSide`) in range `sRange` of square (nX, nZ) matching `sKey`, as a unit
   flag list. */
s32 SearchUnitByRange(s32 nX, s32 nZ, s32 rSide, s32 sSide, s32 sKey, s32 sRange) {
    u32 score;
    u32 hi;
    u16 lo;
    u32 bestA;
    u32 bestB;
    s32 idx;
    s32 side;
    s32 card;
    s32 v;
    s32 y;
    s32 x;
    s32 id;
    s32 best2;
    s32 bestSide;
    u32 res;
    s32 i;
    u16 *p;
    s32 idxB;
    s32 sideB;
    s32 idxC;
    s32 sideC;
    u16 list[24];

    p = list;
    best2 = 0x270F;
    bestSide = -1;
    res = 0;
    bestA = 0;
    bestB = 0x27100000;
    for (i = 0; i < 22; i++) {
        list[i] = 0xFFFF;
    }
    func_0024C910(rSide, sSide, (s16 *)list);
    switch (sRange) {
    case 22:
        for (i = 0; i < func_0027C670(list); i++) {
            if ((*p & 0xFF) > 0) {
                id = func_001E1090(*p >> 8, *p & 0xFF);
                if (func_001E22B0(id & 0xFF, id >> 8) == 2) {
                    v = func_001E0700(*p >> 8, *p & 0xFF);
                    switch (sKey & 0xFFFF) {
                    case 0x1D:
                        if ((v >> 5) == 0 && func_0024DD80(rSide, func_0024DE70(*p >> 8, *p & 0xFF), sSide) == 1) {
                            res = func_0024C780(res, *p >> 8, *p & 0xFF);
                        }
                        break;
                    case 0x1F:
                    case 0x34:
                        res = func_0024C780(res, *p >> 8, *p & 0xFF);
                        break;
                    }
                }
            }
            p++;
        }
        break;
    case 24:
        for (i = 0; i < func_0027C670(list); i++) {
            if ((*p & 0xFF) > 0) {
                id = func_001E1090(*p >> 8, *p & 0xFF);
                if (func_001E22B0(id & 0xFF, id >> 8) == 4) {
                    v = func_001E0700(*p >> 8, *p & 0xFF);
                    switch (sKey & 0xFFFF) {
                    case 0x1D:
                        if ((v >> 5) == 0 && func_0024DD80(rSide, func_0024DE70(*p >> 8, *p & 0xFF), sSide) == 1) {
                            res = func_0024C780(res, *p >> 8, *p & 0xFF);
                        }
                        break;
                    case 0x1F:
                    case 0x34:
                        res = func_0024C780(res, *p >> 8, *p & 0xFF);
                        break;
                    }
                }
            }
            p++;
        }
        break;
    case 23:
        for (i = 0; i < func_0027C670(list); i++) {
            if ((*p & 0xFF) > 0) {
                id = func_001E1090(*p >> 8, *p & 0xFF);
                if (func_001E22B0(id & 0xFF, id >> 8) == 3) {
                    v = func_001E0700(*p >> 8, *p & 0xFF);
                    switch (sKey & 0xFFFF) {
                    case 0x1D:
                        if ((v >> 5) == 0 && func_0024DD80(rSide, func_0024DE70(*p >> 8, *p & 0xFF), sSide) == 1) {
                            res = func_0024C780(res, *p >> 8, *p & 0xFF);
                        }
                        break;
                    case 0x1F:
                    case 0x34:
                        res = func_0024C780(res, *p >> 8, *p & 0xFF);
                        break;
                    }
                }
            }
            p++;
        }
        break;
    case 20:
        for (i = 0; i < func_0027C670(list); i++) {
            if ((*p & 0xFF) > 0) {
                id = func_001E1090(*p >> 8, *p & 0xFF);
                if (func_001E22B0(id & 0xFF, id >> 8) == 0) {
                    v = func_001E0700(*p >> 8, *p & 0xFF);
                    switch (sKey & 0xFFFF) {
                    case 0x1D:
                        if ((v >> 5) == 0 && func_0024DD80(rSide, func_0024DE70(*p >> 8, *p & 0xFF), sSide) == 1) {
                            res = func_0024C780(res, *p >> 8, *p & 0xFF);
                        }
                        break;
                    case 0x1F:
                    case 0x34:
                        res = func_0024C780(res, *p >> 8, *p & 0xFF);
                        break;
                    }
                }
            }
            p++;
        }
        break;
    case 29:
        for (i = 0; i < func_0027C670(list); i++) {
            if ((*p & 0xFF) > 0) {
                id = func_001E1090(*p >> 8, *p & 0xFF);
                if (func_001E22B0(id & 0xFF, id >> 8) == 9) {
                    v = func_001E0700(*p >> 8, *p & 0xFF);
                    switch (sKey & 0xFFFF) {
                    case 0x1D:
                        if ((v >> 5) == 0 && func_0024DD80(rSide, func_0024DE70(*p >> 8, *p & 0xFF), sSide) == 1) {
                            res = func_0024C780(res, *p >> 8, *p & 0xFF);
                        }
                        break;
                    case 0x1F:
                    case 0x34:
                        res = func_0024C780(res, *p >> 8, *p & 0xFF);
                        break;
                    }
                }
            }
            p++;
        }
        break;
    case 18:
        for (i = 0; i < func_0027C670(list); i++) {
            if ((*p & 0xFF) > 0) {
                id = func_001E1090(*p >> 8, *p & 0xFF);
                if ((id & 0xFF) == nX || (id >> 8) == nZ) {
                    v = func_001E0700(*p >> 8, *p & 0xFF);
                    switch (sKey & 0xFFFF) {
                    case 29:
                        if ((v >> 5) == 0 && func_0024DD80(rSide, func_0024DE70(*p >> 8, *p & 0xFF), sSide) == 1) {
                            res = func_0024C780(res, *p >> 8, *p & 0xFF);
                        }
                        break;
                    case 30:
                        if ((v >> 5) != 0 && func_0024DD80(rSide, func_0024DE70(*p >> 8, *p & 0xFF), sSide) == 1) {
                            res = func_0024C780(res, *p >> 8, *p & 0xFF);
                        }
                        break;
                    case 31:
                        res = func_0024C780(res, *p >> 8, *p & 0xFF);
                        break;
                    }
                }
            }
            p++;
        }
        break;
    default:
        for (i = 0; i < func_0027C670(list); i++) {
            id = func_001E1090(*p >> 8, *p & 0xFF);
            if (((((id & 0xFF) < nX) ? nX : (id & 0xFF)) - ((nX < (id & 0xFF)) ? nX : (id & 0xFF)) + ((((id >> 8) < nZ) ? nZ : (id >> 8)) - ((nZ < (id >> 8)) ? nZ : (id >> 8))) <= sRange)) {
                y = id >> 8;
                x = id & 0xFF;
                v = func_001E0700(*p >> 8, *p & 0xFF);
                card = *p;
                switch (sKey & 0xFFFF) {
                case 0x1F:
                case 0x2D:
                case 0x34:
                case 0x3D:
                    res = func_0024C780(res, card >> 8, card & 0xFF);
                    break;
                case 0x1E:
                    if ((v >> 5) != 0) {
                        res = func_0024C780(res, card >> 8, card & 0xFF);
                    }
                    break;
                case 0x1D:
                    if ((v >> 5) == 0) {
                        res = func_0024C780(res, card >> 8, card & 0xFF);
                    }
                    break;
                case 0:
                    if ((v >> 5) == 0 && (v & 0x1F) == 0) {
                        res = func_0024C780(res, card >> 8, card & 0xFF);
                    }
                    break;
                case 1:
                    if ((v >> 5) == 0 && (v & 0x1F) == 1) {
                        res = func_0024C780(res, card >> 8, card & 0xFF);
                    }
                    break;
                case 2:
                    if ((v >> 5) == 0 && (v & 0x1F) == 2) {
                        res = func_0024C780(res, card >> 8, card & 0xFF);
                    }
                    break;
                case 3:
                    if ((v >> 5) == 0 && (v & 0x1F) == 3) {
                        res = func_0024C780(res, card >> 8, card & 0xFF);
                    }
                    break;
                case 4:
                    if ((v >> 5) == 0 && (v & 0x1F) == 4) {
                        res = func_0024C780(res, card >> 8, card & 0xFF);
                    }
                    break;
                case 5:
                    if ((v >> 5) == 0 && (v & 0x1F) == 5) {
                        res = func_0024C780(res, card >> 8, card & 0xFF);
                    }
                    break;
                case 6:
                    if ((v >> 5) == 0 && (v & 0x1F) == 6) {
                        res = func_0024C780(res, card >> 8, card & 0xFF);
                    }
                    break;
                case 7:
                    if ((v >> 5) == 0 && (v & 0x1F) == 7) {
                        res = func_0024C780(res, card >> 8, card & 0xFF);
                    }
                    break;
                case 8:
                    if ((v >> 5) == 0 && (v & 0x1F) == 8) {
                        res = func_0024C780(res, card >> 8, card & 0xFF);
                    }
                    break;
                case 9:
                    if ((v >> 5) == 0 && (v & 0x1F) == 9) {
                        res = func_0024C780(res, card >> 8, card & 0xFF);
                    }
                    break;
                case 10:
                    if ((v >> 5) == 0 && (v & 0x1F) == 10) {
                        res = func_0024C780(res, card >> 8, card & 0xFF);
                    }
                    break;
                case 11:
                    if ((v >> 5) == 0 && (v & 0x1F) == 11) {
                        res = func_0024C780(res, card >> 8, card & 0xFF);
                    }
                    break;
                case 12:
                    if ((v >> 5) == 0 && (v & 0x1F) == 12) {
                        res = func_0024C780(res, card >> 8, card & 0xFF);
                    }
                    break;
                case 13:
                    if ((v >> 5) == 0 && (v & 0x1F) == 13) {
                        res = func_0024C780(res, card >> 8, card & 0xFF);
                    }
                    break;
                case 14:
                    if ((v >> 5) == 0 && (v & 0x1F) == 14) {
                        res = func_0024C780(res, card >> 8, card & 0xFF);
                    }
                    break;
                case 15:
                    if ((v >> 5) == 0 && (v & 0x1F) == 15) {
                        res = func_0024C780(res, card >> 8, card & 0xFF);
                    }
                    break;
                case 16:
                    if ((v >> 5) == 0 && (v & 0x1F) == 16) {
                        res = func_0024C780(res, card >> 8, card & 0xFF);
                    }
                    break;
                case 17:
                    if ((v >> 5) == 0 && (v & 0x1F) == 17) {
                        res = func_0024C780(res, card >> 8, card & 0xFF);
                    }
                    break;
                case 18:
                    if ((v >> 5) == 0 && (v & 0x1F) == 18) {
                        res = func_0024C780(res, card >> 8, card & 0xFF);
                    }
                    break;
                case 19:
                    if ((v >> 5) == 0 && (v & 0x1F) == 19) {
                        res = func_0024C780(res, card >> 8, card & 0xFF);
                    }
                    break;
                case 0x3B:
                    if ((v >> 5) == 0 && (v & 0x1F) == 20) {
                        res = func_0024C780(res, card >> 8, card & 0xFF);
                    }
                    break;
                case 0x14:
                    side = card >> 8;
                    if ((v >> 5) == 0) {
                        idx = card & 0xFF;
                        if (func_001E0830(side, idx) == 0) {
                            res = func_0024C780(res, side, idx);
                        }
                    }
                    break;
                case 0x15:
                    side = card >> 8;
                    if ((v >> 5) == 0) {
                        idx = card & 0xFF;
                        if (func_001E0830(side, idx) == 1) {
                            res = func_0024C780(res, side, idx);
                        }
                    }
                    break;
                case 0x16:
                    side = card >> 8;
                    if ((v >> 5) == 0) {
                        idx = card & 0xFF;
                        if (func_001E0830(side, idx) == 2) {
                            res = func_0024C780(res, side, idx);
                        }
                    }
                    break;
                case 0x18:
                    side = card >> 8;
                    if ((v >> 5) == 0) {
                        idx = card & 0xFF;
                        if (func_001E0830(side, idx) == 4) {
                            res = func_0024C780(res, side, idx);
                        }
                    }
                    break;
                case 0x17:
                    side = card >> 8;
                    if ((v >> 5) == 0) {
                        idx = card & 0xFF;
                        if (func_001E0830(side, idx) == 3) {
                            res = func_0024C780(res, side, idx);
                        }
                    }
                    break;
                case 0x19:
                    side = card >> 8;
                    if ((v >> 5) == 0) {
                        idx = card & 0xFF;
                        if (func_001E0830(side, idx) == 5) {
                            res = func_0024C780(res, side, idx);
                        }
                    }
                    break;
                case 0x3C:
                    side = card >> 8;
                    idx = card & 0xFF;
                    if (func_001E2100(side, idx, 4) == 0) {
                        res = func_0024C780(res, side, idx);
                    }
                    break;
                case 0x35:
                    side = card >> 8;
                    idx = card & 0xFF;
                    if (func_001E2100(side, idx, 3) == 0) {
                        res = func_0024C780(res, side, idx);
                    }
                    break;
                case 0x36:
                    if ((v >> 5) == 4 || (v >> 5) == 3) {
                        side = card >> 8;
                        idx = card & 0xFF;
                        if (func_001E2100(side, idx, 4) != 0) {
                            res = func_0024C780(res, side, idx);
                        }
                    }
                    break;
                case 0x21:
                    sideB = card >> 8;
                    if ((v >> 5) == 0) {
                        idxB = card & 0xFF;
                        id = func_001E1090(sideB, idxB);
                        score = (func_002509E0(sideB, idxB, id & 0xFF, id >> 8) << 16) | func_00250B40(sideB, idxB, id & 0xFF, id >> 8);
                        if ((bestA >> 16) < (score >> 16)) {
                            best2 = func_001E13C0(sideB, idxB);
                            bestA = score;
                            bestSide = sideB;
                            res = func_0024C780(0, sideB, idxB);
                        } else if ((bestA >> 16) == (score >> 16)) {
                            lo = bestA;
                            if (lo == (score & 0xFFFF)) {
                                if (best2 == func_001E13C0(sideB, idxB)) {
                                    if (bestSide == sSide) {
                                        bestA = score;
                                        bestSide = sideB;
                                        res = func_0024C780(0, sideB, idxB);
                                    }
                                } else if (func_001E13C0(sideB, idxB) < best2) {
                                    best2 = func_001E13C0(sideB, idxB);
                                    bestA = score;
                                    bestSide = sideB;
                                    res = func_0024C780(0, sideB, idxB);
                                }
                            } else if (lo < (score & 0xFFFF)) {
                                best2 = func_001E13C0(sideB, idxB);
                                bestA = score;
                                bestSide = sideB;
                                res = func_0024C780(0, sideB, idxB);
                            }
                        }
                    }
                    break;
                case 0x20:
                    sideC = card >> 8;
                    if ((v >> 5) == 0) {
                        idxC = card & 0xFF;
                        id = func_001E1090(sideC, idxC);
                        score = (func_002509E0(sideC, idxC, id & 0xFF, id >> 8) << 16) | func_00250B40(sideC, idxC, id & 0xFF, id >> 8);
                        hi = score >> 16;
                        if (hi < (bestB >> 16)) {
                            best2 = func_001E13C0(sideC, idxC);
                            bestB = score;
                            bestSide = sideC;
                            res = func_0024C780(0, sideC, idxC);
                        } else {
                            if (bestB == hi) {
                            if ((bestB & 0xFFFF) == (score & 0xFFFF)) {
                                if (best2 == func_001E13C0(sideC, idxC)) {
                                    if (bestSide == sSide) {
                                        bestB = score;
                                        bestSide = sideC;
                                        res = func_0024C780(0, sideC, idxC);
                                    }
                                } else if (func_001E13C0(sideC, idxC) < best2) {
                                    best2 = func_001E13C0(sideC, idxC);
                                    bestB = score;
                                    bestSide = sideC;
                                    res = func_0024C780(0, sideC, idxC);
                                }
                            } else if ((bestB & 0xFFFF) > (score & 0xFFFF)) {
                                best2 = func_001E13C0(sideC, idxC);
                                bestB = score;
                                bestSide = sideC;
                                res = func_0024C780(0, sideC, idxC);
                            }
                        }
                        }
                    }
                    break;
                case 0x25:
                    if ((v >> 5) == 0) {
                        side = card >> 8;
                        idx = card & 0xFF;
                        if (func_002509E0(side, idx, x, y) <= (sKey >> 16 & 0xFFFF)) {
                            res = func_0024C780(res, side, idx);
                        }
                    }
                    break;
                case 0x24:
                    if ((v >> 5) == 0) {
                        side = card >> 8;
                        idx = card & 0xFF;
                        if (func_002509E0(side, idx, x, y) >= (sKey >> 16 & 0xFFFF)) {
                            res = func_0024C780(res, side, idx);
                        }
                    }
                    break;
                case 0x3A:
                    if ((v >> 5) == 0) {
                        side = card >> 8;
                        idx = card & 0xFF;
                        if (func_00250B40(side, idx, x, y) <= (sKey >> 16 & 0xFFFF)) {
                            res = func_0024C780(res, side, idx);
                        }
                    }
                    break;
                case 0x39:
                    if ((v >> 5) == 0) {
                        side = card >> 8;
                        idx = card & 0xFF;
                        if (func_00250B40(side, idx, x, y) >= (sKey >> 16 & 0xFFFF)) {
                            res = func_0024C780(res, side, idx);
                        }
                    }
                    break;
                case 0x37:
                    if ((v >> 5) == 0 && (v & 0x1F) == 0) {
                        side = card >> 8;
                        idx = card & 0xFF;
                        if (func_002509E0(side, idx, x, y) <= (sKey >> 16 & 0xFFFF)) {
                            res = func_0024C780(res, side, idx);
                        }
                    }
                    break;
                case 0x22:
                    if ((card & 0xFF) == 0) {
                        res = func_0024C780(res, card >> 8, card & 0xFF);
                    }
                    break;
                case 0x1C: {
                    extern s32 func_001E1030();

                    side = card >> 8;
                    idx = card & 0xFF;
                    if ((sKey >> 16) == func_001E1030(side, idx)) {
                        res = func_0024C780(res, side, idx);
                    }
                    break;
                }
                }
            }
            p++;
        }
        break;
    }
    return res;
}

/* Whether side `cSide` is the side `sSide` means relative to `rSide` (own, other, either). */
s32 Ta_SideMatch(s32 rSide, s32 cSide, s32 sSide) {
    switch (sSide) {
    case 0:
        return 0;
    case 1:
        return (rSide == cSide) ? 1 : 0;
    case 2:
        if (rSide == ((cSide == 0) ? 1 : 0)) {
            return 1;
        }
        return 0;
    case 3:
        return 1;
    default:
        return 0;
    }
}

/* The side an effect owner `eOwner` means for side `nSide`. */
s32 Ta_GetEOwnerSide(s32 nSide, s32 eOwner) {
    switch (eOwner) {
    case 1:
        return nSide;
    case 2:
        return (nSide == 0) ? 1 : 0;
    default:
        return -1;
    }
}

/* The side unit (nSide, nID) currently plays for (a controlled unit plays for the other side). */
s32 Ta_GetCurrentSide(s32 nSide, s32 nID) {
    if (SzDuel_GetUnitStatus(nSide, nID, 1) != 0) {
        return (nSide == 0) ? 1 : 0;
    }
    return nSide;
}

/* The field bonus of field type `Land` for a unit's card (record `vInfo`). */
s32 CheckLandAgreement(s32 Land, void *vInfo) {
    if (((s32) *((u8 *)vInfo + 0x3E) >> 5) != 0 ||
        *((u8 *)vInfo + 0x45) == 0) {
        return 0;
    }
    return Do_CheckLandAgreement(Land, vInfo);
}

/* The field bonus of field type `Land` for unit (nSide, nID). */
s32 CheckLandAgreement2(s32 Land, s32 nSide, s32 nID) {
    if ((SzDuel_GetUnitKind(nSide, nID) >> 5) != 0 || nID == 0) {
        return 0;
    }
    return Do_CheckLandAgreement(Land, (void *)SzDuel_GetUnit(nSide, nID));
}

struct jp_6537d {
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
struct jp_65648 {
    unsigned int dwID;
    unsigned int dwParam;
};
struct jp_65767;
struct jp_64b6d {
    struct jp_6537d *pConstInfo;
    struct jp_65767 *pCardReq;
    struct jp_65648 aVarEffIdx[5];
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

/* Whether a card's type gets a bonus (or a penalty) on field type `land`. */
int Do_CheckLandAgreement(int land, void *vInfo_v)
{
    struct jp_64b6d * vInfo = vInfo_v;
    int kind;
    int ret;

    if ((vInfo->bVarKind >> 5) != 0) {
        return 0;
    }
    kind = vInfo->bVarKind & 0x1f;
    switch (land) {
    case 9:
        if (kind == 20) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 7:
    case 8:
        ret = 0;
        break;
    case 6:
        if (Ta_GetToonAgreement(vInfo->wCardNo) != 0) {
            ret = 1;
        } else {
            ret = 2;
        }
        break;
    case 3:
        switch (kind) {
        case 3:
        case 4:
            ret = 1;
            break;
        case 1:
            ret = 2;
            break;
        default:
            ret = 0;
            break;
        }
        break;
    case 0:
        switch (kind) {
        case 4:
        case 5:
        case 9:
        case 17:
        case 19:
            ret = 1;
            break;
        case 7:
            ret = 2;
            break;
        default:
            ret = 0;
            break;
        }
        break;
    case 2:
        switch (kind) {
        case 0:
        case 6:
        case 8:
        case 15:
            ret = 1;
            break;
        case 2:
            ret = 2;
            break;
        default:
            ret = 0;
            break;
        }
        break;
    case 1:
        switch (kind) {
        case 2:
        case 10:
        case 14:
        case 18:
            ret = 1;
            break;
        case 19:
        case 12:
        case 13:
        case 16:
            ret = 2;
            break;
        default:
            ret = 0;
            break;
        }
        break;
    case 4:
        switch (kind) {
        case 12:
        case 13:
        case 15:
        case 16:
            ret = 1;
            break;
        case 14:
        case 17:
            ret = 2;
            break;
        default:
            ret = 0;
            break;
        }
        break;
    case 5:
        switch (kind) {
        case 2:
        case 1:
        case 7:
            ret = 1;
            break;
        case 8:
            ret = 2;
            break;
        default:
            ret = 0;
            break;
        }
        break;
    default:
        ret = 0;
        break;
    }
    return ret;
}

/* The squares side `nSide` can summon to (`RefLab` adds the labyrinth rule). */
s32 Ta_GetSummonablePiece(s32 nSide, s32 RefLab) {
    s32 index;
    s32 result;
    u8 filter;
    s32 high;
    s32 low;

    filter = RefLab;
    for (index = 0; index < 8; index++) {
        if ((result = Ta_GetSommonPiecePreference(nSide, index)) < 0) {
            continue;
        }
        if (!filter) {
            if (SzDuel_GetMapUnitID(result & 0xFF, result >> 8) < 0) {
                return result;
            }
        } else {
            low = result & 0xFF;
            high = result >> 8;
            if (SzDuel_GetField(low, high) != 8 &&
                SzDuel_GetMapUnitID(low, high) < 0) {
                return result;
            }
        }
    }
    return -1;
}

/* The squares side `nSide` can summon to, in preference order `sOrder`. */
s32 Ta_GetSummonablePieceWithOrder(s32 nSide, s32 sOrder, s32 RefLab) {
    s32 index;
    s32 count;
    s32 value;
    s32 mode;
    s32 high;
    s32 low;

    mode = RefLab & 0xFF;
    index = 0;
    count = 0;
    do {
        if ((value = Ta_GetSommonPiecePreference(nSide, index)) < 0) {
            continue;
        }
        if (mode == 0) {
            if (SzDuel_GetMapUnitID(value & 0xFF, value >> 8) >= 0) {
                continue;
            }
            if (sOrder == count) {
                return value;
            }
            count++;
        } else {
            low = value & 0xFF;
            high = value >> 8;
            if ((SzDuel_GetField(low, high) != 8) && (SzDuel_GetMapUnitID(low, high) < 0)) {
                if (sOrder == count) {
                    return value;
                }
                count++;
            }
        }
    } while (++index < 8);
    return -1;
}

/* The squares side `nSide` prefers for a summon, by preference `nPr`. */
s32 Ta_GetSommonPiecePreference(s32 nSide, u32 nPr) {
    u32 pos;
    u32 next;
    u32 row;

    pos = SzDuel_GetUnitLoc(nSide, 0);
    switch (nSide) {
    case 0:
        switch (nPr) {
        case 0:
            return (((pos >> 8) - 1) << 8) | (pos & 0xFF);
        case 1:
            next = (pos >> 8) + 1;
            return (next < 7) ? ((next << 8) | (pos & 0xFF)) : -1;
        case 2:
            next = (pos & 0xFF) + 1;
            return (next < 7) ? (((pos >> 8) << 8) | next) : -1;
        case 3:
            return ((pos >> 8) << 8) | ((pos & 0xFF) - 1);
        case 4:
            next = (pos & 0xFF) + 1;
            return (next < 7) ? ((((pos >> 8) - 1) << 8) | next) : -1;
        case 5:
            return (((pos >> 8) - 1) << 8) | ((pos & 0xFF) - 1);
        case 6:
            next = (pos & 0xFF) + 1;
            if (next < 7) {
                row = (pos >> 8) + 1;
                if (row < 7) {
                    return (row << 8) | next;
                }
            }
            return -1;
        case 7:
            next = (pos >> 8) + 1;
            return (next < 7) ? ((next << 8) | ((pos & 0xFF) - 1)) : -1;
        default:
            return -1;
        }
    case 1:
        switch (nPr) {
        case 0:
            next = (pos >> 8) + 1;
            return (next < 7) ? ((next << 8) | (pos & 0xFF)) : -1;
        case 1:
            return (((pos >> 8) - 1) << 8) | (pos & 0xFF);
        case 2:
            return ((pos >> 8) << 8) | ((pos & 0xFF) - 1);
        case 3:
            next = (pos & 0xFF) + 1;
            return (next < 7) ? (((pos >> 8) << 8) | next) : -1;
        case 4:
            next = (pos >> 8) + 1;
            return (next < 7) ? ((next << 8) | ((pos & 0xFF) - 1)) : -1;
        case 5:
            next = (pos & 0xFF) + 1;
            if (next < 7) {
                row = (pos >> 8) + 1;
                if (row < 7) {
                    return (row << 8) | next;
                }
            }
            return -1;
        case 6:
            return (((pos >> 8) - 1) << 8) | ((pos & 0xFF) - 1);
        case 7:
            next = (pos & 0xFF) + 1;
            return (next < 7) ? ((((pos >> 8) - 1) << 8) | next) : -1;
        default:
            return -1;
        }
    default:
        return -1;
    }
}

/* How many units side `nSide` has (`bObj` picks monsters, magic or both). */
s32 Ta_GetUnitNum(s32 nSide, u8 bObj) {
    s32 count = 0;
    s32 index;
    s32 end;

    switch (bObj) {
    case 0:
        index = 0;
        end = 11;
        break;
    case 1:
        index = 0;
        end = 6;
        break;
    case 2:
        index = 6;
        end = 11;
        break;
    case 3:
        index = 1;
        end = 11;
        break;
    case 4:
        index = 1;
        end = 6;
        break;
    default:
        return -1;
    }

    for (; index < end; index++) {
        if (SzDuel_GetUnit(nSide, index) != 0) {
            count++;
        }
    }
    return count;
}

typedef struct {
    s32 unused;
    s32 first;
    s32 second;
} Masks_0024E880;

/* Fills an effect's target list from its field condition. */
void Ta_SetEffectObjByField(void *eInfo, s32 *Buf) {
    Masks_0024E880 *masks = eInfo;
    s32 temp_v1;
    s32 var_t3;

    masks->first = 0;
    masks->second = 0;
    var_t3 = 0;
    while ((temp_v1 = *Buf) < 0) {
        if (((temp_v1 & 0xFF) + ((temp_v1 >> 8) * 7)) < 0x1D) {
            masks->first |= 1 << (0x1C - var_t3);
        } else {
            masks->second |= 1 << (0x15 - (var_t3 - 0x1D));
        }
        Buf++;
        var_t3 += 1;
    }
}

/* How many units a unit flag list holds. */
s32 Ta_GetUnitNumFrom22bitFlagList(s32 fLst) {
    s32 count = 0;
    s32 bit = 0;

    do {
        if ((((u32) fLst >> bit) & 1) == 1) {
            count += 1;
        }
        bit += 1;
    } while (bit < 0x16);
    return count;
}

/* Whether square `Loc` is within distance `Dist` of the centre on range shape `ID`. */
s32 Ta_GetLocDistanceFromCenterOnRangeXY(s32 Loc, s32 Dist, s32 ID) {
    s32 x;
    s32 y;
    s32 nextY;

    x = Loc & 0xFF;
    y = Loc >> 8;
    switch (ID) {
    case 0:
        x -= Dist;
        if (x >= 0) {
            return (y << 8) | x;
        }
        break;
    case 1:
        nextY = y - Dist;
        if (nextY < 0) {
            break;
        }
        return x | (nextY << 8);
    case 2:
        x += Dist;
        if (x >= 7) {
            break;
        }
        return (y << 8) | x;
    case 3:
        nextY = y + Dist;
        if (nextY >= 7) {
            break;
        }
        return x | (nextY << 8);
    default:
        return -1;
    }
    return -1;
}

/* Whether unit `OwnID` is in unit flag list `fLst`. */
s32 Ta_GetAgreeOwnerIDon22bitFlagLst(s32 OwnID, u32 fLst) {
    u32 var_v0;

    if ((OwnID >> 8) == 0) {
        var_v0 = ((fLst >> 0xB) >> (0xA - (OwnID & 0xFF))) & 1;
    } else {
        var_v0 = (fLst >> (0xA - (OwnID & 0xFF))) & 1;
    }
    return var_v0;
}

/* How many sides an effect targets. */
s32 TaUtil_GetObjSideNum(void) {
    return 0;
}

/* Attribute `Attr1` against `Attr2` on the attribute wheel: 1 wins, -1 loses, 0 neither. */
s32 ChkAttrAdv(s32 Attr1, s32 Attr2) {
    switch (Attr1) {
    case 0:
        if (Attr2 == 1) {
            return -1;
        }
        return (Attr2 == 4) ? 1 : 0;
    case 1:
        if (Attr2 == 5) {
            return -1;
        }
        return (Attr2 == 0) ? 1 : 0;
    case 2:
        if (Attr2 == 4) {
            return -1;
        }
        return (Attr2 == 3) ? 1 : 0;
    case 3:
        if (Attr2 == 2) {
            return -1;
        }
        return (Attr2 == 5) ? 1 : 0;
    case 4:
        if (Attr2 == 0) {
            return -1;
        }
        return (Attr2 == 2) ? 1 : 0;
    case 5:
        if (Attr2 == 3) {
            return -1;
        }
        return (Attr2 == 1) ? 1 : 0;
    default:
        return 0;
    }
}

/* A random unit of unit flag list `Obj`. */
s32 Ta_GetRandomUnit(s32 Obj) {
    s32 count;
    s32 result;

    count = Ta_GetUnitNumFrom22bitFlagList(Obj);
    if (count == 0) {
        return -1;
    }
    result = Ta_GetUnitOwnerIDFromLstCount(Obj, func_0019A5C8() % count);
    if (result >= 0) {
        return result;
    }
    return -1;
}

/* The unit at position `ordinal` of unit flag list `mask`. */
s32 Ta_GetUnitOwnerIDFromLstCount(s32 mask, s32 ordinal) {
    s32 index;
    s32 count;

    index = 0;
    count = 0;
    do {
        if (((mask >> (21 - index)) & 1) == 1) {
            if (count == ordinal) {
                if (index < 11) {
                    return index;
                } else {
                    return (index - 11) | 0x100;
                }
            }
            count++;
        }
        index++;
    } while (index < 22);
    return -1;
}

typedef struct {
    s8 unused0 : 1;
    s8 invert : 1;
    s8 unused2 : 6;
} Flags_0024ECD0;

/* Whether a unit (record `vInfo`) matches condition `cKey` of effect owner `eOwner` and side `cSide`. */
s32 Ta_GetUnitAgreeWithVarInfo(void *vInfo, s32 eOwner, s32 cSide, s32 cKey) {
    extern s32 Ta_SideMatch();
    s32 temp_s0;
    s32 sideMatch;
    s32 var_v1;
    s32 var_a0;

    temp_s0 = *(u8 *)((u8 *)vInfo + 0x3E);
    if (((s32)temp_s0 >> 5) != 0) {
        return 0;
    }
    if (((Flags_0024ECD0 *)((u8 *)vInfo + 0x57))->invert == 0) {
        var_a0 = *(u8 *)((u8 *)vInfo + 0x44);
    } else {
        var_a0 = (*(u8 *)((u8 *)vInfo + 0x44) == 0) ? 1 : 0;
    }
    sideMatch = Ta_SideMatch(var_a0);
    switch (cKey) {
    case 21:
        if (*(u8 *)((u8 *)vInfo + 0x3F) == 1) {
            var_v1 = 1;
        } else {
            var_v1 = 0;
        }
        break;
    case 20:
        var_v1 = (*(u8 *)((u8 *)vInfo + 0x3F) == 0) ? 1 : 0;
        break;
    case 29:
        var_v1 = 1;
        break;
    case 49:
        if (Do_Chk_Enc(*(u16 *)((u8 *)vInfo + 0x3C), 0x2FF) != 0x3E7) {
            var_v1 = 1;
        } else {
            var_v1 = 0;
        }
        break;
    case 14:
        if ((temp_s0 & 0x1F) == 14) {
            var_v1 = 1;
        } else {
            var_v1 = 0;
        }
        break;
    case 15:
        if ((temp_s0 & 0x1F) == 15) {
            var_v1 = 1;
        } else {
            var_v1 = 0;
        }
        break;
    case 2:
        if ((temp_s0 & 0x1F) == 2) {
            var_v1 = 1;
        } else {
            var_v1 = 0;
        }
        break;
    case 6:
        if ((temp_s0 & 0x1F) == 6) {
            var_v1 = 1;
        } else {
            var_v1 = 0;
        }
        break;
    case 7:
        if ((temp_s0 & 0x1F) == 7) {
            var_v1 = 1;
        } else {
            var_v1 = 0;
        }
        break;
    case 25:
        if (*(u8 *)((u8 *)vInfo + 0x3F) == 5) {
            var_v1 = 1;
        } else {
            var_v1 = 0;
        }
        break;
    case 16:
        if ((temp_s0 & 0x1F) == 16) {
            var_v1 = 1;
        } else {
            var_v1 = 0;
        }
        break;
    case 17:
        if ((temp_s0 & 0x1F) == 17) {
            var_v1 = 1;
        } else {
            var_v1 = 0;
        }
        break;
    case 19:
        if ((temp_s0 & 0x1F) == 19) {
            var_v1 = 1;
        } else {
            var_v1 = 0;
        }
        break;
    default:
        var_v1 = 0;
        break;
    }
    if (sideMatch != 0 && var_v1 != 0) {
        return 1;
    }
    return 0;
}

/* The unit of flag list `mask` that was summoned first. */
s32 Ta_GetMinimumOrderUnitFromFlagList(s32 mask) {
    extern s32 SzDuel_GetUnitSummonOrder(s32, s32);
    s32 i;
    s32 best;
    s32 bestPair;
    s32 pair;
    s32 value;

    best = 0xFF;
    bestPair = -1;
    for (i = 0; i < Ta_GetUnitNumFrom22bitFlagList(mask); i++) {
        pair = Ta_GetUnitOwnerIDFromLstCount(mask, i);
        value = SzDuel_GetUnitSummonOrder(pair >> 8, pair & 0xFF);
        if (value < best) {
            bestPair = pair;
            best = value;
        }
    }
    return bestPair;
}

/* The unit of flag list `eObj` on side `nSide` that was summoned first. */
s32 Ta_GetMinimumOrderUnitFromFlagList2(s32 eObj, s32 nSide) {
    s32 i;
    s32 min;
    s32 result;
    s32 card;
    s32 lo;
    s32 hi;
    s32 cost;

    min = 0xFF;
    result = -1;
    for (i = 0; i < Ta_GetUnitNumFrom22bitFlagList(eObj); i++) {
        card = Ta_GetUnitOwnerIDFromLstCount(eObj, i);
        hi = card >> 8;
        lo = card & 0xFF;
        cost = SzDuel_GetUnitSummonOrder(hi, lo);
        if (cost <= min) {
            min = cost;
            if (result < 0) {
                result = card;
            } else if (nSide == Ta_GetCurrentSide(hi, lo)) {
                result = card;
            }
        }
    }
    return result;
}

/* The unit of flag list `mask` that was summoned last. */
s32 Ta_GetMaximumOrderUnitFromFlagList(s32 mask) {
    extern s32 SzDuel_GetUnitSummonOrder(s32, s32);
    s32 i;
    s32 best;
    s32 bestPair;
    s32 pair;
    s32 value;

    best = -1;
    bestPair = -1;
    for (i = 0; i < Ta_GetUnitNumFrom22bitFlagList(mask); i++) {
        pair = Ta_GetUnitOwnerIDFromLstCount(mask, i);
        value = SzDuel_GetUnitSummonOrder(pair >> 8, pair & 0xFF);
        if (best < value) {
            bestPair = pair;
            best = value;
        }
    }
    return bestPair;
}

/* The units of flag list `eObj` tied at the lowest attack plus defence (a flag list). */
u32 Ta_GetMinimumParamUnitFromFlagList(s32 eObj) {
    s32 i;
    s32 best;
    s32 mask;
    s32 score;
    s32 low;
    s32 high;
    s32 value;

    best = 0xFFFF;
    mask = 0;
    i = 0;
    if (i < Ta_GetUnitNumFrom22bitFlagList(eObj)) {
        do {
            value = Ta_GetUnitOwnerIDFromLstCount(eObj, i);
            high = value >> 8;
            low = value & 0xFF;
            if ((score = Ta_GetAPPlusDP(high, low)) < best) {
                mask = ConvUnitIDtoFlagList(0U, high, low);
                best = score;
            } else if (score == best) {
                mask = ConvUnitIDtoFlagList((u32) mask, high, low);
            }
            i += 1;
        } while (i < Ta_GetUnitNumFrom22bitFlagList(eObj));
    }
    return (u32) mask;
}

/* Unit (nSide, nID)'s attack plus defence. */
s32 Ta_GetAPPlusDP(s32 nSide, s32 nID) {
    s32 loc;
    s32 locLo;
    s32 unitAP;

    loc = SzDuel_GetUnitLoc(nSide, nID);
    locLo = loc & 0xFF;
    unitAP = TaUtil_GetUnitAP(nSide, nID, locLo, locLo);
    return unitAP + TaUtil_GetUnitDP(nSide, nID, locLo, loc >> 8);
}

/* From the dotr-decomp CC0 bundle (commit 88c32bb2), chatC/imp/conv.py. */

struct DotrStateEntry8 {
    int unknown_words[2];
};
int func_001E1030_b(int a, int b);
struct DotrStateEntry8 *func_00250740_b(int a, int b, int n);
extern int func_001E1030_b(int a, int b);

/* Destroys unit (a, b): experience, the graveyard, the board. */
int Ta_DelUnit(int a, int b)
{
    struct DotrStateEntry8 *entry;
    SzData_CalcExp(a, func_001E1030_b(a, b), 0, -4);
    SzDuel_AddGrave(a, func_001E1030_b(a, b));
    SzDuel_DelUnit(a, b);
    if ((entry = func_00250740_b(a, b, 4)) != 0 && (unsigned)entry->unknown_words[0] >> 8 == 81) {
        SzDuel_AddGrave((unsigned)entry->unknown_words[1] >> 24, entry->unknown_words[1] & 0xffff);
        SzData_CalcExp((unsigned)entry->unknown_words[1] >> 24, entry->unknown_words[1] & 0xffff, 0, -4);
    }
    return 0;
}

/* From the dotr-decomp CC0 bundle (commit 88c32bb2), chatC/imp/conv.py. */

struct DotrStateEntry8_24f430 {
    int unknown_words[2];
};
int func_001E1030_b(int a, int b);
struct DotrStateEntry8_24f430 *func_00250740_24f430(int a, int b, int n);
extern int func_001E1030_b(int a, int b);

/* Destroys unit (a, b) (turn owner's experience). */
int Ta_DelUnit2(int a, int b)
{
    struct DotrStateEntry8_24f430 *entry;
    SzData_CalcExp(SzDuel_GetTurnOwner(), func_001E1030_b(a, b), 0, -4);
    SzDuel_AddGrave(SzDuel_GetTurnOwner(), func_001E1030_b(a, b));
    SzDuel_DelUnit(a, b);
    if ((entry = func_00250740_24f430(a, b, 4)) != 0 && (unsigned)entry->unknown_words[0] >> 8 == 81) {
        SzDuel_AddGrave((unsigned)entry->unknown_words[1] >> 24, entry->unknown_words[1] & 0xffff);
        SzData_CalcExp((unsigned)entry->unknown_words[1] >> 24, entry->unknown_words[1] & 0xffff, 0, -4);
    }
    return 0;
}

/* The effects a unit (nSide, nID) gets when it lands on square (nX, nZ), into `eInfo`. */
s32 TaUnit_AddUnitEfc(s32 nSide, s32 nID, s32 nX, s32 nZ, void *eInfo) {
    extern s32 Ta_IsVirus();
    s32 controller;
    s32 kind;
    s32 convUnitIDtoFlagList;
    s32 var_s2;
    s32 convUnitIDtoFlagList2;

    controller = Ta_IsUnitControl(nSide, nID);
    kind = SzDuel_GetUnitKind(nSide, nID);
    var_s2 = convUnitIDtoFlagList2 = 0;
    if (SzDuel_GetUnit(nSide, nID) == 0 || nID == 0) {
        return 0;
    }
    if (SzDuel_GetField(nX, nZ) == 9) {
        if (Ta_IsVirus(nSide, nID, eInfo) == 1) {
            return 1;
        }
    }
    if (Ta_IsLDRange((controller == 0) ? 1 : 0, nX, nZ) != 0) {
        if (Ta_IsLDAbl(0x10, (controller == 0) ? 1 : 0) != 0) {
            if ((Ta_IsLD_DestObj((controller == 0) ? 1 : 0, kind & 0x1F) != 0) && ((kind >> 5) == 0)) {
                var_s2 = ConvUnitIDtoFlagList(var_s2, nSide, nID);
            }
        }
        if ((Ta_IsLDAbl(0xF, (controller == 0) ? 1 : 0) != 0) && (Ta_IsLD_CurseObj((controller == 0) ? 1 : 0, kind & 0x1F) != 0) && ((kind >> 5) == 0)) {
            convUnitIDtoFlagList2 = ConvUnitIDtoFlagList(0U, nSide, nID);
        }
        if (var_s2 > 0 || convUnitIDtoFlagList2 > 0) {
            ((s32 *)eInfo)[0] = 0x71;
            ((s32 *)eInfo)[1] = var_s2;
            ((s32 *)eInfo)[2] = convUnitIDtoFlagList2;
            ((s32 *)eInfo)[3] = 0x80000000;
            return 1;
        }
        convUnitIDtoFlagList = 0;
        if ((Ta_IsLDAbl(0xD, (controller == 0) ? 1 : 0) != 0) && (SzDuel_GetUnitStatus(nSide, nID, 4) == 0)) {
            convUnitIDtoFlagList = ConvUnitIDtoFlagList(0U, nSide, nID);
        }
        if (convUnitIDtoFlagList > 0) {
            ((s32 *)eInfo)[0] = 0x71;
            ((s32 *)eInfo)[1] = 0;
            ((s32 *)eInfo)[2] = 0;
            ((s32 *)eInfo)[3] = (s32) (convUnitIDtoFlagList | 0x80000000);
            return 1;
        }
    }
    return 0;
}

/* Finishes unit (nSide, nID)'s move to (nX, nZ): the field change and move effects. */
s32 Ta_Do_CompMove(s32 nSide, s32 nID, s32 nX, s32 nZ, s32 eInfo) {
    if (SzDuel_GetField(nX, nZ) == 9) {
        if (Ta_IsVirus(nSide, nID, eInfo) == 1) {
            return 0x10001;
        }
    }
    return Ta_Do_MoveEfc(nSide, nID, nX, nZ, (void *)eInfo);
}

/* From the dotr-decomp CC0 bundle (commit 88c32bb2), chatC/imp/conv.py. */

struct jp_9026 {
    int eNO;
    unsigned int dwFrom;
    unsigned int dwTo;
    unsigned int dwPar;
};
struct jp_8cf7 {
    unsigned int dwID;
    unsigned int dwParam;
};
extern int SzDuel_SetField_b(int x, int y, int value);
extern int SzDuel_GetUnitSpellRest_b(int a, int b);
extern struct jp_8cf7 *Ta_GetUnitEffect_b(int a, int b, int n);
#define MAXI(a, b) ((a) < (b) ? (b) : (a))
#define MINI(a, b) ((b) < (a) ? (b) : (a))

/* The effects of unit (nSide, nID) moving to (nX, nZ): leader abilities that change the field, effects in range. */
int Ta_Do_MoveEfc(int nSide, int nID, int nX, int nZ, void *eInfo_v)
{
    struct jp_9026 * eInfo = eInfo_v;
    int i;
    int j;
    int eObj;
    int eObj2;
    int eObj3;
    int Unit;
    struct jp_8cf7 *pDat;
    int bKind;

    if (nID == 0) {
        if (Ta_IsLDAbl(7, nSide)) {
            SzDuel_SetField_b(nX, nZ, Ta_GetLDChgLand(SzDuel_GetUnitKind(nSide, nID) & 0x1F));
        }
        i = 0;
        eObj = 0;
        eObj2 = 0;
        eObj3 = 0;
        for (; i < 7; i++) {
            for (j = 0; j < 7; j++) {
                Unit = SzDuel_GetMapUnitID(i, j);
                if (Unit < 0) {
                    continue;
                }
                if (nSide == Ta_GetCurrentSide(Unit >> 8, Unit & 0xFF)) {
                    continue;
                }
                if ((Unit & 0xFF) == 0) {
                    continue;
                }
                if (!Ta_IsSquareRange(nX, nZ, i, j, Ta_GetLDRange(nSide))) {
                    continue;
                }
                bKind = SzDuel_GetUnitKind(Unit >> 8, Unit & 0xFF);
                if ((bKind >> 5) == 0) {
                    if (Ta_IsLDAbl(16, nSide)) {
                        if (Ta_IsLD_DestObj(nSide, bKind & 0x1F) && (Unit & 0xFF) != 0) {
                            eObj = ConvUnitIDtoFlagList(eObj, Unit >> 8, Unit & 0xFF);
                        }
                    }
                    if (Ta_IsLDAbl(15, nSide)
                        && Ta_IsLD_CurseObj(nSide, SzDuel_GetUnitKind(Unit >> 8, Unit & 0xFF) & 0x1F)
                        && SzDuel_GetUnitSpellRest_b(Unit >> 8, Unit & 0xFF) == 0 && (Unit & 0xFF) != 0) {
                        eObj2 = ConvUnitIDtoFlagList(eObj2, Unit >> 8, Unit & 0xFF);
                    }
                }
                if (Ta_IsLDAbl(13, nSide) && SzDuel_GetUnitStatus(Unit >> 8, Unit & 0xFF, 4) == 0
                    && (Unit & 0xFF) != 0) {
                    eObj3 = ConvUnitIDtoFlagList(eObj3, Unit >> 8, Unit & 0xFF);
                }
            }
        }
        if (eObj > 0 || eObj2 > 0 || eObj3 > 0) {
            eInfo->eNO = 0x71;
            eInfo->dwFrom = eObj | 0x80000000;
            eInfo->dwTo = eObj2;
            eInfo->dwPar = eObj3;
            return 1;
        }
    } else if ((pDat = Ta_GetUnitEffect_b(nSide, nID, 1)) != 0) {
        switch (pDat->dwID >> 8) {
        case 0x42:
            switch ((pDat->dwID >> 6) & 3) {
            case 1:
                SzDuel_CalcLP(Ta_GetCurrentSide(nSide, nID), 1,
                              Ta_GetLPRevByNaturalEffect(0x2C, pDat->dwParam & 0xFFFF));
                break;
            case 2:
                SzDuel_CalcLP(Ta_GetCurrentSide(nSide, nID) == 0 ? 1 : 0, 1,
                              Ta_GetLPRevByNaturalEffect(0x2C, pDat->dwParam & 0xFFFF));
                break;
            }
            eInfo->eNO = 0xFF;
            eInfo->dwFrom = 0;
            eInfo->dwTo = (nSide << 8) | nID;
            eInfo->dwPar = 0;
            return 1;
        case 2:
            for (i = 0; i < 7; i++) {
                for (j = 0; j < 7; j++) {
                    if ((unsigned)((MAXI(i, nX) - MINI(i, nX)) + (MAXI(j, nZ) - MINI(j, nZ))) <= (pDat->dwParam >> 16)) {
                        SzDuel_SetField_b(i, j, pDat->dwParam & 0xFFFF);
                    }
                }
            }
            eInfo->eNO = 0xFF;
            eInfo->dwFrom = 0;
            eInfo->dwTo = (nSide << 8) | nID;
            eInfo->dwPar = 0;
            return 1;
        case 10:
            if (SzDuel_GetField(nX, nZ) == 8) {
                SzDuel_SetField_b(nX, nZ, 7);
                eInfo->eNO = 0xFF;
                eInfo->dwFrom = 0;
                eInfo->dwTo = (nSide << 8) | nID;
                eInfo->dwPar = 0;
                return 1;
            }
            return 0;
        case 9:
            if (SzDuel_GetField(nX, nZ) == 8) {
                eObj = ConvUnitIDtoFlagList(0, nSide, nID);
                eInfo->eNO = 0x3C;
                eInfo->dwFrom = 0;
                eInfo->dwTo = eObj;
                eInfo->dwPar = WallFusion(nSide, nID);
                return 0x10001;
            }
            break;
        }
    }
    return 0;
}
#undef MAXI
#undef MINI

/* Whether unit (nSide, nID) is caught by a virus effect, adding it to `eInfo`. */
s32 Ta_IsVirus(s32 nSide, s32 nID, s32 eInfo) {
    extern s32 Ta_IsVirus_Chk(s32, s32);
    extern void TaUtil_DoOpen(s32, s32, s32);
    s32 *out = (s32 *)eInfo;
    s32 mask;

    if (Ta_IsVirus_Chk(nSide, nID) == 1) {
        mask = ConvUnitIDtoFlagList(0, nSide, nID);
        out[0] = 0x70;
        out[1] = 0;
        out[2] = mask;
        out[3] = 0;
        TaUtil_DoOpen(nSide, nID, 1);
        return 1;
    }
    return 0;
}

/* Whether unit (nSide, nID) is a virus target. */
void Ta_IsVirus_Chk(s32 nSide, s32 nID) {
    Ta_IsVirus_Chk2(SzDuel_GetUnit(nSide, nID));
}

/* Whether a unit (record `pVarInfo`) is a virus target (by its attack). */
s32 Ta_IsVirus_Chk2(s32 pVarInfo) {
    u8 temp_v1;

    if (pVarInfo == 0) {
        return 0;
    }
    temp_v1 = *(u8 *)((u8 *)pVarInfo + 0x3E);
    if ((((s32) temp_v1 >> 5) != 0) ||
        (*(u8 *)((u8 *)pVarInfo + 0x45) == 0) ||
        ((temp_v1 & 0x1F) == 0x14)) {
        return 0;
    }
    return (TaUtil_GetUnitAP2(pVarInfo, *(u8 *)((u8 *)pVarInfo + 0x40), *(u8 *)((u8 *)pVarInfo + 0x41)) < 0x5DC) ? 0 : 1;
}

/* Whether a unit (record `pVarInfo`) on (nX, nZ) is a virus target. */
s32 Ta_IsVirus_Chk3(void *pVarInfo, s32 nX, s32 nZ) {
    u8 temp_v1;

    if (pVarInfo == NULL) {
        return 0;
    }
    temp_v1 = *((u8 *)pVarInfo + 0x3E);
    if ((((s32)temp_v1 >> 5) != 0) ||
        (*((u8 *)pVarInfo + 0x45) == 0) ||
        ((temp_v1 & 0x1F) == 0x14)) {
        return 0;
    }
    return (TaUtil_GetUnitAP2((s32)pVarInfo, nX, nZ) < 0x5DC) ? 0 : 1;
}

/* Every unit a virus effect catches, into `eInfo`. */
s32 Ta_IsVirusAll(void *eInfo) {
    extern s32 Ta_IsVirus_Chk(s32, s32);
    extern void TaUtil_DoOpen(s32, s32, s32);
    u32 mask;
    s32 *out = (s32 *)eInfo;
    s32 i;
    s32 info;

    mask = 0;
    i = 1;
    do {
        info = SzDuel_GetUnitLoc(0, i);
        if (Ta_IsVirus_Chk(0, i) == 1) {
            if (SzDuel_GetField(info & 0xFF, info >> 8) == 9) {
                mask = ConvUnitIDtoFlagList(mask, 0, i);
                TaUtil_DoOpen(0, i, 1);
            }
        }
        info = SzDuel_GetUnitLoc(1, i);
        if (Ta_IsVirus_Chk(1, i) == 1 && SzDuel_GetField(info & 0xFF, info >> 8) == 9) {
            mask = ConvUnitIDtoFlagList(mask, 1, i);
            TaUtil_DoOpen(1, i, 1);
        }
        i++;
    } while (i < 0xB);
    if (Ta_GetUnitNumFrom22bitFlagList((s32)mask) > 0) {
        out[0] = 0x70;
        out[1] = 0;
        out[2] = mask;
        out[3] = 0;
        return 1;
    }
    return 0;
}

/* Whether side `nSide`'s graveyard holds card `cNo` (by key `sKey`). */
s32 Ta_IsGraveEntryHit(s32 nSide, s32 cNo, s32 sKey) {
    extern s32 SzDuel_GetGraveCount(s32);
    s32 card;

    if (SzDuel_GetGraveCount(nSide) < cNo) {
        return 0;
    }
    card = SzDuel_InqGrave(nSide, cNo);
    if (card != 999) {
        switch (sKey) {
        case 0:
            return 1;
        case 1:
            return card < 0x2AB ? 1 : 0;
        case 2:
            if (card >= 0x2AB) {
                return 1;
            }
            return 0;
        }
    }
    return 0;
}

/* Fades unit (nSide, nID) in or out (`Flip`) in `Mode`. */
void Ta_UnitFade(s32 nSide, s32 nID, s32 Flip, s32 Mode, s32 fCM) {
    extern s32 SzDuel_SetUnitCtlModeC();
    extern s32 SzDuel_SetUnitCtlModeM();
    extern s32 SzDuel_SetUnitCtlGoalC();
    extern s32 SzDuel_SetUnitCtlGoalM();
    extern s32 SzDuel_GetUnitCtlRateC();
    extern s32 SzDuel_GetUnitCtlRateM();
    s32 unitCtlRateC;
    s32 unitCtlRateM;

    SzEffect_SetBusyFlag2((nSide << 8) | nID, 0);
    unitCtlRateC = SzDuel_GetUnitCtlRateC(nSide, nID);
    unitCtlRateM = SzDuel_GetUnitCtlRateM(nSide, nID);
    if ((nID != 0) && ((SzDuel_GetUnitKind(nSide, nID) >> 5) != 0)) {
        fCM = ((fCM >> 1) & 1) * 2;
    }
    if (Flip > 0) {
        if (fCM & 1) {
            if (unitCtlRateM < 0x80) {
                SzDuel_SetUnitCtlModeM(nSide, nID, Mode);
                SzDuel_SetUnitCtlGoalM(nSide, nID, 0x80);
                if ((SzDuel_GetUnitStatus(nSide, nID, 4) != 0) || (nID == 0)) {
                    SzDuel_SetUnitCtlRateM(nSide, nID, 1, -1);
                } else {
                    SzDuel_SetUnitCtlRateM(nSide, nID, 0, -1);
                }
            }
        }
        if (((fCM >> 1) & 1) && (unitCtlRateC < 0x80)) {
            SzDuel_SetUnitCtlModeC(nSide, nID, Mode);
            SzDuel_SetUnitCtlGoalC(nSide, nID, 0x80);
            SzDuel_SetUnitCtlRateC(nSide, nID, 1, -1);
        }
    } else {
        if ((fCM & 1) && (unitCtlRateM > 0)) {
            SzDuel_SetUnitCtlModeM(nSide, nID, Mode);
            SzDuel_SetUnitCtlGoalM(nSide, nID, 0);
            SzDuel_SetUnitCtlRateM(nSide, nID, -1, -1);
        }
        if (((fCM >> 1) & 1) && (unitCtlRateC > 0)) {
            SzDuel_SetUnitCtlModeC(nSide, nID, Mode);
            SzDuel_SetUnitCtlGoalC(nSide, nID, 0);
            SzDuel_SetUnitCtlRateC(nSide, nID, -1, -1);
        }
    }
}

/* A unit control speed from rate `bRate`, direction and sign. */
s32 Ta_CalcCtrlRate(u16 bRate, s32 Flip, s32 Sign) {
    if (Sign > 0) {
        bRate += Flip;
        if (bRate > 0x80) {
            bRate = 0x80;
        }
        return bRate;
    }
    if (Flip < bRate) {
        bRate -= Flip;
    } else {
        bRate = 0;
    }
    return bRate;
}

/* The side unit (nSide, nID) plays for now (the other side while it is controlled). */
s32 Ta_IsUnitControl(s32 nSide, s32 nID) {
    return Ta_GetCurrentSide(nSide, nID);
}

typedef struct {
    s8 unused : 1;
    s8 inverted : 1;
    s8 reserved : 6;
} Flags_00250370;

typedef struct {
    u8 pad_00[0x44];
    u8 value;
    u8 pad_45[0x12];
    Flags_00250370 flags;
} Data_00250370;

/* The side a unit (record `pVarInfo`) plays for now (the other side while it is controlled). */
s32 Ta_IsUnitControl2(void *pVarInfo) {
    Data_00250370 *data = pVarInfo;

    if (pVarInfo == NULL) {
        return -1;
    }
    if (data->flags.inverted == 0) {
        return data->value;
    }
    return (data->value == 0) ? 1 : 0;
}

/* Sets unit (nSide, nID)'s curse turns to `bRest` (keeps the longer one). */
void Ta_SetUnitCurseRest(s32 nSide, s32 nID, s32 bRest) {
    /* called unprototyped: the byte goes out zero-extended, not as s8 */
    s32 SzDuel_SetUnitCurseRest();
    u8 value = bRest;

    if (value > 0) {
        if (SzDuel_GetUnitCurseRest() <= value) {
            SzDuel_SetUnitCurseRest(nSide, nID, value);
            SzDuel_SetUnitCurseFlag(nSide, nID, 1);
        }
    } else {
        SzDuel_SetUnitCurseRest(nSide, nID, value);
    }
}

typedef struct {
    u8 kind;
    u8 pad1[2];
    u8 level;
    u8 pad4[5];
    u8 pad9 : 7;
    u8 flag : 1;
} Card_00250430;


/* Reincarnation: the card side `nSide` gets for giving up card `cNo` (a random card of a rolled nearby level;
   0x334 if none). */
s32 Ta_GetRecycle(s32 nSide, s32 cNo) {
    s32 list[0x356];
    Card_00250430 *card;
    s32 count;
    s32 level;
    s32 flag;
    s32 done;
    s32 i;

    for (i = 0; i < 0x356; i++) {
        list[i] = 999;
    }
    card = (Card_00250430 *)SzDuel_GetCardConstInfo(cNo);
    if ((card->kind >> 5) == 0) {
        flag = (func_0019A5C8() % 10 < 8) ? 1 : 0;
    } else {
        flag = (func_0019A5C8() % 10 < 4) ? 0 : 1;
    }
    done = 0;
    count = 0;
    level = Ta_GetRecycleRequestLvl(nSide, card->level);
    if (level > 0) {
        do {
            for (i = flag ? 0 : 0x2AB; i < (flag ? 0x2AB : 0x356); i++) {
                if (i != cNo) {
                    card = (Card_00250430 *)SzDuel_GetCardConstInfo(i);
                    if (card != NULL && card->level == level && card->flag) {
                        list[count++] = i;
                    }
                }
            }
            if (count > 0 || --level == 0) {
                done = 1;
            } else {
                count = 0;
            }
        } while (!done);
    }
    if (count == 0) {
        return 0x334;
    }
    return list[func_0019A5C8() % count];
}

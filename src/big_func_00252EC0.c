#include "common.h"

#define MIN_00252EC0(a, b) ((a) < (b) ? (a) : (b))
#define MAX_00252EC0(a, b) ((a) > (b) ? (a) : (b))

typedef struct Result_00252EC0 {
    s32 kind;
    s32 value;
    s32 pos;
    s32 extra;
} Result_00252EC0;

s32 Ta_Do_Magic(s32 x, s32 y, void *arg2, u8 *tail, s32 phase, u32 *info) {
    extern void Ta_DelUnit(s32, s32);
    extern s32 SzDuel_GetUnitCardNo(s32, s32);
    extern s32 SzDuel_GetGraveCount(s32);
    Result_00252EC0 *res = arg2;
    s32 list[49];
    s32 got[3];
    s32 owner;
    u32 code;
    s32 i;
    s32 j;
    s32 n;
    s32 pos;
    s32 total;
    s32 side;
    s32 kind;
    s32 pick;
    s32 base;
    u32 amount;
    u32 r;

    for (i = 0; i < 49; i++) {
        list[i] = -1;
    }
    owner = Ta_GetCurrentSide(x, y);
    code = *info;
    switch (code >> 8) {
    case 0x17:
        r = Ta_RemoveObjFromFlagLst2(ConvUnitIDtoFlagList_OFF(SearchUnitByRange(0, 0, Ta_GetCurrentSide(x, y), (code >> 6) & 3, code & 0x3F, 0xE), x, y), owner);
        res->kind = 0;
        res->value = 0;
        res->pos = r;
        res->extra = (u16)info[1];
        Ta_DelUnit(x, y);
        if (Ta_GetUnitNumFrom22bitFlagList(r) == 0) {
            res->kind = 0xFE;
            res->value = 0;
            res->pos = 0xFFFF;
            res->extra = 0x10;
            return 1;
        }
        return 1;
    case 0x14:
        res->kind = 1;
        res->value = Ta_GetCurrentSide(x, y) | 0x20000;
        res->pos = SzDuel_GetUnitLoc(x, y);
        res->extra = 999;
        side = 2;
        switch ((*info >> 6) & 3) {
        case 3:
            break;
        case 1:
            side = (Ta_GetCurrentSide(x, y) != 0) ? 1 : 0;
            break;
        case 2:
            side = (Ta_GetCurrentSide(x, y) == 0) ? 1 : 0;
            break;
        default:
            Ta_DelUnit(x, y);
            return 0;
        }
        total = 0;
        switch (*info & 0x3F) {
        case 0x1D:
            if (side == 2) {
                total += TaUtil_GetGraveCardNum(0, 0);
                total += TaUtil_GetGraveCardNum(1, 0);
            } else {
                total += TaUtil_GetGraveCardNum(side, 0);
            }
            if (total == 0) {
                Ta_DelUnit(x, y);
                return 0;
            } else {
                n = 1;
            }
            break;
        case 0x1E:
            if (side == 2) {
                total += TaUtil_GetGraveCardNum(0, 1);
                total += TaUtil_GetGraveCardNum(1, 1);
                total += TaUtil_GetGraveCardNum(0, 2);
                total += TaUtil_GetGraveCardNum(1, 2);
                total += TaUtil_GetGraveCardNum(0, 3);
                total += TaUtil_GetGraveCardNum(1, 3);
                total += TaUtil_GetGraveCardNum(0, 4);
                total += TaUtil_GetGraveCardNum(1, 4);
                total += TaUtil_GetGraveCardNum(0, 5);
                total += TaUtil_GetGraveCardNum(1, 5);
            } else {
                total += TaUtil_GetGraveCardNum(side, 1);
                total += TaUtil_GetGraveCardNum(side, 2);
                total += TaUtil_GetGraveCardNum(side, 3);
                total += TaUtil_GetGraveCardNum(side, 4);
                total += TaUtil_GetGraveCardNum(side, 5);
            }
            if (total == 0) {
                Ta_DelUnit(x, y);
                return 0;
            } else {
                n = 2;
            }
            break;
        case 0x1F:
            if (side == 2) {
                total += SzDuel_GetGraveCount(0);
                total += SzDuel_GetGraveCount(1);
            } else {
                total += SzDuel_GetGraveCount(side);
            }
            if (total == 0) {
                Ta_DelUnit(x, y);
                return 0;
            } else {
                n = 0;
            }
            break;
        default:
            Ta_DelUnit(x, y);
            return 0;
        }
        tail[0] = 0;
        tail[1] = (side << 4) | n;
        Ta_DelUnit(x, y);
        return 2;
    case 2:
        n = 0;
        pos = SzDuel_GetUnitLoc(x, y);
        for (i = 0; i < 7; i++) {
            for (j = 0; j < 7; j++) {
                if ((MAX_00252EC0(i, pos & 0xFF) - MIN_00252EC0(i, pos & 0xFF)) + (MAX_00252EC0(j, pos >> 8) - MIN_00252EC0(j, pos >> 8)) <= (info[1] >> 16)) {
                    list[n++] = (j << 8) | i;
                }
            }
        }
        switch ((u16)info[1]) {
        case 8:
            res->kind = 2;
            res->value = pos;
            res->pos = info[1] >> 16;
            res->extra = (u16)info[1];
            break;
        default:
            res->kind = 2;
            res->value = pos;
            res->pos = info[1] >> 16;
            res->extra = (u16)info[1];
            break;
        }
        Ta_DelUnit(x, y);
        return 1;
    case 0x48:
        n = 0;
        pos = SzDuel_GetUnitLoc(x, y);
        for (i = 0; i < 49; i++) {
            list[i] = -1;
        }
        for (i = 0; i < 7; i++) {
            for (j = 0; j < 7; j++) {
                if (SzDuel_GetField(i, j) == 8) {
                    list[n++] = (j << 8) | i;
                }
            }
        }
        if (n == 0) {
            Ta_DelUnit(x, y);
            return 0;
        }
        pick = list[func_0019A5C8() % n];
        if (pick < 0) {
            pick = 0;
        }
        res->kind = 3;
        res->value = pick;
        res->pos = pos;
        res->extra = 0;
        Ta_DelUnit(x, y);
        return 1;
    case 4:
        switch (info[1] >> 16) {
        case 0x12:
            pos = SzDuel_GetUnitLoc(x, y);
            code = *info;
            code = SearchUnitByRange(pos & 0xFF, pos >> 8, Ta_GetCurrentSide(x, y), (code >> 6) & 3, code & 0x3F, 0x12);
            code = ConvUnitIDtoFlagList_OFF(code, x, y);
            code = ConvUnitIDtoFlagList_OFF(code, x, 0);
            code = ConvUnitIDtoFlagList_OFF(code, (x == 0) ? 1 : 0, 0);
            switch (SzDuel_GetUnitCardNo(x, y)) {
            case 0x2BC:
                res->kind = 5;
                res->value = pos;
                res->pos = code;
                res->extra = owner | (Ta_GetCurrentSide(x, y) << 16);
                Ta_DelUnit(x, y);
                return 1;
            case 0x2BE:
                res->kind = 7;
                res->value = pos;
                res->pos = code;
                res->extra = owner | (Ta_GetCurrentSide(x, y) << 16);
                Ta_DelUnit(x, y);
                return (Ta_GetUnitNumFrom22bitFlagList(code) == 0) ? 0 : 1;
            default:
                Ta_DelUnit(x, y);
                return 0;
            }
        case 0x13:
            res->kind = 0x19;
            res->value = 0;
            res->pos = 0;
            res->extra = owner;
            Ta_SetEffectObjByField(res, list);
            Ta_DelUnit(x, y);
            return 1;
        case 0:
            r = Ta_RemoveObjFromFlagLst2(ConvUnitIDtoFlagList_OFF(SearchUnitByRange(0, 0, Ta_GetCurrentSide(x, y), (code >> 6) & 3, code & 0x3F, 0xE), x, y), owner);
            switch (SzDuel_GetUnitCardNo(x, y)) {
            case 0x2BB:
                res->kind = 4;
                res->value = Ta_GetCurrentSide(x, y);
                res->pos = r;
                res->extra = 0;
                Ta_DelUnit(x, y);
                if (Ta_GetUnitNumFrom22bitFlagList(r) == 0) {
                    res->kind = 0xFE;
                    res->value = 0;
                    res->pos = 0xFFFF;
                    res->extra = 0x10;
                }
                return 1;
            case 0x2BD:
                res->kind = 6;
                res->value = 0;
                res->pos = r;
                res->extra = 0;
                Ta_DelUnit(x, y);
                if (Ta_GetUnitNumFrom22bitFlagList(r) == 0) {
                    res->kind = 0xFE;
                    res->value = 0;
                    res->pos = 0xFFFF;
                    res->extra = 0x10;
                }
                return 1;
            case 0x2D1:
                res->kind = 0x10;
                res->value = 0;
                res->pos = r;
                res->extra = 0;
                Ta_DelUnit(x, y);
                if (Ta_GetUnitNumFrom22bitFlagList(r) == 0) {
                    res->kind = 0xFE;
                    res->value = 0;
                    res->pos = 0xFFFF;
                    res->extra = 0x10;
                }
                return 1;
            case 0x2D2:
                res->kind = 0x11;
                res->value = 0;
                res->pos = r;
                res->extra = 0;
                Ta_DelUnit(x, y);
                if (Ta_GetUnitNumFrom22bitFlagList(r) == 0) {
                    res->kind = 0xFE;
                    res->value = 0;
                    res->pos = 0xFFFF;
                    res->extra = 0x10;
                }
                return 1;
            case 0x2D8:
                res->kind = 0x12;
                res->value = 0;
                res->pos = r;
                res->extra = 0;
                Ta_DelUnit(x, y);
                if (Ta_GetUnitNumFrom22bitFlagList(r) == 0) {
                    res->kind = 0xFE;
                    res->value = 0;
                    res->pos = 0xFFFF;
                    res->extra = 0x10;
                }
                return 1;
            case 0x2D9:
                res->kind = 0x13;
                res->value = 0;
                res->pos = r;
                res->extra = 0;
                Ta_DelUnit(x, y);
                if (Ta_GetUnitNumFrom22bitFlagList(r) == 0) {
                    res->kind = 0xFE;
                    res->value = 0;
                    res->pos = 0xFFFF;
                    res->extra = 0x10;
                }
                return 1;
            case 0x2DA:
                res->kind = 0x14;
                res->value = 0;
                res->pos = r;
                res->extra = 0;
                Ta_DelUnit(x, y);
                if (Ta_GetUnitNumFrom22bitFlagList(r) == 0) {
                    res->kind = 0xFE;
                    res->value = 0;
                    res->pos = 0xFFFF;
                    res->extra = 0x10;
                }
                return 1;
            case 0x2D7:
                res->kind = 0x17;
                res->value = 0;
                res->pos = r;
                res->extra = 0;
                Ta_DelUnit(x, y);
                if (Ta_GetUnitNumFrom22bitFlagList(r) == 0) {
                    res->kind = 0xFE;
                    res->value = 0;
                    res->pos = 0xFFFF;
                    res->extra = 0x10;
                }
                return 1;
            default:
                res->kind = 0x15;
                res->value = 0;
                res->pos = r;
                res->extra = 0;
                Ta_DelUnit(x, y);
                if (Ta_GetUnitNumFrom22bitFlagList(r) == 0) {
                    res->kind = 0xFE;
                    res->value = 0;
                    res->pos = 0xFFFF;
                    res->extra = 0x10;
                }
                return 1;
            }
        default:
            Ta_DelUnit(x, y);
            return 0;
        }
    case 0xD:
        amount = ((info[1] >> 16) << 16) | (info[1] & 0xFFFF);
        if ((code & 0x3F) == 0x32) {
            amount = ((info[1] >> 16) << 16) | ((info[1] & 0xFFFF) * Ta_GetUnitNum((Ta_GetCurrentSide(x, y) == 0) ? 1 : 0, 3));
        }
        if ((amount & 0xFFFF) == 0) {
            Ta_DelUnit(x, y);
            return 0;
        }
        switch ((*info >> 6) & 3) {
        case 1:
            res->kind = 8;
            res->value = 0;
            res->pos = Ta_GetEOwnerSide(Ta_GetCurrentSide(x, y), (*info >> 6) & 3);
            res->extra = amount;
            Ta_DelUnit(x, y);
            return 1;
        case 2:
            res->kind = 9;
            res->value = SzDuel_GetUnitLoc(x, y);
            res->pos = Ta_GetEOwnerSide(Ta_GetCurrentSide(x, y), (*info >> 6) & 3);
            res->extra = amount;
            Ta_DelUnit(x, y);
            return 1;
        default:
            Ta_DelUnit(x, y);
            return 0;
        }
    case 0x49:
        r = Ta_RemoveObjFromFlagLst2(ConvUnitIDtoFlagList_OFF(SearchUnitByRange(0, 0, Ta_GetCurrentSide(x, y), (code >> 6) & 3, code & 0x3F, 0xE), x, y), owner);
        res->kind = 0xC;
        res->value = 0;
        res->pos = r;
        res->extra = (u16)info[1];
        Ta_DelUnit(x, y);
        if (Ta_GetUnitNumFrom22bitFlagList(r) == 0) {
            res->kind = 0xFE;
            res->value = 0;
            res->pos = 0xFFFF;
            res->extra = 0x10;
        }
        return 1;
    case 0x18:
        r = Ta_RemoveObjFromFlagLst2(ConvUnitIDtoFlagList_OFF(SearchUnitByRange(0, 0, Ta_GetCurrentSide(x, y), (code >> 6) & 3, code & 0x3F, 0xE), x, y), owner);
        res->kind = 0xD;
        res->value = 4;
        res->pos = r;
        res->extra = (u16)info[1];
        Ta_DelUnit(x, y);
        if (Ta_GetUnitNumFrom22bitFlagList(r) == 0) {
            res->kind = 0xFE;
            res->value = 0;
            res->pos = 0xFFFF;
            res->extra = 0x10;
        }
        return 1;
    case 0x1D:
        res->kind = 0xE;
        res->value = 0;
        if (Ta_GetCurrentSide(x, y) == 0) {
            pick = 1;
        } else {
            pick = 0;
        }
        res->pos = pick;
        res->extra = 0;
        Ta_DelUnit(x, y);
        return 1;
    case 0x1E:
        r = Ta_RemoveObjFromFlagLst2(ConvUnitIDtoFlagList_OFF(SearchUnitByRange(0, 0, Ta_GetCurrentSide(x, y), (code >> 6) & 3, code & 0x3F, 0xE), x, y), owner);
        res->kind = 0xF;
        res->value = 0;
        res->pos = r;
        res->extra = 0;
        Ta_DelUnit(x, y);
        if (Ta_GetUnitNumFrom22bitFlagList(r) == 0) {
            res->kind = 0xFE;
            res->value = 0;
            res->pos = 0xFFFF;
            res->extra = 0x10;
        }
        return 1;
    case 0x1F:
        if (Ta_SearchUncTypeNaturalEffectUserNum(0x39) > 0) {
            Ta_DelUnit(x, y);
            return 0;
        }
        code = *info;
        switch (code & 0x3F) {
        case 0x21:
            r = Ta_RemoveObjFromFlagLst2(ConvUnitIDtoFlagList_OFF(SearchUnitByRange(0, 0, Ta_GetCurrentSide(x, y), (code >> 6) & 3, code & 0x3F, 0xE), x, y), owner);
            res->kind = 0x1A;
            res->value = owner;
            res->pos = r;
            res->extra = 0xFFFE;
            Ta_DelUnit(x, y);
            if (Ta_GetUnitNumFrom22bitFlagList(r) == 0) {
                res->kind = 0xFE;
                res->value = 0;
                res->pos = 0xFFFF;
                res->extra = 0x10;
            }
            return 1;
        case 0x33:
            r = Ta_RemoveObjFromFlagLst2(ConvUnitIDtoFlagList_OFF(SearchUnitByRange(0, 0, Ta_GetCurrentSide(x, y), 2, 0x34, 0xE), x, y), owner);
            res->kind = 0x1A;
            res->value = owner;
            res->pos = r;
            res->extra = 0;
            tail[0] = 1;
            if (Ta_GetCurrentSide(x, y) == 0) {
                pick = 1;
            } else {
                pick = 0;
            }
            tail[1] = pick << 4;
            Ta_DelUnit(x, y);
            if (Ta_GetUnitNumFrom22bitFlagList(r) == 0) {
                res->kind = 0xFE;
                res->value = 0;
                res->pos = 0xFFFF;
                res->extra = 0x10;
                return 1;
            }
            return 2;
        default:
            Ta_DelUnit(x, y);
            return 0;
        }
    case 0x20:
        base = ConvUnitIDtoFlagList_OFF(SearchUnitByRange(0, 0, Ta_GetCurrentSide(x, y), 3, 0x36, 0xE), x, y);
        res->kind = 0x1C;
        res->value = Ta_GetCurrentSide(x, y);
        res->pos = base;
        res->extra = 0;
        Ta_DelUnit(x, y);
        return 1;
    case 0x12:
        {
            u32 R12;
            u32 C12;
            s32 K12;

            switch (SzDuel_GetUnitCardNo(x, y)) {
            case 0x2E3:
                K12 = 0x5A;
                break;
            case 0x2E4:
                K12 = 0x5C;
                break;
            default:
                K12 = 0x1D;
                break;
            }
            C12 = *info;
            R12 = Ta_RemoveObjFromFlagLst2(ConvUnitIDtoFlagList_OFF(SearchUnitByRange(0, 0, Ta_GetCurrentSide(x, y), (C12 >> 6) & 3, C12 & 0x3F, 0xE), x, y), owner);
            res->kind = K12;
            res->value = 1;
            res->pos = R12;
            res->extra = (u16)info[1];
            Ta_DelUnit(x, y);
            if (Ta_GetUnitNumFrom22bitFlagList(R12) == 0) {
                res->kind = 0xFE;
                res->value = 0;
                res->pos = 0xFFFF;
                res->extra = 0x10;
            }
            return 1;
        }
    case 0x21:
        r = Ta_RemoveObjFromFlagLst2(ConvUnitIDtoFlagList_OFF(SearchUnitByRange(0, 0, Ta_GetCurrentSide(x, y), (code >> 6) & 3, code & 0x3F, 0xE), x, y), owner);
        res->kind = 0x5B;
        res->value = 0;
        res->pos = r;
        res->extra = 0;
        Ta_DelUnit(x, y);
        if (Ta_GetUnitNumFrom22bitFlagList(r) == 0) {
            res->kind = 0xFE;
            res->value = 0;
            res->pos = 0xFFFF;
            res->extra = 0x10;
        }
        return 1;
    case 0x22:
        r = Ta_RemoveObjFromFlagLst2(ConvUnitIDtoFlagList_OFF(SearchUnitByRange(0, 0, Ta_GetCurrentSide(x, y), (code >> 6) & 3, code & 0x3F, 0xE), x, y), owner);
        res->kind = 0x1D;
        res->value = 0;
        res->pos = r;
        res->extra = (u16)info[1];
        Ta_DelUnit(x, y);
        if (Ta_GetUnitNumFrom22bitFlagList(r) == 0) {
            res->kind = 0xFE;
            res->value = 0;
            res->pos = 0xFFFF;
            res->extra = 0x10;
        }
        return 1;
    case 0x23:
        r = Ta_RemoveObjFromFlagLst2(ConvUnitIDtoFlagList_OFF(SearchUnitByRange(0, 0, Ta_GetCurrentSide(x, y), (code >> 6) & 3, code & 0x3F, 0xE), x, y), owner);
        res->kind = 0xD;
        res->value = 5;
        res->pos = r;
        res->extra = (u16)info[1];
        Ta_DelUnit(x, y);
        if (Ta_GetUnitNumFrom22bitFlagList(r) == 0) {
            res->kind = 0xFE;
            res->value = 0;
            res->pos = 0xFFFF;
            res->extra = 0x10;
        }
        return 1;
    case 0x36:
        r = Ta_RemoveObjFromFlagLst2(SearchUnitByRange(0, 0, Ta_GetCurrentSide(x, y), (code >> 6) & 3, code & 0x3F, 0xE), owner);
        res->kind = 0x42;
        res->value = 0x36;
        res->pos = r;
        res->extra = (u16)info[1];
        Ta_DelUnit(x, y);
        if (Ta_GetUnitNumFrom22bitFlagList(r) == 0) {
            res->kind = 0xFE;
            res->value = 0;
            res->pos = 0xFFFF;
            res->extra = 0x10;
        }
        return 1;
    case 0x24:
        r = Ta_RemoveObjFromFlagLst2(ConvUnitIDtoFlagList_OFF(SearchUnitByRange(0, 0, Ta_GetCurrentSide(x, y), (code >> 6) & 3, code & 0x3F, 0xE), x, y), owner);
        res->kind = 0x1E;
        res->value = 0;
        res->pos = r;
        res->extra = Ta_GetCurrentSide(x, y);
        Ta_DelUnit(x, y);
        if (Ta_GetUnitNumFrom22bitFlagList(r) == 0) {
            res->kind = 0xFE;
            res->value = 0;
            res->pos = 0xFFFF;
            res->extra = 0x10;
        }
        return 1;
    case 0x25:
        switch (info[1] >> 16) {
        case 0x21:
            r = Ta_RemoveObjFromFlagLst2(ConvUnitIDtoFlagList_OFF(ConvUnitIDtoFlagList_OFF(ConvUnitIDtoFlagList_OFF(SearchUnitByRange(0, 0, Ta_GetCurrentSide(x, y), (code >> 6) & 3, code & 0x3F, 0xE), x, y), 0, 0), 1, 0), owner);
            res->kind = 0x20;
            res->value = 0;
            res->pos = r;
            res->extra = 0;
            Ta_DelUnit(x, y);
            if (Ta_GetUnitNumFrom22bitFlagList(r) == 0) {
                res->kind = 0xFE;
                res->value = 0;
                res->pos = 0xFFFF;
                res->extra = 0x10;
            }
            return 1;
        default:
            {
                u32 R25;
                s32 V25;
                s32 I25;
                s32 P25;

                if ((code & 0x3F) == 0x22) {
                    R25 = ConvUnitIDtoFlagList(0, owner, 0);
                } else {
                    R25 = Ta_RemoveObjFromFlagLst2(ConvUnitIDtoFlagList_OFF(SearchUnitByRange(0, 0, Ta_GetCurrentSide(x, y), (code >> 6) & 3, code & 0x3F, 0xE), x, y), owner);
                }
                P25 = SzDuel_GetUnitLoc(x, y);
                for (I25 = 0; I25 < Ta_GetUnitNumFrom22bitFlagList(R25); I25++) {
                    V25 = Ta_GetUnitOwnerIDFromLstCount(R25, I25);
                    res->kind = 0x1F;
                    res->value = V25;
                    res->pos = R25;
                    res->extra = P25;
                }
                Ta_DelUnit(x, y);
                if (Ta_GetUnitNumFrom22bitFlagList(R25) == 0) {
                    res->kind = 0xFE;
                    res->value = 0;
                    res->pos = 0xFFFF;
                    res->extra = 0x10;
                }
                return 1;
            }
        }
    case 0x26:
        res->kind = 0x21;
        res->value = 0;
        res->pos = Ta_GetCurrentSide(x, y);
        res->extra = 0;
        Ta_DelUnit(x, y);
        return 1;
    case 0x27:
        res->kind = 0x22;
        if (Ta_GetCurrentSide(x, y) == 0) {
            pick = 1;
        } else {
            pick = 0;
        }
        res->value = pick;
        res->pos = Ta_GetCurrentSide(x, y);
        res->extra = SzDuel_GetSummonPower((Ta_GetCurrentSide(x, y) == 0) ? 1 : 0);
        Ta_DelUnit(x, y);
        return 1;
    case 0x28:
        res->kind = 0x23;
        res->value = owner;
        res->pos = 0;
        res->extra = 0;
        Ta_DelUnit(x, y);
        return 1;
    case 0x32:
        Ta_GetCeremSacrifice(got, info[1]);
        if (got[0] < 0 || got[1] < 0 || got[2] < 0) {
            Ta_DelUnit(x, y);
            return 0;
        }
        pick = Ta_GetSacrificeUnit(got, Ta_GetCurrentSide(x, y));
        if (pick < 0) {
            Ta_DelUnit(x, y);
            return 0;
        }
        res->kind = 0x38;
        res->value = pick;
        res->pos = info[1];
        res->extra = (Ta_GetCurrentSide(x, y) << 16) | SzDuel_GetUnitLoc(x, y);
        Ta_DelUnit(x, y);
        return 1;
    default:
        Ta_DelUnit(x, y);
        return 0;
    }
}

/* Card rules: equip / enchant effects, toons, fusions (Ta_*, TaEnc_*). */

#include "common.h"

/* Half the opposing side's life points (through standing effect 0x2C), plus `pOfs`. */
s32 Ta_GetForceEffection(s32 nSide, s32 pOfs) {
    s32 var_v0;

    if (nSide < 2) {
        var_v0 = SzDuel_GetLP((nSide == 0) ? 1 : 0) >> 1;
    } else {
        var_v0 = SzDuel_GetLP((SzDuel_GetTurnOwner() == 0) ? 1 : 0) >> 1;
    }
    var_v0 = Ta_GetLPRevByNaturalEffect(0x2C, var_v0);
    var_v0 += pOfs;
    return var_v0;
}

typedef struct Entry_00248EA0 {
    u32 unk0;
    u32 value;
} Entry_00248EA0;

/* The total power change the field's equip-like effects give. */
s32 Ta_GetEnchantOfs(void) {
    s32 index;
    s32 total;
    s32 count;
    s32 id;
    u32 kind;
    Entry_00248EA0 *entry;

    total = 0;
    count = Ta_SearchUncTypeNaturalEffectUserNum(0x34);
    for (index = 0; index < count; index++) {
            id = Ta_SearchUncTypeNaturalEffectUser(0x34, index);
            if (id >= 0) {
                entry = Ta_GetUnitEffect(id >> 8, id & 0xFF, 2);
                kind = entry->value >> 16;
                switch (kind) {
                case 0:
                    total += *(u16 *)((u8 *)entry + 4);
                    break;
                case 1:
                    total -= *(u16 *)((u8 *)entry + 4);
                    break;
                }
            }
    }
    return total;
}

/* The equip result of combining hand cards `cNo1` and `cNo2`. */
s32 Ta_GetHandEnchant(s32 cNo1, s32 cNo2) {
    s32 temp_a2;

    temp_a2 = cNo2 - 0x2F0;
    if ((equipMatchTable[cNo1 * 7 + (temp_a2 >> 3)] >> (temp_a2 % 8)) & 1) {
        return Ta_GetHandEnchant3(cNo1, cNo2);
    }
    return -1;
}

/* The equip result of putting hand card `cNo2` on unit (nSide, nID). */
s32 Ta_GetHandEnchant2(s32 nSide, s32 nID, s32 cNo2) {
    extern s32 SzDuel_GetUnitCardNo();

    if (Do_ChkEncMatch(nSide, nID, cNo2) != 0) {
        return Ta_GetHandEnchant3(SzDuel_GetUnitCardNo(nSide, nID), cNo2);
    }
    return -1;
}

/* Whether card `cNo2` equips card `cNo1` (by the equip table). */
s32 Ta_GetHandEnchant3(s32 cNo1, s32 cNo2) {
    s32 result;

    switch (AnmPat_Bakura_used_for_EnchantScore[cNo2]) {
    case 6:
        result = 0x111;
        break;
    case 7:
        result = 0x1AB;
        break;
    case 8:
        switch (cNo1) {
        case 0x156:
            result = 0x1E8;
            break;
        case 7:
            result = 0x1F5;
            break;
        default:
            result = -1;
            break;
        }
        break;
    case 9:
        switch (cNo1) {
        case 0x10:
            result = func_0019A5C8() % 5 + 0xD;
            break;
        case 0x11:
            result = func_0019A5C8() % 5 + 0xD;
            break;
        case 0xA7:
            result = func_0019A5C8() % 15 + 0xD1;
            break;
        case 0x14C:
            result = func_0019A5C8() % 32 + 0x65;
            break;
        case 0x17B:
            result = (u16)TaEnc_GetRandomElf();
            break;
        default:
            result = -1;
            break;
        }
        break;
    default:
        result = cNo1 | 0x10000;
        break;
    }
    return result;
}

/* The power-up of equip effect `eNO`. */
s32 Ta_GetEncEffect(s32 eNO) {
    u8 temp_v1;
    s32 result;

    temp_v1 = D_0029D1F0[eNO];
    switch (temp_v1) {
    case 0:
        switch (AnmPat_Bakura_used_for_EnchantScore[eNO]) {
        case 0:
            result = 0x219;
            break;
        default:
            result = 0x218;
            break;
        }
        break;
    case 3:
        result = 0x21D;
        break;
    case 2:
        result = 0x21E;
        break;
    case 1:
        switch (AnmPat_Bakura_used_for_EnchantScore[eNO]) {
        case 5:
            result = 0x21C;
            break;
        default:
            result = 0x218;
            break;
        }
        break;
    default:
        result = 0x218;
        break;
    }
    return result;
}

/* Whether card `cNo` is a toon (the toon field rules). */
s32 Ta_GetToonAgreement(s32 cNo) {
    return ((s32) D_0029D586[cNo * 7] >> 1) & 1;
}

/* Whether equip effect `eNO` has an effect when applied. */
s32 TaEnc_IsEncDo(s32 eNO) {
    u8 temp_v1;

    temp_v1 = D_0029D1F0[eNO];
    switch (temp_v1) {
    case 2:
    case 3:
        return -1;
    case 4:
        if (AnmPat_Bakura_used_for_EnchantScore[eNO] == 9) {
            return -1;
        }
    default:
        return 1;
    }
}

/* How good equip card `nCardNo` is, for the computer opponent. */
s64 TaEnc_GetEncScore(s32 nCardNo) {
    switch (D_0029D1F0[nCardNo]) {
    case 0:
        return AnmPat_Bakura_used_for_EnchantScore[nCardNo];
    case 1:
    case 4:
        return 0x3E8;
    default:
        return 0;
    }
}

/* The cards that equip card `nCardNo` can be put on, into `pEncLst`; returns how many. */
s32 TaEnc_GetEnchantLst(u16 nCardNo, u16 *pEncLst) {
    s32 i;
    u16 card;
    s32 count;
    u8 *flags;

    card = 0x2F0;
    count = 0;
    i = 0;
    flags = equipMatchTable + nCardNo * 7;

    do {
        s32 offset;

        if (count >= 0xC) {
            return count;
        }
        offset = card - 0x2F0;
        if ((flags[offset >> 3] >> (offset % 8)) & 1) {
            if (card != 0x315 && card != 0x30C && card != 0x31C) {
                *pEncLst++ = card;
                count++;
            }
        }
        card++;
        i++;
    } while (i < 0x31);

    return count;
}

/* One of six cards at random (ids 0x23, 0x4F, 0x2C, 0x5C, 0x17B, 0x18A): what card 0x17B's combination gives. */
s32 TaEnc_GetRandomElf(void) {
    s32 roll;

    roll = func_0019A5C8() % 6;
    switch (roll) {
    case 0:
        return 0x23;
    case 1:
        return 0x4F;
    case 2:
        return 0x2C;
    case 3:
        return 0x5C;
    case 4:
        return 0x17B;
    case 5:
    default:
        return 0x18A;
    }
}

/* Whether equip effect `eNo` reflects an attack. */
s32 TaEnc_IsActReflexEnc(s32 eNo) {
    return (D_0029D1F0[eNo & 0xFFFF] == 0) ? 1 : 0;
}

/* The equip effect of card `nCardNo`. */
u8 TaEnc_GetEncID(s32 nCardNo) {
    return D_0029D1F0[nCardNo & 0xFFFF];
}

/* The fusion result of cards `No1` and `No2`, or none. */
u32 Fusion(s32 No1, s32 No2) {
    s32 i;
    u32 *entry;
    u32 packed;
    s32 temp;

    if (No1 < No2) {
        temp = No1;
        No1 = No2;
        No2 = temp;
    }
    entry = fusionTable;
    i = 0;
    do {
        packed = *entry;
        if ((No1 == (packed & 0x3FF)) &&
            (No2 == ((packed & 0xFFC00) >> 10))) {
            return (fusionTable[i] & 0x3FF00000) >> 20;
        }
        i++;
        entry++;
    } while (i < 0x67AC);
    return 0x3E7U;
}

/* The fusion result of unit (nSide, nID) with a wall card, or none. */
s32 WallFusion(s32 nSide, s32 nID) {
    void *unitEffect;

    unitEffect = Ta_GetUnitEffect(nSide, nID, 1);
    if ((unitEffect != NULL) && ((*(u32 *)unitEffect >> 8) == 9)) {
        return *(u16 *)((u8 *)unitEffect + 4);
    }
    return -1;
}

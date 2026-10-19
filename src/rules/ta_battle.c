/* Card rules: battles, enchantments (Battle, Enchant, Chk_Enc). */

#include "common.h"

typedef struct Effect_002464F0 {
    u32 kind;
    u16 value;
} Effect_002464F0;

typedef struct Flags_002464F0 {
    s8 unused : 2;
    s8 active : 1;
    s8 rest : 5;
} Flags_002464F0;

typedef struct Card_002464F0 {
    u8 pad0[0x10];
    Effect_002464F0 effect;
    u8 pad18[0x26];
    u8 affiliation;
    u8 pad3F[5];
    u8 type;
    u8 present;
    u8 pad46[0x11];
    Flags_002464F0 flags;
} Card_002464F0;

/* How far a unit (record `vInfo`) on square (nX, nZ) may move: its base moves, the field, leader abilities and
   effects. */
s32 GetMoveRev(s32 vInfo, s32 nX, s32 nZ) {
    s32 i;
    s32 temp_s1;
    s32 var_s2;
    s32 checkLandAgreement;
    s32 var_v0;
    u32 temp_a0;
    u32 kind;
    u32 kind2;
    u32 temp_v1;
    u8 temp_a0_3;
    u8 temp_a0_4;
    Effect_002464F0 *temp_a0_2;
    Effect_002464F0 *unitEffect;
    Effect_002464F0 *unitEffect2;

    if (vInfo == 0) {
        return 0;
    }
    var_s2 = 0;
    if (((Card_002464F0 *)vInfo)->present == 0) {
        var_v0 = Ta_IsLDAbl(4, ((Card_002464F0 *)vInfo)->type);
        if (var_v0 != 0) {
            var_v0 = 2;
        } else {
            var_v0 = 1;
        }
        return var_v0;
    }
    if (((Card_002464F0 *)vInfo)->flags.active == 0) {
        var_v0 = 1;
        temp_a0_2 = &((Card_002464F0 *)vInfo)->effect;
        if (temp_a0_2 != NULL) {
            temp_a0 = temp_a0_2->kind >> 8;
            if ((temp_a0 == 8) || ((u32) (temp_a0 - 9) < 2U)) {
                var_v0 |= 0x10;
            }
            if (temp_a0 == 0x4F) {
                return 0;
            }
            return var_v0;
        }
        return var_v0;
    }
    temp_s1 = (nZ << 8) | nX;
    checkLandAgreement = CheckLandAgreement(SzDuel_GetField(temp_s1 & 0xFF, temp_s1 >> 8), (void *)vInfo);
    switch (checkLandAgreement) {
    case 0:
    case 2:
        var_s2 = 1;
        break;
    case 1:
        var_s2 = 2;
        break;
    }
    temp_a0_2 = &((Card_002464F0 *)vInfo)->effect;
    if (temp_a0_2 != NULL) {
        temp_v1 = temp_a0_2->kind >> 8;
        if (temp_v1 == 6) {
            var_s2 = temp_a0_2->value;
        } else if ((u32) (temp_v1 - 8) < 3U) {
            var_s2 |= 0x10;
        } else if (temp_v1 == 0x4F) {
            return 0;
        }
    }
    i = 0;
    do {
        if (SzDuel_GetUnitStatus(0, i, 4) == 1) {
            if (SzDuel_GetUnitStatus(0, i, 5) == 1) {
                unitEffect = Ta_GetUnitEffect(0, i, 2);
                if (unitEffect != NULL) {
                    kind = unitEffect->kind;
                    if ((kind >> 8) == 6) {
                        switch (kind & 0x3F) {
                        case 0xF:
                            temp_a0_3 = ((Card_002464F0 *)vInfo)->affiliation;
                            if (((temp_a0_3 & 0x1F) == 0xF) && (((s32) temp_a0_3 >> 5) == 0)) {
                                var_s2 = ((var_s2 >> 4) << 4) | unitEffect->value;
                            }
                            break;
                        default:
                            var_s2 = ((var_s2 >> 4) << 4) | unitEffect->value;
                            break;
                        }
                    }
                }
            }
        }
        if ((SzDuel_GetUnitStatus(1, i, 4) == 1) && (SzDuel_GetUnitStatus(1, i, 5) == 1)) {
            unitEffect2 = Ta_GetUnitEffect(1, i, 2);
            if (unitEffect2 != NULL) {
                kind2 = unitEffect2->kind;
                if ((kind2 >> 8) == 6) {
                    switch (kind2 & 0x3F) {
                    case 0xF:
                        temp_a0_4 = ((Card_002464F0 *)vInfo)->affiliation;
                        if (((temp_a0_4 & 0x1F) == 0xF) && (((s32) temp_a0_4 >> 5) == 0)) {
                            var_s2 = ((var_s2 >> 4) << 4) | unitEffect2->value;
                        }
                        break;
                    default:
                        var_s2 = ((var_s2 >> 4) << 4) | unitEffect2->value;
                        break;
                    }
                }
            }
        }
        i += 1;
    } while (i < 0xB);
    if (Ta_SearchUncTypeNaturalEffectUser(0x43, 0) >= 0) {
        var_s2 = ((var_s2 >> 4) << 4) | 1;
    }
    var_v0 = var_s2;
    if (Ta_IsLDRangeAvilityFromLoc(temp_s1, ((Card_002464F0 *)vInfo)->type, ((Card_002464F0 *)vInfo)->affiliation & 0x1F, 0xC) == 1) {
        var_v0 = ((var_s2 >> 4) << 4) | 2;
    }
    return var_v0;
}

typedef struct Flags_00246810 {
    u8 bit0 : 1;
    u8 bit1 : 1;
    u8 bit2 : 1;
    u8 bit3 : 1;
    u8 bit4 : 1;
    u8 bit5 : 1;
    u8 bit6 : 1;
    u8 bit7 : 1;
} Flags_00246810;

typedef struct Status_00246810 {
    Flags_00246810 mode;
    s32 value1;
    s32 value2;
    s32 value3;
    Flags_00246810 flags;
} Status_00246810;

/* Packs a battle value. */
static inline s32 encode_00246810(s32 value) {
    return ((value < 0 ? 1 : 0) << 15) | (value >= 0 ? value : -value);
}

/* Resolves a battle between unit (nSide_1, ID_1) and unit (nSide_2, ID_2) on square (nX, nZ): attack against
   attack or defence, the field and attribute bonuses, attack effects, the loser's destruction and the life-point
   damage, into `eInfo`. */
s32 Battle(s32 nSide_1, s32 ID_1, s32 nSide_2, s32 ID_2, s32 nX, s32 nZ, void *eInfo) {
    extern s32 SzDuel_GetUnitLevel();
    extern s32 SzDuel_GetUnitCardNo();
    extern s32 SzDuel_GetUnitCurseRest();
    Status_00246810 status;
    Status_00246810 *p = &status;
    s32 *out = eInfo;
    s32 sp120;
    s32 sp138;
    s32 sp13C;
    s32 sp140;
    s32 sp144;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 cardNo;
    s32 cardNo2;
    s32 cardNo3;
    s32 cardNo3In;
    s32 temp_s0_3;
    s32 temp_s0_4;
    s32 temp_s0_5;
    s32 temp_s0_6;
    s32 temp_s0_7;
    s32 temp_s0_8;
    s32 temp_s0_9;
    s32 temp_s1;
    s32 atkEfc;
    s32 unitAttr;
    s32 paramOfs;
    s32 temp_s5_2;
    s32 enc;
    s32 enc2;
    s32 chkAttrAdv;
    s32 atkEfc2;
    s32 unitStatus;
    s32 var_fp;
    s32 var_s7;

    p->value1 = 0;
    p->value2 = 0;
    p->value3 = 0;
    p->flags.bit0 = 0;
    p->flags.bit1 = 0;
    p->flags.bit2 = 0;
    p->flags.bit3 = 0;
    p->flags.bit4 = 0;
    p->mode.bit1 = 0;
    p->mode.bit2 = 0;
    p->mode.bit0 = 1;
    p->flags.bit5 = 0;
    p->flags.bit6 = 0;
    temp_s1 = SzDuel_GetUnitKind(nSide_1, ID_1) >> 5;
    temp_a0 = SzDuel_GetUnitKind(nSide_2, ID_2) >> 5;
    sp120 = 0;
    var_fp = 0;
    var_s7 = 0;
    if ((temp_s1 == 0) && (temp_a0 == 0)) {
        if (ID_1 == 0) {
            atkEfc = Manage_AtkEfc(nSide_1, ID_1, nSide_2, ID_2, p);
            paramOfs = Ta_GetParamOfs(SzDuel_GetUnit(nSide_2, ID_2), nX, nZ, 1);
            temp_s5_2 = p->value2 + SzDuel_GetUnitAP(nSide_2, ID_2, 0);
            temp_s5_2 = GetParCap(temp_s5_2 + paramOfs);
            SzDuel_CalcUnitAP(nSide_2, ID_2, 0, p->value2);
            SzDuel_CalcUnitDP(nSide_2, ID_2, 0, p->value2);
            p->value2 = encode_00246810(p->value2);
            if (Ta_IsLDAbl(6, nSide_1) != 0) {
                out[0] = 0x5D;
                out[1] = (s32) ((p->value2 << 0x10) | ((nSide_2 << 8) | ID_2));
                out[2] = nSide_1;
                out[3] = (((p->flags.bit6 << 1) | ((atkEfc >> 0x18) & 1)) << 0x16) | ((temp_s5_2 >> 1) | (((p->flags.bit5 << 1) | ((atkEfc >> 0x10) & 1)) << 0x14));
            } else {
                out[0] = 0x5D;
                out[1] = (s32) ((nSide_2 << 8) | ID_2);
                out[2] = nSide_1;
                out[3] = (((p->flags.bit6 << 1) | ((atkEfc >> 0x18) & 1)) << 0x16) | (temp_s5_2 | (((p->flags.bit5 << 1) | ((atkEfc >> 0x10) & 1)) << 0x14));
            }
            return 1;
        }
        unitAttr = SzDuel_GetUnitAttr(nSide_2, ID_2);
        chkAttrAdv = ChkAttrAdv(unitAttr, SzDuel_GetUnitAttr(nSide_1, ID_1));
        switch (chkAttrAdv) {                        /* switch 1; irregular */
        case 1:                                     /* switch 1 */
            if (SzDuel_GetUnitCurseRest(nSide_1, ID_1) == 0) {
                var_fp = 1;
            }
            break;
        case -1:                                    /* switch 1 */
            if (SzDuel_GetUnitCurseRest(nSide_2, ID_2) == 0) {
                var_s7 = 1;
            }
            break;
        }
        atkEfc2 = Manage_AtkEfc(nSide_1, ID_1, nSide_2, ID_2, p);
        if ((atkEfc2 & 0xFF) == 1) {
            temp_a0_2 = (atkEfc2 >> 0x18) & 1;
            if ((temp_a0_2 == 1) && (((atkEfc2 >> 0x10) & 1) == 1)) {
                out[0] = 0x5E;
                out[1] = (s32) ((nSide_2 << 8) | ID_2);
                out[2] = (s32) ((nSide_1 << 8) | ID_1);
                out[3] = (s32) ((p->flags.bit2 << 0x1B) | ((var_s7 << 0x1A) | ((var_fp << 0x19) | ((((p->flags.bit6 << 1) | 1) << 0x16) | ((((p->flags.bit5 << 1) | 1) << 0x14) | 0xCFFFF)))) | 0x10000000);
                cardNo = SzDuel_GetUnitCardNo(nSide_1, ID_1);
                                SzData_CalcExp(nSide_1, cardNo, 0, (SzDuel_GetUnitLevel(nSide_2, ID_2, 0) + 2) * 2);
                cardNo3In = SzDuel_GetUnitCardNo(nSide_2, ID_2);
                                SzData_CalcExp(nSide_2, cardNo3In, 0, (SzDuel_GetUnitLevel(nSide_1, ID_1, 0) + 2) * 2);
                return 1;
            }
            if (temp_a0_2 == 1) {
                out[0] = 0x5E;
                out[1] = (s32) ((nSide_2 << 8) | ID_2);
                out[2] = (s32) ((nSide_1 << 8) | ID_1);
                out[3] = (s32) ((p->flags.bit2 << 0x1B) | ((var_s7 << 0x1A) | ((var_fp << 0x19) | ((((p->flags.bit6 << 1) | 1) << 0x16) | (((p->flags.bit5 << 1) << 0x14) | 0x8FFFF)))) | 0x10000000);
                temp_s0_3 = SzDuel_GetUnitCardNo(nSide_1, ID_1);
                                SzData_CalcExp(nSide_1, temp_s0_3, 0, (SzDuel_GetUnitLevel(nSide_2, ID_2, 0) + 2) * 2);
                return 1;
            }
            if (((atkEfc2 >> 0x10) & 1) == 1) {
                out[0] = 0x5E;
                out[1] = (s32) ((nSide_2 << 8) | ID_2);
                out[2] = (s32) ((nSide_1 << 8) | ID_1);
                out[3] = (s32) ((p->flags.bit2 << 0x1B) | ((var_s7 << 0x1A) | ((var_fp << 0x19) | ((p->flags.bit6 << 0x17) | ((((p->flags.bit5 << 1) | 1) << 0x14) | 0x4FFFF)))));
                temp_s0_4 = SzDuel_GetUnitCardNo(nSide_2, ID_2);
                                SzData_CalcExp(nSide_2, temp_s0_4, 0, (SzDuel_GetUnitLevel(nSide_1, ID_1, 0) + 2) * 2);
                return 1;
            }

        }
        unitStatus = SzDuel_GetUnitStatus(nSide_1, ID_1, 3);
        switch (unitStatus) {                        /* switch 2; irregular */
        case 1:                                     /* switch 2 */
            if (p->flags.bit3 == 1) {
                SzDuel_CalcUnitAP(nSide_1, ID_1, 4, 0);
                SzDuel_CalcUnitDP(nSide_1, ID_1, 4, 0);
                sp13C = GetParCap(SzDuel_GetUnitDP(nSide_1, ID_1, 0) + Ta_GetParamOfs(SzDuel_GetUnit(nSide_1, ID_1), nX, nZ, 0));
            } else {
                sp13C = GetParCap(p->value1 + SzDuel_GetUnitDP(nSide_1, ID_1, 0) + Ta_GetParamOfs(SzDuel_GetUnit(nSide_1, ID_1), nX, nZ, 0));
                SzDuel_CalcUnitAP(nSide_1, ID_1, 0, p->value1);
                SzDuel_CalcUnitDP(nSide_1, ID_1, 0, p->value1);
                p->value1 = encode_00246810(p->value1);
            }
            if (p->flags.bit4 == 1) {
                SzDuel_CalcUnitAP(nSide_2, ID_2, 4, 0);
                SzDuel_CalcUnitDP(nSide_2, ID_2, 4, 0);
                sp138 = GetParCap(SzDuel_GetUnitAP(nSide_2, ID_2, 0) + Ta_GetParamOfs(SzDuel_GetUnit(nSide_2, ID_2), nX, nZ, 1));
            } else {
                sp138 = GetParCap(p->value2 + SzDuel_GetUnitAP(nSide_2, ID_2, 0) + Ta_GetParamOfs(SzDuel_GetUnit(nSide_2, ID_2), nX, nZ, 1));
                SzDuel_CalcUnitAP(nSide_2, ID_2, 0, p->value2);
                SzDuel_CalcUnitDP(nSide_2, ID_2, 0, p->value2);
                p->value2 = encode_00246810(p->value2);
            }
            if (sp13C > sp138) {

                if (p->flags.bit1 == 0) {
                    sp120 += sp13C - sp138;

                }
                out[0] = 0x5E;
                out[1] = (s32) ((p->value2 << 0x10) | ((nSide_2 << 8) | ID_2));
                out[2] = (s32) ((p->value1 << 0x10) | ((nSide_1 << 8) | ID_1));
                out[3] = (s32) ((p->flags.bit2 << 0x1B) | ((var_s7 << 0x1A) | ((var_fp << 0x19) | ((((p->flags.bit6 << 1) | ((atkEfc2 >> 0x18) & 1)) << 0x16) | (sp120 | 0x20000 | (((p->flags.bit5 << 1) | ((atkEfc2 >> 0x10) & 1)) << 0x14)) | 0x01000000))) | 0x10000000);
                return 1;
            }
            if (sp13C == sp138) {
                out[0] = 0x5E;
                out[1] = (s32) ((p->value2 << 0x10) | ((nSide_2 << 8) | ID_2));
                out[2] = (s32) ((p->value1 << 0x10) | ((nSide_1 << 8) | ID_1));
                out[3] = (s32) ((p->flags.bit2 << 0x1B) | ((var_s7 << 0x1A) | ((var_fp << 0x19) | ((((p->flags.bit6 << 1) | ((atkEfc2 >> 0x18) & 1)) << 0x16) | (((p->flags.bit5 << 1) | ((atkEfc2 >> 0x10) & 1)) << 0x14) | 0x01000000))));
                return 1;
            }
            if (sp13C < sp138) {
                out[0] = 0x5E;
                out[1] = (s32) ((p->value2 << 0x10) | ((nSide_2 << 8) | ID_2));
                out[2] = (s32) ((p->value1 << 0x10) | ((nSide_1 << 8) | ID_1));
                out[3] = (s32) ((p->flags.bit2 << 0x1B) | ((var_s7 << 0x1A) | ((var_fp << 0x19) | ((((p->flags.bit6 << 1) | ((atkEfc2 >> 0x18) & 1)) << 0x16) | ((((p->flags.bit5 << 1) | ((atkEfc2 >> 0x10) & 1)) << 0x14) | 0x40000)))));
                temp_s0_5 = SzDuel_GetUnitCardNo(nSide_2, ID_2);
                                SzData_CalcExp(nSide_2, temp_s0_5, 0, (SzDuel_GetUnitLevel(nSide_1, ID_1, 0) + 2) * 2);
                return 1;
            }
            break;
        case 0:                                     /* switch 2 */
            if (p->flags.bit3 == 1) {
                SzDuel_CalcUnitAP(nSide_1, ID_1, 4, 0);
                SzDuel_CalcUnitDP(nSide_1, ID_1, 4, 0);
                sp140 = GetParCap(SzDuel_GetUnitAP(nSide_1, ID_1, 0) + Ta_GetParamOfs(SzDuel_GetUnit(nSide_1, ID_1), nX, nZ, 1));
            } else {
                sp140 = GetParCap(p->value1 + SzDuel_GetUnitAP(nSide_1, ID_1, 0) + Ta_GetParamOfs(SzDuel_GetUnit(nSide_1, ID_1), nX, nZ, 1));
                SzDuel_CalcUnitAP(nSide_1, ID_1, 0, p->value1);
                SzDuel_CalcUnitDP(nSide_1, ID_1, 0, p->value1);
                p->value1 = encode_00246810(p->value1);
            }
            if (p->flags.bit4 == 1) {
                SzDuel_CalcUnitAP(nSide_2, ID_2, 4, 0);
                SzDuel_CalcUnitDP(nSide_2, ID_2, 4, 0);
                sp144 = GetParCap(SzDuel_GetUnitAP(nSide_2, ID_2, 0) + Ta_GetParamOfs(SzDuel_GetUnit(nSide_2, ID_2), nX, nZ, 1));
            } else {
                sp144 = GetParCap(p->value2 + SzDuel_GetUnitAP(nSide_2, ID_2, 0) + Ta_GetParamOfs(SzDuel_GetUnit(nSide_2, ID_2), nX, nZ, 1));
                SzDuel_CalcUnitAP(nSide_2, ID_2, 0, p->value2);
                SzDuel_CalcUnitDP(nSide_2, ID_2, 0, p->value2);
                p->value2 = encode_00246810(p->value2);
            }
            if (sp140 > sp144) {
                if (p->flags.bit1 == 0) {
                    sp120 = sp140 - sp144;
                }
                out[0] = 0x5E;
                out[1] = (s32) ((p->value2 << 0x10) | ((nSide_2 << 8) | ID_2));
                out[2] = (s32) ((p->value1 << 0x10) | ((nSide_1 << 8) | ID_1));
                out[3] = (s32) ((p->flags.bit2 << 0x1B) | ((var_s7 << 0x1A) | ((var_fp << 0x19) | ((((p->flags.bit6 << 1) | ((atkEfc2 >> 0x18) & 1)) << 0x16) | (sp120 | 0xA0000 | (((p->flags.bit5 << 1) | ((atkEfc2 >> 0x10) & 1)) << 0x14))))) | 0x10000000);
                if (sp120 <= 0) {
                    temp_s0_6 = SzDuel_GetUnitCardNo(nSide_1, ID_1);
                                        SzData_CalcExp(nSide_1, temp_s0_6, 0, (SzDuel_GetUnitLevel(nSide_2, ID_2, 0) + 2) * 2);
                } else {
                    temp_s0_7 = SzDuel_GetUnitCardNo(nSide_1, ID_1);
                                        SzData_CalcExp(nSide_1, temp_s0_7, 0, SzDuel_GetUnitLevel(nSide_2, ID_2, 0) * 4);
                }
                return 1;
            }
            if (sp140 == sp144) {
                out[0] = 0x5E;
                out[1] = (s32) ((p->value2 << 0x10) | ((nSide_2 << 8) | ID_2));
                out[2] = (s32) ((p->value1 << 0x10) | ((nSide_1 << 8) | ID_1));
                out[3] = (s32) ((p->flags.bit2 << 0x1B) | ((var_s7 << 0x1A) | ((var_fp << 0x19) | ((((p->flags.bit6 << 1) | ((atkEfc2 >> 0x18) & 1)) << 0x16) | ((((p->flags.bit5 << 1) | ((atkEfc2 >> 0x10) & 1)) << 0x14) | 0xC0000)))) | 0x10000000);
                temp_s0_8 = SzDuel_GetUnitCardNo(nSide_1, ID_1);
                                SzData_CalcExp(nSide_1, temp_s0_8, 0, (SzDuel_GetUnitLevel(nSide_2, ID_2, 0) + 2) * 2);
                temp_s0_9 = SzDuel_GetUnitCardNo(nSide_2, ID_2);
                                SzData_CalcExp(nSide_2, temp_s0_9, 0, (SzDuel_GetUnitLevel(nSide_1, ID_1, 0) + 2) * 2);
                return 1;
            }
            if (sp140 < sp144) {
                if (!(p->flags.bit0)) {
                    sp120 = sp144 - sp140;
                }
                out[0] = 0x5E;
                out[1] = (s32) ((p->value2 << 0x10) | ((nSide_2 << 8) | ID_2));
                out[2] = (s32) ((p->value1 << 0x10) | ((nSide_1 << 8) | ID_1));
                out[3] = (s32) ((p->flags.bit2 << 0x1B) | ((var_s7 << 0x1A) | ((var_fp << 0x19) | ((((p->flags.bit6 << 1) | ((atkEfc2 >> 0x18) & 1)) << 0x16) | (sp120 | 0x50000 | (((p->flags.bit5 << 1) | ((atkEfc2 >> 0x10) & 1)) << 0x14))))));
                if (sp120 <= 0) {
                    cardNo2 = SzDuel_GetUnitCardNo(nSide_2, ID_2);
                                        SzData_CalcExp(nSide_2, cardNo2, 0, (SzDuel_GetUnitLevel(nSide_1, ID_1, 0) + 2) * 2);
                } else {
                    cardNo3 = SzDuel_GetUnitCardNo(nSide_2, ID_2);
                                        SzData_CalcExp(nSide_2, cardNo3, 0, SzDuel_GetUnitLevel(nSide_1, ID_1, 0) * 4);
                }
                return 1;
            }
            break;
        }
    } else {
        if ((temp_s1 == 0) && ((temp_a0 == 1) || ((u32)(temp_a0 - 3) < 3U))) {
            out[0] = 0x5F;
            out[1] = (s32) ((nSide_1 << 8) | ID_1);
            out[2] = (s32) ((nSide_2 << 8) | ID_2);
            out[3] = 1;
            return 1;
        }
        if (temp_s1 == 0) {
            if (temp_a0 == 2) {
                if (Ta_IsLDRangeAvility(nSide_1, ID_1, 0xB) == 1) {
                    out[0] = 0x5F;
                    out[1] = (s32) ((nSide_1 << 8) | ID_1);
                    out[2] = (s32) ((nSide_2 << 8) | ID_2);
                    out[3] = 3;
                    return 0x10001;
                }
                if (Ta_IsResistAll(nSide_1, ID_1) != 0) {
                    out[0] = 0x5F;
                    out[1] = (s32) ((nSide_1 << 8) | ID_1);
                    out[2] = (s32) ((nSide_2 << 8) | ID_2);
                    out[3] = 1;
                    return 0x10001;
                }
                enc = Chk_Enc(nSide_1, ID_1, SzDuel_GetUnitCardNo(nSide_2, ID_2));
                if (enc == 0x3E7) {
                    out[0] = 0x5F;
                    out[1] = (s32) ((nSide_1 << 8) | ID_1);
                    out[2] = (s32) ((nSide_2 << 8) | ID_2);
                    out[3] = 1;
                    return 0x10001;
                }
                if (((enc >> 0x1E) & 1) == 1) {
                    SzDuel_SetUnitStatus(nSide_2, ID_2, 2, 1);
                    out[0] = 0x2B;
                    out[1] = (s32) ((nSide_2 << 8) | ID_2);
                    out[2] = (s32) ((nSide_1 << 8) | ID_1);
                    out[3] = (s32) ((enc >> 0xE) & 0x3FFF);
                    return 0x10001;
                }
                if ((enc >> 0xE) == 0x219) {
                    SzDuel_SetUnitStatus(nSide_2, ID_2, 2, 1);
                    out[0] = 0x25;
                    out[1] = (s32) ((nSide_1 << 8) | ID_1);
                    out[2] = (s32) ((nSide_2 << 8) | ID_2);
                    out[3] = (s32) ((enc & 0x3FFF) | (Ta_GetCurrentSide(nSide_2, ID_2) << 0x10));
                } else {
                    SzDuel_SetUnitStatus(nSide_2, ID_2, 2, 1);
                    out[0] = 0x24;
                    out[1] = (s32) ((nSide_1 << 8) | ID_1);
                    out[2] = (s32) ((nSide_2 << 8) | ID_2);
                    out[3] = enc;
                }
                return 0x10001;
            }
        }

        if (temp_s1 == 2) {
            if (temp_a0 == 0) {
                SzData_CalcExp(nSide_2, SzDuel_GetUnitCardNo(nSide_2, ID_2), 0, 6);
                if (Ta_IsLDRangeAvility(nSide_2, ID_2, 0xB) == 1) {
                    out[0] = 0x5F;
                    out[1] = (s32) ((nSide_1 << 8) | ID_1);
                    out[2] = (s32) ((nSide_2 << 8) | ID_2);
                    out[3] = 2;
                    return 1;
                }
                if (Ta_IsResistAll(nSide_2, ID_2) != 0) {
                    out[0] = 0x5F;
                    out[1] = (s32) ((nSide_1 << 8) | ID_1);
                    out[2] = (s32) ((nSide_2 << 8) | ID_2);
                    out[3] = 0;
                    return 1;
                }
                enc2 = Chk_Enc(nSide_2, ID_2, SzDuel_GetUnitCardNo(nSide_1, ID_1));
                if (enc2 == 0x3E7) {
                    out[0] = 0x5F;
                    out[1] = (s32) ((nSide_1 << 8) | ID_1);
                    out[2] = (s32) ((nSide_2 << 8) | ID_2);
                    out[3] = 0;
                    return 1;
                }
                if (((enc2 >> 0x1E) & 1) == 1) {
                    SzDuel_SetUnitStatus(nSide_1, ID_1, 2, 1);
                    out[0] = 0x2B;
                    out[1] = (s32) ((nSide_1 << 8) | ID_1);
                    out[2] = (s32) ((nSide_2 << 8) | ID_2);
                    out[3] = (s32) ((enc2 >> 0xE) & 0x3FFF);
                    return 1;
                }
                if ((enc2 >> 0xE) == 0x219) {
                    SzDuel_SetUnitStatus(nSide_1, ID_1, 2, 1);
                    out[0] = 0x25;
                    out[1] = (s32) ((nSide_1 << 8) | ID_1);
                    out[2] = (s32) ((nSide_2 << 8) | ID_2);
                    out[3] = (s32) ((enc2 & 0x3FFF) | (Ta_GetCurrentSide(nSide_1, ID_1) << 0x10));
                } else {
                    SzDuel_SetUnitStatus(nSide_1, ID_1, 2, 1);
                    out[0] = 0x24;
                    out[1] = (s32) ((nSide_1 << 8) | ID_1);
                    out[2] = (s32) ((nSide_2 << 8) | ID_2);
                    out[3] = enc2;
                }
                return 1;
            }

        }
        if (((u32)(temp_s1 - 1) < 5U) && ((u32) temp_a0 < 6U)) {
            out[0] = 0x5F;
            out[1] = (s32) ((nSide_1 << 8) | ID_1);
            out[2] = (s32) ((nSide_2 << 8) | ID_2);
            out[3] = 0;
            if (temp_a0 == 0) {
                SzData_CalcExp(nSide_2, SzDuel_GetUnitCardNo(nSide_2, ID_2), 0, 6);
            }
            return 1;
        }
    }
    return 0;
}

/* Resolves stacking unit (nSide_2, ID_2) onto unit (nSide_1, ID_1) (heap): a fusion, an equip, or a replacement,
   into `eInfo`. */
s32 SelfHeap(s32 nSide_1, s32 ID_1, s32 nSide_2, s32 ID_2, s32 *eInfo) {
    s32 type0;
    s32 type1;

    extern s32 SzDuel_GetUnitCardNo();

    if (ID_2 == 0) {
        eInfo[0] = 0x5F;
        eInfo[1] = (nSide_1 << 8) | ID_1;
        eInfo[2] = (nSide_2 << 8) | ID_2;
        eInfo[3] = 0;
        return 1;
    }
    type0 = SzDuel_GetUnitKind(nSide_1, ID_1) >> 5;
    type1 = SzDuel_GetUnitKind(nSide_2, ID_2) >> 5;
    if (type0 == 0 && type1 == 0) {
        s32 card0;
        u32 result;

        if (ID_1 == 0) {
            eInfo[0] = 0x5F;
            eInfo[1] = (nSide_2 << 8) | ID_2;
            eInfo[2] = (nSide_1 << 8) | ID_1;
            eInfo[3] = 1;
            return 1;
        }
        card0 = SzDuel_GetUnitCardNo(nSide_1, ID_1);
        result = Fusion(card0, SzDuel_GetUnitCardNo(nSide_2, ID_2));
        eInfo[0] = 0x64;
        eInfo[1] = (nSide_1 << 8) | ID_1;
        eInfo[2] = (nSide_2 << 8) | ID_2;
        eInfo[3] = result;
        return 1;
    }
    if (type0 == 0 && type1 == 2) {
        s32 result;

        if (ID_1 == 0) {
            eInfo[0] = 0x5F;
            eInfo[1] = (nSide_2 << 8) | ID_2;
            eInfo[2] = (nSide_1 << 8) | ID_1;
            eInfo[3] = 1;
            return 1;
        }
        result = Chk_Enc(nSide_1, ID_1, SzDuel_GetUnitCardNo(nSide_2, ID_2));
        if (result == 0x3E7) {
            eInfo[0] = 0x24;
            eInfo[1] = (nSide_1 << 8) | ID_1;
            eInfo[2] = (nSide_2 << 8) | ID_2;
            eInfo[3] = 0x3E7;
            return 1;
        }
        if (((result >> 30) & 1) == 1) {
            eInfo[0] = 0x2B;
            eInfo[1] = (nSide_2 << 8) | ID_2;
            eInfo[2] = (nSide_1 << 8) | ID_1;
            eInfo[3] = (result >> 14) & 0x3FFF;
            return 0x10001;
        }
        if ((result >> 14) == 0x219) {
            eInfo[0] = 0x25;
            eInfo[1] = (nSide_1 << 8) | ID_1;
            eInfo[2] = (nSide_2 << 8) | ID_2;
            eInfo[3] = (result & 0x3FFF) | (Ta_GetCurrentSide(nSide_1, ID_1) << 16);
        } else {
            eInfo[0] = 0x24;
            eInfo[1] = (nSide_1 << 8) | ID_1;
            eInfo[2] = (nSide_2 << 8) | ID_2;
            eInfo[3] = result;
        }
        return 0x10001;
    }
    if (type0 == 2 && type1 == 0) {
        s32 result;

        if (ID_2 == 0) {
            eInfo[0] = 0x5F;
            eInfo[1] = (nSide_1 << 8) | ID_1;
            eInfo[2] = (nSide_2 << 8) | ID_2;
            eInfo[3] = 0;
            return 1;
        }
        result = Chk_Enc(nSide_2, ID_2, SzDuel_GetUnitCardNo(nSide_1, ID_1));
        if (result == 0x3E7) {
            eInfo[0] = 0x24;
            eInfo[1] = (nSide_1 << 8) | ID_1;
            eInfo[2] = (nSide_2 << 8) | ID_2;
            eInfo[3] = 0x3E7;
            return 1;
        }
        if (((result >> 30) & 1) == 1) {
            eInfo[0] = 0x2B;
            eInfo[1] = (nSide_1 << 8) | ID_1;
            eInfo[2] = (nSide_2 << 8) | ID_2;
            eInfo[3] = (result >> 14) & 0x3FFF;
            return 1;
        }
        if ((result >> 14) == 0x219) {
            eInfo[0] = 0x25;
            eInfo[1] = (nSide_1 << 8) | ID_1;
            eInfo[2] = (nSide_2 << 8) | ID_2;
            eInfo[3] = (result & 0x3FFF) | (Ta_GetCurrentSide(nSide_2, ID_2) << 16);
        } else {
            eInfo[0] = 0x24;
            eInfo[1] = (nSide_1 << 8) | ID_1;
            eInfo[2] = (nSide_2 << 8) | ID_2;
            eInfo[3] = result;
        }
        return 1;
    }
    eInfo[0] = 0x5F;
    eInfo[1] = (nSide_1 << 8) | ID_1;
    eInfo[2] = (nSide_2 << 8) | ID_2;
    eInfo[3] = 0;
    return 1;
}

/* Whether equip card `nEncCardNo` can be equipped to unit (nSide, nID). */
s32 Do_ChkEncMatch(u32 nSide, s32 nID, s32 nEncCardNo) {
    extern s32 SzDuel_GetUnitCardNo();
    s32 offset;
    s32 row;

    if (nSide < 2U) {
        if (nID == 0) {
            return 0;
        }
    }

    if (nEncCardNo == 0x304) {
        if ((SzDuel_GetUnitKind((s32)nSide, nID) >> 5) == 0) {
            if ((SzDuel_GetUnitKind((s32)nSide, nID) & 0x1F) == 2) {
                return 1;
            }
        }
        return 0;
    }

    row = SzDuel_GetUnitCardNo(nSide, nID) * 7;
    offset = nEncCardNo - 0x2F0;
    return ((equipMatchTable + (offset >> 3))[row] >> (offset % 8)) & 1;
}

extern int func_001E1030_b(int a, int b);
extern unsigned *func_001E0B70_b(int a, int b, int n);
extern void func_002503B0_b(int a, int b, unsigned char n);
extern int func_001E15E0_b(int a, int b, int value);
/* Applies one kind of equip result (power-ups, life points, status). */
static inline int apply_kind_00248460(int a, int b, int c, int d, int total, int id)
{
    int val;
    unsigned *p;

    {
        val = D_0029CF32[id];
        switch (D_0029D1F0[id]) {
        case 0:
            if (val == 0) {
                id = d & 0xff;
                total = Ta_GetForceEffection(id, total);
                if (c >> 16) {
                    TaUtil_CalcUnitAP(a, b, 1, total);
                    TaUtil_CalcUnitDP(a, b, 1, total);
                } else {
                    TaUtil_CalcUnitAP(a, b, 0, total);
                    TaUtil_CalcUnitDP(a, b, 0, total);
                }
                SzDuel_CalcLP(id == 0 ? 1 : 0, 1, total);
                return c;
            } else {
                total = val + total;
                if (c >> 16) {
                    TaUtil_CalcUnitAP(a, b, 1, total);
                    TaUtil_CalcUnitDP(a, b, 1, total);
                    return c;
                } else {
                    TaUtil_CalcUnitAP(a, b, 0, total);
                    TaUtil_CalcUnitDP(a, b, 0, total);
                    return c;
                }
            }
        case 1:
            switch (val) {
            case 1:
                p = func_001E0B70_b(a, b, 4);
                p[0] = 5211;
                p[1] = 0;
                p = func_001E0B70_b(a, b, 3);
                p[0] = 14428;
                p[1] = 0x1f0129;
                return c;
            case 2:
                p = func_001E0B70_b(a, b, 0);
                p[0] = 1152;
                p[1] = 0;
                return c;
            case 3:
                p = func_001E0B70_b(a, b, 0);
                p[0] = 1159;
                p[1] = 0;
                return c;
            case 4:
                p = func_001E0B70_b(a, b, 0);
                p[0] = 1153;
                p[1] = 0;
                return c;
            case 5:
                p = func_001E0B70_b(a, b, 4);
                p[0] = 765;
                p[1] = 0x10009;
                return c;
            }
            break;
        case 2:
            TaUtil_CalcUnitAP(a, b, 4, 0);
            TaUtil_CalcUnitDP(a, b, 4, 0);
            func_002503B0_b(a, b, 0);
            func_001E15E0_b(a, b, 0);
            return c;
        case 3:
            func_002503B0_b(a, b, 255);
            SzDuel_SetUnitStatus(a, b, 0, 1);
            return c;
        case 4:
            return c;
        }
    }
    return c;
}

/* Equips unit `cID` of side `nSide` with equip effect `eNO` (owner `nEffectOwner`). */
int Enchant(int nSide, int cID, int eNO, int nEffectOwner)
{
    int total;
    int id;

    func_001E1030_b(nSide, cID);
    total = 0;
    total += Ta_GetEnchantOfs();
    id = eNO & 0x3fff;
    if (Do_ChkEncMatch(nSide, cID, id) != 0) {
        eNO = apply_kind_00248460(nSide, cID, eNO, nEffectOwner, total, id);
    } else {
        eNO = -1;
    }
    return eNO;
}

/* Whether equip effect `eNO` works on card `cNO`. */
s32 Do_Chk_Enc(s32 cNO, s32 eNO) {
    s32 bit;

    bit = eNO - 0x2F0;
    if ((equipMatchTable[cNO * 7 + (bit >> 3)] >> (bit % 8)) & 1) {
        switch (D_0029D1F0[eNO]) {
        case 4:
            switch (D_0029CF32[eNO]) {
            case 6:
                return eNO | 0x40444000;
            case 7:
                return eNO | 0x406AC000;
            case 8:
                switch (cNO) {
                case 0x156:
                    return eNO | 0x407A0000;
                case 7:
                    return eNO | 0x407D4000;
                }
                break;
            case 9:
                switch (cNO) {
                case 0x10:
                    return eNO | (((func_0019A5C8() % 5 + 0xD) << 14) | 0x40000000);
                case 0x11:
                    return eNO | (((func_0019A5C8() % 5 + 0xD) << 14) | 0x40000000);
                case 0xA7:
                    return eNO | (((func_0019A5C8() % 15 + 0xD1) << 14) | 0x40000000);
                case 0x14C:
                    return eNO | (((func_0019A5C8() % 32 + 0x65) << 14) | 0x40000000);
                case 0x17B:
                    return eNO | (((u16)TaEnc_GetRandomElf() << 14) | 0x40000000);
                }
                break;
            }
            break;
        case 0:
            switch (D_0029CF32[eNO]) {
            case 0:
                return eNO | 0x864000;
            default:
                return eNO | 0x860000;
            }
        case 3:
            return eNO | 0x874000;
        case 2:
            return eNO | 0x878000;
        case 1:
            switch (D_0029CF32[eNO]) {
            case 5:
                return eNO | 0x870000;
            default:
                return eNO | 0x860000;
            }
        default:
            return eNO | 0x860000;
        }
    } else {
        return 0x3E7;
    }
    return 0x3E7;
}

/* Whether equip effect `eNO` works on unit `cID` of side `nSide`. */
s32 Chk_Enc(s32 nSide, s32 cID, s32 eNO) {
    s32 kind;
    extern s32 SzDuel_GetUnitCardNo();

    kind = SzDuel_GetUnitCardNo(nSide, cID);
    if (Do_ChkEncMatch(nSide, cID, eNO) != 0) {
        switch (D_0029D1F0[eNO]) {
        case 4:
            switch (D_0029CF32[eNO]) {
            case 6:
                return eNO | 0x40444000;
            case 7:
                return eNO | 0x406AC000;
            case 8:
                switch (kind) {
                case 0x156:
                    return eNO | 0x407A0000;
                case 7:
                    return eNO | 0x407D4000;
                }
                break;
            case 9:
                switch (kind) {
                case 0x10:
                    return eNO | (((func_0019A5C8() % 5 + 0xD) << 14) | 0x40000000);
                case 0x11:
                    return eNO | (((func_0019A5C8() % 5 + 0xD) << 14) | 0x40000000);
                case 0xA7:
                    return eNO | (((func_0019A5C8() % 15 + 0xD1) << 14) | 0x40000000);
                case 0x14C:
                    return eNO | (((func_0019A5C8() % 32 + 0x65) << 14) | 0x40000000);
                case 0x17B:
                    return eNO | (((u16)TaEnc_GetRandomElf() << 14) | 0x40000000);
                }
                break;
            }
            break;
        case 0:
            switch (D_0029CF32[eNO]) {
            case 0:
                return eNO | 0x864000;
            default:
                return eNO | 0x860000;
            }
        case 3:
            return eNO | 0x874000;
        case 2:
            return eNO | 0x878000;
        case 1:
            switch (D_0029CF32[eNO]) {
            case 5:
                return eNO | 0x870000;
            default:
                return eNO | 0x860000;
            }
        default:
            return eNO | 0x860000;
        }
    } else {
        return 0x3E7;
    }
    return 0x3E7;
}

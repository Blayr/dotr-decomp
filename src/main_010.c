#include "common.h"

s32 TaLogic_IsOpenUnit_0013D3D0(s32 arg0, s32 arg1) {
    extern s32 SzDuel_GetUnitCardNo();
    s32 card;
    s32 owner;
    s32 position;
    u8 count;
    s32 slot;
    s32 other;
    s32 otherPosition;

    card = SzDuel_GetUnitCardNo(arg0, arg1);
    owner = Ta_IsUnitControl(arg0, arg1);
    position = SzDuel_GetUnitLoc(arg0, arg1);
    SzDuel_GetUnitEffect(arg0, arg1, 0);
    count = 0;
    if (SzDuel_GetUnitStatus(arg0, arg1, 4) != 0) {
        return 0;
    }
    switch (SzDuel_GetUnitKind(arg0, arg1) >> 5) {
    case 0:
        switch (card) {
        case 0xC5:
            slot = 1;
            while (1) {
                if (SzDuel_GetUnitCardNo(arg0, slot) == 0x99) {
                    if (arg0 == Ta_IsUnitControl(arg0, slot)) {
                        count++;
                    }
                }
                if (SzDuel_GetUnitCardNo(arg0 == 0 ? 1 : 0, slot) == 0x99) {
                    if (arg0 == Ta_IsUnitControl(arg0 == 0 ? 1 : 0, slot)) {
                        count++;
                    }
                }
                slot++;
                if (slot > 5) {
                    break;
                }
            }
            if (count >= 2) {
                return 1;
            }
            break;
        case 0x99:
            slot = 1;
            while (1) {
                if (SzDuel_GetUnitCardNo(arg0, slot) == 0xC5) {
                    if (arg0 == Ta_IsUnitControl(arg0, slot)) {
                        count++;
                    }
                }
                if (SzDuel_GetUnitCardNo(arg0 == 0 ? 1 : 0, slot) == 0xC5) {
                    if (arg0 == Ta_IsUnitControl(arg0 == 0 ? 1 : 0, slot)) {
                        count++;
                    }
                }
                slot++;
                if (slot > 5) {
                    break;
                }
            }
            if (count >= 2) {
                return 1;
            }
            break;
        case 0xAA:
            slot = 1;
            while (1) {
                if (SzDuel_GetUnitCardNo(arg0, slot) == 0xAB) {
                    if (arg0 == Ta_IsUnitControl(arg0, slot)) {
                        count++;
                    }
                }
                if (SzDuel_GetUnitCardNo(arg0 == 0 ? 1 : 0, slot) == 0xAB) {
                    if (arg0 == Ta_IsUnitControl(arg0 == 0 ? 1 : 0, slot)) {
                        count++;
                    }
                }
                slot++;
                if (slot > 5) {
                    break;
                }
            }
            if (count >= 2) {
                return 1;
            }
            break;
        case 0xAB:
            slot = 1;
            while (1) {
                if (SzDuel_GetUnitCardNo(arg0, slot) == 0xAA) {
                    if (arg0 == Ta_IsUnitControl(arg0, slot)) {
                        count++;
                    }
                }
                if (SzDuel_GetUnitCardNo(arg0 == 0 ? 1 : 0, slot) == 0xAA) {
                    if (arg0 == Ta_IsUnitControl(arg0 == 0 ? 1 : 0, slot)) {
                        count++;
                    }
                }
                slot++;
                if (slot > 5) {
                    break;
                }
            }
            if (count >= 2) {
                return 1;
            }
            break;
        }
        return 2;
    case 5:
        if (TaLogic_GetActionReaction(arg0, arg1, 0, 0, 6, 0) == 5) {
            return 2;
        }
        if (TaLogic010_IsDoCerem(Ta_IsUnitControl(arg0, arg1), card) == 1) {
            if (SzDuel_GetField(position & 0xFF, position >> 8) != 9) {
                return 1;
            }
        }
        break;
    case 1:
        if (TaLogic_GetActionReaction(arg0, arg1, 0, 0, 6, 0) == 5) {
            return 2;
        }
        other = TaLogic010_GetUseThunderBolt(owner);
        otherPosition = SzDuel_GetUnitLoc(other >> 8, other & 0xFF);
        if ((position & 0xFF) == (otherPosition & 0xFF) ||
            (position >> 8) == (otherPosition >> 8)) {
            return 1;
        }
        break;
    default:
        return 2;
    }
    return 2;
}

static inline s32 max_0013D880(s32 a, s32 b) {
    if (b < a) {
        return a;
    }
    return b;
}

s32 TaLogic010_IsOpenMoveUnit(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 min_y;
    s32 min_x;

    min_y = arg3 < arg5 ? arg3 : arg5;
    arg5 = max_0013D880(arg3, arg5);
    min_x = arg2 < arg4 ? arg2 : arg4;
    arg4 = max_0013D880(arg2, arg4);
    if ((arg4 - min_x) + (arg5 - min_y) != 2) {
        return 0;
    }
    if (SzDuel_GetUnit(arg0, arg1) == 0) {
        return 0;
    }
    if (SzDuel_GetUnitStatus(arg0, arg1, 0) == 0) {
        return CheckLandAgreement2(SzDuel_GetField(arg2, arg3), arg0, arg1) != 1 ? 0 : 1;
    }
    return 0;
}

s32 TaLogic010_IsDoCerem(s32 arg0, s32 arg1) {
    s32 sp50[4];
    s32 var_s0;
    s32 temp_v0;
    s32 temp_s2;
    s32 temp_s3;
    s32 temp_v0_2;
    s32 temp_v0_3;

    Ta_GetCeremSacrifice(sp50, *(s32 *)((u8 *)TaHand_GetCardEffect(arg1, 0) + 4));
    if ((temp_v0 = Ta_GetSacrificeUnit(sp50, arg0)) < 0) {
        return 0;
    }
    var_s0 = 0;
    if (var_s0 < Ta_GetUnitNumFrom22bitFlagList(temp_v0)) {
        do {
            temp_v0_2 = Ta_GetUnitOwnerIDFromLstCount(temp_v0, var_s0);
            temp_s3 = temp_v0_2 >> 8;
            temp_s2 = temp_v0_2 & 0xFF;
            temp_v0_3 = SzDuel_GetUnitLoc(temp_s3, temp_s2);
            if (TaUtil_GetUnitAP(temp_s3, temp_s2, temp_v0_3 & 0xFF, temp_v0_3 >> 8) >= 0xBB8) {
                return 0;
            }
            var_s0++;
        } while (var_s0 < Ta_GetUnitNumFrom22bitFlagList(temp_v0));
    }
    return 1;
}

s32 TaLogic_GetWarnHideLvl_0013DA70(s32 arg0) {
    if (SzDuel_GetLP(arg0) > 1000) {
        if (SzDuel_GetUnitMonsterCount(arg0) >= 5) {
            return 0;
        }
        return 0;
    }
    return 0;
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
} Req_0013DAD0;

typedef struct {
    u8 pad0[0x160];
    u16 list[32];    /* 0x160 */
    u8 idx : 5;      /* 0x1A0 */
    u8 pad1A0 : 3;
    u8 pad1A1;
    u16 count;       /* 0x1A2 */
} Work_0013DAD0;

s32 TaLogic_GetInputQueFromMinimumTask_b(void *, void *, s32);

s32 func_0013DAD0(s32 arg0, void *arg1) {
    Req_0013DAD0 req;
    Work_0013DAD0 *w;
    s32 i;
    s32 ret;

    w = arg1;
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
        if (TaLogic_GetMinimumTask_00139890(w, &req, arg0) == 0) {
            return 0x800;
        }
        if (TaLogic_GetInputQueFromMinimumTask_b(w, &req, arg0) < 0) {
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

#pragma conditional_move off

s32 TaLogic_GetMinimumTask_0013DCA0(void *work, void *arg1, s32 arg2) {
    u16 *arg0 = work;
    s32 side;
    s32 found;
    s32 result;
    s32 index;

    side = SzDuel_GetTurnOwner();
    found = 0;
    if ((result = TaLogic_GetNextActiveUnit_0013E3D0(arg0, side, (s32)arg1)) < 0) {
        return 0;
    }
    index = TaLogic_GetActionUnitFromOwnerID(arg0, result & 0xFFFF);
    if (index < 0) {
        return 0;
    }
    if ((result >> 16) == 1) {
        if (((arg0[index * 8 + 2] >> 8) & 0xFF) == 10) {
            TaLogic_InitRogicControl(arg0 + index * 8, 1);
        } else {
            TaLogic_InitRogicControl(arg0 + index * 8, 0);
        }
        return 1;
    }
    TaLogic_CommandUnit_0013E1D0(arg0 + index * 8);
    switch ((arg0[index * 8 + 2] >> 8) & 0xFF) {
    case 5:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_RunMission_001402F0(arg0 + index * 8, side, arg1, 1);
            found = 1;
        }
        break;
    case 2:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            if (TaLogic_GetMinimumTask_AtkMission_00140830(arg0 + index * 8, side, arg1, 1) < 0) {
                TaLogic_InitRogicControl(arg0 + index * 8, 1);
                return 1;
            }
            found = 1;
        }
        break;
    case 10:
        if (TaLogic_GetMinimumTask_Summon_0013EEE0(arg0[index * 8], side, (s32)arg1) < 0) {
            TaLogic_InitRogicControl(arg0 + index * 8, 1);
            *(u8 *)((u8 *)arg1 + 2) = 0xFF;
            *(s32 *)((u8 *)arg1 + 0xC) = 0;
        } else {
            TaLogic_InitRogicControl(arg0 + index * 8, 1);
            found = 1;
        }
        break;
    case 6:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_MoveMission_00140E10(arg0 + index * 8, side, arg1, 1, 0);
            found = 1;
        }
        break;
    case 3:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_MoveMission_00140E10(arg0 + index * 8, side, arg1, 1, 1);
            found = 1;
        }
        break;
    case 9:
        TaLogic_GetMinimumTask_EncMission(arg0 + index * 8, side, arg1, 1, 0, TaLogic_GetWarnHideLvl_00141B30(side), 2, 1);
        found = 1;
        break;
    case 11:
        TaLogic_GetMinimumTask_TrapMission_001415F0(arg0 + index * 8, side, arg1, 1);
        found = 1;
        break;
    case 14:
        TaLogic_GetMinimumTask_DoNone(arg0 + index * 8, side, arg1);
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
    switch (arg0[index * 8 + 2] & 0xFF) {
    case 5:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_RunMission_001402F0(arg0 + index * 8, side, arg1, 0);
            found = 1;
        }
        break;
    case 2:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            if (TaLogic_GetMinimumTask_AtkMission_00140830(arg0 + index * 8, side, arg1, 0) < 0) {
                TaLogic_GetMinimumTask_RunMission_001402F0(arg0 + index * 8, side, arg1, 0);
            }
            found = 1;
        }
        break;
    case 10:
        if (TaLogic_GetMinimumTask_Summon_0013EEE0(arg0[index * 8], side, (s32)arg1) < 0) {
            TaLogic_InitRogicControl(arg0 + index * 8, 0);
            *(u8 *)((u8 *)arg1 + 2) = 0xFF;
            found = 1;
            *(s32 *)((u8 *)arg1 + 0xC) = 0;
        } else {
            TaLogic_InitRogicControl(arg0 + index * 8, 0);
            found = 1;
        }
        break;
    case 6:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_MoveMission_00140E10(arg0 + index * 8, side, arg1, 0, 0);
            found = 1;
        }
        break;
    case 3:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_MoveMission_00140E10(arg0 + index * 8, side, arg1, 0, 1);
            found = 1;
        }
        break;
    case 11:
        found = 1;
        TaLogic_GetMinimumTask_TrapMission_001415F0(arg0 + index * 8, side, arg1, 0);
        break;
    case 9:
        TaLogic_GetMinimumTask_EncMission(arg0 + index * 8, side, arg1, 0, 0, TaLogic_GetWarnHideLvl_00141B30(side), 2, 1);
        found = 1;
        break;
    case 14:
        TaLogic_GetMinimumTask_DoNone(arg0 + index * 8, side, arg1);
        break;
    default:
        return 0;
    }
    if (found == 1) {
        return 1;
    }
    return 0;
}
#pragma conditional_move reset

typedef struct {
    u16 id;
    u16 pad2;
    u16 value;
    u16 pad6;
    s32 status;
} Record_0013E1D0;


s32 TaLogic_CommandUnit_0013E1D0(u8 *arg0) {
    s32 category;
    s32 temp_s0;

    temp_s0 = Ta_IsUnitControl(((Record_0013E1D0 *)arg0)->id >> 8, ((Record_0013E1D0 *)arg0)->id & 0xFF);
    if (SzDuel_GetUnit(((Record_0013E1D0 *)arg0)->id >> 8, ((Record_0013E1D0 *)arg0)->id & 0xFF) != 0) {
        if (SzDuel_GetUnitStatus(((Record_0013E1D0 *)arg0)->id >> 8, ((Record_0013E1D0 *)arg0)->id & 0xFF, 0) == 0) {
            if (((Record_0013E1D0 *)arg0)->id != 0xFFFF) {
                if ((((Record_0013E1D0 *)arg0)->id & 0xFF) == 0) {
                    if (((Record_0013E1D0 *)arg0)->status == -1) {
                        if (TaLogic_IsAttackedNow(((Record_0013E1D0 *)arg0)->id >> 8, ((Record_0013E1D0 *)arg0)->id & 0xFF, 0) == 1) {
                            if (SzDuel_InqHandPhase(((Record_0013E1D0 *)arg0)->id >> 8) == 1) {
                                ((Record_0013E1D0 *)arg0)->value = 0x50A;
                            } else {
                                ((Record_0013E1D0 *)arg0)->value = 0x5FF;
                            }
                        } else {
                            if (SzDuel_InqHandPhase(((Record_0013E1D0 *)arg0)->id >> 8) == 1) {
                                ((Record_0013E1D0 *)arg0)->value = 0xA05;
                            } else {
                                ((Record_0013E1D0 *)arg0)->value = 0x5FF;
                            }
                        }
                    }
                } else {
                    category = SzDuel_GetUnitKind(((Record_0013E1D0 *)arg0)->id >> 8, ((Record_0013E1D0 *)arg0)->id & 0xFF) >> 5;
                    switch (category) {
                    case 0:
                        if (TaUtil_IsExMonster(((Record_0013E1D0 *)arg0)->id >> 8, ((Record_0013E1D0 *)arg0)->id & 0xFF) == 1) {
                            TaLogic011_CommandEfcMonster(arg0);
                        } else {
                            TaLogic011_CommandBtlUnit(arg0, 1);
                        }
                        break;
                    case 2:
                        TaLogic_CommandEncUnit(arg0, 2, 0, TaLogic_GetWarnHideLvl_00141B30(temp_s0) & 0xFF);
                        break;
                    case 3:
                        if (TaLogic_CommandGunnerUnit(arg0, 0) == 1) {
                            ((Record_0013E1D0 *)arg0)->value = 0xBFF;
                        } else {
                            ((Record_0013E1D0 *)arg0)->value = 0x5FF;
                        }
                        break;
                    default:
                        ((Record_0013E1D0 *)arg0)->value = 0x5FF;
                        break;
                    }
                }
                return 1;
            }
        }
    }
    return 0;
}

s32 TaLogic_GetNextActiveUnit_0013E3D0(u16 *arg0, s32 arg1, s32 arg2) {
    s32 i;
    s32 pos;
    s32 ret;
    s32 idx;
    u16 list[22];

    for (i = 0; i < 22; i++) {
        list[i] = 0xFFFF;
    }
    TaLogic_GetUnitCtlLst(arg1, list, 0x1D, 1);
    ret = TaLogic_GetAtkUnitNow(arg1, list, arg0);
    if (ret >= 0) {
        return ret;
    }
    for (i = 0; i < 22; i++) {
        list[i] = 0xFFFF;
    }
    TaLogic_GetUnitCtlLst(arg1, list, 0x1E, 1);
    for (i = 0; i < TaLogic_GetUnitCtlLstLen(list); i++) {
        if ((SzDuel_GetUnitKind(list[i] >> 8, list[i] & 0xFF) >> 5) == 3 &&
            TaLogic_IsUnitReadyMove(list[i]) == 1 && TaLogic_IsPickUp(list[i]) == 1) {
            return list[i];
        }
    }
    pos = arg1 << 8;
    idx = TaLogic_GetActionUnitFromOwnerID(arg0, pos);
    TaLogic_CommandUnit_0013E1D0(arg0 + idx * 8);
    if (((arg0[idx * 8 + 2] >> 8) & 0xFF) == 10) {
        if (SzDuel_InqHandPhase(arg1) == 1 && TaLogic_GetMinimumTask_Summon_0013EEE0(pos, arg1, arg2) >= 0) {
            return pos | 0x10000;
        }
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_GetUnitStatus(arg1, 0, 0) == 0) {
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_InqHandPhase(arg1) == 1 && TaLogic_GetMinimumTask_Summon_0013EEE0(pos, arg1, arg2) >= 0) {
        return pos | 0x10000;
    }
    for (i = 0; i < 22; i++) {
        list[i] = 0xFFFF;
    }
    TaLogic_GetUnitCtlLst(arg1, list, 0x1F, 1);
    for (i = 0; i < TaLogic_GetUnitCtlLstLen(list); i++) {
        if (TaLogic_IsUnitReadyMove(list[i]) == 1 && TaLogic_IsPickUp(list[i]) == 1) {
            return list[i];
        }
    }
    for (i = 0; i < 22; i++) {
        list[i] = 0xFFFF;
    }
    TaLogic_GetUnitCtlLst(arg1, list, 0x1F, 1);
    for (i = 0; i < TaLogic_GetUnitCtlLstLen(list); i++) {
        if (SzDuel_GetUnitStatus(list[i] >> 8, list[i] & 0xFF, 0) == 0 && TaLogic_IsPickUp(list[i]) == 1) {
            return list[i];
        }
    }
    return -1;
}

typedef struct {
    u16 coordinates;
    u16 unk02;
    s16 state;
    u16 unk06;
    union {
        u32 word;
        struct {
            u16 low;
            u16 high;
        } halves;
    } data;
} Entry_0013E7B0;

typedef struct {
    u16 card;
    u8 flag;
    u8 pad;
} Slot_0013E7B0;


void TaLogic011_CommandBtlUnit(void *arg0, s32 arg1) {
    extern void TaLogic_InitIgnoreLst();
    extern s32 TaLogic_IsRootOpen();
    extern s32 TaLogic011_GetNearUnit();
    Entry_0013E7B0 *entry = arg0;
    s32 side;
    s32 player;
    s32 other;
    s32 pos;
    s32 otherPos;
    s32 i;
    u8 work[0x70];
    Slot_0013E7B0 list[22];
    s16 countA;
    s16 countB;

    if (SzDuel_GetUnit(entry->coordinates >> 8, entry->coordinates & 0xFF) != 0) {
        side = Ta_GetCurrentSide(entry->coordinates >> 8, entry->coordinates & 0xFF);
        other = (side == 0 ? 1 : 0) << 8;
        pos = SzDuel_GetUnitLoc(entry->coordinates >> 8, entry->coordinates & 0xFF);
        otherPos = SzDuel_GetUnitLoc(other >> 8, other & 0xFF);
        player = SzDuel_GetUnit(entry->coordinates >> 8, entry->coordinates & 0xFF);
        for (i = 0; i < 22; i++) {
            list[i].card = 0xFFFF;
            list[i].flag = 0xFF;
        }
        TaLogic_InitIgnoreLst(work);
        if (arg1 != 0) {
            if (TaLogic_IsRootOpen(entry->coordinates >> 8, entry->coordinates & 0xFF, pos & 0xFF, pos >> 8,
                              other >> 8, other & 0xFF, otherPos & 0xFF, otherPos >> 8, 2) > 0) {
                entry->state = 0x2FF;
                entry->data.word = (other << 16) | entry->data.halves.low;
                return;
            }
        }
        countB = 0;
        countA = 0;
        i = 1;
        while (1) {
            switch (TaLogic011_GetNearUnit(entry, 0, player, pos & 0xFF, pos >> 8,
                                  Ta_GetCurrentSide(entry->coordinates >> 8, entry->coordinates & 0xFF) == 0 ? 1 : 0,
                                  i & 0xFF, TaLogic_GetWarnHideLvl_00141B30(side), list, 0, &countA, &countB, 2, work)) {
            case 3:
                entry->state = 0x6FF;
                entry->data.word = (pos << 16) | entry->data.halves.low;
                return;
            case 2:
                entry->state = 0x3FF;
                entry->data.word = (pos << 16) | entry->data.halves.low;
                return;
            case 1:
                return;
            case 0:
                entry->state = 0x5FF;
                return;
            }
            i++;
            if (i > 2) {
                break;
            }
        }
        TaLogic011_CommandDefenseUnit(entry);
    }
}

void TaLogic011_GetNearUnit(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28) {
    TaLogic_GetNearUnit(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
                  arg_sp0, arg_sp8, arg_sp10, arg_sp18, arg_sp20,
                  0, 0x708, arg_sp28);
}


typedef struct {
    u16 code;
    u16 unknown2;
    u16 state;
    u16 unknown6;
    u32 data;
} Entry_0013EA80;

void TaLogic011_CommandDefenseUnit(void *arg0) {
    Entry_0013EA80 *entry = arg0;
    s32 packed;
    s32 result;

    packed = SzDuel_GetUnitLoc(entry->code >> 8, entry->code & 0xFF);
    Ta_IsUnitControl(entry->code >> 8, entry->code & 0xFF);
    result = TaLogic011_GetNearMountain(SzDuel_GetUnit(entry->code >> 8, entry->code & 0xFF), packed & 0xFF, packed >> 8);
    if (result >= 0) {
        entry->state = 0x6FF;
        entry->data = (result << 16) | (entry->data & 0xFFFF);
    } else {
        entry->state = 0x5FF;
    }
}

s32 TaLogic011_GetNearMountain(s32 arg0, s32 arg1, s32 arg2) {
    s32 x;
    s32 y;
    s32 card;
    s32 best;
    s32 dist;
    s32 result;
    extern s32 TaLogic_IsUnitWin4();

    best = 14;
    for (x = 0; x < 7; x++) {
        for (y = 0; y < 7; y++) {
            if (SzDuel_GetField(x, y) == 2) {
                if ((card = SzDuel_GetMapUnitID(x, y)) < 0) {
                    dist = (((arg1 < x) ? x : arg1) - ((x < arg1) ? x : arg1)) + (((arg2 < y) ? y : arg2) - ((y < arg2) ? y : arg2));
                    if (dist >= 0 && dist < best) {
                        best = dist;
                        result = (y << 8) | x;
                    }
                } else if (Ta_IsUnitControl(card >> 8, card & 0xFF) != Ta_IsUnitControl2((void *)arg0)) {
                    if (TaLogic_IsUnitWin4(arg0, card, TaLogic_GetWarnHideLvl_00141B30(Ta_IsUnitControl2((void *)arg0)), x, y, 0) > 0) {
                        dist = (((arg1 < x) ? x : arg1) - ((x < arg1) ? x : arg1)) + (((arg2 < y) ? y : arg2) - ((y < arg2) ? y : arg2));
                        if (dist >= 0 && dist < best) {
                            best = dist;
                            result = (y << 8) | x;
                        }
                    }
                }
            }
        }
    }
    return result;
}

struct InitEntry_0013ECF0 {
    u16 value;
    u8 flag;
    u8 pad;
};

void TaLogic011_CommandEfcMonster(void *arg0) {
    extern s32 SzDuel_GetUnitCardNo();
    extern void TaLogic_InitIgnoreLst();
    u8 scratch[112];
    struct InitEntry_0013ECF0 entries[22];
    s32 i;
    struct InitEntry_0013ECF0 *entry;
    s32 card;
    s32 color;
    s32 code;
    s32 value;

    if (SzDuel_GetUnit((s32)*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF) == 0) {
        return;
    }

    card = Ta_GetCurrentSide((s32)*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF);
    color = SzDuel_GetUnitLoc((s32)*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF);
    entry = entries;
    i = 0;
    do {
        i++;
        entry->value = 0xFFFF;
        entry->flag = 0xFF;
        entry++;
    } while (i < 22);

    TaLogic_InitIgnoreLst(scratch);
    code = SzDuel_GetUnitCardNo((s32)*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF);
    switch (code) {
    case 0x182:
        if (TaLogic011_IsUseBindChain(card) == 1) {
            *(u16 *)((u8 *)arg0 + 4) = 0x6FF;
            *(u32 *)((u8 *)arg0 + 8) = (color << 16) | *(u16 *)((u8 *)arg0 + 8);
            return;
        }
        break;
    case 0x184:
        value = SzDuel_GetLP(card);
        if (value < SzDuel_GetLP(card == 0 ? 1 : 0)) {
            *(u16 *)((u8 *)arg0 + 4) = 0x6FF;
            *(u32 *)((u8 *)arg0 + 8) = (color << 16) | *(u16 *)((u8 *)arg0 + 8);
            return;
        }
        break;
    case 0x179:
        if ((TaLogic011_IsUseLifeHourGlass(card) == 1) && (TaLogic_CommandGunnerUnit(arg0, 0) == 1)) {
            *(u16 *)((u8 *)arg0 + 4) = 0xBFF;
            return;
        }
        break;
    case 0x186:
        if ((TaLogic011_IsUseBraveHourGlass(card) == 1) && (TaLogic_CommandGunnerUnit(arg0, 0) == 1)) {
            *(u16 *)((u8 *)arg0 + 4) = 0xBFF;
            return;
        }
        break;
    }
    TaLogic011_CommandBtlUnit(arg0, 1);
}

typedef struct {
    u8 data[0x3C];
    u16 unk3C;
    u8 pad3E[0x22];
} Work_0013EEE0;

typedef struct {
    s16 id;
    u8 kind;
    u8 pad3;
    s16 value;
    u8 pad6[6];
    s32 unkC;
} Ctx_0013EEE0;

s32 TaLogic_GetMinimumTask_Summon_0013EEE0(s32 arg0, s32 arg1, s32 arg2) {
    extern s32 TaLogic_GetUnitNum();
    Work_0013EEE0 work;
    s32 ret;
    s32 res;
    s32 pos;
    s32 kind;
    Ctx_0013EEE0 *ctx = (Ctx_0013EEE0 *)arg2;

    ctx->id = arg0;
    if (SzDuel_InqHandPhase(arg1) == 0) {
        return -1;
    }
    if (TaLogic_GetUnitNum(arg1, 0) == 5 && TaLogic_GetUnitNum(arg1, 1) == 5) {
        return -1;
    }
    kind = TaLogic011_IsHandPlay(arg1, &work);
    if (kind < 0) {
        return -1;
    }
    ctx->kind = 10;
    ctx->unkC = 0;
    pos = SzDuel_GetUnitLoc(arg0 >> 8, arg0 & 0xFF);
    ret = TaLogic_GetNearCard2(&work, pos & 0xFF, pos >> 8, arg1 == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, TaLogic_GetWarnHideLvl_00141B30(arg1));
    if (kind == 0) {
        if (TaLogic011_SetComboQue(arg1, ctx, &work) >= 0) {
            if (ret < 0) {
                if (SzDuel_GetUnitMonsterCount(arg1) < 4) {
                    res = TaLogic011_GetSummonPiece(arg1, 0, &work, ret);
                    if (res < 0) {
                        return -1;
                    }
                    ctx->value = res;
                    return 1;
                }
            } else {
                res = TaLogic011_GetSummonPiece(arg1, 0, &work, ret);
                if (res < 0) {
                    return -1;
                }
                ctx->value = res;
                return 1;
            }
        }
    } else if (kind == 2) {
        TaLogic011_SetSpecialComboQue(arg1, ctx, &work);
        res = TaLogic011_GetSummonPiece(arg1, kind & 0xFF, &work, ret);
        if (res < 0) {
            return -1;
        }
        ctx->value = res;
        return 1;
    }
    if (kind == 3) {
        TaLogic011_GetSpecComboPlay(arg1, ctx, &work);
        res = TaLogic011_GetSummonPiece(arg1, kind & 0xFF, &work, ret);
        if (res < 0) {
            return -1;
        }
        ctx->value = res;
        return 1;
    }
    res = TaLogic011_GetSpellPlay(arg1, (u8 *)ctx, &work, work.unk3C);
    if (res < 0) {
        return -1;
    }
    res = TaLogic011_GetSummonPiece(arg1, res & 0xFF, &work, -1);
    if (res < 0) {
        return -1;
    }
    ctx->value = res;
    return 1;
}

s32 TaLogic011_IsHandPlay(s32 arg0, void *arg1) {
    extern s32 TaLogic_GetUnitNum();
    s32 ids[8];
    s32 data[8];
    u8 type = (u8)TaLogic_GetUnitNum(arg0, 0);
    u8 attr = (u8)TaLogic_GetUnitNum(arg0, 1);

    if (arg1 == NULL) {
        return -1;
    }
    TaHand_GetNextHand(arg0, ids);
    if (type == 5) {
        s32 result = TaLogic011_GetSpellPlay(arg0, (u8 *)data, arg1, 0x3E7);
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
        count = TaHand_GetNextHandNum(arg0);
        if (i < count) {
            p = ids;
            do {
                if ((TaHand_GetCardKind(*p) >> 5) == 0 && TaHand_IsCardSummon2(arg0, *p) == 1) {
                    SzDuel_InitCardInfo(arg1, ids[i]);
                    return 0;
                }
                p++;
                i++;
                count = TaHand_GetNextHandNum(arg0);
            } while (i < count);
        }
        return -1;
    }
    if (TaLogic011_IsUseReversalGoddess(arg0) == 1) {
        if (TaLogic011_GetSpecCardPlay(arg0, ids, arg1, data, 0x170) >= 0) {
            return 2;
        }
    }
    if (TaLogic011_GetSpecComboPlay(arg0, (u8 *)data, arg1) >= 0) {
        return 3;
    }
    {
        s32 *p;
        s32 i;
        s32 count;

        i = 0;
        count = TaHand_GetNextHandNum(arg0);
        if (i < count) {
            p = ids;
            do {
                if ((TaHand_GetCardKind(*p) >> 5) == 0 && TaHand_IsCardSummon2(arg0, *p) == 1) {
                    return 0;
                }
                p++;
                i++;
                count = TaHand_GetNextHandNum(arg0);
            } while (i < count);
        }
    }
    {
        s32 result = TaLogic011_GetSpellPlay(arg0, (u8 *)data, arg1, 0x3E7);
        if (result >= 0) {
            return result;
        } else {
            return -1;
        }
    }
}

s32 TaLogic011_GetSpecComboPlay(s32 arg0, void *arg1, void *arg2) {
    s32 cards[8];
    s32 index;
    s32 found;
    s32 *first;
    s32 *second;
    s32 secondIndex;

    found = 0;
    TaHand_GetNextHand(arg0, cards);
    index = 0;
    if (index < TaHand_GetNextHandNum(arg0)) {
        first = cards;
        do {
            if (*first == 0x320) {
                *((s8 *)arg1 + 7) = index;
                SzDuel_InitCardInfo(arg2, *first);
                found = 1;
            }
            first++;
            index++;
        } while (index < TaHand_GetNextHandNum(arg0));
    }
    if (found == 1) {
        secondIndex = 0;
        if (secondIndex < TaHand_GetNextHandNum(arg0)) {
            second = cards;
            do {
                if (((TaHand_GetCardKind(*second) >> 5) == 0) &&
                    (Ta_GetHandEnchant(*second, 0x320) >= 0) &&
                    (TaHand_IsCardSummon(arg0, *second) == 1)) {
                    if ((*second != 0x31B) && (*second != 0x31C)) {
                        *((s8 *)arg1 + 7) = secondIndex;
                        SzDuel_InitCardInfo(arg2, cards[secondIndex]);
                        return TaHand_GetCardKind(cards[secondIndex]) >> 5;
                    }
                }
                second++;
                secondIndex++;
            } while (secondIndex < TaHand_GetNextHandNum(arg0));
        }
    }
    return -1;
}

s32 TaLogic011_GetSpecCardPlay(s32 arg0, s32 *arg1, void *arg2, void *arg3, s32 arg4) {
    s32 i;

    for (i = 0; i < TaHand_GetNextHandNum(arg0); i++) {
        if (TaHand_IsCardSummon2(arg0, arg1[i]) == 1 &&
            (arg4 & 0xFFFF) == arg1[i] &&
            TaHand_IsCardSummon2(arg0, arg1[i]) == 1) {
            *((s8 *)arg3 + 6) = i;
            SzDuel_InitCardInfo(arg2, arg1[i]);
            return TaHand_GetCardKind(arg1[i]) >> 5;
        }
    }
    return -1;
}

s32 TaLogic011_GetSpellPlay(s32 arg0, u8 *arg1, void *arg2, s32 arg3) {
    s32 buf[8];
    s32 i;

    TaHand_GetNextHand(arg0, buf);
    if (arg2 == NULL) {
        return -1;
    }
    for (i = 0; i < 5; i++) {
        arg1[i + 6] = 0xFF;
    }
    for (i = 0; i < TaHand_GetNextHandNum(arg0); i++) {
        if (arg3 == buf[i] && arg3 != 999) {
            arg1[6] = i;
            SzDuel_InitCardInfo(arg2, buf[i]);
            return 1;
        }
    }
    for (i = 0; i < TaHand_GetNextHandNum(arg0); i++) {
        if ((TaHand_GetCardKind(buf[i]) >> 5) != 0 && (TaHand_GetCardKind(buf[i]) >> 5) != 2) {
            arg1[6] = i;
            SzDuel_InitCardInfo(arg2, buf[i]);
            return 1;
        }
    }
    for (i = 0; i < TaHand_GetNextHandNum(arg0); i++) {
        if ((TaHand_GetCardKind(buf[i]) >> 5) != 0 && buf[i] != 0x320) {
            arg1[6] = i;
            SzDuel_InitCardInfo(arg2, buf[i]);
            return 1;
        }
    }
    return -1;
}

s32 TaLogic011_SetComboQue(s32 arg0, u8 *arg1, u8 *arg2) {
    extern s32 TaLogic_GetEnchantQue();
    s32 spA0[8];
    s32 spC0[7];
    s16 spDC;
    s16 spDE;
    s32 var_s5;
    s32 temp_s6;
    s32 temp_s6_2;
    s32 var_s0;
    s32 var_s7;

    if (arg2 == NULL) {
        return -1;
    }
    TaHand_GetNextHand(arg0, spC0);
    var_s7 = -1;
    var_s0 = -1;
    var_s5 = 0;
    if (0 < TaHand_GetNextHandNum(arg0)) {
        s32 *var_s1;
        s32 *var_s2;

        var_s1 = spC0;
        var_s2 = spA0;
        do {
            spDE = 0;
            spDC = 0;
            temp_s6 = *var_s1;
            *var_s2 = 0;
            if ((TaHand_GetCardKind(temp_s6) >> 5) == 0) {
                if (Taku_Get_WinCount() < 3) {
                    *var_s2 = (s32)TaLogic_GetFusionTree2(
                        arg0, *var_s2, var_s5 & 0xFF, temp_s6 & 0xFFFF,
                        0, (u16 *)&spDC, (u16 *)&spDE);
                } else {
                    *var_s2 = (s32)TaLogic_GetFusionTree(
                        arg0, (struct TreeTag *)*var_s2, var_s5 & 0xFF, temp_s6 & 0xFFFF,
                        0, (u16 *)&spDC, (u16 *)&spDE);
                }
                *var_s2 = (s32)TaLogic_GetFusionRes((u16 *)*var_s2);
                temp_s6_2 = TaLogic_GetEnchantQue(arg0, *var_s2, 0, 0);
                if (TaHand_IsCardSummon2(arg0, temp_s6) == 1) {
                    if (var_s7 < temp_s6_2) {
                        if (Taku_Get_WinCount() > 3) {
                            TaLogic_ConvEmptyCombo_0013FA90(arg0, (void *)*var_s2, spC0);
                        }
                        TaLogic_CopyArray((u8 *)*var_s2 + 2, arg1 + 6);
                        SzDuel_InitCardInfo(arg2, *(u16 *)*var_s2);
                        var_s7 = temp_s6_2;
                        *(s16 *)(arg2 + 0x38) = (s16)((temp_s6_2 >> 16)
                            - (*(u16 *)(*(u8 **)arg2 + 8) & 0x1FFF));
                        *(s16 *)(arg2 + 0x3A) = (s16)((temp_s6_2 & 0xFFFF)
                            - (*(s16 *)(*(u8 **)arg2 + 0xA) & 0x1FFF));
                        if (var_s0 < temp_s6_2) {
                            var_s0 = temp_s6_2;
                        }
                    }
                } else if (var_s0 < temp_s6_2) {
                    var_s0 = temp_s6_2;
                }
            }
            var_s1 += 1;
            var_s2 += 1;
            var_s5 += 1;
        } while (var_s5 < TaHand_GetNextHandNum(arg0));
    }
    return var_s0;
}

typedef struct {
    u16 id;
    u8 values[5];
} Info_0013FA90;

void TaLogic_ConvEmptyCombo_0013FA90(s32 arg0, void *arg1, s32 *arg2) {
    Info_0013FA90 *info = arg1;
    u8 buf[5];
    s32 count;
    s32 i;
    s32 card;
    u8 level;
    u32 cost;
    extern u32 TaHand_GetCardAPDP();

    if (info != NULL) {
        level = TaHand_GetCardSummonCost2(info->id, arg0);
        for (i = 0; i < 5; i++) {
            buf[i] = 0xFF;
        }
        for (i = 0, count = 0; i < TaHand_GetNextHandNum(arg0); i++) {
            if ((u8)TaLogic_IsUseHandInCombo(i, info->values) == 0) {
                buf[count++] = i;
            }
        }
        if (count != 0) {
            for (i = 0; i < (u8)TaLogic_GetArrayLength(buf); i++) {
                card = arg2[buf[i]];
                if (card != 0x3E7 && TaLogic011_IsRefuseEmptyCombo(card) == 0 && level >= TaHand_GetCardSummonCost2(card, arg0)) {
                    cost = TaHand_GetCardAPDP(card);
                    if ((cost & 0xFFFF) + (cost >> 16) * 2 < 0xC1D && TaHand_IsCardEffect(card) == 2 &&
                        (u16)TaLogic_GetHandFusion(info->id, (u16)card) == 0x3E7) {
                        TaLogic_AddEmptyCombo(info->values, buf[i]);
                    }
                }
            }
        }
    }
}

s32 TaLogic011_IsRefuseEmptyCombo(s32 arg0) {
    if ((TaHand_GetCardKind(arg0) >> 5) != 0) {
        return 1;
    }
    return (TaHand_IsCardEffect(arg0) != 0) ? 1 : 0;
}

typedef struct {
    u8 pad0[6];
    u8 slot[5];
} Obj1_0013FCC0;

typedef struct {
    u8 pad0[0x3C];
    u16 id;
    u8 f3E;
} Obj2_0013FCC0;

s32 TaLogic011_SetSpecialComboQue(s32 arg0, void *arg1, void *arg2) {
    Obj1_0013FCC0 *o1 = arg1;
    Obj2_0013FCC0 *o2 = arg2;
    s32 list[8];
    s32 i;
    u8 k;

    for (i = 0; i < 5; i++) {
        o1->slot[i] = 0xFF;
    }
    TaHand_GetNextHand(arg0, list);
    if (o2 == NULL) {
        return -1;
    }
    for (i = 0; i < TaHand_GetNextHandNum(arg0); i++) {
        if (i != o1->slot[0] && i != o1->slot[1]) {
            if (o2->id == list[i]) {
                o1->slot[0] = i;
            }
        }
    }
    k = 1;
    if ((TaHand_GetCardKind(list[o1->slot[0]]) >> 5) == 0) {
        for (i = 0; i < TaHand_GetNextHandNum(arg0); i++) {
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
    return o2->f3E >> 5;
}

typedef struct Nibbles_0013FEB0 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_0013FEB0;

s32 TaLogic011_GetSummonPiece(s32 arg0, s32 arg1, void *arg2, s32 arg3) {
    extern s32 TaLogic_IsUnitWin4();
    extern s32 TaLogic_GetInvadeRoot2(s32, s32, s32, s32, s32, s32, s32, s32, u8, u16);
    extern s32 TaLogic_GetRoot2(s32, s32, s32, s32, s32, s32, u16, u8);
    s32 bestPosition;
    s32 bestScore;
    Nibbles_0013FEB0 path[12];
    s32 transformedY;
    s32 transformedX;
    s32 value;
    u8 mode;

    if (arg2 == NULL) {
        return -1;
    }
    {
    s32 initIndex;
    Nibbles_0013FEB0 *p;
    p = path;
    initIndex = 0;
    do {
        p->low = p->high = 15;
        p++;
        initIndex++;
    } while (initIndex < 12);
    }
    mode = *((u8 *)arg2 + 0x3E) >> 5;
    if (mode == 0 || mode == 3) {
        if (arg3 >= 0) {
            s32 candidate;
            s32 candidateY;
            s32 candidateX;
            s32 index;
            s32 score;
            bestScore = 255;
            bestPosition = 65535;
            value = SzDuel_GetUnitLoc(arg3 >> 8, arg3 & 255);
            index = 0;
            transformedY = value >> 8;
            transformedX = value & 255;
            do {
                candidate = Ta_GetSommonPiecePreference(arg0, index);
                if (candidate >= 0) {
                    candidateX = candidate & 255;
                    candidateY = candidate >> 8;
                    if (SzDuel_GetField(candidateX, candidateY) != 8 &&
                        (SzDuel_GetField(candidateX, candidateY) != 9 ||
                         Ta_IsVirus_Chk3(arg2, candidateX, candidateY) != 1) &&
                        SzDuel_GetMapUnit(candidateX, candidateY) == 0) {
                        if (TaLogic_IsUnitWin4((s32)arg2, arg3, TaLogic_GetWarnHideLvl_00141B30(arg0),
                                         transformedX, transformedY, 0) > 0) {
                            score = TaLogic_GetInvadeRoot2((s32)arg2, (s32)path,
                                                       candidateX, candidateY,
                                                       transformedX, transformedY,
                                                       arg3, 0, 2,
                                                       TaLogic_GetWarnHideLvl_00141B30(arg0));
                        } else {
                            score = TaLogic_GetRoot2((s32)arg2, (s32)path,
                                                       candidateX, candidateY,
                                                       transformedX, transformedY,
                                                       arg3, 2);
                        }
                        if (TaLogic_GetMinGoalCount((u8 *)path) > 0 && score < bestScore) {
                            bestScore = score;
                            bestPosition = candidate;
                        }
                    }
                }
                index++;
            } while (index < 8);
            if (bestPosition != 65535) {
                return bestPosition;
            }
            bestPosition = -1;
            return bestPosition;
        } else {
        s32 maxY;
        s32 maxX;
        s32 y;
        s32 x;
        s32 i;
        s32 bestDistance;
        s32 position;
        s32 minY;
        s32 minX;
        bestDistance = 14;
        arg3 = 0;
        i = 0;
        do {
            position = Ta_GetSommonPiecePreference(arg0, i);
            if (position >= 0) {
                x = position & 255;
                y = position >> 8;
                if (SzDuel_GetField(x, y) != 8 &&
                    (SzDuel_GetField(x, y) != 9 || Ta_IsVirus_Chk3(arg2, x, y) != 1) &&
                    SzDuel_GetMapUnitID(x, y) < 0) {
                    value = TaLogic011_GetNearMountain((s32)arg2, x, y);
                    if (y < (value >> 8)) {
                        minY = y;
                    } else {
                        minY = value >> 8;
                    }
                    if (y > (value >> 8)) {
                        maxY = y;
                    } else {
                        maxY = value >> 8;
                    }
                    if (x < (value & 255)) {
                        minX = x;
                    } else {
                        minX = value & 255;
                    }
                    if (x > (value & 255)) {
                        maxX = x;
                    } else {
                        maxX = value & 255;
                    }
                    value = (maxX - minX) + (maxY - minY);
                    if (value < bestDistance && value >= 0) {
                        arg3 = position;
                        bestDistance = value;
                    }
                }
            }
            i++;
        } while (i < 8);
        if (bestDistance < 14) {
            return arg3;
        }
        goto failure;
        }
    }
    {
    s32 y;
    s32 x;
    s32 i;
    s32 best;
    best = -1;
    i = 0;
    do {
        arg3 = Ta_GetSommonPiecePreference(arg0, i);
        if (arg3 >= 0) {
            x = arg3 & 255;
            y = arg3 >> 8;
            if (SzDuel_GetField(x, y) != 8 &&
                (SzDuel_GetField(x, y) != 9 || Ta_IsVirus_Chk3(arg2, x, y) != 1) &&
                SzDuel_GetMapUnitID(x, y) < 0 && y < 8) {
                best = arg3;
            }
        }
        i++;
    } while (i < 8);
    if (best >= 0) {
        return best;
    }
    }
failure:
    return -1;
}

typedef struct {
    u8 low : 4;
    u8 high : 4;
} Flags_001402F0;

typedef struct {
    u16 id;
    u8 action;
    u8 pad3;
    u16 position;
    u8 pad6[6];
    s32 value;
    u8 mode;
} Output_001402F0;


s32 TaLogic_GetMinimumTask_RunMission_001402F0(u16 *arg0, s32 arg1, void *arg2, u8 arg3) {
    extern s32 TaLogic_GetUnitWarning(s32, s32, s32, s32, s32, u8);
    extern s32 TaLogic_IsRunPassRoot(s32, s32, s32, s32, s32, s32, void *, u8);
    extern s32 TaLogic_IsOpenUnit_00141B90();
    s32 position;
    u8 upperX;
    u8 flag;
    Flags_001402F0 cells[12];
    s32 i;
    s32 result;
    s32 y;
    s32 score;
    s32 packedY;
    s32 originalY;
    s32 originalX;
    s32 x;
    s32 bestPosition;
    s32 bestScore;
    Output_001402F0 *out = arg2;

    position = SzDuel_GetUnitLoc(*arg0 >> 8, *arg0 & 0xFF);
    i = 0;
    do {
        cells[i].low = cells[i].high = 15;
        i++;
    } while (i < 12);

    {
        u16 value = (u16)TaLogic_GetWarnHideLvl_00141B30(arg1);
        originalX = position & 0xFF;
        originalY = position >> 8;
        if (TaLogic_GetUnitWarning(originalX, originalY, *arg0, 3, value, 0) == 0) {
            out->id = *arg0;
            out->action = 6;
            out->position = position;
            out->mode = TaLogic_IsDefStyleUnit(*arg0 >> 8, *arg0 & 0xFF, out->position, 1, 0);
            out->value = TaLogic_IsOpenUnit_00141B90(*arg0 >> 8, *arg0 & 0xFF, arg0);
            TaLogic_InitRogicControl(arg0, arg3);
            return 0;
        } else {
            result = GetMoveRev(SzDuel_GetUnit(*arg0 >> 8, *arg0 & 0xFF), originalX, originalY);
            if (result == 0) {
                out->id = *arg0;
                out->action = 6;
                out->position = position;
                out->mode = TaLogic_IsDefStyleUnit(*arg0 >> 8, *arg0 & 0xFF, out->position, 1, 0);
                out->value = TaLogic_IsOpenUnit_00141B90(*arg0 >> 8, *arg0 & 0xFF, arg0);
                TaLogic_InitRogicControl(arg0, arg3);
                return 0;
            } else {
                u8 startY;
                u8 endY;
                u8 startX;
                s32 end;
                bestPosition = 0xFF;
                bestScore = 0xFFFF;
                startX = GetCap(0, originalX - (result & 15)) & 0xFF;
                if (originalX + (result & 15) >= 7) {
                    end = 6;
                } else {
                    end = originalX + (result & 15);
                }
                upperX = end & 0xFF;
                startY = GetCap(0, originalY - (result & 15)) & 0xFF;
                end = originalY + (result & 15);
                if (end >= 7) {
                    end = 6;
                }
                endY = end & 0xFF;
                if ((*arg0 & 0xFF) == 0) {
                    flag = TaLogic_IsAttackedNow(*arg0 >> 8, *arg0 & 0xFF, 0) & 0xFF;
                } else {
                    flag = 0;
                }
                for (x = startX; x <= upperX; x++) {
                    y = startY;
                    packedY = y << 8;
                    for (; y <= endY; packedY += 0x100, y++) {
                        if ((((x < originalX ? originalX : x) -
                              (originalX < x ? originalX : x)) +
                             ((y < originalY ? originalY : y) -
                              (originalY < y ? originalY : y))) <= (result & 15)) {
                            if (TaLogic_IsRunPassRoot(*arg0 >> 8, *arg0 & 0xFF, originalX, originalY, x, y, arg0, flag) == 1 &&
                                (TaLogic_IsAttackedNow2(*arg0 >> 8, *arg0 & 0xFF, x, y, 0) == 0 || (u8)*arg0 == 0)) {
                                value = (u16)TaLogic_GetWarnHideLvl_00141B30(arg1);
                                score = TaLogic_GetUnitWarning(x, y, *arg0, 3, value, 0);
                                if (score < bestScore) {
                                    bestScore = score;
                                    bestPosition = packedY | x;
                                } else if (score == bestScore &&
                                           SzDuel_GetMapUnit(x, y) == 0 &&
                                           SzDuel_GetMapUnit(bestPosition & 0xFF, bestPosition >> 8) != 0) {
                                    bestScore = score;
                                    bestPosition = packedY | x;
                                }
                            }
                        }
                    }
                }
                if (bestPosition != 0xFF) {
                    out->id = *arg0;
                    out->action = 6;
                    out->position = bestPosition;
                    if (bestPosition == position) {
                        out->mode = TaLogic_IsDefStyleUnit(*arg0 >> 8, *arg0 & 0xFF, out->position, 1, 0);
                    } else {
                        out->mode = TaLogic_IsDefStyleUnit(*arg0 >> 8, *arg0 & 0xFF, out->position, 0, 0);
                    }
                    out->value = TaLogic_IsOpenUnit_00141B90(*arg0 >> 8, *arg0 & 0xFF, arg0);
                } else {
                    out->id = *arg0;
                    out->action = 6;
                    out->position = position;
                    out->mode = TaLogic_IsDefStyleUnit(*arg0 >> 8, *arg0 & 0xFF, out->position, 1, 0);
                    out->value = TaLogic_IsOpenUnit_00141B90(*arg0 >> 8, *arg0 & 0xFF, arg0);
                }
                TaLogic_InitRogicControl(arg0, arg3);
            }
        }
    }
    return 0;
}

typedef struct {
    u16 position;
    u8 pad2[6];
    u32 targets;
} Input_00140830;

typedef struct {
    u16 position;
    u8 action;
    u8 pad3;
    u16 destination;
    u8 pad6[6];
    s32 flag;
    u8 result;
} Output_00140830;

typedef struct {
    u8 x : 4;
    u8 y : 4;
} Point_00140830;

static inline u32 target_00140830(void *src, u8 mode) {
    Input_00140830 *input = src;
    if (mode == 1) {
        return (input->targets >> 16) & 0xFFFF;
    }
    return *(u16 *)&input->targets;
}

static inline s32 max_00140830(s32 a, s32 b) {
    return a > b ? a : b;
}


s32 TaLogic_GetMinimumTask_AtkMission_00140830(void *arg0, s32 arg1, void *arg2, u8 arg3) {
    extern s32 TaLogic_IsOpenUnit_00141B90();
    extern void TaLogic_GetInvadeRoot();
    s32 sourcePosition;
    s32 count;
    s32 sourceY;
    s32 sourceX;
    s32 flag;
    Point_00140830 points[12];
    s32 destination;
    s32 oldFlag;
    s32 i;
    s32 best;
    u32 targetX;
    u32 targetY;
    Point_00140830 *p;
    Input_00140830 *input = arg0;
    Output_00140830 *output = arg2;

    targetX = target_00140830(input, arg3);
    targetY = target_00140830(input, arg3);
    if (SzDuel_GetUnit(targetY >> 8, targetX & 0xFF) == 0) {
        TaLogic_InitRogicControl(input, 1);
        return -1;
    }
    oldFlag = TaLogic_IsOpenUnit_00141B90(input->position >> 8, input->position & 0xFF, input);
    sourcePosition = SzDuel_GetUnitLoc(input->position >> 8, input->position & 0xFF);
    targetX = target_00140830(input, arg3);
    targetY = target_00140830(input, arg3);
    destination = SzDuel_GetUnitLoc(targetY >> 8, targetX & 0xFF);
    p = points;
    i = 0;
    do {
        i++;
        p->x = p->y = 15;
        p++;
    } while (i < 12);
    {
        s32 card = SzDuel_GetUnit(input->position >> 8, input->position & 0xFF);
        sourceX = sourcePosition & 0xFF;
        sourceY = sourcePosition >> 8;
        if (GetMoveRev(card, sourceX, sourceY) == 0) {
            s32 cost;
            output->position = input->position;
            output->action = 6;
            output->destination = sourcePosition;
            cost = TaLogic_GetUnitWarning(sourceX, sourceY, arg1, 3, 1, (u8)TaLogic_GetWarnHideLvl_00141B30(arg1));
            if (cost >= SzDuel_GetUnitAP(input->position >> 8, input->position & 0xFF, 0)) {
                output->result = TaLogic_IsDefStyleUnit(input->position >> 8, input->position & 0xFF,
                                             output->destination, 1, 0);
            } else {
                output->result = TaLogic_IsDefStyleUnit(input->position >> 8, input->position & 0xFF,
                                             output->destination, 0, 0);
            }
            TaLogic_InitRogicControl(input, arg3);
            return 0;
        } else {
            s32 position = input->position;
            s32 destinationX;
            Point_00140830 *candidate;
            s32 n;
            s32 minCost;
            s32 identity;
            s32 positionY;
            s32 positionX;

            identity = (u16)TaLogic_GetWarnHideLvl_00141B30(arg1);
            positionY = position >> 8;
            positionX = position & 0xFF;
            destinationX = destination & 0xFF;

            TaLogic_GetInvadeRoot(positionY, positionX, points,
                         sourceX, sourceY, destinationX, destination >>= 8,
                         target_00140830(input, arg3), 0, 30, identity);
            count = TaLogic_GetMinGoalCount((u8 *)points);
            best = 0xFF;
            if (count > 0) {
                flag = 0;
                minCost = 0xFFFF;
                for (n = 0; n < count; n++) {
                    if (TaLogic011_IsOpenMoveUnit(input->position >> 8, input->position & 0xFF,
                                     sourceX, sourceY, destinationX, destination) == 1) {
                        best = n;
                        flag = 1;
                        points[n].x = destinationX;
                        points[n].y = destination;
                        n = count;
                    } else {
                        s32 cost;
                        candidate = &points[n];
                        cost = TaLogic_GetUnitWarning(candidate->x, candidate->y, arg1,
                                                3, 1, (u8)TaLogic_GetWarnHideLvl_00141B30(arg1));
                        if (cost < minCost) {
                            minCost = cost;
                            best = n;
                        } else if (cost == minCost) {
                            if ((max_00140830(candidate->x, destinationX) -
                                 (candidate->x < destinationX ? candidate->x : destinationX)) +
                                (max_00140830(candidate->y, destination) -
                                 (candidate->y < destination ? candidate->y : destination)) <
                                (max_00140830(points[best].x, destinationX) -
                                 (points[best].x < destinationX ? points[best].x : destinationX)) +
                                (max_00140830(points[best].y, destination) -
                                 (points[best].y < destination ? points[best].y : destination))) {
                                minCost = cost;
                                best = n;
                            }
                        }
                    }
                }
            } else {
                output->position = input->position;
                output->action = 6;
                output->destination = sourcePosition;
                output->flag = oldFlag;
                output->result = TaLogic_IsDefStyleUnit(input->position >> 8, input->position & 0xFF,
                                             output->destination, 0, 0);
                TaLogic_InitRogicControl(input, arg3);
                return 0;
            }
                if (best != 0xFF) {
                    output->position = input->position;
                    output->action = 6;
                    output->destination = (points[best].y << 8) | points[best].x;
                    output->flag = flag;
                    output->result = TaLogic_IsDefStyleUnit(input->position >> 8, input->position & 0xFF,
                                                 output->destination, 0, 0);
                } else {
                    output->position = input->position;
                    output->action = 6;
                    output->destination = sourcePosition;
                    output->flag = flag;
                    output->result = TaLogic_IsDefStyleUnit(input->position >> 8, input->position & 0xFF,
                                                 output->destination, 0, 0);
                    TaLogic_InitRogicControl(input, arg3);
                    return 0;
                }

        }
    }
    return 0;
}

typedef struct Coord_00140E10 {
    u8 x : 4;
    u8 y : 4;
} Coord_00140E10;

typedef struct Unit_00140E10 {
    u16 pos;
    u8 pad2[6];
    u32 target;
} Unit_00140E10;

typedef struct Result_00140E10 {
    u16 pos;
    s8 kind;
    u8 pad3;
    u16 target;
    u8 pad6[6];
    s32 action;
    s8 value;
} Result_00140E10;

#define selected_00140E10(unit, mode) \
    ((mode) == 1 ? (u32)(u16)(((Unit_00140E10 *)(unit))->target >> 16) \
                 : (u32)(u16)((Unit_00140E10 *)(unit))->target)

static inline u32 minY_00140E10(u32 value, void *unit, s32 mode) {
    return value < (selected_00140E10(unit, mode) >> 8) ? (u8)value : (selected_00140E10(unit, mode) >> 8);
}

static inline u32 maxY_00140E10(u32 value, void *unit, s32 mode) {
    return (selected_00140E10(unit, mode) >> 8) < value ? (u8)value : (selected_00140E10(unit, mode) >> 8);
}

static inline u32 minX_00140E10(u32 value, void *unit, s32 mode) {
    return value < (selected_00140E10(unit, mode) & 0xFF) ? (u8)value : (selected_00140E10(unit, mode) & 0xFF);
}

static inline u32 maxX_00140E10(u32 value, void *unit, s32 mode) {
    return (selected_00140E10(unit, mode) & 0xFF) < value ? (u8)value : (selected_00140E10(unit, mode) & 0xFF);
}

s32 TaLogic_GetMinimumTask_MoveMission_00140E10(void *arg0, s32 arg1, void *arg2, u8 arg3, u8 arg4) {
    s32 target;
    s32 leader;
    s32 count;
    Coord_00140E10 coords[12];
    extern s32 TaLogic_IsOpenUnit_00141B90();
    extern s32 TaLogic_GetUnitWarning();
    extern void TaLogic_GetRoot();
    extern s32 TaLogic_IsDefStyleUnit(s32, s32, s32, u8, s32);

    {
        s32 bestCost;
        s32 bestIndex;
        s32 mode;
        Coord_00140E10 *p;
        s32 i;
        target = SzDuel_GetUnitLoc(((Unit_00140E10 *)arg0)->pos >> 8, ((Unit_00140E10 *)arg0)->pos & 0xFF);
        mode = arg3;
        if (selected_00140E10(arg0, mode) == 0xFFFF &&
            target == selected_00140E10(arg0, mode)) {
            ((Result_00140E10 *)arg2)->pos = ((Unit_00140E10 *)arg0)->pos;
            ((Result_00140E10 *)arg2)->kind = 6;
            ((Result_00140E10 *)arg2)->target = target;
            ((Result_00140E10 *)arg2)->value = TaLogic_IsDefStyleUnit(
                ((Unit_00140E10 *)arg0)->pos >> 8, ((Unit_00140E10 *)arg0)->pos & 0xFF,
                ((Result_00140E10 *)arg2)->target, arg4, 0);
            ((Result_00140E10 *)arg2)->action = TaLogic_IsOpenUnit_00141B90(
                ((Unit_00140E10 *)arg0)->pos >> 8, ((Unit_00140E10 *)arg0)->pos & 0xFF, arg0);
            TaLogic_InitRogicControl(arg0, arg3);
            return 0;
        }

        p = coords;
        {
            s32 i = 0;
            Coord_00140E10 *q = p;
            do {
                q->x = q->y = 15;
                ++i;
                ++q;
            } while (i < 12);
        }

        leader = SzDuel_GetMapUnitID(selected_00140E10(arg0, mode) & 0xFF,
                             selected_00140E10(arg0, mode) >> 8);
        if (leader < 0) {
            leader = 0xFFFF;
        }
        TaLogic_GetRoot(((Unit_00140E10 *)arg0)->pos >> 8, ((Unit_00140E10 *)arg0)->pos & 0xFF,
                     coords, target & 0xFF, target >> 8,
                     selected_00140E10(arg0, mode) & 0xFF,
                     selected_00140E10(arg0, mode) >> 8, (u16)leader, 7);
        count = TaLogic_GetMinGoalCount((u8 *)coords);
        if (count > 0) {
            s32 cost;
            bestIndex = 0xFF;
            bestCost = 0xFFFF;
            for (i = 0; i < count; ++i, ++p) {
                if (SzDuel_GetMapUnit(p->x, p->y) == 0) {
                    cost = TaLogic_GetUnitWarning(p->x, p->y, arg1, 3, 1,
                                        (u8)TaLogic_GetWarnHideLvl_00141B30(arg1));
                    if (cost < bestCost) {
                        bestCost = cost;
                        bestIndex = i;
                    } else if (cost == bestCost) {
                        if ((maxX_00140E10(p->x, arg0, mode) -
                             minX_00140E10(p->x, arg0, mode)) +
                            (maxY_00140E10((u8)p->y, arg0, mode) -
                             minY_00140E10((u8)p->y, arg0, mode)) <
                            (maxX_00140E10(coords[bestIndex].x, arg0, mode) -
                             minX_00140E10(coords[bestIndex].x, arg0, mode)) +
                            (maxY_00140E10((u8)coords[bestIndex].y, arg0, mode) -
                             minY_00140E10((u8)coords[bestIndex].y, arg0, mode))) {
                            bestCost = cost;
                            bestIndex = i;
                        }
                    }
                }
            }
        } else {
            ((Result_00140E10 *)arg2)->pos = ((Unit_00140E10 *)arg0)->pos;
            ((Result_00140E10 *)arg2)->kind = 6;
            ((Result_00140E10 *)arg2)->target = target;
            ((Result_00140E10 *)arg2)->value = TaLogic_IsDefStyleUnit(
                ((Unit_00140E10 *)arg0)->pos >> 8, ((Unit_00140E10 *)arg0)->pos & 0xFF,
                ((Result_00140E10 *)arg2)->target, arg4, 0);
            ((Result_00140E10 *)arg2)->action = TaLogic_IsOpenUnit_00141B90(
                ((Unit_00140E10 *)arg0)->pos >> 8, ((Unit_00140E10 *)arg0)->pos & 0xFF, arg0);
            TaLogic_InitRogicControl(arg0, arg3);
            return 0;
        }
            if (bestIndex != 0xFF) {
                ((Result_00140E10 *)arg2)->pos = ((Unit_00140E10 *)arg0)->pos;
                ((Result_00140E10 *)arg2)->kind = 6;
                ((Result_00140E10 *)arg2)->target =
                    (coords[bestIndex].y << 8) | coords[bestIndex].x;
                ((Result_00140E10 *)arg2)->value = TaLogic_IsDefStyleUnit(
                    ((Unit_00140E10 *)arg0)->pos >> 8, ((Unit_00140E10 *)arg0)->pos & 0xFF,
                    ((Result_00140E10 *)arg2)->target, arg4, 0);
                ((Result_00140E10 *)arg2)->action = TaLogic_IsOpenUnit_00141B90(
                    ((Unit_00140E10 *)arg0)->pos >> 8, ((Unit_00140E10 *)arg0)->pos & 0xFF, arg0);
            } else {
                ((Result_00140E10 *)arg2)->pos = ((Unit_00140E10 *)arg0)->pos;
                ((Result_00140E10 *)arg2)->kind = 6;
                ((Result_00140E10 *)arg2)->target = target;
                ((Result_00140E10 *)arg2)->value = TaLogic_IsDefStyleUnit(
                    ((Unit_00140E10 *)arg0)->pos >> 8, ((Unit_00140E10 *)arg0)->pos & 0xFF,
                    ((Result_00140E10 *)arg2)->target, arg4, 0);
                ((Result_00140E10 *)arg2)->action = TaLogic_IsOpenUnit_00141B90(
                    ((Unit_00140E10 *)arg0)->pos >> 8, ((Unit_00140E10 *)arg0)->pos & 0xFF, arg0);
            }
            TaLogic_InitRogicControl(arg0, arg3);
        return 0;
    }
}

typedef struct {
    u16 position;
    u8 pad2[6];
    union {
        u32 both;
        u16 half[2];
    } target;
} Source_001415F0;

typedef struct {
    u16 position;
    u8 action;
    u8 pad3;
    u16 target;
    u8 pad6[10];
    s8 result;
} Action_001415F0;

typedef struct {
    u8 x : 4;
    u8 y : 4;
} Point_001415F0;

#define MIN_001415F0(a, b) ((a) < (b) ? (a) : (b))
#define MAX_001415F0(a, b) ((b) < (a) ? (a) : (b))


static inline u32 target_001415F0(void *arg0, s32 mode) {
    Source_001415F0 *source = arg0;
    if (mode == 1) {
        return (u16)(source->target.both >> 16);
    }
    return source->target.half[0];
}

static inline void fill_001415F0(void *arg0, void *arg2, s32 target, s32 flag) {
    Source_001415F0 *source = arg0;
    Action_001415F0 *action = arg2;
    action->position = source->position;
    action->action = 6;
    action->target = target;
    action->result = TaLogic_IsDefStyleUnit(source->position >> 8,
        source->position & 0xFF, action->target, flag, 0);
}

s32 TaLogic_GetMinimumTask_TrapMission_001415F0(void *arg0, s32 arg1, void *arg2, s32 arg3) {
    s32 start;
    s32 count;
    s32 startY;
    Point_001415F0 points[16];
    s32 bestScore;
    Point_001415F0 *p;
    s32 targetY;
    s32 targetX;
    s32 i;
    s32 bestIndex;
    s32 mode;
    s32 target;
    s32 startX;
    u32 xPosition;
    u32 yPosition;
    Source_001415F0 *source = arg0;
    Action_001415F0 *action = arg2;
    extern void TaLogic_GetInvadeRoot();

    mode = arg3 & 0xFF;
    xPosition = target_001415F0(arg0, mode);
    yPosition = target_001415F0(arg0, mode);
    if (SzDuel_GetUnit(yPosition >> 8, xPosition & 0xFF) == 0) {
        TaLogic_InitRogicControl(arg0, 1);
        return -1;
    }
    start = SzDuel_GetUnitLoc(source->position >> 8, source->position & 0xFF);
    xPosition = target_001415F0(arg0, mode);
    yPosition = target_001415F0(arg0, mode);
    target = SzDuel_GetUnitLoc(yPosition >> 8, xPosition & 0xFF);
    if (target_001415F0(arg0, mode) == 0xFFFF) {
        fill_001415F0(arg0, arg2, start, 1);
        return 0;
    } else {
        s32 unit = SzDuel_GetUnit(source->position >> 8, source->position & 0xFF);
        startX = start & 0xFF;
        startY = start >> 8;
        if (GetMoveRev(unit, startX, startY) == 0 ||
                TaLogic_IsAttackedNow(source->position >> 8, source->position & 0xFF, 0) == 1) {
            fill_001415F0(arg0, arg2, start, 1);
            return 0;
        } else {
            p = points;
            {
                s32 n = 0;
                Point_001415F0 *q = p;
                do {
                    q->x = q->y = 0xF;
                    q++;
                    n++;
                } while (n < 12);
            }
            {
                s32 position = source->position;
                u16 card = (u16)TaLogic_GetWarnHideLvl_00141B30(arg1);
                TaLogic_GetInvadeRoot(position >> 8, position & 0xFF, points,
                    startX, startY, targetX = target & 0xFF,
                    targetY = target >> 8, target_001415F0(arg0, mode),
                    0, 30, card);
            }
            count = TaLogic_GetMinGoalCount((u8 *)points);
            bestIndex = 0xFF;
            if (count > 0) {
                bestScore = 0;
                for (i = 0; i < count; i++, p++) {
                    if (SzDuel_GetMapUnit(p->x, p->y) == 0) {
                        s32 score = TaLogic_GetUnitWarning(p->x, p->y, arg1, 3, 1,
                            TaLogic_GetWarnHideLvl_00141B30(arg1) & 0xFF);
                        if (bestScore < score) {
                            bestScore = score;
                            bestIndex = i;
                        } else if (score == bestScore) {
                            if (MAX_001415F0(p->x, targetX) - MIN_001415F0(p->x, targetX)
                                    + (MAX_001415F0(p->y, targetY) - MIN_001415F0(p->y, targetY))
                                    < MAX_001415F0(points[bestIndex].x, targetX) - MIN_001415F0(points[bestIndex].x, targetX)
                                    + (MAX_001415F0(points[bestIndex].y, targetY) - MIN_001415F0(points[bestIndex].y, targetY))) {
                                bestScore = score;
                                bestIndex = i;
                            }
                        }
                    }
                }
            } else {
                fill_001415F0(arg0, arg2, start, 1);
                return 0;
            }
            if (bestIndex != 0xFF) {
                action->position = source->position;
                action->action = 6;
                action->target = (points[bestIndex].y << 8) | points[bestIndex].x;
                action->result = TaLogic_IsDefStyleUnit(source->position >> 8,
                    source->position & 0xFF, action->target, 0, 0);
            } else {
                fill_001415F0(arg0, arg2, start, 1);
                return 0;
            }
        }
    }
    return 0;
}

s32 TaLogic_GetWarnHideLvl_00141B30(s32 arg0) {
    if (SzDuel_GetLP(arg0) > 2000) {
        if (SzDuel_GetUnitMonsterCount(arg0) >= 4) {
            return 0;
        }
        return 0;
    }
    return 0;
}

s32 TaLogic_IsOpenUnit_00141B90(s32 arg0, s32 arg1) {
    s32 id;
    s32 val;
    u32 *p;

    id = SzDuel_GetUnitCardNo();
    val = Ta_IsUnitControl(arg0, arg1);
    if (SzDuel_GetUnitStatus(arg0, arg1, 4) != 0) {
        return 0;
    }
    switch (SzDuel_GetUnitKind(arg0, arg1) >> 5) {
    case 0:
        switch (id) {
        case 0x184:
            if (SzDuel_GetLP(arg0) < SzDuel_GetLP(arg0 == 0 ? 1 : 0)) {
                return 1;
            }
            break;
        case 0x170:
            if (TaLogic011_IsUseReversalGoddess(val) == 1) {
                return 1;
            }
            break;
        case 0x17F:
            if (Ta_GetUnitNumFrom22bitFlagList(SearchUnitByRange(0, 0, arg0, 1, 0x14, 0xE)) >= 3) {
                return 1;
            }
            break;
        case 0x182:
            if (TaLogic011_IsUseBindChain(val) == 1) {
                return 1;
            }
            break;
        }
        return 2;
    case 1:
        if (TaLogic_GetActionReaction(arg0, arg1, 0, 0, 6, 0) == 5) {
            return 2;
        }
        p = Ta_GetUnitEffect(arg0, arg1, 0);
        if (p == NULL) {
            return 2;
        }
        switch (*p >> 8) {
        case 0xD:
            if (SzDuel_GetLP(val) < 2000) {
                return 1;
            }
            break;
        case 0x12:
            if (Ta_GetUnitNumFrom22bitFlagList(SearchUnitByRange(0, 0, arg0, 1, 8, 0xE)) >= 4) {
                return 1;
            }
            break;
        case 0x25:
            if (TaLogic_IsAttackedNow(val, 0, 0) == 1) {
                return 1;
            }
            break;
        }
        return 2;
    }
    return 2;
}

static inline s32 max_00141E30(s32 a, s32 b) {
    if (a < b) {
        return b;
    }
    return a;
}

s32 TaLogic011_IsOpenMoveUnit(s32 arg0, s32 arg1, s32 arg2, s32 arg3,
                  s32 arg4, s32 arg5) {
    s32 min_y;
    s32 min_x;

    min_y = arg3 < arg5 ? arg3 : arg5;
    arg5 = max_00141E30(arg5, arg3);
    min_x = arg2 < arg4 ? arg2 : arg4;
    arg4 = max_00141E30(arg4, arg2);
    if ((arg4 - min_x) + (arg5 - min_y) != 2) {
        return 0;
    }
    if (SzDuel_GetUnit(arg0, arg1) == 0) {
        return 0;
    }
    if (SzDuel_GetUnitStatus(arg0, arg1, 0) == 0) {
        if (CheckLandAgreement2(SzDuel_GetField(arg2, arg3), arg0, arg1) != 1) {
            return 0;
        }
        return 1;
    }
    return 0;
}

s32 TaLogic011_IsUseBindChain(s32 arg0) {
    s32 index;
    u8 count;
    s32 list;
    s32 low;
    s32 high;
    s32 entry;

    count = 0;
    list = SearchUnitByRange(0, 0, arg0, 3, 3, 14);
    for (index = 0; index < Ta_GetUnitNumFrom22bitFlagList(list); index++) {
        entry = Ta_GetUnitOwnerIDFromLstCount(list, index);
        high = entry >> 8;
        low = entry & 0xFF;
        if (arg0 == Ta_IsUnitControl(high, low)) {
            return 0;
        }
        if (TaLogic_IsJudgeUnitDanger(high, low, 0) == 1) {
            count++;
        }
    }
    if (count > 0) {
        return 1;
    }
    return 0;
}

#pragma opt_lifetimes off

s32 TaLogic011_IsUseLifeHourGlass(s32 arg0) {
    extern s32 SzDuel_GetGraveCount(s32);
    u8 slots;
    u32 side;
    s32 i;
    u8 count;

    side = arg0;
    count = 0;
    slots = 0;
    if (SzDuel_GetLP(side) < 0x4B0) {
        return 0;
    }
    for (i = 0; i < SzDuel_GetGraveCount(side); i++) {
        if ((s32)(TaHand_GetCardAPDP(SzDuel_InqGrave(side, i)) >> 16) > 2000) {
            if ((TaHand_GetCardKind(SzDuel_InqGrave(side, i)) >> 5) == 0) {
                count++;
            }
        }
    }
    for (i = 0; i < SzDuel_GetGraveCount(side == 0 ? 1 : 0); i++) {
        if ((s32)(TaHand_GetCardAPDP(SzDuel_InqGrave(side == 0 ? 1 : 0, i)) >> 16) > 2000) {
            if ((TaHand_GetCardKind(SzDuel_InqGrave(side == 0 ? 1 : 0, i)) >> 5) == 0) {
                count++;
            }
        }
    }
    if (count >= 3) {
        for (i = 0; i < 8; i++) {
            if (Ta_GetSummonablePieceWithOrder(side, i, 1) >= 0) {
                slots++;
            }
        }
        if (slots >= 3 && 5 - SzDuel_GetUnitMonsterCount(side) >= 3) {
            return 1;
        }
    }
    return 0;
}
#pragma opt_lifetimes reset

s32 TaLogic011_IsUseBraveHourGlass(s32 arg0) {
    if (SzDuel_GetLP(arg0) < 0x4B0) {
        /* Duplicate return node #6. Try simplifying control flow for better match */
        return 0;
    }
    if (SzDuel_GetUnitMonsterCount(arg0) >= 4) {
        return 1;
    }
    return 0;
}

s32 TaLogic011_IsUseReversalGoddess(s32 arg0) {
    if (Ta_GetUnitNumFrom22bitFlagList(SearchUnitByRange(0, 0, arg0, 1, 0x3E80025, 0xE)) >= 3) {
        return 1;
    }
    return 0;
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
} Req_001422E0;

typedef struct {
    u8 pad0[0x160];
    u16 list[32];    /* 0x160 */
    u8 idx : 5;      /* 0x1A0 */
    u8 pad1A0 : 3;
    u8 pad1A1;
    u16 count;       /* 0x1A2 */
} Work_001422E0;

s32 TaLogic_GetInputQueFromMinimumTask_b(void *, void *, s32);

s32 func_001422E0(s32 arg0, void *arg1) {
    Req_001422E0 req;
    Work_001422E0 *w;
    s32 i;
    s32 ret;

    w = arg1;
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
        if (TaLogic_GetMinimumTask_0013DCA0(w, &req, arg0) == 0) {
            return 0x800;
        }
        if (TaLogic_GetInputQueFromMinimumTask_b(w, &req, arg0) < 0) {
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

#pragma conditional_move off

s32 TaLogic_GetMinimumTask_001424B0(void *work, void *arg1, s32 arg2) {
    u16 *arg0 = work;
    s32 side;
    s32 found;
    s32 result;
    s32 index;

    side = SzDuel_GetTurnOwner();
    found = 0;
    if ((result = TaLogic_GetNextActiveUnit_00142B70(arg0, side, (s32)arg1)) < 0) {
        return 0;
    }
    index = TaLogic_GetActionUnitFromOwnerID(arg0, result & 0xFFFF);
    if (index < 0) {
        return 0;
    }
    if ((result >> 16) == 1) {
        if (((arg0[index * 8 + 2] >> 8) & 0xFF) == 10) {
            TaLogic_InitRogicControl(arg0 + index * 8, 1);
        } else {
            TaLogic_InitRogicControl(arg0 + index * 8, 0);
        }
        return 1;
    }
    TaLogic_CommandUnit_001429B0(arg0 + index * 8);
    switch ((arg0[index * 8 + 2] >> 8) & 0xFF) {
    case 5:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_RunMission_00144EC0(arg0 + index * 8, side, arg1, 1);
            found = 1;
        }
        break;
    case 2:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            if (TaLogic_GetMinimumTask_AtkMission_00145400(arg0 + index * 8, side, arg1, 1) < 0) {
                TaLogic_InitRogicControl(arg0 + index * 8, 1);
                return 1;
            }
            found = 1;
        }
        break;
    case 10:
        if (TaLogic_GetMinimumTask_Summon_00143BA0(arg0[index * 8], side, (s32)arg1) < 0) {
            TaLogic_InitRogicControl(arg0 + index * 8, 1);
            *(u8 *)((u8 *)arg1 + 2) = 0xFF;
            *(s32 *)((u8 *)arg1 + 0xC) = 0;
        } else {
            TaLogic_InitRogicControl(arg0 + index * 8, 1);
            found = 1;
        }
        break;
    case 6:
    case 15:
    case 16:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_MoveMission_001459E0(arg0 + index * 8, side, arg1, 1, 0);
            found = 1;
        }
        break;
    case 3:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_MoveMission_001459E0(arg0 + index * 8, side, arg1, 1, 1);
            found = 1;
        }
        break;
    case 9:
        TaLogic_GetMinimumTask_EncMission(arg0 + index * 8, side, arg1, 1, 0, TaLogic_GetWarnHideLvl_001461C0(side), 2, 1);
        found = 1;
        break;
    case 14:
        TaLogic_GetMinimumTask_DoNone(arg0 + index * 8, side, arg1);
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
    switch (arg0[index * 8 + 2] & 0xFF) {
    case 5:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_RunMission_00144EC0(arg0 + index * 8, side, arg1, 0);
            found = 1;
        }
        break;
    case 2:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            if (TaLogic_GetMinimumTask_AtkMission_00145400(arg0 + index * 8, side, arg1, 0) < 0) {
                TaLogic_GetMinimumTask_RunMission_00144EC0(arg0 + index * 8, side, arg1, 0);
            }
            found = 1;
        }
        break;
    case 10:
        if (TaLogic_GetMinimumTask_Summon_00143BA0(arg0[index * 8], side, (s32)arg1) < 0) {
            TaLogic_InitRogicControl(arg0 + index * 8, 0);
            *(u8 *)((u8 *)arg1 + 2) = 0xFF;
            found = 1;
            *(s32 *)((u8 *)arg1 + 0xC) = 0;
        } else {
            TaLogic_InitRogicControl(arg0 + index * 8, 0);
            found = 1;
        }
        break;
    case 6:
    case 15:
    case 16:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_MoveMission_001459E0(arg0 + index * 8, side, arg1, 0, 0);
            found = 1;
        }
        break;
    case 3:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_MoveMission_001459E0(arg0 + index * 8, side, arg1, 0, 1);
            found = 1;
        }
        break;
    case 9:
        TaLogic_GetMinimumTask_EncMission(arg0 + index * 8, side, arg1, 0, 0, TaLogic_GetWarnHideLvl_001461C0(side), 2, 1);
        found = 1;
        break;
    case 14:
        TaLogic_GetMinimumTask_DoNone(arg0 + index * 8, side, arg1);
        break;
    default:
        return 0;
    }
    if (found == 1) {
        return 1;
    }
    return 0;
}
#pragma conditional_move reset

s32 TaLogic_CommandUnit_001429B0(void *arg0) {
    extern s32 SzDuel_GetUnitCardNo();
    u16 key;
    s32 temp_s1;
    s32 kind;

    key = *(u16 *)arg0;
    temp_s1 = Ta_IsUnitControl((s32)key >> 8, key & 0xFF);

    key = *(u16 *)arg0;
    if (SzDuel_GetUnit((s32)key >> 8, key & 0xFF) != 0) {
        key = *(u16 *)arg0;
        if (SzDuel_GetUnitStatus((s32)key >> 8, key & 0xFF, 0) == 0) {
            key = *(u16 *)arg0;
            if (key != 0xFFFF) {
                if ((key & 0xFF) == 0) {
                    if (*(s32 *)((u8 *)arg0 + 8) == -1) {
                        if (TaLogic_IsAttackedNow((s32)key >> 8, key & 0xFF, 0) == 1) {
                            if (SzDuel_InqHandPhase((s32)(*(u16 *)arg0) >> 8) == 1) {
                                *(u16 *)((u8 *)arg0 + 4) = 0x50A;
                            } else {
                                *(u16 *)((u8 *)arg0 + 4) = 0x5FF;
                            }
                        } else {
                            if (SzDuel_InqHandPhase((s32)(*(u16 *)arg0) >> 8) == 1) {
                                *(u16 *)((u8 *)arg0 + 4) = 0xA05;
                            } else {
                                *(u16 *)((u8 *)arg0 + 4) = 0x5FF;
                            }
                        }
                    }
                } else {
                    kind = SzDuel_GetUnitKind((s32)key >> 8, key & 0xFF) >> 5;
                    switch (kind) {
                    case 0:
                        key = *(u16 *)arg0;
                        if (SzDuel_GetUnitCardNo((s32)key >> 8, key & 0xFF) == 0x160) {
                            TaLogic012_CommandBtlUnit(arg0);
                        } else {
                            TaLogic012_CommandLineUnit(arg0);
                        }
                        break;
                    case 2:
                        TaLogic_CommandEncUnit(arg0, 2, 0, TaLogic_GetWarnHideLvl_001461C0(temp_s1) & 0xFF);
                        break;
                    default:
                        *(u16 *)((u8 *)arg0 + 4) = 0x5FF;
                        break;
                    }
                }
                return 1;
            }
        }
    }
    return 0;
}

s32 TaLogic_GetNextActiveUnit_00142B70(u16 *arg0, s32 arg1, s32 arg2) {
    s32 i;
    s32 pos;
    s32 ret;
    s32 idx;
    u16 list[22];

    for (i = 0; i < 22; i++) {
        list[i] = 0xFFFF;
    }
    TaLogic_GetUnitCtlLst(arg1, list, 0x1D, 1);
    ret = TaLogic_GetAtkUnitNow(arg1, list, arg0);
    if (ret >= 0) {
        return ret;
    }
    for (i = 0; i < 22; i++) {
        list[i] = 0xFFFF;
    }
    TaLogic_GetUnitCtlLst(arg1, list, 0x1E, 1);
    for (i = 0; i < TaLogic_GetUnitCtlLstLen(list); i++) {
        if ((SzDuel_GetUnitKind(list[i] >> 8, list[i] & 0xFF) >> 5) == 3 &&
            TaLogic_IsUnitReadyMove(list[i]) == 1 && TaLogic_IsPickUp(list[i]) == 1) {
            return list[i];
        }
    }
    pos = arg1 << 8;
    idx = TaLogic_GetActionUnitFromOwnerID(arg0, pos);
    TaLogic_CommandUnit_001429B0(arg0 + idx * 8);
    if (((arg0[idx * 8 + 2] >> 8) & 0xFF) == 10) {
        if (SzDuel_InqHandPhase(arg1) == 1 && TaLogic_GetMinimumTask_Summon_00143BA0(pos, arg1, arg2) >= 0) {
            return pos | 0x10000;
        }
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_GetUnitStatus(arg1, 0, 0) == 0) {
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_InqHandPhase(arg1) == 1 && TaLogic_GetMinimumTask_Summon_00143BA0(pos, arg1, arg2) >= 0) {
        return pos | 0x10000;
    }
    for (i = 0; i < 22; i++) {
        list[i] = 0xFFFF;
    }
    TaLogic_GetUnitCtlLst(arg1, list, 0x1F, 1);
    for (i = 0; i < TaLogic_GetUnitCtlLstLen(list); i++) {
        if (TaLogic_IsUnitReadyMove(list[i]) == 1 && TaLogic_IsPickUp(list[i]) == 1) {
            return list[i];
        }
    }
    for (i = 0; i < 22; i++) {
        list[i] = 0xFFFF;
    }
    TaLogic_GetUnitCtlLst(arg1, list, 0x1F, 1);
    for (i = 0; i < TaLogic_GetUnitCtlLstLen(list); i++) {
        if (SzDuel_GetUnitStatus(list[i] >> 8, list[i] & 0xFF, 0) == 0 && TaLogic_IsPickUp(list[i]) == 1) {
            return list[i];
        }
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/main_010", TaLogic012_CommandLineUnit);

typedef struct {
    u16 card;
    u8 flag;
    u8 pad3;
} Slot_00143540;

typedef struct {
    u16 low;
    u16 high;
} DataHalves_00143540;

typedef struct {
    u16 coordinates;
    u8 pad2[2];
    u16 state;
    u8 pad6[2];
    union {
        u32 word;
        DataHalves_00143540 halves;
    } data;
} Entry_00143540;

void TaLogic012_CommandBtlUnit(void *arg0) {
    extern s32 TaLogic_IsRootOpen();
    extern void TaLogic_InitIgnoreLst();
    extern s32 TaLogic012_GetNearUnit();
    Entry_00143540 *entry = arg0;
    s32 side;
    s32 player;
    s32 pos;
    s32 other;
    s32 otherPos;
    s32 i;
    u8 work[0x70];
    Slot_00143540 list[22];
    s16 countA;
    s16 countB;

    if (SzDuel_GetUnit(entry->coordinates >> 8, entry->coordinates & 0xFF) != 0) {
        side = Ta_GetCurrentSide(entry->coordinates >> 8, entry->coordinates & 0xFF);
        other = (side == 0 ? 1 : 0) << 8;
        pos = SzDuel_GetUnitLoc(entry->coordinates >> 8, entry->coordinates & 0xFF);
        otherPos = SzDuel_GetUnitLoc(other >> 8, other & 0xFF);
        player = SzDuel_GetUnit(entry->coordinates >> 8, entry->coordinates & 0xFF);
        TaLogic_InitIgnoreLst(work);
        for (i = 0; i < 22; i++) {
            list[i].card = 0xFFFF;
            list[i].flag = 0xFF;
        }
        if (TaLogic_IsRootOpen(entry->coordinates >> 8, entry->coordinates & 0xFF, pos & 0xFF, pos >> 8,
                          other >> 8, other & 0xFF, otherPos & 0xFF, otherPos >> 8, 2) > 0) {
            entry->state = 0x2FF;
            entry->data.word = (other << 16) | entry->data.halves.low;
            return;
        }
        countB = 0;
        countA = 0;
        i = 1;
        while (1) {
            switch (TaLogic012_GetNearUnit(entry, 0, player, pos & 0xFF, pos >> 8,
                                  Ta_GetCurrentSide(entry->coordinates >> 8, entry->coordinates & 0xFF) == 0 ? 1 : 0,
                                  (u8)i, TaLogic_GetWarnHideLvl_001461C0(side), list, 0,
                                  &countA, &countB, 5, work)) {
            case 3:
                entry->state = 0x6FF;
                entry->data.word = (pos << 16) | entry->data.halves.low;
                break;
            case 2:
                entry->state = 0x3FF;
                entry->data.word = (pos << 16) | entry->data.halves.low;
                return;
            case 1:
                return;
            case 0:
                entry->state = 0x5FF;
                return;
            default:
                break;
            }
            i++;
            if (i > 5) {
                break;
            }
        }
        *(u16 *)((u8 *)arg0 + 4) = 0x5FF;
    }
}

void TaLogic012_GetNearUnit(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28) {
    TaLogic_GetNearUnit(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
                  arg_sp0, arg_sp8, arg_sp10, arg_sp18, arg_sp20,
                  0, 0x708, arg_sp28);
}

s32 TaLogic012_GetLineUnitLst(s16 *output, s32 arg1, s32 arg2, s32 flags) {
    s32 i;
    u8 count;
    s32 entry;
    s32 include_same;
    s32 include_other;

    count = 0;
    i = 0;
    include_same = flags & 1;
    include_other = (flags >> 1) & 1;
    do {
        if ((entry = SzDuel_GetMapUnitID(i, arg1)) >= 0) {
            if (include_same == 1) {
                if (arg2 == Ta_IsUnitControl(entry >> 8, entry & 0xFF)) {
                    output[count] = entry;
                    count++;
                }
            }
            if (include_other == 1) {
                if (arg2 != Ta_IsUnitControl(entry >> 8, entry & 0xFF)) {
                    output[count] = entry;
                    count++;
                }
            }
        }
        i++;
    } while (i < 7);
    return count;
}

s32 TaLogic012_GetAgreeLineZ(void *arg0) {
    s32 i;

    for (i = 1; i <= 5; i++) {
        if (CheckLandAgreement(SzDuel_GetField(0, i), arg0) == 1) {
            return i;
        }
    }
    return -1;
}

static inline u8 TaLogic012_CountLine_00143970(s32 line, s32 key) {
    s32 i;
    u8 count;
    s32 card;

    count = 0;
    i = 0;
    do {
        card = SzDuel_GetMapUnitID(i, line);
        if (card >= 0) {
            if (key == Ta_IsUnitControl(card >> 8, card & 0xFF)) {
                count++;
            }
        }
        i++;
    } while (i < 7);
    return count;
}

s32 TaLogic012_GetEmptyLine(void *arg0) {
    s32 row;
    s32 delay;
    s32 category;
    s32 n;

    category = Ta_IsUnitControl2(arg0);
    row = 0;
    do {
        delay = 0;
        do {
            delay++;
        } while (delay < 7);
        if ((n = TaLogic012_CountLine_00143970(row, category)) == 0) {
            if (CheckLandAgreement(SzDuel_GetField(0, row), arg0) == 1) {
                return row;
            }
        }
        row++;
    } while (row < 7);
    return -1;
}

s32 TaLogic012_IsLineEmpty(s32 arg0, s32 arg1) {
    u8 data[0x60];
    u8 flags;
    s32 key;
    u8 count;
    s32 i;
    s32 value;
    s32 delay;

    flags = TaHand_GetCardKind(arg0);
    SzDuel_InitCardInfo(data, arg0);
    if (((s32) flags >> 5) != 0) {
        return 0;
    }
    key = SzDuel_GetTurnOwner();
    delay = 0;
    do {
        delay++;
    } while (delay < 7);
    count = 0;
    i = 0;
    do {
        value = SzDuel_GetMapUnitID(i, arg1);
        if ((value >= 0) && (key == Ta_IsUnitControl(value >> 8, value & 0xFF))) {
            count++;
        }
        i++;
    } while (i < 7);
    if (count == 0) {
        if (CheckLandAgreement(SzDuel_GetField(0, arg1), data) == 1) {
            return 1;
        }
    }
    return 0;
}

s32 TaLogic_GetMinimumTask_Summon_00143BA0(s32 arg0, s32 arg1, s32 arg2) {
    extern s32 TaLogic_GetUnitNum();
    struct Data_00143BA0 {
        u8 bytes[0x3C];
        u16 value;
        u8 pad[0x22];
    } data;
    s32 coordinate;
    s32 status;
    s32 value;

    *(s16 *)arg2 = (s16)arg0;
    coordinate = arg0;
    if (SzDuel_InqHandPhase(arg1) == 0) {
        return -1;
    }
    if (TaLogic_GetUnitNum(arg1, 0) == 5 && TaLogic_GetUnitNum(arg1, 1) == 5) {
        return -1;
    }
    status = TaLogic012_IsHandPlay(arg1, &data);
    if (status < 0) {
        return -1;
    }
    *(u8 *)((u8 *)arg2 + 2) = 10;
    *(s32 *)((u8 *)arg2 + 0xC) = 0;
    coordinate = SzDuel_GetUnitLoc(coordinate >> 8, coordinate & 0xFF);
    value = TaLogic_GetWarnHideLvl_001461C0(arg1);
    coordinate = TaLogic_GetNearCard2(&data, coordinate & 0xFF, coordinate >> 8,
                                (arg1 == 0 ? 1 : 0), 3, 0x1F, 2, 2, 0,
                                value);
    if (status == 0) {
        if (TaLogic012_SetComboQue(arg1, (u8 *)arg2, &data) < 0) {
            goto fallback;
        }
        if (coordinate < 0) {
            if (SzDuel_GetUnitMonsterCount(arg1) >= 4) {
                goto fallback;
            }
            coordinate = TaLogic012_GetSummonPiece(arg1, 0, &data, coordinate);
            if (coordinate < 0) {
                return -1;
            }
            *(s16 *)((u8 *)arg2 + 4) = (s16)coordinate;
            return 1;
        }
        coordinate = TaLogic012_GetSummonPiece(arg1, 0, &data, coordinate);
        if (coordinate < 0) {
            return -1;
        }
        *(s16 *)((u8 *)arg2 + 4) = (s16)coordinate;
        return 1;
    }
    if (status == 2) {
        TaLogic012_SetSpecialComboQue(arg1, (void *)arg2, &data);
        coordinate = TaLogic012_GetSummonPiece(arg1, status & 0xFF, &data, coordinate);
        if (coordinate < 0) {
            return -1;
        }
        *(s16 *)((u8 *)arg2 + 4) = (s16)coordinate;
        return 1;
    }
fallback:
    coordinate = TaLogic012_GetSpellPlay(arg1, (u8 *)arg2, &data, data.value);
    if (coordinate < 0) {
        return -1;
    }
    coordinate = TaLogic012_GetSummonPiece(arg1, coordinate & 0xFF, &data, -1);
    if (coordinate < 0) {
        return -1;
    }
    *(s16 *)((u8 *)arg2 + 4) = (s16)coordinate;
    return 1;
}

s32 TaLogic012_IsHandPlay(s32 arg0, void *arg1) {
    s32 cards[8];
    u8 scratch[32];
    s32 *fallback;
    s32 result;
    s32 score;
    s32 firstIndex;
    s32 *first;
    s32 level;
    s32 selected;
    s32 fallbackIndex;
    s32 best;
    u8 firstType;
    s32 *entry;
    s32 index;
    u8 secondType;
    extern s32 TaLogic_GetUnitNum();

    firstType = TaLogic_GetUnitNum(arg0, 0);
    secondType = TaLogic_GetUnitNum(arg0, 1);
    best = -1;
    if (arg1 == NULL) {
        return -1;
    }
    TaHand_GetNextHand(arg0, cards);
    if (firstType == 5) {
        if (TaLogic012_GetSpellPlay(arg0, scratch, arg1, 999) >= 0) {
            return 1;
        } else {
            return -1;
        }
    }
    if (secondType == 5) {
        firstIndex = 0;
        if (firstIndex < TaHand_GetNextHandNum(arg0)) {
            first = cards;
            do {
                if ((TaHand_GetCardKind(*first) >> 5) == 0 &&
                    TaHand_IsCardSummon2(arg0, *first) == 1) {
                    SzDuel_InitCardInfo(arg1, cards[firstIndex]);
                    return 0;
                }
                first++;
                firstIndex++;
            } while (firstIndex < TaHand_GetNextHandNum(arg0));
        }
        return -1;
    }
    if (TaLogic012_GetSpecCardPlay(arg0, cards, arg1, scratch, 0x34E) >= 0) {
        if (TaLogic012_IsDoCerem(arg0, 0x34E) == 1) {
            return 2;
        }
    }
    if (TaLogic012_IsPinch(arg0) == 1) {
        if (TaLogic012_GetSpecCardPlay(arg0, cards, arg1, scratch, 0x2DB) >= 0) {
            return 2;
        }
        if (TaLogic012_GetSpecCardPlay(arg0, cards, arg1, scratch, 0x2EF) >= 0) {
            return 2;
        }
    }
    index = 0;
    if (index < TaHand_GetNextHandNum(arg0)) {
        entry = cards;
        do {
            level = 1;
            while (1) {
                if (TaLogic012_IsLineEmpty(*entry, level) == 1 &&
                    TaLogic012_GetSpecCardPlay(arg0, cards, arg1, scratch, *(u16 *)entry) >= 0) {
                    score = SzDuel_GetUnitAP2(arg1, 0);
                    if (best < score) {
                        selected = *entry;
                        best = score;
                    }
                }
                level++;
                if (level > 5) {
                    break;
                }
            }
            entry++;
            index++;
        } while (index < TaHand_GetNextHandNum(arg0));
    }
    if (best >= 0) {
        SzDuel_InitCardInfo(arg1, selected);
        return 2;
    }
    fallbackIndex = 0;
    if (fallbackIndex < TaHand_GetNextHandNum(arg0)) {
        fallback = cards;
        do {
            if ((TaHand_GetCardKind(*fallback) >> 5) == 0 &&
                TaHand_IsCardSummon2(arg0, *fallback) == 1) {
                return 0;
            }
            fallback++;
            fallbackIndex++;
        } while (fallbackIndex < TaHand_GetNextHandNum(arg0));
    }
    result = TaLogic012_GetSpellPlay(arg0, scratch, arg1, 999);
    if (result >= 0) {
        return result;
    }
    return -1;
}

s32 TaLogic012_GetSpecCardPlay(s32 arg0, s32 *arg1, void *arg2, void *arg3, s32 arg4) {
    s32 index;
    s32 *entry;
    s32 key;
    s32 *selected;

    index = 0;
    if (index < TaHand_GetNextHandNum(arg0)) {
        key = (u16)arg4;
        entry = arg1;
        do {
            if (TaHand_IsCardSummon2(arg0, *entry) == 1) {
                if (key == *entry && TaHand_IsCardSummon2(arg0, *entry) == 1) {
                    *((s8 *)arg3 + 6) = index;
                    selected = &arg1[index];
                    SzDuel_InitCardInfo(arg2, *selected);
                    return TaHand_GetCardKind(*selected) >> 5;
                }
            }
            ++entry;
            ++index;
        } while (index < TaHand_GetNextHandNum(arg0));
    }
    return -1;
}

s32 TaLogic012_GetSpellPlay(s32 arg0, u8 *arg1, void *arg2, s32 arg3) {
    s32 buf[8];
    s32 i;

    TaHand_GetNextHand(arg0, buf);
    if (arg2 == NULL) {
        return -1;
    }
    for (i = 0; i < 5; i++) {
        arg1[i + 6] = 0xFF;
    }
    for (i = 0; i < TaHand_GetNextHandNum(arg0); i++) {
        if (arg3 == buf[i] && arg3 != 999) {
            arg1[6] = i;
            SzDuel_InitCardInfo(arg2, buf[i]);
            return 1;
        }
    }
    for (i = 0; i < TaHand_GetNextHandNum(arg0); i++) {
        if ((TaHand_GetCardKind(buf[i]) >> 5) != 0 && (TaHand_GetCardKind(buf[i]) >> 5) != 2) {
            arg1[6] = i;
            SzDuel_InitCardInfo(arg2, buf[i]);
            return 1;
        }
    }
    for (i = 0; i < TaHand_GetNextHandNum(arg0); i++) {
        if ((TaHand_GetCardKind(buf[i]) >> 5) != 0) {
            arg1[6] = i;
            SzDuel_InitCardInfo(arg2, buf[i]);
            return 1;
        }
    }
    return -1;
}

typedef struct Info_00144450 {
    u8 pad00[8];
    u16 x;
    s16 y;
} Info_00144450;

typedef struct Sprite_00144450 {
    Info_00144450 *info;
    u8 pad04[0x34];
    s16 x;
    s16 y;
} Sprite_00144450;


s32 TaLogic012_SetComboQue(s32 arg0, u8 *arg1, void *arg2) {
    u16 *nodes[8];
    s32 entries[7];
    s16 a;
    s16 b;
    s32 i;
    s32 card;
    s32 value;
    s32 best;

    if (arg2 == NULL) {
        return -1;
    } else {
        s32 top;
        s32 *entry;
        u16 **node;

        TaHand_GetNextHand(arg0, entries);
        best = -1;
        top = -1;
        i = 0;
        if (i < TaHand_GetNextHandNum(arg0)) {
            entry = entries;
            node = nodes;
            do {
                b = 0;
                a = 0;
                card = *entry;
                *node = NULL;
                if ((TaHand_GetCardKind(card) >> 5) == 0) {
                    *node = TaLogic_GetFusionTree(arg0, (struct TreeTag *)*node, i & 0xFF, card & 0xFFFF, 0, (u16 *)&a, (u16 *)&b);
                    *node = TaLogic_GetFusionRes(*node);
                    value = TaLogic_GetEnchantQue(arg0, *node, 0, 0);
                    if (TaHand_IsCardSummon2(arg0, card) == 1) {
                        if (best < value) {
                            TaLogic_ConvEmptyCombo_00144630(arg0, *node, entries);
                            TaLogic_CopyArray((u8 *)*node + 2, arg1 + 6);
                            SzDuel_InitCardInfo(arg2, **node);
                            ((Sprite_00144450 *)arg2)->x = (value >> 16) - (((Sprite_00144450 *)arg2)->info->x & 0x1FFF);
                            ((Sprite_00144450 *)arg2)->y = (value & 0xFFFF) - (((Sprite_00144450 *)arg2)->info->y & 0x1FFF);
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
            } while (i < TaHand_GetNextHandNum(arg0));
        }
        return top;
    }
}

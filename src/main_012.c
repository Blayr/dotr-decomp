#include "common.h"

s32 TaLogic_GetNextActiveUnit_0014BFD0(u16 *arg0, s32 arg1, s32 arg2) {
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
    TaLogic_CommandUnit_0014BDE0(arg0 + idx * 8);
    if (((arg0[idx * 8 + 2] >> 8) & 0xFF) == 10) {
        if (SzDuel_InqHandPhase(arg1) == 1 && TaLogic_GetMinimumTask_Summon_0014CBA0(pos, arg1, arg2) >= 0) {
            return pos | 0x10000;
        }
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_GetUnitStatus(arg1, 0, 0) == 0) {
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_InqHandPhase(arg1) == 1 && TaLogic_GetMinimumTask_Summon_0014CBA0(pos, arg1, arg2) >= 0) {
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
    u16 card;
    u8 flag;
    u8 pad3;
} Slot_0014C3B0;

typedef struct {
    u16 low;
    u16 high;
} DataHalves_0014C3B0;

typedef struct {
    u16 coordinates;
    u8 pad2[2];
    u16 state;
    u8 pad6[2];
    union {
        u32 word;
        DataHalves_0014C3B0 halves;
    } data;
} Entry_0014C3B0;


void TaLogic014_CommandBtlUnit(void *arg0) {
    extern s32 TaLogic_IsRootOpen();
    extern void TaLogic_InitIgnoreLst();
    extern s32 TaLogic014_GetNearUnit();
    Entry_0014C3B0 *entry = arg0;
    s32 side;
    s32 player;
    s32 pos;
    s32 other;
    s32 otherPos;
    s32 i;
    s32 result;
    u8 work[0x70];
    Slot_0014C3B0 list[22];
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
                          other >> 8, other & 0xFF, otherPos & 0xFF, otherPos >> 8, 3) > 0) {
            entry->state = 0x2FF;
            entry->data.word = (other << 16) | entry->data.halves.low;
            return;
        }
        countB = 0;
        countA = 0;
        i = 1;
        while (1) {
            switch (TaLogic014_GetNearUnit(entry, 0, player, pos & 0xFF, pos >> 8,
                                  Ta_GetCurrentSide(entry->coordinates >> 8, entry->coordinates & 0xFF) == 0 ? 1 : 0,
                                  (u8)i, TaLogic_GetWarnHideLvl_0014F9B0(side), list, 0,
                                  &countA, &countB, 3, work)) {
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
                entry->state = 0x3FF;
                entry->data.word = (pos << 16) | entry->data.halves.low;
                return;
            }
            i++;
            if (i > 3) {
                break;
            }
        }
        if (TaLogic014_IsLinePoint(pos & 0xFF, pos >> 8) == 1) {
            if (TaLogic014_IsActiveMode() == 1) {
                entry->state = 0x2FF;
                entry->data.word = (other << 16) | entry->data.halves.low;
            } else {
                entry->state = 0x6FF;
                entry->data.word = (pos << 16) | entry->data.halves.low;
            }
            return;
        }
        result = TaLogic014_GetEmptyLine();
        if (result >= 0) {
            entry->state = 0x6FF;
            entry->data.word = (result << 16) | entry->data.halves.low;
        } else {
            entry->state = 0x2FF;
            entry->data.word = (other << 16) | entry->data.halves.low;
        }
    }
}

void TaLogic014_GetNearUnit(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28) {
    TaLogic_GetNearUnit(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
        arg_sp0, arg_sp8, arg_sp10, arg_sp18, arg_sp20, 0, 2500, arg_sp28);
}

void TaLogic014_CommandEfcMonster(void *arg0) {
    extern s32 SzDuel_GetUnitCardNo();
    Entry_0014C3B0 *entry = arg0;
    s32 slot;
    s32 kind;

    slot = Ta_IsUnitControl(entry->coordinates >> 8, entry->coordinates & 0xFF);
    kind = SzDuel_GetUnitCardNo(entry->coordinates >> 8, entry->coordinates & 0xFF);
    switch (kind) {
    case 0x264:
    case 0x227:
        if (TaLogic014_IsUnitNaturalEffectUse(slot, kind) == 1) {
            entry->state = 0x3FF;
            entry->data.word = (SzDuel_GetUnitLoc(entry->coordinates >> 8, entry->coordinates & 0xFF) << 16) | entry->data.halves.low;
            return;
        }
        break;
    case 0x23A:
        if (TaLogic014_IsActiveMode() == 1 && TaLogic_CommandGunnerUnit(entry, 0) == 1) {
            return;
        }
        break;
    case 0x23F:
        if (TaLogic014_IsActiveMode() == 1 && SzDuel_GetUnitStatus(entry->coordinates >> 8, entry->coordinates & 0xFF, 4) == 0 && TaLogic_CommandGunnerUnit(entry, 0) == 1) {
            return;
        }
        break;
    }
    TaLogic014_CommandBtlUnit(entry);
}

typedef struct Entry_0014C870 {
    u16 position;
    u16 unk2;
    u16 state;
    u16 unk6;
    u32 data;
} Entry_0014C870;

s32 TaLogic_GetLandChange(s32, s32, s32, s32, s32, s32);

void TaLogic014_CommandSpellUnit(void *arg0) {
    Entry_0014C870 *entry = arg0;
    u32 *card;
    s32 position;
    s32 result;

    Ta_IsUnitControl((s32)entry->position >> 8, entry->position & 0xFF);
    card = Ta_GetUnitEffect((s32)entry->position >> 8, entry->position & 0xFF, 0);
    position = SzDuel_GetUnitLoc((s32)entry->position >> 8, entry->position & 0xFF);
    if (card == NULL) {
        entry->state = 0x5FF;
    } else {
        switch (*card >> 8) {
        case 2:
            if (TaLogic014_IsActiveMode() == 1) {
                result = TaLogic_GetLandChange(SzDuel_GetUnit((s32)entry->position >> 8, entry->position & 0xFF),
                                      position & 0xFF, position >> 8, 4, 9, 2);
                if (result >= 0) {
                    entry->state = 0x6FF;
                    entry->data = (result << 16) | (entry->data & 0xFFFF);
                }
            }
            break;
        }
        entry->state = 0x5FF;
    }
}

s32 TaLogic014_IsLinePoint(s32 arg0, s32 arg1) {
    s32 var_s0;

    var_s0 = 0;
loop_1:
    if (((arg1 << 8) | arg0) == TaLogic014_GetLine(var_s0)) {
        return 1;
    }
    var_s0 += 1;
    if (var_s0 >= 3) {
        return 0;
    }
    goto loop_1;
}

s32 TaLogic014_GetLine(s32 arg0) {
    s32 TaLogic_GetSommonPiecePreference_0014DA30(s32, s32);
    s32 id;

    id = SzDuel_GetTurnOwner();
    switch (arg0) {
    case 0:
        return TaLogic_GetSommonPiecePreference_0014DA30(id, 0);
    case 1:
        return TaLogic_GetSommonPiecePreference_0014DA30(id, 3);
    case 2:
        return TaLogic_GetSommonPiecePreference_0014DA30(id, 4);
    default:
        return -1;
    }
}

static inline s32 slot_0014CA60(s32 index) {
    s32 TaLogic_GetSommonPiecePreference_0014DA30(s32, s32);
    s32 id;

    id = SzDuel_GetTurnOwner();
    switch (index) {
    case 0:
        return TaLogic_GetSommonPiecePreference_0014DA30(id, 0);
    case 1:
        return TaLogic_GetSommonPiecePreference_0014DA30(id, 3);
    case 2:
        return TaLogic_GetSommonPiecePreference_0014DA30(id, 4);
    default:
        return -1;
    }
}

s32 TaLogic014_GetEmptyLine(void) {
    s32 index;
    s32 position;

    index = 0;
    do {
        position = slot_0014CA60(index);
        if (((SzDuel_GetMapUnit(position & 0xFF, position >> 8) == 0) ? 1 : 0) == 1) {
            return slot_0014CA60(index);
        }
        index++;
    } while (index < 3);
    return -1;
}

typedef struct {
    s16 id;
    u8 unk2;
    u8 pad3;
    s16 unk4;
    u8 pad6[6];
    s32 unkC;
} Ctx_0014CBA0;

typedef struct {
    u8 pad0[0x3C];
    u16 unk3C;
    u8 pad3E[0x22];
} Work_0014CBA0;

s32 TaLogic_GetNearCard2(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8,
                  s32 arg9);

s32 TaLogic_GetMinimumTask_Summon_0014CBA0(s32 arg0, s32 arg1, s32 arg2) {
    s32 ret;
    s32 kind;
    Ctx_0014CBA0 *ctx = (Ctx_0014CBA0 *)arg2;
    Work_0014CBA0 work;
    s32 res;
    extern s32 TaLogic_GetUnitNum();

    ctx->id = arg0;
    if (SzDuel_InqHandPhase(arg1) == 0) {
        return -1;
    }
    if (TaLogic_GetUnitNum(arg1, 0) == 5 && TaLogic_GetUnitNum(arg1, 1) == 5) {
        return -1;
    }
    kind = TaLogic014_IsHandPlay(arg1, &work);
    if (kind < 0) {
        return -1;
    }
    ctx->unk2 = 10;
    ctx->unkC = 2;
    arg0 = SzDuel_GetUnitLoc(arg0 >> 8, arg0 & 0xFF);
    if (kind == 0) {
        if (TaLogic014_SetComboQue(arg1, (u8 *)ctx, &work) >= 0) {
            ret = TaLogic_GetNearCard2(&work, arg0 & 0xFF, arg0 >> 8, arg1 == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, TaLogic_GetWarnHideLvl_0014F9B0(arg1));
            if (ret < 0) {
                if (SzDuel_GetUnitMonsterCount(arg1) < 6) {
                    res = TaLogic014_GetSummonPiece(arg1, kind, &work, ret);
                    if (res < 0) {
                        return -1;
                    }
                    ctx->unk4 = res;
                    return 1;
                }
            } else {
                res = TaLogic014_GetSummonPiece(arg1, kind, &work, ret);
                if (res < 0) {
                    return -1;
                }
                ctx->unk4 = res;
                return 1;
            }
        }
    } else {
        ret = TaLogic_GetNearCard2(&work, arg0 & 0xFF, arg0 >> 8, arg1 == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, TaLogic_GetWarnHideLvl_0014F9B0(arg1));
    }
    if (kind == 2) {
        TaLogic014_SetSpecialComboQue(arg1, ctx, &work);
        res = TaLogic014_GetSummonPiece(arg1, kind, &work, ret);
        if (res < 0) {
            return -1;
        }
        ctx->unk4 = res;
        return 1;
    }
    if (TaLogic014_GetSpellPlay(arg1, (u8 *)ctx, &work, work.unk3C) < 0) {
        return -1;
    }
    res = TaLogic014_GetSummonPiece(arg1, kind, &work, ret);
    if (res < 0) {
        return -1;
    }
    ctx->unk4 = res;
    return 1;
}

s32 TaLogic014_IsHandPlay(s32 arg0, void *arg1) {
    extern s32 TaLogic_GetUnitNum();
    extern s32 SzView_SetCamera();
    s32 ids[8];
    s32 data[8];
    u8 type = (u8)TaLogic_GetUnitNum(arg0, 0);
    u8 attr = (u8)TaLogic_GetUnitNum(arg0, 1);

    if (arg1 == NULL) {
        return -1;
    }
    TaHand_GetNextHand(arg0, ids);
    if (type == 5) {
        s32 result = TaLogic014_GetSpellPlay(arg0, (u8 *)data, arg1, 0x3E7);
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
    if (TaLogic014_GetSpecCardPlay(arg0, (u8 *)data, arg1, 0x354) >= 0) {
        if (TaLogic014_IsDoCerem(arg0, 0x354) == 1) {
            return 2;
        }
    }
    if (TaLogic014_IsActiveMode() == 1) {
        if (SzDuel_GetUnitSpellCount(arg0) == 0) {
            if (TaLogic014_GetSpecCardPlay(arg0, (u8 *)data, arg1, 0x2BD) >= 0) {
                return 2;
            }
        }
    }
    if (SzDuel_GetUnitMonsterCount(arg0) >= 4) {
        if (TaLogic014_GetSpecCardPlay(arg0, (u8 *)data, arg1, 0x2E6) >= 0) {
            return 2;
        }
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
                    SzDuel_InitCardInfo(arg1, ids[i]);
                    return 0;
                }
                p++;
                i++;
                count = TaHand_GetNextHandNum(arg0);
            } while (i < count);
        }
    }
    {
        s32 result = TaLogic014_GetSpellPlay(arg0, (u8 *)data, arg1, 0x3E7);
        if (result >= 0) {
            return result;
        }
        return -1;
    }
}

s32 TaLogic014_GetSpecCardPlay(s32 arg0, void *arg1, void *arg2, s32 arg3) {
    s32 entries[8];
    s32 i;
    s32 *p;
    s32 key;

    TaHand_GetNextHand(arg0, entries);
    i = 0;
    if (0 < TaHand_GetNextHandNum(arg0)) {
        key = arg3 & 0xFFFF;
        p = entries;
        do {
            if (key == *p && TaHand_IsCardSummon2(arg0, *p) == 1) {
                ((s8 *)arg1)[6] = i;
                SzDuel_InitCardInfo(arg2, entries[i]);
                return TaHand_GetCardKind(entries[i]) >> 5;
            }
            p++;
            i++;
        } while (i < TaHand_GetNextHandNum(arg0));
    }
    return -1;
}

s32 TaLogic014_GetSpellPlay(s32 arg0, u8 *arg1, void *arg2, s32 arg3) {
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

typedef struct Info_0014D3E0 {
    u8 pad00[8];
    u16 x;
    s16 y;
} Info_0014D3E0;

typedef struct Sprite_0014D3E0 {
    Info_0014D3E0 *info;
    u8 pad04[0x34];
    s16 x;
    s16 y;
} Sprite_0014D3E0;


s32 TaLogic014_SetComboQue(s32 arg0, u8 *arg1, void *arg2) {
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
                            TaLogic_ConvEmptyCombo_0014D5C0(arg0, *node, entries);
                            TaLogic_CopyArray((u8 *)*node + 2, arg1 + 6);
                            SzDuel_InitCardInfo(arg2, **node);
                            ((Sprite_0014D3E0 *)arg2)->x = (value >> 16) - (((Sprite_0014D3E0 *)arg2)->info->x & 0x1FFF);
                            ((Sprite_0014D3E0 *)arg2)->y = (value & 0xFFFF) - (((Sprite_0014D3E0 *)arg2)->info->y & 0x1FFF);
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

typedef struct {
    u16 id;
    u8 values[5];
} Info_0014D5C0;

void TaLogic_ConvEmptyCombo_0014D5C0(s32 arg0, void *arg1, s32 *arg2) {
    Info_0014D5C0 *info = arg1;
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
                if (card != 0x3E7 && TaLogic014_IsRefuseEmptyCombo(card) == 0 && level >= TaHand_GetCardSummonCost2(card, arg0)) {
                    cost = TaHand_GetCardAPDP(card);
                    if ((cost & 0xFFFF) + (cost >> 16) * 2 < 0x1069 && TaHand_IsCardEffect(card) == 2 &&
                        (u16)TaLogic_GetHandFusion(info->id, (u16)card) == 0x3E7) {
                        TaLogic_AddEmptyCombo(info->values, buf[i]);
                    }
                }
            }
        }
    }
}

s32 TaLogic014_IsRefuseEmptyCombo(s32 arg0) {
    if (TaHand_GetCardKind(arg0) >> 5) {
        return 1;
    }
    if (TaHand_IsCardEffect(arg0) == 1) {
        return 1;
    }
    return 0;
}


typedef struct {
    u8 pad0[6];
    u8 slot[5];
} Obj1_0014D800;

typedef struct {
    u8 pad0[0x38];
    s16 f38;
    s16 f3A;
    u16 id;
} Obj2_0014D800;

s32 TaLogic014_SetSpecialComboQue(s32 arg0, void *arg1, void *arg2) {
    Obj1_0014D800 *o1 = arg1;
    Obj2_0014D800 *o2 = arg2;
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
            if (o2->id == list[i] && TaHand_IsCardSummon2(arg0, list[i]) == 1) {
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
                        o2->f38 += (s16)TaEnc_GetEncScore(list[i]);
                        o2->f3A += (s16)TaEnc_GetEncScore(list[i]);
                    }
                }
            }
        }
    }
    return 1;
}

void TaLogic_GetSommonPiecePreference_0014DA30(s32 unused0, s32 unused1) {
    Ta_GetSommonPiecePreference(unused0, unused1);
}

typedef struct {
    u8 low : 4;
    u8 high : 4;
} Nibbles_0014DA40;

static inline s32 find_0014DA40(void) {
    s32 i;
    s32 position;
    s32 owner;

    i = 0;
    do {
        position = TaLogic014_GetLine(i);
        if ((SzDuel_GetMapUnit(position & 0xFF, position >> 8) == 0 ? 1 : 0) == 1) {
            owner = SzDuel_GetTurnOwner();
            switch (i) {
            case 0:
                position = Ta_GetSommonPiecePreference(owner, 0);
                break;
            case 1:
                position = Ta_GetSommonPiecePreference(owner, 3);
                break;
            case 2:
                position = Ta_GetSommonPiecePreference(owner, 4);
                break;
            default:
                position = -1;
                break;
            }
            return position;
        }
        i++;
    } while (i < 3);
    return -1;
}

s32 TaLogic014_GetSummonPiece(s32 arg0, u8 arg1, void *arg2, s32 arg3) {
    s32 bestPosition;
    s32 bestScore;
    s32 fallbackPosition;
    Nibbles_0014DA40 buffer[12];
    s32 initCount;
    Nibbles_0014DA40 *p;
    s32 kind;
    s32 type;
    s32 position;
    s32 y;
    s32 x;
    s32 i;
    s32 targetY;
    s32 targetX;
    s32 target;
    s32 score;
    extern s32 TaLogic_IsUnitWin4();
    extern s32 SzDuel_Kind2Type();
    extern s32 TaLogic_GetInvadeRoot2();
    extern s32 TaLogic_GetRoot2(s32, s32, s32, s32, s32, s32, u16, u8);

    if (arg2 == NULL) {
        return -1;
    }
    p = buffer;
    initCount = 0;
    do {
        initCount++;
        p->low = p->high = 15;
        p++;
    } while (initCount < 12);

    kind = (type = (u8)(*((u8 *)arg2 + 0x3E) >> 5));
    if (kind == 0 || SzDuel_Kind2Type(kind, type) == 2) {
        if (arg3 >= 0) {
            bestScore = 0xFF;
            bestPosition = 0xFFFF;
            target = SzDuel_GetUnitLoc(arg3 >> 8, arg3 & 0xFF);
            i = 0;
            targetY = target >> 8;
            targetX = target & 0xFF;
            do {
                position = Ta_GetSommonPiecePreference(arg0, i);
                if (position >= 0) {
                    x = position & 0xFF;
                    y = position >> 8;
                    if (SzDuel_GetField(x, y) != 8 &&
                        (SzDuel_GetField(x, y) != 9 || Ta_IsVirus_Chk3(arg2, x, y) != 1) &&
                        SzDuel_GetMapUnit(x, y) == 0) {
                        if (TaLogic_IsUnitWin4((s32)arg2, arg3, TaLogic_GetWarnHideLvl_0014F9B0(arg0),
                                         targetX, targetY, 0) > 0) {
                            score = TaLogic_GetInvadeRoot2((s32)arg2, (s32)buffer, x, y,
                                                 targetX, targetY, arg3, 0, 3,
                                                 (u16)TaLogic_GetWarnHideLvl_0014F9B0(arg0));
                        } else {
                            score = TaLogic_GetRoot2((s32)arg2, (s32)buffer, x, y,
                                                 targetX, targetY, arg3, 3);
                        }
                        if (TaLogic_GetMinGoalCount((u8 *)buffer) > 0 && score < bestScore) {
                            bestScore = score;
                            bestPosition = position;
                        }
                    }
                }
                i++;
            } while (i < 8);
            if (bestPosition != 0xFFFF) {
                return bestPosition;
            }
        }
        {
            s32 y;
            s32 x;
            s32 targetY;
            s32 targetX;
            s32 target;
            s32 score;
            s32 limit;

            limit = 14;
            fallbackPosition = -1;
            i = 0;
            do {
                arg3 = Ta_GetSommonPiecePreference(arg0, i);
                if (arg3 >= 0) {
                    x = arg3 & 0xFF;
                    y = arg3 >> 8;
                    if (SzDuel_GetField(x, y) != 8 &&
                        (SzDuel_GetField(x, y) != 9 || Ta_IsVirus_Chk3(arg2, x, y) != 1) &&
                        SzDuel_GetMapUnitID(x, y) < 0) {
                        target = find_0014DA40();
                        targetX = target & 0xFF;
                        targetY = target >> 8;
                        SzDuel_GetMapUnitID(targetX, targetY);
                        score = TaLogic_GetRoot2((s32)arg2, (s32)buffer, x, y,
                                             targetX, targetY, 0, 7);
                        if (score < limit && score >= 0) {
                            fallbackPosition = arg3;
                            limit = score;
                        }
                    }
                }
                i++;
            } while (i < 8);
            if (limit < 14) {
                return fallbackPosition;
            }
            fallbackPosition = -1;
            return fallbackPosition;
        }
    } else {
        s32 y;
        s32 x;
        s32 i;
        s32 selected;
        s32 position;

        selected = -1;
        i = 0;
        do {
            position = Ta_GetSommonPiecePreference(arg0, i);
            if (position >= 0) {
                x = position & 0xFF;
                y = position >> 8;
                if (SzDuel_GetField(x, y) != 8 &&
                    (SzDuel_GetField(x, y) != 9 || Ta_IsVirus_Chk3(arg2, x, y) != 1) &&
                    SzDuel_GetMapUnitID(x, y) < 0 && y < 8) {
                    selected = position;
                }
            }
            i++;
        } while (i < 8);
        if (selected >= 0) {
            return selected;
        }
        selected = -1;
        return selected;
    }
}

typedef struct Nibbles_0014DF80 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_0014DF80;

typedef struct Output_0014DF80 {
    u16 position;
    u8 action;
    u8 pad3;
    u16 destination;
    u8 pad6[6];
    s32 special;
    u8 result;
} Output_0014DF80;


s32 TaLogic_GetMinimumTask_RunMission_0014DF80(u16 *arg0, s32 arg1, void *arg2, u8 arg3) {
    Output_0014DF80 *output = arg2;
    s32 target;
    u8 endX;
    u8 extra;
    Nibbles_0014DF80 nibbles[12];
    s32 bestScore;
    s32 best;
    s32 i;
    Nibbles_0014DF80 *p;
    extern s32 TaLogic_IsOpenUnit_0014F490();
    extern s32 TaLogic_IsRunPassRoot(s32, s32, s32, s32, s32, s32, void *, u8);

    target = SzDuel_GetUnitLoc(*arg0 >> 8, *arg0 & 0xFF);
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

        initialScore = TaLogic_GetWarnHideLvl_0014F9B0(arg1);
        centerX = target & 0xFF;
        centerY = target >> 8;
        if (TaLogic_GetUnitWarning(centerX, centerY, *arg0, 3, initialScore, 0) == 0) {
            output->position = *arg0;
            output->action = 6;
            output->destination = target;
            output->result = TaLogic_IsDefStyleUnit(*arg0 >> 8, *arg0 & 0xFF, output->destination, 1, 0);
            output->special = TaLogic_IsOpenUnit_0014F490(*arg0 >> 8, *arg0 & 0xFF, arg0);
            TaLogic_InitRogicControl(arg0, arg3);
            return 0;
        }
        if ((range = GetMoveRev(SzDuel_GetUnit(*arg0 >> 8, *arg0 & 0xFF), centerX, centerY)) == 0) {
            output->position = *arg0;
            output->action = 6;
            output->destination = target;
            output->result = TaLogic_IsDefStyleUnit(*arg0 >> 8, *arg0 & 0xFF, output->destination, 1, 0);
            output->special = TaLogic_IsOpenUnit_0014F490(*arg0 >> 8, *arg0 & 0xFF, arg0);
            TaLogic_InitRogicControl(arg0, arg3);
            return 0;
        }
        if (SzDuel_GetUnitStatus(*arg0 >> 8, *arg0 & 0xFF, 4) != 0) {
            if ((SzDuel_GetUnitKind(*arg0 >> 8, *arg0 & 0xFF) >> 5) == 1 ||
                (SzDuel_GetUnitKind(*arg0 >> 8, *arg0 & 0xFF) >> 5) == 5) {
                SzDuel_SetUnitStatus(*arg0 >> 8, *arg0 & 0xFF, 0, 1);
                output->position = *arg0;
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
        if ((*arg0 & 0xFF) == 0) {
            extra = (u8)TaLogic_IsAttackedNow(*arg0 >> 8, *arg0 & 0xFF, 0);
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
                if (TaLogic_IsRunPassRoot(*arg0 >> 8, *arg0 & 0xFF, centerX, centerY, x, y, arg0, extra) == 1) {
                    if (TaLogic_IsAttackedNow2(*arg0 >> 8, *arg0 & 0xFF, x, y, 0) == 0 || (u8)*arg0 == 0) {
                        candidateScore = TaLogic_GetUnitWarning(x, y, *arg0, 3, (u16)TaLogic_GetWarnHideLvl_0014F9B0(arg1), 0);
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
            output->position = *arg0;
            output->action = 6;
            output->destination = best;
            if (best == target) {
                output->result = TaLogic_IsDefStyleUnit(*arg0 >> 8, *arg0 & 0xFF, output->destination, 1, 0);
            } else {
                output->result = TaLogic_IsDefStyleUnit(*arg0 >> 8, *arg0 & 0xFF, output->destination, 0, 0);
            }
            output->special = TaLogic_IsOpenUnit_0014F490(*arg0 >> 8, *arg0 & 0xFF, arg0);
        } else {
            output->position = *arg0;
            output->action = 6;
            output->destination = target;
            output->result = TaLogic_IsDefStyleUnit(*arg0 >> 8, *arg0 & 0xFF, output->destination, 1, 0);
            output->special = TaLogic_IsOpenUnit_0014F490(*arg0 >> 8, *arg0 & 0xFF, arg0);
        }
        TaLogic_InitRogicControl(arg0, arg3);
        return 0;
    }
}

typedef struct {
    u16 position;
    u8 pad2[6];
    u32 targets;
} Input_0014E550;

typedef struct {
    u16 position;
    u8 action;
    u8 pad3;
    u16 destination;
    u8 pad6[6];
    s32 flag;
    u8 result;
} Output_0014E550;

typedef struct {
    u8 x : 4;
    u8 y : 4;
} Point_0014E550;

static inline u32 target_0014E550(void *src, u8 mode) {
    Input_0014E550 *input = src;
    if (mode == 1) {
        return (input->targets >> 16) & 0xFFFF;
    }
    return *(u16 *)&input->targets;
}

static inline s32 max_0014E550(s32 a, s32 b) {
    return a > b ? a : b;
}

s32 TaLogic_GetMinimumTask_AtkMission_0014E550(void *arg0, s32 arg1, void *arg2, u8 arg3) {
    extern s32 TaLogic_IsOpenUnit_0014F490();
    extern void TaLogic_GetInvadeRoot();
    extern s32 GetMoveRev(s32, s32, s32);
    extern s32 TaLogic_GetUnitWarning(s32, s32, s32, s32, s32, u8);
    s32 sourcePosition;
    s32 count;
    s32 sourceY;
    s32 sourceX;
    s32 flag;
    Point_0014E550 points[12];
    s32 destination;
    s32 oldFlag;
    s32 i;
    s32 best;
    u32 targetX;
    u32 targetY;
    Point_0014E550 *p;
    Input_0014E550 *input = arg0;
    Output_0014E550 *output = arg2;

    targetX = target_0014E550(input, arg3);
    targetY = target_0014E550(input, arg3);
    if (SzDuel_GetUnit(targetY >> 8, targetX & 0xFF) == 0) {
        TaLogic_InitRogicControl(input, 1);
        return -1;
    }
    oldFlag = TaLogic_IsOpenUnit_0014F490(input->position >> 8, input->position & 0xFF, input);
    sourcePosition = SzDuel_GetUnitLoc(input->position >> 8, input->position & 0xFF);
    targetX = target_0014E550(input, arg3);
    targetY = target_0014E550(input, arg3);
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
            cost = TaLogic_GetUnitWarning(sourceX, sourceY, arg1, 3, 1, (u8)TaLogic_GetWarnHideLvl_0014F9B0(arg1));
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
            Point_0014E550 *candidate;
            s32 n;
            s32 minCost;
            s32 identity;
            s32 positionY;
            s32 positionX;

            identity = (u16)TaLogic_GetWarnHideLvl_0014F9B0(arg1);
            positionY = position >> 8;
            positionX = position & 0xFF;
            destinationX = destination & 0xFF;

            TaLogic_GetInvadeRoot(positionY, positionX, points,
                         sourceX, sourceY, destinationX, destination >>= 8,
                         target_0014E550(input, arg3), 0, 30, identity);
            count = TaLogic_GetMinGoalCount((u8 *)points);
            best = 0xFF;
            if (count > 0) {
                flag = 0;
                minCost = 0xFFFF;
                for (n = 0; n < count; n++) {
                    if (TaLogic014_IsOpenMoveUnit(input->position >> 8, input->position & 0xFF,
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
                                                3, 1, (u8)TaLogic_GetWarnHideLvl_0014F9B0(arg1));
                        if (cost < minCost) {
                            minCost = cost;
                            best = n;
                        } else if (cost == minCost) {
                            if ((max_0014E550(candidate->x, destinationX) -
                                 (candidate->x < destinationX ? candidate->x : destinationX)) +
                                (max_0014E550(candidate->y, destination) -
                                 (candidate->y < destination ? candidate->y : destination)) <
                                (max_0014E550(points[best].x, destinationX) -
                                 (points[best].x < destinationX ? points[best].x : destinationX)) +
                                (max_0014E550(points[best].y, destination) -
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

typedef struct Coord_0014EB30 {
    u8 x : 4;
    u8 y : 4;
} Coord_0014EB30;

typedef struct Unit_0014EB30 {
    u16 position;
    u8 pad2[6];
    union {
        u32 packed;
        u16 low;
    } target;
} Unit_0014EB30;

typedef struct Output_0014EB30 {
    u16 position;
    u8 kind;
    u8 pad3;
    u16 target;
    u8 pad6[6];
    s32 value;
    u8 flag;
} Output_0014EB30;


static inline u32 target_0014EB30(void *unit, s32 side) {
    return side == 1 ? (u32)(u16)(((Unit_0014EB30 *)unit)->target.packed >> 16) : (u32)((Unit_0014EB30 *)unit)->target.low;
}

static inline u32 minY_0014EB30(void *unit, s32 side, u8 coord) {
    return coord < (target_0014EB30(unit, side) >> 8) ? coord : (target_0014EB30(unit, side) >> 8);
}

static inline u32 maxY_0014EB30(void *unit, s32 side, u8 coord) {
    return (target_0014EB30(unit, side) >> 8) < coord ? coord : (target_0014EB30(unit, side) >> 8);
}

static inline u32 minX_0014EB30(void *unit, s32 side, u8 coord) {
    return coord < (target_0014EB30(unit, side) & 0xFF) ? coord : (target_0014EB30(unit, side) & 0xFF);
}

static inline u32 maxX_0014EB30(void *unit, s32 side, u8 coord) {
    return (target_0014EB30(unit, side) & 0xFF) < coord ? coord : (target_0014EB30(unit, side) & 0xFF);
}

s32 TaLogic_GetMinimumTask_MoveMission_0014EB30(void *arg0, s32 arg1, void *arg2, u8 arg3, u8 arg4) {
    extern s32 TaLogic_IsOpenUnit_0014F490();
    extern s32 TaLogic_GetUnitWarning();
    extern void TaLogic_GetRoot();
    extern s32 TaLogic_IsDefStyleUnit(s32, s32, s32, u8, s32);
    Coord_0014EB30 coords[12];
    s32 initial;
    s32 cell;
    s32 count;

    initial = SzDuel_GetUnitLoc(((Unit_0014EB30 *)arg0)->position >> 8, ((Unit_0014EB30 *)arg0)->position & 0xFF);
    {
    s32 bestScore;
    s32 best;
    s32 side = arg3;
    Coord_0014EB30 *candidate;
    s32 index;
    if (target_0014EB30(arg0, side) == 0xFFFF) {
        if (initial == target_0014EB30(arg0, side)) {
            ((Output_0014EB30 *)arg2)->position = ((Unit_0014EB30 *)arg0)->position;
            ((Output_0014EB30 *)arg2)->kind = 6;
            ((Output_0014EB30 *)arg2)->target = initial;
            ((Output_0014EB30 *)arg2)->flag = TaLogic_IsDefStyleUnit(((Unit_0014EB30 *)arg0)->position >> 8, ((Unit_0014EB30 *)arg0)->position & 0xFF, ((Output_0014EB30 *)arg2)->target, arg4, 0);
            ((Output_0014EB30 *)arg2)->value = TaLogic_IsOpenUnit_0014F490(((Unit_0014EB30 *)arg0)->position >> 8, ((Unit_0014EB30 *)arg0)->position & 0xFF, arg0);
            TaLogic_InitRogicControl(arg0, arg3);
            return 0;
        }
    }

    if (SzDuel_GetUnitStatus(((Unit_0014EB30 *)arg0)->position >> 8,
                      ((Unit_0014EB30 *)arg0)->position & 0xFF, 4) != 0) {
        if ((SzDuel_GetUnitKind(((Unit_0014EB30 *)arg0)->position >> 8,
                          ((Unit_0014EB30 *)arg0)->position & 0xFF) >> 5) == 1 ||
            (SzDuel_GetUnitKind(((Unit_0014EB30 *)arg0)->position >> 8,
                          ((Unit_0014EB30 *)arg0)->position & 0xFF) >> 5) == 5) {
            SzDuel_SetUnitStatus(((Unit_0014EB30 *)arg0)->position >> 8,
                          ((Unit_0014EB30 *)arg0)->position & 0xFF, 0, 1);
            ((Output_0014EB30 *)arg2)->position = ((Unit_0014EB30 *)arg0)->position;
            ((Output_0014EB30 *)arg2)->kind = 0xE;
            return 0;
        }
    }

    candidate = coords;
    {
        s32 i = 0;
        Coord_0014EB30 *entry = candidate;
        do {
            entry->x = entry->y = 0xF;
            i++;
            entry++;
        } while (i < 12);
    }

    cell = SzDuel_GetMapUnitID(target_0014EB30(arg0, side) & 0xFF, ((u32)target_0014EB30(arg0, side)) >> 8);
    if (cell < 0) {
        cell = 0xFFFF;
    }
    TaLogic_GetRoot(((Unit_0014EB30 *)arg0)->position >> 8, ((Unit_0014EB30 *)arg0)->position & 0xFF,
                 coords, initial & 0xFF, initial >> 8, target_0014EB30(arg0, side) & 0xFF,
                 ((u32)target_0014EB30(arg0, side)) >> 8, (u16)cell, 7);
    count = TaLogic_GetMinGoalCount((u8 *)coords);
    {
        if (count > 0) {
        best = 0xFF;
        bestScore = 0xFFFF;
        for (index = 0; index < count; index++) {
                if (SzDuel_GetMapUnit(candidate->x, candidate->y) == 0) {
                    s32 score = TaLogic_GetUnitWarning(candidate->x, candidate->y, arg1, 3, 1, (u8)TaLogic_GetWarnHideLvl_0014F9B0(arg1));
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
                        bestMinY = minY_0014EB30(arg0, side, bestY);
                        bestMaxY = maxY_0014EB30(arg0, side, bestY);
                        bestX = (&coords[best])->x;
                        bestMinX = minX_0014EB30(arg0, side, bestX);
                        bestMaxX = maxX_0014EB30(arg0, side, bestX);
                        currentY = (u8)candidate->y;
                        currentMinY = minY_0014EB30(arg0, side, currentY);
                        currentMaxY = maxY_0014EB30(arg0, side, currentY);
                        currentX = candidate->x;
                        currentMinX = minX_0014EB30(arg0, side, currentX);
                        currentMaxX = maxX_0014EB30(arg0, side, currentX);
                        if ((currentMaxX - currentMinX) + (currentMaxY - currentMinY) < (bestMaxX - bestMinX) + (bestMaxY - bestMinY)) {
                            bestScore = score;
                            best = index;
                        }
                    }
                }
            candidate++;
        }
    } else {
        ((Output_0014EB30 *)arg2)->position = ((Unit_0014EB30 *)arg0)->position;
            ((Output_0014EB30 *)arg2)->kind = 6;
            ((Output_0014EB30 *)arg2)->target = initial;
            ((Output_0014EB30 *)arg2)->flag = TaLogic_IsDefStyleUnit(((Unit_0014EB30 *)arg0)->position >> 8, ((Unit_0014EB30 *)arg0)->position & 0xFF, ((Output_0014EB30 *)arg2)->target, arg4, 0);
            ((Output_0014EB30 *)arg2)->value = TaLogic_IsOpenUnit_0014F490(((Unit_0014EB30 *)arg0)->position >> 8, ((Unit_0014EB30 *)arg0)->position & 0xFF, arg0);
        TaLogic_InitRogicControl(arg0, arg3);
        return 0;
    }

        if (best != 0xFF) {
            ((Output_0014EB30 *)arg2)->position = ((Unit_0014EB30 *)arg0)->position;
            ((Output_0014EB30 *)arg2)->kind = 6;
            ((Output_0014EB30 *)arg2)->target = (coords[best].y << 8) | coords[best].x;
            ((Output_0014EB30 *)arg2)->flag = TaLogic_IsDefStyleUnit(((Unit_0014EB30 *)arg0)->position >> 8, ((Unit_0014EB30 *)arg0)->position & 0xFF, ((Output_0014EB30 *)arg2)->target, arg4, 0);
            ((Output_0014EB30 *)arg2)->value = TaLogic_IsOpenUnit_0014F490(((Unit_0014EB30 *)arg0)->position >> 8, ((Unit_0014EB30 *)arg0)->position & 0xFF, arg0);
        } else {
            ((Output_0014EB30 *)arg2)->position = ((Unit_0014EB30 *)arg0)->position;
            ((Output_0014EB30 *)arg2)->kind = 6;
            ((Output_0014EB30 *)arg2)->target = initial;
            ((Output_0014EB30 *)arg2)->flag = TaLogic_IsDefStyleUnit(((Unit_0014EB30 *)arg0)->position >> 8, ((Unit_0014EB30 *)arg0)->position & 0xFF, ((Output_0014EB30 *)arg2)->target, arg4, 0);
            ((Output_0014EB30 *)arg2)->value = TaLogic_IsOpenUnit_0014F490(((Unit_0014EB30 *)arg0)->position >> 8, ((Unit_0014EB30 *)arg0)->position & 0xFF, arg0);
        }
        TaLogic_InitRogicControl(arg0, arg3);
    }
    }
    return 0;
}

static inline s32 dispatch_0014F3A0(s32 index, s32 id) {
    switch (index) {
    case 0:
        return Ta_GetSommonPiecePreference(id, 0);
    case 1:
        return Ta_GetSommonPiecePreference(id, 3);
    case 2:
        return Ta_GetSommonPiecePreference(id, 4);
    default:
        return -1;
    }
}

static inline s32 select_0014F3A0(void) {
    s32 index;
    s32 position;
    s32 id;

    index = 0;
    do {
        position = TaLogic014_GetLine(index);
        if (((SzDuel_GetMapUnit(position & 0xFF, position >> 8) == 0) ? 1 : 0) == 1) {
            id = SzDuel_GetTurnOwner();
            return dispatch_0014F3A0(index, id);
        }
        index++;
    } while (index < 3);
    return -1;
}

s32 TaLogic014_IsActiveMode(void) {
    s32 result;

    result = select_0014F3A0();
    if (result < 0) {
        return 1;
    }
    return 0;
}

/* From the dotr-decomp CC0 bundle (commit 88c32bb2), chatC/imp/conv.py. */

extern int func_0027D830_b(int, int, int, int, int, int);
extern int func_001E1030_b(int a, int b);
extern unsigned *func_001E0B70_b(int a, int b, int n);
struct DotrStateItem;
extern struct DotrStateItem *func_001E36E0_b(int x, int y);
static inline int spot_find(void)
{
    int i;
    int spot;

    for (i = 0; i < 3; i++) {
        spot = TaLogic014_GetLine(i);
        if ((func_001E36E0_b(spot & 0xff, spot >> 8) == 0 ? 1 : 0) == 1) {
            return TaLogic014_GetLine(i);
        }
    }
    return -1;
}

int TaLogic_IsOpenUnit_0014F490(int x, int y)
{
    int kind;
    int pos;
    int side;
    unsigned *p;
    int r;
    kind = func_001E1030_b(x, y);
    pos = SzDuel_GetUnitLoc(x, y);
    side = Ta_IsUnitControl(x, y);
    p = func_001E0B70_b(x, y, 0);
    if (SzDuel_GetUnitStatus(x, y, 4)) {
        return 0;
    }
    switch (SzDuel_GetUnitKind(x, y) >> 5) {
    case 0:
        switch (kind) {
        case 612:
        case 551:
            if (TaLogic014_IsUnitNaturalEffectUse(side, kind) == 1) {
                return 1;
            }
            break;
        }
        return 2;
    case 5:
        if (func_0027D830_b(x, y, 0, 0, 6, 0) == 5) {
            return 2;
        }
        if (TaLogic014_IsDoCerem(Ta_IsUnitControl(x, y), kind) == 1) {
            if (SzDuel_GetField(pos & 0xFF, pos >> 8) != 9) {
                return 1;
            }
        }
        break;
    case 1:
        if (func_0027D830_b(x, y, 0, 0, 6, 0) == 5) {
            return 2;
        }
        if (p == 0) {
            return 2;
        }
        switch (*p >> 8) {
        case 13:
            return 1;
        case 2:
            r = TaLogic_GetLandChange(SzDuel_GetUnit(x, y), pos & 0xFF, pos >> 8, 4, 9, 2);
            if (r >= 0 && r == pos) {
                return 1;
            }
            break;
        case 4:
            if ((spot_find() < 0 ? 1 : 0) == 1) {
                if (SzDuel_GetUnitSpellCount(x) == 0) {
                    return 1;
                }
            }
            break;
        case 18:
            if (SzDuel_GetUnitMonsterCount(x) >= 4) {
                return 1;
            }
            break;
        }
        break;
    default:
        return 2;
    }
    return 2;
}

static inline s32 max_0014F7C0(s32 a, s32 b) {
    if (b < a) {
        return a;
    }
    return b;
}

s32 TaLogic014_IsOpenMoveUnit(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 min_y;
    s32 min_x;

    min_y = arg3 < arg5 ? arg3 : arg5;
    arg5 = max_0014F7C0(arg3, arg5);
    min_x = arg2 < arg4 ? arg2 : arg4;
    arg4 = max_0014F7C0(arg2, arg4);
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

s32 TaLogic014_IsDoCerem(s32 arg0, s32 arg1) {
    s32 sp50[4];
    s32 i;
    s32 mask;
    s32 low;
    s32 high;
    s32 cell;
    s32 value;

    Ta_GetCeremSacrifice(sp50, *(s32 *)((u8 *)TaHand_GetCardEffect(arg1, 0) + 4));
    if ((mask = Ta_GetSacrificeUnit(sp50, arg0)) < 0) {
        return 0;
    }
    for (i = 0; i < Ta_GetUnitNumFrom22bitFlagList(mask); i++) {
        cell = Ta_GetUnitOwnerIDFromLstCount(mask, i);
        high = cell >> 8;
        low = cell & 0xFF;
        value = SzDuel_GetUnitLoc(high, low);
        if (TaUtil_GetUnitAP(high, low, value & 0xFF, value >> 8) >= 0x9C4) {
            return 0;
        }
    }
    return 1;
}

s32 TaLogic_GetWarnHideLvl_0014F9B0(s32 arg0) {
    if (SzDuel_GetLP(arg0) > 0x4B0) {
        if (SzDuel_GetUnitMonsterCount(arg0) >= 5) {
            return 0x2EE;
        } else {
            return 0x5DC;
        }
    } else {
        return 0x960;
    }
}

s32 TaLogic014_IsUnitNaturalEffectUse(s32 arg0, s32 arg1) {
    s32 index;
    u8 count;
    s32 mask;
    s32 entry;

    count = 0;
    switch (arg1) {
    case 0x264:
        if (Ta_GetUnitNumFrom22bitFlagList(SearchUnitByRange(0, 0, arg0, 1, 0x10, 0xE)) <= 3) {
            break;
        }
        return 1;
    case 0x227:
        if (Ta_GetUnitNumFrom22bitFlagList(SearchUnitByRange(0, 0, arg0, 1, 0xF, 0xE)) > 0) {
            return 0;
        }
        mask = SearchUnitByRange(0, 0, arg0, 2, 0xF, 0xE);
        for (index = 0; index < Ta_GetUnitNumFrom22bitFlagList(mask); index++) {
            entry = Ta_GetUnitOwnerIDFromLstCount(mask, index);
            if (TaLogic_IsJudgeUnitDanger(entry >> 8, entry & 0xFF, 0) == 1) {
                count++;
            }
        }
        if (count >= 2) {
            return 1;
        }
        break;
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
} Req_0014FB70;

typedef struct {
    u8 pad0[0x160];
    u16 list[32];    /* 0x160 */
    u8 idx : 5;      /* 0x1A0 */
    u8 pad1A0 : 3;
    u8 pad1A1;
    u16 count;       /* 0x1A2 */
} Work_0014FB70;

s32 TaLogic_GetInputQueFromMinimumTask_b(void *, void *, s32);

s32 func_0014FB70(s32 arg0, void *arg1) {
    Req_0014FB70 req;
    Work_0014FB70 *w;
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
        if (TaLogic_GetMinimumTask_0014B900(w, &req, arg0) == 0) {
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

/* From the dotr-decomp CC0 bundle (commit 88c32bb2), chatC/imp/conv.py. */

struct DotrFinderUnit {
    unsigned short wUnit;
    unsigned short wOrder;
    unsigned short wPurpose;
    unsigned int dwGoal;
    unsigned char bCond : 2;
};
struct DotrFinderTask {
    unsigned short wUnit;
    unsigned char bPurpose;
    unsigned short wGoal;
    unsigned char bHand[5];
    int bOpen;
    unsigned char bDefense;
};
extern void func_0027B1B0_b(struct DotrFinderUnit *unit, int mode);
extern int func_0027D020_b(struct DotrFinderUnit *unit, int side, struct DotrFinderTask *task, int first, int view, int lvl, int g, int h);
extern int func_00150470_b(struct DotrFinderUnit *list, int side, struct DotrFinderTask *task);
extern void func_00150270_b(struct DotrFinderUnit *unit);
extern int func_00152100_b(struct DotrFinderUnit *unit, int side, struct DotrFinderTask *task, int first);
extern int func_001526D0_b(struct DotrFinderUnit *unit, int side, struct DotrFinderTask *task, int first);
extern int func_00152CD0_b(struct DotrFinderUnit *unit, int side, struct DotrFinderTask *task, int first, int e);
extern int func_00150C40_b(int pos, int side, struct DotrFinderTask *task);
static inline int CRun_val(struct DotrFinderUnit *unit, int side, struct DotrFinderTask *task, int first, int done)
{
    if (SzDuel_GetUnitStatus(unit->wUnit >> 8, unit->wUnit & 0xff, 0) == 0) {
        func_00152100_b(unit, side, task, first);
        done = 1;
    }
    return done;
}
static inline int CMove_val(struct DotrFinderUnit *unit, int side, struct DotrFinderTask *task, int first, int e, int done)
{
    if (SzDuel_GetUnitStatus(unit->wUnit >> 8, unit->wUnit & 0xff, 0) == 0) {
        func_00152CD0_b(unit, side, task, first, e);
        done = 1;
    }
    return done;
}
static inline int CEnc_val(struct DotrFinderUnit *unit, int side, struct DotrFinderTask *task, int first, int done)
{
    func_0027D020_b(unit, side, task, first, 0, TaLogic_GetWarnHideLvl_00153ED0(side), 5, 1);
    done = 1;
    return done;
}
static inline void CRun_void(struct DotrFinderUnit *unit, int side, struct DotrFinderTask *task, int first, int *pd)
{
    if (SzDuel_GetUnitStatus(unit->wUnit >> 8, unit->wUnit & 0xff, 0) == 0) {
        func_00152100_b(unit, side, task, first);
        *pd = 1;
    }
}
static inline void CMove_void(struct DotrFinderUnit *unit, int side, struct DotrFinderTask *task, int first, int e, int *pd)
{
    if (SzDuel_GetUnitStatus(unit->wUnit >> 8, unit->wUnit & 0xff, 0) == 0) {
        func_00152CD0_b(unit, side, task, first, e);
        *pd = 1;
    }
}
static inline void CEnc_void(struct DotrFinderUnit *unit, int side, struct DotrFinderTask *task, int first, int *pd)
{
    func_0027D020_b(unit, side, task, first, 0, TaLogic_GetWarnHideLvl_00153ED0(side), 5, 1);
    *pd = 1;
}

int TaLogic_GetMinimumTask_0014FD40(void *list_v, void *task_v, int owner)
{
    struct DotrFinderUnit * list = list_v;
    struct DotrFinderTask * task = task_v;
    int side = SzDuel_GetTurnOwner();
    int done = 0;
    int r;
    int idx;

    (void)owner;
    if ((r = func_00150470_b(list, side, task)) < 0) {
        return 0;
    }
    idx = TaLogic_GetActionUnitFromOwnerID(list, r & 0xffff);
    if (idx < 0) {
        return 0;
    }
    if ((r >> 16) == 1) {
        if (((list[idx].wPurpose >> 8) & 0xff) == 10) {
            func_0027B1B0_b(&list[idx], 1);
        } else {
            func_0027B1B0_b(&list[idx], 0);
        }
        return 1;
    }
    func_00150270_b(&list[idx]);
    switch ((list[idx].wPurpose >> 8) & 0xff) {
    case 5:
        CRun_void(&list[idx], side, task, 1, &done);
        break;
    case 2:
        if (SzDuel_GetUnitStatus(list[idx].wUnit >> 8, list[idx].wUnit & 0xff, 0) == 0) {
            if (func_001526D0_b(&list[idx], side, task, 1) < 0) {
                func_0027B1B0_b(&list[idx], 1);
                return 1;
            }
            done = 1;
        }
        break;
    case 10:
        if (func_00150C40_b(list[idx].wUnit, side, task) < 0) {
            func_0027B1B0_b(&list[idx], 1);
            task->bPurpose = 255;
            task->bOpen = 0;
            break;
        }
        func_0027B1B0_b(&list[idx], 1);
        done = 1;
        break;
    case 6:
        CMove_void(&list[idx], side, task, 1, 0, &done);
        break;
    case 3:
        CMove_void(&list[idx], side, task, 1, 1, &done);
        break;
    case 11:
        TaLogic_GetMinimumTask_TrapMission_00153550(&list[idx], side, task, 1);
        done = 1;
        break;
    case 9:
        CEnc_void(&list[idx], side, task, 1, &done);
        break;
    case 14:
        TaLogic_GetMinimumTask_DoNone(&list[idx], side, task);
        done = 1;
        break;
    default:
        done = 0;
        break;
    }
    if (done == 1) {
        return 1;
    }
    done = 0;
    switch (list[idx].wPurpose & 0xff) {
    case 5:
        done = CRun_val(&list[idx], side, task, 0, done);
        break;
    case 2:
        if (SzDuel_GetUnitStatus(list[idx].wUnit >> 8, list[idx].wUnit & 0xff, 0) == 0) {
            if (func_001526D0_b(&list[idx], side, task, 0) < 0) {
                func_00152100_b(&list[idx], side, task, 0);
            }
            done = 1;
        }
        break;
    case 10:
        if (func_00150C40_b(list[idx].wUnit, side, task) < 0) {
            func_0027B1B0_b(&list[idx], 0);
            task->bPurpose = 255;
            done = 1;
            task->bOpen = 0;
            break;
        }
        func_0027B1B0_b(&list[idx], 0);
        done = 1;
        break;
    case 6:
        done = CMove_val(&list[idx], side, task, 0, 0, done);
        break;
    case 3:
        done = CMove_val(&list[idx], side, task, 0, 1, done);
        break;
    case 11:
        TaLogic_GetMinimumTask_TrapMission_00153550(&list[idx], side, task, 0);
        done = 1;
        break;
    case 9:
        done = CEnc_val(&list[idx], side, task, 0, done);
        break;
    case 14:
        TaLogic_GetMinimumTask_DoNone(&list[idx], side, task);
        break;
    default:
        return 0;
    }
    if (done == 1) {
        return 1;
    }
    return 0;
}

typedef struct {
    u16 pos;
    u16 unk2;
    u16 unk4;
    u16 unk6;
    s32 unk8;
} Unit_00150270;


s32 TaLogic_CommandUnit_00150270(void *arg0) {
    Unit_00150270 *unit = arg0;
    s32 handle;

    SzDuel_GetUnitLoc(unit->pos >> 8, unit->pos & 0xFF);
    handle = Ta_IsUnitControl(unit->pos >> 8, unit->pos & 0xFF);
    if (SzDuel_GetUnit(unit->pos >> 8, unit->pos & 0xFF) != 0 &&
        SzDuel_GetUnitStatus(unit->pos >> 8, unit->pos & 0xFF, 0) == 0 && unit->pos != 0xFFFF) {
        if ((unit->pos & 0xFF) == 0) {
            if (unit->unk8 == -1) {
                if (TaLogic015_IsActiveMode() == 1) {
                    TaLogic_CommandStdLDUnit(unit, 3, 3, 0);
                } else if (TaLogic_IsAttackedNow(unit->pos >> 8, unit->pos & 0xFF, 0) == 1) {
                    if (SzDuel_InqHandPhase(unit->pos >> 8) == 1) {
                        unit->unk4 = 0x50A;
                    } else {
                        unit->unk4 = 0x5FF;
                    }
                } else {
                    if (SzDuel_InqHandPhase(unit->pos >> 8) == 1) {
                        unit->unk4 = 0xA05;
                    } else {
                        unit->unk4 = 0x5FF;
                    }
                }
            }
        } else {
            switch (SzDuel_GetUnitKind(unit->pos >> 8, unit->pos & 0xFF) >> 5) {
            case 0:
            case 1:
            case 3:
            case 4:
                TaLogic015_CommandBtlUnit(unit);
                break;
            case 2:
                TaLogic_CommandEncUnit(unit, 5, 0, (u8)TaLogic_GetWarnHideLvl_00153ED0(handle));
                break;
            default:
                unit->unk4 = 0x5FF;
                break;
            }
        }
        return 1;
    }
    return 0;
}

s32 TaLogic_GetNextActiveUnit_00150470(u16 *arg0, s32 arg1, s32 arg2) {
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
    TaLogic_CommandUnit_00150270(arg0 + idx * 8);
    if (((arg0[idx * 8 + 2] >> 8) & 0xFF) == 10) {
        if (SzDuel_InqHandPhase(arg1) == 1 && TaLogic_GetMinimumTask_Summon_00150C40(pos, arg1, arg2) >= 0) {
            return pos | 0x10000;
        }
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_GetUnitStatus(arg1, 0, 0) == 0) {
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_InqHandPhase(arg1) == 1 && TaLogic_GetMinimumTask_Summon_00150C40(pos, arg1, arg2) >= 0) {
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

struct DotrTryOrder {
    unsigned short position;
    unsigned short unknown_02;
    unsigned short unknown_04;
    unsigned short unknown_06;
    union {
        unsigned short half;
        int word;
    } flags;
};
struct DotrTryCell {
    unsigned short id;
    unsigned char kind;
};
extern void func_0027E770_b(void *buf);
extern int func_0027B200_b(int a, int b, int c, int d, int e, int f, int g, int h, unsigned char i);
extern int func_001E1030_b(int a, int b);
extern int func_00150BE0_b(struct DotrTryOrder *order, int r1, int r2, int r3, int r4, int r5, int r6, int r7, struct DotrTryCell *cells, int s1, unsigned short *a, unsigned short *b, int n, void *buf);

void TaLogic015_CommandBtlUnit(void *order_v)
{
    struct DotrTryOrder * order = order_v;
    unsigned char buf[112];
    struct DotrTryCell cells[22];
    unsigned short a;
    unsigned short b;
    int here;
    int other;
    int side;
    int there;
    int word;
    int i;
    int r;
    unsigned char deep;

    deep = TaLogic015_IsActiveMode();
    if (SzDuel_GetUnit(order->position >> 8, order->position & 0xff) == 0) {
        return;
    }
    side = Ta_GetCurrentSide(order->position >> 8, order->position & 0xff);
    other = (side == 0 ? 1 : 0) << 8;
    here = SzDuel_GetUnitLoc(order->position >> 8, order->position & 0xff);
    there = SzDuel_GetUnitLoc(other >> 8, other & 0xff);
    word = SzDuel_GetUnit(order->position >> 8, order->position & 0xff);
    func_0027E770_b(buf);
    if (func_001E1030_b(order->position >> 8, order->position & 0xff) == 686) {
        order->unknown_04 = 0xcff;
        return;
    }
    for (i = 0; i < 22; i++) {
        cells[i].id = 0xffff;
        cells[i].kind = 0xff;
    }
    if (func_0027B200_b(order->position >> 8, order->position & 0xff, (unsigned char)here, here >> 8, other >> 8, other & 0xff, (unsigned char)there, there >> 8, 2) > 0) {
        if ((SzDuel_GetUnitKind(order->position >> 8, order->position & 0xff) >> 5) == 0) {
            order->unknown_04 = 0x2ff;
        } else {
            order->unknown_04 = 0xbff;
        }
        order->flags.word = (other << 16) | order->flags.half;
        return;
    }
    b = 0;
    a = 0;
    for (other = 1; other <= (deep ? 5 : 2); other++) {
        r = func_00150BE0_b(order, 0, word, (unsigned char)here, here >> 8, Ta_GetCurrentSide(order->position >> 8, order->position & 0xff) == 0 ? 1 : 0, other & 0xff, TaLogic_GetWarnHideLvl_00153ED0(side), cells, 0, &a, &b, (unsigned char)(deep ? 5 : 2), buf);
        switch (r) {
        case 3:
            order->unknown_04 = 0x6ff;
            order->flags.word = (here << 16) | order->flags.half;
            return;
        case 2:
            order->unknown_04 = 0x3ff;
            order->flags.word = (here << 16) | order->flags.half;
            return;
        case 1:
            if (SzDuel_GetUnitKind(order->position >> 8, order->position & 0xff) >> 5) {
                order->unknown_04 = 0xbff;
            }
            return;
        case 0:
            order->unknown_04 = 0x3ff;
            order->flags.word = (here << 16) | order->flags.half;
            return;
        }
    }
    order->unknown_04 = 0x6ff;
    if (((here >> 8) <= 3 && (there >> 8) <= 3) || ((here >> 8) > 3 && (there >> 8) > 3)) {
        order->flags.word = (there << 16) | order->flags.half;
    } else {
        order->flags.word = (((here & 0xff) | 0x300) << 16) | order->flags.half;
    }
}

void TaLogic015_GetNearUnit(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7,
                   s32 a8, u16 a9, s32 a10, s32 a11, u8 a12, s32 a13) {
    TaLogic_GetNearUnit(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, 0, 2000, a13);
}

typedef struct {
    s16 card;
    u8 f2;
    u8 pad3;
    s16 f4;
    u8 pad6[6];
    s32 fC;
} Act_00150C40;

typedef struct {
    u8 pad0[0x3C];
    u16 id;
    u8 pad3E[0x22];
} Card_00150C40;

s32 TaLogic_GetNearCard2(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8,
                  s32 arg9);

s32 TaLogic_GetMinimumTask_Summon_00150C40(s32 arg0, s32 arg1, s32 arg2) {
    extern s32 TaLogic_GetUnitNum(s32, s32);
    Card_00150C40 buf;
    s32 res;
    s32 type;
    Act_00150C40 *act = (Act_00150C40 *)arg2;
    s32 card;
    s32 r;

    act->card = arg0;
    if (SzDuel_InqHandPhase(arg1) == 0) {
        return -1;
    }
    if (TaLogic_GetUnitNum(arg1, 0) == 5 && TaLogic_GetUnitNum(arg1, 1) == 5) {
        return -1;
    }
    type = TaLogic015_IsHandPlay(arg1, &buf);
    if (type < 0) {
        return -1;
    }
    act->f2 = 10;
    act->fC = 0;
    card = SzDuel_GetUnitLoc(arg0 >> 8, arg0 & 0xFF);
    if (type == 0) {
        if (TaLogic015_SetComboQue(arg1, act, &buf) >= 0) {
            res = TaLogic_GetNearCard2(&buf, card & 0xFF, card >> 8, arg1 == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, TaLogic_GetWarnHideLvl_00153ED0(arg1));
            if (res < 0) {
                if (SzDuel_GetUnitMonsterCount(arg1) < 6) {
                    r = TaLogic015_GetSummonPiece(arg1, type, &buf, res);
                    if (r < 0) {
                        return -1;
                    }
                    act->f4 = r;
                    return 1;
                }
            } else {
                r = TaLogic015_GetSummonPiece(arg1, type, &buf, res);
                if (r < 0) {
                    return -1;
                }
                act->f4 = r;
                return 1;
            }
        }
    } else {
        res = TaLogic_GetNearCard2(&buf, card & 0xFF, card >> 8, arg1 == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, TaLogic_GetWarnHideLvl_00153ED0(arg1));
    }
    if (type == 2) {
        TaLogic015_SetSpecialComboQue(arg1, act, &buf);
        r = TaLogic015_GetSummonPiece(arg1, type, &buf, res);
        if (r < 0) {
            return -1;
        }
        act->f4 = r;
        return 1;
    } else if (type == 3) {
        TaLogic015_GetSpecialComboPlay(arg1, act, &buf);
        r = TaLogic015_GetSummonPiece(arg1, type, &buf, res);
        if (r < 0) {
            return -1;
        }
        act->f4 = r;
        return 1;
    } else {
        if (TaLogic015_GetSpellPlay(arg1, (u8 *)act, &buf, buf.id) < 0) {
            return -1;
        }
        r = TaLogic015_GetSummonPiece(arg1, type, &buf, res);
        if (r < 0) {
            return -1;
        }
        act->f4 = r;
        return 1;
    }
}

s32 TaLogic015_IsHandPlay(s32 arg0, void *arg1) {
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
        s32 result = TaLogic015_GetSpellPlay(arg0, (u8 *)data, arg1, 0x3E7);
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
    if (TaLogic015_GetSpecialComboPlay(arg0, (u8 *)data, arg1) == 1) {
        return 3;
    }
    if (TaLogic015_IsUseRevive(arg0) == 1) {
        s32 result = TaLogic015_GetSpecCardPlay(arg0, (u8 *)data, arg1, 0x2AE);
        if (result >= 0) {
            return 2;
        }
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
                    SzDuel_InitCardInfo(arg1, ids[i]);
                    return 0;
                }
                p++;
                i++;
                count = TaHand_GetNextHandNum(arg0);
            } while (i < count);
        }
    }
    {
        s32 result = TaLogic015_GetSpellPlay(arg0, (u8 *)data, arg1, 0x3E7);
        if (result >= 0) {
            return result;
        }
        return -1;
    }
}

typedef struct {
    u8 pad0[6];
    u8 slot[5];
} Obj1_00151170;

typedef struct {
    u8 pad0[0x38];
    s16 attack;
    s16 defense;
} Obj2_00151170;


s32 TaLogic015_GetSpecialComboPlay(s32 arg0, void *arg1, void *arg2) {
    Obj2_00151170 *o2 = arg2;
    Obj1_00151170 *o1 = arg1;
    s32 list[8];
    s32 i;
    s32 found;
    u8 k;

    TaHand_GetNextHand(arg0, list);
    for (i = 0, found = 0; i < TaHand_GetNextHandNum(arg0); i++) {
        if (list[i] == 0x31F) {
            found = 1;
            o1->slot[0] = i;
        }
    }
    if (found == 0) {
        return -1;
    }
    for (i = 0, found = 0; i < TaHand_GetNextHandNum(arg0); i++) {
        if (list[i] == 7 && TaHand_IsCardSummon2(arg0, list[i]) == 1) {
            o1->slot[1] = i;
            found = 1;
        }
    }
    if (found == 0) {
        return -1;
    }
    k = 2;
    SzDuel_InitCardInfo(o2, 0x1F5);
    for (i = 0; i < TaHand_GetNextHandNum(arg0); i++) {
        if (i != o1->slot[0] && i != o1->slot[1]) {
            if (Ta_GetHandEnchant(0x1F5, list[i]) >= 0 && (TaHand_GetCardKind(list[i]) >> 5) == 2) {
                if (list[i] != 0x31B && list[i] != 0x31C) {
                    o1->slot[k] = i;
                    k++;
                    o2->attack += (s16)TaEnc_GetEncScore(list[i]);
                    o2->defense += (s16)TaEnc_GetEncScore(list[i]);
                }
            }
        }
    }
    return 1;
}

s32 TaLogic015_GetSpecCardPlay(s32 arg0, void *arg1, void *arg2, s32 arg3) {
    s32 i;
    s32 ids[8];

    TaHand_GetNextHand(arg0, ids);
    for (i = 0; i < TaHand_GetNextHandNum(arg0); i++) {
        if (((arg3 & 0xFFFF) == ids[i]) &&
            (TaHand_IsCardSummon2(arg0, ids[i]) == 1)) {
            ((u8 *)arg1)[6] = i;
            SzDuel_InitCardInfo(arg2, ids[i]);
            return TaHand_GetCardKind(ids[i]) >> 5;
        }
    }
    return -1;
}

s32 TaLogic015_GetSpellPlay(s32 arg0, u8 *arg1, void *arg2, s32 arg3) {
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

typedef struct Info_001516A0 {
    u8 pad00[8];
    u16 x;
    s16 y;
} Info_001516A0;

typedef struct Sprite_001516A0 {
    Info_001516A0 *info;
    u8 pad04[0x34];
    s16 x;
    s16 y;
} Sprite_001516A0;


s32 TaLogic015_SetComboQue(s32 arg0, u8 *arg1, void *arg2) {
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
                if ((TaHand_GetCardKind(card) >> 5) == 0 && TaHand_IsCardSummon2(arg0, card) == 1) {
                    *node = TaLogic_GetFusionTree(arg0, (struct TreeTag *)*node, i & 0xFF, card & 0xFFFF, 0, (u16 *)&a, (u16 *)&b);
                    *node = TaLogic_GetFusionRes(*node);
                    value = TaLogic_GetEnchantQue(arg0, *node, 0, 0);
                    if (best < value) {
                        SzDuel_InitCardInfo(arg2, **node);
                        ((Sprite_001516A0 *)arg2)->x = (value >> 16) - (((Sprite_001516A0 *)arg2)->info->x & 0x1FFF);
                        ((Sprite_001516A0 *)arg2)->y = (value & 0xFFFF) - (((Sprite_001516A0 *)arg2)->info->y & 0x1FFF);
                        TaLogic_ConvEmptyCombo_00151880(arg0, *node, entries);
                        TaLogic_CopyArray((u8 *)*node + 2, arg1 + 6);
                        best = value;
                        if (top < value) {
                            top = value;
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

typedef struct {
    u16 id;
    u8 values[5];
} Info_00151880;

void TaLogic_ConvEmptyCombo_00151880(s32 arg0, void *arg1, s32 *arg2) {
    Info_00151880 *info = arg1;
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
                if (card != 0x3E7 && TaLogic015_IsRefuseEmptyCombo(card) == 0 && level >= TaHand_GetCardSummonCost2(card, arg0)) {
                    cost = TaHand_GetCardAPDP(card);
                    if ((cost & 0xFFFF) + (cost >> 16) * 2 < 0xDAD && TaHand_IsCardEffect(card) == 2 &&
                        (u16)TaLogic_GetHandFusion(info->id, (u16)card) == 0x3E7) {
                        TaLogic_AddEmptyCombo(info->values, buf[i]);
                    }
                }
            }
        }
    }
}

s32 TaLogic015_IsRefuseEmptyCombo(s32 arg0) {
    if ((TaHand_GetCardKind(arg0) >> 5) != 0) {
        return 1;
    }
    if (TaHand_IsCardEffect(arg0) == 1) {
        return 1;
    }
    return 0;
}


typedef struct {
    u8 pad0[6];
    u8 slot[5];
} Obj1_00151AC0;

typedef struct {
    u8 pad0[0x38];
    s16 f38;
    s16 f3A;
    u16 id;
} Obj2_00151AC0;

s32 TaLogic015_SetSpecialComboQue(s32 arg0, void *arg1, void *arg2) {
    Obj1_00151AC0 *o1 = arg1;
    Obj2_00151AC0 *o2 = arg2;
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
            if (o2->id == list[i] && TaHand_IsCardSummon2(arg0, list[i]) == 1) {
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
                        o2->f38 += (s16)TaEnc_GetEncScore(list[i]);
                        o2->f3A += (s16)TaEnc_GetEncScore(list[i]);
                    }
                }
            }
        }
    }
    return 1;
}

typedef struct Nibbles_00151CF0 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_00151CF0;

s32 TaLogic015_GetSummonPiece(s32 arg0, u8 arg1, void *arg2, s32 arg3) {
    s32 bestPosition;
    s32 bestScore;
    Nibbles_00151CF0 cells[12];
    s32 targetY;
    s32 targetX;
    s32 kind;
    s32 type;
    s32 j;
    Nibbles_00151CF0 *cell;

    extern s32 TaLogic_IsUnitWin4();
    extern s32 SzDuel_Kind2Type();
    extern s32 TaLogic_GetInvadeRoot2();
    extern s32 TaLogic_GetRoot2(s32, s32, s32, s32, s32, s32, u16, u8);

    if (arg2 == NULL) {
        return -1;
    }
    cell = cells;
    j = 0;
    do {
        cell->low = cell->high = 15;
        j++;
        cell++;
    } while (j < 12);
    kind = (type = (u8)(*((u8 *)arg2 + 0x3E) >> 5));
    if (kind == 0 || SzDuel_Kind2Type(kind, type) == 2) {
        if (arg3 >= 0) {
            s32 position;
            s32 y;
            s32 x;
            s32 i;
            s32 score;
            s32 target;
            bestScore = 255;
            bestPosition = 65535;
            target = SzDuel_GetUnitLoc(arg3 >> 8, arg3 & 255);
            i = 0;
            targetY = target >> 8;
            targetX = target & 255;
            do {
                position = Ta_GetSommonPiecePreference(arg0, i);
                if (position >= 0) {
                    x = position & 255;
                    y = position >> 8;
                    if (SzDuel_GetField(x, y) != 8 &&
                        (SzDuel_GetField(x, y) != 9 || Ta_IsVirus_Chk3(arg2, x, y) != 1) &&
                        SzDuel_GetMapUnit(x, y) == 0) {
                        if (TaLogic_IsUnitWin4(arg2, arg3, TaLogic_GetWarnHideLvl_00153ED0(arg0), targetX, targetY, 0) > 0) {
                            score = TaLogic_GetInvadeRoot2(arg2, cells, x, y, targetX, targetY,
                                                arg3, 0, 3, (u16)TaLogic_GetWarnHideLvl_00153ED0(arg0));
                        } else {
                            score = TaLogic_GetRoot2((s32)arg2, (s32)cells, x, y, targetX, targetY, arg3, 3);
                        }
                        if (TaLogic_GetMinGoalCount((u8 *)cells) > 0 && score < bestScore) {
                            bestScore = score;
                            bestPosition = position;
                        }
                    }
                }
                i++;
            } while (i < 8);
            if (bestPosition != 65535) {
                return bestPosition;
            }
        }
        {
        s32 y;
        s32 x;
        s32 i;
        s32 position;
        SzDuel_GetUnitLoc(arg3 >> 8, arg3 & 255);
        i = 0;
        do {
            position = Ta_GetSommonPiecePreference(arg0, i);
            if (position >= 0) {
                x = position & 255;
                y = position >> 8;
                if (SzDuel_GetField(x, y) != 8 &&
                    (SzDuel_GetField(x, y) != 9 || Ta_IsVirus_Chk3(arg2, x, y) != 1) &&
                    SzDuel_GetMapUnitID(x, y) < 0) {
                    return position;
                }
            }
            i++;
        } while (i < 8);
        return -1;
        }
    } else {
        s32 y;
        s32 x;
        s32 i;
        s32 result;
        s32 position;
        result = -1;
        i = 0;
        do {
            position = Ta_GetSommonPiecePreference(arg0, i);
            if (position >= 0) {
                x = position & 255;
                y = position >> 8;
                if (SzDuel_GetField(x, y) != 8 &&
                    (SzDuel_GetField(x, y) != 9 || Ta_IsVirus_Chk3(arg2, x, y) != 1) &&
                    SzDuel_GetMapUnitID(x, y) < 0 && y < 8) {
                    result = position;
                }
            }
            i++;
        } while (i < 8);
        if (result >= 0) {
            return result;
        }
        result = -1;
        return result;
    }
}

typedef struct Nibbles_00152100 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_00152100;

typedef struct Output_00152100 {
    u16 position;
    u8 action;
    u8 pad3;
    u16 destination;
    u8 pad6[6];
    s32 special;
    u8 result;
} Output_00152100;


s32 TaLogic_GetMinimumTask_RunMission_00152100(u16 *arg0, s32 arg1, void *arg2, u8 arg3) {
    Output_00152100 *output = arg2;
    s32 target;
    u8 endX;
    u8 extra;
    Nibbles_00152100 nibbles[12];
    s32 bestScore;
    s32 best;
    s32 i;
    Nibbles_00152100 *p;
    extern s32 TaLogic_IsOpenUnit_00153AE0();
    extern s32 TaLogic_IsRunPassRoot(s32, s32, s32, s32, s32, s32, void *, u8);

    target = SzDuel_GetUnitLoc(*arg0 >> 8, *arg0 & 0xFF);
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

        initialScore = TaLogic_GetWarnHideLvl_00153ED0(arg1);
        centerX = target & 0xFF;
        centerY = target >> 8;
        if (TaLogic_GetUnitWarning(centerX, centerY, *arg0, 3, initialScore, 0) == 0) {
            output->position = *arg0;
            output->action = 6;
            output->destination = target;
            output->result = TaLogic_IsDefStyleUnit(*arg0 >> 8, *arg0 & 0xFF, output->destination, 1, 0);
            output->special = TaLogic_IsOpenUnit_00153AE0(*arg0 >> 8, *arg0 & 0xFF, arg0);
            TaLogic_InitRogicControl(arg0, arg3);
            return 0;
        }
        if ((range = GetMoveRev(SzDuel_GetUnit(*arg0 >> 8, *arg0 & 0xFF), centerX, centerY)) == 0) {
            output->position = *arg0;
            output->action = 6;
            output->destination = target;
            output->result = TaLogic_IsDefStyleUnit(*arg0 >> 8, *arg0 & 0xFF, output->destination, 1, 0);
            output->special = TaLogic_IsOpenUnit_00153AE0(*arg0 >> 8, *arg0 & 0xFF, arg0);
            TaLogic_InitRogicControl(arg0, arg3);
            return 0;
        }
        if (SzDuel_GetUnitStatus(*arg0 >> 8, *arg0 & 0xFF, 4) != 0) {
            if ((SzDuel_GetUnitKind(*arg0 >> 8, *arg0 & 0xFF) >> 5) == 1 ||
                (SzDuel_GetUnitKind(*arg0 >> 8, *arg0 & 0xFF) >> 5) == 5) {
                SzDuel_SetUnitStatus(*arg0 >> 8, *arg0 & 0xFF, 0, 1);
                output->position = *arg0;
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
        if ((*arg0 & 0xFF) == 0) {
            extra = (u8)TaLogic_IsAttackedNow(*arg0 >> 8, *arg0 & 0xFF, 0);
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
                if (TaLogic_IsRunPassRoot(*arg0 >> 8, *arg0 & 0xFF, centerX, centerY, x, y, arg0, extra) == 1) {
                    if (TaLogic_IsAttackedNow2(*arg0 >> 8, *arg0 & 0xFF, x, y, 0) == 0 || (u8)*arg0 == 0) {
                        candidateScore = TaLogic_GetUnitWarning(x, y, *arg0, 3, (u16)TaLogic_GetWarnHideLvl_00153ED0(arg1), 0);
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
            output->position = *arg0;
            output->action = 6;
            output->destination = best;
            if (best == target) {
                output->result = TaLogic_IsDefStyleUnit(*arg0 >> 8, *arg0 & 0xFF, output->destination, 1, 0);
            } else {
                output->result = TaLogic_IsDefStyleUnit(*arg0 >> 8, *arg0 & 0xFF, output->destination, 0, 0);
            }
            output->special = TaLogic_IsOpenUnit_00153AE0(*arg0 >> 8, *arg0 & 0xFF, arg0);
        } else {
            output->position = *arg0;
            output->action = 6;
            output->destination = target;
            output->result = TaLogic_IsDefStyleUnit(*arg0 >> 8, *arg0 & 0xFF, output->destination, 1, 0);
            output->special = TaLogic_IsOpenUnit_00153AE0(*arg0 >> 8, *arg0 & 0xFF, arg0);
        }
        TaLogic_InitRogicControl(arg0, arg3);
        return 0;
    }
}

typedef struct Input_001526D0 {
    u16 position;
    u8 pad2[6];
    u32 destinations;
} Input_001526D0;

typedef struct Output_001526D0 {
    u16 position;
    u8 command;
    u8 pad3;
    u16 destination;
    u8 pad6[6];
    s32 state;
    u8 result;
} Output_001526D0;

typedef struct Point_001526D0 {
    u8 x : 4;
    u8 y : 4;
} Point_001526D0;

static inline u32 destination_001526D0(void *src, u8 mode) {
    if (mode == 1) {
        return (u16)(((Input_001526D0 *)src)->destinations >> 16);
    }
    return *(u16 *)((u8 *)src + 8);
}


s32 TaLogic_GetMinimumTask_AtkMission_001526D0(void *src, s32 arg1, u16 *out, u8 arg3) {
    extern s32 TaLogic_IsOpenUnit_00153AE0();
    extern void TaLogic_GetInvadeRoot();
    s32 state;
    s32 current;
    s32 count;
    u8 mode;
    s32 target;
    s32 currentY;
    s32 currentX;
    s32 forced;
    s32 i;
    s32 unit;
    u32 destinationX;
    u32 destinationY;
    Point_001526D0 points[12];

    mode = TaLogic015_IsActiveMode();
    destinationX = destination_001526D0(src, arg3);
    destinationY = destination_001526D0(src, arg3);
    if (SzDuel_GetUnit(destinationY >> 8, destinationX & 0xFF) == 0) {
        TaLogic_InitRogicControl(src, 1);
        return -1;
    }
    state = TaLogic_IsOpenUnit_00153AE0(((Input_001526D0 *)src)->position >> 8,
                         ((Input_001526D0 *)src)->position & 0xFF, src);
    current = SzDuel_GetUnitLoc(((Input_001526D0 *)src)->position >> 8,
                           ((Input_001526D0 *)src)->position & 0xFF);
    destinationX = destination_001526D0(src, arg3);
    destinationY = destination_001526D0(src, arg3);
    target = SzDuel_GetUnitLoc(destinationY >> 8, destinationX & 0xFF);
    for (i = 0; i < 12; i++) {
        points[i].x = points[i].y = 0xF;
    }
    unit = SzDuel_GetUnit(((Input_001526D0 *)src)->position >> 8,
                        ((Input_001526D0 *)src)->position & 0xFF);
    currentX = current & 0xFF;
    currentY = current >> 8;
    if (GetMoveRev(unit, currentX, currentY) == 0) {
        s32 cost;
        ((Output_001526D0 *)out)->position = ((Input_001526D0 *)src)->position;
        ((Output_001526D0 *)out)->command = 6;
        ((Output_001526D0 *)out)->destination = current;
        cost = TaLogic_GetUnitWarning(currentX, currentY, arg1, 3, 1,
                            (u8)TaLogic_GetWarnHideLvl_00153ED0(arg1));
        if (cost >= SzDuel_GetUnitAP(((Input_001526D0 *)src)->position >> 8,
                                 ((Input_001526D0 *)src)->position & 0xFF, 0)) {
            ((Output_001526D0 *)out)->result = TaLogic_IsDefStyleUnit(
                ((Input_001526D0 *)src)->position >> 8,
                ((Input_001526D0 *)src)->position & 0xFF,
                out[2], 1, 0);
        } else {
            ((Output_001526D0 *)out)->result = TaLogic_IsDefStyleUnit(
                ((Input_001526D0 *)src)->position >> 8,
                ((Input_001526D0 *)src)->position & 0xFF,
                out[2], 0, 0);
        }
        TaLogic_InitRogicControl(src, arg3);
    } else {
        s32 y;
        s32 x;
        Point_001526D0 *point;
        s32 index;
        s32 bestCost;
        s32 selected;
        s32 position = ((Input_001526D0 *)src)->position;
        TaLogic_GetInvadeRoot(position >> 8, position & 0xFF, points, currentX, currentY,
                      x = target & 0xFF, y = target >> 8,
                      destination_001526D0(src, arg3), 0, 30,
                      (u16)TaLogic_GetWarnHideLvl_00153ED0(arg1));
        count = TaLogic_GetMinGoalCount((u8 *)points);
        selected = 0xFF;
        if (count > 0) {
            forced = 0;
            bestCost = 0xFFFF;
            for (index = 0; index < count; index++) {
                s32 hit = TaLogic015_IsOpenMoveUnit(((Input_001526D0 *)src)->position >> 8,
                                      ((Input_001526D0 *)src)->position & 0xFF,
                                      currentX, currentY, x, y);
                if (hit == 1) {
                    Point_001526D0 *forcedPoint = &points[index];
                    selected = index;
                    forced = 1;
                    index = count;
                    forcedPoint->x = x;
                    forcedPoint->y = y;
                } else {
                    s32 cost;
                    point = &points[index];
                    cost = TaLogic_GetUnitWarning(point->x, point->y, arg1,
                                        (u8)(mode ? 5 : 2), 1,
                                        (u8)TaLogic_GetWarnHideLvl_00153ED0(arg1));
                    if (cost < bestCost) {
                        bestCost = cost;
                        selected = index;
                    } else if (cost == bestCost) {
                        if (((x < point->x ? point->x : x) -
                             (point->x < x ? point->x : x)) +
                            ((y < point->y ? point->y : y) -
                             (point->y < y ? point->y : y)) <
                            ((x < points[selected].x ? points[selected].x : x) -
                             (points[selected].x < x ? points[selected].x : x)) +
                            ((y < points[selected].y ? points[selected].y : y) -
                             (points[selected].y < y ? points[selected].y : y))) {
                            bestCost = cost;
                            selected = index;
                        }
                    }
                }
            }
        } else {
            ((Output_001526D0 *)out)->position = ((Input_001526D0 *)src)->position;
            ((Output_001526D0 *)out)->command = 6;
            ((Output_001526D0 *)out)->destination = current;
            ((Output_001526D0 *)out)->state = state;
            ((Output_001526D0 *)out)->result = TaLogic_IsDefStyleUnit(
                ((Input_001526D0 *)src)->position >> 8,
                ((Input_001526D0 *)src)->position & 0xFF,
                ((Output_001526D0 *)out)->destination, 0, 0);
            TaLogic_InitRogicControl(src, arg3);
            return 0;
        }
        if (selected != 0xFF) {
            ((Output_001526D0 *)out)->position = ((Input_001526D0 *)src)->position;
            ((Output_001526D0 *)out)->command = 6;
            ((Output_001526D0 *)out)->destination = (points[selected].y << 8) | points[selected].x;
            ((Output_001526D0 *)out)->state = forced;
            ((Output_001526D0 *)out)->result = TaLogic_IsDefStyleUnit(
                ((Input_001526D0 *)src)->position >> 8,
                ((Input_001526D0 *)src)->position & 0xFF,
                ((Output_001526D0 *)out)->destination, 0, 0);
        } else {
            ((Output_001526D0 *)out)->position = ((Input_001526D0 *)src)->position;
            ((Output_001526D0 *)out)->command = 6;
            ((Output_001526D0 *)out)->destination = current;
            ((Output_001526D0 *)out)->state = forced;
            ((Output_001526D0 *)out)->result = TaLogic_IsDefStyleUnit(
                ((Input_001526D0 *)src)->position >> 8,
                ((Input_001526D0 *)src)->position & 0xFF,
                ((Output_001526D0 *)out)->destination, 0, 0);
            TaLogic_InitRogicControl(src, arg3);
            return 0;
        }
    }
    return 0;
}

typedef struct Coord_00152CD0 {
    u8 x : 4;
    u8 y : 4;
} Coord_00152CD0;

typedef struct Unit_00152CD0 {
    u16 position;
    u8 pad2[6];
    union {
        u32 packed;
        u16 low;
    } target;
} Unit_00152CD0;

typedef struct Output_00152CD0 {
    u16 position;
    u8 kind;
    u8 pad3;
    u16 target;
    u8 pad6[6];
    s32 value;
    u8 flag;
} Output_00152CD0;


static inline u32 target_00152CD0(void *unit, s32 side) {
    return side == 1 ? (u32)(u16)(((Unit_00152CD0 *)unit)->target.packed >> 16) : (u32)((Unit_00152CD0 *)unit)->target.low;
}

static inline u32 minY_00152CD0(void *unit, s32 side, u8 coord) {
    return coord < (target_00152CD0(unit, side) >> 8) ? coord : (target_00152CD0(unit, side) >> 8);
}

static inline u32 maxY_00152CD0(void *unit, s32 side, u8 coord) {
    return (target_00152CD0(unit, side) >> 8) < coord ? coord : (target_00152CD0(unit, side) >> 8);
}

static inline u32 minX_00152CD0(void *unit, s32 side, u8 coord) {
    return coord < (target_00152CD0(unit, side) & 0xFF) ? coord : (target_00152CD0(unit, side) & 0xFF);
}

static inline u32 maxX_00152CD0(void *unit, s32 side, u8 coord) {
    return (target_00152CD0(unit, side) & 0xFF) < coord ? coord : (target_00152CD0(unit, side) & 0xFF);
}

s32 TaLogic_GetMinimumTask_MoveMission_00152CD0(void *arg0, s32 arg1, void *arg2, u8 arg3, u8 arg4) {
    extern s32 TaLogic_IsOpenUnit_00153AE0();
    extern s32 TaLogic_GetUnitWarning();
    extern void TaLogic_GetRoot();
    extern s32 TaLogic_IsDefStyleUnit(s32, s32, s32, u8, s32);
    Coord_00152CD0 coords[12];
    s32 initial;
    s32 cell;
    s32 count;
    u8 status;

    status = TaLogic015_IsActiveMode();
    initial = SzDuel_GetUnitLoc(((Unit_00152CD0 *)arg0)->position >> 8, ((Unit_00152CD0 *)arg0)->position & 0xFF);
    {
        s32 bestScore;
        s32 best;
        s32 side = arg3;
        Coord_00152CD0 *candidate;
        s32 index;
        if (target_00152CD0(arg0, side) == 0xFFFF) {
            if (initial == target_00152CD0(arg0, side)) {
                ((Output_00152CD0 *)arg2)->position = ((Unit_00152CD0 *)arg0)->position;
                ((Output_00152CD0 *)arg2)->kind = 6;
                ((Output_00152CD0 *)arg2)->target = initial;
                ((Output_00152CD0 *)arg2)->flag = TaLogic_IsDefStyleUnit(((Unit_00152CD0 *)arg0)->position >> 8, ((Unit_00152CD0 *)arg0)->position & 0xFF, ((Output_00152CD0 *)arg2)->target, arg4, 0);
                ((Output_00152CD0 *)arg2)->value = TaLogic_IsOpenUnit_00153AE0(((Unit_00152CD0 *)arg0)->position >> 8, ((Unit_00152CD0 *)arg0)->position & 0xFF, arg0);
                TaLogic_InitRogicControl(arg0, arg3);
                return 0;
            }
        }

        if (SzDuel_GetUnitStatus(((Unit_00152CD0 *)arg0)->position >> 8, ((Unit_00152CD0 *)arg0)->position & 0xFF, 4) != 0) {
            if ((SzDuel_GetUnitKind(((Unit_00152CD0 *)arg0)->position >> 8, ((Unit_00152CD0 *)arg0)->position & 0xFF) >> 5) == 1 ||
                (SzDuel_GetUnitKind(((Unit_00152CD0 *)arg0)->position >> 8, ((Unit_00152CD0 *)arg0)->position & 0xFF) >> 5) == 5) {
                SzDuel_SetUnitStatus(((Unit_00152CD0 *)arg0)->position >> 8, ((Unit_00152CD0 *)arg0)->position & 0xFF, 0, 1);
                ((Output_00152CD0 *)arg2)->position = ((Unit_00152CD0 *)arg0)->position;
                ((Output_00152CD0 *)arg2)->kind = 14;
                return 0;
            }
        }

        candidate = coords;
        {
            s32 i = 0;
            Coord_00152CD0 *entry = candidate;
            do {
                entry->x = entry->y = 0xF;
                i++;
                entry++;
            } while (i < 12);
        }

        cell = SzDuel_GetMapUnitID(target_00152CD0(arg0, side) & 0xFF, target_00152CD0(arg0, side) >> 8);
        if (cell < 0) {
            cell = 0xFFFF;
        }
        TaLogic_GetRoot(((Unit_00152CD0 *)arg0)->position >> 8, ((Unit_00152CD0 *)arg0)->position & 0xFF,
                     coords, initial & 0xFF, initial >> 8, target_00152CD0(arg0, side) & 0xFF,
                     target_00152CD0(arg0, side) >> 8, (u16)cell, 7);
        count = TaLogic_GetMinGoalCount((u8 *)coords);
        {
            if (count > 0) {
                best = 0xFF;
                bestScore = 0xFFFF;
                for (index = 0; index < count; index++) {
                    if (SzDuel_GetMapUnit(candidate->x, candidate->y) == 0) {
                        s32 score = TaLogic_GetUnitWarning(candidate->x, candidate->y, arg1, (u8)(status ? 5 : 2), 1, (u8)TaLogic_GetWarnHideLvl_00153ED0(arg1));
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
                            bestMinY = minY_00152CD0(arg0, side, bestY);
                            bestMaxY = maxY_00152CD0(arg0, side, bestY);
                            bestX = (&coords[best])->x;
                            bestMinX = minX_00152CD0(arg0, side, bestX);
                            bestMaxX = maxX_00152CD0(arg0, side, bestX);
                            currentY = (u8)candidate->y;
                            currentMinY = minY_00152CD0(arg0, side, currentY);
                            currentMaxY = maxY_00152CD0(arg0, side, currentY);
                            currentX = candidate->x;
                            currentMinX = minX_00152CD0(arg0, side, currentX);
                            currentMaxX = maxX_00152CD0(arg0, side, currentX);
                            if ((currentMaxX - currentMinX) + (currentMaxY - currentMinY) < (bestMaxX - bestMinX) + (bestMaxY - bestMinY)) {
                                bestScore = score;
                                best = index;
                            }
                        }
                    }
                    candidate++;
                }
            } else {
                ((Output_00152CD0 *)arg2)->position = ((Unit_00152CD0 *)arg0)->position;
                ((Output_00152CD0 *)arg2)->kind = 6;
                ((Output_00152CD0 *)arg2)->target = initial;
                ((Output_00152CD0 *)arg2)->flag = TaLogic_IsDefStyleUnit(((Unit_00152CD0 *)arg0)->position >> 8, ((Unit_00152CD0 *)arg0)->position & 0xFF, ((Output_00152CD0 *)arg2)->target, arg4, 0);
                ((Output_00152CD0 *)arg2)->value = TaLogic_IsOpenUnit_00153AE0(((Unit_00152CD0 *)arg0)->position >> 8, ((Unit_00152CD0 *)arg0)->position & 0xFF, arg0);
                TaLogic_InitRogicControl(arg0, arg3);
                return 0;
            }

            if (best != 0xFF) {
                ((Output_00152CD0 *)arg2)->position = ((Unit_00152CD0 *)arg0)->position;
                ((Output_00152CD0 *)arg2)->kind = 6;
                ((Output_00152CD0 *)arg2)->target = (coords[best].y << 8) | coords[best].x;
                ((Output_00152CD0 *)arg2)->flag = TaLogic_IsDefStyleUnit(((Unit_00152CD0 *)arg0)->position >> 8, ((Unit_00152CD0 *)arg0)->position & 0xFF, ((Output_00152CD0 *)arg2)->target, arg4, 0);
                ((Output_00152CD0 *)arg2)->value = TaLogic_IsOpenUnit_00153AE0(((Unit_00152CD0 *)arg0)->position >> 8, ((Unit_00152CD0 *)arg0)->position & 0xFF, arg0);
            } else {
                ((Output_00152CD0 *)arg2)->position = ((Unit_00152CD0 *)arg0)->position;
                ((Output_00152CD0 *)arg2)->kind = 6;
                ((Output_00152CD0 *)arg2)->target = initial;
                ((Output_00152CD0 *)arg2)->flag = TaLogic_IsDefStyleUnit(((Unit_00152CD0 *)arg0)->position >> 8, ((Unit_00152CD0 *)arg0)->position & 0xFF, ((Output_00152CD0 *)arg2)->target, arg4, 0);
                ((Output_00152CD0 *)arg2)->value = TaLogic_IsOpenUnit_00153AE0(((Unit_00152CD0 *)arg0)->position >> 8, ((Unit_00152CD0 *)arg0)->position & 0xFF, arg0);
            }
            TaLogic_InitRogicControl(arg0, arg3);
        }
    }
    return 0;
}

typedef struct Input_00153550 {
    u16 position;
    u8 pad2[6];
    u32 target;
} Input_00153550;

typedef struct Output_00153550 {
    u16 position;
    u8 action;
    u8 pad3;
    u16 destination;
    u8 pad6[10];
    u8 result;
} Output_00153550;

typedef struct Point_00153550 {
    u8 x : 4;
    u8 y : 4;
} Point_00153550;

#define MIN_00153550(a, b) ((a) < (b) ? (a) : (b))
#define MAX_00153550(a, b) ((b) < (a) ? (a) : (b))


static inline u32 target_00153550(void *src, s32 mode) {
    if (mode == 1) {
        return (u16)(((Input_00153550 *)src)->target >> 16);
    } else {
        return *(u16 *)((u8 *)src + 8);
    }
}

static inline void stay_00153550(void *src, void *dst, s32 position, s32 flag) {
    Input_00153550 *source = src;
    Output_00153550 *out = dst;

    out->position = source->position;
    out->action = 6;
    out->destination = position;
    out->result = TaLogic_IsDefStyleUnit(source->position >> 8, source->position & 0xFF,
                                out->destination, flag, 0);
}

s32 TaLogic_GetMinimumTask_TrapMission_00153550(void *arg0, s32 arg1, void *arg2, s32 arg3) {
    s32 start;
    s32 count;
    u8 flag;
    s32 startY;
    Point_00153550 points[12];
    s32 bestScore;
    Point_00153550 *p;
    s32 targetY;
    s32 targetX;
    s32 i;
    s32 bestIndex;
    s32 mode;
    s32 target;
    s32 startX;
    u32 xPosition;
    u32 yPosition;
    Input_00153550 *source = arg0;
    Output_00153550 *out = arg2;
    extern void TaLogic_GetInvadeRoot();

    flag = TaLogic015_IsActiveMode();
    mode = arg3 & 0xFF;
    xPosition = target_00153550(arg0, mode);
    yPosition = target_00153550(arg0, mode);
    if (SzDuel_GetUnit(yPosition >> 8, xPosition & 0xFF) == 0) {
        TaLogic_InitRogicControl(arg0, 1);
        return -1;
    }
    start = SzDuel_GetUnitLoc(source->position >> 8, source->position & 0xFF);
    xPosition = target_00153550(arg0, mode);
    yPosition = target_00153550(arg0, mode);
    target = SzDuel_GetUnitLoc(yPosition >> 8, xPosition & 0xFF);
    if (target_00153550(arg0, mode) == 0xFFFF) {
        stay_00153550(arg0, arg2, start, 1);
        return 0;
    } else {
        s32 unit = SzDuel_GetUnit(source->position >> 8, source->position & 0xFF);
        startX = start & 0xFF;
        startY = start >> 8;
        if (GetMoveRev(unit, startX, startY) == 0 ||
                TaLogic_IsAttackedNow(source->position >> 8, source->position & 0xFF, 0) == 1) {
            stay_00153550(arg0, arg2, start, 1);
            return 0;
        } else {
            p = points;
            {
                s32 n = 0;
                Point_00153550 *q = p;
                do {
                    q->x = q->y = 0xF;
                    q++;
                    n++;
                } while (n < 12);
            }
            {
                s32 position = source->position;
                u16 card = (u16)TaLogic_GetWarnHideLvl_00153ED0(arg1);
                TaLogic_GetInvadeRoot(position >> 8, position & 0xFF, points,
                    startX, startY, targetX = target & 0xFF,
                    targetY = target >> 8, target_00153550(arg0, mode),
                    0, 30, card);
            }
            count = TaLogic_GetMinGoalCount((u8 *)points);
            bestIndex = 0xFF;
            if (count > 0) {
                bestScore = 0;
                for (i = 0; i < count; i++, p++) {
                    if (SzDuel_GetMapUnit(p->x, p->y) == 0) {
                        s32 score = TaLogic_GetUnitWarning(p->x, p->y, arg1, (u8)(flag ? 5 : 2), 1,
                            (u8)TaLogic_GetWarnHideLvl_00153ED0(arg1));
                        if (bestScore < score) {
                            bestScore = score;
                            bestIndex = i;
                        } else if (score == bestScore) {
                            if (MAX_00153550(p->x, targetX) - MIN_00153550(p->x, targetX)
                                    + (MAX_00153550(p->y, targetY) - MIN_00153550(p->y, targetY))
                                    < MAX_00153550(points[bestIndex].x, targetX) - MIN_00153550(points[bestIndex].x, targetX)
                                    + (MAX_00153550(points[bestIndex].y, targetY) - MIN_00153550(points[bestIndex].y, targetY))) {
                                bestScore = score;
                                bestIndex = i;
                            }
                        }
                    }
                }
            } else {
                stay_00153550(arg0, arg2, start, 1);
                return 0;
            }
            if (bestIndex != 0xFF) {
                out->position = source->position;
                out->action = 6;
                out->destination = (points[bestIndex].y << 8) | points[bestIndex].x;
                out->result = TaLogic_IsDefStyleUnit(source->position >> 8,
                    source->position & 0xFF, out->destination, 0, 0);
            } else {
                stay_00153550(arg0, arg2, start, 1);
                return 0;
            }
        }
    }
    return 0;
}

s32 TaLogic015_IsActiveMode(void) {
    return (SzDuel_GetUnitCount(SzDuel_GetTurnOwner()) < 3) ? 0 : 1;
}

s32 TaLogic_IsOpenUnit_00153AE0(s32 arg0, s32 arg1) {
    extern s32 SzDuel_GetUnitCardNo();
    u16 buf[22];
    s32 kind;
    u32 *info;
    s32 c1;
    s32 c2;
    s32 player;
    s32 y1;
    s32 x1;
    s32 y2;
    s32 x2;
    s32 pos;
    s32 score;

    kind = SzDuel_GetUnitCardNo(arg0, arg1);
    SzDuel_GetUnitLoc(arg0, arg1);
    player = Ta_IsUnitControl(arg0, arg1);
    info = SzDuel_GetUnitEffect(arg0, arg1, 0);
    if (SzDuel_GetUnitStatus(arg0, arg1, 4) != 0) {
        return 0;
    }
    TaUtil_GetUnitLst(player, 2, buf);
    switch (SzDuel_GetUnitKind(arg0, arg1) >> 5) {
    case 0:
        switch (kind) {
        case 0x24:
            if (Ta_GetUnitNumFrom22bitFlagList(SearchUnitByRange(0, 0, player, 1, 0x95F0037, 0xE)) >= 2) {
                return 1;
            }
            break;
        case 0xD5:
            if (Ta_GetUnitNumFrom22bitFlagList(SearchUnitByRange(0, 0, player, 1, 0x1D, 0x16)) >= 2) {
                return 1;
            }
            break;
        }
        return 2;
    case 1:
        if (TaLogic_GetActionReaction(arg0, arg1, 0, 0, 6, 0) == 5) {
            return 2;
        }
        if (info == NULL) {
            return 2;
        }
        switch (*info >> 8) {
        case 0xD:
            return 1;
        case 0x21:
            TaLogic_GetUnitCtlLst2((player == 0) ? 1 : 0, buf, 0x1D, 0, 0);
            pos = TaLogic_GetMaxApUnit(buf);
            x1 = pos >> 8;
            y1 = pos & 0xFF;
            c1 = SzDuel_GetUnitLoc(x1, y1);
            TaLogic_GetUnitCtlLst(player, buf, 0x1D, 1);
            pos = TaLogic_GetMaxApUnit(buf);
            x2 = pos >> 8;
            y2 = pos & 0xFF;
            c2 = SzDuel_GetUnitLoc(x2, y2);
            TaUtil_GetUnitLst(player, 1, buf);
            if (TaUtil_GetUnitAP(x1, y1, c1 & 0xFF, c1 >> 8) >= 2000) {
                score = TaUtil_GetUnitAP(x1, y1, c1 & 0xFF, c1 >> 8);
                if (TaUtil_GetUnitAP(x2, y2, c2 & 0xFF, c2 >> 8) < score) {
                    return 1;
                }
            }
            break;
        }
        break;
    default:
        return 2;
    }
    return 2;
}

static inline s32 max_00153DD0(s32 a, s32 b) {
    if (a < b) {
        return b;
    }
    return a;
}

s32 TaLogic015_IsOpenMoveUnit(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 min_y;
    s32 min_x;

    min_y = arg3 < arg5 ? arg3 : arg5;
    arg5 = max_00153DD0(arg5, arg3);
    min_x = arg2 < arg4 ? arg2 : arg4;
    arg4 = max_00153DD0(arg4, arg2);
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

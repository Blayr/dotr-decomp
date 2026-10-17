#include "common.h"

/* The next unit of side `nSide` to act: first one that can attack now, then the others by task. */
s32 TaLogic_GetNextActiveUnit_0014BFD0(u16 *pCtl, s32 nSide, s32 pInput) {
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
    TaLogic_CommandUnit_0014BDE0(pCtl + idx * 8);
    if (((pCtl[idx * 8 + 2] >> 8) & 0xFF) == 10) {
        if (SzDuel_InqHandPhase(nSide) == 1 && TaLogic_GetMinimumTask_Summon_0014CBA0(pos, nSide, pInput) >= 0) {
            return pos | 0x10000;
        }
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_GetUnitStatus(nSide, 0, 0) == 0) {
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_InqHandPhase(nSide) == 1 && TaLogic_GetMinimumTask_Summon_0014CBA0(pos, nSide, pInput) >= 0) {
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
    u16 unitId; /* (side << 8) | unit */
    u8 pad2[2];
    u16 state;
    u8 pad6[2];
    union {
        u32 word;
        DataHalves_0014C3B0 halves;
    } data;
} Entry_0014C3B0;


/* Orders a fighting unit (task `pTask`): straight at its goal when the path is open, else the nearest enemy it can
   beat. */
void TaLogic014_CommandBtlUnit(void *pTask) {
    extern s32 TaLogic_IsRootOpen();
    extern void TaLogic_InitIgnoreLst();
    extern s32 TaLogic014_GetNearUnit();
    Entry_0014C3B0 *entry = pTask;
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

    if (SzDuel_GetUnit(entry->unitId >> 8, entry->unitId & 0xFF) != 0) {
        side = Ta_GetCurrentSide(entry->unitId >> 8, entry->unitId & 0xFF);
        other = (side == 0 ? 1 : 0) << 8;
        pos = SzDuel_GetUnitLoc(entry->unitId >> 8, entry->unitId & 0xFF);
        otherPos = SzDuel_GetUnitLoc(other >> 8, other & 0xFF);
        player = SzDuel_GetUnit(entry->unitId >> 8, entry->unitId & 0xFF);
        TaLogic_InitIgnoreLst(work);
        for (i = 0; i < 22; i++) {
            list[i].card = 0xFFFF;
            list[i].flag = 0xFF;
        }
        if (TaLogic_IsRootOpen(entry->unitId >> 8, entry->unitId & 0xFF, pos & 0xFF, pos >> 8,
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
                                  Ta_GetCurrentSide(entry->unitId >> 8, entry->unitId & 0xFF) == 0 ? 1 : 0,
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

/* TaLogic_GetNearUnit with this duelist's view and strength settings. */
void TaLogic014_GetNearUnit(s32 pTask, s32 pTree, s32 pVarInfo, s32 nX, s32 nZ, s32 eSide, s32 bDist, s32 WarnLvl, s32 nUnitLst, u16 wUnitNum, s32 wSize, s32 wNodeCount, u8 bChase, s32 wIgnoreLst) {
    TaLogic_GetNearUnit(pTask, pTree, pVarInfo, nX, nZ, eSide, bDist, WarnLvl,
        nUnitLst, wUnitNum, wSize, wNodeCount, bChase, 0, 2500, wIgnoreLst);
}

/* Orders an effect monster (task `pTask`): where its effect does most. */
void TaLogic014_CommandEfcMonster(void *pTask) {
    extern s32 SzDuel_GetUnitCardNo();
    Entry_0014C3B0 *entry = pTask;
    s32 slot;
    s32 kind;

    slot = Ta_IsUnitControl(entry->unitId >> 8, entry->unitId & 0xFF);
    kind = SzDuel_GetUnitCardNo(entry->unitId >> 8, entry->unitId & 0xFF);
    switch (kind) {
    case 0x264:
    case 0x227:
        if (TaLogic014_IsUnitNaturalEffectUse(slot, kind) == 1) {
            entry->state = 0x3FF;
            entry->data.word = (SzDuel_GetUnitLoc(entry->unitId >> 8, entry->unitId & 0xFF) << 16) | entry->data.halves.low;
            return;
        }
        break;
    case 0x23A:
        if (TaLogic014_IsActiveMode() == 1 && TaLogic_CommandGunnerUnit(entry, 0) == 1) {
            return;
        }
        break;
    case 0x23F:
        if (TaLogic014_IsActiveMode() == 1 && SzDuel_GetUnitStatus(entry->unitId >> 8, entry->unitId & 0xFF, 4) == 0 && TaLogic_CommandGunnerUnit(entry, 0) == 1) {
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


/* Orders a face-down magic card (task `pTask`): whether and where to open it. */
void TaLogic014_CommandSpellUnit(void *pTask) {
    Entry_0014C870 *entry = pTask;
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

/* Whether (nX, nZ) is one of this duelist's three line squares. */
s32 TaLogic014_IsLinePoint(s32 nX, s32 nZ) {
    s32 var_s0;

    var_s0 = 0;
loop_1:
    if (((nZ << 8) | nX) == TaLogic014_GetLine(var_s0)) {
        return 1;
    }
    var_s0 += 1;
    if (var_s0 >= 3) {
        return 0;
    }
    goto loop_1;
}

/* Line square `nNo` (0..2) of this duelist (from its summon preferences), or -1. */
s32 TaLogic014_GetLine(s32 nNo) {
    s32 TaLogic_GetSommonPiecePreference_0014DA30(s32, s32);
    s32 id;

    id = SzDuel_GetTurnOwner();
    switch (nNo) {
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

/* Line square `index` (0..2) of this duelist, or -1. */
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

/* The free line of the board this duelist's units fill next. */
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

/* The summon task for side `nSide`: which hand cards to play and where, into `pInput`; -1 when it plays none. */
s32 TaLogic_GetMinimumTask_Summon_0014CBA0(s32 wUnit, s32 nSide, s32 pInput) {
    s32 ret;
    s32 kind;
    Ctx_0014CBA0 *ctx = (Ctx_0014CBA0 *)pInput;
    Work_0014CBA0 work;
    s32 res;
    extern s32 TaLogic_GetUnitNum();

    ctx->id = wUnit;
    if (SzDuel_InqHandPhase(nSide) == 0) {
        return -1;
    }
    if (TaLogic_GetUnitNum(nSide, 0) == 5 && TaLogic_GetUnitNum(nSide, 1) == 5) {
        return -1;
    }
    kind = TaLogic014_IsHandPlay(nSide, &work);
    if (kind < 0) {
        return -1;
    }
    ctx->unk2 = 10;
    ctx->unkC = 2;
    wUnit = SzDuel_GetUnitLoc(wUnit >> 8, wUnit & 0xFF);
    if (kind == 0) {
        if (TaLogic014_SetComboQue(nSide, (u8 *)ctx, &work) >= 0) {
            ret = TaLogic_GetNearCard2(&work, wUnit & 0xFF, wUnit >> 8, nSide == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, TaLogic_GetWarnHideLvl_0014F9B0(nSide));
            if (ret < 0) {
                if (SzDuel_GetUnitMonsterCount(nSide) < 6) {
                    res = TaLogic014_GetSummonPiece(nSide, kind, &work, ret);
                    if (res < 0) {
                        return -1;
                    }
                    ctx->unk4 = res;
                    return 1;
                }
            } else {
                res = TaLogic014_GetSummonPiece(nSide, kind, &work, ret);
                if (res < 0) {
                    return -1;
                }
                ctx->unk4 = res;
                return 1;
            }
        }
    } else {
        ret = TaLogic_GetNearCard2(&work, wUnit & 0xFF, wUnit >> 8, nSide == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, TaLogic_GetWarnHideLvl_0014F9B0(nSide));
    }
    if (kind == 2) {
        TaLogic014_SetSpecialComboQue(nSide, ctx, &work);
        res = TaLogic014_GetSummonPiece(nSide, kind, &work, ret);
        if (res < 0) {
            return -1;
        }
        ctx->unk4 = res;
        return 1;
    }
    if (TaLogic014_GetSpellPlay(nSide, (u8 *)ctx, &work, work.unk3C) < 0) {
        return -1;
    }
    res = TaLogic014_GetSummonPiece(nSide, kind, &work, ret);
    if (res < 0) {
        return -1;
    }
    ctx->unk4 = res;
    return 1;
}

/* Whether side `nSide` should play from its hand this turn (and what, into `pInput`). */
s32 TaLogic014_IsHandPlay(s32 nSide, void *pInput) {
    extern s32 TaLogic_GetUnitNum();
    extern s32 SzView_SetCamera();
    s32 ids[8];
    s32 data[8];
    u8 type = (u8)TaLogic_GetUnitNum(nSide, 0);
    u8 attr = (u8)TaLogic_GetUnitNum(nSide, 1);

    if (pInput == NULL) {
        return -1;
    }
    TaHand_GetNextHand(nSide, ids);
    if (type == 5) {
        s32 result = TaLogic014_GetSpellPlay(nSide, (u8 *)data, pInput, 0x3E7);
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
        count = TaHand_GetNextHandNum(nSide);
        if (i < count) {
            p = ids;
            do {
                if ((TaHand_GetCardKind(*p) >> 5) == 0 && TaHand_IsCardSummon2(nSide, *p) == 1) {
                    SzDuel_InitCardInfo(pInput, ids[i]);
                    return 0;
                }
                p++;
                i++;
                count = TaHand_GetNextHandNum(nSide);
            } while (i < count);
        }
        return -1;
    }
    if (TaLogic014_GetSpecCardPlay(nSide, (u8 *)data, pInput, 0x354) >= 0) {
        if (TaLogic014_IsDoCerem(nSide, 0x354) == 1) {
            return 2;
        }
    }
    if (TaLogic014_IsActiveMode() == 1) {
        if (SzDuel_GetUnitSpellCount(nSide) == 0) {
            if (TaLogic014_GetSpecCardPlay(nSide, (u8 *)data, pInput, 0x2BD) >= 0) {
                return 2;
            }
        }
    }
    if (SzDuel_GetUnitMonsterCount(nSide) >= 4) {
        if (TaLogic014_GetSpecCardPlay(nSide, (u8 *)data, pInput, 0x2E6) >= 0) {
            return 2;
        }
    }
    {
        s32 *p;
        s32 i;
        s32 count;

        i = 0;
        count = TaHand_GetNextHandNum(nSide);
        if (i < count) {
            p = ids;
            do {
                if ((TaHand_GetCardKind(*p) >> 5) == 0 && TaHand_IsCardSummon2(nSide, *p) == 1) {
                    SzDuel_InitCardInfo(pInput, ids[i]);
                    return 0;
                }
                p++;
                i++;
                count = TaHand_GetNextHandNum(nSide);
            } while (i < count);
        }
    }
    {
        s32 result = TaLogic014_GetSpellPlay(nSide, (u8 *)data, pInput, 0x3E7);
        if (result >= 0) {
            return result;
        }
        return -1;
    }
}

/* Whether side `nSide` holds card `nCardNo` and can summon it (its slot into `bCombo`, the card into `pCardInfo`);
   returns its kind group or -1. */
s32 TaLogic014_GetSpecCardPlay(s32 nSide, void *bCombo, void *pCardInfo, s32 nCardNo) {
    s32 entries[8];
    s32 i;
    s32 *p;
    s32 key;

    TaHand_GetNextHand(nSide, entries);
    i = 0;
    if (0 < TaHand_GetNextHandNum(nSide)) {
        key = nCardNo & 0xFFFF;
        p = entries;
        do {
            if (key == *p && TaHand_IsCardSummon2(nSide, *p) == 1) {
                ((s8 *)bCombo)[6] = i;
                SzDuel_InitCardInfo(pCardInfo, entries[i]);
                return TaHand_GetCardKind(entries[i]) >> 5;
            }
            p++;
            i++;
        } while (i < TaHand_GetNextHandNum(nSide));
    }
    return -1;
}

/* Whether side `nSide` plays a magic or ritual card from its hand now (its slot into `bCombo`, the card into
   `pCardInfo`). */
s32 TaLogic014_GetSpellPlay(s32 nSide, u8 *bCombo, void *pCardInfo, s32 nMode) {
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


/* Fills hand combination `bCombo` for side `nSide`: the best fusion or equip chain, its card into `pCardInfo`. */
s32 TaLogic014_SetComboQue(s32 nSide, u8 *bCombo, void *pCardInfo) {
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
                    if (TaHand_IsCardSummon2(nSide, card) == 1) {
                        if (best < value) {
                            TaLogic_ConvEmptyCombo_0014D5C0(nSide, *node, entries);
                            TaLogic_CopyArray((u8 *)*node + 2, bCombo + 6);
                            SzDuel_InitCardInfo(pCardInfo, **node);
                            ((Sprite_0014D3E0 *)pCardInfo)->x = (value >> 16) - (((Sprite_0014D3E0 *)pCardInfo)->info->x & 0x1FFF);
                            ((Sprite_0014D3E0 *)pCardInfo)->y = (value & 0xFFFF) - (((Sprite_0014D3E0 *)pCardInfo)->info->y & 0x1FFF);
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
} Info_0014D5C0;

/* Fills an empty combination: the hand card side `nSide` can summon with the best attack plus defence. */
void TaLogic_ConvEmptyCombo_0014D5C0(s32 nSide, void *pCardInfo, s32 *pResult) {
    Info_0014D5C0 *info = pCardInfo;
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
                if (card != 0x3E7 && TaLogic014_IsRefuseEmptyCombo(card) == 0 && level >= TaHand_GetCardSummonCost2(card, nSide)) {
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

/* Whether this duelist keeps card `nCardNo` out of a summon (it is wanted for an equip). */
s32 TaLogic014_IsRefuseEmptyCombo(s32 nCardNo) {
    if (TaHand_GetCardKind(nCardNo) >> 5) {
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
} Obj1_0014D800;

typedef struct {
    u8 pad0[0x38];
    s16 f38;
    s16 f3A;
    u16 id;
} Obj2_0014D800;

/* Fills hand combination `bCombo` for side `nSide` with this duelist's special combination, its card into
   `pCardInfo`. */
s32 TaLogic014_SetSpecialComboQue(s32 nSide, void *bCombo, void *pCardInfo) {
    Obj1_0014D800 *o1 = bCombo;
    Obj2_0014D800 *o2 = pCardInfo;
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
            if (o2->id == list[i] && TaHand_IsCardSummon2(nSide, list[i]) == 1) {
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
                        o2->f38 += (s16)TaEnc_GetEncScore(list[i]);
                        o2->f3A += (s16)TaEnc_GetEncScore(list[i]);
                    }
                }
            }
        }
    }
    return 1;
}

/* Ta_GetSommonPiecePreference for this duelist. */
void TaLogic_GetSommonPiecePreference_0014DA30(s32 nSide, s32 nPr) {
    Ta_GetSommonPiecePreference(nSide, nPr);
}

typedef struct {
    u8 low : 4;
    u8 high : 4;
} Nibbles_0014DA40;

/* The first free line square, or -1. */
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

/* The square side `nSide` summons a card of kind `sKind` to. */
s32 TaLogic014_GetSummonPiece(s32 nSide, u8 sKind, void *pInput, s32 nMode) {
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

    if (pInput == NULL) {
        return -1;
    }
    p = buffer;
    initCount = 0;
    do {
        initCount++;
        p->low = p->high = 15;
        p++;
    } while (initCount < 12);

    kind = (type = (u8)(*((u8 *)pInput + 0x3E) >> 5));
    if (kind == 0 || SzDuel_Kind2Type(kind, type) == 2) {
        if (nMode >= 0) {
            bestScore = 0xFF;
            bestPosition = 0xFFFF;
            target = SzDuel_GetUnitLoc(nMode >> 8, nMode & 0xFF);
            i = 0;
            targetY = target >> 8;
            targetX = target & 0xFF;
            do {
                position = Ta_GetSommonPiecePreference(nSide, i);
                if (position >= 0) {
                    x = position & 0xFF;
                    y = position >> 8;
                    if (SzDuel_GetField(x, y) != 8 &&
                        (SzDuel_GetField(x, y) != 9 || Ta_IsVirus_Chk3(pInput, x, y) != 1) &&
                        SzDuel_GetMapUnit(x, y) == 0) {
                        if (TaLogic_IsUnitWin4((s32)pInput, nMode, TaLogic_GetWarnHideLvl_0014F9B0(nSide),
                                         targetX, targetY, 0) > 0) {
                            score = TaLogic_GetInvadeRoot2((s32)pInput, (s32)buffer, x, y,
                                                 targetX, targetY, nMode, 0, 3,
                                                 (u16)TaLogic_GetWarnHideLvl_0014F9B0(nSide));
                        } else {
                            score = TaLogic_GetRoot2((s32)pInput, (s32)buffer, x, y,
                                                 targetX, targetY, nMode, 3);
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
                nMode = Ta_GetSommonPiecePreference(nSide, i);
                if (nMode >= 0) {
                    x = nMode & 0xFF;
                    y = nMode >> 8;
                    if (SzDuel_GetField(x, y) != 8 &&
                        (SzDuel_GetField(x, y) != 9 || Ta_IsVirus_Chk3(pInput, x, y) != 1) &&
                        SzDuel_GetMapUnitID(x, y) < 0) {
                        target = find_0014DA40();
                        targetX = target & 0xFF;
                        targetY = target >> 8;
                        SzDuel_GetMapUnitID(targetX, targetY);
                        score = TaLogic_GetRoot2((s32)pInput, (s32)buffer, x, y,
                                             targetX, targetY, 0, 7);
                        if (score < limit && score >= 0) {
                            fallbackPosition = nMode;
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
            position = Ta_GetSommonPiecePreference(nSide, i);
            if (position >= 0) {
                x = position & 0xFF;
                y = position >> 8;
                if (SzDuel_GetField(x, y) != 8 &&
                    (SzDuel_GetField(x, y) != 9 || Ta_IsVirus_Chk3(pInput, x, y) != 1) &&
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


/* The task of a unit running from danger (task `pTask`): the safest square in reach, into `pInput` (`fFirst` = 1
   for the unit's first-choice task). */
s32 TaLogic_GetMinimumTask_RunMission_0014DF80(u16 *pTask, s32 nSide, void *pInput, u8 fFirst) {
    Output_0014DF80 *output = pInput;
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

    target = SzDuel_GetUnitLoc(*pTask >> 8, *pTask & 0xFF);
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

        initialScore = TaLogic_GetWarnHideLvl_0014F9B0(nSide);
        centerX = target & 0xFF;
        centerY = target >> 8;
        if (TaLogic_GetUnitWarning(centerX, centerY, *pTask, 3, initialScore, 0) == 0) {
            output->position = *pTask;
            output->action = 6;
            output->destination = target;
            output->result = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, output->destination, 1, 0);
            output->special = TaLogic_IsOpenUnit_0014F490(*pTask >> 8, *pTask & 0xFF, pTask);
            TaLogic_InitRogicControl(pTask, fFirst);
            return 0;
        }
        if ((range = GetMoveRev(SzDuel_GetUnit(*pTask >> 8, *pTask & 0xFF), centerX, centerY)) == 0) {
            output->position = *pTask;
            output->action = 6;
            output->destination = target;
            output->result = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, output->destination, 1, 0);
            output->special = TaLogic_IsOpenUnit_0014F490(*pTask >> 8, *pTask & 0xFF, pTask);
            TaLogic_InitRogicControl(pTask, fFirst);
            return 0;
        }
        if (SzDuel_GetUnitStatus(*pTask >> 8, *pTask & 0xFF, 4) != 0) {
            if ((SzDuel_GetUnitKind(*pTask >> 8, *pTask & 0xFF) >> 5) == 1 ||
                (SzDuel_GetUnitKind(*pTask >> 8, *pTask & 0xFF) >> 5) == 5) {
                SzDuel_SetUnitStatus(*pTask >> 8, *pTask & 0xFF, 0, 1);
                output->position = *pTask;
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
        if ((*pTask & 0xFF) == 0) {
            extra = (u8)TaLogic_IsAttackedNow(*pTask >> 8, *pTask & 0xFF, 0);
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
                if (TaLogic_IsRunPassRoot(*pTask >> 8, *pTask & 0xFF, centerX, centerY, x, y, pTask, extra) == 1) {
                    if (TaLogic_IsAttackedNow2(*pTask >> 8, *pTask & 0xFF, x, y, 0) == 0 || (u8)*pTask == 0) {
                        candidateScore = TaLogic_GetUnitWarning(x, y, *pTask, 3, (u16)TaLogic_GetWarnHideLvl_0014F9B0(nSide), 0);
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
            output->position = *pTask;
            output->action = 6;
            output->destination = best;
            if (best == target) {
                output->result = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, output->destination, 1, 0);
            } else {
                output->result = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, output->destination, 0, 0);
            }
            output->special = TaLogic_IsOpenUnit_0014F490(*pTask >> 8, *pTask & 0xFF, pTask);
        } else {
            output->position = *pTask;
            output->action = 6;
            output->destination = target;
            output->result = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, output->destination, 1, 0);
            output->special = TaLogic_IsOpenUnit_0014F490(*pTask >> 8, *pTask & 0xFF, pTask);
        }
        TaLogic_InitRogicControl(pTask, fFirst);
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

/* The task's target square: the second half-word when the second argument is 1, else the first. */
static inline u32 target_0014E550(void *src, u8 mode) {
    Input_0014E550 *input = src;
    if (mode == 1) {
        return (input->targets >> 16) & 0xFFFF;
    }
    return *(u16 *)&input->targets;
}

/* The larger of the two values. */
static inline s32 max_0014E550(s32 a, s32 b) {
    return a > b ? a : b;
}

/* The task of a unit attacking (task `pTask`): its path to the goal, into `pInput`; -1 when it has none (`fFirst`
   = 1 for the unit's first-choice task). */
s32 TaLogic_GetMinimumTask_AtkMission_0014E550(void *pTask, s32 nSide, void *pInput, u8 fFirst) {
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
    Input_0014E550 *input = pTask;
    Output_0014E550 *output = pInput;

    targetX = target_0014E550(input, fFirst);
    targetY = target_0014E550(input, fFirst);
    if (SzDuel_GetUnit(targetY >> 8, targetX & 0xFF) == 0) {
        TaLogic_InitRogicControl(input, 1);
        return -1;
    }
    oldFlag = TaLogic_IsOpenUnit_0014F490(input->position >> 8, input->position & 0xFF, input);
    sourcePosition = SzDuel_GetUnitLoc(input->position >> 8, input->position & 0xFF);
    targetX = target_0014E550(input, fFirst);
    targetY = target_0014E550(input, fFirst);
    destination = SzDuel_GetUnitLoc(targetY >> 8, targetX & 0xFF);
    p = points;
    i = 0;
    do {
        i++;
        p->x = p->y = 15;
        p++;
    } while (i < 12);
    {
        s32 unitInfo = SzDuel_GetUnit(input->position >> 8, input->position & 0xFF);
        sourceX = sourcePosition & 0xFF;
        sourceY = sourcePosition >> 8;
        if (GetMoveRev(unitInfo, sourceX, sourceY) == 0) {
            s32 cost;
            output->position = input->position;
            output->action = 6;
            output->destination = sourcePosition;
            cost = TaLogic_GetUnitWarning(sourceX, sourceY, nSide, 3, 1, (u8)TaLogic_GetWarnHideLvl_0014F9B0(nSide));
            if (cost >= SzDuel_GetUnitAP(input->position >> 8, input->position & 0xFF, 0)) {
                output->result = TaLogic_IsDefStyleUnit(input->position >> 8, input->position & 0xFF,
                                             output->destination, 1, 0);
            } else {
                output->result = TaLogic_IsDefStyleUnit(input->position >> 8, input->position & 0xFF,
                                             output->destination, 0, 0);
            }
            TaLogic_InitRogicControl(input, fFirst);
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

            identity = (u16)TaLogic_GetWarnHideLvl_0014F9B0(nSide);
            positionY = position >> 8;
            positionX = position & 0xFF;
            destinationX = destination & 0xFF;

            TaLogic_GetInvadeRoot(positionY, positionX, points,
                         sourceX, sourceY, destinationX, destination >>= 8,
                         target_0014E550(input, fFirst), 0, 30, identity);
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
                        cost = TaLogic_GetUnitWarning(candidate->x, candidate->y, nSide,
                                                3, 1, (u8)TaLogic_GetWarnHideLvl_0014F9B0(nSide));
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
                TaLogic_InitRogicControl(input, fFirst);
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
                    TaLogic_InitRogicControl(input, fFirst);
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


/* The task's target square: the second half-word when the second argument is 1, else the first. */
static inline u32 target_0014EB30(void *unit, s32 side) {
    return side == 1 ? (u32)(u16)(((Unit_0014EB30 *)unit)->target.packed >> 16) : (u32)((Unit_0014EB30 *)unit)->target.low;
}

/* The smaller of the two values. */
static inline u32 minY_0014EB30(void *unit, s32 side, u8 coord) {
    return coord < (target_0014EB30(unit, side) >> 8) ? coord : (target_0014EB30(unit, side) >> 8);
}

/* The larger of the two values. */
static inline u32 maxY_0014EB30(void *unit, s32 side, u8 coord) {
    return (target_0014EB30(unit, side) >> 8) < coord ? coord : (target_0014EB30(unit, side) >> 8);
}

/* The smaller of the two values. */
static inline u32 minX_0014EB30(void *unit, s32 side, u8 coord) {
    return coord < (target_0014EB30(unit, side) & 0xFF) ? coord : (target_0014EB30(unit, side) & 0xFF);
}

/* The larger of the two values. */
static inline u32 maxX_0014EB30(void *unit, s32 side, u8 coord) {
    return (target_0014EB30(unit, side) & 0xFF) < coord ? coord : (target_0014EB30(unit, side) & 0xFF);
}

/* The task of a unit moving to its goal (task `pTask`), into `pInput` (`fFirst` = 1 for the unit's first-choice
   task). */
s32 TaLogic_GetMinimumTask_MoveMission_0014EB30(void *pTask, s32 nSide, void *pInput, u8 fFirst, u8 nKind) {
    extern s32 TaLogic_IsOpenUnit_0014F490();
    extern s32 TaLogic_GetUnitWarning();
    extern void TaLogic_GetRoot();
    extern s32 TaLogic_IsDefStyleUnit(s32, s32, s32, u8, s32);
    Coord_0014EB30 coords[12];
    s32 initial;
    s32 cell;
    s32 count;

    initial = SzDuel_GetUnitLoc(((Unit_0014EB30 *)pTask)->position >> 8, ((Unit_0014EB30 *)pTask)->position & 0xFF);
    {
    s32 bestScore;
    s32 best;
    s32 side = fFirst;
    Coord_0014EB30 *candidate;
    s32 index;
    if (target_0014EB30(pTask, side) == 0xFFFF) {
        if (initial == target_0014EB30(pTask, side)) {
            ((Output_0014EB30 *)pInput)->position = ((Unit_0014EB30 *)pTask)->position;
            ((Output_0014EB30 *)pInput)->kind = 6;
            ((Output_0014EB30 *)pInput)->target = initial;
            ((Output_0014EB30 *)pInput)->flag = TaLogic_IsDefStyleUnit(((Unit_0014EB30 *)pTask)->position >> 8, ((Unit_0014EB30 *)pTask)->position & 0xFF, ((Output_0014EB30 *)pInput)->target, nKind, 0);
            ((Output_0014EB30 *)pInput)->value = TaLogic_IsOpenUnit_0014F490(((Unit_0014EB30 *)pTask)->position >> 8, ((Unit_0014EB30 *)pTask)->position & 0xFF, pTask);
            TaLogic_InitRogicControl(pTask, fFirst);
            return 0;
        }
    }

    if (SzDuel_GetUnitStatus(((Unit_0014EB30 *)pTask)->position >> 8,
                      ((Unit_0014EB30 *)pTask)->position & 0xFF, 4) != 0) {
        if ((SzDuel_GetUnitKind(((Unit_0014EB30 *)pTask)->position >> 8,
                          ((Unit_0014EB30 *)pTask)->position & 0xFF) >> 5) == 1 ||
            (SzDuel_GetUnitKind(((Unit_0014EB30 *)pTask)->position >> 8,
                          ((Unit_0014EB30 *)pTask)->position & 0xFF) >> 5) == 5) {
            SzDuel_SetUnitStatus(((Unit_0014EB30 *)pTask)->position >> 8,
                          ((Unit_0014EB30 *)pTask)->position & 0xFF, 0, 1);
            ((Output_0014EB30 *)pInput)->position = ((Unit_0014EB30 *)pTask)->position;
            ((Output_0014EB30 *)pInput)->kind = 0xE;
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

    cell = SzDuel_GetMapUnitID(target_0014EB30(pTask, side) & 0xFF, ((u32)target_0014EB30(pTask, side)) >> 8);
    if (cell < 0) {
        cell = 0xFFFF;
    }
    TaLogic_GetRoot(((Unit_0014EB30 *)pTask)->position >> 8, ((Unit_0014EB30 *)pTask)->position & 0xFF,
                 coords, initial & 0xFF, initial >> 8, target_0014EB30(pTask, side) & 0xFF,
                 ((u32)target_0014EB30(pTask, side)) >> 8, (u16)cell, 7);
    count = TaLogic_GetMinGoalCount((u8 *)coords);
    {
        if (count > 0) {
        best = 0xFF;
        bestScore = 0xFFFF;
        for (index = 0; index < count; index++) {
                if (SzDuel_GetMapUnit(candidate->x, candidate->y) == 0) {
                    s32 score = TaLogic_GetUnitWarning(candidate->x, candidate->y, nSide, 3, 1, (u8)TaLogic_GetWarnHideLvl_0014F9B0(nSide));
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
                        bestMinY = minY_0014EB30(pTask, side, bestY);
                        bestMaxY = maxY_0014EB30(pTask, side, bestY);
                        bestX = (&coords[best])->x;
                        bestMinX = minX_0014EB30(pTask, side, bestX);
                        bestMaxX = maxX_0014EB30(pTask, side, bestX);
                        currentY = (u8)candidate->y;
                        currentMinY = minY_0014EB30(pTask, side, currentY);
                        currentMaxY = maxY_0014EB30(pTask, side, currentY);
                        currentX = candidate->x;
                        currentMinX = minX_0014EB30(pTask, side, currentX);
                        currentMaxX = maxX_0014EB30(pTask, side, currentX);
                        if ((currentMaxX - currentMinX) + (currentMaxY - currentMinY) < (bestMaxX - bestMinX) + (bestMaxY - bestMinY)) {
                            bestScore = score;
                            best = index;
                        }
                    }
                }
            candidate++;
        }
    } else {
        ((Output_0014EB30 *)pInput)->position = ((Unit_0014EB30 *)pTask)->position;
            ((Output_0014EB30 *)pInput)->kind = 6;
            ((Output_0014EB30 *)pInput)->target = initial;
            ((Output_0014EB30 *)pInput)->flag = TaLogic_IsDefStyleUnit(((Unit_0014EB30 *)pTask)->position >> 8, ((Unit_0014EB30 *)pTask)->position & 0xFF, ((Output_0014EB30 *)pInput)->target, nKind, 0);
            ((Output_0014EB30 *)pInput)->value = TaLogic_IsOpenUnit_0014F490(((Unit_0014EB30 *)pTask)->position >> 8, ((Unit_0014EB30 *)pTask)->position & 0xFF, pTask);
        TaLogic_InitRogicControl(pTask, fFirst);
        return 0;
    }

        if (best != 0xFF) {
            ((Output_0014EB30 *)pInput)->position = ((Unit_0014EB30 *)pTask)->position;
            ((Output_0014EB30 *)pInput)->kind = 6;
            ((Output_0014EB30 *)pInput)->target = (coords[best].y << 8) | coords[best].x;
            ((Output_0014EB30 *)pInput)->flag = TaLogic_IsDefStyleUnit(((Unit_0014EB30 *)pTask)->position >> 8, ((Unit_0014EB30 *)pTask)->position & 0xFF, ((Output_0014EB30 *)pInput)->target, nKind, 0);
            ((Output_0014EB30 *)pInput)->value = TaLogic_IsOpenUnit_0014F490(((Unit_0014EB30 *)pTask)->position >> 8, ((Unit_0014EB30 *)pTask)->position & 0xFF, pTask);
        } else {
            ((Output_0014EB30 *)pInput)->position = ((Unit_0014EB30 *)pTask)->position;
            ((Output_0014EB30 *)pInput)->kind = 6;
            ((Output_0014EB30 *)pInput)->target = initial;
            ((Output_0014EB30 *)pInput)->flag = TaLogic_IsDefStyleUnit(((Unit_0014EB30 *)pTask)->position >> 8, ((Unit_0014EB30 *)pTask)->position & 0xFF, ((Output_0014EB30 *)pInput)->target, nKind, 0);
            ((Output_0014EB30 *)pInput)->value = TaLogic_IsOpenUnit_0014F490(((Unit_0014EB30 *)pTask)->position >> 8, ((Unit_0014EB30 *)pTask)->position & 0xFF, pTask);
        }
        TaLogic_InitRogicControl(pTask, fFirst);
    }
    }
    return 0;
}

/* Line square `index` (0..2) for side `id`, or -1. */
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

/* The first free line square, or -1. */
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

/* Whether this duelist plays in its attacking mode this turn. */
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
/* The first free line square, or -1. */
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

/* Whether this duelist opens (turns face up) unit (nSide, nID) now: 0 no, 1 or 2 by its kind. */
int TaLogic_IsOpenUnit_0014F490(int nSide, int nID)
{
    int kind;
    int pos;
    int side;
    unsigned *p;
    int r;
    kind = func_001E1030_b(nSide, nID);
    pos = SzDuel_GetUnitLoc(nSide, nID);
    side = Ta_IsUnitControl(nSide, nID);
    p = func_001E0B70_b(nSide, nID, 0);
    if (SzDuel_GetUnitStatus(nSide, nID, 4)) {
        return 0;
    }
    switch (SzDuel_GetUnitKind(nSide, nID) >> 5) {
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
        if (func_0027D830_b(nSide, nID, 0, 0, 6, 0) == 5) {
            return 2;
        }
        if (TaLogic014_IsDoCerem(Ta_IsUnitControl(nSide, nID), kind) == 1) {
            if (SzDuel_GetField(pos & 0xFF, pos >> 8) != 9) {
                return 1;
            }
        }
        break;
    case 1:
        if (func_0027D830_b(nSide, nID, 0, 0, 6, 0) == 5) {
            return 2;
        }
        if (p == 0) {
            return 2;
        }
        switch (*p >> 8) {
        case 13:
            return 1;
        case 2:
            r = TaLogic_GetLandChange(SzDuel_GetUnit(nSide, nID), pos & 0xFF, pos >> 8, 4, 9, 2);
            if (r >= 0 && r == pos) {
                return 1;
            }
            break;
        case 4:
            if ((spot_find() < 0 ? 1 : 0) == 1) {
                if (SzDuel_GetUnitSpellCount(nSide) == 0) {
                    return 1;
                }
            }
            break;
        case 18:
            if (SzDuel_GetUnitMonsterCount(nSide) >= 4) {
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

/* The larger of the two values. */
static inline s32 max_0014F7C0(s32 a, s32 b) {
    if (b < a) {
        return a;
    }
    return b;
}

/* Whether unit (nSide, nID) may open while moving from (nX, nZ) to the square next to it, (gX, gZ). */
s32 TaLogic014_IsOpenMoveUnit(s32 nSide, s32 nID, s32 nX, s32 nZ, s32 gX, s32 gZ) {
    s32 min_y;
    s32 min_x;

    min_y = nZ < gZ ? nZ : gZ;
    gZ = max_0014F7C0(nZ, gZ);
    min_x = nX < gX ? nX : gX;
    gX = max_0014F7C0(nX, gX);
    if ((gX - min_x) + (gZ - min_y) != 2) {
        return 0;
    }
    if (SzDuel_GetUnit(nSide, nID) == 0) {
        return 0;
    }
    if (SzDuel_GetUnitStatus(nSide, nID, 0) == 0) {
        if (CheckLandAgreement2(SzDuel_GetField(nX, nZ), nSide, nID) != 1) {
            return 0;
        }
        return 1;
    }
    return 0;
}

/* Whether side `nSide` can play ritual card `nCardNo` now (it has the units to give up). */
s32 TaLogic014_IsDoCerem(s32 nSide, s32 nCardNo) {
    s32 sp50[4];
    s32 i;
    s32 mask;
    s32 low;
    s32 high;
    s32 cell;
    s32 value;

    Ta_GetCeremSacrifice(sp50, *(s32 *)((u8 *)TaHand_GetCardEffect(nCardNo, 0) + 4));
    if ((mask = Ta_GetSacrificeUnit(sp50, nSide)) < 0) {
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

/* How careful this duelist is about hidden cards (by its life points and monster count). */
s32 TaLogic_GetWarnHideLvl_0014F9B0(s32 nSide) {
    if (SzDuel_GetLP(nSide) > 0x4B0) {
        if (SzDuel_GetUnitMonsterCount(nSide) >= 5) {
            return 0x2EE;
        } else {
            return 0x5DC;
        }
    } else {
        return 0x960;
    }
}

/* Whether side `nSide` should use the standing effect of card `nCardNo` now (enough targets in range). */
s32 TaLogic014_IsUnitNaturalEffectUse(s32 nSide, s32 nCardNo) {
    s32 index;
    u8 count;
    s32 mask;
    s32 entry;

    count = 0;
    switch (nCardNo) {
    case 0x264:
        if (Ta_GetUnitNumFrom22bitFlagList(SearchUnitByRange(0, 0, nSide, 1, 0x10, 0xE)) <= 3) {
            break;
        }
        return 1;
    case 0x227:
        if (Ta_GetUnitNumFrom22bitFlagList(SearchUnitByRange(0, 0, nSide, 1, 0xF, 0xE)) > 0) {
            return 0;
        }
        mask = SearchUnitByRange(0, 0, nSide, 2, 0xF, 0xE);
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

/* This computer duelist's controller (one entry of g_aLogFunc): the buttons it presses this frame. With an empty
   input queue it plans its next task and turns it into buttons, then plays the queue back one button per frame;
   after 600 frames it gives up the turn (0x20, then 0x800). */
s32 func_0014FB70(s32 wCursorPos, void *pCtl) {
    Req_0014FB70 req;
    Work_0014FB70 *w;
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
        if (TaLogic_GetMinimumTask_0014B900(w, &req, wCursorPos) == 0) {
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
/* Runs the run-away task for `unit` when it is face down; returns 1 if it did, else `done`. */
static inline int CRun_val(struct DotrFinderUnit *unit, int side, struct DotrFinderTask *task, int first, int done)
{
    if (SzDuel_GetUnitStatus(unit->wUnit >> 8, unit->wUnit & 0xff, 0) == 0) {
        func_00152100_b(unit, side, task, first);
        done = 1;
    }
    return done;
}
/* Runs the move task for `unit` when it is face down; returns 1 if it did, else `done`. */
static inline int CMove_val(struct DotrFinderUnit *unit, int side, struct DotrFinderTask *task, int first, int e, int done)
{
    if (SzDuel_GetUnitStatus(unit->wUnit >> 8, unit->wUnit & 0xff, 0) == 0) {
        func_00152CD0_b(unit, side, task, first, e);
        done = 1;
    }
    return done;
}
/* Runs the equip task for `unit`; returns 1. */
static inline int CEnc_val(struct DotrFinderUnit *unit, int side, struct DotrFinderTask *task, int first, int done)
{
    func_0027D020_b(unit, side, task, first, 0, TaLogic_GetWarnHideLvl_00153ED0(side), 5, 1);
    done = 1;
    return done;
}
/* Runs the run-away task for `unit` when it is face down (sets `*pd`). */
static inline void CRun_void(struct DotrFinderUnit *unit, int side, struct DotrFinderTask *task, int first, int *pd)
{
    if (SzDuel_GetUnitStatus(unit->wUnit >> 8, unit->wUnit & 0xff, 0) == 0) {
        func_00152100_b(unit, side, task, first);
        *pd = 1;
    }
}
/* Runs the move task for `unit` when it is face down (sets `*pd`). */
static inline void CMove_void(struct DotrFinderUnit *unit, int side, struct DotrFinderTask *task, int first, int e, int *pd)
{
    if (SzDuel_GetUnitStatus(unit->wUnit >> 8, unit->wUnit & 0xff, 0) == 0) {
        func_00152CD0_b(unit, side, task, first, e);
        *pd = 1;
    }
}
/* Runs the equip task for `unit` (sets `*pd`). */
static inline void CEnc_void(struct DotrFinderUnit *unit, int side, struct DotrFinderTask *task, int first, int *pd)
{
    func_0027D020_b(unit, side, task, first, 0, TaLogic_GetWarnHideLvl_00153ED0(side), 5, 1);
    *pd = 1;
}

/* This duelist's move: picks the next unit to act, gives it a task and turns that into input `pInput`; returns 1
   when it set one. */
int TaLogic_GetMinimumTask_0014FD40(void *pCtl, void *pInput, int wCursorPos)
{
    struct DotrFinderUnit * list = pCtl;
    struct DotrFinderTask * task = pInput;
    int side = SzDuel_GetTurnOwner();
    int done = 0;
    int r;
    int idx;

    (void)wCursorPos;
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


/* Gives a unit of this duelist its order for this turn (attack, run, move, summon, guard). */
s32 TaLogic_CommandUnit_00150270(void *pCtl) {
    Unit_00150270 *unit = pCtl;
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

/* The next unit of side `nSide` to act: first one that can attack now, then the others by task. */
s32 TaLogic_GetNextActiveUnit_00150470(u16 *pCtl, s32 nSide, s32 pInput) {
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
    TaLogic_CommandUnit_00150270(pCtl + idx * 8);
    if (((pCtl[idx * 8 + 2] >> 8) & 0xFF) == 10) {
        if (SzDuel_InqHandPhase(nSide) == 1 && TaLogic_GetMinimumTask_Summon_00150C40(pos, nSide, pInput) >= 0) {
            return pos | 0x10000;
        }
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_GetUnitStatus(nSide, 0, 0) == 0) {
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_InqHandPhase(nSide) == 1 && TaLogic_GetMinimumTask_Summon_00150C40(pos, nSide, pInput) >= 0) {
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

/* Orders a fighting unit (task `pTask`): straight at its goal when the path is open, else the nearest enemy it can
   beat. */
void TaLogic015_CommandBtlUnit(void *pTask)
{
    struct DotrTryOrder * order = pTask;
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

/* TaLogic_GetNearUnit with this duelist's view and strength settings. */
void TaLogic015_GetNearUnit(s32 pTask, s32 pTree, s32 pVarInfo, s32 nX, s32 nZ, s32 eSide, s32 bDist, s32 WarnLvl,
                   s32 nUnitLst, u16 wUnitNum, s32 wSize, s32 wNodeCount, u8 bChase, s32 wIgnoreLst) {
    TaLogic_GetNearUnit(pTask, pTree, pVarInfo, nX, nZ, eSide, bDist, WarnLvl, nUnitLst, wUnitNum, wSize, wNodeCount, bChase, 0, 2000, wIgnoreLst);
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

/* The summon task for side `nSide`: which hand cards to play and where, into `pInput`; -1 when it plays none. */
s32 TaLogic_GetMinimumTask_Summon_00150C40(s32 wUnit, s32 nSide, s32 pInput) {
    extern s32 TaLogic_GetUnitNum(s32, s32);
    Card_00150C40 buf;
    s32 res;
    s32 type;
    Act_00150C40 *act = (Act_00150C40 *)pInput;
    s32 card;
    s32 r;

    act->card = wUnit;
    if (SzDuel_InqHandPhase(nSide) == 0) {
        return -1;
    }
    if (TaLogic_GetUnitNum(nSide, 0) == 5 && TaLogic_GetUnitNum(nSide, 1) == 5) {
        return -1;
    }
    type = TaLogic015_IsHandPlay(nSide, &buf);
    if (type < 0) {
        return -1;
    }
    act->f2 = 10;
    act->fC = 0;
    card = SzDuel_GetUnitLoc(wUnit >> 8, wUnit & 0xFF);
    if (type == 0) {
        if (TaLogic015_SetComboQue(nSide, act, &buf) >= 0) {
            res = TaLogic_GetNearCard2(&buf, card & 0xFF, card >> 8, nSide == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, TaLogic_GetWarnHideLvl_00153ED0(nSide));
            if (res < 0) {
                if (SzDuel_GetUnitMonsterCount(nSide) < 6) {
                    r = TaLogic015_GetSummonPiece(nSide, type, &buf, res);
                    if (r < 0) {
                        return -1;
                    }
                    act->f4 = r;
                    return 1;
                }
            } else {
                r = TaLogic015_GetSummonPiece(nSide, type, &buf, res);
                if (r < 0) {
                    return -1;
                }
                act->f4 = r;
                return 1;
            }
        }
    } else {
        res = TaLogic_GetNearCard2(&buf, card & 0xFF, card >> 8, nSide == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, TaLogic_GetWarnHideLvl_00153ED0(nSide));
    }
    if (type == 2) {
        TaLogic015_SetSpecialComboQue(nSide, act, &buf);
        r = TaLogic015_GetSummonPiece(nSide, type, &buf, res);
        if (r < 0) {
            return -1;
        }
        act->f4 = r;
        return 1;
    } else if (type == 3) {
        TaLogic015_GetSpecialComboPlay(nSide, act, &buf);
        r = TaLogic015_GetSummonPiece(nSide, type, &buf, res);
        if (r < 0) {
            return -1;
        }
        act->f4 = r;
        return 1;
    } else {
        if (TaLogic015_GetSpellPlay(nSide, (u8 *)act, &buf, buf.id) < 0) {
            return -1;
        }
        r = TaLogic015_GetSummonPiece(nSide, type, &buf, res);
        if (r < 0) {
            return -1;
        }
        act->f4 = r;
        return 1;
    }
}

/* Whether side `nSide` should play from its hand this turn (and what, into `pInput`). */
s32 TaLogic015_IsHandPlay(s32 nSide, void *pInput) {
    extern s32 TaLogic_GetUnitNum();
    s32 ids[8];
    s32 data[8];
    u8 type = (u8)TaLogic_GetUnitNum(nSide, 0);
    u8 attr = (u8)TaLogic_GetUnitNum(nSide, 1);

    if (pInput == NULL) {
        return -1;
    }
    TaHand_GetNextHand(nSide, ids);
    if (type == 5) {
        s32 result = TaLogic015_GetSpellPlay(nSide, (u8 *)data, pInput, 0x3E7);
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
        count = TaHand_GetNextHandNum(nSide);
        if (i < count) {
            p = ids;
            do {
                if ((TaHand_GetCardKind(*p) >> 5) == 0 && TaHand_IsCardSummon2(nSide, *p) == 1) {
                    SzDuel_InitCardInfo(pInput, ids[i]);
                    return 0;
                }
                p++;
                i++;
                count = TaHand_GetNextHandNum(nSide);
            } while (i < count);
        }
        return -1;
    }
    if (TaLogic015_GetSpecialComboPlay(nSide, (u8 *)data, pInput) == 1) {
        return 3;
    }
    if (TaLogic015_IsUseRevive(nSide) == 1) {
        s32 result = TaLogic015_GetSpecCardPlay(nSide, (u8 *)data, pInput, 0x2AE);
        if (result >= 0) {
            return 2;
        }
    }
    {
        s32 *p;
        s32 i;
        s32 count;

        i = 0;
        count = TaHand_GetNextHandNum(nSide);
        if (i < count) {
            p = ids;
            do {
                if ((TaHand_GetCardKind(*p) >> 5) == 0 && TaHand_IsCardSummon2(nSide, *p) == 1) {
                    SzDuel_InitCardInfo(pInput, ids[i]);
                    return 0;
                }
                p++;
                i++;
                count = TaHand_GetNextHandNum(nSide);
            } while (i < count);
        }
    }
    {
        s32 result = TaLogic015_GetSpellPlay(nSide, (u8 *)data, pInput, 0x3E7);
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


/* Whether side `nSide` can play this duelist's special combination now. */
s32 TaLogic015_GetSpecialComboPlay(s32 nSide, void *bCombo, void *pCardInfo) {
    Obj2_00151170 *o2 = pCardInfo;
    Obj1_00151170 *o1 = bCombo;
    s32 list[8];
    s32 i;
    s32 found;
    u8 k;

    TaHand_GetNextHand(nSide, list);
    for (i = 0, found = 0; i < TaHand_GetNextHandNum(nSide); i++) {
        if (list[i] == 0x31F) {
            found = 1;
            o1->slot[0] = i;
        }
    }
    if (found == 0) {
        return -1;
    }
    for (i = 0, found = 0; i < TaHand_GetNextHandNum(nSide); i++) {
        if (list[i] == 7 && TaHand_IsCardSummon2(nSide, list[i]) == 1) {
            o1->slot[1] = i;
            found = 1;
        }
    }
    if (found == 0) {
        return -1;
    }
    k = 2;
    SzDuel_InitCardInfo(o2, 0x1F5);
    for (i = 0; i < TaHand_GetNextHandNum(nSide); i++) {
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

/* Whether side `nSide` holds card `nCardNo` and can summon it (its slot into `bCombo`, the card into `pCardInfo`);
   returns its kind group or -1. */
s32 TaLogic015_GetSpecCardPlay(s32 nSide, void *bCombo, void *pCardInfo, s32 nCardNo) {
    s32 i;
    s32 ids[8];

    TaHand_GetNextHand(nSide, ids);
    for (i = 0; i < TaHand_GetNextHandNum(nSide); i++) {
        if (((nCardNo & 0xFFFF) == ids[i]) &&
            (TaHand_IsCardSummon2(nSide, ids[i]) == 1)) {
            ((u8 *)bCombo)[6] = i;
            SzDuel_InitCardInfo(pCardInfo, ids[i]);
            return TaHand_GetCardKind(ids[i]) >> 5;
        }
    }
    return -1;
}

/* Whether side `nSide` plays a magic or ritual card from its hand now (its slot into `bCombo`, the card into
   `pCardInfo`). */
s32 TaLogic015_GetSpellPlay(s32 nSide, u8 *bCombo, void *pCardInfo, s32 nMode) {
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


/* Fills hand combination `bCombo` for side `nSide`: the best fusion or equip chain, its card into `pCardInfo`. */
s32 TaLogic015_SetComboQue(s32 nSide, u8 *bCombo, void *pCardInfo) {
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
                if ((TaHand_GetCardKind(card) >> 5) == 0 && TaHand_IsCardSummon2(nSide, card) == 1) {
                    *node = TaLogic_GetFusionTree(nSide, (struct TreeTag *)*node, i & 0xFF, card & 0xFFFF, 0, (u16 *)&a, (u16 *)&b);
                    *node = TaLogic_GetFusionRes(*node);
                    value = TaLogic_GetEnchantQue(nSide, *node, 0, 0);
                    if (best < value) {
                        SzDuel_InitCardInfo(pCardInfo, **node);
                        ((Sprite_001516A0 *)pCardInfo)->x = (value >> 16) - (((Sprite_001516A0 *)pCardInfo)->info->x & 0x1FFF);
                        ((Sprite_001516A0 *)pCardInfo)->y = (value & 0xFFFF) - (((Sprite_001516A0 *)pCardInfo)->info->y & 0x1FFF);
                        TaLogic_ConvEmptyCombo_00151880(nSide, *node, entries);
                        TaLogic_CopyArray((u8 *)*node + 2, bCombo + 6);
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
            } while (i < TaHand_GetNextHandNum(nSide));
        }
        return top;
    }
}

typedef struct {
    u16 id;
    u8 values[5];
} Info_00151880;

/* Fills an empty combination: the hand card side `nSide` can summon with the best attack plus defence. */
void TaLogic_ConvEmptyCombo_00151880(s32 nSide, void *pCardInfo, s32 *pResult) {
    Info_00151880 *info = pCardInfo;
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
                if (card != 0x3E7 && TaLogic015_IsRefuseEmptyCombo(card) == 0 && level >= TaHand_GetCardSummonCost2(card, nSide)) {
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

/* Whether this duelist keeps card `nCardNo` out of a summon (it is wanted for an equip). */
s32 TaLogic015_IsRefuseEmptyCombo(s32 nCardNo) {
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
} Obj1_00151AC0;

typedef struct {
    u8 pad0[0x38];
    s16 f38;
    s16 f3A;
    u16 id;
} Obj2_00151AC0;

/* Fills hand combination `bCombo` for side `nSide` with this duelist's special combination, its card into
   `pCardInfo`. */
s32 TaLogic015_SetSpecialComboQue(s32 nSide, void *bCombo, void *pCardInfo) {
    Obj1_00151AC0 *o1 = bCombo;
    Obj2_00151AC0 *o2 = pCardInfo;
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
            if (o2->id == list[i] && TaHand_IsCardSummon2(nSide, list[i]) == 1) {
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

/* The square side `nSide` summons a card of kind `sKind` to. */
s32 TaLogic015_GetSummonPiece(s32 nSide, u8 sKind, void *pInput, s32 nMode) {
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

    if (pInput == NULL) {
        return -1;
    }
    cell = cells;
    j = 0;
    do {
        cell->low = cell->high = 15;
        j++;
        cell++;
    } while (j < 12);
    kind = (type = (u8)(*((u8 *)pInput + 0x3E) >> 5));
    if (kind == 0 || SzDuel_Kind2Type(kind, type) == 2) {
        if (nMode >= 0) {
            s32 position;
            s32 y;
            s32 x;
            s32 i;
            s32 score;
            s32 target;
            bestScore = 255;
            bestPosition = 65535;
            target = SzDuel_GetUnitLoc(nMode >> 8, nMode & 255);
            i = 0;
            targetY = target >> 8;
            targetX = target & 255;
            do {
                position = Ta_GetSommonPiecePreference(nSide, i);
                if (position >= 0) {
                    x = position & 255;
                    y = position >> 8;
                    if (SzDuel_GetField(x, y) != 8 &&
                        (SzDuel_GetField(x, y) != 9 || Ta_IsVirus_Chk3(pInput, x, y) != 1) &&
                        SzDuel_GetMapUnit(x, y) == 0) {
                        if (TaLogic_IsUnitWin4(pInput, nMode, TaLogic_GetWarnHideLvl_00153ED0(nSide), targetX, targetY, 0) > 0) {
                            score = TaLogic_GetInvadeRoot2(pInput, cells, x, y, targetX, targetY,
                                                nMode, 0, 3, (u16)TaLogic_GetWarnHideLvl_00153ED0(nSide));
                        } else {
                            score = TaLogic_GetRoot2((s32)pInput, (s32)cells, x, y, targetX, targetY, nMode, 3);
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
        SzDuel_GetUnitLoc(nMode >> 8, nMode & 255);
        i = 0;
        do {
            position = Ta_GetSommonPiecePreference(nSide, i);
            if (position >= 0) {
                x = position & 255;
                y = position >> 8;
                if (SzDuel_GetField(x, y) != 8 &&
                    (SzDuel_GetField(x, y) != 9 || Ta_IsVirus_Chk3(pInput, x, y) != 1) &&
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
            position = Ta_GetSommonPiecePreference(nSide, i);
            if (position >= 0) {
                x = position & 255;
                y = position >> 8;
                if (SzDuel_GetField(x, y) != 8 &&
                    (SzDuel_GetField(x, y) != 9 || Ta_IsVirus_Chk3(pInput, x, y) != 1) &&
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


/* The task of a unit running from danger (task `pTask`): the safest square in reach, into `pInput` (`fFirst` = 1
   for the unit's first-choice task). */
s32 TaLogic_GetMinimumTask_RunMission_00152100(u16 *pTask, s32 nSide, void *pInput, u8 fFirst) {
    Output_00152100 *output = pInput;
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

    target = SzDuel_GetUnitLoc(*pTask >> 8, *pTask & 0xFF);
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

        initialScore = TaLogic_GetWarnHideLvl_00153ED0(nSide);
        centerX = target & 0xFF;
        centerY = target >> 8;
        if (TaLogic_GetUnitWarning(centerX, centerY, *pTask, 3, initialScore, 0) == 0) {
            output->position = *pTask;
            output->action = 6;
            output->destination = target;
            output->result = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, output->destination, 1, 0);
            output->special = TaLogic_IsOpenUnit_00153AE0(*pTask >> 8, *pTask & 0xFF, pTask);
            TaLogic_InitRogicControl(pTask, fFirst);
            return 0;
        }
        if ((range = GetMoveRev(SzDuel_GetUnit(*pTask >> 8, *pTask & 0xFF), centerX, centerY)) == 0) {
            output->position = *pTask;
            output->action = 6;
            output->destination = target;
            output->result = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, output->destination, 1, 0);
            output->special = TaLogic_IsOpenUnit_00153AE0(*pTask >> 8, *pTask & 0xFF, pTask);
            TaLogic_InitRogicControl(pTask, fFirst);
            return 0;
        }
        if (SzDuel_GetUnitStatus(*pTask >> 8, *pTask & 0xFF, 4) != 0) {
            if ((SzDuel_GetUnitKind(*pTask >> 8, *pTask & 0xFF) >> 5) == 1 ||
                (SzDuel_GetUnitKind(*pTask >> 8, *pTask & 0xFF) >> 5) == 5) {
                SzDuel_SetUnitStatus(*pTask >> 8, *pTask & 0xFF, 0, 1);
                output->position = *pTask;
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
        if ((*pTask & 0xFF) == 0) {
            extra = (u8)TaLogic_IsAttackedNow(*pTask >> 8, *pTask & 0xFF, 0);
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
                if (TaLogic_IsRunPassRoot(*pTask >> 8, *pTask & 0xFF, centerX, centerY, x, y, pTask, extra) == 1) {
                    if (TaLogic_IsAttackedNow2(*pTask >> 8, *pTask & 0xFF, x, y, 0) == 0 || (u8)*pTask == 0) {
                        candidateScore = TaLogic_GetUnitWarning(x, y, *pTask, 3, (u16)TaLogic_GetWarnHideLvl_00153ED0(nSide), 0);
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
            output->position = *pTask;
            output->action = 6;
            output->destination = best;
            if (best == target) {
                output->result = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, output->destination, 1, 0);
            } else {
                output->result = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, output->destination, 0, 0);
            }
            output->special = TaLogic_IsOpenUnit_00153AE0(*pTask >> 8, *pTask & 0xFF, pTask);
        } else {
            output->position = *pTask;
            output->action = 6;
            output->destination = target;
            output->result = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, output->destination, 1, 0);
            output->special = TaLogic_IsOpenUnit_00153AE0(*pTask >> 8, *pTask & 0xFF, pTask);
        }
        TaLogic_InitRogicControl(pTask, fFirst);
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

/* The task's target square: the second half-word when the second argument is 1, else the first. */
static inline u32 destination_001526D0(void *src, u8 mode) {
    if (mode == 1) {
        return (u16)(((Input_001526D0 *)src)->destinations >> 16);
    }
    return *(u16 *)((u8 *)src + 8);
}


/* The task of a unit attacking (task `pTask`): its path to the goal, into `pInput`; -1 when it has none (`fFirst`
   = 1 for the unit's first-choice task). */
s32 TaLogic_GetMinimumTask_AtkMission_001526D0(void *pTask, s32 nSide, u16 *pInput, u8 fFirst) {
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
    destinationX = destination_001526D0(pTask, fFirst);
    destinationY = destination_001526D0(pTask, fFirst);
    if (SzDuel_GetUnit(destinationY >> 8, destinationX & 0xFF) == 0) {
        TaLogic_InitRogicControl(pTask, 1);
        return -1;
    }
    state = TaLogic_IsOpenUnit_00153AE0(((Input_001526D0 *)pTask)->position >> 8,
                         ((Input_001526D0 *)pTask)->position & 0xFF, pTask);
    current = SzDuel_GetUnitLoc(((Input_001526D0 *)pTask)->position >> 8,
                           ((Input_001526D0 *)pTask)->position & 0xFF);
    destinationX = destination_001526D0(pTask, fFirst);
    destinationY = destination_001526D0(pTask, fFirst);
    target = SzDuel_GetUnitLoc(destinationY >> 8, destinationX & 0xFF);
    for (i = 0; i < 12; i++) {
        points[i].x = points[i].y = 0xF;
    }
    unit = SzDuel_GetUnit(((Input_001526D0 *)pTask)->position >> 8,
                        ((Input_001526D0 *)pTask)->position & 0xFF);
    currentX = current & 0xFF;
    currentY = current >> 8;
    if (GetMoveRev(unit, currentX, currentY) == 0) {
        s32 cost;
        ((Output_001526D0 *)pInput)->position = ((Input_001526D0 *)pTask)->position;
        ((Output_001526D0 *)pInput)->command = 6;
        ((Output_001526D0 *)pInput)->destination = current;
        cost = TaLogic_GetUnitWarning(currentX, currentY, nSide, 3, 1,
                            (u8)TaLogic_GetWarnHideLvl_00153ED0(nSide));
        if (cost >= SzDuel_GetUnitAP(((Input_001526D0 *)pTask)->position >> 8,
                                 ((Input_001526D0 *)pTask)->position & 0xFF, 0)) {
            ((Output_001526D0 *)pInput)->result = TaLogic_IsDefStyleUnit(
                ((Input_001526D0 *)pTask)->position >> 8,
                ((Input_001526D0 *)pTask)->position & 0xFF,
                pInput[2], 1, 0);
        } else {
            ((Output_001526D0 *)pInput)->result = TaLogic_IsDefStyleUnit(
                ((Input_001526D0 *)pTask)->position >> 8,
                ((Input_001526D0 *)pTask)->position & 0xFF,
                pInput[2], 0, 0);
        }
        TaLogic_InitRogicControl(pTask, fFirst);
    } else {
        s32 y;
        s32 x;
        Point_001526D0 *point;
        s32 index;
        s32 bestCost;
        s32 selected;
        s32 position = ((Input_001526D0 *)pTask)->position;
        TaLogic_GetInvadeRoot(position >> 8, position & 0xFF, points, currentX, currentY,
                      x = target & 0xFF, y = target >> 8,
                      destination_001526D0(pTask, fFirst), 0, 30,
                      (u16)TaLogic_GetWarnHideLvl_00153ED0(nSide));
        count = TaLogic_GetMinGoalCount((u8 *)points);
        selected = 0xFF;
        if (count > 0) {
            forced = 0;
            bestCost = 0xFFFF;
            for (index = 0; index < count; index++) {
                s32 hit = TaLogic015_IsOpenMoveUnit(((Input_001526D0 *)pTask)->position >> 8,
                                      ((Input_001526D0 *)pTask)->position & 0xFF,
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
                    cost = TaLogic_GetUnitWarning(point->x, point->y, nSide,
                                        (u8)(mode ? 5 : 2), 1,
                                        (u8)TaLogic_GetWarnHideLvl_00153ED0(nSide));
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
            ((Output_001526D0 *)pInput)->position = ((Input_001526D0 *)pTask)->position;
            ((Output_001526D0 *)pInput)->command = 6;
            ((Output_001526D0 *)pInput)->destination = current;
            ((Output_001526D0 *)pInput)->state = state;
            ((Output_001526D0 *)pInput)->result = TaLogic_IsDefStyleUnit(
                ((Input_001526D0 *)pTask)->position >> 8,
                ((Input_001526D0 *)pTask)->position & 0xFF,
                ((Output_001526D0 *)pInput)->destination, 0, 0);
            TaLogic_InitRogicControl(pTask, fFirst);
            return 0;
        }
        if (selected != 0xFF) {
            ((Output_001526D0 *)pInput)->position = ((Input_001526D0 *)pTask)->position;
            ((Output_001526D0 *)pInput)->command = 6;
            ((Output_001526D0 *)pInput)->destination = (points[selected].y << 8) | points[selected].x;
            ((Output_001526D0 *)pInput)->state = forced;
            ((Output_001526D0 *)pInput)->result = TaLogic_IsDefStyleUnit(
                ((Input_001526D0 *)pTask)->position >> 8,
                ((Input_001526D0 *)pTask)->position & 0xFF,
                ((Output_001526D0 *)pInput)->destination, 0, 0);
        } else {
            ((Output_001526D0 *)pInput)->position = ((Input_001526D0 *)pTask)->position;
            ((Output_001526D0 *)pInput)->command = 6;
            ((Output_001526D0 *)pInput)->destination = current;
            ((Output_001526D0 *)pInput)->state = forced;
            ((Output_001526D0 *)pInput)->result = TaLogic_IsDefStyleUnit(
                ((Input_001526D0 *)pTask)->position >> 8,
                ((Input_001526D0 *)pTask)->position & 0xFF,
                ((Output_001526D0 *)pInput)->destination, 0, 0);
            TaLogic_InitRogicControl(pTask, fFirst);
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


/* The task's target square: the second half-word when the second argument is 1, else the first. */
static inline u32 target_00152CD0(void *unit, s32 side) {
    return side == 1 ? (u32)(u16)(((Unit_00152CD0 *)unit)->target.packed >> 16) : (u32)((Unit_00152CD0 *)unit)->target.low;
}

/* The smaller of the two values. */
static inline u32 minY_00152CD0(void *unit, s32 side, u8 coord) {
    return coord < (target_00152CD0(unit, side) >> 8) ? coord : (target_00152CD0(unit, side) >> 8);
}

/* The larger of the two values. */
static inline u32 maxY_00152CD0(void *unit, s32 side, u8 coord) {
    return (target_00152CD0(unit, side) >> 8) < coord ? coord : (target_00152CD0(unit, side) >> 8);
}

/* The smaller of the two values. */
static inline u32 minX_00152CD0(void *unit, s32 side, u8 coord) {
    return coord < (target_00152CD0(unit, side) & 0xFF) ? coord : (target_00152CD0(unit, side) & 0xFF);
}

/* The larger of the two values. */
static inline u32 maxX_00152CD0(void *unit, s32 side, u8 coord) {
    return (target_00152CD0(unit, side) & 0xFF) < coord ? coord : (target_00152CD0(unit, side) & 0xFF);
}

/* The task of a unit moving to its goal (task `pTask`), into `pInput` (`fFirst` = 1 for the unit's first-choice
   task). */
s32 TaLogic_GetMinimumTask_MoveMission_00152CD0(void *pTask, s32 nSide, void *pInput, u8 fFirst, u8 nKind) {
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
    initial = SzDuel_GetUnitLoc(((Unit_00152CD0 *)pTask)->position >> 8, ((Unit_00152CD0 *)pTask)->position & 0xFF);
    {
        s32 bestScore;
        s32 best;
        s32 side = fFirst;
        Coord_00152CD0 *candidate;
        s32 index;
        if (target_00152CD0(pTask, side) == 0xFFFF) {
            if (initial == target_00152CD0(pTask, side)) {
                ((Output_00152CD0 *)pInput)->position = ((Unit_00152CD0 *)pTask)->position;
                ((Output_00152CD0 *)pInput)->kind = 6;
                ((Output_00152CD0 *)pInput)->target = initial;
                ((Output_00152CD0 *)pInput)->flag = TaLogic_IsDefStyleUnit(((Unit_00152CD0 *)pTask)->position >> 8, ((Unit_00152CD0 *)pTask)->position & 0xFF, ((Output_00152CD0 *)pInput)->target, nKind, 0);
                ((Output_00152CD0 *)pInput)->value = TaLogic_IsOpenUnit_00153AE0(((Unit_00152CD0 *)pTask)->position >> 8, ((Unit_00152CD0 *)pTask)->position & 0xFF, pTask);
                TaLogic_InitRogicControl(pTask, fFirst);
                return 0;
            }
        }

        if (SzDuel_GetUnitStatus(((Unit_00152CD0 *)pTask)->position >> 8, ((Unit_00152CD0 *)pTask)->position & 0xFF, 4) != 0) {
            if ((SzDuel_GetUnitKind(((Unit_00152CD0 *)pTask)->position >> 8, ((Unit_00152CD0 *)pTask)->position & 0xFF) >> 5) == 1 ||
                (SzDuel_GetUnitKind(((Unit_00152CD0 *)pTask)->position >> 8, ((Unit_00152CD0 *)pTask)->position & 0xFF) >> 5) == 5) {
                SzDuel_SetUnitStatus(((Unit_00152CD0 *)pTask)->position >> 8, ((Unit_00152CD0 *)pTask)->position & 0xFF, 0, 1);
                ((Output_00152CD0 *)pInput)->position = ((Unit_00152CD0 *)pTask)->position;
                ((Output_00152CD0 *)pInput)->kind = 14;
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

        cell = SzDuel_GetMapUnitID(target_00152CD0(pTask, side) & 0xFF, target_00152CD0(pTask, side) >> 8);
        if (cell < 0) {
            cell = 0xFFFF;
        }
        TaLogic_GetRoot(((Unit_00152CD0 *)pTask)->position >> 8, ((Unit_00152CD0 *)pTask)->position & 0xFF,
                     coords, initial & 0xFF, initial >> 8, target_00152CD0(pTask, side) & 0xFF,
                     target_00152CD0(pTask, side) >> 8, (u16)cell, 7);
        count = TaLogic_GetMinGoalCount((u8 *)coords);
        {
            if (count > 0) {
                best = 0xFF;
                bestScore = 0xFFFF;
                for (index = 0; index < count; index++) {
                    if (SzDuel_GetMapUnit(candidate->x, candidate->y) == 0) {
                        s32 score = TaLogic_GetUnitWarning(candidate->x, candidate->y, nSide, (u8)(status ? 5 : 2), 1, (u8)TaLogic_GetWarnHideLvl_00153ED0(nSide));
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
                            bestMinY = minY_00152CD0(pTask, side, bestY);
                            bestMaxY = maxY_00152CD0(pTask, side, bestY);
                            bestX = (&coords[best])->x;
                            bestMinX = minX_00152CD0(pTask, side, bestX);
                            bestMaxX = maxX_00152CD0(pTask, side, bestX);
                            currentY = (u8)candidate->y;
                            currentMinY = minY_00152CD0(pTask, side, currentY);
                            currentMaxY = maxY_00152CD0(pTask, side, currentY);
                            currentX = candidate->x;
                            currentMinX = minX_00152CD0(pTask, side, currentX);
                            currentMaxX = maxX_00152CD0(pTask, side, currentX);
                            if ((currentMaxX - currentMinX) + (currentMaxY - currentMinY) < (bestMaxX - bestMinX) + (bestMaxY - bestMinY)) {
                                bestScore = score;
                                best = index;
                            }
                        }
                    }
                    candidate++;
                }
            } else {
                ((Output_00152CD0 *)pInput)->position = ((Unit_00152CD0 *)pTask)->position;
                ((Output_00152CD0 *)pInput)->kind = 6;
                ((Output_00152CD0 *)pInput)->target = initial;
                ((Output_00152CD0 *)pInput)->flag = TaLogic_IsDefStyleUnit(((Unit_00152CD0 *)pTask)->position >> 8, ((Unit_00152CD0 *)pTask)->position & 0xFF, ((Output_00152CD0 *)pInput)->target, nKind, 0);
                ((Output_00152CD0 *)pInput)->value = TaLogic_IsOpenUnit_00153AE0(((Unit_00152CD0 *)pTask)->position >> 8, ((Unit_00152CD0 *)pTask)->position & 0xFF, pTask);
                TaLogic_InitRogicControl(pTask, fFirst);
                return 0;
            }

            if (best != 0xFF) {
                ((Output_00152CD0 *)pInput)->position = ((Unit_00152CD0 *)pTask)->position;
                ((Output_00152CD0 *)pInput)->kind = 6;
                ((Output_00152CD0 *)pInput)->target = (coords[best].y << 8) | coords[best].x;
                ((Output_00152CD0 *)pInput)->flag = TaLogic_IsDefStyleUnit(((Unit_00152CD0 *)pTask)->position >> 8, ((Unit_00152CD0 *)pTask)->position & 0xFF, ((Output_00152CD0 *)pInput)->target, nKind, 0);
                ((Output_00152CD0 *)pInput)->value = TaLogic_IsOpenUnit_00153AE0(((Unit_00152CD0 *)pTask)->position >> 8, ((Unit_00152CD0 *)pTask)->position & 0xFF, pTask);
            } else {
                ((Output_00152CD0 *)pInput)->position = ((Unit_00152CD0 *)pTask)->position;
                ((Output_00152CD0 *)pInput)->kind = 6;
                ((Output_00152CD0 *)pInput)->target = initial;
                ((Output_00152CD0 *)pInput)->flag = TaLogic_IsDefStyleUnit(((Unit_00152CD0 *)pTask)->position >> 8, ((Unit_00152CD0 *)pTask)->position & 0xFF, ((Output_00152CD0 *)pInput)->target, nKind, 0);
                ((Output_00152CD0 *)pInput)->value = TaLogic_IsOpenUnit_00153AE0(((Unit_00152CD0 *)pTask)->position >> 8, ((Unit_00152CD0 *)pTask)->position & 0xFF, pTask);
            }
            TaLogic_InitRogicControl(pTask, fFirst);
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


/* The task's target square: the second half-word when the second argument is 1, else the first. */
static inline u32 target_00153550(void *src, s32 mode) {
    if (mode == 1) {
        return (u16)(((Input_00153550 *)src)->target >> 16);
    } else {
        return *(u16 *)((u8 *)src + 8);
    }
}

/* Sets a move task (action 6) to the given square, and whether the unit should stay in defence there. */
static inline void stay_00153550(void *src, void *dst, s32 position, s32 flag) {
    Input_00153550 *source = src;
    Output_00153550 *out = dst;

    out->position = source->position;
    out->action = 6;
    out->destination = position;
    out->result = TaLogic_IsDefStyleUnit(source->position >> 8, source->position & 0xFF,
                                out->destination, flag, 0);
}

/* The task of setting a trap (task `pTask`), into `pInput`. */
s32 TaLogic_GetMinimumTask_TrapMission_00153550(void *pTask, s32 nSide, void *pInput, s32 fFirst) {
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
    Input_00153550 *source = pTask;
    Output_00153550 *out = pInput;
    extern void TaLogic_GetInvadeRoot();

    flag = TaLogic015_IsActiveMode();
    mode = fFirst & 0xFF;
    xPosition = target_00153550(pTask, mode);
    yPosition = target_00153550(pTask, mode);
    if (SzDuel_GetUnit(yPosition >> 8, xPosition & 0xFF) == 0) {
        TaLogic_InitRogicControl(pTask, 1);
        return -1;
    }
    start = SzDuel_GetUnitLoc(source->position >> 8, source->position & 0xFF);
    xPosition = target_00153550(pTask, mode);
    yPosition = target_00153550(pTask, mode);
    target = SzDuel_GetUnitLoc(yPosition >> 8, xPosition & 0xFF);
    if (target_00153550(pTask, mode) == 0xFFFF) {
        stay_00153550(pTask, pInput, start, 1);
        return 0;
    } else {
        s32 unit = SzDuel_GetUnit(source->position >> 8, source->position & 0xFF);
        startX = start & 0xFF;
        startY = start >> 8;
        if (GetMoveRev(unit, startX, startY) == 0 ||
                TaLogic_IsAttackedNow(source->position >> 8, source->position & 0xFF, 0) == 1) {
            stay_00153550(pTask, pInput, start, 1);
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
                u16 card = (u16)TaLogic_GetWarnHideLvl_00153ED0(nSide);
                TaLogic_GetInvadeRoot(position >> 8, position & 0xFF, points,
                    startX, startY, targetX = target & 0xFF,
                    targetY = target >> 8, target_00153550(pTask, mode),
                    0, 30, card);
            }
            count = TaLogic_GetMinGoalCount((u8 *)points);
            bestIndex = 0xFF;
            if (count > 0) {
                bestScore = 0;
                for (i = 0; i < count; i++, p++) {
                    if (SzDuel_GetMapUnit(p->x, p->y) == 0) {
                        s32 score = TaLogic_GetUnitWarning(p->x, p->y, nSide, (u8)(flag ? 5 : 2), 1,
                            (u8)TaLogic_GetWarnHideLvl_00153ED0(nSide));
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
                stay_00153550(pTask, pInput, start, 1);
                return 0;
            }
            if (bestIndex != 0xFF) {
                out->position = source->position;
                out->action = 6;
                out->destination = (points[bestIndex].y << 8) | points[bestIndex].x;
                out->result = TaLogic_IsDefStyleUnit(source->position >> 8,
                    source->position & 0xFF, out->destination, 0, 0);
            } else {
                stay_00153550(pTask, pInput, start, 1);
                return 0;
            }
        }
    }
    return 0;
}

/* Whether this duelist plays in its attacking mode this turn. */
s32 TaLogic015_IsActiveMode(void) {
    return (SzDuel_GetUnitCount(SzDuel_GetTurnOwner()) < 3) ? 0 : 1;
}

/* Whether this duelist opens (turns face up) unit (nSide, nID) now: 0 no, 1 or 2 by its kind. */
s32 TaLogic_IsOpenUnit_00153AE0(s32 nSide, s32 nID) {
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

    kind = SzDuel_GetUnitCardNo(nSide, nID);
    SzDuel_GetUnitLoc(nSide, nID);
    player = Ta_IsUnitControl(nSide, nID);
    info = SzDuel_GetUnitEffect(nSide, nID, 0);
    if (SzDuel_GetUnitStatus(nSide, nID, 4) != 0) {
        return 0;
    }
    TaUtil_GetUnitLst(player, 2, buf);
    switch (SzDuel_GetUnitKind(nSide, nID) >> 5) {
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
        if (TaLogic_GetActionReaction(nSide, nID, 0, 0, 6, 0) == 5) {
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

/* The larger of the two values. */
static inline s32 max_00153DD0(s32 a, s32 b) {
    if (a < b) {
        return b;
    }
    return a;
}

/* Whether unit (nSide, nID) may open while moving from (nX, nZ) to the square next to it, (gX, gZ). */
s32 TaLogic015_IsOpenMoveUnit(s32 nSide, s32 nID, s32 nX, s32 nZ, s32 gX, s32 gZ) {
    s32 min_y;
    s32 min_x;

    min_y = nZ < gZ ? nZ : gZ;
    gZ = max_00153DD0(gZ, nZ);
    min_x = nX < gX ? nX : gX;
    gX = max_00153DD0(gX, nX);
    if ((gX - min_x) + (gZ - min_y) != 2) {
        return 0;
    }
    if (SzDuel_GetUnit(nSide, nID) == 0) {
        return 0;
    }
    if (SzDuel_GetUnitStatus(nSide, nID, 0) == 0) {
        if (CheckLandAgreement2(SzDuel_GetField(nX, nZ), nSide, nID) != 1) {
            return 0;
        }
        return 1;
    }
    return 0;
}

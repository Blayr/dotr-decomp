#include "common.h"

typedef struct {
    s16 id;
    u8 unk2;
    u8 pad3;
    s16 unk4;
    u8 pad6[6];
    s32 unkC;
} Ctx_0015A360;

typedef struct {
    u8 pad0[0x3C];
    u16 unk3C;
    u8 pad3E[0x22];
} Work_0015A360;

s32 TaLogic_GetNearCard2(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8,
                  s32 arg9);

/* The summon task for side `nSide`: which hand cards to play and where, into `pInput`; -1 when it plays none. */
s32 TaLogic_GetMinimumTask_Summon_0015A360(s32 wUnit, s32 nSide, s32 pInput) {
    s32 ret;
    s32 kind;
    Ctx_0015A360 *ctx = (Ctx_0015A360 *)pInput;
    Work_0015A360 work;
    s32 res;
    extern s32 TaLogic_GetUnitNum();

    ctx->id = wUnit;
    if (SzDuel_InqHandPhase(nSide) == 0) {
        return -1;
    }
    if (TaLogic_GetUnitNum(nSide, 0) == 5 && TaLogic_GetUnitNum(nSide, 1) == 5) {
        return -1;
    }
    kind = TaLogic018_IsHandPlay(nSide, &work);
    if (kind < 0) {
        return -1;
    }
    ctx->unk2 = 10;
    ctx->unkC = 2;
    wUnit = SzDuel_GetUnitLoc(wUnit >> 8, wUnit & 0xFF);
    if (kind == 0) {
        if (TaLogic018_SetComboQue(nSide, (u8 *)ctx, &work) >= 0) {
            ret = TaLogic_GetNearCard2(&work, wUnit & 0xFF, wUnit >> 8, nSide == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, TaLogic_GetWarnHideLvl_0015D120(nSide));
            if (ret < 0) {
                if (SzDuel_GetUnitMonsterCount(nSide) < 6) {
                    res = TaLogic018_GetSummonPiece(nSide, (u8)kind, &work, ret);
                    if (res < 0) {
                        return -1;
                    }
                    ctx->unk4 = res;
                    return 1;
                }
            } else {
                res = TaLogic018_GetSummonPiece(nSide, (u8)kind, &work, ret);
                if (res < 0) {
                    return -1;
                }
                ctx->unk4 = res;
                return 1;
            }
        }
    } else {
        ret = TaLogic_GetNearCard2(&work, wUnit & 0xFF, wUnit >> 8, nSide == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, TaLogic_GetWarnHideLvl_0015D120(nSide));
    }
    if (kind == 2) {
        TaLogic018_SetSpecialComboQue(nSide, ctx, &work);
        res = TaLogic018_GetSummonPiece(nSide, (u8)kind, &work, ret);
        if (res < 0) {
            return -1;
        }
        ctx->unk4 = res;
        return 1;
    }
    if (TaLogic018_GetSpellPlay(nSide, (u8 *)ctx, &work, work.unk3C) < 0) {
        return -1;
    }
    res = TaLogic018_GetSummonPiece(nSide, (u8)kind, &work, ret);
    if (res < 0) {
        return -1;
    }
    ctx->unk4 = res;
    return 1;
}

/* Whether side `nSide` should play from its hand this turn (and what, into `pInput`). */
s32 TaLogic018_IsHandPlay(s32 nSide, void *pInput) {
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
        s32 result = TaLogic018_GetSpellPlay(nSide, (u8 *)data, pInput, 0x3E7);
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
    if (TaLogic018_GetSpecCardPlay(nSide, data, pInput, 0x343) >= 0 && TaLogic018_IsDoCerem(nSide, 0x343) == 1) {
        return 2;
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
        s32 result = TaLogic018_GetSpellPlay(nSide, (u8 *)data, pInput, 0x3E7);
        if (result >= 0) {
            return result;
        } else {
            return -1;
        }
    }
}

/* Whether side `nSide` holds card `nCardNo` and can summon it (its slot into `bCombo`, the card into `pCardInfo`);
   returns its kind group or -1. */
s32 TaLogic018_GetSpecCardPlay(s32 nSide, void *bCombo, void *pCardInfo, s32 nCardNo) {
    s32 entries[8];
    s32 index;
    s32 *entry;
    s32 key;

    TaHand_GetNextHand(nSide, entries);
    index = 0;
    if (index < TaHand_GetNextHandNum(nSide)) {
        key = nCardNo & 0xFFFF;
        entry = entries;
        do {
            if (key == *entry && TaHand_IsCardSummon2(nSide, *entry) == 1) {
                *((s8 *)bCombo + 6) = index;
                SzDuel_InitCardInfo(pCardInfo, entries[index]);
                return TaHand_GetCardKind(entries[index]) >> 5;
            }
            entry++;
            index++;
        } while (index < TaHand_GetNextHandNum(nSide));
    }
    return -1;
}

/* Whether side `nSide` plays a magic or ritual card from its hand now (its slot into `bCombo`, the card into
   `pCardInfo`). */
s32 TaLogic018_GetSpellPlay(s32 nSide, u8 *bCombo, void *pCardInfo, s32 nMode) {
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

extern int func_002493A0_b(int index);
struct DotrPickTarget {
    unsigned char unknown_00[8];
    unsigned short unknown_08;
    short unknown_0a;
};
struct DotrPickBlock {
    struct DotrPickTarget *target;
    unsigned char unknown_04[0x34];
    short unknown_38;
    short unknown_3a;
    unsigned short unknown_3c; 
    unsigned char unknown_3e;
};

/* Fills hand combination `bCombo` for side `nSide`: the best fusion or equip chain, its card into `pCardInfo`. */
int TaLogic018_SetComboQue(int nSide, unsigned char *bCombo, void *pCardInfo)
{
    struct DotrPickBlock * block = pCardInfo;
    int list[8];
    int n;
    int id;
    int i;
    int *p;
    int *q;
    int v;
    int j;

    n = 1;
    if (block == 0) {
        return -1;
    }
    TaHand_GetNextHand(nSide, list);
    id = block->unknown_3c;
    i = 0;
    if (0 < TaHand_GetNextHandNum(nSide)) {
        p = list;
        do {
            if (id == *p && TaHand_GetCardKind(*p) >> 5 == 0) {
                bCombo[6] = i;
            }
            p++;
            i++;
        } while (i < TaHand_GetNextHandNum(nSide));
    }
    j = 0;
    if (0 < TaHand_GetNextHandNum(nSide)) {
        do {
            q = &list[j];
            if (Ta_GetHandEnchant(id, *q) >= 0 && TaHand_GetCardKind(*q) >> 5 == 2 && (v = *q) != 795 && v != 796) {
                if (SzDuel_GetUnitAP2(block, 0) + func_002493A0_b(v) < 1400) {
                    block->unknown_38 += (short)func_002493A0_b(*q);
                    block->unknown_3a += (short)func_002493A0_b(*q);
                    bCombo[n + 6] = j;
                    n++;
                } else {
                    j = TaHand_GetNextHandNum(nSide);
                }
            }
            j++;
        } while (j < TaHand_GetNextHandNum(nSide));
    }
    return 1;
}


typedef struct {
    u8 pad0[6];
    u8 slot[5];
} Obj1_0015AD00;

typedef struct {
    u8 pad0[0x38];
    s16 f38;
    s16 f3A;
    u16 id;
} Obj2_0015AD00;

/* Fills hand combination `bCombo` for side `nSide` with this duelist's special combination, its card into
   `pCardInfo`. */
s32 TaLogic018_SetSpecialComboQue(s32 nSide, void *bCombo, void *pCardInfo) {
    Obj1_0015AD00 *o1 = bCombo;
    Obj2_0015AD00 *o2 = pCardInfo;
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

typedef struct {
    u8 low : 4;
    u8 high : 4;
} Nibbles_0015AF30;

typedef struct {
    u8 pad[0x3E];
    u8 f3E;
} Card_0015AF30;


/* The square side `nSide` summons a card of kind `sKind` to. */
s32 TaLogic018_GetSummonPiece(s32 nSide, s32 sKind, void *pInput, s32 nMode) {
    extern s32 TaLogic_IsUnitWin4();
    extern s32 TaLogic_GetInvadeRoot2(s32, void *, s32, s32, s32, s32, s32, s32, u8, u16);
    extern s32 TaLogic_GetRoot2(s32, void *, s32, s32, s32, s32, u16, u8);
    Card_0015AF30 *card = pInput;
    Nibbles_0015AF30 entries[12];
    s32 id;
    s32 hi;
    s32 lo;
    s32 i;
    Nibbles_0015AF30 *entry;
    s32 pos;
    s32 cost;
    s32 bestId;
    s32 best;
    s32 y;
    s32 x;
    s32 j;
    s32 slot;

    if (card == NULL) {
        return -1;
    }
    entry = entries;
    i = 0;
    do {
        entry->low = entry->high = 15;
        entry++;
        i++;
    } while (i < 12);
    if ((u8)(card->f3E >> 5) == 0 && nMode >= 0) {
        best = 0xFF;
        bestId = 0xFFFF;
        pos = SzDuel_GetUnitLoc(nMode >> 8, nMode & 0xFF);
        for (i = 0; i < 8; i++) {
            id = Ta_GetSommonPiecePreference(nSide, i);
            if (id < 0) {
                continue;
            }
            lo = id & 0xFF;
            hi = id >> 8;
            if (SzDuel_GetField(lo, hi) == 8) {
                continue;
            }
            if (SzDuel_GetField(lo, hi) == 9 && Ta_IsVirus_Chk3(card, lo, hi) == 1) {
                continue;
            }
            if (SzDuel_GetMapUnit(lo, hi) != 0) {
                continue;
            }
            if (TaLogic_IsUnitWin4(card, nMode, TaLogic_GetWarnHideLvl_0015D120(nSide), pos & 0xFF, pos >> 8, 0) > 0) {
                cost = TaLogic_GetInvadeRoot2((s32)card, entries, lo, hi, pos & 0xFF, pos >> 8, nMode, 0, 3,
                                     TaLogic_GetWarnHideLvl_0015D120(nSide));
            } else {
                cost = TaLogic_GetRoot2((s32)card, entries, lo, hi, pos & 0xFF, pos >> 8, nMode, 3);
            }
            if (TaLogic_GetMinGoalCount((u8 *)entries) > 0 && cost < best) {
                best = cost;
                bestId = id;
            }
        }
        if (bestId != 0xFFFF) {
            return bestId;
        }
    }
    for (j = 0; j < 8; j++) {
        slot = Ta_GetSommonPiecePreference(nSide, j);
        if (slot < 0) {
            continue;
        }
        x = slot & 0xFF;
        y = slot >> 8;
        if (SzDuel_GetField(x, y) == 8) {
            continue;
        }
        if (SzDuel_GetField(x, y) == 9 && Ta_IsVirus_Chk3(card, x, y) == 1) {
            continue;
        }
        if (SzDuel_GetMapUnitID(x, y) < 0) {
            return slot;
        }
    }
    return -1;
}

typedef struct Nibbles_0015B250 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_0015B250;

typedef struct Output_0015B250 {
    u16 position;
    u8 action;
    u8 pad3;
    u16 destination;
    u8 pad6[6];
    s32 special;
    u8 result;
} Output_0015B250;


/* The task of a unit running from danger (task `pTask`): the safest square in reach, into `pInput` (`fFirst` = 1
   for the unit's first-choice task). */
s32 TaLogic_GetMinimumTask_RunMission_0015B250(u16 *pTask, s32 nSide, void *pInput, u8 fFirst) {
    Output_0015B250 *output = pInput;
    s32 target;
    u8 endX;
    u8 extra;
    Nibbles_0015B250 nibbles[12];
    s32 bestScore;
    s32 best;
    s32 i;
    Nibbles_0015B250 *p;
    extern s32 TaLogic_IsOpenUnit_0015CBB0();
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

        initialScore = TaLogic_GetWarnHideLvl_0015D120(nSide);
        centerX = target & 0xFF;
        centerY = target >> 8;
        if (TaLogic_GetUnitWarning(centerX, centerY, *pTask, 3, initialScore, 0) == 0) {
            output->position = *pTask;
            output->action = 6;
            output->destination = target;
            output->result = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, output->destination, 1, 0);
            output->special = TaLogic_IsOpenUnit_0015CBB0(*pTask >> 8, *pTask & 0xFF, pTask);
            TaLogic_InitRogicControl(pTask, fFirst);
            return 0;
        }
        if ((range = GetMoveRev(SzDuel_GetUnit(*pTask >> 8, *pTask & 0xFF), centerX, centerY)) == 0) {
            output->position = *pTask;
            output->action = 6;
            output->destination = target;
            output->result = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, output->destination, 1, 0);
            output->special = TaLogic_IsOpenUnit_0015CBB0(*pTask >> 8, *pTask & 0xFF, pTask);
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
                        candidateScore = TaLogic_GetUnitWarning(x, y, *pTask, 3, (u16)TaLogic_GetWarnHideLvl_0015D120(nSide), 0);
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
            output->special = TaLogic_IsOpenUnit_0015CBB0(*pTask >> 8, *pTask & 0xFF, pTask);
        } else {
            output->position = *pTask;
            output->action = 6;
            output->destination = target;
            output->result = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, output->destination, 1, 0);
            output->special = TaLogic_IsOpenUnit_0015CBB0(*pTask >> 8, *pTask & 0xFF, pTask);
        }
        TaLogic_InitRogicControl(pTask, fFirst);
        return 0;
    }
}

typedef struct Input_0015B820 {
    u16 pos;
    u8 pad2[6];
    u32 target;
} Input_0015B820;

typedef struct Output_0015B820 {
    u16 pos;
    u8 command;
    u8 pad3;
    u16 target;
    u8 pad6[6];
    s32 special;
    u8 result;
} Output_0015B820;

typedef struct Cell_0015B820 {
    u8 x : 4;
    u8 y : 4;
} Cell_0015B820;


/* The task's target square: the second half-word when the second argument is 1, else the first. */
static inline u32 target_0015B820(Input_0015B820 *input, u8 mode) {
    if (mode == 1) {
        return (u16)(input->target >> 16);
    }
    return (u16)input->target;
}

/* The task of a unit attacking (task `pTask`): its path to the goal, into `pInput`; -1 when it has none (`fFirst`
   = 1 for the unit's first-choice task). */
s32 TaLogic_GetMinimumTask_AtkMission_0015B820(void *pTask, s32 nSide, void *pInput, u8 fFirst) {
    extern s32 TaLogic_IsOpenUnit_0015CBB0();
    extern void TaLogic_GetInvadeRoot();
    s32 source;
    s32 count;
    s32 source_y;
    s32 source_x;
    s32 special;
    u8 mode;
    Cell_0015B820 cells[12];
    s32 target;
    s32 pos;
    s32 target_y;
    s32 target_x;
    Cell_0015B820 *candidate;
    s32 initial_special;
    s32 i;
    s32 best_cost;
    s32 best;
    s32 cost;
    s32 unit;
    s32 init_i;
    u32 target_low;
    u32 target_high;
    Cell_0015B820 *cell;
    Input_0015B820 *input = pTask;
    Output_0015B820 *output = pInput;

    mode = fFirst;
    target_low = target_0015B820(input, fFirst);
    target_high = target_0015B820(input, fFirst);
    if (SzDuel_GetUnit(target_high >> 8, target_low & 0xFF) == 0) {
        TaLogic_InitRogicControl(input, 1);
        return -1;
    }

    initial_special = TaLogic_IsOpenUnit_0015CBB0(input->pos >> 8, input->pos & 0xFF, input);
    source = SzDuel_GetUnitLoc(input->pos >> 8, input->pos & 0xFF);
    target_low = target_0015B820(input, fFirst);
    target_high = target_0015B820(input, fFirst);
    target = SzDuel_GetUnitLoc(target_high >> 8, target_low & 0xFF);
    cell = cells;
    init_i = 0;
    do {
        init_i++;
        cell->x = cell->y = 0xF;
        cell++;
    } while (init_i < 12);

    unit = SzDuel_GetUnit(input->pos >> 8, input->pos & 0xFF);
    source_x = source & 0xFF;
    source_y = source >> 8;
    if (GetMoveRev(unit, source_x, source_y) == 0) {
        output->pos = input->pos;
        output->command = 6;
        output->target = source;
        cost = TaLogic_GetUnitWarning(source_x, source_y, nSide, 3, 1,
                            (u8)TaLogic_GetWarnHideLvl_0015D120(nSide));
        if (cost >= SzDuel_GetUnitAP(input->pos >> 8, input->pos & 0xFF, 0)) {
            output->result = TaLogic_IsDefStyleUnit(input->pos >> 8, input->pos & 0xFF,
                                         output->target, 1, 0);
        } else {
            output->result = TaLogic_IsDefStyleUnit(input->pos >> 8, input->pos & 0xFF,
                                         output->target, 0, 0);
        }
        TaLogic_InitRogicControl(input, mode);
        return 0;
    } else {
        u16 limit;
        pos = input->pos;
        limit = TaLogic_GetWarnHideLvl_0015D120(nSide);
        TaLogic_GetInvadeRoot(pos >> 8, pos & 0xFF, cells, source_x, source_y,
                     target_x = target & 0xFF, target_y = target >> 8,
                     target_0015B820(input, fFirst), 0, 30, limit);
        count = TaLogic_GetMinGoalCount((u8 *)cells);
        best = 0xFF;
        if (count > 0) {
            special = 0;
            best_cost = 0xFFFF;
            for (i = 0; i < count; i++) {
                if (TaLogic018_IsOpenMoveUnit(input->pos >> 8, input->pos & 0xFF,
                                 source_x, source_y, target_x, target_y) == 1) {
                    Cell_0015B820 *chosen = &cells[i];
                    best = i;
                    special = 1;
                    i = count;
                    chosen->x = target_x;
                    chosen->y = target_y;
                } else {
                    u8 limit;
                    candidate = &cells[i];
                    limit = TaLogic_GetWarnHideLvl_0015D120(nSide);
                    cost = TaLogic_GetUnitWarning(candidate->x, candidate->y, nSide, 3, 1, limit);
                    if (cost < best_cost) {
                        best_cost = cost;
                        best = i;
                    } else if (cost == best_cost) {
                        Cell_0015B820 *chosen = &cells[best];
                        s32 old_y_min;
                        s32 old_y_max;
                        s32 old_x_min;
                        s32 old_x_max;
                        s32 new_y_min;
                        s32 new_y_max;
                        s32 new_x_min;
                        s32 new_x_max;

                        old_y_min = chosen->y < target_y ? chosen->y : target_y;
                        old_y_max = target_y < chosen->y ? chosen->y : target_y;
                        old_x_min = chosen->x < target_x ? chosen->x : target_x;
                        old_x_max = target_x < chosen->x ? chosen->x : target_x;
                        new_y_min = candidate->y < target_y ? candidate->y : target_y;
                        new_y_max = target_y < candidate->y ? candidate->y : target_y;
                        new_x_min = candidate->x < target_x ? candidate->x : target_x;
                        new_x_max = target_x < candidate->x ? candidate->x : target_x;
                        if ((new_x_max - new_x_min) + (new_y_max - new_y_min) <
                            (old_x_max - old_x_min) + (old_y_max - old_y_min)) {
                            best_cost = cost;
                            best = i;
                        }
                    }
                }
            }
        } else {
            output->pos = input->pos;
            output->command = 6;
            output->target = source;
            output->special = initial_special;
            output->result = TaLogic_IsDefStyleUnit(input->pos >> 8, input->pos & 0xFF,
                                         output->target, 0, 0);
            TaLogic_InitRogicControl(input, mode);
            return 0;
        }
        if (best != 0xFF) {
            output->pos = input->pos;
            output->command = 6;
            output->target = (cells[best].y << 8) | cells[best].x;
            output->special = special;
            output->result = TaLogic_IsDefStyleUnit(input->pos >> 8, input->pos & 0xFF,
                                         output->target, 0, 0);
        } else {
            output->pos = input->pos;
            output->command = 6;
            output->target = source;
            output->special = special;
            output->result = TaLogic_IsDefStyleUnit(input->pos >> 8, input->pos & 0xFF,
                                         output->target, 0, 0);
            TaLogic_InitRogicControl(input, mode);
            return 0;
        }
    }
    return 0;
}

typedef struct Coord_0015BE00 {
    u8 x : 4;
    u8 y : 4;
} Coord_0015BE00;

typedef struct Unit_0015BE00 {
    u16 position;
    u8 pad2[6];
    union {
        u32 packed;
        u16 low;
    } target;
} Unit_0015BE00;

typedef struct Output_0015BE00 {
    u16 position;
    u8 kind;
    u8 pad3;
    u16 target;
    u8 pad6[6];
    s32 value;
    u8 flag;
} Output_0015BE00;


/* The task's target square: the second half-word when the second argument is 1, else the first. */
static inline u32 target_0015BE00(void *unit, s32 side) {
    return side == 1 ? (u32)(u16)(((Unit_0015BE00 *)unit)->target.packed >> 16) : (u32)((Unit_0015BE00 *)unit)->target.low;
}

/* The smaller of the two values. */
static inline u32 minY_0015BE00(void *unit, s32 side, u8 coord) {
    return coord < (target_0015BE00(unit, side) >> 8) ? coord : (target_0015BE00(unit, side) >> 8);
}

/* The larger of the two values. */
static inline u32 maxY_0015BE00(void *unit, s32 side, u8 coord) {
    return (target_0015BE00(unit, side) >> 8) < coord ? coord : (target_0015BE00(unit, side) >> 8);
}

/* The smaller of the two values. */
static inline u32 minX_0015BE00(void *unit, s32 side, u8 coord) {
    return coord < (target_0015BE00(unit, side) & 0xFF) ? coord : (target_0015BE00(unit, side) & 0xFF);
}

/* The larger of the two values. */
static inline u32 maxX_0015BE00(void *unit, s32 side, u8 coord) {
    return (target_0015BE00(unit, side) & 0xFF) < coord ? coord : (target_0015BE00(unit, side) & 0xFF);
}

/* The task of a unit moving to its goal (task `pTask`), into `pInput` (`fFirst` = 1 for the unit's first-choice
   task). */
s32 TaLogic_GetMinimumTask_MoveMission_0015BE00(void *pTask, s32 nSide, void *pInput, u8 fFirst, u8 nKind) {
    extern s32 TaLogic_IsOpenUnit_0015CBB0();
    extern s32 TaLogic_GetUnitWarning();
    extern void TaLogic_GetRoot();
    extern s32 TaLogic_IsDefStyleUnit(s32, s32, s32, u8, s32);
    Coord_0015BE00 coords[12];
    s32 initial;
    s32 cell;
    s32 count;

    initial = SzDuel_GetUnitLoc(((Unit_0015BE00 *)pTask)->position >> 8, ((Unit_0015BE00 *)pTask)->position & 0xFF);
    {
    s32 bestScore;
    s32 best;
    s32 side = fFirst;
    Coord_0015BE00 *candidate;
    s32 index;
    if (target_0015BE00(pTask, side) == 0xFFFF) {
        if (initial == target_0015BE00(pTask, side)) {
            ((Output_0015BE00 *)pInput)->position = ((Unit_0015BE00 *)pTask)->position;
            ((Output_0015BE00 *)pInput)->kind = 6;
            ((Output_0015BE00 *)pInput)->target = initial;
            ((Output_0015BE00 *)pInput)->flag = TaLogic_IsDefStyleUnit(((Unit_0015BE00 *)pTask)->position >> 8, ((Unit_0015BE00 *)pTask)->position & 0xFF, ((Output_0015BE00 *)pInput)->target, nKind, 0);
            ((Output_0015BE00 *)pInput)->value = TaLogic_IsOpenUnit_0015CBB0(((Unit_0015BE00 *)pTask)->position >> 8, ((Unit_0015BE00 *)pTask)->position & 0xFF, pTask);
            TaLogic_InitRogicControl(pTask, fFirst);
            return 0;
        }
    }

    if (SzDuel_GetUnitStatus(((Unit_0015BE00 *)pTask)->position >> 8,
                      ((Unit_0015BE00 *)pTask)->position & 0xFF, 4) != 0) {
        if ((SzDuel_GetUnitKind(((Unit_0015BE00 *)pTask)->position >> 8,
                          ((Unit_0015BE00 *)pTask)->position & 0xFF) >> 5) == 1 ||
            (SzDuel_GetUnitKind(((Unit_0015BE00 *)pTask)->position >> 8,
                          ((Unit_0015BE00 *)pTask)->position & 0xFF) >> 5) == 5) {
            SzDuel_SetUnitStatus(((Unit_0015BE00 *)pTask)->position >> 8,
                          ((Unit_0015BE00 *)pTask)->position & 0xFF, 0, 1);
            ((Output_0015BE00 *)pInput)->position = ((Unit_0015BE00 *)pTask)->position;
            ((Output_0015BE00 *)pInput)->kind = 0xE;
            return 0;
        }
    }

    candidate = coords;
    {
        s32 i = 0;
        Coord_0015BE00 *entry = candidate;
        do {
            entry->x = entry->y = 0xF;
            i++;
            entry++;
        } while (i < 12);
    }

    cell = SzDuel_GetMapUnitID(target_0015BE00(pTask, side) & 0xFF, ((u32)target_0015BE00(pTask, side)) >> 8);
    if (cell < 0) {
        cell = 0xFFFF;
    }
    TaLogic_GetRoot(((Unit_0015BE00 *)pTask)->position >> 8, ((Unit_0015BE00 *)pTask)->position & 0xFF,
                 coords, initial & 0xFF, initial >> 8, target_0015BE00(pTask, side) & 0xFF,
                 ((u32)target_0015BE00(pTask, side)) >> 8, (u16)cell, 7);
    count = TaLogic_GetMinGoalCount((u8 *)coords);
    {
        if (count > 0) {
        best = 0xFF;
        bestScore = 0xFFFF;
        for (index = 0; index < count; index++) {
                if (SzDuel_GetMapUnit(candidate->x, candidate->y) == 0) {
                    s32 score = TaLogic_GetUnitWarning(candidate->x, candidate->y, nSide, 3, 1, (u8)TaLogic_GetWarnHideLvl_0015D120(nSide));
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
                        bestMinY = minY_0015BE00(pTask, side, bestY);
                        bestMaxY = maxY_0015BE00(pTask, side, bestY);
                        bestX = (&coords[best])->x;
                        bestMinX = minX_0015BE00(pTask, side, bestX);
                        bestMaxX = maxX_0015BE00(pTask, side, bestX);
                        currentY = (u8)candidate->y;
                        currentMinY = minY_0015BE00(pTask, side, currentY);
                        currentMaxY = maxY_0015BE00(pTask, side, currentY);
                        currentX = candidate->x;
                        currentMinX = minX_0015BE00(pTask, side, currentX);
                        currentMaxX = maxX_0015BE00(pTask, side, currentX);
                        if ((currentMaxX - currentMinX) + (currentMaxY - currentMinY) < (bestMaxX - bestMinX) + (bestMaxY - bestMinY)) {
                            bestScore = score;
                            best = index;
                        }
                    }
                }
            candidate++;
        }
    } else {
        ((Output_0015BE00 *)pInput)->position = ((Unit_0015BE00 *)pTask)->position;
            ((Output_0015BE00 *)pInput)->kind = 6;
            ((Output_0015BE00 *)pInput)->target = initial;
            ((Output_0015BE00 *)pInput)->flag = TaLogic_IsDefStyleUnit(((Unit_0015BE00 *)pTask)->position >> 8, ((Unit_0015BE00 *)pTask)->position & 0xFF, ((Output_0015BE00 *)pInput)->target, nKind, 0);
            ((Output_0015BE00 *)pInput)->value = TaLogic_IsOpenUnit_0015CBB0(((Unit_0015BE00 *)pTask)->position >> 8, ((Unit_0015BE00 *)pTask)->position & 0xFF, pTask);
        TaLogic_InitRogicControl(pTask, fFirst);
        return 0;
    }

        if (best != 0xFF) {
            ((Output_0015BE00 *)pInput)->position = ((Unit_0015BE00 *)pTask)->position;
            ((Output_0015BE00 *)pInput)->kind = 6;
            ((Output_0015BE00 *)pInput)->target = (coords[best].y << 8) | coords[best].x;
            ((Output_0015BE00 *)pInput)->flag = TaLogic_IsDefStyleUnit(((Unit_0015BE00 *)pTask)->position >> 8, ((Unit_0015BE00 *)pTask)->position & 0xFF, ((Output_0015BE00 *)pInput)->target, nKind, 0);
            ((Output_0015BE00 *)pInput)->value = TaLogic_IsOpenUnit_0015CBB0(((Unit_0015BE00 *)pTask)->position >> 8, ((Unit_0015BE00 *)pTask)->position & 0xFF, pTask);
        } else {
            ((Output_0015BE00 *)pInput)->position = ((Unit_0015BE00 *)pTask)->position;
            ((Output_0015BE00 *)pInput)->kind = 6;
            ((Output_0015BE00 *)pInput)->target = initial;
            ((Output_0015BE00 *)pInput)->flag = TaLogic_IsDefStyleUnit(((Unit_0015BE00 *)pTask)->position >> 8, ((Unit_0015BE00 *)pTask)->position & 0xFF, ((Output_0015BE00 *)pInput)->target, nKind, 0);
            ((Output_0015BE00 *)pInput)->value = TaLogic_IsOpenUnit_0015CBB0(((Unit_0015BE00 *)pTask)->position >> 8, ((Unit_0015BE00 *)pTask)->position & 0xFF, pTask);
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
} Source_0015C670;

typedef struct {
    u16 position;
    u8 action;
    u8 pad3;
    u16 target;
    u8 pad6[10];
    s8 result;
} Action_0015C670;

typedef struct {
    u8 x : 4;
    u8 y : 4;
} Point_0015C670;

#define MIN_0015C670(a, b) ((a) < (b) ? (a) : (b))
#define MAX_0015C670(a, b) ((b) < (a) ? (a) : (b))


/* The task's target square: the second half-word when the second argument is 1, else the first. */
static inline u32 target_0015C670(void *arg0, s32 mode) {
    Source_0015C670 *source = arg0;
    if (mode == 1) {
        return (u16)(source->target.both >> 16);
    }
    return source->target.half[0];
}

/* Sets a move task (action 6) to the given square, and whether the unit should stay in defence there. */
static inline void fill_0015C670(void *arg0, void *arg2, s32 target, s32 flag) {
    Source_0015C670 *source = arg0;
    Action_0015C670 *action = arg2;
    action->position = source->position;
    action->action = 6;
    action->target = target;
    action->result = TaLogic_IsDefStyleUnit(source->position >> 8,
        source->position & 0xFF, action->target, flag, 0);
}

/* The task of setting a trap (task `pTask`), into `pInput`. */
s32 TaLogic_GetMinimumTask_TrapMission_0015C670(void *pTask, s32 nSide, void *pInput, s32 fFirst) {
    s32 start;
    s32 count;
    s32 startY;
    Point_0015C670 points[16];
    s32 bestScore;
    Point_0015C670 *p;
    s32 targetY;
    s32 targetX;
    s32 i;
    s32 bestIndex;
    s32 mode;
    s32 target;
    s32 startX;
    u32 xPosition;
    u32 yPosition;
    Source_0015C670 *source = pTask;
    Action_0015C670 *action = pInput;
    extern void TaLogic_GetInvadeRoot();

    mode = fFirst & 0xFF;
    xPosition = target_0015C670(pTask, mode);
    yPosition = target_0015C670(pTask, mode);
    if (SzDuel_GetUnit(yPosition >> 8, xPosition & 0xFF) == 0) {
        TaLogic_InitRogicControl(pTask, 1);
        return -1;
    }
    start = SzDuel_GetUnitLoc(source->position >> 8, source->position & 0xFF);
    xPosition = target_0015C670(pTask, mode);
    yPosition = target_0015C670(pTask, mode);
    target = SzDuel_GetUnitLoc(yPosition >> 8, xPosition & 0xFF);
    if (target_0015C670(pTask, mode) == 0xFFFF) {
        fill_0015C670(pTask, pInput, start, 1);
        return 0;
    } else {
        s32 unit = SzDuel_GetUnit(source->position >> 8, source->position & 0xFF);
        startX = start & 0xFF;
        startY = start >> 8;
        if (GetMoveRev(unit, startX, startY) == 0 ||
                TaLogic_IsAttackedNow(source->position >> 8, source->position & 0xFF, 0) == 1) {
            fill_0015C670(pTask, pInput, start, 1);
            return 0;
        } else {
            p = points;
            {
                s32 n = 0;
                Point_0015C670 *q = p;
                do {
                    q->x = q->y = 0xF;
                    q++;
                    n++;
                } while (n < 12);
            }
            {
                s32 position = source->position;
                u16 card = (u16)TaLogic_GetWarnHideLvl_0015D120(nSide);
                TaLogic_GetInvadeRoot(position >> 8, position & 0xFF, points,
                    startX, startY, targetX = target & 0xFF,
                    targetY = target >> 8, target_0015C670(pTask, mode),
                    0, 30, card);
            }
            count = TaLogic_GetMinGoalCount((u8 *)points);
            bestIndex = 0xFF;
            if (count > 0) {
                bestScore = 0;
                for (i = 0; i < count; i++, p++) {
                    if (SzDuel_GetMapUnit(p->x, p->y) == 0) {
                        s32 score = TaLogic_GetUnitWarning(p->x, p->y, nSide, 3, 1,
                            TaLogic_GetWarnHideLvl_0015D120(nSide) & 0xFF);
                        if (bestScore < score) {
                            bestScore = score;
                            bestIndex = i;
                        } else if (score == bestScore) {
                            if (MAX_0015C670(p->x, targetX) - MIN_0015C670(p->x, targetX)
                                    + (MAX_0015C670(p->y, targetY) - MIN_0015C670(p->y, targetY))
                                    < MAX_0015C670(points[bestIndex].x, targetX) - MIN_0015C670(points[bestIndex].x, targetX)
                                    + (MAX_0015C670(points[bestIndex].y, targetY) - MIN_0015C670(points[bestIndex].y, targetY))) {
                                bestScore = score;
                                bestIndex = i;
                            }
                        }
                    }
                }
            } else {
                fill_0015C670(pTask, pInput, start, 1);
                return 0;
            }
            if (bestIndex != 0xFF) {
                action->position = source->position;
                action->action = 6;
                action->target = (points[bestIndex].y << 8) | points[bestIndex].x;
                action->result = TaLogic_IsDefStyleUnit(source->position >> 8,
                    source->position & 0xFF, action->target, 0, 0);
            } else {
                fill_0015C670(pTask, pInput, start, 1);
                return 0;
            }
        }
    }
    return 0;
}

/* Whether this duelist opens (turns face up) unit (nSide, nID) now: 0 no, 1 or 2 by its kind. */
s32 TaLogic_IsOpenUnit_0015CBB0(s32 nSide, s32 nID) {
    s32 kind;
    s32 pos;
    s32 slot;
    u32 *card;

    kind = SzDuel_GetUnitCardNo();
    pos = SzDuel_GetUnitLoc(nSide, nID);
    slot = Ta_IsUnitControl(nSide, nID);
    card = SzDuel_GetUnitEffect(nSide, nID, 0);
    if (SzDuel_GetUnitStatus(nSide, nID, 4) != 0) {
        return 0;
    }
    switch (SzDuel_GetUnitKind(nSide, nID) >> 5) {
    case 0:
        switch (kind) {
        case 0xE0:
            if (SzDuel_GetSummonPower(slot) < 2) {
                return 1;
            }
            break;
        case 0x28C:
            if (Ta_GetUnitNumFrom22bitFlagList(SearchUnitByRange(pos & 0xFF, pos >> 8, slot, 1, 0x34, 0x14)) > 1) {
                return 2;
            }
            if (Ta_GetUnitNumFrom22bitFlagList(SearchUnitByRange(pos & 0xFF, pos >> 8, slot, 2, 0x34, 0x14)) > 5) {
                return 1;
            }
            break;
        case 0x28F:
            if (Ta_GetUnitNumFrom22bitFlagList(SearchUnitByRange(0, 0, nSide, 2, 0x34, 0xE)) > 5) {
                return 1;
            }
            break;
        }
        return 2;
    case 5:
        if (TaLogic_GetActionReaction(nSide, nID, 0, 0, 6, 0) == 5) {
            return 2;
        }
        if (TaLogic018_IsDoCerem(Ta_IsUnitControl(nSide, nID), kind) == 1 &&
            SzDuel_GetField(pos & 0xFF, pos >> 8) != 9) {
            return 1;
        }
        break;
    case 1:
        if (TaLogic_GetActionReaction(nSide, nID, 0, 0, 6, 0) == 5) {
            return 2;
        }
        if (card == NULL) {
            return 2;
        }
        switch (*card >> 8) {
        case 0x18:
            if (Ta_GetUnitNumFrom22bitFlagList(SearchUnitByRange(0, 0, nSide, 2, 0x34, 0xE)) > 5) {
                return 1;
            }
            break;
        case 0x12:
            if (Ta_GetUnitNumFrom22bitFlagList(SearchUnitByRange(pos & 0xFF, pos >> 8, slot, 1, 0x1D, 0x1D)) > 0) {
                return 2;
            }
            if (Ta_GetUnitNumFrom22bitFlagList(SearchUnitByRange(0, 0, slot, 1, 0x13, 0xE)) > 2) {
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
static inline s32 max_0015CF30(s32 a, s32 b) {
    if (b < a) {
        return a;
    }
    return b;
}

/* Whether unit (nSide, nID) may open while moving from (nX, nZ) to the square next to it, (gX, gZ). */
s32 TaLogic018_IsOpenMoveUnit(s32 nSide, s32 nID, s32 nX, s32 nZ, s32 gX, s32 gZ) {
    s32 minY;
    s32 minX;

    minY = (nZ < gZ) ? nZ : gZ;
    gZ = max_0015CF30(nZ, gZ);
    minX = (nX < gX) ? nX : gX;
    gX = max_0015CF30(nX, gX);

    if (((gX - minX) + (gZ - minY)) != 2) {
        return 0;
    }
    if (SzDuel_GetUnit(nSide, nID) == 0) {
        return 0;
    }
    if (SzDuel_GetUnitStatus(nSide, nID, 0) == 0) {
        return (CheckLandAgreement2(SzDuel_GetField(nX, nZ), nSide, nID) != 1) ? 0 : 1;
    }
    return 0;
}

/* Whether side `nSide` can play ritual card `nCardNo` now (it has the units to give up). */
s32 TaLogic018_IsDoCerem(s32 nSide, s32 nCardNo) {
    s32 data[4];
    s32 index;
    s32 mask;
    s32 low;
    s32 high;
    s32 value;

    Ta_GetCeremSacrifice(data, *(s32 *)((u8 *)TaHand_GetCardEffect(nCardNo, 0) + 4));
    if ((mask = Ta_GetSacrificeUnit(data, nSide)) < 0) {
        return 0;
    }
    for (index = 0; index < Ta_GetUnitNumFrom22bitFlagList(mask); index++) {
        value = Ta_GetUnitOwnerIDFromLstCount(mask, index);
        high = value >> 8;
        low = value & 0xFF;
        value = SzDuel_GetUnitLoc(high, low);
        if (TaUtil_GetUnitAP(high, low, value & 0xFF, value >> 8) >= 0) {
            return 0;
        }
    }
    return 1;
}

/* How careful this duelist is about hidden cards (by its life points and monster count). */
s32 TaLogic_GetWarnHideLvl_0015D120(s32 nSide) {
    if (SzDuel_GetLP(nSide) > 0x4B0) {
        if (SzDuel_GetUnitMonsterCount(nSide) >= 5) {
            return 0x2EE;
        } else {
            return 0x5DC;
        }
    } else {
        return 0x7D0;
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
} Req_0015D180;

typedef struct {
    u8 pad0[0x160];
    u16 list[32];    /* 0x160 */
    u8 idx : 5;      /* 0x1A0 */
    u8 pad1A0 : 3;
    u8 pad1A1;
    u16 count;       /* 0x1A2 */
} Work_0015D180;

s32 TaLogic_GetInputQueFromMinimumTask_b(void *, void *, s32);

/* Computer duelist 18's controller (duelistControllers[18]): the buttons it presses this frame. With an empty
   input queue it plans its next task and turns it into buttons, then plays the queue back one button per frame;
   after 600 frames it gives up the turn (0x20, then 0x800). */
s32 duelistController18(s32 wCursorPos, void *pCtl) {
    Req_0015D180 req;
    Work_0015D180 *w;
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
        if (TaLogic_GetMinimumTask_00158C80(w, &req, wCursorPos) == 0) {
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

#pragma conditional_move off

/* This duelist's move: picks the next unit to act, gives it a task and turns that into input `pInput`; returns 1
   when it set one. */
s32 TaLogic_GetMinimumTask_0015D350(void *pCtl, void *pInput, s32 wCursorPos) {
    u16 *tasks = pCtl;
    s32 side;
    s32 found;
    s32 result;
    s32 index;

    side = SzDuel_GetTurnOwner();
    found = 0;
    if ((result = TaLogic_GetNextActiveUnit_0015DAF0(tasks, side, (s32)pInput)) < 0) {
        return 0;
    }
    index = TaLogic_GetActionUnitFromOwnerID(tasks, result & 0xFFFF);
    if (index < 0) {
        return 0;
    }
    if ((result >> 16) == 1) {
        if (((tasks[index * 8 + 2] >> 8) & 0xFF) == 10) {
            TaLogic_InitRogicControl(tasks + index * 8, 1);
        } else {
            TaLogic_InitRogicControl(tasks + index * 8, 0);
        }
        return 1;
    }
    TaLogic_CommandUnit_0015D8E0(tasks + index * 8);
    switch ((tasks[index * 8 + 2] >> 8) & 0xFF) {
    case 5:
        if (SzDuel_GetUnitStatus(tasks[index * 8] >> 8, tasks[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_RunMission_001607D0(tasks + index * 8, side, pInput, 1);
            found = 1;
        }
        break;
    case 2:
        if (SzDuel_GetUnitStatus(tasks[index * 8] >> 8, tasks[index * 8] & 0xFF, 0) == 0) {
            if (TaLogic_GetMinimumTask_AtkMission_00160DA0(tasks + index * 8, side, pInput, 1) < 0) {
                TaLogic_InitRogicControl(tasks + index * 8, 1);
                return 1;
            }
            found = 1;
        }
        break;
    case 10:
        if (TaLogic_GetMinimumTask_Summon_0015F300(tasks[index * 8], side, (s32)pInput) < 0) {
            TaLogic_InitRogicControl(tasks + index * 8, 1);
            *(u8 *)((u8 *)pInput + 2) = 0xFF;
            *(s32 *)((u8 *)pInput + 0xC) = 0;
        } else {
            TaLogic_InitRogicControl(tasks + index * 8, 1);
            found = 1;
        }
        break;
    case 6:
    case 15:
    case 16:
        if (SzDuel_GetUnitStatus(tasks[index * 8] >> 8, tasks[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_MoveMission_00161380(tasks + index * 8, side, pInput, 1, 0);
            found = 1;
        }
        break;
    case 3:
        if (SzDuel_GetUnitStatus(tasks[index * 8] >> 8, tasks[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_MoveMission_00161380(tasks + index * 8, side, pInput, 1, 1);
            found = 1;
        }
        break;
    case 9:
        TaLogic_GetMinimumTask_EncMission(tasks + index * 8, side, pInput, 1, 0, TaLogic_GetWarnHideLvl_00162580(side), 5, 1);
        found = 1;
        break;
    case 13:
        TaLogic_GetMinimumTask_RevoltMission_00161EA0(tasks + index * 8, side, pInput, 1);
        found = 1;
        break;
    case 12:
        TaLogic_GetMinimumTask_ReviveMission_00161BF0(tasks + index * 8, side, pInput, 1);
        found = 1;
        break;
    case 14:
        TaLogic_GetMinimumTask_DoNone(tasks + index * 8, side, pInput);
        found = 1;
        break;
    default:
        found = 0;
        break;
    }
    if (found == 1) {
        return 1;
    }
    switch (tasks[index * 8 + 2] & 0xFF) {
    case 5:
        if (SzDuel_GetUnitStatus(tasks[index * 8] >> 8, tasks[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_RunMission_001607D0(tasks + index * 8, side, pInput, 0);
            found = 1;
        }
        break;
    case 2:
        if (SzDuel_GetUnitStatus(tasks[index * 8] >> 8, tasks[index * 8] & 0xFF, 0) == 0) {
            if (TaLogic_GetMinimumTask_AtkMission_00160DA0(tasks + index * 8, side, pInput, 0) < 0) {
                TaLogic_GetMinimumTask_RunMission_001607D0(tasks + index * 8, side, pInput, 0);
            }
            found = 1;
        }
        break;
    case 10:
        if (TaLogic_GetMinimumTask_Summon_0015F300(tasks[index * 8], side, (s32)pInput) < 0) {
            TaLogic_InitRogicControl(tasks + index * 8, 0);
            *(u8 *)((u8 *)pInput + 2) = 0xFF;
            found = 1;
            *(s32 *)((u8 *)pInput + 0xC) = 0;
        } else {
            TaLogic_InitRogicControl(tasks + index * 8, 0);
            found = 1;
        }
        break;
    case 6:
    case 15:
    case 16:
        if (SzDuel_GetUnitStatus(tasks[index * 8] >> 8, tasks[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_MoveMission_00161380(tasks + index * 8, side, pInput, 0, 0);
            found = 1;
        }
        break;
    case 3:
        if (SzDuel_GetUnitStatus(tasks[index * 8] >> 8, tasks[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_MoveMission_00161380(tasks + index * 8, side, pInput, 0, 1);
            found = 1;
        }
        break;
    case 9:
        TaLogic_GetMinimumTask_EncMission(tasks + index * 8, side, pInput, 0, 0, TaLogic_GetWarnHideLvl_00162580(side), 5, 1);
        found = 1;
        break;
    case 13:
        TaLogic_GetMinimumTask_RevoltMission_00161EA0(tasks + index * 8, side, pInput, 0);
        found = 1;
        break;
    case 12:
        TaLogic_GetMinimumTask_ReviveMission_00161BF0(tasks + index * 8, side, pInput, 0);
        found = 1;
        break;
    case 14:
        TaLogic_GetMinimumTask_DoNone(tasks + index * 8, side, pInput);
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

/* Gives a unit of this duelist its order for this turn (attack, run, move, summon, guard). */
s32 TaLogic_CommandUnit_0015D8E0(void *pCtl) {
    u16 card;
    s32 low;
    s32 controllingSide;
    s32 type;

    card = *(u16 *)pCtl;
    SzDuel_GetUnitLoc(card >> 8, card & 0xFF);
    card = *(u16 *)pCtl;
    controllingSide = Ta_IsUnitControl(card >> 8, card & 0xFF);
    card = *(u16 *)pCtl;
    if (SzDuel_GetUnit(card >> 8, card & 0xFF) != 0) {
        card = *(u16 *)pCtl;
        if (SzDuel_GetUnitStatus(card >> 8, card & 0xFF, 0) == 0) {
            card = *(u16 *)pCtl;
            if (card != 0xFFFF) {
                low = card & 0xFF;
                if (low == 0) {
                    if (*(s32 *)((u8 *)pCtl + 8) == -1) {
                        if (TaLogic_IsAttackedNow(card >> 8, low, 0) == 1) {
                            if (SzDuel_InqHandPhase(*(u16 *)pCtl >> 8) == 1) {
                                *(s16 *)((u8 *)pCtl + 4) = 0x50A;
                            } else {
                                *(s16 *)((u8 *)pCtl + 4) = 0x5FF;
                            }
                        } else {
                            if (SzDuel_InqHandPhase(*(u16 *)pCtl >> 8) == 1) {
                                *(s16 *)((u8 *)pCtl + 4) = 0xA05;
                            } else {
                                *(s16 *)((u8 *)pCtl + 4) = 0x5FF;
                            }
                        }
                    }
                } else {
                    type = SzDuel_GetUnitKind(card >> 8, low) >> 5;
                    switch (type) {
                    case 0:
                        card = *(u16 *)pCtl;
                        if (TaUtil_IsExMonster(card >> 8, card & 0xFF) == 1) {
                            TaLogic019_CommandEfcMonster(pCtl);
                        } else {
                            TaLogic019_CommandBtlUnit(pCtl);
                        }
                        break;
                    case 2:
                        TaLogic_CommandEncUnit(pCtl, 5, 0, TaLogic_GetWarnHideLvl_00162580(controllingSide) & 0xFF);
                        break;
                    case 1:
                    case 3:
                    case 4:
                        TaLogic019_CommandSpellUnit(pCtl);
                        break;
                    default:
                        *(s16 *)((u8 *)pCtl + 4) = 0x5FF;
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
s32 TaLogic_GetNextActiveUnit_0015DAF0(u16 *pCtl, s32 nSide, s32 pInput) {
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
    TaLogic_CommandUnit_0015D8E0(pCtl + idx * 8);
    if (((pCtl[idx * 8 + 2] >> 8) & 0xFF) == 10) {
        if (SzDuel_InqHandPhase(nSide) == 1 && TaLogic_GetMinimumTask_Summon_0015F300(pos, nSide, pInput) >= 0) {
            return pos | 0x10000;
        }
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_GetUnitStatus(nSide, 0, 0) == 0) {
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_InqHandPhase(nSide) == 1 && TaLogic_GetMinimumTask_Summon_0015F300(pos, nSide, pInput) >= 0) {
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

typedef struct Action_0015DED0 {
    u16 location;
    u16 unk2;
    s16 state;
    u16 unk6;
    union {
        u32 value;
        u16 low;
    } data;
} Action_0015DED0;


/* Orders a fighting unit (task `pTask`): straight at its goal when the path is open, else the nearest enemy it can
   beat. */
void TaLogic019_CommandBtlUnit(void *pTask) {
    s32 other;
    s32 result;
    Action_0015DED0 *action = pTask;

    if (SzDuel_GetUnit(action->location >> 8, action->location & 0xFF) != 0) {
        other = (Ta_GetCurrentSide(action->location >> 8, action->location & 0xFF) == 0 ? 1 : 0) << 8;
        SzDuel_GetUnitLoc(action->location >> 8, action->location & 0xFF);
        SzDuel_GetUnitLoc(other >> 8, other & 0xFF);
        SzDuel_GetUnit(action->location >> 8, action->location & 0xFF);
        if (SzDuel_GetUnitAP(action->location >> 8, action->location & 0xFF, 0) >= 2500) {
            TaLogic019_CommandAtkUnit(pTask);
            return;
        }
        if (TaLogic019_IsEmptyCntrGuard(action->location >> 8, action->location & 0xFF, 1) == 1) {
            TaLogic019_CommandLineUnit(pTask, 1);
            return;
        }
        result = TaLogic019_IsEmptyTrapGuard(action->location >> 8, action->location & 0xFF);
        if (result >= 0) {
            action->state = 0x6FF;
            action->data.value = (result << 16) | action->data.low;
            return;
        }
        if (TaLogic019_IsEmptyCntrGuard(action->location >> 8, action->location & 0xFF, 2) == 1) {
            TaLogic019_CommandLineUnit(pTask, 2);
            return;
        }
        TaLogic019_CommandAtkUnit(pTask);
    }
}

typedef struct Command_0015E030 {
    u16 position;
    u16 pad2;
    u16 action;
    u16 pad6;
    union {
        u32 value;
        struct {
            u16 low;
            u16 high;
        } halves;
    } data;
} Command_0015E030;

typedef struct Entry_0015E030 {
    u16 position;
    u8 state;
    u8 pad;
} Entry_0015E030;

/* Orders an attacking unit (task `pTask`). */
void TaLogic019_CommandAtkUnit(void *pTask) {
    u8 scratch[0x70];
    Entry_0015E030 entries[23];
    s16 count;
    s16 otherCount;
    Command_0015E030 *command = pTask;
    s32 position;
    s32 destination;
    s32 side;
    s32 unitInfo;
    s32 destinationColumn;
    s32 destinationRow;
    s32 row;
    s32 column;
    s32 otherPosition;
    s32 otherRow;
    s32 attempt;
    s32 i;
    Entry_0015E030 *entry;

    extern void TaLogic_InitIgnoreLst();
    extern s32 TaLogic_IsRootOpen();
    extern s32 TaLogic019_GetNearUnit();

    if (SzDuel_GetUnit(command->position >> 8, command->position & 0xFF) == 0) {
        return;
    }

    side = Ta_GetCurrentSide(command->position >> 8, command->position & 0xFF);
    destination = (side == 0 ? 1 : 0) << 8;
    position = SzDuel_GetUnitLoc(command->position >> 8, command->position & 0xFF);
    destinationRow = destination >> 8;
    destinationColumn = destination & 0xFF;
    otherPosition = SzDuel_GetUnitLoc(destinationRow, destinationColumn);
    unitInfo = SzDuel_GetUnit(command->position >> 8, command->position & 0xFF);
    TaLogic_InitIgnoreLst(scratch);

    entry = entries;
    i = 0;
    do {
        i++;
        entry->position = 0xFFFF;
        entry->state = 0xFF;
        entry++;
    } while (i < 22);

    if (TaLogic_IsRootOpen(command->position >> 8, command->position & 0xFF,
                     column = position & 0xFF, row = position >> 8,
                     destinationRow, destinationColumn,
                     otherPosition & 0xFF, otherRow = otherPosition >> 8, 5) > 0) {
        command->action = 0x2FF;
        command->data.value = (destination << 16) | command->data.halves.low;
        return;
    }

    attempt = 1;
    otherCount = 0;
    count = 0;
    while (1) {
        switch (TaLogic019_GetNearUnit(command, 0, unitInfo, column, row,
                             side == 0 ? 1 : 0, (u8) attempt,
                             TaLogic_GetWarnHideLvl_00162580(side), entries, 0,
                             &count, &otherCount, 5, scratch)) {
        case 3:
            command->action = 0x6FF;
            command->data.value = (position << 16) | command->data.halves.low;
            return;
        case 2:
            command->action = 0x3FF;
            command->data.value = (position << 16) | command->data.halves.low;
            return;
        case 1:
            return;
        case 0:
            command->action = 0x3FF;
            command->data.value = (position << 16) | command->data.halves.low;
            return;
        }
        attempt++;
        if (attempt > 5) {
            break;
        }
    }

    command->action = 0x6FF;
    if (((row <= 3) && (otherRow <= 3)) || ((row > 3) && (otherRow > 3))) {
        command->data.value = (otherPosition << 16) | command->data.halves.low;
    } else {
        command->data.value = (((position & 0xFF) | 0x300) << 16) |
                              command->data.halves.low;
    }
}

/* The guard square for unit (nSide, nID) when its side has card 0x33B in play (0x500 if it already stands there). */
s32 TaLogic019_IsEmptyTrapGuard(s32 nSide, s32 nID) {
    s32 controllingSide;
    s32 controllingSide2;
    s32 controllingSide3;
    s32 unitId;
    s32 unitId2;

    controllingSide3 = Ta_IsUnitControl(nSide, nID);
    if (SearchUnitByRange(0, 0, controllingSide3, 1, 0x033B001C, 14) != 0) {
        unitId = SzDuel_GetMapUnitID(0, 5);
        if (unitId >= 0) {
            if (unitId == ((nSide << 8) | nID)) {
                return 0x500;
            }
            controllingSide2 = Ta_IsUnitControl(unitId >> 8, unitId & 0xFF);
            if (controllingSide2 != Ta_IsUnitControl(nSide, nID)) {
                return 0x500;
            }
        } else {
            return 0x500;
        }
    }
    if (SearchUnitByRange(0, 0, controllingSide3, 1, 0x02ED001C, 14) != 0) {
        unitId2 = SzDuel_GetMapUnitID(6, 3);
        if (unitId2 >= 0) {
            if (unitId2 == ((nSide << 8) | nID)) {
                return 0x306;
            }
            controllingSide = Ta_IsUnitControl(unitId2 >> 8, unitId2 & 0xFF);
            if (controllingSide != Ta_IsUnitControl(nSide, nID)) {
                return 0x306;
            }
        } else {
            return 0x306;
        }
    }
    return -1;
}

/* The centre square guard unit (nSide, nID) should hold (`nMode` 1 scans 3 squares, else 4). */
s32 TaLogic019_IsEmptyCntrGuard(s32 nSide, s32 nID, s32 nMode) {
    s32 otherType;
    s32 card;
    s32 i;
    s32 mode;
    s32 key;

    if ((nMode & 0xFF) == 1) {
        mode = 3;
    } else {
        mode = 4;
    }
    key = (nSide << 8) | nID;
    i = 1;
    do {
        card = SzDuel_GetMapUnitID(i, mode);
        if (card != 0) {
            if (card == key) {
                return 1;
            }
            otherType = Ta_IsUnitControl(card >> 8, card & 0xFF);
            if (otherType == Ta_IsUnitControl(nSide, nID)) {
                return 0;
            }
        }
        i++;
        if (i > 5) {
            return 1;
        }
    } while (1);
}

typedef struct {
    u16 position;
    u8 flag;
    u8 pad;
} Slot_0015E520;

/* Orders a unit (task `pTask`) to hold its line of the board. */
void TaLogic019_CommandLineUnit(void *pTask, s32 nMode) {
    u8 work[112];
    Slot_0015E520 slots[22];
    s16 b;
    s16 a;
    s32 i;
    s32 target;
    s32 player;
    s32 enemy;
    s32 position;
    s32 enemyPos;
    s32 owner;
    u16 *record = pTask;
    extern s32 TaLogic_IsRootOpen();
    extern s32 TaLogic019_GetNearUnit();
    extern void TaLogic_InitIgnoreLst();

    if ((nMode & 0xFF) == 1) {
        target = 3;
    } else {
        target = 4;
    }
    SzDuel_GetUnitLoc((s32) record[0] >> 8, record[0] & 0xFF);
    if (SzDuel_GetUnit((s32) record[0] >> 8, record[0] & 0xFF) != 0) {
        player = Ta_GetCurrentSide((s32) record[0] >> 8, record[0] & 0xFF);
        enemy = (player == 0 ? 1 : 0) << 8;
        position = SzDuel_GetUnitLoc((s32) record[0] >> 8, record[0] & 0xFF);
        enemyPos = SzDuel_GetUnitLoc(enemy >> 8, enemy & 0xFF);
        owner = SzDuel_GetUnit((s32) record[0] >> 8, record[0] & 0xFF);
        TaLogic_InitIgnoreLst(work);
        for (i = 0; i < 22; i++) {
            slots[i].position = 0xFFFF;
            slots[i].flag = 0xFF;
        }
        if (TaLogic_IsRootOpen((s32) record[0] >> 8, record[0] & 0xFF, position & 0xFF, position >> 8,
                          enemy >> 8, enemy & 0xFF, enemyPos & 0xFF, enemyPos >> 8, 2) > 0) {
            record[2] = 0x2FF;
            *(u32 *) (record + 4) = (enemy << 16) | record[4];
            return;
        }
        a = 0;
        b = 0;
        i = 1;
        while (1) {
            switch (TaLogic019_GetNearUnit(record, 0, owner, position & 0xFF, position >> 8,
                                  Ta_GetCurrentSide((s32) record[0] >> 8, record[0] & 0xFF) == 0 ? 1 : 0, (u8) i,
                                  TaLogic_GetWarnHideLvl_00162580(player), slots, 0, &b, &a, 2, work)) {
            case 3:
                record[2] = 0x6FF;
                *(u32 *) (record + 4) = (position << 16) | record[4];
                return;
            case 2:
                record[2] = 0x3FF;
                *(u32 *) (record + 4) = (position << 16) | record[4];
                return;
            case 1:
                return;
            case 0:
                record[2] = 0x3FF;
                *(u32 *) (record + 4) = (position << 16) | record[4];
                return;
            }
            i++;
            if (i > 2) {
                break;
            }
        }
        if ((position >> 8) == target) {
            switch ((u8) (record[2] >> 8)) {
            case 16:
                if ((position & 0xFF) > 1) {
                    *(u32 *) (record + 4) = ((position >> 8) << 24) | record[4];
                } else {
                    record[2] = 0xFFF;
                    *(u32 *) (record + 4) = ((((position >> 8) << 8) | 5) << 16) | record[4];
                }
                break;
            case 15:
                if ((position & 0xFF) < 5) {
                    *(u32 *) (record + 4) = ((((position >> 8) << 8) | 5) << 16) | record[4];
                } else {
                    record[2] = 0x10FF;
                    *(u32 *) (record + 4) = ((((position >> 8) << 8) | 1) << 16) | record[4];
                }
                break;
            default:
                if (func_0019A5C8() % 2 == 0) {
                    record[2] = 0x10FF;
                    *(u32 *) (record + 4) = ((((position >> 8) << 8) | 1) << 16) | record[4];
                } else {
                    record[2] = 0xFFF;
                    *(u32 *) (record + 4) = ((((position >> 8) << 8) | 5) << 16) | record[4];
                }
                break;
            }
            return;
        }
        record[2] = 0x6FF;
        *(u32 *) (record + 4) = record[4] | (((target << 8) | (position & 0xFF)) << 16);
    }
}

/* TaLogic_GetNearUnit with this duelist's view and strength settings. */
void TaLogic019_GetNearUnit(s32 pTask, s32 pTree, s32 pVarInfo, s32 nX, s32 nZ, s32 eSide, s32 bDist, s32 WarnLvl, s32 nUnitLst, u16 wUnitNum, s32 wSize, s32 wNodeCount, u8 bChase, s32 wIgnoreLst) {
    TaLogic_GetNearUnit(pTask, pTree, pVarInfo, nX, nZ, eSide, bDist, WarnLvl,
                  nUnitLst, wUnitNum, wSize, wNodeCount, bChase,
                  0, 2500, wIgnoreLst);
}

typedef struct Entry_0015E950 {
    u16 position;
    u8 kind;
    u8 pad;
} Entry_0015E950;


/* Orders an effect monster (task `pTask`): where its effect does most. */
void TaLogic019_CommandEfcMonster(void *pTask) {
    extern s32 SzDuel_GetUnitCardNo();
    extern s32 TaLogic_GetNearUnitL2();
    extern void TaLogic_InitIgnoreLst();
    s32 destination;
    u8 buffer[112];
    Entry_0015E950 entries[22];
    u16 outputA;
    u16 outputB;
    u16 count;
    s32 checkOwner;
    s32 retryX;
    s32 value;
    s32 owner;
    s32 unitInfo;
    s32 cursor;
    s32 index;
    s32 retryY;
    s32 attempt;
    s32 x;
    s32 y;
    s32 position;
    s32 other;
    s32 same;
    s32 i;
    s32 result;
    Entry_0015E950 *entry;
    u16 location;

    location = *(u16 *)pTask;
    owner = Ta_IsUnitControl(location >> 8, location & 0xFF);
    location = *(u16 *)pTask;
    value = SzDuel_GetUnitCardNo(location >> 8, location & 0xFF);
    location = *(u16 *)pTask;
    unitInfo = SzDuel_GetUnit(location >> 8, location & 0xFF);
    location = *(u16 *)pTask;
    destination = SzDuel_GetUnitLoc(location >> 8, location & 0xFF);
    entry = entries;
    count = 0;
    outputB = 0;
    outputA = 0;
    i = 0;
    do {
        i++;
        entry->position = 0xFFFF;
        entry->kind = 0xFF;
        entry++;
    } while (i < 22);
    TaLogic_InitIgnoreLst(buffer);
    cursor = 0;
    switch (value) {
    case 0x2B:
        location = *(u16 *)pTask;
        if (SzDuel_GetUnitStatus(location >> 8, location & 0xFF, 4) != 0) {
            break;
        }
        *(u16 *)((u8 *)pTask + 4) = 0xCFF;
        *(u32 *)((u8 *)pTask + 8) = (destination << 16) | *(u16 *)((u8 *)pTask + 8);
        return;
    case 0x57:
        TaLogic019_CommandAtkUnit(pTask);
        return;
    case 0x129:
        location = *(u16 *)pTask;
        index = 1;
        y = location & 0xFF;
        x = location >> 8;
        position = (x << 8) | y;
        while (1) {
            other = SzDuel_GetMapUnitID(index, 3);
            if (other != 0) {
                if (other == position) {
                    same = 1;
                    break;
                }
                checkOwner = Ta_IsUnitControl(other >> 8, other & 0xFF);
                if (checkOwner == Ta_IsUnitControl(x, y)) {
                    same = 0;
                    break;
                }
            }
            index++;
            if (index > 5) {
                same = 1;
                break;
            }
        }
        if (same == 1) {
            TaLogic019_CommandLineUnit(pTask, 1);
            return;
        }
        retryX = destination >> 8;
        retryY = destination & 0xFF;
        attempt = 1;
        while (1) {
            result = TaLogic_GetWarnHideLvl_00162580(owner);
            cursor = TaLogic_GetNearUnitL2(cursor, unitInfo, retryY, retryX, owner == 0 ? 1 : 0, (u8)attempt, 0, result,
                                  entries, &count, &outputA, &outputB, buffer);
            result = TaLogic_GetNearUnitL3((void *)unitInfo, retryY, retryX, entries, 2, 0x34, 0, 2, 0,
                                  TaLogic_GetWarnHideLvl_00162580(owner), count);
            if (result >= 0) {
                *(u16 *)((u8 *)pTask + 4) = 0x2FF;
                *(u32 *)((u8 *)pTask + 8) = (result << 16) | *(u16 *)((u8 *)pTask + 8);
                return;
            }
            attempt++;
            if (attempt > 2) {
                break;
            }
        }
        location = *(u16 *)pTask;
        TaLogic019_CommandLDGuardUnit(location >> 8, location & 0xFF, pTask);
        return;
    }
    TaLogic019_CommandBtlUnit(pTask);
}

typedef struct {
    u32 field0;
    u16 field4;
    u16 field6;
    union {
        u32 word;
        struct {
            u32 lower : 16;
            u32 upper : 16;
        } bits;
    } field8;
} Item_0015EC60;


/* Sets a task to move (0x3FF) to square `index`. */
static inline void set_index_0015EC60(void *arg, s32 index) {
    Item_0015EC60 *item = arg;

    item->field4 = 0x3FF;
    item->field8.word = (index << 16) | item->field8.bits.lower;
}

/* Orders a guard unit (nSide, nID): to the next free line square, else fight (into `pTask`). */
void TaLogic019_CommandLDGuardUnit(s32 nSide, s32 nID, void *pTask) {
    Item_0015EC60 *item = pTask;
    s32 index;
    s32 next;

    Ta_IsUnitControl(nSide, nID);
    index = SzDuel_GetUnitLoc(nSide, nID);
    if (TaLogic019_IsLinePoint(index & 0xFF, index >> 8) == 1) {
        set_index_0015EC60(item, index);
    } else {
        set_index_0015EC60(item, index);
    }
    next = TaLogic019_GetEmptyLine();
    if (next >= 0) {
        set_index_0015EC60(item, next);
    } else {
        TaLogic019_CommandBtlUnit(item);
    }
}

/* Whether (nX, nZ) is one of this duelist's four line squares. */
s32 TaLogic019_IsLinePoint(s32 nX, s32 nZ) {
    s32 var_s0;

    var_s0 = 0;
loop_1:
    if (((nZ << 8) | nX) == TaLogic019_GetLine(var_s0)) {
        return 1;
    }
    var_s0 += 1;
    if (var_s0 >= 4) {
        return 0;
    }
    goto loop_1;
}

/* Line square `nNo` (0..3) of this duelist (from its summon preferences), or -1. */
s32 TaLogic019_GetLine(s32 nNo) {
    extern s32 TaLogic_GetSommonPiecePreference_001604A0();
    s32 temp;

    temp = SzDuel_GetTurnOwner();
    switch (nNo) {
    case 0:
        return TaLogic_GetSommonPiecePreference_001604A0(temp, 0);
    case 1:
        return TaLogic_GetSommonPiecePreference_001604A0(temp, 3);
    case 2:
        return TaLogic_GetSommonPiecePreference_001604A0(temp, 4);
    case 3:
        return TaLogic_GetSommonPiecePreference_001604A0(temp, 5);
    }
    return -1;
}

/* Line square `slot` (0..3) of this duelist, or -1. */
static inline s32 slot_pos_0015EE40(s32 slot) {
    extern s32 TaLogic_GetSommonPiecePreference_001604A0();
    s32 temp;

    temp = SzDuel_GetTurnOwner();
    switch (slot) {
    case 0:
        return TaLogic_GetSommonPiecePreference_001604A0(temp, 0);
    case 1:
        return TaLogic_GetSommonPiecePreference_001604A0(temp, 3);
    case 2:
        return TaLogic_GetSommonPiecePreference_001604A0(temp, 4);
    case 3:
        return TaLogic_GetSommonPiecePreference_001604A0(temp, 5);
    }
    return -1;
}

/* Whether square `pos` is free. */
static inline s32 is_free_0015EE40(s32 pos) {
    return SzDuel_GetMapUnit(pos & 0xFF, pos >> 8) == 0 ? 1 : 0;
}

/* The free line of the board this duelist's units fill next. */
s32 TaLogic019_GetEmptyLine(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (is_free_0015EE40(TaLogic019_GetLine(i)) == 1) {
            return slot_pos_0015EE40(i);
        }
    }
    return -1;
}

typedef struct {
    u16 id;
    u16 unk2;
    s16 action;
    u16 unk6;
    u32 data;
} Command_0015EF40;


/* Scans the squares from unit `source` along its row for units of its side (`mode` sets how far). */
static inline s32 check_0015EF40(u16 source, s32 mode) {
    s32 id;
    s32 low;
    s32 high;
    s32 i;
    s32 other_card;
    s32 other;

    i = 1;
    low = source & 0xFF;
    high = (s32)source >> 8;
    id = (high << 8) | low;
    while (1) {
        other = SzDuel_GetMapUnitID(i, mode);
        if (other != 0) {
            if (other == id) {
                return 1;
            }
            other_card = Ta_IsUnitControl(other >> 8, other & 0xFF);
            if (other_card == Ta_IsUnitControl(high, low)) {
                return 0;
            }
        }
        i++;
        if (i > 5) {
            break;
        }
    }
    return 1;
}

/* Orders a face-down magic card (task `pTask`): whether and where to open it. */
void TaLogic019_CommandSpellUnit(void *pTask) {
    extern s32 SzDuel_GetUnitCardNo();
    Command_0015EF40 *cmd = pTask;
    s32 flags;
    s32 card_id;
    s32 card;
    u32 *effect;
    s32 position;
    s32 result;

    flags = SzDuel_GetUnitKind((s32)cmd->id >> 8, cmd->id & 0xFF) & 0xFF;
    card_id = SzDuel_GetUnitCardNo((s32)cmd->id >> 8, cmd->id & 0xFF);
    card = Ta_IsUnitControl((s32)cmd->id >> 8, cmd->id & 0xFF);
    effect = Ta_GetUnitEffect((s32)cmd->id >> 8, cmd->id & 0xFF, 0);
    position = SzDuel_GetUnitLoc((s32)cmd->id >> 8, cmd->id & 0xFF);
    if (effect == NULL) {
        cmd->action = 0x5FF;
        return;
    }

    switch ((flags & 0xFF) >> 5) {
    case 1:
        switch (*effect >> 8) {
        case 20:
            cmd->action = 0xCFF;
            return;
        case 4:
            result = TaLogic019_GetUseThunderBolt(card);
            if (result >= 0) {
                cmd->action = 0x6FF;
                cmd->data = *(u16 *)&cmd->data |
                    ((((position >> 8) << 8) |
                      (SzDuel_GetUnitLoc(result >> 8, result & 0xFF) & 0xFF)) << 16);
                return;
            }
            cmd->action = 0x5FF;
            return;
        case 37:
            if (card_id == 0x2ED) {
                cmd->action = 0x6FF;
                cmd->data = *(u16 *)&cmd->data | 0x04060000;
                return;
            }
            if (TaLogic_CommandGunnerUnit(pTask, 0) == 1) {
                cmd->action = 0xBFF;
                return;
            }
            break;
        case 31:
            if (card_id == 0x2DC) {
                cmd->action = 0xDFF;
                return;
            }
            break;
        }
        break;
    case 3:
    case 4:
        if (card_id == 0x2ED) {
            cmd->action = 0x6FF;
            cmd->data = *(u16 *)&cmd->data | 0x06000000;
            return;
        }
        if (check_0015EF40(cmd->id, 3) == 1) {
            TaLogic019_CommandLineUnit(pTask, 1);
            return;
        }
        result = TaLogic019_IsEmptyTrapGuard((s32)cmd->id >> 8, cmd->id & 0xFF);
        if (result >= 0) {
            u32 low;
            cmd->action = 0x6FF;
            low = *(u16 *)&cmd->data;
            cmd->data = (result << 16) | low;
            return;
        }
        if (check_0015EF40(cmd->id, 4) == 1) {
            TaLogic019_CommandLineUnit(pTask, 2);
            return;
        }
        if (TaLogic_CommandGunnerUnit(pTask, 0) == 1) {
            cmd->action = 0xBFF;
            return;
        }
        break;
    }
    cmd->action = 0x5FF;
}

typedef struct {
    s16 card;
    u8 f2;
    u8 pad3;
    s16 f4;
    u8 pad6[6];
    s32 fC;
} Act_0015F300;

typedef struct {
    u8 pad0[0x3C];
    u16 id;
    u8 pad3E[0x22];
} Card_0015F300;


/* The summon task for side `nSide`: which hand cards to play and where, into `pInput`; -1 when it plays none. */
s32 TaLogic_GetMinimumTask_Summon_0015F300(s32 wUnit, s32 nSide, s32 pInput) {
    extern s32 TaLogic_GetUnitNum();
    Card_0015F300 buf;
    s32 res;
    s32 type;
    Act_0015F300 *act = (Act_0015F300 *)pInput;
    s32 card;
    s32 r;

    act->card = wUnit;
    if (SzDuel_InqHandPhase(nSide) == 0) {
        return -1;
    }
    if (TaLogic_GetUnitNum(nSide, 0) == 5 && TaLogic_GetUnitNum(nSide, 1) == 5) {
        return -1;
    }
    type = TaLogic019_IsHandPlay(nSide, &buf);
    if (type < 0) {
        return -1;
    }
    act->f2 = 10;
    act->fC = 2;
    card = SzDuel_GetUnitLoc(wUnit >> 8, wUnit & 0xFF);
    if (type == 0) {
        if (TaLogic019_SetComboQue(nSide, (u8 *)act, &buf) >= 0) {
            res = TaLogic_GetNearCard2(&buf, card & 0xFF, card >> 8, nSide == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, TaLogic_GetWarnHideLvl_00162580(nSide));
            if (res < 0) {
                if (SzDuel_GetUnitMonsterCount(nSide) < 5) {
                    r = TaLogic019_GetSummonPiece(nSide, (u8)type, &buf, res);
                    if (r < 0) {
                        return -1;
                    }
                    act->f4 = r;
                    return 1;
                }
            } else {
                r = TaLogic019_GetSummonPiece(nSide, (u8)type, &buf, res);
                if (r < 0) {
                    return -1;
                }
                act->f4 = r;
                return 1;
            }
        }
    } else {
        res = TaLogic_GetNearCard2(&buf, card & 0xFF, card >> 8, nSide == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, TaLogic_GetWarnHideLvl_00162580(nSide));
    }
    if (type == 2) {
        TaLogic019_SetSpecialComboQue(nSide, act, &buf);
        r = TaLogic019_GetSummonPiece(nSide, (u8)type, &buf, res);
        if (r < 0) {
            return -1;
        }
        act->f4 = r;
        return 1;
    } else if (type == 3) {
        TaLogic019_GetSpecialComboPlay(nSide, act, &buf);
        r = TaLogic019_GetSummonPiece(nSide, (u8)type, &buf, res);
        if (r < 0) {
            return -1;
        }
        act->f4 = r;
        return 1;
    } else {
        if (TaLogic019_GetSpellPlay(nSide, (u8 *)act, &buf, buf.id) < 0) {
            return -1;
        }
        r = TaLogic019_GetSummonPiece(nSide, (u8)type, &buf, res);
        if (r < 0) {
            return -1;
        }
        act->f4 = r;
        return 1;
    }
}

/* Whether side `nSide` should play from its hand this turn (and what, into `pInput`). */
s32 TaLogic019_IsHandPlay(s32 nSide, void *pInput) {
    extern s32 TaLogic_GetUnitNum();
    extern s32 SzDuel_GetUnitCurseRest();
    s32 cards[8];
    u8 buffer[32];
    u8 type0;
    u8 type1;
    s32 result;

    type0 = TaLogic_GetUnitNum(nSide, 0);
    type1 = TaLogic_GetUnitNum(nSide, 1);
    if (pInput == NULL) {
        return -1;
    }
    TaHand_GetNextHand(nSide, cards);
    if (type0 == 5) {
        if (TaLogic019_GetSpellPlay(nSide, buffer, pInput, 999) >= 0) {
            return 1;
        } else {
            return -1;
        }
    } else if (type1 == 5) {
        s32 i;
        s32 *p;

        i = 0;
        if (i < TaHand_GetNextHandNum(nSide)) {
            p = cards;
            do {
                if ((TaHand_GetCardKind(*p) >> 5) == 0 &&
                    TaHand_IsCardSummon2(nSide, *p) == 1) {
                    SzDuel_InitCardInfo(pInput, cards[i]);
                    return 0;
                }
                p++;
                i++;
            } while (i < TaHand_GetNextHandNum(nSide));
        }
        return -1;
    }

    if (TaLogic019_GetSpecCardPlay(nSide, buffer, pInput, 0x341) >= 0) {
        if (TaLogic019_IsDoCerem(nSide, 0x341) == 1) {
            return 2;
        }
    }
    if (TaLogic019_GetSpecCardPlay(nSide, buffer, pInput, 0x355) >= 0) {
        if (TaLogic019_IsDoCerem(nSide, 0x355) == 1) {
            return 2;
        }
    }
    if (TaLogic019_GetUseThunderBolt(nSide) >= 0) {
        if (TaLogic019_GetSpecCardPlay(nSide, buffer, pInput, 0x2BC) >= 0) {
            return 2;
        }
    }
    if (TaLogic019_IsUseGFK(nSide) >= 0) {
        if (TaLogic019_GetSpecCardPlay(nSide, buffer, pInput, 0x2CB) >= 0) {
            return 2;
        }
    }
    if (TaLogic019_IsUseRevive(nSide) >= 0) {
        if (TaLogic019_GetSpecCardPlay(nSide, buffer, pInput, 0x2AD) >= 0) {
            return 2;
        }
    }
    if (TaLogic019_IsUseSaint(nSide) >= 0) {
        if (TaLogic019_GetSpecCardPlay(nSide, buffer, pInput, 0x2B) >= 0) {
            return 2;
        }
    }
    if (TaLogic019_GetSpecialComboPlay(nSide, buffer, pInput) == 1) {
        return 3;
    }
    {
        s32 i;
        i = 0;
        do {
            if (SzDuel_GetUnitCurseRest(nSide, i) != 0 &&
                TaLogic019_GetSpecCardPlay(nSide, buffer, pInput, 0x31C) >= 0) {
                return 2;
            }
            i++;
        } while (i < 11);
    }
    {
        s32 i;
        i = 0;
        do {
            if (SzDuel_GetUnitCurseRest(nSide, i) != 0 &&
                TaLogic019_GetSpecCardPlay(nSide, buffer, pInput, 0x31B) >= 0) {
                return 2;
            }
            i++;
        } while (i < 11);
    }
    {
        s32 *p;
        s32 i;
        i = 0;
        if (i < TaHand_GetNextHandNum(nSide)) {
            p = cards;
            do {
                if ((TaHand_GetCardKind(*p) >> 5) == 0 &&
                    TaHand_IsCardSummon2(nSide, *p) == 1 && *p != 0x129) {
                    SzDuel_InitCardInfo(pInput, cards[i]);
                    return 0;
                }
                p++;
                i++;
            } while (i < TaHand_GetNextHandNum(nSide));
        }
    }
    result = TaLogic019_GetSpellPlay(nSide, buffer, pInput, 999);
    if (result >= 0) {
        return result;
    }
    return -1;
}

/* Whether side `nSide` can play this duelist's special combination now. */
s32 TaLogic019_GetSpecialComboPlay(s32 nSide, void *bCombo, void *pCardInfo) {
    s32 cards[8];
    s32 i;
    s32 found;
    s32 *entry;
    s32 *entry2;
    s32 j;
    s32 found2;
    s32 card;

    TaHand_GetNextHand(nSide, cards);
    i = 0;
    found = 0;
    if (0 < TaHand_GetNextHandNum(nSide)) {
        entry = cards;
        do {
            if (*entry == 0x316) {
                found = 1;
                ((u8 *)bCombo)[6] = i;
            }
            entry++;
            i++;
        } while (i < TaHand_GetNextHandNum(nSide));
    }
    if (found == 0) {
        return -1;
    }
    j = 0;
    found2 = 0;
    if (0 < TaHand_GetNextHandNum(nSide)) {
        entry2 = cards;
        do {
            card = *entry2;
            if ((card == 0x129) && (TaHand_IsCardSummon2(nSide, card) == 1)) {
                ((u8 *)bCombo)[7] = j;
                found2 = 1;
            }
            entry2++;
            j++;
        } while (j < TaHand_GetNextHandNum(nSide));
    }
    if (found2 == 0) {
        return -1;
    }
    SzDuel_InitCardInfo(pCardInfo, 0x129);
    return 1;
}

/* Whether side `nSide` holds card `nCardNo` and can summon it (its slot into `bCombo`, the card into `pCardInfo`);
   returns its kind group or -1. */
s32 TaLogic019_GetSpecCardPlay(s32 nSide, void *bCombo, void *pCardInfo, s32 nCardNo) {
    s32 entries[8];
    s32 index;
    s32 *entry;

    TaHand_GetNextHand(nSide, entries);
    index = 0;
    if (index < TaHand_GetNextHandNum(nSide)) {
        entry = entries;
        do {
            if (((nCardNo & 0xFFFF) == *entry) && (TaHand_IsCardSummon2(nSide, *entry) == 1)) {
                *((s8 *)bCombo + 6) = index;
                SzDuel_InitCardInfo(pCardInfo, entries[index]);
                return TaHand_GetCardKind(entries[index]) >> 5;
            }
            entry++;
            index++;
        } while (index < TaHand_GetNextHandNum(nSide));
    }
    return -1;
}

/* Whether side `nSide` plays a magic or ritual card from its hand now (its slot into `bCombo`, the card into
   `pCardInfo`). */
s32 TaLogic019_GetSpellPlay(s32 nSide, u8 *bCombo, void *pCardInfo, s32 nMode) {
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

typedef struct Info_0015FE50 {
    u8 pad00[8];
    u16 x;
    s16 y;
} Info_0015FE50;

typedef struct Sprite_0015FE50 {
    Info_0015FE50 *info;
    u8 pad04[0x34];
    s16 x;
    s16 y;
} Sprite_0015FE50;


/* Fills hand combination `bCombo` for side `nSide`: the best fusion or equip chain, its card into `pCardInfo`. */
s32 TaLogic019_SetComboQue(s32 nSide, u8 *bCombo, void *pCardInfo) {
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
                            TaLogic_ConvEmptyCombo_00160030(nSide, *node, entries);
                            TaLogic_CopyArray((u8 *)*node + 2, bCombo + 6);
                            SzDuel_InitCardInfo(pCardInfo, **node);
                            ((Sprite_0015FE50 *)pCardInfo)->x = (value >> 16) - (((Sprite_0015FE50 *)pCardInfo)->info->x & 0x1FFF);
                            ((Sprite_0015FE50 *)pCardInfo)->y = (value & 0xFFFF) - (((Sprite_0015FE50 *)pCardInfo)->info->y & 0x1FFF);
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
} Info_00160030;

/* Fills an empty combination: the hand card side `nSide` can summon with the best attack plus defence. */
void TaLogic_ConvEmptyCombo_00160030(s32 nSide, void *pCardInfo, s32 *pResult) {
    Info_00160030 *info = pCardInfo;
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
                if (card != 0x3E7 && TaLogic019_IsRefuseEmptyCombo(card) == 0 && level >= TaHand_GetCardSummonCost2(card, nSide)) {
                    cost = TaHand_GetCardAPDP(card);
                    if ((cost & 0xFFFF) + (cost >> 16) * 2 < 0xFA1 && TaHand_IsCardEffect(card) == 2 &&
                        (u16)TaLogic_GetHandFusion(info->id, (u16)card) == 0x3E7) {
                        TaLogic_AddEmptyCombo(info->values, buf[i]);
                    }
                }
            }
        }
    }
}

/* Whether this duelist keeps card `nCardNo` out of a summon (it is wanted for an equip). */
s32 TaLogic019_IsRefuseEmptyCombo(s32 nCardNo) {
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
} Obj1_00160270;

typedef struct {
    u8 pad0[0x38];
    s16 f38;
    s16 f3A;
    u16 id;
} Obj2_00160270;

/* Fills hand combination `bCombo` for side `nSide` with this duelist's special combination, its card into
   `pCardInfo`. */
s32 TaLogic019_SetSpecialComboQue(s32 nSide, void *bCombo, void *pCardInfo) {
    Obj1_00160270 *o1 = bCombo;
    Obj2_00160270 *o2 = pCardInfo;
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
void TaLogic_GetSommonPiecePreference_001604A0(s32 nSide, s32 nPr) {
    Ta_GetSommonPiecePreference(nSide, nPr);
}

typedef struct {
    u8 low : 4;
    u8 high : 4;
} Nibbles_001604B0;

typedef struct {
    u8 pad[0x3E];
    u8 f3E;
} Card_001604B0;


/* The square side `nSide` summons a card of kind `sKind` to. */
s32 TaLogic019_GetSummonPiece(s32 nSide, s32 sKind, void *pInput, s32 nMode) {
    extern s32 TaLogic_IsUnitWin4();
    extern s32 TaLogic_GetInvadeRoot2(s32, void *, s32, s32, s32, s32, s32, s32, u8, u16);
    extern s32 TaLogic_GetRoot2(s32, void *, s32, s32, s32, s32, u16, u8);
    Card_001604B0 *card = pInput;
    Nibbles_001604B0 entries[12];
    s32 id;
    s32 hi;
    s32 lo;
    s32 i;
    Nibbles_001604B0 *entry;
    s32 pos;
    s32 cost;
    s32 bestId;
    s32 best;
    s32 y;
    s32 x;
    s32 j;
    s32 slot;

    if (card == NULL) {
        return -1;
    }
    entry = entries;
    i = 0;
    do {
        entry->low = entry->high = 15;
        entry++;
        i++;
    } while (i < 12);
    if ((u8)(card->f3E >> 5) == 0 && nMode >= 0) {
        best = 0xFF;
        bestId = 0xFFFF;
        pos = SzDuel_GetUnitLoc(nMode >> 8, nMode & 0xFF);
        for (i = 0; i < 8; i++) {
            id = Ta_GetSommonPiecePreference(nSide, i);
            if (id < 0) {
                continue;
            }
            lo = id & 0xFF;
            hi = id >> 8;
            if (SzDuel_GetField(lo, hi) == 8) {
                continue;
            }
            if (SzDuel_GetField(lo, hi) == 9 && Ta_IsVirus_Chk3(card, lo, hi) == 1) {
                continue;
            }
            if (SzDuel_GetMapUnit(lo, hi) != 0) {
                continue;
            }
            if (TaLogic_IsUnitWin4(card, nMode, TaLogic_GetWarnHideLvl_00162580(nSide), pos & 0xFF, pos >> 8, 0) > 0) {
                cost = TaLogic_GetInvadeRoot2((s32)card, entries, lo, hi, pos & 0xFF, pos >> 8, nMode, 0, 3,
                                     TaLogic_GetWarnHideLvl_00162580(nSide));
            } else {
                cost = TaLogic_GetRoot2((s32)card, entries, lo, hi, pos & 0xFF, pos >> 8, nMode, 3);
            }
            if (TaLogic_GetMinGoalCount((u8 *)entries) > 0 && cost < best) {
                best = cost;
                bestId = id;
            }
        }
        if (bestId != 0xFFFF) {
            return bestId;
        }
    }
    for (j = 0; j < 8; j++) {
        slot = Ta_GetSommonPiecePreference(nSide, j);
        if (slot < 0) {
            continue;
        }
        x = slot & 0xFF;
        y = slot >> 8;
        if (SzDuel_GetField(x, y) == 8) {
            continue;
        }
        if (SzDuel_GetField(x, y) == 9 && Ta_IsVirus_Chk3(card, x, y) == 1) {
            continue;
        }
        if (SzDuel_GetMapUnitID(x, y) < 0) {
            return slot;
        }
    }
    return -1;
}

typedef struct Nibbles_001607D0 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_001607D0;

typedef struct Output_001607D0 {
    u16 position;
    u8 action;
    u8 pad3;
    u16 destination;
    u8 pad6[6];
    s32 special;
    u8 result;
} Output_001607D0;


/* The task of a unit running from danger (task `pTask`): the safest square in reach, into `pInput` (`fFirst` = 1
   for the unit's first-choice task). */
s32 TaLogic_GetMinimumTask_RunMission_001607D0(u16 *pTask, s32 nSide, void *pInput, u8 fFirst) {
    Output_001607D0 *output = pInput;
    s32 target;
    u8 endX;
    u8 extra;
    Nibbles_001607D0 nibbles[12];
    s32 bestScore;
    s32 best;
    s32 i;
    Nibbles_001607D0 *p;
    extern s32 TaLogic_IsOpenUnit_001620B0();
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

        initialScore = TaLogic_GetWarnHideLvl_00162580(nSide);
        centerX = target & 0xFF;
        centerY = target >> 8;
        if (TaLogic_GetUnitWarning(centerX, centerY, *pTask, 3, initialScore, 0) == 0) {
            output->position = *pTask;
            output->action = 6;
            output->destination = target;
            output->result = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, output->destination, 1, 0);
            output->special = TaLogic_IsOpenUnit_001620B0(*pTask >> 8, *pTask & 0xFF, pTask);
            TaLogic_InitRogicControl(pTask, fFirst);
            return 0;
        }
        if ((range = GetMoveRev(SzDuel_GetUnit(*pTask >> 8, *pTask & 0xFF), centerX, centerY)) == 0) {
            output->position = *pTask;
            output->action = 6;
            output->destination = target;
            output->result = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, output->destination, 1, 0);
            output->special = TaLogic_IsOpenUnit_001620B0(*pTask >> 8, *pTask & 0xFF, pTask);
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
                        candidateScore = TaLogic_GetUnitWarning(x, y, *pTask, 3, (u16)TaLogic_GetWarnHideLvl_00162580(nSide), 0);
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
            output->special = TaLogic_IsOpenUnit_001620B0(*pTask >> 8, *pTask & 0xFF, pTask);
        } else {
            output->position = *pTask;
            output->action = 6;
            output->destination = target;
            output->result = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, output->destination, 1, 0);
            output->special = TaLogic_IsOpenUnit_001620B0(*pTask >> 8, *pTask & 0xFF, pTask);
        }
        TaLogic_InitRogicControl(pTask, fFirst);
        return 0;
    }
}

typedef struct Input_00160DA0 {
    u16 position;
    u8 pad[6];
    u32 destinations;
} Input_00160DA0;

typedef struct Output_00160DA0 {
    u16 position;
    u8 action;
    u8 pad3;
    u16 destination;
    u8 pad6[6];
    s32 direct;
    u8 result;
} Output_00160DA0;

typedef struct Coord_00160DA0 {
    u8 x : 4;
    u8 y : 4;
} Coord_00160DA0;


/* The task's target square: the second half-word when the second argument is 1, else the first. */
static inline u32 destination_00160DA0(void *src, s32 which) {
    if (which == 1) {
        return (u16)(((Input_00160DA0 *)src)->destinations >> 16);
    }
    return (u16)((Input_00160DA0 *)src)->destinations;
}

/* Whether the first square is nearer to (x, y) than the second. */
static inline s32 closer_00160DA0(Coord_00160DA0 *best, Coord_00160DA0 *current,
                                  s32 targetX, s32 targetY) {
    s32 minBestY = best->y < targetY ? best->y : targetY;
    s32 maxBestY = targetY < best->y ? best->y : targetY;
    s32 minBestX = best->x < targetX ? best->x : targetX;
    s32 maxBestX = targetX < best->x ? best->x : targetX;
    s32 minCurrentY = current->y < targetY ? current->y : targetY;
    s32 maxCurrentY = targetY < current->y ? current->y : targetY;
    s32 minCurrentX = current->x < targetX ? current->x : targetX;
    s32 maxCurrentX = targetX < current->x ? current->x : targetX;

    return (maxCurrentX - minCurrentX) + (maxCurrentY - minCurrentY) <
           (maxBestX - minBestX) + (maxBestY - minBestY);
}

/* The task of a unit attacking (task `pTask`): its path to the goal, into `pInput`; -1 when it has none (`fFirst`
   = 1 for the unit's first-choice task). */
s32 TaLogic_GetMinimumTask_AtkMission_00160DA0(void *pTask, s32 nSide, void *pInput, u8 fFirst) {
    extern s32 TaLogic_IsOpenUnit_001620B0();
    extern void TaLogic_GetInvadeRoot();
    Coord_00160DA0 coords[12];
    s32 original;
    s32 count;
    s32 originalY;
    s32 originalX;
    s32 direct;
    s32 target;
    s32 targetX;
    Coord_00160DA0 *current;
    s32 fallback;
    s32 sourcePosition;
    s32 mode;
    s32 i;
    s32 bestCost;
    s32 bestIndex;
    u32 destinationForX;
    u32 destinationForY;
    Input_00160DA0 *input = pTask;
    Output_00160DA0 *output = pInput;

    mode = fFirst;
    destinationForX = destination_00160DA0(pTask, mode);
    destinationForY = destination_00160DA0(pTask, mode);
    if (SzDuel_GetUnit(destinationForY >> 8, destinationForX & 0xFF) == 0) {
        TaLogic_InitRogicControl(pTask, 1);
        return -1;
    }
    fallback = TaLogic_IsOpenUnit_001620B0(input->position >> 8,
                            input->position & 0xFF, pTask);
    original = SzDuel_GetUnitLoc(input->position >> 8,
                            input->position & 0xFF);
    destinationForX = destination_00160DA0(pTask, mode);
    destinationForY = destination_00160DA0(pTask, mode);
    target = SzDuel_GetUnitLoc(destinationForY >> 8, destinationForX & 0xFF);
    {
        s32 j = 0;
        do {
            coords[j].x = coords[j].y = 15;
            j++;
        } while (j < 12);
    }
    {
        s32 unitInfo = SzDuel_GetUnit(input->position >> 8,
                                input->position & 0xFF);
        originalX = original & 0xFF;
        originalY = original >> 8;
        if (GetMoveRev(unitInfo, originalX, originalY) == 0) {
            s32 cost;
            output->position = input->position;
            output->action = 6;
            output->destination = original;
            cost = TaLogic_GetUnitWarning(originalX, originalY, nSide, 3, 1,
                                (u8)TaLogic_GetWarnHideLvl_00162580(nSide));
            if (cost >= SzDuel_GetUnitAP(input->position >> 8,
                                     input->position & 0xFF, 0)) {
                output->result = TaLogic_IsDefStyleUnit(
                    input->position >> 8,
                    input->position & 0xFF,
                    output->destination, 1, 0);
            } else {
                output->result = TaLogic_IsDefStyleUnit(
                    input->position >> 8,
                    input->position & 0xFF,
                    output->destination, 0, 0);
            }
            TaLogic_InitRogicControl(pTask, fFirst);
            return 0;
        } else {
            s32 sourceY;
            s32 sourceX;
            u16 leader;
            sourcePosition = input->position;
            leader = (u16)TaLogic_GetWarnHideLvl_00162580(nSide);
            sourceY = sourcePosition >> 8;
            sourceX = sourcePosition & 0xFF;
            targetX = target & 0xFF;
            TaLogic_GetInvadeRoot(sourceY, sourceX,
                          coords, originalX, originalY, targetX, target >>= 8,
                          destination_00160DA0(pTask, mode), 0, 30,
                          leader);
            count = TaLogic_GetMinGoalCount((u8 *)coords);
            bestIndex = 0xFF;
            if (count > 0) {
                direct = 0;
                bestCost = 0xFFFF;
                for (i = 0; i < count; i++) {
                    if (TaLogic019_IsOpenMoveUnit(input->position >> 8,
                                      input->position & 0xFF,
                                      originalX, originalY, targetX, target) == 1) {
                        bestIndex = i;
                        direct = 1;
                        coords[i].x = targetX;
                        coords[i].y = target;
                        i = count;
                    } else {
                        s32 cost;
                        current = &coords[i];
                        cost = TaLogic_GetUnitWarning(current->x, current->y, nSide, 2, 1,
                                             (u8)TaLogic_GetWarnHideLvl_00162580(nSide));
                        if (cost < bestCost) {
                            bestCost = cost;
                            bestIndex = i;
                        } else if (cost == bestCost) {
                            if (closer_00160DA0(&coords[bestIndex], current, targetX, target)) {
                                bestCost = cost;
                                bestIndex = i;
                            }
                        }
                    }
                }
            } else {
                output->position = input->position;
                output->action = 6;
                output->destination = original;
                output->direct = fallback;
                output->result = TaLogic_IsDefStyleUnit(
                    input->position >> 8,
                    input->position & 0xFF,
                    output->destination, 0, 0);
                TaLogic_InitRogicControl(pTask, fFirst);
                return 0;
            }
            if (bestIndex != 0xFF) {
                output->position = input->position;
                output->action = 6;
                output->destination = (coords[bestIndex].y << 8) | coords[bestIndex].x;
                output->direct = direct;
                output->result = TaLogic_IsDefStyleUnit(
                    input->position >> 8,
                    input->position & 0xFF,
                    output->destination, 0, 0);
            } else {
                output->position = input->position;
                output->action = 6;
                output->destination = original;
                output->direct = direct;
                output->result = TaLogic_IsDefStyleUnit(
                    input->position >> 8,
                    input->position & 0xFF,
                    output->destination, 0, 0);
                TaLogic_InitRogicControl(pTask, fFirst);
                return 0;
            }

        }
    }
    return 0;
}

typedef struct Coord_00161380 {
    u8 x : 4;
    u8 y : 4;
} Coord_00161380;

typedef struct Unit_00161380 {
    u16 position;
    u8 pad2[6];
    union {
        u32 packed;
        u16 low;
    } target;
} Unit_00161380;

typedef struct Output_00161380 {
    u16 position;
    u8 kind;
    u8 pad3;
    u16 target;
    u8 pad6[6];
    s32 value;
    u8 flag;
} Output_00161380;


/* The task's target square: the second half-word when the second argument is 1, else the first. */
static inline u32 target_00161380(void *unit, s32 side) {
    return side == 1 ? (u32)(u16)(((Unit_00161380 *)unit)->target.packed >> 16) : (u32)((Unit_00161380 *)unit)->target.low;
}

/* The smaller of the two values. */
static inline u32 minY_00161380(void *unit, s32 side, u8 coord) {
    return coord < (target_00161380(unit, side) >> 8) ? coord : (target_00161380(unit, side) >> 8);
}

/* The larger of the two values. */
static inline u32 maxY_00161380(void *unit, s32 side, u8 coord) {
    return (target_00161380(unit, side) >> 8) < coord ? coord : (target_00161380(unit, side) >> 8);
}

/* The smaller of the two values. */
static inline u32 minX_00161380(void *unit, s32 side, u8 coord) {
    return coord < (target_00161380(unit, side) & 0xFF) ? coord : (target_00161380(unit, side) & 0xFF);
}

/* The larger of the two values. */
static inline u32 maxX_00161380(void *unit, s32 side, u8 coord) {
    return (target_00161380(unit, side) & 0xFF) < coord ? coord : (target_00161380(unit, side) & 0xFF);
}

/* The task of a unit moving to its goal (task `pTask`), into `pInput` (`fFirst` = 1 for the unit's first-choice
   task). */
s32 TaLogic_GetMinimumTask_MoveMission_00161380(void *pTask, s32 nSide, void *pInput, u8 fFirst, u8 nKind) {
    extern s32 TaLogic_IsOpenUnit_001620B0();
    extern s32 TaLogic_GetUnitWarning();
    extern void TaLogic_GetRoot();
    extern s32 TaLogic_IsDefStyleUnit(s32, s32, s32, u8, s32);
    Coord_00161380 coords[12];
    s32 initial;
    s32 cell;
    s32 count;

    initial = SzDuel_GetUnitLoc(((Unit_00161380 *)pTask)->position >> 8, ((Unit_00161380 *)pTask)->position & 0xFF);
    {
    s32 bestScore;
    s32 best;
    s32 side = fFirst;
    Coord_00161380 *candidate;
    s32 index;
    if (target_00161380(pTask, side) == 0xFFFF) {
        if (initial == target_00161380(pTask, side)) {
            ((Output_00161380 *)pInput)->position = ((Unit_00161380 *)pTask)->position;
            ((Output_00161380 *)pInput)->kind = 6;
            ((Output_00161380 *)pInput)->target = initial;
            ((Output_00161380 *)pInput)->flag = TaLogic_IsDefStyleUnit(((Unit_00161380 *)pTask)->position >> 8, ((Unit_00161380 *)pTask)->position & 0xFF, ((Output_00161380 *)pInput)->target, nKind, 0);
            ((Output_00161380 *)pInput)->value = TaLogic_IsOpenUnit_001620B0(((Unit_00161380 *)pTask)->position >> 8, ((Unit_00161380 *)pTask)->position & 0xFF, pTask);
            TaLogic_InitRogicControl(pTask, fFirst);
            return 0;
        }
    }

    if (SzDuel_GetUnitStatus(((Unit_00161380 *)pTask)->position >> 8,
                      ((Unit_00161380 *)pTask)->position & 0xFF, 4) != 0) {
        if ((SzDuel_GetUnitKind(((Unit_00161380 *)pTask)->position >> 8,
                          ((Unit_00161380 *)pTask)->position & 0xFF) >> 5) == 1 ||
            (SzDuel_GetUnitKind(((Unit_00161380 *)pTask)->position >> 8,
                          ((Unit_00161380 *)pTask)->position & 0xFF) >> 5) == 5) {
            SzDuel_SetUnitStatus(((Unit_00161380 *)pTask)->position >> 8,
                          ((Unit_00161380 *)pTask)->position & 0xFF, 0, 1);
            ((Output_00161380 *)pInput)->position = ((Unit_00161380 *)pTask)->position;
            ((Output_00161380 *)pInput)->kind = 0xE;
            return 0;
        }
    }

    candidate = coords;
    {
        s32 i = 0;
        Coord_00161380 *entry = candidate;
        do {
            entry->x = entry->y = 0xF;
            i++;
            entry++;
        } while (i < 12);
    }

    cell = SzDuel_GetMapUnitID(target_00161380(pTask, side) & 0xFF, ((u32)target_00161380(pTask, side)) >> 8);
    if (cell < 0) {
        cell = 0xFFFF;
    }
    TaLogic_GetRoot(((Unit_00161380 *)pTask)->position >> 8, ((Unit_00161380 *)pTask)->position & 0xFF,
                 coords, initial & 0xFF, initial >> 8, target_00161380(pTask, side) & 0xFF,
                 ((u32)target_00161380(pTask, side)) >> 8, (u16)cell, 7);
    count = TaLogic_GetMinGoalCount((u8 *)coords);
    {
        if (count > 0) {
        best = 0xFF;
        bestScore = 0xFFFF;
        for (index = 0; index < count; index++) {
                if (SzDuel_GetMapUnit(candidate->x, candidate->y) == 0) {
                    s32 score = TaLogic_GetUnitWarning(candidate->x, candidate->y, nSide, 2, 1, (u8)TaLogic_GetWarnHideLvl_00162580(nSide));
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
                        bestMinY = minY_00161380(pTask, side, bestY);
                        bestMaxY = maxY_00161380(pTask, side, bestY);
                        bestX = (&coords[best])->x;
                        bestMinX = minX_00161380(pTask, side, bestX);
                        bestMaxX = maxX_00161380(pTask, side, bestX);
                        currentY = (u8)candidate->y;
                        currentMinY = minY_00161380(pTask, side, currentY);
                        currentMaxY = maxY_00161380(pTask, side, currentY);
                        currentX = candidate->x;
                        currentMinX = minX_00161380(pTask, side, currentX);
                        currentMaxX = maxX_00161380(pTask, side, currentX);
                        if ((currentMaxX - currentMinX) + (currentMaxY - currentMinY) < (bestMaxX - bestMinX) + (bestMaxY - bestMinY)) {
                            bestScore = score;
                            best = index;
                        }
                    }
                }
            candidate++;
        }
    } else {
        ((Output_00161380 *)pInput)->position = ((Unit_00161380 *)pTask)->position;
            ((Output_00161380 *)pInput)->kind = 6;
            ((Output_00161380 *)pInput)->target = initial;
            ((Output_00161380 *)pInput)->flag = TaLogic_IsDefStyleUnit(((Unit_00161380 *)pTask)->position >> 8, ((Unit_00161380 *)pTask)->position & 0xFF, ((Output_00161380 *)pInput)->target, nKind, 0);
            ((Output_00161380 *)pInput)->value = TaLogic_IsOpenUnit_001620B0(((Unit_00161380 *)pTask)->position >> 8, ((Unit_00161380 *)pTask)->position & 0xFF, pTask);
        TaLogic_InitRogicControl(pTask, fFirst);
        return 0;
    }

        if (best != 0xFF) {
            ((Output_00161380 *)pInput)->position = ((Unit_00161380 *)pTask)->position;
            ((Output_00161380 *)pInput)->kind = 6;
            ((Output_00161380 *)pInput)->target = (coords[best].y << 8) | coords[best].x;
            ((Output_00161380 *)pInput)->flag = TaLogic_IsDefStyleUnit(((Unit_00161380 *)pTask)->position >> 8, ((Unit_00161380 *)pTask)->position & 0xFF, ((Output_00161380 *)pInput)->target, nKind, 0);
            ((Output_00161380 *)pInput)->value = TaLogic_IsOpenUnit_001620B0(((Unit_00161380 *)pTask)->position >> 8, ((Unit_00161380 *)pTask)->position & 0xFF, pTask);
        } else {
            ((Output_00161380 *)pInput)->position = ((Unit_00161380 *)pTask)->position;
            ((Output_00161380 *)pInput)->kind = 6;
            ((Output_00161380 *)pInput)->target = initial;
            ((Output_00161380 *)pInput)->flag = TaLogic_IsDefStyleUnit(((Unit_00161380 *)pTask)->position >> 8, ((Unit_00161380 *)pTask)->position & 0xFF, ((Output_00161380 *)pInput)->target, nKind, 0);
            ((Output_00161380 *)pInput)->value = TaLogic_IsOpenUnit_001620B0(((Unit_00161380 *)pTask)->position >> 8, ((Unit_00161380 *)pTask)->position & 0xFF, pTask);
        }
        TaLogic_InitRogicControl(pTask, fFirst);
    }
    }
    return 0;
}

typedef struct Nibbles_00161BF0 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_00161BF0;

typedef struct Result_00161BF0 {
    u16 id;
    u8 type;
    u8 pad3;
    u16 target;
    u8 pad6[6];
    s32 state;
    u8 outcome;
} Result_00161BF0;


/* The task of reviving a monster from the graveyard (task `pTask`), into `pInput` (`fFirst` = 1 for the unit's
   first-choice task). */
s32 TaLogic_GetMinimumTask_ReviveMission_00161BF0(u16 *pTask, s32 nSide, void *pInput, s32 fFirst) {
    extern void TaLogic_InitRogicControl();
    extern s32 TaLogic_GetMinimumTask_RunMission_001607D0();
    Nibbles_00161BF0 entries[12];
    s32 value;
    s32 selection;
    s32 index;
    Result_00161BF0 *result = pInput;

    {
        u32 *card;
        s32 mode;

        mode = (u8)(SzDuel_GetUnitKind(*pTask >> 8, *pTask & 0xFF) >> 5);
        if (mode == 0) {
            card = SzDuel_GetUnitEffect(*pTask >> 8, *pTask & 0xFF, 3);
        } else {
            card = SzDuel_GetUnitEffect(*pTask >> 8, *pTask & 0xFF, 0);
        }
        value = SzDuel_GetUnitLoc(*pTask >> 8, *pTask & 0xFF);
        index = 0;
        do {
            entries[index].low = entries[index].high = -1;
            index++;
        } while (index < 12);

        if (card != NULL) {
            if (mode != 0) {
                selection = TaLogic019_IsUseRevive(nSide);
                if (SzDuel_GetField(value & 0xFF, value >> 8) == 9) {
                    selection = -1;
                }
                if (TaLogic_GetActionReaction(*pTask >> 8, *pTask & 0xFF, 0, 0, 6, 0) == 5) {
                    selection = -1;
                }
            } else {
                selection = TaLogic019_IsUseSaint(nSide);
            }
            if (selection >= 0) {
                value = (selection >> 16) & 0xFFFF;
                mode = TaLogic_GetGraveEntryAfterScreen(value, selection & 0xFF, *card & 0x3F);
                result->id = *pTask;
                result->type = 12;
                result->outcome = TaLogic_IsDefStyleUnit(*pTask >> 8, *pTask & 0xFF, result->target, 1, 0);
                result->state = 1;
                if (((*card >> 6) & 3) != 3) {
                    result->target = (nSide << 8) | mode;
                } else {
                    result->target = (value << 8) | mode;
                }
                TaLogic_InitRogicControl(pTask, fFirst);
                return 0;
            }
        }
        if (mode != 0) {
            if (SzDuel_GetUnitStatus(*pTask >> 8, *pTask & 0xFF, 4) != 0) {
                SzDuel_SetUnitStatus(*pTask >> 8, *pTask & 0xFF, 0, 1);
                result->id = *pTask;
                result->type = 14;
                return 0;
            }
        }
        return TaLogic_GetMinimumTask_RunMission_001607D0(pTask, nSide, pInput, fFirst);
    }
}

typedef struct Nibbles_00161EA0 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_00161EA0;

typedef struct Out_00161EA0 {
    u16 pos;
    u8 kind;
    u8 unk03;
    u16 target;
    u8 pad06[6];
    s32 flag;
    u8 result;
} Out_00161EA0;

/* The controlled unit this duelist wants back, unless a trap waits on the way (-1). */
static inline s32 slot_00161EA0(u16 *unit, s32 arg1) {
    s32 card = TaLogic019_IsUseRevolt(arg1);
    if (TaLogic_GetActionReaction(*unit >> 8, *unit & 0xFF, 0, 0, 6, 0) == 5) {
        card = -1;
    }
    return card;
}

/* The task of taking back a controlled unit (task `pTask`), into `pInput`. */
s32 TaLogic_GetMinimumTask_RevoltMission_00161EA0(u16 *pTask, s32 nSide, void *pInput, u8 fFirst) {
    extern s32 SzDuel_SetUnitStatus();
    u16 *unit = pTask;
    s32 count;
    s32 card;
    s32 k;
    Out_00161EA0 *out = pInput;
    Nibbles_00161EA0 entries[12];
    s32 i;
    Nibbles_00161EA0 *entry;

    SzDuel_GetUnitLoc(*unit >> 8, *unit & 0xFF);
    entry = entries;
    i = 0;
    do {
        entry->low = entry->high = 15;
        entry++;
        i++;
    } while (i < 12);
    count = 0;
    card = slot_00161EA0(unit, nSide);
    if (card >= 0) {
        card = (card >> 16) & 0xFFFF;
        if (card != 0xFFFF) {
            k = 1;
            do {
                if (SzDuel_GetUnit(nSide == 0 ? 1 : 0, k) != 0) {
                    count++;
                }
                if (k == card) {
                    k = 11;
                }
                k++;
            } while (k < 11);
            out->pos = *unit;
            out->kind = 13;
            out->result = TaLogic_IsDefStyleUnit(*unit >> 8, *unit & 0xFF, out->target, 1, 0);
            out->flag = 1;
            out->target = count - 1;
            TaLogic_InitRogicControl(unit, fFirst);
            return 0;
        }
    }
    if (SzDuel_GetUnitStatus(*unit >> 8, *unit & 0xFF, 4) != 0) {
        SzDuel_SetUnitStatus(*unit >> 8, *unit & 0xFF, 0, 1);
        out->pos = *unit;
        out->kind = 14;
        return 0;
    }
    return TaLogic_GetMinimumTask_RunMission_001607D0(unit, nSide, out, fFirst);
}

/* Whether this duelist opens (turns face up) unit (nSide, nID) now: 0 no, 1 or 2 by its kind. */
s32 TaLogic_IsOpenUnit_001620B0(s32 nSide, s32 nID) {
    s32 s0;
    s32 s1;
    s32 s2;
    u32 *s3;
    s32 a;
    s32 b;

    s0 = SzDuel_GetUnitCardNo();
    s1 = SzDuel_GetUnitLoc(nSide, nID);
    s2 = Ta_IsUnitControl(nSide, nID);
    s3 = SzDuel_GetUnitEffect(nSide, nID, 0);
    if (SzDuel_GetUnitStatus(nSide, nID, 4) != 0) {
        return 0;
    }
    switch (SzDuel_GetUnitKind(nSide, nID) >> 5) {
    case 5:
        if (TaLogic_GetActionReaction(nSide, nID, 0, 0, 6, 0) == 5) {
            return 2;
        }
        if (TaLogic019_IsDoCerem(Ta_IsUnitControl(nSide, nID), s0) == 1) {
            if (SzDuel_GetField(s1 & 0xFF, s1 >> 8) != 9) {
                return 1;
            }
        }
        break;
    case 1:
        if (TaLogic_GetActionReaction(nSide, nID, 0, 0, 6, 0) == 5) {
            return 2;
        }
        if (s3 == NULL) {
            return 2;
        }
        switch (*s3 >> 8) {
        case 4:
            a = TaLogic019_GetUseThunderBolt(s2);
            s1 = SzDuel_GetUnitLoc(nSide, nID);
            b = SzDuel_GetUnitLoc(a >> 8, a & 0xFF);
            if ((s1 & 0xFF) == (b & 0xFF) || (s1 >> 8) == (b >> 8)) {
                return 1;
            }
            break;
        case 0x49:
            if (TaLogic019_IsUseGFK(s2) == 1) {
                return 1;
            }
            break;
        case 0x25:
            if (s0 == 0x2ED && TaLogic_IsAttackedNow(nSide, 0, 0) == 1) {
                return 1;
            }
            if (s0 == 0x2EA && TaLogic_IsAttackedNow(nSide, nID, 0) == 1) {
                return 1;
            }
            break;
        case 0x1F:
            if (s0 == 0x2DD && TaLogic019_IsUseRevolt(s2) == 1) {
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
static inline s32 max_00162390(s32 a, s32 b) {
    if (a < b) {
        return b;
    }
    return a;
}

/* Whether unit (nSide, nID) may open while moving from (nX, nZ) to the square next to it, (gX, gZ). */
s32 TaLogic019_IsOpenMoveUnit(s32 nSide, s32 nID, s32 nX, s32 nZ, s32 gX, s32 gZ) {
    s32 min_y;
    s32 min_x;

    min_y = (nZ < gZ) ? nZ : gZ;
    gZ = max_00162390(gZ, nZ);
    min_x = (nX < gX) ? nX : gX;
    gX = max_00162390(gX, nX);
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
s32 TaLogic019_IsDoCerem(s32 nSide, s32 nCardNo) {
    s32 i;
    s32 mask;
    s32 low;
    s32 high;
    s32 packed;
    s32 position;
    s32 sp50[4];

    Ta_GetCeremSacrifice(sp50, *(s32 *)((u8 *)TaHand_GetCardEffect(nCardNo, 0) + 4));
    if ((mask = Ta_GetSacrificeUnit(sp50, nSide)) < 0) {
        return 0;
    }

    i = 0;
    if (i < Ta_GetUnitNumFrom22bitFlagList(mask)) {
        do {
            packed = Ta_GetUnitOwnerIDFromLstCount(mask, i);
            high = packed >> 8;
            low = packed & 0xFF;
            position = SzDuel_GetUnitLoc(high, low);
            if (TaUtil_GetUnitAP(high, low, position & 0xFF, position >> 8) >= 0xBB8) {
                return 0;
            }
            i++;
        } while (i < Ta_GetUnitNumFrom22bitFlagList(mask));
    }
    return 1;
}

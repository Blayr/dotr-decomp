#include "common.h"

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
} Entry_0011D110;

typedef struct {
    u16 card;
    u8 flag;
    u8 pad;
} Slot_0011D110;


void TaLogic_CommandBtlUnit_0011D110(void *arg0, s32 arg1) {
    extern void TaLogic_InitIgnoreLst();
    extern s32 TaLogic_IsRootOpen();
    extern s32 TaLogic004_GetNearUnit();
    Entry_0011D110 *entry = arg0;
    s32 side;
    s32 player;
    s32 other;
    s32 pos;
    s32 otherPos;
    s32 i;
    u8 work[0x70];
    Slot_0011D110 list[22];
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
                              other >> 8, other & 0xFF, otherPos & 0xFF, otherPos >> 8, 4) > 0) {
                entry->state = 0x2FF;
                entry->data.word = (other << 16) | entry->data.halves.low;
                return;
            }
        }
        countB = 0;
        countA = 0;
        i = 1;
        while (1) {
            switch (TaLogic004_GetNearUnit(entry, 0, player, pos & 0xFF, pos >> 8,
                                  Ta_GetCurrentSide(entry->coordinates >> 8, entry->coordinates & 0xFF) == 0 ? 1 : 0,
                                  i & 0xFF, TaLogic_GetWarnHideLvl_0011FA80(side), list, 0, &countA, &countB, 4, work)) {
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
            if (i > 4) {
                break;
            }
        }
        TaLogic004_CommandAtkLineUnit(entry);
    }
}

void TaLogic004_GetNearUnit(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28) {
    TaLogic_GetNearUnit(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
                  arg_sp0, arg_sp8, arg_sp10, arg_sp18, arg_sp20,
                  0, 1500, arg_sp28);
}

typedef struct {
    u16 coordinates;
    u16 pad2;
    u16 state;
    u16 pad6;
    u32 value;
} Entry_0011D3E0;


void TaLogic004_CommandAtkLineUnit(void *arg0) {
    Entry_0011D3E0 *entry = arg0;
    s32 value;
    s32 index[2];
    s32 state;
    u16 coordinates;

    SzDuel_GetTurnOwner();
    coordinates = entry->coordinates;
    value = SzDuel_GetUnitLoc((s32) coordinates >> 8, coordinates & 0xFF);
    coordinates = entry->coordinates;
    if (TaLogic004_IsUnitOnLine((s32) coordinates >> 8, coordinates & 0xFF) < 0) {
        coordinates = entry->coordinates;
        TaLogic004_GetNearAtkLineEdge(SzDuel_GetUnit((s32) coordinates >> 8, coordinates & 0xFF), value & 0xFF, value >> 8, index);
        if (index[0] >= 0) {
            entry->state = 0x6FF;
            entry->value = (index[0] << 16) | (entry->value & 0xFFFF);
        } else {
            entry->state = 0x5FF;
        }
    } else {
        state = ((s32) entry->state >> 8) & 0xFF;
        if (state != 0xF && state != 0x10) {
            entry->state = (((value >> 8) < 4 ? 0xF : 0x10) << 8) | 0xFF;
            entry->value = *(u16 *)&entry->value | 0xFFFF0000;
        }
    }
}

typedef struct Pick_0011D4E0 {
    s32 value;
    u8 score;
} Pick_0011D4E0;

typedef struct Nibbles_0011D4E0 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_0011D4E0;

static inline void try_0011D4E0(s32 arg0, s32 arg1, s32 arg2, Pick_0011D4E0 *pick, Nibbles_0011D4E0 *entries, s32 value) {
    extern s32 TaLogic_GetRoot2(s32, s32, s32, s32, s32, s32, u16, u8);
    s32 score;
    s32 cost;

    score = SzDuel_GetMapUnitID(value & 0xFF, value >> 8);
    if (score < 0) {
        score = 0xFFFF;
    }
    cost = TaLogic_GetRoot2(arg0, (s32)entries, arg1, arg2, value & 0xFF, value >> 8, score, 7);
    if (cost < pick->score && cost >= 0) {
        pick->score = cost;
        pick->value = value;
    }
}

void TaLogic004_GetNearAtkLineEdge(s32 arg0, s32 arg1, s32 arg2, void *arg3) {
    Nibbles_0011D4E0 entries[12];
    s32 i;
    Nibbles_0011D4E0 *entry;
    Pick_0011D4E0 *pick = arg3;

    pick->value = -1;
    pick->score = 0xFF;
    entry = entries;
    i = 0;
    do {
        entry->low = entry->high = 15;
        entry++;
        i++;
    } while (i < 12);
    i = 0;
    do {
        if (TaLogic004_IsEmptyAtkLine(0, i) == 1) {
            try_0011D4E0(arg0, arg1, arg2, pick, entries, TaLogic004_GetAtkLineStart(0, i));
            try_0011D4E0(arg0, arg1, arg2, pick, entries, TaLogic004_GetAtkLineEnd(0, i));
        }
        i++;
    } while (i < 4);
}

s32 TaLogic004_IsUnitOnLine(s32 arg0, s32 arg1) {
    s32 value;

    value = SzDuel_GetUnitLoc(arg0, arg1);
    switch (value & 0xFF) {
    case 0:
        value >>= 8;
        if ((value >= 0) && (value < 7)) {
            return 3;
        }
        break;
    case 2:
        value >>= 8;
        if ((value > 1) && (value < 5)) {
            return 0;
        }
        break;
    case 4:
        value >>= 8;
        if ((value > 1) && (value < 5)) {
            return 1;
        }
        break;
    case 6:
        value >>= 8;
        if ((value >= 0) && (value < 7)) {
            return 4;
        }
        break;
    }
    return -1;
}

s32 TaLogic004_IsEmptyAtkLine(s32 arg0, u8 arg1) {
    s32 row;
    s32 column;
    s32 last_column;
    s32 low;
    s32 high;
    s32 value;

    switch (arg1) {
    case 0:
        column = 2;
        last_column = 4;
        row = 2;
        break;
    case 1:
        column = 2;
        row = 4;
        last_column = 4;
        break;
    case 2:
        column = 1;
        last_column = 5;
        row = 0;
        break;
    case 3:
    default:
        row = 6;
        column = 1;
        last_column = 5;
        break;
    }
    for (; column <= last_column; column++) {
        value = SzDuel_GetMapUnitID(row, column);
        if (value >= 0) {
            high = value >> 8;
            low = value & 0xFF;
            if ((arg0 == Ta_IsUnitControl(high, low)) &&
                ((SzDuel_GetUnitKind(high, low) >> 5) == 0)) {
                return 0;
            }
        }
    }
    return 1;
}

s32 TaLogic004_GetAtkLineStart(s32 arg0, s32 arg1) {
    s32 result;

    switch (arg1) {
    case 0:
        result = 0x204;
        break;
    case 1:
        result = 0x202;
        break;
    case 2:
        result = 0;
        break;
    default:
    case 3:
        result = 6;
        break;
    }

    return result;
}

s32 TaLogic004_GetAtkLineEnd(s32 arg0, s32 arg1) {
    switch (arg1) {
    case 0:
        return 0x402;
    case 1:
        return 0x404;
    case 2:
        return 0x600;
    default:
    case 3:
        return 0x606;
    }
}

typedef struct Data_0011D9B0 {
    u16 position;
    u16 unk2;
    u16 state;
    u16 unk6;
    u32 details;
} Data_0011D9B0;

typedef struct Entry_0011D9B0 {
    u16 id;
    u8 kind;
    u8 padding;
} Entry_0011D9B0;


void TaLogic_CommandEfcMonster_0011D9B0(void *arg0, s32 arg1) {
    u8 context[112];
    Entry_0011D9B0 entries[23];
    s16 count;
    s16 total;
    s32 card;
    s32 position;
    s32 available;
    s32 row;
    s32 column;
    s32 attempt;
    Data_0011D9B0 *data = arg0;
    s32 i;
    Entry_0011D9B0 *entry;
    s32 type;
    s32 result;
    u16 packed;
    extern void TaLogic_InitIgnoreLst();
    extern s32 SzDuel_GetUnitCardNo();
    extern s32 TaLogic_GetNearUnit();

    packed = data->position;
    if ((available = SzDuel_GetUnit((s32) packed >> 8, packed & 0xFF)) != 0) {
        packed = data->position;
        card = Ta_GetCurrentSide((s32) packed >> 8, packed & 0xFF);
        packed = data->position;
        position = SzDuel_GetUnitLoc((s32) packed >> 8, packed & 0xFF);
        entry = entries;
        total = 0;
        count = 0;
        i = 0;
        do {
            i++;
            entry->id = 0xFFFF;
            entry->kind = 0xFF;
            entry++;
        } while (i < 22);
        TaLogic_InitIgnoreLst(context);
        packed = data->position;
        type = SzDuel_GetUnitCardNo((s32) packed >> 8, packed & 0xFF);
        if (type != 0x1FD) {
            attempt = 1;
            switch (type) {
            case 0x1F0:
            case 0x1FE:
                row = position >> 8;
                column = position & 0xFF;
                while (1) {
                    result = TaLogic_GetNearUnit(data, 0, available, column, row,
                        card == 0 ? 1 : 0, (u8) attempt, TaLogic_GetWarnHideLvl_0011FA80(card), entries, 0,
                        &count, &total, 2, 0, 1500, context);
                    switch (result) {
                    case 3:
                    case 2:
                        data->state = 0x3FF;
                        data->details = (position << 16) | (data->details & 0xFFFF);
                        return;
                    case 1:
                        return;
                    case 0:
                        data->state = 0x3FF;
                        data->details = (position << 16) | (data->details & 0xFFFF);
                        return;
                    }
                    attempt++;
                    if (attempt > 2) {
                        break;
                    }
                }
                if (Ta_GetUnitNumFrom22bitFlagList(SearchUnitByRange(0, 0, card, 1, 14, 14)) > 3) {
                    data->state = 0x3FF;
                    data->details = (position << 16) | (data->details & 0xFFFF);
                    return;
                }
                break;
            }
        } else {
            if (TaLogic_CommandGunnerUnit(data, 0) == 1) {
                data->state = 0xBFF;
                return;
            }
        }
        TaLogic_CommandBtlUnit_0011D110(data, 0);
    }
}

typedef struct {
    u16 position;
    u8 flag;
    u8 pad;
} Slot_0011DC00;


void TaLogic_CommandTrapUnit_0011DC00(void *arg0) {
    u8 work[112];
    Slot_0011DC00 slots[22];
    s16 c;
    s16 b;
    u16 a;
    s32 i;
    s32 player;
    s32 position;
    s32 owner;
    s32 state;
    s32 result;
    u16 *record = arg0;
    extern s32 TaLogic_GetNearUnitL2();
    extern void TaLogic_InitIgnoreLst();

    if (SzDuel_GetUnit((s32) record[0] >> 8, record[0] & 0xFF) != 0) {
        player = Ta_GetCurrentSide((s32) record[0] >> 8, record[0] & 0xFF);
        position = SzDuel_GetUnitLoc((s32) record[0] >> 8, record[0] & 0xFF);
        owner = SzDuel_GetUnit((s32) record[0] >> 8, record[0] & 0xFF);
        record[2] = 0xBFF;
        for (i = 0; i < 22; i++) {
            slots[i].position = 0xFFFF;
            slots[i].flag = 0xFF;
        }
        TaLogic_InitIgnoreLst(work);
        a = 0;
        b = 0;
        c = 0;
        state = 0;
        for (i = 1; i < 4; i++) {
            state = TaLogic_GetNearUnitL2(state, owner, position & 0xFF, position >> 8,
                                  Ta_GetCurrentSide((s32) record[0] >> 8, record[0] & 0xFF) == 0 ? 1 : 0, (u8) i, 0,
                                  TaLogic_GetWarnHideLvl_0011FA80(player), slots, &a, &c, &b, work);
            result = TaLogic_GetTrapNearCard((s32) record[0] >> 8, record[0] & 0xFF, position & 0xFF, position >> 8,
                                   slots, 4, 0x1F, 1, 2, 0, TaLogic_GetWarnHideLvl_0011FA80(player), a, 1);
            if (result >= 0) {
                *(u32 *) (record + 4) = (result << 16) | record[4];
                return;
            }
            result = TaLogic_GetTrapNearCard((s32) record[0] >> 8, record[0] & 0xFF, position & 0xFF, position >> 8,
                                   slots, 4, 0x1F, 0, 2, 0, TaLogic_GetWarnHideLvl_0011FA80(player), a, 1);
            if (result >= 0) {
                *(u32 *) (record + 4) = (result << 16) | record[4];
                return;
            }
        }
        a = 0;
        b = 0;
        c = 0;
        state = 0;
        for (i = 1; i < 4; i++) {
            state = TaLogic_GetNearUnitL2(state, owner, position & 0xFF, position >> 8,
                                  Ta_GetCurrentSide((s32) record[0] >> 8, record[0] & 0xFF), (u8) i, 0,
                                  TaLogic_GetWarnHideLvl_0011FA80(player), slots, &a, &c, &b, work);
            result = TaLogic_GetFollowNearUnit(position & 0xFF, position >> 8, slots, 4, 0x22, 2, 2, a);
            if (result >= 0) {
                *(u32 *) (record + 4) = (result << 16) | record[4];
                return;
            }
            result = TaLogic_GetFollowNearUnit(position & 0xFF, position >> 8, slots, 4, 0x1F, 1, 2, a);
            if (result >= 0) {
                *(u32 *) (record + 4) = (result << 16) | record[4];
                return;
            }
            result = TaLogic_GetFollowNearUnit(position & 0xFF, position >> 8, slots, 4, 0x1F, 0, 2, a);
            if (result >= 0) {
                *(u32 *) (record + 4) = (result << 16) | record[4];
                return;
            }
        }
        record[2] = 0x5FF;
    }
}

typedef struct {
    s16 card;
    u8 f2;
    u8 pad3;
    s16 f4;
    u8 pad6[6];
    s32 fC;
} Act_0011DFB0;

typedef struct {
    u8 pad0[0x3C];
    u16 id;
    u8 pad3E[0x22];
} Card_0011DFB0;


s32 TaLogic_GetMinimumTask_Summon_0011DFB0(s32 arg0, s32 arg1, s32 arg2) {
    extern s32 TaLogic_GetUnitNum(s32, s32);
    Act_0011DFB0 *act = (Act_0011DFB0 *)arg2;
    Card_0011DFB0 buf;
    s32 res;
    s32 card;
    s32 type;
    s32 r;

    act->card = arg0;
    if (SzDuel_InqHandPhase(arg1) == 0) {
        return -1;
    }
    if (TaLogic_GetUnitNum(arg1, 0) == 5 && TaLogic_GetUnitNum(arg1, 1) == 5) {
        return -1;
    }
    type = TaLogic_IsHandPlay_0011E6E0(arg1, &buf);
    if (type < 0) {
        return -1;
    }
    act->f2 = 10;
    act->fC = 0;
    card = SzDuel_GetUnitLoc(arg0 >> 8, arg0 & 0xFF);
    if (type == 0) {
        if (TaLogic_SetComboQue_0011EF60(arg1, (u8 *)act, &buf) >= 0) {
            res = TaLogic_GetNearCard2(&buf, card & 0xFF, card >> 8, arg1 == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, TaLogic_GetWarnHideLvl_0011FA80(arg1));
            if (res < 0) {
                if (SzDuel_GetUnitMonsterCount(arg1) < 4) {
                    r = TaLogic004_GetSummonPiece(arg1, type, &buf);
                    if (r < 0) {
                        return -1;
                    }
                    act->f4 = r;
                    return 1;
                }
            } else {
                r = TaLogic004_GetSummonPiece(arg1, type, &buf);
                if (r < 0) {
                    return -1;
                }
                act->f4 = r;
                return 1;
            }
        }
    } else {
        res = TaLogic_GetNearCard2(&buf, card & 0xFF, card >> 8, arg1 == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, TaLogic_GetWarnHideLvl_0011FA80(arg1));
    }
    if (type == 2) {
        TaLogic_SetSpecialComboQue_0011F3C0(arg1, arg2, (s32)&buf, 0);
        r = TaLogic004_GetSummonPiece(arg1, type, &buf);
        if (r < 0) {
            return -1;
        }
        act->f4 = r;
        return 1;
    } else if (type == 3) {
        TaLogic_SetSpecialComboQue_0011F3C0(arg1, arg2, (s32)&buf, 1);
        r = TaLogic004_GetSummonPiece(arg1, type, &buf);
        if (r < 0) {
            return -1;
        }
        act->f4 = r;
        return 1;
    } else {
        if (TaLogic004_GetSpellPlay(arg1, (u8 *)act, &buf, buf.id) < 0) {
            return -1;
        }
        r = TaLogic004_GetSummonPiece(arg1, type, &buf);
        if (r < 0) {
            return -1;
        }
        act->f4 = r;
        return 1;
    }
}

typedef struct Nibbles_0011E270 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_0011E270;


s32 TaLogic004_GetSummonPiece(s32 arg0, u8 arg1, void *arg2) {
    s32 bestLocation;
    s32 bestCost;
    Nibbles_0011E270 buffer[12];
    u8 result[8];
    s32 initIndex;
    Nibbles_0011E270 *p;

    extern s32 TaLogic_GetSommonPiecePreference_0011F530();
    extern s32 TaLogic_IsUnitWin4();
    extern s32 TaLogic_GetInvadeRoot2();
    extern s32 TaLogic_GetRoot2(s32, s32, s32, s32, s32, s32, u16, u8);

    if (arg2 == NULL) {
        return -1;
    }
    p = buffer;
    initIndex = 0;
    do {
        p->low = p->high = 0xF;
        initIndex++;
        p++;
    } while (initIndex < 12);

    if (!((u8)(*((u8 *)arg2 + 0x3E) >> 5))) {
        s32 candidate;
        s32 target;
        s32 y;
        s32 x;
        s32 index;
        s32 destY;
        s32 destX;
        s32 cost;
        s32 location;
        location = SzDuel_GetUnitLoc(arg0, 0);
        target = TaLogic_GetNearCard2(arg2, location & 0xFF, location >> 8,
            arg0 == 0 ? 1 : 0, 4, 31, 2, 2, 0, TaLogic_GetWarnHideLvl_0011FA80(arg0));
        if (target >= 0) {
            bestCost = 255;
            bestLocation = 65535;
            location = SzDuel_GetUnitLoc(target >> 8, target & 0xFF);
            index = 0;
            destY = location >> 8;
            destX = location & 0xFF;
            do {
                if ((candidate = TaLogic_GetSommonPiecePreference_0011F530(arg0, index)) >= 0) {
                    x = candidate & 0xFF;
                    y = candidate >> 8;
                    if (SzDuel_GetField(x, y) != 8 &&
                        (SzDuel_GetField(x, y) != 9 || Ta_IsVirus_Chk3(arg2, x, y) != 1) &&
                        SzDuel_GetMapUnit(x, y) == 0) {
                        if (TaLogic_IsUnitWin4(arg2, target, TaLogic_GetWarnHideLvl_0011FA80(arg0), destX, destY, 0) > 0) {
                            cost = TaLogic_GetInvadeRoot2(arg2, buffer, x, y, destX, destY,
                                target, 0, 4, (u16)TaLogic_GetWarnHideLvl_0011FA80(arg0));
                        } else {
                            cost = TaLogic_GetRoot2((s32)arg2, (s32)buffer, x, y, destX, destY,
                                target, 4);
                        }
                        if (TaLogic_GetMinGoalCount((u8 *)buffer) > 0 && cost < bestCost) {
                            bestCost = cost;
                            bestLocation = candidate;
                        }
                    }
                }
                index++;
            } while (index < 8);
            if (bestLocation != 65535) {
                return bestLocation;
            }
            bestLocation = -1;
            return bestLocation;
        }
        {
        s32 y;
        s32 x;
        s32 fallbackIndex;
        s32 limit;
        s32 candidate;
        s32 fallback;
        limit = 14;
        fallback = -1;
        fallbackIndex = 0;
        do {
            if ((candidate = TaLogic_GetSommonPiecePreference_0011F530(arg0, fallbackIndex)) >= 0) {
                x = candidate & 0xFF;
                y = candidate >> 8;
                if (SzDuel_GetField(x, y) != 8 &&
                    (SzDuel_GetField(x, y) != 9 || Ta_IsVirus_Chk3(arg2, x, y) != 1) &&
                    SzDuel_GetMapUnitID(x, y) < 0) {
                    TaLogic004_GetNearAtkLineEdge((s32)arg2, x, y, (s32 *)result);
                    if ((s32)result[4] < limit && (s32)result[4] >= 0) {
                        fallback = candidate;
                        limit = (s32)result[4];
                    }
                }
            }
            fallbackIndex++;
        } while (fallbackIndex < 8);
        if (limit < 14) {
            return fallback;
        }
        }
    } else {
    s32 y;
    s32 x;
    s32 specialIndex;
    s32 best;
    s32 candidate;
    best = -1;
    specialIndex = 0;
    do {
        if ((candidate = TaLogic_GetSommonPiecePreference_0011F530(arg0, specialIndex)) >= 0) {
            x = candidate & 0xFF;
            y = candidate >> 8;
            if (SzDuel_GetField(x, y) != 8 &&
                (SzDuel_GetField(x, y) != 9 || Ta_IsVirus_Chk3(arg2, x, y) != 1) &&
                SzDuel_GetMapUnitID(x, y) < 0 && y < 8) {
                best = candidate;
            }
        }
        specialIndex++;
    } while (specialIndex < 8);
    if (best >= 0) {
        return best;
    }
    }
    return -1;
}

s32 TaLogic_IsHandPlay_0011E6E0(s32 arg0, void *arg1) {
    s32 cards[8];
    u8 scratch[32];
    s32 count;
    s32 index;
    s32 result;
    u8 status0;
    u8 status1;
    extern s32 TaLogic_GetUnitNum();
    extern s32 SzDuel_GetUnitCardNo();
    extern s32 TaLogic004_GetSpecialComboPlay();

    status0 = TaLogic_GetUnitNum(arg0, 0);
    status1 = TaLogic_GetUnitNum(arg0, 1);
    count = 0;
    if (arg1 == NULL) {
        return -1;
    }
    TaHand_GetNextHand(arg0, cards);
    if (status0 == 5) {
        if (TaLogic004_GetSpellPlay(arg0, scratch, arg1, 999) >= 0) {
            return 1;
        }
        return -1;
    }
    if (status1 == 5) {
        if (count < TaHand_GetNextHandNum(arg0)) {
            s32 *card = cards;
            do {
                if ((TaHand_GetCardKind(*card) >> 5) == 0 &&
                    TaHand_IsCardSummon2(arg0, *card) == 1) {
                    SzDuel_InitCardInfo(arg1, cards[count]);
                    return 0;
                }
                card++;
                count++;
            } while (count < TaHand_GetNextHandNum(arg0));
        }
        return -1;
    }
    if (TaLogic004_GetSpecialComboPlay(arg0, scratch, arg1, 0) >= 0) {
        return 2;
    }
    index = 1;
    do {
        if ((SzDuel_GetUnitKind(arg0, index) & 0x1F) == 14 &&
            arg0 == Ta_IsUnitControl(arg0, index)) {
            count = (u8)(count + 1);
        }
        if ((SzDuel_GetUnitKind(arg0 == 0 ? 1 : 0, index) & 0x1F) == 14 &&
            arg0 == Ta_IsUnitControl(arg0 == 0 ? 1 : 0, index)) {
            count = (u8)(count + 1);
        }
        index++;
    } while (index < 5);
    if ((u8)count >= 3) {
        if (TaLogic004_GetSpecialComboPlay(arg0, scratch, arg1, 1) >= 0) {
            return 3;
        }
        result = TaLogic004_GetSpellPlay(arg0, scratch, arg1, 0x2E2);
        if (result >= 0) {
            return result;
        }
    }
    if ((result = TaLogic004_GetSpellPlay(arg0, scratch, arg1, 0x337)) >= 0) {
        index = 1;
        count = 0;
        do {
            if (arg0 == Ta_IsUnitControl(arg0, index)) {
                if (SzDuel_GetUnitCardNo(arg0, index) == 0x337) {
                    index = 11;
                    count = 0;
                }
            } else if (SzDuel_GetUnitStatus(arg0, index, 4) == 0) {
                count = (u8)(count + 1);
            }
            if (arg0 != Ta_IsUnitControl(arg0 == 0 ? 1 : 0, index)) {
                if (SzDuel_GetUnitCardNo(arg0 == 0 ? 1 : 0, index) == 0x337) {
                    index = 11;
                    count = 0;
                }
            } else if (SzDuel_GetUnitStatus(arg0 == 0 ? 1 : 0, index, 4) == 0) {
                count = (u8)(count + 1);
            }
            index++;
        } while (index < 11);
        if ((u8)count >= 6) {
            return result;
        }
    }
    {
        s32 *card;
        s32 i = 0;
        if (i < TaHand_GetNextHandNum(arg0)) {
            card = cards;
            do {
                if ((TaHand_GetCardKind(*card) >> 5) == 0 &&
                    TaHand_IsCardSummon2(arg0, *card) == 1 && *card != 0x156) {
                    SzDuel_InitCardInfo(arg1, cards[i]);
                    return 0;
                }
                card++;
                i++;
            } while (i < TaHand_GetNextHandNum(arg0));
        }
    }
    result = TaLogic004_GetSpellPlay(arg0, scratch, arg1, 999);
    if (result >= 0) {
        return result;
    }
    return -1;
}

s32 TaLogic004_GetSpecialComboPlay(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 values[8];
    s32 i;
    s32 found;
    s32 *firstPtr;
    s32 *scanPtr;
    s32 *modePtr;

    found = 0;
    TaHand_GetNextHand(arg0, values);
    switch (arg3 & 0xFF) {
    case 0:
        i = 0;
        if (0 < TaHand_GetNextHandNum(arg0)) {
            firstPtr = values;
            do {
                if (*firstPtr == 0x31F) {
                    found = 1;
                    ((u8 *)arg1)[6] = i;
                }
                firstPtr++;
                i++;
            } while (i < TaHand_GetNextHandNum(arg0));
        }
        if (found == 1) {
            found = 0;
            if (0 < TaHand_GetNextHandNum(arg0)) {
                scanPtr = values;
                do {
                    if (((TaHand_GetCardKind(*scanPtr) >> 5) == 0) &&
                        (Ta_GetHandEnchant(*scanPtr, 0x31F) >= 0) &&
                        (TaHand_IsCardSummon2(arg0, *scanPtr) == 1) &&
                        (*scanPtr != 0x31B) && (*scanPtr != 0x31C)) {
                        ((u8 *)arg1)[7] = found;
                        SzDuel_InitCardInfo((void *)arg2, values[found]);
                        return TaHand_GetCardKind(values[found]) >> 5;
                    }
                    scanPtr++;
                    found++;
                } while (found < TaHand_GetNextHandNum(arg0));
            }
        }
        break;
    case 1:
        if (0 < TaHand_GetNextHandNum(arg0)) {
            found = 0;
            modePtr = values;
            do {
                if ((*modePtr == 0x202) && (TaHand_IsCardSummon2(arg0, *modePtr) == 1)) {
                    ((u8 *)arg1)[6] = found;
                    SzDuel_InitCardInfo((void *)arg2, values[found]);
                    return TaHand_GetCardKind(values[found]) >> 5;
                }
                modePtr++;
                found++;
            } while (found < TaHand_GetNextHandNum(arg0));
        }
        break;
    default:
        break;
    }
    return -1;
}

s32 TaLogic004_GetSpellPlay(s32 arg0, u8 *arg1, void *arg2, s32 arg3) {
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
        if ((TaHand_GetCardKind(buf[i]) >> 5) != 0 && buf[i] != 0x31F) {
            arg1[6] = i;
            SzDuel_InitCardInfo(arg2, buf[i]);
            return 1;
        }
    }
    return -1;
}

typedef struct Info_0011EF60 {
    u8 pad00[8];
    u16 x;
    s16 y;
} Info_0011EF60;

typedef struct Sprite_0011EF60 {
    Info_0011EF60 *info;
    u8 pad04[0x34];
    s16 x;
    s16 y;
} Sprite_0011EF60;

u16 *TaLogic_GetFusionTree(s32, u16 *, s32, s32, s32, s16 *, s16 *);

s32 TaLogic_SetComboQue_0011EF60(s32 arg0, u8 *arg1, void *arg2) {
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
                if ((TaHand_GetCardKind(card) >> 5) == 0 && card != 0x156) {
                    *node = TaLogic_GetFusionTree(arg0, *node, i & 0xFF, card & 0xFFFF, 0, &a, &b);
                    *node = TaLogic_GetFusionRes(*node);
                    value = TaLogic_GetEnchantQue(arg0, *node, 0, 0);
                    if (TaHand_IsCardSummon2(arg0, card) == 1) {
                        if (best < value) {
                            TaLogic_ConvEmptyCombo_0011F150(arg0, *node, entries);
                            TaLogic_CopyArray((u8 *)*node + 2, arg1 + 6);
                            SzDuel_InitCardInfo(arg2, **node);
                            ((Sprite_0011EF60 *)arg2)->x = (value >> 16) - (((Sprite_0011EF60 *)arg2)->info->x & 0x1FFF);
                            ((Sprite_0011EF60 *)arg2)->y = (value & 0xFFFF) - (((Sprite_0011EF60 *)arg2)->info->y & 0x1FFF);
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
} Info_0011F150;

void TaLogic_ConvEmptyCombo_0011F150(s32 arg0, void *arg1, s32 *arg2) {
    Info_0011F150 *info = arg1;
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
                if (card != 0x3E7 && TaLogic004_IsRefuseEmptyCombo(card) == 0 && level >= TaHand_GetCardSummonCost2(card, arg0)) {
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

s32 TaLogic004_IsRefuseEmptyCombo(s32 arg0) {
    if ((TaHand_GetCardKind(arg0) >> 5) != 0) {
        return 1;
    }
    if ((arg0 == 0x1F0) || (arg0 == 0x1FD) || (arg0 == 0x1FE) ||
        (arg0 == 0x202) || (arg0 == 0x1F6) || (arg0 == 0x20B)) {
        return 1;
    }
    return 0;
}

typedef struct {
    u8 pad[6];
    u8 indices[5];
} CardState_0011F3C0;


s32 TaLogic_SetSpecialComboQue_0011F3C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 cards[5];
    s32 *card;
    s32 i;
    s32 card_id;

    if (arg2 == 0) {
        return -1;
    }
    for (i = 0; i < 5; i++) {
        ((CardState_0011F3C0 *)(arg1 + i))->indices[0] = 0xFF;
    }
    TaHand_GetNextHand(arg0, cards);
    if ((arg3 & 0xFF) == 0) {
        TaLogic004_GetSpecialComboPlay(arg0, arg1, arg2, 0);
        i = 0;
        if (0 < TaHand_GetNextHandNum(arg0)) {
            card = cards;
            do {
                if ((i != ((CardState_0011F3C0 *)arg1)->indices[0]) && (i != ((CardState_0011F3C0 *)arg1)->indices[1]) && (Ta_GetHandEnchant(0x1E8, *card) >= 0) && ((TaHand_GetCardKind(*card) >> 5) == 2)) {
                    card_id = *card;
                    if ((card_id != 0x31B) && (card_id != 0x31C)) {
                        ((CardState_0011F3C0 *)arg1)->indices[2] = i;
                    }
                }
                card++;
                i++;
            } while (i < TaHand_GetNextHandNum(arg0));
        }
    } else if ((arg3 & 0xFF) == 1) {
        TaLogic004_GetSpecialComboPlay(arg0, arg1, arg2, 0);
    }
    return 0;
}

s32 TaLogic_GetSommonPiecePreference_0011F530(s32 arg0, u32 arg1) {
    return Ta_GetSommonPiecePreference(arg0, arg1);
}

typedef struct {
    u8 low : 4;
    u8 high : 4;
} Flags_0011F540;

typedef struct {
    u16 id;
    u8 action;
    u8 pad3;
    u16 position;
    u8 pad6[6];
    s32 value;
    u8 mode;
} Output_0011F540;


s32 TaLogic_GetMinimumTask_RunMission_0011F540(u16 *arg0, s32 arg1, void *arg2, u8 arg3) {
    extern s32 TaLogic_IsRunPassRoot(s32, s32, s32, s32, s32, s32, void *, u8);
    extern s32 TaLogic_IsOpenUnit_001211B0();
    s32 position;
    u8 upperX;
    u8 flag;
    Flags_0011F540 cells[12];
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
    Output_0011F540 *out = arg2;

    position = SzDuel_GetUnitLoc(*arg0 >> 8, *arg0 & 0xFF);
    i = 0;
    do {
        cells[i].low = cells[i].high = 15;
        i++;
    } while (i < 12);

    {
        u16 value = (u16)TaLogic_GetWarnHideLvl_0011FA80(arg1);
        originalX = position & 0xFF;
        originalY = position >> 8;
        if (TaLogic_GetUnitWarning(originalX, originalY, *arg0, 3, value, 0) == 0) {
            out->id = *arg0;
            out->action = 6;
            out->position = position;
            out->mode = TaLogic_IsDefStyleUnit(*arg0 >> 8, *arg0 & 0xFF, out->position, 1, 0);
            out->value = TaLogic_IsOpenUnit_001211B0(*arg0 >> 8, *arg0 & 0xFF, arg0);
            TaLogic004_InitRogicControl(arg0, arg3);
            return 0;
        } else {
            result = GetMoveRev(SzDuel_GetUnit(*arg0 >> 8, *arg0 & 0xFF), originalX, originalY);
            if (result == 0) {
                out->id = *arg0;
                out->action = 6;
                out->position = position;
                out->mode = TaLogic_IsDefStyleUnit(*arg0 >> 8, *arg0 & 0xFF, out->position, 1, 0);
                out->value = TaLogic_IsOpenUnit_001211B0(*arg0 >> 8, *arg0 & 0xFF, arg0);
                TaLogic004_InitRogicControl(arg0, arg3);
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
                                value = (u16)TaLogic_GetWarnHideLvl_0011FA80(arg1);
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
                    out->value = TaLogic_IsOpenUnit_001211B0(*arg0 >> 8, *arg0 & 0xFF, arg0);
                } else {
                    out->id = *arg0;
                    out->action = 6;
                    out->position = position;
                    out->mode = TaLogic_IsDefStyleUnit(*arg0 >> 8, *arg0 & 0xFF, out->position, 1, 0);
                    out->value = TaLogic_IsOpenUnit_001211B0(*arg0 >> 8, *arg0 & 0xFF, arg0);
                }
                TaLogic004_InitRogicControl(arg0, arg3);
            }
        }
    }
    return 0;
}

s32 TaLogic_GetWarnHideLvl_0011FA80(s32 arg0) {
    if (SzDuel_GetLP(arg0) > 0x3E8) {
        if (SzDuel_GetUnitMonsterCount(arg0) >= 3) {
            return 0x1F4;
        } else {
            return 0x3E8;
        }
    } else {
        return 0x7D0;
    }
}

typedef struct Source_0011FAE0 {
    u16 position;
    u8 pad2[6];
    u32 targets;
} Source_0011FAE0;

typedef struct Output_0011FAE0 {
    u16 position;
    u8 mode;
    u8 pad3;
    u16 target;
    u8 pad6[6];
    s32 flag;
    u8 value;
} Output_0011FAE0;

typedef struct Position_0011FAE0 {
    u8 x : 4;
    u8 y : 4;
} Position_0011FAE0;


static inline u32 target_0011FAE0(void *arg0, u8 which) {
    Source_0011FAE0 *source = arg0;
    if (which == 1) {
        return (u16)(source->targets >> 16);
    }
    return *(u16 *)&source->targets;
}

static inline s32 penalty_0011FAE0(s32 object) {
    if (SzDuel_GetLP(object) > 1000) {
        if (SzDuel_GetUnitMonsterCount(object) >= 3) {
            return 500;
        } else {
            return 1000;
        }
    } else {
        return 2000;
    }
}

s32 TaLogic_GetMinimumTask_AtkMission_0011FAE0(void *arg0, s32 arg1, void *arg2, u8 arg3) {
    extern s32 TaLogic_GetInvadeRoot();
    s32 sourceTarget;
    s32 count;
    s32 pathResult;
    s32 sourceY;
    s32 sourceX;
    s32 selectedFlag;
    Position_0011FAE0 positions[12];
    s32 flag;
    s32 otherTarget;
    s32 j;
    Position_0011FAE0 *walk;
    s32 object;
    u32 targetXWord;
    u32 targetYWord;
    Source_0011FAE0 *source = arg0;
    Output_0011FAE0 *output = arg2;

    targetXWord = target_0011FAE0(arg0, arg3);
    targetYWord = target_0011FAE0(arg0, arg3);
    if (SzDuel_GetUnit(targetYWord >> 8, targetXWord & 0xFF) == 0) {
        TaLogic_InitRogicControl(arg0, 1);
        return -1;
    }

    flag = TaLogic_IsOpenUnit_001211B0(source->position >> 8, source->position & 0xFF, arg0);
    sourceTarget = SzDuel_GetUnitLoc(source->position >> 8, source->position & 0xFF);
    targetXWord = target_0011FAE0(arg0, arg3);
    targetYWord = target_0011FAE0(arg0, arg3);
    otherTarget = SzDuel_GetUnitLoc(targetYWord >> 8, targetXWord & 0xFF);
    walk = positions;
    j = 0;
    do {
        walk->x = walk->y = 15;
        j++;
        walk++;
    } while (j < 12);

    object = SzDuel_GetUnit(source->position >> 8, source->position & 0xFF);
    sourceX = sourceTarget & 0xFF;
    sourceY = sourceTarget >> 8;
    if (GetMoveRev(object, sourceX, sourceY) == 0) {
        s32 cost;
        output->position = source->position;
        output->mode = 6;
        output->target = sourceTarget;
        cost = TaLogic_GetUnitWarning(sourceX, sourceY, arg1, 3, 1,
                            (u8)penalty_0011FAE0(arg1));
        if (cost >= SzDuel_GetUnitAP(source->position >> 8, source->position & 0xFF, 0)) {
            output->value = TaLogic_IsDefStyleUnit(source->position >> 8, source->position & 0xFF,
                                        output->target, 1, 0);
        } else {
            output->value = TaLogic_IsDefStyleUnit(source->position >> 8, source->position & 0xFF,
                                        output->target, 0, 0);
        }
        TaLogic004_InitRogicControl(arg0, arg3);
    } else {
        s32 targetY;
        s32 targetX;
        Position_0011FAE0 *current;
        s32 i;
        s32 bestCost;
        s32 selected;
        s32 penalty;
        u16 position;

        penalty = penalty_0011FAE0(arg1);
        position = source->position;
        pathResult = TaLogic_GetInvadeRoot(position >> 8, position & 0xFF, positions,
                      sourceX, sourceY, targetX = otherTarget & 0xFF,
                      targetY = otherTarget >> 8,
                      target_0011FAE0(arg0, arg3), 0, 30, (u16)penalty);
        count = TaLogic_GetMinGoalCount((u8 *)positions);
        selected = 0xFF;
        if (count > 0) {
            selectedFlag = 0;
            bestCost = 0xFFFF;
            for (i = 0; i < count; i++) {
                s32 state = TaLogic004_IsOpenMoveUnit(source->position >> 8, source->position & 0xFF,
                                          sourceX, sourceY, targetX, targetY, pathResult);
                if (state == 1) {
                    Position_0011FAE0 *forcedPosition = &positions[i];
                    selected = i;
                    selectedFlag = 1;
                    i = count;
                    forcedPosition->x = targetX;
                    forcedPosition->y = targetY;
                } else {
                    s32 cost;
                    s32 penalty = penalty_0011FAE0(arg1);
                    current = &positions[i];
                    cost = TaLogic_GetUnitWarning(current->x, current->y, arg1, 4, 1,
                                        (u8)penalty);
                    if (cost < bestCost) {
                        bestCost = cost;
                        selected = i;
                    } else if (cost == bestCost) {
                        if (((targetX < current->x ? current->x : targetX) -
                             (current->x < targetX ? current->x : targetX)) +
                            ((targetY < current->y ? current->y : targetY) -
                             (current->y < targetY ? current->y : targetY)) <
                            ((targetX < positions[selected].x ? positions[selected].x : targetX) -
                             (positions[selected].x < targetX ? positions[selected].x : targetX)) +
                            ((targetY < positions[selected].y ? positions[selected].y : targetY) -
                             (positions[selected].y < targetY ? positions[selected].y : targetY))) {
                            bestCost = cost;
                            selected = i;
                        }
                    }
                }
            }
        } else {
            output->position = source->position;
            output->mode = 6;
            output->target = sourceTarget;
            output->flag = flag;
            output->value = TaLogic_IsDefStyleUnit(source->position >> 8, source->position & 0xFF,
                                        output->target, 0, 0);
            TaLogic_InitRogicControl(arg0, arg3);
            return 0;
        }
        if (selected != 0xFF) {
            output->position = source->position;
            output->mode = 6;
            output->target = (positions[selected].y << 8) | positions[selected].x;
            output->flag = selectedFlag;
            output->value = TaLogic_IsDefStyleUnit(source->position >> 8, source->position & 0xFF,
                                        output->target, 0, 0);
            TaLogic004_InitRogicControl(arg0, arg3);
            return 0;
        } else {
            output->position = source->position;
            output->mode = 6;
            output->target = sourceTarget;
            output->flag = selectedFlag;
            output->value = TaLogic_IsDefStyleUnit(source->position >> 8, source->position & 0xFF,
                                        output->target, 0, 0);
            TaLogic_InitRogicControl(arg0, arg3);
            return 0;
        }
    }
    return 0;
}

typedef struct Input_00120150 {
    u16 position;
    u16 pad2;
    u32 pad4;
    union {
        u32 pair;
        u16 position;
    } target;
} Input_00120150;

typedef struct Output_00120150 {
    u16 position;
    u8 type;
    u8 pad3;
    u16 target;
    u8 pad6[10];
    u8 value;
} Output_00120150;

typedef struct Position_00120150 {
    u8 x : 4;
    u8 y : 4;
} Position_00120150;


static inline u32 target_00120150(Input_00120150 *src, u8 kind) {
    u32 target;
    if (kind == 1) {
        target = (u16)(src->target.pair >> 16);
    } else {
        target = src->target.position;
    }
    return target;
}

static inline s32 power_00120150(s32 card) {
    if (SzDuel_GetLP(card) > 1000) {
        if (SzDuel_GetUnitMonsterCount(card) >= 3) {
            return 500;
        } else {
            return 1000;
        }
    } else {
        return 2000;
    }
}

static inline void output_00120150(Input_00120150 *src, Output_00120150 *out, s32 target, s32 flag) {
    out->position = src->position;
    out->type = 6;
    out->target = target;
    out->value = TaLogic_IsDefStyleUnit(src->position >> 8, src->position & 0xFF,
                             out->target, flag, 0);
}

s32 TaLogic_GetMinimumTask_TrapMission_00120150(void *arg0, s32 card, void *arg2, u8 kind) {
    extern void TaLogic_GetInvadeRoot();
    Position_00120150 positions[12];
    s32 start;
    Input_00120150 *src = arg0;
    Output_00120150 *out = arg2;
    u32 lowTarget;
    u32 highTarget;

    lowTarget = target_00120150(src, kind);
    highTarget = target_00120150(src, kind);
    if (SzDuel_GetUnit(highTarget >> 8, lowTarget & 0xFF) == 0) {
        TaLogic_InitRogicControl(src, 1);
        return -1;
    }
    start = SzDuel_GetUnitLoc(src->position >> 8, src->position & 0xFF);
    {
        Position_00120150 *p;
        s32 target;
        s32 targetY;
        s32 targetX;
        s32 startY;
        s32 startX;
        s32 count;
        s32 best;
        s32 score;
        s32 i;
        s32 value;
        s32 power;
        Position_00120150 *q;

        lowTarget = target_00120150(src, kind);
        highTarget = target_00120150(src, kind);
        target = SzDuel_GetUnitLoc(highTarget >> 8, lowTarget & 0xFF);
        if (target_00120150(src, kind) == 0xFFFF) {
            output_00120150(src, out, start, 1);
            return 0;
        }
        value = SzDuel_GetUnit(src->position >> 8, src->position & 0xFF);
        startX = start & 0xFF;
        startY = start >> 8;
        if (GetMoveRev(value, startX, startY) == 0 ||
            TaLogic_IsAttackedNow(src->position >> 8, src->position & 0xFF, 0) == 1) {
            output_00120150(src, out, start, 1);
            return 0;
        }
        p = positions;
        i = 0;
        q = p;
        do {
            q->x = q->y = 15;
            ++i;
            ++q;
        } while (i < 12);
        power = power_00120150(card);
        targetX = target & 0xFF;
        targetY = target >> 8;
        TaLogic_GetInvadeRoot(src->position >> 8, src->position & 0xFF, positions,
                     startX, startY, targetX, targetY, target_00120150(src, kind),
                     0, 30, (u16)power);
        count = TaLogic_GetMinGoalCount((u8 *)positions);
        best = 0xFF;
        if (count > 0) {
            score = 0;
            for (i = 0; i < count; ++i, ++p) {
                if (SzDuel_GetMapUnit(p->x, p->y) == 0) {
                    value = TaLogic_GetUnitWarning(p->x, p->y, card, 4, 1,
                                          (u8)power_00120150(card));
                    if (score < value) {
                        score = value;
                        best = i;
                    } else if (value == score) {
                        if (((targetX < p->x ? p->x : targetX) -
                             (p->x < targetX ? p->x : targetX)) +
                            ((targetY < p->y ? p->y : targetY) -
                             (p->y < targetY ? p->y : targetY)) <
                            ((targetX < positions[best].x ? positions[best].x : targetX) -
                             (positions[best].x < targetX ? positions[best].x : targetX)) +
                            ((targetY < positions[best].y ? positions[best].y : targetY) -
                             (positions[best].y < targetY ? positions[best].y : targetY))) {
                            score = value;
                            best = i;
                        }
                    }
                }
            }
        } else {
            output_00120150(src, out, start, 1);
            return 0;
        }
        if (best != 0xFF) {
            out->position = src->position;
            out->type = 6;
            out->target = (positions[best].y << 8) | positions[best].x;
            out->value = TaLogic_IsDefStyleUnit(src->position >> 8, src->position & 0xFF,
                                      out->target, 0, 0);
        } else {
            output_00120150(src, out, start, 0);
            return 0;
        }
    }
    return 0;
}

typedef struct Input_001206F0 {
    u16 position;
    u16 unk2;
    u16 command;
    u16 unk6;
    union {
        u32 word;
        u16 low;
    } targets;
} Input_001206F0;

typedef struct Output_001206F0 {
    u16 position;
    u8 action;
    u8 unk3;
    u16 destination;
    u8 unk6[6];
    s32 value;
    u8 state;
} Output_001206F0;

typedef struct Position_001206F0 {
    u8 x : 4;
    u8 y : 4;
} Position_001206F0;

#define target_001206F0(src, mode) ((mode) == 1 ? \
    (u32)(u16)((src)->targets.word >> 16) : (u32)(src)->targets.low)

static inline s32 option_001206F0(s32 card) {
    if (SzDuel_GetLP(card) > 1000) {
        if (SzDuel_GetUnitMonsterCount(card) >= 3) {
            return 500;
        }
        return 1000;
    }
    return 2000;
}

#define min_001206F0(a, b) ((a) < (b) ? (u8)(a) : (b))
#define max_001206F0(a, b) ((b) < (a) ? (u8)(a) : (b))
#define distance_001206F0(pos, src, mode) ( \
    (max_001206F0((pos)->x, target_001206F0(src, mode) & 0xFF) - \
     min_001206F0((pos)->x, target_001206F0(src, mode) & 0xFF)) + \
    (max_001206F0((u8)(pos)->y, target_001206F0(src, mode) >> 8) - \
     min_001206F0((u8)(pos)->y, target_001206F0(src, mode) >> 8)))

s32 TaLogic_GetMinimumTask_MoveMission_001206F0(u32 *arg0, s32 arg1, u16 *arg2, u8 arg3, u8 arg4) {
    extern s32 TaLogic_GetUnitWarning(s32, s32, s32, s32, s32, s32);
    extern s32 TaLogic_IsDefStyleUnit(s32, s32, s32, u8, s32);
    extern void TaLogic_GetRoot(s32, s32, void *, s32, s32, s32, s32, s32, u8);
    Position_001206F0 positions[12];
    s32 y;
    s32 bestScore;
    s32 mode;
    s32 current;
    s32 command;

    current = SzDuel_GetUnitLoc(((Input_001206F0 *)arg0)->position >> 8, ((Input_001206F0 *)arg0)->position & 0xFF);
    mode = arg3;
    if (target_001206F0((Input_001206F0 *)arg0, mode) == 0xFFFF && current == target_001206F0((Input_001206F0 *)arg0, mode)) {
        arg2[0] = ((Input_001206F0 *)arg0)->position;
        ((Output_001206F0 *)arg2)->action = 6;
        arg2[2] = current;
        ((Output_001206F0 *)arg2)->state = TaLogic_IsDefStyleUnit(((Input_001206F0 *)arg0)->position >> 8, ((Input_001206F0 *)arg0)->position & 0xFF,
            arg2[2], arg4, 0);
        ((Output_001206F0 *)arg2)->value = TaLogic_IsOpenUnit_001211B0(((Input_001206F0 *)arg0)->position >> 8, ((Input_001206F0 *)arg0)->position & 0xFF, arg0);
        TaLogic004_InitRogicControl(arg0, arg3);
        return 0;
    } else {
        command = (((Input_001206F0 *)arg0)->command >> 8) & 0xFF;
        if (command == 15) {
            s32 x = current & 0xFF;
            s32 target;

            y = current >> 8;
            arg2[0] = ((Input_001206F0 *)arg0)->position;
            ((Output_001206F0 *)arg2)->action = 6;
            target = x | (GetCap(7, y +
                (GetMoveRev(SzDuel_GetUnit(((Input_001206F0 *)arg0)->position >> 8, ((Input_001206F0 *)arg0)->position & 0xFF), x, y) & 15)) << 8);
            arg2[2] = target;
            target = SzDuel_GetMapUnitID(target_001206F0((Input_001206F0 *)arg0, mode) & 0xFF,
                target_001206F0((Input_001206F0 *)arg0, mode) >> 8);
            if (target < 0) {
                target = 0xFFFF;
            }
            TaLogic_GetRoot(((Input_001206F0 *)arg0)->position >> 8, ((Input_001206F0 *)arg0)->position & 0xFF, positions, x, y,
                arg2[2] & 0xFF, arg2[2] >> 8, (u16)target, 2);
            if (TaLogic_GetMinGoalCount((u8 *)positions) == 0) {
                arg2[2] = current;
            }
            ((Output_001206F0 *)arg2)->state = TaLogic_IsDefStyleUnit(((Input_001206F0 *)arg0)->position >> 8, ((Input_001206F0 *)arg0)->position & 0xFF,
                arg2[2], arg4, 0);
            ((Output_001206F0 *)arg2)->value = TaLogic_IsOpenUnit_001211B0(((Input_001206F0 *)arg0)->position >> 8, ((Input_001206F0 *)arg0)->position & 0xFF, arg0);
            TaLogic004_InitRogicControl(arg0, arg3);
            return 0;
        } else {
            if (command == 16) {
                s32 y2;
                s32 x = current & 0xFF;
                s32 target;

                y2 = current >> 8;
                arg2[0] = ((Input_001206F0 *)arg0)->position;
                ((Output_001206F0 *)arg2)->action = 6;
                target = x | (GetCap(0, y2 -
                    (GetMoveRev(SzDuel_GetUnit(((Input_001206F0 *)arg0)->position >> 8, ((Input_001206F0 *)arg0)->position & 0xFF), x, y2) & 15)) << 8);
                arg2[2] = target;
                target = SzDuel_GetMapUnitID(target_001206F0((Input_001206F0 *)arg0, mode) & 0xFF,
                    target_001206F0((Input_001206F0 *)arg0, mode) >> 8);
                if (target < 0) {
                    target = 0xFFFF;
                }
                TaLogic_GetRoot(((Input_001206F0 *)arg0)->position >> 8, ((Input_001206F0 *)arg0)->position & 0xFF, positions, x, y2,
                    arg2[2] & 0xFF, arg2[2] >> 8, (u16)target, 2);
                if (TaLogic_GetMinGoalCount((u8 *)positions) == 0) {
                    arg2[2] = current;
                }
                ((Output_001206F0 *)arg2)->state = TaLogic_IsDefStyleUnit(((Input_001206F0 *)arg0)->position >> 8, ((Input_001206F0 *)arg0)->position & 0xFF,
                    arg2[2], arg4, 0);
                ((Output_001206F0 *)arg2)->value = TaLogic_IsOpenUnit_001211B0(((Input_001206F0 *)arg0)->position >> 8, ((Input_001206F0 *)arg0)->position & 0xFF, arg0);
                TaLogic004_InitRogicControl(arg0, arg3);
                return 0;
            } else {
                Position_001206F0 *p = positions;
                s32 count;
                s32 i;
                s32 best;
                s32 target;
                s32 j;
                Position_001206F0 *init;

                j = 0;
                init = p;
                do {
                    init->x = init->y = 15;
                    init++;
                    j++;
                } while (j < 12);
                target = SzDuel_GetMapUnitID(target_001206F0((Input_001206F0 *)arg0, mode) & 0xFF,
                    target_001206F0((Input_001206F0 *)arg0, mode) >> 8);
                if (target < 0) {
                    target = 0xFFFF;
                }
                TaLogic_GetRoot(((Input_001206F0 *)arg0)->position >> 8, ((Input_001206F0 *)arg0)->position & 0xFF, positions,
                    current & 0xFF, current >> 8, target_001206F0((Input_001206F0 *)arg0, mode) & 0xFF,
                    target_001206F0((Input_001206F0 *)arg0, mode) >> 8, (u16)target, 7);
                count = TaLogic_GetMinGoalCount((u8 *)positions);
                if (count > 0) {
                    best = 0xFF;
                    bestScore = 0xFFFF;
                    for (i = 0; i < count; i++, p++) {
                        s32 score;
                        if (SzDuel_GetMapUnit(p->x, p->y) == 0) {
                            score = TaLogic_GetUnitWarning(p->x, p->y, arg1, 4, 1, (u8)option_001206F0(arg1));
                            if (score < bestScore) {
                                bestScore = score;
                                best = i;
                            } else if (score == bestScore) {
                                if (distance_001206F0(p, (Input_001206F0 *)arg0, mode) <
                                    distance_001206F0(&positions[best], (Input_001206F0 *)arg0, mode)) {
                                    bestScore = score;
                                    best = i;
                                }
                            }
                        }
                    }
} else {
                    arg2[0] = ((Input_001206F0 *)arg0)->position;
                    ((Output_001206F0 *)arg2)->action = 6;
                    arg2[2] = current;
                    ((Output_001206F0 *)arg2)->state = TaLogic_IsDefStyleUnit(((Input_001206F0 *)arg0)->position >> 8, ((Input_001206F0 *)arg0)->position & 0xFF,
                        arg2[2], arg4, 0);
                    ((Output_001206F0 *)arg2)->value = TaLogic_IsOpenUnit_001211B0(((Input_001206F0 *)arg0)->position >> 8, ((Input_001206F0 *)arg0)->position & 0xFF, arg0);
                    TaLogic004_InitRogicControl(arg0, arg3);
                    return 0;
                }
                    if (best != 0xFF) {
                        arg2[0] = ((Input_001206F0 *)arg0)->position;
                        ((Output_001206F0 *)arg2)->action = 6;
                        arg2[2] = (positions[best].y << 8) | positions[best].x;
                        ((Output_001206F0 *)arg2)->state = TaLogic_IsDefStyleUnit(((Input_001206F0 *)arg0)->position >> 8, ((Input_001206F0 *)arg0)->position & 0xFF,
                            arg2[2], arg4, 0);
                        ((Output_001206F0 *)arg2)->value = TaLogic_IsOpenUnit_001211B0(((Input_001206F0 *)arg0)->position >> 8, ((Input_001206F0 *)arg0)->position & 0xFF, arg0);
                    } else {
                        arg2[0] = ((Input_001206F0 *)arg0)->position;
                        ((Output_001206F0 *)arg2)->action = 6;
                        arg2[2] = current;
                        ((Output_001206F0 *)arg2)->state = TaLogic_IsDefStyleUnit(((Input_001206F0 *)arg0)->position >> 8, ((Input_001206F0 *)arg0)->position & 0xFF,
                            arg2[2], arg4, 0);
                        ((Output_001206F0 *)arg2)->value = TaLogic_IsOpenUnit_001211B0(((Input_001206F0 *)arg0)->position >> 8, ((Input_001206F0 *)arg0)->position & 0xFF, arg0);
                    }
                    TaLogic004_InitRogicControl(arg0, arg3);
                
            }
        }
    }
    return 0;
}

s32 TaLogic_IsOpenUnit_001211B0(s32 arg0, s32 arg1, void *arg2) {
    extern s32 SzDuel_GetUnitCardNo();
    s32 i;
    s32 free;
    s32 owner;
    u8 count;
    u32 *info;

    free = 0;
    owner = Ta_IsUnitControl(arg0, arg1);
    count = 0;
    if (SzDuel_GetUnitStatus(arg0, arg1, 4) != 0) {
        return 0;
    }
    for (i = 1; i < 5; i++) {
        if ((SzDuel_GetUnitKind(arg0, i) & 0x1F) == 0xE && arg0 == Ta_IsUnitControl(arg0, i)) {
            count++;
        }
        if ((SzDuel_GetUnitKind((arg0 == 0) ? 1 : 0, i) & 0x1F) == 0xE &&
            arg0 == Ta_IsUnitControl((arg0 == 0) ? 1 : 0, i)) {
            count++;
        }
    }
    switch (SzDuel_GetUnitKind(arg0, arg1) >> 5) {
    case 0:
        switch (SzDuel_GetUnitCardNo(arg0, arg1)) {
        case 0x202:
            if (count >= 3) {
                return 1;
            }
            break;
        case 0x1F6: {
            s16 list[16];
            u16 *p;
            s32 j;
            s32 position;

            p = (u16 *)list;
            for (j = 0; j < 22; j++) {
                *p++ = 0xFFFF;
            }
            TaUtil_GetUnitLst((owner == 0) ? 1 : 0, 3, list);
            position = TaLogic_GetMaxApUnit((u16 *)list);
            if (owner != Ta_IsUnitControl(position >> 8, position & 0xFF)) {
                return 1;
            }
            break;
        }
        case 0x20B:
            for (i = 1; i < 11; i++) {
                if (owner != Ta_IsUnitControl(owner, i) && SzDuel_GetUnitStatus(owner, i, 4) == 0) {
                    free++;
                }
                if (owner != Ta_IsUnitControl((owner == 0) ? 1 : 0, i) &&
                    SzDuel_GetUnitStatus((owner == 0) ? 1 : 0, i, 4) == 0) {
                    free++;
                }
            }
            if (free >= 6) {
                return 1;
            }
            break;
        }
        return 2;
    case 1:
        if (TaLogic_GetActionReaction(arg0, arg1, 0, 0, 6, 0) == 5) {
            return 2;
        }
        info = Ta_GetUnitEffect(arg0, arg1, 0);
        if (info == NULL) {
            return 2;
        }
        switch (*info >> 8) {
        case 0x12:
            if (count >= 3) {
                return 1;
            }
            break;
        }
        return 2;
    case 2:
    case 3:
    case 4:
    case 5:
    default:
        return 0;
    }
}

static inline s32 max_001214E0(s32 a, s32 b) {
    if (a < b) {
        return b;
    }
    return a;
}

s32 TaLogic004_IsOpenMoveUnit(s32 arg0, s32 arg1, s32 arg2, s32 arg3,
                  s32 arg4, s32 arg5, s32 arg6) {
    s32 min_y;
    s32 min_x;

    min_y = arg3 < arg5 ? arg3 : arg5;
    arg5 = max_001214E0(arg5, arg3);
    min_x = arg2 < arg4 ? arg2 : arg4;
    arg4 = max_001214E0(arg4, arg2);
    if ((arg4 - min_x) + (arg5 - min_y) != 2 || arg6 != 2) {
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

void TaLogic004_InitRogicControl(void *arg0, u8 arg1) {
    if (arg1 < 2) {
        if (arg1 == 1) {
            *(u32 *)((u8 *)arg0 + 8) =
                (*(u32 *)((u8 *)arg0 + 8) & 0xFFFF) | 0xFFFF0000;
        } else {
            *(u32 *)((u8 *)arg0 + 8) =
                (*(u32 *)((u8 *)arg0 + 8) & 0xFFFF0000) | 0xFFFF;
        }
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
} Req_00121630;

typedef struct {
    u8 pad0[0x160];
    u16 list[32];    /* 0x160 */
    u8 idx : 5;      /* 0x1A0 */
    u8 pad1A0 : 3;
    u8 pad1A1;
    u16 count;       /* 0x1A2 */
} Work_00121630;

s32 TaLogic_GetInputQueFromMinimumTask(void *, void *, s32);

s32 func_00121630(s32 arg0, void *arg1) {
    Req_00121630 req;
    Work_00121630 *w;
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
        if (TaLogic_GetMinimumTask_0011C600(w, &req, arg0) == 0) {
            return 0x800;
        }
        if (TaLogic_GetInputQueFromMinimumTask(w, &req, arg0) < 0) {
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

s32 TaLogic_GetMinimumTask_00121800(void *work, void *arg1, s32 arg2) {
    u16 *arg0 = work;
    s32 side;
    s32 found;
    s32 result;
    s32 index;

    side = SzDuel_GetTurnOwner();
    found = 0;
    if ((result = TaLogic_GetNextActiveUnit_00121E90(arg0, side, (s32)arg1)) < 0) {
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
    TaLogic_CommandUnit_00121CE0(arg0 + index * 8);
    switch ((arg0[index * 8 + 2] >> 8) & 0xFF) {
    case 5:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_RunMission_00124F60(arg0 + index * 8, side, arg1, 1);
            found = 1;
        }
        break;
    case 2:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            if (TaLogic_GetMinimumTask_AtkMission_00125500(arg0 + index * 8, side, arg1, 1) < 0) {
                TaLogic005_InitRogicControl(arg0 + index * 8, 1);
                return 1;
            }
            found = 1;
        }
        break;
    case 10:
        if (TaLogic_GetMinimumTask_Summon_00122D30(arg0[index * 8], side, (s32)arg1) < 0) {
            TaLogic005_InitRogicControl(arg0 + index * 8, 1);
            *(u8 *)((u8 *)arg1 + 2) = 0xFF;
            *(s32 *)((u8 *)arg1 + 0xC) = 0;
        } else {
            TaLogic005_InitRogicControl(arg0 + index * 8, 1);
            found = 1;
        }
        break;
    case 6:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_MoveMission_00125B70(arg0 + index * 8, side, arg1, 1, 0);
            found = 1;
        }
        break;
    case 3:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_MoveMission_00125B70(arg0 + index * 8, side, arg1, 1, 1);
            found = 1;
        }
        break;
    case 9:
        TaLogic_GetMinimumTask_EncMission(arg0 + index * 8, side, arg1, 1, 0, TaLogic_GetWarnHideLvl_001254A0(side), 2, 1);
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
            TaLogic_GetMinimumTask_RunMission_00124F60(arg0 + index * 8, side, arg1, 0);
            found = 1;
        }
        break;
    case 2:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            if (TaLogic_GetMinimumTask_AtkMission_00125500(arg0 + index * 8, side, arg1, 0) < 0) {
                TaLogic_GetMinimumTask_RunMission_00124F60(arg0 + index * 8, side, arg1, 0);
            }
            found = 1;
        }
        break;
    case 10:
        if (TaLogic_GetMinimumTask_Summon_00122D30(arg0[index * 8], side, (s32)arg1) < 0) {
            TaLogic005_InitRogicControl(arg0 + index * 8, 0);
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
            TaLogic_GetMinimumTask_MoveMission_00125B70(arg0 + index * 8, side, arg1, 0, 0);
            found = 1;
        }
        break;
    case 3:
        if (SzDuel_GetUnitStatus(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            TaLogic_GetMinimumTask_MoveMission_00125B70(arg0 + index * 8, side, arg1, 0, 1);
            found = 1;
        }
        break;
    case 9:
        TaLogic_GetMinimumTask_EncMission(arg0 + index * 8, side, arg1, 0, 0, TaLogic_GetWarnHideLvl_001254A0(side), 2, 1);
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

typedef struct Unit_00121CE0 {
    u16 pos;
    u16 unk2;
    u16 unk4;
    u16 unk6;
    s32 unk8;
} Unit_00121CE0;


s32 TaLogic_CommandUnit_00121CE0(void *arg0) {
    Unit_00121CE0 *unit = arg0;
    s32 handle;

    handle = Ta_IsUnitControl(unit->pos >> 8, unit->pos & 0xFF);
    if (SzDuel_GetUnit(unit->pos >> 8, unit->pos & 0xFF) != 0 &&
        SzDuel_GetUnitStatus(unit->pos >> 8, unit->pos & 0xFF, 0) == 0 && unit->pos != 0xFFFF) {
    if ((unit->pos & 0xFF) == 0) {
        if (unit->unk8 == -1) {
            TaLogic_CommandStdLDUnit(unit, 3, 2, 0);
        }
    } else {
        switch (SzDuel_GetUnitKind(unit->pos >> 8, unit->pos & 0xFF) >> 5) {
        case 0:
            if (TaUtil_IsExMonster(unit->pos >> 8, unit->pos & 0xFF) == 1) {
                TaLogic_CommandEfcMonster_001229F0(unit, 1);
            } else {
                TaLogic_CommandBtlUnit_00122270(unit, 1);
            }
            break;
        case 1:
        case 5:
            unit->unk4 = 0x5FF;
            break;
        case 2:
            TaLogic_CommandEncUnit(unit, 2, 0, (u8)TaLogic_GetWarnHideLvl_001254A0(handle));
            break;
        case 4:
            TaLogic005_CommandTrapBUnit(unit);
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

s32 TaLogic_GetNextActiveUnit_00121E90(u16 *arg0, s32 arg1, s32 arg2) {
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
    TaLogic_CommandUnit_00121CE0(arg0 + idx * 8);
    if (((arg0[idx * 8 + 2] >> 8) & 0xFF) == 10) {
        if (SzDuel_InqHandPhase(arg1) == 1 && TaLogic_GetMinimumTask_Summon_00122D30(pos, arg1, arg2) >= 0) {
            return pos | 0x10000;
        }
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_GetUnitStatus(arg1, 0, 0) == 0) {
        if (TaLogic_IsUnitReadyMove(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (SzDuel_InqHandPhase(arg1) == 1 && TaLogic_GetMinimumTask_Summon_00122D30(pos, arg1, arg2) >= 0) {
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
} Entry_00122270;

typedef struct {
    u16 card;
    u8 flag;
    u8 pad;
} Slot_00122270;

void TaLogic_CommandBtlUnit_00122270(void *arg0, s32 arg1) {
    extern void TaLogic_InitIgnoreLst();
    extern s32 TaLogic_IsRootOpen();
    extern s32 TaLogic005_GetNearUnit();
    extern s32 TaLogic_GetWarnHideLvl_001254A0(s32);
    extern void TaLogic005_CommandRoutineUnit(void *);
    Entry_00122270 *entry = arg0;
    s32 side;
    s32 player;
    s32 other;
    s32 pos;
    s32 otherPos;
    s32 i;
    u8 work[0x70];
    Slot_00122270 list[22];
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
            switch (TaLogic005_GetNearUnit(entry, 0, player, pos & 0xFF, pos >> 8,
                                  Ta_GetCurrentSide(entry->coordinates >> 8, entry->coordinates & 0xFF) == 0 ? 1 : 0,
                                  i & 0xFF, TaLogic_GetWarnHideLvl_001254A0(side), list, 0, &countA, &countB, 3, work)) {
            case 3:
                entry->state = 0x2FF;
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
            if (i > 3) {
                break;
            }
        }
        TaLogic005_CommandRoutineUnit(entry);
    }
}

void TaLogic005_GetNearUnit(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28) {
    TaLogic_GetNearUnit(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
                  arg_sp0, arg_sp8, arg_sp10, arg_sp18, arg_sp20,
                  0, 1500, arg_sp28);
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
} Entry_00122530;


void TaLogic005_CommandRoutineUnit(void *arg0) {
    Entry_00122530 *entry = arg0;
    s32 packed;
    s32 position;
    s32 result[2];
    u16 coordinates;

    coordinates = entry->coordinates;
    if (SzDuel_GetUnit((s32) coordinates >> 8, coordinates & 0xFF) != 0) {
        coordinates = entry->coordinates;
        Ta_GetCurrentSide((s32) coordinates >> 8, coordinates & 0xFF);
        coordinates = entry->coordinates;
        packed = SzDuel_GetUnitLoc((s32) coordinates >> 8, coordinates & 0xFF);
        entry->state = 0x6FF;
        coordinates = entry->coordinates;
        if (SzDuel_GetUnitAP((s32) coordinates >> 8, coordinates & 0xFF, 0) >= 0x5DC) {
            coordinates = entry->coordinates;
            position = TaLogic005_GetUnitOnCycleRoot((s32) coordinates >> 8, coordinates & 0xFF);
            if (position >= 0) {
                entry->data.word = entry->data.halves.low | (TaLogic_GetCyclePoint((position + 1) % 8) << 16);
                return;
            }
            entry->data.word = entry->data.halves.low | (TaLogic005_GetNearCyclePoint(packed & 0xFF, packed >> 8) << 16);
            return;
        }
        coordinates = entry->coordinates;
        TaLogic005_GetNearDefensePoint(SzDuel_GetUnit((s32) coordinates >> 8, coordinates & 0xFF), packed & 0xFF, packed >> 8, result);
        if (result[0] >= 0) {
            entry->data.word = (result[0] << 16) | entry->data.halves.low;
            return;
        }
        entry->state = 0x5FF;
    }
}

s32 TaLogic005_GetUnitOnCycleRoot(s32 arg0, s32 arg1) {
    s32 x;
    s32 y;

    x = SzDuel_GetUnitLoc(arg0, arg1) & 0xFF;
    y = SzDuel_GetUnitLoc(arg0, arg1) >> 8;
    if ((x >= 2) && (x < 6) && (y == 0)) {
        return 0;
    }
    if ((x == 6) && (y >= 0) && (y < 4)) {
        return 1;
    }
    if ((x > 4) && (x < 7) && (y == 4)) {
        return 2;
    }
    if ((x == 4) && (y >= 4) && (y < 6)) {
        return 3;
    }
    if ((x > 0) && (x < 5) && (y == 6)) {
        return 4;
    }
    if ((x == 0) && (y > 2) && (y < 7)) {
        return 5;
    }
    if ((x >= 0) && (x < 2) && (y == 2)) {
        return 6;
    }
    if ((x == 2) && (y > 0) && (y < 3)) {
        return 7;
    }
    return -1;
}

s32 TaLogic005_GetNearCyclePoint(s32 arg0, s32 arg1) {
    s32 var_s0;
    s32 var_s1;
    s32 var_s2;
    s32 var_s3;
    s32 var_s6;
    s32 var_v0;

    var_s1 = -1;
    var_s0 = 0;
    do {
        if (arg1 < (TaLogic_GetCyclePoint(var_s0) >> 8)) {
            var_s2 = arg1;
        } else {
            var_s2 = TaLogic_GetCyclePoint(var_s0) >> 8;
        }
        if ((TaLogic_GetCyclePoint(var_s0) >> 8) < arg1) {
            var_s3 = arg1;
        } else {
            var_s3 = TaLogic_GetCyclePoint(var_s0) >> 8;
        }
        if (arg0 < (TaLogic_GetCyclePoint(var_s0) & 0xFF)) {
            var_s6 = arg0;
        } else {
            var_s6 = TaLogic_GetCyclePoint(var_s0) & 0xFF;
        }
        if ((TaLogic_GetCyclePoint(var_s0) & 0xFF) < arg0) {
            var_v0 = arg0;
        } else {
            var_v0 = TaLogic_GetCyclePoint(var_s0) & 0xFF;
        }
        if (((var_v0 - var_s6) + (var_s3 - var_s2)) >= -1) {
            var_s1 = TaLogic_GetCyclePoint(var_s0);
        }
        var_s0 += 1;
    } while (var_s0 < 8);
    return var_s1;
}

s32 TaLogic_GetCyclePoint(s32 arg0) {
    switch (arg0) {
    case 0:
        return 2;
    case 1:
        return 6;
    case 2:
        return 0x406;
    case 3:
        return 0x404;
    case 4:
        return 0x604;
    case 5:
        return 0x600;
    case 6:
        return 0x200;
    case 7:
        return 0x202;
    default:
        return 2;
    }
}

typedef struct Unit_001229F0 {
    u16 id;
    u8 pad02[2];
    s16 field04;
    u8 pad06[2];
    u16 field08;
    u16 field0A;
} Unit_001229F0;

void TaLogic_CommandEfcMonster_001229F0(void *arg0, s32 arg1) {
    extern s32 SzDuel_GetUnitCardNo();
    extern void TaLogic_CommandBtlUnit_00122270();
    s32 side;
    s32 value;
    u8 count = 0;
    Unit_001229F0 *unit = arg0;
    s32 i;

    if (SzDuel_GetUnit(unit->id >> 8, unit->id & 0xFF) != 0) {
        side = Ta_GetCurrentSide(unit->id >> 8, unit->id & 0xFF);
        value = SzDuel_GetUnitLoc(unit->id >> 8, unit->id & 0xFF);
        switch (SzDuel_GetUnitCardNo(unit->id >> 8, unit->id & 0xFF)) {
        case 0x235:
            i = 6;
            do {
                if (SzDuel_GetUnitStatus(side, i, 4) != 0) {
                    if (side == Ta_IsUnitControl(side, i)) {
                        count++;
                    }
                }
                if (SzDuel_GetUnitStatus(side == 0 ? 1 : 0, i, 4) != 0) {
                    if (side == Ta_IsUnitControl(side == 0 ? 1 : 0, i)) {
                        count++;
                    }
                }
                i++;
            } while (i < 11);
            if (count > 0) {
                unit->field04 = 0x3FF;
                *(u32 *)&unit->field08 = (value << 16) | unit->field08;
            }
            break;
        }
        TaLogic_CommandBtlUnit_00122270(unit, 0);
    }
}

typedef struct Data_00122B50 {
    u16 id;
    u16 pad2;
    s16 field4;
    u16 pad6;
    u32 field8;
} Data_00122B50;

void TaLogic005_CommandTrapBUnit(void *arg0) {
    Data_00122B50 *p;
    s32 var_s1;
    s32 temp_s2;
    s32 var_s3;
    s32 temp_v0_4;
    s32 var_s4;
    u16 temp_v0;

    extern s32 SzDuel_GetUnitCardNo();

    p = arg0;
    temp_v0 = p->id;
    if (SzDuel_GetUnit((s32)temp_v0 >> 8, temp_v0 & 0xFF) != 0) {
        Ta_GetCurrentSide((s32)p->id >> 8, p->id & 0xFF);
        temp_s2 = SzDuel_GetUnitLoc((s32)p->id >> 8, p->id & 0xFF);
        temp_v0_4 = SzDuel_GetUnitCardNo((s32)p->id >> 8, p->id & 0xFF);
        var_s4 = -1;
        switch (temp_v0_4) {
        case 0x33D:
            p->field4 = 0x3FF;
            p->field8 = (s32)(u16)p->field8;
            break;
        case 0x332:
            p->field4 = 0x3FF;
            p->field8 = (s32)((u16)p->field8 | 0x01000000);
            break;
        case 0x334:
            {
                s32 var_s5;
                s32 var_s2;

                var_s3 = var_s4;
                p->field4 = 0x3FF;
                for (var_s1 = 0; var_s1 < 7; var_s1++) {
                    for (var_s5 = 0, var_s2 = 0; var_s5 < 7; var_s5++, var_s2 += 0x100) {
                        if ((SzDuel_GetField(var_s1, var_s5) == 1) &&
                            (SzDuel_GetMapUnit(var_s1, var_s5) == 0) &&
                            (((((var_s1 < (temp_s2 & 0xFF)) ? (temp_s2 & 0xFF) : var_s1) -
                               (((temp_s2 & 0xFF) < var_s1) ? (temp_s2 & 0xFF) : var_s1)) +
                              (((var_s5 < (temp_s2 >> 8)) ? (temp_s2 >> 8) : var_s5) -
                               (((temp_s2 >> 8) < var_s5) ? (temp_s2 >> 8) : var_s5))) > var_s3)) {
                            var_s4 = var_s2 | var_s1;
                        }
                    }
                }
                if (var_s4 >= 0) {
                    p->field8 = (s32)((u16)p->field8 | 0x01000000);
                } else {
                    p->field4 = 0x5FF;
                }
            }
            break;
        }
        p->field4 = 0x5FF;
    }
}

typedef struct {
    s16 card;
    u8 f2;
    u8 pad3;
    s16 f4;
    u8 pad6[6];
    s32 fC;
} Act_00122D30;

typedef struct {
    u8 pad0[0x3C];
    u16 id;
    u8 pad3E[0x22];
} Card_00122D30;


s32 TaLogic_GetMinimumTask_Summon_00122D30(s32 arg0, s32 arg1, s32 arg2) {
    extern s32 TaLogic_GetUnitNum(s32, s32);
    Card_00122D30 buf;
    s32 res;
    s32 type;
    Act_00122D30 *act = (Act_00122D30 *)arg2;
    s32 card;
    s32 r;

    act->card = arg0;
    if (SzDuel_InqHandPhase(arg1) == 0) {
        return -1;
    }
    if (TaLogic_GetUnitNum(arg1, 0) == 5 && TaLogic_GetUnitNum(arg1, 1) == 5) {
        return -1;
    }
    if ((type = TaLogic_IsHandPlay_00123740(arg1, &buf)) < 0) {
        return -1;
    }
    act->f2 = 10;
    act->fC = 0;
    card = SzDuel_GetUnitLoc(arg0 >> 8, arg0 & 0xFF);
    if (type == 0) {
        if (TaLogic005_SetComboQue(arg1, (u8 *)act, &buf) >= 0) {
            res = TaLogic_GetNearCard2(&buf, card & 0xFF, card >> 8, arg1 == 0 ? 1 : 0, 2, 0x1F, 2, 2, 0, TaLogic_GetWarnHideLvl_001254A0(arg1));
            if (res < 0) {
                if (SzDuel_GetUnitMonsterCount(arg1) < 4) {
                    r = TaLogic005_GetSummonPiece(arg1, type, &buf, res);
                    if (r < 0) {
                        return -1;
                    }
                    act->f4 = r;
                    return 1;
                }
            } else {
                r = TaLogic005_GetSummonPiece(arg1, type, &buf, res);
                if (r < 0) {
                    return -1;
                }
                act->f4 = r;
                return 1;
            }
        }
    } else {
        res = TaLogic_GetNearCard2(&buf, card & 0xFF, card >> 8, arg1 == 0 ? 1 : 0, 2, 0x1F, 2, 2, 0, TaLogic_GetWarnHideLvl_001254A0(arg1));
    }
    if (type == 3) {
        TaLogic_SetSpecialComboQue_00124C90(arg1, act, &buf, 1);
        r = TaLogic005_GetSummonPiece(arg1, type, &buf, res);
        if (r < 0) {
            return -1;
        }
        act->f4 = r;
        return 1;
    } else if (type == 2) {
        TaLogic_SetSpecialComboQue_00124C90(arg1, act, &buf, 0);
        r = TaLogic005_GetSummonPiece(arg1, type, &buf, res);
        if (r < 0) {
            return -1;
        }
        act->f4 = r;
        return 1;
    } else {
        if (TaLogic005_GetSpellPlay(arg1, (u8 *)act, &buf, buf.id) < 0) {
            return -1;
        }
        r = TaLogic005_GetSummonPiece(arg1, type, &buf, -1);
        if (r < 0) {
            return -1;
        }
        act->f4 = r;
        return 1;
    }
}

typedef struct Nibbles_00123010 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_00123010;


s32 TaLogic005_GetSummonPiece(s32 arg0, u8 arg1, void *arg2, s32 arg3) {
    Nibbles_00123010 path[12];
    u8 info[8];
    s32 n;
    Nibbles_00123010 *p;
    u8 kind;

    extern s32 TaLogic_GetSommonPiecePreference_00124F50();
    extern s32 TaLogic_IsUnitWin4();
    extern s32 TaLogic_GetInvadeRoot2();
    extern s32 TaLogic_GetRoot2(s32, s32, s32, s32, s32, s32, u16, u8);

    if (arg2 == NULL) {
        return -1;
    }
    p = path;
    n = 0;
    do {
        p->low = p->high = 15;
        n++;
        p++;
    } while (n < 12);

    kind = *((u8 *)arg2 + 0x3E) >> 5;
    if (kind == 0 || kind == 3) {
        if (arg3 >= 0) {
            s32 position;
            s32 y;
            s32 x;
            s32 i;
            s32 target_y;
            s32 target_x;
            s32 best_position;
            s32 best_distance;
            s32 target;
            s32 distance;

            best_distance = 255;
            best_position = 65535;
            target = SzDuel_GetUnitLoc(arg3 >> 8, arg3 & 255);
            i = 0;
            target_y = target >> 8;
            target_x = target & 255;
            do {
                if ((position = TaLogic_GetSommonPiecePreference_00124F50(arg0, i)) >= 0) {
                    x = position & 255;
                    y = position >> 8;
                    if (SzDuel_GetField(x, y) != 8 &&
                        (SzDuel_GetField(x, y) != 9 || Ta_IsVirus_Chk3(arg2, x, y) != 1) &&
                        SzDuel_GetMapUnit(x, y) == 0) {
                        if (TaLogic_IsUnitWin4(arg2, arg3, TaLogic_GetWarnHideLvl_001254A0(arg0), target_x, target_y, 0) > 0) {
                            distance = TaLogic_GetInvadeRoot2(arg2, path, x, y, target_x, target_y, arg3, 0, 3,
                                                    (u16)TaLogic_GetWarnHideLvl_001254A0(arg0));
                        } else {
                            distance = TaLogic_GetRoot2((s32)arg2, (s32)path, x, y, target_x, target_y, arg3, 3);
                        }
                        if (TaLogic_GetMinGoalCount((u8 *)path) > 0 && distance < best_distance) {
                            best_distance = distance;
                            best_position = position;
                        }
                    }
                }
                i++;
            } while (i < 8);
            if (best_position != 65535) {
                return best_position;
            }
            best_position = -1;
            return best_position;
        } else {
            s32 y;
            s32 x;
            s32 i;
            s32 best_distance;
            s32 best_position;
            s32 distance;

            best_distance = 14;
            best_position = -1;
            i = 0;
            do {
                if ((arg3 = TaLogic_GetSommonPiecePreference_00124F50(arg0, i)) >= 0) {
                    x = arg3 & 255;
                    y = arg3 >> 8;
                    if (SzDuel_GetField(x, y) != 8 &&
                        (SzDuel_GetField(x, y) != 9 || Ta_IsVirus_Chk3(arg2, x, y) != 1) &&
                        SzDuel_GetMapUnitID(x, y) < 0) {
                        TaLogic005_GetNearDefensePoint((s32)arg2, x, y, (s32 *)info);
                        distance = info[4];
                        if (distance < best_distance && distance >= 0) {
                            best_position = arg3;
                            best_distance = distance;
                        }
                    }
                }
                i++;
            } while (i < 8);
            if (best_distance < 14) {
                return best_position;
            }
            {
                s32 fallback_y;
                s32 fallback_x;
                s32 fallback_i = 0;
                s32 fallback_position;
                do {
                    if ((fallback_position = TaLogic_GetSommonPiecePreference_00124F50(arg0, fallback_i)) >= 0) {
                        fallback_x = fallback_position & 255;
                        fallback_y = fallback_position >> 8;
                        if (SzDuel_GetField(fallback_x, fallback_y) != 8 &&
                            (SzDuel_GetField(fallback_x, fallback_y) != 9 ||
                             Ta_IsVirus_Chk3(arg2, fallback_x, fallback_y) != 1) &&
                            SzDuel_GetMapUnitID(fallback_x, fallback_y) < 0 &&
                            SzDuel_GetField(fallback_x, fallback_y) == 4) {
                            return fallback_position;
                        }
                    }
                    fallback_i++;
                } while (fallback_i < 8);
            }
        }
    } else {
        s32 y;
        s32 x;
        s32 i;
        s32 best_position;

        best_position = -1;
        i = 0;
        do {
            if ((arg3 = TaLogic_GetSommonPiecePreference_00124F50(arg0, i)) >= 0) {
                x = arg3 & 255;
                y = arg3 >> 8;
                if (SzDuel_GetField(x, y) != 8 &&
                    (SzDuel_GetField(x, y) != 9 || Ta_IsVirus_Chk3(arg2, x, y) != 1) &&
                    SzDuel_GetMapUnitID(x, y) < 0 && y < 8) {
                    best_position = arg3;
                }
            }
            i++;
        } while (i < 8);
        if (best_position >= 0) {
            return best_position;
        }
    }
    return -1;
}

typedef struct Nibbles_00123500 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_00123500;

typedef struct Result_00123500 {
    s32 packed;
    u8 best;
} Result_00123500;

void TaLogic005_GetNearDefensePoint(s32 arg0, s32 arg1, s32 arg2, void *arg3) {
    extern s32 TaLogic_GetRoot2();
    Result_00123500 *result = arg3;
    Nibbles_00123500 buffer[12];
    s32 j;
    s32 value;
    s32 hi;
    s32 lo;
    s32 score;
    s32 i;

    result->packed = -1;
    result->best = 0xFF;
    for (j = 0; j < 12; j++) {
        buffer[j].low = buffer[j].high = 0xF;
    }
    i = 0;
    do {
        if (TaLogic005_IsEmptyDefensePoint(i) == 1) {
            value = TaLogic005_GetDefensePoint(i);
            lo = value & 0xFF;
            hi = value >> 8;
            score = SzDuel_GetMapUnitID(lo, hi);
            if (score < 0) {
                score = 0xFFFF;
            }
            score = TaLogic_GetRoot2(arg0, buffer, arg1, arg2, lo, hi, (u16)score, 7);
            if (score < result->best && score >= 0) {
                result->best = score;
                result->packed = value;
                return;
            }
        }
        i++;
    } while (i < 3);
}

s32 TaLogic005_GetDefensePoint(s32 arg0) {
    switch (arg0) {                                 /* irregular */
    case 0:
        return 0x303;
    case 1:
        return 0x304;
    default:
    case 2:
        return 0x302;
    }
}

s32 TaLogic005_IsEmptyDefensePoint(s32 arg0) {
    s32 var_v0;

    switch (arg0) {
        case 0:
            var_v0 = 0x303;
            break;
        case 1:
            var_v0 = 0x304;
            break;
        case 2:
        default:
            var_v0 = 0x302;
            break;
    }
    if ((var_v0 >= 0) && (SzDuel_GetMapUnit(var_v0 & 0xFF, var_v0 >> 8) == 0)) {
        return 1;
    }
    return 0;
}

s32 TaLogic_IsHandPlay_00123740(s32 player, void *output) {
    s32 cards[8];
    u8 scratch[32];
    s32 count;
    u8 state0;
    u8 state1;
    s32 *card;
    s32 *card2;
    s32 index;
    s32 slot;
    u8 count2;
    s32 slot2;
    u8 count3;
    s32 slot3;
    u8 count4;
    s32 slot4;
    s32 *finalCard;
    s32 finalIndex;
    s32 result;
    extern s32 TaLogic_GetUnitNum();
    extern s32 SzDuel_GetUnitCardNo();

    state0 = (u8)TaLogic_GetUnitNum(player, 0);
    state1 = (u8)TaLogic_GetUnitNum(player, 1);
    count = 0;
    if (output == NULL) {
        return -1;
    }
    TaHand_GetNextHand(player, cards);
    if (state0 == 5) {
        if (TaLogic005_GetSpellPlay(player, scratch, output, 999) >= 0) {
            return 1;
        }
        return -1;
    }
    if (state1 == 5) {
        if (count < TaHand_GetNextHandNum(player)) {
            card = cards;
            do {
                if ((TaHand_GetCardKind(*card) >> 5) == 0 &&
                    TaHand_IsCardSummon2(player, *card) == 1) {
                    SzDuel_InitCardInfo(output, cards[count]);
                    return 0;
                }
                card++;
                count++;
            } while (count < TaHand_GetNextHandNum(player));
        }
        return -1;
    }
    if (Ta_GetUnitNumFrom22bitFlagList((u8)TaLogic005_Is2Head_ThunderDragon(player, cards)) == 3) {
        if (TaLogic_SetSpecialComboQue_00124C90(player, scratch, output, 1) >= 0) {
            return 3;
        }
    }
    if (TaLogic005_GetSpecialSpellPlay(player, scratch, output) >= 0) {
        return 2;
    }
    if (state0 == 0) {
        index = 0;
        if (index < TaHand_GetNextHandNum(player)) {
            card2 = cards;
            do {
                if ((TaHand_GetCardKind(*card2) >> 5) == 0 &&
                    TaHand_IsCardSummon2(player, *card2) == 1 &&
                    TaLogic005_IsKeepHandCombo(player, cards, (u16)*card2) == 0) {
                    return 0;
                }
                card2++;
                index++;
            } while (index < TaHand_GetNextHandNum(player));
        }
    }
    slot = 6;
    do {
        if (SzDuel_GetUnitStatus(player, slot, 4) != 0) {
            if (player == Ta_IsUnitControl(player, slot)) {
                count = (u8)(count + 1);
            }
        }
        if (SzDuel_GetUnitStatus((player == 0) ? 1 : 0, slot, 4) != 0 &&
            player == Ta_IsUnitControl((player == 0) ? 1 : 0, slot)) {
            count = (u8)(count + 1);
        }
        slot++;
    } while (slot < 11);
    if ((u8)count > 0) {
        if (TaLogic005_GetSpecialCardPlay(player, scratch, output, 0x235) >= 0) {
            return 2;
        }
    }
    slot2 = 1;
    count2 = 0;
    while (1) {
        if ((SzDuel_GetUnitKind(player, slot2) & 0x1F) == 0x10) {
            if (player == Ta_IsUnitControl(player, slot2)) {
                count2++;
            }
        }
        if ((SzDuel_GetUnitKind((player == 0) ? 1 : 0, slot2) & 0x1F) == 0x10 &&
            player == Ta_IsUnitControl((player == 0) ? 1 : 0, slot2)) {
            count2++;
        }
        slot2++;
        if (slot2 > 5) {
            break;
        }
    }
    if (count2 >= 3) {
        if (TaLogic005_GetSpecialCardPlay(player, scratch, output, 0x251) >= 0) {
            return 2;
        }
    }
    slot3 = 1;
    count3 = 0;
    while (1) {
        if (SzDuel_GetUnitCardNo(player, slot3) == 0x258) {
            if (player == Ta_IsUnitControl(player, slot3)) {
                count3++;
            }
        }
        if (SzDuel_GetUnitCardNo((player == 0) ? 1 : 0, slot3) == 0x258 &&
            player == Ta_IsUnitControl((player == 0) ? 1 : 0, slot3)) {
            count3++;
        }
        slot3++;
        if (slot3 > 5) {
            break;
        }
    }
    if (count3 >= 2) {
        if (TaLogic005_GetSpecialCardPlay(player, scratch, output, 0x230) >= 0) {
            return 2;
        }
    }
    slot4 = 1;
    count4 = 0;
    while (1) {
        if (SzDuel_GetUnitCardNo(player, slot4) == 0x230) {
            if (player == Ta_IsUnitControl(player, slot4)) {
                count4++;
            }
        }
        if (SzDuel_GetUnitCardNo((player == 0) ? 1 : 0, slot4) == 0x230 &&
            player == Ta_IsUnitControl((player == 0) ? 1 : 0, slot4)) {
            count4++;
        }
        slot4++;
        if (slot4 > 5) {
            break;
        }
    }
    if (count4 >= 2) {
        if (TaLogic005_GetSpecialCardPlay(player, scratch, output, 0x258) >= 0) {
            return 2;
        }
    }
    if (TaLogic_IsAttackedNow(player, 0, 0) == 1) {
        if (TaLogic005_GetSpecialCardPlay(player, scratch, output, 0x54) >= 0) {
            return 2;
        }
    }
    finalIndex = 0;
    if (finalIndex < TaHand_GetNextHandNum(player)) {
        finalCard = cards;
        do {
            if ((TaHand_GetCardKind(*finalCard) >> 5) == 0 &&
                TaHand_IsCardSummon2(player, *finalCard) == 1) {
                SzDuel_InitCardInfo(output, cards[finalIndex]);
                return 0;
            }
            finalCard++;
            finalIndex++;
        } while (finalIndex < TaHand_GetNextHandNum(player));
    }
    result = TaLogic005_GetSpellPlay(player, scratch, output, 999);
    if (result >= 0) {
        return result;
    }
    return -1;
}

s32 TaLogic005_Is2Head_ThunderDragon(s32 arg0, s32 *arg1) {
    s32 i;
    s32 result;
    s32 *entry;

    result = 0;
    i = 0;
    if (0 < TaHand_GetNextHandNum(arg0)) {
        do {
            entry = &arg1[i];
            if ((TaHand_IsCardSummon2(arg0, *entry) == 1) && ((TaHand_GetCardKind(*entry) >> 5) == 0)) {
                result = (result + (1 << (4 - i))) & 0xFF;
                i = TaHand_GetNextHandNum(arg0);
            }
            i++;
        } while (i < TaHand_GetNextHandNum(arg0));
    }
    {
        s32 resultCheck;
        resultCheck = result & 0xFF;
        if (resultCheck == 0) {
            return 0;
        }
    }
    i = 0;
    if (0 < TaHand_GetNextHandNum(arg0)) {
        do {
            entry = &arg1[i];
            if ((TaHand_IsCardSummon2(arg0, *entry) == 1) && ((TaHand_GetCardKind(*entry) >> 5) == 0x12)) {
                result = (result + (1 << (4 - i))) & 0xFF;
                i = TaHand_GetNextHandNum(arg0);
            }
            i++;
        } while (i < TaHand_GetNextHandNum(arg0));
    }
    {
        s32 resultCheck;
        resultCheck = result & 0xFF;
        if (resultCheck == 2) {
            i = 0;
            if (0 < TaHand_GetNextHandNum(arg0)) {
                do {
                    entry = &arg1[i];
                    if ((TaHand_IsCardSummon2(arg0, *entry) == 1) && ((TaHand_GetCardKind(*entry) >> 5) == 0xF)) {
                        result = (result + (1 << (4 - i))) & 0xFF;
                        i = TaHand_GetNextHandNum(arg0);
                    }
                    i++;
                } while (i < TaHand_GetNextHandNum(arg0));
            }
            return result & 0xFF;
        }
    }
    return 0;
}

s32 TaLogic005_IsKeepHandCombo(s32 arg0, s32 *arg1, s32 arg2) {
    s32 temp_s0;

    temp_s0 = TaHand_GetCardKind(arg2 & 0xFFFF) >> 5;
    if (Ta_GetUnitNumFrom22bitFlagList(TaLogic005_Is2Head_ThunderDragon(arg0, arg1) & 0xFF) == 3) {
        return 0;
    }
    switch (temp_s0) {
    case 18:
    case 15:
        return 1;
    case 0:
        return 1;
    }
    return 0;
}

s32 TaLogic005_GetSpecialSpellPlay(s32 arg0, void *arg1, void *arg2) {
    s32 cards[8];
    s32 i;
    s32 count;
    extern s32 SzDuel_GetUnitCurseRest();
    extern s32 SzDuel_GetUnitCardNo();

    count = 0;
    TaHand_GetNextHand(arg0, cards);
    for (i = 0; i < TaHand_GetNextHandNum(arg0); i++) {
        if (cards[i] == 0x33D) {
            *((s8 *)arg1 + 6) = i;
            SzDuel_InitCardInfo(arg2, cards[i]);
            return TaHand_GetCardKind(cards[i]) >> 5;
        }
    }

    if (TaLogic005_IsDoCerem(arg0, 0x34C) == 1) {
        for (i = 0; i < TaHand_GetNextHandNum(arg0); i++) {
            if (cards[i] == 0x34C) {
                *((s8 *)arg1 + 6) = i;
                SzDuel_InitCardInfo(arg2, cards[i]);
                return TaHand_GetCardKind(cards[i]) >> 5;
            }
        }
    }

    for (i = 0; i < TaHand_GetNextHandNum(arg0); i++) {
        if (cards[i] == 0x332) {
            *((s8 *)arg1 + 6) = i;
            SzDuel_InitCardInfo(arg2, cards[i]);
            return TaHand_GetCardKind(cards[i]) >> 5;
        }
    }

    i = 0;
    while (1) {
        if (arg0 == Ta_IsUnitControl(arg0, i)) {
            if (SzDuel_GetUnitAttr(arg0, i) == 4) {
                count++;
            }
        }
        if (arg0 == Ta_IsUnitControl(arg0 == 0 ? 1 : 0, i)) {
            if (SzDuel_GetUnitAttr(arg0 == 0 ? 1 : 0, i) == 4) {
                count++;
            }
        }
        i++;
        if (i > 5) {
            break;
        }
    }

    if (count >= 3) {
        for (count = 0; count < TaHand_GetNextHandNum(arg0); count++) {
            if (cards[count] == 0x2E6) {
                *((s8 *)arg1 + 6) = count;
                SzDuel_InitCardInfo(arg2, cards[count]);
                return TaHand_GetCardKind(cards[count]) >> 5;
            }
        }
    }

    {
        s32 facedown;
        s32 slot;

        facedown = 0;
        slot = 0;
        do {
            if (arg0 == Ta_IsUnitControl(arg0, slot)) {
                if (SzDuel_GetUnitCurseRest(arg0, slot) == 0xFF) {
                    facedown++;
                }
            }
            if (arg0 == Ta_IsUnitControl(arg0 == 0 ? 1 : 0, slot)) {
                if (SzDuel_GetUnitCurseRest(arg0 == 0 ? 1 : 0, slot) == 0xFF) {
                    facedown++;
                }
            }
            slot++;
        } while (slot < 11);

        if (facedown > 0) {
            for (count = 0; count < TaHand_GetNextHandNum(arg0); count++) {
                if (cards[count] == 0x31C) {
                    *((s8 *)arg1 + 6) = count;
                    SzDuel_InitCardInfo(arg2, cards[count]);
                    return TaHand_GetCardKind(cards[count]) >> 5;
                }
            }
        }
    }

    {
        s32 special;
        s32 slot;

        slot = 6;
        special = 0;
        do {
            if (arg0 == Ta_IsUnitControl(arg0, slot)) {
                if (SzDuel_GetUnitCardNo(arg0, slot) == 0x33D) {
                    special++;
                }
            }
            if (arg0 == Ta_IsUnitControl(arg0 == 0 ? 1 : 0, slot)) {
                if (SzDuel_GetUnitCardNo(arg0 == 0 ? 1 : 0, slot) == 0x33D) {
                    special++;
                }
            }
            slot++;
        } while (slot < 11);

        if (special > 0) {
            for (count = 0; count < TaHand_GetNextHandNum(arg0); count++) {
                if (cards[count] == 0x334) {
                    *((s8 *)arg1 + 6) = count;
                    SzDuel_InitCardInfo(arg2, cards[count]);
                    return TaHand_GetCardKind(cards[count]) >> 5;
                }
            }
        }
    }
    return -1;
}

s32 TaLogic005_GetSpecialCardPlay(s32 arg0, void *arg1, void *arg2, s32 arg3) {
    s32 entries[8];
    s32 i;

    TaHand_GetNextHand(arg0, entries);
    for (i = 0; i < TaHand_GetNextHandNum(arg0); i++) {
        if (((arg3 & 0xFFFF) == entries[i]) && (TaHand_IsCardSummon2(arg0, entries[i]) == 1)) {
            ((s8 *)arg1)[6] = i;
            SzDuel_InitCardInfo(arg2, entries[i]);
            return TaHand_GetCardKind(entries[i]) >> 5;
        }
    }
    return -1;
}

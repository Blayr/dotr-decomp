#include "common.h"

typedef struct Input_00265890 {
    s32 unk0;
    u32 position;
    u32 target;
    s32 mode;
} Input_00265890;

typedef struct State_00265890 {
    u16 value;
    u16 count;
    u16 phase;
    u8 effects[26];
    s32 entries[44];
    s32 frame;
    u8 effectCount;
    u8 padD5[0x2D];
    u16 timer;
} State_00265890;

typedef struct Request_00265890 {
    s32 command;
    s32 unk4;
    s32 argument;
    s32 flag;
} Request_00265890;



/* The absolute value of `value`. */
static inline s32 absolute_00265890(s32 value) {
    return value >= 0 ? value : -value;
}

#pragma opt_strength_reduction off

/* Effect script 046, step `ID`: its camera, fades and effect module; it destroys units, changes life points, uses
   the graveyard, turns cards face up, changes summon power. */
s32 Ta_Eff_046(void *eInfo, void *Temp, s32 ID) {
    extern void SzDuel_SetUnitStatus(u32, s32, s32, s32);
    extern void Ta_DelUnit(s32, s32);
    extern void TaUtil_DoOpen(u32, s32, s32);
    extern void TaView_RestoreOriginalView(void *, s32);
    Input_00265890 *input = eInfo;
    State_00265890 *state = Temp;
    s32 packet[4];
    Request_00265890 *request = (Request_00265890 *)packet;
    s32 found;
    extern s32 SzDuel_GetUnitOpenRate();

    packet[0] = 999;
    packet[1] = 0;
    packet[2] = 0;
    packet[3] = 0;
    found = 0;
    SzDuel_SetWindowDraw(0);
    if (ID >= 0) {
        InitEffectTemp(state);
        state->value = 0x80;
        TaUtil_DoOpen(input->position >> 8, input->position & 0xFF, 1);
        TaView_ReqFocusCamera(0, input->position, 100, 180);
        TaEffect_LoadModule(state, 0x25A);
        TaEffect_LoadModule(state, 0x25B);
        TaEffect_LoadModule(state, 0x222);
        return 1;
    }

    switch (state->phase) {
    case 0:
        if (state->value > 0x30) {
            state->value -= 15;
        } else {
            state->value = 0x30;
            if (SzDuel_GetUnitOpenRate(input->position >> 8, input->position & 0xFF) == 0xFF &&
                TaEffect_IsLoadModule(state) == 1) {
                if (input->mode == 1) {
                    SzDuel_OpenMsgPopup(0, -120, 80, 0x104);
                } else {
                    SzDuel_OpenMsgPopup(0, -120, 80, 0x103);
                }
                request->command = 0x25A;
                request->unk4 = 0;
                request->argument = input->position;
                request->flag = 0;
                state->effects[0] = Ta_Do_Effect(request, state);
                state->phase++;
            }
        }
        if (state->value < 0x30) {
            state->value = 0x30;
        }
        SzEffect_SetBlackOutForDuel((u8)state->value);
        break;
    case 1:
        {
            __int128 owner;
            s32 inner;
            s32 entry;
            s32 y;
            s32 x;
            s32 outer;
            s32 centerHigh;
            s32 distance;
            s32 center;
            extern __int128 Ta_IsUnitControl();

            if (SzEffect_IsUse(state->effects[0]) != 0) {
                return 1;
            }
            SzDuel_SetUnitStatus(input->position >> 8, input->position & 0xFF, 0, 1);
            TaView_ReqFocusCamera(0x10, input->position, 500, 500);
            state->value = 0;
            center = SzDuel_GetUnitLoc(input->position >> 8, input->position & 0xFF);
            request->command = 0x222;
            request->unk4 = 0;
            request->argument = center;
            request->flag = 1;
            state->effects[0] = Ta_Do_Effect(request, state);
            state->entries[0] = input->position;
            outer = -1;
            x = (center & 0xFF) - 1;
            centerHigh = center >> 8;
            state->value++;
            state->effectCount++;
            while (1) {
                inner = -1;
                y = centerHigh - 1;
                while (1) {
                    if (x >= 0 && x < 7 && y >= 0 && y < 7) {
                        distance = outer + inner;
                        distance = absolute_00265890(distance);
                        if (distance < 3 && (outer != 0 || inner != 0)) {
                            request->command = 0x222;
                            request->unk4 = 0;
                            request->argument = (y << 8) | x;
                            request->flag = 0;
                            state->effects[state->effectCount] = Ta_Do_Effect(request, state);
                            if (SzDuel_GetMapUnit(x, y) != 0) {
                                entry = SzDuel_GetMapUnitID(x, y);
                                if (input->mode == 1) {
                                    state->entries[state->effectCount] = entry;
                                    state->value++;
                                } else {
                                    s32 low;
                                    s32 high;

                                    high = entry >> 8;
                                    low = entry & 0xFF;
                                    owner = Ta_IsUnitControl(high, low);
                                    if (owner != Ta_IsUnitControl(input->position >> 8, input->position & 0xFF)) {
                                        if (Ta_IsLDRangeAvility(high, low, 11) == 0 && Ta_IsResistAll(high, low) != 1) {
                                            state->entries[state->effectCount] = entry;
                                            state->value++;
                                            if (input->mode == 0 && entry == input->target) {
                                                found++;
                                            }
                                        }
                                    } else {
                                        state->entries[state->effectCount] = entry;
                                        state->value++;
                                        if (input->mode == 0 && entry == input->target) {
                                            found++;
                                        }
                                    }
                                }
                            } else {
                                state->entries[state->effectCount] = -1;
                            }
                            state->effectCount++;
                        }
                    }
                    inner++;
                    y++;
                    if (inner > 1) {
                        break;
                    }
                }
                outer++;
                x++;
                if (outer > 1) {
                    break;
                }
            }
            if (found == 0 && input->mode == 0) {
                request->command = 0x25B;
                request->unk4 = 0;
                request->argument = input->target;
                request->flag = 1;
                state->effects[state->effectCount] = Ta_Do_Effect(request, state);
                state->entries[state->effectCount] = -1;
                state->effectCount++;
            }
            state->phase++;
            return 1;
        }
    case 2:
        {
            s32 *entry;
            s32 i;
            u8 *effect;

            state->frame++;
            i = 0;
            entry = (s32 *)state;
            for (; i < state->effectCount; entry++, i++) {
                switch (state->frame) {
                case 1:
                    SzSound_PlaySE(1, 0x31);
                    break;
                case 5:
                    SzSound_PlaySE(1, 0x31);
                    SzSound_PlaySE(1, 0x31);
                    SzSound_PlaySE(1, 0x31);
                    SzSound_PlaySE(1, 0x31);
                    break;
                }
                effect = &state->effects[i];
                if (SzEffect_IsUse(*effect) != 0 && SzEffect_GetStatus(*effect) == 2 && entry[8] >= 0) {
                    if ((entry[8] & 0xFF) > 0) {
                        Ta_UnitFade(entry[8] >> 8, entry[8] & 0xFF, -1, 1, 3);
                        state->entries[state->effectCount + state->count] = entry[8];
                        entry[8] = -1;
                    }
                    state->count++;
                }
            }
            if (state->value <= state->count) {
                state->phase++;
            }
            break;
        }
    case 3:
        if (Ta_IsFinishFade() != 0) {
            s32 i;
            s32 *entry;

            i = state->effectCount;
            entry = (s32 *)state + i;
            for (; i < state->effectCount + state->count; entry++, i++) {
                if (entry[8] >= 0 && (entry[8] & 0xFF) > 0) {
                    Ta_DelUnit(entry[8] >> 8, entry[8] & 0xFF);
                }
            }
            if (input->target != 0) {
                Ta_DelUnit(input->target >> 8, input->target & 0xFF);
            }
            state->value = 0x30;
            state->phase++;
        }
        break;
    case 4:
        state->value += 15;
        if (state->value > 0x80) {
            state->value = 0x80;
        }
        SzEffect_SetBlackOutForDuel((u8)state->value);
        if (state->value == 0x80) {
            state->phase++;
            SzDuel_CloseMsgPopup();
            TaView_RestoreOriginalView(state, 0x10);
            state->timer = 0;
        }
        break;
    default:
        if (state->timer++ > 16 && Ta_IsFinishEffect(state) == 1 && Ta_IsFinishFade() == 1) {
            if (SzDuel_GetWindowDisp() != 0) {
                SzDuel_SetWindowDraw(1);
            }
            SzDuel_CloseMsgPopup();
            return 0;
        }
        break;
    }
    return 1;
}

#pragma opt_strength_reduction reset

typedef struct Stats_002660E0 {
    u8 pad[8];
    u16 attack;
    u16 defense;
} Stats_002660E0;

typedef struct Flags_002660E0 {
    s8 unused : 3;
    s8 side : 1;
    s8 remaining : 4;
} Flags_002660E0;

typedef struct Card_002660E0 {
    Stats_002660E0 *stats;
    u8 pad04[0x34];
    s16 attack;
    s16 defense;
    u16 id;
    u8 pad3E[0x19];
    Flags_002660E0 flags;
} Card_002660E0;

typedef struct Effect_002660E0 {
    u32 flags;
    u16 amount;
} Effect_002660E0;

/* A card record's attack. */
static inline s32 attack_002660E0(Card_002660E0 *card) {
    s32 value = card->attack + (card->stats->attack & 0x1FFF);
    if (value > 9999) {
        return 9999;
    }
    return value;
}

/* A card record's defence. */
static inline s32 defense_002660E0(Card_002660E0 *card) {
    s32 value = card->defense + (card->stats->defense & 0x1FFF);
    if (value > 9999) {
        return 9999;
    }
    return value;
}

/* The attack (`fAP` set) or defence change a unit (record `vInfo`) gets on square (nX, nZ) from effects and
   leaders. */
s32 Ta_GetParamOfs(s32 vInfo, s32 nX, s32 nZ, s32 fAP) {
    s32 i;
    s32 side;
    s32 total;
    Effect_002660E0 *effect;
    u32 flags;
    u32 otherFlags;
    Effect_002660E0 *otherEffect;
    s32 j;
    s32 result;

    if (vInfo == 0) {
        return 0;
    }
    total = 0;
    side = Ta_IsUnitControl2((void *)vInfo);
    i = 1;
    if (((Card_002660E0 *)vInfo)->id == 0x2A3) {
        if (fAP == 0) {
            total -= defense_002660E0((Card_002660E0 *)vInfo);
        } else {
            total -= attack_002660E0((Card_002660E0 *)vInfo);
        }
        if (((Card_002660E0 *)vInfo)->flags.side) {
            if (fAP == 0) {
                total += SzDuel_GetUnitDP(side, 0, 1);
            } else {
                total += SzDuel_GetUnitAP(side, 0, 1);
            }
        } else {
            if (fAP == 0) {
                total += SzDuel_GetUnitDP(side == 0 ? 1 : 0, 0, 1);
            } else {
                total += SzDuel_GetUnitAP(side == 0 ? 1 : 0, 0, 1);
            }
        }
        i = 1;
    }
    while (1) {
        if (SzDuel_GetUnit(side, i) != 0 &&
            SzDuel_GetUnitStatus(side, i, 4) != 0 &&
            SzDuel_GetUnitStatus(side, i, 3) != 0 &&
            SzDuel_GetUnitStatus(side, i, 5) != 0) {
            if ((effect = Ta_GetUnitEffect(side, i, 2)) != NULL) {
                flags = effect->flags;
                if (Ta_GetUnitAgreeWithVarInfo((void *)vInfo, Ta_IsUnitControl(side, i),
                                 (flags >> 6) & 3, flags & 0x3F) != 0) {
                    switch (effect->flags >> 8) {
                    case 19:
                        total -= effect->amount;
                        break;
                    case 18:
                        total += effect->amount;
                        break;
                    case 34:
                        if (fAP == 0) {
                            total += effect->amount;
                        }
                        break;
                    }
                }
            }
        }
        i++;
        if (i > 5) {
            break;
        }
    }
    j = 1;
    while (1) {
        if (SzDuel_GetUnit(side == 0 ? 1 : 0, j) != 0 &&
            SzDuel_GetUnitStatus(side == 0 ? 1 : 0, j, 4) != 0 &&
            SzDuel_GetUnitStatus(side == 0 ? 1 : 0, j, 3) != 0 &&
            SzDuel_GetUnitStatus(side == 0 ? 1 : 0, j, 5) != 0) {
            if ((otherEffect = Ta_GetUnitEffect(side == 0 ? 1 : 0, j, 2)) != NULL) {
                otherFlags = otherEffect->flags;
                if (Ta_GetUnitAgreeWithVarInfo((void *)vInfo,
                                 Ta_IsUnitControl(side == 0 ? 1 : 0, j),
                                 (otherFlags >> 6) & 3, otherFlags & 0x3F) != 0) {
                    switch (otherEffect->flags >> 8) {
                    case 19:
                        total -= otherEffect->amount;
                        break;
                    case 18:
                        total += otherEffect->amount;
                        break;
                    case 34:
                        if (fAP == 0) {
                            total += otherEffect->amount;
                        }
                        break;
                    }
                }
            }
        }
        j++;
        if (j > 5) {
            break;
        }
    }
    result = CheckLandAgreement(SzDuel_GetField(nX, nZ), (void *)vInfo);
    switch (result) {
    case 1:
        total += 500;
        break;
    case 2:
        total -= 500;
        break;
    }
    total += Ta_GetLDParamOfs2((void *)vInfo, nX, nZ);
    return total;
}

/* The standing (natural) effect unit (nSide, nID) runs at the start of its turn (counters, graveyard, range), into
   `output`. */
s32 Ta_ManageNaturalEffectInStandbyPhase(s32 nSide, s32 nID, void *output) {
    extern s32 SzDuel_GetUnitDelayCount();
    extern s32 SzDuel_GetGraveCount();
    s32 count;
    void *data;
    s32 target;
    s32 value;
    s32 index0;
    s32 length0;
    s32 length1;
    s32 index1;
    u32 packed;
    u32 word;
    s32 *out = output;

    if ((data = Ta_GetUnitEffect(nSide, nID, 2)) == NULL) {
        return 0;
    }
    word = *(u32 *)data;
    switch (word >> 8) {
    case 0xD:
        out[0] = 8;
        out[1] = 0;
        out[2] = Ta_GetCurrentSide(nSide, nID);
        packed = *(u32 *)((u8 *)data + 4);
        out[3] = ((packed >> 16) << 16) | (packed & 0xFFFF);
        return 1;
    case 0x4D:
        value = SearchUnitByRange(0, 0, Ta_GetCurrentSide(nSide, nID),
                             (word >> 6) & 3, word & 0x3F, 0xE);
        if (value == 0) {
            return 0;
        }
        out[0] = 0x39;
        out[1] = 0;
        out[2] = value;
        out[3] = *(u16 *)((u8 *)data + 4);
        return 1;
    case 0x4E:
        value = SearchUnitByRange(0, 0, Ta_GetCurrentSide(nSide, nID),
                             (word >> 6) & 3, word & 0x3F, 0xE);
        if (value == 0) {
            return 0;
        }
        out[0] = 0x1D;
        out[1] = 1;
        out[2] = value;
        out[3] = *(u16 *)((u8 *)data + 4);
        return 1;
    case 0xC:
        if (SzDuel_GetUnitDelayCount(nSide, nID) == 1) {
            SzDuel_SetUnitDelayCount(nSide, nID, 0);
            value = ConvUnitIDtoFlagList(0, nSide, nID);
            out[0] = 0x3C;
            out[1] = 0;
            out[2] = value;
            out[3] = *(u16 *)((u8 *)data + 4);
            return 1;
        }
        return 0;
    case 0x46:
        if (SzDuel_GetUnitDelayCount(nSide, nID) == 1) {
            SzDuel_SetUnitDelayCount(nSide, nID, 0);
            out[0] = 0x2E;
            out[1] = (nSide << 8) | nID;
            out[2] = 0;
            out[3] = 1;
            return 1;
        }
        return 0;
    case 0x53:
        target = ConvUnitIDtoFlagList(0, nSide, nID);
        count = 0;
        length0 = SzDuel_GetGraveCount(0);
        for (index0 = 0; index0 < length0; index0++) {
            if ((TaHand_GetCardKind(SzDuel_InqGrave(0, index0)) >> 5) == 0) {
                SzDuel_DelGrave(0, index0);
                count++;
            }
        }
        SzDuel_PackGrave(0);
        length1 = SzDuel_GetGraveCount(1);
        for (index1 = 0; index1 < length1; index1++) {
            if ((TaHand_GetCardKind(SzDuel_InqGrave(1, index1)) >> 5) == 0) {
                SzDuel_DelGrave(1, index1);
                count++;
            }
        }
        SzDuel_PackGrave(1);
        out[0] = 0x1D;
        out[1] = 1;
        out[2] = target;
        out[3] = count * *(u16 *)((u8 *)data + 4);
        return 1;
    case 0x54:
        value = ConvUnitIDtoFlagList_OFF(SearchUnitByRange(0, 0, Ta_GetCurrentSide(nSide, nID),
                                         (word >> 6) & 3, word & 0x3F, 0xE),
                             nSide, nID);
        if (value == 0) {
            return 0;
        }
        out[0] = 0x48;
        out[1] = SzDuel_GetUnitLoc(nSide, nID);
        out[2] = value;
        out[3] = Ta_GetCurrentSide(nSide, nID);
        return 1;
    }
    return 0;
}

/* The standing effect a spell-bound unit (nSide, nID) runs at the start of its turn, into `eInfo`. */
s32 Ta_ManageNaturalEffectInStandbyPhase2(s32 nSide, s32 nID, void *eInfo) {
    extern s32 SzDuel_GetUnitSpellRest();
    s32 i;
    u32 temp_s3;
    u32 convUnitIDtoFlagList;
    void *unitEffect;
    s32 unitFlags;
    s32 unitNumFrom22bitFlagList;
    s32 unitId;
    s32 unitIdLo;
    s32 unitIdHi;

    unitEffect = Ta_GetUnitEffect(nSide, nID, 2);
    temp_s3 = *(u32 *)unitEffect;
    convUnitIDtoFlagList = 0;
    switch (temp_s3 >> 8) {
    case 0x17:
        unitFlags = SearchUnitByRange(0, 0, Ta_GetCurrentSide(nSide, nID), (temp_s3 >> 6) & 3, temp_s3 & 0x3F, 0xE);
        if (unitFlags == 0) {
            return 0;
        }
        unitNumFrom22bitFlagList = Ta_GetUnitNumFrom22bitFlagList(unitFlags);
        i = 0;
        if (0 < unitNumFrom22bitFlagList) {
            do {
                unitId = Ta_GetUnitOwnerIDFromLstCount(unitFlags, i);
                unitIdHi = unitId >> 8;
                unitIdLo = unitId & 0xFF;
                if (SzDuel_GetUnitSpellRest(unitIdHi, unitIdLo) == 0) {
                    convUnitIDtoFlagList = ConvUnitIDtoFlagList(convUnitIDtoFlagList, unitIdHi, unitIdLo);
                }
                i += 1;
            } while (i < unitNumFrom22bitFlagList);
        }
        if (Ta_GetUnitNumFrom22bitFlagList((s32) convUnitIDtoFlagList) == 0) {
            return 0;
        }
        ((s32 *)eInfo)[0] = 0;
        ((s32 *)eInfo)[1] = 1;
        ((u32 *)eInfo)[2] = convUnitIDtoFlagList;
        ((s32 *)eInfo)[3] = *(u16 *)((u8 *)unitEffect + 4);
        return 1;
    }
    return 0;
}

/* Whether unit (nSide, nID) is held by a lasting curse from another unit's range. */
s32 TaPerm_IsPermCurseActive(s32 nSide, s32 nID) {
    s32 i;
    s32 key;
    u32 *p;
    u32 v;

    key = (nSide << 8) | nID;
    for (i = 0; i < 11; i++) {
        if (SzDuel_GetUnit(0, i)) {
            if ((p = Ta_GetUnitEffect(0, i, 2)) != NULL && SzDuel_GetUnitStatus(0, i, 4) && SzDuel_GetUnitStatus(0, i, 3) && SzDuel_GetUnitStatus(0, i, 5)) {
                v = *p;
                if ((v >> 8) == 0x17 && Ta_GetAgreeOwnerIDon22bitFlagLst(key, SearchUnitByRange(0, 0, Ta_GetCurrentSide(0, i), (v >> 6) & 3, v & 0x3F, 0xE))) {
                    return 1;
                }
            }
        }
        if (SzDuel_GetUnit(1, i)) {
            if ((p = Ta_GetUnitEffect(1, i, 2)) != NULL && SzDuel_GetUnitStatus(1, i, 4) && SzDuel_GetUnitStatus(1, i, 3) && SzDuel_GetUnitStatus(1, i, 5)) {
                v = *p;
                if ((v >> 8) == 0x17 && Ta_GetAgreeOwnerIDon22bitFlagLst(key, SearchUnitByRange(0, 0, Ta_GetCurrentSide(1, i), (v >> 6) & 3, v & 0x3F, 0xE))) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

/* The `No`-th face-up unit whose standing effect is `sKey`, or none. */
s32 Ta_SearchUncTypeNaturalEffectUser(s32 sKey, s32 No) {
    s32 count;
    s32 index;
    u32 *data;

    index = 1;
    count = 0;
    do {
        if (SzDuel_GetUnitStatus(0, index, 4) != 0 &&
            SzDuel_GetUnitStatus(0, index, 3) != 0 &&
            SzDuel_GetUnitStatus(0, index, 5) != 0) {
            data = Ta_GetUnitEffect(0, index, 2);
            if (data != NULL && (*data >> 8) == sKey) {
                if (count++ == No) {
                    return index;
                }
            }
        }
        index++;
    } while (index < 11);

    index = 1;
    do {
        if (SzDuel_GetUnitStatus(1, index, 4) != 0 &&
            SzDuel_GetUnitStatus(1, index, 3) != 0 &&
            SzDuel_GetUnitStatus(1, index, 5) != 0) {
            data = Ta_GetUnitEffect(1, index, 2);
            if (data != NULL && (*data >> 8) == sKey) {
                if (count++ == No) {
                    return index | 0x100;
                }
            }
        }
        index++;
    } while (index < 11);
    return -1;
}

/* How many face-up units have standing effect `sKey`. */
s32 Ta_SearchUncTypeNaturalEffectUserNum(s32 sKey) {
    s32 i;
    s32 var_s0;
    u32 *temp_v0;
    u32 *temp_v0_2;

    i = 1;
    var_s0 = 0;
    do {
        if ((SzDuel_GetUnit(0, i) != 0) && ((temp_v0 = Ta_GetUnitEffect(0, i, 2)) != NULL) && (SzDuel_GetUnitStatus(0, i, 4) != 0) && (SzDuel_GetUnitStatus(0, i, 3) != 0) && (SzDuel_GetUnitStatus(0, i, 5) != 0) && (((u32) *temp_v0 >> 8) == sKey)) {
            var_s0 += 1;
        }
        i += 1;
    } while (i < 0xB);
    i = 1;
    do {
        if ((SzDuel_GetUnit(1, i) != 0) && ((temp_v0_2 = Ta_GetUnitEffect(1, i, 2)) != NULL) && (SzDuel_GetUnitStatus(1, i, 4) != 0) && (SzDuel_GetUnitStatus(1, i, 3) != 0) && (SzDuel_GetUnitStatus(1, i, 5) != 0) && (((u32) *temp_v0_2 >> 8) == sKey)) {
            var_s0 += 1;
        }
        i += 1;
    } while (i < 0xB);
    return var_s0;
}

/* How many face-up units of side `nSide` have standing effect `sKey`. */
s32 Ta_SearchUncTypeNaturalEffectUserNumWithSide(s32 sKey, s32 nSide) {
    s32 var_s0;
    s32 i;
    u32 *unitEffect;
    u32 *unitEffect2;

    i = 1;
    var_s0 = 0;
    do {
        if ((SzDuel_GetUnitStatus(0, i, 4) != 0) && (SzDuel_GetUnitStatus(0, i, 3) != 0) && (SzDuel_GetUnitStatus(0, i, 5) != 0) && (nSide == Ta_GetCurrentSide(0, i))) {
            unitEffect = Ta_GetUnitEffect(0, i, 2);
            if ((unitEffect != NULL) && (((u32) *unitEffect >> 8) == sKey)) {
                var_s0 += 1;
            }
        }
        i += 1;
    } while (i < 0xB);
    i = 1;
    do {
        if ((SzDuel_GetUnitStatus(1, i, 4) != 0) && (SzDuel_GetUnitStatus(1, i, 3) != 0) && (SzDuel_GetUnitStatus(1, i, 5) != 0) && (nSide == Ta_GetCurrentSide(1, i))) {
            unitEffect2 = Ta_GetUnitEffect(1, i, 2);
            if ((unitEffect2 != NULL) && (((u32) *unitEffect2 >> 8) == sKey)) {
                var_s0 += 1;
            }
        }
        i += 1;
    } while (i < 0xB);
    return var_s0;
}

typedef struct Effect_002670F0 {
    u32 flags;
    union {
        u32 word;
        struct {
            u16 amount;
            u16 operation;
        } parts;
    } data;
} Effect_002670F0;

/* The life-point change standing effects give in mode `sMode` (effect `bEfc`), kept in range. */
s32 Ta_GetLPRevByNaturalEffect(s32 sMode, s32 bEfc) {
    s32 i;
    s32 j;
    s32 var_s1;
    u32 temp_a0;
    u32 temp_a0_2;
    u32 flags;
    u32 temp_a1_2;
    u32 flags2;
    u32 temp_a1_4;
    u32 temp_v0_2;
    u32 temp_v0_4;
    Effect_002670F0 *unitEffect;
    Effect_002670F0 *unitEffect2;

    var_s1 = bEfc;
    if (bEfc == 0) {
        return 0;
    }
    i = 0;
    do {
        if ((SzDuel_GetUnitStatus(0, i, 4) != 0) && (SzDuel_GetUnitStatus(0, i, 3) != 0) && (SzDuel_GetUnitStatus(0, i, 5) != 0)) {
            unitEffect = Ta_GetUnitEffect(0, i, 2);
            if (unitEffect != NULL) {
                flags = unitEffect->flags;
                if (((flags >> 8) == 0x3B) && ((flags & 0x3F) == sMode)) {
                    temp_a1_2 = unitEffect->data.word;
                    temp_a0 = temp_a1_2 >> 0x10;
                    switch (temp_a0) {
                    case 0:
                        var_s1 += unitEffect->data.parts.amount;
                        break;
                    case 1:
                        var_s1 -= unitEffect->data.parts.amount;
                        break;
                    case 2:
                        var_s1 += var_s1 * (unitEffect->data.parts.amount - 1);
                        break;
                    case 3:
                        temp_v0_2 = temp_a1_2 & 0xFFFF;
                        if (temp_v0_2 != 0) {
                            var_s1 -= (u32) var_s1 / temp_v0_2;
                        }
                        break;
                    }
                }
            }
        }
        i += 1;
    } while (i < 0xB);
    j = 1;
    do {
        if ((SzDuel_GetUnitStatus(1, j, 4) != 0) && (SzDuel_GetUnitStatus(1, j, 3) != 0) && (SzDuel_GetUnitStatus(1, j, 5) != 0)) {
            unitEffect2 = Ta_GetUnitEffect(1, j, 2);
            if (unitEffect2 != NULL) {
                flags2 = unitEffect2->flags;
                if (((flags2 >> 8) == 0x3B) && ((flags2 & 0x3F) == sMode)) {
                    temp_a1_4 = unitEffect2->data.word;
                    temp_a0_2 = temp_a1_4 >> 0x10;
                    switch (temp_a0_2) {
                    case 0:
                        var_s1 += unitEffect2->data.parts.amount;
                        break;
                    case 1:
                        var_s1 -= unitEffect2->data.parts.amount;
                        break;
                    case 2:
                        var_s1 += var_s1 * (unitEffect2->data.parts.amount - 1);
                        break;
                    case 3:
                        temp_v0_4 = temp_a1_4 & 0xFFFF;
                        if (temp_v0_4 != 0) {
                            var_s1 -= (u32) var_s1 / temp_v0_4;
                        }
                        break;
                    }
                }
            }
        }
        j += 1;
    } while (j < 0xB);
    return GetParCap(var_s1);
}

typedef struct {
    u8 pad00[0x3E];
    u8 value3E;
    u8 pad3F[5];
    u8 side;
    u8 active;
    u8 pad46[0x11];
    s8 flag0 : 1;
    s8 swapped : 1;
    s8 linked : 1;
} Obj_00267380;

/* Whether a unit (record `vInfo`) is hidden from side `nSide` (a standing effect hides it). */
s32 Ta_IsUnitHide(s32 vInfo, s32 nSide) {
    s32 i;
    s32 count;
    Obj_00267380 *obj = (Obj_00267380 *)vInfo;
    s32 x;
    s32 y;
    s32 pos;
    u32 *card;

    if (obj == NULL) {
        return 0;
    }
    if (nSide == ((obj->swapped == 0) ? obj->side : ((obj->side == 0) ? 1 : 0))) {
        return 0;
    }
    if (obj->active == 0) {
        return 0;
    }
    if (obj->linked == 0) {
        return 1;
    }
    if ((count = Ta_SearchUncTypeNaturalEffectUserNum(0x44)) > 0) {
        for (i = 0; i < count; i++) {
            pos = Ta_SearchUncTypeNaturalEffectUser(0x44, i);
            y = pos >> 8;
            x = pos & 0xFF;
            if (SzDuel_GetUnitStatus(y, x, 4) && SzDuel_GetUnitStatus(y, x, 3) && SzDuel_GetUnitStatus(y, x, 5) &&
                Ta_IsUnitControl(y, x) == Ta_IsUnitControl2(obj) &&
                (card = Ta_GetUnitEffect(y, x, 2)) != NULL) {
                switch (*card & 0x3F) {
                case 29:
                    return ((obj->value3E >> 5) == 0) ? 1 : 0;
                case 30:
                    return ((obj->value3E >> 5) != 0) ? 1 : 0;
                }
            }
        }
    }
    return 0;
}

typedef struct {
    u8 pad00[0x3E];
    u8 value3E;
    u8 pad3F[5];
    u8 side;
    u8 active;
    u8 pad46[0x11];
    s8 flag0 : 1;
    s8 swapped : 1;
} Obj_00267560;

/* Whether a unit (record `vInfo`) is hidden from the turn owner. */
s32 Ta_IsUnitHide2(s32 vInfo) {
    Obj_00267560 *obj = (Obj_00267560 *)vInfo;
    s32 player;
    s32 i;
    s32 count;
    s32 x;
    s32 y;
    s32 pos;
    u32 *card;

    if (obj == NULL) {
        return 0;
    }
    player = SzDuel_GetTurnOwner();
    if (player == ((obj->swapped == 0) ? obj->side : ((obj->side == 0) ? 1 : 0))) {
        return 0;
    }
    if (obj->active == 0) {
        return 0;
    }
    if ((count = Ta_SearchUncTypeNaturalEffectUserNum(0x44)) > 0) {
        for (i = 0; i < count; i++) {
            pos = Ta_SearchUncTypeNaturalEffectUser(0x44, i);
            y = pos >> 8;
            x = pos & 0xFF;
            if (SzDuel_GetUnitStatus(y, x, 4) && SzDuel_GetUnitStatus(y, x, 3) && SzDuel_GetUnitStatus(y, x, 5) &&
                (card = Ta_GetUnitEffect(y, x, 2)) != NULL) {
                switch (*card & 0x3F) {
                case 29:
                    return ((obj->value3E >> 5) == 0) ? 1 : 0;
                case 30:
                    return ((obj->value3E >> 5) != 0) ? 1 : 0;
                }
            }
        }
    }
    return 0;
}

/* Whether unit (nSide, nID) is protected from every effect. */
s32 Ta_IsResistAll(s32 nSide, s32 nID) {
    s32 index;
    s32 count;
    s32 column;
    s32 row;
    s32 value;
    s32 *data;

    if (nID == 0) {
        return 0;
    }
    if ((count = Ta_SearchUncTypeNaturalEffectUserNum(0xB)) > 0) {
            for (index = 0; index < count; index++) {
            value = Ta_SearchUncTypeNaturalEffectUser(0xB, index);
            row = value >> 8;
            column = value & 0xFF;
            if ((SzDuel_GetUnitStatus(row, column, 4) != 0) &&
                (SzDuel_GetUnitStatus(row, column, 3) != 0) &&
                (SzDuel_GetUnitStatus(row, column, 5) != 0)) {
                data = Ta_GetUnitEffect(row, column, 2);
                if (data != NULL) {
                    switch (*data & 0x3F) {
                    case 0:
                        if (!(SzDuel_GetUnitKind(nSide, nID) & 0x1F)) {
                            if ((SzDuel_GetUnitKind(nSide, nID) >> 5) == 0) {
                                return 1;
                            }
                        }
                        return 0;
                    }
                }
            }
            }
    }
    return 0;
}

/* Whether unit (nSide, nID) is protected from every effect by its master (leader) rule. */
s32 Ta_IsResistAllMaster(s32 nSide, s32 nID) {
    s32 i;
    s32 count;
    s32 entry;
    s32 low;
    s32 high;
    s32 *info;

    if (nID == 0) {
        return 0;
    }
    if ((count = Ta_SearchUncTypeNaturalEffectUserNum(0xB)) > 0) {
        for (i = 0; i < count; i++) {
            entry = Ta_SearchUncTypeNaturalEffectUser(0xB, i);
            high = entry >> 8;
            low = entry & 0xFF;
            if ((SzDuel_GetUnitStatus(high, low, 4) != 0) &&
                (SzDuel_GetUnitStatus(high, low, 3) != 0) &&
                (SzDuel_GetUnitStatus(high, low, 5) != 0)) {
                info = Ta_GetUnitEffect(high, low, 2);
                if (info != NULL) {
                    switch (*info & 0x3F) {
                    case 0:
                        if (!(SzDuel_GetUnitKind(nSide, nID) & 0x1F) &&
                            ((SzDuel_GetUnitKind(nSide, nID) >> 5) == 0)) {
                            return entry;
                        }
                        break;
                    }
                }
            }
        }
    }
    return 0;
}

/* Whether unit (nSide, nID) visibly has the attribute advantage over unit (cSide, cID) (hidden cards excluded). */
s32 Ta_IsVisualAttrAdv(s32 nSide, s32 nID, s32 cSide, s32 cID) {
    s32 state;
    s32 first;

    state = SzDuel_GetTurnOwner();
    if ((state == Ta_GetCurrentSide(cSide, cID)) ||
        ((SzDuel_GetUnitKind(nSide, nID) >> 5) != 0) ||
        ((SzDuel_GetUnitKind(cSide, cID) >> 5) != 0) ||
        (nID == 0) || (cID == 0)) {
        return -1;
    }
    if (Ta_IsUnitHide2(SzDuel_GetUnit(cSide, cID)) != 0) {
        return -1;
    }
    if (SzDuel_GetUnitStatus(cSide, cID, 4) != 0) {
        first = SzDuel_GetUnitAttr(nSide, nID);
        return ChkAttrAdv(first, SzDuel_GetUnitAttr(cSide, cID)) + 1;
    }
    if (Ta_SearchUncTypeNaturalEffectUserNum(0x3D) > 0) {
        first = SzDuel_GetUnitAttr(nSide, nID);
        return ChkAttrAdv(first, SzDuel_GetUnitAttr(cSide, cID)) + 1;
    }
    return -1;
}

/* The summon-power change side `nSide` gets from standing effects. */
s32 Ta_GetSummonCalcRevision(s32 nSide) {
    s32 i;
    s32 searchUncTypeNaturalEffectUserNum;
    s32 var_s2;
    s32 searchUncTypeNaturalEffectUserLo;
    s32 searchUncTypeNaturalEffectUserHi;
    s32 searchUncTypeNaturalEffectUser;
    s32 temp_v1;
    u32 *unitEffect;
    u32 temp_a0;

    searchUncTypeNaturalEffectUserNum = Ta_SearchUncTypeNaturalEffectUserNum(0x56);
    var_s2 = 0;
    for (i = 0; i < searchUncTypeNaturalEffectUserNum; i++) {
            searchUncTypeNaturalEffectUser = Ta_SearchUncTypeNaturalEffectUser(0x56, i);
            searchUncTypeNaturalEffectUserHi = searchUncTypeNaturalEffectUser >> 8;
            searchUncTypeNaturalEffectUserLo = searchUncTypeNaturalEffectUser & 0xFF;
            unitEffect = Ta_GetUnitEffect(searchUncTypeNaturalEffectUserHi, searchUncTypeNaturalEffectUserLo, 2);
            if (unitEffect != NULL) {
                temp_a0 = *unitEffect;
                if ((temp_a0 >> 8) == 0x56) {
                    temp_v1 = (temp_a0 >> 6) & 3;
                    if (temp_v1 == 2) {
                        if (nSide != Ta_GetCurrentSide(searchUncTypeNaturalEffectUserHi, searchUncTypeNaturalEffectUserLo)) {
                            var_s2 -= 1;
                        }
                    } else if (temp_v1 == 3) {
                        var_s2 += 1;
                    }
                }
            }
    }
    if (var_s2 > 0) {
        var_s2 = 1;
    } else if (var_s2 < 0) {
        var_s2 = -1;
    }
    return var_s2;
}

extern int func_001DE550_b(void);
extern int func_001DE560_b(void);
extern void *func_001DF540_b(int a, int b);
extern int func_001E1640_b(int a, int b);
extern int func_001E1580_b(int a, int b);
struct jp_65da1;
extern int func_001DE690_b(int index);
extern unsigned *func_00250740_b(int a, int b, int n);
extern int func_001E1700_b(int a, int b);
extern int func_001E16A0_b(int a, int b, int value);
extern int func_001DE740_b(int index);
extern void func_001DE760_b(int index, int value);
struct jp_6826f {
    int eNO;
    unsigned int dwFrom;
    unsigned int dwTo;
    unsigned int dwPar;
};
struct jp_6835c {
    unsigned int dwID;
    unsigned int dwParam;
};

/* Runs the start of a turn (standby phase): turn count, standing effects, curses and spells, into `eInfo_v`. */
int Ta_Do_StandbyPhase(int PrNo, void *eInfo_v)
{
    struct jp_6826f * eInfo = eInfo_v;
    int i;
    int Ret;
    int cRest;
    int Unit;
    int fTwice;
    int U_EXZ[4];
    int TurnOwner;
    int eID;
    struct jp_6835c *temp;

    TurnOwner = SzDuel_GetTurnOwner();
    cRest = func_001DE690_b(TurnOwner);
    Unit = -1;
    if (PrNo == 0) {
        fTwice = Ta_SearchUncTypeNaturalEffectUserNum(85);
        if (fTwice > 0 || TurnOwner == func_001DE550_b()) {
            SzDuel_SetTurnCount(func_001DE560_b() + 1);
        }
        for (i = 1; i < 11; i++) {
            temp = (struct jp_6835c *)func_00250740_b(0, i, 2);
            if (temp == 0 || temp->dwID >> 8 != 81) {
                SzDuel_SetUnitStatus(0, i, 1, 0);
            }
            temp = (struct jp_6835c *)func_00250740_b(1, i, 2);
            if (temp == 0 || temp->dwID >> 8 != 81) {
                SzDuel_SetUnitStatus(1, i, 1, 0);
            }
        }
        for (PrNo = 1; PrNo <= 5; PrNo++) {
            if ((cRest = func_001E1700_b(TurnOwner, PrNo)) > 0 && SzDuel_GetUnitStatus(TurnOwner, PrNo, 4) && SzDuel_GetUnitStatus(TurnOwner, PrNo, 5)) {
                if (fTwice > 0) {
                    func_001E16A0_b(TurnOwner, PrNo, GetCap(1, cRest - 2));
                } else {
                    func_001E16A0_b(TurnOwner, PrNo, GetCap(1, cRest - 1));
                }
            }
        }
        return 0x200000;
    }
    if (PrNo < 64) {
        if (PrNo - 32 < 6) {
            if (func_001DF540_b(TurnOwner, PrNo - 32) && PrNo - 32 != 0) {
                if (SzDuel_GetUnitStatus(TurnOwner, PrNo - 32, 4) && SzDuel_GetUnitStatus(TurnOwner, PrNo - 32, 5) && SzDuel_GetUnitStatus(TurnOwner, PrNo - 32, 1) == 0 && func_00250740_b(TurnOwner, PrNo - 32, 2)) {
                    Unit = TurnOwner << 8 | (PrNo - 32);
                }
                if (Unit >= 0) {
                    Ret = Ta_ManageNaturalEffectInStandbyPhase(Unit >> 8, Unit & 0xff, (struct jp_65da1 *)eInfo);
                    return (PrNo + 1) << 16 | Ret;
                }
            }
        }
        if (PrNo - 32 < 11) {
            if (func_001DF540_b((TurnOwner == 0 ? 1 : 0), PrNo - 37) && PrNo - 37 != 0) {
                if (SzDuel_GetUnitStatus((TurnOwner == 0 ? 1 : 0), PrNo - 37, 4) && SzDuel_GetUnitStatus((TurnOwner == 0 ? 1 : 0), PrNo - 37, 5) && SzDuel_GetUnitStatus((TurnOwner == 0 ? 1 : 0), PrNo - 37, 1) == 0 && func_00250740_b((TurnOwner == 0 ? 1 : 0), PrNo - 37, 2)) {
                    Unit = (TurnOwner == 0 ? 1 : 0) << 8 | (PrNo - 37);
                }
                if (Unit >= 0) {
                    Ret = Ta_ManageNaturalEffectInStandbyPhase2(Unit >> 8, Unit & 0xff, eInfo);
                    return (PrNo + 1) << 16 | Ret;
                }
            }
        }
        if (func_001DF540_b(TurnOwner, PrNo - 42) && PrNo - 42 != 0) {
            if (SzDuel_GetUnitStatus(TurnOwner, PrNo - 42, 4) && SzDuel_GetUnitStatus(TurnOwner, PrNo - 42, 5) && SzDuel_GetUnitStatus(TurnOwner, PrNo - 42, 1) && func_00250740_b(TurnOwner, PrNo - 42, 2)) {
                Unit = TurnOwner << 8 | (PrNo - 42);
            }
            if (Unit >= 0) {
                Ret = Ta_ManageNaturalEffectInStandbyPhase(Unit >> 8, Unit & 0xff, (struct jp_65da1 *)eInfo);
                return (PrNo + 1) << 16 | Ret;
            }
        }
        if (PrNo - 32 < 16) {
            PrNo++;
        } else {
            PrNo = 64;
        }
        return PrNo << 16;
    }
    if (PrNo < 96) {
        for (PrNo = 0; PrNo < 11; PrNo++) {
            if (TurnOwner == Ta_GetCurrentSide(0, PrNo)) {
                SzDuel_SetUnitStatus(0, PrNo, 0, 0);
            } else {
                SzDuel_SetUnitStatus(0, PrNo, 0, 1);
            }
            if (TurnOwner == Ta_GetCurrentSide(1, PrNo)) {
                SzDuel_SetUnitStatus(1, PrNo, 0, 0);
            } else {
                SzDuel_SetUnitStatus(1, PrNo, 0, 1);
            }
        }
        for (PrNo = 1; PrNo < 11; PrNo++) {
            if (func_001E1580_b(TurnOwner, PrNo) > 0 || func_001E1640_b(TurnOwner, PrNo) > 0 || (SzDuel_Kind2Type(SzDuel_GetUnitKind(TurnOwner, PrNo) >> 5) == 2 && SzDuel_GetUnitStatus(TurnOwner, PrNo, 4))) {
                SzDuel_SetUnitStatus(TurnOwner, PrNo, 0, 1);
            }
        }
        for (PrNo = 1; PrNo < 11; PrNo++) {
            if (func_001E1580_b((TurnOwner == 0 ? 1 : 0), PrNo) > 0 || func_001E1640_b((TurnOwner == 0 ? 1 : 0), PrNo) > 0 || (SzDuel_Kind2Type(SzDuel_GetUnitKind((TurnOwner == 0 ? 1 : 0), PrNo) >> 5) == 2 && SzDuel_GetUnitStatus((TurnOwner == 0 ? 1 : 0), PrNo, 4))) {
                SzDuel_SetUnitStatus((TurnOwner == 0 ? 1 : 0), PrNo, 0, 1);
            }
        }
        PrNo = 128;
    }
    if (PrNo < 160 && Ta_IsExzodia(TurnOwner) == 4) {
        if (PrNo == 128) {
            if ((eID = Ta_IsActiveTrapB((TurnOwner == 0 ? 1 : 0), 17)) >= 0) {
                if ((Ret = Ta_IsActiveTrapB((TurnOwner == 0 ? 1 : 0), 46)) >= 0) {
                    eInfo->eNO = 102;
                    eInfo->dwFrom = 1;
                    eInfo->dwTo = Ret;
                    eInfo->dwPar = 0;
                    return (PrNo + 1) << 16 | 1;
                }
                eInfo->eNO = 102;
                eInfo->dwFrom = 1;
                eInfo->dwTo = eID;
                eInfo->dwPar = 0;
                return 0xa00001;
            }
        }
        for (PrNo = 0; PrNo < 4; PrNo++) {
            U_EXZ[PrNo] = Ta_GetExzodiaPartsUnit(TurnOwner, PrNo);
        }
        eInfo->eNO = 109;
        eInfo->dwFrom = TurnOwner;
        eInfo->dwTo = (U_EXZ[0] & 0xff) << 9 | ((U_EXZ[1] & 0xff) << 6 | ((U_EXZ[2] & 0xff) << 3 | (U_EXZ[3] & 0xff)));
        eInfo->dwPar = 0;
        return TaTuto_IsTuto(SzDuel_GetTurnOwner()) == 0 ? 0xff0005 : 0xff0001;
    }
    if (func_001DE560_b() > 1) {
        if (Ta_SearchUncTypeNaturalEffectUserNum(86) > 0) {
            SzDuel_CalcSummonPower(TurnOwner, 0, cRest + Ta_GetSummonCalcRevision(TurnOwner));
        } else {
            SzDuel_CalcSummonPower(TurnOwner, 0, cRest);
        }
    }
    func_001DE740_b(TurnOwner);
    if ((func_001DE740_b(TurnOwner) & 0x80) == 0) {
        if ((Ret = Ta_IsDestinyDraw(TurnOwner)) > 0) {
            func_001DE760_b(TurnOwner, Ret & 0xff);
        }
    }
    SzDuel_SetHandPhase(TurnOwner, 1);
    return 0xff0000;
}

/* From the dotr-decomp CC0 bundle (commit 88c32bb2), chatC/imp/conv.py. */

struct DotrStateItem;
extern int func_001E1030_b(int a, int b);
extern struct DotrStateItem *func_001E36E0_b(int x, int y);
extern int func_001E1580_b(int a, int b);
extern int func_001E1640_b(int a, int b);

/* Whether side `side` has all five Exodia parts on the board (an instant win). */
int Ta_IsExzodia(int side)
{
    int flags[4];
    int k;
    int total;
    int i;
    int x;
    int y;
    int t;
    int lo;
    int hi;
    int cell;

    total = 0;
    if (func_001E1030_b(side, 0) == 58) {
    for (k = 0; k < 4; k++) {
        for (i = 0; i < 8; i++) {
            cell = Ta_GetSommonPiecePreference(side, i);
            y = cell & 0xff;
            x = cell >> 8;
            if (func_001E36E0_b(y, x) != 0) {
                cell = SzDuel_GetMapUnitID(y, x);
                if (cell >= 0) {
                    hi = cell >> 8;
                    lo = cell & 0xff;
                    t = func_001E1030_b(hi, lo);
                    if (t == Ta_GetExzodiaPartsCardNo(k) && SzDuel_GetUnitStatus(hi, lo, 4) != 0 && SzDuel_GetUnitStatus(hi, lo, 0) == 0 && SzDuel_GetUnitStatus(hi, lo, 1) == 0 && func_001E1580_b(hi, lo) == 0 && func_001E1640_b(hi, lo) == 0 && hi == side) {
                        flags[k] = 1;
                    }
                }
            }
        }
        total += flags[k];
    }
    return total;
    }
    return 0;
}

/* Side `tOwner`'s unit holding Exodia part `Order`, or none. */
s32 Ta_GetExzodiaPartsUnit(s32 tOwner, s32 Order) {
    extern s32 SzDuel_GetUnitCardNo();
    s32 type;
    s32 i;
    s32 v;
    s32 min;
    s32 best;
    s32 pos;
    s32 dist;

    best = -1;
    min = 0xFF;
    for (i = 0; i < 8; i++) {
        pos = Ta_GetSommonPiecePreference(tOwner, i);
        if ((v = SzDuel_GetMapUnitID(pos & 0xFF, pos >> 8)) >= 0) {
            type = SzDuel_GetUnitCardNo(v >> 8, v & 0xFF);
            if (type == Ta_GetExzodiaPartsCardNo(Order)) {
                dist = SzDuel_GetUnitSummonOrder(v >> 8, v & 0xFF);
                if (dist < min) {
                    min = dist;
                    best = v;
                }
            }
        }
    }
    return best;
}

/* The card number of Exodia part `Order`. */
s32 Ta_GetExzodiaPartsCardNo(s32 Order) {
    s32 result;

    switch (Order) {
    case 0:
        result = 0x38;
        break;
    case 1:
        result = 0x39;
        break;
    case 2:
        result = 0x36;
        break;
    case 3:
        result = 0x37;
        break;
    default:
        result = 0;
        break;
    }

    return result;
}

typedef struct Command_00268760 {
    s32 unused;
    s32 kind;
    u32 flags;
    u16 value;
    u16 unusedE;
} Command_00268760;

typedef struct State_00268760 {
    u16 value;
    u16 unused2;
    u16 stage;
    u8 ids[0xCE];
    u8 count;
    u8 padding[0x2D];
    u16 timer;
} State_00268760;


/* Effect script 057, step `ID`: its camera, fades and effect module; it changes attack or defence. */
s32 Ta_Eff_057(void *eInfo, void *Temp, s32 ID) {
    s32 stackData[4];
    s32 count;
    s32 *data = stackData;
    s32 i;
    Command_00268760 *command = eInfo;
    State_00268760 *state = Temp;

    data[0] = 999;
    data[1] = 0;
    data[2] = 0;
    data[3] = 0;
    count = 0;
    SzDuel_SetWindowDraw(0);
    if (ID >= 0) {
        InitEffectTemp(Temp);
        state->value = 0x80;
        if (Ta_GetUnitNumFrom22bitFlagList(command->flags) == 1) {
            TaView_ReqFocusCamera(0x10, Ta_GetUnitOwnerIDFromLstCount(command->flags, 0), 100, 180);
        } else {
            TaView_ReqStdCompleteView(0x10);
        }
        Ta_AllUnitFade(eInfo, Temp, ID, -1, 1, 1);
        TaEffect_LoadModule(Temp, 0x22D);
        return 1;
    }

    switch (state->stage) {
    case 0:
        if (state->value > 0x30) {
            state->value -= 15;
        } else {
            state->value = 0x30;
            if (TaEffect_IsLoadModule(Temp) == 1) {
                SzDuel_OpenMsgPopup(0, -120, 80, 0x107);
                Ta_SetEffectDependOnFlagLst(eInfo, Temp, data, 0x22D);
                state->stage++;
            }
        }
        if (state->value < 0x30) {
            state->value = 0x30;
        }
        SzEffect_SetBlackOutForDuel((u8)state->value);
        break;

    case 1:
        for (i = 0; i < state->count; i++) {
            if (SzEffect_IsUse(state->ids[i]) == 0) {
                count++;
            }
        }
        if (count < state->count) {
            return 1;
        }
        SzDuel_CloseMsgPopup();
        count = 0;
        do {
            if ((command->flags >> (21 - count)) & 1) {
                if (count < 11) {
                    TaUtil_CalcUnitDP(0, count, 1, command->value);
                    TaUtil_CalcUnitAP(0, count, 1, command->value);
                } else {
                    TaUtil_CalcUnitDP(1, count - 11, 1, command->value);
                    TaUtil_CalcUnitAP(1, count - 11, 1, command->value);
                }
            }
            count++;
        } while (count < 22);
        Ta_AllUnitFade(eInfo, Temp, ID, 1, 0, 1);
        TaView_RestoreOriginalView(Temp, 0x10);
        state->stage++;
        break;

    default:
        state->value += 15;
        if (state->value > 0x80) {
            state->value = 0x80;
        }
        SzEffect_SetBlackOutForDuel((u8)state->value);
        if (state->value == 0x80 && state->timer++ > 16 && Ta_IsFinishFade() == 1) {
            if (SzDuel_GetWindowDisp() != 0) {
                SzDuel_SetWindowDraw(1);
            }
            SzDuel_CloseMsgPopup();
            return 0;
        }
        break;
    }
    return 1;
}

struct jp_6989c {
    int eNO;
    unsigned int dwFrom;
    unsigned int dwTo;
    unsigned int dwPar;
};
struct jp_68cb4 {
    int fLoad : 1;
    unsigned char bModNum : 5;
    unsigned short wModule[24];
    unsigned char bModCond[24];
};
struct jp_69942 {
    unsigned short wCount_1;
    unsigned short wCount_2;
    unsigned short wLvl;
    unsigned char eID[24];
    int ePos[24];
    struct jp_68cb4 eMod;
    unsigned int fObj;
    unsigned int fObj2;
    unsigned char oNum;
    unsigned char unknown_d5[0xb];
    int camDat[8];
    unsigned char bCamLvl;
    unsigned short wCamTime;
    unsigned char unknown_104[0xc];
    int nTasakiEfc[0x10c];
};
extern int func_00255AC0_b(struct jp_69942 *q, int id);
extern void func_00260740_b(unsigned char who);
extern void func_00260A70_b(struct jp_69942 *Temp, unsigned char b);
extern struct jp_6a917 *func_001DF580_b(int a, int b, int c, int d, int e);
struct jp_6b127 {
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
};
struct jp_6a917 {
    unsigned char unknown_00[0x3E];
    unsigned char bVarKind;
    unsigned char unknown_3F[5];
    unsigned char bOwner;
    unsigned char bID;
    unsigned char unknown_46[0x10];
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
};
extern int func_001DEE50_b(int index);
extern struct jp_6b127 *func_001DD0E0_b(int id);

/* Effect script 058, step `ID`: its camera, fades and effect module; it changes life points, uses the graveyard. */
int Ta_Eff_058(void *eInfo_v, void *Temp_v, int ID)
{
    struct jp_6989c * eInfo = eInfo_v;
    struct jp_69942 * Temp = Temp_v;
    struct jp_6a917 *pVarInfo;
    struct jp_6b127 *pInfo;
    struct jp_6989c eCall;
    struct jp_6989c *pCall = &eCall;
    int j;
    int cNum;
    int LOC;
    int MaxAP;
    int MaxNo;
    int MaxSide;
    int MaxEntry;
    int cNO;
    eCall.eNO = 999;
    eCall.dwFrom = 0;
    eCall.dwTo = 0;
    eCall.dwPar = 0;
    j = 0;
    SzDuel_SetWindowDraw(0);
    if (ID >= 0) {
        InitEffectTemp(Temp);
        func_00260740_b(16);
        func_00255AC0_b(Temp, 508);
        func_00255AC0_b(Temp, 501);
        return 1;
    }
    switch (Temp->wLvl) {
    case 0:
        if (TaEffect_IsLoadModule(Temp) == 1) {
            pCall->eNO = 508;
            pCall->dwFrom = 0;
            pCall->dwTo = 1;
            pCall->dwPar = eInfo->dwFrom;
            Temp->eID[0] = Ta_Do_Effect(pCall, Temp);
            Temp->ePos[0] = 0xFFFF;
            Temp->wLvl++;
        }
        break;
    case 1:
        if (SzEffect_IsUse(Temp->eID[0])) {
            return 1;
        }
        SzDuel_CalcLP(eInfo->dwTo, 1, eInfo->dwFrom);
        Temp->wLvl++;
        break;
    case 2:
        for (; (unsigned)j < eInfo->dwPar; j++) {
            LOC = Ta_GetSummonablePieceWithOrder(eInfo->dwTo, j, 1);
            pCall->eNO = 501;
            pCall->dwFrom = 0;
            pCall->dwTo = LOC;
            pCall->dwPar = 0;
            Temp->eID[j] = Ta_Do_Effect(pCall, Temp);
            if (LOC < 0) {
                Temp->ePos[j] = 0xFFFF;
            } else {
                Temp->ePos[j] = LOC;
            }
            Temp->oNum++;
        }
        Temp->wLvl++;
        break;
    case 3:
        

        for (LOC = 0; LOC < Temp->oNum; LOC++) {
            if (SzEffect_IsUse(Temp->eID[LOC])) {
                if (SzEffect_GetStatus(Temp->eID[LOC]) == 2) {
                    if ((unsigned short)Temp->ePos[LOC] != 0xFFFF) {
                        MaxNo = 999;
                        MaxEntry = -1;
                        MaxAP = 0;
                        cNum = func_001DEE50_b(eInfo->dwTo);
                        for (j = 0; j < cNum; j++) {
                            cNO = SzDuel_InqGrave(eInfo->dwTo, j);
                            if (cNO != 999) {
                                pInfo = func_001DD0E0_b(cNO);
                                if (MaxAP <= pInfo->wAP && (pInfo->bKind >> 5) == 0) {
                                    MaxSide = eInfo->dwTo;
                                    MaxNo = cNO;
                                    MaxAP = pInfo->wAP;
                                    MaxEntry = j;
                                }
                            }
                        }
                        j = func_001DEE50_b(eInfo->dwTo == 0 ? 1 : 0);
                        for (cNum = 0; cNum < j; cNum++) {
                            cNO = SzDuel_InqGrave(eInfo->dwTo == 0 ? 1 : 0, cNum);
                            if (cNO != 999) {
                                pInfo = func_001DD0E0_b(cNO);
                                if (pInfo->wAP > MaxAP && (pInfo->bKind >> 5) == 0) {
                                    MaxSide = eInfo->dwTo == 0 ? 1 : 0;
                                    MaxNo = cNO;
                                    MaxAP = pInfo->wAP;
                                    MaxEntry = cNum;
                                }
                            }
                        }
                        if (MaxEntry >= 0) {
                            pVarInfo = func_001DF580_b(eInfo->dwTo, Temp->ePos[LOC] & 0xFF, Temp->ePos[LOC] >> 8, MaxNo, 0);
                            if (pVarInfo != 0) {
                                pVarInfo->fFinish = -1;
                            }
                            SzDuel_DelGrave(MaxSide, MaxEntry);
                            SzDuel_PackGrave(MaxSide);
                            Temp->ePos[LOC] = 0xFFFF;
                        }
                    }
                }
            } else {
                j++;
            }
        }
        if (j >= Temp->oNum) {
            if (Temp->wCamTime++ > 30) {
                Temp->wCamTime = 0;
                Temp->wLvl++;
                func_00260A70_b(Temp, 16);
                break;
            }
        }
        return 1;
    default:
        if (Temp->wCamTime++ > 16) {
            if (SzDuel_GetWindowDisp() != 0) {
                SzDuel_SetWindowDraw(1);
            }
            SzDuel_CloseMsgPopup();
            return 0;
        }
        break;
    }
    return 1;
}

typedef struct {
    u8 pad00[4];
    s32 f4;
    u32 f8;
    u32 fC;
} Src_00268FA0;

typedef struct {
    u8 pad00[4];
    u16 state;
    u8 ids[0x1A];
    s32 f20;
    u8 pad24[0xD4 - 0x24];
    u8 nids;
    u8 padD5[0x102 - 0xD5];
    u16 timer;
} Work_00268FA0;

typedef struct {
    s32 w0;
    s32 w4;
    s32 w8;
    s32 wC;
} Req_00268FA0;


/* Effect script 059, step `ID`: its camera, fades and effect module; it changes attack or defence, changes life
   points. */
s32 Ta_Eff_059(void *eInfo, void *Temp, s32 ID) {
    Src_00268FA0 *src = (Src_00268FA0 *)eInfo;
    Work_00268FA0 *w = (Work_00268FA0 *)Temp;
    Req_00268FA0 req;
    s32 count;
    Req_00268FA0 *p;
    s32 i;
    s32 j;

    req.w0 = 0x3E7;
    req.w4 = 0;
    req.w8 = 0;
    req.wC = 0;
    p = &req;
    count = 0;
    SzDuel_SetWindowDraw(0);
    if (ID >= 0) {
        InitEffectTemp(Temp);
        TaView_ReqStdCompleteView(0x10);
        TaEffect_LoadModule(Temp, 0x1FC);
        TaEffect_LoadModule(Temp, 0x211);
        TaView_ReqStdCompleteView(0x10);
        return 1;
    }
    switch (w->state) {
    case 0:
        if (TaEffect_IsLoadModule(Temp) == 1) {
            p->w0 = 0x1FC;
            p->w4 = 0;
            p->w8 = 1;
            p->wC = Ta_GetLPRevByNaturalEffect(0x2C, (u16)src->fC);
            w->ids[0] = Ta_Do_Effect(p, Temp);
            w->f20 = 0xFFFF;
            w->nids++;
            w->state++;
        }
        break;
    case 1:
        if (SzEffect_IsUse(w->ids[0]) == 1) {
            return 1;
        }
        SzDuel_CalcLP(src->f4, 1, Ta_GetLPRevByNaturalEffect(0x2C, (u16)src->fC));
        w->state++;
        break;
    case 2:
        SzDuel_OpenMsgPopup(0, -0x78, 0x50, 0x106);
        Ta_SetEffectDependOnFlagLst(eInfo, Temp, p, 0x211);
        w->state++;
        break;
    case 3:
        for (i = 0; i < w->nids; i++) {
            if (SzEffect_IsUse(w->ids[i]) == 0) {
                count++;
            }
        }
        if (count < w->nids) {
            return 1;
        }
        SzDuel_CloseMsgPopup();
        for (j = 0; j < 0x16; j++) {
            if ((src->f8 >> (0x15 - j)) & 1) {
                if (j < 0xB) {
                    TaUtil_CalcUnitDP(0, j, 0, src->fC >> 16);
                    TaUtil_CalcUnitAP(0, j, 0, src->fC >> 16);
                } else {
                    TaUtil_CalcUnitDP(1, j - 0xB, 0, src->fC >> 16);
                    TaUtil_CalcUnitAP(1, j - 0xB, 0, src->fC >> 16);
                }
            }
        }
        TaView_RestoreOriginalView(Temp, 0x10);
        w->state++;
        break;
    default:
        if (w->timer++ > 0x10) {
            if (SzDuel_GetWindowDisp() != 0) {
                SzDuel_SetWindowDraw(1);
            }
            SzDuel_CloseMsgPopup();
            return 0;
        }
        break;
    }
    return 1;
}

typedef struct {
    u16 alpha;
    u16 id;
    u16 state;
    u8 handle;
    u8 pad07[0x19];
    s32 processed;
    u8 pad24[0xDE];
    u16 timer;
} State_002692D0;

typedef struct {
    u8 pad00[8];
    s32 mask;
    s32 value;
} Context_002692D0;


/* Effect script 060, step `ID`: its camera, fades and effect module; it destroys units, puts a card on the board. */
s32 Ta_Eff_060(void *eInfo, void *Temp, s32 ID) {
    s32 data[4];
    s32 *params = data;
    State_002692D0 *state = (State_002692D0 *)Temp;
    Context_002692D0 *context = (Context_002692D0 *)eInfo;

    params[0] = 999;
    params[1] = 0;
    params[2] = 0;
    params[3] = 0;
    SzDuel_SetWindowDraw(0);
    if (ID >= 0) {
        InitEffectTemp(Temp);
        state->alpha = 0x80;
        state->id = Ta_GetMinimumOrderUnitFromFlagList(context->mask);
        Ta_AllUnitFade(eInfo, Temp, ID, -1, 1, 1);
        TaView_ReqFocusCamera(0x1E, state->id, 0x64, 0xB4);
        TaEffect_LoadModule(Temp, 0x230);
    } else {
        switch (state->state) {
        case 0:
            state->timer++;
            if (state->alpha > 0x30) {
                state->alpha -= 0xF;
            } else {
                state->alpha = 0x30;
                if (TaEffect_IsLoadModule(Temp) == 1 && state->timer >= 0x1E) {
                    params[0] = 0x230;
                    params[1] = 0;
                    params[2] = state->id;
                    params[3] = 0;
                    state->handle = Ta_Do_Effect(params, Temp);
                    state->processed = 0;
                    state->state++;
                }
            }
            if (state->alpha < 0x30) {
                state->alpha = 0x30;
            }
            SzEffect_SetBlackOutForDuel((u8)state->alpha);
            return 1;
        case 1:
            if (SzEffect_IsUse(state->handle) == 1) {
                if (SzEffect_GetStatus(state->handle) == 2 && state->processed == 0) {
                    s32 position;

                    position = SzDuel_GetUnitLoc(state->id >> 8, state->id & 0xFF);
                    Ta_DelUnit(state->id >> 8, state->id & 0xFF);
                    SzDuel_AddUnit(Ta_IsUnitControl(state->id >> 8, state->id & 0xFF),
                                 position & 0xFF, position >> 8, context->value, 0);
                    SzEffect_SetBusyFlag2(state->id, 0);
                    state->processed = 1;
                }
            } else {
                Ta_AllUnitFade(eInfo, Temp, ID, 1, 0, 1);
                TaView_RestoreOriginalView(Temp, 0x10);
                state->timer = 0;
                state->state++;
            }
            break;
        default:
            state->alpha += 0xF;
            if (state->alpha > 0x80) {
                state->alpha = 0x80;
            }
            SzEffect_SetBlackOutForDuel((u8)state->alpha);
            if (state->alpha == 0x80) {
                if (state->timer++ > 0x10 && Ta_IsFinishFade() == 1) {
                    if (SzDuel_GetWindowDisp() != 0) {
                        SzDuel_SetWindowDraw(1);
                    }
                    SzDuel_CloseMsgPopup();
                    return 0;
                }
            }
            break;
        }
    }
    return 1;
}

typedef struct Command_002695D0 {
    s32 id;
    u32 source;
    u32 target;
    s32 value;
} Command_002695D0;

typedef struct State_002695D0 {
    u16 flag;
    u16 position;
    u16 mode;
    u8 handles[0x16];
    union {
        s32 flags[0x19];
        u8 flagBytes[0x64];
        struct {
            s32 pad;
            s32 timers[0x18];
        } delayed;
    } entries;
    u8 pad80[2];
    u16 ids[0x25];
    s32 side;
    u8 padD0[4];
    u8 cursor;
} State_002695D0;


/* Effect script 036, step `ID`: its camera, fades and effect module; it destroys units, turns cards face up. */
s32 Ta_Eff_036(void *eInfo, void *Temp, s32 ID) {
    extern s32 SzDuel_GetUnitCardNo();
    extern s32 SzDuel_GetUnitOpenRate();
    Command_002695D0 storage;
    Command_002695D0 *command = &storage;
    Command_002695D0 *src = eInfo;
    State_002695D0 *state = Temp;

    storage.id = 999;
    storage.source = 0;
    storage.target = 0;
    storage.value = 0;
    if (ID >= 0) {
        s32 source;
        s32 first;
        s32 target;
        s32 second;

        InitEffectTemp(state);
        if (SzDuel_GetUnitStatus(src->target >> 8, src->target & 0xFF, 2)) {
            SzDuel_SetUnitStatus(src->target >> 8, src->target & 0xFF, 4, 1);
        }
        if (SzDuel_GetUnitStatus(src->source >> 8, src->source & 0xFF, 2)) {
            SzDuel_SetUnitStatus(src->source >> 8, src->source & 0xFF, 4, 1);
        }
        if ((SzDuel_GetUnitKind(src->source >> 8, src->source & 0xFF) >> 5) == 0) {
            state->side = 1;
            SzDuel_SetUnitStatus(src->target >> 8, src->target & 0xFF, 2, 1);
        } else {
            state->side = 2;
            SzDuel_SetUnitStatus(src->target >> 8, src->target & 0xFF, 2, 1);
        }
        if (src->value == 999) {
            TaEffect_LoadModule(state, 0x21A);
            state->side = 1;
        } else {
            if (state->side == 1) {
                source = src->source;
            } else {
                source = src->target;
            }
            if (state->side == 1) {
                target = src->target;
            } else {
                target = src->source;
            }
            if ((first = Ta_IsActiveTrapB(src->source >> 8, 0x2B)) < 0 ||
                !TaEnc_IsActReflexEnc(SzDuel_GetUnitCardNo(target >> 8, target & 0xFF) & 0xFFFF) ||
                Ta_IsLDRangeAvilityWithLocation(source >> 8, source & 0xFF,
                    SzDuel_GetUnitLoc(source >> 8, source & 0xFF) & 0xFF,
                    SzDuel_GetUnitLoc(source >> 8, source & 0xFF) >> 8, 0xB) == 1) {
                state->flag = 0;
                Ta_Eff_036_LoadEffect(src, state);
            } else {
                TaEffect_LoadModule(state, 0x25A);
                if ((second = Ta_IsActiveTrapB(src->target >> 8, 0x2E)) >= 0) {
                    TaView_ReqFocusCamera(0, second, 0xB4, 0xB4);
                    SzEffect_SetBusyFlag2(second, 0);
                    TaUtil_DoOpen(second >> 8, second & 0xFF, 1);
                    state->mode = 16;
                    state->flag = 0;
                    state->position = second;
                    return 1;
                }
                TaView_ReqFocusCamera(0, first, 0xB4, 0xB4);
                SzEffect_SetBusyFlag2(first, 0);
                TaUtil_DoOpen(first >> 8, first & 0xFF, 1);
                state->mode = 16;
                state->flag = 1;
                state->position = first;
                return 1;
            }
        }
        return 1;
    }

    switch (state->mode) {
    case 0:
        if (TaEffect_IsLoadModule(state) == 1) {
            if (src->value == 999) {
                command->id = 0x21A;
                command->source = src->source;
                command->target = src->target;
                command->value = 1;
            }
            if (state->flag != 0) {
                SzDuel_OpenMsgPopup(0, 0, -0xA0, SzDuel_GetMsgName(0x330));
            } else {
                s32 target;
                if (state->side == 1) {
                    target = src->target;
                } else {
                    target = src->source;
                }
                if (TaEnc_IsActReflexEnc(SzDuel_GetUnitCardNo(target >> 8, target & 0xFF) & 0xFFFF)) {
                    SzDuel_OpenMsgPopup(0, 0, -0xA0, 0x106);
                }
            }
            command->id = state->ids[state->cursor];
            command->source = src->source;
            command->target = src->target;
            command->value = state->side;
            state->handles[state->cursor] = Ta_Do_Effect(command, state);
            state->entries.delayed.timers[state->cursor] = 0;
            state->cursor++;
            state->mode++;
        }
        break;
    case 1:
        if (SzEffect_IsUse(state->handles[state->cursor - 1])) {
            Ta_Eff_036_ManageSound(src, state);
            if (SzEffect_GetStatus(state->handles[state->cursor - 1]) == 2) {
                if (state->entries.flagBytes[state->cursor * 4] == 0 && src->value != 999) {
                    if ((SzDuel_GetUnitKind(src->source >> 8, src->source & 0xFF) >> 5) == 0) {
                        Enchant(src->source >> 8, src->source & 0xFF, (state->flag << 16) | (src->value & 0x3FFF), 0);
                        Ta_DelUnit(src->target >> 8, src->target & 0xFF);
                        if (!SzDuel_GetUnitStatus(src->source >> 8, src->source & 0xFF, 4)) {
                            SzDuel_SetUnitStatus(src->source >> 8, src->source & 0xFF, 2, 0);
                        }
                    } else {
                        Enchant(src->target >> 8, src->target & 0xFF, (state->flag << 16) | (src->value & 0x3FFF), 0);
                        Ta_DelUnit(src->source >> 8, src->source & 0xFF);
                        if (!SzDuel_GetUnitStatus(src->target >> 8, src->target & 0xFF, 4)) {
                            SzDuel_SetUnitStatus(src->target >> 8, src->target & 0xFF, 2, 0);
                        }
                    }
                    state->entries.flags[state->cursor] = 0xFFFF;
                }
            }
            return 1;
        }
        SzDuel_CloseMsgPopup();
        if (src->value == 999) {
            Ta_DelUnit(src->source >> 8, src->source & 0xFF);
            if (!SzDuel_GetUnitStatus(src->target >> 8, src->target & 0xFF, 4)) {
                SzDuel_SetUnitStatus(src->target >> 8, src->target & 0xFF, 2, 0);
            }
        }
        SzSound_PlaySE(0, 2);
        SzDuel_CloseMsgPopup();
        return 0;
    case 16:
        if (SzDuel_GetUnitOpenRate((s32)state->position >> 8, state->position & 0xFF) == 0xFF && TaEffect_IsLoadModule(state) == 1) {
            if (state->flag != 0) {
                SzDuel_OpenMsgPopup(0, -0x78, 0x50, 0x103);
            } else {
                SzDuel_OpenMsgPopup(0, -0x78, 0x50, SzDuel_GetMsgName(0x339));
            }
            command->id = 0x25A;
            command->source = 0;
            command->target = state->position;
            command->value = 0;
            state->mode++;
            state->handles[state->cursor] = Ta_Do_Effect(command, state);
            state->entries.delayed.timers[state->cursor] = 0;
            state->cursor++;
        }
        break;
    case 17:
        if (SzEffect_IsUse(state->handles[state->cursor - 1]) == 1) {
            return 1;
        }
        SzDuel_SetUnitStatus((s32)state->position >> 8, state->position & 0xFF, 0, 1);
        Ta_Eff_036_LoadEffect(src, state);
        TaView_RestoreOriginalView(state, 0);
        state->mode = 0;
        break;
    default:
        return 1;
    }
    return 1;
}

/* Effect script 036_LoadEffect, step `ID`: its camera, fades and effect module. */
/* Loads the effect module of effect script 036. */
void Ta_Eff_036_LoadEffect(void *eInfo, void *Temp) {
    u32 temp_v1;

    temp_v1 = *(u32 *)((u8 *)eInfo + 0xC) >> 14;
    switch (temp_v1) {
    case 0x218:
        TaEffect_LoadModule(Temp, 0x218);
        return;
    case 0x21C:
        TaEffect_LoadModule(Temp, 0x21C);
        return;
    case 0x21D:
        TaEffect_LoadModule(Temp, 0x21D);
        return;
    case 0x21E:
        TaEffect_LoadModule(Temp, 0x21E);
        return;
    default:
        TaEffect_LoadModule(Temp, 0x218);
        return;
    }
}

/* Effect script 036_GetSound, step `ID`: its camera, fades and effect module. */
/* The sound effect script 036 plays. */
void Ta_Eff_036_GetSound(void *eInfo) {
    u32 temp_v1;

    temp_v1 = *(u32 *)((u8 *)eInfo + 0xC) >> 0xE;
    switch (temp_v1) {
    case 0x218:
        SzSound_PlaySE(1, 0x3B);
        return;
    case 0x21C:
        SzSound_PlaySE(1, 0x4B);
        return;
    case 0x21D:
        SzSound_PlaySE(1, 0x4E);
        return;
    case 0x21E:
        SzSound_PlaySE(1, 0x4F);
        return;
    default:
        SzSound_PlaySE(1, 0x4A);
        return;
    }
}

/* Effect script 036_ManageSound, step `ID`: its camera, fades and effect module. */
/* Plays effect script 036's sounds frame by frame. */
void Ta_Eff_036_ManageSound(void *eInfo, void *Temp) {
    u32 *p0;
    s32 *p1;
    u32 temp_a2;
    u32 temp_a3;
    s32 var_t0;
    s32 temp_v0;

    p0 = eInfo;
    p1 = Temp;
    temp_a3 = p0[3];
    temp_a2 = temp_a3 >> 0xE;
    switch (temp_a2) {
    case 0x218:
        var_t0 = 0x40;
        break;
    case 0x21C:
        var_t0 = 0x42;
        break;
    case 0x21D:
        var_t0 = 0x40;
        break;
    case 0x21E:
        var_t0 = 0x48;
        break;
    default:
        var_t0 = 0x30;
        break;
    }
    if (temp_a3 == 0x3E7) {
        temp_v0 = p1[0x34];
        p1[0x34] = temp_v0 + 1;
        switch (temp_v0) {
        case 0:
            SzSound_PlaySE(1, 0x38);
            break;
        case 0x14:
            SzSound_PlaySE(1, 0x39);
            break;
        case 0x1E:
            SzSound_PlaySE(1, 0x4C);
            break;
        case 0x24:
            Ta_Eff_036_GetSound(eInfo);
            break;
        default:
            if (p1[0x34] == var_t0) {
                SzSound_PlaySE(1, 0x3C);
            }
            break;
        }
        return;
    } else {
        temp_v0 = p1[0x34];
        p1[0x34] = temp_v0 + 1;
        switch (temp_v0) {
        case 0:
            SzSound_PlaySE(1, 0x38);
            return;
        case 0x14:
            SzSound_PlaySE(1, 0x39);
            return;
        case 0x1E:
            SzSound_PlaySE(1, 0x4C);
            return;
        case 0x24:
            Ta_Eff_036_GetSound(eInfo);
            return;
        case 0x25:
            if ((p0[3] >> 0xE) == 0x21D || (p0[3] >> 0xE) == 0x21E) {
                SzSound_PlaySE(1, 0x3B);
            }
            return;
        default:
            if (p1[0x34] == var_t0) {
                SzSound_PlaySE(1, 0x3C);
            }
            return;
        }
    }
}

typedef struct Packet_0026A0A0 {
    u32 command;
    u32 source;
    u32 target;
    u32 data;
} Packet_0026A0A0;

typedef struct State_0026A0A0 {
    u16 id;
    u16 mode;
    u16 phase;
    u8 handle;
    u8 pad07[0x19];
    u32 done;
    u8 pad24[0xA8];
    s32 card;
    s32 frame;
    u8 children;
    u8 padD5[0x2D];
    u16 ticks;
} State_0026A0A0;


/* Effect script 037, step `ID`: its camera, fades and effect module; it destroys units, changes life points, turns
   cards face up. */
s32 Ta_Eff_037(void *eInfo, void *Temp, s32 ID) {
    Packet_0026A0A0 packet_data;
    Packet_0026A0A0 *packet = &packet_data;
    Packet_0026A0A0 *request = eInfo;
    State_0026A0A0 *state = Temp;
    s32 frame;
    s32 locLo;
    s32 temp_s4;
    s32 temp_s5;
    s32 temp_v0_10;
    s32 temp_v0_11;
    s32 temp_v0_12;
    s32 card;
    s32 card2;
    s32 temp_v0_9;
    s32 var_a2;
    s32 forceEffection;
    s32 var_v0_2;
    u16 ticks;
    u16 phase;
    u16 ticks2;
    u32 source;
    u32 target;
    u32 target2;
    u32 source2;
    u32 target3;
    u32 source3;
    u32 source3In;
    u32 temp_v0_17;
    u32 data;
    u32 target3In;
    u32 temp_v0_20;
    u32 temp_v0_21;
    u32 data2;
    u32 temp_v0_23;
    u32 temp_v0_24;
    u32 temp_v0_25;
    u32 temp_v0_2;
    u32 temp_v0_3;
    u32 temp_v0_4;
    u32 temp_v0_5;
    u32 temp_v0_6;
    u32 temp_v0_7;
    u32 temp_v0_8;
    u32 var_v0;

    extern s32 SzDuel_GetUnitOpenRate();

    packet_data.command = 0x3E7;
    packet_data.source = 0;
    packet_data.target = 0;
    packet_data.data = 0;
    if (ID >= 0) {
        InitEffectTemp(Temp);
        target2 = request->target;
        if (SzDuel_GetUnitStatus((s32) (target2 >> 8), target2 & 0xFF, 2) != 0) {
            temp_v0_2 = request->target;
            SzDuel_SetUnitStatus(temp_v0_2 >> 8, temp_v0_2 & 0xFF, 4, 1);
        }
        temp_v0_3 = request->source;
        if (SzDuel_GetUnitStatus((s32) (temp_v0_3 >> 8), temp_v0_3 & 0xFF, 2) != 0) {
            temp_v0_4 = request->source;
            SzDuel_SetUnitStatus(temp_v0_4 >> 8, temp_v0_4 & 0xFF, 4, 1);
        }
        temp_v0_5 = request->source;
        if ((SzDuel_GetUnitKind((s32) (temp_v0_5 >> 8), temp_v0_5 & 0xFF) >> 5) == 0) {
            state->card = 1;
            temp_v0_6 = request->target;
            SzDuel_SetUnitStatus(temp_v0_6 >> 8, temp_v0_6 & 0xFF, 2, 1);
        } else {
            state->card = 2;
            temp_v0_7 = request->target;
            SzDuel_SetUnitStatus(temp_v0_7 >> 8, temp_v0_7 & 0xFF, 2, 1);
        }
        forceEffection = Ta_GetForceEffection((s32) ((u32) request->source >> 8), Ta_GetEnchantOfs());
        temp_v0_8 = request->source;
        if ((((SzDuel_GetUnitKind((s32) (temp_v0_8 >> 8), temp_v0_8 & 0xFF) >> 5) == 0) ? 1 : 2) == 1) {
            var_v0 = request->source;
        } else {
            var_v0 = request->target;
        }
        temp_s4 = var_v0 & 0xFF;
        temp_s5 = (s32) var_v0 >> 8;
        locLo = SzDuel_GetUnitLoc(temp_s5, temp_s4) & 0xFF;
        if (Ta_IsLDRangeAvilityWithLocation(temp_s5, temp_s4, locLo, SzDuel_GetUnitLoc(temp_s5, temp_s4) >> 8, 0xB) == 0) {
            if ((temp_v0_9 = Ta_IsActiveTrapB((s32) ((u32) request->data >> 0x10), 0x29)) >= 0) {
                TaEffect_LoadModule(Temp, 0x25A);
                if ((temp_v0_10 = Ta_IsActiveTrapB((s32) request->target, 0x2E)) >= 0) {
                    TaEffect_LoadModule(Temp, 0x219);
                    TaView_ReqFocusCamera(0, temp_v0_10, 0xB4, 0xB4);
                    SzEffect_SetBusyFlag2(temp_v0_10, 0);
                    TaUtil_DoOpen(temp_v0_10 >> 8, temp_v0_10 & 0xFF, 1);
                    state->card = temp_v0_10;
                    state->phase = 0x10U;
                    state->mode = 0U;
                    state->id = (u16) forceEffection;
                    return 1;
                }
                TaEffect_LoadModule(Temp, 0x223);
                SzDuel_SetWindowDraw(0);
                TaView_ReqFocusCamera(0, temp_v0_9, 0xB4, 0xB4);
                state->phase = 0x20U;
                SzEffect_SetBusyFlag2(temp_v0_9, 0);
                TaUtil_DoOpen(temp_v0_9 >> 8, temp_v0_9 & 0xFF, 1);
                state->card = temp_v0_9;
                state->mode = 0U;
                state->id = (u16) forceEffection;
                return 1;
            }
            if ((temp_v0_11 = Ta_IsActiveTrapB((s32) ((u32) request->target >> 8), 0x2B)) >= 0) {
                TaEffect_LoadModule(Temp, 0x219);
                TaEffect_LoadModule(Temp, 0x25A);
                if ((temp_v0_12 = Ta_IsActiveTrapB((s32) request->target, 0x2E)) >= 0) {
                    TaView_ReqFocusCamera(0, temp_v0_12, 0xB4, 0xB4);
                    SzEffect_SetBusyFlag2(temp_v0_12, 0);
                    TaUtil_DoOpen(temp_v0_12 >> 8, temp_v0_12 & 0xFF, 1);
                    state->card = temp_v0_12;
                    state->phase = 0x10U;
                    state->mode = 0U;
                    state->id = (u16) forceEffection;
                    return 1;
                }
                TaView_ReqFocusCamera(0, temp_v0_11, 0xB4, 0xB4);
                SzEffect_SetBusyFlag2(temp_v0_11, 0);
                TaUtil_DoOpen(temp_v0_11 >> 8, temp_v0_11 & 0xFF, 1);
                state->card = temp_v0_11;
                state->phase = 0x10U;
                state->mode = 1U;
                state->id = (u16) forceEffection;
                return 1;
            }
        }
        TaEffect_LoadModule(Temp, 0x219);
        if (forceEffection < 0) {
            forceEffection = 0;
        }
        state->phase = 2U;
        state->id = (u16) forceEffection;
        state->mode = 0U;
        return 1;
    }
    if (TaEffect_IsLoadModule(Temp) != 1) {
        return 1;
    }
    phase = state->phase;
    switch (phase) {
    case 0:
        SzDuel_SetWindowDraw(0);
        SzDuel_OpenMsgPopup(0, -0x78, 0x50, 0x10B);
        packet->command = 0x223;
        if (((u32) request->target >> 8) == 0) {
            var_v0_2 = 1;
        } else {
            var_v0_2 = 0;
        }
        packet->source = (u32) (var_v0_2 << 8);
        packet->target = (u32) (((u32) request->target >> 8) << 8);
        packet->data = (s32) state->id;
        state->handle = Ta_Do_Effect(packet, Temp);
        state->children = (u8) (state->children + 1);
        state->phase = (u16) (state->phase + 1);
        return 1;
    case 1:
        SzDuel_SetWindowDraw(0);
        if (SzEffect_IsUse((s32) state->handle) != 0) {
            ticks = state->ticks;
            state->ticks = (u16) (ticks + 1);
            if (ticks == 6) {
                TaView_ReqFireView(0x1E, ((request->target == 0) ? 1 : 0) << 8, 0x64U, 0xB4U);
            }
        } else {
            SzDuel_CloseMsgPopup();
            source2 = request->source;
            if ((SzDuel_GetUnitKind((s32) (source2 >> 8), source2 & 0xFF) >> 5) == 0) {
                target3 = request->target;
                Ta_DelUnit(target3 >> 8, target3 & 0xFF);
            } else {
                source3 = request->source;
                Ta_DelUnit(source3 >> 8, source3 & 0xFF);
            }
            SzDuel_CalcLP((s32) ((u32) request->source >> 8), 1, (s32) state->id);
            TaView_RestoreOriginalView(Temp, 0x10);
            state->ticks = 0U;
            if (SzDuel_GetWindowDisp() != 0) {
                SzDuel_SetWindowDraw(1);
            }
            state->phase = 0x40U;
        }
        return 1;
    case 2:
        if (state->mode == 1) {
            SzDuel_OpenMsgPopup(0, 0, -0xA0, SzDuel_GetMsgName(0x330));
        } else {
            SzDuel_OpenMsgPopup(0, 0, -0xA0, 0x10C);
        }
        packet->command = 0x219;
        packet->source = (u32) request->source;
        packet->target = (u32) request->target;
        source3In = request->source;
        if ((SzDuel_GetUnitKind((s32) (source3In >> 8), source3In & 0xFF) >> 5) == 0) {
            var_a2 = 1;
        } else {
            var_a2 = 2;
        }
        packet->data = (s32) ((state->id << 0x10) | ((state->mode << 8) | var_a2));
        state->handle = Ta_Do_Effect(packet, Temp);
        state->phase = (u16) (state->phase + 1);
        break;
    case 3:
        if (SzEffect_IsUse((s32) state->handle) != 0) {
            frame = state->frame;
            state->frame = (s32) (frame + 1);
            switch (frame) {
            case 0x0:
                SzSound_PlaySE(1, 0x38);
                break;
            case 0x14:
                SzSound_PlaySE(1, 0x39);
                break;
            case 0x1E:
                SzSound_PlaySE(1, 0x4C);
                break;
            case 0x24:
                SzSound_PlaySE(1, 0x4D);
                break;
            case 0x25:
                SzSound_PlaySE(1, 0x3B);
                break;
            case 0x40:
                SzSound_PlaySE(1, 0x3C);
                break;
            }
            if (SzEffect_GetStatus((s32) state->handle) == 2) {
                if (*(u8 *)&state->done != 0xFFFF) {
                    temp_v0_17 = request->source;
                    if ((SzDuel_GetUnitKind((s32) (temp_v0_17 >> 8), temp_v0_17 & 0xFF) >> 5) == 0) {
                        data = request->data;
                        source = request->source;
                        Enchant(source >> 8, source & 0xFF, (state->mode << 0x10) | (data & 0x3FFF), (data >> 0x10) & 0xFF);
                        target3In = request->target;
                        Ta_DelUnit(target3In >> 8, target3In & 0xFF);
                        temp_v0_20 = request->source;
                        if (SzDuel_GetUnitStatus((s32) (temp_v0_20 >> 8), temp_v0_20 & 0xFF, 4) == 0) {
                            temp_v0_21 = request->source;
                            SzDuel_SetUnitStatus(temp_v0_21 >> 8, temp_v0_21 & 0xFF, 2, 0);
                        }
                    } else {
                        data2 = request->data;
                        target = request->target;
                        Enchant(target >> 8, target & 0xFF, (state->mode << 0x10) | (data2 & 0x3FFF), (data2 >> 0x10) & 0xFF);
                        temp_v0_23 = request->source;
                        Ta_DelUnit(temp_v0_23 >> 8, temp_v0_23 & 0xFF);
                        temp_v0_24 = request->target;
                        if (SzDuel_GetUnitStatus((s32) (temp_v0_24 >> 8), temp_v0_24 & 0xFF, 4) == 0) {
                            temp_v0_25 = request->target;
                            SzDuel_SetUnitStatus(temp_v0_25 >> 8, temp_v0_25 & 0xFF, 2, 0);
                        }
                    }
                    state->done = 0xFFFF;
                }
            }
            return 1;
        }
        SzDuel_CloseMsgPopup();
        SzSound_PlaySE(0, 2);
        SzDuel_CloseMsgPopup();
        return 0;
    case 16:
        if (SzDuel_GetUnitOpenRate((u32)state->card >> 8, state->card & 0xFF) == 0xFF) {
            if (state->mode == 1) {
                SzDuel_OpenMsgPopup(0, -0x78, 0x50, 0x103);
            } else {
                SzDuel_OpenMsgPopup(0, -0x78, 0x50, SzDuel_GetMsgName(0x339));
            }
            packet->command = 0x25A;
            packet->source = 0U;
            packet->target = (u32) state->card;
            packet->data = 0;
            state->handle = Ta_Do_Effect(packet, Temp);
            state->done = 0;
            state->children = (u8) (state->children + 1);
            state->phase = 0x11U;
        }

        break;
    case 17:
        if (SzEffect_IsUse((s32) state->handle) == 1) {
            return 1;
        }
        card = state->card;
        SzDuel_SetUnitStatus((u32) card >> 8, card & 0xFF, 0, 1);
        SzDuel_CloseMsgPopup();
        TaView_RestoreOriginalView(Temp, 0);
        state->phase = 2U;
        break;
    case 32:
        SzDuel_SetWindowDraw(0);
        if (SzDuel_GetUnitOpenRate((u32)state->card >> 8, state->card & 0xFF) == 0xFF) {
            SzDuel_OpenMsgPopup(0, -0x78, 0x50, 0x32E);
            packet->command = 0x25A;
            packet->source = 0U;
            packet->target = (u32) state->card;
            packet->data = 0;
            state->handle = Ta_Do_Effect(packet, Temp);
            state->done = 0;
            state->children = (u8) (state->children + 1);
            state->phase = (u16) (state->phase + 1);
            break;
        }
        break;
    case 33:
        SzDuel_SetWindowDraw(0);
        if (SzEffect_IsUse((s32) state->handle) != 0) {
            return 1;
        }
        card2 = state->card;
        SzDuel_SetUnitStatus((u32) card2 >> 8, card2 & 0xFF, 0, 1);
        TaView_ReqBackFocusCamera(0, ((u32) state->card >> 8) << 8, 0x64, 0xB4);
        state->phase = 0U;
        break;
    default:
        ticks2 = state->ticks;
        state->ticks = (u16) (ticks2 + 1);
        if ((s32) ticks2 > 0x10) {
            SzSound_PlaySE(0, 2);
            SzDuel_CloseMsgPopup();
            return 0;
        }
        break;
    }
    return 1;
}

/* Whether side `nSide` has a face-down trap of kind `sKey` that can go off. */
s32 Ta_IsActiveTrapB(s32 nSide, s32 sKey) {
    switch (sKey) {
    case 0x29:
    case 0x2A:
    case 0x2C:
    case 0x23:
    case 0x4A:
    case 0x4B:
    case 0xE:
    case 0x4:
    case 0x30:
    case 0x31:
        return Ta_GetActiveTrapBUnit(nSide, 2, sKey);
    case 0x50:
    case 0x4C:
    case 0x2D:
    case 0x11:
    case 0x2E:
    case 0x2B:
        return Ta_GetActiveTrapBUnit(nSide, 3, sKey);
    default:
        return -1;
    }
}

/* The unit of side `nSide` holding a trap of kind `sKey` that can go off (effect owner `eOwner`), or none. */
s32 Ta_GetActiveTrapBUnit(s32 nSide, s32 eOwner, s32 sKey) {
    s32 i;
    s32 best;
    s32 result;
    u32 *entry;

    best = 0xFF;
    result = 0xFF;
    if (Ta_SearchUncTypeNaturalEffectUserNum(0xF) > 0) {
        return -1;
    }
    if (eOwner & 1) {
        for (i = 6; i < 11; i++) {
            if ((entry = Ta_GetUnitEffect(nSide, i, 0)) != NULL) {
                if ((SzDuel_GetUnitKind(nSide, i) >> 5) == 4 && (*entry >> 8) == sKey &&
                    SzDuel_GetUnitSummonOrder(nSide, i) < best) {
                    best = SzDuel_GetUnitSummonOrder(nSide, i);
                    result = (nSide << 8) | i;
                }
            }
        }
    }
    if (eOwner >> 1) {
        for (i = 6; i < 11; i++) {
            if ((entry = Ta_GetUnitEffect(nSide == 0 ? 1 : 0, i, 0)) != NULL) {
                if ((SzDuel_GetUnitKind(nSide == 0 ? 1 : 0, i) >> 5) == 4 && (*entry >> 8) == sKey &&
                    SzDuel_GetUnitSummonOrder(nSide == 0 ? 1 : 0, i) < best) {
                    best = SzDuel_GetUnitSummonOrder(nSide == 0 ? 1 : 0, i);
                    result = i | ((nSide == 0 ? 1 : 0) << 8);
                }
            }
        }
    }
    if (result != 0xFF) {
        return result;
    }
    return -1;
}

/* Whether unit (nSide, nID) choosing an action (`stDefense`) sets off a trap, into `eInfo`. */
s32 Ta_IsTrapBInDecideOperation(s32 nSide, s32 nID, s32 stDefense, s32 *eInfo) {
    s32 value;
    s32 position;
    s32 result;
    s32 id;
    s32 special;

    special = 0;
    position = SzDuel_GetUnitLoc(nSide, nID);
    id = Ta_GetCurrentSide(nSide, nID);
    if (!nID) {
        return 0;
    }
    if (Ta_IsLDRangeAvilityWithLocation(nSide, nID, position & 0xFF, position >> 8, 0xB) != 0) {
        special = 1;
    }
    if (Ta_IsResistAll(nSide, nID) != 0) {
        return 0;
    }
    switch (stDefense) {
    s32 fallback;
    case 0: {
        s32 value;
        if ((value = Ta_IsActiveTrapB(id, 0x2C)) >= 0) {
            if (1 == special) {
                s32 position;
                position = SzDuel_GetUnitLoc(id, 0);
                Ta_SetRangeVisual(position & 0xFF, position >> 8, 0, Ta_IsLDAbl(9, id), 1, 1, 0xB);
                eInfo[0] = 0xFE;
                eInfo[1] = 0;
                eInfo[2] = id << 8;
                eInfo[3] = 0x10;
                result = 1;
                break;
            }
            if ((fallback = Ta_IsActiveTrapB(nSide == 0 ? 1 : 0, 0x2E)) >= 0) {
                eInfo[0] = 0x66;
                eInfo[1] = 1;
                eInfo[2] = fallback;
                eInfo[3] = 0;
                result = 1;
                break;
            }
            eInfo[0] = 0x46;
            eInfo[1] = value;
            eInfo[2] = (nSide << 8) | nID;
            eInfo[3] = 0;
            result = 0x10001;
            break;
        }
        result = 0;
        break;
    }
    default: {
        s32 fallback;
        if ((value = Ta_IsActiveTrapB(id, 0x4A)) >= 0) {
            if (special == 1) {
                s32 position;
                position = SzDuel_GetUnitLoc(id, 0);
                Ta_SetRangeVisual(position & 0xFF, position >> 8, 0, Ta_IsLDAbl(9, id), 1, 1, 0xB);
                eInfo[0] = 0xFE;
                eInfo[1] = 0;
                eInfo[2] = id << 8;
                eInfo[3] = 0x10;
                result = 1;
                break;
            }
            if ((fallback = Ta_IsActiveTrapB(nSide == 0 ? 1 : 0, 0x2E)) >= 0) {
                eInfo[0] = 0x66;
                eInfo[1] = 1;
                eInfo[2] = fallback;
                result = 1;
                eInfo[3] = 0;
                break;
            }
            eInfo[0] = 0x47;
            eInfo[1] = value;
            eInfo[2] = (nSide << 8) | nID;
            eInfo[3] = 1;
            result = 0x10001;
            break;
        }
        if ((value = Ta_IsActiveTrapB(id, 0x23)) >= 0) {
            if (special == 1) {
                s32 position;
                position = SzDuel_GetUnitLoc(id, 0);
                Ta_SetRangeVisual(position & 0xFF, position >> 8, 0, Ta_IsLDAbl(9, id), 1, 1, 0xB);
                eInfo[0] = 0xFE;
                eInfo[1] = 0;
                eInfo[2] = id << 8;
                eInfo[3] = 0x10;
                result = 1;
                break;
            }
            if ((fallback = Ta_IsActiveTrapB(nSide == 0 ? 1 : 0, 0x2E)) >= 0) {
                eInfo[0] = 0x66;
                eInfo[1] = 1;
                eInfo[2] = fallback;
                eInfo[3] = 0;
                result = 1;
                break;
            }
            eInfo[0] = 0x47;
            eInfo[1] = value;
            eInfo[2] = (nSide << 8) | nID;
            eInfo[3] = 0;
            result = 1;
            break;
        }
        result = 0;
        break;
    }
    }
    return result;
}

/* Whether unit (nSide, nID) choosing an action (`stDefense`) would set off a trap (`IsView` shows the range). */
s32 Ta_IsTrapBInDecideOperation2(s32 nSide, s32 nID, s32 stDefense, u8 IsView) {
    s32 s1;
    s32 card;
    s32 pos;

    s1 = SzDuel_GetUnitLoc(nSide, nID);
    card = Ta_GetCurrentSide(nSide, nID);
    if (nID == 0) {
        return 0;
    }
    if (Ta_IsLDRangeAvilityWithLocation(nSide, nID, s1 & 0xFF, s1 >> 8, 0xB) != 0) {
        s1 = Ta_IsUnitControl(nSide, nID) == 0 ? 1 : 0;
        if (Ta_IsUnitHide(SzDuel_GetUnit(nSide, nID), s1) == 0) {
            return 1;
        }
    }
    if (Ta_IsResistAll(nSide, nID) != 0) {
        return 0;
    }
    switch (stDefense) {
    case 0:
        pos = Ta_IsActiveTrapB(card, 0x2C);
        if (pos >= 0 && (IsView != 0 || SzDuel_GetUnitStatus(pos >> 8, pos & 0xFF, 4) != 0)) {
            if (Ta_IsActiveTrapB(nSide == 0 ? 1 : 0, 0x2E) >= 0) {
                return 0;
            }
            return 0x10001;
        }
        return 0;
    default:
        pos = Ta_IsActiveTrapB(card, 0x4A);
        if (pos >= 0) {
            if (IsView != 0 || SzDuel_GetUnitStatus(pos >> 8, pos & 0xFF, 4) != 0) {
                if (Ta_IsActiveTrapB(nSide == 0 ? 1 : 0, 0x2E) >= 0) {
                    return 0;
                }
                return 0x10001;
            }
        } else {
            pos = Ta_IsActiveTrapB(card, 0x23);
            if (pos >= 0 && (IsView != 0 || SzDuel_GetUnitStatus(pos >> 8, pos & 0xFF, 4) != 0)) {
                if (Ta_IsActiveTrapB(nSide == 0 ? 1 : 0, 0x2E) >= 0) {
                    return 0;
                }
                return 1;
            }
        }
        return 0;
    }
}

/* Fills the trap effect when a trap goes off, into `eInfo`. */
s32 Ta_DoUncTrapB(void *eInfo) {
    ((s32 *)eInfo)[0] = 0x66;
    ((s32 *)eInfo)[1] = 1;
    ((s32 *)eInfo)[2] = Ta_IsActiveTrapB(0, 0x2E);
    ((s32 *)eInfo)[3] = 0;
    return 1;
}

typedef struct Request_0026B480 {
    u32 unused;
    u32 position;
    u32 result;
    u32 command;
} Request_0026B480;

typedef struct State_0026B480 {
    u8 pad0[4];
    u16 phase;
    u8 handles[26];
    s32 slots[45];
    u8 count;
    u8 padD5[0x2D];
    u16 timer;
} State_0026B480;


/* Effect script 054, step `ID`: its camera, fades and effect module; it destroys units, changes attack or defence,
   turns cards face up. */
s32 Ta_Eff_054(void *eInfo, void *Temp, s32 ID) {
    extern s32 SzDuel_GetUnitCardNo();
    extern s32 SzDuel_GetUnitOpenRate();
    extern s32 Ta_IsFinishDestEfc();
    s32 buffer[4];
    s32 *command = buffer;
    Request_0026B480 *request = eInfo;
    State_0026B480 *state = Temp;
    s32 card;
    s32 i;
    u32 position;
    u32 value;
    u16 timer;

    buffer[0] = 999;
    buffer[1] = 0;
    buffer[2] = 0;
    buffer[3] = 0;
    SzDuel_SetWindowDraw(0);
    if (ID >= 0) {
        InitEffectTemp(state);
        value = request->command;
        TaUtil_DoOpen((value & 0xFFFF) >> 8, value & 0xFF, 1);
        TaEffect_LoadModule(state, 0x22);
        TaEffect_LoadModule(state, 0x22B);
        TaEffect_LoadModule(state, 0x22D);
        TaEffect_LoadModule(state, 0x25A);
        TaEffect_LoadModule(state, 0x25B);
        TaView_ReqFocusCamera3(0, (u16)request->command, 180, 180);
        state->phase = 16;
        return 1;
    }

    switch (state->phase) {
    case 0:
        if (SzEffect_IsUse(state->handles[0]) == 1) {
            return 1;
        }
        value = request->command;
        SzDuel_SetUnitStatus((value & 0xFFFF) >> 8, value & 0xFF, 0, 1);
        value = request->command;
        SzDuel_OpenMsgPopup(0, -120, 80,
            SzDuel_GetMsgName(SzDuel_GetUnitCardNo((value & 0xFFFF) >> 8, value & 0xFF)));
        value = request->command;
        if ((value >> 16) != 49) {
            Ta_DelUnit((value & 0xFFFF) >> 8, value & 0xFF);
        }
        TaView_ReqFocusCamera(0, request->position, 100, 180);
        command[0] = 0x22;
        command[1] = 0;
        command[2] = request->position;
        command[3] = 0;
        state->handles[0] = Ta_Do_Effect(command, state);
        state->phase++;
        return 1;

    case 1:
        if (SzEffect_IsUse(state->handles[0]) == 1) {
            return 1;
        }
        switch (request->command >> 16) {
        case 4:
            position = request->position;
            card = SearchUnitByRange(0, 0,
                Ta_GetCurrentSide(position >> 8, position & 0xFF), 2, 0x35, 14);
            value = request->command;
            value = Ta_RemoveObjFromFlagLst2(card,
                Ta_IsUnitControl((value & 0xFFFF) >> 8, value & 0xFF));
            request->result = value;
            if (value == 0) {
                timer = state->timer++;
                if (timer > 16) {
                    SzDuel_CloseMsgPopup();
                    return 0;
                }
                return 1;
            }
            if (Ta_GetUnitNumFrom22bitFlagList(request->result) == 1) {
                TaView_ReqFocusCamera(0, Ta_GetUnitOwnerIDFromLstCount(request->result, 0), 100, 180);
            } else {
                TaView_ReqStdCompleteView(0);
            }
            Ta_SetEffectDependOnFlagLst(request, state, command, 0x22B);
            state->phase = 2;
            return 1;

        case 48:
            state->phase = 4;
            SzDuel_CloseMsgPopup();
            TaView_RestoreOriginalView(state, 16);
            break;

        case 49:
            TaView_ReqFocusCamera(0, request->result, 100, 180);
            command[0] = 0x22B;
            command[1] = 0;
            command[2] = request->result;
            command[3] = 0;
            state->handles[state->count] = Ta_Do_Effect(command, state);
            state->slots[state->count] = 1;
            state->phase = 2;
            state->count++;
            return 1;
        }
        return 1;

    case 2:
        switch (request->command >> 16) {
        case 4:
            if (Ta_ManageDestroyEffect(request, state, command) != 0) {
                state->phase++;
            }
            break;

        case 49:
            if (SzEffect_IsUse(state->handles[state->count - 1]) == 1 &&
                SzEffect_GetStatus(state->handles[state->count - 1]) == 2 &&
                state->slots[state->count - 1] >= 0) {
                command[0] = 0x22D;
                command[1] = 0;
                command[2] = request->result;
                command[3] = 0;
                state->handles[state->count] = Ta_Do_Effect(command, state);
                state->slots[state->count] = 1;
                state->phase++;
                state->count++;
            }
            break;

        default:
            SzDuel_CloseMsgPopup();
            return 0;
        }
        break;

    case 3:
        switch (request->command >> 16) {
        case 4:
            if (Ta_IsFinishDestEfc(request, state, command) != 0) {
                SzDuel_CloseMsgPopup();
                TaView_RestoreOriginalView(state, 16);
                state->phase++;
            }
            break;

        case 49:
            for (i = 0; i < state->count; i++) {
                if (SzEffect_IsUse(state->handles[i]) == 1) {
                    return 1;
                }
            }
            position = request->result;
            card = SzDuel_GetUnitAP(position / 256, position & 0xFF, 0);
            TaUtil_CalcUnitAP(position >> 8, (u8)position, 1, card >> 1);
            SzDuel_CloseMsgPopup();
            TaView_RestoreOriginalView(state, 16);
            state->phase++;
            break;

        default:
            SzDuel_CloseMsgPopup();
            return 0;
        }
        break;

    case 4:
        timer = state->timer++;
        if (timer > 16) {
            if (SzDuel_GetWindowDisp() != 0) {
                SzDuel_SetWindowDraw(1);
            }
            SzDuel_CloseMsgPopup();
            return 0;
        }
        break;

    case 16:
        value = request->command;
        if (SzDuel_GetUnitOpenRate((value & 0xFFFF) >> 8, value & 0xFF) == 0xFF &&
            TaEffect_IsLoadModule(state) == 1) {
            switch (request->command >> 16) {
            case 49:
                command[0] = 0x25A;
                command[1] = 0;
                command[2] = (u16)request->command;
                command[3] = 0;
                break;
            default:
                command[0] = 0x25A;
                command[1] = 0;
                command[2] = (u16)request->command;
                command[3] = 1;
                break;
            }
            state->handles[0] = Ta_Do_Effect(command, state);
            state->phase = 0;
            SzDuel_OpenMsgPopup(0, -120, 80, 0x103);
            return 1;
        }
        break;

    default:
        return 1;
    }
    return 1;
}

typedef struct Command_0026BB80 {
    s32 id;
    s32 mask;
    s32 x;
    s32 y;
} Command_0026BB80;

typedef struct State_0026BB80 {
    u8 pad0[4];
    u16 state;
    u8 handle;
    u8 pad7[0xFB];
    u16 timer;
} State_0026BB80;


/* Effect script 056, step `ID`: its camera, fades and effect module; it destroys units, turns cards face up. */
s32 Ta_Eff_056(void *eInfo, void *Temp, s32 ID) {
    extern s32 SzDuel_GetUnitOpenRate();
    Command_0026BB80 request;
    Command_0026BB80 *command = &request;
    State_0026BB80 *state = Temp;
    Command_0026BB80 *source = eInfo;
    s32 count;
    s32 i;
    s32 index;
    s32 position;

    request.id = 999;
    request.mask = 0;
    request.x = 0;
    request.y = 0;
    count = 0;
    SzDuel_SetWindowDraw(0);
    if (ID >= 0) {
        InitEffectTemp(Temp);
        for (i = 0; i < Ta_GetUnitNumFrom22bitFlagList(source->mask); i++) {
            position = Ta_GetUnitOwnerIDFromLstCount(source->mask, i);
            TaUtil_DoOpen(position >> 8, position & 0xFF, 1);
        }
        TaEffect_LoadModule(Temp, 0x3B);
        TaView_ReqStdCompleteView(0x10);
        return 1;
    }

    switch (state->state) {
    case 0:
        for (index = 0; index < Ta_GetUnitNumFrom22bitFlagList(source->mask); index++) {
            position = Ta_GetUnitOwnerIDFromLstCount(source->mask, index);
            if (SzDuel_GetUnitOpenRate(position >> 8, position & 0xFF) == 0xFF) {
                count++;
            }
        }
        if (count >= 3) {
            if (TaEffect_IsLoadModule(Temp) == 1) {
                state->state = 1;
                SzDuel_OpenMsgPopup(0, -0x78, 0x50, 0x105);
                command->id = 0x3B;
                command->mask = source->mask;
                command->x = source->x;
                command->y = source->y;
                state->handle = Ta_Do_Effect(command, Temp);
            }
        }
        return 1;
    case 1:
        if (SzEffect_IsUse(state->handle) == 1) {
            if (SzEffect_GetStatus(state->handle) == 2) {
                for (i = 0; i < Ta_GetUnitNumFrom22bitFlagList(source->mask); i++) {
                    position = Ta_GetUnitOwnerIDFromLstCount(source->mask, i);
                    Ta_DelUnit(position >> 8, position & 0xFF);
                }
            }
            return 1;
        }
        SzDuel_CloseMsgPopup();
        TaView_RestoreOriginalView(Temp, 0x10);
        state->state++;
        break;
    default:
        if (state->timer++ > 0x10) {
            if (SzDuel_GetWindowDisp() != 0) {
                SzDuel_SetWindowDraw(1);
            }
            SzDuel_CloseMsgPopup();
            return 0;
        }
        break;
    }
    return 1;
}

typedef struct {
    u8 pad0[4];
    s32 field_4;
    u32 field_8;
    s32 field_C;
} Object_0026BE20;

typedef struct {
    u8 pad0[4];
    u16 state;
    u8 id;
} State_0026BE20;

typedef struct {
    s32 field_0;
    s32 field_4;
    u32 field_8;
    s32 field_C;
} Temp_0026BE20;

/* Effect script 101, step `ID`: its camera, fades and effect module; it turns cards face up. */
s32 Ta_Eff_101(void *eInfo, void *Temp, s32 ID) {
    extern s32 SzDuel_GetUnitOpenRate();
    Temp_0026BE20 tempStorage;
    Temp_0026BE20 *temp = &tempStorage;
    State_0026BE20 *state;
    Object_0026BE20 *obj = (Object_0026BE20 *)eInfo;

    temp->field_0 = 0x3E7;
    temp->field_4 = 0;
    temp->field_8 = 0;
    temp->field_C = 0;

    state = (State_0026BE20 *)Temp;

    if (ID >= 0) {
        InitEffectTemp(state);
        TaEffect_LoadModule(state, 0x259);
        TaUtil_DoOpen(obj->field_8 >> 8, obj->field_8 & 0xFF, 1);
        return 1;
    }

    if (TaEffect_IsLoadModule(state) == 1) {
        if (SzDuel_GetUnitOpenRate(obj->field_8 >> 8, obj->field_8 & 0xFF) == 0xFF) {
            if (state->state == 0) {
                temp->field_0 = 0x259;
                temp->field_4 = 0;
                temp->field_8 = obj->field_8;
                temp->field_C = obj->field_C;
                state->id = Ta_Do_Effect(temp, state);
                state->state++;
            } else {
                if (SzEffect_IsUse(state->id) == 1) {
                    return 1;
                }
                SzDuel_CloseMsgPopup();
                return 0;
            }
        }
    }
    return 1;
}

typedef struct {
    u8 pad0[4];
    s32 field_4;
    u32 field_8;
    s32 field_C;
} Object_0026BF50;

typedef struct {
    u8 pad0[4];
    u16 state;
    u8 id;
    u8 pad7;
    u8 pad8[0xFA];
    u16 counter;
} State_0026BF50;

typedef struct {
    s32 field_0;
    s32 field_4;
    u32 field_8;
    s32 field_C;
} Temp_0026BF50;


/* Effect script 102, step `ID`: its camera, fades and effect module; it destroys units, turns cards face up. */
s32 Ta_Eff_102(void *eInfo, void *Temp, s32 ID) {
    extern s32 SzDuel_GetUnitCardNo();
    extern s32 SzDuel_GetUnitOpenRate();
    Temp_0026BF50 tempStorage;
    Temp_0026BF50 *temp = &tempStorage;
    State_0026BF50 *state;
    Object_0026BF50 *obj = (Object_0026BF50 *)eInfo;

    temp->field_0 = 0x3E7;
    temp->field_4 = 0;
    temp->field_8 = 0;
    temp->field_C = 0;

    state = (State_0026BF50 *)Temp;

    if (ID >= 0) {
        InitEffectTemp(state);
        TaUtil_DoOpen(obj->field_8 >> 8, obj->field_8 & 0xFF, 1);
        TaView_ReqFocusCamera(0, obj->field_8, 0xB4, 0xB4);
        TaEffect_LoadModule(state, 0x25A);
        return 1;
    }

    switch (state->state) {
    case 0:
        if (SzDuel_GetUnitOpenRate(obj->field_8 >> 8, obj->field_8 & 0xFF) == 0xFF) {
            if (TaEffect_IsLoadModule(state) == 1) {
                if (obj->field_4 == 1) {
                    s32 value = SzDuel_GetUnitCardNo(obj->field_8 >> 8, obj->field_8 & 0xFF);
                    SzDuel_OpenMsgPopup(0, -0x78, 0x50, SzDuel_GetMsgName(value));
                } else {
                    SzDuel_OpenMsgPopup(0, -0x78, 0x50, 0x10D);
                }
                temp->field_0 = 0x25A;
                temp->field_4 = 0;
                temp->field_8 = obj->field_8;
                temp->field_C = 0;
                state->id = Ta_Do_Effect((s32 *)temp, state);
                state->state++;
            }
        }
        break;
    case 1:
        if (SzEffect_IsUse(state->id) != 0) {
            return 1;
        }
        SzDuel_SetUnitStatus(obj->field_8 >> 8, obj->field_8 & 0xFF, 0, 1);
        SzDuel_CloseMsgPopup();
        TaView_RestoreOriginalView(state, 0x10);
        if (obj->field_C != 0) {
            Ta_DelUnit(obj->field_8 >> 8, obj->field_8 & 0xFF);
        } else {
            SzEffect_SetBusyFlag2(obj->field_8, 0);
        }
        state->state++;
        return 1;
    default:
        if (state->counter++ > 0x10) {
            SzDuel_CloseMsgPopup();
            return 0;
        }
        break;
    }
    return 1;
}

typedef struct Request_0026C170 {
    s32 command;
    s32 value;
    s32 cell;
    s32 flag;
} Request_0026C170;

typedef struct State_0026C170 {
    u16 fade;
    u8 pad02[2];
    u16 phase;
    u8 handles[0x1A];
    s32 counters[0x2C];
    s32 timer2;
    u8 count;
    u8 padD5[0x2B];
    u8 stage;
    u8 pad101;
    u16 timer;
} State_0026C170;

typedef struct Card_0026C170 {
    u8 pad00[4];
    u8 *model;
    u8 pad08[0x38];
    u8 x;
    u8 y;
} Card_0026C170;

typedef struct Rot_0026C170 {
    s32 x;
    s32 y;
    s32 z;
    s32 w;
} Rot_0026C170;

typedef struct Vec4_0026C170 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4_0026C170;

/* Effect script 109, step `ID`: its camera, fades and effect module; it destroys units, turns cards face up. */
s32 Ta_Eff_109(u32 *src, void *Temp, s32 ID) {
    s32 busy;
    Request_0026C170 data;
    u8 done = 0;
    Request_0026C170 *req = &data;
    State_0026C170 *state = Temp;
    Card_0026C170 *card;
    Vec4_0026C170 color;
    Vec4_0026C170 pos;
    Rot_0026C170 rot;
    s32 i;
    u32 *list;
    u8 *handle;

    data.command = 999;
    data.value = 0;
    data.cell = 0;
    data.flag = 0;
    SzDuel_SetWindowDraw(0);
    color.w = 0.0f;
    color.z = 0.0f;
    color.y = 0.0f;
    color.x = 0.0f;
    busy = 0;
    card = (Card_0026C170 *)SzDuel_GetUnit(src[1], 0);
    if (ID >= 0) {
        InitEffectTemp(state);
        SzSound_PlayBGM(0x2B, 0);
        TaEffect_LoadModule(state, 0x3D);
        TaEffect_LoadModule(state, 0x3E);
        TaEffect_LoadModule(state, 0x3F);
        TaEffect_LoadModule(state, 0x26C);
        if (TaTuto_IsTuto(SzDuel_GetTurnOwner()) == 0) {
            SzModel_Load(0x20, -1, 0x2E1, 1);
            SzModel_SetScale(0x20, &color);
        }
        TaUtil_DoOpen(src[1], src[2] & 7, 1);
        TaUtil_DoOpen(src[1], (src[2] >> 3) & 7, 1);
        TaUtil_DoOpen(src[1], (src[2] >> 6) & 7, 1);
        TaUtil_DoOpen(src[1], (src[2] >> 9) & 7, 1);
        state->fade = 0x80;
        for (i = 1; i < 11; i++) {
            if (SzDuel_GetUnit((src[1] == 0) ? 1 : 0, i)) {
                TaUtil_DoOpen((src[1] == 0) ? 1 : 0, i, 1);
            }
        }
        return 1;
    }
    switch (state->stage) {
    case 0:
        if (SzSound_IsLoadingBGM() == 0) {
            TaView_ReqFocusCamera(0, (src[1] << 8) | (src[2] & 7), 0x32, 0xB4);
            SzSound_PlayBGM(0x2B, 1);
            if (card->model == NULL) {
                card->model = SzDuel_GetCardRequest();
            }
            if (card->model != NULL) {
                *(Card_0026C170 **)(card->model + 0x90) = card;
                SzDuel_CalcUnitPos(card->x, card->y, 0, card->model);
                pos.x = 0.0f;
                pos.y = 0.0f;
                pos.z = (src[1] == 0) ? 350.0f : -350.0f;
                rot.x = 0;
                rot.y = (src[1] == 0) ? 0x8000 : 0;
                rot.z = 0;
                SzModel_SetPos(0x20, &pos);
                SzModel_SetRot(0x20, &rot);
            }
            TaUtil_DoOpen(src[1], 0, 1);
            SzDuel_SetUnitCtlGoalC(src[1], 0, 0);
            SzDuel_SetUnitCtlRateC(src[1], 0, -1, 0);
            SzDuel_SetUnitOpenRate(src[1], 0, 1, 0x80);
            state->stage++;
        }
        break;
    case 1:
        if (state->timer++ > 24) {
            if (SzEffect_IsModelStandby2((src[1] << 8) | ((src[2] >> 3) & 7))) {
                TaView_ReqFocusCamera(0, (src[1] << 8) | ((src[2] >> 3) & 7), 0x32, 0xB4);
                state->timer = 0;
                state->stage++;
            }
        }
        break;
    case 2:
        if (state->timer++ > 24) {
            if (SzEffect_IsModelStandby2((src[1] << 8) | ((src[2] >> 6) & 7))) {
                TaView_ReqFocusCamera(0, (src[1] << 8) | ((src[2] >> 6) & 7), 0x32, 0xB4);
                state->timer = 0;
                state->stage++;
            }
        }
        break;
    case 3:
        if (state->timer++ > 24) {
            if (SzEffect_IsModelStandby2((src[1] << 8) | ((src[2] >> 9) & 7))) {
                TaView_ReqFocusCamera(0, (src[1] << 8) | ((src[2] >> 9) & 7), 0x32, 0xB4);
                state->timer = 0;
                state->stage++;
            }
        }
        break;
    case 4:
        if (state->timer++ > 24) {
            if (SzEffect_IsModelStandby2(src[1] << 8)) {
                TaView_ReqFocusCamera(0, src[1] << 8, 0xC8, 0xB4);
                SzGame_SetAutoBlur(6);
                state->timer = 0;
                state->stage++;
            }
        }
        break;
    case 5:
        if (state->timer++ == 0) {
            SzSound_PlaySE(0, 0x27);
            TaView_ReqFocusCamera(0xC, src[1] << 8, 0x32, 0xB4);
            return 1;
        }
        if (state->timer >= 12) {
            SzGame_SetAutoBlur(4);
        }
        if (state->timer >= 24 && TaEffect_IsLoadModule(state)) {
            SzGame_SetAutoBlur(0);
            TaView_ReqExzFocusCamera(0, src[1] << 8, 0xB4, 0xB4);
            state->phase++;
            state->timer = 0;
            state->stage++;
        }
        break;
    }
    switch (state->phase) {
    case 0:
        break;
    case 1:
        req->command = 0x26C;
        req->value = 0;
        req->cell = SzDuel_GetUnitLoc(src[1], (src[2] >> 9) & 7);
        req->flag = 0;
        state->handles[state->count] = Ta_Do_Effect(req, state);
        state->count++;
        state->timer = 0;
        state->phase++;
        break;
    case 2:
        if (state->timer++ > 24) {
            req->command = 0x26C;
            req->value = 0;
            req->cell = SzDuel_GetUnitLoc(src[1], (src[2] >> 6) & 7);
            req->flag = 0;
            state->handles[state->count] = Ta_Do_Effect(req, state);
            state->count++;
            state->timer = 0;
            state->phase++;
        }
        break;
    case 3:
        if (state->timer++ > 24) {
            req->command = 0x26C;
            req->value = 0;
            req->cell = SzDuel_GetUnitLoc(src[1], (src[2] >> 3) & 7);
            req->flag = 0;
            state->handles[state->count] = Ta_Do_Effect(req, state);
            state->count++;
            state->timer = 0;
            state->phase++;
        }
        break;
    case 4:
        if (state->timer++ > 24) {
            req->command = 0x26C;
            req->value = 0;
            req->cell = SzDuel_GetUnitLoc(src[1], src[2] & 7);
            req->flag = 0;
            state->handles[state->count] = Ta_Do_Effect(req, state);
            state->count++;
            state->timer = 0;
            state->phase++;
        }
        break;
    case 5:
        if (state->timer++ > 24) {
            Ta_UnitFade(src[1], 0, 1, 1, 2);
            req->command = 0x26C;
            req->value = 0;
            req->cell = SzDuel_GetUnitLoc(src[1], 0);
            req->flag = 0;
            state->handles[state->count] = Ta_Do_Effect(req, state);
            state->count++;
            state->timer = 0;
            state->phase++;
        }
        break;
    case 6:
        for (i = 0; i < state->count; i++) {
            if (SzEffect_IsUse(state->handles[i])) {
                return 1;
            }
        }
        if (TaTuto_IsTuto(SzDuel_GetTurnOwner()) == 1) {
            if (SzEffect_GetBlackOutForDuel() > 0) {
                SzEffect_SetBlackOutForDuel((u8)(SzEffect_GetBlackOutForDuel() - 4));
            } else {
                done++;
            }
            if (SzEffect_GetBlackOutForMonster() > 0) {
                SzEffect_SetBlackOutForMonster((u8)(SzEffect_GetBlackOutForMonster() - 4));
            } else {
                done++;
            }
            if (done == 2) {
                SzDuel_SetWindowDisp(0);
                SzDuel_CloseMsgPopup();
                return 0;
            }
            return 1;
        }
        state->count = 0;
        if (SzModel_IsModelStandby(0x20)) {
            list = (u32 *)SzModel_GetEffTextureB(0x20);
            SzText_FreeRequest(5, -1);
            for (i = 0; i < 8; i++) {
                SzText_AddFile(5, i, 0, *list);
                list++;
            }
            SzView_FreeRequest(0, 0);
            SzView_ReqCamera(0, 0, 8, 0, 0x20, (void *)SzModel_GetCamera(0x20, 0x13));
            req->command = 0x3D;
            req->value = src[1];
            req->cell = src[2];
            req->flag = src[3];
            state->handles[state->count] = Ta_Do_Effect(req, state);
            state->counters[state->count] = 0x3D;
            state->count++;
            req->command = 0x3E;
            req->value = src[1];
            req->cell = src[2];
            req->flag = src[3];
            state->handles[state->count] = Ta_Do_Effect(req, state);
            state->counters[state->count] = 0x3E;
            state->count++;
            req->command = 0x3F;
            req->value = src[1];
            req->cell = src[2];
            req->flag = src[3];
            state->handles[state->count] = Ta_Do_Effect(req, state);
            state->counters[state->count] = 0x3F;
            state->count++;
            state->phase++;
        }
        break;
    case 7:
        Ta109_BlackOutForExz(-1);
        if (state->timer++ > 100) {
            color.x = 1.0f;
            color.y = 1.0f;
            color.z = 1.0f;
            color.w = 1.0f;
            SzModel_SetScale(0x20, &color);
            state->phase++;
            state->timer = 0;
        }
        break;
    case 8:
        for (i = 0; i < state->count; i++) {
            handle = &state->handles[i];
            if (SzEffect_IsUse(*handle)) {
                if (SzEffect_GetStatus(*handle) == 2) {
                    Ta109_BlackOutForExz(1);
                    SzDuel_DelUnit(src[1], src[2] & 7);
                    SzDuel_DelUnit(src[1], (src[2] >> 3) & 7);
                    SzDuel_DelUnit(src[1], (src[2] >> 6) & 7);
                    SzDuel_DelUnit(src[1], (src[2] >> 9) & 7);
                    SzModel_Preset(0x20, -1, 999);
                    if (card->model) {
                        SzDuel_FreeCardRequest(card->model);
                    }
                    card->model = NULL;
                }
                busy++;
            }
        }
        if (busy == 0) {
            SzText_FreeRequest(5, -1);
            SzDuel_CloseMsgPopup();
            return 0;
        }
        break;
    }
    return 1;
}

/* Darkens (`Flip`) or restores the models for the Exodia win scene. */
void Ta109_BlackOutForExz(s32 Flip) {
    f32 v[4];
    f32 *p;

    if (Flip < 0) {
        SzModel_GetIntensity(1, v);
        if (v[0] - 0.08f < 0.0f) {
            v[0] = 0.0f;
        } else {
            v[0] -= 0.08f;
        }
        p = &v[1];
        if (*p - 0.08f < 0.0f) {
            *p = 0.0f;
        } else {
            *p -= 0.08f;
        }
        SzModel_SetIntensity(1, v);
        SzModel_GetIntensity(5, v);
        if (v[0] - 0.08f < 0.0f) {
            v[0] = 0.0f;
        } else {
            v[0] -= 0.08f;
        }
        if (*p - 0.08f < 0.0f) {
            *p = 0.0f;
        } else {
            *p -= 0.08f;
        }
        SzModel_SetIntensity(5, v);
        SzModel_GetIntensity(6, v);
        if (v[0] - 0.08f < 0.0f) {
            v[0] = 0.0f;
        } else {
            v[0] -= 0.08f;
        }
        if (*p - 0.08f < 0.0f) {
            *p = 0.0f;
        } else {
            *p -= 0.08f;
        }
        SzModel_SetIntensity(6, v);
    } else {
        SzModel_GetIntensity(1, v);
        v[0] = 0.8f;
        p = &v[1];
        *p = 0.8f;
        SzModel_SetIntensity(1, v);
        SzModel_GetIntensity(5, v);
        v[0] = 0.8f;
        *p = 0.8f;
        SzModel_SetIntensity(5, v);
        SzModel_GetIntensity(6, v);
        v[0] = 0.8f;
        *p = 0.8f;
        SzModel_SetIntensity(6, v);
    }
}

typedef struct {
    u16 fade;
    u16 phase;
    u16 state;
    u8 handles[0x1A];
    s32 values[45];
    u8 count;
    u8 padding[0x2D];
    u16 timer;
} State_0026CFC0;

typedef struct {
    s32 kind;
    s32 flags;
    s32 value;
    s32 extra;
} Command_0026CFC0;

typedef struct {
    s32 unused;
    s32 value;
} Input_0026CFC0;


/* Effect script 072, step `ID`: its camera, fades and effect module; it moves units. */
s32 Ta_Eff_072(void *eInfo, void *Temp, s32 ID) {
    Command_0026CFC0 command;
    Command_0026CFC0 *cmd = &command;
    Input_0026CFC0 *input = eInfo;
    State_0026CFC0 *state = Temp;
    s32 i;

    cmd->kind = 999;
    cmd->flags = 0;
    cmd->value = 0;
    cmd->extra = 0;
    SzDuel_SetWindowDraw(0);
    if (ID >= 0) {
        InitEffectTemp(state);
        state->fade = 0x80;
        i = 0;
        do {
            SzEffect_SetBusyFlag2(i, 1);
            SzEffect_SetBusyFlag2(i | 0x100, 1);
            i++;
        } while (i < 11);
        TaView_ReqFocusCamera(30, input->value, 100, 180);
        TaEffect_LoadModule(state, 0x201);
        TaEffect_LoadModule(state, 0x23C);
        TaView_ReqStdCompleteView(30);
        state->phase = 2;
        SzGame_SetAutoBlur(4);
    } else {
    switch (state->state) {
    case 0:
        state->timer++;
        if (state->fade > 0x30) {
            state->fade -= 15;
        } else {
            state->fade = 0x30;
            if (state->timer >= 30 && TaEffect_IsLoadModule(state) == 1) {
                cmd->kind = 0x201;
                cmd->flags = 0;
                cmd->value = input->value;
                cmd->extra = 0;
                state->handles[0] = Ta_Do_Effect((s32 *)cmd, state);
                state->values[0] = input->value;
                state->state++;
            }
        }
        if (state->fade < 0x30) {
            state->fade = 0x30;
        }
        SzEffect_SetBlackOutForDuel((u8)state->fade);
        break;
    case 1:
        if (SzEffect_IsUse(state->handles[0]) != 0) {
            return 1;
        }
        TaView_ReqStdCompleteView(0);
        state->state++;
        break;
    case 2: {
        u16 phase;
        state->count = 0;
        phase = state->phase;
        if (phase >= 14) {
            TaView_RestoreOriginalView(state, 16);
            SzGame_SetAutoBlur(0);
            state->timer = 0;
            state->state = 4;
        } else if (Ta_SetGravityEffect(input, state, phase) > 0) {
            state->state++;
        } else {
            state->phase++;
        }
        break;
    }
    case 3: {
        u8 *cursor;
        s32 j;
        for (i = 0; i < state->count; i++) {
            if (SzEffect_IsUse(state->handles[i]) != 0) {
                return 1;
            }
        }
        j = 0;
        cursor = (u8 *)state;
        for (; j < state->count; j++) {
            s32 value = *(s32 *)(cursor + 0x20);
            SzDuel_MoveUnit(value >> 24, (value >> 16) & 0xFF,
                         value & 0xFF, (value & 0xFFFF) >> 8);
            cursor += 4;
        }
        if (state->phase >= 14) {
            state->state++;
            break;
        }
        state->state = 2;
        state->phase++;
        return 1;
    }
    case 4:
        state->fade += 15;
        if (state->fade > 0x80) {
            state->fade = 0x80;
        }
        SzEffect_SetBlackOutForDuel((u8)state->fade);
        if (state->fade == 0x80 && state->timer++ > 16) {
            i = 0;
            do {
                SzEffect_SetBusyFlag2(i, 0);
                SzEffect_SetBusyFlag2(i | 0x100, 0);
                i++;
            } while (i < 11);
            if (SzDuel_GetWindowDisp() != 0) {
                SzDuel_SetWindowDraw(1);
            }
            SzDuel_CloseMsgPopup();
            return 0;
        }
        break;
    default:
        break;
    }
    }
    return 1;
}

struct jp_6989c_26d3c0 {
    int eNO;
    unsigned int dwFrom;
    unsigned int dwTo;
    unsigned int dwPar;
};
struct jp_68cb4_26d3c0 {
    int fLoad : 1;
    unsigned char bModNum : 5;
    unsigned short wModule[24];
    unsigned char bModCond[24];
};
struct jp_69942_26d3c0 {
    unsigned short wCount_1;
    unsigned short wCount_2;
    unsigned short wLvl;
    unsigned char eID[24];
    int ePos[24];
    struct jp_68cb4_26d3c0 eMod;
    unsigned int fObj;
    unsigned int fObj2;
    unsigned char oNum;
    unsigned char unknown_d5[0xb];
    int camDat[8];
    unsigned char bCamLvl;
    unsigned short wCamTime;
    unsigned char unknown_104[0xc];
    int nTasakiEfc[0x10c];
};
#define GRAV_MAX(a, b) ((a) > (b) ? (a) : (b))
#define GRAV_MIN(a, b) ((a) < (b) ? (a) : (b))

/* Moves the effect's target units `Dist` squares by a pull (gravity) effect. */
int Ta_SetGravityEffect(void *eInfo_v, void *Temp_v, int Dist)
{
    struct jp_6989c_26d3c0 * eInfo = eInfo_v;
    struct jp_69942_26d3c0 * Temp = Temp_v;
    int Reserve[22];
    struct jp_6989c_26d3c0 eCall;
    struct jp_6989c_26d3c0 *pCall = &eCall;
    int eObj;
    int Unit;
    int Loc;
    int Num;
    int i;

    eCall.eNO = 999;
    eCall.dwFrom = 0;
    eCall.dwTo = 0;
    eCall.dwPar = 0;
    for (i = 0; i < 22; i++) {
        Reserve[i] = -1;
    }
    Num = Ta_GetUnitNumFrom22bitFlagList(eInfo->dwTo);
    for (i = 0, eObj = 0; i < Num; i++) {
        Unit = Ta_GetUnitOwnerIDFromLstCount(eInfo->dwTo, i);
        Loc = SzDuel_GetUnitLoc(Unit >> 8, Unit & 0xFF);
        if (Dist == (int)((GRAV_MAX(eInfo->dwFrom & 0xFF, (unsigned)(Loc & 0xFF)) - GRAV_MIN(eInfo->dwFrom & 0xFF, (unsigned)(Loc & 0xFF))) + (GRAV_MAX(eInfo->dwFrom >> 8, (unsigned)(Loc >> 8)) - GRAV_MIN(eInfo->dwFrom >> 8, (unsigned)(Loc >> 8))))) {
            eObj = ConvUnitIDtoFlagList(eObj, Unit >> 8, Unit & 0xFF);
        }
    }
    Num = Ta_GetUnitNumFrom22bitFlagList(eObj);
    for (i = 0; i < Num; i++) {
        Unit = Ta_GetMinimumOrderUnitFromFlagList2(eObj, eInfo->dwPar);
        if (Unit >= 0) {
            eObj = ConvUnitIDtoFlagList_OFF(eObj, Unit >> 8, Unit & 0xFF);
            if ((Loc = Ta_RequestGravityReserve(eInfo->dwFrom & 0xFF, eInfo->dwFrom >> 8, Unit, Reserve)) >= 0) {
                Reserve[i] = Loc;
                pCall->eNO = 572;
                pCall->dwFrom = 0;
                pCall->dwTo = Unit;
                pCall->dwPar = Loc;
                Temp->eID[Temp->oNum] = Ta_Do_Effect(pCall, Temp);
                Temp->ePos[Temp->oNum] = (Unit << 16) | Loc;
                Temp->oNum++;
            }
        }
    }
    return Num;
}
#undef GRAV_MAX
#undef GRAV_MIN

/* Reserves the square a unit on (nX, nZ) is pulled to, into `Reserve`. */
s32 Ta_RequestGravityReserve(s32 nX, s32 nZ, s32 Unit, s32 *Reserve) {
    s32 i;
    s32 *p;
    s32 result;
    s32 retry;
    s32 j;

    result = Ta_GetUnitGravityLoc(nX, nZ, Unit, 0);
    if (result >= 0) {
        i = 0;
        p = Reserve;
        do {
            if (result == *p) {
                retry = Ta_GetUnitGravityLoc(nX, nZ, Unit, 1);
                if (retry >= 0) {
                    j = 0;
                    do {
                        if (retry == *Reserve) {
                            return -1;
                        }
                        j++;
                        Reserve++;
                    } while (j < 22);
                    return retry;
                }
                return -1;
            }
            i++;
            p++;
        } while (i < 22);
        return result;
    }
    return -1;
}

/* The square unit `Unit` on (nX, nZ) is pulled to, for pull order `Order`. */
s32 Ta_GetUnitGravityLoc(s32 nX, s32 nZ, s32 Unit, s32 Order) {
    s32 locLo;
    s32 temp_s1;
    s32 temp_s1_2;
    s32 locHi;
    s32 locHi2;
    s32 loc;
    s32 var_v0;
    s32 var_v0_2;

    loc = SzDuel_GetUnitLoc(Unit >> 8, Unit & 0xFF);
    locLo = loc & 0xFF;
    if (nX < locLo) {
        temp_s1 = locLo - 1;
        locHi2 = loc >> 8;
        if (SzDuel_GetMapUnitID(temp_s1, locHi2) < 0) {
            if (Order == 0) {
                var_v0_2 = (locHi2 << 8) | temp_s1;
            } else {
                var_v0_2 = Ta_GetUnitGravityLocSearchOnZ(nX, nZ, locLo, locHi2);
            }
            return var_v0_2;
        }
        return Ta_GetUnitGravityLocSearchOnZ(nX, nZ, locLo, locHi2);
    }
    if (locLo < nX) {
        temp_s1_2 = locLo + 1;
        locHi = loc >> 8;
        if (SzDuel_GetMapUnitID(temp_s1_2, locHi) < 0) {
            if (Order == 0) {
                var_v0 = (locHi << 8) | temp_s1_2;
            } else {
                var_v0 = Ta_GetUnitGravityLocSearchOnZ(nX, nZ, locLo, locHi);
            }
            return var_v0;
        }
        return Ta_GetUnitGravityLocSearchOnZ(nX, nZ, locLo, locHi);
    }
    return Ta_GetUnitGravityLocSearchOnZ(nX, nZ, locLo, loc >> 8);
}

/* The free square a pulled unit stops on along its column (the names stay: no JP names known). */
s32 Ta_GetUnitGravityLocSearchOnZ(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg3 < arg1) {
        if (SzDuel_GetMapUnitID(arg2, arg3 + 1) < 0) {
            return ((arg3 + 1) << 8) | arg2;
        } else {
            return -1;
        }
    } else if (arg1 < arg3) {
        if (SzDuel_GetMapUnitID(arg2, arg3 - 1) < 0) {
            return ((arg3 - 1) << 8) | arg2;
        } else {
            return -1;
        }
    } else {
        return -1;
    }
}

typedef struct Command_0026D8F0 {
    s32 unused;
    s32 kind;
    u32 flags;
    s32 value;
} Command_0026D8F0;

typedef struct State_0026D8F0 {
    u16 value;
    u16 unused2;
    u16 stage;
    u8 ids[26];
    s32 positions[45];
    u8 count;
    u8 padding[0x2D];
    u16 timer;
} State_0026D8F0;

/* Effect script 066, step `ID`: its camera, fades and effect module. */
s32 Ta_Eff_066(void *eInfo, void *Temp, s32 ID) {
    extern s32 SzDuel_SetUnitKind();
    extern s32 SzDuel_SetUnitAttr();
    s32 stackData[4];
    s32 *data = stackData;
    s32 i;
    s32 count;
    Command_0026D8F0 *command = eInfo;
    State_0026D8F0 *state = Temp;

    data[0] = 999;
    data[1] = 0;
    data[2] = 0;
    data[3] = 0;
    count = 0;
    SzDuel_SetWindowDraw(0);
    if (ID >= 0) {
        InitEffectTemp(Temp);
        state->value = 0x80;
        if (Ta_GetUnitNumFrom22bitFlagList(command->flags) == 1) {
            TaView_ReqFocusCamera(30, Ta_GetUnitOwnerIDFromLstCount(command->flags, 0), 100, 180);
        } else {
            TaView_ReqStdCompleteView(30);
        }
        Ta_AllUnitFade(eInfo, Temp, ID, -1, 1, 1);
        TaEffect_LoadModule(Temp, 0x201);
        return 1;
    }

    switch (state->stage) {
    case 0:
        state->timer++;
        if (state->value > 0x30) {
            state->value -= 15;
        } else {
            state->value = 0x30;
            if (TaEffect_IsLoadModule(Temp) == 1) {
                if (state->timer >= 30) {
                    if (command->kind == 54) {
                        SzDuel_OpenMsgPopup(0, -120, 80, 0x110);
                    } else {
                        SzDuel_OpenMsgPopup(0, -120, 80, 0x111);
                    }
                    Ta_SetEffectDependOnFlagLst(eInfo, Temp, data, 0x201);
                    state->stage++;
                    state->timer = 0;
                }
            }
        }
        if (state->value < 0x30) {
            state->value = 0x30;
        }
        SzEffect_SetBlackOutForDuel((u8)state->value);
        return 1;

    case 1:
        for (i = 0; i < state->count; i++) {
            if (SzEffect_IsUse(state->ids[i]) == 1) {
                if (SzEffect_GetStatus(state->ids[i]) == 2 && (u16)state->positions[i] != 0xFFFF &&
                    SzEffect_GetStatus(state->ids[i]) == 2) {
                switch (command->kind) {
                case 54:
                    SzDuel_SetUnitKind(state->positions[i] >> 8, state->positions[i] & 0xFF, command->value);
                    break;
                case 55:
                    SzDuel_SetUnitAttr(state->positions[i] >> 8, state->positions[i] & 0xFF, command->value);
                    break;
                }
                state->positions[i] = 0xFFFF;
                }
            } else {
                count++;
            }
        }
        if (count >= state->count) {
            SzDuel_CloseMsgPopup();
            state->stage++;
            TaView_RestoreOriginalView(Temp, 0x10);
            Ta_AllUnitFade(eInfo, Temp, ID, 1, 0, 1);
        }
        return 1;

    default:
        state->value += 15;
        if (state->value > 0x80) {
            state->value = 0x80;
        }
        SzEffect_SetBlackOutForDuel((u8)state->value);
        if (state->value == 0x80 && state->timer++ > 16 && Ta_IsFinishFade() == 1) {
            if (SzDuel_GetWindowDisp() != 0) {
                SzDuel_SetWindowDraw(1);
            }
            SzDuel_CloseMsgPopup();
            return 0;
        }
        break;
    }
    return 1;
}

typedef struct Context_0026DCC0 {
    s32 unk0;
    u32 source;
    u32 destination;
    s32 mode;
} Context_0026DCC0;

typedef struct State_0026DCC0 {
    u8 pad0[4];
    u16 state;
    u8 handles[0xCE];
    u8 count;
    u8 padD5[0x2D];
    u16 timer;
} State_0026DCC0;

typedef struct Command_0026DCC0 {
    s32 command;
    u32 source;
    u32 destination;
    s32 flags;
} Command_0026DCC0;


/* Effect script 067, step `ID`: its camera, fades and effect module; it destroys units, turns cards face up. */
s32 Ta_Eff_067(void *eInfo, void *Temp, s32 ID) {
    Command_0026DCC0 storage;
    Command_0026DCC0 *command = &storage;
    Context_0026DCC0 *context = eInfo;
    State_0026DCC0 *state = Temp;
    s32 i;
    extern void SzDuel_SetUnitStatus();
    extern s32 SzDuel_GetUnitCtlRateM();
    extern s32 SzDuel_GetUnitCtlGoalM();
    extern s32 SzDuel_GetUnitCurseRest();
    extern s32 SzDuel_GetUnitSpellRest();

    storage.command = 999;
    storage.source = 0;
    storage.destination = 0;
    storage.flags = 0;
    SzDuel_SetWindowDraw(0);
    if (ID >= 0) {
        InitEffectTemp(state);
        TaEffect_LoadModule(state, 0x201);
        if (context->mode == 0) {
            Ta_AllUnitFade(context, state, ID, -1, 1, 1);
            if (Ta_GetUnitNumFrom22bitFlagList(context->destination) == 1) {
                TaView_ReqFocusCamera(30, Ta_GetUnitOwnerIDFromLstCount(context->destination, 0), 100, 180);
            } else {
                TaView_ReqStdCompleteView(30);
            }
        } else {
            TaEffect_LoadModule(state, 0x262);
            TaEffect_LoadModule(state, 0x23C);
        }
        return 1;
    }

    switch (state->state) {
    case 0:
        if (TaEffect_IsLoadModule(state) == 1) {
            if (context->mode == 0) {
                if (state->timer++ >= 30) {
                    SzDuel_OpenMsgPopup(0, -120, 80, 0x113);
                    Ta_SetEffectDependOnFlagLst(context, state, command, 0x201);
                    state->state++;
                }
            } else {
                command->command = 0x201;
                command->source = 0;
                command->destination = context->source;
                command->flags = 0;
                state->handles[state->count] = Ta_Do_Effect(command, state);
                state->count++;
                state->state++;
            }
        }
        break;
    case 1:
        for (i = 0; i < state->count; i++) {
            if (SzEffect_IsUse(state->handles[i]) != 0) {
                return 1;
            }
        }
        if (context->mode == 1) {
            s32 value = SzDuel_GetUnitCtlRateM(context->source >> 8, context->source & 0xFF);
            if (value != SzDuel_GetUnitCtlGoalM(context->source >> 8, context->source & 0xFF)) {
                return 1;
            }
            SzDuel_OpenMsgPopup(0, -120, 80, 0x112);
            command->command = 0x262;
            command->source = context->source;
            command->destination = context->destination;
            command->flags = 0;
            state->handles[state->count] = Ta_Do_Effect(command, state);
            state->count++;
            state->state++;
            return 1;
        }
        state->state = 4;
        state->timer = 0;
        SzDuel_CloseMsgPopup();
        TaView_RestoreOriginalView(state, 16);
        Ta_AllUnitFade(context, state, ID, 1, 0, 1);
        break;
    case 2:
        if (SzEffect_IsUse(state->handles[state->count - 1]) == 1) {
            return 1;
        }
        SzEffect_SetBusyFlag2(context->source, 0);
        Ta_UnitFade(context->source >> 8, context->source & 0xFF, -1, 1, 1);
        SzDuel_SetUnitCtlGoalC(context->source >> 8, context->source & 0xFF, 0);
        SzDuel_SetUnitCtlRateC(context->source >> 8, context->source & 0xFF, -1, 0);
        Ta_UnitFade(context->source >> 8, context->source & 0xFF, -1, 1, 1);
        state->state++;
        break;
    case 3:
        if (Ta_IsFinishFade() != 1) {
            return 1;
        }
        SzDuel_DelUnit(context->source >> 8, context->source & 0xFF);
        if (SzDuel_GetUnitStatus(context->destination >> 8, context->destination & 0xFF, 1) != 0) {
            SzDuel_SetUnitStatus(context->destination >> 8, context->destination & 0xFF, 1, 0);
        } else {
            SzDuel_SetUnitStatus(context->destination >> 8, context->destination & 0xFF, 1, 1);
        }
        if (SzDuel_GetUnitCurseRest(context->destination >> 8, context->destination & 0xFF) == 0) {
            if (SzDuel_GetUnitSpellRest(context->destination >> 8, context->destination & 0xFF) == 0) {
                SzDuel_SetUnitStatus(context->destination >> 8, context->destination & 0xFF, 0, 0);
            }
        }
        state->timer = 0;
        TaView_RestoreOriginalView(state, 16);
        SzDuel_CloseMsgPopup();
        state->state++;
        break;
    default:
        if (state->timer++ > 16 && Ta_IsFinishFade() == 1) {
            if (SzDuel_GetWindowDisp() != 0) {
                SzDuel_SetWindowDraw(1);
            }
            SzDuel_CloseMsgPopup();
            return 0;
        }
        break;
    }
    return 1;
}


typedef struct Context_0026E1F0 {
    u32 unk0;
    u32 source;
    u32 target;
    s32 cleanup_source;
} Context_0026E1F0;

typedef struct State_0026E1F0 {
    u8 unk0[4];
    u16 step;
    u8 handles[0x1A];
    s32 flags[0x2D];
    u8 count;
    u8 unkD5[0x2D];
    u16 timer;
} State_0026E1F0;

/* Effect script 051, step `ID`: its camera, fades and effect module; it destroys units, turns cards face up. */
s32 Ta_Eff_051(void *eInfo, void *Temp, s32 ID) {
    s32 completed;
    s32 command[4];
    s32 *request = command;
    s32 i;
    Context_0026E1F0 *context = eInfo;
    State_0026E1F0 *state = Temp;
    extern s32 SzDuel_GetUnitCardNo();

    command[0] = 999;
    command[1] = 0;
    command[2] = 0;
    command[3] = 0;
    completed = 0;
    SzDuel_SetWindowDraw(0);
    if (ID >= 0) {
        InitEffectTemp(state);
        TaView_ReqFocusCamera(0, context->source, 180, 180);
        TaEffect_LoadModule(state, 0x25A);
        TaEffect_LoadModule(state, 0x33);
        return 1;
    }

    switch (state->step) {
    case 0:
        if (TaEffect_IsLoadModule(state) == 1) {
            SzDuel_OpenMsgPopup(0, -120, 80, 0x103);
            request[0] = 0x25A;
            request[1] = 0;
            request[2] = context->source;
            request[3] = 0;
            state->handles[state->count] = Ta_Do_Effect(request, state);
            state->flags[state->count] = 0;
            state->count++;
            state->step++;
        }
        break;
    case 1:
        if (SzEffect_IsUse(state->handles[0]) == 0) {
            SzDuel_SetUnitStatus(context->source >> 8, context->source & 0xFF, 0, 1);
            SzDuel_OpenMsgPopup(0, -120, 80,
                SzDuel_GetMsgName(SzDuel_GetUnitCardNo(context->source >> 8, context->source & 0xFF)));
            request[0] = 0x33;
            request[1] = 0;
            request[2] = context->source;
            request[3] = 0;
            state->handles[state->count] = Ta_Do_Effect(request, state);
            state->flags[state->count] = 0;
            state->count++;
            state->step++;
        }
        break;
    case 2:
        if (SzEffect_IsUse(state->handles[state->count - 1]) != 0) {
            if (SzEffect_GetStatus(state->handles[state->count - 1]) == 2 &&
                state->flags[state->count - 1] == 0) {
                TaView_ReqFocusCamera(0, context->target, 100, 180);
                request[0] = 0x33;
                request[1] = 0;
                request[2] = context->target;
                request[3] = 0;
                state->handles[state->count] = Ta_Do_Effect(request, state);
                state->flags[state->count] = 0;
                state->flags[state->count - 1] = 1;
                state->step++;
                state->count++;
            }
        }
        return 1;
    case 3:
        TaView_ReqFocusCamera(16, context->target, 300, 300);
        state->step++;
        break;
    case 4:
        for (i = 0; i < state->count; i++) {
            if (SzEffect_IsUse(state->handles[i]) == 0) {
                completed++;
            }
        }
        if (completed >= state->count) {
            if (context->cleanup_source == 1) {
                Ta_DelUnit(context->source >> 8, context->source & 0xFF);
            }
            Ta_DelUnit(context->target >> 8, context->target & 0xFF);
            SzDuel_CloseMsgPopup();
            TaView_RestoreOriginalView(state, 16);
            state->step++;
            break;
        }
        return 1;
    default:
        if (state->timer++ > 16) {
            if (SzDuel_GetWindowDisp() != 0) {
                SzDuel_SetWindowDraw(1);
            }
            SzDuel_CloseMsgPopup();
            return 0;
        }
        break;
    }
    return 1;
}

/* Whether stacking unit (nSide1, nID1) onto unit (nSide0, nID0) from the hand works (fusion or equip), into
   `eInfo`. */
s32 Ta_IsHandHeap(s32 nSide0, s32 nID0, s32 nSide1, s32 nID1, s32 *eInfo) {
    extern s32 func_001E1030();
    s32 cNo1;
    s32 cNo2;
    u8 *pInfo1;
    u8 *pInfo2;
    s32 kind1;
    s32 Ret;

    cNo1 = func_001E1030(nSide0, nID0);
    cNo2 = func_001E1030(nSide1, nID1);
    pInfo1 = func_001DD0E0(cNo1);
    pInfo2 = func_001DD0E0(cNo2);
    if ((pInfo1 == NULL) || (pInfo2 == NULL)) {
        return -1;
    }
    kind1 = (s32) *pInfo1 >> 5;
    if ((kind1 == 0) && (((s32) *pInfo2 >> 5) == 0)) {
        Ret = func_002495A0(cNo1, cNo2);
        if (Ret == 999) {
            eInfo[0] = 2;
            eInfo[1] = (nSide0 << 8) | nID0;
            eInfo[2] = (nSide0 << 8) | nID1;
            eInfo[3] = 0;
            return -1;
        }
        eInfo[0] = 0;
        eInfo[1] = (nSide0 << 8) | nID0;
        eInfo[2] = (nSide0 << 8) | nID1;
        eInfo[3] = Ret;
        return 0;
    }
    if (kind1 == 0) {
        switch ((s32) *pInfo2 >> 5) {
        case 2:
            Ret = func_00248FD0(nSide0, nID0, cNo2);
            if (Ret < 0) {
                eInfo[0] = 2;
                eInfo[1] = (nSide0 << 8) | nID0;
                eInfo[2] = (nSide0 << 8) | nID1;
                eInfo[3] = 0;
                return -1;
            }
            if ((Ret >> 16) == 0) {
                eInfo[0] = 0;
                eInfo[1] = (nSide0 << 8) | nID0;
                eInfo[2] = (nSide0 << 8) | nID1;
                eInfo[3] = Ret & 0xFFFF;
                return 0;
            }
            eInfo[0] = 1;
            eInfo[1] = (((nSide0 << 8) | nID0) << 16) | ((nSide0 << 8) | nID1);
            eInfo[2] = func_001DE540();
            eInfo[3] = cNo2;
            return 1;
        default:
            eInfo[0] = 2;
            eInfo[1] = (nSide0 << 8) | nID0;
            eInfo[2] = (nSide0 << 8) | nID1;
            eInfo[3] = 0;
            return -1;
        }
    }
    if (kind1 == 2) {
        switch ((s32) *pInfo2 >> 5) {
        case 0:
            Ret = func_00248FD0(nSide1, nID1, cNo1);
            if (Ret < 0) {
                eInfo[0] = 2;
                eInfo[1] = (nSide0 << 8) | nID0;
                eInfo[2] = (nSide0 << 8) | nID1;
                eInfo[3] = 0;
                return -1;
            }
            if ((Ret >> 16) == 0) {
                eInfo[0] = 0;
                eInfo[1] = (nSide0 << 8) | nID0;
                eInfo[2] = (nSide0 << 8) | nID1;
                eInfo[3] = Ret & 0xFFFF;
                return 0;
            }
            eInfo[0] = 1;
            eInfo[1] = (((nSide0 << 8) | nID0) << 16) | ((nSide0 << 8) | nID1);
            eInfo[2] = func_001DE540();
            eInfo[3] = cNo1;
            return 0x10001;
        default:
            eInfo[0] = 2;
            eInfo[1] = (nSide0 << 8) | nID0;
            eInfo[2] = (nSide0 << 8) | nID1;
            eInfo[3] = 0;
            return -1;
        }
    }
    eInfo[0] = 2;
    eInfo[1] = (nSide0 << 8) | nID0;
    eInfo[2] = (nSide0 << 8) | nID1;
    eInfo[3] = 0;
    return -1;
}

/* The summon cost of the turn owner's hand cards. */
s32 Ta_GetSummonCost(void) {
    s32 i;
    s32 turnOwner;
    s32 handCount;
    s32 var_s3;
    s32 cardNo;
    s32 cardSummonCost;

    turnOwner = SzDuel_GetTurnOwner();
    handCount = SzDuel_GetHandCount(turnOwner);
    var_s3 = 0;
    for (i = 0; i < handCount; i++) {
            cardNo = SzDuel_InqHand(turnOwner, i);
            if (((s32) (cardNo & 0xF000) >> 0xC) > 0) {
                cardSummonCost = TaHand_GetCardSummonCost(cardNo, turnOwner);
                if (var_s3 < cardSummonCost) {
                    var_s3 = cardSummonCost;
                }
            }
    }
    return var_s3;
}

/* Runs the hand-combination animation (fusion, equip or failure). */
s32 Ta_ManageHandEffect(s32 *arg0) {
    extern s32 Ta_Eff_Hand_Fusion();
    extern s32 Ta_Eff_Hand_Enc();
    extern s32 Ta_Eff_Hand_Fail();
    s32 temp_v1;

    temp_v1 = *arg0;
    switch (temp_v1) {
    case 0:
        return Ta_Eff_Hand_Fusion();
    case 1:
        return Ta_Eff_Hand_Enc();
    case 2:
        return Ta_Eff_Hand_Fail();
    default:
        return 0;
    }
}

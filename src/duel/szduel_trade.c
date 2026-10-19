/* The duel screen, part 4 of 12: card trading. */

#include "common.h"

extern u8 gSzDuel_NameIndex0[];
extern u8 gSzDuel_NameIndex1[];
#pragma opt_propagation off

/* Opens the card trade screen: empties both sides' lists and fills them from the trunks. */
void SzDuel_InitTrade(void) {
    u8 *state;
    s16 *bag0;
    s16 *bag1;
    s8 *picked0;
    s8 *picked1;
    s32 i;
    s32 result;
    u8 *names;

    state = duelState.b;
    /* the card lists live in the campaign work area, borrowed as scratch */
    bag0 = (s16 *)CAMPAIGN_WORK_ADDR;
    bag1 = (s16 *)(CAMPAIGN_WORK_ADDR + 0x6AC);
    picked0 = (s8 *)(CAMPAIGN_WORK_ADDR + 0xD58);
    picked1 = (s8 *)(CAMPAIGN_WORK_ADDR + 0x10AE);
    result = SzData_GetOption(0, 0);
    duelState.s.depth = 0xFFFFF8;
    if (result != 0) {
        names = gSzDuel_NameIndex1;
    } else {
        names = gSzDuel_NameIndex0;
    }
    *(u8 **)(state + 0x6D4) = names;
    *(s32 *)(state + 0x6D8) = CAMPAIGN_WORK_ADDR;
    *(s32 *)(state + 0x6DC) = CAMPAIGN_WORK_ADDR + 0x6AC;
    *(s32 *)(state + 0x6E0) = CAMPAIGN_WORK_ADDR + 0xD58;
    *(s32 *)(state + 0x6E4) = (s32)picked1;
    i = 0;
    do {
        i += 1;
        *bag0 = 0x3E7;
        *picked0 = 0;
        bag0 += 1;
        picked0 += 1;
    } while (i < 0x356);
    i = 0;
    do {
        i += 1;
        *bag1 = 0x3E7;
        *picked1 = 0;
        bag1 += 1;
        picked1 += 1;
    } while (i < 0x356);
    *(s16 *)(state + 0xC92) = 0;
    *(s16 *)(state + 0xC94) = 0;
    *(s8 *)(state + 0xCB6) = 0;
    *(s8 *)(state + 0xCB7) = 4;
    *(s8 *)(state + 0xCB8) = 0xA;
    *(s8 *)(state + 0xCB9) = 0;
    *(s8 *)(state + 0xCBA) = 4;
    *(s8 *)(state + 0xCBB) = 0xA;
    *(s8 *)(state + 0xCBE) = 1;
    *(s8 *)(state + 0xCBF) = 1;
    *(s8 *)(state + 0xCC0) = 0;
    *(s8 *)(state + 0xCC1) = 0;
    *(s8 *)(state + 0xD5E) = 0;
    *(s8 *)(state + 0xD5F) = 0;
    *(s16 *)(state + 0xC8A) = 0;
    *(s16 *)(state + 0xC8E) = 0;
    *(s16 *)(state + 0xC96) = 0;
    *(s16 *)(state + 0xC98) = 0;
    *(s8 *)(state + 0xCBC) = 0;
    *(s8 *)(state + 0xCBD) = 0;
    lSzDuel_SetupTrade(0);
    lSzDuel_SetupTrade(1);
}
#pragma opt_propagation reset

/* Fills side `side`'s trade list from its trunk and sorts it. */
void lSzDuel_SetupTrade(s32 side) {
    extern s32 SzData_GetBagCount();
    u8 *base;
    s16 *var_s0;
    u8 *var_a0;
    u8 *var_a1;
    s32 i;
    s32 j;
    s32 k;
    s32 var_v0;
    u16 temp_a0;
    u16 *var_s2;
    u16 *var_s3;
    u8 *var_s4;
    u8 temp_v1;

    base = duelState.b;
    if (side != 0) {
        var_s2 = (u16 *)(base + 0xC8E);
    } else {
        var_s2 = (u16 *)(base + 0xC8A);
    }
    if (side != 0) {
        var_s3 = (u16 *)(base + 0xC90);
    } else {
        var_s3 = (u16 *)(base + 0xC8C);
    }
    if (side != 0) {
        var_s0 = *(s16 **)(base + 0x6DC);
    } else {
        var_s0 = *(s16 **)(base + 0x6D8);
    }
    if (side != 0) {
        var_a0 = *(u8 **)(base + 0x6E4);
    } else {
        var_a0 = *(u8 **)(base + 0x6E0);
    }
    if (side != 0) {
        var_a1 = *(u8 **)(base + 0x6E0);
    } else {
        var_a1 = *(u8 **)(base + 0x6E4);
    }
    if (side != 0) {
        var_s4 = base + 0xD5F;
    } else {
        var_s4 = base + 0xD5E;
    }
    *var_s3 = 0;
    temp_v1 = *(u8 *)(side + (s32)base + 0xCC0);
    if (temp_v1 != 2) {
        switch (temp_v1) {
            case 0:
                k = 0;
                do {
                    if (SzData_GetBagCount(side, k, 3) > 0) {
                        *var_s0 = k;
                        *var_s3 = (u16)(*var_s3 + 1);
                    } else {
                        *var_s0 = 0x3E7;
                    }
                    k += 1;
                    var_s0 += 1;
                } while (k < 0x356);
                break;
            case 1:
                j = 0;
                do {
                    if ((s32)*var_a0 > 0) {
                        *var_s0 = j;
                        *var_s3 = (u16)(*var_s3 + 1);
                    } else {
                        *var_s0 = 0x3E7;
                    }
                    j += 1;
                    var_s0 += 1;
                    var_a0 += 1;
                } while (j < 0x356);
                break;
        }
    } else {
        i = 0;
        do {
            if ((s32)*var_a1 > 0) {
                *var_s0 = i;
                *var_s3 = (u16)(*var_s3 + 1);
            } else {
                *var_s0 = 0x3E7;
            }
            i += 1;
            var_s0 += 1;
            var_a1 += 1;
        } while (i < 0x356);
    }
    temp_a0 = *var_s3;
    if ((s32)temp_a0 < (*var_s2 + *var_s4)) {
        var_v0 = temp_a0 - 5;
        *var_s2 = (u16)(var_v0 > 0 ? var_v0 : 0);
    }
    lSzDuel_SortTrade(side);
}

/* Ends the card trade screen (nothing to do). */
void SzDuel_TermTrade(void) {

}

typedef struct {
    s8 axis_0 : 2;
    s8 axis_1 : 2;
    s8 unused : 4;
} MoveFlags_001C2540;

/* Runs one frame of the card trade screen: scrolls the two lists' highlights, then each side's controls. */
void SzDuel_ActTrade(void) {
    extern s32 SzGame_ActMemCardProc(u8 *, u8 *);
    extern s32 lSzDuel_ActTradeProc(s32);
    extern u16 D_00318118;
    extern u8 D_003181F3;
    extern MoveFlags_001C2540 D_003181F4;
    u8 *state = duelState.b;
    u8 *state2;
    s32 step;
    s32 clamped;
    s32 wave2;
    s32 var_v0_3;
    s32 wave1;

    if (D_003181F3 != 0) {
        ((MoveFlags_001C2540 *)(state + 0xD64))->axis_0 = 1;
    }
    wave1 = (s32)((MoveFlags_001C2540 *)(state + 0xD64))->axis_0 << 9;
    clamped = *(u16 *)(state + 0xC86);
    wave1 = clamped + wave1;
    clamped = wave1 > 0 ? wave1 : 0;
    if (clamped < 0x8000) {
        wave1 = wave1 > 0 ? wave1 : 0;
    } else {
        wave1 = 0x8000;
    }
    *(u16 *)(state + 0xC86) = (u16)wave1;
    if ((*(u16 *)(state + 0xC86) == 0) || ((s32)*(u16 *)(state + 0xC86) >= 0x8000)) {
        ((MoveFlags_001C2540 *)(state + 0xD64))->axis_0 = -((MoveFlags_001C2540 *)(state + 0xD64))->axis_0;
    }
    state2 = duelState.b;
    step = (s32)D_003181F4.axis_1 << 0xB;
    wave2 = D_00318118 + step;
    if (wave2 > 0) {
        wave2 = *(u16 *)(state2 + 0xC88) + step;
    } else {
        wave2 = 0;
    }
    if (wave2 < 0x8000) {
        wave2 = *(u16 *)(state2 + 0xC88) + step;
        wave2 = wave2 > 0 ? wave2 : 0;
    } else {
        wave2 = 0x8000;
    }
    *(u16 *)(state2 + 0xC88) = (u16)wave2;
    if ((*(u16 *)(state2 + 0xC88) == 0) || ((s32)*(u16 *)(state2 + 0xC88) >= 0x8000)) {
        ((MoveFlags_001C2540 *)(state2 + 0xD64))->axis_1 = -((MoveFlags_001C2540 *)(state2 + 0xD64))->axis_1;
    }
    if ((SzGame_ActMemCardProc(state2, state) < 0) && (lSzDuel_ActTradeProc(0) == 0)) {
        lSzDuel_ActTradeProc(1);
    }
}

/* How many cards side `player` has put up for trade. */
static inline s32 count_001C2720(s32 player) {
    u8 *q;
    s32 sum;
    u8 *b = duelState.b;
    s32 i;

    if (player) {
        q = *(u8 **)(b + 0x6E4);
    } else {
        q = *(u8 **)(b + 0x6E0);
    }
    sum = 0;
    for (i = 0; i < 0x356; i++) {
        sum += *q++;
    }
    return sum;
}

/* Runs side `player`'s trade controls: moving through the list, picking cards and amounts, sorting, trading,
   leaving. */
s32 lSzDuel_ActTradeProc(s32 player) {
    u8 *base;
    s32 limit;
    s32 id;
    s32 old;
    s32 oldCursor;
    u16 *list;
    s32 fast;
    s32 delta;
    u16 *timer;
    u8 *counts;
    u16 *scroll;
    u8 *p;
    s32 before;
    u8 *slot;
    u8 *cursor;
    u8 *digits;
    u8 *state;
    u16 *total;

    base = duelState.b;
    if (player) {
        list = *(u16 **)(base + 0x6DC);
    } else {
        list = *(u16 **)(base + 0x6D8);
    }
    if (player) {
        counts = *(u8 **)(base + 0x6E4);
    } else {
        counts = *(u8 **)(base + 0x6E0);
    }
    if (player) {
        digits = base + 0xCB9;
    } else {
        digits = base + 0xCB6;
    }
    if (player) {
        timer = (u16 *)(base + 0xC98);
    } else {
        timer = (u16 *)(base + 0xC96);
    }
    if (player) {
        scroll = (u16 *)(base + 0xC8E);
    } else {
        scroll = (u16 *)(base + 0xC8A);
    }
    if (player) {
        total = (u16 *)(base + 0xC90);
    } else {
        total = (u16 *)(base + 0xC8C);
    }
    if (player) {
        cursor = base + 0xD5F;
    } else {
        cursor = base + 0xD5E;
    }
    state = (u8 *)(player + (s32)base) + 0xCBE;
    if (*state < 4) {
        if (SzPad_Check(player, 1, 0xFFFF)) {
            *timer = 0x5A;
        } else if (*timer != 0) {
            (*timer)--;
        }
    }
    switch (*state) {
    case 0: {
        s16 *slide = (s16 *)((player << 1) + (s32)base + 0xC92);
        *slide = (*slide - 0x2D > 0) ? *slide - 0x2D : 0;
        if (*slide <= 0) {
            *state = 1;
        }
        break;
    }
    case 1:
        id = list[*scroll + *cursor];
        fast = SzPad_Check(player, 1, 0x100) ? 1 : 0;
        oldCursor = *cursor;
        delta = 0;
        if (*total != 0) {
            if (SzPad_Check(player, 2, 0xC)) {
                if (SzPad_Check(player, 2, 4)) {
                    delta = -5;
                } else {
                    delta = 5;
                }
            } else if (SzPad_Check(player, 2, 0x5000)) {
                if (SzPad_Check(player, 2, 0x1000)) {
                    if (*cursor > 0) {
                        (*cursor)--;
                    } else {
                        delta = -1;
                    }
                } else if (*cursor < 4) {
                    (*cursor)++;
                } else {
                    delta = 1;
                }
            }
            if (*cursor != oldCursor) {
                SzSound_PlaySE(0, 3);
                break;
            }
            if (delta == 0 && SzPad_IsAnalog(player)) {
                s32 stick = SzPad_GetAnalogInfo(player, 3) - 0x80;
                s32 size;
                if (stick >= 0) {
                    size = stick;
                } else {
                    size = -stick;
                }
                if (size > 0x30) {
                    if (stick > 0) {
                        stick -= 0x30;
                    } else {
                        stick += 0x30;
                    }
                    delta = (stick * 15) >> 7;
                }
            }
            if (delta != 0) {
                s32 max;
                s32 next;
                u16 prev;
                if (*total - 5 > 0) {
                    max = *total - 5;
                } else {
                    max = 0;
                }
                prev = *scroll;
                next = prev + delta;
                next = ((next > 0 ? next : 0) < max) ? (next > 0 ? next : 0) : max;
                *scroll = next;
                if (*scroll != prev) {
                    SzSound_PlaySE(0, 3);
                }
                *timer = 0x5A;
                break;
            }
            if (SzPad_Check(player, 2, 0xC0)) {
                if (id == 999 || base[player + 0xCC0] == 2) {
                    SzSound_PlaySE(0, 6);
                    break;
                }
                limit = SzData_GetBagCount(player, id, 3);
                slot = counts + id;
                before = *slot;
                if (SzPad_Check(player, 2, (u16)(player ? 0x80 : 0x40))) {
                    if (*slot < limit) {
                        (*slot)++;
                    }
                } else if (*slot > 0) {
                    (*slot)--;
                }
                if (before == *slot) {
                    SzSound_PlaySE(0, 6);
                    break;
                }
                SzSound_PlaySE(0, 3);
                break;
            }
            if (SzPad_Check(player, 0, 0x10)) {
                if (id == 999) {
                    SzSound_PlaySE(0, 6);
                    break;
                }
                *state = 2;
                SzSound_PlaySE(0, 0x10);
                break;
            }
        }
        if (SzPad_Check(player, 0, 0x600)) {
            if (SzPad_Check(player, 0, 0x200)) {
                base[player + 0xCC0] = (base[player + 0xCC0] + 2) % 3;
            } else {
                base[player + 0xCC0] = (base[player + 0xCC0] + 4) % 3;
            }
            lSzDuel_SetupTrade(player);
            *scroll = 0;
            SzSound_PlaySE(0, 0x13);
            break;
        }
        if (SzPad_Check(player, 0, 0x800)) {
            if (base[(player ^ 1) + 0xCBE] == 4) {
                if (count_001C2720(player) > 0 || count_001C2720(player ^ 1) > 0) {
                    SzSound_PlaySE(0, 4);
                    base[0xCBE] = 6;
                    base[0xCBF] = 6;
                    base[0xD36] = 0;
                    break;
                }
                SzSound_PlaySE(0, 6);
                break;
            }
            SzSound_PlaySE(0, 4);
            *state = 4;
            break;
        }
        if (SzPad_Check(player, 2, 3)) {
            p = digits + fast;
            old = *p;
            if (SzPad_Check(player, 2, 1)) {
                *p = (*p + 9) % 10;
            } else {
                *p = (*p + 11) % 10;
            }
            if (old != *p) {
                lSzDuel_SortTrade(player);
                SzSound_PlaySE(0, 0x13);
            }
            break;
        }
        if (SzPad_Check(player, 0, 0x20)) {
            if (base[(player ^ 1) + 0xCBE] == 1) {
                SzSound_PlaySE(0, 5);
                base[0xCBE] = 5;
                base[0xCBF] = 5;
                base[0xD36] = 0;
            } else {
                SzSound_PlaySE(0, 6);
            }
        }
        break;
    case 2: {
        s16 *slide = (s16 *)((player << 1) + (s32)base + 0xC92);
        *slide = (*slide + 0x2D < 0x140) ? *slide + 0x2D : 0x140;
        if (*slide >= 0x140) {
            *state = 3;
        }
        break;
    }
    case 3:
        if (SzPad_Check(player, 2, 0x5000)) {
            p = (u8 *)(player + (u32)base) + 0xCBC;
            before = *p;
            if (SzPad_Check(player, 2, 0x1000)) {
                *p = (*p + 3) % 4;
            } else {
                *p = (*p + 5) % 4;
            }
            if (*p != before) {
                SzSound_PlaySE(0, 0x13);
            }
            break;
        }
        if (SzPad_Check(player, 0, 0x30)) {
            *state = 0;
            SzSound_PlaySE(0, 0x11);
        }
        break;
    case 4:
        if (SzPad_Check(player, 0, 0x20)) {
            SzSound_PlaySE(0, 5);
            *state = 1;
        }
        break;
    case 5:
        if (SzPad_Check(player, 0, 0xA000)) {
            old = base[0xD36];
            if (SzPad_Check(player, 0, 0x8000)) {
                base[0xD36] = 1;
            } else {
                base[0xD36] = 0;
            }
            if (base[0xD36] != old) {
                SzSound_PlaySE(0, 3);
            }
            break;
        }
        if (SzPad_Check(player, 0, 0xC0)) {
            SzSound_PlaySE(0, 4);
            if (base[0xD36] != 0) {
                SzGame_Pop();
                break;
            }
            base[0xCBE] = 1;
            base[0xCBF] = 1;
            break;
        }
        if (SzPad_Check(player, 0, 0x20)) {
            SzSound_PlaySE(0, 5);
            base[0xCBE] = 1;
            base[0xCBF] = 1;
        }
        break;
    case 6:
        if (SzPad_Check(player, 0, 0xA000)) {
            old = base[0xD36];
            if (SzPad_Check(player, 0, 0x8000)) {
                base[0xD36] = 1;
            } else {
                base[0xD36] = 0;
            }
            if (base[0xD36] != old) {
                SzSound_PlaySE(0, 3);
            }
            break;
        }
        if (SzPad_Check(player, 0, 0xC0)) {
            SzSound_PlaySE(0, 4);
            if (base[0xD36] != 0) {
                if (lSzDuel_TradeDo() > 0) {
                    base[0xCBE] = 8;
                    base[0xCBF] = 8;
                    break;
                }
                base[0xCBE] = 7;
                base[0xCBF] = 7;
                SzGame_InitMemCardProc(5);
                return 1;
            }
            *state = 1;
            base[(player ^ 1) + 0xCBE] = 4;
            break;
        }
        if (SzPad_Check(player, 0, 0x20)) {
            SzSound_PlaySE(0, 5);
            *state = 1;
            base[(player ^ 1) + 0xCBE] = 4;
        }
        break;
    case 7:
        SzGame_Pop();
        break;
    case 8:
        if (SzPad_Check(player, 0, 0xF0)) {
            SzSound_PlaySE(0, 4);
            SzGame_Pop();
        }
        break;
    }
    return 0;
}

typedef struct {
    u8 padding[0x6E0];
    u8 *first;
    u8 *second;
} State_001C32B0;

/* Trades the picked cards: what both sides offered of the same card cancels out; returns how many cards change
   hands. */
s32 lSzDuel_TradeDo(void) {
    State_001C32B0 *state = (State_001C32B0 *)duelState.b;
    s32 total;
    s32 i;
    s32 card;
    u8 *offer0;
    u8 *offer1;
    u8 count1;
    u8 count0;

    total = 0;
    card = 0;
    do {
        offer0 = state->first + card;
        count0 = *offer0;
        if (count0 != 0) {
            offer1 = state->second + card;
            count1 = *offer1;
            if (count1 != 0) {
                if ((count0 & 0xFF) > (count1 & 0xFF)) {
                    *offer0 = count0 - count1;
                    state->second[card] = 0;
                } else {
                    *offer1 = count1 - count0;
                    state->first[card] = 0;
                }
            }
        }
        card += 1;
    } while (card < 0x356);
    lSzDuel_TradeDoSide(0);
    lSzDuel_TradeDoSide(1);
    for (i = 0; i < 0x356; i++) {
        total += state->first[i];
        total += state->second[i];
    }
    return total;
}

typedef struct {
    u32 id : 31;
    u32 flag : 1;
    u32 position : 30;
    u32 state : 2;
} Entry_001C33A0;

typedef struct {
    u8 padding[0x6E0];
    u8 *counts0;
    u8 *counts1;
} State_001C33A0;

/* Moves the cards side `player` receives into its trunk and takes away those it gives. */
void lSzDuel_TradeDoSide(s32 player) {
    s32 id;
    s32 slot;
    Entry_001C33A0 *entry;
    u8 *counts;
    u8 *count;
    s32 opponent;
    State_001C33A0 *state;

    state = (State_001C33A0 *)duelState.b;
    if (player != 0) {
        counts = state->counts1;
    } else {
        counts = state->counts0;
    }
    id = 0;
    opponent = player ^ 1;
    do {
        count = counts + id;
        while (*count != 0) {
            if (SzData_GetBagCount(opponent, id, -1) >= 9) {
                break;
            }
            slot = 0;
            do {
                entry = SzData_GetCardInfo(player, id, slot);
                if (entry->id != 0 && entry->state == 3 &&
                    SzData_CheckDup(opponent, entry->id, entry->position, id) == 0) {
                    break;
                }
                slot++;
            } while (slot < 9);
            if (slot >= 9) {
                break;
            }
            SzData_AddBag2(opponent, entry->id, entry->position, id);
            SzData_ClearCardInfo(entry);
            (*count)--;
        }
        id++;
    } while (id < 0x356);
}

typedef struct {
    u8 pad_000[0x6D8];
    s32 values[2];
    u8 pad_6E0[0x67C];
    s8 selection;
} State_001C3520;

/* Sorts side `side`'s trade list by its chosen sort keys. */
void lSzDuel_SortTrade(s32 side) {
    State_001C3520 *state = (State_001C3520 *)duelState.b;
    s32 list;
    void (*compare)(void);

    if (side != 0) {
        list = state->values[1];
    } else {
        list = state->values[0];
    }
    if (side != 0) {
        compare = lSzDuel_SortFunc2;
    } else {
        compare = lSzDuel_SortFunc1;
    }
    state->selection = side;
    func_00199BC0(list, 0x356, 2, compare);
}

/* Draws the card trade screen. */
void SzDuel_DrawTrade(void) {
    RhBase_SetVifPacketArea(SzDuel_DrawTrade_Pipe(RhBase_GetVifPacketArea()));
}

typedef struct State_001C35A0 {
    u8 pad0[0x6D8];
    u16 *values0;
    u16 *values1;
    u8 pad1[0x5AA];
    u16 index0;
    u16 condition0;
    u16 index1;
    u16 condition1;
    s16 amount0;
    s16 amount1;
    u8 pad2[0x28];
    u8 mode0;
    u8 mode1;
    u8 pad3[0x9C];
    u8 side;
    u8 pad4;
    u8 selection0;
    u8 selection1;
} State_001C35A0;

extern u16 D_0031811C;

/* Draws the card trade screen: background, title, both lists, cursors, the card detail and the dialogs over them. */
s32 SzDuel_DrawTrade_Pipe(s32 packet) {
    State_001C35A0 *state = (State_001C35A0 *)duelState.b;
    s32 result;
    s32 next;
    extern s32 lSzDuel_DrawTrade_Title_Pipe();
    extern s32 lSzDuel_Draw_Fade_Pipe();
    extern s32 lSzDuel_DrawTrade_Exit_Pipe();
    extern s32 lSzDuel_DrawTrade_Do_Pipe();
    extern s32 lSzDuel_DrawTrade_Notice_Pipe();

    next = lSzDuel_DrawTrade_Title_Pipe(lSzDuel_DrawTrade_Base_Pipe(SzDuel_StartWindowSessionWithPalette_Pipe(packet, 2)), 0, 0);
    next = lSzDuel_DrawTrade_Bag_Pipe(next, 0, 0, 0);
    if (D_0031811C != 0) {
        next = lSzDuel_DrawTrade_Cursor_Pipe(next, 0, 0, 0, state->selection0);
    }
    if (state->amount0 != 0) {
        next = lSzDuel_Draw_Fade_Pipe(next, 0, 0, 320, 448,
                            (u8)(((s16)state->amount0 << 6) / 320));
        state->side = 0;
        next = func_001BDAF0(next, state->values0[state->index0 + state->selection0],
                            state->amount0, 0, 0, 1, 1, 0);
    }
    if (!(state->mode0 != 4 && state->mode0 != 6 && state->mode0 != 7)) {
        next = lSzDuel_Draw_Fade_Pipe(next, 0, 0, 320, 448, 64);
        next = lSzDuel_DrawTrade_Ready_Pipe(next, -160, 0);
    }
    result = lSzDuel_DrawTrade_Bag_Pipe(next, 1, 0, 0);
    if (state->condition1 != 0) {
        result = lSzDuel_DrawTrade_Cursor_Pipe(result, 1, 0, 0, state->selection1);
    }
    if (state->amount1 != 0) {
        result = lSzDuel_Draw_Fade_Pipe(result, 320, 0, 320, 448,
                              (u8)(((s16)state->amount1 << 6) / 320));
        state->side = 1;
        result = func_001BDAF0(result, state->values1[state->index1 + state->selection1],
                              -state->amount1, 0, 1, 1, 1, 0);
    }
    if (!(state->mode1 != 4 && state->mode1 != 6 && state->mode1 != 7)) {
        result = lSzDuel_Draw_Fade_Pipe(result, 320, 0, 320, 448, 64);
        result = lSzDuel_DrawTrade_Ready_Pipe(result, 160, 0);
    }
    if (state->mode0 == 5 || state->mode1 == 5) {
        result = lSzDuel_DrawTrade_Exit_Pipe(result, 0, 0);
    }
    if (state->mode0 == 6 || state->mode1 == 6) {
        result = lSzDuel_DrawTrade_Do_Pipe(result, 0, 0);
    }
    if (state->mode0 == 8 || state->mode1 == 8) {
        result = lSzDuel_DrawTrade_Notice_Pipe(result, 0, 0);
    }
    SzMsg_Free(0);
    return result;
}

typedef struct {
    u16 count;
    u16 flags;
    u32 padding;
    u64 registers;
} Tag_001C38E0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Color_001C38E0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Vertex_001C38E0;

typedef struct {
    Color_001C38E0 color;
    Vertex_001C38E0 xyz;
} Point_001C38E0;

typedef struct {
    u64 tag[2];
    Point_001C38E0 points[4];
    u64 end;
} Packet_001C38E0;

typedef struct {
    u8 b, g, r, a;
} Source_001C38E0;

/* Sets two vertex colours from `src`. */
static inline void set_color_001C38E0(Color_001C38E0 *a, Color_001C38E0 *b,
                                      Source_001C38E0 *src) {
    a->r = b->r = src->r;
    a->g = b->g = src->g;
    a->b = b->b = src->b;
    a->a = b->a = src->a;
    a->q = b->q = 1.0f;
}

/* Sets a screen vertex at (x, y) at the windows' depth. */
static inline void set_xyz_001C38E0(Vertex_001C38E0 *v, s32 x, s32 y) {
    v->x = (x + 0x6C0) << 4;
    v->y = (y + 0x720) << 4;
    v->z = duelState.s.depth;
    v->fog = 0;
}

/* Draws the trade screen's background gradient. */
s32 lSzDuel_DrawTrade_Base_Pipe(s32 out) {
    extern u8 D_002BE858[];
    Source_001C38E0 *colors = (Source_001C38E0 *)D_002BE858;
    s32 width = 0x140;
    s32 height = 0x1C0;
    Packet_001C38E0 packet __attribute__((aligned(8)));

    ((Tag_001C38E0 *)packet.tag)->flags = 0x14;
    ((Tag_001C38E0 *)packet.tag)->count = 8;
    ((Tag_001C38E0 *)packet.tag)->registers = 0x41414141;
    ((Tag_001C38E0 *)packet.tag)->padding = 0;
    set_color_001C38E0(&packet.points[0].color, &packet.points[2].color, &colors[0]);
    set_color_001C38E0(&packet.points[1].color, &packet.points[3].color, &colors[1]);
    set_xyz_001C38E0(&packet.points[0].xyz, 0, 0);
    set_xyz_001C38E0(&packet.points[1].xyz, width, 0);
    set_xyz_001C38E0(&packet.points[2].xyz, 0, height);
    set_xyz_001C38E0(&packet.points[3].xyz, width, height);
    out = ExSortPrim_Pipe(out, (s32)packet.tag, 0, 0);
    set_color_001C38E0(&packet.points[0].color, &packet.points[2].color, &colors[1]);
    set_color_001C38E0(&packet.points[1].color, &packet.points[3].color, &colors[0]);
    set_xyz_001C38E0(&packet.points[0].xyz, width, 0);
    set_xyz_001C38E0(&packet.points[1].xyz, width * 2, 0);
    set_xyz_001C38E0(&packet.points[2].xyz, width, height);
    set_xyz_001C38E0(&packet.points[3].xyz, width * 2, height);
    return ExSortPrim_Pipe(out, (s32)packet.tag, 0, 0);
}

/* Draws the trade screen's title bar. */
void lSzDuel_DrawTrade_Title_Pipe(s32 packet, s32 left, s32 top) {
    s32 text = (s32)&D_002BF00B;
    s32 x = left + 0xE0;
    s32 y = top + 0x20;
    s32 element;

    packet = lSzDuel_DrawWindow_Base_Pipe(packet, x, y, 6, 1);
    element = lSzDuel_DrawWindow_Frame_Pipe(packet, -1, 0x73, 4, x, y, 0x15, 2, 1);
    SzDuel_DrawWindow_Font_Pipe(element, left + 0x140, top + 0x27, 2, 3,
                  func_0019BEF0((const char *)text), (s8 *)text, 0);
}

typedef struct Header_001C3E20 {
    u16 type;
    u16 count;
    u32 pad;
    u64 registers;
} Header_001C3E20;

typedef struct Vertex_001C3E20 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Vertex_001C3E20;

typedef struct Packet_001C3E20 {
    Header_001C3E20 header;
    u8 r, g, b, a;
    f32 q;
    Vertex_001C3E20 first;
    Vertex_001C3E20 second;
} Packet_001C3E20;

typedef struct Labels_001C3E20 {
    s8 *text[3];
} Labels_001C3E20;

typedef struct Work_001C3E20 {
    Labels_001C3E20 labels;
    Packet_001C3E20 packet;
} Work_001C3E20;

/* `left` for side 0, `right` for side 1. */
static inline s32 side_001C3E20(s32 player, s32 left, s32 right) {
    return player != 0 ? right : left;
}

#define SIDE_001C3E20(left, right) side_001C3E20(arg1, left, right)

/* How many cards side `player` has picked to trade. */
static inline s32 total_001C3E20(s32 player) {
    u8 *state = duelState.b;
    u8 *cards;
    s32 total;
    s32 i;

    if (player != 0) {
        cards = *(u8 **)(state + 0x6E4);
    } else {
        cards = *(u8 **)(state + 0x6E0);
    }
    total = 0;
    i = 0;
    do {
        total += *cards++;
        i++;
    } while (i < 0x356);
    return total;
}

/* Draws a filled rectangle. */
static inline s32 rectangle_001C3E20(s32 cursor, Packet_001C3E20 *packet,
                                    s32 x, s32 y, u8 *data) {
    ((Header_001C3E20 *)(s32)&packet->header)->count = 6;
    ((Header_001C3E20 *)(s32)&packet->header)->type = 3;
    ((Header_001C3E20 *)(s32)&packet->header)->registers = 0x441;
    ((Header_001C3E20 *)(s32)&packet->header)->pad = 0;
    packet->r = 0xA0;
    packet->g = 0xA0;
    packet->b = 0xA0;
    packet->a = 0x80;
    packet->q = 1.0f;
    packet->first.x = (x + 0x6CA) << 4;
    packet->first.y = (y + 0x738) << 4;
    packet->first.z = *(s32 *)(data + 0xC58);
    packet->first.fog = 0;
    packet->second.x = (x + 0x6F2) << 4;
    packet->second.y = (y + 0x739) << 4;
    packet->second.z = *(s32 *)(data + 0xC58);
    packet->second.fog = 0;
    return ExSortPrim_Pipe(cursor, (s32)&packet->header, 0, 0);
}
#pragma opt_propagation off

/* Draws side `arg1`'s trade list at (left, top): title, counts, sort keys, cards and scroll bar. */
s32 lSzDuel_DrawTrade_Bag_Pipe(s32 out, s32 arg1, s32 left, s32 topIn) {
    extern s32 lSzDuel_DrawWindow_ExBoard_Pipe();
    extern s32 SzDuel_DrawWindow_FontDigit_Pipe();
    extern s32 SzDuel_DrawWindow_Font_Pipe();
    extern s32 lSzDuel_DrawTrade_Card_Pipe();
    extern u8 duelIcons[];
    extern u8 D_00290828[];
    extern u8 D_00290832[];
    extern u8 D_0029086E[];
    extern u8 D_00290896[];
    extern u8 D_002908A0[];
    extern u8 D_00290A6C[];
    extern u8 D_00290AA8[];
    extern u8 D_00290AB2[];
    extern u8 D_00290ABC[];
    extern u8 D_00290AC6[];
    extern s8 *sortKeyNames[];
    extern Labels_001C3E20 D_00291490;
    extern u8 D_002BE8A4[];
    extern char D_002BF021[];
    extern char D_002BF024[];
    extern u8 D_0031814E[];
    u8 *data;
    char *descText;
    s8 *sortText;
    s32 flags;
    u16 *list;
    u16 top;
    u16 count;
    u8 pos;
    u8 *state;
    s32 x;
    s32 special;
    s32 style;
    s32 sortY;
    u8 *color;
    s32 labelY;
    s32 labelX;
    s32 active;
    s8 *subText;
    s32 textX;
    s32 textY;
    s32 barY;
    s8 **labelPtr;
    s8 *labelText;
    s32 pageX;
    s32 sortIndex;
    u8 *sortData;
    s32 barX;
    s32 cardY;
    s32 cursor;
    s32 selection;
    s32 sortX;
    s32 cardX;
    s32 pageY;
    s8 *titleText;
    s32 enabled;
    Work_001C3E20 work;

    data = duelState.b;
    special = (D_0031814E[arg1] == 1) ? 1 : 0;
    enabled = 0;
    if (special != 0) {
        if (SzPad_Check(arg1, 1, 0x100) != 0) {
            enabled = 1;
        }
    }
    selection = enabled != 0 ? 1 : 0;
    color = NULL;
    if (selection != 0) {
        color = D_002BE8A4;
    } else {
        color = NULL;
    }
    if (arg1 != 0) {
        titleText = (s8 *)D_002BF021;
    } else {
        titleText = (s8 *)D_002BF024;
    }
    subText = D_002BF024 + 3;
    descText = D_002BEF98;
    work.labels = D_00291490;
    if (arg1 != 0) {
        list = *(u16 **)(data + 0x6DC);
    } else {
        list = *(u16 **)(data + 0x6D8);
    }
    top = arg1 != 0 ? *(u16 *)(data + 0xC8E) : *(u16 *)(data + 0xC8A);
    count = arg1 != 0 ? *(u16 *)(data + 0xC90) : *(u16 *)(data + 0xC8C);
    pos = arg1 != 0 ? data[0xD5F] : data[0xD5E];
    sortData = (arg1 != 0 ? data + 0xCB9 : data + 0xCB6) + selection;
    sortText = sortKeyNames[*sortData];
    flags = 3;
    textX = left + SIDE_001C3E20(0x10, 0x240);
    textY = topIn + 0x10;
    out = lSzDuel_DrawWindow_Frame_Pipe(out, 0xC, -1, 0xB, textX, textY, -0x30, -0x30, 1);
    textX = left + SIDE_001C3E20(0x10, 0x240) + 0x18;
    textY = topIn + 0x1F;
    cursor = SzDuel_DrawWindowText_Pipe(out, textX, textY, 2, 3, titleText, NULL);
    x = left + SIDE_001C3E20(0x40, 0x1B0);
    cursor = lSzDuel_DrawWindow_Frame_Pipe(cursor, 0xC, -1, 6, x, topIn + 0x10, -0x8C, -0x2C, 1);
    textX = left + SIDE_001C3E20(0x40, 0x1B0) + 0x48;
    textY = topIn + 0x15;
    cursor = SzDuel_DrawWindowText_Pipe(cursor, textX, textY, 1, 3, subText, NULL);
    textX = left + SIDE_001C3E20(0x40, 0x1B0) + 0x24;
    textY = topIn + 0x23;
    cursor = SzDuel_DrawWindowText_Pipe(cursor, textX, textY, 1, 3, work.labels.text[1], NULL);
    textY = topIn + 0x31;
    cursor = SzDuel_DrawWindow_FontDigit_Pipe(cursor, textX, textY, 1, 2, 4, total_001C3E20(arg1));
    textX = left + SIDE_001C3E20(0x40, 0x1B0) + 0x6C;
    textY = topIn + 0x23;
    cursor = SzDuel_DrawWindowText_Pipe(cursor, textX, textY, 1, 3, work.labels.text[2], NULL);
    textY = topIn + 0x31;
    cursor = SzDuel_DrawWindow_FontDigit_Pipe(cursor, textX, textY, 1, 2, 4, total_001C3E20(arg1 ^ 1));
    x = left + SIDE_001C3E20(0x10, 0x230);
    cursor = lSzDuel_DrawWindow_Frame_Pipe(cursor, 0xC, -1, 5, x, topIn + 0x40, -0x40, -0x14, 1);
    x = left + 0x6C2 + SIDE_001C3E20(0x10, 0x230);
    cursor = lSzDuel_DrawWindow_ExIcon_Pipe(cursor, D_0029086E, x, topIn + 0x762, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    {
        s32 c = cursor;
        s32 x = left + SIDE_001C3E20(0x10, 0x230) + 0x17;
        s32 y = topIn + 0x44;
        cursor = SzDuel_DrawBagCount_Pipe(c, x, y, arg1);
    }
    x = left + SIDE_001C3E20(0x10, 0x230);
    cursor = lSzDuel_DrawWindow_ExBoard_Pipe(cursor, 3, x, topIn + 0x54, -0x40, -0x1C, -1, 0);
    x = left + 0x6C0 + SIDE_001C3E20(0x15, 0x255);
    cursor = lSzDuel_DrawWindow_ExIcon_Pipe(cursor, D_00290AA8, x, topIn + 0x77D, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    x = left + 0x6C0 + SIDE_001C3E20(0x2C, 0x234);
    cursor = lSzDuel_DrawWindow_ExIcon_Pipe(cursor, D_00290828, x, topIn + 0x77C, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    x = left + SIDE_001C3E20(0x50, 0x140);
    cursor = lSzDuel_DrawWindow_ExBoard_Pipe(cursor, 3, x, topIn + 0x40, -0xF0, -0x30, -1, 0);
    x = left + 0x6CE + SIDE_001C3E20(0x50, 0x140);
    cursor = lSzDuel_DrawWindow_ExIcon_Pipe(cursor, D_00290896, x, topIn + 0x765, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    x = left + 0x6C7 + SIDE_001C3E20(0x50, 0x140);
    cursor = lSzDuel_DrawWindow_ExIcon_Pipe(cursor, D_00290ABC, x, topIn + 0x77E, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    sortX = left + 0x6E8 + SIDE_001C3E20(0x50, 0x140);
    sortY = topIn + 0x769;
    sortIndex = 0;
    do {
        style = -1;
        if (sortIndex == *sortData) {
            style = selection != 0 ? 2 : 1;
        }
        cursor = lSzDuel_DrawWindow_ExIcon_Pipe(cursor, duelIcons + (sortIndex + 0xD1) * 10, sortX, sortY,
                            0, 1, 0, 0, 0, 0, 1, color, style, 0x80);
        sortIndex++;
        sortX += 0x10;
    } while (sortIndex < 10);
    x = left + 0x78A + SIDE_001C3E20(0x50, 0x140);
    cursor = lSzDuel_DrawWindow_ExIcon_Pipe(cursor, D_002908A0, x, topIn + 0x765, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    x = left + 0x793 + SIDE_001C3E20(0x50, 0x140);
    cursor = lSzDuel_DrawWindow_ExIcon_Pipe(cursor, D_00290AC6, x, topIn + 0x77E, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    sortX = left + SIDE_001C3E20(0x50, 0x140) + 0x78;
    sortY = topIn + 0x5E;
    if (color != NULL) {
        flags |= 8;
    }
    cursor = SzDuel_DrawWindowText_Pipe(cursor, sortX, sortY, 0, flags, sortText, color);
    textX = left + SIDE_001C3E20(8, 0x148);
    sortY = topIn + 0x70;
    sortIndex = 0;
    do {
        cursor = lSzDuel_DrawTrade_Card_Pipe(cursor, arg1, list[top + sortIndex], textX, sortY, 1);
        sortY += 0x36;
        sortIndex++;
    } while (sortIndex < 5);
    x = left + SIDE_001C3E20(0x10, 0x184);
    cursor = lSzDuel_DrawWindow_ExBoard_Pipe(cursor, 3, x, topIn + 0x17E, -0xEC, -0x32, -1, 0);
    x = left + 0x6C0 + SIDE_001C3E20(0x2C, 0x234);
    cursor = lSzDuel_DrawWindow_ExIcon_Pipe(cursor, D_00290832, x, topIn + 0x8A2, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    x = left + 0x6C0 + SIDE_001C3E20(0x15, 0x255);
    cursor = lSzDuel_DrawWindow_ExIcon_Pipe(cursor, D_00290AB2, x, topIn + 0x8A7, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    x = left + 0x6C0 + SIDE_001C3E20(0x17, 0x259);
    cursor = lSzDuel_DrawWindow_ExIcon_Pipe(cursor, D_00290A6C, x, topIn + 0x8BA, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    {
        s32 c = cursor;
        s32 x = left + SIDE_001C3E20(0x2C, 0x231);
        s32 y = topIn + 0x19D;
        cursor = SzDuel_DrawWindowText_Pipe(c, x, y, 1, 0, (s8 *)descText, NULL);
    }
    labelX = left + SIDE_001C3E20(0x7E, 0x18A);
    labelY = topIn + 0x182;
    labelPtr = work.labels.text;
    sortIndex = 0;
    state = data + arg1;
    do {
        if (state[0xCC0] == sortIndex) {
            active = 1;
        } else {
            active = 0;
        }
        cursor = lSzDuel_DrawWindow_ExBoard_Pipe(cursor, 3, labelX, labelY, -0x78, -0xE, -1, 1);
        labelText = *labelPtr;
        cursor = SzDuel_DrawWindow_Font_Pipe(cursor, labelX + 1, labelY + 1, 1, 0, func_0019BEF0((char *)labelText),
                                             labelText, active != 0 ? 0 : (s32)D_002BE944);
        sortIndex++;
        labelY += 0xE;
        labelPtr++;
    } while (sortIndex < 3);
    sortX = left + SIDE_001C3E20(0xFC, 0x148);
    sortY = topIn + 0x17E;
    cursor = lSzDuel_DrawWindow_ExBoard_Pipe(cursor, 3, sortX, sortY, -0x3C, -0x32, -1, 0);
    if (count) {
        cursor = rectangle_001C3E20(cursor, &work.packet, sortX, sortY, data);
        pageX = left + SIDE_001C3E20(0xFC, 0x148) + 0x1E;
        pageY = topIn + 0x186;
        cursor = SzDuel_DrawWindow_FontDigit_Pipe(cursor, pageX, pageY, 1, 2, 3, top + pos + 1);
        cursor = SzDuel_DrawWindow_FontDigit_Pipe(cursor, pageX, pageY + 0x17, 1, 2, 3, count);
    }
    return cursor;
}

typedef struct {
    u16 count;
    u16 flags;
    u32 padding;
    u64 registers;
} Tag_001C4B00;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Color_001C4B00;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Vertex_001C4B00;

typedef struct {
    u64 tag[2];
    Color_001C4B00 color;
    Vertex_001C4B00 vertex0;
    Vertex_001C4B00 vertex1;
    u64 end;
} Box_001C4B00;

typedef struct {
    u8 low : 4;
    u8 high : 4;
} Nibbles_001C4B00;

/* `left` for side 0, `right` for side 1. */
static inline s32 offset_001C4B00(s32 side, s32 left, s32 right) {
    return side != 0 ? right : left;
}

extern u8 duelAttrIcons[]; /* original: gSzDuel_Attr */
extern u8 duelIcons[]; /* original: gSzDuel_Icon */
extern u8 D_0029086E[];
extern u8 D_00290878[];
extern u8 D_002908BE[];
extern u8 D_002908C8[];
extern s32 D_002908E6;
extern u8 D_002908F0[];
extern u8 D_00290A12[];
extern s8 D_002BF02D;
extern char D_002BF030[];
extern char gSzDuel_aicolMsg[];
extern char D_002BE948[];
#pragma opt_propagation reset
#pragma opt_dead_assignments off

/* Draws one card row of side `side`'s trade list: picture, name, attribute, level, attack, defence, counts. */
s32 lSzDuel_DrawTrade_Card_Pipe(s32 packet, s32 side, s32 card, s32 left, s32 top, s32 highlight) {
    extern s32 func_001B3CC0(s32, void *, s32, s32, s32, s32, s32, s32, s64, s64, s64, s64, s64, s64);
    extern s32 func_001B4540(s32, s32, s32, s64, s32, s32);
    extern s32 func_001B6EA0();
    extern s32 func_001B6F70();
    extern s32 func_001B65F0();
    extern s32 func_001FEAB0();
    extern s32 func_001FE660(s32, s32, s32, s32, f32, f32, s32, void (*)(void));
    extern s32 func_001DE090();
    extern s64 func_00215D30();
    s32 ret;
    s32 id3;
    u8 *state = duelState.b;
    u8 *info;
    s32 kind;
    s32 style;
    s32 attribute;
    u8 *name;
    u8 *own_counts;
    u8 *counts;
    u8 *other_counts;
    s8 *text;
    u8 mode;
    u8 category;
    s32 low;
    f32 scale;
    s32 px;
    s32 x_position;
    s32 py;
    s32 ty;
    u8 *count;
    s32 width;
    s32 id;
    Box_001C4B00 box __attribute__((aligned(8)));
    s32 value;
    s32 hint = 0;

    info = func_001DD0E0(card);
    if (side != 0) {
        own_counts = *(u8 **)(state + 0x6E4);
    } else {
        own_counts = *(u8 **)(state + 0x6E0);
    }
    if (side != 0) {
        other_counts = *(u8 **)(state + 0x6E0);
    } else {
        other_counts = *(u8 **)(state + 0x6E4);
    }
    mode = state[side + 0xCC0];
    if (mode == 2) {
        counts = other_counts;
    } else {
        counts = own_counts;
    }
    if (mode == 2) {
        text = &D_002BF02D;
    } else {
        text = (s8 *)D_002BF030;
    }
    scale = 1.0f;
    if (info == NULL) {
        return func_001B4780(packet, -1, -1, 9, left, top, -0x130, -0x36, 0);
    }
    category = info[0];
    kind = (s32)category >> 5;
    low = category & 0x1F;
    if (kind == 0) {
        name = duelIcons + low * 10;
    } else {
        name = duelIcons + (kind + 20) * 10;
    }
    style = func_001DE020(kind);
    attribute = func_001DE090(style, info[2] & 0xF);
    if (style == 0) {
        if (*(u16 *)(info + 4) != 0xFFFF) {
            style = 4;
        }
    }
    id = func_001B4780(func_0020F290(func_001FD680(packet, 1, func_001DE210(card), 0, 22)), style + 7, -1, 9, left, top, -0x130, -0x36, 0);
    if (func_00216920(side, card) != 0) {
        x_position = left + 0x6C0 + (side != 0 ? 0x108 : 8);
        id = func_001B3CC0(id, D_00290A12, x_position, top + 0x727, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    } else {
        id = func_001B6EA0(id, left + (side != 0 ? 0x108 : 8), top + 7, 1, 0, 3, card);
    }
    if (kind == 0) {
        s64 leader = func_00215D30(side, card);
        x_position = left + offset_001C4B00(side, 0x28, 0xE8);
        id = func_001B4540(id, x_position, top + 3, leader, 0, offset_001C4B00(side, 0, 1));
    }
    x_position = left + 0x6C0 + (side != 0 ? 0x114 : 4);
    id = func_001B3CC0(id, name, x_position, top + 0x73A, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    x_position = left + 0x6C0 + (side != 0 ? 0xFA : 0x1E);
    id = func_001B3CC0(id, duelAttrIcons + attribute * 10, x_position, top + 0x73A, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    if (kind == 0) {
        x_position = left + 0x6C0 + (side != 0 ? 0xCF : 0x38);
        id = func_001B3CC0(id, &D_002908E6, x_position, top + 0x743, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
        id = func_001B6EA0(id, left + (side != 0 ? 0xCF : 0x38) + 0x16, top + 0x25, 1, 0, 2, ((Nibbles_001C4B00 *)(info + 2))->high);
        x_position = left + 0x6C0 + (side != 0 ? 3 : 0xF8);
        id = func_001B3CC0(id, D_002908BE, x_position, top + 0x723, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
        id = func_001B6EA0(id, left + (side != 0 ? 3 : 0xF8) + 0x10, top + 5, 1, 0, 4, *(u16 *)(info + 8) & 0x1FFF);
        x_position = left + 0x6C0 + (side != 0 ? 3 : 0xF8);
        id = func_001B3CC0(id, D_002908C8, x_position, top + 0x733, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
        id = func_001B6EA0(id, left + (side != 0 ? 3 : 0xF8) + 0x10, top + 0x15, 1, 0, 4, *(u16 *)(info + 10) & 0x1FFF);
    }
    x_position = left + 0x6C0 + (side != 0 ? 0x96 : 0x68);
    id = func_001B3CC0(id, D_002908F0, x_position, top + 0x743, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    ret = func_001B6EA0(id, left + (side != 0 ? 0x96 : 0x68) + 0x16, top + 0x25, 1, 0, 3, info[3]);
    px = left + 0x6C0 + (side != 0 ? 0x66 : 0xAD);
    py = top + 0x743;
    if (func_00216AC0(side, card, -1) < 9) {
        ret = func_001B3CC0(ret, D_0029086E, px, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    } else {
        ret = func_001B3CC0(ret, D_00290878, px, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    }
    px = left + (side != 0 ? 0x66 : 0xAD) + 0x13;
    py = top + 0x25;
    ret = func_001B6EA0(ret, px, py, 1, 0, 1, func_00216AC0(side, card, hint != 0 ? -1 : 3));
    count = counts + card;
    if (*count != 0) {
        ty = top + 0x25;
        ret = func_001B4780(ret, 0xD, -1, 7, left + offset_001C4B00(side, 0xE8, 0), top + 0x23, -0x48, -0x10, 1);
        px = left + (side != 0 ? 0 : 0xE8) + 0xC;
        value = func_0019BEF0((char *)text);
        ret = func_001B6F70(ret, px, ty, 1, 0, value, text, 0);
        px = left + (side != 0 ? 0 : 0xE8) + 0x30;
        ret = func_001B6EA0(ret, px, ty, 1, 0, 1, *count);
    }
    id3 = func_001B65F0(ret, style + 7, left + (side != 0 ? 0x38 : 0x48), top + 3, -0xB0, -0x20, -1, 0);
    width = *(s32 *)((u8 *)func_001FEAB0(1) + 0xC);
    if (width > 168) {
        scale = 168.0f / (f32)width;
    }
    id3 = func_001FE660(id3, 1, left + offset_001C4B00(side, 0x48, 0x38) + 6, top + 9, scale, 1.0f, (s32)gSzDuel_aicolMsg, SzMsg_DrawRect_Pipe);
    id3 = func_001FE660(id3, 1, left + offset_001C4B00(side, 0x48, 0x38) + 5, top + 8, scale, 1.0f, (s32)D_002BE944, SzMsg_DrawRect_Pipe);
    id3 = func_001FE660(id3, 1, left + offset_001C4B00(side, 0x48, 0x38) + 4, top + 7, scale, 1.0f, (s32)D_002BE948, SzMsg_DrawRect_Pipe);
    func_001FEAF0(1);
    if (highlight != 0) {
        if (func_00216AC0(side, card, 3) <= 0) {
            ((Tag_001C4B00 *)box.tag)->flags = 6;
            ((Tag_001C4B00 *)box.tag)->count = 3;
            ((Tag_001C4B00 *)box.tag)->registers = 0x441;
            ((Tag_001C4B00 *)box.tag)->padding = 0;
            func_002086D0(box.tag, func_00208D00(2));
            box.color.r = 0x80;
            box.color.g = 0x80;
            box.color.b = 0x80;
            box.color.a = 0x40;
            box.color.q = 1.0f;
            box.vertex0.x = (left + 0x6C0) << 4;
            box.vertex0.y = (top + 0x720) << 4;
            box.vertex0.z = *(s32 *)(state + 0xC58);
            box.vertex0.fog = 0;
            box.vertex1.x = (left + 0x7F0) << 4;
            box.vertex1.y = (top + 0x756) << 4;
            box.vertex1.z = *(s32 *)(state + 0xC58);
            box.vertex1.fog = 0;
            id3 = func_00207650(id3, (s32)box.tag, 0, 0);
        }
    }
    return id3;
}
#pragma opt_dead_assignments reset

/* Draws side `player`'s cursor on row `row` of its list. */
s32 lSzDuel_DrawTrade_Cursor_Pipe(s32 id, s32 player, s32 left, s32 top, s32 row) {
    extern s32 SzDuel_DrawWindow_Font_Pipe(s32, s32, s32, s32, s32, s32, s8 *, s32);
    extern s32 lSzDuel_DrawWindow_ExIcon_Pipe(s32, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
    extern char D_002BF030[];
    extern char D_002BEFEC[];
    extern s32 D_00290A62;
    extern s32 D_00290A58;
    extern s32 D_00290A4E;
    extern s32 D_00290A76;
    u8 *state = duelState.b;
    s8 *text1 = D_002BF030 + 3;
    s8 *text2 = D_002BEFEC;
    s8 *text4 = (s8 *)&D_002BF00B;
    s32 hint = 0;
    u16 busy;
    s32 x;
    s32 y;
    s32 sx;
    s32 sy;
    s32 px;
    s32 py;

    x = left + 8 + (player != 0 ? 0x140 : 0);
    y = top + 0x70 + row * 0x36;
    sx = x + 0x6C0;
    sy = y + 0x720;
    busy = (player != 0) ? *(u16 *)(state + 0xC98) : *(u16 *)(state + 0xC96);
    id = lSzDuel_DrawWindow_Frame_Pipe(id, -1, 4, 6, x - 2, y - 2, -0x130, -0x36, 1);
    if (busy != 0) {
        return id;
    }
    id = lSzDuel_DrawWindow_Frame_Pipe(id, 0xD, -1, 7, x, y + 0x36, -0x130, -0x14, 1);
    if (state[player + 0xCC0] < 2) {
        px = sx + 5;
        py = sy + 0x38;
        id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_00290A62, px, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
        id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_00290A58, px + 0x11, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
        px = x + 0x2C;
        py = y + 0x3B;
        id = SzDuel_DrawWindow_Font_Pipe(id, px, py, 1, 0, func_0019BEF0((char *)text1), text1,
                           hint != 0 ? (s32)D_002BE944 : 0);
    }
    id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_00290A4E, sx + 0x6B, sy + 0x38, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    px = x + 0x81;
    py = y + 0x3B;
    id = SzDuel_DrawWindow_Font_Pipe(id, px, py, 1, 0, func_0019BEF0((char *)text2), text2,
                       hint != 0 ? (s32)D_002BE944 : 0);
    id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_00290A76, sx + 0xC9, sy + 0x38, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    px = x + 0xDF;
    py = y + 0x3B;
    return SzDuel_DrawWindow_Font_Pipe(id, px, py, 1, 0, func_0019BEF0((char *)text4), text4,
                         hint != 0 ? (s32)D_002BE944 : 0);
}
#pragma opt_propagation off

/* Draws the "ready" box in the middle of the screen. */
s32 lSzDuel_DrawTrade_Ready_Pipe(s32 packet, s32 left, s32 top) {
    extern char D_002BF03A[];
    s8 *text = D_002BF03A;
    s32 width;
    s32 height;
    s32 fx;
    s32 fy;
    s32 ty;

    lSzDuel_GetFontSize(2, 3, strlen(text), text, &width, &height);
    width += 0x18;
    height += 0xC;
    fx = left + 0x140 - (width >> 1);
    fy = top + 0xE0 - (height >> 1);
    packet = lSzDuel_DrawWindow_Frame_Pipe(packet, 0xC, -1, 0xB, fx, fy, -width, -height, 1);
    ty = top + 0xE8 - (height >> 1);
    return SzDuel_DrawWindow_Font_Pipe(packet, left + 0x140, ty, 2, 3, strlen(text), text, 0);
}
#pragma opt_propagation reset

/* Draws the leave-trade dialog (yes / no). */
void lSzDuel_DrawTrade_Exit_Pipe(s32 packet, s32 left, s32 top) {
    extern s32 lSzDuel_DrawDialog_Window_Pipe(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
    extern s32 *SzMsg_GetInfo(s32);
    extern s32 SzMsg_DrawX_Pipe(s32, s32, s32, s32, s32, void (*)(void));
    extern s32 SzDuel_DrawWindow_Font_Pipe(s32, s32, s32, s32, s32, s32, s8 *, s32);
    u8 *state = duelState.b;
    s32 text = (s32)D_002BEF98;
    s8 *text2 = D_002BEF6F;
    s8 *text3 = D_002BEF73;
    s32 id;
    s32 *size;

    packet = lSzDuel_DrawDialog_Window_Pipe(packet, 2, -1, 0x7E, left + 0x140, top + 0x83, 0x140, 0xBA,
                         func_0019BEF0((char *)text), text, 0);
    id = RhText_SetTextureFlush(SzMsg_LoadFont_Pipe(packet, 1, 0x7F, 0, 0x16));
    size = SzMsg_GetInfo(1);
    id = SzMsg_DrawX_Pipe(id, 1, left + 0x140 - (size[3] >> 1), top + 0x119 - (size[4] + 12), 0,
                       SzMsg_DrawRect_Pipe);
    SzMsg_Free(1);
    id = SzDuel_DrawWindow_Font_Pipe(id, left + 0xF0, top + 0x119, 2, 3, func_0019BEF0((char *)text2), text2,
                       D_003181C6 != 0 ? 0 : (s32)D_002BE944);
    SzDuel_DrawWindow_Font_Pipe(id, left + 0x190, top + 0x119, 2, 3, func_0019BEF0((char *)text3), text3,
                  state[0xD36] != 0 ? (s32)D_002BE944 : 0);
}

/* Draws the do-trade dialog (yes / no). */
void lSzDuel_DrawTrade_Do_Pipe(s32 packet, s32 left, s32 top) {
    extern s32 lSzDuel_DrawDialog_Window_Pipe(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
    extern s32 *SzMsg_GetInfo(s32);
    extern s32 SzMsg_DrawX_Pipe(s32, s32, s32, s32, s32, void (*)(void));
    extern s32 SzDuel_DrawWindow_Font_Pipe(s32, s32, s32, s32, s32, s32, s8 *, s32);
    u8 *state = duelState.b;
    s32 text = (s32)&D_002BF00B;
    s8 *text2 = D_002BEF6F;
    s8 *text3 = D_002BEF73;
    s32 id;
    s32 *size;

    packet = lSzDuel_DrawDialog_Window_Pipe(packet, 2, -1, 0x7D, left + 0x140, top + 0x8E, 0x140, 0xA4,
                         func_0019BEF0((char *)text), text, 0);
    id = RhText_SetTextureFlush(SzMsg_LoadFont_Pipe(packet, 1, 0x7F, 0, 0x16));
    size = SzMsg_GetInfo(1);
    id = SzMsg_DrawX_Pipe(id, 1, left + 0x140 - (size[3] >> 1), top + 0x10E - (size[4] + 12), 0,
                       SzMsg_DrawRect_Pipe);
    SzMsg_Free(1);
    id = SzDuel_DrawWindow_Font_Pipe(id, left + 0xF0, top + 0x10E, 2, 3, func_0019BEF0((char *)text2), text2,
                       D_003181C6 != 0 ? 0 : (s32)D_002BE944);
    SzDuel_DrawWindow_Font_Pipe(id, left + 0x190, top + 0x10E, 2, 3, func_0019BEF0((char *)text3), text3,
                  state[0xD36] != 0 ? (s32)D_002BE944 : 0);
}

/* Draws the trade notice dialog. */
void lSzDuel_DrawTrade_Notice_Pipe(s32 packet, s32 left, s32 top) {
    s32 text = (s32) &D_002BF040;
    s32 length = func_0019BEF0((const char *) text);

    lSzDuel_DrawDialog_Window_Pipe(packet, 2, -1, 0x80, left + 0x140, top + 0xA3,
                  0x140, 0x7A, length, text, 1);
}

typedef struct {
    s8 first : 2;
    s8 second : 2;
    s8 unused : 4;
} PulseFlags_001CC620;

extern u16 D_00318118;
extern u8 D_003181F3;
extern PulseFlags_001CC620 D_003181F4;

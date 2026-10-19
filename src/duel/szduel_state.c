/* The duel screen, part 12 of 15: players, turns, summon power, hand phase, deck / graveyard / hand lists, life points. */

#include "common.h"

/* The card type group of card kind `kind`. */
s32 SzDuel_Kind2Type(s32 kind) {
    return kind == 1 ? 1
         : kind == 2 ? 1
         : kind == 3 ? 2
         : kind == 4 ? 2
         : kind == 5 ? 3
         : kind;
}

/* The attribute icon for a type group, or `fallback` for none. */
s32 SzDuel_Type2Attr(s64 type, s32 fallback) {
    return type > 0 ? (s32)type + 5 : fallback;
}

/* The type group of a card kind (SzDuel_Kind2Type written out). */
static inline s32 convert_001DE0B0(s32 value) {
    return value == 1 ? 1 :
           value == 2 ? 1 :
           value == 3 ? 2 :
           value == 4 ? 2 :
           value == 5 ? 3 : value;
}

/* The attribute icon for card kind `kind`, or `fallback` when the kind has no type group. */
s32 SzDuel_Kind2Attr(s32 kind, s32 fallback) {
    s32 result = fallback;

    kind = convert_001DE0B0(kind);
    result = kind > 0 ? kind + 5 : result;
    return result;
}

/* Converts a card number in the old (card list) order to the game's card id; CARD_NONE for none. */
s32 SzDuel_Xax2New(s32 number) {
    if (number < 0 || number >= 0x356) {
        return 0x3E7;
    }
    number = AlternateCardIds[number];
    if (number == 0x29F) {
        number = 0x3E7;
    }
    if (number < 0 || number >= 0x356) {
        return 0x3E7;
    }
    return number;
}

/* Converts a card id to its number in the old (card list) order; CARD_NONE for none. */
s32 SzDuel_New2Xax(s32 card) {
    s32 i;
    u16 *p;

    p = AlternateCardIds;
    if (card == 0x29F) {
        card = 0x3E7;
    }
    if (card < 0 || card >= 0x356) {
        return 0x3E7;
    }
    i = 0;
    do {
        if (*p == card) {
            return i;
        }
        i++;
        p++;
    } while (i < 0x356);
    return 0x3E7;
}

/* The message id of card `card`'s name, or -1. */
s32 SzDuel_GetMsgName(s32 card) {
    SzData_GetOption(0, 0);
    if (card < 0 || card >= 0x356) {
        return -1;
    }
    return card + 0x140;
}

/* The camera distance used to show monster `card` in 3D, or -1. */
s32 SzDuel_GetCamDist(s32 card) {
    if (card < 0 || card >= 0x356) {
        return -1;
    }
    return gSzDuel_CardDefaultCamDist[card];
}

/* Reads the 3D-battle option. */
void SzDuel_GetOption3DBattle(void) {
    SzData_GetOption(0, 1);
}

#define MAX_001DE2B0(a, b) ((a) > (b) ? (a) : (b))
#define MIN_001DE2B0(a, b) ((a) < (b) ? (a) : (b))

typedef struct {
    s8 pad0 : 3;
    s8 flag : 1;
    s8 pad4 : 4;
} Flags_001DE2B0;

/* Which battle animation (3, 4 or 6) the attack of unit (attackerSide, attackerUnit) on unit (defenderSide,
   defenderUnit) uses, from their attack and defence on field square (fieldX, fieldZ). */
s32 SzDuel_GetPlayMotion(s32 attackerSide, s32 attackerUnit, s32 defenderSide, s32 defenderUnit, s32 fieldX, s32 fieldZ, s32 noTieWin) {
    s32 attacker;
    s32 defender;
    s32 result;
    s32 attackerBonus;
    s32 attackerAttack;
    s32 defenderAttack;
    s32 defenderBonus;
    s32 defenderDefence;

    attacker = SzDuel_GetUnit(attackerSide, attackerUnit);
    defender = SzDuel_GetUnit(defenderSide, defenderUnit);
    result = 0;
    if (attacker != 0 && defender != 0) {
        attackerBonus = Ta_GetParamOfs(attacker, fieldX, fieldZ, 1);
        defenderAttack = Ta_GetParamOfs(defender, fieldX, fieldZ, 1);
        defenderBonus = Ta_GetParamOfs(defender, fieldX, fieldZ, 0);
        attackerAttack = attackerBonus + SzDuel_GetUnitAP2((void *)attacker, 0);
        defenderAttack += SzDuel_GetUnitAP2((void *)defender, 0);
        defenderDefence = defenderBonus + SzDuel_GetUnitDP2((void *)defender, 0);
        attackerAttack = MIN_001DE2B0(MAX_001DE2B0(attackerAttack, 0), 9999);
        defenderAttack = MIN_001DE2B0(MAX_001DE2B0(defenderAttack, 0), 9999);
        defenderDefence = MIN_001DE2B0(MAX_001DE2B0(defenderDefence, 0), 9999);
        result = 4;
        if (((Flags_001DE2B0 *)((u8 *)defender + 0x57))->flag) {
            if (defenderDefence >= attackerAttack) {
                result = 6;
            }
        } else if (defenderAttack == attackerAttack) {
            if (noTieWin == 0 && attackerSide == SzDuel_GetTurnOwner()) {
                result = 3;
            }
        } else if (attackerAttack < defenderAttack) {
            result = 3;
        }
    }
    return result;
}

/* Who plays side `player` (DuelPlayer.duelistId). */
u8 SzDuel_GetPlayer(s32 player) {
    return DUEL_PLAYER(player)->duelistId;
}

/* Sets who plays side `player`; only the low 7 bits are kept. */
void SzDuel_SetPlayer(s32 player, s32 duelistId) {
    DuelPlayer *side;

    side = DUEL_PLAYER(player);
    if (side->duelistId != (duelistId & 0xFF)) {
        duelistId &= 0x7F;
        side->duelistId = duelistId;
    }
}

/* The side whose turn it is (0 or 1). */
s32 SzDuel_GetTurnOwner(void) {
    return (s32) duelState.s.turnOwner;
}

/* The side that took the first turn. */
u8 SzDuel_GetTurnFirst(void) {
    return duelState.s.turnFirst;
}

/* How many turns have been played (capped at 255). */
u8 SzDuel_GetTurnCount(void) {
    return duelState.s.turnCount;
}

/* A helper only so the clamp below compiles to the original's code. */
static inline s32 nonnegative_001DE570(s32 value) {
    return value > 0 ? value : 0;
}

/* Sets the turn count, clamped to 0..255. */
void SzDuel_SetTurnCount(s32 count) {
    DuelState *duel = DUEL_STATE;

    duel->turnCount = nonnegative_001DE570(count) < 0xFF
        ? nonnegative_001DE570(count) : 0xFF;
}

/* Side `player`'s summon power (0..12). */
s32 SzDuel_GetSummonPower(s32 player) {
    return DUEL_PLAYER(player)->summonPower;
}

/* Applies `operation` (DUEL_CALC_ADD/SUB/MUL/DIV/SET) with `value` to side `player`'s summon power, clamped
   to 0..12. Returns 0 for an unknown operation, 1 otherwise. */
s32 SzDuel_CalcSummonPower(s32 player, s32 operation, s32 value) {
    s32 current;
    s32 result;
    DuelPlayer *side;

    side = DUEL_PLAYER(player);
    current = side->summonPower;
    switch (operation) {
    case DUEL_CALC_ADD:
        result = current + value;
        break;
    case DUEL_CALC_SUB:
        result = current - value;
        break;
    case DUEL_CALC_MUL:
        result = current * value;
        break;
    case DUEL_CALC_DIV:
        result = current / value;
        break;
    case DUEL_CALC_SET:
        result = value;
        break;
    default:
        return 0;
    }

    value = result; /* this copy is kept for the match */
    value = (value > 0 ? value : 0) < 12 ? (value > 0 ? value : 0) : 12;
    side->summonPower = value;
    return 1;
}

/* Side `player`'s summon charge. */
u8 SzDuel_GetSummonCharge(s32 player) {
    return DUEL_PLAYER(player)->summonCharge;
}

/* Sets side `player`'s summon charge. */
void SzDuel_SetSummonCharge(s32 player, s8 charge) {
    DUEL_PLAYER(player)->summonCharge = charge;
}

/* Whether side `player` is in its hand phase (1) or not (0). */
s32 SzDuel_InqHandPhase(s32 player) {
    return DUEL_PLAYER(player)->flags346.handPhase ? 1 : 0;
}

/* Sets side `player`'s hand phase. */
void SzDuel_SetHandPhase(s32 player, s32 on) {
    DuelPlayer *side = DUEL_PLAYER(player);

    side->flags346.handPhase = on ? 1 : 0;
}

/* Side `player`'s destiny-draw byte (bits 0-3 Destiny_Tab entry, 4-6 bonus level, 7 used this duel). */
u8 SzDuel_InqDestinyFlag(s32 player) {
    return DUEL_PLAYER(player)->destinyDraw;
}

/* Sets side `player`'s destiny-draw byte (bits 0-3 destinyDrawTable entry, 4-6 bonus level, 7 used this duel). */
void SzDuel_SetDestinyFlag(s32 player, s8 flag) {
    DUEL_PLAYER(player)->destinyDraw = flag;
}

/* Whether the duel's info windows are shown. */
s32 SzDuel_GetWindowDisp(void) {
    return duelState.s.f66.windowsShown ? 1 : 0;
}

/* Shows or hides the duel windows. */
void SzDuel_SetWindowDisp(s32 on) {
    DuelState *duel = DUEL_STATE; /* a local pointer, not DUEL_STATE->: needed for the match */

    duel->f66.windowsShown = (s8) (on ? 1 : 0);
}

/* Turns drawing of the duel windows on or off. */
void SzDuel_SetWindowDraw(s32 on) {
    DuelState *duel = DUEL_STATE; /* a local pointer, not DUEL_STATE->: needed for the match */

    duel->f67.windowsDraw = (s8)(on ? 1 : 0);
}

/* Marks the duel windows busy or free. */
void SzDuel_SetWindowBusy(s32 on) {
    DuelState *duel = DUEL_STATE; /* a local pointer, not DUEL_STATE->: needed for the match */

    duel->f67.windowsBusy = (s8)(on ? 1 : 0);
}

/* Moves side `player`'s board cursor to column x, row z (0..6) and points the camera there. Returns 0 if the
   square is off the board. */
s32 SzDuel_SetPlayerCur(s32 player, s32 x, s32 z) {
    DuelPlayer *side;
    f32 saved[4];
    f32 position[3];

    side = DUEL_PLAYER(player);
    if (x < 0 || x >= 7 || z < 0 || z >= 7) {
        return 0;
    }
    SzView_IV2V(side->cameraOrbit, saved);
    side->cursorX = x;
    side->cursorZ = z;
    position[0] = (f32)((x - 3) * 50);
    position[2] = (f32)((z - 3) * 50);
    position[1] = (f32)side->cursorHeight;
    SzView_SetCP(0, position);
    SzView_SetLookSP(0, saved);
    return 1;
}

/* Empties side `player`'s deck. */
void SzDuel_InitDeck(s32 player) {
    DuelDeck *deck;
    s32 i;
    u16 *slot;

    i = 0;
    deck = &DUEL_PLAYER(player)->deck;
    slot = deck->cards;
    do {
        i += 1;
        *slot = CARD_NONE;
        slot++;
    } while (i < 40);
    deck->count = 0;
}

/* How many cards side `player`'s deck holds. */
s32 SzDuel_GetDeckCount(s32 player) {
    return DUEL_PLAYER(player)->deck.count;
}

/* The card in deck slot `slot` (CARD_NONE if empty), or -1 for a bad slot. */
s32 SzDuel_InqDeck(s32 player, s32 slot) {
    u16 *cards = DUEL_PLAYER(player)->deck.cards;

    if ((slot < 0) || (slot >= 40)) {
        return -1;
    }
    return cards[slot];
}

/* Puts `card` into a random free slot of side `player`'s deck. Returns the slot, or -1 if the card id is bad
   or the deck is full. */
s32 SzDuel_AddDeck(s32 player, s32 card) {
    extern s32 func_001A22C0(f32); /* declared here with a float parameter: needed for the match */
    DuelDeck *deck;
    s32 index;

    deck = &DUEL_PLAYER(player)->deck;
    if (card == CARD_REJECTED) {
        card = CARD_NONE;
    }
    if (card < 0 || card >= CARD_COUNT) {
        return -1;
    }
    if (deck->count >= 40) {
        return -1;
    }
    do {
        index = (s32)func_001A22C0(40.0f * ((f32)func_0019A5C8() / 2147483648.0f));
    } while (deck->cards[index] != CARD_NONE);
    deck->cards[index] = card;
    deck->count++;
    return index;
}

/* Moves the cards of side `player`'s deck to the front, keeping their order. */
void SzDuel_PackDeck(s32 player) {
    DuelDeck list;
    u16 *fill;
    DuelDeck *dest;
    s32 i;
    u16 *src;
    u16 card;
    s32 count;

    dest = &DUEL_PLAYER(player)->deck;
    list.count = 0;
    i = 0;
    src = (u16 *)dest;
    do {
        card = *src;
        if (card != CARD_NONE) {
            list.cards[list.count++] = card;
        }
        i++;
        src++;
    } while (i < 40);
    count = list.count;
    if (count < 40) {
        fill = &list.cards[count];
        do {
            count++;
            *fill = CARD_NONE;
            fill++;
        } while (count < 40);
    }
    *dest = list;
}

/* Puts `card` into deck slot `slot` if that slot is free. Returns 1 if it did. */
s32 SzDuel_SetDeck(s32 player, s32 slot, s32 card) {
    DuelDeck *deck;
    u16 *entry;

    deck = &DUEL_PLAYER(player)->deck;
    if ((slot < 0) || (slot >= 40)) {
        return 0;
    }
    if (card == CARD_REJECTED) {
        card = CARD_NONE;
    }
    if ((card < 0) || (card >= CARD_COUNT)) {
        return 0;
    }
    if (deck->count >= 40) {
        return 0;
    }
    entry = &deck->cards[slot];
    if (*entry != CARD_NONE) {
        return 0;
    }
    *entry = card;
    deck->count++;
    return 1;
}

/* Empties deck slot `slot`. Returns 1 if there was a card. */
s32 SzDuel_DelDeck(s32 player, s32 slot) {
    DuelDeck *deck;
    u16 *entry;

    deck = &DUEL_PLAYER(player)->deck;
    if ((slot < 0) || (slot >= 40)) {
        return 0;
    }
    entry = &deck->cards[slot];
    if (*entry == CARD_NONE) {
        return 0;
    }
    *entry = CARD_NONE;
    deck->count--;
    return 1;
}

/* Draws the top card of side `player`'s deck: returns it (CARD_NONE if the deck is empty) and packs the deck. */
s32 SzDuel_DrawDeck(s32 player) {
    s32 card;
    DuelDeck *deck;
    DuelPlayer *side;

    side = DUEL_PLAYER(player);
    card = side->deck.cards[0];
    deck = &side->deck;
    if (card < 0 || card >= CARD_NONE) {
        return CARD_NONE;
    }
    if (deck->cards[0] != CARD_NONE) {
        deck->cards[0] = CARD_NONE;
        deck->count--;
    }
    SzDuel_PackDeck(player);
    return card;
}

/* Empties side `player`'s graveyard. */
void SzDuel_InitGrave(s32 player) {
    DuelGrave *grave;
    s32 count;
    u16 *slot;

    count = 0;
    grave = &DUEL_PLAYER(player)->grave;
    slot = grave->cards;
    do {
        count += 1;
        *slot = CARD_NONE;
        slot++;
    } while (count < 120);
    grave->count = 0;
}

/* The card in graveyard slot `slot`, or -1 for a bad slot. */
s32 SzDuel_InqGrave(s32 player, s32 slot) {
    u16 *cards = DUEL_PLAYER(player)->grave.cards;
    s32 ret;

    if ((slot < 0) || (slot >= 120)) {
        ret = -1;
    } else {
        ret = cards[slot];
    }
    return ret;
}

/* How many cards side `player`'s graveyard holds. */
u8 SzDuel_GetGraveCount(s32 player) {
    return DUEL_PLAYER(player)->grave.count;
}

/* Adds `card` to the end of side `player`'s graveyard. Returns its slot, or -1 if the id is bad or the
   graveyard is full. */
s32 SzDuel_AddGrave(s32 player, s32 card) {
    DuelGrave *grave;

    grave = &DUEL_PLAYER(player)->grave;
    if (card == CARD_REJECTED) {
        card = CARD_NONE;
    }
    if (card < 0 || card >= CARD_COUNT) {
        return -1;
    }
    if (grave->count >= 120) {
        return -1;
    }
    SzDuel_PackGrave(player);
    grave->cards[grave->count] = card;
    return grave->count++;
}

/* Moves the cards of side `player`'s graveyard to the front, keeping their order. */
void SzDuel_PackGrave(s32 player) {
    DuelGrave list;
    s16 *copy;
    s32 remaining;
    s16 *dest;
    s32 i;
    u16 *src;
    u16 card;
    s32 fill;

    dest = (s16 *)&DUEL_PLAYER(player)->grave;
    list.count = 0;
    i = 0;
    src = (u16 *)dest;
    do {
        card = *src;
        if (card != CARD_NONE) {
            list.cards[list.count++] = card;
        }
        i++;
        src++;
    } while (i < 120);

    fill = list.count;
    if (fill < 120) {
        copy = (s16 *)&list.cards[fill];
        do {
            fill++;
            *copy++ = CARD_NONE;
        } while (fill < 120);
    }

    /* copied back one halfword at a time (121 = the cards and the count), not as one struct assignment:
       the original code does it this way */
    copy = (s16 *)&list;
    remaining = 121;
    do {
        remaining--;
        *dest++ = *copy++;
    } while (remaining > 0);
}

/* Empties graveyard slot `slot`. Returns 1 if there was a card. */
s32 SzDuel_DelGrave(s32 player, s32 slot) {
    DuelGrave *grave;
    u16 *entry;

    grave = &DUEL_PLAYER(player)->grave;
    if ((slot < 0) || (slot >= 120)) {
        return 0;
    }
    entry = &grave->cards[slot];
    if (*entry == CARD_NONE) {
        return 0;
    }
    *entry = CARD_NONE;
    grave->count--;
    return 1;
}

/* Empties side `player`'s hand. */
void SzDuel_InitHand(s32 player) {
    DuelHand *hand;
    s32 i;
    u16 *slot;

    i = 0;
    hand = &DUEL_PLAYER(player)->hand;
    slot = hand->cards;
    do {
        i += 1;
        *slot = CARD_NONE;
        slot++;
    } while (i < 5);
    hand->count = 0;
}

/* The raw hand entry in slot `slot` (card id + tag), or -1 for a bad slot. */
s32 SzDuel_InqHand(s32 player, s32 slot) {
    u16 *cards = DUEL_PLAYER(player)->hand.cards;
    s32 result;

    if ((slot < 0) || (slot >= 5)) {
        result = -1;
    } else {
        result = cards[slot];
    }
    return result;
}

/* How many cards side `player`'s hand holds. */
s32 SzDuel_GetHandCount(s32 player) {
    return DUEL_PLAYER(player)->hand.count;
}

/* Adds `card` to the end of side `player`'s hand. Returns its slot, or -1 if the id is bad or the hand is
   full. */
s32 SzDuel_AddHand(s32 player, s32 card) {
    DuelHand *hand;

    hand = &DUEL_PLAYER(player)->hand;
    if (card == CARD_REJECTED) {
        card = CARD_NONE;
    }
    if (card < 0 || card >= CARD_COUNT) {
        return -1;
    }
    if (hand->count >= 5) {
        return -1;
    }
    SzDuel_PackHand(player);
    hand->cards[hand->count] = card & 0xFFF;
    return hand->count++;
}

/* Moves the cards of side `player`'s hand to the front, keeping their order and tags. */
void SzDuel_PackHand(s32 player) {
    DuelHand list;
    DuelHand *dest;
    s32 i;
    u16 *src;
    u16 entry;
    u16 *out;
    s32 count;

    dest = &DUEL_PLAYER(player)->hand;
    list.count = 0;
    i = 0;
    src = dest->cards;
    do {
        entry = *src;
        if ((entry & 0xFFF) != CARD_NONE) {
            list.cards[list.count++] = entry;
        }
        i++;
        src++;
    } while (i < 5);

    count = list.count;
    if (count < 5) {
        out = &list.cards[count];
        do {
            count++;
            *out++ = CARD_NONE;
        } while (count < 5);
    }

    *dest = list;
}

/* Empties hand slot `slot`. Returns 1 if there was a card. */
s32 SzDuel_DelHand(s32 player, s32 slot) {
    DuelHand *hand;
    u16 *entry;

    hand = &DUEL_PLAYER(player)->hand;
    if ((slot < 0) || (slot >= 5)) {
        return 0;
    }
    entry = &hand->cards[slot];
    if ((*entry & 0xFFF) == CARD_NONE) {
        return 0;
    }
    *entry = CARD_NONE;
    hand->count--;
    return 1;
}

/* Clears the pick-order tags of side `player`'s hand. */
s32 SzDuel_ClearHandTag(s32 player) {
    s32 i;
    u16 *entry;

    entry = DUEL_PLAYER(player)->hand.cards;
    i = 0;
    do {
        i += 1;
        *entry &= 0xFFF;
        entry++;
    } while (i < 5);
    return 1;
}

/* Tags hand slot `slot` with pick order `tag` (1..15), or with 0 removes its tag and moves the later tags down
   one. Returns 1 if it did. */
s32 SzDuel_SetHandTag(s32 player, s32 slot, s32 tag) {
    s32 oldTag;
    s32 otherTag;
    s32 i;
    u16 *entry;
    u16 *target;
    s32 value;
    s32 other;

    entry = DUEL_PLAYER(player)->hand.cards;
    if ((slot < 0) || (slot >= 5)) {
        return 0;
    }
    target = entry + slot;
    value = *target;
    if ((value & 0xFFF) == CARD_NONE) {
        return 0;
    }
    oldTag = (s32) (value & 0xF000) >> 0xC;
    if (tag == 0) {
        if (oldTag == 0) {
            return 0;
        }
        *target = value & 0xFFF;
        i = 0;
        do {
            other = *entry;
            if (i != slot) {
                if ((other & 0xFFF) != CARD_NONE) {
                    otherTag = (s32) (other & 0xF000) >> 0xC;
                    if ((otherTag != 0) && (oldTag < otherTag)) {
                        *entry = ((otherTag - 1) << 0xC) | (other & 0xFFF);
                    }
                }
            }
            i += 1;
            entry++;
        } while (i < 5);
    } else {
        if (oldTag != 0) {
            return 0;
        }
        *target = (tag << 0xC) | (value & 0xFFF);
    }
    return 1;
}

/* Side `player`'s life points. */
s32 SzDuel_GetLP(s32 player) {
    return DUEL_PLAYER(player)->lifePoints;
}

/* Applies `operation` (DUEL_CALC_ADD/SUB/MUL/DIV/SET) with `value` to side `player`'s life points, clamped to
   0..9999. Returns 0 for an unknown operation, 1 otherwise. */
s32 SzDuel_CalcLP(s32 player, s32 operation, s32 value) {
    s32 current;
    s32 result;
    DuelPlayer *side;

    side = DUEL_PLAYER(player);
    current = side->lifePoints;
    switch (operation) {
    case DUEL_CALC_ADD:
        result = current + value;
        break;
    case DUEL_CALC_SUB:
        result = current - value;
        break;
    case DUEL_CALC_MUL:
        result = current * value;
        break;
    case DUEL_CALC_DIV:
        result = current / value;
        break;
    case DUEL_CALC_SET:
        result = value;
        break;
    default:
        return 0;
    }

    value = result; /* this copy is kept for the match */
    value = (value > 0 ? value : 0) < 9999 ? (value > 0 ? value : 0) : 9999;
    side->lifePoints = value;
    return 1;
}

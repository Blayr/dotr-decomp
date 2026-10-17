#include "common.h"

typedef struct {
    u32 value0 : 31;
    u8 flag : 1;
    u32 value4 : 30;
    u8 flags : 2;
} Flags_00214FD0;

/* Clears a trunk entry. */
s32 SzData_ClearCardInfo(void *entry) {
    Flags_00214FD0 *flags = entry;

    if (entry == NULL) {
        return 0;
    }
    flags->value0 = 0;
    flags->value4 = 0;
    flags->flags = 3;
    flags->flag = 0;
    return 1;
}

typedef struct {
    u32 card : 31;
    u32 flag : 1;
    u32 value : 30;
    u32 valueFlags : 2;
} Entry_00215060;

typedef struct {
    Entry_00215060 entries[9];
    u8 unknown48;
    u8 flagsLow : 6;
    u8 assigned : 1;
    u8 flagsHigh : 1;
    u8 unknown4A[2];
} Card_00215060;

typedef struct {
    Card_00215060 cards[0x356];
    u8 unknownFD88[0x210];
    s32 defaultCard;
    s32 unknownFF9C;
} Player_00215060;

/* Whether side `side`'s trunk already holds the copy of card `card` from profile `owner` (0: its own) with serial
   `serial`; -1 for a bad id. */
s32 SzData_CheckDup(s32 sideIndex, s32 owner, u32 serial, s32 card) {
    extern u8 profileZeroSide;
    extern Player_00215060 saveProfiles[2];
    Entry_00215060 *entry;
    s32 n;

    if (sideIndex < 0 || sideIndex >= 2) {
        return -1;
    }
    if (owner == 0) {
        Player_00215060 *player;
        s32 side;

        side = (profileZeroSide == sideIndex) ? 0 : 1;
        player = &saveProfiles[side];
        owner = player->defaultCard;
    }
    if (owner == 0) {
        return -1;
    }
    if (card == 0x29F) {
        card = 0x3E7;
    }
    if (card < 0 || card >= 0x356) {
        return -1;
    }
    {
        s32 side;

        side = (profileZeroSide == sideIndex) ? 0 : 1;
        entry = (Entry_00215060 *)((u8 *)&saveProfiles[side] + card * 0x4C);
    }
    n = 9;
    while (n-- != 0) {
        if (entry->card != 0) {
            if (entry->value == serial) {
                return 1;
            }
        }
        entry++;
    }
    return 0;
}

typedef struct {
    u16 entries[40];
    u8 pad_50[4];
} EntryList_002151D0;

typedef struct {
    u8 pad_0[0xFD94];
    EntryList_002151D0 lists[6];
    u8 pad_FF8C[0x14];
} SideData_002151D0;

extern u8 profileZeroSide; /* original: gSzData_bRoseFlag */

/* Whether deck `deck` of side `side` can use card `card` (it owns enough copies). */
s32 SzData_CheckDeck(s32 player, s32 deck, s32 card) {
    extern SideData_002151D0 saveProfiles[];
    s32 i;
    s32 side;
    u16 *entries;

    if (profileZeroSide == player) {
        side = 0;
    } else {
        side = 1;
    }
    entries = (u16 *)(deck * 0x54 + (u8 *)&saveProfiles[side] + 0xFD94);
    if (player < 0 || player >= 2) {
        return -1;
    }
    i = 0;
    do {
        if (card == *entries) {
            return i;
        }
        i++;
        entries++;
    } while (i < 40);
    return -1;
}

typedef struct {
    u8 pad0[3];
    u8 flags3 : 7;
    u8 active : 1;
    u8 pad4[3];
    u8 flags7 : 6;
    u8 slot : 2;
} Card_00215280;

typedef u8 Slot_00215280[0x54];

extern u8 profileZeroSide; /* original: gSzData_bRoseFlag */

/* Makes card `card` the leader of deck `deck` of side `side`. */
s32 SzData_PushDeckLeader(s32 side, s32 deck, s32 card) {
    extern u8 saveProfiles[];
    s32 var_v1;
    u8 *temp_s2;
    Card_00215280 *checkBag;

    if (profileZeroSide == side) {
        var_v1 = 0;
    } else {
        var_v1 = 1;
    }
    temp_s2 = ((Slot_00215280 *)(saveProfiles + (var_v1 * 0xFFA0)))[deck] + 0x7D9C + 0x7FF8;
    if ((side < 0) || (side >= 2)) {
        return 0;
    }
    if (card == 0x29F) {
        card = 0x3E7;
    }
    if ((card < 0) || (card >= 0x356)) {
        return 0;
    }
    if (*(u16 *)(temp_s2 + 0x50) != 0x3E7) {
        return 0;
    }
    checkBag = SzData_CheckBag(side, card, 3, 0);
    if (checkBag == NULL) {
        return 0;
    }
    *(u16 *)(temp_s2 + 0x50) = (u16)card;
    checkBag->slot = deck;
    checkBag->active = 1;
    return 1;
}

typedef struct Slot_002153D0 {
    u8 pad[0x50];
    u16 card;
    u8 pad52[2];
} Slot_002153D0;

typedef struct Side_002153D0 {
    u8 pad0[0xFD94];
    Slot_002153D0 slots[6];
    u8 pad_end[0x14];
} Side_002153D0;

typedef struct Card_002153D0 {
    u8 pad0[3];
    u8 flags3 : 7;
    u8 flag : 1;
    u8 pad4[3];
    u8 flags7 : 6;
    u8 state : 2;
} Card_002153D0;

extern u8 profileZeroSide; /* original: gSzData_bRoseFlag */

/* Takes the leader out of deck `deck` of side `side`. */
s32 SzData_PullDeckLeader(s32 player, s32 deck) {
    extern Side_002153D0 saveProfiles[];
    s32 side;
    u16 card;
    Slot_002153D0 *slot;
    Card_002153D0 *entry;

    if (profileZeroSide == player) {
        side = 0;
    } else {
        side = 1;
    }
    slot = (Slot_002153D0 *)((u8 *)&saveProfiles[side] + deck * 0x54 + 0xFD94);
    if (player < 0 || player >= 2) {
        return 0;
    }
    card = slot->card;
    if (card == 999) {
        return 0;
    }
    entry = SzData_CheckBag(player, card, deck, 1);
    if (entry == NULL) {
        return 0;
    }
    slot->card = 999;
    entry->state = 3;
    entry->flag = 0;
    return 1;
}

typedef struct {
    u16 cards[40];
    u16 unknown;
    u16 cost;
} Deck_002154E0;

typedef struct {
    u8 pad[0xFD94];
    Deck_002154E0 decks[6];
    u8 pad_end[0x14];
} Side_002154E0;

typedef struct {
    u8 pad[7];
    u8 flags7 : 6;
    u8 deck : 2;
} Entry_002154E0;

extern u8 profileZeroSide; /* original: gSzData_bRoseFlag */

/* How many copies of a card a deck holds. */
static inline s32 count_002154E0(s32 player, s32 deck_index, s32 card_id) {
    extern Side_002154E0 saveProfiles[];
    s32 side;
    u16 *cards;
    s32 count;
    s32 i;

    if (profileZeroSide == player) {
        side = 0;
    } else {
        side = 1;
    }
    cards = (u16 *)((u8 *)&saveProfiles[side] + deck_index * 0x54 + 0xFD94);
    count = 0;
    if (player < 0 || player >= 2) {
        return -1;
    }
    for (i = 0; i < 40; i++, cards++) {
        if (card_id == *cards) {
            count++;
        }
    }
    return count;
}

/* The slot of a card in a deck, or -1. */
static inline s32 find_002154E0(s32 player, s32 deck_index, s32 card_id) {
    extern Side_002154E0 saveProfiles[];
    s32 side;
    u16 *cards;
    s32 i;

    if (profileZeroSide == player) {
        side = 0;
    } else {
        side = 1;
    }
    cards = (u16 *)((u8 *)&saveProfiles[side] + deck_index * 0x54 + 0xFD94);
    if (player < 0 || player >= 2) {
        return -1;
    }
    for (i = 0; i < 40; i++, cards++) {
        if (*cards == card_id) {
            return i;
        }
    }
    return -1;
}

/* Adds card `card_id` to deck `deck_index` of side `player` (if it owns another copy). */
s32 SzData_PushDeck(s32 player, s32 deck_index, s32 card_id) {
    extern Side_002154E0 saveProfiles[];
    s32 side;
    Deck_002154E0 *deck;
    Entry_002154E0 *entry;
    u8 *card;
    s32 slot;

    if (profileZeroSide == player) {
        side = 0;
    } else {
        side = 1;
    }
    deck = (Deck_002154E0 *)((u8 *)&saveProfiles[side] + deck_index * 0x54 + 0xFD94);
    if (player < 0 || player >= 2) {
        return 0;
    }
    if (card_id == 0x29F) {
        card_id = 999;
    }
    if (card_id < 0 || card_id >= 0x356) {
        return 0;
    }
    if (count_002154E0(player, deck_index, card_id) >= 3) {
        return 0;
    }
    slot = find_002154E0(player, deck_index, 999);
    if (slot < 0) {
        return 0;
    }
    if ((entry = SzData_CheckBag(player, card_id, 3, 0)) == NULL) {
        return 0;
    }
    card = SzDuel_GetCardConstInfo(card_id);
    if (card == NULL) {
        return 0;
    }
    deck->cost += card[3];
    deck->cards[slot] = card_id;
    entry->deck = deck_index;
    return 1;
}

extern u8 profileZeroSide; /* original: gSzData_bRoseFlag */

typedef struct {
    u8 pad[7];
    u8 flags : 6;
    u8 state : 2;
} Card_00215770;

/* Takes card `card` out of deck `deck` of side `side`. */
s32 SzData_PullDeck(s32 player, s32 deck, s32 pullCard) {
    extern u8 saveProfiles[];
    u8 *hand;
    Card_00215770 *card;
    u16 *slot;
    s32 cardId;
    s32 side;
    u8 *info;

    if (profileZeroSide == player) {
        side = 0;
    } else {
        side = 1;
    }
    hand = (u8 *)((u32)saveProfiles + side * 0xFFA0 + deck * 0x54) + 0x7D9C + 0x7FF8;
    if ((player < 0) || (player >= 2)) {
        return 0;
    }
    if ((pullCard < 0) || (pullCard >= 0x28)) {
        return 0;
    }
    slot = (u16 *)(hand + pullCard * 2);
    cardId = *slot;
    if ((card = SzData_CheckBag(player, cardId, deck, 0)) == NULL) {
        return 0;
    }
    info = SzDuel_GetCardConstInfo(cardId);
    if (info == NULL) {
        return 0;
    }
    *(u16 *)(hand + 0x52) -= info[3];
    *slot = 0x3E7;
    card->state = 3;
    return 1;
}

typedef struct {
    u8 pad[0xFF9C];
    u8 flags;
    u8 tail[3];
} State_002158B0;

extern State_002158B0 saveProfiles[]; /* original: gSzData_All */
extern u8 profileZeroSide; /* original: gSzData_bRoseFlag */

/* Which deck (0..2) side `side` uses. */
s32 SzData_GetCurrentDeck(s32 side) {
    s32 var_v1;
    State_002158B0 *state;

    if (profileZeroSide == side) {
        var_v1 = 0;
    } else {
        var_v1 = 1;
    }
    state = &saveProfiles[var_v1];
    if ((side < 0) || (side >= 2)) {
        return -1;
    }
    return state->flags & 3;
}

extern u8 profileZeroSide; /* original: gSzData_bRoseFlag */

typedef struct {
    u8 padding[0xFF9C];
    u8 mode : 2;
    u8 : 6;
} Flags_00215920;

/* Makes deck `deck` (0..2) the one side `side` uses. */
s32 SzData_SetCurrentDeck(s32 side, s32 deck) {
    s32 var_v1;
    u8 *temp_a2;

    if (profileZeroSide == side) {
        var_v1 = 0;
    } else {
        var_v1 = 1;
    }
    temp_a2 = (u8 *)saveProfiles + (var_v1 * 0xFFA0);
    if ((side < 0) || (side >= 2)) {
        return 0;
    }
    if ((deck < 0) || (deck >= 3)) {
        return 0;
    }
    ((Flags_00215920 *)temp_a2)->mode = deck;
    return 1;
}

typedef struct {
    u8 padding[0x50];
    u16 value;
    u8 padding_52[2];
} Entry_002159D0;

extern u8 profileZeroSide; /* original: gSzData_bRoseFlag */

/* The save profile of a duel side. */
static inline s32 side_002159D0(s32 player) {
    if (profileZeroSide == player) {
        return 0;
    }
    return 1;
}

/* The leader of deck `deck` of side `side` (CARD_NONE for none). */
s32 SzData_GetLeader(s32 player, s32 deck) {
    u8 *side;
    Entry_002159D0 *entry;

    side = (u8 *)saveProfiles + side_002159D0(player) * 0xFFA0;
    entry = (Entry_002159D0 *)(side + deck * sizeof(Entry_002159D0) + 0xFD94);
    if ((player < 0) || (player >= 2)) {
        return -1;
    }
    return entry->value;
}

#ifndef GAME_H
/* The game translation unit already declares this array with its local type. */
extern unsigned char saveProfiles[]; /* original: gSzData_All */
#endif


typedef struct Row_00215A60 {
    u16 values[40];
    u8 pad[4];
} Row_00215A60;

typedef struct Side_00215A60 {
    u8 pad[0xFD94];
    Row_00215A60 rows[6];
    u8 tail[0x14];
} Side_00215A60;

extern u8 profileZeroSide; /* original: gSzData_bRoseFlag */

/* Card `slot` (0..39) of deck `deck` of side `side`. */
s32 SzData_GetCardNo(s32 side, s32 deck, s32 slot) {
    s32 var_v1;
    u16 *values;

    if (profileZeroSide == side) {
        var_v1 = 0;
    } else {
        var_v1 = 1;
    }
    values = ((Side_00215A60 *)saveProfiles)[var_v1].rows[deck].values;
    if ((side < 0) || (side >= 2)) {
        return -1;
    }
    if ((slot < 0) || (slot >= 0x28)) {
        return -1;
    }
    return values[slot];
}

typedef struct Record_00215B10 {
    u8 padding[0x4A];
    u16 value;
} Record_00215B10;

/* Applies `operation` (DUEL_CALC_*) with `value` to side `side`'s experience with card `card`, clamped to
   0..0xFFFF. */
s32 SzData_CalcExp(s32 sideIndex, s32 card, s32 operation, s32 value) {
    s32 side;
    u8 *player;
    Record_00215B10 *record;
    s32 current;
    s32 result;

    side = 1;
    if (profileZeroSide == sideIndex) {
        side = 0;
    }
    player = (u8 *)&saveProfiles[side];
    if ((sideIndex < 0) || (sideIndex >= 2)) {
        return 0;
    }
    if (card == 0x29F) {
        card = 0x3E7;
    }
    if ((card < 0) || (card >= 0x356)) {
        return 0;
    }
    record = (Record_00215B10 *)(player + card * 0x4C);
    current = record->value;
    switch (operation) {
    case 0:
        result = current + value;
        break;
    case 1:
        result = current - value;
        break;
    case 2:
        result = current * value;
        break;
    case 3:
        result = current / value;
        break;
    case 4:
        result = value;
        break;
    default:
        return 0;
    }

    value = result;
    value = (value > 0 ? value : 0) < 0xFFFF ? (value > 0 ? value : 0) : 0xFFFF;
    record->value = value;
    return 1;
}

/* Works out the deck cost of deck `deck` of side `side`. */
s32 SzData_CalcDeckCost(s32 player, s32 deckNo) {
    typedef struct {
        u16 cards[40];
        u16 unk50;
        u16 total;
    } Deck_00215C40;
    Deck_00215C40 *deck;
    s32 i;
    u16 *card;
    s32 side;
    u8 *data;

    if (profileZeroSide == player) {
        side = 0;
    } else {
        side = 1;
    }
    deck = (Deck_00215C40 *)((u8 *)saveProfiles + side * 0xFFA0 + deckNo * sizeof(Deck_00215C40) + 0xFD94);
    if ((player < 0) || (player >= 2)) {
        return -1;
    }
    deck->total = 0;
    i = 0;
    card = deck->cards;
    do {
        data = SzDuel_GetCardConstInfo(*card);
        if (data != NULL) {
            deck->total += data[3];
        }
        i++;
        card++;
    } while (i < 40);
    return deck->total;
}

typedef struct Card_00215D30 {
    u8 padding[0x48];
    u64 rank : 14;
    u64 flags : 2;
    u64 rest : 48;
} Card_00215D30;

/* Side `side`'s rank (leader level) for card `card` (cards below 0x2AB), or -1. */
s64 SzData_GetRank(s32 player, s32 card) {
    s32 side;
    u8 *base;

    if (profileZeroSide == player) {
        side = 0;
    } else {
        side = 1;
    }
    base = (u8 *)saveProfiles + side * 0xFFA0;
    if ((player < 0) || (player >= 2)) {
        return -1;
    }
    if (card == 0x29F) {
        card = 0x3E7;
    }
    if ((card < 0) || (card >= 0x2AB)) {
        return -1;
    }
    return ((Card_00215D30 *)(base + card * 0x4C))->rank;
}

typedef struct Card_00215DE0 {
    u8 padding[0x48];
    u16 rank : 14;
    u16 flags : 2;
    u16 experience;
} Card_00215DE0;

extern u16 D_002D0868;
extern u8 profileZeroSide; /* original: gSzData_bRoseFlag */

/* Raises side `player`'s leader rank for card `index` from its experience. */
s32 SzData_SetRank(s32 player, s32 index) {
    s32 side;
    u8 *base;
    Card_00215DE0 *card;
    s32 rank;
    u16 *threshold;

    if (profileZeroSide == player) {
        side = 0;
    } else {
        side = 1;
    }
    base = (u8 *)saveProfiles + side * 0xFFA0;
    if (player < 0 || player >= 2) {
        return -1;
    }
    if (index == 0x29F) {
        index = 0x3E7;
    }
    if (index < 0 || index >= 0x2AB) {
        return -1;
    }
    card = (Card_00215DE0 *)(base + index * sizeof(Card_00215DE0));
    rank = 12;
    threshold = &D_002D0868;
    for (; rank >= 0; rank--, threshold--) {
        if (card->experience >= *threshold) {
            break;
        }
    }
    if (card->rank != 0) {
        rank = rank > 1 ? rank : 1;
    }
    card->rank = rank;
    return card->rank;
}

typedef struct {
    u8 padding[0x52];
    u16 value;
} Entry_00215F00;

extern u8 profileZeroSide; /* original: gSzData_bRoseFlag */

/* The save profile of a duel side. */
static inline s32 side_00215F00(s32 player) {
    if (profileZeroSide == player) {
        return 0;
    }
    return 1;
}

/* The deck cost of deck `deck` of side `side`. */
s32 SzData_GetDeckCost(s32 player, s32 deck) {
    u8 *side;
    Entry_00215F00 *entry;

    side = (u8 *)saveProfiles + side_00215F00(player) * 0xFFA0;
    entry = (Entry_00215F00 *)(side + deck * sizeof(Entry_00215F00) + 0xFD94);
    if ((player < 0) || (player >= 2)) {
        return -1;
    }
    return entry->value;
}

/* How many cards deck `deck` of side `side` holds. */
s32 SzData_GetDeckCount(s32 player, s32 deck) {
    s32 i;
    s32 count;
    s32 side;
    u16 *card;

    if (profileZeroSide == player) {
        side = 0;
    } else {
        side = 1;
    }
    card = (u16 *)((u8 *)saveProfiles + side * 0xFFA0 + deck * 0x54 + 0xFD94);
    count = 0;
    if ((player < 0) || (player >= 2)) {
        return -1;
    }
    i = 0;
    do {
        if (*card != 0x3E7) {
            count++;
        }
        i++;
        card++;
    } while (i < 0x28);
    return count;
}

typedef struct {
    u32 card : 31;
    u32 flag : 1;
    u32 value : 30;
    u32 valueFlags : 2;
} Entry_00216040;

typedef struct {
    Entry_00216040 entries[9];
    u8 unknown48;
    u8 flagsLow : 6;
    u8 assigned : 1;
    u8 flagsHigh : 1;
    u8 unknown4A[2];
} Card_00216040;

typedef struct {
    Card_00216040 cards[0x356];
    u8 unknownFD88[0x210];
    s32 defaultCard;
    s32 unknownFF9C;
} Player_00216040;


/* The save profile of a duel side. */
static inline s32 side_00216040(s32 player) {
    extern u8 profileZeroSide;
    if (profileZeroSide == player) {
        return 0;
    }
    return 1;
}

/* A side's save profile. */
static inline Player_00216040 *data_00216040(s32 player, void *base) {
    return &((Player_00216040 *)base)[side_00216040(player)];
}

/* A random number. */
static inline s64 random_value_00216040(void) {
    extern s64 func_0019A5C8();
    return (s32)func_0019A5C8() & ~0x40000000LL;
}

/* Adds a copy of card `card` to side `side`'s trunk, from profile `owner` (0: its own) with a new serial. */
s32 SzData_AddBag(s32 side, s32 owner, s32 cardId) {
    Card_00216040 *card;
    Entry_00216040 *entry;
    s32 count;

    if (side < 0 || side >= 2) {
        return 0;
    }
    if (owner == 0) {
        owner = data_00216040(side, saveProfiles)->defaultCard;
    }
    if (owner == 0) {
        return 0;
    }
    if (cardId == 0x29F) {
        cardId = 0x3E7;
    }
    if (cardId < 0 || cardId >= 0x356) {
        return 0;
    }

    card = (Card_00216040 *)data_00216040(side, saveProfiles) + cardId;
    entry = card->entries;
    for (count = 9; count-- != 0; entry++) {
        if (entry->card == 0) {
            do {
                entry->value = random_value_00216040();
            } while (SzData_CheckDup(side, owner, entry->value, cardId) != 0);
            entry->card = owner;
            card->assigned = 1;
            SzData_PushBagNew(side, cardId);
            return 1;
        }
    }
    return 0;
}

typedef struct {
    u32 card : 31;
    u32 flag : 1;
    u32 value : 30;
    u32 valueFlags : 2;
} Entry_00216280;

typedef struct {
    Entry_00216280 entries[9];
    u8 unknown48;
    u8 flagsLow : 6;
    u8 assigned : 1;
    u8 flagsHigh : 1;
    u8 unknown4A[2];
} Card_00216280;

typedef struct {
    Card_00216280 cards[0x356];
    u8 unknownFD88[0x210];
    s32 defaultCard;
    s32 unknownFF9C;
} Player_00216280;


/* The save profile of a duel side. */
static inline s32 side_00216280(s32 player) {
    extern u8 profileZeroSide;
    if (profileZeroSide == player) {
        return 0;
    }
    return 1;
}

/* A side's save profile. */
static inline Player_00216280 *data_00216280(s32 player, void *base) {
    return &((Player_00216280 *)base)[side_00216280(player)];
}

/* Adds the copy of card `card` from profile `owner` (0: its own) with serial `serial` to side `side`'s trunk,
   unless it is already there. */
s32 SzData_AddBag2(s32 side, s32 owner, s32 serial, s32 cardId) {
    Card_00216280 *card;
    Entry_00216280 *entry;
    s32 count;

    if (side < 0 || side >= 2) {
        return 0;
    }
    if (owner == 0) {
        owner = data_00216280(side, saveProfiles)->defaultCard;
    }
    if (owner == 0) {
        return 0;
    }
    if (cardId == 0x29F) {
        cardId = 0x3E7;
    }
    if (cardId < 0 || cardId >= 0x356) {
        return 0;
    }
    if (SzData_CheckDup(side, owner, serial, cardId) != 0) {
        return 0;
    }

    card = (Card_00216280 *)data_00216280(side, saveProfiles) + cardId;
    entry = card->entries;
    for (count = 9; count-- != 0; entry++) {
        if (entry->card == 0) {
            entry->value = serial;
            entry->card = owner;
            card->assigned = 1;
            SzData_PushBagNew(side, cardId);
            return 1;
        }
    }
    return 0;
}

typedef struct Flags_00216490 {
    u32 value0 : 31;
    u32 flag0 : 1;
    u32 value1 : 30;
    u32 flag1 : 2;
} Flags_00216490;


/* Clears a trunk entry. */
static inline void clear_00216490(void *src) {
    Flags_00216490 *entry = (Flags_00216490 *)src;

    if (entry != NULL) {
        entry->value0 = 0;
        entry->value1 = 0;
        entry->flag1 = 3;
        entry->flag0 = 0;
    }
}

/* Takes one copy of card `card` out of side `side`'s trunk. */
s32 SzData_DelBag(s32 side, s32 card) {
    Flags_00216490 *entry;

    if ((side < 0) || (side >= 2)) {
        return 0;
    }
    if (card == 0x29F) {
        card = 0x3E7;
    }
    if ((card < 0) || (card >= 0x356)) {
        return 0;
    }
    entry = SzData_CheckBag(side, card, 3, 0);
    if (entry == NULL) {
        return 0;
    }
    clear_00216490(entry);
    return 1;
}

#ifndef GAME_H
/* The game translation unit already declares this array with its local type. */
typedef struct {
    unsigned char pad[0xFF9C];
    unsigned char flags;
    unsigned char tail[3];
} State_002158B0;
extern State_002158B0 saveProfiles[]; /* original: gSzData_All */
#endif


typedef struct {
    u16 card;
    u16 field_2;
    u16 field_4;
} Entry_00216580;

typedef struct {
    u8 unused : 6;
    u8 count : 2;
} Flags_00216580;

extern Entry_00216580 specialCards[]; /* original: aSpecialCard */
extern u8 profileZeroSide; /* original: gSzData_bRoseFlag */

/* Side `sideIndex` got card `card`: if it is one of the 16 special-card entries, steps that entry's counter
   (save 0xFE90 + i) to its next alternative, wrapping. */
s32 SzData_RollSpecial(s32 sideIndex, s32 card) {
    s32 i;
    State_002158B0 *player;
    Entry_00216580 *entry;
    s32 side;
    s32 decodedCard;
    u8 *count;

    if ((sideIndex < 0) || (sideIndex >= 2)) {
        return 0;
    }
    if (card == 0x29F) {
        card = 0x3E7;
    }
    if ((card < 0) || (card >= 0x356)) {
        return 0;
    }
    if (profileZeroSide == sideIndex) {
        side = 0;
    } else {
        side = 1;
    }
    player = &saveProfiles[side];
    entry = specialCards;
    i = 0;
    do {
        decodedCard = SzDuel_Xax2New(entry->card & 0x3FFF);
        if (decodedCard == card) {
            count = (u8 *)(i + (u32)player) + 0xFE90;
            *count = (*count + 1) % (((Flags_00216580 *)&specialCards[i])[1].count + 1);
            return 1;
        }
        i++;
        entry++;
    } while (i < 16);
    return 0;
}

#ifndef GAME_H
/* The game translation unit already declares these globals with its local types. */
typedef struct {
    unsigned char pad[0xFF9C];
    unsigned char flags;
    unsigned char tail[3];
} State_002158B0;

typedef struct {
    unsigned short card;
    unsigned short field_2;
    unsigned short field_4;
} Entry_00216580;

extern State_002158B0 saveProfiles[]; /* original: gSzData_All */
extern Entry_00216580 specialCards[]; /* original: aSpecialCard */
#endif


typedef struct State_002166D0 {
    u8 unk_0000[0xFE90];
    u8 replacements[16];
    u8 unk_FEA0[0x100];
} State_002166D0;

extern u8 profileZeroSide; /* original: gSzData_bRoseFlag */

/* The card side `side` actually holds for card `card`: a special card if it has unlocked one in its place. */
s32 SzData_ExchSpecial(s32 player, s32 card) {
    State_002166D0 *state;
    Entry_00216580 *entry;
    s32 side;
    s32 replacement;
    s32 resolved;

    if ((player < 0) || (player >= 2)) {
        return card;
    }
    if (card == 0x29F) {
        card = 0x3E7;
    }
    if ((card < 0) || (card >= 0x356)) {
        return card;
    }
    if (profileZeroSide == player) {
        side = 0;
    } else {
        side = 1;
    }
    {
        s32 i;

        state = (State_002166D0 *)saveProfiles + side;
        entry = specialCards;
        i = 0;
        do {
            resolved = SzDuel_Xax2New(entry->card & 0x3FFF);
            if (resolved == card) {
                replacement = state->replacements[i];
                if (replacement != 0) {
                    card = (&specialCards[i].card)[replacement];
                }
                break;
            }
            i++;
            entry++;
        } while (i < 16);
    }
    return card;
}

#ifndef GAME_H
/* The game translation unit already declares this array with its local type. */
extern unsigned char saveProfiles[]; /* original: gSzData_All */
#endif


typedef struct Record_00216800 {
    u8 pad[0xFD88];
    u16 entries[5];
    u8 pad_end[0x20E];
} Record_00216800;

extern u8 profileZeroSide; /* original: gSzData_bRoseFlag */

/* Puts card `card` at the front of side `side`'s five-newest-cards list (save 0xFD88). */
s32 SzData_PushBagNew(s32 side, s32 card) {
    s32 record_index;
    s32 i;
    Record_00216800 *record;

    if (profileZeroSide == side) {
        record_index = 0;
    } else {
        record_index = 1;
    }
    record = &((Record_00216800 *)saveProfiles)[record_index];
    if ((side < 0) || (side >= 2)) {
        return 0;
    }
    if (card == 0x29F) {
        card = 0x3E7;
    }
    if ((card < 0) || (card >= 0x356)) {
        return 0;
    }
    for (i = 0; i < 5; i++) {
        if ((record->entries[i] == card) || (i + 1 >= 5)) {
            while (i > 0) {
                record->entries[i] = record->entries[i - 1];
                i--;
            }
            break;
        }
    }
    record->entries[0] = card;
    return 1;
}

#ifndef GAME_H
/* The game translation unit already declares this array with its local type. */
extern unsigned char saveProfiles[]; /* original: gSzData_All */
#endif


typedef struct {
    u8 padding[0xFD88];
    u16 card;
} Entry_00216920;

extern u8 profileZeroSide; /* original: gSzData_bRoseFlag */

/* Whether card `card` is marked new in side `side`'s trunk. */
s32 SzData_IsBagNew(s32 player, s32 card) {
    s32 side;
    s32 i;
    u8 *data;

    if (player < 0 || player >= 2) {
        return 0;
    }
    if (card == 0x29F) {
        card = 0x3E7;
    }
    if (card < 0 || card >= 0x356) {
        return 0;
    }
    if (profileZeroSide == player) {
        side = 0;
    } else {
        side = 1;
    }
    data = (u8 *)saveProfiles + side * 0xFFA0;
    i = 0;
    do {
        if (((Entry_00216920 *)data)->card == card) {
            return 1;
        }
        i++;
        data += 2;
    } while (i < 5);
    return 0;
}

#ifndef GAME_H
/* The game translation unit already declares this array with its local type. */
extern unsigned char saveProfiles[]; /* original: gSzData_All */
#endif


typedef struct {
    u32 value : 31;
    u32 flag : 1;
    u8 pad[3];
    u8 flags : 6;
    u8 type : 2;
} Entry_002169F0;

extern u8 profileZeroSide; /* original: gSzData_bRoseFlag */

/* How many cards side `side`'s trunk holds. */
s32 SzData_GetBagCountAll(s32 player) {
    s32 rowIndex;
    Entry_002169F0 *entry;
    s32 remaining;
    s32 count;
    s32 side;
    u8 *row;

    side = profileZeroSide == player ? 0 : 1;
    row = (u8 *)saveProfiles + (side * 0xFFA0);
    count = 0;
    if ((player < 0) || (player >= 2)) {
        return -1;
    }
    rowIndex = 0;
    do {
        remaining = 9;
        entry = (Entry_002169F0 *) row;
        while (remaining--) {
            if (entry->value != 0) {
                if (entry->type == 3) {
                    count += 1;
                }
            }
            entry++;
        }
        rowIndex += 1;
        row += 0x4C;
    } while (rowIndex < 0x356);
    return count;
}

#ifndef GAME_H
/* The game translation unit already declares this array with its local type. */
extern unsigned char saveProfiles[]; /* original: gSzData_All */
#endif


typedef struct {
    u32 value : 31;
    u32 flag : 1;
    u8 padding[3];
    u8 unused : 6;
    u8 category : 2;
} Entry_00216AC0;

extern u8 profileZeroSide; /* original: gSzData_bRoseFlag */

/* How many copies of card `card` side `player` owns in `category` (-1 for any). */
s32 SzData_GetBagCount(s32 player, s32 card, s32 category) {
    Entry_00216AC0 *entry;
    s32 remaining;
    s32 count;

    count = 0;
    if ((player < 0) || (player >= 2)) {
        return -1;
    }
    if (card == 0x29F) {
        card = 0x3E7;
    }
    if ((card < 0) || (card >= 0x356)) {
        return -1;
    }
    if (profileZeroSide == player) {
        player = 0;
    } else {
        player = 1;
    }
    entry = (Entry_00216AC0 *)((u8 *)saveProfiles + (player * 0xFFA0));
    entry = (Entry_00216AC0 *)((u8 *)entry + (card * 0x4C));
    remaining = 9;
    while (remaining--) {
        if (entry->value != 0) {
            if ((category < 0) || (entry->category == category)) {
                count += 1;
            }
        }
        entry++;
    }
    return count;
}

#ifndef GAME_H
/* The game translation unit already declares this array with its local type. */
extern unsigned char saveProfiles[]; /* original: gSzData_All */
#endif


typedef struct Flags_00216BC0 {
    u8 unused : 6;
    u8 active : 1;
    u8 unused2 : 1;
} Flags_00216BC0;

extern u8 profileZeroSide; /* original: gSzData_bRoseFlag */

/* Whether side `side` has seen card `card` (the library). */
s32 SzData_GetLookFlag(s32 side, s32 card) {
    extern s32 SD_iPreparePreBlockOnIOP();
    s32 var_v1;
    u8 *cards;

    if (profileZeroSide == side) {
        var_v1 = 0;
    } else {
        var_v1 = 1;
    }
    cards = (u8 *)saveProfiles + var_v1 * 0xFFA0;
    if ((side < 0) || (side >= 2)) {
        return 0;
    }
    if ((card < 0) || (card >= 0x356)) {
        return 0;
    }
    return ((Flags_00216BC0 *)(cards + card * 0x4C + 0x49))->active ? 1 : 0;
}

#ifndef GAME_H
/* The game translation unit already declares this array with its local type. */
extern unsigned char saveProfiles[]; /* original: gSzData_All */
#endif


typedef struct Card_00216C70 {
    u8 padding[0x49];
    u8 flags : 6;
    u8 selected : 1;
    u8 flag7 : 1;
    u8 padding4A[2];
} Card_00216C70;

extern u8 profileZeroSide; /* original: gSzData_bRoseFlag */

/* Marks card `card` as seen by side `side`. */
s32 SzData_SetLookFlag(s32 side, s32 cardId, s32 on) {
    s32 var_v1;
    Card_00216C70 *cards;
    Card_00216C70 *card;

    var_v1 = (profileZeroSide == side) ? 0 : 1;
    cards = (Card_00216C70 *)((u8 *)saveProfiles + var_v1 * 0xFFA0);
    if ((side < 0) || (side >= 2)) {
        return 0;
    }
    if ((cardId < 0) || (cardId >= 0x356)) {
        return 0;
    }
    card = &cards[cardId];
    card->selected = on ? 1 : 0;
    return 1;
}

/* Whether side `side` has used card password `card`. */
s32 SzData_GetPassFlag(s32 player, s32 card) {
    typedef struct {
        u8 pad[0x49];
        u8 unused : 7;
        u8 enabled : 1;
        u8 tail[2];
    } Card_00216D30;
    s32 side;
    Card_00216D30 *cards;

    if (profileZeroSide == player) {
        side = 0;
    } else {
        side = 1;
    }
    cards = (Card_00216D30 *)&saveProfiles[side];
    if ((player < 0) || (player >= 2)) {
        return 0;
    }
    if (card == 0x29F) {
        card = 0x3E7;
    }
    if ((card < 0) || (card >= 0x356)) {
        return 0;
    }
    return cards[card].enabled ? 1 : 0;
}

typedef struct {
    u8 pad[0x49];
    u8 other_flags : 7;
    u8 enabled : 1;
    u8 pad_4A[2];
} Card_00216DF0;

extern u8 profileZeroSide; /* original: gSzData_bRoseFlag */

/* Marks card password `card` as used by side `side`. */
s32 SzData_SetPassFlag(s32 player, s32 cardId, s32 on) {
    s32 side;
    u8 *table;
    Card_00216DF0 *card;

    if (profileZeroSide == player) {
        side = 0;
    } else {
        side = 1;
    }
    table = (u8 *)saveProfiles + side * 0xFFA0;
    if ((player < 0) || (player >= 2)) {
        return 0;
    }
    if (cardId == 0x29F) {
        cardId = 0x3E7;
    }
    if ((cardId < 0) || (cardId >= 0x356)) {
        return 0;
    }
    card = (Card_00216DF0 *)(table + cardId * 0x4C);
    card->enabled = on ? 1 : 0;
    return 1;
}

/* Whether side `side` has found treasure `treasure`. */
s32 SzData_GetTreasureFlag(s32 side, s32 treasure) {
    s32 index;
    u8 *data;
    s32 flags;

    index = (profileZeroSide == side) ? 0 : 1;
    data = (u8 *)saveProfiles + index * 0xFFA0;
    if ((side < 0) || (side >= 2)) {
        return 0;
    }
    if ((treasure < 0) || (treasure >= 0x16)) {
        return 0;
    }
    flags = data[0xFEA0 + (treasure >> 3)];
    return (flags & (1 << (treasure % 8))) ? 1 : 0;
}

#ifndef GAME_H
extern unsigned char saveProfiles[]; /* original: gSzData_All */
#endif


typedef struct PlayerState_00216F80 {
    u8 pad[0xFEA0];
    u8 flags[0x100];
} PlayerState_00216F80;

extern u8 profileZeroSide; /* original: gSzData_bRoseFlag */

/* The save profile of a duel side. */
static inline s32 player_index_00216F80(s32 player) {
    if (profileZeroSide == player) {
        return 0;
    }
    return 1;
}

/* Marks treasure `flag` as found by side `player`. */
s32 SzData_SetTreasureFlag(s32 player, s32 flag, s32 enabled) {
    PlayerState_00216F80 *state;

    state = &((PlayerState_00216F80 *)saveProfiles)[player_index_00216F80(player)];
    if (player < 0 || player >= 2) {
        return 0;
    }
    if (flag < 0 || flag >= 22) {
        return 0;
    }
    if (enabled != 0) {
        state->flags[flag >> 3] |= (u8)(1 << (flag % 8));
    } else {
        state->flags[flag >> 3] &= (u8)~(1 << (flag % 8));
    }
    return 1;
}

typedef struct Entry_002170A0 {
    u8 id;
    u8 x : 4;
    u8 y : 4;
    u16 value;
} Entry_002170A0;

extern Entry_002170A0 treasureData[]; /* original: aTreasureData */
extern u16 D_002D08D2[];

/* The treasure on campaign map square (x, y) of side `side`'s map `map`, if not found yet. */
u16 SzData_SearchTreasure(s32 side, s32 map, s32 x, s32 y) {
    s32 i;
    Entry_002170A0 *entry;
    s32 dx;
    s32 dy;

    if (y <= 0) {
        return 999;
    }
    if (side < 0 || side >= 22) {
        return 999;
    }
    if (map < 0 || map >= 7 || x < 0 || x >= 7) {
        return 999;
    }

    entry = treasureData;
    i = 0;
    do {
        if (side == entry->id) {
            dx = entry->x - map;
            dx = dx >= 0 ? dx : -dx;
            if (dx < y) {
                dy = entry->y - x;
                dy = dy >= 0 ? dy : -dy;
                if (dy < y) {
                    return D_002D08D2[i * 2];
                }
            }
        }
        i++;
        entry++;
    } while (i < 22);

    return 999;
}

#ifndef GAME_H
/* The game translation unit already declares this array with its local type. */
typedef struct {
    unsigned char pad[0xFF9C];
    unsigned char flags;
    unsigned char tail[3];
} State_002158B0;
extern State_002158B0 saveProfiles[]; /* original: gSzData_All */
#endif


typedef struct Flags_002171B0 {
    u8 padding[0xFF9C];
    u8 : 5;
    u8 active : 1;
    u8 : 2;
} Flags_002171B0;

extern u8 profileZeroSide; /* original: gSzData_bRoseFlag */

/* Whether side `side` has an edited map. */
s32 SzData_GetMapEditFlag(s32 side) {
    s32 index;
    State_002158B0 *state;

    if (profileZeroSide == side) {
        index = 0;
    } else {
        index = 1;
    }
    state = &saveProfiles[index];
    if ((side < 0) || (side >= 2)) {
        return 0;
    }
    return ((Flags_002171B0 *)state)->active ? 1 : 0;
}

#ifndef GAME_H
/* The game translation unit already declares this array with its local type. */
extern unsigned char saveProfiles[]; /* original: gSzData_All */
#endif


typedef struct Flags_00217230 {
    u8 padding[0xFF9C];
    u8 unknown : 5;
    u8 enabled : 1;
    u8 : 2;
} Flags_00217230;

extern u8 profileZeroSide; /* original: gSzData_bRoseFlag */

/* Marks side `side` as having an edited map. */
s32 SzData_SetMapEditFlag(s32 side, s32 on) {
    s32 var_v1;
    u8 *temp_a2;

    if (profileZeroSide == side) {
        var_v1 = 0;
    } else {
        var_v1 = 1;
    }
    temp_a2 = (u8 *)saveProfiles + (var_v1 * 0xFFA0);
    if ((side < 0) || (side >= 2)) {
        return 0;
    }
    ((Flags_00217230 *)temp_a2)->enabled = on != 0 ? 1 : 0;
    return 1;
}

#ifndef INCLUDE_ASM
#define DECLARE_STATE_002172D0
#endif


typedef struct {
    u8 pad[0x48];
    u16 flags : 14;
    u16 status : 2;
    u16 value;
} Card_002172D0;

#ifdef DECLARE_STATE_002172D0
typedef struct {
    u8 pad[0xFF9C];
    u8 flags;
    u8 tail[3];
} State_002158B0;
#endif

extern u16 rankExpTable[]; /* original: gSzData_awExpTable */
extern u8 profileZeroSide; /* original: gSzData_bRoseFlag */

/* Sets side `side`'s rank for card `card` to `rank`. */
s32 SzData_SetRankDirect(s32 player, s32 cardId, s32 rank) {
    extern State_002158B0 saveProfiles[];
    s32 side;
    Card_002172D0 *base;
    Card_002172D0 *card;

    if (profileZeroSide == player) {
        side = 0;
    } else {
        side = 1;
    }
    base = (Card_002172D0 *)((u8 *)saveProfiles + side * 0xFFA0);
    if ((player < 0) || (player >= 2)) {
        return -1;
    }
    if ((rank < 0) || (rank >= 0xD)) {
        return -1;
    }
    if (cardId == 0x29F) {
        cardId = 0x3E7;
    }
    if ((cardId < 0) || (cardId >= 0x2AB)) {
        return -1;
    }
    card = &base[cardId];
    card->flags = rank;
    card->value = rankExpTable[rank];
    return card->flags;
}

/* Starts the memory card system (nothing to do here). */
s32 RhMemCard_Init(void) {
    func_00193808();
    return 1;
}

/* Ends the memory card system. */
s32 RhMemCard_Term(void) {
    return 1;
}

/* The memory card system's per-frame work. */
s32 RhMemCard_Act(void) {
    return 1;
}

typedef struct State_00217410 {
    s16 slots[4];
    s8 enabled : 1;
    s8 reserved : 7;
    u8 padding[3];
} State_00217410;

extern State_00217410 soundState; /* original: gSzSound_sl */
extern u8 D_002D0930[];

/* Starts the sound system: the IOP driver, the sound effect groups, the music. */
void SzSound_Init(void) {
    extern u8 *getenv();
    State_00217410 *state = &soundState;
    s16 *slot;
    s32 i;

    RhMem_FillMemory((s8 *)&soundState, 0, 0xC);
    state->enabled = getenv(D_002D0930) ? 1 : 0;
    if (state->enabled) {
        SD_Init(0x400000);
        SD_BGMSetSourceLevel(0x80, 0x80);
        slot = state->slots;
        i = 0;
        do {
            i += 1;
            *slot++ = -1;
        } while (i < 4);
        SzSound_SetOutput(1);
    }
}

typedef struct Flags_002174D0 {
    s8 active : 1;
} Flags_002174D0;

typedef struct State_002174D0 {
    u8 pad[8];
    Flags_002174D0 flags;
} State_002174D0;

struct State_00217410;


/* Ends the sound system. */
void SzSound_Term(void) {
    extern struct State_00217410 soundState;
    extern Flags_002174D0 D_0034F6E8;
    State_002174D0 *state = (State_002174D0 *)&soundState;

    if (D_0034F6E8.active) {
        SD_Term();
        state->flags.active = 0;
    }
}

typedef struct {
    s8 active : 1;
} Flags_00217530;

extern Flags_00217530 D_0034F6E8;

/* Whether the sound system is ready. */
s32 SzSound_IsStandby(void) {
    return D_0034F6E8.active != 0 ? 1 : 0;
}

#ifndef GAME_H
/* The game translation unit already declares this global with its local type. */
typedef struct {
    signed char active : 1;
} Flags_00217530;

extern Flags_00217530 D_0034F6E8;
#endif

/* The sound system's per-vertical-blank work. */
void SzSound_VSync(void) {
    if (D_0034F6E8.active) {
        SD_CallEveryVSync();
    }
}

/* Loads sound effect group `group` into channel `channel` (0..3), unless it is already there (`force` reloads). */
s32 SzSound_TransferSEGrp(s32 channel, s32 group, s32 force) {
    extern char *seGroupFileNames[];
    extern void func_0019B648();
    extern s32 SD_iTransferSEGrpToIop();
    State_00217410 *state = &soundState;
    char text[0x80];

    if (!D_0034F6E8.active) {
        return 0;
    }
    if (channel < 0 || channel >= 4) {
        return 0;
    }
    if (force == 0 && state->slots[channel] == group) {
        return 1;
    }
    state->slots[channel] = group;
    SD_SEStop(channel, -1);
    switch (channel) {
    case 0:
    case 1:
        func_0019B648(text, seGroupFileNames[channel], group);
        break;
    default:
        func_0019B648(text, seGroupFileNames[channel], group, group);
        break;
    }
    return SD_iTransferSEGrpToIop(channel, text);
}

#ifndef GAME_H
typedef struct {
    signed char active : 1;
} Flags_002176B0;
extern Flags_002176B0 D_0034F6E8;
#endif

/* Whether a sound effect is playing. */
s32 SzSound_IsPlaySE(void) {
    extern s64 SD_iGetSDStatus();

    if (!D_0034F6E8.active) {
        return 0;
    }
    return !((s32)SD_iGetSDStatus() & 0x4000) ? 1 : 0;
}

/* Plays sound effect `se` (bit 15: looping) of channel `channel` (0..3). */
s32 SzSound_PlaySE(s32 channel, s32 se) {
    extern s64 SD_iGetSDStatus();
    State_00217410 *state = &soundState;

    if (!D_0034F6E8.active) {
        return 0;
    }
    if (channel < 0 || channel >= 4) {
        return 0;
    }
    if (state->slots[channel] < 0) {
        return 0;
    }
    if ((s32)SD_iGetSDStatus() & 0x4000) {
        return 0;
    }
    SD_SEPlayOnlyOnce(channel, se & 0x7FFF, (se & 0x8000) ? 1 : 0);
    return 1;
}

/* Plays sound effect `se` of channel `channel` with stereo pan `pan`. */
s32 SzSound_StereoPlaySE(s32 channel, s32 se, s32 pan) {
    extern s64 SD_iGetSDStatus();
    State_00217410 *state = &soundState;

    if (!D_0034F6E8.active) {
        return 0;
    }
    if (channel < 0 || channel >= 4) {
        return 0;
    }
    if (state->slots[channel] < 0) {
        return 0;
    }
    if ((s32) SD_iGetSDStatus() & 0x4000) {
        return 0;
    }
    se &= 0x7FFF;
    pan &= 0x7FFF;
    SD_SEPlay2(channel, se, pan);
    return 1;
}

/* Stops sound effect `se` (-1: all) of channel `channel`. */
s32 SzSound_StopSE(s32 channel, s32 se) {
    State_00217410 *state = &soundState;

    if (!D_0034F6E8.active) {
        return 0;
    }
    if (channel < 0 || channel >= 4) {
        return 0;
    }
    if (state->slots[channel] < 0) {
        return 0;
    }
    if ((s64)SD_iGetSDStatus() & 0x4000) {
        return 0;
    }
    SD_SEStop(channel, se);
    return 1;
}

/* Starts music `bgm` (preloading it), with `mode`. */
s32 SzSound_PlayBGM(s32 bgm, s32 mode) {
    if (D_0034F6E8.active == 0) {
        return 0;
    }
    SD_BGMPreLoad(bgm, mode);
    return 1;
}

/* Whether music is still loading. */
s32 SzSound_IsLoadingBGM(void) {
    if (D_0034F6E8.active == 0) {
        return 0;
    }
    return (SD_IsLoadingNow() != 0) ? 1 : 0;
}

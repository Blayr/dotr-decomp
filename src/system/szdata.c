/* The save profiles: trunk, decks, ranks, options, treasures (SzData_*). */

#include "common.h"

typedef struct Slot_00214290 {
    u32 value : 31;
    u32 flag : 1;
    u32 other : 30;
    u32 type : 2;
} Slot_00214290;

typedef struct Card_00214290 {
    Slot_00214290 slots[9];
    u16 value : 14;
    u16 flag : 1;
    u16 otherFlag : 1;
    s16 count;
} Card_00214290;

typedef struct Deck_00214290 {
    s16 cards[40];
    s16 card;
    s16 count;
} Deck_00214290;

typedef struct Flags_00214290 {
    u8 mode : 2;
    u8 bit2 : 1;
    u8 bit3 : 1;
    u8 bit4 : 1;
    u8 bit5 : 1;
    u8 unused : 2;
} Flags_00214290;

typedef struct Save_00214290 {
    Card_00214290 cards[0x356];
    s16 values[5];
    u8 padding[2];
    Deck_00214290 decks[3];
    u8 bytes[16];
    union {
        u8 bytes[22];
        struct {
            u8 header[3];
            u8 grid[5][7][7];
        } board;
    } data;
    u8 padding2[4];
    Flags_00214290 flags;
    u8 padding3[3];
} Save_00214290;

/* Clears both save profiles (0xFFA0 bytes each): every card's trunk entries, the five-newest-cards list (CARD_NONE),
   the special-card counters, the three decks, the five edited maps (all field 7), the options. */
void SzData_Initialize(void) {
    extern Save_00214290 saveProfiles[2];
    s32 card;
    s32 slot;
    s32 profile;
    Slot_00214290 *slotPtr;
    Card_00214290 *cardPtr;
    Save_00214290 *save;
    s16 *valuePtr;
    s32 value;
    Deck_00214290 *currentDeck;
    s16 *deckCardPtr;
    u8 *deckBase;
    s32 deck;
    s32 deckCard;
    s32 byte;
    s32 dataByte;
    s32 grid;
    u8 *columnPtr;
    u8 *rowBase;
    u8 *gridBase;
    s32 row;
    s32 column;

    RhMem_FillMemory((s8 *)saveProfiles, 0, 0x1FF40);
    save = saveProfiles;
    profile = 0;
    do {
        card = 0;
        cardPtr = save->cards;
        do {
            slot = 0;
            slotPtr = cardPtr->slots;
            do {
                slotPtr->value = 0;
                slotPtr->other = 0;
                slotPtr->type = 3;
                slotPtr->flag = 0;
                slot++;
                slotPtr++;
            } while (slot < 9);
            cardPtr->value = 0;
            cardPtr->count = 0;
            cardPtr->flag = 0;
            cardPtr->otherFlag = 0;
            card++;
            cardPtr++;
        } while (card < 0x356);
        value = 0;
        valuePtr = (s16 *)save;
        do {
            valuePtr[0x7EC4] = 999;
            value++;
            valuePtr++;
        } while (value < 5);
        deck = 0;
        deckBase = (u8 *)save;
        do {
            currentDeck = (Deck_00214290 *)(deckBase + 0xFD94);
            deckCard = 0;
            deckCardPtr = currentDeck->cards;
            do {
                *deckCardPtr = 999;
                deckCard++;
                deckCardPtr++;
            } while (deckCard < 40);
            currentDeck->card = 999;
            currentDeck->count = 0;
            deck++;
            deckBase += 0x54;
        } while (deck < 3);
        byte = 0;
        do {
            save->bytes[byte] = 0;
            byte++;
        } while (byte < 16);
        dataByte = 0;
        do {
            save->data.bytes[dataByte] = 0;
            dataByte++;
        } while (dataByte < 22);
        grid = 0;
        gridBase = (u8 *)save;
        do {
            row = 0;
            rowBase = gridBase;
            do {
                column = 0;
                columnPtr = rowBase;
                do {
                    columnPtr[0xFEA3] = 7;
                    column++;
                    columnPtr++;
                } while (column < 7);
                row++;
                rowBase += 7;
            } while (row < 7);
            grid++;
            gridBase += 0x31;
        } while (grid < 5);
        save->flags.mode = 0;
        save->flags.bit2 = 1;
        save->flags.bit3 = 1;
        save->flags.bit4 = 1;
        save->flags.bit5 = 1;
        save++;
        profile++;
    } while (profile < 2);
}

/* Sets which duel side plays with save profile 0 (the other side gets profile 1). */
void SzData_SetRoseFlag(s32 side) {
    extern u8 profileZeroSide;

    profileZeroSide = side;
}

/* The save profile of duel side `side`. */
void *SzData_GetData(s32 side) {
    extern u8 saveProfiles[];
    extern u8 profileZeroSide;
    s32 profile;

    if (profileZeroSide == side) {
        profile = 0;
    } else {
        profile = 1;
    }
    return saveProfiles + (profile * 0xFFA0);
}

typedef struct {
    u8 values[9][8];
    u16 id : 14;
    u16 flag1 : 1;
    u16 flag2 : 1;
    s16 count;
} Entry_00214620;

typedef struct {
    s16 values[40];
    s16 active;
    s16 count;
} Deck_00214620;

typedef struct {
    u8 mode : 2;
    u8 flag2 : 1;
    u8 flag3 : 1;
    u8 flag4 : 1;
    u8 flag5 : 1;
    u8 unused : 2;
} Flags_00214620;

typedef union {
    u8 zeroes[22];
    struct {
        u8 prefix[3];
        u8 values[5][7][7];
    } map;
} Region_00214620;

typedef struct {
    Entry_00214620 entries[854];
    s16 values[5];
    s16 padding_fd92;
    Deck_00214620 decks[3];
    u8 bytes_fe90[16];
    Region_00214620 region;
    s32 count;
    Flags_00214620 flags;
    u8 padding_ff9d[3];
} State_00214620;

extern u8 profileZeroSide; /* original: gSzData_bRoseFlag */

/* Clears the save profile of duel side `side` (cards, decks, maps and options to their defaults). */
void SzData_ClearData(s32 side) {
    extern State_00214620 saveProfiles[2];
    s32 i;
    State_00214620 *state;
    Entry_00214620 *entry;
    s32 j;
    u8 *value;
    s16 *value_base;
    s32 n_values;
    Deck_00214620 *deck;
    s16 *card;
    u8 *deck_base;
    s32 n_decks;
    s32 n_cards;
    s32 n_bytes1;
    s32 n_bytes2;
    s32 n_layers;
    u8 *cell;
    u8 *row;
    u8 *layer;
    s32 n_rows;
    s32 n_cells;

    state = &saveProfiles[profileZeroSide == side ? 0 : 1];
    i = 0;
    entry = state->entries;
    do {
        j = 0;
        value = entry->values[0];
        do {
            SzData_ClearCardInfo(value);
            j++;
            value += 8;
        } while (j < 9);
        entry->id = 0;
        entry->count = 0;
        entry->flag1 = 0;
        entry->flag2 = 0;
        i++;
        entry++;
    } while (i < 854);

    n_values = 0;
    value_base = (s16 *)state;
    do {
        value_base[0x7EC4] = 999;
        n_values++;
        value_base++;
    } while (n_values < 5);

    n_decks = 0;
    deck_base = (u8 *)state;
    do {
        deck = (Deck_00214620 *)(deck_base + 0xFD94);
        n_cards = 0;
        card = deck->values;
        do {
            *card = 999;
            n_cards++;
            card++;
        } while (n_cards < 40);
        deck->active = 999;
        deck->count = 0;
        n_decks++;
        deck_base += 0x54;
    } while (n_decks < 3);

    n_bytes1 = 0;
    do {
        state->bytes_fe90[n_bytes1] = 0;
        n_bytes1++;
    } while (n_bytes1 < 16);

    n_bytes2 = 0;
    do {
        state->region.zeroes[n_bytes2] = 0;
        n_bytes2++;
    } while (n_bytes2 < 22);

    n_layers = 0;
    layer = (u8 *)state;
    do {
        n_rows = 0;
        row = layer;
        do {
            n_cells = 0;
            cell = row;
            do {
                cell[0xFEA3] = 7;
                n_cells++;
                cell++;
            } while (n_cells < 7);
            n_rows++;
            row += 7;
        } while (n_rows < 7);
        n_layers++;
        layer += 49;
    } while (n_layers < 5);
    state->count = 0;
    state->flags.mode = 0;
    state->flags.flag2 = 1;
    state->flags.flag3 = 1;
    state->flags.flag4 = 1;
    state->flags.flag5 = 0;
}

/* Card `slot` (0 = the leader, 1..40) of built-in deck `deck` (0..50), or -1. */
s32 SzData_GetConstDeck(s32 deck, s32 slot) {
    if (deck < 0 || deck >= 51) {
        return -1;
    }
    if (slot < 0 || slot >= 41) {
        return -1;
    }
    return gSzData_ConstDeck[deck][slot] & 0xFFF;
}

typedef struct {
    u8 entries[0xFD88];
    s16 values[5];
    u8 pad_fd92[0x206];
    s32 count;
    u8 flags;
    u8 pad_ff9d[3];
} State_00214990;

extern s32 playerNameOffset;
extern u16 StringBlob[];

/* Gives side `side` built-in deck `deck`: a fresh trunk with its 41 cards, the leader and the deck set up, a new
   profile id. */
void SzData_SetupFromConstDeck(s32 side, s32 deckNo) {
    extern State_00214990 saveProfiles[2];
    u16 *deck;
    s32 sum;
    s32 i;
    u16 *src;
    u16 *card;
    u16 value;
    State_00214990 *state;

    state = &saveProfiles[profileZeroSide == side ? 0 : 1];
    deck = gSzData_ConstDeck[deckNo];
    if (!(deckNo >= 0 && deckNo < 51)) {
        return;
    }
    SzData_ClearData(side);
    if (deckNo < 17) {
        sum = 0;
        src = &StringBlob[playerNameOffset] + 2;
        while (1) {
            value = *src;
            sum += value & 0x1FFF;
            if (value & 0x8000) {
                break;
            }
            src++;
        }
        do {
            state->count = (sum + func_0019A5C8()) & 0x7FFFFFFF;
        } while (state->count == 0);
    } else {
        state->count = deckNo + 0x40000000;
    }
    i = 0;
    card = deck;
    do {
        SzData_AddBag(side, 0, *card & 0xFFF);
        i++;
        card++;
    } while (i < 41);
    for (i = 0; i < 5; i++) {
        state->values[i] = 999;
    }
    SzData_SetRankDirect(side, *deck & 0xFFF, *deck >> 12);
    SzData_PushDeckLeader(side, 0, *deck & 0xFFF);
    deck++;
    i = 1;
    do {
        SzData_PushDeck(side, 0, *deck & 0xFFF);
        i++;
        deck++;
    } while (i < 41);
    SzText_Free(0, 1);
    SzText_Free(0, 0);
    SzText_Free(1, -1);
}

typedef struct State_00214BB0 {
    u8 pad[0xFF9C];
    u8 unused0 : 2;
    u8 flag2 : 1;
    u8 flag3 : 1;
    u8 flag4 : 1;
    u8 unused5 : 3;
    u8 tail[3];
} State_00214BB0;

/* Sets option `option` of side `side`'s profile: 0 and 1 the duel options, 2 the sound output (also applied). */
s32 SzData_SetOption(s32 side, s32 option, s32 on) {
    extern State_00214BB0 saveProfiles[];
    s32 index;
    State_00214BB0 *state;

    if (profileZeroSide == side) {
        index = 0;
    } else {
        index = 1;
    }
    state = &saveProfiles[index];
    switch (option) {
    case 0:
        state->flag2 = on ? 1 : 0;
        break;
    case 1:
        state->flag3 = on ? 1 : 0;
        break;
    case 2:
        state->flag4 = on ? 1 : 0;
        SzSound_SetOutput(state->flag4);
        break;
    default:
        return 0;
    }
    return 1;
}

typedef struct {
    u8 pad[0xFF9C];
    u8 lo : 2;
    u8 flag2 : 1;
    u8 flag3 : 1;
    u8 flag4 : 1;
    u8 hi : 3;
    u8 pad2[3];
} Side_00214D00;

extern Side_00214D00 saveProfiles[]; /* original: gSzData_All */

/* Option `option` (0..2) of side `side`'s profile, or -1. */
s32 SzData_GetOption(s32 player, s32 option) {
    Side_00214D00 *side;
    s32 idx;

    if (profileZeroSide == player) {
        idx = 0;
    } else {
        idx = 1;
    }
    side = &saveProfiles[idx];
    switch (option) {
    case 0:
        return side->flag2 ? 1 : 0;
    case 1:
        return side->flag3 ? 1 : 0;
    case 2:
        return side->flag4 ? 1 : 0;
    default:
        return -1;
    }
}

/* The trunk entry of card `card` for side `side` of `type` with its flag set as `flag`, or NULL. */
void *SzData_CheckBag(s32 player, s32 card, s32 typeIn, s32 flag) {
    typedef struct {
        u32 id : 31;
        u32 active : 1;
        u32 value : 30;
        u32 type : 2;
    } Entry_00214DD0;
    s32 side;
    Entry_00214DD0 *entry;
    s32 count;

    if (player < 0 || player >= 2) {
        return NULL;
    }
    if (card == 0x29F) {
        card = 0x3E7;
    }
    if (card < 0 || card >= 0x356) {
        return NULL;
    }
    if (profileZeroSide == player) {
        side = 0;
    } else {
        side = 1;
    }
    entry = (Entry_00214DD0 *)((u8 *)saveProfiles + side * 0xFFA0 + card * 0x4C);
    count = 9;
    while (count--) {
        if (entry->id != 0 && entry->type == typeIn &&
            (entry->active != 0) == (flag == 1)) {
            return entry;
        }
        entry++;
    }
    return NULL;
}

/* Trunk entry `index` (0..8) of card `card` for side `side`, or NULL. */
void *SzData_GetCardInfo(s32 side, s32 card, s32 index) {
    s32 bank;
    u8 *base;

    if (profileZeroSide == side) {
        bank = 0;
    } else {
        bank = 1;
    }
    base = (u8 *)saveProfiles + bank * 0xFFA0;
    if ((side < 0) || (side >= 2)) {
        return NULL;
    }
    if ((index < 0) || (index >= 9)) {
        return NULL;
    }
    if (card == 0x29F) {
        card = 0x3E7;
    }
    if ((card < 0) || (card >= 0x356)) {
        return NULL;
    }
    return base + card * 0x4C + index * 8;
}

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
    extern Player_00215060 saveProfiles_2[2];
    Entry_00215060 *entry;
    s32 n;

    if (sideIndex < 0 || sideIndex >= 2) {
        return -1;
    }
    if (owner == 0) {
        Player_00215060 *player;
        s32 side;

        side = (profileZeroSide == sideIndex) ? 0 : 1;
        player = &saveProfiles_2[side];
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
        entry = (Entry_00215060 *)((u8 *)&saveProfiles_2[side] + card * 0x4C);
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

/* Whether deck `deck` of side `side` can use card `card` (it owns enough copies). */
s32 SzData_CheckDeck(s32 player, s32 deck, s32 card) {
    extern SideData_002151D0 saveProfiles_2[];
    s32 i;
    s32 side;
    u16 *entries;

    if (profileZeroSide == player) {
        side = 0;
    } else {
        side = 1;
    }
    entries = (u16 *)(deck * 0x54 + (u8 *)&saveProfiles_2[side] + 0xFD94);
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

/* Makes card `card` the leader of deck `deck` of side `side`. */
s32 SzData_PushDeckLeader(s32 side, s32 deck, s32 card) {
    extern u8 saveProfiles_2[];
    s32 var_v1;
    u8 *temp_s2;
    Card_00215280 *checkBag;

    if (profileZeroSide == side) {
        var_v1 = 0;
    } else {
        var_v1 = 1;
    }
    temp_s2 = ((Slot_00215280 *)(saveProfiles_2 + (var_v1 * 0xFFA0)))[deck] + 0x7D9C + 0x7FF8;
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

/* Takes the leader out of deck `deck` of side `side`. */
s32 SzData_PullDeckLeader(s32 player, s32 deck) {
    extern Side_002153D0 saveProfiles_2[];
    s32 side;
    u16 card;
    Slot_002153D0 *slot;
    Card_002153D0 *entry;

    if (profileZeroSide == player) {
        side = 0;
    } else {
        side = 1;
    }
    slot = (Slot_002153D0 *)((u8 *)&saveProfiles_2[side] + deck * 0x54 + 0xFD94);
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

/* How many copies of a card a deck holds. */
static inline s32 count_002154E0(s32 player, s32 deck_index, s32 card_id) {
    extern Side_002154E0 saveProfiles_2[];
    s32 side;
    u16 *cards;
    s32 count;
    s32 i;

    if (profileZeroSide == player) {
        side = 0;
    } else {
        side = 1;
    }
    cards = (u16 *)((u8 *)&saveProfiles_2[side] + deck_index * 0x54 + 0xFD94);
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
    extern Side_002154E0 saveProfiles_2[];
    s32 side;
    u16 *cards;
    s32 i;

    if (profileZeroSide == player) {
        side = 0;
    } else {
        side = 1;
    }
    cards = (u16 *)((u8 *)&saveProfiles_2[side] + deck_index * 0x54 + 0xFD94);
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
    extern Side_002154E0 saveProfiles_2[];
    s32 side;
    Deck_002154E0 *deck;
    Entry_002154E0 *entry;
    CardConstInfo *card;
    s32 slot;

    if (profileZeroSide == player) {
        side = 0;
    } else {
        side = 1;
    }
    deck = (Deck_002154E0 *)((u8 *)&saveProfiles_2[side] + deck_index * 0x54 + 0xFD94);
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
    deck->cost += card->deckCost;
    deck->cards[slot] = card_id;
    entry->deck = deck_index;
    return 1;
}

typedef struct {
    u8 pad[7];
    u8 flags : 6;
    u8 state : 2;
} Card_00215770;

/* Takes card `card` out of deck `deck` of side `side`. */
s32 SzData_PullDeck(s32 player, s32 deck, s32 pullCard) {
    extern u8 saveProfiles_2[];
    u8 *hand;
    Card_00215770 *card;
    u16 *slot;
    s32 cardId;
    s32 side;
    CardConstInfo *info;

    if (profileZeroSide == player) {
        side = 0;
    } else {
        side = 1;
    }
    hand = (u8 *)((u32)saveProfiles_2 + side * 0xFFA0 + deck * 0x54) + 0x7D9C + 0x7FF8;
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
    *(u16 *)(hand + 0x52) -= info->deckCost;
    *slot = 0x3E7;
    card->state = 3;
    return 1;
}

typedef struct {
    u8 pad[0xFF9C];
    u8 flags;
    u8 tail[3];
} State_002158B0;

extern State_002158B0 saveProfiles_2[]; /* original: gSzData_All */

/* Which deck (0..2) side `side` uses. */
s32 SzData_GetCurrentDeck(s32 side) {
    s32 var_v1;
    State_002158B0 *state;

    if (profileZeroSide == side) {
        var_v1 = 0;
    } else {
        var_v1 = 1;
    }
    state = &saveProfiles_2[var_v1];
    if ((side < 0) || (side >= 2)) {
        return -1;
    }
    return state->flags & 3;
}

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
    temp_a2 = (u8 *)saveProfiles_2 + (var_v1 * 0xFFA0);
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

/* The leader of deck `deck` of side `side` (CARD_NONE for none). */
s32 SzData_GetLeader(s32 player, s32 deck) {
    u8 *side;
    Entry_002159D0 *entry;

    side = (u8 *)saveProfiles_2 + SzData_Side(player) * 0xFFA0;
    entry = (Entry_002159D0 *)(side + deck * sizeof(Entry_002159D0) + 0xFD94);
    if ((player < 0) || (player >= 2)) {
        return -1;
    }
    return entry->value;
}

#ifndef GAME_H
/* The game translation unit already declares this array with its local type. */
extern unsigned char saveProfiles_2[]; /* original: gSzData_All */
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

/* Card `slot` (0..39) of deck `deck` of side `side`. */
s32 SzData_GetCardNo(s32 side, s32 deck, s32 slot) {
    s32 var_v1;
    u16 *values;

    if (profileZeroSide == side) {
        var_v1 = 0;
    } else {
        var_v1 = 1;
    }
    values = ((Side_00215A60 *)saveProfiles_2)[var_v1].rows[deck].values;
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
    player = (u8 *)&saveProfiles_2[side];
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
    CardConstInfo *data;

    if (profileZeroSide == player) {
        side = 0;
    } else {
        side = 1;
    }
    deck = (Deck_00215C40 *)((u8 *)saveProfiles_2 + side * 0xFFA0 + deckNo * sizeof(Deck_00215C40) + 0xFD94);
    if ((player < 0) || (player >= 2)) {
        return -1;
    }
    deck->total = 0;
    i = 0;
    card = deck->cards;
    do {
        data = SzDuel_GetCardConstInfo(*card);
        if (data != NULL) {
            deck->total += data->deckCost;
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
    base = (u8 *)saveProfiles_2 + side * 0xFFA0;
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
    base = (u8 *)saveProfiles_2 + side * 0xFFA0;
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

/* The deck cost of deck `deck` of side `side`. */
s32 SzData_GetDeckCost(s32 player, s32 deck) {
    u8 *side;
    Entry_00215F00 *entry;

    side = (u8 *)saveProfiles_2 + SzData_Side(player) * 0xFFA0;
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
    card = (u16 *)((u8 *)saveProfiles_2 + side * 0xFFA0 + deck * 0x54 + 0xFD94);
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

/* A side's save profile. */
static inline Player_00216040 *data_00216040(s32 player, void *base) {
    return &((Player_00216040 *)base)[SzData_Side(player)];
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
        owner = data_00216040(side, saveProfiles_2)->defaultCard;
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

    card = (Card_00216040 *)data_00216040(side, saveProfiles_2) + cardId;
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

/* A side's save profile. */
static inline Player_00216280 *data_00216280(s32 player, void *base) {
    return &((Player_00216280 *)base)[SzData_Side(player)];
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
        owner = data_00216280(side, saveProfiles_2)->defaultCard;
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

    card = (Card_00216280 *)data_00216280(side, saveProfiles_2) + cardId;
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
extern State_002158B0 saveProfiles_2[]; /* original: gSzData_All */
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
    player = &saveProfiles_2[side];
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

extern State_002158B0 saveProfiles_2[]; /* original: gSzData_All */
extern Entry_00216580 specialCards[]; /* original: aSpecialCard */
#endif

typedef struct State_002166D0 {
    u8 unk_0000[0xFE90];
    u8 replacements[16];
    u8 unk_FEA0[0x100];
} State_002166D0;

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

        state = (State_002166D0 *)saveProfiles_2 + side;
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

typedef struct Record_00216800 {
    u8 pad[0xFD88];
    u16 entries[5];
    u8 pad_end[0x20E];
} Record_00216800;

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
    record = &((Record_00216800 *)saveProfiles_2)[record_index];
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

typedef struct {
    u8 padding[0xFD88];
    u16 card;
} Entry_00216920;

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
    data = (u8 *)saveProfiles_2 + side * 0xFFA0;
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

typedef struct {
    u32 value : 31;
    u32 flag : 1;
    u8 pad[3];
    u8 flags : 6;
    u8 type : 2;
} Entry_002169F0;

/* How many cards side `side`'s trunk holds. */
s32 SzData_GetBagCountAll(s32 player) {
    s32 rowIndex;
    Entry_002169F0 *entry;
    s32 remaining;
    s32 count;
    s32 side;
    u8 *row;

    side = profileZeroSide == player ? 0 : 1;
    row = (u8 *)saveProfiles_2 + (side * 0xFFA0);
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

typedef struct {
    u32 value : 31;
    u32 flag : 1;
    u8 padding[3];
    u8 unused : 6;
    u8 category : 2;
} Entry_00216AC0;

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
    entry = (Entry_00216AC0 *)((u8 *)saveProfiles_2 + (player * 0xFFA0));
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

typedef struct Flags_00216BC0 {
    u8 unused : 6;
    u8 active : 1;
    u8 unused2 : 1;
} Flags_00216BC0;

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
    cards = (u8 *)saveProfiles_2 + var_v1 * 0xFFA0;
    if ((side < 0) || (side >= 2)) {
        return 0;
    }
    if ((card < 0) || (card >= 0x356)) {
        return 0;
    }
    return ((Flags_00216BC0 *)(cards + card * 0x4C + 0x49))->active ? 1 : 0;
}

typedef struct Card_00216C70 {
    u8 padding[0x49];
    u8 flags : 6;
    u8 selected : 1;
    u8 flag7 : 1;
    u8 padding4A[2];
} Card_00216C70;

/* Marks card `card` as seen by side `side`. */
s32 SzData_SetLookFlag(s32 side, s32 cardId, s32 on) {
    s32 var_v1;
    Card_00216C70 *cards;
    Card_00216C70 *card;

    var_v1 = (profileZeroSide == side) ? 0 : 1;
    cards = (Card_00216C70 *)((u8 *)saveProfiles_2 + var_v1 * 0xFFA0);
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
    cards = (Card_00216D30 *)&saveProfiles_2[side];
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
    table = (u8 *)saveProfiles_2 + side * 0xFFA0;
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
    data = (u8 *)saveProfiles_2 + index * 0xFFA0;
    if ((side < 0) || (side >= 2)) {
        return 0;
    }
    if ((treasure < 0) || (treasure >= 0x16)) {
        return 0;
    }
    flags = data[0xFEA0 + (treasure >> 3)];
    return (flags & (1 << (treasure % 8))) ? 1 : 0;
}

typedef struct PlayerState_00216F80 {
    u8 pad[0xFEA0];
    u8 flags[0x100];
} PlayerState_00216F80;

/* Marks treasure `flag` as found by side `player`. */
s32 SzData_SetTreasureFlag(s32 player, s32 flag, s32 enabled) {
    PlayerState_00216F80 *state;

    state = &((PlayerState_00216F80 *)saveProfiles_2)[SzData_Side(player)];
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

typedef struct Flags_002171B0 {
    u8 padding[0xFF9C];
    u8 : 5;
    u8 active : 1;
    u8 : 2;
} Flags_002171B0;

/* Whether side `side` has an edited map. */
s32 SzData_GetMapEditFlag(s32 side) {
    s32 index;
    State_002158B0 *state;

    if (profileZeroSide == side) {
        index = 0;
    } else {
        index = 1;
    }
    state = &saveProfiles_2[index];
    if ((side < 0) || (side >= 2)) {
        return 0;
    }
    return ((Flags_002171B0 *)state)->active ? 1 : 0;
}

typedef struct Flags_00217230 {
    u8 padding[0xFF9C];
    u8 unknown : 5;
    u8 enabled : 1;
    u8 : 2;
} Flags_00217230;

/* Marks side `side` as having an edited map. */
s32 SzData_SetMapEditFlag(s32 side, s32 on) {
    s32 var_v1;
    u8 *temp_a2;

    if (profileZeroSide == side) {
        var_v1 = 0;
    } else {
        var_v1 = 1;
    }
    temp_a2 = (u8 *)saveProfiles_2 + (var_v1 * 0xFFA0);
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

/* Sets side `side`'s rank for card `card` to `rank`. */
s32 SzData_SetRankDirect(s32 player, s32 cardId, s32 rank) {
    extern State_002158B0 saveProfiles_2[];
    s32 side;
    Card_002172D0 *base;
    Card_002172D0 *card;

    if (profileZeroSide == player) {
        side = 0;
    } else {
        side = 1;
    }
    base = (Card_002172D0 *)((u8 *)saveProfiles_2 + side * 0xFFA0);
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

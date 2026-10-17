#include "common.h"

typedef struct {
    u32 value0 : 31;
    u8 flag : 1;
    u32 value4 : 30;
    u8 flags : 2;
} Flags_00214FD0;

s32 SzData_ClearCardInfo(void *arg0) {
    Flags_00214FD0 *flags = arg0;

    if (arg0 == NULL) {
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

s32 SzData_CheckDup(s32 arg0, s32 arg1, u32 arg2, s32 arg3) {
    extern u8 gSzData_bRoseFlag;
    extern Player_00215060 gSzData_All[2];
    Entry_00215060 *entry;
    s32 n;

    if (arg0 < 0 || arg0 >= 2) {
        return -1;
    }
    if (arg1 == 0) {
        Player_00215060 *player;
        s32 side;

        side = (gSzData_bRoseFlag == arg0) ? 0 : 1;
        player = &gSzData_All[side];
        arg1 = player->defaultCard;
    }
    if (arg1 == 0) {
        return -1;
    }
    if (arg3 == 0x29F) {
        arg3 = 0x3E7;
    }
    if (arg3 < 0 || arg3 >= 0x356) {
        return -1;
    }
    {
        s32 side;

        side = (gSzData_bRoseFlag == arg0) ? 0 : 1;
        entry = (Entry_00215060 *)((u8 *)&gSzData_All[side] + arg3 * 0x4C);
    }
    n = 9;
    while (n-- != 0) {
        if (entry->card != 0) {
            if (entry->value == arg2) {
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

extern u8 gSzData_bRoseFlag;

s32 SzData_CheckDeck(s32 arg0, s32 arg1, s32 arg2) {
    extern SideData_002151D0 gSzData_All[];
    s32 i;
    s32 side;
    u16 *entries;

    if (gSzData_bRoseFlag == arg0) {
        side = 0;
    } else {
        side = 1;
    }
    entries = (u16 *)(arg1 * 0x54 + (u8 *)&gSzData_All[side] + 0xFD94);
    if (arg0 < 0 || arg0 >= 2) {
        return -1;
    }
    i = 0;
    do {
        if (arg2 == *entries) {
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

extern u8 gSzData_bRoseFlag;

s32 SzData_PushDeckLeader(s32 arg0, s32 arg1, s32 arg2) {
    extern u8 gSzData_All[];
    s32 var_v1;
    u8 *temp_s2;
    Card_00215280 *temp_v0;

    if (gSzData_bRoseFlag == arg0) {
        var_v1 = 0;
    } else {
        var_v1 = 1;
    }
    temp_s2 = ((Slot_00215280 *)(gSzData_All + (var_v1 * 0xFFA0)))[arg1] + 0x7D9C + 0x7FF8;
    if ((arg0 < 0) || (arg0 >= 2)) {
        return 0;
    }
    if (arg2 == 0x29F) {
        arg2 = 0x3E7;
    }
    if ((arg2 < 0) || (arg2 >= 0x356)) {
        return 0;
    }
    if (*(u16 *)(temp_s2 + 0x50) != 0x3E7) {
        return 0;
    }
    temp_v0 = SzData_CheckBag(arg0, arg2, 3, 0);
    if (temp_v0 == NULL) {
        return 0;
    }
    *(u16 *)(temp_s2 + 0x50) = (u16)arg2;
    temp_v0->slot = arg1;
    temp_v0->active = 1;
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

extern u8 gSzData_bRoseFlag;

s32 SzData_PullDeckLeader(s32 arg0, s32 arg1) {
    extern Side_002153D0 gSzData_All[];
    s32 side;
    u16 card;
    Slot_002153D0 *slot;
    Card_002153D0 *entry;

    if (gSzData_bRoseFlag == arg0) {
        side = 0;
    } else {
        side = 1;
    }
    slot = (Slot_002153D0 *)((u8 *)&gSzData_All[side] + arg1 * 0x54 + 0xFD94);
    if (arg0 < 0 || arg0 >= 2) {
        return 0;
    }
    card = slot->card;
    if (card == 999) {
        return 0;
    }
    entry = SzData_CheckBag(arg0, card, arg1, 1);
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

extern u8 gSzData_bRoseFlag;

static inline s32 count_002154E0(s32 player, s32 deck_index, s32 card_id) {
    extern Side_002154E0 gSzData_All[];
    s32 side;
    u16 *cards;
    s32 count;
    s32 i;

    if (gSzData_bRoseFlag == player) {
        side = 0;
    } else {
        side = 1;
    }
    cards = (u16 *)((u8 *)&gSzData_All[side] + deck_index * 0x54 + 0xFD94);
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

static inline s32 find_002154E0(s32 player, s32 deck_index, s32 card_id) {
    extern Side_002154E0 gSzData_All[];
    s32 side;
    u16 *cards;
    s32 i;

    if (gSzData_bRoseFlag == player) {
        side = 0;
    } else {
        side = 1;
    }
    cards = (u16 *)((u8 *)&gSzData_All[side] + deck_index * 0x54 + 0xFD94);
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

s32 SzData_PushDeck(s32 player, s32 deck_index, s32 card_id) {
    extern Side_002154E0 gSzData_All[];
    s32 side;
    Deck_002154E0 *deck;
    Entry_002154E0 *entry;
    u8 *card;
    s32 slot;

    if (gSzData_bRoseFlag == player) {
        side = 0;
    } else {
        side = 1;
    }
    deck = (Deck_002154E0 *)((u8 *)&gSzData_All[side] + deck_index * 0x54 + 0xFD94);
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

extern u8 gSzData_bRoseFlag;

typedef struct {
    u8 pad[7];
    u8 flags : 6;
    u8 state : 2;
} Card_00215770;

s32 SzData_PullDeck(s32 arg0, s32 arg1, s32 arg2) {
    extern u8 gSzData_All[];
    u8 *hand;
    Card_00215770 *card;
    u16 *slot;
    s32 cardId;
    s32 side;
    u8 *info;

    if (gSzData_bRoseFlag == arg0) {
        side = 0;
    } else {
        side = 1;
    }
    hand = (u8 *)((u32)gSzData_All + side * 0xFFA0 + arg1 * 0x54) + 0x7D9C + 0x7FF8;
    if ((arg0 < 0) || (arg0 >= 2)) {
        return 0;
    }
    if ((arg2 < 0) || (arg2 >= 0x28)) {
        return 0;
    }
    slot = (u16 *)(hand + arg2 * 2);
    cardId = *slot;
    if ((card = SzData_CheckBag(arg0, cardId, arg1, 0)) == NULL) {
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

extern State_002158B0 gSzData_All[];
extern u8 gSzData_bRoseFlag;

s32 SzData_GetCurrentDeck(s32 arg0) {
    s32 var_v1;
    State_002158B0 *state;

    if (gSzData_bRoseFlag == arg0) {
        var_v1 = 0;
    } else {
        var_v1 = 1;
    }
    state = &gSzData_All[var_v1];
    if ((arg0 < 0) || (arg0 >= 2)) {
        return -1;
    }
    return state->flags & 3;
}

extern u8 gSzData_bRoseFlag;

typedef struct {
    u8 padding[0xFF9C];
    u8 mode : 2;
    u8 : 6;
} Flags_00215920;

s32 SzData_SetCurrentDeck(s32 arg0, s32 arg1) {
    s32 var_v1;
    u8 *temp_a2;

    if (gSzData_bRoseFlag == arg0) {
        var_v1 = 0;
    } else {
        var_v1 = 1;
    }
    temp_a2 = (u8 *)gSzData_All + (var_v1 * 0xFFA0);
    if ((arg0 < 0) || (arg0 >= 2)) {
        return 0;
    }
    if ((arg1 < 0) || (arg1 >= 3)) {
        return 0;
    }
    ((Flags_00215920 *)temp_a2)->mode = arg1;
    return 1;
}

typedef struct {
    u8 padding[0x50];
    u16 value;
    u8 padding_52[2];
} Entry_002159D0;

extern u8 gSzData_bRoseFlag;

static inline s32 side_002159D0(s32 player) {
    if (gSzData_bRoseFlag == player) {
        return 0;
    }
    return 1;
}

s32 SzData_GetLeader(s32 arg0, s32 arg1) {
    u8 *side;
    Entry_002159D0 *entry;

    side = (u8 *)gSzData_All + side_002159D0(arg0) * 0xFFA0;
    entry = (Entry_002159D0 *)(side + arg1 * sizeof(Entry_002159D0) + 0xFD94);
    if ((arg0 < 0) || (arg0 >= 2)) {
        return -1;
    }
    return entry->value;
}

#ifndef GAME_H
/* The game translation unit already declares this array with its local type. */
extern unsigned char gSzData_All[];
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

extern u8 gSzData_bRoseFlag;

s32 SzData_GetCardNo(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_v1;
    u16 *values;

    if (gSzData_bRoseFlag == arg0) {
        var_v1 = 0;
    } else {
        var_v1 = 1;
    }
    values = ((Side_00215A60 *)gSzData_All)[var_v1].rows[arg1].values;
    if ((arg0 < 0) || (arg0 >= 2)) {
        return -1;
    }
    if ((arg2 < 0) || (arg2 >= 0x28)) {
        return -1;
    }
    return values[arg2];
}

typedef struct Record_00215B10 {
    u8 padding[0x4A];
    u16 value;
} Record_00215B10;

s32 SzData_CalcExp(s32 arg0, s32 arg1, s32 operation, s32 value) {
    s32 side;
    u8 *player;
    Record_00215B10 *record;
    s32 current;
    s32 result;

    side = 1;
    if (gSzData_bRoseFlag == arg0) {
        side = 0;
    }
    player = (u8 *)&gSzData_All[side];
    if ((arg0 < 0) || (arg0 >= 2)) {
        return 0;
    }
    if (arg1 == 0x29F) {
        arg1 = 0x3E7;
    }
    if ((arg1 < 0) || (arg1 >= 0x356)) {
        return 0;
    }
    record = (Record_00215B10 *)(player + arg1 * 0x4C);
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

s32 SzData_CalcDeckCost(s32 arg0, s32 arg1) {
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

    if (gSzData_bRoseFlag == arg0) {
        side = 0;
    } else {
        side = 1;
    }
    deck = (Deck_00215C40 *)((u8 *)gSzData_All + side * 0xFFA0 + arg1 * sizeof(Deck_00215C40) + 0xFD94);
    if ((arg0 < 0) || (arg0 >= 2)) {
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

s64 SzData_GetRank(s32 arg0, s32 arg1) {
    s32 side;
    u8 *base;

    if (gSzData_bRoseFlag == arg0) {
        side = 0;
    } else {
        side = 1;
    }
    base = (u8 *)gSzData_All + side * 0xFFA0;
    if ((arg0 < 0) || (arg0 >= 2)) {
        return -1;
    }
    if (arg1 == 0x29F) {
        arg1 = 0x3E7;
    }
    if ((arg1 < 0) || (arg1 >= 0x2AB)) {
        return -1;
    }
    return ((Card_00215D30 *)(base + arg1 * 0x4C))->rank;
}

typedef struct Card_00215DE0 {
    u8 padding[0x48];
    u16 rank : 14;
    u16 flags : 2;
    u16 experience;
} Card_00215DE0;

extern u16 D_002D0868;
extern u8 gSzData_bRoseFlag;

s32 SzData_SetRank(s32 player, s32 index) {
    s32 side;
    u8 *base;
    Card_00215DE0 *card;
    s32 rank;
    u16 *threshold;

    if (gSzData_bRoseFlag == player) {
        side = 0;
    } else {
        side = 1;
    }
    base = (u8 *)gSzData_All + side * 0xFFA0;
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

extern u8 gSzData_bRoseFlag;

static inline s32 side_00215F00(s32 player) {
    if (gSzData_bRoseFlag == player) {
        return 0;
    }
    return 1;
}

s32 SzData_GetDeckCost(s32 arg0, s32 arg1) {
    u8 *side;
    Entry_00215F00 *entry;

    side = (u8 *)gSzData_All + side_00215F00(arg0) * 0xFFA0;
    entry = (Entry_00215F00 *)(side + arg1 * sizeof(Entry_00215F00) + 0xFD94);
    if ((arg0 < 0) || (arg0 >= 2)) {
        return -1;
    }
    return entry->value;
}

s32 SzData_GetDeckCount(s32 arg0, s32 arg1) {
    s32 i;
    s32 count;
    s32 side;
    u16 *card;

    if (gSzData_bRoseFlag == arg0) {
        side = 0;
    } else {
        side = 1;
    }
    card = (u16 *)((u8 *)gSzData_All + side * 0xFFA0 + arg1 * 0x54 + 0xFD94);
    count = 0;
    if ((arg0 < 0) || (arg0 >= 2)) {
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


static inline s32 side_00216040(s32 player) {
    extern u8 gSzData_bRoseFlag;
    if (gSzData_bRoseFlag == player) {
        return 0;
    }
    return 1;
}

static inline Player_00216040 *data_00216040(s32 player, void *base) {
    return &((Player_00216040 *)base)[side_00216040(player)];
}

static inline s64 random_value_00216040(void) {
    extern s64 func_0019A5C8();
    return (s32)func_0019A5C8() & ~0x40000000LL;
}

s32 SzData_AddBag(s32 arg0, s32 arg1, s32 arg2) {
    Card_00216040 *card;
    Entry_00216040 *entry;
    s32 count;

    if (arg0 < 0 || arg0 >= 2) {
        return 0;
    }
    if (arg1 == 0) {
        arg1 = data_00216040(arg0, gSzData_All)->defaultCard;
    }
    if (arg1 == 0) {
        return 0;
    }
    if (arg2 == 0x29F) {
        arg2 = 0x3E7;
    }
    if (arg2 < 0 || arg2 >= 0x356) {
        return 0;
    }

    card = (Card_00216040 *)data_00216040(arg0, gSzData_All) + arg2;
    entry = card->entries;
    for (count = 9; count-- != 0; entry++) {
        if (entry->card == 0) {
            do {
                entry->value = random_value_00216040();
            } while (SzData_CheckDup(arg0, arg1, entry->value, arg2) != 0);
            entry->card = arg1;
            card->assigned = 1;
            SzData_PushBagNew(arg0, arg2);
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


static inline s32 side_00216280(s32 player) {
    extern u8 gSzData_bRoseFlag;
    if (gSzData_bRoseFlag == player) {
        return 0;
    }
    return 1;
}

static inline Player_00216280 *data_00216280(s32 player, void *base) {
    return &((Player_00216280 *)base)[side_00216280(player)];
}

s32 SzData_AddBag2(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    Card_00216280 *card;
    Entry_00216280 *entry;
    s32 count;

    if (arg0 < 0 || arg0 >= 2) {
        return 0;
    }
    if (arg1 == 0) {
        arg1 = data_00216280(arg0, gSzData_All)->defaultCard;
    }
    if (arg1 == 0) {
        return 0;
    }
    if (arg3 == 0x29F) {
        arg3 = 0x3E7;
    }
    if (arg3 < 0 || arg3 >= 0x356) {
        return 0;
    }
    if (SzData_CheckDup(arg0, arg1, arg2, arg3) != 0) {
        return 0;
    }

    card = (Card_00216280 *)data_00216280(arg0, gSzData_All) + arg3;
    entry = card->entries;
    for (count = 9; count-- != 0; entry++) {
        if (entry->card == 0) {
            entry->value = arg2;
            entry->card = arg1;
            card->assigned = 1;
            SzData_PushBagNew(arg0, arg3);
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


static inline void clear_00216490(void *src) {
    Flags_00216490 *entry = (Flags_00216490 *)src;

    if (entry != NULL) {
        entry->value0 = 0;
        entry->value1 = 0;
        entry->flag1 = 3;
        entry->flag0 = 0;
    }
}

s32 SzData_DelBag(s32 arg0, s32 arg1) {
    Flags_00216490 *entry;

    if ((arg0 < 0) || (arg0 >= 2)) {
        return 0;
    }
    if (arg1 == 0x29F) {
        arg1 = 0x3E7;
    }
    if ((arg1 < 0) || (arg1 >= 0x356)) {
        return 0;
    }
    entry = SzData_CheckBag(arg0, arg1, 3, 0);
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
extern State_002158B0 gSzData_All[];
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

extern Entry_00216580 aSpecialCard[];
extern u8 gSzData_bRoseFlag;

s32 SzData_RollSpecial(s32 arg0, s32 arg1) {
    s32 i;
    State_002158B0 *player;
    Entry_00216580 *entry;
    s32 side;
    s32 decodedCard;
    u8 *count;

    if ((arg0 < 0) || (arg0 >= 2)) {
        return 0;
    }
    if (arg1 == 0x29F) {
        arg1 = 0x3E7;
    }
    if ((arg1 < 0) || (arg1 >= 0x356)) {
        return 0;
    }
    if (gSzData_bRoseFlag == arg0) {
        side = 0;
    } else {
        side = 1;
    }
    player = &gSzData_All[side];
    entry = aSpecialCard;
    i = 0;
    do {
        decodedCard = SzDuel_Xax2New(entry->card & 0x3FFF);
        if (decodedCard == arg1) {
            count = (u8 *)(i + (u32)player) + 0xFE90;
            *count = (*count + 1) % (((Flags_00216580 *)&aSpecialCard[i])[1].count + 1);
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

extern State_002158B0 gSzData_All[];
extern Entry_00216580 aSpecialCard[];
#endif


typedef struct State_002166D0 {
    u8 unk_0000[0xFE90];
    u8 replacements[16];
    u8 unk_FEA0[0x100];
} State_002166D0;

extern u8 gSzData_bRoseFlag;

s32 SzData_ExchSpecial(s32 arg0, s32 arg1) {
    State_002166D0 *state;
    Entry_00216580 *entry;
    s32 side;
    s32 replacement;
    s32 resolved;

    if ((arg0 < 0) || (arg0 >= 2)) {
        return arg1;
    }
    if (arg1 == 0x29F) {
        arg1 = 0x3E7;
    }
    if ((arg1 < 0) || (arg1 >= 0x356)) {
        return arg1;
    }
    if (gSzData_bRoseFlag == arg0) {
        side = 0;
    } else {
        side = 1;
    }
    {
        s32 i;

        state = (State_002166D0 *)gSzData_All + side;
        entry = aSpecialCard;
        i = 0;
        do {
            resolved = SzDuel_Xax2New(entry->card & 0x3FFF);
            if (resolved == arg1) {
                replacement = state->replacements[i];
                if (replacement != 0) {
                    arg1 = (&aSpecialCard[i].card)[replacement];
                }
                break;
            }
            i++;
            entry++;
        } while (i < 16);
    }
    return arg1;
}

#ifndef GAME_H
/* The game translation unit already declares this array with its local type. */
extern unsigned char gSzData_All[];
#endif


typedef struct Record_00216800 {
    u8 pad[0xFD88];
    u16 entries[5];
    u8 pad_end[0x20E];
} Record_00216800;

extern u8 gSzData_bRoseFlag;

s32 SzData_PushBagNew(s32 arg0, s32 arg1) {
    s32 record_index;
    s32 i;
    Record_00216800 *record;

    if (gSzData_bRoseFlag == arg0) {
        record_index = 0;
    } else {
        record_index = 1;
    }
    record = &((Record_00216800 *)gSzData_All)[record_index];
    if ((arg0 < 0) || (arg0 >= 2)) {
        return 0;
    }
    if (arg1 == 0x29F) {
        arg1 = 0x3E7;
    }
    if ((arg1 < 0) || (arg1 >= 0x356)) {
        return 0;
    }
    for (i = 0; i < 5; i++) {
        if ((record->entries[i] == arg1) || (i + 1 >= 5)) {
            while (i > 0) {
                record->entries[i] = record->entries[i - 1];
                i--;
            }
            break;
        }
    }
    record->entries[0] = arg1;
    return 1;
}

#ifndef GAME_H
/* The game translation unit already declares this array with its local type. */
extern unsigned char gSzData_All[];
#endif


typedef struct {
    u8 padding[0xFD88];
    u16 card;
} Entry_00216920;

extern u8 gSzData_bRoseFlag;

s32 SzData_IsBagNew(s32 arg0, s32 arg1) {
    s32 side;
    s32 i;
    u8 *data;

    if (arg0 < 0 || arg0 >= 2) {
        return 0;
    }
    if (arg1 == 0x29F) {
        arg1 = 0x3E7;
    }
    if (arg1 < 0 || arg1 >= 0x356) {
        return 0;
    }
    if (gSzData_bRoseFlag == arg0) {
        side = 0;
    } else {
        side = 1;
    }
    data = (u8 *)gSzData_All + side * 0xFFA0;
    i = 0;
    do {
        if (((Entry_00216920 *)data)->card == arg1) {
            return 1;
        }
        i++;
        data += 2;
    } while (i < 5);
    return 0;
}

#ifndef GAME_H
/* The game translation unit already declares this array with its local type. */
extern unsigned char gSzData_All[];
#endif


typedef struct {
    u32 value : 31;
    u32 flag : 1;
    u8 pad[3];
    u8 flags : 6;
    u8 type : 2;
} Entry_002169F0;

extern u8 gSzData_bRoseFlag;

s32 SzData_GetBagCountAll(s32 arg0) {
    s32 rowIndex;
    Entry_002169F0 *entry;
    s32 remaining;
    s32 count;
    s32 side;
    u8 *row;

    side = gSzData_bRoseFlag == arg0 ? 0 : 1;
    row = (u8 *)gSzData_All + (side * 0xFFA0);
    count = 0;
    if ((arg0 < 0) || (arg0 >= 2)) {
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
extern unsigned char gSzData_All[];
#endif


typedef struct {
    u32 value : 31;
    u32 flag : 1;
    u8 padding[3];
    u8 unused : 6;
    u8 category : 2;
} Entry_00216AC0;

extern u8 gSzData_bRoseFlag;

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
    if (gSzData_bRoseFlag == player) {
        player = 0;
    } else {
        player = 1;
    }
    entry = (Entry_00216AC0 *)((u8 *)gSzData_All + (player * 0xFFA0));
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
extern unsigned char gSzData_All[];
#endif


typedef struct Flags_00216BC0 {
    u8 unused : 6;
    u8 active : 1;
    u8 unused2 : 1;
} Flags_00216BC0;

extern u8 gSzData_bRoseFlag;

s32 SzData_GetLookFlag(s32 arg0, s32 arg1) {
    extern s32 SD_iPreparePreBlockOnIOP();
    s32 var_v1;
    u8 *cards;

    if (gSzData_bRoseFlag == arg0) {
        var_v1 = 0;
    } else {
        var_v1 = 1;
    }
    cards = (u8 *)gSzData_All + var_v1 * 0xFFA0;
    if ((arg0 < 0) || (arg0 >= 2)) {
        return 0;
    }
    if ((arg1 < 0) || (arg1 >= 0x356)) {
        return 0;
    }
    return ((Flags_00216BC0 *)(cards + arg1 * 0x4C + 0x49))->active ? 1 : 0;
}

#ifndef GAME_H
/* The game translation unit already declares this array with its local type. */
extern unsigned char gSzData_All[];
#endif


typedef struct Card_00216C70 {
    u8 padding[0x49];
    u8 flags : 6;
    u8 selected : 1;
    u8 flag7 : 1;
    u8 padding4A[2];
} Card_00216C70;

extern u8 gSzData_bRoseFlag;

s32 SzData_SetLookFlag(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_v1;
    Card_00216C70 *cards;
    Card_00216C70 *card;

    var_v1 = (gSzData_bRoseFlag == arg0) ? 0 : 1;
    cards = (Card_00216C70 *)((u8 *)gSzData_All + var_v1 * 0xFFA0);
    if ((arg0 < 0) || (arg0 >= 2)) {
        return 0;
    }
    if ((arg1 < 0) || (arg1 >= 0x356)) {
        return 0;
    }
    card = &cards[arg1];
    card->selected = arg2 ? 1 : 0;
    return 1;
}

s32 SzData_GetPassFlag(s32 arg0, s32 arg1) {
    typedef struct {
        u8 pad[0x49];
        u8 unused : 7;
        u8 enabled : 1;
        u8 tail[2];
    } Card_00216D30;
    s32 side;
    Card_00216D30 *cards;

    if (gSzData_bRoseFlag == arg0) {
        side = 0;
    } else {
        side = 1;
    }
    cards = (Card_00216D30 *)&gSzData_All[side];
    if ((arg0 < 0) || (arg0 >= 2)) {
        return 0;
    }
    if (arg1 == 0x29F) {
        arg1 = 0x3E7;
    }
    if ((arg1 < 0) || (arg1 >= 0x356)) {
        return 0;
    }
    return cards[arg1].enabled ? 1 : 0;
}

typedef struct {
    u8 pad[0x49];
    u8 other_flags : 7;
    u8 enabled : 1;
    u8 pad_4A[2];
} Card_00216DF0;

extern u8 gSzData_bRoseFlag;

s32 SzData_SetPassFlag(s32 arg0, s32 arg1, s32 arg2) {
    s32 side;
    u8 *table;
    Card_00216DF0 *card;

    if (gSzData_bRoseFlag == arg0) {
        side = 0;
    } else {
        side = 1;
    }
    table = (u8 *)gSzData_All + side * 0xFFA0;
    if ((arg0 < 0) || (arg0 >= 2)) {
        return 0;
    }
    if (arg1 == 0x29F) {
        arg1 = 0x3E7;
    }
    if ((arg1 < 0) || (arg1 >= 0x356)) {
        return 0;
    }
    card = (Card_00216DF0 *)(table + arg1 * 0x4C);
    card->enabled = arg2 ? 1 : 0;
    return 1;
}

s32 SzData_GetTreasureFlag(s32 arg0, s32 arg1) {
    s32 index;
    u8 *data;
    s32 flags;

    index = (gSzData_bRoseFlag == arg0) ? 0 : 1;
    data = (u8 *)gSzData_All + index * 0xFFA0;
    if ((arg0 < 0) || (arg0 >= 2)) {
        return 0;
    }
    if ((arg1 < 0) || (arg1 >= 0x16)) {
        return 0;
    }
    flags = data[0xFEA0 + (arg1 >> 3)];
    return (flags & (1 << (arg1 % 8))) ? 1 : 0;
}

#ifndef GAME_H
extern unsigned char gSzData_All[];
#endif


typedef struct PlayerState_00216F80 {
    u8 pad[0xFEA0];
    u8 flags[0x100];
} PlayerState_00216F80;

extern u8 gSzData_bRoseFlag;

static inline s32 player_index_00216F80(s32 player) {
    if (gSzData_bRoseFlag == player) {
        return 0;
    }
    return 1;
}

s32 SzData_SetTreasureFlag(s32 player, s32 flag, s32 enabled) {
    PlayerState_00216F80 *state;

    state = &((PlayerState_00216F80 *)gSzData_All)[player_index_00216F80(player)];
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

extern Entry_002170A0 aTreasureData[];
extern u16 D_002D08D2[];

u16 SzData_SearchTreasure(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 i;
    Entry_002170A0 *entry;
    s32 dx;
    s32 dy;

    if (arg3 <= 0) {
        return 999;
    }
    if (arg0 < 0 || arg0 >= 22) {
        return 999;
    }
    if (arg1 < 0 || arg1 >= 7 || arg2 < 0 || arg2 >= 7) {
        return 999;
    }

    entry = aTreasureData;
    i = 0;
    do {
        if (arg0 == entry->id) {
            dx = entry->x - arg1;
            dx = dx >= 0 ? dx : -dx;
            if (dx < arg3) {
                dy = entry->y - arg2;
                dy = dy >= 0 ? dy : -dy;
                if (dy < arg3) {
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
extern State_002158B0 gSzData_All[];
#endif


typedef struct Flags_002171B0 {
    u8 padding[0xFF9C];
    u8 : 5;
    u8 active : 1;
    u8 : 2;
} Flags_002171B0;

extern u8 gSzData_bRoseFlag;

s32 SzData_GetMapEditFlag(s32 arg0) {
    s32 index;
    State_002158B0 *state;

    if (gSzData_bRoseFlag == arg0) {
        index = 0;
    } else {
        index = 1;
    }
    state = &gSzData_All[index];
    if ((arg0 < 0) || (arg0 >= 2)) {
        return 0;
    }
    return ((Flags_002171B0 *)state)->active ? 1 : 0;
}

#ifndef GAME_H
/* The game translation unit already declares this array with its local type. */
extern unsigned char gSzData_All[];
#endif


typedef struct Flags_00217230 {
    u8 padding[0xFF9C];
    u8 unknown : 5;
    u8 enabled : 1;
    u8 : 2;
} Flags_00217230;

extern u8 gSzData_bRoseFlag;

s32 SzData_SetMapEditFlag(s32 arg0, s32 arg1) {
    s32 var_v1;
    u8 *temp_a2;

    if (gSzData_bRoseFlag == arg0) {
        var_v1 = 0;
    } else {
        var_v1 = 1;
    }
    temp_a2 = (u8 *)gSzData_All + (var_v1 * 0xFFA0);
    if ((arg0 < 0) || (arg0 >= 2)) {
        return 0;
    }
    ((Flags_00217230 *)temp_a2)->enabled = arg1 != 0 ? 1 : 0;
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

extern u16 gSzData_awExpTable[];
extern u8 gSzData_bRoseFlag;

s32 SzData_SetRankDirect(s32 arg0, s32 arg1, s32 arg2) {
    extern State_002158B0 gSzData_All[];
    s32 side;
    Card_002172D0 *base;
    Card_002172D0 *card;

    if (gSzData_bRoseFlag == arg0) {
        side = 0;
    } else {
        side = 1;
    }
    base = (Card_002172D0 *)((u8 *)gSzData_All + side * 0xFFA0);
    if ((arg0 < 0) || (arg0 >= 2)) {
        return -1;
    }
    if ((arg2 < 0) || (arg2 >= 0xD)) {
        return -1;
    }
    if (arg1 == 0x29F) {
        arg1 = 0x3E7;
    }
    if ((arg1 < 0) || (arg1 >= 0x2AB)) {
        return -1;
    }
    card = &base[arg1];
    card->flags = arg2;
    card->value = gSzData_awExpTable[arg2];
    return card->flags;
}

s32 RhMemCard_Init(void) {
    func_00193808();
    return 1;
}

s32 RhMemCard_Term(void) {
    return 1;
}

s32 RhMemCard_Act(void) {
    return 1;
}

typedef struct State_00217410 {
    s16 slots[4];
    s8 enabled : 1;
    s8 reserved : 7;
    u8 padding[3];
} State_00217410;

extern State_00217410 gSzSound_sl;
extern u8 D_002D0930[];

void SzSound_Init(void) {
    extern u8 *getenv();
    State_00217410 *state = &gSzSound_sl;
    s16 *slot;
    s32 i;

    RhMem_FillMemory((s8 *)&gSzSound_sl, 0, 0xC);
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


void SzSound_Term(void) {
    extern struct State_00217410 gSzSound_sl;
    extern Flags_002174D0 D_0034F6E8;
    State_002174D0 *state = (State_002174D0 *)&gSzSound_sl;

    if (D_0034F6E8.active) {
        SD_Term();
        state->flags.active = 0;
    }
}

typedef struct {
    s8 active : 1;
} Flags_00217530;

extern Flags_00217530 D_0034F6E8;

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

void SzSound_VSync(void) {
    if (D_0034F6E8.active) {
        SD_CallEveryVSync();
    }
}

s32 SzSound_TransferSEGrp(s32 arg0, s32 arg1, s32 arg2) {
    extern char *apchSEGrp[];
    extern void func_0019B648();
    extern s32 SD_iTransferSEGrpToIop();
    State_00217410 *state = &gSzSound_sl;
    char text[0x80];

    if (!D_0034F6E8.active) {
        return 0;
    }
    if (arg0 < 0 || arg0 >= 4) {
        return 0;
    }
    if (arg2 == 0 && state->slots[arg0] == arg1) {
        return 1;
    }
    state->slots[arg0] = arg1;
    SD_SEStop(arg0, -1);
    switch (arg0) {
    case 0:
    case 1:
        func_0019B648(text, apchSEGrp[arg0], arg1);
        break;
    default:
        func_0019B648(text, apchSEGrp[arg0], arg1, arg1);
        break;
    }
    return SD_iTransferSEGrpToIop(arg0, text);
}

#ifndef GAME_H
typedef struct {
    signed char active : 1;
} Flags_002176B0;
extern Flags_002176B0 D_0034F6E8;
#endif

s32 SzSound_IsPlaySE(void) {
    extern s64 SD_iGetSDStatus();

    if (!D_0034F6E8.active) {
        return 0;
    }
    return !((s32)SD_iGetSDStatus() & 0x4000) ? 1 : 0;
}

s32 SzSound_PlaySE(s32 arg0, s32 arg1) {
    extern s64 SD_iGetSDStatus();
    State_00217410 *state = &gSzSound_sl;

    if (!D_0034F6E8.active) {
        return 0;
    }
    if (arg0 < 0 || arg0 >= 4) {
        return 0;
    }
    if (state->slots[arg0] < 0) {
        return 0;
    }
    if ((s32)SD_iGetSDStatus() & 0x4000) {
        return 0;
    }
    SD_SEPlayOnlyOnce(arg0, arg1 & 0x7FFF, (arg1 & 0x8000) ? 1 : 0);
    return 1;
}

s32 SzSound_StereoPlaySE(s32 arg0, s32 arg1, s32 arg2) {
    extern s64 SD_iGetSDStatus();
    State_00217410 *state = &gSzSound_sl;

    if (!D_0034F6E8.active) {
        return 0;
    }
    if (arg0 < 0 || arg0 >= 4) {
        return 0;
    }
    if (state->slots[arg0] < 0) {
        return 0;
    }
    if ((s32) SD_iGetSDStatus() & 0x4000) {
        return 0;
    }
    arg1 &= 0x7FFF;
    arg2 &= 0x7FFF;
    SD_SEPlay2(arg0, arg1, arg2);
    return 1;
}

s32 SzSound_StopSE(s32 arg0, s32 arg1) {
    State_00217410 *state = &gSzSound_sl;

    if (!D_0034F6E8.active) {
        return 0;
    }
    if (arg0 < 0 || arg0 >= 4) {
        return 0;
    }
    if (state->slots[arg0] < 0) {
        return 0;
    }
    if ((s64)SD_iGetSDStatus() & 0x4000) {
        return 0;
    }
    SD_SEStop(arg0, arg1);
    return 1;
}

s32 SzSound_PlayBGM(s32 arg0, s32 arg1) {
    if (D_0034F6E8.active == 0) {
        return 0;
    }
    SD_BGMPreLoad(arg0, arg1);
    return 1;
}

s32 SzSound_IsLoadingBGM(void) {
    if (D_0034F6E8.active == 0) {
        return 0;
    }
    return (SD_IsLoadingNow() != 0) ? 1 : 0;
}

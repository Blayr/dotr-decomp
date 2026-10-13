#include "common.h"

typedef struct {
    u32 value0 : 31;
    u8 flag : 1;
    u32 value4 : 30;
    u8 flags : 2;
} Flags_00214FD0;

s32 func_00214FD0(void *arg0) {
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

INCLUDE_ASM("asm/nonmatchings/main_060", func_00215060);

typedef struct {
    u16 entries[40];
    u8 pad_50[4];
} EntryList_002151D0;

typedef struct {
    u8 pad_0[0xFD94];
    EntryList_002151D0 lists[6];
    u8 pad_FF8C[0x14];
} SideData_002151D0;

extern u8 D_0034F6D0;

s32 func_002151D0(s32 arg0, s32 arg1, s32 arg2) {
    extern SideData_002151D0 D_0032F790[];
    s32 i;
    s32 side;
    u16 *entries;

    if (D_0034F6D0 == arg0) {
        side = 0;
    } else {
        side = 1;
    }
    entries = (u16 *)(arg1 * 0x54 + (u8 *)&D_0032F790[side] + 0xFD94);
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

INCLUDE_ASM("asm/nonmatchings/main_060", func_00215280);

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

extern u8 D_0034F6D0;

s32 func_002153D0(s32 arg0, s32 arg1) {
    extern Side_002153D0 D_0032F790[];
    s32 side;
    u16 card;
    Slot_002153D0 *slot;
    Card_002153D0 *entry;

    if (D_0034F6D0 == arg0) {
        side = 0;
    } else {
        side = 1;
    }
    slot = (Slot_002153D0 *)((u8 *)&D_0032F790[side] + arg1 * 0x54 + 0xFD94);
    if (arg0 < 0 || arg0 >= 2) {
        return 0;
    }
    card = slot->card;
    if (card == 999) {
        return 0;
    }
    entry = func_00214DD0(arg0, card, arg1, 1);
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

extern u8 D_0034F6D0;

static inline s32 count_002154E0(s32 player, s32 deck_index, s32 card_id) {
    extern Side_002154E0 D_0032F790[];
    s32 side;
    u16 *cards;
    s32 count;
    s32 i;

    if (D_0034F6D0 == player) {
        side = 0;
    } else {
        side = 1;
    }
    cards = (u16 *)((u8 *)&D_0032F790[side] + deck_index * 0x54 + 0xFD94);
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
    extern Side_002154E0 D_0032F790[];
    s32 side;
    u16 *cards;
    s32 i;

    if (D_0034F6D0 == player) {
        side = 0;
    } else {
        side = 1;
    }
    cards = (u16 *)((u8 *)&D_0032F790[side] + deck_index * 0x54 + 0xFD94);
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

s32 func_002154E0(s32 player, s32 deck_index, s32 card_id) {
    extern Side_002154E0 D_0032F790[];
    s32 side;
    Deck_002154E0 *deck;
    Entry_002154E0 *entry;
    u8 *card;
    s32 slot;

    if (D_0034F6D0 == player) {
        side = 0;
    } else {
        side = 1;
    }
    deck = (Deck_002154E0 *)((u8 *)&D_0032F790[side] + deck_index * 0x54 + 0xFD94);
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
    if ((entry = func_00214DD0(player, card_id, 3, 0)) == NULL) {
        return 0;
    }
    card = func_001DD0E0(card_id);
    if (card == NULL) {
        return 0;
    }
    deck->cost += card[3];
    deck->cards[slot] = card_id;
    entry->deck = deck_index;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_060", func_00215770);

typedef struct {
    u8 pad[0xFF9C];
    u8 flags;
    u8 tail[3];
} State_002158B0;

extern State_002158B0 D_0032F790[];
extern u8 D_0034F6D0;

s32 func_002158B0(s32 arg0) {
    s32 var_v1;
    State_002158B0 *state;

    if (D_0034F6D0 == arg0) {
        var_v1 = 0;
    } else {
        var_v1 = 1;
    }
    state = &D_0032F790[var_v1];
    if ((arg0 < 0) || (arg0 >= 2)) {
        return -1;
    }
    return state->flags & 3;
}

extern u8 D_0034F6D0;

typedef struct {
    u8 padding[0xFF9C];
    u8 mode : 2;
    u8 : 6;
} Flags_00215920;

s32 func_00215920(s32 arg0, s32 arg1) {
    s32 var_v1;
    u8 *temp_a2;

    if (D_0034F6D0 == arg0) {
        var_v1 = 0;
    } else {
        var_v1 = 1;
    }
    temp_a2 = (u8 *)D_0032F790 + (var_v1 * 0xFFA0);
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

extern u8 D_0034F6D0;

static inline s32 side_002159D0(s32 player) {
    if (D_0034F6D0 == player) {
        return 0;
    }
    return 1;
}

s32 func_002159D0(s32 arg0, s32 arg1) {
    u8 *side;
    Entry_002159D0 *entry;

    side = (u8 *)D_0032F790 + side_002159D0(arg0) * 0xFFA0;
    entry = (Entry_002159D0 *)(side + arg1 * sizeof(Entry_002159D0) + 0xFD94);
    if ((arg0 < 0) || (arg0 >= 2)) {
        return -1;
    }
    return entry->value;
}

#ifndef GAME_H
/* The game translation unit already declares this array with its local type. */
extern unsigned char D_0032F790[];
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

extern u8 D_0034F6D0;

s32 func_00215A60(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_v1;
    u16 *values;

    if (D_0034F6D0 == arg0) {
        var_v1 = 0;
    } else {
        var_v1 = 1;
    }
    values = ((Side_00215A60 *)D_0032F790)[var_v1].rows[arg1].values;
    if ((arg0 < 0) || (arg0 >= 2)) {
        return -1;
    }
    if ((arg2 < 0) || (arg2 >= 0x28)) {
        return -1;
    }
    return values[arg2];
}

INCLUDE_ASM("asm/nonmatchings/main_060", func_00215B10);

s32 func_00215C40(s32 arg0, s32 arg1) {
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

    if (D_0034F6D0 == arg0) {
        side = 0;
    } else {
        side = 1;
    }
    deck = (Deck_00215C40 *)((u8 *)D_0032F790 + side * 0xFFA0 + arg1 * sizeof(Deck_00215C40) + 0xFD94);
    if ((arg0 < 0) || (arg0 >= 2)) {
        return -1;
    }
    deck->total = 0;
    i = 0;
    card = deck->cards;
    do {
        data = func_001DD0E0(*card);
        if (data != NULL) {
            deck->total += data[3];
        }
        i++;
        card++;
    } while (i < 40);
    return deck->total;
}

INCLUDE_ASM("asm/nonmatchings/main_060", func_00215D30);

typedef struct Card_00215DE0 {
    u8 padding[0x48];
    u16 rank : 14;
    u16 flags : 2;
    u16 experience;
} Card_00215DE0;

extern u16 D_002D0868;
extern u8 D_0034F6D0;

s32 func_00215DE0(s32 player, s32 index) {
    s32 side;
    u8 *base;
    Card_00215DE0 *card;
    s32 rank;
    u16 *threshold;

    if (D_0034F6D0 == player) {
        side = 0;
    } else {
        side = 1;
    }
    base = (u8 *)D_0032F790 + side * 0xFFA0;
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

extern u8 D_0034F6D0;

static inline s32 side_00215F00(s32 player) {
    if (D_0034F6D0 == player) {
        return 0;
    }
    return 1;
}

s32 func_00215F00(s32 arg0, s32 arg1) {
    u8 *side;
    Entry_00215F00 *entry;

    side = (u8 *)D_0032F790 + side_00215F00(arg0) * 0xFFA0;
    entry = (Entry_00215F00 *)(side + arg1 * sizeof(Entry_00215F00) + 0xFD94);
    if ((arg0 < 0) || (arg0 >= 2)) {
        return -1;
    }
    return entry->value;
}

s32 func_00215F90(s32 arg0, s32 arg1) {
    s32 i;
    s32 count;
    s32 side;
    u16 *card;

    if (D_0034F6D0 == arg0) {
        side = 0;
    } else {
        side = 1;
    }
    card = (u16 *)((u8 *)D_0032F790 + side * 0xFFA0 + arg1 * 0x54 + 0xFD94);
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

s32 func_00215060(s32, s32, u32, s32);

static inline s32 side_00216040(s32 player) {
    extern u8 D_0034F6D0;
    if (D_0034F6D0 == player) {
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

s32 func_00216040(s32 arg0, s32 arg1, s32 arg2) {
    Card_00216040 *card;
    Entry_00216040 *entry;
    s32 count;

    if (arg0 < 0 || arg0 >= 2) {
        return 0;
    }
    if (arg1 == 0) {
        arg1 = data_00216040(arg0, D_0032F790)->defaultCard;
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

    card = (Card_00216040 *)data_00216040(arg0, D_0032F790) + arg2;
    entry = card->entries;
    for (count = 9; count-- != 0; entry++) {
        if (entry->card == 0) {
            do {
                entry->value = random_value_00216040();
            } while (func_00215060(arg0, arg1, entry->value, arg2) != 0);
            entry->card = arg1;
            card->assigned = 1;
            func_00216800(arg0, arg2);
            return 1;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_060", func_00216280);

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

s32 func_00216490(s32 arg0, s32 arg1) {
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
    entry = func_00214DD0(arg0, arg1, 3, 0);
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
extern State_002158B0 D_0032F790[];
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

extern Entry_00216580 D_002D0870[];
extern u8 D_0034F6D0;

s32 func_00216580(s32 arg0, s32 arg1) {
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
    if (D_0034F6D0 == arg0) {
        side = 0;
    } else {
        side = 1;
    }
    player = &D_0032F790[side];
    entry = D_002D0870;
    i = 0;
    do {
        decodedCard = func_001DE130(entry->card & 0x3FFF);
        if (decodedCard == arg1) {
            count = (u8 *)(i + (u32)player) + 0xFE90;
            *count = (*count + 1) % (((Flags_00216580 *)&D_002D0870[i])[1].count + 1);
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

extern State_002158B0 D_0032F790[];
extern Entry_00216580 D_002D0870[];
#endif


typedef struct State_002166D0 {
    u8 unk_0000[0xFE90];
    u8 replacements[16];
    u8 unk_FEA0[0x100];
} State_002166D0;

extern u8 D_0034F6D0;

s32 func_002166D0(s32 arg0, s32 arg1) {
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
    if (D_0034F6D0 == arg0) {
        side = 0;
    } else {
        side = 1;
    }
    {
        s32 i;

        state = (State_002166D0 *)D_0032F790 + side;
        entry = D_002D0870;
        i = 0;
        do {
            resolved = func_001DE130(entry->card & 0x3FFF);
            if (resolved == arg1) {
                replacement = state->replacements[i];
                if (replacement != 0) {
                    arg1 = (&D_002D0870[i].card)[replacement];
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
extern unsigned char D_0032F790[];
#endif


typedef struct Record_00216800 {
    u8 pad[0xFD88];
    u16 entries[5];
    u8 pad_end[0x20E];
} Record_00216800;

extern u8 D_0034F6D0;

s32 func_00216800(s32 arg0, s32 arg1) {
    s32 record_index;
    s32 i;
    Record_00216800 *record;

    if (D_0034F6D0 == arg0) {
        record_index = 0;
    } else {
        record_index = 1;
    }
    record = &((Record_00216800 *)D_0032F790)[record_index];
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
extern unsigned char D_0032F790[];
#endif


typedef struct {
    u8 padding[0xFD88];
    u16 card;
} Entry_00216920;

extern u8 D_0034F6D0;

s32 func_00216920(s32 arg0, s32 arg1) {
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
    if (D_0034F6D0 == arg0) {
        side = 0;
    } else {
        side = 1;
    }
    data = (u8 *)D_0032F790 + side * 0xFFA0;
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
extern unsigned char D_0032F790[];
#endif


typedef struct {
    u32 value : 31;
    u32 flag : 1;
    u8 pad[3];
    u8 flags : 6;
    u8 type : 2;
} Entry_002169F0;

extern u8 D_0034F6D0;

s32 func_002169F0(s32 arg0) {
    s32 rowIndex;
    Entry_002169F0 *entry;
    s32 remaining;
    s32 count;
    s32 side;
    u8 *row;

    side = D_0034F6D0 == arg0 ? 0 : 1;
    row = (u8 *)D_0032F790 + (side * 0xFFA0);
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
extern unsigned char D_0032F790[];
#endif


typedef struct {
    u32 value : 31;
    u32 flag : 1;
    u8 padding[3];
    u8 unused : 6;
    u8 category : 2;
} Entry_00216AC0;

extern u8 D_0034F6D0;

s32 func_00216AC0(s32 player, s32 card, s32 category) {
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
    if (D_0034F6D0 == player) {
        player = 0;
    } else {
        player = 1;
    }
    entry = (Entry_00216AC0 *)((u8 *)D_0032F790 + (player * 0xFFA0));
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
extern unsigned char D_0032F790[];
#endif


typedef struct Flags_00216BC0 {
    u8 unused : 6;
    u8 active : 1;
    u8 unused2 : 1;
} Flags_00216BC0;

extern u8 D_0034F6D0;

s32 func_00216BC0(s32 arg0, s32 arg1) {
    extern s32 func_0010B3C0();
    s32 var_v1;
    u8 *cards;

    if (D_0034F6D0 == arg0) {
        var_v1 = 0;
    } else {
        var_v1 = 1;
    }
    cards = (u8 *)D_0032F790 + var_v1 * 0xFFA0;
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
extern unsigned char D_0032F790[];
#endif


typedef struct Card_00216C70 {
    u8 padding[0x49];
    u8 flags : 6;
    u8 selected : 1;
    u8 flag7 : 1;
    u8 padding4A[2];
} Card_00216C70;

extern u8 D_0034F6D0;

s32 func_00216C70(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_v1;
    Card_00216C70 *cards;
    Card_00216C70 *card;

    var_v1 = (D_0034F6D0 == arg0) ? 0 : 1;
    cards = (Card_00216C70 *)((u8 *)D_0032F790 + var_v1 * 0xFFA0);
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

s32 func_00216D30(s32 arg0, s32 arg1) {
    typedef struct {
        u8 pad[0x49];
        u8 unused : 7;
        u8 enabled : 1;
        u8 tail[2];
    } Card_00216D30;
    s32 side;
    Card_00216D30 *cards;

    if (D_0034F6D0 == arg0) {
        side = 0;
    } else {
        side = 1;
    }
    cards = (Card_00216D30 *)&D_0032F790[side];
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

extern u8 D_0034F6D0;

s32 func_00216DF0(s32 arg0, s32 arg1, s32 arg2) {
    s32 side;
    u8 *table;
    Card_00216DF0 *card;

    if (D_0034F6D0 == arg0) {
        side = 0;
    } else {
        side = 1;
    }
    table = (u8 *)D_0032F790 + side * 0xFFA0;
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

s32 func_00216EC0(s32 arg0, s32 arg1) {
    s32 index;
    u8 *data;
    s32 flags;

    index = (D_0034F6D0 == arg0) ? 0 : 1;
    data = (u8 *)D_0032F790 + index * 0xFFA0;
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
extern unsigned char D_0032F790[];
#endif


typedef struct PlayerState_00216F80 {
    u8 pad[0xFEA0];
    u8 flags[0x100];
} PlayerState_00216F80;

extern u8 D_0034F6D0;

static inline s32 player_index_00216F80(s32 player) {
    if (D_0034F6D0 == player) {
        return 0;
    }
    return 1;
}

s32 func_00216F80(s32 player, s32 flag, s32 enabled) {
    PlayerState_00216F80 *state;

    state = &((PlayerState_00216F80 *)D_0032F790)[player_index_00216F80(player)];
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

extern Entry_002170A0 D_002D08D0[];
extern u16 D_002D08D2[];

u16 func_002170A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
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

    entry = D_002D08D0;
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
extern State_002158B0 D_0032F790[];
#endif


typedef struct Flags_002171B0 {
    u8 padding[0xFF9C];
    u8 : 5;
    u8 active : 1;
    u8 : 2;
} Flags_002171B0;

extern u8 D_0034F6D0;

s32 func_002171B0(s32 arg0) {
    s32 index;
    State_002158B0 *state;

    if (D_0034F6D0 == arg0) {
        index = 0;
    } else {
        index = 1;
    }
    state = &D_0032F790[index];
    if ((arg0 < 0) || (arg0 >= 2)) {
        return 0;
    }
    return ((Flags_002171B0 *)state)->active ? 1 : 0;
}

#ifndef GAME_H
/* The game translation unit already declares this array with its local type. */
extern unsigned char D_0032F790[];
#endif


typedef struct Flags_00217230 {
    u8 padding[0xFF9C];
    u8 unknown : 5;
    u8 enabled : 1;
    u8 : 2;
} Flags_00217230;

extern u8 D_0034F6D0;

s32 func_00217230(s32 arg0, s32 arg1) {
    s32 var_v1;
    u8 *temp_a2;

    if (D_0034F6D0 == arg0) {
        var_v1 = 0;
    } else {
        var_v1 = 1;
    }
    temp_a2 = (u8 *)D_0032F790 + (var_v1 * 0xFFA0);
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

extern u16 D_002D0850[];
extern u8 D_0034F6D0;

s32 func_002172D0(s32 arg0, s32 arg1, s32 arg2) {
    extern State_002158B0 D_0032F790[];
    s32 side;
    Card_002172D0 *base;
    Card_002172D0 *card;

    if (D_0034F6D0 == arg0) {
        side = 0;
    } else {
        side = 1;
    }
    base = (Card_002172D0 *)((u8 *)D_0032F790 + side * 0xFFA0);
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
    card->value = D_002D0850[arg2];
    return card->flags;
}

s32 func_002173D0(void) {
    func_00193808();
    return 1;
}

s32 func_002173F0(void) {
    return 1;
}

s32 func_00217400(void) {
    return 1;
}

typedef struct State_00217410 {
    s16 slots[4];
    s8 enabled : 1;
    s8 reserved : 7;
    u8 padding[3];
} State_00217410;

extern State_00217410 D_0034F6E0;
extern u8 D_002D0930[];

void func_00217410(void) {
    extern u8 *func_00197548();
    State_00217410 *state = &D_0034F6E0;
    s16 *slot;
    s32 i;

    func_0020B3C0((s8 *)&D_0034F6E0, 0, 0xC);
    state->enabled = func_00197548(D_002D0930) ? 1 : 0;
    if (state->enabled) {
        func_00109CA0(0x400000);
        func_0010A160(0x80, 0x80);
        slot = state->slots;
        i = 0;
        do {
            i += 1;
            *slot++ = -1;
        } while (i < 4);
        func_00217A70(1);
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


void func_002174D0(void) {
    extern struct State_00217410 D_0034F6E0;
    extern Flags_002174D0 D_0034F6E8;
    State_002174D0 *state = (State_002174D0 *)&D_0034F6E0;

    if (D_0034F6E8.active) {
        func_00109D50();
        state->flags.active = 0;
    }
}

typedef struct {
    s8 active : 1;
} Flags_00217530;

extern Flags_00217530 D_0034F6E8;

s32 func_00217530(void) {
    return D_0034F6E8.active != 0 ? 1 : 0;
}

#ifndef GAME_H
/* The game translation unit already declares this global with its local type. */
typedef struct {
    signed char active : 1;
} Flags_00217530;

extern Flags_00217530 D_0034F6E8;
#endif

void func_00217550(void) {
    if (D_0034F6E8.active) {
        func_00109DC0();
    }
}

INCLUDE_ASM("asm/nonmatchings/main_060", func_00217590);

#ifndef GAME_H
typedef struct {
    signed char active : 1;
} Flags_002176B0;
extern Flags_002176B0 D_0034F6E8;
#endif

s32 func_002176B0(void) {
    extern s64 func_0010A8A0();

    if (!D_0034F6E8.active) {
        return 0;
    }
    return !((s32)func_0010A8A0() & 0x4000) ? 1 : 0;
}

INCLUDE_ASM("asm/nonmatchings/main_060", func_00217710);

s32 func_002177E0(s32 arg0, s32 arg1, s32 arg2) {
    extern s64 func_0010A8A0();
    State_00217410 *state = &D_0034F6E0;

    if (!D_0034F6E8.active) {
        return 0;
    }
    if (arg0 < 0 || arg0 >= 4) {
        return 0;
    }
    if (state->slots[arg0] < 0) {
        return 0;
    }
    if ((s32) func_0010A8A0() & 0x4000) {
        return 0;
    }
    arg1 &= 0x7FFF;
    arg2 &= 0x7FFF;
    func_0010A1D0(arg0, arg1, arg2);
    return 1;
}

s32 func_002178C0(s32 arg0, s32 arg1) {
    State_00217410 *state = &D_0034F6E0;

    if (!D_0034F6E8.active) {
        return 0;
    }
    if (arg0 < 0 || arg0 >= 4) {
        return 0;
    }
    if (state->slots[arg0] < 0) {
        return 0;
    }
    if ((s64)func_0010A8A0() & 0x4000) {
        return 0;
    }
    func_0010A3B0(arg0, arg1);
    return 1;
}

s32 func_00217980(s32 arg0, s32 arg1) {
    if (D_0034F6E8.active == 0) {
        return 0;
    }
    func_00109E80(arg0, arg1);
    return 1;
}

s32 func_002179C0(void) {
    if (D_0034F6E8.active == 0) {
        return 0;
    }
    return (func_00109F10() != 0) ? 1 : 0;
}

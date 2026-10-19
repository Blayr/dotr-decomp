/* The duel screen, part 7 of 12: hand actions, turns, card sessions, card nodes, card drawing and cursors. Starts where it does for the compiler (see README, How the files are split). */

#include "common.h"

/* Fills side `side`'s hand at the start of its turn: lays out the cards it holds and, if `draw`, draws up to five
   (with the destiny draw). */
void lSzDuel_InitHandUp(s32 side, s32 draw) {
    u16 ids[4];
    s16 w[4];
    u8 *g = duelState.b;
    u8 *p;
    s32 i;
    s32 x;
    s32 cnt;
    s32 flag;
    s32 ok;
    s32 id;
    s32 n;
    s32 have;
    s32 v;
    s16 r;
    s32 idx;

    p = duelState.b + side * 0x350;
    SzDuel_PackHand(side);
    lSzDuel_InitHandInfo(side, 0, 999, 0, 0, 0, 0);
    x = -250;
    for (i = 0; i < g[0xD49]; i++) {
        v = SzDuel_InqHand(side, i);
        if (v < 0) {
            v = 999;
        } else {
            v &= 0xFFF;
        }
        lSzDuel_InitHandInfo(side, i + 1, v, x, 0x1C0, x, -8);
        x += 0x7D;
    }
    if (draw != 0) {
        have = SzDuel_GetHandCount(side);
        n = SzDuel_GetDeckCount(side);
        cnt = have + n;
        cnt = cnt < 5 ? cnt : 5;
        ok = n > 0;
        flag = 0;
        if (ok) {
            ok = p[0x344] > 0;
        }
        if (ok && !(p[0x344] & 0x80)) {
            flag = 1;
        }
        if (flag) {
            cnt = cnt + 1 < 5 ? cnt + 1 : 5;
        }
        for (; i < cnt; i++) {
            id = 999;
            if (flag && i + 1 >= cnt) {
                if (Ta_GetDestinyDraw(side, ids, w, 0) >= 0) {
                    r = func_001A22C0(100.0f * ((f32)func_0019A5C8() / 2147483648.0f));
                    idx = 2;
                    if (r < w[0]) {
                        idx = 0;
                    } else if (r < w[0] + w[1]) {
                        idx = 1;
                    } else {
                    }
                    id = ids[idx];
                }
            }
            if (id == 999) {
                id = SzDuel_DrawDeck(side);
            }
            SzDuel_AddHand(side, id);
            lSzDuel_InitHandInfo(side, i + 1, id, 0x2EE, 0x1C0, 0x2EE, -8);
        }
        for (; i < 5; i++) {
            SzDuel_AddHand(side, 999);
            lSzDuel_InitHandInfo(side, i + 1, 999, 0, 0, 0, 0);
        }
    } else {
        for (; i < 5; i++) {
            lSzDuel_InitHandInfo(side, i + 1, 999, 0, 0, 0, 0);
        }
    }
    g[0xD4A] = SzDuel_GetHandCount(side);
    for (i = 0; i < g[0xD4A]; i++) {
        g[0xD2C + i] = i + 1;
    }
}

extern s32 CRC_CardConstInfo;

typedef struct {
    s8 bit0 : 1;
    s8 bit1 : 1;
    s8 bit2 : 1;
    s8 bit3 : 1;
    s8 bit4 : 1;
    s8 bit5 : 1;
    s8 bit6 : 1;
    s8 bit7 : 1;
} Flags_001D8080;

/* Card control record `index`, or NULL. */
static inline u8 *lookup_001D8080(s32 index) {
    if (index < 0 || index >= 6) {
        return NULL;
    }
    return cardControls + index * 0xA0;
}

/* Frees a card draw record. */
static inline void releaseModel_001D8080(u8 *model) {
    extern void SzDuel_ClearDrawCard();

    if (model != NULL) {
        SzDuel_ClearDrawCard(model);
        *(s32 *)(model + 0x90) = 0;
    }
}

/* Frees a card control record and its card. */
static inline void freeSlot_001D8080(u8 *slot) {
    if (slot != NULL) {
        if (*(u8 **)slot != NULL) {
            releaseModel_001D8080(*(u8 **)slot);
        }
        SzDuel_ClearCardControl(slot);
    }
}

/* Puts side `side`'s picked hand cards back into the hand. */
s32 lSzDuel_InitHandCancel(s32 side) {
    u8 *base;
    u8 *slot;
    s32 index;
    s32 step;
    s32 result;
    u8 *candidate;

    base = duelState.b;
    if (CRC_CardConstInfo != 0 && *(void **)(*(u8 **)(base + 0x6CC) + 4) != NULL) {
        if ((slot = cardControls) != NULL && *(u8 **)slot != NULL) {
            freeSlot_001D8080(slot);
        }
        ((Flags_001D8080 *)(*(u8 **)(base + 0x6CC) + 0x57))->bit7 = 0;
        ((Flags_001D8080 *)(*(u8 **)(base + 0x6CC) + 0x58))->bit0 = 0;
        ((Flags_001D8080 *)(*(u8 **)(base + 0x6CC) + 0x58))->bit2 = 0;
        ((Flags_001D8080 *)(*(u8 **)(*(u8 **)(base + 0x6CC) + 4) + 0x83))->bit7 = 0;
    }

    step = -0xFA;
    index = 0;
    do {
        result = SzDuel_InqHand(side, index);
        if (result >= 0 && (result & 0xFFF) != 999) {
            candidate = lookup_001D8080(index + 1);
            if (candidate != NULL && *(s32 *)candidate != 0) {
                ((Flags_001D8080 *)(candidate + 0x9F))->bit2 = 1;
                ((Flags_001D8080 *)(candidate + 0x9F))->bit4 = 0;
                lSzDuel_SetCardCtl(candidate, step, 0x1C0, step, -8, 0x80, 0x80);
            }
        }
        index++;
        step += 0x7D;
    } while (index < 5);

    base[0xD4A] = SzDuel_GetHandCount(side);
    for (index = 0; index < base[0xD4A]; index++) {
        base[0xD2C + index] = index + 1;
    }
    return 1;
}

extern u8 D_003181DE;

typedef struct Flags_001D82C0 {
    s8 bit0 : 1;
    s8 bit1 : 1;
    s8 bit2 : 1;
    s8 bit3 : 1;
    s8 bit4 : 1;
    s8 bit5 : 1;
    s8 bit6 : 1;
    s8 bit7 : 1;
} Flags_001D82C0;

typedef struct Vec4_001D82C0 {
    f32 x, y, z, w;
} Vec4_001D82C0;

typedef struct Model_001D82C0 {
    Vec4_001D82C0 position;
    Vec4_001D82C0 rotation;
    u8 pad20[0x10];
    Vec4_001D82C0 scale;
    u8 color[4];
    u8 pad44[0x3D];
    Flags_001D82C0 flags81;
    u8 pad82;
    Flags_001D82C0 flags83;
    u8 pad84[0xC];
    void *owner;
    u8 pad94[0xC];
} Model_001D82C0;

typedef struct Item_001D82C0 {
    s32 unk0;
    Model_001D82C0 *model;
    u8 pad8[0x4B];
    u8 unk53;
    u8 pad54[3];
    Flags_001D82C0 flags57;
    Flags_001D82C0 flags58;
    u8 pad59[3];
} Item_001D82C0;

typedef struct Copy90_001D82C0 {
    __int128 words[9];
} Copy90_001D82C0;

typedef struct Node_001D82C0 {
    Model_001D82C0 *model;
    u8 pad4[0xC];
    Vec4_001D82C0 position;
    Vec4_001D82C0 target;
    Vec4_001D82C0 rotation;
    s32 values40[4];
    s32 values50[4];
    Vec4_001D82C0 values60;
    Vec4_001D82C0 scale;
    s32 values80[4];
    u8 pad90[8];
    s16 speed;
    s16 unk9A;
    s32 index : 26;
    s8 bit2 : 1;
    s8 bit3 : 1;
    s8 bit4 : 1;
    s8 bit5 : 1;
    s8 bit6 : 1;
    s8 bit7 : 1;
} Node_001D82C0;

typedef struct State_001D82C0 {
    u8 pad0[0x6CC];
    Item_001D82C0 *selected;
    u8 pad6D0[0x65C];
    s8 slots[0x1E];
    u8 mode;
    u8 padD4B[3];
    u8 count;
    u8 current;
} State_001D82C0;

/* A free card request record, cleared. */
static inline Model_001D82C0 *get_model_001D82C0(void) {
    extern void SzDuel_ClearDrawCard();
    Model_001D82C0 *model = (Model_001D82C0 *)cardRequests;
    s32 count = 0;
    do {
        if (model->owner == NULL) {
            SzDuel_ClearDrawCard(model);
            return model;
        }
        count++;
        model++;
    } while (count < 0x20);
    return NULL;
}

/* Lines up side `side`'s picked hand cards for a fusion combo. */
s32 lSzDuel_InitHandCombo(s32 side) {
    extern void *SzDuel_GetCardInfo();
    extern void SzDuel_ClearDrawCard();
    State_001D82C0 *state = (State_001D82C0 *)duelState.b;
    s32 next;
    Item_001D82C0 *copy;
    Node_001D82C0 *primary;
    Model_001D82C0 *model;
    s32 i;
    s32 slot;
    s32 x;
    s32 y;
    Node_001D82C0 *node;
    s32 baseX;
    s32 initial;

    if (D_003181DE > 1) {
        initial = state->count;
    } else {
        initial = 1;
    }
    next = initial + 1;
    state->slots[0] = 6;
    if (state->selected != NULL) {
        if (state->selected->model != NULL) {
            primary = (Node_001D82C0 *)cardControls;
            copy = SzDuel_GetCardInfo(2, 0);
            if (primary != NULL && copy != NULL) {
                *copy = *state->selected;
                copy->unk53 = 0;
                primary->model = get_model_001D82C0();
                model = primary->model;
                if (model != NULL) {
                    copy->model = model;
                    copy->model->owner = copy;
                    *(Copy90_001D82C0 *)model = *(Copy90_001D82C0 *)state->selected->model;
                    model->color[3] = 0x80;
                    model->color[0] = 0x80;
                    model->color[1] = 0x80;
                    model->color[2] = 0x80;
                    model->flags83.bit7 = 1;
                    model->flags81.bit5 = 1;
                    primary->bit3 = 1;
                    primary->position = model->position;
                    Ex3d_GetPointOnScreen(&primary->target, -125.0f, -8.0f);
                    primary->bit4 = 1;
                    primary->rotation = model->rotation;
                    primary->values40[0] = 0;
                    primary->values40[1] = 0x10000;
                    primary->values40[2] = 0x10000;
                    primary->values40[3] = 0;
                    primary->bit5 = 1;
                    primary->values50[0] = 0;
                    primary->values50[1] = 0;
                    primary->values50[2] = 0;
                    primary->values50[3] = 0;
                    Ex3d_GetLookVector((s32)&primary->values60);
                    primary->bit6 = 1;
                    primary->scale = model->scale;
                    primary->values80[0] = 0x3EF00000;
                    primary->values80[1] = 0x3EFA6F4E;
                    primary->values80[2] = 0x3F800000;
                    primary->values80[3] = 0;
                    primary->speed = 0x80;
                    primary->unk9A = 0;
                    SzDuel_DoCardControl0(primary);
                    state->slots[0] = primary->index = 0;
                }
            }
            state->selected->flags58.bit0 = 1;
            state->selected->flags57.bit7 = 1;
            state->selected->flags58.bit2 = 1;
            state->selected->model->flags83.bit7 = 1;
        }
    }
    baseX = -250;
    i = 0;
    do {
        s32 index = i + 1;
        if (index < 0 || index >= 6) {
            node = NULL;
        } else {
            node = (Node_001D82C0 *)(index * 0xA0 + cardControls);
        }
        if (node != NULL && node->model != NULL) {
            s32 result = SzDuel_InqHand(side, i);
            if (result >= 0 && (result & 0xFFF) != 999) {
                slot = (result & 0xF000) >> 12;
                y = 448;
                x = baseX;
                if (state->count == 0 && i == state->current) {
                    slot = 1;
                }
                switch (state->mode) {
                case 1:
                    if (slot == 1) {
                        y = -8;
                        node->bit4 = 1;
                        x = 0;
                    }
                    break;
                default:
                    if (slot != 0) {
                        if (state->selected != NULL) {
                            x = (slot - 1) * 16 + 125;
                            y = -8;
                        } else if (slot == 1) {
                            x = -125;
                            y = -8;
                        } else {
                            x = (slot - 2) * 16 + 125;
                            y = -8;
                        }
                        node->bit4 = 1;
                    }
                    break;
                }
                node->bit2 = 0;
                Ex3d_GetPointOnScreen(&node->position, (f32)baseX, -8.0f);
                Ex3d_GetPointOnScreen(&node->target, (f32)x, (f32)y);
                node->rotation.x = 0;
                node->rotation.y = 0;
                node->rotation.z = 0;
                node->rotation.w = 0;
                node->values40[0] = 0;
                node->values40[1] = 0x10000;
                node->values40[2] = 0;
                node->values40[3] = 0;
                node->speed = 0x80;
                node->unk9A = 0;
                SzDuel_DoCardControl0(node);
                if (slot == 0) {
                    state->slots[next++] = node->index;
                } else {
                    state->slots[slot] = node->index;
                }
            }
        }
        i++;
        baseX += 125;
    } while (i < 5);
    return 1;
}

typedef struct Model_001D8880 {
    u8 pad0[0x40];
    u8 r;
    u8 g;
    u8 b;
    u8 pad43[0x4D];
    void *unk90;
} Model_001D8880;

typedef struct Slot_001D8880 {
    Model_001D8880 *model;
} Slot_001D8880;

/* Card control record `index`, or NULL. */
static inline Slot_001D8880 *lookup_001D8880(s32 index) {
    if (index < 0 || index >= 6) {
        return NULL;
    }
    return (Slot_001D8880 *) (cardControls + index * 0xA0);
}

/* Dims the hand cards whose level is above side `side`'s summon power (`dim` = 0 lights them all). */
s32 lSzDuel_InitHandDark(s32 side, s32 dim) {
    extern s32 SzDuel_GetPlayer();
    s32 i;
    Slot_001D8880 *slot;
    Model_001D8880 *model;
    s32 summonPower;
    s32 cardLevel;
    s32 other;
    s32 bits;
    s32 flag;

    bits = SzGame_GetMenuNum(0x1D);
    flag = (bits & (1 << side)) ? 1 : 0;
    other = side ^ 1;
    if (flag) {
        if (SzDuel_GetPlayer(side) < 0x20 && SzDuel_GetPlayer(other) >= 0x64) {
            dim = 0;
        }
    } else if ((u16) SzPad_Check(side, 1, 2) == 0) {
        dim = 0;
    }

    for (i = 0; i < 6; i++) {
        slot = lookup_001D8880(i);
        if (slot != NULL && slot->model != NULL) {
            model = slot->model;
            summonPower = SzDuel_GetSummonPower(side);
            cardLevel = SzDuel_GetUnitLevel2(slot->model->unk90, 0);
            if (dim != 0 && summonPower < cardLevel) {
                model->r = 0x40;
                model->g = 0x40;
                model->b = 0x40;
            } else {
                model->r = 0x80;
                model->g = 0x80;
                model->b = 0x80;
            }
        }
    }
    return 1;
}

typedef struct Flags81_001D89F0 {
    s8 : 4;
    s8 bit4 : 1;
    s8 bit5 : 1;
    s8 bit6 : 1;
    s8 : 1;
} Flags81_001D89F0;

typedef struct FlagsHigh_001D89F0 {
    s8 : 7;
    s8 enabled : 1;
} FlagsHigh_001D89F0;

typedef struct Flags58_001D89F0 {
    s8 bit0 : 1;
    s8 : 1;
    s8 bit2 : 1;
    s8 : 5;
} Flags58_001D89F0;

typedef struct Model_001D89F0 {
    u8 pad00[0x10];
    f32 position[4];
    f32 rotation[4];
    f32 scale[4];
    u8 pad40[0x41];
    Flags81_001D89F0 flags81;
    u8 pad82;
    FlagsHigh_001D89F0 flags83;
    u8 pad84[0xC];
    void *owner;
    u8 pad94[0xC];
} Model_001D89F0;

typedef struct Entry_001D89F0 {
    u8 pad00[4];
    Model_001D89F0 *model;
    u8 pad08[0x34];
    u16 id;
    u8 pad3E[2];
    u8 field40;
    u8 field41;
    u8 pad42[2];
    s8 player;
    s8 slot;
    u8 pad46[2];
    s8 field48;
    u8 pad49[0xE];
    FlagsHigh_001D89F0 flags57;
    Flags58_001D89F0 flags58;
} Entry_001D89F0;

typedef union Status_001D89F0 {
    struct {
        u32 slot : 26;
        u32 : 6;
    } index;
    struct {
        u8 pad[3];
        s8 : 2;
        s8 bit2 : 1;
        s8 bit3 : 1;
        s8 : 4;
    } flags;
} Status_001D89F0;

typedef struct Slot_001D89F0 {
    Model_001D89F0 *model;
    u8 pad04[0x98];
    Status_001D89F0 status;
} Slot_001D89F0;

/* Card control record `index`, or NULL. */
static inline Slot_001D89F0 *lookupSlot_001D89F0(s32 index) {
    if (index < 0 || index >= 6) {
        return NULL;
    }
    return (Slot_001D89F0 *)(cardControls + index * 0xA0);
}

/* A free card request record, cleared. */
static inline Model_001D89F0 *allocateModel_001D89F0(void) {
    extern void SzDuel_ClearDrawCard();
    Model_001D89F0 *candidate;
    s32 i;

    candidate = (Model_001D89F0 *)cardRequests;
    i = 0;
    do {
        if (candidate->owner == NULL) {
            SzDuel_ClearDrawCard(candidate);
            return candidate;
        }
        i++;
        candidate++;
    } while (i < 32);
    return NULL;
}

/* Sets hand slot `slot` of side `side` to `card`, moving from (fromX, fromY) to (toX, toY) on screen. */
s32 lSzDuel_InitHandInfo(s32 side, s32 handSlot, s32 card, s32 fromX, s32 fromY, s32 toX, s32 toY) {
    extern void *SzDuel_GetCardInfo();
    u8 *player;
    Entry_001D89F0 *entry;
    Slot_001D89F0 *slot;
    Model_001D89F0 *model;

    player = duelState.b + side * 0x350;
    entry = SzDuel_GetCardInfo(2, handSlot);
    if (entry == NULL) {
        return 0;
    }
    SzDuel_InitCardInfo(entry, card);
    entry->player = side;
    entry->slot = handSlot;
    entry->field40 = player[0x33D];
    entry->field41 = player[0x33E];
    if (entry->id != 999) {
        slot = lookupSlot_001D89F0(handSlot);
        entry->field48 = Ta_GetSummonRev(side, entry->id);
        if (slot != NULL) {
            if (slot->model == NULL) {
                slot->model = allocateModel_001D89F0();
            }
            model = slot->model;
            if (model != NULL) {
                entry->model = model;
                entry->model->owner = entry;
                model->scale[0] = 0.46875f;
                model->scale[1] = 0.489130437f;
                model->scale[2] = 1.0f;
                model->scale[3] = 0.0f;
                model->position[0] = 0.0f;
                model->position[1] = 0.0f;
                model->position[2] = 0.0f;
                model->position[3] = 0.0f;
                model->flags83.enabled = 1;
                model->flags81.bit4 = 0;
                model->flags81.bit6 = 0;
                model->flags81.bit5 = 1;
                Ex3d_GetLookVector((s32)model->rotation);
                slot->status.flags.bit2 = 1;
                slot->status.flags.bit3 = 1;
                lSzDuel_SetCardCtl(slot, fromX, fromY, toX, toY, 0, 0x80);
                slot->status.index.slot = handSlot;
            }
        }
    }
    entry->flags57.enabled = 1;
    entry->flags58.bit0 = 1;
    entry->flags58.bit2 = 1;
    return 1;
}

typedef struct Flags_001D8CD0 {
    s8 bit0 : 1;
    s8 bit1 : 1;
    s8 bit2 : 1;
    s8 bit3 : 1;
    s8 bit4 : 1;
    s8 bit5 : 1;
    s8 bit6 : 1;
    s8 bit7 : 1;
} Flags_001D8CD0;

typedef struct Index_001D8CD0 {
    u32 index : 26;
    u32 flags : 6;
} Index_001D8CD0;

/* A free card request record, cleared. */
static inline u8 *allocate_001D8CD0(void) {
    extern void SzDuel_ClearDrawCard();
    u8 *p = cardRequests;
    s32 i = 0;

    do {
        if (*(s32 *)(p + 0x90) == 0) {
            SzDuel_ClearDrawCard(p);
            return p;
        }
        i++;
        p += 0xA0;
    } while (i < 32);
    return NULL;
}

/* Sets hand slot `slot` of side `side` to `card` at (x, y) in 3D. */
s32 lSzDuel_InitHandInfo2(s32 side, s32 slot, s32 card, s32 x, s32 y) {
    extern void *SzDuel_GetCardInfo();
    u8 *player;
    u8 *object;
    u8 *entry;
    u8 *resource;

    player = duelState.b + side * 0x350;
    object = SzDuel_GetCardInfo(2, slot);
    if (object == NULL) {
        return 0;
    }
    SzDuel_InitCardInfo(object, card);
    *(s8 *)(object + 0x44) = side;
    *(s8 *)(object + 0x45) = slot;
    *(u8 *)(object + 0x40) = *(u8 *)(player + 0x33D);
    *(u8 *)(object + 0x41) = *(u8 *)(player + 0x33E);
    if (*(u16 *)(object + 0x3C) != 999) {
        if (slot < 0 || slot >= 6) {
            entry = NULL;
        } else {
            entry = cardControls + slot * 0xA0;
        }
        if (entry != NULL) {
            if (*(u8 **)entry == NULL) {
                *(u8 **)entry = allocate_001D8CD0();
            }
            resource = *(u8 **)entry;
            if (resource != NULL) {
                *(u8 **)(object + 4) = resource;
                *(u8 **)(*(u8 **)(object + 4) + 0x90) = object;
                *(s32 *)(resource + 0x30) = 0x3EF00000;
                *(s32 *)(resource + 0x34) = 0x3EFA6F4E;
                *(s32 *)(resource + 0x38) = 0x3F800000;
                *(s32 *)(resource + 0x3C) = 0;
                *(s32 *)(resource + 0x10) = 0;
                *(s32 *)(resource + 0x14) = 0;
                *(s32 *)(resource + 0x18) = 0;
                *(s32 *)(resource + 0x1C) = 0;
                ((Flags_001D8CD0 *)(resource + 0x83))->bit6 = 1;
                ((Flags_001D8CD0 *)(resource + 0x83))->bit7 = 1;
                ((Flags_001D8CD0 *)(resource + 0x81))->bit4 = 1;
                ((Flags_001D8CD0 *)(resource + 0x81))->bit6 = 1;
                ((Flags_001D8CD0 *)(resource + 0x81))->bit5 = 1;
                Ex3d_GetLookVector((s32)(resource + 0x20));
                ((Flags_001D8CD0 *)(entry + 0x9F))->bit2 = 0;
                ((Flags_001D8CD0 *)(entry + 0x9F))->bit3 = 1;
                lSzDuel_SetCardCtl2(entry, x, y, x, y, 128, 128);
                ((Index_001D8CD0 *)(entry + 0x9C))->index = slot;
            }
        }
        *(s8 *)(object + 0x48) = Ta_GetSummonRev(side, *(u16 *)(object + 0x3C));
    }
    ((Flags_001D8CD0 *)(object + 0x57))->bit7 = 1;
    ((Flags_001D8CD0 *)(object + 0x58))->bit0 = 1;
    ((Flags_001D8CD0 *)(object + 0x58))->bit2 = 1;
    return 1;
}

/* Starts card control `control` moving on screen from (fromX, fromY) to (toX, toY) over `frames` frames. */
s32 lSzDuel_SetCardCtl(void *control, s32 fromX, s32 fromY, s32 toX, s32 toY, s32 delay, s32 frames) {
    if (control == NULL) {
        return 0;
    }
    *(f32 *)((u8 *)control + 0x10) = (f32) fromX;
    *(f32 *)((u8 *)control + 0x14) = (f32) fromY;
    *(s32 *)((u8 *)control + 0x18) = 0;
    *(s32 *)((u8 *)control + 0x1C) = 0;
    *(f32 *)((u8 *)control + 0x20) = (f32) toX;
    *(f32 *)((u8 *)control + 0x24) = (f32) toY;
    *(s32 *)((u8 *)control + 0x28) = 0;
    *(s32 *)((u8 *)control + 0x2C) = 0;
    *(s16 *)((u8 *)control + 0x98) = (s16) frames;
    *(s16 *)((u8 *)control + 0x9A) = (s16) delay;
    SzDuel_DoCardControl0(control);
    return 1;
}

/* Starts card control `control` moving in 3D from (fromX, fromY) to (toX, toY) over `frames` frames. */
s32 lSzDuel_SetCardCtl2(void *control, s32 fromX, s32 fromY, s32 toX, s32 toY, s32 delay, s32 frames) {
    if (control == NULL) {
        return 0;
    }
    Ex3d_GetPointOnScreen((u8 *) control + 0x10, (f32) fromX, (f32) fromY);
    Ex3d_GetPointOnScreen((u8 *) control + 0x20, (f32) toX, (f32) toY);
    *(s16 *)((u8 *) control + 0x98) = (s16) frames;
    *(s16 *)((u8 *) control + 0x9A) = (s16) delay;
    SzDuel_DoCardControl0(control);
    return 1;
}

/* Turns the camera to the current side's cursor at (x, z) over `frames` frames. */
void lSzDuel_LockCamera(s32 frames, s32 x, s32 z) {
    f32 look[4];
    f32 target[4];
    u8 *side;

    side = duelState.b + (duelState.s.turnOwner * 0x350);
    SzView_IV2V(side + 0x1D0, look);
    target[0] = (f32) x;
    target[2] = (f32) z;
    target[1] = (f32) *(s8 *)(side + 0x345);
    SzView_ReqCamera(0, 0, 3, (u16)frames, 0, target);
    SzView_ReqCamera(0, 0, 4, frames & 0xFFFF, 0, look);
}

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4_001D91B0;

/* Turns the camera between board squares (x0, z0) and (x1, z1) over `frames` frames. */
void lSzDuel_LockCamera2(s32 frames, s32 column0, s32 row0, s32 column1, s32 row1) {
    Vec4_001D91B0 saved;
    f32 pos[4];
    f32 camera[4];
    u8 *p;
    s32 x0;
    s32 z0;
    s32 x1;
    s32 z1;
    s32 angle;
    u8 *cur;

    p = duelState.b + duelState.s.turnOwner * 0x350;
    saved = *(Vec4_001D91B0 *)(p + 0x1D0);
    x0 = (s32)(f32)((column0 - 3) * 50);
    z0 = (s32)(f32)((row0 - 3) * 50);
    x1 = (s32)(f32)((column1 - 3) * 50);
    z1 = (s32)(f32)((row1 - 3) * 50);
    angle = (s32)(65536.0f * (func_001A6C18((f32)(z1 - z0), (f32)(x1 - x0)) / 6.2831855f));
    *(s32 *)(p + 0x1D0) = 0x96;
    *(s32 *)(p + 0x1D4) = (((angle + 0x80) >> 8) << 8) + 0x4000;
    *(s32 *)(p + 0x1D8) = 0x4000;
    cur = duelState.b + duelState.s.turnOwner * 0x350;
    SzView_IV2V(cur + 0x1D0, camera);
    pos[0] = (f32)((x0 + x1) >> 1);
    pos[2] = (f32)((z0 + z1) >> 1);
    pos[1] = (f32)*(s8 *)(cur + 0x345);
    SzView_ReqCamera(0, 0, 3, (u16)frames, 0, pos);
    SzView_ReqCamera(0, 0, 4, frames & 0xFFFF, 0, camera);
    *(Vec4_001D91B0 *)(p + 0x1D0) = saved;
}

typedef struct {
    u8 pad0[0x40];
    u8 x;
    u8 y;
    u8 pad42[2];
    u8 owner;
    u8 slot;
    u8 pad46[0x11];
    s8 pad57 : 4;
    s8 flag : 1;
    s8 pad57b : 3;
} Card_001D9420;

/* Whether a board card is hidden from the player watching (face down and not theirs). */
s32 lSzDuel_IsUnitHide(void *unit) {
    u8 *duel = duelState.b;
    s32 result;
    void **cell;
    s32 me;
    s32 other;
    s32 flag;
    Card_001D9420 *card = unit;
    s32 target;
    s32 bits;
    extern s32 SzDuel_GetPlayer();

    result = 0;
    if (card != NULL) {
        cell = SzDuel_GetMapInfo(card->x, card->y);
        bits = SzGame_GetMenuNum(0x1D);
        flag = (bits & (1 << card->owner)) ? 1 : 0;
        me = duel[0xD3C];
        other = duel[0xD3C] ^ 1;
        if (card->owner >= 2) {
            return 0;
        }
        if (cell == NULL || *cell != card) {
            if (flag) {
                if (SzDuel_GetPlayer(me) < 0x20 && SzDuel_GetPlayer(other) >= 0x64) {
                    result = 1;
                }
            } else if ((u16) SzPad_Check(duel[0xD3C], 1, 2) == 0) {
                result = 1;
            }
        } else {
            result = Ta_IsUnitHide((s32) card, duel[0xD3C]);
            if (result == 0 && card->flag == 0) {
                target = Ta_IsUnitControl(card->owner, card->slot);
                if (flag) {
                    if (SzDuel_GetPlayer(me) < 0x20 && SzDuel_GetPlayer(other) >= 0x64 && SzDuel_GetPlayer(target) < 0x20) {
                        result = 1;
                    }
                } else if (duel[0xD3C] == target) {
                    if ((u16) SzPad_Check(duel[0xD3C], 1, 2) == 0) {
                        result = 1;
                    }
                } else {
                    result = 1;
                }
            }
        }
    }
    return result;
}

/* Debug: steps through cards with the pad. */
void SzDuel_ActCardTest(void) {
    u8 *p = cardTestState;
    if (SzPad_Check(0, 2, 0x1000) != 0) {
        *(s32 *)(p + 0x5C) = (*(s32 *)(p + 0x5C) + 0x10400) % 0x10000;
    }
    if (SzPad_Check(0, 2, 0x4000) != 0) {
        *(s32 *)(p + 0x5C) = (*(s32 *)(p + 0x5C) + 0xFC00) % 0x10000;
    }
    if (SzPad_Check(0, 2, 0x2000) != 0) {
        *(s32 *)(p + 0x60) = (*(s32 *)(p + 0x60) + 0x10400) % 0x10000;
    }
    if (SzPad_Check(0, 2, 0x8000) != 0) {
        *(s32 *)(p + 0x60) = (*(s32 *)(p + 0x60) + 0xFC00) % 0x10000;
    }
    if (SzPad_Check(0, 2, 8) != 0) {
        *(s32 *)(p + 0x64) = (*(s32 *)(p + 0x64) + 0x10400) % 0x10000;
    }
    if (SzPad_Check(0, 2, 4) != 0) {
        *(s32 *)(p + 0x64) = (*(s32 *)(p + 0x64) + 0xFC00) % 0x10000;
    }
    if (SzPad_Check(0, 2, 2) != 0) {
        *(s32 *)(p + 0x70) = (*(s32 *)(p + 0x70) + 0x357) % 854;
    }
    if (SzPad_Check(0, 2, 1) != 0) {
        *(s32 *)(p + 0x70) = (*(s32 *)(p + 0x70) + 0x355) % 854;
    }
    if (SzPad_Check(0, 0, 0x10) != 0) {
        SzDebug_OutputFrameBuffer();
    }
}

typedef struct {
    u8 pad0[0x1D0];
    u8 f1D0[0x16D];
    u8 x;
    u8 z;
    u8 pad33F[6];
    s8 y;
    s8 active : 1;
    u8 pad347[9];
} Player_001D9820;

typedef struct {
    Player_001D9820 players[4];
    u8 padD40[0x26];
    s8 : 7;
    s8 flagD66 : 1;
    s8 flagD67 : 1;
} State_001D9820;

/* Starts side `side`'s turn: makes it the turn owner and moves the camera to its cursor. */
void SzDuel_InitTurn(s32 unused, s32 side) {
    extern s32 func_001A22C0(f32);
    State_001D9820 *state = (State_001D9820 *)duelState.b;
    Player_001D9820 *p;
    s32 x;
    s32 z;
    Player_001D9820 *cur;
    f32 pos[4];
    f32 saved[4];

    duelState.s.turnOwner = side;
    p = (Player_001D9820 *)(duelState.b + side * 0x350);
    z = func_001A22C0((f32)((p->z - 3) * 50));
    x = func_001A22C0((f32)((p->x - 3) * 50));
    cur = (Player_001D9820 *)(duelState.b + duelState.s.turnOwner * 0x350);
    SzView_IV2V(cur->f1D0, saved);
    pos[0] = (f32)x;
    pos[2] = (f32)z;
    pos[1] = (f32)cur->y;
    SzView_ReqCamera(0, 0, 3, 0x20, 0, pos);
    SzView_ReqCamera(0, 0, 4, 0x20, 0, saved);
    p->active = 1;
    if (TaTuto_IsTuto(side) != 0) {
        p = state->players;
    }
    TaLogic_AdjustLogicData(p);
    state->flagD66 = 1;
    state->flagD67 = state->flagD66;
}

/* Starts drawing cards (palette 2). */
void SzDuel_StartCardSession(void) {
    RhBase_SetVifPacketArea(SzDuel_StartCardSession_Pipe(RhBase_GetVifPacketArea()));
}

/* Starts drawing cards with palette 2. */
s32 SzDuel_StartCardSession_Pipe(s32 packet) {
    return SzDuel_StartCardSessionWithPalette_Pipe(packet, 2);
}

typedef struct {
    s8 low : 5;
    s8 bit5 : 1;
    s8 high : 2;
} Flags_001D9A30;

/* Starts drawing cards: a render frame for them, the card font and textures in GS memory. */
s32 SzDuel_StartCardSessionWithPalette_Pipe(s32 packet, s32 palette) {
    extern s32 SzText_InitClutManage();
    extern s32 SzText_LoadRequest();
    extern s32 *SzMsg_GetInfo(s32);
    extern s32 RhBase_EnableRenderFrame();
    extern s32 RhBase_ClearRenderFrame();
    extern s32 RhBase_DisableRenderFrame();
    u8 *base = duelState.b;
    s32 sprite;
    s32 length;
    s32 i;
    s32 result;

    RhBase_AssignRenderFrame(3, 2, 0x32);
    packet = RhBase_EnableRenderFrame(packet);
    packet = RhBase_ClearRenderFrame(packet, 0);
    sprite = RhBase_DisableRenderFrame(packet);
    packet = RhBase_GetUserGsAddress();
    packet += SzText_InitClutManage(packet, 2);
    sprite = SzMsg_Init_Pipe(sprite, palette, packet, &length);
    i = 0;
    packet += length;
    do {
        *(s32 *)(base + i * 4 + 0x6A0) = 0;
        i++;
    } while (i < 9);
    *(s32 *)(base + 0x6B0) = SzText_LoadRequest(3, 4);
    *(s32 *)(base + 0x6B4) = SzText_LoadRequest(3, 5);
    *(s32 *)(base + 0x6B8) = SzText_LoadRequest(3, 6);
    sprite = SzText_DoRequest_Pipe(sprite, 3, packet, &length);
    packet += length;
    SzText_FreeRequest(3, -1);
    *(s32 *)(base + 0xC80) = packet;
    packet += SzText_InitClutManage(packet, 1);
    *(s32 *)(base + 0x6A0) = SzText_LoadRequest(3, 0);
    sprite = SzText_DoRequest_Pipe(sprite, 3, packet, &length);
    packet += length;
    SzText_FreeRequest(3, 0);
    {
        s32 *info;

        sprite = SzMsg_LoadFont_Pipe(sprite, 0, 0x15, 0, 0);
        info = SzMsg_GetInfo(0);
        info[3] = 0x16;
        sprite = SzMsg_LoadFont_Pipe(sprite, 1, 0xA1, 0, 0x16);
        result = RhText_SetTextureFlush(SzMsg_LoadFont_Pipe(sprite, 2, 0xA2, 0, 0x2C));
    }
    *(s32 *)(base + 0xC7C) = packet;
    *(s32 *)(base + 0xC54) = 0;
    ((Flags_001D9A30 *)(base + 0xD64))->bit5 = 0;
    return result;
}

typedef struct {
    u8 pad000[0x6A0];
    s32 slots[8];
    s32 count;
} State_001D9C40;

/* Loads card texture `index` (0..3 card frames, 8 the back) if it is not loaded yet. */
s32 lSzDuel_SetupCardTexture(s32 packet, s32 index) {
    extern s32 SzText_InitClutManage();
    extern s32 SzText_LoadRequest();
    extern s32 D_00317B30[];
    extern s32 D_00318110;
    State_001D9C40 *state;
    s32 value;
    s32 i;

    state = (State_001D9C40 *)duelState.b;
    value = D_00318110;
    if (D_00317B30[index] != 0) {
        return packet;
    }
    if (index >= 0 && index < 4) {
        i = 0;
        while (1) {
            state->slots[i] = 0;
            i++;
            if (i > 3) {
                break;
            }
        }
        state->count = 0;
        value += SzText_InitClutManage(value, 1);
        state->slots[index] = SzText_LoadRequest(3, index);
        packet = SzText_DoRequest_Pipe(packet, 3, value, NULL);
        SzText_FreeRequest(3, index);
        packet = RhText_SetTextureFlush(packet);
    } else if (index == 8) {
        i = 0;
        while (1) {
            state->slots[i] = 0;
            i++;
            if (i > 3) {
                break;
            }
        }
        value += SzText_InitClutManage(value, 1);
        state->slots[index] = SzText_LoadRequest(9, 0);
        packet = SzText_DoRequest_Pipe(packet, 9, value, NULL);
        SzText_FreeRequest(9, 0);
        packet = RhText_SetTextureFlush(packet);
    }
    return packet;
}

/* Ends drawing cards. */
void SzDuel_FinishCardSession(void) {
    RhBase_SetVifPacketArea(SzDuel_FinishCardSession_Pipe(RhBase_GetVifPacketArea()));
}

/* Ends drawing cards and frees their render frame and fonts. */
s32 SzDuel_FinishCardSession_Pipe(s32 packet) {
    extern s32 ExClampMode_Pipe();
    s32 out2;
    s32 out1;

    RhBase_FreeRenderFrame();
    out1 = RhBase_SetZBufferMode(packet, 0);
    out2 = ExClampMode_Pipe(out1, ExGetRegVal(0, 4));
    SzMsg_Free(0);
    SzMsg_Free(1);
    SzMsg_Free(2);
    return out2;
}

/* Ends drawing cards, keeping the z-buffer mode. */
s32 SzDuel_FinishCardSessionX_Pipe(s32 packet) {
    extern s32 ExClampMode_Pipe();
    s32 out;

    RhBase_FreeRenderFrame();
    out = ExClampMode_Pipe(packet, ExGetRegVal(0, 4));
    SzMsg_Free(0);
    SzMsg_Free(1);
    SzMsg_Free(2);
    return out;
}

/* Sets the depth cards are drawn at. */
void SzDuel_SetCardDefPrioZ(s32 z) {
    D_003180E4 = z;
}

/* Sets the depth windows are drawn at. */
void SzDuel_SetWindowDefPrioZ(s32 z) {
    duelState.s.depth = z;
}

/* The GS memory free after the card textures. */
s32 SzDuel_GetUserGsAddress(void) {
    return GSUserAddress;
}

typedef union {
    __int128 q;
    s32 i[4];
    f32 f[4];
} Vec_001D9F00;

typedef struct {
    s16 value : 12;
    s16 flags : 4;
} Count_001D9F00;

typedef struct {
    s8 unused : 4;
    s8 mode : 1;
    s8 split : 1;
    s8 rotation : 1;
    s8 flag7 : 1;
} Flags_001D9F00;

typedef struct {
    u64 lower : 32;
    u64 color : 24;
    u64 upper : 8;
} Packet_001D9F00;

typedef struct {
    u8 pad00[0x10];
    s32 position[4];
    u8 rotation[0x10];
    u8 orientation[0x10];
    u8 pad40[8];
    s16 field48;
    s16 field4A;
    s32 field4C;
    s64 field50;
    u8 pad58[0x20];
    u8 *vertices;
    s32 field7C;
    union {
        Count_001D9F00 count;
        struct {
            u8 low;
            Flags_001D9F00 flags;
        } bytes;
    } control80;
    Count_001D9F00 count82;
} Object_001D9F00;

extern Vec_001D9F00 D_00291540;
extern Vec_001D9F00 D_00291550;
extern Vec_001D9F00 D_00291560;
extern Vec_001D9F00 D_00291570;
extern Vec_001D9F00 D_00291580;

/* Builds the 3D card `card` (its corners on screen) for drawing; `withShadow` adds its shadow node. Returns 0 if
   off screen. */
s32 SzDuel_GetCardNode(void *card, s32 withShadow) {
    Vec_001D9F00 point;
    Vec_001D9F00 transformed;
    __int128 matrix[4];
    __int128 projection[4];
    u8 *state = duelState.b;
    s32 mode;
    Object_001D9F00 *object = card;
    s32 i;
    s32 offset;
    extern s64 SzDuel_GetCardNodeUnit();
    extern s64 Ex3d_NodeL2V(void *, s32, void *, s32, s32, s32, s32);

    point = D_00291540;
    mode = withShadow ? 15 : -1;
    RhGeom_PushMatrix(0);
    if (object->control80.bytes.flags.split) {
        __int128 rotationMatrix[4];
        __int128 translationMatrix[4];
        Vec_001D9F00 position;
        Vec_001D9F00 height;
        void *orientation;

        position = D_00291550;
        position.i[0] = object->position[0];
        position.i[2] = object->position[2];
        height = D_00291560;
        height.i[1] = object->position[1];
        orientation = object->control80.bytes.flags.rotation ? object->orientation : NULL;
        RhGeom_GetScaleRotXYZTransMatrix(rotationMatrix, NULL, object->rotation, object);
        RhGeom_GetRotXYZMatrix(translationMatrix, &height);
        RhGeom_MulMatrixRev((s32)translationMatrix, (s32)rotationMatrix);
        RhGeom_GetScaleRotXYZTransMatrix(matrix, orientation, &position, NULL);
        RhGeom_MulMatrixRev((s32)matrix, (s32)translationMatrix);
    } else {
        __int128 rotationMatrix[4];
        Vec_001D9F00 position;
        Vec_001D9F00 height;
        void *orientation;

        position = D_00291570;
        position.i[0] = object->position[0];
        position.i[2] = object->position[2];
        height = D_00291580;
        height.i[1] = object->position[1];
        orientation = object->control80.bytes.flags.rotation ? object->orientation : NULL;
        RhGeom_GetScaleRotXYZTransMatrix(rotationMatrix, NULL, &height, object);
        RhGeom_GetScaleRotXYZTransMatrix(matrix, orientation, &position, NULL);
        RhGeom_MulMatrixRev((s32)matrix, (s32)rotationMatrix);
    }
    RhView_GetWorldViewMatrix(projection);
    RhGeom_MulMatrix((s32)projection, matrix);
    RhGeom_MulMatrixVector(&point, projection, &point);
    object->field4A = 0x35;
    object->field48 = 0;
    object->field50 = 0;
    object->field4C = 0;
    ExAssignAlpha(&object->field48, 0x8000000044LL);
    if (object->control80.bytes.flags.mode) {
        ExAssignClamp(&object->field48, 0x5C00040000ALL);
    } else {
        ExAssignClamp(&object->field48, 0x2D0001E000ALL);
    }
    object->count82.value = (s16)SzDuel_GetCardNodeUnit(object->control80.bytes.flags.mode, object->vertices);
    object->count82.value = (s16)Ex3d_NodeL2V(projection, object->count82.value, object->vertices, object->control80.count.value, object->field7C, mode, 0);
    Ex3d_GetViewVectorForNode(NULL, object->count82.value, object->vertices, transformed.f);
    Ex3d_NodeV2S(NULL, object->count82.value, object->vertices);
    if (*(s32 *)(state + 0xC54) != 0) {
        for (i = 0, offset = 0; i < object->count82.value; i++, offset += 0x30) {
            ((Packet_001D9F00 *)(object->vertices + offset + 0x10))->color = *(u32 *)(state + 0xC54);
        }
    }
    RhGeom_PopMatrix();
    return RhGeom_InnerProduct(transformed.f, point.f) <= 0.0f ? 0 : 1;
}

typedef struct {
    s8 reserved0 : 4;
    s8 flag4 : 1;
    s8 reserved5 : 1;
    s8 flag6 : 1;
    s8 reserved7 : 1;
} FlagByte_001DA2B0;

typedef struct {
    s16 count : 12;
    s16 reserved : 4;
} Count_001DA2B0;

typedef union {
    s16 value;
    Count_001DA2B0 bits;
    struct {
        u8 low;
        FlagByte_001DA2B0 flags;
    } bytes;
} Flags_001DA2B0;

typedef struct {
    u8 pad0[0x48];
    s16 field48;
    s16 field4A;
    s32 field4C;
    s64 field50;
    u8 pad58[0x20];
    void *vertices;
    s32 field7C;
    Flags_001DA2B0 field80;
    Count_001DA2B0 field82;
} Object_001DA2B0;

typedef struct {
    u8 pad0[0x10];
    u64 lower : 32;
    u64 color : 24;
    u64 upper : 8;
    u8 pad18[0x18];
} Vertex_001DA2B0;

/* Builds card `card` as a flat card on screen at (x, y); `large` draws the big version. */
s32 SzDuel_GetCardNodeOnScreen(void *card, s32 large, f32 fparg0, f32 fparg1) {
    Object_001DA2B0 *object;
    void *temp_s1;
    u8 *global;

    object = card;
    global = duelState.b;
    temp_s1 = (object->field80.bytes.flags.flag6 == 0) ? NULL : ((u8 *) object + 0x30);
    object->field4A = 0x35;
    object->field48 = 0;
    object->field50 = 0;
    object->field4C = 0;
    ExAssignAlpha(&object->field48, ((s64) 0x80 << 32) | 0x44);
    if (object->field80.bytes.flags.flag4 != 0) {
        ExAssignClamp(&object->field48, ((s64) 0x5C0 << 32) | 0x40000A);
    } else {
        ExAssignClamp(&object->field48, ((s64) 0x2D0 << 32) | 0x1E000A);
    }
    object->field82.count = (s16) SzDuel_GetCardNodeUnitOnScreen(
            object->field80.bytes.flags.flag4,
            fparg0,
            fparg1,
            object->vertices,
            temp_s1);
    if (large != 0) {
        extern s32 Ex3d_ViewClip();
        object->field82.count = (s16) Ex3d_ViewClip(
                object->field82.count,
                object->vertices,
                object->field80.bits.count,
                object->field7C,
                0xF);
    }
    {
        extern void Ex3d_NodeV2S();
        Ex3d_NodeV2S(NULL,
            object->field82.count,
            object->vertices);
    }
    if (*(s32 *) (global + 0xC54) != 0) {
        s32 i;
        for (i = 0; i < object->field82.count; i++) {
            ((Vertex_001DA2B0 *) object->vertices)[i].color = *(s32 *) (global + 0xC54);
        }
    }
    return 1;
}

/* The corners of a card shape (`mode` picks small, large, or the shadow) into `dst`. */
s32 SzDuel_GetCardNodeUnit(s32 mode, void *dst) {
    f32 negativeHalfWidth;
    f32 negativeHalfHeight;
    f32 halfHeight;
    f32 uMax;
    f32 vMax;
    f32 halfWidth;
    f32 width;
    f32 height;

    width = 120.0f;
    height = 180.0f;
    if (mode != 0) {
        width = 256.0f;
        height = 368.0f;
    }
    halfWidth = width / 2.0f;
    halfHeight = height / 2.0f;
    vMax = height / 512.0f;
    uMax = width / 512.0f;
    *(u8 *)((u8 *)dst + 0x18) = 0x80;
    *(u8 *)((u8 *)dst + 0x19) = 0x80;
    *(u8 *)((u8 *)dst + 0x1A) = 0x80;
    *(u8 *)((u8 *)dst + 0x1B) = 0x80;
    *(s32 *)((u8 *)dst + 0x1C) = 0x3F800000;
    negativeHalfWidth = -halfWidth;
    *(f32 *)((u8 *)dst + 0x0) = negativeHalfWidth;
    *(f32 *)((u8 *)dst + 0x4) = halfHeight;
    *(s32 *)((u8 *)dst + 0x8) = 0;
    *(s32 *)((u8 *)dst + 0xC) = 0x3F800000;
    *(s32 *)((u8 *)dst + 0x20) = 0;
    *(s32 *)((u8 *)dst + 0x24) = 0;

    *(u8 *)((u8 *)dst + 0x48) = 0x80;
    *(u8 *)((u8 *)dst + 0x49) = 0x80;
    *(u8 *)((u8 *)dst + 0x4A) = 0x80;
    *(u8 *)((u8 *)dst + 0x4B) = 0x80;
    *(s32 *)((u8 *)dst + 0x4C) = 0x3F800000;
    *(f32 *)((u8 *)dst + 0x30) = negativeHalfWidth;
    negativeHalfHeight = -halfHeight;
    *(f32 *)((u8 *)dst + 0x34) = negativeHalfHeight;
    *(s32 *)((u8 *)dst + 0x38) = 0;
    *(s32 *)((u8 *)dst + 0x3C) = 0x3F800000;
    *(s32 *)((u8 *)dst + 0x50) = 0;
    *(f32 *)((u8 *)dst + 0x54) = vMax;

    *(u8 *)((u8 *)dst + 0x78) = 0x80;
    *(u8 *)((u8 *)dst + 0x79) = 0x80;
    *(u8 *)((u8 *)dst + 0x7A) = 0x80;
    *(u8 *)((u8 *)dst + 0x7B) = 0x80;
    *(s32 *)((u8 *)dst + 0x7C) = 0x3F800000;
    *(f32 *)((u8 *)dst + 0x60) = halfWidth;
    *(f32 *)((u8 *)dst + 0x64) = negativeHalfHeight;
    *(s32 *)((u8 *)dst + 0x68) = 0;
    *(s32 *)((u8 *)dst + 0x6C) = 0x3F800000;
    *(f32 *)((u8 *)dst + 0x80) = uMax;
    *(f32 *)((u8 *)dst + 0x84) = vMax;

    *(u8 *)((u8 *)dst + 0xA8) = 0x80;
    *(u8 *)((u8 *)dst + 0xA9) = 0x80;
    *(u8 *)((u8 *)dst + 0xAA) = 0x80;
    *(u8 *)((u8 *)dst + 0xAB) = 0x80;
    *(s32 *)((u8 *)dst + 0xAC) = 0x3F800000;
    *(f32 *)((u8 *)dst + 0x90) = halfWidth;
    *(f32 *)((u8 *)dst + 0x94) = halfHeight;
    *(s32 *)((u8 *)dst + 0x98) = 0;
    *(s32 *)((u8 *)dst + 0x9C) = 0x3F800000;
    *(f32 *)((u8 *)dst + 0xB0) = uMax;
    *(s32 *)((u8 *)dst + 0xB4) = 0;
    return 4;
}

typedef struct Vertex_001DA5E0 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
    u8 pad10[8];
    u8 r;
    u8 g;
    u8 b;
    u8 a;
    f32 q;
    f32 u;
    f32 v;
    u8 pad28[8];
} Vertex_001DA5E0;

/* The corners of a card drawn flat on screen at (x, y) into `vertices`, scaled by `scaleIn` (two floats; NULL = 1.0). */
s32 SzDuel_GetCardNodeUnitOnScreen(s32 large, f32 x, f32 y, void *vertices, void *scaleIn) {
    f32 *scale = scaleIn;
    f32 width;
    f32 height;
    f32 halfWidth;
    f32 halfHeight;
    f32 z;
    Vertex_001DA5E0 *vertex;

    width = large ? 256 : 120;
    height = large ? 368 : 180;
    vertex = vertices;
    halfWidth = (scale ? width * scale[0] : width) / 2.0f;
    halfHeight = (scale ? height * scale[1] : height) / 2.0f;
    z = SzView_GetScreenDistance(0);

    vertex[0].r = 0x80;
    vertex[0].g = 0x80;
    vertex[0].b = 0x80;
    vertex[0].a = 0x80;
    vertex[0].q = 1.0f;
    vertex[0].x = x - halfWidth;
    vertex[0].y = y - halfHeight;
    vertex[0].z = z;
    vertex[0].w = 1.0f;
    vertex[0].u = 0.0f;
    vertex[0].v = 0.0f;

    vertex[1].r = 0x80;
    vertex[1].g = 0x80;
    vertex[1].b = 0x80;
    vertex[1].a = 0x80;
    vertex[1].q = 1.0f;
    vertex[1].x = x - halfWidth;
    vertex[1].y = y + halfHeight;
    vertex[1].z = z;
    vertex[1].w = 1.0f;
    vertex[1].u = 0.0f;
    vertex[1].v = height / 512.0f;

    vertex[2].r = 0x80;
    vertex[2].g = 0x80;
    vertex[2].b = 0x80;
    vertex[2].a = 0x80;
    vertex[2].q = 1.0f;
    vertex[2].x = x + halfWidth;
    vertex[2].y = y + halfHeight;
    vertex[2].z = z;
    vertex[2].w = 1.0f;
    vertex[2].u = width / 512.0f;
    vertex[2].v = height / 512.0f;

    vertex[3].r = 0x80;
    vertex[3].g = 0x80;
    vertex[3].b = 0x80;
    vertex[3].a = 0x80;
    vertex[3].q = 1.0f;
    vertex[3].x = x + halfWidth;
    vertex[3].y = y - halfHeight;
    vertex[3].z = z;
    vertex[3].w = 1.0f;
    vertex[3].u = width / 512.0f;
    vertex[3].v = 0.0f;
    return 4;
}

/* Draws card `card` as described by `draw`. */
void SzDuel_SetupCard(s32 card, s32 draw) {
    RhBase_SetVifPacketArea(SzDuel_SetupCard_Pipe(RhBase_GetVifPacketArea(), card, (Draw_001DA7F0 *)draw));
}

typedef struct {
    u16 count;
    u16 prim;
    u32 flags;
    u64 regs;
} Tag_001DA7F0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} XYZ_001DA7F0;

typedef struct {
    u64 tag[2];
    u8 r, g, b, a;
    f32 q;
    u64 uv0;
    XYZ_001DA7F0 xyz0;
    u64 uv1;
    XYZ_001DA7F0 xyz1;
    u64 pad[4];
} Sprite_001DA7F0;

typedef struct {
    u64 tag[2];
    u8 r, g, b, a;
    f32 q;
    XYZ_001DA7F0 xyz0;
    XYZ_001DA7F0 xyz1;
    u64 end;
} Solid_001DA7F0;

typedef struct {
    u16 u : 14;
    u16 pad0 : 2;
    u16 v : 14;
    u16 pad1 : 2;
} UV_001DA7F0;

typedef struct {
    u8 tex;
    u8 pad;
    u16 u0;
    u16 v0;
    u16 u1;
    u16 v1;
} Entry_001DA7F0;

typedef struct {
    u16 x;
    u16 y;
} Pos_001DA7F0;

typedef struct {
    Pos_001DA7F0 name;
    Pos_001DA7F0 attr;
    Pos_001DA7F0 stars;
    Pos_001DA7F0 pic;
    Pos_001DA7F0 atkLabel;
    Pos_001DA7F0 atk;
    Pos_001DA7F0 defLabel;
    Pos_001DA7F0 def;
} Layout_001DA7F0;

typedef struct {
    s8 unused0 : 5;
    s8 card : 1;
    s8 unused6 : 2;
} GameFlags_001DA7F0;

typedef struct {
    u8 pad0[0x6A0];
    s32 slots[9];
    u8 pad6C4[0xD64 - 0x6C4];
    GameFlags_001DA7F0 flags;
} Game_001DA7F0;

typedef struct {
    s8 unused0 : 6;
    s8 alt : 1;
    s8 unused7 : 1;
} CardFlags_001DA7F0;

typedef struct {
    u8 pad0[0x3C];
    u16 id;
    u8 kind;
    u8 attr;
    u8 atk0;
    u8 def0;
    u8 atk1;
    u8 def1;
    u8 owner;
    u8 pad45[0x57 - 0x45];
    CardFlags_001DA7F0 flags;
} Card_001DA7F0;

extern Entry_001DA7F0 D_0028FF30[2][10];
extern Entry_001DA7F0 duelAttrIcons[]; /* original: gSzDuel_Attr */
extern Entry_001DA7F0 duelIcons[]; /* original: gSzDuel_Icon */
extern Layout_001DA7F0 D_002BED50[];
extern u16 D_002BED52[][16];
extern u16 D_002BED54[][16];
extern u16 D_002BED56[][16];
extern u16 D_002BED5C[][16];
extern u16 D_002BED5E[][16];
extern u16 D_002BED60[][16];
extern u16 D_002BED62[][16];
extern u16 D_002BED68[][16];
extern u16 D_002BED6A[][16];
extern char gSzDuel_aicolMsg[];

/* Fills a card sprite from its texture entry at (x, y), w x h. */
static inline void SetSprite_001DA7F0(Sprite_001DA7F0 *p, Entry_001DA7F0 *e, s32 x, s32 y, s32 w, s32 h) {
    ((UV_001DA7F0 *)&p->uv0)->u = (e->u0 << 4) + 8;
    ((UV_001DA7F0 *)&p->uv0)->v = (e->v0 << 4) + 8;
    ((UV_001DA7F0 *)&p->uv1)->u = (e->u1 << 4) + 8;
    ((UV_001DA7F0 *)&p->uv1)->v = (e->v1 << 4) + 8;
    p->xyz0.x = x << 4;
    p->xyz0.y = y << 4;
    p->xyz0.z = 0xFFFFFF;
    p->xyz0.f = 0;
    p->xyz1.x = (x + w) << 4;
    p->xyz1.y = (y + h) << 4;
    p->xyz1.z = 0xFFFFFF;
    p->xyz1.f = 0;
}

struct Draw_001DA7F0_s {
    u8 pad0[0x44];
    u8 b, g, r, a;
    u8 pad48[0x81 - 0x48];
    s8 unused81 : 4;
    s8 large : 1;
    s8 unused81b : 3;
    u8 pad82;
    u8 unused83 : 4;
    u8 blend : 2;
    u8 unused83b : 2;
};

/* Renders card `arg1` into its texture: frame, picture, name, attribute, level, attack and defence (or its back). */
s32 SzDuel_SetupCard_Pipe(s32 arg0, s32 arg1, Draw_001DA7F0 *arg2) {
    extern s32 SzGame_GetMode();
    extern s32 *SzMsg_GetInfo(s32);
    extern s32 ExSortPrim_Pipe(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
    Game_001DA7F0 *game;
    s32 sx;
    s32 sy;
    s32 mode;
    s32 picSize;
    s32 width;
    s32 fade;
    s32 kind;
    Entry_001DA7F0 *frameEntry;
    Entry_001DA7F0 *attrEntry;
    s32 level;
    s32 cardId;
    u16 starY;
    s32 large;
    s32 starW;
    s32 frame;
    s32 back;
    s32 hide;
    s32 digitW;
    s32 height;
    Entry_001DA7F0 *entry;
    s32 out;
    s32 tex;
    s32 attr;
    s32 p1;
    u8 p2;
    s8 alt;
    s32 altw;
    s32 atk;
    s32 def;
    s32 i;
    s32 n;
    s32 exch;
    s32 w;
    f32 scale;
    s32 *digits;
    s32 div;
    Layout_001DA7F0 *lay;
    Sprite_001DA7F0 sprite __attribute__((aligned(8)));
    Solid_001DA7F0 solid __attribute__((aligned(8)));

    game = (Game_001DA7F0 *)duelState.b;
    sx = 0x6C0;
    sy = 0x720;
    mode = SzGame_GetMode(1);
    if (arg1 != 0) {
        cardId = ((Card_001DA7F0 *)arg1)->id;
    } else {
        cardId = -1;
    }
    picSize = 0x60;
    width = 0x78;
    frame = 0x20;
    digitW = 0x14;
    starW = 8;
    height = 0xB4;
    large = 0;
    fade = 0;
    back = 0;
    hide = 0;
    if (!arg2) {
        return (s32)arg2;
    }
    if (arg2->large) {
        picSize = 0xC0;
        large = 1;
        frame = 0x1F;
        digitW = 0x16;
        starW = 0x10;
        height = 0x170;
        width = 0x100;
    }
    if (arg2->blend != 0) {
        if (arg2->a != 0) {
            fade = 1;
        }
    }
    ((Tag_001DA7F0 *)sprite.tag)->prim = 0x26;
    ((Tag_001DA7F0 *)sprite.tag)->count = 5;
    ((Tag_001DA7F0 *)sprite.tag)->regs = 0x42421;
    ((Tag_001DA7F0 *)sprite.tag)->flags = 0;
    ((Tag_001DA7F0 *)sprite.tag)->prim |= 0x800;
    ExAssignAlpha(sprite.tag, 0x44 | ((s64)0x80 << 32));
    sprite.r = 0x80;
    sprite.g = 0x80;
    sprite.b = 0x80;
    sprite.a = 0x80;
    sprite.q = 1.0f;
    arg0 = (s32)RhBase_EnableRenderFrame((void *)arg0);
    if (game->flags.card != arg2->large) {
        arg0 = (s32)RhBase_ClearRenderFrame((u8 *)arg0, 0);
        game->flags.card = arg2->large;
    }
    if (cardId >= 0x356) {
        if (((Card_001DA7F0 *)arg1)->owner <= 1) {
            back = 1;
        } else {
            cardId = -1;
        }
    }
    if (cardId == 0x29F) {
        cardId = -1;
    }
    if (SzGame_GetMenuNum(0x1E) != 0 && mode == 1 && arg1 != 0) {
        hide = lSzDuel_IsUnitHide((void *)arg1);
    }
    if (back) {
        entry = &D_0028FF30[large][((Card_001DA7F0 *)arg1)->owner + 8];
        arg0 = lSzDuel_SetupCardTexture(arg0, 8);
        ExAssignTexture(&sprite, (void *)game->slots[8], 0);
        SetSprite_001DA7F0(&sprite, entry, sx, sy, width, height);
        out = ExSortPrim_Pipe(arg0, (s32)&sprite, 0, 0);
    } else if (hide) {
        entry = &D_0028FF30[large][((Card_001DA7F0 *)arg1)->owner + 8];
        tex = lSzDuel_SetupCardTexture(arg0, entry->tex);
        ExAssignTexture(&sprite, (void *)game->slots[entry->tex], 0);
        SetSprite_001DA7F0(&sprite, entry, sx, sy, width, height);
        out = ExSortPrim_Pipe(tex, (s32)&sprite, 0, 0);
    } else if (cardId >= 0) {
        kind = ((Card_001DA7F0 *)arg1)->kind >> 5;
        attr = SzDuel_Kind2Attr(kind, ((Card_001DA7F0 *)arg1)->attr);
        entry = &D_0028FF30[large][kind];
        frameEntry = &duelIcons[frame];
        attrEntry = &duelAttrIcons[attr];
        level = SzDuel_GetUnitLevel2((void *)arg1, 0);
        altw = ((Card_001DA7F0 *)arg1)->flags.alt;
        alt = altw;
        p1 = (u8)(altw ? ((Card_001DA7F0 *)arg1)->atk1 : ((Card_001DA7F0 *)arg1)->atk0);
        p2 = alt ? ((Card_001DA7F0 *)arg1)->def1 : ((Card_001DA7F0 *)arg1)->def0;
        atk = Ta_GetParamOfs(arg1, p1, p2, 1);
        def = Ta_GetParamOfs(arg1, p1, p2, 0);
        atk += SzDuel_GetUnitAP2((void *)arg1, 0);
        def += SzDuel_GetUnitDP2((void *)arg1, 0);
        atk = ((atk > 0 ? atk : 0) < 9999) ? (atk > 0 ? atk : 0) : 9999;
        def = ((def > 0 ? def : 0) < 9999) ? (def > 0 ? def : 0) : 9999;
        if (kind == 0 && SzDuel_GetUnitConstEffect2((void *)arg1, 0) != NULL) {
            entry = &D_0028FF30[large][6];
        }
        if (arg2->large) {
            arg0 = RhText_SetTextureFlush(SzMsg_LoadFont_Pipe(arg0, 9, SzDuel_GetMsgName(cardId), 0, 0xC6));
        }
        arg0 = lSzDuel_SetupCardTexture(arg0, entry->tex);
        ExAssignTexture(&sprite, (void *)game->slots[entry->tex], 0);
        ((UV_001DA7F0 *)&sprite.uv0)->u = (entry->u0 << 4) + 8;
        ((UV_001DA7F0 *)&sprite.uv0)->v = (entry->v0 << 4) + 8;
        ((UV_001DA7F0 *)&sprite.uv1)->u = (entry->u1 << 4) + 8;
        ((UV_001DA7F0 *)&sprite.uv1)->v = (entry->v1 << 4) + 8;
        sprite.xyz0.x = sx << 4;
        sprite.xyz0.y = sy << 4;
        sprite.xyz0.z = 0xFFFFFF;
        sprite.xyz0.f = 0;
        sprite.xyz1.x = (sx + width) << 4;
        sprite.xyz1.y = (sy + height) << 4;
        sprite.xyz1.z = 0xFFFFFF;
        sprite.xyz1.f = 0;
        arg0 = ExSortPrim_Pipe(arg0, (s32)&sprite, 0, 0);
        ExAssignTexture(&sprite, (void *)game->slots[frameEntry->tex], 0);
        ((UV_001DA7F0 *)&sprite.uv0)->u = (frameEntry->u0 << 4) + 8;
        ((UV_001DA7F0 *)&sprite.uv0)->v = (frameEntry->v0 << 4) + 8;
        ((UV_001DA7F0 *)&sprite.uv1)->u = (frameEntry->u1 << 4) + 8;
        ((UV_001DA7F0 *)&sprite.uv1)->v = (frameEntry->v1 << 4) + 8;
        i = 0;
        if (i < level) {
            do {
                starY = sy + starW;
                n = 11 - i;
                sprite.xyz0.x = (sx + starW * n + D_002BED50[large].stars.x + (u16)(large * n)) << 4;
                sprite.xyz0.y = (sy + D_002BED50[large].stars.y) << 4;
                sprite.xyz0.z = 0xFFFFFF;
                sprite.xyz0.f = 0;
                sprite.xyz1.x = (sx + starW * (n + 1) + D_002BED50[large].stars.x + (u16)(large * n)) << 4;
                sprite.xyz1.y = (starY + D_002BED50[large].stars.y) << 4;
                sprite.xyz1.z = 0xFFFFFF;
                sprite.xyz1.f = 0;
                arg0 = ExSortPrim_Pipe(arg0, (s32)&sprite, 0, 0);
                i++;
            } while (i < level);
        }
        exch = SzData_ExchSpecial(((Card_001DA7F0 *)arg1)->owner, cardId);
        if (exch != cardId && SzText_GetReadyItem(1, exch) == NULL) {
            exch = cardId;
        }
        out = lSzDuel_DrawWindow_PicItem_Pipe(arg0, exch, D_002BED5C[large][0], D_002BED5E[large][0], picSize, picSize, 0xFFFFFF);
        if (arg2->large) {
            ExAssignTexture(&sprite, (void *)game->slots[attrEntry->tex], 0);
            ((UV_001DA7F0 *)&sprite.uv0)->u = (attrEntry->u0 << 4) + 8;
            ((UV_001DA7F0 *)&sprite.uv0)->v = (attrEntry->v0 << 4) + 8;
            ((UV_001DA7F0 *)&sprite.uv1)->u = (attrEntry->u1 << 4) + 8;
            ((UV_001DA7F0 *)&sprite.uv1)->v = (attrEntry->v1 << 4) + 8;
            sprite.xyz0.x = (sx + D_002BED54[large][0]) << 4;
            sprite.xyz0.y = (sy + D_002BED56[large][0]) << 4;
            sprite.xyz0.z = 0xFFFFFF;
            sprite.xyz0.f = 0;
            sprite.xyz1.x = (sx + 0x18 + D_002BED54[large][0]) << 4;
            sprite.xyz1.y = (sy + 0x18 + D_002BED56[large][0]) << 4;
            sprite.xyz1.z = 0xFFFFFF;
            sprite.xyz1.f = 0;
            out = ExSortPrim_Pipe(out, (s32)&sprite, 0, 0);
            w = SzMsg_GetInfo(9)[3];
            if ((s32)(w >= 0xC1) != 0) {
                scale = 192.0f / (f32)w;
            } else {
                scale = 1.0f;
            }
            out = SzMsg_DrawRatioX_Pipe(out, 9, D_002BED50[large].name.x, D_002BED52[large][0], scale, 1.0f, (s32)gSzDuel_aicolMsg, (void (*)(void))SzMsg_DrawRect_Pipe);
            SzMsg_Free(9);
        }
        if (kind == 0) {
            extern s32 Ta_GetParamOfs(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
            extern void *SzText_GetReadyItem(s32 arg0, s32 arg1);
            w = SzMsg_GetInfo(1)[3];
            if (w > 22) {
                scale = 22.0f / (f32)w;
            } else {
                scale = 1.0f;
            }
            out = SzMsg_DrawRatioX_Pipe(out, 1, D_002BED60[large][0], D_002BED62[large][0], scale, 1.0f, (s32)gSzDuel_aicolMsg, (void (*)(void))SzMsg_DrawRect_Pipe);
            digits = SzMsg_GetInfo(0);
            div = 1;
            lay = &D_002BED50[large];
            i = 0;
            do {
                digits[1] = (atk / div % 10) * 22;
                out = SzMsg_DrawX_Pipe(out, 0, lay->atk.x + digitW * (4 - i), lay->atk.y, (s32)gSzDuel_aicolMsg, (s32)SzMsg_DrawRect_Pipe);
                div *= 10;
                if (atk < div) {
                    break;
                }
                i++;
            } while (i < 4);
            w = SzMsg_GetInfo(2)[3];
            if (w > 22) {
                scale = 22.0f / (f32)w;
            } else {
                scale = 1.0f;
            }
            out = SzMsg_DrawRatioX_Pipe(out, 2, D_002BED68[large][0], D_002BED6A[large][0], scale, 1.0f, (s32)gSzDuel_aicolMsg, (void (*)(void))SzMsg_DrawRect_Pipe);
            digits = SzMsg_GetInfo(0);
            div = 1;
            i = 0;
            do {
                digits[1] = (def / div % 10) * 22;
                out = SzMsg_DrawX_Pipe(out, 0, lay->def.x + digitW * (4 - i), lay->def.y, (s32)gSzDuel_aicolMsg, (s32)SzMsg_DrawRect_Pipe);
                div *= 10;
                if (def < div) {
                    break;
                }
                i++;
            } while (i < 4);
        }
    } else {
        entry = &D_0028FF30[large][7];
        tex = lSzDuel_SetupCardTexture(arg0, entry->tex);
        ExAssignTexture(&sprite, (void *)game->slots[entry->tex], 0);
        SetSprite_001DA7F0(&sprite, entry, sx, sy, width, height);
        out = ExSortPrim_Pipe(tex, (s32)&sprite, 0, 0);
    }
    if (fade) {
        ((Tag_001DA7F0 *)solid.tag)->prim = 6;
        ((Tag_001DA7F0 *)solid.tag)->count = 3;
        ((Tag_001DA7F0 *)solid.tag)->regs = 0x441;
        ((Tag_001DA7F0 *)solid.tag)->flags = 0;
        ExAssignAlpha(solid.tag, ExGetAlphaVal(arg2->blend));
        solid.r = arg2->r;
        solid.g = arg2->g;
        solid.b = arg2->b;
        solid.a = arg2->a;
        solid.q = 1.0f;
        solid.xyz0.x = 0x6C00;
        solid.xyz0.y = 0x7200;
        solid.xyz0.z = 0xFFFFFF;
        solid.xyz0.f = 0;
        solid.xyz1.x = 0x8000;
        solid.xyz1.y = 0x8E00;
        solid.xyz1.z = 0xFFFFFF;
        solid.xyz1.f = 0;
        out = (s32)RhBase_MaskFBuffer((void *)ExSortPrim_Pipe((s32)RhBase_MaskFBuffer((void *)RhBase_SetZBufferMode(out, 0), 0xFF000000), (s32)&solid, 0, 0), 0);
    }
    RhBase_GetTextureInfoForRender((u8 *)arg2 + 0x60, (u8 *)arg2 + 0x68);
    return RhText_SetTextureFlush((s32)RhBase_DisableRenderFrame((void *)out));
}

typedef struct Packet_001DBC40 {
    u8 pad00[0x18];
    u8 red;
    u8 green;
    u8 blue;
    u8 alpha;
    u8 pad1C[0x14];
} Packet_001DBC40;

typedef struct Data_001DBC40 {
    u8 pad00[0x40];
    u8 blue;
    u8 green;
    u8 red;
    u8 alpha;
    u8 pad44[0x34];
    Packet_001DBC40 *packets;
    u8 pad7C[5];
    s8 flags : 7;
    s8 update : 1;
    s16 count : 12;
    s16 unused : 4;
} Data_001DBC40;

/* Renders card `card` as described by `draw` (SzDuel_SetupCard_Pipe). */
s32 SzDuel_SetupCard2_Pipe(s32 packet, s32 card, void *draw) {
    s32 i;
    Data_001DBC40 *data = draw;

    packet = SzDuel_SetupCard_Pipe(packet, card, draw);
    if (data->update) {
        for (i = 0; i < data->count; i++) {
            data->packets[i].red = data->red;
            data->packets[i].green = data->green;
            data->packets[i].blue = data->blue;
            data->packets[i].alpha = data->alpha;
        }
    }
    return packet;
}

/* Draws a card node. */
void SzDuel_DrawCard(s32 node) {
    RhBase_SetVifPacketArea(SzDuel_DrawCard_Pipe(RhBase_GetVifPacketArea(), node));
}

typedef struct {
    u8 pad_00[0x48];
    u8 data[0x30];
    s32 value;
    u8 pad_7C[6];
    s16 index : 12;
    s16 unused : 4;
} Params_001DBD30;

/* Draws a card node built by SzDuel_GetCardNode. */
s32 SzDuel_DrawCard_Pipe(s32 packet, s32 node) {
    Params_001DBD30 *params = (Params_001DBD30 *)node;

    return ExSortNode_Pipe(packet, params->data, params->index,
                        params->value, 0, 0);
}

typedef struct Vertex_001DBD50 {
    f32 x, y, z;
    u8 pad0C[0xC];
    u8 r, g, b, a;
    f32 q;
    u8 pad20[0x10];
} Vertex_001DBD50;

typedef struct Prim_001DBD50 {
    u16 flags;
    u16 kind;
    u32 pad;
    u64 value;
    u64 alpha;
    u64 tex0;
    u64 tex1;
    u64 clamp;
} Prim_001DBD50;

/* Fills a primitive header. */
static inline void initPrim_001DBD50(s32 kind, void *prim) {
    ((Prim_001DBD50 *)prim)->kind = kind;
    ((Prim_001DBD50 *)prim)->flags = 0;
    ((Prim_001DBD50 *)prim)->value = 0;
    ((Prim_001DBD50 *)prim)->pad = 0;
}

/* Draws a square cursor at `position`, w x h, in `color`, pulsing unless `still`. */
s32 SzDuel_DrawCursor_Pipe(s32 packet, f32 *position, f32 width, f32 height,
                   s32 alpha, u8 *color, s32 still) {
    void *scratchpad = (void *)SCRATCHPAD_ADDR;
    Vertex_001DBD50 *vertices = (Vertex_001DBD50 *)((u8 *)scratchpad + 0x2000);
    s32 repeats = 2;
    s32 count;
    s32 original = packet;
    Prim_001DBD50 prim;
    u8 *end;

    packet = ExSetAnchor_Pipe(packet);
    do {
        vertices[0].r = 0x80;
        vertices[0].g = 0x80;
        vertices[0].b = 0x80;
        vertices[0].a = 0x80;
        if (color != NULL) {
            vertices[0].r = color[2];
            vertices[0].g = color[1];
            vertices[0].b = color[0];
            vertices[0].a = color[3];
        }
        vertices[0].q = 1.0f;
        vertices[0].x = position[0] - width;
        vertices[0].y = position[1];
        vertices[0].z = position[2] - height;
        vertices[1].x = position[0] + width;
        vertices[1].y = position[1];
        vertices[1].z = position[2] - height;
        vertices[2].x = position[0] + width;
        vertices[2].y = position[1];
        vertices[2].z = position[2] + height;
        vertices[3].x = position[0] - width;
        vertices[3].y = position[1];
        vertices[3].z = position[2] + height;
        vertices[4].x = position[0] - width;
        vertices[4].y = position[1];
        vertices[4].z = position[2] - height;
        count = Ex3d_NodeL2V(0, 5, vertices, 0xAA, scratchpad, 0, 0);
        Ex3d_NodeV2S(NULL, count, vertices);
        if (still != 0) {
            initPrim_001DBD50(5, &prim);
        } else {
            initPrim_001DBD50(0x402, &prim);
        }
        if (vertices[0].a < 0xFF) {
            ExAssignAlpha(&prim, ExGetAlphaVal(alpha));
        }
        packet = ExSortNode_Pipe(packet, &prim, count, (s32)vertices, 0, 0);
        if (still != 0 || repeats-- <= 0) {
            break;
        }
        width -= 0.2f;
        height -= 0.2f;
    } while (1);
    end = ExGetMyOT();
    return ExSortAnchor_Pipe(packet, original, (s32)end, Ex3d_GetSampleZ(position, 0.0f));
}

typedef struct Primitive_001DBFE0 {
    u16 mode;
    u16 flags;
    s32 reserved;
    s64 state;
    s64 extra[4];
} Primitive_001DBFE0;

/* Fills a primitive header. */
static inline void init_001DBFE0(void *prim, s32 flags) {
    ((u16 *)prim)[1] = flags;
    ((u16 *)prim)[0] = 0;
    ((s64 *)prim)[1] = 0;
    ((s32 *)prim)[1] = 0;
}

/* Draws the 3D box cursor around a board square at `position`, in `color` (or the default), with its top if
   `withTop`. */
s32 SzDuel_DrawBoxCursor_Pipe(s32 packet, f32 *position, u8 *color, s32 withTop) {
    Primitive_001DBFE0 prim;
    f32 temp_f20;
    f32 height = 35.0f;
    f32 half_width = 24.0f;
    s32 pipe;
    s32 pipe2;
    s32 nodeL2V;
    s32 nodeL2V2;
    s32 nodeL2V3;
    s32 nodeL2V3In;
    s32 pipe3;

    *(u8 *)(SCRATCHPAD_ADDR + 0x2018) = 0;
    *(u8 *)(SCRATCHPAD_ADDR + 0x2019) = 0;
    *(u8 *)(SCRATCHPAD_ADDR + 0x201A) = 0;
    *(u8 *)(SCRATCHPAD_ADDR + 0x201B) = 0xFF;
    if (color != NULL) {
        *(u8 *)(SCRATCHPAD_ADDR + 0x2018) = color[2];
        *(u8 *)(SCRATCHPAD_ADDR + 0x2019) = color[1];
        *(u8 *)(SCRATCHPAD_ADDR + 0x201A) = color[0];
        *(u8 *)(SCRATCHPAD_ADDR + 0x201B) = color[3];
    }
    *(s32 *)(SCRATCHPAD_ADDR + 0x201C) = 0x3F800000;
    if (withTop != 0) {
        init_001DBFE0(&prim, 5);
    } else {
        init_001DBFE0(&prim, 2);
    }
    if (*(u8 *)(SCRATCHPAD_ADDR + 0x201B) != 0xFF) {
        ExAssignAlpha(&prim, 0x48 | ((s64)0x80 << 32));
    }
    *(f32 *)(SCRATCHPAD_ADDR + 0x2000) = position[0] - half_width;
    temp_f20 = -height;
    *(f32 *)(SCRATCHPAD_ADDR + 0x2004) = position[1] - height;
    *(f32 *)(SCRATCHPAD_ADDR + 0x2008) = position[2] - half_width;
    *(f32 *)(SCRATCHPAD_ADDR + 0x2030) = position[0] - half_width;
    *(f32 *)(SCRATCHPAD_ADDR + 0x2034) = temp_f20;
    *(f32 *)(SCRATCHPAD_ADDR + 0x2038) = position[2] - half_width;
    *(f32 *)(SCRATCHPAD_ADDR + 0x2060) = position[0] + half_width;
    *(f32 *)(SCRATCHPAD_ADDR + 0x2064) = temp_f20;
    *(f32 *)(SCRATCHPAD_ADDR + 0x2068) = position[2] - half_width;
    *(f32 *)(SCRATCHPAD_ADDR + 0x2090) = position[0] + half_width;
    *(f32 *)(SCRATCHPAD_ADDR + 0x2094) = position[1] - height;
    *(f32 *)(SCRATCHPAD_ADDR + 0x2098) = position[2] - half_width;
    nodeL2V = Ex3d_NodeL2V(0, 4, (void *)(SCRATCHPAD_ADDR + 0x2000), 0xAA, (void *)SCRATCHPAD_ADDR, 0, 0);
    Ex3d_NodeV2S(NULL, nodeL2V, (void *)(SCRATCHPAD_ADDR + 0x2000));
    pipe = ExSortNode_Pipe(packet, &prim, nodeL2V, 0x70002000, 0, 0);
    *(f32 *)(SCRATCHPAD_ADDR + 0x2000) = (position[0] - half_width);
    *(f32 *)(SCRATCHPAD_ADDR + 0x2004) = (position[1] - height);
    *(f32 *)(SCRATCHPAD_ADDR + 0x2008) = (position[2] + half_width);
    *(f32 *)(SCRATCHPAD_ADDR + 0x2030) = (position[0] - half_width);
    *(f32 *)(SCRATCHPAD_ADDR + 0x2034) = temp_f20;
    *(f32 *)(SCRATCHPAD_ADDR + 0x2038) = (position[2] + half_width);
    *(f32 *)(SCRATCHPAD_ADDR + 0x2060) = (position[0] + half_width);
    *(f32 *)(SCRATCHPAD_ADDR + 0x2064) = temp_f20;
    *(f32 *)(SCRATCHPAD_ADDR + 0x2068) = (position[2] + half_width);
    *(f32 *)(SCRATCHPAD_ADDR + 0x2090) = (position[0] + half_width);
    *(f32 *)(SCRATCHPAD_ADDR + 0x2094) = (position[1] - height);
    *(f32 *)(SCRATCHPAD_ADDR + 0x2098) = (position[2] + half_width);
    nodeL2V2 = Ex3d_NodeL2V(0, 4, (void *)(SCRATCHPAD_ADDR + 0x2000), 0xAA, (void *)SCRATCHPAD_ADDR, 0, 0);
    Ex3d_NodeV2S(NULL, nodeL2V2, (void *)(SCRATCHPAD_ADDR + 0x2000));
    pipe3 = ExSortNode_Pipe(pipe, &prim, nodeL2V2, 0x70002000, 0, 0);
    *(f32 *)(SCRATCHPAD_ADDR + 0x2000) = (position[0] - half_width);
    *(f32 *)(SCRATCHPAD_ADDR + 0x2004) = (position[1] - height);
    *(f32 *)(SCRATCHPAD_ADDR + 0x2008) = (position[2] - half_width);
    *(f32 *)(SCRATCHPAD_ADDR + 0x2030) = (position[0] - half_width);
    *(f32 *)(SCRATCHPAD_ADDR + 0x2034) = temp_f20;
    *(f32 *)(SCRATCHPAD_ADDR + 0x2038) = (position[2] - half_width);
    *(f32 *)(SCRATCHPAD_ADDR + 0x2060) = (position[0] - half_width);
    *(f32 *)(SCRATCHPAD_ADDR + 0x2064) = temp_f20;
    *(f32 *)(SCRATCHPAD_ADDR + 0x2068) = (position[2] + half_width);
    *(f32 *)(SCRATCHPAD_ADDR + 0x2090) = (position[0] - half_width);
    *(f32 *)(SCRATCHPAD_ADDR + 0x2094) = (position[1] - height);
    *(f32 *)(SCRATCHPAD_ADDR + 0x2098) = (position[2] + half_width);
    nodeL2V3 = Ex3d_NodeL2V(0, 4, (void *)(SCRATCHPAD_ADDR + 0x2000), 0xAA, (void *)SCRATCHPAD_ADDR, 0, 0);
    Ex3d_NodeV2S(NULL, nodeL2V3, (void *)(SCRATCHPAD_ADDR + 0x2000));
    pipe2 = ExSortNode_Pipe(pipe3, &prim, nodeL2V3, 0x70002000, 0, 0);
    *(f32 *)(SCRATCHPAD_ADDR + 0x2000) = (position[0] + half_width);
    *(f32 *)(SCRATCHPAD_ADDR + 0x2004) = (position[1] - height);
    *(f32 *)(SCRATCHPAD_ADDR + 0x2008) = (position[2] - half_width);
    *(f32 *)(SCRATCHPAD_ADDR + 0x2030) = (position[0] + half_width);
    *(f32 *)(SCRATCHPAD_ADDR + 0x2034) = temp_f20;
    *(f32 *)(SCRATCHPAD_ADDR + 0x2038) = (position[2] - half_width);
    *(f32 *)(SCRATCHPAD_ADDR + 0x2060) = (position[0] + half_width);
    *(f32 *)(SCRATCHPAD_ADDR + 0x2064) = temp_f20;
    *(f32 *)(SCRATCHPAD_ADDR + 0x2068) = (position[2] + half_width);
    *(f32 *)(SCRATCHPAD_ADDR + 0x2090) = (position[0] + half_width);
    *(f32 *)(SCRATCHPAD_ADDR + 0x2094) = (position[1] - height);
    *(f32 *)(SCRATCHPAD_ADDR + 0x2098) = (position[2] + half_width);
    nodeL2V3In = Ex3d_NodeL2V(0, 4, (void *)(SCRATCHPAD_ADDR + 0x2000), 0xAA, (void *)SCRATCHPAD_ADDR, 0, 0);
    Ex3d_NodeV2S(NULL, nodeL2V3In, (void *)(SCRATCHPAD_ADDR + 0x2000));
    return ExSortNode_Pipe(pipe2, &prim, nodeL2V3In, 0x70002000, 0, 0);
}

MapInfo *func_001DCD00_b(int x, int y);

/* Draws the line between the two halves of the board. */
int SzDuel_DrawLine_Pipe(int cursor)
{
    int x;
    int y;
    MapInfo *cell;
    float pos[4];
    float dx;
    float dz;
    Bgra c0;
    Bgra c1;

    if (SzModel_GetDrawFlag(0) == 0) {
        return cursor;
    }
    for (y = 0; y < 7; y++) {
        for (x = 0; x < 7; x++) {
            cell = func_001DCD00_b(x, y);
            c0 = cell->Highlight;
            c1 = cell->BorderOutline;
            c0.r = (c0.r * cell->mapAlpha) >> 7;
            c0.g = (c0.g * cell->mapAlpha) >> 7;
            c0.b = (c0.b * cell->mapAlpha) >> 7;
            c1.r = (c1.r * cell->mapAlpha) >> 7;
            c1.g = (c1.g * cell->mapAlpha) >> 7;
            c1.b = (c1.b * cell->mapAlpha) >> 7;
            pos[0] = (x - 3) * 50;
            pos[2] = (y - 3) * 50;
            pos[1] = -0.2f;
            if (c0.a != 0) {
                dz = dx = 24.0f;
                cursor = SzDuel_DrawCursor_Pipe(cursor, pos, dx, dz, cell->SelectionHighlightType, &c0.b, 1);
            }
            pos[1] = -0.1f;
            if (c1.a != 0) {
                dz = dx = 24.0f;
                cursor = SzDuel_DrawCursor_Pipe(cursor, pos, dx, dz, 1, &c1.b, 0);
            }
        }
    }
    return cursor;
}

typedef union {
    __int128 q[4];
    f32 v[4][4];
} Points_001DC790;

typedef struct {
    f32 x, y, z;
    u8 padC[0xC];
    u8 red, green, blue, alpha;
    f32 q, u, v;
    u8 pad28[8];
} Vertex_001DC790;

typedef union {
    __int128 raw;
    u8 bytes[48];
} Packet_001DC790;

typedef struct {
    u8 pad000[0x6A0];
    void *textures[1];
} Gfx_001DC790;

extern Points_001DC790 D_00291590;
extern u8 leaderBaseIcons[]; /* original: gSzDuel_Base */
extern u8 DeckLeaderRoseSize;

/* Draws the base under side `side`'s leader at `position`, with alpha `alpha` and an outline if `outline`. */
s32 SzDuel_DrawLeaderBase_Pipe(s32 out, s32 side, f32 *position, s32 baseAlpha, s32 outline) {
    s16 *type;
    s64 *bits;
    s32 *data;
    Points_001DC790 points;
    f32 rotation[4];
    Points_001DC790 matrix;
    Packet_001DC790 packet;
    Gfx_001DC790 *textures = (Gfx_001DC790 *)duelState.b;
    f32 u;
    u8 *entry;
    f32 scale;
    s32 count;
    Unit *card;
    MapInfo *info;
    u8 intensity;

    card = (Unit *)SzDuel_GetUnit(side, 0);
    scale = 16.666666f;
    scale = (scale * DeckLeaderRoseSize) / 128.0f;
    points = D_00291590;
    points.v[0][0] = scale;
    points.v[0][2] = scale;
    points.v[1][0] = scale;
    points.v[1][2] = -scale;
    points.v[2][0] = -scale;
    points.v[2][2] = -scale;
    points.v[3][0] = -scale;
    points.v[3][2] = scale;
    if (side != 0) {
        u = 0.5f;
    } else {
        u = 0.0f;
    }
    entry = &leaderBaseIcons[side * 10];
    intensity = 0x80;
    if (card == NULL) {
        return out;
    }
    if (card->cardModel != 0) {
        return out;
    } else {
        info = SzDuel_GetMapInfo(card->locCol, card->locRow);
        if (card->status.fCardBusy == 0 && card->modelStatusFlags.fCardColBusy == 0) {
            intensity = info->mapAlpha;
        }
        SzModel_GetRot(card->modelId, rotation);
        rotation[2] = 0;
        rotation[0] = 0;
        RhGeom_GetRotXYZMatrix(&matrix, rotation);
        RhGeom_PushMatrix((s32)&matrix);
        RhGeom_MulMatrixVectorArray(&points, 0, &points, 4);
        RhGeom_PopMatrix();
        *(s16 *)((s32)&packet + 2) = 0x35;
        type = (s16 *)((s32)&packet + 2);
        bits = (s64 *)((s32)&packet + 8);
        data = (s32 *)((s32)&packet + 4);
        *(s16 *)(s32)&packet = 0;
        *(s64 *)((s32)&packet + 8) = 0;
        *(s32 *)((s32)&packet + 4) = 0;
        ExAssignAlpha(&packet, 0x8000000044LL);
        ExAssignTexture(&packet, textures->textures[entry[0]], 1);
        {
            s32 first;
            u32 i = 0;
            Vertex_001DC790 *vertex = (Vertex_001DC790 *)(SCRATCHPAD_ADDR + 0x2000);
            f32 *p = points.v[0];
            intensity = (u8)intensity;
            do {
                first = 1;
                vertex->red = vertex->green = vertex->blue = (card->CardHighlight * intensity) >> 7;
                vertex->alpha = baseAlpha;
                vertex->q = 1.0f;
                if (i > 1U) {
                    first = 0;
                }
                vertex->u = u + (first ? 0.0f : 0.5f);
                vertex->v = (i == 0 || i == 3) ? 0.0f : 1.0f;
                i++;
                vertex->x = position[0] + p[0];
                vertex->y = position[1] + p[1];
                vertex->z = position[2] + p[2];
                p += 4;
                vertex++;
            } while ((s32)i < 4);
            count = Ex3d_NodeL2V(0, i, (void *)(SCRATCHPAD_ADDR + 0x2000), 0xAA, (void *)SCRATCHPAD_ADDR, 0xF, 0);
            Ex3d_NodeV2S(0, count, (void *)(SCRATCHPAD_ADDR + 0x2000));
            out = ExSortNode_Pipe(out, &packet, count, 0x70002000, 0, 0);
            if (outline != 0) {
                Vertex_001DC790 *vertex2;
                s32 j;
                *type = 0x402;
                *(s16 *)(s32)&packet = 0;
                *bits = 0;
                *data = 0;
                ExAssignAlpha(&packet, 0x8000000048LL);
                *(u8 *)(SCRATCHPAD_ADDR + 0x2018) = (info->BorderOutline.r * intensity) >> 7;
                *(u8 *)(SCRATCHPAD_ADDR + 0x2019) = (info->BorderOutline.g * intensity) >> 7;
                *(u8 *)(SCRATCHPAD_ADDR + 0x201A) = (info->BorderOutline.b * intensity) >> 7;
                *(u8 *)(SCRATCHPAD_ADDR + 0x201B) = baseAlpha;
                *(f32 *)(SCRATCHPAD_ADDR + 0x201C) = 1.0f;
                vertex2 = (Vertex_001DC790 *)(SCRATCHPAD_ADDR + 0x2000);
                j = 0;
                do {
                    vertex2->x = position[0] + points.v[j % 4][0];
                    vertex2->y = position[1] + points.v[j % 4][1];
                    vertex2->z = position[2] + points.v[j % 4][2];
                    j++;
                    vertex2++;
                } while (j < 5);
                count = Ex3d_NodeL2V(0, j, (void *)(SCRATCHPAD_ADDR + 0x2000), 0xAA, (void *)SCRATCHPAD_ADDR, 0xF, 0);
                Ex3d_NodeV2S(0, count, (void *)(SCRATCHPAD_ADDR + 0x2000));
                out = ExSortNode_Pipe(out, &packet, count, 0x70002000, 0, 0);
            }
        }
    }
    return out;
}

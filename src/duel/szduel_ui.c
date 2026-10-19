/* The duel screen, part 15 of 15: busy flags, card position / rotation / scale / colour, pop-ups, the hand cursor. */

#include "common.h"

typedef struct Flags_001E3850 {
    u8 padding0[0x57];
    s8 reserved57 : 7;
    s8 flag57 : 1;
    s8 flag58 : 1;
    s8 reserved58 : 7;
} Flags_001E3850;

/* The unit record SzDuel_SetBusyFlag writes, or NULL. */
static inline void *get_001E3850(void) {
    extern void *SzDuel_GetCardInfo();
    u8 *card = SzDuel_GetCardInfo();

    if (card == NULL) {
        return NULL;
    }
    if (card[0x45] >= 0xB) {
        return NULL;
    }
    return card;
}

/* Marks unit (side, unit) busy (its card and model are moving) or not. */
s32 SzDuel_SetBusyFlag(s32 side, s32 unit, s32 on) {
    u8 *card = get_001E3850();

    if (card == NULL) {
        return 0;
    }
    ((Flags_001E3850 *)card)->flag57 = (s8) (on ? 1 : 0);
    ((Flags_001E3850 *)card)->flag58 = (s8) (on ? 1 : 0);
    return 1;
}

typedef struct Flags_001E3900 {
    s8 other : 7;
    s8 enabled : 1;
} Flags_001E3900;

typedef struct Entry_001E3900 {
    u8 pad0[0x45];
    u8 kind;
    u8 pad46[0x11];
    Flags_001E3900 flags;
} Entry_001E3900;

/* The unit record SzDuel_SetCardBusyFlag writes, or NULL. */
static inline void *get_001E3900(void) {
    extern void *SzDuel_GetCardInfo();
    Entry_001E3900 *entry = SzDuel_GetCardInfo();
    if (entry == NULL) {
        return NULL;
    }
    if (entry->kind >= 0xB) {
        return NULL;
    }
    return entry;
}

/* Marks unit (side, unit)'s card busy or not. */
s32 SzDuel_SetCardBusyFlag(s32 side, s32 unit, s32 on) {
    Entry_001E3900 *entry = get_001E3900();
    if (entry == NULL) {
        return 0;
    }
    entry->flags.enabled = (s8)((on != 0) ? 1 : 0);
    return 1;
}

typedef struct Object_001E3990 {
    u8 pad0[0x45];
    u8 type;
    u8 pad46[0x12];
    s8 bit0 : 1;
    s8 enabled : 1;
    s8 rest : 6;
} Object_001E3990;

/* The unit record SzDuel_SetCardColBusyFlag writes, or NULL. */
static inline void *check_001E3990(void) {
    extern void *SzDuel_GetCardInfo();
    Object_001E3990 *object = SzDuel_GetCardInfo();

    if (object == NULL) {
        return NULL;
    }
    if (object->type >= 11) {
        return NULL;
    }
    return object;
}

/* Marks unit (side, unit)'s card colour busy (fading) or not. */
s32 SzDuel_SetCardColBusyFlag(s32 side, s32 unit, s32 on) {
    Object_001E3990 *object = check_001E3990();

    if (object == NULL) {
        return 0;
    }
    object->enabled = on ? 1 : 0;
    return 1;
}

struct ObjectFields_001E3A20 {
    u8 pad0[0x45];
    u8 kind;
    u8 pad1[0x12];
    s8 enabled : 1;
    s8 : 7;
};

/* Marks unit (side, unit)'s model busy or not. */
s32 SzDuel_SetModelBusyFlag(s32 side, s32 unit, s32 on) {
    extern void *SzDuel_GetCardInfo();
    struct ObjectFields_001E3A20 *object = SzDuel_GetCardInfo();

    if (object == NULL) {
        object = NULL;
    } else if (object->kind >= 11) {
        object = NULL;
    }

    if (object == NULL) {
        return 0;
    }
    object->enabled = (s8)(on ? 1 : 0);
    return 1;
}

typedef struct Vec4_001E3AB0 {
    f32 x, y, z, w;
} Vec4_001E3AB0;

/* The unit record SzDuel_SetCardPos writes, or NULL. */
static inline void *get_001E3AB0(void) {
    extern void *SzDuel_GetCardInfo();
    void *entry = SzDuel_GetCardInfo();

    if (entry == NULL) {
        return NULL;
    }
    if (*(u8 *)((u8 *)entry + 0x45) >= 11) {
        return NULL;
    }
    return entry;
}

/* Sets unit (side, unit)'s card position offset. */
s32 SzDuel_SetCardPos(s32 side, s32 unit, s32 pos) {
    void *entry;
    Vec4_001E3AB0 *data;

    entry = get_001E3AB0();
    if (entry == NULL) {
        return 0;
    }
    data = *(Vec4_001E3AB0 **)((u8 *)entry + 4);
    if (data == NULL) {
        return 0;
    }
    if (pos != 0) {
        *data = *(Vec4_001E3AB0 *)pos;
    }
    return 1;
}

typedef struct Vec4_001E3B50 {
    f32 x, y, z, w;
} Vec4_001E3B50;

typedef struct Object_001E3B50 {
    u8 pad0[4];
    Vec4_001E3B50 *position;
    u8 pad8[0x3D];
    u8 kind;
} Object_001E3B50;

/* The unit record SzDuel_GetCardPos reads, or NULL. */
static inline void *get_001E3B50(void) {
    extern void *SzDuel_GetCardInfo();
    void *object = SzDuel_GetCardInfo();

    if (object == NULL) {
        return NULL;
    }
    if (((Object_001E3B50 *)object)->kind >= 11) {
        return NULL;
    }
    return object;
}

/* Unit (side, unit)'s card position offset into `out`. */
s32 SzDuel_GetCardPos(s32 side, s32 unit, void *out) {
    Object_001E3B50 *object;
    Vec4_001E3B50 *position;

    object = get_001E3B50();
    if (object == NULL) {
        return 0;
    }
    position = object->position;
    if (position == NULL) {
        return 0;
    }
    if (out != NULL) {
        *(Vec4_001E3B50 *)out = *position;
    }
    return 1;
}

typedef struct Vec4_001E3BF0 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4_001E3BF0;

/* The unit record SzDuel_SetCardRot writes, or NULL. */
static inline void *lookup_001E3BF0(void) {
    extern void *SzDuel_GetCardInfo();
    void *object;

    object = SzDuel_GetCardInfo();
    if (object == NULL) {
        return NULL;
    }
    if (*(u8 *)((u8 *)object + 0x45) >= 0xB) {
        return NULL;
    }
    return object;
}

/* Sets unit (side, unit)'s card rotation. */
s32 SzDuel_SetCardRot(s32 side, s32 unit, s32 rot) {
    void *temp_v0;
    void *var_v0;

    var_v0 = lookup_001E3BF0();
    if (var_v0 == NULL) {
        return 0;
    }
    temp_v0 = *(void **)((u8 *)var_v0 + 4);
    if (temp_v0 == NULL) {
        return 0;
    }
    if (rot != 0) {
        *(Vec4_001E3BF0 *)((u8 *)temp_v0 + 0x10) = *(Vec4_001E3BF0 *)rot;
    }
    return 1;
}

typedef struct Vec4_001E3C90 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4_001E3C90;

/* The unit record SzDuel_GetCardRot reads, or NULL. */
static inline void *lookup_001E3C90(void) {
    extern void *SzDuel_GetCardInfo();
    void *object = SzDuel_GetCardInfo();

    if (object == NULL) {
        return NULL;
    }
    if (((u8 *)object)[0x45] >= 0xB) {
        return NULL;
    }
    return object;
}

/* Unit (side, unit)'s card rotation into `out`. */
s32 SzDuel_GetCardRot(s32 side, s32 unit, void *out) {
    void *temp_v0;
    void *var_v0;

    var_v0 = lookup_001E3C90();
    if (var_v0 == NULL) {
        return 0;
    }
    temp_v0 = *(void **)((u8 *)var_v0 + 4);
    if (temp_v0 == NULL) {
        return 0;
    }
    if (out != NULL) {
        *(Vec4_001E3C90 *)out = *(Vec4_001E3C90 *)((u8 *)temp_v0 + 0x10);
    }
    return 1;
}

typedef struct Vec4_001E3D30 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4_001E3D30;

typedef struct Object_001E3D30 {
    u8 padding[0x30];
    Vec4_001E3D30 position;
} Object_001E3D30;

typedef struct Entry_001E3D30 {
    u8 padding0[4];
    Object_001E3D30 *object;
    u8 padding8[0x3D];
    u8 type;
} Entry_001E3D30;

/* The unit record SzDuel_SetCardScale writes, or NULL. */
static inline void *check_001E3D30(void) {
    extern void *SzDuel_GetCardInfo();
    Entry_001E3D30 *entry = SzDuel_GetCardInfo();

    if (entry == NULL) {
        return NULL;
    }
    if (entry->type >= 11) {
        return NULL;
    }
    return entry;
}

/* Sets unit (side, unit)'s card scale. */
s32 SzDuel_SetCardScale(s32 side, s32 unit, s32 scale) {
    Entry_001E3D30 *entry;
    Object_001E3D30 *object;

    entry = check_001E3D30();
    if (entry == NULL) {
        return 0;
    }
    object = entry->object;
    if (object == NULL) {
        return 0;
    }
    if (scale != 0) {
        object->position = *(Vec4_001E3D30 *)scale;
    }
    return 1;
}

typedef struct Vec4_001E3DD0 {
    f32 x, y, z, w;
} Vec4_001E3DD0;

/* The unit record SzDuel_GetCardScale reads, or NULL. */
static inline void *get_001E3DD0(void) {
    extern void *SzDuel_GetCardInfo();
    void *object = SzDuel_GetCardInfo();

    if (object == NULL) {
        return NULL;
    }
    if (*(u8 *)((u8 *)object + 0x45) >= 11) {
        return NULL;
    }
    return object;
}

/* Unit (side, unit)'s card scale into `out`. */
s32 SzDuel_GetCardScale(s32 side, s32 unit, void *out) {
    void *object = get_001E3DD0();
    void *data;

    if (object == NULL) {
        return 0;
    }
    data = *(void **)((u8 *)object + 4);
    if (data == NULL) {
        return 0;
    }
    if (out != NULL) {
        *(Vec4_001E3DD0 *)out = *(Vec4_001E3DD0 *)((u8 *)data + 0x30);
    }
    return 1;
}

typedef struct {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} Color_001E3E70;

/* The unit record SzDuel_SetCardRgba writes, or NULL. */
static inline void *lookup_001E3E70(void) {
    extern void *SzDuel_GetCardInfo();
    void *object = SzDuel_GetCardInfo();

    if (object == NULL) {
        return NULL;
    }
    if (*(u8 *)((u8 *)object + 0x45) >= 0xB) {
        return NULL;
    }
    return object;
}

/* Sets unit (side, unit)'s card colour. */
s32 SzDuel_SetCardRgba(s32 side, s32 unit, s32 rgba) {
    void *object;
    void *data;

    object = lookup_001E3E70();
    if (object == NULL) {
        return 0;
    }
    data = *(void **)((u8 *)object + 4);
    if (data == NULL) {
        return 0;
    }
    if (rgba != 0) {
        *(Color_001E3E70 *)((u8 *)data + 0x40) = *(Color_001E3E70 *)rgba;
    }
    return 1;
}

typedef struct Color_001E3F10 {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} Color_001E3F10;

/* The unit record SzDuel_GetCardRgba reads, or NULL. */
static inline void *get_001E3F10(void) {
    extern void *SzDuel_GetCardInfo();
    void *object = SzDuel_GetCardInfo();

    if (object == NULL) {
        return NULL;
    }
    if (*(u8 *)((u8 *)object + 0x45) >= 0xB) {
        return NULL;
    }
    return object;
}

/* Unit (side, unit)'s card colour into `out`. */
s32 SzDuel_GetCardRgba(s32 side, s32 unit, void *out) {
    void *object;
    void *data;

    object = get_001E3F10();
    if (object == NULL) {
        return 0;
    }
    data = *(void **)((u8 *)object + 4);
    if (data == NULL) {
        return 0;
    }
    if (out != NULL) {
        *(Color_001E3F10 *)out = *(Color_001E3F10 *)((u8 *)data + 0x40);
    }
    return 1;
}

/* Opens the hand pop-up for hand card `slot` at (x, y). */
void SzDuel_OpenHandPopup(s32 slot, s32 x, s32 y) {
    duelState.s.popupState[2] =  0x12;
    duelState.s.popupValue[2] =  slot;
    duelState.s.popupPos[2][0] =  x;
    duelState.s.popupPos[2][1] =  y;
}

/* Closes the hand pop-up. */
void SzDuel_CloseHandPopup(void) {
    D_00318144 = 0x18;
}

/* Opens the options pop-up at (x, y) for side `side` (< 0 keeps the current state), loaded with the three options. */
void SzDuel_OpenOptionPopup(s32 side, s16 x, s16 y) {
    u8 *state = duelState.b;
    s32 i;
    s32 bit;

    duelState.s.popupState[0] =  7;
    duelState.s.popupValue[0] =  0;
    duelState.s.popupPos[0][0] =  x;
    duelState.s.popupPos[0][1] =  y;
    if (side >= 0) {
        state[0xD54] = side;
        state[0xD35] = 0;
        state[0xD36] = 0;
        i = 0;
        do {
            if (SzData_GetOption(0, i) != 0) {
                bit = 1;
            } else {
                bit = 0;
            }
            state[0xD36] |= bit << i;
            i++;
        } while (i < 3);
    }
}

/* Runs the options pop-up for pad `pad`: 0 still open, 1 confirmed (options saved), 2 cancelled. */
s32 SzDuel_ActOptionPopup(s32 pad) {
    u8 *base;
    s32 option;
    s32 oldRow;
    s32 oldBits;

    base = duelState.b;
    if (SzPad_Check(pad, 2, 0x5000) != 0) {
        oldRow = base[0xD35];
        if (SzPad_Check(pad, 2, 0x1000) != 0) {
            base[0xD35] = (base[0xD35] + 1) % 2;
        } else {
            base[0xD35] = (base[0xD35] + 3) % 2;
        }
        if (base[0xD35] != oldRow) {
            SzSound_PlaySE(0, 3);
        }
        return 0;
    }
    if (SzPad_Check(pad, 0, 0xA000) != 0) {
        oldBits = base[0xD36];
        if (SzPad_Check(pad, 0, 0x8000) != 0) {
            base[0xD36] = base[0xD36] | (1 << (base[0xD35] + 1));
        } else {
            base[0xD36] = base[0xD36] & ~(1 << (base[0xD35] + 1));
        }
        if (base[0xD36] != oldBits) {
            SzSound_PlaySE(0, 3);
        }
        return 0;
    }
    if (SzPad_Check(pad, 0, 0xC0) != 0) {
        option = 0;
        do {
            SzData_SetOption(0, option, base[0xD36] & (1 << option));
            SzData_SetOption(1, option, base[0xD36] & (1 << option));
            option += 1;
        } while (option < 3);
        SzSound_PlaySE(0, 4);
        return 1;
    }
    if (SzPad_Check(pad, 0, 0x20) != 0) {
        SzSound_PlaySE(0, 5);
        return 2;
    }
    return 0;
}

/* Closes the options pop-up. */
void SzDuel_CloseOptionPopup(void) {
    D_00318142 = 0x18;
}

/* Opens message pop-up `kind` at (x, y); `card` is the card it names (a won card is added to the trunk). */
void SzDuel_OpenMsgPopup(s32 kind, s32 x, s32 y, s32 card) {
    u8 *state = duelState.b;

    switch (kind) {
    case 0:
        state[0xCB5] = 0x13;
        break;
    case 1:
        state[0xCB5] = 0xF;
        break;
    case 2:
        state[0xCB5] = 0xC;
        if (SzGame_GetMenuNum(0xF) == 0) {
            SzData_AddBag(state[0xD50], 0, card);
        }
        break;
    case 3:
        state[0xCB5] = 0xD;
        if (SzGame_GetMenuNum(0xF) == 0) {
            SzData_AddBag(state[0xD50], 0, card);
            SzData_RollSpecial(state[0xD50], card);
        }
        break;
    case 5:
        state[0xCB5] = 0x14;
        break;
    case 6:
        state[0xCB5] = 0x15;
        break;
    case 7:
        state[0xCB5] = 0x16;
        if (card >= 0) {
            state[0xD35] = (card & 0x8000) ? 1 : 0;
            card &= 0x7FFF;
        }
        break;
    case 8:
        state[0xCB5] = 0x10;
        break;
    default:
        state[0xCB5] = 0x18;
        return;
    }
    if (card >= 0) {
        *(s16 *)(state + 0xCB0) = card;
    }
    *(s16 *)(state + 0xCA6) = x;
    *(s16 *)(state + 0xCA8) = y;
}

/* Runs a yes/no message pop-up for pad `pad`: 0 still open, 1 yes, 2 no or cancelled. */
s32 SzDuel_ActMsgPopup(s32 pad) {
    u8 *state = duelState.b;
    s32 oldChoice;

    if (SzPad_Check(pad, 0, 0xA000) != 0) {
        oldChoice = state[0xD35];
        if (SzPad_Check(pad, 0, 0x8000) != 0) {
            state[0xD35] = 1;
        } else {
            state[0xD35] = 0;
        }
        if (state[0xD35] != oldChoice) {
            SzSound_PlaySE(0, 3);
        }
        return 0;
    }
    if (SzPad_Check(pad, 0, 0xC0) != 0) {
        SzSound_PlaySE(0, 4);
        return state[0xD35] ? 1 : 2;
    }
    if (SzPad_Check(pad, 0, 0x20) != 0) {
        SzSound_PlaySE(0, 5);
        return 2;
    }
    return 0;
}

/* Closes the message pop-up. */
void SzDuel_CloseMsgPopup(void) {
    D_00318145 = 0x18;
}

/* Opens the hand cursor on hand card `slot` at (x, y). */
void SzDuel_OpenHandCursor(s32 slot, s32 x, s32 y) {
    duelState.s.popupState[2] =  0x17;
    duelState.s.popupValue[2] =  slot;
    duelState.s.popupPos[2][0] =  x;
    duelState.s.popupPos[2][1] =  y;
}

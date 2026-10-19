#ifndef INLINES_H
#define INLINES_H
#ifndef __GNUC_MINOR__ /* not EE GCC: the Sony library files never use these, and
                          EE GCC 2.96's code changes when its headers grow */

/* Small functions the compiler wrote inline into many callers: one copy each, here. */

/* Unit (side, unit)'s record, or NULL when it has none on the board. SzDuel_GetUnit returns it. */
static inline Unit *lSzDuel_GetUnit(s32 side, s32 unit) {
    Unit *p = SzDuel_GetCardInfo(side, unit);

    if (p == NULL) {
        return NULL;
    }
    if (p->slot >= 11) {
        return NULL;
    }
    return p;
}

/* The larger of a and b. */
static inline s32 Max(s32 a, s32 b) {
    if (a < b) {
        return b;
    }
    return a;
}

/* The smaller of a and b. */
static inline s32 Min(s32 a, s32 b) {
    if (a < b) {
        return a;
    }
    return b;
}

/* |value|. */
static inline s32 Abs(s32 value) {
    if (value >= 0) {
        return value;
    }
    return -value;
}

/* How many squares apart (y1, x1) and (y2, x2) are, along the rows plus along the columns. */
static inline s32 TaLogic_Distance(s32 y1, s32 x1, s32 y2, s32 x2) {
    return (((y2 < y1) ? y1 : y2) - ((y1 < y2) ? y1 : y2)) +
           (((x2 < x1) ? x1 : x2) - ((x1 < x2) ? x1 : x2));
}

/* The computer opponent's life-point penalty for side `side`: 2000 at 1000 LP or less, else 500 with three
   or more monsters and 1000 with fewer. */
static inline s32 TaLogic_LifePenalty(s32 side) {
    if (SzDuel_GetLP(side) > 1000) {
        if (SzDuel_GetUnitMonsterCount(side) >= 3) {
            return 500;
        } else {
            return 1000;
        }
    } else {
        return 2000;
    }
}

/* Draws string `text` in a duel window (SzDuel_DrawWindow_Font_Pipe with its length). */
static inline s32 SzDuel_DrawWindowText_Pipe(s32 cursor, s32 x, s32 y, s32 align, s32 flags, s8 *text,
                                              void *color) {
    extern s32 SzDuel_DrawWindow_Font_Pipe();
    s32 length = func_0019BEF0((char *)text);
    return SzDuel_DrawWindow_Font_Pipe(cursor, x, y, align, flags, length, text, color);
}

/* `cell`, square (x, y)'s record, or NULL when (x, y) is off the board. */
static inline MapInfo *SzDuel_MapInfoAt(s32 x, s32 y, MapInfo *cell) {
    if (x < 0 || x >= 7 || y < 0 || y >= 7) {
        return NULL;
    }
    return cell;
}

/* value, or 0 when it is negative. */
static inline s32 AtLeast0(s32 value) {
    if (value > 0) {
        return value;
    }
    return 0;
}

/* Draws how many cards player `player` owns in all (4 digits). */
static inline s32 SzDuel_DrawBagCount_Pipe(s32 cursor, s32 x, s32 y, s32 player) {
    extern s32 SzDuel_DrawWindow_FontDigit_Pipe();
    s32 count = SzData_GetBagCountAll(player);
    return SzDuel_DrawWindow_FontDigit_Pipe(cursor, x, y, 1, 0, 4, count);
}

/* The duel side save profile `player` sits on: 0 for the profile shown on side 0, else 1. */
static inline s32 SzData_Side(s32 player) {
    extern u8 profileZeroSide;
    if (profileZeroSide == player) {
        return 0;
    }
    return 1;
}

/* A window's brightness: 0x80 when lit, else 0x30. */
static inline s32 SzDuel_WindowIntensity(s32 bright) {
    if (bright != 0) {
        return 0x80;
    }
    return 0x30;
}

/* The larger of a and b, written as a conditional expression (its own register order). */
static inline s32 MaxSel(s32 a, s32 b) {
    return b < a ? a : b;
}

/* The smaller of a and b, compared as a >= b + 1 (its own register order). */
static inline s32 MinSel(s32 a, s32 b) {
    return (a >= b + 1) ? b : a;
}

#endif
#endif

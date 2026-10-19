#ifndef INLINES_H
#define INLINES_H

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

#endif

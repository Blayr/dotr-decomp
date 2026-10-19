/* The duel screen, part 10 of 12: units on the board (add, move, stats, curses, control). */

#include "common.h"

/* Match note for this file: many unit getters below are written `(void)` or with parameters they never read,
   and call SzDuel_GetCardInfo() without arguments. Their callers pass (side, unit); the values go straight
   through in a0/a1 to SzDuel_GetCardInfo. Kept that way because it is what makes the bytes match. */

/* Unit `unit` of side `side` (0 = the leader, 1..10 the cards on the board), or 0 if there is none. */
s32 SzDuel_GetUnit(s32 side, s32 unit) {
    extern void *SzDuel_GetCardInfo();
    u8 *result;

    result = SzDuel_GetCardInfo(side, unit);
    if (result == NULL) {
        return 0;
    }
    if (result[0x45] >= 11) {
        result = NULL;
    }
    return (s32)result;
}

/* Puts card `card` on board square (x, z) as a new unit of side `side` (`leader` for the deck leader). */
void SzDuel_AddUnit(s32 side, s32 x, s32 z, s32 card, s32 leader) {
    u8 buffer[0x60];

    SzDuel_InitCardInfo(buffer, card);
    SzDuel_AddUnit2(side, x, z, buffer, leader);
}

/* Two floats: the leader abilities are copied 8 bytes at a time through the float registers (needed for the
   match). */
typedef struct {
    f32 a, b;
} FloatPair_001DF5F0;

/* A unit seen as its two pointers and five of those pairs (its abilities); written through this view, not as
   &unit->cardEffects (needed for the match). */
typedef struct {
    void *constInfo;
    void *cardModel;
    FloatPair_001DF5F0 pairs[5];
} UnitPairs_001DF5F0;

extern FloatPair_001DF5F0 D_002C3338_1df5f0[][5];
extern CardRequest D_003193C0_b[32];
extern DuelPlayer D_00317490_b[];
extern Vec4f D_002915D0;
extern Vec4i D_002915E0;
extern Vec4f D_002915F0;
extern int func_001F1A00_b(int index, int value);
/* A free card request record, cleared. */
static inline CardRequest *free_object(void)
{
    CardRequest *p = D_003193C0_b;
    int i;

    for (i = 0; i < 32; i++, p++) {
        if (p->unit == 0) {
            SzDuel_ClearDrawCard(p);
            return p;
        }
    }
    return 0;
}
/* A card's number in the old card order. */
static inline int card_index(int id)
{
    unsigned short *p = AlternateCardIds;
    int i;

    if (id == 671) {
        id = 999;
    }
    if (id < 0 || id >= 854) {
        return 999;
    }
    for (i = 0; i < 854; i++, p++) {
        if (*p == id) {
            return i;
        }
    }
    return 999;
}
/* Copies a 92-byte card record. */
static inline void copy_item(Unit *to, Unit *from)
{
    int *d = (int *)to;
    int *s = (int *)from;
    int n;

    for (n = 23; n > 0; n--) {
        *d++ = *s++;
    }
}

/* Puts the card record `src` on board square (x, y) as a new unit of side `side`: its slot, model and position. */
int SzDuel_AddUnit2(int side, int x, int y, void *src_v, int leader)
{
    Unit *src = src_v;
    DuelPlayer *rec = &D_00317490_b[side];
    MapInfo *c = SzDuel_MapInfo(x, y);
    int count = 1;
    int first = 0;
    int id;
    int i;
    int n;
    Unit *unit;
    int k;
    int model;

    if (src == 0) {
        return 0;
    }
    if (c == 0) {
        return 0;
    }
    if (c->unit != 0) {
        return 0;
    }
    id = src->cardNo;
    if (id == 671) {
        id = 999;
    }
    if (side < 0 || side >= 2 || id < 0 || id >= 854) {
        return 0;
    }
    if (leader != 0) {
        if (id >= 683) {
            return 0;
        }
    } else {
        count = 5;
        first = 1;
        if (id >= 683) {
            first = 6;
        }
    }
    for (i = 0; i < count; i++) {
        n = first + i;
        unit = &duelUnits[side][n];
        if (unit->slot >= 11) {
            copy_item(unit, src);
            unit->lvRev = Ta_GetSummonRev(side, id);
            unit->locCol = x;
            unit->locRow = y;
            unit->team = side;
            unit->slot = n;
            c->unit = unit;
            if (leader != 0) {
                for (k = 0; k < 5; k++) {
                    ((UnitPairs_001DF5F0 *)unit)->pairs[k] = D_002C3338_1df5f0[id][k];
                }
            } else {
                if (unit->cardModel == 0) {
                    unit->cardModel = free_object();
                }
                if (unit->cardModel != 0) {
                    unit->cardModel->unit = unit;
                    SzDuel_CalcUnitPos(x, y, 0, &unit->cardModel->pos);
                }
                unit->summonOrder = rec->unitsSummoned++;
                SzData_SetLookFlag(side, id, 1);
            }
            k = card_index(id);
            if (first == 0 || first == 1) {
                Vec4f pos = D_002915D0;
                Vec4i rot;
                Vec4f rotc;

                pos.x = (float)((x - 3) * 50);
                pos.z = (float)((y - 3) * 50);
                rot = D_002915E0;
                rot.y = (side != 0) ? 0 : 0x8000;
                rotc = D_002915F0;
                if (first == 0) {
                    model = side + 30;
                } else {
                    model = i + (side * count + 20);
                }
                unit->modelId = model;
                SzModel_Preset(model, -1, k);
                SzModel_SetAnimDirect(model, 0);
                func_001F1A00_b(model, 1);
                SzModel_SetAnimSpeed(model, 1.0f);
                SzModel_SetPos(model, &pos);
                SzModel_SetRot(model, &rot);
                SzModel_SetRotC(model, &rotc);
                SzModel_SetRgba(model, 0, 0);
                SzModel_SetFilter(model, 1, 0);
                lSzDuel_DoUnitRequest(c, (int)unit);
            }
            return (int)unit;
        }
    }
    return 0;
}

/* Unit record (a0, a1), or NULL. */
static inline Unit *check_001DFAF0(s32 a0, s32 a1) {
    extern void *SzDuel_GetCardInfo();
    Unit *p = SzDuel_GetCardInfo(a0, a1);

    if (p == NULL) {
        return NULL;
    }
    if (p->slot >= 0xB) {
        return NULL;
    }
    return p;
}

/* Replaces unit (side, unit) with card `card` on the same square. */
s32 SzDuel_PutUnit(s32 side, s32 unit, s32 card) {
    u8 buffer[0x60];
    Unit *record;
    s32 x;
    s32 y;

    record = check_001DFAF0(side, unit);
    if (record == NULL) {
        return 0;
    }
    side = record->team;
    unit = record->slot;
    x = record->locCol;
    y = record->locRow;
    SzDuel_DelUnit(side, unit);
    SzDuel_InitCardInfo(buffer, card);
    SzDuel_AddUnit2(side, x, y, buffer, unit == 0 ? 1 : 0);
}

/* Unit record (a0, a1), or NULL. */
static inline Unit *check_001DFBB0(s32 a0, s32 a1) {
    Unit *p = SzDuel_GetCardInfo(a0, a1);
    if (p == NULL) {
        return NULL;
    }
    if (p->slot >= 0xB) {
        return NULL;
    }
    return p;
}

/* Frees a card draw record. */
static inline s32 release_001DFBB0(void *p) {
    if (p == NULL) {
        return 0;
    }
    SzDuel_ClearDrawCard(p);
    *(s32 *)((u8 *)p + 0x90) = 0;
    return 1;
}

/* Card control record i, or NULL. */
static inline u8 *slot_001DFBB0(s32 i) {
    if (i < 0 || i >= 6) {
        return NULL;
    }
    return &cardControls[i * 0xA0];
}

/* Removes unit (side, unit) from the board: its square, model and card control. */
s32 SzDuel_DelUnit(s32 side, s32 unit) {
    Unit *obj;
    u8 *slot;

    obj = check_001DFBB0(side, unit);
    if (obj == NULL) {
        return 0;
    }
    if (side < 2) {
        if (obj->slot < 6) {
            SzModel_Preset(obj->modelId, -1, 0x3E7);
        }
        if (obj->cardModel != NULL) {
            release_001DFBB0(obj->cardModel);
        }
        SzDuel_MapInfo(obj->locCol, obj->locRow)->unit = NULL;
    } else if (unit > 0) {
        slot = slot_001DFBB0(unit);
        if (slot != NULL) {
            if (*(void **)slot != NULL) {
                release_001DFBB0(*(void **)slot);
            }
            SzDuel_ClearCardControl(slot);
        }
    }
    SzDuel_InitCardInfo(obj, -1);
    return 1;
}

typedef struct Entry_001DFD50 {
    CardRequest *object;
    u8 pad04[0x9C];
} Entry_001DFD50;

/* Frees a board object. */
static inline void remove_object_001DFD50(CardRequest *object) {
    extern void SzDuel_ClearDrawCard();

    if (object != NULL) {
        SzDuel_ClearDrawCard(object);
        object->unit = NULL;
    }
}

/* Moves unit (side, unit) to board square (x, y). Its three square lookups stay written out: as SzDuel_MapInfo calls
   the bytes differ. */
void *SzDuel_MoveUnit(s32 side, s32 unit, s32 x, s32 y) {
    extern void *SzDuel_GetCardInfo();
    Unit *piece;
    MapInfo *destination;
    Unit *occupied;
    s32 index;
    s32 player;
    MapInfo *source;
    CardRequest *object;
    Entry_001DFD50 *entry;
    CardRequest *entryObject;
    Unit *found;
    MapInfo *removed;
    s32 oldX;
    s32 oldY;
    s32 removedX;
    s32 removedY;
    Vec4f position;

    found = SzDuel_GetCardInfo(side, unit);
    if (found == NULL) {
        piece = NULL;
    } else if (found->slot >= 11) {
        piece = NULL;
    } else {
        piece = found;
    }
    if (piece == NULL) {
        return NULL;
    }
    oldX = piece->locCol;
    if (oldX == x && piece->locRow == y) {
        return NULL;
    }
    destination = NULL;
    if (x < 0 || x >= 7 || y < 0 || y >= 7) {
        destination = NULL;
    } else {
        destination = &boardSquares[y][x];
    }
    oldY = piece->locRow;
    source = NULL;
    if (oldX < 0 || oldX >= 7 || oldY < 0 || oldY >= 7) {
        source = NULL;
    } else {
        source = &boardSquares[oldY][oldX];
    }
    if (destination == NULL || source == NULL) {
        return NULL;
    }
    if (destination->unit != NULL) {
        index = destination->unit->slot;
        player = destination->unit->team;
        found = SzDuel_GetCardInfo(player, index);
        if (found == NULL) {
            occupied = NULL;
        } else if (found->slot >= 11) {
            occupied = NULL;
        } else {
            occupied = found;
        }
        if (occupied != NULL) {
            if (player < 2) {
                if (occupied->slot < 6) {
                    SzModel_Preset(occupied->modelId, -1, 999);
                }
                object = occupied->cardModel;
                if (object != NULL) {
                    remove_object_001DFD50(object);
                }
                removedX = occupied->locCol;
                removedY = occupied->locRow;
                if (removedX < 0 || removedX >= 7 || removedY < 0 || removedY >= 7) {
                    removed = NULL;
                } else {
                    removed = &boardSquares[removedY][removedX];
                }
                removed->unit = NULL;
            } else if (index > 0) {
                if (index < 0 || index >= 6) {
                    entry = NULL;
                } else {
                    entry = (Entry_001DFD50 *)(cardControls + index * 0xA0);
                }

                if (entry != NULL) {
                    entryObject = entry->object;

                    if (entryObject != NULL) {
                        remove_object_001DFD50(entryObject);
                    }
                    SzDuel_ClearCardControl((u8 *)entry);
                }
            }
            SzDuel_InitCardInfo(occupied, -1);
        }
    }
    piece->locCol = x;
    piece->locRow = y;
    piece->xOffsetTerrain = 0;
    piece->yOffsetTerrain = 0;
    source->unit = NULL;
    destination->unit = piece;
    SzModel_GetPos(piece->modelId, &position);
    position.x = (f32)((x - 3) * 50);
    position.z = (f32)((y - 3) * 50);
    SzModel_SetPos(piece->modelId, &position);
    if (piece->cardModel != NULL) {
        position.y = 0.0f;
        piece->cardModel->pos = position;
    }
    return piece;
}

/* How many units side `side` has on the board (monsters and spells). */
s32 SzDuel_GetUnitCount(s32 side) {
    s32 monsters;

    monsters = SzDuel_GetUnitMonsterCount(side);
    return monsters + SzDuel_GetUnitSpellCount(side);
}

/* Unit record (a0, a1) if it is a monster, or NULL. */
static inline Unit *check_001E0150(s32 a0, s32 a1) {
    Unit *p = SzDuel_GetCardInfo(a0, a1);
    if (p == NULL) {
        return NULL;
    }
    if (p->slot >= 0xB) {
        return NULL;
    }
    return p;
}

/* How many monsters side `side` has on the board. */
s32 SzDuel_GetUnitMonsterCount(s32 side) {
    s32 count;
    s32 i;

    count = 0;
    for (i = 1; i < 6; i++) {
        if (check_001E0150(side, i) != NULL) {
            count++;
        }
    }
    return count;
}

/* Unit record (a0, a1) if it is a magic or trap card, or NULL. */
static inline Unit *check_001E01F0(s32 a0, s32 a1) {
    Unit *p = SzDuel_GetCardInfo(a0, a1);
    if (p == NULL) {
        return NULL;
    }
    if (p->slot >= 0xB) {
        return NULL;
    }
    return p;
}

/* How many magic and trap cards side `side` has on the board. */
s32 SzDuel_GetUnitSpellCount(s32 side) {
    s32 count;
    s32 i;

    count = 0;
    for (i = 6; i < 0xB; i++) {
        if (check_001E01F0(side, i) != NULL) {
            count++;
        }
    }
    return count;
}

/* Unit record (side, unit), or NULL. */
static inline void *lookup_001E0290(s32 side, s32 unit)
{
    void *object = SzDuel_GetCardInfo(side, unit);

    if (object == 0) {
        return 0;
    }
    if (*((u8 *)object + 0x45) >= 11) {
        return 0;
    }
    return object;
}

/* Unit (side, unit)'s attack (`baseOnly`: without its power-ups). */
s32 SzDuel_GetUnitAP(s32 side, s32 unit, s32 baseOnly)
{
    return SzDuel_GetUnitAP2(lookup_001E0290(side, unit), baseOnly);
}

#define MAX_001E02F0(a, b) ((a) > (b) ? (a) : (b))
#define MIN_001E02F0(a, b) ((a) < (b) ? (a) : (b))

/* A unit's attack, 0..9999 (`baseOnly`: without its power-ups). */
s32 SzDuel_GetUnitAP2(void *unitInfo, s32 baseOnly) {
    s32 value;
    void *data;

    if (unitInfo == NULL) {
        return -1;
    }
    data = *(void **)unitInfo;
    if (data == NULL) {
        return -1;
    }
    value = *(u16 *)((u8 *)data + 8) & 0x1FFF;
    if (baseOnly == 0) {
        value += *(s16 *)((u8 *)unitInfo + 0x38);
    }
    return MIN_001E02F0(MAX_001E02F0(value, 0), 9999);
}

/* Unit record (side, unit), or NULL. */
static inline void *lookup_001E0370(s32 side, s32 unit) {
    void *ptr;

    ptr = SzDuel_GetCardInfo(side, unit);
    if (ptr == NULL) {
        return NULL;
    }
    if (*((u8 *)ptr + 0x45) >= 11) {
        return NULL;
    }
    return ptr;
}

/* Unit (side, unit)'s defence (`baseOnly`: without its power-ups). */
s32 SzDuel_GetUnitDP(s32 side, s32 unit, s32 baseOnly) {
    return SzDuel_GetUnitDP2(lookup_001E0370(side, unit), baseOnly);
}

/* Clamps at 0. */
static inline s32 lower_bound_001E03D0(s32 value) {
    if (value > 0) {
        return value;
    }
    return 0;
}

/* A unit's defence, 0..9999 (`baseOnly`: without its power-ups). */
s32 SzDuel_GetUnitDP2(void *unitInfo, s32 baseOnly) {
    s32 value;
    void *data;

    if (unitInfo == NULL) {
        return -1;
    }
    data = *(void **)unitInfo;
    if (data == NULL) {
        return -1;
    }
    value = *(u16 *)((u8 *)data + 0xA) & 0x1FFF;
    if (baseOnly == 0) {
        value += *(s16 *)((u8 *)unitInfo + 0x3A);
    }
    if (lower_bound_001E03D0(value) < 9999) {
        return lower_bound_001E03D0(value);
    }
    return 9999;
}

/* The unit record SzDuel_CalcUnitAP works on, or NULL. */
static inline void *get_001E0450(void) {
    extern void *SzDuel_GetCardInfo();
    void *info;

    info = SzDuel_GetCardInfo();
    if (info == NULL) {
        return NULL;
    }
    if (*(u8 *)((u8 *)info + 0x45) >= 0xB) {
        return NULL;
    }
    return info;
}

/* Applies `operation` (DUEL_CALC_*) with `value` to unit (side, unit)'s attack power-up. */
void SzDuel_CalcUnitAP(s32 side, s32 unit, s32 operation, s32 value) {
    SzDuel_CalcUnitAP2(get_001E0450(), operation, value);
}

#define MAX_001E04C0(a, b) ((a) > (b) ? (a) : (b))
#define MIN_001E04C0(a, b) ((a) < (b) ? (a) : (b))

typedef struct {
    u8 pad_00[0x38];
    s16 value;
} Obj_001E04C0;

/* Applies `operation` (DUEL_CALC_*) with `amount` to a unit's attack power-up. */
s32 SzDuel_CalcUnitAP2(void *unitInfo, s32 operation, s32 amount) {
    Obj_001E04C0 *obj = unitInfo;
    s32 cur;
    s32 val;

    val = amount;
    if (obj == NULL) {
        return 0;
    }
    cur = obj->value;
    switch (operation) {
    case 0:
        val = cur + val;
        break;
    case 1:
        val = cur - val;
        break;
    case 2:
        val = cur * val;
        break;
    case 3:
        val = cur / val;
        break;
    case 4:
        break;
    default:
        return 0;
    }
    val = MIN_001E04C0(MAX_001E04C0(val, -9999), 9999);
    obj->value = val;
    return 1;
}

/* A unit record, or NULL if it is not on the board. */
static inline void *check_001E0570(void *ptr) {
    if (ptr == NULL) {
        return NULL;
    }
    if (*((u8 *)ptr + 0x45) >= 0xB) {
        return NULL;
    }
    return ptr;
}

/* Applies `operation` (DUEL_CALC_*) with `value` to unit (side, unit)'s defence power-up. */
s32 SzDuel_CalcUnitDP(s32 side, s32 unit, s32 operation, s32 value) {
    void *info;

    info = check_001E0570(SzDuel_GetCardInfo(side, unit));
    return SzDuel_CalcUnitDP2(info, operation, value);
}

#define MAX_001E05E0(a, b) ((a) > (b) ? (a) : (b))
#define MIN_001E05E0(a, b) ((a) < (b) ? (a) : (b))

typedef struct {
    u8 pad_00[0x3A];
    s16 value;
} Obj_001E05E0;

/* Applies `operation` (DUEL_CALC_*) with `amount` to a unit's defence power-up. */
s32 SzDuel_CalcUnitDP2(void *unitInfo, s32 operation, s32 amount) {
    Obj_001E05E0 *obj = unitInfo;
    s32 cur;
    s32 val;

    val = amount;
    if (obj == NULL) {
        return 0;
    }
    cur = obj->value;
    switch (operation) {
    case 0:
        val = cur + val;
        break;
    case 1:
        val = cur - val;
        break;
    case 2:
        val = cur * val;
        break;
    case 3:
        val = cur / val;
        break;
    case 4:
        break;
    default:
        return 0;
    }
    val = MIN_001E05E0(MAX_001E05E0(val, -9999), 9999);
    obj->value = val;
    return 1;
}

typedef struct Entry_001E0690 {
    u8 *data;
    u8 padding[0x41];
    u8 slot; /* the unit's slot: 0 leader, 1..10 cards; 0xB and up = not on the board */
} Entry_001E0690;

/* The unit record SzDuel_GetUnitConstKind reads, or NULL. */
static inline void *lookup_001E0690(void) {
    extern void *SzDuel_GetCardInfo();
    Entry_001E0690 *entry = SzDuel_GetCardInfo();

    if (entry == NULL) {
        return NULL;
    }
    if (entry->slot >= 0xB) {
        return NULL;
    }
    return entry;
}

/* Unit (side, unit)'s card kind from its constant card data, or -1 (side, unit pass through to SzDuel_GetCardInfo). */
s32 SzDuel_GetUnitConstKind(s32 side, s32 unit) {
    Entry_001E0690 *entry = lookup_001E0690();

    if (entry == NULL) {
        return -1;
    }
    if (entry->data != NULL) {
        return *entry->data;
    }
    return -1;
}

/* The unit record SzDuel_GetUnitKind reads, or NULL. */
static inline Unit *get_entry_bytes_001E0700(void) {
    extern void *SzDuel_GetCardInfo();
    Unit *entry;

    entry = SzDuel_GetCardInfo();
    if (entry == NULL) {
        return NULL;
    }
    if (entry->slot >= 11) {
        return NULL;
    }
    return entry;
}

/* Unit (side, unit)'s current card kind, or -1. */
s32 SzDuel_GetUnitKind(s32 side, s32 unit) {
    Unit *entry;

    entry = get_entry_bytes_001E0700();
    if (entry != NULL) {
        return entry->kind;
    }
    return -1;
}

/* Unit record (a0, a1), or NULL. */
static inline Unit *check_001E0760(s32 a0, s32 a1) {
    Unit *p = SzDuel_GetCardInfo(a0, a1);
    if (p == NULL) {
        return NULL;
    }
    if (p->slot >= 0xB) {
        return NULL;
    }
    return p;
}

/* Sets unit (a0, a1)'s card kind. */
s32 SzDuel_SetUnitKind(s32 a0, s32 a1, s8 kind) {
    Unit *p;

    p = check_001E0760(a0, a1);
    if (p == NULL) {
        return 0;
    }
    p->kind = kind;
    return 1;
}

/* A unit record, or NULL if it is not on the board. */
static inline void *check_001E07C0(void *ptr) {
    if (ptr == NULL) {
        return NULL;
    }
    if (((u8 *)ptr)[0x45] >= 11) {
        return NULL;
    }
    return ptr;
}

/* How far a unit's kind was changed from its card's. */
s32 SzDuel_GetUnitKindOfs(void) {
    extern void *SzDuel_GetCardInfo();
    void **ptr;
    void *data;

    ptr = check_001E07C0(SzDuel_GetCardInfo());
    if (ptr == NULL) {
        return -1;
    }
    data = *ptr;
    if (data != NULL) {
        return ((u8 *)data)[1];
    }
    return -1;
}

/* Unit record (a0, a1), or NULL. */
static inline Unit *check_001E0830(s32 a0, s32 a1) {
    Unit *p = SzDuel_GetCardInfo(a0, a1);
    if (p == NULL) {
        return NULL;
    }
    if (p->slot >= 0xB) {
        return NULL;
    }
    return p;
}

/* Unit (side, unit)'s current attribute, or -1. */
s32 SzDuel_GetUnitAttr(s32 side, s32 unit) {
    Unit *p;

    p = check_001E0830(side, unit);
    if (p != NULL) {
        return p->attr;
    }
    return -1;
}

/* Unit record (side, unit), or NULL. */
static inline void *lookup_001E0890(s32 side, s32 unit) {
    void *entry;

    entry = SzDuel_GetCardInfo(side, unit);
    if (entry == NULL) {
        return NULL;
    }
    if (*(u8 *)((u8 *)entry + 0x45) >= 0xB) {
        return NULL;
    }
    return entry;
}

/* Sets unit (side, unit)'s attribute. */
s32 SzDuel_SetUnitAttr(s32 side, s32 unit, s8 attr) {
    void *entry;

    entry = lookup_001E0890(side, unit);
    if (entry == NULL) {
        return 0;
    }
    *(s8 *)((u8 *)entry + 0x3F) = attr;
    return 1;
}

/* A unit record, or NULL if it is not on the board. */
static inline void *check_001E08F0(void *info) {
    if (info == NULL) {
        return NULL;
    }
    if (*(u8 *)((u8 *)info + 0x45) >= 0xB) {
        return NULL;
    }
    return info;
}

/* Unit (side, unit)'s level (`baseOnly`: without its changes). */
void SzDuel_GetUnitLevel(s32 side, s32 unit, s32 baseOnly) {
    extern void *SzDuel_GetCardInfo();
    SzDuel_GetUnitLevel2(check_001E08F0(SzDuel_GetCardInfo()), baseOnly);
}

typedef struct Flags_001E0950 {
    u8 padding[2];
    u8 low : 4;
    u8 high : 4;
} Flags_001E0950;

/* A unit's level (`baseOnly`: without the summon change). */
s32 SzDuel_GetUnitLevel2(void *unitInfo, s32 baseOnly) {
    s32 value;
    void *card;

    if (unitInfo == NULL) {
        return -1;
    }
    card = *(void **)unitInfo;
    if (card == NULL) {
        return -1;
    }
    value = ((Flags_001E0950 *)card)->high;
    if (baseOnly == 0) {
        value -= *(u8 *)((u8 *)unitInfo + 0x48);
    }
    return (value > 0 ? value : 0) < 12 ? (value > 0 ? value : 0) : 12;
}

typedef struct Sub_001E09E0 {
    u8 pad[4];
    u16 id;
} Sub_001E09E0;

typedef struct Object_001E09E0 {
    Sub_001E09E0 *data;
    u8 pad04[0x38];
    u16 id;
    u8 pad3E[2];
    u8 x;
    u8 y;
    u8 pad42[3];
    u8 state;
} Object_001E09E0;

extern u8 D_002C3338[][5][8];
extern u8 D_002C9DF0[][5][8];
extern u8 D_002CC5F0[][8];

/* A unit's effect word `index` (0..4) from its card's constant data. */
void *SzDuel_GetUnitConstEffect2(void *unitInfo, s32 index) {
    void *cell;
    s32 on_board;
    s32 x;
    s32 y;
    s32 card_id;
    s32 data_id;
    Sub_001E09E0 *data;
    Object_001E09E0 *object = unitInfo;

    on_board = 1;
    if (object == NULL) {
        return NULL;
    }
    data = object->data;
    if (data == NULL) {
        return NULL;
    }
    if (index < 0 || index >= 5) {
        return NULL;
    }
    x = object->x;
    y = object->y;
    cell = SzDuel_MapInfo(x, y);
    if (cell == NULL || *(void **)cell != object) {
        on_board = 0;
    }
    if (on_board != 0 && object->state == 0) {
        card_id = object->id;
        if (card_id >= 0x356) {
            return NULL;
        }
        if (card_id == 0x29F) {
            return NULL;
        }
        return D_002C3338[card_id][index];
    }
    data_id = data->id;
    if (data_id == 0xFFFF) {
        return NULL;
    }
    if (object->state < 6) {
        return D_002C9DF0[data_id][index];
    }
    return D_002CC5F0[data_id];
}

/* The unit record SzDuel_GetUnitEffect reads, or NULL. */
static inline void *check_001E0B70(void) {
    extern void *SzDuel_GetCardInfo();
    void *record;

    record = SzDuel_GetCardInfo();
    if (record == NULL) {
        return NULL;
    }
    if (*(u8 *)((u8 *)record + 0x45) >= 11) {
        return NULL;
    }
    return record;
}

/* Unit (side, unit)'s effect `index`. */
void *SzDuel_GetUnitEffect(s32 side, s32 unit, s32 index) {
    void *record;

    record = check_001E0B70();
    if (record == NULL) {
        return NULL;
    }
    if (index < 0 || index >= 5) {
        return NULL;
    }
    return (u8 *)record + index * 8 + 8;
}

s32 SzDuel_GetUnitLeaderAbility2(void *, s32, s32);                /* extern */

/* The unit record SzDuel_GetUnitLeaderAbility reads, or NULL. */
static inline void *check_001E0C00(void) {
    extern void *SzDuel_GetCardInfo();
    void *ptr = SzDuel_GetCardInfo();
    if (ptr == NULL) {
        return NULL;
    }
    if (*((u8 *)ptr + 0x45) >= 0xB) {
        return NULL;
    }
    return ptr;
}

/* Whether unit (side, unit), a leader, has leader ability `ability` (its strength through `extra`). */
s32 SzDuel_GetUnitLeaderAbility(s32 side, s32 unit, s32 ability, s32 extra) {
    return SzDuel_GetUnitLeaderAbility2(check_001E0C00(), ability, extra);
}

/* Whether a leader unit has leader ability `ability` (its strength through `extra`). */
s32 SzDuel_GetUnitLeaderAbility2(void *unitInfo, s32 ability, s32 extra) {
    extern s32 SzDuel_GetUnitLeaderAbility3();

    return SzDuel_GetUnitLeaderAbility3(unitInfo, ability, extra, 0);
}

typedef struct Card_001E0C80 {
    u8 pad0[8];
    u32 pairs[9];
    u8 pad2C[0x10];
    u16 id;
    u8 pad3E[6];
    u8 owner;
} Card_001E0C80;

/* Whether a leader unit has leader ability `ability` at its rank (its strength through `outExtra`); `ignoreOption`
   skips the custom-duel switch. */
s32 SzDuel_GetUnitLeaderAbility3(void *unitInfo, u32 ability, s32 *outExtra, s32 ignoreOption) {
    extern s32 SzData_GetRank();
    s32 extra;
    s32 need;
    Card_001E0C80 *card = unitInfo;
    s32 value;

    extra = 0;
    if (outExtra != NULL) {
        *outExtra = 0;
    }
    if (card == NULL) {
        return 0;
    }
    if (card->id >= 0x356) {
        return 0;
    }
    if (card->id == 0x29F) {
        return 0;
    }
    if (ignoreOption == 0) {
        value = SzGame_GetMenuNum(0x1C);
        if (!(value & (1 << card->owner))) {
            return 0;
        }
    }
    switch (ability) {
    case 0:
        value = card->pairs[0] >> 16;
        if (value == 0xFFFF) {
            return 0;
        }
        return value ? 1 : 0;
    case 1:
        value = (u16)card->pairs[0];
        if (value == 0xFFFF) {
            return 0;
        }
        return value ? 1 : 0;
    case 2:
        value = card->pairs[1] >> 16;
        if (value == 0xFFFF) {
            return 0;
        }
        need = value >> 8;
        extra = value & 0xFF;
        break;
    case 3:
        value = (u16)card->pairs[1];
        if (value == 0xFFFF) {
            return 0;
        }
        need = value >> 8;
        break;
    case 4:
        value = card->pairs[2] >> 16;
        if (value == 0xFFFF) {
            return 0;
        }
        need = value >> 8;
        break;
    case 5:
        value = (u16)card->pairs[2];
        if (value == 0xFFFF) {
            return 0;
        }
        need = value >> 8;
        break;
    case 6:
        value = card->pairs[3] >> 16;
        if (value == 0xFFFF) {
            return 0;
        }
        need = value >> 8;
        break;
    case 7:
        value = (u16)card->pairs[3];
        if (value == 0xFFFF) {
            return 0;
        }
        need = value & 0xFF;
        extra = value >> 8;
        break;
    case 8:
        value = card->pairs[4] >> 16;
        if (value == 0xFFFF) {
            return 0;
        }
        need = value & 0xFF;
        extra = value >> 8;
        break;
    case 9:
        value = (u16)card->pairs[4];
        if (value == 0xFFFF) {
            return 0;
        }
        need = value >> 8;
        break;
    case 10:
        value = card->pairs[5] >> 16;
        if (value == 0xFFFF) {
            return 0;
        }
        need = value & 0xFF;
        extra = value >> 8;
        break;
    case 11:
        value = (u16)card->pairs[5];
        if (value == 0xFFFF) {
            return 0;
        }
        need = value >> 8;
        break;
    case 12:
        value = card->pairs[6] >> 16;
        if (value == 0xFFFF) {
            return 0;
        }
        need = value >> 8;
        break;
    case 13:
        value = (u16)card->pairs[6];
        if (value == 0xFFFF) {
            return 0;
        }
        need = value >> 8;
        break;
    case 14:
        value = card->pairs[7] >> 16;
        if (value == 0xFFFF) {
            return 0;
        }
        need = value & 0xFF;
        extra = value >> 8;
        break;
    case 15:
        value = (u16)card->pairs[7];
        if (value == 0xFFFF) {
            return 0;
        }
        need = value >> 8;
        break;
    case 16:
        value = card->pairs[8] >> 16;
        if (value == 0xFFFF) {
            return 0;
        }
        need = value >> 8;
        break;
    default:
        return 0;
    }
    value = SzData_GetRank(card->owner, card->id);
    if (outExtra != NULL) {
        *outExtra = extra;
    }
    return (value >= need) ? 1 : 0;
}

/* A unit's card id, or -1. */
s32 SzDuel_GetUnitCardNo(void) {
    extern void *SzDuel_GetCardInfo();
    Unit *entry;

    entry = SzDuel_GetCardInfo();
    if (entry == NULL) {
        entry = NULL;
    } else if (entry->slot >= 11) {
        entry = NULL;
    }
    if (entry != NULL) {
        return entry->cardNo;
    }
    return -1;
}

/* The unit record SzDuel_GetUnitLoc reads, or NULL. */
static inline Unit *get_001E1090(void) {
    extern void *SzDuel_GetCardInfo();
    Unit *data;

    data = SzDuel_GetCardInfo();
    if (data == NULL) {
        return NULL;
    }
    if (data->slot >= 0xB) {
        return NULL;
    }
    return data;
}

/* Unit (side, unit)'s board square as (z << 8) | x, or -1. */
s32 SzDuel_GetUnitLoc(s32 side, s32 unit) {
    Unit *data;

    data = get_001E1090();
    if (data != NULL) {
        return (data->locRow << 8) | data->locCol;
    }
    return -1;
}

/* The 3D position of board square (x, z) at height `height` into `out`. */
void SzDuel_CalcUnitPos(s32 x, s32 z, s32 height, void *outPos) {
    f32 *out = outPos;

    out[2] = 0.0f;
    out[0] = 0.0f;
    if ((x >= 0) && (x < 7)) {
        out[0] = (f32) ((x - 3) * 50);
    }
    if ((z >= 0) && (z < 7)) {
        out[2] = (f32) ((z - 3) * 50);
    }
    out[1] = (f32) (height * 35) / 128.0f;
    out[3] = 1.0f;
}

/* Unit record (a0, a1), or NULL. */
static inline Unit *check_001E11B0(s32 a0, s32 a1) {
    Unit *p = SzDuel_GetCardInfo(a0, a1);
    if (p == NULL) {
        return NULL;
    }
    if (p->slot >= 0xB) {
        return NULL;
    }
    return p;
}

/* SzDuel_CalcUnitPos written out. */
static inline void place_001E11B0(s32 x, s32 z, s32 height, void *outPos) {
    f32 *out = outPos;

    out[2] = 0.0f;
    out[0] = 0.0f;
    if ((x >= 0) && (x < 7)) {
        out[0] = (f32) ((x - 3) * 50);
    }
    if ((z >= 0) && (z < 7)) {
        out[2] = (f32) ((z - 3) * 50);
    }
    out[1] = (f32) (height * 35) / 128.0f;
    out[3] = 1.0f;
}

/* Unit (side, unit)'s 3D position (its square, height and offset) into `pos`. */
s32 SzDuel_GetUnitPos(s32 side, s32 unit, f32 *pos) {
    Unit *p;

    p = check_001E11B0(side, unit);
    if (p == NULL) {
        return 0;
    }
    place_001E11B0(p->locCol, p->locRow, SzDuel_MapInfo(p->locCol, p->locRow)->fieldRate, pos);
    pos[0] += (f32) p->xOffsetTerrain;
    pos[2] += (f32) p->yOffsetTerrain;
    return 1;
}

/* The unit record SzDuel_GetUnitModelID reads, or NULL. */
static inline void *lookup_001E1360(void) {
    extern void *SzDuel_GetCardInfo();
    void *ptr;

    ptr = SzDuel_GetCardInfo();
    if (ptr == NULL) {
        ptr = NULL;
    } else if (*((u8 *)ptr + 0x45) >= 11) {
        ptr = NULL;
    }
    return ptr;
}

/* Unit (side, unit)'s model slot, or -1 (side, unit pass through to SzDuel_GetCardInfo). */
s32 SzDuel_GetUnitModelID(s32 side, s32 unit) {
    void *ptr;

    ptr = lookup_001E1360();
    if (ptr != NULL) {
        return *((u8 *)ptr + 0x46);
    }
    return -1;
}

typedef struct Entry_001E13C0 {
    u8 padding[0x45];
    u8 slot; /* the unit's slot: 0 leader, 1..10 cards; 0xB and up = not on the board */
    u8 padding46;
    u8 value;
} Entry_001E13C0;

/* The order in which unit (side, unit) was summoned, or -1 (side, unit pass through to SzDuel_GetCardInfo). */
s32 SzDuel_GetUnitSummonOrder(s32 side, s32 unit) {
    extern void *SzDuel_GetCardInfo();
    Entry_001E13C0 *entry;

    entry = SzDuel_GetCardInfo();
    if (entry == NULL) {
        entry = NULL;
    } else if (entry->slot >= 0xB) {
        entry = NULL;
    }
    if (entry != NULL) {
        return entry->value;
    }
    return -1;
}

typedef struct Flags_001E1420 {
    s8 : 3;
    s8 enabled : 1;
    s8 : 4;
} Flags_001E1420;

/* The unit record SzDuel_SetUnitCurseFlag writes, or NULL. */
static inline void *check_001E1420(void) {
    extern void *SzDuel_GetCardInfo();
    void *ptr = SzDuel_GetCardInfo();

    if (ptr == NULL) {
        return NULL;
    }
    if (*(u8 *)((u8 *)ptr + 0x45) >= 0xB) {
        return NULL;
    }
    return ptr;
}

/* Marks unit (side, unit) as cursed or not. */
s32 SzDuel_SetUnitCurseFlag(s32 side, s32 unit, s32 on) {
    void *ptr = check_001E1420();

    if (ptr == NULL) {
        return 0;
    }
    ((Flags_001E1420 *)((u8 *)ptr + 0x58))->enabled = (s8)(on != 0 ? 1 : 0);
    return 1;
}

typedef struct {
    s8 reserved : 3;
    s8 active : 1;
    s8 reserved2 : 4;
} Flags_001E14B0;

typedef struct {
    u8 reserved[0x45];
    u8 slot; /* the unit's slot: 0 leader, 1..10 cards; 0xB and up = not on the board */
    u8 reserved2[0x12];
    Flags_001E14B0 flags;
} Entry_001E14B0;

/* The unit record SzDuel_GetUnitCurseFlag reads, or NULL. */
static inline void *lookup_001E14B0(void) {
    extern void *SzDuel_GetCardInfo();
    void *entry = SzDuel_GetCardInfo();

    if (entry == NULL) {
        entry = NULL;
    } else if (((Entry_001E14B0 *)entry)->slot >= 0xB) {
        entry = NULL;
    }
    return entry;
}

/* Whether a unit is cursed. */
s32 SzDuel_GetUnitCurseFlag(void) {
    void *entry = lookup_001E14B0();

    if (entry == NULL) {
        return 0;
    }
    return ((Entry_001E14B0 *)entry)->flags.active != 0 ? 1 : 0;
}

/* The unit record SzDuel_SetUnitCurseRest writes, or NULL. */
static inline void *lookup_001E1520(void) {
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

/* Sets how many turns unit (side, unit)'s curse lasts. */
s32 SzDuel_SetUnitCurseRest(s32 side, s32 unit, s8 turns) {
    void *entry = lookup_001E1520();

    if (entry == NULL) {
        return 0;
    }
    *(s8 *)((u8 *)entry + 0x49) = turns;
    return 1;
}

/* The unit record SzDuel_GetUnitCurseRest reads, or NULL. */
static inline void *get_001E1580(void) {
    extern void *SzDuel_GetCardInfo();
    void *entry;

    entry = SzDuel_GetCardInfo();
    if (entry == NULL) {
        return NULL;
    }
    if (*(u8 *)((u8 *)entry + 0x45) >= 11) {
        return NULL;
    }
    return entry;
}

/* How many turns a unit's curse still lasts, or -1. */
s32 SzDuel_GetUnitCurseRest(void) {
    void *entry;

    entry = get_001E1580();
    if (entry != NULL) {
        return *(u8 *)((u8 *)entry + 0x49);
    }
    return -1;
}

/* Sets how many turns unit (side, unit)'s spell binding lasts. */
s32 SzDuel_SetUnitSpellRest(s32 side, s32 unit, s8 turns) {
    extern void *SzDuel_GetCardInfo();
    void *info;

    info = SzDuel_GetCardInfo();
    if (info == NULL) {
        info = NULL;
    } else if (*(u8 *)((u8 *)info + 0x45) >= 0xB) {
        info = NULL;
    }
    if (info == NULL) {
        return 0;
    }
    *(s8 *)((u8 *)info + 0x4A) = turns;
    return 1;
}

/* The unit record SzDuel_GetUnitSpellRest reads, or NULL. */
static inline Unit *check_001E1640(void) {
    extern void *SzDuel_GetCardInfo();
    Unit *entry;

    entry = SzDuel_GetCardInfo();
    if (entry == NULL) {
        return NULL;
    }
    if (entry->slot >= 11) {
        entry = NULL;
    }
    return entry;
}

/* How many turns a unit's spell binding still lasts, or -1. */
s32 SzDuel_GetUnitSpellRest(void) {
    Unit *entry;

    entry = check_001E1640();
    if (entry != NULL) {
        return entry->spellRest;
    }
    return -1;
}

/* Unit record (a0, a1), or NULL. */
static inline Unit *check_001E16A0(s32 a0, s32 a1) {
    Unit *p = SzDuel_GetCardInfo(a0, a1);
    if (p == NULL) {
        return NULL;
    }
    if (p->slot >= 0xB) {
        return NULL;
    }
    return p;
}

/* Sets unit (a0, a1)'s delay counter. */
s32 SzDuel_SetUnitDelayCount(s32 a0, s32 a1, s8 count) {
    Unit *p;

    p = check_001E16A0(a0, a1);
    if (p == NULL) {
        return 0;
    }
    p->delayCount = count;
    return 1;
}

/* The unit record SzDuel_GetUnitDelayCount reads, or NULL. */
static inline Unit *valid_001E1700(void) {
    extern void *SzDuel_GetCardInfo();
    Unit *ptr;

    ptr = SzDuel_GetCardInfo();
    if (ptr == NULL) {
        return NULL;
    }
    if (ptr->slot >= 0xB) {
        return NULL;
    }
    return ptr;
}

/* A unit's delay counter, or -1. */
s32 SzDuel_GetUnitDelayCount(void) {
    Unit *ptr;

    ptr = valid_001E1700();
    if (ptr != NULL) {
        return ptr->delayCount;
    }
    return -1;
}

typedef struct Card_001E1760 {
    u8 pad00[0x40];
    u8 x;
    u8 y;
    u8 pad42[3];
    u8 slot; /* the unit's slot: 0 leader, 1..10 cards */
} Card_001E1760;

/* How many squares a unit may move from where it stands. */
s32 SzDuel_CalcUnitMovable(void) {
    extern void *SzDuel_GetCardInfo();
    Card_001E1760 *card;

    card = SzDuel_GetCardInfo();
    if (card == NULL) {
        card = NULL;
    } else if (card->slot >= 11) {
        card = NULL;
    }
    if (card != NULL) {
        return GetMoveRange((s32)card, card->x, card->y) & 0xF;
    }
    return 0;
}

typedef struct {
    u8 padding[0x40];
    u8 x;
    u8 y;
    u8 padding_42[3];
    u8 slot; /* the unit's slot: 0 leader, 1..10 cards */
} Card_001E17D0;

/* The unit record SzDuel_IsUnitMovableOnLabyrinth reads, or NULL. */
static inline void *get_card_001E17D0(void) {
    extern void *SzDuel_GetCardInfo();
    Card_001E17D0 *card = SzDuel_GetCardInfo();

    if (card == NULL) {
        return NULL;
    }
    if (card->slot >= 11) {
        return NULL;
    }
    return card;
}

/* Whether a unit may move through labyrinth squares. */
s32 SzDuel_IsUnitMovableOnLabyrinth(void) {
    Card_001E17D0 *card = get_card_001E17D0();

    if (card == NULL) {
        return 0;
    }
    return ((u32)GetMoveRange((s32)card, card->x, card->y) >> 4) != 0 ? 1 : 0;
}

/* Sets unit (side, unit)'s card control mode. */
s32 SzDuel_SetUnitCtlModeC(s32 side, s32 unit, s8 mode) {
    extern void *SzDuel_GetCardInfo();
    void *info;

    info = SzDuel_GetCardInfo();
    if (info == NULL) {
        info = NULL;
    } else if (*(u8 *)((u8 *)info + 0x45) >= 0xB) {
        info = NULL;
    }
    if (info == NULL) {
        return 0;
    }
    *(s8 *)((u8 *)info + 0x4E) = mode;
    return 1;
}

/* The unit record SzDuel_SetUnitCtlModeM writes, or NULL. */
static inline void *check_001E18A0(void) {
    extern void *SzDuel_GetCardInfo();
    void *p = SzDuel_GetCardInfo();
    if (p == NULL) {
        return NULL;
    }
    if (*(u8 *)((u8 *)p + 0x45) >= 0xB) {
        return NULL;
    }
    return p;
}

/* Sets unit (side, unit)'s model control mode. */
s32 SzDuel_SetUnitCtlModeM(s32 side, s32 unit, s8 mode) {
    void *p = check_001E18A0();
    if (p == NULL) {
        return 0;
    }
    *(s8 *)((u8 *)p + 0x4F) = mode;
    return 1;
}

/* Sets unit (side, unit)'s card and model control goal; 1 if both took it. */
s32 SzDuel_SetUnitCtlGoal(s32 side, s32 unit, s8 goal) {
    s32 ok;

    ok = 0;
    if (SzDuel_SetUnitCtlGoalC(side, unit, goal) != 0) {
        if (SzDuel_SetUnitCtlGoalM(side, unit, goal) != 0) {
            ok = 1;
        }
    }
    return ok;
}

/* The unit record SzDuel_SetUnitCtlGoalC writes, or NULL. */
static inline void *get_001E1970(void) {
    extern void *SzDuel_GetCardInfo();
    void *p;

    p = SzDuel_GetCardInfo();
    if (p == NULL) {
        return NULL;
    }
    if (*(u8 *)((u8 *)p + 0x45) >= 0xB) {
        return NULL;
    }
    return p;
}

/* Sets unit (side, unit)'s card control goal. */
s32 SzDuel_SetUnitCtlGoalC(s32 side, s32 unit, s8 goal) {
    void *p;

    p = get_001E1970();
    if (p == NULL) {
        return 0;
    }
    *(s8 *)((u8 *)p + 0x50) = goal;
    return 1;
}

/* The unit record SzDuel_SetUnitCtlGoalM writes, or NULL. */
static inline Unit *lookup_001E19D0(void) {
    extern void *SzDuel_GetCardInfo();
    Unit *entry = SzDuel_GetCardInfo();

    if (entry == NULL) {
        return NULL;
    }
    if (entry->slot >= 11) {
        return NULL;
    }
    return entry;
}

/* Sets unit (side, unit)'s model control goal. */
s32 SzDuel_SetUnitCtlGoalM(s32 side, s32 unit, s8 goal) {
    Unit *entry = lookup_001E19D0();

    if (entry == NULL) {
        return 0;
    }
    entry->ctlGoalM = goal;
    return 1;
}

/* The unit record SzDuel_GetUnitCtlGoalC reads, or NULL. */
static inline Unit *get_entry_001E1A30(void) {
    extern void *SzDuel_GetCardInfo();
    Unit *entry;

    entry = SzDuel_GetCardInfo();
    if (entry == NULL) {
        return NULL;
    }
    if (entry->slot >= 0xB) {
        return NULL;
    }
    return entry;
}

/* A unit's card control goal, or -1. */
s32 SzDuel_GetUnitCtlGoalC(void) {
    Unit *entry;

    entry = get_entry_001E1A30();
    if (entry != NULL) {
        return entry->ctlGoalC;
    }
    return -1;
}

/* A unit record, or NULL if it is not on the board. */
static inline void *check_001E1A90(void *p) {
    if (p == NULL) {
        return NULL;
    }
    if (((u8 *)p)[0x45] >= 11) {
        return NULL;
    }
    return p;
}

/* A unit's model control goal, or -1. */
s32 SzDuel_GetUnitCtlGoalM(void) {
    extern void *SzDuel_GetCardInfo();
    u8 *p;

    p = check_001E1A90(SzDuel_GetCardInfo());
    if (p != NULL) {
        return p[0x51];
    }
    return -1;
}

/* Sets unit (side, unit)'s card and model control direction and speed; 1 if both took it. */
s32 SzDuel_SetUnitCtlRate(s32 side, s32 unit, s32 direction, s32 speed) {
    s32 ok;

    ok = 0;
    if (SzDuel_SetUnitCtlRateC(side, unit, direction, speed) != 0) {
        if (SzDuel_SetUnitCtlRateM(side, unit, direction, speed) != 0) {
            ok = 1;
        }
    }
    return ok;
}

/* The unit record SzDuel_SetUnitCtlRateC writes, or NULL. */
static inline void *check_001E1B70(void) {
    extern void *SzDuel_GetCardInfo();
    Unit *object;

    object = (Unit *) SzDuel_GetCardInfo();
    if (object == NULL) {
        return NULL;
    }
    if (object->slot >= 0xB) {
        return NULL;
    }
    return object;
}

/* Sets unit (side, unit)'s card control direction and speed (speed < 0 keeps it). */
s32 SzDuel_SetUnitCtlRateC(s32 side, s32 unit, s32 direction, s32 speed) {
    Unit *object;

    object = (Unit *) check_001E1B70();
    if (object == NULL) {
        return 0;
    }
    object->SomeStatusBitfield.nCtlFlipC = (s8) (direction & 3);
    if (speed >= 0) {
        object->ctlRateC = speed;
    }
    return 1;
}

typedef struct Flags_001E1C10 {
    s8 unused0 : 2;
    s8 direction : 2;
    s8 unused1 : 4;
} Flags_001E1C10;

/* A unit record, or NULL if it is not on the board. */
static inline void *check_001E1C10(void *p) {
    if (p == NULL) {
        return NULL;
    }
    if (*(u8 *)((u8 *)p + 0x45) >= 0xB) {
        return NULL;
    }
    return p;
}

/* Sets unit (side, unit)'s model control direction and speed (speed < 0 keeps it). */
s32 SzDuel_SetUnitCtlRateM(s32 side, s32 unit, s32 newDirection, s32 speed) {
    extern void *SzDuel_GetCardInfo();
    void *info;

    info = check_001E1C10(SzDuel_GetCardInfo());
    if (info == NULL) {
        return 0;
    }
    ((Flags_001E1C10 *)((u8 *)info + 0x56))->direction = newDirection & 3;
    if (speed >= 0) {
        *(s8 *)((u8 *)info + 0x53) = speed;
    }
    return 1;
}

/* The unit record SzDuel_GetUnitCtlRateC reads, or NULL. */
static inline void *get_entry_001E1CB0(void) {
    extern void *SzDuel_GetCardInfo();
    void *entry;

    entry = SzDuel_GetCardInfo();
    if (entry == NULL) {
        return NULL;
    }
    if (*(u8 *)((u8 *)entry + 0x45) >= 0xB) {
        return NULL;
    }
    return entry;
}

/* A unit's card control speed, or -1. */
s32 SzDuel_GetUnitCtlRateC(void) {
    void *entry;

    entry = get_entry_001E1CB0();
    if (entry != NULL) {
        return *(u8 *)((u8 *)entry + 0x52);
    }
    return -1;
}

/* A unit's model control speed, or -1. */
s32 SzDuel_GetUnitCtlRateM(void) {
    extern void *SzDuel_GetCardInfo();
    Unit *ptr;

    ptr = SzDuel_GetCardInfo();
    if (ptr == NULL) {
        ptr = NULL;
    } else if ((s32) ptr->slot >= 0xB) {
        ptr = NULL;
    }
    if (ptr != NULL) {
        return ptr->ctlRateM;
    }
    return -1;
}

typedef struct Flags_001E1D70 {
    s8 low : 4;
    s8 mode : 2;
    s8 high : 2;
} Flags_001E1D70;

typedef struct State_001E1D70 {
    u8 pad0[0x45];
    u8 kind;
    u8 pad46[0xE];
    s8 value;
    u8 pad55;
    Flags_001E1D70 flags;
} State_001E1D70;

/* Sets how unit (side, unit)'s card opens (face up / down) and how fast (speed < 0 keeps it). */
s32 SzDuel_SetUnitOpenRate(s32 side, s32 unit, s32 openMode, s32 speed) {
    extern void *SzDuel_GetCardInfo();
    State_001E1D70 *state;

    state = SzDuel_GetCardInfo();
    if (state == NULL) {
        state = NULL;
    } else if (state->kind >= 11) {
        state = NULL;
    }
    if (state == NULL) {
        return 0;
    }
    state->flags.mode = openMode & 3;
    if (speed >= 0) {
        state->value = speed;
    }
    return 1;
}

/* The unit record SzDuel_GetUnitOpenRate reads, or NULL. */
static inline Unit *lookup_001E1E10(void) {
    extern void *SzDuel_GetCardInfo();
    Unit *entry;

    entry = SzDuel_GetCardInfo();
    if (entry == NULL) {
        return NULL;
    }
    if (entry->slot >= 0xB) {
        return NULL;
    }
    return entry;
}

/* How fast a unit's card opens, or -1. */
s32 SzDuel_GetUnitOpenRate(void) {
    Unit *entry;

    entry = lookup_001E1E10();
    if (entry != NULL) {
        return entry->openRate;
    }
    return -1;
}

typedef struct Flags_001E1E70 {
    u8 pad0[0x56];
    s8 unused0 : 4;
    s8 sideA : 2;
    s8 sideB : 2;
    s8 bit0 : 1;
    s8 bit1 : 1;
    s8 bit2 : 1;
    s8 bit3 : 1;
    s8 bit4 : 1;
    s8 bit5 : 1;
    s8 unused57 : 2;
} Flags_001E1E70;

/* Unit record (side, unit)'s status flags, or NULL. */
static inline void *get_001E1E70(s32 side, s32 unit) {
    Unit *card = SzDuel_GetCardInfo(side, unit);

    if (card == NULL) {
        return NULL;
    }
    if (card->slot >= 0xB) {
        return NULL;
    }
    return card;
}

/* Sets status flag `flag` (0..5) of unit (side, unit) to `on`; flags 2-5 also turn the card face up or down. */
s32 SzDuel_SetUnitStatus(s32 side, s32 unit, s32 flag, s32 on) {
    Flags_001E1E70 *card = get_001E1E70(side, unit);

    if (card == NULL) {
        return 0;
    }
    switch (flag) {
    case 0:
        card->bit0 = on;
        break;
    case 1:
        card->bit1 = on;
        break;
    case 2:
        card->bit2 = on;
        card->sideA = (on ? 1 : -1) & 3;
        break;
    case 3:
        card->bit3 = on;
        card->sideB = (on ? 1 : -1) & 3;
        break;
    case 4:
        card->bit4 = on;
        card->bit2 = on;
        card->sideA = (on ? 1 : -1) & 3;
        break;
    case 5:
        card->bit5 = on;
        card->bit3 = on;
        card->sideB = (on ? 1 : -1) & 3;
        break;
    default:
        return 0;
    }
    return 1;
}

typedef struct Flags_001E2100 {
    u8 pad0[0x57];
    s8 bit0 : 1;
    s8 bit1 : 1;
    s8 bit2 : 1;
    s8 bit3 : 1;
    s8 bit4 : 1;
    s8 bit5 : 1;
    s8 unused : 2;
} Flags_001E2100;

/* Unit record (side, unit)'s status flags, or NULL. */
static inline void *get_001E2100(s32 side, s32 unit) {
    Unit *card = SzDuel_GetCardInfo(side, unit);

    if (card == NULL) {
        return NULL;
    }
    if (card->slot >= 0xB) {
        return NULL;
    }
    return card;
}

/* Status flag `flag` (0..5) of unit (side, unit). */
s32 SzDuel_GetUnitStatus(s32 side, s32 unit, s32 flag) {
    Flags_001E2100 *card = get_001E2100(side, unit);

    if (card == NULL) {
        return 0;
    }
    switch (flag) {
    case 0:
        return card->bit0 ? 1 : 0;
    case 1:
        return card->bit1 ? 1 : 0;
    case 2:
        return card->bit2 ? 1 : 0;
    case 3:
        return card->bit3 ? 1 : 0;
    case 4:
        return card->bit4 ? 1 : 0;
    case 5:
        return card->bit5 ? 1 : 0;
    default:
        return 0;
    }
}

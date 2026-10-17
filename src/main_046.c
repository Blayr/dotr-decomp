#include "common.h"

/* The unit record SzDuel_SetUnitCtlGoalM writes, or NULL. */
static inline u8 *lookup_001E19D0(void) {
    extern void *SzDuel_GetCardInfo();
    u8 *entry = SzDuel_GetCardInfo();

    if (entry == NULL) {
        return NULL;
    }
    if (entry[0x45] >= 11) {
        return NULL;
    }
    return entry;
}

/* Sets unit (side, unit)'s model control goal. */
s32 SzDuel_SetUnitCtlGoalM(s32 side, s32 unit, s8 goal) {
    u8 *entry = lookup_001E19D0();

    if (entry == NULL) {
        return 0;
    }
    entry[0x51] = goal;
    return 1;
}

/* The unit record SzDuel_GetUnitCtlGoalC reads, or NULL. */
static inline u8 *get_entry_001E1A30(void) {
    extern void *SzDuel_GetCardInfo();
    u8 *entry;

    entry = SzDuel_GetCardInfo();
    if (entry == NULL) {
        return NULL;
    }
    if (entry[0x45] >= 0xB) {
        return NULL;
    }
    return entry;
}

/* A unit's card control goal, or -1. */
s32 SzDuel_GetUnitCtlGoalC(void) {
    u8 *entry;

    entry = get_entry_001E1A30();
    if (entry != NULL) {
        return entry[0x50];
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

typedef struct {
    s8 value : 2;
    s8 unused : 6;
} Flags_001E1B70;

typedef struct {
    u8 pad0[0x45];
    u8 kind;
    u8 pad46[0xC];
    s8 value52;
    u8 pad53[3];
    Flags_001E1B70 flags;
} Object_001E1B70;

/* The unit record SzDuel_SetUnitCtlRateC writes, or NULL. */
static inline void *check_001E1B70(void) {
    extern void *SzDuel_GetCardInfo();
    Object_001E1B70 *object;

    object = (Object_001E1B70 *) SzDuel_GetCardInfo();
    if (object == NULL) {
        return NULL;
    }
    if (object->kind >= 0xB) {
        return NULL;
    }
    return object;
}

/* Sets unit (side, unit)'s card control direction and speed (speed < 0 keeps it). */
s32 SzDuel_SetUnitCtlRateC(s32 side, s32 unit, s32 direction, s32 speed) {
    Object_001E1B70 *object;

    object = (Object_001E1B70 *) check_001E1B70();
    if (object == NULL) {
        return 0;
    }
    object->flags.value = (s8) (direction & 3);
    if (speed >= 0) {
        object->value52 = speed;
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
    u8 *ptr;

    ptr = SzDuel_GetCardInfo();
    if (ptr == NULL) {
        ptr = NULL;
    } else if ((s32) ptr[0x45] >= 0xB) {
        ptr = NULL;
    }
    if (ptr != NULL) {
        return ptr[0x53];
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
static inline u8 *lookup_001E1E10(void) {
    extern void *SzDuel_GetCardInfo();
    u8 *entry;

    entry = SzDuel_GetCardInfo();
    if (entry == NULL) {
        return NULL;
    }
    if (entry[0x45] >= 0xB) {
        return NULL;
    }
    return entry;
}

/* How fast a unit's card opens, or -1. */
s32 SzDuel_GetUnitOpenRate(void) {
    u8 *entry;

    entry = lookup_001E1E10();
    if (entry != NULL) {
        return entry[0x54];
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
    u8 *card = SzDuel_GetCardInfo(side, unit);

    if (card == NULL) {
        return NULL;
    }
    if (card[0x45] >= 0xB) {
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
    u8 *card = SzDuel_GetCardInfo(side, unit);

    if (card == NULL) {
        return NULL;
    }
    if (card[0x45] >= 0xB) {
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

/* Board square (x, z)'s record, or NULL off the board. */
static inline u8 *get_001E2220(s32 x, s32 z) {
    if ((x < 0) || (x >= 7) || (z < 0) || (z >= 7)) {
        return NULL;
    }
    return (x * 0x1C) + (boardSquares + (z * 0xC4));
}

/* Sets board square (x, z)'s field type. */
s32 SzDuel_SetField(s32 x, s32 z, s8 field) {
    u8 *cell;

    cell = get_001E2220(x, z);
    if (cell == NULL) {
        return 0;
    }
    cell[0x16] = field;
    return 1;
}

/* Board square (x, z)'s record, or NULL off the board. */
static inline u8 *get_001E22B0(s32 x, s32 z) {
    if ((x < 0) || (x >= 7) || (z < 0) || (z >= 7)) {
        return NULL;
    }
    return (x * 0x1C) + (boardSquares + (z * 0xC4));
}

/* Board square (x, z)'s field type, or -1 off the board. */
s32 SzDuel_GetField(s32 x, s32 z) {
    u8 *cell;

    cell = get_001E22B0(x, z);
    if (cell == NULL) {
        return -1;
    }
    return cell[0x16];
}

/* Resets every square's field-rate (its highlight) to 0. */
void SzDuel_InitFieldRate(void) {
    s32 x;
    s32 y;

    y = 0;
    do {
        x = 0;
        do {
            SzDuel_SetFieldRate(x, y, 0);
            x++;
        } while (x < 7);
        y++;
    } while (y < 7);
}

/* A board square's record, or NULL off the board. */
static inline u8 *cell_001E23A0(s32 x, s32 y) {
    if ((x < 0) || (x >= 7) || (y < 0) || (y >= 7)) {
        return NULL;
    }
    return (x * 0x1C) + (boardSquares + (y * 0xC4));
}

/* Sets board square (x, z)'s field-rate (its highlight), clamped. */
s32 SzDuel_SetFieldRate(s32 x, s32 z, s32 rate) {
    u8 *cell;

    cell = cell_001E23A0(x, z);
    if (cell == NULL) {
        return -1;
    }
    if (rate < -0x80) {
        rate = -0x80;
    }
    if (rate > 0x80) {
        rate = 0x80;
    }
    *(s16 *)(cell + 0x14) = rate;
    return rate;
}

/* A board square's record, or NULL off the board. */
static inline u8 *lookup_001E2450(s32 x, s32 y) {
    if ((x < 0) || (x >= 7) || (y < 0) || (y >= 7)) {
        return NULL;
    }
    return (x * 0x1C) + (boardSquares + (y * 0xC4));
}

/* Board square (x, z)'s field-rate (its highlight). */
s16 SzDuel_GetFieldRate(s32 x, s32 z) {
    u8 *entry;

    entry = lookup_001E2450(x, z);
    if (entry == NULL) {
        return 0;
    }
    return *(s16 *)(entry + 0x14);
}

/* A board square's record, or NULL off the board. */
static inline u8 *cell_001E24E0(s32 x, s32 y) {
    if ((x < 0) || (x >= 7) || (y < 0) || (y >= 7)) {
        return NULL;
    }
    return (x * 0x1C) + (boardSquares + (y * 0xC4));
}

/* How far a unit can still walk from square (x, y) (the move highlight), or 0xFF. */
u8 SzDuel_GetMapMovable(s32 x, s32 y) {
    u8 *cell;

    cell = cell_001E24E0(x, y);
    if (cell == NULL) {
        return 0xFFU;
    }
    return cell[0x17];
}

struct DotrStateItemBits {
    signed char unknown_bit_0 : 1;
    signed char unknown_bit_1 : 1;
    signed char unknown_bit_2 : 1;
    signed char unknown_bit_3 : 1;
    signed char unknown_bit_4 : 1;
    signed char unknown_bit_5 : 1;
    signed char unknown_bit_6 : 1;
    signed char unknown_bit_7 : 1;
};
struct DotrStateItemPairs {
    signed char unknown_bits_0_1 : 2;
    signed char unknown_bits_2_3 : 2;
    signed char unknown_bits_4_5 : 2;
    signed char unknown_bits_6_7 : 2;
};
struct DotrStateItemFlags {
    signed char unknown_bit_0 : 1;
    signed char unknown_bit_1 : 1;
    signed char unknown_bit_2 : 1;
    signed char unknown_bit_3 : 1;
    signed char unknown_bits_4_7 : 4;
};
struct DotrStateItemObject;
struct DotrStateItemSource {
    unsigned char unknown_00;
    unsigned char unknown_01;
    unsigned char unknown_02_low : 4;
    unsigned char unknown_02_high : 4;
    unsigned char unknown_03;
    unsigned short unknown_04;
    unsigned char unknown_06[2];
    unsigned short unknown_08;
    unsigned short unknown_0a;
};
struct DotrStateEntry8 {
    int unknown_words[2];
};
struct DotrStateItem {
    struct DotrStateItemSource *unknown_00;
    struct DotrStateItemObject *unknown_04; 
    struct DotrStateEntry8 unknown_08[5];
    int unknown_30;
    unsigned char unknown_34[4];
    short unknown_38;
    short unknown_3a;
    unsigned short unknown_3c;
    unsigned char unknown_3e;
    unsigned char unknown_3f;
    unsigned char unknown_40;
    unsigned char unknown_41;
    unsigned char unknown_42[2];
    unsigned char unknown_44;
    unsigned char unknown_45;
    unsigned char unknown_46;
    unsigned char unknown_47;
    unsigned char unknown_48;
    unsigned char unknown_49;
    unsigned char unknown_4a;
    unsigned char unknown_4b;
    unsigned char unknown_4c[2];
    unsigned char unknown_4e;
    unsigned char unknown_4f;
    unsigned char unknown_50;
    unsigned char unknown_51;
    unsigned char unknown_52;
    unsigned char unknown_53;
    unsigned char unknown_54;
    unsigned char unknown_55;
    struct DotrStateItemPairs unknown_56;
    struct DotrStateItemBits unknown_57;
    struct DotrStateItemFlags unknown_58;
    unsigned char unknown_59[3];
};
typedef char DotrStateItemMustBe5c[(sizeof(struct DotrStateItem) == 0x5c) ? 1 : -1];
struct DotrStateVector {
    float x, y, z;
    float unknown_w;
};
struct DotrStateCellQuad {
    unsigned char unknown_0;
    unsigned char unknown_1;
    unsigned char unknown_2;
    unsigned char unknown_3;
};
typedef int DotrStateWord;
struct DotrStateCell {
    DotrStateWord unknown_00;
    struct DotrStateCellQuad unknown_04[4];
    short unknown_14;
    unsigned char unknown_16;
    unsigned char unknown_17;
    unsigned char unknown_18;
    unsigned char unknown_19;
    unsigned char unknown_1a;
};
typedef char DotrStateCellMustBe1c[(sizeof(struct DotrStateCell) == 0x1c) ? 1 : -1];
struct DotrStateItemObject {
    struct DotrStateVector unknown_00;
    struct DotrStateVector unknown_10;
    unsigned char unknown_20[0x10];
    struct DotrStateVector unknown_30;
    struct DotrStateCellQuad unknown_40;
};
extern struct DotrStateCell D_00318E60_b[7][7];
struct DotrStateItem *func_001E36E0_b(int x, int y);
/* A board square's record, or NULL off the board. */
static inline struct DotrStateCell *cell_1e2570(int x, int y)
{
    if (x < 0 || x >= 7 || y < 0 || y >= 7) {
        return 0;
    }
    return &D_00318E60_b[y][x];
}
/* Sets a square's summon-enable mark. */
static inline void set_17(int x, int y, int value)
{
    struct DotrStateCell *c = cell_1e2570(x, y);
    if (c != 0) {
        c->unknown_17 = value;
    }
}
/* A square's walk distance. */
static inline int get_16(int x, int y)
{
    struct DotrStateCell *c = cell_1e2570(x, y);
    if (c != 0) {
        return c->unknown_16;
    }
    return -1;
}

/* Marks the squares side `side` may summon to around (cx, cy). */
void lSzDuel_CalcMapSummonEnable(int side, int cx, int cy)
{
    int x;
    int y;
    int ok;
    int n;
    struct DotrStateItem *item;

    for (y = 0; y < 7; y++) {
        for (x = 0; x < 7; x++) {
            set_17(x, y, 0xff);
        }
    }
    for (y = cy - 1; y <= cy + 1; y++) {
        for (x = cx - 1; x <= cx + 1; x++) {
            if (cx == x && cy == y) {
                continue;
            }
            item = func_001E36E0_b(x, y);
            ok = 1;
            if (get_16(x, y) == 8) {
                ok = 0;
            }
            if (item != 0) {
                n = Ta_IsUnitControl(item->unknown_44, item->unknown_45);
                if (n != side) {
                    ok = 0;
                }
            }
            if (ok) {
                set_17(x, y, 0);
            }
        }
    }
}

typedef struct {
    u8 pad[0x17];
    u8 index;
    u8 pad18[4];
} Cell_001E27D0;


/* A board square's record, or NULL off the board. */
static inline Cell_001E27D0 *cell_001E27D0(s32 x, s32 y) {
    if (x < 0 || x >= 7 || y < 0 || y >= 7) {
        return NULL;
    }
    return (Cell_001E27D0 *)(x * 0x1C + (boardSquares + y * 0xC4));
}

/* Sets a square's walk distance. */
static inline void set_001E27D0(s32 x, s32 y, s32 value) {
    Cell_001E27D0 *cell = cell_001E27D0(x, y);
    if (cell != NULL) {
        cell->index = value;
    }
}

/* A square's walk distance. */
static inline s32 get_001E27D0(s32 x, s32 y) {
    Cell_001E27D0 *cell = cell_001E27D0(x, y);
    if (cell != NULL) {
        return cell->index;
    }
    return 0xFF;
}

/* A square's record if (x, y) is on the board. */
static inline Cell_001E27D0 *checked_001E27D0(s32 x, s32 y, Cell_001E27D0 *cell) {
    if (x < 0 || x >= 7 || y < 0 || y >= 7) {
        return NULL;
    }
    return cell;
}

/* Sets a square's walk mark. */
static inline void set_walk_001E27D0(s32 x, s32 y, Cell_001E27D0 *p, s32 value) {
    Cell_001E27D0 *cell = checked_001E27D0(x, y, p);
    if (cell != NULL) {
        cell->index = value;
    }
}

/* A square's walk mark. */
static inline s32 get_walk_001E27D0(s32 x, s32 y, Cell_001E27D0 *p) {
    Cell_001E27D0 *cell = checked_001E27D0(x, y, p);
    if (cell != NULL) {
        return cell->index;
    }
    return 0xFF;
}

/* Works out where a unit of side `side` on (x, z) can walk within `limit` squares (or along the given path),
   marking each square's distance. */
void lSzDuel_CalcMapMovable(s32 pathOnly, s32 isLeader, s32 side, s32 startX, s32 z, s32 limit, s32 extra, u8 *pathX, u8 *pathZ, s32 count) {
    extern void TaLogic_DoGetShortRoot();
    u8 buffer0[0x40];
    u8 buffer1[0x40];
    s32 x;
    s32 y;
    Cell_001E27D0 *p;
    Cell_001E27D0 *row;
    s32 i;

    if (pathOnly != 0) {
        row = (Cell_001E27D0 *)boardSquares;
        y = 0;
        do {
            x = 0;
            p = row;
            do {
                set_walk_001E27D0(x, y, p, 0xFF);
                x++;
                p++;
            } while (x < 7);
            y++;
            row += 7;
        } while (y < 7);
    } else {
        Cell_001E27D0 *p;
        Cell_001E27D0 *row;
        s32 y;
        s32 x;

        row = (Cell_001E27D0 *)boardSquares;
        y = 0;
        do {
            x = 0;
            p = row;
            do {
                if (get_walk_001E27D0(x, y, p) < 0xFF) {
                    set_walk_001E27D0(x, y, p, 0xFE);
                }
                x++;
                p++;
            } while (x < 7);
            y++;
            row += 7;
        } while (y < 7);
    }
    lSzDuel_CalcMapMovableRecursive(isLeader, side, startX, z, limit, extra, pathX, pathZ, count, buffer0, buffer1, 0, 1);
    for (i = 0; i < count; i++) {
        set_001E27D0(pathX[i], pathZ[i], i);
    }
}

typedef struct Cell_001E2A60 {
    u8 pad[0x16];
    u8 terrain;
    u8 distance;
    u8 tail[4];
} Cell_001E2A60;

typedef struct Object_001E2A60 {
    u8 pad[0x44];
    u8 owner;
    u8 state;
} Object_001E2A60;

/* Whether (x, y) is on the board. */
static inline s32 valid_001E2A60(s32 x, s32 y) {
    if (x < 0 || x >= 7 || y < 0) {
        return 0;
    }
    return y < 7;
}

/* A board square's record, or NULL off the board. */
static inline Cell_001E2A60 *cell_001E2A60(s32 x, s32 y) {
    if (x < 0 || x >= 7 || y < 0 || y >= 7) {
        return NULL;
    }
    return (Cell_001E2A60 *)(x * 0x1C + (boardSquares + y * 0xC4));
}

/* A square's field type. */
static inline s32 terrain_001E2A60(s32 x, s32 y) {
    Cell_001E2A60 *cell = cell_001E2A60(x, y);
    s32 terrain;
    if (cell != NULL) {
        terrain = cell->terrain;
    } else {
        terrain = -1;
    }
    return terrain;
}

/* A square's walk distance (0xFF unreached). */
static inline s32 distance_001E2A60(s32 x, s32 y) {
    Cell_001E2A60 *cell = cell_001E2A60(x, y);
    if (cell != NULL) {
        return cell->distance;
    }
    return 0xFF;
}

/* Sets a square's walk distance. */
static inline void set_distance_001E2A60(s32 x, s32 y, s32 distance) {
    Cell_001E2A60 *cell = cell_001E2A60(x, y);
    if (cell != NULL) {
        cell->distance = distance;
    }
}

/* Whether (x, y) is on the path already. */
static inline s32 visited_001E2A60(s32 x, s32 y, u8 *pathX, u8 *pathY, s32 count) {
    s32 i;
    for (i = 0; i < count; i++) {
        if (x == pathX[i] && y == pathY[i]) {
            break;
        }
    }
    return i < count;
}

/* One step of the walk search: marks square (x, y) and tries its four neighbours. */
void lSzDuel_CalcMapMovableRecursive(s32 pathOnly, s32 isLeader, s32 side, s32 x, s32 y, s32 limit,
                   u8 *oldX, u8 *oldY, s32 oldCount, u8 *pathX, u8 *pathY,
                   s32 depth, s32 allowance) {
    Object_001E2A60 *object;
    s32 terrain;
    s32 i;
    s32 nextDepth;

    if (x < 0 || x >= 7 || y < 0 || y >= 7) {
        return;
    }
    object = (Object_001E2A60 *)SzDuel_GetMapUnit(x, y);
    terrain = terrain_001E2A60(x, y);
    if (depth > 0) {
        for (i = 0; i < oldCount; i++) {
            if (x == oldX[i] && y == oldY[i]) {
                return;
            }
        }
        if (object != NULL) {
            s32 owner = Ta_IsUnitControl(object->owner, object->state);
            if (isLeader != 0 && owner != side) {
                return;
            }
            if (object->state == 0 && object->owner == side) {
                return;
            }
        }
    }
    pathX[depth] = x;
    pathY[depth] = y;
    if (object != NULL || terrain != 8 || pathOnly != 0) {
        if (distance_001E2A60(x, y) > oldCount + depth) {
            set_distance_001E2A60(x, y, oldCount + depth);
        }
    }
    if (object != NULL || (terrain == 8 && pathOnly == 0)) {
        if (oldCount + depth > 0) {
            allowance--;
            if (allowance <= 0) {
                return;
            }
        }
    }
    nextDepth = ++depth;
    if (nextDepth > limit) {
        return;
    }
    if (!visited_001E2A60(x + 1, y, pathX, pathY, nextDepth)) {
        lSzDuel_CalcMapMovableRecursive(pathOnly, isLeader, side, x + 1, y, limit, oldX, oldY,
                      oldCount, pathX, pathY, nextDepth, allowance);
    }
    if (!visited_001E2A60(x - 1, y, pathX, pathY, nextDepth)) {
        lSzDuel_CalcMapMovableRecursive(pathOnly, isLeader, side, x - 1, y, limit, oldX, oldY,
                      oldCount, pathX, pathY, nextDepth, allowance);
    }
    if (!visited_001E2A60(x, y + 1, pathX, pathY, nextDepth)) {
        lSzDuel_CalcMapMovableRecursive(pathOnly, isLeader, side, x, y + 1, limit, oldX, oldY,
                      oldCount, pathX, pathY, nextDepth, allowance);
    }
    if (!visited_001E2A60(x, y - 1, pathX, pathY, nextDepth)) {
        lSzDuel_CalcMapMovableRecursive(pathOnly, isLeader, side, x, y - 1, limit, oldX, oldY,
                      oldCount, pathX, pathY, nextDepth, allowance);
    }
}

/* Sets every square's colour to `value` and colour `color` (redraws). */
void SzDuel_InitMapColor(s32 value, s32 color, s32 blink) {
    SzDuel_InitMapColor2(value, color, blink, 1);
}

/* Sets every square's colour to `value` and `color`, with `redraw`. */
void SzDuel_InitMapColor2(s32 value, s32 color, s32 blink, s32 redraw) {
    s32 column;
    s32 row;

    row = 0;
    do {
        column = 0;
        do {
            SzDuel_SetMapColor2(column, row, value, color, blink, redraw);
            column++;
        } while (column < 7);
        row++;
    } while (row < 7);
}

/* Sets board square (x, z)'s colour (redraws). */
void SzDuel_SetMapColor(s32 x, s32 z, s32 value, s32 color, s32 blink) {
    SzDuel_SetMapColor2(x, z, value, color, blink, 1);
}

typedef struct {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} Color_001E3070;

typedef struct {
    u8 pad[0x44];
    u8 kind;
    u8 pad45[0x12];
    s8 unused : 1;
    s8 highlighted : 1;
} Entity_001E3070;

typedef struct {
    Entity_001E3070 *entity;
    Color_001E3070 color;
    Color_001E3070 savedColor;
    Color_001E3070 glow;
    Color_001E3070 savedGlow;
    u8 pad14[4];
    s8 value;
    u8 pad19[3];
} Cell_001E3070;

extern u16 D_00318118;

/* Sets board square (x, z)'s colour value and colour; `blink` makes it pulse. */
s32 SzDuel_SetMapColor2(s32 x, s32 z, s32 colorValue, s32 newColor, s32 blink, s32 redraw) {
    Cell_001E3070 *cell;
    u8 inverse;
    u8 channel;
    s32 lit;
    s32 dim;
    Entity_001E3070 *entity;

    if (x < 0 || x >= 7 || z < 0 || z >= 7) {
        cell = NULL;
    } else {
        cell = (Cell_001E3070 *)(boardSquares + z * 0xC4 + x * 0x1C);
    }

    channel = (D_00318118 >> 8) & 0xFF;
    inverse = (0x80 - channel) & 0xFF;
    if (cell == NULL) {
        return 0;
    }

    cell->value = colorValue;
    if (newColor != 0) {
        cell->color = *(Color_001E3070 *)newColor;
    } else {
        cell->color.b = 0;
        cell->color.g = 0;
        cell->color.r = 0;
        cell->color.a = 0;
    }

    cell->glow.b = 0;
    cell->glow.g = 0;
    cell->glow.r = 0;
    cell->glow.a = 0;

    if (redraw != 0) {
        entity = cell->entity;
        if (entity != NULL) {
            if (entity->highlighted) {
                lit = (channel * 0xFF) >> 7;
                dim = (inverse * 0xFF) >> 7;
                cell->glow.b = lit + dim;
                cell->glow.g = dim;
                cell->glow.r = dim;
            } else if (entity->kind == 0) {
                cell->glow.b = 0xFF;
                cell->glow.g = 0;
                cell->glow.r = 0;
            } else {
                cell->glow.b = 0xFF;
                cell->glow.g = 0xFF;
                cell->glow.r = 0xFF;
            }
            cell->glow.a = 0x80;
        }
    }

    if (blink != 0) {
        cell->savedColor = cell->color;
        cell->savedGlow = cell->glow;
    }

    return 1;
}

/* Clamps to 0..7. */
static inline s32 clamp_001E3230(s32 value) {
    if (value < 8) {
        return value;
    }
    return 8;
}

/* A board square's record, or NULL off the board. */
static inline u8 *lookup_001E3230(s32 x, s32 y) {
    if (x < 0 || x >= 7 || y < 0 || y >= 7) {
        return NULL;
    }
    return boardSquares + y * 0xC4 + x * 0x1C;
}

/* Works out board square (x, y)'s colour from its field type, highlight and blinking. */
s32 SzDuel_CalcMapColor(s32 x, s32 y) {
    u8 *p;
    s32 step;
    u8 current;
    u8 target;

    p = lookup_001E3230(x, y);
    if (p == NULL) {
        return 0;
    }
    current = p[0x18];
    if (current != p[0x19]) {
        target = p[0xB];
        if (target != 0) {
            step = target & 0xFF;
            step = clamp_001E3230(step);
            p[0xB] -= step;
        } else {
            p[0x19] = current;
        }
        return 1;
    } else {
        current = p[0xA];
        target = p[0x6];
        if (current > target) {
            step = current - target;
            step = clamp_001E3230(step);
            p[0xA] -= step;
        } else {
            step = target - current;
            step = clamp_001E3230(step);
            p[0xA] += step;
        }
        current = p[0x9];
        target = p[0x5];
        if (current > target) {
            step = current - target;
            step = clamp_001E3230(step);
            p[0x9] -= step;
        } else {
            step = target - current;
            step = clamp_001E3230(step);
            p[0x9] += step;
        }
        current = p[0x8];
        target = p[0x4];
        if (current > target) {
            step = current - target;
            step = clamp_001E3230(step);
            p[0x8] -= step;
        } else {
            step = target - current;
            step = clamp_001E3230(step);
            p[0x8] += step;
        }
        current = p[0xB];
        target = p[0x7];
        if (current > target) {
            step = current - target;
            step = clamp_001E3230(step);
            p[0xB] -= step;
        } else {
            step = target - current;
            step = clamp_001E3230(step);
            p[0xB] += step;
        }
        current = p[0x12];
        target = p[0xE];
        if (current > target) {
            step = current - target;
            step = clamp_001E3230(step);
            p[0x12] -= step;
        } else {
            step = target - current;
            step = clamp_001E3230(step);
            p[0x12] += step;
        }
        current = p[0x11];
        target = p[0xD];
        if (current > target) {
            step = current - target;
            step = clamp_001E3230(step);
            p[0x11] -= step;
        } else {
            step = target - current;
            step = clamp_001E3230(step);
            p[0x11] += step;
        }
        current = p[0x10];
        target = p[0xC];
        if (current > target) {
            step = current - target;
            step = clamp_001E3230(step);
            p[0x10] -= step;
        } else {
            step = target - current;
            step = clamp_001E3230(step);
            p[0x10] += step;
        }
        current = p[0x13];
        target = p[0xF];
        if (current > target) {
            step = current - target;
            step = clamp_001E3230(step);
            p[0x13] -= step;
        } else {
            step = target - current;
            step = clamp_001E3230(step);
            p[0x13] += step;
        }
    }
    return 1;
}

/* A board square's record, or NULL off the board. */
static inline u8 *lookup_001E3650(s32 x, s32 y) {
    if (x < 0 || x >= 7 || y < 0 || y >= 7) {
        return NULL;
    }
    return (x * 0x1C) + (boardSquares + (y * 0xC4));
}

/* Sets board square (x, z)'s alpha. */
s32 SzDuel_SetMapAlpha(s32 x, s32 z, s8 alpha) {
    u8 *cell;

    cell = lookup_001E3650(x, z);
    if (cell == NULL) {
        return 0;
    }
    *(s8 *)(cell + 0x1A) = alpha;
    return 1;
}

/* A board square's unit pointer, or NULL off the board. */
static inline void **cell_001E36E0(s32 x, s32 y) {
    if ((x < 0) || (x >= 7) || (y < 0) || (y >= 7)) {
        return NULL;
    }
    return (void **)(boardSquares + y * 0xC4 + x * 0x1C);
}

/* The unit standing on board square (x, z), or 0. */
s32 SzDuel_GetMapUnit(s32 x, s32 z) {
    void **cell;
    void *result;

    cell = cell_001E36E0(x, z);
    if (cell == NULL) {
        return 0;
    }
    result = *cell;
    if (result == NULL) {
        return 0;
    }
    if (*(u8 *)((u8 *)result + 0x45) >= 0xB) {
        result = NULL;
    }
    return (s32)result;
}

/* A board square's unit pointer, or NULL off the board. */
static inline void **lookup_001E3790(s32 x, s32 z) {
    if ((x < 0) || (x >= 7) || (z < 0) || (z >= 7)) {
        return NULL;
    }
    return (void **)(boardSquares + (z * 0xC4) + (x * 0x1C));
}

/* The unit standing on board square (x, z) as (side << 8) | unit, or -1. */
s32 SzDuel_GetMapUnitID(s32 x, s32 z) {
    u8 unit;
    void **slot;
    void *info;

    slot = lookup_001E3790(x, z);
    if (slot == NULL) {
        return -1;
    }
    info = *slot;
    if (info == NULL) {
        return -1;
    }
    unit = *((u8 *)info + 0x45);
    if ((s32) unit >= 0xB) {
        return -1;
    }
    return (*((u8 *)info + 0x44) << 8) | unit;
}

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
    *(s8 *)0x00318144 = 0x12;
    *(s16 *)0x0031813E = slot;
    *(s16 *)0x00318132 = x;
    *(s16 *)0x00318134 = y;
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

    *(s8 *)0x00318142 = 7;
    *(s16 *)0x0031813A = 0;
    *(s16 *)0x0031812A = x;
    *(s16 *)0x0031812C = y;
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
    *(s8 *)0x00318144 = 0x17;
    *(s16 *)0x0031813E = slot;
    *(s16 *)0x00318132 = x;
    *(s16 *)0x00318134 = y;
}

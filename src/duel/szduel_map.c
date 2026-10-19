/* The duel screen, part 14 of 15: terrain, movable squares, square colours. */

#include "common.h"

/* Board square (x, z)'s record, or NULL off the board. */
static inline MapInfo *get_001E2220(s32 x, s32 z) {
    if ((x < 0) || (x >= 7) || (z < 0) || (z >= 7)) {
        return NULL;
    }
    return &boardSquares[z][x];
}

/* Sets board square (x, z)'s field type. */
s32 SzDuel_SetField(s32 x, s32 z, s8 field) {
    MapInfo *cell;

    cell = get_001E2220(x, z);
    if (cell == NULL) {
        return 0;
    }
    cell->field = field;
    return 1;
}

/* Board square (x, z)'s record, or NULL off the board. */
static inline MapInfo *get_001E22B0(s32 x, s32 z) {
    if ((x < 0) || (x >= 7) || (z < 0) || (z >= 7)) {
        return NULL;
    }
    return &boardSquares[z][x];
}

/* Board square (x, z)'s field type, or -1 off the board. */
s32 SzDuel_GetField(s32 x, s32 z) {
    MapInfo *cell;

    cell = get_001E22B0(x, z);
    if (cell == NULL) {
        return -1;
    }
    return cell->field;
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
static inline MapInfo *cell_001E23A0(s32 x, s32 y) {
    if ((x < 0) || (x >= 7) || (y < 0) || (y >= 7)) {
        return NULL;
    }
    return &boardSquares[y][x];
}

/* Sets board square (x, z)'s field-rate (its highlight), clamped. */
s32 SzDuel_SetFieldRate(s32 x, s32 z, s32 rate) {
    MapInfo *cell;

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
    cell->fieldRate = rate;
    return rate;
}

/* A board square's record, or NULL off the board. */
static inline MapInfo *lookup_001E2450(s32 x, s32 y) {
    if ((x < 0) || (x >= 7) || (y < 0) || (y >= 7)) {
        return NULL;
    }
    return &boardSquares[y][x];
}

/* Board square (x, z)'s field-rate (its highlight). */
s16 SzDuel_GetFieldRate(s32 x, s32 z) {
    MapInfo *entry;

    entry = lookup_001E2450(x, z);
    if (entry == NULL) {
        return 0;
    }
    return entry->fieldRate;
}

/* A board square's record, or NULL off the board. */
static inline MapInfo *cell_001E24E0(s32 x, s32 y) {
    if ((x < 0) || (x >= 7) || (y < 0) || (y >= 7)) {
        return NULL;
    }
    return &boardSquares[y][x];
}

/* How far a unit can still walk from square (x, y) (the move highlight), or 0xFF. */
u8 SzDuel_GetMapMovable(s32 x, s32 y) {
    MapInfo *cell;

    cell = cell_001E24E0(x, y);
    if (cell == NULL) {
        return 0xFFU;
    }
    return cell->MapMovable;
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
    return (Cell_001E27D0 *)&boardSquares[y][x];
}

/* Sets a square's walk distance. */
static inline void set_001E27D0(s32 x, s32 y, s32 value) {
    Cell_001E27D0 *cell = cell_001E27D0(x, y);
    if (cell != NULL) {
        cell->index = value;
    }
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

/* A board square's record, or NULL off the board. */
static inline Cell_001E2A60 *cell_001E2A60(s32 x, s32 y) {
    if (x < 0 || x >= 7 || y < 0 || y >= 7) {
        return NULL;
    }
    return (Cell_001E2A60 *)&boardSquares[y][x];
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
        cell = (Cell_001E3070 *)&boardSquares[z][x];
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
static inline MapInfo *lookup_001E3230(s32 x, s32 y) {
    if (x < 0 || x >= 7 || y < 0 || y >= 7) {
        return NULL;
    }
    return &boardSquares[y][x];
}

/* Works out board square (x, y)'s colour from its field type, highlight and blinking. */
s32 SzDuel_CalcMapColor(s32 x, s32 y) {
    MapInfo *p;
    s32 step;
    u8 current;
    u8 target;

    p = lookup_001E3230(x, y);
    if (p == NULL) {
        return 0;
    }
    current = p->TargetSelectionHighlight;
    if (current != p->SelectionHighlightType) {
        target = p->Highlight.a;
        if (target != 0) {
            step = target & 0xFF;
            step = clamp_001E3230(step);
            p->Highlight.a -= step;
        } else {
            p->SelectionHighlightType = current;
        }
        return 1;
    } else {
        current = p->Highlight.b;
        target = p->TargetHighlight.b;
        if (current > target) {
            step = current - target;
            step = clamp_001E3230(step);
            p->Highlight.b -= step;
        } else {
            step = target - current;
            step = clamp_001E3230(step);
            p->Highlight.b += step;
        }
        current = p->Highlight.g;
        target = p->TargetHighlight.g;
        if (current > target) {
            step = current - target;
            step = clamp_001E3230(step);
            p->Highlight.g -= step;
        } else {
            step = target - current;
            step = clamp_001E3230(step);
            p->Highlight.g += step;
        }
        current = p->Highlight.r;
        target = p->TargetHighlight.r;
        if (current > target) {
            step = current - target;
            step = clamp_001E3230(step);
            p->Highlight.r -= step;
        } else {
            step = target - current;
            step = clamp_001E3230(step);
            p->Highlight.r += step;
        }
        current = p->Highlight.a;
        target = p->TargetHighlight.a;
        if (current > target) {
            step = current - target;
            step = clamp_001E3230(step);
            p->Highlight.a -= step;
        } else {
            step = target - current;
            step = clamp_001E3230(step);
            p->Highlight.a += step;
        }
        current = p->BorderOutline.b;
        target = p->TargetBorderOutline.b;
        if (current > target) {
            step = current - target;
            step = clamp_001E3230(step);
            p->BorderOutline.b -= step;
        } else {
            step = target - current;
            step = clamp_001E3230(step);
            p->BorderOutline.b += step;
        }
        current = p->BorderOutline.g;
        target = p->TargetBorderOutline.g;
        if (current > target) {
            step = current - target;
            step = clamp_001E3230(step);
            p->BorderOutline.g -= step;
        } else {
            step = target - current;
            step = clamp_001E3230(step);
            p->BorderOutline.g += step;
        }
        current = p->BorderOutline.r;
        target = p->TargetBorderOutline.r;
        if (current > target) {
            step = current - target;
            step = clamp_001E3230(step);
            p->BorderOutline.r -= step;
        } else {
            step = target - current;
            step = clamp_001E3230(step);
            p->BorderOutline.r += step;
        }
        current = p->BorderOutline.a;
        target = p->TargetBorderOutline.a;
        if (current > target) {
            step = current - target;
            step = clamp_001E3230(step);
            p->BorderOutline.a -= step;
        } else {
            step = target - current;
            step = clamp_001E3230(step);
            p->BorderOutline.a += step;
        }
    }
    return 1;
}

/* A board square's record, or NULL off the board. */
static inline MapInfo *lookup_001E3650(s32 x, s32 y) {
    if (x < 0 || x >= 7 || y < 0 || y >= 7) {
        return NULL;
    }
    return &boardSquares[y][x];
}

/* Sets board square (x, z)'s alpha. */
s32 SzDuel_SetMapAlpha(s32 x, s32 z, s8 alpha) {
    MapInfo *cell;

    cell = lookup_001E3650(x, z);
    if (cell == NULL) {
        return 0;
    }
    cell->mapAlpha = alpha;
    return 1;
}

/* A board square's unit pointer, or NULL off the board. */
static inline void **cell_001E36E0(s32 x, s32 y) {
    if ((x < 0) || (x >= 7) || (y < 0) || (y >= 7)) {
        return NULL;
    }
    return (void **)&boardSquares[y][x];
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
    return (void **)&boardSquares[z][x];
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

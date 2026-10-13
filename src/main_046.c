#include "common.h"

static inline u8 *lookup_001E19D0(void) {
    extern void *func_001DD130();
    u8 *entry = func_001DD130();

    if (entry == NULL) {
        return NULL;
    }
    if (entry[0x45] >= 11) {
        return NULL;
    }
    return entry;
}

s32 func_001E19D0(s32 arg0, s32 arg1, s8 arg2) {
    u8 *entry = lookup_001E19D0();

    if (entry == NULL) {
        return 0;
    }
    entry[0x51] = arg2;
    return 1;
}

static inline u8 *get_entry_001E1A30(void) {
    extern void *func_001DD130();
    u8 *entry;

    entry = func_001DD130();
    if (entry == NULL) {
        return NULL;
    }
    if (entry[0x45] >= 0xB) {
        return NULL;
    }
    return entry;
}

s32 func_001E1A30(void) {
    u8 *entry;

    entry = get_entry_001E1A30();
    if (entry != NULL) {
        return entry[0x50];
    }
    return -1;
}

static inline void *check_001E1A90(void *p) {
    if (p == NULL) {
        return NULL;
    }
    if (((u8 *)p)[0x45] >= 11) {
        return NULL;
    }
    return p;
}

s32 func_001E1A90(void) {
    extern void *func_001DD130();
    u8 *p;

    p = check_001E1A90(func_001DD130());
    if (p != NULL) {
        return p[0x51];
    }
    return -1;
}

s32 func_001E1AF0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 var_s0;

    var_s0 = 0;
    if (func_001E1B70(arg0, arg1, arg2, arg3) != 0) {
        if (func_001E1C10(arg0, arg1, arg2, arg3) != 0) {
            var_s0 = 1;
        }
    }
    return var_s0;
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

static inline void *check_001E1B70(void) {
    extern void *func_001DD130();
    Object_001E1B70 *object;

    object = (Object_001E1B70 *) func_001DD130();
    if (object == NULL) {
        return NULL;
    }
    if (object->kind >= 0xB) {
        return NULL;
    }
    return object;
}

s32 func_001E1B70(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    Object_001E1B70 *object;

    object = (Object_001E1B70 *) check_001E1B70();
    if (object == NULL) {
        return 0;
    }
    object->flags.value = (s8) (arg2 & 3);
    if (arg3 >= 0) {
        object->value52 = arg3;
    }
    return 1;
}

typedef struct Flags_001E1C10 {
    s8 unused0 : 2;
    s8 direction : 2;
    s8 unused1 : 4;
} Flags_001E1C10;

static inline void *check_001E1C10(void *p) {
    if (p == NULL) {
        return NULL;
    }
    if (*(u8 *)((u8 *)p + 0x45) >= 0xB) {
        return NULL;
    }
    return p;
}

s32 func_001E1C10(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    extern void *func_001DD130();
    void *var_v0;

    var_v0 = check_001E1C10(func_001DD130());
    if (var_v0 == NULL) {
        return 0;
    }
    ((Flags_001E1C10 *)((u8 *)var_v0 + 0x56))->direction = arg2 & 3;
    if (arg3 >= 0) {
        *(s8 *)((u8 *)var_v0 + 0x53) = arg3;
    }
    return 1;
}

static inline void *get_entry_001E1CB0(void) {
    extern void *func_001DD130();
    void *entry;

    entry = func_001DD130();
    if (entry == NULL) {
        return NULL;
    }
    if (*(u8 *)((u8 *)entry + 0x45) >= 0xB) {
        return NULL;
    }
    return entry;
}

s32 func_001E1CB0(void) {
    void *entry;

    entry = get_entry_001E1CB0();
    if (entry != NULL) {
        return *(u8 *)((u8 *)entry + 0x52);
    }
    return -1;
}

s32 func_001E1D10(void) {
    extern void *func_001DD130();
    u8 *ptr;

    ptr = func_001DD130();
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

s32 func_001E1D70(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    extern void *func_001DD130();
    State_001E1D70 *state;

    state = func_001DD130();
    if (state == NULL) {
        state = NULL;
    } else if (state->kind >= 11) {
        state = NULL;
    }
    if (state == NULL) {
        return 0;
    }
    state->flags.mode = arg2 & 3;
    if (arg3 >= 0) {
        state->value = arg3;
    }
    return 1;
}

static inline u8 *lookup_001E1E10(void) {
    extern void *func_001DD130();
    u8 *entry;

    entry = func_001DD130();
    if (entry == NULL) {
        return NULL;
    }
    if (entry[0x45] >= 0xB) {
        return NULL;
    }
    return entry;
}

s32 func_001E1E10(void) {
    u8 *entry;

    entry = lookup_001E1E10();
    if (entry != NULL) {
        return entry[0x54];
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/main_046", func_001E1E70);

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

static inline void *get_001E2100(s32 arg0, s32 arg1) {
    u8 *card = func_001DD130(arg0, arg1);

    if (card == NULL) {
        return NULL;
    }
    if (card[0x45] >= 0xB) {
        return NULL;
    }
    return card;
}

s32 func_001E2100(s32 arg0, s32 arg1, s32 arg2) {
    Flags_001E2100 *card = get_001E2100(arg0, arg1);

    if (card == NULL) {
        return 0;
    }
    switch (arg2) {
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

static inline u8 *get_001E2220(s32 arg0, s32 arg1) {
    if ((arg0 < 0) || (arg0 >= 7) || (arg1 < 0) || (arg1 >= 7)) {
        return NULL;
    }
    return (arg0 * 0x1C) + (D_00318E60 + (arg1 * 0xC4));
}

s32 func_001E2220(s32 arg0, s32 arg1, s8 arg2) {
    u8 *var_v0;

    var_v0 = get_001E2220(arg0, arg1);
    if (var_v0 == NULL) {
        return 0;
    }
    var_v0[0x16] = arg2;
    return 1;
}

static inline u8 *get_001E22B0(s32 arg0, s32 arg1) {
    if ((arg0 < 0) || (arg0 >= 7) || (arg1 < 0) || (arg1 >= 7)) {
        return NULL;
    }
    return (arg0 * 0x1C) + (D_00318E60 + (arg1 * 0xC4));
}

s32 func_001E22B0(s32 arg0, s32 arg1) {
    u8 *var_v0;

    var_v0 = get_001E22B0(arg0, arg1);
    if (var_v0 == NULL) {
        return -1;
    }
    return var_v0[0x16];
}

void func_001E2340(void) {
    s32 x;
    s32 y;

    y = 0;
    do {
        x = 0;
        do {
            func_001E23A0(x, y, 0);
            x++;
        } while (x < 7);
        y++;
    } while (y < 7);
}

static inline u8 *cell_001E23A0(s32 x, s32 y) {
    if ((x < 0) || (x >= 7) || (y < 0) || (y >= 7)) {
        return NULL;
    }
    return (x * 0x1C) + (D_00318E60 + (y * 0xC4));
}

s32 func_001E23A0(s32 arg0, s32 arg1, s32 arg2) {
    u8 *cell;

    cell = cell_001E23A0(arg0, arg1);
    if (cell == NULL) {
        return -1;
    }
    if (arg2 < -0x80) {
        arg2 = -0x80;
    }
    if (arg2 > 0x80) {
        arg2 = 0x80;
    }
    *(s16 *)(cell + 0x14) = arg2;
    return arg2;
}

static inline u8 *lookup_001E2450(s32 x, s32 y) {
    if ((x < 0) || (x >= 7) || (y < 0) || (y >= 7)) {
        return NULL;
    }
    return (x * 0x1C) + (D_00318E60 + (y * 0xC4));
}

s16 func_001E2450(s32 arg0, s32 arg1) {
    u8 *entry;

    entry = lookup_001E2450(arg0, arg1);
    if (entry == NULL) {
        return 0;
    }
    return *(s16 *)(entry + 0x14);
}

static inline u8 *cell_001E24E0(s32 x, s32 y) {
    if ((x < 0) || (x >= 7) || (y < 0) || (y >= 7)) {
        return NULL;
    }
    return (x * 0x1C) + (D_00318E60 + (y * 0xC4));
}

u8 func_001E24E0(s32 x, s32 y) {
    u8 *cell;

    cell = cell_001E24E0(x, y);
    if (cell == NULL) {
        return 0xFFU;
    }
    return cell[0x17];
}

INCLUDE_ASM("asm/nonmatchings/main_046", func_001E2570);

typedef struct {
    u8 pad[0x17];
    u8 index;
    u8 pad18[4];
} Cell_001E27D0;

extern s32 func_001E2A60(s32, s32, s32, s32, s32, s32, u8 *, u8 *, s32, void *, void *, s32, s32);

static inline Cell_001E27D0 *cell_001E27D0(s32 x, s32 y) {
    if (x < 0 || x >= 7 || y < 0 || y >= 7) {
        return NULL;
    }
    return (Cell_001E27D0 *)(x * 0x1C + (D_00318E60 + y * 0xC4));
}

static inline void set_001E27D0(s32 x, s32 y, s32 value) {
    Cell_001E27D0 *cell = cell_001E27D0(x, y);
    if (cell != NULL) {
        cell->index = value;
    }
}

static inline s32 get_001E27D0(s32 x, s32 y) {
    Cell_001E27D0 *cell = cell_001E27D0(x, y);
    if (cell != NULL) {
        return cell->index;
    }
    return 0xFF;
}

static inline Cell_001E27D0 *checked_001E27D0(s32 x, s32 y, Cell_001E27D0 *cell) {
    if (x < 0 || x >= 7 || y < 0 || y >= 7) {
        return NULL;
    }
    return cell;
}

static inline void set_walk_001E27D0(s32 x, s32 y, Cell_001E27D0 *p, s32 value) {
    Cell_001E27D0 *cell = checked_001E27D0(x, y, p);
    if (cell != NULL) {
        cell->index = value;
    }
}

static inline s32 get_walk_001E27D0(s32 x, s32 y, Cell_001E27D0 *p) {
    Cell_001E27D0 *cell = checked_001E27D0(x, y, p);
    if (cell != NULL) {
        return cell->index;
    }
    return 0xFF;
}

void func_001E27D0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, u8 *arg7, u8 *arg8, s32 count) {
    extern void func_0027ACB0();
    u8 buffer0[0x40];
    u8 buffer1[0x40];
    s32 x;
    s32 y;
    Cell_001E27D0 *p;
    Cell_001E27D0 *row;
    s32 i;

    if (arg0 != 0) {
        row = (Cell_001E27D0 *)D_00318E60;
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

        row = (Cell_001E27D0 *)D_00318E60;
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
    func_001E2A60(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, count, buffer0, buffer1, 0, 1);
    for (i = 0; i < count; i++) {
        set_001E27D0(arg7[i], arg8[i], i);
    }
}

INCLUDE_ASM("asm/nonmatchings/main_046", func_001E2A60);

void func_001E2FB0(s32 arg0, s32 arg1, s32 arg2) {
    func_001E2FC0(arg0, arg1, arg2, 1);
}

void func_001E2FC0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 column;
    s32 row;

    row = 0;
    do {
        column = 0;
        do {
            func_001E3070(column, row, arg0, arg1, arg2, arg3);
            column++;
        } while (column < 7);
        row++;
    } while (row < 7);
}

void func_001E3060(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_001E3070(arg0, arg1, arg2, arg3, arg4, 1);
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

s32 func_001E3070(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    Cell_001E3070 *cell;
    u8 inverse;
    u8 channel;
    s32 lit;
    s32 dim;
    Entity_001E3070 *entity;

    if (arg0 < 0 || arg0 >= 7 || arg1 < 0 || arg1 >= 7) {
        cell = NULL;
    } else {
        cell = (Cell_001E3070 *)(D_00318E60 + arg1 * 0xC4 + arg0 * 0x1C);
    }

    channel = (D_00318118 >> 8) & 0xFF;
    inverse = (0x80 - channel) & 0xFF;
    if (cell == NULL) {
        return 0;
    }

    cell->value = arg2;
    if (arg3 != 0) {
        cell->color = *(Color_001E3070 *)arg3;
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

    if (arg5 != 0) {
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

    if (arg4 != 0) {
        cell->savedColor = cell->color;
        cell->savedGlow = cell->glow;
    }

    return 1;
}

static inline s32 clamp_001E3230(s32 value) {
    if (value < 8) {
        return value;
    }
    return 8;
}

static inline u8 *lookup_001E3230(s32 x, s32 y) {
    if (x < 0 || x >= 7 || y < 0 || y >= 7) {
        return NULL;
    }
    return D_00318E60 + y * 0xC4 + x * 0x1C;
}

s32 func_001E3230(s32 x, s32 y) {
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

static inline u8 *lookup_001E3650(s32 x, s32 y) {
    if (x < 0 || x >= 7 || y < 0 || y >= 7) {
        return NULL;
    }
    return (x * 0x1C) + (D_00318E60 + (y * 0xC4));
}

s32 func_001E3650(s32 arg0, s32 arg1, s8 arg2) {
    u8 *var_v0;

    var_v0 = lookup_001E3650(arg0, arg1);
    if (var_v0 == NULL) {
        return 0;
    }
    *(s8 *)(var_v0 + 0x1A) = arg2;
    return 1;
}

static inline void **cell_001E36E0(s32 x, s32 y) {
    if ((x < 0) || (x >= 7) || (y < 0) || (y >= 7)) {
        return NULL;
    }
    return (void **)(D_00318E60 + y * 0xC4 + x * 0x1C);
}

s32 func_001E36E0(s32 arg0, s32 arg1) {
    void **cell;
    void *result;

    cell = cell_001E36E0(arg0, arg1);
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

static inline void **lookup_001E3790(s32 arg0, s32 arg1) {
    if ((arg0 < 0) || (arg0 >= 7) || (arg1 < 0) || (arg1 >= 7)) {
        return NULL;
    }
    return (void **)(D_00318E60 + (arg1 * 0xC4) + (arg0 * 0x1C));
}

s32 func_001E3790(s32 arg0, s32 arg1) {
    u8 temp_v1;
    void **var_v0;
    void *temp_a0;

    var_v0 = lookup_001E3790(arg0, arg1);
    if (var_v0 == NULL) {
        return -1;
    }
    temp_a0 = *var_v0;
    if (temp_a0 == NULL) {
        return -1;
    }
    temp_v1 = *((u8 *)temp_a0 + 0x45);
    if ((s32) temp_v1 >= 0xB) {
        return -1;
    }
    return (*((u8 *)temp_a0 + 0x44) << 8) | temp_v1;
}

typedef struct Flags_001E3850 {
    u8 padding0[0x57];
    s8 reserved57 : 7;
    s8 flag57 : 1;
    s8 flag58 : 1;
    s8 reserved58 : 7;
} Flags_001E3850;

static inline void *get_001E3850(void) {
    extern void *func_001DD130();
    u8 *card = func_001DD130();

    if (card == NULL) {
        return NULL;
    }
    if (card[0x45] >= 0xB) {
        return NULL;
    }
    return card;
}

s32 func_001E3850(s32 arg0, s32 arg1, s32 arg2) {
    u8 *card = get_001E3850();

    if (card == NULL) {
        return 0;
    }
    ((Flags_001E3850 *)card)->flag57 = (s8) (arg2 ? 1 : 0);
    ((Flags_001E3850 *)card)->flag58 = (s8) (arg2 ? 1 : 0);
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

static inline void *get_001E3900(void) {
    extern void *func_001DD130();
    Entry_001E3900 *entry = func_001DD130();
    if (entry == NULL) {
        return NULL;
    }
    if (entry->kind >= 0xB) {
        return NULL;
    }
    return entry;
}

s32 func_001E3900(s32 arg0, s32 arg1, s32 arg2) {
    Entry_001E3900 *entry = get_001E3900();
    if (entry == NULL) {
        return 0;
    }
    entry->flags.enabled = (s8)((arg2 != 0) ? 1 : 0);
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

static inline void *check_001E3990(void) {
    extern void *func_001DD130();
    Object_001E3990 *object = func_001DD130();

    if (object == NULL) {
        return NULL;
    }
    if (object->type >= 11) {
        return NULL;
    }
    return object;
}

s32 func_001E3990(s32 arg0, s32 arg1, s32 arg2) {
    Object_001E3990 *object = check_001E3990();

    if (object == NULL) {
        return 0;
    }
    object->enabled = arg2 ? 1 : 0;
    return 1;
}

struct ObjectFields_001E3A20 {
    u8 pad0[0x45];
    u8 kind;
    u8 pad1[0x12];
    s8 enabled : 1;
    s8 : 7;
};

s32 func_001E3A20(s32 arg0, s32 arg1, s32 arg2) {
    extern void *func_001DD130();
    struct ObjectFields_001E3A20 *object = func_001DD130();

    if (object == NULL) {
        object = NULL;
    } else if (object->kind >= 11) {
        object = NULL;
    }

    if (object == NULL) {
        return 0;
    }
    object->enabled = (s8)(arg2 ? 1 : 0);
    return 1;
}

typedef struct Vec4_001E3AB0 {
    f32 x, y, z, w;
} Vec4_001E3AB0;

static inline void *get_001E3AB0(void) {
    extern void *func_001DD130();
    void *entry = func_001DD130();

    if (entry == NULL) {
        return NULL;
    }
    if (*(u8 *)((u8 *)entry + 0x45) >= 11) {
        return NULL;
    }
    return entry;
}

s32 func_001E3AB0(s32 arg0, s32 arg1, s32 arg2) {
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
    if (arg2 != 0) {
        *data = *(Vec4_001E3AB0 *)arg2;
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

static inline void *get_001E3B50(void) {
    extern void *func_001DD130();
    void *object = func_001DD130();

    if (object == NULL) {
        return NULL;
    }
    if (((Object_001E3B50 *)object)->kind >= 11) {
        return NULL;
    }
    return object;
}

s32 func_001E3B50(s32 arg0, s32 arg1, void *arg2) {
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
    if (arg2 != NULL) {
        *(Vec4_001E3B50 *)arg2 = *position;
    }
    return 1;
}

typedef struct Vec4_001E3BF0 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4_001E3BF0;

static inline void *lookup_001E3BF0(void) {
    extern void *func_001DD130();
    void *object;

    object = func_001DD130();
    if (object == NULL) {
        return NULL;
    }
    if (*(u8 *)((u8 *)object + 0x45) >= 0xB) {
        return NULL;
    }
    return object;
}

s32 func_001E3BF0(s32 arg0, s32 arg1, s32 arg2) {
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
    if (arg2 != 0) {
        *(Vec4_001E3BF0 *)((u8 *)temp_v0 + 0x10) = *(Vec4_001E3BF0 *)arg2;
    }
    return 1;
}

typedef struct Vec4_001E3C90 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4_001E3C90;

static inline void *lookup_001E3C90(void) {
    extern void *func_001DD130();
    void *object = func_001DD130();

    if (object == NULL) {
        return NULL;
    }
    if (((u8 *)object)[0x45] >= 0xB) {
        return NULL;
    }
    return object;
}

s32 func_001E3C90(s32 arg0, s32 arg1, void *arg2) {
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
    if (arg2 != NULL) {
        *(Vec4_001E3C90 *)arg2 = *(Vec4_001E3C90 *)((u8 *)temp_v0 + 0x10);
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

static inline void *check_001E3D30(void) {
    extern void *func_001DD130();
    Entry_001E3D30 *entry = func_001DD130();

    if (entry == NULL) {
        return NULL;
    }
    if (entry->type >= 11) {
        return NULL;
    }
    return entry;
}

s32 func_001E3D30(s32 arg0, s32 arg1, s32 arg2) {
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
    if (arg2 != 0) {
        object->position = *(Vec4_001E3D30 *)arg2;
    }
    return 1;
}

typedef struct Vec4_001E3DD0 {
    f32 x, y, z, w;
} Vec4_001E3DD0;

static inline void *get_001E3DD0(void) {
    extern void *func_001DD130();
    void *object = func_001DD130();

    if (object == NULL) {
        return NULL;
    }
    if (*(u8 *)((u8 *)object + 0x45) >= 11) {
        return NULL;
    }
    return object;
}

s32 func_001E3DD0(s32 arg0, s32 arg1, void *arg2) {
    void *object = get_001E3DD0();
    void *data;

    if (object == NULL) {
        return 0;
    }
    data = *(void **)((u8 *)object + 4);
    if (data == NULL) {
        return 0;
    }
    if (arg2 != NULL) {
        *(Vec4_001E3DD0 *)arg2 = *(Vec4_001E3DD0 *)((u8 *)data + 0x30);
    }
    return 1;
}

typedef struct {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} Color_001E3E70;

static inline void *lookup_001E3E70(void) {
    extern void *func_001DD130();
    void *object = func_001DD130();

    if (object == NULL) {
        return NULL;
    }
    if (*(u8 *)((u8 *)object + 0x45) >= 0xB) {
        return NULL;
    }
    return object;
}

s32 func_001E3E70(s32 arg0, s32 arg1, s32 arg2) {
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
    if (arg2 != 0) {
        *(Color_001E3E70 *)((u8 *)data + 0x40) = *(Color_001E3E70 *)arg2;
    }
    return 1;
}

typedef struct Color_001E3F10 {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} Color_001E3F10;

static inline void *get_001E3F10(void) {
    extern void *func_001DD130();
    void *object = func_001DD130();

    if (object == NULL) {
        return NULL;
    }
    if (*(u8 *)((u8 *)object + 0x45) >= 0xB) {
        return NULL;
    }
    return object;
}

s32 func_001E3F10(s32 arg0, s32 arg1, void *arg2) {
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
    if (arg2 != NULL) {
        *(Color_001E3F10 *)arg2 = *(Color_001E3F10 *)((u8 *)data + 0x40);
    }
    return 1;
}

void func_001E3FB0(s32 arg0, s32 arg1, s32 arg2) {
    *(s8 *)0x00318144 = 0x12;
    *(s16 *)0x0031813E = arg0;
    *(s16 *)0x00318132 = arg1;
    *(s16 *)0x00318134 = arg2;
}

void func_001E3FE0(void) {
    D_00318144 = 0x18;
}

void func_001E3FF0(s32 arg0, s16 arg1, s16 arg2) {
    u8 *state = D_00317490;
    s32 i;
    s32 bit;

    *(s8 *)0x00318142 = 7;
    *(s16 *)0x0031813A = 0;
    *(s16 *)0x0031812A = arg1;
    *(s16 *)0x0031812C = arg2;
    if (arg0 >= 0) {
        state[0xD54] = arg0;
        state[0xD35] = 0;
        state[0xD36] = 0;
        i = 0;
        do {
            if (func_00214D00(0, i) != 0) {
                bit = 1;
            } else {
                bit = 0;
            }
            state[0xD36] |= bit << i;
            i++;
        } while (i < 3);
    }
}

s32 func_001E40A0(s32 arg0) {
    u8 *base;
    s32 var_s1;
    s32 temp_s1;
    s32 temp_s1_2;

    base = D_00317490;
    if (func_00203A40(arg0, 2, 0x5000) != 0) {
        temp_s1 = base[0xD35];
        if (func_00203A40(arg0, 2, 0x1000) != 0) {
            base[0xD35] = (base[0xD35] + 1) % 2;
        } else {
            base[0xD35] = (base[0xD35] + 3) % 2;
        }
        if (base[0xD35] != temp_s1) {
            func_00217710(0, 3);
        }
        return 0;
    }
    if (func_00203A40(arg0, 0, 0xA000) != 0) {
        temp_s1_2 = base[0xD36];
        if (func_00203A40(arg0, 0, 0x8000) != 0) {
            base[0xD36] = base[0xD36] | (1 << (base[0xD35] + 1));
        } else {
            base[0xD36] = base[0xD36] & ~(1 << (base[0xD35] + 1));
        }
        if (base[0xD36] != temp_s1_2) {
            func_00217710(0, 3);
        }
        return 0;
    }
    if (func_00203A40(arg0, 0, 0xC0) != 0) {
        var_s1 = 0;
        do {
            func_00214BB0(0, var_s1, base[0xD36] & (1 << var_s1));
            func_00214BB0(1, var_s1, base[0xD36] & (1 << var_s1));
            var_s1 += 1;
        } while (var_s1 < 3);
        func_00217710(0, 4);
        return 1;
    }
    if (func_00203A40(arg0, 0, 0x20) != 0) {
        func_00217710(0, 5);
        return 2;
    }
    return 0;
}

void func_001E42B0(void) {
    D_00318142 = 0x18;
}

INCLUDE_ASM("asm/nonmatchings/main_046", func_001E42C0);

s32 func_001E4430(s32 arg0) {
    u8 *state = D_00317490;
    s32 temp_s1;

    if (func_00203A40(arg0, 0, 0xA000) != 0) {
        temp_s1 = state[0xD35];
        if (func_00203A40(arg0, 0, 0x8000) != 0) {
            state[0xD35] = 1;
        } else {
            state[0xD35] = 0;
        }
        if (state[0xD35] != temp_s1) {
            func_00217710(0, 3);
        }
        return 0;
    }
    if (func_00203A40(arg0, 0, 0xC0) != 0) {
        func_00217710(0, 4);
        return state[0xD35] ? 1 : 2;
    }
    if (func_00203A40(arg0, 0, 0x20) != 0) {
        func_00217710(0, 5);
        return 2;
    }
    return 0;
}

void func_001E4530(void) {
    D_00318145 = 0x18;
}

void func_001E4540(s32 arg0, s32 arg1, s32 arg2) {
    *(s8 *)0x00318144 = 0x17;
    *(s16 *)0x0031813E = arg0;
    *(s16 *)0x00318132 = arg1;
    *(s16 *)0x00318134 = arg2;
}

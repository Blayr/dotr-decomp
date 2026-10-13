#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_045", func_001DF540);

void func_001DF580(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u8 buffer[0x60];

    func_001DCD70(buffer, arg3);
    func_001DF5F0(arg0, arg1, arg2, buffer, arg4);
}

INCLUDE_ASM("asm/nonmatchings/main_045", func_001DF5F0);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001DFAF0);

void *func_001DD130();
void func_001CD560();

static inline u8 *check_001DFBB0(s32 a0, s32 a1) {
    u8 *p = func_001DD130(a0, a1);
    if (p == NULL) {
        return NULL;
    }
    if (p[0x45] >= 0xB) {
        return NULL;
    }
    return p;
}

static inline s32 release_001DFBB0(void *p) {
    if (p == NULL) {
        return 0;
    }
    func_001CD560(p);
    *(s32 *)((u8 *)p + 0x90) = 0;
    return 1;
}

static inline u8 *cell_001DFBB0(s32 x, s32 y) {
    if ((x < 0) || (x >= 7) || (y < 0) || (y >= 7)) {
        return NULL;
    }
    return (x * 0x1C) + (D_00318E60 + (y * 0xC4));
}

static inline u8 *slot_001DFBB0(s32 i) {
    if (i < 0 || i >= 6) {
        return NULL;
    }
    return &D_0031A7C0[i * 0xA0];
}

s32 func_001DFBB0(s32 arg0, s32 arg1) {
    u8 *obj;
    u8 *slot;

    obj = check_001DFBB0(arg0, arg1);
    if (obj == NULL) {
        return 0;
    }
    if (arg0 < 2) {
        if (obj[0x45] < 6) {
            func_001E7E70(obj[0x46], -1, 0x3E7);
        }
        if (*(void **)(obj + 4) != NULL) {
            release_001DFBB0(*(void **)(obj + 4));
        }
        *(s32 *)cell_001DFBB0(obj[0x40], obj[0x41]) = 0;
    } else if (arg1 > 0) {
        slot = slot_001DFBB0(arg1);
        if (slot != NULL) {
            if (*(void **)slot != NULL) {
                release_001DFBB0(*(void **)slot);
            }
            func_001CDD90(slot);
        }
    }
    func_001DCD70(obj, -1);
    return 1;
}

typedef struct Vec4_001DFD50 {
    f32 x, y, z, w;
} Vec4_001DFD50;

typedef struct Object_001DFD50 {
    Vec4_001DFD50 position;
    u8 pad10[0x80];
    s32 active;
} Object_001DFD50;

typedef struct Piece_001DFD50 {
    u8 pad00[4];
    Object_001DFD50 *object;
    u8 pad08[0x2C];
    s16 field34;
    s16 field36;
    u8 pad38[8];
    u8 x;
    u8 y;
    u8 pad42[2];
    u8 player;
    u8 index;
    u8 handle;
} Piece_001DFD50;

typedef struct Cell_001DFD50 {
    Piece_001DFD50 *piece;
    u8 pad04[0x18];
} Cell_001DFD50;

typedef struct Entry_001DFD50 {
    Object_001DFD50 *object;
    u8 pad04[0x9C];
} Entry_001DFD50;

static inline void remove_object_001DFD50(Object_001DFD50 *object) {
    extern void func_001CD560();

    if (object != NULL) {
        func_001CD560(object);
        object->active = 0;
    }
}

void *func_001DFD50(s32 arg0, s32 arg1, s32 x, s32 y) {
    extern void *func_001DD130();
    Piece_001DFD50 *piece;
    Cell_001DFD50 *destination;
    Piece_001DFD50 *occupied;
    s32 index;
    s32 player;
    Cell_001DFD50 *source;
    Object_001DFD50 *object;
    Entry_001DFD50 *entry;
    Object_001DFD50 *entryObject;
    Piece_001DFD50 *found;
    Cell_001DFD50 *removed;
    s32 oldX;
    s32 oldY;
    s32 removedX;
    s32 removedY;
    Vec4_001DFD50 position;

    found = func_001DD130(arg0, arg1);
    if (found == NULL) {
        piece = NULL;
    } else if (found->index >= 11) {
        piece = NULL;
    } else {
        piece = found;
    }
    if (piece == NULL) {
        return NULL;
    }
    oldX = piece->x;
    if (oldX == x && piece->y == y) {
        return NULL;
    }
    destination = NULL;
    if (x < 0 || x >= 7 || y < 0 || y >= 7) {
        destination = NULL;
    } else {
        destination = (Cell_001DFD50 *)(x * 0x1C + (D_00318E60 + y * 0xC4));
    }
    oldY = piece->y;
    source = NULL;
    if (oldX < 0 || oldX >= 7 || oldY < 0 || oldY >= 7) {
        source = NULL;
    } else {
        source = (Cell_001DFD50 *)(oldX * 0x1C + (D_00318E60 + oldY * 0xC4));
    }
    if (destination == NULL || source == NULL) {
        return NULL;
    }
    if (destination->piece != NULL) {
        index = destination->piece->index;
        player = destination->piece->player;
        found = func_001DD130(player, index);
        if (found == NULL) {
            occupied = NULL;
        } else if (found->index >= 11) {
            occupied = NULL;
        } else {
            occupied = found;
        }
        if (occupied != NULL) {
            if (player < 2) {
                if (occupied->index < 6) {
                    func_001E7E70(occupied->handle, -1, 999);
                }
                object = occupied->object;
                if (object != NULL) {
                    remove_object_001DFD50(object);
                }
                removedX = occupied->x;
                removedY = occupied->y;
                if (removedX < 0 || removedX >= 7 || removedY < 0 || removedY >= 7) {
                    removed = NULL;
                } else {
                    removed = (Cell_001DFD50 *)(removedX * 0x1C + (D_00318E60 + removedY * 0xC4));
                }
                removed->piece = NULL;
            } else if (index > 0) {
                if (index < 0 || index >= 6) {
                    entry = NULL;
                } else {
                    entry = (Entry_001DFD50 *)(D_0031A7C0 + index * 0xA0);
                }

                if (entry != NULL) {
                    entryObject = entry->object;

                    if (entryObject != NULL) {
                        remove_object_001DFD50(entryObject);
                    }
                    func_001CDD90((u8 *)entry);
                }
            }
            func_001DCD70(occupied, -1);
        }
    }
    piece->x = x;
    piece->y = y;
    piece->field34 = 0;
    piece->field36 = 0;
    source->piece = NULL;
    destination->piece = piece;
    func_001F1FD0(piece->handle, &position);
    position.x = (f32)((x - 3) * 50);
    position.z = (f32)((y - 3) * 50);
    func_001F22B0(piece->handle, &position);
    if (piece->object != NULL) {
        position.y = 0.0f;
        piece->object->position = position;
    }
    return piece;
}

s32 func_001E0110(s32 arg0) {
    s32 temp_s0;

    temp_s0 = func_001E0150(arg0);
    return temp_s0 + func_001E01F0(arg0);
}

void *func_001DD130();

static inline u8 *check_001E0150(s32 a0, s32 a1) {
    u8 *p = func_001DD130(a0, a1);
    if (p == NULL) {
        return NULL;
    }
    if (p[0x45] >= 0xB) {
        return NULL;
    }
    return p;
}

s32 func_001E0150(s32 arg0) {
    s32 count;
    s32 i;

    count = 0;
    for (i = 1; i < 6; i++) {
        if (check_001E0150(arg0, i) != NULL) {
            count++;
        }
    }
    return count;
}

void *func_001DD130();

static inline u8 *check_001E01F0(s32 a0, s32 a1) {
    u8 *p = func_001DD130(a0, a1);
    if (p == NULL) {
        return NULL;
    }
    if (p[0x45] >= 0xB) {
        return NULL;
    }
    return p;
}

s32 func_001E01F0(s32 arg0) {
    s32 count;
    s32 i;

    count = 0;
    for (i = 6; i < 0xB; i++) {
        if (check_001E01F0(arg0, i) != NULL) {
            count++;
        }
    }
    return count;
}

void *func_001DD130();

static inline void *lookup_001E0290(s32 arg0, s32 arg1)
{
    void *object = func_001DD130(arg0, arg1);

    if (object == 0) {
        return 0;
    }
    if (*((u8 *)object + 0x45) >= 11) {
        return 0;
    }
    return object;
}

s32 func_001E0290(s32 arg0, s32 arg1, s32 arg2)
{
    return func_001E02F0(lookup_001E0290(arg0, arg1), arg2);
}

#define MAX_001E02F0(a, b) ((a) > (b) ? (a) : (b))
#define MIN_001E02F0(a, b) ((a) < (b) ? (a) : (b))

s32 func_001E02F0(void *arg0, s32 arg1) {
    s32 value;
    void *data;

    if (arg0 == NULL) {
        return -1;
    }
    data = *(void **)arg0;
    if (data == NULL) {
        return -1;
    }
    value = *(u16 *)((u8 *)data + 8) & 0x1FFF;
    if (arg1 == 0) {
        value += *(s16 *)((u8 *)arg0 + 0x38);
    }
    return MIN_001E02F0(MAX_001E02F0(value, 0), 9999);
}

void *func_001DD130();

static inline void *lookup_001E0370(s32 arg0, s32 arg1) {
    void *ptr;

    ptr = func_001DD130(arg0, arg1);
    if (ptr == NULL) {
        return NULL;
    }
    if (*((u8 *)ptr + 0x45) >= 11) {
        return NULL;
    }
    return ptr;
}

s32 func_001E0370(s32 arg0, s32 arg1, s32 arg2) {
    return func_001E03D0(lookup_001E0370(arg0, arg1), arg2);
}

static inline s32 lower_bound_001E03D0(s32 value) {
    if (value > 0) {
        return value;
    }
    return 0;
}

s32 func_001E03D0(void *arg0, s32 arg1) {
    s32 value;
    void *data;

    if (arg0 == NULL) {
        return -1;
    }
    data = *(void **)arg0;
    if (data == NULL) {
        return -1;
    }
    value = *(u16 *)((u8 *)data + 0xA) & 0x1FFF;
    if (arg1 == 0) {
        value += *(s16 *)((u8 *)arg0 + 0x3A);
    }
    if (lower_bound_001E03D0(value) < 9999) {
        return lower_bound_001E03D0(value);
    }
    return 9999;
}


static inline void *get_001E0450(void) {
    void *var_v0;

    var_v0 = func_001DD130();
    if (var_v0 == NULL) {
        return NULL;
    }
    if (*(u8 *)((u8 *)var_v0 + 0x45) >= 0xB) {
        return NULL;
    }
    return var_v0;
}

void func_001E0450(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_001E04C0(get_001E0450(), arg2, arg3);
}

#define MAX_001E04C0(a, b) ((a) > (b) ? (a) : (b))
#define MIN_001E04C0(a, b) ((a) < (b) ? (a) : (b))

typedef struct {
    u8 pad_00[0x38];
    s16 value;
} Obj_001E04C0;

s32 func_001E04C0(void *arg0, s32 arg1, s32 arg2) {
    Obj_001E04C0 *obj = arg0;
    s32 cur;
    s32 val;

    val = arg2;
    if (obj == NULL) {
        return 0;
    }
    cur = obj->value;
    switch (arg1) {
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

static inline void *check_001E0570(void *ptr) {
    if (ptr == NULL) {
        return NULL;
    }
    if (*((u8 *)ptr + 0x45) >= 0xB) {
        return NULL;
    }
    return ptr;
}

s32 func_001E0570(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    void *var_v0;

    var_v0 = check_001E0570(func_001DD130(arg0, arg1));
    return func_001E05E0(var_v0, arg2, arg3);
}

#define MAX_001E05E0(a, b) ((a) > (b) ? (a) : (b))
#define MIN_001E05E0(a, b) ((a) < (b) ? (a) : (b))

typedef struct {
    u8 pad_00[0x3A];
    s16 value;
} Obj_001E05E0;

s32 func_001E05E0(void *arg0, s32 arg1, s32 arg2) {
    Obj_001E05E0 *obj = arg0;
    s32 cur;
    s32 val;

    val = arg2;
    if (obj == NULL) {
        return 0;
    }
    cur = obj->value;
    switch (arg1) {
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
    u8 kind;
} Entry_001E0690;

static inline void *lookup_001E0690(void) {
    Entry_001E0690 *entry = func_001DD130();

    if (entry == NULL) {
        return NULL;
    }
    if (entry->kind >= 0xB) {
        return NULL;
    }
    return entry;
}

s32 func_001E0690(s32 unused0, s32 unused1) {
    Entry_001E0690 *entry = lookup_001E0690();

    if (entry == NULL) {
        return -1;
    }
    if (entry->data != NULL) {
        return *entry->data;
    }
    return -1;
}

static inline u8 *get_entry_bytes_001E0700(void) {
    u8 *entry;

    entry = func_001DD130();
    if (entry == NULL) {
        return NULL;
    }
    if (entry[0x45] >= 11) {
        return NULL;
    }
    return entry;
}

s32 func_001E0700(s32 arg0, s32 arg1) {
    u8 *entry;

    entry = get_entry_bytes_001E0700();
    if (entry != NULL) {
        return entry[0x3E];
    }
    return -1;
}

void *func_001DD130();

static inline u8 *check_001E0760(s32 a0, s32 a1) {
    u8 *p = func_001DD130(a0, a1);
    if (p == NULL) {
        return NULL;
    }
    if (p[0x45] >= 0xB) {
        return NULL;
    }
    return p;
}

s32 func_001E0760(s32 a0, s32 a1, s8 arg2) {
    u8 *p;

    p = check_001E0760(a0, a1);
    if (p == NULL) {
        return 0;
    }
    p[0x3E] = arg2;
    return 1;
}

static inline void *check_001E07C0(void *ptr) {
    if (ptr == NULL) {
        return NULL;
    }
    if (((u8 *)ptr)[0x45] >= 11) {
        return NULL;
    }
    return ptr;
}

s32 func_001E07C0(void) {
    void **ptr;
    void *data;

    ptr = check_001E07C0(func_001DD130());
    if (ptr == NULL) {
        return -1;
    }
    data = *ptr;
    if (data != NULL) {
        return ((u8 *)data)[1];
    }
    return -1;
}

void *func_001DD130();

static inline u8 *check_001E0830(s32 a0, s32 a1) {
    u8 *p = func_001DD130(a0, a1);
    if (p == NULL) {
        return NULL;
    }
    if (p[0x45] >= 0xB) {
        return NULL;
    }
    return p;
}

s32 func_001E0830(s32 arg0, s32 arg1) {
    u8 *p;

    p = check_001E0830(arg0, arg1);
    if (p != NULL) {
        return p[0x3F];
    }
    return -1;
}

void *func_001DD130();

static inline void *lookup_001E0890(s32 arg0, s32 arg1) {
    void *entry;

    entry = func_001DD130(arg0, arg1);
    if (entry == NULL) {
        return NULL;
    }
    if (*(u8 *)((u8 *)entry + 0x45) >= 0xB) {
        return NULL;
    }
    return entry;
}

s32 func_001E0890(s32 arg0, s32 arg1, s8 arg2) {
    void *entry;

    entry = lookup_001E0890(arg0, arg1);
    if (entry == NULL) {
        return 0;
    }
    *(s8 *)((u8 *)entry + 0x3F) = arg2;
    return 1;
}

void *func_001DD130();

static inline void *check_001E08F0(void *var_v0) {
    if (var_v0 == NULL) {
        return NULL;
    }
    if (*(u8 *)((u8 *)var_v0 + 0x45) >= 0xB) {
        return NULL;
    }
    return var_v0;
}

void func_001E08F0(s32 arg0, s32 arg1, s32 arg2) {
    func_001E0950(check_001E08F0(func_001DD130()), arg2);
}

typedef struct Flags_001E0950 {
    u8 padding[2];
    u8 low : 4;
    u8 high : 4;
} Flags_001E0950;

s32 func_001E0950(void *arg0, s32 arg1) {
    s32 value;
    void *temp_v0;

    if (arg0 == NULL) {
        return -1;
    }
    temp_v0 = *(void **)arg0;
    if (temp_v0 == NULL) {
        return -1;
    }
    value = ((Flags_001E0950 *)temp_v0)->high;
    if (arg1 == 0) {
        value -= *(u8 *)((u8 *)arg0 + 0x48);
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

void *func_001E09E0(void *arg0, s32 arg1) {
    void *cell;
    s32 on_board;
    s32 x;
    s32 y;
    s32 card_id;
    s32 data_id;
    Sub_001E09E0 *data;
    Object_001E09E0 *object = arg0;

    on_board = 1;
    if (object == NULL) {
        return NULL;
    }
    data = object->data;
    if (data == NULL) {
        return NULL;
    }
    if (arg1 < 0 || arg1 >= 5) {
        return NULL;
    }
    x = object->x;
    y = object->y;
    if (x < 0 || x >= 7 || y < 0 || y >= 7) {
        cell = NULL;
    } else {
        cell = (void *)(x * 0x1C + (D_00318E60 + y * 0xC4));
    }
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
        return D_002C3338[card_id][arg1];
    }
    data_id = data->id;
    if (data_id == 0xFFFF) {
        return NULL;
    }
    if (object->state < 6) {
        return D_002C9DF0[data_id][arg1];
    }
    return D_002CC5F0[data_id];
}

static inline void *check_001E0B70(void) {
    void *record;

    record = func_001DD130();
    if (record == NULL) {
        return NULL;
    }
    if (*(u8 *)((u8 *)record + 0x45) >= 11) {
        return NULL;
    }
    return record;
}

void *func_001E0B70(s32 arg0, s32 arg1, s32 index) {
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

s32 func_001E0C70(void *, s32, s32);                /* extern */

static inline void *check_001E0C00(void) {
    void *ptr = func_001DD130();
    if (ptr == NULL) {
        return NULL;
    }
    if (*((u8 *)ptr + 0x45) >= 0xB) {
        return NULL;
    }
    return ptr;
}

s32 func_001E0C00(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return func_001E0C70(check_001E0C00(), arg2, arg3);
}

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E0C70);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E0C80);

s32 func_001E1030(void) {
    u8 *entry;

    entry = func_001DD130();
    if (entry == NULL) {
        entry = NULL;
    } else if (entry[0x45] >= 11) {
        entry = NULL;
    }
    if (entry != NULL) {
        return *(u16 *)(entry + 0x3C);
    }
    return -1;
}

void *func_001DD130();

static inline u8 *get_001E1090(void) {
    u8 *data;

    data = func_001DD130();
    if (data == NULL) {
        return NULL;
    }
    if (data[0x45] >= 0xB) {
        return NULL;
    }
    return data;
}

s32 func_001E1090(s32 arg0, s32 arg1) {
    u8 *data;

    data = get_001E1090();
    if (data != NULL) {
        return (data[0x41] << 8) | data[0x40];
    }
    return -1;
}

void func_001E10F0(s32 arg0, s32 arg1, s32 arg2, void *arg3) {
    f32 *out = arg3;

    out[2] = 0.0f;
    out[0] = 0.0f;
    if ((arg0 >= 0) && (arg0 < 7)) {
        out[0] = (f32) ((arg0 - 3) * 50);
    }
    if ((arg1 >= 0) && (arg1 < 7)) {
        out[2] = (f32) ((arg1 - 3) * 50);
    }
    out[1] = (f32) (arg2 * 35) / 128.0f;
    out[3] = 1.0f;
}

void *func_001DD130();

static inline u8 *check_001E11B0(s32 a0, s32 a1) {
    u8 *p = func_001DD130(a0, a1);
    if (p == NULL) {
        return NULL;
    }
    if (p[0x45] >= 0xB) {
        return NULL;
    }
    return p;
}

static inline u8 *cell_001E11B0(s32 x, s32 y) {
    if ((x < 0) || (x >= 7) || (y < 0) || (y >= 7)) {
        return NULL;
    }
    return (x * 0x1C) + (D_00318E60 + (y * 0xC4));
}

static inline void place_001E11B0(s32 arg0, s32 arg1, s32 arg2, void *arg3) {
    f32 *out = arg3;

    out[2] = 0.0f;
    out[0] = 0.0f;
    if ((arg0 >= 0) && (arg0 < 7)) {
        out[0] = (f32) ((arg0 - 3) * 50);
    }
    if ((arg1 >= 0) && (arg1 < 7)) {
        out[2] = (f32) ((arg1 - 3) * 50);
    }
    out[1] = (f32) (arg2 * 35) / 128.0f;
    out[3] = 1.0f;
}

s32 func_001E11B0(s32 arg0, s32 arg1, f32 *arg2) {
    u8 *p;

    p = check_001E11B0(arg0, arg1);
    if (p == NULL) {
        return 0;
    }
    place_001E11B0(p[0x40], p[0x41], *(s16 *)(cell_001E11B0(p[0x40], p[0x41]) + 0x14), arg2);
    arg2[0] += (f32) *(s16 *)(p + 0x34);
    arg2[2] += (f32) *(s16 *)(p + 0x36);
    return 1;
}

void *func_001DD130(void);

static inline void *lookup_001E1360(void) {
    void *ptr;

    ptr = func_001DD130();
    if (ptr == NULL) {
        ptr = NULL;
    } else if (*((u8 *)ptr + 0x45) >= 11) {
        ptr = NULL;
    }
    return ptr;
}

s32 func_001E1360(s32 unused0, s32 unused1) {
    void *ptr;

    ptr = lookup_001E1360();
    if (ptr != NULL) {
        return *((u8 *)ptr + 0x46);
    }
    return -1;
}

typedef struct Entry_001E13C0 {
    u8 padding[0x45];
    u8 type;
    u8 padding46;
    u8 value;
} Entry_001E13C0;

void *func_001DD130(void);

s32 func_001E13C0(s32 unused0, s32 unused1) {
    Entry_001E13C0 *entry;

    entry = func_001DD130();
    if (entry == NULL) {
        entry = NULL;
    } else if (entry->type >= 0xB) {
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

static inline void *check_001E1420(void) {
    void *ptr = func_001DD130();

    if (ptr == NULL) {
        return NULL;
    }
    if (*(u8 *)((u8 *)ptr + 0x45) >= 0xB) {
        return NULL;
    }
    return ptr;
}

s32 func_001E1420(s32 arg0, s32 arg1, s32 arg2) {
    void *ptr = check_001E1420();

    if (ptr == NULL) {
        return 0;
    }
    ((Flags_001E1420 *)((u8 *)ptr + 0x58))->enabled = (s8)(arg2 != 0 ? 1 : 0);
    return 1;
}

typedef struct {
    s8 reserved : 3;
    s8 active : 1;
    s8 reserved2 : 4;
} Flags_001E14B0;

typedef struct {
    u8 reserved[0x45];
    u8 type;
    u8 reserved2[0x12];
    Flags_001E14B0 flags;
} Entry_001E14B0;

static inline void *lookup_001E14B0(void) {
    void *entry = func_001DD130();

    if (entry == NULL) {
        entry = NULL;
    } else if (((Entry_001E14B0 *)entry)->type >= 0xB) {
        entry = NULL;
    }
    return entry;
}

s32 func_001E14B0(void) {
    void *entry = lookup_001E14B0();

    if (entry == NULL) {
        return 0;
    }
    return ((Entry_001E14B0 *)entry)->flags.active != 0 ? 1 : 0;
}

void *func_001DD130();

static inline void *lookup_001E1520(void) {
    void *entry = func_001DD130();

    if (entry == NULL) {
        return NULL;
    }
    if (*(u8 *)((u8 *)entry + 0x45) >= 11) {
        return NULL;
    }
    return entry;
}

s32 func_001E1520(s32 arg0, s32 arg1, s8 arg2) {
    void *entry = lookup_001E1520();

    if (entry == NULL) {
        return 0;
    }
    *(s8 *)((u8 *)entry + 0x49) = arg2;
    return 1;
}

void *func_001DD130(void);

static inline void *get_001E1580(void) {
    void *entry;

    entry = func_001DD130();
    if (entry == NULL) {
        return NULL;
    }
    if (*(u8 *)((u8 *)entry + 0x45) >= 11) {
        return NULL;
    }
    return entry;
}

s32 func_001E1580(void) {
    void *entry;

    entry = get_001E1580();
    if (entry != NULL) {
        return *(u8 *)((u8 *)entry + 0x49);
    }
    return -1;
}

s32 func_001E15E0(s32 arg0, s32 arg1, s8 arg2) {
    void *var_v0;

    var_v0 = func_001DD130();
    if (var_v0 == NULL) {
        var_v0 = NULL;
    } else if (*(u8 *)((u8 *)var_v0 + 0x45) >= 0xB) {
        var_v0 = NULL;
    }
    if (var_v0 == NULL) {
        return 0;
    }
    *(s8 *)((u8 *)var_v0 + 0x4A) = arg2;
    return 1;
}

void *func_001DD130(void);

static inline u8 *check_001E1640(void) {
    u8 *entry;

    entry = func_001DD130();
    if (entry == NULL) {
        return NULL;
    }
    if (entry[0x45] >= 11) {
        entry = NULL;
    }
    return entry;
}

s32 func_001E1640(void) {
    u8 *entry;

    entry = check_001E1640();
    if (entry != NULL) {
        return entry[0x4A];
    }
    return -1;
}

void *func_001DD130();

static inline u8 *check_001E16A0(s32 a0, s32 a1) {
    u8 *p = func_001DD130(a0, a1);
    if (p == NULL) {
        return NULL;
    }
    if (p[0x45] >= 0xB) {
        return NULL;
    }
    return p;
}

s32 func_001E16A0(s32 a0, s32 a1, s8 arg2) {
    u8 *p;

    p = check_001E16A0(a0, a1);
    if (p == NULL) {
        return 0;
    }
    p[0x4B] = arg2;
    return 1;
}

void *func_001DD130(void);

static inline u8 *valid_001E1700(void) {
    u8 *ptr;

    ptr = func_001DD130();
    if (ptr == NULL) {
        return NULL;
    }
    if (ptr[0x45] >= 0xB) {
        return NULL;
    }
    return ptr;
}

s32 func_001E1700(void) {
    u8 *ptr;

    ptr = valid_001E1700();
    if (ptr != NULL) {
        return ptr[0x4B];
    }
    return -1;
}

typedef struct Card_001E1760 {
    u8 pad00[0x40];
    u8 x;
    u8 y;
    u8 pad42[3];
    u8 type;
} Card_001E1760;

s32 func_002464F0(void *, u8, u8);

s32 func_001E1760(void) {
    Card_001E1760 *card;

    card = func_001DD130();
    if (card == NULL) {
        card = NULL;
    } else if (card->type >= 11) {
        card = NULL;
    }
    if (card != NULL) {
        return func_002464F0(card, card->x, card->y) & 0xF;
    }
    return 0;
}

typedef struct {
    u8 padding[0x40];
    u8 x;
    u8 y;
    u8 padding_42[3];
    u8 type;
} Card_001E17D0;

s32 func_002464F0(void *, u8, u8);

static inline void *get_card_001E17D0(void) {
    Card_001E17D0 *card = func_001DD130();

    if (card == NULL) {
        return NULL;
    }
    if (card->type >= 11) {
        return NULL;
    }
    return card;
}

s32 func_001E17D0(void) {
    Card_001E17D0 *card = get_card_001E17D0();

    if (card == NULL) {
        return 0;
    }
    return ((u32)func_002464F0(card, card->x, card->y) >> 4) != 0 ? 1 : 0;
}

s32 func_001E1840(s32 arg0, s32 arg1, s8 arg2) {
    void *var_v0;

    var_v0 = func_001DD130();
    if (var_v0 == NULL) {
        var_v0 = NULL;
    } else if (*(u8 *)((u8 *)var_v0 + 0x45) >= 0xB) {
        var_v0 = NULL;
    }
    if (var_v0 == NULL) {
        return 0;
    }
    *(s8 *)((u8 *)var_v0 + 0x4E) = arg2;
    return 1;
}

static inline void *check_001E18A0(void) {
    void *p = func_001DD130();
    if (p == NULL) {
        return NULL;
    }
    if (*(u8 *)((u8 *)p + 0x45) >= 0xB) {
        return NULL;
    }
    return p;
}

s32 func_001E18A0(s32 arg0, s32 arg1, s8 arg2) {
    void *p = check_001E18A0();
    if (p == NULL) {
        return 0;
    }
    *(s8 *)((u8 *)p + 0x4F) = arg2;
    return 1;
}

s32 func_001E1900(s32 arg0, s32 arg1, s8 arg2) {
    s32 var_s0;

    var_s0 = 0;
    if (func_001E1970(arg0, arg1, arg2) != 0) {
        if (func_001E19D0(arg0, arg1, arg2) != 0) {
            var_s0 = 1;
        }
    }
    return var_s0;
}

static inline void *get_001E1970(void) {
    void *p;

    p = func_001DD130();
    if (p == NULL) {
        return NULL;
    }
    if (*(u8 *)((u8 *)p + 0x45) >= 0xB) {
        return NULL;
    }
    return p;
}

s32 func_001E1970(s32 arg0, s32 arg1, s8 arg2) {
    void *p;

    p = get_001E1970();
    if (p == NULL) {
        return 0;
    }
    *(s8 *)((u8 *)p + 0x50) = arg2;
    return 1;
}

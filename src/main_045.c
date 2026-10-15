#include "common.h"

s32 SzDuel_GetUnit(s32 arg0, s32 arg1) {
    extern void *SzDuel_GetCardInfo();
    u8 *result;

    result = SzDuel_GetCardInfo(arg0, arg1);
    if (result == NULL) {
        return 0;
    }
    if (result[0x45] >= 11) {
        result = NULL;
    }
    return (s32)result;
}

void SzDuel_AddUnit(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u8 buffer[0x60];

    SzDuel_InitCardInfo(buffer, arg3);
    SzDuel_AddUnit2(arg0, arg1, arg2, buffer, arg4);
}

struct DotrStateBlock {
    int unknown_words[24];
};
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
extern struct DotrStateItem D_00318280_b[3][11];
extern struct DotrStateCell D_00318E60_b[7][7];
extern struct DotrStateEntry8 D_002C3338_1df5f0[][5];
struct DotrReleaseCurrent;
struct DotrReleaseObject {
    unsigned char unknown_00[0x10];
    int unknown_10[4]; 
    int unknown_20[4]; 
    float unknown_30;
    float unknown_34;
    float unknown_38;
    int unknown_3c;
    unsigned char unknown_40[0x41];
    signed char unknown_81_bits_0_3 : 4;
    signed char unknown_81_bit_4 : 1;
    signed char unknown_81_bit_5 : 1;
    signed char unknown_81_bit_6 : 1;
    signed char unknown_81_bit_7 : 1;
    unsigned char unknown_82;
    signed char unknown_83_bits_0_5 : 6;
    signed char unknown_83_bit_6 : 1;
    signed char unknown_83_bit_7 : 1; 
    unsigned char unknown_84[0xc];
    struct DotrReleaseCurrent *unknown_90; 
    unsigned char unknown_94[0xc];
};
extern struct DotrReleaseObject D_003193C0_b[32];
struct DotrOwnerDrawBlock;
struct DotrReleaseCurrent {
    int unknown_00;
    struct DotrReleaseObject *object;
    unsigned char unknown_08[0x34];
    unsigned short unknown_3c; 
    unsigned char unknown_3e[2];
    unsigned char unknown_40;
    unsigned char unknown_41;
    unsigned char unknown_42[2];
    unsigned char unknown_44;
    unsigned char unknown_45;
    unsigned char unknown_46[2];
    unsigned char unknown_48;
    unsigned char unknown_49[0xa];
    unsigned char unknown_53; 
    unsigned char unknown_54[3];
    signed char unknown_57_bits_0_6 : 7;
    signed char unknown_57_bit_7 : 1;
    signed char unknown_58_bit_0 : 1;
    signed char unknown_58_bit_1 : 1;
    signed char unknown_58_bit_2 : 1;
    signed char unknown_58_bits_3_7 : 5;
};
struct DotrReleaseSide {
    unsigned char unknown_000[0x33d];
    unsigned char unknown_33d;
    unsigned char unknown_33e;
    unsigned char unknown_33f[4];
    unsigned char unknown_343; 
    unsigned char unknown_344[0xc];
};
extern struct DotrReleaseSide D_00317490_b[];
struct DotrReleasePair {
    float unknown_00;
    float unknown_04;
};
struct DotrReleaseItemPairs {
    void *unknown_00; 
    void *unknown_04;
    struct DotrReleasePair unknown_08[5];
};
struct DotrReleaseAngles {
    int x;
    int y;
    int z;
    int w;
};
extern struct DotrStateVector D_002915D0;
extern struct DotrReleaseAngles D_002915E0;
extern struct DotrStateVector D_002915F0;
extern int func_001F1A00_b(int index, int value);
static inline struct DotrStateCell *cell_1df5f0(int x, int y)
{
    if (x < 0 || x >= 7 || y < 0 || y >= 7) {
        return 0;
    }
    return &D_00318E60_b[y][x];
}
static inline struct DotrReleaseObject *free_object(void)
{
    struct DotrReleaseObject *p = D_003193C0_b;
    int i;

    for (i = 0; i < 32; i++, p++) {
        if (p->unknown_90 == 0) {
            SzDuel_ClearDrawCard((struct DotrOwnerDrawBlock *)p);
            return p;
        }
    }
    return 0;
}
static inline int card_index(int id)
{
    unsigned short *p = D_002CD8A0;
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
static inline void copy_item(struct DotrStateItem *to, struct DotrStateItem *from)
{
    int *d = (int *)to;
    int *s = (int *)from;
    int n;

    for (n = 23; n > 0; n--) {
        *d++ = *s++;
    }
}

int SzDuel_AddUnit2(int side, int x, int y, void *src_v, int leader)
{
    struct DotrStateBlock * src = src_v;
    struct DotrReleaseSide *rec = &D_00317490_b[side];
    struct DotrStateCell *c = cell_1df5f0(x, y);
    int count = 1;
    int first = 0;
    int id;
    int i;
    int n;
    struct DotrStateItem *unit;
    int k;
    int model;

    if (src == 0) {
        return 0;
    }
    if (c == 0) {
        return 0;
    }
    if (c->unknown_00 != 0) {
        return 0;
    }
    id = ((struct DotrStateItem *)src)->unknown_3c;
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
        unit = &D_00318280_b[side][n];
        if (unit->unknown_45 >= 11) {
            copy_item(unit, (struct DotrStateItem *)src);
            unit->unknown_48 = Ta_GetSummonRev(side, id);
            unit->unknown_40 = x;
            unit->unknown_41 = y;
            unit->unknown_44 = side;
            unit->unknown_45 = n;
            c->unknown_00 = (DotrStateWord)unit;
            if (leader != 0) {
                for (k = 0; k < 5; k++) {
                    ((struct DotrReleaseItemPairs *)unit)->unknown_08[k] =
                        ((struct DotrReleasePair *)D_002C3338_1df5f0[id])[k];
                }
            } else {
                if (unit->unknown_04 == 0) {
                    unit->unknown_04 = (struct DotrStateItemObject *)free_object();
                }
                if (unit->unknown_04 != 0) {
                    ((struct DotrReleaseObject *)unit->unknown_04)->unknown_90 =
                        (struct DotrReleaseCurrent *)unit;
                    SzDuel_CalcUnitPos(x, y, 0, (struct DotrStateVector *)unit->unknown_04);
                }
                unit->unknown_47 = rec->unknown_343++;
                SzData_SetLookFlag(side, id, 1);
            }
            k = card_index(id);
            if (first == 0 || first == 1) {
                struct DotrStateVector pos = D_002915D0;
                struct DotrReleaseAngles rot;
                struct DotrStateVector rotc;

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
                unit->unknown_46 = model;
                SzModel_Preset(model, -1, k);
                SzModel_SetAnimDirect(model, 0);
                func_001F1A00_b(model, 1);
                SzModel_SetAnimSpeed(model, 1.0f);
                SzModel_SetPos(model, &pos);
                SzModel_SetRot(model, &rot);
                SzModel_SetRotC(model, &rotc);
                SzModel_SetRgba(model, 0, 0);
                SzModel_SetFilter(model, 1, 0);
                lSzDuel_DoUnitRequest(c, (DotrStateWord)unit);
            }
            return (int)(DotrStateWord)unit;
        }
    }
    return 0;
}

static inline u8 *check_001DFAF0(s32 a0, s32 a1) {
    extern void *SzDuel_GetCardInfo();
    u8 *p = SzDuel_GetCardInfo(a0, a1);

    if (p == NULL) {
        return NULL;
    }
    if (p[0x45] >= 0xB) {
        return NULL;
    }
    return p;
}

s32 SzDuel_PutUnit(s32 arg0, s32 arg1, s32 arg2) {
    u8 buffer[0x60];
    u8 *record;
    s32 x;
    s32 y;

    record = check_001DFAF0(arg0, arg1);
    if (record == NULL) {
        return 0;
    }
    arg0 = record[0x44];
    arg1 = record[0x45];
    x = record[0x40];
    y = record[0x41];
    SzDuel_DelUnit(arg0, arg1);
    SzDuel_InitCardInfo(buffer, arg2);
    SzDuel_AddUnit2(arg0, x, y, buffer, arg1 == 0 ? 1 : 0);
}


static inline u8 *check_001DFBB0(s32 a0, s32 a1) {
    u8 *p = SzDuel_GetCardInfo(a0, a1);
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
    SzDuel_ClearDrawCard(p);
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

s32 SzDuel_DelUnit(s32 arg0, s32 arg1) {
    u8 *obj;
    u8 *slot;

    obj = check_001DFBB0(arg0, arg1);
    if (obj == NULL) {
        return 0;
    }
    if (arg0 < 2) {
        if (obj[0x45] < 6) {
            SzModel_Preset(obj[0x46], -1, 0x3E7);
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
            SzDuel_ClearCardControl(slot);
        }
    }
    SzDuel_InitCardInfo(obj, -1);
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
    extern void SzDuel_ClearDrawCard();

    if (object != NULL) {
        SzDuel_ClearDrawCard(object);
        object->active = 0;
    }
}

void *SzDuel_MoveUnit(s32 arg0, s32 arg1, s32 x, s32 y) {
    extern void *SzDuel_GetCardInfo();
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

    found = SzDuel_GetCardInfo(arg0, arg1);
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
        found = SzDuel_GetCardInfo(player, index);
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
                    SzModel_Preset(occupied->handle, -1, 999);
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
                    SzDuel_ClearCardControl((u8 *)entry);
                }
            }
            SzDuel_InitCardInfo(occupied, -1);
        }
    }
    piece->x = x;
    piece->y = y;
    piece->field34 = 0;
    piece->field36 = 0;
    source->piece = NULL;
    destination->piece = piece;
    SzModel_GetPos(piece->handle, &position);
    position.x = (f32)((x - 3) * 50);
    position.z = (f32)((y - 3) * 50);
    SzModel_SetPos(piece->handle, &position);
    if (piece->object != NULL) {
        position.y = 0.0f;
        piece->object->position = position;
    }
    return piece;
}

s32 SzDuel_GetUnitCount(s32 arg0) {
    s32 temp_s0;

    temp_s0 = SzDuel_GetUnitMonsterCount(arg0);
    return temp_s0 + SzDuel_GetUnitSpellCount(arg0);
}


static inline u8 *check_001E0150(s32 a0, s32 a1) {
    u8 *p = SzDuel_GetCardInfo(a0, a1);
    if (p == NULL) {
        return NULL;
    }
    if (p[0x45] >= 0xB) {
        return NULL;
    }
    return p;
}

s32 SzDuel_GetUnitMonsterCount(s32 arg0) {
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


static inline u8 *check_001E01F0(s32 a0, s32 a1) {
    u8 *p = SzDuel_GetCardInfo(a0, a1);
    if (p == NULL) {
        return NULL;
    }
    if (p[0x45] >= 0xB) {
        return NULL;
    }
    return p;
}

s32 SzDuel_GetUnitSpellCount(s32 arg0) {
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


static inline void *lookup_001E0290(s32 arg0, s32 arg1)
{
    void *object = SzDuel_GetCardInfo(arg0, arg1);

    if (object == 0) {
        return 0;
    }
    if (*((u8 *)object + 0x45) >= 11) {
        return 0;
    }
    return object;
}

s32 SzDuel_GetUnitAP(s32 arg0, s32 arg1, s32 arg2)
{
    return SzDuel_GetUnitAP2(lookup_001E0290(arg0, arg1), arg2);
}

#define MAX_001E02F0(a, b) ((a) > (b) ? (a) : (b))
#define MIN_001E02F0(a, b) ((a) < (b) ? (a) : (b))

s32 SzDuel_GetUnitAP2(void *arg0, s32 arg1) {
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


static inline void *lookup_001E0370(s32 arg0, s32 arg1) {
    void *ptr;

    ptr = SzDuel_GetCardInfo(arg0, arg1);
    if (ptr == NULL) {
        return NULL;
    }
    if (*((u8 *)ptr + 0x45) >= 11) {
        return NULL;
    }
    return ptr;
}

s32 SzDuel_GetUnitDP(s32 arg0, s32 arg1, s32 arg2) {
    return SzDuel_GetUnitDP2(lookup_001E0370(arg0, arg1), arg2);
}

static inline s32 lower_bound_001E03D0(s32 value) {
    if (value > 0) {
        return value;
    }
    return 0;
}

s32 SzDuel_GetUnitDP2(void *arg0, s32 arg1) {
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
    extern void *SzDuel_GetCardInfo();
    void *var_v0;

    var_v0 = SzDuel_GetCardInfo();
    if (var_v0 == NULL) {
        return NULL;
    }
    if (*(u8 *)((u8 *)var_v0 + 0x45) >= 0xB) {
        return NULL;
    }
    return var_v0;
}

void SzDuel_CalcUnitAP(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    SzDuel_CalcUnitAP2(get_001E0450(), arg2, arg3);
}

#define MAX_001E04C0(a, b) ((a) > (b) ? (a) : (b))
#define MIN_001E04C0(a, b) ((a) < (b) ? (a) : (b))

typedef struct {
    u8 pad_00[0x38];
    s16 value;
} Obj_001E04C0;

s32 SzDuel_CalcUnitAP2(void *arg0, s32 arg1, s32 arg2) {
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

s32 SzDuel_CalcUnitDP(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    void *var_v0;

    var_v0 = check_001E0570(SzDuel_GetCardInfo(arg0, arg1));
    return SzDuel_CalcUnitDP2(var_v0, arg2, arg3);
}

#define MAX_001E05E0(a, b) ((a) > (b) ? (a) : (b))
#define MIN_001E05E0(a, b) ((a) < (b) ? (a) : (b))

typedef struct {
    u8 pad_00[0x3A];
    s16 value;
} Obj_001E05E0;

s32 SzDuel_CalcUnitDP2(void *arg0, s32 arg1, s32 arg2) {
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
    extern void *SzDuel_GetCardInfo();
    Entry_001E0690 *entry = SzDuel_GetCardInfo();

    if (entry == NULL) {
        return NULL;
    }
    if (entry->kind >= 0xB) {
        return NULL;
    }
    return entry;
}

s32 SzDuel_GetUnitConstKind(s32 unused0, s32 unused1) {
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
    extern void *SzDuel_GetCardInfo();
    u8 *entry;

    entry = SzDuel_GetCardInfo();
    if (entry == NULL) {
        return NULL;
    }
    if (entry[0x45] >= 11) {
        return NULL;
    }
    return entry;
}

s32 SzDuel_GetUnitKind(s32 arg0, s32 arg1) {
    u8 *entry;

    entry = get_entry_bytes_001E0700();
    if (entry != NULL) {
        return entry[0x3E];
    }
    return -1;
}


static inline u8 *check_001E0760(s32 a0, s32 a1) {
    u8 *p = SzDuel_GetCardInfo(a0, a1);
    if (p == NULL) {
        return NULL;
    }
    if (p[0x45] >= 0xB) {
        return NULL;
    }
    return p;
}

s32 SzDuel_SetUnitKind(s32 a0, s32 a1, s8 arg2) {
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


static inline u8 *check_001E0830(s32 a0, s32 a1) {
    u8 *p = SzDuel_GetCardInfo(a0, a1);
    if (p == NULL) {
        return NULL;
    }
    if (p[0x45] >= 0xB) {
        return NULL;
    }
    return p;
}

s32 SzDuel_GetUnitAttr(s32 arg0, s32 arg1) {
    u8 *p;

    p = check_001E0830(arg0, arg1);
    if (p != NULL) {
        return p[0x3F];
    }
    return -1;
}


static inline void *lookup_001E0890(s32 arg0, s32 arg1) {
    void *entry;

    entry = SzDuel_GetCardInfo(arg0, arg1);
    if (entry == NULL) {
        return NULL;
    }
    if (*(u8 *)((u8 *)entry + 0x45) >= 0xB) {
        return NULL;
    }
    return entry;
}

s32 SzDuel_SetUnitAttr(s32 arg0, s32 arg1, s8 arg2) {
    void *entry;

    entry = lookup_001E0890(arg0, arg1);
    if (entry == NULL) {
        return 0;
    }
    *(s8 *)((u8 *)entry + 0x3F) = arg2;
    return 1;
}


static inline void *check_001E08F0(void *var_v0) {
    if (var_v0 == NULL) {
        return NULL;
    }
    if (*(u8 *)((u8 *)var_v0 + 0x45) >= 0xB) {
        return NULL;
    }
    return var_v0;
}

void SzDuel_GetUnitLevel(s32 arg0, s32 arg1, s32 arg2) {
    extern void *SzDuel_GetCardInfo();
    SzDuel_GetUnitLevel2(check_001E08F0(SzDuel_GetCardInfo()), arg2);
}

typedef struct Flags_001E0950 {
    u8 padding[2];
    u8 low : 4;
    u8 high : 4;
} Flags_001E0950;

s32 SzDuel_GetUnitLevel2(void *arg0, s32 arg1) {
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

void *SzDuel_GetUnitConstEffect2(void *arg0, s32 arg1) {
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

void *SzDuel_GetUnitEffect(s32 arg0, s32 arg1, s32 index) {
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

s32 SzDuel_GetUnitLeaderAbility(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return SzDuel_GetUnitLeaderAbility2(check_001E0C00(), arg2, arg3);
}

s32 SzDuel_GetUnitLeaderAbility2(void *arg0, s32 arg1, s32 arg2) {
    extern s32 SzDuel_GetUnitLeaderAbility3();

    return SzDuel_GetUnitLeaderAbility3(arg0, arg1, arg2, 0);
}

typedef struct Card_001E0C80 {
    u8 pad0[8];
    u32 pairs[9];
    u8 pad2C[0x10];
    u16 id;
    u8 pad3E[6];
    u8 owner;
} Card_001E0C80;

s32 SzDuel_GetUnitLeaderAbility3(void *arg0, u32 arg1, s32 *arg2, s32 arg3) {
    extern s32 SzData_GetRank();
    s32 extra;
    s32 need;
    Card_001E0C80 *card = arg0;
    s32 value;

    extra = 0;
    if (arg2 != NULL) {
        *arg2 = 0;
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
    if (arg3 == 0) {
        value = SzGame_GetMenuNum(0x1C);
        if (!(value & (1 << card->owner))) {
            return 0;
        }
    }
    switch (arg1) {
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
    if (arg2 != NULL) {
        *arg2 = extra;
    }
    return (value >= need) ? 1 : 0;
}

s32 SzDuel_GetUnitCardNo(void) {
    extern void *SzDuel_GetCardInfo();
    u8 *entry;

    entry = SzDuel_GetCardInfo();
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


static inline u8 *get_001E1090(void) {
    extern void *SzDuel_GetCardInfo();
    u8 *data;

    data = SzDuel_GetCardInfo();
    if (data == NULL) {
        return NULL;
    }
    if (data[0x45] >= 0xB) {
        return NULL;
    }
    return data;
}

s32 SzDuel_GetUnitLoc(s32 arg0, s32 arg1) {
    u8 *data;

    data = get_001E1090();
    if (data != NULL) {
        return (data[0x41] << 8) | data[0x40];
    }
    return -1;
}

void SzDuel_CalcUnitPos(s32 arg0, s32 arg1, s32 arg2, void *arg3) {
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


static inline u8 *check_001E11B0(s32 a0, s32 a1) {
    u8 *p = SzDuel_GetCardInfo(a0, a1);
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

s32 SzDuel_GetUnitPos(s32 arg0, s32 arg1, f32 *arg2) {
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

s32 SzDuel_GetUnitModelID(s32 unused0, s32 unused1) {
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


s32 SzDuel_GetUnitSummonOrder(s32 unused0, s32 unused1) {
    extern void *SzDuel_GetCardInfo();
    Entry_001E13C0 *entry;

    entry = SzDuel_GetCardInfo();
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

s32 SzDuel_SetUnitCurseFlag(s32 arg0, s32 arg1, s32 arg2) {
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
    extern void *SzDuel_GetCardInfo();
    void *entry = SzDuel_GetCardInfo();

    if (entry == NULL) {
        entry = NULL;
    } else if (((Entry_001E14B0 *)entry)->type >= 0xB) {
        entry = NULL;
    }
    return entry;
}

s32 SzDuel_GetUnitCurseFlag(void) {
    void *entry = lookup_001E14B0();

    if (entry == NULL) {
        return 0;
    }
    return ((Entry_001E14B0 *)entry)->flags.active != 0 ? 1 : 0;
}


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

s32 SzDuel_SetUnitCurseRest(s32 arg0, s32 arg1, s8 arg2) {
    void *entry = lookup_001E1520();

    if (entry == NULL) {
        return 0;
    }
    *(s8 *)((u8 *)entry + 0x49) = arg2;
    return 1;
}


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

s32 SzDuel_GetUnitCurseRest(void) {
    void *entry;

    entry = get_001E1580();
    if (entry != NULL) {
        return *(u8 *)((u8 *)entry + 0x49);
    }
    return -1;
}

s32 SzDuel_SetUnitSpellRest(s32 arg0, s32 arg1, s8 arg2) {
    extern void *SzDuel_GetCardInfo();
    void *var_v0;

    var_v0 = SzDuel_GetCardInfo();
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


static inline u8 *check_001E1640(void) {
    extern void *SzDuel_GetCardInfo();
    u8 *entry;

    entry = SzDuel_GetCardInfo();
    if (entry == NULL) {
        return NULL;
    }
    if (entry[0x45] >= 11) {
        entry = NULL;
    }
    return entry;
}

s32 SzDuel_GetUnitSpellRest(void) {
    u8 *entry;

    entry = check_001E1640();
    if (entry != NULL) {
        return entry[0x4A];
    }
    return -1;
}


static inline u8 *check_001E16A0(s32 a0, s32 a1) {
    u8 *p = SzDuel_GetCardInfo(a0, a1);
    if (p == NULL) {
        return NULL;
    }
    if (p[0x45] >= 0xB) {
        return NULL;
    }
    return p;
}

s32 SzDuel_SetUnitDelayCount(s32 a0, s32 a1, s8 arg2) {
    u8 *p;

    p = check_001E16A0(a0, a1);
    if (p == NULL) {
        return 0;
    }
    p[0x4B] = arg2;
    return 1;
}


static inline u8 *valid_001E1700(void) {
    extern void *SzDuel_GetCardInfo();
    u8 *ptr;

    ptr = SzDuel_GetCardInfo();
    if (ptr == NULL) {
        return NULL;
    }
    if (ptr[0x45] >= 0xB) {
        return NULL;
    }
    return ptr;
}

s32 SzDuel_GetUnitDelayCount(void) {
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


s32 SzDuel_CalcUnitMovable(void) {
    extern void *SzDuel_GetCardInfo();
    Card_001E1760 *card;

    card = SzDuel_GetCardInfo();
    if (card == NULL) {
        card = NULL;
    } else if (card->type >= 11) {
        card = NULL;
    }
    if (card != NULL) {
        return GetMoveRev((s32)card, card->x, card->y) & 0xF;
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


static inline void *get_card_001E17D0(void) {
    extern void *SzDuel_GetCardInfo();
    Card_001E17D0 *card = SzDuel_GetCardInfo();

    if (card == NULL) {
        return NULL;
    }
    if (card->type >= 11) {
        return NULL;
    }
    return card;
}

s32 SzDuel_IsUnitMovableOnLabyrinth(void) {
    Card_001E17D0 *card = get_card_001E17D0();

    if (card == NULL) {
        return 0;
    }
    return ((u32)GetMoveRev((s32)card, card->x, card->y) >> 4) != 0 ? 1 : 0;
}

s32 SzDuel_SetUnitCtlModeC(s32 arg0, s32 arg1, s8 arg2) {
    extern void *SzDuel_GetCardInfo();
    void *var_v0;

    var_v0 = SzDuel_GetCardInfo();
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

s32 SzDuel_SetUnitCtlModeM(s32 arg0, s32 arg1, s8 arg2) {
    void *p = check_001E18A0();
    if (p == NULL) {
        return 0;
    }
    *(s8 *)((u8 *)p + 0x4F) = arg2;
    return 1;
}

s32 SzDuel_SetUnitCtlGoal(s32 arg0, s32 arg1, s8 arg2) {
    s32 var_s0;

    var_s0 = 0;
    if (SzDuel_SetUnitCtlGoalC(arg0, arg1, arg2) != 0) {
        if (SzDuel_SetUnitCtlGoalM(arg0, arg1, arg2) != 0) {
            var_s0 = 1;
        }
    }
    return var_s0;
}

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

s32 SzDuel_SetUnitCtlGoalC(s32 arg0, s32 arg1, s8 arg2) {
    void *p;

    p = get_001E1970();
    if (p == NULL) {
        return 0;
    }
    *(s8 *)((u8 *)p + 0x50) = arg2;
    return 1;
}

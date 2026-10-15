#include "common.h"

void func_001D7D10(s32 arg0, s32 arg1) {
    u16 ids[4];
    s16 w[4];
    u8 *g = D_00317490.b;
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

    p = D_00317490.b + arg0 * 0x350;
    func_001DF1E0(arg0);
    func_001D89F0(arg0, 0, 999, 0, 0, 0, 0);
    x = -250;
    for (i = 0; i < g[0xD49]; i++) {
        v = func_001DF0C0(arg0, i);
        if (v < 0) {
            v = 999;
        } else {
            v &= 0xFFF;
        }
        func_001D89F0(arg0, i + 1, v, x, 0x1C0, x, -8);
        x += 0x7D;
    }
    if (arg1 != 0) {
        have = func_001DF110(arg0);
        n = func_001DE9C0(arg0);
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
                if (func_0026F690(arg0, ids, w, 0) >= 0) {
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
                id = func_001DED30(arg0);
            }
            func_001DF130(arg0, id);
            func_001D89F0(arg0, i + 1, id, 0x2EE, 0x1C0, 0x2EE, -8);
        }
        for (; i < 5; i++) {
            func_001DF130(arg0, 999);
            func_001D89F0(arg0, i + 1, 999, 0, 0, 0, 0);
        }
    } else {
        for (; i < 5; i++) {
            func_001D89F0(arg0, i + 1, 999, 0, 0, 0, 0);
        }
    }
    g[0xD4A] = func_001DF110(arg0);
    for (i = 0; i < g[0xD4A]; i++) {
        g[0xD2C + i] = i + 1;
    }
}

extern s32 D_00317B5C;

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

static inline u8 *lookup_001D8080(s32 index) {
    if (index < 0 || index >= 6) {
        return NULL;
    }
    return D_0031A7C0 + index * 0xA0;
}

static inline void releaseModel_001D8080(u8 *model) {
    extern void func_001CD560();

    if (model != NULL) {
        func_001CD560(model);
        *(s32 *)(model + 0x90) = 0;
    }
}

static inline void freeSlot_001D8080(u8 *slot) {
    if (slot != NULL) {
        if (*(u8 **)slot != NULL) {
            releaseModel_001D8080(*(u8 **)slot);
        }
        func_001CDD90(slot);
    }
}

s32 func_001D8080(s32 arg0) {
    u8 *base;
    u8 *slot;
    s32 index;
    s32 step;
    s32 result;
    u8 *candidate;

    base = D_00317490.b;
    if (D_00317B5C != 0 && *(void **)(*(u8 **)(base + 0x6CC) + 4) != NULL) {
        if ((slot = D_0031A7C0) != NULL && *(u8 **)slot != NULL) {
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
        result = func_001DF0C0(arg0, index);
        if (result >= 0 && (result & 0xFFF) != 999) {
            candidate = lookup_001D8080(index + 1);
            if (candidate != NULL && *(s32 *)candidate != 0) {
                ((Flags_001D8080 *)(candidate + 0x9F))->bit2 = 1;
                ((Flags_001D8080 *)(candidate + 0x9F))->bit4 = 0;
                func_001D8FB0(candidate, step, 0x1C0, step, -8, 0x80, 0x80);
            }
        }
        index++;
        step += 0x7D;
    } while (index < 5);

    base[0xD4A] = func_001DF110(arg0);
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

static inline Model_001D82C0 *get_model_001D82C0(void) {
    extern void func_001CD560();
    Model_001D82C0 *model = (Model_001D82C0 *)D_003193C0;
    s32 count = 0;
    do {
        if (model->owner == NULL) {
            func_001CD560(model);
            return model;
        }
        count++;
        model++;
    } while (count < 0x20);
    return NULL;
}

s32 func_001D82C0(s32 arg0) {
    extern void *func_001DD130();
    extern void func_001CD560();
    State_001D82C0 *state = (State_001D82C0 *)D_00317490.b;
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
            primary = (Node_001D82C0 *)D_0031A7C0;
            copy = func_001DD130(2, 0);
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
                    func_00205CB0(&primary->target, -125.0f, -8.0f);
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
                    func_00205C40((s32)&primary->values60);
                    primary->bit6 = 1;
                    primary->scale = model->scale;
                    primary->values80[0] = 0x3EF00000;
                    primary->values80[1] = 0x3EFA6F4E;
                    primary->values80[2] = 0x3F800000;
                    primary->values80[3] = 0;
                    primary->speed = 0x80;
                    primary->unk9A = 0;
                    func_001CDEB0(primary);
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
            node = (Node_001D82C0 *)(index * 0xA0 + D_0031A7C0);
        }
        if (node != NULL && node->model != NULL) {
            s32 result = func_001DF0C0(arg0, i);
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
                func_00205CB0(&node->position, (f32)baseX, -8.0f);
                func_00205CB0(&node->target, (f32)x, (f32)y);
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
                func_001CDEB0(node);
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

static inline Slot_001D8880 *lookup_001D8880(s32 index) {
    if (index < 0 || index >= 6) {
        return NULL;
    }
    return (Slot_001D8880 *) (D_0031A7C0 + index * 0xA0);
}

s32 func_001D8880(s32 arg0, s32 arg1) {
    extern s32 func_001DE4E0();
    s32 i;
    Slot_001D8880 *slot;
    Model_001D8880 *model;
    s32 level;
    s32 limit;
    s32 other;
    s32 bits;
    s32 flag;

    bits = func_001A82E0(0x1D);
    flag = (bits & (1 << arg0)) ? 1 : 0;
    other = arg0 ^ 1;
    if (flag) {
        if (func_001DE4E0(arg0) < 0x20 && func_001DE4E0(other) >= 0x64) {
            arg1 = 0;
        }
    } else if ((u16) func_00203A40(arg0, 1, 2) == 0) {
        arg1 = 0;
    }

    for (i = 0; i < 6; i++) {
        slot = lookup_001D8880(i);
        if (slot != NULL && slot->model != NULL) {
            model = slot->model;
            level = func_001DE5C0(arg0);
            limit = func_001E0950(slot->model->unk90, 0);
            if (arg1 != 0 && level < limit) {
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

static inline Slot_001D89F0 *lookupSlot_001D89F0(s32 index) {
    if (index < 0 || index >= 6) {
        return NULL;
    }
    return (Slot_001D89F0 *)(D_0031A7C0 + index * 0xA0);
}

static inline Model_001D89F0 *allocateModel_001D89F0(void) {
    extern void func_001CD560();
    Model_001D89F0 *candidate;
    s32 i;

    candidate = (Model_001D89F0 *)D_003193C0;
    i = 0;
    do {
        if (candidate->owner == NULL) {
            func_001CD560(candidate);
            return candidate;
        }
        i++;
        candidate++;
    } while (i < 32);
    return NULL;
}

s32 func_001D89F0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    extern void *func_001DD130();
    u8 *player;
    Entry_001D89F0 *entry;
    Slot_001D89F0 *slot;
    Model_001D89F0 *model;

    player = D_00317490.b + arg0 * 0x350;
    entry = func_001DD130(2, arg1);
    if (entry == NULL) {
        return 0;
    }
    func_001DCD70(entry, arg2);
    entry->player = arg0;
    entry->slot = arg1;
    entry->field40 = player[0x33D];
    entry->field41 = player[0x33E];
    if (entry->id != 999) {
        slot = lookupSlot_001D89F0(arg1);
        entry->field48 = func_0026EA80(arg0, entry->id);
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
                func_00205C40((s32)model->rotation);
                slot->status.flags.bit2 = 1;
                slot->status.flags.bit3 = 1;
                func_001D8FB0(slot, arg3, arg4, arg5, arg6, 0, 0x80);
                slot->status.index.slot = arg1;
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

static inline u8 *allocate_001D8CD0(void) {
    extern void func_001CD560();
    u8 *p = D_003193C0;
    s32 i = 0;

    do {
        if (*(s32 *)(p + 0x90) == 0) {
            func_001CD560(p);
            return p;
        }
        i++;
        p += 0xA0;
    } while (i < 32);
    return NULL;
}

s32 func_001D8CD0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    extern void *func_001DD130();
    u8 *player;
    u8 *object;
    u8 *entry;
    u8 *resource;

    player = D_00317490.b + arg0 * 0x350;
    object = func_001DD130(2, arg1);
    if (object == NULL) {
        return 0;
    }
    func_001DCD70(object, arg2);
    *(s8 *)(object + 0x44) = arg0;
    *(s8 *)(object + 0x45) = arg1;
    *(u8 *)(object + 0x40) = *(u8 *)(player + 0x33D);
    *(u8 *)(object + 0x41) = *(u8 *)(player + 0x33E);
    if (*(u16 *)(object + 0x3C) != 999) {
        if (arg1 < 0 || arg1 >= 6) {
            entry = NULL;
        } else {
            entry = D_0031A7C0 + arg1 * 0xA0;
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
                func_00205C40((s32)(resource + 0x20));
                ((Flags_001D8CD0 *)(entry + 0x9F))->bit2 = 0;
                ((Flags_001D8CD0 *)(entry + 0x9F))->bit3 = 1;
                func_001D9030(entry, arg3, arg4, arg3, arg4, 128, 128);
                ((Index_001D8CD0 *)(entry + 0x9C))->index = arg1;
            }
        }
        *(s8 *)(object + 0x48) = func_0026EA80(arg0, *(u16 *)(object + 0x3C));
    }
    ((Flags_001D8CD0 *)(object + 0x57))->bit7 = 1;
    ((Flags_001D8CD0 *)(object + 0x58))->bit0 = 1;
    ((Flags_001D8CD0 *)(object + 0x58))->bit2 = 1;
    return 1;
}

s32 func_001D8FB0(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    if (arg0 == NULL) {
        return 0;
    }
    *(f32 *)((u8 *)arg0 + 0x10) = (f32) arg1;
    *(f32 *)((u8 *)arg0 + 0x14) = (f32) arg2;
    *(s32 *)((u8 *)arg0 + 0x18) = 0;
    *(s32 *)((u8 *)arg0 + 0x1C) = 0;
    *(f32 *)((u8 *)arg0 + 0x20) = (f32) arg3;
    *(f32 *)((u8 *)arg0 + 0x24) = (f32) arg4;
    *(s32 *)((u8 *)arg0 + 0x28) = 0;
    *(s32 *)((u8 *)arg0 + 0x2C) = 0;
    *(s16 *)((u8 *)arg0 + 0x98) = (s16) arg6;
    *(s16 *)((u8 *)arg0 + 0x9A) = (s16) arg5;
    func_001CDEB0(arg0);
    return 1;
}

s32 func_001D9030(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    if (arg0 == NULL) {
        return 0;
    }
    func_00205CB0((u8 *) arg0 + 0x10, (f32) arg1, (f32) arg2);
    func_00205CB0((u8 *) arg0 + 0x20, (f32) arg3, (f32) arg4);
    *(s16 *)((u8 *) arg0 + 0x98) = (s16) arg6;
    *(s16 *)((u8 *) arg0 + 0x9A) = (s16) arg5;
    func_001CDEB0(arg0);
    return 1;
}

void func_001D90E0(s32 arg0, s32 arg1, s32 arg2) {
    f32 sp50[4];
    f32 sp60[4];
    u8 *temp_s3;

    temp_s3 = D_00317490.b + (D_003181E4 * 0x350);
    func_001FC950(temp_s3 + 0x1D0, sp50);
    sp60[0] = (f32) arg1;
    sp60[2] = (f32) arg2;
    sp60[1] = (f32) *(s8 *)(temp_s3 + 0x345);
    func_001FA8A0(0, 0, 3, (u16)arg0, 0, sp60);
    func_001FA8A0(0, 0, 4, arg0 & 0xFFFF, 0, sp50);
}

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4_001D91B0;

void func_001D91B0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
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

    p = D_00317490.b + D_003181E4 * 0x350;
    saved = *(Vec4_001D91B0 *)(p + 0x1D0);
    x0 = (s32)(f32)((arg1 - 3) * 50);
    z0 = (s32)(f32)((arg2 - 3) * 50);
    x1 = (s32)(f32)((arg3 - 3) * 50);
    z1 = (s32)(f32)((arg4 - 3) * 50);
    angle = (s32)(65536.0f * (func_001A6C18((f32)(z1 - z0), (f32)(x1 - x0)) / 6.2831855f));
    *(s32 *)(p + 0x1D0) = 0x96;
    *(s32 *)(p + 0x1D4) = (((angle + 0x80) >> 8) << 8) + 0x4000;
    *(s32 *)(p + 0x1D8) = 0x3800;
    cur = D_00317490.b + D_003181E4 * 0x350;
    func_001FC950(cur + 0x1D0, camera);
    pos[0] = (f32)((x0 + x1) >> 1);
    pos[2] = (f32)((z0 + z1) >> 1);
    pos[1] = (f32)*(s8 *)(cur + 0x345);
    func_001FA8A0(0, 0, 3, (u16)arg0, 0, pos);
    func_001FA8A0(0, 0, 4, arg0 & 0xFFFF, 0, camera);
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

s32 func_001D9420(void *arg0) {
    u8 *duel = D_00317490.b;
    s32 result;
    void **cell;
    s32 me;
    s32 other;
    s32 flag;
    Card_001D9420 *card = arg0;
    s32 target;
    s32 bits;
    extern s32 func_001DE4E0();

    result = 0;
    if (card != NULL) {
        cell = func_001DCD00(card->x, card->y);
        bits = func_001A82E0(0x1D);
        flag = (bits & (1 << card->owner)) ? 1 : 0;
        me = duel[0xD3C];
        other = duel[0xD3C] ^ 1;
        if (card->owner >= 2) {
            return 0;
        }
        if (cell == NULL || *cell != card) {
            if (flag) {
                if (func_001DE4E0(me) < 0x20 && func_001DE4E0(other) >= 0x64) {
                    result = 1;
                }
            } else if ((u16) func_00203A40(duel[0xD3C], 1, 2) == 0) {
                result = 1;
            }
        } else {
            result = func_00267380((s32) card, duel[0xD3C]);
            if (result == 0 && card->flag == 0) {
                target = func_00250360(card->owner, card->slot);
                if (flag) {
                    if (func_001DE4E0(me) < 0x20 && func_001DE4E0(other) >= 0x64 && func_001DE4E0(target) < 0x20) {
                        result = 1;
                    }
                } else if (duel[0xD3C] == target) {
                    if ((u16) func_00203A40(duel[0xD3C], 1, 2) == 0) {
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

void func_001D95F0(void) {
    u8 *p = D_00318200;
    if (func_00203A40(0, 2, 0x1000) != 0) {
        *(s32 *)(p + 0x5C) = (*(s32 *)(p + 0x5C) + 0x10400) % 0x10000;
    }
    if (func_00203A40(0, 2, 0x4000) != 0) {
        *(s32 *)(p + 0x5C) = (*(s32 *)(p + 0x5C) + 0xFC00) % 0x10000;
    }
    if (func_00203A40(0, 2, 0x2000) != 0) {
        *(s32 *)(p + 0x60) = (*(s32 *)(p + 0x60) + 0x10400) % 0x10000;
    }
    if (func_00203A40(0, 2, 0x8000) != 0) {
        *(s32 *)(p + 0x60) = (*(s32 *)(p + 0x60) + 0xFC00) % 0x10000;
    }
    if (func_00203A40(0, 2, 8) != 0) {
        *(s32 *)(p + 0x64) = (*(s32 *)(p + 0x64) + 0x10400) % 0x10000;
    }
    if (func_00203A40(0, 2, 4) != 0) {
        *(s32 *)(p + 0x64) = (*(s32 *)(p + 0x64) + 0xFC00) % 0x10000;
    }
    if (func_00203A40(0, 2, 2) != 0) {
        *(s32 *)(p + 0x70) = (*(s32 *)(p + 0x70) + 0x357) % 854;
    }
    if (func_00203A40(0, 2, 1) != 0) {
        *(s32 *)(p + 0x70) = (*(s32 *)(p + 0x70) + 0x355) % 854;
    }
    if (func_00203A40(0, 0, 0x10) != 0) {
        func_00205210();
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

void func_001D9820(s32 arg0, s32 arg1) {
    extern s32 func_001A22C0(f32);
    State_001D9820 *state = (State_001D9820 *)D_00317490.b;
    Player_001D9820 *p;
    s32 x;
    s32 z;
    Player_001D9820 *cur;
    f32 pos[4];
    f32 saved[4];

    D_003181E4 = arg1;
    p = (Player_001D9820 *)(D_00317490.b + arg1 * 0x350);
    z = func_001A22C0((f32)((p->z - 3) * 50));
    x = func_001A22C0((f32)((p->x - 3) * 50));
    cur = (Player_001D9820 *)(D_00317490.b + D_003181E4 * 0x350);
    func_001FC950(cur->f1D0, saved);
    pos[0] = (f32)x;
    pos[2] = (f32)z;
    pos[1] = (f32)cur->y;
    func_001FA8A0(0, 0, 3, 0x20, 0, pos);
    func_001FA8A0(0, 0, 4, 0x20, 0, saved);
    p->active = 1;
    if (func_0027F830(arg1) != 0) {
        p = state->players;
    }
    func_00275E30(p);
    state->flagD66 = 1;
    state->flagD67 = state->flagD66;
}

void func_001D99F0(void) {
    func_00209D30(func_001D9A20(func_00209D20()));
}

s32 func_001D9A20(s32 arg0) {
    return func_001D9A30(arg0, 2);
}

typedef struct {
    s8 low : 5;
    s8 bit5 : 1;
    s8 high : 2;
} Flags_001D9A30;


s32 func_001D9A30(s32 arg0, s32 arg1) {
    extern s32 func_00202E00();
    extern s32 func_00202BF0();
    extern s32 *func_001FEAB0(s32);
    extern s32 func_0020A610();
    extern s32 func_0020A870();
    extern s32 func_0020A760();
    u8 *base = D_00317490.b;
    s32 sprite;
    s32 length;
    s32 i;
    s32 result;

    func_0020A470(3, 2, 0x32);
    arg0 = func_0020A610(arg0);
    arg0 = func_0020A870(arg0, 0);
    sprite = func_0020A760(arg0);
    arg0 = func_00209E50();
    arg0 += func_00202E00(arg0, 2);
    sprite = func_001FD320(sprite, arg1, arg0, &length);
    i = 0;
    arg0 += length;
    do {
        *(s32 *)(base + i * 4 + 0x6A0) = 0;
        i++;
    } while (i < 9);
    *(s32 *)(base + 0x6B0) = func_00202BF0(3, 4);
    *(s32 *)(base + 0x6B4) = func_00202BF0(3, 5);
    *(s32 *)(base + 0x6B8) = func_00202BF0(3, 6);
    sprite = func_00202B00(sprite, 3, arg0, &length);
    arg0 += length;
    func_00202D60(3, -1);
    *(s32 *)(base + 0xC80) = arg0;
    arg0 += func_00202E00(arg0, 1);
    *(s32 *)(base + 0x6A0) = func_00202BF0(3, 0);
    sprite = func_00202B00(sprite, 3, arg0, &length);
    arg0 += length;
    func_00202D60(3, 0);
    {
        s32 *info;

        sprite = func_001FD680(sprite, 0, 0x15, 0, 0);
        info = func_001FEAB0(0);
        info[3] = 0x16;
        sprite = func_001FD680(sprite, 1, 0xA1, 0, 0x16);
        result = func_0020F290(func_001FD680(sprite, 2, 0xA2, 0, 0x2C));
    }
    *(s32 *)(base + 0xC7C) = arg0;
    *(s32 *)(base + 0xC54) = 0;
    ((Flags_001D9A30 *)(base + 0xD64))->bit5 = 0;
    return result;
}

typedef struct {
    u8 pad000[0x6A0];
    s32 slots[8];
    s32 count;
} State_001D9C40;

s32 func_001D9C40(s32 arg0, s32 arg1) {
    extern s32 func_00202E00();
    extern s32 func_00202BF0();
    extern s32 D_00317B30[];
    extern s32 D_00318110;
    State_001D9C40 *state;
    s32 value;
    s32 i;

    state = (State_001D9C40 *)D_00317490.b;
    value = D_00318110;
    if (D_00317B30[arg1] != 0) {
        return arg0;
    }
    if (arg1 >= 0 && arg1 < 4) {
        i = 0;
        while (1) {
            state->slots[i] = 0;
            i++;
            if (i > 3) {
                break;
            }
        }
        state->count = 0;
        value += func_00202E00(value, 1);
        state->slots[arg1] = func_00202BF0(3, arg1);
        arg0 = func_00202B00(arg0, 3, value, NULL);
        func_00202D60(3, arg1);
        arg0 = func_0020F290(arg0);
    } else if (arg1 == 8) {
        i = 0;
        while (1) {
            state->slots[i] = 0;
            i++;
            if (i > 3) {
                break;
            }
        }
        value += func_00202E00(value, 1);
        state->slots[arg1] = func_00202BF0(9, 0);
        arg0 = func_00202B00(arg0, 9, value, NULL);
        func_00202D60(9, 0);
        arg0 = func_0020F290(arg0);
    }
    return arg0;
}

void func_001D9DD0(void) {
    func_00209D30(func_001D9E00(func_00209D20()));
}

s32 func_001D9E00(s32 arg0) {
    extern s32 func_002084D0();
    s32 temp_s0;
    s32 temp_s0_2;

    func_0020A9E0();
    temp_s0_2 = func_0020A0B0(arg0, 0);
    temp_s0 = func_002084D0(temp_s0_2, func_00208680(0, 4));
    func_001FEAF0(0);
    func_001FEAF0(1);
    func_001FEAF0(2);
    return temp_s0;
}

s32 func_001D9E70(s32 arg0) {
    extern s32 func_002084D0();
    s32 temp_s0;

    func_0020A9E0();
    temp_s0 = func_002084D0(arg0, func_00208680(0, 4));
    func_001FEAF0(0);
    func_001FEAF0(1);
    func_001FEAF0(2);
    return temp_s0;
}

void func_001D9ED0(s32 arg0) {
    D_003180E4 = arg0;
}

void func_001D9EE0(s32 arg0) {
    D_003180E8 = arg0;
}

s32 func_001D9EF0(void) {
    return D_0031810C;
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


s32 func_001D9F00(void *arg0, s32 arg1) {
    Vec_001D9F00 point;
    Vec_001D9F00 transformed;
    __int128 matrix[4];
    __int128 projection[4];
    u8 *state = D_00317490.b;
    s32 mode;
    Object_001D9F00 *object = arg0;
    s32 i;
    s32 offset;
    extern s64 func_001DA4C0();
    extern s64 func_002070F0(void *, s32, void *, s32, s32, s32, s32);

    point = D_00291540;
    mode = arg1 ? 15 : -1;
    func_0020BAF0(0);
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
        func_0020C940(rotationMatrix, NULL, object->rotation, object);
        func_0020C630(translationMatrix, &height);
        func_0020BCF0((s32)translationMatrix, (s32)rotationMatrix);
        func_0020C940(matrix, orientation, &position, NULL);
        func_0020BCF0((s32)matrix, (s32)translationMatrix);
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
        func_0020C940(rotationMatrix, NULL, &height, object);
        func_0020C940(matrix, orientation, &position, NULL);
        func_0020BCF0((s32)matrix, (s32)rotationMatrix);
    }
    func_0020EBA0(projection);
    func_0020BC00((s32)projection, matrix);
    func_0020CDD0(&point, projection, &point);
    object->field4A = 0x35;
    object->field48 = 0;
    object->field50 = 0;
    object->field4C = 0;
    func_002086D0(&object->field48, 0x8000000044LL);
    if (object->control80.bytes.flags.mode) {
        func_00208CB0(&object->field48, 0x5C00040000ALL);
    } else {
        func_00208CB0(&object->field48, 0x2D0001E000ALL);
    }
    object->count82.value = (s16)func_001DA4C0(object->control80.bytes.flags.mode, object->vertices);
    object->count82.value = (s16)func_002070F0(projection, object->count82.value, object->vertices, object->control80.count.value, object->field7C, mode, 0);
    func_002061F0(NULL, object->count82.value, object->vertices, transformed.f);
    func_00207230(NULL, object->count82.value, object->vertices);
    if (*(s32 *)(state + 0xC54) != 0) {
        for (i = 0, offset = 0; i < object->count82.value; i++, offset += 0x30) {
            ((Packet_001D9F00 *)(object->vertices + offset + 0x10))->color = *(u32 *)(state + 0xC54);
        }
    }
    func_0020BB50();
    return func_0020D1A0(transformed.f, point.f) <= 0.0f ? 0 : 1;
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

s32 func_001DA2B0(void *arg0, s32 arg1, f32 fparg0, f32 fparg1) {
    Object_001DA2B0 *object;
    void *temp_s1;
    u8 *global;

    object = arg0;
    global = D_00317490.b;
    temp_s1 = (object->field80.bytes.flags.flag6 == 0) ? NULL : ((u8 *) object + 0x30);
    object->field4A = 0x35;
    object->field48 = 0;
    object->field50 = 0;
    object->field4C = 0;
    func_002086D0(&object->field48, ((s64) 0x80 << 32) | 0x44);
    if (object->field80.bytes.flags.flag4 != 0) {
        func_00208CB0(&object->field48, ((s64) 0x5C0 << 32) | 0x40000A);
    } else {
        func_00208CB0(&object->field48, ((s64) 0x2D0 << 32) | 0x1E000A);
    }
    object->field82.count = (s16) func_001DA5E0(
            object->field80.bytes.flags.flag4,
            fparg0,
            fparg1,
            object->vertices,
            temp_s1);
    if (arg1 != 0) {
        extern s32 func_00206D00();
        object->field82.count = (s16) func_00206D00(
                object->field82.count,
                object->vertices,
                object->field80.bits.count,
                object->field7C,
                0xF);
    }
    {
        extern void func_00207230();
        func_00207230(NULL,
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

s32 func_001DA4C0(s32 mode, void *dst) {
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

s32 func_001DA5E0(s32 arg0, f32 x, f32 y, void *arg1, void *arg2) {
    f32 *scale = arg2;
    f32 width;
    f32 height;
    f32 halfWidth;
    f32 halfHeight;
    f32 z;
    Vertex_001DA5E0 *vertex;

    width = arg0 ? 256 : 120;
    height = arg0 ? 368 : 180;
    vertex = arg1;
    halfWidth = (scale ? width * scale[0] : width) / 2.0f;
    halfHeight = (scale ? height * scale[1] : height) / 2.0f;
    z = func_001F9A20(0);

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

void func_001DA7A0(s32 arg0, s32 arg1) {
    func_00209D30(func_001DA7F0(func_00209D20(), arg0, arg1));
}

INCLUDE_ASM("asm/nonmatchings/main_043", func_001DA7F0);

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

s32 func_001DBC40(s32 arg0, s32 arg1, void *arg2) {
    s32 i;
    Data_001DBC40 *data = arg2;

    arg0 = func_001DA7F0(arg0, arg1, (s32)arg2);
    if (data->update) {
        for (i = 0; i < data->count; i++) {
            data->packets[i].red = data->red;
            data->packets[i].green = data->green;
            data->packets[i].blue = data->blue;
            data->packets[i].alpha = data->alpha;
        }
    }
    return arg0;
}

void func_001DBCF0(s32 arg0) {
    func_00209D30(func_001DBD30(func_00209D20(), arg0));
}

typedef struct {
    u8 pad_00[0x48];
    u8 data[0x30];
    s32 value;
    u8 pad_7C[6];
    s16 index : 12;
    s16 unused : 4;
} Params_001DBD30;

s32 func_00207AA0(s32, void *, s32, s32, s32, s32);

s32 func_001DBD30(s32 arg0, s32 arg1) {
    Params_001DBD30 *params = (Params_001DBD30 *)arg1;

    return func_00207AA0(arg0, params->data, params->index,
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

s32 func_00207AA0(s32, void *, s32, s32, s32, s32);

static inline void initPrim_001DBD50(s32 kind, void *prim) {
    ((Prim_001DBD50 *)prim)->kind = kind;
    ((Prim_001DBD50 *)prim)->flags = 0;
    ((Prim_001DBD50 *)prim)->value = 0;
    ((Prim_001DBD50 *)prim)->pad = 0;
}

s32 func_001DBD50(s32 arg0, f32 *position, f32 width, f32 height,
                   s32 arg2, u8 *color, s32 arg4) {
    void *scratchpad = (void *)0x70000000;
    Vertex_001DBD50 *vertices = (Vertex_001DBD50 *)((u8 *)scratchpad + 0x2000);
    s32 repeats = 2;
    s32 count;
    s32 original = arg0;
    Prim_001DBD50 prim;
    u8 *end;

    arg0 = func_00207FA0(arg0);
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
        count = func_002070F0(0, 5, vertices, 0xAA, scratchpad, 0, 0);
        func_00207230(NULL, count, vertices);
        if (arg4 != 0) {
            initPrim_001DBD50(5, &prim);
        } else {
            initPrim_001DBD50(0x402, &prim);
        }
        if (vertices[0].a < 0xFF) {
            func_002086D0(&prim, func_00208D00(arg2));
        }
        arg0 = func_00207AA0(arg0, &prim, count, (s32)vertices, 0, 0);
        if (arg4 != 0 || repeats-- <= 0) {
            break;
        }
        width -= 0.2f;
        height -= 0.2f;
    } while (1);
    end = func_00207500();
    return func_00208030(arg0, original, (s32)end, func_00205D10(position, 0.0f));
}

typedef struct Primitive_001DBFE0 {
    u16 mode;
    u16 flags;
    s32 reserved;
    s64 state;
    s64 extra[4];
} Primitive_001DBFE0;

static inline void init_001DBFE0(void *prim, s32 flags) {
    ((u16 *)prim)[1] = flags;
    ((u16 *)prim)[0] = 0;
    ((s64 *)prim)[1] = 0;
    ((s32 *)prim)[1] = 0;
}

s32 func_00207AA0(s32, void *, s32, s32, s32, s32);

void func_001DBFE0(s32 arg0, f32 *arg1, u8 *arg2, s32 arg3) {
    Primitive_001DBFE0 sp50;
    f32 temp_f20;
    f32 height = 35.0f;
    f32 half_width = 24.0f;
    s32 temp_s1;
    s32 temp_s1_2;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_s2;

    *(u8 *)0x70002018 = 0;
    *(u8 *)0x70002019 = 0;
    *(u8 *)0x7000201A = 0;
    *(u8 *)0x7000201B = 0xFF;
    if (arg2 != NULL) {
        *(u8 *)0x70002018 = arg2[2];
        *(u8 *)0x70002019 = arg2[1];
        *(u8 *)0x7000201A = arg2[0];
        *(u8 *)0x7000201B = arg2[3];
    }
    *(s32 *)0x7000201C = 0x3F800000;
    if (arg3 != 0) {
        init_001DBFE0(&sp50, 5);
    } else {
        init_001DBFE0(&sp50, 2);
    }
    if (*(u8 *)0x7000201B != 0xFF) {
        func_002086D0(&sp50, 0x48 | ((s64)0x80 << 32));
    }
    *(f32 *)0x70002000 = arg1[0] - half_width;
    temp_f20 = -height;
    *(f32 *)0x70002004 = arg1[1] - height;
    *(f32 *)0x70002008 = arg1[2] - half_width;
    *(f32 *)0x70002030 = arg1[0] - half_width;
    *(f32 *)0x70002034 = temp_f20;
    *(f32 *)0x70002038 = arg1[2] - half_width;
    *(f32 *)0x70002060 = arg1[0] + half_width;
    *(f32 *)0x70002064 = temp_f20;
    *(f32 *)0x70002068 = arg1[2] - half_width;
    *(f32 *)0x70002090 = arg1[0] + half_width;
    *(f32 *)0x70002094 = arg1[1] - height;
    *(f32 *)0x70002098 = arg1[2] - half_width;
    temp_v0 = func_002070F0(0, 4, (void *)0x70002000, 0xAA, (void *)0x70000000, 0, 0);
    func_00207230(NULL, temp_v0, (void *)0x70002000);
    temp_s1 = func_00207AA0(arg0, &sp50, temp_v0, 0x70002000, 0, 0);
    *(f32 *)0x70002000 = (arg1[0] - half_width);
    *(f32 *)0x70002004 = (arg1[1] - height);
    *(f32 *)0x70002008 = (arg1[2] + half_width);
    *(f32 *)0x70002030 = (arg1[0] - half_width);
    *(f32 *)0x70002034 = temp_f20;
    *(f32 *)0x70002038 = (arg1[2] + half_width);
    *(f32 *)0x70002060 = (arg1[0] + half_width);
    *(f32 *)0x70002064 = temp_f20;
    *(f32 *)0x70002068 = (arg1[2] + half_width);
    *(f32 *)0x70002090 = (arg1[0] + half_width);
    *(f32 *)0x70002094 = (arg1[1] - height);
    *(f32 *)0x70002098 = (arg1[2] + half_width);
    temp_v0_2 = func_002070F0(0, 4, (void *)0x70002000, 0xAA, (void *)0x70000000, 0, 0);
    func_00207230(NULL, temp_v0_2, (void *)0x70002000);
    temp_s2 = func_00207AA0(temp_s1, &sp50, temp_v0_2, 0x70002000, 0, 0);
    *(f32 *)0x70002000 = (arg1[0] - half_width);
    *(f32 *)0x70002004 = (arg1[1] - height);
    *(f32 *)0x70002008 = (arg1[2] - half_width);
    *(f32 *)0x70002030 = (arg1[0] - half_width);
    *(f32 *)0x70002034 = temp_f20;
    *(f32 *)0x70002038 = (arg1[2] - half_width);
    *(f32 *)0x70002060 = (arg1[0] - half_width);
    *(f32 *)0x70002064 = temp_f20;
    *(f32 *)0x70002068 = (arg1[2] + half_width);
    *(f32 *)0x70002090 = (arg1[0] - half_width);
    *(f32 *)0x70002094 = (arg1[1] - height);
    *(f32 *)0x70002098 = (arg1[2] + half_width);
    temp_v0_3 = func_002070F0(0, 4, (void *)0x70002000, 0xAA, (void *)0x70000000, 0, 0);
    func_00207230(NULL, temp_v0_3, (void *)0x70002000);
    temp_s1_2 = func_00207AA0(temp_s2, &sp50, temp_v0_3, 0x70002000, 0, 0);
    *(f32 *)0x70002000 = (arg1[0] + half_width);
    *(f32 *)0x70002004 = (arg1[1] - height);
    *(f32 *)0x70002008 = (arg1[2] - half_width);
    *(f32 *)0x70002030 = (arg1[0] + half_width);
    *(f32 *)0x70002034 = temp_f20;
    *(f32 *)0x70002038 = (arg1[2] - half_width);
    *(f32 *)0x70002060 = (arg1[0] + half_width);
    *(f32 *)0x70002064 = temp_f20;
    *(f32 *)0x70002068 = (arg1[2] + half_width);
    *(f32 *)0x70002090 = (arg1[0] + half_width);
    *(f32 *)0x70002094 = (arg1[1] - height);
    *(f32 *)0x70002098 = (arg1[2] + half_width);
    temp_v0_4 = func_002070F0(0, 4, (void *)0x70002000, 0xAA, (void *)0x70000000, 0, 0);
    func_00207230(NULL, temp_v0_4, (void *)0x70002000);
    func_00207AA0(temp_s1_2, &sp50, temp_v0_4, 0x70002000, 0, 0);
}

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
struct DotrStateCell *func_001DCD00_b(int x, int y);

int func_001DC560(int cursor)
{
    int x;
    int y;
    struct DotrStateCell *cell;
    float pos[4];
    float dx;
    float dz;
    struct DotrStateCellQuad c0;
    struct DotrStateCellQuad c1;

    if (func_001F3130(0) == 0) {
        return cursor;
    }
    for (y = 0; y < 7; y++) {
        for (x = 0; x < 7; x++) {
            cell = func_001DCD00_b(x, y);
            c0 = cell->unknown_04[1];
            c1 = cell->unknown_04[3];
            c0.unknown_2 = (c0.unknown_2 * cell->unknown_1a) >> 7;
            c0.unknown_1 = (c0.unknown_1 * cell->unknown_1a) >> 7;
            c0.unknown_0 = (c0.unknown_0 * cell->unknown_1a) >> 7;
            c1.unknown_2 = (c1.unknown_2 * cell->unknown_1a) >> 7;
            c1.unknown_1 = (c1.unknown_1 * cell->unknown_1a) >> 7;
            c1.unknown_0 = (c1.unknown_0 * cell->unknown_1a) >> 7;
            pos[0] = (x - 3) * 50;
            pos[2] = (y - 3) * 50;
            pos[1] = -0.2f;
            if (c0.unknown_3 != 0) {
                dz = dx = 24.0f;
                cursor = func_001DBD50(cursor, pos, dx, dz, cell->unknown_19, &c0.unknown_0, 1);
            }
            pos[1] = -0.1f;
            if (c1.unknown_3 != 0) {
                dz = dx = 24.0f;
                cursor = func_001DBD50(cursor, pos, dx, dz, 1, &c1.unknown_0, 0);
            }
        }
    }
    return cursor;
}

typedef struct {
    s8 unused : 7;
    s8 set : 1;
} Flag7_001DC790;

typedef struct {
    s8 unused : 1;
    s8 set : 1;
    s8 rest : 6;
} Flag1_001DC790;

typedef struct {
    u8 pad0[4];
    s32 state;
    u8 pad8[0x38];
    u8 x, y;
    u8 pad42[4];
    u8 angle;
    u8 pad47[6];
    u8 intensity;
    u8 pad4E[9];
    Flag7_001DC790 flag7;
    Flag1_001DC790 flag1;
} Card_001DC790;

typedef struct {
    u8 pad0[0x10];
    u8 blue, green, red;
    u8 pad13[7];
    u8 intensity;
} Info_001DC790;

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

void func_0020CF00(void *, s32, void *, s32);
extern Points_001DC790 D_00291590;
extern u8 D_00290000[];
extern u8 D_003181C4;

s32 func_001DC790(s32 arg0, s32 arg1, f32 *arg2, s32 arg3, s32 arg4) {
    s16 *type;
    s64 *bits;
    s32 *data;
    Points_001DC790 points;
    f32 rotation[4];
    Points_001DC790 matrix;
    Packet_001DC790 packet;
    Gfx_001DC790 *textures = (Gfx_001DC790 *)D_00317490.b;
    f32 u;
    u8 *entry;
    f32 scale;
    s32 count;
    Card_001DC790 *card;
    Info_001DC790 *info;
    u8 intensity;

    card = (Card_001DC790 *)func_001DF540(arg1, 0);
    scale = 16.666666f;
    scale = (scale * D_003181C4) / 128.0f;
    points = D_00291590;
    points.v[0][0] = scale;
    points.v[0][2] = scale;
    points.v[1][0] = scale;
    points.v[1][2] = -scale;
    points.v[2][0] = -scale;
    points.v[2][2] = -scale;
    points.v[3][0] = -scale;
    points.v[3][2] = scale;
    if (arg1 != 0) {
        u = 0.5f;
    } else {
        u = 0.0f;
    }
    entry = &D_00290000[arg1 * 10];
    intensity = 0x80;
    if (card == NULL) {
        return arg0;
    }
    if (card->state != 0) {
        return arg0;
    } else {
        info = func_001DCD00(card->x, card->y);
        if (card->flag7.set == 0 && card->flag1.set == 0) {
            intensity = info->intensity;
        }
        func_001F2330(card->angle, rotation);
        rotation[2] = 0;
        rotation[0] = 0;
        func_0020C630(&matrix, rotation);
        func_0020BAF0((s32)&matrix);
        func_0020CF00(&points, 0, &points, 4);
        func_0020BB50();
        *(s16 *)((s32)&packet + 2) = 0x35;
        type = (s16 *)((s32)&packet + 2);
        bits = (s64 *)((s32)&packet + 8);
        data = (s32 *)((s32)&packet + 4);
        *(s16 *)(s32)&packet = 0;
        *(s64 *)((s32)&packet + 8) = 0;
        *(s32 *)((s32)&packet + 4) = 0;
        func_002086D0(&packet, 0x8000000044LL);
        func_00208700(&packet, textures->textures[entry[0]], 1);
        {
            s32 first;
            u32 i = 0;
            Vertex_001DC790 *vertex = (Vertex_001DC790 *)0x70002000;
            f32 *p = points.v[0];
            intensity = (u8)intensity;
            do {
                first = 1;
                vertex->red = vertex->green = vertex->blue = (card->intensity * intensity) >> 7;
                vertex->alpha = arg3;
                vertex->q = 1.0f;
                if (i > 1U) {
                    first = 0;
                }
                vertex->u = u + (first ? 0.0f : 0.5f);
                vertex->v = (i == 0 || i == 3) ? 0.0f : 1.0f;
                i++;
                vertex->x = arg2[0] + p[0];
                vertex->y = arg2[1] + p[1];
                vertex->z = arg2[2] + p[2];
                p += 4;
                vertex++;
            } while ((s32)i < 4);
            count = func_002070F0(0, i, (void *)0x70002000, 0xAA, (void *)0x70000000, 0xF, 0);
            func_00207230(0, count, (void *)0x70002000);
            arg0 = func_00207AA0(arg0, &packet, count, 0x70002000, 0, 0);
            if (arg4 != 0) {
                Vertex_001DC790 *vertex2;
                s32 j;
                *type = 0x402;
                *(s16 *)(s32)&packet = 0;
                *bits = 0;
                *data = 0;
                func_002086D0(&packet, 0x8000000048LL);
                *(u8 *)0x70002018 = (info->red * intensity) >> 7;
                *(u8 *)0x70002019 = (info->green * intensity) >> 7;
                *(u8 *)0x7000201A = (info->blue * intensity) >> 7;
                *(u8 *)0x7000201B = arg3;
                *(f32 *)0x7000201C = 1.0f;
                vertex2 = (Vertex_001DC790 *)0x70002000;
                j = 0;
                do {
                    vertex2->x = arg2[0] + points.v[j % 4][0];
                    vertex2->y = arg2[1] + points.v[j % 4][1];
                    vertex2->z = arg2[2] + points.v[j % 4][2];
                    j++;
                    vertex2++;
                } while (j < 5);
                count = func_002070F0(0, j, (void *)0x70002000, 0xAA, (void *)0x70000000, 0xF, 0);
                func_00207230(0, count, (void *)0x70002000);
                arg0 = func_00207AA0(arg0, &packet, count, 0x70002000, 0, 0);
            }
        }
    }
    return arg0;
}

void func_001DCC90(void *arg0) {
    *(s32 *)arg0 = 0;
    ((u8 *)arg0)[6] = 0;
    ((u8 *)arg0)[5] = 0;
    ((u8 *)arg0)[4] = 0;
    ((u8 *)arg0)[7] = 0;
    ((u8 *)arg0)[0xA] = 0;
    ((u8 *)arg0)[9] = 0;
    ((u8 *)arg0)[8] = 0;
    ((u8 *)arg0)[0xB] = 0;
    ((u8 *)arg0)[0xE] = 0;
    ((u8 *)arg0)[0xD] = 0;
    ((u8 *)arg0)[0xC] = 0;
    ((u8 *)arg0)[0xF] = 0;
    ((u8 *)arg0)[0x12] = 0;
    ((u8 *)arg0)[0x11] = 0;
    ((u8 *)arg0)[0x10] = 0;
    ((u8 *)arg0)[0x13] = 0;
    ((u8 *)arg0)[0x16] = 0;
    ((u8 *)arg0)[0x17] = 0;
    ((u8 *)arg0)[0x18] = 0;
    ((u8 *)arg0)[0x19] = 0;
    ((u8 *)arg0)[0x1A] = 0x80;
    *(s16 *)((u8 *)arg0 + 0x14) = 0;
}

void *func_001DCD00(s32 arg0, s32 arg1) {
    if ((arg0 < 0) || (arg0 >= 7) || (arg1 < 0) || (arg1 >= 7)) {
        return NULL;
    }
    return (arg0 * 0x1C) + (D_00318E60 + (arg1 * 0xC4));
}

typedef struct Pair_001DCD70 {
    f32 x;
    f32 y;
} Pair_001DCD70;

typedef union Slot_001DCD70 {
    Pair_001DCD70 value;
    struct {
        s32 x;
        s32 y;
    } bits;
} Slot_001DCD70;

typedef struct State_001DCD70 {
    u8 *record;
    s32 field04;
    Slot_001DCD70 slots[5];
    s32 field30;
    s16 field34;
    s16 field36;
    s16 field38;
    s16 field3A;
    s16 id;
    u8 field3E;
    u8 field3F;
    u8 field40;
    u8 field41;
    u8 field42;
    u8 field43;
    u8 field44;
    u8 field45;
    u8 field46;
    u8 field47;
    u8 field48;
    u8 field49;
    u8 field4A;
    u8 field4B;
    u8 field4C;
    u8 field4D;
    u8 field4E;
    u8 field4F;
    u8 field50;
    u8 field51;
    u8 field52;
    u8 field53;
    u8 field54;
    u8 field55;
    s8 flag56_0 : 2;
    s8 flag56_1 : 2;
    s8 flag56_2 : 2;
    s8 flag56_3 : 2;
    s8 flag57_0 : 1;
    s8 flag57_1 : 1;
    s8 flag57_2 : 1;
    s8 flag57_3 : 1;
    s8 flag57_4 : 1;
    s8 flag57_5 : 1;
    s8 flag57_6 : 1;
    s8 flag57_7 : 1;
    s8 flag58_0 : 1;
    s8 flag58_1 : 1;
    s8 flag58_2 : 1;
    s8 flag58_3 : 1;
    s16 flag58_4 : 6;
} State_001DCD70;

extern Pair_001DCD70 D_002C9DF0[][5];
extern Pair_001DCD70 D_002CC5F0[];

void func_001DCD70(void *arg0, s32 arg1) {
    State_001DCD70 *state;
    s32 i;
    s32 *words;
    Pair_001DCD70 *source;
    s32 index;

    state = arg0;
    state->record = NULL;
    state->field04 = 0;
    i = 0;
    words = (s32 *)state;
    do {
        i++;
        words[2] = -1;
        words[3] = -1;
        words += 2;
    } while (i < 5);
    state->field30 = 0;
    state->field34 = 0;
    state->field36 = 0;
    state->field38 = 0;
    state->field3A = 0;
    state->id = 999;
    state->field3E = 0xFF;
    state->field3F = 0xFF;
    state->field40 = 7;
    state->field41 = 7;
    state->field42 = 7;
    state->field43 = 7;
    state->field44 = 2;
    state->field45 = 11;
    state->field46 = 84;
    state->field47 = 0;
    state->field48 = 0;
    state->field49 = 0;
    state->field4A = 0;
    state->field4B = 0;
    state->field4C = 0;
    state->field4D = 0x80;
    state->field4E = 1;
    state->field4F = 7;
    state->field50 = 0x80;
    state->field51 = 0x80;
    state->field52 = 0x80;
    state->field53 = 0;
    state->field54 = 0;
    state->field55 = 0;
    state->flag56_0 = 0;
    state->flag56_1 = 0;
    state->flag56_2 = 0;
    state->flag56_3 = 0;
    state->flag57_0 = 0;
    state->flag57_1 = 0;
    state->flag57_2 = 0;
    state->flag57_3 = 0;
    state->flag57_4 = 0;
    state->flag57_5 = 0;
    state->flag57_6 = 0;
    state->flag57_7 = 0;
    state->flag58_0 = 0;
    state->flag58_1 = 0;
    state->flag58_2 = 0;
    state->flag58_3 = 0;
    state->flag58_4 = 63;
    if (arg1 == 0x29F) {
        arg1 = 999;
    }
    if (arg1 >= 0 && arg1 < 0x356) {
        state->id = arg1;
        state->record = func_001DD0E0(arg1);
        state->field3E = state->record[0];
        state->field3F = state->record[2] & 0xF;
        index = *(u16 *)(state->record + 4);
        if (index != 0xFFFF) {
            if (arg1 >= 0x2AB) {
                state->slots[0].value = D_002CC5F0[index];
            } else {
                source = D_002C9DF0[index];
                i = 0;
                do {
                    state->slots[0].value = *source;
                    i++;
                    source++;
                    state = (State_001DCD70 *)((u8 *)state + 8);
                } while (i < 5);
            }
        }
    }
}

u8 *func_001DD0E0(s32 arg0) {
    extern u8 D_002BF080[];
    u8 *ret;

    if (arg0 == 0x29F) {
        arg0 = 0x3E7;
    }
    if (arg0 < 0 || arg0 >= 0x356) {
        ret = NULL;
    } else {
        ret = &D_002BF080[arg0 * 0x14];
    }
    return ret;
}

void *func_001DD130(s32 group, s32 index) {
    extern s32 func_001F2980();
    s32 type;
    s32 offset;

    if (group < 0) {
        type = func_001F2980(index);
        if (type < 0) {
            return NULL;
        }
        switch (type) {
        case 5:
            group = index - 30;
            index = 0;
            break;
        case 4:
            offset = index - 20;
            group = offset < 5 ? 0 : 1;
            index = offset % 5 + 1;
            break;
        default:
            return NULL;
        }
    }
    if (group < 0 || group >= 3 || index < 0 || index >= 11) {
        return NULL;
    }
    return group * 0x3F4 + D_00318280 + index * 0x5C;
}

extern u8 D_00318E60[];

static inline u8 *cell_001DD220(s32 x, s32 y, u8 *cell) {
    if (x < 0 || x >= 7 || y < 0 || y >= 7) {
        return NULL;
    }
    return cell;
}

void func_001DD220(void) {
    s32 var_s0;
    s32 var_s1;
    u8 *var_a0;
    u8 *var_s2;
    u8 *var_s3;

    var_s3 = D_00318E60;
    var_s1 = 0;
    do {
        var_s0 = 0;
        var_s2 = var_s3;
        do {
            var_a0 = cell_001DD220(var_s0, var_s1, var_s2);
            func_001DD2D0(var_a0, *(s32 *)var_a0);
            var_s0 += 1;
            var_s2 += 0x1C;
        } while (var_s0 < 7);
        var_s1 += 1;
        var_s3 += 0xC4;
    } while (var_s1 < 7);
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
struct DotrStateCellQuad_1dd2d0 {
    unsigned char unknown_0;
    unsigned char unknown_1;
    unsigned char unknown_2;
    unsigned char unknown_3;
};
typedef int DotrStateWord_1dd2d0;
struct DotrStateCell_1dd2d0 {
    DotrStateWord_1dd2d0 unknown_00;
    struct DotrStateCellQuad_1dd2d0 unknown_04[4];
    short unknown_14;
    unsigned char unknown_16;
    unsigned char unknown_17;
    unsigned char unknown_18;
    unsigned char unknown_19;
    unsigned char unknown_1a;
};
typedef char DotrStateCellMustBe1c[(sizeof(struct DotrStateCell_1dd2d0) == 0x1c) ? 1 : -1];
struct DotrStateItemObject {
    struct DotrStateVector unknown_00;
    struct DotrStateVector unknown_10;
    unsigned char unknown_20[0x10];
    struct DotrStateVector unknown_30;
    struct DotrStateCellQuad_1dd2d0 unknown_40;
};
struct DotrUnitRequestObject {
    unsigned char unknown_00[0x14];
    int unknown_14;
    int unknown_18;
    unsigned char unknown_1c[0x14];
    struct DotrStateVector unknown_30;
    struct DotrStateCellQuad_1dd2d0 unknown_40;
};
extern int func_001AAF60_b(int a);
extern int func_001F2800_b(int index, int value);

void func_001DD2D0(void *cell_v, int unknown)
{
    struct DotrStateCell_1dd2d0 * cell = cell_v;
    struct DotrUnitRequestObject *o;
    struct DotrStateVector v;
    int mode;
    struct DotrStateItem *u = (struct DotrStateItem *)unknown;
    int n, flag;
    signed char d;
    unsigned char level;
    float f;
    mode = func_001AAF60_b(1);
    if (cell == 0) {
        return;
    }
    if (u == 0) {
        return;
    }
    if (!u->unknown_57.unknown_bit_7) {
        if (!u->unknown_58.unknown_bit_1) {
            if (u->unknown_57.unknown_bit_0) {
                n = u->unknown_4c[1] - 4;
                n = n > 64 ? n : 64;
                u->unknown_4c[1] = n;
            } else {
                n = u->unknown_4c[1] + 4;
                n = n < 128 ? n : 128;
                u->unknown_4c[1] = n;
            }
        }
        if (u->unknown_56.unknown_bits_4_5) {
            d = u->unknown_56.unknown_bits_4_5;
            if ((d > 0 && u->unknown_54 >= 255) || (d < 0 && u->unknown_54 <= 0)) {
                u->unknown_56.unknown_bits_4_5 = 0;
            } else if (d > 0) {
                n = u->unknown_54 + 32;
                n = n < 255 ? n : 255;
                u->unknown_54 = n;
            } else {
                n = u->unknown_54 - 32;
                n = n > 0 ? n : 0;
                u->unknown_54 = n;
            }
        }
        if (u->unknown_56.unknown_bits_6_7) {
            d = u->unknown_56.unknown_bits_6_7;
            if ((d > 0 && u->unknown_55 >= 255) || (d < 0 && u->unknown_55 <= 0)) {
                u->unknown_56.unknown_bits_6_7 = 0;
            } else if (d > 0) {
                n = u->unknown_55 + 32;
                n = n < 255 ? n : 255;
                u->unknown_55 = n;
            } else {
                n = u->unknown_55 - 32;
                n = n > 0 ? n : 0;
                u->unknown_55 = n;
            }
        }
        n = u->unknown_56.unknown_bits_0_1;
        if ((n > 0 && u->unknown_52 >= u->unknown_50) || (n < 0 && u->unknown_52 <= 0)) {
            if (mode == 1) {
                u->unknown_4e = 1;
            } else {
                u->unknown_4e = 0;
            }
            u->unknown_56.unknown_bits_0_1 = 0;
        } else if (n > 0) {
            int t = u->unknown_52 + 8;
            t = t < u->unknown_50 ? t : u->unknown_50;
            u->unknown_52 = t;
        } else if (n < 0) {
            int t = u->unknown_52 - 8;
            t = t > 0 ? t : 0;
            u->unknown_52 = t;
        }
        o = (struct DotrUnitRequestObject *)u->unknown_04;
        if (o != 0) {
            if (u->unknown_58.unknown_bit_1) {
                level = 128;
            } else {
                level = cell->unknown_1a;
            }
            o->unknown_14 = -((u->unknown_55 << 14) / 255);
            if (u->unknown_44 == 0) {
                o->unknown_14 = o->unknown_14 + 0x8000;
            }
            o->unknown_18 = (u->unknown_54 << 15) / 255;
            n = (u->unknown_4c[1] * level) >> 7;
            o->unknown_40.unknown_0 = n;
            o->unknown_40.unknown_1 = n;
            o->unknown_40.unknown_2 = n;
            if (u->unknown_4e & 1) {
                o->unknown_40.unknown_3 = u->unknown_52;
            }
            if (u->unknown_4e & 2) {
                f = (float)(unsigned)u->unknown_52 / 1280.0f;
                o->unknown_30.z = f;
                o->unknown_30.y = f;
                o->unknown_30.x = f;
            }
        }
    }
    if (u->unknown_45 >= 6) {
        return;
    }
    if (u->unknown_58.unknown_bit_0) {
        return;
    }
    flag = 0;
    if (func_001F1300(u->unknown_46)) {
        if (u->unknown_45 == 0) {
            flag = 1;
        } else if (u->unknown_57.unknown_bit_4) {
            flag = 1;
        }
    }
    if (flag) {
        n = u->unknown_56.unknown_bits_2_3;
        if ((n > 0 && u->unknown_53 >= u->unknown_51) || (n < 0 && u->unknown_53 <= 0)) {
            if (mode == 1) {
                u->unknown_4f = 1;
            } else {
                u->unknown_4f = 0;
            }
            u->unknown_56.unknown_bits_2_3 = 0;
        } else if (n > 0) {
            int t = u->unknown_53 + 8;
            t = t < u->unknown_51 ? t : u->unknown_51;
            u->unknown_53 = t;
        } else if (n < 0) {
            int t = u->unknown_53 - 8;
            t = t > 0 ? t : 0;
            u->unknown_53 = t;
        }
    }
    if (u->unknown_4f & 1) {
        func_001F2800_b(u->unknown_46, u->unknown_53);
    }
    if (u->unknown_4f & 2) {
        f = (float)(unsigned)u->unknown_53 / 128.0f;
        f = f < 1.0f ? f : 1.0f;
        v.z = f;
        v.y = f;
        v.x = f;
        func_001F25D0(u->unknown_46, &v);
    }
}

s32 func_001DD890(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 *first;
    u8 *second;
    s32 result;

    first = (u8 *)func_001DF540(arg0, arg1);
    second = (u8 *)func_001DF540(arg2, arg3);
    result = 0;
    if (first == second) {
        second = 0;
    }
    if (first != 0 && second != 0) {
        result |= func_001DDAC0(arg0, arg1, second[0x40], second[0x41]);
        result |= func_001DDAC0(arg2, arg3, first[0x40], first[0x41]);
    } else {
        if (first != 0) {
            result |= func_001DD990(arg0, arg1);
        }
        if (second != 0) {
            result |= func_001DD990(arg2, arg3);
        }
    }
    return result;
}

typedef struct Flags_001DD990 {
    s8 unused : 1;
    s8 facing : 1;
    s8 remaining : 6;
} Flags_001DD990;

typedef struct State_001DD990 {
    u8 pad00[0x30];
    s32 angle;
    u8 pad34[0x23];
    Flags_001DD990 flags;
} State_001DD990;

s32 func_001DD990(s32 arg0, s32 arg1) {
    State_001DD990 *state;
    s32 result;
    s32 target;
    s32 delta;

    state = (State_001DD990 *)func_001DF540(arg0, arg1);
    result = 0;
    if (state != 0) {
        target = state->flags.facing ? 0x8000 : 0;
        if (state->angle != target) {
            delta = (target - state->angle) % 0x10000;
            if (delta < -0x7FFF) {
                delta += 0x10000;
            } else if (delta > 0x8000) {
                delta -= 0x10000;
            }
            if (delta != 0) {
                if (delta > 0) {
                    if (delta > 0x800) {
                        delta = 0x800;
                    }
                    state->angle += delta;
                } else {
                    if (delta < -0x800) {
                        delta = -0x800;
                    }
                    state->angle += delta;
                }
                state->angle = (state->angle + 0x10000) % 0x10000;
                if (state->angle > 0x8000) {
                    state->angle -= 0x10000;
                }
            }
        }
        result = 1;
    }
    return result;
}

typedef struct Unit_001DDAC0 {
    u8 pad00[0x30];
    s32 rotation;
    s16 x;
    s16 y;
    u8 pad38[8];
    u8 grid_x;
    u8 grid_y;
    u8 pad42[2];
    u8 reversed;
} Unit_001DDAC0;

s32 func_001DDAC0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    extern s32 func_001A22C0(f32);
    Unit_001DDAC0 *self;
    Unit_001DDAC0 *target;
    s32 x;
    s32 result;
    s32 y;
    s32 difference;

    self = (Unit_001DDAC0 *)func_001DF540(arg0, arg1);
    target = (Unit_001DDAC0 *)func_001E36E0(arg2, arg3);
    x = func_001A22C0((f32)((arg2 - 3) * 50));
    y = func_001A22C0((f32)((arg3 - 3) * 50));
    result = 0;
    if (self == target) {
        return func_001DD990(arg0, arg1);
    }
    if (target != 0) {
        x += target->x;
        y += target->y;
    }
    if (self != 0) {
        f32 dx;
        f32 dy;
        s32 desired_angle;

        dx = (f32)x - ((f32)self->x + (f32)((self->grid_x - 3) * 50));
        dy = (f32)y - ((f32)self->y + (f32)((self->grid_y - 3) * 50));
        desired_angle = ((((self->reversed == 0 ? 0 : 0x8000) +
            func_001A22C0(65536.0f * (func_001A6C18(
                dy, dx) /
                6.2831855f)) + 0x400) >> 11) << 11);
        desired_angle += self->rotation;
        difference = -((desired_angle + 0x14000) % 0x10000);
        if (difference < -0x7FFF) {
            difference += 0x10000;
        } else if (difference > 0x8000) {
            difference -= 0x10000;
        }
        if (difference != 0) {
            if (difference > 0) {
                if (difference > 0x800) {
                    difference = 0x800;
                }
                self->rotation += difference;
            } else {
                if (difference < -0x800) {
                    difference = -0x800;
                }
                self->rotation += difference;
            }
            self->rotation = (self->rotation + 0x10000) % 0x10000;
            if (self->rotation > 0x8000) {
                self->rotation -= 0x10000;
            }
            result = 1;
        }
    }
    return result;
}

void func_001E7F70(s32, s32, s32);
extern u8 D_002BF080[];

static inline u8 *lookup_001DDD80(s32 index) {
    if (index < 0 || index >= 0x356) {
        return NULL;
    }
    return D_002BF080 + index * 0x14;
}

void func_001DDD80(s32 arg0, s32 arg1, s32 arg2, void *arg3) {
    s32 var_a0;
    s32 var_s0;
    s32 var_s1;
    u8 *var_v1;

    func_001F3910(0, 0x26C, 0, arg3);
    func_001E7F70(6, 0, 0);
    func_001E7F70(0, 0, 0);
    var_s0 = 0;
    var_s1 = 0;
    do {
        var_a0 = func_002159D0(var_s0, func_002158B0(var_s0));
        if (var_a0 == 0x29F) {
            var_a0 = 0x3E7;
        }
        var_v1 = lookup_001DDD80(var_a0);
        if (var_v1 != NULL) {
            func_001E8780(var_s0 + 5, -1, (*var_v1 & 0x1F) + var_s1, 1);
        }
        var_s0 += 1;
        var_s1 += 0x64;
    } while (var_s0 < 2);
}

extern u8 D_002CEE5C[][7][7];

typedef struct {
    u8 pad[0xFEA3];
    u8 maps[5][7][7];
} Maps_001DDE80;

void func_001DDE80(s32 arg0) {
    s32 y;
    s32 x;
    Maps_001DDE80 *maps;
    extern s32 func_001E2220();

    if (arg0 >= 0 && arg0 < 0x2E) {
        for (y = 0; y < 7; y++) {
            for (x = 0; x < 7; x++) {
                func_001E2220(x, y, D_002CEE5C[arg0][y][x]);
            }
        }
    } else if (arg0 < 0x33) {
        maps = func_002145E0(0);
        arg0 -= 0x2E;
        for (y = 0; y < 7; y++) {
            for (x = 0; x < 7; x++) {
                func_001E2220(x, y, maps->maps[arg0][y][x]);
            }
        }
    } else if (arg0 < 0x38) {
        maps = func_002145E0(1);
        arg0 -= 0x33;
        for (y = 0; y < 7; y++) {
            for (x = 0; x < 7; x++) {
                func_001E2220(x, y, maps->maps[arg0][y][x]);
            }
        }
    }
}

s32 func_001DE020(s32 arg0) {
    return arg0 == 1 ? 1
         : arg0 == 2 ? 1
         : arg0 == 3 ? 2
         : arg0 == 4 ? 2
         : arg0 == 5 ? 3
         : arg0;
}

s32 func_001DE090(s64 arg0, s32 arg1) {
    return arg0 > 0 ? (s32)arg0 + 5 : arg1;
}

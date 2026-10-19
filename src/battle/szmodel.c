/* The 3D model system (84 model slots; SzModel_*). */

#include "common.h"

typedef struct Entry_001E7A60 {
    u8 padding[0x68];
    s32 id : 27;
    u32 flags : 5;
    u32 padding_6C;
} Entry_001E7A60;

extern Entry_001E7A60 motionBlurs[]; /* original: gSzModel_aBlur */
extern s32 motionBlurMode; /* original: gSzModel_nBlurMode */
extern s32 modelUsePackedFiles; /* original: gSzModel_fPacking */
extern u8 D_002CF9D0[];
extern u8 D_002CF9D5[];

/* Clears the 84 model slots, the blur and packing settings. */
s32 SzModel_Init(void) {
    extern u8 *getenv();
    s32 i;
    Entry_001E7A60 *entry;
    s32 j;

    for (i = 0; i < 0x54; i++) {
        modelSlots[i] = NULL;
    }
    entry = motionBlurs;
    for (j = 0; j < 0x20; j++) {
        entry->id = -1;
        entry++;
    }
    motionBlurMode = 0;
    if (getenv(D_002CF9D0) != NULL || getenv(D_002CF9D5) != NULL) {
        modelUsePackedFiles = 1;
    }
    return 1;
}

typedef struct ObjInit_001E7B20 {
    u8 pad000[0x30];
    f32 v[4];
    u8 pad040[0xE0];
    f32 f120;
    f32 f124;
    f32 f128;
    u8 rgba[4];
    u8 c130[4];
    u8 pad134[0xB8];
    s32 f1EC;
    u8 pad1F0;
    s8 f1E1_dummy;
    s8 f1F2;
    u8 pad1F3;
    s16 f1F4;
    u8 pad1F6;
    s8 pad1F7 : 6;
    s8 mode1F7 : 2;
    u8 pad1F8a : 2;
    u8 kind1F8 : 2;
    u8 pad1F8b : 4;
    u8 pad1F9[0x13];
    s8 b0 : 1;
    s8 b1 : 1;
    s8 b2 : 1;
    s8 b3 : 1;
    s8 b4 : 1;
    s8 b5 : 1;
    s8 b6 : 1;
    s8 b7 : 1;
} ObjInit_001E7B20;

/* Allocates model slot `index` (0..83) and clears it. */
s32 SzModel_Create(s32 index) {
    ObjInit_001E7B20 *obj;
    s32 off;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    if ((obj = (ObjInit_001E7B20 *)SzMem_Alloc(0x210)) == NULL) {
        return 0;
    }
    modelSlots[index] = (Obj_0031ABB0 *)obj;
    RhMem_FillMemory4(obj, 0, 0x84);
    ((s8 *)obj)[0x1E1] = -1;
    obj->mode1F7 = 1;
    obj->f1F2 = -1;
    obj->f1F4 = -1;
    obj->f1EC = -1;
    obj->v[0] = 1.0f;
    obj->v[1] = 1.0f;
    obj->v[2] = 1.0f;
    obj->v[3] = 1.0f;
    obj->f120 = 0.8f;
    obj->f124 = 0.8f;
    obj->f128 = 1.0f;
    obj->rgba[2] = 0x80;
    obj->rgba[1] = 0x80;
    obj->rgba[0] = 0x80;
    obj->rgba[3] = 0x80;
    obj->kind1F8 = 1;
    obj->c130[2] = 0;
    obj->c130[1] = 0;
    obj->c130[0] = 0;
    obj->c130[3] = 0;
    off = 0;
    obj->b0 = 1;
    obj->b1 = 1;
    obj->b2 = off;
    obj->b3 = off;
    obj->b4 = off;
    obj->b5 = off;
    obj->b6 = 1;
    obj->b7 = 1;
    lSzModel_Clean(index);
    return 1;
}

typedef struct {
    s8 bit0 : 1;
    s8 bit1 : 1;
    s8 bits2_4 : 3;
    s8 bit5 : 1;
    s8 bits6_7 : 2;
} Flags_001E7D00;

/* Resets model slot `index` to its defaults: position, rotation, scale, colour, animation. */
s32 lSzModel_Clean(s32 index) {
    Obj_0031ABB0 *object;

    if ((index < 0) || (index >= 0x54)) {
        return 0;
    }
    object = modelSlots[index];
    if (object == NULL) {
        return 0;
    }
    *(f32 *)((u8 *)object + 0x198) = 1.0f;
    *(f32 *)((u8 *)object + 0x19C) = 1.0f;
    *(f32 *)((u8 *)object + 0x1A0) = 1.0f;
    *(f32 *)((u8 *)object + 0x1A4) = 1.0f;
    *(f32 *)((u8 *)object + 0x1A8) = 1.0f;
    *(f32 *)((u8 *)object + 0x1AC) = 0.0f;
    object->lv[1] = -1;
    object->lv[0] = 0;
    ((Flags_001E7D00 *)((u8 *)object + 0x20D))->bit1 = 0;
    *(s8 *)((u8 *)object + 0x200) = 0;
    *(s16 *)((u8 *)object + 0x20A) = 0;
    *(s8 *)((u8 *)object + 0x1FB) = 6;
    *(s8 *)((u8 *)object + 0x1FC) = 0;
    *(s8 *)((u8 *)object + 0x1FD) = 0;
    ((Flags_001E7D00 *)((u8 *)object + 0x20C))->bit5 = 0;
    SzModel_SetRefID(index, -1, 1);
    *(s16 *)((u8 *)object + 0x1F0) = 0x7FFF;
    return 1;
}

/* Frees model slot `index` and its model. */
s32 SzModel_Destroy(s32 index) {
    s32 lSzModel_FreeModel(s32);
    void SzMem_Free(void *);
    Obj_0031ABB0 *obj;
    Obj_0031ABB0 **slot;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    slot = &modelSlots[index];
    obj = *slot;
    if (obj == NULL) {
        return 0;
    }
    if (lSzModel_FreeModel(index) == 0) {
        return 0;
    }
    SzMem_Free(obj);
    *slot = NULL;
    return 1;
}

typedef struct {
    s8 unused0 : 2;
    s8 pending : 1;
    s8 busy : 1;
    s8 unused4 : 4;
} Flags_001E7E70;

/* Whether a model slot is still loading. */
static inline s64 busy_001E7E70(Obj_0031ABB0 *obj) {
    return (s64) ((u64) obj->lv[0x2C] << 60) >> 63;
}

/* Frees model slot `index`'s model (waiting for its load) and books what it will hold: `kind` and `number`. */
s32 SzModel_Preset(s32 index, s32 kind, s32 number) {
    Obj_0031ABB0 *obj;

    if ((index < 0) || (index >= 0x54)) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    if (busy_001E7E70(obj)) {
        while (busy_001E7E70(obj)) {
            SzFile_DoRequestS();
        }
    }
    lSzModel_FreeModel(index);
    *(s8 *) ((u8 *) obj + 0x1F2) = -1;
    if (kind >= 0) {
        *(s8 *) ((u8 *) obj + 0x1F3) = (s8) kind;
    }
    *(s16 *) ((u8 *) obj + 0x1F4) = (s16) number;
    ((Flags_001E7E70 *) &obj->lv[0x2C])->pending = 1;
    return 1;
}

typedef struct {
    s16 *values[9];
} Sources_001E7F70;

typedef struct {
    s32 values[9];
} Table_001E7F70;

typedef struct {
    s32 file;
    u16 base;
    u16 mask;
} File_001E7F70;

typedef struct {
    s8 unused0 : 2;
    s8 pending : 1;
    s8 active : 1;
    s8 unused4 : 4;
} Flags_001E7F70;

/* Loads model group `group` set `set` (stage, leaders, monsters...) from the merged model file into its slots. */
s32 SzModel_LoadMerge(s32 group, s32 set, s32 force) {
    s32 *start;
    s32 value;
    s32 id;
    Sources_001E7F70 sources;
    extern s32 SzFile_ReadRequestParam();
    extern s32 SzModel_GetModelNo();
    extern s32 modelFileOffsets[];
    extern s32 D_00292A54[];
    extern File_001E7F70 modelGroupInfo[];
    extern u16 D_00292BA4[];
    extern Sources_001E7F70 D_00292BE0;
    extern Table_001E7F70 D_00292C10;
    extern Table_001E7F70 D_00292C40;
    extern Table_001E7F70 D_00292C70;
    extern u8 gSzDuel_DuelData[];
    extern s16 gSzDuel_RingData[];
    extern u8 gSzDuel_StageData[];
    extern u8 gSzDuel_EventData[];
    extern u8 gSzDuel_FieldData[];
    extern u16 gSzModel_awIgnore[];
    extern u8 D_002CF9DD[];
    extern u8 D_002CF9F0[];
    s32 fileIndex;
    s32 offset;
    s32 length;
    s32 file;
    Table_001E7F70 types;
    Table_001E7F70 counts;
    Table_001E7F70 starts;
    u8 *path;
    u8 name[128];
    File_001E7F70 *info;
    s16 *commonSource;
    s32 i;

    if (group < 0 || group >= 7) {
        return 0;
    }

    sources = D_00292BE0;
    sources.values[0] = (s16 *)&gSzDuel_DuelData[set * 10];
    sources.values[1] = &gSzDuel_RingData[set];
    sources.values[2] = (s16 *)&gSzDuel_StageData[24 * set];
    commonSource = (s16 *)&gSzDuel_EventData[set * 80];
    sources.values[3] = commonSource;
    sources.values[4] = commonSource;
    sources.values[5] = commonSource;
    sources.values[6] = (s16 *)&gSzDuel_FieldData[set * 20];
    types = D_00292C10;
    counts = D_00292C40;
    starts = D_00292C70;
    fileIndex = set + *(u16 *)((u8 *)D_00292BA4 + group * 8);
    offset = modelFileOffsets[fileIndex];
    length = D_00292A54[fileIndex] - offset;
    info = &modelGroupInfo[group];
    file = info->file;
    path = name;
    func_0019B648(path, D_002CF9DD, (s32)SzFile_GetEnv((s32)D_002CF9F0));
    if (4 != group) {
        if (SzText_GetItem(0, 0) != NULL) {
            SzText_Free(0, 0);
            SzText_Free(1, -1);
        }
    }
    if (3 != group) {
        SzText_Free(0, 5);
        SzText_Free(0, 6);
        SzText_Free(7, -1);
        SzText_Free(8, -1);
    }
    if (group == 4) {
        counts.values[7] = 9;
    }

    if (force == 0) {
        s32 j;
        s32 id;
        s32 count;
        s32 *start;
        s32 *amount;

        start = starts.values;
        amount = counts.values;
        i = 0;
        do {
            if ((1 << i) & info->mask) {
                id = *start;
                count = *amount;
                j = 0;
                goto test;
                body:
                    if (SzModel_IsModelStandby(id) != 0) {
                        force = 1;
                    }
                    id++;
                    j++;
                test:
                if (j < count) goto body;
            }
            i++;
            start++;
            amount++;
        } while (i < 9);

        {
            s32 *start;
            u16 *limit;
            s32 *amount;
            s16 *source;
            s32 i;

            source = sources.values[group];
            if (source != NULL) {
                i = 0;
                start = &starts.values[group];
                amount = &counts.values[group];
                limit = &gSzModel_awIgnore[types.values[group]];
                while (i < *amount) {
                    value = *source;
                    id = i + *start;
                    if (value < *limit && value != SzModel_GetModelNo(id)) {
                        force = 1;
                    }
                    source++;
                    i++;
                }
            }
        }
    }

    if (0 == force) {
        return 1;
    }

    {
        s32 *amount;
        s32 *type;
        s32 i;
        s32 j;

        start = starts.values;
        amount = counts.values;
        type = types.values;
        i = 0;
        do {
            if ((1 << i) & info->mask) {
                j = 0;
                while (j < *amount) {
                    SzModel_Preset(j + *start, -1, 999);
                    j++;
                }
                if (*type == 4) {
                    j = 1;
                    do {
                        SzDuel_DelUnit(0, j);
                        SzDuel_DelUnit(1, j);
                        j++;
                    } while (j < 11);
                }
            }
            i++;
            start++;
            amount++;
            type++;
        } while (i < 9);
    }

    {
        i = 0;
        while (i < counts.values[group]) {
            SzModel_Preset(starts.values[group] + i, -1, sources.values[group][i]);
            i++;
        }
        if (SzFile_ReadRequestParam(group, 0, (s32)path, file, length, offset, length,
                          (s32)lSzModel_LoadMergeCB, fileIndex) == 0) {
            return 0;
        }
        i = 0;
        while (i < counts.values[group]) {
            Obj_0031ABB0 *obj = modelSlots[i + starts.values[group]];
            if (obj != NULL) {
                ((Flags_001E7F70 *)((u8 *)obj + 0x20C))->pending = 0;
                ((Flags_001E7F70 *)((u8 *)obj + 0x20C))->active = 1;
            }
            i++;
        }
    }
    return 1;
}

struct DotrMergeRecord {
    char unknown_00[0x14];
    char *data;
    int unknown_18;
    int user;
};
struct DotrMergeBits {
    signed char bit_0 : 1;
    signed char bit_1 : 1;
    signed char bit_2 : 1;
    signed char bit_3 : 1;
    signed char bit_4 : 1;
    signed char bit_5 : 1;
    signed char bit_6 : 1;
    signed char bit_7 : 1;
};
struct DotrMergeObject {
    unsigned char unknown_000[0x1f3];
    signed char kind;
    short number;
    unsigned char unknown_1f6[0x16];
    struct DotrMergeBits bits;
};
struct DotrMergeTable {
    int v[39];
};
struct DotrMergeOffsets {
    int *v[39];
};
extern struct DotrMergeTable D_00292CA0;
extern struct DotrMergeTable D_00292D40;
extern struct DotrMergeTable D_00292DE0;
extern struct DotrMergeOffsets D_00292E80;
extern unsigned short gSzModel_awIgnore[];
extern struct DotrMergeObject *D_0031ABB0_b[];

/* A merged model file has loaded: binds each model it holds to its slot. */
void lSzModel_LoadMergeCB(void *req_v, int ok)
{
    struct DotrMergeRecord * req = req_v;
    int user = req->user;
    struct DotrMergeTable first = D_00292CA0;
    struct DotrMergeTable count = D_00292D40;
    struct DotrMergeTable limit = D_00292DE0;
    struct DotrMergeOffsets offs = D_00292E80;
    int j;
    struct DotrMergeObject *p;

    if (!ok) {
        for (j = 0; j < count.v[user]; j++) {
            p = D_0031ABB0_b[first.v[user] + j];
            if (p) {
                p->bits.bit_3 = 0;
            }
        }
        return;
    }
    for (j = 0; j < count.v[user]; j++) {
        p = D_0031ABB0_b[first.v[user] + j];
        if (p) {
            p->bits.bit_3 = 0;
            if (p->number < gSzModel_awIgnore[p->kind] && j < limit.v[user] && *(int *)(req->data + offs.v[user][j]) == 0x304852) {
                p->bits.bit_0 = 0;
                lSzModel_Clean(first.v[user] + j);
                lSzModel_BindModelByAddr(first.v[user] + j, req->data + offs.v[user][j]);
            }
        }
    }
}

typedef struct {
    Obj_0031ABB0 shared;
    u8 pad1E4[0x1F2 - sizeof(Obj_0031ABB0)];
    s8 state;
    s8 kind;
    s16 value;
    u8 pad1F6[0x16];
    s8 unused0 : 2;
    s8 loading : 1;
    s8 busy : 1;
    s8 unused4 : 4;
} Fields_001E8780;

typedef struct {
    s32 values[3];
} Table_001E8780;

extern s32 modelFolderNames[]; /* original: gSzModel_apchBase */
extern s32 modelFileOffsets[]; /* original: anOfs_MODEL */
extern s32 D_00292A54[];
extern Table_001E8780 D_00292F20;
extern Table_001E8780 D_00292F30;
extern u16 gSzModel_awIgnore[];
extern u8 D_002CF9DD[];
extern u8 D_002CF9F0[];
extern u8 D_002CF9F5[];
extern u8 D_002CFA0A[];
extern u8 D_002CFA17[];
extern u8 D_002CFA1D[];

/* Loads model `number` of `kind` into slot `index` (`packed` reads it from the packed file). */
s32 SzModel_Load(s32 slotIndex, s32 modelKind, s32 number, s32 packed) {
    u8 format[128];
    u8 path[128];
    Table_001E8780 slots;
    Table_001E8780 starts;
    Fields_001E8780 *obj;
    s32 slot;
    s32 base;
    u8 *root;
    s32 value;
    s32 id;
    s32 group;
    s32 index;
    s32 start;
    s32 size;
    s32 card;
    s32 leader;
    s32 kind;
    s32 tableIndex;

    extern void func_0019B648();

    value = number;
    if (slotIndex < 0 || slotIndex >= 0x54) {
        return 0;
    }
    obj = (Fields_001E8780 *)modelSlots[slotIndex];
    if (obj == NULL) {
        return 0;
    }
    if (obj->busy) {
        while (obj->busy) {
            SzFile_DoRequestS();
        }
    }
    obj->state = -1;
    if (modelKind >= 0) {
        obj->kind = modelKind;
    }
    if (value >= 0) {
        obj->value = value;
    } else {
        value = obj->value;
    }
    obj->loading = 0;
    if (value < 0 || value >= gSzModel_awIgnore[obj->kind]) {
        return 0;
    }
    base = modelFolderNames[obj->kind];
    if (packed != 0 && modelUsePackedFiles != 0) {
        if (getenv((s32)D_002CF9D5) != NULL) {
            root = SzFile_GetEnv((s32)D_002CF9F0);
            kind = obj->kind;
            card = 0;
            leader = 0;
            if (kind == 4) {
                goto card_kind;
            }
            if (kind == 5) {
                goto card_kind;
            }
            if (kind == 6) {
            card_kind:
                card = 1;
            }
            if (kind == 1) {
                leader = 1;
            }
            if (card) {
                if (value == 0x2E1) {
                    id = 0x29F;
                } else {
                    id = SzDuel_Xax2New(value);
                }
                if (id < 0x2AB) {
                    slot = obj->kind - 4;
                    slots = D_00292F20;
                    starts = D_00292F30;
                    func_0019B648(path, D_002CF9F5, root);
                    if (lSzModel_LoadModelPack(slotIndex, path, starts.values[slot] + ((slotIndex - slots.values[slot]) << 20), 0x100000, id << 20, 0x100000)) {
                        return 1;
                    }
                }
                return 0;
            } else if (leader) {
                group = value / 100;
                index = value % 100;
                if (group >= 0 && group < 2 && index >= 0 && index < 21) {
                    tableIndex = index + (group != 0 ? 0x3C : 0x27);
                    start = modelFileOffsets[tableIndex];
                    size = D_00292A54[tableIndex] - start;
                    func_0019B648(path, D_002CF9DD, root);
                    if (lSzModel_LoadModelPack(slotIndex, path, (s32)((s64)group * 0xA000 + 0x010AA800), size, start, size)) {
                        return 1;
                    }
                }
                return 0;
            }
        }
        func_0019B648(format, D_002CFA0A, SzFile_GetEnv((s32)D_002CFA17), base, base);
        func_0019B648(path, format, value, value);
        if (lSzModel_LoadModelPack(slotIndex, path, 0, -1, 0, -1) == 0) {
            return 0;
        }
    } else {
        func_0019B648(format, D_002CFA1D, SzFile_GetEnv((s32)D_002CFA17), base, base);
        func_0019B648(path, format, value, value);
        if (lSzModel_LoadModel(slotIndex, path) == 0) {
            return 0;
        }
    }
    return 1;
}

struct DotrModelLoadHeader {
    int node_offset;
    unsigned int flags;
    unsigned char unknown_08[80];
    int gnode_flag;
};
struct DotrModelLoadNode {
    unsigned char unknown_00[0x30];
    float x, y, z, radius;
};
struct DotrModelLoadObject {
    unsigned char unknown_000[0x90];
    float pos[4];
    unsigned char unknown_0a0[0x94];
    struct DotrModelLoadNode *node;
    char *base;
    struct DotrModelLoadHeader *desc;
    unsigned char unknown_140[0x38];
    int heads[8];
    unsigned char unknown_198[0x48];
    signed char motion[4];
    float radius;
    float scale;
    unsigned char unknown_1ec[6];
    signed char index;
    signed char kind;
    short id;
    unsigned short look : 14;
    unsigned char unknown_1f8[6];
    signed char level;
    unsigned char unknown_1ff[7];
    unsigned short loaded_id;
    unsigned char unknown_208[4];
    signed char unknown_bit_0 : 3;
    signed char loading : 1;
};
extern struct DotrModelLoadObject *D_0031ABB0_1e8bf0[84];
extern unsigned short gSzDuel_Camera[];
extern char D_002CFA17_1e8bf0[];
extern char D_002CFA2A[];
extern char *func_001FFF90_b(const char *label);
extern void func_001F3910_b(int a, int b, int c);

/* A model file has loaded into slot `index`: sets up its nodes, textures and animations. */
void lSzModel_LoadCB(int index)
{
    struct DotrModelLoadObject *obj;
    struct DotrModelLoadNode *node;
    int i;
    index &= 0x3ff;
    if (index < 0 || index >= 84) return;
    obj = D_0031ABB0_1e8bf0[index];
    if (obj == 0) return;
    obj->loading = 0;
    if (obj->base == 0) return;
    obj->index = index;
    

    if (obj->kind != 4) if (obj->kind != 5) if (obj->kind != 6) goto skip;
    {
        obj->loaded_id = obj->id;
        obj->look = gSzDuel_Camera[AlternateCardIds[obj->id]] & 0x3fff;
    }
skip:
    node = (struct DotrModelLoadNode *)(obj->base + obj->desc->node_offset);
    obj->node = node;
    obj->level = obj->desc->flags >> 6;
    lSzModel_GetGNode(index, -1, &obj->desc->gnode_flag);
    obj->pos[0] = node->x;
    obj->pos[1] = node->y;
    obj->pos[2] = node->z;
    obj->pos[3] = 1.0f;
    obj->radius = node->radius;
    obj->scale = 40.0f / obj->radius;
    if (obj->scale > 1.0f) obj->scale = 1.0f;
    if (obj->scale < 0.3f) obj->scale = 0.3f;
    if (obj->heads[obj->motion[0]] == 0) {
        obj->motion[0] = 0;
        for (i = 0; i < 8; i++) {
            if (obj->heads[i] != 0) {
                obj->motion[0] = i;
                break;
            }
        }
    }
    for (i = 1; i < 4; i++) {
        if (obj->motion[i] >= 0 && obj->heads[obj->motion[i]] == 0) {
            obj->motion[i] = obj->motion[0];
        }
    }
    if (obj->kind != 4) if (obj->kind != 5) if (obj->kind != 6) return;
    {
        func_001FFF90_b(D_002CFA17_1e8bf0);
        func_001FFF90_b(D_002CFA2A);
        ((struct DotrModelLoadHeader *)obj->base)->flags &= ~0x400;
        func_001F3910_b(1, obj->id, 0);
    }
}

typedef struct {
    u8 pad0[0xC];
    u16 count;
} Res_001E8E90;

typedef struct {
    u8 pad0[4];
    u32 flags;
} Sub_001E8E90;

typedef struct {
    u8 pad000[0x138];
    Sub_001E8E90 *sub;
    u8 pad13C[0x30];
    Res_001E8E90 *res0;
    Res_001E8E90 *res1;
    u8 pad174[0x8E];
    u16 cur;
    u16 last;
} Obj_001E8E90;

typedef struct {
    u8 pad0[0x14];
    Res_001E8E90 *res;
    u8 pad18[4];
    u32 bits;
} Req_001E8E90;

/* A model's camera file has loaded. */
void lSzModel_LoadCameraCB(void *request, s32 arg1) {
    Req_001E8E90 *req = request;
    s32 second;
    Obj_001E8E90 *obj;
    s32 index;

    index = req->bits & 0x7F;
    second = req->bits & 0x80;
    if (index < 0 || index >= 0x54) {
        return;
    }
    obj = (Obj_001E8E90 *)modelSlots[index];
    if (obj == NULL) {
        return;
    }
    if (obj->sub == NULL) {
        SzMem_Free((s32)req->res);
        arg1 = 0;
    }
    if (arg1 == 0) {
        if (second) {
            obj->res1 = NULL;
        } else {
            obj->res0 = NULL;
        }
        return;
    }
    if (second) {
        obj->res1 = req->res;
        obj->sub->flags &= ~0x100000;
    } else {
        obj->res0 = req->res;
        obj->cur = obj->last = obj->res0->count - 1;
        obj->sub->flags &= ~0x80000;
    }
}

typedef struct {
    s32 data;
    s32 unk04;
    s32 additional;
    s32 resolved;
} Entry_001E8FA0;

/* Binds model slot `index`'s texture file to its model. */
s32 SzModel_BindTextureFile(s32 index) {
    Obj_0031ABB0 *obj;
    Entry_001E8FA0 *entry;
    s32 count;
    s32 i;
    void *directory;
    s32 base;
    u8 *table;

    if ((index < 0) || (index >= 0x54)) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    base = *(s32 *)&obj->pad040[0xF8];
    if (base == 0) {
        return 1;
    }
    directory = *(void **)&obj->pad040[0xFC];
    if (*(s32 *)((u8 *)directory + 0x2C) == 0) {
        return 1;
    }
    i = 0;
    table = (u8 *)(base + *(s32 *)((u8 *)directory + 0x28));
    count = *(s32 *)table;
    entry = (Entry_001E8FA0 *)(table + 0x10);
    for (; i < count; i++, entry++) {
        if (entry->data != 0) {
            entry->data = *(s32 *)&obj->pad040[0xF8] + entry->data;
            RhText_BindAddress(entry->data);
            if (entry->additional != 0) {
                entry->additional = *(s32 *)&obj->pad040[0xF8] + entry->additional;
            }
            entry->resolved = 0;
        }
    }
    return 1;
}

typedef int DotrObjectWord;
struct DotrObjPackEntry { DotrObjectWord a; DotrObjectWord b; DotrObjectWord c; DotrObjectWord d; };
struct DotrObjPackDesc { unsigned char unknown_00[0x28]; DotrObjectWord unknown_28; DotrObjectWord unknown_2c; };
struct DotrObjPackTable { int count; int pad[3]; struct DotrObjPackEntry entries[1]; };
struct DotrObjPackView { unsigned char unknown_00[0x138]; DotrObjectWord base; struct DotrObjPackDesc *desc; };
struct DotrResourceSubmitRecord;
struct DotrLoadObject {
    unsigned char unknown_000[312];
    int unknown_138;
    int unknown_13c;
    int main_part;
    int parts[8];
    unsigned char unknown_164[143];
    signed char kind;
    short number;
};
extern struct DotrLoadObject *D_0031ABB0_1e90b0[84];
extern char *D_00292480_1e90b0[];
extern char D_002CFA17_1e90b0[];
extern char D_002CFA30[];
extern char D_002CFA3A[];
extern char D_002CFA3F[];
struct DotrResourceQueueRecord {
    int status;
    short selector;
    short priority;
    unsigned char unknown_008[28];
};
typedef char DotrResourceRecordSizeMustBe36[(sizeof(struct DotrResourceQueueRecord) == 36) ? 1 : -1];
char *func_001FFF90_b(const char *label);
typedef void (*DotrResourceSubmitCallback)(struct DotrResourceSubmitRecord *record, int completed);
struct DotrResourceSubmitRecord {
    int status;
    short selector;
    short priority;
    signed int byte_size : 31;
    signed int flag_008 : 1;
    signed int byte_offset : 31;
    signed int flag_00c : 1;
    signed int unknown_010 : 31;
    signed int sector_mode : 1;
    int unknown_014;
    DotrResourceSubmitCallback callback;
    int unknown_01c;
    int handle;
};
struct DotrResourceQueueRecord *func_001FEC70_b(int type, char *name, int unknown_014, int byte_size,
                                              DotrResourceSubmitCallback callback, int unknown_01c);

/* Loads model slot `index`'s texture file. */
int SzModel_LoadTextureFile(int index)
{
    char format[128];
    char name[128];
    char anim[128];
    struct DotrLoadObject *obj;
    struct DotrObjPackView *view;
    struct DotrObjPackTable *table;
    struct DotrObjPackEntry *entry;
    char *base;
    int number;
    int count;
    int i;
    char *kind;
    

    if (index < 0 || index >= 84) {
        return 0;
    }
    obj = D_0031ABB0_1e90b0[index];
    if (obj == 0) {
        return 0;
    }
    base = func_001FFF90_b(D_002CFA17_1e90b0);
    number = obj->number;
    view = (struct DotrObjPackView *)obj;
    if (view->base == 0) {
        return 1;
    }
    if (view->desc->unknown_2c == 0) {
        return 1;
    }
    kind = D_00292480_1e90b0[obj->kind];
    table = (struct DotrObjPackTable *)(view->base + view->desc->unknown_28);
    count = table->count;
    entry = table->entries;
    func_0019B648(format, D_002CFA30, base, kind);
    for (i = 0; i < count; i++) {
        func_0019B648(name, format, number, &entry[i]);
        func_0019B9D0(name, D_002CFA3A);
        func_0019B648(anim, format, number, &entry[i]);
        func_0019B9D0(anim, D_002CFA3F);
        entry[i].a = 0;
        entry[i].c = 0;
        entry[i].d = 0;
        func_001FEC70_b(index, name, 0, -1, lSzModel_LoadTextureFileCB, ((unsigned int)(DotrObjectWord)entry & 0x3ffffff) | ((i & 0x3f) << 26));
        func_001FEC70_b(index, anim, 0, -1, lSzModel_LoadTexAnimFileCB, ((unsigned int)(DotrObjectWord)entry & 0x3ffffff) | ((i & 0x3f) << 26));
    }
    return 1;
}

typedef struct Object_001E9280 {
    u8 pad_00[0x14];
    s32 value;
    u8 pad_18[4];
    s32 packed;
} Object_001E9280;

/* A texture file has loaded (`ok`): binds it. */
void lSzModel_LoadTextureFileCB(void *request, s32 ok) {
    Object_001E9280 *object = request;
    s32 packed = object->packed;
    s32 *entry = (s32 *)(packed & 0x03FFFFFF);

    packed >>= 26;
    if (ok != 0) {
        entry = (s32 *)((u8 *)entry + packed * 0x10);
        *entry = object->value;
        RhText_BindAddress(*entry);
    }
}

typedef struct Slot_001E92C0 {
    s32 key;
    s32 unk04;
    u8 *data;
    s32 unk0C;
} Slot_001E92C0;

typedef struct State_001E92C0 {
    u8 unk00[8];
    signed int length : 31;
    unsigned int flag : 1;
    u8 unk0C[8];
    u8 *data;
    u8 unk18[4];
    s32 packed;
} State_001E92C0;

/* A texture animation file has loaded (`ok`): converts it. */
void lSzModel_LoadTexAnimFileCB(void *request, s32 ok) {
    void SzMem_Free(u8 *);
    Slot_001E92C0 *slot;
    u8 *buffer;
    s32 index;
    State_001E92C0 *state = request;

    slot = (Slot_001E92C0 *)(state->packed & 0x3FFFFFF);
    index = state->packed >> 26;
    if (ok != 0) {
        slot += index;
        slot->data = state->data;
        buffer = slot->data;
        if (buffer != NULL) {
            buffer[state->length - 1] = 0;
            slot->data = lSzModel_TexAnimConv(slot->key, buffer);
            SzMem_Free(buffer);
        }
    }
}

typedef union B3_001E9340 {
    u8 raw;
    struct {
        s8 a : 2;
        s8 b : 6;
    } s;
    struct {
        u8 c : 1;
        u8 : 7;
    } u;
} B3_001E9340;

typedef union V6_001E9340 {
    u16 w;
    struct {
        u8 lo;
        u8 hi;
    } b;
} V6_001E9340;

typedef struct Entry_001E9340 {
    u8 last : 1;
    u8 plain : 1;
    u8 kind : 3;
    u8 align : 3;
    u8 mask;
    u8 lo : 4;
    u8 hi : 4;
    B3_001E9340 b3;
    u16 v4;
    V6_001E9340 v6;
    u16 x8;
    u16 xA;
    u16 xC;
    u16 xE;
    u16 x10;
    u16 x12;
    s32 x14;
} Entry_001E9340;

typedef struct Hdr_001E9340 {
    u8 pad[0x44];
    u16 w;
    u16 h;
} Hdr_001E9340;

#define MAX_001E9340(a, b) ((a) > (b) ? (a) : (b))
#define MIN_001E9340(a, b) ((a) < (b) ? (a) : (b))
#define CLAMP_001E9340(x, lo, hi) MIN_001E9340(MAX_001E9340(x, lo), hi)

extern char D_002CFA72[];
extern char D_002CFA75[];
extern char D_002CFAA2[];
extern char D_002CFAC2[];
extern char D_002CFAF2[];
extern char D_002CFB16[];
extern char D_002CFB18[];
extern char D_002CFB32[];
extern char D_002CFB34[];
extern char D_002CFB3A[];
extern char D_002CFB3C[];
extern char D_002CFB40[];
extern char D_002CFB45[];
extern char D_002CFB4B[];
extern char D_002CFB4D[];
extern char *texAnimModeNames[]; /* original: apchMode */

/* Converts a texture animation text file into the game's table (its key words: mode, frames, loops...). */
u8 *lSzModel_TexAnimConv(s32 out, u8 *text) {
    char buf[0x400];
    char name[0x80];
    char flags[0x80];
    char place[0x80];
    char size[0x80];
    s32 x8;
    s32 xA;
    s32 xC;
    s32 xE;
    s32 x10;
    s32 x12;
    s32 a4;
    s32 b4;
    s32 b6;
    s32 c4;
    s32 c6;
    s32 d4;
    s32 d6;
    s32 e4;
    s32 e6;
    s32 sizeX;
    s32 sizeY;
    s32 count;
    s32 i;
    s32 kind;
    char **names;
    char *c;
    char *line;
    Entry_001E9340 *e;
    char *p;
    Entry_001E9340 *entries;
    char *tok;
    Hdr_001E9340 *hdr;

    line = buf;
    hdr = (Hdr_001E9340 *)(out + 0x10);
    p = line;
    count = 0;
    tok = func_0019D430((char *)text, D_002CFA72);
    while (tok != NULL) {
        if (*(u8 *)tok != '#') {
            func_0019BDD8(p, tok);
            p += func_0019BEF0(tok) + 1;
            count++;
        }
        tok = func_0019D430(NULL, D_002CFA72);
    }
    entries = count > 0 ? (Entry_001E9340 *)SzMem_Alloc(count * 24) : NULL;
    if (entries == NULL) {
        e = (Entry_001E9340 *)text;
        e->last = 1;
        e->lo = 0;
        e->hi = 0;
        return 0;
    }
    e = entries;
    for (i = 0; i < count; i++) {
        e->last = 1;
        e->lo = 0;
        e->hi = 0;
        kind = 0;
        names = texAnimModeNames;
        do {
            if (strncasecmp(line, *names, func_0019BEF0(*names)) == 0) {
                break;
            }
            kind++;
            names++;
        } while (kind < 7);
        switch (kind) {
        case 0:
        case 1:
            if (sscanf(line, D_002CFA75, name, flags, place, size, &a4, &x8, &xA, &xC, &xE, &x10, &x12) < 11) {
                scePrintf(D_002CFAA2, name);
                goto next;
            }
            e->b3.raw = 0;
            e->v4 = CLAMP_001E9340(a4, 1, 0xFFFF);
            break;
        case 2:
        case 3:
            if (sscanf(line, D_002CFAC2, name, flags, place, size, &b4, &b6, &x8, &xA, &xC, &xE, &x10, &x12) < 12) {
                scePrintf(D_002CFAA2, name);
                goto next;
            }
            e->b3.s.a = 1;
            e->b3.s.b = 0;
            e->v4 = CLAMP_001E9340(b4, 1, 0xFFFF);
            e->v6.w = CLAMP_001E9340(b6, 1, 0xFFFF);
            break;
        case 6:
            if (sscanf(line, D_002CFAF2, name, flags, &c4, &c6, &x8, &xA, &xC, &xE, &x10, &x12) < 10) {
                scePrintf(D_002CFAA2, name);
                goto next;
            }
            func_0019BDD8(place, D_002CFB16);
            e->b3.u.c = 0;
            e->v4 = CLAMP_001E9340(c4, 1, 0xFFFF);
            e->v6.b.lo = CLAMP_001E9340(c6, 0, 0xFF);
            e->v6.b.hi = 0;
            break;
        case 5:
            if (sscanf(line, D_002CFAF2, name, flags, &d4, &d6, &x8, &xA, &xC, &xE, &x10, &x12) < 10) {
                scePrintf(D_002CFAA2, name);
                goto next;
            }
            func_0019BDD8(place, D_002CFB16);
            e->b3.u.c = 0;
            e->v4 = CLAMP_001E9340(d4, 1, 0xFFFF);
            e->v6.b.lo = CLAMP_001E9340(d6, 0, 0xFF);
            e->v6.b.hi = 0;
            break;
        case 4:
            if (sscanf(line, D_002CFAF2, name, flags, &e4, &e6, &x8, &xA, &xC, &xE, &x10, &x12) < 10) {
                scePrintf(D_002CFAA2, name);
                goto next;
            }
            func_0019BDD8(place, D_002CFB16);
            e->v4 = CLAMP_001E9340(e4, 1, 0xFFFF);
            e->v6.w = CLAMP_001E9340(e6, 1, 0xFFFF);
            break;
        default:
            scePrintf(D_002CFB18);
            goto next;
        }
        e->kind = kind;
        e->align = 0;
        if (strcasecmp(place, D_002CFB16) == 0) {
            e->align = 0;
        } else if (strcasecmp(place, D_002CFB32) == 0) {
            e->align = 1;
        } else if (strcasecmp(place, D_002CFB34) == 0) {
            e->align = 2;
        } else if (strcasecmp(place, D_002CFB34 + 3) == 0) {
            e->align = 3;
        } else if (strcasecmp(place, D_002CFB3A) == 0) {
            e->align = 0;
        } else if (strcasecmp(place, D_002CFB3C) == 0) {
            e->align = 1;
        } else if (strcasecmp(place, D_002CFB3C + 2) == 0) {
            e->align = 2;
        } else if (strcasecmp(place, D_002CFB40) == 0) {
            e->align = 3;
        } else if (strcasecmp(place, D_002CFB40 + 2) == 0) {
            e->align = 4;
        }
        e->lo = 1;
        e->hi = 1;
        switch (e->align) {
        case 0:
        case 2:
            e->lo = CLAMP_001E9340(atoi(size), 1, 0xF);
            break;
        case 1:
        case 3:
            e->hi = CLAMP_001E9340(atoi(size), 1, 0xF);
            break;
        case 4:
            sizeX = 1;
            sizeY = 1;
            sscanf(size, D_002CFB45, &sizeX, &sizeY);
            e->lo = CLAMP_001E9340(sizeX, 1, 0xF);
            e->hi = CLAMP_001E9340(sizeY, 1, 0xF);
            break;
        }
        e->mask = 0;
        e->plain = 1;
        if (func_0019BC90(flags, D_002CFB4B) == 0) {
            e->mask = 0xFF;
            e->plain = 0;
        } else if (func_0019BC90(flags, D_002CFB4D) == 0) {
            e->mask = 0xFF;
        } else {
            kind = 0;
            if (kind < (u32)func_0019BEF0(flags)) {
                c = flags;
                do {
                    if (*c >= 'A' && *c < 'I') {
                        e->mask |= 1 << (*(u8 *)c - 'A');
                        e->plain = 0;
                    } else if (*c >= 'a' && *c < 'i') {
                        e->mask |= 1 << (*(u8 *)c - 'a');
                    }
                    c++;
                    kind++;
                } while (kind < (u32)func_0019BEF0(flags));
            }
        }
        e->last = (i + 1 >= count) ? 1 : 0;
        e->x8 = CLAMP_001E9340(x8, 1, hdr->w);
        e->xA = CLAMP_001E9340(xA, 1, hdr->h);
        e->xC = CLAMP_001E9340(xC, 0, hdr->w - 1);
        e->xE = CLAMP_001E9340(xE, 0, hdr->h - 1);
        e->x10 = CLAMP_001E9340(x10, 0, hdr->w - 1);
        e->x12 = CLAMP_001E9340(x12, 0, hdr->h - 1);
        e->x14 = 0;
        e++;
    next:
        line += func_0019BEF0(line) + 1;
    }
    return (u8 *)entries;
}

/* Loads model slot `index`'s two effect texture files. */
s32 SzModel_LoadEffectTextureFile(s32 index) {
    extern u8 D_002CFA17[];
    extern u8 D_002CFB4F[];
    extern u8 D_002CFB64[];
    extern s32 modelFolderNames[];
    extern void func_0019B648();
    extern s32 SzFile_ReadRequest();
    u8 buf1[0x80];
    u8 buf2[0x80];
    s32 s0;
    s32 s1;
    u8 *obj;
    s32 s4;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = (u8 *)modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    s0 = (s32)SzFile_GetEnv((s32)D_002CFA17);
    s1 = *(s16 *)(obj + 0x1F4);
    if (*(s32 *)(obj + 0x138) == 0) {
        return 1;
    }
    s4 = modelFolderNames[*(s8 *)(obj + 0x1F3)];
    *(s32 *)(obj + 0x140) = 0;
    func_0019B648(buf1, D_002CFB4F, s0, s4);
    func_0019B648(buf2, buf1, s1, s1);
    SzFile_ReadRequest(index, buf2, 0, -1, lSzModel_LoadEffectTextureFileCB, (s32)(obj + 0x140));
    func_0019B648(buf1, D_002CFB64, s0, s4);
    s0 = 0;
    do {
        *(s32 *)(obj + 0x144) = 0;
        func_0019B648(buf2, buf1, s1, s1, s0);
        SzFile_ReadRequest(index, buf2, 0, -1, lSzModel_LoadEffectTextureFileCB, (s32)(obj + 0x144));
        s0 += 1;
        obj += 4;
    } while (s0 < 8);
    return 1;
}

/* An effect texture file has loaded (`ok`): binds it. */
void lSzModel_LoadEffectTextureFileCB(void *request, s32 ok) {
    s32 *dest;

    dest = *(s32 **)((u8 *)request + 0x1C);
    if (ok != 0) {
        *dest = *(s32 *)((u8 *)request + 0x14);
        RhText_BindAddress(*dest);
    }
}

typedef struct {
    s32 id;
    s32 unused;
    s32 enabled;
    s32 count;
} Entry_001EA2A0;

typedef struct {
    u8 unused[0x28];
    s32 offset;
    s32 present;
} Header_001EA2A0;

/* Loads a model's textures into GS memory at `current` (and its texture animation's current frame). */
s32 SzModel_LoadTexture_Pipe(s32 current, s32 object, void *data, s32 *size) {
    extern s32 SzText_InitClutManage();
    s32 cursor;
    s32 count;
    s32 index;
    Entry_001EA2A0 *entry;
    s32 base;
    s32 entry_size;
    s32 *table;
    Header_001EA2A0 *header;

    if (size != NULL) {
        *size = 0;
    }
    if (data == NULL) {
        return current;
    }
    header = (Header_001EA2A0 *)((u8 *)data + 0x10);
    if (header->present == 0) {
        return current;
    }
    table = (s32 *)((u8 *)data + header->offset);
    count = *table;
    entry = (Entry_001EA2A0 *)((u8 *)table + 0x10);
    base = cursor = RhBase_GetUserGsAddress();
    cursor += SzText_InitClutManage(cursor, 2);
    for (index = 0; index < count; index++, entry++) {
        if (entry->id != 0) {
            current = SzText_Load_Pipe(current, entry->id, cursor, (s32)&entry_size);
            if (entry->enabled != 0 && SzModel_GetPauseFlag(object) == 0 && SzModel_GetStoneFlag(object) == 0) {
                current = SzModel_LoadTexAnim_Pipe(current, object, cursor, entry);
                entry->count++;
            }
            cursor += entry_size;
        }
    }
    if (size != NULL) {
        *size = cursor - base;
    }
    return RhText_SetTextureFlush(current);
}

typedef int DotrTexAnimWord;
typedef unsigned long DotrTexAnimLong;
struct DotrTexAnimTexture {
    char unknown_00[0x40];
    unsigned short psm;         
    unsigned short unknown_42;
    unsigned short width;       
};
struct DotrTexAnimHead {
    char unknown_00[16];
    struct DotrTexAnimTexture tex;
};
struct DotrTexAnimEntry {
    unsigned char last : 1;     
    unsigned char count : 1;    
    unsigned char type : 3;     
    unsigned char mode : 3;     
    unsigned char mask;         
    unsigned char cols : 4;     
    unsigned char rows : 4;
    union {
        signed char cell;       
        struct {
            signed char dir : 2;
            signed char pos : 6;
        } swing;                
        struct {
            unsigned char on : 1;
        } gate;                 
    } u3;                       
    union {
        struct {
            unsigned short a, b;
        } h;
        struct {
            unsigned short a;
            unsigned char limit, time;
        } b;
    } u4;                       
    unsigned short w, h;        
    unsigned short sx, sy;      
    unsigned short dx, dy;      
    int counter;                
};
struct DotrTexAnimRecord {
    struct DotrTexAnimHead *head;
    int unknown_4;
    struct DotrTexAnimEntry *entries;
};
extern int func_001F13F0_b(int index);

/* Loads the current frame of a model's texture animation. */
int SzModel_LoadTexAnim_Pipe(int cursor, int index, int position, void *record_v)
{
    struct DotrTexAnimRecord * record = record_v;
    struct DotrTexAnimEntry *e;
    DotrTexAnimLong *p = (DotrTexAnimLong *)cursor;
    DotrTexAnimLong *start;
    struct DotrTexAnimTexture *tex;
    int n;
    int step;
    int last;
    int cells;
    int anim;
    unsigned int frame;
    int cell;

    tex = &record->head->tex;
    e = record->entries;
    n = tex->width >> 6;
    start = p;
    n = (n > 1) ? n : 1;
    step = SzModel_GetPauseFlag(index) ? 0 : 1;
    for (last = 0; !last; e++) {
        cells = e->cols * e->rows;
        anim = func_001F13F0_b(index);
        frame = func_001A23B0(SzModel_GetAnimFrame(index));
        cell = 0;
        if (e->count) {
            frame = e->counter;
            e->counter = frame + step;
        }
        if (e->last) {
            last = 1;
        }
        if (cells == 0) {
            continue;
        }
        if (!(e->mask & (1 << anim))) {
            continue;
        }
        if (e->type == 0 || e->type == 2) {
            cells++;
        }
        switch (e->type) {
        case 0:
        case 1:
        {
            unsigned short span = e->u4.h.a;
            cell = e->u3.cell;
            if (step && frame && frame % span == 0) {
                cell = (cell + 1) % cells;
                e->u3.cell = cell;
            }
            break;
        }
        case 2:
        case 3: {
            unsigned short span;
            int dir = e->u3.swing.dir;
            if (dir > 0) {
                span = e->u4.h.a;
            } else {
                span = e->u4.h.b;
            }
            cell = e->u3.swing.pos;
            if (step && frame && frame % span == 0) {
                cell += dir;
                cell = ((cell > 0 ? cell : 0) < cells - 1) ? (cell > 0 ? cell : 0) : cells - 1;
                e->u3.swing.pos = cell;
                if (cell <= 0 || cell >= cells - 1) {
                    e->u3.swing.dir = -e->u3.swing.dir;
                    e->counter = 1;
                }
            }
            break;
        }
        case 6:
            if (e->u3.gate.on) {
                e->u4.b.time += step;
                if (e->u4.b.time < e->u4.b.limit) {
                    break;
                }
                e->u3.gate.on = 0;
                continue;
            }
            if (frame % e->u4.h.a) {
                continue;
            }
            if (step && e->u4.b.limit) {
                e->u3.gate.on = 1;
                e->u4.b.time = 0;
            }
            break;
        case 5:
            if (e->u3.gate.on) {
                if (frame == e->u4.h.a) {
                    break;
                }
                e->u4.b.time += step;
                if (e->u4.b.time < e->u4.b.limit) {
                    break;
                }
                e->u3.gate.on = 0;
                continue;
            }
            if (frame != e->u4.h.a) {
                continue;
            }
            if (step && e->u4.b.limit) {
                e->u3.gate.on = 1;
                e->u4.b.time = 0;
            }
            break;
        case 4:
            if (frame < e->u4.h.a) {
                continue;
            }
            if (frame > e->u4.h.b) {
                continue;
            }
            break;
        }
        if (e->type == 0 || e->type == 2) {
            if (cell == 0) {
                continue;
            }
            cell--;
        }
        if (e->sx == e->dx && e->sy == e->dy) {
            if (cell == 0) {
                continue;
            }
        }
        if (e->mode == 2 || e->mode == 3) {
            cell = -cell;
        }
        p[1] = 0;
        p[0] = 0;
        ((unsigned char *)p)[3] = 0x10;
        p[2] = 0x1000000000008004;
        p[3] = 0xe;
        p[4] = (DotrTexAnimLong)position | ((DotrTexAnimLong)n << 16) | ((DotrTexAnimLong)tex->psm << 24) | ((DotrTexAnimLong)position << 32) |
               ((DotrTexAnimLong)n << 48) | ((DotrTexAnimLong)tex->psm << 56);
        p[5] = 0x50;
        p[6] = (DotrTexAnimLong)(e->sx + e->w * (cell % e->cols)) | ((DotrTexAnimLong)(e->sy + e->h * (cell / e->cols)) << 16) |
               ((DotrTexAnimLong)e->dx << 32) | ((DotrTexAnimLong)e->dy << 48);
        p[7] = 0x51;
        p[8] = (DotrTexAnimLong)e->w | ((DotrTexAnimLong)e->h << 32);
        p[9] = 0x52;
        p[10] = 2;
        p[11] = 0x53;
        p += 12;
    }
    if (p != start) {
        unsigned short q = ((p - start) >> 1) - 1;
        *(unsigned short *)start = q;
        ((int *)start)[2] = 0x11000000;
        ((int *)start)[3] = q | 0x51000000;
    }
    return (DotrTexAnimWord)p;
}

/* Debug viewer controls for one object slot: the pad drives animation, camera, light and fog settings
   depending on the viewer page (func_00205150). */

typedef struct DbgFlags_001EAA60 {
    u8 pad[4];
    s32 flags;
} DbgFlags_001EAA60;

typedef struct Digits4_001EAA60 {
    s32 d0, d1, d2, d3;
} Digits4_001EAA60;

typedef struct Digits3_001EAA60 {
    s32 d0, d1, d2;
} Digits3_001EAA60;

typedef struct DbgObj_001EAA60 {
    f32 pos[3];                       /* 0x000 */
    u8 pad00C[0x14];
    s32 rot[3];                       /* 0x020 */
    u8 pad02C[4];
    Vec4f v;                          /* 0x030 */
    u8 pad040[0xE0];
    f32 light[3];                     /* 0x120 */
    u8 col0[4];                       /* 0x12C */
    u8 col1[4];                       /* 0x130 */
    u8 pad134[4];
    DbgFlags_001EAA60 *model;         /* 0x138 */
    u8 pad13C[8];
    s32 parts[8];                     /* 0x144 */
    u8 pad164[8];
    void *anim;                       /* 0x16C */
    u8 pad170[8];
    ObjSlot_0031ABB0 *slots[8];       /* 0x178 */
    f32 speed;                        /* 0x198 */
    f32 frame;                        /* 0x19C */
    u8 pad1A0[0x20];
    u32 vals[8];                      /* 0x1C0 */
    s8 lv[4];                         /* 0x1E0 */
    u8 pad1E4[8];
    s32 sound;                        /* 0x1EC */
    u8 pad1F0[2];
    s8 page;                          /* 0x1F2 */
    s8 kind;                          /* 0x1F3 */
    u8 pad1F4[2];
    u16 num : 14;                     /* 0x1F6 */
    s16 loop : 2;
    u8 fog0 : 2;                      /* 0x1F8 */
    u8 fog1 : 2;
    u8 pad1F8 : 4;
    u8 pad1F9[5];
    u8 count;                         /* 0x1FE */
    u8 pad1FF[3];
    u16 f202;                         /* 0x202 */
    u8 pad204[2];
    u16 f206;                         /* 0x206 */
    u16 f208;                         /* 0x208 */
} DbgObj_001EAA60;

extern u8 icolF[4];
extern u8 icolT[4];
extern u16 wFrame;
extern s32 nCameraCur;
extern s32 nEffCur;
extern Digits4_001EAA60 D_00292F90;
extern Digits4_001EAA60 D_00292FA0;
extern Digits3_001EAA60 D_00292FB0;
extern Digits3_001EAA60 D_00292FC0;
extern char D_002CFA17_2[];
extern char D_002CFB7D[];
extern s32 gSzModel_fRefLock;
extern s32 gSzModel_nRefLock;
extern u16 wAlphaMode;
extern s32 nBlurUse;
extern s32 nBlurCur;
extern s32 nEffCur2;

#define PAD_001EAA60(m, b) func_00203A40(0, m, b)

/* Debug: the model viewer for model slot `index`: moves, turns, scales and colours it, steps its motions, effects
   and camera with the pads. */
s32 SzModel_Act(s32 index) {
    extern s32 func_001EDCB0();
    extern s32 func_001FECB0();
    s64 mode;
    DbgObj_001EAA60 *obj;
    s32 page;
    f32 last;
    s32 i;
    s32 sel;
    s32 snd;
    s32 num;
    s32 newnum;
    s32 sub;
    s32 dir;
    s32 flag;
    s32 flag2;
    s32 n;
    f32 *anim;
    s32 pos;
    s8 *cur;
    s8 *lvp;
    void *ap;

    mode = func_001AAF60(1);
    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = (DbgObj_001EAA60 *)modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    if (obj->page == func_00205160()) {
        anim = &obj->speed;
        lvp = &obj->lv[0];
        if (index == 0) lvp = &obj->lv[0]; /* second definition: keeps lvp in its own register (s5) */
        cur = &obj->lv[2];
        page = func_00205150();
        last = (f32)obj->vals[*lvp] - 1.0f;
        if (page == 1) {
            if (obj->slots[*lvp] != NULL) {
                if (!(PAD_001EAA60(1, 3) & 0xFFFF)) {
                    if (PAD_001EAA60(2, 8) != 0) {
                        do {
                            *cur = (*cur + 9) % 8;
                        } while (obj->slots[*cur] == NULL);
                    }
                    if (PAD_001EAA60(2, 4) != 0) {
                        do {
                            *cur = (*cur + 7) % 8;
                        } while (obj->slots[*cur] == NULL);
                    }
                }
                if (PAD_001EAA60(1, 0x10) != 0) {
                    if (PAD_001EAA60(0, 0x10) != 0) {
                        func_001F1480(index, *cur);
                    } else {
                        if (PAD_001EAA60(2, 2) != 0) {
                            func_001F1A80(index, anim[0] + 0.1f);
                        }
                        if (PAD_001EAA60(2, 1) != 0) {
                            func_001F1A80(index, anim[0] - 0.1f);
                        }
                    }
                }
                if (PAD_001EAA60(0, 0xF000) != 0) {
                    sel = 0;
                    if (PAD_001EAA60(0, 0x1000) != 0) {
                        sel = 0;
                    } else if (PAD_001EAA60(0, 0x2000) != 0) {
                        sel = 1;
                    } else if (PAD_001EAA60(0, 0x4000) != 0) {
                        sel = 2;
                    } else if (PAD_001EAA60(0, 0x8000) != 0) {
                        sel = 3;
                    }
                    if (PAD_001EAA60(1, 0x10) != 0) {
                        sel += 4;
                    }
                    func_001F1550(index, sel);
                }
                if (PAD_001EAA60(1, 0x40) != 0 || obj->loop == 0) {
                    if (PAD_001EAA60(2, 0x20) != 0) {
                        obj->loop = 1;
                        if (!(anim[1] < last)) {
                            anim[1] = 1.0f;
                        } else {
                            anim[1] += anim[0];
                            if (!(anim[1] <= last)) {
                                anim[1] = last;
                            }
                        }
                    }
                    if (PAD_001EAA60(2, 0x80) != 0) {
                        obj->loop = -1;
                        if (anim[1] <= 1.0f) {
                            anim[1] = last;
                        } else {
                            anim[1] -= anim[0];
                            if (anim[1] < 1.0f) {
                                anim[1] = 1.0f;
                            }
                        }
                    }
                    if (PAD_001EAA60(1, 0x40) != 0) {
                        obj->loop = 0;
                    }
                } else {
                    if (PAD_001EAA60(0, 0x20) != 0) {
                        obj->loop = 1;
                    }
                    if (PAD_001EAA60(0, 0x80) != 0) {
                        obj->loop = -1;
                    }
                }
            }
        }
        if (page == 2) {
            switch (nBlurCur) {
            case 0:
                flag = 0;
                flag2 = 0;
                if (PAD_001EAA60(0, 0x4000) != 0) {
                    wAlphaMode = 0;
                    wFrame = 6;
                }
                if (!(PAD_001EAA60(1, 3) & 0xFFFF)) {
                    if (PAD_001EAA60(1, 0x1000) != 0) {
                        if (PAD_001EAA60(2, 0xC) != 0) {
                            if (PAD_001EAA60(2, 4) != 0) {
                                wAlphaMode = (wAlphaMode + 3) % 4;
                            } else {
                                wAlphaMode = (wAlphaMode + 5) % 4;
                            }
                        }
                    } else if (PAD_001EAA60(2, 0xC) != 0) {
                        if (PAD_001EAA60(2, 4) != 0) {
                            n = wFrame - 1;
                            wFrame = (n > 1) ? n : 1;
                        } else {
                            n = wFrame + 1;
                            wFrame = (n < 0x63) ? n : 0x63;
                        }
                    }
                }
                if (PAD_001EAA60(1, 0x10) != 0) {
                    if (func_001A8720() & 1) {
                        flag = 1;
                        flag2 = 1;
                    }
                }
                if (PAD_001EAA60(1, 0x80) != 0) {
                    if (func_001A8720() & 1) {
                        flag2 = 1;
                    }
                }
                if (PAD_001EAA60(0, 0x20) != 0) {
                    flag2 = 1;
                }
                if (flag2 != 0) {
                    func_001EDCB0(index, wFrame, wAlphaMode, icolF, icolT, flag);
                }
                break;
            case 1:
                if (PAD_001EAA60(0, 0x4000) != 0) {
                    icolF[0] = 0x80;
                    icolF[1] = 0x80;
                    icolF[2] = 0x80;
                    icolF[3] = 0x40;
                }
                if (PAD_001EAA60(1, 0x1000) != 0) {
                    if (PAD_001EAA60(2, 0x80) != 0) {
                        if (icolF[3] > 0) {
                            icolF[3]--;
                        }
                    }
                    if (PAD_001EAA60(2, 0x20) != 0 && icolF[3] < 0xFF) {
                        icolF[3]++;
                    }
                } else {
                    if (PAD_001EAA60(2, 0x81) != 0) {
                        if (icolF[2] > 0) {
                            icolF[2]--;
                        }
                    }
                    if (PAD_001EAA60(2, 0x22) != 0) {
                        if (icolF[2] < 0xFF) {
                            icolF[2]++;
                        }
                    }
                    if (PAD_001EAA60(2, 0x41) != 0) {
                        if (icolF[1] > 0) {
                            icolF[1]--;
                        }
                    }
                    if (PAD_001EAA60(2, 0x12) != 0) {
                        if (icolF[1] < 0xFF) {
                            icolF[1]++;
                        }
                    }
                    if (PAD_001EAA60(2, 5) != 0) {
                        if (icolF[0] > 0) {
                            icolF[0]--;
                        }
                    }
                    if (PAD_001EAA60(2, 0xA) != 0 && icolF[0] < 0xFF) {
                        icolF[0]++;
                    }
                }
                break;
            case 2:
                if (PAD_001EAA60(0, 0x4000) != 0) {
                    icolT[0] = 0x80;
                    icolT[1] = 0x80;
                    icolT[2] = 0x80;
                    icolT[3] = 0;
                }
                if (PAD_001EAA60(1, 0x1000) != 0) {
                    if (PAD_001EAA60(2, 0x80) != 0) {
                        if (icolT[3] > 0) {
                            icolT[3]--;
                        }
                    }
                    if (PAD_001EAA60(2, 0x20) != 0 && icolT[3] < 0xFF) {
                        icolT[3]++;
                    }
                } else {
                    if (PAD_001EAA60(2, 0x81) != 0) {
                        if (icolT[2] > 0) {
                            icolT[2]--;
                        }
                    }
                    if (PAD_001EAA60(2, 0x22) != 0) {
                        if (icolT[2] < 0xFF) {
                            icolT[2]++;
                        }
                    }
                    if (PAD_001EAA60(2, 0x41) != 0) {
                        if (icolT[1] > 0) {
                            icolT[1]--;
                        }
                    }
                    if (PAD_001EAA60(2, 0x12) != 0) {
                        if (icolT[1] < 0xFF) {
                            icolT[1]++;
                        }
                    }
                    if (PAD_001EAA60(2, 5) != 0) {
                        if (icolT[0] > 0) {
                            icolT[0]--;
                        }
                    }
                    if (PAD_001EAA60(2, 0xA) != 0 && icolT[0] < 0xFF) {
                        icolT[0]++;
                    }
                }
                break;
            case 3:
                if (PAD_001EAA60(0, 0x4000) != 0) {
                    nBlurUse = 2;
                }
                if (PAD_001EAA60(0, 0x10) != 0) {
                    nBlurUse = 2;
                }
                if (PAD_001EAA60(0, 0xC0) != 0) {
                    nBlurUse = 1;
                }
                if (PAD_001EAA60(0, 0x40) != 0) {
                    nBlurUse = 0;
                }
                break;
            }
            if (PAD_001EAA60(2, 0xA000) != 0) {
                if (PAD_001EAA60(2, 0x8000) != 0) {
                    nBlurCur = (nBlurCur + 3) % 4;
                } else {
                    nBlurCur = (nBlurCur + 5) % 4;
                }
            }
        }
        if (page == 3) {
            Digits4_001EAA60 dig;
            char path[0x80];

            sub = index - 0x1E;
            num = obj->num;
            dig = D_00292F90;
            newnum = num;
            dig.d0 = num / 1000 % 10;
            dig.d1 = num / 100 % 10;
            dig.d2 = num / 10 % 10;
            dig.d3 = num % 10;
            if (PAD_001EAA60(0, 0xC0) != 0) {
                if (obj->anim != NULL) {
                    flag = PAD_001EAA60(1, 3) != 0 ? 1 : 0;
                    dir = PAD_001EAA60(0, 0x80) != 0 ? 1 : 0;
                    func_001FA810(0, 1);
                    snd = obj->sound;
                    if (snd >= 0) {
                        func_001F4CB0(snd);
                    }
                    func_001F1830(0x1E, 0);
                    func_001F1830(0x1F, 0);
                    func_001F1A00(0x1E, 1);
                    func_001F1A00(0x1F, 1);
                    func_001E1E70(sub ^ 1, 0, 5, dir);
                    func_001F0CD0(sub, 1, flag > 0);
                }
            }
            if (PAD_001EAA60(0, 0x600) != 0) {
                if (obj->anim != NULL) {
                    flag = PAD_001EAA60(0, 0x200) != 0 ? 1 : 0;
                    func_001FA810(0, 1);
                    func_001F1830(0x1E, 0);
                    func_001F1A00(0x1E, 1);
                    func_001F1550(index, 5);
                    ap = *(void *volatile *)&obj->anim; /* loaded before f202, as shipped */
                    func_001FA8A0(0, 1, flag + 8, obj->f202, index, ap);
                }
            }
            if (PAD_001EAA60(0, 0x20) != 0) {
                func_001FA810(0, 1);
                snd = obj->sound;
                if (snd >= 0) {
                    func_001F4CB0(snd);
                }
                func_001F1830(0x1E, 0);
                func_001F1830(0x1F, 0);
                func_001F1A00(0x1E, 1);
                func_001F1A00(0x1F, 1);
            }
            if (PAD_001EAA60(0, 0x10) != 0) {
                func_001FA810(0, 1);
                if (obj->model->flags & 0x80000) {
                    obj->anim = NULL;
                } else if (obj->anim != NULL) {
                    func_00217B50((s32)obj->anim);
                    obj->anim = NULL;
                }
                snd = obj->sound;
                if (snd >= 0) {
                    func_001F4CB0(snd);
                }
                func_0019B648(path, D_002CFB7D, func_001FFF90((s32)D_002CFA17_2), num, num);
                func_001FECB0(0x400, 1, path, 0, -1, 0, -1, lSzModel_LoadCameraCB, index);
            }
            if (PAD_001EAA60(2, 0x5000) != 0) {
                if (PAD_001EAA60(2, 0x1000) != 0) {
                    (&dig.d0)[nCameraCur] = ((&dig.d0)[nCameraCur] + 11) % 10;
                } else {
                    (&dig.d0)[nCameraCur] = ((&dig.d0)[nCameraCur] + 9) % 10;
                }
                newnum = (&dig.d0)[0] * 1000 + (&dig.d0)[1] * 100 + (&dig.d0)[2] * 10 + (&dig.d0)[3];
            }
            if (!(PAD_001EAA60(1, 3) & 0xFFFF)) {
                if (PAD_001EAA60(2, 8) != 0) {
                    if (obj->f202 < 0x3E7) {
                        obj->f202++;
                    }
                }
                if (PAD_001EAA60(2, 4) != 0) {
                    if (obj->f202 > 0) {
                        obj->f202--;
                    }
                }
            }
            if (PAD_001EAA60(2, 0x8000) != 0) {
                nCameraCur = (nCameraCur + 3) % 4;
            }
            if (PAD_001EAA60(2, 0x2000) != 0) {
                nCameraCur = (nCameraCur + 5) % 4;
            }
            if (newnum != num) {
                obj->num = newnum;
                func_001FA810(0, 1);
                if (obj->model->flags & 0x80000) {
                    obj->anim = NULL;
                } else if (obj->anim != NULL) {
                    func_00217B50((s32)obj->anim);
                    obj->anim = NULL;
                }
                snd = obj->sound;
                if (snd >= 0) {
                    func_001F4CB0(snd);
                }
            }
        }
        if (page == 4) {
            Digits4_001EAA60 dig2;
            char path2[0x80];
            s32 num;
            s32 i;
            s32 flag;
            s32 newnum;

            num = obj->num;
            dig2 = D_00292FA0;
            newnum = num;
            dig2.d0 = num / 1000 % 10;
            dig2.d1 = num / 100 % 10;
            dig2.d2 = num / 10 % 10;
            dig2.d3 = num % 10;
            if (PAD_001EAA60(0, 0xC0) != 0) {
                flag = PAD_001EAA60(1, 3) != 0 ? 1 : 0;
                PAD_001EAA60(0, 0x80);
                func_001FA810(0, 1);
                func_001F4E50(0, 0x3D);
                func_001F4E50(0, 0x3E);
                func_001F4E50(0, 0x3F);
                func_001F1830(0x20, 0);
                func_001F1A00(0x20, 1);
                func_00202D60(5, -1);
                for (i = 0; i < 8; i++) {
                    func_00202810(5, i, NULL, obj->parts[i]);
                }
                func_001F4900(0, 0x3D, 0, 0, 0, 0, 0);
                func_001F4900(0, 0x3E, 0, 0, 0, 0, 0);
                func_001F4900(0, 0x3F, 0, 0, 0, 0, 0);
                if (obj->anim != NULL) {
                    func_001FA8A0(0, 1, flag + 8, obj->f202, index, obj->anim);
                }
            }
            if (PAD_001EAA60(0, 0x20) != 0) {
                func_001FA810(0, 1);
                func_001F4E50(0, 0x3D);
                func_001F4E50(0, 0x3E);
                func_001F4E50(0, 0x3F);
                func_001F1830(0x20, 0);
                func_001F1A00(0x20, 1);
            }
            if (PAD_001EAA60(0, 0x10) != 0) {
                func_001FA810(0, 1);
                if (obj->model->flags & 0x80000) {
                    obj->anim = NULL;
                } else if (obj->anim != NULL) {
                    func_00217B50((s32)obj->anim);
                    obj->anim = NULL;
                }
                func_001F4E50(0, 0x3D);
                func_001F4E50(0, 0x3E);
                func_001F4E50(0, 0x3F);
                func_0019B648(path2, D_002CFB7D, func_001FFF90((s32)D_002CFA17_2), num, num);
                func_001FECB0(0x400, 1, path2, 0, -1, 0, -1, lSzModel_LoadCameraCB, index);
            }
            if (PAD_001EAA60(2, 0x5000) != 0) {
                if (PAD_001EAA60(2, 0x1000) != 0) {
                    (&dig2.d0)[nCameraCur] = ((&dig2.d0)[nCameraCur] + 11) % 10;
                } else {
                    (&dig2.d0)[nCameraCur] = ((&dig2.d0)[nCameraCur] + 9) % 10;
                }
                newnum = (&dig2.d0)[0] * 1000 + (&dig2.d0)[1] * 100 + (&dig2.d0)[2] * 10 + (&dig2.d0)[3];
            }
            if (!(PAD_001EAA60(1, 3) & 0xFFFF)) {
                if (PAD_001EAA60(2, 8) != 0) {
                    if (obj->f202 < 0x3E7) {
                        obj->f202++;
                    }
                }
                if (PAD_001EAA60(2, 4) != 0) {
                    if (obj->f202 > 0) {
                        obj->f202--;
                    }
                }
            }
            if (PAD_001EAA60(2, 0x8000) != 0) {
                nCameraCur = (nCameraCur + 3) % 4;
            }
            if (PAD_001EAA60(2, 0x2000) != 0) {
                nCameraCur = (nCameraCur + 5) % 4;
            }
            if (newnum != num) {
                obj->num = newnum;
                func_001FA810(0, 1);
                if (obj->model->flags & 0x80000) {
                    obj->anim = NULL;
                } else if (obj->anim != NULL) {
                    func_00217B50((s32)obj->anim);
                    obj->anim = NULL;
                }
                snd = obj->sound;
                if (snd >= 0) {
                    func_001F4CB0(snd);
                }
            }
        }
        if (page == 5) {
            Digits3_001EAA60 d3;
            Digits3_001EAA60 d3b;

            sub = index - 0x1E;
            d3 = D_00292FB0;
            d3.d0 = obj->f206 / 100 % 10;
            d3.d1 = obj->f206 / 10 % 10;
            d3.d2 = obj->f206 % 10;
            d3b = D_00292FC0;
            d3b.d0 = obj->f208 / 100 % 10;
            d3b.d1 = obj->f208 / 10 % 10;
            d3b.d2 = obj->f208 % 10;
            if (PAD_001EAA60(0, 0xC0) != 0) {
                dir = PAD_001EAA60(0, 0x80) != 0 ? 1 : 0;
                snd = obj->sound;
                if (snd >= 0) {
                    func_001F4CB0(snd);
                }
                func_001F1830(0x1E, 0);
                func_001F1830(0x1F, 0);
                func_001F1A00(0x1E, 1);
                func_001F1A00(0x1F, 1);
                func_001E1E70(sub ^ 1, 0, 5, dir);
                func_001F0CD0(sub, 0, 0);
            }
            if (PAD_001EAA60(0, 0x40) != 0) {
                snd = obj->sound;
                if (snd >= 0) {
                    func_001F4CB0(snd);
                }
                func_001F1830(0x1E, 0);
                func_001F1830(0x1F, 0);
                func_001F1A00(0x1E, 1);
                func_001F1A00(0x1F, 1);
            }
            if (PAD_001EAA60(0, 0x10) != 0) {
                while (func_001FF350(0x800) != 0) {
                    func_001FF420();
                }
                func_001F4E50(-1, -1);
                func_001F3790();
            }
            switch (nEffCur2) {
            case 0:
                if (PAD_001EAA60(2, 0x2000) != 0) {
                    if (++nEffCur > 2) {
                        nEffCur = 0;
                        nEffCur2 = 1;
                    }
                } else if (PAD_001EAA60(2, 0x8000) != 0) {
                    if (--nEffCur < 0) {
                        nEffCur2 = 1;
                        nEffCur = 2;
                    }
                } else if (PAD_001EAA60(2, 0x5000) != 0) {
                    if (PAD_001EAA60(2, 0x1000) != 0) {
                        (&d3.d0)[nEffCur] = ((&d3.d0)[nEffCur] + 11) % 10;
                    } else {
                        (&d3.d0)[nEffCur] = ((&d3.d0)[nEffCur] + 9) % 10;
                    }
                    obj->f206 = (&d3.d0)[0] * 100 + (&d3.d0)[1] * 10 + (&d3.d0)[2];
                }
                break;
            case 1:
                if (PAD_001EAA60(2, 0x2000) != 0) {
                    if (++nEffCur > 2) {
                        nEffCur2 = 0;
                        nEffCur = 0;
                    }
                } else if (PAD_001EAA60(2, 0x8000) != 0) {
                    if (--nEffCur < 0) {
                        nEffCur2 = 0;
                        nEffCur = 2;
                    }
                } else if (PAD_001EAA60(2, 0x5000) != 0) {
                    if (PAD_001EAA60(2, 0x1000) != 0) {
                        (&d3b.d0)[nEffCur] = ((&d3b.d0)[nEffCur] + 11) % 10;
                    } else {
                        (&d3b.d0)[nEffCur] = ((&d3b.d0)[nEffCur] + 9) % 10;
                    }
                    obj->f208 = (&d3b.d0)[0] * 100 + (&d3b.d0)[1] * 10 + (&d3b.d0)[2];
                }
                break;
            }
        }
        if (page == 6) {
            if (PAD_001EAA60(0, 0xC0) != 0) {
                gSzModel_fRefLock = 1;
            }
            if (PAD_001EAA60(0, 0x40) != 0) {
                gSzModel_fRefLock = 0;
            }
            if (PAD_001EAA60(2, 4) != 0) {
                gSzModel_nRefLock = (gSzModel_nRefLock + obj->count - 1) % obj->count;
            }
            if (PAD_001EAA60(2, 8) != 0) {
                gSzModel_nRefLock = (gSzModel_nRefLock + obj->count + 1) % obj->count;
            }
        }
        if (page == 7) {
            if (PAD_001EAA60(2, 0x8000) != 0) {
                obj->pos[0] -= 0.5f;
            }
            if (PAD_001EAA60(2, 0x2000) != 0) {
                obj->pos[0] += 0.5f;
            }
            if (PAD_001EAA60(2, 0x4000) != 0) {
                obj->pos[1] -= 0.5f;
            }
            if (PAD_001EAA60(2, 0x1000) != 0) {
                obj->pos[1] += 0.5f;
            }
            if (PAD_001EAA60(2, 4) != 0) {
                obj->pos[2] -= 0.5f;
            }
            if (PAD_001EAA60(2, 8) != 0) {
                obj->pos[2] += 0.5f;
            }
            if (PAD_001EAA60(2, 0x80) != 0) {
                obj->rot[1] = (obj->rot[1] + 0xFF00) % 0x10000;
            }
            if (PAD_001EAA60(2, 0x20) != 0) {
                obj->rot[1] = (obj->rot[1] + 0x10100) % 0x10000;
            }
            if (PAD_001EAA60(2, 0x40) != 0) {
                obj->rot[0] = (obj->rot[0] + 0xFF00) % 0x10000;
            }
            if (PAD_001EAA60(2, 0x10) != 0) {
                obj->rot[0] = (obj->rot[0] + 0x10100) % 0x10000;
            }
            if (PAD_001EAA60(2, 1) != 0) {
                obj->rot[2] = (obj->rot[2] + 0xFF00) % 0x10000;
            }
            if (PAD_001EAA60(2, 2) != 0) {
                obj->rot[2] = (obj->rot[2] + 0x10100) % 0x10000;
            }
        }
        if (page == 8) {
            if (PAD_001EAA60(0, 0x4000) != 0) {
                func_001F25D0(index, NULL);
            }
            if (PAD_001EAA60(2, 0x81) != 0) {
                obj->v.x -= 0.01f;
            }
            if (PAD_001EAA60(2, 0x22) != 0) {
                obj->v.x += 0.01f;
            }
            if (PAD_001EAA60(2, 0x41) != 0) {
                obj->v.y -= 0.01f;
            }
            if (PAD_001EAA60(2, 0x12) != 0) {
                obj->v.y += 0.01f;
            }
            if (PAD_001EAA60(2, 5) != 0) {
                obj->v.z -= 0.01f;
            }
            if (PAD_001EAA60(2, 0xA) != 0) {
                obj->v.z += 0.01f;
            }
        }
        if (page == 9) {
            if (PAD_001EAA60(0, 0x4000) != 0) {
                func_001F1EE0(index, NULL);
            }
            if (PAD_001EAA60(2, 0x81) != 0) {
                obj->light[0] -= 0.01f;
            }
            if (PAD_001EAA60(2, 0x22) != 0) {
                obj->light[0] += 0.01f;
            }
            if (PAD_001EAA60(2, 0x41) != 0) {
                obj->light[1] -= 0.01f;
            }
            if (PAD_001EAA60(2, 0x12) != 0) {
                obj->light[1] += 0.01f;
            }
            if (PAD_001EAA60(2, 4) != 0) {
                obj->light[2] -= 0.01f;
            }
            if (PAD_001EAA60(2, 8) != 0) {
                obj->light[2] += 0.01f;
            }
        }
        if (page == 10) {
            if (PAD_001EAA60(0, 0x4000) != 0) {
                func_001F26E0(index, 0, NULL);
            }
            if (PAD_001EAA60(2, 0x8000) != 0) {
                obj->fog0 = (obj->fog0 + 3) % 4;
            }
            if (PAD_001EAA60(2, 0x2000) != 0) {
                obj->fog0 = (obj->fog0 + 5) % 4;
            }
            if (PAD_001EAA60(1, 0x1000) != 0) {
                if (PAD_001EAA60(2, 0x80) != 0) {
                    if (obj->col0[3] > 0) {
                        obj->col0[3]--;
                    }
                }
                if (PAD_001EAA60(2, 0x20) != 0) {
                    if (obj->col0[3] < 0xFF) {
                        obj->col0[3]++;
                    }
                }
            } else {
                if (PAD_001EAA60(2, 0x81) != 0) {
                    if (obj->col0[2] > 0) {
                        obj->col0[2]--;
                    }
                }
                if (PAD_001EAA60(2, 0x22) != 0) {
                    if (obj->col0[2] < 0xFF) {
                        obj->col0[2]++;
                    }
                }
                if (PAD_001EAA60(2, 0x41) != 0) {
                    if (obj->col0[1] > 0) {
                        obj->col0[1]--;
                    }
                }
                if (PAD_001EAA60(2, 0x12) != 0) {
                    if (obj->col0[1] < 0xFF) {
                        obj->col0[1]++;
                    }
                }
                if (PAD_001EAA60(2, 5) != 0) {
                    if (obj->col0[0] > 0) {
                        obj->col0[0]--;
                    }
                }
                if (PAD_001EAA60(2, 0xA) != 0) {
                    if (obj->col0[0] < 0xFF) {
                        obj->col0[0]++;
                    }
                }
            }
        }
        if (page == 11) {
            if (PAD_001EAA60(0, 0x4000) != 0) {
                func_001F2860(index, 1, NULL);
            }
            if (PAD_001EAA60(2, 0x8000) != 0) {
                obj->fog1 = (obj->fog1 + 3) % 4;
            }
            if (PAD_001EAA60(2, 0x2000) != 0) {
                obj->fog1 = (obj->fog1 + 5) % 4;
            }
            if (PAD_001EAA60(1, 0x1000) != 0) {
                if (PAD_001EAA60(2, 0x80) != 0) {
                    if (obj->col1[3] > 0) {
                        obj->col1[3]--;
                    }
                }
                if (PAD_001EAA60(2, 0x20) != 0) {
                    if (obj->col1[3] < 0xFF) {
                        obj->col1[3]++;
                    }
                }
            } else {
                if (PAD_001EAA60(2, 0x81) != 0) {
                    if (obj->col1[2] > 0) {
                        obj->col1[2]--;
                    }
                }
                if (PAD_001EAA60(2, 0x22) != 0) {
                    if (obj->col1[2] < 0xFF) {
                        obj->col1[2]++;
                    }
                }
                if (PAD_001EAA60(2, 0x41) != 0) {
                    if (obj->col1[1] > 0) {
                        obj->col1[1]--;
                    }
                }
                if (PAD_001EAA60(2, 0x12) != 0) {
                    if (obj->col1[1] < 0xFF) {
                        obj->col1[1]++;
                    }
                }
                if (PAD_001EAA60(2, 5) != 0) {
                    if (obj->col1[0] > 0) {
                        obj->col1[0]--;
                    }
                }
                if (PAD_001EAA60(2, 0xA) != 0) {
                    if (obj->col1[0] < 0xFF) {
                        obj->col1[0]++;
                    }
                }
            }
        }
        if (mode == 5 && nBlurUse != 0 && (func_001A8720() & 1)) {
            func_001EDCB0(index, wFrame, wAlphaMode, icolF, icolT, nBlurUse == 1 ? 0 : 1);
        }
        if (func_00205170() == 0) {
            s8 kind = obj->kind;

            if (kind == 5 && mode == 5) {
                if (page == 3) {
                    pos = 1000;
                    i = nCameraCur;
                    while (i-- != 0) {
                        pos /= 10;
                    }
                }
                if (page == 5) {
                    pos = 100;
                    i = nEffCur;
                    while (i-- != 0) {
                        pos /= 10;
                    }
                }
            }
            if (kind == 6 && mode == 0 && page == 4) {
                pos = 1000;
                i = nCameraCur;
                while (i-- != 0) {
                    pos /= 10;
                }
            }
        }
    }
    return 1;
}

#undef PAD_001EAA60

/* An effect attached to model slot `index` has finished: clears the model's effect reference. */
void lSzModel_EffectCB(s32 index) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return;
    }
    obj = modelSlots[index];
    if (obj != NULL) {
        *(s32 *)((u8 *)obj + 0x1EC) = -1;
    }
}

typedef struct {
    f32 speed;
    f32 frame;
    f32 blend;
} Animation_001ED4A0;

typedef struct {
    s8 b0 : 1;
    s8 b1 : 1;
    s8 b2 : 1;
    s8 b3 : 1;
    s8 b4 : 1;
    s8 b5 : 1;
    s8 b6 : 1;
    s8 b7 : 1;
} Flags_001ED4A0;

typedef struct {
    s8 reserved : 6;
    s8 direction : 2;
} Direction_001ED4A0;

/* View used only for fields absent from Obj_0031ABB0. */
typedef struct {
    u8 pad000[0x1F2];
    s8 status;
    u8 pad1F3[4];
    Direction_001ED4A0 control;
    u8 pad1F8[3];
    u8 duration;
    u8 progress;
    u8 pause;
    u8 pad1FE;
    u8 fade;
    u8 pad200[12];
    Flags_001ED4A0 flags;
    Flags_001ED4A0 options;
} Fields_001ED4A0;

/* Advances model slot `index`'s animation by one game frame (speed, blending, loops, the end of a one-shot
   motion). */
s32 SzModel_Motion(s32 index)
{
    Fields_001ED4A0 *fields;
    Obj_0031ABB0 *obj;
    Animation_001ED4A0 *animation;
    Animation_001ED4A0 *previous;
    s8 *current_slot;
    s8 *previous_slot;
    s8 *next_slot;
    f32 ticks;
    extern s32 SzGame_GetFrameSpeed();

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    fields = (Fields_001ED4A0 *)obj;
    animation = (Animation_001ED4A0 *)&obj->slots[8];
    previous = (Animation_001ED4A0 *)&obj->slots[11];
    current_slot = &obj->lv[0];
    previous_slot = &obj->lv[1];
    next_slot = &obj->lv[3];
    ticks = (f32)SzGame_GetFrameSpeed();
    if (fields->status < 0) {
        return 0;
    }
    if (((s32 *)obj)[0x138 / 4] == 0) {
        return 0;
    }
    if (fields->flags.b3) {
        return 0;
    }
    if (!fields->flags.b1) {
        return 0;
    }
    if (fields->options.b0) {
        return 1;
    }

    if (*previous_slot >= 0 && obj->slots[*previous_slot] != NULL) {
        f32 end = (f32)(u32)obj->vals[*previous_slot] - 1.0f;
        f32 advance = previous->speed * ticks;
        s32 direction = fields->control.direction;
        if (direction == 1) {
            if (!(previous->frame < end)) {
                previous->frame = 1.0f;
            } else {
                previous->frame += advance;
                if (!(previous->frame <= end)) {
                    previous->frame = end;
                }
            }
        } else if (direction == -1) {
            if (previous->frame <= 1.0f) {
                previous->frame = end;
            } else {
                previous->frame -= advance;
                if (previous->frame < 1.0f) {
                    previous->frame = 1.0f;
                }
            }
        }
        animation->blend = (f32)(u32)fields->progress /
                           (f32)(u32)fields->duration;
        {
            u8 progress = (u32)fields->progress + 1;
            fields->progress = progress;
            if (progress >= (s32)fields->duration) {
                *previous_slot = -1;
                animation->blend = 1.0f;
                fields->progress = 0;
            }
        }
        previous->blend = 1.0f - animation->blend;
    }

    if (obj->slots[*current_slot] != NULL) {
        f32 end = (f32)(u32)obj->vals[*current_slot] - 1.0f;
        f32 advance = animation->speed * ticks;
        if (fields->control.direction != 0) {
            switch (*current_slot) {
            case 6:
                if (!(animation->frame < 10.0f)) {
                    if (fields->pause < 15) {
                        ++fields->pause;
                        advance = 0.0f;
                    }
                }
                break;
            case 3:
            case 4:
                if (!(animation->frame < end)) {
                    fields->control.direction = 0;
                }
                break;
            }
        }
        if (fields->control.direction == 1) {
            if (!(animation->frame < end)) {
                animation->frame = 1.0f;
                if (*next_slot >= 0 && *current_slot != *next_slot) {
                    *previous = *animation;
                    *previous_slot = -1;
                    *current_slot = *next_slot;
                    fields->pause = 0;
                }
            } else {
                animation->frame += advance;
                if (!(animation->frame <= end)) {
                    animation->frame = end;
                }
            }
        } else if (fields->control.direction == -1) {
            if (animation->frame <= 1.0f) {
                animation->frame = end;
                if (*next_slot >= 0 && *current_slot != *next_slot) {
                    *previous = *animation;
                    *previous_slot = -1;
                    *current_slot = *next_slot;
                    animation->frame = (f32)(u32)obj->vals[*current_slot] - 1.0f;
                    fields->pause = 0;
                }
            } else {
                animation->frame -= advance;
                if (animation->frame < 1.0f) {
                    animation->frame = 1.0f;
                }
            }
        }
    }

    if (fields->flags.b4) {
        if (fields->fade < 32) {
            ++fields->fade;
        }
    } else if (fields->fade > 0) {
        --fields->fade;
    }
    return 1;
}

struct DotrObjectVector3 {
    float x, y, z;
};
struct DotrObjectVector4 {
    float x, y, z;
    float unknown_w;
};
struct DotrObjectLink {
    int unknown_00;
    int unknown_04;
};
struct DotrObjectPair {
    signed char unknown_bits_0_5 : 6;
    signed char unknown_bits_6_7 : 2;
};
struct DotrObjectBits {
    signed char unknown_bit_0 : 1;
    signed char unknown_bit_1 : 1;
    signed char unknown_bit_2 : 1;
    signed char unknown_bit_3 : 1;
    signed char unknown_bit_4 : 1;
    signed char unknown_bit_5 : 1;
    signed char unknown_bit_6 : 1;
    signed char unknown_bit_7 : 1;
};
struct DotrObjectLowPair {
    unsigned char unknown_bits_0_1 : 2;
    unsigned char unknown_bits_2_3 : 2;
    unsigned char unknown_bits_4_7 : 4;
};
struct DotrObjectQuad {
    unsigned char unknown_0;
    unsigned char unknown_1;
    unsigned char unknown_2;
    unsigned char unknown_3;
};
struct DotrObject {
    struct DotrObjectVector4 unknown_000;
    struct DotrObjectVector4 unknown_010;
    struct DotrObjectVector4 unknown_020;
    struct DotrObjectVector4 unknown_030;
    unsigned char unknown_040[0x40];
    struct DotrObjectVector4 unknown_080;
    unsigned char unknown_090[0x10];
    struct DotrObjectVector4 unknown_0a0[8];
    struct DotrObjectVector3 unknown_120;
    struct DotrObjectQuad unknown_12c;
    struct DotrObjectQuad unknown_130;
    int unknown_134;
    struct DotrObjectLink *unknown_138;
    unsigned char unknown_13c[8];
    unsigned char unknown_144[0x20];
    int unknown_164;
    int unknown_168;
    int unknown_16c;
    int unknown_170;
    unsigned char unknown_174[4];
    int unknown_178[8];
    

    struct DotrObjectVector3 unknown_198[2];
    unsigned short unknown_1b0[8];
    unsigned unknown_1c0[8];
    signed char unknown_1e0[4];
    float unknown_1e4;
    unsigned char unknown_1e8[8];
    short unknown_1f0;
    signed char unknown_1f2;
    signed char unknown_1f3;
    short unknown_1f4;
    unsigned char unknown_1f6;
    struct DotrObjectPair unknown_1f7;
    struct DotrObjectLowPair unknown_1f8;
    unsigned char unknown_1f9;
    unsigned char unknown_1fa;
    unsigned char unknown_1fb;
    unsigned char unknown_1fc;
    unsigned char unknown_1fd;
    unsigned char unknown_1fe;
    unsigned char unknown_1ff;
    unsigned char unknown_200;
    unsigned char unknown_201[9];
    unsigned short unknown_20a;
    struct DotrObjectBits unknown_20c;
    struct DotrObjectBits unknown_20d;
};
extern struct DotrObject *D_0031ABB0_b_2[];
struct DotrObjectCue {
    unsigned short kind : 4;
    unsigned short time : 12;
    unsigned short code;
};
extern int func_001A8760_b(void);

/* Plays the sound effects model slot `index`'s current animation asks for at this frame, on `channel`. */
int SzModel_ReqSE(int channel, int index)
{
    struct DotrObject *p;
    int kind;
    struct DotrObjectCue *cue;
    int i;
    float previous;
    float now;

    if (channel != 2 && channel != 3) {
        return 0;
    }
    if (index < 0 || index >= 84) {
        return 0;
    }
    p = D_0031ABB0_b_2[index];
    if (p == 0) {
        return 0;
    }
    if (p->unknown_1f2 < 0) {
        return 0;
    }
    if (p->unknown_138 == 0) {
        return 0;
    }
    if (p->unknown_20c.unknown_bit_3) {
        return 0;
    }
    if (!p->unknown_20c.unknown_bit_1) {
        return 0;
    }
    if (p->unknown_20d.unknown_bit_0) {
        return 0;
    }
    if (*(int *)&p->unknown_1e8[4] < 0 && p->unknown_1f7.unknown_bits_6_7 != 1) {
        return 0;
    }
    cue = *(struct DotrObjectCue **)p->unknown_174;
    if (cue != 0) {
        kind = p->unknown_1e0[0];
        previous = func_001A8760_b();
        now = p->unknown_198[0].y;
        if (*(int *)&p->unknown_1e8[4] >= 0) {
            kind = 2;
            now = SzEffect_GetCount(*(int *)&p->unknown_1e8[4]);
        }
        previous = now - previous;
        for (i = 0; i < 64; i++, cue++) {
            if (cue->kind == 15) {
                break;
            }
            if (cue->kind == kind) {
                if (cue->time >= previous && cue->time < now) {
                    SzSound_PlaySE(channel, cue->code);
                }
            }
        }
        return 1;
    }
    return 0;
}

typedef struct {
    f32 x, y, z;
} Vec3_001EDCB0;

typedef struct {
    u8 r, g, b, a;
} Color_001EDCB0;

typedef struct {
    u8 unused : 3;
    u8 mode : 2;
    u8 unused2 : 2;
    s8 enabled : 1;
} Flags_001EDCB0;

typedef struct {
    u8 mode : 2;
    u8 unused : 6;
} ObjFlags_001EDCB0;

typedef struct {
    u8 pad00[0x40];
    Vec3_001EDCB0 position[2];
    s8 lv[2];
    Color_001EDCB0 color0, color1;
    s16 duration;
    s16 counter;
    u8 pad66[2];
    s32 owner : 27;
    u32 unused : 5;
    u8 pad6C[4];
} Entry_001EDCB0;

/* Starts a motion blur trail on model slot `index` for `duration` frames, fading from colour0 to colour1. */
s32 SzModel_ReqMotionBlur(s32 index, s16 duration, s32 mode, void *color0, void *color1, s32 enabled) {
    extern Entry_001EDCB0 D_0031AD70[];
    Obj_0031ABB0 *obj;
    Entry_001EDCB0 *entry;
    s32 i;
    s32 j;

    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    if (*(s8 *)((u8 *)obj + 0x1F3) != 4 && *(s8 *)((u8 *)obj + 0x1F3) != 5) {
        return 0;
    }
    i = 1;
    entry = D_0031AD70;
    for (; i < 32; i++, entry++) {
        if (entry->owner < 0) {
            u8 *source;
            u8 *destination;
            j = 0;
            source = (u8 *)obj;
            destination = (u8 *)entry;
            do {
                *(Vec3_001EDCB0 *)(destination + 0x40) = *(Vec3_001EDCB0 *)(source + 0x198);
                entry->lv[j] = obj->lv[j];
                source += sizeof(Vec3_001EDCB0);
                destination += sizeof(Vec3_001EDCB0);
                j++;
            } while (j < 2);
            RhMem_CopyMemory16(entry, obj, 4);
            if (color0 != NULL) {
                entry->color0 = *(Color_001EDCB0 *)color0;
            } else {
                entry->color0 = *(Color_001EDCB0 *)&obj->pad040[0xEC];
                entry->color1.a = 0x80;
            }
            if (color1 != NULL) {
                entry->color1 = *(Color_001EDCB0 *)color1;
            } else {
                entry->color1 = *(Color_001EDCB0 *)&obj->pad040[0xEC];
                entry->color1.a = 0;
            }
            ((Flags_001EDCB0 *)((u8 *)entry + 0x6B))->mode = mode >= 0
                ? mode
                : (mode = ((ObjFlags_001EDCB0 *)((u8 *)obj + 0x1F8))->mode);
            entry->duration = duration;
            entry->counter = 0;
            ((Flags_001EDCB0 *)((u8 *)entry + 0x6B))->enabled = enabled;
            entry->owner = index;
            return 1;
        }
    }
    return 0;
}

typedef struct Entry_001EDF20 {
    u8 padding[0x68];
    s32 id : 27;
    u32 flags : 5;
    u32 padding_6C;
} Entry_001EDF20;

extern Entry_001EDF20 D_0031AD70[];

/* Stops model slot `index`'s motion blur (-1: every model's). */
void SzModel_CancelMotionBlur(s32 index) {
    s32 i;
    Entry_001EDF20 *entry;
    s32 entryIndex;

    i = 1;
    entry = D_0031AD70;
    do {
        entryIndex = entry->id;
        if (entryIndex >= 0) {
            if (index < 0 || entryIndex == index) {
                entry->id = -1;
            }
        }
        i += 1;
        entry++;
    } while (i < 0x20);
}

/* Draws the motion blur trails of model `index` (-1: all). */
void SzModel_DrawMotionBlur(s32 index) {
    RhBase_SetVifPacketArea(SzModel_DrawMotionBlur_Pipe(RhBase_GetVifPacketArea(), index));
}

typedef struct Vec3_001EDFD0 {
    f32 x;
    f32 y;
    f32 z;
} Vec3_001EDFD0;

typedef struct Color_001EDFD0 {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} Color_001EDFD0;

typedef struct Slot_001EDFD0 {
    u8 pad00[0x40];
    Vec3_001EDFD0 pos[2];
    s8 level[2];
    Color_001EDFD0 color;
    Color_001EDFD0 target;
    u16 duration;
    u16 timer;
    u8 pad66[2];
    s32 index : 27;
    u32 style : 2;
    u32 : 2;
    s32 alternate : 1;
    u8 pad6C[4];
} Slot_001EDFD0;

typedef struct View_001EDFD0 {
    u8 pad000[0x12C];
    Color_001EDFD0 color;
    u8 pad130[0x68];
    Vec3_001EDFD0 pos[2];
    u8 pad1B0[0x30];
    s8 level[2];
    u8 pad1E2[0x16];
    u8 style : 2;
    u8 : 6;
} View_001EDFD0;

/* Draws the motion blur trails of model `index` (-1: all) from their saved poses. */
s32 SzModel_DrawMotionBlur_Pipe(s32 packet, s32 modelIndex) {
    extern Slot_001EDFD0 motionBlurs_2;
    extern Slot_001EDFD0 D_0031BA90;
    extern s32 motionBlurMode;
    extern s32 SzModel_ExSort_Pipe();
    Slot_001EDFD0 *scratch;
    s32 ready;
    s32 remaining;
    View_001EDFD0 *obj;
    Slot_001EDFD0 *slot;
    s32 i;

    scratch = &motionBlurs_2;
    ready = 0;
    motionBlurMode = (modelIndex < 0) ? 2 : 1;
    remaining = 31;
    slot = &D_0031BA90;
    do {
        if (slot->index >= 0 && (modelIndex < 0 || slot->index == modelIndex)) {
            if (SzModel_IsModelDisp(slot->index) == 0) {
                slot->index = -1;
            } else {
                obj = (View_001EDFD0 *)modelSlots[slot->index];
                if (obj == NULL) {
                    goto next;
                }
                if (modelIndex < 0) {
                    if (!slot->alternate) {
                        goto next;
                    }
                } else if (slot->alternate) {
                    goto next;
                }
                {
                    if (!ready) {
                        SzModel_SetDrawCache(0);
                        ready = 1;
                    }
                    for (i = 0; i < 2; i++) {
                        scratch->pos[i] = obj->pos[i];
                        scratch->level[i] = obj->level[i];
                    }
                    RhMem_CopyMemory16(scratch, obj, 4);
                    scratch->color = obj->color;
                    scratch->style = obj->style;
                    for (i = 0; i < 2; i++) {
                        obj->pos[i] = slot->pos[i];
                        obj->level[i] = slot->level[i];
                    }
                    RhMem_CopyMemory16(obj, slot, 4);
                    obj->color.b = (slot->color.b * (slot->duration - slot->timer) + slot->target.b * slot->timer) /
                                   slot->duration;
                    obj->color.g = (slot->color.g * (slot->duration - slot->timer) + slot->target.g * slot->timer) /
                                   slot->duration;
                    obj->color.r = (slot->color.r * (slot->duration - slot->timer) + slot->target.r * slot->timer) /
                                   slot->duration;
                    obj->color.a = (slot->color.a * (slot->duration - slot->timer) + slot->target.a * slot->timer) /
                                   slot->duration;
                    obj->style = slot->style;
                    if (slot->alternate) {
                        packet = SzModel_ExSort_Pipe(packet, slot->index, 0, 0, 0, 0, 0x80FFFFF5);
                    } else {
                        packet = SzModel_Draw_Pipe(packet, slot->index, 0, 0, 0, 0, 0x80FFFFF5);
                    }
                    for (i = 0; i < 2; i++) {
                        obj->pos[i] = scratch->pos[i];
                        obj->level[i] = scratch->level[i];
                    }
                    RhMem_CopyMemory16(obj, scratch, 4);
                    obj->color = scratch->color;
                    obj->style = scratch->style;
                    if (++slot->timer >= slot->duration) {
                        slot->index = -1;
                    }
                }
            }
        }
    next:
        remaining--;
        slot--;
    } while (remaining > 0);
    if (ready) {
        SzModel_SetDrawCache(0);
    }
    motionBlurMode = 0;
    return packet;
}

/* Sets the draw cache function used by the model drawing. */
void SzModel_SetDrawCache(s32 cache) {
    modelDrawCache = cache;
}

/* Draws model slot `index`, moved by `pos`, `rot` and `scale` if given (texture-animated kinds draw through their
   own function). */
s32 SzModel_Draw_Pipe(s32 packet, s32 index, s32 pos, s32 rot, s32 scale, s32 header, s32 flags) {
    Obj_0031ABB0 *obj;
    s8 kind;
    void *data;
    void (*callback)(void) = NULL;

    if ((index < 0) || (index >= 0x54)) {
        return packet;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return packet;
    }
    if (*(s32 *)((u8 *)obj + 0x138) == 0) {
        return packet;
    }
    data = *(void **)((u8 *)obj + 0x13C);
    if (data == NULL) {
        return packet;
    }
    kind = *(s8 *)((u8 *)obj + 0x1F3);
    if ((kind == 4) || (kind == 5U) || (kind == 6)) {
        if (*(s32 *)((u8 *)data + 0x1C) != 0) {
            callback = lSzModel_Draw_DefFunc;
        }
    }
    return SzModel_DrawWithFunc_Pipe(packet, index, pos, rot, scale, header, flags, callback, 0);
}

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Xyzf_001EE570;

typedef struct {
    u16 count;
    u16 kind;
    u32 flags;
    u64 regs;
} Header_001EE570;

typedef struct {
    u64 dmatag;
    Header_001EE570 header;
    u8 r;
    u8 g;
    u8 b;
    u8 a;
    f32 q;
    f32 s0;
    f32 t0;
    Xyzf_001EE570 v0;
    f32 s1;
    f32 t1;
    Xyzf_001EE570 v1;
    u64 extra[3];
} Packet_001EE570;

/* The default per-model draw callback: copies the frame buffer into a texture and draws it back masked. */
void lSzModel_Draw_DefFunc(s32 cursor) {
    extern s32 ExFrameBuffer2Texture_Pipe();
    extern s32 RhBase_MaskFBuffer();
    Packet_001EE570 packet;

    ((Header_001EE570 *)&packet.header)->kind = 0x26;
    ((Header_001EE570 *)&packet.header)->count = 5;
    ((Header_001EE570 *)&packet.header)->regs = 0x42421;
    ((Header_001EE570 *)&packet.header)->flags = 0;
    packet.r = 0x80;
    packet.g = 0x80;
    packet.b = 0x80;
    packet.a = 0x80;
    packet.q = 1.0f;
    packet.v0.x = 0x6BF8;
    packet.v0.y = 0x71F8;
    packet.v0.z = 0xFFFFFF;
    packet.v0.fog = 0;
    packet.v1.x = 0x93F8;
    packet.v1.y = 0x8DF8;
    packet.v1.z = 0xFFFFFF;
    packet.v1.fog = 0;
    packet.s0 = 0.0f;
    packet.t0 = 0.0f;
    packet.s1 = 0.625f;
    packet.t1 = 0.875f;
    RhBase_MaskFBuffer(RhBase_SetZBufferMode(ExSortPrim_Pipe(RhBase_SetZBufferMode(RhBase_MaskFBuffer(RhText_SetTextureFlush(ExFrameBuffer2Texture_Pipe(RhText_SetTextureFlush(cursor), -1, 0, &packet.extra[1], &packet.extra[2])), 0xFF000000), 0), (s32)(&packet.dmatag + 1), 0, 0), 1), 0);
}

typedef union { __int128 q; f32 f[4]; } Vector_001EE6C0;
typedef union { __int128 q[4]; f32 f[16]; } Matrix_001EE6C0;
typedef union { __int128 q[9]; u8 bytes[0x90]; } Effect_001EE6C0;
typedef struct {
    s8 b0:1, b1:1, b2:1, b3:1, b4:1, b5:1, b6:1, b7:1;
} ObjectFlags_001EE6C0;
typedef struct {
    u8 b0:1, b1:1, b2:1, b3:1, b4:1, b5:1, b6:1, b7:1;
} Flags_001EE6C0;
typedef struct {
    u8 base:2, overlay:2, other:4;
} TextureFlags_001EE6C0;
typedef struct {
    Vector_001EE6C0 position;
    Vector_001EE6C0 extra;
    s32 rotation[4];
    Vector_001EE6C0 scale;
} Transform_001EE6C0;
typedef struct {
    s32 model;
    Flags_001EE6C0 flags0, flags1;
    u8 pad06[2];
    ObjSlot_0031ABB0 *slot0;
    f32 value0;
    ObjSlot_0031ABB0 *slot1;
    f32 value1, value2, value3;
    u8 pad20[0xC];
    s32 depth;
    f32 values[4];
    u8 pad40[0x10];
} Model_001EE6C0;
typedef struct {
    u16 count, type;
    s32 pad04;
    u64 tag;
} Header_001EE6C0;
typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Xyzf_001EE6C0;
typedef struct {
    u16 low : 5;
    u16 flag : 1;
    u16 type : 3;
    u16 high : 7;
} PrimitiveFlags_001EE6C0;
typedef struct {
    Header_001EE6C0 header;
    u8 r, g, b, a;
    f32 q;
    f32 s0, t0;
    Xyzf_001EE6C0 v0;
    f32 s1, t1;
    Xyzf_001EE6C0 v1;
    u64 extra[4];
} Primitive_001EE6C0;
typedef struct {
    Header_001EE6C0 header;
    u8 r, g, b, a;
    f32 q;
    Xyzf_001EE6C0 v0;
    Xyzf_001EE6C0 v1;
    u8 tail[4];
} Sprite_001EE6C0;

extern Vector_001EE6C0 D_00292FD0;
extern Vector_001EE6C0 D_00292FE0;

/* Missing fields in the shared Obj_0031ABB0 declaration, accessed by casts:
 * needs shared field: modelSlots +0x080 f32[4]
 * needs shared field: modelSlots +0x090 f32[4]
 * needs shared field: modelSlots +0x0A0 f32[8][4]
 * needs shared field: modelSlots +0x120 f32
 * needs shared field: modelSlots +0x124 f32
 * needs shared field: modelSlots +0x128 f32
 * needs shared field: modelSlots +0x134 u8*
 * needs shared field: modelSlots +0x138 s32
 * needs shared field: modelSlots +0x13C u8*
 * needs shared field: modelSlots +0x19C f32
 * needs shared field: modelSlots +0x1A0 f32
 * needs shared field: modelSlots +0x1A8 f32
 * needs shared field: modelSlots +0x1AC f32
 * needs shared field: modelSlots +0x1B0 u16[8]
 * needs shared field: modelSlots +0x1E4 f32
 * needs shared field: modelSlots +0x1E8 f32
 * needs shared field: modelSlots +0x1F0 u16
 * needs shared field: modelSlots +0x1F2 s8
 * needs shared field: modelSlots +0x1F3 s8
 * needs shared field: modelSlots +0x1F8 TextureFlags_001EE6C0
 * needs shared field: modelSlots +0x1FE u8
 * needs shared field: modelSlots +0x1FF u8
 * needs shared field: modelSlots +0x20C ObjectFlags_001EE6C0
 */

/* Absolute value. */
static inline f32 abs_001EE6C0(f32 x) {
    return (x >= 0.0f) ? x : -x;
}
#pragma global_optimizer off

/* Draws model slot `index` with draw callback `func`: its transform (plus `pos`, `rot`, `scaleIn`), lights, fog,
   textures and render frame. */
s32 SzModel_DrawWithFunc_Pipe(s32 out, s32 index, s32 pos, s32 rot, s32 scaleIn,
                 s32 headerIn, s32 flags, void (*func)(void), s32 arg_sp0) {
    Matrix_001EE6C0 matrix;
    Vector_001EE6C0 origin;
    Vector_001EE6C0 offset;
    Transform_001EE6C0 transform;
    Effect_001EE6C0 effect0;
    Model_001EE6C0 model;
    Vector_001EE6C0 position;
    Effect_001EE6C0 effect1;
    Primitive_001EE6C0 primitive;
    s32 overlay;
    s32 enabled;
    Obj_0031ABB0 *obj;
    f32 scale;
    f32 scaledY;
    u32 depth;
    void *packet;
    s32 k;
    s32 draw;
    s32 i;
    u8 *p;
    Flags_001EE6C0 *fl;
    Flags_001EE6C0 *f0;
    f32 *sx;
    f32 *sy;
    f32 *sz;
    PrimitiveFlags_001EE6C0 *pflags;
    Xyzf_001EE6C0 *pv0;
    Xyzf_001EE6C0 *pv1;
    Xyzf_001EE6C0 *sv0;
    Xyzf_001EE6C0 *sv1;
    Sprite_001EE6C0 sprite __attribute__((aligned(8)));

    origin = D_00292FD0;
    offset = D_00292FE0;
    enabled = 1;
    overlay = 0;
    draw = 0;
    if (!(SzEffect_IsUse2(0, -1) & 1) && !(SzEffect_IsUse2(1, -1) & 1) &&
        !(SzEffect_IsUse2(2, -1) & 1)) {
        enabled = 0;
    }
    if (headerIn) {
        Header_001EE6C0 *header = (Header_001EE6C0 *)headerIn;
        header->type = 7;
        header->count = 0;
        header->tag = 0;
        header->pad04 = 0;
    }
    if (index < 0 || index >= 0x54) {
        return out;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return out;
    }
    if (*(s8 *)((u8 *)obj + 0x1F2) < 0) {
        return out;
    }
    if (*(s32 *)((u8 *)obj + 0x138) == 0) {
        return out;
    }
    if (((ObjectFlags_001EE6C0 *)((u8 *)obj + 0x20C))->b3) {
        return out;
    }
    if (!((ObjectFlags_001EE6C0 *)((u8 *)obj + 0x20C))->b1) {
        return out;
    }
    if (headerIn == 0) {
        s32 type;
        if (obj->pad040[0xEF] == 0) {
            return out;
        }
        type = *(s8 *)((u8 *)obj + 0x1F3);
        if (type != 4 && type != 5 && type != 6) {
            if (abs_001EE6C0(*(f32 *)((u8 *)obj + 0x128)) <= 0.000001f) {
                return out;
            }
            if (abs_001EE6C0(*(f32 *)((u8 *)obj + 0x120)) <= 0.000001f &&
                abs_001EE6C0(*(f32 *)((u8 *)obj + 0x124)) <= 0.000001f) {
                return out;
            }
        }
    }
    RhMem_CopyMemory16(&transform, obj, 4);
    if (0 != pos) {
        transform.position.f[0] += ((f32 *)pos)[0];
        transform.position.f[1] += ((f32 *)pos)[1];
        transform.position.f[2] += ((f32 *)pos)[2];
    }
    if (rot != 0) {
        transform.rotation[0] += ((s32 *)rot)[0];
        transform.rotation[1] += ((s32 *)rot)[1];
        transform.rotation[2] += ((s32 *)rot)[2];
    }
    if (0 != scaleIn) {
        transform.scale.f[0] *= ((f32 *)scaleIn)[0];
        transform.scale.f[1] *= ((f32 *)scaleIn)[1];
        transform.scale.f[2] *= ((f32 *)scaleIn)[2];
    }
    sx = &transform.scale.f[0];
    sy = &transform.scale.f[1];
    sz = &transform.scale.f[2];
    scale = *sx;
    scaledY = 1.0638298f * *sy;
    scale = (scale > scaledY) ? scale : scaledY;
    if (scale < *sz) {
        scale = *sz;
    }
    if (abs_001EE6C0(scale) <= 0.000001f) {
        return out;
    }
    if (((TextureFlags_001EE6C0 *)((u8 *)obj + 0x1F8))->overlay && obj->pad040[0xF3]) {
        overlay = 1;
    }
    if (headerIn || overlay || motionBlurMode || ((TextureFlags_001EE6C0 *)((u8 *)obj + 0x1F8))->base ||
        obj->pad040[0xEE] != 0x80 || obj->pad040[0xED] != 0x80 ||
        obj->pad040[0xEC] != 0x80 || obj->pad040[0xEF] != 0x80) {
        if (enabled) {
            draw = RhBase_AssignRenderFrame(0, 2, 0x32);
        } else {
            draw = RhBase_AssignRenderFrame(0, 0xA, 0x31);
        }
    }
    if (draw) {
        if (motionBlurMode != 1) {
            modelDrawCache = 0;
        }
        out = (s32)RhBase_EnableRenderFrame((void *)out);
        out = (s32)RhBase_ClearRenderFrame((u8 *)out, 0);
        if (enabled && RhView_PushStack()) {
            RhView_GetCurView(&effect0);
            RhView_SetClipZ(1.0f, 1024.0f);
            RhView_Modify(&effect0);
            out = RhView_SendViewParameters(out);
        }
        if (func) {
            out = ((s32 (*)(s32))func)(out);
        }
    }
    out = SzView_SetLight_Pipe((s32)SzView_SetFog_Pipe((void *)out, 0, *(s8 *)((u8 *)obj + 0x1F3),
                        *(f32 *)((u8 *)obj + 0x128)), 0, *(s8 *)((u8 *)obj + 0x1F3));
    if (modelDrawCache != *(s32 *)((u8 *)obj + 0x138)) {
        s32 result;
        out = SzModel_LoadTexture_Pipe(out, index, *(void **)((u8 *)obj + 0x138), &result);
        modelDrawCache = *(s32 *)((u8 *)obj + 0x138);
    }
    {
        s8 *lv = &obj->lv[0];
        s8 *lvNext = &obj->lv[1];
        f32 *slotpos = (f32 *)&obj->slots[8];
        f32 *slotpos2 = (f32 *)&obj->slots[11];
        RhMem_FillMemory4(&model, 0, 0x18);
        model.model = *(s32 *)((u8 *)obj + 0x138);
        if (*(ObjSlot_0031ABB0 **)((*lv << 2) + (u32)obj + 0x178) != NULL) {
            ((Flags_001EE6C0 *)&model.flags0)->b2 = 1;
            ((Flags_001EE6C0 *)&model.flags0)->b4 = 1;
            model.slot0 = *(ObjSlot_0031ABB0 **)((*lv << 2) + (u32)obj + 0x178);
            model.value0 = slotpos[1];
            model.value2 = slotpos[2];
            if (*lvNext >= 0 && *lvNext != *lv && *(ObjSlot_0031ABB0 **)((*lvNext << 2) + (u32)obj + 0x178) != NULL) {
                ((Flags_001EE6C0 *)&model.flags0)->b3 = 1;
                model.slot1 = *(ObjSlot_0031ABB0 **)((*lvNext << 2) + (u32)obj + 0x178);
                model.value1 = slotpos2[1];
                model.value3 = slotpos2[2];
            }
        }
    }
    if (((ObjectFlags_001EE6C0 *)((u8 *)obj + 0x20C))->b7) {
        model.flags0.b1 = SzView_IsFogZ(0, *(s8 *)((u8 *)obj + 0x1F3));
        model.flags1.b2 = SzView_IsFogY(0, *(s8 *)((u8 *)obj + 0x1F3));
    }
    fl = &model.flags1;
    if (!fl->b2 && SzView_InqPointLight(0, *(s8 *)((u8 *)obj + 0x1F3))) {
        model.flags0.b0 = 1;
    }
    fl->b3 = 1;
    f0 = (Flags_001EE6C0 *)&model.flags0;
    f0->b7 = 1;
    model.values[0] = *(f32 *)((u8 *)obj + 0x120) * *(f32 *)((u8 *)obj + 0x128);
    model.values[1] = *(f32 *)((u8 *)obj + 0x124) * *(f32 *)((u8 *)obj + 0x128);
    model.values[2] = 1.0f;
    if (*(s8 *)((u8 *)obj + 0x1F3) == 4 || *(s8 *)((u8 *)obj + 0x1F3) == 5 ||
        *(s8 *)((u8 *)obj + 0x1F3) == 6) {
        GetAnyCoordinateInit();
        if (*(u8 *)((u8 *)obj + 0x1FE) &&
            ((ObjectFlags_001EE6C0 *)((u8 *)obj + 0x20C))->b6) {
            BookingGetAnyCoordinate(1);
            if (0 == motionBlurMode) {
                if (*(u8 *)((u8 *)obj + 0x1F0) < 0xFF) {
                    BookingGetAnyCoordinate(*(u8 *)((u8 *)obj + 0x1F0));
                }
                *(u16 *)((u8 *)obj + 0x1F0) &= 0x7FFF;
                i = 0;
                p = (u8 *)obj;
                do {
                    if (*(u8 *)(p + 0x1B0) < 0xFF) {
                        BookingGetAnyCoordinate(*(u8 *)(0x1B0 + p));
                    }
                    *(u16 *)(p + 0x1B0) &= 0x7FFF;
                    p += 2;
                    i++;
                } while (i < 8);
            }
            if (((ObjectFlags_001EE6C0 *)((u8 *)obj + 0x20C))->b5) {
                RhGeom_PushMatrix(0);
                *(Vec4f *)&position = *(Vec4f *)((u8 *)obj + 0x80);
                RhGeom_MulMatrixVector(&position, NULL, &position);
                fl->b4 = 1;
                RhGeom_PopMatrix();
            }
            ((ObjectFlags_001EE6C0 *)((u8 *)obj + 0x20C))->b5 = 0;
        }
    }
    RhGeom_PushMatrix(0);
    *(f32 *)(*(u8 **)((u8 *)obj + 0x134) + 0x3C) =
        *(f32 *)((u8 *)obj + 0x1E4) * scale;
    if (*(s8 *)((u8 *)obj + 0x1F3) == 4 || *(s8 *)((u8 *)obj + 0x1F3) == 5 || *(s8 *)((u8 *)obj + 0x1F3) == 6) {
        s32 bounds;
        bounds = lSzModel_GetGNode(index, 1, NULL);
        if (bounds) {
            f32 denominator;
            f32 *o1 = &origin.f[1];
            f32 *o2 = &origin.f[2];
            denominator = *(f32 *)(*(u8 **)((u8 *)obj + 0x13C) + 0x54);
            origin.f[0] = *(f32 *)((u8 *)bounds + 0x20) / denominator;
            *o1 = *(f32 *)((u8 *)bounds + 0x24) / denominator;
            *o2 = *(f32 *)((u8 *)bounds + 0x28) / denominator;
            offset.f[0] = origin.f[0];
            offset.f[1] = *o1;
            offset.f[2] = *o2;
            origin.f[0] *= -1.0f;
            *o1 *= -1.0f;
            *o2 *= -1.0f;
        }
        if (*(u8 *)((u8 *)obj + 0x1FF)) {
            f32 blend = (f32)(u32)*(u8 *)((u8 *)obj + 0x1FF) / 32.0f;
            f32 factor;
            f32 remainder;
            factor = 1.0f + (*(f32 *)((u8 *)obj + 0x1E8) - 1.0f) * blend;
            *(f32 *)(*(u8 **)((u8 *)obj + 0x134) + 0x3C) *= factor;
            remainder = 1.0f - blend;
            *sx *= factor;
            *sy *= factor;
            *sz *= factor;
            offset.f[0] *= remainder;
            offset.f[2] *= remainder;
        }
        RhGeom_ScaleRotXYZTransMatrix(0, 0, (s32 *)&transform.extra, transform.position.f);
        RhGeom_GetScaleRotXYZTransMatrix(&matrix, (f32 *)&transform.scale, transform.rotation, offset.f);
        RhGeom_MulMatrix(0, &matrix);
        RhGeom_GetTransMatrix(&matrix, origin.f);
        RhGeom_MulMatrix(0, &matrix);
        packet = RhModel_Draw((void *)out, &model);
        if (*(u8 *)((u8 *)obj + 0x1FE) &&
            ((ObjectFlags_001EE6C0 *)((u8 *)obj + 0x20C))->b6) {
            if (f0->b2 && GetAnyCoordinate(1, &matrix)) {
                *(f32 *)((u8 *)obj + 0x80) = matrix.f[12];
                *(f32 *)((u8 *)obj + 0x84) = matrix.f[13];
                *(f32 *)((u8 *)obj + 0x88) = matrix.f[14];
                *(f32 *)((u8 *)obj + 0x8C) = 1.0f;
            } else {
                RhView_GetWorldViewMatrix(&matrix);
                RhGeom_InvertMatrix(&matrix, &matrix);
                RhGeom_MulMatrixRev(0, (s32)&matrix);
                RhGeom_MulMatrixVector(&obj->pad040[0x40], NULL, &obj->pad040[0x50]);
            }
            if (!motionBlurMode && f0->b2) {
                if (*(u8 *)((u8 *)obj + 0x1F0) < 0xFF &&
                    GetAnyCoordinate(*(u8 *)((u8 *)obj + 0x1F0), obj->pad040)) {
                    *(u16 *)((u8 *)obj + 0x1F0) |= 0x8000;
                }
                k = 0;
                i = (s32)obj;
                p = (u8 *)obj;
                do {
                    if (*(u8 *)(i + 0x1B0) < 0xFF &&
                        GetAnyCoordinate(*(u8 *)(i + 0x1B0), &matrix)) {
                        *(u16 *)(0x1B0 + i) |= 0x8000;
                        *(f32 *)(p + 0xA0) = matrix.f[12];
                        *(f32 *)(p + 0xA4) = matrix.f[13];
                        *(f32 *)(0xA8 + p) = matrix.f[14];
                        *(f32 *)(0xAC + p) = 1.0f;
                    }
                    k++;
                    i += 2;
                    p += 0x10;
                } while (k < 8);
            }
            ((ObjectFlags_001EE6C0 *)((u8 *)obj + 0x20C))->b5 = 1;
        }
    } else {
        RhGeom_ScaleRotXYZTransMatrix(0, 0, (s32 *)&transform.extra, transform.position.f);
        RhGeom_GetScaleRotXYZTransMatrix(&matrix, (f32 *)&transform.scale, transform.rotation, NULL);
        RhGeom_MulMatrix(0, &matrix);
        packet = RhModel_Draw((void *)out, &model);
        if (((ObjectFlags_001EE6C0 *)((u8 *)obj + 0x20C))->b6) {
            RhView_GetWorldViewMatrix(&matrix);
            RhGeom_InvertMatrix(&matrix, &matrix);
            RhGeom_MulMatrixRev(0, (s32)&matrix);
            RhGeom_MulMatrixVector(&obj->pad040[0x40], NULL, &obj->pad040[0x50]);
            ((ObjectFlags_001EE6C0 *)((u8 *)obj + 0x20C))->b5 = 1;
        }
    }
    RhGeom_PopMatrix();
    *(s32 *)&model.depth = depth = Ex3d_GetSampleZ(&obj->pad040[0x40], 0.0f);
    if (flags && !(flags & 0x80000000)) {
        *(s32 *)flags = *(s32 *)&model.depth;
        if (draw == 0 && *(s32 *)(*(u8 **)((u8 *)obj + 0x13C) + 0x1C) == 0) {
            *(s32 *)flags = 0;
        }
    }
    if (draw != 0) {
        if (0x80000000 & flags) {
            depth = flags & 0x7FFFFFFF;
        }
        if (overlay) {
            ((Header_001EE6C0 *)&sprite.header)->type = 6;
            ((Header_001EE6C0 *)&sprite.header)->count = 3;
            ((Header_001EE6C0 *)&sprite.header)->tag = 0x441;
            ((Header_001EE6C0 *)&sprite.header)->pad04 = 0;
            ExAssignAlpha(&sprite, ExGetAlphaVal(((TextureFlags_001EE6C0 *)((u8 *)obj + 0x1F8))->overlay));
            sprite.r = obj->pad040[0xF2];
            sprite.g = obj->pad040[0xF1];
            sprite.b = obj->pad040[0xF0];
            sprite.a = func_001A23B0((f32)(u32)obj->pad040[0xF3] *
                                         *(f32 *)((u8 *)obj + 0x128));
            sprite.q = 1.0f;
            (sv0 = (Xyzf_001EE6C0 *)&sprite.v0)->x = 0x6C00;
            sprite.v0.y = 0x7200;
            sv0->z = 0xFFFFFF;
            sprite.v0.fog = 0;
            (sv1 = (Xyzf_001EE6C0 *)&sprite.v1)->x = 0x9400;
            sprite.v1.y = 0x8E00;
            sv1->z = 0xFFFFFF;
            sprite.v1.fog = 0;
            packet = RhBase_MaskFBuffer((void *)ExSortPrim_Pipe((s32)RhBase_MaskFBuffer(packet, 0xFF000000), (s32)&sprite, 0, 0), 0);
        }
        if (arg_sp0) {
            packet = ((void *(*)(void *))arg_sp0)(packet);
        }
        ((Header_001EE6C0 *)&primitive.header)->type = 0x26;
        ((Header_001EE6C0 *)&primitive.header)->count = 5;
        ((Header_001EE6C0 *)&primitive.header)->tag = 0x42421;
        ((Header_001EE6C0 *)&primitive.header)->pad04 = 0;
        ExAssignAlpha(&primitive, ExGetAlphaVal(((TextureFlags_001EE6C0 *)((u8 *)obj + 0x1F8))->base));
        primitive.r = obj->pad040[0xEE];
        primitive.g = obj->pad040[0xED];
        primitive.b = obj->pad040[0xEC];
        primitive.a = obj->pad040[0xEF];
        primitive.q = 1.0f;
        (pv0 = (Xyzf_001EE6C0 *)&primitive.v0)->x = 0x6BF8;
        primitive.v0.y = 0x71F8;
        pv0->z = depth;
        primitive.v0.fog = 0;
        (pv1 = (Xyzf_001EE6C0 *)&primitive.v1)->x = 0x93F8;
        primitive.v1.y = 0x8DF8;
        pv1->z = depth;
        primitive.v1.fog = 0;
        primitive.s0 = 0.0f;
        primitive.t0 = 0.0f;
        primitive.s1 = 0.625f;
        primitive.t1 = 0.875f;
        pflags = (PrimitiveFlags_001EE6C0 *)&primitive.extra[2];
        RhBase_GetTextureInfoForRender(&primitive.extra[1], pflags);
        pflags->flag = pflags->type = 0;
        packet = (void *)RhText_SetTextureFlush((s32)RhBase_DisableRenderFrame(packet));
        if (enabled && RhView_PopStack()) {
            RhView_GetCurView(&effect1);
            RhView_Modify(&effect1);
            packet = (void *)RhView_SendViewParameters((s32)packet);
        }
        RhBase_FreeRenderFrame();
        if (headerIn != 0) {
            *(Primitive_001EE6C0 *)headerIn = primitive;
        } else {
            packet = ExDitherMode_Pipe((void *)RhBase_SetZBufferMode(ExSortPrim_Pipe(RhBase_SetZBufferMode((s32)ExDitherMode_Pipe(packet, 0), 0), (s32)&primitive, 0, 0), 1), 1);
        }
        if (1 != motionBlurMode) {
            modelDrawCache = 0;
        }
    }
    return (s32)packet;
}

struct DotrExSortVec {
    float x, y, z, w;
};
extern int D_0031BB00_1ef8a0;
extern long func_00208680_b(int, int);
extern int func_002084D0_b(int, long);
extern int func_00207500_b(void);
#pragma global_optimizer reset

/* Draws model slot `index` sorted by depth (with its motion blur), between anchors. */
int SzModel_ExSort_Pipe(int cursor, int index, int c, int d, int e, int f, int g)
{
    struct DotrExSortVec position;
    int chain;
    int depth;
    int packet;
    int out;
    float dz;
    float z;
    int result;

    modelDrawCache = 0;
    out = ExDitherMatrixEz_Pipe(ExSetAnchor_Pipe(cursor), 2);
    if (D_0031BB00_1ef8a0 == 0) {
        out = SzModel_DrawMotionBlur_Pipe(RhBase_SetZBufferMode(out, 0), index);
    }
    out = RhBase_SetZBufferMode(SzModel_Draw_Pipe(RhBase_SetZBufferMode(out, 1), index, c, d, e, f, g), 0);
    out = ExDitherMatrixEz_Pipe(out, 3);
    packet = func_002084D0_b(out, func_00208680_b(0, 4));
    if (SzModel_GetCenter(index, &position) != 0) {
        depth = SzModel_GetMaxOT(index);
        dz = 0.0f;
        if (depth < 0) {
            depth = 0;
        }
        if (D_0031BB00_1ef8a0 == 2) {
            dz = SzModel_GetRadius(index) / 2.0f;
        }
        z = Ex3d_GetSampleW(&position, dz);
        chain = func_00207500_b();
        depth = z < (float)depth ? depth : func_001A23B0(z);
        result = ExSortAnchor_Pipe(packet, cursor, chain, depth);
    } else {
        return cursor;
    }
    return result;
}

/* Draws model slot `index` with its matrices left as they are (calculation turned off for this draw). */
s32 SzModel_DrawWithOutCalc_Pipe(s32 packet, s32 index, s32 pos, s32 rot, s32 scale, s32 header, s32 flags) {
    s32 saved;

    saved = SzModel_GetCalcFlag(index);
    SzModel_SetCalcFlag(index, 0);
    packet = SzModel_Draw_Pipe(packet, index, pos, rot, scale, header, flags);
    SzModel_SetCalcFlag(index, saved);
    return packet;
}

/* Finds node `node` of model slot `index`'s node tree; the tree's depth through `maxDepth`. */
s32 lSzModel_GetGNode(s32 index, s32 node, s32 *maxDepth) {
    s32 count;
    Obj_0031ABB0 *obj;
    s32 root;

    count = 0;
    if ((index < 0) || (index >= 0x54)) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    if (maxDepth != NULL) {
        *maxDepth = 1;
    }
    root = *(s32 *)((u8 *)obj + 0x134);
    return lSzModel_TraceGNode(node, root, root, &count, 0, maxDepth, 0);
}

typedef struct Node_001EFBD0 {
    u8 pad0[0x1C];
    s32 child;
    u8 pad20[0xC];
    s32 sibling;
} Node_001EFBD0;

/* Walks a model's node tree looking for node `target`. */
s32 lSzModel_TraceGNode(s32 target, s32 base, s32 node, s32 *index,
                  s32 depthAddress, s32 *maxDepth, s32 callbackAddress) {
    s32 nextDepth;
    s32 result;
    s32 currentDepth;

    if (maxDepth != NULL && depthAddress != 0) {
        if (*maxDepth < *(s32 *)depthAddress) {
            *maxDepth = *(s32 *)depthAddress;
        }
    }

    for (;;) {
        if (callbackAddress != 0) {
            ((void (*)(s32, s32))callbackAddress)(*index, node);
        }
        if (target >= 0 && *index == target) {
            return node;
        }
        *index += 1;
        if (*(s32 *)(node + 0x1C) != 0) {
            currentDepth = depthAddress != 0 ? *(s32 *)depthAddress : 1;
            nextDepth = currentDepth + 1;
            result = lSzModel_TraceGNode(target, base,
                base + (*(s32 *)(node + 0x1C) & 0x0FFFFFFF),
                index, (s32)&nextDepth, maxDepth, callbackAddress);
            if (result != 0) {
                if (depthAddress != 0) {
                    *(s32 *)depthAddress += 1;
                }
                return result;
            }
        }
        if (((Node_001EFBD0 *)node)->sibling == 0) {
            break;
        }
        node = base + (((Node_001EFBD0 *)node)->sibling & 0x0FFFFFFF);
    }
    return 0;
}

/* Renders model `index` into a texture (SzModel_ShotTextureWithFunc_Pipe). */
void SzModel_ShotTextureWithFunc(s32 index, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    RhBase_SetVifPacketArea(SzModel_ShotTextureWithFunc_Pipe(RhBase_GetVifPacketArea(), index, arg1, arg2, arg3, arg4, arg5));
}

typedef struct Bits_001EFDC0 {
    u64 low : 5;
    u64 flag : 1;
    u64 kind : 3;
    u64 rest : 55;
} Bits_001EFDC0;

typedef struct Word_001EFDC0 {
    u64 value;
} Word_001EFDC0;

typedef struct Info_001EFDC0 {
    u64 head;
    u8 data[0x40];
    Word_001EFDC0 word;
    Bits_001EFDC0 bits;
} Info_001EFDC0;

/* Renders model slot `index` into a texture of `size`, with draw callback `func` if given; the texture's words
   through outWord / outBits. */
s32 SzModel_ShotTextureWithFunc_Pipe(s32 packet, s32 index, s32 size, s32 outWord, s32 outBits, s32 func, s32 funcArg) {
    extern s32 SzModel_DrawWithFunc_Pipe();
    extern s32 ExClampMode_Pipe();
    Info_001EFDC0 info;
    s32 saved;
    s32 ret;

    saved = SzModel_GetCalcFlag(index);
    modelDrawCache = 0;
    packet = ExDitherMatrixEz_Pipe(packet, 2);
    packet = RhBase_SetZBufferMode(packet, 1);
    SzModel_SetCalcFlag(index, 0);
    if (func != 0 || funcArg != 0) {
        packet = SzModel_DrawWithFunc_Pipe(packet, index, 0, 0, 0, (s32)info.data, 0, func, funcArg);
    } else {
        packet = SzModel_Draw_Pipe(packet, index, 0, 0, 0, (s32)info.data, 0);
    }
    SzModel_SetCalcFlag(index, saved);
    ret = ExClampMode_Pipe(ExDitherMatrixEz_Pipe(RhBase_SetZBufferMode(packet, 0), 3), ExGetRegVal(0, 4));
    info.bits.flag = info.bits.kind = size;
    *(Word_001EFDC0 *)outWord = info.word;
    *(Bits_001EFDC0 *)outBits = info.bits;
    return ret;
}

typedef struct Flags_001EFF70 {
    s64 loaded : 1;
    s64 unused1 : 2;
    s64 pending : 1;
    s64 rest : 60;
} Flags_001EFF70;

/* Starts loading model file `path` into model slot `index`. */
s32 lSzModel_LoadModel(s32 index, void *path) {
    extern void lSzModel_FreeModel(s32);
    extern void lSzModel_LoadModelCB();
    extern s32 SzFile_ReadRequest();
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    if (((Flags_001EFF70 *)&obj->lv[0x2C])->pending) {
        return 0;
    }
    lSzModel_FreeModel(index);
    ((Flags_001EFF70 *)&obj->lv[0x2C])->loaded = 1;
    if (SzFile_ReadRequest(index, path, 0, -1, lSzModel_LoadModelCB, index) != 0) {
        ((Flags_001EFF70 *)&obj->lv[0x2C])->pending = 1;
    }
    return 1;
}

typedef struct {
    u8 pad000[0x20C];
    s8 bit0 : 1;
    s8 : 2;
    s8 bit3 : 1;
} Obj_001F0060;

/* Starts loading part of packed model file `path` into model slot `index`. */
s32 lSzModel_LoadModelPack(s32 index, void *path, s32 address, s32 size, s32 offset, s32 readSize) {
    extern void lSzModel_FreeModel(s32);
    extern s32 lSzModel_LoadModelPackCB();
    extern s32 SzFile_ReadRequestParam();
    Obj_001F0060 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = (Obj_001F0060 *)modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    if (obj->bit3) {
        return 0;
    }
    lSzModel_FreeModel(index);
    obj->bit0 = (address != 0) ? 0 : 1;
    if (SzFile_ReadRequestParam(index, 0, (s32)path, address, size, offset, readSize, (s32)lSzModel_LoadModelPackCB, index) != 0) {
        obj->bit3 = 1;
    }
    return 1;
}

typedef struct Fields_001F01A0 {
    u8 pad000[0x138];
    s32 *header;
    s32 *data;
    u8 pad140[0xB3];
    s8 kind;
    s16 value;
    u8 pad1F6[0x16];
    s8 loaded : 1;
    s8 unused1 : 2;
    s8 busy : 1;
    s8 unused4 : 4;
} Fields_001F01A0;

typedef struct Request_001F01A0 {
    u8 pad00[0x14];
    s32 *header;
    u8 pad18[4];
    s32 index;
} Request_001F01A0;

/* A model file has loaded (`ok`): binds it, then loads its textures, effect textures and motions. */
void lSzModel_LoadModelCB(void *request, s32 ok) {
    extern void func_0019B648();
    extern void lSzModel_LoadCB(s32);
    extern s32 modelFolderNames[];
    extern u8 D_002CFA17[];
    extern u8 D_002CFB94[];
    s32 index;
    Fields_001F01A0 *obj;

    index = ((Request_001F01A0 *)request)->index;
    if (index < 0 || index >= 0x54) {
        return;
    }
    obj = (Fields_001F01A0 *)modelSlots[index];
    if (obj != NULL) {
        if (ok == 0) {
            obj->busy = 0;
            return;
        }
        lSzModel_Clean(index);
        obj->header = ((Request_001F01A0 *)request)->header;
        obj->data = obj->header + 4;
        obj->header[1] = 0;
        RhModel_BindAddress(obj->header);
        SzModel_LoadTextureFile(index);
        switch (obj->kind) {
        case 4:
        case 5:
        case 6: {
            u8 format[128];
            u8 path[128];
            s32 value;
            s32 base;
            s32 i;

            value = obj->value;
            base = modelFolderNames[obj->kind];
            func_0019B648(format, D_002CFB94, SzFile_GetEnv((s32)D_002CFA17), base, base);
            for (i = 0; i < 8; i++) {
                func_0019B648(path, format, value, value, i + 0x61);
                lSzModel_LoadMotion(index, i, (s32)path);
            }
            SzModel_LoadEffectTextureFile(index);
            break;
        }
        case 0:
        case 3:
        case 7: {
            u8 format[128];
            u8 path[128];
            s32 value;
            s32 base;

            value = obj->value;
            base = modelFolderNames[obj->kind];
            func_0019B648(format, D_002CFB94, SzFile_GetEnv((s32)D_002CFA17), base, base);
            func_0019B648(path, format, value, value, 0x61);
            lSzModel_LoadMotion(index, 0, (s32)path);
            break;
        }
        }
        SzFile_EntryGroup(index, (s32)lSzModel_LoadCB);
    }
}

typedef struct Fields_001F0390 {
    u8 pad000[0x1F3];
    s8 kind;
    s16 value;
    u8 pad1F6[0x16];
    s8 loaded : 1;
    s8 unused1 : 2;
    s8 busy : 1;
    s8 unused4 : 4;
} Fields_001F0390;

typedef struct Request_001F0390 {
    u8 pad00[0x14];
    s32 *header;
    u8 pad18[4];
    s32 index;
} Request_001F0390;

/* A packed model has loaded (`ok`): binds it, or falls back to the single model file. */
void lSzModel_LoadModelPackCB(s32 request, s32 ok) {
    extern void func_0019B648();
    extern void lSzModel_LoadModelCB();
    extern s32 SzFile_ReadRequest();
    extern s32 modelFolderNames[];
    extern u8 D_002CFA17[];
    extern u8 D_002CFA1D[];
    u8 format[128];
    u8 path[128];
    s32 index;
    Fields_001F0390 *obj;
    s32 base;

    index = ((Request_001F0390 *)request)->index;
    if (index < 0 || index >= 0x54) {
        return;
    }
    obj = (Fields_001F0390 *)modelSlots[index];
    if (obj != NULL) {
        if (ok != 0 && *((Request_001F0390 *)request)->header != 0x304852) {
            ok = 0;
        }
        if (ok == 0) {
            base = modelFolderNames[obj->kind];
            func_0019B648(format, D_002CFA1D, SzFile_GetEnv((s32)D_002CFA17), base, base);
            func_0019B648(path, format, obj->value, obj->value);
            obj->loaded = 1;
            request = SzFile_ReadRequest(index, path, 0, -1, lSzModel_LoadModelCB, index);
            obj->busy = (request != 0) ? 1 : 0;
        } else {
            lSzModel_Clean(index);
            lSzModel_BindModelByAddr(index, ((Request_001F0390 *)request)->header);
        }
    }
}

typedef struct {
    u32 header[2];
    u8 data[0x7FF8];
} FixedBlock_001F0500;

/* Binds the model data at `address` to model slot `index`: its node tree, textures and up to eight motions. */
s32 lSzModel_BindModelByAddr(s32 index, void *address) {
    Obj_0031ABB0 *obj;
    u8 *motionData;
    s32 motion;
    Obj_0031ABB0 *objMotion;
    Obj_0031ABB0 *cur;
    s32 i;
    u8 *temp_v1;

    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    *(u8 **)&obj->pad040[0xF8] = address;
    *(u8 **)((u8 *)obj + 0x13C) = *(u8 **)&obj->pad040[0xF8] + 0x10;
    RhModel_BindAddress(*(u8 **)&obj->pad040[0xF8]);
    SzModel_BindTextureFile(index);
    temp_v1 = *(u8 **)&obj->pad040[0xF8];
    motion = 0;
    objMotion = obj;
    motionData = temp_v1 + *(s32 *)(temp_v1 + 0xC);
    do {
        if (*(s32 *)(*(u8 **)&obj->pad040[0xF8] + 4) & (1 << motion)) {
            objMotion->slots[0] = (ObjSlot_0031ABB0 *)motionData;
            NjaReloc_Adjust_M3DMOT(objMotion->slots[0]);
            objMotion->vals[0] = objMotion->slots[0]->f14->f4;
            motionData += *(s32 *)(motionData + 4);
        } else {
            objMotion->vals[0] = 1;
            objMotion->slots[0] = NULL;
        }
        motion += 1;
        objMotion = (Obj_0031ABB0 *)((u8 *)objMotion + 4);
    } while (motion < 8);
    if (*(s32 *)(*(u8 **)&obj->pad040[0xF8] + 4) & 0x100) {
        *(u8 **)((u8 *)obj + 0x164) = motionData;
        motionData = ((FixedBlock_001F0500 *)motionData)->data + 0x7FF8;
    } else {
        *(u8 **)((u8 *)obj + 0x164) = NULL;
    }
    if (*(s32 *)(*(u8 **)&obj->pad040[0xF8] + 4) & 0x200) {
        RhText_BindAddress((s32) motionData);
        *(u8 **)((u8 *)obj + 0x140) = motionData;
        motionData += *(s32 *)(motionData + 8);
    } else {
        *(u8 **)((u8 *)obj + 0x140) = NULL;
    }
    if (*(s32 *)(*(u8 **)&obj->pad040[0xF8] + 4) & 0x400) {
        *(u8 **)((u8 *)obj + 0x168) = motionData;
        motionData = ((FixedBlock_001F0500 *)motionData)->data + 0x7FF8;
    } else {
        *(u8 **)((u8 *)obj + 0x168) = NULL;
    }
    i = 0;
    cur = obj;
    do {
        if (*(s32 *)(*(u8 **)&obj->pad040[0xF8] + 4) & (1 << (i + 0xB))) {
            RhText_BindAddress((s32) motionData);
            *(u8 **)((u8 *)cur + 0x144) = motionData;
            motionData += *(s32 *)(motionData + 8);
        } else {
            *(u8 **)((u8 *)cur + 0x144) = NULL;
        }
        i += 1;
        cur = (Obj_0031ABB0 *)((u8 *)cur + 4);
    } while (i < 8);
    if (*(s32 *)(*(u8 **)&obj->pad040[0xF8] + 4) & 0x80000) {
        s32 size = (*(s32 *)(motionData + 8) + 0xF) & ~0xF;
        *(u8 **)((u8 *)obj + 0x16C) = motionData;
        motionData += size;
    }
    if (*(s32 *)(*(u8 **)&obj->pad040[0xF8] + 4) & 0x100000) {
        s32 size = (*(s32 *)(motionData + 8) + 0xF) & ~0xF;
        *(u8 **)((u8 *)obj + 0x170) = motionData;
        motionData += size;
    }
    if (*(s32 *)(*(u8 **)&obj->pad040[0xF8] + 4) & 0x200000) {
        *(u8 **)((u8 *)obj + 0x174) = motionData;
    } else {
        *(u8 **)((u8 *)obj + 0x174) = NULL;
    }
    lSzModel_LoadCB(index);
    return 1;
}

/* Starts loading motion file `path` into motion slot `motion` (0..7) of model slot `index`. */
s32 lSzModel_LoadMotion(s32 index, s32 motion, s32 path) {
    extern void SzFile_ReadRequest();

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    if (motion < 0 || motion >= 8) {
        return 0;
    }
    if (modelSlots[index] == NULL) {
        return 0;
    }
    lSzModel_FreeMotion(index, motion);
    SzFile_ReadRequest(index, path, 0, -1, lSzModel_LoadMotionCB, (index << 8) | motion);
    return 1;
}

typedef struct {
    u8 pad00[0x14];
    ObjSlot_0031ABB0 *f14;
    u8 pad18[4];
    s32 f1C;
} Arg_001F0830;

/* A motion file has loaded (`ok`): relocates it and binds it to its model. */
void lSzModel_LoadMotionCB(void *request, s32 ok) {
    Arg_001F0830 *a = (Arg_001F0830 *)request;
    s32 v;
    s32 idx;
    s32 sub;
    Obj_0031ABB0 *base;

    v = a->f1C;
    idx = v >> 8;
    sub = v & 0xFF;
    if (idx < 0 || idx >= 0x54) {
        return;
    }
    base = modelSlots[idx];
    if (base != NULL && ok != 0) {
        base->slots[sub] = a->f14;
        NjaReloc_Adjust_M3DMOT(base->slots[sub]);
        base->vals[sub] = base->slots[sub]->f14->f4;
    }
}

typedef struct {
    s8 owns_data : 1;
    s8 reserved : 2;
    s8 busy : 1;
    s8 rest : 4;
} Flags_001F08D0;

/* Reads a word of a model record. */
static inline s32 read_001F08D0(void *obj, s32 offset) {
    return *(s32 *)((u8 *)obj + offset);
}

/* Clears a word of a model record. */
static inline void clear_001F08D0(void *obj, s32 offset) {
    *(s32 *)((u32)obj + offset) = 0;
}

/* Whether a model record is still loading. */
static inline s32 busy_001F08D0(void *obj) {
    return ((Flags_001F08D0 *)obj)[0x20C].busy;
}

/* Whether a model record owns its data. */
static inline s32 owns_001F08D0(void *obj) {
    return ((Flags_001F08D0 *)((u32)obj + 0x20C))->owns_data;
}
#pragma global_optimizer off

/* Frees model slot `index`'s model, motions, effects and camera requests. */
s32 lSzModel_FreeModel(s32 index) {
    u8 *data;
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    data = (u8 *)read_001F08D0(obj, 0x138);
    if (data == NULL) {
        return 1;
    }
    if (busy_001F08D0(obj)) {
        return 0;
    }

    if (*(s32 *)(data + 4) != 0) {
        s32 i;
        u8 *cursor;

        i = 0;
        cursor = (u8 *)obj;
        do {
            i++;
            *(s32 *)(cursor + 0x178) = 0;
            cursor += 4;
        } while (i < 8);
        clear_001F08D0(obj, 0x140);
        {
            u8 *clear_cursor;
            s32 j;

            j = 0;
            clear_cursor = (u8 *)obj;
            do {
                j++;
                *(s32 *)(clear_cursor + 0x144) = 0;
                clear_cursor += 4;
            } while (j < 8);
        }
    } else {
        s32 slot;
        u8 *metadata;
        s32 resource;

        metadata = (u8 *)read_001F08D0(obj, 0x13C);
        if (*(s32 *)(metadata + 0x2C) != 0) {
            s32 *table;
            s32 *resources;
            s32 count;
            s32 k;

            k = 0;
            table = (s32 *)(data + *(s32 *)(metadata + 0x28));
            count = table[0];
            resources = table + 4;
            if (0 < count) {
                do {
                    resource = resources[0];
                    if (resource != 0) {
                        SzMem_Free(resource);
                    }
                    resource = resources[2];
                    if (resource != 0) {
                        SzMem_Free(resource);
                    }
                    k++;
                    resources += 4;
                } while (k < count);
            }
        }
        slot = 0;
        do {
            lSzModel_FreeMotion(index, slot);
            slot++;
        } while (slot < 8);
        resource = read_001F08D0(obj, 0x140);
        if (resource != 0) {
            SzMem_Free(resource);
            clear_001F08D0(obj, 0x140);
        }
        {
            u8 *cursor;
            s32 l;

            l = 0;
            cursor = (u8 *)obj;
            do {
                resource = *(s32 *)(cursor + 0x144);
                if (resource != 0) {
                    SzMem_Free(resource);
                    *(s32 *)(cursor + 0x144) = 0;
                }
                l++;
                cursor += 4;
            } while (l < 8);
        }
    }

    clear_001F08D0(obj, 0x164);
    clear_001F08D0(obj, 0x168);
    SzView_FreeRequest(0, 1);
    if (*(s32 *)((u8 *)read_001F08D0(obj, 0x138) + 4) & 0x80000) {
        clear_001F08D0(obj, 0x16C);
    } else if (read_001F08D0(obj, 0x16C) != 0) {
        SzMem_Free(read_001F08D0(obj, 0x16C));
        clear_001F08D0(obj, 0x16C);
    }
    if (*(s32 *)((u8 *)read_001F08D0(obj, 0x138) + 4) & 0x100000) {
        clear_001F08D0(obj, 0x170);
    } else if (read_001F08D0(obj, 0x170) != 0) {
        SzMem_Free(read_001F08D0(obj, 0x170));
        clear_001F08D0(obj, 0x170);
    }
    if (*(s32 *)((u8 *)read_001F08D0(obj, 0x138) + 4) & 0x200000) {
        clear_001F08D0(obj, 0x174);
    } else if (read_001F08D0(obj, 0x174) != 0) {
        SzMem_Free(read_001F08D0(obj, 0x174));
        clear_001F08D0(obj, 0x174);
    }
    if (read_001F08D0(obj, 0x1EC) >= 0) {
        SzEffect_Destroy(read_001F08D0(obj, 0x1EC));
    }
    if (owns_001F08D0(obj)) {
        SzMem_Free((s32)(u8 *)read_001F08D0(obj, 0x138));
    }
    {
        s32 n;
        Entry_001EDF20 *entry;

        n = 1;
        entry = D_0031AD70;
        clear_001F08D0(obj, 0x138);
        do {
            if (entry->id >= 0 && (index < 0 || entry->id == index)) {
                entry->id = -1;
            }
            n++;
            entry++;
        } while (n < 0x20);
    }
    return 1;
}
#pragma global_optimizer reset

/* Frees motion slot `motion` (0..7) of model slot `index`. */
s32 lSzModel_FreeMotion(s32 index, s32 motion) {
    void SzMem_Free(void *);
    Obj_0031ABB0 *obj;
    ObjSlot_0031ABB0 *slot;

    if ((index < 0) || (index >= 0x54)) {
        return 0;
    }
    if ((motion < 0) || (motion >= 8)) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    slot = obj->slots[motion];
    if (slot == NULL) {
        return 1;
    }
    SzMem_Free(slot);
    obj->slots[motion] = NULL;
    obj->vals[motion] = 1;
    return 1;
}

/* Starts side `side`'s battle motion (`start`) with its camera (`close` for the close one) and effects. */
s32 SzModel_BattleSeq(s32 side, s32 start, s32 close) {
    Obj_0031ABB0 *obj;
    s32 s1;
    s32 s2;
    s32 index;
    s32 i;
    Obj_0031ABB0 *ptr;
    extern s32 SzEffect_EntryCallback();

    s1 = SzBattle_InqEntry(side);
    s2 = SzBattle_InqEntry(side ^ 1);
    index = SzDuel_GetUnitModelID(s1 >> 8, s1 & 0xFF);
    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    SzModel_SetAnimIntr(index, 2);
    SzText_FreeRequest(5, -1);
    SzEffect_ClearRefID2(s1, 1);
    SzEffect_ClearRefID2(s2, 1);
    i = 0;
    ptr = obj;
    do {
        SzText_AddFile(5, i, NULL, *(s32 *)((u8 *)ptr + 0x144));
        i += 1;
        ptr = (Obj_0031ABB0 *)((u8 *)ptr + 4);
    } while (i < 8);
    *(s32 *)((u8 *)obj + 0x1EC) = SzEffect_EntryCallback(1, *(u16 *)((u8 *)obj + 0x206), *(u16 *)((u8 *)obj + 0x208), s2, s1, lSzModel_EffectCB, index);
    if (start != 0) {
        if (*(s32 *)((u8 *)obj + 0x16C) != 0) {
            SzView_ReqCamera(0, 1, ((close != 0) ? 1 : 0) + 8, *(u16 *)((u8 *)obj + 0x202), index, (void *)*(s32 *)((u8 *)obj + 0x16C));
        }
    }
    return 1;
}

/* Starts side `side`'s second battle motion with its camera. */
s32 SzModel_BattleSeq2(s32 side, s32 start, s32 close) {
    s32 index;
    Obj_0031ABB0 *obj;
    void *data;

    index = SzBattle_InqEntry(side);
    SzBattle_InqEntry(side ^ 1);
    index = SzDuel_GetUnitModelID(index >> 8, index & 0xFF);
    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    SzModel_SetAnimIntr(index, 5);
    if (start != 0) {
        data = *(void **)((u8 *)obj + 0x170);
        if (data != NULL) {
            SzView_ReqCamera(0, 1, (close != 0 ? 1 : 0) + 8, 0, index, data);
        }
    }
    return 1;
}

/* Model slot `index`'s bounding radius. */
f32 SzModel_GetRadius(s32 index) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return -1.0f;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return -1.0f;
    }
    return *(f32 *)((u8 *)obj + 0x1E4);
}

/* Model slot `index`'s second effect texture. */
u8 *SzModel_GetEffTextureB(s32 index) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return NULL;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return NULL;
    }
    return &obj->pad040[0x104];
}

/* Model slot `index`'s monster overlay (its module), or 0. */
s32 SzModel_GetOverlayM(s32 index) {
    Obj_0031ABB0 *obj;
    void *data;
    s32 ret;

    if (index < 0 || index >= 0x54) {
        ret = 0;
    } else {
        obj = modelSlots[index];
        if (obj == NULL) {
            ret = 0;
        } else {
            data = *(void **)((u8 *)obj + 0x138);
            if (data == NULL) {
                ret = 0;
            } else if (!(*(s32 *)((u8 *)data + 4) & 0x100)) {
                ret = 0;
            } else {
                ret = *(s32 *)((u8 *)obj + 0x164);
            }
        }
    }
    return ret;
}

/* Loads model slot `index`'s battle overlay module. Returns 1 if it started. */
s32 SzModel_LoadOverlayB(s32 index) {
    Obj_0031ABB0 *obj;
    s8 kind;
    void *data;

    if ((index < 0) || (index >= 0x54)) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    data = *(void **)((u8 *)obj + 0x138);
    if (data == NULL) {
        return 0;
    }
    kind = *(s8 *)((u8 *)obj + 0x1F3);
    if ((kind != 4) && (kind != 5) && (kind != 6)) {
        return 1;
    }
    *(s32 *)((u8 *)data + 4) &= ~0x400;
    return (SzEffect_LoadModule(1, *(s16 *)((u8 *)obj + 0x1F4), 0, data) != 0) ? 1 : 0;
}

/* Model slot `index`'s battle overlay (its module), or 0. */
s32 SzModel_GetOverlayB(s32 index) {
    Obj_0031ABB0 *obj;
    void *state;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    state = *(void **)((u8 *)obj + 0x138);
    if (state == NULL) {
        return 0;
    }
    if ((*(s32 *)((u8 *)state + 4) & 0x400) == 0) {
        return 0;
    }
    return *(s32 *)((u8 *)obj + 0x168);
}

/* Camera `which` (0 or 1) of model slot `index`, or 0. */
s32 SzModel_GetCamera(s32 index, s32 which) {
    s32 ret = 0;
    Obj_0031ABB0 *obj;

    if ((index < 0) || (index >= 0x54)) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return ret;
    }
    if (*(s32 *)((u8 *)obj + 0x138) == 0) {
        return ret;
    }
    switch (which) {
    case 19:
        ret = *(s32 *)((u8 *)obj + 0x16C);
        break;
    case 20:
        ret = *(s32 *)((u8 *)obj + 0x170);
        break;
    }
    return ret;
}

typedef struct {
    s8 : 2;
    s8 active : 1;
} Flags_001F1240;

/* Whether model slot `index` has a model bound. */
s32 SzModel_IsModelReady(s32 index) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    return ((Flags_001F1240 *)((u8 *)obj + 0x20C))->active ? 1 : 0;
}

typedef struct {
    s8 : 3;
    s8 active : 1;
} Flags_001F12A0;

/* Whether model slot `index` is still loading. */
s32 SzModel_IsModelLoading(s32 index) {
    Obj_0031ABB0 *obj;
    s32 ret;

    if (index < 0 || index >= 0x54) {
        ret = 0;
    } else {
        obj = modelSlots[index];
        if (obj == NULL) {
            ret = 0;
        } else {
            ret = ((Flags_001F12A0 *)((u8 *)obj + 0x20C))->active ? 1 : 0;
        }
    }
    return ret;
}

/* Whether model slot `index` has a model booked (SzModel_Preset) and ready. */
s32 SzModel_IsModelStandby(s32 index) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }

    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    if (*(s8 *)((u8 *)obj + 0x1F2) >= 0) {
        return 1;
    }
    return 0;
}

typedef struct {
    s8 unused : 1;
    s8 enabled : 1;
} Flags_001F1370;

/* Whether model slot `index` is shown. */
s32 SzModel_IsModelDisp(s32 index) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    if (*(s8 *)((u8 *)obj + 0x1F2) < 0) {
        return 0;
    }
    return ((Flags_001F1370 *)((u8 *)obj + 0x20C))->enabled ? 1 : 0;
}

/* Model slot `index`'s current animation. */
s8 SzModel_GetAnim(s32 index) {
    return SzModel_GetAnimParam(index, 0);
}

/* Animation parameter `which` (0..3) of model slot `index`. */
s8 SzModel_GetAnimParam(s32 index, s32 which) {
    Obj_0031ABB0 *base;

    if (index < 0 || index >= 0x54) {
        return -1;
    }
    if (which < 0 || which >= 4) {
        return -1;
    }
    base = modelSlots[index];
    if (base == NULL) {
        return -1;
    }
    return base->lv[which];
}

/* Starts animation `anim` on model slot `index`. */
s32 SzModel_SetAnim(s32 index, s32 anim) {
    return SzModel_SetAnimParam(index, anim, 3);
}

/* Sets animation parameter `which` (0..3) of model slot `index` to animation `anim`, if the model has it. */
s32 SzModel_SetAnimParam(s32 index, s32 anim, s32 which) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    if (which < 0 || which >= 4) {
        return 0;
    }
    if (anim < 0 || anim >= 8) {
        return 0;
    }

    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    if (obj->slots[anim] == NULL) {
        return 0;
    }

    obj->lv[which] = anim;
    return 1;
}

/* Blends model slot `index` into animation `anim` (over 6 frames). */
s32 SzModel_SetAnimIntr(s32 index, s32 anim) {
    return SzModel_SetAnimIntrParam(index, anim, 6);
}

typedef struct {
    f32 x, y, z;
} Vec3_001F1560;

typedef struct {
    s8 unused : 6;
    s8 direction : 2;
} Flags_001F1560;

/* Blends model slot `index` into animation `anim` over `frames` frames. */
s32 SzModel_SetAnimIntrParam(s32 index, s32 anim, s32 frames) {
    Obj_0031ABB0 *obj;
    Vec3_001F1560 *current;
    Vec3_001F1560 *previous;
    s8 *current_slot;
    s8 *previous_slot;
    f32 last_frame;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    if (anim < 0 || anim >= 8) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    current = (Vec3_001F1560 *)&obj->slots[8];
    previous = (Vec3_001F1560 *)&obj->slots[11];
    current_slot = &obj->lv[0];
    previous_slot = &obj->lv[1];
    if (obj->slots[anim] != NULL) {
        last_frame = (f32)(u32)obj->vals[anim] - 1.0f;
        *previous = *current;
        *previous_slot = *current_slot;
        *current_slot = anim;
        if ((s64)((Flags_001F1560 *)((u8 *)obj + 0x1F7))->direction == -1) {
            current->y = last_frame;
        } else {
            current->y = 1.0f;
        }
        current->z = 0.0f;
        previous->z = 1.0f - current->z;
        *(s8 *)((u8 *)obj + 0x1FB) = frames;
        *(s8 *)((u8 *)obj + 0x1FD) = 0;
    } else {
        return 0;
    }
    return 1;
}

/* Blends model slot `index` back out (over 6 frames). */
s32 SzModel_SetAnimIntrReverse(s32 index) {
    return SzModel_SetAnimIntrReverseParam(index, 6);
}

typedef struct {
    f32 x, y, z;
} Vec3_001F16C0;

/* Blends model slot `index` back out over `frames` frames. */
s32 SzModel_SetAnimIntrReverseParam(s32 index, s32 frames) {
    s8 oldLevel;
    s32 scaled;
    u8 * bytes;
    Vec3_001F16C0 temp;
    Obj_0031ABB0 * obj;
    Vec3_001F16C0 * first;
    Vec3_001F16C0 * second;
    s8 * firstLevel;
    s8 * secondLevel;
    if ((index < 0) || (index >= 0x54)) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    bytes = (u8 *)obj;
    first = (Vec3_001F16C0 *)&obj->slots[8];
    second = (Vec3_001F16C0 *)&obj->slots[11];
    firstLevel = &obj->lv[0];
    secondLevel = &obj->lv[1];
    if (*firstLevel >= 0 && (oldLevel = *secondLevel) >= 0) {
        temp = *second;
        *second = *first;
        *first = temp;
        *secondLevel = *firstLevel;
        *firstLevel = oldLevel;
        bytes[0x1FC] = (f32)(bytes[0x1FC] * frames) / (f32)(u32)bytes[0x1FB];
        bytes[0x1FB] = frames;
        bytes[0x1FC] = bytes[0x1FB] - bytes[0x1FC];
        bytes[0x1FD] = 0;
    } else {
        return 0;
    }
    return 1;
}

typedef struct {
    u8 unused : 6;
    s8 mode : 2;
} Flags_001F1830;

/* Switches model slot `index` to animation `anim` at once. */
s32 SzModel_SetAnimDirect(s32 index, s32 anim) {
    Obj_0031ABB0 *obj;
    f32 *state;
    s8 *next;
    s8 *selected;
    f32 value;
    f32 start;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    if (anim < 0 || anim >= 8) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    state = (f32 *)&obj->slots[8];
    next = &obj->lv[1];
    selected = &obj->lv[0];
    if (obj->slots[anim] != NULL) {
        value = (f32)(u32)obj->vals[anim];
        start = value - 1.0f;
        *next = -1;
        *selected = anim;
        if (((Flags_001F1830 *)((u8 *)obj + 0x1F7))->mode == -1) {
            state[1] = start;
        } else {
            state[1] = 1.0f;
        }
        state[2] = 1.0f;
        *(s8 *)((u8 *)obj + 0x1FD) = 0;
    } else {
        return 0;
    }
    return 1;
}

/* Sets model slot `index`'s motion delay in frames. */
s32 SzModel_SetMotionDelay(s32 index, s8 delay) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    *(s8 *)((u8 *)obj + 0x1FD) = delay;
    return 1;
}

typedef struct {
    s8 unused : 6;
    s8 value : 2;
} Flags_001F19A0;

/* Model slot `index`'s animation direction. */
s64 SzModel_GetAnimDir(s32 index) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return -1;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return -1;
    }
    return ((Flags_001F19A0 *)((u8 *)obj + 0x1F7))->value;
}

typedef struct {
    s8 low : 6;
    s8 mode : 2;
} Flags_001F1A00;

/* Sets model slot `index`'s animation direction (forwards, backwards, loop...). */
s32 SzModel_SetAnimDir(s32 index, s64 dir) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    } else {
        obj = modelSlots[index];
        if (obj == NULL) {
            return 0;
        }
        ((Flags_001F1A00 *)((u8 *)obj + 0x1F7))->mode = (s8)dir;
        return 1;
    }
}

/* Sets model slot `index`'s animation speed (for its current animation parameter). */
s32 SzModel_SetAnimSpeed(s32 index, f32 value) {
    return SzModel_SetAnimSpeedParam(index, 0, value);
}

typedef struct View_001F1A90 {
    u8 pad[0x198];
    f32 m[4][3];
} View_001F1A90;

/* Sets the speed of animation parameter `which` of model slot `index`. */
s32 SzModel_SetAnimSpeedParam(s32 index, s32 which, f32 value) {
    Obj_0031ABB0 *obj;
    View_001F1A90 *view;
    s32 slot;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    if (which < 0 || which >= 4) {
        return 0;
    }
    obj = modelSlots[index];
    view = (View_001F1A90 *)obj;
    if (obj == NULL) {
        return 0;
    }
    slot = obj->lv[which];
    if (slot < 0) {
        return 0;
    }
    if (obj->slots[slot] == NULL) {
        return 0;
    }
    view->m[which][0] = value;
    return 1;
}

/* Model slot `index`'s current animation frame. */
f32 SzModel_GetAnimFrame(s32 index) {
    return SzModel_GetAnimFrameParam(index, 0);
}

typedef struct View_001F1B60 {
    u8 pad[0x19C];
    f32 m[4][3];
} View_001F1B60;

/* The current frame of animation parameter `which` of model slot `index`. */
f32 SzModel_GetAnimFrameParam(s32 index, s32 which) {
    Obj_0031ABB0 *obj;
    View_001F1B60 *view;
    s8 slot;

    if (index < 0 || index >= 0x54) {
        return -1.0f;
    }
    if (which < 0 || which >= 4) {
        return -1.0f;
    }
    obj = modelSlots[index];
    view = (View_001F1B60 *)obj;
    if (obj == NULL) {
        return -1.0f;
    }
    slot = obj->lv[which];
    if (slot < 0) {
        return -1.0f;
    }
    if (obj->slots[slot] == NULL) {
        return -1.0f;
    }
    return view->m[which][0];
}

/* Sets model slot `index`'s current animation frame. */
void SzModel_SetAnimFrame(s32 index, f32 value) {
    SzModel_SetAnimFrameParam(index, 0, value);
}

typedef struct View_001F1C50 {
    u8 pad[0x19C];
    f32 m[4][3];
} View_001F1C50;

/* Sets the current frame of animation parameter `which` of model slot `index`. */
s32 SzModel_SetAnimFrameParam(s32 index, s32 which, f32 value) {
    s32 slot;
    f32 maximum;
    Obj_0031ABB0 *obj;
    View_001F1C50 *view;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    view = (View_001F1C50 *)obj;
    if (obj == NULL) {
        return 0;
    }
    slot = obj->lv[which];
    if (slot < 0) {
        return 0;
    }
    if (obj->slots[slot] == NULL) {
        return 0;
    }
    maximum = (f32) (u32) obj->vals[slot] - 1.0f;
    if (value < 1.0f) {
        value = 1.0f;
    }
    if (!(value <= maximum)) {
        value = maximum;
    }
    view->m[which][0] = value;
    return 1;
}

/* How many frames animation `anim` of model slot `index` has (-1: the current one). */
s32 SzModel_GetAnimFrameMax(s32 index, s32 anim) {
    extern s32 SzModel_GetAnimParam();
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return -1;
    }
    if (anim < 0) {
        anim = SzModel_GetAnimParam(index, 0);
    }
    if (anim < 0 || anim >= 8) {
        return -1;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return -1;
    }
    if (obj->slots[anim] == NULL) {
        return -1;
    }
    return obj->vals[anim] - 1;
}

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Vec3_001F1E10;

/* Model slot `index`'s light intensity (four values) into `out`. */
s32 SzModel_GetIntensity(s32 index, f32 *out) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    *(Vec3_001F1E10 *)out = *(Vec3_001F1E10 *)((u8 *)obj + 0x120);
    return 1;
}

/* Model slot `index`'s overall intensity into `out`. */
s32 SzModel_GetIntensityOnly(s32 index, f32 *out) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    *out = *(f32 *)((u8 *)obj + 0x128);
    return 1;
}

typedef struct {
    f32 x, y, z;
} Vec3_001F1EE0;

/* Sets model slot `index`'s light intensity (four values). */
s32 SzModel_SetIntensity(s32 index, f32 *values) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    if (values != NULL) {
        *(Vec3_001F1EE0 *) ((u8 *) obj + 0x120) = *(Vec3_001F1EE0 *) values;
    } else {
        ((Vec3_001F1EE0 *) ((u8 *) obj + 0x120))->x = 0.8f;
        ((Vec3_001F1EE0 *) ((u8 *) obj + 0x120))->y = 0.8f;
        ((Vec3_001F1EE0 *) ((u8 *) obj + 0x120))->z = 1.0f;
    }
    return 1;
}

/* Sets model slot `index`'s overall intensity. */
s32 SzModel_SetIntensityOnly(s32 index, f32 fparg0) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    *(f32 *)((u8 *)obj + 0x128) = fparg0;
    return 1;
}

/* Model slot `index`'s position into `out`. */
s32 SzModel_GetPos(s32 index, void *out) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    if (out != NULL) {
        *(Vec4f *)out = *(Vec4f *)obj;
    }
    return 1;
}

typedef struct {
    s8 unused0 : 5;
    s8 ready : 1;
    s8 unused1 : 2;
} Flags_001F2050;

/* Whether model slot `index` has a model bound. */
static inline s32 check_001F2050(s32 index) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    if (*(s8 *)((u8 *)obj + 0x1F2) >= 0) {
        return 1;
    }
    return 0;
}

/* Model slot `index`'s centre in the world into `out`. */
s32 SzModel_GetCenter(s32 index, void *out) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    if (check_001F2050(index) == 0) {
        return 0;
    }
    if ((s32)*(u8 *)((u8 *)obj + 0x1FE) <= 0) {
        return 0;
    }
    if (((Flags_001F2050 *)((u8 *)obj + 0x20C))->ready == 0) {
        return 0;
    }
    if (out != NULL) {
        *(Vec4f *)out = *(Vec4f *)((u8 *)obj + 0x80);
    }
    return 1;
}

/* Whether model slot `index` has a model bound. */
static inline s32 ready_001F2150(s32 index) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    if (*(s8 *)((u8 *)obj + 0x1F2) >= 0) {
        return 1;
    }
    return 0;
}

/* Model slot `index`'s centre offset (from its centre node) into `out`. */
s32 SzModel_GetCenterOfs(s32 index, f32 *out) {
    s32 sp3C;
    Obj_0031ABB0 *obj;
    f32 temp_f1;
    s32 temp_a1;
    s32 temp_a1_2;
    s32 traceGNode;

    if ((index < 0) || (temp_a1 = index < 0x54, (temp_a1 == 0))) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    if (ready_001F2150(index) == 0) {
        return 0;
    }
    if ((s32)*(u8 *)((u8 *)obj + 0x1FE) <= 0) {
        return 0;
    }
    sp3C = 0;
    if ((index < 0) || (index >= 0x54)) {
        traceGNode = 0;
    } else if (obj == NULL) {
        traceGNode = 0;
    } else {
        temp_a1_2 = *(s32 *)((u8 *)obj + 0x134);
        traceGNode = lSzModel_TraceGNode(1, temp_a1_2, temp_a1_2, &sp3C, 0, NULL, 0);
    }
    if (traceGNode != 0) {
        temp_f1 = *(f32 *)(*(u8 **)((u8 *)obj + 0x13C) + 0x54);
        out[0] = *(f32 *)((u8 *)traceGNode + 0x20) / temp_f1;
        out[1] = *(f32 *)((u8 *)traceGNode + 0x24) / temp_f1;
        out[2] = *(f32 *)((u8 *)traceGNode + 0x28) / temp_f1;
        out[3] = 1.0f;
    }
    return 1;
}

/* Sets model slot `index`'s position. */
s32 SzModel_SetPos(s32 index, void *src) {
    Obj_0031ABB0 *dst;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    dst = modelSlots[index];
    if (dst == NULL) {
        return 0;
    }
    if (src != NULL) {
        *(Vec4f *)dst = *(Vec4f *)src;
    }
    return 1;
}

/* Model slot `index`'s rotation into `out`. */
s32 SzModel_GetRot(s32 index, void *out) {
    s32 result;
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        result = 0;
    } else {
        obj = modelSlots[index];
        if (obj == NULL) {
            result = 0;
        } else {
            if (out != NULL) {
                *(Vec4f *)out = *(Vec4f *)((u8 *)obj + 0x10);
            }
            result = 1;
        }
    }
    return result;
}

/* Model slot `index`'s rotation centre into `out`. */
s32 SzModel_GetRotC(s32 index, void *out) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    if (out != NULL) {
        *(Vec4f *)out = *(Vec4f *)((u8 *)obj + 0x20);
    }
    return 1;
}

typedef struct {
    f32 x, y, z, w;
} Vec4_001F2430;

/* needs shared field: modelSlots +0x10 f32[4] */

/* Sets model slot `index`'s rotation. */
s32 SzModel_SetRot(s32 index, void *src) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    if (src != NULL) {
        *(Vec4_001F2430 *)((u8 *)obj + 0x10) = *(Vec4_001F2430 *)src;
    } else {
        *(f32 *)((u8 *)obj + 0x10) = 0.0f;
        *(f32 *)((u8 *)obj + 0x14) = 0.0f;
        *(f32 *)((u8 *)obj + 0x18) = 0.0f;
        *(f32 *)((u8 *)obj + 0x1C) = 0.0f;
    }
    return 1;
}

/* Sets model slot `index`'s rotation centre. */
s32 SzModel_SetRotC(s32 index, void *src) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    if (src != NULL) {
        *(Vec4f *)((u8 *)obj + 0x20) = *(Vec4f *)src;
    } else {
        ((Vec4f *)((u8 *)obj + 0x20))->x = 0.0f;
        ((Vec4f *)((u8 *)obj + 0x20))->y = 0.0f;
        ((Vec4f *)((u8 *)obj + 0x20))->z = 0.0f;
        ((Vec4f *)((u8 *)obj + 0x20))->w = 0.0f;
    }
    return 1;
}

/* Model slot `index`'s scale into `out`. */
s32 SzModel_GetScale(s32 index, void *out) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    if (out != NULL) {
        *(Vec4f *)out = obj->v;
    }
    return 1;
}

/* Sets model slot `idx`'s scale. */
s32 SzModel_SetScale(s32 idx, void *src) {
    Obj_0031ABB0 *obj;

    if (idx < 0 || idx >= 0x54) {
        return 0;
    }
    obj = modelSlots[idx];
    if (obj == NULL) {
        return 0;
    }
    if (src != NULL) {
        obj->v = *(Vec4f *)src;
    } else {
        obj->v.x = 1.0f;
        obj->v.y = 1.0f;
        obj->v.z = 1.0f;
        obj->v.w = 1.0f;
    }
    return 1;
}

typedef struct {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} Color_001F2660;

/* Model slot `index`'s colour into `out`. */
s32 SzModel_GetRgba(s32 index, void *out) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return -1;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return -1;
    }
    if (out != NULL) {
        *(Color_001F2660 *)out = *(Color_001F2660 *)&obj->pad040[0xEC];
    }
    return *(u8 *)((u8 *)obj + 0x1F8) & 3;
}

typedef struct {
    u8 mode : 2;
    u8 reserved : 6;
} Flags_001F26E0;

typedef struct {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} Color_001F26E0;

/* Sets model slot `index`'s colour (`mode` says how it mixes). */
s32 SzModel_SetRgba(s32 index, s32 mixMode, void *rgba) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    if (mixMode >= 0 && mixMode < 4) {
        ((Flags_001F26E0 *)((u8 *)obj + 0x1F8))->mode = mixMode;
    }
    if (rgba != NULL) {
        *(Color_001F26E0 *)&obj->pad040[0xEC] = *(Color_001F26E0 *)rgba;
    } else {
        obj->pad040[0xEC] = obj->pad040[0xED] = obj->pad040[0xEE] = 0x80;
        obj->pad040[0xEF] = 0x80;
    }
    return 1;
}

/* Model slot `index`'s alpha. */
s32 SzModel_GetAlpha(s32 index) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return -1;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return -1;
    }
    return obj->pad040[0xEF];
}

/* Sets model slot `index`'s alpha. */
s32 SzModel_SetAlpha(s32 index, u8 value) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    obj->pad040[0xEF] = value;
    return 1;
}

typedef struct {
    u8 low : 2;
    u8 mode : 2;
    u8 high : 4;
} Flags_001F2860;

typedef struct {
    u8 r, g, b, a;
} Color_001F2860;

/* Sets model slot `index`'s colour filter (`mode` and its colour). */
s32 SzModel_SetFilter(s32 index, s32 filterMode, void *color) {
    Obj_0031ABB0 *obj;

    if ((index < 0) || (index >= 0x54)) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    if ((filterMode >= 0) && (filterMode < 4)) {
        ((Flags_001F2860 *)((u8 *)obj + 0x1F8))->mode = filterMode;
    }
    if (color != NULL) {
        *(Color_001F2860 *)&obj->pad040[0xF0] = *(Color_001F2860 *)color;
    } else {
        obj->pad040[0xF0] = obj->pad040[0xF1] = obj->pad040[0xF2] = 0;
        obj->pad040[0xF3] = 0;
    }
    return 1;
}

/* The model number loaded in slot `index`. */
s16 SzModel_GetModelNo(s32 index) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return -1;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return -1;
    }
    return *(s16 *)((u8 *)obj + 0x1F4);
}

/* The kind of model loaded in slot `index`. */
s8 SzModel_GetModelType(s32 index) {
    Obj_0031ABB0 *obj;
    s8 ret;

    if (index < 0 || index >= 0x54) {
        ret = -1;
    } else {
        obj = modelSlots[index];
        if (obj == NULL) {
            ret = -1;
        } else {
            ret = *(s8 *)((u8 *)obj + 0x1F3);
        }
    }
    return ret;
}

typedef struct {
    u8 pad000[0x20C];
    s8 unused0 : 4;
    s8 enabled : 1;
    s8 unused1 : 3;
} ObjView_001F29E0;

/* Sets model slot `index`'s deform effect. */
s32 SzModel_SetDeform(s32 index, s32 value) {
    ObjView_001F29E0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = (ObjView_001F29E0 *) modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    if (obj->enabled != value) {
        obj->enabled = (s8) value;
    }
    return 1;
}

typedef struct {
    s8 : 4;
    s8 active : 1;
    s8 : 3;
} Flags_001F2A70;

/* Model slot `index`'s deform effect. */
s32 SzModel_GetDeform(s32 index) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    return ((Flags_001F2A70 *) ((u8 *) obj + 0x20C))->active ? 1 : 0;
}

/* Sets how strong model slot `index`'s deform effect is. */
s32 SzModel_SetDeformRatio(s32 index, s8 value) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }

    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }

    *(s8 *)((u8 *)obj + 0x1FF) = value;
    return 1;
}

/* Whether model slot `index` has a model bound. */
static inline s32 check_001F2B30(s32 index) {
    if (index < 0 || index >= 0x54) {
        return 0;
    }
    if (modelSlots[index] == NULL) {
        return 0;
    }
    if (*(s8 *)((u8 *)modelSlots[index] + 0x1F2) >= 0) {
        return 1;
    }
    return 0;
}

/* How many references model slot `index` has. */
s32 SzModel_GetRefNum(s32 index) {
    if (index < 0 || index >= 0x54) {
        return -1;
    }
    if (modelSlots[index] == NULL) {
        return -1;
    }
    if (check_001F2B30(index)) {
        return *(u8 *)((u8 *)modelSlots[index] + 0x1FE);
    }
    return -1;
}

/* Whether model slot `index` holds reference `id`. */
s32 SzModel_InqRefID(s32 index, s32 id) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return -1;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return -1;
    }
    if (id < 0 || id >= 8) {
        return -1;
    }
    return *(u16 *)((id << 1) + (s32)obj + 0x1B0);
}

typedef struct View_001F2C60 {
    u8 pad0[0x1B0];
    u16 slots[8];
    u8 pad1C0[0x39];
    u8 count;
    u8 pad1FA[4];
    u8 max;
} View_001F2C60;

/* Sets reference `ref` of model slot `index` to `id`. */
s32 SzModel_SetRefID(s32 index, s32 ref, s32 id) {
    View_001F2C60 *obj;
    s32 i;
    s32 group;
    s32 newGroup;
    u16 current;

    if (index < 0 || index >= 0x54) {
        return -1;
    }
    obj = (View_001F2C60 *) modelSlots[index];
    if (obj == NULL) {
        return -1;
    }
    if (id != 0) {
        if (ref >= 0) {
            group = (ref & 0x7F00) >> 8;
            for (i = 0; i < 8; i++) {
                if (((obj->slots[i] & 0x7F00) >> 8) == group) {
                    obj->slots[i] = 0x7FFF;
                }
            }
        } else {
            for (i = 0; i < 8; i++) {
                obj->slots[i] = 0x7FFF;
            }
        }
        obj->count = 0;
    }
    if (obj->count >= 8) {
        return -1;
    }
    if (ref >= 0) {
        newGroup = (ref & 0x7F00) >> 8;
        if ((ref & 0xFF) >= obj->max) {
            return -1;
        }
        current = obj->slots[obj->count];
        if ((current & 0x7FFF) < 0x7FFF && ((current & 0x7F00) >> 8) != newGroup) {
            return -1;
        }
    }
    obj->slots[obj->count] = (ref < 0) ? 0x7FFF : ref;
    return obj->count++;
}

/* Sets the reference numbered `refNo` of model slot `index` to `id`. */
s32 SzModel_SetRefID_RefNo(s32 index, s32 refNo, s32 id) {
    Obj_0031ABB0 *obj;
    s32 group;
    u16 current;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    if (id < 0 || id >= 8) {
        return 0;
    }
    if (refNo >= 0) {
        group = (refNo & 0x7F00) >> 8;
        if ((refNo & 0xFF) >= *(u8 *)((u8 *)obj + 0x1FE)) {
            return 0;
        }
        current = *(u16 *)((id << 1) + (s32)obj + 0x1B0);
        if ((current & 0x7FFF) < 0x7FFF && ((current & 0x7F00) >> 8) != group) {
            return 0;
        }
    }
    *(u16 *)((id << 1) + (s32)obj + 0x1B0) = (refNo < 0) ? 0x7FFF : refNo;
    return 1;
}

typedef struct {
    s8 unused : 5;
    s8 available : 1;
    s8 remaining : 2;
} Flags_001F2EC0;

typedef struct {
    f32 x, y, z, w;
} Vec4_001F2EC0;

/* Whether model slot `index` has a model bound. */
static inline s32 active_001F2EC0(s32 index) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    if (*(s8 *)((u8 *)obj + 0x1F2) >= 0) {
        return 1;
    }
    return 0;
}

/* Reference `ref` of model slot `index` (`which` picks the word). */
s32 SzModel_GetRef(s32 index, s32 ref, s32 which) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    if (!active_001F2EC0(index)) {
        return 0;
    }
    if (!((Flags_001F2EC0 *)((u8 *)obj + 0x20C))->available) {
        return 0;
    }
    if (ref < 0 || ref >= 8) {
        return 0;
    }
    if (!(*(u16 *)((ref << 1) + (s32)obj + 0x1B0) & 0x8000)) {
        return 0;
    }
    *(Vec4_001F2EC0 *)which = *(Vec4_001F2EC0 *)((ref << 4) + (s32)obj + 0xA0);
    return 1;
}

/* Sets model slot `index`'s deepest draw-order level. */
s32 SzModel_SetMaxOT(s32 index, s16 value) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    *(s16 *)((u8 *)obj + 0x20A) = value;
    return 1;
}

/* Model slot `index`'s deepest draw-order level. */
s32 SzModel_GetMaxOT(s32 index) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return -1;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return -1;
    }
    return *(u16 *)((u8 *)obj + 0x20A);
}

typedef struct {
    s8 reserved : 1;
    s8 enabled : 1;
} Flags_001F30B0;

/* Shows or hides model slot `index`. */
s32 SzModel_SetDrawFlag(s32 index, s32 on) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }

    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }

    ((Flags_001F30B0 *)((u8 *)obj + 0x20C))->enabled = (s8)on;
    return 1;
}

typedef struct {
    s8 unused : 1;
    s8 enabled : 1;
} Flags_001F3130;

/* Whether model slot `index` is shown. */
s32 SzModel_GetDrawFlag(s32 index) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    return ((Flags_001F3130 *)((u8 *)obj + 0x20C))->enabled ? 1 : 0;
}

typedef struct {
    s8 low : 6;
    s8 flag : 1;
    s8 high : 1;
} Flags_001F3190;

/* Turns model slot `index`'s matrix calculation on or off. */
s32 SzModel_SetCalcFlag(s32 index, s32 on) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    ((Flags_001F3190 *)((u8 *)obj + 0x20C))->flag = on;
    return 1;
}

typedef struct {
    s8 : 6;
    s8 active : 1;
    s8 : 1;
} Flags_001F3210;

/* Whether model slot `index`'s matrices are calculated when it draws. */
s32 SzModel_GetCalcFlag(s32 index) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    return ((Flags_001F3210 *)((u8 *)obj + 0x20C))->active ? 1 : 0;
}

typedef struct {
    s8 : 7;
    s8 enabled : 1;
} Flags_001F3270;

/* Turns fog on or off for model slot `index`. */
s32 SzModel_SetFogFlag(s32 index, s64 on) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    ((Flags_001F3270 *)((u8 *)obj + 0x20C))->enabled = (s8)on;
    return 1;
}

typedef struct {
    s8 enabled : 1;
} Flags_001F32F0;

/* Pauses or resumes model slot `index`'s animation. */
s32 SzModel_SetPauseFlag(s32 index, s64 on) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    ((Flags_001F32F0 *)((u8 *)obj + 0x20D))->enabled = on;
    return 1;
}

typedef struct {
    s8 active : 1;
} Flags_001F3360;

/* Whether model slot `index`'s animation is paused. */
s32 SzModel_GetPauseFlag(s32 index) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    return ((Flags_001F3360 *)((u8 *)obj + 0x20D))->active ? 1 : 0;
}

typedef struct {
    s8 : 1;
    s8 enabled : 1;
} Flags_001F33C0;

/* Turns model slot `index` to stone or back. */
s32 SzModel_SetStoneFlag(s32 index, s64 on) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    ((Flags_001F33C0 *)((u8 *)obj + 0x20D))->enabled = (s8)on;
    return 1;
}

typedef struct {
    s8 bit0 : 1;
    s8 enabled : 1;
} Flags_001F3440;

/* Whether model slot `index` is stone. */
s32 SzModel_GetStoneFlag(s32 index) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    return ((Flags_001F3440 *)((u8 *)obj + 0x20D))->enabled ? 1 : 0;
}
extern struct DotrObject *D_0031ABB0_b_3[];
struct DotrObjectShadeHeader {
    unsigned char unknown_00[0x1c];
    int unknown_1c;
    unsigned char unknown_20[8];
    int unknown_28;
    int unknown_2c;
};
struct DotrObjectShadeNode {
    unsigned char unknown_00[0x10];
    struct DotrObjectShadeInfo {
        int unknown_00;
        int unknown_04;
        int unknown_08;
        int unknown_0c;
    } unknown_10;
};
struct DotrObjectShadeSlot {
    struct DotrObjectShadeNode *node;
    int unknown_04[3];
};
extern int func_00241A00_b(float scale, unsigned short color, int e);

/* Sets how far model slot `index` has turned to stone. */
int SzModel_SetStoneRatio(int index, int value)
{
    struct DotrObject *p;
    struct DotrObjectLink *base;
    struct DotrObjectShadeHeader *header;
    int count;
    int i;
    unsigned short *words;
    int left;
    struct DotrObjectShadeSlot *slot;
    int level;
    struct DotrObjectShadeNode *node;
    int *list;
    struct DotrObjectShadeInfo *info;

    if (index < 0 || index >= 84) {
        return 0;
    }
    p = D_0031ABB0_b_3[index];
    if (p == 0) {
        return 0;
    }
    if (p->unknown_1f2 < 0) {
        return 0;
    }
    base = p->unknown_138;
    if (base == 0) {
        return 0;
    }
    if (p->unknown_20c.unknown_bit_3) {
        return 0;
    }
    if (base == 0) {
        return 0;
    }
    header = *(struct DotrObjectShadeHeader **)p->unknown_13c;
    if (header == 0) {
        return 0;
    }
    if (header->unknown_2c == 0) {
        return 0;
    }
    if (!p->unknown_20d.unknown_bit_1) {
        return 0;
    }
    level = value & 0xff;
    if (level < p->unknown_200) {
        return 0;
    }
    list = (int *)((char *)base + header->unknown_28);
    count = *list;
    slot = (struct DotrObjectShadeSlot *)(list + 4);
    for (i = 0; i < count; i++, slot++) {
        node = slot->node;
        if (node != 0 && (info = &node->unknown_10, node->unknown_10.unknown_0c != 0)) {
            words = (unsigned short *)((char *)node + info->unknown_08 + 96) + p->unknown_200;
            left = level - p->unknown_200 + 1;
            while (left-- != 0) {
                *words = func_00241A00_b(1.0f, *words, 6);
                words++;
            }
        }
    }
    p->unknown_200 = value;
    return 1;
}

typedef struct {
    s8 unused : 1;
    s8 active : 1;
} Flags_001F3690;

/* How far model slot `index` has turned to stone. */
s32 SzModel_GetStoneRatio(s32 index) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return -1;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return -1;
    }
    if (((Flags_001F3690 *)((u8 *)obj + 0x20D))->active != 0) {
        return *(u8 *)((u8 *)obj + 0x200);
    }
    return -1;
}

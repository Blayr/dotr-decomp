/* Text and texture files (SzText_*). */

#include "common.h"

typedef struct Record_002007D0 {
    s32 value0;
    s32 value4;
    s8 flag0 : 1;
    s8 flag1 : 1;
    s8 flag2 : 1;
    s16 index : 13;
    s16 valueA;
} Record_002007D0;

extern struct Entry_002008A0 textureItems[]; /* original: gSzText_aItem */

/* Clears the texture item table. */
void SzText_Init(void) {
    Record_002007D0 *record;
    s32 i;

    record = (Record_002007D0 *)textureItems;
    RhMem_FillMemory((s8 *)&clutState, 0, 6);
    i = 0;
    do {
        record->value0 = 0;
        record->value4 = 0;
        record->flag0 = 0;
        record->flag1 = 0;
        record->flag2 = 0;
        record->index = record->valueA = -1;
        record++;
        i++;
    } while (i < 0x400);
}

typedef struct Entry_002008A0 {
    s32 occupied;
    s32 unknown;
    s16 flags : 3;
    s16 category : 13;
    s16 id;
} Entry_002008A0;

extern Entry_002008A0 textureItems[]; /* original: gSzText_aItem */

/* Texture item `id` of category `category` (0..9), loaded or not, or NULL. */
void *SzText_GetItem(s32 category, s32 id) {
    Entry_002008A0 *entry;
    s32 i;

    entry = textureItems;
    if ((category < 0) || (category >= 10)) {
        return NULL;
    }
    if (id < 0) {
        return NULL;
    }
    i = 0;
    do {
        if (entry->occupied && (entry->category == category) && (entry->id == id)) {
            return entry;
        }
        i++;
        entry++;
    } while (i < 1024);
    return NULL;
}

/* A texture item by category and id. */
static inline Entry_002008A0 *find_00200930(s32 arg0, s32 arg1) {
    Entry_002008A0 *entry;
    s32 i;

    entry = textureItems;
    if ((arg0 < 0) || (arg0 >= 10)) {
        return NULL;
    }
    if (arg1 < 0) {
        return NULL;
    }
    i = 0;
    do {
        if (entry->occupied && (entry->category == arg0) && (entry->id == arg1)) {
            return entry;
        }
        i++;
        entry++;
    } while (i < 1024);
    return NULL;
}

/* Texture item `id` of category `category` if it has finished loading, or NULL. */
void *SzText_GetReadyItem(s32 category, s32 id) {
    Entry_002008A0 *entry = find_00200930(category, id);

    if (entry != NULL && !(entry->occupied & 0x80000000)) {
        return entry;
    }
    return NULL;
}

typedef struct Slot_002009E0 {
    void *ptr;
    s32 x4;
    s16 lo : 3;
    s16 cat : 13;
    s16 type;
} Slot_002009E0;

extern Slot_002009E0 textureItems_2[0x400]; /* original: gSzText_aItem */
extern char D_002D074B[];
extern char D_002D0750[];
extern char *gSzText_apchMerge;
extern char *D_00293CD4;
extern char *D_00293CD8;
extern char *D_00293CDC;
extern char *D_00293CE0;
extern char *D_00293CE4;
extern char *D_00293CE8;
extern char *D_00293CEC;
extern char *D_00293CF0;
extern char *D_00293CF4;
extern s32 anOfs_TEXETC;
extern s32 D_00293CC4;
extern s32 D_00293CC8;
extern s32 D_00293CCC;

/* A texture item by category and type. */
static inline Slot_002009E0 *find_002009E0(s32 cat, s32 type) {
    Slot_002009E0 *p;
    s32 i;

    p = textureItems_2;
    if (type < 0) {
        return NULL;
    }
    for (i = 0; i < 0x400; i++, p++) {
        if (p->ptr != NULL && p->cat == cat && p->type == type) {
            return p;
        }
    }
    return NULL;
}

/* Loads the merged texture set `set` for game mode `mode` (card pictures of both decks, portraits, windows),
   unless already loaded. */
s32 SzText_LoadMerge(s32 set, s32 mode) {
    char name[0x80];
    u16 ids[41];
    u16 list[17];
    u8 *dir;
    s32 result;
    s32 i;
    s32 j;
    s32 idx;
    s32 base;
    s32 n;
    s32 count;
    s32 id;
    s32 got;
    s32 sector;
    s32 pos;
    s32 size;
    s32 k;
    s32 len;
    s32 off;
    u16 t;

    dir = SzFile_GetEnv((s32)D_002D074B);
    result = 0;
    if (set < 0 || set >= 18) {
        return 0;
    }
    switch (set) {
    case 0:
        func_0019B648(name, D_002D0750, dir, gSzText_apchMerge);
        if (find_002009E0(0, 0) == NULL) {
            mode = 1;
        }
        if (find_002009E0(0, 1) != NULL) {
            mode = 1;
        }
        if (find_002009E0(0, 5) != NULL) {
            mode = 1;
        }
        if (find_002009E0(0, 6) != NULL) {
            mode = 1;
        }
        if (mode == 0) {
            return 1;
        }
        for (i = 0; i < 5; i++) {
            SzModel_Preset(i, -1, 999);
        }
        for (i = 0; i < 2; i++) {
            SzModel_Preset(i + 5, -1, 999);
        }
        for (i = 0; i < 1; i++) {
            SzModel_Preset(i + 7, -1, 999);
        }
        for (i = 0; i < 12; i++) {
            SzModel_Preset(i + 8, -1, 999);
        }
        for (i = 1; i < 11; i++) {
            SzDuel_DelUnit(0, i);
            SzDuel_DelUnit(1, i);
        }
        for (i = 0; i < 10; i++) {
            SzModel_Preset(i + 0x14, -1, 999);
        }
        for (i = 0; i < 2; i++) {
            SzModel_Preset(i + 0x20, -1, 999);
        }
        for (i = 0; i < 40; i++) {
            SzModel_Preset(i + 0x22, -1, 999);
        }
        for (i = 0; i < 10; i++) {
            SzModel_Preset(i + 0x4A, -1, 999);
        }
        SzText_Free(0, 1);
        SzText_Free(0, 5);
        SzText_Free(0, 6);
        SzText_Free(1, -1);
        SzText_Free(7, -1);
        SzText_Free(8, -1);
        {
            s32 SZ0;
            s32 CNT0;
            s32 SEC0;
            s32 POS0;
            s32 ID0;
            s32 K0;

            for (K0 = 0, SEC0 = 0, POS0 = 0, ID0 = 0; K0 <= 8; K0++, SEC0 += 0x1A9640, POS0 += 0x1C2000, ID0 += 0x10) {
                if (K0 < 8) {
                    CNT0 = 100;
                } else {
                    CNT0 = 71;
                }
                SZ0 = CNT0 * 0x4800;
                SzText_Free(0, ID0);
                result |= SzText_LoadFileEx(0, ID0, name, (s32)((s64)SEC0 + 0xB1B000), SZ0, POS0, SZ0);
            }
        }
        break;
    case 1:
        func_0019B648(name, D_002D0750, dir, D_00293CD4);
        if (find_002009E0(0, 1) == NULL) {
            mode = 1;
        }
        if (find_002009E0(0, 0) != NULL) {
            mode = 1;
        }
        if (find_002009E0(0, 5) != NULL) {
            mode = 1;
        }
        if (find_002009E0(0, 6) != NULL) {
            mode = 1;
        }
        if (mode == 0) {
            return 1;
        }
        SzText_Free(0, 0);
        SzText_Free(0, 1);
        SzText_Free(0, 5);
        SzText_Free(0, 6);
        SzText_Free(1, -1);
        SzText_Free(7, -1);
        SzText_Free(8, -1);
        result = SzText_LoadFileEx(0, 1, name, 0xB1B000, -1, 0, -1);
        break;
    case 2:
    case 3:
        idx = set - 2;
        got = SzData_GetLeader(idx, SzData_GetCurrentDeck(idx));
        base = idx * 41 + 0xDF;
        func_0019B648(name, D_002D0750, dir, gSzText_apchMerge);
        ids[40] = got;
        for (i = 0; i < 40; i++) {
            ids[i] = SzDuel_InqDeck(idx, i);
        }
        for (i = 0; i < 41; i++) {
            for (j = i + 1; j < 41; j++) {
                if (ids[i] > ids[j]) {
                    t = ids[i];
                    ids[i] = ids[j];
                    ids[j] = t;
                }
            }
        }
        for (i = 0; i < 41; base++, i++) {
            id = ids[i];
            if (id != 999) {
                id = SzData_ExchSpecial(idx, id);
            }
            if (find_002009E0(1, id) == NULL) {
                result |= SzText_LoadFileEx(1, id, name, (s32)((s64)(base * 0x4410) + 0xB1B000), 0x4800, id * 0x4800, 0x4800);
            }
        }
        break;
    case 10:
        n = 0;
        func_0019B648(name, D_002D0750, dir, gSzText_apchMerge);
        for (i = 0; i < 17; i++) {
            list[i] = SzData_GetConstDeck(i, 0);
        }
        for (i = 0; i < 17; i++) {
            for (j = i + 1; j < 17; j++) {
                if (list[i] > list[j]) {
                    t = list[i];
                    list[i] = list[j];
                    list[j] = t;
                }
            }
        }
        SzText_Free(0, 0);
        SzText_Free(0, 1);
        SzText_Free(1, -1);
        for (i = 0; i < 17; n++, i++) {
            id = list[i];
            if (find_002009E0(1, id) == NULL) {
                result |= SzText_LoadFileEx(1, id, name, (s32)((s64)(n * 0x4410) + 0xB1B000), 0x4800, id * 0x4800, 0x4800);
            }
        }
        break;
    case 4:
        result = SzText_LoadMerge(5, mode);
        result |= SzText_LoadMerge(6, mode);
        break;
    case 5:
    case 6:
        idx = set - 5;
        got = SzData_GetLeader(idx, SzData_GetCurrentDeck(idx));
        func_0019B648(name, D_002D0750, dir, D_00293CD8);
        if (find_002009E0(2, idx) == NULL) {
            mode = 1;
        }
        if (mode == 0) {
            return 1;
        }
        SzText_Free(2, idx);
        if (got == 999) {
            break;
        }
        id = SzData_ExchSpecial(idx, got);
        pos = idx << 12;
        sector = got << 12;
        if (id != got) {
            sector = (id - 0xAB) << 12;
        }
        result = SzText_LoadFileEx(2, idx, name, (s32)((s64)pos + 0xB19000), 0x1000, sector, 0x1000);
        break;
    case 7:
        result = SzText_LoadMerge(8, mode);
        result |= SzText_LoadMerge(9, mode);
        break;
    case 8:
    case 9:
        {
            s32 ID8;
            s32 I8;
            s32 IDX8;
            s32 GOT8;
            s32 POS8;
            s32 SEC8;
            s32 K8;

            IDX8 = set - 8;
            func_0019B648(name, D_002D0750, dir, D_00293CD8);
            SzText_Free(0, 7);
            SzText_Free(0, 8);
            SzText_Free(0, 9);
            SzText_Free(9, -1);
            for (I8 = 0; I8 < 3; I8++) {
                GOT8 = SzData_GetLeader(IDX8, I8);
                ID8 = SzData_ExchSpecial(IDX8, GOT8);
                K8 = I8 + (IDX8 ? 20 : 10);
                POS8 = (IDX8 * 3 + I8) << 12;
                SEC8 = GOT8 << 12;
                if (ID8 != GOT8) {
                    SEC8 = (ID8 - 0xAB) << 12;
                }
                SzText_Free(2, K8);
                result = SzText_LoadFileEx(2, K8, name, (s32)((s64)POS8 + 0xA75000), 0x1000, SEC8, 0x1000);
            }
        }
        break;
    case 11:
        func_0019B648(name, D_002D0750, dir, D_00293CDC);
        if (find_002009E0(0, 3) == NULL) {
            mode = 1;
        }
        if (mode == 0) {
            return 1;
        }
        SzText_Free(0, 3);
        SzText_Free(3, -1);
        result = SzText_LoadFileEx(0, 3, name, 0x912000, 0x11E800, 0, -1);
        break;
    case 12:
        func_0019B648(name, D_002D0750, dir, D_00293CE0);
        if (find_002009E0(0, 4) == NULL) {
            mode = 1;
        }
        if (mode == 0) {
            return 1;
        }
        SzText_Free(0, 4);
        SzText_Free(4, -1);
        result = SzText_LoadFileEx(0, 4, name, 0xA30800, 0x44800, 0, -1);
        break;
    case 13:
        func_0019B648(name, D_002D0750, dir, D_00293CE4);
        if (find_002009E0(0, 5) == NULL) {
            mode = 1;
        }
        if (find_002009E0(0, 0) != NULL) {
            mode = 1;
        }
        if (find_002009E0(0, 1) != NULL) {
            mode = 1;
        }
        if (mode == 0) {
            return 1;
        }
        SzText_Free(0, 0);
        SzText_Free(0, 1);
        SzText_Free(0, 5);
        SzText_Free(1, -1);
        SzText_Free(7, -1);
        result = SzText_LoadFileEx(0, 5, name, 0xB63540, 0x16A800, 0, -1);
        break;
    case 14:
        func_0019B648(name, D_002D0750, dir, D_00293CE8);
        if (find_002009E0(0, 6) == NULL) {
            mode = 1;
        }
        if (find_002009E0(0, 0) != NULL) {
            mode = 1;
        }
        if (find_002009E0(0, 1) != NULL) {
            mode = 1;
        }
        if (mode == 0) {
            return 1;
        }
        for (i = 0; i < 5; i++) {
            SzModel_Preset(i, -1, 999);
        }
        for (i = 0; i < 2; i++) {
            SzModel_Preset(i + 5, -1, 999);
        }
        for (i = 0; i < 1; i++) {
            SzModel_Preset(i + 7, -1, 999);
        }
        for (i = 0; i < 12; i++) {
            SzModel_Preset(i + 8, -1, 999);
        }
        for (i = 0; i < 2; i++) {
            SzModel_Preset(i + 0x20, -1, 999);
        }
        for (i = 0; i < 10; i++) {
            SzModel_Preset(i + 0x4A, -1, 999);
        }
        SzText_Free(0, 0);
        SzText_Free(0, 1);
        SzText_Free(0, 6);
        SzText_Free(1, -1);
        SzText_Free(8, -1);
        result = SzText_LoadFileEx(0, 6, name, 0xCCDD40, 0x47F000, 0, -1);
        break;
    case 15:
        off = anOfs_TEXETC;
        len = D_00293CC4 - off;
        func_0019B648(name, D_002D0750, dir, D_00293CEC);
        if (find_002009E0(0, 7) == NULL) {
            mode = 1;
        }
        if (find_002009E0(0, 8) != NULL) {
            mode = 1;
        }
        if (find_002009E0(0, 9) != NULL) {
            mode = 1;
        }
        if (mode == 0) {
            return 1;
        }
        SzText_Free(0, 7);
        SzText_Free(0, 8);
        SzText_Free(0, 9);
        SzText_Free(9, -1);
        result = SzText_LoadFileEx(0, 7, name, 0xA75000, len, off, len);
        break;
    case 16:
        off = D_00293CC4;
        len = D_00293CC8 - off;
        func_0019B648(name, D_002D0750, dir, D_00293CF0);
        if (find_002009E0(0, 8) == NULL) {
            mode = 1;
        }
        if (find_002009E0(0, 7) != NULL) {
            mode = 1;
        }
        if (find_002009E0(0, 9) != NULL) {
            mode = 1;
        }
        if (mode == 0) {
            return 1;
        }
        SzText_Free(0, 8);
        SzText_Free(0, 7);
        SzText_Free(0, 9);
        SzText_Free(9, -1);
        result = SzText_LoadFileEx(0, 8, name, 0xA75000, len, off, len);
        break;
    case 17:
        off = D_00293CC8;
        len = D_00293CCC - off;
        func_0019B648(name, D_002D0750, dir, D_00293CF4);
        if (find_002009E0(0, 9) == NULL) {
            mode = 1;
        }
        if (find_002009E0(0, 7) != NULL) {
            mode = 1;
        }
        if (find_002009E0(0, 8) != NULL) {
            mode = 1;
        }
        if (mode == 0) {
            return 1;
        }
        SzText_Free(0, 9);
        SzText_Free(0, 7);
        SzText_Free(0, 8);
        SzText_Free(9, -1);
        result = SzText_LoadFileEx(0, 9, name, 0xA75000, len, off, len);
        break;
    }
    return result;
}

typedef struct Entry_00202220 {
    s32 state;
    char *name;
    s8 flag0 : 1;
    s8 flag1 : 1;
    s8 flag2 : 1;
    s16 group : 13;
    s16 index;
} Entry_00202220;

extern s8 D_002BD0C1[];
extern char D_002D0760[];

/* A texture item by group and index. */
static inline Entry_00202220 *find_00202220(s32 group, s32 index) {
    extern Entry_00202220 textureItems_3[];
    Entry_00202220 *entry = textureItems_3;
    s32 i;

    if (group < 0 || group >= 10) {
        return NULL;
    }
    if (index < 0) {
        return NULL;
    }
    i = 0;
    do {
        if (entry->state != 0 && entry->group == group && entry->index == index) {
            return entry;
        }
        i++;
        entry++;
    } while (i < 1024);
    return NULL;
}

/* A free texture item record, or NULL. */
static inline Entry_00202220 *empty_00202220(void) {
    extern Entry_00202220 textureItems_3[];
    Entry_00202220 *entry = textureItems_3;
    s32 i = 0;

    do {
        if (entry->state == 0) {
            return entry;
        }
        i++;
        entry++;
    } while (i < 1024);
    return NULL;
}

/* Starts loading texture file `name` as item `id` of category `category` (0..9), into `address` if given (else
   allocated). */
s32 SzText_LoadFileEx(s32 category, s32 id, char *name, s32 address, s32 size, s32 offset, s32 length) {
    Entry_00202220 *entry;
    char path[128];
    extern s32 SzFile_ReadRequestParam();
    extern void func_0019B648();

    if (category < 0 || category >= 10) {
        return 0;
    }
    if (id < 0) {
        return 0;
    }
    if (find_00202220(category, id) != NULL) {
        return 0;
    }
    entry = empty_00202220();
    if (entry == NULL) {
        return 0;
    }
    if ((D_002BD0C1[*(s8 *)name] & 3) && ((s8 *)name)[1] == ':') {
        func_0019BDD8(path, name);
    } else {
        func_0019B648(path, D_002D0760, SzFile_GetEnv((s32)D_002D074B), name);
    }
    if (SzFile_ReadRequestParam(category | 0x1000, 0, (s32)path, address, size, offset, length,
                     (s32)lSzText_LoadFileCB, entry) == 0) {
        return 0;
    }
    entry->name = SzMem_StrDup(name);
    entry->state = 0x80000000;
    entry->flag0 = 0;
    entry->flag1 = 0;
    entry->flag2 = (s8)(address != 0 ? 0 : 1);
    entry->group = (s16)category;
    entry->index = id;
    return 1;
}

typedef struct Track_002024D0 {
    s32 *data;
    s32 buffer;
    s16 low : 3;
    s16 count : 13;
    s16 mode;
    u16 *names;
} Track_002024D0;

typedef struct Stream_002024D0 {
    u8 pad0[8];
    s32 size : 31;
    s32 unk8 : 1;
    s32 unkC : 31;
    s32 owned : 1;
    u8 pad10[4];
    s32 *data;
    u8 pad18[4];
    Track_002024D0 *track;
} Stream_002024D0;

/* A texture file has loaded (`ok`): relocates its TIM2 pictures and marks the item ready. */
void lSzText_LoadFileCB(void *request, s32 ok) {
    extern u16 D_002CE9FC[];
    Stream_002024D0 *stream = request;
    Track_002024D0 *track = stream->track;
    u8 *block;
    s32 kind;
    s32 remaining;
    s32 index;
    u8 *dest;
    s32 step;
    s32 value;
    s32 blockSize;
    s32 i;
    s32 offset;
    s32 chunk;
    s16 mode;
    u16 *names;

    if (ok != 0 && *stream->data != 0x324852) {
        if (stream->owned) {
            SzMem_Free((s32)stream->data);
        }
        ok = 0;
    }
    if (ok == 0) {
        if (track->buffer != 0) {
            SzMem_Free(track->buffer);
            track->buffer = 0;
        }
        track->data = NULL;
        return;
    }
    track->data = stream->data;
    if (track->count == 0) {
        mode = track->mode;
        index = 0;
        block = (u8 *)track->data;
        blockSize = ((s32 *)block)[2];
        kind = mode & 0xF;
        remaining = stream->size;
        if (kind == 0) {
            index = (mode >> 4) * 100;
        }
        i = 0;
        offset = index * blockSize;
        names = D_002CE9FC;
        chunk = blockSize >> 4;
        while (1) {
            value = i;
            dest = NULL;
            step = blockSize;
            if (*(s32 *)block == 0x324852) {
                dest = block;
                if (kind == 0 || kind == 2) {
                    value = index;
                    if (index != 0) {
                        {
                            s64 t = offset;
                            dest = (u8 *)(t + 0xB1B000);
                        }
                        RhMem_CopyMemory16(dest, block, chunk);
                    }
                    index++;
                    offset += blockSize;
                    if (kind == 0) {
                        step = 0x4800;
                    } else {
                        step = 0x1000;
                    }
                } else if (kind == 1) {
                    value = *names;
                } else {
                    step = ((s32 *)block)[2];
                }
                RhText_BindAddress((s32)dest);
            } else if (remaining < blockSize) {
                return;
            }
            switch (kind) {
            case 0:
                SzText_AddFile(1, value, 0, (s32)dest);
                break;
            case 1:
                SzText_AddFile(1, value, 0, (s32)dest);
                break;
            case 2:
                SzText_AddFile(2, value, 0, (s32)dest);
                break;
            case 3:
                SzText_AddFile(3, value, 0, (s32)dest);
                break;
            case 4:
                SzText_AddFile(4, value, 0, (s32)dest);
                break;
            case 5:
                SzText_AddFile(7, value, 0, (s32)dest);
                break;
            case 6:
                SzText_AddFile(8, value, 0, (s32)dest);
                break;
            case 7:
            case 8:
            case 9:
                SzText_AddFile(9, value, 0, (s32)dest);
                break;
            }
            block += step;
            remaining -= step;
            if (remaining <= 0) {
                return;
            }
            names++;
            i++;
        }
    } else {
        RhText_BindAddress((s32)track->data);
    }
}

typedef struct {
    s32 data;
    char *name;
    s8 flag0 : 1;
    s8 flag1 : 1;
    s8 flag2 : 1;
    s16 category : 13;
    s16 id;
} Slot_00202810;

/* A texture item by category and id. */
static inline void *find_00202810(s32 arg0, s32 arg1) {
    Slot_00202810 *entry = SzText_GetItem(arg0, arg1);
    if (entry != NULL && !(entry->data & 0x80000000)) {
        return entry;
    }
    return NULL;
}

/* A free texture item record, or NULL. */
static inline void *alloc_00202810(void) {
    extern Slot_00202810 textureItems_3[];
    Slot_00202810 *entry;
    s32 i;

    entry = textureItems_3;
    i = 0;
    do {
        if (entry->data == 0) {
            return entry;
        }
        i++;
        entry++;
    } while (i < 0x400);
    return NULL;
}

/* Registers texture data already in memory at `data` as item `id` of category `category` (replacing any). */
s32 SzText_AddFile(s32 category, s32 id, char *name, s32 data) {
    Slot_00202810 *entry;

    if (category < 0 || category >= 10) {
        return 0;
    }
    if (id < 0) {
        return 0;
    }
    entry = find_00202810(category, id);
    if (entry == NULL) {
        entry = alloc_00202810();
        if (entry == NULL) {
            return 0;
        }
    } else {
        SzText_Free(category, id);
    }
    entry->name = (name != NULL) ? SzMem_StrDup(name) : NULL;
    entry->data = data;
    entry->flag0 = 0;
    entry->flag1 = 0;
    entry->flag2 = 0;
    entry->category = category;
    entry->id = id;
    return 1;
}

typedef struct {
    s32 data;
    char *name;
    s8 flag0 : 1;
    s8 flag1 : 1;
    s8 flag2 : 1;
    s16 category : 13;
    s16 id;
} Slot_002029B0;

/* Frees the texture items of `category` and `id` (-1 for any). Returns whether any was freed. */
s32 SzText_Free(s32 category, s32 id) {
    extern Slot_002029B0 textureItems_3[];
    Slot_002029B0 *entry;
    s32 i;
    s32 result;

    entry = textureItems_3;
    result = 0;
    i = 0;
    do {
        if (entry->data != 0 && (category < 0 || entry->category == category) &&
            (id < 0 || entry->id == id) && !(entry->data & 0x80000000)) {
            if (entry->name != NULL) {
                SzMem_Free((s32)entry->name);
                entry->name = NULL;
            }
            if (entry->data != 0) {
                if (entry->flag2) {
                    SzMem_Free(entry->data);
                }
                entry->data = 0;
            }
            result = 1;
        }
        i++;
        entry++;
    } while (i < 0x400);
    return result;
}

/* Sends the requested texture items of `category` to GS memory. */
s32 SzText_DoRequest(s32 category, s32 address) {
    s32 sp3C;

    RhBase_SetVifPacketArea(SzText_DoRequest_Pipe(RhBase_GetVifPacketArea(), category, address, &sp3C));
    return sp3C;
}

typedef struct Record_00202B00 {
    s32 data;
    s32 unused;
    union {
        struct {
            s8 active : 1;
            s8 excluded : 1;
            s8 unused : 6;
        } flags;
        struct {
            s16 unused : 3;
            s16 category : 13;
        } category;
    } state;
    s16 padding;
} Record_00202B00;

/* Sends the requested texture items of `category` (-1 for all) to GS memory from `address`; the space used through
   `outSize`. */
s32 SzText_DoRequest_Pipe(s32 packet, s32 category, s32 address, s32 *outSize) {
    extern Record_00202B00 textureItems_3[];
    Record_00202B00 *entry;
    s32 start;
    s32 i;
    s32 size;

    entry = textureItems_3;
    start = address;
    i = 0;
    do {
        if (entry->data != 0 && entry->state.flags.active && !entry->state.flags.excluded &&
            (category < 0 || entry->state.category.category == category)) {
            packet = SzText_Load_Pipe(packet, entry->data, address, (s32) &size);
            address += size;
        }
        i++;
        entry++;
    } while (i < 0x400);
    if (outSize != NULL) {
        *outSize = address - start;
    }
    return packet;
}

typedef struct Entry_00202BF0 {
    s32 value;
    s32 unk4;
    s8 enabled : 1;
    s8 pending : 1;
    s8 other : 6;
} Entry_00202BF0;

/* A texture item by category and id. */
static inline Entry_00202BF0 *lookup_00202BF0(s32 arg0, s32 arg1) {
    Entry_00202BF0 *entry;

    entry = SzText_GetItem(arg0, arg1);
    if ((entry != NULL) && !(entry->value & 0x80000000)) {
        return entry;
    }
    return NULL;
}

/* Asks for texture item `id` of category `category` to be sent to GS memory. Returns its data. */
s32 SzText_LoadRequest(s32 category, s32 id) {
    Entry_00202BF0 *entry;

    if ((category < 0) || (category >= 0xA)) {
        return 0;
    }
    if (id < 0) {
        return 0;
    }
    entry = lookup_00202BF0(category, id);
    if (entry == NULL) {
        return 0;
    }
    entry->enabled = 1;
    entry->pending = 0;
    return entry->value;
}

typedef struct Flags_00202CB0 {
    s8 active : 1;
    s8 enabled : 1;
    s8 unused : 6;
} Flags_00202CB0;

typedef struct Filter_00202CB0 {
    s16 unused : 3;
    s16 category : 13;
} Filter_00202CB0;

typedef struct Entry_00202CB0 {
    s32 handle;
    s32 unused;
    union {
        Flags_00202CB0 flags;
        Filter_00202CB0 filter;
    } state;
    s16 id;
} Entry_00202CB0;

/* Excludes (`enabled` 0) or includes a requested texture item. */
s32 SzText_SleepRequest(s32 category, s32 id, s32 enabled) {
    extern Entry_00202CB0 textureItems_3[];
    Entry_00202CB0 *entry;
    s32 i;
    s32 result;

    entry = textureItems_3;
    result = 0;
    i = 0;
    do {
        if (entry->handle != 0 && entry->state.flags.active != 0 &&
            (category < 0 || entry->state.filter.category == category) &&
            (id < 0 || entry->id == id)) {
            entry->state.flags.enabled = (s8)(enabled ? 1 : 0);
            result = 1;
        }
        i++;
        entry++;
    } while (i < 0x400);
    return result;
}

typedef struct {
    s32 data;
    s32 unknown;
    s16 active : 1;
    s16 flags : 2;
    s16 category : 13;
    s16 id;
} Entry_00202D60;

extern Entry_00202D60 textureItems_3[]; /* original: gSzText_aItem */

/* Drops the request for texture item `id` of category `category`. */
s32 SzText_FreeRequest(s32 category, s32 id) {
    Entry_00202D60 *var_t0;
    s32 i;
    s32 var_v0;

    var_t0 = textureItems_3;
    var_v0 = 0;
    i = 0;
    do {
        if (var_t0->data != 0 && var_t0->active != 0) {
            if ((category < 0 || var_t0->category == category) &&
                (id < 0 || var_t0->id == id)) {
                var_v0 = 1;
                var_t0->active = 0;
            }
        }
        i += 1;
        var_t0++;
    } while (i < 0x400);
    return var_v0;
}

/* Starts handing out palette space at GS address `address`, `pages` pages of it. */
u16 SzText_InitClutManage(s16 address, s32 pages) {
    clutState = address;
    D_00322992 = (u16) ((s32) ((s32) (pages << 0xD) >> 6) >> 2);
    D_00322994 = 0;
    return D_00322992;
}

typedef struct Fields_00202E30 {
    u8 padding[0x40];
    u16 field40;
    u16 field42;
} Fields_00202E30;

/* The palette size of a TIM2 picture. */
s32 SzText_GetClutSize(void *header) {
    s32 multiplier;
    s32 shift;
    s32 result;

    switch (((Fields_00202E30 *)header)->field40) {
    case 0x14:
        shift = 4;
        break;
    case 0x13:
        shift = 8;
        break;
    default:
        return 0;
    }

    switch (((Fields_00202E30 *)header)->field42) {
    case 0:
        multiplier = 4;
        break;
    case 2:
    case 0xA:
        multiplier = 2;
        break;
    default:
        return 0;
    }

    result = ((1 << shift) * multiplier / 64) / 4;
    return result <= 0 ? 1 : result;
}

typedef struct {
    u16 base;
    u16 capacity;
    u16 used;
} Buffer_00202F00;

/* Takes `count` units of palette space; returns their GS address, or -1 if there is no room. */
s32 SzText_GetClutGsAddr(s32 count) {
    s32 temp_v0;
    Buffer_00202F00 *buffer = (Buffer_00202F00 *)&clutState;

    if (((u16) D_00322994 + count) > (s32) D_00322992) {
        return -1;
    }
    temp_v0 = buffer->base + buffer->used;
    buffer->used += count;
    return temp_v0;
}

/* Sends a TIM2 picture to GS memory. */
void SzText_Load(s32 data, s32 address, s32 outSize) {
    RhBase_SetVifPacketArea(SzText_Load_Pipe(RhBase_GetVifPacketArea(), data, address, outSize));
}

typedef struct Tex0_00202FB0 {
    u64 base : 14;
    u64 reserved0 : 23;
    u64 clut : 14;
    u64 reserved1 : 13;
} Tex0_00202FB0;

typedef struct Header_00202FB0 {
    s32 dataOffset;
    s32 dataSize;
    u8 reserved0[0x18];
    Tex0_00202FB0 tex0;
    u8 reserved1[0x20];
    s32 packetCount;
} Header_00202FB0;

typedef struct Packet_00202FB0 {
    u8 reserved0[0x24];
    u16 base : 14;
    u16 reserved1 : 2;
    u8 reserved2[0xA];
} Packet_00202FB0;

typedef struct Range_00202FB0 {
    u16 base;
    u16 size;
    u16 used;
} Range_00202FB0;

/* Palette space of `size`, or -1. */
/* clutState starts a {base, size, used} record of three shorts. */
static inline s32 allocate_00202FB0(s32 size) {
    Range_00202FB0 *range = (Range_00202FB0 *)&clutState;
    s32 base;

    if ((u16)(&clutState)[2] + size > (u16)(&clutState)[1]) {
        return -1;
    }
    base = range->base + range->used;
    range->used += size;
    return base;
}

/* Restarts the palette space. */
static inline u16 reset_00202FB0(s16 base) {
    clutState = base;
    (&clutState)[1] = 0x20;
    (&clutState)[2] = 0;
    return (u16)(&clutState)[1];
}

/* Sends the TIM2 picture at `data` to GS memory at `address` (its palette where there is space); the space used
   through `outSize`. */
s32 SzText_Load_Pipe(s32 out, s32 data, s32 address, s32 outSize) {
    extern s32 RhMem_CopyMemory16();
    Header_00202FB0 *header = (Header_00202FB0 *)(data + 0x10);
    Packet_00202FB0 *packet = (Packet_00202FB0 *)out;
    s32 clutSize;
    s32 clutBase;
    s32 start = address;
    s32 count;

    clutBase = 0;
    if (outSize != 0) {
        *(s32 *)outSize = 0;
    }
    if (data == 0) {
        return out;
    }

    if ((clutSize = SzText_GetClutSize(header)) > 0) {
        clutBase = allocate_00202FB0(clutSize);
        if (clutBase < 0) {
            address += reset_00202FB0(address);
            clutBase = allocate_00202FB0(clutSize);
        }
    }

    out = RhMem_CopyMemory16((void *)out, (void *)(data + header->dataOffset), header->dataSize >> 4);
    header->tex0.base = address;
    header->tex0.clut = clutBase;
    count = header->packetCount;
    if (clutSize != 0) {
        count--;
        packet->base = clutBase;
        packet++;
    }
    while (count--) {
        packet->base = address;
        address += 0x20;
        packet++;
    }
    if (outSize != 0) {
        *(s32 *)outSize = address - start;
    }
    return out;
}

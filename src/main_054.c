#include "common.h"

static s32 lSzFile_NextRequest(void);

/* Turns a path into the disc's form: upper case, back slashes, ";1" at the end. */
void lSzFile_StrNormalize(s8 *p) {
    s32 network;
    s32 first;
    s32 c;

    first = p[0];
    network = 0;
    if ((first == '/' && p[1] == '/') ||
        (first == '\\' && p[1] == '\\')) {
        network = 1;
    }
    lRhFile_StrUpper(p);
    while ((c = *p) != 0) {
        if (network != 0) {
            if (c == '/') {
                *p = '\\';
            }
        } else if (c == '\\') {
            *p = '/';
        }
        p++;
    }
}

/* Whether any file read is still queued or running. */
s32 SzFile_InqRequestEx(void) {
    s32 var_s0;

    var_s0 = 0;
loop_1:
    if (SzFile_InqRequestX(var_s0, 1) != 0) {
        return 1;
    }
    var_s0 += 1;
    if (var_s0 >= 5) {
        return 0;
    }
    goto loop_1;
}

/* The first queued read of owner `owner` (-1 for any), or 0. */
s32 SzFile_InqRequest(s32 owner) {
    return SzFile_InqRequestX(owner, 0);
}

typedef struct Record_001FF360 {
    s32 status;
    s16 id;
    u8 padding[0x1E];
} Record_001FF360;

extern Record_001FF360 D_00320370[];

/* The first queued read of owner `owner` (-1 for any; `byGroup` compares owner >> 10), or 0. */
s32 SzFile_InqRequestX(s32 owner, s32 byGroup) {
    Record_001FF360 *record;
    s32 remaining;
    s32 shift;

    shift = byGroup ? 10 : 0;
    record = D_00320370;
    for (remaining = 0x100; remaining--; record++) {
        if (record->status >= 0 &&
            (owner < 0 || owner == (record->id >> shift))) {
            return (s32) record;
        }
    }
    record = NULL;
    return (s32) record;
}

/* Runs the file read queue for this frame. */
void SzFile_DoRequest(void) {
    s32 start;

    start = *(s32 *)0x10000800;
    do {
        if (SzFile_DoRequestS() == 0) {
            break;
        }
    } while (*(s32 *)0x10000800 - start <= 0x40);
}

typedef struct State_001FF420 {
    u8 pad[0x6688];
    s32 current;
} State_001FF420;

typedef struct Flags_001FF420 {
    s8 reserved : 1;
    s8 active : 1;
    s8 remaining : 6;
} Flags_001FF420;


/* Runs the file read queue until it is empty. */
s32 SzFile_DoRequestS(void) {
    extern State_001FF420 fileQueue;
    extern Flags_001FF420 D_00322980;
    State_001FF420 *state = &fileQueue;
    s32 temp_v0;

    if (D_00322980.active == 0) {
        temp_v0 = lSzFile_NextRequest();
        state->current = temp_v0;
        if (temp_v0 < 0) {
            return 0;
        }
    }
    return lSzFile_DoRequestMain(state->current);
}

typedef struct Word_001FF480 {
    s32 value : 31;
    s32 flag : 1;
} Word_001FF480;

typedef struct Flags_001FF480 {
    s8 bit0 : 1;
    s8 busy : 1;
    s8 rest : 6;
} Flags_001FF480;

typedef struct Entry_001FF480 {
    s32 handle;
    s32 unknown04;
    Word_001FF480 size;
    Word_001FF480 offset;
    Word_001FF480 length;
    s32 buffer;
    s32 unknown18;
    s32 unknown1C;
    s32 name;
} Entry_001FF480;

typedef struct State_001FF480 {
    u8 unknown0000[0x4080];
    Entry_001FF480 entries[256];
    u8 unknown6480[0x210];
    Flags_001FF480 flags;
} State_001FF480;

typedef struct Progress_001FF480 {
    f32 value;
} Progress_001FF480;

extern Progress_001FF480 D_00293CB0;
extern char D_002D0648[];
extern char D_002D064D[];

/* Runs read request `index`: opens the file (by name, or by disc sector), allocates its buffer, reads it; 1 when
   it finished. */
s32 lSzFile_DoRequestMain(s32 index) {
    extern State_001FF480 fileQueue;
    extern s32 func_0019B648();
    char path[0x88];
    s32 status;
    Progress_001FF480 progress;
    State_001FF480 *state;
    Entry_001FF480 *entry;
    s32 sector;
    s32 count;

    state = &fileQueue;
    if (index < 0) {
        return 0;
    }
    entry = &state->entries[index];
    if (entry->length.flag) {
        if (state->flags.busy) {
            return 0;
        }
        if (!entry->size.flag) {
            entry->size.flag = 1;
        }
        if (func_00191A58(1) != 2) {
            return 0;
        }
        progress = D_00293CB0;
        if (entry->size.value != 0 && entry->buffer == 0) {
            if ((entry->buffer = SzMem_Alloc(entry->size.value)) == 0) {
                lSzFile_TermRequest(index, 0);
                return 0;
            }
            entry->offset.flag = 1;
        }
        if (entry->length.value < 0) {
            entry->length.value = entry->size.value - entry->offset.value;
        }
        sector = entry->handle + (entry->offset.value >> 11);
        count = entry->length.value >> 11;
        FlushCache(0);
        if (func_00191D18(sector, count, entry->buffer, &progress) == 0) {
            return 0;
        }
        state->flags.busy = 1;
    } else {
        state->flags.busy = 1;
        if (!entry->size.flag) {
            func_0019B648(path, D_002D0648, D_002D064D, entry->name);
            if (entry->size.value < 0) {
                if ((entry->handle = func_0017FA98(path, 1)) < 0) {
                    lSzFile_TermRequest(index, 0);
                    return 0;
                }
                if ((entry->size.value = func_0017FEA0(entry->handle, 0, 2)) < 0) {
                    lSzFile_TermRequest(index, 0);
                    return 0;
                }
                func_0017FD20(entry->handle);
            }
            entry->handle = func_0017FA98(path, 0x8001);
            if (entry->handle < 0) {
                lSzFile_TermRequest(index, 0);
                return 0;
            }
            if (entry->size.value != 0) {
                entry->size.value = (entry->size.value + 15) & ~15;
                if (entry->buffer == 0) {
                    if ((entry->buffer = SzMem_Alloc(entry->size.value)) == 0) {
                        lSzFile_TermRequest(index, 0);
                        return 0;
                    }
                    entry->offset.flag = 1;
                }
            }
            if (entry->length.value < 0) {
                entry->length.value = entry->size.value - entry->offset.value;
            }
            entry->length.value = (entry->length.value + 15) & ~15;
            if (entry->offset.value != 0) {
                if (func_0017FEA0(entry->handle, entry->offset.value, 0) < 0) {
                    lSzFile_TermRequest(index, 0);
                    return 0;
                }
                do {
                    if (func_00180608(entry->handle, 1, &status) < 0) {
                        lSzFile_TermRequest(index, 0);
                        return 0;
                    }
                } while (status != 0);
            }
            FlushCache(0);
            if (func_001800D8(entry->handle, entry->buffer, entry->length.value) < 0) {
                lSzFile_TermRequest(index, 0);
                return 0;
            }
            entry->size.flag = 1;
        }
        if (func_00180608(entry->handle, 1, &status) < 0) {
            lSzFile_TermRequest(index, 0);
            return 0;
        }
        if (status == 0) {
            FlushCache(0);
            lSzFile_TermRequest(index, 1);
            return 1;
        }
    }
    return 0;
}

typedef struct {
    s32 state;
    s16 unknown;
    s16 priority;
    u8 padding[0x1C];
} Entry_001FF9C0;

typedef struct {
    u8 padding[0x4080];
    Entry_001FF9C0 entries[256];
    u8 padding2[0x20C];
    u16 head;
    u16 count;
} Queue_001FF9C0;

/* The next read request to run, or -1. */
static s32 lSzFile_NextRequest(void) {
    extern Queue_001FF9C0 fileQueue;
    Queue_001FF9C0 *queue = &fileQueue;
    s32 bestIndex = -1;
    s32 bestPriority = -1;
    s32 i;
    s32 index;
    s32 count;

    while (queue->count != 0) {
        if (queue->entries[queue->head].state >= 0) {
            break;
        }
        if (--queue->count > 0) {
            queue->head = (queue->head + 1) % 256;
        }
    }

    count = queue->count & 0xFFFF;
    i = 0;
    goto check;
loop:
    {
        Entry_001FF9C0 *entry;

        index = (queue->head + i) % 256;
        entry = &queue->entries[index];
        if (entry->state >= 0) {
            if (bestPriority < entry->priority) {
                bestPriority = entry->priority;
                bestIndex = index;
            }
        }
        i++;
    }
check:
    if (i < count) {
        goto loop;
    }
    return bestIndex;
}

typedef struct Flags_001FFAC0 {
    s8 unused : 7;
    s8 set : 1;
} Flags_001FFAC0;

typedef struct Entry_001FFAC0 {
    s32 handle;
    s16 id;
    u8 pad06[9];
    Flags_001FFAC0 flags0F;
    u8 pad10[3];
    Flags_001FFAC0 flags13;
    void *allocation;
    void (*callback)(void *, s32);
    s32 unused1C;
    void *extra;
} Entry_001FFAC0;

typedef struct Callback_001FFAC0 {
    s32 handle;
    void (*callback)(s32);
} Callback_001FFAC0;

typedef struct StateFlags_001FFAC0 {
    s8 unused0 : 1;
    s8 active : 1;
    s8 unused2 : 6;
} StateFlags_001FFAC0;

typedef struct State_001FFAC0 {
    u8 pad0000[0x4080];
    Entry_001FFAC0 entries[256];
    u8 pad6480[0x20C];
    u16 index;
    u16 count;
    StateFlags_001FFAC0 flags;
} State_001FFAC0;


/* Ends read request `index` (`ok` if it worked): calls its callback, closes the file, frees what it took, and its
   group's callback when the group is done. */
void lSzFile_TermRequest(s32 index, s32 ok) {
    extern State_001FFAC0 fileQueue;
    extern void *SzFile_InqGroup();
    extern void SzMem_Free();
    State_001FFAC0 *state;
    Entry_001FFAC0 *entry;
    Callback_001FFAC0 *callback;

    state = &fileQueue;
    entry = &fileQueue.entries[index];
    if (entry->callback != NULL) {
        entry->callback(entry, ok);
    }
    if (entry->handle >= 0) {
        if (entry->flags13.set == 0) {
            func_0017FD20(entry->handle);
        }
        entry->handle = -1;
    }
    if (entry->extra != NULL) {
        SzMem_Free(entry->extra);
        entry->extra = NULL;
    }
    if (ok == 0 && entry->flags0F.set != 0 && entry->allocation != NULL) {
        SzMem_Free(entry->allocation);
    }
    if (SzFile_InqRequestX(entry->id, 0) == 0) {
        if ((callback = SzFile_InqGroup(entry->id)) != NULL) {
            if (callback->callback != NULL) {
                callback->callback(entry->id);
            }
            callback->handle = -1;
        }
    }
    if (state->index == index && state->count != 0) {
        if (--state->count > 0) {
            state->index = (state->index + 1) % 256;
        }
    }
    state->flags.active = 0;
}

typedef struct Entry_001FFC50 {
    s32 key;
    s32 value;
} Entry_001FFC50;

extern Entry_001FFC50 D_00322770[];

/* Registers read group `group` with callback `callback` (called when all its reads are done). Returns 0 if the
   table is full. */
s32 SzFile_EntryGroup(s32 group, s32 callback) {
    Entry_001FFC50 *entry;
    s32 remaining;

    entry = D_00322770;
    remaining = 0x40;
    while (remaining--) {
        if (entry->key < 0) {
            entry->key = group;
            entry->value = callback;
            return 1;
        }
        entry++;
    }
    return 0;
}

/* The record of read group `group`, or NULL. */
void SzFile_InqGroup(void *group) {
    SzFile_InqGroupX(group, 0);
}

typedef struct Entry_001FFCC0 {
    s32 value;
    s32 unknown;
} Entry_001FFCC0;

/* The record of read group `group` (-1 for any; `byGroup` compares >> 10), or NULL. */
void *SzFile_InqGroupX(void *group, s32 byGroup) {
    extern struct Entry_001FFC50 D_00322770[];
    s32 shift;
    s32 count;
    Entry_001FFCC0 *entry;

    shift = byGroup ? 10 : 0;
    count = 64;
    entry = (Entry_001FFCC0 *)D_00322770;
    while (count--) {
        if (entry->value >= 0) {
            if ((s32)group < 0 || (s32)group == (entry->value >> shift)) {
                return entry;
            }
        }
        entry++;
    }
    return NULL;
}

typedef struct {
    s8 completed : 1;
    s8 running : 1;
    s8 reserved : 6;
} Flags_001FFD30;

typedef struct {
    u8 pad0[0x6688];
    s32 handle;
    u16 head;
    u16 count;
    Flags_001FFD30 flags;
} Queue_001FFD30;

/* Runs the file read queue once (waiting for a read). */
static inline s32 poll_001FFD30(void) {
    extern Queue_001FFD30 fileQueue;
    extern Flags_001FFD30 D_00322980;
    Queue_001FFD30 *queue = &fileQueue;
    s32 handle;

    if (D_00322980.running == 0) {
        handle = lSzFile_NextRequest();
        queue->handle = handle;
        if (handle < 0) {
            return 0;
        }
    }
    return lSzFile_DoRequestMain(queue->handle);
}

/* Reads file `path` to `address` (`size` bytes or -1 for all) and waits for it. Returns the request, or 0. */
s32 SzFile_Read(s32 path, s32 address, s32 size) {
    extern Queue_001FFD30 fileQueue;
    extern s32 SzFile_ReadRequestParam();
    s32 result;
    Queue_001FFD30 *queue = &fileQueue;

    result = SzFile_ReadRequestParam(0x1400, 0, path, address, size, 0, -1, lSzFile_ReadCB, (s64)0);
    if (result == 0) {
        return 0;
    }
    goto check;
loop:
    poll_001FFD30();
check:
    if (SzFile_InqRequestX(-1, 0) != 0) {
        goto loop;
    }
    return queue->flags.completed ? result : 0;
}

typedef struct {
    s8 completed : 1;
    s8 running : 1;
    s8 reserved : 6;
} Flags_001FFE00;

typedef struct {
    u8 data[0x24];
} Request_001FFE00;

typedef struct {
    u8 pad0[0x4080];
    Request_001FFE00 requests[0x100];
    u8 pad1[0x208];
    s32 handle;
    u16 head;
    u16 count;
    Flags_001FFE00 flags;
} Queue_001FFE00;

/* Queues a read request. */
static inline void *enqueue_001FFE00(s32 arg0, s32 arg1, s32 arg2,
                                     s32 arg3, s32 arg4, s32 arg5) {
    extern Queue_001FFE00 fileQueue;
    Queue_001FFE00 *queue = &fileQueue;
    Request_001FFE00 *request;

    if (arg1 == 0) {
        return NULL;
    }
    if (queue->count >= 0x100) {
        return NULL;
    }
    request = &queue->requests[(queue->head + queue->count) % 0x100];
    if (lSzFile_SetReadRequestParam(request, 0x1400, arg0, (void *)arg1, arg2, arg3, arg4,
                      arg5, (s32)lSzFile_ReadCB, 0) == 0) {
        return NULL;
    }
    queue->count++;
    return request;
}

/* Runs the file read queue once (waiting for a read). */
static inline s32 poll_001FFE00(void) {
    extern Queue_001FFE00 fileQueue;
    extern Flags_001FFE00 D_00322980;
    Queue_001FFE00 *queue = &fileQueue;
    s32 handle;

    if (D_00322980.running == 0) {
        handle = lSzFile_NextRequest();
        queue->handle = handle;
        if (handle < 0) {
            return 0;
        }
    }
    return lSzFile_DoRequestMain(queue->handle);
}

/* Queues a read and waits for it. Returns the request, or NULL. */
void *SzFile_ReadParam(s32 arg0, s32 arg1, s32 arg2, s32 arg3,
                    s32 arg4, s32 arg5) {
    extern Queue_001FFE00 fileQueue;
    Queue_001FFE00 *queue = &fileQueue;
    void *request;

    request = enqueue_001FFE00(arg0, arg1, arg2, arg3, arg4, arg5);
    if (request == NULL) {
        return NULL;
    }
    goto check;
loop:
    poll_001FFE00();
check:
    if (SzFile_InqRequestX(-1, 0) != 0) {
        goto loop;
    }
    return queue->flags.completed ? request : NULL;
}

typedef struct Flags_001FFF60 {
    s8 enabled : 1;
    s8 reserved : 7;
} Flags_001FFF60;

extern Flags_001FFF60 D_00322980;

/* The callback of the blocking reads (nothing to do). */
void lSzFile_ReadCB(s32 request, s64 ok) {
    D_00322980.enabled = (s8)ok;
}

/* The value of setting `name` from the environment (the folder files are read from), or the default folder. */
u8 *SzFile_GetEnv(s32 name) {
    u8 *ret;

    ret = getenv(name);
    if (ret == NULL) {
        ret = D_002D0655;
    }
    return ret;
}

typedef struct Module_001FFFC0 {
    s32 name;
    s32 arg;
} Module_001FFFC0;

typedef struct File_001FFFC0 {
    s32 name;
    s32 unk4;
    s32 sector;
    s32 unkC[3];
    s32 size;
    s32 unk1C;
} File_001FFFC0;

typedef struct Stat_001FFFC0 {
    s32 sector;
    u32 size;
    s32 unk8[10];
} Stat_001FFFC0;

extern char D_002D0657[];
extern Module_001FFFC0 iopModuleList[]; /* original: gSzFile_aIopList */
extern char D_002D0638[];
extern File_001FFFC0 discFileMap[]; /* original: mapFile */
extern char D_002D066F[];


/* Starts the file system: CD, IOP modules, the read queue. */
s32 RhFile_Init(void) {
    extern s32 RhFile_LoadIopModuleWrapper(s32, s32);
    extern s32 sceCdSearchFile(Stat_001FFFC0 *, s32);
    extern u8 fileQueue[];
    u8 *buf = fileQueue;
    s32 i;
    Module_001FFFC0 *mod;
    File_001FFFC0 *file;
    u32 j;
    Stat_001FFFC0 stat;

    func_0017E240(0);
    func_00191778(0);
    while (func_00183A38(D_002D0657) == 0) {
    }
    while (func_00183A00() == 0) {
    }
    func_0017E240(0);
    sceSifInitIopHeap();
    sceSifLoadFileReset();
    func_00191778(0);
    func_00191C50(2);
    sceFsReset();
    while (func_00191A58(0) != 2) {
    }
    for (i = 0, mod = iopModuleList; mod->name != 0; i++) {
        if (RhFile_LoadIopModuleWrapper(mod->name, mod->arg) == 0) {
            return 0;
        }
        mod++;
    }
    if (getenv((s32)D_002D0638) != NULL) {
        file = discFileMap;
        for (j = 0; j < 0x61; j++) {
            while (func_00191A58(0) != 2) {
            }
            if (sceCdSearchFile(&stat, file->name) != 0) {
                file->sector = stat.sector;
                file->size = stat.size >> 11;
            } else {
                file->name = (s32)D_002D066F;
            }
            file++;
        }
    }
    sceCdInitEeCB(0, buf + 0x80, 0x4000);
    func_00190A90(lRhFile_CdCallback);
    return 1;
}

typedef struct Flags_00200170 {
    s8 reserved : 1;
    s8 active : 1;
    s8 remaining : 6;
} Flags_00200170;

typedef struct State_00200170 {
    u8 pad[0x6688];
    s32 current;
    s32 unk668C;
    Flags_00200170 flags;
} State_00200170;

/* The CD's interrupt callback: a sector read has finished (`reason` 1), so the running request ends. */
void lRhFile_CdCallback(s32 reason) {
    extern State_00200170 fileQueue;
    State_00200170 *state = &fileQueue;

    if (reason == 1) {
        if (state->flags.active) {
            if (func_00191EF8() == 0) {
                iFlushCache(0);
                lSzFile_TermRequest(state->current, 1);
            } else {
                state->flags.active = 0;
            }
        }
    }
    asm("sync");
    asm("ei");
}

/* Ends the file system. */
s32 RhFile_Term(void) {
    return 1;
}

/* Loads IOP module `name`. */
void RhFile_LoadIopModuleWrapper(s32 name, s32 argCount) {
    RhFile_LoadIopModuleWrapperEx(name, 0, 0, argCount);
}

/* Loads IOP module `name` (from the disc's module folder) with its arguments, retrying until it loads. */
s32 RhFile_LoadIopModuleWrapperEx(s32 name, s32 argCount, s32 args, s32 fromHost) {
    extern char fileQueue[];
    extern char D_002D0670[];
    extern char D_002D067D[];
    extern s32 func_00183538(char *, s32, s32);
    extern char *func_0019B9D0(char *, const char *);
    char *path = fileQueue;

    lRhFile_StrUpper((s8 *)name);
    if (fromHost != 0) {
        func_0019BDD8(path, D_002D0670);
    } else {
        func_0019BDD8(path, D_002D0670);
    }
    func_0019B9D0(path, (char *)name);
    func_0019B9D0(path, D_002D067D);
    do {

    } while (func_00183538(path, argCount, args) < 0);
    return 1;
}

/* Turns a string into upper case. */
void lRhFile_StrUpper(s8 *str) {
    s8 *var_a0;
    s32 temp_a1;

    var_a0 = str;
    while ((temp_a1 = *var_a0) != 0) {
        if ((temp_a1 >= 0x61) && (temp_a1 < 0x7B)) {
            *var_a0 = temp_a1 - 0x20;
        }
        var_a0 += 1;
    }
}

/* The file system's per-frame work (nothing to do). */
void RhFile_VSyncProcess(void) {

}

typedef struct State_00200360 {
    u8 pad[0x6684];
    char *file;
} State_00200360;

/* Remembers file `name` (in the data folder) as the one RhFile_ReadAndBlock reads. */
s32 RhFile_OpenFile(s32 name) {
    extern State_00200360 fileQueue;
    extern char D_002D0680[];
    extern char D_002D0686[];
    extern u8 *getenv();
    extern void func_0019B648(void *, void *, ...);
    State_00200360 *state = &fileQueue;
    char path[128];
    u8 *directory;

    directory = getenv(D_002D0680);
    if (directory == NULL) {
        directory = D_002D0655;
    }
    func_0019B648(path, D_002D0686, directory, name);
    state->file = SzMem_StrDup(path);
    return 0;
}

typedef struct {
    u8 pad[0x6684];
    s32 file;
    s32 handle;
    u16 head;
    u16 count;
    Flags_001FFE00 flags;
} Queue_002003E0;

/* Reads part of a file and waits for it. */
static inline s32 wait_002003E0(s32 file, s32 arg1, s32 arg2, s32 arg3) {
    extern Queue_002003E0 fileQueue;
    extern s32 SzFile_ReadRequestParam();
    Queue_002003E0 *queue = &fileQueue;
    s32 result;

    result = SzFile_ReadRequestParam(0x1400, 2, file, arg3, arg2, arg1, arg2, lSzFile_ReadCB, (s64)0);
    if (result == 0) {
        return 0;
    }
    goto check;
loop:
    poll_001FFE00();
check:
    if (SzFile_InqRequestX(-1, 0) != 0) {
        goto loop;
    }
    return queue->flags.completed ? result : 0;
}

/* Reads `size` bytes at `offset` of the file RhFile_OpenFile chose into `buffer`, and waits. Returns 1 if it
   worked. */
s32 RhFile_ReadAndBlock(s32 handle, s32 buffer, s32 offset, s32 size) {
    extern Queue_002003E0 fileQueue;
    Queue_002003E0 *queue = &fileQueue;

    if (handle < 0) {
        return 0;
    }
    return wait_002003E0(queue->file, buffer, offset, size) ? 1 : 0;
}

typedef struct State_002004C0 {
    u8 pad[0x6684];
    s32 handle;
} State_002004C0;

/* Forgets the file RhFile_OpenFile chose. */
s32 RhFile_CloseFile(s32 handle) {
    extern State_002004C0 fileQueue;
    State_002004C0 *state = &fileQueue;

    if (handle < 0) {
        return 0;
    }
    if (state->handle != 0) {
        SzMem_Free(state->handle);
        state->handle = 0;
    }
    return 1;
}

typedef struct {
    u8 data[0x24];
} Request_00200510;

typedef struct {
    u8 pad0[0x4080];
    Request_00200510 requests[0x100];
    u8 pad1[0x200];
    void (*callback)(void);
    u8 pad2[0x8];
    u16 head;
    u16 count;
} Queue_00200510;

/* Queues a read of a named file. */
static inline Request_00200510 *enqueue_00200510(s32 arg1, s32 arg2, s32 arg3, u8 *buf, s32 arg5, s32 arg6) {
    extern u8 fileQueue[];
    Queue_00200510 *queue = (Queue_00200510 *)fileQueue;
    Request_00200510 *slot;
    s32 count;
    s32 idx;
    s32 temp;

    count = queue->count;
    if (count >= 0x100) {
        return NULL;
    }
    temp = queue->head + count;
    idx = temp & 0xFF;
    if (temp < 0) {
        if (idx != 0) {
            idx -= 0x100;
        }
    }
    slot = &queue->requests[idx];
    if (lSzFile_SetReadRequestParam(slot, 0x1400, (arg6 != 0) ? 8 : 7, buf, arg3, arg2, arg1, arg2,
                      (s32)lRhFile_ReadCB, arg5) == 0) {
        return NULL;
    }
    queue->count++;
    return slot;
}

/* Queues a read of file `name` (in the data folder) into `buffer`, calling `callback` when done. */
s32 RhFile_ReadAndCallbackByFileName(s32 name, s32 buffer, s32 offset, s32 size, void (*callback)(void), s32 callbackArg, s32 flags) {
    extern Queue_00200510 fileQueue;
    extern u8 D_002D0680[];
    extern u8 D_002D0686[];
    extern u8 D_002D0655[];
    extern void func_0019B648();
    Queue_00200510 *queue = &fileQueue;
    u8 buf[0x80];
    u8 *text;
    Request_00200510 *slot;

    if (name == 0) {
        return 0;
    }
    text = getenv((s32)D_002D0680);
    if (text == NULL) {
        text = D_002D0655;
    }
    func_0019B648(buf, D_002D0686, (s32)text, name);
    queue->callback = callback;
    slot = enqueue_00200510(buffer, offset, size, buf, callbackArg, flags);
    return (slot != NULL) ? 1 : 0;
}

typedef struct CallbackTable_00200680 {
    u8 pad[0x6680];
    void (*callback)(s32, void *);
} CallbackTable_00200680;

extern CallbackTable_00200680 fileQueue; /* original: gSzFile_fl */
extern s32 D_00322970;

/* A named-file read has finished: calls the caller's callback. */
void lRhFile_ReadCB(void *request) {
    CallbackTable_00200680 *table = &fileQueue;

    if (D_00322970 != 0) {
        table->callback(*(s32 *)((u8 *)request + 0x1C), table);
    }
}

/* Whether file `name` exists in the data folder. */
s32 RhFile_ExistFile(s32 name) {
    extern char D_002D0680[];
    extern char D_002D0686[];
    extern u8 *getenv();
    extern void func_0019B648(void *, void *, ...);
    char path[128];
    char full[128];
    u8 *directory;
    s32 handle;

    if (name == 0) {
        return 0;
    }
    directory = getenv(D_002D0680);
    if (directory == NULL) {
        directory = D_002D0655;
    }
    func_0019B648(path, D_002D0686, directory, name);
    goto check;
loop:
    poll_001FFE00();
check:
    if (SzFile_InqRequestX(-1, 0) != 0) {
        goto loop;
    }
    lSzFile_StrNormalize((s8 *)path);
    func_0019B648(full, D_002D0648, D_002D064D, path);
    handle = func_0017FA98(full, 1);
    if (handle < 0) {
        return 0;
    }
    func_0017FD20(handle);
    return 1;
}

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

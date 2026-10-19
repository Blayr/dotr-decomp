/* File reads from the disc (SzFile_* and RhFile_*, one original file). */

#include "common.h"

typedef struct Flags_001FEB80 {
    s8 bit0 : 1;
    s8 bit1 : 1;
    s8 bits2_7 : 6;
} Flags_001FEB80;

typedef struct State_001FEB80 {
    u8 pad[0x6688];
    s32 field_6688;
    s16 field_668C;
    s16 field_668E;
    Flags_001FEB80 field_6690;
} State_001FEB80;

typedef struct Entry36_001FEB80 {
    s32 field0;
    u8 pad[0x20];
} Entry36_001FEB80;

typedef struct Entry8_001FEB80 {
    s32 field0;
    s32 field4;
} Entry8_001FEB80;

extern State_001FEB80 fileQueue; /* original: gSzFile_fl */
extern Entry36_001FEB80 D_00320370[];
extern Entry8_001FEB80 D_00322770[];

/* Clears the file read queue. */
void SzFile_Init(void) {
    State_001FEB80 *state;
    Entry8_001FEB80 *small;
    Entry36_001FEB80 *large;
    s32 count;

    state = &fileQueue;
    large = D_00320370;
    small = D_00322770;
    count = 0x100;
    RhMem_FillMemory((s8 *)&fileQueue, 0, 0x66A0);
    while (count--) {
        large->field0 = -1;
        large++;
    }
    count = 0x40;
    while (count--) {
        small->field0 = -1;
        small++;
    }
    state->field_668C = 0;
    state->field_668E = 0;
    state->field_6688 = -1;
    state->field_6690.bit1 = 0;
}

/* Queues a read of file `path` to `address` (`size` bytes or -1 for all), calling `callback(request, ok)` with
   `callbackArg` when done. */
void SzFile_ReadRequest(s32 owner, s32 path, s32 address, s32 size, s32 callback, s64 callbackArg) {
    SzFile_ReadRequestParam(owner, 0, path, address, size, 0, -1, callback, callbackArg);
}

typedef struct Request_001FECB0 {
    u8 data[0x24];
} Request_001FECB0;

typedef struct Queue_001FECB0 {
    u8 pad0[0x4080];
    Request_001FECB0 requests[0x100];
    u8 pad1[0x20C];
    u16 head;
    u16 count;
} Queue_001FECB0;

/* Queues a read of `length` bytes from `offset` of file `path` (a name or a disc file number | 0x80000000) to
   `address`. Returns the request, or 0. */
s32 SzFile_ReadRequestParam(s32 owner, s32 type, s32 path, s32 address, s32 size, s32 offset, s32 length, s32 callback, s64 callbackArg) {
    Queue_001FECB0 *queue = (Queue_001FECB0 *)&fileQueue;
    Request_001FECB0 *request;

    if (path == 0) {
        return 0;
    }
    if (queue->count >= 0x100) {
        return 0;
    }
    request = &queue->requests[(queue->head + queue->count) % 0x100];
    if (lSzFile_SetReadRequestParam(request, owner, type, (void *)path, address, size, offset, length, callback, callbackArg) == 0) {
        return 0;
    }
    queue->count++;
    return (s32)request;
}

extern char *discFileMap[]; /* original: mapFile */
extern s64 D_00293098[];
extern s32 D_002930A8[];
extern char D_002D0638[];
extern char D_002D063D[];

typedef struct Record_001FEDA0 {
    s32 id;
    s16 type;
    s16 count;
    u32 size : 31;
    s32 sizeFlag : 1;
    u32 offset : 31;
    s32 offsetFlag : 1;
    u32 limit : 31;
    s32 discFlag : 1;
    s32 mode;
    s32 arg8;
    s32 arg9;
    char *file;
} Record_001FEDA0;

/* Fills a read request record. */
static inline void initialize_001FEDA0(Record_001FEDA0 *record,
                                      s32 type, s32 count, s32 mode,
                                      s32 size, s32 offset, s32 limit,
                                      s32 arg8, s32 arg9) {
    record->type = type;
    record->count = count > 0 ? count : 0;
    record->size = size;
    record->offset = offset;
    record->limit = limit;
    record->sizeFlag = 0;
    record->offsetFlag = 0;
    record->mode = mode;
    record->arg8 = arg8;
    record->arg9 = arg9;
}

/* Fills a read request: finds the file (a card picture by number, a disc file, or a name), checks the sector
   alignment. */
s32 lSzFile_SetReadRequestParam(void *request, s32 owner, s32 type, void *fileName,
                 s32 address, s32 size, s32 offset, s32 readLength,
                 s32 callback, s32 callbackArg) {
    char buffer[128];
    Record_001FEDA0 *record = request;

    if (record == NULL) {
        return 0;
    }
    if (fileName == 0) {
        return 0;
    }
    if (getenv((s32)D_002D0638) != NULL) {
        if (!((u32)fileName & 0x80000000)) {
            s32 name;
            u32 i;
            s32 length;
            char **entry;
            s32 digit1;
            s32 digit2;
            s32 digit3;

            func_0019BDD8(buffer, (char *)fileName);
            if ((name = (s32)func_0019C478(buffer, '/')) != NULL ||
                (name = (s32)func_0019C478(buffer, '\\')) != NULL) {
                length = func_0019BEF0((char *)(name + 1));
                if (length >= 8 && owner == 0x1400 &&
                    (((char *)name)[1] == 'M' || ((char *)name)[1] == 'm') &&
                    (digit1 = ((char *)name)[2]) >= '0' && digit1 <= '9' &&
                    (digit2 = ((char *)name)[3]) >= '0' && digit2 <= '9' &&
                    (digit3 = ((char *)name)[4]) >= '0' && digit3 <= '9' &&
                    ((char *)name)[5] == '.' &&
                    (((char *)name)[6] == 'G' || ((char *)name)[6] == 'g') &&
                    (((char *)name)[7] == 'R' || ((char *)name)[7] == 'r') &&
                    (((char *)name)[8] == 'P' || ((char *)name)[8] == 'p')) {
                    offset += SzDuel_Xax2New(digit3 - '0' +
                                         ((digit1 - '0') * 100 +
                                          (digit2 - '0') * 10)) * 0x80800;
                    name = (s32)D_002D063D;
                    length = func_0019BEF0((char *)(name + 1));
                }
                entry = discFileMap;
                i = 0;
                do {
                    char *path = func_0019C478(*entry, '\\');
                    if (path != NULL && strncasecmp((char *)(name + 1), path + 1, length) == 0) {
                        fileName = (void *)(D_00293098[i * 4] | 0x80000000);
                        if (size < 0) {
                            size = D_002930A8[i * 8] << 11;
                        }
                        break;
                    }
                    i++;
                    entry += 8;
                } while (i < 97U);
            }
        }
    }
    if ((u32)fileName & 0x80000000) {
        if (size < 0) {
            return 0;
        }
        if (size > 0 && size % 2048 != 0) {
            return 0;
        }
        if (offset % 2048 != 0) {
            return 0;
        }
        if (readLength > 0 && readLength % 2048 != 0) {
            return 0;
        }
        record->file = NULL;
        record->discFlag = 1;
        record->id = (u32)fileName & 0x7FFFFFFF;
    } else {
        char *file = SzMem_StrDup((char *)fileName);
        record->file = file;
        if (file == NULL) {
            return 0;
        }
        lSzFile_StrNormalize((s8 *)record->file);
        record->discFlag = 0;
        record->id = 0;
    }
    initialize_001FEDA0(record, owner, type, address, size, offset, readLength, callback, callbackArg);
    return 1;
}

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

extern Record_001FF360 D_00320370_2[];

/* The first queued read of owner `owner` (-1 for any; `byGroup` compares owner >> 10), or 0. */
s32 SzFile_InqRequestX(s32 owner, s32 byGroup) {
    Record_001FF360 *record;
    s32 remaining;
    s32 shift;

    shift = byGroup ? 10 : 0;
    record = D_00320370_2;
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

    start = *(s32 *)T1_COUNT_ADDR;
    do {
        if (SzFile_DoRequestS() == 0) {
            break;
        }
    } while (*(s32 *)T1_COUNT_ADDR - start <= 0x40);
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
    extern State_001FF420 fileQueue_2;
    extern Flags_001FF420 D_00322980;
    State_001FF420 *state = &fileQueue_2;
    s32 nextRequest;

    if (D_00322980.active == 0) {
        nextRequest = lSzFile_NextRequest();
        state->current = nextRequest;
        if (nextRequest < 0) {
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
    extern State_001FF480 fileQueue_2;
    extern s32 func_0019B648();
    char path[0x88];
    s32 status;
    Progress_001FF480 progress;
    State_001FF480 *state;
    Entry_001FF480 *entry;
    s32 sector;
    s32 count;

    state = &fileQueue_2;
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
    extern Queue_001FF9C0 fileQueue_2;
    Queue_001FF9C0 *queue = &fileQueue_2;
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
    extern State_001FFAC0 fileQueue_2;
    extern void *SzFile_InqGroup();
    extern void SzMem_Free();
    State_001FFAC0 *state;
    Entry_001FFAC0 *entry;
    Callback_001FFAC0 *callback;

    state = &fileQueue_2;
    entry = &fileQueue_2.entries[index];
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

extern Entry_001FFC50 D_00322770_2[];

/* Registers read group `group` with callback `callback` (called when all its reads are done). Returns 0 if the
   table is full. */
s32 SzFile_EntryGroup(s32 group, s32 callback) {
    Entry_001FFC50 *entry;
    s32 remaining;

    entry = D_00322770_2;
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

/* The record of read group `groupId`, or NULL (SzFile_InqGroupX's result is left in v0: declared void for the
   match). */
void SzFile_InqGroup(void *groupId) {
    SzFile_InqGroupX(groupId, 0);
}

typedef struct Entry_001FFCC0 {
    s32 value;
    s32 unknown;
} Entry_001FFCC0;

/* The record of read group `group` (-1 for any; `byGroup` compares >> 10), or NULL. */
void *SzFile_InqGroupX(void *group, s32 byGroup) {
    extern struct Entry_001FFC50 D_00322770_2[];
    s32 shift;
    s32 count;
    Entry_001FFCC0 *entry;

    shift = byGroup ? 10 : 0;
    count = 64;
    entry = (Entry_001FFCC0 *)D_00322770_2;
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
    extern Queue_001FFD30 fileQueue_2;
    extern Flags_001FFD30 D_00322980;
    Queue_001FFD30 *queue = &fileQueue_2;
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
    extern Queue_001FFD30 fileQueue_2;
    extern s32 SzFile_ReadRequestParam();
    s32 result;
    Queue_001FFD30 *queue = &fileQueue_2;

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
    extern Queue_001FFE00 fileQueue_2;
    Queue_001FFE00 *queue = &fileQueue_2;
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
    extern Queue_001FFE00 fileQueue_2;
    extern Flags_001FFE00 D_00322980;
    Queue_001FFE00 *queue = &fileQueue_2;
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
    extern Queue_001FFE00 fileQueue_2;
    Queue_001FFE00 *queue = &fileQueue_2;
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
extern File_001FFFC0 discFileMap_2[]; /* original: mapFile */
extern char D_002D066F[];

/* Starts the file system: CD, IOP modules, the read queue. */
s32 RhFile_Init(void) {
    extern s32 RhFile_LoadIopModuleWrapper(s32, s32);
    extern s32 sceCdSearchFile(Stat_001FFFC0 *, s32);
    extern u8 fileQueue_2[];
    u8 *buf = fileQueue_2;
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
        file = discFileMap_2;
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
    extern State_00200170 fileQueue_2;
    State_00200170 *state = &fileQueue_2;

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
    extern char fileQueue_2[];
    extern char D_002D0670[];
    extern char D_002D067D[];
    extern s32 func_00183538(char *, s32, s32);
    extern char *func_0019B9D0(char *, const char *);
    char *path = fileQueue_2;

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
    extern State_00200360 fileQueue_2;
    extern char D_002D0680[];
    extern char D_002D0686[];
    extern u8 *getenv();
    extern void func_0019B648(void *, void *, ...);
    State_00200360 *state = &fileQueue_2;
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
    extern Queue_002003E0 fileQueue_2;
    extern s32 SzFile_ReadRequestParam();
    Queue_002003E0 *queue = &fileQueue_2;
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
    extern Queue_002003E0 fileQueue_2;
    Queue_002003E0 *queue = &fileQueue_2;

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
    extern State_002004C0 fileQueue_2;
    State_002004C0 *state = &fileQueue_2;

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
    extern u8 fileQueue_2[];
    Queue_00200510 *queue = (Queue_00200510 *)fileQueue_2;
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
    extern Queue_00200510 fileQueue_2;
    extern u8 D_002D0680[];
    extern u8 D_002D0686[];
    extern u8 D_002D0655[];
    extern void func_0019B648();
    Queue_00200510 *queue = &fileQueue_2;
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

extern CallbackTable_00200680 fileQueue_2; /* original: gSzFile_fl */
extern s32 D_00322970;

/* A named-file read has finished: calls the caller's callback. */
void lRhFile_ReadCB(void *request) {
    CallbackTable_00200680 *table = &fileQueue_2;

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

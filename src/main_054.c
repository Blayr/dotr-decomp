#include "common.h"

static s32 func_001FF9C0(void);

void func_001FF250(s8 *p) {
    s32 network;
    s32 first;
    s32 c;

    first = p[0];
    network = 0;
    if ((first == '/' && p[1] == '/') ||
        (first == '\\' && p[1] == '\\')) {
        network = 1;
    }
    func_00200300(p);
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

s32 func_001FF300(void) {
    s32 var_s0;

    var_s0 = 0;
loop_1:
    if (func_001FF360(var_s0, 1) != 0) {
        return 1;
    }
    var_s0 += 1;
    if (var_s0 >= 5) {
        return 0;
    }
    goto loop_1;
}

s32 func_001FF350(s32 arg0) {
    return func_001FF360(arg0, 0);
}

typedef struct Record_001FF360 {
    s32 status;
    s16 id;
    u8 padding[0x1E];
} Record_001FF360;

extern Record_001FF360 D_00320370[];

s32 func_001FF360(s32 arg0, s32 arg1) {
    Record_001FF360 *record;
    s32 remaining;
    s32 shift;

    shift = arg1 ? 10 : 0;
    record = D_00320370;
    for (remaining = 0x100; remaining--; record++) {
        if (record->status >= 0 &&
            (arg0 < 0 || arg0 == (record->id >> shift))) {
            return (s32) record;
        }
    }
    record = NULL;
    return (s32) record;
}

void func_001FF3D0(void) {
    s32 start;

    start = *(s32 *)0x10000800;
    do {
        if (func_001FF420() == 0) {
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


s32 func_001FF420(void) {
    extern State_001FF420 D_0031C2F0;
    extern Flags_001FF420 D_00322980;
    State_001FF420 *state = &D_0031C2F0;
    s32 temp_v0;

    if (D_00322980.active == 0) {
        temp_v0 = func_001FF9C0();
        state->current = temp_v0;
        if (temp_v0 < 0) {
            return 0;
        }
    }
    return func_001FF480(state->current);
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

s32 func_001FF480(s32 arg0) {
    extern State_001FF480 D_0031C2F0;
    extern s32 func_0019B648();
    char path[0x88];
    s32 status;
    Progress_001FF480 progress;
    State_001FF480 *state;
    Entry_001FF480 *entry;
    s32 sector;
    s32 count;

    state = &D_0031C2F0;
    if (arg0 < 0) {
        return 0;
    }
    entry = &state->entries[arg0];
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
            if ((entry->buffer = func_00217B40(entry->size.value)) == 0) {
                func_001FFAC0(arg0, 0);
                return 0;
            }
            entry->offset.flag = 1;
        }
        if (entry->length.value < 0) {
            entry->length.value = entry->size.value - entry->offset.value;
        }
        sector = entry->handle + (entry->offset.value >> 11);
        count = entry->length.value >> 11;
        func_0017BB60(0);
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
                    func_001FFAC0(arg0, 0);
                    return 0;
                }
                if ((entry->size.value = func_0017FEA0(entry->handle, 0, 2)) < 0) {
                    func_001FFAC0(arg0, 0);
                    return 0;
                }
                func_0017FD20(entry->handle);
            }
            entry->handle = func_0017FA98(path, 0x8001);
            if (entry->handle < 0) {
                func_001FFAC0(arg0, 0);
                return 0;
            }
            if (entry->size.value != 0) {
                entry->size.value = (entry->size.value + 15) & ~15;
                if (entry->buffer == 0) {
                    if ((entry->buffer = func_00217B40(entry->size.value)) == 0) {
                        func_001FFAC0(arg0, 0);
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
                    func_001FFAC0(arg0, 0);
                    return 0;
                }
                do {
                    if (func_00180608(entry->handle, 1, &status) < 0) {
                        func_001FFAC0(arg0, 0);
                        return 0;
                    }
                } while (status != 0);
            }
            func_0017BB60(0);
            if (func_001800D8(entry->handle, entry->buffer, entry->length.value) < 0) {
                func_001FFAC0(arg0, 0);
                return 0;
            }
            entry->size.flag = 1;
        }
        if (func_00180608(entry->handle, 1, &status) < 0) {
            func_001FFAC0(arg0, 0);
            return 0;
        }
        if (status == 0) {
            func_0017BB60(0);
            func_001FFAC0(arg0, 1);
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

static s32 func_001FF9C0(void) {
    extern Queue_001FF9C0 D_0031C2F0;
    Queue_001FF9C0 *queue = &D_0031C2F0;
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


void func_001FFAC0(s32 arg0, s32 arg1) {
    extern State_001FFAC0 D_0031C2F0;
    extern void *func_001FFCB0();
    extern void func_00217B50();
    State_001FFAC0 *state;
    Entry_001FFAC0 *entry;
    Callback_001FFAC0 *callback;

    state = &D_0031C2F0;
    entry = &D_0031C2F0.entries[arg0];
    if (entry->callback != NULL) {
        entry->callback(entry, arg1);
    }
    if (entry->handle >= 0) {
        if (entry->flags13.set == 0) {
            func_0017FD20(entry->handle);
        }
        entry->handle = -1;
    }
    if (entry->extra != NULL) {
        func_00217B50(entry->extra);
        entry->extra = NULL;
    }
    if (arg1 == 0 && entry->flags0F.set != 0 && entry->allocation != NULL) {
        func_00217B50(entry->allocation);
    }
    if (func_001FF360(entry->id, 0) == 0) {
        if ((callback = func_001FFCB0(entry->id)) != NULL) {
            if (callback->callback != NULL) {
                callback->callback(entry->id);
            }
            callback->handle = -1;
        }
    }
    if (state->index == arg0 && state->count != 0) {
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

s32 func_001FFC50(s32 arg0, s32 arg1) {
    Entry_001FFC50 *entry;
    s32 remaining;

    entry = D_00322770;
    remaining = 0x40;
    while (remaining--) {
        if (entry->key < 0) {
            entry->key = arg0;
            entry->value = arg1;
            return 1;
        }
        entry++;
    }
    return 0;
}

void func_001FFCB0(void *arg0) {
    func_001FFCC0(arg0, 0);
}

typedef struct Entry_001FFCC0 {
    s32 value;
    s32 unknown;
} Entry_001FFCC0;

void *func_001FFCC0(void *arg0, s32 arg1) {
    extern struct Entry_001FFC50 D_00322770[];
    s32 shift;
    s32 count;
    Entry_001FFCC0 *entry;

    shift = arg1 ? 10 : 0;
    count = 64;
    entry = (Entry_001FFCC0 *)D_00322770;
    while (count--) {
        if (entry->value >= 0) {
            if ((s32)arg0 < 0 || (s32)arg0 == (entry->value >> shift)) {
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

static inline s32 poll_001FFD30(void) {
    extern Queue_001FFD30 D_0031C2F0;
    extern Flags_001FFD30 D_00322980;
    Queue_001FFD30 *queue = &D_0031C2F0;
    s32 handle;

    if (D_00322980.running == 0) {
        handle = func_001FF9C0();
        queue->handle = handle;
        if (handle < 0) {
            return 0;
        }
    }
    return func_001FF480(queue->handle);
}

s32 func_001FFD30(s32 arg0, s32 arg1, s32 arg2) {
    extern Queue_001FFD30 D_0031C2F0;
    extern s32 func_001FECB0();
    s32 result;
    Queue_001FFD30 *queue = &D_0031C2F0;

    result = func_001FECB0(0x1400, 0, arg0, arg1, arg2, 0, -1, func_001FFF60, (s64)0);
    if (result == 0) {
        return 0;
    }
    goto check;
loop:
    poll_001FFD30();
check:
    if (func_001FF360(-1, 0) != 0) {
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

static inline void *enqueue_001FFE00(s32 arg0, s32 arg1, s32 arg2,
                                     s32 arg3, s32 arg4, s32 arg5) {
    extern Queue_001FFE00 D_0031C2F0;
    Queue_001FFE00 *queue = &D_0031C2F0;
    Request_001FFE00 *request;

    if (arg1 == 0) {
        return NULL;
    }
    if (queue->count >= 0x100) {
        return NULL;
    }
    request = &queue->requests[(queue->head + queue->count) % 0x100];
    if (func_001FEDA0(request, 0x1400, arg0, (void *)arg1, arg2, arg3, arg4,
                      arg5, (s32)func_001FFF60, 0) == 0) {
        return NULL;
    }
    queue->count++;
    return request;
}

static inline s32 poll_001FFE00(void) {
    extern Queue_001FFE00 D_0031C2F0;
    extern Flags_001FFE00 D_00322980;
    Queue_001FFE00 *queue = &D_0031C2F0;
    s32 handle;

    if (D_00322980.running == 0) {
        handle = func_001FF9C0();
        queue->handle = handle;
        if (handle < 0) {
            return 0;
        }
    }
    return func_001FF480(queue->handle);
}

void *func_001FFE00(s32 arg0, s32 arg1, s32 arg2, s32 arg3,
                    s32 arg4, s32 arg5) {
    extern Queue_001FFE00 D_0031C2F0;
    Queue_001FFE00 *queue = &D_0031C2F0;
    void *request;

    request = enqueue_001FFE00(arg0, arg1, arg2, arg3, arg4, arg5);
    if (request == NULL) {
        return NULL;
    }
    goto check;
loop:
    poll_001FFE00();
check:
    if (func_001FF360(-1, 0) != 0) {
        goto loop;
    }
    return queue->flags.completed ? request : NULL;
}

typedef struct Flags_001FFF60 {
    s8 enabled : 1;
    s8 reserved : 7;
} Flags_001FFF60;

extern Flags_001FFF60 D_00322980;

void func_001FFF60(s32 arg0, s64 arg1) {
    D_00322980.enabled = (s8)arg1;
}

u8 *func_001FFF90(s32 unused0) {
    u8 *ret;

    ret = func_00197548(unused0);
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
extern Module_001FFFC0 D_002CFCE0[];
extern char D_002D0638[];
extern File_001FFFC0 D_00293090[];
extern char D_002D066F[];

void func_0017E240(s32);

s32 func_001FFFC0(void) {
    extern s32 func_00200220(s32, s32);
    extern s32 func_00190FF0(Stat_001FFFC0 *, s32);
    extern u8 D_0031C2F0[];
    u8 *buf = D_0031C2F0;
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
    func_00182838();
    func_00182CC8();
    func_00191778(0);
    func_00191C50(2);
    func_0017FA60();
    while (func_00191A58(0) != 2) {
    }
    for (i = 0, mod = D_002CFCE0; mod->name != 0; i++) {
        if (func_00200220(mod->name, mod->arg) == 0) {
            return 0;
        }
        mod++;
    }
    if (func_00197548((s32)D_002D0638) != NULL) {
        file = D_00293090;
        for (j = 0; j < 0x61; j++) {
            while (func_00191A58(0) != 2) {
            }
            if (func_00190FF0(&stat, file->name) != 0) {
                file->sector = stat.sector;
                file->size = stat.size >> 11;
            } else {
                file->name = (s32)D_002D066F;
            }
            file++;
        }
    }
    func_00190C48(0, buf + 0x80, 0x4000);
    func_00190A90(func_00200170);
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

void func_00200170(s32 arg0) {
    extern State_00200170 D_0031C2F0;
    State_00200170 *state = &D_0031C2F0;

    if (arg0 == 1) {
        if (state->flags.active) {
            if (func_00191EF8() == 0) {
                func_0017BB90(0);
                func_001FFAC0(state->current, 1);
            } else {
                state->flags.active = 0;
            }
        }
    }
    asm("sync");
    asm("ei");
}

s32 func_00200210(void) {
    return 1;
}

void func_00200220(s32 arg0, s32 arg1) {
    func_00200230(arg0, 0, 0, arg1);
}

s32 func_00200230(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    extern char D_0031C2F0[];
    extern char D_002D0670[];
    extern char D_002D067D[];
    extern s32 func_00183538(char *, s32, s32);
    extern char *func_0019B9D0(char *, const char *);
    char *path = D_0031C2F0;

    func_00200300((s8 *)arg0);
    if (arg3 != 0) {
        func_0019BDD8(path, D_002D0670);
    } else {
        func_0019BDD8(path, D_002D0670);
    }
    func_0019B9D0(path, (char *)arg0);
    func_0019B9D0(path, D_002D067D);
    do {

    } while (func_00183538(path, arg1, arg2) < 0);
    return 1;
}

void func_00200300(s8 *arg0) {
    s8 *var_a0;
    s32 temp_a1;

    var_a0 = arg0;
    while ((temp_a1 = *var_a0) != 0) {
        if ((temp_a1 >= 0x61) && (temp_a1 < 0x7B)) {
            *var_a0 = temp_a1 - 0x20;
        }
        var_a0 += 1;
    }
}

void func_00200350(void) {

}

typedef struct State_00200360 {
    u8 pad[0x6684];
    char *file;
} State_00200360;

s32 func_00200360(s32 arg0) {
    extern State_00200360 D_0031C2F0;
    extern char D_002D0680[];
    extern char D_002D0686[];
    extern u8 *func_00197548();
    extern void func_0019B648(void *, void *, ...);
    State_00200360 *state = &D_0031C2F0;
    char path[128];
    u8 *directory;

    directory = func_00197548(D_002D0680);
    if (directory == NULL) {
        directory = D_002D0655;
    }
    func_0019B648(path, D_002D0686, directory, arg0);
    state->file = func_00217B60(path);
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

static inline s32 wait_002003E0(s32 file, s32 arg1, s32 arg2, s32 arg3) {
    extern Queue_002003E0 D_0031C2F0;
    extern s32 func_001FECB0();
    Queue_002003E0 *queue = &D_0031C2F0;
    s32 result;

    result = func_001FECB0(0x1400, 2, file, arg3, arg2, arg1, arg2, func_001FFF60, (s64)0);
    if (result == 0) {
        return 0;
    }
    goto check;
loop:
    poll_001FFE00();
check:
    if (func_001FF360(-1, 0) != 0) {
        goto loop;
    }
    return queue->flags.completed ? result : 0;
}

s32 func_002003E0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    extern Queue_002003E0 D_0031C2F0;
    Queue_002003E0 *queue = &D_0031C2F0;

    if (arg0 < 0) {
        return 0;
    }
    return wait_002003E0(queue->file, arg1, arg2, arg3) ? 1 : 0;
}

typedef struct State_002004C0 {
    u8 pad[0x6684];
    s32 handle;
} State_002004C0;

s32 func_002004C0(s32 arg0) {
    extern State_002004C0 D_0031C2F0;
    State_002004C0 *state = &D_0031C2F0;

    if (arg0 < 0) {
        return 0;
    }
    if (state->handle != 0) {
        func_00217B50(state->handle);
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

static inline Request_00200510 *enqueue_00200510(s32 arg1, s32 arg2, s32 arg3, u8 *buf, s32 arg5, s32 arg6) {
    extern u8 D_0031C2F0[];
    Queue_00200510 *queue = (Queue_00200510 *)D_0031C2F0;
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
    if (func_001FEDA0(slot, 0x1400, (arg6 != 0) ? 8 : 7, buf, arg3, arg2, arg1, arg2,
                      (s32)func_00200680, arg5) == 0) {
        return NULL;
    }
    queue->count++;
    return slot;
}

s32 func_00200510(s32 arg0, s32 arg1, s32 arg2, s32 arg3, void (*arg4)(void), s32 arg5, s32 arg6) {
    extern Queue_00200510 D_0031C2F0;
    extern u8 D_002D0680[];
    extern u8 D_002D0686[];
    extern u8 D_002D0655[];
    extern void func_0019B648();
    Queue_00200510 *queue = &D_0031C2F0;
    u8 buf[0x80];
    u8 *text;
    Request_00200510 *slot;

    if (arg0 == 0) {
        return 0;
    }
    text = func_00197548((s32)D_002D0680);
    if (text == NULL) {
        text = D_002D0655;
    }
    func_0019B648(buf, D_002D0686, (s32)text, arg0);
    queue->callback = arg4;
    slot = enqueue_00200510(arg1, arg2, arg3, buf, arg5, arg6);
    return (slot != NULL) ? 1 : 0;
}

typedef struct CallbackTable_00200680 {
    u8 pad[0x6680];
    void (*callback)(s32, void *);
} CallbackTable_00200680;

extern CallbackTable_00200680 D_0031C2F0;
extern s32 D_00322970;

void func_00200680(void *arg0) {
    CallbackTable_00200680 *table = &D_0031C2F0;

    if (D_00322970 != 0) {
        table->callback(*(s32 *)((u8 *)arg0 + 0x1C), table);
    }
}

s32 func_002006C0(s32 arg0) {
    extern char D_002D0680[];
    extern char D_002D0686[];
    extern u8 *func_00197548();
    extern void func_0019B648(void *, void *, ...);
    char path[128];
    char full[128];
    u8 *directory;
    s32 handle;

    if (arg0 == 0) {
        return 0;
    }
    directory = func_00197548(D_002D0680);
    if (directory == NULL) {
        directory = D_002D0655;
    }
    func_0019B648(path, D_002D0686, directory, arg0);
    goto check;
loop:
    poll_001FFE00();
check:
    if (func_001FF360(-1, 0) != 0) {
        goto loop;
    }
    func_001FF250((s8 *)path);
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

extern struct Entry_002008A0 D_003229A0[];

void func_002007D0(void) {
    Record_002007D0 *record;
    s32 i;

    record = (Record_002007D0 *)D_003229A0;
    func_0020B3C0((s8 *)&D_00322990, 0, 6);
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

extern Entry_002008A0 D_003229A0[];

void *func_002008A0(s32 arg0, s32 arg1) {
    Entry_002008A0 *entry;
    s32 i;

    entry = D_003229A0;
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

static inline Entry_002008A0 *find_00200930(s32 arg0, s32 arg1) {
    Entry_002008A0 *entry;
    s32 i;

    entry = D_003229A0;
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

void *func_00200930(s32 arg0, s32 arg1) {
    Entry_002008A0 *entry = find_00200930(arg0, arg1);

    if (entry != NULL && !(entry->occupied & 0x80000000)) {
        return entry;
    }
    return NULL;
}

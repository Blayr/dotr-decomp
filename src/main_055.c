#include "common.h"

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
extern char D_002D074B[];
extern char D_002D0760[];

/* A texture item by group and index. */
static inline Entry_00202220 *find_00202220(s32 group, s32 index) {
    extern Entry_00202220 textureItems[];
    Entry_00202220 *entry = textureItems;
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
    extern Entry_00202220 textureItems[];
    Entry_00202220 *entry = textureItems;
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
    extern Slot_00202810 textureItems[];
    Slot_00202810 *entry;
    s32 i;

    entry = textureItems;
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
    extern Slot_002029B0 textureItems[];
    Slot_002029B0 *entry;
    s32 i;
    s32 result;

    entry = textureItems;
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
    extern Record_00202B00 textureItems[];
    Record_00202B00 *entry;
    s32 start;
    s32 i;
    s32 size;

    entry = textureItems;
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
    extern Entry_00202CB0 textureItems[];
    Entry_00202CB0 *entry;
    s32 i;
    s32 result;

    entry = textureItems;
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

extern Entry_00202D60 textureItems[]; /* original: gSzText_aItem */

/* Drops the request for texture item `id` of category `category`. */
s32 SzText_FreeRequest(s32 category, s32 id) {
    Entry_00202D60 *var_t0;
    s32 var_t1;
    s32 var_v0;

    var_t0 = textureItems;
    var_v0 = 0;
    var_t1 = 0;
    do {
        if (var_t0->data != 0 && var_t0->active != 0) {
            if ((category < 0 || var_t0->category == category) &&
                (id < 0 || var_t0->id == id)) {
                var_v0 = 1;
                var_t0->active = 0;
            }
        }
        var_t1 += 1;
        var_t0++;
    } while (var_t1 < 0x400);
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


typedef struct {
    s8 low : 4;
    s8 high : 4;
} Flags_002031F0;

typedef struct {
    s8 type;
    Flags_002031F0 mode;
    u8 pad[0x5A];
} Port_002031F0;

extern u8 D_00325AC0;
extern Port_002031F0 D_00325C75[];

/* Starts the two pads. */
void SzPad_Init(void) {
    RhMem_FillMemory((s8 *) padStates, 0, 0x2C0);
    D_00325C75[-1].type = 0xA;
    D_00325C75[0].type = 0xA;
    D_00325C75[-1].mode.low = 4;
    D_00325C75[0].mode.low = 4;
    scePadInit(0);
    scePadPortOpen(0, 0, padStates);
    scePadPortOpen(1, 0, &D_00325AC0);
}

/* Ends the pads. */
void SzPad_Term(void) {
    RhMem_FillMemory4(padStates, 0, 0xB0);
}

extern s8 D_00325C19[];

typedef struct {
    u8 pad[0x25A];
    s8 low : 4;
    s8 high : 4;
} Flags_002032C0;

/* Sets pad `pad`'s key-repeat interval and its analog mode. */
void SzPad_SetParam(s32 pad, s8 interval, s64 analog) {
    s32 offset;
    Flags_002032C0 *entry;

    offset = pad * 0x5C;
    D_00325C19[offset] = interval;
    entry = (Flags_002032C0 *)(padStates + offset);
    entry->low = analog;
}

typedef struct Pad_00203320 {
    u16 buttons[3];
    u8 act[4];
    u8 data[12];
    u8 pad16[2];
    s32 press[16];
    s8 mode;
    s8 base;
    s8 low : 4;
    s8 count : 4;
    s8 state : 6;
    s8 pressed : 1;
    s8 ready : 1;
} Pad_00203320;

/* Clears a pad's state. */
static inline void reset_00203320(Pad_00203320 *pad) {
    s32 i;

    for (i = 0; i < 3; i++) {
        pad->buttons[i] = 0;
    }
    for (i = 0; i < 16; i++) {
        pad->press[i] = -pad->base;
    }
    pad->pressed = 0;
    for (i = 0; i < 4; i++) {
        pad->act[i] = 0x80;
    }
    pad->ready = 0;
    for (i = 0; i < 12; i++) {
        pad->data[i] = 0;
    }
}

/* Reads both pads' state from libpad: connected, analog or not, buttons, sticks, pressures. */
void SzPad_Status(void) {
    extern s32 scePadGetReqState();
    s32 port;
    Pad_00203320 *pad;
    u8 *base;
    s32 state;
    s32 id;
    s32 offs;

    base = padStates;
    for (port = 0; port < 2; port++, base += 0x5C) {
        pad = (Pad_00203320 *)(base + 0x200);
        state = scePadGetState(port, 0);
        if (state == 0) {
            reset_00203320(pad);
            pad->state = 0;
        }
        if (state == 2 || state == 6) {
            switch (pad->state) {
            case 0:
                for (state = 0; state < 3; state++) {
                    pad->buttons[state] = 0;
                }
                for (state = 0; state < 16; state++) {
                    pad->press[state] = -pad->base;
                }
                pad->pressed = 0;
                for (state = 0; state < 4; state++) {
                    pad->act[state] = 0x80;
                }
                pad->ready = 0;
                for (state = 0; state < 12; state++) {
                    pad->data[state] = 0;
                }
                pad->count = scePadInfoMode(port, 0, 4, -1);
                id = scePadInfoMode(port, 0, 1, 0);
                if (id == 0) {
                    break;
                }
                pad->mode = id;
                id = scePadInfoMode(port, 0, 2, 0);
                if (id > 0) {
                    pad->mode = id;
                }
                if (pad->count != 0) {
                    pad->state = 1;
                } else {
                    pad->state = 5;
                }
                break;
            case 1:
                pad->state = 5;
                for (offs = 0; offs < pad->count; offs++) {
                    id = scePadInfoMode(port, 0, 4, offs);
                    if (id == 7 && scePadSetMainMode(port, 0, offs, 3) == 1) {
                        pad->mode = id;
                        pad->state = 2;
                        break;
                    }
                }
                break;
            case 2:
                id = scePadGetReqState(port, 0);
                if (id != 0) {
                    if (id == 1) {
                        pad->state = 1;
                    }
                } else {
                    pad->pressed = 1;
                    pad->state = 3;
                }
                break;
            case 3:
                pad->state = 5;
                if (scePadInfoPressMode(port, 0) == 1 && scePadEnterPressMode(port, 0) == 1) {
                    pad->state = 4;
                }
                break;
            case 4:
                id = scePadGetReqState(port, 0);
                if (id != 0) {
                    if (id == 1) {
                        pad->state = 3;
                    }
                } else {
                    pad->ready = 1;
                    pad->state = 5;
                }
                break;
            case 5:
                break;
            }
        }
    }
}

typedef struct Flags_00203840 {
    s8 status : 6;
    s8 unused : 2;
} Flags_00203840;

/* Works out this frame's newly pressed, held and repeating buttons of both pads. */
void SzPad_Act(void) {
    s32 var_a2;
    s32 var_a3;
    u8 *temp_t0;
    s32 temp_t1;
    u8 *var_t2;
    u8 *var_t3;
    s32 temp_t4;

    var_t3 = padStates;
    var_a2 = 0;
    do {
        temp_t0 = var_t3 + 0x200;
        if (((Flags_00203840 *)(var_t3 + 0x25B))->status == 5) {
            var_a3 = 0;
            var_t2 = temp_t0;
            do {
                temp_t1 = 1 << var_a3;
                temp_t4 = *(u16 *)temp_t0 & temp_t1;
                if ((temp_t4 != 0) && (temp_t4 == (*(u16 *)(temp_t0 + 2) & temp_t1))) {
                    *(s32 *)(var_t2 + 0x18) += 1;
                } else {
                    *(s32 *)(var_t2 + 0x18) = -*(s8 *)(temp_t0 + 0x59);
                }
                var_a3 += 1;
                var_t2 += 4;
            } while (var_a3 < 0x10);
            *(u16 *)(temp_t0 + 2) = *(u16 *)temp_t0;
            *(u16 *)temp_t0 = *(u16 *)(temp_t0 + 4);
            *(u16 *)(temp_t0 + 4) = 0;
        }
        var_a2 += 1;
        var_t3 += 0x5C;
    } while (var_a2 < 2);
}

typedef struct Flags_002038F0 {
    s8 mode : 6;
    s8 axes : 1;
    s8 pressure : 1;
} Flags_002038F0;

extern u8 padStates[]; /* original: gSzPad_pl */

/* The pads' per-vertical-blank work. */
s32 SzPad_VSync(void) {
    u8 data[20];
    u8 *pressure;
    s32 axisIndex;
    s32 state;
    u8 *axes;
    s32 pressureIndex;
    s32 port;
    u8 *pad;
    u8 *entry;

    entry = padStates;
    port = 0;
    do {
        pad = entry + 0x200;
        if (((Flags_002038F0 *)(entry + 0x25B))->mode == 5) {
            state = scePadGetState(port, 0);
            if (state == 2 || state == 6) {
                if (scePadRead(port, 0, data) != 0) {
                    if (((Flags_002038F0 *)(pad + 0x5B))->axes) {
                        axes = data;
                        axisIndex = 0;
                        do {
                            pad[6 + axisIndex] = axes[4];
                            axisIndex++;
                            axes++;
                        } while (axisIndex < 4);
                    }
                    if (((Flags_002038F0 *)(pad + 0x5B))->pressure) {
                        pressure = data;
                        pressureIndex = 0;
                        do {
                            pad[0xA + pressureIndex] = pressure[8];
                            pressureIndex++;
                            pressure++;
                        } while (pressureIndex < 12);
                    }
                    *(u16 *)(pad + 4) |= ((data[2] << 8) | data[3]) ^ 0xFFFF;
                }
            }
        }
        port++;
        entry += 0x5C;
    } while (port < 2);
    return 1;
}

typedef struct State_00203A40 {
    u16 held;       /* the buttons held this frame */
    u16 heldBefore; /* the buttons held the frame before (SzPad_Act copies `held` here first) */
    u8 padding04[0x14];
    s32 counters[16];
    u8 padding58[2];
    s8 interval : 4;
    s8 other : 4;
    u8 padding5B;
} State_00203A40;

/* Pad `pad`'s buttons in `wanted` that are newly pressed (`mode` 0), held (1), or newly pressed or repeating (2). */
s32 SzPad_Check(s32 pad, s32 mode, s32 wanted) {
    s32 bit;
    State_00203A40 *buttons;
    s32 bitMask;
    u8 *counters;
    s32 mask;
    s32 counter;
    s32 result;
    u8 *padState;

    padState = padStates + (pad * 0x5C);
    buttons = (State_00203A40 *)(padState + 0x200);
    switch (mode) {
    case 0:
        return wanted & (buttons->held & ~buttons->heldBefore);
    case 2:
        result = 0;
        bit = 0;
        counters = (u8 *)buttons;
        mask = wanted & 0xFFFF;
        do {
            bitMask = 1 << bit;
            if (mask & bitMask) {
                counter = *(s32 *)(counters + 0x18);
                if ((counter >= 0) && ((counter % buttons->interval) == 0)) {
                    result = (result | bitMask) & 0xFFFF;
                }
            }
            bit += 1;
            counters += 4;
        } while (bit < 0x10);
        return result | SzPad_Check(pad, 0, wanted);
    case 1:
        return buttons->held & wanted;
    }
    return 0;
}

/* Restarts the key-repeat counters of pad `pad`'s buttons in `mask`. */
s32 SzPad_ResetCounter(s32 pad, s32 mask) {
    u8 *buttons;
    s32 bit;
    u8 *counters;

    buttons = padStates + (pad * 0x5C) + 0x200;
    bit = 0;
    counters = buttons;
    do {
        if (mask & 0xFFFF & (1 << bit)) {
            *(s32 *)(counters + 0x18) = -*(s8 *)(buttons + 0x59);
        }
        bit += 1;
        counters += 4;
    } while (bit < 0x10);
    return 0;
}

typedef struct {
    u8 padding[0x25B];
    s8 unused : 6;
    s8 flag : 1;
    s8 unused_high : 1;
} Flags_00203BC0;

extern u8 padStates[]; /* original: gSzPad_pl */

/* Whether pad `pad` is in analog mode. */
s32 SzPad_IsAnalog(s32 pad) {
    return ((Flags_00203BC0 *)(padStates + pad * 0x5C))->flag ? 1 : 0;
}

typedef struct {
    u8 padding[0x25B];
    s8 : 7;
    s8 flag : 1;
} Flags_00203C00;

/* Whether pad `pad` reports button pressures. */
s32 SzPad_IsPress(s32 pad) {
    Flags_00203C00 *flags = (Flags_00203C00 *)(padStates + pad * 0x5C);

    return flags->flag ? 1 : 0;
}

typedef struct Entry_00203C40 {
    u8 pad[0x206];
    u8 value;
} Entry_00203C40;

/* Analog byte `index` of pad `pad` (the sticks). */
u8 SzPad_GetAnalogInfo(s32 pad, s32 index) {
    return ((Entry_00203C40 *)(padStates + pad * 0x5C + index))->value;
}

/* Sets analog byte `index` of pad `pad` (the tutorial fakes stick input with it). */
void SzPad_SetAnalogInfo(s32 pad, s32 index, s8 value) {
    *(s8 *)(padStates + pad * 0x5C + index + 0x206) = value;
}

typedef struct {
    u8 pad[0x20A];
    u8 value;
} Entry_00203CA0;

/* The pressure of button `index` of pad `pad`. */
u8 SzPad_GetPressInfo(s32 pad, s32 index) {
    return ((Entry_00203CA0 *)(index + (padStates + pad * 0x5C)))->value;
}

typedef struct Flags_00203CD0 {
    s8 flag0 : 1;
    s8 flag1 : 1;
    s8 flag2 : 1;
    s8 unused3 : 5;
} Flags_00203CD0;

typedef struct State_00203CD0 {
    s32 f00;
    s32 f04;
    s32 f08;
    s32 f0C;
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
    s32 f20;
    s32 f24;
    s32 f28;
    Flags_00203CD0 flags;
} State_00203CD0;

extern State_00203CD0 debugState; /* original: gSzDebug_dl */

/* Starts the debug menus. */
void SzDebug_Init(void) {
    extern s32 func_0019B648();
    extern u8 D_002D078C;
    extern u8 D_002D07F4[];
    extern u8 D_002D07FA[];
    extern u8 D_002D07FF[];
    State_00203CD0 *state = &debugState;
    u8 buffer[0x80];

    RhMem_FillMemory((s8 *)&debugState, 0, 0x30);
    debugState.f00 = 0;
    debugState.f04 = D_002D078C;
    debugState.f08 = 0;
    debugState.f0C = 0;
    debugState.f10 = 0;
    debugState.f14 = 0;
    debugState.f18 = 0;
    debugState.f1C = 0;
    debugState.f20 = 0;
    debugState.f24 = 0;
    debugState.f28 = 2;
    debugState.flags.flag0 = 0;
    debugState.flags.flag1 = 0;
    debugState.flags.flag2 = 0;
    func_0019B648(buffer, D_002D07F4, SzFile_GetEnv((s32)D_002D07FA), D_002D07FF);
    if (getenv((s32)D_002D07FF) != 0) {
        state->flags.flag1 = 1;
    }
}

struct DotrSmallBits {
    signed char unknown_bit_0 : 1;
    signed char unknown_bit_1 : 1;
    signed char unknown_bit_2 : 1;
    signed char unknown_bit_3 : 1;
    signed char unknown_bit_4 : 1;
    signed char unknown_bit_5 : 1;
    signed char unknown_bit_6 : 1;
    signed char unknown_bit_7 : 1;
};
struct DotrSmallFlagsOwner {
    int unknown_00[11];
    struct DotrSmallBits unknown_2c;
};
extern struct DotrSmallFlagsOwner D_00325C80_203e20;
enum {
    DOTR_DEBUG_MENU = 0,  
    DOTR_DEBUG_MODEL = 1, 
    DOTR_DEBUG_DIGIT = 2, 
    
    DOTR_DEBUG_EFF_NO = 3,     
    DOTR_DEBUG_EFF_ARG = 4,    
    DOTR_DEBUG_EFF_A_HI = 5,   
    DOTR_DEBUG_EFF_A_LO = 6,   
    DOTR_DEBUG_EFF_B_HI = 7,   
    DOTR_DEBUG_EFF_B_LO = 8,   
    DOTR_DEBUG_EFF_ROW = 9,    
    DOTR_DEBUG_EFF_COLUMN = 10 
};
struct DotrDebugCardConst {
    unsigned char unknown_00;
    unsigned char unknown_01;
    unsigned char unknown_02;
};
struct DotrDebugCard {
    struct DotrDebugCardConst *info; 
    char unknown_04[0x38];
    unsigned short unknown_3c;       
    unsigned char unknown_3e;
    unsigned char unknown_3f;
    char unknown_40[4];
    unsigned char unknown_44;        
    unsigned char unknown_45;
};
struct DotrDebugDigits {
    int d[3];
};
extern struct DotrDebugDigits D_00293D28;
extern char *gBaseStr[];
extern int func_001F2980_b(int index);
extern int func_001AAF60_b(int);
extern int func_001F2920_b(int index);
extern struct DotrDebugCard *func_001DD130_b(int a, int b);
extern struct DotrDebugCardConst *func_001DD0E0_b(int id);
extern void *func_001DF540_b(int a, int b);
extern int func_001E18A0_b(int a, int b, int value);
extern int func_001F33C0_b(int index, int value);

/* Runs the debug menus on pad 1 (model, camera, light and frame-buffer tools). */
void SzDebug_Act(void)
{
    struct DotrSmallFlagsOwner *p = &D_00325C80_203e20;
    int standby = SzModel_IsModelStandby(p->unknown_00[DOTR_DEBUG_MODEL]);
    int type = func_001F2980_b(p->unknown_00[DOTR_DEBUG_MODEL]);
    int menu = SzDebug_GetActiveMenu();
    int mode = func_001AAF60_b(1);

    if (standby == 0 && p->unknown_00[DOTR_DEBUG_MENU] > 0 && p->unknown_00[DOTR_DEBUG_MENU] < 12) {
        p->unknown_00[DOTR_DEBUG_MENU] = 0;
        menu = 0;
    }
    if (p->unknown_00[DOTR_DEBUG_MENU] == 2 && type != 4 && type != 5) {
        p->unknown_00[DOTR_DEBUG_MENU] = 0;
        menu = 0;
    }
    if (!(p->unknown_00[DOTR_DEBUG_MENU] != 3 && p->unknown_00[DOTR_DEBUG_MENU] != 5 && p->unknown_00[DOTR_DEBUG_MENU] != 6) && (type != 5 || mode != 5)) {
        p->unknown_00[DOTR_DEBUG_MENU] = 0;
        menu = 0;
    }
    if (p->unknown_00[DOTR_DEBUG_MENU] == 4 && (type != 6 || mode != 0)) {
        p->unknown_00[DOTR_DEBUG_MENU] = 0;
        menu = 0;
    }
    if (p->unknown_2c.unknown_bit_1) {
        if (SzPad_Check(1, 0, 0x800)) {
            p->unknown_2c.unknown_bit_2 = p->unknown_2c.unknown_bit_2 ? 0 : 1;
        }
    } else if (SzPad_Check(1, 0, 0x800)) {
        SzView_SetMode(0, (SzView_GetMode(0) + 1) % 3);
    }
    if (SzPad_Check(1, 0, 0x100)) {
        p->unknown_2c.unknown_bit_0 = p->unknown_2c.unknown_bit_0 ? 0 : 1;
    }
    if (p->unknown_2c.unknown_bit_2) {
        lSzDebug_ActEffect();
        return;
    }
    if (SzPad_Check(0, 2, 0x100)) {
        for (;;) {
            p->unknown_00[DOTR_DEBUG_MENU] = (p->unknown_00[DOTR_DEBUG_MENU] + 17) % 18;
            if (standby == 0 && p->unknown_00[DOTR_DEBUG_MENU] > 0 && p->unknown_00[DOTR_DEBUG_MENU] <= 11) {
                continue;
            }
            if (p->unknown_00[DOTR_DEBUG_MENU] == 2 && type != 4 && type != 5) {
                continue;
            }
            if (!(p->unknown_00[DOTR_DEBUG_MENU] != 3 && p->unknown_00[DOTR_DEBUG_MENU] != 5 && p->unknown_00[DOTR_DEBUG_MENU] != 6) && (type != 5 || mode != 5)) {
                continue;
            }
            if (p->unknown_00[DOTR_DEBUG_MENU] == 4 && (type != 6 || mode != 0)) {
                continue;
            }
            break;
        }
        SzSound_PlaySE(0, 0);
    }
    if (SzPad_Check(0, 2, 0x800)) {
        for (;;) {
            p->unknown_00[DOTR_DEBUG_MENU] = (p->unknown_00[DOTR_DEBUG_MENU] + 19) % 18;
            if (standby == 0 && p->unknown_00[DOTR_DEBUG_MENU] > 0 && p->unknown_00[DOTR_DEBUG_MENU] <= 11) {
                continue;
            }
            if (p->unknown_00[DOTR_DEBUG_MENU] == 2 && type != 4 && type != 5) {
                continue;
            }
            if (!(p->unknown_00[DOTR_DEBUG_MENU] != 3 && p->unknown_00[DOTR_DEBUG_MENU] != 5 && p->unknown_00[DOTR_DEBUG_MENU] != 6) && (type != 5 || mode != 5)) {
                continue;
            }
            if (p->unknown_00[DOTR_DEBUG_MENU] == 4 && (type != 6 || mode != 0)) {
                continue;
            }
            break;
        }
        SzSound_PlaySE(0, 0);
    }
    if (menu == 0) {
        int no = func_001F2920_b(p->unknown_00[DOTR_DEBUG_MODEL]);
        struct DotrDebugDigits dd = D_00293D28;
        int n;
        

        {
            int *e = dd.d;
            *e++ = (no / 100) % 10;
            *e++ = (no / 10) % 10;
            *e = no % 10;
        }
        n = no;
        if (SzPad_Check(0, 2, 0x5000)) {
            if (SzPad_Check(0, 2, 0x1000)) {
                dd.d[p->unknown_00[DOTR_DEBUG_DIGIT]] = (dd.d[p->unknown_00[DOTR_DEBUG_DIGIT]] + 11) % 10;
            } else {
                dd.d[p->unknown_00[DOTR_DEBUG_DIGIT]] = (dd.d[p->unknown_00[DOTR_DEBUG_DIGIT]] + 9) % 10;
            }
            n = dd.d[0] * 100 + dd.d[1] * 10 + dd.d[2];
        }
        if (SzPad_Check(0, 2, 2)) {
            n = (n + 1001) % 1000;
        }
        if (SzPad_Check(0, 2, 1)) {
            n = (n + 999) % 1000;
        }
        if (SzPad_Check(0, 2, 0x2000)) {
            p->unknown_00[DOTR_DEBUG_DIGIT] = (p->unknown_00[DOTR_DEBUG_DIGIT] + 4) % 3;
        }
        if (SzPad_Check(0, 2, 0x8000)) {
            p->unknown_00[DOTR_DEBUG_DIGIT] = (p->unknown_00[DOTR_DEBUG_DIGIT] + 2) % 3;
        }
        if (n == no) {
            if (SzPad_Check(0, 2, 8)) {
                p->unknown_00[DOTR_DEBUG_MODEL] = (p->unknown_00[DOTR_DEBUG_MODEL] + 45) % 44;
            }
            if (SzPad_Check(0, 2, 4)) {
                p->unknown_00[DOTR_DEBUG_MODEL] = (p->unknown_00[DOTR_DEBUG_MODEL] + 43) % 44;
            }
            type = func_001F2980_b(p->unknown_00[DOTR_DEBUG_MODEL]);
        } else if (!SzModel_IsModelLoading(p->unknown_00[DOTR_DEBUG_MODEL])) {
            struct DotrDebugCard *q = func_001DD130_b(-1, p->unknown_00[DOTR_DEBUG_MODEL]);
            if (q != 0) {
                q->unknown_3c = SzDuel_Xax2New(n);
                q->info = func_001DD0E0_b(q->unknown_3c);
                if (q->info != 0) {
                    q->unknown_3e = q->info->unknown_00;
                    q->unknown_3f = q->info->unknown_02 & 0xf;
                }
            }
            SzModel_Preset(p->unknown_00[DOTR_DEBUG_MODEL], -1, n);
        }
        if (SzPad_Check(0, 0, 0x30) && !SzModel_IsModelLoading(p->unknown_00[DOTR_DEBUG_MODEL])) {
            int flag = SzPad_Check(0, 0, 0x10) ? 1 : 0;
            int none = 0;
            if ((type == 4 || type == 5) && func_001DF540_b(-1, p->unknown_00[DOTR_DEBUG_MODEL]) == 0) {
                none = 1;
            }
            if (!none && SzModel_Load(p->unknown_00[DOTR_DEBUG_MODEL], -1, n, flag) && (type == 4 || type == 5)) {
                struct DotrDebugCard *q = func_001DD130_b(-1, p->unknown_00[DOTR_DEBUG_MODEL]);
                if (q != 0 && q->info != 0) {
                    if (mode == 5 && type == 5) {
                        SzBattle_Entry(q->unknown_44, (q->unknown_44 << 8) | q->unknown_45);
                        SzDuel_SetBusyFlag(q->unknown_44, q->unknown_45, 0);
                    }
                    func_001E18A0_b(-1, p->unknown_00[DOTR_DEBUG_MODEL], 7);
                    SzDuel_SetUnitCtlRateM(-1, p->unknown_00[DOTR_DEBUG_MODEL], 1, 0);
                }
            }
        }
        if (type == 4 || type == 5) {
            if (SzPad_Check(0, 0, 0x80)) {
                SzModel_SetDeform(p->unknown_00[DOTR_DEBUG_MODEL], 1);
            }
            if (SzPad_Check(0, 0, 0x40)) {
                SzModel_SetDeform(p->unknown_00[DOTR_DEBUG_MODEL], 0);
            }
            if (SzPad_Check(0, 0, 0x600)) {
                func_001F33C0_b(p->unknown_00[DOTR_DEBUG_MODEL], 1);
            }
        }
    }
    if (SzDebug_IsHide()) {
        return;
    }
    func_001F2920_b(p->unknown_00[DOTR_DEBUG_MODEL]);
    func_0019BEF0(gBaseStr[type]);
    {
    int none = 0;
    if ((type == 4 || type == 5) && func_001DF540_b(-1, p->unknown_00[DOTR_DEBUG_MODEL]) == 0) {
        none = 1;
    }
    if (!none && !SzModel_IsModelReady(p->unknown_00[DOTR_DEBUG_MODEL]) && !SzModel_IsModelLoading(p->unknown_00[DOTR_DEBUG_MODEL]) && SzModel_IsModelStandby(p->unknown_00[DOTR_DEBUG_MODEL])) {
        SzModel_IsModelDisp(p->unknown_00[DOTR_DEBUG_MODEL]);
    }
    }
    SzModel_GetDeform(p->unknown_00[DOTR_DEBUG_MODEL]);
    if (menu == 0) {
        int i = p->unknown_00[DOTR_DEBUG_DIGIT];
        int k = 100;
        while (i-- != 0) {
            k /= 10;
        }
    }
}

struct DotrSmallBits_2047f0 {
    signed char unknown_bit_0 : 1;
    signed char unknown_bit_1 : 1;
    signed char unknown_bit_2 : 1;
    signed char unknown_bit_3 : 1;
    signed char unknown_bit_4 : 1;
    signed char unknown_bit_5 : 1;
    signed char unknown_bit_6 : 1;
    signed char unknown_bit_7 : 1;
};
struct DotrSmallFlagsOwner_2047f0 {
    int unknown_00[11];
    struct DotrSmallBits_2047f0 unknown_2c;
};
extern struct DotrSmallFlagsOwner_2047f0 D_00325C80_2047f0;
enum {
    DOTR_DEBUG_MENU_2047f0 = 0,  
    DOTR_DEBUG_MODEL_2047f0 = 1, 
    DOTR_DEBUG_DIGIT_2047f0 = 2, 
    
    DOTR_DEBUG_EFF_NO_2047f0 = 3,     
    DOTR_DEBUG_EFF_ARG_2047f0 = 4,    
    DOTR_DEBUG_EFF_A_HI_2047f0 = 5,   
    DOTR_DEBUG_EFF_A_LO_2047f0 = 6,   
    DOTR_DEBUG_EFF_B_HI_2047f0 = 7,   
    DOTR_DEBUG_EFF_B_LO_2047f0 = 8,   
    DOTR_DEBUG_EFF_ROW_2047f0 = 9,    
    DOTR_DEBUG_EFF_COLUMN_2047f0 = 10 
};
struct DotrDebugDigits_2047f0 {
    int d[3];
};
extern struct DotrDebugDigits_2047f0 D_00293D38;
extern struct DotrDebugDigits_2047f0 D_00293D48;
int func_001F48F0_b(int a, int b, int c, int d, int e);

/* Runs the debug effect player. */
void lSzDebug_ActEffect(void)
{
    struct DotrSmallFlagsOwner_2047f0 *p = &D_00325C80_2047f0;

    if ((SzPad_Check(0, 1, 3) & 0xffff) != 3) {
    struct DotrDebugDigits_2047f0 a = D_00293D38;
    int no = p->unknown_00[DOTR_DEBUG_EFF_NO_2047f0];
    struct DotrDebugDigits_2047f0 b;
    int arg;
    
    {
        int *e = a.d;
        *e++ = (no / 100) % 10;
        *e++ = (no / 10) % 10;
        *e = no % 10;
    }
    b = D_00293D48;
    arg = p->unknown_00[DOTR_DEBUG_EFF_ARG_2047f0];
    {
        int *e = b.d;
        *e++ = (arg / 100) % 10;
        *e++ = (arg / 10) % 10;
        *e = arg % 10;
    }
    switch (p->unknown_00[DOTR_DEBUG_EFF_ROW_2047f0]) {
    case 0:
        if (SzPad_Check(0, 2, 0x2000)) {
            if (++p->unknown_00[DOTR_DEBUG_EFF_COLUMN_2047f0] > 2) {
                p->unknown_00[DOTR_DEBUG_EFF_ROW_2047f0] = 1;
                p->unknown_00[DOTR_DEBUG_EFF_COLUMN_2047f0] = 0;
            }
        } else if (SzPad_Check(0, 2, 0x8000)) {
            if (--p->unknown_00[DOTR_DEBUG_EFF_COLUMN_2047f0] < 0) {
                p->unknown_00[DOTR_DEBUG_EFF_ROW_2047f0] = 5;
                p->unknown_00[DOTR_DEBUG_EFF_COLUMN_2047f0] = 0;
            }
        } else if (SzPad_Check(0, 2, 0x5000)) {
            int i = p->unknown_00[DOTR_DEBUG_EFF_COLUMN_2047f0];
            if (SzPad_Check(0, 2, 0x1000)) {
                a.d[i] = (a.d[i] + 11) % 10;
            } else {
                a.d[i] = (a.d[i] + 9) % 10;
            }
            p->unknown_00[DOTR_DEBUG_EFF_NO_2047f0] = a.d[0] * 100 + a.d[1] * 10 + a.d[2];
        }
        break;
    case 1:
        if (SzPad_Check(0, 2, 0x2000)) {
            if (++p->unknown_00[DOTR_DEBUG_EFF_COLUMN_2047f0] > 2) {
                p->unknown_00[DOTR_DEBUG_EFF_ROW_2047f0] = 2;
                p->unknown_00[DOTR_DEBUG_EFF_COLUMN_2047f0] = 0;
            }
        } else if (SzPad_Check(0, 2, 0x8000)) {
            if (--p->unknown_00[DOTR_DEBUG_EFF_COLUMN_2047f0] < 0) {
                p->unknown_00[DOTR_DEBUG_EFF_ROW_2047f0] = 0;
                p->unknown_00[DOTR_DEBUG_EFF_COLUMN_2047f0] = 2;
            }
        } else if (SzPad_Check(0, 2, 0x5000)) {
            int i = p->unknown_00[DOTR_DEBUG_EFF_COLUMN_2047f0];
            if (SzPad_Check(0, 2, 0x1000)) {
                b.d[i] = (b.d[i] + 11) % 10;
            } else {
                b.d[i] = (b.d[i] + 9) % 10;
            }
            p->unknown_00[DOTR_DEBUG_EFF_ARG_2047f0] = b.d[0] * 100 + b.d[1] * 10 + b.d[2];
        }
        break;
    case 2:
        if (SzPad_Check(0, 2, 0x2000)) {
            if (++p->unknown_00[DOTR_DEBUG_EFF_COLUMN_2047f0] > 0) {
                p->unknown_00[DOTR_DEBUG_EFF_ROW_2047f0] = 3;
                p->unknown_00[DOTR_DEBUG_EFF_COLUMN_2047f0] = 0;
            }
        } else if (SzPad_Check(0, 2, 0x8000)) {
            if (--p->unknown_00[DOTR_DEBUG_EFF_COLUMN_2047f0] < 0) {
                p->unknown_00[DOTR_DEBUG_EFF_ROW_2047f0] = 1;
                p->unknown_00[DOTR_DEBUG_EFF_COLUMN_2047f0] = 2;
            }
        } else if (SzPad_Check(0, 2, 0x5000)) {
            if (SzPad_Check(0, 2, 0x1000)) {
                p->unknown_00[DOTR_DEBUG_EFF_A_HI_2047f0] = (p->unknown_00[DOTR_DEBUG_EFF_A_HI_2047f0] + 3) % 2;
            } else {
                p->unknown_00[DOTR_DEBUG_EFF_A_HI_2047f0] = (p->unknown_00[DOTR_DEBUG_EFF_A_HI_2047f0] + 1) % 2;
            }
        }
        break;
    case 3:
        if (SzPad_Check(0, 2, 0x2000)) {
            if (++p->unknown_00[DOTR_DEBUG_EFF_COLUMN_2047f0] > 0) {
                p->unknown_00[DOTR_DEBUG_EFF_ROW_2047f0] = 4;
                p->unknown_00[DOTR_DEBUG_EFF_COLUMN_2047f0] = 0;
            }
        } else if (SzPad_Check(0, 2, 0x8000)) {
            if (--p->unknown_00[DOTR_DEBUG_EFF_COLUMN_2047f0] < 0) {
                p->unknown_00[DOTR_DEBUG_EFF_ROW_2047f0] = 2;
                p->unknown_00[DOTR_DEBUG_EFF_COLUMN_2047f0] = 0;
            }
        } else if (SzPad_Check(0, 2, 0x5000)) {
            if (SzPad_Check(0, 2, 0x1000)) {
                p->unknown_00[DOTR_DEBUG_EFF_A_LO_2047f0] = (p->unknown_00[DOTR_DEBUG_EFF_A_LO_2047f0] + 12) % 11;
            } else {
                p->unknown_00[DOTR_DEBUG_EFF_A_LO_2047f0] = (p->unknown_00[DOTR_DEBUG_EFF_A_LO_2047f0] + 10) % 11;
            }
        }
        break;
    case 4:
        if (SzPad_Check(0, 2, 0x2000)) {
            if (++p->unknown_00[DOTR_DEBUG_EFF_COLUMN_2047f0] > 0) {
                p->unknown_00[DOTR_DEBUG_EFF_ROW_2047f0] = 5;
                p->unknown_00[DOTR_DEBUG_EFF_COLUMN_2047f0] = 0;
            }
        } else if (SzPad_Check(0, 2, 0x8000)) {
            if (--p->unknown_00[DOTR_DEBUG_EFF_COLUMN_2047f0] < 0) {
                p->unknown_00[DOTR_DEBUG_EFF_ROW_2047f0] = 3;
                p->unknown_00[DOTR_DEBUG_EFF_COLUMN_2047f0] = 0;
            }
        } else if (SzPad_Check(0, 2, 0x5000)) {
            if (SzPad_Check(0, 2, 0x1000)) {
                p->unknown_00[DOTR_DEBUG_EFF_B_HI_2047f0] = (p->unknown_00[DOTR_DEBUG_EFF_B_HI_2047f0] + 3) % 2;
            } else {
                p->unknown_00[DOTR_DEBUG_EFF_B_HI_2047f0] = (p->unknown_00[DOTR_DEBUG_EFF_B_HI_2047f0] + 1) % 2;
            }
        }
        break;
    case 5:
        if (SzPad_Check(0, 2, 0x2000)) {
            if (++p->unknown_00[DOTR_DEBUG_EFF_COLUMN_2047f0] > 0) {
                p->unknown_00[DOTR_DEBUG_EFF_ROW_2047f0] = 0;
                p->unknown_00[DOTR_DEBUG_EFF_COLUMN_2047f0] = 0;
            }
        } else if (SzPad_Check(0, 2, 0x8000)) {
            if (--p->unknown_00[DOTR_DEBUG_EFF_COLUMN_2047f0] < 0) {
                p->unknown_00[DOTR_DEBUG_EFF_ROW_2047f0] = 4;
                p->unknown_00[DOTR_DEBUG_EFF_COLUMN_2047f0] = 0;
            }
        } else if (SzPad_Check(0, 2, 0x5000)) {
            if (SzPad_Check(0, 2, 0x1000)) {
                p->unknown_00[DOTR_DEBUG_EFF_B_LO_2047f0] = (p->unknown_00[DOTR_DEBUG_EFF_B_LO_2047f0] + 12) % 11;
            } else {
                p->unknown_00[DOTR_DEBUG_EFF_B_LO_2047f0] = (p->unknown_00[DOTR_DEBUG_EFF_B_LO_2047f0] + 10) % 11;
            }
        }
        break;
    }
    if (SzPad_Check(0, 2, 8)) {
        p->unknown_00[DOTR_DEBUG_EFF_A_LO_2047f0] = (p->unknown_00[DOTR_DEBUG_EFF_A_LO_2047f0] + 12) % 11;
    }
    if (SzPad_Check(0, 2, 4)) {
        p->unknown_00[DOTR_DEBUG_EFF_A_LO_2047f0] = (p->unknown_00[DOTR_DEBUG_EFF_A_LO_2047f0] + 10) % 11;
    }
    if (SzPad_Check(0, 0, 0x10)) {
        SzEffect_Clear();
    }
    if (SzPad_Check(0, 0, 0x40)) {
        SzEffect_Destroy2(0, p->unknown_00[DOTR_DEBUG_EFF_NO_2047f0]);
    }
    if (SzPad_Check(0, 0, 0x20)) {
        func_001F48F0_b(0, p->unknown_00[DOTR_DEBUG_EFF_NO_2047f0], p->unknown_00[DOTR_DEBUG_EFF_ARG_2047f0],
                       (p->unknown_00[DOTR_DEBUG_EFF_A_HI_2047f0] << 8) | p->unknown_00[DOTR_DEBUG_EFF_A_LO_2047f0],
                       (p->unknown_00[DOTR_DEBUG_EFF_B_HI_2047f0] << 8) | p->unknown_00[DOTR_DEBUG_EFF_B_LO_2047f0]);
    }
    if (SzPad_Check(0, 0, 0x80)) {
        SzEffect_Erase2(0, -1);
    }
    if (SzPad_Check(0, 0, 0x800)) {
        SzEffect_Sleep2(0, p->unknown_00[DOTR_DEBUG_EFF_NO_2047f0], 0);
    }
    if (SzPad_Check(0, 0, 0x100)) {
        SzEffect_Sleep2(0, p->unknown_00[DOTR_DEBUG_EFF_NO_2047f0], 1);
    }
    }
    {
        int i = p->unknown_00[DOTR_DEBUG_EFF_COLUMN_2047f0];
        int k = 100;
        while (i-- != 0) {
            k /= 10;
        }
    }
}

/* The open debug menu. */
s32 SzDebug_GetActiveMenu(void) {
    return debugState.f00;
}

/* The model slot the debug menu works on. */
s32 SzDebug_GetActiveModel(void) {
    return debugState.f04;
}

typedef struct Flags_00205170 {
    s8 flag0 : 1;
    s8 unused1 : 1;
    s8 flag2 : 1;
    s8 unused3 : 5;
} Flags_00205170;

typedef struct State_00205170 {
    u8 padding[0x2C];
    Flags_00205170 flags;
} State_00205170;

/* Whether the debug display is hidden. */
s32 SzDebug_IsHide(void) {
    extern Flags_00205170 D_00325CAC;
    State_00205170 *state = (State_00205170 *)&debugState;

    if (D_00325CAC.flag2 != 0) {
        return 1;
    }
    return state->flags.flag0 != 0 ? 1 : 0;
}

typedef struct {
    s8 enabled : 1;
} Flags_002051C0;

/* Hides or shows the debug display. */
void SzDebug_SetHideFlag(s64 on) {
    extern Flags_002051C0 D_00325CAC;

    D_00325CAC.enabled = (s8)on;
}

typedef struct {
    s8 : 2;
    s8 flag : 1;
} Flags_002051F0;

extern Flags_002051F0 D_00325CAC;

/* Whether the debug effect player is running. */
s32 SzDebug_IsEffect(void) {
    return D_00325CAC.flag ? 1 : 0;
}

#pragma pack(2)
typedef struct BitmapFileHeader_00205210 {
    s16 type;
    u16 sizeLow;
    u16 sizeHigh;
    s16 reserved1;
    s16 reserved2;
    u16 offsetLow;
    u16 offsetHigh;
} BitmapFileHeader_00205210;
#pragma pack()

typedef struct BitmapInfo_00205210 {
    s32 size;
    s32 width;
    s32 height;
    s16 planes;
    s16 bits;
    s32 compression;
    s32 imageSize;
    s32 horizontalResolution;
    s32 verticalResolution;
    s32 colorsUsed;
    s32 colorsImportant;
} BitmapInfo_00205210;

extern u8 D_002D07FA[];
extern u8 D_002D0806[];
extern s32 nSaveCount;

/* Debug: writes the frame buffer to a file on the host. */
void SzDebug_OutputFrameBuffer(void) {
    u8 buffer[0x780];
    BitmapInfo_00205210 info;
    BitmapFileHeader_00205210 fileHeader;
    s32 fd;
    u32 fileSize;
    extern s32 func_0019B648();

    while (SzFile_InqRequest(-1) != 0) {
        SzFile_DoRequestS();
    }
    RhBase_CopyFrameBuffer(0x04000000);
    fileHeader.type = 0x4D42;
    fileSize = 0x280 * 0x1C0 * 3 + 0x36;
    fileHeader.sizeLow = fileSize;
    fileHeader.sizeHigh = fileSize >> 16;
    fileHeader.reserved1 = 0;
    fileHeader.reserved2 = 0;
    fileHeader.offsetLow = 0x36;
    fileHeader.offsetHigh = 0;
    info.size = 0x28;
    info.width = 0x280;
    info.height = 0x1C0;
    info.planes = 1;
    info.bits = 0x18;
    info.compression = 0;
    info.imageSize = 0xD2000;
    info.horizontalResolution = 1;
    info.verticalResolution = 1;
    info.colorsUsed = 0;
    info.colorsImportant = 0;

    for (;;) {
        func_0019B648(buffer, D_002D0806,
                     SzFile_GetEnv((s32)D_002D07FA), nSaveCount);
        fd = func_0017FA98(buffer, 1);
        if (fd < 0) {
            break;
        }
        func_0017FD20(fd);
        nSaveCount += 1;
    }
    nSaveCount += 1;
    fd = func_0017FA98(buffer, 0x202);
    if (fd >= 0) {
        s32 y;
        u16 *row;

        func_00180348(fd, &fileHeader, 0xE);
        func_00180348(fd, &info, 0x28);
        y = 0x1BF;
        row = (u16 *)0x0408BB00;
        do {
            s32 x;
            u16 *src;
            u8 *dst;

            dst = buffer;
            x = 0;
            src = row;
            do {
                x += 1;
                dst[0] = ((*src >> 7) & 0xF8) | ((*src >> 12) & 7);
                dst[1] = ((*src >> 2) & 0xF8) | ((*src >> 7) & 7);
                dst[2] = ((*src << 3) & 0xF8) | ((*src >> 2) & 7);
                src++;
                dst += 3;
            } while (x < 0x280);
            func_00180348(fd, buffer, 0x780);
            y -= 1;
            row -= 0x280;
        } while (y >= 0);
        func_0017FD20(fd);
    }
}

typedef struct {
    f32 x, y, z, w;
} Vec4_00205440;

typedef union {
    struct {
        u16 x;
        u16 y;
    } xy;
    struct {
        u64 xy : 32;
        u64 z : 24;
        u64 f : 8;
    } bits;
} Xyz_00205440;


/* Projects point `point` to the screen with `matrix` (or the world-screen one); its screen x, y and z through
   `out` and `outZ`. Returns 0 off screen. */
s32 Ex3d_RotTransPers(s32 point, void *matrix, u16 *out, s32 *outZ) {
    extern s64 func_001A23B0(f32);
    f32 mtx[16];
    Vec4_00205440 v;
    f32 inv;

    v = *(Vec4_00205440 *)point;
    if (matrix == NULL) {
        RhView_GetWorldScreenMatrix(mtx);
        matrix = mtx;
    }
    RhGeom_PushMatrix((s32)matrix);
    v.w = 1.0f;
    RhGeom_MulMatrixVector(&v, NULL, &v);
    RhGeom_PopMatrix();
    inv = 1.0f / v.w;
    v.x *= inv;
    v.y *= inv;
    v.z *= inv;
    if (v.z < 1.0f || !(v.z <= 16777215.0f) || v.x < 0.0f || !(v.x <= 4095.0f) ||
        v.y < 0.0f || !(v.y <= 4095.0f)) {
        return 0;
    }
    ((Xyz_00205440 *)out)->xy.x = func_001A23B0(16.0f * v.x);
    ((Xyz_00205440 *)out)->xy.y = func_001A23B0(16.0f * v.y);
    ((Xyz_00205440 *)out)->bits.z = func_001A23B0(v.z);
    if (outZ != NULL) {
        *(f32 *)outZ = v.w;
    }
    return 1;
}

typedef union Vertex_00205630 {
    struct {
        u16 x;
        u16 y;
        u32 zflags;
    } coords;
    struct {
        u64 x : 16;
        u64 y : 16;
        u64 z : 24;
        u64 flags : 8;
    } bits;
} Vertex_00205630;


/* Projects `count` points with `matrix` into a draw packet, working out each one's Q. */
s32 Ex3d_RotTransPersAuto(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 *arg4) {
    extern s64 func_001A23B0(f32);
    f32 matrix[4][4];
    f32 *input = (f32 *)arg0;
    Vertex_00205630 *vertex = (Vertex_00205630 *)(arg3 + 0x10);
    u64 *tags = (u64 *)(arg3 + 8);
    u64 flags = *tags;
    s32 count = 0;
    u16 length = *(u16 *)arg3;
    f32 sum = 0.0f;
    s32 i;

    if (arg2 == 0) {
        RhView_GetWorldScreenMatrix(matrix);
        arg2 = (s32)matrix;
    }
    for (i = 0; i < length; i++, flags >>= 4) {
        if ((flags & 0xF) == 4) {
            input[3] = 1.0f;
            input += 4;
            count++;
        }
    }
    RhGeom_PushMatrix(arg2);
    RhGeom_MulMatrixVectorArray(arg1, 0, arg0, count);
    RhGeom_PopMatrix();

    flags = *tags;
    for (i = 0; i < length; i++, vertex++, flags >>= 4) {
        if ((flags & 0xF) == 4) {
            f32 *output = (f32 *)arg1;
            f32 reciprocal = 1.0f / output[3];
            output[0] *= reciprocal;
            output[1] *= reciprocal;
            output[2] *= reciprocal;
            if (output[2] < 1.0f || !(output[2] <= 16777215.0f) ||
                output[0] < 0.0f || !(output[0] <= 4095.0f) ||
                output[1] < 0.0f || !(output[1] <= 4095.0f)) {
                return 0;
            }
            vertex->coords.x = func_001A23B0(16.0f * output[0]);
            vertex->coords.y = func_001A23B0(16.0f * output[1]);
            vertex->bits.z = func_001A23B0(output[2]);
            sum += output[3];
            arg1 += 0x10;
        }
    }
    if (arg4 != NULL) {
        *arg4 = sum / (f32)count;
    }
    return 1;
}

typedef struct Packet_002058D0 {
    u16 count;
    u16 flags;
    u32 padding;
    u64 types;
    u8 data[1];
} Packet_002058D0;

typedef struct Packed_002058D0 {
    u64 xy : 32;
    u64 z : 24;
    u64 fog : 8;
} Packed_002058D0;

/* Projects points with `matrix` into `packet` with their Q (perspective) values. */
s32 Ex3d_RotTransPersAutoCalcQ(void *src MW_ALIGN(16), f32 *vertices, s32 matrix, s32 packet, s32 average) {
    extern s64 func_001A23B0(f32);
    f32 local_matrix[16];
    f32 *input = src;
    u64 *type_word = &((Packet_002058D0 *)packet)->types;
    f32 *attribute1 = NULL;
    f32 *attribute2 = NULL;
    u8 *entry = ((Packet_002058D0 *)packet)->data;
    u64 types = *type_word;
    u16 count = ((Packet_002058D0 *)packet)->count;
    f32 total = 0.0f;
    s32 scale_attributes = 0;
    s32 vertex_count = 0;
    u16 flags = ((Packet_002058D0 *)packet)->flags;
    s32 i;

    if (!(flags & 0x800) && (flags & 0x20) && (flags & 0x10)) {
        scale_attributes = 1;
    }
    if (matrix == 0) {
        RhView_GetWorldScreenMatrix(local_matrix);
        matrix = (s32)local_matrix;
    }
    for (i = 0; i < (u16)count; i++) {
        if ((types & 0xF) == 4) {
            input[3] = 1.0f;
            input += 4;
            vertex_count++;
        }
        types >>= 4;
    }
    RhGeom_PushMatrix(matrix);
    RhGeom_MulMatrixVectorArray((s32)vertices, 0, (s32)src, vertex_count);
    RhGeom_PopMatrix();
    types = *type_word;
    for (i = 0; i < (u16)count; i++, entry += 8, types >>= 4) {
        s32 kind = types & 0xF;
        switch (kind) {
        case 1:
            attribute1 = (f32 *)entry;
            break;
        case 2:
            attribute2 = (f32 *)entry;
            break;
        case 4: {
            f32 reciprocal = 1.0f / vertices[3];
            f32 x, y, z;

            if (scale_attributes && attribute1 != NULL && attribute2 != NULL) {
                attribute1[1] = reciprocal;
                attribute1 = NULL;
                attribute2[0] *= reciprocal;
                attribute2[1] *= reciprocal;
                attribute2 = NULL;
            }
            vertices[0] *= reciprocal;
            vertices[1] *= reciprocal;
            z = vertices[2] * reciprocal;
            vertices[2] = z;
            if (z < 1.0f || !(z <= 16777215.0f) ||
                (x = vertices[0]) < 0.0f || !(x <= 4095.0f) ||
                (y = vertices[1]) < 0.0f || !(y <= 4095.0f)) {
                return 0;
            }
            *(s16 *)(entry + 0) = func_001A23B0(16.0f * x);
            *(s16 *)(entry + 2) = func_001A23B0(16.0f * vertices[1]);
            ((Packed_002058D0 *)entry)->z = func_001A23B0(vertices[2]);
            total += vertices[3];
            vertices += 4;
            break;
        }
        }
    }
    if (average != 0) {
        *(f32 *)average = total / (f32)vertex_count;
    }
    return 1;
}

/* The camera's look direction (view `view`). */
f32 Ex3d_GetLookVector(s32 view) {
    f32 *temp_s0;

    temp_s0 = SzView_GetLook(0);
    SzView_GetLookVector(0, view);
    return *temp_s0;
}

/* The camera's look matrix (view `view`). */
void Ex3d_GetLookMatrix(s32 view) {
    SzView_GetLookMatrix(0, view);
}

/* The camera's look matrix with its roll (view `view`). */
void Ex3d_GetLookMatrixWithRoll(s32 view) {
    SzView_GetLookMatrixWithRoll(0, view);
}

/* The 3D point under screen point (x, y) at the card distance into `out`. */
void Ex3d_GetPointOnScreen(void *out, f32 fparg0, f32 fparg1) {
    f32 matrix[4][4];
    f32 *vector = out;

    vector[0] = fparg0;
    vector[1] = fparg1;
    vector[2] = SzView_GetScreenDistance(0);
    vector[3] = 1.0f;
    RhView_GetWorldViewMatrix(matrix);
    RhGeom_InvertMatrix(matrix, matrix);
    RhGeom_MulMatrixVector(vector, matrix, vector);
}

/* The GS depth of point `point` (moved by `bias`). */
s32 Ex3d_GetSampleZ(void *point, f32 bias) {
    f32 vector[4];
    f32 matrix1[4][4];
    f32 matrix2[4][4];

    RhView_GetWorldViewMatrix(matrix1);
    RhView_GetViewScreenMatrix(matrix2);
    ((f32 *)point)[3] = 1.0f;
    RhGeom_MulMatrixVector(vector, matrix1, point);
    vector[2] -= bias;
    RhGeom_MulMatrixVector(vector, matrix2, vector);
    if (vector[3] <= 0.0f) {
        return 0xFFFFF6;
    }
    if (vector[2] <= 0.0f) {
        return 0;
    }
    return func_001A23B0(vector[2] / vector[3]);
}

/* The perspective W of point `point` (moved by `bias`). */
f32 Ex3d_GetSampleW(void *point, f32 bias) {
    f32 vector[4];
    f32 matrix1[4][4];
    f32 matrix2[4][4];

    RhView_GetWorldViewMatrix(matrix1);
    RhView_GetViewScreenMatrix(matrix2);
    ((f32 *)point)[3] = 1.0f;
    RhGeom_MulMatrixVector(vector, matrix1, point);
    vector[2] -= bias;
    RhGeom_MulMatrixVector(vector, matrix2, vector);
    return vector[3];
}

typedef struct Vec4_00205E70 {
    f32 x, y, z, w;
} Vec4_00205E70;

extern Vec4_00205E70 D_00293D60;
extern Vec4_00205E70 D_00293D70;

/* The normal of the surface through `count` points into `normal`. */
s32 Ex3d_GetSurfaceNormal(s32 count, void *arg1, f32 *normal) {
    Vec4_00205E70 *points = arg1;
    s32 i;
    Vec4_00205E70 *p0;
    Vec4_00205E70 *p1;
    Vec4_00205E70 *p2;
    Vec4_00205E70 a;
    Vec4_00205E70 b;
    Vec4_00205E70 c;

    normal[0] = 0.0f;
    normal[1] = 0.0f;
    normal[2] = 0.0f;
    normal[3] = 0.0f;
    if (count < 3) {
        return 0;
    }
    for (i = 0; i < count; i++) {
        p0 = &points[i % count];
        p1 = &points[(i + 1) % count];
        p2 = &points[(i + 2) % count];
        a = D_00293D60;
        a.x = p1->x - p0->x;
        a.y = p1->y - p0->y;
        a.z = p1->z - p0->z;
        b = D_00293D70;
        b.x = p2->x - p1->x;
        b.y = p2->y - p1->y;
        b.z = p2->z - p1->z;
        RhGeom_OuterProduct(&c.x, &a.x, &b.x);
        normal[0] += c.x;
        normal[1] += c.y;
        normal[2] += c.z;
    }
    normal[0] /= (f32)count;
    normal[1] /= (f32)count;
    normal[2] /= (f32)count;
    RhGeom_NormalizeVector(normal);
    return 1;
}

typedef struct Vec4_00206030 {
    f32 x, y, z, w;
} Vec4_00206030;

/* The average of `count` points into `out`. */
s32 Ex3d_GetPointsAverage(s32 count, void *points, void *out) {
    Vec4_00206030 *src = points;
    Vec4_00206030 *dst = out;
    s32 i;
    f32 divisor;

    dst->x = 0.0f;
    dst->y = 0.0f;
    dst->z = 0.0f;
    dst->w = 0.0f;
    if (count == 0) {
        return 0;
    }
    for (i = 0; i < count; i++) {
        dst->x += src->x;
        dst->y += src->y;
        dst->z += src->z;
        dst->w += src->w;
        src++;
    }
    divisor = (f32) count;
    dst->x /= divisor;
    dst->y /= divisor;
    dst->z /= divisor;
    dst->w /= divisor;
    return 1;
}

/* The direction from `origin` to the average of `count` points into `out`. */
s32 Ex3d_GetViewVector(f32 *origin, s32 count, f32 *points, f32 *out) {
    s32 i;
    f32 divisor;

    out[0] = 0.0f;
    out[1] = 0.0f;
    out[2] = 0.0f;
    out[3] = 0.0f;
    if (count == 0) {
        return 0;
    }

    for (i = 0; i < count; i++) {
        out[0] += (origin != NULL ? origin[0] : 0.0f) - points[0];
        out[1] += (origin != NULL ? origin[1] : 0.0f) - points[1];
        out[2] += (origin != NULL ? origin[2] : 0.0f) - points[2];
        points += 4;
    }

    divisor = (f32) count;
    out[0] /= divisor;
    out[1] /= divisor;
    out[2] /= divisor;
    RhGeom_NormalizeVector(out);
    return 1;
}

typedef struct Point_002061F0 {
    f32 x;
    f32 y;
    f32 z;
    u8 padding[0x24];
} Point_002061F0;

/* The direction from `origin` to the average of a node's `count` points into `out`. */
s32 Ex3d_GetViewVectorForNode(f32 *origin, s32 count, void *src, f32 *out) {
    f32 divisor;
    s32 i;
    Point_002061F0 *point;

    point = src;
    out[0] = 0.0f;
    out[1] = 0.0f;
    out[2] = 0.0f;
    out[3] = 0.0f;
    if (count == 0) {
        return 0;
    }

    for (i = 0; i < count; i++, point++) {
        out[0] += (origin != NULL ? origin[0] : 0.0f) - point->x;
        out[1] += (origin != NULL ? origin[1] : 0.0f) - point->y;
        out[2] += (origin != NULL ? origin[2] : 0.0f) - point->z;
    }

    divisor = (f32)count;
    out[0] /= divisor;
    out[1] /= divisor;
    out[2] /= divisor;
    RhGeom_NormalizeVector(out);
    return 1;
}

/* The constant term of the plane through three points into `out`. */
void Ex3d_GetSurfaceC(f32 *a, f32 *b, f32 *c, f32 *out) {
    out[0] = a[1] * (b[2] - c[2])
            + b[1] * (c[2] - a[2])
            + c[1] * (a[2] - b[2]);
    out[1] = a[2] * (b[0] - c[0])
            + b[2] * (c[0] - a[0])
            + c[2] * (a[0] - b[0]);
    out[2] = a[0] * (b[1] - c[1])
            + b[0] * (c[1] - a[1])
            + c[0] * (a[1] - b[1]);
    out[3] = a[0] * (b[2] * c[1] - b[1] * c[2])
            + a[1] * (b[0] * c[2] - b[2] * c[0])
            + a[2] * (b[1] * c[0] - b[0] * c[1]);
    out[4] = func_001A6C60(out[0] * out[0]
                           + out[1] * out[1]
                           + out[2] * out[2]);
}

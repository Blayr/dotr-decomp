/* Movie player: the video input buffer. */

#include "common.h"

typedef struct {
    s32 count;
    s32 max_count;
    s32 init_count;
    s32 wait_threads;
    u32 attr;
    u32 option;
} Sema_00243EE0;

/* Sets up the video input FIFO: `data` and `tag` areas of `size`, timestamps `ts` (n of them). */
s32 viBufCreate(void *f, s32 data, u32 tag, s32 size, s32 ts, s32 n_ts) {
    Sema_00243EE0 sema;

    *(s32 *)f = data;
    *(s32 *)((u8 *)f + 4) = (tag & 0x0FFFFFFF) | 0x20000000;
    *(s32 *)((u8 *)f + 8) = size;
    *(s32 *)((u8 *)f + 0x18) = size << 11;
    *(s32 *)((u8 *)f + 0x50) = ts;
    *(s32 *)((u8 *)f + 0x54) = n_ts;
    sema.init_count = 1;
    sema.max_count = 1;
    *(s32 *)((u8 *)f + 0x40) = CreateSema(&sema);
    viBufReset(f);
    *(s64 *)((u8 *)f + 0x48) = 0;
    return 1;
}

typedef struct {
    s64 a;
    s64 b;
    s32 c;
    s32 d;
} Ent_00243F60;

typedef struct {
    u64 tag;
    u64 pad;
} Tag_00243F60;

typedef struct {
    u32 base;
    Tag_00243F60 *tags;
    s32 nTags;
    s32 f0C;
    s32 f10;
    s32 f14;
    u8 pad18[0x2C];
    s32 f44;
    u8 pad48[8];
    Ent_00243F60 *ents;
    s32 nEnts;
    s32 f58;
    s32 f5C;
} Obj_00243F60;

/* Resets the video input FIFO. */
s32 viBufReset(void *f) {
    Obj_00243F60 *obj = f;
    s32 i;

    obj->f0C = 0;
    obj->f10 = 0;
    obj->f14 = 0;
    obj->f44 = 1;
    obj->f58 = 0;
    obj->f5C = 0;
    for (i = 0; i < obj->nEnts; i++) {
        obj->ents[i].a = -1;
        obj->ents[i].b = -1;
        obj->ents[i].c = 0;
        obj->ents[i].d = 0;
    }
    for (i = 0; i < obj->nTags; i++) {
        obj->tags[i].tag = ((u64)((obj->base + i * 0x800) & 0x0FFFFFFF) << 32) | 0x30000080;
    }
    obj->tags[i].tag = ((u64)((u32)obj->tags & 0x0FFFFFFF) << 32) | 0x20000000;
    *(u32 *)D4_QWC_ADDR = 0;
    *(u32 *)D4_MADR_ADDR = obj->base & 0x0FFFFFFF;
    *(u32 *)D4_TADR_ADDR = (u32)obj->tags & 0x0FFFFFFF;
    func_001843E0();
    *(u32 *)D_ENABLEW_ADDR = *(u32 *)D_ENABLER_ADDR | 0x10000;
    *(u32 *)D4_CHCR_ADDR = 5;
    *(u32 *)D_ENABLEW_ADDR = *(u32 *)D_ENABLER_ADDR & 0xFFFEFFFF;
    func_00184428();
    return 1;
}

typedef struct Buffer_002440F0 {
    s32 base;
    s32 unknown04;
    s32 blockCount;
    s32 blockOffset;
    s32 reservedBlocks;
    s32 byteOffset;
    s32 capacity;
    u8 padding1C[0x24];
    s32 semaphore;
} Buffer_002440F0;

/* Where the next video data can go (ptr0/len0, ptr1/len1). */
void viBufBeginPut(void *f, s32 *ptr0, s32 *len0, s32 *ptr1, s32 *len1) {
    Buffer_002440F0 *buffer = f;
    s32 byteOffset;
    s32 start;
    s32 offset;
    s32 length;

    WaitSema(buffer->semaphore);
    byteOffset = buffer->byteOffset;
    start = (buffer->blockOffset + buffer->reservedBlocks) << 11;
    offset = (start + byteOffset) % buffer->capacity;
    length = ((buffer->blockCount - 2 - buffer->reservedBlocks) << 11) - byteOffset;
    if (buffer->capacity - offset >= length) {
        *ptr0 = buffer->base + offset;
        *len0 = length;
        *ptr1 = 0;
        *len1 = 0;
    } else {
        *ptr0 = buffer->base + offset;
        *len0 = buffer->capacity - offset;
        *ptr1 = buffer->base;
        *len1 = length - (buffer->capacity - offset);
    }
    SignalSema(buffer->semaphore);
}

typedef struct Counter_002441F0 {
    u8 pad0[0x14];
    s32 count;
    u8 pad18[0x28];
    s32 semaphore;
    u8 pad44[4];
    s64 total;
} Counter_002441F0;

/* Marks `size` bytes of video data as put. */
void viBufEndPut(void *f, s32 size) {
    Counter_002441F0 *counter = f;

    WaitSema(counter->semaphore);
    counter->count += size;
    counter->total += size;
    SignalSema(counter->semaphore);
}

typedef struct Ring_00244250 {
    u8 *data;
    u8 *tags;
    s32 count;
    s32 read;
    s32 used;
    s32 bytes;
    u8 pad[0x28];
    s32 sema;
    s32 active;
} Ring_00244250;

extern s8 D_0030F890;

/* A DMA tag. */
static inline u64 tag_00244250(u32 address, u32 id) {
    return ((u64)address << 32) | ((u64)id << 28) | 0x80;
}

/* Feeds the video input FIFO's data to the IPU by DMA. */
s32 viBufAddDMA(void *f) {
    s32 chcr;
    s32 patched;
    u32 current;
    s32 count;
    s32 consumed;
    s32 head;
    s32 index;
    s32 blocks;
    s32 last;
    s32 i;
    s32 id;
    Ring_00244250 *ring = f;

    patched = 0;
    WaitSema(ring->sema);
    if (ring->active == 0) {
        ErrMessage(&D_0030F890);
        return 0;
    }

    func_001843E0();
    *(volatile s32 *)D_ENABLEW_ADDR = *(volatile s32 *)D_ENABLER_ADDR | 0x10000;
    *(volatile s32 *)D4_CHCR_ADDR = 5;
    *(volatile s32 *)D_ENABLEW_ADDR = *(volatile s32 *)D_ENABLER_ADDR & 0xFFFEFFFF;
    func_00184428();
    chcr = *(volatile s32 *)D4_CHCR_ADDR;
    count = ring->count;
    current = *(volatile s32 *)D4_MADR_ADDR;
    if (current == ((u32)(ring->tags + (count + 1) * 16) & 0x0FFFFFFF)) {
        current = 0;
    } else {
        current = (u32)(current - (u32)ring->data) >> 11;
    }
    head = ring->read;
    consumed = (s32)(current + count - head) % count;
    ring->read = (head + consumed) % count;
    ring->used -= consumed;
    index = (ring->read + ring->used) % ring->count;
    blocks = ring->bytes >> 11;
    ring->bytes %= 2048;

    if (blocks > 0) {
        last = (ring->count + (ring->read + ring->used - 1)) % ring->count;
        patched = 1;
        *(u64 *)(ring->tags + last * 16) = tag_00244250((u32)ring->data + (last << 11), 3);
    }
    for (i = 0; i < blocks; i++) {
        if (i == blocks - 1) {
            id = 0;
        } else {
            id = 3;
        }
        *(u64 *)(ring->tags + index * 16) = tag_00244250((u32)ring->data + (index << 11), id);
        index = (index + 1) % ring->count;
    }

    ring->used += blocks;
    if (ring->used != 0) {
        if (patched != 0) {
            chcr = (chcr & 0x0FFFFFFF) | 0x30000000;
        }
        func_001843E0();
        *(volatile s32 *)D_ENABLEW_ADDR = *(volatile s32 *)D_ENABLER_ADDR | 0x10000;
        *(volatile s32 *)D4_CHCR_ADDR = chcr | 0x100;
        *(volatile s32 *)D_ENABLEW_ADDR = *(volatile s32 *)D_ENABLER_ADDR & 0xFFFEFFFF;
        func_00184428();
    }
    SignalSema(ring->sema);
    return 1;
}

/* Stops the video input DMA. */
s32 viBufStopDMA(u8 *f) {
    WaitSema(*(s32 *)(f + 0x40));
    *(s32 *)(f + 0x44) = 0;
    func_001843E0();
    *(volatile u32 *)D_ENABLEW_ADDR = *(volatile u32 *)D_ENABLER_ADDR | 0x10000;
    *(volatile u32 *)D4_CHCR_ADDR = 5;
    *(volatile u32 *)D_ENABLEW_ADDR = *(volatile u32 *)D_ENABLER_ADDR & 0xFFFEFFFF;
    func_00184428();
    *(s32 *)(f + 0x1C) = *(volatile u32 *)D4_MADR_ADDR;
    *(s32 *)(f + 0x20) = *(volatile u32 *)D4_TADR_ADDR;
    *(s32 *)(f + 0x24) = *(volatile u32 *)D4_QWC_ADDR;
    *(s32 *)(f + 0x28) = *(volatile u32 *)D4_CHCR_ADDR;
    do {
    } while (*(volatile u32 *)IPU_CTRL_ADDR & 0xF0);
    func_001843E0();
    *(volatile u32 *)D_ENABLEW_ADDR = *(volatile u32 *)D_ENABLER_ADDR | 0x10000;
    *(volatile u32 *)D3_CHCR_ADDR = 0;
    *(volatile u32 *)D_ENABLEW_ADDR = *(volatile u32 *)D_ENABLER_ADDR & 0xFFFEFFFF;
    func_00184428();
    *(s32 *)(f + 0x2C) = *(volatile u32 *)D3_MADR_ADDR;
    *(s32 *)(f + 0x30) = *(volatile u32 *)D3_QWC_ADDR;
    *(s32 *)(f + 0x34) = *(volatile u32 *)D3_CHCR_ADDR;
    *(s32 *)(f + 0x38) = *(volatile u32 *)IPU_BP_ADDR;
    *(s32 *)(f + 0x3C) = *(volatile u32 *)IPU_CTRL_ADDR;
    SignalSema(*(s32 *)(f + 0x40));
    return 1;
}

struct DotrSoundStream {
    int unknown_00;
    int unknown_04;
    int unknown_08;
    int unknown_0c;
    int unknown_10;
    int unknown_14;
    int unknown_18;
    int unknown_1c[9];
    int unknown_40;
    int unknown_44;
    long unknown_48;
    int unknown_50;
    int unknown_54;
    int unknown_58;
    int unknown_5c;
};
#define DOTR_SOUND_REG(addr) (*(volatile int *)(addr))
extern void func_001843E0_b(void);
extern void func_00184428_b(void);
struct DotrSoundViBuf {
    unsigned data;
    unsigned tag;
    int n;
    int dmaStart;
    int dmaN;
    int readBytes;
    int buffSize;
    unsigned d4madr;
    unsigned d4tadr;
    unsigned d4qwc;
    unsigned d4chcr;
    unsigned d3madr;
    unsigned d3qwc;
    unsigned d3chcr;
    unsigned ipubp;
    unsigned ipuctrl;
    int sema;
    int isActive;
};
#define VIBUF_ELM_SIZE 2048
#define DmaAddr(v) ((unsigned)(v) & 0x0fffffff)
#define DataAddr(f, i) ((f)->data + VIBUF_ELM_SIZE * (i))
#define TagAddr(f, i) ((f)->tag + 16 * (i))
#define IsInRegion(i, start, len, n) (0 <= ((i) + (n) - (start)) % (n) && ((i) + (n) - (start)) % (n) < (len))
/* The FIFO index of a DMA address. */
static inline int getFIFOindex(struct DotrSoundViBuf *f, unsigned addr)
{
    if (addr == DmaAddr(TagAddr(f, f->n + 1))) {
        return 0;
    } else {
        return (addr - f->data) / VIBUF_ELM_SIZE;
    }
}
/* Sets DMA channel 3's control register. */
static inline void setD3_CHCR(unsigned val)
{
    func_001843E0_b();
    DOTR_SOUND_REG(0x1000f590) = DOTR_SOUND_REG(0x1000f520) | 0x10000;
    DOTR_SOUND_REG(0x1000b000) = val;
    DOTR_SOUND_REG(0x1000f590) = DOTR_SOUND_REG(0x1000f520) & ~0x10000;
    func_00184428_b();
}
/* Sets DMA channel 4's control register. */
static inline void setD4_CHCR(unsigned val)
{
    func_001843E0_b();
    DOTR_SOUND_REG(0x1000f590) = DOTR_SOUND_REG(0x1000f520) | 0x10000;
    DOTR_SOUND_REG(0x1000b400) = val;
    DOTR_SOUND_REG(0x1000f590) = DOTR_SOUND_REG(0x1000f520) & ~0x10000;
    func_00184428_b();
}

/* Restarts the video input DMA where it stopped. */
int viBufRestartDMA(void *p_v)
{
    struct DotrSoundStream * p = p_v;
    struct DotrSoundViBuf *f = (struct DotrSoundViBuf *)p;
    int bp = f->ipubp & 0x7f;
    int fp = (f->ipubp >> 16) & 3;
    int ifc = (f->ipubp >> 8) & 0xf;
    unsigned d4madr_next = f->d4madr - ((fp + ifc) << 4);
    unsigned d4qwc_next = f->d4qwc + (fp + ifc);
    unsigned d4chcr_next = f->d4chcr | 0x100;
    unsigned d3chcr_next;
    unsigned d4tadr_next = f->d4tadr;
    int index;
    int index_next;
    int id;

    WaitSema(f->sema);
    if (d4madr_next < f->data) {
        d4qwc_next = (DataAddr(f, 0) - d4madr_next) >> 4;
        d4madr_next += f->n * 2048;
        d4tadr_next = DmaAddr(TagAddr(f, 0));
        id = (f->d4madr == DataAddr(f, 0) || f->d4madr == DataAddr(f, f->n)) ? 0 : 3;
        d4chcr_next = (f->d4chcr & 0x0fffffff) | (id << 28) | 0x100;
        if (!IsInRegion(0, f->dmaStart, f->dmaN, f->n)) {
            f->dmaStart = f->n - 1;
            f->dmaN++;
        }
    } else if ((index = getFIFOindex(f, f->d4madr)) != (index_next = getFIFOindex(f, d4madr_next))) {
        d4tadr_next = DmaAddr(TagAddr(f, index));
        d4qwc_next = (DataAddr(f, index) - d4madr_next) >> 4;
        id = (f->data + (f->d4madr - f->data) % (f->n * 2048) == DataAddr(f, (f->dmaStart + f->dmaN) % f->n)) ? 0 : 3;
        d4chcr_next = (f->d4chcr & 0x0fffffff) | (id << 28) | 0x100;
        if (!IsInRegion(index_next, f->dmaStart, f->dmaN, f->n)) {
            f->dmaStart = index_next;
            f->dmaN++;
        }
    }
    if (f->d3madr && f->d3qwc) {
        DOTR_SOUND_REG(0x1000b010) = f->d3madr;
        DOTR_SOUND_REG(0x1000b020) = f->d3qwc;
        d3chcr_next = f->d3chcr | 0x100;
        setD3_CHCR(d3chcr_next);
    }
    if (f->dmaN) {
        while (DOTR_SOUND_REG(0x10002010) < 0) {
        }
        DOTR_SOUND_REG(0x10002000) = bp;
        while (DOTR_SOUND_REG(0x10002010) < 0) {
        }
    }
    DOTR_SOUND_REG(0x1000b410) = d4madr_next;
    DOTR_SOUND_REG(0x1000b430) = d4tadr_next;
    DOTR_SOUND_REG(0x1000b420) = d4qwc_next;
    if (f->dmaN) {
        setD4_CHCR(d4chcr_next);
    }
    DOTR_SOUND_REG(0x10002010) = f->ipuctrl;
    f->isActive = 1;
    SignalSema(f->sema);
    return 1;
}
#undef DOTR_SOUND_REG
#undef VIBUF_ELM_SIZE
#undef DmaAddr
#undef DataAddr
#undef TagAddr
#undef IsInRegion

/* Frees the video input FIFO. */
s32 viBufDelete(void *f) {
    func_001843E0();
    *(volatile u32 *)D_ENABLEW_ADDR = *(volatile u32 *)D_ENABLER_ADDR | 0x10000;
    *(volatile u32 *)D4_CHCR_ADDR = 5;
    *(volatile u32 *)D_ENABLEW_ADDR = *(volatile u32 *)D_ENABLER_ADDR & 0xFFFEFFFF;
    func_00184428();
    *(volatile u32 *)D4_QWC_ADDR = 0;
    *(volatile u32 *)D4_MADR_ADDR = 0;
    *(volatile u32 *)D4_TADR_ADDR = 0;
    DeleteSema(*(s32 *)((u8 *)f + 0x40));
    return 1;
}

typedef struct Data_00244AD0 {
    u8 pad_00[0x10];
    s32 field_10;
    s32 field_14;
    u8 pad_18[0x28];
    s32 field_40;
} Data_00244AD0;

/* How much data the video input FIFO holds. */
s32 viBufCount(void *f) {
    Data_00244AD0 *data = f;
    s32 temp_s0;

    WaitSema(data->field_40);
    temp_s0 = data->field_14 + (data->field_10 << 11);
    SignalSema(data->field_40);
    return temp_s0;
}

typedef struct State_00244B20 {
    u8 pad_00[0x14];
    s32 field_14;
    u8 pad_18[0x28];
    s32 field_40;
} State_00244B20;

/* Empties the video input FIFO. */
void viBufFlush(void *f) {
    State_00244B20 *state = f;

    WaitSema(state->field_40);
    state->field_14 = ((state->field_14 + 0x7FF) >> 11) << 11;
    SignalSema(state->field_40);
}

typedef struct Entry_00244B70 {
    s64 first;
    s64 second;
    s32 position;
    s32 length;
} Entry_00244B70;

typedef struct Queue_00244B70 {
    u8 pad0[8];
    s32 blocks;
    u8 padC[0x44];
    Entry_00244B70 *entries;
    s32 capacity;
    s32 count;
    s32 tail;
} Queue_00244B70;

/* Clamps a count. */
static inline s32 clamp_00244B70(s32 count) {
    if (count < 0) {
        return 0;
    }
    return count;
}

/* Moves the video timestamps to `new_ts`. */
s32 viBufModifyPts(void *f, void *new_ts) {
    Queue_00244B70 *queue = f;
    Entry_00244B70 *request = new_ts;
    s32 index;
    s32 repeat;
    s32 bufferSize;
    Entry_00244B70 *entry;
    s32 requestLength;
    s32 requestPosition;
    s32 position;
    s32 amount;
    s32 end;

    repeat = 1;
    index = (queue->capacity + (queue->tail - queue->count)) % queue->capacity;
    bufferSize = queue->blocks << 11;
    if (queue->count > 0) {
        do {
            entry = &queue->entries[index];
            amount = entry->length;
            if (amount == 0) {
                break;
            }
            requestLength = request->length;
            if (requestLength == 0) {
                break;
            }
            position = entry->position;
            requestPosition = request->position;
            if ((position + bufferSize - requestPosition) % bufferSize < requestLength) {
                end = requestPosition + requestLength - position;
                amount = amount < end ? amount : end;
                entry->position = (position + amount) % bufferSize;
                entry->length -= amount;
                if (entry->length == 0) {
                    if (entry->first >= 0) {
                        entry->first = -1;
                        entry->second = -1;
                        entry->position = 0;
                        entry->length = 0;
                    }
                    queue->count = clamp_00244B70(queue->count - 1);
                }
            } else {
                repeat = 0;
            }
            index = (index + 1) % queue->capacity;
        } while (repeat != 0);
    }
    return 0;
}

typedef struct Record_00244CB0 {
    s64 value0;
    s64 value8;
    s32 value10;
    s32 value14;
} Record_00244CB0;

typedef struct Queue_00244CB0 {
    u8 padding0[0x40];
    s32 semaphore;
    u8 padding44[0xC];
    Record_00244CB0 *records;
    s32 capacity;
    s32 count;
    s32 tail;
} Queue_00244CB0;

/* Adds a video timestamp. */
s32 viBufPutTs(void *f, void *ts) {
    Record_00244CB0 *record = ts;
    Queue_00244CB0 *queue = f;
    s32 result = 0;

    WaitSema(queue->semaphore);
    if (queue->count < queue->capacity) {
        viBufModifyPts(queue, record);
        if (record->value0 >= 0 || record->value8 >= 0) {
            queue->records[queue->tail].value0 = record->value0;
            queue->records[queue->tail].value8 = record->value8;
            queue->records[queue->tail].value10 = record->value10;
            queue->records[queue->tail].value14 = record->value14;
            queue->count++;
            queue->tail = (queue->tail + 1) % queue->capacity;
        }
        result = 1;
    }
    SignalSema(queue->semaphore);
    return result;
}

typedef struct TimeStamp_00244DE0 {
    s64 pts;
    s64 dts;
    s32 pos;
    s32 len;
} TimeStamp_00244DE0;

typedef struct ViBuf_00244DE0 {
    u32 data;
    u32 tag;
    s32 n;
    s32 dmaStart;
    s32 dmaN;
    s32 readBytes;
    s32 buffSize;
    u32 d4madr;
    u32 d4tadr;
    u32 d4qwc;
    u32 d4chcr;
    u32 d3madr;
    u32 d3qwc;
    u32 d3chcr;
    u32 ipubp;
    u32 ipuctrl;
    s32 sema;
    s32 isActive;
    s64 totalcount;
    TimeStamp_00244DE0 *ts;
    s32 n_ts;
    s32 count_ts;
    s32 wt_ts;
} ViBuf_00244DE0;
#pragma opt_dead_assignments off

/* Takes the next video timestamp. */
s32 viBufGetTs(void *fIn, void *tsIn)
{
    ViBuf_00244DE0 *f;
    s32 count;
    u32 ipubp;
    u32 d4madr;
    s32 i;
    s32 bp;
    s32 datasize;
    u32 fp;
    u32 ifc;
    TimeStamp_00244DE0 *ts;
    s32 isEnd;
    s32 wt;
    s32 stop;
    f = fIn;
    ts = tsIn;

    d4madr = *(volatile u32 *)D4_MADR_ADDR;
    isEnd = 0;
    ipubp = *(volatile u32 *)IPU_BP_ADDR;
    bp = f->ipubp & 0x7F;
    fp = (ipubp >> 16) & 3;
    ifc = (ipubp >> 8) & 0xF;
    datasize = f->n << 11;
    WaitSema(f->sema);
    stop = d4madr - ((fp + ifc) << 4);
    ts->pts = -1;
    ts->dts = -1;
    count = f->count_ts;
    stop = (stop + (bp >> 3) + datasize - f->data) % datasize;
    wt = f->wt_ts;
    for (i = 0; i < count && !isEnd; i++) {
        s32 index;
        index = (wt - count + f->n_ts + i) % f->n_ts;
        if ((stop + datasize - f->ts[index].pos) % datasize < f->ts[index].len) {
            ts->pts = f->ts[index].pts;
            ts->dts = f->ts[index].dts;
            f->ts[index].pts = -1;
            f->ts[index].dts = -1;
            isEnd = 1;
            f->count_ts -= (f->count_ts <= 0) ? f->count_ts : 1;
        }
    }
    SignalSema(f->sema);
    return 1;
}
#pragma opt_dead_assignments reset

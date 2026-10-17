#include "common.h"

/* The movie video decoder's state. */
s32 videoDecGetState(void *vd) {
    return *(s32 *)((u8 *)vd + 0xA8);
}

typedef struct Values_00245160 {
    s64 first;
    s64 second;
    s32 offset;
    s32 fourth;
} Values_00245160;

extern u8 D_003506C8[];

/* Records a video timestamp (pts, dts) for stream position `pos` of `len` bytes. */
void videoDecPutTs(void *vd, s64 pts, s64 dts, s32 pos, s32 len) {
    Values_00245160 values;

    values.first = pts;
    values.second = dts;
    values.offset = pos - *(s32 *)((u8 *)vd + 0x48);
    values.fourth = len;
    viBufPutTs(D_003506C8, &values);
}

typedef struct {
    u8 pad00[0x48];
    u8 unk48[0x60];
    s32 unkA8;
} Obj_002451A0;

typedef struct {
    f32 v;
} Flt_002451A0;

extern Flt_002451A0 D_0029B300;
extern u8 D_003506C8[];

/* Flushes the movie video decoder's data. */
s32 videoDecFlush(void *vd) {
    Obj_002451A0 *p = (Obj_002451A0 *)vd;
    s32 sp2C;
    s32 sp30;
    Flt_002451A0 sp34;
    s32 sp38;
    s32 sp3C;

    sp34 = D_0029B300;
    viBufBeginPut(p->unk48, &sp2C, &sp38, &sp30, &sp3C);
    if ((sp38 + sp3C) < 4) {
        return 0;
    }
    viBufEndPut(D_003506C8, cpy2area((sp2C & 0xFFFFFFF) | 0x20000000, sp38, (sp30 & 0xFFFFFFF) | 0x20000000, sp3C, &sp34, 4, 0, 0));
    viBufFlush(p->unk48);
    if (p->unkA8 == 0) {
        p->unkA8 = 2;
    }
    return 1;
}

/* Whether the movie video decoder has flushed. */
s32 videoDecIsFlushed(void *vd) {
    s32 result;

    result = 0;
    if (viBufCount((u8 *)vd + 0x48) == 0) {
        if (sceMpegIsRefBuffEmpty(vd) != 0) {
            result = 1;
        }
    }
    return result;
}

/* The movie video decoder's thread: decodes pictures until the end. */
void videoDecMain(void *vd) {
    viBufReset((u8 *)vd + 0x48);
    voBufReset(voBuf);
    decBs0(vd);
    do {

    } while (D_0035060C != 0);
    *(s32 *)((u8 *)vd + 0xA8) = 3;
}

extern int func_00199B50_b(const char *format, ...);
typedef int DotrSoundAddress;
struct DotrSoundBig {
    int state;
    unsigned char unknown_04[60];
    unsigned int tags[2][0x99c0]; 
};
struct DotrSoundBigQueue {
    unsigned char (*images)[0x195000]; 
    struct DotrSoundBig *items;
    int index;
    int count;
    int capacity;
};
struct DotrSoundVideoDec {
    int width;
    int height;
    int frame_count;
    int unknown_0c[39];
    int state;
};
extern struct DotrSoundBigQueue D_00350600_b;
extern char D_0030F8B0[];
extern char D_0030F8C8[];
extern int func_0018EE78_b(struct DotrSoundVideoDec *dec);
extern void func_00242CF0_b(DotrSoundAddress text);
extern void func_00241E80_b(unsigned int *tags, void *image, int index, int w, int h);

/* Decodes the movie's video stream (one call of the MPEG library). */
int decBs0(void *dec_v)
{
    struct DotrSoundVideoDec * dec = dec_v;
    int ret;
    DotrSoundAddress data;
    int i;
    int w;
    int h;

    ret = 1;
    while (sceMpegIsEnd(dec) == 0) {
        if (dec->state == 1) {
            ret = -1;
            func_00199B50_b(D_0030F8B0);
            break;
        }
        while ((data = voBufGetData(&D_00350600_b)) == 0) {
            switchThread();
        }
        if (sceMpegGetPicture(dec, data, 0x654) < 0) {
            func_00242CF0_b((DotrSoundAddress)D_0030F8C8);
        }
        if (dec->frame_count == 0) {
            w = dec->width;
            h = dec->height;
            for (i = 0; i < D_00350600_b.capacity; i++) {
                func_00241E80_b(D_00350600_b.items[i].tags[0], D_00350600_b.images[i], 0, w, h);
                func_00241E80_b(D_00350600_b.items[i].tags[1], D_00350600_b.images[i], 1, w, h);
            }
        }
        voBufIncCount(&D_00350600_b);
        switchThread();
    }
    func_0018EE78_b(dec);
    return ret;
}

/* The MPEG library's error callback. */
s32 mpegError(void *mp, void *data) {
    func_00199B50(&D_0030F8E9, *(s32 *)((u8 *)data + 4));
    return 1;
}

/* The MPEG library's no-data callback: waits for input. */
s32 mpegNodata(void) {
    switchThread();
    viBufAddDMA(D_003506C8);
    return 1;
}

/* The MPEG library's stop-DMA callback. */
s32 mpegStopDMA(void) {
    viBufStopDMA(D_003506C8);
    return 1;
}

/* The MPEG library's restart-DMA callback. */
s32 mpegRestartDMA(void) {
    viBufRestartDMA(D_003506C8);
    return 1;
}

typedef struct Entry_002455E0 {
    s64 values[2];
    s32 offset;
    s32 size;
} Entry_002455E0;


/* The MPEG library's timestamp callback: hands it the next video timestamp. */
s32 mpegTS(s32 mp, void *cbData) {
    Entry_002455E0 entry;

    viBufGetTs(D_003506C8, &entry);
    *(s64 *)((u8 *)cbData + 8) = entry.values[0];
    *(s64 *)((u8 *)cbData + 0x10) = entry.values[1];
    return 1;
}

/* Copies two source areas into two destination areas (the decoded pictures' ring); returns the size copied, 0 if
   it does not fit. */
s32 cpy2area(s32 pd0, s32 d0, s32 pd1, s32 d1,
                  void *ps0, s32 s0, s32 ps1, s32 s1) {
    s32 rest;
    s32 total;

    total = s0 + s1;
    if ((d0 + d1) < total) {
        return 0;
    }
    if (s0 >= d0) {
        func_00198790((u8 *)pd0, ps0, d0);
        func_00198790((u8 *)pd1, (u8 *)ps0 + d0, s0 - d0);
        func_00198790(((u8 *)pd1 + s0) - d0, (u8 *)ps1, s1);
    } else {
        rest = d0 - s0;
        if (s1 >= rest) {
            func_00198790((u8 *)pd0, ps0, s0);
            func_00198790((u8 *)pd0 + s0, (u8 *)ps1, rest);
            func_00198790((u8 *)pd1, ((u8 *)ps1 + d0) - s0, s1 - rest);
        } else {
            func_00198790((u8 *)pd0, ps0, s0);
            func_00198790((u8 *)pd0 + s0, (u8 *)ps1, s1);
        }
    }
    return total;
}

typedef struct State_00245770 {
    s32 value;
    u8 *entries;
    s32 field8;
    s32 fieldC;
    s32 count;
} State_00245770;

/* Sets up the decoded-picture buffer: `count` pictures at `data`, with `tag`. */
void voBufCreate(void *f, s32 tag, void *data, s32 count) {
    State_00245770 *state = f;
    s32 *temp_a2;
    s32 i;

    state->value = tag;
    state->entries = data;
    state->count = count;
    state->fieldC = 0;
    state->field8 = 0;
    for (i = 0; i < count; i++) {
        temp_a2 = (s32 *)(state->entries + i * 0x4CE40);
        *temp_a2 = 0;
    }
}

/* Frees the decoded-picture buffer (nothing to do). */
void voBufDelete(void) {

}

/* Empties the decoded-picture buffer. */
void voBufReset(void *f) {
    *(s32 *)((u8 *)f + 0xC) = 0;
    *(s32 *)((u8 *)f + 0x8) = 0;
}

typedef struct {
    u8 pad[0xC];
    s32 field_C;
    s32 field_10;
} Fields_002457E0;

/* Whether the decoded-picture buffer is full. */
s32 voBufIsFull(void *f) {
    return ((Fields_002457E0 *)f)->field_C == ((Fields_002457E0 *)f)->field_10;
}

typedef struct {
    s32 unk0;
    u8 *data;
    s32 index;
    s32 count;
    s32 capacity;
} Queue_00245800;


/* Adds one decoded picture. */
void voBufIncCount(void *f) {
    Queue_00245800 *queue = (Queue_00245800 *)f;

    func_001843E0();
    *(s32 *)(queue->data + queue->index * 0x4CE40) = 2;
    queue->count++;
    queue->index = (queue->index + 1) % queue->capacity;
    func_00184428();
}

typedef struct State_00245890 {
    s32 base;
    s32 unk4;
    s32 index;
    s32 current;
    s32 end;
} State_00245890;

/* Whether the decoded-picture buffer is empty. */
static inline u8 empty_00245890(void *arg0) {
    State_00245890 *state = arg0;

    return state->current == state->end;
}

/* The next decoded picture, or 0. */
s32 voBufGetData(void *f) {
    State_00245890 *state = f;

    if (empty_00245890(state)) {
        return 0;
    }
    return state->base + (state->index * 0x195000);
}

typedef struct Buffer_002458E0 {
    s32 unk0;
    s32 base;
    s32 index;
    volatile s32 count;
    s32 capacity;
} Buffer_002458E0;

/* Whether the decoded-picture buffer is empty. */
static inline u8 is_empty_002458E0(void *arg0) {
    return ((Buffer_002458E0 *)arg0)->count == 0;
}

/* The next decoded picture's DMA tag, or 0. */
s32 voBufGetTag(void *f) {
    s32 capacity;
    Buffer_002458E0 *buffer = f;

    if (is_empty_002458E0(f)) {
        return 0;
    }
    capacity = buffer->capacity;
    return buffer->base + ((capacity + (buffer->index - buffer->count)) % capacity) * 0x4CE40;
}

typedef struct Counter_00245960 {
    u8 pad[0xC];
    volatile s32 count;
} Counter_00245960;

/* Drops the oldest decoded picture. */
void voBufDecCount(void *f) {
    Counter_00245960 *counter = f;

    if (counter->count > 0) {
        counter->count--;
    }
}

typedef struct Quad_00245980 {
    s16 x;
    s16 y;
    s16 z;
    s16 w;
} Quad_00245980;

extern Quad_00245980 **faceSetIndex[]; /* original: gpShFaceIndex */

/* The texture rectangle of part `part` of face set `face` into `out`. */
void ShAnime_GetPartsRect(s32 face, s32 part, void *out) {
    *(Quad_00245980 *)out = (*faceSetIndex[(u8)face])[(u8)part];
}

typedef struct Name_002459D0 {
    u8 text[8];
} Name_002459D0;

/* Pattern `pattern` of face set `face` into `out`. */
void ShAnime_GetPatInfo(u8 face, u8 pattern, void *out) {
    *(Name_002459D0 *)out = ((Name_002459D0 **)faceSetIndex[face])[1][pattern];
}

typedef struct Record_00245A30 {
    s16 x;
    s16 y;
    s16 width;
    s16 height;
} Record_00245A30;

typedef struct Data_00245A30 {
    s32 unk0;
    u8 (*indices)[8];
    Record_00245A30 *records;
} Data_00245A30;

/* The fixed record of animation `anim` of face set `face`, `step` links on, into `out`. */
void ShAnime_GetFixInfo(s32 face, s32 anim, s32 step, void *out) {
    extern struct Quad_00245980 **faceSetIndex[];
    u8 link;
    u8 next;
    Record_00245A30 *records;
    s32 i;

    i = 0;
    link = ((Data_00245A30 *)faceSetIndex[face & 0xFF])->indices[anim & 0xFF][1];
    if (step != 0) {
        records = ((Data_00245A30 *)faceSetIndex[face & 0xFF])->records;
        while (i != (step & 0xFF)) {
            next = *(u8 *)&records[link & 0xFF];
            if (next == 0 || next == 0xFF) {
                break;
            }
            i += 1;
            link = next & 0xFF;
        }
    }
    *(Record_00245A30 *)out = ((Data_00245A30 *)faceSetIndex[face & 0xFF])->records[link & 0xFF];
}

typedef struct Record_00245AE0 {
    s16 x;
    s16 y;
    s16 width;
    s16 height;
} Record_00245AE0;

typedef struct Data_00245AE0 {
    s32 unk0;
    u8 (*indices)[8];
    union {
        Record_00245AE0 *records;
        u8 (*links)[8];
    } u;
} Data_00245AE0;

/* The animation record of animation `anim` of face set `face`, `step` and then `frame` links on, into `out`. */
void ShAnime_GetAnmDat(s32 face, s32 anim, s32 step, s32 frame, void *out) {
    extern struct Quad_00245980 **faceSetIndex[];
    Record_00245AE0 *table;
    u8 link;
    u8 next;
    Record_00245AE0 *records;
    s32 i;
    s32 count;

    i = 0;
    link = ((Data_00245AE0 *)faceSetIndex[face & 0xFF])->indices[anim & 0xFF][1];
    if (step != 0) {
        records = ((Data_00245AE0 *)faceSetIndex[face & 0xFF])->u.records;
        while (i != (step & 0xFF)) {
            next = *(u8 *)&records[link & 0xFF];
            if (next == 0 || next == 0xFF) {
                break;
            }
            i += 1;
            link = next & 0xFF;
        }
    }
    i = ((Data_00245AE0 *)faceSetIndex[face & 0xFF])->u.links[link & 0xFF][6];
    table = ((Data_00245AE0 *)faceSetIndex[face & 0xFF])->u.records;
    count = 0;
    if (frame != 0) {
        while (count != (frame & 0xFF)) {
            next = *(u8 *)&table[i & 0xFF];
            if (next == 0 || next == 0xFF) {
                break;
            }
            count += 1;
            i = next & 0xFF;
        }
    }
    *(Record_00245AE0 *)out = table[i & 0xFF];
}

typedef struct Request_00245BE0 {
    u8 slot;
    u8 a;
    u8 b;
    u8 c;
    u16 d;
    u16 e;
} Request_00245BE0;

typedef struct Slot_00245BE0 {
    s32 value;
    u8 a;
    u8 b;
    u8 c;
    u8 pad7[4];
    u8 x[16];
    u8 y[16];
    u8 pad2B;
    u16 d;
    u16 e;
    u8 pad30[4];
} Slot_00245BE0;

/* Shows (or updates) a duelist face from request `reqIn` in one of the 8 face slots. Returns 0 if none is free. */
s32 ShFace_Request(void *reqIn) {
    Request_00245BE0 *req = reqIn;
    Slot_00245BE0 *entry;
    s32 i;
    extern Slot_00245BE0 faceSlots[];

    if (req->slot == 0xFF) {
        for (i = 0; i < 8; i++) {
            if (faceSlots[i].value == 0) {
                break;
            }
        }
        if (i == 8) {
            return 0;
        }
        req->slot = i;
        faceSlots[req->slot].value = 1;
        faceSlots[req->slot].b = 0xFF;
    }
    entry = &faceSlots[req->slot];
    if (entry->value == 0) {
        return 0;
    }
    if (entry->b != req->b) {
        for (i = 0; i < 16; i++) {
            faceSlots[req->slot].y[i] = 0;
            faceSlots[req->slot].x[i] = 0;
        }
    }
    entry->a = req->a;
    entry->b = req->b;
    entry->c = req->c;
    entry->d = req->d;
    entry->e = req->e;
    return 1;
}

typedef struct {
    s32 value;
    u8 padding[0x30];
} Entry_00245D80;

extern Entry_00245D80 faceSlots[]; /* original: gSh_Face */

/* Closes the face slot of request `req`. */
void ShFace_Close(u8 *req) {
    faceSlots[*req].value = 0;
}

typedef struct {
    u16 count;
    u16 flags;
    u32 padding;
    u64 registers;
} Tag_00245DB0;

typedef struct {
    u64 u : 14;
    u64 pad0 : 2;
    u64 v : 14;
    u64 pad1 : 34;
} UV_00245DB0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} XYZ_00245DB0;

typedef struct {
    u64 uv;
    XYZ_00245DB0 xyz;
} Vertex_00245DB0;

typedef struct {
    u64 tag[2];
    u8 r, g, b, a;
    f32 q;
    Vertex_00245DB0 vertex[4];
    u64 state[4];
} Packet_00245DB0;

typedef struct {
    u8 pad0[0x2C];
    u16 x;
    u16 y;
    void *texture;
} Object_00245DB0;

/* Draws one part `rectIn` of a face at its position plus (dx, dy). */
void ShFace_Prim(void *face, void *rectIn, s32 dx, s32 dy) {
    extern s32 facePacket;
    Object_00245DB0 *object = face;
    u16 *rect = rectIn;
    u32 shift;
    u16 y;
    Packet_00245DB0 packet __attribute__((aligned(8)));

    ((Tag_00245DB0 *)packet.tag)->flags = 0x24;
    ((Tag_00245DB0 *)packet.tag)->count = 9;
    ((Tag_00245DB0 *)packet.tag)->registers = 0x424242421ULL;
    ((Tag_00245DB0 *)packet.tag)->padding = 0;
    shift = 4;
    packet.r = packet.g = packet.b = packet.a = 0x80;
    packet.q = 1.0f;
    y = object->y + 0x720;
    packet.vertex[2].xyz.x = packet.vertex[0].xyz.x =
        ((object->x + 0x6C0) << 4) + (dx << shift);
    packet.vertex[1].xyz.y = packet.vertex[0].xyz.y = (y << 4) + (dy << shift);
    packet.vertex[3].xyz.x = packet.vertex[1].xyz.x =
        packet.vertex[0].xyz.x + ((rect[3] - rect[1]) << shift);
    packet.vertex[3].xyz.y = packet.vertex[2].xyz.y =
        packet.vertex[0].xyz.y + ((rect[2] - rect[0]) << shift);
    packet.vertex[0].xyz.z = packet.vertex[1].xyz.z = packet.vertex[2].xyz.z =
        packet.vertex[3].xyz.z = 0xFFFFF8;
    packet.vertex[0].xyz.fog = packet.vertex[1].xyz.fog = packet.vertex[2].xyz.fog =
        packet.vertex[3].xyz.fog = 0;
    ((Tag_00245DB0 *)packet.tag)->flags |= 0x800;
    ((UV_00245DB0 *)&packet.vertex[0].uv)->u = rect[1] << 4;
    ((UV_00245DB0 *)&packet.vertex[0].uv)->v = rect[0] << 4;
    ((UV_00245DB0 *)&packet.vertex[1].uv)->u = rect[3] << 4;
    ((UV_00245DB0 *)&packet.vertex[1].uv)->v = rect[0] << 4;
    ((UV_00245DB0 *)&packet.vertex[2].uv)->u = rect[1] << 4;
    ((UV_00245DB0 *)&packet.vertex[2].uv)->v = rect[2] << 4;
    ((UV_00245DB0 *)&packet.vertex[3].uv)->u = rect[3] << 4;
    ((UV_00245DB0 *)&packet.vertex[3].uv)->v = rect[2] << 4;
    ExAssignTexture(packet.tag, object->texture, 1);
    ExAssignClamp(packet.tag, ((u64)rect[1] << 4) | 0xA | ((u64)rect[3] << 14) |
                                  ((u64)rect[0] << 24) | ((u64)rect[2] << 34));
    ExAssignAlpha(packet.tag, 0x44);
    if (facePacket != 0) {
        facePacket = ExSortPrim_Pipe(facePacket, (s32)packet.tag, 0, 0);
    }
}

typedef struct {
    u8 kind;
    u8 flags;
    u16 mode;
    u16 length;
    u16 value;
} Entry_002460F0;

typedef union {
    u64 raw;
    Entry_002460F0 record;
} Buffer_002460F0;

typedef struct {
    u8 kind;
    u8 delay;
    u16 image;
    u16 x;
    u16 y;
} Frame_002460F0;

typedef struct {
    s32 value;
    u8 resource;
    u8 object;
    u8 mask;
    u8 padding7[4];
    u8 delay[16];
    u8 frame[16];
} State_002460F0;

/* Draws one face: its parts for the current frame of its animation. */
void ShFace_DrawOne(void *face) {
    extern void ShAnime_GetFixInfo(u8, u8, u8, void *);
    extern void ShAnime_GetPartsRect(u8, u8, void *);
    extern void ShFace_Prim(void *, void *, u16, u16);
    u8 header[8];
    Buffer_002460F0 entry;
    Frame_002460F0 frame;
    u8 image[8];
    State_002460F0 *state = (State_002460F0 *)face;
    s32 randomSum;

    randomSum = ((func_0019A5C8() >> 4) & 0x3F) + ((func_0019A5C8() >> 4) & 0x3F);
    {
    Entry_002460F0 *data;
    s32 slot;
    s32 part;
    s32 randomSmall;

    randomSmall = (func_0019A5C8() >> 4) & 7;
    if (face != NULL) {
        ShAnime_GetPatInfo(state->resource, state->object, header);
        slot = 0;
        for (part = 0; part < header[0]; part++) {
            ShAnime_GetFixInfo(state->resource, state->object, part, &entry);
            if (entry.record.flags & 0x80) {
                data = (Entry_002460F0 *)&entry.raw;
                if (state->mask & (1 << data->mode)) {
                    if (state->delay[slot] != 0) {
                        state->delay[slot]--;
                    }
                    if (state->delay[slot] == 0) {
                        state->frame[slot]++;
                    }
                    if (state->frame[slot] >= data->length) {
                        state->frame[slot] = 0;
                    }
                } else {
                    state->frame[slot] = 0;
                }
                if (data->length != 0) {
                    ShAnime_GetAnmDat(state->resource, state->object, (u8)part, state->frame[slot], &frame);
                    ShAnime_GetPartsRect(state->resource, frame.image, image);
                    ShFace_Prim(face, image, frame.x, frame.y);
                    if (state->delay[slot] == 0) {
                        switch (data->mode) {
                        case 0:
                            if (state->frame[slot] == 0) {
                                state->delay[slot] = frame.delay + randomSum;
                            } else {
                                state->delay[slot] = frame.delay;
                            }
                            break;
                        case 1:
                            state->delay[slot] = frame.delay + randomSmall;
                            break;
                        default:
                            state->delay[slot] = frame.delay;
                            break;
                        }
                    }
                }
                slot++;
            } else {
                ShAnime_GetPartsRect(state->resource, entry.record.mode, image);
                ShFace_Prim(face, image, entry.record.length, entry.record.value);
            }
        }
    }
    }
}

typedef struct {
    s32 value;
    u8 kind;
    u8 pad5[0x2B];
    s32 handle;
} Entry_00246340;

/* Draws every shown face. */
s32 ShFace_Draw_Pipe(s32 packet) {
    extern s32 facePacket;
    extern s32 ShFace_DrawOne();
    extern s32 SzText_InitClutManage();
    Entry_00246340 *entry;
    s32 i;
    s32 base;

    facePacket = packet;
    for (i = 0; i < 8; i++) {
        if (((Entry_00246340 *)faceSlots)[i].value != 0) {
            ((Entry_00246340 *)faceSlots)[i].handle = SzText_LoadRequest(7, ((Entry_00246340 *)faceSlots)[i].kind);
        }
    }
    base = RhBase_GetUserGsAddress();
    base += SzText_InitClutManage(base, 2);
    facePacket = SzText_DoRequest_Pipe(facePacket, 7, base, NULL);
    facePacket = RhText_SetTextureFlush(facePacket);
    SzText_FreeRequest(7, -1);
    entry = (Entry_00246340 *)faceSlots;
    for (i = 0; i < 8; i++, entry++) {
        if (entry->value != 0 && entry->handle != 0) {
            ShFace_DrawOne(entry);
        }
    }
    return facePacket;
}

/* Starts the face system for game mode `mode`. */
void ShFace_Init(s32 mode) {
    extern s32 facePacket;
    s32 i;
    Entry_00245D80 *entry;

    gSh_FaceMode = mode;
    entry = faceSlots;
    i = 0;
    do {
        i += 1;
        entry->value = 0;
        entry++;
    } while (i < 8);
    facePacket = 0;
}

/* Draws every shown face. */
void ShFace_Draw(void) {
    RhBase_SetVifPacketArea(ShFace_Draw_Pipe(RhBase_GetVifPacketArea()));
}

/* Advances the faces' animations. */
void ShFace_Act(void) {
    if (gSh_FaceMode) {
        return;
    }
}

/* Ends the face system (nothing to do). */
void ShFace_Term(void) {

}

typedef struct Effect_002464F0 {
    u32 kind;
    u16 value;
} Effect_002464F0;

typedef struct Flags_002464F0 {
    s8 unused : 2;
    s8 active : 1;
    s8 rest : 5;
} Flags_002464F0;

typedef struct Card_002464F0 {
    u8 pad0[0x10];
    Effect_002464F0 effect;
    u8 pad18[0x26];
    u8 affiliation;
    u8 pad3F[5];
    u8 type;
    u8 present;
    u8 pad46[0x11];
    Flags_002464F0 flags;
} Card_002464F0;

/* How far a unit (record `vInfo`) on square (nX, nZ) may move: its base moves, the field, leader abilities and
   effects. */
s32 GetMoveRev(s32 vInfo, s32 nX, s32 nZ) {
    s32 i;
    s32 temp_s1;
    s32 var_s2;
    s32 checkLandAgreement;
    s32 var_v0;
    u32 temp_a0;
    u32 kind;
    u32 kind2;
    u32 temp_v1;
    u8 temp_a0_3;
    u8 temp_a0_4;
    Effect_002464F0 *temp_a0_2;
    Effect_002464F0 *unitEffect;
    Effect_002464F0 *unitEffect2;

    if (vInfo == 0) {
        return 0;
    }
    var_s2 = 0;
    if (((Card_002464F0 *)vInfo)->present == 0) {
        var_v0 = Ta_IsLDAbl(4, ((Card_002464F0 *)vInfo)->type);
        if (var_v0 != 0) {
            var_v0 = 2;
        } else {
            var_v0 = 1;
        }
        return var_v0;
    }
    if (((Card_002464F0 *)vInfo)->flags.active == 0) {
        var_v0 = 1;
        temp_a0_2 = &((Card_002464F0 *)vInfo)->effect;
        if (temp_a0_2 != NULL) {
            temp_a0 = temp_a0_2->kind >> 8;
            if ((temp_a0 == 8) || ((u32) (temp_a0 - 9) < 2U)) {
                var_v0 |= 0x10;
            }
            if (temp_a0 == 0x4F) {
                return 0;
            }
            return var_v0;
        }
        return var_v0;
    }
    temp_s1 = (nZ << 8) | nX;
    checkLandAgreement = CheckLandAgreement(SzDuel_GetField(temp_s1 & 0xFF, temp_s1 >> 8), (void *)vInfo);
    switch (checkLandAgreement) {
    case 0:
    case 2:
        var_s2 = 1;
        break;
    case 1:
        var_s2 = 2;
        break;
    }
    temp_a0_2 = &((Card_002464F0 *)vInfo)->effect;
    if (temp_a0_2 != NULL) {
        temp_v1 = temp_a0_2->kind >> 8;
        if (temp_v1 == 6) {
            var_s2 = temp_a0_2->value;
        } else if ((u32) (temp_v1 - 8) < 3U) {
            var_s2 |= 0x10;
        } else if (temp_v1 == 0x4F) {
            return 0;
        }
    }
    i = 0;
    do {
        if (SzDuel_GetUnitStatus(0, i, 4) == 1) {
            if (SzDuel_GetUnitStatus(0, i, 5) == 1) {
                unitEffect = Ta_GetUnitEffect(0, i, 2);
                if (unitEffect != NULL) {
                    kind = unitEffect->kind;
                    if ((kind >> 8) == 6) {
                        switch (kind & 0x3F) {
                        case 0xF:
                            temp_a0_3 = ((Card_002464F0 *)vInfo)->affiliation;
                            if (((temp_a0_3 & 0x1F) == 0xF) && (((s32) temp_a0_3 >> 5) == 0)) {
                                var_s2 = ((var_s2 >> 4) << 4) | unitEffect->value;
                            }
                            break;
                        default:
                            var_s2 = ((var_s2 >> 4) << 4) | unitEffect->value;
                            break;
                        }
                    }
                }
            }
        }
        if ((SzDuel_GetUnitStatus(1, i, 4) == 1) && (SzDuel_GetUnitStatus(1, i, 5) == 1)) {
            unitEffect2 = Ta_GetUnitEffect(1, i, 2);
            if (unitEffect2 != NULL) {
                kind2 = unitEffect2->kind;
                if ((kind2 >> 8) == 6) {
                    switch (kind2 & 0x3F) {
                    case 0xF:
                        temp_a0_4 = ((Card_002464F0 *)vInfo)->affiliation;
                        if (((temp_a0_4 & 0x1F) == 0xF) && (((s32) temp_a0_4 >> 5) == 0)) {
                            var_s2 = ((var_s2 >> 4) << 4) | unitEffect2->value;
                        }
                        break;
                    default:
                        var_s2 = ((var_s2 >> 4) << 4) | unitEffect2->value;
                        break;
                    }
                }
            }
        }
        i += 1;
    } while (i < 0xB);
    if (Ta_SearchUncTypeNaturalEffectUser(0x43, 0) >= 0) {
        var_s2 = ((var_s2 >> 4) << 4) | 1;
    }
    var_v0 = var_s2;
    if (Ta_IsLDRangeAvilityFromLoc(temp_s1, ((Card_002464F0 *)vInfo)->type, ((Card_002464F0 *)vInfo)->affiliation & 0x1F, 0xC) == 1) {
        var_v0 = ((var_s2 >> 4) << 4) | 2;
    }
    return var_v0;
}


typedef struct Flags_00246810 {
    u8 bit0 : 1;
    u8 bit1 : 1;
    u8 bit2 : 1;
    u8 bit3 : 1;
    u8 bit4 : 1;
    u8 bit5 : 1;
    u8 bit6 : 1;
    u8 bit7 : 1;
} Flags_00246810;

typedef struct Status_00246810 {
    Flags_00246810 mode;
    s32 value1;
    s32 value2;
    s32 value3;
    Flags_00246810 flags;
} Status_00246810;

/* Packs a battle value. */
static inline s32 encode_00246810(s32 value) {
    return ((value < 0 ? 1 : 0) << 15) | (value >= 0 ? value : -value);
}

/* Resolves a battle between unit (nSide_1, ID_1) and unit (nSide_2, ID_2) on square (nX, nZ): attack against
   attack or defence, the field and attribute bonuses, attack effects, the loser's destruction and the life-point
   damage, into `eInfo`. */
s32 Battle(s32 nSide_1, s32 ID_1, s32 nSide_2, s32 ID_2, s32 nX, s32 nZ, void *eInfo) {
    extern s32 SzDuel_GetUnitLevel();
    extern s32 SzDuel_GetUnitCardNo();
    extern s32 SzDuel_GetUnitCurseRest();
    Status_00246810 status;
    Status_00246810 *p = &status;
    s32 *out = eInfo;
    s32 sp120;
    s32 sp138;
    s32 sp13C;
    s32 sp140;
    s32 sp144;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 cardNo;
    s32 cardNo2;
    s32 cardNo3;
    s32 cardNo3In;
    s32 temp_s0_3;
    s32 temp_s0_4;
    s32 temp_s0_5;
    s32 temp_s0_6;
    s32 temp_s0_7;
    s32 temp_s0_8;
    s32 temp_s0_9;
    s32 temp_s1;
    s32 atkEfc;
    s32 unitAttr;
    s32 paramOfs;
    s32 temp_s5_2;
    s32 enc;
    s32 enc2;
    s32 chkAttrAdv;
    s32 atkEfc2;
    s32 unitStatus;
    s32 var_fp;
    s32 var_s7;

    p->value1 = 0;
    p->value2 = 0;
    p->value3 = 0;
    p->flags.bit0 = 0;
    p->flags.bit1 = 0;
    p->flags.bit2 = 0;
    p->flags.bit3 = 0;
    p->flags.bit4 = 0;
    p->mode.bit1 = 0;
    p->mode.bit2 = 0;
    p->mode.bit0 = 1;
    p->flags.bit5 = 0;
    p->flags.bit6 = 0;
    temp_s1 = SzDuel_GetUnitKind(nSide_1, ID_1) >> 5;
    temp_a0 = SzDuel_GetUnitKind(nSide_2, ID_2) >> 5;
    sp120 = 0;
    var_fp = 0;
    var_s7 = 0;
    if ((temp_s1 == 0) && (temp_a0 == 0)) {
        if (ID_1 == 0) {
            atkEfc = Manage_AtkEfc(nSide_1, ID_1, nSide_2, ID_2, p);
            paramOfs = Ta_GetParamOfs(SzDuel_GetUnit(nSide_2, ID_2), nX, nZ, 1);
            temp_s5_2 = p->value2 + SzDuel_GetUnitAP(nSide_2, ID_2, 0);
            temp_s5_2 = GetParCap(temp_s5_2 + paramOfs);
            SzDuel_CalcUnitAP(nSide_2, ID_2, 0, p->value2);
            SzDuel_CalcUnitDP(nSide_2, ID_2, 0, p->value2);
            p->value2 = encode_00246810(p->value2);
            if (Ta_IsLDAbl(6, nSide_1) != 0) {
                out[0] = 0x5D;
                out[1] = (s32) ((p->value2 << 0x10) | ((nSide_2 << 8) | ID_2));
                out[2] = nSide_1;
                out[3] = (((p->flags.bit6 << 1) | ((atkEfc >> 0x18) & 1)) << 0x16) | ((temp_s5_2 >> 1) | (((p->flags.bit5 << 1) | ((atkEfc >> 0x10) & 1)) << 0x14));
            } else {
                out[0] = 0x5D;
                out[1] = (s32) ((nSide_2 << 8) | ID_2);
                out[2] = nSide_1;
                out[3] = (((p->flags.bit6 << 1) | ((atkEfc >> 0x18) & 1)) << 0x16) | (temp_s5_2 | (((p->flags.bit5 << 1) | ((atkEfc >> 0x10) & 1)) << 0x14));
            }
            return 1;
        }
        unitAttr = SzDuel_GetUnitAttr(nSide_2, ID_2);
        chkAttrAdv = ChkAttrAdv(unitAttr, SzDuel_GetUnitAttr(nSide_1, ID_1));
        switch (chkAttrAdv) {                        /* switch 1; irregular */
        case 1:                                     /* switch 1 */
            if (SzDuel_GetUnitCurseRest(nSide_1, ID_1) == 0) {
                var_fp = 1;
            }
            break;
        case -1:                                    /* switch 1 */
            if (SzDuel_GetUnitCurseRest(nSide_2, ID_2) == 0) {
                var_s7 = 1;
            }
            break;
        }
        atkEfc2 = Manage_AtkEfc(nSide_1, ID_1, nSide_2, ID_2, p);
        if ((atkEfc2 & 0xFF) == 1) {
            temp_a0_2 = (atkEfc2 >> 0x18) & 1;
            if ((temp_a0_2 == 1) && (((atkEfc2 >> 0x10) & 1) == 1)) {
                out[0] = 0x5E;
                out[1] = (s32) ((nSide_2 << 8) | ID_2);
                out[2] = (s32) ((nSide_1 << 8) | ID_1);
                out[3] = (s32) ((p->flags.bit2 << 0x1B) | ((var_s7 << 0x1A) | ((var_fp << 0x19) | ((((p->flags.bit6 << 1) | 1) << 0x16) | ((((p->flags.bit5 << 1) | 1) << 0x14) | 0xCFFFF)))) | 0x10000000);
                cardNo = SzDuel_GetUnitCardNo(nSide_1, ID_1);
                                SzData_CalcExp(nSide_1, cardNo, 0, (SzDuel_GetUnitLevel(nSide_2, ID_2, 0) + 2) * 2);
                cardNo3In = SzDuel_GetUnitCardNo(nSide_2, ID_2);
                                SzData_CalcExp(nSide_2, cardNo3In, 0, (SzDuel_GetUnitLevel(nSide_1, ID_1, 0) + 2) * 2);
                return 1;
            }
            if (temp_a0_2 == 1) {
                out[0] = 0x5E;
                out[1] = (s32) ((nSide_2 << 8) | ID_2);
                out[2] = (s32) ((nSide_1 << 8) | ID_1);
                out[3] = (s32) ((p->flags.bit2 << 0x1B) | ((var_s7 << 0x1A) | ((var_fp << 0x19) | ((((p->flags.bit6 << 1) | 1) << 0x16) | (((p->flags.bit5 << 1) << 0x14) | 0x8FFFF)))) | 0x10000000);
                temp_s0_3 = SzDuel_GetUnitCardNo(nSide_1, ID_1);
                                SzData_CalcExp(nSide_1, temp_s0_3, 0, (SzDuel_GetUnitLevel(nSide_2, ID_2, 0) + 2) * 2);
                return 1;
            }
            if (((atkEfc2 >> 0x10) & 1) == 1) {
                out[0] = 0x5E;
                out[1] = (s32) ((nSide_2 << 8) | ID_2);
                out[2] = (s32) ((nSide_1 << 8) | ID_1);
                out[3] = (s32) ((p->flags.bit2 << 0x1B) | ((var_s7 << 0x1A) | ((var_fp << 0x19) | ((p->flags.bit6 << 0x17) | ((((p->flags.bit5 << 1) | 1) << 0x14) | 0x4FFFF)))));
                temp_s0_4 = SzDuel_GetUnitCardNo(nSide_2, ID_2);
                                SzData_CalcExp(nSide_2, temp_s0_4, 0, (SzDuel_GetUnitLevel(nSide_1, ID_1, 0) + 2) * 2);
                return 1;
            }

        }
        unitStatus = SzDuel_GetUnitStatus(nSide_1, ID_1, 3);
        switch (unitStatus) {                        /* switch 2; irregular */
        case 1:                                     /* switch 2 */
            if (p->flags.bit3 == 1) {
                SzDuel_CalcUnitAP(nSide_1, ID_1, 4, 0);
                SzDuel_CalcUnitDP(nSide_1, ID_1, 4, 0);
                sp13C = GetParCap(SzDuel_GetUnitDP(nSide_1, ID_1, 0) + Ta_GetParamOfs(SzDuel_GetUnit(nSide_1, ID_1), nX, nZ, 0));
            } else {
                sp13C = GetParCap(p->value1 + SzDuel_GetUnitDP(nSide_1, ID_1, 0) + Ta_GetParamOfs(SzDuel_GetUnit(nSide_1, ID_1), nX, nZ, 0));
                SzDuel_CalcUnitAP(nSide_1, ID_1, 0, p->value1);
                SzDuel_CalcUnitDP(nSide_1, ID_1, 0, p->value1);
                p->value1 = encode_00246810(p->value1);
            }
            if (p->flags.bit4 == 1) {
                SzDuel_CalcUnitAP(nSide_2, ID_2, 4, 0);
                SzDuel_CalcUnitDP(nSide_2, ID_2, 4, 0);
                sp138 = GetParCap(SzDuel_GetUnitAP(nSide_2, ID_2, 0) + Ta_GetParamOfs(SzDuel_GetUnit(nSide_2, ID_2), nX, nZ, 1));
            } else {
                sp138 = GetParCap(p->value2 + SzDuel_GetUnitAP(nSide_2, ID_2, 0) + Ta_GetParamOfs(SzDuel_GetUnit(nSide_2, ID_2), nX, nZ, 1));
                SzDuel_CalcUnitAP(nSide_2, ID_2, 0, p->value2);
                SzDuel_CalcUnitDP(nSide_2, ID_2, 0, p->value2);
                p->value2 = encode_00246810(p->value2);
            }
            if (sp13C > sp138) {

                if (p->flags.bit1 == 0) {
                    sp120 += sp13C - sp138;

                }
                out[0] = 0x5E;
                out[1] = (s32) ((p->value2 << 0x10) | ((nSide_2 << 8) | ID_2));
                out[2] = (s32) ((p->value1 << 0x10) | ((nSide_1 << 8) | ID_1));
                out[3] = (s32) ((p->flags.bit2 << 0x1B) | ((var_s7 << 0x1A) | ((var_fp << 0x19) | ((((p->flags.bit6 << 1) | ((atkEfc2 >> 0x18) & 1)) << 0x16) | (sp120 | 0x20000 | (((p->flags.bit5 << 1) | ((atkEfc2 >> 0x10) & 1)) << 0x14)) | 0x01000000))) | 0x10000000);
                return 1;
            }
            if (sp13C == sp138) {
                out[0] = 0x5E;
                out[1] = (s32) ((p->value2 << 0x10) | ((nSide_2 << 8) | ID_2));
                out[2] = (s32) ((p->value1 << 0x10) | ((nSide_1 << 8) | ID_1));
                out[3] = (s32) ((p->flags.bit2 << 0x1B) | ((var_s7 << 0x1A) | ((var_fp << 0x19) | ((((p->flags.bit6 << 1) | ((atkEfc2 >> 0x18) & 1)) << 0x16) | (((p->flags.bit5 << 1) | ((atkEfc2 >> 0x10) & 1)) << 0x14) | 0x01000000))));
                return 1;
            }
            if (sp13C < sp138) {
                out[0] = 0x5E;
                out[1] = (s32) ((p->value2 << 0x10) | ((nSide_2 << 8) | ID_2));
                out[2] = (s32) ((p->value1 << 0x10) | ((nSide_1 << 8) | ID_1));
                out[3] = (s32) ((p->flags.bit2 << 0x1B) | ((var_s7 << 0x1A) | ((var_fp << 0x19) | ((((p->flags.bit6 << 1) | ((atkEfc2 >> 0x18) & 1)) << 0x16) | ((((p->flags.bit5 << 1) | ((atkEfc2 >> 0x10) & 1)) << 0x14) | 0x40000)))));
                temp_s0_5 = SzDuel_GetUnitCardNo(nSide_2, ID_2);
                                SzData_CalcExp(nSide_2, temp_s0_5, 0, (SzDuel_GetUnitLevel(nSide_1, ID_1, 0) + 2) * 2);
                return 1;
            }
            break;
        case 0:                                     /* switch 2 */
            if (p->flags.bit3 == 1) {
                SzDuel_CalcUnitAP(nSide_1, ID_1, 4, 0);
                SzDuel_CalcUnitDP(nSide_1, ID_1, 4, 0);
                sp140 = GetParCap(SzDuel_GetUnitAP(nSide_1, ID_1, 0) + Ta_GetParamOfs(SzDuel_GetUnit(nSide_1, ID_1), nX, nZ, 1));
            } else {
                sp140 = GetParCap(p->value1 + SzDuel_GetUnitAP(nSide_1, ID_1, 0) + Ta_GetParamOfs(SzDuel_GetUnit(nSide_1, ID_1), nX, nZ, 1));
                SzDuel_CalcUnitAP(nSide_1, ID_1, 0, p->value1);
                SzDuel_CalcUnitDP(nSide_1, ID_1, 0, p->value1);
                p->value1 = encode_00246810(p->value1);
            }
            if (p->flags.bit4 == 1) {
                SzDuel_CalcUnitAP(nSide_2, ID_2, 4, 0);
                SzDuel_CalcUnitDP(nSide_2, ID_2, 4, 0);
                sp144 = GetParCap(SzDuel_GetUnitAP(nSide_2, ID_2, 0) + Ta_GetParamOfs(SzDuel_GetUnit(nSide_2, ID_2), nX, nZ, 1));
            } else {
                sp144 = GetParCap(p->value2 + SzDuel_GetUnitAP(nSide_2, ID_2, 0) + Ta_GetParamOfs(SzDuel_GetUnit(nSide_2, ID_2), nX, nZ, 1));
                SzDuel_CalcUnitAP(nSide_2, ID_2, 0, p->value2);
                SzDuel_CalcUnitDP(nSide_2, ID_2, 0, p->value2);
                p->value2 = encode_00246810(p->value2);
            }
            if (sp140 > sp144) {
                if (p->flags.bit1 == 0) {
                    sp120 = sp140 - sp144;
                }
                out[0] = 0x5E;
                out[1] = (s32) ((p->value2 << 0x10) | ((nSide_2 << 8) | ID_2));
                out[2] = (s32) ((p->value1 << 0x10) | ((nSide_1 << 8) | ID_1));
                out[3] = (s32) ((p->flags.bit2 << 0x1B) | ((var_s7 << 0x1A) | ((var_fp << 0x19) | ((((p->flags.bit6 << 1) | ((atkEfc2 >> 0x18) & 1)) << 0x16) | (sp120 | 0xA0000 | (((p->flags.bit5 << 1) | ((atkEfc2 >> 0x10) & 1)) << 0x14))))) | 0x10000000);
                if (sp120 <= 0) {
                    temp_s0_6 = SzDuel_GetUnitCardNo(nSide_1, ID_1);
                                        SzData_CalcExp(nSide_1, temp_s0_6, 0, (SzDuel_GetUnitLevel(nSide_2, ID_2, 0) + 2) * 2);
                } else {
                    temp_s0_7 = SzDuel_GetUnitCardNo(nSide_1, ID_1);
                                        SzData_CalcExp(nSide_1, temp_s0_7, 0, SzDuel_GetUnitLevel(nSide_2, ID_2, 0) * 4);
                }
                return 1;
            }
            if (sp140 == sp144) {
                out[0] = 0x5E;
                out[1] = (s32) ((p->value2 << 0x10) | ((nSide_2 << 8) | ID_2));
                out[2] = (s32) ((p->value1 << 0x10) | ((nSide_1 << 8) | ID_1));
                out[3] = (s32) ((p->flags.bit2 << 0x1B) | ((var_s7 << 0x1A) | ((var_fp << 0x19) | ((((p->flags.bit6 << 1) | ((atkEfc2 >> 0x18) & 1)) << 0x16) | ((((p->flags.bit5 << 1) | ((atkEfc2 >> 0x10) & 1)) << 0x14) | 0xC0000)))) | 0x10000000);
                temp_s0_8 = SzDuel_GetUnitCardNo(nSide_1, ID_1);
                                SzData_CalcExp(nSide_1, temp_s0_8, 0, (SzDuel_GetUnitLevel(nSide_2, ID_2, 0) + 2) * 2);
                temp_s0_9 = SzDuel_GetUnitCardNo(nSide_2, ID_2);
                                SzData_CalcExp(nSide_2, temp_s0_9, 0, (SzDuel_GetUnitLevel(nSide_1, ID_1, 0) + 2) * 2);
                return 1;
            }
            if (sp140 < sp144) {
                if (!(p->flags.bit0)) {
                    sp120 = sp144 - sp140;
                }
                out[0] = 0x5E;
                out[1] = (s32) ((p->value2 << 0x10) | ((nSide_2 << 8) | ID_2));
                out[2] = (s32) ((p->value1 << 0x10) | ((nSide_1 << 8) | ID_1));
                out[3] = (s32) ((p->flags.bit2 << 0x1B) | ((var_s7 << 0x1A) | ((var_fp << 0x19) | ((((p->flags.bit6 << 1) | ((atkEfc2 >> 0x18) & 1)) << 0x16) | (sp120 | 0x50000 | (((p->flags.bit5 << 1) | ((atkEfc2 >> 0x10) & 1)) << 0x14))))));
                if (sp120 <= 0) {
                    cardNo2 = SzDuel_GetUnitCardNo(nSide_2, ID_2);
                                        SzData_CalcExp(nSide_2, cardNo2, 0, (SzDuel_GetUnitLevel(nSide_1, ID_1, 0) + 2) * 2);
                } else {
                    cardNo3 = SzDuel_GetUnitCardNo(nSide_2, ID_2);
                                        SzData_CalcExp(nSide_2, cardNo3, 0, SzDuel_GetUnitLevel(nSide_1, ID_1, 0) * 4);
                }
                return 1;
            }
            break;
        }
    } else {
        if ((temp_s1 == 0) && ((temp_a0 == 1) || ((u32)(temp_a0 - 3) < 3U))) {
            out[0] = 0x5F;
            out[1] = (s32) ((nSide_1 << 8) | ID_1);
            out[2] = (s32) ((nSide_2 << 8) | ID_2);
            out[3] = 1;
            return 1;
        }
        if (temp_s1 == 0) {
            if (temp_a0 == 2) {
                if (Ta_IsLDRangeAvility(nSide_1, ID_1, 0xB) == 1) {
                    out[0] = 0x5F;
                    out[1] = (s32) ((nSide_1 << 8) | ID_1);
                    out[2] = (s32) ((nSide_2 << 8) | ID_2);
                    out[3] = 3;
                    return 0x10001;
                }
                if (Ta_IsResistAll(nSide_1, ID_1) != 0) {
                    out[0] = 0x5F;
                    out[1] = (s32) ((nSide_1 << 8) | ID_1);
                    out[2] = (s32) ((nSide_2 << 8) | ID_2);
                    out[3] = 1;
                    return 0x10001;
                }
                enc = Chk_Enc(nSide_1, ID_1, SzDuel_GetUnitCardNo(nSide_2, ID_2));
                if (enc == 0x3E7) {
                    out[0] = 0x5F;
                    out[1] = (s32) ((nSide_1 << 8) | ID_1);
                    out[2] = (s32) ((nSide_2 << 8) | ID_2);
                    out[3] = 1;
                    return 0x10001;
                }
                if (((enc >> 0x1E) & 1) == 1) {
                    SzDuel_SetUnitStatus(nSide_2, ID_2, 2, 1);
                    out[0] = 0x2B;
                    out[1] = (s32) ((nSide_2 << 8) | ID_2);
                    out[2] = (s32) ((nSide_1 << 8) | ID_1);
                    out[3] = (s32) ((enc >> 0xE) & 0x3FFF);
                    return 0x10001;
                }
                if ((enc >> 0xE) == 0x219) {
                    SzDuel_SetUnitStatus(nSide_2, ID_2, 2, 1);
                    out[0] = 0x25;
                    out[1] = (s32) ((nSide_1 << 8) | ID_1);
                    out[2] = (s32) ((nSide_2 << 8) | ID_2);
                    out[3] = (s32) ((enc & 0x3FFF) | (Ta_GetCurrentSide(nSide_2, ID_2) << 0x10));
                } else {
                    SzDuel_SetUnitStatus(nSide_2, ID_2, 2, 1);
                    out[0] = 0x24;
                    out[1] = (s32) ((nSide_1 << 8) | ID_1);
                    out[2] = (s32) ((nSide_2 << 8) | ID_2);
                    out[3] = enc;
                }
                return 0x10001;
            }
        }

        if (temp_s1 == 2) {
            if (temp_a0 == 0) {
                SzData_CalcExp(nSide_2, SzDuel_GetUnitCardNo(nSide_2, ID_2), 0, 6);
                if (Ta_IsLDRangeAvility(nSide_2, ID_2, 0xB) == 1) {
                    out[0] = 0x5F;
                    out[1] = (s32) ((nSide_1 << 8) | ID_1);
                    out[2] = (s32) ((nSide_2 << 8) | ID_2);
                    out[3] = 2;
                    return 1;
                }
                if (Ta_IsResistAll(nSide_2, ID_2) != 0) {
                    out[0] = 0x5F;
                    out[1] = (s32) ((nSide_1 << 8) | ID_1);
                    out[2] = (s32) ((nSide_2 << 8) | ID_2);
                    out[3] = 0;
                    return 1;
                }
                enc2 = Chk_Enc(nSide_2, ID_2, SzDuel_GetUnitCardNo(nSide_1, ID_1));
                if (enc2 == 0x3E7) {
                    out[0] = 0x5F;
                    out[1] = (s32) ((nSide_1 << 8) | ID_1);
                    out[2] = (s32) ((nSide_2 << 8) | ID_2);
                    out[3] = 0;
                    return 1;
                }
                if (((enc2 >> 0x1E) & 1) == 1) {
                    SzDuel_SetUnitStatus(nSide_1, ID_1, 2, 1);
                    out[0] = 0x2B;
                    out[1] = (s32) ((nSide_1 << 8) | ID_1);
                    out[2] = (s32) ((nSide_2 << 8) | ID_2);
                    out[3] = (s32) ((enc2 >> 0xE) & 0x3FFF);
                    return 1;
                }
                if ((enc2 >> 0xE) == 0x219) {
                    SzDuel_SetUnitStatus(nSide_1, ID_1, 2, 1);
                    out[0] = 0x25;
                    out[1] = (s32) ((nSide_1 << 8) | ID_1);
                    out[2] = (s32) ((nSide_2 << 8) | ID_2);
                    out[3] = (s32) ((enc2 & 0x3FFF) | (Ta_GetCurrentSide(nSide_1, ID_1) << 0x10));
                } else {
                    SzDuel_SetUnitStatus(nSide_1, ID_1, 2, 1);
                    out[0] = 0x24;
                    out[1] = (s32) ((nSide_1 << 8) | ID_1);
                    out[2] = (s32) ((nSide_2 << 8) | ID_2);
                    out[3] = enc2;
                }
                return 1;
            }

        }
        if (((u32)(temp_s1 - 1) < 5U) && ((u32) temp_a0 < 6U)) {
            out[0] = 0x5F;
            out[1] = (s32) ((nSide_1 << 8) | ID_1);
            out[2] = (s32) ((nSide_2 << 8) | ID_2);
            out[3] = 0;
            if (temp_a0 == 0) {
                SzData_CalcExp(nSide_2, SzDuel_GetUnitCardNo(nSide_2, ID_2), 0, 6);
            }
            return 1;
        }
    }
    return 0;
}

/* Resolves stacking unit (nSide_2, ID_2) onto unit (nSide_1, ID_1) (heap): a fusion, an equip, or a replacement,
   into `eInfo`. */
s32 SelfHeap(s32 nSide_1, s32 ID_1, s32 nSide_2, s32 ID_2, s32 *eInfo) {
    s32 type0;
    s32 type1;

    extern s32 SzDuel_GetUnitCardNo();

    if (ID_2 == 0) {
        eInfo[0] = 0x5F;
        eInfo[1] = (nSide_1 << 8) | ID_1;
        eInfo[2] = (nSide_2 << 8) | ID_2;
        eInfo[3] = 0;
        return 1;
    }
    type0 = SzDuel_GetUnitKind(nSide_1, ID_1) >> 5;
    type1 = SzDuel_GetUnitKind(nSide_2, ID_2) >> 5;
    if (type0 == 0 && type1 == 0) {
        s32 card0;
        u32 result;

        if (ID_1 == 0) {
            eInfo[0] = 0x5F;
            eInfo[1] = (nSide_2 << 8) | ID_2;
            eInfo[2] = (nSide_1 << 8) | ID_1;
            eInfo[3] = 1;
            return 1;
        }
        card0 = SzDuel_GetUnitCardNo(nSide_1, ID_1);
        result = Fusion(card0, SzDuel_GetUnitCardNo(nSide_2, ID_2));
        eInfo[0] = 0x64;
        eInfo[1] = (nSide_1 << 8) | ID_1;
        eInfo[2] = (nSide_2 << 8) | ID_2;
        eInfo[3] = result;
        return 1;
    }
    if (type0 == 0 && type1 == 2) {
        s32 result;

        if (ID_1 == 0) {
            eInfo[0] = 0x5F;
            eInfo[1] = (nSide_2 << 8) | ID_2;
            eInfo[2] = (nSide_1 << 8) | ID_1;
            eInfo[3] = 1;
            return 1;
        }
        result = Chk_Enc(nSide_1, ID_1, SzDuel_GetUnitCardNo(nSide_2, ID_2));
        if (result == 0x3E7) {
            eInfo[0] = 0x24;
            eInfo[1] = (nSide_1 << 8) | ID_1;
            eInfo[2] = (nSide_2 << 8) | ID_2;
            eInfo[3] = 0x3E7;
            return 1;
        }
        if (((result >> 30) & 1) == 1) {
            eInfo[0] = 0x2B;
            eInfo[1] = (nSide_2 << 8) | ID_2;
            eInfo[2] = (nSide_1 << 8) | ID_1;
            eInfo[3] = (result >> 14) & 0x3FFF;
            return 0x10001;
        }
        if ((result >> 14) == 0x219) {
            eInfo[0] = 0x25;
            eInfo[1] = (nSide_1 << 8) | ID_1;
            eInfo[2] = (nSide_2 << 8) | ID_2;
            eInfo[3] = (result & 0x3FFF) | (Ta_GetCurrentSide(nSide_1, ID_1) << 16);
        } else {
            eInfo[0] = 0x24;
            eInfo[1] = (nSide_1 << 8) | ID_1;
            eInfo[2] = (nSide_2 << 8) | ID_2;
            eInfo[3] = result;
        }
        return 0x10001;
    }
    if (type0 == 2 && type1 == 0) {
        s32 result;

        if (ID_2 == 0) {
            eInfo[0] = 0x5F;
            eInfo[1] = (nSide_1 << 8) | ID_1;
            eInfo[2] = (nSide_2 << 8) | ID_2;
            eInfo[3] = 0;
            return 1;
        }
        result = Chk_Enc(nSide_2, ID_2, SzDuel_GetUnitCardNo(nSide_1, ID_1));
        if (result == 0x3E7) {
            eInfo[0] = 0x24;
            eInfo[1] = (nSide_1 << 8) | ID_1;
            eInfo[2] = (nSide_2 << 8) | ID_2;
            eInfo[3] = 0x3E7;
            return 1;
        }
        if (((result >> 30) & 1) == 1) {
            eInfo[0] = 0x2B;
            eInfo[1] = (nSide_1 << 8) | ID_1;
            eInfo[2] = (nSide_2 << 8) | ID_2;
            eInfo[3] = (result >> 14) & 0x3FFF;
            return 1;
        }
        if ((result >> 14) == 0x219) {
            eInfo[0] = 0x25;
            eInfo[1] = (nSide_1 << 8) | ID_1;
            eInfo[2] = (nSide_2 << 8) | ID_2;
            eInfo[3] = (result & 0x3FFF) | (Ta_GetCurrentSide(nSide_2, ID_2) << 16);
        } else {
            eInfo[0] = 0x24;
            eInfo[1] = (nSide_1 << 8) | ID_1;
            eInfo[2] = (nSide_2 << 8) | ID_2;
            eInfo[3] = result;
        }
        return 1;
    }
    eInfo[0] = 0x5F;
    eInfo[1] = (nSide_1 << 8) | ID_1;
    eInfo[2] = (nSide_2 << 8) | ID_2;
    eInfo[3] = 0;
    return 1;
}

/* Whether equip card `nEncCardNo` can be equipped to unit (nSide, nID). */
s32 Do_ChkEncMatch(u32 nSide, s32 nID, s32 nEncCardNo) {
    extern s32 SzDuel_GetUnitCardNo();
    s32 offset;
    s32 row;

    if (nSide < 2U) {
        if (nID == 0) {
            return 0;
        }
    }

    if (nEncCardNo == 0x304) {
        if ((SzDuel_GetUnitKind((s32)nSide, nID) >> 5) == 0) {
            if ((SzDuel_GetUnitKind((s32)nSide, nID) & 0x1F) == 2) {
                return 1;
            }
        }
        return 0;
    }

    row = SzDuel_GetUnitCardNo(nSide, nID) * 7;
    offset = nEncCardNo - 0x2F0;
    return ((equipMatchTable + (offset >> 3))[row] >> (offset % 8)) & 1;
}

extern int func_001E1030_b(int a, int b);
extern unsigned *func_001E0B70_b(int a, int b, int n);
extern void func_002503B0_b(int a, int b, unsigned char n);
extern int func_001E15E0_b(int a, int b, int value);
/* Applies one kind of equip result (power-ups, life points, status). */
static inline int apply_kind_00248460(int a, int b, int c, int d, int total, int id)
{
    int val;
    unsigned *p;

    {
        val = D_0029CF32[id];
        switch (D_0029D1F0[id]) {
        case 0:
            if (val == 0) {
                id = d & 0xff;
                total = Ta_GetForceEffection(id, total);
                if (c >> 16) {
                    TaUtil_CalcUnitAP(a, b, 1, total);
                    TaUtil_CalcUnitDP(a, b, 1, total);
                } else {
                    TaUtil_CalcUnitAP(a, b, 0, total);
                    TaUtil_CalcUnitDP(a, b, 0, total);
                }
                SzDuel_CalcLP(id == 0 ? 1 : 0, 1, total);
                return c;
            } else {
                total = val + total;
                if (c >> 16) {
                    TaUtil_CalcUnitAP(a, b, 1, total);
                    TaUtil_CalcUnitDP(a, b, 1, total);
                    return c;
                } else {
                    TaUtil_CalcUnitAP(a, b, 0, total);
                    TaUtil_CalcUnitDP(a, b, 0, total);
                    return c;
                }
            }
        case 1:
            switch (val) {
            case 1:
                p = func_001E0B70_b(a, b, 4);
                p[0] = 5211;
                p[1] = 0;
                p = func_001E0B70_b(a, b, 3);
                p[0] = 14428;
                p[1] = 0x1f0129;
                return c;
            case 2:
                p = func_001E0B70_b(a, b, 0);
                p[0] = 1152;
                p[1] = 0;
                return c;
            case 3:
                p = func_001E0B70_b(a, b, 0);
                p[0] = 1159;
                p[1] = 0;
                return c;
            case 4:
                p = func_001E0B70_b(a, b, 0);
                p[0] = 1153;
                p[1] = 0;
                return c;
            case 5:
                p = func_001E0B70_b(a, b, 4);
                p[0] = 765;
                p[1] = 0x10009;
                return c;
            }
            break;
        case 2:
            TaUtil_CalcUnitAP(a, b, 4, 0);
            TaUtil_CalcUnitDP(a, b, 4, 0);
            func_002503B0_b(a, b, 0);
            func_001E15E0_b(a, b, 0);
            return c;
        case 3:
            func_002503B0_b(a, b, 255);
            SzDuel_SetUnitStatus(a, b, 0, 1);
            return c;
        case 4:
            return c;
        }
    }
    return c;
}

/* Equips unit `cID` of side `nSide` with equip effect `eNO` (owner `nEffectOwner`). */
int Enchant(int nSide, int cID, int eNO, int nEffectOwner)
{
    int total;
    int id;

    func_001E1030_b(nSide, cID);
    total = 0;
    total += Ta_GetEnchantOfs();
    id = eNO & 0x3fff;
    if (Do_ChkEncMatch(nSide, cID, id) != 0) {
        eNO = apply_kind_00248460(nSide, cID, eNO, nEffectOwner, total, id);
    } else {
        eNO = -1;
    }
    return eNO;
}

/* Whether equip effect `eNO` works on card `cNO`. */
s32 Do_Chk_Enc(s32 cNO, s32 eNO) {
    s32 bit;

    bit = eNO - 0x2F0;
    if ((equipMatchTable[cNO * 7 + (bit >> 3)] >> (bit % 8)) & 1) {
        switch (D_0029D1F0[eNO]) {
        case 4:
            switch (D_0029CF32[eNO]) {
            case 6:
                return eNO | 0x40444000;
            case 7:
                return eNO | 0x406AC000;
            case 8:
                switch (cNO) {
                case 0x156:
                    return eNO | 0x407A0000;
                case 7:
                    return eNO | 0x407D4000;
                }
                break;
            case 9:
                switch (cNO) {
                case 0x10:
                    return eNO | (((func_0019A5C8() % 5 + 0xD) << 14) | 0x40000000);
                case 0x11:
                    return eNO | (((func_0019A5C8() % 5 + 0xD) << 14) | 0x40000000);
                case 0xA7:
                    return eNO | (((func_0019A5C8() % 15 + 0xD1) << 14) | 0x40000000);
                case 0x14C:
                    return eNO | (((func_0019A5C8() % 32 + 0x65) << 14) | 0x40000000);
                case 0x17B:
                    return eNO | (((u16)TaEnc_GetRandomElf() << 14) | 0x40000000);
                }
                break;
            }
            break;
        case 0:
            switch (D_0029CF32[eNO]) {
            case 0:
                return eNO | 0x864000;
            default:
                return eNO | 0x860000;
            }
        case 3:
            return eNO | 0x874000;
        case 2:
            return eNO | 0x878000;
        case 1:
            switch (D_0029CF32[eNO]) {
            case 5:
                return eNO | 0x870000;
            default:
                return eNO | 0x860000;
            }
        default:
            return eNO | 0x860000;
        }
    } else {
        return 0x3E7;
    }
    return 0x3E7;
}

/* Whether equip effect `eNO` works on unit `cID` of side `nSide`. */
s32 Chk_Enc(s32 nSide, s32 cID, s32 eNO) {
    s32 kind;
    extern s32 SzDuel_GetUnitCardNo();

    kind = SzDuel_GetUnitCardNo(nSide, cID);
    if (Do_ChkEncMatch(nSide, cID, eNO) != 0) {
        switch (D_0029D1F0[eNO]) {
        case 4:
            switch (D_0029CF32[eNO]) {
            case 6:
                return eNO | 0x40444000;
            case 7:
                return eNO | 0x406AC000;
            case 8:
                switch (kind) {
                case 0x156:
                    return eNO | 0x407A0000;
                case 7:
                    return eNO | 0x407D4000;
                }
                break;
            case 9:
                switch (kind) {
                case 0x10:
                    return eNO | (((func_0019A5C8() % 5 + 0xD) << 14) | 0x40000000);
                case 0x11:
                    return eNO | (((func_0019A5C8() % 5 + 0xD) << 14) | 0x40000000);
                case 0xA7:
                    return eNO | (((func_0019A5C8() % 15 + 0xD1) << 14) | 0x40000000);
                case 0x14C:
                    return eNO | (((func_0019A5C8() % 32 + 0x65) << 14) | 0x40000000);
                case 0x17B:
                    return eNO | (((u16)TaEnc_GetRandomElf() << 14) | 0x40000000);
                }
                break;
            }
            break;
        case 0:
            switch (D_0029CF32[eNO]) {
            case 0:
                return eNO | 0x864000;
            default:
                return eNO | 0x860000;
            }
        case 3:
            return eNO | 0x874000;
        case 2:
            return eNO | 0x878000;
        case 1:
            switch (D_0029CF32[eNO]) {
            case 5:
                return eNO | 0x870000;
            default:
                return eNO | 0x860000;
            }
        default:
            return eNO | 0x860000;
        }
    } else {
        return 0x3E7;
    }
    return 0x3E7;
}

/* Half the opposing side's life points (through standing effect 0x2C), plus `pOfs`. */
s32 Ta_GetForceEffection(s32 nSide, s32 pOfs) {
    s32 var_v0;

    if (nSide < 2) {
        var_v0 = SzDuel_GetLP((nSide == 0) ? 1 : 0) >> 1;
    } else {
        var_v0 = SzDuel_GetLP((SzDuel_GetTurnOwner() == 0) ? 1 : 0) >> 1;
    }
    var_v0 = Ta_GetLPRevByNaturalEffect(0x2C, var_v0);
    var_v0 += pOfs;
    return var_v0;
}

typedef struct Entry_00248EA0 {
    u32 unk0;
    u32 value;
} Entry_00248EA0;


/* The total power change the field's equip-like effects give. */
s32 Ta_GetEnchantOfs(void) {
    s32 index;
    s32 total;
    s32 count;
    s32 id;
    u32 kind;
    Entry_00248EA0 *entry;

    total = 0;
    count = Ta_SearchUncTypeNaturalEffectUserNum(0x34);
    for (index = 0; index < count; index++) {
            id = Ta_SearchUncTypeNaturalEffectUser(0x34, index);
            if (id >= 0) {
                entry = Ta_GetUnitEffect(id >> 8, id & 0xFF, 2);
                kind = entry->value >> 16;
                switch (kind) {
                case 0:
                    total += *(u16 *)((u8 *)entry + 4);
                    break;
                case 1:
                    total -= *(u16 *)((u8 *)entry + 4);
                    break;
                }
            }
    }
    return total;
}

/* The equip result of combining hand cards `cNo1` and `cNo2`. */
s32 Ta_GetHandEnchant(s32 cNo1, s32 cNo2) {
    s32 temp_a2;

    temp_a2 = cNo2 - 0x2F0;
    if ((equipMatchTable[cNo1 * 7 + (temp_a2 >> 3)] >> (temp_a2 % 8)) & 1) {
        return Ta_GetHandEnchant3(cNo1, cNo2);
    }
    return -1;
}

/* The equip result of putting hand card `cNo2` on unit (nSide, nID). */
s32 Ta_GetHandEnchant2(s32 nSide, s32 nID, s32 cNo2) {
    extern s32 SzDuel_GetUnitCardNo();

    if (Do_ChkEncMatch(nSide, nID, cNo2) != 0) {
        return Ta_GetHandEnchant3(SzDuel_GetUnitCardNo(nSide, nID), cNo2);
    }
    return -1;
}

/* Whether card `cNo2` equips card `cNo1` (by the equip table). */
s32 Ta_GetHandEnchant3(s32 cNo1, s32 cNo2) {
    s32 result;

    switch (D_0029CF32[cNo2]) {
    case 6:
        result = 0x111;
        break;
    case 7:
        result = 0x1AB;
        break;
    case 8:
        switch (cNo1) {
        case 0x156:
            result = 0x1E8;
            break;
        case 7:
            result = 0x1F5;
            break;
        default:
            result = -1;
            break;
        }
        break;
    case 9:
        switch (cNo1) {
        case 0x10:
            result = func_0019A5C8() % 5 + 0xD;
            break;
        case 0x11:
            result = func_0019A5C8() % 5 + 0xD;
            break;
        case 0xA7:
            result = func_0019A5C8() % 15 + 0xD1;
            break;
        case 0x14C:
            result = func_0019A5C8() % 32 + 0x65;
            break;
        case 0x17B:
            result = (u16)TaEnc_GetRandomElf();
            break;
        default:
            result = -1;
            break;
        }
        break;
    default:
        result = cNo1 | 0x10000;
        break;
    }
    return result;
}

/* The power-up of equip effect `eNO`. */
s32 Ta_GetEncEffect(s32 eNO) {
    u8 temp_v1;
    s32 result;

    temp_v1 = D_0029D1F0[eNO];
    switch (temp_v1) {
    case 0:
        switch (D_0029CF32[eNO]) {
        case 0:
            result = 0x219;
            break;
        default:
            result = 0x218;
            break;
        }
        break;
    case 3:
        result = 0x21D;
        break;
    case 2:
        result = 0x21E;
        break;
    case 1:
        switch (D_0029CF32[eNO]) {
        case 5:
            result = 0x21C;
            break;
        default:
            result = 0x218;
            break;
        }
        break;
    default:
        result = 0x218;
        break;
    }
    return result;
}

/* Whether card `cNo` is a toon (the toon field rules). */
s32 Ta_GetToonAgreement(s32 cNo) {
    return ((s32) D_0029D586[cNo * 7] >> 1) & 1;
}

/* Whether equip effect `eNO` has an effect when applied. */
s32 TaEnc_IsEncDo(s32 eNO) {
    u8 temp_v1;

    temp_v1 = D_0029D1F0[eNO];
    switch (temp_v1) {
    case 2:
    case 3:
        return -1;
    case 4:
        if (D_0029CF32[eNO] == 9) {
            return -1;
        }
    default:
        return 1;
    }
}

/* How good equip card `nCardNo` is, for the computer opponent. */
s64 TaEnc_GetEncScore(s32 nCardNo) {
    switch (D_0029D1F0[nCardNo]) {
    case 0:
        return D_0029CF32[nCardNo];
    case 1:
    case 4:
        return 0x3E8;
    default:
        return 0;
    }
}

/* The cards that equip card `nCardNo` can be put on, into `pEncLst`; returns how many. */
s32 TaEnc_GetEnchantLst(u16 nCardNo, u16 *pEncLst) {
    s32 i;
    u16 card;
    s32 count;
    u8 *flags;

    card = 0x2F0;
    count = 0;
    i = 0;
    flags = equipMatchTable + nCardNo * 7;

    do {
        s32 offset;

        if (count >= 0xC) {
            return count;
        }
        offset = card - 0x2F0;
        if ((flags[offset >> 3] >> (offset % 8)) & 1) {
            if (card != 0x315 && card != 0x30C && card != 0x31C) {
                *pEncLst++ = card;
                count++;
            }
        }
        card++;
        i++;
    } while (i < 0x31);

    return count;
}

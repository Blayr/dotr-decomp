#include "common.h"

s32 videoDecGetState(void *arg0) {
    return *(s32 *)((u8 *)arg0 + 0xA8);
}

typedef struct Values_00245160 {
    s64 first;
    s64 second;
    s32 offset;
    s32 fourth;
} Values_00245160;

extern u8 D_003506C8[];

void videoDecPutTs(void *arg0, s64 arg1, s64 arg2, s32 arg3, s32 arg4) {
    Values_00245160 values;

    values.first = arg1;
    values.second = arg2;
    values.offset = arg3 - *(s32 *)((u8 *)arg0 + 0x48);
    values.fourth = arg4;
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

s32 videoDecFlush(void *arg0) {
    Obj_002451A0 *p = (Obj_002451A0 *)arg0;
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

s32 videoDecIsFlushed(void *arg0) {
    s32 result;

    result = 0;
    if (viBufCount((u8 *)arg0 + 0x48) == 0) {
        if (sceMpegIsRefBuffEmpty(arg0) != 0) {
            result = 1;
        }
    }
    return result;
}

void videoDecMain(void *arg0) {
    viBufReset((u8 *)arg0 + 0x48);
    voBufReset(voBuf);
    decBs0(arg0);
    do {

    } while (D_0035060C != 0);
    *(s32 *)((u8 *)arg0 + 0xA8) = 3;
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

s32 mpegError(void *arg0, void *arg1) {
    func_00199B50(&D_0030F8E9, *(s32 *)((u8 *)arg1 + 4));
    return 1;
}

s32 mpegNodata(void) {
    switchThread();
    viBufAddDMA(D_003506C8);
    return 1;
}

s32 mpegStopDMA(void) {
    viBufStopDMA(D_003506C8);
    return 1;
}

s32 mpegRestartDMA(void) {
    viBufRestartDMA(D_003506C8);
    return 1;
}

typedef struct Entry_002455E0 {
    s64 values[2];
    s32 offset;
    s32 size;
} Entry_002455E0;


s32 mpegTS(s32 arg0, void *arg1) {
    Entry_002455E0 entry;

    viBufGetTs(D_003506C8, &entry);
    *(s64 *)((u8 *)arg1 + 8) = entry.values[0];
    *(s64 *)((u8 *)arg1 + 0x10) = entry.values[1];
    return 1;
}

s32 cpy2area(s32 arg0, s32 arg1, s32 arg2, s32 arg3,
                  void *arg4, s32 arg5, s32 arg6, s32 arg7) {
    s32 temp_fp;
    s32 temp_s0;

    temp_s0 = arg5 + arg7;
    if ((arg1 + arg3) < temp_s0) {
        return 0;
    }
    if (arg5 >= arg1) {
        func_00198790((u8 *)arg0, arg4, arg1);
        func_00198790((u8 *)arg2, (u8 *)arg4 + arg1, arg5 - arg1);
        func_00198790(((u8 *)arg2 + arg5) - arg1, (u8 *)arg6, arg7);
    } else {
        temp_fp = arg1 - arg5;
        if (arg7 >= temp_fp) {
            func_00198790((u8 *)arg0, arg4, arg5);
            func_00198790((u8 *)arg0 + arg5, (u8 *)arg6, temp_fp);
            func_00198790((u8 *)arg2, ((u8 *)arg6 + arg1) - arg5, arg7 - temp_fp);
        } else {
            func_00198790((u8 *)arg0, arg4, arg5);
            func_00198790((u8 *)arg0 + arg5, (u8 *)arg6, arg7);
        }
    }
    return temp_s0;
}

typedef struct State_00245770 {
    s32 value;
    u8 *entries;
    s32 field8;
    s32 fieldC;
    s32 count;
} State_00245770;

void voBufCreate(void *arg0, s32 arg1, void *arg2, s32 arg3) {
    State_00245770 *state = arg0;
    s32 *temp_a2;
    s32 var_t0;

    state->value = arg1;
    state->entries = arg2;
    state->count = arg3;
    state->fieldC = 0;
    state->field8 = 0;
    for (var_t0 = 0; var_t0 < arg3; var_t0++) {
        temp_a2 = (s32 *)(state->entries + var_t0 * 0x4CE40);
        *temp_a2 = 0;
    }
}

void voBufDelete(void) {

}

void voBufReset(void *arg0) {
    *(s32 *)((u8 *)arg0 + 0xC) = 0;
    *(s32 *)((u8 *)arg0 + 0x8) = 0;
}

typedef struct {
    u8 pad[0xC];
    s32 field_C;
    s32 field_10;
} Fields_002457E0;

s32 voBufIsFull(void *arg0) {
    return ((Fields_002457E0 *)arg0)->field_C == ((Fields_002457E0 *)arg0)->field_10;
}

typedef struct {
    s32 unk0;
    u8 *data;
    s32 index;
    s32 count;
    s32 capacity;
} Queue_00245800;


void voBufIncCount(void *arg0) {
    Queue_00245800 *queue = (Queue_00245800 *)arg0;

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

static inline u8 empty_00245890(void *arg0) {
    State_00245890 *state = arg0;

    return state->current == state->end;
}

s32 voBufGetData(void *arg0) {
    State_00245890 *state = arg0;

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

static inline u8 is_empty_002458E0(void *arg0) {
    return ((Buffer_002458E0 *)arg0)->count == 0;
}

s32 voBufGetTag(void *arg0) {
    s32 capacity;
    Buffer_002458E0 *buffer = arg0;

    if (is_empty_002458E0(arg0)) {
        return 0;
    }
    capacity = buffer->capacity;
    return buffer->base + ((capacity + (buffer->index - buffer->count)) % capacity) * 0x4CE40;
}

typedef struct Counter_00245960 {
    u8 pad[0xC];
    volatile s32 count;
} Counter_00245960;

void voBufDecCount(void *arg0) {
    Counter_00245960 *counter = arg0;

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

extern Quad_00245980 **gpShFaceIndex[];

void ShAnime_GetPartsRect(s32 arg0, s32 arg1, void *arg2) {
    *(Quad_00245980 *)arg2 = (*gpShFaceIndex[(u8)arg0])[(u8)arg1];
}

typedef struct Name_002459D0 {
    u8 text[8];
} Name_002459D0;

void ShAnime_GetPatInfo(u8 arg0, u8 arg1, void *arg2) {
    *(Name_002459D0 *)arg2 = ((Name_002459D0 **)gpShFaceIndex[arg0])[1][arg1];
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

void ShAnime_GetFixInfo(s32 arg0, s32 arg1, s32 arg2, void *arg3) {
    extern struct Quad_00245980 **gpShFaceIndex[];
    u8 var_a1;
    u8 temp_a0;
    Record_00245A30 *records;
    s32 var_t1;

    var_t1 = 0;
    var_a1 = ((Data_00245A30 *)gpShFaceIndex[arg0 & 0xFF])->indices[arg1 & 0xFF][1];
    if (arg2 != 0) {
        records = ((Data_00245A30 *)gpShFaceIndex[arg0 & 0xFF])->records;
        while (var_t1 != (arg2 & 0xFF)) {
            temp_a0 = *(u8 *)&records[var_a1 & 0xFF];
            if (temp_a0 == 0 || temp_a0 == 0xFF) {
                break;
            }
            var_t1 += 1;
            var_a1 = temp_a0 & 0xFF;
        }
    }
    *(Record_00245A30 *)arg3 = ((Data_00245A30 *)gpShFaceIndex[arg0 & 0xFF])->records[var_a1 & 0xFF];
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

void ShAnime_GetAnmDat(s32 arg0, s32 arg1, s32 arg2, s32 arg3, void *arg4) {
    extern struct Quad_00245980 **gpShFaceIndex[];
    Record_00245AE0 *table;
    u8 var_a1;
    u8 temp_a0;
    Record_00245AE0 *records;
    s32 var_t1;
    s32 count;

    var_t1 = 0;
    var_a1 = ((Data_00245AE0 *)gpShFaceIndex[arg0 & 0xFF])->indices[arg1 & 0xFF][1];
    if (arg2 != 0) {
        records = ((Data_00245AE0 *)gpShFaceIndex[arg0 & 0xFF])->u.records;
        while (var_t1 != (arg2 & 0xFF)) {
            temp_a0 = *(u8 *)&records[var_a1 & 0xFF];
            if (temp_a0 == 0 || temp_a0 == 0xFF) {
                break;
            }
            var_t1 += 1;
            var_a1 = temp_a0 & 0xFF;
        }
    }
    var_t1 = ((Data_00245AE0 *)gpShFaceIndex[arg0 & 0xFF])->u.links[var_a1 & 0xFF][6];
    table = ((Data_00245AE0 *)gpShFaceIndex[arg0 & 0xFF])->u.records;
    count = 0;
    if (arg3 != 0) {
        while (count != (arg3 & 0xFF)) {
            temp_a0 = *(u8 *)&table[var_t1 & 0xFF];
            if (temp_a0 == 0 || temp_a0 == 0xFF) {
                break;
            }
            count += 1;
            var_t1 = temp_a0 & 0xFF;
        }
    }
    *(Record_00245AE0 *)arg4 = table[var_t1 & 0xFF];
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

s32 ShFace_Request(void *arg0) {
    Request_00245BE0 *req = arg0;
    Slot_00245BE0 *entry;
    s32 i;
    extern Slot_00245BE0 gSh_Face[];

    if (req->slot == 0xFF) {
        for (i = 0; i < 8; i++) {
            if (gSh_Face[i].value == 0) {
                break;
            }
        }
        if (i == 8) {
            return 0;
        }
        req->slot = i;
        gSh_Face[req->slot].value = 1;
        gSh_Face[req->slot].b = 0xFF;
    }
    entry = &gSh_Face[req->slot];
    if (entry->value == 0) {
        return 0;
    }
    if (entry->b != req->b) {
        for (i = 0; i < 16; i++) {
            gSh_Face[req->slot].y[i] = 0;
            gSh_Face[req->slot].x[i] = 0;
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

extern Entry_00245D80 gSh_Face[];

void ShFace_Close(u8 *arg0) {
    gSh_Face[*arg0].value = 0;
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

void ShFace_Prim(void *arg0, void *arg1, s32 arg2, s32 arg3) {
    extern s32 gSh_pbVif1;
    Object_00245DB0 *object = arg0;
    u16 *rect = arg1;
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
        ((object->x + 0x6C0) << 4) + (arg2 << shift);
    packet.vertex[1].xyz.y = packet.vertex[0].xyz.y = (y << 4) + (arg3 << shift);
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
    if (gSh_pbVif1 != 0) {
        gSh_pbVif1 = ExSortPrim_Pipe(gSh_pbVif1, (s32)packet.tag, 0, 0);
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

void ShFace_DrawOne(void *arg0) {
    extern void ShAnime_GetFixInfo(u8, u8, u8, void *);
    extern void ShAnime_GetPartsRect(u8, u8, void *);
    extern void ShFace_Prim(void *, void *, u16, u16);
    u8 header[8];
    Buffer_002460F0 entry;
    Frame_002460F0 frame;
    u8 image[8];
    State_002460F0 *state = (State_002460F0 *)arg0;
    s32 randomSum;

    randomSum = ((func_0019A5C8() >> 4) & 0x3F) + ((func_0019A5C8() >> 4) & 0x3F);
    {
    Entry_002460F0 *data;
    s32 slot;
    s32 part;
    s32 randomSmall;

    randomSmall = (func_0019A5C8() >> 4) & 7;
    if (arg0 != NULL) {
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
                    ShFace_Prim(arg0, image, frame.x, frame.y);
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
                ShFace_Prim(arg0, image, entry.record.length, entry.record.value);
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

s32 ShFace_Draw_Pipe(s32 arg0) {
    extern s32 gSh_pbVif1;
    extern s32 ShFace_DrawOne();
    extern s32 SzText_InitClutManage();
    Entry_00246340 *entry;
    s32 i;
    s32 base;

    gSh_pbVif1 = arg0;
    for (i = 0; i < 8; i++) {
        if (((Entry_00246340 *)gSh_Face)[i].value != 0) {
            ((Entry_00246340 *)gSh_Face)[i].handle = SzText_LoadRequest(7, ((Entry_00246340 *)gSh_Face)[i].kind);
        }
    }
    base = RhBase_GetUserGsAddress();
    base += SzText_InitClutManage(base, 2);
    gSh_pbVif1 = SzText_DoRequest_Pipe(gSh_pbVif1, 7, base, NULL);
    gSh_pbVif1 = RhText_SetTextureFlush(gSh_pbVif1);
    SzText_FreeRequest(7, -1);
    entry = (Entry_00246340 *)gSh_Face;
    for (i = 0; i < 8; i++, entry++) {
        if (entry->value != 0 && entry->handle != 0) {
            ShFace_DrawOne(entry);
        }
    }
    return gSh_pbVif1;
}

void ShFace_Init(s32 arg0) {
    extern s32 gSh_pbVif1;
    s32 i;
    Entry_00245D80 *entry;

    gSh_FaceMode = arg0;
    entry = gSh_Face;
    i = 0;
    do {
        i += 1;
        entry->value = 0;
        entry++;
    } while (i < 8);
    gSh_pbVif1 = 0;
}

void ShFace_Draw(void) {
    RhBase_SetVifPacketArea(ShFace_Draw_Pipe(RhBase_GetVifPacketArea()));
}

void ShFace_Act(void) {
    if (gSh_FaceMode) {
        return;
    }
}

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

s32 GetMoveRev(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_s0;
    s32 temp_s1;
    s32 var_s2;
    s32 temp_v0;
    s32 var_v0;
    u32 temp_a0;
    u32 temp_a1;
    u32 temp_a1_2;
    u32 temp_v1;
    u8 temp_a0_3;
    u8 temp_a0_4;
    Effect_002464F0 *temp_a0_2;
    Effect_002464F0 *temp_v0_2;
    Effect_002464F0 *temp_v0_3;

    if (arg0 == 0) {
        return 0;
    }
    var_s2 = 0;
    if (((Card_002464F0 *)arg0)->present == 0) {
        var_v0 = Ta_IsLDAbl(4, ((Card_002464F0 *)arg0)->type);
        if (var_v0 != 0) {
            var_v0 = 2;
        } else {
            var_v0 = 1;
        }
        return var_v0;
    }
    if (((Card_002464F0 *)arg0)->flags.active == 0) {
        var_v0 = 1;
        temp_a0_2 = &((Card_002464F0 *)arg0)->effect;
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
    temp_s1 = (arg2 << 8) | arg1;
    temp_v0 = CheckLandAgreement(SzDuel_GetField(temp_s1 & 0xFF, temp_s1 >> 8), (void *)arg0);
    switch (temp_v0) {
    case 0:
    case 2:
        var_s2 = 1;
        break;
    case 1:
        var_s2 = 2;
        break;
    }
    temp_a0_2 = &((Card_002464F0 *)arg0)->effect;
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
    var_s0 = 0;
    do {
        if (SzDuel_GetUnitStatus(0, var_s0, 4) == 1) {
            if (SzDuel_GetUnitStatus(0, var_s0, 5) == 1) {
                temp_v0_2 = Ta_GetUnitEffect(0, var_s0, 2);
                if (temp_v0_2 != NULL) {
                    temp_a1 = temp_v0_2->kind;
                    if ((temp_a1 >> 8) == 6) {
                        switch (temp_a1 & 0x3F) {
                        case 0xF:
                            temp_a0_3 = ((Card_002464F0 *)arg0)->affiliation;
                            if (((temp_a0_3 & 0x1F) == 0xF) && (((s32) temp_a0_3 >> 5) == 0)) {
                                var_s2 = ((var_s2 >> 4) << 4) | temp_v0_2->value;
                            }
                            break;
                        default:
                            var_s2 = ((var_s2 >> 4) << 4) | temp_v0_2->value;
                            break;
                        }
                    }
                }
            }
        }
        if ((SzDuel_GetUnitStatus(1, var_s0, 4) == 1) && (SzDuel_GetUnitStatus(1, var_s0, 5) == 1)) {
            temp_v0_3 = Ta_GetUnitEffect(1, var_s0, 2);
            if (temp_v0_3 != NULL) {
                temp_a1_2 = temp_v0_3->kind;
                if ((temp_a1_2 >> 8) == 6) {
                    switch (temp_a1_2 & 0x3F) {
                    case 0xF:
                        temp_a0_4 = ((Card_002464F0 *)arg0)->affiliation;
                        if (((temp_a0_4 & 0x1F) == 0xF) && (((s32) temp_a0_4 >> 5) == 0)) {
                            var_s2 = ((var_s2 >> 4) << 4) | temp_v0_3->value;
                        }
                        break;
                    default:
                        var_s2 = ((var_s2 >> 4) << 4) | temp_v0_3->value;
                        break;
                    }
                }
            }
        }
        var_s0 += 1;
    } while (var_s0 < 0xB);
    if (Ta_SearchUncTypeNaturalEffectUser(0x43, 0) >= 0) {
        var_s2 = ((var_s2 >> 4) << 4) | 1;
    }
    var_v0 = var_s2;
    if (Ta_IsLDRangeAvilityFromLoc(temp_s1, ((Card_002464F0 *)arg0)->type, ((Card_002464F0 *)arg0)->affiliation & 0x1F, 0xC) == 1) {
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

static inline s32 encode_00246810(s32 value) {
    return ((value < 0 ? 1 : 0) << 15) | (value >= 0 ? value : -value);
}

s32 Battle(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, void *arg6) {
    extern s32 SzDuel_GetUnitLevel();
    extern s32 SzDuel_GetUnitCardNo();
    extern s32 SzDuel_GetUnitCurseRest();
    Status_00246810 status;
    Status_00246810 *p = &status;
    s32 *out = arg6;
    s32 sp120;
    s32 sp138;
    s32 sp13C;
    s32 sp140;
    s32 sp144;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_s0;
    s32 temp_s0_10;
    s32 temp_s0_11;
    s32 temp_s0_2;
    s32 temp_s0_3;
    s32 temp_s0_4;
    s32 temp_s0_5;
    s32 temp_s0_6;
    s32 temp_s0_7;
    s32 temp_s0_8;
    s32 temp_s0_9;
    s32 temp_s1;
    s32 temp_s1_2;
    s32 temp_s1_3;
    s32 temp_s5;
    s32 temp_s5_2;
    s32 temp_v0_20;
    s32 temp_v0_21;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v0_7;
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
    temp_s1 = SzDuel_GetUnitKind(arg0, arg1) >> 5;
    temp_a0 = SzDuel_GetUnitKind(arg2, arg3) >> 5;
    sp120 = 0;
    var_fp = 0;
    var_s7 = 0;
    if ((temp_s1 == 0) && (temp_a0 == 0)) {
        if (arg1 == 0) {
            temp_s1_2 = Manage_AtkEfc(arg0, arg1, arg2, arg3, p);
            temp_s5 = Ta_GetParamOfs(SzDuel_GetUnit(arg2, arg3), arg4, arg5, 1);
            temp_s5_2 = p->value2 + SzDuel_GetUnitAP(arg2, arg3, 0);
            temp_s5_2 = GetParCap(temp_s5_2 + temp_s5);
            SzDuel_CalcUnitAP(arg2, arg3, 0, p->value2);
            SzDuel_CalcUnitDP(arg2, arg3, 0, p->value2);
            p->value2 = encode_00246810(p->value2);
            if (Ta_IsLDAbl(6, arg0) != 0) {
                out[0] = 0x5D;
                out[1] = (s32) ((p->value2 << 0x10) | ((arg2 << 8) | arg3));
                out[2] = arg0;
                out[3] = (((p->flags.bit6 << 1) | ((temp_s1_2 >> 0x18) & 1)) << 0x16) | ((temp_s5_2 >> 1) | (((p->flags.bit5 << 1) | ((temp_s1_2 >> 0x10) & 1)) << 0x14));
            } else {
                out[0] = 0x5D;
                out[1] = (s32) ((arg2 << 8) | arg3);
                out[2] = arg0;
                out[3] = (((p->flags.bit6 << 1) | ((temp_s1_2 >> 0x18) & 1)) << 0x16) | (temp_s5_2 | (((p->flags.bit5 << 1) | ((temp_s1_2 >> 0x10) & 1)) << 0x14));
            }
            return 1;
        }
        temp_s1_3 = SzDuel_GetUnitAttr(arg2, arg3);
        temp_v0_4 = ChkAttrAdv(temp_s1_3, SzDuel_GetUnitAttr(arg0, arg1));
        switch (temp_v0_4) {                        /* switch 1; irregular */
        case 1:                                     /* switch 1 */
            if (SzDuel_GetUnitCurseRest(arg0, arg1) == 0) {
                var_fp = 1;
            }
            break;
        case -1:                                    /* switch 1 */
            if (SzDuel_GetUnitCurseRest(arg2, arg3) == 0) {
                var_s7 = 1;
            }
            break;
        }
        temp_v0_5 = Manage_AtkEfc(arg0, arg1, arg2, arg3, p);
        if ((temp_v0_5 & 0xFF) == 1) {
            temp_a0_2 = (temp_v0_5 >> 0x18) & 1;
            if ((temp_a0_2 == 1) && (((temp_v0_5 >> 0x10) & 1) == 1)) {
                out[0] = 0x5E;
                out[1] = (s32) ((arg2 << 8) | arg3);
                out[2] = (s32) ((arg0 << 8) | arg1);
                out[3] = (s32) ((p->flags.bit2 << 0x1B) | ((var_s7 << 0x1A) | ((var_fp << 0x19) | ((((p->flags.bit6 << 1) | 1) << 0x16) | ((((p->flags.bit5 << 1) | 1) << 0x14) | 0xCFFFF)))) | 0x10000000);
                temp_s0 = SzDuel_GetUnitCardNo(arg0, arg1);
                                SzData_CalcExp(arg0, temp_s0, 0, (SzDuel_GetUnitLevel(arg2, arg3, 0) + 2) * 2);
                temp_s0_2 = SzDuel_GetUnitCardNo(arg2, arg3);
                                SzData_CalcExp(arg2, temp_s0_2, 0, (SzDuel_GetUnitLevel(arg0, arg1, 0) + 2) * 2);
                return 1;
            }
            if (temp_a0_2 == 1) {
                out[0] = 0x5E;
                out[1] = (s32) ((arg2 << 8) | arg3);
                out[2] = (s32) ((arg0 << 8) | arg1);
                out[3] = (s32) ((p->flags.bit2 << 0x1B) | ((var_s7 << 0x1A) | ((var_fp << 0x19) | ((((p->flags.bit6 << 1) | 1) << 0x16) | (((p->flags.bit5 << 1) << 0x14) | 0x8FFFF)))) | 0x10000000);
                temp_s0_3 = SzDuel_GetUnitCardNo(arg0, arg1);
                                SzData_CalcExp(arg0, temp_s0_3, 0, (SzDuel_GetUnitLevel(arg2, arg3, 0) + 2) * 2);
                return 1;
            }
            if (((temp_v0_5 >> 0x10) & 1) == 1) {
                out[0] = 0x5E;
                out[1] = (s32) ((arg2 << 8) | arg3);
                out[2] = (s32) ((arg0 << 8) | arg1);
                out[3] = (s32) ((p->flags.bit2 << 0x1B) | ((var_s7 << 0x1A) | ((var_fp << 0x19) | ((p->flags.bit6 << 0x17) | ((((p->flags.bit5 << 1) | 1) << 0x14) | 0x4FFFF)))));
                temp_s0_4 = SzDuel_GetUnitCardNo(arg2, arg3);
                                SzData_CalcExp(arg2, temp_s0_4, 0, (SzDuel_GetUnitLevel(arg0, arg1, 0) + 2) * 2);
                return 1;
            }

        }
        temp_v0_7 = SzDuel_GetUnitStatus(arg0, arg1, 3);
        switch (temp_v0_7) {                        /* switch 2; irregular */
        case 1:                                     /* switch 2 */
            if (p->flags.bit3 == 1) {
                SzDuel_CalcUnitAP(arg0, arg1, 4, 0);
                SzDuel_CalcUnitDP(arg0, arg1, 4, 0);
                sp13C = GetParCap(SzDuel_GetUnitDP(arg0, arg1, 0) + Ta_GetParamOfs(SzDuel_GetUnit(arg0, arg1), arg4, arg5, 0));
            } else {
                sp13C = GetParCap(p->value1 + SzDuel_GetUnitDP(arg0, arg1, 0) + Ta_GetParamOfs(SzDuel_GetUnit(arg0, arg1), arg4, arg5, 0));
                SzDuel_CalcUnitAP(arg0, arg1, 0, p->value1);
                SzDuel_CalcUnitDP(arg0, arg1, 0, p->value1);
                p->value1 = encode_00246810(p->value1);
            }
            if (p->flags.bit4 == 1) {
                SzDuel_CalcUnitAP(arg2, arg3, 4, 0);
                SzDuel_CalcUnitDP(arg2, arg3, 4, 0);
                sp138 = GetParCap(SzDuel_GetUnitAP(arg2, arg3, 0) + Ta_GetParamOfs(SzDuel_GetUnit(arg2, arg3), arg4, arg5, 1));
            } else {
                sp138 = GetParCap(p->value2 + SzDuel_GetUnitAP(arg2, arg3, 0) + Ta_GetParamOfs(SzDuel_GetUnit(arg2, arg3), arg4, arg5, 1));
                SzDuel_CalcUnitAP(arg2, arg3, 0, p->value2);
                SzDuel_CalcUnitDP(arg2, arg3, 0, p->value2);
                p->value2 = encode_00246810(p->value2);
            }
            if (sp13C > sp138) {

                if (p->flags.bit1 == 0) {
                    sp120 += sp13C - sp138;

                }
                out[0] = 0x5E;
                out[1] = (s32) ((p->value2 << 0x10) | ((arg2 << 8) | arg3));
                out[2] = (s32) ((p->value1 << 0x10) | ((arg0 << 8) | arg1));
                out[3] = (s32) ((p->flags.bit2 << 0x1B) | ((var_s7 << 0x1A) | ((var_fp << 0x19) | ((((p->flags.bit6 << 1) | ((temp_v0_5 >> 0x18) & 1)) << 0x16) | (sp120 | 0x20000 | (((p->flags.bit5 << 1) | ((temp_v0_5 >> 0x10) & 1)) << 0x14)) | 0x01000000))) | 0x10000000);
                return 1;
            }
            if (sp13C == sp138) {
                out[0] = 0x5E;
                out[1] = (s32) ((p->value2 << 0x10) | ((arg2 << 8) | arg3));
                out[2] = (s32) ((p->value1 << 0x10) | ((arg0 << 8) | arg1));
                out[3] = (s32) ((p->flags.bit2 << 0x1B) | ((var_s7 << 0x1A) | ((var_fp << 0x19) | ((((p->flags.bit6 << 1) | ((temp_v0_5 >> 0x18) & 1)) << 0x16) | (((p->flags.bit5 << 1) | ((temp_v0_5 >> 0x10) & 1)) << 0x14) | 0x01000000))));
                return 1;
            }
            if (sp13C < sp138) {
                out[0] = 0x5E;
                out[1] = (s32) ((p->value2 << 0x10) | ((arg2 << 8) | arg3));
                out[2] = (s32) ((p->value1 << 0x10) | ((arg0 << 8) | arg1));
                out[3] = (s32) ((p->flags.bit2 << 0x1B) | ((var_s7 << 0x1A) | ((var_fp << 0x19) | ((((p->flags.bit6 << 1) | ((temp_v0_5 >> 0x18) & 1)) << 0x16) | ((((p->flags.bit5 << 1) | ((temp_v0_5 >> 0x10) & 1)) << 0x14) | 0x40000)))));
                temp_s0_5 = SzDuel_GetUnitCardNo(arg2, arg3);
                                SzData_CalcExp(arg2, temp_s0_5, 0, (SzDuel_GetUnitLevel(arg0, arg1, 0) + 2) * 2);
                return 1;
            }
            break;
        case 0:                                     /* switch 2 */
            if (p->flags.bit3 == 1) {
                SzDuel_CalcUnitAP(arg0, arg1, 4, 0);
                SzDuel_CalcUnitDP(arg0, arg1, 4, 0);
                sp140 = GetParCap(SzDuel_GetUnitAP(arg0, arg1, 0) + Ta_GetParamOfs(SzDuel_GetUnit(arg0, arg1), arg4, arg5, 1));
            } else {
                sp140 = GetParCap(p->value1 + SzDuel_GetUnitAP(arg0, arg1, 0) + Ta_GetParamOfs(SzDuel_GetUnit(arg0, arg1), arg4, arg5, 1));
                SzDuel_CalcUnitAP(arg0, arg1, 0, p->value1);
                SzDuel_CalcUnitDP(arg0, arg1, 0, p->value1);
                p->value1 = encode_00246810(p->value1);
            }
            if (p->flags.bit4 == 1) {
                SzDuel_CalcUnitAP(arg2, arg3, 4, 0);
                SzDuel_CalcUnitDP(arg2, arg3, 4, 0);
                sp144 = GetParCap(SzDuel_GetUnitAP(arg2, arg3, 0) + Ta_GetParamOfs(SzDuel_GetUnit(arg2, arg3), arg4, arg5, 1));
            } else {
                sp144 = GetParCap(p->value2 + SzDuel_GetUnitAP(arg2, arg3, 0) + Ta_GetParamOfs(SzDuel_GetUnit(arg2, arg3), arg4, arg5, 1));
                SzDuel_CalcUnitAP(arg2, arg3, 0, p->value2);
                SzDuel_CalcUnitDP(arg2, arg3, 0, p->value2);
                p->value2 = encode_00246810(p->value2);
            }
            if (sp140 > sp144) {
                if (p->flags.bit1 == 0) {
                    sp120 = sp140 - sp144;
                }
                out[0] = 0x5E;
                out[1] = (s32) ((p->value2 << 0x10) | ((arg2 << 8) | arg3));
                out[2] = (s32) ((p->value1 << 0x10) | ((arg0 << 8) | arg1));
                out[3] = (s32) ((p->flags.bit2 << 0x1B) | ((var_s7 << 0x1A) | ((var_fp << 0x19) | ((((p->flags.bit6 << 1) | ((temp_v0_5 >> 0x18) & 1)) << 0x16) | (sp120 | 0xA0000 | (((p->flags.bit5 << 1) | ((temp_v0_5 >> 0x10) & 1)) << 0x14))))) | 0x10000000);
                if (sp120 <= 0) {
                    temp_s0_6 = SzDuel_GetUnitCardNo(arg0, arg1);
                                        SzData_CalcExp(arg0, temp_s0_6, 0, (SzDuel_GetUnitLevel(arg2, arg3, 0) + 2) * 2);
                } else {
                    temp_s0_7 = SzDuel_GetUnitCardNo(arg0, arg1);
                                        SzData_CalcExp(arg0, temp_s0_7, 0, SzDuel_GetUnitLevel(arg2, arg3, 0) * 4);
                }
                return 1;
            }
            if (sp140 == sp144) {
                out[0] = 0x5E;
                out[1] = (s32) ((p->value2 << 0x10) | ((arg2 << 8) | arg3));
                out[2] = (s32) ((p->value1 << 0x10) | ((arg0 << 8) | arg1));
                out[3] = (s32) ((p->flags.bit2 << 0x1B) | ((var_s7 << 0x1A) | ((var_fp << 0x19) | ((((p->flags.bit6 << 1) | ((temp_v0_5 >> 0x18) & 1)) << 0x16) | ((((p->flags.bit5 << 1) | ((temp_v0_5 >> 0x10) & 1)) << 0x14) | 0xC0000)))) | 0x10000000);
                temp_s0_8 = SzDuel_GetUnitCardNo(arg0, arg1);
                                SzData_CalcExp(arg0, temp_s0_8, 0, (SzDuel_GetUnitLevel(arg2, arg3, 0) + 2) * 2);
                temp_s0_9 = SzDuel_GetUnitCardNo(arg2, arg3);
                                SzData_CalcExp(arg2, temp_s0_9, 0, (SzDuel_GetUnitLevel(arg0, arg1, 0) + 2) * 2);
                return 1;
            }
            if (sp140 < sp144) {
                if (!(p->flags.bit0)) {
                    sp120 = sp144 - sp140;
                }
                out[0] = 0x5E;
                out[1] = (s32) ((p->value2 << 0x10) | ((arg2 << 8) | arg3));
                out[2] = (s32) ((p->value1 << 0x10) | ((arg0 << 8) | arg1));
                out[3] = (s32) ((p->flags.bit2 << 0x1B) | ((var_s7 << 0x1A) | ((var_fp << 0x19) | ((((p->flags.bit6 << 1) | ((temp_v0_5 >> 0x18) & 1)) << 0x16) | (sp120 | 0x50000 | (((p->flags.bit5 << 1) | ((temp_v0_5 >> 0x10) & 1)) << 0x14))))));
                if (sp120 <= 0) {
                    temp_s0_10 = SzDuel_GetUnitCardNo(arg2, arg3);
                                        SzData_CalcExp(arg2, temp_s0_10, 0, (SzDuel_GetUnitLevel(arg0, arg1, 0) + 2) * 2);
                } else {
                    temp_s0_11 = SzDuel_GetUnitCardNo(arg2, arg3);
                                        SzData_CalcExp(arg2, temp_s0_11, 0, SzDuel_GetUnitLevel(arg0, arg1, 0) * 4);
                }
                return 1;
            }
            break;
        }
    } else {
        if ((temp_s1 == 0) && ((temp_a0 == 1) || ((u32)(temp_a0 - 3) < 3U))) {
            out[0] = 0x5F;
            out[1] = (s32) ((arg0 << 8) | arg1);
            out[2] = (s32) ((arg2 << 8) | arg3);
            out[3] = 1;
            return 1;
        }
        if (temp_s1 == 0) {
            if (temp_a0 == 2) {
                if (Ta_IsLDRangeAvility(arg0, arg1, 0xB) == 1) {
                    out[0] = 0x5F;
                    out[1] = (s32) ((arg0 << 8) | arg1);
                    out[2] = (s32) ((arg2 << 8) | arg3);
                    out[3] = 3;
                    return 0x10001;
                }
                if (Ta_IsResistAll(arg0, arg1) != 0) {
                    out[0] = 0x5F;
                    out[1] = (s32) ((arg0 << 8) | arg1);
                    out[2] = (s32) ((arg2 << 8) | arg3);
                    out[3] = 1;
                    return 0x10001;
                }
                temp_v0_20 = Chk_Enc(arg0, arg1, SzDuel_GetUnitCardNo(arg2, arg3));
                if (temp_v0_20 == 0x3E7) {
                    out[0] = 0x5F;
                    out[1] = (s32) ((arg0 << 8) | arg1);
                    out[2] = (s32) ((arg2 << 8) | arg3);
                    out[3] = 1;
                    return 0x10001;
                }
                if (((temp_v0_20 >> 0x1E) & 1) == 1) {
                    SzDuel_SetUnitStatus(arg2, arg3, 2, 1);
                    out[0] = 0x2B;
                    out[1] = (s32) ((arg2 << 8) | arg3);
                    out[2] = (s32) ((arg0 << 8) | arg1);
                    out[3] = (s32) ((temp_v0_20 >> 0xE) & 0x3FFF);
                    return 0x10001;
                }
                if ((temp_v0_20 >> 0xE) == 0x219) {
                    SzDuel_SetUnitStatus(arg2, arg3, 2, 1);
                    out[0] = 0x25;
                    out[1] = (s32) ((arg0 << 8) | arg1);
                    out[2] = (s32) ((arg2 << 8) | arg3);
                    out[3] = (s32) ((temp_v0_20 & 0x3FFF) | (Ta_GetCurrentSide(arg2, arg3) << 0x10));
                } else {
                    SzDuel_SetUnitStatus(arg2, arg3, 2, 1);
                    out[0] = 0x24;
                    out[1] = (s32) ((arg0 << 8) | arg1);
                    out[2] = (s32) ((arg2 << 8) | arg3);
                    out[3] = temp_v0_20;
                }
                return 0x10001;
            }
        }

        if (temp_s1 == 2) {
            if (temp_a0 == 0) {
                SzData_CalcExp(arg2, SzDuel_GetUnitCardNo(arg2, arg3), 0, 6);
                if (Ta_IsLDRangeAvility(arg2, arg3, 0xB) == 1) {
                    out[0] = 0x5F;
                    out[1] = (s32) ((arg0 << 8) | arg1);
                    out[2] = (s32) ((arg2 << 8) | arg3);
                    out[3] = 2;
                    return 1;
                }
                if (Ta_IsResistAll(arg2, arg3) != 0) {
                    out[0] = 0x5F;
                    out[1] = (s32) ((arg0 << 8) | arg1);
                    out[2] = (s32) ((arg2 << 8) | arg3);
                    out[3] = 0;
                    return 1;
                }
                temp_v0_21 = Chk_Enc(arg2, arg3, SzDuel_GetUnitCardNo(arg0, arg1));
                if (temp_v0_21 == 0x3E7) {
                    out[0] = 0x5F;
                    out[1] = (s32) ((arg0 << 8) | arg1);
                    out[2] = (s32) ((arg2 << 8) | arg3);
                    out[3] = 0;
                    return 1;
                }
                if (((temp_v0_21 >> 0x1E) & 1) == 1) {
                    SzDuel_SetUnitStatus(arg0, arg1, 2, 1);
                    out[0] = 0x2B;
                    out[1] = (s32) ((arg0 << 8) | arg1);
                    out[2] = (s32) ((arg2 << 8) | arg3);
                    out[3] = (s32) ((temp_v0_21 >> 0xE) & 0x3FFF);
                    return 1;
                }
                if ((temp_v0_21 >> 0xE) == 0x219) {
                    SzDuel_SetUnitStatus(arg0, arg1, 2, 1);
                    out[0] = 0x25;
                    out[1] = (s32) ((arg0 << 8) | arg1);
                    out[2] = (s32) ((arg2 << 8) | arg3);
                    out[3] = (s32) ((temp_v0_21 & 0x3FFF) | (Ta_GetCurrentSide(arg0, arg1) << 0x10));
                } else {
                    SzDuel_SetUnitStatus(arg0, arg1, 2, 1);
                    out[0] = 0x24;
                    out[1] = (s32) ((arg0 << 8) | arg1);
                    out[2] = (s32) ((arg2 << 8) | arg3);
                    out[3] = temp_v0_21;
                }
                return 1;
            }

        }
        if (((u32)(temp_s1 - 1) < 5U) && ((u32) temp_a0 < 6U)) {
            out[0] = 0x5F;
            out[1] = (s32) ((arg0 << 8) | arg1);
            out[2] = (s32) ((arg2 << 8) | arg3);
            out[3] = 0;
            if (temp_a0 == 0) {
                SzData_CalcExp(arg2, SzDuel_GetUnitCardNo(arg2, arg3), 0, 6);
            }
            return 1;
        }
    }
    return 0;
}

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

s32 Do_ChkEncMatch(u32 arg0, s32 arg1, s32 arg2) {
    extern s32 SzDuel_GetUnitCardNo();
    s32 offset;
    s32 row;

    if (arg0 < 2U) {
        if (arg1 == 0) {
            return 0;
        }
    }

    if (arg2 == 0x304) {
        if ((SzDuel_GetUnitKind((s32)arg0, arg1) >> 5) == 0) {
            if ((SzDuel_GetUnitKind((s32)arg0, arg1) & 0x1F) == 2) {
                return 1;
            }
        }
        return 0;
    }

    row = SzDuel_GetUnitCardNo(arg0, arg1) * 7;
    offset = arg2 - 0x2F0;
    return ((EnchMatch + (offset >> 3))[row] >> (offset % 8)) & 1;
}

extern int func_001E1030_b(int a, int b);
extern unsigned *func_001E0B70_b(int a, int b, int n);
extern void func_002503B0_b(int a, int b, unsigned char n);
extern int func_001E15E0_b(int a, int b, int value);
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

int Enchant(int a, int b, int c, int d)
{
    int total;
    int id;

    func_001E1030_b(a, b);
    total = 0;
    total += Ta_GetEnchantOfs();
    id = c & 0x3fff;
    if (Do_ChkEncMatch(a, b, id) != 0) {
        c = apply_kind_00248460(a, b, c, d, total, id);
    } else {
        c = -1;
    }
    return c;
}

s32 Do_Chk_Enc(s32 arg0, s32 arg1) {
    s32 bit;

    bit = arg1 - 0x2F0;
    if ((EnchMatch[arg0 * 7 + (bit >> 3)] >> (bit % 8)) & 1) {
        switch (D_0029D1F0[arg1]) {
        case 4:
            switch (D_0029CF32[arg1]) {
            case 6:
                return arg1 | 0x40444000;
            case 7:
                return arg1 | 0x406AC000;
            case 8:
                switch (arg0) {
                case 0x156:
                    return arg1 | 0x407A0000;
                case 7:
                    return arg1 | 0x407D4000;
                }
                break;
            case 9:
                switch (arg0) {
                case 0x10:
                    return arg1 | (((func_0019A5C8() % 5 + 0xD) << 14) | 0x40000000);
                case 0x11:
                    return arg1 | (((func_0019A5C8() % 5 + 0xD) << 14) | 0x40000000);
                case 0xA7:
                    return arg1 | (((func_0019A5C8() % 15 + 0xD1) << 14) | 0x40000000);
                case 0x14C:
                    return arg1 | (((func_0019A5C8() % 32 + 0x65) << 14) | 0x40000000);
                case 0x17B:
                    return arg1 | (((u16)TaEnc_GetRandomElf() << 14) | 0x40000000);
                }
                break;
            }
            break;
        case 0:
            switch (D_0029CF32[arg1]) {
            case 0:
                return arg1 | 0x864000;
            default:
                return arg1 | 0x860000;
            }
        case 3:
            return arg1 | 0x874000;
        case 2:
            return arg1 | 0x878000;
        case 1:
            switch (D_0029CF32[arg1]) {
            case 5:
                return arg1 | 0x870000;
            default:
                return arg1 | 0x860000;
            }
        default:
            return arg1 | 0x860000;
        }
    } else {
        return 0x3E7;
    }
    return 0x3E7;
}

s32 Chk_Enc(s32 arg0, s32 arg1, s32 arg2) {
    s32 kind;
    extern s32 SzDuel_GetUnitCardNo();

    kind = SzDuel_GetUnitCardNo(arg0, arg1);
    if (Do_ChkEncMatch(arg0, arg1, arg2) != 0) {
        switch (D_0029D1F0[arg2]) {
        case 4:
            switch (D_0029CF32[arg2]) {
            case 6:
                return arg2 | 0x40444000;
            case 7:
                return arg2 | 0x406AC000;
            case 8:
                switch (kind) {
                case 0x156:
                    return arg2 | 0x407A0000;
                case 7:
                    return arg2 | 0x407D4000;
                }
                break;
            case 9:
                switch (kind) {
                case 0x10:
                    return arg2 | (((func_0019A5C8() % 5 + 0xD) << 14) | 0x40000000);
                case 0x11:
                    return arg2 | (((func_0019A5C8() % 5 + 0xD) << 14) | 0x40000000);
                case 0xA7:
                    return arg2 | (((func_0019A5C8() % 15 + 0xD1) << 14) | 0x40000000);
                case 0x14C:
                    return arg2 | (((func_0019A5C8() % 32 + 0x65) << 14) | 0x40000000);
                case 0x17B:
                    return arg2 | (((u16)TaEnc_GetRandomElf() << 14) | 0x40000000);
                }
                break;
            }
            break;
        case 0:
            switch (D_0029CF32[arg2]) {
            case 0:
                return arg2 | 0x864000;
            default:
                return arg2 | 0x860000;
            }
        case 3:
            return arg2 | 0x874000;
        case 2:
            return arg2 | 0x878000;
        case 1:
            switch (D_0029CF32[arg2]) {
            case 5:
                return arg2 | 0x870000;
            default:
                return arg2 | 0x860000;
            }
        default:
            return arg2 | 0x860000;
        }
    } else {
        return 0x3E7;
    }
    return 0x3E7;
}

s32 Ta_GetForceEffection(s32 arg0, s32 arg1) {
    s32 var_v0;

    if (arg0 < 2) {
        var_v0 = SzDuel_GetLP((arg0 == 0) ? 1 : 0) >> 1;
    } else {
        var_v0 = SzDuel_GetLP((SzDuel_GetTurnOwner() == 0) ? 1 : 0) >> 1;
    }
    var_v0 = Ta_GetLPRevByNaturalEffect(0x2C, var_v0);
    var_v0 += arg1;
    return var_v0;
}

typedef struct Entry_00248EA0 {
    u32 unk0;
    u32 value;
} Entry_00248EA0;


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

s32 Ta_GetHandEnchant(s32 arg0, s32 arg1) {
    s32 temp_a2;

    temp_a2 = arg1 - 0x2F0;
    if ((EnchMatch[arg0 * 7 + (temp_a2 >> 3)] >> (temp_a2 % 8)) & 1) {
        return Ta_GetHandEnchant3(arg0, arg1);
    }
    return -1;
}

s32 Ta_GetHandEnchant2(s32 arg0, s32 arg1, s32 arg2) {
    extern s32 SzDuel_GetUnitCardNo();

    if (Do_ChkEncMatch(arg0, arg1, arg2) != 0) {
        return Ta_GetHandEnchant3(SzDuel_GetUnitCardNo(arg0, arg1), arg2);
    }
    return -1;
}

s32 Ta_GetHandEnchant3(s32 arg0, s32 arg1) {
    s32 result;

    switch (D_0029CF32[arg1]) {
    case 6:
        result = 0x111;
        break;
    case 7:
        result = 0x1AB;
        break;
    case 8:
        switch (arg0) {
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
        switch (arg0) {
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
        result = arg0 | 0x10000;
        break;
    }
    return result;
}

s32 Ta_GetEncEffect(s32 arg0) {
    u8 temp_v1;
    s32 result;

    temp_v1 = D_0029D1F0[arg0];
    switch (temp_v1) {
    case 0:
        switch (D_0029CF32[arg0]) {
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
        switch (D_0029CF32[arg0]) {
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

s32 Ta_GetToonAgreement(s32 arg0) {
    return ((s32) D_0029D586[arg0 * 7] >> 1) & 1;
}

s32 TaEnc_IsEncDo(s32 arg0) {
    u8 temp_v1;

    temp_v1 = D_0029D1F0[arg0];
    switch (temp_v1) {
    case 2:
    case 3:
        return -1;
    case 4:
        if (D_0029CF32[arg0] == 9) {
            return -1;
        }
    default:
        return 1;
    }
}

s64 TaEnc_GetEncScore(s32 arg0) {
    switch (D_0029D1F0[arg0]) {
    case 0:
        return D_0029CF32[arg0];
    case 1:
    case 4:
        return 0x3E8;
    default:
        return 0;
    }
}

s32 TaEnc_GetEnchantLst(u16 arg0, u16 *arg1) {
    s32 i;
    u16 card;
    s32 count;
    u8 *flags;

    card = 0x2F0;
    count = 0;
    i = 0;
    flags = EnchMatch + arg0 * 7;

    do {
        s32 offset;

        if (count >= 0xC) {
            return count;
        }
        offset = card - 0x2F0;
        if ((flags[offset >> 3] >> (offset % 8)) & 1) {
            if (card != 0x315 && card != 0x30C && card != 0x31C) {
                *arg1++ = card;
                count++;
            }
        }
        card++;
        i++;
    } while (i < 0x31);

    return count;
}

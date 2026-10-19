/* Duelist face pictures (ShFace_*). */

#include "common.h"

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

#include "common.h"

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
extern struct DotrObject *D_0031ABB0_b[];
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
    p = D_0031ABB0_b[index];
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
    extern Slot_001EDFD0 motionBlurs;
    extern Slot_001EDFD0 D_0031BA90;
    extern s32 motionBlurMode;
    extern s32 SzModel_ExSort_Pipe();
    Slot_001EDFD0 *scratch;
    s32 ready;
    s32 remaining;
    View_001EDFD0 *obj;
    Slot_001EDFD0 *slot;
    s32 i;

    scratch = &motionBlurs;
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
extern s32 motionBlurMode; /* original: gSzModel_nBlurMode */

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
#pragma global_optimizer reset

struct DotrExSortVec {
    float x, y, z, w;
};
extern int D_0031BB00_1ef8a0;
extern long func_00208680_b(int, int);
extern int func_002084D0_b(int, long);
extern int func_00207500_b(void);

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
    s32 var_s3_2;
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
    var_s3_2 = 0;
    cur = obj;
    do {
        if (*(s32 *)(*(u8 **)&obj->pad040[0xF8] + 4) & (1 << (var_s3_2 + 0xB))) {
            RhText_BindAddress((s32) motionData);
            *(u8 **)((u8 *)cur + 0x144) = motionData;
            motionData += *(s32 *)(motionData + 8);
        } else {
            *(u8 **)((u8 *)cur + 0x144) = NULL;
        }
        var_s3_2 += 1;
        cur = (Obj_0031ABB0 *)((u8 *)cur + 4);
    } while (var_s3_2 < 8);
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

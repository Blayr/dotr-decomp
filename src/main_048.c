#include "common.h"

void func_001ED460(s32 arg0) {
    Obj_0031ABB0 *obj;

    if (arg0 < 0 || arg0 >= 0x54) {
        return;
    }
    obj = D_0031ABB0[arg0];
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

s32 func_001ED4A0(s32 index)
{
    Fields_001ED4A0 *fields;
    Obj_0031ABB0 *obj;
    Animation_001ED4A0 *animation;
    Animation_001ED4A0 *previous;
    s8 *current_slot;
    s8 *previous_slot;
    s8 *next_slot;
    f32 ticks;
    extern s32 func_001A8760();

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = D_0031ABB0[index];
    if (obj == NULL) {
        return 0;
    }
    fields = (Fields_001ED4A0 *)obj;
    animation = (Animation_001ED4A0 *)&obj->slots[8];
    previous = (Animation_001ED4A0 *)&obj->slots[11];
    current_slot = &obj->lv[0];
    previous_slot = &obj->lv[1];
    next_slot = &obj->lv[3];
    ticks = (f32)func_001A8760();
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

int func_001EDA40(int channel, int index)
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
            now = func_001F5320(*(int *)&p->unknown_1e8[4]);
        }
        previous = now - previous;
        for (i = 0; i < 64; i++, cue++) {
            if (cue->kind == 15) {
                break;
            }
            if (cue->kind == kind) {
                if (cue->time >= previous && cue->time < now) {
                    func_00217710(channel, cue->code);
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

s32 func_001EDCB0(s32 index, s16 duration, s32 mode, void *color0, void *color1, s32 enabled) {
    extern Entry_001EDCB0 D_0031AD70[];
    Obj_0031ABB0 *obj;
    Entry_001EDCB0 *entry;
    s32 i;
    s32 j;

    obj = D_0031ABB0[index];
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
            func_0020B380(entry, obj, 4);
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

void func_001EDF20(s32 arg0) {
    s32 var_a3;
    Entry_001EDF20 *var_t0;
    s32 temp_v1;

    var_a3 = 1;
    var_t0 = D_0031AD70;
    do {
        temp_v1 = var_t0->id;
        if (temp_v1 >= 0) {
            if (arg0 < 0 || temp_v1 == arg0) {
                var_t0->id = -1;
            }
        }
        var_a3 += 1;
        var_t0++;
    } while (var_a3 < 0x20);
}

void func_001EDF90(s32 arg0) {
    func_00209D30(func_001EDFD0(func_00209D20(), arg0));
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

s32 func_001EDFD0(s32 arg0, s32 arg1) {
    extern Slot_001EDFD0 D_0031AD00;
    extern Slot_001EDFD0 D_0031BA90;
    extern s32 D_0031BB00;
    extern s32 func_001EF8A0();
    Slot_001EDFD0 *scratch;
    s32 ready;
    s32 remaining;
    View_001EDFD0 *obj;
    Slot_001EDFD0 *slot;
    s32 i;

    scratch = &D_0031AD00;
    ready = 0;
    D_0031BB00 = (arg1 < 0) ? 2 : 1;
    remaining = 31;
    slot = &D_0031BA90;
    do {
        if (slot->index >= 0 && (arg1 < 0 || slot->index == arg1)) {
            if (func_001F1370(slot->index) == 0) {
                slot->index = -1;
            } else {
                obj = (View_001EDFD0 *)D_0031ABB0[slot->index];
                if (obj == NULL) {
                    goto next;
                }
                if (arg1 < 0) {
                    if (!slot->alternate) {
                        goto next;
                    }
                } else if (slot->alternate) {
                    goto next;
                }
                {
                    if (!ready) {
                        func_001EE4A0(0);
                        ready = 1;
                    }
                    for (i = 0; i < 2; i++) {
                        scratch->pos[i] = obj->pos[i];
                        scratch->level[i] = obj->level[i];
                    }
                    func_0020B380(scratch, obj, 4);
                    scratch->color = obj->color;
                    scratch->style = obj->style;
                    for (i = 0; i < 2; i++) {
                        obj->pos[i] = slot->pos[i];
                        obj->level[i] = slot->level[i];
                    }
                    func_0020B380(obj, slot, 4);
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
                        arg0 = func_001EF8A0(arg0, slot->index, 0, 0, 0, 0, 0x80FFFFF5);
                    } else {
                        arg0 = func_001EE4B0(arg0, slot->index, 0, 0, 0, 0, 0x80FFFFF5);
                    }
                    for (i = 0; i < 2; i++) {
                        obj->pos[i] = scratch->pos[i];
                        obj->level[i] = scratch->level[i];
                    }
                    func_0020B380(obj, scratch, 4);
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
        func_001EE4A0(0);
    }
    D_0031BB00 = 0;
    return arg0;
}

void func_001EE4A0(s32 arg0) {
    D_0031BB10 = arg0;
}

s32 func_001EE4B0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    Obj_0031ABB0 *temp_v1;
    s8 temp_v1_2;
    void *temp_t4;
    void (*callback)(void) = NULL;

    if ((arg1 < 0) || (arg1 >= 0x54)) {
        return arg0;
    }
    temp_v1 = D_0031ABB0[arg1];
    if (temp_v1 == NULL) {
        return arg0;
    }
    if (*(s32 *)((u8 *)temp_v1 + 0x138) == 0) {
        return arg0;
    }
    temp_t4 = *(void **)((u8 *)temp_v1 + 0x13C);
    if (temp_t4 == NULL) {
        return arg0;
    }
    temp_v1_2 = *(s8 *)((u8 *)temp_v1 + 0x1F3);
    if ((temp_v1_2 == 4) || (temp_v1_2 == 5U) || (temp_v1_2 == 6)) {
        if (*(s32 *)((u8 *)temp_t4 + 0x1C) != 0) {
            callback = func_001EE570;
        }
    }
    return func_001EE6C0(arg0, arg1, arg2, arg3, arg4, arg5, arg6, callback, 0);
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

void func_001EE570(s32 arg0) {
    extern s32 func_00208870();
    extern s32 func_00209F70();
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
    func_00209F70(func_0020A0B0(func_00207650(func_0020A0B0(func_00209F70(func_0020F290(func_00208870(func_0020F290(arg0), -1, 0, &packet.extra[1], &packet.extra[2])), 0xFF000000), 0), (s32)(&packet.dmatag + 1), 0, 0), 1), 0);
}

INCLUDE_ASM("asm/nonmatchings/main_048", func_001EE6C0);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001EF8A0);

s32 func_001EFA80(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    s32 saved;

    saved = func_001F3210(arg1);
    func_001F3190(arg1, 0);
    arg0 = func_001EE4B0(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
    func_001F3190(arg1, saved);
    return arg0;
}

s32 func_001EFB40(s32 arg0, s32 arg1, s32 *arg2) {
    s32 sp1C;
    Obj_0031ABB0 *temp_v1;
    s32 temp_a2;

    sp1C = 0;
    if ((arg0 < 0) || (arg0 >= 0x54)) {
        return 0;
    }
    temp_v1 = D_0031ABB0[arg0];
    if (temp_v1 == NULL) {
        return 0;
    }
    if (arg2 != NULL) {
        *arg2 = 1;
    }
    temp_a2 = *(s32 *)((u8 *)temp_v1 + 0x134);
    return func_001EFBD0(arg1, temp_a2, temp_a2, &sp1C, 0, arg2, 0);
}

typedef struct Node_001EFBD0 {
    u8 pad0[0x1C];
    s32 child;
    u8 pad20[0xC];
    s32 sibling;
} Node_001EFBD0;

s32 func_001EFBD0(s32 target, s32 base, s32 node, s32 *index,
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
            result = func_001EFBD0(target, base,
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

void func_001EFD30(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    func_00209D30(func_001EFDC0(func_00209D20(), arg0, arg1, arg2, arg3, arg4, arg5));
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

s32 func_001EFDC0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    extern s32 func_001EE6C0();
    extern s32 func_002084D0();
    Info_001EFDC0 info;
    s32 saved;
    s32 ret;

    saved = func_001F3210(arg1);
    D_0031BB10 = 0;
    arg0 = func_002085E0(arg0, 2);
    arg0 = func_0020A0B0(arg0, 1);
    func_001F3190(arg1, 0);
    if (arg5 != 0 || arg6 != 0) {
        arg0 = func_001EE6C0(arg0, arg1, 0, 0, 0, (s32)info.data, 0, arg5, arg6);
    } else {
        arg0 = func_001EE4B0(arg0, arg1, 0, 0, 0, (s32)info.data, 0);
    }
    func_001F3190(arg1, saved);
    ret = func_002084D0(func_002085E0(func_0020A0B0(arg0, 0), 3), func_00208680(0, 4));
    info.bits.flag = info.bits.kind = arg2;
    *(Word_001EFDC0 *)arg3 = info.word;
    *(Bits_001EFDC0 *)arg4 = info.bits;
    return ret;
}

typedef struct Flags_001EFF70 {
    s64 loaded : 1;
    s64 unused1 : 2;
    s64 pending : 1;
    s64 rest : 60;
} Flags_001EFF70;

s32 func_001EFF70(s32 arg0, void *arg1) {
    extern void func_001F08D0(s32);
    extern void func_001F01A0();
    extern s32 func_001FEC70();
    Obj_0031ABB0 *obj;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    obj = D_0031ABB0[arg0];
    if (obj == NULL) {
        return 0;
    }
    if (((Flags_001EFF70 *)&obj->lv[0x2C])->pending) {
        return 0;
    }
    func_001F08D0(arg0);
    ((Flags_001EFF70 *)&obj->lv[0x2C])->loaded = 1;
    if (func_001FEC70(arg0, arg1, 0, -1, func_001F01A0, arg0) != 0) {
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

s32 func_001F0060(s32 arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    extern void func_001F08D0(s32);
    extern s32 func_001F0390();
    extern s32 func_001FECB0();
    Obj_001F0060 *obj;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    obj = (Obj_001F0060 *)D_0031ABB0[arg0];
    if (obj == NULL) {
        return 0;
    }
    if (obj->bit3) {
        return 0;
    }
    func_001F08D0(arg0);
    obj->bit0 = (arg2 != 0) ? 0 : 1;
    if (func_001FECB0(arg0, 0, (s32)arg1, arg2, arg3, arg4, arg5, (s32)func_001F0390, arg0) != 0) {
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

void func_001F01A0(void *arg0, s32 arg1) {
    extern void func_0019B648();
    extern void func_001E8BF0(s32);
    extern s32 D_00292480[];
    extern u8 D_002CFA17[];
    extern u8 D_002CFB94[];
    s32 index;
    Fields_001F01A0 *obj;

    index = ((Request_001F01A0 *)arg0)->index;
    if (index < 0 || index >= 0x54) {
        return;
    }
    obj = (Fields_001F01A0 *)D_0031ABB0[index];
    if (obj != NULL) {
        if (arg1 == 0) {
            obj->busy = 0;
            return;
        }
        func_001E7D00(index);
        obj->header = ((Request_001F01A0 *)arg0)->header;
        obj->data = obj->header + 4;
        obj->header[1] = 0;
        func_0020F370(obj->header);
        func_001E90B0(index);
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
            base = D_00292480[obj->kind];
            func_0019B648(format, D_002CFB94, func_001FFF90((s32)D_002CFA17), base, base);
            for (i = 0; i < 8; i++) {
                func_0019B648(path, format, value, value, i + 0x61);
                func_001F0760(index, i, (s32)path);
            }
            func_001EA0F0(index);
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
            base = D_00292480[obj->kind];
            func_0019B648(format, D_002CFB94, func_001FFF90((s32)D_002CFA17), base, base);
            func_0019B648(path, format, value, value, 0x61);
            func_001F0760(index, 0, (s32)path);
            break;
        }
        }
        func_001FFC50(index, (s32)func_001E8BF0);
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

void func_001F0390(s32 arg0, s32 arg1) {
    extern void func_0019B648();
    extern void func_001F01A0();
    extern s32 func_001FEC70();
    extern s32 D_00292480[];
    extern u8 D_002CFA17[];
    extern u8 D_002CFA1D[];
    u8 format[128];
    u8 path[128];
    s32 index;
    Fields_001F0390 *obj;
    s32 base;

    index = ((Request_001F0390 *)arg0)->index;
    if (index < 0 || index >= 0x54) {
        return;
    }
    obj = (Fields_001F0390 *)D_0031ABB0[index];
    if (obj != NULL) {
        if (arg1 != 0 && *((Request_001F0390 *)arg0)->header != 0x304852) {
            arg1 = 0;
        }
        if (arg1 == 0) {
            base = D_00292480[obj->kind];
            func_0019B648(format, D_002CFA1D, func_001FFF90((s32)D_002CFA17), base, base);
            func_0019B648(path, format, obj->value, obj->value);
            obj->loaded = 1;
            arg0 = func_001FEC70(index, path, 0, -1, func_001F01A0, index);
            obj->busy = (arg0 != 0) ? 1 : 0;
        } else {
            func_001E7D00(index);
            func_001F0500(index, ((Request_001F0390 *)arg0)->header);
        }
    }
}

typedef struct {
    u32 header[2];
    u8 data[0x7FF8];
} FixedBlock_001F0500;


s32 func_001F0500(s32 arg0, void *arg1) {
    Obj_0031ABB0 *temp_s0;
    u8 *var_s1;
    s32 var_s2;
    Obj_0031ABB0 *var_s3;
    Obj_0031ABB0 *var_s2_2;
    s32 var_s3_2;
    u8 *temp_v1;

    temp_s0 = D_0031ABB0[arg0];
    if (temp_s0 == NULL) {
        return 0;
    }
    *(u8 **)&temp_s0->pad040[0xF8] = arg1;
    *(u8 **)((u8 *)temp_s0 + 0x13C) = *(u8 **)&temp_s0->pad040[0xF8] + 0x10;
    func_0020F370(*(u8 **)&temp_s0->pad040[0xF8]);
    func_001E8FA0(arg0);
    temp_v1 = *(u8 **)&temp_s0->pad040[0xF8];
    var_s2 = 0;
    var_s3 = temp_s0;
    var_s1 = temp_v1 + *(s32 *)(temp_v1 + 0xC);
    do {
        if (*(s32 *)(*(u8 **)&temp_s0->pad040[0xF8] + 4) & (1 << var_s2)) {
            var_s3->slots[0] = (ObjSlot_0031ABB0 *)var_s1;
            func_00214090(var_s3->slots[0]);
            var_s3->vals[0] = var_s3->slots[0]->f14->f4;
            var_s1 += *(s32 *)(var_s1 + 4);
        } else {
            var_s3->vals[0] = 1;
            var_s3->slots[0] = NULL;
        }
        var_s2 += 1;
        var_s3 = (Obj_0031ABB0 *)((u8 *)var_s3 + 4);
    } while (var_s2 < 8);
    if (*(s32 *)(*(u8 **)&temp_s0->pad040[0xF8] + 4) & 0x100) {
        *(u8 **)((u8 *)temp_s0 + 0x164) = var_s1;
        var_s1 = ((FixedBlock_001F0500 *)var_s1)->data + 0x7FF8;
    } else {
        *(u8 **)((u8 *)temp_s0 + 0x164) = NULL;
    }
    if (*(s32 *)(*(u8 **)&temp_s0->pad040[0xF8] + 4) & 0x200) {
        func_0020F250((s32) var_s1);
        *(u8 **)((u8 *)temp_s0 + 0x140) = var_s1;
        var_s1 += *(s32 *)(var_s1 + 8);
    } else {
        *(u8 **)((u8 *)temp_s0 + 0x140) = NULL;
    }
    if (*(s32 *)(*(u8 **)&temp_s0->pad040[0xF8] + 4) & 0x400) {
        *(u8 **)((u8 *)temp_s0 + 0x168) = var_s1;
        var_s1 = ((FixedBlock_001F0500 *)var_s1)->data + 0x7FF8;
    } else {
        *(u8 **)((u8 *)temp_s0 + 0x168) = NULL;
    }
    var_s3_2 = 0;
    var_s2_2 = temp_s0;
    do {
        if (*(s32 *)(*(u8 **)&temp_s0->pad040[0xF8] + 4) & (1 << (var_s3_2 + 0xB))) {
            func_0020F250((s32) var_s1);
            *(u8 **)((u8 *)var_s2_2 + 0x144) = var_s1;
            var_s1 += *(s32 *)(var_s1 + 8);
        } else {
            *(u8 **)((u8 *)var_s2_2 + 0x144) = NULL;
        }
        var_s3_2 += 1;
        var_s2_2 = (Obj_0031ABB0 *)((u8 *)var_s2_2 + 4);
    } while (var_s3_2 < 8);
    if (*(s32 *)(*(u8 **)&temp_s0->pad040[0xF8] + 4) & 0x80000) {
        s32 size = (*(s32 *)(var_s1 + 8) + 0xF) & ~0xF;
        *(u8 **)((u8 *)temp_s0 + 0x16C) = var_s1;
        var_s1 += size;
    }
    if (*(s32 *)(*(u8 **)&temp_s0->pad040[0xF8] + 4) & 0x100000) {
        s32 size = (*(s32 *)(var_s1 + 8) + 0xF) & ~0xF;
        *(u8 **)((u8 *)temp_s0 + 0x170) = var_s1;
        var_s1 += size;
    }
    if (*(s32 *)(*(u8 **)&temp_s0->pad040[0xF8] + 4) & 0x200000) {
        *(u8 **)((u8 *)temp_s0 + 0x174) = var_s1;
    } else {
        *(u8 **)((u8 *)temp_s0 + 0x174) = NULL;
    }
    func_001E8BF0(arg0);
    return 1;
}

s32 func_001F0760(s32 arg0, s32 arg1, s32 arg2) {
    extern void func_001FEC70();

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    if (arg1 < 0 || arg1 >= 8) {
        return 0;
    }
    if (D_0031ABB0[arg0] == NULL) {
        return 0;
    }
    func_001F0C10(arg0, arg1);
    func_001FEC70(arg0, arg2, 0, -1, func_001F0830, (arg0 << 8) | arg1);
    return 1;
}

typedef struct {
    u8 pad00[0x14];
    ObjSlot_0031ABB0 *f14;
    u8 pad18[4];
    s32 f1C;
} Arg_001F0830;


void func_001F0830(void *arg0, s32 arg1) {
    Arg_001F0830 *a = (Arg_001F0830 *)arg0;
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
    base = D_0031ABB0[idx];
    if (base != NULL && arg1 != 0) {
        base->slots[sub] = a->f14;
        func_00214090(base->slots[sub]);
        base->vals[sub] = base->slots[sub]->f14->f4;
    }
}

typedef struct {
    s8 owns_data : 1;
    s8 reserved : 2;
    s8 busy : 1;
    s8 rest : 4;
} Flags_001F08D0;

static inline s32 read_001F08D0(void *obj, s32 offset) {
    return *(s32 *)((u8 *)obj + offset);
}

static inline void clear_001F08D0(void *obj, s32 offset) {
    *(s32 *)((u32)obj + offset) = 0;
}

static inline s32 busy_001F08D0(void *obj) {
    return ((Flags_001F08D0 *)obj)[0x20C].busy;
}

static inline s32 owns_001F08D0(void *obj) {
    return ((Flags_001F08D0 *)((u32)obj + 0x20C))->owns_data;
}

#pragma global_optimizer off

s32 func_001F08D0(s32 arg0) {
    u8 *data;
    Obj_0031ABB0 *obj;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    obj = D_0031ABB0[arg0];
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
                        func_00217B50(resource);
                    }
                    resource = resources[2];
                    if (resource != 0) {
                        func_00217B50(resource);
                    }
                    k++;
                    resources += 4;
                } while (k < count);
            }
        }
        slot = 0;
        do {
            func_001F0C10(arg0, slot);
            slot++;
        } while (slot < 8);
        resource = read_001F08D0(obj, 0x140);
        if (resource != 0) {
            func_00217B50(resource);
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
                    func_00217B50(resource);
                    *(s32 *)(cursor + 0x144) = 0;
                }
                l++;
                cursor += 4;
            } while (l < 8);
        }
    }

    clear_001F08D0(obj, 0x164);
    clear_001F08D0(obj, 0x168);
    func_001FA810(0, 1);
    if (*(s32 *)((u8 *)read_001F08D0(obj, 0x138) + 4) & 0x80000) {
        clear_001F08D0(obj, 0x16C);
    } else if (read_001F08D0(obj, 0x16C) != 0) {
        func_00217B50(read_001F08D0(obj, 0x16C));
        clear_001F08D0(obj, 0x16C);
    }
    if (*(s32 *)((u8 *)read_001F08D0(obj, 0x138) + 4) & 0x100000) {
        clear_001F08D0(obj, 0x170);
    } else if (read_001F08D0(obj, 0x170) != 0) {
        func_00217B50(read_001F08D0(obj, 0x170));
        clear_001F08D0(obj, 0x170);
    }
    if (*(s32 *)((u8 *)read_001F08D0(obj, 0x138) + 4) & 0x200000) {
        clear_001F08D0(obj, 0x174);
    } else if (read_001F08D0(obj, 0x174) != 0) {
        func_00217B50(read_001F08D0(obj, 0x174));
        clear_001F08D0(obj, 0x174);
    }
    if (read_001F08D0(obj, 0x1EC) >= 0) {
        func_001F4CB0(read_001F08D0(obj, 0x1EC));
    }
    if (owns_001F08D0(obj)) {
        func_00217B50((s32)(u8 *)read_001F08D0(obj, 0x138));
    }
    {
        s32 n;
        Entry_001EDF20 *entry;

        n = 1;
        entry = D_0031AD70;
        clear_001F08D0(obj, 0x138);
        do {
            if (entry->id >= 0 && (arg0 < 0 || entry->id == arg0)) {
                entry->id = -1;
            }
            n++;
            entry++;
        } while (n < 0x20);
    }
    return 1;
}
#pragma global_optimizer reset

s32 func_001F0C10(s32 arg0, s32 arg1) {
    void func_00217B50(void *);
    Obj_0031ABB0 *obj;
    ObjSlot_0031ABB0 *slot;

    if ((arg0 < 0) || (arg0 >= 0x54)) {
        return 0;
    }
    if ((arg1 < 0) || (arg1 >= 8)) {
        return 0;
    }
    obj = D_0031ABB0[arg0];
    if (obj == NULL) {
        return 0;
    }
    slot = obj->slots[arg1];
    if (slot == NULL) {
        return 1;
    }
    func_00217B50(slot);
    obj->slots[arg1] = NULL;
    obj->vals[arg1] = 1;
    return 1;
}

s32 func_001F0CD0(s32 arg0, s32 arg1, s32 arg2) {
    Obj_0031ABB0 *obj;
    s32 s1;
    s32 s2;
    s32 index;
    s32 i;
    Obj_0031ABB0 *ptr;
    extern s32 func_001F4900();

    s1 = func_001E5240(arg0);
    s2 = func_001E5240(arg0 ^ 1);
    index = func_001E1360(s1 >> 8, s1 & 0xFF);
    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = D_0031ABB0[index];
    if (obj == NULL) {
        return 0;
    }
    func_001F1550(index, 2);
    func_00202D60(5, -1);
    func_001F56D0(s1, 1);
    func_001F56D0(s2, 1);
    i = 0;
    ptr = obj;
    do {
        func_00202810(5, i, NULL, *(s32 *)((u8 *)ptr + 0x144));
        i += 1;
        ptr = (Obj_0031ABB0 *)((u8 *)ptr + 4);
    } while (i < 8);
    *(s32 *)((u8 *)obj + 0x1EC) = func_001F4900(1, *(u16 *)((u8 *)obj + 0x206), *(u16 *)((u8 *)obj + 0x208), s2, s1, func_001ED460, index);
    if (arg1 != 0) {
        if (*(s32 *)((u8 *)obj + 0x16C) != 0) {
            func_001FA8A0(0, 1, ((arg2 != 0) ? 1 : 0) + 8, *(u16 *)((u8 *)obj + 0x202), index, (void *)*(s32 *)((u8 *)obj + 0x16C));
        }
    }
    return 1;
}

s32 func_001F0E50(s32 arg0, s32 arg1, s32 arg2) {
    s32 index;
    Obj_0031ABB0 *obj;
    void *data;

    index = func_001E5240(arg0);
    func_001E5240(arg0 ^ 1);
    index = func_001E1360(index >> 8, index & 0xFF);
    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = D_0031ABB0[index];
    if (obj == NULL) {
        return 0;
    }
    func_001F1550(index, 5);
    if (arg1 != 0) {
        data = *(void **)((u8 *)obj + 0x170);
        if (data != NULL) {
            func_001FA8A0(0, 1, (arg2 != 0 ? 1 : 0) + 8, 0, index, data);
        }
    }
    return 1;
}

f32 func_001F0F40(s32 arg0) {
    Obj_0031ABB0 *temp_v0;

    if (arg0 < 0 || arg0 >= 0x54) {
        return -1.0f;
    }
    temp_v0 = D_0031ABB0[arg0];
    if (temp_v0 == NULL) {
        return -1.0f;
    }
    return *(f32 *)((u8 *)temp_v0 + 0x1E4);
}

u8 *func_001F0FA0(s32 arg0) {
    Obj_0031ABB0 *temp_v0;

    if (arg0 < 0 || arg0 >= 0x54) {
        return NULL;
    }
    temp_v0 = D_0031ABB0[arg0];
    if (temp_v0 == NULL) {
        return NULL;
    }
    return &temp_v0->pad040[0x104];
}

s32 func_001F0FF0(s32 arg0) {
    Obj_0031ABB0 *obj;
    void *data;
    s32 ret;

    if (arg0 < 0 || arg0 >= 0x54) {
        ret = 0;
    } else {
        obj = D_0031ABB0[arg0];
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

s32 func_001F1070(s32 arg0) {
    Obj_0031ABB0 *temp_a1;
    s8 temp_v1;
    void *temp_a3;

    if ((arg0 < 0) || (arg0 >= 0x54)) {
        return 0;
    }
    temp_a1 = D_0031ABB0[arg0];
    if (temp_a1 == NULL) {
        return 0;
    }
    temp_a3 = *(void **)((u8 *)temp_a1 + 0x138);
    if (temp_a3 == NULL) {
        return 0;
    }
    temp_v1 = *(s8 *)((u8 *)temp_a1 + 0x1F3);
    if ((temp_v1 != 4) && (temp_v1 != 5) && (temp_v1 != 6)) {
        return 1;
    }
    *(s32 *)((u8 *)temp_a3 + 4) &= ~0x400;
    return (func_001F3910(1, *(s16 *)((u8 *)temp_a1 + 0x1F4), 0, temp_a3) != 0) ? 1 : 0;
}

s32 func_001F1130(s32 arg0) {
    Obj_0031ABB0 *obj;
    void *state;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    obj = D_0031ABB0[arg0];
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

s32 func_001F11B0(s32 arg0, s32 arg1) {
    s32 ret = 0;
    Obj_0031ABB0 *temp_a0;

    if ((arg0 < 0) || (arg0 >= 0x54)) {
        return 0;
    }
    temp_a0 = D_0031ABB0[arg0];
    if (temp_a0 == NULL) {
        return ret;
    }
    if (*(s32 *)((u8 *)temp_a0 + 0x138) == 0) {
        return ret;
    }
    switch (arg1) {
    case 19:
        ret = *(s32 *)((u8 *)temp_a0 + 0x16C);
        break;
    case 20:
        ret = *(s32 *)((u8 *)temp_a0 + 0x170);
        break;
    }
    return ret;
}

typedef struct {
    s8 : 2;
    s8 active : 1;
} Flags_001F1240;

s32 func_001F1240(s32 arg0) {
    Obj_0031ABB0 *obj;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    obj = D_0031ABB0[arg0];
    if (obj == NULL) {
        return 0;
    }
    return ((Flags_001F1240 *)((u8 *)obj + 0x20C))->active ? 1 : 0;
}

typedef struct {
    s8 : 3;
    s8 active : 1;
} Flags_001F12A0;

s32 func_001F12A0(s32 arg0) {
    Obj_0031ABB0 *temp_v0;
    s32 ret;

    if (arg0 < 0 || arg0 >= 0x54) {
        ret = 0;
    } else {
        temp_v0 = D_0031ABB0[arg0];
        if (temp_v0 == NULL) {
            ret = 0;
        } else {
            ret = ((Flags_001F12A0 *)((u8 *)temp_v0 + 0x20C))->active ? 1 : 0;
        }
    }
    return ret;
}

s32 func_001F1300(s32 arg0) {
    Obj_0031ABB0 *temp_v0;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }

    temp_v0 = D_0031ABB0[arg0];
    if (temp_v0 == NULL) {
        return 0;
    }
    if (*(s8 *)((u8 *)temp_v0 + 0x1F2) >= 0) {
        return 1;
    }
    return 0;
}

typedef struct {
    s8 unused : 1;
    s8 enabled : 1;
} Flags_001F1370;

s32 func_001F1370(s32 arg0) {
    Obj_0031ABB0 *obj;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    obj = D_0031ABB0[arg0];
    if (obj == NULL) {
        return 0;
    }
    if (*(s8 *)((u8 *)obj + 0x1F2) < 0) {
        return 0;
    }
    return ((Flags_001F1370 *)((u8 *)obj + 0x20C))->enabled ? 1 : 0;
}

s8 func_001F13F0(s32 arg0) {
    return func_001F1400(arg0, 0);
}

s8 func_001F1400(s32 arg0, s32 arg1) {
    Obj_0031ABB0 *base;

    if (arg0 < 0 || arg0 >= 0x54) {
        return -1;
    }
    if (arg1 < 0 || arg1 >= 4) {
        return -1;
    }
    base = D_0031ABB0[arg0];
    if (base == NULL) {
        return -1;
    }
    return base->lv[arg1];
}

s32 func_001F1480(s32 arg0, s32 arg1) {
    return func_001F1490(arg0, arg1, 3);
}

s32 func_001F1490(s32 arg0, s32 arg1, s32 arg2) {
    Obj_0031ABB0 *obj;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    if (arg2 < 0 || arg2 >= 4) {
        return 0;
    }
    if (arg1 < 0 || arg1 >= 8) {
        return 0;
    }

    obj = D_0031ABB0[arg0];
    if (obj == NULL) {
        return 0;
    }
    if (obj->slots[arg1] == NULL) {
        return 0;
    }

    obj->lv[arg2] = arg1;
    return 1;
}

s32 func_001F1550(s32 arg0, s32 arg1) {
    return func_001F1560(arg0, arg1, 6);
}

typedef struct {
    f32 x, y, z;
} Vec3_001F1560;

typedef struct {
    s8 unused : 6;
    s8 direction : 2;
} Flags_001F1560;

s32 func_001F1560(s32 arg0, s32 arg1, s32 arg2) {
    Obj_0031ABB0 *obj;
    Vec3_001F1560 *current;
    Vec3_001F1560 *previous;
    s8 *current_slot;
    s8 *previous_slot;
    f32 last_frame;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    if (arg1 < 0 || arg1 >= 8) {
        return 0;
    }
    obj = D_0031ABB0[arg0];
    if (obj == NULL) {
        return 0;
    }
    current = (Vec3_001F1560 *)&obj->slots[8];
    previous = (Vec3_001F1560 *)&obj->slots[11];
    current_slot = &obj->lv[0];
    previous_slot = &obj->lv[1];
    if (obj->slots[arg1] != NULL) {
        last_frame = (f32)(u32)obj->vals[arg1] - 1.0f;
        *previous = *current;
        *previous_slot = *current_slot;
        *current_slot = arg1;
        if ((s64)((Flags_001F1560 *)((u8 *)obj + 0x1F7))->direction == -1) {
            current->y = last_frame;
        } else {
            current->y = 1.0f;
        }
        current->z = 0.0f;
        previous->z = 1.0f - current->z;
        *(s8 *)((u8 *)obj + 0x1FB) = arg2;
        *(s8 *)((u8 *)obj + 0x1FD) = 0;
    } else {
        return 0;
    }
    return 1;
}

s32 func_001F16B0(s32 arg0) {
    return func_001F16C0(arg0, 6);
}

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F16C0);

typedef struct {
    u8 unused : 6;
    s8 mode : 2;
} Flags_001F1830;

s32 func_001F1830(s32 arg0, s32 arg1) {
    Obj_0031ABB0 *obj;
    f32 *state;
    s8 *next;
    s8 *selected;
    f32 value;
    f32 start;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    if (arg1 < 0 || arg1 >= 8) {
        return 0;
    }
    obj = D_0031ABB0[arg0];
    if (obj == NULL) {
        return 0;
    }
    state = (f32 *)&obj->slots[8];
    next = &obj->lv[1];
    selected = &obj->lv[0];
    if (obj->slots[arg1] != NULL) {
        value = (f32)(u32)obj->vals[arg1];
        start = value - 1.0f;
        *next = -1;
        *selected = arg1;
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

s32 func_001F1940(s32 arg0, s8 arg1) {
    Obj_0031ABB0 *obj;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    obj = D_0031ABB0[arg0];
    if (obj == NULL) {
        return 0;
    }
    *(s8 *)((u8 *)obj + 0x1FD) = arg1;
    return 1;
}

typedef struct {
    s8 unused : 6;
    s8 value : 2;
} Flags_001F19A0;

s64 func_001F19A0(s32 arg0) {
    Obj_0031ABB0 *obj;

    if (arg0 < 0 || arg0 >= 0x54) {
        return -1;
    }
    obj = D_0031ABB0[arg0];
    if (obj == NULL) {
        return -1;
    }
    return ((Flags_001F19A0 *)((u8 *)obj + 0x1F7))->value;
}

typedef struct {
    s8 low : 6;
    s8 mode : 2;
} Flags_001F1A00;

s32 func_001F1A00(s32 arg0, s64 arg1) {
    Obj_0031ABB0 *temp_a2;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    } else {
        temp_a2 = D_0031ABB0[arg0];
        if (temp_a2 == NULL) {
            return 0;
        }
        ((Flags_001F1A00 *)((u8 *)temp_a2 + 0x1F7))->mode = (s8)arg1;
        return 1;
    }
}

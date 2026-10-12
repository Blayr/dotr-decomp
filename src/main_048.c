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

INCLUDE_ASM("asm/nonmatchings/main_048", func_001EDA40);

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

INCLUDE_ASM("asm/nonmatchings/main_048", func_001EDFD0);

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

INCLUDE_ASM("asm/nonmatchings/main_048", func_001EE570);

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

INCLUDE_ASM("asm/nonmatchings/main_048", func_001EFF70);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F0060);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F01A0);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F0390);

typedef struct {
    u32 header[2];
    u8 data[0x7FF8];
} FixedBlock_001F0500;

void func_001E8BF0(s32);

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

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F0760);

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

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F08D0);

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

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F0CD0);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F0E50);

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

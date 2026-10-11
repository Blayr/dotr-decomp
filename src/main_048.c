#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_048", func_001ED460);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001ED4A0);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001EDA40);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001EDCB0);

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

INCLUDE_ASM("asm/nonmatchings/main_048", func_001EE4A0);

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

INCLUDE_ASM("asm/nonmatchings/main_048", func_001EFDC0);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001EFF70);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F0060);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F01A0);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F0390);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F0500);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F0760);

typedef struct {
    u8 pad00[0x14];
    ObjSlot_0031ABB0 *f14;
    u8 pad18[4];
    s32 f1C;
} Arg_001F0830;

void func_00214090(ObjSlot_0031ABB0 *);

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

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F0C10);

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

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F1370);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F13F0);

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

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F1480);

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

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F1550);

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

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F16B0);

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

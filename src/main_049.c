#include "common.h"

/* Sets model slot `index`'s animation speed (for its current animation parameter). */
s32 SzModel_SetAnimSpeed(s32 index, f32 value) {
    return SzModel_SetAnimSpeedParam(index, 0, value);
}

typedef struct View_001F1A90 {
    u8 pad[0x198];
    f32 m[4][3];
} View_001F1A90;

/* Sets the speed of animation parameter `which` of model slot `index`. */
s32 SzModel_SetAnimSpeedParam(s32 index, s32 which, f32 value) {
    Obj_0031ABB0 *obj;
    View_001F1A90 *view;
    s32 slot;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    if (which < 0 || which >= 4) {
        return 0;
    }
    obj = modelSlots[index];
    view = (View_001F1A90 *)obj;
    if (obj == NULL) {
        return 0;
    }
    slot = obj->lv[which];
    if (slot < 0) {
        return 0;
    }
    if (obj->slots[slot] == NULL) {
        return 0;
    }
    view->m[which][0] = value;
    return 1;
}

/* Model slot `index`'s current animation frame. */
f32 SzModel_GetAnimFrame(s32 index) {
    return SzModel_GetAnimFrameParam(index, 0);
}

typedef struct View_001F1B60 {
    u8 pad[0x19C];
    f32 m[4][3];
} View_001F1B60;

/* The current frame of animation parameter `which` of model slot `index`. */
f32 SzModel_GetAnimFrameParam(s32 index, s32 which) {
    Obj_0031ABB0 *obj;
    View_001F1B60 *view;
    s8 slot;

    if (index < 0 || index >= 0x54) {
        return -1.0f;
    }
    if (which < 0 || which >= 4) {
        return -1.0f;
    }
    obj = modelSlots[index];
    view = (View_001F1B60 *)obj;
    if (obj == NULL) {
        return -1.0f;
    }
    slot = obj->lv[which];
    if (slot < 0) {
        return -1.0f;
    }
    if (obj->slots[slot] == NULL) {
        return -1.0f;
    }
    return view->m[which][0];
}

/* Sets model slot `index`'s current animation frame. */
void SzModel_SetAnimFrame(s32 index, f32 value) {
    SzModel_SetAnimFrameParam(index, 0, value);
}

typedef struct View_001F1C50 {
    u8 pad[0x19C];
    f32 m[4][3];
} View_001F1C50;

/* Sets the current frame of animation parameter `which` of model slot `index`. */
s32 SzModel_SetAnimFrameParam(s32 index, s32 which, f32 value) {
    s32 slot;
    f32 maximum;
    Obj_0031ABB0 *obj;
    View_001F1C50 *view;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    view = (View_001F1C50 *)obj;
    if (obj == NULL) {
        return 0;
    }
    slot = obj->lv[which];
    if (slot < 0) {
        return 0;
    }
    if (obj->slots[slot] == NULL) {
        return 0;
    }
    maximum = (f32) (u32) obj->vals[slot] - 1.0f;
    if (value < 1.0f) {
        value = 1.0f;
    }
    if (!(value <= maximum)) {
        value = maximum;
    }
    view->m[which][0] = value;
    return 1;
}

/* How many frames animation `anim` of model slot `index` has (-1: the current one). */
s32 SzModel_GetAnimFrameMax(s32 index, s32 anim) {
    extern s32 SzModel_GetAnimParam();
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return -1;
    }
    if (anim < 0) {
        anim = SzModel_GetAnimParam(index, 0);
    }
    if (anim < 0 || anim >= 8) {
        return -1;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return -1;
    }
    if (obj->slots[anim] == NULL) {
        return -1;
    }
    return obj->vals[anim] - 1;
}

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Vec3_001F1E10;

/* Model slot `index`'s light intensity (four values) into `out`. */
s32 SzModel_GetIntensity(s32 index, f32 *out) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    *(Vec3_001F1E10 *)out = *(Vec3_001F1E10 *)((u8 *)obj + 0x120);
    return 1;
}

/* Model slot `index`'s overall intensity into `out`. */
s32 SzModel_GetIntensityOnly(s32 index, f32 *out) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    *out = *(f32 *)((u8 *)obj + 0x128);
    return 1;
}

typedef struct {
    f32 x, y, z;
} Vec3_001F1EE0;

/* Sets model slot `index`'s light intensity (four values). */
s32 SzModel_SetIntensity(s32 index, f32 *values) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    if (values != NULL) {
        *(Vec3_001F1EE0 *) ((u8 *) obj + 0x120) = *(Vec3_001F1EE0 *) values;
    } else {
        ((Vec3_001F1EE0 *) ((u8 *) obj + 0x120))->x = 0.8f;
        ((Vec3_001F1EE0 *) ((u8 *) obj + 0x120))->y = 0.8f;
        ((Vec3_001F1EE0 *) ((u8 *) obj + 0x120))->z = 1.0f;
    }
    return 1;
}

/* Sets model slot `index`'s overall intensity. */
s32 SzModel_SetIntensityOnly(s32 index, f32 fparg0) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    *(f32 *)((u8 *)obj + 0x128) = fparg0;
    return 1;
}

/* Model slot `index`'s position into `out`. */
s32 SzModel_GetPos(s32 index, void *out) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    if (out != NULL) {
        *(Vec4f *)out = *(Vec4f *)obj;
    }
    return 1;
}

typedef struct {
    s8 unused0 : 5;
    s8 ready : 1;
    s8 unused1 : 2;
} Flags_001F2050;

/* Whether model slot `index` has a model bound. */
static inline s32 check_001F2050(s32 index) {
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

/* Model slot `index`'s centre in the world into `out`. */
s32 SzModel_GetCenter(s32 index, void *out) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    if (check_001F2050(index) == 0) {
        return 0;
    }
    if ((s32)*(u8 *)((u8 *)obj + 0x1FE) <= 0) {
        return 0;
    }
    if (((Flags_001F2050 *)((u8 *)obj + 0x20C))->ready == 0) {
        return 0;
    }
    if (out != NULL) {
        *(Vec4f *)out = *(Vec4f *)((u8 *)obj + 0x80);
    }
    return 1;
}

/* Whether model slot `index` has a model bound. */
static inline s32 ready_001F2150(s32 index) {
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

/* Model slot `index`'s centre offset (from its centre node) into `out`. */
s32 SzModel_GetCenterOfs(s32 index, f32 *out) {
    s32 sp3C;
    Obj_0031ABB0 *obj;
    f32 temp_f1;
    s32 temp_a1;
    s32 temp_a1_2;
    s32 traceGNode;

    if ((index < 0) || (temp_a1 = index < 0x54, (temp_a1 == 0))) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    if (ready_001F2150(index) == 0) {
        return 0;
    }
    if ((s32)*(u8 *)((u8 *)obj + 0x1FE) <= 0) {
        return 0;
    }
    sp3C = 0;
    if ((index < 0) || (index >= 0x54)) {
        traceGNode = 0;
    } else if (obj == NULL) {
        traceGNode = 0;
    } else {
        temp_a1_2 = *(s32 *)((u8 *)obj + 0x134);
        traceGNode = lSzModel_TraceGNode(1, temp_a1_2, temp_a1_2, &sp3C, 0, NULL, 0);
    }
    if (traceGNode != 0) {
        temp_f1 = *(f32 *)(*(u8 **)((u8 *)obj + 0x13C) + 0x54);
        out[0] = *(f32 *)((u8 *)traceGNode + 0x20) / temp_f1;
        out[1] = *(f32 *)((u8 *)traceGNode + 0x24) / temp_f1;
        out[2] = *(f32 *)((u8 *)traceGNode + 0x28) / temp_f1;
        out[3] = 1.0f;
    }
    return 1;
}

/* Sets model slot `index`'s position. */
s32 SzModel_SetPos(s32 index, void *src) {
    Obj_0031ABB0 *dst;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    dst = modelSlots[index];
    if (dst == NULL) {
        return 0;
    }
    if (src != NULL) {
        *(Vec4f *)dst = *(Vec4f *)src;
    }
    return 1;
}

/* Model slot `index`'s rotation into `out`. */
s32 SzModel_GetRot(s32 index, void *out) {
    s32 result;
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        result = 0;
    } else {
        obj = modelSlots[index];
        if (obj == NULL) {
            result = 0;
        } else {
            if (out != NULL) {
                *(Vec4f *)out = *(Vec4f *)((u8 *)obj + 0x10);
            }
            result = 1;
        }
    }
    return result;
}

/* Model slot `index`'s rotation centre into `out`. */
s32 SzModel_GetRotC(s32 index, void *out) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    if (out != NULL) {
        *(Vec4f *)out = *(Vec4f *)((u8 *)obj + 0x20);
    }
    return 1;
}

typedef struct {
    f32 x, y, z, w;
} Vec4_001F2430;

/* needs shared field: modelSlots +0x10 f32[4] */

/* Sets model slot `index`'s rotation. */
s32 SzModel_SetRot(s32 index, void *src) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    if (src != NULL) {
        *(Vec4_001F2430 *)((u8 *)obj + 0x10) = *(Vec4_001F2430 *)src;
    } else {
        *(f32 *)((u8 *)obj + 0x10) = 0.0f;
        *(f32 *)((u8 *)obj + 0x14) = 0.0f;
        *(f32 *)((u8 *)obj + 0x18) = 0.0f;
        *(f32 *)((u8 *)obj + 0x1C) = 0.0f;
    }
    return 1;
}

/* Sets model slot `index`'s rotation centre. */
s32 SzModel_SetRotC(s32 index, void *src) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    if (src != NULL) {
        *(Vec4f *)((u8 *)obj + 0x20) = *(Vec4f *)src;
    } else {
        ((Vec4f *)((u8 *)obj + 0x20))->x = 0.0f;
        ((Vec4f *)((u8 *)obj + 0x20))->y = 0.0f;
        ((Vec4f *)((u8 *)obj + 0x20))->z = 0.0f;
        ((Vec4f *)((u8 *)obj + 0x20))->w = 0.0f;
    }
    return 1;
}

/* Model slot `index`'s scale into `out`. */
s32 SzModel_GetScale(s32 index, void *out) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    if (out != NULL) {
        *(Vec4f *)out = obj->v;
    }
    return 1;
}

/* Sets model slot `idx`'s scale. */
s32 SzModel_SetScale(s32 idx, void *src) {
    Obj_0031ABB0 *obj;

    if (idx < 0 || idx >= 0x54) {
        return 0;
    }
    obj = modelSlots[idx];
    if (obj == NULL) {
        return 0;
    }
    if (src != NULL) {
        obj->v = *(Vec4f *)src;
    } else {
        obj->v.x = 1.0f;
        obj->v.y = 1.0f;
        obj->v.z = 1.0f;
        obj->v.w = 1.0f;
    }
    return 1;
}

typedef struct {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} Color_001F2660;

/* Model slot `index`'s colour into `out`. */
s32 SzModel_GetRgba(s32 index, void *out) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return -1;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return -1;
    }
    if (out != NULL) {
        *(Color_001F2660 *)out = *(Color_001F2660 *)&obj->pad040[0xEC];
    }
    return *(u8 *)((u8 *)obj + 0x1F8) & 3;
}

typedef struct {
    u8 mode : 2;
    u8 reserved : 6;
} Flags_001F26E0;

typedef struct {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} Color_001F26E0;

/* Sets model slot `index`'s colour (`mode` says how it mixes). */
s32 SzModel_SetRgba(s32 index, s32 mixMode, void *rgba) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    if (mixMode >= 0 && mixMode < 4) {
        ((Flags_001F26E0 *)((u8 *)obj + 0x1F8))->mode = mixMode;
    }
    if (rgba != NULL) {
        *(Color_001F26E0 *)&obj->pad040[0xEC] = *(Color_001F26E0 *)rgba;
    } else {
        obj->pad040[0xEC] = obj->pad040[0xED] = obj->pad040[0xEE] = 0x80;
        obj->pad040[0xEF] = 0x80;
    }
    return 1;
}

/* Model slot `index`'s alpha. */
s32 SzModel_GetAlpha(s32 index) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return -1;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return -1;
    }
    return obj->pad040[0xEF];
}

/* Sets model slot `index`'s alpha. */
s32 SzModel_SetAlpha(s32 index, u8 value) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    obj->pad040[0xEF] = value;
    return 1;
}

typedef struct {
    u8 low : 2;
    u8 mode : 2;
    u8 high : 4;
} Flags_001F2860;

typedef struct {
    u8 r, g, b, a;
} Color_001F2860;

/* Sets model slot `index`'s colour filter (`mode` and its colour). */
s32 SzModel_SetFilter(s32 index, s32 filterMode, void *color) {
    Obj_0031ABB0 *obj;

    if ((index < 0) || (index >= 0x54)) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    if ((filterMode >= 0) && (filterMode < 4)) {
        ((Flags_001F2860 *)((u8 *)obj + 0x1F8))->mode = filterMode;
    }
    if (color != NULL) {
        *(Color_001F2860 *)&obj->pad040[0xF0] = *(Color_001F2860 *)color;
    } else {
        obj->pad040[0xF0] = obj->pad040[0xF1] = obj->pad040[0xF2] = 0;
        obj->pad040[0xF3] = 0;
    }
    return 1;
}

/* The model number loaded in slot `index`. */
s16 SzModel_GetModelNo(s32 index) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return -1;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return -1;
    }
    return *(s16 *)((u8 *)obj + 0x1F4);
}

/* The kind of model loaded in slot `index`. */
s8 SzModel_GetModelType(s32 index) {
    Obj_0031ABB0 *obj;
    s8 ret;

    if (index < 0 || index >= 0x54) {
        ret = -1;
    } else {
        obj = modelSlots[index];
        if (obj == NULL) {
            ret = -1;
        } else {
            ret = *(s8 *)((u8 *)obj + 0x1F3);
        }
    }
    return ret;
}

typedef struct {
    u8 pad000[0x20C];
    s8 unused0 : 4;
    s8 enabled : 1;
    s8 unused1 : 3;
} ObjView_001F29E0;

/* Sets model slot `index`'s deform effect. */
s32 SzModel_SetDeform(s32 index, s32 value) {
    ObjView_001F29E0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = (ObjView_001F29E0 *) modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    if (obj->enabled != value) {
        obj->enabled = (s8) value;
    }
    return 1;
}

typedef struct {
    s8 : 4;
    s8 active : 1;
    s8 : 3;
} Flags_001F2A70;

/* Model slot `index`'s deform effect. */
s32 SzModel_GetDeform(s32 index) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    return ((Flags_001F2A70 *) ((u8 *) obj + 0x20C))->active ? 1 : 0;
}

/* Sets how strong model slot `index`'s deform effect is. */
s32 SzModel_SetDeformRatio(s32 index, s8 value) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }

    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }

    *(s8 *)((u8 *)obj + 0x1FF) = value;
    return 1;
}

/* Whether model slot `index` has a model bound. */
static inline s32 check_001F2B30(s32 index) {
    if (index < 0 || index >= 0x54) {
        return 0;
    }
    if (modelSlots[index] == NULL) {
        return 0;
    }
    if (*(s8 *)((u8 *)modelSlots[index] + 0x1F2) >= 0) {
        return 1;
    }
    return 0;
}

/* How many references model slot `index` has. */
s32 SzModel_GetRefNum(s32 index) {
    if (index < 0 || index >= 0x54) {
        return -1;
    }
    if (modelSlots[index] == NULL) {
        return -1;
    }
    if (check_001F2B30(index)) {
        return *(u8 *)((u8 *)modelSlots[index] + 0x1FE);
    }
    return -1;
}

/* Whether model slot `index` holds reference `id`. */
s32 SzModel_InqRefID(s32 index, s32 id) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return -1;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return -1;
    }
    if (id < 0 || id >= 8) {
        return -1;
    }
    return *(u16 *)((id << 1) + (s32)obj + 0x1B0);
}

typedef struct View_001F2C60 {
    u8 pad0[0x1B0];
    u16 slots[8];
    u8 pad1C0[0x39];
    u8 count;
    u8 pad1FA[4];
    u8 max;
} View_001F2C60;

/* Sets reference `ref` of model slot `index` to `id`. */
s32 SzModel_SetRefID(s32 index, s32 ref, s32 id) {
    View_001F2C60 *obj;
    s32 i;
    s32 group;
    s32 newGroup;
    u16 current;

    if (index < 0 || index >= 0x54) {
        return -1;
    }
    obj = (View_001F2C60 *) modelSlots[index];
    if (obj == NULL) {
        return -1;
    }
    if (id != 0) {
        if (ref >= 0) {
            group = (ref & 0x7F00) >> 8;
            for (i = 0; i < 8; i++) {
                if (((obj->slots[i] & 0x7F00) >> 8) == group) {
                    obj->slots[i] = 0x7FFF;
                }
            }
        } else {
            for (i = 0; i < 8; i++) {
                obj->slots[i] = 0x7FFF;
            }
        }
        obj->count = 0;
    }
    if (obj->count >= 8) {
        return -1;
    }
    if (ref >= 0) {
        newGroup = (ref & 0x7F00) >> 8;
        if ((ref & 0xFF) >= obj->max) {
            return -1;
        }
        current = obj->slots[obj->count];
        if ((current & 0x7FFF) < 0x7FFF && ((current & 0x7F00) >> 8) != newGroup) {
            return -1;
        }
    }
    obj->slots[obj->count] = (ref < 0) ? 0x7FFF : ref;
    return obj->count++;
}

/* Sets the reference numbered `refNo` of model slot `index` to `id`. */
s32 SzModel_SetRefID_RefNo(s32 index, s32 refNo, s32 id) {
    Obj_0031ABB0 *obj;
    s32 group;
    u16 current;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    if (id < 0 || id >= 8) {
        return 0;
    }
    if (refNo >= 0) {
        group = (refNo & 0x7F00) >> 8;
        if ((refNo & 0xFF) >= *(u8 *)((u8 *)obj + 0x1FE)) {
            return 0;
        }
        current = *(u16 *)((id << 1) + (s32)obj + 0x1B0);
        if ((current & 0x7FFF) < 0x7FFF && ((current & 0x7F00) >> 8) != group) {
            return 0;
        }
    }
    *(u16 *)((id << 1) + (s32)obj + 0x1B0) = (refNo < 0) ? 0x7FFF : refNo;
    return 1;
}

typedef struct {
    s8 unused : 5;
    s8 available : 1;
    s8 remaining : 2;
} Flags_001F2EC0;

typedef struct {
    f32 x, y, z, w;
} Vec4_001F2EC0;

/* Whether model slot `index` has a model bound. */
static inline s32 active_001F2EC0(s32 index) {
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

/* Reference `ref` of model slot `index` (`which` picks the word). */
s32 SzModel_GetRef(s32 index, s32 ref, s32 which) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    if (!active_001F2EC0(index)) {
        return 0;
    }
    if (!((Flags_001F2EC0 *)((u8 *)obj + 0x20C))->available) {
        return 0;
    }
    if (ref < 0 || ref >= 8) {
        return 0;
    }
    if (!(*(u16 *)((ref << 1) + (s32)obj + 0x1B0) & 0x8000)) {
        return 0;
    }
    *(Vec4_001F2EC0 *)which = *(Vec4_001F2EC0 *)((ref << 4) + (s32)obj + 0xA0);
    return 1;
}

/* Sets model slot `index`'s deepest draw-order level. */
s32 SzModel_SetMaxOT(s32 index, s16 value) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    *(s16 *)((u8 *)obj + 0x20A) = value;
    return 1;
}

/* Model slot `index`'s deepest draw-order level. */
s32 SzModel_GetMaxOT(s32 index) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return -1;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return -1;
    }
    return *(u16 *)((u8 *)obj + 0x20A);
}

typedef struct {
    s8 reserved : 1;
    s8 enabled : 1;
} Flags_001F30B0;

/* Shows or hides model slot `index`. */
s32 SzModel_SetDrawFlag(s32 index, s32 on) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }

    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }

    ((Flags_001F30B0 *)((u8 *)obj + 0x20C))->enabled = (s8)on;
    return 1;
}

typedef struct {
    s8 unused : 1;
    s8 enabled : 1;
} Flags_001F3130;

/* Whether model slot `index` is shown. */
s32 SzModel_GetDrawFlag(s32 index) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    return ((Flags_001F3130 *)((u8 *)obj + 0x20C))->enabled ? 1 : 0;
}

typedef struct {
    s8 low : 6;
    s8 flag : 1;
    s8 high : 1;
} Flags_001F3190;

/* Turns model slot `index`'s matrix calculation on or off. */
s32 SzModel_SetCalcFlag(s32 index, s32 on) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    ((Flags_001F3190 *)((u8 *)obj + 0x20C))->flag = on;
    return 1;
}

typedef struct {
    s8 : 6;
    s8 active : 1;
    s8 : 1;
} Flags_001F3210;

/* Whether model slot `index`'s matrices are calculated when it draws. */
s32 SzModel_GetCalcFlag(s32 index) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    return ((Flags_001F3210 *)((u8 *)obj + 0x20C))->active ? 1 : 0;
}

typedef struct {
    s8 : 7;
    s8 enabled : 1;
} Flags_001F3270;

/* Turns fog on or off for model slot `index`. */
s32 SzModel_SetFogFlag(s32 index, s64 on) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    ((Flags_001F3270 *)((u8 *)obj + 0x20C))->enabled = (s8)on;
    return 1;
}

typedef struct {
    s8 enabled : 1;
} Flags_001F32F0;

/* Pauses or resumes model slot `index`'s animation. */
s32 SzModel_SetPauseFlag(s32 index, s64 on) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    ((Flags_001F32F0 *)((u8 *)obj + 0x20D))->enabled = on;
    return 1;
}

typedef struct {
    s8 active : 1;
} Flags_001F3360;

/* Whether model slot `index`'s animation is paused. */
s32 SzModel_GetPauseFlag(s32 index) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    return ((Flags_001F3360 *)((u8 *)obj + 0x20D))->active ? 1 : 0;
}

typedef struct {
    s8 : 1;
    s8 enabled : 1;
} Flags_001F33C0;

/* Turns model slot `index` to stone or back. */
s32 SzModel_SetStoneFlag(s32 index, s64 on) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    ((Flags_001F33C0 *)((u8 *)obj + 0x20D))->enabled = (s8)on;
    return 1;
}

typedef struct {
    s8 bit0 : 1;
    s8 enabled : 1;
} Flags_001F3440;

/* Whether model slot `index` is stone. */
s32 SzModel_GetStoneFlag(s32 index) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    return ((Flags_001F3440 *)((u8 *)obj + 0x20D))->enabled ? 1 : 0;
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
struct DotrObjectShadeHeader {
    unsigned char unknown_00[0x1c];
    int unknown_1c;
    unsigned char unknown_20[8];
    int unknown_28;
    int unknown_2c;
};
struct DotrObjectShadeNode {
    unsigned char unknown_00[0x10];
    struct DotrObjectShadeInfo {
        int unknown_00;
        int unknown_04;
        int unknown_08;
        int unknown_0c;
    } unknown_10;
};
struct DotrObjectShadeSlot {
    struct DotrObjectShadeNode *node;
    int unknown_04[3];
};
extern int func_00241A00_b(float scale, unsigned short color, int e);

/* Sets how far model slot `index` has turned to stone. */
int SzModel_SetStoneRatio(int index, int value)
{
    struct DotrObject *p;
    struct DotrObjectLink *base;
    struct DotrObjectShadeHeader *header;
    int count;
    int i;
    unsigned short *words;
    int left;
    struct DotrObjectShadeSlot *slot;
    int level;
    struct DotrObjectShadeNode *node;
    int *list;
    struct DotrObjectShadeInfo *info;

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
    base = p->unknown_138;
    if (base == 0) {
        return 0;
    }
    if (p->unknown_20c.unknown_bit_3) {
        return 0;
    }
    if (base == 0) {
        return 0;
    }
    header = *(struct DotrObjectShadeHeader **)p->unknown_13c;
    if (header == 0) {
        return 0;
    }
    if (header->unknown_2c == 0) {
        return 0;
    }
    if (!p->unknown_20d.unknown_bit_1) {
        return 0;
    }
    level = value & 0xff;
    if (level < p->unknown_200) {
        return 0;
    }
    list = (int *)((char *)base + header->unknown_28);
    count = *list;
    slot = (struct DotrObjectShadeSlot *)(list + 4);
    for (i = 0; i < count; i++, slot++) {
        node = slot->node;
        if (node != 0 && (info = &node->unknown_10, node->unknown_10.unknown_0c != 0)) {
            words = (unsigned short *)((char *)node + info->unknown_08 + 96) + p->unknown_200;
            left = level - p->unknown_200 + 1;
            while (left-- != 0) {
                *words = func_00241A00_b(1.0f, *words, 6);
                words++;
            }
        }
    }
    p->unknown_200 = value;
    return 1;
}

typedef struct {
    s8 unused : 1;
    s8 active : 1;
} Flags_001F3690;

/* How far model slot `index` has turned to stone. */
s32 SzModel_GetStoneRatio(s32 index) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return -1;
    }
    obj = modelSlots[index];
    if (obj == NULL) {
        return -1;
    }
    if (((Flags_001F3690 *)((u8 *)obj + 0x20D))->active != 0) {
        return *(u8 *)((u8 *)obj + 0x200);
    }
    return -1;
}

typedef struct Table_001F3700 {
    s32 *values;
    s32 unused;
    s32 count;
} Table_001F3700;

extern Table_001F3700 effectKindTable[3]; /* original: gSzEffect_aEffFuncTbl */
extern s8 effectState; /* original: gSzEffect_el */

/* Clears the effect slots and sets the default black-out, fog and light values for duels, battles and monsters. */
void SzEffect_Init(void) {
    s32 i;
    s32 *values;
    s32 *count;
    Table_001F3700 *table;

    table = effectKindTable;
    i = 0;
    do {
        values = table->values;
        count = &table->count;
        table->count = 0;
        while (*values++ != 0) {
            (*count)++;
        }
        i++;
        table++;
    } while (i < 3);
    RhMem_FillMemory(&effectState, 0, 0x354);
    SzEffect_Clear();
    SzEffect_SetBlackOutForMonster(0x80);
    SzEffect_SetBlackOutForDuel(0x80);
    SzEffect_SetBlackOutForBattle(0x80);
}

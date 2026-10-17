#include "common.h"

s32 SzModel_SetAnimSpeed(s32 arg0, f32 value) {
    return SzModel_SetAnimSpeedParam(arg0, 0, value);
}

typedef struct View_001F1A90 {
    u8 pad[0x198];
    f32 m[4][3];
} View_001F1A90;

s32 SzModel_SetAnimSpeedParam(s32 arg0, s32 arg1, f32 value) {
    Obj_0031ABB0 *obj;
    View_001F1A90 *view;
    s32 slot;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    if (arg1 < 0 || arg1 >= 4) {
        return 0;
    }
    obj = gSzModel_ahModel[arg0];
    view = (View_001F1A90 *)obj;
    if (obj == NULL) {
        return 0;
    }
    slot = obj->lv[arg1];
    if (slot < 0) {
        return 0;
    }
    if (obj->slots[slot] == NULL) {
        return 0;
    }
    view->m[arg1][0] = value;
    return 1;
}

f32 SzModel_GetAnimFrame(s32 arg0) {
    return SzModel_GetAnimFrameParam(arg0, 0);
}

typedef struct View_001F1B60 {
    u8 pad[0x19C];
    f32 m[4][3];
} View_001F1B60;

f32 SzModel_GetAnimFrameParam(s32 arg0, s32 arg1) {
    Obj_0031ABB0 *obj;
    View_001F1B60 *view;
    s8 slot;

    if (arg0 < 0 || arg0 >= 0x54) {
        return -1.0f;
    }
    if (arg1 < 0 || arg1 >= 4) {
        return -1.0f;
    }
    obj = gSzModel_ahModel[arg0];
    view = (View_001F1B60 *)obj;
    if (obj == NULL) {
        return -1.0f;
    }
    slot = obj->lv[arg1];
    if (slot < 0) {
        return -1.0f;
    }
    if (obj->slots[slot] == NULL) {
        return -1.0f;
    }
    return view->m[arg1][0];
}

void SzModel_SetAnimFrame(s32 arg0, f32 value) {
    SzModel_SetAnimFrameParam(arg0, 0, value);
}

typedef struct View_001F1C50 {
    u8 pad[0x19C];
    f32 m[4][3];
} View_001F1C50;

s32 SzModel_SetAnimFrameParam(s32 arg0, s32 arg1, f32 value) {
    s32 slot;
    f32 maximum;
    Obj_0031ABB0 *obj;
    View_001F1C50 *view;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    obj = gSzModel_ahModel[arg0];
    view = (View_001F1C50 *)obj;
    if (obj == NULL) {
        return 0;
    }
    slot = obj->lv[arg1];
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
    view->m[arg1][0] = value;
    return 1;
}

s32 SzModel_GetAnimFrameMax(s32 arg0, s32 arg1) {
    extern s32 SzModel_GetAnimParam();
    Obj_0031ABB0 *temp_v0;

    if (arg0 < 0 || arg0 >= 0x54) {
        return -1;
    }
    if (arg1 < 0) {
        arg1 = SzModel_GetAnimParam(arg0, 0);
    }
    if (arg1 < 0 || arg1 >= 8) {
        return -1;
    }
    temp_v0 = gSzModel_ahModel[arg0];
    if (temp_v0 == NULL) {
        return -1;
    }
    if (temp_v0->slots[arg1] == NULL) {
        return -1;
    }
    return temp_v0->vals[arg1] - 1;
}

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Vec3_001F1E10;

s32 SzModel_GetIntensity(s32 arg0, f32 *arg1) {
    Obj_0031ABB0 *obj;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    obj = gSzModel_ahModel[arg0];
    if (obj == NULL) {
        return 0;
    }
    *(Vec3_001F1E10 *)arg1 = *(Vec3_001F1E10 *)((u8 *)obj + 0x120);
    return 1;
}

s32 SzModel_GetIntensityOnly(s32 arg0, f32 *arg1) {
    Obj_0031ABB0 *temp_v0;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    temp_v0 = gSzModel_ahModel[arg0];
    if (temp_v0 == NULL) {
        return 0;
    }
    *arg1 = *(f32 *)((u8 *)temp_v0 + 0x128);
    return 1;
}

typedef struct {
    f32 x, y, z;
} Vec3_001F1EE0;

s32 SzModel_SetIntensity(s32 arg0, f32 *arg1) {
    Obj_0031ABB0 *obj;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    obj = gSzModel_ahModel[arg0];
    if (obj == NULL) {
        return 0;
    }
    if (arg1 != NULL) {
        *(Vec3_001F1EE0 *) ((u8 *) obj + 0x120) = *(Vec3_001F1EE0 *) arg1;
    } else {
        ((Vec3_001F1EE0 *) ((u8 *) obj + 0x120))->x = 0.8f;
        ((Vec3_001F1EE0 *) ((u8 *) obj + 0x120))->y = 0.8f;
        ((Vec3_001F1EE0 *) ((u8 *) obj + 0x120))->z = 1.0f;
    }
    return 1;
}

s32 SzModel_SetIntensityOnly(s32 arg0, f32 fparg0) {
    Obj_0031ABB0 *temp_v0;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    temp_v0 = gSzModel_ahModel[arg0];
    if (temp_v0 == NULL) {
        return 0;
    }
    *(f32 *)((u8 *)temp_v0 + 0x128) = fparg0;
    return 1;
}

s32 SzModel_GetPos(s32 arg0, void *arg1) {
    Obj_0031ABB0 *temp_v0;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    temp_v0 = gSzModel_ahModel[arg0];
    if (temp_v0 == NULL) {
        return 0;
    }
    if (arg1 != NULL) {
        *(Vec4f *)arg1 = *(Vec4f *)temp_v0;
    }
    return 1;
}

typedef struct {
    s8 unused0 : 5;
    s8 ready : 1;
    s8 unused1 : 2;
} Flags_001F2050;

static inline s32 check_001F2050(s32 index) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = gSzModel_ahModel[index];
    if (obj == NULL) {
        return 0;
    }
    if (*(s8 *)((u8 *)obj + 0x1F2) >= 0) {
        return 1;
    }
    return 0;
}

s32 SzModel_GetCenter(s32 index, void *out) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = gSzModel_ahModel[index];
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

static inline s32 ready_001F2150(s32 index) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = gSzModel_ahModel[index];
    if (obj == NULL) {
        return 0;
    }
    if (*(s8 *)((u8 *)obj + 0x1F2) >= 0) {
        return 1;
    }
    return 0;
}

s32 SzModel_GetCenterOfs(s32 arg0, f32 *arg1) {
    s32 sp3C;
    Obj_0031ABB0 *temp_s1;
    f32 temp_f1;
    s32 temp_a1;
    s32 temp_a1_2;
    s32 var_v0_2;

    if ((arg0 < 0) || (temp_a1 = arg0 < 0x54, (temp_a1 == 0))) {
        return 0;
    }
    temp_s1 = gSzModel_ahModel[arg0];
    if (temp_s1 == NULL) {
        return 0;
    }
    if (ready_001F2150(arg0) == 0) {
        return 0;
    }
    if ((s32)*(u8 *)((u8 *)temp_s1 + 0x1FE) <= 0) {
        return 0;
    }
    sp3C = 0;
    if ((arg0 < 0) || (arg0 >= 0x54)) {
        var_v0_2 = 0;
    } else if (temp_s1 == NULL) {
        var_v0_2 = 0;
    } else {
        temp_a1_2 = *(s32 *)((u8 *)temp_s1 + 0x134);
        var_v0_2 = lSzModel_TraceGNode(1, temp_a1_2, temp_a1_2, &sp3C, 0, NULL, 0);
    }
    if (var_v0_2 != 0) {
        temp_f1 = *(f32 *)(*(u8 **)((u8 *)temp_s1 + 0x13C) + 0x54);
        arg1[0] = *(f32 *)((u8 *)var_v0_2 + 0x20) / temp_f1;
        arg1[1] = *(f32 *)((u8 *)var_v0_2 + 0x24) / temp_f1;
        arg1[2] = *(f32 *)((u8 *)var_v0_2 + 0x28) / temp_f1;
        arg1[3] = 1.0f;
    }
    return 1;
}

s32 SzModel_SetPos(s32 index, void *src) {
    Obj_0031ABB0 *dst;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    dst = gSzModel_ahModel[index];
    if (dst == NULL) {
        return 0;
    }
    if (src != NULL) {
        *(Vec4f *)dst = *(Vec4f *)src;
    }
    return 1;
}

s32 SzModel_GetRot(s32 arg0, void *arg1) {
    s32 result;
    Obj_0031ABB0 *temp_v0;

    if (arg0 < 0 || arg0 >= 0x54) {
        result = 0;
    } else {
        temp_v0 = gSzModel_ahModel[arg0];
        if (temp_v0 == NULL) {
            result = 0;
        } else {
            if (arg1 != NULL) {
                *(Vec4f *)arg1 = *(Vec4f *)((u8 *)temp_v0 + 0x10);
            }
            result = 1;
        }
    }
    return result;
}

s32 SzModel_GetRotC(s32 arg0, void *arg1) {
    Obj_0031ABB0 *temp_v0;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    temp_v0 = gSzModel_ahModel[arg0];
    if (temp_v0 == NULL) {
        return 0;
    }
    if (arg1 != NULL) {
        *(Vec4f *)arg1 = *(Vec4f *)((u8 *)temp_v0 + 0x20);
    }
    return 1;
}

typedef struct {
    f32 x, y, z, w;
} Vec4_001F2430;

/* needs shared field: gSzModel_ahModel +0x10 f32[4] */

s32 SzModel_SetRot(s32 arg0, void *arg1) {
    Obj_0031ABB0 *obj;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    obj = gSzModel_ahModel[arg0];
    if (obj == NULL) {
        return 0;
    }
    if (arg1 != NULL) {
        *(Vec4_001F2430 *)((u8 *)obj + 0x10) = *(Vec4_001F2430 *)arg1;
    } else {
        *(f32 *)((u8 *)obj + 0x10) = 0.0f;
        *(f32 *)((u8 *)obj + 0x14) = 0.0f;
        *(f32 *)((u8 *)obj + 0x18) = 0.0f;
        *(f32 *)((u8 *)obj + 0x1C) = 0.0f;
    }
    return 1;
}

s32 SzModel_SetRotC(s32 index, void *src) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = gSzModel_ahModel[index];
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

s32 SzModel_GetScale(s32 arg0, void *arg1) {
    Obj_0031ABB0 *temp_v0;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    temp_v0 = gSzModel_ahModel[arg0];
    if (temp_v0 == NULL) {
        return 0;
    }
    if (arg1 != NULL) {
        *(Vec4f *)arg1 = temp_v0->v;
    }
    return 1;
}

s32 SzModel_SetScale(s32 idx, void *src) {
    Obj_0031ABB0 *obj;

    if (idx < 0 || idx >= 0x54) {
        return 0;
    }
    obj = gSzModel_ahModel[idx];
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

s32 SzModel_GetRgba(s32 arg0, void *arg1) {
    Obj_0031ABB0 *obj;

    if (arg0 < 0 || arg0 >= 0x54) {
        return -1;
    }
    obj = gSzModel_ahModel[arg0];
    if (obj == NULL) {
        return -1;
    }
    if (arg1 != NULL) {
        *(Color_001F2660 *)arg1 = *(Color_001F2660 *)&obj->pad040[0xEC];
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

s32 SzModel_SetRgba(s32 arg0, s32 arg1, void *arg2) {
    Obj_0031ABB0 *obj;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    obj = gSzModel_ahModel[arg0];
    if (obj == NULL) {
        return 0;
    }
    if (arg1 >= 0 && arg1 < 4) {
        ((Flags_001F26E0 *)((u8 *)obj + 0x1F8))->mode = arg1;
    }
    if (arg2 != NULL) {
        *(Color_001F26E0 *)&obj->pad040[0xEC] = *(Color_001F26E0 *)arg2;
    } else {
        obj->pad040[0xEC] = obj->pad040[0xED] = obj->pad040[0xEE] = 0x80;
        obj->pad040[0xEF] = 0x80;
    }
    return 1;
}

s32 SzModel_GetAlpha(s32 arg0) {
    Obj_0031ABB0 *temp_v0;

    if (arg0 < 0 || arg0 >= 0x54) {
        return -1;
    }
    temp_v0 = gSzModel_ahModel[arg0];
    if (temp_v0 == NULL) {
        return -1;
    }
    return temp_v0->pad040[0xEF];
}

s32 SzModel_SetAlpha(s32 arg0, u8 arg1) {
    Obj_0031ABB0 *temp_v0;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    temp_v0 = gSzModel_ahModel[arg0];
    if (temp_v0 == NULL) {
        return 0;
    }
    temp_v0->pad040[0xEF] = arg1;
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

s32 SzModel_SetFilter(s32 arg0, s32 arg1, void *arg2) {
    Obj_0031ABB0 *temp_a3;

    if ((arg0 < 0) || (arg0 >= 0x54)) {
        return 0;
    }
    temp_a3 = gSzModel_ahModel[arg0];
    if (temp_a3 == NULL) {
        return 0;
    }
    if ((arg1 >= 0) && (arg1 < 4)) {
        ((Flags_001F2860 *)((u8 *)temp_a3 + 0x1F8))->mode = arg1;
    }
    if (arg2 != NULL) {
        *(Color_001F2860 *)&temp_a3->pad040[0xF0] = *(Color_001F2860 *)arg2;
    } else {
        temp_a3->pad040[0xF0] = temp_a3->pad040[0xF1] = temp_a3->pad040[0xF2] = 0;
        temp_a3->pad040[0xF3] = 0;
    }
    return 1;
}

s16 SzModel_GetModelNo(s32 arg0) {
    Obj_0031ABB0 *temp_v0;

    if (arg0 < 0 || arg0 >= 0x54) {
        return -1;
    }
    temp_v0 = gSzModel_ahModel[arg0];
    if (temp_v0 == NULL) {
        return -1;
    }
    return *(s16 *)((u8 *)temp_v0 + 0x1F4);
}

s8 SzModel_GetModelType(s32 arg0) {
    Obj_0031ABB0 *obj;
    s8 ret;

    if (arg0 < 0 || arg0 >= 0x54) {
        ret = -1;
    } else {
        obj = gSzModel_ahModel[arg0];
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

s32 SzModel_SetDeform(s32 arg0, s32 arg1) {
    ObjView_001F29E0 *obj;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    obj = (ObjView_001F29E0 *) gSzModel_ahModel[arg0];
    if (obj == NULL) {
        return 0;
    }
    if (obj->enabled != arg1) {
        obj->enabled = (s8) arg1;
    }
    return 1;
}

typedef struct {
    s8 : 4;
    s8 active : 1;
    s8 : 3;
} Flags_001F2A70;

s32 SzModel_GetDeform(s32 arg0) {
    Obj_0031ABB0 *temp_v0;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    temp_v0 = gSzModel_ahModel[arg0];
    if (temp_v0 == NULL) {
        return 0;
    }
    return ((Flags_001F2A70 *) ((u8 *) temp_v0 + 0x20C))->active ? 1 : 0;
}

s32 SzModel_SetDeformRatio(s32 arg0, s8 arg1) {
    Obj_0031ABB0 *obj;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }

    obj = gSzModel_ahModel[arg0];
    if (obj == NULL) {
        return 0;
    }

    *(s8 *)((u8 *)obj + 0x1FF) = arg1;
    return 1;
}

static inline s32 check_001F2B30(s32 index) {
    if (index < 0 || index >= 0x54) {
        return 0;
    }
    if (gSzModel_ahModel[index] == NULL) {
        return 0;
    }
    if (*(s8 *)((u8 *)gSzModel_ahModel[index] + 0x1F2) >= 0) {
        return 1;
    }
    return 0;
}

s32 SzModel_GetRefNum(s32 index) {
    if (index < 0 || index >= 0x54) {
        return -1;
    }
    if (gSzModel_ahModel[index] == NULL) {
        return -1;
    }
    if (check_001F2B30(index)) {
        return *(u8 *)((u8 *)gSzModel_ahModel[index] + 0x1FE);
    }
    return -1;
}

s32 SzModel_InqRefID(s32 arg0, s32 arg1) {
    Obj_0031ABB0 *obj;

    if (arg0 < 0 || arg0 >= 0x54) {
        return -1;
    }
    obj = gSzModel_ahModel[arg0];
    if (obj == NULL) {
        return -1;
    }
    if (arg1 < 0 || arg1 >= 8) {
        return -1;
    }
    return *(u16 *)((arg1 << 1) + (s32)obj + 0x1B0);
}

typedef struct View_001F2C60 {
    u8 pad0[0x1B0];
    u16 slots[8];
    u8 pad1C0[0x39];
    u8 count;
    u8 pad1FA[4];
    u8 max;
} View_001F2C60;

s32 SzModel_SetRefID(s32 arg0, s32 arg1, s32 arg2) {
    View_001F2C60 *obj;
    s32 i;
    s32 group;
    s32 newGroup;
    u16 current;

    if (arg0 < 0 || arg0 >= 0x54) {
        return -1;
    }
    obj = (View_001F2C60 *) gSzModel_ahModel[arg0];
    if (obj == NULL) {
        return -1;
    }
    if (arg2 != 0) {
        if (arg1 >= 0) {
            group = (arg1 & 0x7F00) >> 8;
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
    if (arg1 >= 0) {
        newGroup = (arg1 & 0x7F00) >> 8;
        if ((arg1 & 0xFF) >= obj->max) {
            return -1;
        }
        current = obj->slots[obj->count];
        if ((current & 0x7FFF) < 0x7FFF && ((current & 0x7F00) >> 8) != newGroup) {
            return -1;
        }
    }
    obj->slots[obj->count] = (arg1 < 0) ? 0x7FFF : arg1;
    return obj->count++;
}

s32 SzModel_SetRefID_RefNo(s32 arg0, s32 arg1, s32 arg2) {
    Obj_0031ABB0 *obj;
    s32 group;
    u16 current;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    obj = gSzModel_ahModel[arg0];
    if (obj == NULL) {
        return 0;
    }
    if (arg2 < 0 || arg2 >= 8) {
        return 0;
    }
    if (arg1 >= 0) {
        group = (arg1 & 0x7F00) >> 8;
        if ((arg1 & 0xFF) >= *(u8 *)((u8 *)obj + 0x1FE)) {
            return 0;
        }
        current = *(u16 *)((arg2 << 1) + (s32)obj + 0x1B0);
        if ((current & 0x7FFF) < 0x7FFF && ((current & 0x7F00) >> 8) != group) {
            return 0;
        }
    }
    *(u16 *)((arg2 << 1) + (s32)obj + 0x1B0) = (arg1 < 0) ? 0x7FFF : arg1;
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

static inline s32 active_001F2EC0(s32 index) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = gSzModel_ahModel[index];
    if (obj == NULL) {
        return 0;
    }
    if (*(s8 *)((u8 *)obj + 0x1F2) >= 0) {
        return 1;
    }
    return 0;
}

s32 SzModel_GetRef(s32 arg0, s32 arg1, s32 arg2) {
    Obj_0031ABB0 *obj;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    obj = gSzModel_ahModel[arg0];
    if (obj == NULL) {
        return 0;
    }
    if (!active_001F2EC0(arg0)) {
        return 0;
    }
    if (!((Flags_001F2EC0 *)((u8 *)obj + 0x20C))->available) {
        return 0;
    }
    if (arg1 < 0 || arg1 >= 8) {
        return 0;
    }
    if (!(*(u16 *)((arg1 << 1) + (s32)obj + 0x1B0) & 0x8000)) {
        return 0;
    }
    *(Vec4_001F2EC0 *)arg2 = *(Vec4_001F2EC0 *)((arg1 << 4) + (s32)obj + 0xA0);
    return 1;
}

s32 SzModel_SetMaxOT(s32 arg0, s16 arg1) {
    Obj_0031ABB0 *temp_v0;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    temp_v0 = gSzModel_ahModel[arg0];
    if (temp_v0 == NULL) {
        return 0;
    }
    *(s16 *)((u8 *)temp_v0 + 0x20A) = arg1;
    return 1;
}

s32 SzModel_GetMaxOT(s32 arg0) {
    Obj_0031ABB0 *temp_v0;

    if (arg0 < 0 || arg0 >= 0x54) {
        return -1;
    }
    temp_v0 = gSzModel_ahModel[arg0];
    if (temp_v0 == NULL) {
        return -1;
    }
    return *(u16 *)((u8 *)temp_v0 + 0x20A);
}

typedef struct {
    s8 reserved : 1;
    s8 enabled : 1;
} Flags_001F30B0;

s32 SzModel_SetDrawFlag(s32 arg0, s32 arg1) {
    Obj_0031ABB0 *obj;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }

    obj = gSzModel_ahModel[arg0];
    if (obj == NULL) {
        return 0;
    }

    ((Flags_001F30B0 *)((u8 *)obj + 0x20C))->enabled = (s8)arg1;
    return 1;
}

typedef struct {
    s8 unused : 1;
    s8 enabled : 1;
} Flags_001F3130;

s32 SzModel_GetDrawFlag(s32 arg0) {
    Obj_0031ABB0 *temp_v0;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    temp_v0 = gSzModel_ahModel[arg0];
    if (temp_v0 == NULL) {
        return 0;
    }
    return ((Flags_001F3130 *)((u8 *)temp_v0 + 0x20C))->enabled ? 1 : 0;
}

typedef struct {
    s8 low : 6;
    s8 flag : 1;
    s8 high : 1;
} Flags_001F3190;

s32 SzModel_SetCalcFlag(s32 arg0, s32 arg1) {
    Obj_0031ABB0 *obj;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    obj = gSzModel_ahModel[arg0];
    if (obj == NULL) {
        return 0;
    }
    ((Flags_001F3190 *)((u8 *)obj + 0x20C))->flag = arg1;
    return 1;
}

typedef struct {
    s8 : 6;
    s8 active : 1;
    s8 : 1;
} Flags_001F3210;

s32 SzModel_GetCalcFlag(s32 arg0) {
    Obj_0031ABB0 *temp_v0;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    temp_v0 = gSzModel_ahModel[arg0];
    if (temp_v0 == NULL) {
        return 0;
    }
    return ((Flags_001F3210 *)((u8 *)temp_v0 + 0x20C))->active ? 1 : 0;
}

typedef struct {
    s8 : 7;
    s8 enabled : 1;
} Flags_001F3270;

s32 SzModel_SetFogFlag(s32 arg0, s64 arg1) {
    Obj_0031ABB0 *obj;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    obj = gSzModel_ahModel[arg0];
    if (obj == NULL) {
        return 0;
    }
    ((Flags_001F3270 *)((u8 *)obj + 0x20C))->enabled = (s8)arg1;
    return 1;
}

typedef struct {
    s8 enabled : 1;
} Flags_001F32F0;

s32 SzModel_SetPauseFlag(s32 arg0, s64 arg1) {
    Obj_0031ABB0 *temp_a2;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    temp_a2 = gSzModel_ahModel[arg0];
    if (temp_a2 == NULL) {
        return 0;
    }
    ((Flags_001F32F0 *)((u8 *)temp_a2 + 0x20D))->enabled = arg1;
    return 1;
}

typedef struct {
    s8 active : 1;
} Flags_001F3360;

s32 SzModel_GetPauseFlag(s32 arg0) {
    Obj_0031ABB0 *temp_v0;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    temp_v0 = gSzModel_ahModel[arg0];
    if (temp_v0 == NULL) {
        return 0;
    }
    return ((Flags_001F3360 *)((u8 *)temp_v0 + 0x20D))->active ? 1 : 0;
}

typedef struct {
    s8 : 1;
    s8 enabled : 1;
} Flags_001F33C0;

s32 SzModel_SetStoneFlag(s32 arg0, s64 arg1) {
    Obj_0031ABB0 *temp_a2;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    temp_a2 = gSzModel_ahModel[arg0];
    if (temp_a2 == NULL) {
        return 0;
    }
    ((Flags_001F33C0 *)((u8 *)temp_a2 + 0x20D))->enabled = (s8)arg1;
    return 1;
}

typedef struct {
    s8 bit0 : 1;
    s8 enabled : 1;
} Flags_001F3440;

s32 SzModel_GetStoneFlag(s32 arg0) {
    Obj_0031ABB0 *temp_v0;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    temp_v0 = gSzModel_ahModel[arg0];
    if (temp_v0 == NULL) {
        return 0;
    }
    return ((Flags_001F3440 *)((u8 *)temp_v0 + 0x20D))->enabled ? 1 : 0;
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

s32 SzModel_GetStoneRatio(s32 arg0) {
    Obj_0031ABB0 *temp_v1;

    if (arg0 < 0 || arg0 >= 0x54) {
        return -1;
    }
    temp_v1 = gSzModel_ahModel[arg0];
    if (temp_v1 == NULL) {
        return -1;
    }
    if (((Flags_001F3690 *)((u8 *)temp_v1 + 0x20D))->active != 0) {
        return *(u8 *)((u8 *)temp_v1 + 0x200);
    }
    return -1;
}

typedef struct Table_001F3700 {
    s32 *values;
    s32 unused;
    s32 count;
} Table_001F3700;

extern Table_001F3700 gSzEffect_aEffFuncTbl[3];
extern s8 gSzEffect_el;

void SzEffect_Init(void) {
    s32 i;
    s32 *values;
    s32 *count;
    Table_001F3700 *table;

    table = gSzEffect_aEffFuncTbl;
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
    RhMem_FillMemory(&gSzEffect_el, 0, 0x354);
    SzEffect_Clear();
    SzEffect_SetBlackOutForMonster(0x80);
    SzEffect_SetBlackOutForDuel(0x80);
    SzEffect_SetBlackOutForBattle(0x80);
}

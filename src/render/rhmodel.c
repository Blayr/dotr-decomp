/* Model drawing and motions (RhModel_*). */

#include "common.h"

/* Relocates the model file at `model` (its offsets become pointers) and binds its textures. */
s32 RhModel_BindAddress(void *model) {
    s32 *sections;
    s32 i;
    u32 *entries;
    u32 value;
    u32 *target;
    u8 *resolved;

    sections = (s32 *)((u8 *)model + 0x10);
    entries = (u32 *)((u8 *)model + *(s32 *)((u8 *)model + 0x50));
    for (i = 0; entries[i] != 0xFFFFFFFF; i++) {
        value = entries[i];
        switch (value & 0xF0000000) {
        case 0x20000000:
            target = (u32 *)((u8 *)model + sections[2] + (value & 0x0FFFFFFF));
            break;
        case 0x30000000:
            target = (u32 *)((u8 *)model + sections[4] + (value & 0x0FFFFFFF));
            break;
        case 0x40000000:
            target = (u32 *)((u8 *)model + sections[6] + (value & 0x0FFFFFFF));
            break;
        case 0x50000000:
            target = (u32 *)((u8 *)model + sections[8] + (value & 0x0FFFFFFF));
            break;
        default:
            continue;
        }
        value = *target;
        switch (value & 0xF0000000) {
        case 0x20000000:
            resolved = (u8 *)model + sections[2] + (value & 0x0FFFFFFF);
            break;
        case 0x30000000:
            resolved = (u8 *)model + sections[4] + (value & 0x0FFFFFFF);
            break;
        case 0x40000000:
            resolved = (u8 *)model + sections[6] + (value & 0x0FFFFFFF);
            break;
        case 0x50000000:
            resolved = (u8 *)model + sections[8] + (value & 0x0FFFFFFF);
            break;
        default:
            continue;
        }
        *target = (u32)resolved;
    }
    return 1;
}

typedef struct Flags_0020F4E0 {
    u8 bit0 : 1;
    u8 bit1 : 1;
    u8 bit2 : 1;
    u8 bit3 : 1;
    u8 bit4 : 1;
    u8 bit5 : 1;
    u8 bit6 : 1;
    u8 bit7 : 1;
} Flags_0020F4E0;

typedef struct Object_0020F4E0 {
    u8 *data;
    Flags_0020F4E0 flags4;
    Flags_0020F4E0 flags5;
    u8 pad6[0x26];
    s32 result;
} Object_0020F4E0;

typedef struct Offset_0020F4E0 {
    s32 unused;
    u32 value : 28;
    u32 flags : 4;
} Offset_0020F4E0;

typedef struct Transform_0020F4E0 {
    u8 pad0[0x30];
    union {
        __int128 quad;
        struct {
            f32 x, y, z, w;
        } values;
    } vector;
} Transform_0020F4E0;

extern s32 require_coordinate_index;

/* Draws model `model` through VU1 (fast or normal method, by its view-volume test and the point light). */
void *RhModel_Draw(void *packet, void *model) {
    extern s32 RhView_GetSampleZ(void *, f32);
    s32 temp_v1;
    Transform_0020F4E0 *transform;
    s32 var_s1;
    Object_0020F4E0 *obj;

    obj = model;
    if (!obj->flags4.bit1 || !obj->flags5.bit2) {
        packet = RhVu1Mac_SetFogOnOff(packet, (u8)obj->flags4.bit1, obj->flags5.bit2);
    }
    *(void **)(SCRATCHPAD_ADDR + 0xC0) = packet;
    *(u8 **)(SCRATCHPAD_ADDR + 0xDC) = obj->data + 0x10;
    *(s32 *)(SCRATCHPAD_ADDR + 0xD8) = ((Offset_0020F4E0 *)(obj->data + *(s32 *)(*(u8 **)(SCRATCHPAD_ADDR + 0xDC) + 8)))->value;
    RhGeom_PushMatrix(0);
    transform = (Transform_0020F4E0 *)(obj->data + *(s32 *)*(u8 **)(SCRATCHPAD_ADDR + 0xDC));
    *(__int128 *)(SCRATCHPAD_ADDR + 0x20) = transform->vector.quad;
    *(s32 *)(SCRATCHPAD_ADDR + 0x2C) = 0x3F800000;
    if (obj->flags5.bit4 != 0) {
        RhMem_CopyMemory16((void *)SCRATCHPAD_ADDR, (u8 *)model + 0x50, 1);
    } else {
        RhGeom_MulMatrixVector((void *)SCRATCHPAD_ADDR, NULL, (void *)(SCRATCHPAD_ADDR + 0x20));
    }
    obj->result = RhView_GetSampleZ((void *)SCRATCHPAD_ADDR, transform->vector.values.w);
    var_s1 = 0;
    if (obj->flags4.bit0 && (RhVu1Mac_GetPointLight(NULL, (void *)(SCRATCHPAD_ADDR + 0x50), (f32 *)(SCRATCHPAD_ADDR + 0x30), (f32 *)(SCRATCHPAD_ADDR + 0x34), (f32 *)(SCRATCHPAD_ADDR + 0x38)) != 0) && (RhGeom_GetPointsDistance((f32 *)(SCRATCHPAD_ADDR + 0x50), (f32 *)SCRATCHPAD_ADDR) <= (*(f32 *)(SCRATCHPAD_ADDR + 0x34) + transform->vector.values.w))) {
        var_s1 = 1;
    }
    require_coordinate_index = 0;
    if (obj->flags4.bit2 != 0) {
        packet = lRhModel_DrawNormalMethod(model, var_s1);
    } else {
        *(s32 *)(SCRATCHPAD_ADDR + 0xB0) = RhView_CheckViewVolume((void *)(SCRATCHPAD_ADDR + 0x20), transform->vector.values.w);
        temp_v1 = *(s32 *)(SCRATCHPAD_ADDR + 0xB0);
        if (temp_v1 & 1) {
            if ((temp_v1 & 4) || (*(s32 *)(*(u8 **)(SCRATCHPAD_ADDR + 0xDC) + 0x1C) > 0) || (var_s1 != 0)) {
                packet = lRhModel_DrawNormalMethod(model, var_s1);
            } else {
                packet = lRhModel_DrawFastMethod(model);
            }
        }
    }
    RhGeom_PopMatrix();
    if ((obj->flags4.bit1 == 0) || (obj->flags5.bit2 == 0)) {
        packet = RhVu1Mac_SetFogOnOff(packet, 1, 1);
    }
    return packet;
}

typedef struct {
    u8 pad[4];
    u8 reserved4_0 : 1;
    u8 flag4_1 : 1;
    u8 flag4_2 : 1;
    u8 reserved4_3 : 5;
    u8 reserved5_0 : 2;
    u8 flag5_2 : 1;
    u8 flag5_3 : 1;
    u8 reserved5_4 : 4;
} Flags_0020F780;

extern u8 gRhModel_mlsmSwapArea[];

/* Picks the VU1 draw method of a model part (lit, fogged, clipped; `noClip` turns clipping off). */
void *lRhModel_DrawNormalMethod(void *part, s32 noClip) {
    Flags_0020F780 *obj = part;
    s32 flags;
    s32 result;
    u32 flag5;
    u32 flag4;

    flags = 1;
    flag5 = obj->flag5_2 ? 0x40 : 0;
    flag4 = (obj->flag4_1 != 0) ? 0x10 : 0;
    flags |= flag4 | flag5;
    flags |= noClip ? 2 : 0;
    RhGeomEx_SetMatrixForPointLight();
    if (!obj->flag4_2) {
        if (*(s32 *)(SCRATCHPAD_ADDR + 0xB0) & 4) {
            flags |= 0x20;
        }
        *(void **)(SCRATCHPAD_ADDR + 0xC4) = RhVu1Mac_ChangeDrawMethod(*(void **)(SCRATCHPAD_ADDR + 0xC0), flags);
    } else {
        *(void **)(SCRATCHPAD_ADDR + 0xC4) = RhVu1Mac_ReserveChangeDrawMethod(*(void **)(SCRATCHPAD_ADDR + 0xC0));
    }
    lRhModel_DrawCommonPart(obj);
    if (!(*(s32 *)(SCRATCHPAD_ADDR + 0xB0) & 1)) {
        return *(void **)(SCRATCHPAD_ADDR + 0xC0);
    }
    if (*(s32 *)(*(u8 **)(SCRATCHPAD_ADDR + 0xDC) + 0x1C) > 0) {
        if (obj->flag5_3) {
            result = *(s32 *)(SCRATCHPAD_ADDR + 0xD0);
        } else {
            RhMem_CopyMemory16(gRhModel_mlsmSwapArea, (void *)SCRATCHPAD_ADDR, 0x11);
            result = RhBase_SetZBufferMode((s32)RhModelCpu_DrawAlpha(
                (u8 *)RhBase_SetZBufferMode(*(s32 *)(SCRATCHPAD_ADDR + 0xD0), 0),
                *(s32 *)(SCRATCHPAD_ADDR + 0xCC),
                *(s32 *)(*(u8 **)(SCRATCHPAD_ADDR + 0xDC) + 0x1C),
                obj->flag4_1), 1);
            RhMem_CopyMemory16((void *)SCRATCHPAD_ADDR, gRhModel_mlsmSwapArea, 0x11);
        }
        *(s32 *)(SCRATCHPAD_ADDR + 0xD4) = result;
    } else {
        *(s32 *)(SCRATCHPAD_ADDR + 0xD4) = *(s32 *)(SCRATCHPAD_ADDR + 0xC8);
    }
    if (*(s32 *)(SCRATCHPAD_ADDR + 0xB0) & 4) {
        flags |= 0x20;
    } else if (noClip == 0) {
        RhView_GetViewScreenMatrix((void *)SCRATCHPAD_ADDR);
        lRhModel_ChangeL2VtoL2S(*(s32 *)(SCRATCHPAD_ADDR + 0xB4) + 0x10, 0x70000000,
                     ((*(s32 *)(SCRATCHPAD_ADDR + 0xD8) - 0x10) >> 4) / 7);
    }
    if (*(void **)(SCRATCHPAD_ADDR + 0xB4) == (void *)(SCRATCHPAD_ADDR + 0xF0)) {
        RhMem_CopyMemory16(*(u8 **)(SCRATCHPAD_ADDR + 0xC4) + 0x10, (void *)(SCRATCHPAD_ADDR + 0x100),
                     (*(s32 *)(SCRATCHPAD_ADDR + 0xD8) - 0x10) >> 4);
    }
    if (obj->flag4_2) {
        RhVu1Mac_ChangeDrawMethod(*(void **)(SCRATCHPAD_ADDR + 0xC0), flags);
    }
    return *(void **)(SCRATCHPAD_ADDR + 0xD4);
}

typedef struct {
    u8 pad[4];
    u8 unused4_0 : 1;
    u8 flag4 : 1;
    u8 unused4_2 : 6;
    u8 unused5_0 : 2;
    u8 flag5 : 1;
    u8 unused5_3 : 5;
} Flags_0020FA10;

/* Picks the fast VU1 draw method of a model part. */
void *lRhModel_DrawFastMethod(void *part) {
    u32 mode = 1;
    u32 flag5 = ((Flags_0020FA10 *)part)->flag5 ? 0x40 : 0;
    u32 flag4 = (((Flags_0020FA10 *)part)->flag4 != 0) ? 0x10 : 0;
    mode |= flag4 | flag5;
    *(void **)(SCRATCHPAD_ADDR + 0xC4) = RhVu1Mac_ChangeDrawMethod(*(void **)(SCRATCHPAD_ADDR + 0xC0), mode);
    RhView_GetViewScreenMatrix((void *)SCRATCHPAD_ADDR);
    RhGeomEx_SetMatrixForStraightLight((void *)SCRATCHPAD_ADDR);
    lRhModel_DrawCommonPart(part);
    if (*(u8 **)(SCRATCHPAD_ADDR + 0xB4) == (u8 *)(SCRATCHPAD_ADDR + 0xF0)) {
        RhMem_CopyMemory16(*(u8 **)(SCRATCHPAD_ADDR + 0xC4) + 0x10, (void *)(SCRATCHPAD_ADDR + 0x100), (*(s32 *)(SCRATCHPAD_ADDR + 0xD8) - 0x10) >> 4);
    }
    *(void **)(SCRATCHPAD_ADDR + 0xD4) = *(void **)(SCRATCHPAD_ADDR + 0xC8);
    return *(void **)(SCRATCHPAD_ADDR + 0xD4);
}

typedef struct {
    u8 bit0 : 1;
    u8 bit1 : 1;
    u8 bit2 : 1;
    u8 bit3 : 1;
    u8 bit4 : 1;
    u8 bit5 : 1;
    u8 bit6 : 1;
    u8 bit7 : 1;
} Flags_0020FAF0;

typedef struct {
    u8 *data;
    Flags_0020FAF0 flags4;
    Flags_0020FAF0 flags5;
    u8 pad6[2];
    u8 *src8;
    f32 valueC;
    u8 *src10;
    f32 value14;
    f32 value18;
    f32 value1C;
    s32 value20;
    s32 value24;
    s32 value28;
} Args_0020FAF0;

typedef struct {
    u8 pad0[8];
    s32 offset8;
    s32 sizeC;
    u8 pad10[8];
    s32 offset18;
    s32 size1C;
    u8 pad20[0x34];
    f32 value54;
    s32 value58;
} Data_0020FAF0;

/* Sends what every draw method of a model part shares. */
void lRhModel_DrawCommonPart(void *part) {
    Args_0020FAF0 *arg = part;
    s32 value24;

    if ((*(s32 *)(SCRATCHPAD_ADDR + 0xD8) + ((*(Data_0020FAF0 **)(SCRATCHPAD_ADDR + 0xDC))->value58 << 8)) > 0x3F10) {
        *(u8 **)(SCRATCHPAD_ADDR + 0xB4) = *(u8 **)(SCRATCHPAD_ADDR + 0xC4);
    } else {
        *(u8 **)(SCRATCHPAD_ADDR + 0xB4) = (u8 *)(SCRATCHPAD_ADDR + 0xF0);
    }

    **(__int128 **)(SCRATCHPAD_ADDR + 0xC4) = *(__int128 *)(arg->data + (*(Data_0020FAF0 **)(SCRATCHPAD_ADDR + 0xDC))->offset8);
    RhMem_CopyMemory16(*(u8 **)(SCRATCHPAD_ADDR + 0xC4) + *(s32 *)(SCRATCHPAD_ADDR + 0xD8),
                 arg->data + (*(Data_0020FAF0 **)(SCRATCHPAD_ADDR + 0xDC))->offset8 + *(s32 *)(SCRATCHPAD_ADDR + 0xD8),
                 ((*(Data_0020FAF0 **)(SCRATCHPAD_ADDR + 0xDC))->sizeC - *(s32 *)(SCRATCHPAD_ADDR + 0xD8)) >> 4);
    lRhModel_DynamicAddressBind(arg->data, *(u8 **)(SCRATCHPAD_ADDR + 0xC4), *(u8 **)(SCRATCHPAD_ADDR + 0xC4), 0);
    *(u8 **)(SCRATCHPAD_ADDR + 0xC8) = *(u8 **)(SCRATCHPAD_ADDR + 0xC4) + (*(Data_0020FAF0 **)(SCRATCHPAD_ADDR + 0xDC))->sizeC;

    if ((*(Data_0020FAF0 **)(SCRATCHPAD_ADDR + 0xDC))->size1C > 0) {
        if (arg->flags5.bit3) {
            *(u8 **)(SCRATCHPAD_ADDR + 0xCC) = (u8 *)RhBase_SetZBufferMode((s32)*(u8 **)(SCRATCHPAD_ADDR + 0xC8), 0);
        } else {
            **(s32 **)(SCRATCHPAD_ADDR + 0xC8) = 0x20000000;
            (*(s32 **)(SCRATCHPAD_ADDR + 0xC8))[1] = (s32)(*(u8 **)(SCRATCHPAD_ADDR + 0xC8) + (*(Data_0020FAF0 **)(SCRATCHPAD_ADDR + 0xDC))->size1C + 0x10);
            (*(s32 **)(SCRATCHPAD_ADDR + 0xC8))[2] = 0;
            (*(s32 **)(SCRATCHPAD_ADDR + 0xC8))[3] = 0;
            *(u8 **)(SCRATCHPAD_ADDR + 0xCC) = *(u8 **)(SCRATCHPAD_ADDR + 0xC8) + 0x10;
        }
        RhMem_CopyMemory16(*(u8 **)(SCRATCHPAD_ADDR + 0xCC),
                     arg->data + (*(Data_0020FAF0 **)(SCRATCHPAD_ADDR + 0xDC))->offset18,
                     (*(Data_0020FAF0 **)(SCRATCHPAD_ADDR + 0xDC))->size1C >> 4);
        lRhModel_DynamicAddressBind(arg->data, *(u8 **)(SCRATCHPAD_ADDR + 0xC4), *(u8 **)(SCRATCHPAD_ADDR + 0xCC), 1);
        *(u8 **)(SCRATCHPAD_ADDR + 0xD0) = *(u8 **)(SCRATCHPAD_ADDR + 0xCC) + (*(Data_0020FAF0 **)(SCRATCHPAD_ADDR + 0xDC))->size1C;
        if (arg->flags5.bit3) {
            *(u8 **)(SCRATCHPAD_ADDR + 0xD0) = (u8 *)RhBase_SetZBufferMode((s32)*(u8 **)(SCRATCHPAD_ADDR + 0xD0), 1);
        }
    } else {
        *(u8 **)(SCRATCHPAD_ADDR + 0xCC) = NULL;
        *(u8 **)(SCRATCHPAD_ADDR + 0xD0) = NULL;
    }

    if (arg->flags4.bit6) {
        value24 = arg->value24;
    } else {
        value24 = -1;
    }
    lRhModel_SetupTexture(arg->data, *(u8 **)(SCRATCHPAD_ADDR + 0xC4), *(u8 **)(SCRATCHPAD_ADDR + 0xCC), value24);
    lRhModel_SetupOptionObject(arg->data, *(u8 **)(SCRATCHPAD_ADDR + 0xC4), *(u8 **)(SCRATCHPAD_ADDR + 0xCC), !arg->flags4.bit5, arg->value20);
    if (arg->flags4.bit7 || arg->flags5.bit0 || arg->flags5.bit1) {
        lRhModel_SetMaterialIntensity(*(u8 **)(SCRATCHPAD_ADDR + 0xC4),
                     *(u8 **)(SCRATCHPAD_ADDR + 0xC4) + (*(Data_0020FAF0 **)(SCRATCHPAD_ADDR + 0xDC))->sizeC,
                     *(u8 **)(SCRATCHPAD_ADDR + 0xCC),
                     *(u8 **)(SCRATCHPAD_ADDR + 0xCC) + (*(Data_0020FAF0 **)(SCRATCHPAD_ADDR + 0xDC))->size1C,
                     arg);
    }
    *(s32 *)(SCRATCHPAD_ADDR + 0xB8) = arg->value28;
    if (!arg->flags4.bit2) {
        lRhModel_SetupNoMotion(arg->data);
    } else {
        *(s32 *)(SCRATCHPAD_ADDR + 0xB0) = 0;
        *(f32 *)(SCRATCHPAD_ADDR + 0xBC) = (*(Data_0020FAF0 **)(SCRATCHPAD_ADDR + 0xDC))->value54;
        if (arg->flags4.bit3) {
            lRhModel_SetupMultiMotion(arg->data, arg->src8 + 0xC, arg->src10 + 0xC,
                         arg->valueC, arg->value14, arg->value18, arg->value1C);
        } else if (arg->flags4.bit4) {
            lRhModel_SetupFloatMotion(arg->data, arg->src8 + 0xC, arg->valueC);
        } else {
            lRhModel_SetupPulseMotion(arg->data, arg->src8 + 0xC, arg->valueC);
        }
    }
}

typedef struct Header_0020FED0 {
    u8 pad[0x30];
    s32 offset0;
    s32 pad34;
    s32 offset1;
} Header_0020FED0;

/* Relocates a model's dynamic packet addresses against `base` (`second` picks the other table). */
void lRhModel_DynamicAddressBind(void *model, void *base, void *packets, s32 second) {
    Header_0020FED0 *header;
    s32 i;
    s32 value;
    s32 *table;
    s32 *entry;
    s32 tagged;

    header = (Header_0020FED0 *)((u8 *)model + 0x10);
    if (second != 0) {
        table = (s32 *)((u8 *)model + header->offset1);
    } else {
        table = (s32 *)((u8 *)model + header->offset0);
    }
    for (i = 0; (value = *table) != -1; i++) {
        switch (value & ~0x0FFFFFFF) {
        case 0x20000000:
        case 0x40000000:
            entry = (s32 *)((u32)packets + (value & 0x0FFFFFFF));
            tagged = *entry;
            switch (tagged & ~0x0FFFFFFF) {
            case 0x20000000:
            case 0x40000000:
                *entry = (u32)base + (tagged & 0x0FFFFFFF);
                break;
            }
            break;
        }
        table++;
    }
}

typedef struct {
    f32 x, y, z, w;
} V4_0020FF80;

typedef struct {
    u8 pad00[0x90];
    u8 *data;
    u8 pad94[0xB8 - 0x94];
    V4_0020FF80 *dst;
} Spr_0020FF80;

extern void *gRhModel_dwStack;
extern u8 D_70004000[];
extern u8 gRhModel_vecScale[];

/* Builds a model's node matrices from its rest pose (no motion). */
s32 lRhModel_SetupNoMotion(void *model) {
    Spr_0020FF80 *spr = (Spr_0020FF80 *)SCRATCHPAD_ADDR;
    u8 *data = (u8 *)model + *(s32 *)((u8 *)model + 0x10);

    if (spr->dst != NULL) {
        *spr->dst = *(V4_0020FF80 *)(data + 0x20);
    }
    spr->data = data;
    asm {
        la v0, gRhModel_dwStack
        sw sp, 0(v0)
        la at, D_70004000
        addiu sp, at, 0
    }
    lRhModel_SetupNoMotionRecursive((void *)SCRATCHPAD_ADDR, data, gRhModel_vecScale);
    asm {
        la v0, gRhModel_dwStack
        lw sp, 0(v0)
    }
    return 1;
}

typedef struct Vec3_00210010 {
    f32 x, y, z;
} Vec3_00210010;

typedef struct Node_00210010 {
    Vec3_00210010 scale;
    u16 flags;
    u16 matrix;
    Vec3_00210010 rotation;
    u32 child;
    Vec3_00210010 translation;
    u32 next;
} Node_00210010;

typedef struct Model_00210010 {
    u8 pad0[0x90];
    u8 *nodes;
    u8 pad94[0x20];
    f32 (*matrices)[4];
} Model_00210010;

typedef struct Entry_00210010 {
    s32 id;
    s32 active;
    u8 pad8[8];
    f32 matrix[16];
} Entry_00210010;

extern Vec3_00210010 D_00295080;
extern u32 require_coordinate_no;

/* Builds one node's matrix from its rest pose, then its children's and siblings'. */
void lRhModel_SetupNoMotionRecursive(void *modelIn, void *node, void *parentScaleIn) {
    extern Entry_00210010 require_coordinate[];
    u8 buffer[0x20];
    Vec3_00210010 translation;
    Vec3_00210010 *scale;
    s32 flags;
    s32 mode;
    f32 *matrix;
    s32 matrixIndex;
    Entry_00210010 *entry;
    u32 i;
    u32 offset;
    Model_00210010 *model = modelIn;
    Vec3_00210010 *parentScale = parentScaleIn;

    scale = (Vec3_00210010 *)(((u32)buffer + 15) & ~15);
    for (;;) {
        RhMem_CopyMemory16(scale, parentScale, 1);
        flags = ((Node_00210010 *)node)->flags;
        mode = flags & 3;
        if (mode != 3) {
            translation = D_00295080;
            translation.x = ((Node_00210010 *)node)->translation.x * parentScale->x;
            translation.y = ((Node_00210010 *)node)->translation.y * parentScale->y;
            translation.z = ((Node_00210010 *)node)->translation.z * parentScale->z;
            RhGeomEx_PushMatrix();
            RhGeomEx_ScaleRotXYZTransMatrix(NULL, (flags & 2) ? NULL : &((Node_00210010 *)node)->rotation,
                         (flags & 1) ? NULL : &translation);
        }
        if (!(flags & 4)) {
            scale->x *= ((Node_00210010 *)node)->scale.x;
            scale->y *= ((Node_00210010 *)node)->scale.y;
            scale->z *= ((Node_00210010 *)node)->scale.z;
        }
        matrixIndex = ((Node_00210010 *)node)->matrix;
        if (matrixIndex != 0) {
            matrix = model->matrices[matrixIndex];
            RhGeomEx_GetMatrix(matrix);
            RhGeom_ScaleMatrix(matrix, scale);
        }
        entry = require_coordinate;
        for (i = 0; i < require_coordinate_no; entry++, i++) {
            if (require_coordinate_index == entry->id) {
                require_coordinate[i].active = 1;
                RhGeom_GetMatrix(require_coordinate[i].matrix);
                break;
            }
        }
        require_coordinate_index++;
        offset = ((Node_00210010 *)node)->child;
        if (offset != 0) {
            lRhModel_SetupNoMotionRecursive(model, model->nodes + (offset & 0x0FFFFFFF), scale);
        }
        if (mode != 3) {
            RhGeomEx_PopMatrix();
        }
        offset = ((Node_00210010 *)node)->next;
        if (offset == 0) {
            break;
        }
        node = model->nodes + (offset & 0x0FFFFFFF);
    }
}

typedef struct {
    u8 pad00[0x90];
    u8 *data;
    s32 motion94;
    f32 frame98;
    s32 count9C;
    s32 motionA0;
    f32 frameA4;
    f32 valueA8;
    f32 valueAC;
    u8 padB0[0xE0 - 0xB0];
    u16 countE0;
} Spr_00210260;

typedef struct {
    u8 pad0[4];
    u16 count;
    u8 pad6[2];
    s32 *motion;
} Motion_00210260;

/* Builds a model's node matrices from two motions blended at their frames and weights. */
s32 lRhModel_SetupMultiMotion(void *arg0, void *arg1, void *arg2, f32 frame, f32 frame2, f32 value, f32 value2) {
    Spr_00210260 *spr = (Spr_00210260 *)SCRATCHPAD_ADDR;
    Motion_00210260 *m1 = arg1;
    Motion_00210260 *m2 = arg2;
    s32 c1;
    s32 c2;
    u8 *data = (u8 *)arg0 + *(s32 *)((u8 *)arg0 + 0x10);

    spr->data = data;
    spr->motion94 = *m1->motion;
    spr->frame98 = frame;
    c1 = m1->count;
    c2 = m2->count;
    spr->count9C = (c1 < c2) ? c1 : c2;
    spr->motionA0 = *m2->motion;
    spr->frameA4 = frame2;
    spr->valueA8 = value;
    spr->valueAC = value2;
    spr->countE0 = ((u16 *)m1->motion)[4];
    {
    register void **save = &gRhModel_dwStack;
    asm {
        sw sp, 0(save)
        la at, D_70004000
        addiu sp, at, 0
    }
    }
    lRhModel_SetupMultiMotionRecursive(data, 0, gRhModel_vecScale);
    asm {
        la v0, gRhModel_dwStack
        lw sp, 0(v0)
    }
    return 1;
}

typedef f32 Vec4_00210310[4] __attribute__((aligned(16)));

typedef struct {
    Vec4_00210310 v;
} Quad_00210310;

typedef struct {
    f32 v[4];
} Plain4_00210310;

typedef struct {
    u8 pad0[0xC];
    u16 flags;
    u16 idx;
    u8 pad10[0xC];
    u32 child;
    u8 pad20[0xC];
    u32 sibling;
    Quad_00210310 pos;
} Node_00210310;

typedef struct {
    f32 v00[4];
    f32 v10[4];
    f32 v20[4];
    u8 pad30[0x60];
    u8 *base90;
    u8 *tbl94;
    f32 f98;
    s32 cnt9C;
    u8 *tblA0;
    f32 fA4;
    f32 fA8;
    f32 fAC;
    u32 flagsB0;
    u8 *ptrB4;
    Plain4_00210310 *outB8;
    f32 fBC;
    u8 padC0[0x20];
    u16 flagsE0;
} Spr_00210310;

typedef struct {
    s32 id;
    s32 used;
    u8 pad8[8];
    u8 data[0x40];
} Slot_00210310;

/* One node of lRhModel_SetupMultiMotion, then its children and siblings. */
s32 lRhModel_SetupMultiMotionRecursive(void *arg0, s32 depth, void *arg2) {
    extern Slot_00210310 require_coordinate[];
    Spr_00210310 *spr = (Spr_00210310 *)SCRATCHPAD_ADDR;
    u8 buf[32];
    f32 *vec = (f32 *)(((s32)buf + 0xF) & ~0xF);
    u32 flags;
    s32 mode;
    u8 *p;
    u8 *q;
    f32 f;
    f32 max;
    u32 i;

    for (;;) {
        Node_00210310 *node = arg0;

        RhMem_CopyMemory16(vec, arg2, 1);
        flags = node->flags;
        RhMem_CopyMemory16(spr, node, 3);
        if (depth < spr->cnt9C) {
            p = spr->tbl94;
            q = spr->tblA0;
            if (spr->flagsE0 & 4) {
                p += depth * 0x18;
                q += depth * 0x18;
            } else {
                p += depth * 0x10;
                q += depth * 0x10;
            }
            {
                u16 nflags = node->flags;
                f32 *pos = spr->v20;
                f32 *rot = spr->v10;
                f32 scale = depth == 0 ? 1.0f : spr->fBC;

                flags = lRhModel_GetMultiMotionItem(p, q, nflags, spr->f98, spr->fA8, spr->fA4, spr->fAC, pos, rot, spr, scale);
            }
            if (depth == 0 && (spr->flagsE0 & 4)) {
                RhMem_CopyMemory4(spr, node, 3);
            }
        }
        if (depth == 0) {
            if (spr->outB8 != NULL) {
                *spr->outB8 = *(Plain4_00210310 *)spr->v20;
            }
        }
        mode = flags & 3;
        depth++;
        if (mode != 3) {
            spr->v20[0] *= ((f32 *)arg2)[0];
            spr->v20[1] *= ((f32 *)arg2)[1];
            spr->v20[2] *= ((f32 *)arg2)[2];
            RhGeomEx_PushMatrix();
            RhGeomEx_ScaleRotXYZTransMatrix(NULL, (flags & 2) ? NULL : spr->v10, (flags & 1) ? NULL : spr->v20);
        }
        if (!(flags & 4)) {
            vec[0] *= spr->v00[0];
            vec[1] *= spr->v00[1];
            vec[2] *= spr->v00[2];
        }
        if (node->idx != 0) {
            p = spr->ptrB4 + node->idx * 0x10;
            RhGeomEx_GetMatrix(p);
            RhGeom_ScaleMatrix(p, vec);
        }
        if (!(node->flags & 0x8000)) {
            f = node->pos.v[3];
            max = vec[0];
            if (max < vec[1]) {
                max = vec[1];
            }
            if (max < vec[2]) {
                max = vec[2];
            }
            f = f * (spr->fBC * max);
            *(Quad_00210310 *)spr->v20 = node->pos;
            spr->v20[3] = 1.0f;
            RhGeomEx_PushMatrix();
            RhGeom_ScaleMatrix(NULL, vec);
            spr->flagsB0 |= RhView_CheckViewVolume(spr->v20, f);
            RhGeomEx_PopMatrix();
        }
        for (i = 0; i < require_coordinate_no; i++) {
            if (require_coordinate_index == require_coordinate[i].id) {
                require_coordinate[i].used = 1;
                RhGeom_GetMatrix(require_coordinate[i].data);
                break;
            }
        }
        require_coordinate_index++;
        if (node->child != 0) {
            depth = lRhModel_SetupMultiMotionRecursive(spr->base90 + (node->child & 0x0FFFFFFF), depth, vec);
        }
        if (mode != 3) {
            RhGeomEx_PopMatrix();
        }
        if (node->sibling == 0) {
            return depth;
        }
        arg0 = spr->base90 + (node->sibling & 0x0FFFFFFF);
    }
}

/* One node's position, rotation and scale from two motions blended. */
s32 lRhModel_GetMultiMotionItem(void *src0, void *src1, s32 flags, f32 time0, f32 weight0, f32 time1, f32 weight1,
                  void *pos, void *rot, void *scl, f32 multiplier) {
    f32 *position = pos;
    s32 *rotation = rot;
    f32 *scale = scl;
    s32 result;

    RhMem_CopyMemory16((void *)(SCRATCHPAD_ADDR + 0x30), (void *)SCRATCHPAD_ADDR, 3);
    RhMem_CopyMemory16((void *)(SCRATCHPAD_ADDR + 0x60), (void *)SCRATCHPAD_ADDR, 3);
    flags = lRhModel_GetInterpolateMotionItem(src0, time0, flags, (f32 *)(SCRATCHPAD_ADDR + 0x50), (void *)(SCRATCHPAD_ADDR + 0x40), (void *)(SCRATCHPAD_ADDR + 0x30), multiplier);
    result = lRhModel_GetInterpolateMotionItem(src1, time1, flags, (f32 *)(SCRATCHPAD_ADDR + 0x80), (void *)(SCRATCHPAD_ADDR + 0x70), (void *)(SCRATCHPAD_ADDR + 0x60), multiplier);
    position[0] = ((f32 *)(SCRATCHPAD_ADDR + 0x50))[0] * weight0 + ((f32 *)(SCRATCHPAD_ADDR + 0x80))[0] * weight1;
    position[1] = ((f32 *)(SCRATCHPAD_ADDR + 0x50))[1] * weight0 + ((f32 *)(SCRATCHPAD_ADDR + 0x80))[1] * weight1;
    position[2] = ((f32 *)(SCRATCHPAD_ADDR + 0x50))[2] * weight0 + ((f32 *)(SCRATCHPAD_ADDR + 0x80))[2] * weight1;
    RhGeom_RoationComplexInterpolate(rotation, (s32 *)(SCRATCHPAD_ADDR + 0x40), (s32 *)(SCRATCHPAD_ADDR + 0x70), weight0, weight1);
    if (!(result & 4)) {
        scale[0] = ((f32 *)(SCRATCHPAD_ADDR + 0x30))[0] * weight0 + ((f32 *)(SCRATCHPAD_ADDR + 0x60))[0] * weight1;
        scale[1] = ((f32 *)(SCRATCHPAD_ADDR + 0x30))[1] * weight0 + ((f32 *)(SCRATCHPAD_ADDR + 0x60))[1] * weight1;
        scale[2] = ((f32 *)(SCRATCHPAD_ADDR + 0x30))[2] * weight0 + ((f32 *)(SCRATCHPAD_ADDR + 0x60))[2] * weight1;
    }
    return result;
}

/* lRhModel_SetupPulseMotion's twin: fill the scratchpad header for a float-motion walk, then run
   lRhModel_SetupFloatMotionRecursive with the stack on the scratchpad (0x70004000). */

/* Builds a model's node matrices from a key-framed (float) motion at `time`. */
s32 lRhModel_SetupFloatMotion(u8 *model, u8 *motion, f32 time) {
    u8 *spr = (u8 *)SCRATCHPAD_ADDR;
    register void **saved;

    model += *(s32 *)(model + 0x10);
    *(u8 **)(spr + 0x90) = model;
    *(s32 *)(spr + 0x94) = **(s32 **)(motion + 8);
    *(f32 *)(spr + 0x98) = time;
    *(s32 *)(spr + 0x9C) = *(u16 *)(motion + 4);
    *(u16 *)(spr + 0xE0) = *(u16 *)(*(u8 **)(motion + 8) + 8);
    saved = &gRhModel_dwStack;
    asm {
        sw sp, 0x0(saved)
        la at, D_70004000
        addiu sp, at, 0x0
    }
    lRhModel_SetupFloatMotionRecursive(model, 0, gRhModel_vecScale);
    {
        register void **back = &gRhModel_dwStack;
        asm {
            lw sp, 0x0(back)
        }
    }
    return 1;
}

typedef f32 Vec4_00210940[4] __attribute__((aligned(16)));

typedef struct {
    Vec4_00210940 v;
} Quad_00210940;

typedef struct {
    f32 v[4];
} Plain4_00210940;

typedef struct {
    u8 pad0[0xC];
    u16 flags;
    u16 idx;
    u8 pad10[0xC];
    u32 child;
    u8 pad20[0xC];
    u32 sibling;
    Quad_00210940 pos;
} Node_00210940;

typedef struct {
    f32 v00[4];
    f32 v10[4];
    f32 v20[4];
    u8 pad30[0x60];
    u8 *base90;
    u8 *tbl94;
    f32 f98;
    s32 cnt9C;
    u8 padA0[0x10];
    u32 flagsB0;
    u8 *ptrB4;
    Plain4_00210940 *outB8;
    f32 fBC;
    u8 padC0[0x20];
    u16 flagsE0;
} Spr_00210940;

typedef struct {
    s32 id;
    s32 used;
    u8 pad8[8];
    u8 data[0x40];
} Slot_00210940;

/* One node of lRhModel_SetupFloatMotion, then its children and siblings. */
s32 lRhModel_SetupFloatMotionRecursive(void *arg0, s32 depth, void *arg2) {
    extern s32 lRhModel_GetInterpolateMotionItem(void *, u16, f32, void *, void *, void *, f32);
    extern Slot_00210940 require_coordinate[];
    Spr_00210940 *spr = (Spr_00210940 *)SCRATCHPAD_ADDR;
    u8 buf[32];
    f32 *vec = (f32 *)(((s32)buf + 0xF) & ~0xF);
    u32 flags;
    s32 mode;
    u8 *p;
    f32 f;
    f32 max;
    u32 i;

    for (;;) {
        Node_00210940 *node = arg0;

        RhMem_CopyMemory16(vec, arg2, 1);
        flags = node->flags;
        RhMem_CopyMemory16(spr, node, 3);
        if (depth < spr->cnt9C) {
            p = spr->tbl94;
            if (spr->flagsE0 & 4) {
                p += depth * 0x18;
            } else {
                p += depth * 0x10;
            }
            flags = lRhModel_GetInterpolateMotionItem(p, node->flags, spr->f98, spr->v20, spr->v10, spr,
                                  depth == 0 ? 1.0f : spr->fBC);
            if (depth == 0 && (spr->flagsE0 & 4)) {
                RhMem_CopyMemory4(spr, node, 3);
            }
        }
        if (depth == 0) {
            if (spr->outB8 != NULL) {
                *spr->outB8 = *(Plain4_00210940 *)spr->v20;
            }
        }
        mode = flags & 3;
        depth++;
        if (mode != 3) {
            spr->v20[0] *= ((f32 *)arg2)[0];
            spr->v20[1] *= ((f32 *)arg2)[1];
            spr->v20[2] *= ((f32 *)arg2)[2];
            RhGeomEx_PushMatrix();
            RhGeomEx_ScaleRotXYZTransMatrix(NULL, (flags & 2) ? NULL : spr->v10, (flags & 1) ? NULL : spr->v20);
        }
        if (!(flags & 4)) {
            vec[0] *= spr->v00[0];
            vec[1] *= spr->v00[1];
            vec[2] *= spr->v00[2];
        }
        if (node->idx != 0) {
            p = spr->ptrB4 + node->idx * 0x10;
            RhGeomEx_GetMatrix(p);
            RhGeom_ScaleMatrix(p, vec);
        }
        if (!(node->flags & 0x8000)) {
            f = node->pos.v[3];
            max = vec[0];
            if (max < vec[1]) {
                max = vec[1];
            }
            if (max < vec[2]) {
                max = vec[2];
            }
            f = f * (spr->fBC * max);
            *(Quad_00210940 *)spr->v20 = node->pos;
            spr->v20[3] = 1.0f;
            RhGeomEx_PushMatrix();
            RhGeom_ScaleMatrix(NULL, vec);
            spr->flagsB0 |= RhView_CheckViewVolume(spr->v20, f);
            RhGeomEx_PopMatrix();
        }
        for (i = 0; i < require_coordinate_no; i++) {
            if (require_coordinate_index == require_coordinate[i].id) {
                require_coordinate[i].used = 1;
                RhGeom_GetMatrix(require_coordinate[i].data);
                break;
            }
        }
        require_coordinate_index++;
        if (node->child != 0) {
            depth = lRhModel_SetupFloatMotionRecursive(spr->base90 + (node->child & 0x0FFFFFFF), depth, vec);
        }
        if (mode != 3) {
            RhGeomEx_PopMatrix();
        }
        if (node->sibling == 0) {
            return depth;
        }
        arg0 = spr->base90 + (node->sibling & 0x0FFFFFFF);
    }
}

typedef struct FloatKey_00210CF0 {
    u32 time;
    f32 value[3];
} FloatKey_00210CF0;

typedef struct IntKey_00210CF0 {
    u32 time;
    s32 value[3];
} IntKey_00210CF0;

/* One node's position, rotation and scale from a key-framed motion at `time`, interpolated between keys. */
s32 lRhModel_GetInterpolateMotionItem(void *src, f32 time, s32 flags, f32 *position,
                  void *rotation, void *scale, f32 multiplier) {
    extern s32 RhGeom_RotationInterpolate(s32, s32, f32, f32);
    IntKey_00210CF0 *rotationLeft;
    IntKey_00210CF0 *rotationRight;
    void **tracks;
    u32 *counts;

    if (*(u16 *)(SCRATCHPAD_ADDR + 0xE0) & 4) {
        counts = (u32 *)((u8 *)src + 12);
        tracks = src;
    } else {
        counts = (u32 *)((u8 *)src + 8);
        tracks = src;
    }

    {
        FloatKey_00210CF0 *keys = tracks[0];
        if (keys != 0) {
            s32 low;
            s32 high = counts[0];
            flags &= ~1;
            if (high < 3) {
                RhMem_CopyMemory4(position, keys[0].value, 3);
                position[0] *= multiplier;
                position[1] *= multiplier;
                position[2] *= multiplier;
            } else {
                s32 middle = high >> 1;
                FloatKey_00210CF0 *left;
                low = 0;
                while (low < middle) {
                    FloatKey_00210CF0 *key = &keys[middle];
                    if (!(time < (f32)key[1].time)) {
                        low = middle;
                    } else if (time < (f32)key->time) {
                        high = middle;
                    } else {
                        break;
                    }
                    middle = (low + high) >> 1;
                }
                left = &keys[middle];
                if ((u32)(middle + 1) >= counts[0]) {
                    RhMem_CopyMemory4(position, left->value, 3);
                    position[0] *= multiplier;
                    position[1] *= multiplier;
                    position[2] *= multiplier;
                } else {
                    FloatKey_00210CF0 *right = &keys[middle + 1];
                    f32 duration = (f32)(right->time - left->time);
                    f32 leftWeight = ((f32)right->time - time) / duration;
                    f32 rightWeight = (time - (f32)left->time) / duration;
                    position[0] = leftWeight * left->value[0] + rightWeight * right->value[0];
                    position[1] = leftWeight * left->value[1] + rightWeight * right->value[1];
                    position[2] = leftWeight * left->value[2] + rightWeight * right->value[2];
                    position[0] *= multiplier;
                    position[1] *= multiplier;
                    position[2] *= multiplier;
                }
            }
        }
    }
    {
        IntKey_00210CF0 *keys = tracks[1];
        if (keys != 0) {
            IntKey_00210CF0 *key;
            s32 high = counts[1];
            flags &= ~2;
            if (high < 3) {
                RhMem_CopyMemory4(rotation, keys[0].value, 3);
            } else {
                s32 low = 0;
                s32 middle = high >> 1;
                while (low < middle) {
                    key = &keys[middle];
                    if (!(time < (f32)key[1].time)) {
                        low = middle;
                    } else if (time < (f32)key->time) {
                        high = middle;
                    } else {
                        break;
                    }
                    middle = (low + high) >> 1;
                }
                rotationLeft = &keys[middle];
                if ((u32)(middle + 1) >= counts[1]) {
                    RhMem_CopyMemory4(rotation, rotationLeft->value, 3);
                } else {
                    f32 duration;
                    f32 leftWeight;
                    f32 rightWeight;
                    rotationRight = &keys[middle + 1];
                    duration = (f32)(rotationRight->time - rotationLeft->time);
                    leftWeight = ((f32)rotationRight->time - time) / duration;
                    rightWeight = (time - (f32)rotationLeft->time) / duration;
                    ((s32 *)rotation)[0] = RhGeom_RotationInterpolate(rotationLeft->value[0], rotationRight->value[0], leftWeight, rightWeight);
                    ((s32 *)rotation)[1] = RhGeom_RotationInterpolate(rotationLeft->value[1], rotationRight->value[1], leftWeight, rightWeight);
                    ((s32 *)rotation)[2] = RhGeom_RotationInterpolate(rotationLeft->value[2], rotationRight->value[2], leftWeight, rightWeight);
                }
            }
        }
    }
    if (*(u16 *)(SCRATCHPAD_ADDR + 0xE0) & 4) {
        FloatKey_00210CF0 *keys = tracks[2];
        if (keys != 0) {
            FloatKey_00210CF0 *key;
            s32 high = counts[2];
            flags &= ~4;
            if (high < 3) {
                RhMem_CopyMemory4(scale, keys[0].value, 3);
            } else {
                s32 low = 0;
                s32 middle = high >> 1;
                FloatKey_00210CF0 *left;
                while (low < middle) {
                    key = &keys[middle];
                    if (!(time < (f32)key[1].time)) {
                        low = middle;
                    } else if (time < (f32)key->time) {
                        high = middle;
                    } else {
                        break;
                    }
                    middle = (low + high) >> 1;
                }
                left = &keys[middle];
                if ((u32)(middle + 1) >= counts[2]) {
                    RhMem_CopyMemory4(scale, left->value, 3);
                } else {
                    u32 rightTime;
                    u32 leftTime;
                    FloatKey_00210CF0 *right;
                    f32 duration;
                    f32 leftWeight;
                    f32 rightWeight;
                    right = &keys[middle + 1];
                    leftTime = left->time;
                    rightTime = right->time;
                    duration = (f32)(rightTime - leftTime);
                    leftWeight = ((f32)rightTime - time) / duration;
                    rightWeight = (time - (f32)leftTime) / duration;
                    ((f32 *)scale)[0] = leftWeight * left->value[0] + rightWeight * right->value[0];
                    ((f32 *)scale)[1] = leftWeight * left->value[1] + rightWeight * right->value[1];
                    ((f32 *)scale)[2] = leftWeight * left->value[2] + rightWeight * right->value[2];
                }
            }
        }
    }
    return flags;
}

/* Fill the scratchpad header for a pulse-motion walk, then run lRhModel_SetupPulseMotionRecursive with the
   stack on the scratchpad (0x70004000), the real stack pointer kept in gRhModel_dwStack. */

/* Builds a model's node matrices from a per-frame (pulse) motion at `time`. */
s32 lRhModel_SetupPulseMotion(u8 *model, u8 *motion, f32 time) {
    u8 *spr = (u8 *)SCRATCHPAD_ADDR;
    register void **saved;

    model += *(s32 *)(model + 0x10);
    *(u8 **)(spr + 0x90) = model;
    *(s32 *)(spr + 0x94) = **(s32 **)(motion + 8);
    *(f32 *)(spr + 0x98) = time;
    *(s32 *)(spr + 0x9C) = *(u16 *)(motion + 4);
    *(u16 *)(spr + 0xE0) = *(u16 *)(*(u8 **)(motion + 8) + 8);
    saved = &gRhModel_dwStack;
    asm {
        sw sp, 0x0(saved)
        la at, D_70004000
        addiu sp, at, 0x0
    }
    lRhModel_SetupPulseMotionRecursive(model, 0, gRhModel_vecScale);
    {
        register void **back = &gRhModel_dwStack;
        asm {
            lw sp, 0x0(back)
        }
    }
    return 1;
}

typedef f32 Vec4_00211530[4] __attribute__((aligned(16)));

typedef struct {
    Vec4_00211530 v;
} Quad_00211530;

typedef struct {
    f32 v[4];
} Plain4_00211530;

typedef struct {
    u8 pad0[0xC];
    u16 flags;
    u16 idx;
    u8 pad10[0xC];
    u32 child;
    u8 pad20[0xC];
    u32 sibling;
    Quad_00211530 pos;
} Node_00211530;

typedef struct {
    f32 v00[4];
    f32 v10[4];
    f32 v20[4];
    u8 pad30[0x60];
    u8 *base90;
    u8 *tbl94;
    f32 f98;
    s32 cnt9C;
    u8 padA0[0x10];
    u32 flagsB0;
    u8 *ptrB4;
    Plain4_00211530 *outB8;
    f32 fBC;
    u8 padC0[0x20];
    u16 flagsE0;
} Spr_00211530;

typedef struct {
    s32 id;
    s32 used;
    u8 pad8[8];
    u8 data[0x40];
} Slot_00211530;

#define PARENT ((f32 *)arg2)
extern Slot_00211530 require_coordinate[];

/* One node of lRhModel_SetupPulseMotion, then its children and siblings. */
s32 lRhModel_SetupPulseMotionRecursive(void *arg0, s32 depth, void *arg2) {
    extern s32 lRhModel_GetPulseMotionItem(void *, s64, u16, void *, void *, void *, f32);
    Spr_00211530 *spr = (Spr_00211530 *)SCRATCHPAD_ADDR;
    u8 buf[32];
    f32 *vec = (f32 *)(((s32)buf + 0xF) & ~0xF);
    u32 flags;
    s32 mode;
    u8 *p;
    f32 f;
    f32 max;
    u32 i;

    for (;;) {
        Node_00211530 *node = arg0;

        RhMem_CopyMemory16(vec, arg2, 1);
        flags = node->flags;
        RhMem_CopyMemory16(spr, node, 3);
        if (depth < spr->cnt9C) {
            p = spr->tbl94;
            if (spr->flagsE0 & 4) {
                p += depth * 0x18;
            } else {
                p += depth * 0x10;
            }
            flags = lRhModel_GetPulseMotionItem(p, func_001A22C0(spr->f98), node->flags, spr->v20, spr->v10, spr,
                                  depth == 0 ? 1.0f : spr->fBC);
            if (depth == 0 && (spr->flagsE0 & 4)) {
                RhMem_CopyMemory4(spr, node, 3);
            }
        }
        if (depth == 0) {
            if (spr->outB8 != NULL) {
                *spr->outB8 = *(Plain4_00211530 *)spr->v20;
            }
        }
        mode = flags & 3;
        depth++;
        if (mode != 3) {
            spr->v20[0] *= PARENT[0];
            spr->v20[1] *= PARENT[1];
            spr->v20[2] *= PARENT[2];
            RhGeomEx_PushMatrix();
            RhGeomEx_ScaleRotXYZTransMatrix(NULL, (flags & 2) ? NULL : spr->v10, (flags & 1) ? NULL : spr->v20);
        }
        if (!(flags & 4)) {
            vec[0] *= spr->v00[0];
            vec[1] *= spr->v00[1];
            vec[2] *= spr->v00[2];
        }
        if (node->idx != 0) {
            p = spr->ptrB4 + node->idx * 0x10;
            RhGeomEx_GetMatrix(p);
            RhGeom_ScaleMatrix(p, vec);
        }
        if (!(node->flags & 0x8000)) {
            f = node->pos.v[3];
            max = vec[0];
            if (max < vec[1]) {
                max = vec[1];
            }
            if (max < vec[2]) {
                max = vec[2];
            }
            f = f * (spr->fBC * max);
            *(Quad_00211530 *)spr->v20 = node->pos;
            spr->v20[3] = 1.0f;
            RhGeomEx_PushMatrix();
            RhGeom_ScaleMatrix(NULL, vec);
            spr->flagsB0 |= RhView_CheckViewVolume(spr->v20, f);
            RhGeomEx_PopMatrix();
        }
        for (i = 0; i < require_coordinate_no; i++) {
            if (require_coordinate_index == require_coordinate[i].id) {
                require_coordinate[i].used = 1;
                RhGeom_GetMatrix(require_coordinate[i].data);
                break;
            }
        }
        require_coordinate_index++;
        if (node->child != 0) {
            depth = lRhModel_SetupPulseMotionRecursive(spr->base90 + (node->child & 0x0FFFFFFF), depth, vec);
        }
        if (mode != 3) {
            RhGeomEx_PopMatrix();
        }
        if (node->sibling == 0) {
            return depth;
        }
        arg0 = spr->base90 + (node->sibling & 0x0FFFFFFF);
    }
}

typedef struct FloatKey_002118F0 {
    u32 time;
    f32 value[3];
} FloatKey_002118F0;

typedef struct IntKey_002118F0 {
    u32 time;
    s32 value[3];
} IntKey_002118F0;

typedef struct Tracks_002118F0 {
    FloatKey_002118F0 *position;
    IntKey_002118F0 *rotation;
    FloatKey_002118F0 *scale;
} Tracks_002118F0;

/* One node's position, rotation and scale from a per-frame motion at frame `time`. */
s32 lRhModel_GetPulseMotionItem(void *src, u32 time, s32 flags, f32 *position,
                  s32 *rotation, f32 *scale, f32 factor) {
    extern s32 RhGeom_RotationInterpolate(s32, s32, f32, f32);
    extern s32 Ta_Eff_Hand_Fusion();
    IntKey_002118F0 *rotation_next;
    Tracks_002118F0 *tracks;
    u32 *counts;
    IntKey_002118F0 *rotation_previous;
    FloatKey_002118F0 *scale_keys;
    s32 low;
    FloatKey_002118F0 *position_keys;
    s32 high;
    s32 middle;
    FloatKey_002118F0 *previous;
    FloatKey_002118F0 *next;

    if (*(u16 *)(SCRATCHPAD_ADDR + 0xE0) & 4) {
        counts = (u32 *)((u8 *)src + 12);
        tracks = src;
    } else {
        counts = (u32 *)((u8 *)src + 8);
        tracks = src;
    }
 
    position_keys = tracks->position;
    if (position_keys != NULL) {
        high = counts[0];
        flags &= ~1;
        if (high < 3) {
            RhMem_CopyMemory4(position, position_keys[0].value, 3);
            position[0] *= factor;
            position[1] *= factor;
            position[2] *= factor;
        } else {
            f32 duration;
            f32 before;
            f32 after;

            low = 0;
            middle = high >> 1;
            while (low < middle) {
                if (time >= position_keys[middle + 1].time) {
                    low = middle;
                } else if (time < position_keys[middle].time) {
                    high = middle;
                } else {
                    break;
                }
                middle = (low + high) >> 1;
            }
            previous = &position_keys[middle];
            if (time == previous->time || (u32)(middle + 1) >= (u32)counts[0]) {
                RhMem_CopyMemory4(position, previous->value, 3);
            } else {
                next = &position_keys[middle + 1];
                duration = (f32)(next->time - previous->time);
                before = (f32)(next->time - time);
                after = (f32)(time - previous->time);
                position[0] = (before * previous->value[0] + after * next->value[0]) / duration;
                position[1] = (before * previous->value[1] + after * next->value[1]) / duration;
                position[2] = (before * previous->value[2] + after * next->value[2]) / duration;
            }
            position[0] *= factor;
            position[1] *= factor;
            position[2] *= factor;
        }
    }

    if (tracks->rotation != NULL) {
        IntKey_002118F0 *keys = tracks->rotation;
        high = counts[1];
        flags &= ~2;
        if (high < 3) {
            RhMem_CopyMemory4(rotation, keys[0].value, 3);
        } else {
            f32 duration;
            f32 before;
            f32 after;

            low = 0;
            middle = high >> 1;
            while (low < middle) {
                if (time >= keys[middle + 1].time) {
                    low = middle;
                } else if (time < keys[middle].time) {
                    high = middle;
                } else {
                    break;
                }
                middle = (low + high) >> 1;
            }
            rotation_previous = &keys[middle];
            low = rotation_previous->time;
            if (time == (u32)low || (u32)(middle + 1) >= (u32)counts[1]) {
                RhMem_CopyMemory4(rotation, rotation_previous->value, 3);
            } else {
                rotation_next = &keys[middle + 1];
                high = rotation_next->time;
                duration = (f32)((u32)high - (u32)low);
                before = (f32)((u32)high - time) / duration;
                after = (f32)(time - (u32)low) / duration;
                rotation[0] = RhGeom_RotationInterpolate(rotation_previous->value[0], rotation_next->value[0], before, after);
                rotation[1] = RhGeom_RotationInterpolate(rotation_previous->value[1], rotation_next->value[1], before, after);
                rotation[2] = RhGeom_RotationInterpolate(rotation_previous->value[2], rotation_next->value[2], before, after);
            }
        }
    }

    if (*(u16 *)(SCRATCHPAD_ADDR + 0xE0) & 4) {
        if (tracks->scale != NULL) {
            scale_keys = tracks->scale;
            high = counts[2];
            flags &= ~4;
            if (high < 3) {
                RhMem_CopyMemory4(scale, scale_keys[0].value, 3);
            } else {
                u32 rightTime;
                u32 leftTime;
                f32 duration;
                f32 before;
                f32 after;

                low = 0;
                middle = high >> 1;
                while (low < middle) {
                    if (time >= scale_keys[middle + 1].time) {
                        low = middle;
                    } else if (time < scale_keys[middle].time) {
                        high = middle;
                    } else {
                        break;
                    }
                    middle = (low + high) >> 1;
                }
                previous = &scale_keys[middle];
                leftTime = previous->time;
                if (time == leftTime || (u32)(middle + 1) >= (u32)counts[2]) {
                    RhMem_CopyMemory4(scale, previous->value, 3);
                } else {
                    next = &scale_keys[middle + 1];
                    rightTime = next->time;
                    duration = (f32)(rightTime - leftTime);
                    before = (f32)(rightTime - time) / duration;
                    after = (f32)(time - leftTime) / duration;
                    scale[0] = before * previous->value[0] + after * next->value[0];
                    scale[1] = before * previous->value[1] + after * next->value[1];
                    scale[2] = before * previous->value[2] + after * next->value[2];
                }
            }
        }
    }
    return flags;
}

/* Points a model's texture packets at its loaded textures (`bank` picks the set). */
void lRhModel_SetupTexture(void *model, void *textures0, void *textures1, s32 bank) {
    u8 *spA0;
    u8 *spB0;
    u8 *spC0;
    s32 spDC;
    s32 var_s7;
    u8 *temp_fp;
    u8 *temp_a1;
    s32 temp_a2;
    s32 temp_a0;
    s32 temp_v1;

    extern s32 RhMem_CopyMemory16();

    temp_a1 = (u8 *)model + 0x10;
    spDC = bank;
    if (*(s32 *)((u8 *)model + 0x3C) != 0) {
        s32 *var_s0;
        s32 *var_s1;
        s32 temp_s2;
        s32 i;
        s32 *var_s4;
        s32 temp_a1_3;
        s32 temp_a0_2;
        s32 temp_v0;

        temp_a2 = *(s32 *)(temp_a1 + 0x48);
        temp_fp = (u8 *)model + *(s32 *)(temp_a1 + 0x28);
        if (temp_a2 == 0 || *(s32 *)(temp_a1 + 0x4C) == 0) {
            spA0 = NULL;
        } else {
            spA0 = (u8 *)model + temp_a2;
        }
        spB0 = temp_fp + 0x10;
        var_s7 = 0;
        var_s1 = (s32 *)(temp_fp + *(s32 *)(temp_fp + 4));
        spC0 = spA0 + (spDC * 4);
        while (var_s7 < *(s32 *)temp_fp) {
            if (spA0 != NULL && (temp_a0 = *(s32 *)(spA0 + 0x184)) >= 0 && spDC >= 0 && var_s7 == temp_a0 && (temp_v1 = *(s32 *)(spC0 + 0x84)) >= 0 && temp_v1 < *(s32 *)temp_fp) {
                var_s0 = (s32 *)(temp_fp + 0x10);
                var_s0 = (s32 *)((u8 *)var_s0 + temp_v1 * 0x10);
            } else {
                var_s0 = (s32 *)spB0;
            }
            temp_s2 = var_s1[0];
            var_s4 = (s32 *)(temp_fp + var_s1[1]);
            for (i = 0; i < temp_s2; i++) {
                temp_a1_3 = *var_s4;
                temp_a0_2 = temp_a1_3 & 0xF0000000;
                switch (temp_a0_2) {
                case 0x20000000:
                    temp_v0 = *var_s0 + 0x10;
                    RhMem_CopyMemory16((u8 *)textures0 + (temp_a1_3 & 0x0FFFFFFF), (u32)temp_v0 + 0x20, 2);
                    break;
                case 0x40000000:
                    temp_v0 = *var_s0 + 0x10;
                    RhMem_CopyMemory16((u8 *)textures1 + (temp_a1_3 & 0x0FFFFFFF), (u32)temp_v0 + 0x20, 2);
                    break;
                }
                var_s4 += 1;
            }
            var_s1 += 2;
            var_s7 += 1;
            spB0 += 0x10;
        }
    }
}

typedef struct Header_00212170 {
    u8 padding[0x58];
    s32 offset;
} Header_00212170;

typedef struct State_00212170 {
    u8 padding[0x4C];
    s32 enabled;
} State_00212170;

/* Clears a word. */
static inline void clear_00212170(u32 *target) {
    target[0] = 0x10000000;
    target[1] = 0;
    target[2] = 0;
    target[3] = 0;
}
#pragma conditional_move off

/* Sets up a model's optional parts (shown by `mask`). */
s32 lRhModel_SetupOptionObject(void *arg0, void *arg1, void *arg2, s32 arg3, s32 mask) {
    s32 ret;
    u8 *base;
    s32 index;
    s32 *list;
    s32 *table;
    s32 value;
    s32 offset;
    u32 kind;
    u32 *target;
    State_00212170 *state;

    offset = ((Header_00212170 *)arg0)->offset;
    state = (State_00212170 *)((u8 *)arg0 + 0x10);
    if (offset != 0) {
        if (state->enabled == 0) {
            return ret;
        }
        base = (u8 *)arg0 + offset;
        index = 0;
        if (arg3 != 0) {
            mask = *(u32 *)(base + 0x80);
        }
        table = (s32 *)base;
        do {
            if (!(mask & (1U << index))) {
                offset = *table;
                list = (s32 *)(base + offset);
                if (offset != 0) {
                    for (; (value = *list) != 0; list++) {
                        kind = value & 0xF0000000;
                        switch (kind) {
                        case 0x20000000:
                            target = (u32 *)((u8 *)arg1 + (value & 0x0FFFFFFF));
                            break;
                        case 0x40000000:
                            if (arg2 == 0) {
                                continue;
                            }
                            target = (u32 *)((u8 *)arg2 + (value & 0x0FFFFFFF));
                            break;
                        default:
                            continue;
                        }
                        clear_00212170(target);
                    }
                }
            }
            index++;
            table++;
        } while (index < 32);
    }
    return ret;
}

typedef struct Flags_00212250 {
    u8 reserved0 : 7;
    u8 scale : 1;
    u8 add : 1;
    u8 replace : 1;
    u8 reserved1 : 6;
} Flags_00212250;
#pragma conditional_move reset
#pragma optimization_level 0
#pragma optimization_level 2
#pragma schedule on

/* Scales a model's material colours by its light intensity. */
void lRhModel_SetMaterialIntensity(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3, u8 *arg4) {
    if (arg0 < arg1) {
    do {
        switch (*(u32 *)arg0 & 0xF0000000) {
        case 0x10000000:
            if ((*(s64 *)(arg0 + 0) == 0x10000003) && (*(s64 *)(arg0 + 8) == 0x6C03003C10000000ULL)) {
                if (((Flags_00212250 *)(arg4 + 4))->replace) {
                    *(f32 *)(arg0 + 0x10) = (f32) *(f32 *)(arg4 + 0x3C);
                    *(f32 *)(arg0 + 0x14) = (f32) *(f32 *)(arg4 + 0x40);
                    *(f32 *)(arg0 + 0x18) = (f32) *(f32 *)(arg4 + 0x44);
                    if (*(f32 *)(arg0 + 0x20) != 0.0f) {
                        *(f32 *)(arg0 + 0x20) = (f32) *(f32 *)(arg4 + 0x3C);
                        *(f32 *)(arg0 + 0x24) = (f32) *(f32 *)(arg4 + 0x40);
                        *(f32 *)(arg0 + 0x28) = (f32) *(f32 *)(arg4 + 0x44);
                    }
                    *(f32 *)(arg0 + 0x2C) = (f32) *(f32 *)(arg4 + 0x48);
                    *(f32 *)(arg0 + 0x30) = (f32) *(f32 *)(arg4 + 0x3C);
                    *(f32 *)(arg0 + 0x34) = (f32) *(f32 *)(arg4 + 0x40);
                    *(f32 *)(arg0 + 0x38) = (f32) *(f32 *)(arg4 + 0x44);
                }
                if ((*(u8 *)(arg4 + 5) & 1)) {
                    *(f32 *)(arg0 + 0x10) += *(f32 *)(arg4 + 0x3C);
                    *(f32 *)(arg0 + 0x14) += *(f32 *)(arg4 + 0x40);
                    *(f32 *)(arg0 + 0x18) += *(f32 *)(arg4 + 0x44);
                    if (*(f32 *)(arg0 + 0x20) != 0.0f) {
                        *(f32 *)(arg0 + 0x20) += *(f32 *)(arg4 + 0x3C);
                        *(f32 *)(arg0 + 0x24) += *(f32 *)(arg4 + 0x40);
                        *(f32 *)(arg0 + 0x28) += *(f32 *)(arg4 + 0x44);
                    }
                    *(f32 *)(arg0 + 0x2C) += *(f32 *)(arg4 + 0x48);
                    *(f32 *)(arg0 + 0x30) += *(f32 *)(arg4 + 0x3C);
                    *(f32 *)(arg0 + 0x34) += *(f32 *)(arg4 + 0x40);
                    *(f32 *)(arg0 + 0x38) += *(f32 *)(arg4 + 0x44);
                    if (*(f32 *)(arg0 + 0x10) < 0.0f) {
                        *(f32 *)(arg0 + 0x10) = 0.0f;
                    }
                    if (*(f32 *)(arg0 + 0x14) < 0.0f) {
                        *(f32 *)(arg0 + 0x14) = 0.0f;
                    }
                    if (*(f32 *)(arg0 + 0x18) < 0.0f) {
                        *(f32 *)(arg0 + 0x18) = 0.0f;
                    }
                    if (*(f32 *)(arg0 + 0x20) < 0.0f) {
                        *(f32 *)(arg0 + 0x20) = 0.0f;
                    }
                    if (*(f32 *)(arg0 + 0x24) < 0.0f) {
                        *(f32 *)(arg0 + 0x24) = 0.0f;
                    }
                    if (*(f32 *)(arg0 + 0x28) < 0.0f) {
                        *(f32 *)(arg0 + 0x28) = 0.0f;
                    }
                    if (*(f32 *)(arg0 + 0x2C) < 0.0f) {
                        *(f32 *)(arg0 + 0x2C) = 0.0f;
                    }
                    if (*(f32 *)(arg0 + 0x30) < 0.0f) {
                        *(f32 *)(arg0 + 0x30) = 0.0f;
                    }
                    if (*(f32 *)(arg0 + 0x34) < 0.0f) {
                        *(f32 *)(arg0 + 0x34) = 0.0f;
                    }
                    if (*(f32 *)(arg0 + 0x38) < 0.0f) {
                        *(f32 *)(arg0 + 0x38) = 0.0f;
                    }
                    if (!(*(f32 *)(arg0 + 0x10) <= 255.0f)) {
                        *(f32 *)(arg0 + 0x10) = 255.0f;
                    }
                    if (!(*(f32 *)(arg0 + 0x14) <= 255.0f)) {
                        *(f32 *)(arg0 + 0x14) = 255.0f;
                    }
                    if (!(*(f32 *)(arg0 + 0x18) <= 255.0f)) {
                        *(f32 *)(arg0 + 0x18) = 255.0f;
                    }
                    if (!(*(f32 *)(arg0 + 0x20) <= 255.0f)) {
                        *(f32 *)(arg0 + 0x20) = 255.0f;
                    }
                    if (!(*(f32 *)(arg0 + 0x24) <= 255.0f)) {
                        *(f32 *)(arg0 + 0x24) = 255.0f;
                    }
                    if (!(*(f32 *)(arg0 + 0x28) <= 255.0f)) {
                        *(f32 *)(arg0 + 0x28) = 255.0f;
                    }
                    if (!(*(f32 *)(arg0 + 0x2C) <= 255.0f)) {
                        *(f32 *)(arg0 + 0x2C) = 255.0f;
                    }
                    if (!(*(f32 *)(arg0 + 0x30) <= 255.0f)) {
                        *(f32 *)(arg0 + 0x30) = 255.0f;
                    }
                    if (!(*(f32 *)(arg0 + 0x34) <= 255.0f)) {
                        *(f32 *)(arg0 + 0x34) = 255.0f;
                    }
                    if (!(*(f32 *)(arg0 + 0x38) <= 255.0f)) {
                        *(f32 *)(arg0 + 0x38) = 255.0f;
                    }
                }
                if ((((Flags_00212250 *)(arg4 + 4))->scale) && (*(f32 *)(arg0 + 0x20) != 0.0f)) {
                    *(f32 *)(arg0 + 0x10) = (f32) (*(f32 *)(arg0 + 0x10) * *(f32 *)(arg4 + 0x34));
                    *(f32 *)(arg0 + 0x14) = (f32) (*(f32 *)(arg0 + 0x14) * *(f32 *)(arg4 + 0x34));
                    *(f32 *)(arg0 + 0x18) = (f32) (*(f32 *)(arg0 + 0x18) * *(f32 *)(arg4 + 0x34));
                    *(f32 *)(arg0 + 0x20) = (f32) (*(f32 *)(arg0 + 0x20) * *(f32 *)(arg4 + 0x30));
                    *(f32 *)(arg0 + 0x24) = (f32) (*(f32 *)(arg0 + 0x24) * *(f32 *)(arg4 + 0x30));
                    *(f32 *)(arg0 + 0x28) = (f32) (*(f32 *)(arg0 + 0x28) * *(f32 *)(arg4 + 0x30));
                    *(f32 *)(arg0 + 0x30) = (f32) (*(f32 *)(arg0 + 0x30) * *(f32 *)(arg4 + 0x38));
                    *(f32 *)(arg0 + 0x34) = (f32) (*(f32 *)(arg0 + 0x34) * *(f32 *)(arg4 + 0x38));
                    *(f32 *)(arg0 + 0x38) = (f32) (*(f32 *)(arg0 + 0x38) * *(f32 *)(arg4 + 0x38));
                }
            }
            arg0 = arg0 + *(u16 *)arg0 * 0x10 + 0x10;
            break;
        case 0x20000000:
            arg0 = *(u8 **)(arg0 + 4);
            break;
        case 0x30000000:
            arg0 += 0x10;
            break;
        default:
            return;
        }
    } while (arg0 < arg1);
    }
    if (arg2 != NULL) {
        if (arg2 < arg3) {
        do {
            switch (*(u32 *)arg2 & 0xF0000000) {
            case 0x10000000:
                if ((*(s64 *)(arg2 + 0) == 0x10000003) && (*(s64 *)(arg2 + 8) == 0x6C03003C10000000ULL)) {
                    if (((Flags_00212250 *)(arg4 + 4))->replace) {
                        *(f32 *)(arg2 + 0x10) = (f32) *(f32 *)(arg4 + 0x3C);
                        *(f32 *)(arg2 + 0x14) = (f32) *(f32 *)(arg4 + 0x40);
                        *(f32 *)(arg2 + 0x18) = (f32) *(f32 *)(arg4 + 0x44);
                        if (*(f32 *)(arg2 + 0x20) != 0.0f) {
                            *(f32 *)(arg2 + 0x20) = (f32) *(f32 *)(arg4 + 0x3C);
                            *(f32 *)(arg2 + 0x24) = (f32) *(f32 *)(arg4 + 0x40);
                            *(f32 *)(arg2 + 0x28) = (f32) *(f32 *)(arg4 + 0x44);
                        }
                        *(f32 *)(arg2 + 0x2C) = (f32) *(f32 *)(arg4 + 0x48);
                        *(f32 *)(arg2 + 0x30) = (f32) *(f32 *)(arg4 + 0x3C);
                        *(f32 *)(arg2 + 0x34) = (f32) *(f32 *)(arg4 + 0x40);
                        *(f32 *)(arg2 + 0x38) = (f32) *(f32 *)(arg4 + 0x44);
                    }
                    if ((*(u8 *)(arg4 + 5) & 1)) {
                        *(f32 *)(arg2 + 0x10) += *(f32 *)(arg4 + 0x3C);
                        *(f32 *)(arg2 + 0x14) += *(f32 *)(arg4 + 0x40);
                        *(f32 *)(arg2 + 0x18) += *(f32 *)(arg4 + 0x44);
                        if (*(f32 *)(arg2 + 0x20) != 0.0f) {
                            *(f32 *)(arg2 + 0x20) += *(f32 *)(arg4 + 0x3C);
                            *(f32 *)(arg2 + 0x24) += *(f32 *)(arg4 + 0x40);
                            *(f32 *)(arg2 + 0x28) += *(f32 *)(arg4 + 0x44);
                        }
                        *(f32 *)(arg2 + 0x2C) += *(f32 *)(arg4 + 0x48);
                        *(f32 *)(arg2 + 0x30) += *(f32 *)(arg4 + 0x3C);
                        *(f32 *)(arg2 + 0x34) += *(f32 *)(arg4 + 0x40);
                        *(f32 *)(arg2 + 0x38) += *(f32 *)(arg4 + 0x44);
                        if (*(f32 *)(arg2 + 0x10) < 0.0f) {
                            *(f32 *)(arg2 + 0x10) = 0.0f;
                        }
                        if (*(f32 *)(arg2 + 0x14) < 0.0f) {
                            *(f32 *)(arg2 + 0x14) = 0.0f;
                        }
                        if (*(f32 *)(arg2 + 0x18) < 0.0f) {
                            *(f32 *)(arg2 + 0x18) = 0.0f;
                        }
                        if (*(f32 *)(arg2 + 0x20) < 0.0f) {
                            *(f32 *)(arg2 + 0x20) = 0.0f;
                        }
                        if (*(f32 *)(arg2 + 0x24) < 0.0f) {
                            *(f32 *)(arg2 + 0x24) = 0.0f;
                        }
                        if (*(f32 *)(arg2 + 0x28) < 0.0f) {
                            *(f32 *)(arg2 + 0x28) = 0.0f;
                        }
                        if (*(f32 *)(arg2 + 0x2C) < 0.0f) {
                            *(f32 *)(arg2 + 0x2C) = 0.0f;
                        }
                        if (*(f32 *)(arg2 + 0x30) < 0.0f) {
                            *(f32 *)(arg2 + 0x30) = 0.0f;
                        }
                        if (*(f32 *)(arg2 + 0x34) < 0.0f) {
                            *(f32 *)(arg2 + 0x34) = 0.0f;
                        }
                        if (*(f32 *)(arg2 + 0x38) < 0.0f) {
                            *(f32 *)(arg2 + 0x38) = 0.0f;
                        }
                        if (!(*(f32 *)(arg2 + 0x10) <= 255.0f)) {
                            *(f32 *)(arg2 + 0x10) = 255.0f;
                        }
                        if (!(*(f32 *)(arg2 + 0x14) <= 255.0f)) {
                            *(f32 *)(arg2 + 0x14) = 255.0f;
                        }
                        if (!(*(f32 *)(arg2 + 0x18) <= 255.0f)) {
                            *(f32 *)(arg2 + 0x18) = 255.0f;
                        }
                        if (!(*(f32 *)(arg2 + 0x20) <= 255.0f)) {
                            *(f32 *)(arg2 + 0x20) = 255.0f;
                        }
                        if (!(*(f32 *)(arg2 + 0x24) <= 255.0f)) {
                            *(f32 *)(arg2 + 0x24) = 255.0f;
                        }
                        if (!(*(f32 *)(arg2 + 0x28) <= 255.0f)) {
                            *(f32 *)(arg2 + 0x28) = 255.0f;
                        }
                        if (!(*(f32 *)(arg2 + 0x2C) <= 255.0f)) {
                            *(f32 *)(arg2 + 0x2C) = 255.0f;
                        }
                        if (!(*(f32 *)(arg2 + 0x30) <= 255.0f)) {
                            *(f32 *)(arg2 + 0x30) = 255.0f;
                        }
                        if (!(*(f32 *)(arg2 + 0x34) <= 255.0f)) {
                            *(f32 *)(arg2 + 0x34) = 255.0f;
                        }
                        if (!(*(f32 *)(arg2 + 0x38) <= 255.0f)) {
                            *(f32 *)(arg2 + 0x38) = 255.0f;
                        }
                    }
                    if ((((Flags_00212250 *)(arg4 + 4))->scale) && (*(f32 *)(arg2 + 0x20) != 0.0f)) {
                        *(f32 *)(arg2 + 0x10) = (f32) (*(f32 *)(arg2 + 0x10) * *(f32 *)(arg4 + 0x34));
                        *(f32 *)(arg2 + 0x14) = (f32) (*(f32 *)(arg2 + 0x14) * *(f32 *)(arg4 + 0x34));
                        *(f32 *)(arg2 + 0x18) = (f32) (*(f32 *)(arg2 + 0x18) * *(f32 *)(arg4 + 0x34));
                        *(f32 *)(arg2 + 0x20) = (f32) (*(f32 *)(arg2 + 0x20) * *(f32 *)(arg4 + 0x30));
                        *(f32 *)(arg2 + 0x24) = (f32) (*(f32 *)(arg2 + 0x24) * *(f32 *)(arg4 + 0x30));
                        *(f32 *)(arg2 + 0x28) = (f32) (*(f32 *)(arg2 + 0x28) * *(f32 *)(arg4 + 0x30));
                        *(f32 *)(arg2 + 0x30) = (f32) (*(f32 *)(arg2 + 0x30) * *(f32 *)(arg4 + 0x38));
                        *(f32 *)(arg2 + 0x34) = (f32) (*(f32 *)(arg2 + 0x34) * *(f32 *)(arg4 + 0x38));
                        *(f32 *)(arg2 + 0x38) = (f32) (*(f32 *)(arg2 + 0x38) * *(f32 *)(arg4 + 0x38));
                    }
                }
                arg2 = arg2 + *(u16 *)arg2 * 0x10 + 0x10;
                break;
            case 0x20000000:
                arg2 = *(u8 **)(arg2 + 4);
                break;
            case 0x30000000:
                arg2 += 0x10;
                break;
            default:
                return;
            }
        } while (arg2 < arg3);
        }
    }
}
#pragma schedule reset
#pragma optimization_level reset
#pragma optimization_level reset

/* Turns `count` local-to-view matrices into local-to-screen ones. */
void lRhModel_ChangeL2VtoL2S(s32 matrices, s32 viewScreen, s32 count) {
    s32 i;
    s32 var_s1;

    i = 0;
    if (i < count) {
        var_s1 = matrices;
        do {
            RhGeom_MulMatrixRev(var_s1, viewScreen);
            i += 1;
            var_s1 += 0x70;
        } while (i < count);
    }
}

/* Empties the table of booked node coordinates. */
void GetAnyCoordinateInit(void) {
    extern u32 require_coordinate_no;

    require_coordinate_no = 0;
}

/* Books node coordinate `id` to be recorded when its model next draws. */
s32 BookingGetAnyCoordinate(s32 id) {
    if (require_coordinate_no >= 0x100) {
        return 0;
    }
    require_coordinate[require_coordinate_no].id = id;
    require_coordinate[require_coordinate_no].used = -1;
    require_coordinate_no++;
    return 1;
}

/* The recorded matrix of booked node coordinate `id` into `out`. Returns 0 if not recorded. */
s32 GetAnyCoordinate(s32 id, void *out) {
    u32 i;
    s32 *state;
    s32 offset;
    void *payload;
    Slot_00211530 *record;
    u8 temporary[0x40];

    if ((require_coordinate_no == 0) || (id <= 0) || (out == NULL)) {
        return 0;
    }
    record = require_coordinate;
    for (i = 0; i < require_coordinate_no; record++, i++) {
        if (id == record->id) {
            offset = i * 0x50;
            state = (s32 *)(D_0032A784 + offset);
            if (*state == -1) {
                return 0;
            }
            if (*state == 1) {
                *state = 0;
                func_00198790(temporary, InvertView, 0x40);
                payload = (u8 *)require_coordinate + offset + 0x10;
                RhGeom_MulMatrix((s32)temporary, payload);
                func_00198790(payload, temporary, 0x40);
            }
            if (*state == 0) {
                func_00198790(out, (u8 *)require_coordinate + offset + 0x10, 0x40);
            }
            break;
        }
    }
    if (i == require_coordinate_no) {
        return 0;
    }
    return 1;
}

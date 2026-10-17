#include "common.h"

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
        if (*(s32 *)0x700000B0 & 4) {
            flags |= 0x20;
        }
        *(void **)0x700000C4 = RhVu1Mac_ChangeDrawMethod(*(void **)0x700000C0, flags);
    } else {
        *(void **)0x700000C4 = RhVu1Mac_ReserveChangeDrawMethod(*(void **)0x700000C0);
    }
    lRhModel_DrawCommonPart(obj);
    if (!(*(s32 *)0x700000B0 & 1)) {
        return *(void **)0x700000C0;
    }
    if (*(s32 *)(*(u8 **)0x700000DC + 0x1C) > 0) {
        if (obj->flag5_3) {
            result = *(s32 *)0x700000D0;
        } else {
            RhMem_CopyMemory16(gRhModel_mlsmSwapArea, (void *)0x70000000, 0x11);
            result = RhBase_SetZBufferMode((s32)RhModelCpu_DrawAlpha(
                (u8 *)RhBase_SetZBufferMode(*(s32 *)0x700000D0, 0),
                *(s32 *)0x700000CC,
                *(s32 *)(*(u8 **)0x700000DC + 0x1C),
                obj->flag4_1), 1);
            RhMem_CopyMemory16((void *)0x70000000, gRhModel_mlsmSwapArea, 0x11);
        }
        *(s32 *)0x700000D4 = result;
    } else {
        *(s32 *)0x700000D4 = *(s32 *)0x700000C8;
    }
    if (*(s32 *)0x700000B0 & 4) {
        flags |= 0x20;
    } else if (noClip == 0) {
        RhView_GetViewScreenMatrix((void *)0x70000000);
        lRhModel_ChangeL2VtoL2S(*(s32 *)0x700000B4 + 0x10, 0x70000000,
                     ((*(s32 *)0x700000D8 - 0x10) >> 4) / 7);
    }
    if (*(void **)0x700000B4 == (void *)0x700000F0) {
        RhMem_CopyMemory16(*(u8 **)0x700000C4 + 0x10, (void *)0x70000100,
                     (*(s32 *)0x700000D8 - 0x10) >> 4);
    }
    if (obj->flag4_2) {
        RhVu1Mac_ChangeDrawMethod(*(void **)0x700000C0, flags);
    }
    return *(void **)0x700000D4;
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
    *(void **)0x700000C4 = RhVu1Mac_ChangeDrawMethod(*(void **)0x700000C0, mode);
    RhView_GetViewScreenMatrix((void *)0x70000000);
    RhGeomEx_SetMatrixForStraightLight((void *)0x70000000);
    lRhModel_DrawCommonPart(part);
    if (*(u8 **)0x700000B4 == (u8 *)0x700000F0) {
        RhMem_CopyMemory16(*(u8 **)0x700000C4 + 0x10, (void *)0x70000100, (*(s32 *)0x700000D8 - 0x10) >> 4);
    }
    *(void **)0x700000D4 = *(void **)0x700000C8;
    return *(void **)0x700000D4;
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

    if ((*(s32 *)0x700000D8 + ((*(Data_0020FAF0 **)0x700000DC)->value58 << 8)) > 0x3F10) {
        *(u8 **)0x700000B4 = *(u8 **)0x700000C4;
    } else {
        *(u8 **)0x700000B4 = (u8 *)0x700000F0;
    }

    **(__int128 **)0x700000C4 = *(__int128 *)(arg->data + (*(Data_0020FAF0 **)0x700000DC)->offset8);
    RhMem_CopyMemory16(*(u8 **)0x700000C4 + *(s32 *)0x700000D8,
                 arg->data + (*(Data_0020FAF0 **)0x700000DC)->offset8 + *(s32 *)0x700000D8,
                 ((*(Data_0020FAF0 **)0x700000DC)->sizeC - *(s32 *)0x700000D8) >> 4);
    lRhModel_DynamicAddressBind(arg->data, *(u8 **)0x700000C4, *(u8 **)0x700000C4, 0);
    *(u8 **)0x700000C8 = *(u8 **)0x700000C4 + (*(Data_0020FAF0 **)0x700000DC)->sizeC;

    if ((*(Data_0020FAF0 **)0x700000DC)->size1C > 0) {
        if (arg->flags5.bit3) {
            *(u8 **)0x700000CC = (u8 *)RhBase_SetZBufferMode((s32)*(u8 **)0x700000C8, 0);
        } else {
            **(s32 **)0x700000C8 = 0x20000000;
            (*(s32 **)0x700000C8)[1] = (s32)(*(u8 **)0x700000C8 + (*(Data_0020FAF0 **)0x700000DC)->size1C + 0x10);
            (*(s32 **)0x700000C8)[2] = 0;
            (*(s32 **)0x700000C8)[3] = 0;
            *(u8 **)0x700000CC = *(u8 **)0x700000C8 + 0x10;
        }
        RhMem_CopyMemory16(*(u8 **)0x700000CC,
                     arg->data + (*(Data_0020FAF0 **)0x700000DC)->offset18,
                     (*(Data_0020FAF0 **)0x700000DC)->size1C >> 4);
        lRhModel_DynamicAddressBind(arg->data, *(u8 **)0x700000C4, *(u8 **)0x700000CC, 1);
        *(u8 **)0x700000D0 = *(u8 **)0x700000CC + (*(Data_0020FAF0 **)0x700000DC)->size1C;
        if (arg->flags5.bit3) {
            *(u8 **)0x700000D0 = (u8 *)RhBase_SetZBufferMode((s32)*(u8 **)0x700000D0, 1);
        }
    } else {
        *(u8 **)0x700000CC = NULL;
        *(u8 **)0x700000D0 = NULL;
    }

    if (arg->flags4.bit6) {
        value24 = arg->value24;
    } else {
        value24 = -1;
    }
    lRhModel_SetupTexture(arg->data, *(u8 **)0x700000C4, *(u8 **)0x700000CC, value24);
    lRhModel_SetupOptionObject(arg->data, *(u8 **)0x700000C4, *(u8 **)0x700000CC, !arg->flags4.bit5, arg->value20);
    if (arg->flags4.bit7 || arg->flags5.bit0 || arg->flags5.bit1) {
        lRhModel_SetMaterialIntensity(*(u8 **)0x700000C4,
                     *(u8 **)0x700000C4 + (*(Data_0020FAF0 **)0x700000DC)->sizeC,
                     *(u8 **)0x700000CC,
                     *(u8 **)0x700000CC + (*(Data_0020FAF0 **)0x700000DC)->size1C,
                     arg);
    }
    *(s32 *)0x700000B8 = arg->value28;
    if (!arg->flags4.bit2) {
        lRhModel_SetupNoMotion(arg->data);
    } else {
        *(s32 *)0x700000B0 = 0;
        *(f32 *)0x700000BC = (*(Data_0020FAF0 **)0x700000DC)->value54;
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
    Spr_0020FF80 *spr = (Spr_0020FF80 *)0x70000000;
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
    lRhModel_SetupNoMotionRecursive((void *)0x70000000, data, gRhModel_vecScale);
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
extern s32 require_coordinate_index;


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

extern void *gRhModel_dwStack;
extern u8 D_70004000[];
extern u8 gRhModel_vecScale[];

/* Builds a model's node matrices from two motions blended at their frames and weights. */
s32 lRhModel_SetupMultiMotion(void *arg0, void *arg1, void *arg2, f32 frame, f32 frame2, f32 value, f32 value2) {
    Spr_00210260 *spr = (Spr_00210260 *)0x70000000;
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

extern u32 require_coordinate_no;
extern s32 require_coordinate_index;


/* One node of lRhModel_SetupMultiMotion, then its children and siblings. */
s32 lRhModel_SetupMultiMotionRecursive(void *arg0, s32 depth, void *arg2) {
    extern Slot_00210310 require_coordinate[];
    Spr_00210310 *spr = (Spr_00210310 *)0x70000000;
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

    RhMem_CopyMemory16((void *)0x70000030, (void *)0x70000000, 3);
    RhMem_CopyMemory16((void *)0x70000060, (void *)0x70000000, 3);
    flags = lRhModel_GetInterpolateMotionItem(src0, time0, flags, (f32 *)0x70000050, (void *)0x70000040, (void *)0x70000030, multiplier);
    result = lRhModel_GetInterpolateMotionItem(src1, time1, flags, (f32 *)0x70000080, (void *)0x70000070, (void *)0x70000060, multiplier);
    position[0] = ((f32 *)0x70000050)[0] * weight0 + ((f32 *)0x70000080)[0] * weight1;
    position[1] = ((f32 *)0x70000050)[1] * weight0 + ((f32 *)0x70000080)[1] * weight1;
    position[2] = ((f32 *)0x70000050)[2] * weight0 + ((f32 *)0x70000080)[2] * weight1;
    RhGeom_RoationComplexInterpolate(rotation, (s32 *)0x70000040, (s32 *)0x70000070, weight0, weight1);
    if (!(result & 4)) {
        scale[0] = ((f32 *)0x70000030)[0] * weight0 + ((f32 *)0x70000060)[0] * weight1;
        scale[1] = ((f32 *)0x70000030)[1] * weight0 + ((f32 *)0x70000060)[1] * weight1;
        scale[2] = ((f32 *)0x70000030)[2] * weight0 + ((f32 *)0x70000060)[2] * weight1;
    }
    return result;
}

/* lRhModel_SetupPulseMotion's twin: fill the scratchpad header for a float-motion walk, then run
   lRhModel_SetupFloatMotionRecursive with the stack on the scratchpad (0x70004000). */

/* Builds a model's node matrices from a key-framed (float) motion at `time`. */
s32 lRhModel_SetupFloatMotion(u8 *model, u8 *motion, f32 time) {
    u8 *spr = (u8 *)0x70000000;
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

extern u32 require_coordinate_no;
extern s32 require_coordinate_index;


/* One node of lRhModel_SetupFloatMotion, then its children and siblings. */
s32 lRhModel_SetupFloatMotionRecursive(void *arg0, s32 depth, void *arg2) {
    extern s32 lRhModel_GetInterpolateMotionItem(void *, u16, f32, void *, void *, void *, f32);
    extern Slot_00210940 require_coordinate[];
    Spr_00210940 *spr = (Spr_00210940 *)0x70000000;
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

    if (*(u16 *)0x700000E0 & 4) {
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
    if (*(u16 *)0x700000E0 & 4) {
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

extern void *gRhModel_dwStack;  /* the stack pointer saved while the pulse walk runs on the scratchpad */
extern u8 D_70004000[];   /* the scratchpad stack top */
extern u8 gRhModel_vecScale[];

/* Fill the scratchpad header for a pulse-motion walk, then run lRhModel_SetupPulseMotionRecursive with the
   stack on the scratchpad (0x70004000), the real stack pointer kept in gRhModel_dwStack. */

/* Builds a model's node matrices from a per-frame (pulse) motion at `time`. */
s32 lRhModel_SetupPulseMotion(u8 *model, u8 *motion, f32 time) {
    u8 *spr = (u8 *)0x70000000;
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

extern u32 require_coordinate_no;
extern s32 require_coordinate_index;
extern Slot_00211530 require_coordinate[];


/* One node of lRhModel_SetupPulseMotion, then its children and siblings. */
s32 lRhModel_SetupPulseMotionRecursive(void *arg0, s32 depth, void *arg2) {
    extern s32 lRhModel_GetPulseMotionItem(void *, s64, u16, void *, void *, void *, f32);
    Spr_00211530 *spr = (Spr_00211530 *)0x70000000;
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

    if (*(u16 *)0x700000E0 & 4) {
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

    if (*(u16 *)0x700000E0 & 4) {
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
        s32 var_s3;
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
            for (var_s3 = 0; var_s3 < temp_s2; var_s3++) {
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
#pragma conditional_move reset

typedef struct Flags_00212250 {
    u8 reserved0 : 7;
    u8 scale : 1;
    u8 add : 1;
    u8 replace : 1;
    u8 reserved1 : 6;
} Flags_00212250;

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
    s32 var_s0;
    s32 var_s1;

    var_s0 = 0;
    if (var_s0 < count) {
        var_s1 = matrices;
        do {
            RhGeom_MulMatrixRev(var_s1, viewScreen);
            var_s0 += 1;
            var_s1 += 0x70;
        } while (var_s0 < count);
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

/* Draws a model part's translucent polygons on the CPU (sorted back to front) into the packet. */
u8 *RhModelCpu_DrawAlpha(u8 *packet, s32 data, s32 size, s32 global) {
    u8 *temp_s1;
    u8 *temp_v0;

    lRhModelCpu_SetupGlobal(global);
    *(s32 *)(packet + 0) = 0x10000002;
    *(s32 *)(packet + 4) = 0;
    *(s32 *)(packet + 8) = 0x11000000;
    *(s32 *)(packet + 0xC) = 0x51000002;
    *(s64 *)(packet + 0x10) = 0x1000000000008001LL;
    *(s64 *)(packet + 0x18) = 0xE;
    *(s64 *)(packet + 0x20) = 0x73;
    temp_s1 = packet + 0x30;
    *(s64 *)(packet + 0x28) = 0;
    temp_v0 = lRhModelCpu_TraceDynamicBlock(temp_s1, data, size);
    if (temp_v0 == NULL) {
        return packet;
    }
    lRhModelCpu_SortPolygon(temp_s1, temp_v0);
    lRhModelCpu_CleanupPacket(temp_s1, temp_v0);
    return temp_v0;
}

typedef struct Spr_002130A0 {
    f32 m[4][4];
    u8 pad40[0x1C];
    f32 f5C;
    u32 tag[8];
    u64 f80;
    u64 f88;
    u8 pad90[0x64];
    f32 fF4;
    f32 fF8;
    u8 padFC[8];
    s32 f104;
    u8 pad108[8];
    f32 f110;
    f32 f114;
} Spr_002130A0;

/* Sets up the CPU drawer's matrices and lights (`withLight`). */
s32 lRhModelCpu_SetupGlobal(s32 withLight) {
    Spr_002130A0 *spr = (Spr_002130A0 *)0x70000000;
    u8 e[4];
    f32 near;
    f32 far;
    f32 c;
    f32 d;

    RhView_GetViewScreenMatrix(spr);
    {
        register u8 *m = (u8 *)0x70000000;
        asm {
            lqc2 vf20, 0x0(m)
            lqc2 vf21, 0x10(m)
            lqc2 vf22, 0x20(m)
            lqc2 vf23, 0x30(m)
        }
    }
    spr->tag[0] = 0x10000000;
    spr->tag[1] = 0;
    spr->tag[2] = 0;
    spr->tag[3] = 0;
    spr->tag[4] = 0x10000006;
    spr->tag[5] = 0;
    spr->tag[6] = 0;
    spr->tag[7] = 0x51000006;
    spr->f80 = 0x3400000000008003;
    spr->f88 = 0x412;
    RhView_GetClipZ(&spr->fF4, &spr->fF8);
    spr->f104 = sceDmaGetChan(8);
    spr->f5C = 1.0f;
    RhView_GetFogParameter(&near, &far, &c, &d, e);
    if (withLight != 0) {
        spr->f110 = 255.0f * far / (far - near);
        spr->f114 = 255.0f / (far - near);
    } else {
        spr->f110 = 255.0f;
        spr->f114 = 0.0f;
    }
    return 1;
}

#define P_002131D0 ((u8 *)data)

/* Transforms a model part's dynamic block on the CPU into `out`. */
u8 *lRhModelCpu_TraceDynamicBlock(u8 *out, s32 data, s32 size) {
    u8 *spr = (u8 *)0x70000000;
    u32 cmd;

    size = data + size;
    while (P_002131D0 < (u8 *)size) {
        cmd = *(u32 *)P_002131D0;
        if (cmd == 0x10000008) {
            *(__int128 *)(spr + 0x60) = *(__int128 *)P_002131D0;
            *(u32 *)(spr + 0x60) = 0x30000008;
            *(u8 **)(spr + 0x64) = P_002131D0 + 0x10;
            data += 0x90;
        } else if (cmd == 0x10000000) {
            data += 0x10;
        } else if (cmd == 0x10000003) {
            u8 *q = P_002131D0;

            func_0020B380(spr, q, 4);
            *(u32 *)(spr + 0x100) = (u8)(u32)(*(f32 *)(spr + 0x20) / 2.0f + *(f32 *)(spr + 0x10));
            *(u32 *)(spr + 0x100) |= (u8)(u32)(*(f32 *)(spr + 0x24) / 2.0f + *(f32 *)(spr + 0x14)) << 8;
            *(u32 *)(spr + 0x100) |= (u8)(u32)(*(f32 *)(spr + 0x28) / 2.0f + *(f32 *)(spr + 0x18)) << 16;
            *(u32 *)(spr + 0x100) |= (u32)*(f32 *)(spr + 0x2C) << 24;
            data = (s32)(q + 0x40);
        } else if ((cmd & 0xF0000000) == 0x30000000) {
            s32 x = *(s32 *)(P_002131D0 + 0xC);

            if (x == 0) {
                u8 *q = P_002131D0;

                out = (u8 *)func_00213410((s32)out, (s32)*(u32 *)(q + 4), *(u16 *)q << 4);
                data = (s32)(q + 0x10);
            } else {
                register u8 *m;
                register u32 dst = x & 0x3FF;
                u8 *q = P_002131D0;

                data = (s32)(q + 0x10);
                m = *(u8 **)(q + 4);
                asm {
                    lqc2 vf16, 0x0(m)
                    lqc2 vf17, 0x10(m)
                    lqc2 vf18, 0x20(m)
                    lqc2 vf19, 0x30(m)
                    ctc2.ni dst, vi1
                    vmulax.xyzw ACC, vf20, vf16x
                    vmadday.xyzw ACC, vf21, vf16y
                    vmaddaz.xyzw ACC, vf22, vf16z
                    vmaddw.xyzw vf16, vf23, vf16w
                    vmulax.xyzw ACC, vf20, vf17x
                    vmadday.xyzw ACC, vf21, vf17y
                    vmaddaz.xyzw ACC, vf22, vf17z
                    vmaddw.xyzw vf17, vf23, vf17w
                    vmulax.xyzw ACC, vf20, vf18x
                    vmadday.xyzw ACC, vf21, vf18y
                    vmaddaz.xyzw ACC, vf22, vf18z
                    vmaddw.xyzw vf18, vf23, vf18w
                    vmulax.xyzw ACC, vf20, vf19x
                    vmadday.xyzw ACC, vf21, vf19y
                    vmaddaz.xyzw ACC, vf22, vf19z
                    vmaddw.xyzw vf19, vf23, vf19w
                    vsqi.xyzw vf16, (vi1++)
                    vsqi.xyzw vf17, (vi1++)
                    vsqi.xyzw vf18, (vi1++)
                    vsqi.xyzw vf19, (vi1++)
                }
            }
        } else {
            return NULL;
        }
    }
    return out;
}

#undef P_002131D0

/* Transforms a model part's static block on the CPU. */
s32 lRhModelCpu_TraceStaticBlock(s32 arg0, u32 cursor, s32 size) {
    u32 end = cursor + size;
    u32 *scratchpad = (u32 *)0x70000000;
    u32 packet;

    if (cursor < end) {
        do {
        packet = cursor;
        if (!(*(u32 *)(cursor + 0xC) & 0x8000)) {
            arg0 = lRhModelCpu_CalcIndepStrip(arg0, (s32 *)cursor);
        } else {
            arg0 = lRhModelCpu_CalcSharedStrip(arg0, (s32 *)cursor);
        }
        cursor = scratchpad[0x3F];
        if (*(u32 *)(packet + 4) & 0x8000) {
            cursor += 4;
        }
        while (*(s32 *)cursor == 0) {
            cursor += 4;
        }
        } while (cursor < end);
    }
    return arg0;
}

typedef struct {
    u32 xy;
    u32 z : 24;
    u32 f : 8;
} Vert_002134D0;

typedef struct {
    u8 pad00[0x40];
    Vert_002134D0 v0;
    u8 pad48[0x10];
    Vert_002134D0 v1;
    u8 pad60[0x10];
    Vert_002134D0 v2;
    s32 f78;
    s32 depth;
} Prim_002134D0;


#define prim ((Prim_002134D0 *)arg0)

/* Transforms a strip of separate vertices on the CPU. */
s32 lRhModelCpu_CalcIndepStrip(s32 arg0, s32 *arg1) {
    u8 *scratch;
    u8 *var_s1;
    s32 var_s2;
    s32 temp_s3;
    s32 var_s4;

    var_s1 = (u8 *)arg1 + 0x18;
    scratch = (u8 *)0x70000000;
    var_s4 = 0;
    temp_s3 = arg1[1] & 0x7FFF;
    for (var_s2 = 0; var_s2 < temp_s3; var_s2++) {
        register s32 base = arg1[4];
        asm {
            ctc2.ni base, vi1
            vlqi.xyzw vf16, (vi1++)
            vlqi.xyzw vf17, (vi1++)
            vlqi.xyzw vf18, (vi1++)
            vlqi.xyzw vf19, (vi1++)
        }
        scratch[0xF0 + var_s4] = lRhModelCpu_CalcIndepPoint((s32)(scratch + var_s4 * 0x18 + 0x90), (s32 *)var_s1);
        if (var_s2 >= 2) {
            if (scratch[0xF0] && scratch[0xF1] && scratch[0xF2]) {
                RhMem_CopyMemory16(prim, scratch + 0x60, 8);
                prim->f78 = 0;
                prim->depth = ((prim->v0.z > prim->v1.z ? prim->v0.z : prim->v1.z) > prim->v2.z)
                    ? (prim->v0.z > prim->v1.z ? prim->v0.z : prim->v1.z) : prim->v2.z;
                arg0 += sizeof(Prim_002134D0);
            }
        }
        var_s1 += 0x12;
        var_s4 = (var_s4 + 1) % 3;
    }
    *(u32 *)(scratch + 0xFC) = (u32)(var_s1 + 3) & ~3;
    return arg0;
}

#undef prim

typedef struct Spr_00213680 {
    u8 pad00[0x40];
    f32 res[4];
    f32 in[4];
    u8 pad60[0x98];
    f32 fF8;
    u8 padFC[4];
    u32 f100;
    u8 pad104[0xC];
    f32 f110;
    f32 f114;
} Spr_00213680;

typedef struct Out_00213680 {
    f32 s;
    f32 t;
    u32 color;
    f32 q;
    u16 x;
    u16 y;
    u32 z : 24;
    u32 fog : 8;
} Out_00213680;

typedef struct In_00213680 {
    s16 u;
    s16 v;
    u8 pad4[8];
    s16 x;
    s16 y;
    s16 z;
} In_00213680;

#define OUT_00213680 ((Out_00213680 *)arg0)
#define IN_00213680 ((In_00213680 *)arg1)

/* Transforms one separate vertex on the CPU. */
s8 lRhModelCpu_CalcIndepPoint(s32 arg0, s32 *arg1) {
    Spr_00213680 *spr = (Spr_00213680 *)0x70000000;
    register f32 *src = spr->in;
    register f32 *dst = spr->res;
    f32 w;
    f32 fog;

    OUT_00213680->color = spr->f100;
    spr->in[0] = IN_00213680->x;
    spr->in[1] = IN_00213680->y;
    spr->in[2] = IN_00213680->z;
    asm {
        lqc2 vf1, 0x0(src)
        vmulax.xyzw ACC, vf16, vf1x
        vmadday.xyzw ACC, vf17, vf1y
        vmaddaz.xyzw ACC, vf18, vf1z
        vmaddw.xyzw vf1, vf19, vf1w
        vdiv Q, vf0w, vf1w
        vwaitq
        vmulq.xyz vf1, vf1, Q
        sqc2 vf1, 0x0(dst)
    }
    w = spr->res[3];
    if (w < 1.0f || !(w < spr->fF8) || spr->res[0] <= 1.0f || !(spr->res[0] < 4095.0f) || spr->res[1] <= 1.0f ||
        !(spr->res[1] < 4095.0f)) {
        return 0;
    }
    OUT_00213680->x = (u32)(16.0f * spr->res[0]);
    OUT_00213680->y = (u32)(16.0f * spr->res[1]);
    OUT_00213680->z = (u32)(spr->res[2]);
    fog = spr->f110 - spr->f114 * spr->res[3];
    if (fog <= 0.0f) {
        OUT_00213680->fog = 0;
    } else if (!(fog < 255.0f)) {
        OUT_00213680->fog = 0xFF;
    } else {
        OUT_00213680->fog = (u32)(fog);
    }
    OUT_00213680->s = IN_00213680->u / spr->res[3] / 4096.0f;
    OUT_00213680->t = IN_00213680->v / spr->res[3] / 4096.0f;
    OUT_00213680->q = 1.0f / spr->res[3];
    return 1;
}

#undef OUT_00213680
#undef IN_00213680

typedef struct {
    u32 xy;
    u32 z : 24;
    u32 f : 8;
} Vert_002138D0;

typedef struct {
    u8 data[0x12];
} Item_002138D0;

typedef struct {
    u8 pad00[0x40];
    Vert_002138D0 v0;
    u8 pad48[0x10];
    Vert_002138D0 v1;
    u8 pad60[0x10];
    Vert_002138D0 v2;
    s32 f78;
    s32 depth;
} Prim_002138D0;

#pragma opt_lifetimes off

/* Transforms a strip of shared vertices on the CPU. */
s32 lRhModelCpu_CalcSharedStrip(s32 arg0, s32 *arg1) {
    extern s8 lRhModelCpu_CalcSharedPoint(s32, s32 *);
    u8 *scratch;
    u8 *var_s1;
    s32 var_s2;
    s32 temp_s3;
    s32 var_s4;
    Prim_002138D0 *prim;
    u32 z0;
    u32 z1;

    var_s1 = (u8 *)arg1 + 0x14;
    prim = (Prim_002138D0 *)arg0;
    scratch = (u8 *)0x70000000;
    var_s4 = 0;
    temp_s3 = arg1[1] & 0x7FFF;
    for (var_s2 = 0; var_s2 < temp_s3; var_s2++) {
        scratch[0xF0 + var_s4] = lRhModelCpu_CalcSharedPoint((s32)(scratch + var_s4 * 0x18 + 0x90), (s32 *)var_s1);
        if (var_s2 >= 2) {
            if (scratch[0xF0] && scratch[0xF1] && scratch[0xF2]) {
                RhMem_CopyMemory16(prim, scratch + 0x60, 8);
                prim->f78 = 0;
                z0 = prim->v0.z;
                z1 = prim->v1.z;
                z0 = ((z0 > z1 ? z0 : z1) > prim->v2.z) ? (z0 > z1 ? z0 : z1) : prim->v2.z;
                prim->depth = z0;
                prim++;
            }
        }
        var_s1 = (u8 *)((Item_002138D0 *)(var_s1 + 6) + *(u16 *)(var_s1 + 4));
        var_s4 = (var_s4 + 1) % 3;
    }
    *(u32 *)0x700000FC = (u32)(var_s1 + 3) & ~3;
    return (s32)prim;
}
#pragma opt_lifetimes reset

typedef struct Spr_00213A40 {
    u8 pad00[0x40];
    f32 res[4];
    f32 in[4];
    u8 pad60[0x98];
    f32 fF8;
    u8 padFC[4];
    u32 f100;
    u8 pad104[0xC];
    f32 f110;
    f32 f114;
} Spr_00213A40;

typedef struct Out_00213A40 {
    f32 s;
    f32 t;
    u32 color;
    f32 q;
    u16 x;
    u16 y;
    u32 z : 24;
    u32 fog : 8;
} Out_00213A40;

typedef struct Weight_00213A40 {
    u16 matrix;
    u16 weight;
    u8 pad4[8];
    s16 x;
    s16 y;
    s16 z;
} Weight_00213A40;

typedef struct In_00213A40 {
    s16 u;
    s16 v;
    u16 count;
    Weight_00213A40 w[1];
} In_00213A40;

#define OUT_00213A40 ((Out_00213A40 *)arg0)
#define IN_00213A40 ((In_00213A40 *)arg1)

/* Transforms one shared vertex on the CPU. */
s8 lRhModelCpu_CalcSharedPoint(s32 arg0, s32 *arg1) {
    Spr_00213A40 *spr = (Spr_00213A40 *)0x70000000;
    register Weight_00213A40 *rec;
    s32 i;
    s32 n;
    s32 last;
    register f32 *src;
    f32 w;
    f32 fog;

    asm {
        vsub.xyzw vf1, vf0, vf0
    }
    n = IN_00213A40->count;
    last = -1;
    rec = IN_00213A40->w;
    src = spr->in;
    for (i = 0; i < n; i++, rec++) {
        register u32 m = rec->matrix;
        register u32 wgt;
        if (last != m) {
            last = m;
            asm {
                ctc2.ni m, vi1
                vlqi.xyzw vf16, (vi1++)
                vlqi.xyzw vf17, (vi1++)
                vlqi.xyzw vf18, (vi1++)
                vlqi.xyzw vf19, (vi1++)
            }
        }
        spr->in[0] = rec->x;
        spr->in[1] = rec->y;
        spr->in[2] = rec->z;
        wgt = rec->weight;
        asm {
            qmtc2.ni wgt, vf4
            lqc2 vf2, 0x0(src)
            vitof12.x vf4, vf4
            vmulax.xyzw ACC, vf16, vf2x
            vmadday.xyzw ACC, vf17, vf2y
            vmaddaz.xyzw ACC, vf18, vf2z
            vmaddw.xyzw vf3, vf19, vf2w
            vmulx.xyzw vf2, vf3, vf4x
            vadd.xyzw vf1, vf1, vf2
        }
    }
    {
        register f32 *dst = spr->res;
        asm {
            vdiv Q, vf0w, vf1w
            vwaitq
            vmulq.xyz vf1, vf1, Q
            sqc2 vf1, 0x0(dst)
        }
    }
    w = spr->res[3];
    if (w < 1.0f || !(w < spr->fF8) || spr->res[0] <= 1.0f || !(spr->res[0] < 4095.0f) || spr->res[1] <= 1.0f ||
        !(spr->res[1] < 4095.0f)) {
        return 0;
    }
    OUT_00213A40->x = (u32)(16.0f * spr->res[0]);
    OUT_00213A40->y = (u32)(16.0f * spr->res[1]);
    OUT_00213A40->z = (u32)(spr->res[2]);
    fog = spr->f110 - spr->f114 * spr->res[3];
    if (fog <= 0.0f) {
        OUT_00213A40->fog = 0;
    } else if (!(fog < 255.0f)) {
        OUT_00213A40->fog = 0xFF;
    } else {
        OUT_00213A40->fog = (u32)(fog);
    }
    OUT_00213A40->color = spr->f100;
    OUT_00213A40->s = IN_00213A40->u / spr->res[3] / 4096.0f;
    OUT_00213A40->t = IN_00213A40->v / spr->res[3] / 4096.0f;
    OUT_00213A40->q = 1.0f / spr->res[3];
    return 1;
}

#undef OUT_00213A40
#undef IN_00213A40

/* From the dotr-decomp CC0 bundle (commit 88c32bb2), chatC/imp/conv.py. */

typedef int DotrWalkAddr;
struct DotrWalkPolygon {
    int unknown_00[31];
    unsigned int key;
};
struct DotrWalkSortPad {
    unsigned char unknown_000[0x120];
    struct DotrWalkPolygon temp;
};
#define DOTR_WALK_SORT_PAD ((struct DotrWalkSortPad *)0x70000000)
#define DOTR_SORT_AT(i) (first + (i) - 1)
#define DOTR_SORT_COPY(k) ((struct DotrWalkPolygon *)(((k) << 7) + (DotrWalkAddr)first - 128))

/* Sorts the CPU drawer's polygons back to front. */
void lRhModelCpu_SortPolygon(void *first_v, void *end_v)
{
    struct DotrWalkPolygon * first = first_v;
    struct DotrWalkPolygon * end = end_v;
    struct DotrWalkSortPad *scratch = DOTR_WALK_SORT_PAD;
    int k;
    int j;
    int i;
    int n = end - first;
    struct DotrWalkPolygon *p;

    i = n >> 1;
    if (i > 0) {
        p = DOTR_SORT_COPY(i);
        do {
            k = i;
            RhMem_CopyMemory16(&scratch->temp, p, 8);
            while ((j = k * 2) <= n) {
                if (j < n && DOTR_SORT_AT(j)->key < DOTR_SORT_AT(j + 1)->key) {
                    j++;
                }
                if (!(scratch->temp.key < DOTR_SORT_AT(j)->key)) {
                    break;
                }
                RhMem_CopyMemory16(DOTR_SORT_COPY(k), DOTR_SORT_COPY(j), 8);
                k = j;
            }
            RhMem_CopyMemory16(DOTR_SORT_COPY(k), &scratch->temp, 8);
            i--;
            p--;
        } while (i > 0);
    }
    if (n > 1) {
        p = DOTR_SORT_COPY(n);
        do {
            RhMem_CopyMemory16(&scratch->temp, p, 8);
            RhMem_CopyMemory16(p, first, 8);
            p--;
            n--;
            k = 1;
            while ((j = k * 2) <= n) {
                if (j < n && DOTR_SORT_AT(j)->key < DOTR_SORT_AT(j + 1)->key) {
                    j++;
                }
                if (!(scratch->temp.key < DOTR_SORT_AT(j)->key)) {
                    break;
                }
                RhMem_CopyMemory16(DOTR_SORT_COPY(k), DOTR_SORT_COPY(j), 8);
                k = j;
            }
            RhMem_CopyMemory16(DOTR_SORT_COPY(k), &scratch->temp, 8);
        } while (n > 1);
    }
}
#undef DOTR_WALK_SORT_PAD
#undef DOTR_SORT_AT
#undef DOTR_SORT_COPY

/* Finishes the CPU drawer's packet. */
void lRhModelCpu_CleanupPacket(u8 *start, u8 *end) {
    s32 *field;
    s32 previous;
    s32 value;
    u8 *cursor;

    cursor = start;
    previous = 0;
    if (cursor < end) {
        do {
            field = (s32 *)(cursor + 4);
            value = *field;
            if (value == previous) {
                *(s32 *)(cursor + 0) = 0x10000000;
                *field = 0;
                *(s32 *)(cursor + 8) = 0;
                *(s32 *)(cursor + 0xC) = 0;
            } else {
                previous = value;
            }
            cursor += 0x80;
        } while (cursor < end);
    }
}

/* Starts a depth-sorted polygon list at `list` with room for `count`. */
void RhZSort_Start(s32 list, s32 count) {
    zSortList = list;
    D_0032F784 = count;
    D_0032F78C = count;
    D_0032F788 = 1;
}

/* Sorts and sends the depth-sorted polygon list. */
void RhZSort_Finish(void) {
    RhBase_SetVifPacketArea(RhZSort_Finish_Pipe(RhBase_GetVifPacketArea()));
}

typedef struct {
    s32 key;
    s32 value;
} Record_00213FC0;

typedef struct {
    s32 *output;
    Record_00213FC0 *end;
    s32 ready;
    Record_00213FC0 *begin;
} State_00213FC0;


/* Sorts the depth-sorted polygon list and writes it into the packet. */
s32 RhZSort_Finish_Pipe(s32 packet) {
    State_00213FC0 *state = (State_00213FC0 *)&zSortList;
    s32 *output = (s32 *)packet;
    Record_00213FC0 *record;

    if (D_0032F78C == D_0032F784) {
        return packet;
    }

    RhMath_HeapSortStruct(state->begin, state->end - state->begin, 8, lRhZSort_ZCompare);
    for (record = state->begin; record < state->end; record++) {
        output[0] = 0x50000000;
        output[1] = record->value;
        output[2] = 0;
        output[3] = 0;
        output += 4;
    }

    state->output = output;
    state->begin = state->end;
    state->ready = 1;
    return (s32)output;
}

/* Compares two polygons by depth. */
s32 lRhZSort_ZCompare(s32 *a, s32 *b) {
    return *a - *b;
}

typedef struct Flags_00214090 {
    u8 unused : 7;
    u8 enabled : 1;
} Flags_00214090;

typedef struct Header_00214090 {
    s32 magic;
    u8 padding[0xC];
    u16 count;
    u8 unknown;
    Flags_00214090 flags;
    u32 data;
    u32 extra;
} Header_00214090;

/* Relocates a motion file (its offsets become pointers). */
s32 NjaReloc_Adjust_M3DMOT(void *motion) {
    Header_00214090 *header = motion;

    if (header->magic != 0x1A544F4D) {
        return 0;
    }
    header->data = (u32)header + header->data;
    header->extra = (u32)header + header->extra;
    lNjaReloc_AdjustMotion((void *)header->data, (s32)header, header->count, header->flags.enabled);
    return 1;
}

/* Relocates one motion's data against `base`. */
s32 lNjaReloc_AdjustMotion(void *motion, s32 base, s32 count, s32 first) {
    s32 temp_v1;
    s32 temp_v0;
    s32 temp_v0_2;

    if (first != 0) {
        *(s32 *)((u8 *)motion - 4) = base + *(s32 *)((u8 *)motion - 4);
    }
    temp_v1 = *(u16 *)((u8 *)motion + 8) & 0x3F;
    if (temp_v1 == 3) {
        temp_v0 = *(s32 *)motion;
        if (temp_v0 != 0) {
            *(s32 *)motion = base + temp_v0;
            lNjaReloc_AdjustMData2((u8 *)*(s32 *)motion, base, count, first);
        }
    } else if (temp_v1 == 7) {
        temp_v0_2 = *(s32 *)motion;
        if (temp_v0_2 != 0) {
            *(s32 *)motion = base + temp_v0_2;
            lNjaReloc_AdjustMData3((u8 *)*(s32 *)motion, base, count, first);
        }
    }
    return 1;
}

/* Relocates a motion's two-channel key data. */
s32 lNjaReloc_AdjustMData2(u8 *data, s32 base, s32 count, s32 first) {
    s32 i;
    s32 j;
    s32 *p;

    if (first != 0) {
        *(s32 *)(data - 4) = base + *(s32 *)(data - 4);
    }
    for (i = 0; i < count; i++) {
        j = 0;
        p = (s32 *)data;
        do {
            if (*p != 0) {
                *p = base + *p;
                if (first != 0) {
                    *(s32 *)(*p - 4) = base + *(s32 *)(*p - 4);
                }
            }
            j++;
            p++;
        } while (j < 2);
        data += 0x10;
    }
    return 1;
}

/* Relocates a motion's three-channel key data. */
s32 lNjaReloc_AdjustMData3(u8 *data, s32 base, s32 count, s32 first) {
    s32 i;
    s32 j;
    s32 *p;

    if (first != 0) {
        *(s32 *)(data - 4) = base + *(s32 *)(data - 4);
    }
    for (i = 0; i < count; i++, data += 0x18) {
        j = 0;
        p = (s32 *)data;
        do {
            if (*p != 0) {
                *p = base + *p;
                if (first != 0) {
                    *(s32 *)(*p - 4) = base + *(s32 *)(*p - 4);
                }
            }
            j++;
            p++;
        } while (j < 3);
    }
    return 1;
}

typedef struct Slot_00214290 {
    u32 value : 31;
    u32 flag : 1;
    u32 other : 30;
    u32 type : 2;
} Slot_00214290;

typedef struct Card_00214290 {
    Slot_00214290 slots[9];
    u16 value : 14;
    u16 flag : 1;
    u16 otherFlag : 1;
    s16 count;
} Card_00214290;

typedef struct Deck_00214290 {
    s16 cards[40];
    s16 card;
    s16 count;
} Deck_00214290;

typedef struct Flags_00214290 {
    u8 mode : 2;
    u8 bit2 : 1;
    u8 bit3 : 1;
    u8 bit4 : 1;
    u8 bit5 : 1;
    u8 unused : 2;
} Flags_00214290;

typedef struct Save_00214290 {
    Card_00214290 cards[0x356];
    s16 values[5];
    u8 padding[2];
    Deck_00214290 decks[3];
    u8 bytes[16];
    union {
        u8 bytes[22];
        struct {
            u8 header[3];
            u8 grid[5][7][7];
        } board;
    } data;
    u8 padding2[4];
    Flags_00214290 flags;
    u8 padding3[3];
} Save_00214290;

/* Clears both save profiles (0xFFA0 bytes each): every card's trunk entries, the five special cards, the three
   decks, the five edited maps (all field 7), the options. */
void SzData_Initialize(void) {
    extern Save_00214290 saveProfiles[2];
    s32 card;
    s32 slot;
    s32 profile;
    Slot_00214290 *slotPtr;
    Card_00214290 *cardPtr;
    Save_00214290 *save;
    s16 *valuePtr;
    s32 value;
    Deck_00214290 *currentDeck;
    s16 *deckCardPtr;
    u8 *deckBase;
    s32 deck;
    s32 deckCard;
    s32 byte;
    s32 dataByte;
    s32 grid;
    u8 *columnPtr;
    u8 *rowBase;
    u8 *gridBase;
    s32 row;
    s32 column;

    RhMem_FillMemory((s8 *)saveProfiles, 0, 0x1FF40);
    save = saveProfiles;
    profile = 0;
    do {
        card = 0;
        cardPtr = save->cards;
        do {
            slot = 0;
            slotPtr = cardPtr->slots;
            do {
                slotPtr->value = 0;
                slotPtr->other = 0;
                slotPtr->type = 3;
                slotPtr->flag = 0;
                slot++;
                slotPtr++;
            } while (slot < 9);
            cardPtr->value = 0;
            cardPtr->count = 0;
            cardPtr->flag = 0;
            cardPtr->otherFlag = 0;
            card++;
            cardPtr++;
        } while (card < 0x356);
        value = 0;
        valuePtr = (s16 *)save;
        do {
            valuePtr[0x7EC4] = 999;
            value++;
            valuePtr++;
        } while (value < 5);
        deck = 0;
        deckBase = (u8 *)save;
        do {
            currentDeck = (Deck_00214290 *)(deckBase + 0xFD94);
            deckCard = 0;
            deckCardPtr = currentDeck->cards;
            do {
                *deckCardPtr = 999;
                deckCard++;
                deckCardPtr++;
            } while (deckCard < 40);
            currentDeck->card = 999;
            currentDeck->count = 0;
            deck++;
            deckBase += 0x54;
        } while (deck < 3);
        byte = 0;
        do {
            save->bytes[byte] = 0;
            byte++;
        } while (byte < 16);
        dataByte = 0;
        do {
            save->data.bytes[dataByte] = 0;
            dataByte++;
        } while (dataByte < 22);
        grid = 0;
        gridBase = (u8 *)save;
        do {
            row = 0;
            rowBase = gridBase;
            do {
                column = 0;
                columnPtr = rowBase;
                do {
                    columnPtr[0xFEA3] = 7;
                    column++;
                    columnPtr++;
                } while (column < 7);
                row++;
                rowBase += 7;
            } while (row < 7);
            grid++;
            gridBase += 0x31;
        } while (grid < 5);
        save->flags.mode = 0;
        save->flags.bit2 = 1;
        save->flags.bit3 = 1;
        save->flags.bit4 = 1;
        save->flags.bit5 = 1;
        save++;
        profile++;
    } while (profile < 2);
}

/* Sets which duel side plays with save profile 0 (the other side gets profile 1). */
void SzData_SetRoseFlag(s32 side) {
    extern u8 profileZeroSide;

    profileZeroSide = side;
}

/* The save profile of duel side `side`. */
void *SzData_GetData(s32 side) {
    extern u8 saveProfiles[];
    extern u8 profileZeroSide;
    s32 profile;

    if (profileZeroSide == side) {
        profile = 0;
    } else {
        profile = 1;
    }
    return saveProfiles + (profile * 0xFFA0);
}

typedef struct {
    u8 values[9][8];
    u16 id : 14;
    u16 flag1 : 1;
    u16 flag2 : 1;
    s16 count;
} Entry_00214620;

typedef struct {
    s16 values[40];
    s16 active;
    s16 count;
} Deck_00214620;

typedef struct {
    u8 mode : 2;
    u8 flag2 : 1;
    u8 flag3 : 1;
    u8 flag4 : 1;
    u8 flag5 : 1;
    u8 unused : 2;
} Flags_00214620;

typedef union {
    u8 zeroes[22];
    struct {
        u8 prefix[3];
        u8 values[5][7][7];
    } map;
} Region_00214620;

typedef struct {
    Entry_00214620 entries[854];
    s16 values[5];
    s16 padding_fd92;
    Deck_00214620 decks[3];
    u8 bytes_fe90[16];
    Region_00214620 region;
    s32 count;
    Flags_00214620 flags;
    u8 padding_ff9d[3];
} State_00214620;

extern u8 profileZeroSide; /* original: gSzData_bRoseFlag */

/* Clears the save profile of duel side `side` (cards, decks, maps and options to their defaults). */
void SzData_ClearData(s32 side) {
    extern State_00214620 saveProfiles[2];
    s32 i;
    State_00214620 *state;
    Entry_00214620 *entry;
    s32 j;
    u8 *value;
    s16 *value_base;
    s32 n_values;
    Deck_00214620 *deck;
    s16 *card;
    u8 *deck_base;
    s32 n_decks;
    s32 n_cards;
    s32 n_bytes1;
    s32 n_bytes2;
    s32 n_layers;
    u8 *cell;
    u8 *row;
    u8 *layer;
    s32 n_rows;
    s32 n_cells;

    state = &saveProfiles[profileZeroSide == side ? 0 : 1];
    i = 0;
    entry = state->entries;
    do {
        j = 0;
        value = entry->values[0];
        do {
            SzData_ClearCardInfo(value);
            j++;
            value += 8;
        } while (j < 9);
        entry->id = 0;
        entry->count = 0;
        entry->flag1 = 0;
        entry->flag2 = 0;
        i++;
        entry++;
    } while (i < 854);

    n_values = 0;
    value_base = (s16 *)state;
    do {
        value_base[0x7EC4] = 999;
        n_values++;
        value_base++;
    } while (n_values < 5);

    n_decks = 0;
    deck_base = (u8 *)state;
    do {
        deck = (Deck_00214620 *)(deck_base + 0xFD94);
        n_cards = 0;
        card = deck->values;
        do {
            *card = 999;
            n_cards++;
            card++;
        } while (n_cards < 40);
        deck->active = 999;
        deck->count = 0;
        n_decks++;
        deck_base += 0x54;
    } while (n_decks < 3);

    n_bytes1 = 0;
    do {
        state->bytes_fe90[n_bytes1] = 0;
        n_bytes1++;
    } while (n_bytes1 < 16);

    n_bytes2 = 0;
    do {
        state->region.zeroes[n_bytes2] = 0;
        n_bytes2++;
    } while (n_bytes2 < 22);

    n_layers = 0;
    layer = (u8 *)state;
    do {
        n_rows = 0;
        row = layer;
        do {
            n_cells = 0;
            cell = row;
            do {
                cell[0xFEA3] = 7;
                n_cells++;
                cell++;
            } while (n_cells < 7);
            n_rows++;
            row += 7;
        } while (n_rows < 7);
        n_layers++;
        layer += 49;
    } while (n_layers < 5);
    state->count = 0;
    state->flags.mode = 0;
    state->flags.flag2 = 1;
    state->flags.flag3 = 1;
    state->flags.flag4 = 1;
    state->flags.flag5 = 0;
}

/* Card `slot` (0 = the leader, 1..40) of built-in deck `deck` (0..50), or -1. */
s32 SzData_GetConstDeck(s32 deck, s32 slot) {
    if (deck < 0 || deck >= 51) {
        return -1;
    }
    if (slot < 0 || slot >= 41) {
        return -1;
    }
    return D_002D0970[deck][slot] & 0xFFF;
}

typedef struct {
    u8 entries[0xFD88];
    s16 values[5];
    u8 pad_fd92[0x206];
    s32 count;
    u8 flags;
    u8 pad_ff9d[3];
} State_00214990;

extern s32 D_002D19D8;
extern u16 D_002D49D4[];
extern u8 profileZeroSide; /* original: gSzData_bRoseFlag */

/* Gives side `side` built-in deck `deck`: a fresh trunk with its 41 cards, the leader and the deck set up, a new
   profile id. */
void SzData_SetupFromConstDeck(s32 side, s32 deckNo) {
    extern State_00214990 saveProfiles[2];
    u16 *deck;
    s32 sum;
    s32 i;
    u16 *src;
    u16 *card;
    u16 value;
    State_00214990 *state;

    state = &saveProfiles[profileZeroSide == side ? 0 : 1];
    deck = D_002D0970[deckNo];
    if (!(deckNo >= 0 && deckNo < 51)) {
        return;
    }
    SzData_ClearData(side);
    if (deckNo < 17) {
        sum = 0;
        src = &D_002D49D4[D_002D19D8] + 2;
        while (1) {
            value = *src;
            sum += value & 0x1FFF;
            if (value & 0x8000) {
                break;
            }
            src++;
        }
        do {
            state->count = (sum + func_0019A5C8()) & 0x7FFFFFFF;
        } while (state->count == 0);
    } else {
        state->count = deckNo + 0x40000000;
    }
    i = 0;
    card = deck;
    do {
        SzData_AddBag(side, 0, *card & 0xFFF);
        i++;
        card++;
    } while (i < 41);
    for (i = 0; i < 5; i++) {
        state->values[i] = 999;
    }
    SzData_SetRankDirect(side, *deck & 0xFFF, *deck >> 12);
    SzData_PushDeckLeader(side, 0, *deck & 0xFFF);
    deck++;
    i = 1;
    do {
        SzData_PushDeck(side, 0, *deck & 0xFFF);
        i++;
        deck++;
    } while (i < 41);
    SzText_Free(0, 1);
    SzText_Free(0, 0);
    SzText_Free(1, -1);
}

typedef struct State_00214BB0 {
    u8 pad[0xFF9C];
    u8 unused0 : 2;
    u8 flag2 : 1;
    u8 flag3 : 1;
    u8 flag4 : 1;
    u8 unused5 : 3;
    u8 tail[3];
} State_00214BB0;

extern u8 profileZeroSide; /* original: gSzData_bRoseFlag */

/* Sets option `option` of side `side`'s profile: 0 and 1 the duel options, 2 the sound output (also applied). */
s32 SzData_SetOption(s32 side, s32 option, s32 on) {
    extern State_00214BB0 saveProfiles[];
    s32 index;
    State_00214BB0 *state;

    if (profileZeroSide == side) {
        index = 0;
    } else {
        index = 1;
    }
    state = &saveProfiles[index];
    switch (option) {
    case 0:
        state->flag2 = on ? 1 : 0;
        break;
    case 1:
        state->flag3 = on ? 1 : 0;
        break;
    case 2:
        state->flag4 = on ? 1 : 0;
        SzSound_SetOutput(state->flag4);
        break;
    default:
        return 0;
    }
    return 1;
}

typedef struct {
    u8 pad[0xFF9C];
    u8 lo : 2;
    u8 flag2 : 1;
    u8 flag3 : 1;
    u8 flag4 : 1;
    u8 hi : 3;
    u8 pad2[3];
} Side_00214D00;

extern Side_00214D00 saveProfiles[]; /* original: gSzData_All */
extern u8 profileZeroSide; /* original: gSzData_bRoseFlag */

/* Option `option` (0..2) of side `side`'s profile, or -1. */
s32 SzData_GetOption(s32 player, s32 option) {
    Side_00214D00 *side;
    s32 idx;

    if (profileZeroSide == player) {
        idx = 0;
    } else {
        idx = 1;
    }
    side = &saveProfiles[idx];
    switch (option) {
    case 0:
        return side->flag2 ? 1 : 0;
    case 1:
        return side->flag3 ? 1 : 0;
    case 2:
        return side->flag4 ? 1 : 0;
    default:
        return -1;
    }
}

/* The trunk entry of card `card` for side `side` of `type` with its flag set as `flag`, or NULL. */
void *SzData_CheckBag(s32 player, s32 card, s32 typeIn, s32 flag) {
    typedef struct {
        u32 id : 31;
        u32 active : 1;
        u32 value : 30;
        u32 type : 2;
    } Entry_00214DD0;
    s32 side;
    Entry_00214DD0 *entry;
    s32 count;

    if (player < 0 || player >= 2) {
        return NULL;
    }
    if (card == 0x29F) {
        card = 0x3E7;
    }
    if (card < 0 || card >= 0x356) {
        return NULL;
    }
    if (profileZeroSide == player) {
        side = 0;
    } else {
        side = 1;
    }
    entry = (Entry_00214DD0 *)((u8 *)saveProfiles + side * 0xFFA0 + card * 0x4C);
    count = 9;
    while (count--) {
        if (entry->id != 0 && entry->type == typeIn &&
            (entry->active != 0) == (flag == 1)) {
            return entry;
        }
        entry++;
    }
    return NULL;
}

/* Trunk entry `index` (0..8) of card `card` for side `side`, or NULL. */
void *SzData_GetCardInfo(s32 side, s32 card, s32 index) {
    s32 bank;
    u8 *base;

    if (profileZeroSide == side) {
        bank = 0;
    } else {
        bank = 1;
    }
    base = (u8 *)saveProfiles + bank * 0xFFA0;
    if ((side < 0) || (side >= 2)) {
        return NULL;
    }
    if ((index < 0) || (index >= 9)) {
        return NULL;
    }
    if (card == 0x29F) {
        card = 0x3E7;
    }
    if ((card < 0) || (card >= 0x356)) {
        return NULL;
    }
    return base + card * 0x4C + index * 8;
}

#include "common.h"

/* Where the line start..end crosses `plane` into `out`. */
void Ex3d_IntersectP(void *planeIn, void *startIn, void *endIn, void *outIn) {
    f32 *plane = planeIn;
    f32 *start = startIn;
    f32 *end = endIn;
    f32 *out = outIn;
    f32 numerator;
    f32 denominator;
    f32 magnitude;
    f32 t;

    numerator = -plane[3] - (plane[0] * start[0] + plane[1] * start[1] + plane[2] * start[2]);
    denominator = plane[0] * (end[0] - start[0]) + plane[1] * (end[1] - start[1]) + plane[2] * (end[2] - start[2]);
    magnitude = denominator >= 0.0f ? denominator : -denominator;
    if (magnitude < 0.000001f) {
        denominator = 0.000001f;
    }
    t = numerator / denominator;
    out[0] = start[0] + t * (end[0] - start[0]);
    out[1] = start[1] + t * (end[1] - start[1]);
    out[2] = start[2] + t * (end[2] - start[2]);
    out[3] = 1.0f;
}

typedef struct Vertex_00206530 {
    f32 position[4];
    u8 padding[8];
    u8 color[4];
    f32 weight;
    f32 uv[2];
} Vertex_00206530;

typedef struct PackedUV_00206530 {
    u16 u : 14;
    u16 flags_u : 2;
    u16 v : 14;
    u16 flags_v : 2;
} PackedUV_00206530;

/* Splits a polygon's vertices against a plane (`factor` weights the cut). */
void Ex3d_DivideN(void *src, void *dstIn, s32 flags, void *plane, f32 factor) {
    ((Vertex_00206530 *)plane)->position[0] = ((Vertex_00206530 *)src)->position[0] +
        factor * (((Vertex_00206530 *)dstIn)->position[0] - ((Vertex_00206530 *)src)->position[0]);
    ((Vertex_00206530 *)plane)->position[1] = ((Vertex_00206530 *)src)->position[1] +
        factor * (((Vertex_00206530 *)dstIn)->position[1] - ((Vertex_00206530 *)src)->position[1]);
    ((Vertex_00206530 *)plane)->position[2] = ((Vertex_00206530 *)src)->position[2] +
        factor * (((Vertex_00206530 *)dstIn)->position[2] - ((Vertex_00206530 *)src)->position[2]);
    ((Vertex_00206530 *)plane)->position[3] = ((Vertex_00206530 *)src)->position[3] +
        factor * (((Vertex_00206530 *)dstIn)->position[3] - ((Vertex_00206530 *)src)->position[3]);
    if (flags & 1) {
        ((Vertex_00206530 *)plane)->color[0] = func_001A23B0(
            (f32)(u32)((Vertex_00206530 *)src)->color[0] + factor *
            (s32)(((Vertex_00206530 *)dstIn)->color[0] - ((Vertex_00206530 *)src)->color[0]));
        ((Vertex_00206530 *)plane)->color[1] = func_001A23B0(
            (f32)(u32)((Vertex_00206530 *)src)->color[1] + factor *
            (s32)(((Vertex_00206530 *)dstIn)->color[1] - ((Vertex_00206530 *)src)->color[1]));
        ((Vertex_00206530 *)plane)->color[2] = func_001A23B0(
            (f32)(u32)((Vertex_00206530 *)src)->color[2] + factor *
            (s32)(((Vertex_00206530 *)dstIn)->color[2] - ((Vertex_00206530 *)src)->color[2]));
        ((Vertex_00206530 *)plane)->color[3] = func_001A23B0(
            (f32)(u32)((Vertex_00206530 *)src)->color[3] + factor *
            (s32)(((Vertex_00206530 *)dstIn)->color[3] - ((Vertex_00206530 *)src)->color[3]));
        ((Vertex_00206530 *)plane)->weight = ((Vertex_00206530 *)src)->weight +
            factor * (((Vertex_00206530 *)dstIn)->weight - ((Vertex_00206530 *)src)->weight);
    }
    if (flags & 2) {
        ((Vertex_00206530 *)plane)->uv[0] = ((Vertex_00206530 *)src)->uv[0] +
            factor * (((Vertex_00206530 *)dstIn)->uv[0] - ((Vertex_00206530 *)src)->uv[0]);
        ((Vertex_00206530 *)plane)->uv[1] = ((Vertex_00206530 *)src)->uv[1] +
            factor * (((Vertex_00206530 *)dstIn)->uv[1] - ((Vertex_00206530 *)src)->uv[1]);
    }
    if (flags & 0x10) {
        PackedUV_00206530 *src0 = (PackedUV_00206530 *)((u8 *)src + 0x20);
        PackedUV_00206530 *src1 = (PackedUV_00206530 *)((u8 *)dstIn + 0x20);
        PackedUV_00206530 *dst = (PackedUV_00206530 *)((u8 *)plane + 0x20);
        s32 u = src0->u;
        s32 v;

        dst->u = u + func_001A23B0(factor * (s32)(src1->u - u));
        v = src0->v;
        dst->v = v + func_001A23B0(factor * (s32)(src1->v - v));
    }
}

/* The plane through three points. */
static inline void surface_00206830(f32 *v0, f32 *v1, f32 *v2, f32 *plane) {
    plane[0] = v0[1] * (v1[2] - v2[2])
             + v1[1] * (v2[2] - v0[2])
             + v2[1] * (v0[2] - v1[2]);
    plane[1] = v0[2] * (v1[0] - v2[0])
             + v1[2] * (v2[0] - v0[0])
             + v2[2] * (v0[0] - v1[0]);
    plane[2] = v0[0] * (v1[1] - v2[1])
             + v1[0] * (v2[1] - v0[1])
             + v2[0] * (v0[1] - v1[1]);
    plane[3] = v0[0] * (v1[2] * v2[1] - v1[1] * v2[2])
             + v0[1] * (v1[0] * v2[2] - v1[2] * v2[0])
             + v0[2] * (v1[1] * v2[0] - v1[0] * v2[1]);
    plane[4] = func_001A6C60(plane[0] * plane[0]
                            + plane[1] * plane[1]
                            + plane[2] * plane[2]);
}

/* Builds the six view clip planes from the current camera. */
void Ex3d_InitClipPlane(void)
{
    f32 near;
    f32 far;
    f32 cx;
    f32 cy;
    f32 dist;
    f32 v[5][3];
    f32 nw;
    f32 w;
    f32 f;
    f32 *planes = (f32 *)viewClipPlanes;
    f32 *p;

    RhView_GetClipZ(&near, &far);
    RhView_GetScreenCenter(&cx, &cy);
    RhView_GetScreenDist(&dist);
    cx += 10.0f;
    cy += 10.0f;
    nw = -cx;
    w = cx;
    f = dist;
    v[0][0] = 0.0f; v[0][1] = 0.0f; v[0][2] = 0.0f;
    v[1][0] = nw; v[1][1] = nw;
    v[2][1] = nw;
    v[4][0] = nw;
    v[2][0] = v[3][0] = v[3][1] = v[4][1] = w;
    v[1][2] = v[2][2] = v[3][2] = v[4][2] = f;
    p = (f32 *)viewClipPlanes;
    surface_00206830(v[0], v[1], v[2], p);
    p = planes + 5;
    surface_00206830(v[0], v[4], v[1], p);
    p = planes + 10;
    surface_00206830(v[0], v[3], v[4], p);
    p = planes + 15;
    surface_00206830(v[0], v[2], v[3], p);
    v[1][2] = near; v[2][2] = near; v[4][2] = near;
    p = planes + 20;
    surface_00206830(v[1], v[2], v[4], p);
    v[1][2] = far; v[2][2] = far; v[4][2] = far;
    p = planes + 25;
    surface_00206830(v[4], v[2], v[1], p);
}

/* Clips a polygon against the six view planes. */
void Ex3d_ViewClip(s32 count, s32 vertices, s32 unused, s32 output, s32 flags) {
    Ex3d_Clipping(6, viewClipPlanes, count, vertices, unused, output, flags);
}

typedef union {
    f32 f[12];
    __int128 q[3];
} Vertex_00206D30;

typedef struct {
    f32 u;
    f32 v;
} UV_00206D30;

/* Clips a polygon of `count` vertices against `planeCount` planes into `outputArg`; returns the new count. */
s32 Ex3d_Clipping(s32 planeCount, void *planeArg, s32 count, s32 verticesArg,
                  s32 unused, s32 outputArg, s32 flags) {
    f32 *plane = planeArg;
    Vertex_00206D30 intersection;
    UV_00206D30 saved;
    s32 textured;
    s32 planeIndex;
    s32 i;
    u32 outputCount;

    if (count < 2) {
        return count;
    }
    textured = flags & 1;
    if (textured == 0) {
        saved = *(UV_00206D30 *)&((Vertex_00206D30 *)verticesArg)[0].f[6];
    }
    if ((u32)count > 0x155U) {
        count = 0x155;
    }

    for (planeIndex = 0; planeIndex < planeCount; planeIndex++, plane += 5) {
        outputCount = 0;
        for (i = 0; i < count; i++) {
            Vertex_00206D30 *current = &((Vertex_00206D30 *)verticesArg)[i];
            Vertex_00206D30 *next = &((Vertex_00206D30 *)verticesArg)[(i + 1) % count];
            f32 distance = (plane[3] + (plane[0] * current->f[0] +
                            plane[1] * current->f[1] + plane[2] * current->f[2])) / plane[4];
            f32 nextDistance = (plane[3] + (plane[0] * next->f[0] +
                                plane[1] * next->f[1] + plane[2] * next->f[2])) / plane[4];

            if (distance < 0.0f && nextDistance < 0.0f) {
                continue;
            }
            if (!(distance < 0.0f) && !(nextDistance < 0.0f)) {
                ((Vertex_00206D30 *)outputArg)[outputCount++] = *current;
            } else {
                Ex3d_DivideN(current, next, flags, &intersection,
                    (distance >= 0.0f ? distance : -distance) /
                    ((distance >= 0.0f ? distance : -distance) +
                     (nextDistance >= 0.0f ? nextDistance : -nextDistance)));
                if (!(distance < 0.0f)) {
                    ((Vertex_00206D30 *)outputArg)[outputCount++] = *current;
                }
                ((Vertex_00206D30 *)outputArg)[outputCount++] = intersection;
            }
            if (outputCount >= 0x155U) {
                outputCount = 0x155;
                break;
            }
        }
        if (count < 3 && count < (s32)outputCount) {
            outputCount = count;
        }
        for (i = 0; i < (s32)outputCount; i++) {
            ((Vertex_00206D30 *)verticesArg)[i] = ((Vertex_00206D30 *)outputArg)[i];
        }
        count = outputCount;
    }
    if (textured == 0) {
        *(UV_00206D30 *)&((Vertex_00206D30 *)verticesArg)[0].f[6] = saved;
    }
    return count;
}

typedef struct Vertex_002070F0 {
    f32 position[4];
    u8 padding[0x20];
} Vertex_002070F0;

/* Transforms a node's `count` vertices by `matrix` (local to view); its average depth through `depth`. */
s32 Ex3d_NodeL2V(void *matrix, s32 count, void *vertices, s32 normals, void *out, s32 flags, f32 *depth) {
    f32 identity[16];
    s32 result;
    s32 i;
    Vertex_002070F0 *vertex;
    f32 sum;

    sum = 0.0f;
    if (matrix == NULL) {
        RhView_GetWorldViewMatrix(identity);
        matrix = identity;
    }
    RhGeom_PushMatrix((s32)matrix);
    vertex = vertices;
    for (i = 0; i < count; i++) {
        vertex[i].position[3] = 1.0f;
        RhGeom_MulMatrixVector(&vertex[i], NULL, &vertex[i]);
        sum += vertex[i].position[2];
    }
    RhGeom_PopMatrix();
    if (flags >= 0) {
        result = Ex3d_Clipping(6, viewClipPlanes, count, (s32)vertices, normals, (s32)out, flags);
    }
    if (depth != NULL) {
        *depth = sum / (f32)result;
    }
    return result;
}

typedef union PackedXYZ_00207230 {
    struct {
        s16 x;
        s16 y;
        u8 depth[3];
        u8 flags;
    } components;
    struct {
        u64 xy : 32;
        u64 z : 24;
        u64 flags : 8;
    } bits;
} PackedXYZ_00207230;

typedef struct Vertex_00207230 {
    f32 position[4];
    PackedXYZ_00207230 xyz;
    u8 padding[0x18];
} Vertex_00207230;

/* Projects a node's `count` view-space vertices to the screen. */
void Ex3d_NodeV2S(void *matrix, s32 count, void *vertices) {
    f32 identity[16];
    s32 i;
    PackedXYZ_00207230 *xyz;
    Vertex_00207230 *vertex;
    f32 reciprocal;

    vertex = vertices;
    if (matrix == NULL) {
        RhView_GetViewScreenMatrix(identity);
        matrix = identity;
    }
    RhGeom_PushMatrix((s32)matrix);
    for (i = 0; i < count; i++, vertex++) {
        xyz = &vertex->xyz;
        vertex->position[3] = 1.0f;
        RhGeom_MulMatrixVector(vertex, NULL, vertex);
        reciprocal = 1.0f / vertex->position[3];
        xyz->components.x = func_001A23B0(16.0f * (vertex->position[0] * reciprocal));
        xyz->components.y = func_001A23B0(16.0f * (vertex->position[1] * reciprocal));
        xyz->bits.z = (u32)func_001A23B0(vertex->position[2] * reciprocal);
        xyz->components.flags = 0;
    }
    RhGeom_PopMatrix();
}

/* Starts the primitive system. */
void ExInitPrim(void) {
    RhGeom_PushMatrix(0);
    ExClearOt(mainDrawList, 0x01E08000, 0xC);
}

/* Ends the primitive system. */
void ExTermPrim(void) {
    ExBindPrim(mainDrawList);
    RhGeom_PopMatrix();
}

typedef struct Tag_002073D0 {
    u16 qwc;
    u8 pad2;
    u8 id;
    s32 next;
    u32 vif0;
    u32 vif1;
} Tag_002073D0;

typedef struct Node_002073D0 {
    u16 qwc;
    u16 mark;
    struct Node_002073D0 *next;
} Node_002073D0;

typedef struct Context_002073D0 {
    Node_002073D0 *table;
    Tag_002073D0 *start;
    Tag_002073D0 *head;
    s32 depth;
} Context_002073D0;

/* Starts draw list `ot` with a table of 2^`depth` depth slots at `table`, and the GS register set-up packet. */
void ExClearOt(u8 *ot, s32 table, s32 depth) {
    extern u8 gsRegisterSets[];
    s32 count;
    Node_002073D0 *node;
    u64 *packet;
    Context_002073D0 *ctx;

    packet = (u64 *)RhBase_GetVifPacketArea();
    count = 1 << depth;
    packet[1] = 0;
    packet[0] = 0;
    ctx = (Context_002073D0 *)ot;
    ctx->start = (Tag_002073D0 *)packet;
    packet[2] = 0x100000000000800EULL;
    packet[3] = 0xE;
    packet = RhMem_CopyMemory16(packet + 4, gsRegisterSets, 0xE);
    ctx->start->qwc = 0xF;
    ctx->start->id = 0x10;
    ctx->start->vif0 = 0x11000000;
    ctx->start->vif1 = ctx->start->qwc | 0x51000000;
    packet[1] = 0;
    packet[0] = 0;
    ctx->head = (Tag_002073D0 *)packet;
    ctx->head->id = 0x10;
    RhBase_SetVifPacketArea((s32)(packet + 2));
    ctx->depth = depth;
    ctx->table = (Node_002073D0 *)table;
    node = (Node_002073D0 *)table;
    node += count - 1;
    while (--count != 0) {
        node->next = node - 1;
        node->mark = 7;
        node->qwc = 0;
        node--;
    }
    node->next = (Node_002073D0 *)-1;
    node->mark = 7;
    node->qwc = 0;
}

/* The current draw list. */
u8 *ExGetMyOT(void) {
    return mainDrawList;
}

typedef struct Node_00207510 {
    u16 unused0;
    u8 unused2;
    u8 tag;
    struct Node_00207510 *next;
} Node_00207510;

typedef struct Context_00207510 {
    Node_00207510 *table;
    s32 unused4;
    Node_00207510 *head;
    s32 depth;
} Context_00207510;

/* Links the used depth slots of draw list `ot` into one DMA chain, back to front. */
void ExBindPrim(void *ot) {
    Node_00207510 *tail;
    Node_00207510 *node;
    Node_00207510 *next;
    Context_00207510 *ctx = ot;

    tail = NULL;
    node = ctx->table + ((1 << ctx->depth) - 1);
    do {
        next = node->next;
        if (*(u16 *)((u8 *)node + 2) != 7) {
            if (tail != NULL) {
                if (tail->tag == 0x50) {
                    tail->next = (Node_00207510 *)((u8 *)tail + 0x20);
                    tail = (Node_00207510 *)((u8 *)tail + 0x10);
                }
                tail->tag = 0x20;
                tail->next = node;
            } else {
                ctx->head->tag = 0x20;
                ctx->head->next = node;
            }
            tail = node;
        }
        node = next;
    } while (next != (Node_00207510 *)-1);
    if (tail != NULL) {
        if (tail->tag == 0x50) {
            tail->next = (Node_00207510 *)((u8 *)tail + 0x20);
            tail = (Node_00207510 *)((u8 *)tail + 0x10);
        }
        tail->tag = 0x20;
        tail->next = (Node_00207510 *)RhBase_GetVifPacketArea();
    }
}

/* Adds primitive `prim` to draw list `ot` at depth `z`. */
void ExSortPrim(s32 prim, s32 ot, s32 z) {
    RhBase_SetVifPacketArea(ExSortPrim_Pipe(RhBase_GetVifPacketArea(), prim, ot, z));
}

typedef struct {
    u16 count;
    u16 flags;
    u32 padding;
    u64 registers;
    u64 data[1];
} Source_00207650;

typedef struct {
    u32 tag;
    void *next;
} Link_00207650;

typedef struct {
    Link_00207650 *links;
    u8 padding[8];
    s32 shift;
} Table_00207650;

typedef struct {
    u64 lower : 32;
    u64 enabled : 1;
    u64 upper : 31;
} Register_00207650;

typedef struct {
    u16 loops : 15;
    u16 end : 1;
} Tag_00207650;


/* Writes primitive `prim` into the packet at `cursor`, linked into draw list `ot` at depth `z` (or sent straight
   away for no list). */
s32 ExSortPrim_Pipe(s32 cursorIn, s32 prim, s32 ot, s32 z) {
    extern u8 gsRegisterSets[];
    u64 *cursor;
    u64 *start;
    u64 registers;
    s32 flags;
    s32 context;
    u64 *data;
    s32 replace;
    u16 count;
    s32 texture;
    s32 alpha;
    s32 alphaMask;
    s32 contextMask;
    u32 primitive;
    s32 restore;
    s32 i;
    u64 reg;
    u16 length;
    u64 prim64;
    Register_00207650 saved;

    cursor = (u64 *)cursorIn;
    start = cursor;
    registers = ((Source_00207650 *)prim)->registers;
    count = ((Source_00207650 *)prim)->count;
    data = ((Source_00207650 *)prim)->data;
    flags = ((Source_00207650 *)prim)->flags;
    alphaMask = flags & 0x200;
    contextMask = flags & 0x1000;
    if (alphaMask != 0) {
        alpha = 1;
    } else {
        alpha = 0;
    }
    if (contextMask != 0) {
        context = 1;
    } else {
        context = 0;
    }
    primitive = flags & 0xF;
    if (primitive == 7) {
        return cursorIn;
    }
    cursor[1] = 0;
    cursor[0] = 0;
    *((u8 *)cursor + 3) = 0x10;
    if (ot != 0) {
        Table_00207650 *table = (Table_00207650 *)ot;
        s32 limit = 1 << table->shift;
        if (flags & 0x8000) {
            z = limit - 1;
        } else if ((u32)(limit - 2) < (u32)z) {
            z = limit - 2;
        }
        *(void **)((u8 *)cursor + 4) =
            *(void **)((s32)table->links + z * 8 + 4);
        *(void **)((s32)table->links + z * 8 + 4) = cursor;
    }
    prim64 = primitive;
    cursor[2] = 0x1000000000008000ULL;
    cursor[3] = 0xE;
    texture = flags & 0x20;
    replace = flags & 0x800;
    cursor[4] = ((s64)((flags & 0x2000) ? 1 : 0) << 10) |
        (((s64)(contextMask ? 1 : 0) << 9) |
        (((s64)(replace ? 1 : 0) << 8) |
        (((s64)((flags & 0x400) ? 1 : 0) << 7) |
        (((s64)(alphaMask ? 1 : 0) << 6) |
        (((s64)((flags & 0x100) ? 1 : 0) << 5) |
        (prim64 |
        ((s64)((flags & 0x10) ? 1 : 0) * 8) |
        ((s64)(texture ? 1 : 0) * 16)))))));
    cursor[5] = 0;
    cursor[6] = (s64)(alpha ? 1 : 0) | 0x5000C;
    cursor[7] = (s64)(context + 0x47);
    cursor += 8;
    if (alphaMask != 0) {
        cursor[0] = data[(u16)count];
        cursor[1] = (s64)(context + 0x42);
        cursor += 2;
    }
    if (texture != 0) {
        u64 *extra = &data[(u16)count];
        cursor[0] = extra[1];
        cursor[1] = (s64)(context + 6);
        cursor[2] = extra[2];
        cursor[3] = (s64)(context + 0x14);
        cursor += 4;
        if (flags & 0x4000) {
            cursor[0] = extra[3];
            cursor[1] = (s64)(context + 8);
            cursor += 2;
        }
    }
    restore = flags & 0x8000;
    if (restore != 0) {
        RhBase_GetZBufInfo(&saved);
        saved.enabled = 0;
        cursor[0] = *(u64 *)&saved;
        cursor[1] = (s64)(context + 0x4E);
        cursor += 2;
    }
    for (i = 0; i < (u16)count; i++) {
        reg = registers & 0xF;
        if (replace != 0 && reg == 2) {
            reg = 3;
        }
        registers >>= 4;
        cursor[0] = *data;
        cursor[1] = reg;
        cursor += 2;
        data++;
    }
    if (texture != 0 && (flags & 0x4000)) {
        u64 *extra = (u64 *)(gsRegisterSets + context * 0x70);
        cursor[0] = extra[8];
        cursor[1] = extra[9];
        cursor += 2;
    }
    if (restore != 0) {
        saved.enabled = 1;
        cursor[0] = *(u64 *)&saved;
        cursor[1] = (s64)(context + 0x4E);
        cursor += 2;
    }
    length = ((cursor - start) >> 1) - 1;
    *(u16 *)start = length;
    *(u32 *)((u8 *)start + 8) = 0x11000000;
    *(u32 *)((u8 *)start + 0xC) = length | 0x51000000;
    ((Tag_00207650 *)((u8 *)start + 0x10))->loops = length - 1;
    return (s32)cursor;
}

typedef int DotrDrawWord;
struct DotrDrawPair {
    long unknown_00;
    long unknown_08;
};
extern struct DotrDrawPair D_00293D80_207aa0[][7];
struct DotrDrawFields {
    unsigned short low_9 : 9;
    unsigned short unknown_bits_9_15 : 7;
    unsigned char unknown_02;
    unsigned char low_4 : 4;
    unsigned char unknown_bits_4_7 : 4;
};
typedef struct DotrDrawSlot {
    int unknown_00;
    struct DotrDrawNode *head;
} DotrDrawSlot;
typedef struct DotrDrawNode {
    int unknown_00;
    struct DotrDrawNode *next;
} DotrDrawNode;
typedef struct DotrDrawChain {
    DotrDrawSlot *slots;
    int unknown_04;
    int unknown_08;
    int shift;
} DotrDrawChain;
struct DotrSortHeader {
    unsigned short count;
    unsigned short type;
    int unknown_04;
    unsigned long regs;
    unsigned long data[4];
};
struct DotrSortVertex {
    float unknown_00[3];
    float q;
    unsigned long xyz;
    unsigned long colour;
    unsigned long uv;
    unsigned long unknown_28;
};
struct DotrSortZBuf {
    struct DotrDrawFields fields;
    unsigned char mask : 1;
    unsigned char unknown_bits_1_7 : 7;
    unsigned char unknown_05[3];
};
struct DotrSortTag {
    unsigned short size;
    unsigned char unknown_02;
    unsigned char kind;
    int next;
    int unknown_08;
    int unknown_0c;
    unsigned short loops : 15;
    unsigned short end : 1;
};

/* Writes a node's `count` vertices as primitives into the packet, linked into a draw list at depth `z`. */
int ExSortNode_Pipe(int cursor, void *header_v, int count, s32 vertices_v, void *chain_v, int z)
{
    struct DotrSortHeader * header = header_v;
    struct DotrSortVertex * vertices = (struct DotrSortVertex *)vertices_v;
    DotrDrawChain * chain = chain_v;
    unsigned long *p = (unsigned long *)cursor;
    int type = header->type;
    struct DotrSortVertex *vertex = vertices;
    int textured = (type & 0x200) ? 1 : 0;
    int context = (type & 0x1000) ? 1 : 0;
    unsigned long *start = p;
    struct DotrSortZBuf zbuf;
    int depth;
    int i;
    int size;
    unsigned long *q;
    struct DotrDrawPair *row;

    if ((type & 0xf) == 7) {
        return cursor;
    }
    if (count <= 0) {
        return cursor;
    }
    p[1] = 0;
    p[0] = 0;
    ((struct DotrSortTag *)p)->kind = 0x10;
    if (chain) {
        size = 1 << chain->shift;
        if (type & 0x8000) {
            z = size - 1;
        } else if ((unsigned int)(size - 2) < (unsigned int)z) {
            z = size - 2;
        }
        
        z <<= 3;
        ((struct DotrSortTag *)p)->next = (int)(DotrDrawWord)((DotrDrawSlot *)((DotrDrawWord)chain->slots + z))->head;
        ((DotrDrawSlot *)((DotrDrawWord)chain->slots + z))->head = (DotrDrawNode *)p;
    }
    p[2] = 0x1000000000008000;
    p[3] = 0xe;
    p[4] = (unsigned int)(type & 0xf) | ((long)(int)((type & 0x10) ? 1 : 0) << 3) | ((long)(int)((type & 0x20) ? 1 : 0) << 4)
        | ((long)(int)((type & 0x100) ? 1 : 0) << 5) | ((long)(int)((type & 0x200) ? 1 : 0) << 6) | ((long)(int)((type & 0x400) ? 1 : 0) << 7)
        | ((long)(int)((type & 0x800) ? 1 : 0) << 8) | ((long)(int)((type & 0x1000) ? 1 : 0) << 9) | ((long)(int)((type & 0x2000) ? 1 : 0) << 10);
    p[5] = 0;
    p[6] = (long)(int)(textured ? 1 : 0) | 0x5000c;
    p[7] = context + 0x47;
    p += 8;
    if (type & 0x200) {
        p[0] = header->data[0];
        p[1] = context + 0x42;
        p += 2;
    }
    if (type & 0x20) {
        p[0] = header->data[1];
        p[1] = context + 6;
        p[2] = header->data[2];
        p[3] = context + 0x14;
        p += 4;
        if (type & 0x4000) {
            p[0] = header->data[3];
            p[1] = context + 8;
            p += 2;
        }
    }
    depth = type & 0x8000;
    if (depth) {
        RhBase_GetZBufInfo(&zbuf.fields);
        zbuf.mask = 0;
        p[0] = *(unsigned long *)&zbuf;
        p[1] = context + 0x4e;
        p += 2;
    }
    for (i = 0; i < count; i++, vertex++) {
        if (i == 0 || (type & 0x10)) {
            q = p;
            p[0] = vertex->colour;
            p[1] = 1;
            p += 2;
            if (type & 0x10) {
                ((float *)q)[1] = 1.0f / vertex->q;
            }
        }
        if (type & 0x20) {
            q = p;
            p[0] = vertex->uv;
            p[1] = (type & 0x800) ? 3 : 2;
            p += 2;
            if (!(type & 0x800) && (type & 0x10)) {
                ((float *)q)[0] /= vertex->q;
                ((float *)q)[1] /= vertex->q;
            }
        }
        p[0] = vertex->xyz;
        p[1] = 4;
        p += 2;
    }
    if ((type & 0x20) && (type & 0x4000)) {
        row = D_00293D80_207aa0[context];
        p[0] = row[4].unknown_00;
        p[1] = row[4].unknown_08;
        p += 2;
    }
    if (depth) {
        zbuf.mask = 1;
        p[0] = *(unsigned long *)&zbuf;
        p[1] = context + 0x4e;
        p += 2;
    }
    size = ((p - start) >> 1) - 1;
    ((struct DotrSortTag *)start)->size = size;
    ((struct DotrSortTag *)start)->unknown_08 = 0x11000000;
    ((struct DotrSortTag *)start)->unknown_0c = (size & 0xffff) | 0x51000000;
    ((struct DotrSortTag *)start)->loops = (size & 0xffff) - 1;
    return (DotrDrawWord)p;
}

/* Starts an anchor (a group of primitives sorted together). */
s32 ExSetAnchor(void) {
    s32 cursor;

    cursor = RhBase_GetVifPacketArea();
    RhBase_SetVifPacketArea(ExSetAnchor_Pipe(cursor));
    return cursor;
}

/* Writes an anchor's head into the packet at `cursor`. */
s32 ExSetAnchor_Pipe(s32 cursor) {
    ((s64 *)cursor)[3] = 0;
    ((s64 *)cursor)[2] = 0;
    ((s64 *)cursor)[1] = 0;
    ((s64 *)cursor)[0] = 0;
    ((s8 *)cursor)[3] = 0x50;
    ((s8 *)cursor)[0x13] = 0x20;
    return cursor + 0x20;
}

/* Links an anchor's group into draw list `ot` at depth `z`. */
void ExSortAnchor(s32 anchor, s32 ot, s32 z) {
    RhBase_SetVifPacketArea(ExSortAnchor_Pipe(RhBase_GetVifPacketArea(), anchor, ot, z));
}

/* Closes the anchor started at `anchor` and links its group into draw list `ot` at depth `z`. */
s32 ExSortAnchor_Pipe(s32 cursor, s32 anchor, s32 ot, s32 z) {
    s32 offset;
    u32 limit;

    limit = (1 << *(s32 *)(ot + 0xC)) - 2;
    if (limit < (u32) z) {
        z = limit;
    }
    offset = z * 8;
    *(s32 *)(anchor + 4) = *(s32 *)(*(s32 *)ot + offset + 4);
    *(s32 *)(*(s32 *)ot + offset + 4) = anchor;
    *(s64 *)(cursor + 8) = 0;
    *(s64 *)cursor = 0;
    *(s8 *)(cursor + 3) = 0x60;
    return cursor + 0x10;
}

/* Draws the frame buffer over itself (motion blur). */
void ExSortDispBlur(s32 ot, s32 z, s32 frame, s32 alpha, s32 color) {
    RhBase_SetVifPacketArea(ExSortDispBlur_Pipe(RhBase_GetVifPacketArea(), ot, z, frame, alpha, color));
}

typedef struct {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} Color_00208110;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Xyzf_00208110;

typedef struct {
    u16 count;
    u16 kind;
    u32 flags;
    u64 regs;
} Header_00208110;

typedef struct {
    Header_00208110 header;
    u8 r;
    u8 g;
    u8 b;
    u8 a;
    f32 q;
    f32 s0;
    f32 t0;
    Xyzf_00208110 v0;
    f32 s1;
    f32 t1;
    Xyzf_00208110 v1;
    u64 extra[4];
} Packet_00208110;

/* Draws the frame buffer `frame` over the screen with `alpha` and `color` (motion blur). */
s32 ExSortDispBlur_Pipe(s32 cursor, s32 ot, s32 z, s32 frame, s32 alpha, s32 colorIn) {
    extern Color_00208110 D_00293ED0;
    extern s32 ExAssignAlpha();
    Color_00208110 def;
    Packet_00208110 packet;
    u8 *color;

    def = D_00293ED0;
    ((Header_00208110 *)&packet)->kind = 0x26;
    ((Header_00208110 *)&packet)->count = 5;
    ((Header_00208110 *)&packet)->regs = 0x42421;
    ((Header_00208110 *)&packet)->flags = 0;
    color = (u8 *)colorIn;
    if (color == NULL) {
        color = (u8 *)&def;
    }
    packet.r = color[2];
    packet.g = color[1];
    packet.b = color[0];
    packet.a = color[3];
    packet.q = 1.0f;
    packet.v0.x = 0x6BF8;
    packet.v0.y = 0x71F8;
    packet.v0.z = 0xFFFFF7;
    packet.v0.fog = 0;
    packet.v1.x = 0x93F8;
    packet.v1.y = 0x8DF8;
    packet.v1.z = 0xFFFFF7;
    packet.v1.fog = 0;
    packet.s0 = 0.0f;
    packet.t0 = 0.0f;
    packet.s1 = 0.625f;
    packet.t1 = 0.875f;
    ExAssignAlpha(&packet, alpha);
    ExAssignFrameBuffer(&packet, frame);
    return ExSortPrim_Pipe(cursor, (s32)&packet, ot, z);
}

typedef struct {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} Color_00208280;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Xyzf_00208280;

typedef struct {
    u16 count;
    u16 kind;
    u32 flags;
    u64 regs;
} Header_00208280;

typedef struct {
    Header_00208280 header;
    u8 r;
    u8 g;
    u8 b;
    u8 a;
    f32 q;
    f32 s0;
    f32 t0;
    Xyzf_00208280 v0;
    f32 s1;
    f32 t1;
    Xyzf_00208280 v1;
    u64 extra[1];
} Packet_00208280;

typedef struct {
    u8 pad0[4];
    u8 : 2;
    u8 tcc : 1;
    u8 : 5;
    u8 pad5[3];
} Tex0_00208280;

typedef struct {
    Tex0_00208280 tex0;
    u64 tex1;
    u64 clamp;
} Regs_00208280;

/* Draws a copy of the frame buffer `frame` moved by (dx, dy) over the screen in `color` (soft focus). */
s32 ExSortSoftFocus_Pipe(s32 cursor, s32 ot, s32 z, s32 frame, s32 dx, s32 dy, u8 *color) {
    extern Color_00208280 D_00293ED8;
    extern s32 ExFrameBuffer2Texture_Pipe();
    Color_00208280 def;
    Packet_00208280 packet;
    Regs_00208280 regs;
    s32 obj;

    def = D_00293ED8;
    ((Header_00208280 *)&packet)->kind = 0x26;
    ((Header_00208280 *)&packet)->count = 5;
    ((Header_00208280 *)&packet)->regs = 0x42421;
    ((Header_00208280 *)&packet)->flags = 0;
    ExAssignAlpha(&packet, 0x44 | ((s64)0x80 << 32));
    if (color == NULL) {
        color = (u8 *)&def;
    }
    packet.r = color[2];
    packet.g = color[1];
    packet.b = color[0];
    packet.a = color[3];
    packet.q = 1.0f;
    packet.v0.x = dx + 0x6BF8;
    packet.v0.y = dy + 0x71F8;
    packet.v0.z = 0xFFFFFF;
    packet.v0.fog = 0;
    packet.v1.x = dx + 0x93F8;
    packet.v1.y = dy + 0x8DF8;
    packet.v1.z = 0xFFFFFF;
    packet.v1.fog = 0;
    packet.s0 = 0.0f;
    packet.t0 = 0.0f;
    packet.s1 = 0.625f;
    packet.t1 = 0.875f;
    cursor = RhText_SetTextureFlush(cursor);
    obj = RhText_SetTextureFlush(ExFrameBuffer2Texture_Pipe(cursor, RhBase_GetUserGsAddress(), frame, &regs.tex0, &regs.tex1));
    regs.tex0.tcc = 1;
    return ExSortPrim_Pipe(obj, (s32)&packet, ot, z);
}

/* Flushes the GS texture cache. */
void ExFlushTexture(void) {
    RhBase_SetVifPacketArea(RhText_SetTextureFlush(RhBase_GetVifPacketArea()));
}

/* Turns the z-buffer test on or off. */
void ExZBufferMode(s32 on) {
    RhBase_SetVifPacketArea(RhBase_SetZBufferMode(RhBase_GetVifPacketArea(), on));
}

/* Sets the GS texture clamp register to `clamp`. */
s32 ExClampMode_Pipe(s32 cursor, s64 clamp) {
    *(s64 *)((u8 *)cursor + 8) = 0;
    *(s64 *)cursor = 0;
    *(s8 *)((u8 *)cursor + 3) = 0x10;
    *(s64 *)((u8 *)cursor + 0x10) = 0x1000000000008001LL;
    *(s64 *)((u8 *)cursor + 0x18) = 0xE;
    *(s64 *)((u8 *)cursor + 0x20) = clamp;
    *(s64 *)((u8 *)cursor + 0x28) = 8;
    *(s16 *)cursor = 2;
    *(s32 *)((u8 *)cursor + 8) = 0x11000000;
    *(s32 *)((u8 *)cursor + 0xC) = 0x51000002;
    return cursor + 0x30;
}

/* Turns GS dithering on or off. */
void *ExDitherMode_Pipe(void *cursor, s32 on) {
    *(s64 *)((u8 *)cursor + 8) = 0;
    *(s64 *)cursor = 0;
    *((u8 *)cursor + 3) = 0x10;
    *(u64 *)((u8 *)cursor + 0x10) = 0x1000000000008001ULL;
    *(s64 *)((u8 *)cursor + 0x18) = 0xE;
    *(s64 *)((u8 *)cursor + 0x20) = on;
    *(s64 *)((u8 *)cursor + 0x28) = 0x45;
    *(u16 *)cursor = 2;
    *(u32 *)((u8 *)cursor + 8) = 0x11000000;
    *(u32 *)((u8 *)cursor + 0xC) = 0x51000002;
    return (u8 *)cursor + 0x30;
}

/* Sets dither matrix `index` (0..3). */
void ExDitherMatrixEz(s32 index) {
    RhBase_SetVifPacketArea(ExDitherMatrixEz_Pipe(RhBase_GetVifPacketArea(), index));
}

/* Sets the GS dither matrix to built-in matrix `index` (0..3). */
s32 ExDitherMatrixEz_Pipe(s32 cursor, s32 index) {
    u64 value;

    if (index < 0 || index >= 4) {
        return cursor;
    }

    value = ditherMatrices[index];
    *(u64 *)(cursor + 8) = 0;
    *(u64 *)cursor = 0;
    *(u8 *)(cursor + 3) = 0x10;
    *(u64 *)(cursor + 0x10) = 0x1000000000008001ULL;
    *(u64 *)(cursor + 0x18) = 0xE;
    *(u64 *)(cursor + 0x20) = value;
    *(u64 *)(cursor + 0x28) = 0x44;
    *(u16 *)cursor = 2;
    *(u32 *)(cursor + 8) = 0x11000000;
    *(u32 *)(cursor + 0xC) = 0x51000002;
    return cursor + 0x30;
}

typedef struct {
    s64 value;
    s64 padding;
} Entry_00208680;

extern Entry_00208680 gsRegisterSets[][7]; /* original: gExPrim_aaRegs */

/* The value of GS register `reg` (0..6) of register set `set`. */
s64 ExGetRegVal(s32 set, s32 reg) {
    if (reg < 0 || reg >= 7) {
        return -1;
    }
    return gsRegisterSets[set][reg].value;
}

typedef struct {
    u16 index;
    u16 flags;
    u8 padding[0xC];
    s64 values[1];
} Buffer_002086D0;

/* Sets a primitive's alpha blend register. */
s32 ExAssignAlpha(void *prim, s64 alpha) {
    Buffer_002086D0 *buffer = prim;
    u16 index = buffer->index;
    s64 *values = (s64 *)((u8 *)prim + 0x10);

    buffer->flags |= 0x200;
    values[index] = alpha;
    return 1;
}

typedef struct {
    u64 reserved0 : 5;
    u64 flag : 1;
    u64 mode : 3;
    u64 reserved9 : 55;
} Flags_00208700;

/* Sets a primitive's texture registers from `texture` (`mode` the texture function). */
s32 ExAssignTexture(void *prim, void *texture, s32 mode) {
    u8 *base = (u8 *)prim + 0x10;
    u16 count = *(u16 *)prim;
    u64 *dst;

    if (!(*(u16 *)((u8 *)prim + 2) & 0x20)) {
        return 0;
    }
    if (texture == NULL) {
        return 0;
    }
    dst = (u64 *)(base + count * 8);
    dst[1] = *(u64 *)((u8 *)texture + 0x30);
    dst[2] = *(u64 *)((u8 *)texture + 0x40);
    ((Flags_00208700 *)(dst + 2))->flag = (((Flags_00208700 *)(dst + 2))->mode = mode);
    return 1;
}

typedef struct {
    u16 count;
    u16 flags;
    u8 padding[12];
    u8 data[1];
} Header_002087A0;


/* Sets a primitive's texture to frame buffer `frame`. */
s32 ExAssignFrameBuffer(void *prim, s32 frame) {
    Header_002087A0 *header = prim;
    u16 count = header->count;
    u8 *data = header->data;

    if (!(header->flags & 0x20)) {
        return 0;
    }
    ExFrameBuffer2Texture_Pipe(0, 0, frame, data + (count & 0xFFFF) * 8 + 8,
                 data + (count & 0xFFFF) * 8 + 0x10);
    return 1;
}

/* Uses part of the frame buffer as a texture. */
void ExFrameBuffer2Texture(s32 cursor, s32 address, s32 frame, s32 tex0) {
    extern s32 ExFrameBuffer2Texture_Pipe();

    RhBase_SetVifPacketArea(ExFrameBuffer2Texture_Pipe(RhBase_GetVifPacketArea(), cursor, address, frame, tex0));
}

typedef struct Tex0_00208870 {
    u64 tbp0 : 14;
    u64 tbw : 6;
    u64 psm : 6;
    u64 tw : 4;
    u64 th : 4;
    u64 tcc : 1;
    u64 tfx : 2;
    u64 cbp : 14;
    u64 cpsm : 4;
    u64 csm : 1;
    u64 csa : 5;
    u64 cld : 3;
} Tex0_00208870;

typedef struct Tex1_00208870 {
    u64 lcm : 1;
    u64 pad0 : 1;
    u64 mxl : 3;
    u64 mmag : 1;
    u64 mmin : 3;
    u64 mtba : 1;
    u64 pad1 : 9;
    u64 l : 2;
    u64 pad2 : 11;
    u64 k : 12;
    u64 pad3 : 20;
} Tex1_00208870;

/* Builds the texture registers that read frame buffer `frame` (copied to `address` if given) into `tex0` / `tex1`. */
s32 ExFrameBuffer2Texture_Pipe(s32 cursor, s32 address, s32 frame, void *tex0In, void *tex1In) {
    s32 widthIn;
    s32 height;
    s32 fbp;
    s32 psm;
    s32 tw;
    s32 th;
    Tex0_00208870 *tex0 = (Tex0_00208870 *)tex0In;
    Tex1_00208870 *tex1 = (Tex1_00208870 *)tex1In;
    s64 *packet = (s64 *)cursor;
    s64 *start = packet;

    RhBase_GetBufferFormatEx(address != 0 ? 1 : 0, &widthIn, &height, NULL);
    RhBase_GetScreenSize(&fbp, &psm);
    for (tw = 0; (1 << tw) < fbp; tw++) {
    }
    for (th = 0; (1 << th) < psm; th++) {
    }
    if (tex0 != NULL) {
        tex0->tbp0 = address > 0 ? address : widthIn;
        tex0->tbw = fbp >> 6;
        tex0->psm = height;
        tex0->tw = tw;
        tex0->th = th;
        tex0->tcc = 0;
        tex0->tfx = 0;
        tex0->cbp = 0;
        tex0->cpsm = 0;
        tex0->csm = 0;
        tex0->csa = 0;
        tex0->cld = 1;
    }
    if (tex1 != NULL) {
        tex1->lcm = 0;
        tex1->mxl = 0;
        tex1->mmag = frame;
        tex1->mmin = frame;
        tex1->mtba = 0;
        tex1->l = 0;
        tex1->k = 0;
    }
    if (address > 0) {
        s64 width;
        u16 count;

        packet[1] = 0;
        packet[0] = 0;
        ((u8 *)packet)[3] = 0x10;
        packet[2] = 0x1000000000008004LL;
        packet[3] = 0xE;
        width = fbp >> 6;
        packet[4] = ((s64)height << 56) | ((width << 48) | (((s64)address << 32) |
                    (((s64)height << 24) | (widthIn | (width << 16)))));
        packet[5] = 0x50;
        packet[6] = 0;
        packet[7] = 0x51;
        packet[8] = fbp | ((s64)psm << 32);
        packet[9] = 0x52;
        packet[10] = 2;
        packet[11] = 0x53;
        packet += 12;
        count = ((packet - start) >> 1) - 1;
        *(u16 *)start = count;
        ((s32 *)start)[2] = 0x11000000;
        ((s32 *)start)[3] = count | 0x51000000;
    }
    return (s32)packet;
}

typedef struct Buffer_00208CB0 {
    u16 index;
    u16 flags;
    u8 padding[0xC];
    s64 values[1];
} Buffer_00208CB0;

/* Sets a primitive's texture clamp register. */
s32 ExAssignClamp(void *prim, s64 clamp) {
    Buffer_00208CB0 *buffer = prim;
    u16 index = buffer->index;
    s64 *values = buffer->values;
    u16 *flags = &buffer->flags;

    if (!(*flags & 0x20)) {
        return 0;
    }
    *flags |= 0x4000;
    *(s64 *)((u8 *)values + (index & 0xFFFF) * 8 + 0x18) = clamp;
    return 1;
}

/* Alpha blend mode `mode` (0..3) as a GS register value. */
s64 ExGetAlphaVal(s32 mode) {
    s64 ret;

    if (mode < 0 || mode >= 4) {
        ret = 0;
    } else {
        ret = alphaBlendModes[mode];
    }
    return ret;
}

/* Picks the VU1 microprogram for draw `flags` (lit, fogged, clipped...) in the packet. */
void *RhVu1Mac_ChangeDrawMethod(void *packetIn, s32 flags) {
    s32 *packet = packetIn;

    packet[0] = 0x10000001;
    packet[1] = 0;
    packet[2] = 0x10000000;
    packet[3] = 0x68014000;
    if (!(flags & 2) || !D_00325E2C) {
        if (flags & 0x40) {
            if (flags & 0x20) {
                packet[4] = 0x274;
            } else if (flags & 0x10) {
                packet[4] = 0xE8;
            } else {
                packet[4] = 0xE8;
            }
        } else {
            if (flags & 0x20) {
                packet[4] = 0x1A4;
            } else if (flags & 0x10) {
                packet[4] = 0x30;
            } else {
                packet[4] = 0x30;
            }
        }
    } else {
        if (flags & 0x20) {
            packet[4] = 0x6D4;
        } else {
            packet[4] = 0x580;
        }
    }
    packet[5] = 0;
    packet[6] = 0;
    packet[7] = 0x10000000;
    vu1DrawMethod = flags;
    return packet + 8;
}

typedef struct {
    s32 flags;
    void *data;
    s32 field8;
    s32 fieldC;
} Header_00208E40;

/* Marks the VU1 microprogram to be picked again at the next draw. */
void *RhVu1Mac_ReserveChangeDrawMethod(void *packet) {
    Header_00208E40 *header = packet;

    header->flags = 0x20000000;
    header->data = (u8 *)packet + 0x20;
    header->field8 = 0;
    header->fieldC = 0;
    return (u8 *)packet + 0x20;
}

/* Sends the view-to-screen matrix to VU1. */
void *RhVu1Mac_SetViewScreenMatrix(void *packet, void *matrix) {
    ((u32 *)packet)[0] = 0x10000004;
    ((u32 *)packet)[1] = 0;
    ((u32 *)packet)[2] = 0;
    ((u32 *)packet)[3] = 0x6C040044;
    RhMem_CopyMemory16((u8 *)packet + 0x10, matrix, 4);
    return (u8 *)packet + 0x50;
}

/* Sends the screen-to-world matrix to VU1. */
void *RhVu1Mac_SetScreenWorldMatrix(void *packet, void *matrix) {
    ((s32 *)packet)[0] = 0x10000004;
    ((s32 *)packet)[1] = 0;
    ((s32 *)packet)[2] = 0;
    ((s32 *)packet)[3] = 0x6C040056;
    RhMem_CopyMemory16((u8 *)packet + 0x10, matrix, 4);
    return (u8 *)packet + 0x50;
}

/* Sends the three directional lights (`colors`, `dirs`) to VU1. */
s32 RhVu1Mac_SetStraightLightToVu1_Ex(s32 packet, void *colors, void *dirs, s32 count) {
    u8 buffer[0x50];
    s32 matrix;

    matrix = ((u32)buffer + 0xF) & ~0xF;
    if (count >= 0 && count < 3 && (colors == NULL || dirs == NULL)) {
        return packet;
    }
    switch (count) {
    case 0:
        vu1LightColors = ((f32 *)colors)[1];
        D_00325D94 = ((f32 *)colors)[2];
        D_00325D98 = ((f32 *)colors)[3];
        vu1LightDirs = ((f32 *)dirs)[0];
        D_00325D60 = ((f32 *)dirs)[1];
        D_00325D70 = ((f32 *)dirs)[2];
        break;
    case 1:
        D_00325DA0 = ((f32 *)colors)[1];
        D_00325DA4 = ((f32 *)colors)[2];
        D_00325DA8 = ((f32 *)colors)[3];
        D_00325D54 = ((f32 *)dirs)[0];
        D_00325D64 = ((f32 *)dirs)[1];
        D_00325D74 = ((f32 *)dirs)[2];
        break;
    case 2:
        D_00325DB0 = ((f32 *)colors)[1];
        D_00325DB4 = ((f32 *)colors)[2];
        D_00325DB8 = ((f32 *)colors)[3];
        D_00325D58 = ((f32 *)dirs)[0];
        D_00325D68 = ((f32 *)dirs)[1];
        D_00325D78 = ((f32 *)dirs)[2];
        break;
    }
    if (packet != 0) {
        u32 *tag = (u32 *)packet;

        RhMem_CopyMemory16((void *)matrix, &vu1LightColors, 4);
        RhGeom_MulMatrix(matrix, &vu1LightDirs);
        tag[0] = 0x10000004;
        tag[1] = 0;
        tag[2] = 0;
        tag[3] = 0x6C04003F;
        RhMem_CopyMemory16((void *)(packet + 0x10), (void *)matrix, 4);
        packet = (s32)(tag + 4) + 0x40;
    } else if (count < 0) {
        func_00198948(&vu1LightDirs, 0, 0x40);
        func_00198948(&vu1LightColors, 0, 0x40);
    }
    return packet;
}

typedef struct Packet_00209110 {
    u32 header[4];
    f32 values[8];
} Packet_00209110;

/* Sends the point light (position, colour, range) to VU1. */
s32 RhVu1Mac_SetPointLightToVu1(s32 packetIn, void *pos, void *color, f32 fparg0, f32 fparg1, f32 fparg2) {
    extern void RhMem_CopyMemory4(f32 *, void *, s32);
    extern f32 D_00325E00[4];
    extern f32 D_00325E10[4];
    extern f32 D_00325E20;
    extern f32 D_00325E24;
    extern f32 D_00325E28;
    Packet_00209110 *packet;
    f32 range;

    packet = (Packet_00209110 *)packetIn;
    if ((pos == NULL) || (color == NULL)) {
        packet->header[0] = 0x10000002;
        packet->header[1] = 0;
        packet->header[2] = 0x11000000;
        packet->header[3] = 0x6C020054;
        RhMem_FillMemory8((s64 *)packet->values, 0, 4);
        packet++;
        D_00325E2C = 0;
    } else {
        packet->header[0] = 0x10000002;
        packet->header[1] = 0;
        range = fparg1 - fparg0;
        packet->header[2] = 0x11000000;
        packet->header[3] = 0x6C020054;
        packet->values[0] = ((f32 *)pos)[1];
        packet->values[1] = ((f32 *)pos)[2];
        packet->values[2] = ((f32 *)pos)[3];
        packet->values[3] = (fparg2 * fparg1) / range;
        packet->values[4] = ((f32 *)color)[0];
        packet->values[5] = ((f32 *)color)[1];
        packet->values[6] = ((f32 *)color)[2];
        packet->values[7] = fparg2 / range;
        packet++;
        RhMem_CopyMemory4(D_00325E00, pos, 4);
        RhMem_CopyMemory4(D_00325E10, color, 4);
        D_00325E20 = fparg0;
        D_00325E24 = fparg1;
        D_00325E28 = fparg2;
        D_00325E2C = 1;
    }
    return (s32)packet;
}

typedef struct Vec4_00209270 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4_00209270;

extern Vec4_00209270 D_00325E00;
extern Vec4_00209270 D_00325E10;
extern f32 D_00325E20;
extern f32 D_00325E24;
extern f32 D_00325E28;
extern s32 D_00325E2C;

/* The point light last sent to VU1: position, colour and its three range values. */
s32 RhVu1Mac_GetPointLight(void *pos, void *color, f32 *near, f32 *far, f32 *power) {
    if (pos != NULL) {
        *(Vec4_00209270 *)pos = D_00325E00;
    }
    if (color != NULL) {
        *(Vec4_00209270 *)color = D_00325E10;
    }
    if (near != NULL) {
        *near = D_00325E20;
    }
    if (far != NULL) {
        *far = D_00325E24;
    }
    if (power != NULL) {
        *power = D_00325E28;
    }
    return D_00325E2C;
}

typedef struct Packet_00209320 {
    s32 tag0;
    s32 zero0;
    s32 zero1;
    s32 command0;
    f32 right;
    f32 left;
    f32 near_value;
    f32 far_value;
    s32 tag1;
    s32 zero2;
    s32 zero3;
    s32 command1;
    s32 enabled;
    s32 zero4;
    s32 zero5;
    s32 zero6;
} Packet_00209320;

/* Sends the clip parameters to VU1. */
void *RhVu1Mac_SetClipParameter(void *packetIn, s32 mode, f32 fparg0, f32 fparg1, f32 fparg2) {
    f32 scale;
    s32 enabled;
    Packet_00209320 *packet = packetIn;

    packet->tag0 = 0x10000001;
    packet->zero0 = 0;
    packet->zero1 = 0;
    packet->command0 = 0x6C014052;
    scale = 2.0f * fparg0;
    packet->right = 645.0f / scale;
    packet->left = -645.0f / scale;
    packet->near_value = 0.01f + fparg1;
    packet->far_value = fparg2 - 0.01f;
    packet->tag1 = 0x10000001;
    packet->zero2 = 0;
    packet->zero3 = 0;
    packet->command1 = 0x6C01405A;
    if (mode == 1) {
        enabled = 1;
    } else {
        enabled = 0;
    }
    packet->enabled = enabled;
    packet->zero4 = 0;
    packet->zero5 = 0;
    packet->zero6 = 0;
    return (u8 *)packetIn + 0x40;
}

typedef struct Packet_002093E0 {
    s32 tag[4];
    f32 values[4];
} Packet_002093E0;

extern f32 D_00325DE0;
extern f32 D_00325DE4;
extern f32 D_00325DE8;
extern f32 D_00325DEC;
extern f32 D_00325DF0;
extern f32 D_00325DF4;
extern f32 D_00325DF8;
extern f32 D_00325DFC;

/* Sends the fog ranges to VU1. */
void *RhVu1Mac_SetFogParameterEx(void *packetIn, f32 fparg0, f32 fparg1, f32 fparg2, f32 fparg3) {
    Packet_002093E0 *packet = packetIn;
    f32 range0;
    f32 range1;

    packet->tag[0] = 0x10000001;
    packet->tag[1] = 0;
    packet->tag[2] = 0x10000000;
    range1 = 255.0f / (fparg3 - fparg2);
    packet->tag[3] = 0x6C014053;
    packet->values[0] = range1;
    range0 = 255.0f / (fparg1 - fparg0);
    packet->values[1] = fparg2 * range1;
    packet->values[2] = range0;
    packet->values[3] = fparg1 * range0;
    D_00325DE0 = packet->values[2];
    D_00325DE4 = packet->values[3];
    D_00325DE8 = packet->values[0];
    D_00325DEC = packet->values[1];
    D_00325DF0 = fparg0;
    D_00325DF4 = fparg1;
    D_00325DF8 = fparg2;
    D_00325DFC = fparg3;
    return packet + 1;
}

typedef struct {
    u32 header[4];
    f32 value_10;
    f32 value_14;
    f32 value_18;
    f32 value_1C;
} Packet_00209490;

extern f32 D_00325DE0;
extern f32 D_00325DE4;
extern f32 D_00325DE8;
extern f32 D_00325DEC;

/* Turns depth fog (`depthOn`) and height fog (`heightOn`) on or off in VU1. */
void *RhVu1Mac_SetFogOnOff(void *packetIn, s32 depthOn, s32 heightOn) {
    Packet_00209490 *packet = packetIn;

    packet->header[0] = 0x10000001;
    packet->header[1] = 0;
    packet->header[2] = 0x10000000;
    packet->header[3] = 0x6C014053;
    if (depthOn != 0) {
        packet->value_18 = D_00325DE0;
        packet->value_1C = D_00325DE4;
    } else {
        packet->value_18 = 0.0f;
        packet->value_1C = 255.0f;
    }
    if (heightOn != 0) {
        packet->value_10 = D_00325DE8;
        packet->value_14 = D_00325DEC;
    } else {
        packet->value_10 = 0.0f;
        packet->value_14 = 0.0f;
    }
    return (u8 *)packetIn + 0x20;
}

typedef struct Flags_00209510 {
    u8 pad0 : 6;
    u8 enabled : 1;
    u8 pad7 : 1;
} Flags_00209510;

typedef struct State_00209510 {
    u8 pad0[0x274];
    u8 *decoder;
    s32 option;
    s32 base;
    s32 current;
    s32 size;
    s32 ready;
    s32 start;
    s32 end;
    s32 field294;
    s32 field298;
} State_00209510;

typedef struct Env_00209510 {
    u8 pad0[6];
    s16 field6;
    u8 pad8[20];
} Env_00209510;

typedef struct Mode_00209510 {
    u32 clock : 2;
    u32 gate : 1;
    u32 gate_source : 1;
    u32 gate_mode : 2;
    u32 zero_return : 1;
    u32 enable : 1;
    u32 compare_interrupt : 1;
    u32 overflow_interrupt : 1;
    u32 compare_flag : 1;
    u32 overflow_flag : 1;
    u32 reserved : 20;
} Mode_00209510;

extern u8 D_00286980[];
extern u8 screenModes[]; /* original: gRhSys_asd */
extern u8 D_00293F14[];
extern u8 D_00293F18[];
extern s32 D_003261C8;

/* Starts the renderer: screen mode `mode`, its frame buffers, the packet area start..end of `size`. */
s32 RhBase_Init(s32 modeIn, s32 interlace, s32 field, s32 start, s32 end, s32 size, s32 flags) {
    void sceDmaSend(u8 *, s32);
    Env_00209510 env;
    Mode_00209510 mode;
    State_00209510 *state = (State_00209510 *)screenState;
    s32 *packet;

    func_00198948(screenState, 0, 0x2A0);
    D_003261C8 = flags;
    if (RhFile_Init() == 0) {
        return 0;
    }
    sceDevVif0Reset();
    sceDevVu0Reset();
    sceGsResetPath();
    sceDmaReset(1);
    sceDmaGetEnv(&env);
    env.field6 = 0x100;
    sceDmaPutEnv(&env);
    func_00184810(0, *(s16 *)(screenModes + modeIn * 0x28),
                    *(s16 *)(D_00293F14 + modeIn * 0x28),
                    *(s16 *)(D_00293F18 + modeIn * 0x28));
    state->decoder = (u8 *)sceDmaGetChan(1);
    ((Flags_00209510 *)state->decoder)->enabled = 1;
    lRhBase_InitScreenVariables(state, modeIn, interlace, field);
    mode.clock = 3;
    mode.gate = 0;
    mode.gate_source = 0;
    mode.gate_mode = 0;
    mode.zero_return = 0;
    mode.enable = 1;
    mode.compare_interrupt = 0;
    mode.overflow_interrupt = 0;
    mode.compare_flag = 0;
    mode.overflow_flag = 1;
    mode.reserved = 0;
    *(s32 *)0x10000810 = *(s32 *)&mode;
    *(s32 *)0x10000800 = 0;
    state->start = start;
    state->end = end;
    state->size = size;
    state->ready = 1;
    state->base = start;
    state->current = start;
    ChangeThreadPriority(GetThreadId(), 0x20);
    state->field294 = 0;
    state->field298 = 0;
    packet = (s32 *)lRhBase_InitGsAndVif(state->base);
    RhGeom_Init();
    RhView_Init();
    RhMemCard_Init();
    packet[0] = 0x70000000;
    packet[1] = 0;
    packet[2] = 0;
    packet[3] = 0;
    FlushCache(0);
    sceGsSyncPath(0, 0);
    sceDmaSend(state->decoder, state->base);
    sceGsSyncPath(0, 0);
    sceDmaSend(state->decoder, (s32)D_00286980);
    sceGsSyncPath(0, 0);
    RhZSort_Start(state->base, state->base + state->size);
    sceGsSyncV(0);
    return 1;
}

/* Ends the renderer. */
s32 RhBase_Term(void) {
    RhView_Term();
    RhFile_Term();
    RhGeom_Term();
    RhMemCard_Term();
    return 1;
}

/* Resets the GS drawing environment for `field`. */
void RhBase_ResetGsEnv(s32 field) {
    void sceDmaSend(u8 *, s32);
    extern void sceDmaSync(u8 *, s32, s32);
    extern void sceVpu0Reset(void);
    extern u8 D_00293F1C[];
    extern u8 D_00293F20[];
    extern u8 *D_003261C4;
    s32 *packet;

    sceDmaSync(D_003261C4, 0, 0);
    sceDmaReset(1);
    sceGsSyncPath(0, 0);
    sceGsResetPath();
    sceVpu0Reset();
    func_00184810(0, *(s16 *)(screenModes + field * 0x28),
                    *(s16 *)(D_00293F14 + field * 0x28),
                    *(s16 *)(D_00293F18 + field * 0x28));
    D_0032618C = *(s32 *)(D_00293F1C + field * 0x28);
    D_00326190 = *(s32 *)(D_00293F20 + field * 0x28);
    packet = (s32 *)lRhBase_InitGsAndVif(*(s32 *)0x003261CC);
    packet[0] = 0x70000000;
    packet[1] = 0;
    packet[2] = 0;
    packet[3] = 0;
    FlushCache(0);
    sceGsSyncPath(0, 0);
    sceDmaSend(D_003261C4, *(s32 *)0x003261CC);
    sceGsSyncPath(0, 0);
}

typedef struct State_002099D0 {
    u8 pad0[0x240];
    s32 width;
    u8 pad244[8];
    s32 display;
    u8 pad250[0x10];
    s16 x;
    u8 pad262[2];
    s16 y;
    u8 pad266[6];
    s32 frame;
    u8 pad270[0xC];
    s32 dmaAddress;
    s32 dmaBuffer;
    s32 dmaSize;
    s32 currentBuffer;
    s32 buffer0;
    s32 buffer1;
    void (*beforeDisplay)(void);
    void (*beforeWait)(void);
} State_002099D0;


/* Ends the frame: sends the draw lists, waits for the GS, swaps the frame buffers. */
s32 RhBase_FlipBuffer(void) {
    extern s32 sceGsSyncPath();
    extern s32 lRhBase_SetRandomDither();
    extern u8 D_00293F14[];
    extern s32 D_00325E30;
    extern s32 D_00326188;
    State_002099D0 *state = (State_002099D0 *)screenState;
    s32 result;
    s32 width;
    s32 period;
    s32 remaining;
    s32 *packet;
    u8 *display;

    RhZSort_Finish();
    RhFile_VSyncProcess();
    RhMemCard_Act();
    packet = (s32 *)D_003261D0;
    packet[0] = 0x70000000;
    packet[1] = 0;
    packet[2] = 0;
    packet[3] = 0;
    (void)*(volatile u32 *)0x10000800;
    if (sceGsSyncPath(0, 0) < 0) {
        RhBase_ResetGsEnv(D_00326188);
    }
    if (state->beforeWait != NULL) {
        state->beforeWait();
    }
    remaining = D_00325E30;
    if (*(s32 *)(D_00293F14 + D_00326188 * 0x28) == 2) {
        width = 0x1C0;
        period = 0x208;
    } else {
        width = 0x200;
        period = 0x26C;
    }
    while (remaining-- >= 0) {
        result = sceGsSyncV(0);
        if (state->width == width) {
            if (result != 0) {
                result = sceGsSyncV(0);
            }
        }
        if (*(volatile u32 *)0x10000800 > (u32)(period * (D_00325E30 + 1))) {
            break;
        }
    }
    D_00325E30 = 0;
    if (state->beforeDisplay != NULL) {
        state->beforeDisplay();
    }
    if (state->display != 0) {
        if (state->frame & 1) {
            display = (u8 *)state + 0x150;
        } else {
            display = (u8 *)state + 0x60;
        }
        sceGsSetHalfOffset(display, state->x, state->y, (s16)result);
    }
    FlushCache(0);
    sceGsSwapDBuff((u8 *)state, state->frame);
    if (SzGame_InqSoftFocus() != 0) {
        func_00100610(1);
    }
    sceGsSyncPath(0, 0);
    *(volatile s32 *)0x10009020 = 0;
    *(volatile s32 *)0x10009030 = (u32)state->dmaAddress & 0x0FFFFFFF;
    *(volatile s32 *)0x1000E010 = 2;
    FlushCache(0);
    *(volatile s32 *)0x10009000 = 0x145;
    if (state->currentBuffer != 0) {
        state->dmaAddress = state->buffer1;
        state->dmaBuffer = state->buffer1;
        state->currentBuffer = 0;
    } else {
        state->dmaAddress = state->buffer0;
        state->dmaBuffer = state->buffer0;
        state->currentBuffer = 1;
    }
    state->frame++;
    result = 1;
    if (*(s32 *)(D_00293F14 + D_00326188 * 0x28) == 2) {
        if (state->width == 0x1C0) {
            if (*(volatile u32 *)0x10000800 > 0x21C) {
                result = 2;
            }
        } else if (*(volatile u32 *)0x10000800 > 0x10E) {
            result = 2;
        }
    } else if (*(volatile u32 *)0x10000800 > 0x280) {
        result = 2;
    }
    *(volatile u32 *)0x10000800 = 0;
    RhZSort_Start(state->dmaAddress, state->dmaAddress + state->dmaSize);
    RhBase_SetVifPacketArea(lRhBase_SetRandomDither(RhBase_GetVifPacketArea()));
    return result;
}

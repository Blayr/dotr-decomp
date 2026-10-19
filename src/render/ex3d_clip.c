/* 3D helpers: surface normals, clip planes, node transforms (Ex3d_*). */

#include "common.h"

typedef struct Vec4_00205E70 {
    f32 x, y, z, w;
} Vec4_00205E70;

extern Vec4_00205E70 D_00293D60;
extern Vec4_00205E70 D_00293D70;

/* The normal of the surface through `count` points into `normal`. */
s32 Ex3d_GetSurfaceNormal(s32 count, void *arg1, f32 *normal) {
    Vec4_00205E70 *points = arg1;
    s32 i;
    Vec4_00205E70 *p0;
    Vec4_00205E70 *p1;
    Vec4_00205E70 *p2;
    Vec4_00205E70 a;
    Vec4_00205E70 b;
    Vec4_00205E70 c;

    normal[0] = 0.0f;
    normal[1] = 0.0f;
    normal[2] = 0.0f;
    normal[3] = 0.0f;
    if (count < 3) {
        return 0;
    }
    for (i = 0; i < count; i++) {
        p0 = &points[i % count];
        p1 = &points[(i + 1) % count];
        p2 = &points[(i + 2) % count];
        a = D_00293D60;
        a.x = p1->x - p0->x;
        a.y = p1->y - p0->y;
        a.z = p1->z - p0->z;
        b = D_00293D70;
        b.x = p2->x - p1->x;
        b.y = p2->y - p1->y;
        b.z = p2->z - p1->z;
        RhGeom_OuterProduct(&c.x, &a.x, &b.x);
        normal[0] += c.x;
        normal[1] += c.y;
        normal[2] += c.z;
    }
    normal[0] /= (f32)count;
    normal[1] /= (f32)count;
    normal[2] /= (f32)count;
    RhGeom_NormalizeVector(normal);
    return 1;
}

typedef struct Vec4_00206030 {
    f32 x, y, z, w;
} Vec4_00206030;

/* The average of `count` points into `out`. */
s32 Ex3d_GetPointsAverage(s32 count, void *points, void *out) {
    Vec4_00206030 *src = points;
    Vec4_00206030 *dst = out;
    s32 i;
    f32 divisor;

    dst->x = 0.0f;
    dst->y = 0.0f;
    dst->z = 0.0f;
    dst->w = 0.0f;
    if (count == 0) {
        return 0;
    }
    for (i = 0; i < count; i++) {
        dst->x += src->x;
        dst->y += src->y;
        dst->z += src->z;
        dst->w += src->w;
        src++;
    }
    divisor = (f32) count;
    dst->x /= divisor;
    dst->y /= divisor;
    dst->z /= divisor;
    dst->w /= divisor;
    return 1;
}

/* The direction from `origin` to the average of `count` points into `out`. */
s32 Ex3d_GetViewVector(f32 *origin, s32 count, f32 *points, f32 *out) {
    s32 i;
    f32 divisor;

    out[0] = 0.0f;
    out[1] = 0.0f;
    out[2] = 0.0f;
    out[3] = 0.0f;
    if (count == 0) {
        return 0;
    }

    for (i = 0; i < count; i++) {
        out[0] += (origin != NULL ? origin[0] : 0.0f) - points[0];
        out[1] += (origin != NULL ? origin[1] : 0.0f) - points[1];
        out[2] += (origin != NULL ? origin[2] : 0.0f) - points[2];
        points += 4;
    }

    divisor = (f32) count;
    out[0] /= divisor;
    out[1] /= divisor;
    out[2] /= divisor;
    RhGeom_NormalizeVector(out);
    return 1;
}

typedef struct Point_002061F0 {
    f32 x;
    f32 y;
    f32 z;
    u8 padding[0x24];
} Point_002061F0;

/* The direction from `origin` to the average of a node's `count` points into `out`. */
s32 Ex3d_GetViewVectorForNode(f32 *origin, s32 count, void *src, f32 *out) {
    f32 divisor;
    s32 i;
    Point_002061F0 *point;

    point = src;
    out[0] = 0.0f;
    out[1] = 0.0f;
    out[2] = 0.0f;
    out[3] = 0.0f;
    if (count == 0) {
        return 0;
    }

    for (i = 0; i < count; i++, point++) {
        out[0] += (origin != NULL ? origin[0] : 0.0f) - point->x;
        out[1] += (origin != NULL ? origin[1] : 0.0f) - point->y;
        out[2] += (origin != NULL ? origin[2] : 0.0f) - point->z;
    }

    divisor = (f32)count;
    out[0] /= divisor;
    out[1] /= divisor;
    out[2] /= divisor;
    RhGeom_NormalizeVector(out);
    return 1;
}

/* The constant term of the plane through three points into `out`. */
void Ex3d_GetSurfaceC(f32 *a, f32 *b, f32 *c, f32 *out) {
    out[0] = a[1] * (b[2] - c[2])
            + b[1] * (c[2] - a[2])
            + c[1] * (a[2] - b[2]);
    out[1] = a[2] * (b[0] - c[0])
            + b[2] * (c[0] - a[0])
            + c[2] * (a[0] - b[0]);
    out[2] = a[0] * (b[1] - c[1])
            + b[0] * (c[1] - a[1])
            + c[0] * (a[1] - b[1]);
    out[3] = a[0] * (b[2] * c[1] - b[1] * c[2])
            + a[1] * (b[0] * c[2] - b[2] * c[0])
            + a[2] * (b[1] * c[0] - b[0] * c[1]);
    out[4] = func_001A6C60(out[0] * out[0]
                           + out[1] * out[1]
                           + out[2] * out[2]);
}

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

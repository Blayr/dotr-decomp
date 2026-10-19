/* 3D helpers: projection to the screen, sample depths (Ex3d_*). */

#include "common.h"

typedef struct {
    f32 x, y, z, w;
} Vec4_00205440;

typedef union {
    struct {
        u16 x;
        u16 y;
    } xy;
    struct {
        u64 xy : 32;
        u64 z : 24;
        u64 f : 8;
    } bits;
} Xyz_00205440;

/* Projects point `point` to the screen with `matrix` (or the world-screen one); its screen x, y and z through
   `out` and `outZ`. Returns 0 off screen. */
s32 Ex3d_RotTransPers(s32 point, void *matrix, u16 *out, s32 *outZ) {
    extern s64 func_001A23B0(f32);
    f32 mtx[16];
    Vec4_00205440 v;
    f32 inv;

    v = *(Vec4_00205440 *)point;
    if (matrix == NULL) {
        RhView_GetWorldScreenMatrix(mtx);
        matrix = mtx;
    }
    RhGeom_PushMatrix((s32)matrix);
    v.w = 1.0f;
    RhGeom_MulMatrixVector(&v, NULL, &v);
    RhGeom_PopMatrix();
    inv = 1.0f / v.w;
    v.x *= inv;
    v.y *= inv;
    v.z *= inv;
    if (v.z < 1.0f || !(v.z <= 16777215.0f) || v.x < 0.0f || !(v.x <= 4095.0f) ||
        v.y < 0.0f || !(v.y <= 4095.0f)) {
        return 0;
    }
    ((Xyz_00205440 *)out)->xy.x = func_001A23B0(16.0f * v.x);
    ((Xyz_00205440 *)out)->xy.y = func_001A23B0(16.0f * v.y);
    ((Xyz_00205440 *)out)->bits.z = func_001A23B0(v.z);
    if (outZ != NULL) {
        *(f32 *)outZ = v.w;
    }
    return 1;
}

typedef union Vertex_00205630 {
    struct {
        u16 x;
        u16 y;
        u32 zflags;
    } coords;
    struct {
        u64 x : 16;
        u64 y : 16;
        u64 z : 24;
        u64 flags : 8;
    } bits;
} Vertex_00205630;

/* Projects `count` points with `matrix` into a draw packet, working out each one's Q. */
s32 Ex3d_RotTransPersAuto(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 *arg4) {
    extern s64 func_001A23B0(f32);
    f32 matrix[4][4];
    f32 *input = (f32 *)arg0;
    Vertex_00205630 *vertex = (Vertex_00205630 *)(arg3 + 0x10);
    u64 *tags = (u64 *)(arg3 + 8);
    u64 flags = *tags;
    s32 count = 0;
    u16 length = *(u16 *)arg3;
    f32 sum = 0.0f;
    s32 i;

    if (arg2 == 0) {
        RhView_GetWorldScreenMatrix(matrix);
        arg2 = (s32)matrix;
    }
    for (i = 0; i < length; i++, flags >>= 4) {
        if ((flags & 0xF) == 4) {
            input[3] = 1.0f;
            input += 4;
            count++;
        }
    }
    RhGeom_PushMatrix(arg2);
    RhGeom_MulMatrixVectorArray(arg1, 0, arg0, count);
    RhGeom_PopMatrix();

    flags = *tags;
    for (i = 0; i < length; i++, vertex++, flags >>= 4) {
        if ((flags & 0xF) == 4) {
            f32 *output = (f32 *)arg1;
            f32 reciprocal = 1.0f / output[3];
            output[0] *= reciprocal;
            output[1] *= reciprocal;
            output[2] *= reciprocal;
            if (output[2] < 1.0f || !(output[2] <= 16777215.0f) ||
                output[0] < 0.0f || !(output[0] <= 4095.0f) ||
                output[1] < 0.0f || !(output[1] <= 4095.0f)) {
                return 0;
            }
            vertex->coords.x = func_001A23B0(16.0f * output[0]);
            vertex->coords.y = func_001A23B0(16.0f * output[1]);
            vertex->bits.z = func_001A23B0(output[2]);
            sum += output[3];
            arg1 += 0x10;
        }
    }
    if (arg4 != NULL) {
        *arg4 = sum / (f32)count;
    }
    return 1;
}

typedef struct Packet_002058D0 {
    u16 count;
    u16 flags;
    u32 padding;
    u64 types;
    u8 data[1];
} Packet_002058D0;

typedef struct Packed_002058D0 {
    u64 xy : 32;
    u64 z : 24;
    u64 fog : 8;
} Packed_002058D0;

/* Projects points with `matrix` into `packet` with their Q (perspective) values. */
s32 Ex3d_RotTransPersAutoCalcQ(void *src MW_ALIGN(16), f32 *vertices, s32 matrix, s32 packet, s32 average) {
    extern s64 func_001A23B0(f32);
    f32 local_matrix[16];
    f32 *input = src;
    u64 *type_word = &((Packet_002058D0 *)packet)->types;
    f32 *attribute1 = NULL;
    f32 *attribute2 = NULL;
    u8 *entry = ((Packet_002058D0 *)packet)->data;
    u64 types = *type_word;
    u16 count = ((Packet_002058D0 *)packet)->count;
    f32 total = 0.0f;
    s32 scale_attributes = 0;
    s32 vertex_count = 0;
    u16 flags = ((Packet_002058D0 *)packet)->flags;
    s32 i;

    if (!(flags & 0x800) && (flags & 0x20) && (flags & 0x10)) {
        scale_attributes = 1;
    }
    if (matrix == 0) {
        RhView_GetWorldScreenMatrix(local_matrix);
        matrix = (s32)local_matrix;
    }
    for (i = 0; i < (u16)count; i++) {
        if ((types & 0xF) == 4) {
            input[3] = 1.0f;
            input += 4;
            vertex_count++;
        }
        types >>= 4;
    }
    RhGeom_PushMatrix(matrix);
    RhGeom_MulMatrixVectorArray((s32)vertices, 0, (s32)src, vertex_count);
    RhGeom_PopMatrix();
    types = *type_word;
    for (i = 0; i < (u16)count; i++, entry += 8, types >>= 4) {
        s32 kind = types & 0xF;
        switch (kind) {
        case 1:
            attribute1 = (f32 *)entry;
            break;
        case 2:
            attribute2 = (f32 *)entry;
            break;
        case 4: {
            f32 reciprocal = 1.0f / vertices[3];
            f32 x, y, z;

            if (scale_attributes && attribute1 != NULL && attribute2 != NULL) {
                attribute1[1] = reciprocal;
                attribute1 = NULL;
                attribute2[0] *= reciprocal;
                attribute2[1] *= reciprocal;
                attribute2 = NULL;
            }
            vertices[0] *= reciprocal;
            vertices[1] *= reciprocal;
            z = vertices[2] * reciprocal;
            vertices[2] = z;
            if (z < 1.0f || !(z <= 16777215.0f) ||
                (x = vertices[0]) < 0.0f || !(x <= 4095.0f) ||
                (y = vertices[1]) < 0.0f || !(y <= 4095.0f)) {
                return 0;
            }
            *(s16 *)(entry + 0) = func_001A23B0(16.0f * x);
            *(s16 *)(entry + 2) = func_001A23B0(16.0f * vertices[1]);
            ((Packed_002058D0 *)entry)->z = func_001A23B0(vertices[2]);
            total += vertices[3];
            vertices += 4;
            break;
        }
        }
    }
    if (average != 0) {
        *(f32 *)average = total / (f32)vertex_count;
    }
    return 1;
}

/* The camera's look direction (view `view`). */
f32 Ex3d_GetLookVector(s32 view) {
    f32 *look;

    look = SzView_GetLook(0);
    SzView_GetLookVector(0, view);
    return *look;
}

/* The camera's look matrix (view `view`). */
void Ex3d_GetLookMatrix(s32 view) {
    SzView_GetLookMatrix(0, view);
}

/* The camera's look matrix with its roll (view `view`). */
void Ex3d_GetLookMatrixWithRoll(s32 view) {
    SzView_GetLookMatrixWithRoll(0, view);
}

/* The 3D point under screen point (x, y) at the card distance into `out`. */
void Ex3d_GetPointOnScreen(void *out, f32 fparg0, f32 fparg1) {
    f32 matrix[4][4];
    f32 *vector = out;

    vector[0] = fparg0;
    vector[1] = fparg1;
    vector[2] = SzView_GetScreenDistance(0);
    vector[3] = 1.0f;
    RhView_GetWorldViewMatrix(matrix);
    RhGeom_InvertMatrix(matrix, matrix);
    RhGeom_MulMatrixVector(vector, matrix, vector);
}

/* The GS depth of point `point` (moved by `bias`). */
s32 Ex3d_GetSampleZ(void *point, f32 bias) {
    f32 vector[4];
    f32 matrix1[4][4];
    f32 matrix2[4][4];

    RhView_GetWorldViewMatrix(matrix1);
    RhView_GetViewScreenMatrix(matrix2);
    ((f32 *)point)[3] = 1.0f;
    RhGeom_MulMatrixVector(vector, matrix1, point);
    vector[2] -= bias;
    RhGeom_MulMatrixVector(vector, matrix2, vector);
    if (vector[3] <= 0.0f) {
        return 0xFFFFF6;
    }
    if (vector[2] <= 0.0f) {
        return 0;
    }
    return func_001A23B0(vector[2] / vector[3]);
}

/* The perspective W of point `point` (moved by `bias`). */
f32 Ex3d_GetSampleW(void *point, f32 bias) {
    f32 vector[4];
    f32 matrix1[4][4];
    f32 matrix2[4][4];

    RhView_GetWorldViewMatrix(matrix1);
    RhView_GetViewScreenMatrix(matrix2);
    ((f32 *)point)[3] = 1.0f;
    RhGeom_MulMatrixVector(vector, matrix1, point);
    vector[2] -= bias;
    RhGeom_MulMatrixVector(vector, matrix2, vector);
    return vector[3];
}

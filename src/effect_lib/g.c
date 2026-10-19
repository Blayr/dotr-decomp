/* Effect helpers, part 1 of 4 of one original Konami file: small geometry (G*): perspective transforms, rotation matrices, random vectors. */

#include "common.h"

/* Sony crt0.s _start (the Japanese build has the same code, from an older crt0 that orders the
   bss-clear loop's nops differently). Linker names: _fbss, _end, _gp, _stack, _stack_size, _args, _root. */
extern f32 g_vec_temp[];

typedef struct Vec4_00100B00 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4_00100B00;

/* Projects triangle (a, b, c) with Q values into the draw packet. */
void GRotTransPers_3(void *a, void *b, void *c, s32 matrix, s32 packet, s32 average) {
    Vec4_00100B00 vertices[3];

    vertices[0] = *(Vec4_00100B00 *)a;
    vertices[1] = *(Vec4_00100B00 *)b;
    vertices[2] = *(Vec4_00100B00 *)c;
    Ex3d_RotTransPersAutoCalcQ(vertices, g_vec_temp, matrix, packet, average);
}

typedef struct Vec4_00100BA0 {
    f32 x, y, z, w;
} Vec4_00100BA0;

/* Projects quad (a, b, c, d) with Q values into the draw packet. */
void GRotTransPers_4(void *a, void *b, void *c, void *d,
                   s32 matrix, s32 packet, s32 average) {
    Vec4_00100BA0 vectors[4];

    vectors[0] = *(Vec4_00100BA0 *)a;
    vectors[1] = *(Vec4_00100BA0 *)b;
    vectors[2] = *(Vec4_00100BA0 *)c;
    vectors[3] = *(Vec4_00100BA0 *)d;
    Ex3d_RotTransPersAutoCalcQ(vectors, g_vec_temp, matrix, packet, average);
}

typedef struct {
    u16 x : 14;
    u16 flags_x : 2;
    u16 y : 14;
    u16 flags_y : 2;
} PackedCoordinates_00100C60;

/* Sets a texture coordinate from a screen vertex moved by (dx, dy), kept inside the 640x448 screen. */
void GSet_WindowUv(void *uv, void *vertex, s32 dx, s32 dy) {
    s32 u;
    s32 v;

    u = ((s32) ((u16 *) vertex)[0] >> 4) - 0x6C0 + dx;
    v = ((s32) ((u16 *) vertex)[1] >> 4) - 0x720 + dy;
    if (u <= 0) {
        u = 1;
    } else if (u > 0x27F) {
        u = 0x27F;
    }
    if (v <= 0) {
        v = 1;
    } else if (v > 0x1BF) {
        v = 0x1BF;
    }
    ((PackedCoordinates_00100C60 *) uv)->x = u << 4;
    ((PackedCoordinates_00100C60 *) uv)->y = v << 4;
}

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Vec3_00100D00;

/* Whether unit `id`'s model is in front of (1) or behind (-1) the board's centre line. */
s32 GGet_ModelPosZSign(s32 id) {
    Vec3_00100D00 v;
    s32 ret;

    ret = 1;
    SzEffect_GetModelPos2(id, &v);
    if (v.z < 0.0f) {
        ret = -1;
    }
    return ret;
}

/* A wave-shaped fade value (0..1) for frame `frame` of `length`, with power `power`. */
f32 GCalc_Trans(s32 frame, s32 length, s32 power) {
    f32 wave;

    wave = func_001A6B70(6.2831855f * ((f32) ((s32) ((length - frame) << 0x10) / (s32) (length * 5)) / 65536.0f));
    return 1.0f - func_001A6C48(wave / func_001A6B70(1.2566179f), (f32) power);
}

typedef struct {
    u32 values[4];
} Config_00100E00;

extern Config_00100E00 D_0028C210;

/* Rotates matrix `matrix` by `angle` around axis `axis` (0 x, 1 y, 2 z). */
void GRot_Matrix(s32 matrix, s32 angle, s32 axis) {
    Config_00100E00 values;
    u32 *words = (u32 *)&values;

    values = D_0028C210;
    angle &= 0xFFFF;
    words[axis] = angle;
    RhGeom_RotXYZMatrix(matrix, words);
}

#ifndef GAME_H
/* The game translation unit already declares this global with its local type. */
typedef struct {
    unsigned int values[4];
} Config_00100E00;

extern Config_00100E00 D_0028C210;
#endif

/* Builds a matrix turning the z axis onto `vector`. */
void GVec2RotMat_Z(void *matrix, f32 *vector) {
    Config_00100E00 rotationZ;
    Config_00100E00 rotationY;
    f32 xSquared;
    s64 angleZ;
    s64 angleY;

    RhGeom_UnitMatrix(matrix);
    angleZ = func_001A22C0(65536.0f * (func_001A6C18(vector[1], vector[0]) / 6.2831855f));
    rotationZ = D_0028C210;
    ((s32 *)&rotationZ)[2] = angleZ & 0xFFFF;
    RhGeom_RotXYZMatrix((s32)matrix, (u32 *)&rotationZ);
    xSquared = func_001A6C48(vector[0], 2.0f);
    angleY = func_001A22C0(65536.0f * (func_001A6C18(func_001A6C60(xSquared + func_001A6C48(vector[1], 2.0f)), vector[2]) / 6.2831855f));
    rotationY = D_0028C210;
    ((s32 *)&rotationY)[1] = angleY & 0xFFFF;
    RhGeom_RotXYZMatrix((s32)matrix, (u32 *)&rotationY);
}

/* The centre of triangle (a, b, c) into `out`. */
void GGet_TriangleCenter(float *out, float *a, float *b, float *c)
{
    float v[2][4];

    sceVu0AddVector(v[0], a, b);
    sceVu0ScaleVector((float *)v, (float *)v, 0.5f);
    sceVu0SubVector(v[1], c, v[0]);
    sceVu0ScaleVector(v[1], v[1], 0.33333334f);
    sceVu0AddVector(out, v[1], v[0]);
}

/* 1 until `value` passes `end`, then falling from 1 as it nears `start` (a fade-out ramp). */
f32 GCalc_Decrease(f32 value, f32 start, f32 end) {
    f32 result;

    result = 1.0f;
    if (!(value <= end)) {
        result = (value - start) / (end - start);
    }
    return result;
}

/* `value` / `length`, at most 1 (a fade-in ramp). */
f32 GCalc_Increase(f32 value, f32 length) {
    f32 result;

    result = 1.0f;
    if (value < length) {
        result = value / length;
    }
    return result;
}

/* `value` clamped to low..high. */
s32 GWithin_LimitsI(s32 value, s32 low, s32 high) {
    if (value < low) {
        value = low;
    } else if (high < value) {
        value = high;
    }
    return value;
}

extern f32 g_rand_f[4][32][3];

/* Rotates a matrix around one axis. */
static inline void rotate_00101080(void *matrix, s32 angle, s32 axis) {
    Config_00100E00 values;
    u32 *words = (u32 *)&values;

    values = D_0028C210;
    angle &= 0xFFFF;
    words[axis] = angle;
    RhGeom_RotXYZMatrix((s32)matrix, words);
}

/* A random direction of length `scale` into `vector`. */
void GSet_RandVector(f32 *vector, f32 scale) {
    f32 matrix[16];
    f32 *value;
    f32 sign;

    value = &g_rand_f[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32][(func_0019A5C8() >> 23) % 3];
    sign = 2.0f * (f32)((func_0019A5C8() >> 23) % 2) - 1.0f;
    vector[0] = sign * *value;

    value = &g_rand_f[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32][(func_0019A5C8() >> 23) % 3];
    sign = 2.0f * (f32)((func_0019A5C8() >> 23) % 2) - 1.0f;
    vector[1] = sign * *value;

    value = &g_rand_f[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32][(func_0019A5C8() >> 23) % 3];
    sign = 2.0f * (f32)((func_0019A5C8() >> 23) % 2) - 1.0f;
    vector[2] = sign * *value;
    vector[3] = 1.0f;
    sceVu0ScaleVector(vector, vector, scale);
    RhGeom_UnitMatrix(matrix);
    rotate_00101080(matrix, (((func_0019A5C8() >> 23) % 256) << 16) >> 8, 0);
    rotate_00101080(matrix, (((func_0019A5C8() >> 23) % 256) << 16) >> 8, 1);
    rotate_00101080(matrix, (((func_0019A5C8() >> 23) % 256) << 16) >> 8, 2);
    sceVu0ApplyMatrix(vector, matrix, vector);
}

typedef struct Point_00101430 {
    u16 x;
    u16 y;
} Point_00101430;

typedef struct Vec4_00101430 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4_00101430;

/* Whether screen triangle (a, b, c) faces the camera. */
s32 GJudge_FrontBack2(void *aIn, void *bIn, void *cIn) {
    Point_00101430 *a = aIn;
    Point_00101430 *b = bIn;
    Point_00101430 *c = cIn;
    s32 result = 1;
    f32 normal[4];
    Vec4_00101430 verts[3];

    verts[0].x = (u32)a->x;
    verts[0].y = (u32)a->y;
    verts[0].z = 0.0f;
    verts[0].w = 1.0f;
    verts[1].x = (u32)b->x;
    verts[1].y = (u32)b->y;
    verts[1].z = 0.0f;
    verts[1].w = 1.0f;
    verts[2].x = (u32)c->x;
    verts[2].y = (u32)c->y;
    verts[2].z = 0.0f;
    verts[2].w = 1.0f;
    Ex3d_GetSurfaceNormal(3, verts, normal);
    if (!(normal[2] < 0.0f)) {
        result = 0;
    }
    return result;
}

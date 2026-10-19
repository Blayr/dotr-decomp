/* Effect helpers, part 3 of 4 of one original Konami file: Lk* counters, vectors, coordinates, UV assignment. */

#include "common.h"

/* Asks for the second effect texture set (category 4) into `out`. */
s32 LkInitTex2(s32 *out) {
    extern s32 SzText_LoadRequest();

    *out = SzText_LoadRequest(4);
    return 0;
}

/* Asks for the battle effect texture set into `out`. */
s32 LkInitTexBtl(s32 *out) {
    extern s32 SzText_LoadRequest();

    *out = SzText_LoadRequest(5);
    return 0;
}

/* Steps byte `p` up by `step` towards `target`; 0 once it got there. */
s32 LkIncrBYTE(u8 *p, u8 target, u8 step) {
    u8 value;

    value = *p;
    if (value <= (target - step)) {
        *p = value + step;
        return 1;
    }
    *p = target;
    return 0;
}

/* Steps a short `p` up by `step` towards `target`; 0 once it got there. */
s32 LkIncrSHORT(s16 *p, s32 target, s32 step) {
    s16 value;
    s32 result;

    value = *p;
    if (value <= ((s16) target - (s16) step)) {
        *p = value + step;
        result = 1;
    } else {
        *p = (s16) target;
        result = 0;
    }
    return result;
}

/* Steps an int `p` up by `step` towards `target`; 0 once it got there. */
s32 LkIncrINT(s32 *p, s32 target, s32 step) {
    s32 value;
    s32 result;

    value = *p;
    if (value <= (target - step)) {
        *p = value + step;
        result = 1;
    } else {
        *p = target;
        result = 0;
    }
    return result;
}

/* Steps a float `p` up by `step` towards `target`; 0 once it got there. */
s32 LkIncrFLOAT(f32 *p, f32 target, f32 step) {
    f32 value;

    value = *p;
    if (value <= (target - step)) {
        *p = value + step;
        return 1;
    }
    *p = target;
    return 0;
}

/* Steps the three values of `values` up by `step` towards `target`; 0 once all got there. */
s32 LkIncrVec(f32 *values, f32 target, f32 step) {
    f32 limit = target - step;
    s32 flags = 0;

    if (values[0] <= limit) {
        values[0] += step;
        flags |= 1;
    } else {
        values[0] = target;
        flags &= ~1;
    }
    if (values[1] <= limit) {
        values[1] += step;
        flags |= 2;
    } else {
        values[1] = target;
        flags &= ~2;
    }
    if (values[2] <= limit) {
        values[2] += step;
        flags |= 4;
    } else {
        values[2] = target;
        flags &= ~4;
    }
    return flags;
}

/* Steps byte `p` down by `step` towards `target`; 0 once it got there. */
s32 LkDecrBYTE(u8 *p, u8 target, s32 step) {
    u8 value;

    value = *p;
    if ((s32) value >= ((target & 0xFF) + (step & 0xFF))) {
        *p = value - step;
        return 1;
    }
    *p = target;
    return 0;
}

/* Steps a short `p` down by `step` towards `target`; 0 once it got there. */
s32 LkDecrSHORT(s16 *p, s16 target, s16 step) {
    s16 value;

    value = *p;
    if (value >= target + step) {
        *p = value - step;
        return 1;
    }
    *p = (s16) target;
    return 0;
}

/* Steps an int `p` down by `step` towards `target`; 0 once it got there. */
s32 LkDecrINT(s32 *p, s32 target, s32 step) {
    s32 value;

    value = *p;
    if (value >= (target + step)) {
        *p = value - step;
        return 1;
    }
    *p = target;
    return 0;
}

/* Steps a float `p` down by `step` towards `target`; 0 once it got there. */
s32 LkDecrFLOAT(f32 *p, f32 target, f32 step) {
    f32 value;

    value = *p;
    if (!(value < (target + step))) {
        *p = value - step;
        return 1;
    }
    *p = target;
    return 0;
}

/* Steps the three values of `values` down by `step` towards `target`; 0 once all got there. */
s32 LkDecrVec(void *valuesIn, f32 target, f32 step) {
    f32 *values = (f32 *)valuesIn;
    f32 threshold = target + step;
    s32 flags = 0;

    if (!(values[0] < threshold)) {
        flags |= 1;
        values[0] -= step;
    } else {
        values[0] = target;
        flags &= ~1;
    }
    if (!(values[1] < threshold)) {
        flags |= 2;
        values[1] -= step;
    } else {
        values[1] = target;
        flags &= ~2;
    }
    if (!(values[2] < threshold)) {
        flags |= 4;
        values[2] -= step;
    } else {
        values[2] = target;
        flags &= ~4;
    }
    return flags;
}

/* dst += src (3 floats). */
void LkAddVector(void *dst, void *src) {
    ((f32 *)dst)[0] += ((f32 *)src)[0];
    ((f32 *)dst)[1] += ((f32 *)src)[1];
    ((f32 *)dst)[2] += ((f32 *)src)[2];
}

/* dst -= src (3 floats). */
void LkSubVector(void *dstVec, void *srcVec) {
    f32 *dst = dstVec;
    f32 *src = srcVec;

    dst[0] -= src[0];
    dst[1] -= src[1];
    dst[2] -= src[2];
}

/* dst *= src (3 floats, one by one). */
void LkMulVector(void *dstVec, void *srcVec) {
    f32 *dst = dstVec;
    const f32 *src = srcVec;

    dst[0] *= src[0];
    dst[1] *= src[1];
    dst[2] *= src[2];
}

/* The point halfway between a and b into `out`. */
void LkGetCenter(f32 *a, f32 *b, f32 *out) {
    f32 delta[3];

    delta[0] = b[0];
    delta[1] = b[1];
    delta[2] = b[2];
    delta[0] -= a[0];
    delta[1] -= a[1];
    delta[2] -= a[2];
    delta[0] /= 2.0f;
    delta[1] /= 2.0f;
    delta[2] /= 2.0f;
    out[0] = a[0];
    out[1] = a[1];
    out[2] = a[2];
    out[0] += delta[0];
    out[1] += delta[1];
    out[2] += delta[2];
}

/* The angle of a 2D vector, turned by 90 degrees. */
void LkSetAngleXY_m90(void *vec) {
    f32 *vector = vec;

    func_001A22C0(90.0f + (360.0f / (6.2831855f / func_001A6C18(vector[1], vector[0]))));
}

/* The screen angle (0..0xFFFF) from world point `to` to world point `from`, projected through the object's matrix. */
s32 LkSetAngleW2S(u8 *object, s32 from, s32 to) {
    extern s32 func_001A22C0(f32);
    u16 point1[4];
    u16 point2[4];
    s32 depth;

    Ex3d_RotTransPers(from, object + 0x30, point1, &depth);
    Ex3d_RotTransPers(to, object + 0x30, point2, &depth);
    return func_001A22C0(65536.0f *
        (func_001A6C18((f32)((s32)(point1[0] - point2[0]) >> 4),
                      (f32)((s32)(point1[1] - point2[1]) >> 4)) / 6.2831855f)) % 65536;
}

/* Sets a coordinate record to scale 1, no rotation, no move. */
void LkInitCoordinate(void *coord) {
    f32 *values = coord;

    values[3] = 1.0f;
    values[2] = 1.0f;
    values[1] = 1.0f;
    values[0] = 1.0f;
    values[7] = 0.0f;
    values[6] = 0.0f;
    values[5] = 0.0f;
    values[4] = 0.0f;
    values[11] = 0.0f;
    values[10] = 0.0f;
    values[9] = 0.0f;
    values[8] = 0.0f;
}

typedef struct {
    f32 values[4][4];
} Matrix_001038D0;

typedef struct {
    f32 eye[4];
    f32 target[4];
    f32 up[4];
    Matrix_001038D0 matrix;
} Camera_001038D0;

/* Builds a camera record's matrix: world-to-screen times its scale, rotation and position. */
void LkSetCoordinate(void *coordinate) {
    Camera_001038D0 *camera = coordinate;
    Matrix_001038D0 matrix;

    RhView_GetWorldScreenMatrix(&camera->matrix);
    RhGeom_GetScaleRotXYZTransMatrix(&matrix, camera->eye, camera->target, camera->up);
    RhGeom_MulMatrix((s32)&camera->matrix, &matrix);
}

typedef struct Transform_00103920 {
    f32 field0[4];
    f32 field10[4];
    f32 field20[4];
    f32 field30[16];
} Transform_00103920;

/* Places an object at screen point (x, y), facing the camera, and builds its matrix. */
s32 LkChange2D(void *object, f32 x, f32 y) {
    Transform_00103920 *transform = object;
    f32 vector[4];
    f32 matrix[16];

    Ex3d_GetPointOnScreen(vector, x, y);
    LkRotSF(object);
    transform->field20[0] = vector[0];
    transform->field20[1] = vector[1];
    transform->field20[2] = vector[2];
    RhView_GetWorldScreenMatrix(transform->field30);
    RhGeom_GetScaleRotXYZTransMatrix(matrix, transform->field0, transform->field10, transform->field20);
    RhGeom_MulMatrix((s32)transform->field30, matrix);
    return 0;
}

typedef struct Vec3_001039A0 {
    s32 x;
    s32 y;
    s32 z;
} Vec3_001039A0;

typedef struct Object_001039A0 {
    s32 leading[4];
    Vec3_001039A0 values10;
    s32 padding1C;
    Vec3_001039A0 values20;
    s32 padding2C;
    f32 matrix[4][4];
} Object_001039A0;

/* Turns an object to face the camera and builds its matrix; returns its heading. */
s32 LkRotSF(void *obj) {
    s32 vector[4];
    f32 matrix[4][4];
    Object_001039A0 *object = obj;

    Ex3d_GetLookVector((s32) &vector);
    object->values10.y = vector[1] % 0x10000;
    object->values10.x = vector[0];
    object->values10.z = vector[2];
    RhView_GetWorldScreenMatrix(object->matrix);
    RhGeom_GetScaleRotXYZTransMatrix(matrix, object, &object->values10, &object->values20);
    RhGeom_MulMatrix((s32)object->matrix, matrix);
    return vector[1];
}

/* The rotation (pitch, heading) that points along `vec`. */
s32 LkVec2Rot(f32 *vec, s32 *rot) {
    rot[1] = (s32)(65536.0f * (func_001A6C18(vec[0], vec[2]) / 6.2831855f)) % 65536;
    rot[0] = (s32)(65536.0f * (func_001A6C18(vec[2], vec[1]) / 6.2831855f)) % 65536;
    rot[2] = (s32)(65536.0f * (func_001A6C18(vec[1], vec[0]) / 6.2831855f)) % 65536;
    rot[3] = 0;
    return 0;
}

/* The rotation in the x/y plane that points along `vec`. */
s32 LkVec2RotXY(f32 *vec, s32 *rot) {
    rot[1] = (s32)(65536.0f * (func_001A6C18(vec[0], vec[2]) / 6.2831855f)) % 65536;
    rot[0] = (s32)(65536.0f * (func_001A6C18(func_001A6C60(vec[0] * vec[0] + vec[2] * vec[2]), vec[1]) / 6.2831855f)) % 65536;
    rot[3] = 0;
    rot[2] = 0;
    return 0;
}

/* The rotation matrix that points along `vec` into `out`. */
s32 LkVec2Mat(Vec4f *vec, void *out) {
    Vec4f sp20;
    Vec4f sp30;
    Vec4f sp40;
    void RhGeom_GetRotVectorMatrix();

    sp20 = *vec;
    RhGeom_NormalizeVector(&sp20.x);
    sp30.z = 0.0f;
    sp30.x = 0.0f;
    sp30.y = 1.0f;
    RhGeom_NormalizeVector(&sp30.x);
    RhGeom_OuterProduct(&sp40.x, &sp30.x, &sp20.x);
    RhGeom_GetRotVectorMatrix(out, &sp40, func_001A22C0(65536.0f * (func_001A6C00(RhGeom_GetVectorScalor(&sp40.x)) / 6.2831855f)));
    return 0;
}

/* The signed shortest difference between two angles (0..0xFFFF). */
s32 LkRegulateRotBorder(s32 a, s32 b) {
    s32 result;

    if (b < a) {
        if ((a - b) % 0x10000 <= 0x8000) {
            result = a - b;
        } else {
            result = -((0x10000 - a) + b);
        }
    } else {
        if (a < b) {
            if ((b - a) % 0x10000 <= 0x8000) {
                result = -(b - a);
            } else {
                result = (0x10000 - b) + a;
            }
        } else {
            result = 0;
        }
    }
    return result;
}

/* The rotation (pitch, heading) from `to` towards `from` into `rot`. */
s32 LkChangeAxisY(f32 *from, f32 *to, s32 *rot) {
    extern s32 func_001A22C0(f32);
    f32 x;
    f32 y;
    f32 z;

    x = from[0] - to[0];
    y = from[1] - to[1];
    z = from[2] - to[2];
    rot[1] = func_001A22C0(65536.0f * (func_001A6C18(x, z) / 6.2831855f)) % 65536;
    rot[0] = func_001A22C0(65536.0f * (func_001A6C18(func_001A6C60(x * x + z * z), y) / 6.2831855f)) % 65536;
    rot[3] = 0;
    rot[2] = 0;
    return 0;
}

/* The game angle of a 2D direction. */
static inline s32 angle_00103EC0(f32 a, f32 b) {
    extern s32 func_001A22C0(f32);
    return func_001A22C0(65536.0f * (func_001A6C18(a, b) / 6.2831855f)) % 65536;
}

/* The signed shortest difference between two angles. */
static inline s32 difference_00103EC0(s32 target, s32 current) {
    s32 difference;

    if (current < target) {
        difference = target - current;
        if (difference % 65536 <= 32768) {
            return difference;
        } else {
            return -((65536 - target) + current);
        }
    } else if (target < current) {
        difference = current - target;
        if (difference % 65536 <= 32768) {
            return -difference;
        } else {
            return (65536 - current) + target;
        }
    } else {
        return 0;
    }
}

/* Moves `position` towards `target` like a homing missile, turning `velocity` by at most `limit`. */
s32 LkMoveHoming(f32 *position, f32 *target, f32 *velocity, s32 limit) {
    f32 matrix[4][4];
    s32 rotation[4];
    f32 movement[4];
    s32 targetYaw;
    s32 targetPitch;
    s32 targetRoll;
    s32 currentYaw;
    s32 currentPitch;
    s32 currentRoll;

    target[0] -= position[0];
    target[1] -= position[1];
    target[2] -= position[2];
    targetYaw = angle_00103EC0(target[0], target[2]);
    targetPitch = angle_00103EC0(target[2], target[1]);
    targetRoll = angle_00103EC0(target[1], target[0]);
    currentYaw = angle_00103EC0(velocity[0], velocity[2]);
    currentPitch = angle_00103EC0(velocity[2], velocity[1]);
    currentRoll = angle_00103EC0(velocity[1], velocity[0]);

    rotation[0] = difference_00103EC0(targetPitch, currentPitch);
    rotation[1] = difference_00103EC0(targetYaw, currentYaw);
    rotation[2] = difference_00103EC0(targetRoll, currentRoll);
    rotation[3] = 0;

    if (rotation[0] >= limit) {
        rotation[0] = limit;
    } else if (rotation[0] <= -limit) {
        rotation[0] = -limit;
    }
    if (rotation[1] >= limit) {
        rotation[1] = limit;
    } else if (rotation[1] <= -limit) {
        rotation[1] = -limit;
    }
    if (rotation[2] >= limit) {
        rotation[2] = limit;
    } else if (rotation[2] <= -limit) {
        rotation[2] = -limit;
    }

    RhGeom_GetRotXYZMatrix(matrix, rotation);
    RhGeom_MulMatrixVector(movement, matrix, velocity);
    position[0] += movement[0];
    position[1] += movement[1];
    position[2] += movement[2];
    velocity[0] = movement[0];
    velocity[1] = movement[1];
    velocity[2] = movement[2];
    velocity[3] = 0.0f;
    return 0;
}

typedef struct {
    f32 x, y, z, w;
} Vec4_001043F0;

extern Vec4_001043F0 D_0028C220;

/* A random direction of length `length` into `out`. */
s32 LkGetRandVec(void *out, f32 length) {
    f32 matrix[4][4];
    Vec4_001043F0 vector;
    s32 angles[3];

    vector = D_0028C220;
    vector.y = length;
    angles[0] = func_0019A5C8() % 0x10000;
    angles[1] = func_0019A5C8() % 0x10000;
    angles[2] = 0;
    RhGeom_GetRotXYZMatrix(matrix, angles);
    RhGeom_MulMatrixVector(out, matrix, &vector);
    return 0;
}

/* Moves `pos` a 1/`steps` part of the way to `target` (all the way for 0). */
void LkOBJ_TransitVector(f32 *pos, f32 *target, s32 steps) {
    f32 x;
    f32 y;
    f32 z;

    if (steps != 0) {
        x = target[0];
        y = target[1];
        z = target[2];
        x -= pos[0];
        y -= pos[1];
        z -= pos[2];
        x /= (f32)steps;
        pos[0] += x;
        y /= (f32)steps;
        pos[1] += y;
        z /= (f32)steps;
        pos[2] += z;
    } else {
        pos[0] = target[0];
        pos[1] = target[1];
        pos[2] = target[2];
    }
}

/* Whether bit `bit` of `flags` is set. */
s32 LkCheckFlag(s32 flags, s32 bit) {
    return !(flags & (1 << bit)) ? 0 : 1;
}

typedef struct {
    u16 val : 14;
    u16 hi : 2;
} Coord_00104540;

typedef struct {
    u8 pad0[8];
    Coord_00104540 x;
    Coord_00104540 y;
    u8 padC[0xC];
} Vert_00104540;

typedef struct {
    u16 pad0;
    u16 flags;
    u8 pad4[0xC];
    Vert_00104540 v[4];
} Sprite_00104540;

typedef struct {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} Rect_00104540;

/* Sets an effect sprite's texture coordinates for its animation frame `frame`. */
s32 LkAssignUV(void *prim, void *anim, s32 frame) {
    Sprite_00104540 *s = prim;
    Rect_00104540 *r = anim;

    s->flags |= 0x800;
    switch (frame) {
    case 0:
        s->v[0].x.val = r->x << 4;
        s->v[0].y.val = r->y << 4;
        s->v[1].x.val = (r->x + r->w) << 4;
        s->v[1].y.val = r->y << 4;
        s->v[2].x.val = r->x << 4;
        s->v[2].y.val = (r->y + r->h) << 4;
        s->v[3].x.val = (r->x + r->w) << 4;
        s->v[3].y.val = (r->y + r->h) << 4;
        break;
    case 1:
        s->v[0].x.val = r->x << 4;
        s->v[0].y.val = r->y << 4;
        s->v[1].x.val = r->x << 4;
        s->v[1].y.val = (r->y + r->h) << 4;
        s->v[2].x.val = (r->x + r->w) << 4;
        s->v[2].y.val = r->y << 4;
        s->v[3].x.val = (r->x + r->w) << 4;
        s->v[3].y.val = (r->y + r->h) << 4;
        break;
    case 2:
        s->v[0].x.val = r->x << 4;
        s->v[0].y.val = (r->y + r->h) << 4;
        s->v[1].x.val = r->x << 4;
        s->v[1].y.val = r->y << 4;
        s->v[2].x.val = (r->x + r->w) << 4;
        s->v[2].y.val = (r->y + r->h) << 4;
        s->v[3].x.val = (r->x + r->w) << 4;
        s->v[3].y.val = r->y << 4;
        break;
    case 3:
        s->v[0].x.val = r->x << 4;
        s->v[0].y.val = (r->y + r->h) << 4;
        s->v[1].x.val = (r->x + r->w) << 4;
        s->v[1].y.val = (r->y + r->h) << 4;
        s->v[2].x.val = r->x << 4;
        s->v[2].y.val = r->y << 4;
        s->v[3].x.val = (r->x + r->w) << 4;
        s->v[3].y.val = r->y << 4;
        break;
    case 4:
        s->v[0].x.val = (r->x + r->w) << 4;
        s->v[0].y.val = r->y << 4;
        s->v[1].x.val = r->x << 4;
        s->v[1].y.val = r->y << 4;
        s->v[2].x.val = (r->x + r->w) << 4;
        s->v[2].y.val = (r->y + r->h) << 4;
        s->v[3].x.val = r->x << 4;
        s->v[3].y.val = (r->y + r->h) << 4;
        break;
    case 5:
        s->v[0].x.val = (r->x + r->w) << 4;
        s->v[0].y.val = r->y << 4;
        s->v[1].x.val = (r->x + r->w) << 4;
        s->v[1].y.val = (r->y + r->h) << 4;
        s->v[2].x.val = r->x << 4;
        s->v[2].y.val = r->y << 4;
        s->v[3].x.val = r->x << 4;
        s->v[3].y.val = (r->y + r->h) << 4;
        break;
    case 6:
        s->v[0].x.val = (r->x + r->w) << 4;
        s->v[0].y.val = (r->y + r->h) << 4;
        s->v[1].x.val = r->x << 4;
        s->v[1].y.val = (r->y + r->h) << 4;
        s->v[2].x.val = (r->x + r->w) << 4;
        s->v[2].y.val = r->y << 4;
        s->v[3].x.val = r->x << 4;
        s->v[3].y.val = r->y << 4;
        break;
    case 7:
        s->v[0].x.val = (r->x + r->w) << 4;
        s->v[0].y.val = (r->y + r->h) << 4;
        s->v[1].x.val = (r->x + r->w) << 4;
        s->v[1].y.val = r->y << 4;
        s->v[2].x.val = r->x << 4;
        s->v[2].y.val = (r->y + r->h) << 4;
        s->v[3].x.val = r->x << 4;
        s->v[3].y.val = r->y << 4;
        break;
    }
    return 0;
}

typedef struct {
    u16 val : 14;
    u16 hi : 2;
} Coord_00104DC0;

typedef struct {
    u8 pad0[8];
    union {
        struct {
            Coord_00104DC0 x;
            Coord_00104DC0 y;
        } uv;
        struct {
            f32 s;
            f32 t;
        } st;
    } tex;
    u8 pad10[8];
} Vert_00104DC0;

typedef struct {
    u16 pad0;
    u16 flags;
    u8 pad4[0xC];
    Vert_00104DC0 v[4];
} Sprite_00104DC0;

typedef struct {
    s16 u;
    s16 v;
    s16 w;
    s16 h;
    s16 baseU;
    s16 baseV;
    s16 texW;
    s16 texH;
} Cell_00104DC0;

typedef struct {
    f32 x;
    f32 y;
    f32 w;
    f32 h;
} Rect_00104DC0;

typedef struct {
    union {
        Cell_00104DC0 i;
        Rect_00104DC0 f;
    } r;
    u8 pad10[0x28];
    s32 flags;
    u8 pad3C[0xC];
    s16 timer;
    s16 delay;
    s16 last;
    s16 loopLength;
    s16 frame;
    s16 loop;
} Anim_00104DC0;

/* Whether an animation flag bit is set. */
static inline s32 flag_00104DC0(Anim_00104DC0 *anim, s32 bit) {
    return (anim->flags & bit) ? 1 : 0;
}

/* Sets an effect sprite's texture coordinates (ST form) for its current animation frame. */
void LkAssignUVST(void *prim, void *animIn) {
    Sprite_00104DC0 *sprite = prim;
    Anim_00104DC0 *anim = animIn;

    if (flag_00104DC0(anim, 1)) {
        if (flag_00104DC0(anim, 2)) {
            anim->r.i.u = anim->r.i.baseU + anim->r.i.w * (anim->frame % (anim->r.i.texW / anim->r.i.w));
            anim->r.i.v = anim->r.i.baseV + anim->r.i.h * (anim->frame / (anim->r.i.texW / anim->r.i.w));
        } else {
            anim->r.i.u = anim->r.i.baseU + anim->r.i.w * (anim->frame / (anim->r.i.texH / anim->r.i.h));
            anim->r.i.v = anim->r.i.baseV + anim->r.i.h * (anim->frame % (anim->r.i.texH / anim->r.i.h));
        }
        sprite->flags |= 0x800;
        sprite->v[0].tex.uv.x.val = anim->r.i.u << 4;
        sprite->v[0].tex.uv.y.val = anim->r.i.v << 4;
        sprite->v[1].tex.uv.x.val = (anim->r.i.u + anim->r.i.w) << 4;
        sprite->v[1].tex.uv.y.val = anim->r.i.v << 4;
        sprite->v[2].tex.uv.x.val = anim->r.i.u << 4;
        sprite->v[2].tex.uv.y.val = (anim->r.i.v + anim->r.i.h) << 4;
        sprite->v[3].tex.uv.x.val = (anim->r.i.u + anim->r.i.w) << 4;
        sprite->v[3].tex.uv.y.val = (anim->r.i.v + anim->r.i.h) << 4;
    } else {
        if (flag_00104DC0(anim, 2)) {
            anim->r.f.x = anim->r.f.w * (f32)(anim->frame % (s16)(1.0f / anim->r.f.w));
            anim->r.f.y = anim->r.f.h * (f32)(anim->frame / (s16)(1.0f / anim->r.f.w));
        } else {
            anim->r.f.x = anim->r.f.w * (f32)(anim->frame / (s16)(1.0f / anim->r.f.h));
            anim->r.f.y = anim->r.f.h * (f32)(anim->frame % (s16)(1.0f / anim->r.f.h));
        }
        sprite->v[0].tex.st.s = anim->r.f.x;
        sprite->v[0].tex.st.t = anim->r.f.y;
        sprite->v[1].tex.st.s = anim->r.f.x + anim->r.f.w;
        sprite->v[1].tex.st.t = anim->r.f.y;
        sprite->v[2].tex.st.s = anim->r.f.x;
        sprite->v[2].tex.st.t = anim->r.f.y + anim->r.f.h;
        sprite->v[3].tex.st.s = anim->r.f.x + anim->r.f.w;
        sprite->v[3].tex.st.t = anim->r.f.y + anim->r.f.h;
    }
    anim->timer++;
    if (anim->timer > anim->delay) {
        anim->timer = 0;
        anim->frame++;
        if (anim->frame > anim->last) {
            if (anim->loop == 999) {
                anim->frame = anim->last - anim->loopLength + 1;
            } else {
                anim->loop = 1;
            }
        }
    }
}

typedef struct UV_00105260 {
    u16 u : 14;
    u16 unusedU : 2;
    u16 v : 14;
    u16 unusedV : 2;
} UV_00105260;

typedef struct Frame_00105260 {
    f32 x;
    f32 y;
    u32 unused;
    s16 index;
    s16 timer;
} Frame_00105260;

typedef struct State_00105260 {
    u32 unused0;
    u32 flags;
    u8 unused8[8];
    f32 x;
    f32 y;
    u8 unused18[8];
    union {
        struct {
            s16 u, v;
            s16 width, height;
            s16 baseU, baseV;
            s16 imageWidth, imageHeight;
        } fixed;
        struct {
            f32 u, v;
            f32 width, height;
        } floating;
    } uv;
    Frame_00105260 frames[16];
    u8 unused130[6];
    s16 randomX;
    s16 randomY;
    s16 unused13A;
    s16 delay;
    s16 end;
    s16 rewind;
} State_00105260;

/* Whether a state flag bit is set. */
static inline s32 flag_00105260(State_00105260 *s, s32 bit) {
    return (s->flags & bit) ? 1 : 0;
}

/* Sets a triangle effect sprite's texture coordinates (ST form) for frame `frame`. */
void LkAssignUVST3(void *prim, void *anim, s32 frame) {
    State_00105260 *state = anim;
    u8 *packet = prim;

    if (flag_00105260(state, 1)) {
        if (flag_00105260(state, 2)) {
            state->uv.fixed.u = state->uv.fixed.baseU + state->uv.fixed.width *
                (state->frames[frame].index % (state->uv.fixed.imageWidth / state->uv.fixed.width));
            state->uv.fixed.v = state->uv.fixed.baseV + state->uv.fixed.height *
                (state->frames[frame].index / (state->uv.fixed.imageWidth / state->uv.fixed.width));
        } else {
            state->uv.fixed.u = state->uv.fixed.baseU + state->uv.fixed.width *
                (state->frames[frame].index / (state->uv.fixed.imageHeight / state->uv.fixed.height));
            state->uv.fixed.v = state->uv.fixed.baseV + state->uv.fixed.height *
                (state->frames[frame].index % (state->uv.fixed.imageHeight / state->uv.fixed.height));
        }
        *(u16 *)(packet + 2) |= 0x800;
        ((UV_00105260 *)(packet + 0x18))->u = state->uv.fixed.u << 4;
        ((UV_00105260 *)(packet + 0x18))->v = state->uv.fixed.v << 4;
        ((UV_00105260 *)(packet + 0x30))->u = (state->uv.fixed.u + state->uv.fixed.width - 1) << 4;
        ((UV_00105260 *)(packet + 0x30))->v = state->uv.fixed.v << 4;
        ((UV_00105260 *)(packet + 0x48))->u = state->uv.fixed.u << 4;
        ((UV_00105260 *)(packet + 0x48))->v = (state->uv.fixed.v + state->uv.fixed.height - 1) << 4;
        ((UV_00105260 *)(packet + 0x60))->u = (state->uv.fixed.u + state->uv.fixed.width - 1) << 4;
        ((UV_00105260 *)(packet + 0x60))->v = (state->uv.fixed.v + state->uv.fixed.height - 1) << 4;
    } else {
        if (flag_00105260(state, 2)) {
            state->uv.floating.u = state->uv.floating.width *
                (state->frames[frame].index % (s16)(1.0f / state->uv.floating.width));
            state->uv.floating.v = state->uv.floating.height *
                (state->frames[frame].index / (s16)(1.0f / state->uv.floating.width));
        } else {
            state->uv.floating.u = state->uv.floating.width *
                (state->frames[frame].index / (s16)(1.0f / state->uv.floating.height));
            state->uv.floating.v = state->uv.floating.height *
                (state->frames[frame].index % (s16)(1.0f / state->uv.floating.height));
        }
        *(f32 *)(packet + 0x18) = state->uv.floating.u;
        *(f32 *)(packet + 0x1C) = state->uv.floating.v;
        *(f32 *)(packet + 0x30) = state->uv.floating.u + state->uv.floating.width;
        *(f32 *)(packet + 0x34) = state->uv.floating.v;
        *(f32 *)(packet + 0x48) = state->uv.floating.u;
        *(f32 *)(packet + 0x4C) = state->uv.floating.v + state->uv.floating.height;
        *(f32 *)(packet + 0x60) = state->uv.floating.u + state->uv.floating.width;
        *(f32 *)(packet + 0x64) = state->uv.floating.v + state->uv.floating.height;
    }

    state->frames[frame].timer++;
    if (state->frames[frame].timer > state->delay) {
        state->frames[frame].timer = 0;
        state->frames[frame].index++;
        if (state->frames[frame].index > state->end) {
            if (flag_00105260(state, 4)) {
                s16 range;
                state->frames[frame].x = state->x;
                state->frames[frame].y = state->y;
                range = state->randomX;
                if (range != 0) {
                    state->frames[frame].x = state->x + (func_0019A5C8() % (range * 2) - range);
                }
                range = state->randomY;
                if (range != 0) {
                    state->frames[frame].y = state->y + (func_0019A5C8() % (range * 2) - range);
                }
                if (state->randomY < 0) {
                    state->frames[frame].y = state->y + func_0019A5C8() % state->randomY;
                }
            }
            state->frames[frame].index -= state->rewind;
        }
    }
}

typedef struct {
    s16 x, y, width, height;
    s16 origin_x, origin_y, sheet_width, sheet_height;
    u8 pad10[0x28];
    s32 flags;
    u8 pad3C[0xC];
    s16 tick, delay, last_frame, loop_length, frame, state;
} Animation_00105830;

typedef struct {
    u16 value : 14;
    u16 unused : 2;
} Coordinate_00105830;

typedef struct {
    u16 unused, flags;
    u8 pad04[0x14];
    Coordinate_00105830 x0, y0;
    u8 pad1C[0x14];
    Coordinate_00105830 x1, y1;
    u8 pad34[0x14];
    Coordinate_00105830 x2, y2;
    u8 pad4C[0x14];
    Coordinate_00105830 x3, y3;
} Packet_00105830;

/* Sets an effect sprite's texture coordinates (second layout) for frame `frame`. */
void LkAssignUV2(void *prim, void *animIn, s32 frame) {
    Packet_00105830 *packet = prim;
    Animation_00105830 *anim = animIn;

    if ((!(anim->flags & 2) ? 0 : 1) != 0) {
        anim->x = anim->origin_x + anim->width * (anim->frame % (anim->sheet_width / anim->width));
        anim->y = anim->origin_y + anim->height * (anim->frame / (anim->sheet_width / anim->width));
    } else {
        anim->x = anim->origin_x + anim->width * (anim->frame / (anim->sheet_height / anim->height));
        anim->y = anim->origin_y + anim->height * (anim->frame % (anim->sheet_height / anim->height));
    }

    if (frame == 0) {
        packet->flags |= 0x800;
        packet->x0.value = anim->x * 16;
        packet->y0.value = anim->y * 16;
        packet->x1.value = (anim->x + anim->width - 1) * 16;
        packet->y1.value = anim->y * 16;
        packet->x2.value = anim->x * 16;
        packet->y2.value = (anim->y + anim->height / 2 - 1) * 16;
        packet->x3.value = (anim->x + anim->width - 1) * 16;
        packet->y3.value = (anim->y + anim->height / 2 - 1) * 16;
    } else {
        packet->flags |= 0x800;
        packet->x0.value = anim->x * 16;
        packet->y0.value = (anim->y + anim->height / 2 - 1) * 16;
        packet->x1.value = (anim->x + anim->width - 1) * 16;
        packet->y1.value = (anim->y + anim->height / 2 - 1) * 16;
        packet->x2.value = anim->x * 16;
        packet->y2.value = (anim->y + anim->height - 1) * 16;
        packet->x3.value = (anim->x + anim->width - 1) * 16;
        packet->y3.value = (anim->y + anim->height - 1) * 16;
    }

    if (frame == 1) {
        anim->tick++;
        if (anim->tick > anim->delay) {
            anim->tick = 0;
            anim->frame++;
            if (anim->frame > anim->last_frame) {
                if (anim->state == 999) {
                    anim->frame = anim->last_frame - anim->loop_length + 1;
                } else {
                    anim->state = 1;
                }
            }
        }
    }
}

/* Advances an effect's texture animation frame. */
s32 LkAssignFrameST(void *anim) {
    Vec4f *v = anim;
    f32 x_ratio;
    f32 y_ratio;
    f32 inverse;
    f32 packed_x;
    s32 func_001A22C0(f32);

    if (v->x == 0.0f) {
        x_ratio = 0.0f;
    } else {
        x_ratio = v->x / v->z;
    }
    inverse = 1.0f / v->w;
    if (v->y == 0.0f) {
        y_ratio = 0.0f;
    } else {
        y_ratio = v->y / v->w;
    }
    packed_x = (f32)func_001A22C0(x_ratio);
    return func_001A22C0(y_ratio + packed_x * inverse);
}

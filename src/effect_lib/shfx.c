/* Effect helpers, part 2 of 4 of one original Konami file: ShFx_* clipping, timers, texture UVs, splines, vibration. */

#include "common.h"

/* Whether a screen vertex is inside the drawable area. */
s32 ShFx_isClip(void *vertex) {
    u16 x;
    u16 y;

    x = ((u16 *)vertex)[0];
    if ((f32)x < 22528.0f) {
        return 0;
    }
    if (!((f32)x <= 43008.0f)) {
        return 0;
    }
    y = ((u16 *)vertex)[1];
    if ((f32)y < 25600.0f) {
        return 0;
    }
    if ((f32)y > 39936.0f) {
        return 0;
    }
    return 1;
}

/* Whether a screen point is inside the drawable area. */
s32 ShFx_isClipSC(void *point) {
    u16 *p = (u16 *)point;
    if ((f32)(u32)p[0] < 27648.0f) return 0;
    if ((f32)(u32)p[0] > 37888.0f) return 0;
    if ((f32)(u32)p[1] < 29184.0f) return 0;
    if ((f32)(u32)p[1] > 36352.0f) return 0;
    return 1;
}

/* The screen size of an object of `size` at depth `w`, at the current lens. */
f32 ShFx_GetDrawSize(f32 size, f32 w) {
    return (size / (w / 256.0f)) * (SzView_GetScreenDistance(0) / 800.0f);
}

/* The rotation (pitch, heading) that points along `vec`. */
void ShFx_Vec2Rot(f32 *vec, s32 *rot) {
    rot[0] = (u16) func_001A22C0(65536.0f * (func_001A6C18(func_001A6C60(vec[0] * vec[0] + vec[2] * vec[2]), vec[1]) / 6.2831855f));
    rot[1] = (u16) func_001A22C0(65536.0f * (func_001A6C18(vec[0], vec[2]) / 6.2831855f));
    rot[2] = 0;
}

/* The rotation matrix that points along `src`. */
void ShFx_Vec2Mat(f32 *src, void *dst) {
    extern void RhGeom_GetRotXYZMatrix(void *, s32 *);
    s32 angles[3];

    angles[0] = (u16)func_001A22C0(65536.0f * (func_001A6C18(func_001A6C60(src[0] * src[0] + src[2] * src[2]), src[1]) / 6.2831855f));
    angles[1] = (u16)func_001A22C0(65536.0f * (func_001A6C18(src[0], src[2]) / 6.2831855f));
    angles[2] = 0;
    RhGeom_GetRotXYZMatrix(dst, angles);
}

/* Starts effect timer `timer`: `count` ticks after `delay`, with `step`. */
void ShFx_initTimer(s8 *timer, s8 count, s8 delay, s8 step) {
    timer[2] = count;
    timer[0] = count;
    timer[1] = delay;
    timer[3] = step;
}

typedef struct Timer_00101AF0 {
    u8 count;
    u8 delay;
} Timer_00101AF0;

/* Ticks an effect timer: 1 when a tick fires. */
s32 ShFx_isTimer(void *timerIn) {
    Timer_00101AF0 *timer = timerIn;
    u8 delay;
    u8 count;

    count = timer->count;
    if (count == 0) {
        return 0;
    }
    delay = timer->delay;
    if (delay != 0) {
        timer->delay = (u8) (delay - 1);
        return 0;
    }
    timer->count = (u8) (count - 1);
    return 1;
}

/* Starts a particle timer: `count` ticks after `delay`. */
void ShFx_initPartsTimer(void *timer, s8 count, s8 delay) {
    ((s8 *)timer)[2] = count;
    ((s8 *)timer)[0] = count;
    ((s8 *)timer)[1] = delay;
}

typedef struct Counter_00101B50 {
    u8 count;
    u8 delay;
} Counter_00101B50;

/* Ticks a particle timer: 1 when a tick fires. */
s32 ShFx_isPartsTimer(void *timer) {
    Counter_00101B50 *counter = timer;

    if (counter->count == 0) {
        return 0;
    }
    if (counter->delay != 0) {
        counter->delay--;
        return 0;
    }
    counter->count--;
    return 1;
}

/* Moves an effect point onto its anchor (the effect's source or target model), into `out`. */
void ShFx_AdjustPoint(void *point, s32 out) {
    u8 anchor;

    anchor = *((u8 *)point + 5);
    switch (anchor) {
    case 0:
        return;
    case 1:
        SzEffect_GetRef2(SzEffect_GetFrom(anchor), *((u8 *)point + 6), out);
        return;
    case 2:
        SzEffect_GetRef2(SzEffect_GetTarget(anchor), *((u8 *)point + 6), out);
        return;
    }
}

/* The first free record of `count` records of `size` bytes, or -1. */
s32 ShFx_GetTempIndex(u8 *records, s32 size, s32 count) {
    s32 offset;
    s32 i;

    i = 0;
    if (i < count) {
        offset = 0;
        do {
            if (records[offset] == 0) {
                return i;
            }
            i++;
            offset += size;
        } while (i < count);
    }
    return -1;
}

/* The alpha blend words for an effect sprite's blend mode into `out`. */
void ShFx_GetAlpha(void *sprite, void *outIn) {
    s8 *out = (s8 *)outIn;

    switch (((u8 *)sprite)[5]) {
    case 1:
        out[0] = 0;
        out[1] = 1;
        out[2] = 0;
        out[3] = 1;
        break;
    case 2:
        out[0] = 0;
        out[1] = 2;
        out[2] = 0;
        out[3] = 1;
        break;
    case 3:
        out[0] = 1;
        out[1] = 0;
        out[2] = 0;
        out[3] = 1;
        break;
    case 4:
        out[0] = 2;
        out[1] = 0;
        out[2] = 0;
        out[3] = 1;
        break;
    }
}

typedef struct Coord_00101D20 {
    u16 val : 14;
    u16 hi : 2;
} Coord_00101D20;

typedef struct Vert_00101D20 {
    u8 pad0[8];
    Coord_00101D20 x;
    Coord_00101D20 y;
    u8 padC[4];
} Vert_00101D20;

typedef struct Sprite_00101D20 {
    u16 pad0;
    u16 flags;
    u8 pad4[0xC];
    Vert_00101D20 v[4];
} Sprite_00101D20;

/* Fills a flat-shaded textured sprite from an effect's texture rectangle. */
void ShFx_SetTexFT4(void *prim, void *rect, void *texture) {
    Sprite_00101D20 *dst = prim;
    s32 *src = rect;
    u8 alpha[4];

    dst->flags |= 0x800;
    dst->v[0].x.val = src[2] << 4;
    dst->v[0].y.val = src[4] << 4;
    dst->v[1].x.val = src[3] << 4;
    dst->v[1].y.val = src[4] << 4;
    dst->v[2].x.val = src[2] << 4;
    dst->v[2].y.val = src[5] << 4;
    dst->v[3].x.val = src[3] << 4;
    dst->v[3].y.val = src[5] << 4;
    ExAssignClamp(prim, 0xA | ((s64)src[2] << 4) | ((s64)(src[3] - 1) << 14) | ((s64)src[4] << 24) |
                            ((s64)(src[5] - 1) << 34));
    ExAssignTexture(prim, texture, 1);
    ShFx_GetAlpha(rect, alpha);
    ExAssignAlpha(prim, (s64)alpha[0] | ((s64)alpha[1] << 2) | ((s64)alpha[2] << 4) | ((s64)alpha[3] << 6));
}

typedef struct Coord_00101EE0 {
    u16 val : 14;
    u16 hi : 2;
} Coord_00101EE0;

typedef struct Vert_00101EE0 {
    u8 pad0[8];
    Coord_00101EE0 x;
    Coord_00101EE0 y;
    u8 padC[0xC];
} Vert_00101EE0;

typedef struct Sprite_00101EE0 {
    u16 pad0;
    u16 flags;
    u8 pad4[0xC];
    Vert_00101EE0 v[4];
} Sprite_00101EE0;

/* Fills a Gouraud-shaded textured sprite from an effect's texture rectangle. */
void ShFx_SetTexGT4(void *prim, void *rect, void *texture) {
    Sprite_00101EE0 *dst = prim;
    s32 *src = rect;
    u8 alpha[4];

    dst->flags |= 0x800;
    dst->v[0].x.val = src[2] << 4;
    dst->v[0].y.val = src[4] << 4;
    dst->v[1].x.val = src[3] << 4;
    dst->v[1].y.val = src[4] << 4;
    dst->v[2].x.val = src[2] << 4;
    dst->v[2].y.val = src[5] << 4;
    dst->v[3].x.val = src[3] << 4;
    dst->v[3].y.val = src[5] << 4;
    ExAssignClamp(prim, 0xA | ((s64)src[2] << 4) | ((s64)(src[3] - 1) << 14) | ((s64)src[4] << 24) |
                            ((s64)(src[5] - 1) << 34));
    ExAssignTexture(prim, texture, 1);
    if (((u8 *)rect)[5] != 0) {
        ShFx_GetAlpha(rect, alpha);
        ExAssignAlpha(prim, (s64)alpha[0] | ((s64)alpha[1] << 2) | ((s64)alpha[2] << 4) | ((s64)alpha[3] << 6));
    }
}

/* Sets an effect sprite's texture rectangle for frame `index` of its animation `mode`. */
void ShFx_SetUV(s32 *rect, s32 index, u32 mode, s32 width) {
    s32 height;
    s32 cols;
    s32 rows;

    switch (mode) {
    case 0:
        height = 0x20;
        width = 0x20;
        cols = 4;
        rows = 2;
        break;
    case 1:
        height = 0x20;
        width = 0x20;
        cols = 2;
        rows = 4;
        break;
    case 2:
        height = 0x20;
        width = 0x20;
        rows = 4;
        cols = 4;
        break;
    case 3:
        width = 0x20;
        height = 0x40;
        cols = 8;
        rows = 1;
        break;
    case 4:
        height = 0x40;
        width = 0x40;
        cols = 2;
        rows = 1;
        break;
    case 5:
        height = 0x40;
        width = 0x40;
        rows = 2;
        cols = 2;
        break;
    case 9:
        height = 0x40;
        width = 0x40;
        rows = 1;
        cols = 1;
        break;
    case 6:
        rows = 1;
        width = 0x20;
        height = 0x80;
        cols = 1;
        break;
    case 7:
        rows = 1;
        width = 0x80;
        height = 0x40;
        cols = 1;
        break;
    case 8:
        height = 0x80;
        width = 0x80;
        rows = 1;
        cols = 1;
        break;
    }
    if (cols * rows - 1 < index) {
        rect[5] = 0;
        rect[4] = 0;
        rect[3] = 0;
        rect[2] = 0;
        return;
    }
    rect[2] = width * (index % cols);
    rect[3] = rect[2] + width;
    rect[4] = height * (index / cols);
    rect[5] = rect[4] + height;
}

/* The width and height of an effect texture of `kind` into `outW` / `outH`. */
void ShFx_GetTexWidth(u32 kind, s32 *outW, s32 *outH) {
    switch (kind) {
    case 0:
    case 4:
        *outW = 0x43000000;
        *outH = 0x42800000;
        return;
    case 1:
        *outW = 0x42800000;
        *outH = 0x43000000;
        return;
    case 2:
    case 5:
    case 8:
        *outH = 0x43000000;
        *outW = 0x43000000;
        return;
    case 3:
        *outW = 0x43800000;
        *outH = 0x42800000;
        return;
    case 6:
        *outW = 0x42000000;
        *outH = 0x43000000;
        return;
    case 7:
        *outW = 0x43000000;
        *outH = 0x42800000;
        return;
    case 9:
        *outH = 0x42800000;
        *outW = 0x42800000;
        return;
    default:
        *outH = 0;
        *outW = 0;
        return;
    }
}

/* The animation frame to use for effect texture `kind` at frame `frame`. */
s32 ShFx_GetAnmID(u32 kind, s32 frame) {
    switch (kind) {
    case 0:
    case 1:
    case 3:
        return frame & 7;
    case 4:
        return frame & 1;
    case 2:
        return frame & 0xF;
    case 5:
        return frame & 3;
    case 9:
    default:
        return 0;
    }
}

/* Fills `count` random bytes. */
void ShFx_MakeRnd(s8 *out, s32 count) {
    s8 *p;
    s32 i;

    p = out;
    for (i = 0; i < count; i += 1) {
        *p = (s8) (func_0019A5C8() >> 4);
        p += 1;
    }
}

/* Builds the second-derivative table of a cubic spline through n points. */
void ShFx_Spline_MakeTable(s32 n, f32 *x, f32 *y, f32 *y2) {
    f32 h[8];
    f32 d[8];
    s32 i;
    f32 m;

    y2[n - 1] = 0.0f;
    y2[0] = 0.0f;
    for (i = 0; i < n - 1; i++) {
        h[i] = x[i + 1] - x[i];
        d[i + 1] = (y[i + 1] - y[i]) / h[i];
    }
    y2[1] = (d[2] - d[1]) - h[0] * y2[0];
    d[1] = 2.0f * (x[2] - x[0]);
    for (i = 1; i < n - 2; i++) {
        m = h[i] / d[i];
        y2[i + 1] = (d[i + 2] - d[i + 1]) - m * y2[i];
        d[i + 1] = 2.0f * (x[i + 2] - x[i]) - m * h[i];
    }
    y2[n - 2] -= h[n - 2] * y2[n - 1];
    for (i = n - 2; i > 0; i--) {
        y2[i] = (y2[i] - h[i] * y2[i + 1]) / d[i];
    }
}

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Point_00102550;

typedef struct {
    s32 count;
    f32 x[8];
    f32 y[8];
    f32 z[8];
    Point_00102550 out[28];
} Spline_00102550;

/* A cubic spline's value at `u`. */
static inline f32 sample_00102550(s32 n, f32 *t, f32 *p, f32 *m, f32 u) {
    s32 lo;
    s32 hi;
    s32 mid;
    f32 d;
    f32 h;

    lo = 0;
    hi = n - 1;
    while (lo < hi) {
        mid = (s32)((lo + hi) / 2.0f);
        if (t[mid] < u) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    if (lo > 0) {
        lo--;
    }
    h = t[lo + 1] - t[lo];
    d = u - t[lo];
    return p[lo] + d * ((p[lo + 1] - p[lo]) / h - h * (2.0f * m[lo] + m[lo + 1]) +
                        d * (3.0f * m[lo] + d * (m[lo + 1] - m[lo]) / h));
}

/* Moves an effect along its spline path. */
s32 ShFx_Spline(void *effect) {
    Spline_00102550 *s = effect;
    f32 t[8];
    f32 mx[8];
    f32 my[8];
    f32 mz[8];
    s32 i;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 u;
    f32 step;

    if (s->count < 3 || s->count > 8) {
        return 0;
    }
    t[0] = 0.0f;
    for (i = 1; i < s->count; i++) {
        dx = s->x[i] - s->x[i - 1];
        dy = s->y[i] - s->y[i - 1];
        dz = s->z[i] - s->z[i - 1];
        t[i] = t[i - 1] + func_001A6C60(dx * dx + dy * dy + dz * dz);
    }
    for (i = 1; i < s->count; i++) {
        t[i] /= t[s->count - 1];
    }
    ShFx_Spline_MakeTable(s->count, t, s->x, mx);
    ShFx_Spline_MakeTable(s->count, t, s->y, my);
    ShFx_Spline_MakeTable(s->count, t, s->z, mz);
    step = 1.0f / (4.0f * (f32)(s->count - 1));
    u = 0.0f;
    for (i = 0; i < (s->count - 1) * 4; i++) {
        s->out[i].x = sample_00102550(s->count, t, s->x, mx, u);
        s->out[i].y = sample_00102550(s->count, t, s->y, my, u);
        s->out[i].z = sample_00102550(s->count, t, s->z, mz, u);
        u += step;
    }
    return 1;
}

typedef struct Vec3_00102A50 {
    f32 x;
    f32 y;
    f32 z;
} Vec3_00102A50;

typedef struct Arg_00102A50 {
    s32 count;
    f32 amplitude;
    f32 startX;
    f32 startY;
    f32 startZ;
    f32 endX;
    f32 endY;
    f32 endZ;
    f32 *points;
} Arg_00102A50;

/* Shakes an effect between its two points. */
void ShFx_Vib2P(void *effect) {
    Arg_00102A50 *arg = effect;
    extern s32 func_001A22C0(f32);
    f32 steps[3];
    f32 temp_f4;
    f32 temp_f12;
    f32 *temp_s0;
    f32 *temp_v0;
    s32 i;
    s32 temp_s2;
    s32 temp_s6;
    s32 temp_s6_2;
    s32 temp_s6_3;

    steps[0] = (arg->endX - arg->startX) / (f32) arg->count;
    steps[1] = (arg->endY - arg->startY) / (f32) arg->count;
    steps[2] = (arg->endZ - arg->startZ) / (f32) arg->count;
    temp_f4 = arg->amplitude * RhGeom_GetVectorScalor(steps);
    temp_s0 = arg->points;
    i = 1;
    *(Vec3_00102A50 *) temp_s0 = *(Vec3_00102A50 *) &arg->startX;
    temp_f12 = 200.0f * temp_f4;
    temp_v0 = temp_s0 + (arg->count * 3);
    temp_s0 += 3;
    *(Vec3_00102A50 *) temp_v0 = *(Vec3_00102A50 *) &arg->endX;
    temp_s2 = func_001A22C0(200.0f * temp_f4) >> 1;
    for (; i < arg->count;) {
        temp_s6 = func_0019A5C8() >> 4;
        temp_s0[0] = arg->startX + (steps[0] * (f32) i) + ((f32) ((temp_s6 % func_001A22C0(temp_f12)) - temp_s2) / 100.0f);
        temp_s6_2 = func_0019A5C8() >> 4;
        temp_s0[1] = arg->startY + (steps[1] * (f32) i) + ((f32) ((temp_s6_2 % func_001A22C0(temp_f12)) - temp_s2) / 100.0f);
        temp_s6_3 = func_0019A5C8() >> 4;
        temp_s0[2] = arg->startZ + (steps[2] * (f32) i++) + ((f32) ((temp_s6_3 % func_001A22C0(temp_f12)) - temp_s2) / 100.0f);
        temp_s0 += 3;
    }
}

typedef struct Vec3_00102CB0 {
    f32 x, y, z;
} Vec3_00102CB0;

typedef struct Curve_00102CB0 {
    s32 count;
    f32 radius;
    f32 angle;
    f32 angleStep;
    Vec3_00102CB0 start;
    Vec3_00102CB0 end;
    Vec3_00102CB0 *points;
} Curve_00102CB0;

/* Spins an effect around the line between its two points. */
void ShFx_Spin2P(void *effect) {
    extern s32 func_001A22C0(f32);
    f32 matrix[16];
    Vec3_00102CB0 delta;
    Vec3_00102CB0 point;
    s32 angles[3];
    Vec3_00102CB0 *p;
    Vec3_00102CB0 *end;
    s32 i;
    f32 step;
    f32 angle;
    f32 horizontalDistance;
    Curve_00102CB0 *curve = effect;

    p = curve->points;
    *p = curve->start;
    end = p + curve->count;
    *end = curve->end;
    p++;
    delta.x = curve->end.x - curve->start.x;
    delta.y = curve->end.y - curve->start.y;
    delta.z = curve->end.z - curve->start.z;
    step = RhGeom_GetVectorScalor(&delta.x) / (f32)curve->count;
    horizontalDistance = func_001A6C60(delta.x * delta.x + delta.z * delta.z);
    angles[0] = (u16)func_001A22C0(65536.0f * (func_001A6C18(horizontalDistance, delta.y) / 6.2831855f));
    angles[1] = (u16)func_001A22C0(65536.0f * (func_001A6C18(delta.x, delta.z) / 6.2831855f));
    angles[2] = 0;
    RhGeom_GetRotXYZMatrix(matrix, angles);
    for (i = 1; i < curve->count; i++) {
        angle = (3.1415927f * (curve->angle + curve->angleStep * (f32)i)) / 180.0f;
        point.x = curve->radius * func_001A6898(angle);
        point.z = curve->radius * func_001A6A88(angle);
        point.y = step * (f32)i;
        RhGeom_MulMatrixVector(p, matrix, &point);
        p->x += curve->start.x;
        p->y += curve->start.y;
        p->z += curve->start.z;
        p++;
    }
}

typedef struct {
    f32 x, y, z;
} Vec3_00102F20;

typedef struct {
    s32 count;
    f32 radius;
    f32 angle;
    f32 angleDelta;
    Vec3_00102F20 start;
    Vec3_00102F20 end;
    Vec3_00102F20 *points;
} Curve_00102F20;

/* Copies a vector and moves on. */
static inline Vec3_00102F20 *append_00102F20(Vec3_00102F20 *dst,
                                           const Vec3_00102F20 *src) {
    *dst = *src;
    return dst + 1;
}

/* Moves an effect between its two points along a half sine. */
void ShFx_Hsin2P(void *effect) {
    Vec3_00102F20 *point;
    s32 i;
    f32 matrix[4][4];
    f32 direction[4];
    f32 offset[4];
    s32 rotation[4];
    Curve_00102F20 *curve = effect;
    f32 lengthStep;
    f32 angleStep;
    f32 radius;
    f32 angle;
    f32 length;

    point = curve->points;
    point = append_00102F20(point, &curve->start);
    direction[0] = curve->end.x - curve->start.x;
    direction[1] = curve->end.y - curve->start.y;
    direction[2] = curve->end.z - curve->start.z;
    length = RhGeom_GetVectorScalor(direction);
    angleStep = 180.0f / (f32)curve->count;
    lengthStep = length / (f32)curve->count;
    rotation[0] = (u16)func_001A22C0(65536.0f *
        (func_001A6C18(func_001A6C60(direction[0] * direction[0] +
                                  direction[2] * direction[2]), direction[1]) / 6.2831855f));
    rotation[1] = (u16)func_001A22C0(65536.0f *
        (func_001A6C18(direction[0], direction[2]) / 6.2831855f));
    rotation[2] = 0;
    RhGeom_GetRotXYZMatrix(matrix, rotation);
    for (i = 1; i < curve->count + 1; i++) {
        radius = curve->radius * func_001A6A88((3.1415927f * (angleStep * (f32)i)) / 180.0f);
        angle = (3.1415927f * (curve->angle + (f32)i * curve->angleDelta)) / 180.0f;
        offset[0] = radius * func_001A6898(angle);
        offset[2] = radius * func_001A6A88(angle);
        offset[1] = lengthStep * (f32)i;
        RhGeom_MulMatrixVector(point, matrix, offset);
        point->x += curve->start.x;
        point->y += curve->start.y;
        point->z += curve->start.z;
        point++;
    }
}

/* Fades the battle black-out in and out around an effect's two key frames `frames` at frame `frame`. */
void ShFx_BlackBG(u16 *frames, s32 frame) {
    s32 d;
    s32 e;

    d = ((frame - frames[0]) + 1) & 0xFFFF;
    if (d != 0) {
        e = d & 0xFFFF;
        if (e < 6) {
            SzEffect_SetBlackOutForBattle((0x80 - (e * 0x10)) & 0xFF);
        }
    }
    d = ((frame - frames[1]) + 1) & 0xFFFF;
    if (d != 0) {
        e = d & 0xFFFF;
        if (e < 6) {
            SzEffect_SetBlackOutForBattle(((e * 0x10) + 0x30) & 0xFF);
        }
    }
}

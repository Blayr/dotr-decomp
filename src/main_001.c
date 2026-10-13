#include "common.h"

void func_001031C0(u16 *arg0, s32 arg1) {
    s32 d;
    s32 e;

    d = ((arg1 - arg0[0]) + 1) & 0xFFFF;
    if (d != 0) {
        e = d & 0xFFFF;
        if (e < 6) {
            func_001F6D00((0x80 - (e * 0x10)) & 0xFF);
        }
    }
    d = ((arg1 - arg0[1]) + 1) & 0xFFFF;
    if (d != 0) {
        e = d & 0xFFFF;
        if (e < 6) {
            func_001F6D00(((e * 0x10) + 0x30) & 0xFF);
        }
    }
}

s32 func_00103260(s32 *arg0) {
    extern s32 func_00202BF0();

    *arg0 = func_00202BF0(4);
    return 0;
}

s32 func_00103290(s32 *arg0) {
    extern s32 func_00202BF0();

    *arg0 = func_00202BF0(5);
    return 0;
}

s32 func_001032C0(u8 *arg0, u8 arg1, u8 arg2) {
    u8 temp_a3;

    temp_a3 = *arg0;
    if (temp_a3 <= (arg1 - arg2)) {
        *arg0 = temp_a3 + arg2;
        return 1;
    }
    *arg0 = arg1;
    return 0;
}

s32 func_00103300(s16 *arg0, s32 arg1, s32 arg2) {
    s16 temp_a3;
    s32 result;

    temp_a3 = *arg0;
    if (temp_a3 <= ((s16) arg1 - (s16) arg2)) {
        *arg0 = temp_a3 + arg2;
        result = 1;
    } else {
        *arg0 = (s16) arg1;
        result = 0;
    }
    return result;
}

s32 func_00103350(s32 *arg0, s32 arg1, s32 arg2) {
    s32 temp_v1;
    s32 result;

    temp_v1 = *arg0;
    if (temp_v1 <= (arg1 - arg2)) {
        *arg0 = temp_v1 + arg2;
        result = 1;
    } else {
        *arg0 = arg1;
        result = 0;
    }
    return result;
}

s32 func_00103390(f32 *arg0, f32 fparg0, f32 fparg1) {
    f32 temp_f1;

    temp_f1 = *arg0;
    if (temp_f1 <= (fparg0 - fparg1)) {
        *arg0 = temp_f1 + fparg1;
        return 1;
    }
    *arg0 = fparg0;
    return 0;
}

s32 func_001033D0(f32 *values, f32 target, f32 step) {
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

s32 func_00103470(u8 *arg0, u8 arg1, s32 arg2) {
    u8 temp_a3;

    temp_a3 = *arg0;
    if ((s32) temp_a3 >= ((arg1 & 0xFF) + (arg2 & 0xFF))) {
        *arg0 = temp_a3 - arg2;
        return 1;
    }
    *arg0 = arg1;
    return 0;
}

s32 func_001034B0(s16 *arg0, s16 arg1, s16 arg2) {
    s16 temp_a3;

    temp_a3 = *arg0;
    if (temp_a3 >= arg1 + arg2) {
        *arg0 = temp_a3 - arg2;
        return 1;
    }
    *arg0 = (s16) arg1;
    return 0;
}

s32 func_00103500(s32 *arg0, s32 arg1, s32 arg2) {
    s32 temp_v1;

    temp_v1 = *arg0;
    if (temp_v1 >= (arg1 + arg2)) {
        *arg0 = temp_v1 - arg2;
        return 1;
    }
    *arg0 = arg1;
    return 0;
}

s32 func_00103540(f32 *arg0, f32 fparg0, f32 fparg1) {
    f32 temp_f1;

    temp_f1 = *arg0;
    if (!(temp_f1 < (fparg0 + fparg1))) {
        *arg0 = temp_f1 - fparg1;
        return 1;
    }
    *arg0 = fparg0;
    return 0;
}

s32 func_00103580(void *arg0, f32 fparg0, f32 fparg1) {
    f32 *values = (f32 *)arg0;
    f32 threshold = fparg0 + fparg1;
    s32 flags = 0;

    if (!(values[0] < threshold)) {
        flags |= 1;
        values[0] -= fparg1;
    } else {
        values[0] = fparg0;
        flags &= ~1;
    }
    if (!(values[1] < threshold)) {
        flags |= 2;
        values[1] -= fparg1;
    } else {
        values[1] = fparg0;
        flags &= ~2;
    }
    if (!(values[2] < threshold)) {
        flags |= 4;
        values[2] -= fparg1;
    } else {
        values[2] = fparg0;
        flags &= ~4;
    }
    return flags;
}

void func_00103620(void *arg0, void *arg1) {
    ((f32 *)arg0)[0] += ((f32 *)arg1)[0];
    ((f32 *)arg0)[1] += ((f32 *)arg1)[1];
    ((f32 *)arg0)[2] += ((f32 *)arg1)[2];
}

void func_00103660(void *arg0, void *arg1) {
    f32 *dst = arg0;
    f32 *src = arg1;

    dst[0] -= src[0];
    dst[1] -= src[1];
    dst[2] -= src[2];
}

void func_001036A0(void *arg0, void *arg1) {
    f32 *dst = arg0;
    const f32 *src = arg1;

    dst[0] *= src[0];
    dst[1] *= src[1];
    dst[2] *= src[2];
}

void func_001036E0(f32 *arg0, f32 *arg1, f32 *arg2) {
    f32 delta[3];

    delta[0] = arg1[0];
    delta[1] = arg1[1];
    delta[2] = arg1[2];
    delta[0] -= arg0[0];
    delta[1] -= arg0[1];
    delta[2] -= arg0[2];
    delta[0] /= 2.0f;
    delta[1] /= 2.0f;
    delta[2] /= 2.0f;
    arg2[0] = arg0[0];
    arg2[1] = arg0[1];
    arg2[2] = arg0[2];
    arg2[0] += delta[0];
    arg2[1] += delta[1];
    arg2[2] += delta[2];
}

void func_00103760(void *arg0) {
    f32 *vector = arg0;

    func_001A22C0(90.0f + (360.0f / (6.2831855f / func_001A6C18(vector[1], vector[0]))));
}

s32 func_001037C0(u8 *arg0, s32 arg1, s32 arg2) {
    extern s32 func_001A22C0(f32);
    u16 point1[4];
    u16 point2[4];
    s32 depth;

    func_00205440(arg1, arg0 + 0x30, point1, &depth);
    func_00205440(arg2, arg0 + 0x30, point2, &depth);
    return func_001A22C0(65536.0f *
        (func_001A6C18((f32)((s32)(point1[0] - point2[0]) >> 4),
                      (f32)((s32)(point1[1] - point2[1]) >> 4)) / 6.2831855f)) % 65536;
}

void func_00103890(void *arg0) {
    f32 *values = arg0;

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

void func_0020C940(void *, void *, void *, void *);

typedef struct {
    f32 values[4][4];
} Matrix_001038D0;

typedef struct {
    f32 eye[4];
    f32 target[4];
    f32 up[4];
    Matrix_001038D0 matrix;
} Camera_001038D0;

void func_001038D0(void *arg0) {
    Camera_001038D0 *camera = arg0;
    Matrix_001038D0 matrix;

    func_0020EB40(&camera->matrix);
    func_0020C940(&matrix, camera->eye, camera->target, camera->up);
    func_0020BC00((s32)&camera->matrix, &matrix);
}

void func_0020C940(void *, void *, void *, void *);

typedef struct Transform_00103920 {
    f32 field0[4];
    f32 field10[4];
    f32 field20[4];
    f32 field30[16];
} Transform_00103920;

s32 func_00103920(void *arg0, f32 fparg0, f32 fparg1) {
    Transform_00103920 *transform = arg0;
    f32 vector[4];
    f32 matrix[16];

    func_00205CB0(vector, fparg0, fparg1);
    func_001039A0(arg0);
    transform->field20[0] = vector[0];
    transform->field20[1] = vector[1];
    transform->field20[2] = vector[2];
    func_0020EB40(transform->field30);
    func_0020C940(matrix, transform->field0, transform->field10, transform->field20);
    func_0020BC00((s32)transform->field30, matrix);
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

void func_0020C940(void *, void *, void *, void *);

s32 func_001039A0(void *arg0) {
    s32 vector[4];
    f32 matrix[4][4];
    Object_001039A0 *object = arg0;

    func_00205C40((s32) &vector);
    object->values10.y = vector[1] % 0x10000;
    object->values10.x = vector[0];
    object->values10.z = vector[2];
    func_0020EB40(object->matrix);
    func_0020C940(matrix, object, &object->values10, &object->values20);
    func_0020BC00((s32)object->matrix, matrix);
    return vector[1];
}

s32 func_00103A30(f32 *arg0, s32 *arg1) {
    arg1[1] = (s32)(65536.0f * (func_001A6C18(arg0[0], arg0[2]) / 6.2831855f)) % 65536;
    arg1[0] = (s32)(65536.0f * (func_001A6C18(arg0[2], arg0[1]) / 6.2831855f)) % 65536;
    arg1[2] = (s32)(65536.0f * (func_001A6C18(arg0[1], arg0[0]) / 6.2831855f)) % 65536;
    arg1[3] = 0;
    return 0;
}

s32 func_00103B50(f32 *arg0, s32 *arg1) {
    arg1[1] = (s32)(65536.0f * (func_001A6C18(arg0[0], arg0[2]) / 6.2831855f)) % 65536;
    arg1[0] = (s32)(65536.0f * (func_001A6C18(func_001A6C60(arg0[0] * arg0[0] + arg0[2] * arg0[2]), arg0[1]) / 6.2831855f)) % 65536;
    arg1[3] = 0;
    arg1[2] = 0;
    return 0;
}

s32 func_00103C40(Vec4f *arg0, void *arg1) {
    Vec4f sp20;
    Vec4f sp30;
    Vec4f sp40;
    void func_0020C750();

    sp20 = *arg0;
    func_0020D070(&sp20.x);
    sp30.z = 0.0f;
    sp30.x = 0.0f;
    sp30.y = 1.0f;
    func_0020D070(&sp30.x);
    func_0020D140(&sp40.x, &sp30.x, &sp20.x);
    func_0020C750(arg1, &sp40, func_001A22C0(65536.0f * (func_001A6C00(func_0020D0E0(&sp40.x)) / 6.2831855f)));
    return 0;
}

s32 func_00103D00(s32 arg0, s32 arg1) {
    s32 result;

    if (arg1 < arg0) {
        if ((arg0 - arg1) % 0x10000 <= 0x8000) {
            result = arg0 - arg1;
        } else {
            result = -((0x10000 - arg0) + arg1);
        }
    } else {
        if (arg0 < arg1) {
            if ((arg1 - arg0) % 0x10000 <= 0x8000) {
                result = -(arg1 - arg0);
            } else {
                result = (0x10000 - arg1) + arg0;
            }
        } else {
            result = 0;
        }
    }
    return result;
}

s32 func_00103DB0(f32 *arg0, f32 *arg1, s32 *arg2) {
    extern s32 func_001A22C0(f32);
    f32 x;
    f32 y;
    f32 z;

    x = arg0[0] - arg1[0];
    y = arg0[1] - arg1[1];
    z = arg0[2] - arg1[2];
    arg2[1] = func_001A22C0(65536.0f * (func_001A6C18(x, z) / 6.2831855f)) % 65536;
    arg2[0] = func_001A22C0(65536.0f * (func_001A6C18(func_001A6C60(x * x + z * z), y) / 6.2831855f)) % 65536;
    arg2[3] = 0;
    arg2[2] = 0;
    return 0;
}


static inline s32 angle_00103EC0(f32 a, f32 b) {
    extern s32 func_001A22C0(f32);
    return func_001A22C0(65536.0f * (func_001A6C18(a, b) / 6.2831855f)) % 65536;
}

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

s32 func_00103EC0(f32 *position, f32 *target, f32 *velocity, s32 limit) {
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

    func_0020C630(matrix, rotation);
    func_0020CDD0(movement, matrix, velocity);
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

s32 func_001043F0(void *arg0, f32 fparg0) {
    f32 matrix[4][4];
    Vec4_001043F0 vector;
    s32 angles[3];

    vector = D_0028C220;
    vector.y = fparg0;
    angles[0] = func_0019A5C8() % 0x10000;
    angles[1] = func_0019A5C8() % 0x10000;
    angles[2] = 0;
    func_0020C630(matrix, angles);
    func_0020CDD0(arg0, matrix, &vector);
    return 0;
}

void func_00104490(f32 *arg0, f32 *arg1, s32 arg2) {
    f32 x;
    f32 y;
    f32 z;

    if (arg2 != 0) {
        x = arg1[0];
        y = arg1[1];
        z = arg1[2];
        x -= arg0[0];
        y -= arg0[1];
        z -= arg0[2];
        x /= (f32)arg2;
        arg0[0] += x;
        y /= (f32)arg2;
        arg0[1] += y;
        z /= (f32)arg2;
        arg0[2] += z;
    } else {
        arg0[0] = arg1[0];
        arg0[1] = arg1[1];
        arg0[2] = arg1[2];
    }
}

s32 func_00104520(s32 arg0, s32 arg1) {
    return !(arg0 & (1 << arg1)) ? 0 : 1;
}

INCLUDE_ASM("asm/nonmatchings/main_001", func_00104540);

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

static inline s32 flag_00104DC0(Anim_00104DC0 *anim, s32 bit) {
    return (anim->flags & bit) ? 1 : 0;
}

void func_00104DC0(void *arg0, void *arg1) {
    Sprite_00104DC0 *sprite = arg0;
    Anim_00104DC0 *anim = arg1;

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

INCLUDE_ASM("asm/nonmatchings/main_001", func_00105260);

INCLUDE_ASM("asm/nonmatchings/main_001", func_00105830);

s32 func_00105C40(void *arg0) {
    Vec4f *v = arg0;
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

typedef struct Rect_00105D00 {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
    s32 padding[2];
} Rect_00105D00;

void func_00105D00(void *dst, s16 kind, s16 index) {
    Rect_00105D00 rect;

    if (kind == 0) {
        rect.x = 0x40;
        rect.y = 0;
        rect.w = 0x3F;
        rect.h = 0x3F;
        *(Rect_00105D00 *)dst = rect;
        return;
    } else if (kind == 1) {
        rect.x = 0xF0;
        rect.y = index * 0x10;
        rect.w = 0x10;
        rect.h = 0x10;
        *(Rect_00105D00 *)dst = rect;
        return;
    } else if (kind == 2) {
        rect.w = 0x1F;
        rect.h = 0x40;
        if (index == 0) {
            rect.x = 0x8F;
            rect.y = 0;
            *(Rect_00105D00 *)dst = rect;
            return;
        } else {
            rect.x = 0x8F;
            rect.y = 0x3F;
            *(Rect_00105D00 *)dst = rect;
            return;
        }
    } else if (kind == 3) {
        rect.x = 0x80;
        rect.y = 0x80;
        rect.w = 0x7F;
        rect.h = 0x3F;
        *(Rect_00105D00 *)dst = rect;
        return;
    } else if (kind == 4) {
        rect.w = 0x3F;
        rect.h = 0x20;
        if (index == 0) {
            rect.x = 0x80;
            rect.y = 0x80;
            *(Rect_00105D00 *)dst = rect;
            return;
        } else if (index == 1) {
            rect.x = 0x80;
            rect.y = 0xA0;
            *(Rect_00105D00 *)dst = rect;
            return;
        } else if (index == 2) {
            rect.x = 0xC0;
            rect.y = 0x80;
            *(Rect_00105D00 *)dst = rect;
            return;
        } else if (index == 3) {
            rect.x = 0xC0;
            rect.y = 0xA0;
            *(Rect_00105D00 *)dst = rect;
            return;
        }
    } else if (kind == 5) {
        rect.x = 0x8F;
        rect.y = 0;
        rect.w = 0x1F;
        rect.h = 0x7F;
        *(Rect_00105D00 *)dst = rect;
        return;
    } else if (kind == 6) {
        rect.x = 0xB0;
        rect.y = 0;
        rect.w = 0x3B;
        rect.h = 0x1F;
        *(Rect_00105D00 *)dst = rect;
        return;
    }
    rect.x = 0;
    rect.y = 0;
    rect.w = 0x60;
    rect.h = 0x60;
    *(Rect_00105D00 *)dst = rect;
}

typedef struct Rect_00106080 {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
    s32 unk8;
    s32 unkC;
} Rect_00106080;

void func_00106080(void *arg0, s16 arg1, s16 arg2) {
    Rect_00106080 rect;

    if (arg1 == 0x8C) {
        if (arg2 == 0) {
            rect.x = 1;
            rect.y = 1;
            rect.w = 0x1E;
            rect.h = 0x7E;
        }
    } else if (arg1 == 0x8D) {
        if (arg2 == 0) {
            rect.x = 0;
            rect.y = 0x80;
        } else if (arg2 == 1) {
            rect.x = 0x20;
            rect.y = 0x80;
        } else if (arg2 == 2) {
            rect.x = 0x40;
            rect.y = 0x80;
        }
        rect.w = 0x1F;
        rect.h = 0x7F;
    } else if (arg1 == 0x8E) {
        if (arg2 < 4) {
            rect.x = 0x21;
            rect.y = (arg2 << 5) + 1;
        } else {
            rect.x = 0x41;
            rect.y = ((arg2 - 4) << 5) + 1;
        }
        rect.w = 0x1E;
        rect.h = 0x1E;
    } else if (arg1 == 0x8F) {
        rect.x = 0x60;
        rect.y = 0xF0;
        rect.w = 0x9F;
        rect.h = 0xF;
    } else if (arg1 == 0x96) {
        rect.x = (arg2 * 0x2C) + 0xA;
        rect.y = 0;
        rect.w = 0x2B;
        rect.h = 0x7F;
    } else if (arg1 == 0x97) {
        rect.x = 0x8F;
        rect.y = 0;
        rect.w = 0x1F;
        rect.h = 0x7F;
    } else if (arg1 == 0x98) {
        rect.x = 0xB0;
        rect.y = 0;
        rect.w = 0x3B;
        rect.h = 0x1F;
    } else if (arg1 == 0x99) {
        rect.x = 0xF1;
        rect.y = arg2 * 0x10;
        rect.w = 0xE;
        rect.h = 0xF;
    } else if (arg1 == 0x9A) {
        rect.x = (arg2 << 5) + 0xB1;
        rect.y = 0x21;
        rect.w = 0x1E;
        rect.h = 0x1E;
    } else if (arg1 == 0x9B) {
        if (arg2 < 2) {
            rect.x = (arg2 << 5) + 0xB1;
            rect.y = 0x41;
        } else {
            rect.x = ((arg2 - 2) << 5) + 0xB1;
            rect.y = 0x61;
        }
        rect.w = 0x1E;
        rect.h = 0x1E;
    } else if (arg1 == 0x9C) {
        rect.x = 0x80;
        rect.y = 0x81;
        rect.w = 0x7F;
        rect.h = 0x3F;
    } else if (arg1 == 0x9D) {
        if (arg2 < 4) {
            rect.x = (arg2 << 5) + 0x80;
            rect.y = 0xC1;
        } else {
            rect.x = ((arg2 - 4) << 5) + 0x80;
            rect.y = 0xE1;
        }
        rect.w = 0x1F;
        rect.h = 0x1F;
    } else if (arg1 == 0x9E) {
        rect.x = 1;
        rect.y = (arg2 * 0xA) + 0xD1;
        rect.w = 8;
        rect.h = 8;
    } else if (arg1 == 0x9F) {
        if (arg2 < 2) {
            rect.x = (arg2 * 0x3B) + 0xB;
            rect.y = 0x81;
        } else {
            rect.x = ((arg2 - 2) * 0x3B) + 0xB;
            rect.y = 0xC1;
        }
        rect.w = 0x38;
        rect.h = 0x3F;
    } else if (arg1 == 0x64) {
        rect.w = 0x12;
        rect.h = 0x1F;
        if (arg2 == 0) {
            rect.x = 1;
            rect.y = 1;
        } else if (arg2 == 1) {
            rect.x = 0x15;
            rect.y = 1;
        } else if (arg2 == 2) {
            rect.x = 0x29;
            rect.y = 1;
        } else if (arg2 == 3) {
            rect.x = 0x3D;
            rect.y = 1;
        } else if (arg2 == 4) {
            rect.x = 1;
            rect.y = 0x21;
        } else if (arg2 == 5) {
            rect.x = 0x15;
            rect.y = 0x21;
        } else if (arg2 == 6) {
            rect.x = 0x29;
            rect.y = 0x21;
        } else if (arg2 == 7) {
            rect.x = 0x3D;
            rect.y = 0x21;
        }
    } else if (arg1 == 0x65) {
        rect.x = 0x50;
        rect.y = 0;
        rect.w = 0x2F;
        rect.h = 0x3F;
    } else if (arg1 == 0x6E) {
        rect.x = arg2 << 6;
        rect.y = 0;
        rect.w = 0x3F;
        rect.h = 0x3F;
    } else if (arg1 == 0x3C) {
        rect.x = arg2 << 6;
        rect.y = 0;
        rect.w = 0x3F;
        rect.h = 0x3F;
    } else if (arg1 == 0x3D) {
        rect.w = 0x1F;
        rect.h = 0x1F;
        if (arg2 == 0) {
            rect.x = 0x21;
            rect.y = 0;
        } else if (arg2 == 1) {
            rect.x = 0x21;
            rect.y = 0x21;
        } else if (arg2 == 2) {
            rect.x = 0x41;
            rect.y = 0;
        } else if (arg2 == 3) {
            rect.x = 0x41;
            rect.y = 0x21;
        }
    } else if (arg1 == 0x5A) {
        rect.x = arg2 << 6;
        rect.y = 1;
        rect.w = 0x3F;
        rect.h = 0x3F;
    } else if (arg1 == 0x14) {
        if (arg2 < 4) {
            rect.x = arg2 << 5;
            rect.y = 1;
        } else {
            rect.x = (arg2 - 4) << 5;
            rect.y = 0x21;
        }
        rect.w = 0x1F;
        rect.h = 0x1F;
    } else if (arg1 == 0x82) {
        rect.w = 0x12;
        rect.h = 0x1F;
        if (arg2 == 0) {
            rect.x = 1;
            rect.y = 0x41;
        } else if (arg2 == 1) {
            rect.x = 0x15;
            rect.y = 0x41;
        } else if (arg2 == 2) {
            rect.x = 0x29;
            rect.y = 0x41;
        } else if (arg2 == 3) {
            rect.x = 0x3D;
            rect.y = 0x41;
        } else if (arg2 == 4) {
            rect.x = 1;
            rect.y = 0x61;
        } else if (arg2 == 5) {
            rect.x = 0x15;
            rect.y = 0x61;
        } else if (arg2 == 6) {
            rect.x = 0x29;
            rect.y = 0x61;
        } else if (arg2 == 7) {
            rect.x = 0x3D;
            rect.y = 0x61;
        }
    } else if (arg1 == 0x83) {
        if (arg2 < 2) {
            rect.x = (arg2 * 0x18) + 0x51;
            rect.y = 0x51;
        } else {
            rect.x = ((arg2 - 2) * 0x18) + 0x51;
            rect.y = 0x51;
        }
        rect.w = 0x17;
        rect.h = 0x16;
    } else if (arg1 == 0x50) {
        rect.x = 1;
        rect.y = (arg2 * 0xA) + 1;
        rect.w = 8;
        rect.h = 8;
    } else if (arg1 == 0xA) {
        if (arg2 < 5) {
            rect.x = (arg2 * 0x18) + 1;
            rect.y = 1;
        } else {
            rect.x = ((arg2 - 5) * 0x18) + 1;
            rect.y = 0x21;
        }
        rect.w = 0x17;
        rect.h = 0x1F;
    } else if (arg1 == 0x1E) {
        if (arg2 < 4) {
            rect.x = arg2 * 0x10;
            rect.y = 0;
        } else if (arg2 < 8) {
            rect.x = (arg2 - 4) * 0x10;
            rect.y = 0x10;
        } else if (arg2 < 0xC) {
            rect.x = (arg2 - 8) * 0x10;
            rect.y = 0x20;
        } else if (arg2 < 0x10) {
            rect.x = (arg2 - 0xC) * 0x10;
            rect.y = 0x30;
        }
        rect.w = 0x10;
        rect.h = 0x10;
    }

    *(Rect_00106080 *)arg0 = rect;
}

s32 func_00106A00(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 i;
    s32 offset;
    u8 *slot;

    for (i = 0; i < arg2; i++) {
        if ((arg3 == 0) && (*(s16 *)((u8 *)arg0 + i * 0xC0 + 0xD04) == 0)) {
            offset = i * 0xC0;
            slot = (u8 *)arg0 + offset + 0xC60;
            func_00195108((s32)slot, 0xC0);
            *(s16 *)(offset + (s32)arg0 + 0xD04) = i + 1;
            return (s32)slot;
        }
    }
    return 0;
}

void func_00106AB0(s16 *arg0, f32 *arg1, s32 arg2) {
    if (arg2 == 0) {
        arg0[0] = func_001A22C0(arg1[0]);
        arg0[1] = func_001A22C0(arg1[1]);
        arg0[2] = func_001A22C0(arg1[2]);
        arg0[3] = func_001A22C0(arg1[3]);
    } else {
        arg0[4] = func_001A22C0(arg1[0]);
        arg0[5] = func_001A22C0(arg1[1]);
        arg0[6] = func_001A22C0(arg1[2]);
        arg0[7] = func_001A22C0(arg1[3]);
    }
}

void func_00106B50(void *arg0, void *arg1) {
    f32 *dst = arg0;
    f32 *src = arg1;

    dst[0] += src[0];
    dst[1] += src[1];
    dst[2] += src[2];
}

s32 func_00106B90(void *arg0, s32 arg1, s32 arg2) {
    ((u8 *)arg0)[0xAF] = (u8)(((u8 *)arg0)[0xAF] - arg1);
    ((u8 *)arg0)[0xB3] = (u8)(((u8 *)arg0)[0xB3] - arg1);
    return (((u8 *)arg0)[0xAF] < (arg2 & 0xFF)) ? 1 : 0;
}

s32 func_00106BC0(void *arg0, s32 arg1, s32 arg2) {
    *((u8 *)arg0 + 0xAF) = (u8)(*((u8 *)arg0 + 0xAF) + arg1);
    *((u8 *)arg0 + 0xB3) = (u8)(*((u8 *)arg0 + 0xB3) + arg1);
    return *((u8 *)arg0 + 0xAF) > (arg2 & 0xFF) ? 1 : 0;
}

s32 func_00106BF0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg3 == 0) {
        arg0[0] += arg1;
        arg0[1] += arg1;
        arg0[2] += arg1;
    } else {
        arg0[0] -= arg1;
        arg0[1] -= arg1;
        arg0[2] -= arg1;
    }
    return 0;
}

typedef struct Data_00106C50 {
    u8 padding[3];
    u8 value;
} Data_00106C50;

s32 func_00106C50(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    Data_00106C50 *data = arg0;
    u8 temp_v1;
    u8 temp_v1_2;

    if (arg3 == 0) {
        temp_v1 = data->value;
        if ((s32) temp_v1 < (arg2 & 0xFF)) {
            data->value = temp_v1 + arg1;
        } else {
            return 1;
        }
    } else {
        temp_v1_2 = data->value;
        if ((arg2 & 0xFF) < (s32) temp_v1_2) {
            data->value = temp_v1_2 - arg1;
        } else {
            return 1;
        }
    }
    return 0;
}

s32 func_00106CC0(s32 arg0, s32 arg1) {
    func_00195108(arg0, (s16)arg1);
    return arg0;
}

s32 func_00106CF0(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    ((f32 *)arg0)[0] = (f32)arg2 * func_00108030(arg3, arg1, 1);
    ((f32 *)arg0)[2] = (f32)arg2 * func_00108030(arg3, arg1, 0);
    return 0;
}

s32 func_00106D80(s32 arg0, s16 *arg1) {
    *arg1 += arg0;
    if (*arg1 >= 360 || *arg1 < -359) {
        *arg1 %= 360;
    }
    return 0;
}

void func_00106DD0(void *arg0, f32 fparg0, f32 fparg1, f32 fparg2) {
    ((f32 *)arg0)[0] = fparg0;
    ((f32 *)arg0)[1] = fparg1;
    ((f32 *)arg0)[2] = fparg2;
}

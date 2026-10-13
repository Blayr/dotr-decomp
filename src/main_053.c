#include "common.h"

f32 func_001A6C30(f32, f32);
void func_0020C630(void *, void *);
extern f32 D_00293040[4][4];

typedef struct Vec4_001FB500 {
    f32 x, y, z, w;
} Vec4_001FB500;

typedef struct Camera_001FB500 {
    Vec4_001FB500 param;
    f32 direction[4];
    f32 origin[4];
    f32 target[4];
} Camera_001FB500;

static inline s32 aim_001FB500(s32 index) {
    Camera_001FB500 *entry;

    if ((index < 0) || (index > 0)) {
        return 0;
    }
    entry = (Camera_001FB500 *)D_0031BEB0[index];
    if (entry == 0) {
        return 0;
    }
    entry->direction[0] = entry->target[0] - entry->origin[0];
    entry->direction[1] = entry->target[1] - entry->origin[1];
    entry->direction[2] = entry->target[2] - entry->origin[2];
    entry->direction[3] = 0.0f;
    func_0020D070(entry->direction);
    return 1;
}

s32 func_001FB500(s32 index, f32 *src) {
    Camera_001FB500 *entry;
    f32 matrix[4][4];
    f32 angles[4];

    if ((index < 0) || (index > 0)) {
        return 0;
    }
    entry = (Camera_001FB500 *)D_0031BEB0[index];
    if (entry == 0) {
        return 0;
    }
    if (src == NULL) {
        return 0;
    }
    entry->param = *(Vec4_001FB500 *)src;
    entry->param.y = func_001A6C30(6.2831855f + entry->param.y, 6.2831855f);
    if (func_001FAFB0(index, (s32)angles) != 0) {
        func_0020C630(matrix, angles);
    }
    func_0020CDD0(entry->direction, matrix, D_00293040);
    entry->target[0] = entry->origin[0] - entry->direction[0] * entry->param.x;
    entry->target[1] = entry->origin[1] - entry->direction[1] * entry->param.x;
    entry->target[2] = entry->origin[2] - entry->direction[2] * entry->param.x;
    entry->target[3] = 0.0f;
    aim_001FB500(index);
    return 1;
}

typedef struct Camera_001FB6A0 {
    f32 radius;
    f32 yaw;
    f32 pitch;
    f32 pad0C;
    f32 direction[4];
    f32 eye[4];
    f32 target[4];
    u8 pad40[0x870];
    s32 mode;
} Camera_001FB6A0;

f32 func_001A6C30(f32, f32);
f32 func_0020B620(f32);

s32 func_001FB6A0(s32 arg0, s32 arg1, s32 arg2, f32 fparg0, f32 fparg1, f32 fparg2) {
    Camera_001FB6A0 *camera;
    f32 *source;
    f32 *destination;
    s32 *slot;
    f32 horizontal;
    f32 vertical;
    f32 depth;
    f32 minimum;
    f32 radius;
    f32 pitch;
    f32 scale;
    s32 mode;

    if ((arg0 < 0) || (arg0 > 0)) {
        return 0;
    }
    slot = &D_0031BEB0[arg0];
    camera = (Camera_001FB6A0 *)*slot;
    if (camera == 0) {
        return 0;
    }
    if (arg2 > 0) {
        source = camera->target;
        destination = camera->eye;
    } else {
        source = camera->eye;
        destination = camera->target;
    }
    mode = camera->mode;
    switch (mode) {
    case 0:
    case 2:
        minimum = 50.0f;
        if (mode == 2) {
            minimum = 10.0f;
        }
        if (arg1 == 0) {
            radius = camera->radius + fparg2;
            if (radius < minimum) {
                func_001FB6A0(arg0, 1, -arg2, 0.0f, 0.0f, minimum - radius);
            }
        }
        pitch = camera->pitch;
        if (!((pitch + fparg1) <= 1.5706217f)) {
            fparg1 = 1.5706217f - pitch;
        }
        if ((pitch + fparg1) < -1.5706217f) {
            fparg1 = -1.5706217f - pitch;
        }
        break;
    }
    camera->radius += fparg2;
    camera->yaw = func_001A6C30(6.2831855f + (camera->yaw + fparg0), 6.2831855f);
    camera->pitch = func_001A6C30(camera->pitch + fparg1, 6.2831855f);
    horizontal = camera->radius * func_0020B620(camera->pitch);
    vertical = camera->radius * func_0020B730(camera->pitch);
    depth = horizontal * func_0020B730(camera->yaw);
    horizontal *= func_0020B620(camera->yaw);
    scale = (f32)arg2;
    destination[0] = source[0] + horizontal * scale;
    destination[1] = source[1] + vertical * scale;
    destination[2] = source[2] + depth * scale;
    if (arg0 >= 0) {
        if (arg0 <= 0) {
            camera = (Camera_001FB6A0 *)*slot;
            if (camera != 0) {
                camera->direction[0] = camera->target[0] - camera->eye[0];
                camera->direction[1] = camera->target[1] - camera->eye[1];
                camera->direction[2] = camera->target[2] - camera->eye[2];
                camera->direction[3] = 0.0f;
                func_0020D070(camera->direction);
            }
        }
    }
    return 1;
}

typedef struct Vec4_001FB940 {
    f32 x, y, z, w;
} Vec4_001FB940;

typedef struct Camera_001FB940 {
    Vec4_001FB940 polar;
    Vec4_001FB940 direction;
    Vec4_001FB940 eye;
    Vec4_001FB940 target;
    s32 angle;
    f32 distance;
    f32 pad48[2];
    f32 minimum;
} Camera_001FB940;

typedef struct Motion_001FB940 {
    s32 magic;
    s32 pad04[2];
    u32 frames;
    u16 eyeOffset, eyeCount;
    u16 targetOffset, targetCount;
    u16 angleOffset, angleCount;
    u16 fovOffset, fovCount;
} Motion_001FB940;

void func_001FBE50(void *, void *, u16, f32);
f32 func_0020B620(f32);
f32 func_001A6C30(f32, f32);
void func_0020C630(void *, void *);

static inline void direction_001FB940(s32 index) {
    Camera_001FB940 *camera;
    if (index >= 0 && index <= 0) {
        camera = (Camera_001FB940 *)D_0031BEB0[index];
        if (camera != NULL) {
            camera->direction.x = camera->target.x - camera->eye.x;
            camera->direction.y = camera->target.y - camera->eye.y;
            camera->direction.z = camera->target.z - camera->eye.z;
            camera->direction.w = 0.0f;
            func_0020D070(&camera->direction.x);
        }
    }
}

static inline void polar_001FB940(s32 index) {
    Camera_001FB940 *camera;
    Vec4_001FB940 *eye;
    Vec4_001FB940 *target;
    Vec4_001FB940 polar;
    if (index >= 0) {
        if (index <= 0) {
            camera = (Camera_001FB940 *)D_0031BEB0[index];
            if (camera != NULL) {
                eye = &camera->eye;
                target = &camera->target;
                polar.x = func_001A6C60((eye->x - target->x) * (eye->x - target->x) +
                                      (eye->z - target->z) * (eye->z - target->z));
                polar.y = func_001A6C18(eye->z - target->z, eye->x - target->x);
                polar.y = func_001A6C30(6.2831855f + polar.y, 6.2831855f);
                polar.z = func_001A6C18(eye->y - target->y, polar.x);
                polar.x = func_001A6C60((eye->x - target->x) * (eye->x - target->x) +
                                      (eye->y - target->y) * (eye->y - target->y) +
                                      (eye->z - target->z) * (eye->z - target->z));
                camera->polar = polar;
            }
        }
    }
}

s32 func_001FB940(s32 index, void *motion, s32 duration, s32 frame, s32 parent, s32 mirror) {
    extern s32 func_001A22C0(f32);
    Vec4_001FB940 translation;
    Vec4_001FB940 rotation;
    f32 matrix[4][4];
    Camera_001FB940 *camera;
    void *targetData;
    s32 *slot;
    void *angleData;
    void *fovData;
    f32 time;
    f32 angle;
    f32 fov;
    f32 halfFov;
    f32 sine;

    if ((index < 0) || (index > 0)) {
        return 0;
    }
    if (duration == 0) {
        return 0;
    }
    if (motion == NULL) {
        return 0;
    }
    if (((Motion_001FB940 *)motion)->magic != 0x544F4D43) {
        return 0;
    }
    slot = &D_0031BEB0[index];
    camera = (Camera_001FB940 *)*slot;
    if (camera == NULL) {
        return 0;
    }
    targetData = (u8 *)motion + ((Motion_001FB940 *)motion)->targetOffset * 8 + 0x20;
    angleData = (u8 *)motion + ((Motion_001FB940 *)motion)->angleOffset * 8 + 0x20;
    fovData = (u8 *)motion + ((Motion_001FB940 *)motion)->fovOffset * 8 + 0x20;
    time = ((f32)(((Motion_001FB940 *)motion)->frames - 1) * (f32)frame) / (f32)duration;
    func_001FBE50(&camera->eye, (u8 *)motion + ((Motion_001FB940 *)motion)->eyeOffset * 8 + 0x20, ((Motion_001FB940 *)motion)->eyeCount, time);
    func_001FBE50(&camera->target, targetData, ((Motion_001FB940 *)motion)->targetCount, time);
    angle = func_001FC050(angleData, ((Motion_001FB940 *)motion)->angleCount, time);
    fov = func_001FC050(fovData, ((Motion_001FB940 *)motion)->fovCount, time);
    camera->angle = func_001A22C0((32768.0f * angle) / 180.0f);
    halfFov = ((3.1415927f * fov) / 180.0f) / 2.0f;
    if (halfFov < 0.000001f) {
        halfFov = 0.000001f;
    }
    sine = func_0020B620(halfFov);
    camera->distance = 224.0f * (sine / func_0020B730(halfFov));
    if (camera->distance < camera->minimum) {
        camera->distance = camera->minimum;
    }
    if (mirror != 0) {
        camera->eye.x = -camera->eye.x;
        camera->target.x = -camera->target.x;
        camera->angle = -camera->angle;
    }
    if (parent >= 0) {
        if (func_001F2330(parent, &rotation) != 0) {
            func_0020C630(matrix, &rotation);
            func_0020BAF0((s32)matrix);
            func_0020CDD0(&camera->eye, NULL, &camera->eye);
            func_0020CDD0(&camera->target, NULL, &camera->target);
            func_0020BB50();
        }
        if (func_001F1FD0(parent, &translation) != 0) {
            camera->eye.x += translation.x;
            camera->eye.y += translation.y;
            camera->eye.z += translation.z;
            camera->target.x += translation.x;
            camera->target.y += translation.y;
            camera->target.z += translation.z;
        }
    }
    direction_001FB940(index);
    polar_001FB940(index);
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FBE50);

typedef struct Key_001FC050 {
    u32 time;
    f32 value;
} Key_001FC050;

f32 func_001FC050(u8 *arg0, s32 arg1, f32 fparg0) {
    f32 var_f0;
    f32 var_f0_2;
    f32 var_f0_3;
    f32 var_f0_4;
    f32 var_f3;
    f32 weight;
    f32 result;
    Key_001FC050 *temp_a2;
    u32 temp_a1;
    u32 temp_a3;
    u32 temp_v0;
    u32 temp_v0_2;
    u32 temp_v0_3;
    s32 temp_v1;
    s32 var_a2;
    s32 var_a3;
    s32 var_t0;
    s32 var_v0;
    void *temp_t1;

    var_a3 = 0;
    if (arg1 > 2) {
    var_a2 = 0;
    var_t0 = arg1;
loop_2:
    var_a3 = (s32)(var_a2 + var_t0) >> 1;
    var_v0 = var_a3 * 8;
    if (var_a2 >= var_a3) {
        goto block_15;
    }
    temp_t1 = arg0 + (var_a3 * 8);
    temp_v0 = *(u32 *)((u8 *)temp_t1 + 8);
    var_f0_3 = (f32)temp_v0;
    if (!(fparg0 < var_f0_3)) {
        var_a2 = var_a3;
        goto loop_2;
    }
    temp_v0_2 = *(u32 *)temp_t1;
    var_f0_4 = (f32)temp_v0_2;
    if (fparg0 < var_f0_4) {
        var_t0 = var_a3;
        goto loop_2;
    }
    }
block_15:
    var_v0 = var_a3 * 8;
    temp_a2 = (Key_001FC050 *)(arg0 + var_v0);
    temp_v1 = var_a3 + 1;
    if (temp_v1 >= arg1) {
        return temp_a2->value;
    }
    arg0 += temp_v1 * 8;
    temp_a1 = temp_a2->time;
    temp_a3 = *(u32 *)arg0;
    temp_v0_3 = temp_a3 - temp_a1;
    var_f3 = (f32)temp_v0_3;
    var_f0 = (f32)temp_a3;
    var_f0_2 = (f32)temp_a1;
    weight = (var_f0 - fparg0) / var_f3;
    result = weight * temp_a2->value;
    weight = (fparg0 - var_f0_2) / var_f3;
    return result + weight * *(f32 *)(arg0 + 4);
}

typedef struct Vec4_001FC210 {
    f32 x, y, z, w;
} Vec4_001FC210;

typedef struct Camera_001FC210 {
    Vec4_001FC210 polar;
    Vec4_001FC210 direction;
    Vec4_001FC210 position;
    Vec4_001FC210 target;
} Camera_001FC210;

f32 func_001A6C30(f32, f32);

static inline void direction_001FC210(s32 index) {
    if (index >= 0 && index <= 0) {
        Camera_001FC210 *camera = (Camera_001FC210 *)D_0031BEB0[index];
        if (camera != NULL) {
        camera->direction.x = camera->target.x - camera->position.x;
        camera->direction.y = camera->target.y - camera->position.y;
        camera->direction.z = camera->target.z - camera->position.z;
        camera->direction.w = 0.0f;
        func_0020D070(&camera->direction.x);
        }
    }
}

static inline void polar_001FC210(s32 index) {
    if (index >= 0 && index <= 0) {
        Camera_001FC210 *camera = (Camera_001FC210 *)D_0031BEB0[index];
        if (camera != NULL) {
        Vec4_001FC210 polar;
        Vec4_001FC210 *position = &camera->position;
        Vec4_001FC210 *target = &camera->target;

        polar.x = func_001A6C60(
            (position->x - target->x) * (position->x - target->x) +
            (position->z - target->z) * (position->z - target->z));
        polar.y = func_001A6C18(position->z - target->z, position->x - target->x);
        polar.y = func_001A6C30(6.2831855f + polar.y, 6.2831855f);
        polar.z = func_001A6C18(position->y - target->y, polar.x);
        polar.x = func_001A6C60(
            (position->x - target->x) * (position->x - target->x) +
            (position->y - target->y) * (position->y - target->y) +
            (position->z - target->z) * (position->z - target->z));
        camera->polar = polar;
        }
    }
}

s32 func_001FC210(s32 index, s32 otherIndex, f32 *target, s32 mode, f32 weight) {
    f32 inverse = 1.0f - weight;
    Camera_001FC210 *camera;
    Vec4_001FC210 newTarget;
    Vec4_001FC210 oldPolar;

    if (index < 0 || index > 0) {
        return 0;
    }
    camera = (Camera_001FC210 *)D_0031BEB0[index];
    if (camera == NULL) {
        return 0;
    }
    if (target == NULL) {
        target = &camera->target.x;
    }
    newTarget = camera->target;
    switch (mode) {
    case 1:
        func_001F2050(otherIndex, &newTarget);
        camera->target.x = newTarget.x * weight + target[0] * inverse;
        camera->target.y = newTarget.y * weight + target[1] * inverse;
        camera->target.z = newTarget.z * weight + target[2] * inverse;
        camera->target.w = 1.0f;
        direction_001FC210(index);
        polar_001FC210(index);
        break;
    case 2:
        oldPolar = camera->polar;
        func_001F2050(otherIndex, &newTarget);
        camera->target.x = newTarget.x * weight + target[0] * inverse;
        camera->target.y = newTarget.y * weight + target[1] * inverse;
        camera->target.z = newTarget.z * weight + target[2] * inverse;
        camera->target.w = 1.0f;
        direction_001FC210(index);
        polar_001FC210(index);
        oldPolar.y -= camera->polar.y;
        oldPolar.z -= camera->polar.z;
        oldPolar.x -= camera->polar.x;
        func_001FB6A0(index, 0, 1, oldPolar.y, oldPolar.z, oldPolar.x);
        break;
    }
    return 1;
}

s32 func_001FC6D0(s32 arg0, s32 arg1) {
    s32 entry;
    u16 flags;

    if (arg0 < 0 || arg0 > 0) {
        return 0;
    }
    entry = D_0031BEB0[arg0];
    if (entry == 0) {
        return 0;
    }
    if (arg1 < 0 || arg1 >= 10) {
        return 0;
    }
    flags = *(u16 *)((u8 *)entry + 0x8AC);
    if (flags & (1 << arg1)) {
        return 1;
    }
    return (flags & 0x200) ? 1 : 0;
}

s32 func_001FC760(s32 arg0, s32 arg1) {
    s32 temp_v1;
    u16 temp_a0;

    if (arg0 < 0 || arg0 > 0) {
        return 0;
    }
    temp_v1 = D_0031BEB0[arg0];
    if (temp_v1 == 0) {
        return 0;
    }
    if (arg1 < 0 || arg1 >= 0xA) {
        return 0;
    }
    temp_a0 = *(u16 *)((u8 *)temp_v1 + 0x8AE);
    if (temp_a0 & (1 << arg1)) {
        return 1;
    }
    return !(temp_a0 & 0x200) ? 0 : 1;
}

s32 func_001FC7F0(s32 arg0) {
    void *temp_v0;
    s32 result;

    if (arg0 < 0 || arg0 > 0) {
        result = -1;
    } else {
        temp_v0 = (void *)D_0031BEB0[arg0];
        if (temp_v0 == NULL) {
            result = -1;
        } else {
            result = *(s32 *)((u8 *)temp_v0 + 0x8B0);
        }
    }
    return result;
}

s32 func_001FC840(s32 arg0, s32 arg1) {
    void *temp_v0;

    if (arg0 < 0 || arg0 > 0) {
        return 0;
    }
    temp_v0 = (void *)D_0031BEB0[arg0];
    if (temp_v0 == NULL) {
        return 0;
    }
    *(s32 *)((u8 *)temp_v0 + 0x8B0) = arg1;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FC890);

void func_001FC950(void *arg0, void *arg1) {
    s32 *src = arg0;
    f32 *dst = arg1;

    dst[0] = (f32) src[0];
    dst[1] = (3.1415927f * (f32) src[1]) / 32768.0f;
    dst[2] = (3.1415927f * (f32) src[2]) / 32768.0f;
    dst[3] = (f32) src[3];
}

typedef struct {
    u8 pad00[0xC];
    u16 unkC;
} Data_001FC9B0;

typedef struct {
    u8 pad00[8];
    s32 size : 31;
    s32 flag : 1;
    u8 pad0C[8];
    Data_001FC9B0 *data;
} Entry_001FC9B0;

s32 func_001FC9B0(s32 arg0) {
    extern char D_002CFC50[];
    extern char D_002CFC67[];
    extern u16 D_00293070;
    extern void func_0019B648();
    extern void *func_001FFE00();
    char path[128];
    Entry_001FC9B0 *entry;
    Data_001FC9B0 *data;

    func_001FCA70();
    func_0019B648(path, D_002CFC50, func_001FFF90((s32)D_002CFC67), arg0, arg0);
    entry = func_001FFE00(1, path, 0, -1, 0, -1);
    if (entry == NULL) {
        return 0;
    }
    if (entry->size == 0 || (data = entry->data) == NULL) {
        return 0;
    }
    D_0031C048 = (s32)data;
    D_00293070 = data->unkC;
    return 1;
}

void func_001FCA70(void) {

    if (D_0031C048 != 0) {
        func_00217B50(D_0031C048);
        D_0031C048 = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FCAB0);

void func_001FCC20(void) {
    Entry_0031C050 *entry;
    s32 count;

    entry = D_0031C050;
    count = 2;
    while (count--) {
        entry->flag = 1;
        entry++;
    }
}

typedef struct {
    u8 r, g, b, a;
} Color_001FCC70;

typedef struct {
    u8 value : 6;
    u8 unused : 2;
} Value_001FCC70;

typedef struct {
    s8 flag : 1;
    s8 unused : 7;
} Flags_001FCC70;

s32 func_001FCC70(s32 arg0, s32 arg1, u8 arg2, u8 arg3, u8 arg4, void *arg5) {
    Entry_0031C050 *entry;

    entry = &D_0031C050[arg0];
    if (entry->flag == 0) {
        return 0;
    }
    ((Value_001FCC70 *)((u8 *)entry + 7))->value = arg1;
    entry->pad0[4] = arg2;
    entry->lo = arg3;
    entry->hi = arg4;
    entry->flag = 0;
    entry->pad7b = 0;
    ((Flags_001FCC70 *)entry->pad8)->flag = 0;
    if (arg5 != 0) {
        *(Color_001FCC70 *)entry->pad0 = *(Color_001FCC70 *)arg5;
    } else {
        entry->pad0[2] = 0;
        entry->pad0[1] = 0;
        entry->pad0[0] = 0;
        entry->pad0[3] = 0x80;
    }
    return 1;
}

s32 func_001FCD60(s32 arg0) {
    Entry_0031C050 *temp_a2;

    temp_a2 = &D_0031C050[arg0];
    temp_a2->flag = 1;
    return 1;
}

void func_001FCDA0(void) {
    s32 i;

    i = 0;
    do {
        func_001FCDE0(i);
        i += 1;
    } while (i < 2);
}

typedef struct {
    s8 paused : 1;
    s8 unused : 7;
} Flags_001FCDE0;

s32 func_001FCDE0(s32 arg0) {
    u8 color[4];
    Entry_0031C050 *entry;
    s32 next;
    u8 amount;

    if ((arg0 < 0) || (arg0 >= 2)) {
        return 0;
    }
    entry = &D_0031C050[arg0];
    if (entry->flag != 0) {
        return 0;
    }
    amount = entry->lo;
    if (!(*(u8 *)((u8 *)entry + 7) & 0x3F)) {
        amount = entry->hi - amount;
    }
    color[2] = entry->pad0[2];
    color[1] = entry->pad0[1];
    color[0] = entry->pad0[0];
    color[3] = (entry->pad0[3] * (amount & 0xFF)) / entry->hi;
    func_001FCF30(0, (s32)color, 0xFFFFFF);
    if (entry->lo >= entry->hi) {
        if (entry->pad7b != 0) {
            entry->flag = 1;
        }
    } else if (((Flags_001FCDE0 *)&entry->pad8[0])->paused == 0) {
        next = entry->lo + entry->pad0[4];
        if (entry->hi < next) {
            entry->lo = entry->hi;
        } else {
            entry->lo = next;
        }
    }
    return 1;
}

void func_001FCF30(s32 arg0, s32 arg1, s32 arg2) {
    func_00209D30(func_001FCF90(func_00209D20(), arg0, arg1, arg2));
}

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 reserved : 8;
} Vertex_001FCF90;

typedef struct {
    u16 count;
    u16 flags;
    u32 reserved;
    u64 registers;
} Header_001FCF90;

typedef struct {
    u64 tag[2];
    u8 color[4];
    f32 q;
    Vertex_001FCF90 vertices[2];
} Packet_001FCF90;

static inline void init_001FCF90(void *tag) {
    ((Header_001FCF90 *)tag)->flags = 6;
    ((Header_001FCF90 *)tag)->count = 3;
    ((Header_001FCF90 *)tag)->registers = 0x441;
    ((Header_001FCF90 *)tag)->reserved = 0;
}

s32 func_001FCF90(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    Packet_001FCF90 packet;

    init_001FCF90((Header_001FCF90 *)packet.tag);
    func_002086D0(&packet, func_00208D00(arg1));
    packet.color[0] = ((u8 *)arg2)[2];
    packet.color[1] = ((u8 *)arg2)[1];
    packet.color[2] = ((u8 *)arg2)[0];
    packet.color[3] = ((u8 *)arg2)[3];
    packet.q = 1.0f;
    packet.vertices[0].x = 0x6C00;
    packet.vertices[0].y = 0x7200;
    packet.vertices[0].z = (u32)arg3;
    packet.vertices[0].reserved = 0;
    packet.vertices[1].x = 0x9400;
    packet.vertices[1].y = 0x8E00;
    packet.vertices[1].z = (u32)arg3;
    packet.vertices[1].reserved = 0;
    return func_00207650(arg0, (s32)&packet, 0, 0);
}

s32 func_001FD0B0(s32 arg0) {
    Entry_0031C050 *entry;

    if (arg0 < 0 || arg0 >= 2) {
        return 0;
    }
    entry = &D_0031C050[arg0];
    if (entry->flag) {
        return 0;
    }
    entry->pad7b = -1;
    return 1;
}

typedef struct {
    s8 enabled : 1;
    s8 pad : 7;
} Flags_001FD130;

s32 func_001FD130(s32 arg0, s64 arg1) {
    Entry_0031C050 *temp_a2;

    if (arg0 < 0 || arg0 >= 2) {
        return 0;
    }
    temp_a2 = &D_0031C050[arg0];
    if (temp_a2->flag != 0) {
        return 0;
    }
    ((Flags_001FD130 *) temp_a2->pad8)->enabled = (s8) arg1;
    return 1;
}

s32 func_001FD1B0(s32 arg0) {
    Entry_0031C050 *e;

    if (arg0 < 0 || arg0 >= 2) {
        return -1;
    }
    e = &D_0031C050[arg0];
    if (e->flag != 0) {
        return -1;
    }
    return e->hi - e->lo;
}

static inline s32 calc_001FD220(s32 idx) {
    Entry_0031C050 *e;

    if (idx < 0 || idx >= 2) {
        return -1;
    }
    e = &D_0031C050[idx];
    if (e->flag) {
        return -1;
    }
    return e->hi - e->lo;
}

s32 func_001FD220(s32 arg0) {
    s32 i;
    s32 want = arg0 ? 1 : 0;

    for (i = 0; i < 2; i++) {
        if (calc_001FD220(i) >= want) {
            return 1;
        }
    }
    return 0;
}

void func_001FD2B0(void) {
    extern u8 D_0031C070[];

    func_0020B3C0((s8 *)D_0031C070, 0, 0x27C);
}

s32 func_001FD2D0(s32 arg0, s32 arg1) {
    s32 sp3C;

    func_00209D30(func_001FD320(func_00209D20(), arg0, arg1, &sp3C));
    return sp3C;
}

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FD320);

void func_001FD4B0(s32 arg0) {
    D_0031C2E4 = arg0;
}

typedef union Packet_001FD4C0 {
    u64 words[14];
    struct {
        u16 count;
        u8 pad02;
        u8 flag;
        u32 pad04;
        u32 dma0;
        u32 dma1;
    } header;
} Packet_001FD4C0;

void func_001FD4C0(u64 *arg0, s32 arg1, s32 arg2) {
    extern void *func_0020B340(void *, void *, s32);
    extern u8 D_002CFC70[][16];
    extern u8 D_002CFCA0[][16];
    Packet_001FD4C0 *packet = (Packet_001FD4C0 *)arg0;
    u8 colors[16][4];
    s32 i;
    u64 *end;
    s32 count;

    for (i = 0; i < 16; i++) {
        colors[i][0] = colors[i][1] = colors[i][2] = D_002CFCA0[arg1][i];
        colors[i][3] = D_002CFC70[arg1][i];
    }

    arg0[1] = 0;
    arg0[0] = 0;
    ((Packet_001FD4C0 *)arg0)->header.flag = 0x10;
    arg0[2] = 4 | ((u64)0x10000000 << 32);
    arg0[3] = 0xE;
    arg0[4] = ((s64)arg2 << 32) | ((u64)0x10000 << 32);
    arg0[5] = 0x50;
    arg0[6] = 0;
    arg0[7] = 0x51;
    arg0[8] = 8 | ((u64)2 << 32);
    arg0[9] = 0x52;
    arg0[10] = 0;
    arg0[11] = 0x53;
    arg0[12] = 0x8004 | ((u64)0x08000000 << 32);
    arg0[13] = 0;
    arg0 += 14;
    end = func_0020B340(arg0, colors, 16);
    count = ((end - packet->words) >> 1) - 1;
    packet->header.count = count;
    packet->header.dma0 = 0x11000000;
    packet->header.dma1 = (count & 0xFFFF) | 0x51000000;
}

void func_001FD610(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_00209D30(func_001FD680(func_00209D20(), arg0, arg1, arg2, arg3));
}

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FD680);

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FDB90);

typedef struct {
    u64 TBP0 : 14;
    u64 TBW : 6;
    u64 PSM : 6;
    u64 TW : 4;
    u64 TH : 4;
    u64 TCC : 1;
    u64 TFX : 2;
    u64 CBP : 14;
    u64 CPSM : 4;
    u64 CSM : 1;
    u64 CSA : 5;
    u64 CLD : 3;
} Tex0_001FDD70;

typedef struct {
    u64 LCM : 1;
    u64 : 1;
    u64 MXL : 3;
    u64 MMAG : 1;
    u64 MMIN : 3;
    u64 MTBA : 1;
    u64 : 9;
    u64 L : 2;
    u64 : 11;
    u64 K : 12;
    u64 : 20;
} Tex1_001FDD70;

typedef struct {
    s32 width;
    s32 height;
    s32 tw;
    s32 th;
    s32 cbp;
    s32 tbp;
    s32 cbpOffset;
} TexInfo_001FDD70;

void func_001FDD70(void *arg0, void *arg1) {
    extern TexInfo_001FDD70 D_0031C070;
    TexInfo_001FDD70 *texture = &D_0031C070;

    if (arg0 != NULL) {
        ((Tex0_001FDD70 *)arg0)->TBP0 = texture->tbp;
        ((Tex0_001FDD70 *)arg0)->TBW = texture->width >> 6;
        ((Tex0_001FDD70 *)arg0)->PSM = 20;
        ((Tex0_001FDD70 *)arg0)->TW = texture->tw;
        ((Tex0_001FDD70 *)arg0)->TH = texture->th;
        ((Tex0_001FDD70 *)arg0)->TCC = 1;
        ((Tex0_001FDD70 *)arg0)->TFX = 0;
        ((Tex0_001FDD70 *)arg0)->CBP = texture->cbp + texture->cbpOffset;
        ((Tex0_001FDD70 *)arg0)->CPSM = 0;
        ((Tex0_001FDD70 *)arg0)->CSM = 0;
        ((Tex0_001FDD70 *)arg0)->CSA = 0;
        ((Tex0_001FDD70 *)arg0)->CLD = 1;
    }
    if (arg1 != NULL) {
        ((Tex1_001FDD70 *)arg1)->LCM = 0;
        ((Tex1_001FDD70 *)arg1)->MXL = 0;
        ((Tex1_001FDD70 *)arg1)->MMAG = 0;
        ((Tex1_001FDD70 *)arg1)->MMIN = 0;
        ((Tex1_001FDD70 *)arg1)->MTBA = 0;
        ((Tex1_001FDD70 *)arg1)->L = 0;
        ((Tex1_001FDD70 *)arg1)->K = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FDFE0);

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FE290);

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FE660);

void func_001FE750(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_00209D30(func_001FE7D0(func_00209D20(), arg0, arg1, arg2, arg3, arg4));
}

typedef struct Rect_001FE7D0 {
    s32 x;
    s32 y;
    s32 w;
    s32 h;
} Rect_001FE7D0;

typedef s32 (*Draw_001FE7D0)(s32, s32, s32, s32, Rect_001FE7D0 *, s32);

s32 func_001FE7D0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    extern Rect_001FE7D0 D_002CFCD0;
    Rect_001FE7D0 rect;
    s32 *info;

    info = func_001FEAB0(arg1);
    rect = D_002CFCD0;
    if (info == NULL) {
        return arg0;
    }
    rect.w = info[3];
    rect.h = info[4];
    return ((Draw_001FE7D0)arg5)(arg0, arg1, arg2, arg3, &rect, arg4);
}

void func_001FE880(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_00209D30(func_001FE8F0(func_00209D20(), arg0, arg1, arg2, arg3));
}

typedef struct Xyzf_001FE8F0 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Xyzf_001FE8F0;

typedef struct Packet_001FE8F0 {
    u16 count;
    u16 size;
    u32 flags;
    u64 registers;
    u8 r, g, b, a;
    f32 q;
    Xyzf_001FE8F0 first;
    Xyzf_001FE8F0 second;
} Packet_001FE8F0;

typedef struct State_001FE8F0 {
    u8 pad[0x274];
    s32 depth;
} State_001FE8F0;

static inline void tag_001FE8F0(void *packet) {
    *(u16 *)((u8 *)packet + 2) = 6;
    *(u16 *)packet = 3;
    *(u64 *)((u8 *)packet + 8) = 0x441;
    *(u32 *)((u8 *)packet + 4) = 0;
}

s32 func_001FE8F0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    extern u8 D_00293088[];
    extern s32 D_002CFCD0[];
    extern State_001FE8F0 D_0031C070;
    Packet_001FE8F0 packet;
    u8 *color = (u8 *)arg4;
    State_001FE8F0 *state = &D_0031C070;
    s32 x0;
    s32 y0;
    s32 x1;
    s32 y1;
    s32 *rect = (s32 *)arg3;

    if (rect == NULL) {
        rect = D_002CFCD0;
    }
    if (color == NULL) {
        color = D_00293088;
    }
    x0 = rect[0] + arg1;
    y0 = rect[1] + arg2;
    x1 = rect[2] + x0;
    y1 = rect[3] + y0;
    tag_001FE8F0(&packet);
    func_002086D0(&packet, 0x8000000044LL);
    packet.r = color[2];
    packet.g = color[1];
    packet.b = color[0];
    packet.a = color[3];
    packet.q = 1.0f;
    packet.first.x = x0 << 4;
    packet.first.y = y0 << 4;
    packet.first.z = state->depth;
    packet.first.fog = 0;
    packet.second.x = x1 << 4;
    packet.second.y = y1 << 4;
    packet.second.z = state->depth;
    packet.second.fog = 0;
    return func_00207650(arg0, (s32)&packet, 0, 0);
}

typedef struct Vec4_001FEA80 {
    f32 x, y, z, w;
} Vec4_001FEA80;

extern Vec4_001FEA80 D_002CFCD0;

void func_001FEA80(void *arg0) {
    *(Vec4_001FEA80 *)arg0 = D_002CFCD0;
}

void *func_001FEAB0(s32 arg0) {
    extern u8 D_0031C070[];
    u8 *data = D_0031C070;
    void *result;

    if (arg0 >= 0) {
        result = NULL;
        if (arg0 < 0x1E) {
            result = data + (arg0 * 0x14) + 0x1C;
        }
    } else {
        result = NULL;
    }
    return result;
}

typedef struct {
    u8 pad00[0x13];
    s8 low_001FEAF0 : 7;
    s8 flag_001FEAF0 : 1;
} Entry_001FEAF0;

typedef struct {
    u8 pad00[0xC];
    Entry_001FEAF0 entries[30];
} Table_001FEAF0;

extern Table_001FEAF0 D_0031C070;

void func_001FEAF0(s32 arg0) {
    Table_001FEAF0 *t = &D_0031C070;

    if (arg0 >= 0 && arg0 < 0x1E) {
        t->entries[arg0].flag_001FEAF0 = 0;
    }
}

typedef struct {
    s8 pad0[3];
    s8 unused : 7;
    s8 active : 1;
    s8 pad4[16];
} Entry_001FEB40;

extern Entry_001FEB40 D_0031C08C[30];

void func_001FEB40(void) {
    Entry_001FEB40 *entry;
    s32 i;

    entry = D_0031C08C;
    i = 0;
    do {
        i += 1;
        entry->active = 0;
        entry++;
    } while (i < 30);
}

typedef struct Flags_001FEB80 {
    s8 bit0 : 1;
    s8 bit1 : 1;
    s8 bits2_7 : 6;
} Flags_001FEB80;

typedef struct State_001FEB80 {
    u8 pad[0x6688];
    s32 field_6688;
    s16 field_668C;
    s16 field_668E;
    Flags_001FEB80 field_6690;
} State_001FEB80;

typedef struct Entry36_001FEB80 {
    s32 field0;
    u8 pad[0x20];
} Entry36_001FEB80;

typedef struct Entry8_001FEB80 {
    s32 field0;
    s32 field4;
} Entry8_001FEB80;

extern State_001FEB80 D_0031C2F0;
extern Entry36_001FEB80 D_00320370[];
extern Entry8_001FEB80 D_00322770[];

void func_001FEB80(void) {
    State_001FEB80 *state;
    Entry8_001FEB80 *small;
    Entry36_001FEB80 *large;
    s32 count;

    state = &D_0031C2F0;
    large = D_00320370;
    small = D_00322770;
    count = 0x100;
    func_0020B3C0((s8 *)&D_0031C2F0, 0, 0x66A0);
    while (count--) {
        large->field0 = -1;
        large++;
    }
    count = 0x40;
    while (count--) {
        small->field0 = -1;
        small++;
    }
    state->field_668C = 0;
    state->field_668E = 0;
    state->field_6688 = -1;
    state->field_6690.bit1 = 0;
}

void func_001FEC70(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s64 arg5) {
    func_001FECB0(arg0, 0, arg1, arg2, arg3, 0, -1, arg4, arg5);
}

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FECB0);

s32 func_0019C028(const char *, const char *, s32);
char *func_0019C478(const char *, s32);
extern char *D_00293090[];
extern s64 D_00293098[];
extern s32 D_002930A8[];
extern char D_002D0638[];
extern char D_002D063D[];

typedef struct Record_001FEDA0 {
    s32 id;
    s16 type;
    s16 count;
    u32 size : 31;
    s32 sizeFlag : 1;
    u32 offset : 31;
    s32 offsetFlag : 1;
    u32 limit : 31;
    s32 discFlag : 1;
    s32 mode;
    s32 arg8;
    s32 arg9;
    char *file;
} Record_001FEDA0;

static inline void initialize_001FEDA0(Record_001FEDA0 *record,
                                      s32 type, s32 count, s32 mode,
                                      s32 size, s32 offset, s32 limit,
                                      s32 arg8, s32 arg9) {
    record->type = type;
    record->count = count > 0 ? count : 0;
    record->size = size;
    record->offset = offset;
    record->limit = limit;
    record->sizeFlag = 0;
    record->offsetFlag = 0;
    record->mode = mode;
    record->arg8 = arg8;
    record->arg9 = arg9;
}

s32 func_001FEDA0(void *arg0, s32 arg1, s32 arg2, void *arg3,
                 s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                 s32 arg8, s32 arg9) {
    char buffer[128];
    Record_001FEDA0 *record = arg0;

    if (record == NULL) {
        return 0;
    }
    if (arg3 == 0) {
        return 0;
    }
    if (func_00197548((s32)D_002D0638) != NULL) {
        if (!((u32)arg3 & 0x80000000)) {
            s32 name;
            u32 i;
            s32 length;
            char **entry;
            s32 digit1;
            s32 digit2;
            s32 digit3;

            func_0019BDD8(buffer, (char *)arg3);
            if ((name = (s32)func_0019C478(buffer, '/')) != NULL ||
                (name = (s32)func_0019C478(buffer, '\\')) != NULL) {
                length = func_0019BEF0((char *)(name + 1));
                if (length >= 8 && arg1 == 0x1400 &&
                    (((char *)name)[1] == 'M' || ((char *)name)[1] == 'm') &&
                    (digit1 = ((char *)name)[2]) >= '0' && digit1 <= '9' &&
                    (digit2 = ((char *)name)[3]) >= '0' && digit2 <= '9' &&
                    (digit3 = ((char *)name)[4]) >= '0' && digit3 <= '9' &&
                    ((char *)name)[5] == '.' &&
                    (((char *)name)[6] == 'G' || ((char *)name)[6] == 'g') &&
                    (((char *)name)[7] == 'R' || ((char *)name)[7] == 'r') &&
                    (((char *)name)[8] == 'P' || ((char *)name)[8] == 'p')) {
                    arg6 += func_001DE130(digit3 - '0' +
                                         ((digit1 - '0') * 100 +
                                          (digit2 - '0') * 10)) * 0x80800;
                    name = (s32)D_002D063D;
                    length = func_0019BEF0((char *)(name + 1));
                }
                entry = D_00293090;
                i = 0;
                do {
                    char *path = func_0019C478(*entry, '\\');
                    if (path != NULL && func_0019C028((char *)(name + 1), path + 1, length) == 0) {
                        arg3 = (void *)(D_00293098[i * 4] | 0x80000000);
                        if (arg5 < 0) {
                            arg5 = D_002930A8[i * 8] << 11;
                        }
                        break;
                    }
                    i++;
                    entry += 8;
                } while (i < 97U);
            }
        }
    }
    if ((u32)arg3 & 0x80000000) {
        if (arg5 < 0) {
            return 0;
        }
        if (arg5 > 0 && arg5 % 2048 != 0) {
            return 0;
        }
        if (arg6 % 2048 != 0) {
            return 0;
        }
        if (arg7 > 0 && arg7 % 2048 != 0) {
            return 0;
        }
        record->file = NULL;
        record->discFlag = 1;
        record->id = (u32)arg3 & 0x7FFFFFFF;
    } else {
        char *file = func_00217B60((char *)arg3);
        record->file = file;
        if (file == NULL) {
            return 0;
        }
        func_001FF250((s8 *)record->file);
        record->discFlag = 0;
        record->id = 0;
    }
    initialize_001FEDA0(record, arg1, arg2, arg4, arg5, arg6, arg7, arg8, arg9);
    return 1;
}

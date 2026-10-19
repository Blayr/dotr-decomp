/* The camera (SzView_*), part 2 of 2: look points, roll and camera motion. Starts where it does for the compiler (see README, How the files are split). */

#include "common.h"

extern f32 identityMatrix[4][4]; /* original: gSzView_vecUnit */

typedef struct Vec4_001FB500 {
    f32 x, y, z, w;
} Vec4_001FB500;

typedef struct Camera_001FB500 {
    Vec4_001FB500 param;
    f32 direction[4];
    f32 origin[4];
    f32 target[4];
} Camera_001FB500;

/* Works out a view's aim. */
static inline s32 aim_001FB500(s32 index) {
    Camera_001FB500 *entry;

    if ((index < 0) || (index > 0)) {
        return 0;
    }
    entry = (Camera_001FB500 *)views[index];
    if (entry == 0) {
        return 0;
    }
    entry->direction[0] = entry->target[0] - entry->origin[0];
    entry->direction[1] = entry->target[1] - entry->origin[1];
    entry->direction[2] = entry->target[2] - entry->origin[2];
    entry->direction[3] = 0.0f;
    RhGeom_NormalizeVector(entry->direction);
    return 1;
}

/* Sets view `index`'s look point. */
s32 SzView_SetLookCP(s32 index, f32 *src) {
    Camera_001FB500 *entry;
    f32 matrix[4][4];
    f32 angles[4];

    if ((index < 0) || (index > 0)) {
        return 0;
    }
    entry = (Camera_001FB500 *)views[index];
    if (entry == 0) {
        return 0;
    }
    if (src == NULL) {
        return 0;
    }
    entry->param = *(Vec4_001FB500 *)src;
    entry->param.y = func_001A6C30(6.2831855f + entry->param.y, 6.2831855f);
    if (SzView_GetLookVector(index, (s32)angles) != 0) {
        RhGeom_GetRotXYZMatrix(matrix, angles);
    }
    RhGeom_MulMatrixVector(entry->direction, matrix, identityMatrix);
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

/* Turns view `view`'s camera around its look point (`aroundLook`) or itself over `frames` frames: by heading,
   pitch (kept short of straight up or down) and distance. */
s32 SzView_RollCamera(s32 view, s32 aroundLook, s32 frames, f32 fparg0, f32 fparg1, f32 fparg2) {
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

    if ((view < 0) || (view > 0)) {
        return 0;
    }
    slot = &views[view];
    camera = (Camera_001FB6A0 *)*slot;
    if (camera == 0) {
        return 0;
    }
    if (frames > 0) {
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
        if (aroundLook == 0) {
            radius = camera->radius + fparg2;
            if (radius < minimum) {
                SzView_RollCamera(view, 1, -frames, 0.0f, 0.0f, minimum - radius);
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
    horizontal = camera->radius * RhMath_Cos(camera->pitch);
    vertical = camera->radius * RhMath_Sin(camera->pitch);
    depth = horizontal * RhMath_Sin(camera->yaw);
    horizontal *= RhMath_Cos(camera->yaw);
    scale = (f32)frames;
    destination[0] = source[0] + horizontal * scale;
    destination[1] = source[1] + vertical * scale;
    destination[2] = source[2] + depth * scale;
    if (view >= 0) {
        if (view <= 0) {
            camera = (Camera_001FB6A0 *)*slot;
            if (camera != 0) {
                camera->direction[0] = camera->target[0] - camera->eye[0];
                camera->direction[1] = camera->target[1] - camera->eye[1];
                camera->direction[2] = camera->target[2] - camera->eye[2];
                camera->direction[3] = 0.0f;
                RhGeom_NormalizeVector(camera->direction);
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

/* Works out a view's look direction. */
static inline void direction_001FB940(s32 index) {
    Camera_001FB940 *camera;
    if (index >= 0 && index <= 0) {
        camera = (Camera_001FB940 *)views[index];
        if (camera != NULL) {
            camera->direction.x = camera->target.x - camera->eye.x;
            camera->direction.y = camera->target.y - camera->eye.y;
            camera->direction.z = camera->target.z - camera->eye.z;
            camera->direction.w = 0.0f;
            RhGeom_NormalizeVector(&camera->direction.x);
        }
    }
}

/* Works out a view's spherical position. */
static inline void polar_001FB940(s32 index) {
    Camera_001FB940 *camera;
    Vec4_001FB940 *eye;
    Vec4_001FB940 *target;
    Vec4_001FB940 polar;
    if (index >= 0) {
        if (index <= 0) {
            camera = (Camera_001FB940 *)views[index];
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

/* Plays camera motion `motion` on view `index` over `duration` frames from `frame`, blended with its current
   camera. */
s32 SzView_SetInterpCameraMotion(s32 index, void *motion, s32 duration, s32 frame, s32 parent, s32 mirror) {
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
    slot = &views[index];
    camera = (Camera_001FB940 *)*slot;
    if (camera == NULL) {
        return 0;
    }
    targetData = (u8 *)motion + ((Motion_001FB940 *)motion)->targetOffset * 8 + 0x20;
    angleData = (u8 *)motion + ((Motion_001FB940 *)motion)->angleOffset * 8 + 0x20;
    fovData = (u8 *)motion + ((Motion_001FB940 *)motion)->fovOffset * 8 + 0x20;
    time = ((f32)(((Motion_001FB940 *)motion)->frames - 1) * (f32)frame) / (f32)duration;
    lSzView_CalcInterpCameraMotion(&camera->eye, (u8 *)motion + ((Motion_001FB940 *)motion)->eyeOffset * 8 + 0x20, ((Motion_001FB940 *)motion)->eyeCount, time);
    lSzView_CalcInterpCameraMotion(&camera->target, targetData, ((Motion_001FB940 *)motion)->targetCount, time);
    angle = lSzView_CalcInterpCameraMotion1(angleData, ((Motion_001FB940 *)motion)->angleCount, time);
    fov = lSzView_CalcInterpCameraMotion1(fovData, ((Motion_001FB940 *)motion)->fovCount, time);
    camera->angle = func_001A22C0((32768.0f * angle) / 180.0f);
    halfFov = ((3.1415927f * fov) / 180.0f) / 2.0f;
    if (halfFov < 0.000001f) {
        halfFov = 0.000001f;
    }
    sine = RhMath_Cos(halfFov);
    camera->distance = 224.0f * (sine / RhMath_Sin(halfFov));
    if (camera->distance < camera->minimum) {
        camera->distance = camera->minimum;
    }
    if (mirror != 0) {
        camera->eye.x = -camera->eye.x;
        camera->target.x = -camera->target.x;
        camera->angle = -camera->angle;
    }
    if (parent >= 0) {
        if (SzModel_GetRot(parent, &rotation) != 0) {
            RhGeom_GetRotXYZMatrix(matrix, &rotation);
            RhGeom_PushMatrix((s32)matrix);
            RhGeom_MulMatrixVector(&camera->eye, NULL, &camera->eye);
            RhGeom_MulMatrixVector(&camera->target, NULL, &camera->target);
            RhGeom_PopMatrix();
        }
        if (SzModel_GetPos(parent, &translation) != 0) {
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

typedef struct Key_001FBE50 {
    u32 time;
    f32 value[3];
} Key_001FBE50;

/* The camera of a camera motion at frame `frame`, blended by `t`. */
void lSzView_CalcInterpCameraMotion(void *out, void *motion, s32 frame, f32 t) {
    f32 var_f0;
    f32 var_f0_2;
    f32 var_f0_3;
    f32 var_f0_4;
    f32 var_f3;
    f32 weight;
    f32 weight2;
    s32 temp_v1;
    Key_001FBE50 *temp_a2;
    Key_001FBE50 *next;
    u32 time2;
    u32 time;
    u32 temp_v0;
    u32 temp_v0_2;
    u32 temp_v0_3;
    s32 var_a2;
    s32 var_a3;
    s32 var_t0;
    void *temp_t1;

    var_a3 = 0;
    if (frame > 2) {
    var_a2 = 0;
    var_t0 = frame;
loop_2:
    var_a3 = (s32)(var_a2 + var_t0) >> 1;
    if (var_a2 >= var_a3) {
        goto block_15;
    }
    temp_t1 = (u8 *)motion + (var_a3 * 16);
    temp_v0 = *(u32 *)((u8 *)temp_t1 + 16);
    var_f0_3 = (f32)temp_v0;
    if (!(t < var_f0_3)) {
        var_a2 = var_a3;
        goto loop_2;
    }
    temp_v0_2 = *(u32 *)temp_t1;
    var_f0_4 = (f32)temp_v0_2;
    if (t < var_f0_4) {
        var_t0 = var_a3;
        goto loop_2;
    }
    }
block_15:
    temp_a2 = (Key_001FBE50 *)((u8 *)motion + var_a3 * 16);
    temp_v1 = var_a3 + 1;
    if (temp_v1 >= frame) {
        ((f32 *)out)[0] = temp_a2->value[0];
        ((f32 *)out)[1] = temp_a2->value[1];
        ((f32 *)out)[2] = temp_a2->value[2];
        return;
    }
    next = (Key_001FBE50 *)((u8 *)motion + temp_v1 * 16);
    time = temp_a2->time;
    time2 = next->time;
    temp_v0_3 = time2 - time;
    var_f3 = (f32)temp_v0_3;
    var_f0 = (f32)time2;
    var_f0_2 = (f32)time;
    weight = (var_f0 - t) / var_f3;
    weight2 = (t - var_f0_2) / var_f3;
    ((f32 *)out)[0] = weight * temp_a2->value[0] + weight2 * next->value[0];
    ((f32 *)out)[1] = weight * temp_a2->value[1] + weight2 * next->value[1];
    ((f32 *)out)[2] = weight * temp_a2->value[2] + weight2 * next->value[2];
}

typedef struct Key_001FC050 {
    u32 time;
    f32 value;
} Key_001FC050;

/* One channel of a camera motion at frame `frame`, blended by `t`. */
f32 lSzView_CalcInterpCameraMotion1(u8 *channel, s32 frame, f32 t) {
    f32 var_f0;
    f32 var_f0_2;
    f32 var_f0_3;
    f32 var_f0_4;
    f32 var_f3;
    f32 weight;
    f32 result;
    Key_001FC050 *temp_a2;
    u32 time;
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
    if (frame > 2) {
    var_a2 = 0;
    var_t0 = frame;
loop_2:
    var_a3 = (s32)(var_a2 + var_t0) >> 1;
    var_v0 = var_a3 * 8;
    if (var_a2 >= var_a3) {
        goto block_15;
    }
    temp_t1 = channel + (var_a3 * 8);
    temp_v0 = *(u32 *)((u8 *)temp_t1 + 8);
    var_f0_3 = (f32)temp_v0;
    if (!(t < var_f0_3)) {
        var_a2 = var_a3;
        goto loop_2;
    }
    temp_v0_2 = *(u32 *)temp_t1;
    var_f0_4 = (f32)temp_v0_2;
    if (t < var_f0_4) {
        var_t0 = var_a3;
        goto loop_2;
    }
    }
block_15:
    var_v0 = var_a3 * 8;
    temp_a2 = (Key_001FC050 *)(channel + var_v0);
    temp_v1 = var_a3 + 1;
    if (temp_v1 >= frame) {
        return temp_a2->value;
    }
    channel += temp_v1 * 8;
    time = temp_a2->time;
    temp_a3 = *(u32 *)channel;
    temp_v0_3 = temp_a3 - time;
    var_f3 = (f32)temp_v0_3;
    var_f0 = (f32)temp_a3;
    var_f0_2 = (f32)time;
    weight = (var_f0 - t) / var_f3;
    result = weight * temp_a2->value;
    weight = (t - var_f0_2) / var_f3;
    return result + weight * *(f32 *)(channel + 4);
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

/* Works out a view's look direction. */
static inline void direction_001FC210(s32 index) {
    if (index >= 0 && index <= 0) {
        Camera_001FC210 *camera = (Camera_001FC210 *)views[index];
        if (camera != NULL) {
        camera->direction.x = camera->target.x - camera->position.x;
        camera->direction.y = camera->target.y - camera->position.y;
        camera->direction.z = camera->target.z - camera->position.z;
        camera->direction.w = 0.0f;
        RhGeom_NormalizeVector(&camera->direction.x);
        }
    }
}

/* Works out a view's spherical position. */
static inline void polar_001FC210(s32 index) {
    if (index >= 0 && index <= 0) {
        Camera_001FC210 *camera = (Camera_001FC210 *)views[index];
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

/* Puts view `index`'s camera where view `otherIndex` looks at `target`, mixed by `weight`. */
s32 SzView_SetViewCamera(s32 index, s32 otherIndex, f32 *target, s32 mode, f32 weight) {
    f32 inverse = 1.0f - weight;
    Camera_001FC210 *camera;
    Vec4_001FC210 newTarget;
    Vec4_001FC210 oldPolar;

    if (index < 0 || index > 0) {
        return 0;
    }
    camera = (Camera_001FC210 *)views[index];
    if (camera == NULL) {
        return 0;
    }
    if (target == NULL) {
        target = &camera->target.x;
    }
    newTarget = camera->target;
    switch (mode) {
    case 1:
        SzModel_GetCenter(otherIndex, &newTarget);
        camera->target.x = newTarget.x * weight + target[0] * inverse;
        camera->target.y = newTarget.y * weight + target[1] * inverse;
        camera->target.z = newTarget.z * weight + target[2] * inverse;
        camera->target.w = 1.0f;
        direction_001FC210(index);
        polar_001FC210(index);
        break;
    case 2:
        oldPolar = camera->polar;
        SzModel_GetCenter(otherIndex, &newTarget);
        camera->target.x = newTarget.x * weight + target[0] * inverse;
        camera->target.y = newTarget.y * weight + target[1] * inverse;
        camera->target.z = newTarget.z * weight + target[2] * inverse;
        camera->target.w = 1.0f;
        direction_001FC210(index);
        polar_001FC210(index);
        oldPolar.y -= camera->polar.y;
        oldPolar.z -= camera->polar.z;
        oldPolar.x -= camera->polar.x;
        SzView_RollCamera(index, 0, 1, oldPolar.y, oldPolar.z, oldPolar.x);
        break;
    }
    return 1;
}

/* Whether setting set `set` of view `view` (or its default) has depth fog. */
s32 SzView_IsFogZ(s32 view, s32 set) {
    s32 entry;
    u16 flags;

    if (view < 0 || view > 0) {
        return 0;
    }
    entry = views[view];
    if (entry == 0) {
        return 0;
    }
    if (set < 0 || set >= 10) {
        return 0;
    }
    flags = *(u16 *)((u8 *)entry + 0x8AC);
    if (flags & (1 << set)) {
        return 1;
    }
    return (flags & 0x200) ? 1 : 0;
}

/* Whether setting set `set` of view `view` (or its default) has height fog. */
s32 SzView_IsFogY(s32 view, s32 set) {
    s32 temp_v1;
    u16 temp_a0;

    if (view < 0 || view > 0) {
        return 0;
    }
    temp_v1 = views[view];
    if (temp_v1 == 0) {
        return 0;
    }
    if (set < 0 || set >= 0xA) {
        return 0;
    }
    temp_a0 = *(u16 *)((u8 *)temp_v1 + 0x8AE);
    if (temp_a0 & (1 << set)) {
        return 1;
    }
    return !(temp_a0 & 0x200) ? 0 : 1;
}

/* View `view`'s camera mode, or -1. */
s32 SzView_GetMode(s32 view) {
    void *state;
    s32 result;

    if (view < 0 || view > 0) {
        result = -1;
    } else {
        state = (void *)views[view];
        if (state == NULL) {
            result = -1;
        } else {
            result = *(s32 *)((u8 *)state + 0x8B0);
        }
    }
    return result;
}

/* Sets view `view`'s camera mode. */
s32 SzView_SetMode(s32 view, s32 mode) {
    void *temp_v0;

    if (view < 0 || view > 0) {
        return 0;
    }
    temp_v0 = (void *)views[view];
    if (temp_v0 == NULL) {
        return 0;
    }
    *(s32 *)((u8 *)temp_v0 + 0x8B0) = mode;
    return 1;
}

/* Radians to the game's fixed angle units. */
static inline s32 toAngle_001FC890(f32 radians) {
    return (s32)(32768.0f * radians / 3.1415927f);
}

/* A float vector (angles in radians) to the game's integer vector (fixed angles). */
void SzView_V2IV(f32 *src, s32 *dst) {
    dst[0] = (s32)src[0];
    dst[1] = toAngle_001FC890(src[1]);
    dst[2] = toAngle_001FC890(src[2]);
    dst[3] = (s32)src[3];
}

/* The game's integer vector (distance, fixed heading and pitch) to a float vector. */
void SzView_IV2V(void *intVec, void *floatVec) {
    s32 *src = intVec;
    f32 *dst = floatVec;

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

/* Starts the camera system for game mode `mode`. */
s32 SzView_InitCamera(s32 mode) {
    extern char D_002CFC50[];
    extern char D_002CFC67[];
    extern u16 gSzView_wFrame;
    extern void func_0019B648();
    extern void *SzFile_ReadParam();
    char path[128];
    Entry_001FC9B0 *entry;
    Data_001FC9B0 *data;

    SzView_TermCamera();
    func_0019B648(path, D_002CFC50, SzFile_GetEnv((s32)D_002CFC67), mode, mode);
    entry = SzFile_ReadParam(1, path, 0, -1, 0, -1);
    if (entry == NULL) {
        return 0;
    }
    if (entry->size == 0 || (data = entry->data) == NULL) {
        return 0;
    }
    gSzView_pCamera = (s32)data;
    gSzView_wFrame = data->unkC;
    return 1;
}

/* Ends the camera system. */
void SzView_TermCamera(void) {

    if (gSzView_pCamera != 0) {
        SzMem_Free(gSzView_pCamera);
        gSzView_pCamera = 0;
    }
}

/* Runs the camera system for a frame. */
void SzView_ActCamera(void) {
    extern u16 gSzView_wFrame;
    s32 value;
    s32 handle;
    s32 hint = 0;

    if (gSzView_pCamera != 0) {
        if (SzPad_Check(0, 2, 4) != 0) {
            value = gSzView_wFrame - 1;
            gSzView_wFrame = (value > 0) ? value : 0;
        }
        if (SzPad_Check(0, 2, 8) != 0) {
            value = gSzView_wFrame + 1;
            gSzView_wFrame = (value < 1000) ? value : 1000;
        }
        if (SzPad_Check(0, 0, 0x10) != 0) {
            SzView_ReqCamera(0, 0, 8, gSzView_wFrame, 7, hint != 0 ? NULL : (void *)gSzView_pCamera);
        }
        if (SzPad_Check(0, 0, 0xA0) != 0) {
            value = SzBattle_InqEntry(0);
            handle = SzDuel_GetUnitModelID(value >> 8, value & 0xFF);
            SzModel_SetAnimIntr(handle, SzPad_Check(0, 0, 0x80) ? 5 : 2);
            SzView_ReqCamera(0, 0, 8, gSzView_wFrame, handle, hint != 0 ? NULL : (void *)gSzView_pCamera);
        }
    }
}

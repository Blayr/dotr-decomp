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
void lSzView_CalcInterpCameraMotion(void *out, void *motion, s32 frame, f32 fparg0) {
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
    u32 temp_a3;
    u32 temp_a1;
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
    temp_a2 = (Key_001FBE50 *)((u8 *)motion + var_a3 * 16);
    temp_v1 = var_a3 + 1;
    if (temp_v1 >= frame) {
        ((f32 *)out)[0] = temp_a2->value[0];
        ((f32 *)out)[1] = temp_a2->value[1];
        ((f32 *)out)[2] = temp_a2->value[2];
        return;
    }
    next = (Key_001FBE50 *)((u8 *)motion + temp_v1 * 16);
    temp_a1 = temp_a2->time;
    temp_a3 = next->time;
    temp_v0_3 = temp_a3 - temp_a1;
    var_f3 = (f32)temp_v0_3;
    var_f0 = (f32)temp_a3;
    var_f0_2 = (f32)temp_a1;
    weight = (var_f0 - fparg0) / var_f3;
    weight2 = (fparg0 - var_f0_2) / var_f3;
    ((f32 *)out)[0] = weight * temp_a2->value[0] + weight2 * next->value[0];
    ((f32 *)out)[1] = weight * temp_a2->value[1] + weight2 * next->value[1];
    ((f32 *)out)[2] = weight * temp_a2->value[2] + weight2 * next->value[2];
}

typedef struct Key_001FC050 {
    u32 time;
    f32 value;
} Key_001FC050;

/* One channel of a camera motion at frame `frame`, blended by `t`. */
f32 lSzView_CalcInterpCameraMotion1(u8 *channel, s32 frame, f32 fparg0) {
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
    temp_a2 = (Key_001FC050 *)(channel + var_v0);
    temp_v1 = var_a3 + 1;
    if (temp_v1 >= frame) {
        return temp_a2->value;
    }
    channel += temp_v1 * 8;
    temp_a1 = temp_a2->time;
    temp_a3 = *(u32 *)channel;
    temp_v0_3 = temp_a3 - temp_a1;
    var_f3 = (f32)temp_v0_3;
    var_f0 = (f32)temp_a3;
    var_f0_2 = (f32)temp_a1;
    weight = (var_f0 - fparg0) / var_f3;
    result = weight * temp_a2->value;
    weight = (fparg0 - var_f0_2) / var_f3;
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

/* Clears the two fades. */
void SzFade_Init(void) {
    Entry_0031C050 *entry;
    s32 count;

    entry = gSzFade_fl;
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

/* Starts fade `fade` (0 or 1): `in` (1) or out, `step` per frame up to `length`, in `color` (or black). */
s32 SzFade_Entry(s32 fade, s32 in, u8 step, u8 start, u8 length, void *color) {
    Entry_0031C050 *entry;

    entry = &gSzFade_fl[fade];
    if (entry->flag == 0) {
        return 0;
    }
    ((Value_001FCC70 *)((u8 *)entry + 7))->value = in;
    entry->pad0[4] = step;
    entry->lo = start;
    entry->hi = length;
    entry->flag = 0;
    entry->pad7b = 0;
    ((Flags_001FCC70 *)entry->pad8)->flag = 0;
    if (color != 0) {
        *(Color_001FCC70 *)entry->pad0 = *(Color_001FCC70 *)color;
    } else {
        entry->pad0[2] = 0;
        entry->pad0[1] = 0;
        entry->pad0[0] = 0;
        entry->pad0[3] = 0x80;
    }
    return 1;
}

/* Stops fade `fade`. */
s32 SzFade_Destroy(s32 fade) {
    Entry_0031C050 *temp_a2;

    temp_a2 = &gSzFade_fl[fade];
    temp_a2->flag = 1;
    return 1;
}

/* Draws and advances both fades. */
void SzFade_DispAll(void) {
    s32 i;

    i = 0;
    do {
        SzFade_Disp(i);
        i += 1;
    } while (i < 2);
}

typedef struct {
    s8 paused : 1;
    s8 unused : 7;
} Flags_001FCDE0;

/* Draws fade `fade` at its current level and advances it. */
s32 SzFade_Disp(s32 fade) {
    u8 color[4];
    Entry_0031C050 *entry;
    s32 next;
    u8 amount;

    if ((fade < 0) || (fade >= 2)) {
        return 0;
    }
    entry = &gSzFade_fl[fade];
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
    SzFade_Draw(0, (s32)color, 0xFFFFFF);
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

/* Draws a full-screen rectangle in colour `color` with alpha mode `alpha` at depth `z`. */
void SzFade_Draw(s32 alpha, s32 color, s32 z) {
    RhBase_SetVifPacketArea(SzFade_Draw_Pipe(RhBase_GetVifPacketArea(), alpha, color, z));
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

/* Fills a GIF tag. */
static inline void init_001FCF90(void *tag) {
    ((Header_001FCF90 *)tag)->flags = 6;
    ((Header_001FCF90 *)tag)->count = 3;
    ((Header_001FCF90 *)tag)->registers = 0x441;
    ((Header_001FCF90 *)tag)->reserved = 0;
}

/* Draws a full-screen rectangle in colour `color` with alpha mode `alpha` at depth `z`. */
s32 SzFade_Draw_Pipe(s32 cursor, s32 alpha, s32 color, s32 z) {
    Packet_001FCF90 packet;

    init_001FCF90((Header_001FCF90 *)packet.tag);
    ExAssignAlpha(&packet, ExGetAlphaVal(alpha));
    packet.color[0] = ((u8 *)color)[2];
    packet.color[1] = ((u8 *)color)[1];
    packet.color[2] = ((u8 *)color)[0];
    packet.color[3] = ((u8 *)color)[3];
    packet.q = 1.0f;
    packet.vertices[0].x = 0x6C00;
    packet.vertices[0].y = 0x7200;
    packet.vertices[0].z = (u32)z;
    packet.vertices[0].reserved = 0;
    packet.vertices[1].x = 0x9400;
    packet.vertices[1].y = 0x8E00;
    packet.vertices[1].z = (u32)z;
    packet.vertices[1].reserved = 0;
    return ExSortPrim_Pipe(cursor, (s32)&packet, 0, 0);
}

/* Makes fade `fade` stop by itself when it is done. */
s32 SzFade_SetKillFlag(s32 fade) {
    Entry_0031C050 *entry;

    if (fade < 0 || fade >= 2) {
        return 0;
    }
    entry = &gSzFade_fl[fade];
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

/* Pauses (`on`) or resumes fade `fade`. */
s32 SzFade_SetPauseFlag(s32 fade, s64 on) {
    Entry_0031C050 *temp_a2;

    if (fade < 0 || fade >= 2) {
        return 0;
    }
    temp_a2 = &gSzFade_fl[fade];
    if (temp_a2->flag != 0) {
        return 0;
    }
    ((Flags_001FD130 *) temp_a2->pad8)->enabled = (s8) on;
    return 1;
}

/* How many steps fade `fade` has left, or 0. */
s32 SzFade_GetRestCount(s32 fade) {
    Entry_0031C050 *e;

    if (fade < 0 || fade >= 2) {
        return -1;
    }
    e = &gSzFade_fl[fade];
    if (e->flag != 0) {
        return -1;
    }
    return e->hi - e->lo;
}

/* The steps a fade has left. */
static inline s32 calc_001FD220(s32 idx) {
    Entry_0031C050 *e;

    if (idx < 0 || idx >= 2) {
        return -1;
    }
    e = &gSzFade_fl[idx];
    if (e->flag) {
        return -1;
    }
    return e->hi - e->lo;
}

/* Whether fade `fade` is running. */
s32 SzFade_IsDoing(s32 fade) {
    s32 i;
    s32 want = fade ? 1 : 0;

    for (i = 0; i < 2; i++) {
        if (calc_001FD220(i) >= want) {
            return 1;
        }
    }
    return 0;
}

/* Clears the message system. */
void SzMsg_Initialize(void) {
    extern u8 textState[];

    RhMem_FillMemory((s8 *)textState, 0, 0x27C);
}

/* Starts the message system with palette `palette` at GS address `address`. */
s32 SzMsg_Init(s32 palette, s32 address) {
    s32 sp3C;

    RhBase_SetVifPacketArea(SzMsg_Init_Pipe(RhBase_GetVifPacketArea(), palette, address, &sp3C));
    return sp3C;
}

typedef struct State_001FD320 {
    s32 width;
    s32 height;
    s32 tw;
    s32 th;
    s32 cbp;
    s32 tbp;
    s32 cbpOffset;
    u8 pad1C[0x258];
    s32 unk274;
    u16 unk278;
} State_001FD320;

/* Starts the message system: the 640x384 text texture, its palettes at GS address `address`; the GS memory it took
   through `outSize`. */
s32 SzMsg_Init_Pipe(s32 packet, s32 palette, s32 address, s32 *outSize) {
    extern State_001FD320 textState;
    extern s32 D_002D19D0;
    extern u16 D_002D49D4[];
    extern s32 SzText_InitClutManage();
    extern s32 SzMsg_LoadClut_Pipe();
    State_001FD320 *state = &textState;
    s32 start;
    s32 i;
    s32 tw;
    s32 th;

    start = address;
    SzMsg_FreeAll();
    textState.width = 640;
    textState.height = 384;
    for (tw = 0; (1 << tw) < 640; tw++) {
    }
    for (th = 0; (1 << th) < 384; th++) {
    }
    state->tw = tw;
    state->th = th;
    state->cbp = SzText_GetClutGsAddr(3);
    if (state->cbp < 0) {
        address += SzText_InitClutManage(address, 1);
        state->cbp = SzText_GetClutGsAddr(3);
    }
    state->tbp = address;
    for (i = 0; i < 3; i++) {
        packet = SzMsg_LoadClut_Pipe(packet, i, state->cbp + i);
    }
    if (outSize != NULL) {
        *outSize = address + 0x1E0 - start;
    }
    state->cbpOffset = palette;
    state->unk274 = 0xFFFFFB;
    state->unk278 = D_002D49D4[D_002D19D0] & 0x1FFF;
    return packet;
}

/* Sets the depth messages are drawn at. */
void SzMsg_SetDefPrioZ(s32 z) {
    D_0031C2E4 = z;
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

/* Loads text palette `index` into GS memory at `address`. */
void SzMsg_LoadClut_Pipe(u64 *cursor, s32 index, s32 address) {
    extern void *RhMem_CopyMemory4(void *, void *, s32);
    extern u8 textAlphas[][16];
    extern u8 textColors[][16];
    Packet_001FD4C0 *packet = (Packet_001FD4C0 *)cursor;
    u8 colors[16][4];
    s32 i;
    u64 *end;
    s32 count;

    for (i = 0; i < 16; i++) {
        colors[i][0] = colors[i][1] = colors[i][2] = textColors[index][i];
        colors[i][3] = textAlphas[index][i];
    }

    cursor[1] = 0;
    cursor[0] = 0;
    ((Packet_001FD4C0 *)cursor)->header.flag = 0x10;
    cursor[2] = 4 | ((u64)0x10000000 << 32);
    cursor[3] = 0xE;
    cursor[4] = ((s64)address << 32) | ((u64)0x10000 << 32);
    cursor[5] = 0x50;
    cursor[6] = 0;
    cursor[7] = 0x51;
    cursor[8] = 8 | ((u64)2 << 32);
    cursor[9] = 0x52;
    cursor[10] = 0;
    cursor[11] = 0x53;
    cursor[12] = 0x8004 | ((u64)0x08000000 << 32);
    cursor[13] = 0;
    cursor += 14;
    end = RhMem_CopyMemory4(cursor, colors, 16);
    count = ((end - packet->words) >> 1) - 1;
    packet->header.count = count;
    packet->header.dma0 = 0x11000000;
    packet->header.dma1 = (count & 0xFFFF) | 0x51000000;
}

/* Renders message `msg` into text slot `slot` at (x, y) of the text texture. */
void SzMsg_LoadFont(s32 slot, s32 msg, s32 x, s32 y) {
    RhBase_SetVifPacketArea(SzMsg_LoadFont_Pipe(RhBase_GetVifPacketArea(), slot, msg, x, y));
}

typedef struct {
    u32 count : 8;
    u32 width : 12;
    u32 height : 11;
    s32 used : 1;
    s32 x;
    s32 y;
    s32 pixelWidth;
    s32 pixelHeight;
} Texture_001FD680;

typedef struct {
    s32 width;
    u8 pad[0x10];
    s32 tbp;
} Context_001FD680;

/* Renders message `msg` (the game's text) into text slot `slot` at (x, y) of the text texture, glyph by glyph. */
s32 SzMsg_LoadFont_Pipe(s32 cursorIn, s32 slot, s32 msg, s32 x, s32 y) {
    extern s32 D_002D19D0[];
    extern u16 D_002D49D4[];
    extern u8 D_002F8DEC[];
    extern Context_001FD680 textState;
    Context_001FD680 *context = &textState;
    u8 *glyphs[17][53];
    u8 runs[17][53];
    u16 indices[17][53];
    u16 counts[17];
    u16 advances[17];
    u16 lineCount;
    s64 *packet = (s64 *)cursorIn;
    Texture_001FD680 *texture;
    u16 *stream;
    u16 width;
    u16 height;
    u16 *count;
    u16 *advance;
    s32 n;
    s32 clearIndex;
    u16 *clearCount;
    u16 *clearAdvance;
    u8 *data;
    u8 *out;
    u16 maxCount;
    s32 pixelHeight;
    s32 maxWidth;
    s32 glyphIndex;
    u16 *nextId;
    u8 **next;
    s32 num;
    s32 offset;
    u16 *id;
    s32 outputRow;
    u8 **nextGlyph;
    s32 rowSize;
    u16 *nextCount;
    s32 bytes;
    u8 **lineGlyphs;
    s32 lineIndex;
    u8 *run;
    u8 **glyph;
    s32 outputGlyph;
    u16 currentAdvance;
    s32 pixelWidth;
    s32 rows;
    u8 *lineRuns;
    s64 dimensions;
    s64 coordinates;
    s32 length;

    texture = (Texture_001FD680 *)SzMsg_GetInfo(slot);
    stream = &D_002D49D4[D_002D19D0[msg]];
    width = 16;
    height = 16;
    lineCount = 0;
    if (texture == 0) {
        return cursorIn;
    }
    if (texture->used) {
        return cursorIn;
    }
    count = counts;
    advance = advances;
    clearIndex = 0;
    clearCount = count;
    clearAdvance = advance;
    do {
        clearIndex++;
        *clearCount++ = 0;
        *clearAdvance++ = 0;
    } while (clearIndex < 17);

    do {
        n = lSzMsg_FontTrace(stream, (char (*)[53])runs, (short (*)[53])indices, counts, advances, &lineCount);
        if (stream[n - 1] & 0x8000) {
            break;
        }
        stream += n;
    } while (1);

    lineCount++;
    lineGlyphs = glyphs[0];
    id = indices[0];
    maxWidth = 0;
    maxCount = maxWidth;
    lineIndex = 0;
    nextGlyph = lineGlyphs;
    nextCount = count;
    while (lineIndex < lineCount) {
        num = *nextCount;
        glyphIndex = 0;
        nextId = id;
        next = nextGlyph;
        goto glyph_test;
    glyph_loop:
        *next = D_002F8DEC + *nextId * 242;
        glyphIndex++;
        nextId++;
        next++;
    glyph_test:
        if (glyphIndex < num) {
            goto glyph_loop;
        }
        if ((u16)maxWidth < (currentAdvance = *advance)) {
            maxCount = *nextCount;
            maxWidth = (u16)currentAdvance;
        }
        id += 53;
        nextGlyph += 53;
        nextCount++;
        advance++;
        lineIndex++;
    }

    pixelHeight = (u16)(lineCount * 22);
    pixelWidth = (u16)maxWidth;
    while (pixelWidth > (u16)width) {
        width = (u16)(width * 2);
    }
    rows = (u16)pixelHeight;
    while (rows > (u16)height) {
        height = (u16)(height * 2);
    }

    dimensions = (s64)(u16)maxWidth | ((s64)(u16)pixelHeight << 32);
    texture->used = 1;
    texture->count = maxCount;
    texture->width = width;
    texture->height = height;
    texture->x = x;
    texture->y = y;
    texture->pixelWidth = pixelWidth;
    texture->pixelHeight = rows;

    packet[1] = 0;
    packet[0] = 0;
    ((u8 *)packet)[3] = 16;
    packet[2] = 4 | ((s64)0x10000000 << 32);
    packet[3] = 14;
    coordinates = ((s64)x << 32) | ((s64)y << 48);
    packet[4] = ((s64)context->tbp << 32) |
                      ((s64)(context->width >> 6) << 48) |
                      ((s64)0x14000000 << 32);
    packet[5] = 0x50;
    packet[6] = coordinates;
    packet[7] = 0x51;
    packet[8] = dimensions;
    packet[9] = 0x52;
    packet[10] = 0;
    packet[11] = 0x53;
    n = pixelWidth >> 1;
    packet[12] = (s64)((n * rows + 15) >> 4) |
                       (0x8000 | ((s64)0x08000000 << 32));
    out = (u8 *)(packet + 14);
    packet[13] = 0;
    lineRuns = runs[0];
    lineIndex = 0;
    while (lineIndex < lineCount) {
        outputRow = 0;
        do {
            rowSize = 0;
            outputGlyph = 0;
            run = lineRuns;
            glyph = lineGlyphs;
            while (outputGlyph < *count) {
                bytes = *run;
                offset = 0;
                if (0 < bytes) {
                    do {
                        *out++ = (*glyph)[offset++];
                    } while (offset < (s32)bytes);
                }
                rowSize += bytes;
                run++;
                outputGlyph++;
                *glyph += 11;
                glyph++;
            }
            goto padding_test;
        padding_loop:
            *out++ = 0;
            rowSize++;
        padding_test:
            if (rowSize < n) {
                goto padding_loop;
            }
            outputRow++;
        } while (outputRow < 22);
        lineRuns += 53;
        lineGlyphs += 53;
        count++;
        lineIndex++;
    }
    while ((s32)out % 16 != 0) {
        out++;
    }
    length = (((s64 *)out - packet) >> 1) - 1;
    *(u16 *)packet = length;
    ((s32 *)packet)[2] = 0x11000000;
    ((s32 *)packet)[3] = (u16)length | 0x51000000;
    return (s32)out;
}

struct DotrSlotTableEntry {
    unsigned int unknown_000 : 31;
    signed int flag : 1;
    int unknown_004[4];
};
typedef char DotrSlotTableEntrySizeMustBe20[(sizeof(struct DotrSlotTableEntry) == 20) ? 1 : -1];
struct DotrSlotTable {
    int words[7];
    struct DotrSlotTableEntry entries[30];
    int unknown_274;
    unsigned short unknown_278;
};
extern struct DotrSlotTable D_0031C070_1fdb90;
extern int D_002D19D0_1fdb90;
extern unsigned short D_002D49D4_1fdb90[];
/* Whether a character code is half width. */
static inline int narrow_p(unsigned short x) { return (x & 0x2000) ? 1 : 0; }

/* Lays out a message line by line: each character's width and code, and the line widths. */
int lSzMsg_FontTrace(unsigned short *p, char (*half)[53], short (*code)[53], unsigned short *cols, unsigned short *widths, unsigned short *line)
{
    struct DotrSlotTable *ml = &D_0031C070_1fdb90;
    unsigned short word = *p;
    unsigned short c = word & 0x1fff;
    unsigned char w = narrow_p(word) ? 12 : 22;
    int ret = 1;
    int n;
    int count;
    unsigned short *q;

    if (word & 0x4000) {
        word = *++p;
        count = c & 0x3f;
        q = &D_002D49D4_1fdb90[(&D_002D19D0_1fdb90)[word & 0x3fff]];
        q += (c >> 6) & 0x7f;
        while (count != 0) {
            n = lSzMsg_FontTrace(q, half, code, cols, widths, line);
            if (q[n - 1] & 0x8000) {
                break;
            }
            count -= n;
            q += n;
        }
        ret = 2;
    } else if (c == ml->unknown_278) {
        (*line)++;
    } else {
        widths[*line] += w;
        half[*line][cols[*line]] = w >> 1;
        code[*line][cols[*line]] = c;
        cols[*line]++;
    }
    return ret;
}

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

/* The texture rectangle a text slot uses. */
void lSzMsg_GetTexInfo(void *info, void *out) {
    extern TexInfo_001FDD70 textState;
    TexInfo_001FDD70 *texture = &textState;

    if (info != NULL) {
        ((Tex0_001FDD70 *)info)->TBP0 = texture->tbp;
        ((Tex0_001FDD70 *)info)->TBW = texture->width >> 6;
        ((Tex0_001FDD70 *)info)->PSM = 20;
        ((Tex0_001FDD70 *)info)->TW = texture->tw;
        ((Tex0_001FDD70 *)info)->TH = texture->th;
        ((Tex0_001FDD70 *)info)->TCC = 1;
        ((Tex0_001FDD70 *)info)->TFX = 0;
        ((Tex0_001FDD70 *)info)->CBP = texture->cbp + texture->cbpOffset;
        ((Tex0_001FDD70 *)info)->CPSM = 0;
        ((Tex0_001FDD70 *)info)->CSM = 0;
        ((Tex0_001FDD70 *)info)->CSA = 0;
        ((Tex0_001FDD70 *)info)->CLD = 1;
    }
    if (out != NULL) {
        ((Tex1_001FDD70 *)out)->LCM = 0;
        ((Tex1_001FDD70 *)out)->MXL = 0;
        ((Tex1_001FDD70 *)out)->MMAG = 0;
        ((Tex1_001FDD70 *)out)->MMIN = 0;
        ((Tex1_001FDD70 *)out)->MTBA = 0;
        ((Tex1_001FDD70 *)out)->L = 0;
        ((Tex1_001FDD70 *)out)->K = 0;
    }
}

typedef struct {
    u16 count;
    u16 flags;
    u32 padding;
    u64 registers;
} Tag_001FDFE0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Color_001FDFE0;

typedef struct {
    u64 u : 14;
    u64 pad0 : 2;
    u64 v : 14;
    u64 pad1 : 34;
} UV_001FDFE0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Vertex_001FDFE0;

typedef struct {
    u64 tag[2];
    Color_001FDFE0 color;
    u64 uv0;
    Vertex_001FDFE0 vertex0;
    u64 uv1;
    Vertex_001FDFE0 vertex1;
    u64 test;
    s64 texture0;
    s64 texture1;
    u64 clamp;
} Packet_001FDFE0;

typedef struct {
    s8 pad0[3];
    s8 unused : 7;
    s8 active : 1;
    s32 u;
    s32 v;
    s32 width;
    s32 height;
} Info_001FDFE0;

typedef struct {
    u8 pad[0x274];
    s32 depth;
} State_001FDFE0;

/* Sets a sprite corner's texture coordinates. */
static inline void set_uv_001FDFE0(UV_001FDFE0 *p, s32 u, s32 v) {
    p->u = u;
    p->v = v;
}

/* Draws text slot `slot` at (x, y) inside `rect`, in `color`. */
s32 SzMsg_DrawRect_Pipe(s32 out, s32 slot, s32 x, s32 y, s32 *rectIn, u8 *colorIn) {
    extern u8 D_00293078[];
    extern s32 textDefaultRect[];
    extern State_001FDFE0 textState;
    Packet_001FDFE0 packet __attribute__((aligned(8)));
    State_001FDFE0 *state = &textState;
    Info_001FDFE0 *info;
    s32 x0;
    s32 y0;
    s32 x1;
    s32 y1;
    s32 u0;
    s32 v0;
    s32 u1;
    s32 v1;
    s32 *rect = rectIn;
    u8 *color = colorIn;

    info = SzMsg_GetInfo(slot);
    if (info == NULL) {
        return out;
    }
    if (info->active == 0) {
        return out;
    }
    if (rect == NULL) {
        rect = textDefaultRect;
    }
    if (color == NULL) {
        color = D_00293078;
    }
    x0 = rect[0] + x;
    y0 = rect[1] + y;
    x1 = rect[2] + x0;
    y1 = rect[3] + y0;
    u0 = info->u;
    v0 = info->v;
    u1 = info->width + u0;
    v1 = info->height + v0;
    ((Tag_001FDFE0 *)packet.tag)->flags = 0x26;
    ((Tag_001FDFE0 *)packet.tag)->count = 5;
    ((Tag_001FDFE0 *)packet.tag)->registers = 0x42421;
    ((Tag_001FDFE0 *)packet.tag)->padding = 0;
    ((Tag_001FDFE0 *)packet.tag)->flags |= 0x800;
    ExAssignAlpha(packet.tag, 0x44 | ((s64)0x80 << 32));
    packet.color.r = color[2];
    packet.color.g = color[1];
    packet.color.b = color[0];
    packet.color.a = color[3];
    packet.color.q = 1.0f;
    packet.vertex0.x = x0 << 4;
    packet.vertex0.y = y0 << 4;
    packet.vertex0.z = state->depth;
    packet.vertex0.fog = 0;
    packet.vertex1.x = x1 << 4;
    packet.vertex1.y = y1 << 4;
    packet.vertex1.z = state->depth;
    packet.vertex1.fog = 0;
    set_uv_001FDFE0((UV_001FDFE0 *)&packet.uv0, (u0 << 4) + 8, (v0 << 4) + 8);
    set_uv_001FDFE0((UV_001FDFE0 *)&packet.uv1, (u1 << 4) + 8, (v1 << 4) + 8);
    lSzMsg_GetTexInfo(&packet.texture0, &packet.texture1);
    return ExSortPrim_Pipe(out, (s32)&packet, 0, 0);
}

typedef int DotrDrawWord;
struct DotrCursorPacketHeader {
    unsigned short unknown_00;
    unsigned short unknown_02;
    int unknown_04;
    long unknown_08;
};
int func_002086D0_b(struct DotrCursorPacketHeader *packet, long value);
DotrDrawWord func_00207650_b(DotrDrawWord cursor, void *packet, int a1, int a2);
extern unsigned char D_0031C070_1fe290[];
struct DotrSlotTableWords {
    int words[4];
};
extern struct DotrSlotTableWords D_002CFCD0_1fe290[];
struct DotrCursorSlotEntry {
    unsigned int unknown_000 : 31;
    signed int flag : 1;
    int unknown_004[4];
};
struct DotrCursorTex {
    long word;
};
extern struct DotrCursorSlotEntry *func_001FEAB0_b(int index);
struct DotrCursorSlotUv {
    unsigned short u : 14;
    unsigned short v : 14;
};
struct DotrCursorSlotXyz {
    unsigned long x : 16;
    unsigned long y : 16;
    unsigned long z : 24;
    unsigned long f : 8;
};
struct DotrCursorRectGVertex {
    unsigned char colour[4];
    float unknown_04;
    long uv;
    struct DotrCursorSlotXyz xyz;
};
struct DotrCursorRectGPacket {
    long header[2];
    struct DotrCursorRectGVertex vertex[4];
    long unknown_70;
    struct DotrCursorTex tex0;
    struct DotrCursorTex tex1;
    long unknown_88;
};
extern unsigned char D_00293080[];

/* Draws text slot `index` at (x, y) inside `rect` with a colour gradient. */
int SzMsg_DrawRectG_Pipe(int cursor, int index, int x, int y, void *rect_v, unsigned char *colour)
{
    struct DotrSlotTableWords * rect = rect_v;
    struct DotrCursorRectGPacket packet;
    int *state = (int *)D_0031C070_1fe290;
    struct DotrCursorSlotEntry *entry;
    int left, top, right, bottom;
    int u, v, u2, v2;

    entry = func_001FEAB0_b(index);
    if (entry == 0) {
        return cursor;
    }
    if (!entry->flag) {
        return cursor;
    }
    if (rect == 0) {
        rect = D_002CFCD0_1fe290;
    }
    if (colour == 0) {
        colour = D_00293080;
    }
    left = rect->words[0] + x;
    top = rect->words[1] + y;
    right = rect->words[2] + left;
    bottom = rect->words[3] + top;
    v = entry->unknown_004[1];
    u = entry->unknown_004[0];
    u2 = entry->unknown_004[2] + u;
    v2 = entry->unknown_004[3] + v;
    ((struct DotrCursorPacketHeader *)packet.header)->unknown_02 = 52;
    ((struct DotrCursorPacketHeader *)packet.header)->unknown_00 = 12;
    ((struct DotrCursorPacketHeader *)packet.header)->unknown_08 = 0x421421421421L;
    ((struct DotrCursorPacketHeader *)packet.header)->unknown_04 = 0;
    ((struct DotrCursorPacketHeader *)packet.header)->unknown_02 |= 0x800;
    func_002086D0_b((struct DotrCursorPacketHeader *)packet.header, 0x8000000044L);
    packet.vertex[0].colour[0] = colour[2];
    packet.vertex[0].colour[1] = colour[1];
    packet.vertex[0].colour[2] = colour[0];
    packet.vertex[0].colour[3] = colour[3];
    packet.vertex[0].unknown_04 = 1.0f;
    packet.vertex[1].colour[0] = colour[6];
    packet.vertex[1].colour[1] = colour[5];
    packet.vertex[1].colour[2] = colour[4];
    packet.vertex[1].colour[3] = colour[7];
    packet.vertex[1].unknown_04 = 1.0f;
    packet.vertex[2].colour[0] = colour[10];
    packet.vertex[2].colour[1] = colour[9];
    packet.vertex[2].colour[2] = colour[8];
    packet.vertex[2].colour[3] = colour[11];
    packet.vertex[2].unknown_04 = 1.0f;
    packet.vertex[3].colour[0] = colour[14];
    packet.vertex[3].colour[1] = colour[13];
    packet.vertex[3].colour[2] = colour[12];
    packet.vertex[3].colour[3] = colour[15];
    packet.vertex[3].unknown_04 = 1.0f;
    packet.vertex[0].xyz.x = left << 4;
    packet.vertex[0].xyz.y = top << 4;
    packet.vertex[0].xyz.z = state[157];
    packet.vertex[0].xyz.f = 0;
    packet.vertex[1].xyz.x = right << 4;
    packet.vertex[1].xyz.y = top << 4;
    packet.vertex[1].xyz.z = state[157];
    packet.vertex[1].xyz.f = 0;
    packet.vertex[2].xyz.x = left << 4;
    packet.vertex[2].xyz.y = bottom << 4;
    packet.vertex[2].xyz.z = state[157];
    packet.vertex[2].xyz.f = 0;
    packet.vertex[3].xyz.x = right << 4;
    packet.vertex[3].xyz.y = bottom << 4;
    packet.vertex[3].xyz.z = state[157];
    packet.vertex[3].xyz.f = 0;
    ((struct DotrCursorSlotUv *)&packet.vertex[0].uv)->u = (u << 4) + 8;
    ((struct DotrCursorSlotUv *)&packet.vertex[0].uv)->v = (v << 4) + 8;
    ((struct DotrCursorSlotUv *)&packet.vertex[1].uv)->u = (u2 << 4) + 8;
    ((struct DotrCursorSlotUv *)&packet.vertex[1].uv)->v = (v << 4) + 8;
    ((struct DotrCursorSlotUv *)&packet.vertex[2].uv)->u = (u << 4) + 8;
    ((struct DotrCursorSlotUv *)&packet.vertex[2].uv)->v = (v2 << 4) + 8;
    ((struct DotrCursorSlotUv *)&packet.vertex[3].uv)->u = (u2 << 4) + 8;
    ((struct DotrCursorSlotUv *)&packet.vertex[3].uv)->v = (v2 << 4) + 8;
    lSzMsg_GetTexInfo(&packet.tex0, &packet.tex1);
    return func_00207650_b(cursor, &packet, 0, 0);
}

typedef struct Rect_001FE660 {
    s32 x;
    s32 y;
    s32 w;
    s32 h;
} Rect_001FE660;

typedef s32 (*Draw_001FE660)(s32, s32, s64, s64, Rect_001FE660 *, s32);

/* Draws text slot `slot` at (x, y), scaled, through draw function `draw`. */
s32 SzMsg_DrawRatioX_Pipe(s32 packet, s32 slot, s64 x, s64 y, f32 scaleX, f32 scaleY, s32 color, void (*draw)(void)) {
    extern Rect_001FE660 textDefaultRect;
    Rect_001FE660 rect;
    s32 *info;

    info = SzMsg_GetInfo(slot);
    rect = textDefaultRect;
    if (info == NULL) {
        return packet;
    }
    rect.w = (s32)((f32)info[3] * scaleX);
    rect.h = (s32)((f32)info[4] * scaleY);
    return ((Draw_001FE660)draw)(packet, slot, x, y, &rect, color);
}

/* Draws text slot `slot` at (x, y). */
void SzMsg_DrawX(s32 slot, s32 x, s32 y, s32 arg3, s32 arg4) {
    RhBase_SetVifPacketArea(SzMsg_DrawX_Pipe(RhBase_GetVifPacketArea(), slot, x, y, arg3, arg4));
}

typedef struct Rect_001FE7D0 {
    s32 x;
    s32 y;
    s32 w;
    s32 h;
} Rect_001FE7D0;

typedef s32 (*Draw_001FE7D0)(s32, s32, s32, s32, Rect_001FE7D0 *, s32);

/* Draws text slot `slot` at (x, y), through draw function `draw`. */
s32 SzMsg_DrawX_Pipe(s32 packet, s32 slot, s32 x, s32 y, s32 color, s32 draw) {
    extern Rect_001FE7D0 textDefaultRect;
    Rect_001FE7D0 rect;
    s32 *info;

    info = SzMsg_GetInfo(slot);
    rect = textDefaultRect;
    if (info == NULL) {
        return packet;
    }
    rect.w = info[3];
    rect.h = info[4];
    return ((Draw_001FE7D0)draw)(packet, slot, x, y, &rect, color);
}

/* Draws a see-through glass panel. */
void SzMsg_DrawGlass(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    RhBase_SetVifPacketArea(SzMsg_DrawGlass_Pipe(RhBase_GetVifPacketArea(), arg0, arg1, arg2, arg3));
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

/* Fills a GIF tag. */
static inline void tag_001FE8F0(void *packet) {
    *(u16 *)((u8 *)packet + 2) = 6;
    *(u16 *)packet = 3;
    *(u64 *)((u8 *)packet + 8) = 0x441;
    *(u32 *)((u8 *)packet + 4) = 0;
}

/* Draws a see-through glass panel inside `rect` (or the default one), in `color`. */
s32 SzMsg_DrawGlass_Pipe(s32 out, s32 arg1, s32 arg2, s32 rectIn, s32 colorIn) {
    extern u8 D_00293088[];
    extern s32 textDefaultRect[];
    extern State_001FE8F0 textState;
    Packet_001FE8F0 packet;
    u8 *color = (u8 *)colorIn;
    State_001FE8F0 *state = &textState;
    s32 x0;
    s32 y0;
    s32 x1;
    s32 y1;
    s32 *rect = (s32 *)rectIn;

    if (rect == NULL) {
        rect = textDefaultRect;
    }
    if (color == NULL) {
        color = D_00293088;
    }
    x0 = rect[0] + arg1;
    y0 = rect[1] + arg2;
    x1 = rect[2] + x0;
    y1 = rect[3] + y0;
    tag_001FE8F0(&packet);
    ExAssignAlpha(&packet, 0x8000000044LL);
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
    return ExSortPrim_Pipe(out, (s32)&packet, 0, 0);
}

typedef struct Vec4_001FEA80 {
    f32 x, y, z, w;
} Vec4_001FEA80;

extern Vec4_001FEA80 textDefaultRect; /* original: gSzMsg_defRect */

/* The default text rectangle into `out`. */
void SzMsg_GetDefRect(void *out) {
    *(Vec4_001FEA80 *)out = textDefaultRect;
}

/* Text slot `slot`'s record (its rectangle in words 3 and 4), or NULL. */
void *SzMsg_GetInfo(s32 slot) {
    extern u8 textState[];
    u8 *data = textState;
    void *result;

    if (slot >= 0) {
        result = NULL;
        if (slot < 0x1E) {
            result = data + (slot * 0x14) + 0x1C;
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

extern Table_001FEAF0 textState; /* original: gSzMsg_ml */

/* Frees text slot `slot`. */
void SzMsg_Free(s32 slot) {
    Table_001FEAF0 *t = &textState;

    if (slot >= 0 && slot < 0x1E) {
        t->entries[slot].flag_001FEAF0 = 0;
    }
}

typedef struct {
    s8 pad0[3];
    s8 unused : 7;
    s8 active : 1;
    s8 pad4[16];
} Entry_001FEB40;

extern Entry_001FEB40 D_0031C08C[30];

/* Frees every text slot. */
void SzMsg_FreeAll(void) {
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

extern State_001FEB80 fileQueue; /* original: gSzFile_fl */
extern Entry36_001FEB80 D_00320370[];
extern Entry8_001FEB80 D_00322770[];

/* Clears the file read queue. */
void SzFile_Init(void) {
    State_001FEB80 *state;
    Entry8_001FEB80 *small;
    Entry36_001FEB80 *large;
    s32 count;

    state = &fileQueue;
    large = D_00320370;
    small = D_00322770;
    count = 0x100;
    RhMem_FillMemory((s8 *)&fileQueue, 0, 0x66A0);
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

/* Queues a read of file `path` to `address` (`size` bytes or -1 for all), calling `callback(request, ok)` with
   `callbackArg` when done. */
void SzFile_ReadRequest(s32 owner, s32 path, s32 address, s32 size, s32 callback, s64 callbackArg) {
    SzFile_ReadRequestParam(owner, 0, path, address, size, 0, -1, callback, callbackArg);
}

typedef struct Request_001FECB0 {
    u8 data[0x24];
} Request_001FECB0;

typedef struct Queue_001FECB0 {
    u8 pad0[0x4080];
    Request_001FECB0 requests[0x100];
    u8 pad1[0x20C];
    u16 head;
    u16 count;
} Queue_001FECB0;

/* Queues a read of `length` bytes from `offset` of file `path` (a name or a disc file number | 0x80000000) to
   `address`. Returns the request, or 0. */
s32 SzFile_ReadRequestParam(s32 owner, s32 type, s32 path, s32 address, s32 size, s32 offset, s32 length, s32 callback, s64 callbackArg) {
    Queue_001FECB0 *queue = (Queue_001FECB0 *)&fileQueue;
    Request_001FECB0 *request;

    if (path == 0) {
        return 0;
    }
    if (queue->count >= 0x100) {
        return 0;
    }
    request = &queue->requests[(queue->head + queue->count) % 0x100];
    if (lSzFile_SetReadRequestParam(request, owner, type, (void *)path, address, size, offset, length, callback, callbackArg) == 0) {
        return 0;
    }
    queue->count++;
    return (s32)request;
}

extern char *discFileMap[]; /* original: mapFile */
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

/* Fills a read request record. */
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

/* Fills a read request: finds the file (a card picture by number, a disc file, or a name), checks the sector
   alignment. */
s32 lSzFile_SetReadRequestParam(void *request, s32 owner, s32 type, void *fileName,
                 s32 address, s32 size, s32 offset, s32 readLength,
                 s32 callback, s32 callbackArg) {
    char buffer[128];
    Record_001FEDA0 *record = request;

    if (record == NULL) {
        return 0;
    }
    if (fileName == 0) {
        return 0;
    }
    if (getenv((s32)D_002D0638) != NULL) {
        if (!((u32)fileName & 0x80000000)) {
            s32 name;
            u32 i;
            s32 length;
            char **entry;
            s32 digit1;
            s32 digit2;
            s32 digit3;

            func_0019BDD8(buffer, (char *)fileName);
            if ((name = (s32)func_0019C478(buffer, '/')) != NULL ||
                (name = (s32)func_0019C478(buffer, '\\')) != NULL) {
                length = func_0019BEF0((char *)(name + 1));
                if (length >= 8 && owner == 0x1400 &&
                    (((char *)name)[1] == 'M' || ((char *)name)[1] == 'm') &&
                    (digit1 = ((char *)name)[2]) >= '0' && digit1 <= '9' &&
                    (digit2 = ((char *)name)[3]) >= '0' && digit2 <= '9' &&
                    (digit3 = ((char *)name)[4]) >= '0' && digit3 <= '9' &&
                    ((char *)name)[5] == '.' &&
                    (((char *)name)[6] == 'G' || ((char *)name)[6] == 'g') &&
                    (((char *)name)[7] == 'R' || ((char *)name)[7] == 'r') &&
                    (((char *)name)[8] == 'P' || ((char *)name)[8] == 'p')) {
                    offset += SzDuel_Xax2New(digit3 - '0' +
                                         ((digit1 - '0') * 100 +
                                          (digit2 - '0') * 10)) * 0x80800;
                    name = (s32)D_002D063D;
                    length = func_0019BEF0((char *)(name + 1));
                }
                entry = discFileMap;
                i = 0;
                do {
                    char *path = func_0019C478(*entry, '\\');
                    if (path != NULL && strncasecmp((char *)(name + 1), path + 1, length) == 0) {
                        fileName = (void *)(D_00293098[i * 4] | 0x80000000);
                        if (size < 0) {
                            size = D_002930A8[i * 8] << 11;
                        }
                        break;
                    }
                    i++;
                    entry += 8;
                } while (i < 97U);
            }
        }
    }
    if ((u32)fileName & 0x80000000) {
        if (size < 0) {
            return 0;
        }
        if (size > 0 && size % 2048 != 0) {
            return 0;
        }
        if (offset % 2048 != 0) {
            return 0;
        }
        if (readLength > 0 && readLength % 2048 != 0) {
            return 0;
        }
        record->file = NULL;
        record->discFlag = 1;
        record->id = (u32)fileName & 0x7FFFFFFF;
    } else {
        char *file = SzMem_StrDup((char *)fileName);
        record->file = file;
        if (file == NULL) {
            return 0;
        }
        lSzFile_StrNormalize((s8 *)record->file);
        record->discFlag = 0;
        record->id = 0;
    }
    initialize_001FEDA0(record, owner, type, address, size, offset, readLength, callback, callbackArg);
    return 1;
}

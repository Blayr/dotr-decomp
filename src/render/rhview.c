/* Views: view stack, sample Z, view-volume checks (RhView_*). */

#include "common.h"

typedef struct Entry_0020DDB0 {
    u8 pad0[0xC0];
    u8 unkC0[0x90];
    f32 centerX;
    f32 centerY;
    f32 unk158;
    f32 unk15C;
    f32 unk160;
    f32 width;
    f32 height;
    f32 unk16C;
    f32 farZ;
    f32 range;
    f32 unk178;
    f32 unk17C;
    f32 nearZ;
    u8 r;
    u8 g;
    u8 b;
    u8 a;
    u8 pad188[0x18];
} Entry_0020DDB0;

/* Starts the renderer's view: default screen, aspect, clip, fog and its stack. */
s32 RhView_Init(void) {
    extern s32 D_0032A294;
    extern Entry_0020DDB0 viewStack[];
    s32 width;
    s32 height;

    viewStackIndex = 0;
    D_0032A294 = 0;
    RhBase_GetScreenSize(&width, &height);
    viewStack[0].unk160 = 400.0f;
    viewStack[0].width = width;
    viewStack[0].height = height;
    viewStack[0].centerX = viewStack[0].width / 2.0f;
    viewStack[0].centerY = viewStack[0].height / 2.0f;
    viewStack[0].unk158 = 1.0f;
    viewStack[0].unk15C = 0.95f;
    viewStack[0].unk16C = 1.0f;
    viewStack[0].farZ = 10000.0f;
    viewStack[0].range = viewStack[0].farZ - 1000.0f;
    viewStack[0].unk178 = viewStack[0].farZ;
    viewStack[0].unk17C = 0.0f;
    viewStack[0].nearZ = 1000.0f;
    viewStack[0].a = 0xFF;
    viewStack[0].b = 0xFF;
    viewStack[0].g = 0xFF;
    viewStack[0].r = 0xFF;
    RhView_Reset(viewStack[0].unkC0);
    return 1;
}

/* Ends the renderer's view. */
s32 RhView_Term(void) {
    return 1;
}

typedef struct {
    __int128 data[9];
} Copy_0020DEF0;

extern u8 D_0032A360[];

/* The current view state into `out`. */
s32 RhView_GetCurView(void *out) {
    *(Copy_0020DEF0 *)out =
        *(Copy_0020DEF0 *)(D_0032A360 + viewStackIndex * 0x1A0);
    return 1;
}

typedef struct State_0020DF40 {
    u8 pad000[0x150];
    f32 field150;
    f32 field154;
    u8 pad158[8];
    f32 field160;
    f32 field164;
    f32 field168;
    u8 pad16C[0x34];
} State_0020DF40;

/* Sets the screen distance and the screen's centre and size. */
s32 RhView_SetScreen(f32 distance, f32 fparg1, f32 fparg2, f32 fparg3, f32 fparg4) {
    extern State_0020DF40 viewStack[];
    State_0020DF40 *state;

    state = &viewStack[viewStackIndex];
    state->field160 = distance;
    state->field164 = fparg1;
    state->field168 = fparg2;
    state->field150 = fparg3;
    state->field154 = fparg4;
    return 1;
}

typedef struct State_0020DF90 {
    u8 pad0[0x158];
    f32 field158;
    f32 field15C;
    u8 pad160[0x40];
} State_0020DF90;

/* Sets the aspect ratio (x, y). */
s32 RhView_SetAspect(f32 x, f32 y) {
    extern State_0020DF90 viewStack[];
    State_0020DF90 *state;

    state = &viewStack[viewStackIndex];
    state->field158 = x;
    state->field15C = y;
    return 1;
}

typedef struct {
    u8 pad_000[0x16C];
    f32 x;
    f32 y;
    u8 pad_174[0x2C];
} Entry_0020DFD0;

/* Sets the near and far clip depths. */
s32 RhView_SetClipZ(f32 near, f32 far) {
    extern Entry_0020DFD0 viewStack[];
    Entry_0020DFD0 *entry;

    entry = &viewStack[viewStackIndex];
    entry->x = near;
    entry->y = far;
    return 1;
}

typedef struct {
    u8 pad0[0x150];
    f32 x;
    f32 y;
    u8 pad158[0x48];
} Entry_0020E010;

extern s32 viewStackIndex; /* original: gRhView_nStackIndex */
extern Entry_0020E010 viewStack[]; /* original: gRhView_avl */

/* The screen centre. */
s32 RhView_GetScreenCenter(f32 *outX, f32 *outY) {
    Entry_0020E010 *e = &viewStack[viewStackIndex];

    *outX = e->x;
    *outY = e->y;
    return 1;
}

/* The screen distance. */
s32 RhView_GetScreenDist(f32 *out) {
    Entry_0020E010 *e = &viewStack[viewStackIndex];

    *out = *(f32 *)&e->pad158[8];
    return 1;
}

/* The near and far clip depths. */
s32 RhView_GetClipZ(f32 *outNear, f32 *outFar) {
    Entry_0020DFD0 *entry = (Entry_0020DFD0 *)&viewStack[viewStackIndex];

    *outNear = entry->x;
    *outFar = entry->y;
    return 1;
}

/* Sets the fog colour and its depth and height ranges. */
s32 RhView_SetFogParameter(void *colorIn, f32 nearZ, f32 farZ, f32 nearY, f32 farY) {
    typedef struct {
        u8 r;
        u8 g;
        u8 b;
        u8 a;
    } Color_0020E0D0;
    typedef struct {
        u8 pad[0x174];
        f32 x;
        f32 y;
        f32 z;
        f32 w;
        Color_0020E0D0 color;
        u8 pad188[0x18];
    } Entry_0020E0D0;
    Entry_0020E0D0 *entry;

    entry = (Entry_0020E0D0 *)&viewStack[viewStackIndex];
    entry->x = nearZ;
    entry->y = farZ;
    entry->z = nearY;
    entry->w = farY;
    entry->color = *(Color_0020E0D0 *)colorIn;
    return 1;
}

typedef struct Color_0020E130 {
    u8 r, g, b, a;
} Color_0020E130;

typedef struct Entry_0020E130 {
    u8 pad0[0x174];
    f32 values[4];
    Color_0020E130 color;
    u8 pad188[0x18];
} Entry_0020E130;

/* The fog ranges and colour. */
s32 RhView_GetFogParameter(f32 *outNearZ, f32 *outFarZ, f32 *outNearY, f32 *outFarY, u8 *outColor) {
    Entry_0020E130 *entry;

    entry = (Entry_0020E130 *)&viewStack[viewStackIndex];
    *outNearZ = entry->values[0];
    *outFarZ = entry->values[1];
    *outNearY = entry->values[2];
    *outFarY = entry->values[3];
    *(Color_0020E130 *)outColor = entry->color;
    return 1;
}

typedef struct {
    u8 pad[0x40];
    f32 vector40[4];
    f32 vector50[4];
    f32 vector60[4];
    f32 vector70[4];
    f32 vector80[4];
} State_0020E1A0;

/* Resets a view state to the defaults. */
s32 RhView_Reset(void *state) {
    if (state == NULL) {
        state = (u8 *)&viewStack[viewStackIndex] + 0xC0;
    }
    RhGeom_UnitMatrix(state);
    ((State_0020E1A0 *)state)->vector40[0] = 0.0f;
    ((State_0020E1A0 *)state)->vector40[1] = 0.0f;
    ((State_0020E1A0 *)state)->vector40[2] = 0.0f;
    ((State_0020E1A0 *)state)->vector40[3] = 1.0f;
    ((State_0020E1A0 *)state)->vector50[0] = 0.0f;
    ((State_0020E1A0 *)state)->vector50[1] = 0.0f;
    ((State_0020E1A0 *)state)->vector50[2] = -1.0f;
    ((State_0020E1A0 *)state)->vector50[3] = 0.0f;
    ((State_0020E1A0 *)state)->vector80[0] = 0.0f;
    ((State_0020E1A0 *)state)->vector60[0] = 0.0f;
    ((State_0020E1A0 *)state)->vector60[1] = 0.0f;
    ((State_0020E1A0 *)state)->vector60[2] = 0.0f;
    ((State_0020E1A0 *)state)->vector60[3] = 1.0f;
    ((State_0020E1A0 *)state)->vector70[0] = 0.0f;
    ((State_0020E1A0 *)state)->vector70[1] = 0.0f;
    ((State_0020E1A0 *)state)->vector70[2] = -1.0f;
    ((State_0020E1A0 *)state)->vector70[3] = 0.0f;
    ((State_0020E1A0 *)state)->vector80[1] = 0.0f;
    ((State_0020E1A0 *)state)->vector80[2] = 0.0f;
    ((State_0020E1A0 *)state)->vector80[3] = 0.0f;
    return 1;
}

/* Makes `view` the current view and builds its matrices. */
s32 RhView_Set(void *view) {
    typedef struct {
        u8 pad0[0x40];
        u8 unk40[0x80];
        u8 unkC0[0x90];
        f32 x;
        f32 y;
        u8 pad158[8];
        f32 radius;
        f32 width;
        f32 height;
        u8 pad16C[0x1C];
        f32 radius_squared;
        f32 width_squared;
        f32 height_squared;
        u8 pad194[0xC];
    } State_0020E260;
    State_0020E260 *state;

    state = (State_0020E260 *)&viewStack[viewStackIndex];
    RhMem_CopyMemory16(state->unkC0, view, 9);
    lRhView_ConstructMatrix();
    RhGeom_ResetMatrixStack();
    RhGeom_SetMatrix(state->unk40);
    state->radius_squared = 4186116.0f + state->radius * state->radius;
    state->width_squared = (state->width * state->width) / 4.0f + state->radius * state->radius;
    state->height_squared = (state->height * state->height) / 4.0f + state->radius * state->radius;
    RhGeom_GetMatrix(view);
    RhView_GetWorldViewMatrix(InvertView);
    RhGeom_InvertMatrix(InvertView, InvertView);
    return 1;
}

typedef struct State_0020E360 {
    u8 pad_000[0x40];
    f32 matrix[4][4];
    u8 pad_080[0xE0];
    f32 radius;
    f32 width;
    f32 height;
    u8 pad_16C[0x1C];
    f32 radius_squared;
    f32 width_squared;
    f32 height_squared;
    u8 pad_194[0xC];
} State_0020E360;

/* Changes the current view to `view` (and rebuilds its matrices). */
s32 RhView_Modify(void *view) {
    State_0020E360 *state;

    state = (State_0020E360 *)&viewStack[viewStackIndex];
    RhMem_CopyMemory16((u8 *)state + 0xC0, view, 9);
    lRhView_ConstructMatrix();
    RhGeom_SetMatrix(&state->matrix);
    RhMem_CopyMemory16(view, state->matrix, 4);
    state->radius_squared = 4186116.0f + state->radius * state->radius;
    state->width_squared = (state->width * state->width) / 4.0f +
                           state->radius * state->radius;
    state->height_squared = (state->height * state->height) / 4.0f +
                            state->radius * state->radius;
    RhView_GetWorldViewMatrix(InvertView);
    RhGeom_InvertMatrix(InvertView, InvertView);
    return 1;
}

typedef struct Copy_0020E460 {
    __int128 data[26];
} Copy_0020E460;

/* Saves the current view on the view stack. */
s32 RhView_PushStack(void) {
    extern u8 D_0032A440[];

    if (viewStackIndex + 1 >= 2) {
        return 0;
    }
    ((Copy_0020E460 *)D_0032A440)[viewStackIndex] = ((Copy_0020E460 *)viewStack)[viewStackIndex];
    viewStackIndex += 1;
    return 1;
}

/* Restores the view saved on the view stack. */
s32 RhView_PopStack(void) {
    if (viewStackIndex <= 0) {
        return 0;
    }
    viewStackIndex -= 1;
    return 1;
}

#ifndef GAME_H
/* The game translation unit already declares this array with its local type. */
extern unsigned char viewStack[]; /* original: gRhView_avl */
#endif

typedef struct Vec4_0020E520 {
    f32 x, y, z, w;
} Vec4_0020E520;

typedef struct State_0020E520 {
    Vec4_0020E520 point;
    Vec4_0020E520 normal;
    Vec4_0020E520 direction;
    Vec4_0020E520 displacement;
    f32 distance;
    s32 active;
} State_0020E520;

typedef struct Object_0020E520 {
    __int128 reserved0[4];
    Vec4_0020E520 point;
    Vec4_0020E520 direction;
    u8 reserved1[0x20];
    s32 angle;
    u8 reserved2[0xC];
} Object_0020E520;

typedef struct Block_0020E520 {
    __int128 data[26];
} Block_0020E520;

extern s32 D_0032A294;
extern u8 D_0032A440[];

/* Reflects a vector in a plane. */
static inline void reflect_0020E520(Vec4_0020E520 *v, Vec4_0020E520 *normal) {
    f32 twiceDot = 2.0f * (normal->x * v->x + normal->y * v->y + normal->z * v->z);
    v->x = twiceDot * normal->x - v->x;
    v->y = twiceDot * normal->y - v->y;
    v->z = twiceDot * normal->z - v->z;
}

/* Saves the view and mirrors it in the plane through `point` with `normal` (for fake reflections). */
s32 RhView_PushFakeMirror(f32 *point, f32 *normal, void *output) {
    extern State_0020E520 fakeMirrorSaved;
    extern s32 func_001A22C0(f32);
    State_0020E520 *state = &fakeMirrorSaved;
    Object_0020E520 *original = (Object_0020E520 *)D_0032A360;
    u8 scratch[0xA0 + 0xF];
    Vec4_0020E520 *up;
    f32 *cross;
    void *matrix;
    void *inverse;
    Object_0020E520 *object = (Object_0020E520 *)output;

    up = (Vec4_0020E520 *)(((u32)scratch + 0xF) & ~0xF);
    up->x = 0.0f;
    up->y = 1.0f;
    up->z = 0.0f;
    cross = (f32 *)((u8 *)up + 0x10);
    matrix = (u8 *)cross + 0x40;
    up->w = 0.0f;
    inverse = (u8 *)matrix + 0x40;
    if (D_0032A294 != 0) {
        return 0;
    }
    *object = *original;
    state->point = *(Vec4_0020E520 *)point;
    state->normal = *(Vec4_0020E520 *)normal;
    state->direction.x = -original->direction.x;
    state->direction.y = -original->direction.y;
    state->direction.z = -original->direction.z;
    state->displacement.x = original->point.x - state->point.x;
    state->displacement.y = original->point.y - state->point.y;
    state->displacement.z = original->point.z - state->point.z;
    state->distance = RhGeom_GetVectorScalor(&state->displacement.x);
    RhGeom_NormalizeVector(&state->normal.x);
    RhGeom_NormalizeVector(&state->direction.x);
    RhGeom_NormalizeVector(&state->displacement.x);
    reflect_0020E520(&state->direction, &state->normal);
    reflect_0020E520(&state->displacement, &state->normal);
    object->direction = state->direction;
    object->point.x = point[0] - state->displacement.x * state->distance;
    object->point.y = point[1] - state->displacement.y * state->distance;
    object->point.z = point[2] - state->displacement.z * state->distance;
    object->point.w = 0.0f;
    RhView_GetWorldViewMatrix(matrix);
    RhGeom_InvertMatrix(inverse, matrix);
    RhGeom_MulMatrixVector(up, inverse, up);
    reflect_0020E520(up, &state->normal);
    RhGeom_OuterProduct(cross, (f32 *)up, &object->direction.x);
    RhGeom_CreateCameraMatrix2(matrix, &object->point, &object->direction, 0);
    RhGeom_MulMatrixVector(cross, matrix, cross);
    object->angle = (s32)func_001A22C0(65536.0f * (func_001A6C18(cross[1], cross[0]) / 6.2831855f)) + 0x8000;
    if (viewStackIndex + 1 < 2) {
        ((Block_0020E520 *)D_0032A440)[viewStackIndex] = ((Block_0020E520 *)viewStack)[viewStackIndex];
        viewStackIndex++;
    }
    state->active = 1;
    return 1;
}

typedef struct {
    u8 padding[0x44];
    s32 ready;
} State_0020E970;

typedef struct {
    __int128 data[9];
} Buffer_0020E970;

extern State_0020E970 fakeMirrorSaved; /* original: gRhView_FakeMirror */

/* Restores the view after a fake mirror. */
s32 RhView_PopFakeMirror(void *saved) {
    State_0020E970 *state = &fakeMirrorSaved;

    if (D_0032A294 == 0) {
        return 0;
    }
    if (viewStackIndex > 0) {
        viewStackIndex -= 1;
    }
    state->ready = 0;
    *(Buffer_0020E970 *)saved = *(Buffer_0020E970 *)D_0032A360;
    return 1;
}

#ifndef GAME_H
/* The game translation unit already declares this array with its local type. */
extern unsigned char viewStack[][0x1A0]; /* original: gRhView_avl */
#endif

typedef struct Object_0020E9F0 {
    u8 unk0[0x40];
    f32 matrix40[16];
    f32 matrix80[16];
    u8 unkC0[0x80];
    s32 unk140;
    u8 unk144[0xC];
    f32 unk150;
    f32 unk154;
    f32 unk158;
    f32 unk15C;
    f32 unk160;
    f32 unk164;
    f32 unk168;
    f32 unk16C;
    f32 unk170;
    u8 unk174[0x2C];
} Object_0020E9F0;

/* Builds the current view's world-view, view-screen and world-screen matrices. */
s32 lRhView_ConstructMatrix(void) {
    s32 sp50;
    s32 sp54;
    s32 sp58;
    s32 sp5C;
    f32 temp_f20;
    f32 temp_f21;
    Object_0020E9F0 *view;
    u8 *temp_s1;

    view = (Object_0020E9F0 *)&viewStack[viewStackIndex];
    temp_s1 = (u8 *) view + 0xC0;
    RhBase_GetScreenCenter(&sp50, &sp54);
    temp_f20 = ((f32) sp50 + view->unk150) - (view->unk164 / 2.0f);
    temp_f21 = ((f32) sp54 + view->unk154) - (view->unk168 / 2.0f);
    RhBase_GetZMinMax(&sp58, &sp5C);
    RhGeom_CreateCameraMatrix2(view->matrix40, temp_s1 + 0x40, temp_s1 + 0x50, *(s32 *) (temp_s1 + 0x80));
    RhGeom_GetScreenMatrix(view->matrix80, view->unk160, view->unk158, view->unk15C * RhBase_GetAspectY(NULL), temp_f20, temp_f21, (f32) sp58, (f32) sp5C, view->unk16C, 2.0f * view->unk170);
    RhMem_CopyMemory16(view, view->matrix80, 4);
    RhGeom_MulMatrix((s32) view, view->matrix40);
    RhMem_CopyMemory16(temp_s1, view, 4);
    return 1;
}

typedef struct {
    s32 words[16];
} Block_0020EB40;

/* The current world-to-screen matrix into `out`. */
void RhView_GetWorldScreenMatrix(void *out) {
    *(Block_0020EB40 *)out = *(Block_0020EB40 *)&viewStack[viewStackIndex];
}

typedef struct {
    s32 words[16];
} Block_0020EBA0;

extern u8 D_0032A2E0[][0x1A0];

/* The current world-to-view matrix into `out`. */
void RhView_GetWorldViewMatrix(void *out) {
    *(Block_0020EBA0 *)out = *(Block_0020EBA0 *)D_0032A2E0[viewStackIndex];
}

typedef struct {
    s32 words[16];
} Block_0020EC00;

typedef struct {
    Block_0020EC00 block;
    u8 padding[0x160];
} Entry_0020EC00;

extern Entry_0020EC00 D_0032A320[];

/* The current view-to-screen matrix into `dst`. */
void RhView_GetViewScreenMatrix(void *dst) {
    *(Block_0020EC00 *)dst = D_0032A320[viewStackIndex].block;
}

/* Sends the current view's matrices and clip values to VU1. */
s32 RhView_SendViewParameters(s32 packet) {
    u8 matrix_storage[0x4F];
    u8 *matrix;
    u8 *item;
    void *result;

    matrix = (u8 *)(((u32)matrix_storage + 0xF) & ~0xF);
    item = (u8 *)&viewStack[viewStackIndex];
    result = RhVu1Mac_SetViewScreenMatrix((void *)packet, item + 0x80);
    RhGeom_InvertMatrix(matrix, item);
    return (s32)RhVu1Mac_SetFogParameterEx(
        RhBase_SetFogColor(
            RhVu1Mac_SetClipParameter(RhVu1Mac_SetScreenWorldMatrix(result, matrix), 1,
                *(f32 *)(item + 0x160), *(f32 *)(item + 0x16C),
                *(f32 *)(item + 0x170)),
            item + 0x184),
        *(f32 *)(item + 0x174), *(f32 *)(item + 0x178),
        *(f32 *)(item + 0x17C), *(f32 *)(item + 0x180));
}

typedef struct {
    f32 x, y, z, w;
} Vec4_0020ED30;

/* The GS depth of point `point` (moved by `bias`). */
void RhView_GetSampleZ(void *point, f32 bias) {
    u8 buffer[31];
    Vec4_0020ED30 *vector;
    void *matrix;

    matrix = (u8 *)&viewStack[viewStackIndex] + 0x80;
    vector = (Vec4_0020ED30 *) (((u32) buffer + 15) & ~15);
    *vector = *(Vec4_0020ED30 *) point;
    vector->z -= bias;
    RhGeom_MulMatrixVector(vector, matrix, vector);
    func_001A23B0(vector->z / vector->w);
}

typedef __int128 DotrViewWord128;
struct DotrViewVector {
    float x, y, z;
    float unknown_w;
};
struct DotrViewQuad {
    unsigned char unknown_0;
    unsigned char unknown_1;
    unsigned char unknown_2;
    unsigned char unknown_3;
};
struct DotrViewBlock {
    DotrViewWord128 unknown_words[9];
};
struct DotrViewMatrix {
    float unknown_values[16];
};
struct DotrViewEntry {
    struct DotrViewMatrix unknown_000;
    struct DotrViewMatrix unknown_040;
    struct DotrViewMatrix unknown_080;
    struct DotrViewBlock unknown_0c0;
    float unknown_150;
    float unknown_154;
    float unknown_158;
    float unknown_15c;
    float unknown_160;
    float unknown_164;
    float unknown_168;
    float unknown_16c;
    float unknown_170;
    float unknown_174;
    float unknown_178;
    float unknown_17c;
    float unknown_180;
    struct DotrViewQuad unknown_184;
    unsigned char unknown_188[0x18];
};
typedef char DotrViewEntryMustBe1a0[(sizeof(struct DotrViewEntry) == 0x1a0) ? 1 : -1];
extern struct DotrViewEntry D_0032A2A0_20ede0[];
extern int D_0032A240_b[];
extern struct DotrViewVector pntDst;
#define DOTR_VIEW_SIDE(x, n, cross, outside) \
    { \
        float d = (x); \
        float q = d * d / (n); \
        if (d < 0.0f) { \
            if (q >= rr) { \
                return outside; \
            } \
            cross; \
        } else if (q <= rr) { \
            cross; \
        } \
    }

/* Whether a sphere at `centre` of `radius` is (partly) inside the view. */
int RhView_CheckViewVolume(void *centre_v, float radius)
{
    struct DotrViewVector * centre = centre_v;
    float sx;
    float rr;
    float z;
    float sy;
    float nn;
    int flags;
    float ny;
    float h;
    struct DotrViewEntry *e;
    float dist;
    float nx;
    float hy;
    float hx;

    flags = 0;
    e = &D_0032A2A0_20ede0[D_0032A240_b[0]];
    centre->unknown_w = 1.0f;
    RhGeom_MulMatrixVector(&pntDst, 0, centre);
    z = pntDst.z;
    if (e->unknown_16c > z + radius) {
        return 4;
    }
    if (e->unknown_16c > z - radius) {
        flags = 4;
    }
    if (e->unknown_170 < z - radius) {
        return 4;
    }
    if (e->unknown_170 < z + radius) {
        flags = 4;
    }
    sx = e->unknown_164 * (1.0f / e->unknown_158);
    sy = e->unknown_168 * (1.0f / e->unknown_15c);
    dist = e->unknown_160;
    nn = *(float *)&e->unknown_188[0];
    ny = dist * pntDst.y;
    h = 2046.0f * z;
    rr = radius * radius;
    DOTR_VIEW_SIDE(h - ny, nn, flags = 6, 4)
    DOTR_VIEW_SIDE(h + ny, nn, flags = 6, 4)
    nx = dist * pntDst.x;
    DOTR_VIEW_SIDE(h - nx, nn, flags = 6, 4)
    DOTR_VIEW_SIDE(h + nx, nn, flags = 6, 4)
    nn = *(float *)&e->unknown_188[8];
    hy = z * sy / 2.0f;
    DOTR_VIEW_SIDE(hy - ny, nn, flags |= 2, flags | 2)
    DOTR_VIEW_SIDE(hy + ny, nn, flags |= 2, flags | 2)
    hx = z * sx / 2.0f;
    nn = *(float *)&e->unknown_188[4];
    DOTR_VIEW_SIDE(hx - nx, nn, flags |= 2, flags | 2)
    DOTR_VIEW_SIDE(hx + nx, nn, flags |= 2, flags | 2)
    return flags | 1;
}
#undef DOTR_VIEW_SIDE

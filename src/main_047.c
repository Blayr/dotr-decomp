#include "common.h"

typedef struct {
    u16 count;
    u16 flags;
    u32 padding;
    u64 registers;
} Tag_001E4570;

typedef struct {
    u8 texture;
    u8 padding;
    u16 left;
    u16 top;
    u16 right;
    u16 bottom;
} Texture_001E4570;

typedef struct {
    u64 u : 14;
    u64 pad0 : 2;
    u64 v : 14;
    u64 pad1 : 34;
} UV_001E4570;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Vertex_001E4570;

typedef struct {
    u64 uv;
    Vertex_001E4570 xyz;
} Corner_001E4570;

typedef struct {
    u64 tag[2];
    u8 r, g, b, a;
    f32 q;
    Corner_001E4570 corners[4];
    u64 extra[4];
} Packet_001E4570;

typedef struct {
    f32 v[8][4];
} Quad_001E4570;

typedef struct {
    s32 v[4];
} Rotation_001E4570;

typedef struct {
    f32 m[4][4];
} Matrix_001E4570;

typedef struct {
    u8 pad000[0x6A0];
    void *textures[16];
    u8 pad6E0[0x578];
    s32 depth;
} State_001E4570;

static inline s32 abs_001E4570(s32 value) {
    return value >= 0 ? value : -value;
}

void lSzDuel_OpenHandCursor_Pipe(s32 packet, s32 angle, s32 x, s32 y) {
    extern Quad_001E4570 D_00291600;
    extern Rotation_001E4570 D_00291680;
    extern u8 D_00290814[];
    extern u8 D_0029081E[];
    extern void RhGeom_MulMatrixVectorArray(void *, s32, void *, s32);
    State_001E4570 *state;
    Texture_001E4570 *first;
    Texture_001E4570 *second;
    s32 originX;
    s32 originY;
    s32 halfWidth;
    s32 halfHeight;
    s32 width;
    s32 height;
    s32 du;
    s32 dv;
    s32 turn;
    Quad_001E4570 corners;
    Rotation_001E4570 rotation;
    Matrix_001E4570 matrix;
    Packet_001E4570 sprite __attribute__((aligned(8)));

    state = (State_001E4570 *)D_00317490.b;
    first = (Texture_001E4570 *)D_00290814;
    second = (Texture_001E4570 *)D_0029081E;
    halfWidth = abs_001E4570(first->right - first->left) >> 1;
    halfHeight = abs_001E4570(first->bottom - first->top) >> 1;
    width = abs_001E4570(second->right - second->left);
    height = abs_001E4570(second->bottom - second->top);
    corners = D_00291600;
    corners.v[0][0] = -(f32)halfWidth;
    corners.v[0][1] = -(f32)halfHeight;
    corners.v[1][0] = (f32)halfWidth;
    corners.v[1][1] = -(f32)halfHeight;
    corners.v[2][0] = -(f32)halfWidth;
    corners.v[2][1] = (f32)halfHeight;
    corners.v[3][0] = (f32)halfWidth;
    corners.v[3][1] = (f32)halfHeight;
    corners.v[4][0] = (f32)-halfWidth;
    corners.v[4][1] = (f32)-halfHeight;
    corners.v[5][0] = (f32)(width - halfWidth);
    corners.v[5][1] = (f32)-halfHeight;
    corners.v[6][0] = (f32)-halfWidth;
    corners.v[6][1] = (f32)(height - halfHeight);
    corners.v[7][0] = (f32)(width - halfWidth);
    corners.v[7][1] = (f32)(height - halfHeight);
    turn = (angle + 0x10000) % 0x10000;
    originY = y + 0x800;
    rotation = D_00291680;
    originX = x + 0x800;
    rotation.v[2] = (turn << 16) >> 8;
    dv = du = 8;
    switch (turn >> 14) {
    case 1:
        dv = -8;
        break;
    case 2:
        dv = du = -8;
        break;
    case 3:
        du = -8;
        break;
    }
    RhGeom_GetRotXYZMatrix(&matrix, &rotation);
    RhGeom_PushMatrix((s32)&matrix);
    RhGeom_MulMatrixVectorArray((void *)0x70000000, 0, &corners, 8);
    RhGeom_PopMatrix();
    ((Tag_001E4570 *)sprite.tag)->flags = 0x24;
    ((Tag_001E4570 *)sprite.tag)->count = 9;
    ((Tag_001E4570 *)sprite.tag)->registers = 0x424242421ULL;
    ((Tag_001E4570 *)sprite.tag)->padding = 0;
    ((Tag_001E4570 *)sprite.tag)->flags |= 0x800;
    ExAssignAlpha(&sprite, 0x8000000044ULL);
    sprite.r = 0x80;
    sprite.g = 0x80;
    sprite.b = 0x80;
    sprite.a = 0x80;
    sprite.q = 1.0f;
    sprite.corners[0].xyz.z = state->depth;
    sprite.corners[0].xyz.fog = 0;
    sprite.corners[1].xyz.z = state->depth;
    sprite.corners[1].xyz.fog = 0;
    sprite.corners[2].xyz.z = state->depth;
    sprite.corners[2].xyz.fog = 0;
    sprite.corners[3].xyz.z = state->depth;
    sprite.corners[3].xyz.fog = 0;
    ExAssignTexture(&sprite, state->textures[first->texture], 0);
    ((UV_001E4570 *)&sprite.corners[0].uv)->u = (first->left << 4) + du;
    ((UV_001E4570 *)&sprite.corners[0].uv)->v = (first->top << 4) + dv;
    ((UV_001E4570 *)&sprite.corners[1].uv)->u = (first->right << 4) - du;
    ((UV_001E4570 *)&sprite.corners[1].uv)->v = (first->top << 4) + dv;
    ((UV_001E4570 *)&sprite.corners[2].uv)->u = (first->left << 4) + du;
    ((UV_001E4570 *)&sprite.corners[2].uv)->v = (first->bottom << 4) - dv;
    ((UV_001E4570 *)&sprite.corners[3].uv)->u = (first->right << 4) - du;
    ((UV_001E4570 *)&sprite.corners[3].uv)->v = (first->bottom << 4) - dv;
    sprite.corners[0].xyz.x = (originX << 4) + (s32)(16.0f * ((f32 *)0x70000000)[0]);
    sprite.corners[0].xyz.y = (originY << 4) + (s32)(16.0f * ((f32 *)0x70000000)[1]);
    sprite.corners[1].xyz.x = (originX << 4) + (s32)(16.0f * ((f32 *)0x70000000)[4]);
    sprite.corners[1].xyz.y = (originY << 4) + (s32)(16.0f * ((f32 *)0x70000000)[5]);
    sprite.corners[2].xyz.x = (originX << 4) + (s32)(16.0f * ((f32 *)0x70000000)[8]);
    sprite.corners[2].xyz.y = (originY << 4) + (s32)(16.0f * ((f32 *)0x70000000)[9]);
    sprite.corners[3].xyz.x = (originX << 4) + (s32)(16.0f * ((f32 *)0x70000000)[12]);
    sprite.corners[3].xyz.y = (originY << 4) + (s32)(16.0f * ((f32 *)0x70000000)[13]);
    packet = ExSortPrim_Pipe(packet, (s32)&sprite, 0, 0);
    ExAssignTexture(&sprite, state->textures[second->texture], 0);
    ((UV_001E4570 *)&sprite.corners[0].uv)->u = (second->left << 4) + du;
    ((UV_001E4570 *)&sprite.corners[0].uv)->v = (second->top << 4) + dv;
    ((UV_001E4570 *)&sprite.corners[1].uv)->u = (second->right << 4) - du;
    ((UV_001E4570 *)&sprite.corners[1].uv)->v = (second->top << 4) + dv;
    ((UV_001E4570 *)&sprite.corners[2].uv)->u = (second->left << 4) + du;
    ((UV_001E4570 *)&sprite.corners[2].uv)->v = (second->bottom << 4) - dv;
    ((UV_001E4570 *)&sprite.corners[3].uv)->u = (second->right << 4) - du;
    ((UV_001E4570 *)&sprite.corners[3].uv)->v = (second->bottom << 4) - dv;
    sprite.corners[0].xyz.x = (originX << 4) + (s32)(16.0f * ((f32 *)0x70000000)[16]);
    sprite.corners[0].xyz.y = (originY << 4) + (s32)(16.0f * ((f32 *)0x70000000)[17]);
    sprite.corners[1].xyz.x = (originX << 4) + (s32)(16.0f * ((f32 *)0x70000000)[20]);
    sprite.corners[1].xyz.y = (originY << 4) + (s32)(16.0f * ((f32 *)0x70000000)[21]);
    sprite.corners[2].xyz.x = (originX << 4) + (s32)(16.0f * ((f32 *)0x70000000)[24]);
    sprite.corners[2].xyz.y = (originY << 4) + (s32)(16.0f * ((f32 *)0x70000000)[25]);
    sprite.corners[3].xyz.x = (originX << 4) + (s32)(16.0f * ((f32 *)0x70000000)[28]);
    sprite.corners[3].xyz.y = (originY << 4) + (s32)(16.0f * ((f32 *)0x70000000)[29]);
    ExSortPrim_Pipe(packet, (s32)&sprite, 0, 0);
}

void SzDuel_CloseHandCursor(void) {
    D_00318144 = 0x18;
}

typedef struct {
    s8 pad0 : 5;
    s8 flag : 1;
    s8 pad1 : 2;
} Flags;

extern Flags D_003181F7;

void SzDuel_SetIgnoreJudge(s64 arg0) {
    D_003181F7.flag = arg0;
}

typedef struct {
    s32 entries[2];
    s32 count;
} State_001E4E90;

void SzBattle_Initialize(void) {
    extern State_001E4E90 D_0031AB88;
    State_001E4E90 *state = &D_0031AB88;
    s32 i;

    RhMem_FillMemory((s8 *)&D_0031AB88, 0, 0xC);
    i = 0;
    do {
        state->entries[i] = -1;
        i++;
    } while (i < 2);
    state->count = 0;
}

typedef struct Vec3_001E4F00 {
    f32 x, y, z;
} Vec3_001E4F00;

void SzBattle_Init(s32 arg0) {
    extern u8 D_00291690[];
    extern s32 D_00292168;
    extern s32 D_00292170[];
    extern s32 D_00292174[];
    extern Vec3_001E4F00 D_002921A0;
    extern Vec3_001E4F00 D_002921B0;
    extern char D_002CF730[];
    extern char D_002CF746[];
    extern s32 D_0031AB88[];
    extern s32 SzFile_ReadRequestParam(s32, s32, char *, s32, s32, s32, s32, void *, s64);
    s32 * state;
    s32 begin;
    f32 * vec20;
    s32 j;
    f32 * range;
    f32 * vecC;
    s32 size;
    f32 * vecB8;
    char filename[128];
    s32 i;
    s64 enabled;
    u8 * base;

    state = D_0031AB88;
    base = D_00291690 + arg0 * 0xC0;
    vecC = (f32 *)(base + 0xC);
    vec20 = (f32 *)(base + 0x20);
    range = (f32 *)(base + 0xB0);
    vecB8 = (f32 *)(base + 0xB8);
    if (arg0 == 4) {
        enabled = 0;
    } else {
        enabled = 1;
    }
    SzView_SetStraightLight(0, 9, 1);
    i = 0;
    do {
        SzModel_SetDrawFlag(i, 0);
        i += 1;
    } while (i < 0x54);
    i = 0;
    do {
        SzModel_SetDrawFlag(i + 8, 1);
        i += 1;
    } while (i < 0xC);
    i = 0;
    do {
        SzModel_SetDrawFlag(i + 7, 1);
        i += 1;
    } while (i <= 0);
    SzEffect_SetFogColorForMonster((s32) vecB8);
    SzEffect_SetFogColorForBattle((s32) vecB8);
    SzEffect_SetFogParamZForMonster(0);
    SzEffect_SetFogParamZForBattle(0);
    if (range[0] == range[1]) {
        SzEffect_SetFogParamYForMonster(0);
        SzEffect_SetFogParamYForBattle(0);
    } else {
        SzEffect_SetFogParamYForMonster((s32) range);
        SzEffect_SetFogParamYForBattle((s32) range);
    }
    SzEffect_SetStraightLightForMonster((s32) vec20);
    SzEffect_SetStraightLightForBattle((s32) vec20);
    SzEffect_SetPointLightForMonster(0);
    SzEffect_SetPointLightForBattle(0);
    SzEffect_SetIntensityForMonster((s32) vecC);
    SzEffect_SetIntensityForBattle((s32) base);
    SzEffect_SetBlackOutForMonster(0x80);
    SzEffect_SetBlackOutForBattle(0x80);
    j = 0;
    do {
        SzModel_SetFogFlag(j + 8, enabled);
        j += 1;
    } while (j < 0xC);
    if (arg0 == 4) {
        Vec3_001E4F00 position = D_002921A0;
        Vec3_001E4F00 other;
        position.x = ((f32 *)base)[0];
        position.y = ((f32 *)base)[1];
        other = D_002921B0;
        SzModel_SetIntensity(8, &position.x);
        SzModel_SetFogFlag(9, 1);
        SzModel_SetIntensity(0xC, &other.x);
    }
    if (arg0 == 2) {
        SzModel_SetFogFlag(9, 0);
    }
    if (arg0 != D_00292168) {
        D_00292168 = arg0;
    }
    if (state[2] != 0) {
        SzMem_Free(state[2]);
        state[2] = 0;
    }
    begin = D_00292170[arg0];
    size = D_00292174[arg0] - begin;
    func_0019B648(filename, D_002CF730, (s32) SzFile_GetEnv((s32) D_002CF746));
    SzFile_ReadRequestParam(0x400, 1, filename, 0, size, begin, size, lSzBattle_CameraCB, 0);
}

typedef struct {
    u8 padding[8];
    s32 field8;
} State_001E5210;

extern State_001E5210 D_0031AB88;

void lSzBattle_CameraCB(void *arg0, s32 arg1) {
    State_001E5210 *state = &D_0031AB88;
    s32 var_v1;

    if (arg1 != 0) {
        var_v1 = *(s32 *)((u8 *)arg0 + 0x14);
    } else {
        var_v1 = 0;
    }
    state->field8 = var_v1;
}

s32 SzBattle_InqCamera(void) {
    return D_0031AB90;
}

s32 SzBattle_InqEntry(s32 index) {
    return *(s32 *)&D_0031AB88.padding[index * 4];
}

#ifndef GAME_H
/* The game translation unit already declares this global with its local type. */
typedef struct {
    unsigned char padding[8];
    int field8;
} State_001E5210;

extern State_001E5210 D_0031AB88;
#endif



typedef union {
    __int128 value;
    s32 axis[4];
} Rotation_001E5260;

extern Rotation_001E5260 D_002921C0;

void SzBattle_Entry(s32 arg0, s32 arg1) {
    extern s32 SzModel_GetModelNo();
    s32 *states = (s32 *)&D_0031AB88;
    s32 x = arg1 >> 8;
    s32 y = arg1 & 0xFF;
    void *card;
    s32 model;
    Rotation_001E5260 rotation;
    f32 position[4];
    f32 offset;

    card = (void *)SzDuel_GetUnit(x, y);
    rotation = D_002921C0;
    rotation.axis[1] = (arg0 != 0) ? 0 : 0x8000;
    if (card != NULL && *(s32 *)card != 0) {
        SzDuel_SetBusyFlag(x, y, 1);
        model = *((u8 *)card + 0x46);
        SzSound_TransferSEGrp(arg0 + 2, SzModel_GetModelNo(model), 0);
        SzModel_SetRot(model, &rotation);
        SzModel_GetPos(model, position);
        position[0] = 0.0f;
        if (arg0 != 0) {
            offset = -80.0f;
        } else {
            offset = 80.0f;
        }
        position[2] = offset;
        SzModel_SetPos(model, position);
        SzModel_SetDrawFlag(model, 1);
        SzModel_SetDeform(model, 0);
        SzModel_SetDeformRatio(model, 0);
        SzModel_SetAnimDirect(model, 0);
        SzModel_SetAnimDir(model, 1);
        states[arg0] = arg1;
    }
}

typedef struct {
    s32 entries[2];
    s32 count;
} Slots_001E53C0;

typedef struct {
    s32 v[4];
} Rot_001E53C0 __attribute__((aligned(16)));

typedef struct {
    u8 pad0[0x40];
    u8 f40;
    u8 f41;
    u8 pad42[4];
    u8 model;
} Card_001E53C0;

extern Rot_001E53C0 D_002921D0;

void SzBattle_Return(s32 arg0, s32 arg1) {
    extern s32 SzEffect_ClearRefID2();
    Slots_001E53C0 *state = (Slots_001E53C0 *)&D_0031AB88;
    s32 pos;
    s32 hi;
    s32 lo;
    Card_001E53C0 *card;
    s32 model;
    Rot_001E53C0 rot;
    f32 vecA[4];
    f32 vecB[4];

    pos = ((Slots_001E53C0 *)&D_0031AB88)->entries[arg0];
    hi = pos >> 8;
    lo = pos & 0xFF;
    card = (Card_001E53C0 *)SzDuel_GetUnit(hi, lo);
    rot = D_002921D0;
    rot.v[1] = (hi != 0) ? 0 : 0x8000;
    if (card != NULL) {
        model = card->model;
        SzEffect_ClearRefID2(pos, 1, &rot);
        SzDuel_SetBusyFlag(hi, lo, 0);
        SzModel_SetScale(model, NULL);
        SzModel_SetRot(model, &rot);
        SzModel_GetPos(model, vecA);
        SzDuel_CalcUnitPos(card->f40, card->f41, 0, vecB);
        vecA[0] = vecB[0];
        vecA[2] = vecB[2];
        SzModel_SetPos(model, vecA);
        SzModel_SetDeform(model, 1);
        SzModel_SetDeformRatio(model, 0x20);
        if (arg1 != 0) {
            SzDuel_SetUnitCtlRateM(hi, lo, 0, 0);
            SzDuel_SetUnitCtlGoalM(hi, lo, 0);
        } else {
            SzModel_SetAnimDirect(model, 0);
            SzModel_SetAnimDir(model, 1);
        }
        SzModel_SetRgba(model, 0, NULL);
        SzModel_SetFilter(model, 1, NULL);
        SzModel_CancelMotionBlur(model);
        SzSound_StopSE(arg0 + 2, -1);
        state->entries[arg0] = -1;
    }
}

s32 SzBattle_DrawStage_Pipe(s32 arg0) {
    if (SzModel_GetDrawFlag(8) != 0) {
        return lSzBattle_DrawStage_Pipe(arg0);
    }
    return arg0;
}

typedef struct Vec3_001E55E0 {
    f32 x;
    f32 y;
    f32 z;
} Vec3_001E55E0;

typedef struct Camera_001E55E0 {
    f32 position[4];
    s32 rotation[4];
    f32 scale[4];
    u8 pad30[0x60];
} Camera_001E55E0;

typedef struct Stage_001E55E0 {
    Vec3_001E55E0 light;
    Vec3_001E55E0 ambient;
    u8 pad18[8];
    Camera_001E55E0 camera;
    u8 padB0[0x10];
} Stage_001E55E0;

s32 lSzBattle_DrawStage_Pipe(s32 arg0) {
    extern Stage_001E55E0 D_00291690[];
    extern Camera_001E55E0 D_002921F0;
    extern Vec3_001E55E0 D_00292280;
    extern Vec3_001E55E0 D_00292290;
    extern s32 D_00292168;
    extern s8 D_0031AB98;
    extern s8 D_0031ABA0;
    extern u8 D_002921E0;
    extern s32 lSzBattle_DrawGrass_Pipe(s32, s32, s32);
    extern s32 SzEffect_GetBlackOutForBattle(void);
    extern s32 SzModel_GetModelNo(s32);
    Camera_001E55E0 camera;
    Vec3_001E55E0 ambient;
    Vec3_001E55E0 light;
    Camera_001E55E0 *stage;
    Camera_001E55E0 *toCamera;
    Camera_001E55E0 *fromCamera;
    Vec3_001E55E0 *toAmbient;
    Vec3_001E55E0 *fromAmbient;
    Vec3_001E55E0 *toLight;
    Vec3_001E55E0 *fromLight;
    f32 scale;
    f32 u;
    f32 t;
    s32 i;
    s32 id;
    s32 value;
    s32 id2;
    s32 j;

    scale = (u8)SzEffect_GetBlackOutForBattle() / 128.0f;
    if (D_00292168 == 7) {
        if (D_0031AB98 < 0x3C) {
            t = 0.0f;
        } else {
            t = (D_0031AB98 - 0x3C) / 4.0f;
        }
        u = 1.0f - t;
        toCamera = &D_00291690[10].camera;
        fromCamera = &D_00291690[7].camera;
        toAmbient = &D_00291690[10].ambient;
        fromAmbient = &D_00291690[7].ambient;
        toLight = &D_00291690[10].light;
        fromLight = &D_00291690[7].light;
        camera = D_002921F0;
        camera.position[0] = toCamera->position[0] * t + fromCamera->position[0] * u;
        camera.position[1] = toCamera->position[1] * t + fromCamera->position[1] * u;
        camera.position[2] = toCamera->position[2] * t + fromCamera->position[2] * u;
        camera.position[3] = toCamera->position[3] * t + fromCamera->position[3] * u;
        camera.rotation[0] = (s32)((f32)toCamera->rotation[0] * t + (f32)fromCamera->rotation[0] * u);
        camera.rotation[1] = (s32)((f32)toCamera->rotation[1] * t + (f32)fromCamera->rotation[1] * u);
        camera.rotation[2] = (s32)((f32)toCamera->rotation[2] * t + (f32)fromCamera->rotation[2] * u);
        camera.rotation[3] = (s32)((f32)toCamera->rotation[3] * t + (f32)fromCamera->rotation[3] * u);
        camera.scale[0] = toCamera->scale[0] * t + fromCamera->scale[0] * u;
        camera.scale[1] = toCamera->scale[1] * t + fromCamera->scale[1] * u;
        camera.scale[2] = toCamera->scale[2] * t + fromCamera->scale[2] * u;
        camera.scale[3] = toCamera->scale[3] * t + fromCamera->scale[3] * u;
        ambient = D_00292280;
        ambient.x = toAmbient->x * t + fromAmbient->x * u;
        ambient.y = toAmbient->y * t + fromAmbient->y * u;
        ambient.z = toAmbient->z * t + fromAmbient->z * u;
        light = D_00292290;
        light.x = toLight->x * t + fromLight->x * u;
        light.y = toLight->y * t + fromLight->y * u;
        light.z = toLight->z * t + fromLight->z * u;
        SzModel_SetDrawFlag(0x10, t > 0.0f ? 1 : 0);
        SzEffect_SetStraightLightForMonster((s32)&camera);
        SzEffect_SetStraightLightForBattle((s32)&camera);
        SzEffect_SetIntensityForMonster((s32)&ambient);
        SzEffect_SetIntensityForBattle((s32)&light);
        if (SzModel_GetPauseFlag(8) == 0) {
            if ((s32)(60.0f * (func_0019A5C8() / 2147483648.0f)) == 0) {
                D_0031ABA0 = 1;
            }
            D_0031AB98 += D_0031ABA0;
            if (D_0031AB98 < 0) {
                D_0031AB98 = 0;
                D_0031ABA0 = 0;
            }
            if (D_0031AB98 < 0x20) {
                D_002921E0 = 1;
            }
            if (D_0031AB98 > 0x40) {
                D_0031AB98 = 0x40;
                D_0031ABA0 = -1;
                if (D_002921E0 != 0) {
                    if ((s32)(2.0f * (func_0019A5C8() / 2147483648.0f)) != 0) {
                        SzSound_StereoPlaySE(0, 0x22, 0x23);
                    } else {
                        SzSound_StereoPlaySE(0, 0x24, 0x25);
                    }
                    D_002921E0 = 0;
                }
            }
        }
    }
    if (D_00292168 == 5 || D_00292168 == 6) {
        stage = &D_00291690[D_00292168].camera;
        if (SzModel_GetPauseFlag(8) == 0) {
            if (D_00292168 == 6) {
                stage->rotation[1] = (stage->rotation[1] + 0x200) % 0x10000;
            } else {
                stage->rotation[2] = (stage->rotation[2] + 0x200) % 0x10000;
            }
        }
        SzEffect_SetStraightLightForMonster((s32)stage);
        SzEffect_SetStraightLightForBattle((s32)stage);
    }
    if (D_00292168 == 8) {
        value = func_001A23B0(SzModel_GetAnimFrame(9));
        if (value == 0x14 || value == 0xDC) {
            SzSound_PlaySE(0, 0x28);
        }
    }
    SzEffect_SetIntensityOnly(2, scale);
    SzEffect_SetIntensityOnly(3, scale);
    for (i = 0; i < 12; i++) {
        id = i + 8;
        value = SzModel_GetModelNo(id) % 100;
        if (SzModel_IsModelDisp(id) != 0) {
            switch (D_00292168) {
            case 1:
                arg0 = lSzBattle_DrawWasteland_Pipe(arg0, id, value);
                break;
            case 3:
                arg0 = lSzBattle_DrawGrass_Pipe(arg0, id, value);
                break;
            case 4:
                arg0 = lSzBattle_DrawSea_Pipe(arg0, id, value);
                break;
            case 7:
                arg0 = lSzBattle_DrawNormal_Pipe(arg0, id, value);
                break;
            default:
                arg0 = SzModel_DrawWithOutCalc_Pipe(arg0, id, 0, 0, 0, 0, 0);
                break;
            }
        }
    }
    for (j = 0; j < 1; j++) {
        id2 = j + 7;
        if (SzModel_IsModelDisp(id2) != 0) {
            arg0 = SzModel_DrawWithOutCalc_Pipe(arg0, id2, 0, 0, 0, 0, 0);
        }
    }
    return arg0;
}

s32 lSzBattle_DrawWasteland_Pipe(s32 arg0, s32 arg1, s32 arg2) {
    s32 parameters[4];

    arg0 = SzModel_DrawWithOutCalc_Pipe(arg0, arg1, 0, 0, 0, 0, 0);
    if (arg2 < 9) {
        SzModel_GetRot(arg1, parameters);
        parameters[1] = 0x8000;
        arg0 = SzModel_DrawWithOutCalc_Pipe(arg0, arg1, 0, (s32) parameters, 0, 0, 0);
    }
    return arg0;
}

s32 lSzBattle_DrawGrass_Pipe(s32 arg0, s32 arg1, s32 arg2) {
    extern s32 lSzBattle_DrawFakeShadow(s32, s32, s32, f32, f32);
    s32 i;
    s32 *entry;
    s32 result;

    entry = (s32 *)&D_0031AB88;
    result = SzModel_DrawWithOutCalc_Pipe(arg0, arg1, 0, 0, 0, 0, 0);
    if (arg2 == 0) {
        result = lSzBattle_DrawFakeShadow(result, 7, -1, -25.0f, 800.0f);
        i = 0;
        do {
            s32 value = *entry;
            if (value >= 0) {
                u8 *card = (u8 *)SzDuel_GetUnit(value >> 8, value & 0xFF);
                if (card != NULL) {
                    result = lSzBattle_DrawFakeShadow(result, card[0x46], -1, -25.0f, 800.0f);
                }
            }
            i++;
            entry++;
        } while (i < 2);
    }
    return result;
}

typedef struct Part_001E5EB0 {
    u8 pad0[0x10];
    f32 x;
    f32 y;
    s32 phase;
    u8 pad1C[4];
} Part_001E5EB0;

typedef struct Rot_001E5EB0 {
    s32 x;
    s32 y;
    s32 z;
    s32 w;
} Rot_001E5EB0;

static inline f32 toAngle_001E5EB0(f32 degrees) {
    return 32768.0f * degrees / 180.0f;
}

s32 lSzBattle_DrawSea_Pipe(s32 arg0, s32 arg1, s32 arg2) {
    extern Part_001E5EB0 *D_00292150[];
    extern u8 D_00292160[];
    extern Rot_001E5EB0 D_002922A0;
    extern s32 lSzBattle_DrawFakeMirror(s32, s32);
    Rot_001E5EB0 rot;
    s32 i;
    s32 count;
    s32 base;
    Part_001E5EB0 *part;
    s32 idx;
    s32 phase;

    switch (arg2) {
    case 0:
        arg0 = SzModel_DrawWithOutCalc_Pipe(arg0, arg1, 0, 0, 0, 0, 0);
        arg0 = lSzBattle_DrawFakeMirror(arg0, 0xF);
        break;
    case 5:
    case 6:
    case 7:
    case 8:
        count = SzModel_GetAnimFrameMax(arg1, -1);
        base = (s32)SzModel_GetAnimFrame(arg1);
        idx = arg2 - 5;
        part = D_00292150[idx];
        for (i = 0; i < D_00292160[idx]; i++) {
            rot = D_002922A0;
            rot.x = (s32)toAngle_001E5EB0(part->x);
            rot.y = (s32)toAngle_001E5EB0(part->y);
            phase = (base + part->phase) % count;
            SzModel_SetAnimFrame(arg1, (f32)phase);
            arg0 = SzModel_DrawWithOutCalc_Pipe(arg0, arg1, (s32)part, (s32)&rot, 0, 0, 0);
            part++;
        }
        SzModel_SetAnimFrame(arg1, (f32)base);
        break;
    default:
        arg0 = SzModel_DrawWithOutCalc_Pipe(arg0, arg1, 0, 0, 0, 0, 0);
        break;
    }
    return arg0;
}

typedef union {
    __int128 q;
    f32 f[4];
    s32 i[4];
} Quad_001E60E0;

extern Quad_001E60E0 D_002922B0;
extern Quad_001E60E0 D_002922C0;
extern Quad_001E60E0 D_002922D0;
extern Quad_001E60E0 D_002922E0;
extern Quad_001E60E0 D_002922F0;
extern Quad_001E60E0 D_00292300;

s32 lSzBattle_DrawNormal_Pipe(s32 arg0, s32 arg1, s32 arg2) {
    s32 i;
    s32 j;
    s32 *entry = (s32 *)&D_0031AB88;
    Quad_001E60E0 scale;

    scale = D_002922B0;
    switch (arg2) {
    case 1: {
        Quad_001E60E0 rotation;
        rotation = D_002922C0;
        i = 0;
        do {
            arg0 = SzModel_DrawWithOutCalc_Pipe(arg0, arg1, 0, (s32)&rotation, (s32)&scale, 0, 0);
            rotation.i[1] += 0x4000;
            i++;
        } while (i < 4);
        break;
    }
    case 3: {
        Quad_001E60E0 rotation;
        rotation = D_002922D0;
        i = 0;
        do {
            arg0 = SzModel_DrawWithOutCalc_Pipe(arg0, arg1, 0, (s32)&rotation, (s32)&scale, 0, 0);
            rotation.i[1] += 0x8000;
            i++;
        } while (i < 2);
        break;
    }
    case 5: {
        Quad_001E60E0 rotation;
        Quad_001E60E0 position;
        f32 signZ;
        f32 baseX;
        f32 baseZ;
        f32 signX;

        rotation = D_002922E0;
        SzModel_GetPos(arg1, &position);
        i = 0;
        do {
            if (i % 2 == 0) {
                signX = -1.0f;
            } else {
                signX = 1.0f;
            }
            if (i >> 1 == 0) {
                signZ = -1.0f;
            } else {
                signZ = 1.0f;
            }
            baseX = 275.0f * signX;
            position.f[0] = baseX * scale.f[0];
            baseZ = 275.0f * signZ;
            position.f[2] = baseZ * scale.f[2];
            arg0 = SzModel_DrawWithOutCalc_Pipe(arg0, arg1, (s32)&position, (s32)&rotation, (s32)&scale, 0, 0);
            position.f[0] = scale.f[0] * (baseX - 100.0f * signX);
            position.f[2] = baseZ * scale.f[2];
            arg0 = SzModel_DrawWithOutCalc_Pipe(arg0, arg1, (s32)&position, (s32)&rotation, (s32)&scale, 0, 0);
            position.f[0] = baseX * scale.f[0];
            position.f[2] = scale.f[2] * (baseZ - 100.0f * signZ);
            arg0 = SzModel_DrawWithOutCalc_Pipe(arg0, arg1, (s32)&position, (s32)&rotation, (s32)&scale, 0, 0);
            i++;
        } while (i < 4);
        break;
    }
    case 6: {
        Quad_001E60E0 rotation;
        Quad_001E60E0 position;
        f32 signX;
        f32 signZ;
        f32 baseX;
        f32 baseZ;
        f32 distance;

        rotation = D_002922F0;
        SzModel_GetPos(arg1, &position);
        i = 0;
        do {
            if (i % 2 == 0) {
                signX = -1.0f;
            } else {
                signX = 1.0f;
            }
            if (i >> 1 == 0) {
                signZ = -1.0f;
            } else {
                signZ = 1.0f;
            }
            baseX = 425.0f * signX;
            position.f[0] = baseX * scale.f[0];
            baseZ = 425.0f * signZ;
            position.f[2] = baseZ * scale.f[2];
            arg0 = SzModel_DrawWithOutCalc_Pipe(arg0, arg1, (s32)&position, (s32)&rotation, (s32)&scale, 0, 0);
            j = 0;
            do {
                distance = 100.0f * (f32)(j + 1);
                position.f[0] = scale.f[0] * (baseX - distance * signX);
                position.f[2] = baseZ * scale.f[2];
                arg0 = SzModel_DrawWithOutCalc_Pipe(arg0, arg1, (s32)&position, 0, (s32)&scale, 0, 0);
                position.f[0] = baseX * scale.f[0];
                position.f[2] = scale.f[2] * (baseZ - distance * signZ);
                arg0 = SzModel_DrawWithOutCalc_Pipe(arg0, arg1, (s32)&position, 0, (s32)&scale, 0, 0);
                j++;
            } while (j < 3);
            i++;
        } while (i < 4);
        break;
    }
    default: {
        Quad_001E60E0 rotation;
        rotation = D_00292300;
        arg0 = SzModel_DrawWithOutCalc_Pipe(arg0, arg1, 0, (s32)&rotation, (s32)&scale, 0, 0);
        break;
    }
    }
    if (arg2 == 0) {
        arg0 = lSzBattle_DrawFakeShadow(arg0, 7, -1, -13.5f, 400.0f);
        i = 0;
        do {
            s32 value = *entry;
            if (value >= 0) {
                u8 *card = (u8 *)SzDuel_GetUnit(value >> 8, value & 0xFF);
                if (card != NULL) {
                    arg0 = lSzBattle_DrawFakeShadow(arg0, card[0x46], -1, -13.5f, 400.0f);
                }
            }
            i++;
            entry++;
        } while (i < 2);
    }
    return arg0;
}

INCLUDE_ASM("asm/nonmatchings/main_047", lSzBattle_DrawFakeMirror);

typedef struct {
    f32 f[5];
} Plane_001E6F90;

typedef struct {
    f32 matrix[4][4];
    f32 position[4];
    f32 direction[4][4];
} Camera_001E6F90;

typedef struct {
    f32 f[3][2][2][4];
} Points_001E6F90;

typedef union {
    u64 bits;
    struct {
        u64 low : 32;
        u64 flags : 24;
        u64 high : 8;
    } fields;
} Color_001E6F90;

typedef struct {
    f32 position[4];
    Color_001E6F90 color;
    u8 r, g, b, a;
    f32 q;
    f32 uv[2];
    u32 reserved[2];
} Vertex_001E6F90;

typedef struct {
    u16 first, type;
    u32 flags;
    u64 value;
    u8 tail[8];
} Header_001E6F90;

typedef union {
    s64 packed;
    f32 f[2];
} Range_001E6F90;

static inline void tag_001E6F90(Header_001E6F90 *p, s32 first, s32 type, u64 value) { p->type = type; p->first = first; p->value = value; p->flags = 0; }
#define MAX_001E6F90(a, b) ((a) > (b) ? (a) : (b))


#pragma opt_dead_assignments off

s32 lSzBattle_DrawFakeShadow(s32 arg0, s32 arg1, s32 arg2, f32 fparg0, f32 fparg1) {
    f32 delta;
    extern s32 func_002070F0(s32, s32, void *, s32, void *, s32, s32);
    extern void func_0020A470(s32, s32, s32);
    extern s32 func_0020A870(void *, s32);
    extern s32 func_00207AA0(s32, void *, s32, void *, s32, s32);
    extern void func_0020CF00(void *, s32, void *, s32);
    extern s32 func_0020EC60(void *);
    extern s32 func_001F2980();
    extern Plane_001E6F90 D_00292380;
    extern Points_001E6F90 D_002923A0;
    extern Range_001E6F90 D_00292460;
    Plane_001E6F90 plane;
    Camera_001E6F90 camera;
    Points_001E6F90 points;
    f32 position[4];
    f32 matrix[4][4];
    f32 midpoint[6];
    Header_001E6F90 header __attribute__((aligned(8)));
    s64 saved[3] __attribute__((aligned(8)));
    Range_001E6F90 range __attribute__((aligned(8)));
    s32 alpha;

    plane = D_00292380;
    plane.f[3] = -fparg0;
    alpha = func_001F2980(arg1, &plane);
    if (func_001F1370(arg1) == 0) {
        return (s32)arg0;
    }
    if (func_001F96F0(0, alpha) == 0) {
        alpha = 9;
    }
    func_0020DEF0(&camera);
    func_001F9500(0, alpha, 0, camera.direction[0]);
    {
        f32 absolute = camera.direction[0][1];
        absolute = absolute >= 0.0f ? absolute : -absolute;
        if (!(absolute < 1.0f)) {
            camera.direction[0][1] *= 0.999999f;
            camera.direction[0][2] = 0.000001f;
        }
    }
    if (!(func_0020D1A0(plane.f, camera.direction[0]) <= 0.0f) &&
        func_0020E460() != 0) {
        s32 count;
        s32 endpoint;
        s32 opacityScale;
        Vertex_001E6F90 *scratch;
        s32 i;
        Vertex_001E6F90 *vertex;
        Vertex_001E6F90 *current;
        Vertex_001E6F90 *opposite;
        s32 packet;
        s32 drawPacket;
        s32 band;
        s32 pair;
        f32 scale;
        f32 width;
        f32 height;
        u8 *scratchpad;

        opacityScale = (func_001F27A0(arg1) << 6) >> 7;
        scale = fparg1 / 800.0f;
        scratchpad = (u8 *)0x70000000;
        width = 320.0f * scale;
        height = 224.0f * scale;
        scratch = (Vertex_001E6F90 *)(0x2000 + scratchpad);
        points = D_002923A0;
        points.f[0][0][0][0] = -width;
        points.f[0][0][0][1] = -height;
        points.f[0][0][1][0] = -width;
        points.f[0][0][1][1] = height;
        points.f[0][1][0][0] = width;
        points.f[0][1][0][1] = -height;
        points.f[0][1][1][0] = width;
        points.f[0][1][1][1] = height;
        points.f[1][0][0][0] = -width;
        points.f[1][0][0][1] = -height;
        points.f[1][0][0][2] = fparg1;
        points.f[1][0][1][0] = -width;
        points.f[1][0][1][1] = height;
        points.f[1][0][1][2] = fparg1;
        points.f[1][1][0][0] = width;
        points.f[1][1][0][1] = -height;
        points.f[1][1][0][2] = fparg1;
        points.f[1][1][1][0] = width;
        points.f[1][1][1][1] = height;
        points.f[1][1][1][2] = fparg1;
        packet = (s32)func_00208530((void *)arg0, 0);
        func_0020A470(0, 10, 0x31);
        packet = func_0020A870(func_0020A610((void *)packet), 0);
        func_001F2050(arg1, position);
        camera.position[0] = position[0] + camera.direction[0][0] * fparg1;
        camera.position[1] = position[1] + camera.direction[0][1] * fparg1;
        camera.position[2] = position[2] + camera.direction[0][2] * fparg1;
        camera.direction[0][0] *= -1.0f;
        camera.direction[0][1] *= -1.0f;
        camera.direction[0][2] *= -1.0f;
        { f32 h = 448.0f, cy = 224.0f, d = 800.0f, w = 640.0f, cx = 320.0f; func_0020DF40(d, w, h, cx, cy); }
        func_0020E360(&camera);
        count = func_0020EC60((void *)packet);
        func_0020EBA0(matrix);
        func_0020BDE0(matrix, matrix);
        func_0020BAF0((s32)matrix);
        RhGeom_MulMatrixVectorArray((void *)(u32)&points, 0, (void *)(u32)&points, 8);
        func_0020BB50();
        count = func_001EFA80(count, arg1, 0, 0, 0, 0, 0);
        func_0020AA30(saved, saved + 1);
        count = func_0020F290((s32)func_0020A760((void *)count));
        func_0020E4F0();
        func_0020DEF0(&camera);
        func_0020E360(&camera);
        drawPacket = func_0020A0B0(func_0020EC60((void *)count), 0);
        {
            tag_001E6F90((Header_001E6F90 *)(u32)&header, 0, 0x35, 0);
            func_002086D0(&header, 0x8000000044LL);
        }
        i = 0;
        vertex = scratch;
        do {
            f32 * p;
            s32 endpoint;
            s32 side;
            side = i >> 1;
            endpoint = i % 2;
            p = points.f[0][side][endpoint];
            vertex->r = 0;
            vertex->g = 0;
            vertex->b = 0;
            vertex->a = opacityScale;
            vertex->q = 1.0f;
            func_00206430(plane.f, p, p + 16, p + 32);
            i++;
            vertex++;
        } while (i < 4);
        band = 0;
        do {
            s32 j;
            s32 side;
            Vertex_001E6F90 *interpolated;
            f32 *p;
            range = D_00292460;
            range.f[0] = (f32)band / 8.0f;
            interpolated = scratch;
            range.f[1] = (f32)(band + 1) / 8.0f;
            j = 0;
            do {
                f32 nextX;
                f32 x;
                f32 t;
                side = j >> 1;
                p = points.f[0][side][0];
                x = p[32];
                endpoint = (j == 0 || j == 3) ? 0 : 1;
                nextX = p[36];
                t = range.f[endpoint];
                delta = nextX - x;
                interpolated->position[0] = x + delta * t;
                delta = p[37] - p[33];
                interpolated->position[1] = p[33] + delta * t;
                x = p[34];
                delta = p[38] - x;
                interpolated->position[2] = x + delta * t;
                interpolated->position[3] = 1.0f;
                interpolated->uv[0] = (640.0f * (f32)side) / 1024.0f;
                j++;
                interpolated->uv[1] = (448.0f * t) / 512.0f;
                interpolated++;
            } while (j < 4);
            pair = 0;
            current = scratch;
            do {
                f32 distance;
                s32 opacity;
                f32 intensity;
                midpoint[0] = (current->position[0] + (opposite = &scratch[3 - pair])->position[0]) / 2.0f;
                midpoint[1] = (current->position[1] + opposite->position[1]) / 2.0f;
                midpoint[2] = (current->position[2] + opposite->position[2]) / 2.0f;
                distance = func_0020D100(position, midpoint);
                if (distance < 1.0f) {
                    distance = 1.0f;
                }
                intensity = 1e11f / (distance * (distance * (distance * (distance * distance))));
                intensity = MAX_001E6F90(intensity, 0.0f) < 1.0f
                    ? MAX_001E6F90(intensity, 0.0f) : 1.0f;
                opacity = func_001A23B0((f32)opacityScale * intensity);
                opposite->a = opacity;
                current->a = opacity;
                current++;
                pair++;
            } while (pair < 2);
            count = func_002070F0(0, 4, scratch, 0xAA, scratchpad, 15, 0);
            if (count >= 3) {
                func_00207230(0, count, scratch);
                {
                    Vertex_001E6F90 * p;
                    s32 n;
                    n = 0;
                    if (n < count) {
                        p = scratch;
                        do {
                            p->color.fields.flags = 0xFFFFF6;
                            n++;
                            p++;
                        } while (n < count);
                    }
                }
                drawPacket = func_00207AA0(drawPacket, &header, count, scratch, 0, 0);
            }
            band++;
        } while (band < 7);
        opacityScale = func_0020A0B0(drawPacket, 1);
        func_0020A9E0();
        arg0 = (s32)func_00208530((void *)opacityScale, 1);
    }
    return (s32)arg0;
}
#pragma opt_dead_assignments reset

void SzBattle_Term(void) {
    s32 i;

    i = 0;
    do {
        SzBattle_Return(i, 0);
        i += 1;
    } while (i < 2);
}

void SzEvent_Init(s32 arg0) {
    s32 var_s0;

    SzView_SetStraightLight(0, 9, 1);
    var_s0 = 0;
    do {
        SzModel_SetDrawFlag(var_s0, 0);
        var_s0 += 1;
    } while (var_s0 < 0x54);
    var_s0 = 0;
    do {
        SzModel_SetDrawFlag(var_s0 + 0x22, 1);
        var_s0 += 1;
    } while (var_s0 < 0x28);
    var_s0 = 0;
    do {
        SzModel_SetDrawFlag(var_s0 + 0x1E, 1);
        var_s0 += 1;
    } while (var_s0 < 2);
    if (arg0 != D_00292468) {
        D_00292468 = arg0;
    }
}

void SzEvent_Draw(void) {
    RhBase_SetVifPacketArea(SzEvent_Draw_Pipe(RhBase_GetVifPacketArea()));
}

typedef struct Entry_001E78C0 {
    s16 first;
    s16 second;
    f32 x;
    f32 z;
} Entry_001E78C0;

typedef union Quad_001E78C0 {
    __int128 q;
    f32 f[4];
} Quad_001E78C0;

s32 SzEvent_Draw_Pipe(s32 arg0) {
    extern Quad_001E78C0 D_00292470;
    extern Entry_001E78C0 D_002CF750[];
    Quad_001E78C0 position;
    s32 i;
    s32 firstId;
    s32 secondId;
    s32 id;

    if (SzModel_GetDrawFlag(0x22) != 0) {
        if (D_00292468 == 2) {
            for (i = 0; D_002CF750[i].second >= 0; i++) {
                secondId = D_002CF750[i].second + 0x22;
                firstId = D_002CF750[i].first + 0x22;
                position = D_00292470;
                position.f[0] = D_002CF750[i].x;
                position.f[2] = D_002CF750[i].z;
                if (D_002CF750[i].first >= 0 && SzModel_IsModelDisp(firstId) != 0) {
                    arg0 = SzModel_DrawWithOutCalc_Pipe(arg0, firstId, (s32) &position, 0, 0, 0, 0);
                }
                if (D_002CF750[i].second >= 0 && SzModel_IsModelDisp(secondId) != 0) {
                    arg0 = SzModel_DrawWithOutCalc_Pipe(arg0, secondId, (s32) &position, 0, 0, 0, 0);
                }
            }
        } else {
            for (i = 0; i < 0x28; i++) {
                id = i + 0x22;
                if (SzModel_IsModelDisp(id) != 0) {
                    arg0 = SzModel_DrawWithOutCalc_Pipe(arg0, id, 0, 0, 0, 0, 0);
                }
            }
        }
    }
    return arg0;
}

void SzEvent_Term(void) {

}

typedef struct Entry_001E7A60 {
    u8 padding[0x68];
    s32 id : 27;
    u32 flags : 5;
    u32 padding_6C;
} Entry_001E7A60;

extern Entry_001E7A60 D_0031AD00[];
extern s32 D_0031BB00;
extern s32 D_0031BB18;
extern u8 D_002CF9D0[];
extern u8 D_002CF9D5[];

s32 SzModel_Init(void) {
    extern u8 *getenv();
    s32 i;
    Entry_001E7A60 *entry;
    s32 j;

    for (i = 0; i < 0x54; i++) {
        D_0031ABB0[i] = NULL;
    }
    entry = D_0031AD00;
    for (j = 0; j < 0x20; j++) {
        entry->id = -1;
        entry++;
    }
    D_0031BB00 = 0;
    if (getenv(D_002CF9D0) != NULL || getenv(D_002CF9D5) != NULL) {
        D_0031BB18 = 1;
    }
    return 1;
}

typedef struct ObjInit_001E7B20 {
    u8 pad000[0x30];
    f32 v[4];
    u8 pad040[0xE0];
    f32 f120;
    f32 f124;
    f32 f128;
    u8 rgba[4];
    u8 c130[4];
    u8 pad134[0xB8];
    s32 f1EC;
    u8 pad1F0;
    s8 f1E1_dummy;
    s8 f1F2;
    u8 pad1F3;
    s16 f1F4;
    u8 pad1F6;
    s8 pad1F7 : 6;
    s8 mode1F7 : 2;
    u8 pad1F8a : 2;
    u8 kind1F8 : 2;
    u8 pad1F8b : 4;
    u8 pad1F9[0x13];
    s8 b0 : 1;
    s8 b1 : 1;
    s8 b2 : 1;
    s8 b3 : 1;
    s8 b4 : 1;
    s8 b5 : 1;
    s8 b6 : 1;
    s8 b7 : 1;
} ObjInit_001E7B20;

s32 SzModel_Create(s32 arg0) {
    ObjInit_001E7B20 *obj;
    s32 off;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    if ((obj = (ObjInit_001E7B20 *)SzMem_Alloc(0x210)) == NULL) {
        return 0;
    }
    D_0031ABB0[arg0] = (Obj_0031ABB0 *)obj;
    RhMem_FillMemory4(obj, 0, 0x84);
    ((s8 *)obj)[0x1E1] = -1;
    obj->mode1F7 = 1;
    obj->f1F2 = -1;
    obj->f1F4 = -1;
    obj->f1EC = -1;
    obj->v[0] = 1.0f;
    obj->v[1] = 1.0f;
    obj->v[2] = 1.0f;
    obj->v[3] = 1.0f;
    obj->f120 = 0.8f;
    obj->f124 = 0.8f;
    obj->f128 = 1.0f;
    obj->rgba[2] = 0x80;
    obj->rgba[1] = 0x80;
    obj->rgba[0] = 0x80;
    obj->rgba[3] = 0x80;
    obj->kind1F8 = 1;
    obj->c130[2] = 0;
    obj->c130[1] = 0;
    obj->c130[0] = 0;
    obj->c130[3] = 0;
    off = 0;
    obj->b0 = 1;
    obj->b1 = 1;
    obj->b2 = off;
    obj->b3 = off;
    obj->b4 = off;
    obj->b5 = off;
    obj->b6 = 1;
    obj->b7 = 1;
    lSzModel_Clean(arg0);
    return 1;
}

typedef struct {
    s8 bit0 : 1;
    s8 bit1 : 1;
    s8 bits2_4 : 3;
    s8 bit5 : 1;
    s8 bits6_7 : 2;
} Flags_001E7D00;


s32 lSzModel_Clean(s32 index) {
    Obj_0031ABB0 *object;

    if ((index < 0) || (index >= 0x54)) {
        return 0;
    }
    object = D_0031ABB0[index];
    if (object == NULL) {
        return 0;
    }
    *(f32 *)((u8 *)object + 0x198) = 1.0f;
    *(f32 *)((u8 *)object + 0x19C) = 1.0f;
    *(f32 *)((u8 *)object + 0x1A0) = 1.0f;
    *(f32 *)((u8 *)object + 0x1A4) = 1.0f;
    *(f32 *)((u8 *)object + 0x1A8) = 1.0f;
    *(f32 *)((u8 *)object + 0x1AC) = 0.0f;
    object->lv[1] = -1;
    object->lv[0] = 0;
    ((Flags_001E7D00 *)((u8 *)object + 0x20D))->bit1 = 0;
    *(s8 *)((u8 *)object + 0x200) = 0;
    *(s16 *)((u8 *)object + 0x20A) = 0;
    *(s8 *)((u8 *)object + 0x1FB) = 6;
    *(s8 *)((u8 *)object + 0x1FC) = 0;
    *(s8 *)((u8 *)object + 0x1FD) = 0;
    ((Flags_001E7D00 *)((u8 *)object + 0x20C))->bit5 = 0;
    SzModel_SetRefID(index, -1, 1);
    *(s16 *)((u8 *)object + 0x1F0) = 0x7FFF;
    return 1;
}

s32 SzModel_Destroy(s32 arg0) {
    s32 lSzModel_FreeModel(s32);
    void SzMem_Free(void *);
    Obj_0031ABB0 *obj;
    Obj_0031ABB0 **slot;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    slot = &D_0031ABB0[arg0];
    obj = *slot;
    if (obj == NULL) {
        return 0;
    }
    if (lSzModel_FreeModel(arg0) == 0) {
        return 0;
    }
    SzMem_Free(obj);
    *slot = NULL;
    return 1;
}

typedef struct {
    s8 unused0 : 2;
    s8 pending : 1;
    s8 busy : 1;
    s8 unused4 : 4;
} Flags_001E7E70;


static inline s64 busy_001E7E70(Obj_0031ABB0 *obj) {
    return (s64) ((u64) obj->lv[0x2C] << 60) >> 63;
}

s32 SzModel_Preset(s32 arg0, s32 arg1, s32 arg2) {
    Obj_0031ABB0 *temp_s0;

    if ((arg0 < 0) || (arg0 >= 0x54)) {
        return 0;
    }
    temp_s0 = D_0031ABB0[arg0];
    if (temp_s0 == NULL) {
        return 0;
    }
    if (busy_001E7E70(temp_s0)) {
        while (busy_001E7E70(temp_s0)) {
            SzFile_DoRequestS();
        }
    }
    lSzModel_FreeModel(arg0);
    *(s8 *) ((u8 *) temp_s0 + 0x1F2) = -1;
    if (arg1 >= 0) {
        *(s8 *) ((u8 *) temp_s0 + 0x1F3) = (s8) arg1;
    }
    *(s16 *) ((u8 *) temp_s0 + 0x1F4) = (s16) arg2;
    ((Flags_001E7E70 *) &temp_s0->lv[0x2C])->pending = 1;
    return 1;
}

typedef struct {
    s16 *values[9];
} Sources_001E7F70;

typedef struct {
    s32 values[9];
} Table_001E7F70;

typedef struct {
    s32 file;
    u16 base;
    u16 mask;
} File_001E7F70;

typedef struct {
    s8 unused0 : 2;
    s8 pending : 1;
    s8 active : 1;
    s8 unused4 : 4;
} Flags_001E7F70;

s32 SzModel_LoadMerge(s32 arg0, s32 arg1, s32 arg2) {
    s32 *start;
    s32 value;
    s32 id;
    Sources_001E7F70 sources;
    extern s32 SzFile_ReadRequestParam();
    extern s32 SzModel_GetModelNo();
    extern s32 D_00292A50[];
    extern s32 D_00292A54[];
    extern File_001E7F70 D_00292BA0[];
    extern u16 D_00292BA4[];
    extern Sources_001E7F70 D_00292BE0;
    extern Table_001E7F70 D_00292C10;
    extern Table_001E7F70 D_00292C40;
    extern Table_001E7F70 D_00292C70;
    extern u8 D_002CEBBC[];
    extern s16 D_002CEBC6[];
    extern u8 D_002CEBC8[];
    extern u8 D_002CECB8[];
    extern u8 D_002CEE48[];
    extern u16 D_002CF910[];
    extern u8 D_002CF9DD[];
    extern u8 D_002CF9F0[];
    s32 fileIndex;
    s32 offset;
    s32 length;
    s32 file;
    Table_001E7F70 types;
    Table_001E7F70 counts;
    Table_001E7F70 starts;
    u8 *path;
    u8 name[128];
    File_001E7F70 *info;
    s16 *commonSource;
    s32 i;

    if (arg0 < 0 || arg0 >= 7) {
        return 0;
    }

    sources = D_00292BE0;
    sources.values[0] = (s16 *)&D_002CEBBC[arg1 * 10];
    sources.values[1] = &D_002CEBC6[arg1];
    sources.values[2] = (s16 *)&D_002CEBC8[24 * arg1];
    commonSource = (s16 *)&D_002CECB8[arg1 * 80];
    sources.values[3] = commonSource;
    sources.values[4] = commonSource;
    sources.values[5] = commonSource;
    sources.values[6] = (s16 *)&D_002CEE48[arg1 * 20];
    types = D_00292C10;
    counts = D_00292C40;
    starts = D_00292C70;
    fileIndex = arg1 + *(u16 *)((u8 *)D_00292BA4 + arg0 * 8);
    offset = D_00292A50[fileIndex];
    length = D_00292A54[fileIndex] - offset;
    info = &D_00292BA0[arg0];
    file = info->file;
    path = name;
    func_0019B648(path, D_002CF9DD, (s32)SzFile_GetEnv((s32)D_002CF9F0));
    if (4 != arg0) {
        if (SzText_GetItem(0, 0) != NULL) {
            SzText_Free(0, 0);
            SzText_Free(1, -1);
        }
    }
    if (3 != arg0) {
        SzText_Free(0, 5);
        SzText_Free(0, 6);
        SzText_Free(7, -1);
        SzText_Free(8, -1);
    }
    if (arg0 == 4) {
        counts.values[7] = 9;
    }

    if (arg2 == 0) {
        s32 j;
        s32 id;
        s32 count;
        s32 *start;
        s32 *amount;

        start = starts.values;
        amount = counts.values;
        i = 0;
        do {
            if ((1 << i) & info->mask) {
                id = *start;
                count = *amount;
                j = 0;
                goto test;
                body:
                    if (SzModel_IsModelStandby(id) != 0) {
                        arg2 = 1;
                    }
                    id++;
                    j++;
                test:
                if (j < count) goto body;
            }
            i++;
            start++;
            amount++;
        } while (i < 9);

        {
            s32 *start;
            u16 *limit;
            s32 *amount;
            s16 *source;
            s32 i;

            source = sources.values[arg0];
            if (source != NULL) {
                i = 0;
                start = &starts.values[arg0];
                amount = &counts.values[arg0];
                limit = &D_002CF910[types.values[arg0]];
                while (i < *amount) {
                    value = *source;
                    id = i + *start;
                    if (value < *limit && value != SzModel_GetModelNo(id)) {
                        arg2 = 1;
                    }
                    source++;
                    i++;
                }
            }
        }
    }

    if (0 == arg2) {
        return 1;
    }

    {
        s32 *amount;
        s32 *type;
        s32 i;
        s32 j;

        start = starts.values;
        amount = counts.values;
        type = types.values;
        i = 0;
        do {
            if ((1 << i) & info->mask) {
                j = 0;
                while (j < *amount) {
                    SzModel_Preset(j + *start, -1, 999);
                    j++;
                }
                if (*type == 4) {
                    j = 1;
                    do {
                        SzDuel_DelUnit(0, j);
                        SzDuel_DelUnit(1, j);
                        j++;
                    } while (j < 11);
                }
            }
            i++;
            start++;
            amount++;
            type++;
        } while (i < 9);
    }

    {
        i = 0;
        while (i < counts.values[arg0]) {
            SzModel_Preset(starts.values[arg0] + i, -1, sources.values[arg0][i]);
            i++;
        }
        if (SzFile_ReadRequestParam(arg0, 0, (s32)path, file, length, offset, length,
                          (s32)lSzModel_LoadMergeCB, fileIndex) == 0) {
            return 0;
        }
        i = 0;
        while (i < counts.values[arg0]) {
            Obj_0031ABB0 *obj = D_0031ABB0[i + starts.values[arg0]];
            if (obj != NULL) {
                ((Flags_001E7F70 *)((u8 *)obj + 0x20C))->pending = 0;
                ((Flags_001E7F70 *)((u8 *)obj + 0x20C))->active = 1;
            }
            i++;
        }
    }
    return 1;
}

struct DotrMergeRecord {
    char unknown_00[0x14];
    char *data;
    int unknown_18;
    int user;
};
struct DotrMergeBits {
    signed char bit_0 : 1;
    signed char bit_1 : 1;
    signed char bit_2 : 1;
    signed char bit_3 : 1;
    signed char bit_4 : 1;
    signed char bit_5 : 1;
    signed char bit_6 : 1;
    signed char bit_7 : 1;
};
struct DotrMergeObject {
    unsigned char unknown_000[0x1f3];
    signed char kind;
    short number;
    unsigned char unknown_1f6[0x16];
    struct DotrMergeBits bits;
};
struct DotrMergeTable {
    int v[39];
};
struct DotrMergeOffsets {
    int *v[39];
};
extern struct DotrMergeTable D_00292CA0;
extern struct DotrMergeTable D_00292D40;
extern struct DotrMergeTable D_00292DE0;
extern struct DotrMergeOffsets D_00292E80;
extern unsigned short D_002CF910[];
extern struct DotrMergeObject *D_0031ABB0_b[];

void lSzModel_LoadMergeCB(void *req_v, int ok)
{
    struct DotrMergeRecord * req = req_v;
    int user = req->user;
    struct DotrMergeTable first = D_00292CA0;
    struct DotrMergeTable count = D_00292D40;
    struct DotrMergeTable limit = D_00292DE0;
    struct DotrMergeOffsets offs = D_00292E80;
    int j;
    struct DotrMergeObject *p;

    if (!ok) {
        for (j = 0; j < count.v[user]; j++) {
            p = D_0031ABB0_b[first.v[user] + j];
            if (p) {
                p->bits.bit_3 = 0;
            }
        }
        return;
    }
    for (j = 0; j < count.v[user]; j++) {
        p = D_0031ABB0_b[first.v[user] + j];
        if (p) {
            p->bits.bit_3 = 0;
            if (p->number < D_002CF910[p->kind] && j < limit.v[user] && *(int *)(req->data + offs.v[user][j]) == 0x304852) {
                p->bits.bit_0 = 0;
                lSzModel_Clean(first.v[user] + j);
                lSzModel_BindModelByAddr(first.v[user] + j, req->data + offs.v[user][j]);
            }
        }
    }
}

typedef struct {
    s8 unused0 : 2;
    s8 loading : 1;
    s8 busy : 1;
    s8 unused4 : 4;
} Flags_001E8780;

typedef struct {
    Obj_0031ABB0 shared;
    u8 pad1E4[0x1F2 - sizeof(Obj_0031ABB0)];
    s8 state;
    s8 kind;
    s16 value;
    u8 pad1F6[0x16];
    s8 unused0 : 2;
    s8 loading : 1;
    s8 busy : 1;
    s8 unused4 : 4;
} Fields_001E8780;

typedef struct {
    s32 values[3];
} Table_001E8780;

extern s32 D_00292480[];
extern s32 D_00292A50[];
extern s32 D_00292A54[];
extern Table_001E8780 D_00292F20;
extern Table_001E8780 D_00292F30;
extern u16 D_002CF910[];
extern u8 D_002CF9D5[];
extern u8 D_002CF9DD[];
extern u8 D_002CF9F0[];
extern u8 D_002CF9F5[];
extern u8 D_002CFA0A[];
extern u8 D_002CFA17[];
extern u8 D_002CFA1D[];
extern s32 D_0031BB18;

s32 SzModel_Load(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 format[128];
    u8 path[128];
    Table_001E8780 slots;
    Table_001E8780 starts;
    Fields_001E8780 *obj;
    s32 slot;
    s32 base;
    u8 *root;
    s32 value;
    s32 id;
    s32 group;
    s32 index;
    s32 start;
    s32 size;
    s32 card;
    s32 leader;
    s32 kind;
    s32 tableIndex;

    extern void func_0019B648();

    value = arg2;
    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    obj = (Fields_001E8780 *)D_0031ABB0[arg0];
    if (obj == NULL) {
        return 0;
    }
    if (obj->busy) {
        while (obj->busy) {
            SzFile_DoRequestS();
        }
    }
    obj->state = -1;
    if (arg1 >= 0) {
        obj->kind = arg1;
    }
    if (value >= 0) {
        obj->value = value;
    } else {
        value = obj->value;
    }
    obj->loading = 0;
    if (value < 0 || value >= D_002CF910[obj->kind]) {
        return 0;
    }
    base = D_00292480[obj->kind];
    if (arg3 != 0 && D_0031BB18 != 0) {
        if (getenv((s32)D_002CF9D5) != NULL) {
            root = SzFile_GetEnv((s32)D_002CF9F0);
            kind = obj->kind;
            card = 0;
            leader = 0;
            if (kind == 4) {
                goto card_kind;
            }
            if (kind == 5) {
                goto card_kind;
            }
            if (kind == 6) {
            card_kind:
                card = 1;
            }
            if (kind == 1) {
                leader = 1;
            }
            if (card) {
                if (value == 0x2E1) {
                    id = 0x29F;
                } else {
                    id = SzDuel_Xax2New(value);
                }
                if (id < 0x2AB) {
                    slot = obj->kind - 4;
                    slots = D_00292F20;
                    starts = D_00292F30;
                    func_0019B648(path, D_002CF9F5, root);
                    if (lSzModel_LoadModelPack(arg0, path, starts.values[slot] + ((arg0 - slots.values[slot]) << 20), 0x100000, id << 20, 0x100000)) {
                        return 1;
                    }
                }
                return 0;
            } else if (leader) {
                group = value / 100;
                index = value % 100;
                if (group >= 0 && group < 2 && index >= 0 && index < 21) {
                    tableIndex = index + (group != 0 ? 0x3C : 0x27);
                    start = D_00292A50[tableIndex];
                    size = D_00292A54[tableIndex] - start;
                    func_0019B648(path, D_002CF9DD, root);
                    if (lSzModel_LoadModelPack(arg0, path, (s32)((s64)group * 0xA000 + 0x010AA800), size, start, size)) {
                        return 1;
                    }
                }
                return 0;
            }
        }
        func_0019B648(format, D_002CFA0A, SzFile_GetEnv((s32)D_002CFA17), base, base);
        func_0019B648(path, format, value, value);
        if (lSzModel_LoadModelPack(arg0, path, 0, -1, 0, -1) == 0) {
            return 0;
        }
    } else {
        func_0019B648(format, D_002CFA1D, SzFile_GetEnv((s32)D_002CFA17), base, base);
        func_0019B648(path, format, value, value);
        if (lSzModel_LoadModel(arg0, path) == 0) {
            return 0;
        }
    }
    return 1;
}

struct DotrModelLoadHeader {
    int node_offset;
    unsigned int flags;
    unsigned char unknown_08[80];
    int gnode_flag;
};
struct DotrModelLoadNode {
    unsigned char unknown_00[0x30];
    float x, y, z, radius;
};
struct DotrModelLoadObject {
    unsigned char unknown_000[0x90];
    float pos[4];
    unsigned char unknown_0a0[0x94];
    struct DotrModelLoadNode *node;
    char *base;
    struct DotrModelLoadHeader *desc;
    unsigned char unknown_140[0x38];
    int heads[8];
    unsigned char unknown_198[0x48];
    signed char motion[4];
    float radius;
    float scale;
    unsigned char unknown_1ec[6];
    signed char index;
    signed char kind;
    short id;
    unsigned short look : 14;
    unsigned char unknown_1f8[6];
    signed char level;
    unsigned char unknown_1ff[7];
    unsigned short loaded_id;
    unsigned char unknown_208[4];
    signed char unknown_bit_0 : 3;
    signed char loading : 1;
};
extern struct DotrModelLoadObject *D_0031ABB0_1e8bf0[84];
extern unsigned short D_002CDF4C[];
extern char D_002CFA17_1e8bf0[];
extern char D_002CFA2A[];
extern char *func_001FFF90_b(const char *label);
extern void func_001F3910_b(int a, int b, int c);

void lSzModel_LoadCB(int index)
{
    struct DotrModelLoadObject *obj;
    struct DotrModelLoadNode *node;
    int i;
    index &= 0x3ff;
    if (index < 0 || index >= 84) return;
    obj = D_0031ABB0_1e8bf0[index];
    if (obj == 0) return;
    obj->loading = 0;
    if (obj->base == 0) return;
    obj->index = index;
    

    if (obj->kind != 4) if (obj->kind != 5) if (obj->kind != 6) goto skip;
    {
        obj->loaded_id = obj->id;
        obj->look = D_002CDF4C[D_002CD8A0[obj->id]] & 0x3fff;
    }
skip:
    node = (struct DotrModelLoadNode *)(obj->base + obj->desc->node_offset);
    obj->node = node;
    obj->level = obj->desc->flags >> 6;
    lSzModel_GetGNode(index, -1, &obj->desc->gnode_flag);
    obj->pos[0] = node->x;
    obj->pos[1] = node->y;
    obj->pos[2] = node->z;
    obj->pos[3] = 1.0f;
    obj->radius = node->radius;
    obj->scale = 40.0f / obj->radius;
    if (obj->scale > 1.0f) obj->scale = 1.0f;
    if (obj->scale < 0.3f) obj->scale = 0.3f;
    if (obj->heads[obj->motion[0]] == 0) {
        obj->motion[0] = 0;
        for (i = 0; i < 8; i++) {
            if (obj->heads[i] != 0) {
                obj->motion[0] = i;
                break;
            }
        }
    }
    for (i = 1; i < 4; i++) {
        if (obj->motion[i] >= 0 && obj->heads[obj->motion[i]] == 0) {
            obj->motion[i] = obj->motion[0];
        }
    }
    if (obj->kind != 4) if (obj->kind != 5) if (obj->kind != 6) return;
    {
        func_001FFF90_b(D_002CFA17_1e8bf0);
        func_001FFF90_b(D_002CFA2A);
        ((struct DotrModelLoadHeader *)obj->base)->flags &= ~0x400;
        func_001F3910_b(1, obj->id, 0);
    }
}

typedef struct {
    u8 pad0[0xC];
    u16 count;
} Res_001E8E90;

typedef struct {
    u8 pad0[4];
    u32 flags;
} Sub_001E8E90;

typedef struct {
    u8 pad000[0x138];
    Sub_001E8E90 *sub;
    u8 pad13C[0x30];
    Res_001E8E90 *res0;
    Res_001E8E90 *res1;
    u8 pad174[0x8E];
    u16 cur;
    u16 last;
} Obj_001E8E90;

typedef struct {
    u8 pad0[0x14];
    Res_001E8E90 *res;
    u8 pad18[4];
    u32 bits;
} Req_001E8E90;

void lSzModel_LoadCameraCB(void *arg0, s32 arg1) {
    Req_001E8E90 *req = arg0;
    s32 second;
    Obj_001E8E90 *obj;
    s32 index;

    index = req->bits & 0x7F;
    second = req->bits & 0x80;
    if (index < 0 || index >= 0x54) {
        return;
    }
    obj = (Obj_001E8E90 *)D_0031ABB0[index];
    if (obj == NULL) {
        return;
    }
    if (obj->sub == NULL) {
        SzMem_Free((s32)req->res);
        arg1 = 0;
    }
    if (arg1 == 0) {
        if (second) {
            obj->res1 = NULL;
        } else {
            obj->res0 = NULL;
        }
        return;
    }
    if (second) {
        obj->res1 = req->res;
        obj->sub->flags &= ~0x100000;
    } else {
        obj->res0 = req->res;
        obj->cur = obj->last = obj->res0->count - 1;
        obj->sub->flags &= ~0x80000;
    }
}

typedef struct {
    s32 data;
    s32 unk04;
    s32 additional;
    s32 resolved;
} Entry_001E8FA0;

s32 SzModel_BindTextureFile(s32 arg0) {
    Obj_0031ABB0 *obj;
    Entry_001E8FA0 *entry;
    s32 count;
    s32 i;
    void *directory;
    s32 base;
    u8 *table;

    if ((arg0 < 0) || (arg0 >= 0x54)) {
        return 0;
    }
    obj = D_0031ABB0[arg0];
    if (obj == NULL) {
        return 0;
    }
    base = *(s32 *)&obj->pad040[0xF8];
    if (base == 0) {
        return 1;
    }
    directory = *(void **)&obj->pad040[0xFC];
    if (*(s32 *)((u8 *)directory + 0x2C) == 0) {
        return 1;
    }
    i = 0;
    table = (u8 *)(base + *(s32 *)((u8 *)directory + 0x28));
    count = *(s32 *)table;
    entry = (Entry_001E8FA0 *)(table + 0x10);
    for (; i < count; i++, entry++) {
        if (entry->data != 0) {
            entry->data = *(s32 *)&obj->pad040[0xF8] + entry->data;
            RhText_BindAddress(entry->data);
            if (entry->additional != 0) {
                entry->additional = *(s32 *)&obj->pad040[0xF8] + entry->additional;
            }
            entry->resolved = 0;
        }
    }
    return 1;
}

typedef int DotrObjectWord;
struct DotrObjPackEntry { DotrObjectWord a; DotrObjectWord b; DotrObjectWord c; DotrObjectWord d; };
struct DotrObjPackDesc { unsigned char unknown_00[0x28]; DotrObjectWord unknown_28; DotrObjectWord unknown_2c; };
struct DotrObjPackTable { int count; int pad[3]; struct DotrObjPackEntry entries[1]; };
struct DotrObjPackView { unsigned char unknown_00[0x138]; DotrObjectWord base; struct DotrObjPackDesc *desc; };
struct DotrResourceSubmitRecord;
struct DotrLoadObject {
    unsigned char unknown_000[312];
    int unknown_138;
    int unknown_13c;
    int main_part;
    int parts[8];
    unsigned char unknown_164[143];
    signed char kind;
    short number;
};
extern struct DotrLoadObject *D_0031ABB0_1e90b0[84];
extern char *D_00292480_1e90b0[];
extern char D_002CFA17_1e90b0[];
extern char *func_001FFF90_b(const char *label);
struct DotrResourceSubmitRecord;
extern char D_002CFA30[];
extern char D_002CFA3A[];
extern char D_002CFA3F[];
struct DotrResourceQueueRecord {
    int status;
    short selector;
    short priority;
    unsigned char unknown_008[28];
};
typedef char DotrResourceRecordSizeMustBe36[(sizeof(struct DotrResourceQueueRecord) == 36) ? 1 : -1];
char *func_001FFF90_b(const char *label);
struct DotrResourceSubmitRecord;
typedef void (*DotrResourceSubmitCallback)(struct DotrResourceSubmitRecord *record, int completed);
struct DotrResourceSubmitRecord {
    int status;
    short selector;
    short priority;
    signed int byte_size : 31;
    signed int flag_008 : 1;
    signed int byte_offset : 31;
    signed int flag_00c : 1;
    signed int unknown_010 : 31;
    signed int sector_mode : 1;
    int unknown_014;
    DotrResourceSubmitCallback callback;
    int unknown_01c;
    int handle;
};
struct DotrResourceQueueRecord *func_001FEC70_b(int type, char *name, int unknown_014, int byte_size,
                                              DotrResourceSubmitCallback callback, int unknown_01c);

int SzModel_LoadTextureFile(int index)
{
    char format[128];
    char name[128];
    char anim[128];
    struct DotrLoadObject *obj;
    struct DotrObjPackView *view;
    struct DotrObjPackTable *table;
    struct DotrObjPackEntry *entry;
    char *base;
    int number;
    int count;
    int i;
    char *kind;
    

    if (index < 0 || index >= 84) {
        return 0;
    }
    obj = D_0031ABB0_1e90b0[index];
    if (obj == 0) {
        return 0;
    }
    base = func_001FFF90_b(D_002CFA17_1e90b0);
    number = obj->number;
    view = (struct DotrObjPackView *)obj;
    if (view->base == 0) {
        return 1;
    }
    if (view->desc->unknown_2c == 0) {
        return 1;
    }
    kind = D_00292480_1e90b0[obj->kind];
    table = (struct DotrObjPackTable *)(view->base + view->desc->unknown_28);
    count = table->count;
    entry = table->entries;
    func_0019B648(format, D_002CFA30, base, kind);
    for (i = 0; i < count; i++) {
        func_0019B648(name, format, number, &entry[i]);
        func_0019B9D0(name, D_002CFA3A);
        func_0019B648(anim, format, number, &entry[i]);
        func_0019B9D0(anim, D_002CFA3F);
        entry[i].a = 0;
        entry[i].c = 0;
        entry[i].d = 0;
        func_001FEC70_b(index, name, 0, -1, lSzModel_LoadTextureFileCB, ((unsigned int)(DotrObjectWord)entry & 0x3ffffff) | ((i & 0x3f) << 26));
        func_001FEC70_b(index, anim, 0, -1, lSzModel_LoadTexAnimFileCB, ((unsigned int)(DotrObjectWord)entry & 0x3ffffff) | ((i & 0x3f) << 26));
    }
    return 1;
}

typedef struct Object_001E9280 {
    u8 pad_00[0x14];
    s32 value;
    u8 pad_18[4];
    s32 packed;
} Object_001E9280;

void lSzModel_LoadTextureFileCB(void *arg0, s32 arg1) {
    Object_001E9280 *object = arg0;
    s32 packed = object->packed;
    s32 *entry = (s32 *)(packed & 0x03FFFFFF);

    packed >>= 26;
    if (arg1 != 0) {
        entry = (s32 *)((u8 *)entry + packed * 0x10);
        *entry = object->value;
        RhText_BindAddress(*entry);
    }
}

typedef struct Slot_001E92C0 {
    s32 key;
    s32 unk04;
    u8 *data;
    s32 unk0C;
} Slot_001E92C0;

typedef struct State_001E92C0 {
    u8 unk00[8];
    signed int length : 31;
    unsigned int flag : 1;
    u8 unk0C[8];
    u8 *data;
    u8 unk18[4];
    s32 packed;
} State_001E92C0;


void lSzModel_LoadTexAnimFileCB(void *arg0, s32 arg1) {
    void SzMem_Free(u8 *);
    Slot_001E92C0 *slot;
    u8 *buffer;
    s32 index;
    State_001E92C0 *state = arg0;

    slot = (Slot_001E92C0 *)(state->packed & 0x3FFFFFF);
    index = state->packed >> 26;
    if (arg1 != 0) {
        slot += index;
        slot->data = state->data;
        buffer = slot->data;
        if (buffer != NULL) {
            buffer[state->length - 1] = 0;
            slot->data = lSzModel_TexAnimConv(slot->key, buffer);
            SzMem_Free(buffer);
        }
    }
}

typedef union B3_001E9340 {
    u8 raw;
    struct {
        s8 a : 2;
        s8 b : 6;
    } s;
    struct {
        u8 c : 1;
        u8 : 7;
    } u;
} B3_001E9340;

typedef union V6_001E9340 {
    u16 w;
    struct {
        u8 lo;
        u8 hi;
    } b;
} V6_001E9340;

typedef struct Entry_001E9340 {
    u8 last : 1;
    u8 plain : 1;
    u8 kind : 3;
    u8 align : 3;
    u8 mask;
    u8 lo : 4;
    u8 hi : 4;
    B3_001E9340 b3;
    u16 v4;
    V6_001E9340 v6;
    u16 x8;
    u16 xA;
    u16 xC;
    u16 xE;
    u16 x10;
    u16 x12;
    s32 x14;
} Entry_001E9340;

typedef struct Hdr_001E9340 {
    u8 pad[0x44];
    u16 w;
    u16 h;
} Hdr_001E9340;

#define MAX_001E9340(a, b) ((a) > (b) ? (a) : (b))
#define MIN_001E9340(a, b) ((a) < (b) ? (a) : (b))
#define CLAMP_001E9340(x, lo, hi) MIN_001E9340(MAX_001E9340(x, lo), hi)

extern char D_002CFA72[];
extern char D_002CFA75[];
extern char D_002CFAA2[];
extern char D_002CFAC2[];
extern char D_002CFAF2[];
extern char D_002CFB16[];
extern char D_002CFB18[];
extern char D_002CFB32[];
extern char D_002CFB34[];
extern char D_002CFB3A[];
extern char D_002CFB3C[];
extern char D_002CFB40[];
extern char D_002CFB45[];
extern char D_002CFB4B[];
extern char D_002CFB4D[];
extern char *D_00292F40[];

u8 *lSzModel_TexAnimConv(s32 arg0, u8 *arg1) {
    char buf[0x400];
    char name[0x80];
    char flags[0x80];
    char place[0x80];
    char size[0x80];
    s32 x8;
    s32 xA;
    s32 xC;
    s32 xE;
    s32 x10;
    s32 x12;
    s32 a4;
    s32 b4;
    s32 b6;
    s32 c4;
    s32 c6;
    s32 d4;
    s32 d6;
    s32 e4;
    s32 e6;
    s32 sizeX;
    s32 sizeY;
    s32 count;
    s32 i;
    s32 kind;
    char **names;
    char *c;
    char *line;
    Entry_001E9340 *e;
    char *p;
    Entry_001E9340 *entries;
    char *tok;
    Hdr_001E9340 *hdr;

    line = buf;
    hdr = (Hdr_001E9340 *)(arg0 + 0x10);
    p = line;
    count = 0;
    tok = func_0019D430((char *)arg1, D_002CFA72);
    while (tok != NULL) {
        if (*(u8 *)tok != '#') {
            func_0019BDD8(p, tok);
            p += func_0019BEF0(tok) + 1;
            count++;
        }
        tok = func_0019D430(NULL, D_002CFA72);
    }
    entries = count > 0 ? (Entry_001E9340 *)SzMem_Alloc(count * 24) : NULL;
    if (entries == NULL) {
        e = (Entry_001E9340 *)arg1;
        e->last = 1;
        e->lo = 0;
        e->hi = 0;
        return 0;
    }
    e = entries;
    for (i = 0; i < count; i++) {
        e->last = 1;
        e->lo = 0;
        e->hi = 0;
        kind = 0;
        names = D_00292F40;
        do {
            if (strncasecmp(line, *names, func_0019BEF0(*names)) == 0) {
                break;
            }
            kind++;
            names++;
        } while (kind < 7);
        switch (kind) {
        case 0:
        case 1:
            if (sscanf(line, D_002CFA75, name, flags, place, size, &a4, &x8, &xA, &xC, &xE, &x10, &x12) < 11) {
                scePrintf(D_002CFAA2, name);
                goto next;
            }
            e->b3.raw = 0;
            e->v4 = CLAMP_001E9340(a4, 1, 0xFFFF);
            break;
        case 2:
        case 3:
            if (sscanf(line, D_002CFAC2, name, flags, place, size, &b4, &b6, &x8, &xA, &xC, &xE, &x10, &x12) < 12) {
                scePrintf(D_002CFAA2, name);
                goto next;
            }
            e->b3.s.a = 1;
            e->b3.s.b = 0;
            e->v4 = CLAMP_001E9340(b4, 1, 0xFFFF);
            e->v6.w = CLAMP_001E9340(b6, 1, 0xFFFF);
            break;
        case 6:
            if (sscanf(line, D_002CFAF2, name, flags, &c4, &c6, &x8, &xA, &xC, &xE, &x10, &x12) < 10) {
                scePrintf(D_002CFAA2, name);
                goto next;
            }
            func_0019BDD8(place, D_002CFB16);
            e->b3.u.c = 0;
            e->v4 = CLAMP_001E9340(c4, 1, 0xFFFF);
            e->v6.b.lo = CLAMP_001E9340(c6, 0, 0xFF);
            e->v6.b.hi = 0;
            break;
        case 5:
            if (sscanf(line, D_002CFAF2, name, flags, &d4, &d6, &x8, &xA, &xC, &xE, &x10, &x12) < 10) {
                scePrintf(D_002CFAA2, name);
                goto next;
            }
            func_0019BDD8(place, D_002CFB16);
            e->b3.u.c = 0;
            e->v4 = CLAMP_001E9340(d4, 1, 0xFFFF);
            e->v6.b.lo = CLAMP_001E9340(d6, 0, 0xFF);
            e->v6.b.hi = 0;
            break;
        case 4:
            if (sscanf(line, D_002CFAF2, name, flags, &e4, &e6, &x8, &xA, &xC, &xE, &x10, &x12) < 10) {
                scePrintf(D_002CFAA2, name);
                goto next;
            }
            func_0019BDD8(place, D_002CFB16);
            e->v4 = CLAMP_001E9340(e4, 1, 0xFFFF);
            e->v6.w = CLAMP_001E9340(e6, 1, 0xFFFF);
            break;
        default:
            scePrintf(D_002CFB18);
            goto next;
        }
        e->kind = kind;
        e->align = 0;
        if (strcasecmp(place, D_002CFB16) == 0) {
            e->align = 0;
        } else if (strcasecmp(place, D_002CFB32) == 0) {
            e->align = 1;
        } else if (strcasecmp(place, D_002CFB34) == 0) {
            e->align = 2;
        } else if (strcasecmp(place, D_002CFB34 + 3) == 0) {
            e->align = 3;
        } else if (strcasecmp(place, D_002CFB3A) == 0) {
            e->align = 0;
        } else if (strcasecmp(place, D_002CFB3C) == 0) {
            e->align = 1;
        } else if (strcasecmp(place, D_002CFB3C + 2) == 0) {
            e->align = 2;
        } else if (strcasecmp(place, D_002CFB40) == 0) {
            e->align = 3;
        } else if (strcasecmp(place, D_002CFB40 + 2) == 0) {
            e->align = 4;
        }
        e->lo = 1;
        e->hi = 1;
        switch (e->align) {
        case 0:
        case 2:
            e->lo = CLAMP_001E9340(atoi(size), 1, 0xF);
            break;
        case 1:
        case 3:
            e->hi = CLAMP_001E9340(atoi(size), 1, 0xF);
            break;
        case 4:
            sizeX = 1;
            sizeY = 1;
            sscanf(size, D_002CFB45, &sizeX, &sizeY);
            e->lo = CLAMP_001E9340(sizeX, 1, 0xF);
            e->hi = CLAMP_001E9340(sizeY, 1, 0xF);
            break;
        }
        e->mask = 0;
        e->plain = 1;
        if (func_0019BC90(flags, D_002CFB4B) == 0) {
            e->mask = 0xFF;
            e->plain = 0;
        } else if (func_0019BC90(flags, D_002CFB4D) == 0) {
            e->mask = 0xFF;
        } else {
            kind = 0;
            if (kind < (u32)func_0019BEF0(flags)) {
                c = flags;
                do {
                    if (*c >= 'A' && *c < 'I') {
                        e->mask |= 1 << (*(u8 *)c - 'A');
                        e->plain = 0;
                    } else if (*c >= 'a' && *c < 'i') {
                        e->mask |= 1 << (*(u8 *)c - 'a');
                    }
                    c++;
                    kind++;
                } while (kind < (u32)func_0019BEF0(flags));
            }
        }
        e->last = (i + 1 >= count) ? 1 : 0;
        e->x8 = CLAMP_001E9340(x8, 1, hdr->w);
        e->xA = CLAMP_001E9340(xA, 1, hdr->h);
        e->xC = CLAMP_001E9340(xC, 0, hdr->w - 1);
        e->xE = CLAMP_001E9340(xE, 0, hdr->h - 1);
        e->x10 = CLAMP_001E9340(x10, 0, hdr->w - 1);
        e->x12 = CLAMP_001E9340(x12, 0, hdr->h - 1);
        e->x14 = 0;
        e++;
    next:
        line += func_0019BEF0(line) + 1;
    }
    return (u8 *)entries;
}

s32 SzModel_LoadEffectTextureFile(s32 arg0) {
    extern u8 D_002CFA17[];
    extern u8 D_002CFB4F[];
    extern u8 D_002CFB64[];
    extern s32 D_00292480[];
    extern void func_0019B648();
    extern s32 SzFile_ReadRequest();
    u8 buf1[0x80];
    u8 buf2[0x80];
    s32 s0;
    s32 s1;
    u8 *obj;
    s32 s4;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    obj = (u8 *)D_0031ABB0[arg0];
    if (obj == NULL) {
        return 0;
    }
    s0 = (s32)SzFile_GetEnv((s32)D_002CFA17);
    s1 = *(s16 *)(obj + 0x1F4);
    if (*(s32 *)(obj + 0x138) == 0) {
        return 1;
    }
    s4 = D_00292480[*(s8 *)(obj + 0x1F3)];
    *(s32 *)(obj + 0x140) = 0;
    func_0019B648(buf1, D_002CFB4F, s0, s4);
    func_0019B648(buf2, buf1, s1, s1);
    SzFile_ReadRequest(arg0, buf2, 0, -1, lSzModel_LoadEffectTextureFileCB, (s32)(obj + 0x140));
    func_0019B648(buf1, D_002CFB64, s0, s4);
    s0 = 0;
    do {
        *(s32 *)(obj + 0x144) = 0;
        func_0019B648(buf2, buf1, s1, s1, s0);
        SzFile_ReadRequest(arg0, buf2, 0, -1, lSzModel_LoadEffectTextureFileCB, (s32)(obj + 0x144));
        s0 += 1;
        obj += 4;
    } while (s0 < 8);
    return 1;
}

void lSzModel_LoadEffectTextureFileCB(void *arg0, s32 arg1) {
    s32 *temp_v1;

    temp_v1 = *(s32 **)((u8 *)arg0 + 0x1C);
    if (arg1 != 0) {
        *temp_v1 = *(s32 *)((u8 *)arg0 + 0x14);
        RhText_BindAddress(*temp_v1);
    }
}

typedef struct {
    s32 id;
    s32 unused;
    s32 enabled;
    s32 count;
} Entry_001EA2A0;

typedef struct {
    u8 unused[0x28];
    s32 offset;
    s32 present;
} Header_001EA2A0;


s32 SzModel_LoadTexture_Pipe(s32 current, s32 object, void *data, s32 *size) {
    extern s32 SzText_InitClutManage();
    s32 cursor;
    s32 count;
    s32 index;
    Entry_001EA2A0 *entry;
    s32 base;
    s32 entry_size;
    s32 *table;
    Header_001EA2A0 *header;

    if (size != NULL) {
        *size = 0;
    }
    if (data == NULL) {
        return current;
    }
    header = (Header_001EA2A0 *)((u8 *)data + 0x10);
    if (header->present == 0) {
        return current;
    }
    table = (s32 *)((u8 *)data + header->offset);
    count = *table;
    entry = (Entry_001EA2A0 *)((u8 *)table + 0x10);
    base = cursor = RhBase_GetUserGsAddress();
    cursor += SzText_InitClutManage(cursor, 2);
    for (index = 0; index < count; index++, entry++) {
        if (entry->id != 0) {
            current = SzText_Load_Pipe(current, entry->id, cursor, (s32)&entry_size);
            if (entry->enabled != 0 && SzModel_GetPauseFlag(object) == 0 && SzModel_GetStoneFlag(object) == 0) {
                current = SzModel_LoadTexAnim_Pipe(current, object, cursor, entry);
                entry->count++;
            }
            cursor += entry_size;
        }
    }
    if (size != NULL) {
        *size = cursor - base;
    }
    return RhText_SetTextureFlush(current);
}

typedef int DotrTexAnimWord;
typedef unsigned long DotrTexAnimLong;
struct DotrTexAnimTexture {
    char unknown_00[0x40];
    unsigned short psm;         
    unsigned short unknown_42;
    unsigned short width;       
};
struct DotrTexAnimHead {
    char unknown_00[16];
    struct DotrTexAnimTexture tex;
};
struct DotrTexAnimEntry {
    unsigned char last : 1;     
    unsigned char count : 1;    
    unsigned char type : 3;     
    unsigned char mode : 3;     
    unsigned char mask;         
    unsigned char cols : 4;     
    unsigned char rows : 4;
    union {
        signed char cell;       
        struct {
            signed char dir : 2;
            signed char pos : 6;
        } swing;                
        struct {
            unsigned char on : 1;
        } gate;                 
    } u3;                       
    union {
        struct {
            unsigned short a, b;
        } h;
        struct {
            unsigned short a;
            unsigned char limit, time;
        } b;
    } u4;                       
    unsigned short w, h;        
    unsigned short sx, sy;      
    unsigned short dx, dy;      
    int counter;                
};
struct DotrTexAnimRecord {
    struct DotrTexAnimHead *head;
    int unknown_4;
    struct DotrTexAnimEntry *entries;
};
extern int func_001F13F0_b(int index);

int SzModel_LoadTexAnim_Pipe(int cursor, int index, int position, void *record_v)
{
    struct DotrTexAnimRecord * record = record_v;
    struct DotrTexAnimEntry *e;
    DotrTexAnimLong *p = (DotrTexAnimLong *)cursor;
    DotrTexAnimLong *start;
    struct DotrTexAnimTexture *tex;
    int n;
    int step;
    int last;
    int cells;
    int anim;
    unsigned int frame;
    int cell;

    tex = &record->head->tex;
    e = record->entries;
    n = tex->width >> 6;
    start = p;
    n = (n > 1) ? n : 1;
    step = SzModel_GetPauseFlag(index) ? 0 : 1;
    for (last = 0; !last; e++) {
        cells = e->cols * e->rows;
        anim = func_001F13F0_b(index);
        frame = func_001A23B0(SzModel_GetAnimFrame(index));
        cell = 0;
        if (e->count) {
            frame = e->counter;
            e->counter = frame + step;
        }
        if (e->last) {
            last = 1;
        }
        if (cells == 0) {
            continue;
        }
        if (!(e->mask & (1 << anim))) {
            continue;
        }
        if (e->type == 0 || e->type == 2) {
            cells++;
        }
        switch (e->type) {
        case 0:
        case 1:
        {
            unsigned short span = e->u4.h.a;
            cell = e->u3.cell;
            if (step && frame && frame % span == 0) {
                cell = (cell + 1) % cells;
                e->u3.cell = cell;
            }
            break;
        }
        case 2:
        case 3: {
            unsigned short span;
            int dir = e->u3.swing.dir;
            if (dir > 0) {
                span = e->u4.h.a;
            } else {
                span = e->u4.h.b;
            }
            cell = e->u3.swing.pos;
            if (step && frame && frame % span == 0) {
                cell += dir;
                cell = ((cell > 0 ? cell : 0) < cells - 1) ? (cell > 0 ? cell : 0) : cells - 1;
                e->u3.swing.pos = cell;
                if (cell <= 0 || cell >= cells - 1) {
                    e->u3.swing.dir = -e->u3.swing.dir;
                    e->counter = 1;
                }
            }
            break;
        }
        case 6:
            if (e->u3.gate.on) {
                e->u4.b.time += step;
                if (e->u4.b.time < e->u4.b.limit) {
                    break;
                }
                e->u3.gate.on = 0;
                continue;
            }
            if (frame % e->u4.h.a) {
                continue;
            }
            if (step && e->u4.b.limit) {
                e->u3.gate.on = 1;
                e->u4.b.time = 0;
            }
            break;
        case 5:
            if (e->u3.gate.on) {
                if (frame == e->u4.h.a) {
                    break;
                }
                e->u4.b.time += step;
                if (e->u4.b.time < e->u4.b.limit) {
                    break;
                }
                e->u3.gate.on = 0;
                continue;
            }
            if (frame != e->u4.h.a) {
                continue;
            }
            if (step && e->u4.b.limit) {
                e->u3.gate.on = 1;
                e->u4.b.time = 0;
            }
            break;
        case 4:
            if (frame < e->u4.h.a) {
                continue;
            }
            if (frame > e->u4.h.b) {
                continue;
            }
            break;
        }
        if (e->type == 0 || e->type == 2) {
            if (cell == 0) {
                continue;
            }
            cell--;
        }
        if (e->sx == e->dx && e->sy == e->dy) {
            if (cell == 0) {
                continue;
            }
        }
        if (e->mode == 2 || e->mode == 3) {
            cell = -cell;
        }
        p[1] = 0;
        p[0] = 0;
        ((unsigned char *)p)[3] = 0x10;
        p[2] = 0x1000000000008004;
        p[3] = 0xe;
        p[4] = (DotrTexAnimLong)position | ((DotrTexAnimLong)n << 16) | ((DotrTexAnimLong)tex->psm << 24) | ((DotrTexAnimLong)position << 32) |
               ((DotrTexAnimLong)n << 48) | ((DotrTexAnimLong)tex->psm << 56);
        p[5] = 0x50;
        p[6] = (DotrTexAnimLong)(e->sx + e->w * (cell % e->cols)) | ((DotrTexAnimLong)(e->sy + e->h * (cell / e->cols)) << 16) |
               ((DotrTexAnimLong)e->dx << 32) | ((DotrTexAnimLong)e->dy << 48);
        p[7] = 0x51;
        p[8] = (DotrTexAnimLong)e->w | ((DotrTexAnimLong)e->h << 32);
        p[9] = 0x52;
        p[10] = 2;
        p[11] = 0x53;
        p += 12;
    }
    if (p != start) {
        unsigned short q = ((p - start) >> 1) - 1;
        *(unsigned short *)start = q;
        ((int *)start)[2] = 0x11000000;
        ((int *)start)[3] = q | 0x51000000;
    }
    return (DotrTexAnimWord)p;
}

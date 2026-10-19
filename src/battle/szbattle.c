/* 3D battles (SzBattle_*). The first three functions are the duel screen's (SzDuel_*): the battle functions after them match only with them in front. Starts where it does for the compiler (see README, How the files are split). */

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

/* Absolute value. */
static inline s32 abs_001E4570(s32 value) {
    return value >= 0 ? value : -value;
}

/* Draws the hand cursor (the pointing hand) at (x, y), turned by `angle`. */
s32 lSzDuel_OpenHandCursor_Pipe(s32 packet, s32 angle, s32 x, s32 y) {
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

    state = (State_001E4570 *)duelState.b;
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
    RhGeom_MulMatrixVectorArray((void *)SCRATCHPAD_ADDR, 0, &corners, 8);
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
    sprite.corners[0].xyz.x = (originX << 4) + (s32)(16.0f * ((f32 *)SCRATCHPAD_ADDR)[0]);
    sprite.corners[0].xyz.y = (originY << 4) + (s32)(16.0f * ((f32 *)SCRATCHPAD_ADDR)[1]);
    sprite.corners[1].xyz.x = (originX << 4) + (s32)(16.0f * ((f32 *)SCRATCHPAD_ADDR)[4]);
    sprite.corners[1].xyz.y = (originY << 4) + (s32)(16.0f * ((f32 *)SCRATCHPAD_ADDR)[5]);
    sprite.corners[2].xyz.x = (originX << 4) + (s32)(16.0f * ((f32 *)SCRATCHPAD_ADDR)[8]);
    sprite.corners[2].xyz.y = (originY << 4) + (s32)(16.0f * ((f32 *)SCRATCHPAD_ADDR)[9]);
    sprite.corners[3].xyz.x = (originX << 4) + (s32)(16.0f * ((f32 *)SCRATCHPAD_ADDR)[12]);
    sprite.corners[3].xyz.y = (originY << 4) + (s32)(16.0f * ((f32 *)SCRATCHPAD_ADDR)[13]);
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
    sprite.corners[0].xyz.x = (originX << 4) + (s32)(16.0f * ((f32 *)SCRATCHPAD_ADDR)[16]);
    sprite.corners[0].xyz.y = (originY << 4) + (s32)(16.0f * ((f32 *)SCRATCHPAD_ADDR)[17]);
    sprite.corners[1].xyz.x = (originX << 4) + (s32)(16.0f * ((f32 *)SCRATCHPAD_ADDR)[20]);
    sprite.corners[1].xyz.y = (originY << 4) + (s32)(16.0f * ((f32 *)SCRATCHPAD_ADDR)[21]);
    sprite.corners[2].xyz.x = (originX << 4) + (s32)(16.0f * ((f32 *)SCRATCHPAD_ADDR)[24]);
    sprite.corners[2].xyz.y = (originY << 4) + (s32)(16.0f * ((f32 *)SCRATCHPAD_ADDR)[25]);
    sprite.corners[3].xyz.x = (originX << 4) + (s32)(16.0f * ((f32 *)SCRATCHPAD_ADDR)[28]);
    sprite.corners[3].xyz.y = (originY << 4) + (s32)(16.0f * ((f32 *)SCRATCHPAD_ADDR)[29]);
    return ExSortPrim_Pipe(packet, (s32)&sprite, 0, 0);
}

/* Closes the hand cursor. */
void SzDuel_CloseHandCursor(void) {
    HandCursorState = 0x18;
}

typedef struct {
    s8 pad0 : 5;
    s8 flag : 1;
    s8 pad1 : 2;
} Flags;

extern Flags DisplayUIBitfield;

/* Turns the end-of-duel judgement off or on (the tutorial uses it). */
void SzDuel_SetIgnoreJudge(s64 on) {
    DisplayUIBitfield.flag = on;
}

typedef struct {
    s32 entries[2];
    s32 count;
} State_001E4E90;

/* Clears the battle state. */
void SzBattle_Initialize(void) {
    extern State_001E4E90 battleState;
    State_001E4E90 *state = &battleState;
    s32 i;

    RhMem_FillMemory((s8 *)&battleState, 0, 0xC);
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

/* Starts a 3D battle on battle stage `stage`: its lights and fog, which models draw, and its camera file. */
void SzBattle_Init(s32 stage) {
    extern u8 battleStageParams[];
    extern s32 battleLoadedStage;
    extern s32 stageCameraOffsets[];
    extern s32 D_00292174[];
    extern Vec3_001E4F00 D_002921A0;
    extern Vec3_001E4F00 D_002921B0;
    extern char D_002CF730[];
    extern char D_002CF746[];
    extern s32 battleState[];
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

    state = battleState;
    base = battleStageParams + stage * 0xC0;
    vecC = (f32 *)(base + 0xC);
    vec20 = (f32 *)(base + 0x20);
    range = (f32 *)(base + 0xB0);
    vecB8 = (f32 *)(base + 0xB8);
    if (stage == 4) {
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
    if (stage == 4) {
        Vec3_001E4F00 position = D_002921A0;
        Vec3_001E4F00 other;
        position.x = ((f32 *)base)[0];
        position.y = ((f32 *)base)[1];
        other = D_002921B0;
        SzModel_SetIntensity(8, &position.x);
        SzModel_SetFogFlag(9, 1);
        SzModel_SetIntensity(0xC, &other.x);
    }
    if (stage == 2) {
        SzModel_SetFogFlag(9, 0);
    }
    if (stage != battleLoadedStage) {
        battleLoadedStage = stage;
    }
    if (state[2] != 0) {
        SzMem_Free(state[2]);
        state[2] = 0;
    }
    begin = stageCameraOffsets[stage];
    size = D_00292174[stage] - begin;
    func_0019B648(filename, D_002CF730, (s32) SzFile_GetEnv((s32) D_002CF746));
    SzFile_ReadRequestParam(0x400, 1, filename, 0, size, begin, size, lSzBattle_CameraCB, 0);
}

typedef struct {
    u8 padding[8];
    s32 field8;
} State_001E5210;

extern State_001E5210 battleState; /* original: gSzBattle_bl */

/* The battle camera file has loaded (`ok`): keeps its address. */
void lSzBattle_CameraCB(void *request, s32 ok) {
    State_001E5210 *state = &battleState;
    s32 address;

    if (ok != 0) {
        address = *(s32 *)((u8 *)request + 0x14);
    } else {
        address = 0;
    }
    state->field8 = address;
}

/* The battle camera data, or 0 while it loads. */
s32 SzBattle_InqCamera(void) {
    return D_0031AB90;
}

/* The unit ((side << 8) | unit) in battle slot `index`, or -1. */
s32 SzBattle_InqEntry(s32 index) {
    return *(s32 *)&battleState.padding[index * 4];
}

#ifndef GAME_H
/* The game translation unit already declares this global with its local type. */
typedef struct {
    unsigned char padding[8];
    int field8;
} State_001E5210;

extern State_001E5210 battleState; /* original: gSzBattle_bl */
#endif

typedef union {
    __int128 value;
    s32 axis[4];
} Rotation_001E5260;

extern Rotation_001E5260 D_002921C0;

/* Brings unit `unitId` ((side << 8) | unit) into the 3D battle on battle side `side` (0 near, 1 far). */
void SzBattle_Entry(s32 side, s32 unitId) {
    extern s32 SzModel_GetModelNo();
    s32 *states = (s32 *)&battleState;
    s32 unitSide = unitId >> 8;
    s32 unitIndex = unitId & 0xFF;
    void *card;
    s32 model;
    Rotation_001E5260 rotation;
    f32 position[4];
    f32 offset;

    card = (void *)SzDuel_GetUnit(unitSide, unitIndex);
    rotation = D_002921C0;
    rotation.axis[1] = (side != 0) ? 0 : 0x8000;
    if (card != NULL && *(s32 *)card != 0) {
        SzDuel_SetBusyFlag(unitSide, unitIndex, 1);
        model = *((u8 *)card + 0x46);
        SzSound_TransferSEGrp(side + 2, SzModel_GetModelNo(model), 0);
        SzModel_SetRot(model, &rotation);
        SzModel_GetPos(model, position);
        position[0] = 0.0f;
        if (side != 0) {
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
        states[side] = unitId;
    }
}

typedef struct {
    s32 entries[2];
    s32 count;
} Slots_001E53C0;

typedef struct {
    s32 v[4];
} Rot_001E53C0 __attribute__((aligned(16)));

extern Rot_001E53C0 D_002921D0;

/* Sends side `side`'s monster back from the 3D battle to the board (`restore` puts its model back as it was). */
void SzBattle_Return(s32 side, s32 restore) {
    extern s32 SzEffect_ClearRefID2();
    Slots_001E53C0 *state = (Slots_001E53C0 *)&battleState;
    s32 pos;
    s32 hi;
    s32 lo;
    Unit *card;
    s32 model;
    Rot_001E53C0 rot;
    f32 vecA[4];
    f32 vecB[4];

    pos = ((Slots_001E53C0 *)&battleState)->entries[side];
    hi = pos >> 8;
    lo = pos & 0xFF;
    card = (Unit *)SzDuel_GetUnit(hi, lo);
    rot = D_002921D0;
    rot.v[1] = (hi != 0) ? 0 : 0x8000;
    if (card != NULL) {
        model = card->modelId;
        SzEffect_ClearRefID2(pos, 1, &rot);
        SzDuel_SetBusyFlag(hi, lo, 0);
        SzModel_SetScale(model, NULL);
        SzModel_SetRot(model, &rot);
        SzModel_GetPos(model, vecA);
        SzDuel_CalcUnitPos(card->locCol, card->locRow, 0, vecB);
        vecA[0] = vecB[0];
        vecA[2] = vecB[2];
        SzModel_SetPos(model, vecA);
        SzModel_SetDeform(model, 1);
        SzModel_SetDeformRatio(model, 0x20);
        if (restore != 0) {
            SzDuel_SetUnitCtlRateM(hi, lo, 0, 0);
            SzDuel_SetUnitCtlGoalM(hi, lo, 0);
        } else {
            SzModel_SetAnimDirect(model, 0);
            SzModel_SetAnimDir(model, 1);
        }
        SzModel_SetRgba(model, 0, NULL);
        SzModel_SetFilter(model, 1, NULL);
        SzModel_CancelMotionBlur(model);
        SzSound_StopSE(side + 2, -1);
        state->entries[side] = -1;
    }
}

/* Draws the battle stage if it is shown. */
s32 SzBattle_DrawStage_Pipe(s32 packet) {
    if (SzModel_GetDrawFlag(8) != 0) {
        return lSzBattle_DrawStage_Pipe(packet);
    }
    return packet;
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

/* Draws the battle stage for the field type of the battle square (wasteland, grass, sea or the normal stages). */
s32 lSzBattle_DrawStage_Pipe(s32 packet) {
    extern Stage_001E55E0 battleStageParams[];
    extern Camera_001E55E0 D_002921F0;
    extern Vec3_001E55E0 D_00292280;
    extern Vec3_001E55E0 D_00292290;
    extern s32 battleLoadedStage;
    extern s8 chRate;
    extern s8 chFlip;
    extern u8 battleStageSoundOn;
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
    if (battleLoadedStage == 7) {
        if (chRate < 0x3C) {
            t = 0.0f;
        } else {
            t = (chRate - 0x3C) / 4.0f;
        }
        u = 1.0f - t;
        toCamera = &battleStageParams[10].camera;
        fromCamera = &battleStageParams[7].camera;
        toAmbient = &battleStageParams[10].ambient;
        fromAmbient = &battleStageParams[7].ambient;
        toLight = &battleStageParams[10].light;
        fromLight = &battleStageParams[7].light;
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
                chFlip = 1;
            }
            chRate += chFlip;
            if (chRate < 0) {
                chRate = 0;
                chFlip = 0;
            }
            if (chRate < 0x20) {
                battleStageSoundOn = 1;
            }
            if (chRate > 0x40) {
                chRate = 0x40;
                chFlip = -1;
                if (battleStageSoundOn != 0) {
                    if ((s32)(2.0f * (func_0019A5C8() / 2147483648.0f)) != 0) {
                        SzSound_StereoPlaySE(0, 0x22, 0x23);
                    } else {
                        SzSound_StereoPlaySE(0, 0x24, 0x25);
                    }
                    battleStageSoundOn = 0;
                }
            }
        }
    }
    if (battleLoadedStage == 5 || battleLoadedStage == 6) {
        stage = &battleStageParams[battleLoadedStage].camera;
        if (SzModel_GetPauseFlag(8) == 0) {
            if (battleLoadedStage == 6) {
                stage->rotation[1] = (stage->rotation[1] + 0x200) % 0x10000;
            } else {
                stage->rotation[2] = (stage->rotation[2] + 0x200) % 0x10000;
            }
        }
        SzEffect_SetStraightLightForMonster((s32)stage);
        SzEffect_SetStraightLightForBattle((s32)stage);
    }
    if (battleLoadedStage == 8) {
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
            switch (battleLoadedStage) {
            case 1:
                packet = lSzBattle_DrawWasteland_Pipe(packet, id, value);
                break;
            case 3:
                packet = lSzBattle_DrawGrass_Pipe(packet, id, value);
                break;
            case 4:
                packet = lSzBattle_DrawSea_Pipe(packet, id, value);
                break;
            case 7:
                packet = lSzBattle_DrawNormal_Pipe(packet, id, value);
                break;
            default:
                packet = SzModel_DrawWithOutCalc_Pipe(packet, id, 0, 0, 0, 0, 0);
                break;
            }
        }
    }
    for (j = 0; j < 1; j++) {
        id2 = j + 7;
        if (SzModel_IsModelDisp(id2) != 0) {
            packet = SzModel_DrawWithOutCalc_Pipe(packet, id2, 0, 0, 0, 0, 0);
        }
    }
    return packet;
}

/* Draws the wasteland battle stage model `model` (`kind` < 9 adds its second, turned copy). */
s32 lSzBattle_DrawWasteland_Pipe(s32 packet, s32 model, s32 kind) {
    s32 parameters[4];

    packet = SzModel_DrawWithOutCalc_Pipe(packet, model, 0, 0, 0, 0, 0);
    if (kind < 9) {
        SzModel_GetRot(model, parameters);
        parameters[1] = 0x8000;
        packet = SzModel_DrawWithOutCalc_Pipe(packet, model, 0, (s32) parameters, 0, 0, 0);
    }
    return packet;
}

/* Draws the grass battle stage model `model`, with the monsters' fake shadows. */
s32 lSzBattle_DrawGrass_Pipe(s32 packet, s32 model, s32 kind) {
    extern s32 lSzBattle_DrawFakeShadow(s32, s32, s32, f32, f32);
    s32 i;
    s32 *entry;
    s32 result;

    entry = (s32 *)&battleState;
    result = SzModel_DrawWithOutCalc_Pipe(packet, model, 0, 0, 0, 0, 0);
    if (kind == 0) {
        result = lSzBattle_DrawFakeShadow(result, 7, -1, -25.0f, 800.0f);
        i = 0;
        do {
            s32 value = *entry;
            if (value >= 0) {
                /* a unit record; read raw (card[0x46] = its modelId): as a Unit * the float arguments
                   below come out in another order (the compiler's memory, see the README) */
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

/* Degrees to the game's angle units (0x8000 = 180 degrees). */
static inline f32 toAngle_001E5EB0(f32 degrees) {
    return 32768.0f * degrees / 180.0f;
}

/* Draws the sea battle stage model `model`: water, its moving parts, the fake mirror. */
s32 lSzBattle_DrawSea_Pipe(s32 packet, s32 model, s32 kind) {
    extern Part_001E5EB0 *apLocData[];
    extern u8 abLocDataMax[];
    extern Rot_001E5EB0 D_002922A0;
    extern s32 lSzBattle_DrawFakeMirror(s32, s32);
    Rot_001E5EB0 rot;
    s32 i;
    s32 count;
    s32 base;
    Part_001E5EB0 *part;
    s32 idx;
    s32 phase;

    switch (kind) {
    case 0:
        packet = SzModel_DrawWithOutCalc_Pipe(packet, model, 0, 0, 0, 0, 0);
        packet = lSzBattle_DrawFakeMirror(packet, 0xF);
        break;
    case 5:
    case 6:
    case 7:
    case 8:
        count = SzModel_GetAnimFrameMax(model, -1);
        base = (s32)SzModel_GetAnimFrame(model);
        idx = kind - 5;
        part = apLocData[idx];
        for (i = 0; i < abLocDataMax[idx]; i++) {
            rot = D_002922A0;
            rot.x = (s32)toAngle_001E5EB0(part->x);
            rot.y = (s32)toAngle_001E5EB0(part->y);
            phase = (base + part->phase) % count;
            SzModel_SetAnimFrame(model, (f32)phase);
            packet = SzModel_DrawWithOutCalc_Pipe(packet, model, (s32)part, (s32)&rot, 0, 0, 0);
            part++;
        }
        SzModel_SetAnimFrame(model, (f32)base);
        break;
    default:
        packet = SzModel_DrawWithOutCalc_Pipe(packet, model, 0, 0, 0, 0, 0);
        break;
    }
    return packet;
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

/* Draws the other battle stage models (`kind` picks the layout), with the monsters' fake shadows. */
s32 lSzBattle_DrawNormal_Pipe(s32 packet, s32 model, s32 kind) {
    s32 i;
    s32 j;
    s32 *entry = (s32 *)&battleState;
    Quad_001E60E0 scale;

    scale = D_002922B0;
    switch (kind) {
    case 1: {
        Quad_001E60E0 rotation;
        rotation = D_002922C0;
        i = 0;
        do {
            packet = SzModel_DrawWithOutCalc_Pipe(packet, model, 0, (s32)&rotation, (s32)&scale, 0, 0);
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
            packet = SzModel_DrawWithOutCalc_Pipe(packet, model, 0, (s32)&rotation, (s32)&scale, 0, 0);
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
        SzModel_GetPos(model, &position);
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
            packet = SzModel_DrawWithOutCalc_Pipe(packet, model, (s32)&position, (s32)&rotation, (s32)&scale, 0, 0);
            position.f[0] = scale.f[0] * (baseX - 100.0f * signX);
            position.f[2] = baseZ * scale.f[2];
            packet = SzModel_DrawWithOutCalc_Pipe(packet, model, (s32)&position, (s32)&rotation, (s32)&scale, 0, 0);
            position.f[0] = baseX * scale.f[0];
            position.f[2] = scale.f[2] * (baseZ - 100.0f * signZ);
            packet = SzModel_DrawWithOutCalc_Pipe(packet, model, (s32)&position, (s32)&rotation, (s32)&scale, 0, 0);
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
        SzModel_GetPos(model, &position);
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
            packet = SzModel_DrawWithOutCalc_Pipe(packet, model, (s32)&position, (s32)&rotation, (s32)&scale, 0, 0);
            j = 0;
            do {
                distance = 100.0f * (f32)(j + 1);
                position.f[0] = scale.f[0] * (baseX - distance * signX);
                position.f[2] = baseZ * scale.f[2];
                packet = SzModel_DrawWithOutCalc_Pipe(packet, model, (s32)&position, 0, (s32)&scale, 0, 0);
                position.f[0] = baseX * scale.f[0];
                position.f[2] = scale.f[2] * (baseZ - distance * signZ);
                packet = SzModel_DrawWithOutCalc_Pipe(packet, model, (s32)&position, 0, (s32)&scale, 0, 0);
                j++;
            } while (j < 3);
            i++;
        } while (i < 4);
        break;
    }
    default: {
        Quad_001E60E0 rotation;
        rotation = D_00292300;
        packet = SzModel_DrawWithOutCalc_Pipe(packet, model, 0, (s32)&rotation, (s32)&scale, 0, 0);
        break;
    }
    }
    if (kind == 0) {
        packet = lSzBattle_DrawFakeShadow(packet, 7, -1, -13.5f, 400.0f);
        i = 0;
        do {
            s32 value = *entry;
            if (value >= 0) {
                /* a unit record; read raw (card[0x46] = its modelId): as a Unit * the float arguments
                   below come out in another order (the compiler's memory, see the README) */
                u8 *card = (u8 *)SzDuel_GetUnit(value >> 8, value & 0xFF);
                if (card != NULL) {
                    packet = lSzBattle_DrawFakeShadow(packet, card[0x46], -1, -13.5f, 400.0f);
                }
            }
            i++;
            entry++;
        } while (i < 2);
    }
    return packet;
}

typedef struct Quad_001E6650 {
    f32 points[4][4];
} Quad_001E6650;

typedef struct Vec3_001E6650 {
    f32 x;
    f32 y;
    f32 z;
} Vec3_001E6650;

typedef struct Tag_001E6650 {
    u16 count;
    u16 flags;
    u32 padding;
    u64 registers;
} Tag_001E6650;

typedef struct UV_001E6650 {
    u64 u : 14;
    u64 pad0 : 2;
    u64 v : 14;
    u64 pad1 : 34;
} UV_001E6650;

typedef struct Vertex_001E6650 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Vertex_001E6650;

typedef struct Tex0_001E6650 {
    u64 tbp : 14;
    u64 tbw : 6;
    u64 psm : 6;
    u64 tw : 4;
    u64 th : 4;
    u64 tcc : 1;
    u64 rest : 29;
} Tex0_001E6650;

typedef struct Packet_001E6650 {
    u64 tag[2];
    u8 r;
    u8 g;
    u8 b;
    u8 a;
    f32 q;
    u64 uv0;
    Vertex_001E6650 xyz0;
    u64 uv1;
    Vertex_001E6650 xyz1;
    u64 test;
    Tex0_001E6650 tex0;
    u64 tex1;
    u64 clamp;
} Packet_001E6650;

#define ABS_001E6650(x) ((x) >= 0 ? (x) : -(x))
#define RANDOM_001E6650(n) ((s32)((n) * (func_0019A5C8() / 2147483648.0f)))

/* Draws model `model` mirrored on the water as a fake reflection. */
s32 lSzBattle_DrawFakeMirror(s32 arg0, s32 model) {
    extern Quad_001E6650 D_00292310;
    extern Vec3_001E6650 D_00292350;
    extern s16 sTrimX[4];
    extern s16 sTrimY[4];
    extern s16 sFlipX;
    extern s16 sFlipY;
    extern s32 func_0020A470(s32, s32, s32);
    extern s32 func_00207650(s32, void *, s32, s32);
    Quad_001E6650 quad;
    f32 center[4];
    f32 normal[4];
    f32 view[4];
    u8 screen[0x90];
    f32 previous[4];
    Vec3_001E6650 light __attribute__((aligned(16)));
    Packet_001E6650 packet;
    f32 saved;
    u8 color[4];
    u8 *card;
    s32 flag;
    s32 id;
    s32 j;
    s32 state;
    s32 *slot;
    s32 out;
    f32 scale;

    slot = (s32 *)&battleState;
    out = arg0;
    quad = D_00292310;
    light = D_00292350;
    func_00206030(4, &quad, center);
    func_00205E70(4, &quad, normal);
    func_002060F0((f32 *)func_001F9AD0(0), 4, quad.points[0], view);
    if (!(func_0020D1A0(view, normal) <= 0.0f) && func_0020E520(center, normal, screen) != 0) {
        if ((func_001A8720() & 1) == 0) {
            s32 range;
            s32 n;
            s32 dx;
            s32 dy;
            s16 *x;
            s16 *y;
            f32 distance;

            range = 6;
            distance = func_0020D0E0((f32 *)func_001F9AD0(0));
            if (distance <= 600.0f) {
                n = (s32)(600.0f / distance);
                range += (n < 6) ? n : 6;
            }
            if (func_001F3360(8) == 0) {
                for (j = 2; j >= 0; j--) {
                    sTrimX[j + 1] = sTrimX[j];
                    sTrimY[j + 1] = sTrimY[j];
                }
                if (RANDOM_001E6650(3.0f) != 0) {
                    dx = sFlipX;
                } else {
                    dx = 0;
                }
                sTrimX[0] += dx;
                if (RANDOM_001E6650(3.0f) != 0) {
                    dy = sFlipY;
                } else {
                    dy = 0;
                }
                sTrimY[0] += dy;
                if (ABS_001E6650(sTrimX[0]) > range ||
                    (ABS_001E6650(sTrimX[0]) > range >> 1 && RANDOM_001E6650(3.0f) == 0)) {
                    sFlipX = (sTrimX[0] > 0) ? -1 : 1;
                }
                if (sTrimY[0] > range * 2 || sTrimY[0] < 0 ||
                    (sTrimY[0] > range && RANDOM_001E6650(3.0f) == 0)) {
                    sFlipY = (sTrimY[0] > range) ? -1 : 1;
                }
            }
        }
        arg0 = (s32)func_00208530((void *)arg0, 0);
        func_0020A470(0, 10, 0x31);
        out = (s32)func_0020A610((void *)arg0);
        out = (s32)func_0020A870((u8 *)out, NULL);
        func_0020E360(screen);
        out = func_0020EC60(out);
        out = (s32)func_00209F70((void *)out, 0xFFFFFF);
        out = func_0020A0B0(out, 0);
        out = func_001EFA80(out, model, 0, 0, 0, 0, 0);
        out = (s32)func_00209F70((void *)out, 0xFF000000);
        out = func_0020A0B0(out, 1);
        {
        s32 i;
        for (i = 0; i < 2; i++, slot++) {
            if (*slot < 0) {
                continue;
            }
            card = (u8 *)func_001DF540(*slot >> 8, *slot & 0xFF);
            flag = 0;
            saved = 1.0f;
            if (card == NULL) {
                continue;
            }
            id = card[0x46];
            if (func_001F1370(id) == 0) {
                continue;
            }
            state = func_001F2660(id, color);
            func_001F26E0(id, 0, NULL);
            if (color[3] != 0x80) {
                flag = 1;
            }
            if (flag) {
                scale = color[3] / 128.0f;
                (void)scale; /* a use right after the assignment keeps scale at its own statement, as in the original */
                func_001F1E80(id, &saved);
                func_001F1F70(id, scale);
            }
            out = func_001EFA80(out, id, 0, 0, 0, 0, 0);
            if (flag) {
                func_001F1F70(id, saved);
            }
            func_001F26E0(id, state, color);
        }
        }
        out = func_001EFA80(out, 7, 0, 0, 0, 0, 0);
        func_001F1E10(0x10, previous);
        func_001F1EE0(0x10, &light.x);
        out = func_001EFA80(out, 0x10, 0, 0, 0, 0, 0);
        func_001F1EE0(0x10, previous);
        ((Tag_001E6650 *)packet.tag)->flags = 0x26;
        ((Tag_001E6650 *)packet.tag)->count = 5;
        ((Tag_001E6650 *)packet.tag)->registers = 0x42421;
        ((Tag_001E6650 *)packet.tag)->padding = 0;
        ((Tag_001E6650 *)packet.tag)->flags |= 0x800;
        func_002086D0(&packet, 0x8000000048LL);
        packet.r = 0x80;
        packet.g = 0x80;
        packet.b = 0x80;
        packet.a = 0x10;
        packet.q = 1.0f;
        packet.xyz0.z = 0xFFFFF6;
        packet.xyz0.fog = 0;
        packet.xyz1.z = 0xFFFFF6;
        packet.xyz1.fog = 0;
        ((UV_001E6650 *)&packet.uv0)->u = 0x2800;
        ((UV_001E6650 *)&packet.uv0)->v = 0;
        ((UV_001E6650 *)&packet.uv1)->u = 0;
        ((UV_001E6650 *)&packet.uv1)->v = 0x1C00;
        func_0020AA30(&packet.tex0, &packet.tex1);
        packet.tex0.tcc = 0;
        out = (s32)func_0020A760((void *)out);
        out = func_0020F290(out);
        func_0020E970(screen);
        func_0020E360(screen);
        out = func_0020EC60(out);
        out = func_0020A0B0(out, 0);
        packet.xyz0.x = ((sTrimX[0] + 0x6BA) << 4) - 8;
        packet.xyz0.y = 0x7198;
        packet.xyz1.x = ((sTrimX[0] + 0x946) << 4) - 8;
        packet.xyz1.y = ((sTrimY[0] + 0x8E6) << 4) - 8;
        out = func_00207650(out, &packet, 0, 0);
        packet.xyz0.x = ((sTrimX[1] + 0x6BA) << 4) - 8;
        packet.xyz0.y = 0x7198;
        packet.xyz1.x = ((sTrimX[1] + 0x946) << 4) - 8;
        packet.xyz1.y = ((sTrimY[1] + 0x8E6) << 4) - 8;
        out = func_00207650(out, &packet, 0, 0);
        packet.xyz0.x = ((sTrimX[2] + 0x6BA) << 4) - 8;
        packet.xyz0.y = 0x7198;
        packet.xyz1.x = ((sTrimX[2] + 0x946) << 4) - 8;
        packet.xyz1.y = ((sTrimY[2] + 0x8E6) << 4) - 8;
        out = func_00207650(out, &packet, 0, 0);
        packet.xyz0.x = ((sTrimX[3] + 0x6BA) << 4) - 8;
        packet.xyz0.y = 0x7198;
        packet.xyz1.x = ((sTrimX[3] + 0x946) << 4) - 8;
        packet.xyz1.y = ((sTrimY[3] + 0x8E6) << 4) - 8;
        out = func_00207650(out, &packet, 0, 0);
        packet.a = 0x30;
        packet.xyz0.x = 0x6B98;
        packet.xyz0.y = 0x7198;
        packet.xyz1.x = 0x9458;
        packet.xyz1.y = 0x8E58;
        out = func_00207650(out, &packet, 0, 0);
        out = func_0020A0B0(out, 1);
        func_0020A9E0();
        out = (s32)func_00208530((void *)out, 1);
    }
    return out;
}

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

/* Fills a GIF tag header. */
static inline void tag_001E6F90(Header_001E6F90 *p, s32 first, s32 type, u64 value) { p->type = type; p->first = first; p->value = value; p->flags = 0; }
#define MAX_001E6F90(a, b) ((a) > (b) ? (a) : (b))
#pragma opt_dead_assignments off

/* Draws model `model`'s fake shadow on the ground plane. */
s32 lSzBattle_DrawFakeShadow(s32 arg0, s32 model, s32 arg2, f32 fparg0, f32 fparg1) {
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
    /* the header's tail: ExSortNode_Pipe reads TEX0/TEX1 at header + 0x18 for the textured (0x35) header, and on
       the EE saved sits right there. One struct would say so, but it changes the compiler's memory this file's
       float arguments depend on (see the README): a port must keep the two together. */
    s64 saved[3] __attribute__((aligned(8)));
    Range_001E6F90 range __attribute__((aligned(8)));
    s32 alpha;

    plane = D_00292380;
    plane.f[3] = -fparg0;
    alpha = func_001F2980(model, &plane);
    if (func_001F1370(model) == 0) {
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

        opacityScale = (func_001F27A0(model) << 6) >> 7;
        scale = fparg1 / 800.0f;
        scratchpad = (u8 *)SCRATCHPAD_ADDR;
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
        func_001F2050(model, position);
        camera.position[0] = position[0] + camera.direction[0][0] * fparg1;
        camera.position[1] = position[1] + camera.direction[0][1] * fparg1;
        camera.position[2] = position[2] + camera.direction[0][2] * fparg1;
        camera.direction[0][0] *= -1.0f;
        camera.direction[0][1] *= -1.0f;
        camera.direction[0][2] *= -1.0f;
        { f32 h = 448.0f, d = 800.0f, w = 640.0f, cy = 224.0f, cx = 320.0f; func_0020DF40(d, w, h, cx, cy); }
        func_0020E360(&camera);
        count = func_0020EC60((void *)packet);
        func_0020EBA0(matrix);
        func_0020BDE0(matrix, matrix);
        func_0020BAF0((s32)matrix);
        RhGeom_MulMatrixVectorArray((void *)(u32)&points, 0, (void *)(u32)&points, 8);
        func_0020BB50();
        count = func_001EFA80(count, model, 0, 0, 0, 0, 0);
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

/* Ends the 3D battle: sends both monsters back. */
void SzBattle_Term(void) {
    s32 i;

    i = 0;
    do {
        SzBattle_Return(i, 0);
        i += 1;
    } while (i < 2);
}

#include "common.h"

/* The program's entry stub (jumps to the start-up code). */
asm void func_00100000(void) {
    .set noreorder
    nop
}

/* Sony crt0.s _start (the Japanese build has the same code, from an older crt0 that orders the
   bss-clear loop's nops differently). Linker names: _fbss, _end, _gp, _stack, _stack_size, _args, _root. */
extern f32 g_vec_temp[];
extern s32 D_00317EF0;
extern s32 D_0030FFC0;
extern s32 D_12000;
extern s32 D_20000;
extern s32 _stack;

/* Start-up code: clears .bss, sets up the stack, the heap and the thread, calls main. */
asm void func_00100008(void) {
    .set noreorder
    la v0, g_vec_temp
    la v1, D_1FE0000
L_00100018:
    sq zero, 0x0(v0)
    nop
    sltu at, v0, v1
    nop
    nop
    bnez at, L_00100018
    addiu v0, v0, 0x10
    la a0, D_00317EF0
    la a1, _stack
    la a2, D_12000
    la a3, D_0030FFC0
    la t0, func_001000C0
    .word 0x0080E025 /* or gp, a0, zero: the assembler would write paddub */
    addiu v1, zero, 0x3C
    syscall 0
    .word 0x0040E825 /* or sp, v0, zero */
    la a0, D_1FE0000
    la a1, D_20000
    addiu v1, zero, 0x3D
    syscall 0
    jal func_00184540
    nop
    jal FlushCache
    .word 0x00002025 /* or a0, zero, zero */
    ei
    la v0, D_0030FFC0
    lw a0, 0x0(v0)
    jal main
    addiu a1, v0, 0x4
    j func_001847B0
    .word 0x00402025 /* or a0, v0, zero */
}

/* Hand-written tail jump (GCC-style move into the delay slot). */

/* A start-up stub. */
asm void func_001000B8(void) {
    .set noreorder
    j func_001847B0
    .word 0x00002025 /* or a0, zero, zero: the assembler would write paddub */
}

/* Kernel call 0x23 (ExitThread): ends the calling thread. */
asm void func_001000C0(void) {
    .set noreorder
    addiu v1, zero, 0x23
    syscall 0
}

/* The program: starts everything (Main_Init), runs the main loop until it ends, then shuts down. */
s32 main(void) {
    asm {
        la sp, D_912000
    }
    SzMem_Init();
    func_0019B0F8((s32)D_002B8F00, (s32)D_002B8F05, 1);
    func_0019B0F8((s32)D_002B8F07, (s32)D_002B8F05, 1);
    func_0019B0F8((s32)D_002B8F0D, (s32)D_002B8F05, 1);
    func_0019B0F8((s32)D_002B8F13, (s32)D_002B8F18, 1);
    func_0019B0F8((s32)D_002B8F1F, (s32)D_002B8F18, 1);
    func_0019B0F8((s32)D_002B8F27, (s32)D_002B8F18, 1);
    func_0019B0F8((s32)D_002B8F2C, (s32)D_002B8F32, 1);
    if (Main_Init() == 0) {
        return 0;
    }
    Main_Loop();
    Main_Term();
    return 0;
}

/* Starts the hardware and every system: memory, files, pads, sound, renderer, models, text, the game. */
s32 Main_Init(void) {
    SzFile_Init();
    if (RhBase_Init(0, 0xA, 0x31, 0x600000, 0x780000, 0x180000, 0x4000000) == 0) {
        return 0;
    }
    RhBase_SetClearColorEx(0, 0, 0, 0);
    SzGame_ClearGsMem(0xA, 0, 0, 0, 0x400, 0x400);
    SzText_Init();
    SzPad_Init();
    SzSound_Init();
    SzModel_Init();
    SzView_Init();
    SzFade_Init();
    SzGame_Init();
    SzEffect_Init();
    SzDebug_Init();
    SzPad_SetParam(0, 0xC, 1);
    SzPad_SetParam(1, 0xC, 1);
    if (SzView_Create(0) == 0) {
        return 0;
    }
    SzMsg_Initialize();
    SzData_Initialize();
    SzDuel_Initialize();
    SzBattle_Initialize();
    if (lMain_InitModel2() == 0) {
        return 0;
    }
    SzGame_SetMode(0x24, 0);
    SzFade_Entry(1, 0, 1, 0, 0x5A, 0);
    SzFade_SetKillFlag(1);
    SzFade_SetPauseFlag(1, 1);
    lMain_LoadModel();
    return 1;
}

typedef struct {
    s32 type;
    s32 data;
    s32 arg1;
    s32 arg2;
    u8 position[0x10];
    u8 rotation[0x10];
} Entry_00100350;

extern Entry_00100350 gMain_ModelData[];

/* Starts the model and effect systems. */
s32 lMain_InitModel2(void) {
    s32 index;

    index = 0;
    do {
        if (SzModel_Create(index) == 0) {
            return 0;
        }
        SzModel_SetPos(index, gMain_ModelData[index].position);
        SzModel_SetRot(index, gMain_ModelData[index].rotation);
        SzModel_Preset(index, gMain_ModelData[index].type, gMain_ModelData[index].data);
        if (gMain_ModelData[index].type == 5) {
            SzDuel_AddUnit(index - 0x1E, gMain_ModelData[index].arg1, gMain_ModelData[index].arg2,
                         SzDuel_Xax2New(gMain_ModelData[index].data), 1);
            SzDuel_SetUnitStatus(-1, index, 4, 1);
            SzDuel_SetUnitOpenRate(-1, index, 0, 0xFF);
            SzDuel_SetUnitCtlRateM(-1, index, 1, 0);
        } else if (gMain_ModelData[index].type == 4) {
            s32 mode;
            s32 handle;

            mode = (index - 0x14 < 5) ? 0 : 1;
            handle = SzDuel_Xax2New(gMain_ModelData[index].data);
            SzDuel_AddUnit(mode, gMain_ModelData[index].arg1, gMain_ModelData[index].arg2, handle, 0);
            SzDuel_SetUnitStatus(-1, index, 4, 1);
            SzDuel_SetUnitOpenRate(-1, index, 0, 0xFF);
            SzDuel_SetUnitCtlRateM(-1, index, 1, 0);
        }
        index++;
    } while (index < 0x54);
    return 1;
}

/* Shuts the systems down. */
void Main_Term(void) {
    s32 i;

    SzView_Destroy(0);
    i = 0;
    do {
        SzModel_Destroy(i);
        i += 1;
    } while (i < 0x54);
    RhBase_Term();
    SzPad_Term();
}

/* The main loop: one game frame per pass. */
void Main_Loop(void) {
    RhBase_SetVSyncCallback(SzEffect_StoneProc);
    for (;;) {
        if (SzGame_GetMode(1) == 1) {
            lMain_LoadModel();
        }
        Main_LoopProc();
    }
}

/* One game frame: pads, the current game mode, drawing, and waiting for the frame's vertical blanks. */
void Main_LoopProc(void) {
    SzPad_Status();
    SzSound_VSync();
    SzFile_DoRequest();
    SzGame_ModeAct();
    SzView_DoRequest(-1, -1);
    SzDuel_DoUnitRequest();
    Main_Draw();
    SzGame_SetFrameSpeed(RhBase_FlipBuffer());
    if (SzGame_GetStabilizer() != 0) {
        SzGame_SetFrameSpeed(1);
    } else {
        SzGame_SetStabilizer(1);
    }
    Main_VSync();
    SzGame_AddFrameCount();
    SzPad_Act();
}

/* Sets the GS display registers for the screen size and buffer format; `dim` halves the brightness. */
void func_00100610(s32 dim) {
    s32 width;
    s32 height;
    s32 fbp;
    s32 psm;

    RhBase_GetScreenSize(&width, &height);
    RhBase_GetBufferFormatEx(0, &fbp, &psm, NULL);
    *(s64 *)0x12000000 = ((s64) (dim ? 0x7F : 0xFF) << 8) | 0x23;
    *(s64 *)0x12000090 = ((s64) psm << 15) | ((s64) (fbp >> 5) | ((s64) (width >> 6) << 9));
    *(s64 *)0x120000A0 = ((s64) (height - 1) << 44) | (((s64) ((width * 4) - 1) << 32) | 0x0183227C);
    *(s64 *)0x12000070 = ((s64) psm << 15) | ((s64) (fbp >> 5) | ((s64) (width >> 6) << 9));
    *(s64 *)0x12000080 = ((s64) (height - 1) << 44) | (((s64) ((width * 4) - 1) << 32) | 0x0183327C);
    *(s64 *)0x120000D0 = 0;
}

/* Loads the models every mode needs. */
void lMain_LoadModel(void) {
    extern s32 SzModel_GetModelType(s32);
    s32 i;
    s32 type;

    for (i = 0; i < 0x54; i++) {
        type = SzModel_GetModelType(i);
        if (SzModel_IsModelReady(i) == 0) {
            continue;
        }
        if (type == 4 || type == 5) {
            if (SzDuel_GetUnit(-1, i) == 0) {
                continue;
            }
        }
        SzModel_Load(i, -1, -1, 1);
    }
}

/* The main program's vertical-blank handler. */
s32 Main_VSync(void) {
    func_0019A5C8();
    SzPad_VSync();
    SzGame_VSync();
    return 0;
}


typedef union {
    f32 value;
    struct {
        u8 r, g, b, a;
    } color;
} Color_00100850;

/* Draws a frame: the 3D scene, the overlays, soft focus, then swaps the buffers. */
void Main_Draw(void) {
    extern s32 SzGame_InqAutoBlur();
    extern s32 SzText_InitClutManage();
    extern s32 ExDitherMode_Pipe();
    extern s32 ExGetAlphaVal();
    extern Color_00100850 D_0028B840;
    Color_00100850 color;
    s32 initial;
    s32 allocation;
    s32 i;
    s32 level;

    initial = RhBase_GetVifPacketArea();
    SzText_InitClutManage(0, 0);
    SzModel_SetDrawCache(0);
    RhBase_SetVifPacketArea(RhZSort_Finish_Pipe(SzDuel_DrawStage_Pipe(SzBattle_DrawStage_Pipe(SzView_Set_Pipe(ExDitherMatrixEz_Pipe(ExDitherMode_Pipe(RhBase_SetZBufferMode(initial, 1), 1), 1), 0)))));
    ExDitherMatrixEz(2);
    SzGame_ModeDraw();
    SzModel_SetDrawCache(0);
    ExZBufferMode(0);
    ExDitherMatrixEz(3);
    if (SzEffect_IsUse2(0, -1) == 0) {
        if ((SzEffect_IsUse2(1, -1) == 0) && (SzEffect_IsUse2(2, -1) == 0)) {
            SzText_FreeRequest(4, -1);
        }
    }
    if (SzEffect_IsUse2(0, -1) == 0) {
        if (SzEffect_IsUse2(1, -1) == 0) {
            SzText_FreeRequest(5, -1);
            SzText_FreeRequest(8, -1);
        }
    }
    if (SzEffect_IsUse2(1, -1) == 0) {
        if (SzEffect_IsUse2(2, -1) == 0) {
            SzText_FreeRequest(6, -1);
        }
    }
    allocation = 0x3BC0;
    allocation += SzText_InitClutManage(allocation, 2);
    allocation += SzText_DoRequest(4, allocation);
    allocation += SzText_DoRequest(5, allocation);
    allocation += SzText_DoRequest(6, allocation);
    SzText_DoRequest(8, allocation);
    ExFlushTexture();
    ExInitPrim();
    SzDuel_DrawStageAfter();
    SzModel_DrawMotionBlur(-1);
    SzDuel_DrawUnit();
    i = 0;
    do {
        SzModel_SetMaxOT(i, 0);
        i += 1;
    } while (i < 0x54);
    SzEffect_Draw(0);
    SzEffect_Draw(1);
    SzEffect_Draw(2);
    SzDuel_DrawAllCard();
    ExTermPrim();
    ExZBufferMode(1);
    SzGame_ModeDrawAfter();
    ExDitherMatrixEz(2);
    if ((level = SzGame_InqAutoBlur()) > 0) {
        s32 image = (s32)ExGetAlphaVal(0);
        color = D_0028B840;
        color.color.a = level << 4;
        ExSortDispBlur(0, 0, 1, image, (s32)&color);
    }
    SzFade_DispAll();
    ExDitherMatrixEz(3);
    SzGame_ModeDrawLast();
}

typedef struct Vec4_00100B00 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4_00100B00;

extern f32 g_vec_temp[];

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

extern f32 g_vec_temp[];

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
    s32 var_s1;
    s32 temp_s2;
    s32 temp_s6;
    s32 temp_s6_2;
    s32 temp_s6_3;

    steps[0] = (arg->endX - arg->startX) / (f32) arg->count;
    steps[1] = (arg->endY - arg->startY) / (f32) arg->count;
    steps[2] = (arg->endZ - arg->startZ) / (f32) arg->count;
    temp_f4 = arg->amplitude * RhGeom_GetVectorScalor(steps);
    temp_s0 = arg->points;
    var_s1 = 1;
    *(Vec3_00102A50 *) temp_s0 = *(Vec3_00102A50 *) &arg->startX;
    temp_f12 = 200.0f * temp_f4;
    temp_v0 = temp_s0 + (arg->count * 3);
    temp_s0 += 3;
    *(Vec3_00102A50 *) temp_v0 = *(Vec3_00102A50 *) &arg->endX;
    temp_s2 = func_001A22C0(200.0f * temp_f4) >> 1;
    for (; var_s1 < arg->count;) {
        temp_s6 = func_0019A5C8() >> 4;
        temp_s0[0] = arg->startX + (steps[0] * (f32) var_s1) + ((f32) ((temp_s6 % func_001A22C0(temp_f12)) - temp_s2) / 100.0f);
        temp_s6_2 = func_0019A5C8() >> 4;
        temp_s0[1] = arg->startY + (steps[1] * (f32) var_s1) + ((f32) ((temp_s6_2 % func_001A22C0(temp_f12)) - temp_s2) / 100.0f);
        temp_s6_3 = func_0019A5C8() >> 4;
        temp_s0[2] = arg->startZ + (steps[2] * (f32) var_s1++) + ((f32) ((temp_s6_3 % func_001A22C0(temp_f12)) - temp_s2) / 100.0f);
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

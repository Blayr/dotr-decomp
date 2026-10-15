#include "common.h"

asm void func_00100000(void) {
    .set noreorder
    nop
}

INCLUDE_ASM("asm/nonmatchings/main_000", func_00100008);

/* Hand-written tail jump (GCC-style move into the delay slot). */

asm void func_001000B8(void) {
    .set noreorder
    j func_001847B0
    .word 0x00002025 /* or a0, zero, zero: the assembler would write paddub */
}

asm void func_001000C0(void) {
    .set noreorder
    addiu v1, zero, 0x23
    syscall 0
}

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
    func_001A6C80();
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

extern Entry_00100350 D_0028A880[];

s32 lMain_InitModel2(void) {
    s32 index;

    index = 0;
    do {
        if (SzModel_Create(index) == 0) {
            return 0;
        }
        SzModel_SetPos(index, D_0028A880[index].position);
        SzModel_SetRot(index, D_0028A880[index].rotation);
        SzModel_Preset(index, D_0028A880[index].type, D_0028A880[index].data);
        if (D_0028A880[index].type == 5) {
            SzDuel_AddUnit(index - 0x1E, D_0028A880[index].arg1, D_0028A880[index].arg2,
                         SzDuel_Xax2New(D_0028A880[index].data), 1);
            SzDuel_SetUnitStatus(-1, index, 4, 1);
            SzDuel_SetUnitOpenRate(-1, index, 0, 0xFF);
            SzDuel_SetUnitCtlRateM(-1, index, 1, 0);
        } else if (D_0028A880[index].type == 4) {
            s32 mode;
            s32 handle;

            mode = (index - 0x14 < 5) ? 0 : 1;
            handle = SzDuel_Xax2New(D_0028A880[index].data);
            SzDuel_AddUnit(mode, D_0028A880[index].arg1, D_0028A880[index].arg2, handle, 0);
            SzDuel_SetUnitStatus(-1, index, 4, 1);
            SzDuel_SetUnitOpenRate(-1, index, 0, 0xFF);
            SzDuel_SetUnitCtlRateM(-1, index, 1, 0);
        }
        index++;
    } while (index < 0x54);
    return 1;
}

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

void Main_Loop(void) {
    RhBase_SetVSyncCallback(SzEffect_StoneProc);
    for (;;) {
        if (SzGame_GetMode(1) == 1) {
            lMain_LoadModel();
        }
        Main_LoopProc();
    }
}

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

void func_00100610(s32 arg0) {
    s32 sp20;
    s32 sp24;
    s32 sp28;
    s32 sp2C;

    RhBase_GetScreenSize(&sp20, &sp24);
    RhBase_GetBufferFormatEx(0, &sp28, &sp2C, NULL);
    *(s64 *)0x12000000 = ((s64) (arg0 ? 0x7F : 0xFF) << 8) | 0x23;
    *(s64 *)0x12000090 = ((s64) sp2C << 15) | ((s64) (sp28 >> 5) | ((s64) (sp20 >> 6) << 9));
    *(s64 *)0x120000A0 = ((s64) (sp24 - 1) << 44) | (((s64) ((sp20 * 4) - 1) << 32) | 0x0183227C);
    *(s64 *)0x12000070 = ((s64) sp2C << 15) | ((s64) (sp28 >> 5) | ((s64) (sp20 >> 6) << 9));
    *(s64 *)0x12000080 = ((s64) (sp24 - 1) << 44) | (((s64) ((sp20 * 4) - 1) << 32) | 0x0183327C);
    *(s64 *)0x120000D0 = 0;
}

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

void Ex3d_RotTransPersAutoCalcQ(void *, void *, s32, s32, s32);
extern f32 D_0030FF00[];

void GRotTransPers_3(void *arg0, void *arg1, void *arg2, s32 arg3, s32 arg4, s32 arg5) {
    Vec4_00100B00 vertices[3];

    vertices[0] = *(Vec4_00100B00 *)arg0;
    vertices[1] = *(Vec4_00100B00 *)arg1;
    vertices[2] = *(Vec4_00100B00 *)arg2;
    Ex3d_RotTransPersAutoCalcQ(vertices, D_0030FF00, arg3, arg4, arg5);
}

typedef struct Vec4_00100BA0 {
    f32 x, y, z, w;
} Vec4_00100BA0;

void Ex3d_RotTransPersAutoCalcQ(void *, void *, s32, s32, s32);
extern f32 D_0030FF00[];

void GRotTransPers_4(void *arg0, void *arg1, void *arg2, void *arg3,
                   s32 arg4, s32 arg5, s32 arg6) {
    Vec4_00100BA0 vectors[4];

    vectors[0] = *(Vec4_00100BA0 *)arg0;
    vectors[1] = *(Vec4_00100BA0 *)arg1;
    vectors[2] = *(Vec4_00100BA0 *)arg2;
    vectors[3] = *(Vec4_00100BA0 *)arg3;
    Ex3d_RotTransPersAutoCalcQ(vectors, D_0030FF00, arg4, arg5, arg6);
}

typedef struct {
    u16 x : 14;
    u16 flags_x : 2;
    u16 y : 14;
    u16 flags_y : 2;
} PackedCoordinates_00100C60;

void GSet_WindowUv(void *arg0, void *arg1, s32 arg2, s32 arg3) {
    s32 var_a1;
    s32 var_a2;

    var_a1 = ((s32) ((u16 *) arg1)[0] >> 4) - 0x6C0 + arg2;
    var_a2 = ((s32) ((u16 *) arg1)[1] >> 4) - 0x720 + arg3;
    if (var_a1 <= 0) {
        var_a1 = 1;
    } else if (var_a1 > 0x27F) {
        var_a1 = 0x27F;
    }
    if (var_a2 <= 0) {
        var_a2 = 1;
    } else if (var_a2 > 0x1BF) {
        var_a2 = 0x1BF;
    }
    ((PackedCoordinates_00100C60 *) arg0)->x = var_a1 << 4;
    ((PackedCoordinates_00100C60 *) arg0)->y = var_a2 << 4;
}

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Vec3_00100D00;


s32 GGet_ModelPosZSign(s32 arg0) {
    Vec3_00100D00 v;
    s32 ret;

    ret = 1;
    SzEffect_GetModelPos2(arg0, &v);
    if (v.z < 0.0f) {
        ret = -1;
    }
    return ret;
}

f32 GCalc_Trans(s32 arg0, s32 arg1, s32 arg2) {
    f32 temp_f20;

    temp_f20 = func_001A6B70(6.2831855f * ((f32) ((s32) ((arg1 - arg0) << 0x10) / (s32) (arg1 * 5)) / 65536.0f));
    return 1.0f - func_001A6C48(temp_f20 / func_001A6B70(1.2566179f), (f32) arg2);
}

typedef struct {
    u32 values[4];
} Config_00100E00;

extern Config_00100E00 D_0028C210;

void GRot_Matrix(s32 arg0, s32 arg1, s32 arg2) {
    Config_00100E00 values;
    u32 *words = (u32 *)&values;

    values = D_0028C210;
    arg1 &= 0xFFFF;
    words[arg2] = arg1;
    RhGeom_RotXYZMatrix(arg0, words);
}

#ifndef GAME_H
/* The game translation unit already declares this global with its local type. */
typedef struct {
    unsigned int values[4];
} Config_00100E00;

extern Config_00100E00 D_0028C210;
#endif



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

void GGet_TriangleCenter(float *out, float *a, float *b, float *c)
{
    float v[2][4];

    sceVu0AddVector(v[0], a, b);
    sceVu0ScaleVector((float *)v, (float *)v, 0.5f);
    sceVu0SubVector(v[1], c, v[0]);
    sceVu0ScaleVector(v[1], v[1], 0.33333334f);
    sceVu0AddVector(out, v[1], v[0]);
}

f32 GCalc_Decrease(f32 fparg0, f32 fparg1, f32 fparg2) {
    f32 var_f0;

    var_f0 = 1.0f;
    if (!(fparg0 <= fparg2)) {
        var_f0 = (fparg0 - fparg1) / (fparg2 - fparg1);
    }
    return var_f0;
}

f32 GCalc_Increase(f32 fparg0, f32 fparg1) {
    f32 var_f0;

    var_f0 = 1.0f;
    if (fparg0 < fparg1) {
        var_f0 = fparg0 / fparg1;
    }
    return var_f0;
}

s32 GWithin_LimitsI(s32 arg0, s32 arg1, s32 arg2) {
    if (arg0 < arg1) {
        arg0 = arg1;
    } else if (arg2 < arg0) {
        arg0 = arg2;
    }
    return arg0;
}

extern f32 D_0028BC10[4][32][3];

static inline void rotate_00101080(void *matrix, s32 angle, s32 axis) {
    Config_00100E00 values;
    u32 *words = (u32 *)&values;

    values = D_0028C210;
    angle &= 0xFFFF;
    words[axis] = angle;
    RhGeom_RotXYZMatrix((s32)matrix, words);
}

void GSet_RandVector(f32 *vector, f32 scale) {
    f32 matrix[16];
    f32 *value;
    f32 sign;

    value = &D_0028BC10[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32][(func_0019A5C8() >> 23) % 3];
    sign = 2.0f * (f32)((func_0019A5C8() >> 23) % 2) - 1.0f;
    vector[0] = sign * *value;

    value = &D_0028BC10[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32][(func_0019A5C8() >> 23) % 3];
    sign = 2.0f * (f32)((func_0019A5C8() >> 23) % 2) - 1.0f;
    vector[1] = sign * *value;

    value = &D_0028BC10[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32][(func_0019A5C8() >> 23) % 3];
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

s32 GJudge_FrontBack2(void *arg0, void *arg1, void *arg2) {
    Point_00101430 *a = arg0;
    Point_00101430 *b = arg1;
    Point_00101430 *c = arg2;
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

s32 ShFx_isClip(void *arg0) {
    u16 x;
    u16 y;

    x = ((u16 *)arg0)[0];
    if ((f32)x < 22528.0f) {
        return 0;
    }
    if (!((f32)x <= 43008.0f)) {
        return 0;
    }
    y = ((u16 *)arg0)[1];
    if ((f32)y < 25600.0f) {
        return 0;
    }
    if ((f32)y > 39936.0f) {
        return 0;
    }
    return 1;
}

s32 ShFx_isClipSC(void *arg0) {
    u16 *p = (u16 *)arg0;
    if ((f32)(u32)p[0] < 27648.0f) return 0;
    if ((f32)(u32)p[0] > 37888.0f) return 0;
    if ((f32)(u32)p[1] < 29184.0f) return 0;
    if ((f32)(u32)p[1] > 36352.0f) return 0;
    return 1;
}

f32 ShFx_GetDrawSize(f32 fparg0, f32 fparg1) {
    return (fparg0 / (fparg1 / 256.0f)) * (SzView_GetScreenDistance(0) / 800.0f);
}

void ShFx_Vec2Rot(f32 *arg0, s32 *arg1) {
    arg1[0] = (u16) func_001A22C0(65536.0f * (func_001A6C18(func_001A6C60(arg0[0] * arg0[0] + arg0[2] * arg0[2]), arg0[1]) / 6.2831855f));
    arg1[1] = (u16) func_001A22C0(65536.0f * (func_001A6C18(arg0[0], arg0[2]) / 6.2831855f));
    arg1[2] = 0;
}

void ShFx_Vec2Mat(f32 *src, void *dst) {
    extern void RhGeom_GetRotXYZMatrix(void *, s32 *);
    s32 angles[3];

    angles[0] = (u16)func_001A22C0(65536.0f * (func_001A6C18(func_001A6C60(src[0] * src[0] + src[2] * src[2]), src[1]) / 6.2831855f));
    angles[1] = (u16)func_001A22C0(65536.0f * (func_001A6C18(src[0], src[2]) / 6.2831855f));
    angles[2] = 0;
    RhGeom_GetRotXYZMatrix(dst, angles);
}

void ShFx_initTimer(s8 *arg0, s8 arg1, s8 arg2, s8 arg3) {
    arg0[2] = arg1;
    arg0[0] = arg1;
    arg0[1] = arg2;
    arg0[3] = arg3;
}

typedef struct Timer_00101AF0 {
    u8 count;
    u8 delay;
} Timer_00101AF0;

s32 ShFx_isTimer(void *arg0) {
    Timer_00101AF0 *timer = arg0;
    u8 temp_v0;
    u8 temp_v1;

    temp_v1 = timer->count;
    if (temp_v1 == 0) {
        return 0;
    }
    temp_v0 = timer->delay;
    if (temp_v0 != 0) {
        timer->delay = (u8) (temp_v0 - 1);
        return 0;
    }
    timer->count = (u8) (temp_v1 - 1);
    return 1;
}

void ShFx_initPartsTimer(void *arg0, s8 arg1, s8 arg2) {
    ((s8 *)arg0)[2] = arg1;
    ((s8 *)arg0)[0] = arg1;
    ((s8 *)arg0)[1] = arg2;
}

typedef struct Counter_00101B50 {
    u8 count;
    u8 delay;
} Counter_00101B50;

s32 ShFx_isPartsTimer(void *arg0) {
    Counter_00101B50 *counter = arg0;

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

void ShFx_AdjustPoint(void *arg0, s32 arg1) {
    u8 temp_a0;

    temp_a0 = *((u8 *)arg0 + 5);
    switch (temp_a0) {
    case 0:
        return;
    case 1:
        SzEffect_GetRef2(SzEffect_GetFrom(temp_a0), *((u8 *)arg0 + 6), arg1);
        return;
    case 2:
        SzEffect_GetRef2(SzEffect_GetTarget(temp_a0), *((u8 *)arg0 + 6), arg1);
        return;
    }
}

s32 ShFx_GetTempIndex(u8 *arg0, s32 arg1, s32 arg2) {
    s32 offset;
    s32 i;

    i = 0;
    if (i < arg2) {
        offset = 0;
        do {
            if (arg0[offset] == 0) {
                return i;
            }
            i++;
            offset += arg1;
        } while (i < arg2);
    }
    return -1;
}

void ShFx_GetAlpha(void *arg0, void *arg1) {
    s8 *out = (s8 *)arg1;

    switch (((u8 *)arg0)[5]) {
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

void ShFx_SetTexFT4(void *arg0, void *arg1, void *arg2) {
    Sprite_00101D20 *dst = arg0;
    s32 *src = arg1;
    u8 sp4C[4];

    dst->flags |= 0x800;
    dst->v[0].x.val = src[2] << 4;
    dst->v[0].y.val = src[4] << 4;
    dst->v[1].x.val = src[3] << 4;
    dst->v[1].y.val = src[4] << 4;
    dst->v[2].x.val = src[2] << 4;
    dst->v[2].y.val = src[5] << 4;
    dst->v[3].x.val = src[3] << 4;
    dst->v[3].y.val = src[5] << 4;
    ExAssignClamp(arg0, 0xA | ((s64)src[2] << 4) | ((s64)(src[3] - 1) << 14) | ((s64)src[4] << 24) |
                            ((s64)(src[5] - 1) << 34));
    ExAssignTexture(arg0, arg2, 1);
    ShFx_GetAlpha(arg1, sp4C);
    ExAssignAlpha(arg0, (s64)sp4C[0] | ((s64)sp4C[1] << 2) | ((s64)sp4C[2] << 4) | ((s64)sp4C[3] << 6));
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

void ShFx_SetTexGT4(void *arg0, void *arg1, void *arg2) {
    Sprite_00101EE0 *dst = arg0;
    s32 *src = arg1;
    u8 sp4C[4];

    dst->flags |= 0x800;
    dst->v[0].x.val = src[2] << 4;
    dst->v[0].y.val = src[4] << 4;
    dst->v[1].x.val = src[3] << 4;
    dst->v[1].y.val = src[4] << 4;
    dst->v[2].x.val = src[2] << 4;
    dst->v[2].y.val = src[5] << 4;
    dst->v[3].x.val = src[3] << 4;
    dst->v[3].y.val = src[5] << 4;
    ExAssignClamp(arg0, 0xA | ((s64)src[2] << 4) | ((s64)(src[3] - 1) << 14) | ((s64)src[4] << 24) |
                            ((s64)(src[5] - 1) << 34));
    ExAssignTexture(arg0, arg2, 1);
    if (((u8 *)arg1)[5] != 0) {
        ShFx_GetAlpha(arg1, sp4C);
        ExAssignAlpha(arg0, (s64)sp4C[0] | ((s64)sp4C[1] << 2) | ((s64)sp4C[2] << 4) | ((s64)sp4C[3] << 6));
    }
}

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

void ShFx_GetTexWidth(u32 arg0, s32 *arg1, s32 *arg2) {
    switch (arg0) {
    case 0:
    case 4:
        *arg1 = 0x43000000;
        *arg2 = 0x42800000;
        return;
    case 1:
        *arg1 = 0x42800000;
        *arg2 = 0x43000000;
        return;
    case 2:
    case 5:
    case 8:
        *arg2 = 0x43000000;
        *arg1 = 0x43000000;
        return;
    case 3:
        *arg1 = 0x43800000;
        *arg2 = 0x42800000;
        return;
    case 6:
        *arg1 = 0x42000000;
        *arg2 = 0x43000000;
        return;
    case 7:
        *arg1 = 0x43000000;
        *arg2 = 0x42800000;
        return;
    case 9:
        *arg2 = 0x42800000;
        *arg1 = 0x42800000;
        return;
    default:
        *arg2 = 0;
        *arg1 = 0;
        return;
    }
}

s32 ShFx_GetAnmID(u32 arg0, s32 arg1) {
    switch (arg0) {
    case 0:
    case 1:
    case 3:
        return arg1 & 7;
    case 4:
        return arg1 & 1;
    case 2:
        return arg1 & 0xF;
    case 5:
        return arg1 & 3;
    case 9:
    default:
        return 0;
    }
}

void ShFx_MakeRnd(s8 *arg0, s32 arg1) {
    s8 *var_s0;
    s32 var_s1;

    var_s0 = arg0;
    for (var_s1 = 0; var_s1 < arg1; var_s1 += 1) {
        *var_s0 = (s8) (func_0019A5C8() >> 4);
        var_s0 += 1;
    }
}

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

s32 ShFx_Spline(void *arg0) {
    Spline_00102550 *s = arg0;
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

void ShFx_Vib2P(void *arg0) {
    Arg_00102A50 *arg = arg0;
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


void ShFx_Spin2P(void *arg0) {
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
    Curve_00102CB0 *curve = arg0;

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

static inline Vec3_00102F20 *append_00102F20(Vec3_00102F20 *dst,
                                           const Vec3_00102F20 *src) {
    *dst = *src;
    return dst + 1;
}

void ShFx_Hsin2P(void *arg0) {
    Vec3_00102F20 *point;
    s32 i;
    f32 matrix[4][4];
    f32 direction[4];
    f32 offset[4];
    s32 rotation[4];
    Curve_00102F20 *curve = arg0;
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

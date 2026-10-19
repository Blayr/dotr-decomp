/* main() and the main loop: starts every system, then runs and draws each frame. */

#include "common.h"

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
    *(s64 *)GS_PMODE_ADDR = ((s64) (dim ? 0x7F : 0xFF) << 8) | 0x23;
    *(s64 *)GS_DISPFB2_ADDR = ((s64) psm << 15) | ((s64) (fbp >> 5) | ((s64) (width >> 6) << 9));
    *(s64 *)GS_DISPLAY2_ADDR = ((s64) (height - 1) << 44) | (((s64) ((width * 4) - 1) << 32) | 0x0183227C);
    *(s64 *)GS_DISPFB1_ADDR = ((s64) psm << 15) | ((s64) (fbp >> 5) | ((s64) (width >> 6) << 9));
    *(s64 *)GS_DISPLAY1_ADDR = ((s64) (height - 1) << 44) | (((s64) ((width * 4) - 1) << 32) | 0x0183327C);
    *(s64 *)GS_EXTWRITE_ADDR = 0;
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

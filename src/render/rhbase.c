/* The renderer base: GS and VIF set-up, frame buffers, Z buffer, flips (RhBase_*). */

#include "common.h"

typedef struct Flags_00209510 {
    u8 pad0 : 6;
    u8 enabled : 1;
    u8 pad7 : 1;
} Flags_00209510;

typedef struct State_00209510 {
    u8 pad0[0x274];
    u8 *decoder;
    s32 option;
    s32 base;
    s32 current;
    s32 size;
    s32 ready;
    s32 start;
    s32 end;
    s32 field294;
    s32 field298;
} State_00209510;

typedef struct Env_00209510 {
    u8 pad0[6];
    s16 field6;
    u8 pad8[20];
} Env_00209510;

typedef struct Mode_00209510 {
    u32 clock : 2;
    u32 gate : 1;
    u32 gate_source : 1;
    u32 gate_mode : 2;
    u32 zero_return : 1;
    u32 enable : 1;
    u32 compare_interrupt : 1;
    u32 overflow_interrupt : 1;
    u32 compare_flag : 1;
    u32 overflow_flag : 1;
    u32 reserved : 20;
} Mode_00209510;

extern u8 D_00286980[];
extern u8 screenModes[]; /* original: gRhSys_asd */
extern u8 D_00293F14[];
extern u8 D_00293F18[];
extern s32 D_003261C8;

/* Starts the renderer: screen mode `mode`, its frame buffers, the packet area start..end of `size`. */
s32 RhBase_Init(s32 modeIn, s32 interlace, s32 field, s32 start, s32 end, s32 size, s32 flags) {
    void sceDmaSend(u8 *, s32);
    Env_00209510 env;
    Mode_00209510 mode;
    State_00209510 *state = (State_00209510 *)screenState;
    s32 *packet;

    func_00198948(screenState, 0, 0x2A0);
    D_003261C8 = flags;
    if (RhFile_Init() == 0) {
        return 0;
    }
    sceDevVif0Reset();
    sceDevVu0Reset();
    sceGsResetPath();
    sceDmaReset(1);
    sceDmaGetEnv(&env);
    env.field6 = 0x100;
    sceDmaPutEnv(&env);
    func_00184810(0, *(s16 *)(screenModes + modeIn * 0x28),
                    *(s16 *)(D_00293F14 + modeIn * 0x28),
                    *(s16 *)(D_00293F18 + modeIn * 0x28));
    state->decoder = (u8 *)sceDmaGetChan(1);
    ((Flags_00209510 *)state->decoder)->enabled = 1;
    lRhBase_InitScreenVariables(state, modeIn, interlace, field);
    mode.clock = 3;
    mode.gate = 0;
    mode.gate_source = 0;
    mode.gate_mode = 0;
    mode.zero_return = 0;
    mode.enable = 1;
    mode.compare_interrupt = 0;
    mode.overflow_interrupt = 0;
    mode.compare_flag = 0;
    mode.overflow_flag = 1;
    mode.reserved = 0;
    *(s32 *)T1_MODE_ADDR = *(s32 *)&mode;
    *(s32 *)T1_COUNT_ADDR = 0;
    state->start = start;
    state->end = end;
    state->size = size;
    state->ready = 1;
    state->base = start;
    state->current = start;
    ChangeThreadPriority(GetThreadId(), 0x20);
    state->field294 = 0;
    state->field298 = 0;
    packet = (s32 *)lRhBase_InitGsAndVif(state->base);
    RhGeom_Init();
    RhView_Init();
    RhMemCard_Init();
    packet[0] = 0x70000000;
    packet[1] = 0;
    packet[2] = 0;
    packet[3] = 0;
    FlushCache(0);
    sceGsSyncPath(0, 0);
    sceDmaSend(state->decoder, state->base);
    sceGsSyncPath(0, 0);
    sceDmaSend(state->decoder, (s32)D_00286980);
    sceGsSyncPath(0, 0);
    RhZSort_Start(state->base, state->base + state->size);
    sceGsSyncV(0);
    return 1;
}

/* Ends the renderer. */
s32 RhBase_Term(void) {
    RhView_Term();
    RhFile_Term();
    RhGeom_Term();
    RhMemCard_Term();
    return 1;
}

/* Resets the GS drawing environment for `field`. */
void RhBase_ResetGsEnv(s32 field) {
    void sceDmaSend(u8 *, s32);
    extern void sceDmaSync(u8 *, s32, s32);
    extern void sceVpu0Reset(void);
    extern u8 D_00293F1C[];
    extern u8 D_00293F20[];
    extern u8 *D_003261C4;
    s32 *packet;

    sceDmaSync(D_003261C4, 0, 0);
    sceDmaReset(1);
    sceGsSyncPath(0, 0);
    sceGsResetPath();
    sceVpu0Reset();
    func_00184810(0, *(s16 *)(screenModes + field * 0x28),
                    *(s16 *)(D_00293F14 + field * 0x28),
                    *(s16 *)(D_00293F18 + field * 0x28));
    D_0032618C = *(s32 *)(D_00293F1C + field * 0x28);
    currentTimingModeValue = *(s32 *)(D_00293F20 + field * 0x28);
    packet = (s32 *)lRhBase_InitGsAndVif(*(s32 *)0x003261CC);
    packet[0] = 0x70000000;
    packet[1] = 0;
    packet[2] = 0;
    packet[3] = 0;
    FlushCache(0);
    sceGsSyncPath(0, 0);
    sceDmaSend(D_003261C4, *(s32 *)0x003261CC);
    sceGsSyncPath(0, 0);
}

typedef struct State_002099D0 {
    u8 pad0[0x240];
    s32 width;
    u8 pad244[8];
    s32 display;
    u8 pad250[0x10];
    s16 x;
    u8 pad262[2];
    s16 y;
    u8 pad266[6];
    s32 frame;
    u8 pad270[0xC];
    s32 dmaAddress;
    s32 dmaBuffer;
    s32 dmaSize;
    s32 currentBuffer;
    s32 buffer0;
    s32 buffer1;
    void (*beforeDisplay)(void);
    void (*beforeWait)(void);
} State_002099D0;

/* Ends the frame: sends the draw lists, waits for the GS, swaps the frame buffers. */
s32 RhBase_FlipBuffer(void) {
    extern s32 sceGsSyncPath();
    extern s32 lRhBase_SetRandomDither();
    extern u8 D_00293F14[];
    extern s32 frameSkipCounter;
    extern s32 currentVideoModeIndex;
    State_002099D0 *state = (State_002099D0 *)screenState;
    s32 result;
    s32 width;
    s32 period;
    s32 remaining;
    s32 *packet;
    u8 *display;

    RhZSort_Finish();
    RhFile_VSyncProcess();
    RhMemCard_Act();
    packet = (s32 *)VifPacketArea;
    packet[0] = 0x70000000;
    packet[1] = 0;
    packet[2] = 0;
    packet[3] = 0;
    (void)*(volatile u32 *)T1_COUNT_ADDR;
    if (sceGsSyncPath(0, 0) < 0) {
        RhBase_ResetGsEnv(currentVideoModeIndex);
    }
    if (state->beforeWait != NULL) {
        state->beforeWait();
    }
    remaining = frameSkipCounter;
    if (*(s32 *)(D_00293F14 + currentVideoModeIndex * 0x28) == 2) {
        width = 0x1C0;
        period = 0x208;
    } else {
        width = 0x200;
        period = 0x26C;
    }
    while (remaining-- >= 0) {
        result = sceGsSyncV(0);
        if (state->width == width) {
            if (result != 0) {
                result = sceGsSyncV(0);
            }
        }
        if (*(volatile u32 *)T1_COUNT_ADDR > (u32)(period * (frameSkipCounter + 1))) {
            break;
        }
    }
    frameSkipCounter = 0;
    if (state->beforeDisplay != NULL) {
        state->beforeDisplay();
    }
    if (state->display != 0) {
        if (state->frame & 1) {
            display = (u8 *)state + 0x150;
        } else {
            display = (u8 *)state + 0x60;
        }
        sceGsSetHalfOffset(display, state->x, state->y, (s16)result);
    }
    FlushCache(0);
    sceGsSwapDBuff((u8 *)state, state->frame);
    if (SzGame_InqSoftFocus() != 0) {
        func_00100610(1);
    }
    sceGsSyncPath(0, 0);
    *(volatile s32 *)D1_QWC_ADDR = 0;
    *(volatile s32 *)D1_TADR_ADDR = (u32)state->dmaAddress & 0x0FFFFFFF;
    *(volatile s32 *)D_STAT_ADDR = 2;
    FlushCache(0);
    *(volatile s32 *)D1_CHCR_ADDR = 0x145;
    if (state->currentBuffer != 0) {
        state->dmaAddress = state->buffer1;
        state->dmaBuffer = state->buffer1;
        state->currentBuffer = 0;
    } else {
        state->dmaAddress = state->buffer0;
        state->dmaBuffer = state->buffer0;
        state->currentBuffer = 1;
    }
    state->frame++;
    result = 1;
    if (*(s32 *)(D_00293F14 + currentVideoModeIndex * 0x28) == 2) {
        if (state->width == 0x1C0) {
            if (*(volatile u32 *)T1_COUNT_ADDR > 0x21C) {
                result = 2;
            }
        } else if (*(volatile u32 *)T1_COUNT_ADDR > 0x10E) {
            result = 2;
        }
    } else if (*(volatile u32 *)T1_COUNT_ADDR > 0x280) {
        result = 2;
    }
    *(volatile u32 *)T1_COUNT_ADDR = 0;
    RhZSort_Start(state->dmaAddress, state->dmaAddress + state->dmaSize);
    RhBase_SetVifPacketArea(lRhBase_SetRandomDither(RhBase_GetVifPacketArea()));
    return result;
}

/* The current end of the VIF packet being built (where the next primitive goes). */
s32 RhBase_GetVifPacketArea(void) {
    return VifPacketArea;
}

/* Sets the end of the VIF packet being built. */
void RhBase_SetVifPacketArea(s32 cursor) {
    VifPacketArea = cursor;
}

typedef struct {
    u8 padding[0x244];
    f32 field_244;
    s32 field_248;
} Data_00209D40;

/* The screen's vertical aspect ratio; its other ratio word through `out`. */
f32 RhBase_GetAspectY(s32 *out) {
    Data_00209D40 *data = (Data_00209D40 *)screenState;

    if (out != NULL) {
        *out = data->field_248;
    }
    return data->field_244;
}

/* The screen's width and height. */
s32 RhBase_GetScreenSize(s32 *outW, s32 *outH) {
    *outW = D_0032618C;
    *outH = currentTimingModeValue;
    return 1;
}

/* The depth range of the current z-buffer format. */
s32 RhBase_GetZMinMax(s32 *outMin, s32 *outMax) {
    typedef struct Flags_00209D80 {
        s8 active : 1;
        s8 useSaved : 1;
    } Flags_00209D80;

    typedef struct State_00209D80 {
        u8 pad0[0x18];
        s32 value;
        u8 pad1[4];
        Flags_00209D80 flags;
    } State_00209D80;

    extern State_00209D80 renderFrameState;
    extern Flags_00209D80 renderFrameData;
    extern s32 D_003261A8;

    State_00209D80 *state;
    s32 value;

    value = D_003261A8;
    state = &renderFrameState;
    if (renderFrameData.active) {
        if (state->flags.useSaved) {
            value = state->value;
        }
    }
    *outMin = 0;
    switch (value) {
    case 0x30:
        *outMax = 0x7FFFFFFF;
        break;
    case 0x31:
        *outMax = 0xFFFFFF;
        break;
    case 0x32:
    case 0x3A:
        *outMax = 0xFFFF;
        break;
    }
    return 1;
}

/* The screen centre in GS coordinates. */
s32 RhBase_GetScreenCenter(s32 *outX, s32 *outY) {
    *outX = screenCenterX;
    *outY = ScreenCenterY;
    return 1;
}

typedef struct {
    u8 pad[0x10];
    s32 index;
} State_00209E50;

typedef struct {
    s8 enabled : 1;
    s8 flag1 : 1;
} Flags_00209E50;

extern State_00209E50 renderFrameState; /* original: gRhBase_rl */
extern Flags_00209E50 renderFrameData;

/* The GS memory free for textures after the frame and z buffers (and any render frame). */
s32 RhBase_GetUserGsAddress(void) {
    u8 *base = screenState;
    State_00209E50 *state = &renderFrameState;
    s32 address;

    if (renderFrameData.enabled != 0) {
        address = state->index;
    } else {
        address = 0;
    }
    return *(s32 *)(base + 0x268) + (address << 5);
}

typedef struct {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
    s32 timer;
    u8 pad08[0xE8];
} Slot_00209E90;

extern Slot_00209E90 D_00326050[2];

/* Sets the colour both frame buffers are cleared to. */
s32 RhBase_SetClearColorEx(u8 r, u8 g, u8 b, u8 a) {
    D_00326050[0].r = r;
    D_00326050[0].g = g;
    D_00326050[0].b = b;
    D_00326050[0].a = a;
    D_00326050[0].timer = 0;
    D_00326050[1].r = r;
    D_00326050[1].g = g;
    D_00326050[1].b = b;
    D_00326050[1].a = a;
    D_00326050[1].timer = 0;
    return 1;
}

typedef struct State_00209EF0 {
    u8 pad00[0x60];
    u16 value60;
    u8 pad62[0xEE];
    u16 value150;
    u8 pad152[0xFE];
    s32 value250;
    s32 pad254;
    s32 value258;
    u8 pad25C[0x10];
    s32 flags26C;
} State_00209EF0;

/* The address (`back` picks the back buffer), pixel format and width of a frame buffer. */
s32 RhBase_GetBufferFormatEx(s32 back, s32 *outAddress, s32 *outPsm, s32 *outWidth) {
    State_00209EF0 *state = (State_00209EF0 *)screenState;
    u16 *frame;

    if (outAddress != NULL) {
        if ((state->flags26C & 1) == (back ? 1 : 0)) {
            frame = &state->value150;
        } else {
            frame = &state->value60;
        }
        *outAddress = (*frame & 0x1FF) << 5;
    }
    if (outPsm != NULL) {
        *outPsm = state->value250;
    }
    if (outWidth != NULL) {
        *outWidth = state->value258;
    }
    return 1;
}

/* Sets the function called at every vertical blank. */
s32 RhBase_SetVSyncCallback(void (*callback)(void)) {
    extern void (*vSyncCallback)(void);

    vSyncCallback = callback;
    return 1;
}

/* Sets the frame buffer register with write mask `mask` (the render frame's if one is on). */
void *RhBase_MaskFBuffer(void *packetIn, u32 mask) {
    typedef struct {
        s8 active : 1;
        s8 custom : 1;
        s8 unused : 6;
    } Flags_00209F70;
    typedef struct {
        s32 index;
        s32 unknown4;
        s32 unknown8;
        s32 base;
        s32 unknown10;
        s32 format;
        u8 unknown18[8];
        Flags_00209F70 flags;
    } State_00209F70;
    typedef struct {
        s32 base;
        u8 unknown4[0x24];
    } Entry_00209F70;
    typedef struct {
        u16 base;
        u8 width;
        u8 format;
    } Texture_00209F70;
    extern Entry_00209F70 D_00293F1C_2[];
    u8 *textureBase = screenState;
    State_00209F70 *state = (State_00209F70 *)&renderFrameState;
    Texture_00209F70 *texture;
    u64 *packet = packetIn;

    if (frameBufferIndex & 1) {
        texture = (Texture_00209F70 *)(textureBase + 0x150);
    } else {
        texture = (Texture_00209F70 *)(textureBase + 0x60);
    }
    ((u32 *)packet)[0] = 0x10000002;
    ((u32 *)packet)[1] = 0;
    ((u32 *)packet)[2] = 0x11000000;
    ((u32 *)packet)[3] = 0x51000002;
    packet[2] = ((u64)0x10000000 << 32) | 0x8001;
    packet[3] = 0xE;
    if (state->flags.active && state->flags.custom) {
        packet[4] = ((u64)mask << 32) |
            (((s64)state->format << 24) |
             (state->base | ((s64)(D_00293F1C_2[state->index].base >> 6) << 16)));
        packet += 5;
    } else {
        packet[4] = ((u64)mask << 32) |
            ((((u64)texture->format & 0x3F) << 24) |
             (((u64)texture->base & 0x1FF) | (((u64)texture->width & 0x3F) << 16)));
        packet += 5;
    }
    *packet++ = 0x4C;
    return packet;
}

typedef struct Flags_0020A0B0 {
    s8 enabled : 1;
    s8 apply : 1;
} Flags_0020A0B0;

typedef struct State_0020A0B0 {
    u8 pad00[0xC];
    s32 base;
    u8 pad10[8];
    s32 mode;
    s32 offset;
    Flags_0020A0B0 flags;
} State_0020A0B0;

typedef union Packet_0020A0B0 {
    u64 raw;
    struct {
        u16 value : 9;
        u16 reserved : 7;
        u8 pad02;
        u8 mode : 4;
        u8 other : 4;
        u8 clear : 1;
        u8 rest : 7;
        u8 pad05[3];
    } f;
} Packet_0020A0B0;

/* Turns z-buffer writes on (`write`) or off. */
s32 RhBase_SetZBufferMode(s32 cursor, s32 write) {
    extern u8 gSceVif1[];
    extern __int128 gowGif;
    extern Packet_0020A0B0 SceZBuf;
    extern Packet_0020A0B0 D_00325FC0;
    State_0020A0B0 *state = (State_0020A0B0 *)&renderFrameState;

    sceVif1PkInit((s32 *)gSceVif1, cursor);
    sceVif1PkCnt(gSceVif1, 0);
    sceVif1PkAddCode((s32 **)gSceVif1, 0x11000000);
    sceVif1PkAlign(gSceVif1, 2, 3);
    sceVif1PkOpenDirectHLCode(gSceVif1, 0);
    ((u64 *)&gowGif)[0] = ((u64)0x10000000 << 32) | 0x8000;
    ((u64 *)&gowGif)[1] = 0xE;
    sceVif1PkOpenGifTag(gSceVif1, gowGif);
    if (renderFrameData.enabled && state->flags.apply) {
        SceZBuf.f.value = state->base + state->offset;
        SceZBuf.f.mode = state->mode;
    } else {
        SceZBuf = D_00325FC0;
    }
    SceZBuf.f.clear = !write;
    sceVif1PkAddGsAD(gSceVif1, 0x4E, ((u64 *)&SceZBuf)[0]);
    sceVif1PkCloseGifTag(gSceVif1);
    sceVif1PkCloseDirectHLCode(gSceVif1);
    return sceVif1PkTerminate(gSceVif1);
}

typedef struct Flags_0020A280 {
    s8 enabled : 1;
    s8 apply : 1;
} Flags_0020A280;

typedef struct State_0020A280 {
    u8 pad00[0xC];
    s32 base;
    u8 pad10[8];
    s32 mode;
    s32 offset;
    Flags_0020A280 flags;
} State_0020A280;

typedef struct Packet_0020A280 {
    u16 value : 9;
    u16 reserved : 7;
    u8 pad02;
    u8 mode : 4;
    u8 other : 4;
} Packet_0020A280;

/* The z-buffer's address and format into `out`. */
void RhBase_GetZBufInfo(void *out) {
    extern Packet_0020A280 D_00325FC0;
    State_0020A280 *state = (State_0020A280 *)&renderFrameState;
    Packet_0020A280 *packet = out;

    if (renderFrameData.enabled && state->flags.apply) {
        packet->value = state->base + state->offset;
        packet->mode = state->mode;
    } else {
        packet->value = D_00325FC0.value;
        packet->mode = D_00325FC0.mode;
    }
}

/* Sets the GS fog colour. */
void *RhBase_SetFogColor(void *packet, void *color) {
    *(s32 *)((u8 *)packet + 0) = 0x10000002;
    *(s32 *)((u8 *)packet + 4) = 0;
    *(s32 *)((u8 *)packet + 8) = 0;
    *(s32 *)((u8 *)packet + 0xC) = 0x51000002;
    *(s64 *)((u8 *)packet + 0x10) = ((s64)0x10000000 << 32) | 0x8001;
    *(s64 *)((u8 *)packet + 0x18) = 0xE;
    *(s64 *)((u8 *)packet + 0x20) = ((s64)((u8 *)color)[0] << 16) |
        ((s64)((u8 *)color)[2] | ((s64)((u8 *)color)[1] << 8));
    *(s64 *)((u8 *)packet + 0x28) = 0x3D;
    return (u8 *)packet + 0x30;
}

/* Copies the shown frame buffer into main memory at `address`. */
void RhBase_CopyFrameBuffer(u32 address) {
    u8 *base = screenState;
    u16 *p;

    sceGsSyncPath(0, 0);
    if (frameBufferIndex & 1) {
        p = (u16 *)(base + 0x60);
    } else {
        p = (u16 *)(base + 0x150);
    }
    sceGsSetDefStoreImage(GSI, (*p & 0x1FF) << 5, 10, 10, 0, 0, 0x280, 0x1C0);
    FlushCache(0);
    sceGsExecStoreImage(GSI, (void *)(address & 0x0FFFFFFF));
    sceGsSyncPath(0, 0);
}

typedef struct {
    s32 id;
    s32 value4;
    s32 value8;
    s32 valueC;
    s32 value10;
    s32 mode;
    s32 kind;
    s32 value1C;
    s8 enabled : 1;
    s8 flag1 : 1;
} Full_0020A470;

typedef struct {
    s32 value0;
    s32 value4;
    s32 pad08[3];
    s32 sizes[2];
    s32 pad1C[3];
} Table_0020A470;

/* Books render frame `size` (an off-screen buffer) with pixel format `psm` and z format `zpsm`. Returns 0 if it
   does not fit. */
s32 RhBase_AssignRenderFrame(s32 size, s32 psm, s32 zpsm) {
    extern Table_0020A470 D_00293F1C_2[];
    u8 *base = screenState;
    Full_0020A470 *state = (Full_0020A470 *)&renderFrameState;
    s32 a = 0;
    s32 b = 0;

    if (renderFrameData.enabled != 0) {
        return 0;
    }
    state->id = size;
    state->value4 = D_00293F1C_2[size].value0;
    state->value8 = D_00293F1C_2[size].value4;
    state->mode = psm;
    state->kind = zpsm;
    switch (psm) {
    case 0:
    case 1:
        a = 1;
        break;
    case 2:
    case 10:
        a = 0;
        break;
    }
    switch (zpsm) {
    case 0x30:
    case 0x31:
        b = 1;
        break;
    case 0x32:
    case 0x3A:
        b = 0;
        break;
    }
    state->valueC = *(s32 *)(base + 0x268) >> 5;
    state->value1C = D_00293F1C_2[size].sizes[a];
    state->value10 = D_00293F1C_2[size].sizes[a] + D_00293F1C_2[size].sizes[b];
    if (state->valueC + state->value10 > 0x200) {
        return 0;
    }
    state->enabled = 1;
    state->flag1 = 0;
    return 1;
}

typedef struct Flags_0020A610 {
    s8 enabled : 1;
    s8 built : 1;
    s8 reserved : 6;
} Flags_0020A610;

typedef struct State_0020A610 {
    s32 texture;
    s32 width;
    s32 height;
    s32 base;
    s32 unused10;
    s32 format;
    s32 nextFormat;
    s32 endOffset;
    Flags_0020A610 flags;
} State_0020A610;

typedef struct Texture_0020A610 {
    s32 address;
    s32 unused[9];
} Texture_0020A610;

typedef struct Packet_0020A610 {
    s32 tag[4];
    s64 registers[10];
} Packet_0020A610;

/* Starts drawing into the booked render frame. */
void *RhBase_EnableRenderFrame(void *packetIn) {
    extern Texture_0020A610 D_00293F1C_2[];
    State_0020A610 *state = (State_0020A610 *)&renderFrameState;
    Packet_0020A610 *packet = packetIn;

    if (!renderFrameData.enabled) {
        return packetIn;
    }
    packet->tag[0] = 0x10000005;
    packet->tag[1] = 0;
    packet->tag[2] = 0x11000000;
    packet->tag[3] = 0x51000005;
    packet->registers[0] = 0x1000000000008004LL;
    packet->registers[1] = 0xE;
    packet->registers[2] = ((s64) state->format << 24) |
        (state->base | ((s64) (D_00293F1C_2[state->texture].address >> 6) << 16));
    packet->registers[3] = 0x4C;
    packet->registers[4] = ((s64) state->nextFormat << 24) |
        (s64) (state->base + state->endOffset);
    packet->registers[5] = 0x4E;
    packet->registers[6] = 1;
    packet->registers[7] = 0x4A;
    packet->registers[8] = ((s64) (state->width - 1) << 16) |
        ((s64) (state->height - 1) << 48);
    packet->registers[9] = 0x40;
    state->flags.built = 1;
    return (u8 *) packetIn + 0x60;
}

#ifndef GAME_H
/* The game translation unit already declares this global with its local type. */
extern unsigned char renderFrameState[]; /* original: gRhBase_rl */
#endif

typedef struct Flags_0020A760 {
    u8 padding[0x20];
    s8 enabled : 1;
    s8 pending : 1;
    s8 unused : 6;
} Flags_0020A760;

typedef struct Packet_0020A760 {
    s32 dmaTag;
    s32 dmaAddress;
    s32 vifCode0;
    s32 vifCode1;
    s64 gifTag;
    s64 gifRegisters;
    s64 environment[4];
    s64 frameMask;
    s64 frameMaskRegister;
    s64 scissor;
    s64 scissorRegister;
} Packet_0020A760;

typedef struct Context_0020A760 {
    u8 padding0[0x60];
    s64 environment0[4];
    u8 padding1[0xD0];
    s64 environment1[4];
    u8 padding2[0xCC];
    s32 width;
    s32 height;
} Context_0020A760;

/* Goes back to drawing into the frame buffer. */
void *RhBase_DisableRenderFrame(void *packetIn) {
    Context_0020A760 *context = (Context_0020A760 *)screenState;
    Flags_0020A760 *flags = (Flags_0020A760 *)&renderFrameState;
    s64 *environment;
    Packet_0020A760 *packet = packetIn;

    if (frameBufferIndex & 1) {
        environment = context->environment1;
    } else {
        environment = context->environment0;
    }
    if (!flags->enabled) {
        return packetIn;
    }
    packet->dmaTag = 0x10000005;
    packet->dmaAddress = 0;
    packet->vifCode0 = 0x11000000;
    packet->vifCode1 = 0x51000005;
    packet->gifTag = ((s64)0x10000000 << 32) | 0x8004;
    packet->gifRegisters = 0xE;
    packet->environment[0] = environment[0];
    packet->environment[1] = environment[1];
    packet->environment[2] = environment[2];
    packet->environment[3] = environment[3];
    packet->frameMask = 0;
    packet->frameMaskRegister = 0x4A;
    packet->scissor = ((s64)(context->width - 1) << 16)
                    | ((s64)(context->height - 1) << 48);
    packet->scissorRegister = 0x40;
    flags->pending = 0;
    return packet + 1;
}

typedef struct Flags_0020A870 {
    s8 enabled : 1;
    s8 draw : 1;
} Flags_0020A870;

typedef struct State_0020A870 {
    u8 pad[0x20];
    Flags_0020A870 flags;
} State_0020A870;

typedef struct Packet_0020A870 {
    u32 words[4];
    u64 tag;
    u64 registers;
    u64 alpha;
    u64 alphaRegister;
} Packet_0020A870;

typedef struct Color_0020A870 {
    f32 value;
} Color_0020A870;

extern Color_0020A870 D_00293F00;

/* Sets the default clear colour. */
static inline void default_color_0020A870(void *color, void *value) {
    *(Color_0020A870 *)color = *(Color_0020A870 *)value;
}

/* Whether the render frame is drawing. */
static inline s32 draw_0020A870(void *state) {
    return ((State_0020A870 *)state)->flags.draw;
}

/* One component of a colour, or its default. */
static inline s32 color_0020A870(u8 *color, s32 component) {
    if (color != NULL) {
        return color[component];
    }
    return 0;
}

/* Clears the render frame to `color` (or its default). */
void *RhBase_ClearRenderFrame(u8 *packet, u8 *color) {
    s32 sceGsSetDefClear(void *, s32, s32, s32, s32, s32, u8, u8, u8, u8, s32);
    Color_0020A870 defaultColor;
    State_0020A870 *state = (State_0020A870 *)&renderFrameState;
    s32 alpha;
    s32 red;
    s32 green;

    default_color_0020A870(&defaultColor, &D_00293F00);
    if (!renderFrameData.enabled) {
        return packet;
    }
    if (!draw_0020A870(state)) {
        return packet;
    }
    if (color == NULL) {
        color = (u8 *)&defaultColor;
    }
    ((Packet_0020A870 *)packet)->words[0] = 0x10000009;
    ((Packet_0020A870 *)packet)->words[1] = 0;
    ((Packet_0020A870 *)packet)->words[2] = 0x11000000;
    ((Packet_0020A870 *)packet)->words[3] = 0x51000009;
    ((Packet_0020A870 *)packet)->tag = 0x1000000000008008ULL;
    ((Packet_0020A870 *)packet)->registers = 0xE;
    ((Packet_0020A870 *)packet)->alpha = 0;
    ((Packet_0020A870 *)packet)->alphaRegister = 0x4A;
    packet += 0x30;
    alpha = color_0020A870(color, 3);
    red = color_0020A870(color, 0);
    green = color_0020A870(color, 1);
    packet += sceGsSetDefClear(packet, 2, 0, 0, 0xFFF, 0xFFF,
                           color_0020A870(color, 2), green, red, alpha, 0) * 0x10;
    ((u64 *)packet)[0] = 1;
    ((u64 *)packet)[1] = 0x4A;
    return packet + 0x10;
}

/* Frees the render frame. */
void RhBase_FreeRenderFrame(void) {
    renderFrameData.enabled = 0;
    renderFrameData.flag1 = 0;
}

/* The texture registers that read the render frame, into `tex0` and `tex1`. */
s32 RhBase_GetTextureInfoForRender(void *tex0, void *tex1) {
    typedef struct {
        s32 index;
        s32 unk4;
        s32 unk8;
        s32 position;
        s32 unk10;
        s32 value;
    } State_0020AA30;
    typedef struct {
        s32 value;
        s32 padding[9];
    } Entry_0020AA30;
    typedef struct {
        u64 position : 14;
        u64 quotient : 6;
        u64 value : 6;
        u64 kind : 4;
        u64 otherKind : 4;
        u64 enabled : 1;
        u64 mode : 2;
        u64 number : 14;
        u64 extra : 4;
        u64 flag : 1;
        u64 count : 5;
        u64 state : 3;
    } Record_0020AA30;
    typedef struct {
        u64 flag0 : 1;
        u64 flag1 : 1;
        u64 mode : 3;
        u64 enabled : 1;
        u64 state : 3;
        u64 flag9 : 1;
        u64 padding0 : 9;
        u64 extra : 2;
        u64 padding1 : 11;
        u64 number : 12;
    } Extra_0020AA30;
    extern Entry_0020AA30 D_00293F1C_2[];
    extern Entry_0020AA30 D_00293F20_2[];
    State_0020AA30 *state = (State_0020AA30 *)&renderFrameState;
    s32 first;
    s32 second;
    s32 kind;
    Record_0020AA30 *record = tex0;
    Extra_0020AA30 *extra = tex1;

    if (renderFrameData.enabled == 0) {
        return 0;
    }
    if (record != NULL) {
        first = D_00293F1C_2[state->index].value;
        second = D_00293F20_2[state->index].value;
        record->position = state->position << 5;
        record->quotient = first >> 6;
        record->value = state->value;
        if (first < 0x141) {
            kind = 9;
        } else {
            kind = 10;
        }
        record->kind = kind;
        if (second < 0xE1) {
            kind = 8;
        } else {
            kind = 9;
        }
        record->otherKind = kind;
        record->enabled = 1;
        record->mode = 0;
        record->number = 0;
        record->extra = 0;
        record->flag = 0;
        record->count = 0;
        record->state = 1;
    }
    if (extra != NULL) {
        extra->flag0 = 0;
        extra->mode = 0;
        extra->enabled = 1;
        extra->state = 1;
        extra->flag9 = 0;
        extra->extra = 0;
        extra->number = 0;
    }
    return 1;
}

typedef struct {
    u64 x : 9;
    u64 reserved : 55;
} Coord_0020AD10;

typedef struct {
    u32 reserved;
    u32 reserved1 : 12;
    u32 height : 11;
    u32 reserved2 : 9;
} Display_0020AD10;

typedef struct {
    u8 reserved0[0x10];
    Coord_0020AD10 firstX;
    Display_0020AD10 firstDisplay;
    u8 reserved20[0x18];
    Coord_0020AD10 secondX;
    Display_0020AD10 secondDisplay;
    u8 reserved48[0x18];
    Coord_0020AD10 thirdX;
    u8 reserved68[8];
    Coord_0020AD10 fourthX;
    u8 reserved78[0x88];
    u8 firstColor[4];
    s32 firstColorWord;
    u8 reserved108[0x48];
    Coord_0020AD10 fifthX;
    u8 reserved158[8];
    Coord_0020AD10 sixthX;
    u8 reserved168[0x88];
    u8 secondColor[4];
    s32 secondColorWord;
    u8 reserved1F8[0x40];
    s32 mode;
    s32 width;
    s32 height;
    f32 scale;
    s32 field248;
    s32 field24C;
    s32 firstMode;
    s32 firstIndex;
    s32 secondMode;
    s32 secondIndex;
    s32 originX;
    s32 originY;
    s32 offset;
    s32 field26C;
} State_0020AD10;

typedef struct {
    s32 value;
    u8 reserved[0x24];
} Entry_0020AD10;

typedef struct {
    f32 value;
    u8 reserved[0x24];
} Scale_0020AD10;

typedef struct {
    s32 values[2];
    u8 reserved[0x20];
} Sizes_0020AD10;

/* A 12.4 fixed-point value as an integer. */
static inline s32 from_fixed_0020AD10(s32 value) {
    return value >> 6;
}

/* Sets up the screen state for mode `mode`: sizes, buffers, the GS environment. */
void lRhBase_InitScreenVariables(void *stateIn, s32 mode, s32 interlace, s32 field) {
    extern Entry_0020AD10 D_00293F1C_2[];
    extern Entry_0020AD10 D_00293F20_2[];
    extern Scale_0020AD10 D_00293F24[];
    extern Entry_0020AD10 D_00293F28[];
    extern Entry_0020AD10 D_00293F2C[];
    extern Sizes_0020AD10 D_00293F30[];
    State_0020AD10 *state = stateIn;

    state->mode = mode;
    state->width = D_00293F1C_2[mode].value;
    state->height = D_00293F20_2[mode].value;
    state->scale = D_00293F24[mode].value;
    state->field248 = D_00293F28[mode].value;
    state->field24C = D_00293F2C[mode].value;
    state->firstMode = interlace;
    switch (interlace) {
    case 0:
    case 1:
        state->firstIndex = 1;
        break;
    case 2:
    case 10:
        state->firstIndex = 0;
        break;
    }
    state->secondMode = field;
    switch (field) {
    case 0x30:
    case 0x31:
        state->secondIndex = 1;
        break;
    case 0x32:
    case 0x3A:
        state->secondIndex = 0;
        break;
    }
    state->originX = 0x800;
    state->originY = 0x800;
    state->offset = D_00293F30[mode].values[state->secondIndex] + D_00293F30[mode].values[state->firstIndex] * 2;
    state->offset = from_fixed_0020AD10((state->offset << 13) >> 2);
    sceGsSetDefDBuff(stateIn, (s16)interlace, (s16)D_00293F1C_2[mode].value, (s16)D_00293F20_2[mode].value, 3, (s16)field, 1);
    if (state->firstX.x == state->secondX.x) {
        state->firstX.x = 0;
        state->secondX.x = D_00293F30[mode].values[state->firstIndex];
        state->thirdX.x = state->secondX.x;
        state->fifthX.x = state->firstX.x;
        state->fourthX.x = D_00293F30[mode].values[state->firstIndex] * 2;
        state->sixthX.x = state->fourthX.x;
        state->firstDisplay.height = state->secondDisplay.height = D_00293F20_2[mode].value - 1;
    }
    state->firstColor[0] = 0;
    state->firstColor[1] = 0;
    state->firstColor[2] = 0x80;
    state->firstColor[3] = 0xFF;
    state->firstColorWord = 0;
    state->secondColor[0] = 0;
    state->secondColor[1] = 0;
    state->secondColor[2] = 0x80;
    state->secondColor[3] = 0xFF;
    state->secondColorWord = 0;
    state->field26C = 0;
}

/* Resets the GS and VIF1 for mode `mode`. */
s32 lRhBase_InitGsAndVif(s32 mode) {
    extern void sceVif1PkAddGsAD();

    D_00326180 = 0x63721405 | ((u64)0x72630514 << 32);
    sceVif1PkInit(D_00325F00, mode);
    sceVif1PkCnt(D_00325F00, 0);
    sceVif1PkAddCode(D_00325F00, 0x01000404);
    sceVif1PkAddData(D_00325F00, 0x20000000);
    sceVif1PkAddData(D_00325F00, 0x05000000);
    sceVif1PkAlign(D_00325F00, 2, 3);
    sceVif1PkOpenDirectHLCode(D_00325F00, 0);
    *(u64 *)&D_00325EF0 = 0x8000 | ((u64)0x10000000 << 32);
    *((u64 *)&D_00325EF0 + 1) = 0xE;
    sceVif1PkOpenGifTag(D_00325F00, D_00325EF0);
    sceVif1PkAddGsAD(D_00325F00, 0x46, 1);
    sceVif1PkAddGsAD(D_00325F00, 0x40, ((u64)(D_0032618C - 1) << 16) | ((u64)(currentTimingModeValue - 1) << 48));
    sceVif1PkAddGsAD(D_00325F00, 0x1A, 1);
    sceVif1PkAddGsAD(D_00325F00, 0x3B, (u64)0x80 << 32);
    sceVif1PkAddGsAD(D_00325F00, 0x3D, 0xC0C0C0);
    sceVif1PkAddGsAD(D_00325F00, 0x45, 1);
    sceVif1PkAddGsAD(D_00325F00, 0x44, D_00326180);
    sceVif1PkCloseGifTag(D_00325F00);
    sceVif1PkCloseDirectHLCode(D_00325F00);
    return sceVif1PkTerminate(D_00325F00);
}

/* Sets a random dither matrix (`on`). */
void lRhBase_SetRandomDither(s32 on) {
    extern void sceVif1PkAddGsAD();
    u8 buffer[0x40];
    u8 *packet;
    u64 *tag;
    s32 shift;

    packet = (u8 *) (((u32) buffer + 0xF) & ~0xF);
    tag = (u64 *) (packet + 0x20);
    shift = (func_0019A5C8() % 16) * 4;
    D_00326180 = (D_00326180 >> shift) | (D_00326180 << (0x40 - shift));
    sceVif1PkInit(packet, on);
    sceVif1PkCnt(packet, 0);
    sceVif1PkAlign(packet, 2, 3);
    sceVif1PkOpenDirectHLCode(packet, 0);
    tag[0] = 0x1000000000008000ULL;
    tag[1] = 0xE;
    sceVif1PkOpenGifTag(packet, *(__int128 *) tag);
    sceVif1PkAddGsAD(packet, 0x45, 1);
    sceVif1PkAddGsAD(packet, 0x44, D_00326180);
    sceVif1PkCloseGifTag(packet);
    sceVif1PkCloseDirectHLCode(packet);
    sceVif1PkTerminate(packet);
}

#include "common.h"

/* The current end of the VIF packet being built (where the next primitive goes). */
s32 RhBase_GetVifPacketArea(void) {
    return D_003261D0;
}

/* Sets the end of the VIF packet being built. */
void RhBase_SetVifPacketArea(s32 cursor) {
    D_003261D0 = cursor;
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
    *outH = D_00326190;
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
    extern Flags_00209D80 D_00325F40;
    extern s32 D_003261A8;

    State_00209D80 *state;
    s32 value;

    value = D_003261A8;
    state = &renderFrameState;
    if (D_00325F40.active) {
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
    *outX = D_003261B0;
    *outY = D_003261B4;
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
extern Flags_00209E50 D_00325F40;

/* The GS memory free for textures after the frame and z buffers (and any render frame). */
s32 RhBase_GetUserGsAddress(void) {
    u8 *base = screenState;
    State_00209E50 *state = &renderFrameState;
    s32 address;

    if (D_00325F40.enabled != 0) {
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
    extern void (*D_003261E4)(void);

    D_003261E4 = callback;
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
    extern Entry_00209F70 D_00293F1C[];
    u8 *textureBase = screenState;
    State_00209F70 *state = (State_00209F70 *)&renderFrameState;
    Texture_00209F70 *texture;
    u64 *packet = packetIn;

    if (D_003261BC & 1) {
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
             (state->base | ((s64)(D_00293F1C[state->index].base >> 6) << 16)));
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

typedef struct GifTag_0020A0B0 {
    u64 lo;
    u64 hi;
} GifTag_0020A0B0;

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
    if (D_00325F40.enabled && state->flags.apply) {
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

    if (D_00325F40.enabled && state->flags.apply) {
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
    if (D_003261BC & 1) {
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
    s8 enabled : 1;
} Flags_0020A470;

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
    extern Table_0020A470 D_00293F1C[];
    u8 *base = screenState;
    Full_0020A470 *state = (Full_0020A470 *)&renderFrameState;
    s32 a = 0;
    s32 b = 0;

    if (D_00325F40.enabled != 0) {
        return 0;
    }
    state->id = size;
    state->value4 = D_00293F1C[size].value0;
    state->value8 = D_00293F1C[size].value4;
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
    state->value1C = D_00293F1C[size].sizes[a];
    state->value10 = D_00293F1C[size].sizes[a] + D_00293F1C[size].sizes[b];
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
    extern Texture_0020A610 D_00293F1C[];
    State_0020A610 *state = (State_0020A610 *)&renderFrameState;
    Packet_0020A610 *packet = packetIn;

    if (!D_00325F40.enabled) {
        return packetIn;
    }
    packet->tag[0] = 0x10000005;
    packet->tag[1] = 0;
    packet->tag[2] = 0x11000000;
    packet->tag[3] = 0x51000005;
    packet->registers[0] = 0x1000000000008004LL;
    packet->registers[1] = 0xE;
    packet->registers[2] = ((s64) state->format << 24) |
        (state->base | ((s64) (D_00293F1C[state->texture].address >> 6) << 16));
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

    if (D_003261BC & 1) {
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
    if (!D_00325F40.enabled) {
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
    D_00325F40.enabled = 0;
    D_00325F40.flag1 = 0;
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
    extern Entry_0020AA30 D_00293F1C[];
    extern Entry_0020AA30 D_00293F20[];
    State_0020AA30 *state = (State_0020AA30 *)&renderFrameState;
    s32 first;
    s32 second;
    s32 kind;
    Record_0020AA30 *record = tex0;
    Extra_0020AA30 *extra = tex1;

    if (D_00325F40.enabled == 0) {
        return 0;
    }
    if (record != NULL) {
        first = D_00293F1C[state->index].value;
        second = D_00293F20[state->index].value;
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
    extern Entry_0020AD10 D_00293F1C[];
    extern Entry_0020AD10 D_00293F20[];
    extern Scale_0020AD10 D_00293F24[];
    extern Entry_0020AD10 D_00293F28[];
    extern Entry_0020AD10 D_00293F2C[];
    extern Sizes_0020AD10 D_00293F30[];
    State_0020AD10 *state = stateIn;

    state->mode = mode;
    state->width = D_00293F1C[mode].value;
    state->height = D_00293F20[mode].value;
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
    sceGsSetDefDBuff(stateIn, (s16)interlace, (s16)D_00293F1C[mode].value, (s16)D_00293F20[mode].value, 3, (s16)field, 1);
    if (state->firstX.x == state->secondX.x) {
        state->firstX.x = 0;
        state->secondX.x = D_00293F30[mode].values[state->firstIndex];
        state->thirdX.x = state->secondX.x;
        state->fifthX.x = state->firstX.x;
        state->fourthX.x = D_00293F30[mode].values[state->firstIndex] * 2;
        state->sixthX.x = state->fourthX.x;
        state->firstDisplay.height = state->secondDisplay.height = D_00293F20[mode].value - 1;
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
    sceVif1PkAddGsAD(D_00325F00, 0x40, ((u64)(D_0032618C - 1) << 16) | ((u64)(D_00326190 - 1) << 48));
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

/* Copies `size` bytes; returns the end of the copy. */
u8 *RhMem_CopyMemory(u8 *dst, u8 *src, s32 size) {
    if (size > 0) {
        do {
            size -= 1;
            *dst = *src;
            src += 1;
            dst += 1;
        } while (size > 0);
    }
    return dst;
}

/* Copies `count` words; returns the end of the copy. */
void *RhMem_CopyMemory4(void *dest, void *source, s32 count) {
    s32 *dst = dest;
    s32 *src = source;

    if (count > 0) {
        do {
            count--;
            *dst = *src;
            src++;
            dst++;
        } while (count > 0);
    }
    return dst;
}

/* Copies `count` quadwords; returns the end of the copy. */
void *RhMem_CopyMemory16(void *dest, void *source, s32 count) {
    __int128 *dst = dest;
    __int128 *src = source;

    if (count > 0) {
        do {
            count -= 1;
            *dst = *src;
            src++;
            dst++;
        } while (count > 0);
    }
    return dst;
}

/* Fills `size` bytes with `value`. */
s8 *RhMem_FillMemory(s8 *dst, s8 value, s32 size) {
    if (size > 0) {
        do {
            *dst = value;
            size -= 1;
            dst += 1;
        } while (size > 0);
    }
    return dst;
}

/* Fills `count` words with `val`. */
void *RhMem_FillMemory4(void *dst, s32 val, s32 count) {
    s32 *p = dst;

    while (count > 0) {
        *p++ = val;
        count--;
    }
    return p;
}

/* Fills `count` doublewords with `value`. */
s64 *RhMem_FillMemory8(s64 *dst, s64 value, s32 count) {
    while (count > 0) {
        *dst = value;
        count -= 1;
        dst++;
    }
    return dst;
}

/* The cosine of an angle in the game's units (0x10000 = 360 degrees), from the table. */
f32 RhMath_CosI(s32 angle) {
    f32 sign;
    f32 *samples;
    f32 sample0;
    f32 sample1;
    s32 fraction;

    angle = (s16)(angle + 0x4000);
    sign = 1.0f;
    if (angle < 0) {
        sign = -1.0f;
        angle = -angle;
    }
    if (angle > 0x4000) {
        angle = 0x8000 - angle;
    }
    if ((angle & 0x3FFF) == 0) {
        return angle == 0x4000 ? sign : 0.0f;
    }
    fraction = angle & 0xF;
    samples = &gRhMath_adwSinTable[angle >> 4];
    sample0 = samples[0];
    sample1 = samples[1];
    return sign * (sample0 * (16 - fraction) + sample1 * fraction) / 16.0f;
}

/* The sine of an angle in the game's units (0x10000 = 360 degrees), from the table. */
f32 RhMath_SinI(s32 angle) {
    f32 sign;
    f32 *samples;
    f32 sample0;
    f32 sample1;
    s32 fraction;

    angle = (s16)angle;
    sign = 1.0f;
    if (angle < 0) {
        sign = -1.0f;
        angle = -angle;
    }
    if (angle > 0x4000) {
        angle = 0x8000 - angle;
    }
    if ((angle & 0x3FFF) == 0) {
        return angle == 0x4000 ? sign : 0.0f;
    }
    fraction = angle & 0xF;
    samples = &gRhMath_adwSinTable[angle >> 4];
    sample0 = samples[0];
    sample1 = samples[1];
    return sign * (sample0 * (16 - fraction) + sample1 * fraction) / 16.0f;
}

/* The cosine of an angle in radians, from the table. */
f32 RhMath_Cos(f32 angle) {
    s32 phase;
    f32 sign;
    s32 fraction;
    f32 weight;
    f32 *entry;
    f32 lower;
    f32 upper;

    phase = (s16)(s32)(16384.0f + (0.5f + ((65536.0f * angle) / 6.2831855f)));
    sign = 1.0f;
    if (phase < 0) {
        sign = -1.0f;
        phase = -phase;
    }
    if (phase > 0x4000) {
        phase = 0x8000 - phase;
    }
    if ((phase & 0x3FFF) == 0) {
        if (phase == 0x4000) {
            return sign;
        }
        sign = 0.0f;
    } else {
        fraction = phase & 0xF;
        weight = fraction;
        entry = &gRhMath_adwSinTable[phase >> 4];
        lower = entry[0];
        upper = entry[1];
        sign = (sign * (lower * (16 - fraction) + upper * weight)) / 16.0f;
    }
    return sign;
}

/* The sine of an angle in radians, from the table. */
f32 RhMath_Sin(f32 angle) {
    s32 phase;
    f32 sign;
    s32 fraction;
    f32 weight;
    f32 *entry;
    f32 lower;
    f32 upper;

    phase = (s16)func_001A22C0(0.5f + ((65536.0f * angle) / 6.2831855f));
    sign = 1.0f;
    if (phase < 0) {
        sign = -1.0f;
        phase = -phase;
    }
    if (phase > 0x4000) {
        phase = 0x8000 - phase;
    }
    if ((phase & 0x3FFF) == 0) {
        if (phase == 0x4000) {
            return sign;
        }
        sign = 0.0f;
    } else {
        fraction = phase & 0xF;
        weight = fraction;
        entry = &gRhMath_adwSinTable[phase >> 4];
        lower = entry[0];
        upper = entry[1];
        sign = (sign * (lower * (16 - fraction) + upper * weight)) / 16.0f;
    }
    return sign;
}

/* Heap-sorts `count` records of `size` bytes at `base` with `compare`. */
void RhMath_HeapSortStruct(u8 *base, s32 count, s32 size, s32 (*compare)(u8 *, u8 *)) {
    s32 spA0;
    u8 *var_s3_2;
    u8 *temp_s3;
    s32 var_v0;
    s32 var_s3;
    s32 var_s4_2;
    s32 var_fp_2;
    s32 var_s2;
    u8 *sentinel;
    u8 *temp_s5;
    s32 var_s6;
    s32 var_s4;
    s32 var_fp;
    u8 *temp_s6;
    u8 *spB0;

    sentinel = &abTmpBuf;
    var_fp = count >> 1;
    temp_s5 = base - size;
    var_s2 = count;
    if (var_fp > 0) {
        spA0 = var_fp * size;
        do {
            var_s3 = var_fp;
            RhMem_CopyMemory(sentinel, temp_s5 + spA0, size);
            while ((var_s4 = var_s3 * 2) <= var_s2) {
                if (var_s4 < var_s2 &&
                    compare(temp_s5 + (var_s4 * size), temp_s5 + ((var_s4 + 1) * size)) < 0) {
                    var_s4 += 1;
                }
                temp_s6 = temp_s5 + (var_s4 * size);
                if (compare(sentinel, temp_s6) >= 0) {
                    break;
                }
                var_v0 = var_s3 * size;
                RhMem_CopyMemory(temp_s5 + var_v0, temp_s6, size);
                var_s3 = var_s4;
            }
            RhMem_CopyMemory(temp_s5 + (var_s3 * size), sentinel, size);
            var_fp -= 1;
            spA0 -= size;
        } while (var_fp > 0);
    }
    if (var_s2 > 1) {
        var_fp_2 = var_s2 * size;
        spB0 = temp_s5 + size;
        var_s3_2 = temp_s5 + var_fp_2;
        do {
            RhMem_CopyMemory(sentinel, var_s3_2, size);
            RhMem_CopyMemory(var_s3_2, spB0, size);
            var_s2 -= 1;
            var_s4_2 = 1;
            var_fp_2 -= size;
            while ((var_s6 = var_s4_2 * 2) <= var_s2) {
                if (var_s6 < var_s2 &&
                    compare(temp_s5 + (var_s6 * size), temp_s5 + ((var_s6 + 1) * size)) < 0) {
                    var_s6 += 1;
                }
                temp_s3 = temp_s5 + (var_s6 * size);
                if (compare(sentinel, temp_s3) >= 0) {
                    break;
                }
                RhMem_CopyMemory(temp_s5 + (var_s4_2 * size), temp_s3, size);
                var_s4_2 = var_s6;
            }
            RhMem_CopyMemory(temp_s5 + (var_s4_2 * size), sentinel, size);
            var_s3_2 = temp_s5 + var_fp_2;
        } while (var_s2 > 1);
    }
}

/* Starts the matrix stack. */
s32 RhGeom_Init(void) {
    D_0032A220 = 0;
    return 1;
}

/* Ends the matrix stack. */
s32 RhGeom_Term(void) {
    return 1;
}

/* Loads matrix `p` into the VU0 registers. */
asm void RhGeom_SetMatrix(void *p) {
    .set noreorder
    beqz a0, L_0020BAAC
    nop
    lqc2 vf28, 0x0(a0)
    lqc2 vf29, 0x10(a0)
    lqc2 vf30, 0x20(a0)
    b L_0020BAC0
    lqc2 vf31, 0x30(a0)
L_0020BAAC:
    vsub.xyzw vf31, vf0, vf0
    vadd.w vf31, vf31, vf0
    vmr32.xyzw vf30, vf31
    vmr32.xyzw vf29, vf30
    vmr32.xyzw vf28, vf29
L_0020BAC0:
    jr ra
    nop
}

/* Stores the VU0 matrix into `p`. */
asm void RhGeom_GetMatrix(void *p) {
    .set noreorder
    sqc2 vf28, 0x0(a0)
    sqc2 vf29, 0x10(a0)
    sqc2 vf30, 0x20(a0)
    jr ra
    sqc2 vf31, 0x30(a0)
}

/* Pushes matrix `matrix` on the matrix stack (VU0). */
asm void RhGeom_PushMatrix(s32 matrix) {
    .set noreorder
    lw a2, D_0032A220
    la v1, matrixStack
    sll a1, a2, 3
    subu a1, a1, a2
    sll a1, a1, 4
    addu v1, v1, a1
    sqc2 vf28, 0x0(v1)
    sqc2 vf29, 0x10(v1)
    sqc2 vf30, 0x20(v1)
    beqz a0, L_0020BB38
    sqc2 vf31, 0x30(v1)
    lqc2 vf28, 0x0(a0)
    lqc2 vf29, 0x10(a0)
    lqc2 vf30, 0x20(a0)
    lqc2 vf31, 0x30(a0)
    nop
L_0020BB38:
    lw v1, D_0032A220
    addiu v1, v1, 0x1
    .set reorder
    sw v1, D_0032A220
    jr ra
}

/* Pops the matrix stack. */
asm void RhGeom_PopMatrix(void) {
    .set noreorder
    lw a0, D_0032A220
    la v1, matrixStack
    addiu a0, a0, -0x1
    sw a0, D_0032A220
    lw a1, D_0032A220
    sll a0, a1, 3
    subu a0, a0, a1
    sll a0, a0, 4
    addu v1, v1, a0
    lqc2 vf28, 0x0(v1)
    lqc2 vf29, 0x10(v1)
    lqc2 vf30, 0x20(v1)
    jr ra
    lqc2 vf31, 0x30(v1)
}

/* Empties the matrix stack. */
s32 RhGeom_ResetMatrixStack(void) {
    D_0032A220 = 0;
    return 1;
}

/* Sets `matrix` to the identity. */
asm void RhGeom_UnitMatrix(void *matrix) {
    .set noreorder
    bnez a0, L_0020BBD0
    nop
    vsub.xyzw vf31, vf0, vf0
    vadd.w vf31, vf31, vf0
    vmr32.xyzw vf30, vf31
    vmr32.xyzw vf29, vf30
    b L_0020BBF4
    vmr32.xyzw vf28, vf29
L_0020BBD0:
    vsub.xyzw vf4, vf0, vf0
    vadd.w vf4, vf4, vf0
    vmr32.xyzw vf5, vf4
    vmr32.xyzw vf6, vf5
    vmr32.xyzw vf7, vf6
    sqc2 vf4, 0x30(a0)
    sqc2 vf5, 0x20(a0)
    sqc2 vf6, 0x10(a0)
    sqc2 vf7, 0x0(a0)
L_0020BBF4:
    jr ra
    nop
}

/* dst = dst x src (VU0). */
asm void RhGeom_MulMatrix(s32 dst, void *src) {
    .set noreorder
    bnez a0, L_0020BC6C
    nop
    lqc2 vf8, 0x0(a1)
    lqc2 vf9, 0x10(a1)
    lqc2 vf10, 0x20(a1)
    lqc2 vf11, 0x30(a1)
    vmulax.xyzw ACC, vf28, vf8x
    vmadday.xyzw ACC, vf29, vf8y
    vmaddaz.xyzw ACC, vf30, vf8z
    vmaddw.xyzw vf20, vf31, vf8w
    vmulax.xyzw ACC, vf28, vf9x
    vmadday.xyzw ACC, vf29, vf9y
    vmaddaz.xyzw ACC, vf30, vf9z
    vmaddw.xyzw vf21, vf31, vf9w
    vmulax.xyzw ACC, vf28, vf10x
    vmadday.xyzw ACC, vf29, vf10y
    vmaddaz.xyzw ACC, vf30, vf10z
    vmaddw.xyzw vf22, vf31, vf10w
    vmulax.xyzw ACC, vf28, vf11x
    vmadday.xyzw ACC, vf29, vf11y
    vmaddaz.xyzw ACC, vf30, vf11z
    vmaddw.xyzw vf23, vf31, vf11w
    vmove.xyzw vf28, vf20
    vmove.xyzw vf29, vf21
    vmove.xyzw vf30, vf22
    b L_0020BCDC
    vmove.xyzw vf31, vf23
L_0020BC6C:
    lqc2 vf4, 0x0(a0)
    lqc2 vf5, 0x10(a0)
    lqc2 vf6, 0x20(a0)
    lqc2 vf7, 0x30(a0)
    lqc2 vf8, 0x0(a1)
    vmulax.xyzw ACC, vf4, vf8x
    vmadday.xyzw ACC, vf5, vf8y
    vmaddaz.xyzw ACC, vf6, vf8z
    vmaddw.xyzw vf9, vf7, vf8w
    sqc2 vf9, 0x0(a0)
    lqc2 vf8, 0x10(a1)
    vmulax.xyzw ACC, vf4, vf8x
    vmadday.xyzw ACC, vf5, vf8y
    vmaddaz.xyzw ACC, vf6, vf8z
    vmaddw.xyzw vf9, vf7, vf8w
    sqc2 vf9, 0x10(a0)
    lqc2 vf8, 0x20(a1)
    vmulax.xyzw ACC, vf4, vf8x
    vmadday.xyzw ACC, vf5, vf8y
    vmaddaz.xyzw ACC, vf6, vf8z
    vmaddw.xyzw vf9, vf7, vf8w
    sqc2 vf9, 0x20(a0)
    lqc2 vf8, 0x30(a1)
    vmulax.xyzw ACC, vf4, vf8x
    vmadday.xyzw ACC, vf5, vf8y
    vmaddaz.xyzw ACC, vf6, vf8z
    vmaddw.xyzw vf9, vf7, vf8w
    sqc2 vf9, 0x30(a0)
L_0020BCDC:
    jr ra
    nop
}

/* dst = src x dst (VU0). */
asm void RhGeom_MulMatrixRev(s32 dst, s32 src) {
    .set noreorder
    bnez a0, L_0020BD5C
    nop
    lqc2 vf8, 0x0(a1)
    lqc2 vf9, 0x10(a1)
    lqc2 vf10, 0x20(a1)
    lqc2 vf11, 0x30(a1)
    vmulax.xyzw ACC, vf8, vf28x
    vmadday.xyzw ACC, vf9, vf28y
    vmaddaz.xyzw ACC, vf10, vf28z
    vmaddw.xyzw vf20, vf11, vf28w
    vmulax.xyzw ACC, vf8, vf29x
    vmadday.xyzw ACC, vf9, vf29y
    vmaddaz.xyzw ACC, vf10, vf29z
    vmaddw.xyzw vf21, vf11, vf29w
    vmulax.xyzw ACC, vf8, vf30x
    vmadday.xyzw ACC, vf9, vf30y
    vmaddaz.xyzw ACC, vf10, vf30z
    vmaddw.xyzw vf22, vf11, vf30w
    vmulax.xyzw ACC, vf8, vf31x
    vmadday.xyzw ACC, vf9, vf31y
    vmaddaz.xyzw ACC, vf10, vf31z
    vmaddw.xyzw vf23, vf11, vf31w
    vmove.xyzw vf28, vf20
    vmove.xyzw vf29, vf21
    vmove.xyzw vf30, vf22
    b L_0020BDCC
    vmove.xyzw vf31, vf23
L_0020BD5C:
    lqc2 vf4, 0x0(a1)
    lqc2 vf5, 0x10(a1)
    lqc2 vf6, 0x20(a1)
    lqc2 vf7, 0x30(a1)
    lqc2 vf8, 0x0(a0)
    vmulax.xyzw ACC, vf4, vf8x
    vmadday.xyzw ACC, vf5, vf8y
    vmaddaz.xyzw ACC, vf6, vf8z
    vmaddw.xyzw vf9, vf7, vf8w
    sqc2 vf9, 0x0(a0)
    lqc2 vf8, 0x10(a0)
    vmulax.xyzw ACC, vf4, vf8x
    vmadday.xyzw ACC, vf5, vf8y
    vmaddaz.xyzw ACC, vf6, vf8z
    vmaddw.xyzw vf9, vf7, vf8w
    sqc2 vf9, 0x10(a0)
    lqc2 vf8, 0x20(a0)
    vmulax.xyzw ACC, vf4, vf8x
    vmadday.xyzw ACC, vf5, vf8y
    vmaddaz.xyzw ACC, vf6, vf8z
    vmaddw.xyzw vf9, vf7, vf8w
    sqc2 vf9, 0x20(a0)
    lqc2 vf8, 0x30(a0)
    vmulax.xyzw ACC, vf4, vf8x
    vmadday.xyzw ACC, vf5, vf8y
    vmaddaz.xyzw ACC, vf6, vf8z
    vmaddw.xyzw vf9, vf7, vf8w
    sqc2 vf9, 0x30(a0)
L_0020BDCC:
    jr ra
    nop
}

typedef struct Matrix_0020BDE0 {
    f32 m[4][4];
} Matrix_0020BDE0;

/* dst = the inverse of matrix src. */
void RhGeom_InvertMatrix(void *dst, void *src) {
    Matrix_0020BDE0 result;
    f32 det;


    det = ((((Matrix_0020BDE0 *)src)->m[0][0] * ((((((Matrix_0020BDE0 *)src)->m[3][2] * (((Matrix_0020BDE0 *)src)->m[1][3] * ((Matrix_0020BDE0 *)src)->m[2][1]) + (((Matrix_0020BDE0 *)src)->m[3][3] * (((Matrix_0020BDE0 *)src)->m[1][1] * ((Matrix_0020BDE0 *)src)->m[2][2]) + ((Matrix_0020BDE0 *)src)->m[3][1] * (((Matrix_0020BDE0 *)src)->m[1][2] * ((Matrix_0020BDE0 *)src)->m[2][3])))
            - ((Matrix_0020BDE0 *)src)->m[3][1] * (((Matrix_0020BDE0 *)src)->m[1][3] * ((Matrix_0020BDE0 *)src)->m[2][2])) - ((Matrix_0020BDE0 *)src)->m[3][3] * (((Matrix_0020BDE0 *)src)->m[1][2] * ((Matrix_0020BDE0 *)src)->m[2][1])) - ((Matrix_0020BDE0 *)src)->m[3][2] * (((Matrix_0020BDE0 *)src)->m[1][1] * ((Matrix_0020BDE0 *)src)->m[2][3])) - ((Matrix_0020BDE0 *)src)->m[0][1] * ((((((Matrix_0020BDE0 *)src)->m[3][2] * (((Matrix_0020BDE0 *)src)->m[1][3] * ((Matrix_0020BDE0 *)src)->m[2][0]) + (((Matrix_0020BDE0 *)src)->m[3][3] * (((Matrix_0020BDE0 *)src)->m[1][0] * ((Matrix_0020BDE0 *)src)->m[2][2]) + ((Matrix_0020BDE0 *)src)->m[3][0] * (((Matrix_0020BDE0 *)src)->m[1][2] * ((Matrix_0020BDE0 *)src)->m[2][3])))
            - ((Matrix_0020BDE0 *)src)->m[3][0] * (((Matrix_0020BDE0 *)src)->m[1][3] * ((Matrix_0020BDE0 *)src)->m[2][2])) - ((Matrix_0020BDE0 *)src)->m[3][3] * (((Matrix_0020BDE0 *)src)->m[1][2] * ((Matrix_0020BDE0 *)src)->m[2][0])) - ((Matrix_0020BDE0 *)src)->m[3][2] * (((Matrix_0020BDE0 *)src)->m[1][0] * ((Matrix_0020BDE0 *)src)->m[2][3]))) + ((Matrix_0020BDE0 *)src)->m[0][2] * ((((((Matrix_0020BDE0 *)src)->m[3][1] * (((Matrix_0020BDE0 *)src)->m[1][3] * ((Matrix_0020BDE0 *)src)->m[2][0]) + (((Matrix_0020BDE0 *)src)->m[3][3] * (((Matrix_0020BDE0 *)src)->m[1][0] * ((Matrix_0020BDE0 *)src)->m[2][1]) + ((Matrix_0020BDE0 *)src)->m[3][0] * (((Matrix_0020BDE0 *)src)->m[1][1] * ((Matrix_0020BDE0 *)src)->m[2][3])))
            - ((Matrix_0020BDE0 *)src)->m[3][0] * (((Matrix_0020BDE0 *)src)->m[1][3] * ((Matrix_0020BDE0 *)src)->m[2][1])) - ((Matrix_0020BDE0 *)src)->m[3][3] * (((Matrix_0020BDE0 *)src)->m[1][1] * ((Matrix_0020BDE0 *)src)->m[2][0])) - ((Matrix_0020BDE0 *)src)->m[3][1] * (((Matrix_0020BDE0 *)src)->m[1][0] * ((Matrix_0020BDE0 *)src)->m[2][3]))) - ((Matrix_0020BDE0 *)src)->m[0][3] * ((((((Matrix_0020BDE0 *)src)->m[3][1] * (((Matrix_0020BDE0 *)src)->m[1][2] * ((Matrix_0020BDE0 *)src)->m[2][0]) + (((Matrix_0020BDE0 *)src)->m[3][2] * (((Matrix_0020BDE0 *)src)->m[1][0] * ((Matrix_0020BDE0 *)src)->m[2][1]) + ((Matrix_0020BDE0 *)src)->m[3][0] * (((Matrix_0020BDE0 *)src)->m[1][1] * ((Matrix_0020BDE0 *)src)->m[2][2])))
            - ((Matrix_0020BDE0 *)src)->m[3][0] * (((Matrix_0020BDE0 *)src)->m[1][2] * ((Matrix_0020BDE0 *)src)->m[2][1])) - ((Matrix_0020BDE0 *)src)->m[3][2] * (((Matrix_0020BDE0 *)src)->m[1][1] * ((Matrix_0020BDE0 *)src)->m[2][0])) - ((Matrix_0020BDE0 *)src)->m[3][1] * (((Matrix_0020BDE0 *)src)->m[1][0] * ((Matrix_0020BDE0 *)src)->m[2][2]));

    if (det != 0.0f) {
        result.m[0][0] = 1.0 * (((((((Matrix_0020BDE0 *)src)->m[3][2] * (((Matrix_0020BDE0 *)src)->m[1][3] * ((Matrix_0020BDE0 *)src)->m[2][1]) + (((Matrix_0020BDE0 *)src)->m[3][3] * (((Matrix_0020BDE0 *)src)->m[1][1] * ((Matrix_0020BDE0 *)src)->m[2][2]) + ((Matrix_0020BDE0 *)src)->m[3][1] * (((Matrix_0020BDE0 *)src)->m[1][2] * ((Matrix_0020BDE0 *)src)->m[2][3])))
            - ((Matrix_0020BDE0 *)src)->m[3][1] * (((Matrix_0020BDE0 *)src)->m[1][3] * ((Matrix_0020BDE0 *)src)->m[2][2])) - ((Matrix_0020BDE0 *)src)->m[3][3] * (((Matrix_0020BDE0 *)src)->m[1][2] * ((Matrix_0020BDE0 *)src)->m[2][1])) - ((Matrix_0020BDE0 *)src)->m[3][2] * (((Matrix_0020BDE0 *)src)->m[1][1] * ((Matrix_0020BDE0 *)src)->m[2][3])) / det);
        result.m[1][0] = -1.0 * (((((((Matrix_0020BDE0 *)src)->m[3][2] * (((Matrix_0020BDE0 *)src)->m[1][3] * ((Matrix_0020BDE0 *)src)->m[2][0]) + (((Matrix_0020BDE0 *)src)->m[3][3] * (((Matrix_0020BDE0 *)src)->m[1][0] * ((Matrix_0020BDE0 *)src)->m[2][2]) + ((Matrix_0020BDE0 *)src)->m[3][0] * (((Matrix_0020BDE0 *)src)->m[1][2] * ((Matrix_0020BDE0 *)src)->m[2][3])))
            - ((Matrix_0020BDE0 *)src)->m[3][0] * (((Matrix_0020BDE0 *)src)->m[1][3] * ((Matrix_0020BDE0 *)src)->m[2][2])) - ((Matrix_0020BDE0 *)src)->m[3][3] * (((Matrix_0020BDE0 *)src)->m[1][2] * ((Matrix_0020BDE0 *)src)->m[2][0])) - ((Matrix_0020BDE0 *)src)->m[3][2] * (((Matrix_0020BDE0 *)src)->m[1][0] * ((Matrix_0020BDE0 *)src)->m[2][3])) / det);
        result.m[2][0] = 1.0 * (((((((Matrix_0020BDE0 *)src)->m[3][1] * (((Matrix_0020BDE0 *)src)->m[1][3] * ((Matrix_0020BDE0 *)src)->m[2][0]) + (((Matrix_0020BDE0 *)src)->m[3][3] * (((Matrix_0020BDE0 *)src)->m[1][0] * ((Matrix_0020BDE0 *)src)->m[2][1]) + ((Matrix_0020BDE0 *)src)->m[3][0] * (((Matrix_0020BDE0 *)src)->m[1][1] * ((Matrix_0020BDE0 *)src)->m[2][3])))
            - ((Matrix_0020BDE0 *)src)->m[3][0] * (((Matrix_0020BDE0 *)src)->m[1][3] * ((Matrix_0020BDE0 *)src)->m[2][1])) - ((Matrix_0020BDE0 *)src)->m[3][3] * (((Matrix_0020BDE0 *)src)->m[1][1] * ((Matrix_0020BDE0 *)src)->m[2][0])) - ((Matrix_0020BDE0 *)src)->m[3][1] * (((Matrix_0020BDE0 *)src)->m[1][0] * ((Matrix_0020BDE0 *)src)->m[2][3])) / det);
        result.m[3][0] = -1.0 * (((((((Matrix_0020BDE0 *)src)->m[3][1] * (((Matrix_0020BDE0 *)src)->m[1][2] * ((Matrix_0020BDE0 *)src)->m[2][0]) + (((Matrix_0020BDE0 *)src)->m[3][2] * (((Matrix_0020BDE0 *)src)->m[1][0] * ((Matrix_0020BDE0 *)src)->m[2][1]) + ((Matrix_0020BDE0 *)src)->m[3][0] * (((Matrix_0020BDE0 *)src)->m[1][1] * ((Matrix_0020BDE0 *)src)->m[2][2])))
            - ((Matrix_0020BDE0 *)src)->m[3][0] * (((Matrix_0020BDE0 *)src)->m[1][2] * ((Matrix_0020BDE0 *)src)->m[2][1])) - ((Matrix_0020BDE0 *)src)->m[3][2] * (((Matrix_0020BDE0 *)src)->m[1][1] * ((Matrix_0020BDE0 *)src)->m[2][0])) - ((Matrix_0020BDE0 *)src)->m[3][1] * (((Matrix_0020BDE0 *)src)->m[1][0] * ((Matrix_0020BDE0 *)src)->m[2][2])) / det);

        result.m[0][1] = -1.0 * (
            ((((((Matrix_0020BDE0 *)src)->m[3][2] * (((Matrix_0020BDE0 *)src)->m[0][3] * ((Matrix_0020BDE0 *)src)->m[2][1]) + (((Matrix_0020BDE0 *)src)->m[3][3] * (((Matrix_0020BDE0 *)src)->m[0][1] * ((Matrix_0020BDE0 *)src)->m[2][2]) + ((Matrix_0020BDE0 *)src)->m[3][1] * (((Matrix_0020BDE0 *)src)->m[0][2] * ((Matrix_0020BDE0 *)src)->m[2][3])))
                - ((Matrix_0020BDE0 *)src)->m[3][1] * (((Matrix_0020BDE0 *)src)->m[0][3] * ((Matrix_0020BDE0 *)src)->m[2][2])) - ((Matrix_0020BDE0 *)src)->m[3][3] * (((Matrix_0020BDE0 *)src)->m[0][2] * ((Matrix_0020BDE0 *)src)->m[2][1])) - ((Matrix_0020BDE0 *)src)->m[3][2] * (((Matrix_0020BDE0 *)src)->m[0][1] * ((Matrix_0020BDE0 *)src)->m[2][3])) / det);
        result.m[1][1] = 1.0 * (
            ((((((Matrix_0020BDE0 *)src)->m[3][2] * (((Matrix_0020BDE0 *)src)->m[0][3] * ((Matrix_0020BDE0 *)src)->m[2][0]) + (((Matrix_0020BDE0 *)src)->m[3][3] * (((Matrix_0020BDE0 *)src)->m[0][0] * ((Matrix_0020BDE0 *)src)->m[2][2]) + ((Matrix_0020BDE0 *)src)->m[3][0] * (((Matrix_0020BDE0 *)src)->m[0][2] * ((Matrix_0020BDE0 *)src)->m[2][3])))
                - ((Matrix_0020BDE0 *)src)->m[3][0] * (((Matrix_0020BDE0 *)src)->m[0][3] * ((Matrix_0020BDE0 *)src)->m[2][2])) - ((Matrix_0020BDE0 *)src)->m[3][3] * (((Matrix_0020BDE0 *)src)->m[0][2] * ((Matrix_0020BDE0 *)src)->m[2][0])) - ((Matrix_0020BDE0 *)src)->m[3][2] * (((Matrix_0020BDE0 *)src)->m[0][0] * ((Matrix_0020BDE0 *)src)->m[2][3])) / det);
        result.m[2][1] = -1.0 * (
            ((((((Matrix_0020BDE0 *)src)->m[3][1] * (((Matrix_0020BDE0 *)src)->m[0][3] * ((Matrix_0020BDE0 *)src)->m[2][0]) + (((Matrix_0020BDE0 *)src)->m[3][3] * (((Matrix_0020BDE0 *)src)->m[0][0] * ((Matrix_0020BDE0 *)src)->m[2][1]) + ((Matrix_0020BDE0 *)src)->m[3][0] * (((Matrix_0020BDE0 *)src)->m[0][1] * ((Matrix_0020BDE0 *)src)->m[2][3])))
                - ((Matrix_0020BDE0 *)src)->m[3][0] * (((Matrix_0020BDE0 *)src)->m[0][3] * ((Matrix_0020BDE0 *)src)->m[2][1])) - ((Matrix_0020BDE0 *)src)->m[3][3] * (((Matrix_0020BDE0 *)src)->m[0][1] * ((Matrix_0020BDE0 *)src)->m[2][0])) - ((Matrix_0020BDE0 *)src)->m[3][1] * (((Matrix_0020BDE0 *)src)->m[0][0] * ((Matrix_0020BDE0 *)src)->m[2][3])) / det);
        result.m[3][1] = 1.0 * (
            ((((((Matrix_0020BDE0 *)src)->m[3][1] * (((Matrix_0020BDE0 *)src)->m[0][2] * ((Matrix_0020BDE0 *)src)->m[2][0]) + (((Matrix_0020BDE0 *)src)->m[3][2] * (((Matrix_0020BDE0 *)src)->m[0][0] * ((Matrix_0020BDE0 *)src)->m[2][1]) + ((Matrix_0020BDE0 *)src)->m[3][0] * (((Matrix_0020BDE0 *)src)->m[0][1] * ((Matrix_0020BDE0 *)src)->m[2][2])))
                - ((Matrix_0020BDE0 *)src)->m[3][0] * (((Matrix_0020BDE0 *)src)->m[0][2] * ((Matrix_0020BDE0 *)src)->m[2][1])) - ((Matrix_0020BDE0 *)src)->m[3][2] * (((Matrix_0020BDE0 *)src)->m[0][1] * ((Matrix_0020BDE0 *)src)->m[2][0])) - ((Matrix_0020BDE0 *)src)->m[3][1] * (((Matrix_0020BDE0 *)src)->m[0][0] * ((Matrix_0020BDE0 *)src)->m[2][2])) / det);

        result.m[0][2] = 1.0 * (
            ((((((Matrix_0020BDE0 *)src)->m[3][2] * (((Matrix_0020BDE0 *)src)->m[0][3] * ((Matrix_0020BDE0 *)src)->m[1][1]) + (((Matrix_0020BDE0 *)src)->m[3][3] * (((Matrix_0020BDE0 *)src)->m[0][1] * ((Matrix_0020BDE0 *)src)->m[1][2]) + ((Matrix_0020BDE0 *)src)->m[3][1] * (((Matrix_0020BDE0 *)src)->m[0][2] * ((Matrix_0020BDE0 *)src)->m[1][3])))
                - ((Matrix_0020BDE0 *)src)->m[3][1] * (((Matrix_0020BDE0 *)src)->m[0][3] * ((Matrix_0020BDE0 *)src)->m[1][2])) - ((Matrix_0020BDE0 *)src)->m[3][3] * (((Matrix_0020BDE0 *)src)->m[0][2] * ((Matrix_0020BDE0 *)src)->m[1][1])) - ((Matrix_0020BDE0 *)src)->m[3][2] * (((Matrix_0020BDE0 *)src)->m[0][1] * ((Matrix_0020BDE0 *)src)->m[1][3])) / det);
        result.m[1][2] = -1.0 * (
            ((((((Matrix_0020BDE0 *)src)->m[3][2] * (((Matrix_0020BDE0 *)src)->m[0][3] * ((Matrix_0020BDE0 *)src)->m[1][0]) + (((Matrix_0020BDE0 *)src)->m[3][3] * (((Matrix_0020BDE0 *)src)->m[0][0] * ((Matrix_0020BDE0 *)src)->m[1][2]) + ((Matrix_0020BDE0 *)src)->m[3][0] * (((Matrix_0020BDE0 *)src)->m[0][2] * ((Matrix_0020BDE0 *)src)->m[1][3])))
                - ((Matrix_0020BDE0 *)src)->m[3][0] * (((Matrix_0020BDE0 *)src)->m[0][3] * ((Matrix_0020BDE0 *)src)->m[1][2])) - ((Matrix_0020BDE0 *)src)->m[3][3] * (((Matrix_0020BDE0 *)src)->m[0][2] * ((Matrix_0020BDE0 *)src)->m[1][0])) - ((Matrix_0020BDE0 *)src)->m[3][2] * (((Matrix_0020BDE0 *)src)->m[0][0] * ((Matrix_0020BDE0 *)src)->m[1][3])) / det);
        result.m[2][2] = 1.0 * (
            ((((((Matrix_0020BDE0 *)src)->m[3][1] * (((Matrix_0020BDE0 *)src)->m[0][3] * ((Matrix_0020BDE0 *)src)->m[1][0]) + (((Matrix_0020BDE0 *)src)->m[3][3] * (((Matrix_0020BDE0 *)src)->m[0][0] * ((Matrix_0020BDE0 *)src)->m[1][1]) + ((Matrix_0020BDE0 *)src)->m[3][0] * (((Matrix_0020BDE0 *)src)->m[0][1] * ((Matrix_0020BDE0 *)src)->m[1][3])))
                - ((Matrix_0020BDE0 *)src)->m[3][0] * (((Matrix_0020BDE0 *)src)->m[0][3] * ((Matrix_0020BDE0 *)src)->m[1][1])) - ((Matrix_0020BDE0 *)src)->m[3][3] * (((Matrix_0020BDE0 *)src)->m[0][1] * ((Matrix_0020BDE0 *)src)->m[1][0])) - ((Matrix_0020BDE0 *)src)->m[3][1] * (((Matrix_0020BDE0 *)src)->m[0][0] * ((Matrix_0020BDE0 *)src)->m[1][3])) / det);
        result.m[3][2] = -1.0 * (
            ((((((Matrix_0020BDE0 *)src)->m[3][1] * (((Matrix_0020BDE0 *)src)->m[0][2] * ((Matrix_0020BDE0 *)src)->m[1][0]) + (((Matrix_0020BDE0 *)src)->m[3][2] * (((Matrix_0020BDE0 *)src)->m[0][0] * ((Matrix_0020BDE0 *)src)->m[1][1]) + ((Matrix_0020BDE0 *)src)->m[3][0] * (((Matrix_0020BDE0 *)src)->m[0][1] * ((Matrix_0020BDE0 *)src)->m[1][2])))
                - ((Matrix_0020BDE0 *)src)->m[3][0] * (((Matrix_0020BDE0 *)src)->m[0][2] * ((Matrix_0020BDE0 *)src)->m[1][1])) - ((Matrix_0020BDE0 *)src)->m[3][2] * (((Matrix_0020BDE0 *)src)->m[0][1] * ((Matrix_0020BDE0 *)src)->m[1][0])) - ((Matrix_0020BDE0 *)src)->m[3][1] * (((Matrix_0020BDE0 *)src)->m[0][0] * ((Matrix_0020BDE0 *)src)->m[1][2])) / det);

        result.m[0][3] = -1.0 * (
            ((((((Matrix_0020BDE0 *)src)->m[2][2] * (((Matrix_0020BDE0 *)src)->m[0][3] * ((Matrix_0020BDE0 *)src)->m[1][1]) + (((Matrix_0020BDE0 *)src)->m[2][3] * (((Matrix_0020BDE0 *)src)->m[0][1] * ((Matrix_0020BDE0 *)src)->m[1][2]) + ((Matrix_0020BDE0 *)src)->m[2][1] * (((Matrix_0020BDE0 *)src)->m[0][2] * ((Matrix_0020BDE0 *)src)->m[1][3])))
                - ((Matrix_0020BDE0 *)src)->m[2][1] * (((Matrix_0020BDE0 *)src)->m[0][3] * ((Matrix_0020BDE0 *)src)->m[1][2])) - ((Matrix_0020BDE0 *)src)->m[2][3] * (((Matrix_0020BDE0 *)src)->m[0][2] * ((Matrix_0020BDE0 *)src)->m[1][1])) - ((Matrix_0020BDE0 *)src)->m[2][2] * (((Matrix_0020BDE0 *)src)->m[0][1] * ((Matrix_0020BDE0 *)src)->m[1][3])) / det);
        result.m[1][3] = 1.0 * (
            ((((((Matrix_0020BDE0 *)src)->m[2][2] * (((Matrix_0020BDE0 *)src)->m[0][3] * ((Matrix_0020BDE0 *)src)->m[1][0]) + (((Matrix_0020BDE0 *)src)->m[2][3] * (((Matrix_0020BDE0 *)src)->m[0][0] * ((Matrix_0020BDE0 *)src)->m[1][2]) + ((Matrix_0020BDE0 *)src)->m[2][0] * (((Matrix_0020BDE0 *)src)->m[0][2] * ((Matrix_0020BDE0 *)src)->m[1][3])))
                - ((Matrix_0020BDE0 *)src)->m[2][0] * (((Matrix_0020BDE0 *)src)->m[0][3] * ((Matrix_0020BDE0 *)src)->m[1][2])) - ((Matrix_0020BDE0 *)src)->m[2][3] * (((Matrix_0020BDE0 *)src)->m[0][2] * ((Matrix_0020BDE0 *)src)->m[1][0])) - ((Matrix_0020BDE0 *)src)->m[2][2] * (((Matrix_0020BDE0 *)src)->m[0][0] * ((Matrix_0020BDE0 *)src)->m[1][3])) / det);
        result.m[2][3] = -1.0 * (
            ((((((Matrix_0020BDE0 *)src)->m[2][1] * (((Matrix_0020BDE0 *)src)->m[0][3] * ((Matrix_0020BDE0 *)src)->m[1][0]) + (((Matrix_0020BDE0 *)src)->m[2][3] * (((Matrix_0020BDE0 *)src)->m[0][0] * ((Matrix_0020BDE0 *)src)->m[1][1]) + ((Matrix_0020BDE0 *)src)->m[2][0] * (((Matrix_0020BDE0 *)src)->m[0][1] * ((Matrix_0020BDE0 *)src)->m[1][3])))
                - ((Matrix_0020BDE0 *)src)->m[2][0] * (((Matrix_0020BDE0 *)src)->m[0][3] * ((Matrix_0020BDE0 *)src)->m[1][1])) - ((Matrix_0020BDE0 *)src)->m[2][3] * (((Matrix_0020BDE0 *)src)->m[0][1] * ((Matrix_0020BDE0 *)src)->m[1][0])) - ((Matrix_0020BDE0 *)src)->m[2][1] * (((Matrix_0020BDE0 *)src)->m[0][0] * ((Matrix_0020BDE0 *)src)->m[1][3])) / det);
        result.m[3][3] = 1.0 * (
            ((((((Matrix_0020BDE0 *)src)->m[2][1] * (((Matrix_0020BDE0 *)src)->m[0][2] * ((Matrix_0020BDE0 *)src)->m[1][0]) + (((Matrix_0020BDE0 *)src)->m[2][2] * (((Matrix_0020BDE0 *)src)->m[0][0] * ((Matrix_0020BDE0 *)src)->m[1][1]) + ((Matrix_0020BDE0 *)src)->m[2][0] * (((Matrix_0020BDE0 *)src)->m[0][1] * ((Matrix_0020BDE0 *)src)->m[1][2])))
                - ((Matrix_0020BDE0 *)src)->m[2][0] * (((Matrix_0020BDE0 *)src)->m[0][2] * ((Matrix_0020BDE0 *)src)->m[1][1])) - ((Matrix_0020BDE0 *)src)->m[2][2] * (((Matrix_0020BDE0 *)src)->m[0][1] * ((Matrix_0020BDE0 *)src)->m[1][0])) - ((Matrix_0020BDE0 *)src)->m[2][1] * (((Matrix_0020BDE0 *)src)->m[0][0] * ((Matrix_0020BDE0 *)src)->m[1][2])) / det);

        *(Matrix_0020BDE0 *)dst = result;
    }
}

/* The rotation matrix for angles src (x, y, z) into dst. */
void RhGeom_GetRotXYZMatrix(void *dst, void *src) {
    f32 *matrix = dst;
    s32 *angles = src;
    f32 cx;
    f32 sx;
    f32 cy;
    f32 sy;
    f32 cz;
    f32 sz;

    cx = RhMath_CosI(angles[0]);
    sx = RhMath_SinI(angles[0]);
    cy = RhMath_CosI(angles[1]);
    sy = RhMath_SinI(angles[1]);
    cz = RhMath_CosI(angles[2]);
    sz = RhMath_SinI(angles[2]);
    matrix[0] = cy * cz;
    matrix[4] = cz * (sx * sy) - cx * sz;
    matrix[8] = cz * (cx * sy) + sx * sz;
    matrix[1] = cy * sz;
    matrix[5] = sz * (sx * sy) + cx * cz;
    matrix[9] = sz * (cx * sy) - sx * cz;
    matrix[2] = -sy;
    matrix[6] = sx * cy;
    matrix[10] = cx * cy;
    matrix[3] = 0.0f;
    matrix[7] = 0.0f;
    matrix[11] = 0.0f;
    matrix[12] = 0.0f;
    matrix[13] = 0.0f;
    matrix[14] = 0.0f;
    matrix[15] = 1.0f;
}

typedef struct Vec4_0020C750 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4_0020C750;


/* The rotation matrix turning around vector `axis` by `angle` into `dst`. */
void RhGeom_GetRotVectorMatrix(void *dst, void *axis, s32 angle) {
    f32 *m = dst;
    Vec4_0020C750 v;
    f32 c;
    f32 s;
    f32 t;

    v = *(Vec4_0020C750 *)axis;
    c = RhMath_CosI(angle);
    t = 1.0f - c;
    s = RhMath_SinI(angle);
    RhGeom_NormalizeVector(&v.x);
    m[0] = c + t * (v.x * v.x);
    m[4] = t * (v.x * v.y) - v.z * s;
    m[8] = t * (v.x * v.z) + v.y * s;
    m[1] = t * (v.x * v.y) + v.z * s;
    m[5] = c + t * (v.y * v.y);
    m[9] = t * (v.y * v.z) - v.x * s;
    m[2] = t * (v.x * v.z) - v.y * s;
    m[6] = t * (v.y * v.z) + v.x * s;
    m[10] = c + t * (v.z * v.z);
    m[12] = 0.0f;
    m[13] = 0.0f;
    m[14] = 0.0f;
    m[3] = 0.0f;
    m[7] = 0.0f;
    m[11] = 0.0f;
    m[15] = 1.0f;
}

typedef struct {
    f32 rotation[12];
    f32 translation[3];
} Matrix_0020C8F0;


/* The translation matrix for `pos` into `dst`. */
void RhGeom_GetTransMatrix(void *dst, f32 *pos) {
    Matrix_0020C8F0 *matrix = dst;

    RhGeom_UnitMatrix(dst);
    matrix->translation[0] = pos[0];
    matrix->translation[1] = pos[1];
    matrix->translation[2] = pos[2];
}

typedef struct {
    f32 m[3][4];
    f32 t[3];
} Matrix_0020C940;


/* The matrix scale x rotation x translation from p1 (scale), p2 (angles), p3 (position) into `dst`. */
void RhGeom_GetScaleRotXYZTransMatrix(void *dst, void *p1, void *p2, void *p3) {
    Matrix_0020C940 *mtx = dst;
    f32 *arg1 = p1;
    s32 *arg2 = p2;
    f32 *arg3 = p3;
    f32 cx;
    f32 sx;
    f32 cy;
    f32 sy;
    f32 cz;
    f32 sz;

    RhGeom_UnitMatrix(dst);
    if (arg3 != NULL) {
        mtx->t[0] = arg3[0];
        mtx->t[1] = arg3[1];
        mtx->t[2] = arg3[2];
    }
    if (arg2 != NULL) {
        cx = RhMath_CosI(arg2[0]);
        sx = RhMath_SinI(arg2[0]);
        cy = RhMath_CosI(arg2[1]);
        sy = RhMath_SinI(arg2[1]);
        cz = RhMath_CosI(arg2[2]);
        sz = RhMath_SinI(arg2[2]);
        mtx->m[0][0] = cy * cz;
        mtx->m[1][0] = sx * sy * cz - cx * sz;
        mtx->m[2][0] = cx * sy * cz + sx * sz;
        mtx->m[0][1] = cy * sz;
        mtx->m[1][1] = sx * sy * sz + cx * cz;
        mtx->m[2][1] = cx * sy * sz - sx * cz;
        mtx->m[0][2] = -sy;
        mtx->m[1][2] = sx * cy;
        mtx->m[2][2] = cx * cy;
    }
    if (arg1 != NULL) {
        mtx->m[0][0] *= arg1[0];
        mtx->m[0][1] *= arg1[0];
        mtx->m[0][2] *= arg1[0];
        mtx->m[1][0] *= arg1[1];
        mtx->m[1][1] *= arg1[1];
        mtx->m[1][2] *= arg1[1];
        mtx->m[2][0] *= arg1[2];
        mtx->m[2][1] *= arg1[2];
        mtx->m[2][2] *= arg1[2];
    }
}

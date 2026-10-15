#include "common.h"

s32 func_00209D20(void) {
    return D_003261D0;
}

void func_00209D30(s32 arg0) {
    D_003261D0 = arg0;
}

typedef struct {
    u8 padding[0x244];
    f32 field_244;
    s32 field_248;
} Data_00209D40;

f32 func_00209D40(s32 *arg0) {
    Data_00209D40 *data = (Data_00209D40 *)D_00325F50;

    if (arg0 != NULL) {
        *arg0 = data->field_248;
    }
    return data->field_244;
}

s32 func_00209D60(s32 *arg0, s32 *arg1) {
    *arg0 = D_0032618C;
    *arg1 = D_00326190;
    return 1;
}

s32 func_00209D80(s32 *arg0, s32 *arg1) {
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

    extern State_00209D80 D_00325F20;
    extern Flags_00209D80 D_00325F40;
    extern s32 D_003261A8;

    State_00209D80 *state;
    s32 value;

    value = D_003261A8;
    state = &D_00325F20;
    if (D_00325F40.active) {
        if (state->flags.useSaved) {
            value = state->value;
        }
    }
    *arg0 = 0;
    switch (value) {
    case 0x30:
        *arg1 = 0x7FFFFFFF;
        break;
    case 0x31:
        *arg1 = 0xFFFFFF;
        break;
    case 0x32:
    case 0x3A:
        *arg1 = 0xFFFF;
        break;
    }
    return 1;
}

s32 func_00209E30(s32 *arg0, s32 *arg1) {
    *arg0 = D_003261B0;
    *arg1 = D_003261B4;
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

extern State_00209E50 D_00325F20;
extern Flags_00209E50 D_00325F40;

s32 func_00209E50(void) {
    u8 *base = D_00325F50;
    State_00209E50 *state = &D_00325F20;
    s32 var_v0;

    if (D_00325F40.enabled != 0) {
        var_v0 = state->index;
    } else {
        var_v0 = 0;
    }
    return *(s32 *)(base + 0x268) + (var_v0 << 5);
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

s32 func_00209E90(u8 arg0, u8 arg1, u8 arg2, u8 arg3) {
    D_00326050[0].r = arg0;
    D_00326050[0].g = arg1;
    D_00326050[0].b = arg2;
    D_00326050[0].a = arg3;
    D_00326050[0].timer = 0;
    D_00326050[1].r = arg0;
    D_00326050[1].g = arg1;
    D_00326050[1].b = arg2;
    D_00326050[1].a = arg3;
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

s32 func_00209EF0(s32 arg0, s32 *arg1, s32 *arg2, s32 *arg3) {
    State_00209EF0 *state = (State_00209EF0 *)D_00325F50;
    u16 *var_v0;

    if (arg1 != NULL) {
        if ((state->flags26C & 1) == (arg0 ? 1 : 0)) {
            var_v0 = &state->value150;
        } else {
            var_v0 = &state->value60;
        }
        *arg1 = (*var_v0 & 0x1FF) << 5;
    }
    if (arg2 != NULL) {
        *arg2 = state->value250;
    }
    if (arg3 != NULL) {
        *arg3 = state->value258;
    }
    return 1;
}

s32 func_00209F60(void (*arg0)(void)) {
    extern void (*D_003261E4)(void);

    D_003261E4 = arg0;
    return 1;
}

void *func_00209F70(void *arg0, u32 arg1) {
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
    u8 *textureBase = D_00325F50;
    State_00209F70 *state = (State_00209F70 *)&D_00325F20;
    Texture_00209F70 *texture;
    u64 *packet = arg0;

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
        packet[4] = ((u64)arg1 << 32) |
            (((s64)state->format << 24) |
             (state->base | ((s64)(D_00293F1C[state->index].base >> 6) << 16)));
        packet += 5;
    } else {
        packet[4] = ((u64)arg1 << 32) |
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

s32 func_0020A0B0(s32 arg0, s32 arg1) {
    extern u8 D_00325E40[];
    extern __int128 D_00325E60;
    extern Packet_0020A0B0 D_00325E70;
    extern Packet_0020A0B0 D_00325FC0;
    State_0020A0B0 *state = (State_0020A0B0 *)&D_00325F20;

    func_001875F8((s32 *)D_00325E40, arg0);
    func_00187660(D_00325E40, 0);
    func_001877F8((s32 **)D_00325E40, 0x11000000);
    func_00187778(D_00325E40, 2, 3);
    func_00187858(D_00325E40, 0);
    ((u64 *)&D_00325E60)[0] = ((u64)0x10000000 << 32) | 0x8000;
    ((u64 *)&D_00325E60)[1] = 0xE;
    func_001876B8(D_00325E40, D_00325E60);
    if (D_00325F40.enabled && state->flags.apply) {
        D_00325E70.f.value = state->base + state->offset;
        D_00325E70.f.mode = state->mode;
    } else {
        D_00325E70 = D_00325FC0;
    }
    D_00325E70.f.clear = !arg1;
    func_00187828(D_00325E40, 0x4E, ((u64 *)&D_00325E70)[0]);
    func_001876D0(D_00325E40);
    func_001878B0(D_00325E40);
    return func_00187608(D_00325E40);
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

void func_0020A280(void *arg0) {
    extern Packet_0020A280 D_00325FC0;
    State_0020A280 *state = (State_0020A280 *)&D_00325F20;
    Packet_0020A280 *packet = arg0;

    if (D_00325F40.enabled && state->flags.apply) {
        packet->value = state->base + state->offset;
        packet->mode = state->mode;
    } else {
        packet->value = D_00325FC0.value;
        packet->mode = D_00325FC0.mode;
    }
}

void *func_0020A340(void *arg0, void *arg1) {
    *(s32 *)((u8 *)arg0 + 0) = 0x10000002;
    *(s32 *)((u8 *)arg0 + 4) = 0;
    *(s32 *)((u8 *)arg0 + 8) = 0;
    *(s32 *)((u8 *)arg0 + 0xC) = 0x51000002;
    *(s64 *)((u8 *)arg0 + 0x10) = ((s64)0x10000000 << 32) | 0x8001;
    *(s64 *)((u8 *)arg0 + 0x18) = 0xE;
    *(s64 *)((u8 *)arg0 + 0x20) = ((s64)((u8 *)arg1)[0] << 16) |
        ((s64)((u8 *)arg1)[2] | ((s64)((u8 *)arg1)[1] << 8));
    *(s64 *)((u8 *)arg0 + 0x28) = 0x3D;
    return (u8 *)arg0 + 0x30;
}

void func_0020A3B0(u32 arg0) {
    u8 *base = D_00325F50;
    u16 *p;

    func_00185578(0, 0);
    if (D_003261BC & 1) {
        p = (u16 *)(base + 0x60);
    } else {
        p = (u16 *)(base + 0x150);
    }
    func_00185890(D_00325E80, (*p & 0x1FF) << 5, 10, 10, 0, 0, 0x280, 0x1C0);
    func_0017BB60(0);
    func_001859D0(D_00325E80, (void *)(arg0 & 0x0FFFFFFF));
    func_00185578(0, 0);
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

s32 func_0020A470(s32 arg0, s32 arg1, s32 arg2) {
    extern Table_0020A470 D_00293F1C[];
    u8 *base = D_00325F50;
    Full_0020A470 *state = (Full_0020A470 *)&D_00325F20;
    s32 a = 0;
    s32 b = 0;

    if (D_00325F40.enabled != 0) {
        return 0;
    }
    state->id = arg0;
    state->value4 = D_00293F1C[arg0].value0;
    state->value8 = D_00293F1C[arg0].value4;
    state->mode = arg1;
    state->kind = arg2;
    switch (arg1) {
    case 0:
    case 1:
        a = 1;
        break;
    case 2:
    case 10:
        a = 0;
        break;
    }
    switch (arg2) {
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
    state->value1C = D_00293F1C[arg0].sizes[a];
    state->value10 = D_00293F1C[arg0].sizes[a] + D_00293F1C[arg0].sizes[b];
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

void *func_0020A610(void *arg0) {
    extern Texture_0020A610 D_00293F1C[];
    State_0020A610 *state = (State_0020A610 *)&D_00325F20;
    Packet_0020A610 *packet = arg0;

    if (!D_00325F40.enabled) {
        return arg0;
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
    return (u8 *) arg0 + 0x60;
}

#ifndef GAME_H
/* The game translation unit already declares this global with its local type. */
extern unsigned char D_00325F20[];
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

void *func_0020A760(void *arg0) {
    Context_0020A760 *context = (Context_0020A760 *)D_00325F50;
    Flags_0020A760 *flags = (Flags_0020A760 *)&D_00325F20;
    s64 *environment;
    Packet_0020A760 *packet = arg0;

    if (D_003261BC & 1) {
        environment = context->environment1;
    } else {
        environment = context->environment0;
    }
    if (!flags->enabled) {
        return arg0;
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

static inline void default_color_0020A870(void *color, void *value) {
    *(Color_0020A870 *)color = *(Color_0020A870 *)value;
}

static inline s32 draw_0020A870(void *state) {
    return ((State_0020A870 *)state)->flags.draw;
}

static inline s32 color_0020A870(u8 *color, s32 component) {
    if (color != NULL) {
        return color[component];
    }
    return 0;
}

void *func_0020A870(u8 *packet, u8 *color) {
    s32 func_00184FF8(void *, s32, s32, s32, s32, s32, u8, u8, u8, u8, s32);
    Color_0020A870 defaultColor;
    State_0020A870 *state = (State_0020A870 *)&D_00325F20;
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
    packet += func_00184FF8(packet, 2, 0, 0, 0xFFF, 0xFFF,
                           color_0020A870(color, 2), green, red, alpha, 0) * 0x10;
    ((u64 *)packet)[0] = 1;
    ((u64 *)packet)[1] = 0x4A;
    return packet + 0x10;
}

void func_0020A9E0(void) {
    D_00325F40.enabled = 0;
    D_00325F40.flag1 = 0;
}

s32 func_0020AA30(void *arg0, void *arg1) {
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
    State_0020AA30 *state = (State_0020AA30 *)&D_00325F20;
    s32 first;
    s32 second;
    s32 kind;
    Record_0020AA30 *record = arg0;
    Extra_0020AA30 *extra = arg1;

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

static inline s32 from_fixed_0020AD10(s32 value) {
    return value >> 6;
}

void func_0020AD10(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    extern Entry_0020AD10 D_00293F1C[];
    extern Entry_0020AD10 D_00293F20[];
    extern Scale_0020AD10 D_00293F24[];
    extern Entry_0020AD10 D_00293F28[];
    extern Entry_0020AD10 D_00293F2C[];
    extern Sizes_0020AD10 D_00293F30[];
    State_0020AD10 *state = arg0;

    state->mode = arg1;
    state->width = D_00293F1C[arg1].value;
    state->height = D_00293F20[arg1].value;
    state->scale = D_00293F24[arg1].value;
    state->field248 = D_00293F28[arg1].value;
    state->field24C = D_00293F2C[arg1].value;
    state->firstMode = arg2;
    switch (arg2) {
    case 0:
    case 1:
        state->firstIndex = 1;
        break;
    case 2:
    case 10:
        state->firstIndex = 0;
        break;
    }
    state->secondMode = arg3;
    switch (arg3) {
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
    state->offset = D_00293F30[arg1].values[state->secondIndex] + D_00293F30[arg1].values[state->firstIndex] * 2;
    state->offset = from_fixed_0020AD10((state->offset << 13) >> 2);
    func_001851E8(arg0, (s16)arg2, (s16)D_00293F1C[arg1].value, (s16)D_00293F20[arg1].value, 3, (s16)arg3, 1);
    if (state->firstX.x == state->secondX.x) {
        state->firstX.x = 0;
        state->secondX.x = D_00293F30[arg1].values[state->firstIndex];
        state->thirdX.x = state->secondX.x;
        state->fifthX.x = state->firstX.x;
        state->fourthX.x = D_00293F30[arg1].values[state->firstIndex] * 2;
        state->sixthX.x = state->fourthX.x;
        state->firstDisplay.height = state->secondDisplay.height = D_00293F20[arg1].value - 1;
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

s32 func_0020B000(s32 arg0) {
    extern void func_00187828();

    D_00326180 = 0x63721405 | ((u64)0x72630514 << 32);
    func_001875F8(D_00325F00, arg0);
    func_00187660(D_00325F00, 0);
    func_001877F8(D_00325F00, 0x01000404);
    func_00187810(D_00325F00, 0x20000000);
    func_00187810(D_00325F00, 0x05000000);
    func_00187778(D_00325F00, 2, 3);
    func_00187858(D_00325F00, 0);
    *(u64 *)&D_00325EF0 = 0x8000 | ((u64)0x10000000 << 32);
    *((u64 *)&D_00325EF0 + 1) = 0xE;
    func_001876B8(D_00325F00, D_00325EF0);
    func_00187828(D_00325F00, 0x46, 1);
    func_00187828(D_00325F00, 0x40, ((u64)(D_0032618C - 1) << 16) | ((u64)(D_00326190 - 1) << 48));
    func_00187828(D_00325F00, 0x1A, 1);
    func_00187828(D_00325F00, 0x3B, (u64)0x80 << 32);
    func_00187828(D_00325F00, 0x3D, 0xC0C0C0);
    func_00187828(D_00325F00, 0x45, 1);
    func_00187828(D_00325F00, 0x44, D_00326180);
    func_001876D0(D_00325F00);
    func_001878B0(D_00325F00);
    return func_00187608(D_00325F00);
}

void func_0020B1E0(s32 arg0) {
    extern void func_00187828();
    u8 buffer[0x40];
    u8 *packet;
    u64 *tag;
    s32 shift;

    packet = (u8 *) (((u32) buffer + 0xF) & ~0xF);
    tag = (u64 *) (packet + 0x20);
    shift = (func_0019A5C8() % 16) * 4;
    D_00326180 = (D_00326180 >> shift) | (D_00326180 << (0x40 - shift));
    func_001875F8(packet, arg0);
    func_00187660(packet, 0);
    func_00187778(packet, 2, 3);
    func_00187858(packet, 0);
    tag[0] = 0x1000000000008000ULL;
    tag[1] = 0xE;
    func_001876B8(packet, *(__int128 *) tag);
    func_00187828(packet, 0x45, 1);
    func_00187828(packet, 0x44, D_00326180);
    func_001876D0(packet);
    func_001878B0(packet);
    func_00187608(packet);
}

u8 *func_0020B300(u8 *arg0, u8 *arg1, s32 arg2) {
    if (arg2 > 0) {
        do {
            arg2 -= 1;
            *arg0 = *arg1;
            arg1 += 1;
            arg0 += 1;
        } while (arg2 > 0);
    }
    return arg0;
}

void *func_0020B340(void *dest, void *source, s32 count) {
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

void *func_0020B380(void *dest, void *source, s32 count) {
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

s8 *func_0020B3C0(s8 *arg0, s8 arg1, s32 arg2) {
    if (arg2 > 0) {
        do {
            *arg0 = arg1;
            arg2 -= 1;
            arg0 += 1;
        } while (arg2 > 0);
    }
    return arg0;
}

void *func_0020B400(void *dst, s32 val, s32 count) {
    s32 *p = dst;

    while (count > 0) {
        *p++ = val;
        count--;
    }
    return p;
}

s64 *func_0020B440(s64 *arg0, s64 arg1, s32 arg2) {
    while (arg2 > 0) {
        *arg0 = arg1;
        arg2 -= 1;
        arg0++;
    }
    return arg0;
}

f32 func_0020B480(s32 arg0) {
    f32 sign;
    f32 *samples;
    f32 sample0;
    f32 sample1;
    s32 fraction;

    arg0 = (s16)(arg0 + 0x4000);
    sign = 1.0f;
    if (arg0 < 0) {
        sign = -1.0f;
        arg0 = -arg0;
    }
    if (arg0 > 0x4000) {
        arg0 = 0x8000 - arg0;
    }
    if ((arg0 & 0x3FFF) == 0) {
        return arg0 == 0x4000 ? sign : 0.0f;
    }
    fraction = arg0 & 0xF;
    samples = &D_00294050[arg0 >> 4];
    sample0 = samples[0];
    sample1 = samples[1];
    return sign * (sample0 * (16 - fraction) + sample1 * fraction) / 16.0f;
}

f32 func_0020B550(s32 arg0) {
    f32 sign;
    f32 *samples;
    f32 sample0;
    f32 sample1;
    s32 fraction;

    arg0 = (s16)arg0;
    sign = 1.0f;
    if (arg0 < 0) {
        sign = -1.0f;
        arg0 = -arg0;
    }
    if (arg0 > 0x4000) {
        arg0 = 0x8000 - arg0;
    }
    if ((arg0 & 0x3FFF) == 0) {
        return arg0 == 0x4000 ? sign : 0.0f;
    }
    fraction = arg0 & 0xF;
    samples = &D_00294050[arg0 >> 4];
    sample0 = samples[0];
    sample1 = samples[1];
    return sign * (sample0 * (16 - fraction) + sample1 * fraction) / 16.0f;
}

f32 func_0020B620(f32 angle) {
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
        entry = &D_00294050[phase >> 4];
        lower = entry[0];
        upper = entry[1];
        sign = (sign * (lower * (16 - fraction) + upper * weight)) / 16.0f;
    }
    return sign;
}

f32 func_0020B730(f32 angle) {
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
        entry = &D_00294050[phase >> 4];
        lower = entry[0];
        upper = entry[1];
        sign = (sign * (lower * (16 - fraction) + upper * weight)) / 16.0f;
    }
    return sign;
}

void func_0020B840(u8 *arg0, s32 arg1, s32 arg2, s32 (*arg3)(u8 *, u8 *)) {
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

    sentinel = &D_003261F0;
    var_fp = arg1 >> 1;
    temp_s5 = arg0 - arg2;
    var_s2 = arg1;
    if (var_fp > 0) {
        spA0 = var_fp * arg2;
        do {
            var_s3 = var_fp;
            func_0020B300(sentinel, temp_s5 + spA0, arg2);
            while ((var_s4 = var_s3 * 2) <= var_s2) {
                if (var_s4 < var_s2 &&
                    arg3(temp_s5 + (var_s4 * arg2), temp_s5 + ((var_s4 + 1) * arg2)) < 0) {
                    var_s4 += 1;
                }
                temp_s6 = temp_s5 + (var_s4 * arg2);
                if (arg3(sentinel, temp_s6) >= 0) {
                    break;
                }
                var_v0 = var_s3 * arg2;
                func_0020B300(temp_s5 + var_v0, temp_s6, arg2);
                var_s3 = var_s4;
            }
            func_0020B300(temp_s5 + (var_s3 * arg2), sentinel, arg2);
            var_fp -= 1;
            spA0 -= arg2;
        } while (var_fp > 0);
    }
    if (var_s2 > 1) {
        var_fp_2 = var_s2 * arg2;
        spB0 = temp_s5 + arg2;
        var_s3_2 = temp_s5 + var_fp_2;
        do {
            func_0020B300(sentinel, var_s3_2, arg2);
            func_0020B300(var_s3_2, spB0, arg2);
            var_s2 -= 1;
            var_s4_2 = 1;
            var_fp_2 -= arg2;
            while ((var_s6 = var_s4_2 * 2) <= var_s2) {
                if (var_s6 < var_s2 &&
                    arg3(temp_s5 + (var_s6 * arg2), temp_s5 + ((var_s6 + 1) * arg2)) < 0) {
                    var_s6 += 1;
                }
                temp_s3 = temp_s5 + (var_s6 * arg2);
                if (arg3(sentinel, temp_s3) >= 0) {
                    break;
                }
                func_0020B300(temp_s5 + (var_s4_2 * arg2), temp_s3, arg2);
                var_s4_2 = var_s6;
            }
            func_0020B300(temp_s5 + (var_s4_2 * arg2), sentinel, arg2);
            var_s3_2 = temp_s5 + var_fp_2;
        } while (var_s2 > 1);
    }
}

s32 func_0020BA70(void) {
    D_0032A220 = 0;
    return 1;
}

s32 func_0020BA80(void) {
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020BA90);

asm void func_0020BAD0(void *p) {
    .set noreorder
    sqc2 vf28, 0x0(a0)
    sqc2 vf29, 0x10(a0)
    sqc2 vf30, 0x20(a0)
    jr ra
    sqc2 vf31, 0x30(a0)
}

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020BAF0);

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020BB50);

s32 func_0020BBA0(void) {
    D_0032A220 = 0;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020BBB0);

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020BC00);

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020BCF0);

typedef struct Matrix_0020BDE0 {
    f32 m[4][4];
} Matrix_0020BDE0;

void func_0020BDE0(void *dst, void *src) {
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

void func_0020C630(void *dst, void *src) {
    f32 *matrix = dst;
    s32 *angles = src;
    f32 cx;
    f32 sx;
    f32 cy;
    f32 sy;
    f32 cz;
    f32 sz;

    cx = func_0020B480(angles[0]);
    sx = func_0020B550(angles[0]);
    cy = func_0020B480(angles[1]);
    sy = func_0020B550(angles[1]);
    cz = func_0020B480(angles[2]);
    sz = func_0020B550(angles[2]);
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


void func_0020C750(void *arg0, void *arg1, s32 arg2) {
    f32 *m = arg0;
    Vec4_0020C750 v;
    f32 c;
    f32 s;
    f32 t;

    v = *(Vec4_0020C750 *)arg1;
    c = func_0020B480(arg2);
    t = 1.0f - c;
    s = func_0020B550(arg2);
    func_0020D070(&v.x);
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

void func_0020BBB0(void *arg0);

void func_0020C8F0(void *arg0, f32 *arg1) {
    Matrix_0020C8F0 *matrix = arg0;

    func_0020BBB0(arg0);
    matrix->translation[0] = arg1[0];
    matrix->translation[1] = arg1[1];
    matrix->translation[2] = arg1[2];
}

typedef struct {
    f32 m[3][4];
    f32 t[3];
} Matrix_0020C940;

void func_0020BBB0(void *arg0);

void func_0020C940(void *arg0, void *p1, void *p2, void *p3) {
    Matrix_0020C940 *mtx = arg0;
    f32 *arg1 = p1;
    s32 *arg2 = p2;
    f32 *arg3 = p3;
    f32 cx;
    f32 sx;
    f32 cy;
    f32 sy;
    f32 cz;
    f32 sz;

    func_0020BBB0(arg0);
    if (arg3 != NULL) {
        mtx->t[0] = arg3[0];
        mtx->t[1] = arg3[1];
        mtx->t[2] = arg3[2];
    }
    if (arg2 != NULL) {
        cx = func_0020B480(arg2[0]);
        sx = func_0020B550(arg2[0]);
        cy = func_0020B480(arg2[1]);
        sy = func_0020B550(arg2[1]);
        cz = func_0020B480(arg2[2]);
        sz = func_0020B550(arg2[2]);
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

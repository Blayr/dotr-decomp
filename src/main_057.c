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

INCLUDE_ASM("asm/nonmatchings/main_057", func_00209F60);

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

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020A0B0);

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020A280);

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

void func_0020A3B0(s64 arg0) {
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
    func_001859D0(D_00325E80, arg0 & 0x0FFFFFFF);
    func_00185578(0, 0);
}

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020A470);

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

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020A870);

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020A9E0);

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

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020AD10);

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

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020B340);

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020B380);

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

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020B550);

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020B620);

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

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020B840);

s32 func_0020BA70(void) {
    D_0032A220 = 0;
    return 1;
}

s32 func_0020BA80(void) {
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020BA90);

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020BAD0);

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020BAF0);

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020BB50);

s32 func_0020BBA0(void) {
    D_0032A220 = 0;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020BBB0);

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020BC00);

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020BCF0);

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020BDE0);

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020C630);

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020C750);

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

INCLUDE_ASM("asm/nonmatchings/main_057", func_0020C940);

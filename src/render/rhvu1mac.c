/* The VU1 drawing program's settings: lights, fog, draw method (RhVu1Mac_*). */

#include "common.h"

/* Picks the VU1 microprogram for draw `flags` (lit, fogged, clipped...) in the packet. */
void *RhVu1Mac_ChangeDrawMethod(void *packetIn, s32 flags) {
    s32 *packet = packetIn;

    packet[0] = 0x10000001;
    packet[1] = 0;
    packet[2] = 0x10000000;
    packet[3] = 0x68014000;
    if (!(flags & 2) || !D_00325E2C) {
        if (flags & 0x40) {
            if (flags & 0x20) {
                packet[4] = 0x274;
            } else if (flags & 0x10) {
                packet[4] = 0xE8;
            } else {
                packet[4] = 0xE8;
            }
        } else {
            if (flags & 0x20) {
                packet[4] = 0x1A4;
            } else if (flags & 0x10) {
                packet[4] = 0x30;
            } else {
                packet[4] = 0x30;
            }
        }
    } else {
        if (flags & 0x20) {
            packet[4] = 0x6D4;
        } else {
            packet[4] = 0x580;
        }
    }
    packet[5] = 0;
    packet[6] = 0;
    packet[7] = 0x10000000;
    vu1DrawMethod = flags;
    return packet + 8;
}

typedef struct {
    s32 flags;
    void *data;
    s32 field8;
    s32 fieldC;
} Header_00208E40;

/* Marks the VU1 microprogram to be picked again at the next draw. */
void *RhVu1Mac_ReserveChangeDrawMethod(void *packet) {
    Header_00208E40 *header = packet;

    header->flags = 0x20000000;
    header->data = (u8 *)packet + 0x20;
    header->field8 = 0;
    header->fieldC = 0;
    return (u8 *)packet + 0x20;
}

/* Sends the view-to-screen matrix to VU1. */
void *RhVu1Mac_SetViewScreenMatrix(void *packet, void *matrix) {
    ((u32 *)packet)[0] = 0x10000004;
    ((u32 *)packet)[1] = 0;
    ((u32 *)packet)[2] = 0;
    ((u32 *)packet)[3] = 0x6C040044;
    RhMem_CopyMemory16((u8 *)packet + 0x10, matrix, 4);
    return (u8 *)packet + 0x50;
}

/* Sends the screen-to-world matrix to VU1. */
void *RhVu1Mac_SetScreenWorldMatrix(void *packet, void *matrix) {
    ((s32 *)packet)[0] = 0x10000004;
    ((s32 *)packet)[1] = 0;
    ((s32 *)packet)[2] = 0;
    ((s32 *)packet)[3] = 0x6C040056;
    RhMem_CopyMemory16((u8 *)packet + 0x10, matrix, 4);
    return (u8 *)packet + 0x50;
}

/* Sends the three directional lights (`colors`, `dirs`) to VU1. */
s32 RhVu1Mac_SetStraightLightToVu1_Ex(s32 packet, void *colors, void *dirs, s32 count) {
    u8 buffer[0x50];
    s32 matrix;

    matrix = ((u32)buffer + 0xF) & ~0xF;
    if (count >= 0 && count < 3 && (colors == NULL || dirs == NULL)) {
        return packet;
    }
    switch (count) {
    case 0:
        vu1LightColors = ((f32 *)colors)[1];
        D_00325D94 = ((f32 *)colors)[2];
        D_00325D98 = ((f32 *)colors)[3];
        vu1LightDirs = ((f32 *)dirs)[0];
        D_00325D60 = ((f32 *)dirs)[1];
        D_00325D70 = ((f32 *)dirs)[2];
        break;
    case 1:
        D_00325DA0 = ((f32 *)colors)[1];
        D_00325DA4 = ((f32 *)colors)[2];
        D_00325DA8 = ((f32 *)colors)[3];
        D_00325D54 = ((f32 *)dirs)[0];
        D_00325D64 = ((f32 *)dirs)[1];
        D_00325D74 = ((f32 *)dirs)[2];
        break;
    case 2:
        D_00325DB0 = ((f32 *)colors)[1];
        D_00325DB4 = ((f32 *)colors)[2];
        D_00325DB8 = ((f32 *)colors)[3];
        D_00325D58 = ((f32 *)dirs)[0];
        D_00325D68 = ((f32 *)dirs)[1];
        D_00325D78 = ((f32 *)dirs)[2];
        break;
    }
    if (packet != 0) {
        u32 *tag = (u32 *)packet;

        RhMem_CopyMemory16((void *)matrix, &vu1LightColors, 4);
        RhGeom_MulMatrix(matrix, &vu1LightDirs);
        tag[0] = 0x10000004;
        tag[1] = 0;
        tag[2] = 0;
        tag[3] = 0x6C04003F;
        RhMem_CopyMemory16((void *)(packet + 0x10), (void *)matrix, 4);
        packet = (s32)(tag + 4) + 0x40;
    } else if (count < 0) {
        func_00198948(&vu1LightDirs, 0, 0x40);
        func_00198948(&vu1LightColors, 0, 0x40);
    }
    return packet;
}

typedef struct Packet_00209110 {
    u32 header[4];
    f32 values[8];
} Packet_00209110;

/* Sends the point light (position, colour, range) to VU1. */
s32 RhVu1Mac_SetPointLightToVu1(s32 packetIn, void *pos, void *color, f32 fparg0, f32 fparg1, f32 fparg2) {
    extern void RhMem_CopyMemory4(f32 *, void *, s32);
    extern f32 D_00325E00[4];
    extern f32 D_00325E10[4];
    extern f32 D_00325E20;
    extern f32 D_00325E24;
    extern f32 D_00325E28;
    Packet_00209110 *packet;
    f32 range;

    packet = (Packet_00209110 *)packetIn;
    if ((pos == NULL) || (color == NULL)) {
        packet->header[0] = 0x10000002;
        packet->header[1] = 0;
        packet->header[2] = 0x11000000;
        packet->header[3] = 0x6C020054;
        RhMem_FillMemory8((s64 *)packet->values, 0, 4);
        packet++;
        D_00325E2C = 0;
    } else {
        packet->header[0] = 0x10000002;
        packet->header[1] = 0;
        range = fparg1 - fparg0;
        packet->header[2] = 0x11000000;
        packet->header[3] = 0x6C020054;
        packet->values[0] = ((f32 *)pos)[1];
        packet->values[1] = ((f32 *)pos)[2];
        packet->values[2] = ((f32 *)pos)[3];
        packet->values[3] = (fparg2 * fparg1) / range;
        packet->values[4] = ((f32 *)color)[0];
        packet->values[5] = ((f32 *)color)[1];
        packet->values[6] = ((f32 *)color)[2];
        packet->values[7] = fparg2 / range;
        packet++;
        RhMem_CopyMemory4(D_00325E00, pos, 4);
        RhMem_CopyMemory4(D_00325E10, color, 4);
        D_00325E20 = fparg0;
        D_00325E24 = fparg1;
        D_00325E28 = fparg2;
        D_00325E2C = 1;
    }
    return (s32)packet;
}

typedef struct Vec4_00209270 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4_00209270;

extern Vec4_00209270 D_00325E00;
extern Vec4_00209270 D_00325E10;
extern f32 D_00325E20;
extern f32 D_00325E24;
extern f32 D_00325E28;
extern s32 D_00325E2C;

/* The point light last sent to VU1: position, colour and its three range values. */
s32 RhVu1Mac_GetPointLight(void *pos, void *color, f32 *near, f32 *far, f32 *power) {
    if (pos != NULL) {
        *(Vec4_00209270 *)pos = D_00325E00;
    }
    if (color != NULL) {
        *(Vec4_00209270 *)color = D_00325E10;
    }
    if (near != NULL) {
        *near = D_00325E20;
    }
    if (far != NULL) {
        *far = D_00325E24;
    }
    if (power != NULL) {
        *power = D_00325E28;
    }
    return D_00325E2C;
}

typedef struct Packet_00209320 {
    s32 tag0;
    s32 zero0;
    s32 zero1;
    s32 command0;
    f32 right;
    f32 left;
    f32 near_value;
    f32 far_value;
    s32 tag1;
    s32 zero2;
    s32 zero3;
    s32 command1;
    s32 enabled;
    s32 zero4;
    s32 zero5;
    s32 zero6;
} Packet_00209320;

/* Sends the clip parameters to VU1. */
void *RhVu1Mac_SetClipParameter(void *packetIn, s32 mode, f32 fparg0, f32 fparg1, f32 fparg2) {
    f32 scale;
    s32 enabled;
    Packet_00209320 *packet = packetIn;

    packet->tag0 = 0x10000001;
    packet->zero0 = 0;
    packet->zero1 = 0;
    packet->command0 = 0x6C014052;
    scale = 2.0f * fparg0;
    packet->right = 645.0f / scale;
    packet->left = -645.0f / scale;
    packet->near_value = 0.01f + fparg1;
    packet->far_value = fparg2 - 0.01f;
    packet->tag1 = 0x10000001;
    packet->zero2 = 0;
    packet->zero3 = 0;
    packet->command1 = 0x6C01405A;
    if (mode == 1) {
        enabled = 1;
    } else {
        enabled = 0;
    }
    packet->enabled = enabled;
    packet->zero4 = 0;
    packet->zero5 = 0;
    packet->zero6 = 0;
    return (u8 *)packetIn + 0x40;
}

typedef struct Packet_002093E0 {
    s32 tag[4];
    f32 values[4];
} Packet_002093E0;

extern f32 D_00325DE0;
extern f32 D_00325DE4;
extern f32 D_00325DE8;
extern f32 D_00325DEC;
extern f32 D_00325DF0;
extern f32 D_00325DF4;
extern f32 D_00325DF8;
extern f32 D_00325DFC;

/* Sends the fog ranges to VU1. */
void *RhVu1Mac_SetFogParameterEx(void *packetIn, f32 fparg0, f32 fparg1, f32 fparg2, f32 fparg3) {
    Packet_002093E0 *packet = packetIn;
    f32 range0;
    f32 range1;

    packet->tag[0] = 0x10000001;
    packet->tag[1] = 0;
    packet->tag[2] = 0x10000000;
    range1 = 255.0f / (fparg3 - fparg2);
    packet->tag[3] = 0x6C014053;
    packet->values[0] = range1;
    range0 = 255.0f / (fparg1 - fparg0);
    packet->values[1] = fparg2 * range1;
    packet->values[2] = range0;
    packet->values[3] = fparg1 * range0;
    D_00325DE0 = packet->values[2];
    D_00325DE4 = packet->values[3];
    D_00325DE8 = packet->values[0];
    D_00325DEC = packet->values[1];
    D_00325DF0 = fparg0;
    D_00325DF4 = fparg1;
    D_00325DF8 = fparg2;
    D_00325DFC = fparg3;
    return packet + 1;
}

typedef struct {
    u32 header[4];
    f32 value_10;
    f32 value_14;
    f32 value_18;
    f32 value_1C;
} Packet_00209490;

/* Turns depth fog (`depthOn`) and height fog (`heightOn`) on or off in VU1. */
void *RhVu1Mac_SetFogOnOff(void *packetIn, s32 depthOn, s32 heightOn) {
    Packet_00209490 *packet = packetIn;

    packet->header[0] = 0x10000001;
    packet->header[1] = 0;
    packet->header[2] = 0x10000000;
    packet->header[3] = 0x6C014053;
    if (depthOn != 0) {
        packet->value_18 = D_00325DE0;
        packet->value_1C = D_00325DE4;
    } else {
        packet->value_18 = 0.0f;
        packet->value_1C = 255.0f;
    }
    if (heightOn != 0) {
        packet->value_10 = D_00325DE8;
        packet->value_14 = D_00325DEC;
    } else {
        packet->value_10 = 0.0f;
        packet->value_14 = 0.0f;
    }
    return (u8 *)packetIn + 0x20;
}

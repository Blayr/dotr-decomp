#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_039", func_001B62F0);

void func_001B65E0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4,
                   s32 arg5, s32 arg6) {
    func_001B65F0(arg0, arg1, arg2, arg3, arg4, arg5, arg6, 0);
}

INCLUDE_ASM("asm/nonmatchings/main_039", func_001B65F0);

void func_001B6C90(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    func_001B6CA0(arg0, arg1, arg2, arg3, arg4, arg5, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/main_039", func_001B6CA0);

void func_001B6EA0(s32 arg0, s32 arg1, s32 arg2, s32 arg3,
                   s32 flags, s32 width, s32 number) {
    s8 text[16];
    s32 padded;
    s32 power;
    s32 i;

    power = 1;
    padded = 0;
    if (flags & 0x20) {
        padded = 1;
    }
    for (i = 0; i < width; i++) {
        text[i] = ' ';
    }
    for (i = 0; i < width;) {
        text[width - i - 1] = (number / power) % 10 + '0';
        power *= 10;
        i++;
        if (!padded && number < power) {
            break;
        }
    }
    func_001B6F70(arg0, arg1, arg2, arg3, flags, width, text, 0);
}

INCLUDE_ASM("asm/nonmatchings/main_039", func_001B6F70);

s32 func_001B7660(s8 character) {
    s32 result = -1;

    if (character >= 'A' && character <= 'Z') {
        result = character - 'A';
    } else if (character >= 'a' && character <= 'z') {
        result = character - 'a';
    } else if (character >= '0' && character <= '9') {
        result = character - '0' + 26;
    } else if (character == '?') {
        result = 36;
    }
    return result;
}

INCLUDE_ASM("asm/nonmatchings/main_039", func_001B76E0);

INCLUDE_ASM("asm/nonmatchings/main_039", func_001B7820);

INCLUDE_ASM("asm/nonmatchings/main_039", func_001B7D60);

INCLUDE_ASM("asm/nonmatchings/main_039", func_001B7F90);

void func_001B81E0(void) {
    func_00209D30(func_001B8210(func_00209D20()));
}

s32 func_001B8210(s32 arg0) {
    u8 *state = D_00317490;

    if (D_003181CA == 0) {
        return arg0;
    }
    func_001B8260(arg0, 0, 0, 0x280, 0x1C0, state[0xD3A]);
}

typedef struct {
    u16 count;
    u16 flags;
    u32 padding;
    u64 registers;
} Tag_001B8260;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Color_001B8260;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Vertex_001B8260;

typedef struct {
    u64 tag[2];
    Color_001B8260 color;
    Vertex_001B8260 vertices[2];
} Packet_001B8260;

void func_001B8260(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 x;
    s32 y;
    Packet_001B8260 packet;

    ((Tag_001B8260 *) packet.tag)->flags = 6;
    ((Tag_001B8260 *) packet.tag)->count = 3;
    ((Tag_001B8260 *) packet.tag)->registers = 0x441;
    x = arg1 + 0x6C0;
    y = arg2 + 0x720;
    ((Tag_001B8260 *) packet.tag)->padding = 0;
    func_002086D0(packet.tag, func_00208D00(2));
    packet.color.r = 0xFF;
    packet.color.g = 0xFF;
    packet.color.b = 0xFF;
    packet.color.a = arg5;
    packet.color.q = 1.0f;
    packet.vertices[0].x = x << 4;
    packet.vertices[0].y = y << 4;
    packet.vertices[0].z = 0xFFFFFD;
    packet.vertices[0].fog = 0;
    packet.vertices[1].x = (x + arg3) << 4;
    packet.vertices[1].y = (y + arg4) << 4;
    packet.vertices[1].z = 0xFFFFFD;
    packet.vertices[1].fog = 0;
    arg0 = func_0020A0B0(arg0, 0);
    arg0 = func_00207650(arg0, (s32) &packet, 0, 0);
    func_0020A0B0(arg0, 1);
}

void func_001B83C0(void) {
    func_00209D30(func_001B83F0(func_00209D20()));
}

INCLUDE_ASM("asm/nonmatchings/main_039", func_001B83F0);

INCLUDE_ASM("asm/nonmatchings/main_039", func_001B8520);

INCLUDE_ASM("asm/nonmatchings/main_039", func_001B8720);

void func_001B8830(void) {

}

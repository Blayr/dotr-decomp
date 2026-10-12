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

typedef struct Result_001B6CA0 {
    s32 unk0;
    s32 unk4;
} Result_001B6CA0;

s32 func_001B6CA0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    extern s32 func_001FEAB0();
    extern s32 func_001FE7D0();
    Result_001B6CA0 *spA8;
    s32 stride;
    s32 digit;

    spA8 = (Result_001B6CA0 *) func_001FEAB0(0);
    stride = 0x14 - (arg5 ? 4 : 0);
    {
        s32 power = 1;

        if (arg4 == 0x7FFFFFFF) {
            digit = 0;
            spA8->unk4 = 0x108;
            if (0 < arg3) {
                do {
                    arg0 = func_001FE7D0(arg0, 0, arg1 + (stride * (arg3 - digit - 1)), arg2, arg7, func_001FDFE0);
                    digit += 1;
                } while (digit < arg3);
            }
            return arg0;
        }
        digit = 0;
        if (0 < arg3) {
            do {
                spA8->unk4 = (((arg4 / power) % 10) * 0x16);
                arg0 = func_001FE7D0(arg0, 0, arg1 + (stride * (arg3 - digit - 1)), arg2, arg7, func_001FDFE0);
                power *= 10;
                digit += 1;
            } while ((arg6 != 0 || arg4 >= power) && digit < arg3);
        }
        if (digit < arg3) {
            if (arg4 < 0) {
                spA8->unk4 = 0xF2;
                arg0 = func_001FE7D0(arg0, 0, arg1 + (stride * (arg3 - digit - 1)), arg2, arg7, func_001FDFE0);
            }
        }
    }
    return arg0;
}

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

static s32 func_001B7660(s8 character) {
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

void func_001B8520(s32 arg0) {
    extern s32 func_00216AC0();
    extern s32 func_00215A60();
    extern s32 func_00215C40();
    u8 *state;
    s32 temp_s1;
    s16 *var_s2;
    s16 *var_s3;
    u8 *var_s4;
    s32 var_s5;
    s32 var_s2_2;
    s32 var_v1;
    u8 *var_v0;

    state = D_00317490;
    temp_s1 = func_002158B0(arg0);
    var_s2 = (s16 *)0x01ED0000;
    var_s3 = (s16 *)0x01ED06AC;
    var_s4 = (u8 *)0x01ED06FE;
    var_v1 = func_00214D00(0, 0);
    D_003180E8 = 0xFFFFF8;
    if (var_v1 != 0) {
        var_v0 = D_002CD1F4;
    } else {
        var_v0 = D_002CCB48;
    }
    *(u8 **)(state + 0x6D4) = var_v0;
    *(s32 *)(state + 0x6D8) = 0x01ED0000;
    *(s32 *)(state + 0x6DC) = 0x01ED06AC;
    *(s32 *)(state + 0x6D0) = 0x01ED06FE;
    *(u16 *)(state + 0xC8C) = 0;
    var_s5 = 0;
    do {
        if (func_00216AC0(arg0, var_s5, -1) > 0) {
            *var_s2 = var_s5;
            *(u16 *)(state + 0xC8C) = (u16)(*(u16 *)(state + 0xC8C) + 1);
        } else {
            *var_s2 = 0x3E7;
        }
        var_s5 += 1;
        var_s2++;
    } while (var_s5 < 0x356);
    *(u16 *)(state + 0xC90) = 0;
    *(s16 *)0x01ED06AC = func_002159D0(arg0, temp_s1);
    var_s3++;
    var_s2_2 = 0;
    *(u16 *)(state + 0xC90) = (u16)(*(u16 *)(state + 0xC90) + 1);
    do {
        *var_s3 = func_00215A60(arg0, temp_s1, var_s2_2);
        var_s2_2 += 1;
        var_s3++;
        *(u16 *)(state + 0xC90) = (u16)(*(u16 *)(state + 0xC90) + 1);
    } while (var_s2_2 < 0x28);
    var_v1 = 0;
    do {
        var_v1 += 1;
        *(s8 *)(var_s4 + 2) = 0;
        var_s4 += 4;
    } while (var_v1 < 8);
    *(u16 *)(state + 0xC92) = 0;
    *(u16 *)(state + 0xC94) = 0;
    *(s8 *)(state + 0xCB6) = 0;
    *(s8 *)(state + 0xCB7) = 4;
    *(s8 *)(state + 0xCB8) = 0xA;
    *(s8 *)(state + 0xCB9) = 0;
    *(s8 *)(state + 0xCBA) = 4;
    *(s8 *)(state + 0xCBB) = 0xA;
    *(s8 *)(state + 0xD5D) = 3;
    *(s8 *)(state + 0xD5E) = 0;
    *(s8 *)(state + 0xD5F) = 0;
    *(u16 *)(state + 0xC8A) = 0;
    *(u16 *)(state + 0xC8E) = 0;
    *(u16 *)(state + 0xC96) = 0;
    *(u16 *)(state + 0xC98) = 0;
    *(s8 *)(state + 0xD60) = 0;
    *(s8 *)(state + 0xD61) = 0;
    *(s8 *)(state + 0xD62) = 0;
    *(s8 *)(state + 0xCBC) = 0;
    *(s8 *)(state + 0xCBD) = 0;
    *(s8 *)(state + 0xD5C) = (s8)arg0;
    func_001BA5F0();
    func_001BA610();
    func_00215C40(arg0, temp_s1);
    *(s8 *)(state + 0xD32) = 0;
}

INCLUDE_ASM("asm/nonmatchings/main_039", func_001B8720);

void func_001B8830(void) {

}

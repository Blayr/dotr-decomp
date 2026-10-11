#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_056", func_00206430);

INCLUDE_ASM("asm/nonmatchings/main_056", func_00206530);

INCLUDE_ASM("asm/nonmatchings/main_056", func_00206830);

void func_00206D00(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_00206D30(6, D_00325CC0, arg0, arg1, arg2, arg3, arg4);
}

INCLUDE_ASM("asm/nonmatchings/main_056", func_00206D30);

INCLUDE_ASM("asm/nonmatchings/main_056", func_002070F0);

INCLUDE_ASM("asm/nonmatchings/main_056", func_00207230);

void func_00207360(void) {
    func_0020BAF0(0);
    func_002073D0(D_00325D38, 0x01E08000, 0xC);
}

void func_002073A0(void) {
    func_00207510(D_00325D38);
    func_0020BB50();
}

INCLUDE_ASM("asm/nonmatchings/main_056", func_002073D0);

INCLUDE_ASM("asm/nonmatchings/main_056", func_00207500);

INCLUDE_ASM("asm/nonmatchings/main_056", func_00207510);

void func_002075F0(s32 arg0, s32 arg1, s32 arg2) {
    func_00209D30(func_00207650(func_00209D20(), arg0, arg1, arg2));
}

INCLUDE_ASM("asm/nonmatchings/main_056", func_00207650);

INCLUDE_ASM("asm/nonmatchings/main_056", func_00207AA0);

s32 func_00207F60(void) {
    s32 temp_v0;

    temp_v0 = func_00209D20();
    func_00209D30(func_00207FA0(temp_v0));
    return temp_v0;
}

s32 func_00207FA0(s32 arg0) {
    ((s64 *)arg0)[3] = 0;
    ((s64 *)arg0)[2] = 0;
    ((s64 *)arg0)[1] = 0;
    ((s64 *)arg0)[0] = 0;
    ((s8 *)arg0)[3] = 0x50;
    ((s8 *)arg0)[0x13] = 0x20;
    return arg0 + 0x20;
}

void func_00207FD0(s32 arg0, s32 arg1, s32 arg2) {
    func_00209D30(func_00208030(func_00209D20(), arg0, arg1, arg2));
}

s32 func_00208030(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 var_t0;
    u32 temp_v0;

    temp_v0 = (1 << *(s32 *)(arg2 + 0xC)) - 2;
    if (temp_v0 < (u32) arg3) {
        arg3 = temp_v0;
    }
    var_t0 = arg3 * 8;
    *(s32 *)(arg1 + 4) = *(s32 *)(*(s32 *)arg2 + var_t0 + 4);
    *(s32 *)(*(s32 *)arg2 + var_t0 + 4) = arg1;
    *(s64 *)(arg0 + 8) = 0;
    *(s64 *)arg0 = 0;
    *(s8 *)(arg0 + 3) = 0x60;
    return arg0 + 0x10;
}

void func_00208090(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_00209D30(func_00208110(func_00209D20(), arg0, arg1, arg2, arg3, arg4));
}

INCLUDE_ASM("asm/nonmatchings/main_056", func_00208110);

INCLUDE_ASM("asm/nonmatchings/main_056", func_00208280);

void func_00208460(void) {
    func_00209D30(func_0020F290(func_00209D20()));
}

void func_00208490(s32 arg0) {
    func_00209D30(func_0020A0B0(func_00209D20(), arg0));
}

INCLUDE_ASM("asm/nonmatchings/main_056", func_002084D0);

void *func_00208530(void *arg0, s32 arg1) {
    *(s64 *)((u8 *)arg0 + 8) = 0;
    *(s64 *)arg0 = 0;
    *((u8 *)arg0 + 3) = 0x10;
    *(u64 *)((u8 *)arg0 + 0x10) = 0x1000000000008001ULL;
    *(s64 *)((u8 *)arg0 + 0x18) = 0xE;
    *(s64 *)((u8 *)arg0 + 0x20) = arg1;
    *(s64 *)((u8 *)arg0 + 0x28) = 0x45;
    *(u16 *)arg0 = 2;
    *(u32 *)((u8 *)arg0 + 8) = 0x11000000;
    *(u32 *)((u8 *)arg0 + 0xC) = 0x51000002;
    return (u8 *)arg0 + 0x30;
}

void func_002085A0(s32 arg0) {
    func_00209D30(func_002085E0(func_00209D20(), arg0));
}

INCLUDE_ASM("asm/nonmatchings/main_056", func_002085E0);

INCLUDE_ASM("asm/nonmatchings/main_056", func_00208680);

typedef struct {
    u16 index;
    u16 flags;
    u8 padding[0xC];
    s64 values[1];
} Buffer_002086D0;

s32 func_002086D0(void *arg0, s64 arg1) {
    Buffer_002086D0 *buffer = arg0;
    u16 index = buffer->index;
    s64 *values = (s64 *)((u8 *)arg0 + 0x10);

    buffer->flags |= 0x200;
    values[index] = arg1;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_056", func_00208700);

typedef struct {
    u16 count;
    u16 flags;
    u8 padding[12];
    u8 data[1];
} Header_002087A0;

void func_00208870(s32, s32, s32, void *, void *);

s32 func_002087A0(void *arg0, s32 arg1) {
    Header_002087A0 *header = arg0;
    u16 count = header->count;
    u8 *data = header->data;

    if (!(header->flags & 0x20)) {
        return 0;
    }
    func_00208870(0, 0, arg1, data + (count & 0xFFFF) * 8 + 8,
                 data + (count & 0xFFFF) * 8 + 0x10);
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_056", func_00208800);

INCLUDE_ASM("asm/nonmatchings/main_056", func_00208870);

typedef struct Buffer_00208CB0 {
    u16 index;
    u16 flags;
    u8 padding[0xC];
    s64 values[1];
} Buffer_00208CB0;

s32 func_00208CB0(void *arg0, s64 arg1) {
    Buffer_00208CB0 *buffer = arg0;
    u16 index = buffer->index;
    s64 *values = buffer->values;
    u16 *flags = &buffer->flags;

    if (!(*flags & 0x20)) {
        return 0;
    }
    *flags |= 0x4000;
    *(s64 *)((u8 *)values + (index & 0xFFFF) * 8 + 0x18) = arg1;
    return 1;
}

s64 func_00208D00(s32 arg0) {
    s64 ret;

    if (arg0 < 0 || arg0 >= 4) {
        ret = 0;
    } else {
        ret = D_002D0830[arg0];
    }
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/main_056", func_00208D40);

typedef struct {
    s32 flags;
    void *data;
    s32 field8;
    s32 fieldC;
} Header_00208E40;

void *func_00208E40(void *arg0) {
    Header_00208E40 *header = arg0;

    header->flags = 0x20000000;
    header->data = (u8 *)arg0 + 0x20;
    header->field8 = 0;
    header->fieldC = 0;
    return (u8 *)arg0 + 0x20;
}

void *func_00208E60(void *arg0, void *arg1) {
    ((u32 *)arg0)[0] = 0x10000004;
    ((u32 *)arg0)[1] = 0;
    ((u32 *)arg0)[2] = 0;
    ((u32 *)arg0)[3] = 0x6C040044;
    func_0020B380((u8 *)arg0 + 0x10, arg1, 4);
    return (u8 *)arg0 + 0x50;
}

INCLUDE_ASM("asm/nonmatchings/main_056", func_00208EB0);

INCLUDE_ASM("asm/nonmatchings/main_056", func_00208F00);

INCLUDE_ASM("asm/nonmatchings/main_056", func_00209110);

INCLUDE_ASM("asm/nonmatchings/main_056", func_00209270);

INCLUDE_ASM("asm/nonmatchings/main_056", func_00209320);

INCLUDE_ASM("asm/nonmatchings/main_056", func_002093E0);

typedef struct {
    u32 header[4];
    f32 value_10;
    f32 value_14;
    f32 value_18;
    f32 value_1C;
} Packet_00209490;

extern f32 D_00325DE0;
extern f32 D_00325DE4;
extern f32 D_00325DE8;
extern f32 D_00325DEC;

void *func_00209490(void *arg0, s32 arg1, s32 arg2) {
    Packet_00209490 *packet = arg0;

    packet->header[0] = 0x10000001;
    packet->header[1] = 0;
    packet->header[2] = 0x10000000;
    packet->header[3] = 0x6C014053;
    if (arg1 != 0) {
        packet->value_18 = D_00325DE0;
        packet->value_1C = D_00325DE4;
    } else {
        packet->value_18 = 0.0f;
        packet->value_1C = 255.0f;
    }
    if (arg2 != 0) {
        packet->value_10 = D_00325DE8;
        packet->value_14 = D_00325DEC;
    } else {
        packet->value_10 = 0.0f;
        packet->value_14 = 0.0f;
    }
    return (u8 *)arg0 + 0x20;
}

INCLUDE_ASM("asm/nonmatchings/main_056", func_00209510);

s32 func_00209870(void) {
    func_0020DEE0();
    func_00200210();
    func_0020BA80();
    func_002173F0();
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_056", func_002098B0);

INCLUDE_ASM("asm/nonmatchings/main_056", func_002099D0);

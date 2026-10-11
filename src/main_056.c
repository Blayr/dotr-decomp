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

typedef struct Node_00207510 {
    u16 unused0;
    u8 unused2;
    u8 tag;
    struct Node_00207510 *next;
} Node_00207510;

typedef struct Context_00207510 {
    Node_00207510 *table;
    s32 unused4;
    Node_00207510 *head;
    s32 depth;
} Context_00207510;

void func_00207510(void *arg0) {
    Node_00207510 *tail;
    Node_00207510 *node;
    Node_00207510 *next;
    Context_00207510 *ctx = arg0;

    tail = NULL;
    node = ctx->table + ((1 << ctx->depth) - 1);
    do {
        next = node->next;
        if (*(u16 *)((u8 *)node + 2) != 7) {
            if (tail != NULL) {
                if (tail->tag == 0x50) {
                    tail->next = (Node_00207510 *)((u8 *)tail + 0x20);
                    tail = (Node_00207510 *)((u8 *)tail + 0x10);
                }
                tail->tag = 0x20;
                tail->next = node;
            } else {
                ctx->head->tag = 0x20;
                ctx->head->next = node;
            }
            tail = node;
        }
        node = next;
    } while (next != (Node_00207510 *)-1);
    if (tail != NULL) {
        if (tail->tag == 0x50) {
            tail->next = (Node_00207510 *)((u8 *)tail + 0x20);
            tail = (Node_00207510 *)((u8 *)tail + 0x10);
        }
        tail->tag = 0x20;
        tail->next = (Node_00207510 *)func_00209D20();
    }
}

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

s32 func_002085E0(s32 arg0, s32 arg1) {
    u64 value;

    if (arg1 < 0 || arg1 >= 4) {
        return arg0;
    }

    value = D_00293EE0[arg1];
    *(u64 *)(arg0 + 8) = 0;
    *(u64 *)arg0 = 0;
    *(u8 *)(arg0 + 3) = 0x10;
    *(u64 *)(arg0 + 0x10) = 0x1000000000008001ULL;
    *(u64 *)(arg0 + 0x18) = 0xE;
    *(u64 *)(arg0 + 0x20) = value;
    *(u64 *)(arg0 + 0x28) = 0x44;
    *(u16 *)arg0 = 2;
    *(u32 *)(arg0 + 8) = 0x11000000;
    *(u32 *)(arg0 + 0xC) = 0x51000002;
    return arg0 + 0x30;
}

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

typedef struct {
    u64 reserved0 : 5;
    u64 flag : 1;
    u64 mode : 3;
    u64 reserved9 : 55;
} Flags_00208700;

s32 func_00208700(void *arg0, void *arg1, s32 arg2) {
    u8 *base = (u8 *)arg0 + 0x10;
    u16 count = *(u16 *)arg0;
    u64 *dst;

    if (!(*(u16 *)((u8 *)arg0 + 2) & 0x20)) {
        return 0;
    }
    if (arg1 == NULL) {
        return 0;
    }
    dst = (u64 *)(base + count * 8);
    dst[1] = *(u64 *)((u8 *)arg1 + 0x30);
    dst[2] = *(u64 *)((u8 *)arg1 + 0x40);
    ((Flags_00208700 *)(dst + 2))->flag = (((Flags_00208700 *)(dst + 2))->mode = arg2);
    return 1;
}

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

void *func_00208D40(void *arg0, s32 arg1) {
    s32 *packet = arg0;

    packet[0] = 0x10000001;
    packet[1] = 0;
    packet[2] = 0x10000000;
    packet[3] = 0x68014000;
    if (!(arg1 & 2) || !D_00325E2C) {
        if (arg1 & 0x40) {
            if (arg1 & 0x20) {
                packet[4] = 0x274;
            } else if (arg1 & 0x10) {
                packet[4] = 0xE8;
            } else {
                packet[4] = 0xE8;
            }
        } else {
            if (arg1 & 0x20) {
                packet[4] = 0x1A4;
            } else if (arg1 & 0x10) {
                packet[4] = 0x30;
            } else {
                packet[4] = 0x30;
            }
        }
    } else {
        if (arg1 & 0x20) {
            packet[4] = 0x6D4;
        } else {
            packet[4] = 0x580;
        }
    }
    packet[5] = 0;
    packet[6] = 0;
    packet[7] = 0x10000000;
    D_00325DD0 = arg1;
    return packet + 8;
}

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

s32 func_00209270(void *arg0, void *arg1, f32 *arg2, f32 *arg3, f32 *arg4) {
    if (arg0 != NULL) {
        *(Vec4_00209270 *)arg0 = D_00325E00;
    }
    if (arg1 != NULL) {
        *(Vec4_00209270 *)arg1 = D_00325E10;
    }
    if (arg2 != NULL) {
        *arg2 = D_00325E20;
    }
    if (arg3 != NULL) {
        *arg3 = D_00325E24;
    }
    if (arg4 != NULL) {
        *arg4 = D_00325E28;
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

void *func_00209320(void *arg0, s32 arg1, f32 fparg0, f32 fparg1, f32 fparg2) {
    f32 temp_f2;
    s32 enabled;
    Packet_00209320 *packet = arg0;

    packet->tag0 = 0x10000001;
    packet->zero0 = 0;
    packet->zero1 = 0;
    packet->command0 = 0x6C014052;
    temp_f2 = 2.0f * fparg0;
    packet->right = 645.0f / temp_f2;
    packet->left = -645.0f / temp_f2;
    packet->near_value = 0.01f + fparg1;
    packet->far_value = fparg2 - 0.01f;
    packet->tag1 = 0x10000001;
    packet->zero2 = 0;
    packet->zero3 = 0;
    packet->command1 = 0x6C01405A;
    if (arg1 == 1) {
        enabled = 1;
    } else {
        enabled = 0;
    }
    packet->enabled = enabled;
    packet->zero4 = 0;
    packet->zero5 = 0;
    packet->zero6 = 0;
    return (u8 *)arg0 + 0x40;
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

void *func_002093E0(void *arg0, f32 fparg0, f32 fparg1, f32 fparg2, f32 fparg3) {
    Packet_002093E0 *packet = arg0;
    f32 temp_f1;
    f32 temp_f2;

    packet->tag[0] = 0x10000001;
    packet->tag[1] = 0;
    packet->tag[2] = 0x10000000;
    temp_f2 = 255.0f / (fparg3 - fparg2);
    packet->tag[3] = 0x6C014053;
    packet->values[0] = temp_f2;
    temp_f1 = 255.0f / (fparg1 - fparg0);
    packet->values[1] = fparg2 * temp_f2;
    packet->values[2] = temp_f1;
    packet->values[3] = fparg1 * temp_f1;
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

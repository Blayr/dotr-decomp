#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_068", func_0023B1F0);

INCLUDE_ASM("asm/nonmatchings/main_068", func_0023B920);

void func_0023BB00(s32 arg0) {
    s32 var_s0;
    s32 var_s1;
    s32 var_s2;

    switch (D_0034F700) {
    case 0:
        var_s0 = 0x20;
        var_s1 = 0x11;
        var_s2 = 0x12;
        break;
    case 1:
        var_s0 = 0x21;
        var_s1 = 0x13;
        var_s2 = 0x14;
        break;
    case 2:
        var_s0 = 0x22;
        var_s1 = 0x15;
        var_s2 = 0x16;
        break;
    case 3:
        var_s0 = 0x23;
        var_s1 = 0x17;
        var_s2 = 0x18;
        break;
    case 4:
        var_s0 = 0x24;
        var_s1 = 0x19;
        var_s2 = 0x1A;
        break;
    }
    func_001A8320(1, 0);
    func_001A8320(2, 0);
    func_001A8320(3, var_s0);
    func_001A8320(4, var_s0);
    func_00214990(0, var_s1);
    func_00214990(1, var_s2);
    if (D_0034F700 < 3) {
        D_0034F700 += 1;
        if (D_0034F700 > 2) {
            D_0034F700 = 0;
            D_0034F708 = 1;
        }
    }
    if (arg0 != 0) {
        func_001A87C0(1, 0);
    } else {
        func_001A8870(1, 0);
    }
}

INCLUDE_ASM("asm/nonmatchings/main_068", func_0023BC80);

INCLUDE_ASM("asm/nonmatchings/main_068", func_0023BCE0);

INCLUDE_ASM("asm/nonmatchings/main_068", func_0023BFF0);

INCLUDE_ASM("asm/nonmatchings/main_068", func_0023C140);

INCLUDE_ASM("asm/nonmatchings/main_068", func_0023C150);

INCLUDE_ASM("asm/nonmatchings/main_068", func_0023C160);

INCLUDE_ASM("asm/nonmatchings/main_068", func_0023C170);

INCLUDE_ASM("asm/nonmatchings/main_068", func_0023C3F0);

INCLUDE_ASM("asm/nonmatchings/main_068", func_0023C560);

INCLUDE_ASM("asm/nonmatchings/main_068", func_0023C770);

INCLUDE_ASM("asm/nonmatchings/main_068", func_0023C8B0);

INCLUDE_ASM("asm/nonmatchings/main_068", func_0023CA10);

INCLUDE_ASM("asm/nonmatchings/main_068", func_0023CC50);

INCLUDE_ASM("asm/nonmatchings/main_068", func_0023CE40);

INCLUDE_ASM("asm/nonmatchings/main_068", func_0023D170);

INCLUDE_ASM("asm/nonmatchings/main_068", func_0023D400);

INCLUDE_ASM("asm/nonmatchings/main_068", func_0023D920);

INCLUDE_ASM("asm/nonmatchings/main_068", func_0023DE90);

typedef struct State_0023E610 {
    s32 result;
    u8 pad04[0x1C];
    s32 command;
    s32 status;
    u8 pad28[8];
    s16 field30;
    u8 pad32[2];
    s16 field34;
    u8 pad36[0xA];
    s16 field40;
} State_0023E610;

s32 func_00194248(s32, s32 *, s32 *);
s32 func_001948A8(s32, s32);
extern State_0023E610 D_0034FB00;
extern s32 D_0034FB04;
extern s32 D_0034FB08;
extern s32 D_0034FB0C;
extern s32 D_0034FB20;
extern s32 D_0034FB24;

s32 func_0023E610(void) {
    State_0023E610 *state = &D_0034FB00;

    D_0034FB00.result = func_001948A8(D_0034FB08, D_0034FB0C);
    D_0034FB04 = func_00194248(1, &D_0034FB20, &D_0034FB24);
    if (D_0034FB04 == 1) {
        if (state->command == 0x10) {
            if (state->status == 0) {
                state->field30 = 0xE;
                state->field40 = 0;
                state->field34 = 0;
                return 0xC;
            }
            return 0xD;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_068", func_0023E6D0);

INCLUDE_ASM("asm/nonmatchings/main_068", func_0023E7A0);

INCLUDE_ASM("asm/nonmatchings/main_068", func_0023F130);

INCLUDE_ASM("asm/nonmatchings/main_068", func_0023F340);

INCLUDE_ASM("asm/nonmatchings/main_068", func_0023F5A0);

INCLUDE_ASM("asm/nonmatchings/main_068", func_0023FBE0);

INCLUDE_ASM("asm/nonmatchings/main_068", func_0023FCE0);

INCLUDE_ASM("asm/nonmatchings/main_068", func_0023FF30);

INCLUDE_ASM("asm/nonmatchings/main_068", func_002406C0);

INCLUDE_ASM("asm/nonmatchings/main_068", func_002409E0);

s32 func_00241190(u16 *arg0) {
    u16 checksum;
    u16 saved;
    u16 i;
    u16 *p;

    saved = arg0[1];
    checksum = 0;
    i = 0;
    p = arg0;
    arg0[1] = 0;
    while (i < 0x8078) {
        checksum ^= *p++;
        i++;
    }
    checksum ^= 0x4C6B;
    arg0[1] = checksum;
    if (checksum == saved) {
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_068", func_00241200);

INCLUDE_ASM("asm/nonmatchings/main_068", func_002413F0);

INCLUDE_ASM("asm/nonmatchings/main_068", func_00241840);

s32 func_00241A00(s32 arg0, s32 arg1) {
    u8 color[4];
    s32 temp_v1;

    temp_v1 = arg0 & 0xFFFF;
    if (!(temp_v1 & 0xFFFF7FFF)) {
        return arg0;
    }
    func_00241840(color, temp_v1 & 0x1F, (temp_v1 >> 5) & 0x1F, (temp_v1 >> 0xA) & 0x1F, arg1, 0x1F);
    return (arg0 & 0x8000) | (((color[2] & 0x1F) << 0xA) | ((color[0] & 0x1F) | ((color[1] & 0x1F) << 5)));
}

typedef struct Buffer_00241A90 {
    u8 data[0x50000];
    s32 field_50000;
    s32 field_50004;
    s32 field_50008;
} Buffer_00241A90;

void func_00241A90(void *arg0) {
    Buffer_00241A90 *buffer = arg0;

    buffer->field_50004 = 0;
    buffer->field_50000 = 0;
    buffer->field_50008 = 0x50000;
}

void func_00241AC0(void) {

}

typedef struct Header_00241AD0 {
    u8 padding[0x50000];
    s32 offset;
    s32 start;
    s32 end;
} Header_00241AD0;

s32 func_00241AD0(void *arg0, void **arg1) {
    s32 size = ((Header_00241AD0 *)arg0)->end - ((Header_00241AD0 *)arg0)->start;

    if (size != 0) {
        *arg1 = (u8 *)arg0 + ((Header_00241AD0 *)arg0)->offset;
    }
    return size;
}

typedef struct {
    u8 padding[0x50000];
    s32 position;
    s32 count;
    s32 capacity;
} Buffer_00241B10;

s32 func_00241B10(void *arg0, s32 arg1) {
    Buffer_00241B10 *buffer = arg0;
    s32 capacity;
    s32 available;

    capacity = buffer->capacity;
    available = capacity - buffer->count;
    arg1 = (arg1 < available) ? arg1 : available;
    buffer->position = (buffer->position + arg1) % capacity;
    buffer->count = buffer->count + arg1;
    return arg1;
}

typedef struct {
    u8 data[0x50000];
    s32 write_index;
    s32 count;
    s32 capacity;
} Buffer_00241B80;

s32 func_00241B80(void *arg0, void **arg1) {
    Buffer_00241B80 *buffer = arg0;
    s32 count;
    s32 capacity;

    count = buffer->count;
    if (count != 0) {
        capacity = buffer->capacity;
        *arg1 = (u8 *)arg0 + ((capacity + (buffer->write_index - count)) % capacity);
    }
    return buffer->count;
}

s32 func_00241BE0(s32 *arg0, s32 arg1) {
    s32 remaining;

    remaining = arg0[0x14001];
    arg1 = (arg1 < remaining) ? arg1 : remaining;
    arg0[0x14001] -= arg1;
    return arg1;
}

INCLUDE_ASM("asm/nonmatchings/main_068", func_00241C20);

INCLUDE_ASM("asm/nonmatchings/main_068", func_00241E80);

INCLUDE_ASM("asm/nonmatchings/main_068", func_00242190);

INCLUDE_ASM("asm/nonmatchings/main_068", func_002423A0);

INCLUDE_ASM("asm/nonmatchings/main_068", func_002423F0);

void func_00242450(void) {
    D_00350340 = 0;
    D_003505F8 = 0;
}

void func_00242470(s32 arg0, s32 arg1, s32 arg2) {
    D_0029B2F0 = arg1;
    D_003503B0 = arg2;
    func_00241C20(0, 0, 0, 0x280, 0x1C0);
    func_001851E8(D_003503C0, 0, 0x280, 0xE0, 0, 0, 1);
    func_0017BB60(0);
    D_00350368 = 0x01200000;
    D_00350370 = 0x0152A000;
    D_00350378 = 0x015C3C80;
    D_00350380 = 0x015C4CC0;
    D_00350388 = 0x0178DE40;
    D_00350788 = 0x0178E640;
    D_00350390 = 0x017DE680;
    D_00350398 = 0x017EA680;
    D_003503A0 = 0x0186A680;
    D_003503A8 = 0x0186E680;
    func_00242580(arg0);
}

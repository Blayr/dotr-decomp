#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_068", func_0023B1F0);

INCLUDE_ASM("asm/nonmatchings/main_068", func_0023B920);

INCLUDE_ASM("asm/nonmatchings/main_068", func_0023BB00);

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

INCLUDE_ASM("asm/nonmatchings/main_068", func_0023E610);

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

INCLUDE_ASM("asm/nonmatchings/main_068", func_00241190);

INCLUDE_ASM("asm/nonmatchings/main_068", func_00241200);

INCLUDE_ASM("asm/nonmatchings/main_068", func_002413F0);

INCLUDE_ASM("asm/nonmatchings/main_068", func_00241840);

INCLUDE_ASM("asm/nonmatchings/main_068", func_00241A00);

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

INCLUDE_ASM("asm/nonmatchings/main_068", func_00241B10);

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

INCLUDE_ASM("asm/nonmatchings/main_068", func_00242470);

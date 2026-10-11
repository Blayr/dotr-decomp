#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_075", func_0025ED20);

INCLUDE_ASM("asm/nonmatchings/main_075", func_0025EE40);

INCLUDE_ASM("asm/nonmatchings/main_075", func_0025EF40);

INCLUDE_ASM("asm/nonmatchings/main_075", func_0025F2A0);

INCLUDE_ASM("asm/nonmatchings/main_075", func_0025F310);

INCLUDE_ASM("asm/nonmatchings/main_075", func_0025F390);

INCLUDE_ASM("asm/nonmatchings/main_075", func_0025F400);

INCLUDE_ASM("asm/nonmatchings/main_075", func_0025F670);

s32 func_0024EC50(s32, s32);
s32 func_00255A30(void *, void *);

typedef struct Source_0025F720 {
    s32 pad[2];
    s32 handle;
} Source_0025F720;
typedef struct Request_0025F720 {
    s32 type, zero, value, flag;
} Request_0025F720;
typedef struct Result_0025F720 {
    u8 pad[6];
    u8 status[26];
    s32 values[45];
    u8 count;
} Result_0025F720;

void func_0025F720(void *arg0, void *arg1, void *arg2, s32 arg3) {
    s32 index;
    s32 count;
    s32 value;
    s64 flag;
    u8 result;
    Source_0025F720 *src = arg0;
    Result_0025F720 *dst = arg1;
    Request_0025F720 *req = arg2;

    count = func_0024E910(src->handle);
    for (index = 0; index < count; index++) {
        value = func_0024EC50(src->handle, index);
        req->type = arg3;
        req->zero = 0;
        req->value = value;
        if (arg3 == 0x25B) {
            flag = 1;
        } else {
            flag = 0;
        }
        req->flag = flag;
        result = func_00255A30(req, dst);
        dst->status[dst->count] = result;
        if ((s32)result >= 0) {
            dst->values[dst->count] = value;
            dst->count++;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/main_075", func_0025F820);

INCLUDE_ASM("asm/nonmatchings/main_075", func_0025F990);

INCLUDE_ASM("asm/nonmatchings/main_075", func_0025FB00);

INCLUDE_ASM("asm/nonmatchings/main_075", func_0025FC30);

INCLUDE_ASM("asm/nonmatchings/main_075", func_0025FD90);

INCLUDE_ASM("asm/nonmatchings/main_075", func_0025FF30);

INCLUDE_ASM("asm/nonmatchings/main_075", func_00260020);

INCLUDE_ASM("asm/nonmatchings/main_075", func_00260200);

INCLUDE_ASM("asm/nonmatchings/main_075", func_00260320);

INCLUDE_ASM("asm/nonmatchings/main_075", func_00260490);

INCLUDE_ASM("asm/nonmatchings/main_075", func_00260740);

INCLUDE_ASM("asm/nonmatchings/main_075", func_002607D0);

INCLUDE_ASM("asm/nonmatchings/main_075", func_00260860);

INCLUDE_ASM("asm/nonmatchings/main_075", func_002608F0);

INCLUDE_ASM("asm/nonmatchings/main_075", func_00260990);

INCLUDE_ASM("asm/nonmatchings/main_075", func_00260A70);

INCLUDE_ASM("asm/nonmatchings/main_075", func_00260AF0);

INCLUDE_ASM("asm/nonmatchings/main_075", func_00260D10);

INCLUDE_ASM("asm/nonmatchings/main_075", func_00260EB0);

INCLUDE_ASM("asm/nonmatchings/main_075", func_002610D0);

INCLUDE_ASM("asm/nonmatchings/main_075", func_002612E0);

INCLUDE_ASM("asm/nonmatchings/main_075", func_00261380);

INCLUDE_ASM("asm/nonmatchings/main_075", func_00261420);

INCLUDE_ASM("asm/nonmatchings/main_075", func_002614C0);

INCLUDE_ASM("asm/nonmatchings/main_075", func_00261570);

INCLUDE_ASM("asm/nonmatchings/main_075", func_00261580);

INCLUDE_ASM("asm/nonmatchings/main_075", func_00261600);

void func_00261680(s32 arg0) {
    f32 temp_f0;

    if (func_001F6620() != 4) {
        func_001F66A0(arg0, 4);
        return;
    }
    temp_f0 = func_001F67C0(arg0, 4);
    if (!(temp_f0 < 16.0f)) {
        func_001F6840(arg0, 11.0f);
        return;
    }
    if (!(temp_f0 <= 11.0f) && ((func_0019A5C8() % 3) == 0)) {
        func_001F6840(arg0, temp_f0 - 2.0f);
    }
}

INCLUDE_ASM("asm/nonmatchings/main_075", func_00261760);

INCLUDE_ASM("asm/nonmatchings/main_075", func_00261B70);

INCLUDE_ASM("asm/nonmatchings/main_075", func_00261F20);

INCLUDE_ASM("asm/nonmatchings/main_075", func_00262190);

INCLUDE_ASM("asm/nonmatchings/main_075", func_00262680);

INCLUDE_ASM("asm/nonmatchings/main_075", func_002626F0);

INCLUDE_ASM("asm/nonmatchings/main_075", func_00262BE0);

INCLUDE_ASM("asm/nonmatchings/main_075", func_00263180);

INCLUDE_ASM("asm/nonmatchings/main_075", func_00263500);

INCLUDE_ASM("asm/nonmatchings/main_075", func_00263790);

INCLUDE_ASM("asm/nonmatchings/main_075", func_00263930);

INCLUDE_ASM("asm/nonmatchings/main_075", func_00265050);

INCLUDE_ASM("asm/nonmatchings/main_075", func_00265440);

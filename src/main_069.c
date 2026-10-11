#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_069", func_00242580);

INCLUDE_ASM("asm/nonmatchings/main_069", func_00242600);

INCLUDE_ASM("asm/nonmatchings/main_069", func_00242900);

INCLUDE_ASM("asm/nonmatchings/main_069", func_00242910);

INCLUDE_ASM("asm/nonmatchings/main_069", func_00242950);

INCLUDE_ASM("asm/nonmatchings/main_069", func_00242C20);

void func_00242CD0(void) {
loop_1:
    func_0017B790(0x20);
    goto loop_1;
}

INCLUDE_ASM("asm/nonmatchings/main_069", func_00242CF0);

INCLUDE_ASM("asm/nonmatchings/main_069", func_00242D00);

INCLUDE_ASM("asm/nonmatchings/main_069", func_00242D10);

INCLUDE_ASM("asm/nonmatchings/main_069", func_00242E40);

INCLUDE_ASM("asm/nonmatchings/main_069", func_00242F20);

INCLUDE_ASM("asm/nonmatchings/main_069", func_00243060);

INCLUDE_ASM("asm/nonmatchings/main_069", func_00243170);

INCLUDE_ASM("asm/nonmatchings/main_069", func_002431B0);

INCLUDE_ASM("asm/nonmatchings/main_069", func_00243230);

INCLUDE_ASM("asm/nonmatchings/main_069", func_00243290);

INCLUDE_ASM("asm/nonmatchings/main_069", func_002432F0);

INCLUDE_ASM("asm/nonmatchings/main_069", func_00243390);

INCLUDE_ASM("asm/nonmatchings/main_069", func_00243450);

INCLUDE_ASM("asm/nonmatchings/main_069", func_00243580);

INCLUDE_ASM("asm/nonmatchings/main_069", func_002435A0);

INCLUDE_ASM("asm/nonmatchings/main_069", func_00243750);

INCLUDE_ASM("asm/nonmatchings/main_069", func_002437F0);

INCLUDE_ASM("asm/nonmatchings/main_069", func_00243950);

INCLUDE_ASM("asm/nonmatchings/main_069", func_002439D0);

void func_00243A40(s32 arg0) {
    func_00190810(1, 0x8010, 0xF80, arg0);
    func_00190810(1, 0x8010, 0x1080, arg0);
}

INCLUDE_ASM("asm/nonmatchings/main_069", func_00243A90);

typedef struct {
    s32 unk00;
    u8 pad04[0x28];
    s32 unk2C;
    s32 unk30;
} Obj_00243D90;

void func_0017FD20(s32);
void func_00182A28(s32);
void func_00192058(void);

s32 func_00243D90(void *arg0) {
    Obj_00243D90 *p = (Obj_00243D90 *)arg0;

    if (p->unk00 != 0) {
        func_00192058();
        func_00182A28(p->unk2C);
    } else {
        func_0017FD20(p->unk30);
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_069", func_00243DE0);

INCLUDE_ASM("asm/nonmatchings/main_069", func_00243EE0);

INCLUDE_ASM("asm/nonmatchings/main_069", func_00243F60);

INCLUDE_ASM("asm/nonmatchings/main_069", func_002440F0);

INCLUDE_ASM("asm/nonmatchings/main_069", func_002441F0);

INCLUDE_ASM("asm/nonmatchings/main_069", func_00244250);

INCLUDE_ASM("asm/nonmatchings/main_069", func_00244530);

INCLUDE_ASM("asm/nonmatchings/main_069", func_00244680);

INCLUDE_ASM("asm/nonmatchings/main_069", func_00244A40);

INCLUDE_ASM("asm/nonmatchings/main_069", func_00244AD0);

INCLUDE_ASM("asm/nonmatchings/main_069", func_00244B20);

INCLUDE_ASM("asm/nonmatchings/main_069", func_00244B70);

INCLUDE_ASM("asm/nonmatchings/main_069", func_00244CB0);

INCLUDE_ASM("asm/nonmatchings/main_069", func_00244DE0);

INCLUDE_ASM("asm/nonmatchings/main_069", func_00244FB0);

s32 func_002450B0(void) {
    func_0018E200();
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_069", func_002450D0);

INCLUDE_ASM("asm/nonmatchings/main_069", func_002450E0);

INCLUDE_ASM("asm/nonmatchings/main_069", func_002450F0);

INCLUDE_ASM("asm/nonmatchings/main_069", func_00245100);

INCLUDE_ASM("asm/nonmatchings/main_069", func_00245140);

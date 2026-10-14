#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_030", func_0018DAA8);

INCLUDE_ASM("asm/nonmatchings/main_030", func_0018DB40);

INCLUDE_ASM("asm/nonmatchings/main_030", func_0018DB90);

INCLUDE_ASM("asm/nonmatchings/main_030", func_0018DBD8);

INCLUDE_ASM("asm/nonmatchings/main_030", func_0018DC30);

INCLUDE_ASM("asm/nonmatchings/main_030", func_0018DC60);

INCLUDE_ASM("asm/nonmatchings/main_030", func_0018DCE8);

INCLUDE_ASM("asm/nonmatchings/main_030", func_0018DEE8);

INCLUDE_ASM("asm/nonmatchings/main_030", func_0018E1E0);

INCLUDE_ASM("asm/nonmatchings/main_030", func_0018E200);

INCLUDE_ASM("asm/nonmatchings/main_030", func_0018E2F8);

INCLUDE_ASM("asm/nonmatchings/main_030", func_0018E448);

INCLUDE_ASM("asm/nonmatchings/main_030", func_0018E4B8);

INCLUDE_ASM("asm/nonmatchings/main_030", func_0018EA68);

INCLUDE_ASM("asm/nonmatchings/main_030", func_0018EB08);

s32 func_0018ED10(s32 unused0) {
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_030", func_0018ED18);

INCLUDE_ASM("asm/nonmatchings/main_030", func_0018ED40);

INCLUDE_ASM("asm/nonmatchings/main_030", func_0018ED88);

INCLUDE_ASM("asm/nonmatchings/main_030", func_0018EDD0);

INCLUDE_ASM("asm/nonmatchings/main_030", func_0018EE20);

void func_0018EE38(void *arg0, s32 *arg1, s32 *arg2, s32 *arg3) {
    void *temp_t0;

    temp_t0 = (*(void **)((u8 *)arg0 + 0x40));
    *arg1 = (*(s32 *)((u8 *)temp_t0 + 0x94));
    *arg2 = (*(s32 *)((u8 *)temp_t0 + 0x98));
    *arg3 = (*(s32 *)((u8 *)temp_t0 + 0x9C));
}

s32 func_0018EE58(void *arg0) {
    return *(*(s32 **)((u8 *)arg0 + 0x40));
}

s32 func_0018EE68(void *arg0) {
    return (*(s32 *)((u8 *)((*(void **)((u8 *)arg0 + 0x40))) + 4)) == 0;
}

INCLUDE_ASM("asm/nonmatchings/main_030", func_0018EE78);

INCLUDE_ASM("asm/nonmatchings/main_030", func_0018EEC8);

INCLUDE_ASM("asm/nonmatchings/main_030", func_0018EF20);

INCLUDE_ASM("asm/nonmatchings/main_030", func_0018EF48);

INCLUDE_ASM("asm/nonmatchings/main_030", func_0018EF98);

INCLUDE_ASM("asm/nonmatchings/main_030", func_0018EFC0);

void func_0018EFD8(void *arg0) {
    u8 *p = *(u8 **)((u8 *)arg0 + 0x40);

    *(s32 *)(p + 0x70) = 0;
    *(s64 *)(p + 0x78) = 0;
}

void func_0018EFE8(void *arg0, s32 arg1) {
    (*(s32 *)((u8 *)((*(void **)((u8 *)arg0 + 0x40))) + 0xD8)) = arg1;
}

s32 func_0018EFF8(void *arg0) {
    return (*(s32 *)((u8 *)((*(void **)((u8 *)arg0 + 0x40))) + 0xCC));
}

s32 func_0018F008(void *arg0) {
    return (*(s32 *)((u8 *)((*(void **)((u8 *)arg0 + 0x40))) + 0xD0));
}

s32 func_0018F018(void *arg0) {
    return (*(s32 *)((u8 *)arg0 + 0x40)) + 0xB4;
}

s32 func_0018F028(void *arg0) {
    return (*(s32 *)((u8 *)arg0 + 0x40)) + 0xB4;
}

s32 func_0018F038(void *arg0, s32 arg1) {
    s32 temp_v0;
    void *temp_v1;

    temp_v1 = (*(void **)((u8 *)arg0 + 0x40));
    temp_v0 = (*(s32 *)((u8 *)temp_v1 + 0xE8));
    (*(s32 *)((u8 *)temp_v1 + 0xE8)) = arg1;
    return temp_v0;
}

INCLUDE_ASM("asm/nonmatchings/main_030", func_0018F048);

INCLUDE_ASM("asm/nonmatchings/main_030", func_0018F060);

void func_0018F078(void *arg0) {
    (*(s32 *)((u8 *)arg0 + 0xC)) = (s32) (*(s32 *)((u8 *)arg0 + 8));
}

void func_0018F088(void *arg0) {
    (*(s32 *)((u8 *)arg0 + 8)) = (s32) (*(s32 *)((u8 *)arg0 + 0xC));
}

INCLUDE_ASM("asm/nonmatchings/main_030", func_0018F098);

s32 func_0018F108(s32 *arg0) {
    return (arg0[0] + arg0[1]) - arg0[2];
}

INCLUDE_ASM("asm/nonmatchings/main_030", func_0018F120);

INCLUDE_ASM("asm/nonmatchings/main_030", func_0018F290);

INCLUDE_ASM("asm/nonmatchings/main_030", func_0018F3A8);

INCLUDE_ASM("asm/nonmatchings/main_030", func_0018F3F0);

INCLUDE_ASM("asm/nonmatchings/main_030", func_0018F550);

void func_0018F5B8(void *arg0) {
    *(s32 *)((u8 *)arg0 + 0x848) = 0;
    func_0018A378(1);
}

INCLUDE_ASM("asm/nonmatchings/main_030", func_0018F5C8);

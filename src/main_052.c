#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_052", func_001F6F50);

INCLUDE_ASM("asm/nonmatchings/main_052", func_001F7060);

void func_001F7070(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_001F70A0(D_0031BE9C, arg0, arg1, arg2, arg3, arg4);
}

INCLUDE_ASM("asm/nonmatchings/main_052", func_001F70A0);

void func_001F7170(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_001F71A0(D_0031BE9C, arg0, arg1, arg2, arg3, arg4);
}

INCLUDE_ASM("asm/nonmatchings/main_052", func_001F71A0);

void func_001F7260(s32 arg0) {
    func_001F7350(4, arg0);
    func_001F7350(5, arg0);
    func_001F7350(2, arg0);
    func_001F7350(3, arg0);
    func_001FA770(-1, -1, arg0);
}

INCLUDE_ASM("asm/nonmatchings/main_052", func_001F72C0);

INCLUDE_ASM("asm/nonmatchings/main_052", func_001F7350);

INCLUDE_ASM("asm/nonmatchings/main_052", func_001F73C0);

s32 func_001F74B0(void) {
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_052", func_001F74C0);

INCLUDE_ASM("asm/nonmatchings/main_052", func_001F7550);

INCLUDE_ASM("asm/nonmatchings/main_052", func_001F7720);

INCLUDE_ASM("asm/nonmatchings/main_052", func_001F7790);

INCLUDE_ASM("asm/nonmatchings/main_052", func_001F8A30);

INCLUDE_ASM("asm/nonmatchings/main_052", func_001F8B50);

INCLUDE_ASM("asm/nonmatchings/main_052", func_001F8D30);

INCLUDE_ASM("asm/nonmatchings/main_052", func_001F8F80);

INCLUDE_ASM("asm/nonmatchings/main_052", func_001F90E0);

INCLUDE_ASM("asm/nonmatchings/main_052", func_001F9170);

INCLUDE_ASM("asm/nonmatchings/main_052", func_001F9230);

INCLUDE_ASM("asm/nonmatchings/main_052", func_001F9310);

INCLUDE_ASM("asm/nonmatchings/main_052", func_001F93F0);

INCLUDE_ASM("asm/nonmatchings/main_052", func_001F9500);

INCLUDE_ASM("asm/nonmatchings/main_052", func_001F95E0);

INCLUDE_ASM("asm/nonmatchings/main_052", func_001F96F0);

INCLUDE_ASM("asm/nonmatchings/main_052", func_001F9770);

INCLUDE_ASM("asm/nonmatchings/main_052", func_001F98C0);

INCLUDE_ASM("asm/nonmatchings/main_052", func_001F9940);

INCLUDE_ASM("asm/nonmatchings/main_052", func_001F9A20);

INCLUDE_ASM("asm/nonmatchings/main_052", func_001F9A80);

s32 func_001F9AD0(s32 arg0) {
    s32 temp_v0;

    if (arg0 < 0 || arg0 > 0) {
        return 0;
    }
    temp_v0 = D_0031BEB0[arg0];
    if (temp_v0 == 0) {
        return 0;
    }
    return temp_v0 + 0x20;
}

INCLUDE_ASM("asm/nonmatchings/main_052", func_001F9B20);

s32 func_001F9D30(s32 arg0) {
    s32 data;

    if (arg0 < 0 || arg0 >= 1) {
        return 0;
    }
    data = D_0031BEB0[arg0];
    if (data == 0) {
        return 0;
    }
    return data + 0x30;
}

INCLUDE_ASM("asm/nonmatchings/main_052", func_001F9D80);

s32 func_001F9F90(s32 arg0, s32 arg1) {
    void *temp_v0;

    if (arg0 < 0 || arg0 > 0) {
        return 0;
    }
    temp_v0 = (void *)D_0031BEB0[arg0];
    if (temp_v0 == NULL) {
        return 0;
    }
    *(s32 *)((u8 *)temp_v0 + 0x40) = arg1;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_052", func_001F9FE0);

INCLUDE_ASM("asm/nonmatchings/main_052", func_001FA220);

INCLUDE_ASM("asm/nonmatchings/main_052", func_001FA6F0);

INCLUDE_ASM("asm/nonmatchings/main_052", func_001FA770);

INCLUDE_ASM("asm/nonmatchings/main_052", func_001FA810);

INCLUDE_ASM("asm/nonmatchings/main_052", func_001FA8A0);

s32 func_001FAD10(s32 arg0) {
    s32 temp_v0;

    if (arg0 < 0 || arg0 > 0) {
        return 0;
    }
    temp_v0 = D_0031BEB0[arg0];
    if (temp_v0 == 0) {
        return 0;
    }
    return temp_v0 + 0x10;
}

INCLUDE_ASM("asm/nonmatchings/main_052", func_001FAD60);

INCLUDE_ASM("asm/nonmatchings/main_052", func_001FAF60);

INCLUDE_ASM("asm/nonmatchings/main_052", func_001FAFB0);

INCLUDE_ASM("asm/nonmatchings/main_052", func_001FB0B0);

INCLUDE_ASM("asm/nonmatchings/main_052", func_001FB1D0);

INCLUDE_ASM("asm/nonmatchings/main_052", func_001FB360);

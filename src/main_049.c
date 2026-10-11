#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F1A80);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F1A90);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F1B50);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F1B60);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F1C40);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F1C50);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F1D50);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F1E10);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F1E80);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F1EE0);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F1F70);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F1FD0);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F2050);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F2150);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F22B0);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F2330);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F23B0);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F2430);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F24C0);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F2550);

s32 func_001F25D0(s32 idx, void *src) {
    Obj_0031ABB0 *obj;

    if (idx < 0 || idx >= 0x54) {
        return 0;
    }
    obj = D_0031ABB0[idx];
    if (obj == NULL) {
        return 0;
    }
    if (src != NULL) {
        obj->v = *(Vec4f *)src;
    } else {
        obj->v.x = 1.0f;
        obj->v.y = 1.0f;
        obj->v.z = 1.0f;
        obj->v.w = 1.0f;
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F2660);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F26E0);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F27A0);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F2800);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F2860);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F2920);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F2980);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F29E0);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F2A70);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F2AD0);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F2B30);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F2BE0);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F2C60);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F2DD0);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F2EC0);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F2FF0);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F3050);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F30B0);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F3130);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F3190);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F3210);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F3270);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F32F0);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F3360);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F33C0);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F3440);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F34A0);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F3690);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F3700);

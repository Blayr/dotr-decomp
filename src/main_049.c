#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F1A80);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F1A90);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F1B50);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F1B60);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F1C40);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F1C50);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F1D50);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F1E10);

s32 func_001F1E80(s32 arg0, f32 *arg1) {
    Obj_0031ABB0 *temp_v0;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    temp_v0 = D_0031ABB0[arg0];
    if (temp_v0 == NULL) {
        return 0;
    }
    *arg1 = *(f32 *)((u8 *)temp_v0 + 0x128);
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F1EE0);

s32 func_001F1F70(s32 arg0, f32 fparg0) {
    Obj_0031ABB0 *temp_v0;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    temp_v0 = D_0031ABB0[arg0];
    if (temp_v0 == NULL) {
        return 0;
    }
    *(f32 *)((u8 *)temp_v0 + 0x128) = fparg0;
    return 1;
}

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

s32 func_001F27A0(s32 arg0) {
    Obj_0031ABB0 *temp_v0;

    if (arg0 < 0 || arg0 >= 0x54) {
        return -1;
    }
    temp_v0 = D_0031ABB0[arg0];
    if (temp_v0 == NULL) {
        return -1;
    }
    return temp_v0->pad040[0xEF];
}

s32 func_001F2800(s32 arg0, u8 arg1) {
    Obj_0031ABB0 *temp_v0;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    temp_v0 = D_0031ABB0[arg0];
    if (temp_v0 == NULL) {
        return 0;
    }
    temp_v0->pad040[0xEF] = arg1;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F2860);

s16 func_001F2920(s32 arg0) {
    Obj_0031ABB0 *temp_v0;

    if (arg0 < 0 || arg0 >= 0x54) {
        return -1;
    }
    temp_v0 = D_0031ABB0[arg0];
    if (temp_v0 == NULL) {
        return -1;
    }
    return *(s16 *)((u8 *)temp_v0 + 0x1F4);
}

s8 func_001F2980(s32 arg0) {
    Obj_0031ABB0 *obj;
    s8 ret;

    if (arg0 < 0 || arg0 >= 0x54) {
        ret = -1;
    } else {
        obj = D_0031ABB0[arg0];
        if (obj == NULL) {
            ret = -1;
        } else {
            ret = *(s8 *)((u8 *)obj + 0x1F3);
        }
    }
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F29E0);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F2A70);

s32 func_001F2AD0(s32 arg0, s8 arg1) {
    Obj_0031ABB0 *obj;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }

    obj = D_0031ABB0[arg0];
    if (obj == NULL) {
        return 0;
    }

    *(s8 *)((u8 *)obj + 0x1FF) = arg1;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F2B30);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F2BE0);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F2C60);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F2DD0);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F2EC0);

s32 func_001F2FF0(s32 arg0, s16 arg1) {
    Obj_0031ABB0 *temp_v0;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    temp_v0 = D_0031ABB0[arg0];
    if (temp_v0 == NULL) {
        return 0;
    }
    *(s16 *)((u8 *)temp_v0 + 0x20A) = arg1;
    return 1;
}

s32 func_001F3050(s32 arg0) {
    Obj_0031ABB0 *temp_v0;

    if (arg0 < 0 || arg0 >= 0x54) {
        return -1;
    }
    temp_v0 = D_0031ABB0[arg0];
    if (temp_v0 == NULL) {
        return -1;
    }
    return *(u16 *)((u8 *)temp_v0 + 0x20A);
}

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F30B0);

typedef struct {
    s8 unused : 1;
    s8 enabled : 1;
} Flags_001F3130;

s32 func_001F3130(s32 arg0) {
    Obj_0031ABB0 *temp_v0;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    temp_v0 = D_0031ABB0[arg0];
    if (temp_v0 == NULL) {
        return 0;
    }
    return ((Flags_001F3130 *)((u8 *)temp_v0 + 0x20C))->enabled ? 1 : 0;
}

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F3190);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F3210);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F3270);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F32F0);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F3360);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F33C0);

typedef struct {
    s8 bit0 : 1;
    s8 enabled : 1;
} Flags_001F3440;

s32 func_001F3440(s32 arg0) {
    Obj_0031ABB0 *temp_v0;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    temp_v0 = D_0031ABB0[arg0];
    if (temp_v0 == NULL) {
        return 0;
    }
    return ((Flags_001F3440 *)((u8 *)temp_v0 + 0x20D))->enabled ? 1 : 0;
}

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F34A0);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F3690);

INCLUDE_ASM("asm/nonmatchings/main_049", func_001F3700);

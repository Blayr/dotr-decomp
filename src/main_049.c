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

s32 func_001F1FD0(s32 arg0, void *arg1) {
    Obj_0031ABB0 *temp_v0;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    temp_v0 = D_0031ABB0[arg0];
    if (temp_v0 == NULL) {
        return 0;
    }
    if (arg1 != NULL) {
        *(Vec4f *)arg1 = *(Vec4f *)temp_v0;
    }
    return 1;
}

typedef struct {
    s8 unused0 : 5;
    s8 ready : 1;
    s8 unused1 : 2;
} Flags_001F2050;

static inline s32 check_001F2050(s32 index) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = D_0031ABB0[index];
    if (obj == NULL) {
        return 0;
    }
    if (*(s8 *)((u8 *)obj + 0x1F2) >= 0) {
        return 1;
    }
    return 0;
}

s32 func_001F2050(s32 index, void *out) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = D_0031ABB0[index];
    if (obj == NULL) {
        return 0;
    }
    if (check_001F2050(index) == 0) {
        return 0;
    }
    if ((s32)*(u8 *)((u8 *)obj + 0x1FE) <= 0) {
        return 0;
    }
    if (((Flags_001F2050 *)((u8 *)obj + 0x20C))->ready == 0) {
        return 0;
    }
    if (out != NULL) {
        *(Vec4f *)out = *(Vec4f *)((u8 *)obj + 0x80);
    }
    return 1;
}

static inline s32 ready_001F2150(s32 index) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = D_0031ABB0[index];
    if (obj == NULL) {
        return 0;
    }
    if (*(s8 *)((u8 *)obj + 0x1F2) >= 0) {
        return 1;
    }
    return 0;
}

s32 func_001F2150(s32 arg0, f32 *arg1) {
    s32 sp3C;
    Obj_0031ABB0 *temp_s1;
    f32 temp_f1;
    s32 temp_a1;
    s32 temp_a1_2;
    s32 var_v0_2;

    if ((arg0 < 0) || (temp_a1 = arg0 < 0x54, (temp_a1 == 0))) {
        return 0;
    }
    temp_s1 = D_0031ABB0[arg0];
    if (temp_s1 == NULL) {
        return 0;
    }
    if (ready_001F2150(arg0) == 0) {
        return 0;
    }
    if ((s32)*(u8 *)((u8 *)temp_s1 + 0x1FE) <= 0) {
        return 0;
    }
    sp3C = 0;
    if ((arg0 < 0) || (arg0 >= 0x54)) {
        var_v0_2 = 0;
    } else if (temp_s1 == NULL) {
        var_v0_2 = 0;
    } else {
        temp_a1_2 = *(s32 *)((u8 *)temp_s1 + 0x134);
        var_v0_2 = func_001EFBD0(1, temp_a1_2, temp_a1_2, &sp3C, 0, NULL, 0);
    }
    if (var_v0_2 != 0) {
        temp_f1 = *(f32 *)(*(u8 **)((u8 *)temp_s1 + 0x13C) + 0x54);
        arg1[0] = *(f32 *)((u8 *)var_v0_2 + 0x20) / temp_f1;
        arg1[1] = *(f32 *)((u8 *)var_v0_2 + 0x24) / temp_f1;
        arg1[2] = *(f32 *)((u8 *)var_v0_2 + 0x28) / temp_f1;
        arg1[3] = 1.0f;
    }
    return 1;
}

s32 func_001F22B0(s32 index, void *src) {
    Obj_0031ABB0 *dst;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    dst = D_0031ABB0[index];
    if (dst == NULL) {
        return 0;
    }
    if (src != NULL) {
        *(Vec4f *)dst = *(Vec4f *)src;
    }
    return 1;
}

s32 func_001F2330(s32 arg0, void *arg1) {
    s32 result;
    Obj_0031ABB0 *temp_v0;

    if (arg0 < 0 || arg0 >= 0x54) {
        result = 0;
    } else {
        temp_v0 = D_0031ABB0[arg0];
        if (temp_v0 == NULL) {
            result = 0;
        } else {
            if (arg1 != NULL) {
                *(Vec4f *)arg1 = *(Vec4f *)((u8 *)temp_v0 + 0x10);
            }
            result = 1;
        }
    }
    return result;
}

s32 func_001F23B0(s32 arg0, void *arg1) {
    Obj_0031ABB0 *temp_v0;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    temp_v0 = D_0031ABB0[arg0];
    if (temp_v0 == NULL) {
        return 0;
    }
    if (arg1 != NULL) {
        *(Vec4f *)arg1 = *(Vec4f *)((u8 *)temp_v0 + 0x20);
    }
    return 1;
}

typedef struct {
    f32 x, y, z, w;
} Vec4_001F2430;

/* needs shared field: D_0031ABB0 +0x10 f32[4] */

s32 func_001F2430(s32 arg0, void *arg1) {
    Obj_0031ABB0 *obj;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    obj = D_0031ABB0[arg0];
    if (obj == NULL) {
        return 0;
    }
    if (arg1 != NULL) {
        *(Vec4_001F2430 *)((u8 *)obj + 0x10) = *(Vec4_001F2430 *)arg1;
    } else {
        *(f32 *)((u8 *)obj + 0x10) = 0.0f;
        *(f32 *)((u8 *)obj + 0x14) = 0.0f;
        *(f32 *)((u8 *)obj + 0x18) = 0.0f;
        *(f32 *)((u8 *)obj + 0x1C) = 0.0f;
    }
    return 1;
}

s32 func_001F24C0(s32 index, void *src) {
    Obj_0031ABB0 *obj;

    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = D_0031ABB0[index];
    if (obj == NULL) {
        return 0;
    }
    if (src != NULL) {
        *(Vec4f *)((u8 *)obj + 0x20) = *(Vec4f *)src;
    } else {
        ((Vec4f *)((u8 *)obj + 0x20))->x = 0.0f;
        ((Vec4f *)((u8 *)obj + 0x20))->y = 0.0f;
        ((Vec4f *)((u8 *)obj + 0x20))->z = 0.0f;
        ((Vec4f *)((u8 *)obj + 0x20))->w = 0.0f;
    }
    return 1;
}

s32 func_001F2550(s32 arg0, void *arg1) {
    Obj_0031ABB0 *temp_v0;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    temp_v0 = D_0031ABB0[arg0];
    if (temp_v0 == NULL) {
        return 0;
    }
    if (arg1 != NULL) {
        *(Vec4f *)arg1 = temp_v0->v;
    }
    return 1;
}

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

typedef struct {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} Color_001F2660;

s32 func_001F2660(s32 arg0, void *arg1) {
    Obj_0031ABB0 *obj;

    if (arg0 < 0 || arg0 >= 0x54) {
        return -1;
    }
    obj = D_0031ABB0[arg0];
    if (obj == NULL) {
        return -1;
    }
    if (arg1 != NULL) {
        *(Color_001F2660 *)arg1 = *(Color_001F2660 *)&obj->pad040[0xEC];
    }
    return *(u8 *)((u8 *)obj + 0x1F8) & 3;
}

typedef struct {
    u8 mode : 2;
    u8 reserved : 6;
} Flags_001F26E0;

typedef struct {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} Color_001F26E0;

s32 func_001F26E0(s32 arg0, s32 arg1, void *arg2) {
    Obj_0031ABB0 *obj;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    obj = D_0031ABB0[arg0];
    if (obj == NULL) {
        return 0;
    }
    if (arg1 >= 0 && arg1 < 4) {
        ((Flags_001F26E0 *)((u8 *)obj + 0x1F8))->mode = arg1;
    }
    if (arg2 != NULL) {
        *(Color_001F26E0 *)&obj->pad040[0xEC] = *(Color_001F26E0 *)arg2;
    } else {
        obj->pad040[0xEC] = obj->pad040[0xED] = obj->pad040[0xEE] = 0x80;
        obj->pad040[0xEF] = 0x80;
    }
    return 1;
}

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

typedef struct {
    u8 low : 2;
    u8 mode : 2;
    u8 high : 4;
} Flags_001F2860;

typedef struct {
    u8 r, g, b, a;
} Color_001F2860;

s32 func_001F2860(s32 arg0, s32 arg1, void *arg2) {
    Obj_0031ABB0 *temp_a3;

    if ((arg0 < 0) || (arg0 >= 0x54)) {
        return 0;
    }
    temp_a3 = D_0031ABB0[arg0];
    if (temp_a3 == NULL) {
        return 0;
    }
    if ((arg1 >= 0) && (arg1 < 4)) {
        ((Flags_001F2860 *)((u8 *)temp_a3 + 0x1F8))->mode = arg1;
    }
    if (arg2 != NULL) {
        *(Color_001F2860 *)&temp_a3->pad040[0xF0] = *(Color_001F2860 *)arg2;
    } else {
        temp_a3->pad040[0xF0] = temp_a3->pad040[0xF1] = temp_a3->pad040[0xF2] = 0;
        temp_a3->pad040[0xF3] = 0;
    }
    return 1;
}

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

typedef struct {
    s8 : 4;
    s8 active : 1;
    s8 : 3;
} Flags_001F2A70;

s32 func_001F2A70(s32 arg0) {
    Obj_0031ABB0 *temp_v0;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    temp_v0 = D_0031ABB0[arg0];
    if (temp_v0 == NULL) {
        return 0;
    }
    return ((Flags_001F2A70 *) ((u8 *) temp_v0 + 0x20C))->active ? 1 : 0;
}

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

static inline s32 check_001F2B30(s32 index) {
    if (index < 0 || index >= 0x54) {
        return 0;
    }
    if (D_0031ABB0[index] == NULL) {
        return 0;
    }
    if (*(s8 *)((u8 *)D_0031ABB0[index] + 0x1F2) >= 0) {
        return 1;
    }
    return 0;
}

s32 func_001F2B30(s32 index) {
    if (index < 0 || index >= 0x54) {
        return -1;
    }
    if (D_0031ABB0[index] == NULL) {
        return -1;
    }
    if (check_001F2B30(index)) {
        return *(u8 *)((u8 *)D_0031ABB0[index] + 0x1FE);
    }
    return -1;
}

s32 func_001F2BE0(s32 arg0, s32 arg1) {
    Obj_0031ABB0 *obj;

    if (arg0 < 0 || arg0 >= 0x54) {
        return -1;
    }
    obj = D_0031ABB0[arg0];
    if (obj == NULL) {
        return -1;
    }
    if (arg1 < 0 || arg1 >= 8) {
        return -1;
    }
    return *(u16 *)((arg1 << 1) + (s32)obj + 0x1B0);
}

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

typedef struct {
    s8 reserved : 1;
    s8 enabled : 1;
} Flags_001F30B0;

s32 func_001F30B0(s32 arg0, s32 arg1) {
    Obj_0031ABB0 *obj;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }

    obj = D_0031ABB0[arg0];
    if (obj == NULL) {
        return 0;
    }

    ((Flags_001F30B0 *)((u8 *)obj + 0x20C))->enabled = (s8)arg1;
    return 1;
}

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

typedef struct {
    s8 : 6;
    s8 active : 1;
    s8 : 1;
} Flags_001F3210;

s32 func_001F3210(s32 arg0) {
    Obj_0031ABB0 *temp_v0;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    temp_v0 = D_0031ABB0[arg0];
    if (temp_v0 == NULL) {
        return 0;
    }
    return ((Flags_001F3210 *)((u8 *)temp_v0 + 0x20C))->active ? 1 : 0;
}

typedef struct {
    s8 : 7;
    s8 enabled : 1;
} Flags_001F3270;

s32 func_001F3270(s32 arg0, s64 arg1) {
    Obj_0031ABB0 *obj;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    obj = D_0031ABB0[arg0];
    if (obj == NULL) {
        return 0;
    }
    ((Flags_001F3270 *)((u8 *)obj + 0x20C))->enabled = (s8)arg1;
    return 1;
}

typedef struct {
    s8 enabled : 1;
} Flags_001F32F0;

s32 func_001F32F0(s32 arg0, s64 arg1) {
    Obj_0031ABB0 *temp_a2;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    temp_a2 = D_0031ABB0[arg0];
    if (temp_a2 == NULL) {
        return 0;
    }
    ((Flags_001F32F0 *)((u8 *)temp_a2 + 0x20D))->enabled = arg1;
    return 1;
}

typedef struct {
    s8 active : 1;
} Flags_001F3360;

s32 func_001F3360(s32 arg0) {
    Obj_0031ABB0 *temp_v0;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    temp_v0 = D_0031ABB0[arg0];
    if (temp_v0 == NULL) {
        return 0;
    }
    return ((Flags_001F3360 *)((u8 *)temp_v0 + 0x20D))->active ? 1 : 0;
}

typedef struct {
    s8 : 1;
    s8 enabled : 1;
} Flags_001F33C0;

s32 func_001F33C0(s32 arg0, s64 arg1) {
    Obj_0031ABB0 *temp_a2;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    temp_a2 = D_0031ABB0[arg0];
    if (temp_a2 == NULL) {
        return 0;
    }
    ((Flags_001F33C0 *)((u8 *)temp_a2 + 0x20D))->enabled = (s8)arg1;
    return 1;
}

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

typedef struct {
    s8 unused : 1;
    s8 active : 1;
} Flags_001F3690;

s32 func_001F3690(s32 arg0) {
    Obj_0031ABB0 *temp_v1;

    if (arg0 < 0 || arg0 >= 0x54) {
        return -1;
    }
    temp_v1 = D_0031ABB0[arg0];
    if (temp_v1 == NULL) {
        return -1;
    }
    if (((Flags_001F3690 *)((u8 *)temp_v1 + 0x20D))->active != 0) {
        return *(u8 *)((u8 *)temp_v1 + 0x200);
    }
    return -1;
}

typedef struct Table_001F3700 {
    s32 *values;
    s32 unused;
    s32 count;
} Table_001F3700;

void func_001F3790(void);
void func_001F6CE0(s32);
void func_001F6CF0(s32);
extern Table_001F3700 D_00292FF0[3];
extern s8 D_0031BB50;

void func_001F3700(void) {
    s32 i;
    s32 *values;
    s32 *count;
    Table_001F3700 *table;

    table = D_00292FF0;
    i = 0;
    do {
        values = table->values;
        count = &table->count;
        table->count = 0;
        while (*values++ != 0) {
            (*count)++;
        }
        i++;
        table++;
    } while (i < 3);
    func_0020B3C0(&D_0031BB50, 0, 0x354);
    func_001F3790();
    func_001F6CE0(0x80);
    func_001F6CF0(0x80);
    func_001F6D00(0x80);
}

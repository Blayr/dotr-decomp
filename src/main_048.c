#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_048", func_001ED460);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001ED4A0);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001EDA40);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001EDCB0);

typedef struct Entry_001EDF20 {
    u8 padding[0x68];
    s32 id : 27;
    u32 flags : 5;
    u32 padding_6C;
} Entry_001EDF20;

extern Entry_001EDF20 D_0031AD70[];

void func_001EDF20(s32 arg0) {
    s32 var_a3;
    Entry_001EDF20 *var_t0;
    s32 temp_v1;

    var_a3 = 1;
    var_t0 = D_0031AD70;
    do {
        temp_v1 = var_t0->id;
        if (temp_v1 >= 0) {
            if (arg0 < 0 || temp_v1 == arg0) {
                var_t0->id = -1;
            }
        }
        var_a3 += 1;
        var_t0++;
    } while (var_a3 < 0x20);
}

void func_001EDF90(s32 arg0) {
    func_00209D30(func_001EDFD0(func_00209D20(), arg0));
}

INCLUDE_ASM("asm/nonmatchings/main_048", func_001EDFD0);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001EE4A0);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001EE4B0);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001EE570);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001EE6C0);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001EF8A0);

s32 func_001EFA80(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    s32 saved;

    saved = func_001F3210(arg1);
    func_001F3190(arg1, 0);
    arg0 = func_001EE4B0(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
    func_001F3190(arg1, saved);
    return arg0;
}

INCLUDE_ASM("asm/nonmatchings/main_048", func_001EFB40);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001EFBD0);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001EFD30);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001EFDC0);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001EFF70);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F0060);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F01A0);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F0390);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F0500);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F0760);

typedef struct {
    u8 pad00[0x14];
    ObjSlot_0031ABB0 *f14;
    u8 pad18[4];
    s32 f1C;
} Arg_001F0830;

void func_00214090(ObjSlot_0031ABB0 *);

void func_001F0830(void *arg0, s32 arg1) {
    Arg_001F0830 *a = (Arg_001F0830 *)arg0;
    s32 v;
    s32 idx;
    s32 sub;
    Obj_0031ABB0 *base;

    v = a->f1C;
    idx = v >> 8;
    sub = v & 0xFF;
    if (idx < 0 || idx >= 0x54) {
        return;
    }
    base = D_0031ABB0[idx];
    if (base != NULL && arg1 != 0) {
        base->slots[sub] = a->f14;
        func_00214090(base->slots[sub]);
        base->vals[sub] = base->slots[sub]->f14->f4;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F08D0);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F0C10);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F0CD0);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F0E50);

f32 func_001F0F40(s32 arg0) {
    Obj_0031ABB0 *temp_v0;

    if (arg0 < 0 || arg0 >= 0x54) {
        return -1.0f;
    }
    temp_v0 = D_0031ABB0[arg0];
    if (temp_v0 == NULL) {
        return -1.0f;
    }
    return *(f32 *)((u8 *)temp_v0 + 0x1E4);
}

u8 *func_001F0FA0(s32 arg0) {
    Obj_0031ABB0 *temp_v0;

    if (arg0 < 0 || arg0 >= 0x54) {
        return NULL;
    }
    temp_v0 = D_0031ABB0[arg0];
    if (temp_v0 == NULL) {
        return NULL;
    }
    return &temp_v0->pad040[0x104];
}

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F0FF0);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F1070);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F1130);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F11B0);

typedef struct {
    s8 : 2;
    s8 active : 1;
} Flags_001F1240;

s32 func_001F1240(s32 arg0) {
    Obj_0031ABB0 *obj;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    obj = D_0031ABB0[arg0];
    if (obj == NULL) {
        return 0;
    }
    return ((Flags_001F1240 *)((u8 *)obj + 0x20C))->active ? 1 : 0;
}

typedef struct {
    s8 : 3;
    s8 active : 1;
} Flags_001F12A0;

s32 func_001F12A0(s32 arg0) {
    Obj_0031ABB0 *temp_v0;
    s32 ret;

    if (arg0 < 0 || arg0 >= 0x54) {
        ret = 0;
    } else {
        temp_v0 = D_0031ABB0[arg0];
        if (temp_v0 == NULL) {
            ret = 0;
        } else {
            ret = ((Flags_001F12A0 *)((u8 *)temp_v0 + 0x20C))->active ? 1 : 0;
        }
    }
    return ret;
}

s32 func_001F1300(s32 arg0) {
    Obj_0031ABB0 *temp_v0;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }

    temp_v0 = D_0031ABB0[arg0];
    if (temp_v0 == NULL) {
        return 0;
    }
    if (*(s8 *)((u8 *)temp_v0 + 0x1F2) >= 0) {
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F1370);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F13F0);

s8 func_001F1400(s32 arg0, s32 arg1) {
    Obj_0031ABB0 *base;

    if (arg0 < 0 || arg0 >= 0x54) {
        return -1;
    }
    if (arg1 < 0 || arg1 >= 4) {
        return -1;
    }
    base = D_0031ABB0[arg0];
    if (base == NULL) {
        return -1;
    }
    return base->lv[arg1];
}

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F1480);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F1490);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F1550);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F1560);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F16B0);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F16C0);

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F1830);

s32 func_001F1940(s32 arg0, s8 arg1) {
    Obj_0031ABB0 *obj;

    if (arg0 < 0 || arg0 >= 0x54) {
        return 0;
    }
    obj = D_0031ABB0[arg0];
    if (obj == NULL) {
        return 0;
    }
    *(s8 *)((u8 *)obj + 0x1FD) = arg1;
    return 1;
}

typedef struct {
    s8 unused : 6;
    s8 value : 2;
} Flags_001F19A0;

s64 func_001F19A0(s32 arg0) {
    Obj_0031ABB0 *obj;

    if (arg0 < 0 || arg0 >= 0x54) {
        return -1;
    }
    obj = D_0031ABB0[arg0];
    if (obj == NULL) {
        return -1;
    }
    return ((Flags_001F19A0 *)((u8 *)obj + 0x1F7))->value;
}

INCLUDE_ASM("asm/nonmatchings/main_048", func_001F1A00);

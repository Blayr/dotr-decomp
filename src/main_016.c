#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_016", func_00169420);

INCLUDE_ASM("asm/nonmatchings/main_016", func_00169610);

INCLUDE_ASM("asm/nonmatchings/main_016", func_00169A10);

INCLUDE_ASM("asm/nonmatchings/main_016", func_00169FE0);

INCLUDE_ASM("asm/nonmatchings/main_016", func_0016A5C0);

INCLUDE_ASM("asm/nonmatchings/main_016", func_0016AE30);

INCLUDE_ASM("asm/nonmatchings/main_016", func_0016AFE0);

s32 func_0016B0E0(void) {
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_016", func_0016B0F0);

INCLUDE_ASM("asm/nonmatchings/main_016", func_0016B1F0);

INCLUDE_ASM("asm/nonmatchings/main_016", func_0016B3C0);

INCLUDE_ASM("asm/nonmatchings/main_016", func_0016B610);

INCLUDE_ASM("asm/nonmatchings/main_016", func_0016C6B0);

INCLUDE_ASM("asm/nonmatchings/main_016", func_0016C8F0);

INCLUDE_ASM("asm/nonmatchings/main_016", func_0016CBB0);

INCLUDE_ASM("asm/nonmatchings/main_016", func_0016CE00);

INCLUDE_ASM("asm/nonmatchings/main_016", func_0016CF10);

INCLUDE_ASM("asm/nonmatchings/main_016", func_0016CF30);

INCLUDE_ASM("asm/nonmatchings/main_016", func_0016CFF0);

INCLUDE_ASM("asm/nonmatchings/main_016", func_0016D140);

INCLUDE_ASM("asm/nonmatchings/main_016", func_0016D6A0);

INCLUDE_ASM("asm/nonmatchings/main_016", func_0016D8C0);

INCLUDE_ASM("asm/nonmatchings/main_016", func_0016DCA0);

INCLUDE_ASM("asm/nonmatchings/main_016", func_0016DDA0);

s32 func_0016E000(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_s2;
    s32 temp_v0;
    s32 var_s3;
    s32 var_s4;
    s32 packed;

    if ((arg2 & 0xFF) == 1) {
        var_s4 = 3;
    } else {
        var_s4 = 4;
    }
    packed = (arg0 << 8) | arg1;
    var_s3 = 1;
    for (;;) {
        temp_v0 = func_001E3790(var_s3, var_s4);
        if (temp_v0 != 0) {
            if (temp_v0 == packed) {
                return 1;
            }
            temp_s2 = func_00250360(temp_v0 >> 8, temp_v0 & 0xFF);
            if (temp_s2 == func_00250360(arg0, arg1)) {
                return 0;
            }
        }
        var_s3++;
        if (var_s3 > 5) {
            break;
        }
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_016", func_0016E0E0);

void func_0016E4B0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28) {
    func_0027DE20(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
                  arg_sp0, arg_sp8, arg_sp10, arg_sp18, arg_sp20,
                  0, 2500, arg_sp28);
}

INCLUDE_ASM("asm/nonmatchings/main_016", func_0016E510);

INCLUDE_ASM("asm/nonmatchings/main_016", func_0016F240);

INCLUDE_ASM("asm/nonmatchings/main_016", func_0016F4D0);

INCLUDE_ASM("asm/nonmatchings/main_016", func_0016F760);

INCLUDE_ASM("asm/nonmatchings/main_016", func_0016FC00);

INCLUDE_ASM("asm/nonmatchings/main_016", func_0016FCF0);

INCLUDE_ASM("asm/nonmatchings/main_016", func_0016FEF0);

INCLUDE_ASM("asm/nonmatchings/main_016", func_001700D0);

INCLUDE_ASM("asm/nonmatchings/main_016", func_001702B0);

void func_0026FD30(s32, s32 *);
s64 func_002493A0(s32);

typedef struct {
    u8 pad0[6];
    u8 slot[5];
} Obj1_001703E0;

typedef struct {
    u8 pad0[0x38];
    s16 f38;
    s16 f3A;
    u16 id;
} Obj2_001703E0;

s32 func_001703E0(s32 arg0, void *arg1, void *arg2) {
    Obj1_001703E0 *o1 = arg1;
    Obj2_001703E0 *o2 = arg2;
    s32 list[8];
    s32 i;
    u8 k;

    for (i = 0; i < 5; i++) {
        o1->slot[i] = 0xFF;
    }
    func_0026FD30(arg0, list);
    if (o2 == NULL) {
        return -1;
    }
    for (i = 0; i < func_0026FE20(arg0); i++) {
        if (i != o1->slot[0] && i != o1->slot[1]) {
            if (o2->id == list[i] && func_0026FB10(arg0, list[i]) == 1) {
                o1->slot[0] = i;
            }
        }
    }
    k = 1;
    if ((func_0026FCE0(list[o1->slot[0]]) >> 5) == 0) {
        for (i = 0; i < func_0026FE20(arg0); i++) {
            if (i != o1->slot[0] && i != o1->slot[1]) {
                if (func_00248F60(list[o1->slot[0]], list[i]) >= 0 && (func_0026FCE0(list[i]) >> 5) == 2) {
                    if (list[i] != 0x31B && list[i] != 0x31C) {
                        o1->slot[k] = i;
                        k++;
                        o2->f38 += (s16)func_002493A0(list[i]);
                        o2->f3A += (s16)func_002493A0(list[i]);
                    }
                }
            }
        }
    }
    return 1;
}

void func_00170610(void) {
    func_0024E410();
}

INCLUDE_ASM("asm/nonmatchings/main_016", func_00170620);

INCLUDE_ASM("asm/nonmatchings/main_016", func_00170940);

INCLUDE_ASM("asm/nonmatchings/main_016", func_00170F10);

INCLUDE_ASM("asm/nonmatchings/main_016", func_001714F0);

INCLUDE_ASM("asm/nonmatchings/main_016", func_00171D60);

INCLUDE_ASM("asm/nonmatchings/main_016", func_00172000);

INCLUDE_ASM("asm/nonmatchings/main_016", func_00172210);

s32 func_00172310(s32 arg0) {
    if (func_001DF470() > 0x4B0) {
        if (func_001E0150(arg0) >= 4) {
            return 0x3E8;
        } else {
            return 0x7D0;
        }
    } else {
        return 0x960;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_016", func_00172370);

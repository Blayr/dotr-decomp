#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_054", func_001FF250);

s32 func_001FF300(void) {
    s32 var_s0;

    var_s0 = 0;
loop_1:
    if (func_001FF360(var_s0, 1) != 0) {
        return 1;
    }
    var_s0 += 1;
    if (var_s0 >= 5) {
        return 0;
    }
    goto loop_1;
}

INCLUDE_ASM("asm/nonmatchings/main_054", func_001FF350);

INCLUDE_ASM("asm/nonmatchings/main_054", func_001FF360);

INCLUDE_ASM("asm/nonmatchings/main_054", func_001FF3D0);

INCLUDE_ASM("asm/nonmatchings/main_054", func_001FF420);

INCLUDE_ASM("asm/nonmatchings/main_054", func_001FF480);

INCLUDE_ASM("asm/nonmatchings/main_054", func_001FF9C0);

INCLUDE_ASM("asm/nonmatchings/main_054", func_001FFAC0);

INCLUDE_ASM("asm/nonmatchings/main_054", func_001FFC50);

INCLUDE_ASM("asm/nonmatchings/main_054", func_001FFCB0);

INCLUDE_ASM("asm/nonmatchings/main_054", func_001FFCC0);

INCLUDE_ASM("asm/nonmatchings/main_054", func_001FFD30);

INCLUDE_ASM("asm/nonmatchings/main_054", func_001FFE00);

typedef struct Flags_001FFF60 {
    s8 enabled : 1;
    s8 reserved : 7;
} Flags_001FFF60;

extern Flags_001FFF60 D_00322980;

void func_001FFF60(s32 arg0, s64 arg1) {
    D_00322980.enabled = (s8)arg1;
}

u8 *func_001FFF90(void) {
    u8 *ret;

    ret = func_00197548();
    if (ret == NULL) {
        ret = D_002D0655;
    }
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/main_054", func_001FFFC0);

INCLUDE_ASM("asm/nonmatchings/main_054", func_00200170);

s32 func_00200210(void) {
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_054", func_00200220);

INCLUDE_ASM("asm/nonmatchings/main_054", func_00200230);

void func_00200300(s8 *arg0) {
    s8 *var_a0;
    s32 temp_a1;

    var_a0 = arg0;
    while ((temp_a1 = *var_a0) != 0) {
        if ((temp_a1 >= 0x61) && (temp_a1 < 0x7B)) {
            *var_a0 = temp_a1 - 0x20;
        }
        var_a0 += 1;
    }
}

void func_00200350(void) {

}

INCLUDE_ASM("asm/nonmatchings/main_054", func_00200360);

INCLUDE_ASM("asm/nonmatchings/main_054", func_002003E0);

INCLUDE_ASM("asm/nonmatchings/main_054", func_002004C0);

INCLUDE_ASM("asm/nonmatchings/main_054", func_00200510);

typedef struct CallbackTable_00200680 {
    u8 pad[0x6680];
    void (*callback)(s32, void *);
} CallbackTable_00200680;

extern CallbackTable_00200680 D_0031C2F0;
extern s32 D_00322970;

void func_00200680(void *arg0) {
    CallbackTable_00200680 *table = &D_0031C2F0;

    if (D_00322970 != 0) {
        table->callback(*(s32 *)((u8 *)arg0 + 0x1C), table);
    }
}

INCLUDE_ASM("asm/nonmatchings/main_054", func_002006C0);

INCLUDE_ASM("asm/nonmatchings/main_054", func_002007D0);

INCLUDE_ASM("asm/nonmatchings/main_054", func_002008A0);

INCLUDE_ASM("asm/nonmatchings/main_054", func_00200930);

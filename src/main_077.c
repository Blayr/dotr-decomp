#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_077", func_0026EA80);

INCLUDE_ASM("asm/nonmatchings/main_077", func_0026EB10);

s32 func_0026EEA0(void *arg0, s32 arg1, s32 arg2) {
    ((s32 *)arg0)[0] = 0x96;
    ((s32 *)arg0)[1] = 0;
    ((s32 *)arg0)[2] = (arg1 << 8) | arg2;
    ((s32 *)arg0)[3] = 0;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_077", func_0026EED0);

INCLUDE_ASM("asm/nonmatchings/main_077", func_0026EFD0);

INCLUDE_ASM("asm/nonmatchings/main_077", func_0026F600);

INCLUDE_ASM("asm/nonmatchings/main_077", func_0026F690);

INCLUDE_ASM("asm/nonmatchings/main_077", func_0026FA70);

INCLUDE_ASM("asm/nonmatchings/main_077", func_0026FA80);

s32 func_0026FB10(s32 arg0, s32 arg1) {
    s32 temp_s0;

    temp_s0 = func_0026FA80(arg1, arg0);
    return (func_001DE5C0(arg0) < temp_s0) ? 0 : 1;
}

s32 func_0026FB60(s32 arg0, s32 arg1) {
    s32 temp_s0;

    temp_s0 = func_0026FA80(arg1 & 0xFFF, arg0);
    return (func_001DE5C0(arg0) < temp_s0) ? 0 : 1;
}

INCLUDE_ASM("asm/nonmatchings/main_077", func_0026FBB0);

s32 func_0026FC10(s32 arg0) {
    u8 *p;

    if (arg0 == 0x3E7) {
        return 0;
    }
    p = func_001DD0E0(arg0);
    if (p == NULL) {
        return 0;
    }
    if ((p[0] >> 5) == 0) {
        if (*(u16 *)(p + 4) == 0xFFFF) {
            return 2;
        }
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_077", func_0026FC90);

s32 func_0026FCE0(s32 arg0) {
    u8 *temp_v0;

    if (arg0 == 0x3E7) {
        return 0U;
    }
    temp_v0 = func_001DD0E0();
    if (temp_v0 == NULL) {
        return 0U;
    }
    return *temp_v0;
}

INCLUDE_ASM("asm/nonmatchings/main_077", func_0026FD30);

s32 func_0026FE20(s32 arg0) {
    s32 temp_s0;
    s32 var_v0;

    temp_s0 = func_001DF110();
    var_v0 = temp_s0 + func_001DE9C0(arg0);
    if (var_v0 >= 5) {
        var_v0 = 5;
    }
    return var_v0;
}

INCLUDE_ASM("asm/nonmatchings/main_077", func_0026FE70);

INCLUDE_ASM("asm/nonmatchings/main_077", func_00270030);

INCLUDE_ASM("asm/nonmatchings/main_077", func_00270260);

INCLUDE_ASM("asm/nonmatchings/main_077", func_00270C30);

INCLUDE_ASM("asm/nonmatchings/main_077", func_00271630);

s32 func_00271740(s32 arg0, s32 arg1) {
    if (func_00266F70(0x58, (arg1 == 0) ? 1 : 0) > 0) {
        return 0;
    }
    return func_001E0C00(arg1, 0, arg0, 0);
}

INCLUDE_ASM("asm/nonmatchings/main_077", func_002717A0);

INCLUDE_ASM("asm/nonmatchings/main_077", func_00271830);

INCLUDE_ASM("asm/nonmatchings/main_077", func_00271950);

INCLUDE_ASM("asm/nonmatchings/main_077", func_00271A40);

INCLUDE_ASM("asm/nonmatchings/main_077", func_00271AF0);

INCLUDE_ASM("asm/nonmatchings/main_077", func_00271C90);

INCLUDE_ASM("asm/nonmatchings/main_077", func_00271E40);

INCLUDE_ASM("asm/nonmatchings/main_077", func_00271F00);

INCLUDE_ASM("asm/nonmatchings/main_077", func_00271F90);

INCLUDE_ASM("asm/nonmatchings/main_077", func_00272050);

INCLUDE_ASM("asm/nonmatchings/main_077", func_002720F0);

INCLUDE_ASM("asm/nonmatchings/main_077", func_00272210);

INCLUDE_ASM("asm/nonmatchings/main_077", func_00272330);

INCLUDE_ASM("asm/nonmatchings/main_077", func_002724C0);

INCLUDE_ASM("asm/nonmatchings/main_077", func_002724F0);

INCLUDE_ASM("asm/nonmatchings/main_077", func_00272CC0);

INCLUDE_ASM("asm/nonmatchings/main_077", func_00273460);

INCLUDE_ASM("asm/nonmatchings/main_077", func_002738B0);

INCLUDE_ASM("asm/nonmatchings/main_077", func_00273E60);

INCLUDE_ASM("asm/nonmatchings/main_077", func_002747A0);

INCLUDE_ASM("asm/nonmatchings/main_077", func_002755D0);

INCLUDE_ASM("asm/nonmatchings/main_077", func_00275740);

INCLUDE_ASM("asm/nonmatchings/main_077", func_002759D0);

INCLUDE_ASM("asm/nonmatchings/main_077", func_00275D00);

INCLUDE_ASM("asm/nonmatchings/main_077", func_00275E30);

INCLUDE_ASM("asm/nonmatchings/main_077", func_00275E80);

INCLUDE_ASM("asm/nonmatchings/main_077", func_002760E0);

#include "common.h"

s32 func_0026EA80(s32 arg0, s32 arg1) {
    s32 temp_s0;
    u8 *temp_v0;
    u8 temp_s1;

    temp_v0 = func_001DD0E0(arg1);
    if (temp_v0 == NULL) {
        return 0;
    }
    temp_s1 = *temp_v0;
    temp_s0 = temp_s1 & 0x1F;
    if (temp_s0 == (func_001E0700(arg0, 0) & 0x1F)) {
        if (((s32) temp_s1 >> 5) == 0) {
            return func_00271830(arg0);
        }
    }
    return 0;
}

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

typedef struct {
    u8 flags;
    u8 pad;
    u8 unused : 4;
    u8 value : 4;
} Flags_0026FA80;

s32 func_00271830(s32);

s32 func_0026FA80(s32 arg0, s32 arg1) {
    s32 owner;
    s32 value;
    Flags_0026FA80 *data;

    data = (Flags_0026FA80 *)func_001DD0E0(arg0);
    if (data == NULL) {
        return 0xFF;
    }
    value = data->value;
    if ((data->flags >> 5) == 0) {
        owner = data->flags & 0x1F;
        if (owner == (func_001E0700(arg1, 0) & 0x1F)) {
            value -= func_00271830(arg1);
        }
    }
    return value;
}

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

void *func_0026FC90(s32 arg0, s32 arg1) {
    u8 data[0x60];

    if (arg0 == 0x3E7) {
        return NULL;
    }
    func_001DCD70(data, arg0);
    return data + 8 + arg1 * 8;
}

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

s32 func_002717A0(s32 arg0) {
    s32 ret;

    switch (arg0) {
    case 1:
    case 7:
        ret = 5;
        break;
    case 9:
        ret = 0;
        break;
    case 10:
        ret = 1;
        break;
    case 16:
        ret = 4;
        break;
    case 20:
        ret = 9;
        break;
    default:
        ret = 7;
        break;
    }

    return ret;
}

INCLUDE_ASM("asm/nonmatchings/main_077", func_00271830);

INCLUDE_ASM("asm/nonmatchings/main_077", func_00271950);

s32 func_00271A40(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_s0;

    temp_s0 = func_001E1090(arg0, 0);
    if (func_00271740(9, arg0) != 0) {
        return (func_00271950(temp_s0 & 0xFF, temp_s0 >> 8, arg1, arg2, 5) != 0) ? 1 : 0;
    } else {
        return (func_00271950(temp_s0 & 0xFF, temp_s0 >> 8, arg1, arg2, 3) != 0) ? 1 : 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_077", func_00271AF0);

INCLUDE_ASM("asm/nonmatchings/main_077", func_00271C90);

INCLUDE_ASM("asm/nonmatchings/main_077", func_00271E40);

INCLUDE_ASM("asm/nonmatchings/main_077", func_00271F00);

INCLUDE_ASM("asm/nonmatchings/main_077", func_00271F90);

INCLUDE_ASM("asm/nonmatchings/main_077", func_00272050);

INCLUDE_ASM("asm/nonmatchings/main_077", func_002720F0);

INCLUDE_ASM("asm/nonmatchings/main_077", func_00272210);

INCLUDE_ASM("asm/nonmatchings/main_077", func_00272330);

s32 func_002724C0(s32 arg0) {
    return func_00271740(9, arg0) ? 5 : 3;
}

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

s32 func_00275E30(void *arg0) {
    if (func_0027F830(func_001DE540()) == 1) {
        return 1;
    }
    *(s16 *)((u8 *)arg0 + 0x1A2) = 0;
    return func_00275E80(arg0);
}

INCLUDE_ASM("asm/nonmatchings/main_077", func_00275E80);

s32 func_002760E0(u16 value, u16 *entries) {
    s32 i = 0;

    do {
        if (value == *entries) {
            return 1;
        }
        i++;
        entries += 8;
    } while (i < 22);

    return 0;
}

#include "common.h"

s32 func_00193D18(s32 arg0) {
    u8 *b_D_00315C40;
    s32 temp_v0;

    if (func_0017B930(D_0028F794) < 0) {
        return -0xC8;
    }
    b_D_00315C40 = (u8 *)&D_00315C40;
    if ((*(s32 *)(b_D_00315C40 + 0x24)) == 0) {
        func_0017B900(D_0028F794);
        return -0x64;
    }
    D_00315CC0 = arg0;
    temp_v0 = func_0017EA80((void *)b_D_00315C40, 3, 1, &D_00315CC0, 0x30, &D_00317200, 4, 0, 0);
    if (temp_v0 == 0) {
        D_0028F790 = 3;
    } else {
        func_0017B900(D_0028F794);
    }
    return temp_v0;
}

s32 func_00193DD0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 *b_D_00315C40;
    s32 temp_v0;

    if (func_0017B930(D_0028F794) < 0) {
        return -0xC8;
    }
    b_D_00315C40 = (u8 *)&D_00315C40;
    if ((*(s32 *)(b_D_00315C40 + 0x24)) == 0) {
        func_0017B900(D_0028F794);
        return -0x64;
    }
    (*(s32 *)(&D_00315CC0)) = arg0;
    (*(s32 *)((u8 *)(&D_00315CC0) + 0x10)) = arg1;
    (*(s32 *)((u8 *)(&D_00315CC0) + 0x14)) = arg2;
    temp_v0 = func_0017EA80((void *)b_D_00315C40, 4, 1, &D_00315CC0, 0x30, &D_00317200, 4, 0, 0);
    if (temp_v0 == 0) {
        D_0028F790 = 4;
    } else {
        func_0017B900(D_0028F794);
    }
    return temp_v0;
}

INCLUDE_ASM("asm/nonmatchings/main_033", func_00193EA8);

s32 func_00193F38(s32 arg0, s32 *arg1, s32 arg2) {
    u8 *b_D_00315C40;
    s32 temp_v0;

    if (func_0017B930(D_0028F794) < 0) {
        return -0xC8;
    }
    b_D_00315C40 = (u8 *)&D_00315C40;
    if ((*(s32 *)(b_D_00315C40 + 0x24)) == 0) {
        func_0017B900(D_0028F794);
        return -0x64;
    }
    (*(s32 *)(&D_00315CC0)) = arg0;
    (*(s32 **)((u8 *)(&D_00315CC0) + 0x1C)) = &D_00316140;
    (*(s32 **)((u8 *)(&D_00315CC0) + 0x18)) = arg1;
    (*(s32 *)((u8 *)(&D_00315CC0) + 0xC)) = arg2;
    func_0017E190(arg1, arg2);
    func_0017E190(&D_00316140, 0xC0);
    temp_v0 = func_0017EA80((void *)b_D_00315C40, 5, 1, &D_00315CC0, 0x30, &D_00317200, 4, (s32) &func_00193EA8, (s32) &D_00316140);
    if (temp_v0 == 0) {
        D_0028F790 = 5;
    } else {
        func_0017B900(D_0028F794);
    }
    return temp_v0;
}

typedef struct McWriteDesc_00194058 {
    s32 fd;
    s32 unk4;
    s32 unk8;
    s32 rest;
    s32 unk10;
    s32 size;
    s32 origin;
    s32 unk1C;
    u8 data[16];
} McWriteDesc_00194058;

s32 func_00194058(s32 arg0, void *arg1, s32 arg2) {

    u8 *p;
    u32 i;
    u32 t;
    s32 ret;

    if (func_0017B930(D_0028F794) < 0) {
        return -0xC8;
    }
    p = (u8 *)&D_00315C40;
    if ((*(s32 *)(p + 0x24)) == 0) {
        func_0017B900(D_0028F794);
        return -0x64;
    }

    (*(McWriteDesc_00194058 *)&D_00315CC0).fd = arg0;
    if (arg2 < 0x11) {
        (*(McWriteDesc_00194058 *)&D_00315CC0).size = arg2;
        (*(McWriteDesc_00194058 *)&D_00315CC0).rest = 0;
        (*(McWriteDesc_00194058 *)&D_00315CC0).origin = 0;
    } else {
        t = (u32)arg1 - 0x10;
        (*(McWriteDesc_00194058 *)&D_00315CC0).size = (((u32)arg1 - 1) & 0xFFFFFFF0) - t;
        (*(McWriteDesc_00194058 *)&D_00315CC0).rest = arg2 - (*(McWriteDesc_00194058 *)&D_00315CC0).size;
        (*(McWriteDesc_00194058 *)&D_00315CC0).origin = (u32)arg1 + (*(McWriteDesc_00194058 *)&D_00315CC0).size;
    }
    for (i = 0; i < (*(McWriteDesc_00194058 *)&D_00315CC0).size; i++) {
        (*(McWriteDesc_00194058 *)&D_00315CC0).data[i] = ((u8 *)arg1)[i];
    }
    func_0017BB60(0);
    ret = func_0017EA80(&D_00315C40, 6, 1, &D_00315CC0, 0x30, &D_00317200, 4, 0, 0);
    if (ret == 0) {
        D_0028F790 = 6;
    } else {
        func_0017B900(D_0028F794);
    }
    return ret;
}

void func_001941D8(s32 arg0, s32 arg1, s32 arg2) {
    func_0017C8D0(arg2);
    __asm__ volatile("sync");
    __asm__ volatile("ei");
}

void func_00194200(s32 arg0) {
    func_0017B660(arg0 & 0xFFFF, &func_001941D8, func_0017B7D0());
    func_0017B800();
}

s32 func_00194248(s32 arg0, s32 *arg1, s32 *arg2) {
    s32 ret;

    if (D_0028F790 == 0) {
        return -1;
    }
    ret = func_0017EC70(&D_00315C40);
    if (arg0 == 0 && ret != 0) {
        while (func_0017EC70(&D_00315C40) != 0) {
            func_00194200(0x3C);
        }
        ret = 0;
    }
    ret = ret == 0;
    if (arg1 != NULL) {
        *arg1 = D_0028F790;
    }
    if (ret != 0) {
        D_0028F790 = 0;
        if (arg2 != NULL) {
            *arg2 = D_00317200;
        }
        func_0017B900(D_0028F794);
    }
    return ret;
}

void func_00194328(s32 arg0) {
    s32 temp_a0;

    temp_a0 = arg0 | 0x20000000;
    if (D_00315C68 != NULL) {
        *D_00315C68 = (*(s32 *)temp_a0);
    }
    if (D_00315C6C != NULL) {
        *D_00315C6C = (*(s32 *)((u8 *)temp_a0 + 4));
    }
    if (D_00315C70 != NULL) {
        *D_00315C70 = (*(s32 *)((u8 *)temp_a0 + 0x90));
    }
}

INCLUDE_ASM("asm/nonmatchings/main_033", func_00194380);

s32 func_00194508(void) {
    if (func_0017EA80(&D_00315C40, 0x35, 0, &D_00315CC0, 0x30, &D_00317200, 4, 0, 0) != 0) {
        func_00199B50(&D_002BD0A0);
        return -1;
    }
    return D_00317200;
}

s32 func_00194578(s32 arg0, s32 arg1, void *arg2, u32 arg3, s32 arg4, void *arg5) {
    u8 *b_D_00315C40;
    s32 temp_v0;

    if (func_0017B930(D_0028F794) < 0) {
        return -0xC8;
    }
    b_D_00315C40 = (u8 *)&D_00315C40;
    if ((*(s32 *)(b_D_00315C40 + 0x24)) == 0) {
        func_0017B900(D_0028F794);
        return -0x64;
    }
    if ((arg2 == NULL) || (*(s8 *)arg2 == 0)) {
        func_0017B900(D_0028F794);
        return -0xD2;
    }
    (*(s32 *)(&D_00315CF0)) = arg0;
    (*(s32 *)((u8 *)(&D_00315CF0) + 4)) = arg1;
    (*(s32 *)((u8 *)(&D_00315CF0) + 8)) = arg3;
    (*(s32 *)((u8 *)(&D_00315CF0) + 0xC)) = arg4;
    (*(s32 *)((u8 *)(&D_00315CF0) + 0x10)) = (s32) arg5;
    func_0019C2B8((u8 *)&D_00315CF0 + 0x14, arg2, 0x3FFU);
    (*(s8 *)((u8 *)(&D_00315CF0) + 0x413)) = 0;
    if (arg4 >= 0) {
        func_0017E190(arg5, arg4 << 6);
    }
    temp_v0 = func_0017EA80((void *)b_D_00315C40, 0xD, 1, &D_00315CF0, 0x414, &D_00317200, 4, 0, 0);
    if (temp_v0 == 0) {
        D_0028F790 = 0xD;
    } else {
        func_0017B900(D_0028F794);
    }
    return temp_v0;
}

void func_001946D0(void *arg0) {
    s32 temp_s0;
    s32 var_s0;

    if (arg0 != NULL) {
        temp_s0 = (s32) &D_00316200 | 0x20000000;
        if (func_0019BEF0((s8 *) temp_s0) < 0x400U) {
            var_s0 = func_0019BEF0((s8 *) temp_s0);
        } else {
            var_s0 = 0x3FF;
        }
        func_00198790(arg0, (void *) ((s32) &D_00316200 | 0x20000000), var_s0);
        *(s8 *)(arg0 + var_s0) = 0;
    }
}

s32 func_00194758(s32 arg0, s32 arg1, void *arg2, void *arg3) {
    u8 *b_D_00315C40;
    s32 temp_v0;

    if (func_0017B930(D_0028F794) < 0) {
        return -0xC8;
    }
    b_D_00315C40 = (u8 *)&D_00315C40;
    if ((*(s32 *)(b_D_00315C40 + 0x24)) == 0) {
        func_0017B900(D_0028F794);
        return -0x64;
    }
    if ((arg2 == NULL) || (*(s8 *)arg2 == 0)) {
        func_0017B900(D_0028F794);
        return -0xD2;
    }
    (*(s32 *)(&D_00315CF0)) = arg0;
    (*(s32 **)((u8 *)(&D_00315CF0) + 0x10)) = &D_00316200;
    (*(s32 *)((u8 *)(&D_00315CF0) + 4)) = arg1;
    func_0019C2B8((u8 *)&D_00315CF0 + 0x14, arg2, 0x3FFU);
    (*(s8 *)((u8 *)(&D_00315CF0) + 0x413)) = 0;
    func_0017E190(&D_00316200, 0x400);
    temp_v0 = func_0017EA80((void *)b_D_00315C40, 0xC, 1, &D_00315CF0, 0x414, &D_00317200, 4, (s32) func_001946D0, (s32) arg3);
    if (temp_v0 == 0) {
        D_0028F790 = 0xC;
    } else {
        func_0017B900(D_0028F794);
    }
    return temp_v0;
}

s32 func_001948A8(s32 arg0, s32 arg1) {
    u8 *b_D_00315CC0;
    u8 *b_D_00315C40;
    s32 temp_v0;

    if (func_0017B930(D_0028F794) < 0) {
        return -0xC8;
    }
    b_D_00315C40 = (u8 *)&D_00315C40;
    if ((*(s32 *)(b_D_00315C40 + 0x24)) == 0) {
        func_0017B900(D_0028F794);
        return -0x64;
    }
    b_D_00315CC0 = (u8 *)&D_00315CC0;
    (*(s32 *)(b_D_00315CC0 + 8)) = arg1;
    (*(s32 *)(b_D_00315CC0 + 4)) = arg0;
    temp_v0 = func_0017EA80((void *)b_D_00315C40, 0x10, 1, (void *)b_D_00315CC0, 0x30, &D_00317200, 4, 0, 0);
    if (temp_v0 == 0) {
        D_0028F790 = 0x10;
    } else {
        func_0017B900(D_0028F794);
    }
    return temp_v0;
}

s32 func_00194970(s32 arg0, s32 arg1, s8 *arg2) {
    u8 *b_D_00315C40;
    u8 *b_D_00315D04;
    s32 *temp_v1;
    s32 temp_v0;

    if (func_0017B930(D_0028F794) < 0) {
        return -0xC8;
    }
    b_D_00315C40 = (u8 *)&D_00315C40;
    if ((*(s32 *)(b_D_00315C40 + 0x24)) == 0) {
        func_0017B900(D_0028F794);
        return -0x64;
    }
    if ((arg2 == NULL) || (*arg2 == 0)) {
        func_0017B900(D_0028F794);
        return -0xD2;
    }
    b_D_00315D04 = (u8 *)&D_00315D04;
    func_0019C2B8((void *)b_D_00315D04, arg2, 0x3FFU);
    temp_v1 = (void *)b_D_00315D04 - 0x14;
    (*(s32 *)(b_D_00315D04 + -0x14)) = arg0;
    (*(s32 *)((u8 *)temp_v1 + 4)) = arg1;
    (*(s8 *)((u8 *)temp_v1 + 0x413)) = 0;
    (*(s32 *)((u8 *)temp_v1 + 8)) = 0;
    temp_v0 = func_0017EA80((void *)b_D_00315C40, 0xF, 1, temp_v1, 0x414, &D_00317200, 4, 0, 0);
    if (temp_v0 == 0) {
        D_0028F790 = 0xF;
    } else {
        func_0017B900(D_0028F794);
    }
    return temp_v0;
}

s32 func_00194A98(s32 arg0) {
    u8 *b_D_00315C40;
    s32 temp_v0;

    if (func_0017B930(D_0028F794) < 0) {
        return -0xC8;
    }
    b_D_00315C40 = (u8 *)&D_00315C40;
    if ((*(s32 *)(b_D_00315C40 + 0x24)) == 0) {
        func_0017B900(D_0028F794);
        return -0x64;
    }
    D_00315CC0 = arg0;
    temp_v0 = func_0017EA80((void *)b_D_00315C40, 0xA, 1, &D_00315CC0, 0x30, &D_00317200, 4, 0, 0);
    if (temp_v0 == 0) {
        D_0028F790 = 0xA;
    } else {
        func_0017B900(D_0028F794);
    }
    return temp_v0;
}

INCLUDE_ASM("asm/nonmatchings/main_033", func_00194B50);

s32 func_00194D28(s32 arg0, s32 arg1, s8 *arg2, void *arg3) {
    s32 temp_v0;
    void *temp_s0;
    s32 *p;

    if (func_0017B930(D_0028F794) < 0) {
        return -0xC8;
    }
    p = (s32 *)&D_00315C40;
    if (p[9] == 0) {
        func_0017B900(D_0028F794);
        return -0x64;
    }
    if ((arg2 == NULL) || (*arg2 == 0) || (arg3 == NULL)) {
        func_0017B900(D_0028F794);
        return -0xD2;
    }
    (*(s32 *)(&D_00315CF0)) = arg0;
    (*(s32 *)((u8 *)(&D_00315CF0) + 4)) = arg1;
    (*(s32 *)((u8 *)(&D_00315CF0) + 8)) = 0x10;
    func_0019C2B8((u8 *)&D_00315CF0 + 0x14, arg2, 0x3FFU);
    (*(s8 *)((u8 *)(&D_00315CF0) + 0x413)) = 0;
    func_0019C2B8(&D_00315CA0, arg3, 0x20U);
    temp_s0 = (u8 *)&D_00315CA0 - 0x20;
    (*(s8 *)((u8 *)temp_s0 + 0x3F)) = 0;
    (*(void **)((u8 *)(&D_00315CF0) + 0x10)) = temp_s0;
    func_0017BB60(0);
    temp_v0 = func_0017EA80(p, 0xE, 1, &D_00315CF0, 0x414, &D_00317200, 4, 0, 0);
    if (temp_v0 == 0) {
        D_0028F790 = 0x13;
    } else {
        func_0017B900(D_0028F794);
    }
    return temp_v0;
}

s32 func_00194E90(s32 arg0, s32 arg1) {
    u8 *b_D_00315CC0;
    u8 *b_D_00315C40;
    s32 temp_v0;

    if (func_0017B930(D_0028F794) < 0) {
        return -0xC8;
    }
    b_D_00315C40 = (u8 *)&D_00315C40;
    if ((*(s32 *)(b_D_00315C40 + 0x24)) == 0) {
        func_0017B900(D_0028F794);
        return -0x64;
    }
    b_D_00315CC0 = (u8 *)&D_00315CC0;
    (*(s32 *)(b_D_00315CC0 + 8)) = arg1;
    (*(s32 *)(b_D_00315CC0 + 4)) = arg0;
    temp_v0 = func_0017EA80((void *)b_D_00315C40, 0x11, 1, (void *)b_D_00315CC0, 0x30, &D_00317200, 4, 0, 0);
    if (temp_v0 == 0) {
        D_0028F790 = 0x11;
    } else {
        func_0017B900(D_0028F794);
    }
    return temp_v0;
}

s32 func_00194F58(s32 arg0, s32 arg1, s8 *arg2) {
    u8 *b_D_00315C40;
    s32 temp_v0;

    if (func_0017B930(D_0028F794) < 0) {
        return -0xC8;
    }
    b_D_00315C40 = (u8 *)&D_00315C40;
    if ((*(s32 *)(b_D_00315C40 + 0x24)) == 0) {
        func_0017B900(D_0028F794);
        return -0x64;
    }
    if ((arg2 == NULL) || (*arg2 == 0)) {
        func_0017B900(D_0028F794);
        return -0xD2;
    }
    (*(s32 *)(&D_00315CF0)) = arg0;
    (*(s32 *)((u8 *)(&D_00315CF0) + 4)) = arg1;
    func_0019C2B8((u8 *)&D_00315CF0 + 0x14, arg2, 0x3FFU);
    (*(s8 *)((u8 *)(&D_00315CF0) + 0x413)) = 0;
    temp_v0 = func_0017EA80((void *)b_D_00315C40, 0x12, 1, &D_00315CF0, 0x414, &D_00317200, 4, 0, 0);
    if (temp_v0 == 0) {
        D_0028F790 = 0x12;
    } else {
        func_0017B900(D_0028F794);
    }
    return temp_v0;
}

#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_030", func_0018DAA8);

s32 func_0018DB40(u64 *arg0, s32 arg1) {
    s32 temp_s2;

    temp_s2 = func_0018DA88(arg0, arg1);
    func_0018DAA8(arg0, arg1);
    return temp_s2;
}

s32 func_0018DB90(u64 *arg0) {
    s32 temp_s1;

    temp_s1 = func_0018DA88(arg0, 1);
    func_0018DAA8(arg0, 1);
    return temp_s1;
}

INCLUDE_ASM("asm/nonmatchings/main_030", func_0018DBD8);

u32 func_0018DC30(void *arg0, s32 arg1) {
    u32 var_v1;

    var_v1 = (*(s32 *)((u8 *)arg0 + 8)) + (arg1 >> 3);
    if (var_v1 >= (u32) (*(u32 *)((u8 *)arg0 + 0x24))) {
        var_v1 -= (*(s32 *)((u8 *)arg0 + 0x28));
    }
    return var_v1;
}

INCLUDE_ASM("asm/nonmatchings/main_030", func_0018DC60);

INCLUDE_ASM("asm/nonmatchings/main_030", func_0018DCE8);

INCLUDE_ASM("asm/nonmatchings/main_030", func_0018DEE8);

s32 func_0018E1E0(s32 arg0, s32 arg1, s32 arg2) {
    return func_0018DEE8(arg0, arg1, arg2, 0, -1);
}

INCLUDE_ASM("asm/nonmatchings/main_030", func_0018E200);

INCLUDE_ASM("asm/nonmatchings/main_030", func_0018E2F8);

INCLUDE_ASM("asm/nonmatchings/main_030", func_0018E448);

INCLUDE_ASM("asm/nonmatchings/main_030", func_0018E4B8);

void func_0018EA68(void) {
    func_001843E0();
    *(volatile s32 *)0x1000F590 = *(volatile s32 *)0x1000F520 | 0x10000;
    *(volatile s32 *)0x1000B000 &= 0xFFFFFEFF;
    *(volatile s32 *)0x1000B400 &= 0xFFFFFEFF;
    *(volatile s32 *)0x1000F590 = *(volatile s32 *)0x1000F520 & 0xFFFEFFFF;
    func_00184428();
    *(volatile s32 *)0x1000B020 = 0;
    *(volatile s32 *)0x1000B420 = 0;
    func_00190498();
}

INCLUDE_ASM("asm/nonmatchings/main_030", func_0018EB08);

s32 func_0018ED10(s32 unused0) {
    return 1;
}

void func_0018ED18(void *arg0, s32 arg1, s32 arg2) {
    func_0018F808(*(s32 *)((u8 *)arg0 + 0x40), arg1, (arg2 + 0x13) / 16 * 16);
}

INCLUDE_ASM("asm/nonmatchings/main_030", func_0018ED40);

INCLUDE_ASM("asm/nonmatchings/main_030", func_0018ED88);

INCLUDE_ASM("asm/nonmatchings/main_030", func_0018EDD0);

void func_0018EE20(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    void *temp_v0;

    temp_v0 = (*(void **)((u8 *)arg0 + 0x40));
    (*(s32 *)((u8 *)temp_v0 + 0x94)) = arg1;
    (*(s32 *)((u8 *)temp_v0 + 0x98)) = arg2;
    (*(s32 *)((u8 *)temp_v0 + 0x9C)) = arg3;
}

void func_0018EE38(void *arg0, s32 *arg1, s32 *arg2, s32 *arg3) {
    void *temp_t0;

    temp_t0 = (*(void **)((u8 *)arg0 + 0x40));
    *arg1 = (*(s32 *)((u8 *)temp_t0 + 0x94));
    *arg2 = (*(s32 *)((u8 *)temp_t0 + 0x98));
    *arg3 = (*(s32 *)((u8 *)temp_t0 + 0x9C));
}

s32 func_0018EE58(void *arg0) {
    return *(*(s32 **)((u8 *)arg0 + 0x40));
}

s32 func_0018EE68(void *arg0) {
    return (*(s32 *)((u8 *)((*(void **)((u8 *)arg0 + 0x40))) + 4)) == 0;
}

void func_0018EE78(void *arg0) {
    void *temp_s0;

    temp_s0 = (*(void **)((u8 *)arg0 + 0x40));
    (*(s32 *)temp_s0) = 0;
    (*(s32 *)((u8 *)temp_s0 + 4)) = 0;
    (*(s32 *)((u8 *)temp_s0 + 8)) = 0;
    (*(s32 *)((u8 *)arg0 + 8)) = 0;
    (*(s32 *)((u8 *)temp_s0 + 0xAC)) = 0;
    (*(s32 *)((u8 *)temp_s0 + 0x80)) = -1;
    func_0018F6A8(temp_s0);
    (*(s32 *)((u8 *)temp_s0 + 0x118)) = 0;
    func_0018F5B8(temp_s0);
}

s32 func_0018EEC8(void *arg0) {
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v0_3;
    void *temp_v0_4;
    void *temp_v0_5;
    void *temp_v0_6;
    void *temp_v1;

    temp_v1 = (*(void **)((u8 *)arg0 + 0x40));
    temp_v0 = (*(void **)((u8 *)temp_v1 + 0x1B8));
    if (temp_v0 != NULL) {
        (*(s32 *)((u8 *)temp_v0 + 0x28)) = 0;
    }
    temp_v0_2 = (*(void **)((u8 *)temp_v1 + 0x1C8));
    if (temp_v0_2 != NULL) {
        (*(s32 *)((u8 *)temp_v0_2 + 0x28)) = 0;
    }
    temp_v0_3 = (*(void **)((u8 *)temp_v1 + 0x1D8));
    if (temp_v0_3 != NULL) {
        (*(s32 *)((u8 *)temp_v0_3 + 0x28)) = 0;
    }
    temp_v0_4 = (*(void **)((u8 *)temp_v1 + 0x1BC));
    if (temp_v0_4 != NULL) {
        (*(s32 *)((u8 *)temp_v0_4 + 0x28)) = 0;
    }
    temp_v0_5 = (*(void **)((u8 *)temp_v1 + 0x1CC));
    if (temp_v0_5 != NULL) {
        (*(s32 *)((u8 *)temp_v0_5 + 0x28)) = 0;
    }
    temp_v0_6 = (*(void **)((u8 *)temp_v1 + 0x1DC));
    if (temp_v0_6 != NULL) {
        (*(s32 *)((u8 *)temp_v0_6 + 0x28)) = 0;
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_030", func_0018EF20);

INCLUDE_ASM("asm/nonmatchings/main_030", func_0018EF48);

void func_0018EF98(s32 arg0) {
    s32 sp0[8];
    sp0[0] = /* extra? */ 1;
    func_0018EF48(arg0, sp0);
}

void func_0018EFC0(void *arg0, s64 arg1) {
    void *temp_v0;

    temp_v0 = (*(void **)((u8 *)arg0 + 0x40));
    (*(s32 *)((u8 *)temp_v0 + 0x70)) = 1;
    (*(s64 *)((u8 *)temp_v0 + 0x78)) = arg1;
}

void func_0018EFD8(void *arg0) {
    u8 *p = *(u8 **)((u8 *)arg0 + 0x40);

    *(s32 *)(p + 0x70) = 0;
    *(s64 *)(p + 0x78) = 0;
}

void func_0018EFE8(void *arg0, s32 arg1) {
    (*(s32 *)((u8 *)((*(void **)((u8 *)arg0 + 0x40))) + 0xD8)) = arg1;
}

s32 func_0018EFF8(void *arg0) {
    return (*(s32 *)((u8 *)((*(void **)((u8 *)arg0 + 0x40))) + 0xCC));
}

s32 func_0018F008(void *arg0) {
    return (*(s32 *)((u8 *)((*(void **)((u8 *)arg0 + 0x40))) + 0xD0));
}

s32 func_0018F018(void *arg0) {
    return (*(s32 *)((u8 *)arg0 + 0x40)) + 0xB4;
}

s32 func_0018F028(void *arg0) {
    return (*(s32 *)((u8 *)arg0 + 0x40)) + 0xB4;
}

s32 func_0018F038(void *arg0, s32 arg1) {
    s32 temp_v0;
    void *temp_v1;

    temp_v1 = (*(void **)((u8 *)arg0 + 0x40));
    temp_v0 = (*(s32 *)((u8 *)temp_v1 + 0xE8));
    (*(s32 *)((u8 *)temp_v1 + 0xE8)) = arg1;
    return temp_v0;
}

void func_0018F048(void *arg0, s64 arg1) {
    void *temp_v1;

    temp_v1 = (*(void **)((u8 *)arg0 + 0x40));
    (*(s64 *)((u8 *)temp_v1 + 0xF0)) = arg1;
    (*(s32 *)((u8 *)temp_v1 + 0xF8)) = 1;
}

void func_0018F060(void *arg0, s32 arg1, s32 arg2) {
    (*(s32 *)((u8 *)arg0 + 4)) = arg2;
    (*(s32 *)arg0) = arg1;
    (*(s32 *)((u8 *)arg0 + 8)) = arg1;
    (*(s32 *)((u8 *)arg0 + 0xC)) = arg1;
}

void func_0018F078(void *arg0) {
    (*(s32 *)((u8 *)arg0 + 0xC)) = (s32) (*(s32 *)((u8 *)arg0 + 8));
}

void func_0018F088(void *arg0) {
    (*(s32 *)((u8 *)arg0 + 8)) = (s32) (*(s32 *)((u8 *)arg0 + 0xC));
}

s32 func_0018F098(s32 arg0, void *arg1, s32 arg2, u32 arg3) {
    s32 temp_v0;
    u32 temp_a0;

    temp_v0 = ((u32) (((*(u32 *)((u8 *)arg1 + 8)) + arg3) - 1) / arg3) * arg3;
    temp_a0 = temp_v0 + arg2;
    if ((u32) ((*(s32 *)arg1) + (*(s32 *)((u8 *)arg1 + 4))) >= temp_a0) {
        (*(u32 *)((u8 *)arg1 + 8)) = temp_a0;
        return temp_v0;
    }
    func_0018F7B0(arg0, &D_002BC9F8);
    return 0;
}

s32 func_0018F108(s32 *arg0) {
    return (arg0[0] + arg0[1]) - arg0[2];
}

s32 func_0018F120(void *arg0) {
    s32 *p;
    s32 ret;
    u32 st;

    st = 1;
    ret = 0;
    p = *(s32 **)((u8 *)arg0 + 0x40);
    p[0] = 0;
    if (p[0xD8 / 4] & 0x3F) {
        func_0018F778((s32)p, D_002BCA18, p[0xD8 / 4]);
        return -1;
    }
    p[0x820 / 4] = 0;
    do {
        if (ret != -1) {
            do {
                st = func_0018BC80(p);
            } while (st != 0 && p[0x174 / 4] != p[0xD4 / 4] && p[0x848 / 4] != 0);
        }
        switch (st) {
        case 0:
            func_0018F550(arg0);
            p[0] = 1;
            break;
        case 1:
            p[0xA8 / 4] = 0;
            p[0xA4 / 4] = 0;
            p[0xA0 / 4] = 0;
            ret = func_0018F3A8(arg0, 0, p[0x94 / 4]);
            p[0xA0 / 4]++;
            break;
        case 2:
            ret = func_0018F3A8(arg0, p[0xA4 / 4], p[0x98 / 4]);
            p[0xA4 / 4]++;
            break;
        case 3:
        case 4:
            ret = func_0018F3A8(arg0, p[0xA8 / 4], p[0x9C / 4]);
            p[0xA8 / 4]++;
            break;
        }
        if (p[0x820 / 4] != 0) {
            return 1;
        }
    } while (p[0] == 0);
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_030", func_0018F290);

INCLUDE_ASM("asm/nonmatchings/main_030", func_0018F3A8);

INCLUDE_ASM("asm/nonmatchings/main_030", func_0018F3F0);

s32 func_0018F550(void *arg0) {
    s32 var_a0;
    void *temp_s0;

    temp_s0 = (*(void **)((u8 *)arg0 + 0x40));
    var_a0 = 0;
    if ((*(s32 *)((u8 *)temp_s0 + 4)) != 0) {
        if ((*(s32 *)((u8 *)temp_s0 + 8)) != 0) {
            func_0018F5C8(temp_s0);
            var_a0 = 1;
            (*(s32 *)((u8 *)arg0 + 8)) = (s32) ((*(s32 *)((u8 *)temp_s0 + 0x118)) - (*(s32 *)((u8 *)temp_s0 + 0xAC)));
            (*(s32 *)((u8 *)temp_s0 + 4)) = 0;
        }
    }
    return var_a0;
}

void func_0018F5B8(void *arg0) {
    *(s32 *)((u8 *)arg0 + 0x848) = 0;
    func_0018A378(1);
}

INCLUDE_ASM("asm/nonmatchings/main_030", func_0018F5C8);

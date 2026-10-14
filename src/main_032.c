#include "common.h"

s32 func_00191C50(s32 arg0) {
    u8 *b_D_0028F300 = (u8 *)&D_0028F300;
    s32 temp_s0;

    if (func_00191608(0x22) == 0) {
        return 0;
    }
    (*(s32 *)b_D_0028F300) = arg0;
    func_0017E190(&D_0028F300, 4);
    if (func_0017EA80(&D_0028F708, 0x22, 0, &D_0028F300, 4, &D_0028EEC0, 4, 0, 0) < 0) {
        func_0017B900(D_0028DCEC);
        return 0;
    }
    temp_s0 = *(s32 *)((s32) &D_0028EEC0 | 0x20000000);
    func_0017B900(D_0028DCEC);
    return temp_s0;
}

INCLUDE_ASM("asm/nonmatchings/main_032", func_00191D18);

s32 func_00191EF8(void) {
    s32 temp_s0;

    if (func_00191608(3) == 0) {
        return -1;
    }
    if (func_0017EA80(&D_0028F708, 4, 0, 0, 0, &D_0028EEC0, 4, 0, 0) < 0) {
        func_0017B900(D_0028DCEC);
        return -1;
    }
    temp_s0 = *(s32 *)((s32) &D_0028EEC0 | 0x20000000);
    func_0017B900(D_0028DCEC);
    return temp_s0;
}

s32 func_00191F90(s32 arg0, s32 arg1, s32 arg2) {
    D_0028F730 = 0;
    return func_00192308(arg0, arg1, arg2, 5, &D_00315958);
}

s32 func_00191FC0(s32 arg0, s32 *arg1) {
    D_0028F730 = 1;
    return func_00192308(arg0, 0, 0, 1, arg1);
}

s32 func_00191FF8(s32 arg0) {

    return func_00192308(arg0, 0, 0, 9, &D_00315958);
}

s32 func_00192028(s32 arg0) {

    return func_00192308(arg0, 0, 0, 4, &D_00315958);
}

s32 func_00192058(void) {
    D_0028F730 = 0;
    return func_00192308(0, 0, 0, 3, &D_00315958);
}

INCLUDE_ASM("asm/nonmatchings/main_032", func_00192090);

s32 func_00192218(void) {
    D_0028F730 = 0;
    if (D_0028DCD0 > 0) {
        func_0017DA98(&D_002BCE58);
    }
    return func_00192308(0, 0, 0, 7, &D_00315958);
}

s32 func_00192268(void) {
    D_0028F730 = 1;
    if (D_0028DCD0 > 0) {
        func_0017DA98(&D_002BCE70);
    }
    return func_00192308(0, 0, 0, 8, &D_00315958);
}

s32 func_001922C0(void) {
    if (D_0028DCD0 > 0) {
        func_0017DA98(&D_002BCE88);
    }
    return func_00192308(0, 0, 0, 6, &D_00315958);
}

INCLUDE_ASM("asm/nonmatchings/main_032", func_00192308);

INCLUDE_ASM("asm/nonmatchings/main_032", func_00192470);

INCLUDE_ASM("asm/nonmatchings/main_032", func_00192588);

INCLUDE_ASM("asm/nonmatchings/main_032", func_001926C8);

s32 func_00192768(void) {
    (*(s32 *)(&D_00315BC0)) = 0xF;
    if (func_0017EA80(&D_00315980, 1, 0, &D_00315BC0, 0x80, &D_00315BC0, 0x80, 0, 0) < 0) {
        return 0;
    }
    if ((*(s32 *)((u8 *)(&D_00315BC0) + 0xC)) == 1) {
        D_0028F748 = 0;
    }
    return (*(s32 *)((u8 *)(&D_00315BC0) + 0xC));
}

INCLUDE_ASM("asm/nonmatchings/main_032", func_001927E8);

INCLUDE_ASM("asm/nonmatchings/main_032", func_001929D0);

INCLUDE_ASM("asm/nonmatchings/main_032", func_00192A88);

INCLUDE_ASM("asm/nonmatchings/main_032", func_00192AE8);

INCLUDE_ASM("asm/nonmatchings/main_032", func_00192B38);

INCLUDE_ASM("asm/nonmatchings/main_032", func_00192BB8);

void func_00192C30(u32 arg0, s8 *arg1) {
    if (arg0 < 8U) {
        func_0019BDD8(arg1, (&D_0028F750)[arg0]);
        return;
    }
    *arg1 = (s8) D_002BD000;
}

INCLUDE_ASM("asm/nonmatchings/main_032", func_00192C68);

INCLUDE_ASM("asm/nonmatchings/main_032", func_00192CD0);

void func_00192D20(u32 arg0, s8 *arg1) {
    if (arg0 < 4U) {
        func_0019BDD8(arg1, (&D_0028F770)[arg0]);
        return;
    }
    *arg1 = (s8) D_002BD000;
}

INCLUDE_ASM("asm/nonmatchings/main_032", func_00192D58);

INCLUDE_ASM("asm/nonmatchings/main_032", func_00192E78);

INCLUDE_ASM("asm/nonmatchings/main_032", func_00192F98);

INCLUDE_ASM("asm/nonmatchings/main_032", func_001930D0);

INCLUDE_ASM("asm/nonmatchings/main_032", func_00193188);

INCLUDE_ASM("asm/nonmatchings/main_032", func_00193248);

INCLUDE_ASM("asm/nonmatchings/main_032", func_00193320);

s32 func_001933D8(s32 arg0, s32 arg1, s32 arg2) {
    u8 *b_D_00315BC0 = (u8 *)&D_00315BC0;
    s32 temp_v0;

    (*(s32 *)(b_D_00315BC0 + 0xC)) = arg2;
    (*(s32 *)(&D_00315BC0)) = 0xA;
    (*(s32 *)(b_D_00315BC0 + 4)) = arg0;
    (*(s32 *)(b_D_00315BC0 + 8)) = arg1;
    if (func_0017EA80(&D_00315980, 1, 0, &D_00315BC0, 0x80, &D_00315BC0, 0x80, 0, 0) < 0) {
        return 0;
    }
    if ((*(s32 *)(b_D_00315BC0 + 0x10)) == 1) {
        func_00192C68(arg0, arg1, 2);
    }
    return (*(s32 *)(b_D_00315BC0 + 0x10));
}

INCLUDE_ASM("asm/nonmatchings/main_032", func_00193488);

INCLUDE_ASM("asm/nonmatchings/main_032", func_001934E8);

INCLUDE_ASM("asm/nonmatchings/main_032", func_00193540);

INCLUDE_ASM("asm/nonmatchings/main_032", func_00193598);

s32 func_00193668(void) {
    (*(s32 *)(&D_00315BC0)) = 0xC;
    if (func_0017EA80(&D_00315980, 1, 0, &D_00315BC0, 0x80, &D_00315BC0, 0x80, 0, 0) < 0) {
        return 0;
    }
    return (*(s32 *)((u8 *)(&D_00315BC0) + 0xC));
}

s32 func_001936D0(s32 arg0) {
    (*(s32 *)(&D_00315BC0)) = 0xD;
    (*(s32 *)((u8 *)(&D_00315BC0) + 4)) = arg0;
    if (func_0017EA80(&D_00315980, 1, 0, &D_00315BC0, 0x80, &D_00315BC0, 0x80, 0, 0) < 0) {
        return 0;
    }
    return (*(s32 *)((u8 *)(&D_00315BC0) + 0xC));
}

s32 func_00193738(void) {
    (*(s32 *)(&D_00315BC0)) = 0x12;
    if (func_0017EA80(&D_00315980, 1, 0, &D_00315BC0, 0x80, &D_00315BC0, 0x80, 0, 0) < 0) {
        return 0;
    }
    return (*(s32 *)((u8 *)(&D_00315BC0) + 0xC));
}

s32 func_001937A0(s32 arg0) {
    (*(s32 *)(&D_00315BC0)) = 0x14;
    (*(s32 *)((u8 *)(&D_00315BC0) + 4)) = arg0;
    if (func_0017EA80(&D_00315980, 1, 0, &D_00315BC0, 0x80, &D_00315BC0, 0x80, 0, 0) < 0) {
        return 0;
    }
    return (*(s32 *)((u8 *)(&D_00315BC0) + 8));
}

INCLUDE_ASM("asm/nonmatchings/main_032", func_00193808);

s32 func_001939C0(void) {
    if (D_0028F794 >= 0) {
        func_0017B8F0(D_0028F794);
        D_0028F794 = -1;
    }
    return 1;
}

s32 *func_00193A00(s32 **arg0, s32 **arg1) {
    *arg0 = &D_00317200;
    *arg1 = &D_0028F790;
    (*(s32 *)((u8 *)(&D_00317200) + 0x3C)) = (s32) D_0028F794;
    return &D_00315C40;
}

INCLUDE_ASM("asm/nonmatchings/main_032", func_00193A30);

INCLUDE_ASM("asm/nonmatchings/main_032", func_00193AE8);

INCLUDE_ASM("asm/nonmatchings/main_032", func_00193BA8);

INCLUDE_ASM("asm/nonmatchings/main_032", func_00193CE0);

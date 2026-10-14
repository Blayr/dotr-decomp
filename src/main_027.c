#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_027", func_00186D78);

INCLUDE_ASM("asm/nonmatchings/main_027", func_00186E58);

void func_00186FC8(void) {
    *(volatile s32 *)0x10003810 = 1;
    *(volatile s32 *)0x10003820 = 6;
}

INCLUDE_ASM("asm/nonmatchings/main_027", func_00186FF0);

INCLUDE_ASM("asm/nonmatchings/main_027", func_00187058);

INCLUDE_ASM("asm/nonmatchings/main_027", func_00187098);

s32 func_001870B8(void) {
    return *(volatile s32 *)0x10003820;
}

INCLUDE_ASM("asm/nonmatchings/main_027", func_001870C8);

s32 func_00187118(void *arg0) {
    u32 temp_s4;

    temp_s4 = *(volatile u32 *)0x10003840;
    if (func_001870C8() >= 2U) {
        return 0;
    }
    (*(s32 *)arg0) = (s32) *(volatile s32 *)0x10003900;
    (*(s32 *)((u8 *)arg0 + 4)) = (s32) *(volatile s32 *)0x10003910;
    (*(s32 *)((u8 *)arg0 + 8)) = (s32) *(volatile s32 *)0x10003920;
    (*(s32 *)((u8 *)arg0 + 0xC)) = (s32) *(volatile s32 *)0x10003930;
    (*(s32 *)((u8 *)arg0 + 0x10)) = (s32) *(volatile s32 *)0x10003940;
    (*(s32 *)((u8 *)arg0 + 0x14)) = (s32) *(volatile s32 *)0x10003950;
    (*(s32 *)((u8 *)arg0 + 0x18)) = (s32) *(volatile s32 *)0x10003960;
    (*(s32 *)((u8 *)arg0 + 0x1C)) = (s32) *(volatile s32 *)0x10003970;
    (*(s32 *)((u8 *)arg0 + 0x20)) = (s32) *(volatile s32 *)0x10003870;
    (*(s32 *)((u8 *)arg0 + 0x24)) = (s32) *(volatile s32 *)0x10003880;
    (*(s32 *)((u8 *)arg0 + 0x28)) = (s32) *(volatile s32 *)0x10003800;
    (*(s16 *)((u8 *)arg0 + 0x2C)) = (s16) *(volatile s32 *)0x100038D0;
    (*(s16 *)((u8 *)arg0 + 0x2E)) = (s16) *(volatile s32 *)0x10003890;
    (*(s16 *)((u8 *)arg0 + 0x30)) = (s16) *(volatile s32 *)0x10003830;
    (*(s16 *)((u8 *)arg0 + 0x32)) = (s16) *(volatile s32 *)0x10003860;
    (*(s8 *)((u8 *)arg0 + 0x34)) = (s8) *(volatile s32 *)0x10003820;
    (*(s8 *)((u8 *)arg0 + 0x35)) = (s8) temp_s4;
    (*(s8 *)((u8 *)arg0 + 0x36)) = (s8) (temp_s4 >> 8);
    (*(s8 *)((u8 *)arg0 + 0x37)) = (s8) *(volatile s32 *)0x10003850;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_027", func_00187298);

INCLUDE_ASM("asm/nonmatchings/main_027", func_001872F8);

void func_00187308(void *arg0) {
    (*(s32 *)((u8 *)arg0 + 8)) = 0;
    (*(s32 *)arg0) = (s32) (*(s32 *)((u8 *)arg0 + 4));
}

s32 func_00187318(void *arg0) {
    s32 *temp_a2;
    s32 var_a1;

    var_a1 = (*(s32 *)arg0);
    temp_a2 = (*(s32 **)((u8 *)arg0 + 8));
    if (var_a1 & 0xC) {
        do {
            *(s32 *)var_a1 = 0;
            var_a1 += 4;
        } while (var_a1 & 0xC);
    }
    if (temp_a2 != NULL) {
        s32 n = (((__int128 *)var_a1) - ((__int128 *)temp_a2)) - 1; *temp_a2 += n;
    }
    (*(s32 *)arg0) = var_a1;
    (*(s32 **)((u8 *)arg0 + 8)) = NULL;
    return var_a1;
}

INCLUDE_ASM("asm/nonmatchings/main_027", func_00187370);

INCLUDE_ASM("asm/nonmatchings/main_027", func_001873E8);

INCLUDE_ASM("asm/nonmatchings/main_027", func_00187480);

INCLUDE_ASM("asm/nonmatchings/main_027", func_001874F8);

void func_00187510(s32 *arg0, __int128 arg1) {
    __int128 *p = (__int128 *) arg0[0];
    *p = arg1;
    arg0[3] = (s32) p;
    arg0[0] = (s32) (p + 1);
}

INCLUDE_ASM("asm/nonmatchings/main_027", func_00187528);

INCLUDE_ASM("asm/nonmatchings/main_027", func_001875D0);

void func_001875F8(s32 *arg0, s32 arg1) {
    arg0[1] = arg1;
    arg0[0] = arg1;
    arg0[2] = 0;
}

s32 func_00187608(void *arg0) {
    s32 *temp_a2;
    s32 var_a1;

    var_a1 = (*(s32 *)arg0);
    temp_a2 = (*(s32 **)((u8 *)arg0 + 8));
    if (var_a1 & 0xC) {
        do {
            *(s32 *)var_a1 = 0;
            var_a1 += 4;
        } while (var_a1 & 0xC);
    }
    if (temp_a2 != NULL) {
        s32 n = (((__int128 *)var_a1) - ((__int128 *)temp_a2)) - 1; *temp_a2 += n;
    }
    (*(s32 *)arg0) = var_a1;
    (*(s32 **)((u8 *)arg0 + 8)) = NULL;
    return var_a1;
}

INCLUDE_ASM("asm/nonmatchings/main_027", func_00187660);

void func_001876B8(void *arg0, __int128 arg1) {
    __int128 *temp_v0;

    temp_v0 = (*(__int128 **)arg0);
    *temp_v0 = arg1;
    (*(__int128 **)((u8 *)arg0 + 0x14)) = temp_v0;
    (*(__int128 **)arg0) = (__int128 *) (temp_v0 + 1);
}

INCLUDE_ASM("asm/nonmatchings/main_027", func_001876D0);

INCLUDE_ASM("asm/nonmatchings/main_027", func_00187778);

void func_001877F8(s32 **arg0, s32 arg1) {
    *(*arg0)++ = arg1;
}

void func_00187810(s32 **arg0, s32 arg1) {
    *(*arg0)++ = arg1;
}

INCLUDE_ASM("asm/nonmatchings/main_027", func_00187828);

void func_00187858(void *arg0, s32 arg1) {
    s32 *temp_a1;

    func_00187778(arg0, 2, 3);
    temp_a1 = (*(s32 **)arg0);
    (*(s32 **)((u8 *)arg0 + 0xC)) = temp_a1;
    (*(s32 **)arg0) = (s32 *) (temp_a1 + 1);
    *temp_a1 = (arg1 != 0) ? 0xD1000000 : 0x51000000;
}

INCLUDE_ASM("asm/nonmatchings/main_027", func_001878B0);

INCLUDE_ASM("asm/nonmatchings/main_027", func_001878E0);

INCLUDE_ASM("asm/nonmatchings/main_027", func_00187910);

INCLUDE_ASM("asm/nonmatchings/main_027", func_00187958);

INCLUDE_ASM("asm/nonmatchings/main_027", func_00187978);

INCLUDE_ASM("asm/nonmatchings/main_027", func_001879A0);

INCLUDE_ASM("asm/nonmatchings/main_027", func_001879E0);

INCLUDE_ASM("asm/nonmatchings/main_027", func_00187A28);

INCLUDE_ASM("asm/nonmatchings/main_027", func_00187A98);

INCLUDE_ASM("asm/nonmatchings/main_027", func_00187AB8);

INCLUDE_ASM("asm/nonmatchings/main_027", func_00187AD8);

INCLUDE_ASM("asm/nonmatchings/main_027", func_00187B00);

INCLUDE_ASM("asm/nonmatchings/main_027", func_00187B18);

INCLUDE_ASM("asm/nonmatchings/main_027", func_00187B30);

INCLUDE_ASM("asm/nonmatchings/main_027", func_00187B48);

INCLUDE_ASM("asm/nonmatchings/main_027", func_00187B60);

INCLUDE_ASM("asm/nonmatchings/main_027", func_00187B90);

INCLUDE_ASM("asm/nonmatchings/main_027", func_00187BA0);

INCLUDE_ASM("asm/nonmatchings/main_027", func_00187BC8);

INCLUDE_ASM("asm/nonmatchings/main_027", func_00187BD8);

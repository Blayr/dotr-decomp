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

INCLUDE_ASM("asm/nonmatchings/main_027", func_00187118);

INCLUDE_ASM("asm/nonmatchings/main_027", func_00187298);

INCLUDE_ASM("asm/nonmatchings/main_027", func_001872F8);

void func_00187308(void *arg0) {
    (*(s32 *)((u8 *)arg0 + 8)) = 0;
    (*(s32 *)arg0) = (s32) (*(s32 *)((u8 *)arg0 + 4));
}

INCLUDE_ASM("asm/nonmatchings/main_027", func_00187318);

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

INCLUDE_ASM("asm/nonmatchings/main_027", func_00187608);

INCLUDE_ASM("asm/nonmatchings/main_027", func_00187660);

INCLUDE_ASM("asm/nonmatchings/main_027", func_001876B8);

INCLUDE_ASM("asm/nonmatchings/main_027", func_001876D0);

INCLUDE_ASM("asm/nonmatchings/main_027", func_00187778);

void func_001877F8(s32 **arg0, s32 arg1) {
    *(*arg0)++ = arg1;
}

void func_00187810(s32 **arg0, s32 arg1) {
    *(*arg0)++ = arg1;
}

INCLUDE_ASM("asm/nonmatchings/main_027", func_00187828);

INCLUDE_ASM("asm/nonmatchings/main_027", func_00187858);

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

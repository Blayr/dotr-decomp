#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017D0C0);

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017D180);

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017D1B8);

void func_0017D268(s32 arg0) {
    if (arg0 == 0xA) {
        func_0017D180(0xD);
        func_0017D180(0xA);
        return;
    }
    func_0017D180(arg0);
}

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017D2A0);

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017D330);

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017D498);

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017DA60);

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017DA98);

void func_0017DAF8(s32 *arg0, s32 *arg1) {
    ((s32 **) arg1)[7][arg0[4]] = arg0[5];
}

void func_0017DB18(void *arg0, void *arg1) {
    (*(s32 *)((u8 *)arg1 + 8)) = (s32) (*(s32 *)((u8 *)arg0 + 0x10));
}

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017DB28);

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017DB40);

s32 *func_0017DB60(void) {
    return &D_00310E98;
}

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017DB70);

void func_0017DDF0(void) {
    func_0017C490(5);
    func_0017B610(5, D_00310E94);
    D_0028CA10 = 0;
}

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017DE28);

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017DE40);

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017DE58);

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017DE88);

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017DEB0);

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017DFE8);

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017E028);

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017E068);

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017E190);

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017E23C);

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017E244);

void func_0017E3E0(void) {
    func_0017DDF0();
    D_0028CA18 = 0;
}

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017E408);

void func_0017E4B0(void *arg0) {
    (*(s32 *)((u8 *)arg0 + 0x18)) = 0;
    (*(s32 *)((u8 *)arg0 + 0x10)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x10)) & 0xFFFFFFFE);
}

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017E4D0);

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017E500);

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017E540);

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017E5F8);

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017E658);

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017E7B0);

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017E800);

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017E8B0);

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017E9F0);

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017EA80);

s32 func_0017EC70(void *arg0) {
    void *temp_a1;

    temp_a1 = (*(void **)arg0);
    if ((temp_a1 == NULL) || ((*(s32 *)((u8 *)arg0 + 4)) != (*(s32 *)((u8 *)temp_a1 + 0x18))) || !((*(s32 *)((u8 *)temp_a1 + 0x10)) & 1)) {
        return 0;
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017ECB0);

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017ED48);

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017EE18);

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017EEB0);

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017EF40);

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017EF98);

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017F160);

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017F1A0);

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017F200);

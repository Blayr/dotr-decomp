#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_033", func_00193D18);

INCLUDE_ASM("asm/nonmatchings/main_033", func_00193DD0);

INCLUDE_ASM("asm/nonmatchings/main_033", func_00193EA8);

INCLUDE_ASM("asm/nonmatchings/main_033", func_00193F38);

INCLUDE_ASM("asm/nonmatchings/main_033", func_00194058);

INCLUDE_ASM("asm/nonmatchings/main_033", func_001941D8);

void func_00194200(s32 arg0) {
    func_0017B660(arg0 & 0xFFFF, &func_001941D8, func_0017B7D0());
    func_0017B800();
}

INCLUDE_ASM("asm/nonmatchings/main_033", func_00194248);

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

INCLUDE_ASM("asm/nonmatchings/main_033", func_00194508);

INCLUDE_ASM("asm/nonmatchings/main_033", func_00194578);

INCLUDE_ASM("asm/nonmatchings/main_033", func_001946D0);

INCLUDE_ASM("asm/nonmatchings/main_033", func_00194758);

INCLUDE_ASM("asm/nonmatchings/main_033", func_001948A8);

INCLUDE_ASM("asm/nonmatchings/main_033", func_00194970);

INCLUDE_ASM("asm/nonmatchings/main_033", func_00194A98);

INCLUDE_ASM("asm/nonmatchings/main_033", func_00194B50);

INCLUDE_ASM("asm/nonmatchings/main_033", func_00194D28);

INCLUDE_ASM("asm/nonmatchings/main_033", func_00194E90);

INCLUDE_ASM("asm/nonmatchings/main_033", func_00194F58);

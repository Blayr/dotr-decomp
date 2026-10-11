#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_039", func_001B62F0);

INCLUDE_ASM("asm/nonmatchings/main_039", func_001B65E0);

INCLUDE_ASM("asm/nonmatchings/main_039", func_001B65F0);

INCLUDE_ASM("asm/nonmatchings/main_039", func_001B6C90);

INCLUDE_ASM("asm/nonmatchings/main_039", func_001B6CA0);

INCLUDE_ASM("asm/nonmatchings/main_039", func_001B6EA0);

INCLUDE_ASM("asm/nonmatchings/main_039", func_001B6F70);

s32 func_001B7660(s8 character) {
    s32 result = -1;

    if (character >= 'A' && character <= 'Z') {
        result = character - 'A';
    } else if (character >= 'a' && character <= 'z') {
        result = character - 'a';
    } else if (character >= '0' && character <= '9') {
        result = character - '0' + 26;
    } else if (character == '?') {
        result = 36;
    }
    return result;
}

INCLUDE_ASM("asm/nonmatchings/main_039", func_001B76E0);

INCLUDE_ASM("asm/nonmatchings/main_039", func_001B7820);

INCLUDE_ASM("asm/nonmatchings/main_039", func_001B7D60);

INCLUDE_ASM("asm/nonmatchings/main_039", func_001B7F90);

void func_001B81E0(void) {
    func_00209D30(func_001B8210(func_00209D20()));
}

INCLUDE_ASM("asm/nonmatchings/main_039", func_001B8210);

INCLUDE_ASM("asm/nonmatchings/main_039", func_001B8260);

void func_001B83C0(void) {
    func_00209D30(func_001B83F0(func_00209D20()));
}

INCLUDE_ASM("asm/nonmatchings/main_039", func_001B83F0);

INCLUDE_ASM("asm/nonmatchings/main_039", func_001B8520);

INCLUDE_ASM("asm/nonmatchings/main_039", func_001B8720);

void func_001B8830(void) {

}

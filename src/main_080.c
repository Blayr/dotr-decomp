#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_080", func_0027F700);

INCLUDE_ASM("asm/nonmatchings/main_080", func_0027F830);

INCLUDE_ASM("asm/nonmatchings/main_080", func_0027F890);

INCLUDE_ASM("asm/nonmatchings/main_080", func_0027F8B4);

INCLUDE_ASM("asm/nonmatchings/main_080", func_0027F8D8);

INCLUDE_ASM("asm/nonmatchings/main_080", func_0027F8FC);

INCLUDE_ASM("asm/nonmatchings/main_080", func_0027FA30);

INCLUDE_ASM("asm/nonmatchings/main_080", func_0027FAB0);

INCLUDE_ASM("asm/nonmatchings/main_080", func_0027FC20);

INCLUDE_ASM("asm/nonmatchings/main_080", func_0027FFC0);

INCLUDE_ASM("asm/nonmatchings/main_080", func_00280060);

INCLUDE_ASM("asm/nonmatchings/main_080", func_00280670);

INCLUDE_ASM("asm/nonmatchings/main_080", func_00280920);

INCLUDE_ASM("asm/nonmatchings/main_080", func_00280CB0);

INCLUDE_ASM("asm/nonmatchings/main_080", func_002817C0);

INCLUDE_ASM("asm/nonmatchings/main_080", func_002818A0);

INCLUDE_ASM("asm/nonmatchings/main_080", func_002825F0);

INCLUDE_ASM("asm/nonmatchings/main_080", func_002831A0);

INCLUDE_ASM("asm/nonmatchings/main_080", func_00283880);

INCLUDE_ASM("asm/nonmatchings/main_080", func_00284D30);

INCLUDE_ASM("asm/nonmatchings/main_080", func_00285880);

#pragma optimization_level 0

s32 func_00284D30(s32);                             /* extern */

void func_00285EE0(void) {
    func_00209D30(func_00284D30(func_00209D20()));
}

#pragma optimization_level reset

INCLUDE_ASM("asm/nonmatchings/main_080", func_00285F20);

void func_00286900(void) {

}

void func_00286910(void *arg0, void *arg1) {
    Callback_00286910 *current = arg0;
    Callback_00286910 *end = arg1;

    if (current < end) {
        do {
            (*current)();
            current++;
        } while (current < end);
    }
}

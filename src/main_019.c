#include "common.h"

f32 func_0017B340(u64 arg0) {
    f32 result;

    if ((s64) arg0 > 0) {
        return func_001A1F18(arg0);
    }
    result = func_001A1F18((arg0 >> 1) | (arg0 & 1));
    return result + result;
}

void func_0017B380(u32 arg0) {
    extern s32 func_001A2858(s32, s32);
    extern s32 func_001A1E70(u64);
    s32 temp_v0;
    u64 value;

    value = arg0;
    if ((s64) value > 0) {
        func_001A1E70(value);
        return;
    }
    temp_v0 = func_001A1E70((value >> 1) | (value & 1));
    func_001A2858(temp_v0, temp_v0);
}

s32 func_0017B3D0(void) {
    extern s32 func_001A2E60();
    return func_001A2E60() < 0;
}

s32 func_0017B3F0(void) {
    extern s32 func_001A2E60();
    return func_001A2E60() > 0;
}

typedef struct Module_0017B410 {
    u8 pad[0x14];
    s32 size;
    void *start;
    void *end;
} Module_0017B410;

void func_0017B410(s32 arg0, s32 arg1) {
    extern void func_00286910();
    u8 *cursor = (u8 *)arg0;
    Module_0017B410 *module = (Module_0017B410 *)arg0;
    s32 size = module->size;

    func_0017BB60(2);
    if (size != 0) {
        cursor += arg1;
        func_00198948(cursor, 0, size);
    }
    func_00286910(module->start, module->end, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B4C0);

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B4D0);

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B4E0);

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B4F0);

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B500);

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B510);

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B520);

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B530);

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B540);

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B550);

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B560);

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B570);

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B580);

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B590);

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B5A0);

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B5B0);

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B5C0);

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B5D0);

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B5E0);

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B5F0);

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B600);

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B610);

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B620);

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B630);

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B640);

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B650);

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B660);

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B670);

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B680);

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B690);

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B6A0);

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B6B0);

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B6C0);

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B6D0);

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B6E0);

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B6F0);

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B700);

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B710);

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B720);

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B730);

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B740);

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B750);

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B760);

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B770);

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B780);

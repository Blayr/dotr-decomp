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

asm int func_0017B4C0(void) {
    .set noreorder
    addiu v1, zero, 0x0
    syscall 0
    jr ra
    nop
}

asm int func_0017B4D0(void) {
    .set noreorder
    addiu v1, zero, 0x1
    syscall 0
    jr ra
    nop
}

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B4E0);

asm int func_0017B4F0(void) {
    .set noreorder
    addiu v1, zero, 0x3
    syscall 0
    jr ra
    nop
}

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B500);

asm int func_0017B510(void) {
    .set noreorder
    addiu v1, zero, 0x5
    syscall 0
    jr ra
    nop
}

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B520);

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B530);

asm int func_0017B540(void) {
    .set noreorder
    addiu v1, zero, 0x8
    syscall 0
    jr ra
    nop
}

asm int func_0017B550(void) {
    .set noreorder
    addiu v1, zero, 0x9
    syscall 0
    jr ra
    nop
}

asm int func_0017B560(void) {
    .set noreorder
    addiu v1, zero, 0xA
    syscall 0
    jr ra
    nop
}

asm int func_0017B570(void) {
    .set noreorder
    addiu v1, zero, 0xB
    syscall 0
    jr ra
    nop
}

asm int func_0017B580(void) {
    .set noreorder
    addiu v1, zero, 0xC
    syscall 0
    jr ra
    nop
}

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B590);

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B5A0);

asm int func_0017B5B0(void) {
    .set noreorder
    addiu v1, zero, 0xF
    syscall 0
    jr ra
    nop
}

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B5C0);

asm int func_0017B5D0(void) {
    .set noreorder
    addiu v1, zero, 0x10
    syscall 0
    jr ra
    nop
}

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B5E0);

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B5F0);

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B600);

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B610);

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B620);

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B630);

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B640);

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B650);

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B660);

asm int func_0017B670(void) {
    .set noreorder
    addiu v1, zero, 0xFD
    syscall 0
    jr ra
    nop
}

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B680);

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B690);

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B6A0);

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B6B0);

asm int func_0017B6C0(void) {
    .set noreorder
    addiu v1, zero, -0xFE
    syscall 0
    jr ra
    nop
}

asm int func_0017B6D0(void) {
    .set noreorder
    addiu v1, zero, -0xFF
    syscall 0
    jr ra
    nop
}

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B6E0);

asm int func_0017B6F0(void) {
    .set noreorder
    addiu v1, zero, 0x21
    syscall 0
    jr ra
    nop
}

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B700);

asm int func_0017B710(void) {
    .set noreorder
    addiu v1, zero, 0x23
    syscall 0
    jr ra
    nop
}

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B720);

asm int func_0017B730(void) {
    .set noreorder
    addiu v1, zero, 0x25
    syscall 0
    jr ra
    nop
}

asm int func_0017B740(void) {
    .set noreorder
    addiu v1, zero, -0x26
    syscall 0
    jr ra
    nop
}

asm int func_0017B750(void) {
    .set noreorder
    addiu v1, zero, 0x27
    syscall 0
    jr ra
    nop
}

asm int func_0017B760(void) {
    .set noreorder
    addiu v1, zero, 0x28
    syscall 0
    jr ra
    nop
}

INCLUDE_ASM("asm/nonmatchings/main_019", func_0017B770);

asm int func_0017B780(void) {
    .set noreorder
    addiu v1, zero, -0x2A
    syscall 0
    jr ra
    nop
}

/* Sony's start-up code (crt0): clears .bss, sets up the stack, heap and thread, then calls main. */

#include "common.h"

/* The program's entry stub (jumps to the start-up code). */
asm void func_00100000(void) {
    .set noreorder
    nop
}

/* Sony crt0.s _start (the Japanese build has the same code, from an older crt0 that orders the
   bss-clear loop's nops differently). Linker names: _fbss, _end, _gp, _stack, _stack_size, _args, _root. */
extern f32 g_vec_temp[];
extern s32 D_00317EF0;
extern s32 D_0030FFC0;
extern s32 D_12000;
extern s32 D_20000;
extern s32 _stack;

/* Start-up code: clears .bss, sets up the stack, the heap and the thread, calls main. */
asm void func_00100008(void) {
    .set noreorder
    la v0, g_vec_temp
    la v1, D_1FE0000
L_00100018:
    sq zero, 0x0(v0)
    nop
    sltu at, v0, v1
    nop
    nop
    bnez at, L_00100018
    addiu v0, v0, 0x10
    la a0, D_00317EF0
    la a1, _stack
    la a2, D_12000
    la a3, D_0030FFC0
    la t0, func_001000C0
    .word 0x0080E025 /* or gp, a0, zero: the assembler would write paddub */
    addiu v1, zero, 0x3C
    syscall 0
    .word 0x0040E825 /* or sp, v0, zero */
    la a0, D_1FE0000
    la a1, D_20000
    addiu v1, zero, 0x3D
    syscall 0
    jal func_00184540
    nop
    jal FlushCache
    .word 0x00002025 /* or a0, zero, zero */
    ei
    la v0, D_0030FFC0
    lw a0, 0x0(v0)
    jal main
    addiu a1, v0, 0x4
    j func_001847B0
    .word 0x00402025 /* or a0, v0, zero */
}

/* Hand-written tail jump (GCC-style move into the delay slot). */

/* A start-up stub. */
asm void func_001000B8(void) {
    .set noreorder
    j func_001847B0
    .word 0x00002025 /* or a0, zero, zero: the assembler would write paddub */
}

/* Kernel call 0x23 (ExitThread): ends the calling thread. */
asm void func_001000C0(void) {
    .set noreorder
    addiu v1, zero, 0x23
    syscall 0
}

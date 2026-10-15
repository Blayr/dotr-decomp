#include "common.h"

f32 _f_ulltof(u64 arg0) {
    f32 result;

    if ((s64) arg0 > 0) {
        return func_001A1F18(arg0);
    }
    result = func_001A1F18((arg0 >> 1) | (arg0 & 1));
    return result + result;
}

void _d_utod(u32 arg0) {
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

s32 _dpflt(void) {
    extern s32 func_001A2E60();
    return func_001A2E60() < 0;
}

s32 _dpfgt(void) {
    extern s32 func_001A2E60();
    return func_001A2E60() > 0;
}

typedef struct Module_0017B410 {
    u8 pad[0x14];
    s32 size;
    void *start;
    void *end;
} Module_0017B410;

void mwOverlayInit(s32 arg0, s32 arg1) {
    extern void __initialize_cpp_rts();
    u8 *cursor = (u8 *)arg0;
    Module_0017B410 *module = (Module_0017B410 *)arg0;
    s32 size = module->size;

    FlushCache(2);
    if (size != 0) {
        cursor += arg1;
        func_00198948(cursor, 0, size);
    }
    __initialize_cpp_rts(module->start, module->end, 0, 0);
}

asm int RFU000_FullReset(void) {
    .set noreorder
    addiu v1, zero, 0x0
    syscall 0
    jr ra
    nop
}

asm int ResetEE(void) {
    .set noreorder
    addiu v1, zero, 0x1
    syscall 0
    jr ra
    nop
}

asm int SetGsCrt(int arg0, int arg1, int arg2) {
    .set noreorder
    addiu v1, zero, 0x2
    syscall 0
    jr ra
    nop
}

asm int RFU003(void) {
    .set noreorder
    addiu v1, zero, 0x3
    syscall 0
    jr ra
    nop
}

asm int Exit(int arg0) {
    .set noreorder
    addiu v1, zero, 0x4
    syscall 0
    jr ra
    nop
}

asm int RFU005(void) {
    .set noreorder
    addiu v1, zero, 0x5
    syscall 0
    jr ra
    nop
}

asm int LoadExecPS2(int arg0, int arg1, int arg2) {
    .set noreorder
    addiu v1, zero, 0x6
    syscall 0
    jr ra
    nop
}

asm s32 ExecPS2(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    .set noreorder
    addiu v1, zero, 0x7
    syscall 0
    jr ra
    nop
}

asm int RFU008(void) {
    .set noreorder
    addiu v1, zero, 0x8
    syscall 0
    jr ra
    nop
}

asm int RFU009(void) {
    .set noreorder
    addiu v1, zero, 0x9
    syscall 0
    jr ra
    nop
}

asm int AddSbusIntcHandler(void) {
    .set noreorder
    addiu v1, zero, 0xA
    syscall 0
    jr ra
    nop
}

asm int RemoveSbusIntcHandler(void) {
    .set noreorder
    addiu v1, zero, 0xB
    syscall 0
    jr ra
    nop
}

asm int Interrupt2Iop(void) {
    .set noreorder
    addiu v1, zero, 0xC
    syscall 0
    jr ra
    nop
}

asm int SetVTLBRefillHandler(int arg0, int *arg1) {
    .set noreorder
    addiu v1, zero, 0xD
    syscall 0
    jr ra
    nop
}

asm int SetVCommonHandler(int arg0, int *arg1) {
    .set noreorder
    addiu v1, zero, 0xE
    syscall 0
    jr ra
    nop
}

asm int SetVInterruptHandler(void) {
    .set noreorder
    addiu v1, zero, 0xF
    syscall 0
    jr ra
    nop
}

asm s32 AddIntcHandler(s32 arg0, void (*arg1)(), s32 arg2) {
    .set noreorder
    addiu v1, zero, 0x10
    syscall 0
    jr ra
    nop
}

asm int AddIntcHandler2(void) {
    .set noreorder
    addiu v1, zero, 0x10
    syscall 0
    jr ra
    nop
}

asm int RemoveIntcHandler(int arg0, int arg1) {
    .set noreorder
    addiu v1, zero, 0x11
    syscall 0
    jr ra
    nop
}

asm s32 AddDmacHandler(s32 arg0, void (*arg1)(), s32 arg2) {
    .set noreorder
    addiu v1, zero, 0x12
    syscall 0
    jr ra
    nop
}

asm s32 AddDmacHandler2(s32 arg0, s32 (*arg1)(s32, void *), s32 arg2, u32 *arg3) {
    .set noreorder
    addiu v1, zero, 0x12
    syscall 0
    jr ra
    nop
}

asm int RemoveDmacHandler(int arg0, int arg1) {
    .set noreorder
    addiu v1, zero, 0x13
    syscall 0
    jr ra
    nop
}

asm int _EnableIntc(int arg0) {
    .set noreorder
    addiu v1, zero, 0x14
    syscall 0
    jr ra
    nop
}

asm int _DisableIntc(int arg0) {
    .set noreorder
    addiu v1, zero, 0x15
    syscall 0
    jr ra
    nop
}

asm int _EnableDmac(int arg0) {
    .set noreorder
    addiu v1, zero, 0x16
    syscall 0
    jr ra
    nop
}

asm int _DisableDmac(int arg0) {
    .set noreorder
    addiu v1, zero, 0x17
    syscall 0
    jr ra
    nop
}

asm int _SetAlarm(int arg0, int *arg1, int arg2) {
    .set noreorder
    addiu v1, zero, 0xFC
    syscall 0
    jr ra
    nop
}

asm int _ReleaseAlarm(void) {
    .set noreorder
    addiu v1, zero, 0xFD
    syscall 0
    jr ra
    nop
}

asm void _iEnableIntc(void) {
    .set noreorder
    addiu v1, zero, -0x1A
    syscall 0
    jr ra
    nop
}

asm void _iDisableIntc(void) {
    .set noreorder
    addiu v1, zero, -0x1B
    syscall 0
    jr ra
    nop
}

asm void _iEnableDmac(void) {
    .set noreorder
    addiu v1, zero, -0x1C
    syscall 0
    jr ra
    nop
}

asm void _iDisableDmac(void) {
    .set noreorder
    addiu v1, zero, -0x1D
    syscall 0
    jr ra
    nop
}

asm int _iSetAlarm(void) {
    .set noreorder
    addiu v1, zero, -0xFE
    syscall 0
    jr ra
    nop
}

asm int _iReleaseAlarm(void) {
    .set noreorder
    addiu v1, zero, -0xFF
    syscall 0
    jr ra
    nop
}

asm s32 CreateThread(void *arg0) {
    .set noreorder
    addiu v1, zero, 0x20
    syscall 0
    jr ra
    nop
}

asm int DeleteThread(void) {
    .set noreorder
    addiu v1, zero, 0x21
    syscall 0
    jr ra
    nop
}

asm s32 StartThread(s32 arg0, void *arg1) {
    .set noreorder
    addiu v1, zero, 0x22
    syscall 0
    jr ra
    nop
}

asm int ExitThread(void) {
    .set noreorder
    addiu v1, zero, 0x23
    syscall 0
    jr ra
    nop
}

asm void ExitDeleteThread(void) {
    .set noreorder
    addiu v1, zero, 0x24
    syscall 0
    jr ra
    nop
}

asm int TerminateThread(void) {
    .set noreorder
    addiu v1, zero, 0x25
    syscall 0
    jr ra
    nop
}

asm int iTerminateThread(void) {
    .set noreorder
    addiu v1, zero, -0x26
    syscall 0
    jr ra
    nop
}

asm int DisableDispatchThread(void) {
    .set noreorder
    addiu v1, zero, 0x27
    syscall 0
    jr ra
    nop
}

asm int EnableDispatchThread(void) {
    .set noreorder
    addiu v1, zero, 0x28
    syscall 0
    jr ra
    nop
}

asm s32 ChangeThreadPriority(s32 arg0, s32 arg1) {
    .set noreorder
    addiu v1, zero, 0x29
    syscall 0
    jr ra
    nop
}

asm int iChangeThreadPriority(void) {
    .set noreorder
    addiu v1, zero, -0x2A
    syscall 0
    jr ra
    nop
}

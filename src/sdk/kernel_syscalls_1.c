#include "common.h"

/* Converts an unsigned 64-bit integer to float. */
f32 _f_ulltof(u64 value) {
    f32 result;

    if ((s64) value > 0) {
        return func_001A1F18(value);
    }
    result = func_001A1F18((value >> 1) | (value & 1));
    return result + result;
}

/* Converts an unsigned integer to double. */
void _d_utod(u32 valueIn) {
    extern s32 func_001A2858(s32, s32);
    extern s32 func_001A1E70(u64);
    s32 temp_v0;
    u64 value;

    value = valueIn;
    if ((s64) value > 0) {
        func_001A1E70(value);
        return;
    }
    temp_v0 = func_001A1E70((value >> 1) | (value & 1));
    func_001A2858(temp_v0, temp_v0);
}

/* Double compare: less than (runtime helper). */
s32 _dpflt(void) {
    extern s32 func_001A2E60();
    return func_001A2E60() < 0;
}

/* Double compare: greater than (runtime helper). */
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

/* Runs the static constructors and flushes the cache after loading a program part. */
void mwOverlayInit(s32 start, s32 end) {
    extern void __initialize_cpp_rts();
    u8 *cursor = (u8 *)start;
    Module_0017B410 *module = (Module_0017B410 *)start;
    s32 size = module->size;

    FlushCache(2);
    if (size != 0) {
        cursor += end;
        func_00198948(cursor, 0, size);
    }
    __initialize_cpp_rts(module->start, module->end, 0, 0);
}

/* EE kernel call 0 (reserved: full reset). */
asm int RFU000_FullReset(void) {
    .set noreorder
    addiu v1, zero, 0x0
    syscall 0
    jr ra
    nop
}

/* EE kernel call: resets EE parts. */
asm int ResetEE(void) {
    .set noreorder
    addiu v1, zero, 0x1
    syscall 0
    jr ra
    nop
}

/* EE kernel call: sets the video mode (`interlace`, `mode`, `field`). */
asm int SetGsCrt(int interlace, int mode, int field) {
    .set noreorder
    addiu v1, zero, 0x2
    syscall 0
    jr ra
    nop
}

/* EE kernel call 3 (reserved). */
asm int RFU003(void) {
    .set noreorder
    addiu v1, zero, 0x3
    syscall 0
    jr ra
    nop
}

/* EE kernel call: ends the program with `status`. */
asm int Exit(int status) {
    .set noreorder
    addiu v1, zero, 0x4
    syscall 0
    jr ra
    nop
}

/* EE kernel call 5 (reserved). */
asm int RFU005(void) {
    .set noreorder
    addiu v1, zero, 0x5
    syscall 0
    jr ra
    nop
}

/* EE kernel call: loads and runs program `filename` with `argc`, `argv`. */
asm int LoadExecPS2(int filename, int argc, int argv) {
    .set noreorder
    addiu v1, zero, 0x6
    syscall 0
    jr ra
    nop
}

/* EE kernel call: runs a loaded program at `entry` (`gp`, `argc`, `argv`). */
asm s32 ExecPS2(s32 entry, s32 gp, s32 argc, s32 argv) {
    .set noreorder
    addiu v1, zero, 0x7
    syscall 0
    jr ra
    nop
}

/* EE kernel call 8 (reserved). */
asm int RFU008(void) {
    .set noreorder
    addiu v1, zero, 0x8
    syscall 0
    jr ra
    nop
}

/* EE kernel call 9 (reserved). */
asm int RFU009(void) {
    .set noreorder
    addiu v1, zero, 0x9
    syscall 0
    jr ra
    nop
}

/* EE kernel call: adds a SBUS interrupt handler. */
asm int AddSbusIntcHandler(void) {
    .set noreorder
    addiu v1, zero, 0xA
    syscall 0
    jr ra
    nop
}

/* EE kernel call: removes a SBUS interrupt handler. */
asm int RemoveSbusIntcHandler(void) {
    .set noreorder
    addiu v1, zero, 0xB
    syscall 0
    jr ra
    nop
}

/* EE kernel call: raises an interrupt on the IOP. */
asm int Interrupt2Iop(void) {
    .set noreorder
    addiu v1, zero, 0xC
    syscall 0
    jr ra
    nop
}

/* EE kernel call: sets TLB-refill handler `handler` for cause `cause`. */
asm int SetVTLBRefillHandler(int cause, int *handler) {
    .set noreorder
    addiu v1, zero, 0xD
    syscall 0
    jr ra
    nop
}

/* EE kernel call: sets common exception handler `handler` for cause `cause`. */
asm int SetVCommonHandler(int cause, int *handler) {
    .set noreorder
    addiu v1, zero, 0xE
    syscall 0
    jr ra
    nop
}

/* EE kernel call: sets an interrupt vector handler. */
asm int SetVInterruptHandler(void) {
    .set noreorder
    addiu v1, zero, 0xF
    syscall 0
    jr ra
    nop
}

/* EE kernel call: adds interrupt handler `handler` for cause `cause` (`next` places it). */
asm s32 AddIntcHandler(s32 cause, void (*handler)(), s32 next) {
    .set noreorder
    addiu v1, zero, 0x10
    syscall 0
    jr ra
    nop
}

/* EE kernel call: adds an interrupt handler with an argument. */
asm int AddIntcHandler2(void) {
    .set noreorder
    addiu v1, zero, 0x10
    syscall 0
    jr ra
    nop
}

/* EE kernel call: removes interrupt handler `id` of cause `cause`. */
asm int RemoveIntcHandler(int cause, int id) {
    .set noreorder
    addiu v1, zero, 0x11
    syscall 0
    jr ra
    nop
}

/* EE kernel call: adds DMA handler `handler` for channel `channel`. */
asm s32 AddDmacHandler(s32 channel, void (*handler)(), s32 next) {
    .set noreorder
    addiu v1, zero, 0x12
    syscall 0
    jr ra
    nop
}

/* EE kernel call: adds DMA handler `handler` for channel `channel` with argument `arg`. */
asm s32 AddDmacHandler2(s32 channel, s32 (*handler)(s32, void *), s32 arg, u32 *arg3) {
    .set noreorder
    addiu v1, zero, 0x12
    syscall 0
    jr ra
    nop
}

/* EE kernel call: removes DMA handler `id` of channel `channel`. */
asm int RemoveDmacHandler(int channel, int id) {
    .set noreorder
    addiu v1, zero, 0x13
    syscall 0
    jr ra
    nop
}

/* EE kernel call: enables interrupt cause `cause`. */
asm int _EnableIntc(int cause) {
    .set noreorder
    addiu v1, zero, 0x14
    syscall 0
    jr ra
    nop
}

/* EE kernel call: disables interrupt cause `cause`. */
asm int _DisableIntc(int cause) {
    .set noreorder
    addiu v1, zero, 0x15
    syscall 0
    jr ra
    nop
}

/* EE kernel call: enables DMA channel `channel`'s interrupt. */
asm int _EnableDmac(int channel) {
    .set noreorder
    addiu v1, zero, 0x16
    syscall 0
    jr ra
    nop
}

/* EE kernel call: disables DMA channel `channel`'s interrupt. */
asm int _DisableDmac(int channel) {
    .set noreorder
    addiu v1, zero, 0x17
    syscall 0
    jr ra
    nop
}

/* EE kernel call: calls `handler` with `arg` after `time` horizontal lines. */
asm int _SetAlarm(int time, int *handler, int arg) {
    .set noreorder
    addiu v1, zero, 0xFC
    syscall 0
    jr ra
    nop
}

/* EE kernel call: cancels an alarm. */
asm int _ReleaseAlarm(void) {
    .set noreorder
    addiu v1, zero, 0xFD
    syscall 0
    jr ra
    nop
}

/* EE kernel call (from an interrupt): enables an interrupt cause. */
asm void _iEnableIntc(void) {
    .set noreorder
    addiu v1, zero, -0x1A
    syscall 0
    jr ra
    nop
}

/* EE kernel call (from an interrupt): disables an interrupt cause. */
asm void _iDisableIntc(void) {
    .set noreorder
    addiu v1, zero, -0x1B
    syscall 0
    jr ra
    nop
}

/* EE kernel call (from an interrupt): enables a DMA channel's interrupt. */
asm void _iEnableDmac(void) {
    .set noreorder
    addiu v1, zero, -0x1C
    syscall 0
    jr ra
    nop
}

/* EE kernel call (from an interrupt): disables a DMA channel's interrupt. */
asm void _iDisableDmac(void) {
    .set noreorder
    addiu v1, zero, -0x1D
    syscall 0
    jr ra
    nop
}

/* EE kernel call (from an interrupt): sets an alarm. */
asm int _iSetAlarm(void) {
    .set noreorder
    addiu v1, zero, -0xFE
    syscall 0
    jr ra
    nop
}

/* EE kernel call (from an interrupt): cancels an alarm. */
asm int _iReleaseAlarm(void) {
    .set noreorder
    addiu v1, zero, -0xFF
    syscall 0
    jr ra
    nop
}

/* EE kernel call: creates a thread from `param`; returns its id. */
asm s32 CreateThread(void *param) {
    .set noreorder
    addiu v1, zero, 0x20
    syscall 0
    jr ra
    nop
}

/* EE kernel call: deletes a thread. */
asm int DeleteThread(void) {
    .set noreorder
    addiu v1, zero, 0x21
    syscall 0
    jr ra
    nop
}

/* EE kernel call: starts thread `thid` with `arg`. */
asm s32 StartThread(s32 thid, void *arg) {
    .set noreorder
    addiu v1, zero, 0x22
    syscall 0
    jr ra
    nop
}

/* EE kernel call: ends the calling thread. */
asm int ExitThread(void) {
    .set noreorder
    addiu v1, zero, 0x23
    syscall 0
    jr ra
    nop
}

/* EE kernel call: ends and deletes the calling thread. */
asm void ExitDeleteThread(void) {
    .set noreorder
    addiu v1, zero, 0x24
    syscall 0
    jr ra
    nop
}

/* EE kernel call: stops a thread. */
asm int TerminateThread(void) {
    .set noreorder
    addiu v1, zero, 0x25
    syscall 0
    jr ra
    nop
}

/* EE kernel call (from an interrupt): stops a thread. */
asm int iTerminateThread(void) {
    .set noreorder
    addiu v1, zero, -0x26
    syscall 0
    jr ra
    nop
}

/* EE kernel call: stops thread switching. */
asm int DisableDispatchThread(void) {
    .set noreorder
    addiu v1, zero, 0x27
    syscall 0
    jr ra
    nop
}

/* EE kernel call: allows thread switching. */
asm int EnableDispatchThread(void) {
    .set noreorder
    addiu v1, zero, 0x28
    syscall 0
    jr ra
    nop
}

/* EE kernel call: sets thread `thid`'s priority to `priority`. */
asm s32 ChangeThreadPriority(s32 thid, s32 priority) {
    .set noreorder
    addiu v1, zero, 0x29
    syscall 0
    jr ra
    nop
}

/* EE kernel call (from an interrupt): sets a thread's priority. */
asm int iChangeThreadPriority(void) {
    .set noreorder
    addiu v1, zero, -0x2A
    syscall 0
    jr ra
    nop
}

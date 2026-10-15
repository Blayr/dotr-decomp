#include "common.h"

asm int RotateThreadReadyQueue(int arg0) {
    .set noreorder
    addiu v1, zero, 0x2B
    syscall 0
    jr ra
    nop
}

asm int _iRotateThreadReadyQueue(void) {
    .set noreorder
    addiu v1, zero, -0x2C
    syscall 0
    jr ra
    nop
}

asm int ReleaseWaitThread(void) {
    .set noreorder
    addiu v1, zero, 0x2D
    syscall 0
    jr ra
    nop
}

asm int iReleaseWaitThread(void) {
    .set noreorder
    addiu v1, zero, -0x2E
    syscall 0
    jr ra
    nop
}

asm int GetThreadId(void) {
    .set noreorder
    addiu v1, zero, 0x2F
    syscall 0
    jr ra
    nop
}

asm s32 ReferThreadStatus(s32 arg0, s32 *arg1) {
    .set noreorder
    addiu v1, zero, 0x30
    syscall 0
    jr ra
    nop
}

asm int iReferThreadStatus(void) {
    .set noreorder
    addiu v1, zero, -0x31
    syscall 0
    jr ra
    nop
}

asm int SleepThread(void) {
    .set noreorder
    addiu v1, zero, 0x32
    syscall 0
    jr ra
    nop
}

asm int WakeupThread(void) {
    .set noreorder
    addiu v1, zero, 0x33
    syscall 0
    jr ra
    nop
}

asm int _iWakeupThread(int arg0) {
    .set noreorder
    addiu v1, zero, -0x34
    syscall 0
    jr ra
    nop
}

asm int CancelWakeupThread(void) {
    .set noreorder
    addiu v1, zero, 0x35
    syscall 0
    jr ra
    nop
}

asm int iCancelWakeupThread(void) {
    .set noreorder
    addiu v1, zero, -0x36
    syscall 0
    jr ra
    nop
}

asm int SuspendThread(void) {
    .set noreorder
    addiu v1, zero, 0x37
    syscall 0
    jr ra
    nop
}

asm int _iSuspendThread(int arg0) {
    .set noreorder
    addiu v1, zero, -0x38
    syscall 0
    jr ra
    nop
}

asm int ResumeThread(void) {
    .set noreorder
    addiu v1, zero, 0x39
    syscall 0
    jr ra
    nop
}

asm int iResumeThread(void) {
    .set noreorder
    addiu v1, zero, -0x3A
    syscall 0
    jr ra
    nop
}

asm int JoinThread(void) {
    .set noreorder
    addiu v1, zero, 0x3B
    syscall 0
    jr ra
    nop
}

asm int RFU060(void) {
    .set noreorder
    addiu v1, zero, 0x3C
    syscall 0
    jr ra
    nop
}

asm int RFU061(void) {
    .set noreorder
    addiu v1, zero, 0x3D
    syscall 0
    jr ra
    nop
}

asm unsigned int EndOfHeap(void) {
    .set noreorder
    addiu v1, zero, 0x3E
    syscall 0
    jr ra
    nop
}

asm int RFU063(void) {
    .set noreorder
    addiu v1, zero, 0x3F
    syscall 0
    jr ra
    nop
}

asm int CreateSema(void *arg0) {
    .set noreorder
    addiu v1, zero, 0x40
    syscall 0
    jr ra
    nop
}

asm int DeleteSema(int arg0) {
    .set noreorder
    addiu v1, zero, 0x41
    syscall 0
    jr ra
    nop
}

asm void SignalSema(int arg0) {
    .set noreorder
    addiu v1, zero, 0x42
    syscall 0
    jr ra
    nop
}

asm void iSignalSema(int arg0) {
    .set noreorder
    addiu v1, zero, -0x43
    syscall 0
    jr ra
    nop
}

asm void WaitSema(int arg0) {
    .set noreorder
    addiu v1, zero, 0x44
    syscall 0
    jr ra
    nop
}

asm int PollSema(int arg0) {
    .set noreorder
    addiu v1, zero, 0x45
    syscall 0
    jr ra
    nop
}

asm int iPollSema(void) {
    .set noreorder
    addiu v1, zero, -0x46
    syscall 0
    jr ra
    nop
}

asm int ReferSemaStatus(void) {
    .set noreorder
    addiu v1, zero, 0x47
    syscall 0
    jr ra
    nop
}

asm int iReferSemaStatus(void) {
    .set noreorder
    addiu v1, zero, -0x48
    syscall 0
    jr ra
    nop
}

asm int RFU073(void) {
    .set noreorder
    addiu v1, zero, 0x49
    syscall 0
    jr ra
    nop
}

asm int SetOsdConfigParam(unsigned int *arg0) {
    .set noreorder
    addiu v1, zero, 0x4A
    syscall 0
    jr ra
    nop
}

asm int GetOsdConfigParam(unsigned int *arg0) {
    .set noreorder
    addiu v1, zero, 0x4B
    syscall 0
    jr ra
    nop
}

asm int GetGsHParam(void) {
    .set noreorder
    addiu v1, zero, 0x4C
    syscall 0
    jr ra
    nop
}

asm int GetGsVParam(void) {
    .set noreorder
    addiu v1, zero, 0x4D
    syscall 0
    jr ra
    nop
}

asm int SetGsHParam(void) {
    .set noreorder
    addiu v1, zero, 0x4E
    syscall 0
    jr ra
    nop
}

asm int SetGsVParam(void) {
    .set noreorder
    addiu v1, zero, 0x4F
    syscall 0
    jr ra
    nop
}

asm int RFU080_CreateEventFlag(void) {
    .set noreorder
    addiu v1, zero, 0x50
    syscall 0
    jr ra
    nop
}

asm int RFU081_DeleteEventFlag(void) {
    .set noreorder
    addiu v1, zero, 0x51
    syscall 0
    jr ra
    nop
}

asm int RFU082_SetEventFlag(void) {
    .set noreorder
    addiu v1, zero, 0x52
    syscall 0
    jr ra
    nop
}

asm int RFU083_iSetEventFlag(void) {
    .set noreorder
    addiu v1, zero, -0x53
    syscall 0
    jr ra
    nop
}

asm int RFU084_ClearEventFlag(void) {
    .set noreorder
    addiu v1, zero, 0x54
    syscall 0
    jr ra
    nop
}

asm int RFU085_iClearEventFlag(void) {
    .set noreorder
    addiu v1, zero, -0x55
    syscall 0
    jr ra
    nop
}

asm int RFU086_WaitEvnetFlag(void) {
    .set noreorder
    addiu v1, zero, 0x56
    syscall 0
    jr ra
    nop
}

asm int RFU087_PollEvnetFlag(void) {
    .set noreorder
    addiu v1, zero, 0x57
    syscall 0
    jr ra
    nop
}

asm int RFU088_iPollEvnetFlag(void) {
    .set noreorder
    addiu v1, zero, -0x58
    syscall 0
    jr ra
    nop
}

asm int RFU089_ReferEventFlagStatus(void) {
    .set noreorder
    addiu v1, zero, 0x59
    syscall 0
    jr ra
    nop
}

asm int RFU090_iReferEventFlagStatus(void) {
    .set noreorder
    addiu v1, zero, -0x5A
    syscall 0
    jr ra
    nop
}

asm int RFU091(void) {
    .set noreorder
    addiu v1, zero, 0x5B
    syscall 0
    jr ra
    nop
}

asm int EnableIntcHandler(void) {
    .set noreorder
    addiu v1, zero, 0x5C
    syscall 0
    jr ra
    nop
}

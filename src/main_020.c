#include "common.h"

/* EE kernel call: moves the next thread of priority `priority` to the back of its queue. */
asm int RotateThreadReadyQueue(int priority) {
    .set noreorder
    addiu v1, zero, 0x2B
    syscall 0
    jr ra
    nop
}

/* EE kernel call (from an interrupt): rotates a priority's ready queue. */
asm int _iRotateThreadReadyQueue(void) {
    .set noreorder
    addiu v1, zero, -0x2C
    syscall 0
    jr ra
    nop
}

/* EE kernel call: releases a waiting thread. */
asm int ReleaseWaitThread(void) {
    .set noreorder
    addiu v1, zero, 0x2D
    syscall 0
    jr ra
    nop
}

/* EE kernel call (from an interrupt): releases a waiting thread. */
asm int iReleaseWaitThread(void) {
    .set noreorder
    addiu v1, zero, -0x2E
    syscall 0
    jr ra
    nop
}

/* EE kernel call: the calling thread's id. */
asm int GetThreadId(void) {
    .set noreorder
    addiu v1, zero, 0x2F
    syscall 0
    jr ra
    nop
}

/* EE kernel call: thread `thid`'s status into `info`. */
asm s32 ReferThreadStatus(s32 thid, s32 *info) {
    .set noreorder
    addiu v1, zero, 0x30
    syscall 0
    jr ra
    nop
}

/* EE kernel call (from an interrupt): a thread's status. */
asm int iReferThreadStatus(void) {
    .set noreorder
    addiu v1, zero, -0x31
    syscall 0
    jr ra
    nop
}

/* EE kernel call: puts the calling thread to sleep until woken. */
asm int SleepThread(void) {
    .set noreorder
    addiu v1, zero, 0x32
    syscall 0
    jr ra
    nop
}

/* EE kernel call: wakes a sleeping thread. */
asm int WakeupThread(void) {
    .set noreorder
    addiu v1, zero, 0x33
    syscall 0
    jr ra
    nop
}

/* EE kernel call (from an interrupt): wakes thread `thid`. */
asm int _iWakeupThread(int thid) {
    .set noreorder
    addiu v1, zero, -0x34
    syscall 0
    jr ra
    nop
}

/* EE kernel call: cancels pending wake-ups of a thread. */
asm int CancelWakeupThread(void) {
    .set noreorder
    addiu v1, zero, 0x35
    syscall 0
    jr ra
    nop
}

/* EE kernel call (from an interrupt): cancels pending wake-ups. */
asm int iCancelWakeupThread(void) {
    .set noreorder
    addiu v1, zero, -0x36
    syscall 0
    jr ra
    nop
}

/* EE kernel call: suspends a thread. */
asm int SuspendThread(void) {
    .set noreorder
    addiu v1, zero, 0x37
    syscall 0
    jr ra
    nop
}

/* EE kernel call (from an interrupt): suspends thread `thid`. */
asm int _iSuspendThread(int thid) {
    .set noreorder
    addiu v1, zero, -0x38
    syscall 0
    jr ra
    nop
}

/* EE kernel call: resumes a suspended thread. */
asm int ResumeThread(void) {
    .set noreorder
    addiu v1, zero, 0x39
    syscall 0
    jr ra
    nop
}

/* EE kernel call (from an interrupt): resumes a thread. */
asm int iResumeThread(void) {
    .set noreorder
    addiu v1, zero, -0x3A
    syscall 0
    jr ra
    nop
}

/* EE kernel call: waits for a thread. */
asm int JoinThread(void) {
    .set noreorder
    addiu v1, zero, 0x3B
    syscall 0
    jr ra
    nop
}

/* EE kernel call 60 (reserved). */
asm int RFU060(void) {
    .set noreorder
    addiu v1, zero, 0x3C
    syscall 0
    jr ra
    nop
}

/* EE kernel call 61 (reserved). */
asm int RFU061(void) {
    .set noreorder
    addiu v1, zero, 0x3D
    syscall 0
    jr ra
    nop
}

/* EE kernel call: the end of the program's heap. */
asm unsigned int EndOfHeap(void) {
    .set noreorder
    addiu v1, zero, 0x3E
    syscall 0
    jr ra
    nop
}

/* EE kernel call 63 (reserved). */
asm int RFU063(void) {
    .set noreorder
    addiu v1, zero, 0x3F
    syscall 0
    jr ra
    nop
}

/* EE kernel call: creates a semaphore from `param`; returns its id. */
asm int CreateSema(void *param) {
    .set noreorder
    addiu v1, zero, 0x40
    syscall 0
    jr ra
    nop
}

/* EE kernel call: deletes semaphore `sid`. */
asm int DeleteSema(int sid) {
    .set noreorder
    addiu v1, zero, 0x41
    syscall 0
    jr ra
    nop
}

/* EE kernel call: signals semaphore `sid`. */
asm void SignalSema(int sid) {
    .set noreorder
    addiu v1, zero, 0x42
    syscall 0
    jr ra
    nop
}

/* EE kernel call (from an interrupt): signals semaphore `sid`. */
asm void iSignalSema(int sid) {
    .set noreorder
    addiu v1, zero, -0x43
    syscall 0
    jr ra
    nop
}

/* EE kernel call: waits on semaphore `sid`. */
asm void WaitSema(int sid) {
    .set noreorder
    addiu v1, zero, 0x44
    syscall 0
    jr ra
    nop
}

/* EE kernel call: takes semaphore `sid` if it is free, without waiting. */
asm int PollSema(int sid) {
    .set noreorder
    addiu v1, zero, 0x45
    syscall 0
    jr ra
    nop
}

/* EE kernel call (from an interrupt): polls a semaphore. */
asm int iPollSema(void) {
    .set noreorder
    addiu v1, zero, -0x46
    syscall 0
    jr ra
    nop
}

/* EE kernel call: a semaphore's status. */
asm int ReferSemaStatus(void) {
    .set noreorder
    addiu v1, zero, 0x47
    syscall 0
    jr ra
    nop
}

/* EE kernel call (from an interrupt): a semaphore's status. */
asm int iReferSemaStatus(void) {
    .set noreorder
    addiu v1, zero, -0x48
    syscall 0
    jr ra
    nop
}

/* EE kernel call 73 (reserved). */
asm int RFU073(void) {
    .set noreorder
    addiu v1, zero, 0x49
    syscall 0
    jr ra
    nop
}

/* EE kernel call: sets the console's settings from `param`. */
asm int SetOsdConfigParam(unsigned int *param) {
    .set noreorder
    addiu v1, zero, 0x4A
    syscall 0
    jr ra
    nop
}

/* EE kernel call: the console's settings (language, screen) into `param`. */
asm int GetOsdConfigParam(unsigned int *param) {
    .set noreorder
    addiu v1, zero, 0x4B
    syscall 0
    jr ra
    nop
}

/* EE kernel call: the GS horizontal settings. */
asm int GetGsHParam(void) {
    .set noreorder
    addiu v1, zero, 0x4C
    syscall 0
    jr ra
    nop
}

/* EE kernel call: the GS vertical settings. */
asm int GetGsVParam(void) {
    .set noreorder
    addiu v1, zero, 0x4D
    syscall 0
    jr ra
    nop
}

/* EE kernel call: sets the GS horizontal settings. */
asm int SetGsHParam(void) {
    .set noreorder
    addiu v1, zero, 0x4E
    syscall 0
    jr ra
    nop
}

/* EE kernel call: sets the GS vertical settings. */
asm int SetGsVParam(void) {
    .set noreorder
    addiu v1, zero, 0x4F
    syscall 0
    jr ra
    nop
}

/* EE kernel call 80 (reserved: create event flag). */
asm int RFU080_CreateEventFlag(void) {
    .set noreorder
    addiu v1, zero, 0x50
    syscall 0
    jr ra
    nop
}

/* EE kernel call 81 (reserved: delete event flag). */
asm int RFU081_DeleteEventFlag(void) {
    .set noreorder
    addiu v1, zero, 0x51
    syscall 0
    jr ra
    nop
}

/* EE kernel call 82 (reserved: set event flag). */
asm int RFU082_SetEventFlag(void) {
    .set noreorder
    addiu v1, zero, 0x52
    syscall 0
    jr ra
    nop
}

/* EE kernel call 83 (reserved: set event flag from an interrupt). */
asm int RFU083_iSetEventFlag(void) {
    .set noreorder
    addiu v1, zero, -0x53
    syscall 0
    jr ra
    nop
}

/* EE kernel call 84 (reserved: clear event flag). */
asm int RFU084_ClearEventFlag(void) {
    .set noreorder
    addiu v1, zero, 0x54
    syscall 0
    jr ra
    nop
}

/* EE kernel call 85 (reserved: clear event flag from an interrupt). */
asm int RFU085_iClearEventFlag(void) {
    .set noreorder
    addiu v1, zero, -0x55
    syscall 0
    jr ra
    nop
}

/* EE kernel call 86 (reserved: wait for event flag). */
asm int RFU086_WaitEvnetFlag(void) {
    .set noreorder
    addiu v1, zero, 0x56
    syscall 0
    jr ra
    nop
}

/* EE kernel call 87 (reserved: poll event flag). */
asm int RFU087_PollEvnetFlag(void) {
    .set noreorder
    addiu v1, zero, 0x57
    syscall 0
    jr ra
    nop
}

/* EE kernel call 88 (reserved: poll event flag from an interrupt). */
asm int RFU088_iPollEvnetFlag(void) {
    .set noreorder
    addiu v1, zero, -0x58
    syscall 0
    jr ra
    nop
}

/* EE kernel call 89 (reserved: event flag status). */
asm int RFU089_ReferEventFlagStatus(void) {
    .set noreorder
    addiu v1, zero, 0x59
    syscall 0
    jr ra
    nop
}

/* EE kernel call 90 (reserved: event flag status from an interrupt). */
asm int RFU090_iReferEventFlagStatus(void) {
    .set noreorder
    addiu v1, zero, -0x5A
    syscall 0
    jr ra
    nop
}

/* EE kernel call 91 (reserved). */
asm int RFU091(void) {
    .set noreorder
    addiu v1, zero, 0x5B
    syscall 0
    jr ra
    nop
}

/* EE kernel call: enables an interrupt handler. */
asm int EnableIntcHandler(void) {
    .set noreorder
    addiu v1, zero, 0x5C
    syscall 0
    jr ra
    nop
}

#include "common.h"

/* EE kernel call (from an interrupt): enables an interrupt handler. */
int iEnableIntcHandler(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,-0x5C\n\tsyscall" : "=r" (ret));
    return ret;
}

/* EE kernel call: disables an interrupt handler. */
int DisableIntcHandler(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x5D\n\tsyscall" : "=r" (ret));
    return ret;
}

/* EE kernel call (from an interrupt): disables an interrupt handler. */
int iDisableIntcHandler(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,-0x5D\n\tsyscall" : "=r" (ret));
    return ret;
}

/* EE kernel call: enables a DMA handler. */
int EnableDmacHandler(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x5E\n\tsyscall" : "=r" (ret));
    return ret;
}

/* EE kernel call (from an interrupt): enables a DMA handler. */
int iEnableDmacHandler(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,-0x5E\n\tsyscall" : "=r" (ret));
    return ret;
}

/* EE kernel call: disables a DMA handler. */
int DisableDmacHandler(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x5F\n\tsyscall" : "=r" (ret));
    return ret;
}

/* EE kernel call (from an interrupt): disables a DMA handler. */
int iDisableDmacHandler(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,-0x5F\n\tsyscall" : "=r" (ret));
    return ret;
}

/* EE kernel call: sets the KSEG0 cache mode. */
int KSeg0(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x60\n\tsyscall" : "=r" (ret));
    return ret;
}

/* EE kernel call: turns a cache on. */
int EnableCache(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x61\n\tsyscall" : "=r" (ret));
    return ret;
}

/* EE kernel call: turns a cache off. */
int DisableCache(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x62\n\tsyscall" : "=r" (ret));
    return ret;
}

/* EE kernel call: reads a COP0 register. */
int GetCop0(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x63\n\tsyscall" : "=r" (ret));
    return ret;
}

/* EE kernel call: writes back or clears cache `mode` (0 data, 2 instruction). */
void FlushCache(int mode) {
    __asm__ __volatile__("addiu\t$3,$0,0x64\n\tsyscall");
}

/* EE kernel call: CPU configuration. */
int CpuConfig(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x66\n\tsyscall" : "=r" (ret));
    return ret;
}

/* EE kernel call (from an interrupt): reads a COP0 register. */
int iGetCop0(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,-0x67\n\tsyscall" : "=r" (ret));
    return ret;
}

/* EE kernel call (from an interrupt): writes back or clears cache `mode`. */
void iFlushCache(s32 mode) {
    __asm__ __volatile__("addiu\t$3,$0,-0x68\n\tsyscall");
}

/* EE kernel call (from an interrupt): CPU configuration. */
int iCpuConfig(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,-0x6A\n\tsyscall" : "=r" (ret));
    return ret;
}

/* EE kernel call: stops the SIF DMA to the IOP. */
int sceSifStopDma(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x6B\n\tsyscall" : "=r" (ret));
    return ret;
}

/* EE kernel call: sets the CPU timer handler. */
int SetCPUTimerHandler(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x6C\n\tsyscall" : "=r" (ret));
    return ret;
}

/* EE kernel call: sets the CPU timer. */
int SetCPUTimer(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x6D\n\tsyscall" : "=r" (ret));
    return ret;
}

/* EE kernel call: sets extended console settings. */
int SetOsdConfigParam2(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x6E\n\tsyscall" : "=r" (ret));
    return ret;
}

/* EE kernel call: extended console settings. */
int GetOsdConfigParam2(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x6F\n\tsyscall" : "=r" (ret));
    return ret;
}

/* EE kernel call: the GS interrupt mask. */
u64 GsGetIMR(void) {
    register u64 ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x70\n\tsyscall" : "=r" (ret));
    return ret;
}

/* EE kernel call (from an interrupt): the GS interrupt mask. */
int iGsGetIMR(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,-0x70\n\tsyscall" : "=r" (ret));
    return ret;
}

/* EE kernel call: sets the GS interrupt mask to `imr`. */
unsigned long long GsPutIMR(unsigned long long imr) {
    register unsigned long long ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x71\n\tsyscall" : "=r" (ret));
    return ret;
}

/* EE kernel call (from an interrupt): sets the GS interrupt mask. */
int iGsPutIMR(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,-0x71\n\tsyscall" : "=r" (ret));
    return ret;
}

/* EE kernel call: sets the PGIF handler. */
int SetPgifHandler(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x72\n\tsyscall" : "=r" (ret));
    return ret;
}

/* EE kernel call: sets the words the kernel marks at each vertical blank (`flag`, `csr`). */
int SetVSyncFlag(void *flag, long long *csr) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x73\n\tsyscall" : "=r" (ret));
    return ret;
}

/* EE kernel call 116 (reserved). */
int RFU116(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x74\n\tsyscall" : "=r" (ret));
    return ret;
}

/* EE kernel call: kernel debug print. */
int print(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x75\n\tsyscall" : "=r" (ret));
    return ret;
}

/* EE kernel call: whether SIF DMA transfer `id` is still running. */
int sceSifDmaStat(int id) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x76\n\tsyscall" : "=r" (ret));
    return ret;
}

/* EE kernel call (from an interrupt): SIF DMA transfer status. */
int isceSifDmaStat(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,-0x76\n\tsyscall" : "=r" (ret));
    return ret;
}

/* EE kernel call: starts `count` SIF DMA transfers from list `list`; returns its id. */
int sceSifSetDma(int *list, int count) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x77\n\tsyscall" : "=r" (ret));
    return ret;
}

/* EE kernel call (from an interrupt): starts SIF DMA transfers. */
int isceSifSetDma(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,-0x77\n\tsyscall" : "=r" (ret));
    return ret;
}

/* EE kernel call: sets up the SIF receive chain. */
int sceSifSetDChain(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x78\n\tsyscall" : "=r" (ret));
    return ret;
}

/* EE kernel call (from an interrupt): sets up the SIF receive chain. */
int isceSifSetDChain(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,-0x78\n\tsyscall" : "=r" (ret));
    return ret;
}

/* EE kernel call: sets SIF register `reg` to `val`. */
int sceSifSetReg(u32 reg, int val) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x79\n\tsyscall" : "=r" (ret));
    return ret;
}

/* EE kernel call: SIF register `reg`. */
int sceSifGetReg(int reg) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x7A\n\tsyscall" : "=r" (ret));
    return ret;
}

/* EE kernel call: returns to the console's browser with `argc`, `argv`. */
int ExecOSD(int argc, int argv) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x7B\n\tsyscall" : "=r" (ret));
    return ret;
}

/* EE kernel call: DECI2 debug service call `func` with `param`. */
int Deci2Call(int func, void *param) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x7C\n\tsyscall" : "=r" (ret));
    return ret;
}

/* EE kernel call: the console mode. */
int PSMode(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x7D\n\tsyscall" : "=r" (ret));
    return ret;
}

/* EE kernel call: the machine type. */
int MachineType(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x7E\n\tsyscall" : "=r" (ret));
    return ret;
}

/* EE kernel call: the main memory size. */
int GetMemorySize(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x7F\n\tsyscall" : "=r" (ret));
    return ret;
}

/* EE kernel call 0x82. */
int func_0017BD50(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x82\n\tsyscall" : "=r" (ret));
    return ret;
}

/* sceResetttyinit (JP symbol beside it): the tty-init done flag back to 0 */

void func_0017BD60(void) {
    ttyinit = 0;
}

/* Waits for the GS vertical-blank flag (clears it, waits for it, clears it again) with interrupts held. */
void func_0017BD70(void) {
    s32 temp_v0;
    s32 temp_v0_2;

    temp_v0 = func_001843E0();
    *(volatile s32 *)0x1000F000 = 4;
    __asm__ volatile("sync");
    if (temp_v0 != 0) {
        func_00184428();
    }
    do {

    } while (!(*(volatile s32 *)0x1000F000 & 4));
    temp_v0_2 = func_001843E0();
    *(volatile s32 *)0x1000F000 = 4;
    __asm__ volatile("sync");
    if (temp_v0_2 != 0) {
        func_00184428();
    }
}

/* Waits for the next vertical blank through the kernel's SetVSyncFlag words; returns the value the kernel stored. */
s64 func_0017BE00(void) {
    volatile s32 done;
    volatile s64 val;
    s32 eie;

    done = 0;
    SetVSyncFlag((void *)&done, (s64 *)&val);
    eie = func_001843E0();
    *(volatile s32 *)0x1000F000 = 4;
    __asm__ volatile("sync");
    if (eie) {
        func_00184428();
    }
    while (!(*(volatile s32 *)0x1000F000 & 4) && done == 0) {
    }
    eie = func_001843E0();
    *(volatile s32 *)0x1000F000 = 4;
    __asm__ volatile("sync");
    if (eie) {
        func_00184428();
    }
    return val;
}

/* write: adapted from gt4-decomp (MIT), see THIRD_PARTY_NOTICES.md */

s32 write(s32 mode, s32 a, s32 b) {
    extern s32 sceTtyWrite(const char *, s32);

    if (mode == 1 || mode == 2) {
        if (ttyinit == 0) {
            if (sceTtyInit() == 0)
                return -1;
            ttyinit = 1;
        }
        return sceTtyWrite((const char *)a, b);
    }
    return -1;
}

/* newlib system call: reads `n` bytes into `buf` from file `fd` (the debug console only). */
s32 read(s32 fd, char *buf, s32 n) {
    if (fd == 0) {
        if (ttyinit == 0) {
            if (sceTtyInit() == 0) {
                return -1;
            }
            ttyinit = 1;
        }
        return sceTtyRead(buf, n);
    }
    return -1;
}

/* newlib system call: no files here (sets errno, returns -1). */
s32 open(void) {
    *(s32 *)__errno() = 5;
    return -1;
}

/* newlib system call: does nothing. */
s32 close(void) {
    return -1;
}

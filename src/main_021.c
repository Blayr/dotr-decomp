#include "common.h"

int iEnableIntcHandler(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,-0x5C\n\tsyscall" : "=r" (ret));
    return ret;
}

int DisableIntcHandler(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x5D\n\tsyscall" : "=r" (ret));
    return ret;
}

int iDisableIntcHandler(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,-0x5D\n\tsyscall" : "=r" (ret));
    return ret;
}

int EnableDmacHandler(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x5E\n\tsyscall" : "=r" (ret));
    return ret;
}

int iEnableDmacHandler(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,-0x5E\n\tsyscall" : "=r" (ret));
    return ret;
}

int DisableDmacHandler(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x5F\n\tsyscall" : "=r" (ret));
    return ret;
}

int iDisableDmacHandler(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,-0x5F\n\tsyscall" : "=r" (ret));
    return ret;
}

int KSeg0(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x60\n\tsyscall" : "=r" (ret));
    return ret;
}

int EnableCache(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x61\n\tsyscall" : "=r" (ret));
    return ret;
}

int DisableCache(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x62\n\tsyscall" : "=r" (ret));
    return ret;
}

int GetCop0(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x63\n\tsyscall" : "=r" (ret));
    return ret;
}

void FlushCache(int arg0) {
    __asm__ __volatile__("addiu\t$3,$0,0x64\n\tsyscall");
}

int CpuConfig(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x66\n\tsyscall" : "=r" (ret));
    return ret;
}

int iGetCop0(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,-0x67\n\tsyscall" : "=r" (ret));
    return ret;
}

void iFlushCache(s32 arg0) {
    __asm__ __volatile__("addiu\t$3,$0,-0x68\n\tsyscall");
}

int iCpuConfig(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,-0x6A\n\tsyscall" : "=r" (ret));
    return ret;
}

int sceSifStopDma(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x6B\n\tsyscall" : "=r" (ret));
    return ret;
}

int SetCPUTimerHandler(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x6C\n\tsyscall" : "=r" (ret));
    return ret;
}

int SetCPUTimer(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x6D\n\tsyscall" : "=r" (ret));
    return ret;
}

int SetOsdConfigParam2(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x6E\n\tsyscall" : "=r" (ret));
    return ret;
}

int GetOsdConfigParam2(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x6F\n\tsyscall" : "=r" (ret));
    return ret;
}

u64 GsGetIMR(void) {
    register u64 ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x70\n\tsyscall" : "=r" (ret));
    return ret;
}

int iGsGetIMR(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,-0x70\n\tsyscall" : "=r" (ret));
    return ret;
}

unsigned long long GsPutIMR(unsigned long long arg0) {
    register unsigned long long ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x71\n\tsyscall" : "=r" (ret));
    return ret;
}

int iGsPutIMR(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,-0x71\n\tsyscall" : "=r" (ret));
    return ret;
}

int SetPgifHandler(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x72\n\tsyscall" : "=r" (ret));
    return ret;
}

int SetVSyncFlag(void *arg0, long long *arg1) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x73\n\tsyscall" : "=r" (ret));
    return ret;
}

int RFU116(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x74\n\tsyscall" : "=r" (ret));
    return ret;
}

int print(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x75\n\tsyscall" : "=r" (ret));
    return ret;
}

int sceSifDmaStat(int arg0) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x76\n\tsyscall" : "=r" (ret));
    return ret;
}

int isceSifDmaStat(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,-0x76\n\tsyscall" : "=r" (ret));
    return ret;
}

int sceSifSetDma(int *arg0, int arg1) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x77\n\tsyscall" : "=r" (ret));
    return ret;
}

int isceSifSetDma(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,-0x77\n\tsyscall" : "=r" (ret));
    return ret;
}

int sceSifSetDChain(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x78\n\tsyscall" : "=r" (ret));
    return ret;
}

int isceSifSetDChain(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,-0x78\n\tsyscall" : "=r" (ret));
    return ret;
}

int sceSifSetReg(u32 reg, int val) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x79\n\tsyscall" : "=r" (ret));
    return ret;
}

int sceSifGetReg(int arg0) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x7A\n\tsyscall" : "=r" (ret));
    return ret;
}

int ExecOSD(int arg0, int arg1) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x7B\n\tsyscall" : "=r" (ret));
    return ret;
}

int Deci2Call(int arg0, void *arg1) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x7C\n\tsyscall" : "=r" (ret));
    return ret;
}

int PSMode(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x7D\n\tsyscall" : "=r" (ret));
    return ret;
}

int MachineType(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x7E\n\tsyscall" : "=r" (ret));
    return ret;
}

int GetMemorySize(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x7F\n\tsyscall" : "=r" (ret));
    return ret;
}

int func_0017BD50(void) {
    register int ret __asm__("$2");
    __asm__ __volatile__("addiu\t$3,$0,0x82\n\tsyscall" : "=r" (ret));
    return ret;
}

/* sceResetttyinit (JP symbol beside it): the tty-init done flag back to 0 */

void func_0017BD60(void) {
    D_0028C250 = 0;
}

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
        if (D_0028C250 == 0) {
            if (sceTtyInit() == 0)
                return -1;
            D_0028C250 = 1;
        }
        return sceTtyWrite((const char *)a, b);
    }
    return -1;
}

s32 read(s32 fd, char *buf, s32 n) {
    if (fd == 0) {
        if (D_0028C250 == 0) {
            if (sceTtyInit() == 0) {
                return -1;
            }
            D_0028C250 = 1;
        }
        return sceTtyRead(buf, n);
    }
    return -1;
}

s32 open(void) {
    *(s32 *)__errno() = 5;
    return -1;
}

s32 close(void) {
    return -1;
}

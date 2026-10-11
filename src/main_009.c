#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_009", func_00135790);

INCLUDE_ASM("asm/nonmatchings/main_009", func_00135970);

INCLUDE_ASM("asm/nonmatchings/main_009", func_00135D50);

void func_00135FB0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28) {
    func_0027DE20(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
                  arg_sp0, arg_sp8, arg_sp10, arg_sp18, arg_sp20,
                  1, 0x898, arg_sp28);
}

void func_00136010(void *arg0) {
    s32 temp_v0;

    temp_v0 = func_00136060(arg0);
    if (temp_v0 >= 0) {
        *(s16 *)((u8 *)arg0 + 4) = 0x3FF;
        *(u32 *)((u8 *)arg0 + 8) = (temp_v0 << 16) | *(u16 *)((u8 *)arg0 + 8);
        return;
    }
    *(s16 *)((u8 *)arg0 + 4) = 0x5FF;
}

INCLUDE_ASM("asm/nonmatchings/main_009", func_00136060);

INCLUDE_ASM("asm/nonmatchings/main_009", func_001360E0);

INCLUDE_ASM("asm/nonmatchings/main_009", func_00136210);

INCLUDE_ASM("asm/nonmatchings/main_009", func_00136490);

INCLUDE_ASM("asm/nonmatchings/main_009", func_00136890);

INCLUDE_ASM("asm/nonmatchings/main_009", func_00136980);

INCLUDE_ASM("asm/nonmatchings/main_009", func_00136B80);

INCLUDE_ASM("asm/nonmatchings/main_009", func_00136D60);

INCLUDE_ASM("asm/nonmatchings/main_009", func_00136F30);

INCLUDE_ASM("asm/nonmatchings/main_009", func_00137120);

INCLUDE_ASM("asm/nonmatchings/main_009", func_001374D0);

INCLUDE_ASM("asm/nonmatchings/main_009", func_001379F0);

INCLUDE_ASM("asm/nonmatchings/main_009", func_00137FB0);

INCLUDE_ASM("asm/nonmatchings/main_009", func_00138780);

INCLUDE_ASM("asm/nonmatchings/main_009", func_00138950);

INCLUDE_ASM("asm/nonmatchings/main_009", func_00138B60);

INCLUDE_ASM("asm/nonmatchings/main_009", func_00138DB0);

INCLUDE_ASM("asm/nonmatchings/main_009", func_00138EA0);

INCLUDE_ASM("asm/nonmatchings/main_009", func_00138F90);

INCLUDE_ASM("asm/nonmatchings/main_009", func_00139080);

INCLUDE_ASM("asm/nonmatchings/main_009", func_00139180);

INCLUDE_ASM("asm/nonmatchings/main_009", func_001396C0);

INCLUDE_ASM("asm/nonmatchings/main_009", func_00139890);

INCLUDE_ASM("asm/nonmatchings/main_009", func_00139D90);

INCLUDE_ASM("asm/nonmatchings/main_009", func_0013A010);

INCLUDE_ASM("asm/nonmatchings/main_009", func_0013A400);

void func_0013A6B0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28) {
    func_0027DE20(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
                  arg_sp0, arg_sp8, arg_sp10, arg_sp18, arg_sp20,
                  0, 2500, arg_sp28);
}

INCLUDE_ASM("asm/nonmatchings/main_009", func_0013A710);

INCLUDE_ASM("asm/nonmatchings/main_009", func_0013A870);

INCLUDE_ASM("asm/nonmatchings/main_009", func_0013A9A0);

INCLUDE_ASM("asm/nonmatchings/main_009", func_0013AA40);

INCLUDE_ASM("asm/nonmatchings/main_009", func_0013AB70);

INCLUDE_ASM("asm/nonmatchings/main_009", func_0013AE00);

INCLUDE_ASM("asm/nonmatchings/main_009", func_0013B130);

INCLUDE_ASM("asm/nonmatchings/main_009", func_0013B220);

INCLUDE_ASM("asm/nonmatchings/main_009", func_0013B420);

INCLUDE_ASM("asm/nonmatchings/main_009", func_0013B600);

s32 func_0013B7E0(s32 arg0) {
    if ((func_0026FCE0(arg0) >> 5) != 0) {
        return 1;
    }
    if (func_0026FC10(arg0) == 1) {
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_009", func_0013B840);

INCLUDE_ASM("asm/nonmatchings/main_009", func_0013BA30);

INCLUDE_ASM("asm/nonmatchings/main_009", func_0013BE60);

INCLUDE_ASM("asm/nonmatchings/main_009", func_0013C430);

INCLUDE_ASM("asm/nonmatchings/main_009", func_0013CA10);

s32 func_0013D280(void) {
    if (func_0013A870(func_001DE540()) < 0) {
        return 1;
    }
    return 0;
}

s32 func_0013D2C0(s32 arg0) {
    u16 buf[0x16];
    s32 i;
    s32 a;
    s32 b;
    s32 r;

    for (i = 0; i < 0x16; i++) {
        buf[i] = 0xFFFF;
    }
    func_0027C2C0(arg0 == 0 ? 1 : 0, buf, 0x1D, 0, 0);
    a = func_0027B650(buf);
    for (i = 0; i < 0x16; i++) {
        buf[i] = 0xFFFF;
    }
    func_0027C070(arg0, buf, 0x1D, 1);
    b = func_0027B650(buf);
    if (a >= 0) {
        if (b >= 0) {
            r = func_001E1090(a >> 8, a & 0xFF);
            if (func_002781F0(a, b, r & 0xFF, r >> 8) > 0) {
                return a;
            }
        }
    }
    return -1;
}

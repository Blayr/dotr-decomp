#include "common.h"

void func_0018A378(s32 arg0) {
    *(s32 *)0x10002010 = (*(s32 *)0x10002010 & 0xFF7FFFFF) | (arg0 << 0x17);
}

INCLUDE_ASM("asm/nonmatchings/main_029", func_0018A3A0);

s32 func_0018A590(s32 arg0) {
    return func_0018B6D8(arg0, 3);
}

INCLUDE_ASM("asm/nonmatchings/main_029", func_0018A5B0);

INCLUDE_ASM("asm/nonmatchings/main_029", func_0018A738);

s32 func_0018A848(void *arg0) {
    s32 n;
    s32 ret;

    (*(s32 *)((u8 *)arg0 + 0x810)) = 0;
    (*(s32 *)((u8 *)arg0 + 0x814)) = 0;
    n = (*(s32 *)((u8 *)arg0 + 0x12C)) * (*(s32 *)((u8 *)arg0 + 0x130));
    if ((*(s32 *)((u8 *)arg0 + 0x174)) != 3) {
        n >>= 1;
    }
    do {
        ret = func_0018AA80(arg0, n);
    } while (ret == 1 || ret == 3);
    func_0018B580(arg0);
    if (func_0018A3A0(arg0) == 0) {
        ret = 2;
    }
    while ((*(volatile u32 *)0x1000D400 >> 8) & 1) {
    }
    if (ret == 0) {
        func_001893A8(arg0, (*(s32 *)((u8 *)arg0 + 0x810)) == 0);
    }
    if (ret == 1 || ret == 2) {
        func_0018F7B0((s32)arg0, &D_002BC7A0);
    }
    return ret == 0;
}

s32 func_0018A950(void *arg0, s32 arg1, s32 *arg2, s32 *arg3, void *arg4) {
    s32 temp_s3;
    s32 temp_v0;
    s32 temp_v0_2;

    (*(s32 *)((u8 *)arg0 + 0x11C)) = 0;
    func_0018BB98(arg0);
    temp_v0 = func_0018B850(arg0, 0x20);
    if ((u32) (temp_v0 - 0x101) >= 0xAFU) {
        func_0018F778((s32) arg0, &D_002BC7C0, temp_v0);
        return 2;
    }
    func_0018B958(arg0, 0x20);
    temp_s3 = ((s32 (*)(void *))func_0018BC18)(arg0);
    temp_v0_2 = func_0018A738(arg0);
    *arg3 = temp_v0_2;
    if ((*(s32 *)((u8 *)arg0 + 0x11C)) != 0) {
        func_0018F7B0((s32) arg0, &D_002BC7E8);
        return 1;
    }
    *arg2 = (((((temp_s3 << 7) + (temp_v0 & 0xFF)) - 1) * (*(s32 *)((u8 *)arg0 + 0x12C))) + temp_v0_2) - 1;
    *arg3 = 1;
    (*(s32 *)((u8 *)arg0 + 0x1B0)) = 1;
    (*(s32 *)((u8 *)arg4 + 0x14)) = 0;
    (*(s32 *)((u8 *)arg4 + 0x10)) = 0;
    (*(s32 *)((u8 *)arg4 + 4)) = 0;
    (*(s32 *)arg4) = 0;
    (*(s32 *)((u8 *)arg4 + 0x1C)) = 0;
    (*(s32 *)((u8 *)arg4 + 0x18)) = 0;
    (*(s32 *)((u8 *)arg4 + 0xC)) = 0;
    (*(s32 *)((u8 *)arg4 + 8)) = 0;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_029", func_0018AA80);

s32 func_0018AC70(void *arg0, void *arg1, s32 *arg2, void *arg3, s32 *arg4) {
    s32 temp_v0;
    s32 var_a5;

    var_a5 = 1;
    (*(s32 *)((u8 *)((((*(s32 *)((u8 *)arg0 + 0x810)) * 0x140) + arg0)) + 0x6CC)) = 1;
    (*(s32 *)((u8 *)arg0 + 0x1B0)) = 1;
    if ((*(s32 *)((u8 *)arg0 + 0x150)) == 2) {
        (*(s32 *)((u8 *)arg1 + 0x14)) = 0;
        (*(s32 *)((u8 *)arg1 + 0x10)) = 0;
        (*(s32 *)((u8 *)arg1 + 4)) = 0;
        (*(s32 *)arg1) = 0;
    }
    if ((*(s32 *)((u8 *)arg0 + 0x174)) == 3) {
        *arg2 = 2;
    } else {
        *arg2 = 1;
        temp_v0 = (*(s32 *)((u8 *)arg0 + 0x174)) == 2;
        (*(s32 *)((u8 *)arg3 + 4)) = temp_v0;
        (*(s32 *)arg3) = temp_v0;
    }
    if ((*(s32 *)((u8 *)arg0 + 0x150)) == 1) {
        func_0018F7B0((s32) arg0, &D_002BC828);
        var_a5 = 0;
    }
    *arg4 &= ~1;
    return var_a5;
}

INCLUDE_ASM("asm/nonmatchings/main_029", func_0018AD30);

INCLUDE_ASM("asm/nonmatchings/main_029", func_0018B1D8);

void func_0018B260(s32 arg0, s32 PMV[2][2][2], s32 *dmvector, s32 sel[2][2], s32 s, s32 count, s32 fmt, s32 h_r, s32 v_r, s32 dmv, s32 mvscale) {
    if (count == 1) {
        if (fmt == 0 && dmv == 0) {
            sel[1][s] = sel[0][s] = func_0018BA48((void *)arg0, 1);
        }
        func_0018B400(arg0, PMV[0][s], dmvector, h_r, v_r, dmv, mvscale, 0);
        PMV[1][s][0] = PMV[0][s][0];
        PMV[1][s][1] = PMV[0][s][1];
    } else {
        sel[0][s] = func_0018BA48((void *)arg0, 1);
        func_0018B400(arg0, PMV[0][s], dmvector, h_r, v_r, dmv, mvscale, 0);
        sel[1][s] = func_0018BA48((void *)arg0, 1);
        func_0018B400(arg0, PMV[1][s], dmvector, h_r, v_r, dmv, mvscale, 0);
    }
}

void func_0018B400(s32 arg0, s32 *arg1, s32 *arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    s32 code;
    s32 r;

    code = func_0018B6D8(arg0, 2);
    r = (arg3 != 0 && code != 0) ? func_0018BA48((void *)arg0, arg3) : 0;
    func_0018B1D8(arg1, arg3, code, r, arg7);
    if (arg5 != 0) {
        arg2[0] = func_0018A590(arg0);
    }
    code = func_0018B6D8(arg0, 2);
    r = (arg4 != 0 && code != 0) ? func_0018BA48((void *)arg0, arg4) : 0;
    if (arg6 != 0) {
        arg1[1] >>= 1;
    }
    func_0018B1D8(&arg1[1], arg4, code, r, arg7);
    if (arg6 != 0) {
        arg1[1] <<= 1;
    }
    if (arg5 != 0) {
        arg2[1] = func_0018A590(arg0);
    }
}

s32 func_0018B550(void *arg0, s32 arg1) {
    s32 temp_v0;

    *(volatile s32 *)0x10002000 = arg1;
    temp_v0 = (&D_0028DA50)[((u32) arg1 >> 0x1C)];
    (*(s32 *)((u8 *)arg0 + 0x818)) = temp_v0;
    return temp_v0;
}

void func_0018B580(void *arg0) {
    s32 n;

    n = 0;
    while ((*(volatile s32 *)0x10002010 & 0x80004000) == 0x80000000) {
        if (n++ > 5000) {
            func_0018EF98((*(s32 *)((u8 *)arg0 + 0x858)));
            n = 0;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/main_029", func_0018B628);

INCLUDE_ASM("asm/nonmatchings/main_029", func_0018B6D8);

s32 func_0018B850(void *arg0, s32 arg1) {
    s32 i;
    s32 *tbl;

    if (*(s32 *)((u8 *)arg0 + 0x818) != 0 || *(s32 *)((u8 *)arg0 + 0x83C) < arg1) {
        i = 0;
        while ((*(volatile s32 *)0x10002010 & 0x80004000) == 0x80000000) {
            if (i++ > 5000) {
                func_0018EF98(*(s32 *)((u8 *)arg0 + 0x858));
                i = 0;
            }
        }
        *(volatile s32 *)0x10002000 = 0x40000000;
        tbl = &D_0028DA50;
        *(s32 *)((u8 *)arg0 + 0x818) = tbl[4];
        *(s32 *)((u8 *)arg0 + 0x838) = func_0018B628(arg0);
        *(s32 *)((u8 *)arg0 + 0x83C) = 0x20;
    }
    return *(u32 *)((u8 *)arg0 + 0x838) >> (32 - arg1);
}

INCLUDE_ASM("asm/nonmatchings/main_029", func_0018B958);

INCLUDE_ASM("asm/nonmatchings/main_029", func_0018BA48);

void func_0018BB98(void *arg0) {
    s32 n;

    func_0018B580(arg0);
    n = -(*(volatile s32 *)0x10002020 & 7) & 7;
    if (n != 0) {
        func_0018B958(arg0, n);
    }
    while (func_0018B850(arg0, 0x18) != 1) {
        func_0018B958(arg0, 8);
    }
}

s32 func_0018BC18(void *arg0, s32 arg1) {
    (*(s32 *)((u8 *)arg0 + 0x1B4)) = func_0018BA48(arg0, 5);
    if (func_0018BA48(arg0, 1) != 0) {
        func_0018BA48(arg0, 1);
        func_0018B958(arg0, 7);
        func_0018C170(arg0);
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_029", func_0018BC80);

void func_0018BD90(void *arg0, s32 arg1) {
    s32 temp_s1;

    temp_s1 = func_0018BA48(arg0, 0xA);
    (*(s32 *)((u8 *)arg0 + 0x150)) = func_0018BA48(arg0, 3);
    func_0018BA48(arg0, 0x10);
    if ((u32) ((*(s32 *)((u8 *)arg0 + 0x150)) - 2) < 2U) {
        (*(s32 *)((u8 *)arg0 + 0x154)) = func_0018BA48(arg0, 1);
        (*(s32 *)((u8 *)arg0 + 0x158)) = func_0018BA48(arg0, 3);
    }
    if ((*(s32 *)((u8 *)arg0 + 0x150)) == 3) {
        (*(s32 *)((u8 *)arg0 + 0x15C)) = func_0018BA48(arg0, 1);
        (*(s32 *)((u8 *)arg0 + 0x160)) = func_0018BA48(arg0, 3);
    }
    func_0018C170(arg0);
    func_0018BE58(arg0);
    func_0018C1B8(arg0, temp_s1);
}

INCLUDE_ASM("asm/nonmatchings/main_029", func_0018BE58);

void func_0018BF80(void *arg0) {
    s32 temp_v0;

    (*(s32 *)((u8 *)arg0 + 0x164)) = func_0018BA48(arg0, 4);
    (*(s32 *)((u8 *)arg0 + 0x168)) = func_0018BA48(arg0, 4);
    (*(s32 *)((u8 *)arg0 + 0x16C)) = func_0018BA48(arg0, 4);
    (*(s32 *)((u8 *)arg0 + 0x170)) = func_0018BA48(arg0, 4);
    *(s32 *)0x10002010 = (*(s32 *)0x10002010 & 0xFFFCFFFF) | (func_0018BA48(arg0, 2) << 0x10);
    temp_v0 = func_0018BA48(arg0, 2);
    (*(s32 *)((u8 *)arg0 + 0x174)) = temp_v0;
    if ((*(s32 *)((u8 *)arg0 + 0xD4)) == 0) {
        (*(s32 *)((u8 *)arg0 + 0xD4)) = temp_v0;
    }
    (*(s32 *)((u8 *)arg0 + 0x178)) = func_0018BA48(arg0, 1);
    (*(s32 *)((u8 *)arg0 + 0x17C)) = func_0018BA48(arg0, 1);
    (*(s32 *)((u8 *)arg0 + 0x180)) = func_0018BA48(arg0, 1);
    *(volatile s32 *)0x10002010 = (s32) ((*(volatile s32 *)0x10002010 & 0xFFBFFFFF) | (func_0018BA48(arg0, 1) << 0x16));
    *(volatile s32 *)0x10002010 = (s32) ((*(volatile s32 *)0x10002010 & 0xFFDFFFFF) | (func_0018BA48(arg0, 1) << 0x15));
    *(volatile s32 *)0x10002010 = (s32) ((*(volatile s32 *)0x10002010 & 0xFFEFFFFF) | (func_0018BA48(arg0, 1) << 0x14));
    (*(s32 *)((u8 *)arg0 + 0x184)) = func_0018BA48(arg0, 1);
    func_0018BA48(arg0, 1);
    (*(s32 *)((u8 *)arg0 + 0x188)) = func_0018BA48(arg0, 1);
    if (func_0018BA48(arg0, 1) != 0) {
        func_0018BA48(arg0, 1);
        func_0018BA48(arg0, 3);
        func_0018BA48(arg0, 1);
        func_0018BA48(arg0, 7);
        func_0018BA48(arg0, 8);
    }
}

s32 func_0018C170(void *arg0) {
    while (func_0018BA48(arg0, 1) != 0) {
        func_0018B958(arg0, 8);
    }
}

s32 func_0018C1B8(void *arg0, s32 arg1) {
    s32 temp_a0;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v1;
    s32 var_a0;
    s32 var_a3;

    var_a3 = 0;
    var_a0 = 0;
    if (((*(s32 *)((u8 *)arg0 + 0x150)) != 3) && (arg1 != 0)) {
        if (arg1 < 0) {
            var_a3 = (*(s32 *)((u8 *)arg0 + 0x854)) == 0;
        }
        (*(s32 *)((u8 *)arg0 + 0x854)) = 0;
        var_a0 = arg1;
    }
    temp_v1 = (*(s32 *)((u8 *)arg0 + 0x84C)) + arg1;
    (*(s32 *)((u8 *)arg0 + 0x1AC)) = temp_v1;
    if ((var_a3 != 0) && (var_a0 >= arg1)) {
        (*(s32 *)((u8 *)arg0 + 0x1AC)) = (s32) (temp_v1 + 0x400);
    }
    temp_v0_2 = (*(s32 *)((u8 *)arg0 + 0x850));
    temp_a0 = (*(s32 *)((u8 *)arg0 + 0x1AC));
    temp_v0 = (temp_v0_2 < temp_a0) ? temp_a0 : temp_v0_2;
    (*(s32 *)((u8 *)arg0 + 0x850)) = temp_v0;
    return temp_v0;
}

void func_0018C230(void *arg0, s32 arg1) {
    (*(s32 *)((u8 *)arg0 + 0xE8)) = 0;
    (*(s32 *)((u8 *)arg0 + 0x854)) = 1;
    (*(s32 *)((u8 *)arg0 + 0x84C)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x850)) + 1);
    func_0018BA48(arg0, 1);
    func_0018BA48(arg0, 5);
    func_0018BA48(arg0, 6);
    func_0018BA48(arg0, 1);
    func_0018BA48(arg0, 6);
    func_0018BA48(arg0, 6);
    (*(s32 *)((u8 *)arg0 + 0x1A4)) = func_0018BA48(arg0, 1);
    (*(s32 *)((u8 *)arg0 + 0x1A8)) = func_0018BA48(arg0, 1);
    func_0018BE58(arg0);
}

void func_0018C2D0(void *arg0, s32 arg1) {
    s32 temp_v0;
    s32 temp_v0_2;

    temp_v0 = func_0018BA48(arg0, 1);
    (*(s32 *)((u8 *)arg0 + 0x840)) = temp_v0;
    if (temp_v0 != 0) {
        func_0018B580(arg0);
        func_0018B550(arg0, 0x50000000);
        func_0018B580(arg0);
    }
    temp_v0_2 = func_0018BA48(arg0, 1);
    (*(s32 *)((u8 *)arg0 + 0x844)) = temp_v0_2;
    if (temp_v0_2 != 0) {
        func_0018B580(arg0);
        func_0018B550(arg0, 0x58000000);
        func_0018B580(arg0);
    }
    if (func_0018BA48(arg0, 1) != 0) {
        func_0018F7B0((s32) arg0, &D_002BC8A8);
    }
    if (func_0018BA48(arg0, 1) != 0) {
        func_0018F7B0((s32) arg0, &D_002BC8D0);
    }
}

INCLUDE_ASM("asm/nonmatchings/main_029", func_0018C398);

void func_0018C490(s32 arg0, s32 arg1) {
    func_0018BA48(arg0, 1);
    func_0018BA48(arg0, 8);
    func_0018BA48(arg0, 1);
    func_0018BA48(arg0, 7);
    func_0018BA48(arg0, 1);
    func_0018BA48(arg0, 0x14);
    func_0018BA48(arg0, 1);
    func_0018BA48(arg0, 0x16);
    func_0018BA48(arg0, 1);
    func_0018BA48(arg0, 0x16);
}

s32 func_0018C520(void *arg0) {
    s32 temp_v0;
    void *var_s1;

    if (((*(s32 *)((u8 *)arg0 + 0x174)) == 3) && ((*(s32 *)((u8 *)arg0 + 0x120)) != 0)) {
        func_0018F7B0((s32) arg0, &D_002BC900);
        (*(s32 *)((u8 *)arg0 + 0x120)) = 0;
    }
    switch ((*(s32 *)((u8 *)arg0 + 0x174))) {        /* irregular */
    case 3:
        var_s1 = (*(void **)((u8 *)arg0 + 0x1C0));
        break;
    case 1:
        var_s1 = (*(void **)((u8 *)arg0 + 0x1D0));
        break;
    case 2:
        var_s1 = (*(void **)((u8 *)arg0 + 0x1E0));
        break;
    default:
        var_s1 = (*(void **)((u8 *)arg0 + 0x1C0));
        func_0018F7B0((s32) arg0, &D_002BC920);
        break;
    }
    temp_v0 = func_0018A848(arg0);
    if (temp_v0 != 0) {
        (*(s32 *)((u8 *)var_s1 + 0x28)) = 1;
    }
    return temp_v0;
}

void func_0018C5F0(void *arg0, s32 arg1, s32 arg2) {
    s32 temp_v0;
    s32 var_a1;
    s32 var_a1_2;
    s32 var_a2;

    if (arg2 != 0) {
        if ((*(s32 *)((u8 *)arg0 + 0x174)) == 3) {
            if ((*(s32 *)((u8 *)arg0 + 0x150)) == 3) {
                var_a1 = (*(s32 *)((u8 *)arg0 + 0x1C4));
            } else {
                var_a1 = (*(s32 *)((u8 *)arg0 + 0x1B8));
            }
            func_0018CE00(arg0, var_a1, arg1 - 1);
        } else {
            if ((*(s32 *)((u8 *)arg0 + 0x150)) == 3) {
                var_a1_2 = (*(s32 *)((u8 *)arg0 + 0x1D4));
                var_a2 = (*(s32 *)((u8 *)arg0 + 0x1E4));
            } else {
                var_a1_2 = (*(s32 *)((u8 *)arg0 + 0x1C8));
                var_a2 = (*(s32 *)((u8 *)arg0 + 0x1D8));
            }
            func_0018CF10(arg0, var_a1_2, var_a2, arg1 - 1);
        }
    }
    if ((*(s32 *)((u8 *)arg0 + 0xF8)) == 1) {
        (*(s32 *)((u8 *)arg0 + 0xF8)) = 2;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_029", func_0018C680);

s32 func_0018C938(void *arg0, s32 *arg1) {
    s8 buf[0x100];
    s32 ok;

    if (*(s32 *)((u8 *)arg0 + 0xE0) != 0) {
        ok = *(s32 *)((u8 *)arg0 + 0xDC) >= arg1[1] && *(s32 *)((u8 *)arg0 + 0xE0) >= arg1[2];
    } else {
        ok = *(s32 *)((u8 *)arg0 + 0xE4) >= arg1[3] * arg1[4];
    }
    if (!ok) {
        func_0019B648(buf, &D_002BC940, arg1[1], arg1[2]);
        func_0018F7B0((s32)arg0, buf);
    }
    return ok;
}

INCLUDE_ASM("asm/nonmatchings/main_029", func_0018C9D8);

void func_0018CC48(void *arg0) {
    if ((*(s32 *)((u8 *)arg0 + 8)) != 2) {
        (*(s32 *)((u8 *)arg0 + 8)) = 2;
        (*(s32 *)((u8 *)arg0 + 0xAC)) = (s32) (*(s32 *)((u8 *)arg0 + 0x118));
    }
    (*(s32 *)((u8 *)arg0 + 0x820)) = 1;
}

INCLUDE_ASM("asm/nonmatchings/main_029", func_0018CC70);

INCLUDE_ASM("asm/nonmatchings/main_029", func_0018CE00);

INCLUDE_ASM("asm/nonmatchings/main_029", func_0018CF10);

INCLUDE_ASM("asm/nonmatchings/main_029", func_0018D0C8);

void func_0018D220(s32 arg0, s32 arg1) {
    func_001843E0();
    *(volatile s32 *)0x1000B010 = (arg0 & 0x0FFFFFFF) | 0x80000000;
    *(volatile s32 *)0x1000B020 = arg1 >> 4;
    *(volatile s32 *)0x1000B000 = 0x100;
    func_00184428();
}

void func_0018D290(void *arg0, s32 arg1, s32 arg2) {
    s32 sp0[8];
    do {

    } while (*(volatile s32 *)0x10002010 < 0);
    func_001843E0();
    *(volatile s32 *)0x1000B010 = arg1 & 0x0FFFFFFF;
    *(volatile s32 *)0x1000B020 = arg2 << 6;
    *(volatile u32 *)0x1000B000 = 0x100;
    func_00184428();
    func_0018B550(arg0, arg2 | 0x70000000);
    sp0[0] = 4;
    func_0018EF48((*(s32 *)((u8 *)arg0 + 0x858)), sp0);
    do {

    } while (((u32) *(volatile s32 *)0x1000B000 >> 8) & 1);
    do {

    } while (*(volatile s32 *)0x10002010 < 0);
}

typedef struct {
    volatile s32 count;
    s32 done;
    s32 remain;
    s32 addr;
    s32 n;
} IpuDmaState;

s32 func_0018D3A8(s32 ch, void *arg) {
    IpuDmaState *st = arg;

    *(volatile u32 *)0x1000E010 = 8;
    st->count++;
    if (*(volatile u32 *)0x1000B020 != 0 || (*(volatile u32 *)0x1000B000 & 0x100)) {
        st->done = 1;
        return 0;
    }
    if (st->count < st->n - 1) {
        func_001843E0();
        *(volatile u32 *)0x1000B010 = st->addr;
        *(volatile u32 *)0x1000B020 = 0xFFC0;
        *(volatile u32 *)0x1000B000 = 0x100;
        func_00184428();
        *(volatile u32 *)0x10002000 = 0x700003FF;
        st->addr = (st->addr + 0xFFC00) & 0x0FFFFFFF;
    } else if (st->count == st->n - 1) {
        st->remain -= st->count * 1023;
        func_001843E0();
        *(volatile u32 *)0x1000B010 = st->addr;
        *(volatile u32 *)0x1000B020 = st->remain << 6;
        *(volatile u32 *)0x1000B000 = 0x100;
        func_00184428();
        *(volatile u32 *)0x10002000 = st->remain | 0x70000000;
    }
    __asm__ volatile("sync");
    __asm__ volatile("ei");
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_029", func_0018D520);

s32 func_0018D6D0(s32 arg0, void *arg1) {
    u32 temp_v0;

    *(volatile s32 *)0x1000E010 = 0x10;
    temp_v0 = (*(u32 *)arg1);
    if (temp_v0 == 0) {
        return 1;
    }
    if (temp_v0 > 0xFFFFU) {
        func_001843E0();
        *(volatile s32 *)0x1000B410 = (*(s32 *)((u8 *)arg1 + 4));
        *(volatile u32 *)0x1000B420 = 0xFFFF;
        *(volatile s32 *)0x1000B400 = 0x101;
        func_00184428();
        (*(u32 *)arg1) = (u32) ((*(u32 *)arg1) - 0xFFFF);
        (*(s32 *)((u8 *)arg1 + 4)) = (s32) (((*(s32 *)((u8 *)arg1 + 4)) + 0xFFFF0) & 0x0FFFFFFF);
    } else {
        func_001843E0();
        *(volatile s32 *)0x1000B410 = (s32) (*(s32 *)((u8 *)arg1 + 4));
        *(volatile s32 *)0x1000B420 = (u32) (*(u32 *)arg1);
        *(volatile s32 *)0x1000B400 = 0x101;
        func_00184428();
        (*(u32 *)arg1) = 0U;
    }
    return 0;
}

s32 func_0017B600(s32, s32 (*)(s32, void *), s32, u32 *);
s32 func_0018D520(void *, s32, s32);

typedef struct MpegOut_0018D7D8 {
    s32 type;
    s32 unk4[7];
    u32 qwc;
    u32 addr;
} MpegOut_0018D7D8;

void func_0018D7D8(void *arg0, s32 *arg1) {
    MpegOut_0018D7D8 cb;
    s32 mbs;
    s32 small;
    s32 hid;
    s32 addr;

    mbs = arg1[3] * arg1[4];
    cb.type = 2;
    func_0018EF48(*(s32 *)((u8 *)arg0 + 0x858), &cb);
    if (*(volatile s32 *)0x10002010 & 0x4000) {
        *(volatile s32 *)0x10002010 = 0x40000000;
    }
    small = mbs < 0x400;
    while (*(volatile s32 *)0x10002010 < 0) {
    }
    func_0018B550(arg0, 0);
    addr = arg1[0];
    while (*(volatile s32 *)0x10002010 < 0) {
    }
    cb.qwc = mbs * 0x18;
    cb.addr = addr & 0x0FFFFFFF;
    if (cb.qwc > 0xFFFF) {
        hid = func_0017B600(4, func_0018D6D0, 0, &cb.qwc);
        *(volatile s32 *)0x1000E010 = 0x10;
        func_0017C4F8(4);
        func_001843E0();
        *(volatile u32 *)0x1000B410 = cb.addr;
        *(volatile u32 *)0x1000B420 = 0xFFFF;
        *(volatile u32 *)0x1000B400 = 0x101;
        func_00184428();
        cb.addr = (cb.addr + 0xFFFF0) & 0x0FFFFFFF;
        cb.qwc -= 0xFFFF;
        if (small) {
            func_0018D290(arg0, *(s32 *)((u8 *)arg0 + 0xD8), mbs);
        } else {
            func_0018D520(arg0, *(s32 *)((u8 *)arg0 + 0xD8), mbs);
        }
        func_0017C490(4);
        func_0017B610(4, hid);
    } else {
        func_001843E0();
        *(volatile u32 *)0x1000B410 = arg1[0] & 0x0FFFFFFF;
        *(volatile u32 *)0x1000B420 = cb.qwc;
        *(volatile u32 *)0x1000B400 = 0x101;
        func_00184428();
        cb.qwc = 0;
        if (small) {
            func_0018D290(arg0, *(s32 *)((u8 *)arg0 + 0xD8), mbs);
        } else {
            func_0018D520(arg0, *(s32 *)((u8 *)arg0 + 0xD8), mbs);
        }
    }
    cb.type = 3;
    func_0018EF48(*(s32 *)((u8 *)arg0 + 0x858), &cb);
}

void func_0018DA50(u64 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    (*(s32 *)((u8 *)arg0 + 8)) = arg1;
    (*(u64 *)arg0) = 0;
    (*(s32 *)((u8 *)arg0 + 0xC)) = arg1;
    (*(s32 *)((u8 *)arg0 + 0x10)) = 0;
    (*(s64 *)((u8 *)arg0 + 0x18)) = 0;
    (*(s32 *)((u8 *)arg0 + 0x20)) = arg2;
    (*(s32 *)((u8 *)arg0 + 0x24)) = (s32) (arg2 + arg3);
    (*(s32 *)((u8 *)arg0 + 0x28)) = arg3;
    func_0018DAA8(arg0, 0);
}

s32 func_0018DA88(u64 *arg0, s32 arg1) {
    return *arg0 >> (64 - arg1);
}

#include "common.h"

void func_0018A378(s32 arg0) {
    *(s32 *)0x10002010 = (*(s32 *)0x10002010 & 0xFF7FFFFF) | (arg0 << 0x17);
}

INCLUDE_ASM("asm/nonmatchings/main_029", func_0018A3A0);

s32 func_0018A590(s32 arg0) {
    return func_0018B6D8(arg0, 3);
}

void func_0018A5B0(void *arg0, s32 DMV[][2], s32 *dmvector, s32 mvx, s32 mvy) {
    if (*(s32 *)((u8 *)arg0 + 0x174) == 3) {
        if (*(s32 *)((u8 *)arg0 + 0x178)) {
            DMV[0][0] = ((mvx + (mvx > 0)) >> 1) + dmvector[0];
            DMV[0][1] = ((mvy + (mvy > 0)) >> 1) + dmvector[1] - 1;
            DMV[1][0] = ((3 * mvx + (mvx > 0)) >> 1) + dmvector[0];
            DMV[1][1] = ((3 * mvy + (mvy > 0)) >> 1) + dmvector[1] + 1;
        } else {
            DMV[0][0] = ((3 * mvx + (mvx > 0)) >> 1) + dmvector[0];
            DMV[0][1] = ((3 * mvy + (mvy > 0)) >> 1) + dmvector[1] - 1;
            DMV[1][0] = ((mvx + (mvx > 0)) >> 1) + dmvector[0];
            DMV[1][1] = ((mvy + (mvy > 0)) >> 1) + dmvector[1] + 1;
        }
    } else {
        DMV[0][0] = ((mvx + (mvx > 0)) >> 1) + dmvector[0];
        DMV[0][1] = ((mvy + (mvy > 0)) >> 1) + dmvector[1];
        if (*(s32 *)((u8 *)arg0 + 0x174) == 1) {
            DMV[0][1]--;
        } else {
            DMV[0][1]++;
        }
    }
}

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

s32 func_0018AA80(void *arg0, s32 arg1) {
    s32 dc[8];
    s32 pmv[4];
    s32 mvfs[4];
    s32 MBA;
    s32 MBAinc;
    s32 mbtype;
    s32 mtype;
    s32 dct;
    s32 ret;

    MBA = 0;
    MBAinc = 0;
    if ((ret = func_0018A950(arg0, arg1, &MBA, &MBAinc, dc)) != 0) {
        return ret;
    }
    *(s32 *)((u8 *)arg0 + 0x11C) = 0;
    for (;;) {
        if (MBA >= arg1) {
            return 0;
        }
        *(s32 *)((u8 *)arg0 + *(s32 *)((u8 *)arg0 + 0x810) * 0x140 + 0x6CC) = 0;
        if (func_0018A3A0(arg0) == 0) {
            return 2;
        }
        if (MBAinc == 0) {
            if (func_0018B850(arg0, 23) == 0 || *(s32 *)((u8 *)arg0 + 0x11C) != 0) {
                *(s32 *)((u8 *)arg0 + 0x11C) = 0;
                return 3;
            }
            MBAinc = func_0018A738(arg0);
            if (*(s32 *)((u8 *)arg0 + 0x11C) != 0) {
                goto fault;
            }
        }
        if (MBA >= arg1) {
            func_0018F7B0((s32)arg0, &D_002BC808);
            return 2;
        }
        if (MBAinc == 1) {
            if (func_0018AD30(arg0, &mbtype, &mtype, &dct, dc, pmv, mvfs) == 0) {
fault:
                *(s32 *)((u8 *)arg0 + 0x11C) = 0;
                return 1;
            }
        } else {
            if (func_0018AC70(arg0, dc, &mtype, pmv, &mbtype) == 0) {
                goto fail;
            }
        }
        if (func_00188630(arg0, MBA, MBAinc, mbtype, mtype, dc, pmv, mvfs) == 0) {
fail:
            *(s32 *)((u8 *)arg0 + 0x11C) = 0;
            return 2;
        }
        if (MBA != 0) {
            func_001893A8(arg0, *(s32 *)((u8 *)arg0 + 0x810) ^ 1);
        }
        MBA++;
        *(s32 *)((u8 *)arg0 + 0x810) ^= 1;
        MBAinc--;
    }
}

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

s32 func_0018B1D8(s32 *pred, s32 r_size, s32 motion_code, s32 motion_residual, s32 full_pel_vector) {
    s32 lim, vec;

    lim = 16 << r_size;
    vec = full_pel_vector ? (*pred >> 1) : (*pred);

    if (motion_code > 0) {
        vec += ((motion_code - 1) << r_size) + motion_residual + 1;
        if (vec >= lim) {
            vec -= lim + lim;
        }
    } else if (motion_code < 0) {
        vec -= ((-motion_code - 1) << r_size) + motion_residual + 1;
        if (vec < -lim) {
            vec += lim + lim;
        }
    }
    return *pred = full_pel_vector ? (vec << 1) : vec;
}

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

s64 func_0018B628(void *arg0) {
    s32 i;
    s64 r;

    i = 0;
    while ((r = *(volatile s64 *)0x10002000) < 0 && !(*(volatile s32 *)0x10002010 & 0x4000)) {
        if (i++ > 5000) {
            func_0018EF98(*(s32 *)((u8 *)arg0 + 0x858));
            i = 0;
        }
    }
    return r;
}

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

s32 func_0018BA48(void *arg0, s32 arg1) {
    s32 i;
    s32 *tbl;
    s32 cmd;
    u32 v;

    i = 0;
    while ((*(volatile s32 *)0x10002010 & 0x80004000) == 0x80000000) {
        if (i++ > 5000) {
            func_0018EF98(*(s32 *)((u8 *)arg0 + 0x858));
            i = 0;
        }
    }
    if (*(s32 *)((u8 *)arg0 + 0x818) != 0 || *(s32 *)((u8 *)arg0 + 0x83C) < arg1) {
        *(volatile s32 *)0x10002000 = 0x40000000;
        tbl = &D_0028DA50;
        *(s32 *)((u8 *)arg0 + 0x818) = tbl[4];
        *(s32 *)((u8 *)arg0 + 0x838) = func_0018B628(arg0);
    }
    cmd = arg1 | 0x40000000;
    v = *(u32 *)((u8 *)arg0 + 0x838) >> (0x20 - arg1);
    *(s32 *)((u8 *)arg0 + 0x83C) = 0x20;
    *(volatile u32 *)0x10002000 = cmd;
    *(s32 *)((u8 *)arg0 + 0x818) = (&D_0028DA50)[(u32)cmd >> 28];
    *(s32 *)((u8 *)arg0 + 0x838) = func_0018B628(arg0);
    return v;
}

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

typedef struct MpegCb_0018BC80 {
    s32 type;
    s32 pad4;
    s64 a;
    s64 b;
} MpegCb_0018BC80;

s32 func_0018BC80(void *arg0) {
    MpegCb_0018BC80 cb;
    u32 code;

    for (;;) {
        func_0018BB98(arg0);
        code = func_0018BA48(arg0, 32);
        switch (code) {
        case 0x1B3:
            func_0018F918(arg0);
            break;
        case 0x1B8:
            ((void (*)(void *))func_0018C230)(arg0);
            break;
        case 0x100:
            ((void (*)(void *))func_0018BD90)(arg0);
            cb.type = 5;
            cb.a = -1;
            cb.b = -1;
            func_0018EF48(*(s32 *)((u8 *)arg0 + 0x858), &cb);
            *(s64 *)((u8 *)arg0 + 0x828) = cb.a;
            *(s64 *)((u8 *)arg0 + 0x830) = cb.b;
            return *(s32 *)((u8 *)arg0 + 0x150);
        case 0x1B7:
            return 0;
        }
    }
}

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

typedef struct ExtTbl_0018BE58 {
    void (*f[11])(void *);
} ExtTbl_0018BE58;

extern ExtTbl_0018BE58 D_002BC878;

void func_0018BE58(void *d) {
    ExtTbl_0018BE58 tbl;
    u32 id;
    s32 code;

    tbl = D_002BC878;
    func_0018BB98(d);
    while ((code = func_0018B850(d, 32)) == 0x1B5 || code == 0x1B2) {
        if (code == 0x1B5) {
            func_0018B958(d, 32);
            id = func_0018BA48(d, 4);
            id = (id > 10) ? 0 : id;
            tbl.f[id](d);
            func_0018BB98(d);
        } else {
            func_0018B958(d, 32);
            func_0018BB98(d);
        }
    }
}

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

typedef struct DispExt_0018C398 {
    u8 pad[0x18C];
    s32 h[3];
    s32 v[3];
} DispExt_0018C398;

void func_0018C398(void *arg0) {
    u8 *d;
    s32 i;
    s32 n;

    d = arg0;
    if (*(s32 *)(d + 0x13C)) {
        if (*(s32 *)(d + 0x184)) {
            if (*(s32 *)(d + 0x178)) {
                n = 3;
            } else {
                n = 2;
            }
        } else {
            n = 1;
        }
    } else {
        if (*(s32 *)(d + 0x174) != 3) {
            n = 1;
        } else {
            if (*(s32 *)(d + 0x184)) {
                n = 3;
            } else {
                n = 2;
            }
        }
    }
    for (i = 0; i < n; i++) {
        ((DispExt_0018C398 *)d)->h[i] = func_0018BA48(arg0, 16);
        func_0018BA48(arg0, 1);
        ((DispExt_0018C398 *)d)->v[i] = func_0018BA48(arg0, 16);
        func_0018BA48(arg0, 1);
    }
}

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

void func_0018C9D8(void *arg0, s32 *s) {
    u8 *d = arg0;
    s32 src;
    s32 n;
    s32 dst;
    s32 p;
    s32 i;
    s32 j;
    s32 qwc;
    s32 inc_src;
    s32 inc_dst;

    src = s[0] & 0x0FFFFFFF;
    dst = *(s32 *)(d + 0xD8) & 0x0FFFFFFF;
    if (*(s32 *)(d + 0x174) == 3 || *(s32 *)(d + 0xE0) == 0) {
        inc_src = s[4] * 0x180;
        qwc = inc_src >> 4;
        if (*(s32 *)(d + 0xE0) != 0) {
            inc_dst = (*(s32 *)(d + 0xE0) >> 4) * 0x180;
        } else {
            inc_dst = inc_src;
        }
        n = 1;
    } else {
        inc_dst = (*(s32 *)(d + 0xE0) >> 4) * 0xC0;
        inc_src = (s[4] >> 1) * 0x180;
        n = 2;
        qwc = inc_src >> 4;
    }
    for (i = 0; i < n; i++) {
        p = dst;
        for (j = 0; j < s[3]; j++) {
            func_001843E0();
            *(volatile s32 *)0x1000D480 = 0;
            *(volatile s32 *)0x1000D410 = src;
            *(volatile s32 *)0x1000D420 = qwc;
            *(volatile s32 *)0x1000D400 = 0x101;
            func_00184428();
            while (*(volatile s32 *)0x1000D400 & 0x100) {
            }
            func_001843E0();
            *(volatile s32 *)0x1000D080 = 0;
            *(volatile s32 *)0x1000D010 = p;
            *(volatile s32 *)0x1000D020 = qwc;
            *(volatile s32 *)0x1000D000 = 0x100;
            func_00184428();
            while (*(volatile s32 *)0x1000D000 & 0x100) {
            }
            while (*(volatile s32 *)0x1000D020 != 0) {
            }
            p += inc_dst;
            src += inc_src;
        }
        dst += *(s32 *)(d + 0xE4) * 0xC0;
    }
}

void func_0018CC48(void *arg0) {
    if ((*(s32 *)((u8 *)arg0 + 8)) != 2) {
        (*(s32 *)((u8 *)arg0 + 8)) = 2;
        (*(s32 *)((u8 *)arg0 + 0xAC)) = (s32) (*(s32 *)((u8 *)arg0 + 0x118));
    }
    (*(s32 *)((u8 *)arg0 + 0x820)) = 1;
}

typedef struct {
    u8 pad00[0x70];
    int usePtsGap;   /* 0x070 */
    int pad74;       /* 0x074 */
    long long ptsGap;   /* 0x078 */
    int lastPts;     /* 0x080 */
    int pad84;       /* 0x084 */
    long long lastShow; /* 0x088 */
    int halfCount;   /* 0x090 */
    u8 pad94[0xF0 - 0x94];
    long long ptm;   /* 0x0F0 */
    int ptmState;    /* 0x0F8 */
} MpegSys_0018CC70;

#define s_0018CC70 ((MpegSys_0018CC70 *)arg0)
#define pts_0018CC70 ((long long *)arg2)
#define dts_0018CC70 ((long long *)arg3)
#define flags_0018CC70 ((long long *)arg4)

/* _getPtsDtsFlags (this SDK passes the decoder record first): adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

void func_0018CC70(void *arg0, s32 *img, void *arg2, void *arg3, void *arg4) {
    long long t;
    int show;
    int last;
    int carry;

    if (s_0018CC70->usePtsGap != 0) {
        t = *(long long *)&img[0x18 / 4];
        if (t < 0 && (last = s_0018CC70->lastPts) >= 0) {
            show = (int)s_0018CC70->lastShow;
            carry = (int)((long long)(show & 1) * (s_0018CC70->ptsGap & 1) * (s_0018CC70->halfCount & 1));
            *pts_0018CC70 = last + ((int)((s_0018CC70->ptsGap * show) >> 1) + carry);
            if ((long long)(show & 1) * (s_0018CC70->ptsGap & 1) != 0) {
                s_0018CC70->halfCount = s_0018CC70->halfCount + 1;
            }
        } else {
            *pts_0018CC70 = t;
        }
    } else {
        *pts_0018CC70 = *(long long *)&img[0x18 / 4];
    }
    if (s_0018CC70->ptmState == 2) {
        long long v = s_0018CC70->ptm;

        if (v >= 0) {
            *pts_0018CC70 = v;
            s_0018CC70->ptmState = 0;
            s_0018CC70->ptm = -1;
        }
    }
    *dts_0018CC70 = *(long long *)&img[0x20 / 4];
    *flags_0018CC70 = ((long long)img[0x34 / 4] << 8) | ((long long)img[0x38 / 4] << 7) |
                      ((long long)img[0x3C / 4] << 6) | ((long long)img[0x40 / 4] << 5) |
                      ((long long)img[0x30 / 4] << 3) | img[0x2C / 4];
}

#undef s_0018CC70
#undef pts_0018CC70
#undef dts_0018CC70
#undef flags_0018CC70

void func_0018CE00(void *d, s32 arg1, s32 unused) {
    s32 *s = (s32 *)arg1;
    u8 *p;

    p = *(u8 **)((u8 *)d + 0x858);
    func_0018CC70(d, s, p + 0x10, p + 0x18, p + 0x20);
    p = *(u8 **)((u8 *)d + 0x858);
    *(s32 *)((u8 *)d + 0x80) = *(s32 *)(p + 0x10);
    *(u64 *)((u8 *)d + 0x88) = D_0028DA78[(s32)(*(u64 *)(p + 0x20) >> 5) & 0xF];
    *(s32 *)((u8 *)d + 0xCC) = s[0x5C / 4];
    *(s32 *)((u8 *)d + 0xD0) = s[0x60 / 4];
    *(s32 *)((u8 *)d + 0xB4) = s[0x44 / 4];
    *(s32 *)((u8 *)d + 0xB8) = s[0x48 / 4];
    *(s32 *)((u8 *)d + 0xBC) = s[0x4C / 4];
    *(s32 *)((u8 *)d + 0xC0) = s[0x50 / 4];
    *(s32 *)((u8 *)d + 0xC4) = s[0x54 / 4];
    *(s32 *)((u8 *)d + 0xC8) = s[0x58 / 4];
    if (func_0018C938(d, s) == 0) {
        return;
    }
    if (s[0x28 / 4] != 1) {
        return;
    }
    if (*(s32 *)((u8 *)d + 0xB0) != 0) {
        func_0018D7D8(d, s);
    } else {
        ((void (*)(void *, s32 *))func_0018C9D8)(d, s);
    }
    func_0018CC48(d);
}

typedef union MpegU64_0018CF10 {
    u64 d;
    s32 w[2];
} MpegU64_0018CF10;

void func_0018CF10(void *d, s32 arg1, s32 arg2, s32 unused) {
    s32 *top = (s32 *)arg1;
    s32 *bot = (s32 *)arg2;
    s32 *s0;
    s32 *s1;
    s32 bits = 0;
    u8 *p;
    u8 *q;
    u8 *r;

    if (*(s32 *)((u8 *)d + 0x174) == 2) {
        s0 = top;
        s1 = bot;
        bits = 0x40;
    } else {
        s0 = bot;
        s1 = top;
    }
    p = *(u8 **)((u8 *)d + 0x858);
    func_0018CC70(d, s0, p + 0x10, p + 0x18, p + 0x20);
    q = *(u8 **)((u8 *)d + 0x858);
    *(s32 *)((u8 *)d + 0x80) = *(s32 *)(q + 0x10);
    ((MpegU64_0018CF10 *)((u8 *)d + 0x88))->d = 1;
    func_0018CC70(d, s1, q + 0x28, q + 0x30, q + 0x38);
    r = *(u8 **)((u8 *)d + 0x858);
    *(s32 *)((u8 *)d + 0x80) = *(s32 *)(r + 0x28);
    ((MpegU64_0018CF10 *)((u8 *)d + 0x88))->d = 1;
    *(u64 *)(r + 0x20) |= bits;
    *(u64 *)(r + 0x38) |= bits;
    *(s32 *)((u8 *)d + 0xCC) = s0[0x5C / 4];
    *(s32 *)((u8 *)d + 0xD0) = s0[0x60 / 4];
    *(s32 *)((u8 *)d + 0xB4) = s0[0x44 / 4];
    *(s32 *)((u8 *)d + 0xB8) = s1[0x48 / 4];
    *(s32 *)((u8 *)d + 0xC0) = s0[0x50 / 4];
    *(s32 *)((u8 *)d + 0xC4) = s1[0x54 / 4];
    if (func_0018C938(d, top) == 0) {
        return;
    }
    if (top[0x28 / 4] != 1) {
        return;
    }
    if (bot[0x28 / 4] != 1) {
        return;
    }
    top[0x10 / 4] <<= 1;
    if (*(s32 *)((u8 *)d + 0xB0) != 0) {
        func_0018D7D8(d, top);
    } else {
        ((void (*)(void *, s32 *))func_0018C9D8)(d, top);
    }
    top[0x10 / 4] >>= 1;
    func_0018CC48(d);
}

extern s32 D_00315300;

typedef struct SprBuf_0018D0C8 {
    s32 spr;
    s32 unk4;
    s32 a[4];
    s32 b[4];
    u8 unk28[0x104];
    s32 n;
    u8 unk130[0x10];
} SprBuf_0018D0C8;

typedef struct SprDec_0018D0C8 {
    u8 unk0[0x590];
    SprBuf_0018D0C8 bufs[2];
    s32 cur;
} SprDec_0018D0C8;

void func_0018D0C8(void *arg0) {
    SprDec_0018D0C8 *d;
    s32 cur;
    s32 n;
    s32 i;
    u64 *t;
    s32 id;
    u64 hi;

    d = arg0;
    cur = d->cur;
    n = d->bufs[cur].n;
    t = (u64 *)(((u32)&D_00315300 & 0x0FFFFFFF) | 0x20000000);
    for (i = 0; i < n; i++) {
        t[0] = ((u64)(d->bufs[cur].a[i] & 0x0FFFFFFF) << 32) | 0x30000030;
        hi = (u64)(d->bufs[cur].b[i] & 0x0FFFFFFF) << 32;
        id = 3;
        if (i == n - 1) {
            id = 0;
        }
        t[2] = hi | ((u64)id << 28) | 0x30;
        t += 4;
    }
    func_001843E0();
    __asm__ volatile("sync");
    *(volatile s32 *)0x1000D480 = d->bufs[d->cur].spr;
    *(volatile s32 *)0x1000D430 = (s32)&D_00315300;
    *(volatile s32 *)0x1000D420 = 0;
    *(volatile s32 *)0x1000D400 = 0x105;
    func_00184428();
}

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

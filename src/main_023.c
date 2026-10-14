#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017D0C0);

s32 func_0017D180(s32 arg0) {
    do {

    } while (*(volatile s32 *)0x1000F130 & 0x8000);
    *(volatile s8 *)0x1000F180 = (s8) arg0;
    return arg0;
}

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017D1B8);

void func_0017D268(s32 arg0) {
    if (arg0 == 0xA) {
        func_0017D180(0xD);
        func_0017D180(0xA);
        return;
    }
    func_0017D180(arg0);
}

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017D2A0);

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017D330);

void func_0017D498(char *fmt, u8 *ap) {
    char buf[32];
    char *p;
    char *pad;
    s64 v;
    u64 u;
    s32 mod;
    s32 w;
    s32 c;
    f32 f;
    char *s;
    char ch;
    u64 d;
    u64 e;

    while (*fmt) {
        pad = 0;
        mod = 0;
        if (*fmt == '%') {
    again:
        switch (*++fmt) {
        case '0':
            w = fmt[1] - '0';
            c = fmt[2];
            if ((u8)w < 10) {
                if (c >= '0' && c <= '9') {
                    w = w * 10 + (c - '0');
                    fmt += 2;
                    if (w >= 32) {
                        w = 31;
                    }
                } else {
                    fmt++;
                }
                pad = buf + (31 - w);
                while (w > 0) {
                    buf[31 - w] = '0';
                    w--;
                }
            }
            goto again;
        case 'l':
            mod = 'l';
            goto again;
        case 'h':
            mod = 'h';
            goto again;
        case 'o':
            if (mod == 'l') {
                ap += 8;
                u = *(u64 *)(ap - 8);
            } else if (mod == 'h') {
                ap += 8;
                u = *(u16 *)(ap - 8);
            } else {
                ap += 8;
                u = *(u32 *)(ap - 8);
            }
            p = &buf[31];
            *p = 0;
            if (u == 0) {
                *--p = '0';
            } else {
                while (u != 0) {
                    *--p = (u & 7) + '0';
                    u >>= 3;
                }
            }
            if (pad != 0 && pad < p) {
                p = pad;
            }
            while (*p) {
                D_0028CA0C(*p++);
            }
            break;
        case 'x':
            if (mod == 'l') {
                ap += 8;
                u = *(u64 *)(ap - 8);
            } else if (mod == 'h') {
                ap += 8;
                u = *(u16 *)(ap - 8);
            } else {
                ap += 8;
                u = *(u32 *)(ap - 8);
            }
            p = &buf[31];
            *p = 0;
            if (u == 0) {
                *--p = '0';
            } else {
                while (u != 0) {
                    d = u & 0xF;
                    if (d < 10) {
                        *--p = d + '0';
                    } else {
                        *--p = d + 'a' - 10;
                    }
                    u >>= 4;
                }
            }
            if (pad != 0 && pad < p) {
                p = pad;
            }
            while (*p) {
                D_0028CA0C(*p++);
            }
            break;
        case 'd':
            if (mod == 'l') {
                ap += 8;
                v = *(s64 *)(ap - 8);
            } else if (mod == 'h') {
                ap += 8;
                v = *(s16 *)(ap - 8);
            } else {
                ap += 8;
                v = *(s32 *)(ap - 8);
            }
            p = &buf[31];
            *p = 0;
            if (v == 0) {
                *--p = '0';
            } else {
                if (v < 0) {
                    v = -v;
                    D_0028CA0C('-');
                }
                while (v != 0) {
                    *--p = func_001A0CF8(v, 10) + '0';
                    v = func_001A0660(v, 10);
                }
            }
            if (pad != 0 && pad < p) {
                p = pad;
            }
            while (*p) {
                D_0028CA0C(*p++);
            }
            break;
        case 'u':
            if (mod == 'l') {
                ap += 8;
                u = *(u64 *)(ap - 8);
            } else if (mod == 'h') {
                ap += 8;
                u = *(u16 *)(ap - 8);
            } else {
                ap += 8;
                u = *(u32 *)(ap - 8);
            }
            p = &buf[31];
            *p = 0;
            if (u == 0) {
                *--p = '0';
            } else {
                while (u != 0) {
                    *--p = func_001A1908(u, 10) + '0';
                    u = func_001A1388(u, 10);
                }
            }
            if (pad != 0 && pad < p) {
                p = pad;
            }
            while (*p) {
                D_0028CA0C(*p++);
            }
            break;
        case 'e':
        case 'f':
            ap += 8;
            f = *(f32 *)(ap - 8);
            if (f == 0.0f) {
                D_0028CA0C('0');
            } else {
                func_0017D330(((s64 (*)(f32))func_001A2370)(f));
            }
            break;
        case 's':
            ap += 8;
            s = *(char **)(ap - 8);
            if (*s == 0) {
                D_0028CA0C('(');
                D_0028CA0C('n');
                D_0028CA0C('u');
                D_0028CA0C('l');
                D_0028CA0C('l');
                D_0028CA0C(')');
            } else {
                p = s;
                do {
                    D_0028CA0C(*p++);
                } while (*p);
            }
            break;
        case 'c':
            ap += 8;
            v = *(char *)(ap - 8);
            D_0028CA0C(v);
            break;
        }
        } else {
            D_0028CA0C(*fmt);
        }
        fmt++;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017DA60);

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017DA98);

void func_0017DAF8(s32 *arg0, s32 *arg1) {
    ((s32 **) arg1)[7][arg0[4]] = arg0[5];
}

void func_0017DB18(void *arg0, void *arg1) {
    (*(s32 *)((u8 *)arg1 + 8)) = (s32) (*(s32 *)((u8 *)arg0 + 0x10));
}

s32 func_0017DB28(s32 arg0) {
    return (&D_00310FC0)[arg0];
}

s32 func_0017DB40(s32 arg0, s32 arg1) {
    (&D_00310FC0)[arg0] = arg1;
    return arg1;
}

s32 *func_0017DB60(void) {
    return &D_00310E98;
}

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017DB70);

void func_0017DDF0(void) {
    func_0017C490(5);
    func_0017B610(5, D_00310E94);
    D_0028CA10 = 0;
}

s32 func_0017DE28(s32 arg0, s32 arg1) {
    s32 *p = (s32 *)&D_00310E98;
    s32 old = p[5];
    p[5] = arg0;
    p[6] = arg1;
    return old;
}

s32 func_0017DE40(s32 arg0, s32 arg1) {
    s32 *p = (s32 *)&D_00310E98;
    s32 old = p[3];
    p[3] = arg0;
    p[4] = arg1;
    return old;
}

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017DE58);

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017DE88);

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017DEB0);

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017DFE8);

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017E028);

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017E068);

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017E190);

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017E23C);

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017E240);

void func_0017E3E0(void) {
    func_0017DDF0();
    D_0028CA18 = 0;
}

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017E408);

void func_0017E4B0(void *arg0) {
    (*(s32 *)((u8 *)arg0 + 0x18)) = 0;
    (*(s32 *)((u8 *)arg0 + 0x10)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x10)) & 0xFFFFFFFE);
}

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017E4D0);

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017E500);

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017E540);

void func_0017E5F8(void *arg0, s32 arg1) {
    void *temp_v0;
    s32 a;
    s32 b;

    temp_v0 = func_0017E4D0(arg1);
    a = *(s32 *)((u8 *)arg0 + 0x14);
    b = *(s32 *)((u8 *)arg0 + 0x1C);
    (*(s32 *)((u8 *)temp_v0 + 0x14)) = a;
    (*(s32 *)((u8 *)temp_v0 + 0x1C)) = b;
    (*(s32 *)((u8 *)temp_v0 + 0x20)) = 0x8000000C;
    func_0017E028(0x80000008, temp_v0, 0x40, (*(s32 *)((u8 *)arg0 + 0x20)), (*(s32 *)((u8 *)arg0 + 0x24)), (*(s32 *)((u8 *)arg0 + 0x28)));
}

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017E658);

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017E7B0);

void func_0017E800(void *arg0, s32 arg1) {
    s32 hl0;
    void *temp_v0;
    void *temp_v0_2;

    temp_v0 = func_0017E4D0(arg1);
    hl0 = (s32) (*(s32 *)((u8 *)arg0 + 0x14));
    (*(s32 *)((u8 *)temp_v0 + 0x1C)) = (s32) (*(s32 *)((u8 *)arg0 + 0x1C));
    (*(s32 *)((u8 *)temp_v0 + 0x14)) = hl0;
    (*(s32 *)((u8 *)temp_v0 + 0x20)) = 0x80000009;
    temp_v0_2 = func_0017E7B0((*(s32 *)((u8 *)arg0 + 0x20)), arg1);
    if (temp_v0_2 == NULL) {
        (*(void **)((u8 *)temp_v0 + 0x24)) = NULL;
        (*(s32 *)((u8 *)temp_v0 + 0x28)) = 0;
        (*(s32 *)((u8 *)temp_v0 + 0x2C)) = 0;
    } else {
        (*(void **)((u8 *)temp_v0 + 0x24)) = temp_v0_2;
        (*(s32 *)((u8 *)temp_v0 + 0x28)) = (s32) (*(s64 *)((u8 *)temp_v0_2 + 8));
        (*(s32 *)((u8 *)temp_v0 + 0x2C)) = (s32) (*(s32 *)((u8 *)temp_v0_2 + 0x14));
    }
    func_0017E028(0x80000008, temp_v0, 0x40, 0, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017E8B0);

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017E9F0);

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017EA80);

s32 func_0017EC70(void *arg0) {
    void *temp_a1;

    temp_a1 = (*(void **)arg0);
    if ((temp_a1 == NULL) || ((*(s32 *)((u8 *)arg0 + 4)) != (*(s32 *)((u8 *)temp_a1 + 0x18))) || !((*(s32 *)((u8 *)temp_a1 + 0x10)) & 1)) {
        return 0;
    }
    return 1;
}

void func_0017ECB0(void *arg0, s32 arg1) {
    u8 *b_D_00312840;
    void *temp_v0;
    void *var_a0;
    void *var_v1;

    func_001843E0();
    (*(s32 *)arg0) = arg1;
    (*(s32 *)((u8 *)arg0 + 4)) = 0;
    (*(s32 *)((u8 *)arg0 + 8)) = 0;
    (*(s32 *)((u8 *)arg0 + 0xC)) = 0;
    (*(s32 *)((u8 *)arg0 + 0x10)) = 0;
    (*(s32 *)((u8 *)arg0 + 0x14)) = 0;
    b_D_00312840 = (u8 *)&D_00312840;
    if ((*(void **)(b_D_00312840 + 0x28)) == NULL) {
        (*(void **)(b_D_00312840 + 0x28)) = arg0;
    } else {
        var_a0 = (*(void **)(b_D_00312840 + 0x28));
        var_v1 = (*(void **)((u8 *)var_a0 + 0x14));
        if (var_v1 != NULL) {
            do {
                var_a0 = var_v1;
                temp_v0 = (*(void **)((u8 *)var_a0 + 0x14));
                var_v1 = temp_v0;
            } while (temp_v0 != NULL);
        }
        (*(void **)((u8 *)var_a0 + 0x14)) = arg0;
    }
    func_00184428();
}

void func_0017ED48(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, void *arg6) {
    void *temp_v0;
    void *temp_v0_2;
    void *var_a0;
    void *var_v1;

    func_001843E0();
    (*(volatile s32 *)((u8 *)arg0 + 0x3C)) = 0;
    (*(volatile s32 *)((u8 *)arg0 + 0x38)) = 0;
    (*(volatile s32 *)arg0) = arg1;
    temp_v0 = (void *)(*(s32 *)((u8 *)arg6 + 8));
    (*(s32 *)((u8 *)arg0 + 4)) = arg2;
    (*(s32 *)((u8 *)arg0 + 8)) = arg3;
    (*(s32 *)((u8 *)arg0 + 0x10)) = arg4;
    (*(s32 *)((u8 *)arg0 + 0x14)) = arg5;
    (*(s32 *)((u8 *)arg0 + 0x40)) = (s32)arg6;
    if (temp_v0 == NULL) {
        (*(void **)((u8 *)arg6 + 8)) = arg0;
    } else {
        var_a0 = temp_v0;
        var_v1 = (*(void **)((u8 *)var_a0 + 0x38));
        if (var_v1 != NULL) {
            do {
                var_a0 = var_v1;
                temp_v0_2 = (*(void **)((u8 *)var_a0 + 0x38));
                var_v1 = temp_v0_2;
            } while (temp_v0_2 != NULL);
        }
        (*(void **)((u8 *)var_a0 + 0x38)) = arg0;
    }
    func_00184428();
}

void *func_0017EE18(void *arg0, void *arg1) {
    void *p;
    void *n;

    func_001843E0();
    p = (*(void **)((u8 *)arg1 + 8));
    if (p == arg0) {
        (*(void **)((u8 *)arg1 + 8)) = (*(void **)((u8 *)p + 0x38));
    } else {
        for (; p != NULL; p = (*(void **)((u8 *)p + 0x38))) {
            if ((*(void **)((u8 *)p + 0x38)) == arg0) {
                (*(void **)((u8 *)p + 0x38)) = (*(void **)((u8 *)arg0 + 0x38));
                break;
            }
        }
    }
    func_00184428();
    return p;
}

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017EEB0);

void *func_0017EF40(void *arg0) {
    void *temp_s1;

    func_001843E0();
    temp_s1 = (*(void **)((u8 *)arg0 + 0xC));
    if (temp_s1 == NULL) {
        (*(s32 *)((u8 *)arg0 + 4)) = 0;
    } else {
        (*(s32 *)((u8 *)arg0 + 4)) = 1;
        (*(void **)((u8 *)arg0 + 0xC)) = (void *) (*(void **)((u8 *)temp_s1 + 0x3C));
    }
    func_00184428();
    return temp_s1;
}

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017EF98);

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017F160);

void func_0017F1A0(void) {
    s32 sp0[8];
    if (D_0028CAA8 == -1) {
        sp0[2] = 1;
        sp0[1] = 1;
        sp0[5] = 0;
        D_0028CAA8 = func_0017B8E0(sp0);
        D_0028CAAC = func_0017B8E0(sp0);
    }
}

INCLUDE_ASM("asm/nonmatchings/main_023", func_0017F200);

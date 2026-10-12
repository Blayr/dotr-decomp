#include "common.h"

s32 func_00109CA0(s32 arg0) {
    D_0030FF40 = (s32 *)arg0;
    D_0030FF48 = arg0 + 0x2A80;
    func_00198948(D_0030FF40, 0, 0x2A80);
    *(s32 *)((u8 *)D_0030FF40 + 0x1DC) = -1;
    *(s32 *)((u8 *)D_0030FF40 + 0x1F4) = -1;
    *(s32 *)((u8 *)D_0030FF40 + 0x2248) = -1;
    *(s32 *)((u8 *)D_0030FF40 + 0x2254) = -1;
    *(s32 *)((u8 *)D_0030FF40 + 0x224C) = -1;
    *(s32 *)((u8 *)D_0030FF40 + 0x2258) = -1;
    *(s32 *)((u8 *)D_0030FF40 + 0x2250) = -1;
    *(s32 *)((u8 *)D_0030FF40 + 0x225C) = -1;
    func_0010BDC0();
    func_00109A90();
    return 1;
}

void func_00109D50(void) {
    func_0010C720(0xF004, D_0030FF40[5]);
}

void func_00109D70(s32 arg0) {
    if (arg0 != 0) {
        func_0010A160(0, 0);
        func_0010C720(0x5004, 0x7FFF);
    }
    func_0010C720(0xF006, arg0);
}

void func_00109DC0(void) {
    s32 temp_v0;

    if (D_0030FF40 == NULL || D_0030FF48 == 0) {
        return;
    }
    if (D_0030FF40[0] & 1) {
        if (func_0010C720(0x5002) == 0) {
            func_00198790((u8 *)D_0030FF40 + 0x54, (u8 *)D_0030FF40 + 0x180, 0x10);
            D_0030FF40[0x1EC / 4] = D_0030FF40[0x60 / 4];
            temp_v0 = D_0030FF40[0x5C / 4];
            if (temp_v0 != 0) {
                D_0030FF40[0x18 / 4] = temp_v0;
            }
        }
        func_0010BE60();
        func_0010ADB0();
        func_0010B6C0();
        func_0010A4D0();
    }
}

s32 func_00109E80(s32 arg0, s32 arg1) {
    if (D_0030FF40 == NULL || D_0030FF48 == 0) {
        return 0;
    }
    if (!(D_0030FF40[1] & 2)) {
        return 1;
    }
    if (D_0030FF40[0] & 1) {
        if (arg1 != 0) {
            func_0010B490(arg0);
        } else {
            func_0010B3C0(arg0);
        }
    }
    return 1;
}

s32 func_00109F10(void) {
    if (D_0030FF40 == NULL || D_0030FF48 == 0) {
        return 0;
    }
    return (*D_0030FF40 & 0x2000) ? 1 : 0;
}

void func_00109F60(s32 arg0) {
    if (D_0030FF40 == NULL || D_0030FF48 == 0) {
        return;
    }
    func_0010C720(0xF003, arg0);
    *(s32 *)((u8 *)D_0030FF40 + 0x2A6C) = arg0;
}

void func_00109FC0(void) {
    if (D_0030FF40 == NULL || D_0030FF48 == 0) {
        return;
    }
    func_0010A010();
    func_0010A450();
}

void func_0010A010(void) {
    if (D_0030FF40 == NULL || D_0030FF48 == 0) {
        return;
    }
    if (D_0030FF40[1] & 2) {
        if (D_0030FF40[0] & 1) {
            func_0010B270();
        }
        D_0030FF40[0] &= ~0x200;
    }
}

void func_0010A090(s16 arg0) {
    if (D_0030FF40 == NULL || D_0030FF48 == 0) {
        return;
    }
    if (D_0030FF40[1] & 2) {
        func_0010C720(0x5003, arg0);
    }
}

static inline u32 flags_0010A0F0(void) {
    if (D_0030FF40 == NULL) {
        return 0;
    }
    return *(u32 *)D_0030FF40;
}

s32 func_0010A0F0(void) {
    if (D_0030FF40 == NULL || D_0030FF48 == 0) {
        return 0;
    }
    if ((u64)flags_0010A0F0() & 0x100) {
        return D_0030FF40[0x1EC / sizeof(s32)];
    }
    return 0;
}

void func_0010A160(s32 arg0, s32 arg1) {
    if (D_0030FF40 == NULL || D_0030FF48 == 0) {
        return;
    }
    if ((D_0030FF40[1] & 2) && (D_0030FF40[0] & 1)) {
        if (arg1 < 0) {
            arg1 = -arg1;
        }
        func_0010C720(0x5005, arg0, arg1);
    }
}

void func_0010A1D0(s32 arg0, s32 arg1, s32 arg2) {
    if (D_0030FF40 == NULL || D_0030FF48 == 0) {
        return;
    }
    if ((D_0030FF40[1] & 4) && (D_0030FF40[0] & 1) && ((s64)func_0010A8A0() & 0x80)) {
        func_0010C720(0x5210, arg0, arg1, arg2, 0);
    }
}

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010A280);

void func_0010A390(s32 arg0, s32 arg1, s32 arg2) {
    func_0010A280(arg0, arg1, 0, 0, 0, arg2);
}

void func_0010A3B0(s32 arg0, s32 arg1) {
    if (D_0030FF40 == NULL || D_0030FF48 == 0) {
        return;
    }
    if ((D_0030FF40[1] & 4) && (D_0030FF40[0] & 1) && ((s64)func_0010A8A0() & 0x80)) {
        func_0010C720(0x5201, arg0, arg1);
    }
}

void func_0010A450(void) {
    if (D_0030FF40 == NULL || D_0030FF48 == 0) {
        return;
    }
    if ((D_0030FF40[1] & 4) && (D_0030FF40[0] & 1) && ((s64)func_0010A8A0() & 0x80)) {
        func_0010C720(0x5202);
    }
}

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010A4D0);

s32 func_0010A780(s32 arg0) {
    s16 left;
    s16 *src;
    s16 *dst;
    s32 row;
    u32 column;
    s16 *dst2;
    s16 right;

    func_0017BB60(0);
    row = 0;
    src = (s16 *)(D_0030FF48 + 0x800);
    src += arg0 >> 1;
    dst = (s16 *)((u8 *)D_0030FF48 + 0x181800);
    do {
        dst2 = dst + 0x100;
        column = 0;
        do {
            s16 *end;

            left = src[0];
            right = src[1];
            src += 2;
            if (D_0030FF40[0x2A6C / 4] != 0) {
                right = (left + right) >> 1;
                left = right;
            }
            dst[0] = left;
            dst[1] = left;
            dst2[0] = right;
            dst2[1] = right;
            dst += 2;
            dst2 += 2;
            end = (s16 *)(D_0030FF48 + 0x800);
            end = (s16 *)((s32)end + 0x100000);
            if ((s32)src >= (s32)end) {
                src = (s16 *)((s32)src - 0x100000);
            }
            column++;
        } while (column < 0x80U);
        arg0 += 0x200;
        dst = dst2;
        arg0 %= 0x100000;
        row++;
    } while (row < 0x80);
    return arg0;
}

s32 func_0010A8A0(void) {
    return *D_0030FF40;
}

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010A8B0);

extern u8 D_002B90A0[];

typedef struct Entry_0010A8D0 {
    s32 size;
    s32 id;
    s32 start;
    s32 end;
} Entry_0010A8D0;

typedef struct Table_0010A8D0 {
    u8 header[0x210];
    Entry_0010A8D0 entries[0x100];
} Table_0010A8D0;

static inline s32 find_0010A8D0(s32 id) {
    s32 i = 0;
    do {
        if (((Table_0010A8D0 *) D_0030FF40)->entries[i].id == id) {
            return i;
        }
        i++;
    } while (i < 0x100);
    return -1;
}

static inline void clear_0010A8D0(s32 count, s32 offset) {
    __int128 *ptr;

    if (count > 0x20000) {
        count = 0x20000;
    }
    ptr = (__int128 *) ((u8 *) D_0030FF48 + 0x800);
    count >>= 4;
    ptr = (__int128 *) ((u8 *) ptr + (*(s32 *) ((u8 *) D_0030FF40 + 0x1D0) + offset));
    if (count != 0) {
        do {
            *ptr = 0;
            ptr++;
            if ((u8 *) ptr >= (u8 *) D_0030FF48 + 0x100800) {
                ptr = (__int128 *) ((u8 *) ptr - 0x100000);
            }
            count--;
        } while (count != 0);
    }
}

void func_0010A8D0(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_s2;
    s32 temp_s3;
    s32 temp_s3_2;
    s32 temp_s4;
    s32 temp_s5;
    s32 temp_s6;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_s0;
    s32 var_s1;
    s32 var_s2;
    s32 var_s3;
    s32 var_s7;

    var_s0 = arg2;
    var_s1 = arg1;
    var_a0 = find_0010A8D0(arg0);
    if (var_a0 >= 0) {
        temp_s3 = D_0030FF40[var_a0 * 4 + 0x84];
        temp_s4 = D_0030FF40[var_a0 * 4 + 0x86] * 4;
        temp_s5 = D_0030FF40[var_a0 * 4 + 0x87] * 4;
        temp_s3 &= ~0xF;
        temp_s4 &= ~0xF;
        temp_s5 &= ~0xF;
        if (var_s1 < temp_s3) {
            func_0019B648((u8 *) D_0030FF40 + 0x1210, D_002B90A0, arg0);
            if (temp_s5 != 0) {
                while (var_s1 + var_s0 > temp_s5) {
                    temp_s3_2 = temp_s5 - var_s1;
                    var_s7 = temp_s3_2;
                    func_0019B648((u8 *) D_0030FF40 + 0x1210, D_002B90A0, arg0);
                    temp_a1 = *(s32 *) ((u8 *) D_0030FF40 + 0x1D0);
                    if ((temp_a1 + temp_s3_2) >= 0x100000) {
                        temp_s6 = 0x100000 - temp_a1;
                        func_0010C110((u8 *) D_0030FF40 + 0x1210, (void *) (D_0030FF48 + temp_a1 + 0x800), var_s1 + 0x800, temp_s6);
                        var_s1 += temp_s6;
                        var_s7 -= temp_s6;
                        *(s32 *) ((u8 *) D_0030FF40 + 0x1D0) = 0;
                    }
                    if (var_s7 != 0) {
                        func_0010C110((u8 *) D_0030FF40 + 0x1210, (void *) (D_0030FF48 + *(s32 *) ((u8 *) D_0030FF40 + 0x1D0) + 0x800), var_s1 + 0x800, var_s7);
                        *(s32 *) ((u8 *) D_0030FF40 + 0x1D0) += var_s7;
                    }
                    var_s0 -= temp_s3_2;
                    var_s1 = temp_s4;
                }
            } else if (temp_s3 < var_s1 + var_s0) {
                var_a0_2 = var_s1 + var_s0 - temp_s3;
                var_s0 -= var_a0_2;
                clear_0010A8D0(var_a0_2, var_s0);
            }
            var_s3 = var_s0;
            var_s2 = var_s1;
            func_0019B648((u8 *) D_0030FF40 + 0x1210, D_002B90A0, arg0);
            temp_a1_2 = *(s32 *) ((u8 *) D_0030FF40 + 0x1D0);
            if ((temp_a1_2 + var_s0) >= 0x100000) {
                temp_s2 = 0x100000 - temp_a1_2;
                func_0010C110((u8 *) D_0030FF40 + 0x1210, (void *) (D_0030FF48 + temp_a1_2 + 0x800), var_s1 + 0x800, temp_s2);
                var_s3 = var_s0 - temp_s2;
                var_s2 = var_s1 + temp_s2;
                *(s32 *) ((u8 *) D_0030FF40 + 0x1D0) = 0;
            }
            if (var_s3 != 0) {
                func_0010C110((u8 *) D_0030FF40 + 0x1210, (void *) (D_0030FF48 + *(s32 *) ((u8 *) D_0030FF40 + 0x1D0) + 0x800), var_s2 + 0x800, var_s3);
                *(s32 *) ((u8 *) D_0030FF40 + 0x1D0) += var_s3;
            }
            var_s1 += var_s0;
            *(s32 *) ((u8 *) D_0030FF40 + 0x1CC) = var_s1;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010AC20);

void func_0010ADB0(void) {
    s32 flags;
    s32 input;
    s32 mode;

    if ((D_0030FF40[1] & 2) &&
        ((flags = D_0030FF40[0]) & 0x10) &&
        (flags & 0x20) && (flags & 0x40)) {
        if (D_0030FF40[0x7B] == 0) {
            func_0010B270();
        }
        switch (D_0030FF40[0x79]) {
        default:
            D_0030FF40[0x79] = 0;
            break;
        case 100:
            if (func_0010A0F0() == 0) {
                func_0010B270();
                D_0030FF40[0x72] = 0;
                D_0030FF40[0x73] = 0;
                D_0030FF40[0x74] = 0;
                D_0030FF40[0x79]++;
            }
            break;
        case 101:
        case 102:
        case 103:
            D_0030FF40[0x79]++;
            break;
        case 104:
            if (D_0030FF40[0x892] == 0x23A7) {
                D_0030FF40[0] &= ~0x100;
                D_0030FF40[0] &= ~0x2000;
                D_0030FF40[0] &= ~0x200;
                D_0030FF40[0x77] = 0x23A7;
                D_0030FF40[0x79] = 0;
            } else {
                D_0030FF40[0x79] = 1;
                D_0030FF40[0x77] = D_0030FF40[0x892];
            }
            break;
        case 1:
            if (D_0030FF40[0x7F] & 2) {
                func_0010A8D0(D_0030FF40[0x77], 0, 0x90000);
            } else {
                func_0010A8D0(D_0030FF40[0x77], 0, 0x100000);
            }
            D_0030FF40[0x79]++;
            return;
        case 2:
            if (func_0010BDE0() == 0) {
                D_0030FF40[6] = 0;
                D_0030FF40[0x71] = 0;
                D_0030FF40[0x70] = 0;
                D_0030FF40[0x76] = 0;
                func_0010AC20(0);
                D_0030FF40[0x79]++;
            }
            return;
        case 3:
            if (func_0010BE20() == 0) {
                func_0010AC20(0);
                D_0030FF40[0x79]++;
            }
            return;
        case 4:
            if (func_0010BE20() == 0) {
                if (D_0030FF40[0x7F] & 2) {
                    D_0030FF40[0x7F] &= ~2;
                    D_0030FF40[0x79]++;
                } else {
                    D_0030FF40[0x7F] = 4;
                    D_0030FF40[0x79] = 0;
                    D_0030FF40[0] &= ~0x2000;
                }
            }
            break;
        case 5:
            func_0010A8D0(D_0030FF40[0x77], 0x90000, 0x70000);
            func_0010B270();
            func_0010B1F0();
            D_0030FF40[0x79]++;
            return;
        case 6:
            if (func_0010BDE0() == 0) {
                D_0030FF40[0x79] = 0;
                D_0030FF40[0] &= ~0x2000;
            }
            break;
        }
        if (D_0030FF40[0] & 0x100) {
            if ((D_0030FF40[0x71] & 0x01000000) !=
                ((input = D_0030FF40[6]) & 0x01000000)) {
                D_0030FF40[0x71] = input;
                D_0030FF40[0x70] = D_0030FF40[0x71];
                D_0030FF40[0x76] = (D_0030FF40[0x70] & 0x01000000) ? 0 : 1;
                func_0010AC20(0);
                if ((D_0030FF40[0] & 0x100) &&
                    ((mode = D_0030FF40[0x72]) == 0 || mode == 0xA0000)) {
                    func_0010A8D0(D_0030FF40[0x77], D_0030FF40[0x73], 0x80000);
                }
                D_0030FF40[0x70] = 0;
            }
        }
    }
}

s32 func_0010B1F0(void) {
    D_0030FF40[0] |= 0x100;
    D_0030FF40[0x1FC / 4] &= ~4;
    D_0030FF40[0x1D4 / 4] = 0;
    D_0030FF40[0x2254 / 4] = D_0030FF40[0x1DC / 4];
    func_0010C720(0x1020, D_0030FF40[0x14 / 4], 0x40000, 1);
    return 1;
}

s32 func_0010B270(void) {
    s32 temp_v1;

    if (!(D_0030FF40[1] & 2)) {
        return 0;
    }
    temp_v1 = D_0030FF40[0];
    if (temp_v1 & 0x100) {
        D_0030FF40[0] = temp_v1 & ~0x100;
        D_0030FF40[0] &= ~0x200;
        *(s32 *)((u8 *)D_0030FF40 + 0x18) = 0;
        *(s32 *)((u8 *)D_0030FF40 + 0x1C4) = 0;
        *(s32 *)((u8 *)D_0030FF40 + 0x1C0) = 0;
        func_0010C720(0x1021);
        *(s32 *)((u8 *)D_0030FF40 + 0x1D4) = 0;
        *(s32 *)((u8 *)D_0030FF40 + 0x1D8) = 0;
        *(s32 *)((u8 *)D_0030FF40 + 0x2254) = -1;
    }
    return 1;
}

void func_0010B330(void) {
    s32 temp_a0;

    temp_a0 = *D_0030FF40;
    if (!(temp_a0 & 0x10)) {
        *D_0030FF40 = temp_a0 | 0x10;
    }
}

void func_0010B360(void) {
    if (!(D_0030FF40[0] & 0x40)) {
        func_0010C720(0x5000);
        D_0030FF40[0] |= 0x40;
        D_0030FF40[0x7A] = -1;
    }
}

static inline s32 find_0010B3C0(s32 *base, s32 value) {
    u8 *entry;
    s32 i;

    for (i = 0, entry = (u8 *)&base[i * 4]; i < 0x100; i++, entry += 0x10) {
        if (*(s32 *)(entry + 0x214) == value) {
            return i;
        }
    }
    return -1;
}

s32 func_0010B3C0(s32 value) {
    if (!(D_0030FF40[1] & 2)) {
        return 0;
    }

    func_0010A090(0x100);
    *(s32 *)((u8 *)D_0030FF40 + 0x2248) = value;

    if (find_0010B3C0(D_0030FF40, value) < 0) {
        if (value != 0x23A7) {
            return 0;
        }
    }

    *(s32 *)((u8 *)D_0030FF40 + 0x1FC) = 1;
    *(s32 *)((u8 *)D_0030FF40 + 0x1E4) = 0x64;
    D_0030FF40[0] |= 0x2000;
    return 1;
}

static inline s32 find_0010B490(s32 id) {
    s32 *entry;
    s32 i;

    i = 0;
    entry = &D_0030FF40[i * 4];

    do {
        if (entry[0x85] == id) {
            return i;
        }
        i++;
        entry += 4;
    } while (i < 0x100);
    return -1;
}

s32 func_0010B490(s32 id) {
    s32 i;
    s32 current;

    if ((D_0030FF40[1] & 2) == 0) {
        return 0;
    }

    i = find_0010B490(id);
    if (i < 0 && id != 0x23A7) {
        return 0;
    }

    D_0030FF40[0x892] = id;
    current = D_0030FF40[0x77];
    if (current == id && (D_0030FF40[0] & 0x100) != 0) {
        if (D_0030FF40[0x7B] < 0x7FFF) {
            func_0010C720(0x5004, 0x100);
        }
        if ((D_0030FF40[0] & 0x2000) != 0) {
            D_0030FF40[0] &= ~0x2000;
        }
        return 1;
    }

    if (D_0030FF40[0x7F] == 4 && current == id) {
        D_0030FF40[0] |= 0x100;
        D_0030FF40[0x7F] &= ~4;
        D_0030FF40[0x75] = 0;
        D_0030FF40[0x895] = D_0030FF40[0x77];
        func_0010C720(0x1020, D_0030FF40[5], 0x40000, 1);
        return 1;
    }

    if ((D_0030FF40[1] & 2) != 0) {
        s32 j;

        func_0010A090(0x100);
        D_0030FF40[0x892] = id;
        j = find_0010B490(id);
        if (j >= 0 || id == 0x23A7) {
            D_0030FF40[0x7F] = 1;
            D_0030FF40[0x79] = 0x64;
            D_0030FF40[0] |= 0x2000;
        }
    }

    D_0030FF40[0x7F] |= 2;
    return 1;
}

void func_0010B6C0(void) {
    u8 request[0x1C];
    s32 command;

    if (D_0030FF40 != NULL && (D_0030FF40[1] & 4)) {
        switch (D_0030FF40[0x82C]) {
        case 1:
            if (func_0010C2C0() == 0) {
                func_0010C220((s32)((u8 *)D_0030FF48 + 0x101800),
                             D_0030FF40[5] + 0x40000, 0x80800);
                D_0030FF40[0x82C]++;
            }
            break;
        case 2:
            if (func_0010BE20() == 0) {
                func_0010C720(0x5100, D_0030FF40[0x82D],
                             D_0030FF40[5] + 0x40000);
                D_0030FF40[0x82C]++;
            }
            break;
        case 3:
            if (((u8 *)D_0030FF40)[0x5A] == 0) {
                D_0030FF40[0x82C] = 0;
                D_0030FF40[0] &= ~0x4000;
            }
            break;
        case 20:
            if (func_0010C290() == 0) {
                D_0030FF40[0x82C] = 1;
            }
            break;
        case 30:
            if (func_0010C290() == 0) {
                D_0030FF40[0x82C]++;
            }
            break;
        case 31:
            if (func_0010C2C0() == 0) {
                D_0030FF40[0x82E] = *(s32 *)((u8 *)D_0030FF48 + 0x101804) + 0x800;
                D_0030FF40[0x82F] = 0;
                if (D_0030FF40[0x82E] <= 0x80800) {
                    D_0030FF40[0x830] = D_0030FF40[0x82E];
                } else {
                    D_0030FF40[0x830] = 0x80800;
                }
                func_0010C220((s32)((u8 *)D_0030FF48 + 0x101800),
                             D_0030FF40[5] + 0x40000, D_0030FF40[0x830]);
                D_0030FF40[0x82E] -= D_0030FF40[0x830];
                *(u32 *)&D_0030FF40[0x82F] += D_0030FF40[0x830];
                D_0030FF40[0x82C]++;
            }
            break;
        case 32:
            if (func_0010BE20() == 0) {
                func_0010C720(0x5102, D_0030FF40[0x82D],
                             D_0030FF40[5] + 0x40000, D_0030FF40[0x830], 0);
                if (D_0030FF40[0x82E] > 0) {
                    D_0030FF40[0x82C]++;
                } else {
                    D_0030FF40[0x82C] = 3;
                }
            }
            break;
        case 33:
            if (((u8 *)D_0030FF40)[0x5A] == 0) {
                if (D_0030FF40[0x82E] <= 0x80800) {
                    D_0030FF40[0x830] = D_0030FF40[0x82E];
                } else {
                    D_0030FF40[0x830] = 0x80800;
                }
                func_0010C110(D_0030FF40 + 0x81C,
                             (u8 *)D_0030FF48 + 0x101800,
                             D_0030FF40[0x82F], D_0030FF40[0x830]);
                D_0030FF40[0x82C]++;
            }
            break;
        case 34:
            if (func_0010C290() == 0) {
                D_0030FF40[0x82C]++;
            }
            break;
        case 35:
            if (func_0010C2C0() == 0) {
                func_0010C220((s32)((u8 *)D_0030FF48 + 0x101800),
                             D_0030FF40[5] + 0x40000, D_0030FF40[0x830]);
                D_0030FF40[0x82E] -= D_0030FF40[0x830];
                *(u32 *)&D_0030FF40[0x82F] += D_0030FF40[0x830];
                D_0030FF40[0x82C]++;
            }
            break;
        case 36:
            if (func_0010BE20() == 0) {
                func_0010C720(0x5102, D_0030FF40[0x82D],
                             D_0030FF40[5] + 0x40000, D_0030FF40[0x830],
                             D_0030FF40[0x82F] - D_0030FF40[0x830] - 0x800);
                if (D_0030FF40[0x82E] > 0) {
                    D_0030FF40[0x82C] = 33;
                } else {
                    D_0030FF40[0x82C] = 3;
                }
            }
            break;
        default:
            D_0030FF40[0x82C] = 0;
            if (func_0010BD40(&command, request) != 0) {
                func_0010BC30(command, (s32)request);
            }
            break;
        }
    }
}

s32 func_0010BBC0(void) {
    if (D_0030FF40 == NULL) {
        return 0;
    }
    if (!(D_0030FF40[1] & 4)) {
        return 0;
    }
    if (D_0030FF40[0] & 1) {
        return func_0010BCC0();
    }
    return 0;
}

void func_0010BC30(s32 arg0, s32 arg1) {
    *(s32 *)((u8 *)D_0030FF40 + 0x20B4) = arg0;
    func_0019B648((u8 *)D_0030FF40 + 0x2070, D_002B90B0, arg1);
    func_0010C110((u8 *)D_0030FF40 + 0x2070, (u8 *)D_0030FF48 + 0x101800, 0, 0x80800);
    *D_0030FF40 |= 0x4000;
    *(s32 *)((u8 *)D_0030FF40 + 0x20B0) = 0x1E;
}

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010BCC0);

s32 func_0010BD40(s32 *arg0, void *arg1) {
    s32 temp_v1_2;
    s8 temp_v1;

    temp_v1 = *(s8 *)((u8 *)D_0030FF40 + 0x20C5);
    if (temp_v1 == *(s8 *)((u8 *)D_0030FF40 + 0x20C4)) {
        return 0;
    }
    *(s8 *)((u8 *)D_0030FF40 + 0x20C5) = (s8)((temp_v1 + 1) & 7);
    temp_v1_2 = temp_v1 << 5;
    *arg0 = *(s32 *)(temp_v1_2 + (u32)D_0030FF40 + 0x20C8);
    func_0019C2B8(arg1, (u8 *)D_0030FF40 + temp_v1_2 + 0x20CC, 0x1C);
    return 1;
}

void func_0010BDC0(void) {
    *((s8 *)D_0030FF40 + 0x20C5) = 0;
    *((s8 *)D_0030FF40 + 0x20C4) = 0;
}

s32 func_0010BDE0(void) {
    s32 temp_v0;
    s32 temp_v0_2;

    temp_v0_2 = D_0030FF40[0x1710 / sizeof(s32)];
    if (temp_v0_2 != 0) {
        return temp_v0_2;
    }
    temp_v0 = D_0030FF40[0x171C / sizeof(s32)];
    if (temp_v0 != 0) {
        return temp_v0;
    }
    return 0;
}

s32 func_0010BE20(void) {
    s32 temp_v0;
    s32 temp_v0_2;

    temp_v0_2 = *(s32 *)((u8 *)D_0030FF40 + 0x1820);
    if (temp_v0_2 != 0) {
        return temp_v0_2;
    }
    temp_v0 = *(s32 *)((u8 *)D_0030FF40 + 0x182C);
    if (temp_v0 != 0) {
        return temp_v0;
    }
    return 0;
}

typedef struct {
    u8 data[0x40];
    s32 arg1;
    s32 arg2;
    s32 arg3;
} Request_0010BE60;

typedef struct {
    s32 arg0;
    s32 arg1;
    s32 arg2;
    s32 reserved;
} Request2_0010BE60;

typedef struct {
    s32 flags;
    u8 padding[0x124C];
    Request_0010BE60 requests[16];
    s32 pending;
    s32 write;
    s32 read;
    s32 state;
    Request2_0010BE60 requests2[16];
    s32 pending2;
    s32 write2;
    s32 read2;
    s32 state2;
} Queues_0010BE60;

void func_0010BE60(void) {
    extern s32 D_0030FF50;
    Queues_0010BE60 *queues;
    Queues_0010BE60 *queues2;
    s32 state2;
    s32 state;
    Request_0010BE60 *request;
    Request2_0010BE60 *request2;
    s32 *stateField;
    s32 *state2Field;

    queues = (Queues_0010BE60 *)D_0030FF40;
    stateField = &queues->state;
    state = *stateField;
    if (state != 0) {
        request = &queues->requests[queues->read];
        switch (state) {
        case 1:
            if (func_0010C2C0() == 0) {
                func_0010C2D0((s32)request, request->arg1, request->arg2, request->arg3);
                ((Queues_0010BE60 *)D_0030FF40)->state++;
                ((Queues_0010BE60 *)D_0030FF40)->flags |= 0x800000;
            }
            break;
        case 2:
            if (func_0010C2C0() == 0) {
                D_0030FF50++;
                ((Queues_0010BE60 *)D_0030FF40)->flags &= 0xFF7FFFFF;
                ((Queues_0010BE60 *)D_0030FF40)->read = (((Queues_0010BE60 *)D_0030FF40)->read + 1) % 16;
                ((Queues_0010BE60 *)D_0030FF40)->state++;
            }
            break;
        default:
            *stateField = 0;
            break;
        }
    } else if (queues->pending != 0) {
        *stateField = 1;
        ((Queues_0010BE60 *)D_0030FF40)->pending--;
    }
    queues2 = (Queues_0010BE60 *)D_0030FF40;
    state2Field = &queues2->state2;
    state2 = *state2Field;
    if (state2 != 0) {
        request2 = &queues2->requests2[queues2->read2];
        switch (state2) {
        case 1:
            if (func_0010C8A0() < 0) {
                func_0010C800(request2->arg0, request2->arg1, request2->arg2);
                ((Queues_0010BE60 *)D_0030FF40)->state2++;
                ((Queues_0010BE60 *)D_0030FF40)->flags |= 0x08000000;
                return;
            }
            break;
        case 2:
            if (func_0010C8A0() < 0) {
                ((Queues_0010BE60 *)D_0030FF40)->flags &= 0xF7FFFFFF;
                ((Queues_0010BE60 *)D_0030FF40)->read2 = (((Queues_0010BE60 *)D_0030FF40)->read2 + 1) % 16;
                ((Queues_0010BE60 *)D_0030FF40)->state2++;
                return;
            }
            break;
        default:
            *state2Field = 0;
            return;
        }
    } else if (queues2->pending2 != 0) {
        *state2Field = 1;
        ((Queues_0010BE60 *)D_0030FF40)->pending2--;
    }
}

typedef struct {
    char name[0x40];
    u8 *data;
    s32 offset;
    s32 size;
} Request_0010C110;

typedef struct {
    u8 padding[0x1250];
    Request_0010C110 requests[16];
    s32 count;
    s32 index;
} Queue_0010C110;

void func_0010C110(void *arg0, void *arg1, s32 arg2, s32 arg3) {
    Request_0010C110 *request;

    request = &((Queue_0010C110 *)D_0030FF40)->requests[((Queue_0010C110 *)D_0030FF40)->index];
    func_0019BDD8(request->name, (const char *)arg0);
    request->data = arg1;
    request->offset = arg2;
    request->size = arg3;
    request->offset &= ~0x7FF;
    request->data -= arg2 - request->offset;
    request->size += arg2 - request->offset;
    request->size += 0x7FF;
    request->size &= ~0x7FF;
    ((Queue_0010C110 *)D_0030FF40)->index = (((Queue_0010C110 *)D_0030FF40)->index + 1) % 16;
    ((Queue_0010C110 *)D_0030FF40)->count++;
}

typedef struct QueueEntry_0010C220 {
    s32 value0;
    s32 value1;
    s32 value2;
    s32 unused;
} QueueEntry_0010C220;

typedef struct Queue_0010C220 {
    u8 padding[0x1720];
    QueueEntry_0010C220 entries[16];
    s32 count;
    s32 write_index;
} Queue_0010C220;

void func_0010C220(s32 arg0, s32 arg1, s32 arg2) {
    QueueEntry_0010C220 *entry;

    entry = &((Queue_0010C220 *)D_0030FF40)->entries[((Queue_0010C220 *)D_0030FF40)->write_index];
    entry->value0 = arg0;
    entry->value1 = arg1;
    entry->value2 = arg2;
    ((Queue_0010C220 *)D_0030FF40)->write_index = (((Queue_0010C220 *)D_0030FF40)->write_index + 1) % 16;
    ((Queue_0010C220 *)D_0030FF40)->count++;
}

s32 func_0010C290(void) {
    s32 var_v0;

    var_v0 = 1;
    if ((D_0030FF40[0x5C4] == 0) && (D_0030FF40[0x5C7] == 0)) {
        var_v0 = 0;
    }
    return var_v0;
}

s32 func_0010C2C0(void) {
    return D_0030FF58;
}

s32 func_0010C2D0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (!(arg1 & 0xF)) {
        if ((arg2 % 2048) == 0) {
            if ((arg3 % 2048) == 0) {
                D_0030FFA0 = 0;
                D_0030FFA4 = 0;
                D_0030FFA8 = 0;
                D_0030FFAC = 0;
                D_0030FFB0 = 0;
                func_00199B50(D_002B90C0, arg0, arg1);
                if (func_00200510(arg0, arg2, arg3, arg1, func_0010C580, 0, 0x20) == 0) {
                    return -1;
                }
            }
        }
    }
    D_0030FF58 = 1;
    return 1;
}

s32 func_0010C3D0(s32 file, s32 destination, s32 position, s32 size) {
    s32 handle;
    s32 blockStart;
    s32 blockOffset;
    s32 blockSize;
    s32 totalSize;
    s32 copySize;

    func_00199B50(D_002B90DA, file, destination, position, size);
    func_00199B50(D_002B9102);
    if ((handle = func_00200360(file)) < 0) {
        return 0;
    }
    if ((destination & 0xF) || (position % 0x800) || (size % 0x800)) {
        while (size > 0) {
            blockStart = (position >> 11) << 11;
            totalSize = position - blockStart;
            totalSize += size;
            blockSize = totalSize < 0x80001 ? totalSize : 0x80000;
            blockOffset = position - blockStart;
            size = totalSize - blockSize;
            position = blockStart + blockSize;
            func_00199B50(D_002B9112, file, handle);
            func_002003E0(handle, blockStart, ((blockSize + 0x7FF) >> 11) << 11, 0x04000000);
            copySize = blockSize - blockOffset;
            func_00198790((void *)destination, (u8 *)0x04000000 + blockOffset, copySize);
            destination += copySize;
        }
    } else {
        func_00199B50(D_002B9127);
        func_002003E0(handle, position, size, destination);
    }
    func_00199B50(D_002B9135);
    func_002004C0(handle);
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010C580);

typedef char *VaList_0010C720;
#define VA_START_0010C720(ap, parm) \
    ((ap) = (char *)__builtin_next_arg(parm) - (__builtin_args_info(2) >= 8 ? 0 : (8 - __builtin_args_info(2)) * 8))
#define VA_ARG_0010C720(ap, T) (*(T *)((ap += 8) - 8))

extern s32 func_0017EA80(s32 *, s32, s32, s32 *, s32, s32 *, s32, s32, s32);

s32 func_0010C720(s32 cmd, ...) {
    s32 id;
    s32 i;
    VaList_0010C720 ap;

    if (D_0030FF40 == NULL) {
        return 0;
    }
    id = cmd;
    VA_START_0010C720(ap, cmd);
    D_0030FF40[0x20] = (s32)&D_0030FF40[0x20];
    for (i = 1; i < 7; i++) {
        D_0030FF40[0x20 + i] = VA_ARG_0010C720(ap, s32);
    }
    return func_0017EA80(&D_0030FF40[7], id, 0, &D_0030FF40[0x20], 0x40, &D_0030FF40[0x60], 0x10, 0, 0);
}

s32 func_0010C800(s32 arg0, s32 arg1, s32 arg2) {
    func_0017BB60(0);
    D_0030FF40[0x11] = arg0;
    D_0030FF40[0x12] = arg1;
    D_0030FF40[0x13] = arg2;
    D_0030FF40[0x14] = 0;
    D_0030FF40[0x19] = func_0017BCA0(&D_0030FF40[0x11], 1);
    return D_0030FF40[0x19];
}

s32 func_0010C8A0(void) {
    return func_0017BC80(D_0030FF40[0x64 / sizeof(s32)]);
}

s32 func_0010C8B0(void) {
    s32 count;

    do {
        if (func_0017E8B0((u8 *)D_0030FF40 + 0x1C, 0x05730601, 0) < 0) {
            for (;;) {
            }
        }
        count = 1000000;
        while (count-- != 0) {
        }
    } while (D_0030FF40[0x10] == 0);
    func_0017BB60(0);
    return 1;
}

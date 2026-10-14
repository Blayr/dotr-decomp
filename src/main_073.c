#include "common.h"

s32 func_00250620(s32 arg0, s32 arg1) {
    extern s32 func_00215D30();
    s32 i;
    s32 id;
    s32 max;

    max = 0;
    for (i = 0; i < 2; i++) {
        if ((id = func_002159D0(arg0, i)) != 999) {
            if (max < func_00215D30(arg0, id)) {
                max = func_00215D30(arg0, id);
            }
        }
    }
    if ((max - 1) * 2 + func_0019A5C8() % 100 >= 90) {
        return arg1 + (func_0019A5C8() % 10 + 1);
    }
    return arg1 - func_0019A5C8() % 12 + 1;
}

void *func_00250740(s32 arg0, s32 arg1, s32 arg2) {
    void *var_v0;

    if (func_001DF540(arg0, arg1) == 0) {
        return NULL;
    }
    var_v0 = func_001E0B70(arg0, arg1, arg2);
    if (var_v0 == NULL) {
        return NULL;
    }
    if ((((s32 *)var_v0)[0] == -1) && (((s32 *)var_v0)[1] == -1)) {
        var_v0 = NULL;
    }
    return var_v0;
}

s32 func_002507D0(s32 arg0, s32 arg1) {
    s32 var_s0;

    if ((func_001E0700(arg0, arg1) >> 5) != 0) {
        return -1;
    }
    var_s0 = 0;
    do {
        if (func_00250740(arg0, arg1, var_s0) != NULL) {
            return 1;
        }
        var_s0++;
    } while (var_s0 <= 4);
    return 0;
}

s32 func_00250860(s32 arg0, s32 arg1) {
    switch (arg0) {
    case 0:
    case 1:
        if (arg1 < arg0) {
            return arg0;
        }
        return arg1;
    case 7:
    case 6:
    case 0x270F:
    case 0x1F4:
    case 0x5DC:
        return arg1 >= arg0 ? arg0 : arg1;
    default:
        return 0;
    }
}

s32 func_002508D0(s32 arg0) {
    if (arg0 < 0) {
        return 0;
    }
    arg0 = arg0 > 9999 ? 9999 : arg0;
    return arg0;
}

s32 func_00250900(void *arg0) {
    u8 state;

    if (*((u8 *)arg0 + 0x45) == 0) {
        state = *((u8 *)arg0 + 0x44);
        if (state == 0 || state == 1) {
            return 1;
        }
    }
    return 0;
}

s32 func_00250940(s32 arg0, s32 arg1) {
    extern s32 func_001DEE50(s32);
    s32 i;
    s32 count;

    for (i = 0, count = 0; i < func_001DEE50(arg0); i++) {
        if (arg1 == (func_0026FCE0(func_001DEE00(arg0, i)) >> 5)) {
            count += 1;
        }
    }
    return count;
}

s32 func_002509E0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return func_002508D0(func_001E0290(arg0, arg1, 0) +
                         func_002660E0(func_001DF540(arg0, arg1), arg2, arg3, 1));
}

s32 func_00250A60(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_s0;

    temp_s0 = func_001E02F0((void *)arg0, 0);
    return func_002508D0(temp_s0 + func_002660E0(arg0, arg1, arg2, 1));
}

s32 func_00250AC0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_s0;
    s32 result;

    temp_s0 = func_002660E0(func_001DF540(arg0, arg1), arg2, arg3, 1);
    result = func_001E0290(arg0, arg1, 0);
    result += temp_s0;
    return result;
}

s32 func_00250B40(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 value;
    s32 base;

    value = func_002660E0(func_001DF540(arg0, arg1), arg2, arg3, 0);
    base = func_001E0370(arg0, arg1, 0);
    return func_002508D0(base + value);
}

void func_00250BC0(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_s0;

    temp_s0 = func_001E03D0((void *)arg0, 0);
    func_002508D0(temp_s0 + func_002660E0(arg0, arg1, arg2, 0));
}

s32 func_00250C20(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_s0;
    s32 result;

    temp_s0 = func_002660E0(func_001DF540(arg0, arg1), arg2, arg3, 0);
    result = func_001E0370(arg0, arg1, 0);
    return result + temp_s0;
}

s32 func_00250CA0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    switch (arg2) {
    case 0:
        if (arg3 + func_001E0290(arg0, arg1, 0) > 9999) {
            func_001E0450(arg0, arg1, 4, 9999 - func_001E0290(arg0, arg1, 1));
        } else {
            func_001E0450(arg0, arg1, 0, arg3);
        }
        break;
    case 1:
        if (func_001E0290(arg0, arg1, 0) - arg3 < 0) {
            func_001E0450(arg0, arg1, 4, -func_001E0290(arg0, arg1, 1));
        } else {
            func_001E0450(arg0, arg1, 1, arg3);
        }
        break;
    case 2:
        if (arg3 * func_001E0290(arg0, arg1, 0) > 9999) {
            func_001E0450(arg0, arg1, 4, 9999 - func_001E0290(arg0, arg1, 1));
        } else {
            func_001E0450(arg0, arg1, 2, arg3);
        }
        break;
    case 3:
        if (arg3 == 0) {
            return -1;
        }
        func_001E0450(arg0, arg1, 3, arg3);
        break;
    case 4:
        func_001E0450(arg0, arg1, 4, arg3);
        break;
    }
    return 1;
}

s32 func_00250E80(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    switch (arg2) {
    case 0:
        if (arg3 + func_001E0370(arg0, arg1, 0) > 9999) {
            func_001E0570(arg0, arg1, 4, 9999 - func_001E0370(arg0, arg1, 1));
        } else {
            func_001E0570(arg0, arg1, 0, arg3);
        }
        break;
    case 1:
        if (func_001E0370(arg0, arg1, 0) - arg3 < 0) {
            func_001E0570(arg0, arg1, 4, -func_001E0370(arg0, arg1, 1));
        } else {
            func_001E0570(arg0, arg1, 1, arg3);
        }
        break;
    case 2:
        if (arg3 * func_001E0370(arg0, arg1, 0) > 9999) {
            func_001E0570(arg0, arg1, 4, 9999 - func_001E0370(arg0, arg1, 1));
        } else {
            func_001E0570(arg0, arg1, 2, arg3);
        }
        break;
    case 3:
        if (arg3 == 0) {
            return -1;
        }
        func_001E0570(arg0, arg1, 3, arg3);
        break;
    case 4:
        func_001E0570(arg0, arg1, 4, arg3);
        break;
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_073", func_00251060);

s32 func_00251370(s32 count, u16 *src, void *dst) {
    u16 buffer[120];
    s32 row;
    s32 i;
    s32 result;
    u16 *read;
    u16 *write;

    for (i = 0; i < 120; i++) {
        buffer[i] = 999;
    }
    result = 0;
    if (count < 16) {
        if (count < 9) {
            for (; count < 8; count++) {
                src[count] = 820;
            }
        }
        for (i = 0; src[i] != 999; i++) {
            result++;
        }
        i = 0;
        do {
            row = 0;
            read = src;
            write = dst;
            do {
                write[4] = *read;
                row++;
                read++;
                write++;
            } while (row < 21);
            i++;
            dst = (u8 *)dst + 42;
        } while (i < 3);
    } else {
        result = 16;
        for (i = 0; i < 3; i++) {
            for (row = 0; row < count; row++) {
                buffer[row] = src[row];
            }
            for (row = 0; row < 16; row++) {
                ((u16 *)dst)[row + 4] = buffer[row];
            }
            dst = (u8 *)dst + 42;
        }
    }
    return result;
}

INCLUDE_ASM("asm/nonmatchings/main_073", func_002514F0);

void func_002516D0(s32 arg0, s32 arg1, s32 arg2) {
    extern s32 func_001E1900();
    extern s32 func_001E1CB0();
    extern s32 func_001E1D10();
    extern void func_001E1E70(s32, s32, s32, s32);

    if (arg2 == 1) {
        func_001E1900(arg0, arg1, 0x80);
        func_001E1B70(arg0, arg1, 1, func_001E1CB0(arg0, arg1));
        func_001E1C10(arg0, arg1, 1, func_001E1D10(arg0, arg1));
        func_001E1E70(arg0, arg1, 2, 1);
        func_001E1E70(arg0, arg1, 4, 1);
        return;
    }
    func_001E19D0(arg0, arg1, 0);
    func_001E1C10(arg0, arg1, -1, func_001E1D10(arg0, arg1));
    func_001E1E70(arg0, arg1, 2, 0);
    func_001E1E70(arg0, arg1, 4, 0);
}

typedef struct {
    u32 flags;
    u32 value;
} Script_002517D0;

s32 func_002517D0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 *out, s32 arg7) {
    Script_002517D0 *temp_v0;
    s32 spA8;
    s32 spAC;
    s32 temp_fp;
    s32 temp_s0;
    s32 temp_s1;
    s32 temp_s1_5;
    s32 temp_s1_6;
    s32 temp_s1_7;
    s32 temp_s1_8;
    s32 temp_s1_9;
    s32 temp_s3;
    s32 temp_s3_2;
    s32 temp_s3_4;
    s32 temp_s3_5;
    s32 temp_s4;
    s32 var_s4;
    s32 temp_s5;
    s32 temp_s7;
    s32 temp_v0_10;
    s32 temp_v0_11;
    s32 temp_v0_12;
    s32 temp_v0_13;
    s32 temp_v0_14;
    s32 temp_v0_15;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 temp_v0_7;
    s32 temp_v0_8;
    s32 temp_v0_9;
    s32 temp_v1;
    s32 temp_v1_3;
    s32 temp_v1_4;
    s32 var_s3;
    s32 var_s5;
    s32 var_s5_2;
    s32 var_s6;
    s32 var_s6_2;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v0_4;
    s32 var_v0_5;
    s32 var_v0_6;
    s32 var_v0_7;
    u32 temp_a1;
    u32 temp_a2;
    u32 temp_s1_2;
    u32 temp_s1_3;
    u32 temp_s1_4;
    u32 temp_v1_2;

    extern s32 func_001E1030();

    temp_fp = arg4;
    spAC = arg5;
    temp_s7 = arg7;
    if (func_001DF540(arg0, arg1) == 0) {
        return 0;
    }
    if ((temp_v0 = func_00250740(arg0, arg1, 4)) == NULL) {
        return 0;
    }
    temp_s1 = func_0024DE70(arg0, arg1);
    if (temp_s1 == func_0024DE70(arg2, arg3)) {
        return 0;
    }
    temp_s1_2 = temp_v0->flags;
    temp_a1 = temp_s1_2 >> 8;
    switch (temp_a1) {                              /* switch 1; irregular */
    case 0x2:                                       /* switch 1 */
        switch (*(u16 *)&temp_v0->value) {
        case 8:
            out[0] = 2;
            out[1] = (s32) ((spAC << 8) | temp_fp);
            out[2] = (s32) (temp_v0->value >> 0x10);
            out[3] = (s32) *(u16 *)&temp_v0->value;
            break;
        default:
            out[0] = 2;
            out[1] = (s32) ((spAC << 8) | temp_fp);
            out[2] = (s32) (temp_v0->value >> 0x10);
            out[3] = (s32) *(u16 *)&temp_v0->value;
            break;
        }
        return 1;
    case 0x13:                                      /* switch 1 */
        if ((temp_s1_2 & 0x3F) == 0x1A) {
            if (arg2 >= 0 && arg3 > 0 && temp_s7 == 0) {
                var_v0_2 = func_0024C780(0U, arg2, arg3);
            } else {
                return 0;
            }
        } else {
        spA8 = func_001E1090(arg0, arg1);
        temp_fp = temp_v0->value >> 0x10;
        if (temp_fp == 0) {
            temp_s1_3 = temp_v0->flags;
            var_v0_2 = func_0024CA40(0, 0, func_0024DE70(arg0, arg1), (temp_s1_3 >> 6) & 3, temp_s1_3 & 0x3F, 0xE);
        } else {
            temp_s1_4 = temp_v0->flags;
            var_v0_2 = func_0024CA40(spA8 & 0xFF, spA8 >> 8, func_0024DE70(arg0, arg1), (temp_s1_4 >> 6) & 3, temp_s1_4 & 0x3F, temp_fp);
        }
        }
        var_v0_3 = func_0024C7D0((u32) var_v0_2, arg0, arg1);
        if (temp_s7 != 0) {
            var_v0_3 = func_0024C7D0((u32) var_v0_3, arg2, arg3);
        }
        if (var_v0_3 == 0) {
            return 0;
        }
        out[0] = 0x39;
        out[1] = 0;
        out[2] = var_v0_3;
        out[3] = (s32) *(u16 *)&temp_v0->value;
        return 1;
    case 0x17:                                      /* switch 1 */
        temp_fp = temp_s1_2 & 0x3F;
        if (temp_fp == 0x1A) {
            if (arg2 >= 0 && arg3 > 0 && temp_s7 == 0) {
                var_v0 = func_0024C780(0U, arg2, arg3);
            } else {
                return 0;
            }
        } else {
        temp_fp = temp_s1_2 & 0x3F;
        var_v0 = func_0024CA40(0, 0, func_0024DE70(arg0, arg1), (temp_s1_2 >> 6) & 3, temp_fp, 0xE);
        }
        if (temp_s7 != 0) {
            var_v0 = func_0024C7D0((u32) var_v0, arg2, arg3);
        }
        out[0] = 0;
        out[1] = 0;
        out[2] = var_v0;
        out[3] = (s32) *(u16 *)&temp_v0->value;
        if (var_v0 == 0) {
            return 0;
        }
        return 0x401;
    case 0x24:                                      /* switch 1 */
        temp_v0_2 = func_0024C780(0U, arg0, arg1);
        out[0] = 0x1E;
        out[1] = 0;
        out[2] = temp_v0_2;
        out[3] = func_0024DE70(arg0, arg1);
        return 1;
    case 0xD:                                       /* switch 1 */
        temp_a2 = temp_v0->value;
        temp_v1 = (temp_s1_2 >> 6) & 3;
        temp_s1_5 = ((temp_a2 >> 0x10) << 0x10) | (temp_a2 & 0xFFFF);
        switch (temp_v1) {                          /* switch 2; irregular */
        case 1:                                     /* switch 2 */
            out[0] = 8;
            out[1] = 0;
            out[2] = func_0024DE20(func_0024DE70(arg0, arg1), ((u32) temp_v0->flags >> 6) & 3);
            out[3] = temp_s1_5;
            return 1;
        case 2:                                     /* switch 2 */
            out[0] = 9;
            out[1] = func_001E1090(arg0, arg1);
            out[2] = func_0024DE20(func_0024DE70(arg0, arg1), ((u32) temp_v0->flags >> 6) & 3);
            out[3] = temp_s1_5;
            return 1;
        default:                                    /* switch 2 */
            return 0;
        }
        break;
    case 0x14:                                      /* switch 1 */
        if ((temp_v0_3 = func_0026AB80((arg0 == 0) ? 1 : 0, 0x4C)) >= 0) {
            if (func_0026AB80(0, 0x2E) < 0) {
                out[0] = 0x66;
                out[1] = 1;
                out[2] = temp_v0_3;
                out[3] = 0;
                return 1;
            }
            if ((temp_v0_4 = func_0024E220(arg0, 1)) >= 0) {
                temp_v0_5 = func_0024C780(0U, arg0, arg1);
                out[0] = 0x1F;
                out[1] = (s32) ((arg0 << 8) | arg1 | 0x10000);
                out[2] = temp_v0_5;
                out[3] = temp_v0_4;
                return 0x103;
            }
            return 0;
        }
        if ((temp_v0_6 = func_0024E220(arg0, 1)) >= 0) {
            temp_v0_7 = func_0024C780(0U, arg0, arg1);
            out[0] = 0x1F;
            out[1] = (s32) ((arg0 << 8) | arg1 | 0x10000);
            out[2] = temp_v0_7;
            out[3] = temp_v0_6;
            return 0x101;
        }
        return 0;
    case 0x3E:                                      /* switch 1 */
        if ((temp_v0_8 = func_0026AB80((arg0 == 0) ? 1 : 0, 0x4C)) >= 0) {
            if (func_0026AB80(0, 0x2E) >= 0) {
                temp_s1_6 = func_0024DE70(arg0, arg1);
                temp_s3 = func_001DF470(arg0);
                if (func_002670F0(0x2C, (s32) *(u16 *)&temp_v0->value) < temp_s3 && func_0024E220(temp_s1_6, 1) >= 0) {
                    temp_s5 = 5 - func_0024E780(temp_s1_6, 4U);
                    temp_s3_2 = func_00250940(temp_s1_6, 0) + func_00250940((temp_s1_6 == 0) ? 1 : 0, 0);
                    var_s6 = 0;
                    var_s4 = 0;
                    do {
                        if (func_0024E300(temp_s1_6, var_s6, 1) >= 0) {
                            var_s4 += 1;
                        }
                        var_s6 += 1;
                    } while (var_s6 < 8);
                    if (temp_s5 <= 0 || temp_s3_2 == 0 || var_s4 == 0) {
                        return 0;
                    }
                    out[0] = 0x3A;
                    if (func_002670F0(0x2C, (s32) *(u16 *)&temp_v0->value) >= 0) {
                        var_v0_4 = func_002670F0(0x2C, (s32) *(u16 *)&temp_v0->value);
                    } else {
                        var_v0_4 = -func_002670F0(0x2C, (s32) *(u16 *)&temp_v0->value);
                    }
                    out[1] = var_v0_4;
                    out[2] = temp_s1_6;
                    temp_s5 = ((temp_s5 < temp_s3_2 ? temp_s5 : temp_s3_2) < var_s4)
                        ? (temp_s5 < temp_s3_2 ? temp_s5 : temp_s3_2) : var_s4;
                    out[3] = temp_s5;
                    return 3;
                }
                return 0;
            }
            out[0] = 0x66;
            out[1] = 1;
            out[2] = temp_v0_8;
            out[3] = 0;
            return 1;
        }
        temp_s1_7 = func_0024DE70(arg0, arg1);
        temp_s3_4 = func_001DF470(arg0);
        if (func_002670F0(0x2C, (s32) *(u16 *)&temp_v0->value) < temp_s3_4 && func_0024E220(temp_s1_7, 1) >= 0) {
            temp_s3_5 = 5 - func_0024E780(temp_s1_7, 4U);
            temp_s4 = func_00250940(temp_s1_7, 0) + func_00250940((temp_s1_7 == 0) ? 1 : 0, 0);
            var_s6_2 = 0;
            var_s5_2 = 0;
            do {
                if (func_0024E300(temp_s1_7, var_s6_2, 1) >= 0) {
                    var_s5_2 += 1;
                }
                var_s6_2 += 1;
            } while (var_s6_2 < 8);
            if (temp_s3_5 <= 0 || temp_s4 == 0 || var_s5_2 == 0) {
                return 0;
            }
            out[0] = 0x3A;
            out[1] = func_002670F0(0x2C, (s32) *(u16 *)&temp_v0->value);
            out[2] = temp_s1_7;
            temp_s3_5 = ((temp_s3_5 < temp_s4 ? temp_s3_5 : temp_s4) < var_s5_2)
                ? (temp_s3_5 < temp_s4 ? temp_s3_5 : temp_s4) : var_s5_2;
            out[3] = temp_s3_5;
            return 1;
        }
        return 0;
    case 0x26:                                      /* switch 1 */
        out[0] = 0x21;
        out[1] = 0;
        out[2] = func_0024DE70(arg0, arg1);
        out[3] = 0;
        return 1;
    case 0x41:                                      /* switch 1 */
        if ((u32) func_001DF470(arg0) > (temp_v0->value >> 0x10)) {
            temp_v0_9 = func_0024DE70(arg0, arg1);
            temp_v0_10 = func_0024C7D0(func_0024CA40(0, 0, temp_v0_9, ((u32) temp_v0->flags >> 6) & 3, temp_v0->flags & 0x3F, 0xE), arg0, arg1);
            if (temp_v0_10 == 0) {
                return 0;
            }
            out[0] = 0x3B;
            out[1] = temp_v0_9;
            out[2] = temp_v0_10;
            out[3] = (s32) temp_v0->value;
            return 1;
        }
        return 0;
    case 0x38:                                      /* switch 1 */
        temp_s1_8 = func_0024DE70(arg0, arg1);
        temp_v1_2 = temp_v0->value >> 0x10;
        switch (temp_v1_2) {                        /* switch 3; irregular */
        case 31:                                    /* switch 3 */
            temp_v0_11 = func_0024E220(temp_s1_8, 1);
            if (temp_v0_11 >= 0) {
                out[0] = 1;
                out[1] = temp_s1_8;
                out[2] = temp_v0_11;
                out[3] = (s32) temp_v0->value;
                return 1;
            }
            return 0;
        case 30:                                    /* switch 3 */
            temp_v0_12 = func_0024E220((temp_s1_8 == 0) ? 1 : 0, 1);
            if (temp_v0_12 >= 0) {
                out[0] = 1;
                out[1] = temp_s1_8;
                out[2] = temp_v0_12;
                out[3] = (s32) temp_v0->value;
                return 1;
            }
            return 0;
        default:                                    /* switch 3 */
            return 0;
        }
        break;
    case 0x51:                                      /* switch 1 */
        temp_s1_9 = func_0024DE70(arg0, arg1);
        temp_v1_3 = (temp_v0->value >> 0x10) & 0xFF;
        switch (temp_v1_3) {                        /* switch 4; irregular */
        case 31:                                    /* switch 4 */
            temp_v0_13 = func_0024E220(temp_s1_9, 1);
            if (temp_v0_13 >= 0) {
                out[0] = 1;
                out[1] = (s32) (temp_s1_9 | 0x10000);
                out[2] = temp_v0_13;
                out[3] = (s32) temp_v0->value;
                temp_v0->flags = -1U;
                temp_v0->value = -1U;
                return 1;
            }
            return 0;
        case 30:                                    /* switch 4 */
            temp_v0_14 = func_0024E220((temp_s1_9 == 0) ? 1 : 0, 1);
            if (temp_v0_14 >= 0) {
                out[0] = 1;
                out[1] = (s32) (temp_s1_9 | 0x10000);
                out[2] = temp_v0_14;
                out[3] = (s32) temp_v0->value;
                temp_v0->flags = -1U;
                temp_v0->value = -1U;
                return 1;
            }
            return 0;
        default:                                    /* switch 4 */
            return 0;
        }
        break;
    case 0x1A:                                      /* switch 1 */
        out[0] = 0x41;
        out[1] = 0;
        var_v0_5 = func_0024DE70(arg0, arg1);
        if (var_v0_5 == 0) {
            var_v0_5 = 1;
        } else {
            var_v0_5 = 0;
        }
        out[2] = var_v0_5;
        out[3] = (s32) *(u16 *)&temp_v0->value;
        return 1;
    case 0x4:                                       /* switch 1 */
        temp_v1_4 = temp_s1_2 & 0x3F;
        switch (temp_v1_4) {                        /* switch 5; irregular */
        case 26:                                    /* switch 5 */
            if (arg2 >= 0 && arg3 > 0 && temp_s7 == 0) {
                temp_v0_15 = func_0024C780(0U, arg2, arg3);
                out[0] = 0x15;
                out[1] = 0;
                out[2] = temp_v0_15;
                out[3] = 0;
                return 0x201;
            }
            return 0;
        case 30:                                    /* switch 5 */
            temp_s0 = func_0024CA40(temp_fp, spAC, func_0024DE70(arg0, arg1), (temp_s1_2 >> 6) & 3, 30, temp_v0->value >> 16);
            out[0] = 0x15;
            out[1] = 0;
            out[2] = temp_s0;
            out[3] = 0;
            if (func_001E1030(arg0, arg1) == 0x269) {
                out[0] = 0x17;
            }
            out[1] = 0;
            out[2] = temp_s0;
            out[3] = 0;
            return (temp_s0 != 0) ? 1 : 0;
        case 31:                                    /* switch 5 */
            var_v0_6 = func_0024C7D0(func_0024CA40(temp_fp, spAC, func_0024DE70(arg0, arg1), (temp_s1_2 >> 6) & 3, 31, temp_v0->value >> 16), arg0, arg1);
            if (temp_s7 != 0) {
                var_v0_6 = func_0024C7D0((u32) var_v0_6, arg2, arg3);
            }
            out[0] = 0x15;
            out[1] = 0;
            out[2] = var_v0_6;
            out[3] = 0;
            if (func_001E1030(arg0, arg1) == 0x1FD || func_001E1030(arg0, arg1) == 0x1FA) {
                out[0] = 0x2E;
            }
            var_v0_7 = arg0 << 8;
            out[1] = (s32) (var_v0_7 | arg1);
            out[2] = 0;
            out[3] = 1;
            return 0x201;
        default:                                    /* switch 5 */
            return 0;
        }
        break;
    default:                                        /* switch 1 */
        return 0;
    }
}

typedef struct Result_00252440 {
    s32 kind;
    s32 value;
    s32 pos;
    s32 extra;
    u8 flag0;
    u8 flag1;
} Result_00252440;

s32 func_00252440(s32 x, s32 y, void *arg2, s32 phase) {
    extern s32 func_001E1E10();
    extern s32 func_00263930();
    extern s32 func_00252EC0();
    extern s32 func_0024F370();
    s32 type;
    u32 *info;
    s32 pos;
    s32 card;
    s32 other;
    u8 *tail;
    Result_00252440 *res;
    s32 found;
    s32 target;

    res = arg2;
    tail = &res->flag0;
    type = func_001E0700(x, y) >> 5;
    res->kind = 0;
    res->value = 0;
    res->pos = 0;
    res->extra = 0;
    res->flag0 = 0;
    res->flag1 = 0;
    info = func_00250740(x, y, 0);
    switch (phase) {
    case 0:
        if (type == 0) {
            if ((card = (s32)func_00250740(x, y, 3)) != 0 && func_001E2100(x, y, 4) == 0 && func_001E2100(x, y, 2) != 0) {
                pos = func_001E1090(x, y);
                func_002516D0(x, y, 1);
                return func_00263930(card, x, y, -1, -1, pos & 0xFF, pos >> 8, res, tail, 0) | 0x100;
            }
            return 0x100;
        }
        if (type != 1 && type != 5) {
            return 0x100;
        }
        if ((type == 1 || type == 5) && func_001E2100(x, y, 2) == 0) {
            return 0x100;
        }
        return (phase + 1) << 16;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
        found = func_00266C70(0xE, 0);
        if (found >= 0) {
        switch (phase) {
        case 1:
            res->kind = 0x65;
            res->value = 0;
            res->pos = (x << 8) | y;
            res->extra = 0;
            return 0x20001;
        case 2:
            res->kind = 0x66;
            res->value = 0;
            res->pos = found;
            res->extra = 0;
            return 0x30001;
        case 3:
            func_0024F370(x, y);
            return 0;
        }
        return 0;
        }
        found = func_00266C70(0x4C, 0);
        if (found >= 0 && (*info >> 8) == 0x14) {
        switch (phase) {
        case 1:
            res->kind = 0x65;
            res->value = 0;
            res->pos = (x << 8) | y;
            res->extra = 0;
            return 0x20001;
        case 2:
            res->kind = 0x66;
            res->value = 0;
            res->pos = found;
            res->extra = 0;
            return 0x30001;
        case 3:
            func_0024F370(x, y);
            return 0;
        }
        return 0;
        }
        found = func_00266C70(0x11, 0);
        if (found >= 0 && (*info >> 8) == 0x32) {
        switch (phase) {
        case 1:
            res->kind = 0x65;
            res->value = 0;
            res->pos = (x << 8) | y;
            res->extra = 0;
            return 0x20001;
        case 2:
            res->kind = 0x66;
            res->value = 0;
            res->pos = found;
            res->extra = 0;
            return 0x30001;
        case 3:
            func_0024F370(x, y);
            return 0;
        }
        return 0;
        }
        if ((target = func_0026AB80(func_0024DE70(x, y), 0xE)) >= 0) {
            if ((other = func_0026AB80(0, 0x2E)) < 0) {
                switch (phase) {
                case 1:
                    return (phase + 1) << 16;
                case 2:
                    res->kind = 0x65;
                    res->value = 0;
                    res->pos = (x << 8) | y;
                    res->extra = 0;
                    return 0x30001;
                case 3:
                    func_002516D0(target >> 8, target & 0xFF, 1);
                    return 0x40000;
                case 4:
                    if (func_001E1E10(target >> 8, target & 0xFF) == 0xFF) {
                        res->kind = 0x33;
                        res->value = target;
                        res->pos = (x << 8) | y;
                        res->extra = 1;
                        return 1;
                    }
                    return 0x40000;
                }
                return 0;
            }
            switch (phase) {
            case 1:
                return (phase + 1) << 16;
            case 2:
                res->kind = 0x65;
                res->value = 0;
                res->pos = (x << 8) | y;
                res->extra = 0;
                return 0x30001;
            case 3:
                func_002516D0(other >> 8, other & 0xFF, 1);
                return 0x40000;
            case 4:
                if (func_001E1E10(other >> 8, other & 0xFF) == 0xFF) {
                    res->kind = 0x66;
                    res->value = 1;
                    res->pos = other;
                    res->extra = 0;
                    return 0x50001;
                }
                return 0x40000;
            case 5:
                res->kind = 0x65;
                res->value = 0;
                res->pos = (x << 8) | y;
                res->extra = 2;
                return 0x70001;
            }
            return 0;
        }
        if ((target = func_0026AB80(func_0024DE70(x, y), 0x4C)) >= 0 && (*info >> 8) == 0x14) {
            if ((other = func_0026AB80(0, 0x2E)) < 0) {
                switch (phase) {
                case 1:
                    return (phase + 1) << 16;
                case 2:
                    res->kind = 0x65;
                    res->value = 0;
                    res->pos = (x << 8) | y;
                    res->extra = 0;
                    return 0x30001;
                case 3:
                    func_002516D0(target >> 8, target & 0xFF, 1);
                    return 0x40000;
                default:
                    if (func_001E1E10(target >> 8, target & 0xFF) == 0xFF) {
                        res->kind = 0x33;
                        res->value = target;
                        res->pos = (x << 8) | y;
                        res->extra = 0;
                        return 1;
                    }
                    return 0x40000;
                }
            }
            switch (phase) {
            case 1:
                return (phase + 1) << 16;
            case 2:
                res->kind = 0x65;
                res->value = 0;
                res->pos = (x << 8) | y;
                res->extra = 0;
                return 0x30001;
            case 3:
                func_002516D0(target >> 8, target & 0xFF, 1);
                return 0x40000;
            case 4:
                if (func_001E1E10(other >> 8, other & 0xFF) == 0xFF) {
                    res->kind = 0x66;
                    res->value = 1;
                    res->pos = other;
                    res->extra = 0;
                    return 0x50001;
                }
                return 0x40000;
            case 5:
                res->kind = 0x65;
                res->value = 0;
                res->pos = (x << 8) | y;
                res->extra = 2;
                return 0x70001;
            }
            return 0;
        }
        if ((target = func_0026AB80(func_0024DE70(x, y), 0x11)) >= 0 && (*info >> 8) == 0x32) {
            if ((other = func_0026AB80(0, 0x2E)) < 0) {
                switch (phase) {
                case 1:
                    return (phase + 1) << 16;
                case 2:
                    res->kind = 0x65;
                    res->value = 0;
                    res->pos = (x << 8) | y;
                    res->extra = 0;
                    return 0x30001;
                case 3:
                    func_002516D0(target >> 8, target & 0xFF, 1);
                    return 0x40000;
                default:
                    if (func_001E1E10(target >> 8, target & 0xFF) == 0xFF) {
                        res->kind = 0x33;
                        res->value = target;
                        res->pos = (x << 8) | y;
                        res->extra = 0;
                        return 1;
                    }
                    return 0x40000;
                }
            }
            switch (phase) {
            case 1:
                return (phase + 1) << 16;
            case 2:
                res->kind = 0x65;
                res->value = 0;
                res->pos = (x << 8) | y;
                res->extra = 0;
                return 0x30001;
            case 3:
                func_002516D0(other >> 8, other & 0xFF, 1);
                return 0x40000;
            case 4:
                if (func_001E1E10(other >> 8, other & 0xFF) == 0xFF) {
                    res->kind = 0x66;
                    res->value = 1;
                    res->pos = other;
                    res->extra = 0;
                    return 0x50001;
                }
                return 0x40000;
            case 5:
                res->kind = 0x65;
                res->value = 0;
                res->pos = (x << 8) | y;
                res->extra = 2;
                return 0x70001;
            }
            return 0;
        }
        res->kind = 0x65;
        res->value = 0;
        res->pos = (x << 8) | y;
        res->extra = 1;
        return 0x70001;
    }
    return func_00252EC0(x, y, res, tail, phase, info);
}

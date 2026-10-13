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

INCLUDE_ASM("asm/nonmatchings/main_073", func_002517D0);

INCLUDE_ASM("asm/nonmatchings/main_073", func_00252440);

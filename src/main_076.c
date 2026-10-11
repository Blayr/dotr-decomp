#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_076", func_00265890);

INCLUDE_ASM("asm/nonmatchings/main_076", func_002660E0);

INCLUDE_ASM("asm/nonmatchings/main_076", func_00266500);

INCLUDE_ASM("asm/nonmatchings/main_076", func_00266910);

INCLUDE_ASM("asm/nonmatchings/main_076", func_00266A80);

s32 func_00266C70(s32 arg0, s32 arg1) {
    s32 count;
    s32 index;
    u32 *data;

    index = 1;
    count = 0;
    do {
        if (func_001E2100(0, index, 4) != 0 &&
            func_001E2100(0, index, 3) != 0 &&
            func_001E2100(0, index, 5) != 0) {
            data = func_00250740(0, index, 2);
            if (data != NULL && (*data >> 8) == arg0) {
                if (count++ == arg1) {
                    return index;
                }
            }
        }
        index++;
    } while (index < 11);

    index = 1;
    do {
        if (func_001E2100(1, index, 4) != 0 &&
            func_001E2100(1, index, 3) != 0 &&
            func_001E2100(1, index, 5) != 0) {
            data = func_00250740(1, index, 2);
            if (data != NULL && (*data >> 8) == arg0) {
                if (count++ == arg1) {
                    return index | 0x100;
                }
            }
        }
        index++;
    } while (index < 11);
    return -1;
}

s32 func_00266DF0(s32 arg0) {
    s32 var_s2;
    s32 var_s0;
    u32 *temp_v0;
    u32 *temp_v0_2;

    var_s2 = 1;
    var_s0 = 0;
    do {
        if ((func_001DF540(0, var_s2) != 0) && ((temp_v0 = func_00250740(0, var_s2, 2)) != NULL) && (func_001E2100(0, var_s2, 4) != 0) && (func_001E2100(0, var_s2, 3) != 0) && (func_001E2100(0, var_s2, 5) != 0) && (((u32) *temp_v0 >> 8) == arg0)) {
            var_s0 += 1;
        }
        var_s2 += 1;
    } while (var_s2 < 0xB);
    var_s2 = 1;
    do {
        if ((func_001DF540(1, var_s2) != 0) && ((temp_v0_2 = func_00250740(1, var_s2, 2)) != NULL) && (func_001E2100(1, var_s2, 4) != 0) && (func_001E2100(1, var_s2, 3) != 0) && (func_001E2100(1, var_s2, 5) != 0) && (((u32) *temp_v0_2 >> 8) == arg0)) {
            var_s0 += 1;
        }
        var_s2 += 1;
    } while (var_s2 < 0xB);
    return var_s0;
}

s32 func_00266F70(s32 arg0, s32 arg1) {
    s32 var_s0;
    s32 var_s3;
    u32 *temp_v0;
    u32 *temp_v0_2;

    var_s3 = 1;
    var_s0 = 0;
    do {
        if ((func_001E2100(0, var_s3, 4) != 0) && (func_001E2100(0, var_s3, 3) != 0) && (func_001E2100(0, var_s3, 5) != 0) && (arg1 == func_0024DE70(0, var_s3))) {
            temp_v0 = func_00250740(0, var_s3, 2);
            if ((temp_v0 != NULL) && (((u32) *temp_v0 >> 8) == arg0)) {
                var_s0 += 1;
            }
        }
        var_s3 += 1;
    } while (var_s3 < 0xB);
    var_s3 = 1;
    do {
        if ((func_001E2100(1, var_s3, 4) != 0) && (func_001E2100(1, var_s3, 3) != 0) && (func_001E2100(1, var_s3, 5) != 0) && (arg1 == func_0024DE70(1, var_s3))) {
            temp_v0_2 = func_00250740(1, var_s3, 2);
            if ((temp_v0_2 != NULL) && (((u32) *temp_v0_2 >> 8) == arg0)) {
                var_s0 += 1;
            }
        }
        var_s3 += 1;
    } while (var_s3 < 0xB);
    return var_s0;
}

INCLUDE_ASM("asm/nonmatchings/main_076", func_002670F0);

INCLUDE_ASM("asm/nonmatchings/main_076", func_00267380);

INCLUDE_ASM("asm/nonmatchings/main_076", func_00267560);

s32 func_00267700(s32 arg0, s32 arg1) {
    s32 index;
    s32 count;
    s32 column;
    s32 row;
    s32 value;
    s32 *data;

    if (arg1 == 0) {
        return 0;
    }
    if ((count = func_00266DF0(0xB)) > 0) {
            for (index = 0; index < count; index++) {
            value = func_00266C70(0xB, index);
            row = value >> 8;
            column = value & 0xFF;
            if ((func_001E2100(row, column, 4) != 0) &&
                (func_001E2100(row, column, 3) != 0) &&
                (func_001E2100(row, column, 5) != 0)) {
                data = func_00250740(row, column, 2);
                if (data != NULL) {
                    switch (*data & 0x3F) {
                    case 0:
                        if (!(func_001E0700(arg0, arg1) & 0x1F)) {
                            if ((func_001E0700(arg0, arg1) >> 5) == 0) {
                                return 1;
                            }
                        }
                        return 0;
                    }
                }
            }
            }
    }
    return 0;
}

s32 func_00267860(s32 arg0, s32 arg1) {
    s32 i;
    s32 count;
    s32 entry;
    s32 low;
    s32 high;
    s32 *info;

    if (arg1 == 0) {
        return 0;
    }
    if ((count = func_00266DF0(0xB)) > 0) {
        for (i = 0; i < count; i++) {
            entry = func_00266C70(0xB, i);
            high = entry >> 8;
            low = entry & 0xFF;
            if ((func_001E2100(high, low, 4) != 0) &&
                (func_001E2100(high, low, 3) != 0) &&
                (func_001E2100(high, low, 5) != 0)) {
                info = func_00250740(high, low, 2);
                if (info != NULL) {
                    switch (*info & 0x3F) {
                    case 0:
                        if (!(func_001E0700(arg0, arg1) & 0x1F) &&
                            ((func_001E0700(arg0, arg1) >> 5) == 0)) {
                            return entry;
                        }
                        break;
                    }
                }
            }
        }
    }
    return 0;
}

s32 func_002679C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 state;
    s32 first;

    state = func_001DE540();
    if ((state == func_0024DE70(arg2, arg3)) ||
        ((func_001E0700(arg0, arg1) >> 5) != 0) ||
        ((func_001E0700(arg2, arg3) >> 5) != 0) ||
        (arg1 == 0) || (arg3 == 0)) {
        return -1;
    }
    if (func_00267560(func_001DF540(arg2, arg3)) != 0) {
        return -1;
    }
    if (func_001E2100(arg2, arg3, 4) != 0) {
        first = func_001E0830(arg0, arg1);
        return func_0024EA70(first, func_001E0830(arg2, arg3)) + 1;
    }
    if (func_00266DF0(0x3D) > 0) {
        first = func_001E0830(arg0, arg1);
        return func_0024EA70(first, func_001E0830(arg2, arg3)) + 1;
    }
    return -1;
}

s32 func_00267B30(s32 arg0) {
    s32 var_s0;
    s32 temp_v0;
    s32 var_s2;
    s32 temp_s3;
    s32 temp_s4;
    s32 temp_v0_2;
    s32 temp_v1;
    u32 *temp_v0_3;
    u32 temp_a0;

    temp_v0 = func_00266DF0(0x56);
    var_s2 = 0;
    for (var_s0 = 0; var_s0 < temp_v0; var_s0++) {
            temp_v0_2 = func_00266C70(0x56, var_s0);
            temp_s4 = temp_v0_2 >> 8;
            temp_s3 = temp_v0_2 & 0xFF;
            temp_v0_3 = func_00250740(temp_s4, temp_s3, 2);
            if (temp_v0_3 != NULL) {
                temp_a0 = *temp_v0_3;
                if ((temp_a0 >> 8) == 0x56) {
                    temp_v1 = (temp_a0 >> 6) & 3;
                    if (temp_v1 == 2) {
                        if (arg0 != func_0024DE70(temp_s4, temp_s3)) {
                            var_s2 -= 1;
                        }
                    } else if (temp_v1 == 3) {
                        var_s2 += 1;
                    }
                }
            }
    }
    if (var_s2 > 0) {
        var_s2 = 1;
    } else if (var_s2 < 0) {
        var_s2 = -1;
    }
    return var_s2;
}

INCLUDE_ASM("asm/nonmatchings/main_076", func_00267C50);

INCLUDE_ASM("asm/nonmatchings/main_076", func_00268460);

INCLUDE_ASM("asm/nonmatchings/main_076", func_00268600);

s32 func_002686F0(s32 arg0) {
    s32 result;

    switch (arg0) {
    case 0:
        result = 0x38;
        break;
    case 1:
        result = 0x39;
        break;
    case 2:
        result = 0x36;
        break;
    case 3:
        result = 0x37;
        break;
    default:
        result = 0;
        break;
    }

    return result;
}

INCLUDE_ASM("asm/nonmatchings/main_076", func_00268760);

INCLUDE_ASM("asm/nonmatchings/main_076", func_00268AD0);

typedef struct {
    u8 pad00[4];
    s32 f4;
    u32 f8;
    u32 fC;
} Src_00268FA0;

typedef struct {
    u8 pad00[4];
    u16 state;
    u8 ids[0x1A];
    s32 f20;
    u8 pad24[0xD4 - 0x24];
    u8 nids;
    u8 padD5[0x102 - 0xD5];
    u16 timer;
} Work_00268FA0;

typedef struct {
    s32 w0;
    s32 w4;
    s32 w8;
    s32 wC;
} Req_00268FA0;

void func_001DF490(s32, s32, s32);
void func_001E42C0(s32, s32, s32, s32);
s32 func_001F51D0(s32);
void func_00250CA0(s32, s32, s32, u32);
void func_00250E80(s32, s32, s32, u32);
void func_00255960(void *);
u8 func_00255A30(void *, void *);
void func_00255AC0(void *, s32);
void func_00260740(s32);
void func_00260A70(void *, s32);
s32 func_002670F0(s32, s32);

s32 func_00268FA0(void *arg0, void *arg1, s32 arg2) {
    Src_00268FA0 *src = (Src_00268FA0 *)arg0;
    Work_00268FA0 *w = (Work_00268FA0 *)arg1;
    Req_00268FA0 req;
    s32 count;
    Req_00268FA0 *p;
    s32 i;
    s32 j;

    req.w0 = 0x3E7;
    req.w4 = 0;
    req.w8 = 0;
    req.wC = 0;
    p = &req;
    count = 0;
    func_001DE7E0(0);
    if (arg2 >= 0) {
        func_00255960(arg1);
        func_00260740(0x10);
        func_00255AC0(arg1, 0x1FC);
        func_00255AC0(arg1, 0x211);
        func_00260740(0x10);
        return 1;
    }
    switch (w->state) {
    case 0:
        if (func_00255B50(arg1) == 1) {
            p->w0 = 0x1FC;
            p->w4 = 0;
            p->w8 = 1;
            p->wC = func_002670F0(0x2C, (u16)src->fC);
            w->ids[0] = func_00255A30(p, arg1);
            w->f20 = 0xFFFF;
            w->nids++;
            w->state++;
        }
        break;
    case 1:
        if (func_001F51D0(w->ids[0]) == 1) {
            return 1;
        }
        func_001DF490(src->f4, 1, func_002670F0(0x2C, (u16)src->fC));
        w->state++;
        break;
    case 2:
        func_001E42C0(0, -0x78, 0x50, 0x106);
        func_0025F720(arg0, arg1, p, 0x211);
        w->state++;
        break;
    case 3:
        for (i = 0; i < w->nids; i++) {
            if (func_001F51D0(w->ids[i]) == 0) {
                count++;
            }
        }
        if (count < w->nids) {
            return 1;
        }
        func_001E4530();
        for (j = 0; j < 0x16; j++) {
            if ((src->f8 >> (0x15 - j)) & 1) {
                if (j < 0xB) {
                    func_00250E80(0, j, 0, src->fC >> 16);
                    func_00250CA0(0, j, 0, src->fC >> 16);
                } else {
                    func_00250E80(1, j - 0xB, 0, src->fC >> 16);
                    func_00250CA0(1, j - 0xB, 0, src->fC >> 16);
                }
            }
        }
        func_00260A70(arg1, 0x10);
        w->state++;
        break;
    default:
        if (w->timer++ > 0x10) {
            if (func_001DE780() != 0) {
                func_001DE7E0(1);
            }
            func_001E4530();
            return 0;
        }
        break;
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_076", func_002692D0);

INCLUDE_ASM("asm/nonmatchings/main_076", func_002695D0);

INCLUDE_ASM("asm/nonmatchings/main_076", func_00269D60);

void func_00269E10(void *arg0) {
    u32 temp_v1;

    temp_v1 = *(u32 *)((u8 *)arg0 + 0xC) >> 0xE;
    switch (temp_v1) {
    case 0x218:
        func_00217710(1, 0x3B);
        return;
    case 0x21C:
        func_00217710(1, 0x4B);
        return;
    case 0x21D:
        func_00217710(1, 0x4E);
        return;
    case 0x21E:
        func_00217710(1, 0x4F);
        return;
    default:
        func_00217710(1, 0x4A);
        return;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_076", func_00269EC0);

INCLUDE_ASM("asm/nonmatchings/main_076", func_0026A0A0);

s32 func_0026AB80(s32 arg0, s32 arg1) {
    switch (arg1) {
    case 0x29:
    case 0x2A:
    case 0x2C:
    case 0x23:
    case 0x4A:
    case 0x4B:
    case 0xE:
    case 0x4:
    case 0x30:
    case 0x31:
        return func_0026AC90(arg0, 2, arg1);
    case 0x50:
    case 0x4C:
    case 0x2D:
    case 0x11:
    case 0x2E:
    case 0x2B:
        return func_0026AC90(arg0, 3, arg1);
    default:
        return -1;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_076", func_0026AC90);

INCLUDE_ASM("asm/nonmatchings/main_076", func_0026AE70);

INCLUDE_ASM("asm/nonmatchings/main_076", func_0026B1F0);

s32 func_0026B430(void *arg0) {
    ((s32 *)arg0)[0] = 0x66;
    ((s32 *)arg0)[1] = 1;
    ((s32 *)arg0)[2] = func_0026AB80(0, 0x2E);
    ((s32 *)arg0)[3] = 0;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_076", func_0026B480);

INCLUDE_ASM("asm/nonmatchings/main_076", func_0026BB80);

INCLUDE_ASM("asm/nonmatchings/main_076", func_0026BE20);

INCLUDE_ASM("asm/nonmatchings/main_076", func_0026BF50);

INCLUDE_ASM("asm/nonmatchings/main_076", func_0026C170);

void func_0026CD80(s32 arg0) {
    f32 v[4];
    f32 *p;

    if (arg0 < 0) {
        func_001F1E10(1, v);
        if (v[0] - 0.08f < 0.0f) {
            v[0] = 0.0f;
        } else {
            v[0] -= 0.08f;
        }
        p = &v[1];
        if (*p - 0.08f < 0.0f) {
            *p = 0.0f;
        } else {
            *p -= 0.08f;
        }
        func_001F1EE0(1, v);
        func_001F1E10(5, v);
        if (v[0] - 0.08f < 0.0f) {
            v[0] = 0.0f;
        } else {
            v[0] -= 0.08f;
        }
        if (*p - 0.08f < 0.0f) {
            *p = 0.0f;
        } else {
            *p -= 0.08f;
        }
        func_001F1EE0(5, v);
        func_001F1E10(6, v);
        if (v[0] - 0.08f < 0.0f) {
            v[0] = 0.0f;
        } else {
            v[0] -= 0.08f;
        }
        if (*p - 0.08f < 0.0f) {
            *p = 0.0f;
        } else {
            *p -= 0.08f;
        }
        func_001F1EE0(6, v);
    } else {
        func_001F1E10(1, v);
        v[0] = 0.8f;
        p = &v[1];
        *p = 0.8f;
        func_001F1EE0(1, v);
        func_001F1E10(5, v);
        v[0] = 0.8f;
        *p = 0.8f;
        func_001F1EE0(5, v);
        func_001F1E10(6, v);
        v[0] = 0.8f;
        *p = 0.8f;
        func_001F1EE0(6, v);
    }
}

INCLUDE_ASM("asm/nonmatchings/main_076", func_0026CFC0);

INCLUDE_ASM("asm/nonmatchings/main_076", func_0026D3C0);

s32 func_0026D600(s32 arg0, s32 arg1, s32 arg2, s32 *arg3) {
    s32 i;
    s32 *p;
    s32 result;
    s32 retry;
    s32 j;

    result = func_0026D6E0(arg0, arg1, arg2, 0);
    if (result >= 0) {
        i = 0;
        p = arg3;
        do {
            if (result == *p) {
                retry = func_0026D6E0(arg0, arg1, arg2, 1);
                if (retry >= 0) {
                    j = 0;
                    do {
                        if (retry == *arg3) {
                            return -1;
                        }
                        j++;
                        arg3++;
                    } while (j < 22);
                    return retry;
                }
                return -1;
            }
            i++;
            p++;
        } while (i < 22);
        return result;
    }
    return -1;
}

s32 func_0026D6E0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_s0;
    s32 temp_s1;
    s32 temp_s1_2;
    s32 temp_s2;
    s32 temp_s2_2;
    s32 temp_v0;
    s32 var_v0;
    s32 var_v0_2;

    temp_v0 = func_001E1090(arg2 >> 8, arg2 & 0xFF);
    temp_s0 = temp_v0 & 0xFF;
    if (arg0 < temp_s0) {
        temp_s1 = temp_s0 - 1;
        temp_s2_2 = temp_v0 >> 8;
        if (func_001E3790(temp_s1, temp_s2_2) < 0) {
            if (arg3 == 0) {
                var_v0_2 = (temp_s2_2 << 8) | temp_s1;
            } else {
                var_v0_2 = func_0026D840(arg0, arg1, temp_s0, temp_s2_2);
            }
            return var_v0_2;
        }
        return func_0026D840(arg0, arg1, temp_s0, temp_s2_2);
    }
    if (temp_s0 < arg0) {
        temp_s1_2 = temp_s0 + 1;
        temp_s2 = temp_v0 >> 8;
        if (func_001E3790(temp_s1_2, temp_s2) < 0) {
            if (arg3 == 0) {
                var_v0 = (temp_s2 << 8) | temp_s1_2;
            } else {
                var_v0 = func_0026D840(arg0, arg1, temp_s0, temp_s2);
            }
            return var_v0;
        }
        return func_0026D840(arg0, arg1, temp_s0, temp_s2);
    }
    return func_0026D840(arg0, arg1, temp_s0, temp_v0 >> 8);
}

s32 func_0026D840(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg3 < arg1) {
        if (func_001E3790(arg2, arg3 + 1) < 0) {
            return ((arg3 + 1) << 8) | arg2;
        } else {
            return -1;
        }
    } else if (arg1 < arg3) {
        if (func_001E3790(arg2, arg3 - 1) < 0) {
            return ((arg3 - 1) << 8) | arg2;
        } else {
            return -1;
        }
    } else {
        return -1;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_076", func_0026D8F0);

INCLUDE_ASM("asm/nonmatchings/main_076", func_0026DCC0);

INCLUDE_ASM("asm/nonmatchings/main_076", func_0026E1F0);

INCLUDE_ASM("asm/nonmatchings/main_076", func_0026E610);

s32 func_0026E950(void) {
    s32 var_s0;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_s3;
    s32 temp_v0_3;
    s32 temp_v0_4;

    temp_v0 = func_001DE540();
    temp_v0_2 = func_001DF110(temp_v0);
    var_s3 = 0;
    for (var_s0 = 0; var_s0 < temp_v0_2; var_s0++) {
            temp_v0_3 = func_001DF0C0(temp_v0, var_s0);
            if (((s32) (temp_v0_3 & 0xF000) >> 0xC) > 0) {
                temp_v0_4 = func_0026FA70(temp_v0_3, temp_v0);
                if (var_s3 < temp_v0_4) {
                    var_s3 = temp_v0_4;
                }
            }
    }
    return var_s3;
}

s32 func_0026EA00(s32 *arg0) {
    s32 temp_v1;

    temp_v1 = *arg0;
    switch (temp_v1) {
    case 0:
        return func_00270030();
    case 1:
        return func_00270260();
    case 2:
        return func_0026FE70();
    default:
        return 0;
    }
}

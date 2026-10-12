#include "common.h"

void func_0021BAE0(void *arg0) {
    f32 *values = arg0;

    values[3] = 1.0f;
    values[2] = 1.0f;
    values[1] = 1.0f;
    values[0] = 1.0f;
    values[7] = 0.0f;
    values[6] = 0.0f;
    values[5] = 0.0f;
    values[4] = 0.0f;
    values[11] = 0.0f;
    values[10] = 0.0f;
    values[9] = 0.0f;
    values[8] = 0.0f;
}

void func_0020C940(void *, void *, void *, void *);
void func_0020EB40(void *);

typedef struct {
    f32 m[4][4];
} Matrix_0021BB20;

void func_0021BB20(u8 *arg0) {
    Matrix_0021BB20 matrix;

    func_0020EB40(arg0 + 0x30);
    func_0020C940(&matrix, arg0, arg0 + 0x10, arg0 + 0x20);
    func_0020BC00((s32)(arg0 + 0x30), &matrix);
}

void func_0021BB70(void *arg0, void *arg1) {
    ((f32 *)arg0)[0] = ((f32 *)arg1)[0];
    ((f32 *)arg0)[1] = ((f32 *)arg1)[1];
    ((f32 *)arg0)[2] = ((f32 *)arg1)[2];
}

void func_0021BB90(s32 *arg0, s32 *arg1, s32 arg2) {
    u16 projected[6];
    s32 depth;

    if (func_00205440(arg2, D_00299F90, projected, &depth) != 0) {
        *arg0 = ((s32) projected[0] >> 4) - 0x6C0;
        *arg1 = ((s32) projected[1] >> 4) - 0x720;
    } else {
        *arg0 = -1;
        *arg1 = -1;
    }
}

void func_0021BC10(f32 *outX, f32 *outY, s16 *outCount, f32 *points,
                   f32 *intervals, s32 count, s16 mode, f32 spacing) {
    f32 lower[64];
    f32 diagonal[64];
    f32 upper[64];
    f32 slopes[2][64];
    f32 rhs[2][64];
    f32 cubic[2];
    f32 quadratic[2];
    f32 linear[2];
    f32 constant[2];
    s32 i;
    s32 dimension;
    s32 written;

    diagonal[0] = 2.0f * intervals[0];
    upper[0] = intervals[0];
    lower[count - 1] = intervals[count - 2];
    diagonal[count - 1] = 2.0f * intervals[count - 2];
    for (i = 1; i <= count - 2; i++) {
        lower[i] = intervals[i];
        diagonal[i] = 2.0f * (intervals[i - 1] + intervals[i]);
        upper[i] = intervals[i - 1];
    }

    {
        dimension = 0;
        while (1) {
            rhs[dimension][0] = 3.0f * (points[dimension + 2] - points[dimension]);
            rhs[dimension][count - 1] = 3.0f *
                ((points + dimension)[2 * count - 2] - (points + dimension)[2 * count - 4]);
            for (i = 1; i <= count - 2; i++) {
                rhs[dimension][i] = func_0021C320((points + dimension)[2 * i - 2],
                    (points + dimension)[2 * i], (points + dimension)[2 * i + 2],
                    intervals[i - 1], intervals[i]);
            }
            func_0021C350(lower, diagonal, upper, rhs[dimension], slopes[dimension], count);
            dimension++;
            if (dimension > 1) {
                break;
            }
        }
    }

    {
    dimension = 0;
    written = 0;
    for (; dimension < count - 1; dimension++) {
        i = 0;
        while (1) {
            cubic[i] = (slopes[i][dimension] + slopes[i][dimension + 1]) /
                (intervals[0] * intervals[0]) +
                (2.0f * (points[i] - points[i + 2])) /
                func_001A6C48(intervals[0], 3.0f);
            quadratic[i] = (3.0f * (points[i + 2] - points[i])) /
                (intervals[0] * intervals[0]) -
                (2.0f * slopes[i][dimension] + slopes[i][dimension + 1]) / intervals[0];
            linear[i] = slopes[i][dimension];
            constant[i] = points[i];
            i++;
            if (i > 1) {
                break;
            }
        }
        if (mode == 1) {
            if (dimension < count - 2) {
                f32 t;
                for (t = 0.0f; t <= intervals[0] - 0.1f; t += 0.1f) {
                    outX[written] = constant[0] + t *
                        (linear[0] + t * (quadratic[0] + cubic[0] * t));
                    outY[written] = constant[1] + t *
                        (linear[1] + t * (quadratic[1] + cubic[1] * t));
                    written++;
                }
            } else {
                f32 t;
                for (t = 0.0f; t <= intervals[0]; t += 0.1f) {
                    outX[written] = constant[0] + t *
                        (linear[0] + t * (quadratic[0] + cubic[0] * t));
                    outY[written] = constant[1] + t *
                        (linear[1] + t * (quadratic[1] + cubic[1] * t));
                    written++;
                }
            }
        } else {
            s16 samples;
            f32 dx;
            f32 dySquared;

            dx = points[2] - points[0];
            dySquared = func_001A6C48(points[3] - points[1], 2.0f);
            dx = func_001A6C48(dx, 2.0f);
            samples = func_001A22C0(func_001A6C60(dx + dySquared) / spacing);
            if (dimension < count - 2) {
                f32 t;
                for (i = 0; i < samples;) {
                    t = ((f32)i * intervals[0]) / (f32)samples;
                    i++;
                    outX[written] = constant[0] + t *
                        (linear[0] + t * (quadratic[0] + cubic[0] * t));
                    outY[written] = constant[1] + t *
                        (linear[1] + t * (quadratic[1] + cubic[1] * t));
                    written++;
                }
            } else {
                f32 t;
                for (i = 0; i <= samples;) {
                    t = ((f32)i * intervals[0]) / (f32)samples;
                    i++;
                    outX[written] = constant[0] + t *
                        (linear[0] + t * (quadratic[0] + cubic[0] * t));
                    outY[written] = constant[1] + t *
                        (linear[1] + t * (quadratic[1] + cubic[1] * t));
                    written++;
                }
            }
        }
        *outCount = written - 1;
        points += 2;
        intervals++;
    }
    }
}

f32 func_0021C320(f32 fparg0, f32 fparg1, f32 fparg2, f32 fparg3, f32 fparg4) {
    return 3.0f * (((fparg4 * (fparg1 - fparg0)) / fparg3) + ((fparg3 * (fparg2 - fparg1)) / fparg4));
}

void func_0021C350(f32 *a, f32 *b, f32 *c, f32 *r, f32 *u, s32 n) {
    f32 gamma[64];
    f32 denominator;
    s32 i;

    denominator = b[0];
    u[0] = r[0] / denominator;
    for (i = 1; i < n; i++) {
        gamma[i] = c[i - 1] / denominator;
        denominator = b[i] - a[i] * gamma[i];
        u[i] = (r[i] - a[i] * u[i - 1]) / denominator;
    }
    for (i = n - 2; i >= 0; i--) {
        u[i] -= gamma[i + 1] * u[i + 1];
    }
}

s32 func_0021C450(s32 arg0, s32 arg1, s32 arg2, s64 arg3, s64 arg4, s32 arg5, s32 arg6) {
    s32 result;
    s32 object;

    object = func_0020F290(func_001FD680(arg0, arg1, arg2, 0, arg1 * 22));
    func_001FEAB0(arg1);
    result = func_001FE660(object, arg1, (s16)arg3, (s16)arg4, 1.0f, 1.0f, arg6, func_001FDFE0);
    func_001FEAF0(arg1);
    return result;
}

INCLUDE_ASM("asm/nonmatchings/main_062", func_0021C510);

typedef struct Buffer_0021D480 {
    u32 data[0x3FE8];
} Buffer_0021D480;

typedef struct Entry_0021D480 {
    u16 value;
    u16 other[5];
} Entry_0021D480;

extern u16 D_00299CE0[];
extern Entry_0021D480 D_00299D00[];
extern s8 D_0034F6F8;
void *func_002145E0();

void func_0021D480(void) {
    u8 *base = (u8 *)0x01ED0000;
    u8 *record = (u8 *)&D_00299E10;
    f32 eye[4];
    f32 target[4];
    f32 up[4];
    s32 i;
    s32 inner;
    s32 k;
    s16 *cell;
    u8 *row;
    s16 *count;
    s16 *block;
    u8 *rows;
    u8 *counts;
    u8 *data;
    s32 outer;
    s16 n;
    s32 total;
    u16 j;
    s32 shift;
    u32 *words;
    u16 *halves;

    func_00195108((s32)base, 0x54B0);
    eye[0] = 0.0f;
    eye[1] = 8.65f;
    eye[2] = 100.0f;
    target[0] = 0.0f;
    target[1] = 8.65f;
    target[2] = 0.0f;
    up[0] = 100.0f;
    up[1] = 8.65f;
    up[2] = 0.0f;
    func_002062F0(eye, target, up, (f32 *)0x01ED0190);
    i = 0;
    do {
        base[0x53CF + i] = 0;
        base[0x53DB + i] = 6;
        base[0x53E7 + i] = 1;
        i++;
    } while (i < 12);
    *(s16 *)0x01ED547C = 0x80;
    *(s16 *)0x01ED0000 = 0x140;
    *(s16 *)0x01ED0002 = 0xBE;
    *(s16 *)0x01ED0004 = 0;
    *(s16 *)0x01ED001A = 0;
    *(s16 *)0x01ED001C = 0;
    *(s16 *)0x01ED001E = 0;
    *(s16 *)0x01ED536E = *(s16 *)(record + 0xC2);
    *(s16 *)0x01ED536C = 0;
    *(s8 *)0x01ED5372 = 0;
    *(s8 *)0x01ED006E = 0;
    *(f32 *)0x01ED0040 = 0.0f;
    *(f32 *)0x01ED0044 = 0.0f;
    *(f32 *)0x01ED0048 = 0.0f;
    *(f32 *)0x01ED004C = 0.0f;
    *(f32 *)0x01ED0030 = *(f32 *)0x01ED0040;
    *(f32 *)0x01ED0034 = 96.0f + *(f32 *)0x01ED0044;
    *(f32 *)0x01ED0038 = 96.0f + *(f32 *)0x01ED0048;
    *(f32 *)0x01ED003C = *(f32 *)0x01ED004C;
    func_001F9FE0(0, (void *)0x01ED0030, (void *)0x01ED0040);

    i = 0;
    words = (u32 *)0x01ED0000;
    do {
        words[0x8C / 4] = 0;
        words[0x10C / 4] = 0;
        words++;
        i++;
    } while (i < 32);
    *(s16 *)0x01ED01A6 = 0;
    *(s16 *)0x01ED01AE = 0;
    *(s16 *)0x01ED01B0 = 0;
    *(s16 *)0x01ED01B2 = 0;
    *(s16 *)0x01ED0224 = 0x80;
    rows = (u8 *)0x01ED0000;
    *(s16 *)0x01ED0226 = 0x80;
    *(s16 *)0x01ED0228 = 0x80;
    outer = 0;
    counts = (u8 *)0x01ED0000;
    data = (u8 *)0x01ED0000;
    do {
        inner = 0;
        row = rows;
        count = (s16 *)counts;
        block = (s16 *)data;
        do {
            *(s16 *)(row + 0x42E) = 0;
            count[0x42AC / 2] = 0;
            k = 0;
            cell = block;
            do {
                k++;
                cell[0x42EC / 2] = 0;
                cell++;
            } while (k < 64);
            inner++;
            row += 0x204;
            count++;
            block += 64;
        } while (inner < 16);
        outer++;
        rows += 0x2040;
        counts += 0x20;
        data += 0x800;
    } while (outer < 2);
    {
        u16 *clear;
        s32 clear_count = 0;
        clear = (u16 *)0x01ED0000;
        do {
            clear_count++;
            clear[0x52EC / 2] = 0;
            clear[0x532C / 2] = 0;
            clear++;
        } while (clear_count < 32);
    }

    if (D_0034F6F8 != 0) {
        *(Buffer_0021D480 *)func_002145E0(0) = *(Buffer_0021D480 *)0x01E301E0;
        D_0034F6F8 = 0;
    }
    n = 0;
    total = 0;
    for (; n < 12; n++) {
        total += (s32)*(u16 *)(record + 0x24) % 16;
        record += 2;
    }
    *(u16 *)0x01ED53F6 = total & 0xF;
    j = 0;
    shift = 0;
    halves = (u16 *)0x01ED0000;
    for (; j < 3; j++) {
        halves[0x53F8 / 2] = ((s32)D_00299CE0[*(u16 *)(base + 0x53F6)] >> shift) & 0x1F;
        shift += 5;
        halves[0x53FE / 2] = D_00299D00[halves[0x53F8 / 2]].value & 0x3FF;
        halves++;
    }
}

typedef struct Coord_0021D850 {
    f32 x;
    f32 y;
    f32 z;
} Coord_0021D850;

extern u8 D_00298BA0[];
extern u8 D_00298BA8[];
extern s8 D_00299ED6;
extern s8 D_00299ED7;
extern u8 D_00299F60;

void func_0021D850(void) {
    s16 var_s0;
    u8 *var_s1;
    s32 *var_s2;
    Coord_0021D850 pos;

    func_0021BB20(&D_00299F60);
    *(f32 *)0x01ED0040 = *(f32 *)(D_00298BA0 + D_00299ED6 * 0x34);
    *(f32 *)0x01ED0044 = 0.0f;
    *(f32 *)0x01ED0048 = *(f32 *)(D_00298BA8 + D_00299ED6 * 0x34);
    *(f32 *)0x01ED0040 = *(f32 *)(D_00298BA0 + D_00299ED7 * 0x34);
    *(f32 *)0x01ED0044 = 0.0f;
    *(f32 *)0x01ED0048 = *(f32 *)(D_00298BA8 + D_00299ED7 * 0x34);
    *(f32 *)0x01ED0030 = *(f32 *)0x01ED0040;
    *(f32 *)0x01ED0034 = 96.0f + *(f32 *)0x01ED0044;
    *(f32 *)0x01ED0038 = 96.0f + *(f32 *)0x01ED0048;
    *(f32 *)0x01ED003C = *(f32 *)0x01ED004C;
    func_001F9FE0(0, (void *)0x01ED0030, (void *)0x01ED0040);
    var_s1 = D_00298BA0;
    var_s0 = 0;
    var_s2 = (s32 *)0x01ED0000;
    while (var_s0 <= 0x15) {
        pos.x = *(f32 *)var_s1;
        pos.y = 8.65f + *(f32 *)(var_s1 + 4);
        pos.z = *(f32 *)(var_s1 + 8);
        func_0021BB90((s32 *)((u8 *)var_s2 + 0x8C), (s32 *)((u8 *)var_s2 + 0x10C), (s32)&pos);
        var_s1 += 0x34;
        var_s2++;
        var_s0++;
    }
    *(s16 *)0x01ED0000 = 0x140;
    *(s16 *)0x01ED0002 = 0xBE;
}

void func_0021DA60(void) {
    if (D_0034F710 == 0) {
        func_00209D30(func_0021DDA0(func_00209D20()));
    }
}

typedef struct {
    f32 x, y, z, w;
} Vec4_0021DAA0;

void *func_0021DFF0(void *, s32, s32, s32, f32, s32, s32, s32);
void *func_002297C0(s32);
void *func_0023BFF0(void *, s32, s32, f32, f32);
extern s16 D_00298AD0;
extern s16 D_00298AD2;
extern s16 D_00298AD4;
extern s16 D_00298ADA;
extern Vec4_0021DAA0 D_0029A7B0;
extern Vec4_0021DAA0 D_0029A7C0;

static inline s32 offset_y_0021DAA0(s32 y) {
    return (s16)y - 0x100;
}

void func_0021DAA0(void) {
    extern void *func_00218970(void *, void *, s16, s16);
    Vec4_0021DAA0 sp80;
    Vec4_0021DAA0 sp90;
    s8 *state;
    s16 angle;
    s16 x_offset;
    s16 y_offset;
    s32 temp_s4;
    s32 temp_s5;
    s16 temp_v0;
    s16 temp_v0_2;
    s8 temp_a1;
    void *var_s6;

    state = &D_00299E10;
    angle = ((*(s16 *)0x01ED5478 << 10) >> 12) - 0x200;
    if (D_0034F710 == 0) {
        var_s6 = func_002297C0(func_00209D20());
        temp_v0 = *(s16 *)0x01ED006C;
        if (temp_v0 != 0) {
            temp_a1 = *(s8 *)0x01ED5440;
            y_offset = offset_y_0021DAA0(temp_v0);
            x_offset = (temp_a1 * -0x280) / 100;
            if (*(s8 *)0x01ED5488 != 0) {
                var_s6 = func_00218970(var_s6, &D_00298AD0, x_offset, y_offset);
                *(s8 *)0x01ED5488 = 0;
            }
            if (func_001F12A0(0x1F) == 0) {
                if ((*(s8 *)0x01ED5406 == 1) && (*(s16 *)0x01ED006C != 0)) {
                    sp80 = D_0029A7B0;
                    sp90 = D_0029A7C0;
                    *(s16 *)0x01ED5404 = func_002159D0(1, 0);
                    func_001F22B0(0x1F, &sp80);
                    func_001F2430(0x1F, &sp90);
                    func_001E8780(0x1F, -1, func_001DE1A0(*(s16 *)0x01ED5404), 1);
                    *(s8 *)0x01ED5406 = 2;
                    *(s16 *)0x01ED543A = 0;
                }
            }
            if ((func_001F1300(0x1F) != 0) && (*(s8 *)0x01ED5406 == 2)) {
                temp_v0_2 = *(s16 *)0x01ED543A;
                if (temp_v0_2 < 0x80) {
                    *(s16 *)0x01ED543A = temp_v0_2 + 8;
                }
                if (*(s16 *)0x01ED543A >= 0x80) {
                    *(s16 *)0x01ED543A = 0x80;
                }
                temp_s4 = D_00298AD2;
                temp_s5 = D_00298AD0;
                var_s6 = func_0021DFF0(var_s6, 0x1F, temp_s5 + x_offset,
                    temp_s4 + y_offset, (f32)func_001DE260(*(s16 *)0x01ED5404),
                    D_00298AD4 - temp_s5, D_00298ADA - temp_s4, *(s16 *)0x01ED543A);
            }
        }
        if (*(s8 *)0x01ED5472 != 0) {
            var_s6 = func_0023BFF0(var_s6, *state ^ 1, *(s32 *)0x01ED5474, (f32)angle, 0.0f);
        }
        *(s8 *)0x01ED5481 = 0;
        func_00209D30((s32) var_s6);
    }
}

INCLUDE_ASM("asm/nonmatchings/main_062", func_0021DDA0);

INCLUDE_ASM("asm/nonmatchings/main_062", func_0021DFF0);

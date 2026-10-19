/* Maths: sine, cosine, heap sort (RhMath_*). */

#include "common.h"

/* The cosine of an angle in the game's units (0x10000 = 360 degrees), from the table. */
f32 RhMath_CosI(s32 angle) {
    f32 sign;
    f32 *samples;
    f32 sample0;
    f32 sample1;
    s32 fraction;

    angle = (s16)(angle + 0x4000);
    sign = 1.0f;
    if (angle < 0) {
        sign = -1.0f;
        angle = -angle;
    }
    if (angle > 0x4000) {
        angle = 0x8000 - angle;
    }
    if ((angle & 0x3FFF) == 0) {
        return angle == 0x4000 ? sign : 0.0f;
    }
    fraction = angle & 0xF;
    samples = &gRhMath_adwSinTable[angle >> 4];
    sample0 = samples[0];
    sample1 = samples[1];
    return sign * (sample0 * (16 - fraction) + sample1 * fraction) / 16.0f;
}

/* The sine of an angle in the game's units (0x10000 = 360 degrees), from the table. */
f32 RhMath_SinI(s32 angle) {
    f32 sign;
    f32 *samples;
    f32 sample0;
    f32 sample1;
    s32 fraction;

    angle = (s16)angle;
    sign = 1.0f;
    if (angle < 0) {
        sign = -1.0f;
        angle = -angle;
    }
    if (angle > 0x4000) {
        angle = 0x8000 - angle;
    }
    if ((angle & 0x3FFF) == 0) {
        return angle == 0x4000 ? sign : 0.0f;
    }
    fraction = angle & 0xF;
    samples = &gRhMath_adwSinTable[angle >> 4];
    sample0 = samples[0];
    sample1 = samples[1];
    return sign * (sample0 * (16 - fraction) + sample1 * fraction) / 16.0f;
}

/* The cosine of an angle in radians, from the table. */
f32 RhMath_Cos(f32 angle) {
    s32 phase;
    f32 sign;
    s32 fraction;
    f32 weight;
    f32 *entry;
    f32 lower;
    f32 upper;

    phase = (s16)(s32)(16384.0f + (0.5f + ((65536.0f * angle) / 6.2831855f)));
    sign = 1.0f;
    if (phase < 0) {
        sign = -1.0f;
        phase = -phase;
    }
    if (phase > 0x4000) {
        phase = 0x8000 - phase;
    }
    if ((phase & 0x3FFF) == 0) {
        if (phase == 0x4000) {
            return sign;
        }
        sign = 0.0f;
    } else {
        fraction = phase & 0xF;
        weight = fraction;
        entry = &gRhMath_adwSinTable[phase >> 4];
        lower = entry[0];
        upper = entry[1];
        sign = (sign * (lower * (16 - fraction) + upper * weight)) / 16.0f;
    }
    return sign;
}

/* The sine of an angle in radians, from the table. */
f32 RhMath_Sin(f32 angle) {
    s32 phase;
    f32 sign;
    s32 fraction;
    f32 weight;
    f32 *entry;
    f32 lower;
    f32 upper;

    phase = (s16)func_001A22C0(0.5f + ((65536.0f * angle) / 6.2831855f));
    sign = 1.0f;
    if (phase < 0) {
        sign = -1.0f;
        phase = -phase;
    }
    if (phase > 0x4000) {
        phase = 0x8000 - phase;
    }
    if ((phase & 0x3FFF) == 0) {
        if (phase == 0x4000) {
            return sign;
        }
        sign = 0.0f;
    } else {
        fraction = phase & 0xF;
        weight = fraction;
        entry = &gRhMath_adwSinTable[phase >> 4];
        lower = entry[0];
        upper = entry[1];
        sign = (sign * (lower * (16 - fraction) + upper * weight)) / 16.0f;
    }
    return sign;
}

/* Heap-sorts `count` records of `size` bytes at `base` with `compare`. */
void RhMath_HeapSortStruct(u8 *base, s32 count, s32 size, s32 (*compare)(u8 *, u8 *)) {
    s32 spA0;
    u8 *var_s3_2;
    u8 *temp_s3;
    s32 var_v0;
    s32 var_s3;
    s32 var_s4_2;
    s32 var_fp_2;
    s32 var_s2;
    u8 *sentinel;
    u8 *temp_s5;
    s32 var_s6;
    s32 var_s4;
    s32 var_fp;
    u8 *temp_s6;
    u8 *spB0;

    sentinel = &abTmpBuf;
    var_fp = count >> 1;
    temp_s5 = base - size;
    var_s2 = count;
    if (var_fp > 0) {
        spA0 = var_fp * size;
        do {
            var_s3 = var_fp;
            RhMem_CopyMemory(sentinel, temp_s5 + spA0, size);
            while ((var_s4 = var_s3 * 2) <= var_s2) {
                if (var_s4 < var_s2 &&
                    compare(temp_s5 + (var_s4 * size), temp_s5 + ((var_s4 + 1) * size)) < 0) {
                    var_s4 += 1;
                }
                temp_s6 = temp_s5 + (var_s4 * size);
                if (compare(sentinel, temp_s6) >= 0) {
                    break;
                }
                var_v0 = var_s3 * size;
                RhMem_CopyMemory(temp_s5 + var_v0, temp_s6, size);
                var_s3 = var_s4;
            }
            RhMem_CopyMemory(temp_s5 + (var_s3 * size), sentinel, size);
            var_fp -= 1;
            spA0 -= size;
        } while (var_fp > 0);
    }
    if (var_s2 > 1) {
        var_fp_2 = var_s2 * size;
        spB0 = temp_s5 + size;
        var_s3_2 = temp_s5 + var_fp_2;
        do {
            RhMem_CopyMemory(sentinel, var_s3_2, size);
            RhMem_CopyMemory(var_s3_2, spB0, size);
            var_s2 -= 1;
            var_s4_2 = 1;
            var_fp_2 -= size;
            while ((var_s6 = var_s4_2 * 2) <= var_s2) {
                if (var_s6 < var_s2 &&
                    compare(temp_s5 + (var_s6 * size), temp_s5 + ((var_s6 + 1) * size)) < 0) {
                    var_s6 += 1;
                }
                temp_s3 = temp_s5 + (var_s6 * size);
                if (compare(sentinel, temp_s3) >= 0) {
                    break;
                }
                RhMem_CopyMemory(temp_s5 + (var_s4_2 * size), temp_s3, size);
                var_s4_2 = var_s6;
            }
            RhMem_CopyMemory(temp_s5 + (var_s4_2 * size), sentinel, size);
            var_s3_2 = temp_s5 + var_fp_2;
        } while (var_s2 > 1);
    }
}

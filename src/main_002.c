#include "common.h"

void func_00106DE0(f32 x, f32 y, f32 z, s32 *out) {
    extern s32 func_001A22C0(f32);

    out[0] = func_001A22C0(x);
    out[1] = func_001A22C0(y);
    out[2] = func_001A22C0(z);
}

void func_00106E40(s32 *dst, f32 *src) {
    extern s32 func_001A22C0(f32);

    dst[0] = func_001A22C0(src[0]);
    dst[1] = func_001A22C0(src[1]);
    dst[2] = func_001A22C0(src[2]);
}

void func_00106E90(void *arg0, void *arg1) {
    f32 *dst = arg0;
    f32 *src = arg1;

    dst[0] *= src[0];
    dst[1] *= src[1];
    dst[2] *= src[2];
}

void func_00106ED0(void *arg0, void *arg1) {
    f32 *matrix = (f32 *)arg0;
    f32 *scale = (f32 *)arg1;

    matrix[0] *= scale[0];
    matrix[1] *= scale[1];
    matrix[2] *= scale[2];
    matrix[4] *= scale[0];
    matrix[5] *= scale[1];
    matrix[6] *= scale[2];
    matrix[8] *= scale[0];
    matrix[9] *= scale[1];
    matrix[10] *= scale[2];
    matrix[12] *= scale[0];
    matrix[13] *= scale[1];
    matrix[14] *= scale[2];
}

void func_00106FA0(f32 *dst, f32 *src) {
    dst[0] += src[0];
    dst[1] += src[1];
    dst[2] += src[2];
    dst[4] += src[0];
    dst[5] += src[1];
    dst[6] += src[2];
    dst[8] += src[0];
    dst[9] += src[1];
    dst[10] += src[2];
    dst[12] += src[0];
    dst[13] += src[1];
    dst[14] += src[2];
}

s32 func_00107070(void *arg0, s64 arg1, f32 fparg0) {
    f32 (*matrix)[4] = (f32 (*)[4])arg0;

    if (arg1 == 0) {
        matrix[0][0] += fparg0;
        matrix[1][0] += fparg0;
        matrix[2][0] += fparg0;
        matrix[3][0] += fparg0;
    } else if ((s16)arg1 == 1) {
        matrix[0][1] += fparg0;
        matrix[1][1] += fparg0;
        matrix[2][1] += fparg0;
        matrix[3][1] += fparg0;
    } else {
        matrix[0][2] += fparg0;
        matrix[1][2] += fparg0;
        matrix[2][2] += fparg0;
        matrix[3][2] += fparg0;
    }
    return 0;
}

s32 func_00107130(void *arg0, void *arg1, s32 arg2) {
    if (arg2 == 0) {
        ((f32 *)arg0)[0] = ((f32 *)arg1)[0];
        ((f32 *)arg0)[1] = ((f32 *)arg1)[1];
        ((f32 *)arg0)[2] = ((f32 *)arg1)[2];
    } else {
        ((f32 *)arg1)[0] = ((f32 *)arg0)[0];
        ((f32 *)arg1)[1] = ((f32 *)arg0)[1];
        ((f32 *)arg1)[2] = ((f32 *)arg0)[2];
    }
    return 0;
}


static inline void reduce_00107180(f32 *value) {
    *value -= 0.18f;
    if (*value < 0.0f) {
        *value = 0.0f;
    }
}

s32 func_00107180(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    f32 values[3];

    if ((func_001F5EC0(arg0) != 0) && (arg3 != 0)) {
        func_001F6340(arg0, values);
        reduce_00107180(values);
        reduce_00107180(&values[1]);
        reduce_00107180(&values[2]);
        func_001F62B0(arg0, values);
    }
    return 0;
}

s32 func_00107280(s32 arg0) {
    u8 data[4];
    u8 temp_v0;

    if (func_001F5AF0(arg0) != 0) {
        func_001F5E40(arg0, data);
        temp_v0 = data[3];
        if (temp_v0 > 0x14) {
            data[3] = temp_v0 - 0x13;
        } else {
            data[3] = 0;
        }
        func_001F5DE0(arg0, (s32) data);
        if (data[3] == 0) {
            return 1;
        }
    }
    return 0;
}

s32 func_00107310(s32 arg0, s32 arg1, s32 arg2) {
    f32 scale[3];

    if ((func_001F5EC0(arg0) != 0) && (arg2 != 0)) {
        scale[0] = 1.0f;
        scale[1] = 1.0f;
        scale[2] = 1.0f;
        func_001F62B0(arg0, scale);
    }
    return 0;
}


static inline void add_clamped_00107370(f32 *value, f32 amount) {
    *value += amount;
    if (!(*value <= 1.0f)) {
        *value = 1.0f;
    }
}

s32 func_00107370(s32 arg0, f32 fparg0) {
    f32 color[3];

    if (func_001F5EC0(arg0) != 0) {
        func_001F6340(arg0, color);
        add_clamped_00107370(&color[0], fparg0);
        add_clamped_00107370(&color[1], fparg0);
        add_clamped_00107370(&color[2], fparg0);
        func_001F62B0(arg0, color);
    }
    return 0;
}


static inline void subtract_00107450(f32 *value, f32 amount) {
    *value -= amount;
    if (*value < 0.0f) {
        *value = 0.0f;
    }
}

s32 func_00107450(s32 arg0, f32 fparg0) {
    f32 values[3];

    if (func_001F5EC0(arg0) != 0) {
        func_001F6340(arg0, values);
        subtract_00107450(&values[0], fparg0);
        subtract_00107450(&values[1], fparg0);
        subtract_00107450(&values[2], fparg0);
        func_001F62B0(arg0, values);
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_002", func_00107510);

s32 func_00107650(s32 arg0, s32 arg1) {
    u8 color[4];

    if (func_001F5AF0(arg0) != 0) {
        func_001F5E40(arg0, color);
        color[3] += arg1;
        if (color[3] >= 0x80) {
            color[3] = 0x80;
        }
        func_001F5DE0(arg0, (s32) color);
        if (color[3] >= 0x80) {
            return 1;
        }
    }
    return 0;
}

s32 func_001076F0(void *arg0, s8 arg1, s8 arg2, s8 arg3) {
    ((s8 *)arg0)[0] = arg1;
    ((s8 *)arg0)[1] = arg2;
    ((s8 *)arg0)[2] = arg3;
    return 0;
}

s32 func_00107710(u8 *arg0, u8 *arg1) {
    arg0[0] = arg1[0];
    arg0[1] = arg1[1];
    arg0[2] = arg1[2];
    arg0[3] = arg1[3];
    return 0;
}

typedef struct {
    f32 x;
    f32 y;
} FloatPair_00107740;

typedef union {
    struct {
        u8 bytes[4];
        f32 value;
    } packed;
    FloatPair_00107740 pair;
} PackedPair_00107740;

void func_00107740(void *arg0, void *arg1) {
    PackedPair_00107740 temp;
    u8 *src = arg1;

    temp.packed.bytes[0] = src[0];
    temp.packed.bytes[1] = src[1];
    temp.packed.bytes[2] = src[2];
    temp.packed.bytes[3] = src[3];
    temp.packed.value = 1.0f;
    *(FloatPair_00107740 *)arg0 = temp.pair;
}

typedef struct {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
    f32 q;
} Rgbaq_00107790;

typedef struct {
    Rgbaq_00107790 rgbaq;
    u64 st;
    u64 xyz;
} Vertex_00107790;

typedef struct {
    u8 tag[0x10];
    Vertex_00107790 v[4];
} Packet_00107790;

static inline Rgbaq_00107790 rgbaq_00107790(u8 *color) {
    Rgbaq_00107790 c;

    c.r = color[0];
    c.g = color[1];
    c.b = color[2];
    c.a = color[3];
    c.q = 1.0f;
    return c;
}

s32 func_00107790(void *arg0, u8 *arg1, s32 arg2) {
    Packet_00107790 *packet = arg0;

    if (arg2 == 0) {
        packet->v[0].rgbaq = rgbaq_00107790(arg1);
        packet->v[1].rgbaq = rgbaq_00107790(arg1);
        packet->v[2].rgbaq = rgbaq_00107790(arg1);
        packet->v[3].rgbaq = rgbaq_00107790(arg1);
    } else if (arg2 == 1) {
        packet->v[0].rgbaq = rgbaq_00107790(arg1);
        packet->v[1].rgbaq = rgbaq_00107790(arg1);
    } else if (arg2 == 2) {
        packet->v[2].rgbaq = rgbaq_00107790(arg1);
        packet->v[3].rgbaq = rgbaq_00107790(arg1);
    }
    return 0;
}

typedef struct {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
    f32 q;
} Rgbaq_00107990;

typedef struct {
    Rgbaq_00107990 rgbaq;
    u64 xyz;
} Vertex_00107990;

typedef struct {
    u8 tag[0x10];
    Vertex_00107990 v[4];
} Packet_00107990;

static inline Rgbaq_00107990 rgbaq_00107990(u8 *color) {
    Rgbaq_00107990 c;

    c.r = color[0];
    c.g = color[1];
    c.b = color[2];
    c.a = color[3];
    c.q = 1.0f;
    return c;
}

s32 func_00107990(void *arg0, u8 *arg1, s32 arg2) {
    Packet_00107990 *packet = arg0;

    if (arg2 == 0) {
        packet->v[0].rgbaq = rgbaq_00107990(arg1);
        packet->v[1].rgbaq = rgbaq_00107990(arg1);
        packet->v[2].rgbaq = rgbaq_00107990(arg1);
        packet->v[3].rgbaq = rgbaq_00107990(arg1);
    } else if (arg2 == 1) {
        packet->v[0].rgbaq = rgbaq_00107990(arg1);
        packet->v[1].rgbaq = rgbaq_00107990(arg1);
    } else if (arg2 == 2) {
        packet->v[2].rgbaq = rgbaq_00107990(arg1);
        packet->v[3].rgbaq = rgbaq_00107990(arg1);
    }
    return 0;
}

void func_00107B90(f32 *arg0, f32 *arg1, void *arg2, void *arg3) {
    f32 temp_f0;
    f32 temp_f0_2;

    *arg0 = ((f32 *)arg3)[0] - (((f32 *)arg2)[0] + ((f32 *)arg2)[4]);
    *arg1 = ((f32 *)arg3)[2] - (((f32 *)arg2)[2] + ((f32 *)arg2)[6]);
    temp_f0 = *arg0;
    *arg0 = func_001A6C60(temp_f0 * temp_f0);
    temp_f0_2 = *arg1;
    *arg1 = func_001A6C60(temp_f0_2 * temp_f0_2);
}

void func_00107C10(f32 *arg0) {
    s16 i;
    f32 *dst;

    dst = arg0;
    for (i = 0; i < 91; i++) {
        *dst = func_001A6A88((3.1415927f * (f32)i) / 180.0f);
        dst++;
    }
}

void func_00107CB0(void *arg0, s32 arg1, s32 arg2) {
    s16 i;
    s32 angle;
    f32 *p;
    f32 radians;

    p = arg0;
    i = 0;
    angle = 0;
    while (i < arg2) {
        radians = (3.1415927f * (f32)angle) / 180.0f;
        p[0] = func_001A6A88(radians);
        p[20] = func_001A6898(radians);
        radians = (3.1415927f * (f32)(arg1 + angle)) / 180.0f;
        p[40] = func_001A6A88(radians);
        p[60] = func_001A6898(radians);
        angle += arg1;
        p++;
        i++;
    }
}

s32 func_00107DD0(void *arg0, void *arg1, void *arg2) {
    f32 *dst = arg0;
    f32 *src = arg1;
    f32 *base = arg2;

    dst[0] += src[0] - base[0];
    dst[2] += src[2] - base[2];
    dst[4] += src[0] - base[0];
    dst[6] += src[2] - base[2];
    return 0;
}

typedef struct Fields_00107E40 {
    u8 padding[0xA0];
    f32 value;
    u8 padding_a4[4];
    s16 first;
    s16 second;
} Fields_00107E40;

s32 func_00107E40(f32 fparg0, f32 fparg1, f32 fparg2, void *arg0) {
    Fields_00107E40 *fields = arg0;

    fields->first = func_001A22C0(fparg0);
    fields->second = func_001A22C0(fparg1);
    fields->value = fparg2;
    return 0;
}

s32 func_00107EA0(void *arg0, f32 fparg0, f32 fparg1, f32 fparg2) {
    *(f32 *)((u8 *)arg0 + 0x449C) = fparg0;
    *(f32 *)((u8 *)arg0 + 0x44A0) = fparg1;
    *(f32 *)((u8 *)arg0 + 0x44A4) = fparg2;
    return 0;
}

s32 func_00107EC0(u8 *arg0, s32 arg1, s16 arg2) {
    if (arg2 == 0) {
        arg0[0] = 0xFF;
        arg0[1] = 0xFF;
        arg0[2] = 0xFF;
    } else if (arg2 == 1) {
        arg0[0] = 0xFF;
        arg0[1] = 0;
        arg0[2] = 0;
    } else if (arg2 == 2) {
        arg0[0] = 0;
        arg0[1] = 0xFF;
        arg0[2] = 0;
    } else if (arg2 == 3) {
        arg0[0] = 0;
        arg0[1] = 0;
        arg0[2] = 0xFF;
    } else if (arg2 == 4) {
        arg0[0] = 0xFF;
        arg0[1] = 0xFF;
        arg0[2] = 0;
    } else if (arg2 == 5) {
        arg0[0] = 0xFF;
        arg0[1] = 0;
        arg0[2] = 0xFF;
    } else if (arg2 == 6) {
        arg0[0] = 0;
        arg0[1] = 0xFF;
        arg0[2] = 0xFF;
    } else if (arg2 == 7) {
        arg0[0] = 0xFF;
        arg0[1] = 0x80;
        arg0[2] = 0xFF;
    } else if (arg2 == 8) {
        arg0[0] = 0x80;
        arg0[1] = 0;
        arg0[2] = 0xFF;
    } else if (arg2 == 9) {
        arg0[0] = 0xFF;
        arg0[1] = 0x80;
        arg0[2] = 0;
    } else {
        arg0[0] = 0xFF;
        arg0[1] = 0xFF;
        arg0[2] = 0xFF;
    }
    return 0;
}

f32 func_00108030(s32 arg0, s32 arg1, s32 arg2) {
    f32 result;
    f32 *table = (f32 *)arg0;

    if (arg2 == 0) {
        if ((s16)arg1 >= 360) {
            arg1 = (s16)(arg1 % 360);
        }
        if ((s16)arg1 <= -360) {
            arg1 = (s16)(arg1 % 360);
        }
        if ((s16)arg1 < 0) {
            arg1 = (s16)(arg1 + 360);
        }

        if ((s16)arg1 < 90) {
            table += (s16)arg1;
            result = *table;
        } else if ((s16)arg1 < 180) {
            table += 90 - (s16)(arg1 - 90);
            result = *table;
        } else if ((s16)arg1 < 270) {
            table += (s16)(arg1 - 180);
            result = *table;
            result *= -1.0f;
        } else {
            table += 90 - (s16)(arg1 - 270);
            result = *table;
            result *= -1.0f;
        }
    } else {
        if ((s16)arg1 >= 360) {
            arg1 = (s16)(arg1 % 360);
        }
        if ((s16)arg1 <= -360) {
            arg1 = (s16)(arg1 % 360);
        }
        if ((s16)arg1 < 0) {
            arg1 = (s16)(arg1 + 360);
        }

        if ((s16)arg1 < 90) {
            table += 90 - (s16)arg1;
            result = *table;
        } else if ((s16)arg1 < 180) {
            table += (s16)(arg1 - 90);
            result = *table;
            result *= -1.0f;
        } else if ((s16)arg1 < 270) {
            table += 90 - (s16)(arg1 - 180);
            result = *table;
            result *= -1.0f;
        } else {
            table += (s16)(arg1 - 270);
            result = *table;
        }
    }

    return result;
}

s32 func_001082B0(s64 x, s64 y) {
    s64 ax;
    s64 ay;

    if (x == 0 && y == 0) {
        return 0;
    }
    ax = func_00195070(x);
    ay = func_00195070(y);
    if (ax + ay == 0) {
        return 0;
    }
    if (y >= 0) {
        if (x > 0) {
            if (ax == ay) {
                return 45;
            } else if (ay < ax) {
                return func_001A0660(ay * 45, ax);
            } else {
                return 90 - func_001A0660(ax * 45, ay);
            }
        } else {
            if (ax == ay) {
                return 135;
            } else if (ay < ax) {
                return 180 - func_001A0660(ay * 45, ax);
            } else {
                return func_001A0660(ax * 45, ay) + 90;
            }
        }
    } else {
        if (x > 0) {
            if (ax == ay) {
                return 315;
            } else if (ay < ax) {
                return 360 - func_001A0660(ay * 45, ax);
            } else {
                return func_001A0660(ax * 45, ay) + 270;
            }
        } else {
            if (ax == ay) {
                return 225;
            } else if (ay < ax) {
                return func_001A0660(ay * 45, ax) + 180;
            } else {
                return 270 - func_001A0660(ax * 45, ay);
            }
        }
    }
}

typedef struct UV_00108500 {
    u64 u : 14;
    u64 : 2;
    u64 v : 14;
    u64 : 34;
} UV_00108500;

typedef struct Rect_00108500 {
    s16 x;
    s16 y;
    s16 width;
    s16 height;
} Rect_00108500;

static inline s32 edge_uv_00108500(s32 extent, s32 origin) {
    return (origin + extent) << 4;
}

void func_00108500(void *arg0, void *arg1, s32 arg2) {
    Rect_00108500 *rect = arg1;

    if (arg2 == 0) {
        ((UV_00108500 *)((u8 *)arg0 + 0x18))->u = (rect->x << 4);
        ((UV_00108500 *)((u8 *)arg0 + 0x18))->v = (rect->y << 4);
        ((UV_00108500 *)((u8 *)arg0 + 0x30))->u = edge_uv_00108500(rect->width, rect->x);
        ((UV_00108500 *)((u8 *)arg0 + 0x30))->v = (rect->y << 4);
        ((UV_00108500 *)((u8 *)arg0 + 0x48))->u = (rect->x << 4);
        ((UV_00108500 *)((u8 *)arg0 + 0x48))->v = edge_uv_00108500(rect->height, rect->y);
        ((UV_00108500 *)((u8 *)arg0 + 0x60))->u = edge_uv_00108500(rect->width, rect->x);
        ((UV_00108500 *)((u8 *)arg0 + 0x60))->v = edge_uv_00108500(rect->height, rect->y);
    } else if (arg2 == 1) {
        ((UV_00108500 *)((u8 *)arg0 + 0x18))->u = (rect->x << 4);
        ((UV_00108500 *)((u8 *)arg0 + 0x18))->v = edge_uv_00108500(rect->height, rect->y);
        ((UV_00108500 *)((u8 *)arg0 + 0x30))->u = (rect->x << 4);
        ((UV_00108500 *)((u8 *)arg0 + 0x30))->v = (rect->y << 4);
        ((UV_00108500 *)((u8 *)arg0 + 0x48))->u = edge_uv_00108500(rect->width, rect->x);
        ((UV_00108500 *)((u8 *)arg0 + 0x48))->v = edge_uv_00108500(rect->height, rect->y);
        ((UV_00108500 *)((u8 *)arg0 + 0x60))->u = edge_uv_00108500(rect->width, rect->x);
        ((UV_00108500 *)((u8 *)arg0 + 0x60))->v = (rect->y << 4);
    } else if (arg2 == 10) {
        ((UV_00108500 *)((u8 *)arg0 + 0x48))->u = (rect->x << 4);
        ((UV_00108500 *)((u8 *)arg0 + 0x48))->v = (rect->y << 4);
        ((UV_00108500 *)((u8 *)arg0 + 0x18))->u = edge_uv_00108500(rect->width, rect->x);
        ((UV_00108500 *)((u8 *)arg0 + 0x18))->v = (rect->y << 4);
        ((UV_00108500 *)((u8 *)arg0 + 0x60))->u = (rect->x << 4);
        ((UV_00108500 *)((u8 *)arg0 + 0x60))->v = edge_uv_00108500(rect->height, rect->y);
        ((UV_00108500 *)((u8 *)arg0 + 0x30))->u = edge_uv_00108500(rect->width, rect->x);
        ((UV_00108500 *)((u8 *)arg0 + 0x30))->v = edge_uv_00108500(rect->height, rect->y);
    } else {
        ((UV_00108500 *)((u8 *)arg0 + 0x30))->u = (rect->x << 4);
        ((UV_00108500 *)((u8 *)arg0 + 0x30))->v = (rect->y << 4);
        ((UV_00108500 *)((u8 *)arg0 + 0x18))->u = edge_uv_00108500(rect->width, rect->x);
        ((UV_00108500 *)((u8 *)arg0 + 0x18))->v = (rect->y << 4);
        ((UV_00108500 *)((u8 *)arg0 + 0x60))->u = (rect->x << 4);
        ((UV_00108500 *)((u8 *)arg0 + 0x60))->v = edge_uv_00108500(rect->height, rect->y);
        ((UV_00108500 *)((u8 *)arg0 + 0x48))->u = edge_uv_00108500(rect->width, rect->x);
        ((UV_00108500 *)((u8 *)arg0 + 0x48))->v = edge_uv_00108500(rect->height, rect->y);
    }
}

INCLUDE_ASM("asm/nonmatchings/main_002", func_00108950);

typedef struct Vec4_00108BE0 {
    f32 x, y, z, w;
} Vec4_00108BE0;

void func_00108BE0(void *arg0, void *arg1, s64 arg2, f32 arg3, f32 arg4) {
    Vec4_00108BE0 input;
    Vec4_00108BE0 output;

    input = *(Vec4_00108BE0 *)arg1;
    if (arg2 == 0) {
        output.x = arg3 * input.x + -arg4 * input.z;
        output.z = arg4 * input.x + arg3 * input.z;
        output.y = input.y;
    }
    if ((s16)arg2 == 1) {
        output.x = input.x;
        output.y = arg4 * input.y + arg3 * input.z;
        output.z = -arg3 * input.y + arg4 * input.z;
    }
    if ((s16)arg2 == 2) {
        output.x = arg3 * input.x + arg4 * input.y;
        output.y = -arg4 * input.x + arg3 * input.y;
        output.z = input.z;
    }
    *(Vec4_00108BE0 *)arg0 = output;
}

typedef struct Vec4_00108CE0 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4_00108CE0;

s32 func_00108CE0(void *arg0, f32 fparg0, f32 fparg1) {
    Vec4_00108CE0 *vertices = arg0;
    f32 negative_x;
    f32 negative_y;

    negative_x = -fparg0;
    vertices[0].x = negative_x;
    vertices[0].y = fparg1;
    vertices[0].z = 0.0f;
    vertices[1].x = fparg0;
    vertices[1].y = fparg1;
    vertices[1].z = 0.0f;
    vertices[2].x = negative_x;
    negative_y = -fparg1;
    vertices[2].y = negative_y;
    vertices[2].z = 0.0f;
    vertices[3].x = fparg0;
    vertices[3].y = negative_y;
    vertices[3].z = 0.0f;
    return 0;
}

s32 func_00108D20(void *dst, f32 x, f32 z) {
    f32 (*vertices)[4] = dst;

    vertices[0][0] = -x;
    vertices[0][1] = 0.0f;
    vertices[0][2] = z;
    vertices[1][0] = x;
    vertices[1][1] = 0.0f;
    vertices[1][2] = z;
    vertices[2][0] = -x;
    vertices[2][1] = 0.0f;
    vertices[2][2] = -z;
    vertices[3][0] = x;
    vertices[3][1] = 0.0f;
    vertices[3][2] = -z;
    return 0;
}

s32 func_00108D60(void *arg0, s32 arg1, s32 arg2, s16 arg3) {
    f32 x;
    f32 y;
    f32 *coords = arg0;

    if (arg3 == 0) {
        x = (f32) -(s16) arg1;
        y = (f32) arg2;
        coords[0] = x;
        coords[1] = y;
        coords[2] = 0.0f;
        coords[4] = 0.0f;
        coords[5] = y;
        coords[6] = 0.0f;
        coords[8] = x;
        coords[9] = 0.0f;
        coords[10] = 0.0f;
        coords[12] = 0.0f;
        coords[13] = 0.0f;
        coords[14] = 0.0f;
    } else if (arg3 == 1) {
        x = (f32) arg1;
        y = (f32) arg2;
        coords[0] = x;
        coords[1] = y;
        coords[2] = 0.0f;
        coords[4] = 0.0f;
        coords[5] = y;
        coords[6] = 0.0f;
        coords[8] = x;
        coords[9] = 0.0f;
        coords[10] = 0.0f;
        coords[12] = 0.0f;
        coords[13] = 0.0f;
        coords[14] = 0.0f;
    } else if (arg3 == 2) {
        x = (f32) -(s16) arg1;
        coords[0] = x;
        y = (f32) -(s16) arg2;
        coords[1] = y;
        coords[2] = 0.0f;
        coords[4] = 0.0f;
        coords[5] = y;
        coords[6] = 0.0f;
        coords[8] = x;
        coords[9] = 0.0f;
        coords[10] = 0.0f;
        coords[12] = 0.0f;
        coords[13] = 0.0f;
        coords[14] = 0.0f;
    } else if (arg3 == 3) {
        x = (f32) arg1;
        coords[0] = x;
        y = (f32) -(s16) arg2;
        coords[1] = y;
        coords[2] = 0.0f;
        coords[4] = 0.0f;
        coords[5] = y;
        coords[6] = 0.0f;
        coords[8] = x;
        coords[9] = 0.0f;
        coords[10] = 0.0f;
        coords[12] = 0.0f;
        coords[13] = 0.0f;
        coords[14] = 0.0f;
    }
    return 0;
}

typedef struct {
    s32 data[16];
} Matrix_00108EF0;

void func_0020C940(void *, s32, s32, s32);

void func_00108EF0(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    Matrix_00108EF0 sp50;
    Matrix_00108EF0 sp90;

    func_0020EB40(&sp90);
    func_0020C940(&sp50, arg1, arg2, arg3);
    func_0020BC00((s32) &sp90, &sp50);
    *(Matrix_00108EF0 *)arg0 = sp90;
}

s32 func_00108F90(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    f32 result[4];

    if (func_00205630(arg0, 0x70000000, arg2, arg1, result) != 0) {
        func_002075F0(arg1, arg3, func_001A23B0(result[0]));
    }
    return 0;
}

s32 func_00108FF0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    f32 depth[4];

    if (func_00205630(arg0, 0x70000000, arg2, arg1, depth) != 0) {
        func_002075F0(arg1, arg3, func_001A23B0(depth[0]));
    }
    return 0;
}

typedef struct Color_00109050 {
    u64 low : 32;
    u64 rgb : 24;
    u64 high : 8;
} Color_00109050;

s32 func_00109050(s32 arg0, void *arg1, s32 arg2, s32 arg3) {
    f32 result[4];

    if (func_00205630(arg0, 0x70000000, arg2, (s32)arg1, result) != 0) {
        ((Color_00109050 *)((u8 *)arg1 + 0x18))->rgb = 0xFFFFFF;
        ((Color_00109050 *)((u8 *)arg1 + 0x28))->rgb = 0xFFFFFF;
        func_002075F0((s32)arg1, arg3, 0);
    }
    return 0;
}

typedef struct Vec4_00109100 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4_00109100;

s32 func_00108950(void *, void *, s32, s32);

s32 func_00109100(u8 *arg0, void *arg1, s32 arg2, s32 arg3) {
    Vec4_00109100 sp40 = *(Vec4_00109100 *)arg1;

    func_00108950(arg0, &sp40, arg2, arg3);
    func_00108950(arg0 + 0x10, &sp40, arg2, arg3);
    func_00108950(arg0 + 0x20, &sp40, arg2, arg3);
    func_00108950(arg0 + 0x30, &sp40, arg2, arg3);
    return 0;
}

s32 func_001091B0(void *arg0, void *arg1, void *arg2) {
    *(s16 *)((u8 *)arg0 + 2) = 0x11;
    *(s16 *)arg0 = 4;
    *(s64 *)((u8 *)arg0 + 8) = 0x4141;
    *(s32 *)((u8 *)arg0 + 4) = 0;
    func_002086D0(arg0, 0x48 | ((s64)0x80 << 32));
    ((u8 *)arg0)[0x10] = ((u8 *)arg1)[0];
    ((u8 *)arg0)[0x11] = ((u8 *)arg1)[1];
    ((u8 *)arg0)[0x12] = ((u8 *)arg1)[2];
    ((u8 *)arg0)[0x13] = ((u8 *)arg1)[3];
    ((u8 *)arg0)[0x20] = ((u8 *)arg2)[0];
    ((u8 *)arg0)[0x21] = ((u8 *)arg2)[1];
    ((u8 *)arg0)[0x22] = ((u8 *)arg2)[2];
    ((u8 *)arg0)[0x23] = ((u8 *)arg2)[3];
    *(s32 *)((u8 *)arg0 + 0x24) = 0x3F800000;
    *(s32 *)((u8 *)arg0 + 0x14) = 0x3F800000;
    ((u8 *)arg0)[0x1F] = 0;
    ((u8 *)arg0)[0x2F] = 0;
    return 0;
}

typedef struct Packet_00109270 {
    s16 count;
    u16 flags;
    s32 reserved;
    s64 registers;
} Packet_00109270;

s32 func_00109270(void *arg0) {
    Packet_00109270 *packet = arg0;

    packet->flags = 0x34;
    packet->count = 0xC;
    packet->registers = 0x421421421421LL;
    packet->reserved = 0;
    packet->flags |= 0x800;
    func_002086D0(arg0, 0x8000000048LL);
    return 0;
}

s32 func_001092E0(void *arg0, s32 arg1) {
    *(s16 *)((u8 *)arg0 + 2) = 0x14;
    *(s16 *)arg0 = 8;
    *(s64 *)((u8 *)arg0 + 8) = 0x41414141;
    *(s32 *)((u8 *)arg0 + 4) = 0;
    if (arg1 == 0) {
        func_002086D0(arg0, 0x48 | ((s64)0x80 << 32));
    } else {
        func_002086D0(arg0, 0x42 | ((s64)0x80 << 32));
    }
    *(s32 *)((u8 *)arg0 + 0x44) = 0;
    *(s32 *)((u8 *)arg0 + 0x34) = 0;
    *(s32 *)((u8 *)arg0 + 0x24) = 0;
    *(s32 *)((u8 *)arg0 + 0x14) = 0;
    *(s8 *)((u8 *)arg0 + 0x1F) = 0;
    *(s8 *)((u8 *)arg0 + 0x2F) = 0;
    *(s8 *)((u8 *)arg0 + 0x3F) = 0;
    *(s8 *)((u8 *)arg0 + 0x4F) = 0;
    return 0;
}

typedef struct {
    u64 command : 32;
    u64 rgb : 24;
    u64 alpha : 8;
} Color_00109380;

typedef struct {
    Color_00109380 color;
    u64 texture;
    u64 position;
} TexturedVertex_00109380;

typedef struct {
    Color_00109380 color;
    u64 position;
} Vertex_00109380;

typedef struct {
    u8 header[0x20];
    TexturedVertex_00109380 vertices[4];
} TexturedPacket_00109380;

typedef struct {
    u8 header[0x18];
    Vertex_00109380 vertices[4];
} Packet_00109380;

s32 func_00109380(void *arg0, s32 arg1) {
    if (arg1 == 0) {
        TexturedPacket_00109380 *packet = (TexturedPacket_00109380 *)arg0;

        packet->vertices[0].color.rgb =
            packet->vertices[1].color.rgb =
            packet->vertices[2].color.rgb =
            packet->vertices[3].color.rgb = 0xFFFFFF;
    } else {
        Packet_00109380 *packet = (Packet_00109380 *)arg0;

        packet->vertices[0].color.rgb =
            packet->vertices[1].color.rgb =
            packet->vertices[2].color.rgb =
            packet->vertices[3].color.rgb = 0xFFFFFF;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_002", func_001094F0);

INCLUDE_ASM("asm/nonmatchings/main_002", func_001095D0);

INCLUDE_ASM("asm/nonmatchings/main_002", func_00109830);

typedef struct Vec4_001098E0 {
    f32 x, y, z, w;
} Vec4_001098E0;

void func_001098E0(void *out, f32 *offset, f32 *point, f32 *a, f32 *b) {
    Vec4_001098E0 result;
    f32 zero;
    f32 dx, dy, dz;
    f32 lengthSquared;
    f32 startX, startY, startZ;
    f32 pointY;
    f32 t;

    result.x = 0.0f;
    startX = a[0] + offset[0];
    startY = a[1];
    startZ = a[2] + offset[2];
    pointY = point[1];
    dx = (b[0] + offset[0]) - startX;
    dy = b[1] - startY;
    dz = (b[2] + offset[2]) - startZ;
    lengthSquared = dx * dx + dy * dy + dz * dz;
    zero = 0.0f;
    if (lengthSquared == 0.0f) {
        *(Vec4_001098E0 *)out = result;
    } else {
        t = (dx * (zero - startX) + dy * (pointY - startY) +
             dz * (zero - startZ)) / lengthSquared;
        result.x = startX + dx * t;
        result.y = 0.0f;
        result.z = startZ + dz * t;
        *(Vec4_001098E0 *)out = result;
    }
}

typedef struct Vec4_001099E0 {
    f32 x, y, z, w;
} Vec4_001099E0;

void func_001099E0(void *arg0, void *arg1, void *arg2, f32 fparg0) {
    Vec4_001099E0 delta;

    delta.x = (((f32 *)arg1)[0] - (((f32 *)arg2)[0] + ((f32 *)arg2)[4])) / fparg0;
    delta.z = (((f32 *)arg1)[2] - (((f32 *)arg2)[2] + ((f32 *)arg2)[6])) / fparg0;
    delta.y = (((f32 *)arg1)[1] - (((f32 *)arg2)[1] + ((f32 *)arg2)[5])) / fparg0;
    delta.w = 0.0f;
    *(Vec4_001099E0 *)arg0 = delta;
}

s32 func_00109A70(void *arg0, void *arg1) {
    ((f32 *)arg0)[0] = ((f32 *)arg1)[0];
    ((f32 *)arg0)[1] = ((f32 *)arg1)[1];
    ((f32 *)arg0)[2] = ((f32 *)arg1)[2];
    return 0;
}

void func_00109A90(void) {
    if (D_0030FF40 == NULL || D_0030FF48 == 0) {
        return;
    }
    if (!(D_0030FF40[0] & 1)) {
        func_0010C8B0();
        func_0010C720(0xF005);
        if (!(D_0030FF40[0] & 0x20)) {
            func_0010C720(0xF002, 0xC1800);
            D_0030FF40[5] = D_0030FF40[0x60];
            D_0030FF40[0] |= 0x20;
        }
        func_0010C720(0x5F10, 0, 0x5010);
        func_0010C720(0x5F10, 1, 0x9F810);
        func_0010C720(0x5F10, 2, 0x199810);
        func_0010C720(0x5F10, 3, 0x1CB810);
        func_0010C720(0x5F10, 4, 0x1FD810);
        func_0010C720(0x5F10, 5, 0x8F810);
        func_0010C720(0x5F10, 6, 0x9F810);
        func_0010C720(0x5F10, 7, 0xAF810);
        func_0010C720(0x5F10, 8, 0xBF810);
        func_0010C720(0x5F10, 9, 0xD7810);
        func_0010C720(0x5F10, 0xA, 0xEF810);
        func_0010C720(0x5F10, 0xB, 0x107810);
        func_0010C720(0x5F12, 0x150000, 0x38000);
        func_0010A8B0();
        func_0010B330();
        func_0010B360();
        D_0030FF40[0] |= 1;
        D_0030FF40[1] |= 0xE;
        D_0030FF40[0xA9B] = 0;
    }
    D_0030FF40[0] |= 0x80;
}

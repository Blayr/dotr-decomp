#include "common.h"

/* Converts a rotation in degrees (x, y, z) into the game's angle units into `out`. */
void OBJ_ROT(f32 x, f32 y, f32 z, s32 *out) {
    extern s32 func_001A22C0(f32);

    out[0] = func_001A22C0(x);
    out[1] = func_001A22C0(y);
    out[2] = func_001A22C0(z);
}

/* Converts a float vector into integers. */
void OBJ_I_V_IN(s32 *dst, f32 *src) {
    extern s32 func_001A22C0(f32);

    dst[0] = func_001A22C0(src[0]);
    dst[1] = func_001A22C0(src[1]);
    dst[2] = func_001A22C0(src[2]);
}

/* dst *= src (3 floats, one by one). */
void OBJ_VE_SCL_KAKE(void *dstVec, void *srcVec) {
    f32 *dst = dstVec;
    f32 *src = srcVec;

    dst[0] *= src[0];
    dst[1] *= src[1];
    dst[2] *= src[2];
}

/* Multiplies four vectors by `srcVec`, one by one. */
void OBJ_VE_SCL_KAKE_4(void *dstVecs, void *srcVec) {
    f32 *matrix = (f32 *)dstVecs;
    f32 *scale = (f32 *)srcVec;

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

/* Adds `src` to four vectors. */
void POS_POS_4(f32 *dst, f32 *src) {
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

/* Adds `amount` to axis `axis` (0 x, 1 y, 2 z) of four vectors. */
s32 XYZ_POS_4(void *vecs, s64 axis, f32 amount) {
    f32 (*matrix)[4] = (f32 (*)[4])vecs;

    if (axis == 0) {
        matrix[0][0] += amount;
        matrix[1][0] += amount;
        matrix[2][0] += amount;
        matrix[3][0] += amount;
    } else if ((s16)axis == 1) {
        matrix[0][1] += amount;
        matrix[1][1] += amount;
        matrix[2][1] += amount;
        matrix[3][1] += amount;
    } else {
        matrix[0][2] += amount;
        matrix[1][2] += amount;
        matrix[2][2] += amount;
        matrix[3][2] += amount;
    }
    return 0;
}

/* Copies a vector a -> b, or b -> a when `reverse`. */
s32 POINT_IN_VECTOR_(void *a, void *b, s32 reverse) {
    if (reverse == 0) {
        ((f32 *)a)[0] = ((f32 *)b)[0];
        ((f32 *)a)[1] = ((f32 *)b)[1];
        ((f32 *)a)[2] = ((f32 *)b)[2];
    } else {
        ((f32 *)b)[0] = ((f32 *)a)[0];
        ((f32 *)b)[1] = ((f32 *)a)[1];
        ((f32 *)b)[2] = ((f32 *)a)[2];
    }
    return 0;
}


/* Shrinks a scale value by one step. */
static inline void reduce_00107180(f32 *value) {
    *value -= 0.18f;
    if (*value < 0.0f) {
        *value = 0.0f;
    }
}

/* Shrinks unit `id`'s model by one step (when `on`). */
s32 MODEL_OFF(s32 id, s32 arg1, s32 arg2, s32 on) {
    f32 values[3];

    if ((SzEffect_IsModelStandby2(id) != 0) && (on != 0)) {
        SzEffect_GetModelScale2(id, values);
        reduce_00107180(values);
        reduce_00107180(&values[1]);
        reduce_00107180(&values[2]);
        SzEffect_SetModelScale2(id, values);
    }
    return 0;
}

/* Fades unit `id`'s card out by one step; 1 once it is gone. */
s32 CARD_OFF(s32 id) {
    u8 data[4];
    u8 alpha;

    if (SzEffect_IsCardStandby2(id) != 0) {
        SzEffect_GetCardRgba2(id, data);
        alpha = data[3];
        if (alpha > 0x14) {
            data[3] = alpha - 0x13;
        } else {
            data[3] = 0;
        }
        SzEffect_SetCardRgba2(id, (s32) data);
        if (data[3] == 0) {
            return 1;
        }
    }
    return 0;
}

/* Gives unit `id`'s model its full size again (when `on`). */
s32 MODEL_ON(s32 id, s32 arg1, s32 on) {
    f32 scale[3];

    if ((SzEffect_IsModelStandby2(id) != 0) && (on != 0)) {
        scale[0] = 1.0f;
        scale[1] = 1.0f;
        scale[2] = 1.0f;
        SzEffect_SetModelScale2(id, scale);
    }
    return 0;
}


/* Grows a scale value by `amount`, up to 1. */
static inline void add_clamped_00107370(f32 *value, f32 amount) {
    *value += amount;
    if (!(*value <= 1.0f)) {
        *value = 1.0f;
    }
}

/* Grows unit `id`'s model by `step`, up to full size. */
s32 MODEL_SCL_ON_1(s32 id, f32 step) {
    f32 color[3];

    if (SzEffect_IsModelStandby2(id) != 0) {
        SzEffect_GetModelScale2(id, color);
        add_clamped_00107370(&color[0], step);
        add_clamped_00107370(&color[1], step);
        add_clamped_00107370(&color[2], step);
        SzEffect_SetModelScale2(id, color);
    }
    return 0;
}


/* Shrinks a scale value by `amount`. */
static inline void subtract_00107450(f32 *value, f32 amount) {
    *value -= amount;
    if (*value < 0.0f) {
        *value = 0.0f;
    }
}

/* Shrinks unit `id`'s model by `step`. */
s32 MODEL_SCL_OFF_1(s32 id, f32 step) {
    f32 values[3];

    if (SzEffect_IsModelStandby2(id) != 0) {
        SzEffect_GetModelScale2(id, values);
        subtract_00107450(&values[0], step);
        subtract_00107450(&values[1], step);
        subtract_00107450(&values[2], step);
        SzEffect_SetModelScale2(id, values);
    }
    return 0;
}

/* Grows a scale value by `amount`, up to its limit. */
static inline void add_limited_00107510(f32 *value, f32 amount) {
    *value += amount;
    if (*value > 0.1) {
        *value = 0.1f;
    }
}

/* Grows unit `id`'s card by `step`. */
s32 CARD_SCL_ON_1(s32 id, f32 step) {
    f32 values[3];

    if (SzEffect_IsCardStandby2(id) != 0) {
        SzEffect_SetCardScale2(id, (s32)values);
        add_limited_00107510(&values[0], step);
        add_limited_00107510(&values[1], step);
        add_limited_00107510(&values[2], step);
        SzEffect_SetCardScale2(id, (s32)values);
    }
    return 0;
}

/* Fades unit `id`'s card in by `step`; 1 once it is fully shown. */
s32 CARD_ON(s32 id, s32 step) {
    u8 color[4];

    if (SzEffect_IsCardStandby2(id) != 0) {
        SzEffect_GetCardRgba2(id, color);
        color[3] += step;
        if (color[3] >= 0x80) {
            color[3] = 0x80;
        }
        SzEffect_SetCardRgba2(id, (s32) color);
        if (color[3] >= 0x80) {
            return 1;
        }
    }
    return 0;
}

/* Sets an RGB colour. */
s32 OBJ_RGB_IN(void *rgb, s8 r, s8 g, s8 b) {
    ((s8 *)rgb)[0] = r;
    ((s8 *)rgb)[1] = g;
    ((s8 *)rgb)[2] = b;
    return 0;
}

/* Copies an RGBA colour. */
s32 OBJ_GsRGB_RGB_IN(u8 *dstRgba, u8 *srcRgba) {
    dstRgba[0] = srcRgba[0];
    dstRgba[1] = srcRgba[1];
    dstRgba[2] = srcRgba[2];
    dstRgba[3] = srcRgba[3];
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

/* Copies an RGBA colour into a GS colour word. */
void OBJ_GsRGB_RGB_IN2(void *dstColor, void *srcColor) {
    PackedPair_00107740 temp;
    u8 *src = srcColor;

    temp.packed.bytes[0] = src[0];
    temp.packed.bytes[1] = src[1];
    temp.packed.bytes[2] = src[2];
    temp.packed.bytes[3] = src[3];
    temp.packed.value = 1.0f;
    *(FloatPair_00107740 *)dstColor = temp.pair;
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

/* An RGBAQ word for a colour. */
static inline Rgbaq_00107790 rgbaq_00107790(u8 *color) {
    Rgbaq_00107790 c;

    c.r = color[0];
    c.g = color[1];
    c.b = color[2];
    c.a = color[3];
    c.q = 1.0f;
    return c;
}

/* Sets the colour of a textured quad's corners: all (`which` 0), the top two (1) or the bottom two (2). */
s32 GT4_IN_RGBA(void *prim, u8 *color, s32 which) {
    Packet_00107790 *packet = prim;

    if (which == 0) {
        packet->v[0].rgbaq = rgbaq_00107790(color);
        packet->v[1].rgbaq = rgbaq_00107790(color);
        packet->v[2].rgbaq = rgbaq_00107790(color);
        packet->v[3].rgbaq = rgbaq_00107790(color);
    } else if (which == 1) {
        packet->v[0].rgbaq = rgbaq_00107790(color);
        packet->v[1].rgbaq = rgbaq_00107790(color);
    } else if (which == 2) {
        packet->v[2].rgbaq = rgbaq_00107790(color);
        packet->v[3].rgbaq = rgbaq_00107790(color);
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

/* An RGBAQ word for a colour. */
static inline Rgbaq_00107990 rgbaq_00107990(u8 *color) {
    Rgbaq_00107990 c;

    c.r = color[0];
    c.g = color[1];
    c.b = color[2];
    c.a = color[3];
    c.q = 1.0f;
    return c;
}

/* Sets the colour of a flat quad's corners: all (`which` 0), the top two (1) or the bottom two (2). */
s32 G4_IN_RGBA(void *prim, u8 *color, s32 which) {
    Packet_00107990 *packet = prim;

    if (which == 0) {
        packet->v[0].rgbaq = rgbaq_00107990(color);
        packet->v[1].rgbaq = rgbaq_00107990(color);
        packet->v[2].rgbaq = rgbaq_00107990(color);
        packet->v[3].rgbaq = rgbaq_00107990(color);
    } else if (which == 1) {
        packet->v[0].rgbaq = rgbaq_00107990(color);
        packet->v[1].rgbaq = rgbaq_00107990(color);
    } else if (which == 2) {
        packet->v[2].rgbaq = rgbaq_00107990(color);
        packet->v[3].rgbaq = rgbaq_00107990(color);
    }
    return 0;
}

/* The x and z distances from a card (its position plus offset) to a point. */
void CARD_X_Z_IN_(f32 *outX, f32 *outZ, void *card, void *point) {
    f32 dx;
    f32 dz;

    *outX = ((f32 *)point)[0] - (((f32 *)card)[0] + ((f32 *)card)[4]);
    *outZ = ((f32 *)point)[2] - (((f32 *)card)[2] + ((f32 *)card)[6]);
    dx = *outX;
    *outX = func_001A6C60(dx * dx);
    dz = *outZ;
    *outZ = func_001A6C60(dz * dz);
}

/* Fills a sine table for 0..90 degrees. */
void SIN_IN_PSYS(f32 *table) {
    s16 i;
    f32 *dst;

    dst = table;
    for (i = 0; i < 91; i++) {
        *dst = func_001A6A88((3.1415927f * (f32)i) / 180.0f);
        dst++;
    }
}

/* Fills `count` sine and cosine entries, `step` degrees apart (and one step ahead), for a particle system. */
void SIN_IN_PSYS2(void *table, s32 step, s32 count) {
    s16 i;
    s32 angle;
    f32 *p;
    f32 radians;

    p = table;
    i = 0;
    angle = 0;
    while (i < count) {
        radians = (3.1415927f * (f32)angle) / 180.0f;
        p[0] = func_001A6A88(radians);
        p[20] = func_001A6898(radians);
        radians = (3.1415927f * (f32)(step + angle)) / 180.0f;
        p[40] = func_001A6A88(radians);
        p[60] = func_001A6898(radians);
        angle += step;
        p++;
        i++;
    }
}

/* Moves two x/z pairs of `dst` by (src - base). */
s32 V0IN_V1_V2_XZ(void *dstVec, void *srcVec, void *baseIn) {
    f32 *dst = dstVec;
    f32 *src = srcVec;
    f32 *base = baseIn;

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

/* Stores two angles and a height. */
s32 OBJ_RR2H_IN(f32 angle0, f32 angle1, f32 height, void *out) {
    Fields_00107E40 *fields = out;

    fields->first = func_001A22C0(angle0);
    fields->second = func_001A22C0(angle1);
    fields->value = height;
    return 0;
}

/* Stores two angles and a height in a particle system. */
s32 PSYS_RR2H_IN(void *psys, f32 angle0, f32 angle1, f32 height) {
    *(f32 *)((u8 *)psys + 0x449C) = angle0;
    *(f32 *)((u8 *)psys + 0x44A0) = angle1;
    *(f32 *)((u8 *)psys + 0x44A4) = height;
    return 0;
}

/* Sets a colour from the built-in colour table, entry `index` of `kind`. */
s32 OBJ_GsRGB_RGB_IN_DATA(u8 *out, s32 kind, s16 index) {
    if (index == 0) {
        out[0] = 0xFF;
        out[1] = 0xFF;
        out[2] = 0xFF;
    } else if (index == 1) {
        out[0] = 0xFF;
        out[1] = 0;
        out[2] = 0;
    } else if (index == 2) {
        out[0] = 0;
        out[1] = 0xFF;
        out[2] = 0;
    } else if (index == 3) {
        out[0] = 0;
        out[1] = 0;
        out[2] = 0xFF;
    } else if (index == 4) {
        out[0] = 0xFF;
        out[1] = 0xFF;
        out[2] = 0;
    } else if (index == 5) {
        out[0] = 0xFF;
        out[1] = 0;
        out[2] = 0xFF;
    } else if (index == 6) {
        out[0] = 0;
        out[1] = 0xFF;
        out[2] = 0xFF;
    } else if (index == 7) {
        out[0] = 0xFF;
        out[1] = 0x80;
        out[2] = 0xFF;
    } else if (index == 8) {
        out[0] = 0x80;
        out[1] = 0;
        out[2] = 0xFF;
    } else if (index == 9) {
        out[0] = 0xFF;
        out[1] = 0x80;
        out[2] = 0;
    } else {
        out[0] = 0xFF;
        out[1] = 0xFF;
        out[2] = 0xFF;
    }
    return 0;
}

/* The sine (`cosine` 0) or cosine of `degrees` from a 0..90 degree sine table. */
f32 SIN_COS_INRAD(s32 tableIn, s32 degrees, s32 cosine) {
    f32 result;
    f32 *table = (f32 *)tableIn;

    if (cosine == 0) {
        if ((s16)degrees >= 360) {
            degrees = (s16)(degrees % 360);
        }
        if ((s16)degrees <= -360) {
            degrees = (s16)(degrees % 360);
        }
        if ((s16)degrees < 0) {
            degrees = (s16)(degrees + 360);
        }

        if ((s16)degrees < 90) {
            table += (s16)degrees;
            result = *table;
        } else if ((s16)degrees < 180) {
            table += 90 - (s16)(degrees - 90);
            result = *table;
        } else if ((s16)degrees < 270) {
            table += (s16)(degrees - 180);
            result = *table;
            result *= -1.0f;
        } else {
            table += 90 - (s16)(degrees - 270);
            result = *table;
            result *= -1.0f;
        }
    } else {
        if ((s16)degrees >= 360) {
            degrees = (s16)(degrees % 360);
        }
        if ((s16)degrees <= -360) {
            degrees = (s16)(degrees % 360);
        }
        if ((s16)degrees < 0) {
            degrees = (s16)(degrees + 360);
        }

        if ((s16)degrees < 90) {
            table += 90 - (s16)degrees;
            result = *table;
        } else if ((s16)degrees < 180) {
            table += (s16)(degrees - 90);
            result = *table;
            result *= -1.0f;
        } else if ((s16)degrees < 270) {
            table += 90 - (s16)(degrees - 180);
            result = *table;
            result *= -1.0f;
        } else {
            table += (s16)(degrees - 270);
            result = *table;
        }
    }

    return result;
}

/* The angle in degrees (0..359) of the direction (x, y). */
s32 tanD_360_(s64 x, s64 y) {
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

/* A texture coordinate at the edge of a panel. */
static inline s32 edge_uv_00108500(s32 extent, s32 origin) {
    return (origin + extent) << 4;
}

/* Sets a panel's texture coordinates for frame `frame`. */
void POLPAN_UVIN_(void *prim, void *rectIn, s32 frame) {
    Rect_00108500 *rect = rectIn;

    if (frame == 0) {
        ((UV_00108500 *)((u8 *)prim + 0x18))->u = (rect->x << 4);
        ((UV_00108500 *)((u8 *)prim + 0x18))->v = (rect->y << 4);
        ((UV_00108500 *)((u8 *)prim + 0x30))->u = edge_uv_00108500(rect->width, rect->x);
        ((UV_00108500 *)((u8 *)prim + 0x30))->v = (rect->y << 4);
        ((UV_00108500 *)((u8 *)prim + 0x48))->u = (rect->x << 4);
        ((UV_00108500 *)((u8 *)prim + 0x48))->v = edge_uv_00108500(rect->height, rect->y);
        ((UV_00108500 *)((u8 *)prim + 0x60))->u = edge_uv_00108500(rect->width, rect->x);
        ((UV_00108500 *)((u8 *)prim + 0x60))->v = edge_uv_00108500(rect->height, rect->y);
    } else if (frame == 1) {
        ((UV_00108500 *)((u8 *)prim + 0x18))->u = (rect->x << 4);
        ((UV_00108500 *)((u8 *)prim + 0x18))->v = edge_uv_00108500(rect->height, rect->y);
        ((UV_00108500 *)((u8 *)prim + 0x30))->u = (rect->x << 4);
        ((UV_00108500 *)((u8 *)prim + 0x30))->v = (rect->y << 4);
        ((UV_00108500 *)((u8 *)prim + 0x48))->u = edge_uv_00108500(rect->width, rect->x);
        ((UV_00108500 *)((u8 *)prim + 0x48))->v = edge_uv_00108500(rect->height, rect->y);
        ((UV_00108500 *)((u8 *)prim + 0x60))->u = edge_uv_00108500(rect->width, rect->x);
        ((UV_00108500 *)((u8 *)prim + 0x60))->v = (rect->y << 4);
    } else if (frame == 10) {
        ((UV_00108500 *)((u8 *)prim + 0x48))->u = (rect->x << 4);
        ((UV_00108500 *)((u8 *)prim + 0x48))->v = (rect->y << 4);
        ((UV_00108500 *)((u8 *)prim + 0x18))->u = edge_uv_00108500(rect->width, rect->x);
        ((UV_00108500 *)((u8 *)prim + 0x18))->v = (rect->y << 4);
        ((UV_00108500 *)((u8 *)prim + 0x60))->u = (rect->x << 4);
        ((UV_00108500 *)((u8 *)prim + 0x60))->v = edge_uv_00108500(rect->height, rect->y);
        ((UV_00108500 *)((u8 *)prim + 0x30))->u = edge_uv_00108500(rect->width, rect->x);
        ((UV_00108500 *)((u8 *)prim + 0x30))->v = edge_uv_00108500(rect->height, rect->y);
    } else {
        ((UV_00108500 *)((u8 *)prim + 0x30))->u = (rect->x << 4);
        ((UV_00108500 *)((u8 *)prim + 0x30))->v = (rect->y << 4);
        ((UV_00108500 *)((u8 *)prim + 0x18))->u = edge_uv_00108500(rect->width, rect->x);
        ((UV_00108500 *)((u8 *)prim + 0x18))->v = (rect->y << 4);
        ((UV_00108500 *)((u8 *)prim + 0x60))->u = (rect->x << 4);
        ((UV_00108500 *)((u8 *)prim + 0x60))->v = edge_uv_00108500(rect->height, rect->y);
        ((UV_00108500 *)((u8 *)prim + 0x48))->u = edge_uv_00108500(rect->width, rect->x);
        ((UV_00108500 *)((u8 *)prim + 0x48))->v = edge_uv_00108500(rect->height, rect->y);
    }
}

struct DotrPaintVector {
    float x, y, z, w;
};
union DotrMatrixAngles {
    struct DotrPaintVector f;
    int i[4];
};
extern float func_00108030_b(int unit, short angle, int cosine);
#define S_108950(a) func_00108030_b(unit, (a), 0)
#define C_108950(a) func_00108030_b(unit, (a), 1)

/* Transforms one vector by the rotation of `axis`. */
int MATRIX_XYZ_ININ33(void *row_v, void *v_v, int axis, int unit)
{
    struct DotrPaintVector * row = row_v;
    struct DotrPaintVector * v = v_v;
    union DotrMatrixAngles rot = *(union DotrMatrixAngles *)v;
    struct DotrPaintVector out;
    int a;

    if (axis == 0) {
        a = rot.i[1];
        out.x = row->x * C_108950(a) + row->z * -S_108950(a);
        out.y = row->y;
        out.z = row->x * S_108950(a) + row->z * C_108950(a);
        *row = out;
    }
    if (axis == 1) {
        out.x = row->x;
        out.y = row->y * C_108950(rot.i[0]) + row->z * S_108950(rot.i[0]);
        out.z = row->y * -S_108950(rot.i[0]) + row->z * C_108950(rot.i[0]);
        *row = out;
    }
    if (axis == 2) {
        a = rot.i[2];
        out.x = row->x * C_108950(a) + row->y * S_108950(a);
        out.y = row->x * -S_108950(a) + row->y * C_108950(a);
        out.z = row->z;
        *row = out;
    }
    return 0;
}
#undef S_108950
#undef C_108950

typedef struct Vec4_00108BE0 {
    f32 x, y, z, w;
} Vec4_00108BE0;

/* Rotates `srcVec` around axis `axis` (0 y, 1 x, 2 z) by the angle with cosine `c` and sine `s` into `outVec`. */
void RAD_XYZ_IN(void *outVec, void *srcVec, s64 axis, f32 c, f32 s) {
    Vec4_00108BE0 input;
    Vec4_00108BE0 output;

    input = *(Vec4_00108BE0 *)srcVec;
    if (axis == 0) {
        output.x = c * input.x + -s * input.z;
        output.z = s * input.x + c * input.z;
        output.y = input.y;
    }
    if ((s16)axis == 1) {
        output.x = input.x;
        output.y = s * input.y + c * input.z;
        output.z = -c * input.y + s * input.z;
    }
    if ((s16)axis == 2) {
        output.x = c * input.x + s * input.y;
        output.y = -s * input.x + c * input.y;
        output.z = input.z;
    }
    *(Vec4_00108BE0 *)outVec = output;
}

typedef struct Vec4_00108CE0 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4_00108CE0;

/* Sets four corners of a w x h rectangle centred on 0. */
s32 PAINT_VECTOR_4TG_SET_IN(void *corners, f32 halfW, f32 halfH) {
    Vec4_00108CE0 *vertices = corners;
    f32 negative_x;
    f32 negative_y;

    negative_x = -halfW;
    vertices[0].x = negative_x;
    vertices[0].y = halfH;
    vertices[0].z = 0.0f;
    vertices[1].x = halfW;
    vertices[1].y = halfH;
    vertices[1].z = 0.0f;
    vertices[2].x = negative_x;
    negative_y = -halfH;
    vertices[2].y = negative_y;
    vertices[2].z = 0.0f;
    vertices[3].x = halfW;
    vertices[3].y = negative_y;
    vertices[3].z = 0.0f;
    return 0;
}

/* Sets four corners of a rectangle lying flat in x and z. */
s32 PAINT_VECTOR_4TG_SET_IN2(void *dst, f32 x, f32 z) {
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

/* Sets the four corners of board square (x, z) (`mode` picks the layout). */
s32 PAINT_VECTOR_4TG_SET_INMAP4(void *corners, s32 xIn, s32 z, s16 mode) {
    f32 x;
    f32 y;
    f32 *coords = corners;

    if (mode == 0) {
        x = (f32) -(s16) xIn;
        y = (f32) z;
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
    } else if (mode == 1) {
        x = (f32) xIn;
        y = (f32) z;
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
    } else if (mode == 2) {
        x = (f32) -(s16) xIn;
        coords[0] = x;
        y = (f32) -(s16) z;
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
    } else if (mode == 3) {
        x = (f32) xIn;
        coords[0] = x;
        y = (f32) -(s16) z;
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

/* Builds an object's matrix: world-to-screen times its scale, rotation and position. */
void S_I_P_IN(void *outMatrix, s32 scale, s32 rot, s32 pos) {
    extern void RhGeom_GetScaleRotXYZTransMatrix(void *, s32, s32, s32);
    Matrix_00108EF0 local;
    Matrix_00108EF0 world;

    RhView_GetWorldScreenMatrix(&world);
    RhGeom_GetScaleRotXYZTransMatrix(&local, scale, rot, pos);
    RhGeom_MulMatrix((s32) &world, &local);
    *(Matrix_00108EF0 *)outMatrix = world;
}

/* Projects a flat quad's `count` corners and sorts it into the draw list at its depth. */
s32 PAINT_PIRM_G4(s32 corners, s32 prim, s32 count, s32 ot) {
    f32 result[4];

    if (Ex3d_RotTransPersAuto(corners, 0x70000000, count, prim, result) != 0) {
        ExSortPrim(prim, ot, func_001A23B0(result[0]));
    }
    return 0;
}

/* Projects a textured quad's `count` corners and sorts it into the draw list at its depth. */
s32 PAINT_PIRM_GT4(s32 corners, s32 prim, s32 count, s32 ot) {
    f32 depth[4];

    if (Ex3d_RotTransPersAuto(corners, 0x70000000, count, prim, depth) != 0) {
        ExSortPrim(prim, ot, func_001A23B0(depth[0]));
    }
    return 0;
}

typedef struct Color_00109050 {
    u64 low : 32;
    u64 rgb : 24;
    u64 high : 8;
} Color_00109050;

/* Projects a white line's corners and sorts it into the draw list. */
s32 PAINT_PIRM_LG2(s32 corners, void *prim, s32 count, s32 ot) {
    f32 result[4];

    if (Ex3d_RotTransPersAuto(corners, 0x70000000, count, (s32)prim, result) != 0) {
        ((Color_00109050 *)((u8 *)prim + 0x18))->rgb = 0xFFFFFF;
        ((Color_00109050 *)((u8 *)prim + 0x28))->rgb = 0xFFFFFF;
        ExSortPrim((s32)prim, ot, 0);
    }
    return 0;
}

typedef struct Vec4_00109100 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4_00109100;


/* Transforms a matrix's four rows by the rotation of `axis`. */
s32 MATRIX_XYZ_ININ_4(u8 *matrix, void *vec, s32 axis, s32 unit) {
    Vec4_00109100 v = *(Vec4_00109100 *)vec;

    MATRIX_XYZ_ININ33(matrix, &v, axis, unit);
    MATRIX_XYZ_ININ33(matrix + 0x10, &v, axis, unit);
    MATRIX_XYZ_ININ33(matrix + 0x20, &v, axis, unit);
    MATRIX_XYZ_ININ33(matrix + 0x30, &v, axis, unit);
    return 0;
}

/* Sets up a two-colour line primitive from colours `c0` and `c1`. */
s32 PAINT__2G_SET_IN(void *prim, void *c0, void *c1) {
    *(s16 *)((u8 *)prim + 2) = 0x11;
    *(s16 *)prim = 4;
    *(s64 *)((u8 *)prim + 8) = 0x4141;
    *(s32 *)((u8 *)prim + 4) = 0;
    ExAssignAlpha(prim, 0x48 | ((s64)0x80 << 32));
    ((u8 *)prim)[0x10] = ((u8 *)c0)[0];
    ((u8 *)prim)[0x11] = ((u8 *)c0)[1];
    ((u8 *)prim)[0x12] = ((u8 *)c0)[2];
    ((u8 *)prim)[0x13] = ((u8 *)c0)[3];
    ((u8 *)prim)[0x20] = ((u8 *)c1)[0];
    ((u8 *)prim)[0x21] = ((u8 *)c1)[1];
    ((u8 *)prim)[0x22] = ((u8 *)c1)[2];
    ((u8 *)prim)[0x23] = ((u8 *)c1)[3];
    *(s32 *)((u8 *)prim + 0x24) = 0x3F800000;
    *(s32 *)((u8 *)prim + 0x14) = 0x3F800000;
    ((u8 *)prim)[0x1F] = 0;
    ((u8 *)prim)[0x2F] = 0;
    return 0;
}

typedef struct Packet_00109270 {
    s16 count;
    u16 flags;
    s32 reserved;
    s64 registers;
} Packet_00109270;

/* Sets up a textured quad primitive. */
s32 PAINT__GT4_SET_IN(void *prim) {
    Packet_00109270 *packet = prim;

    packet->flags = 0x34;
    packet->count = 0xC;
    packet->registers = 0x421421421421LL;
    packet->reserved = 0;
    packet->flags |= 0x800;
    ExAssignAlpha(prim, 0x8000000048LL);
    return 0;
}

/* Sets up a flat quad primitive, normal (`additive` 0) or additive blend. */
s32 PAINT__G4_SET_IN(void *prim, s32 additive) {
    *(s16 *)((u8 *)prim + 2) = 0x14;
    *(s16 *)prim = 8;
    *(s64 *)((u8 *)prim + 8) = 0x41414141;
    *(s32 *)((u8 *)prim + 4) = 0;
    if (additive == 0) {
        ExAssignAlpha(prim, 0x48 | ((s64)0x80 << 32));
    } else {
        ExAssignAlpha(prim, 0x42 | ((s64)0x80 << 32));
    }
    *(s32 *)((u8 *)prim + 0x44) = 0;
    *(s32 *)((u8 *)prim + 0x34) = 0;
    *(s32 *)((u8 *)prim + 0x24) = 0;
    *(s32 *)((u8 *)prim + 0x14) = 0;
    *(s8 *)((u8 *)prim + 0x1F) = 0;
    *(s8 *)((u8 *)prim + 0x2F) = 0;
    *(s8 *)((u8 *)prim + 0x3F) = 0;
    *(s8 *)((u8 *)prim + 0x4F) = 0;
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

/* Sets a quad's four corner colours to white (`flat` picks the untextured layout). */
s32 GT4_Xyz_ZIN(void *prim, s32 flat) {
    if (flat == 0) {
        TexturedPacket_00109380 *packet = (TexturedPacket_00109380 *)prim;

        packet->vertices[0].color.rgb =
            packet->vertices[1].color.rgb =
            packet->vertices[2].color.rgb =
            packet->vertices[3].color.rgb = 0xFFFFFF;
    } else {
        Packet_00109380 *packet = (Packet_00109380 *)prim;

        packet->vertices[0].color.rgb =
            packet->vertices[1].color.rgb =
            packet->vertices[2].color.rgb =
            packet->vertices[3].color.rgb = 0xFFFFFF;
    }
    return 0;
}

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Xyzf_001094F0;

typedef struct {
    u64 color;
    Xyzf_001094F0 xyzf;
} Vertex_001094F0;

typedef struct {
    u8 header[0x10];
    Vertex_001094F0 v[4];
} Packet_001094F0;

/* Sets up a box of flat quads. */
s32 G4_BOX_IN__(void *box) {
    s32 h;
    s32 w;
    Packet_001094F0 *p = box;

    w = 320;
    h = 240;
    *(s32 *)((u8 *)box + 0x44) = 0;
    *(s32 *)((u8 *)box + 0x34) = 0;
    *(s32 *)((u8 *)box + 0x24) = 0;
    *(s32 *)((u8 *)box + 0x14) = 0;
    p->v[0].xyzf.x = (0x800 - w) << 4;
    p->v[0].xyzf.y = (0x800 - h) << 4;
    p->v[0].xyzf.z = 0xFFFFFF;
    p->v[0].xyzf.fog = 0;
    p->v[1].xyzf.x = (0x800 + w) << 4;
    p->v[1].xyzf.y = (0x800 - h) << 4;
    p->v[1].xyzf.z = 0xFFFFFF;
    p->v[1].xyzf.fog = 0;
    p->v[2].xyzf.x = (0x800 - w) << 4;
    p->v[2].xyzf.y = (0x800 + h) << 4;
    p->v[2].xyzf.z = 0xFFFFFF;
    p->v[2].xyzf.fog = 0;
    p->v[3].xyzf.x = (0x800 + w) << 4;
    p->v[3].xyzf.y = (0x800 + h) << 4;
    p->v[3].xyzf.z = 0xFFFFFF;
    p->v[3].xyzf.fog = 0;
    return 0;
}

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4_001095D0;

typedef struct {
    u64 color;
    u64 uv;
    Xyzf_001094F0 xyzf;
} Vertex_001095D0;

typedef struct {
    u8 header[0x10];
    Vertex_001095D0 v[4];
} Packet_001095D0;

/* Sets up a box of textured quads on the 2D map. */
s32 GT4_BOX_IN__2DMAP(void *box, void *rect, void *texture) {
    Vec4_001095D0 size;
    Vec4_001095D0 pos;
    s32 h;
    s32 w;
    u16 x0;
    u16 y0;
    u16 x1;
    u16 y1;
    Packet_001095D0 *p = box;

    size = *(Vec4_001095D0 *)rect;
    pos = *(Vec4_001095D0 *)texture;
    h = (s32)(size.y / 2.0f);
    w = (s32)(size.x / 2.0f);
    p->v[0].xyzf.x = x0 = ((0x800 - w) + (u16)(s32)pos.x) << 4;
    p->v[0].xyzf.y = y0 = ((0x800 - h) + (u16)(s32)pos.y) << 4;
    p->v[0].xyzf.z = 0xFFFFFF;
    p->v[0].xyzf.fog = 0;
    p->v[1].xyzf.x = x1 = ((0x800 + w) + (u16)(s32)pos.x) << 4;
    p->v[1].xyzf.y = y0;
    p->v[1].xyzf.z = 0xFFFFFF;
    p->v[1].xyzf.fog = 0;
    p->v[2].xyzf.x = x0;
    p->v[2].xyzf.y = y1 = ((0x800 + h) + (u16)(s32)pos.y) << 4;
    p->v[2].xyzf.z = 0xFFFFFF;
    p->v[2].xyzf.fog = 0;
    p->v[3].xyzf.x = x1;
    p->v[3].xyzf.y = y1;
    p->v[3].xyzf.z = 0xFFFFFF;
    p->v[3].xyzf.fog = 0;
    return 0;
}

/* out = a - b (3 floats). */
void R3D_RRR_XYZ(void *outVec, void *aIn, void *bIn) {
    Vec4_00109830 a;
    Vec4_00109830 b;

    a = *(Vec4_00109830 *)aIn;
    b = *(Vec4_00109830 *)bIn;
    a.x = a.x - b.x;
    ((Vec4_00109830 *)&a.y)->x = ((Vec4_00109830 *)&a.y)->x - b.y;
    ((Vec4_00109830 *)&a.z)->x = ((Vec4_00109830 *)&a.z)->x - b.z;
    *(Vec4_00109830 *)outVec = a;
}

typedef struct Vec4_001098E0 {
    f32 x, y, z, w;
} Vec4_001098E0;

/* Collision: where the point `point` + `offset` hits the line a..b, into `out`. */
void ATARI3(void *out, f32 *offset, f32 *point, f32 *a, f32 *b) {
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

/* The step that moves a card (position plus offset) to `target` in `frames` frames into `outVec`. */
void Card_V_IN(void *outVec, void *target, void *card, f32 frames) {
    Vec4_001099E0 delta;

    delta.x = (((f32 *)target)[0] - (((f32 *)card)[0] + ((f32 *)card)[4])) / frames;
    delta.z = (((f32 *)target)[2] - (((f32 *)card)[2] + ((f32 *)card)[6])) / frames;
    delta.y = (((f32 *)target)[1] - (((f32 *)card)[1] + ((f32 *)card)[5])) / frames;
    delta.w = 0.0f;
    *(Vec4_001099E0 *)outVec = delta;
}

/* Copies a vector. */
s32 VEC_POI_IN(void *dstVec, void *srcVec) {
    ((f32 *)dstVec)[0] = ((f32 *)srcVec)[0];
    ((f32 *)dstVec)[1] = ((f32 *)srcVec)[1];
    ((f32 *)dstVec)[2] = ((f32 *)srcVec)[2];
    return 0;
}

/* Starts the sound driver on the IOP. */
void SD_InitializeDevice(void) {
    if (g_SDValue == NULL || g_SDBuffer == 0) {
        return;
    }
    if (!(g_SDValue[0] & 1)) {
        SDRPC_Init();
        SDRPC_SendCommand(0xF005);
        if (!(g_SDValue[0] & 0x20)) {
            SDRPC_SendCommand(0xF002, 0xC1800);
            g_SDValue[5] = g_SDValue[0x60];
            g_SDValue[0] |= 0x20;
        }
        SDRPC_SendCommand(0x5F10, 0, 0x5010);
        SDRPC_SendCommand(0x5F10, 1, 0x9F810);
        SDRPC_SendCommand(0x5F10, 2, 0x199810);
        SDRPC_SendCommand(0x5F10, 3, 0x1CB810);
        SDRPC_SendCommand(0x5F10, 4, 0x1FD810);
        SDRPC_SendCommand(0x5F10, 5, 0x8F810);
        SDRPC_SendCommand(0x5F10, 6, 0x9F810);
        SDRPC_SendCommand(0x5F10, 7, 0xAF810);
        SDRPC_SendCommand(0x5F10, 8, 0xBF810);
        SDRPC_SendCommand(0x5F10, 9, 0xD7810);
        SDRPC_SendCommand(0x5F10, 0xA, 0xEF810);
        SDRPC_SendCommand(0x5F10, 0xB, 0x107810);
        SDRPC_SendCommand(0x5F12, 0x150000, 0x38000);
        SD_vInitializeFileHandler();
        SD_vInitSDThread();
        SD_vInitializeAutoDMA();
        g_SDValue[0] |= 1;
        g_SDValue[1] |= 0xE;
        g_SDValue[0xA9B] = 0;
    }
    g_SDValue[0] |= 0x80;
}

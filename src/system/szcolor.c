/* Colour conversions (SzColor_*). */

#include "common.h"
#include "campaign.h"

struct DotrColorBytes {
    unsigned char v[3];
};
union DotrColorChannels {
    struct DotrColorBytes bytes;
    struct {
        unsigned char r;
        unsigned char g;
        unsigned char b;
    } rgb;
};
extern struct DotrColorBytes D_0029B2B0;

/* Converts a colour from RGB (0..max) to hue, lightness, saturation. */
void SzColor_RGB2HLS(float *hls, int r, int g, int b, int max)
{
    

    union DotrColorChannels t;
    int hi;
    int lo;
    int i;
    int sum;
    int diff;
    int mn;
    int mx;

    t.bytes = D_0029B2B0;
    t.rgb.r = r;
    t.rgb.g = g;
    t.rgb.b = b;
    hi = 0;
    lo = 0;
    for (i = 1; i < 3; i++) {
        if (t.bytes.v[hi] < t.bytes.v[i]) {
            hi = i;
        }
        if (t.bytes.v[i] < t.bytes.v[lo]) {
            lo = i;
        }
    }
    mx = t.bytes.v[hi];
    mn = t.bytes.v[lo];
    sum = mx + mn;
    diff = mx - mn;
    hls[0] = 0.0f;
    hls[1] = (float)sum / (float)((unsigned char)max * 2);
    hls[2] = hls[1];
    if (diff != 0 && hls[1] > 0.0f && hls[1] < 1.0f) {
        if (hls[1] <= 0.5f) {
            hls[2] = (float)diff / (float)sum;
        } else {
            hls[2] = (float)diff / (float)((unsigned char)max * 2 - sum);
        }
        hls[0] = (float)(hi * 2) + (float)(t.bytes.v[(hi + 1) % 3] - t.bytes.v[(hi + 2) % 3]) / (float)diff;
        if (hls[0] < 0.0f) {
            hls[0] += 6.0f;
        }
    }
}

#define MIN_002413F0(a, b) ((a) < (b) ? (a) : (b))
#define MAX_002413F0(a, b) ((a) > (b) ? (a) : (b))

/* Converts a colour from hue, lightness, saturation to RGB. */
void SzColor_HLS2RGB(u8 *out, u8 value, f32 hue, f32 light, f32 sat) {
    f32 color[3];
    f32 frac;
    s32 max;
    s32 mid;
    s32 low;

    while (hue < 0.0f) {
        hue += 6.0f;
    }
    while (hue >= 6.0f) {
        hue -= 6.0f;
    }
    light = MIN_002413F0(MAX_002413F0(light, 0.0f), 1.0f);
    sat = MIN_002413F0(MAX_002413F0(sat, 0.0f), 1.0f);
    max = ((s32)(hue + 0.5f) % 6) >> 1;
    if (hue >= (f32)(max * 2)) {
        mid = (max + 1) % 3;
        low = (max + 2) % 3;
    } else {
        low = (max + 1) % 3;
        mid = (max + 2) % 3;
    }
    if (light <= 0.5f) {
        color[low] = value * (light * (1.0f - sat));
        color[max] = light * (value * 2) - color[low];
    } else {
        color[max] = value * (sat + light * (1.0f - sat));
        color[low] = light * (value * 2) - color[max];
    }
    frac = hue - (f32)(max * 2);
    color[mid] = color[low] + frac * (color[max] - color[low]);
    out[0] = MIN_002413F0((s32)(color[0] + 0.5f), 0xFF);
    out[1] = MIN_002413F0((s32)(color[1] + 0.5f), 0xFF);
    out[2] = MIN_002413F0((s32)(color[2] + 0.5f), 0xFF);
}

typedef struct Vec_00241840 {
    f32 x;
    f32 y;
    f32 z;
} Vec_00241840;

/* Turns an RGB colour into a sepia tone of the same lightness. */
void SzColor_RGB2SEP(u8 *color, s32 r, s32 g, s32 b, s32 unused, u8 max, f32 scale) {
    extern void SzColor_RGB2HLS(void *, s32, s32, s32, u8);
    Vec_00241840 vec;
    s32 flip;
    s32 isSix;
    s32 mode;
    u8 flags;

    flags = unused;
    if (flags & 8) {
        flip = 1;
    } else {
        flip = 0;
    }
    mode = flags & 7;
    if (mode == 6) {
        isSix = 1;
    } else {
        isSix = 0;
    }
    SzColor_RGB2HLS(&vec, r, g, b, max);
    if (mode < 7) {
        unused &= 7;
        if (flip) {
            unused = (u8)(((u8)unused + 3) % 6);
        }
        vec.x = (u32)unused;
    }
    if (isSix) {
        vec.z = 0.0f;
    } else {
        vec.z = vec.z * scale;
    }
    SzColor_HLS2RGB(color, max, vec.x, vec.y, vec.z);
    if (flip) {
        color[0] = max - color[0];
        color[1] = max - color[1];
        color[2] = max - color[2];
    }
    color[0] = (color[0] > 1) ? color[0] : 1;
    color[1] = (color[1] > 1) ? color[1] : 1;
    color[2] = (color[2] > 1) ? color[2] : 1;
}

/* Turns the `count` colours of palette `clut` into sepia tones. */
s32 SzColor_CLUT2SEP(s32 clut, s32 count, f32 scale) {
    u8 color[4];
    s32 entry;

    entry = clut & 0xFFFF;
    if (!(entry & 0xFFFF7FFF)) {
        return clut;
    }
    SzColor_RGB2SEP(color, entry & 0x1F, (entry >> 5) & 0x1F, (entry >> 0xA) & 0x1F, count, 0x1F, scale);
    return (clut & 0x8000) | (((color[2] & 0x1F) << 0xA) | ((color[0] & 0x1F) | ((color[1] & 0x1F) << 5)));
}

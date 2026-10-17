#include "common.h"

typedef struct {
    s16 x0, y0, x1, y1, x2, y2, x3, y3;
    u8 data[17];
    u8 flag;
    s16 depth;
    u16 index;
} Prim_002195E0;

typedef struct {
    s16 x0, y0, x1, y1;
    s16 kind;
} Rect_002195E0;

typedef struct {
    s16 u, v, width, height;
    u8 pad08[8];
    u16 texture;
    u8 pad12[2];
} Tex_002195E0;

extern Tex_002195E0 tex_uv_data[];
extern u16 window_tex_no[][0x100];

static inline s32 sprite_002195E0(s32 p, Prim_002195E0 *s, s16 dx, s16 dy) {
    extern s32 func_00217D70(s32, s16, s16, s16, s16, s16, s16, s16, s16,
                               u8, u8, u8, u8, u8, u16, u8, s16);
    Tex_002195E0 *e = &tex_uv_data[s->index];

    return func_00217D70(p, (s16)(s->x0 + dx), (s16)(s->y0 + dy),
                         (s16)(s->x1 + dx), (s16)(s->y1 + dy),
                         e->u, e->v, e->width, e->height,
                         s->data[0], s->data[1], s->data[2], s->data[3],
                         s->data[16], e->texture, s->flag, s->depth);
}

static inline s32 flipped_002195E0(s32 p, Prim_002195E0 *s, s16 dx, s16 dy) {
    extern s32 func_00217D70(s32, s16, s16, s16, s16, s16, s16, s16, s16,
                               u8, u8, u8, u8, u8, u16, u8, s16);
    Tex_002195E0 *e = &tex_uv_data[s->index];

    return func_00217D70(p, (s16)(s->x0 + dx), (s16)(s->y0 + dy),
                         (s16)(s->x1 + dx), (s16)(s->y1 + dy),
                         e->u, e->v - 1, e->width, e->height,
                         s->data[0], s->data[1], s->data[2], s->data[3],
                         s->data[16], e->texture, s->flag, s->depth);
}

static inline s32 quad_002195E0(s32 p, Prim_002195E0 *q, s16 x, s16 y) {
    extern s32 func_00218C10(s32, s16, s16, s16, s16, s16, s16, s16, s16,
                               u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u16,
                               s16);

    return func_00218C10(p,
        q->x0 + x, q->y0 + y,
        q->x1 + x, q->y1 + y,
        q->x2 + x, q->y2 + y,
        q->x3 + x, q->y3 + y,
        q->data[0], q->data[1], q->data[2], q->data[3],
        q->data[4], q->data[5], q->data[6], q->data[7],
        q->data[8], q->data[9], q->data[10], q->data[11],
        q->data[12], q->data[13], q->data[14], q->data[15],
        q->data[16], q->depth);
}

s32 Taku_Window_Set(s32 p, void *rect_arg, u16 style, u16 mode, u16 dx, u16 dy, u16 depth,
                    s32 unused, s16 alpha) {
    Rect_002195E0 *rect = rect_arg;
    s32 k;
    s16 w;
    Tex_002195E0 *e;
    s16 c;
    s32 hr;

    u8 b;
    s16 x0;
    s16 x1;
    s32 hg;
    s16 y1;
    s32 hb;
    u8 r;
    Prim_002195E0 q;
    s32 t;
    u8 g;
    s16 y0;
    s32 i;

    if (style == 0) {
        r = 0x60;
        g = 0;
        b = 0;
    } else if (style == 1) {
        g = 0x60;
        r = 0;
        b = g;
    } else if (style == 2) {
        r = 0;
        g = 0;
        b = 0;
    } else if (style == 3) {
        r = 0x80;
        g = r;
        b = r;
    } else if (style == 4) {
        r = 0xFF;
        g = r;
        b = r;
    } else if (style == 5) {
        r = 0;
        g = 0;
        b = 0x60;
    } else if (style == 10) {
        t = (*(s16 *)0x01ED006C * 0x60) >> 8;
        g = t;
        r = 0x60 - t;
        b = g;
    } else if (style == 11) {
        t = (*(s16 *)0x01ED006C * 0x60) >> 8;
        g = 0x60 - t;
        r = t;
        b = g;
    }

    switch (rect->kind) {
    case 0:
    case 1:
    case 2:
    case 6:
    case 8:
    case 9:
    case 10:
        if (style == 2) {
            x0 = rect->x0 + 2;
            y0 = rect->y0 + 2;
            x1 = rect->x1 - 2;
            y1 = rect->y1 - 2;
            q.data[0] = q.data[4] = r;
            q.data[1] = q.data[5] = g;
            q.data[2] = q.data[6] = b;
            q.data[3] = q.data[7] = alpha;
            q.data[8] = q.data[12] = r;
            q.data[9] = q.data[13] = g;
            q.data[10] = q.data[14] = b;
            q.data[11] = q.data[15] = alpha;
            q.x0 = x0;
            q.y0 = y0;
            q.x1 = x1;
            q.y1 = y0;
            q.x2 = x0;
            q.y2 = y1;
            q.x3 = x1;
            q.y3 = y1;
            q.data[16] = mode;
            q.flag = 1;
            q.depth = depth;
            p = quad_002195E0(p, &q, dx, dy);
        } else if (style != 3) {
            hr = r >> 1;
            hg = g >> 1;
            hb = b >> 1;
            for (k = 0; k < 2; k++) {
                if (k == 0) {
                    x0 = rect->x0 + 2;
                    y0 = rect->y0 + 2;
                    x1 = rect->x1 - 2;
                    y1 = (rect->y0 + rect->y1) >> 1;
                    q.data[0] = q.data[4] = hr;
                    q.data[1] = q.data[5] = hg;
                    q.data[2] = q.data[6] = hb;
                    q.data[3] = q.data[7] = alpha;
                    q.data[8] = q.data[12] = r;
                    q.data[9] = q.data[13] = g;
                    q.data[10] = q.data[14] = b;
                    q.data[11] = q.data[15] = alpha;
                } else {
                    x0 = rect->x0 + 2;
                    y0 = (rect->y0 + rect->y1) >> 1;
                    x1 = rect->x1 - 2;
                    y1 = rect->y1 - 2;
                    q.data[0] = q.data[4] = r;
                    q.data[1] = q.data[5] = g;
                    q.data[2] = q.data[6] = b;
                    q.data[3] = q.data[7] = alpha;
                    q.data[8] = q.data[12] = hr;
                    q.data[9] = q.data[13] = hg;
                    q.data[10] = q.data[14] = hb;
                    q.data[11] = q.data[15] = alpha;
                }
                q.x0 = x0;
                q.y0 = y0;
                q.x1 = x1;
                q.y1 = y0;
                q.x2 = x0;
                q.y2 = y1;
                q.x3 = x1;
                q.y3 = y1;
                q.data[16] = mode;
                q.flag = 1;
                q.depth = depth;
                p = quad_002195E0(p, &q, dx, dy);
            }
        }
        for (i = 0; i < 8; i++) {
            q.index = window_tex_no[rect->kind][i];
            q.data[0] = 0x80;
            q.data[1] = 0x80;
            q.data[2] = 0x80;
            q.data[3] = 0x80;
            q.data[16] = 1;
            q.flag = 1;
            q.depth = depth;
            if (i <= 3) {
                if (i == 0) {
                    x0 = rect->x0;
                    e = &tex_uv_data[q.index];
                    y0 = rect->y0;
                    x1 = x0 + e->width;
                    y1 = y0 + e->height;
                } else if (i == 1) {
                    y0 = rect->y0;
                    x1 = rect->x1;
                    e = &tex_uv_data[q.index];
                    x0 = x1 - e->width;
                    y1 = y0 + e->height;
                } else if (i == 2) {
                    x0 = rect->x0;
                    y1 = rect->y1;
                    e = &tex_uv_data[q.index];
                    x1 = x0 + e->width;
                    y0 = y1 - e->height;
                } else {
                    x1 = rect->x1;
                    y1 = rect->y1;
                    e = &tex_uv_data[q.index];
                    x0 = x1 - e->width;
                    y0 = y1 - e->height;
                }
            } else {
                c = window_tex_no[rect->kind][0];
                if (i == 4) {
                    e = &tex_uv_data[c];
                    w = e->width;
                    x0 = rect->x0 + w;
                    x1 = rect->x1 - w;
                    y0 = rect->y0;
                    y1 = y0 + e->height;
                } else if (i == 5) {
                    y1 = rect->y1;
                    e = &tex_uv_data[c];
                    w = e->width;
                    x0 = rect->x0 + w;
                    x1 = rect->x1 - w;
                    y0 = y1 - e->height;
                } else if (i == 6) {
                    x0 = rect->x0;
                    e = &tex_uv_data[c];
                    x1 = x0 + e->width;
                    y0 = rect->y0 + e->height;
                    y1 = rect->y1 - e->height;
                } else {
                    e = &tex_uv_data[c];
                    x1 = rect->x1;
                    x0 = x1 - e->width;
                    y0 = rect->y0 + e->height;
                    y1 = rect->y1 - e->height;
                }
            }
            q.x0 = x0;
            q.y0 = y0;
            q.x1 = x1;
            q.y1 = y1;
            p = sprite_002195E0(p, &q, dx, dy);
        }
        break;
    case 3:
        for (i = 0; i < 3; i++) {
            q.index = window_tex_no[rect->kind][i];
            q.data[0] = r;
            q.data[1] = g;
            q.data[2] = b;
            q.data[3] = alpha;
            q.data[16] = mode;
            q.flag = 1;
            q.depth = depth;
            if (i <= 1) {
                if (i == 0) {
                    x0 = rect->x0;
                    y0 = rect->y0;
                    e = &tex_uv_data[q.index];
                    x1 = x0 + e->width;
                    y1 = y0 + e->height;
                } else {
                    x1 = rect->x1;
                    y1 = rect->y1;
                    e = &tex_uv_data[q.index];
                    x0 = x1 - e->width;
                    y0 = y1 - e->height;
                }
            } else {
                w = tex_uv_data[(s16)window_tex_no[rect->kind][0]].width;
                x0 = rect->x0 + w;
                y0 = rect->y0;
                x1 = rect->x1 - w;
                y1 = rect->y1;
            }
            q.x0 = x0;
            q.y0 = y0;
            q.x1 = x1;
            q.y1 = y1;
            p = sprite_002195E0(p, &q, dx, dy);
        }
        break;
    case 4:
        hr = r >> 1;
        hg = g >> 1;
        hb = b >> 1;
        x0 = rect->x0 + 2;
        y0 = rect->y0 + 2;
        x1 = rect->x1 - 2;
        y1 = rect->y1;
        q.data[0] = q.data[4] = hr;
        q.data[1] = q.data[5] = hg;
        q.data[2] = q.data[6] = hb;
        q.data[3] = q.data[7] = alpha;
        q.data[8] = q.data[12] = hr;
        q.data[9] = q.data[13] = hg;
        q.data[10] = q.data[14] = hb;
        q.data[11] = q.data[15] = alpha;
        q.x0 = x0;
        q.y0 = y0;
        q.x1 = x1;
        q.y1 = y0;
        q.x2 = x0;
        q.y2 = y1;
        q.x3 = x1;
        q.y3 = y1;
        q.data[16] = 1;
        q.flag = 1;
        q.depth = depth;
        p = quad_002195E0(p, &q, dx, dy);
        for (i = 0; i < 4; i++) {
            q.index = window_tex_no[rect->kind][i];
            q.data[0] = 0x80;
            q.data[1] = 0x80;
            q.data[2] = 0x80;
            q.data[3] = 0x80;
            q.data[16] = 1;
            q.flag = 1;
            q.depth = depth;
            if (i <= 2) {
                if (i == 0) {
                    x0 = rect->x0;
                    y0 = rect->y0;
                    e = &tex_uv_data[q.index];
                    x1 = x0 + e->width;
                    y1 = y0 + e->height;
                } else if (i == 1) {
                    x1 = rect->x1;
                    y1 = rect->y1;
                    e = &tex_uv_data[q.index];
                    x0 = x1 - e->width;
                    y0 = y1 - e->height;
                } else {
                    w = tex_uv_data[(s16)window_tex_no[rect->kind][0]].width;
                    y0 = rect->y0;
                    x0 = rect->x0 + w;
                    x1 = rect->x1 - w;
                    y1 = rect->y1;
                }
                q.x0 = x0;
                q.y0 = y0;
                q.x1 = x1;
                q.y1 = y1;
                p = sprite_002195E0(p, &q, dx, dy);
            } else {
                x0 = (rect->x0 + rect->x1) >> 1;
                y0 = (rect->y0 + rect->y1) >> 1;
                q.x0 = x0 - 0x10;
                q.y0 = y0 - 0xE;
                q.x1 = x0 + 0x10;
                q.y1 = y0 - 0xE;
                q.x2 = x0 - 0x10;
                q.y2 = y0 + 2;
                q.x3 = x0 + 0x10;
                q.y3 = y0 + 2;
                p = (s32)func_00218020((void *)p, &q, dx, dy, 0);
            }
        }
        break;
    case 5:
        if (style == 2) {
            x0 = rect->x0 + 6;
            y0 = rect->y0 + 6;
            x1 = rect->x1 - 6;
            y1 = rect->y1;
            q.data[0] = q.data[4] = r;
            q.data[1] = q.data[5] = g;
            q.data[2] = q.data[6] = b;
            q.data[3] = q.data[7] = alpha;
            q.data[8] = q.data[12] = r;
            q.data[9] = q.data[13] = g;
            q.data[10] = q.data[14] = b;
            q.data[11] = q.data[15] = alpha;
            q.x0 = x0;
            q.y0 = y0;
            q.x1 = x1;
            q.y1 = y0;
            q.x2 = x0;
            q.y2 = y1;
            q.x3 = x1;
            q.y3 = y1;
            q.data[16] = mode;
            q.flag = 1;
            q.depth = depth;
            p = quad_002195E0(p, &q, dx, dy);
        }
        for (i = 0; i < 16; i++) {
            q.data[i] = 0x80;
        }
        for (i = 0; i < 5; i++) {
            q.data[16] = 1;
            q.flag = 1;
            q.depth = depth;
            if (style == 0) {
                if (i <= 1) {
                    if (i == 0) {
                        q.index = window_tex_no[rect->kind][2];
                        y0 = rect->y0;
                        x0 = rect->x0;
                        e = &tex_uv_data[q.index];
                        x1 = x0 + e->width;
                        y1 = y0 + e->height;
                    } else {
                        q.index = window_tex_no[rect->kind][3];
                        y0 = rect->y0;
                        x1 = rect->x1;
                        e = &tex_uv_data[q.index];
                        x0 = x1 - e->width;
                        y1 = y0 + e->height;
                    }
                } else {
                    c = window_tex_no[rect->kind][0];
                    if (i == 2) {
                        q.index = window_tex_no[rect->kind][5];
                        y0 = rect->y0;
                        e = &tex_uv_data[c];
                        w = e->width;
                        x0 = rect->x0 + w;
                        x1 = rect->x1 - w;
                        y1 = y0 + e->height;
                    } else if (i == 3) {
                        q.index = window_tex_no[rect->kind][6];
                        x0 = rect->x0;
                        e = &tex_uv_data[c];
                        x1 = x0 + e->width;
                        y0 = rect->y0 + e->height;
                        y1 = rect->y1;
                    } else {
                        q.index = window_tex_no[rect->kind][7];
                        e = &tex_uv_data[c];
                        x1 = rect->x1;
                        x0 = x1 - e->width;
                        y0 = rect->y0 + e->height;
                        y1 = rect->y1;
                    }
                }
                q.x0 = x0;
                q.y0 = y1;
                q.x1 = x1;
                q.y1 = y0;
                p = flipped_002195E0(p, &q, dx, dy);
            } else {
                if (i <= 1) {
                    if (i == 0) {
                        q.index = window_tex_no[rect->kind][0];
                        x0 = rect->x0;
                        y0 = rect->y0;
                        e = &tex_uv_data[q.index];
                        x1 = x0 + e->width;
                        y1 = y0 + e->height;
                    } else {
                        q.index = window_tex_no[rect->kind][1];
                        y0 = rect->y0;
                        x1 = rect->x1;
                        e = &tex_uv_data[q.index];
                        x0 = x1 - e->width;
                        y1 = y0 + e->height;
                    }
                } else {
                    c = window_tex_no[rect->kind][0];
                    if (i == 2) {
                        q.index = window_tex_no[rect->kind][4];
                        e = &tex_uv_data[c];
                        w = e->width;
                        x0 = rect->x0 + w;
                        x1 = rect->x1 - w;
                        y0 = rect->y0;
                        y1 = y0 + e->height;
                    } else if (i == 3) {
                        q.index = window_tex_no[rect->kind][6];
                        x0 = rect->x0;
                        e = &tex_uv_data[c];
                        x1 = x0 + e->width;
                        y0 = rect->y0 + e->height;
                        y1 = rect->y1;
                    } else {
                        q.index = window_tex_no[rect->kind][7];
                        e = &tex_uv_data[c];
                        x1 = rect->x1;
                        x0 = x1 - e->width;
                        y0 = rect->y0 + e->height;
                        y1 = rect->y1;
                    }
                }
                q.x0 = x0;
                q.y0 = y0;
                q.x1 = x1;
                q.y1 = y1;
                p = sprite_002195E0(p, &q, dx, dy);
            }
        }
        break;
    case 7:
        if (style == 2) {
            x0 = rect->x0 + 6;
            y0 = rect->y0;
            x1 = rect->x1 - 6;
            y1 = rect->y1 - 6;
            q.data[0] = q.data[4] = r;
            q.data[1] = q.data[5] = g;
            q.data[2] = q.data[6] = b;
            q.data[3] = q.data[7] = alpha;
            q.data[8] = q.data[12] = r;
            q.data[9] = q.data[13] = g;
            q.data[10] = q.data[14] = b;
            q.data[11] = q.data[15] = alpha;
            q.x0 = x0;
            q.y0 = y0;
            q.x1 = x1;
            q.y1 = y0;
            q.x2 = x0;
            q.y2 = y1;
            q.x3 = x1;
            q.y3 = y1;
            q.data[16] = mode;
            q.flag = 1;
            q.depth = depth;
            p = quad_002195E0(p, &q, dx, dy);
        }
        for (i = 0; i < 16; i++) {
            q.data[i] = 0x80;
        }
        for (i = 0; i < 5; i++) {
            q.data[16] = 1;
            q.flag = 1;
            q.depth = depth;
            if (style == 0) {
                if (i < 2) {
                    if (i == 0) {
                        q.index = window_tex_no[rect->kind][0];
                        x0 = rect->x0;
                        y1 = rect->y1;
                        e = &tex_uv_data[q.index];
                        x1 = x0 + e->width;
                        y0 = y1 - e->height;
                    } else if (i == 1) {
                        q.index = window_tex_no[rect->kind][1];
                        x1 = rect->x1;
                        y1 = rect->y1;
                        e = &tex_uv_data[q.index];
                        x0 = x1 - e->width;
                        y0 = y1 - e->height;
                    }
                } else {
                    c = window_tex_no[rect->kind][0];
                    if (i == 2) {
                        q.index = window_tex_no[rect->kind][4];
                        e = &tex_uv_data[c];
                        w = e->width;
                        y1 = rect->y1;
                        x0 = rect->x0 + w;
                        x1 = rect->x1 - w;
                        y0 = y1 - e->height;
                    } else if (i == 3) {
                        q.index = window_tex_no[rect->kind][6];
                        e = &tex_uv_data[c];
                        x0 = rect->x0;
                        y0 = rect->y0;
                        x1 = x0 + e->width;
                        y1 = rect->y1 - e->height;
                    } else {
                        q.index = window_tex_no[rect->kind][7];
                        e = &tex_uv_data[c];
                        x1 = rect->x1;
                        y0 = rect->y0;
                        x0 = x1 - e->width;
                        y1 = rect->y1 - e->height;
                    }
                }
                q.x0 = x0;
                q.y0 = y1;
                q.x1 = x1;
                q.y1 = y0;
                p = flipped_002195E0(p, &q, dx, dy);
            } else {
                if (i <= 1) {
                    if (i == 0) {
                        q.index = window_tex_no[rect->kind][2];
                        x0 = rect->x0;
                        y1 = rect->y1;
                        e = &tex_uv_data[q.index];
                        x1 = x0 + e->width;
                        y0 = y1 - e->height;
                    } else {
                        q.index = window_tex_no[rect->kind][3];
                        x1 = rect->x1;
                        y1 = rect->y1;
                        e = &tex_uv_data[q.index];
                        x0 = x1 - e->width;
                        y0 = y1 - e->height;
                    }
                } else {
                    c = window_tex_no[rect->kind][0];
                    if (i == 2) {
                        q.index = window_tex_no[rect->kind][5];
                        e = &tex_uv_data[c];
                        w = e->width;
                        y1 = rect->y1;
                        x0 = rect->x0 + w;
                        x1 = rect->x1 - w;
                        y0 = y1 - e->height;
                    } else if (i == 3) {
                        q.index = window_tex_no[rect->kind][6];
                        e = &tex_uv_data[c];
                        x0 = rect->x0;
                        y0 = rect->y0;
                        x1 = x0 + e->width;
                        y1 = rect->y1 - e->height;
                    } else {
                        q.index = window_tex_no[rect->kind][7];
                        e = &tex_uv_data[c];
                        x1 = rect->x1;
                        y0 = rect->y0;
                        x0 = x1 - e->width;
                        y1 = rect->y1 - e->height;
                    }
                }
                q.x0 = x0;
                q.y0 = y0;
                q.x1 = x1;
                q.y1 = y1;
                p = sprite_002195E0(p, &q, dx, dy);
            }
        }
        break;
    }
    return p;
}

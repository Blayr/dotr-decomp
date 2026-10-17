#include "common.h"

typedef struct Tag_001B4780 {
    u32 count : 16;
    u32 flags : 16;
    u32 reserved;
    u64 registers;
} Tag_001B4780;

typedef struct Color_001B4780 {
    u32 r : 8;
    u32 g : 8;
    u32 b : 8;
    u32 a : 8;
    f32 q;
} Color_001B4780;

typedef struct UV_001B4780 {
    u16 u : 14;
    u16 pad0 : 2;
    u16 v : 14;
    u16 pad1 : 2;
    u32 reserved;
} UV_001B4780;

typedef struct XYZ_001B4780 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} XYZ_001B4780;

typedef struct Sprite_001B4780 {
    u64 tag[2];
    Color_001B4780 color;
    u64 uv0;
    XYZ_001B4780 xyz0;
    u64 uv1;
    XYZ_001B4780 xyz1;
    u64 texture[4];
} Sprite_001B4780;

typedef struct Vertex_001B4780 {
    Color_001B4780 color;
    XYZ_001B4780 xyz;
} Vertex_001B4780;

typedef struct Gradient_001B4780 {
    u64 tag[2];
    Vertex_001B4780 v[4];
} Gradient_001B4780;

typedef struct Corner_001B4780 {
    u64 uv;
    XYZ_001B4780 xyz;
} Corner_001B4780;

typedef struct Quad_001B4780 {
    u64 tag[2];
    Color_001B4780 color;
    Corner_001B4780 c[4];
    u64 texture[4];
} Quad_001B4780;

typedef struct Texture_001B4780 {
    u8 index;
    u8 reserved;
    u16 x0;
    u16 y0;
    u16 x1;
    u16 y1;
} Texture_001B4780;

typedef struct State_001B4780 {
    u8 pad000[0x6A0];
    void *textures[16];
    u8 pad6E0[0x578];
    s32 depth;
} State_001B4780;

extern Texture_001B4780 gSzDuel_Icon[];
extern u8 gSzDuel_aaicolRgba[];
extern u8 aabFrameOfs[];
extern u8 abDecoOfs[];

static inline void tag_001B4780(Tag_001B4780 *tag, s32 count, s32 flags, u64 registers) {
    tag->flags = flags;
    tag->count = count;
    tag->registers = registers;
    tag->reserved = 0;
}

static inline s32 abs_001B4780(s32 value) {
    if (value >= 0) {
        return value;
    }
    return -value;
}

static inline s32 intensity_001B4780(s32 bright) {
    if (bright != 0) {
        return 0x80;
    }
    return 0x30;
}

s32 lSzDuel_DrawWindow_Frame_Pipe(s32 packet, s32 colorIndex, s32 icons, s32 style, s32 x, s32 y, s32 cols, s32 rows, s64 bright) {
    Sprite_001B4780 sprite __attribute__((aligned(8)));
    Gradient_001B4780 gradient __attribute__((aligned(8)));
    u64 spare;
    Quad_001B4780 arrow __attribute__((aligned(8)));
    Quad_001B4780 cursor __attribute__((aligned(8)));
    Quad_001B4780 page __attribute__((aligned(8)));
    State_001B4780 *graphics;
    Texture_001B4780 *parts;
    Texture_001B4780 *part;
    Texture_001B4780 *icon;
    u8 *margin;
    s32 dx;
    s32 x0;
    s32 y0;
    s32 height;
    s32 index;
    s32 ih;
    s32 w;
    s32 width;
    s32 kind;
    s32 shift;
    s32 col;
    s32 dy;
    s32 px;
    s32 py;
    s32 row;
    s32 iw;
    u8 *rgb;
    extern s32 ExSortPrim_Pipe();
    u32 tmp;

    (void)&spare; /* spare's 8-byte slot sits between gradient and arrow in the original frame */
    graphics = (State_001B4780 *)duelState.b;
    tmp = style;
    parts = &gSzDuel_Icon[tmp * 9 + 0x3B];
    margin = &aabFrameOfs[tmp * 4];
    tmp = x + 0x6C0;
    style = y + 0x720;
    if (colorIndex >= 0) {
        rgb = &gSzDuel_aaicolRgba[colorIndex * 8];
        if (cols >= 0) {
            width = ((parts[2].x1 - parts[2].x0) - margin[1]) + (((parts[0].x1 - parts[0].x0) - margin[0]) + cols * (parts[1].x1 - parts[1].x0));
        } else {
            width = abs_001B4780(cols);
        }
        if (rows >= 0) {
            height = ((parts[6].y1 - parts[6].y0) - margin[3]) + (((parts[0].y1 - parts[0].y0) - margin[2]) + rows * (parts[3].y1 - parts[3].y0));
        } else {
            height = abs_001B4780(rows);
        }
        height >>= 1;
        x0 = tmp + margin[0];
        y0 = style + margin[2];
        tag_001B4780((Tag_001B4780 *)gradient.tag, 8, 0x14, 0x41414141);
        if (colorIndex >= 0xE) {
            ExAssignAlpha(&gradient, ExGetAlphaVal(0));
        } else if (colorIndex >= 0xC) {
            ExAssignAlpha(&gradient, ExGetAlphaVal(2));
        }
        gradient.v[0].color.r = gradient.v[1].color.r = rgb[2];
        gradient.v[0].color.g = gradient.v[1].color.g = rgb[1];
        gradient.v[0].color.b = gradient.v[1].color.b = rgb[0];
        gradient.v[0].color.a = gradient.v[1].color.a = rgb[3];
        gradient.v[0].color.q = gradient.v[1].color.q = 1.0f;
        gradient.v[2].color.r = gradient.v[3].color.r = rgb[6];
        gradient.v[2].color.g = gradient.v[3].color.g = rgb[5];
        gradient.v[2].color.b = gradient.v[3].color.b = rgb[4];
        gradient.v[2].color.a = gradient.v[3].color.a = rgb[7];
        gradient.v[2].color.q = gradient.v[3].color.q = 1.0f;
        gradient.v[0].xyz.x = x0 * 16;
        gradient.v[0].xyz.y = y0 * 16;
        gradient.v[0].xyz.z = graphics->depth;
        gradient.v[0].xyz.fog = 0;
        gradient.v[1].xyz.x = (x0 + width) * 16;
        gradient.v[1].xyz.y = y0 * 16;
        gradient.v[1].xyz.z = graphics->depth;
        gradient.v[1].xyz.fog = 0;
        gradient.v[2].xyz.x = x0 * 16;
        gradient.v[2].xyz.y = (y0 + height) * 16;
        gradient.v[2].xyz.z = graphics->depth;
        gradient.v[2].xyz.fog = 0;
        gradient.v[3].xyz.x = (x0 + width) * 16;
        gradient.v[3].xyz.y = (y0 + height) * 16;
        gradient.v[3].xyz.z = graphics->depth;
        gradient.v[3].xyz.fog = 0;
        packet = ExSortPrim_Pipe(packet, &gradient, 0, 0);
        gradient.v[0].color.r = gradient.v[1].color.r = rgb[6];
        gradient.v[0].color.g = gradient.v[1].color.g = rgb[5];
        gradient.v[0].color.b = gradient.v[1].color.b = rgb[4];
        gradient.v[0].color.a = gradient.v[1].color.a = rgb[7];
        gradient.v[0].color.q = gradient.v[1].color.q = 1.0f;
        gradient.v[2].color.r = gradient.v[3].color.r = rgb[2];
        gradient.v[2].color.g = gradient.v[3].color.g = rgb[1];
        gradient.v[2].color.b = gradient.v[3].color.b = rgb[0];
        gradient.v[2].color.a = gradient.v[3].color.a = rgb[3];
        gradient.v[2].color.q = gradient.v[3].color.q = 1.0f;
        gradient.v[0].xyz.x = x0 * 16;
        gradient.v[0].xyz.y = (y0 + height) * 16;
        gradient.v[0].xyz.z = graphics->depth;
        gradient.v[0].xyz.fog = 0;
        gradient.v[1].xyz.x = (x0 + width) * 16;
        gradient.v[1].xyz.y = (y0 + height) * 16;
        gradient.v[1].xyz.z = graphics->depth;
        gradient.v[1].xyz.fog = 0;
        gradient.v[2].xyz.x = x0 * 16;
        gradient.v[2].xyz.y = (y0 + height * 2) * 16;
        gradient.v[2].xyz.z = graphics->depth;
        gradient.v[2].xyz.fog = 0;
        gradient.v[3].xyz.x = (x0 + width) * 16;
        gradient.v[3].xyz.y = (y0 + height * 2) * 16;
        gradient.v[3].xyz.z = graphics->depth;
        gradient.v[3].xyz.fog = 0;
        packet = ExSortPrim_Pipe(packet, &gradient, 0, 0);
    }
    tag_001B4780((Tag_001B4780 *)sprite.tag, 5, 0x26, 0x42421);
    ((Tag_001B4780 *)sprite.tag)->flags |= 0x800;
    ExAssignAlpha(&sprite, 0x8000000044LL);
    sprite.color.r = sprite.color.g = sprite.color.b = intensity_001B4780(bright);
    sprite.color.a = 0x80;
    sprite.color.q = 1.0f;
    sprite.xyz0.z = graphics->depth;
    sprite.xyz0.fog = 0;
    sprite.xyz1.z = graphics->depth;
    sprite.xyz1.fog = 0;
    if (cols < 0) {
        cols += ((parts[0].x1 - parts[0].x0) - margin[0]) + ((parts[2].x1 - parts[2].x0) - margin[1]);
    }
    if (rows < 0) {
        rows += ((parts[0].y1 - parts[0].y0) - margin[2]) + ((parts[6].y1 - parts[6].y0) - margin[3]);
    }
    dy = 0;
    for (row = 0; row < 3; row++) {
        dx = 0;
        for (col = 0; col < 3; col++) {
            index = row * 3 + col;
            part = &parts[index];
            width = part->x1 - part->x0;
            height = part->y1 - part->y0;
            if (index == 1 || index == 4 || index == 7) {
                if (cols > 0) {
                    width *= cols;
                } else if (cols >= 0) {
                    width = cols;
                } else {
                    width = -cols;
                }
            }
            if ((u32)(index - 3) < 3) {
                if (rows > 0) {
                    height *= rows;
                } else if (rows >= 0) {
                    height = rows;
                } else {
                    height = -rows;
                }
            }
            if (index != 4 && width > 0 && height > 0) {
                ExAssignTexture(&sprite, graphics->textures[part->index], 0);
                ((UV_001B4780 *)&sprite.uv0)->u = part->x0 * 16;
                ((UV_001B4780 *)&sprite.uv0)->v = part->y0 * 16;
                ((UV_001B4780 *)&sprite.uv1)->u = part->x1 * 16;
                ((UV_001B4780 *)&sprite.uv1)->v = part->y1 * 16;
                sprite.xyz0.x = (tmp + dx) * 16 - 8;
                sprite.xyz0.y = (style + dy) * 16 - 8;
                sprite.xyz1.x = (width + (tmp + dx)) * 16 - 8;
                sprite.xyz1.y = (height + (style + dy)) * 16 - 8;
                packet = ExSortPrim_Pipe(packet, &sprite, 0, 0);
            }
            dx += width;
        }
        dy += height;
    }
    if (icons >= 0) {
        do {
            kind = icons & 0xF;
            shift = abDecoOfs[kind];
            icon = &gSzDuel_Icon[kind + 0x2F];
            if ((u32)(kind - 3) < 2) {
                tag_001B4780((Tag_001B4780 *)arrow.tag, 9, 0x24, 0x24242421 | ((u64)4 << 32));
                ((Tag_001B4780 *)arrow.tag)->flags |= 0x800;
                ExAssignAlpha(&arrow, 0x8000000044LL);
                ExAssignTexture(&arrow, graphics->textures[icon->index], 0);
                arrow.color.r = 0x80;
                arrow.color.g = 0x80;
                arrow.color.b = 0x80;
                arrow.color.a = 0x80;
                arrow.color.q = 1.0f;
                arrow.c[0].xyz.z = graphics->depth;
                arrow.c[0].xyz.fog = 0;
                arrow.c[1].xyz.z = graphics->depth;
                arrow.c[1].xyz.fog = 0;
                arrow.c[2].xyz.z = graphics->depth;
                arrow.c[2].xyz.fog = 0;
                arrow.c[3].xyz.z = graphics->depth;
                arrow.c[3].xyz.fog = 0;
                ((UV_001B4780 *)&arrow.c[0].uv)->u = icon->x0 * 16;
                ((UV_001B4780 *)&arrow.c[0].uv)->v = icon->y0 * 16;
                ((UV_001B4780 *)&arrow.c[1].uv)->u = icon->x1 * 16;
                ((UV_001B4780 *)&arrow.c[1].uv)->v = icon->y0 * 16;
                ((UV_001B4780 *)&arrow.c[2].uv)->u = icon->x0 * 16;
                ((UV_001B4780 *)&arrow.c[2].uv)->v = icon->y1 * 16;
                ((UV_001B4780 *)&arrow.c[3].uv)->u = icon->x1 * 16;
                ((UV_001B4780 *)&arrow.c[3].uv)->v = icon->y1 * 16;
                ih = icon->y1 - icon->y0;
                iw = icon->x1 - icon->x0;
                px = (tmp + margin[0]) - shift;
                py = style + margin[2];
                arrow.c[0].xyz.x = px * 16 + 8;
                arrow.c[0].xyz.y = (py + iw) * 16 + 8;
                arrow.c[1].xyz.x = px * 16 + 8;
                arrow.c[1].xyz.y = py * 16 + 8;
                arrow.c[2].xyz.x = (px + ih) * 16 + 8;
                arrow.c[2].xyz.y = (py + iw) * 16 + 8;
                arrow.c[3].xyz.x = (px + ih) * 16 + 8;
                arrow.c[3].xyz.y = py * 16 + 8;
                packet = ExSortPrim_Pipe(packet, &arrow, 0, 0);
                px = ((parts[0].x1 - parts[0].x0) - margin[0]) + ((parts[2].x1 - parts[2].x0) - margin[1]);
                w = cols > 0 ? cols * (parts[1].x1 - parts[1].x0) : (cols >= 0 ? cols : -cols);
                px += w;
                px = (px + (tmp + margin[0])) - ((icon->y1 - icon->y0) - shift);
                py = style + margin[2];
                arrow.c[0].xyz.x = (px + ih) * 16 - 0x18;
                arrow.c[0].xyz.y = (py + iw) * 16 + 8;
                arrow.c[1].xyz.x = (px + ih) * 16 - 0x18;
                arrow.c[1].xyz.y = py * 16 + 8;
                arrow.c[2].xyz.x = px * 16 - 0x18;
                arrow.c[2].xyz.y = (py + iw) * 16 + 8;
                arrow.c[3].xyz.x = px * 16 - 0x18;
                arrow.c[3].xyz.y = py * 16 + 8;
                packet = ExSortPrim_Pipe(packet, &arrow, 0, 0);
            } else if (kind == 5) {
                tag_001B4780((Tag_001B4780 *)cursor.tag, 9, 0x24, 0x24242421 | ((u64)4 << 32));
                ((Tag_001B4780 *)cursor.tag)->flags |= 0x800;
                ExAssignAlpha(&cursor, 0x8000000044LL);
                ExAssignTexture(&cursor, graphics->textures[icon->index], 0);
                cursor.color.r = 0x80;
                cursor.color.g = 0x80;
                cursor.color.b = 0x80;
                cursor.color.a = 0x80;
                cursor.color.q = 1.0f;
                cursor.c[0].xyz.z = graphics->depth;
                cursor.c[0].xyz.fog = 0;
                cursor.c[1].xyz.z = graphics->depth;
                cursor.c[1].xyz.fog = 0;
                cursor.c[2].xyz.z = graphics->depth;
                cursor.c[2].xyz.fog = 0;
                cursor.c[3].xyz.z = graphics->depth;
                cursor.c[3].xyz.fog = 0;
                ((UV_001B4780 *)&cursor.c[0].uv)->u = icon->x0 * 16;
                ((UV_001B4780 *)&cursor.c[0].uv)->v = icon->y0 * 16;
                ((UV_001B4780 *)&cursor.c[1].uv)->u = icon->x1 * 16;
                ((UV_001B4780 *)&cursor.c[1].uv)->v = icon->y0 * 16;
                ((UV_001B4780 *)&cursor.c[2].uv)->u = icon->x0 * 16;
                ((UV_001B4780 *)&cursor.c[2].uv)->v = icon->y1 * 16;
                ((UV_001B4780 *)&cursor.c[3].uv)->u = icon->x1 * 16;
                ((UV_001B4780 *)&cursor.c[3].uv)->v = icon->y1 * 16;
                ih = icon->y1 - icon->y0;
                iw = icon->x1 - icon->x0;
                px = ((parts[0].x1 - parts[0].x0) - margin[0]) + ((parts[2].x1 - parts[2].x0) - margin[1]);
                if (cols > 0) {
                    w = cols * (parts[1].x1 - parts[1].x0);
                } else if (cols >= 0) {
                    w = cols;
                } else {
                    w = -cols;
                }
                px += w;
                w = ih - shift;
                px = (px + (tmp + margin[0])) - w;
                (void)w; /* keeps ih - shift in its own temp (no fold into px) */
                py = style + margin[2];
                cursor.c[0].xyz.x = (px + ih) * 16 - 0x18;
                cursor.c[0].xyz.y = (py + iw) * 16 + 8;
                cursor.c[1].xyz.x = (px + ih) * 16 - 0x18;
                cursor.c[1].xyz.y = py * 16 + 8;
                cursor.c[2].xyz.x = px * 16 - 0x18;
                cursor.c[2].xyz.y = (py + iw) * 16 + 8;
                cursor.c[3].xyz.x = px * 16 - 0x18;
                cursor.c[3].xyz.y = py * 16 + 8;
                packet = ExSortPrim_Pipe(packet, &cursor, 0, 0);
                icon = &gSzDuel_Icon[0x38];
                ((UV_001B4780 *)&cursor.c[0].uv)->u = icon->x0 * 16;
                ((UV_001B4780 *)&cursor.c[0].uv)->v = icon->y0 * 16;
                ((UV_001B4780 *)&cursor.c[1].uv)->u = icon->x1 * 16;
                ((UV_001B4780 *)&cursor.c[1].uv)->v = icon->y0 * 16;
                ((UV_001B4780 *)&cursor.c[2].uv)->u = icon->x0 * 16;
                ((UV_001B4780 *)&cursor.c[2].uv)->v = icon->y1 * 16;
                ((UV_001B4780 *)&cursor.c[3].uv)->u = icon->x1 * 16;
                ((UV_001B4780 *)&cursor.c[3].uv)->v = icon->y1 * 16;
                ih = icon->y1 - icon->y0;
                iw = icon->x1 - icon->x0;
                py += 8;
                cursor.c[0].xyz.x = (px + ih) * 16 - 0x18;
                cursor.c[0].xyz.y = (py + iw) * 16 + 8;
                cursor.c[1].xyz.x = (px + ih) * 16 - 0x18;
                cursor.c[1].xyz.y = py * 16 + 8;
                cursor.c[2].xyz.x = px * 16 - 0x18;
                cursor.c[2].xyz.y = (py + iw) * 16 + 8;
                cursor.c[3].xyz.x = px * 16 - 0x18;
                cursor.c[3].xyz.y = py * 16 + 8;
                packet = ExSortPrim_Pipe(packet, &cursor, 0, 0);
            } else if (kind == 6) {
                tag_001B4780((Tag_001B4780 *)page.tag, 9, 0x24, 0x24242421 | ((u64)4 << 32));
                ((Tag_001B4780 *)page.tag)->flags |= 0x800;
                ExAssignAlpha(&page, 0x8000000044LL);
                ExAssignTexture(&page, graphics->textures[icon->index], 0);
                page.color.r = 0x80;
                page.color.g = 0x80;
                page.color.b = 0x80;
                page.color.a = 0x80;
                page.color.q = 1.0f;
                page.c[0].xyz.z = graphics->depth;
                page.c[0].xyz.fog = 0;
                page.c[1].xyz.z = graphics->depth;
                page.c[1].xyz.fog = 0;
                page.c[2].xyz.z = graphics->depth;
                page.c[2].xyz.fog = 0;
                page.c[3].xyz.z = graphics->depth;
                page.c[3].xyz.fog = 0;
                ((UV_001B4780 *)&page.c[0].uv)->u = icon->x0 * 16;
                ((UV_001B4780 *)&page.c[0].uv)->v = icon->y0 * 16;
                ((UV_001B4780 *)&page.c[1].uv)->u = icon->x1 * 16;
                ((UV_001B4780 *)&page.c[1].uv)->v = icon->y0 * 16;
                ((UV_001B4780 *)&page.c[2].uv)->u = icon->x0 * 16;
                ((UV_001B4780 *)&page.c[2].uv)->v = icon->y1 * 16;
                ((UV_001B4780 *)&page.c[3].uv)->u = icon->x1 * 16;
                ((UV_001B4780 *)&page.c[3].uv)->v = icon->y1 * 16;
                ih = icon->y1 - icon->y0;
                iw = icon->x1 - icon->x0;
                px = (tmp + margin[0]) - shift;
                py = style + margin[2];
                page.c[0].xyz.x = px * 16 + 8;
                page.c[0].xyz.y = (py + iw) * 16 + 8;
                page.c[1].xyz.x = px * 16 + 8;
                page.c[1].xyz.y = py * 16 + 8;
                page.c[2].xyz.x = (px + ih) * 16 + 8;
                page.c[2].xyz.y = (py + iw) * 16 + 8;
                page.c[3].xyz.x = (px + ih) * 16 + 8;
                page.c[3].xyz.y = py * 16 + 8;
                packet = ExSortPrim_Pipe(packet, &page, 0, 0);
                icon = &gSzDuel_Icon[0x39];
                ((UV_001B4780 *)&page.c[0].uv)->u = icon->x0 * 16;
                ((UV_001B4780 *)&page.c[0].uv)->v = icon->y0 * 16;
                ((UV_001B4780 *)&page.c[1].uv)->u = icon->x1 * 16;
                ((UV_001B4780 *)&page.c[1].uv)->v = icon->y0 * 16;
                ((UV_001B4780 *)&page.c[2].uv)->u = icon->x0 * 16;
                ((UV_001B4780 *)&page.c[2].uv)->v = icon->y1 * 16;
                ((UV_001B4780 *)&page.c[3].uv)->u = icon->x1 * 16;
                ((UV_001B4780 *)&page.c[3].uv)->v = icon->y1 * 16;
                ih = icon->y1 - icon->y0;
                iw = icon->x1 - icon->x0;
                py += 8;
                px -= ih - shift;
                page.c[0].xyz.x = (px + ih) * 16 + 8;
                page.c[0].xyz.y = py * 16 + 8;
                page.c[1].xyz.x = (px + ih) * 16 + 8;
                page.c[1].xyz.y = (py + iw) * 16 + 8;
                page.c[2].xyz.x = px * 16 + 8;
                page.c[2].xyz.y = py * 16 + 8;
                page.c[3].xyz.x = px * 16 + 8;
                page.c[3].xyz.y = (py + iw) * 16 + 8;
                packet = ExSortPrim_Pipe(packet, &page, 0, 0);
            } else {
                px = ((parts[0].x1 - parts[0].x0) - margin[0]) + ((parts[2].x1 - parts[2].x0) - margin[1]);
                w = cols > 0 ? cols * (parts[1].x1 - parts[1].x0) : (cols >= 0 ? cols : -cols);
                px += w;
                px >>= 1;
                px -= (icon->x1 - icon->x0) >> 1;
                px = px + (tmp + margin[0]);
                py = (style + margin[2]) - shift;
                ExAssignTexture(&sprite, graphics->textures[icon->index], 0);
                ((UV_001B4780 *)&sprite.uv0)->u = icon->x0 * 16 + 8;
                ((UV_001B4780 *)&sprite.uv0)->v = icon->y0 * 16 + 8;
                ((UV_001B4780 *)&sprite.uv1)->u = icon->x1 * 16 + 8;
                ((UV_001B4780 *)&sprite.uv1)->v = icon->y1 * 16 + 8;
                iw = icon->x1 - icon->x0;
                ih = icon->y1 - icon->y0;
                sprite.xyz0.x = px * 16;
                sprite.xyz0.y = py * 16;
                sprite.xyz1.x = (px + iw) * 16;
                sprite.xyz1.y = (py + ih) * 16;
                packet = ExSortPrim_Pipe(packet, &sprite, 0, 0);
            }
            icons >>= 4;
        } while (icons != 0);
    }
    return packet;
}

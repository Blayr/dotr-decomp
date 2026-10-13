#include "common.h"

typedef struct {
    u8 texture;
    u8 padding;
    u16 left;
    u16 top;
    u16 right;
    u16 bottom;
} Texture_001B62F0;

typedef struct {
    u64 u : 14;
    u64 pad0 : 2;
    u64 v : 14;
    u64 pad1 : 34;
} UV_001B62F0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 padding : 8;
} XYZ_001B62F0;

typedef struct {
    u16 count;
    u16 flags;
    u32 padding;
    u64 registers;
} Header_001B62F0;

typedef struct {
    u64 header[2];
    u8 r, g, b, a;
    f32 q;
    u64 uv0;
    XYZ_001B62F0 xyz0;
    u64 uv1;
    XYZ_001B62F0 xyz1;
    u64 primitive;
    u64 tex0;
    u64 tex1;
    u64 clamp;
} Packet_001B62F0;

s32 func_001B62F0(s32 packet, s32 x, s32 y, s32 columns, s32 rows) {
    extern u8 D_002907E2[];
    extern void *D_00317B30[];
    Texture_001B62F0 *texture;
    s32 width;
    s32 xOffset;
    s32 column;
    u16 y0;
    u16 y1;
    s32 originY;
    s32 originX;
    s32 height;
    s32 yOffset;
    s32 row;
    Packet_001B62F0 sprite __attribute__((aligned(8)));
    UV_001B62F0 *uv0;
    UV_001B62F0 *uv1;

    originY = y + 0x720;
    texture = (Texture_001B62F0 *)D_002907E2;
    ((Header_001B62F0 *)sprite.header)->flags = 0x26;
    ((Header_001B62F0 *)sprite.header)->count = 5;
    ((Header_001B62F0 *)sprite.header)->registers = 0x42421;
    ((Header_001B62F0 *)sprite.header)->padding = 0;
    originX = x + 0x6C0;
    ((Header_001B62F0 *)sprite.header)->flags |= 0x800;
    func_002086D0(&sprite, 0x8000000044ULL);
    sprite.r = sprite.g = sprite.b = 0x80;
    sprite.a = 0x80;
    sprite.q = 1.0f;
    sprite.xyz0.z = D_003180E8;
    sprite.xyz0.padding = 0;
    sprite.xyz1.z = D_003180E8;
    sprite.xyz1.padding = 0;
    func_00208700(&sprite, D_00317B30[texture->texture], 0);
    uv0 = (UV_001B62F0 *)&sprite.uv0;
    uv1 = (UV_001B62F0 *)&sprite.uv1;
    uv0->u = texture->left * 16;
    yOffset = 0;
    row = 0;
    uv0->v = texture->top * 16;
    uv1->u = texture->right * 16;
    uv1->v = texture->bottom * 16;
    width = texture->right - texture->left;
    height = texture->bottom - texture->top;
    if (row < rows) {
        do {
            xOffset = 0;
            column = 0;
            if (column < columns) {
                u16 rowY = originY + yOffset;
                y0 = rowY * 16 - 8;
                y1 = (height + rowY) * 16 - 8;
                do {
                    u16 columnX = originX + xOffset;
                    sprite.xyz0.x = columnX * 16 - 8;
                    sprite.xyz0.y = y0;
                    sprite.xyz1.x = (width + columnX) * 16 - 8;
                    sprite.xyz1.y = y1;
                    packet = func_00207650(packet, (s32)&sprite, 0, 0);
                    column++;
                    xOffset += width;
                } while (column < columns);
            }
            yOffset += height;
            row++;
        } while (row < rows);
    }
    return packet;
}

void func_001B65E0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4,
                   s32 arg5, s32 arg6) {
    func_001B65F0(arg0, arg1, arg2, arg3, arg4, arg5, arg6, 0);
}

typedef struct {
    u8 texture;
    u8 padding;
    u16 left;
    u16 top;
    u16 right;
    u16 bottom;
} Slice_001B65F0;

typedef struct {
    u8 pad[4];
    u8 b;
    u8 g;
    u8 r;
    u8 a;
} Color_001B65F0;

typedef struct {
    u64 u : 14;
    u64 pad0 : 2;
    u64 v : 14;
    u64 pad1 : 34;
} UV_001B65F0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} XYZ_001B65F0;

typedef struct {
    u16 count;
    u16 flags;
    u32 padding;
    u64 registers;
} Header_001B65F0;

typedef struct {
    u64 header[2];
    u8 r, g, b, a;
    f32 q;
    u64 uv0;
    XYZ_001B65F0 xyz0;
    u64 uv1;
    XYZ_001B65F0 xyz1;
    u64 primitive;
    u64 tex0;
    u64 tex1;
    u64 clamp;
} Sprite_001B65F0;

typedef struct {
    u64 header[2];
    u8 r, g, b, a;
    f32 q;
    XYZ_001B65F0 xyz0;
    XYZ_001B65F0 xyz1;
    u64 end;
} Box_001B65F0;

s32 func_001B65F0(s32 packet, s32 colorIndex, s32 x, s32 y, s32 w, s32 h, s32 shadow, s32 style) {
    extern Slice_001B65F0 D_00290080[];
    extern Color_001B65F0 D_002BE840[];
    u8 *state = D_00317490;
    Slice_001B65F0 *slices = &D_00290080[style * 9 + 0x8C];
    Color_001B65F0 *color;
    s32 originX;
    s32 originY;
    s32 width;
    s32 height;
    s32 xOffset;
    s32 yOffset;
    s32 column;
    Slice_001B65F0 *slice;
    s32 row;
    s32 i;
    u16 y0;
    Sprite_001B65F0 sprite __attribute__((aligned(8)));
    Box_001B65F0 box __attribute__((aligned(8)));

    if (colorIndex < 0) {
        colorIndex = 2;
    }
    color = &D_002BE840[colorIndex];
    ((Header_001B65F0 *)sprite.header)->flags = 0x26;
    ((Header_001B65F0 *)sprite.header)->count = 5;
    ((Header_001B65F0 *)sprite.header)->registers = 0x42421;
    ((Header_001B65F0 *)sprite.header)->padding = 0;
    ((Header_001B65F0 *)sprite.header)->flags |= 0x800;
    func_002086D0(sprite.header, func_00208D00(0));
    originX = x + 0x6C0;
    originY = y + 0x720;
    sprite.r = color->r;
    sprite.g = color->g;
    sprite.b = color->b;
    sprite.a = color->a;
    sprite.q = 1.0f;
    sprite.xyz0.z = *(s32 *)(state + 0xC58);
    sprite.xyz0.fog = 0;
    sprite.xyz1.z = *(s32 *)(state + 0xC58);
    sprite.xyz1.fog = 0;
    if (shadow >= 0) {
        color = &D_002BE840[shadow];
        if (w >= 0) {
            width = (slices[2].right - slices[2].left) +
                    ((slices[0].right - slices[0].left) + w * (slices[1].right - slices[1].left));
        } else {
            width = (w >= 0) ? w : -w;
        }
        if (h >= 0) {
            height = (slices[6].bottom - slices[6].top) +
                     ((slices[0].bottom - slices[0].top) + h * (slices[3].bottom - slices[3].top));
        } else {
            height = (h >= 0) ? h : -h;
        }
        ((Header_001B65F0 *)box.header)->flags = 6;
        ((Header_001B65F0 *)box.header)->count = 3;
        ((Header_001B65F0 *)box.header)->registers = 0x441;
        ((Header_001B65F0 *)box.header)->padding = 0;
        if (shadow >= 0xE) {
            func_002086D0(box.header, func_00208D00(0));
        } else if (shadow >= 0xC) {
            func_002086D0(box.header, func_00208D00(2));
        }
        box.r = color->r;
        box.g = color->g;
        box.b = color->b;
        box.a = color->a;
        box.q = 1.0f;
        box.xyz0.z = *(s32 *)(state + 0xC58);
        box.xyz0.fog = 0;
        box.xyz1.z = *(s32 *)(state + 0xC58);
        box.xyz1.fog = 0;
        box.xyz0.x = originX << 4;
        box.xyz0.y = originY << 4;
        box.xyz1.x = (originX + width) << 4;
        box.xyz1.y = (originY + height) << 4;
        packet = func_00207650(packet, (s32)&box, 0, 0);
    }
    if (w < 0) {
        w += (slices[0].right - slices[0].left) + (slices[2].right - slices[2].left);
    }
    if (h < 0) {
        h += (slices[0].bottom - slices[0].top) + (slices[6].bottom - slices[6].top);
    }
    yOffset = 0;
    for (row = 0; row < 3; row++) {
        xOffset = 0;
        y0 = (u16)(originY + yOffset) * 16 - 8;
        for (column = 0; column < 3; column++) {
            i = row * 3 + column;
            slice = &slices[i];
            width = slice->right - slice->left;
            height = slice->bottom - slice->top;
            if (i == 1 || i == 4 || i == 7) {
                if (w > 0) {
                    width *= w;
                } else {
                    width = (w >= 0) ? w : -w;
                }
            }
            if ((u32)(i - 3) < 3) {
                if (h > 0) {
                    height *= h;
                } else {
                    height = (h >= 0) ? h : -h;
                }
            }
            if (i != 4 && width > 0 && height > 0) {
                u16 columnX;

                func_00208700(&sprite, *(void **)(state + 0x6A0 + slice->texture * 4), 0);
                ((UV_001B65F0 *)&sprite.uv0)->u = slice->left * 16;
                columnX = originX + xOffset;
                ((UV_001B65F0 *)&sprite.uv0)->v = slice->top * 16;
                ((UV_001B65F0 *)&sprite.uv1)->u = slice->right * 16;
                ((UV_001B65F0 *)&sprite.uv1)->v = slice->bottom * 16;
                sprite.xyz0.x = columnX * 16 - 8;
                sprite.xyz0.y = y0;
                sprite.xyz1.x = (width + columnX) * 16 - 8;
                sprite.xyz1.y = (height + (u16)(originY + yOffset)) * 16 - 8;
                packet = func_00207650(packet, (s32)&sprite, 0, 0);
            }
            xOffset += width;
        }
        yOffset += height;
    }
    return packet;
}

void func_001B6C90(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    func_001B6CA0(arg0, arg1, arg2, arg3, arg4, arg5, 0, 0);
}

typedef struct Result_001B6CA0 {
    s32 unk0;
    s32 unk4;
} Result_001B6CA0;

s32 func_001B6CA0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    extern s32 func_001FEAB0();
    extern s32 func_001FE7D0();
    Result_001B6CA0 *spA8;
    s32 stride;
    s32 digit;

    spA8 = (Result_001B6CA0 *) func_001FEAB0(0);
    stride = 0x14 - (arg5 ? 4 : 0);
    {
        s32 power = 1;

        if (arg4 == 0x7FFFFFFF) {
            digit = 0;
            spA8->unk4 = 0x108;
            if (0 < arg3) {
                do {
                    arg0 = func_001FE7D0(arg0, 0, arg1 + (stride * (arg3 - digit - 1)), arg2, arg7, func_001FDFE0);
                    digit += 1;
                } while (digit < arg3);
            }
            return arg0;
        }
        digit = 0;
        if (0 < arg3) {
            do {
                spA8->unk4 = (((arg4 / power) % 10) * 0x16);
                arg0 = func_001FE7D0(arg0, 0, arg1 + (stride * (arg3 - digit - 1)), arg2, arg7, func_001FDFE0);
                power *= 10;
                digit += 1;
            } while ((arg6 != 0 || arg4 >= power) && digit < arg3);
        }
        if (digit < arg3) {
            if (arg4 < 0) {
                spA8->unk4 = 0xF2;
                arg0 = func_001FE7D0(arg0, 0, arg1 + (stride * (arg3 - digit - 1)), arg2, arg7, func_001FDFE0);
            }
        }
    }
    return arg0;
}

void func_001B6EA0(s32 arg0, s32 arg1, s32 arg2, s32 arg3,
                   s32 flags, s32 width, s32 number) {
    s8 text[16];
    s32 padded;
    s32 power;
    s32 i;

    power = 1;
    padded = 0;
    if (flags & 0x20) {
        padded = 1;
    }
    for (i = 0; i < width; i++) {
        text[i] = ' ';
    }
    for (i = 0; i < width;) {
        text[width - i - 1] = (number / power) % 10 + '0';
        power *= 10;
        i++;
        if (!padded && number < power) {
            break;
        }
    }
    func_001B6F70(arg0, arg1, arg2, arg3, flags, width, text, 0);
}

INCLUDE_ASM("asm/nonmatchings/main_039", func_001B6F70);

static s32 func_001B7660(s8 character) {
    s32 result = -1;

    if (character >= 'A' && character <= 'Z') {
        result = character - 'A';
    } else if (character >= 'a' && character <= 'z') {
        result = character - 'a';
    } else if (character >= '0' && character <= '9') {
        result = character - '0' + 26;
    } else if (character == '?') {
        result = 36;
    }
    return result;
}

typedef struct Glyph_001B76E0 {
    u16 unk0;
    u16 left;
    u16 unk4;
    u16 right;
    u16 unk8;
} Glyph_001B76E0;

extern u8 D_002BE950[];
extern u8 D_002BE951[];
extern Glyph_001B76E0 D_00290B70[];

void func_001B76E0(s32 arg0, s32 arg1, s32 arg2, s8 *arg3, s32 *arg4, s32 *arg5) {
    s32 width;
    s32 lineHeight;
    s32 proportional;
    s32 maxWidth;
    s32 lineWidth;
    s32 height;
    s32 i;
    s32 halfWidth;
    s32 glyphBase;
    s8 *character;
    s32 glyph;
    Glyph_001B76E0 *entry;

    width = D_002BE950[arg0 * 2];
    lineHeight = D_002BE951[arg0 * 2];
    proportional = 0;
    maxWidth = 0;
    lineWidth = 0;
    height = 0;
    if (arg1 & 1) {
        proportional = 1;
    }
    for (i = 0; i < arg2; i++) {
        halfWidth = width >> 1;
        glyphBase = arg0 * 37;
        character = arg3 + i;
        glyph = func_001B7660(*character);
        if (glyph < 0) {
            if (*character == '\n') {
                if (maxWidth < lineWidth) {
                    maxWidth = lineWidth;
                }
                height += lineHeight;
                lineWidth = 0;
            } else {
                lineWidth += proportional ? halfWidth : width;
            }
        } else {
            entry = &D_00290B70[glyph + glyphBase];
            if (proportional) {
                lineWidth += entry->right - entry->left;
            } else {
                lineWidth += width;
            }
        }
    }
    if (maxWidth < lineWidth) {
        maxWidth = lineWidth;
    }
    height += lineHeight;
    if (arg4 != 0) {
        *arg4 = maxWidth;
    }
    if (arg5 != 0) {
        *arg5 = height;
    }
}

typedef struct {
    u16 count;
    u16 flags;
    u32 padding;
    u64 registers;
} Tag_001B7820;

typedef struct {
    u8 texture;
    u8 padding;
    u16 left;
    u16 top;
    u16 right;
    u16 bottom;
} Texture_001B7820;

typedef struct {
    u64 u : 14;
    u64 pad0 : 2;
    u64 v : 14;
    u64 pad1 : 34;
} UV_001B7820;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Vertex_001B7820;

typedef struct {
    u64 uv;
    Vertex_001B7820 xyz;
} Corner_001B7820;

typedef struct {
    u64 tag[2];
    u8 r, g, b, a;
    f32 q;
    Corner_001B7820 corners[4];
    u64 extra[4];
} Packet_001B7820;

typedef struct {
    f32 v[4][4];
} Quad_001B7820;

typedef struct {
    s32 v[4];
} Rotation_001B7820;

typedef struct {
    f32 m[4][4];
} Matrix_001B7820;

typedef struct {
    u8 pad000[0x6A0];
    void *textures[16];
    u8 pad6E0[0x578];
    s32 depth;
} State_001B7820;

s32 func_001B7820(s32 packet, s32 x, s32 y, s32 alpha) {
    extern Quad_001B7820 D_002912E0;
    extern Rotation_001B7820 D_00291320;
    extern u8 D_0029080A[];
    extern void func_0020CF00(void *, s32, void *, s32);
    State_001B7820 *state;
    Texture_001B7820 *texture;
    s32 originX;
    s32 originY;
    u8 *player;
    s32 base;
    s32 halfWidth;
    s32 halfHeight;
    Quad_001B7820 corners;
    Rotation_001B7820 rotation;
    Matrix_001B7820 matrix;
    Packet_001B7820 sprite __attribute__((aligned(8)));

    state = (State_001B7820 *)D_00317490;
    player = D_00317490 + D_003181CC * 0x350;
    texture = (Texture_001B7820 *)D_0029080A;
    originX = x + 0x6C0;
    originY = y + 0x720;
    halfWidth = (texture->right - texture->left) >> 1;
    halfHeight = (texture->bottom - texture->top) >> 1;
    corners = D_002912E0;
    base = D_003181CC ? 0xC000 : 0x4000;
    corners.v[0][0] = -(f32)halfWidth;
    corners.v[0][1] = -(f32)halfHeight;
    corners.v[1][0] = (f32)halfWidth;
    corners.v[1][1] = -(f32)halfHeight;
    corners.v[2][0] = -(f32)halfWidth;
    corners.v[2][1] = (f32)halfHeight;
    corners.v[3][0] = (f32)halfWidth;
    corners.v[3][1] = (f32)halfHeight;
    rotation = D_00291320;
    rotation.v[2] = -(*(s32 *)(player + 0x1D4) - base);
    ((Tag_001B7820 *)sprite.tag)->flags = 0x24;
    ((Tag_001B7820 *)sprite.tag)->count = 9;
    ((Tag_001B7820 *)sprite.tag)->registers = 0x424242421ULL;
    ((Tag_001B7820 *)sprite.tag)->padding = 0;
    ((Tag_001B7820 *)sprite.tag)->flags |= 0x800;
    func_002086D0(&sprite, 0x8000000044ULL);
    sprite.r = 0x80;
    sprite.g = 0x80;
    sprite.b = 0x80;
    sprite.a = alpha;
    sprite.q = 1.0f;
    func_00208700(&sprite, state->textures[texture->texture], 0);
    ((UV_001B7820 *)&sprite.corners[0].uv)->u = texture->left * 16;
    ((UV_001B7820 *)&sprite.corners[0].uv)->v = texture->top * 16;
    ((UV_001B7820 *)&sprite.corners[1].uv)->u = texture->right * 16;
    ((UV_001B7820 *)&sprite.corners[1].uv)->v = texture->top * 16;
    ((UV_001B7820 *)&sprite.corners[2].uv)->u = texture->left * 16;
    ((UV_001B7820 *)&sprite.corners[2].uv)->v = texture->bottom * 16;
    ((UV_001B7820 *)&sprite.corners[3].uv)->u = texture->right * 16;
    ((UV_001B7820 *)&sprite.corners[3].uv)->v = texture->bottom * 16;
    func_0020C630(&matrix, &rotation);
    func_0020BAF0((s32)&matrix);
    func_0020CF00((void *)0x70000000, 0, &corners, 4);
    func_0020BB50();
    sprite.corners[0].xyz.x = (originX << 4) + (s32)(16.0f * ((f32 *)0x70000000)[0]) - 8;
    sprite.corners[0].xyz.y = (originY << 4) + (s32)(16.0f * ((f32 *)0x70000000)[1]) - 8;
    sprite.corners[0].xyz.z = state->depth;
    sprite.corners[0].xyz.fog = 0;
    sprite.corners[1].xyz.x = (originX << 4) + (s32)(16.0f * ((f32 *)0x70000000)[4]) - 8;
    sprite.corners[1].xyz.y = (originY << 4) + (s32)(16.0f * ((f32 *)0x70000000)[5]) - 8;
    sprite.corners[1].xyz.z = state->depth;
    sprite.corners[1].xyz.fog = 0;
    sprite.corners[2].xyz.x = (originX << 4) + (s32)(16.0f * ((f32 *)0x70000000)[8]) - 8;
    sprite.corners[2].xyz.y = (originY << 4) + (s32)(16.0f * ((f32 *)0x70000000)[9]) - 8;
    sprite.corners[2].xyz.z = state->depth;
    sprite.corners[2].xyz.fog = 0;
    sprite.corners[3].xyz.x = (originX << 4) + (s32)(16.0f * ((f32 *)0x70000000)[12]) - 8;
    sprite.corners[3].xyz.y = (originY << 4) + (s32)(16.0f * ((f32 *)0x70000000)[13]) - 8;
    sprite.corners[3].xyz.z = state->depth;
    sprite.corners[3].xyz.fog = 0;
    packet = func_0020A0B0(packet, 0);
    packet = func_00207650(packet, (s32)&sprite, 0, 0);
    return func_0020A0B0(packet, 1);
}

typedef struct {
    u16 count;
    u16 flags;
    u32 padding;
    u64 registers;
} Tag_001B7D60;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Color_001B7D60;

typedef struct {
    u64 u : 14;
    u64 pad0 : 2;
    u64 v : 14;
    u64 pad1 : 34;
} UV_001B7D60;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Vertex_001B7D60;

typedef struct {
    u64 tag[2];
    Color_001B7D60 color;
    u64 uv0;
    Vertex_001B7D60 vertex0;
    u64 uv1;
    Vertex_001B7D60 vertex1;
    u64 test;
    u64 texture0;
    u64 texture1;
    u64 clamp;
} Packet_001B7D60;

static inline void set_uv_001B7D60(UV_001B7D60 *p, s32 u, s32 v) {
    p->u = u;
    p->v = v;
}

s32 func_001B7D60(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5,
                  s64 arg6) {
    extern s32 func_00202E00();
    u8 *state = D_00317490;
    s32 x = arg2 + 0x6C0;
    s32 y = arg3 + 0x720;
    void **image;
    s32 address;
    Packet_001B7D60 packet __attribute__((aligned(8)));

    image = func_00200930(1, arg1);
    if (image == NULL) {
        return arg0;
    }
    if (**(s32 **)image == 0x324852) {
        address = *(s32 *)(state + 0xC7C);
        address += func_00202E00(address, 1);
        arg0 = func_00202FB0(arg0, (s32)*image, address, 0);
        arg0 = func_0020F290(arg0);
        ((Tag_001B7D60 *)packet.tag)->flags = 0x26;
        ((Tag_001B7D60 *)packet.tag)->count = 5;
        ((Tag_001B7D60 *)packet.tag)->registers = 0x42421;
        ((Tag_001B7D60 *)packet.tag)->padding = 0;
        ((Tag_001B7D60 *)packet.tag)->flags |= 0x800;
        func_00208700(packet.tag, *image, 0);
        packet.color.r = 0x80;
        packet.color.g = 0x80;
        packet.color.b = 0x80;
        packet.color.a = 0x80;
        packet.color.q = 1.0f;
        set_uv_001B7D60((UV_001B7D60 *)&packet.uv0, 8, 8);
        set_uv_001B7D60((UV_001B7D60 *)&packet.uv1, 0x808, 0x808);
        packet.vertex0.x = x << 4;
        packet.vertex0.y = y << 4;
        packet.vertex0.z = arg6;
        packet.vertex0.fog = 0;
        packet.vertex1.x = (x + arg4) << 4;
        packet.vertex1.y = (y + arg5) << 4;
        packet.vertex1.z = arg6;
        packet.vertex1.fog = 0;
        arg0 = func_00207650(arg0, (s32)packet.tag, 0, 0);
    }
    return arg0;
}

typedef struct {
    u16 count;
    u16 flags;
    u32 padding;
    u64 registers;
} Tag_001B7F90;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Color_001B7F90;

typedef struct {
    u64 u : 14;
    u64 pad0 : 2;
    u64 v : 14;
    u64 pad1 : 34;
} UV_001B7F90;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Vertex_001B7F90;

typedef struct {
    u64 tag[2];
    Color_001B7F90 color;
    u64 uv0;
    Vertex_001B7F90 vertex0;
    u64 uv1;
    Vertex_001B7F90 vertex1;
    u64 test;
    u64 texture0;
    u64 texture1;
    u64 clamp;
} Packet_001B7F90;

static inline void set_uv_001B7F90(UV_001B7F90 *p, s32 u, s32 v) {
    p->u = u;
    p->v = v;
}

s32 func_001B7F90(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5,
                  s64 arg6, s32 arg7) {
    extern s32 func_00202E00();
    u8 *state = D_00317490;
    s32 x = arg2 + 0x6C0;
    s32 y = arg3 + 0x720;
    void **image;
    s32 address;
    u8 color;
    Packet_001B7F90 packet __attribute__((aligned(8)));

    image = func_00200930(2, arg1);
    if (image == NULL) {
        return arg0;
    }
    if (**(s32 **)image == 0x324852) {
        address = *(s32 *)(state + 0xC7C);
        address += func_00202E00(address, 1);
        arg0 = func_00202FB0(arg0, (s32)*image, address, 0);
        arg0 = func_0020F290(arg0);
        ((Tag_001B7F90 *)packet.tag)->flags = 0x26;
        ((Tag_001B7F90 *)packet.tag)->count = 5;
        ((Tag_001B7F90 *)packet.tag)->registers = 0x42421;
        ((Tag_001B7F90 *)packet.tag)->padding = 0;
        ((Tag_001B7F90 *)packet.tag)->flags |= 0x800;
        func_00208700(packet.tag, *image, 0);
        color = arg7 ? 0x80 : 0x30;
        packet.color.r = packet.color.g = packet.color.b = color;
        packet.color.a = 0x80;
        packet.color.q = 1.0f;
        set_uv_001B7F90((UV_001B7F90 *)&packet.uv0, 8, 8);
        set_uv_001B7F90((UV_001B7F90 *)&packet.uv1, 0x288, 0x208);
        packet.vertex0.x = x << 4;
        packet.vertex0.y = y << 4;
        packet.vertex0.z = arg6;
        packet.vertex0.fog = 0;
        packet.vertex1.x = (x + arg4) << 4;
        packet.vertex1.y = (y + arg5) << 4;
        packet.vertex1.z = arg6;
        packet.vertex1.fog = 0;
        arg0 = func_00207650(arg0, (s32)packet.tag, 0, 0);
    }
    return arg0;
}

void func_001B81E0(void) {
    func_00209D30(func_001B8210(func_00209D20()));
}

s32 func_001B8210(s32 arg0) {
    u8 *state = D_00317490;

    if (D_003181CA == 0) {
        return arg0;
    }
    func_001B8260(arg0, 0, 0, 0x280, 0x1C0, state[0xD3A]);
}

typedef struct {
    u16 count;
    u16 flags;
    u32 padding;
    u64 registers;
} Tag_001B8260;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Color_001B8260;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Vertex_001B8260;

typedef struct {
    u64 tag[2];
    Color_001B8260 color;
    Vertex_001B8260 vertices[2];
} Packet_001B8260;

void func_001B8260(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 x;
    s32 y;
    Packet_001B8260 packet;

    ((Tag_001B8260 *) packet.tag)->flags = 6;
    ((Tag_001B8260 *) packet.tag)->count = 3;
    ((Tag_001B8260 *) packet.tag)->registers = 0x441;
    x = arg1 + 0x6C0;
    y = arg2 + 0x720;
    ((Tag_001B8260 *) packet.tag)->padding = 0;
    func_002086D0(packet.tag, func_00208D00(2));
    packet.color.r = 0xFF;
    packet.color.g = 0xFF;
    packet.color.b = 0xFF;
    packet.color.a = arg5;
    packet.color.q = 1.0f;
    packet.vertices[0].x = x << 4;
    packet.vertices[0].y = y << 4;
    packet.vertices[0].z = 0xFFFFFD;
    packet.vertices[0].fog = 0;
    packet.vertices[1].x = (x + arg3) << 4;
    packet.vertices[1].y = (y + arg4) << 4;
    packet.vertices[1].z = 0xFFFFFD;
    packet.vertices[1].fog = 0;
    arg0 = func_0020A0B0(arg0, 0);
    arg0 = func_00207650(arg0, (s32) &packet, 0, 0);
    func_0020A0B0(arg0, 1);
}

void func_001B83C0(void) {
    func_00209D30(func_001B83F0(func_00209D20()));
}

typedef struct Flags_001B83F0 {
    s8 unused : 4;
    s8 horizontal : 1;
    s8 enabled : 1;
    s8 colored : 1;
    s8 reserved : 1;
} Flags_001B83F0;

typedef struct Draw_001B83F0 {
    u8 pad00[0x43];
    u8 alpha;
    u8 pad44[0x3D];
    Flags_001B83F0 flags;
    u8 pad82[0xE];
} Draw_001B83F0;

s32 func_001B83F0(s32 arg0) {
    extern void func_001CD560();
    extern s32 D_00317B58;
    u8 *state = D_00317490;
    Draw_001B83F0 draw;

    if (D_00317B58 == 0) {
        return arg0;
    }
    if (*(s32 *)(state + 0x6CC) == 0) {
        return arg0;
    }
    if (state[0xD3B] == 0) {
        return arg0;
    }
    func_001CD560(&draw);
    draw.flags.colored = 0;
    draw.alpha = state[0xD3B];
    arg0 = func_001D9A20(arg0);
    func_001D9ED0(0xFFFFFE);
    func_001DA2B0(&draw, 0, -150.0f, 0.0f);
    arg0 = func_001DBD30(func_001DBC40(arg0, *(s32 *)(state + 0x6C8), &draw), (s32)&draw);
    func_001DA2B0(&draw, 0, 150.0f, 0.0f);
    arg0 = func_001DBD30(func_001DBC40(arg0, *(s32 *)(state + 0x6CC), &draw), (s32)&draw);
    return func_001D9E00(arg0);
}

void func_001B8520(s32 arg0) {
    extern s32 func_00216AC0();
    extern s32 func_00215A60();
    extern s32 func_00215C40();
    u8 *state;
    s32 temp_s1;
    s16 *var_s2;
    s16 *var_s3;
    u8 *var_s4;
    s32 var_s5;
    s32 var_s2_2;
    s32 var_v1;
    u8 *var_v0;

    state = D_00317490;
    temp_s1 = func_002158B0(arg0);
    var_s2 = (s16 *)0x01ED0000;
    var_s3 = (s16 *)0x01ED06AC;
    var_s4 = (u8 *)0x01ED06FE;
    var_v1 = func_00214D00(0, 0);
    D_003180E8 = 0xFFFFF8;
    if (var_v1 != 0) {
        var_v0 = D_002CD1F4;
    } else {
        var_v0 = D_002CCB48;
    }
    *(u8 **)(state + 0x6D4) = var_v0;
    *(s32 *)(state + 0x6D8) = 0x01ED0000;
    *(s32 *)(state + 0x6DC) = 0x01ED06AC;
    *(s32 *)(state + 0x6D0) = 0x01ED06FE;
    *(u16 *)(state + 0xC8C) = 0;
    var_s5 = 0;
    do {
        if (func_00216AC0(arg0, var_s5, -1) > 0) {
            *var_s2 = var_s5;
            *(u16 *)(state + 0xC8C) = (u16)(*(u16 *)(state + 0xC8C) + 1);
        } else {
            *var_s2 = 0x3E7;
        }
        var_s5 += 1;
        var_s2++;
    } while (var_s5 < 0x356);
    *(u16 *)(state + 0xC90) = 0;
    *(s16 *)0x01ED06AC = func_002159D0(arg0, temp_s1);
    var_s3++;
    var_s2_2 = 0;
    *(u16 *)(state + 0xC90) = (u16)(*(u16 *)(state + 0xC90) + 1);
    do {
        *var_s3 = func_00215A60(arg0, temp_s1, var_s2_2);
        var_s2_2 += 1;
        var_s3++;
        *(u16 *)(state + 0xC90) = (u16)(*(u16 *)(state + 0xC90) + 1);
    } while (var_s2_2 < 0x28);
    var_v1 = 0;
    do {
        var_v1 += 1;
        *(s8 *)(var_s4 + 2) = 0;
        var_s4 += 4;
    } while (var_v1 < 8);
    *(u16 *)(state + 0xC92) = 0;
    *(u16 *)(state + 0xC94) = 0;
    *(s8 *)(state + 0xCB6) = 0;
    *(s8 *)(state + 0xCB7) = 4;
    *(s8 *)(state + 0xCB8) = 0xA;
    *(s8 *)(state + 0xCB9) = 0;
    *(s8 *)(state + 0xCBA) = 4;
    *(s8 *)(state + 0xCBB) = 0xA;
    *(s8 *)(state + 0xD5D) = 3;
    *(s8 *)(state + 0xD5E) = 0;
    *(s8 *)(state + 0xD5F) = 0;
    *(u16 *)(state + 0xC8A) = 0;
    *(u16 *)(state + 0xC8E) = 0;
    *(u16 *)(state + 0xC96) = 0;
    *(u16 *)(state + 0xC98) = 0;
    *(s8 *)(state + 0xD60) = 0;
    *(s8 *)(state + 0xD61) = 0;
    *(s8 *)(state + 0xD62) = 0;
    *(s8 *)(state + 0xCBC) = 0;
    *(s8 *)(state + 0xCBD) = 0;
    *(s8 *)(state + 0xD5C) = (s8)arg0;
    func_001BA5F0();
    func_001BA610();
    func_00215C40(arg0, temp_s1);
    *(s8 *)(state + 0xD32) = 0;
}

INCLUDE_ASM("asm/nonmatchings/main_039", func_001B8720);

void func_001B8830(void) {

}

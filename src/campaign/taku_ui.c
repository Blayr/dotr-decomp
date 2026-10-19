/* Campaign map: objects, windows, text (Taku_*). */

#include "common.h"

typedef struct {
    s16 x0, y0, x1, y1;
    u8 pad08[8];
    u8 r, g, b, a;
    u8 pad14[12];
    u8 field20, field21;
    s16 field22;
    u16 index;
} Sprite_00217BD0;

typedef struct {
    s16 x, y, width, height;
    u8 pad08[8];
    u16 field10;
    u8 pad12[2];
} Entry_00217BD0;

s32 Taku_Prim_Set_SP1(s32, s16, s16, s16, s16, s16, s16, s16, s16,
                   u8, u8, u8, u8, u8, u16, u8, s16);
struct Sprite_00217CB0;
extern struct Sprite_00217CB0 campaignSprites[]; /* original: tex_uv_data */

/* Draws campaign sprite `src` (its picture from campaignSprites) moved by (dx, dy). */
s32 Taku_Obj_Set(s32 packet, void *src, s16 dx, s16 dy) {
    Sprite_00217BD0 *sprite = src;
    Entry_00217BD0 *entry = &((Entry_00217BD0 *)campaignSprites)[sprite->index];

    return Taku_Prim_Set_SP1(packet, (s16)(sprite->x0 + dx), (s16)(sprite->y0 + dy),
                   (s16)(sprite->x1 + dx), (s16)(sprite->y1 + dy),
                   entry->x, entry->y, entry->width, entry->height,
                   sprite->r, sprite->g, sprite->b, sprite->a,
                   sprite->field20, entry->field10, sprite->field21,
                   sprite->field22);
}

typedef struct Sprite_00217CB0 {
    s16 u;
    s16 v;
    s16 width;
    s16 height;
    u8 pad08[8];
    u16 texture;
    u8 pad12[2];
} Sprite_00217CB0;

typedef struct Source_00217CB0 {
    u8 pad00[0x10];
    u8 r;
    u8 g;
    u8 b;
    u8 a;
    u8 pad14[0xC];
    u8 flags0;
    u8 flags1;
    s16 z;
    u16 sprite;
} Source_00217CB0;

extern Sprite_00217CB0 campaignSprites[]; /* original: tex_uv_data */

/* Draws campaign picture `srcIn` at (x, y) at its own size. */
void Taku_Te_Set(s32 packet, void *srcIn, s16 x, s16 y) {
    Source_00217CB0 *src = srcIn;
    Sprite_00217CB0 *sprite = &campaignSprites[src->sprite];

    Taku_Prim_Set_SP1(packet, x, y, (s16)(x + sprite->width),
                   (s16)(y + sprite->height), sprite->u, sprite->v,
                   sprite->width, sprite->height, src->r, src->g, src->b,
                   src->a, src->flags0, sprite->texture, src->flags1, src->z);
}

typedef struct {
    u16 u : 14;
    u16 reserved_u : 2;
    u16 v : 14;
    u16 reserved_v : 2;
    u8 pad[12];
} Vertex_00217D70;

typedef struct {
    u16 count;
    u16 flags;
    u32 pad;
    u64 registers;
} Header_00217D70;

typedef struct {
    u8 tag[0x10];
    u8 r, g, b, a;
    f32 q;
    u8 vertices[0x20];
    u8 state[0x20];
} Packet_00217D70;

/* Draws a campaign sprite: screen rectangle (x0, y0)-(x1, y1) of texture `texture` at (u, v), in colour (r, g, b,
   a), at `depth`. */
s32 Taku_Prim_Set_SP1(s32 packetIn, s16 x0, s16 y0, s16 x1, s16 y1,
                   s16 u, s16 v, s16 width, s16 height,
                   u8 r, u8 g, u8 b, u8 a, u8 mode,
                   u16 texture, u8 flag, s16 depth) {
    extern void *campaignTextures[];
    extern void TAKU_SP_XYWH(void *, s16, s16, s16, s16, s32, s32);
    Packet_00217D70 packet __attribute__((aligned(8)));

    ExGetMyOT();
    ((Header_00217D70 *)packet.tag)->flags = 0x26;
    ((Header_00217D70 *)packet.tag)->count = 5;
    ((Header_00217D70 *)packet.tag)->registers = 0x42421;
    ((Header_00217D70 *)packet.tag)->pad = 0;
    packet.r = r;
    packet.g = g;
    packet.b = b;
    packet.a = a;
    packet.q = 1.0f;
    TAKU_SP_XYWH(packet.tag, x0, y0, (s16)(x1 - x0), (s16)(y1 - y0), depth + 0xFFFFF8, 0);
    ((Header_00217D70 *)packet.tag)->flags |= 0x800;
    ((Vertex_00217D70 *)packet.vertices)->u = (u * 16) + 8;
    ((Vertex_00217D70 *)packet.vertices)->v = (v * 16) + 8;
    ((Vertex_00217D70 *)(packet.vertices + 0x10))->u = ((u + width) * 16) + 8;
    ((Vertex_00217D70 *)(packet.vertices + 0x10))->v = ((v + height) * 16) + 8;
    ExAssignTexture(packet.tag, campaignTextures[texture], 0);
    ExAssignAlpha(packet.tag, 0x0000008000000044ULL);
    return ExSortPrim_Pipe(packetIn, (s32)packet.tag, 0, 0);
}

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vertex_00217F90;

typedef struct {
    u8 pad0[0x20];
    Vertex_00217F90 first;
    u64 pad1;
    Vertex_00217F90 second;
} Packet_00217F90;

/* Sets a sprite's two corners from (x, y), width x height, at depth `z` and fog `f`. */
void TAKU_SP_XYWH(void *sprite, s32 x, s32 y, s32 width, s32 height, s32 z, s32 f) {
    Packet_00217F90 *packet = sprite;

    packet->first.x = (x + 0x6C0) * 0x10;
    packet->first.y = (y + 0x720) * 0x10;
    packet->second.x = packet->first.x + width * 0x10;
    packet->second.y = packet->first.y + height * 0x10;
    packet->first.z = z;
    packet->second.z = z;
    packet->first.f = f;
    packet->second.f = f;
}

typedef struct {
    s16 x0, y0, x1, y1, x2, y2, x3, y3;
    u8 r, g, b, a;
    u8 pad14[12];
    u8 mode, flag;
    s16 depth;
    u16 texture;
} Sprite_00218020;

typedef struct {
    s16 u0, v0, u1, v1, u2, v2, u3, v3;
    u16 texture;
    u16 pad12;
} Texture_00218020;

void *Taku_Prim_Set_FT4(void *, s16, s16, s16, s16, s16, s16, s16, s16,
                   s16, s16, s16, s16, s16, s16, s16, s16,
                   u8, u8, u8, u8, u8, u16, u8, s16);
void *Taku_Prim_Set_FT4_ST(void *, s16, s16, s16, s16, s16, s16, s16, s16,
                   s16, s16, s16, s16, s16, s16, s16, s16,
                   u8, u8, u8, u8, u8, u16, u8, s16);

/* Draws campaign quad `src` (flat, textured) moved by (x, y), optionally flipped. */
void *Taku_FT4_Set(void *packet, void *src, s16 x, s16 y, u16 flip) {
    extern struct Sprite_00217CB0 campaignSprites[];
    Sprite_00218020 *sprite = src;
    Texture_00218020 *texture = &((Texture_00218020 *)campaignSprites)[sprite->texture];
    s32 flip_u = 0;
    s32 flip_v = 0;

    if (flip == 0) {
        packet = Taku_Prim_Set_FT4(packet,
            sprite->x0 + x, sprite->y0 + y,
            sprite->x1 + x, sprite->y1 + y,
            sprite->x2 + x, sprite->y2 + y,
            sprite->x3 + x, sprite->y3 + y,
            texture->u0, texture->v0, texture->u1, texture->v1,
            texture->u2, texture->v2, texture->u3, texture->v3,
            sprite->r, sprite->g, sprite->b, sprite->a,
            sprite->mode, texture->texture, sprite->flag, sprite->depth);
    } else {
        if (flip == 1) {
            flip_u = 1;
        } else if (flip == 2) {
            flip_v = 1;
        } else if (flip == 3) {
            flip_u = 1;
            flip_v = 1;
        }
        packet = Taku_Prim_Set_FT4_ST(packet,
            sprite->x0 + x, sprite->y0 + y,
            sprite->x1 + x, sprite->y1 + y,
            sprite->x2 + x, sprite->y2 + y,
            sprite->x3 + x, sprite->y3 + y,
            texture->u0 - flip_u, texture->v0 - flip_v,
            texture->u1 - flip_u, texture->v1 - flip_v,
            texture->u2 - flip_u, texture->v2 - flip_v,
            texture->u3 - flip_u, texture->v3 - flip_v,
            sprite->r, sprite->g, sprite->b, sprite->a,
            sprite->mode, texture->texture, sprite->flag, sprite->depth);
    }
    return packet;
}

typedef struct {
    u16 u : 14;
    u16 reserved_u : 2;
    u16 v : 14;
    u16 reserved_v : 2;
    u8 pad[12];
} Vertex_00218340;

typedef struct {
    u16 count;
    u16 flags;
    u32 pad;
    u64 registers;
} Header_00218340;

typedef struct {
    u8 tag[0x10];
    u8 r, g, b, a;
    f32 q;
    u8 vertices[0x40];
    u8 state[0x20];
} Packet_00218340;

/* Draws a flat textured quad with the four corners and texture coordinates given. */
void *Taku_Prim_Set_FT4(void *packetIn, s16 x0, s16 y0, s16 x1, s16 y1,
                    s16 x2, s16 y2, s16 x3, s16 y3,
                    s16 u0, s16 v0, s16 u1, s16 v1,
                    s16 u2, s16 v2, s16 u3, s16 v3,
                    u8 r, u8 g, u8 b, u8 a, u8 mode,
                    u16 texture, u8 flag, s16 depth) {
    extern void TAKU_FT4_XYWH(void *, s16, s16, s32, u8, s16, s16, s32, u8,
                              s16, s16, s32, u8, s16, s16, s32, u8);
    extern void *campaignTextures[];
    Packet_00218340 packet __attribute__((aligned(8)));
    s32 z;

    ExGetMyOT();
    ((Header_00218340 *)packet.tag)->flags = 0x24;
    ((Header_00218340 *)packet.tag)->count = 9;
    ((Header_00218340 *)packet.tag)->registers = 0x0000000424242421ULL;
    ((Header_00218340 *)packet.tag)->pad = 0;
    packet.r = r;
    packet.g = g;
    packet.b = b;
    packet.a = a;
    packet.q = 1.0f;
    z = depth + 0xFFFFF8;
    TAKU_FT4_XYWH(packet.tag, x0, y0, z, 0, x1, y1, z, 0,
                 x2, y2, z, 0, x3, y3, z, 0);
    ((Header_00218340 *)packet.tag)->flags |= 0x800;
    ((Vertex_00218340 *)packet.vertices)->u = (u0 * 16) + 8;
    ((Vertex_00218340 *)packet.vertices)->v = (v0 * 16) + 8;
    ((Vertex_00218340 *)(packet.vertices + 0x10))->u = (u1 * 16) + 8;
    ((Vertex_00218340 *)(packet.vertices + 0x10))->v = (v1 * 16) + 8;
    ((Vertex_00218340 *)(packet.vertices + 0x20))->u = (u2 * 16) + 8;
    ((Vertex_00218340 *)(packet.vertices + 0x20))->v = (v2 * 16) + 8;
    ((Vertex_00218340 *)(packet.vertices + 0x30))->u = (u3 * 16) + 8;
    ((Vertex_00218340 *)(packet.vertices + 0x30))->v = (v3 * 16) + 8;
    ExAssignTexture(packet.tag, campaignTextures[texture], 0);
    ExAssignAlpha(packet.tag, 0x0000008000000088ULL);
    return (void *)ExSortPrim_Pipe((s32)packetIn, (s32) packet.tag, 0, 0);
}

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Color_002185E0;

typedef struct {
    f32 s, t;
    s64 xyz;
} Vertex_002185E0;

typedef struct {
    s16 count;
    s16 flags;
    s32 zero;
    s64 regs;
    Color_002185E0 color;
    Vertex_002185E0 vertex[4];
    u8 padding[0x20];
} Packet_002185E0;

/* Fills a GIF tag. */
static inline void init_002185E0(void *packet) {
    *(s16 *)((u8 *)packet + 2) = 0x24;
    *(s16 *)packet = 9;
    *(s64 *)((u8 *)packet + 8) = 0x424242421LL;
    *(s32 *)((u8 *)packet + 4) = 0;
}

/* Draws a flat textured quad with the four corners and ST texture coordinates given. */
void *Taku_Prim_Set_FT4_ST(void *packetIn, s16 x0, s16 y0, s16 x1, s16 y1,
                    s16 x2, s16 y2, s16 x3, s16 y3,
                    s16 u0, s16 v0, s16 u1, s16 v1,
                    s16 u2, s16 v2, s16 u3, s16 v3,
                    u8 r, u8 g, u8 b, u8 a,
                    u8 unused0, u16 texture, u8 unused1, s16 z) {
    extern void *campaignTextures[];
    extern void TAKU_FT4_XYWH(void *, s16, s16, s32, u8, s16, s16, s32, u8,
                              s16, s16, s32, u8, s16, s16, s32, u8);
    void **textures;
    Packet_002185E0 packet __attribute__((aligned(8)));
    s32 depth;

    textures = campaignTextures;
    ExGetMyOT();
    init_002185E0(&packet);
    packet.color.r = r;
    packet.color.g = g;
    packet.color.b = b;
    packet.color.a = a;
    packet.color.q = 1.0f;
    depth = z + 0xFFFFF8;
    TAKU_FT4_XYWH(&packet, x0, y0, depth, 0, x1, y1, depth,
                  0, x2, y2, depth, 0, x3, y3, depth, 0);
    packet.vertex[0].s = (0.5f + (f32)u0) / 256.0f;
    packet.vertex[0].t = (0.5f + (f32)v0) / 256.0f;
    packet.vertex[1].s = (0.5f + (f32)u1) / 256.0f;
    packet.vertex[1].t = (0.5f + (f32)v1) / 256.0f;
    packet.vertex[2].s = (0.5f + (f32)u2) / 256.0f;
    packet.vertex[2].t = (0.5f + (f32)v2) / 256.0f;
    packet.vertex[3].s = (0.5f + (f32)u3) / 256.0f;
    packet.vertex[3].t = (0.5f + (f32)v3) / 256.0f;
    ExAssignTexture(&packet, textures[texture], 0);
    ExAssignAlpha(&packet, 0x8000000088LL);
    return (void *)ExSortPrim_Pipe((s32)packetIn, (s32)&packet, 0, 0);
}

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
    u64 pad;
} Vertex_00218840;

typedef struct {
    u8 pad[0x20];
    Vertex_00218840 vertices[4];
} Packet_00218840;

/* Sets a flat quad's four corners (x, y, depth, fog). */
void TAKU_FT4_XYWH(void *prim, u16 x0, u16 y0, s32 z0, u8 f0,
                   u16 x1, u16 y1, s32 z1, u8 f1,
                   u16 x2, u16 y2, s32 z2, u8 f2,
                   u16 x3, u16 y3, s32 z3, u8 f3) {
    Packet_00218840 *p = prim;

    p->vertices[0].x = (x0 + 0x6C0) * 0x10;
    p->vertices[0].y = (y0 + 0x720) * 0x10;
    p->vertices[1].x = (x1 + 0x6C0) * 0x10;
    p->vertices[1].y = (y1 + 0x720) * 0x10;
    p->vertices[2].x = (x2 + 0x6C0) * 0x10;
    p->vertices[2].y = (y2 + 0x720) * 0x10;
    p->vertices[3].x = (x3 + 0x6C0) * 0x10;
    p->vertices[3].y = (y3 + 0x720) * 0x10;
    p->vertices[0].z = z0;
    p->vertices[1].z = z1;
    p->vertices[2].z = z2;
    p->vertices[3].z = z3;
    p->vertices[0].f = f0;
    p->vertices[1].f = f1;
    p->vertices[2].f = f2;
    p->vertices[3].f = f3;
}

typedef struct Quad_00218970 {
    s16 x0;
    s16 y0;
    s16 x1;
    s16 y1;
    s16 x2;
    s16 y2;
    s16 x3;
    s16 y3;
    u8 data[17];
    s16 field22;
} Quad_00218970;

s32 Taku_Prim_Set_G4(void *, s16, s16, s16, s16, s16, s16, s16, s16,
                  u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u16,
                  s16);

/* Draws campaign colour quad `src` moved by (x, y). */
s32 Taku_G4_Set(void *packet, void *src, s16 x, s16 y) {
    Quad_00218970 *quad = (Quad_00218970 *)src;

    return Taku_Prim_Set_G4(packet,
        quad->x0 + x, quad->y0 + y,
        quad->x1 + x, quad->y1 + y,
        quad->x2 + x, quad->y2 + y,
        quad->x3 + x, quad->y3 + y,
        quad->data[0], quad->data[1], quad->data[2], quad->data[3],
        quad->data[4], quad->data[5], quad->data[6], quad->data[7],
        quad->data[8], quad->data[9], quad->data[10], quad->data[11],
        quad->data[12], quad->data[13], quad->data[14], quad->data[15],
        quad->data[16], quad->field22);
}

typedef struct {
    s16 x0;
    s16 y0;
    s16 x1;
    s16 y1;
    s16 x2;
    s16 y2;
    s16 x3;
    s16 y3;
    u8 data[17];
    s16 field22;
} Quad_00218AB0;

/* Draws campaign colour quad `src` moved by (x, y) and stretched by (dx, dy). */
s32 Taku_G4_Set2(void *packet, void *src, s16 x, s16 y, s16 dx, s16 dy) {
    Quad_00218AB0 *quad = (Quad_00218AB0 *)src;

    return Taku_Prim_Set_G4(packet,
        quad->x0 + x, quad->y0 + y,
        dx + (quad->x1 + x), dy + (quad->y1 + y),
        quad->x2 + x, quad->y2 + y,
        dx + (quad->x3 + x), dy + (quad->y3 + y),
        quad->data[0], quad->data[1], quad->data[2], quad->data[3],
        quad->data[4], quad->data[5], quad->data[6], quad->data[7],
        quad->data[8], quad->data[9], quad->data[10], quad->data[11],
        quad->data[12], quad->data[13], quad->data[14], quad->data[15],
        quad->data[16], quad->field22);
}

typedef struct {
    u16 count;
    u16 flags;
    u32 padding;
    u64 registers;
} Tag_00218C10;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 xyz;
} Vertex_00218C10;

typedef struct {
    u64 tag[2];
    Vertex_00218C10 vertex[4];
    u64 end;
} Packet_00218C10;

/* Draws a Gouraud-shaded quad with the four corners and colours given. */
s32 Taku_Prim_Set_G4(void *packetIn, s16 x0, s16 y0, s16 x1, s16 y1,
                   s16 x2, s16 y2, s16 x3, s16 y3,
                   u8 r0, u8 g0, u8 b0, u8 a0,
                   u8 r1, u8 g1, u8 b1, u8 a1,
                   u8 r2, u8 g2, u8 b2, u8 a2,
                   u8 r3, u8 g3, u8 b3, u8 a3,
                   u16 mode, s16 z) {
    extern void TAKU_G4_XYWH(void *, s16, s16, s32, u8, s16, s16, s32, u8,
                              s16, s16, s32, u8, s16, s16, s32, u8);
    Packet_00218C10 packet __attribute__((aligned(8)));
    s32 depth;

    ExGetMyOT();
    ((Tag_00218C10 *)packet.tag)->flags = 0x14;
    ((Tag_00218C10 *)packet.tag)->count = 8;
    ((Tag_00218C10 *)packet.tag)->registers = 0x41414141;
    ((Tag_00218C10 *)packet.tag)->padding = 0;
    packet.vertex[0].r = r0;
    packet.vertex[0].g = g0;
    packet.vertex[0].b = b0;
    packet.vertex[0].a = a0;
    packet.vertex[0].q = 1.0f;
    packet.vertex[1].r = r1;
    packet.vertex[1].g = g1;
    packet.vertex[1].b = b1;
    packet.vertex[1].a = a1;
    packet.vertex[1].q = 1.0f;
    packet.vertex[2].r = r2;
    packet.vertex[2].g = g2;
    packet.vertex[2].b = b2;
    packet.vertex[2].a = a2;
    packet.vertex[2].q = 1.0f;
    packet.vertex[3].r = r3;
    packet.vertex[3].g = g3;
    packet.vertex[3].b = b3;
    packet.vertex[3].a = a3;
    packet.vertex[3].q = 1.0f;
    depth = z + 0xFFFFF8;
    TAKU_G4_XYWH(packet.tag, x0, y0, depth, 0, x1, y1, depth, 0,
                  x2, y2, depth, 0, x3, y3, depth, 0);
    switch (mode) {
    case 0:
        ExAssignAlpha(packet.tag, ExGetAlphaVal(0));
        break;
    case 1:
        ExAssignAlpha(packet.tag, ExGetAlphaVal(0));
        break;
    case 2:
        ExAssignAlpha(packet.tag, ExGetAlphaVal(0));
        break;
    case 3:
        ExAssignAlpha(packet.tag, ExGetAlphaVal(2));
        break;
    default:
        ExAssignAlpha(packet.tag, ExGetAlphaVal(0));
        break;
    }
    return ExSortPrim_Pipe((s32)packetIn, (s32)packet.tag, 0, 0);
}

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Vertex_00218E80;

/* Sets a Gouraud quad's four corners (x, y, depth, fog). */
void TAKU_G4_XYWH(void *prim, u16 x0, u16 y0, s32 z0, u8 fog0,
                   u16 x1, u16 y1, s32 z1, u8 fog1,
                   u16 x2, u16 y2, s32 z2, u8 fog2,
                   u16 x3, u16 y3, s32 z3, u8 fog3) {
    Vertex_00218E80 *vertices = (Vertex_00218E80 *)((u8 *)prim + 0x18);

    vertices[0].x = (x0 + 0x6C0) * 0x10;
    vertices[0].y = (y0 + 0x720) * 0x10;
    vertices[2].x = (x1 + 0x6C0) * 0x10;
    vertices[2].y = (y1 + 0x720) * 0x10;
    vertices[4].x = (x2 + 0x6C0) * 0x10;
    vertices[4].y = (y2 + 0x720) * 0x10;
    vertices[6].x = (x3 + 0x6C0) * 0x10;
    vertices[6].y = (y3 + 0x720) * 0x10;
    vertices[0].z = z0;
    vertices[2].z = z1;
    vertices[4].z = z2;
    vertices[6].z = z3;
    vertices[0].fog = fog0;
    vertices[2].fog = fog1;
    vertices[4].fog = fog2;
    vertices[6].fog = fog3;
}

typedef struct {
    s16 x0;
    s16 y0;
    s16 x1;
    s16 y1;
    s16 x2;
    s16 y2;
    s16 x3;
    s16 y3;
    u8 data[17];
    u8 field21;
    s16 field22;
    u16 index;
} Quad_00218FB0;

typedef struct {
    s16 u0;
    s16 v0;
    s16 u1;
    s16 v1;
    s16 u2;
    s16 v2;
    s16 u3;
    s16 v3;
    u16 texture;
    u8 pad12[2];
} Entry_00218FB0;

void Taku_Prim_Set_GT4(void *, s16, s16, s16, s16, s16, s16, s16, s16,
                   s16, s16, s16, s16, s16, s16, s16, s16,
                   u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8,
                   u16, u8, s16);

/* Draws campaign textured colour quad `src` moved by (x, y) and stretched by (dx, dy). */
void Taku_GT4_Set(void *packet, void *src, s16 x, s16 y, s16 dx, s16 dy) {
    Quad_00218FB0 *quad = (Quad_00218FB0 *)src;
    Entry_00218FB0 *entry = &((Entry_00218FB0 *)campaignSprites)[quad->index];

    Taku_Prim_Set_GT4(packet,
        quad->x0 + x, quad->y0 + y,
        dx + (quad->x1 + x), dy + (quad->y1 + y),
        quad->x2 + x, quad->y2 + y,
        dx + (quad->x3 + x), dy + (quad->y3 + y),
        entry->u0, entry->v0, entry->u1, entry->v1,
        entry->u2, entry->v2, entry->u3, entry->v3,
        quad->data[0], quad->data[1], quad->data[2], quad->data[3],
        quad->data[4], quad->data[5], quad->data[6], quad->data[7],
        quad->data[8], quad->data[9], quad->data[10], quad->data[11],
        quad->data[12], quad->data[13], quad->data[14], quad->data[15],
        quad->data[16], entry->texture, quad->field21, quad->field22);
}

typedef struct {
    u8 r, g, b, a;
    f32 q;
    f32 s, t;
    s64 xyz;
} Vertex_00219180;

typedef struct {
    s16 count;
    s16 flags;
    s32 zero;
    s64 regs;
    Vertex_00219180 vertex[4];
    u8 padding[0x20];
} Packet_00219180;

/* Fills a GIF tag. */
static inline void init_00219180(void *packet) {
    *(s16 *)((u8 *)packet + 2) = 0x34;
    *(s16 *)packet = 0xC;
    *(s64 *)((u8 *)packet + 8) = 0x421421421421LL;
    *(s32 *)((u8 *)packet + 4) = 0;
}

/* Draws a Gouraud-shaded textured quad with the four corners, texture coordinates and colours given. */
void Taku_Prim_Set_GT4(void *packetIn, s16 x0, s16 y0, s16 x1, s16 y1,
                   s16 x2, s16 y2, s16 x3, s16 y3,
                   s16 u0, s16 v0, s16 u1, s16 v1,
                   s16 u2, s16 v2, s16 u3, s16 v3,
                   u8 r0, u8 g0, u8 b0, u8 a0,
                   u8 r1, u8 g1, u8 b1, u8 a1,
                   u8 r2, u8 g2, u8 b2, u8 a2,
                   u8 r3, u8 g3, u8 b3, u8 a3,
                   u8 unused0, u16 texture, u8 unused1, s16 z) {
    extern void *campaignTextures[];
    extern s32 SzDuel_TrimUnitDir2();
    void **textures;
    Packet_00219180 packet;
    f32 width;
    f32 height;
    s32 depth;

    textures = campaignTextures;
    ExGetMyOT();
    init_00219180(&packet);
    packet.vertex[0].r = r0;
    packet.vertex[0].g = g0;
    packet.vertex[0].b = b0;
    packet.vertex[0].a = a0;
    packet.vertex[0].q = 1.0f;
    packet.vertex[1].r = r1;
    packet.vertex[1].g = g1;
    packet.vertex[1].b = b1;
    packet.vertex[1].a = a1;
    packet.vertex[1].q = 1.0f;
    packet.vertex[2].r = r2;
    packet.vertex[2].g = g2;
    packet.vertex[2].b = b2;
    packet.vertex[2].a = a2;
    packet.vertex[2].q = 1.0f;
    packet.vertex[3].r = r3;
    packet.vertex[3].g = g3;
    packet.vertex[3].b = b3;
    packet.vertex[3].a = a3;
    packet.vertex[3].q = 1.0f;
    depth = z + 0xFFFFF8;
    TAKU_GT4_XYWH(&packet, x0, y0, depth, 0, x1, y1, depth,
                  0, x2, y2, depth, 0, x3, y3, depth, 0);
    if ((u1 - (s16)u0) < 0x101) {
        width = 256.0f;
    } else {
        width = 512.0f;
    }
    if ((v2 - v0) < 0x101) {
        height = 256.0f;
    } else {
        height = 512.0f;
    }
    packet.vertex[0].s = (0.5f + (f32)u0) / width;
    packet.vertex[0].t = (0.5f + (f32)v0) / height;
    packet.vertex[1].s = (0.5f + (f32)u1) / width;
    packet.vertex[1].t = (0.5f + (f32)v1) / height;
    packet.vertex[2].s = (0.5f + (f32)u2) / width;
    packet.vertex[2].t = (0.5f + (f32)v2) / height;
    packet.vertex[3].s = (0.5f + (f32)u3) / width;
    packet.vertex[3].t = (0.5f + (f32)v3) / height;
    ExAssignTexture(&packet, textures[texture], 0);
    ExAssignAlpha(&packet, ExGetAlphaVal(0));
    ExSortPrim_Pipe((s32)packetIn, (s32)&packet, 0, 0);
}

typedef union {
    u64 value;
    struct {
        u16 x;
        u16 y;
        u8 z[3];
        u8 fog;
    } coords;
    struct {
        u64 xy : 32;
        u64 z : 24;
        u64 fog : 8;
    } bits;
} XYZ_002194B0;

typedef struct {
    u8 header[0x20];
    XYZ_002194B0 v0;
    u8 pad28[0x10];
    XYZ_002194B0 v1;
    u8 pad40[0x10];
    XYZ_002194B0 v2;
    u8 pad58[0x10];
    XYZ_002194B0 v3;
} Packet_002194B0;

/* Sets a Gouraud textured quad's four corners (x, y, depth, fog). */
void TAKU_GT4_XYWH(void *prim, s16 x0, s16 y0, s32 z0, u8 fog0,
                   s16 x1, s16 y1, s32 z1, u8 fog1,
                   s16 x2, s16 y2, s32 z2, u8 fog2,
                   s16 x3, s16 y3, s32 z3, u8 fog3) {
    Packet_002194B0 *packet = prim;

    packet->v0.coords.x = (x0 + 0x6C0) * 0x10;
    packet->v0.coords.y = (y0 + 0x720) * 0x10;
    packet->v1.coords.x = (x1 + 0x6C0) * 0x10;
    packet->v1.coords.y = (y1 + 0x720) * 0x10;
    packet->v2.coords.x = (x2 + 0x6C0) * 0x10;
    packet->v2.coords.y = (y2 + 0x720) * 0x10;
    packet->v3.coords.x = (x3 + 0x6C0) * 0x10;
    packet->v3.coords.y = (y3 + 0x720) * 0x10;
    packet->v0.bits.z = z0;
    packet->v1.bits.z = z1;
    packet->v2.bits.z = z2;
    packet->v3.bits.z = z3;
    packet->v0.coords.fog = fog0;
    packet->v1.coords.fog = fog1;
    packet->v2.coords.fog = fog2;
    packet->v3.coords.fog = fog3;
}

#include "campaign.h"

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

extern Tex_002195E0 campaignSprites_2[]; /* original: tex_uv_data */
extern u16 windowTextureTable[][0x100]; /* original: window_tex_no */

/* Draws one window piece. */
static inline s32 sprite_002195E0(s32 p, Prim_002195E0 *s, s16 dx, s16 dy) {
    extern s32 func_00217D70(s32, s16, s16, s16, s16, s16, s16, s16, s16,
                               u8, u8, u8, u8, u8, u16, u8, s16);
    Tex_002195E0 *e = &campaignSprites_2[s->index];

    return func_00217D70(p, (s16)(s->x0 + dx), (s16)(s->y0 + dy),
                         (s16)(s->x1 + dx), (s16)(s->y1 + dy),
                         e->u, e->v, e->width, e->height,
                         s->data[0], s->data[1], s->data[2], s->data[3],
                         s->data[16], e->texture, s->flag, s->depth);
}

/* Draws one window piece mirrored. */
static inline s32 flipped_002195E0(s32 p, Prim_002195E0 *s, s16 dx, s16 dy) {
    extern s32 func_00217D70(s32, s16, s16, s16, s16, s16, s16, s16, s16,
                               u8, u8, u8, u8, u8, u16, u8, s16);
    Tex_002195E0 *e = &campaignSprites_2[s->index];

    return func_00217D70(p, (s16)(s->x0 + dx), (s16)(s->y0 + dy),
                         (s16)(s->x1 + dx), (s16)(s->y1 + dy),
                         e->u, e->v - 1, e->width, e->height,
                         s->data[0], s->data[1], s->data[2], s->data[3],
                         s->data[16], e->texture, s->flag, s->depth);
}

/* Draws one window quad. */
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

/* Draws a campaign window frame for rectangle `rect_arg` in `style`, moved by (dx, dy), at `depth`, with `alpha`. */
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
        t = (campaignWork.windowOpen * 0x60) >> 8;
        g = t;
        r = 0x60 - t;
        b = g;
    } else if (style == 11) {
        t = (campaignWork.windowOpen * 0x60) >> 8;
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
            q.index = windowTextureTable[rect->kind][i];
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
                    e = &campaignSprites_2[q.index];
                    y0 = rect->y0;
                    x1 = x0 + e->width;
                    y1 = y0 + e->height;
                } else if (i == 1) {
                    y0 = rect->y0;
                    x1 = rect->x1;
                    e = &campaignSprites_2[q.index];
                    x0 = x1 - e->width;
                    y1 = y0 + e->height;
                } else if (i == 2) {
                    x0 = rect->x0;
                    y1 = rect->y1;
                    e = &campaignSprites_2[q.index];
                    x1 = x0 + e->width;
                    y0 = y1 - e->height;
                } else {
                    x1 = rect->x1;
                    y1 = rect->y1;
                    e = &campaignSprites_2[q.index];
                    x0 = x1 - e->width;
                    y0 = y1 - e->height;
                }
            } else {
                c = windowTextureTable[rect->kind][0];
                if (i == 4) {
                    e = &campaignSprites_2[c];
                    w = e->width;
                    x0 = rect->x0 + w;
                    x1 = rect->x1 - w;
                    y0 = rect->y0;
                    y1 = y0 + e->height;
                } else if (i == 5) {
                    y1 = rect->y1;
                    e = &campaignSprites_2[c];
                    w = e->width;
                    x0 = rect->x0 + w;
                    x1 = rect->x1 - w;
                    y0 = y1 - e->height;
                } else if (i == 6) {
                    x0 = rect->x0;
                    e = &campaignSprites_2[c];
                    x1 = x0 + e->width;
                    y0 = rect->y0 + e->height;
                    y1 = rect->y1 - e->height;
                } else {
                    e = &campaignSprites_2[c];
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
            q.index = windowTextureTable[rect->kind][i];
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
                    e = &campaignSprites_2[q.index];
                    x1 = x0 + e->width;
                    y1 = y0 + e->height;
                } else {
                    x1 = rect->x1;
                    y1 = rect->y1;
                    e = &campaignSprites_2[q.index];
                    x0 = x1 - e->width;
                    y0 = y1 - e->height;
                }
            } else {
                w = campaignSprites_2[(s16)windowTextureTable[rect->kind][0]].width;
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
            q.index = windowTextureTable[rect->kind][i];
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
                    e = &campaignSprites_2[q.index];
                    x1 = x0 + e->width;
                    y1 = y0 + e->height;
                } else if (i == 1) {
                    x1 = rect->x1;
                    y1 = rect->y1;
                    e = &campaignSprites_2[q.index];
                    x0 = x1 - e->width;
                    y0 = y1 - e->height;
                } else {
                    w = campaignSprites_2[(s16)windowTextureTable[rect->kind][0]].width;
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
                        q.index = windowTextureTable[rect->kind][2];
                        y0 = rect->y0;
                        x0 = rect->x0;
                        e = &campaignSprites_2[q.index];
                        x1 = x0 + e->width;
                        y1 = y0 + e->height;
                    } else {
                        q.index = windowTextureTable[rect->kind][3];
                        y0 = rect->y0;
                        x1 = rect->x1;
                        e = &campaignSprites_2[q.index];
                        x0 = x1 - e->width;
                        y1 = y0 + e->height;
                    }
                } else {
                    c = windowTextureTable[rect->kind][0];
                    if (i == 2) {
                        q.index = windowTextureTable[rect->kind][5];
                        y0 = rect->y0;
                        e = &campaignSprites_2[c];
                        w = e->width;
                        x0 = rect->x0 + w;
                        x1 = rect->x1 - w;
                        y1 = y0 + e->height;
                    } else if (i == 3) {
                        q.index = windowTextureTable[rect->kind][6];
                        x0 = rect->x0;
                        e = &campaignSprites_2[c];
                        x1 = x0 + e->width;
                        y0 = rect->y0 + e->height;
                        y1 = rect->y1;
                    } else {
                        q.index = windowTextureTable[rect->kind][7];
                        e = &campaignSprites_2[c];
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
                        q.index = windowTextureTable[rect->kind][0];
                        x0 = rect->x0;
                        y0 = rect->y0;
                        e = &campaignSprites_2[q.index];
                        x1 = x0 + e->width;
                        y1 = y0 + e->height;
                    } else {
                        q.index = windowTextureTable[rect->kind][1];
                        y0 = rect->y0;
                        x1 = rect->x1;
                        e = &campaignSprites_2[q.index];
                        x0 = x1 - e->width;
                        y1 = y0 + e->height;
                    }
                } else {
                    c = windowTextureTable[rect->kind][0];
                    if (i == 2) {
                        q.index = windowTextureTable[rect->kind][4];
                        e = &campaignSprites_2[c];
                        w = e->width;
                        x0 = rect->x0 + w;
                        x1 = rect->x1 - w;
                        y0 = rect->y0;
                        y1 = y0 + e->height;
                    } else if (i == 3) {
                        q.index = windowTextureTable[rect->kind][6];
                        x0 = rect->x0;
                        e = &campaignSprites_2[c];
                        x1 = x0 + e->width;
                        y0 = rect->y0 + e->height;
                        y1 = rect->y1;
                    } else {
                        q.index = windowTextureTable[rect->kind][7];
                        e = &campaignSprites_2[c];
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
                        q.index = windowTextureTable[rect->kind][0];
                        x0 = rect->x0;
                        y1 = rect->y1;
                        e = &campaignSprites_2[q.index];
                        x1 = x0 + e->width;
                        y0 = y1 - e->height;
                    } else if (i == 1) {
                        q.index = windowTextureTable[rect->kind][1];
                        x1 = rect->x1;
                        y1 = rect->y1;
                        e = &campaignSprites_2[q.index];
                        x0 = x1 - e->width;
                        y0 = y1 - e->height;
                    }
                } else {
                    c = windowTextureTable[rect->kind][0];
                    if (i == 2) {
                        q.index = windowTextureTable[rect->kind][4];
                        e = &campaignSprites_2[c];
                        w = e->width;
                        y1 = rect->y1;
                        x0 = rect->x0 + w;
                        x1 = rect->x1 - w;
                        y0 = y1 - e->height;
                    } else if (i == 3) {
                        q.index = windowTextureTable[rect->kind][6];
                        e = &campaignSprites_2[c];
                        x0 = rect->x0;
                        y0 = rect->y0;
                        x1 = x0 + e->width;
                        y1 = rect->y1 - e->height;
                    } else {
                        q.index = windowTextureTable[rect->kind][7];
                        e = &campaignSprites_2[c];
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
                        q.index = windowTextureTable[rect->kind][2];
                        x0 = rect->x0;
                        y1 = rect->y1;
                        e = &campaignSprites_2[q.index];
                        x1 = x0 + e->width;
                        y0 = y1 - e->height;
                    } else {
                        q.index = windowTextureTable[rect->kind][3];
                        x1 = rect->x1;
                        y1 = rect->y1;
                        e = &campaignSprites_2[q.index];
                        x0 = x1 - e->width;
                        y0 = y1 - e->height;
                    }
                } else {
                    c = windowTextureTable[rect->kind][0];
                    if (i == 2) {
                        q.index = windowTextureTable[rect->kind][5];
                        e = &campaignSprites_2[c];
                        w = e->width;
                        y1 = rect->y1;
                        x0 = rect->x0 + w;
                        x1 = rect->x1 - w;
                        y0 = y1 - e->height;
                    } else if (i == 3) {
                        q.index = windowTextureTable[rect->kind][6];
                        e = &campaignSprites_2[c];
                        x0 = rect->x0;
                        y0 = rect->y0;
                        x1 = x0 + e->width;
                        y1 = rect->y1 - e->height;
                    } else {
                        q.index = windowTextureTable[rect->kind][7];
                        e = &campaignSprites_2[c];
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

/* Sets a campaign coordinate record to scale 1, no rotation, no move. */
void Taku_Coord_Init(void *coord) {
    f32 *values = coord;

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

typedef struct {
    f32 m[4][4];
} Matrix_0021BB20;

/* Builds a campaign coordinate record's matrix: world-to-screen times its scale, rotation and position. */
void Taku_Coord_Set(u8 *coord) {
    Matrix_0021BB20 matrix;

    RhView_GetWorldScreenMatrix(coord + 0x30);
    RhGeom_GetScaleRotXYZTransMatrix(&matrix, coord, coord + 0x10, coord + 0x20);
    RhGeom_MulMatrix((s32)(coord + 0x30), &matrix);
}

/* Copies a 3-float vector. */
void Taku_Vector_Set(void *dst, void *src) {
    ((f32 *)dst)[0] = ((f32 *)src)[0];
    ((f32 *)dst)[1] = ((f32 *)src)[1];
    ((f32 *)dst)[2] = ((f32 *)src)[2];
}

/* The screen position of world point `point` on the campaign map into (outX, outY); -1 when off screen. */
void Taku_3D_2D_Set(s32 *outX, s32 *outY, s32 point) {
    u16 projected[6];
    s32 depth;

    if (Ex3d_RotTransPers(point, D_00299F90, projected, &depth) != 0) {
        *outX = ((s32) projected[0] >> 4) - 0x6C0;
        *outY = ((s32) projected[1] >> 4) - 0x720;
    } else {
        *outX = -1;
        *outY = -1;
    }
}

/* Builds a smooth path through `count` points (a cubic spline), `spacing` apart, into outX / outY. */
void Taku_spline2(f32 *outX, f32 *outY, s16 *outCount, f32 *points,
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
            tri_diag(lower, diagonal, upper, rhs[dimension], slopes[dimension], count);
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

/* The slope term of a cubic spline at a point from its neighbours and intervals. */
f32 func_0021C320(f32 fparg0, f32 fparg1, f32 fparg2, f32 fparg3, f32 fparg4) {
    return 3.0f * (((fparg4 * (fparg1 - fparg0)) / fparg3) + ((fparg3 * (fparg2 - fparg1)) / fparg4));
}

/* Solves a tridiagonal system of n equations (for the spline). */
void tri_diag(f32 *a, f32 *b, f32 *c, f32 *r, f32 *u, s32 n) {
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

/* Draws message `msg` in text slot `slot` at (x, y) in colour `color` (loads, draws and frees it). (original: Taku_Bunsyou_Set) */
s32 Taku_Text_Set(s32 packet, s32 slot, s32 msg, s64 x, s64 y, s32 arg5, s32 color) {
    s32 result;
    s32 object;

    object = RhText_SetTextureFlush(SzMsg_LoadFont_Pipe(packet, slot, msg, 0, slot * 22));
    SzMsg_GetInfo(slot);
    result = SzMsg_DrawRatioX_Pipe(object, slot, (s16)x, (s16)y, 1.0f, 1.0f, color, SzMsg_DrawRect_Pipe);
    SzMsg_Free(slot);
    return result;
}

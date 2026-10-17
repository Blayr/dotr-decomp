#include "common.h"

typedef struct {
    s8 enabled : 1;
} Flags_00217A10;

extern Flags_00217A10 D_0034F6E8;

/* Stops the music, fading it out over `fade` frames (0: at once). */
s32 SzSound_StopBGM(s64 fade) {
    if (D_0034F6E8.enabled == 0) {
        return 0;
    }
    if (fade > 0) {
        SD_BGMFadeOut((s16) fade);
    } else {
        SD_BGMStop();
    }
    return 1;
}

typedef struct {
    s8 active : 1;
    s8 mode : 1;
} Flags_00217A70;

typedef struct {
    u8 pad[8];
    Flags_00217A70 flags;
} State_00217A70;

extern State_00217A70 soundState; /* original: gSzSound_sl */

/* Sets the sound output: stereo (`stereo` set) or mono. */
s32 SzSound_SetOutput(s32 stereo) {
    State_00217A70 *state = &soundState;

    if (D_0034F6E8.enabled == 0) {
        return 0;
    }
    state->flags.mode = (s8)(stereo ? 1 : 0);
    SD_SetOutputType(state->flags.mode ? 0 : 1);
    return 1;
}

/* Starts the memory allocator (nothing to do). */
void SzMem_Init(void) {
    func_00197C18(func_00197BC0(0x01FFEFF0 - (s32)&D_1FE0000));
}

/* Allocates `size` bytes, 16-byte aligned. */
s32 SzMem_Alloc(s32 size) {
    return (s32)func_00197990(0x10, size);
}

/* Frees allocation `block`. */
void SzMem_Free(s32 block) {
    func_00197C18(block);
}

/* A newly allocated copy of `str`, or 0. */
char *SzMem_StrDup(char *str) {
    char *copy;

    if (str == 0) {
        return 0;
    }
    copy = func_00197990(0x10, func_0019BEF0(str) + 1);
    if (copy == 0) {
        return 0;
    }
    func_0019BDD8(copy, str);
    return copy;
}

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

void Taku_Prim_Set_SP1(s32, s16, s16, s16, s16, s16, s16, s16, s16,
                   u8, u8, u8, u8, u8, u16, u8, s16);
struct Sprite_00217CB0;
extern struct Sprite_00217CB0 campaignSprites[]; /* original: tex_uv_data */

/* Draws campaign sprite `src` (its picture from campaignSprites) moved by (dx, dy). */
void Taku_Obj_Set(s32 packet, void *src, s16 dx, s16 dy) {
    Sprite_00217BD0 *sprite = src;
    Entry_00217BD0 *entry = &((Entry_00217BD0 *)campaignSprites)[sprite->index];

    Taku_Prim_Set_SP1(packet, (s16)(sprite->x0 + dx), (s16)(sprite->y0 + dy),
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

void Taku_Prim_Set_SP1(s32, s16, s16, s16, s16, s16, s16, s16, s16,
                   u8, u8, u8, u8, u8, u16, u8, s16);

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
void Taku_Prim_Set_SP1(s32 packetIn, s16 x0, s16 y0, s16 x1, s16 y1,
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
    ExSortPrim_Pipe(packetIn, (s32)packet.tag, 0, 0);
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

void Taku_Prim_Set_G4(void *, s16, s16, s16, s16, s16, s16, s16, s16,
                  u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u16,
                  s16);

/* Draws campaign colour quad `src` moved by (x, y). */
void Taku_G4_Set(void *packet, void *src, s16 x, s16 y) {
    Quad_00218970 *quad = (Quad_00218970 *)src;

    Taku_Prim_Set_G4(packet,
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

void Taku_Prim_Set_G4(void *, s16, s16, s16, s16, s16, s16, s16, s16,
                  u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u16,
                  s16);

/* Draws campaign colour quad `src` moved by (x, y) and stretched by (dx, dy). */
void Taku_G4_Set2(void *packet, void *src, s16 x, s16 y, s16 dx, s16 dy) {
    Quad_00218AB0 *quad = (Quad_00218AB0 *)src;

    Taku_Prim_Set_G4(packet,
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
void Taku_Prim_Set_G4(void *packetIn, s16 x0, s16 y0, s16 x1, s16 y1,
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
    ExSortPrim_Pipe((s32)packetIn, (s32)packet.tag, 0, 0);
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

struct Sprite_00217CB0;
extern struct Sprite_00217CB0 campaignSprites[]; /* original: tex_uv_data */

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

#include "common.h"

typedef struct {
    s8 enabled : 1;
} Flags_00217A10;

void func_0010A010(void);
void func_0010A090(s16);
extern Flags_00217A10 D_0034F6E8;

s32 func_00217A10(s64 arg0) {
    if (D_0034F6E8.enabled == 0) {
        return 0;
    }
    if (arg0 > 0) {
        func_0010A090((s16) arg0);
    } else {
        func_0010A010();
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_061", func_00217A70);

void func_00217B00(void) {
    func_00197C18(func_00197BC0(0x01FFEFF0 - (s32)&D_1FE0000));
}

INCLUDE_ASM("asm/nonmatchings/main_061", func_00217B40);

void func_00217B50(void) {
    func_00197C18();
}

char *func_00217B60(char *arg0) {
    char *temp_v0;

    if (arg0 == 0) {
        return 0;
    }
    temp_v0 = func_00197990(0x10, func_0019BEF0(arg0) + 1);
    if (temp_v0 == 0) {
        return 0;
    }
    func_0019BDD8(temp_v0, arg0);
    return temp_v0;
}

INCLUDE_ASM("asm/nonmatchings/main_061", func_00217BD0);

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

extern Sprite_00217CB0 D_002950A0[];

void func_00217D70(s32, s16, s16, s16, s16, s16, s16, s16, s16,
                   u8, u8, u8, u8, u8, u16, u8, s16);

void func_00217CB0(s32 arg0, void *arg1, s16 x, s16 y) {
    Source_00217CB0 *src = arg1;
    Sprite_00217CB0 *sprite = &D_002950A0[src->sprite];

    func_00217D70(arg0, x, y, (s16)(x + sprite->width),
                   (s16)(y + sprite->height), sprite->u, sprite->v,
                   sprite->width, sprite->height, src->r, src->g, src->b,
                   src->a, src->flags0, sprite->texture, src->flags1, src->z);
}

INCLUDE_ASM("asm/nonmatchings/main_061", func_00217D70);

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

void func_00217F90(void *arg0, s32 x, s32 y, s32 width, s32 height, s32 z, s32 f) {
    Packet_00217F90 *packet = arg0;

    packet->first.x = (x + 0x6C0) * 0x10;
    packet->first.y = (y + 0x720) * 0x10;
    packet->second.x = packet->first.x + width * 0x10;
    packet->second.y = packet->first.y + height * 0x10;
    packet->first.z = z;
    packet->second.z = z;
    packet->first.f = f;
    packet->second.f = f;
}

INCLUDE_ASM("asm/nonmatchings/main_061", func_00218020);

INCLUDE_ASM("asm/nonmatchings/main_061", func_00218340);

INCLUDE_ASM("asm/nonmatchings/main_061", func_002185E0);

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

void func_00218840(void *arg0, u16 x0, u16 y0, s32 z0, u8 f0,
                   u16 x1, u16 y1, s32 z1, u8 f1,
                   u16 x2, u16 y2, s32 z2, u8 f2,
                   u16 x3, u16 y3, s32 z3, u8 f3) {
    Packet_00218840 *p = arg0;

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

void func_00218C10(void *, s16, s16, s16, s16, s16, s16, s16, s16,
                  u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8,
                  s16);

void func_00218970(void *arg0, void *src, s16 x, s16 y) {
    Quad_00218970 *quad = (Quad_00218970 *)src;

    func_00218C10(arg0,
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

void func_00218C10(void *, s16, s16, s16, s16, s16, s16, s16, s16,
                  u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8,
                  s16);

void func_00218AB0(void *arg0, void *src, s16 x, s16 y, s16 dx, s16 dy) {
    Quad_00218AB0 *quad = (Quad_00218AB0 *)src;

    func_00218C10(arg0,
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

INCLUDE_ASM("asm/nonmatchings/main_061", func_00218C10);

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Vertex_00218E80;

void func_00218E80(void *arg0, u16 x0, u16 y0, s32 z0, u8 fog0,
                   u16 x1, u16 y1, s32 z1, u8 fog1,
                   u16 x2, u16 y2, s32 z2, u8 fog2,
                   u16 x3, u16 y3, s32 z3, u8 fog3) {
    Vertex_00218E80 *vertices = (Vertex_00218E80 *)((u8 *)arg0 + 0x18);

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

INCLUDE_ASM("asm/nonmatchings/main_061", func_00218FB0);

INCLUDE_ASM("asm/nonmatchings/main_061", func_00219180);

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

void func_002194B0(void *arg0, u16 x0, u16 y0, s32 z0, u8 fog0,
                   u16 x1, u16 y1, s32 z1, u8 fog1,
                   u16 x2, u16 y2, s32 z2, u8 fog2,
                   u16 x3, u16 y3, s32 z3, u8 fog3) {
    Packet_002194B0 *packet = arg0;

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

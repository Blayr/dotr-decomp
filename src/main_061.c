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

INCLUDE_ASM("asm/nonmatchings/main_061", func_00218840);

INCLUDE_ASM("asm/nonmatchings/main_061", func_00218970);

INCLUDE_ASM("asm/nonmatchings/main_061", func_00218AB0);

INCLUDE_ASM("asm/nonmatchings/main_061", func_00218C10);

INCLUDE_ASM("asm/nonmatchings/main_061", func_00218E80);

INCLUDE_ASM("asm/nonmatchings/main_061", func_00218FB0);

INCLUDE_ASM("asm/nonmatchings/main_061", func_00219180);

INCLUDE_ASM("asm/nonmatchings/main_061", func_002194B0);

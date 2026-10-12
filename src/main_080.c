#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_080", func_0027F700);

INCLUDE_ASM("asm/nonmatchings/main_080", func_0027F830);

INCLUDE_ASM("asm/nonmatchings/main_080", func_0027F890);

INCLUDE_ASM("asm/nonmatchings/main_080", func_0027F8B4);

INCLUDE_ASM("asm/nonmatchings/main_080", func_0027F8D8);

INCLUDE_ASM("asm/nonmatchings/main_080", func_0027F8FC);

INCLUDE_ASM("asm/nonmatchings/main_080", func_0027FA30);

INCLUDE_ASM("asm/nonmatchings/main_080", func_0027FAB0);

INCLUDE_ASM("asm/nonmatchings/main_080", func_0027FC20);

INCLUDE_ASM("asm/nonmatchings/main_080", func_0027FFC0);

typedef struct Constants_00280060 {
    f32 values[6];
} Constants_00280060;

typedef union Position_00280060 {
    struct {
        u16 x, y;
        u32 packed;
    } coordinates;
    struct {
        u64 x : 16;
        u64 y : 16;
        u64 z : 24;
        u64 adc : 8;
    } bits;
} Position_00280060;

typedef struct Vertex_00280060 {
    u8 r, g, b, a;
    f32 q;
    Position_00280060 position;
} Vertex_00280060;

typedef struct Packet_00280060 {
    u16 count;
    u16 primitive;
    u32 flags;
    u64 registers;
    Vertex_00280060 vertex[3];
    u64 padding;
} Packet_00280060;

typedef struct Particle_00280060 {
    u8 age;
    u8 padding1;
    u8 duration;
    u8 padding3;
    u8 flags;
    u8 padding5[2];
    u8 divisions;
    u8 b, g, r, paddingB;
    u8 centerB, centerG, centerR, alpha;
    f32 radius;
    f32 speed;
    u8 padding18[8];
    f32 x, y;
    u8 padding28[8];
} Particle_00280060;

extern Constants_00280060 D_002B8760;
extern s32 D_00351228;

#pragma optimization_level 0

s32 func_00280060(void *arg0, s32 arg1) {
    extern s32 func_001A22C0(f32);
    extern s32 func_00207650(s32, void *, s32, s32);
    Particle_00280060 *particle = arg0;
    Constants_00280060 constants = D_002B8760;
    Packet_00280060 packet;
    f32 depth;
    f32 previousX, previousY;
    f32 offsetX, offsetY;
    f32 angleStep;
    s32 j;
    u8 *header;
    s32 divisions;
    s32 i;
    u8 remaining;

    for (i = 0; i < arg1; i++) {
        if (i != 0) {
            particle++;
        }
        header = (u8 *)particle;
        if (func_00101AF0(header) != 0) {
            particle->radius += particle->speed;
            if (header[7] > 9) {
                divisions = 9;
            } else {
                divisions = header[7];
            }
            angleStep = 90.0f / (f32)divisions;
            if (header[4] & 0x80) {
                packet.vertex[0].position.bits.z = packet.vertex[1].position.bits.z = packet.vertex[2].position.bits.z = 0xFFFFFE;
                depth = 0.0f;
            } else {
                packet.vertex[0].position.bits.z = packet.vertex[1].position.bits.z = packet.vertex[2].position.bits.z = 0xFFFFF8;
                depth = -1.0f;
            }
            ((u16 *)&packet)[1] = 0x13;
            ((u16 *)&packet)[0] = 6;
            ((u64 *)&packet)[1] = 0x414141;
            ((u32 *)&packet)[1] = 0;
            packet.vertex[0].r = particle->centerR;
            packet.vertex[1].r = packet.vertex[2].r = particle->r;
            packet.vertex[0].g = particle->centerG;
            packet.vertex[1].g = packet.vertex[2].g = particle->g;
            packet.vertex[0].b = particle->centerB;
            packet.vertex[1].b = packet.vertex[2].b = particle->b;
            packet.vertex[0].q = packet.vertex[1].q = packet.vertex[2].q = 1.0f;
            func_002086D0(&packet, 0x48);
            packet.vertex[0].a = particle->alpha;
            packet.vertex[1].a = packet.vertex[2].a = 0;
            if (!(header[4] & 0x40)) {
                if (header[0] < 8) {
                    packet.vertex[0].a = (u8)((particle->alpha >> 3) * header[0]);
                } else {
                    remaining = (u8)(header[2] - header[0]);
                    if (remaining < 8) {
                        packet.vertex[0].a = (u8)((particle->alpha >> 3) * remaining);
                    }
                }
            }
            offsetX = particle->radius * func_001A6898(0.0f);
            offsetY = particle->radius * func_001A6A88(0.0f);
            packet.vertex[0].position.bits.adc = packet.vertex[1].position.bits.adc = packet.vertex[2].position.bits.adc = 1;
            for (j = 1; j < divisions * 4 + 1; j++) {
                previousX = offsetX;
                previousY = offsetY;
                offsetX = particle->radius * func_001A6898((3.1415927f * (angleStep * (f32)j)) / 180.0f);
                offsetY = particle->radius * func_001A6A88((3.1415927f * (angleStep * (f32)j)) / 180.0f);
                packet.vertex[0].position.coordinates.x = (u16)(func_001A22C0(particle->x) << 4);
                packet.vertex[0].position.coordinates.y = (u16)(func_001A22C0(particle->y) << 4);
                packet.vertex[1].position.coordinates.x = (u16)(func_001A22C0(particle->x + previousX) << 4);
                packet.vertex[1].position.coordinates.y = (u16)(func_001A22C0(particle->y + previousY) << 4);
                packet.vertex[2].position.coordinates.x = (u16)(func_001A22C0(particle->x + offsetX) << 4);
                packet.vertex[2].position.coordinates.y = (u16)(func_001A22C0(particle->y + offsetY) << 4);
                D_00351228 = func_00207650(D_00351228, &packet, 0, func_001A23B0(depth));
            }
        }
    }
    return 1;
}

#pragma optimization_level reset

typedef struct {
    u8 state;
    u8 padding01[9];
    u8 enabled;
    u8 padding0B[0x2F];
} Flags_00280670;

typedef struct {
    u8 padding00[4];
    u8 intensity;
    u8 padding05[2];
    u8 mode;
    u8 field08;
    u8 field09;
    u8 field0A;
    u8 padding0B;
    u8 red;
    u8 green;
    u8 blue;
    u8 alpha;
    f32 width;
    f32 height;
    u8 padding18[8];
    f32 x;
    f32 y;
    u8 padding28[8];
} Object_00280670;

extern Object_00280670 D_00351180[];
extern Flags_00280670 D_00351240[];
extern u8 D_00351241;
extern u8 D_00351242;
extern s16 D_00351246;

#pragma optimization_level 0

void func_00280670(void) {
    extern s32 func_00101AD0();
    s32 i;

    for (i = 0; i < 3; i++) {
        D_00351240[i].enabled = 1;
    }
    D_00351240[0].state = 1;
    func_00217710(0, 0x1E);
    for (i = 0; i < 3; i++) {
        func_00101AD0(&D_00351180[i], 0x28, 0, 0xFF);
        D_00351180[i].intensity = 0x80;
        D_00351180[i].mode = 9;
        D_00351180[i].width = 40.0f;
        D_00351180[i].height = 0.0f;
        D_00351180[i].blue = D_00351180[i].green = D_00351180[i].red = D_00351180[i].alpha = 0xF0;
        D_00351180[i].field0A = 0x40;
        D_00351180[i].field09 = 0x10;
        D_00351180[i].field08 = 0x80;
        D_00351180[i].x = (f32) (i * 0x70 + 0x78E);
        D_00351180[i].y = 2249.0f;
    }
    D_00351242 = D_00351241;
    D_00351246 = 0;
}

#pragma optimization_level reset

INCLUDE_ASM("asm/nonmatchings/main_080", func_00280920);

INCLUDE_ASM("asm/nonmatchings/main_080", func_00280CB0);

INCLUDE_ASM("asm/nonmatchings/main_080", func_002817C0);

INCLUDE_ASM("asm/nonmatchings/main_080", func_002818A0);

INCLUDE_ASM("asm/nonmatchings/main_080", func_002825F0);

INCLUDE_ASM("asm/nonmatchings/main_080", func_002831A0);

INCLUDE_ASM("asm/nonmatchings/main_080", func_00283880);

INCLUDE_ASM("asm/nonmatchings/main_080", func_00284D30);

INCLUDE_ASM("asm/nonmatchings/main_080", func_00285880);

#pragma optimization_level 0

s32 func_00284D30(s32);                             /* extern */

void func_00285EE0(void) {
    func_00209D30(func_00284D30(func_00209D20()));
}

#pragma optimization_level reset

INCLUDE_ASM("asm/nonmatchings/main_080", func_00285F20);

void func_00286900(void) {

}

void func_00286910(void *arg0, void *arg1) {
    Callback_00286910 *current = arg0;
    Callback_00286910 *end = arg1;

    if (current < end) {
        do {
            (*current)();
            current++;
        } while (current < end);
    }
}

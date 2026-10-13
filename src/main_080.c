#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_080", func_0027F700);

s32 func_0027F830(s32 arg0) {
    extern s32 func_001DE4E0();
    s32 var_s0;

    var_s0 = 0;
    if (func_001DE4E0(arg0) >= 0x20) {
        if (func_001DE4E0(arg0) < 0x64) {
            var_s0 = 1;
        }
    }
    return (var_s0 != 0) ? 1 : 0;
}

INCLUDE_ASM("asm/nonmatchings/main_080", func_0027F890);

INCLUDE_ASM("asm/nonmatchings/main_080", func_0027F8B4);

INCLUDE_ASM("asm/nonmatchings/main_080", func_0027F8D8);

INCLUDE_ASM("asm/nonmatchings/main_080", func_0027F8FC);

INCLUDE_ASM("asm/nonmatchings/main_080", func_0027FA30);

INCLUDE_ASM("asm/nonmatchings/main_080", func_0027FAB0);

INCLUDE_ASM("asm/nonmatchings/main_080", func_0027FC20);

void func_0027FFC0(s32 arg0) {
    void *temp_s0;
    f32 *temp_v0;

    func_001FA810(0, 0);
    temp_s0 = (void *)func_001F9D30(0);
    temp_v0 = func_001FAF60(0);
    *temp_v0 = 2.0f * *temp_v0;
    func_001FA8A0(0, 0, 3, (u8)arg0 & 0xFF, 0, temp_s0);
    func_001FA8A0(0, 0, 4, (u8)arg0, 0, temp_v0);
}

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
    u8 padding01[5];
    u16 frame;
    s16 limit;
    u8 enabled;
    u8 countdown;
    u8 padding0C[6];
    s16 position;
    s16 angle;
    s16 velocity;
    u16 center;
    u16 symbols[16];
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

#pragma optimization_level 0

void func_00280CB0(s32 arg0) {
    extern u8 *D_00351230;
    u16 symbols[3][3];
    s32 row;
    s32 column;
    s32 offset;
    s32 clear;

    for (row = 0; row < 3; row++) {
        if (D_00351240[row].enabled != 4) {
            symbols[row][0] = symbols[row][1] = symbols[row][2] = 0xFFFF;
        } else {
            offset = D_00351240[row].position / 0x70;
            for (column = 0; column < 3; column++) {
                symbols[row][column] = D_00351240[row].symbols[(offset + column) % *D_00351230];
            }
        }
    }
    for (column = 0; column < 5; column++) {
        if (D_00351242 & (1 << column)) {
            clear = 0;
            switch (column) {
            case 0:
                if ((symbols[arg0][1]) == 0x334) {
                    clear = 1;
                }
                switch (arg0) {
                case 0:
                    if (((symbols[1][1]) != 0xFFFF) && ((symbols[0][1]) != (symbols[1][1]))) {
                        clear = 1;
                    }
                    if (((symbols[2][1]) != 0xFFFF) && ((symbols[0][1]) != (symbols[2][1]))) {
                        clear = 1;
                    }
                    break;
                case 1:
                    if (((symbols[0][1]) != 0xFFFF) && ((symbols[1][1]) != (symbols[0][1]))) {
                        clear = 1;
                    }
                    if (((symbols[2][1]) != 0xFFFF) && ((symbols[1][1]) != (symbols[2][1]))) {
                        clear = 1;
                    }
                    break;
                case 2:
                    if (((symbols[0][1]) != 0xFFFF) && ((symbols[2][1]) != (symbols[0][1]))) {
                        clear = 1;
                    }
                    if (((symbols[1][1]) != 0xFFFF) && ((symbols[2][1]) != (symbols[1][1]))) {
                        clear = 1;
                    }
                    break;
                }
                break;
            case 1:
                if ((symbols[arg0][2]) == 0x334) {
                    clear = 1;
                }
                switch (arg0) {
                case 0:
                    if (((symbols[1][2]) != 0xFFFF) && ((symbols[0][2]) != (symbols[1][2]))) {
                        clear = 1;
                    }
                    if (((symbols[2][2]) != 0xFFFF) && ((symbols[0][2]) != (symbols[2][2]))) {
                        clear = 1;
                    }
                    break;
                case 1:
                    if (((symbols[0][2]) != 0xFFFF) && ((symbols[1][2]) != (symbols[0][2]))) {
                        clear = 1;
                    }
                    if (((symbols[2][2]) != 0xFFFF) && ((symbols[1][2]) != (symbols[2][2]))) {
                        clear = 1;
                    }
                    break;
                case 2:
                    if (((symbols[0][2]) != 0xFFFF) && ((symbols[2][2]) != (symbols[0][2]))) {
                        clear = 1;
                    }
                    if (((symbols[1][2]) != 0xFFFF) && ((symbols[2][2]) != (symbols[1][2]))) {
                        clear = 1;
                    }
                    break;
                }
                break;
            case 2:
                if ((symbols[arg0][0]) == 0x334) {
                    clear = 1;
                }
                switch (arg0) {
                case 0:
                    if (((symbols[1][0]) != 0xFFFF) && ((symbols[0][0]) != (symbols[1][0]))) {
                        clear = 1;
                    }
                    if (((symbols[2][0]) != 0xFFFF) && ((symbols[0][0]) != (symbols[2][0]))) {
                        clear = 1;
                    }
                    break;
                case 1:
                    if (((symbols[0][0]) != 0xFFFF) && ((symbols[1][0]) != (symbols[0][0]))) {
                        clear = 1;
                    }
                    if (((symbols[2][0]) != 0xFFFF) && ((symbols[1][0]) != (symbols[2][0]))) {
                        clear = 1;
                    }
                    break;
                case 2:
                    if (((symbols[0][0]) != 0xFFFF) && ((symbols[2][0]) != (symbols[0][0]))) {
                        clear = 1;
                    }
                    if (((symbols[1][0]) != 0xFFFF) && ((symbols[2][0]) != (symbols[1][0]))) {
                        clear = 1;
                    }
                    break;
                }
                break;
            case 3:
                if ((symbols[arg0][2 - arg0]) == 0x334) {
                    clear = 1;
                }
                switch (arg0) {
                case 0:
                    if (((symbols[1][1]) != 0xFFFF) && ((symbols[0][2]) != (symbols[1][1]))) {
                        clear = 1;
                    }
                    if (((symbols[2][0]) != 0xFFFF) && ((symbols[0][2]) != (symbols[2][0]))) {
                        clear = 1;
                    }
                    break;
                case 1:
                    if (((symbols[0][2]) != 0xFFFF) && ((symbols[1][1]) != (symbols[0][2]))) {
                        clear = 1;
                    }
                    if (((symbols[2][0]) != 0xFFFF) && ((symbols[1][1]) != (symbols[2][0]))) {
                        clear = 1;
                    }
                    break;
                case 2:
                    if (((symbols[0][2]) != 0xFFFF) && ((symbols[2][0]) != (symbols[0][2]))) {
                        clear = 1;
                    }
                    if (((symbols[1][1]) != 0xFFFF) && ((symbols[2][0]) != (symbols[1][1]))) {
                        clear = 1;
                    }
                    break;
                }
                break;
            case 4:
                if ((symbols[arg0][arg0]) == 0x334) {
                    clear = 1;
                }
                switch (arg0) {
                case 0:
                    if (((symbols[1][1]) != 0xFFFF) && ((symbols[0][0]) != (symbols[1][1]))) {
                        clear = 1;
                    }
                    if (((symbols[2][2]) != 0xFFFF) && ((symbols[0][0]) != (symbols[2][2]))) {
                        clear = 1;
                    }
                    break;
                case 1:
                    if (((symbols[0][0]) != 0xFFFF) && ((symbols[1][1]) != (symbols[0][0]))) {
                        clear = 1;
                    }
                    if (((symbols[2][2]) != 0xFFFF) && ((symbols[1][1]) != (symbols[2][2]))) {
                        clear = 1;
                    }
                    break;
                case 2:
                    if (((symbols[0][0]) != 0xFFFF) && ((symbols[2][2]) != (symbols[0][0]))) {
                        clear = 1;
                    }
                    if (((symbols[1][1]) != 0xFFFF) && ((symbols[2][2]) != (symbols[1][1]))) {
                        clear = 1;
                    }
                    break;
                }
                break;
            }
            if (clear != 0) {
                D_00351242 &= (u8)~(1 << column);
            }
        }
    }
    D_00351240[arg0].center = symbols[arg0][1];
}
#pragma optimization_level reset

typedef struct {
    u8 pad[4];
    u8 slots[5];
    u8 cells[3][3];
} Board_002817C0;

#pragma optimization_level 0

s32 func_002817C0(void) {
    extern Board_002817C0 D_00351210;
    s32 i;
    s32 j;

    for (i = 0; i < 5; i++) {
        if (D_00351210.slots[i] > 1) {
            return 0;
        }
    }
    for (j = 0; j < 3; j++) {
        for (i = 0; i < 3; i++) {
            if (D_00351210.cells[j][i] > 1) {
                return 0;
            }
        }
    }
    return 1;
}

#pragma optimization_level reset

INCLUDE_ASM("asm/nonmatchings/main_080", func_002818A0);

INCLUDE_ASM("asm/nonmatchings/main_080", func_002825F0);

typedef struct {
    u16 u : 14;
    u16 : 2;
    u16 v : 14;
    u16 : 2;
    u32 padding;
} Texture_002831A0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Position_002831A0;

typedef struct {
    s16 id;
    u16 flags;
    s32 reserved;
    s64 command;
} Header_002831A0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Color_002831A0;

typedef struct {
    u64 texture;
    Position_002831A0 position;
} Vertex_002831A0;

typedef struct {
    u64 tag;
    u64 header[2];
    Color_002831A0 color;
    Vertex_002831A0 v0, v1, v2, v3;
    u64 reserved[4];
} Packet_002831A0;

typedef struct {
    u8 padding[9];
    u8 cells[3][3];
} State_002831A0;

#pragma optimization_level 0

void func_002831A0(void) {
    extern s32 func_00202BF0();
    extern s32 func_00202E00();
    extern s32 func_00207650();
    extern u8 D_002B8740[];
    extern State_002831A0 D_00351210;
    extern s32 D_00351228;
    Packet_002831A0 packet;
    s32 y;
    s32 x;
    s32 k;
    s32 handle;
    s32 j;
    s32 i;
    s32 size;

    handle = func_00202BF0(9, 1);
    size = func_00209E50();
    size += func_00202E00(size, 1);
    D_00351228 = func_00202B00(D_00351228, 9, size, NULL);
    D_00351228 = func_0020F290(D_00351228);
    func_00202D60(9, -1);

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (D_00351210.cells[i][j]) {
                x = i * 0x70 + 0x760;
                y = 0x840 - j * 0x70;
                ((Header_002831A0 *)&packet.header[0])->flags = 0x24;
                ((Header_002831A0 *)&packet.header[0])->id = 9;
                ((Header_002831A0 *)&packet.header[0])->command = 0x424242421LL;
                ((Header_002831A0 *)&packet.header[0])->reserved = 0;
                packet.color.r = packet.color.g = packet.color.b = D_002B8740[D_00351210.cells[i][j]];
                packet.color.a = packet.color.r >> 1;
                packet.color.q = 1.0f;
                packet.v0.position.z = packet.v1.position.z = packet.v2.position.z = packet.v3.position.z = 0xFFFFF8;
                packet.v0.position.fog = packet.v1.position.fog = packet.v2.position.fog = packet.v3.position.fog = 0;
                ((Header_002831A0 *)&packet.header[0])->flags |= 0x800;
                ((Texture_002831A0 *)&packet.v0.texture)->u = 0x440;
                ((Texture_002831A0 *)&packet.v0.texture)->v = 0x390;
                ((Texture_002831A0 *)&packet.v1.texture)->u = 0x7D0;
                ((Texture_002831A0 *)&packet.v1.texture)->v = 0x390;
                ((Texture_002831A0 *)&packet.v2.texture)->u = 0x440;
                ((Texture_002831A0 *)&packet.v2.texture)->v = 0x720;
                ((Texture_002831A0 *)&packet.v3.texture)->u = 0x7D0;
                ((Texture_002831A0 *)&packet.v3.texture)->v = 0x720;

                for (k = 0; k < 4; k++) {
                    switch (k) {
                    case 0:
                        packet.v2.position.x = packet.v0.position.x = (x - 9) * 16;
                        packet.v1.position.y = packet.v0.position.y = (y - 9) * 16;
                        packet.v3.position.x = packet.v1.position.x = packet.v0.position.x + 0x390;
                        packet.v3.position.y = packet.v2.position.y = packet.v0.position.y + 0x390;
                        break;
                    case 1:
                        packet.v3.position.x = packet.v1.position.x = (x + 0x30) * 16;
                        packet.v1.position.y = packet.v0.position.y = (y - 9) * 16;
                        packet.v2.position.x = packet.v0.position.x = packet.v1.position.x + 0x390;
                        packet.v3.position.y = packet.v2.position.y = packet.v0.position.y + 0x390;
                        break;
                    case 2:
                        packet.v2.position.x = packet.v0.position.x = (x - 9) * 16;
                        packet.v3.position.y = packet.v2.position.y = (y + 0x30) * 16;
                        packet.v3.position.x = packet.v1.position.x = packet.v0.position.x + 0x390;
                        packet.v1.position.y = packet.v0.position.y = packet.v2.position.y + 0x390;
                        break;
                    case 3:
                        packet.v3.position.x = packet.v1.position.x = (x + 0x30) * 16;
                        packet.v3.position.y = packet.v2.position.y = (y + 0x30) * 16;
                        packet.v2.position.x = packet.v0.position.x = packet.v1.position.x + 0x390;
                        packet.v1.position.y = packet.v0.position.y = packet.v2.position.y + 0x390;
                        break;
                    }
                    func_00208CB0(&packet.header[0], 0x1C4391F044ALL);
                    func_00208700(&packet.header[0], (void *)handle, 1);
                    func_002086D0(&packet.header[0], 0x44);
                    D_00351228 = func_00207650(D_00351228, &packet.header[0], 0, -1);
                    func_002086D0(&packet.header[0], 0x49);
                    D_00351228 = func_00207650(D_00351228, &packet.header[0], 0, -1);
                }
            }
        }
    }
}

#pragma optimization_level reset

INCLUDE_ASM("asm/nonmatchings/main_080", func_00283880);

INCLUDE_ASM("asm/nonmatchings/main_080", func_00284D30);

typedef struct Deck_00285880 {
    u8 count;
    u8 flags;
    u8 pad2[6];
    u16 cards[3][21];
    u16 extra[5];
} Deck_00285880;

typedef struct Row_00285880 {
    u8 padding00[0x12];
    s16 field12;
    u8 padding14[2];
    s16 field16;
    u16 field18;
    u16 cards[21];
} Row_00285880;

typedef struct Counters_00285880 {
    s32 state;
    u8 pad4[5];
    u8 rows[3][3];
} Counters_00285880;

extern Counters_00285880 D_00351210;
extern u8 D_00351214;
extern u8 D_00351215;
extern u8 D_00351216;
extern u8 D_00351217;
extern u8 D_00351218;
extern Deck_00285880 *D_00351230;
extern u8 D_00351241;
extern u8 D_00351242;
extern u8 D_00351244;
extern s16 D_00351246;
extern s16 D_00351248;

#pragma optimization_level 0

void func_00285880(s32 arg0) {
    s32 i;
    s32 j;
    s32 a;
    s32 b;
    u16 temp;
    Deck_00285880 *deck;
    s32 k;
    extern Flags_00280670 D_00351240[];
    extern s32 func_00280670();

    D_00351244 = arg0;
    D_00351230 = (Deck_00285880 *)0x01ED0000;
    if (D_00351244) {
        deck = D_00351230;
        deck->count = 0x10;
        deck->extra[0] = deck->extra[1] = deck->extra[2] = deck->extra[3] = deck->extra[4] = 0xFFFE;
        for (k = 0; k < deck->count; k++) {
            deck->cards[0][k] = (func_0019A5C8() >> 4) % 3 + 5;
        }
        deck->cards[0][deck->count >> 1] = 0x334;
        deck->flags = 2;
    }
    D_00351230->extra[0] = 0xFFFE;
    D_00351241 = D_00351242 = 0;
    for (i = 0; i < 5; i++) {
        if (D_00351230->extra[i] != 0xFFFF) {
            D_00351241 |= (u8)(1 << i);
        }
    }
    D_00351240[0].state = 0;
    D_00351248 = D_00351230->count * 0x70;
    D_00351246 = 0;
    D_00351210.state = 0;
    for (j = 0; j < 3; j++) {
        D_00351210.rows[j][0] = D_00351210.rows[j][1] = D_00351210.rows[j][2] = 0;
    }
    D_00351214 = D_00351215 = D_00351216 = D_00351217 = D_00351218 = 0;
    for (j = 0; j < 3; j++) {
        ((Row_00285880 *)&D_00351240[j])->field12 = 0;
        ((Row_00285880 *)&D_00351240[j])->field16 = 0;
        ((Row_00285880 *)&D_00351240[j])->field18 = 0xFFFF;
        D_00351240[j].enabled = 0;
        switch (j) {
        case 0:
            for (i = 0; i < D_00351230->count; i++) {
                ((Row_00285880 *)&(&D_00351240[0].state)[i * 2])->cards[0] = D_00351230->cards[0][i];
            }
            break;
        case 1:
        case 2:
            if (D_00351230->flags & 1) {
                for (i = 0; i < D_00351230->count; i++) {
                    ((Row_00285880 *)&(&D_00351240[j].state)[i * 2])->cards[0] = D_00351230->cards[j][i];
                }
            } else {
                for (i = 0; i < D_00351230->count; i++) {
                    ((Row_00285880 *)&(&D_00351240[j].state)[i * 2])->cards[0] = ((Row_00285880 *)&(&D_00351240[0].state)[i * 2])->cards[0];
                }
                for (i = 0; i < D_00351230->count * 2; i++) {
                    a = (func_0019A5C8() >> 4) % D_00351230->count;
                    b = (func_0019A5C8() >> 4) % D_00351230->count;
                    temp = ((Row_00285880 *)&(&D_00351240[j].state)[a * 2])->cards[0];
                    ((Row_00285880 *)&(&D_00351240[j].state)[a * 2])->cards[0] = ((Row_00285880 *)&(&D_00351240[j].state)[b * 2])->cards[0];
                    ((Row_00285880 *)&(&D_00351240[j].state)[b * 2])->cards[0] = temp;
                }
            }
            break;
        }
    }
    if (!D_00351244) {
        func_00280670();
    }
}

#pragma optimization_level reset

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

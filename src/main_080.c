#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_080", TaTuto_DrawTrapArea);

s32 TaTuto_IsTuto(s32 arg0) {
    extern s32 SzDuel_GetPlayer();
    s32 var_s0;

    var_s0 = 0;
    if (SzDuel_GetPlayer(arg0) >= 0x20) {
        if (SzDuel_GetPlayer(arg0) < 0x64) {
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

void TaView_ReqHalfFarView(s32 arg0) {
    void *temp_s0;
    f32 *temp_v0;

    SzView_FreeRequest(0, 0);
    temp_s0 = (void *)SzView_GetCP(0);
    temp_v0 = SzView_GetLook(0);
    *temp_v0 = 2.0f * *temp_v0;
    SzView_ReqCamera(0, 0, 3, (u8)arg0 & 0xFF, 0, temp_s0);
    SzView_ReqCamera(0, 0, 4, (u8)arg0, 0, temp_v0);
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

s32 ShSlot_Flear(void *arg0, s32 arg1) {
    extern s32 func_001A22C0(f32);
    extern s32 ExSortPrim_Pipe(s32, void *, s32, s32);
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
        if (ShFx_isTimer(header) != 0) {
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
            ExAssignAlpha(&packet, 0x48);
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
                D_00351228 = ExSortPrim_Pipe(D_00351228, &packet, 0, func_001A23B0(depth));
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
extern u16 D_00351246;

#pragma optimization_level 0

void ShSlot_Start(void) {
    extern s32 ShFx_initTimer();
    s32 i;

    for (i = 0; i < 3; i++) {
        D_00351240[i].enabled = 1;
    }
    D_00351240[0].state = 1;
    SzSound_PlaySE(0, 0x1E);
    for (i = 0; i < 3; i++) {
        ShFx_initTimer(&D_00351180[i], 0x28, 0, 0xFF);
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

typedef struct Reel_00280920 {
    u8 count;
    u8 pad1[0x85];
    u16 stops[5];
} Reel_00280920;

typedef struct Board_00280920 {
    u8 pad[4];
    u8 slots[5];
} Board_00280920;

#pragma optimization_level 0

void ShSlot_HitCardRequest(void) {
    extern Board_00280920 D_00351210;
    extern Reel_00280920 *D_00351230;
    extern s32 D_002B8780[];
    extern s16 D_00351252;
    extern u16 D_00351258;
    extern u16 D_00351292;
    extern s32 TaSlot_GetFeverGain(u16, u8);
    extern u8 D_0035117A;
    extern u16 D_0035117C;
    u16 id;
    s32 slot;
    s32 base;

    D_0035117C = 0xFFFF;
    while (D_0035117A < 8) {
        id = D_00351240[D_0035117A].center;
        switch (D_0035117A) {
        case 0:
            if (id != 0xFFFF) {
                D_0035117C = D_00351240[D_0035117A].center;
                D_0035117A++;
                return;
            }
            break;
        case 1:
            if (id != 0xFFFF && id != D_00351258) {
                D_0035117C = D_00351240[D_0035117A].center;
                D_0035117A++;
                return;
            }
            break;
        case 2:
            if (id != 0xFFFF && id != D_00351258 && id != D_00351292) {
                D_0035117C = D_00351240[D_0035117A].center;
                D_0035117A++;
                return;
            }
            break;
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            slot = D_0035117A - 3;
            if (D_00351210.slots[slot]) {
                if (D_00351230->stops[slot] == 0xFFFE) {
                    base = D_00351252 / 0x70;
                    D_0035117C = TaSlot_GetFeverGain(D_00351240[0].symbols[(base + D_002B8780[slot]) % D_00351230->count], slot);
                } else {
                    D_0035117C = D_00351230->stops[D_0035117A - 3];
                }
                D_0035117A++;
                return;
            }
            break;
        }
        D_0035117A++;
    }
}

#pragma optimization_level reset

#pragma optimization_level 0

void ShSlot_CheckLine(s32 arg0) {
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

s32 ShSlot_IsFlashStop(void) {
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

typedef struct {
    s16 count;
    u16 flags;
    s32 reserved;
    s64 registers;
} Tag_002818A0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Color_002818A0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Position_002818A0;

typedef struct {
    u16 u : 14;
    u16 : 2;
    u16 v : 14;
    u16 : 2;
    u32 padding;
} UV_002818A0;

typedef struct {
    u64 texture;
    Position_002818A0 xyz;
} Vertex_002818A0;

typedef struct {
    u64 header[2];
    Color_002818A0 color;
    Vertex_002818A0 v0, v1, v2, v3;
    u64 texture[4];
} Packet_002818A0;

typedef struct {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
    s16 u;
    s16 v;
    s16 uw;
    s16 vh;
    s16 kind;
    s16 tex;
} Item_002818A0;

typedef struct {
    Item_002818A0 items[84];
} Items_002818A0;

typedef struct {
    u8 values[16];
} Pulse_002818A0;

#define CLAMP_002818A0(wms, wmt, minu, maxu, minv, maxv) \
    ((u64)(wms) | ((u64)(wmt) << 2) | ((u64)(minu) << 4) | ((u64)(maxu) << 14) | ((u64)(minv) << 24) | \
     ((u64)(maxv) << 34))

#pragma optimization_level 0

void ShSlot_DrawParts(s32 arg0) {
    extern s32 func_00202E00();
    extern s32 func_00207650();
    extern Items_002818A0 D_002B87A0;
    extern Pulse_002818A0 D_002B8E30;
    extern struct { u8 pad[4]; u8 lv[12]; } D_00351210;
    extern u8 D_002B8740[];
    s32 i;
    s32 bit;
    s32 skip;
    s32 tmp;
    Items_002818A0 items;
    Pulse_002818A0 pulse;
    void *handles[2];
    Packet_002818A0 packet __attribute__((aligned(8)));

    items = D_002B87A0;
    pulse = D_002B8E30;
    switch (arg0) {
    case 0:
        i = 0;
        break;
    case 1:
        i = 0x16;
        break;
    case 2:
        i = 0x35;
        break;
    }
    handles[0] = (void *)func_00202BF0(9, 0);
    handles[1] = (void *)func_00202BF0(9, 1);
    tmp = func_00209E50();
    tmp += func_00202E00(tmp, 1);
    D_00351228 = func_00202B00(D_00351228, 9, tmp, NULL);
    D_00351228 = func_0020F290(D_00351228);
    func_00202D60(9, -1);
    while (items.items[i].x != -1) {
        skip = 0;
        ((Tag_002818A0 *)&packet.header[0])->flags = 0x24;
        ((Tag_002818A0 *)&packet.header[0])->count = 9;
        ((Tag_002818A0 *)&packet.header[0])->registers = 0x424242421LL;
        ((Tag_002818A0 *)&packet.header[0])->reserved = 0;
        packet.color.r = packet.color.g = packet.color.b = packet.color.a = 0x80;
        packet.color.q = 1.0f;
        packet.v0.xyz.z = packet.v1.xyz.z = packet.v2.xyz.z = packet.v3.xyz.z = 0xFFFFF8;
        packet.v0.xyz.f = packet.v1.xyz.f = packet.v2.xyz.f = packet.v3.xyz.f = 0;
        packet.v2.xyz.x = packet.v0.xyz.x = (items.items[i].x + 0x6C0) << 4;
        packet.v1.xyz.y = packet.v0.xyz.y = (items.items[i].y + 0x720) << 4;
        packet.v3.xyz.x = packet.v1.xyz.x = packet.v0.xyz.x + (items.items[i].w << 4);
        packet.v3.xyz.y = packet.v2.xyz.y = packet.v0.xyz.y + (items.items[i].h << 4);
        ((Tag_002818A0 *)&packet.header[0])->flags |= 0x800;
        ((UV_002818A0 *)&packet.v0.texture)->u = items.items[i].u << 4;
        ((UV_002818A0 *)&packet.v0.texture)->v = items.items[i].v << 4;
        ((UV_002818A0 *)&packet.v1.texture)->u = items.items[i].uw << 4;
        ((UV_002818A0 *)&packet.v1.texture)->v = items.items[i].v << 4;
        ((UV_002818A0 *)&packet.v2.texture)->u = items.items[i].u << 4;
        ((UV_002818A0 *)&packet.v2.texture)->v = items.items[i].vh << 4;
        ((UV_002818A0 *)&packet.v3.texture)->u = items.items[i].uw << 4;
        ((UV_002818A0 *)&packet.v3.texture)->v = items.items[i].vh << 4;
        switch (items.items[i].kind) {
        case 1:
            func_00208CB0(&packet.header[0], CLAMP_002818A0(2, 2, items.items[i].u, items.items[i].uw, items.items[i].v,
                                                          items.items[i].vh - 1));
            break;
        case 2:
            func_00208CB0(&packet.header[0], 0x100030800FFLL);
            break;
        case 3:
            func_00208CB0(&packet.header[0], 0x10C030800FFLL);
            break;
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            if (D_00351240[0].state == 1) {
                bit = items.items[i].kind - 4;
                if (D_00351242 & (1 << bit)) {
                    packet.color.r = packet.color.g = packet.color.b = pulse.values[(D_00351246 >> 1) & 0xF] + 0x40;
                    packet.color.a = pulse.values[(D_00351246 >> 1) & 0xF] + 4;
                    break;
                }
            }
            skip = 1;
            break;
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
            bit = items.items[i].kind - 9;
            if (!(D_00351241 & (1 << bit))) {
                skip = 1;
            }
            break;
        case 14:
            func_00208CB0(&packet.header[0], 0x3F0003FF);
            break;
        case 15:
            func_00208CB0(&packet.header[0], 0x1001F0001FFLL);
            break;
        case 16:
            packet.v0.xyz.x = (items.items[i].x + 0x6C0) << 4;
            packet.v0.xyz.y = (items.items[i].y + 0x720 + items.items[i].h) << 4;
            packet.v1.xyz.x = (items.items[i].x + 0x6C0) << 4;
            packet.v1.xyz.y = (items.items[i].y + 0x720) << 4;
            packet.v3.xyz.x = (items.items[i].x + 0x6C0 + items.items[i].w) << 4;
            packet.v3.xyz.y = (items.items[i].y + 0x720) << 4;
            packet.v2.xyz.x = (items.items[i].x + 0x6C0 + items.items[i].w) << 4;
            packet.v2.xyz.y = (items.items[i].y + 0x720 + items.items[i].h) << 4;
            break;
        case 17:
        case 18:
        case 19:
        case 20:
        case 21:
            tmp = items.items[i].kind - 0x11;
            bit = tmp;
            if (D_00351210.lv[bit]) {
                packet.color.r = packet.color.g = packet.color.b = D_002B8740[D_00351210.lv[bit]];
                packet.color.a = packet.color.r >> 1;
                func_00208700(&packet.header[0], handles[items.items[i].tex], 1);
                func_00208CB0(&packet.header[0], CLAMP_002818A0(2, 2, items.items[i].u, items.items[i].uw,
                                                              items.items[i].v, items.items[i].vh));
                func_002086D0(&packet.header[0], 0x44);
                D_00351228 = func_00207650(D_00351228, &packet.header[0], 0, -1);
                func_002086D0(&packet.header[0], 0x49);
                D_00351228 = func_00207650(D_00351228, &packet.header[0], 0, -1);
            }
            skip = 1;
            break;
        }
        if (!skip) {
            func_00208700(&packet.header[0], handles[items.items[i].tex], 1);
            func_002086D0(&packet.header[0], 0x44);
            D_00351228 = func_00207650(D_00351228, &packet.header[0], 0, -1);
        }
        i++;
    }
}

#pragma optimization_level reset

typedef struct {
    s16 count;
    u16 flags;
    s32 reserved;
    s64 registers;
} Tag_002825F0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Color_002825F0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Position_002825F0;

typedef struct {
    u16 u : 14;
    u16 : 2;
    u16 v : 14;
    u16 : 2;
    u32 padding;
} UV_002825F0;

typedef struct {
    u64 texture;
    Position_002825F0 xyz;
} Vertex_002825F0;

typedef struct {
    u64 header[2];
    Color_002825F0 color;
    Vertex_002825F0 v0, v1, v2, v3;
    u64 texture[4];
} Packet_002825F0;

typedef struct {
    s32 values[17];
} Pulse_002825F0;

#pragma optimization_level 0

void ShSlot_DrawEye(void) {
    extern s32 SzText_LoadRequest();
    extern s32 SzText_InitClutManage();
    extern s32 ExSortPrim_Pipe();
    extern Pulse_002825F0 D_002B8E40;
    Pulse_002825F0 pulse;
    Packet_002825F0 packet __attribute__((aligned(8)));
    s32 i;
    s32 handle;
    s32 x;
    s32 y;
    s32 width;
    s32 size;

    pulse = D_002B8E40;
    handle = SzText_LoadRequest(3, 7);
    size = RhBase_GetUserGsAddress();
    size += SzText_InitClutManage(size, 1);
    D_00351228 = SzText_DoRequest_Pipe(D_00351228, 3, size, NULL);
    D_00351228 = RhText_SetTextureFlush(D_00351228);
    SzText_FreeRequest(3, -1);
    ((Tag_002825F0 *)&packet.header[0])->flags = 0x24;
    ((Tag_002825F0 *)&packet.header[0])->count = 9;
    ((Tag_002825F0 *)&packet.header[0])->registers = 0x424242421LL;
    ((Tag_002825F0 *)&packet.header[0])->reserved = 0;
    packet.color.r = packet.color.g = packet.color.b = 0x80;
    packet.color.a = 0x80;
    packet.color.q = 1.0f;
    packet.v0.xyz.z = packet.v1.xyz.z = packet.v2.xyz.z = packet.v3.xyz.z = 0xFFFFF8;
    packet.v0.xyz.f = packet.v1.xyz.f = packet.v2.xyz.f = packet.v3.xyz.f = 0;
    y = (pulse.values[D_00351246 & 0xF] >> 2) + 0x8B8;
    x = (pulse.values[D_00351246 & 0xF] >> 2) + 0x77E;
    width = 0x20 - (pulse.values[D_00351246 & 0xF] >> 1);
    for (i = 0; i < 3; i++) {
        if (D_00351240[i].enabled != 4) {
            packet.v2.xyz.x = packet.v0.xyz.x = (x + i * 0x70) << 4;
            packet.v1.xyz.y = packet.v0.xyz.y = y << 4;
            packet.v3.xyz.x = packet.v1.xyz.x = packet.v0.xyz.x + (width << 4);
            packet.v3.xyz.y = packet.v2.xyz.y = packet.v0.xyz.y + (width << 4);
            ((Tag_002825F0 *)&packet.header[0])->flags |= 0x800;
            switch (i) {
            case 0:
                ((UV_002825F0 *)&packet.v0.texture)->u = 0x160;
                ((UV_002825F0 *)&packet.v0.texture)->v = 0xB00;
                ((UV_002825F0 *)&packet.v1.texture)->u = 0x2C0;
                ((UV_002825F0 *)&packet.v1.texture)->v = 0xB00;
                ((UV_002825F0 *)&packet.v2.texture)->u = 0x160;
                ((UV_002825F0 *)&packet.v2.texture)->v = 0xC60;
                ((UV_002825F0 *)&packet.v3.texture)->u = 0x2B0;
                ((UV_002825F0 *)&packet.v3.texture)->v = 0xC60;
                break;
            case 1:
                ((UV_002825F0 *)&packet.v0.texture)->u = 0;
                ((UV_002825F0 *)&packet.v0.texture)->v = 0xB00;
                ((UV_002825F0 *)&packet.v1.texture)->u = 0x160;
                ((UV_002825F0 *)&packet.v1.texture)->v = 0xB00;
                ((UV_002825F0 *)&packet.v2.texture)->u = 0;
                ((UV_002825F0 *)&packet.v2.texture)->v = 0xC60;
                ((UV_002825F0 *)&packet.v3.texture)->u = 0x160;
                ((UV_002825F0 *)&packet.v3.texture)->v = 0xC60;
                break;
            case 2:
                ((UV_002825F0 *)&packet.v0.texture)->u = 0x420;
                ((UV_002825F0 *)&packet.v0.texture)->v = 0xB00;
                ((UV_002825F0 *)&packet.v1.texture)->u = 0x580;
                ((UV_002825F0 *)&packet.v1.texture)->v = 0xB00;
                ((UV_002825F0 *)&packet.v2.texture)->u = 0x420;
                ((UV_002825F0 *)&packet.v2.texture)->v = 0xC60;
                ((UV_002825F0 *)&packet.v3.texture)->u = 0x580;
                ((UV_002825F0 *)&packet.v3.texture)->v = 0xC60;
                break;
            }
            ExAssignTexture(&packet.header[0], (void *)handle, 0);
            ExAssignAlpha(&packet.header[0], 0x44);
            D_00351228 = ExSortPrim_Pipe(D_00351228, &packet.header[0], 0, -1);
        }
    }

    handle = SzText_LoadRequest(9, 0);
    size = RhBase_GetUserGsAddress();
    size += SzText_InitClutManage(size, 1);
    D_00351228 = SzText_DoRequest_Pipe(D_00351228, 9, size, NULL);
    D_00351228 = RhText_SetTextureFlush(D_00351228);
    SzText_FreeRequest(9, -1);
    ((Tag_002825F0 *)&packet.header[0])->flags = 0x24;
    ((Tag_002825F0 *)&packet.header[0])->count = 9;
    ((Tag_002825F0 *)&packet.header[0])->registers = 0x424242421LL;
    ((Tag_002825F0 *)&packet.header[0])->reserved = 0;
    packet.color.r = 0x60;
    packet.color.g = packet.color.b = 0x80;
    packet.color.a = pulse.values[D_00351246 & 0xF] * 3;
    packet.color.q = 1.0f;
    packet.v0.xyz.z = packet.v1.xyz.z = packet.v2.xyz.z = packet.v3.xyz.z = 0xFFFFF8;
    packet.v0.xyz.f = packet.v1.xyz.f = packet.v2.xyz.f = packet.v3.xyz.f = 0;
    y = 0x8B7;
    x = 0x77D;
    for (i = 0; i < 3; i++) {
        if (D_00351240[i].enabled != 4) {
            packet.v2.xyz.x = packet.v0.xyz.x = (x + i * 0x70) << 4;
            packet.v1.xyz.y = packet.v0.xyz.y = y << 4;
            packet.v3.xyz.x = packet.v1.xyz.x = packet.v0.xyz.x + 0x220;
            packet.v3.xyz.y = packet.v2.xyz.y = packet.v0.xyz.y + 0x220;
            ((Tag_002825F0 *)&packet.header[0])->flags |= 0x800;
            ((UV_002825F0 *)&packet.v0.texture)->u = 0x160;
            ((UV_002825F0 *)&packet.v0.texture)->v = 0x600;
            ((UV_002825F0 *)&packet.v1.texture)->u = 0x2E0;
            ((UV_002825F0 *)&packet.v1.texture)->v = 0x600;
            ((UV_002825F0 *)&packet.v2.texture)->u = 0x160;
            ((UV_002825F0 *)&packet.v2.texture)->v = 0x780;
            ((UV_002825F0 *)&packet.v3.texture)->u = 0x2E0;
            ((UV_002825F0 *)&packet.v3.texture)->v = 0x780;
            ExAssignTexture(&packet.header[0], (void *)handle, 0);
            ExAssignAlpha(&packet.header[0], 0x48);
            D_00351228 = ExSortPrim_Pipe(D_00351228, &packet.header[0], 0, -1);
        }
    }
}

#pragma optimization_level reset

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

void ShSlot_FlashBox(void) {
    extern s32 SzText_LoadRequest();
    extern s32 SzText_InitClutManage();
    extern s32 ExSortPrim_Pipe();
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

    handle = SzText_LoadRequest(9, 1);
    size = RhBase_GetUserGsAddress();
    size += SzText_InitClutManage(size, 1);
    D_00351228 = SzText_DoRequest_Pipe(D_00351228, 9, size, NULL);
    D_00351228 = RhText_SetTextureFlush(D_00351228);
    SzText_FreeRequest(9, -1);

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
                    ExAssignClamp(&packet.header[0], 0x1C4391F044ALL);
                    ExAssignTexture(&packet.header[0], (void *)handle, 1);
                    ExAssignAlpha(&packet.header[0], 0x44);
                    D_00351228 = ExSortPrim_Pipe(D_00351228, &packet.header[0], 0, -1);
                    ExAssignAlpha(&packet.header[0], 0x49);
                    D_00351228 = ExSortPrim_Pipe(D_00351228, &packet.header[0], 0, -1);
                }
            }
        }
    }
}

#pragma optimization_level reset

typedef struct {
    s16 count;
    u16 flags;
    s32 reserved;
    s64 registers;
} Tag_00283880;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Color_00283880;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Position_00283880;

typedef struct {
    u16 u : 14;
    u16 : 2;
    u16 v : 14;
    u16 : 2;
    u32 padding;
} UV_00283880;

typedef struct {
    u64 texture;
    Position_00283880 xyz;
} TexVertex_00283880;

typedef struct {
    Color_00283880 color;
    Position_00283880 xyz;
} ColorVertex_00283880;

typedef struct {
    u64 tag;
    u64 header[2];
    ColorVertex_00283880 v0, v1, v2, v3;
} Gradient_00283880;

typedef struct {
    u64 tag;
    u64 header[2];
    Color_00283880 color;
    TexVertex_00283880 v0, v1, v2, v3;
    u64 texture[4];
} Textured_00283880;

typedef struct {
    s32 images[4];
    s32 *background;
    Gradient_00283880 gradient;
    Textured_00283880 textured;
} DrawWork_00283880;

#pragma optimization_level 0

void ShSlot_DrawReel(s32 arg0) {
    extern s32 SzText_LoadRequest();
    extern s32 SzText_InitClutManage();
    extern s32 ExSortPrim_Pipe();
    extern s32 SzText_GetReadyItem();
    extern s32 SzText_Load_Pipe();
    extern s32 D_00351228;
    extern u8 *D_00351230;

    s32 i;
    s32 u0;
    s32 u1;
    s32 scroll;
    s32 y;
    s32 shadeY;
    s32 shadeHeight;
    s32 top;
    s32 bottom;
    DrawWork_00283880 work;
    s32 position;
    s32 x;
    s32 imageIndex;
    s32 height;
    s32 size;
    s32 backgroundX;
    s32 backgroundY;

    work.background = (s32 *) SzText_LoadRequest(9, 0);
    position = RhBase_GetUserGsAddress();
    position += SzText_InitClutManage(position, 1);
    D_00351228 = SzText_DoRequest_Pipe(D_00351228, 9, position, NULL);
    D_00351228 = RhText_SetTextureFlush(D_00351228);
    SzText_FreeRequest(9, -1);
    scroll = D_00351240[arg0].angle % 176;

    ((Tag_00283880 *) &work.textured.header[0])->flags = 0x24;
    ((Tag_00283880 *) &work.textured.header[0])->count = 9;
    ((Tag_00283880 *) &work.textured.header[0])->registers = 0x424242421LL;
    ((Tag_00283880 *) &work.textured.header[0])->reserved = 0;
    work.textured.color.r = work.textured.color.g = work.textured.color.b = 0x80;
    work.textured.color.a = 0x80;
    work.textured.color.q = 1.0f;
    work.textured.v0.xyz.z = work.textured.v1.xyz.z = work.textured.v2.xyz.z = work.textured.v3.xyz.z = 0xFFFFF8;
    work.textured.v0.xyz.f = work.textured.v1.xyz.f = work.textured.v2.xyz.f = work.textured.v3.xyz.f = 0;

    backgroundY = 0x750;
    backgroundX = arg0 * 0x70 + 0x75C;
    for (i = 0; i < 3; i++) {
        switch (i) {
        case 0:
            work.textured.v2.xyz.x = work.textured.v0.xyz.x = backgroundX << 4;
            work.textured.v1.xyz.y = work.textured.v0.xyz.y = (backgroundY + scroll) << 4;
            work.textured.v3.xyz.x = work.textured.v1.xyz.x = work.textured.v0.xyz.x + 0x680;
            work.textured.v3.xyz.y = work.textured.v2.xyz.y = work.textured.v0.xyz.y + 0xB00;
            ((Tag_00283880 *) &work.textured.header[0])->flags |= 0x800;
            if (D_00351240[arg0].angle < 176) {
                u0 = 0x30;
                u1 = 0x98;
            } else {
                u0 = 0x98;
                u1 = 0x100;
            }
            ((Tag_00283880 *) &work.textured.header[0])->flags |= 0x800;
            ((UV_00283880 *) &work.textured.v0.texture)->u = (u16) (u0 << 4);
            ((UV_00283880 *) &work.textured.v0.texture)->v = 0x500;
            ((UV_00283880 *) &work.textured.v1.texture)->u = (u16) (u1 << 4);
            ((UV_00283880 *) &work.textured.v1.texture)->v = 0x500;
            ((UV_00283880 *) &work.textured.v2.texture)->u = (u16) (u0 << 4);
            ((UV_00283880 *) &work.textured.v2.texture)->v = 0x1000;
            ((UV_00283880 *) &work.textured.v3.texture)->u = (u16) (u1 << 4);
            ((UV_00283880 *) &work.textured.v3.texture)->v = 0x1000;
            break;
        case 1:
            work.textured.v2.xyz.x = work.textured.v0.xyz.x = backgroundX << 4;
            work.textured.v1.xyz.y = work.textured.v0.xyz.y = backgroundY << 4;
            work.textured.v3.xyz.x = work.textured.v1.xyz.x = work.textured.v0.xyz.x + 0x680;
            work.textured.v3.xyz.y = work.textured.v2.xyz.y = work.textured.v0.xyz.y + (scroll << 4);
            if (D_00351240[arg0].angle < 176) {
                u0 = 0x98;
                u1 = 0x100;
            } else {
                u0 = 0x30;
                u1 = 0x98;
            }
            ((Tag_00283880 *) &work.textured.header[0])->flags |= 0x800;
            ((UV_00283880 *) &work.textured.v0.texture)->u = (u16) (u0 << 4);
            ((UV_00283880 *) &work.textured.v0.texture)->v = (u16) ((0x100 - scroll) * 16);
            ((UV_00283880 *) &work.textured.v1.texture)->u = (u16) (u1 << 4);
            ((UV_00283880 *) &work.textured.v1.texture)->v = (u16) ((0x100 - scroll) * 16);
            ((UV_00283880 *) &work.textured.v2.texture)->u = (u16) (u0 << 4);
            ((UV_00283880 *) &work.textured.v2.texture)->v = 0x1000;
            ((UV_00283880 *) &work.textured.v3.texture)->u = (u16) (u1 << 4);
            ((UV_00283880 *) &work.textured.v3.texture)->v = 0x1000;
            break;
        case 2:
            work.textured.v2.xyz.x = work.textured.v0.xyz.x = backgroundX << 4;
            work.textured.v1.xyz.y = work.textured.v0.xyz.y = (backgroundY + 0xB0 + scroll) << 4;
            work.textured.v3.xyz.x = work.textured.v1.xyz.x = work.textured.v0.xyz.x + 0x680;
            work.textured.v3.xyz.y = work.textured.v2.xyz.y = work.textured.v0.xyz.y + ((0xB0 - scroll) << 4);
            ((Tag_00283880 *) &work.textured.header[0])->flags |= 0x800;
            ((UV_00283880 *) &work.textured.v0.texture)->u = (u16) (u0 << 4);
            ((UV_00283880 *) &work.textured.v0.texture)->v = 0x500;
            ((UV_00283880 *) &work.textured.v1.texture)->u = (u16) (u1 << 4);
            ((UV_00283880 *) &work.textured.v1.texture)->v = 0x500;
            ((UV_00283880 *) &work.textured.v2.texture)->u = (u16) (u0 << 4);
            ((UV_00283880 *) &work.textured.v2.texture)->v = (u16) ((0x100 - scroll) * 16);
            ((UV_00283880 *) &work.textured.v3.texture)->u = (u16) (u1 << 4);
            ((UV_00283880 *) &work.textured.v3.texture)->v = (u16) ((0x100 - scroll) * 16);
            break;
        }
        ExAssignClamp(&work.textured.header[0], ((s64) u0 << 4) | 0xA | ((s64) u1 << 14) | 0x50000000 | ((u64) 0x3FC << 32));
        ExAssignTexture(&work.textured.header[0], work.background, 1);
        ExAssignAlpha(&work.textured.header[0], 0x44);
        D_00351228 = ExSortPrim_Pipe(D_00351228, &work.textured.header[0], 0, -1);
    }

    imageIndex = D_00351240[arg0].position / 112;
    scroll = D_00351240[arg0].position % 112;
    position = RhBase_GetUserGsAddress();
    position += SzText_InitClutManage(position, 1);
    for (i = 0; i < 4; i++) {
        work.images[i] = SzText_GetReadyItem(1, D_00351240[arg0].symbols[(imageIndex + i) % *D_00351230]);
        if (work.images[i] != NULL) {
            D_00351228 = SzText_Load_Pipe(D_00351228, *(s32 *) work.images[i], position, &size);
            position += size;
        }
    }
    D_00351228 = RhText_SetTextureFlush(D_00351228);
    for (i = 0; i < 4; i++) {
        if (work.images[i] != NULL) {
            ((Tag_00283880 *) &work.textured.header[0])->flags = 0x24;
            ((Tag_00283880 *) &work.textured.header[0])->count = 9;
            ((Tag_00283880 *) &work.textured.header[0])->registers = 0x424242421LL;
            ((Tag_00283880 *) &work.textured.header[0])->reserved = 0;
            work.textured.color.r = work.textured.color.g = work.textured.color.b = work.textured.color.a = 0x80;
            work.textured.color.q = 1.0f;
            work.textured.v0.xyz.z = work.textured.v1.xyz.z = work.textured.v2.xyz.z = work.textured.v3.xyz.z = 0xFFFFF8;
            work.textured.v0.xyz.f = work.textured.v1.xyz.f = work.textured.v2.xyz.f = work.textured.v3.xyz.f = 0;

            x = arg0 * 0x70 + 0xA0;
            work.textured.v2.xyz.x = work.textured.v0.xyz.x = (x + 0x6C0) << 4;
            work.textured.v3.xyz.x = work.textured.v1.xyz.x = work.textured.v0.xyz.x + 0x600;
            y = scroll + (0x120 - i * 0x70);
            if (y < 0x30) {
                top = ((0x30 - y) << 7) / 96;
                height = 0x60 - (0x30 - y);
                y = 0x30;
            } else {
                height = 0x60;
                top = 0;
            }
            if (y + 0x60 > 400) {
                bottom = ((400 - y) << 7) / 96;
                height = 400 - y;
            } else {
                bottom = 0x80;
            }
            work.textured.v1.xyz.y = work.textured.v0.xyz.y = (y + 0x720) << 4;
            work.textured.v3.xyz.y = work.textured.v2.xyz.y = work.textured.v0.xyz.y + (height << 4);
            ((Tag_00283880 *) &work.textured.header[0])->flags |= 0x800;
            ((UV_00283880 *) &work.textured.v0.texture)->u = 0;
            ((UV_00283880 *) &work.textured.v0.texture)->v = (u16) (top << 4);
            ((UV_00283880 *) &work.textured.v1.texture)->u = 0x800;
            ((UV_00283880 *) &work.textured.v1.texture)->v = (u16) (top << 4);
            ((UV_00283880 *) &work.textured.v2.texture)->u = 0;
            ((UV_00283880 *) &work.textured.v2.texture)->v = (u16) (bottom << 4);
            ((UV_00283880 *) &work.textured.v3.texture)->u = 0x800;
            ((UV_00283880 *) &work.textured.v3.texture)->v = (u16) (bottom << 4);
            ExAssignClamp(&work.textured.header[0], ((s64) top << 24) | 0x20000A | ((s64) bottom << 34));
            ExAssignTexture(&work.textured.header[0], *(void **) work.images[i], 1);
            D_00351228 = ExSortPrim_Pipe(D_00351228, &work.textured.header[0], 0, -1);
        }
    }
    ((Tag_00283880 *) &work.gradient.header[0])->flags = 0x14;
    ((Tag_00283880 *) &work.gradient.header[0])->count = 8;
    ((Tag_00283880 *) &work.gradient.header[0])->registers = 0x41414141LL;
    ((Tag_00283880 *) &work.gradient.header[0])->reserved = 0;
    x = arg0 * 0x70 + 0x9C;
    for (i = 0; i < 4; i++) {
        switch (i) {
        case 0:
            work.gradient.v0.color.r = work.gradient.v0.color.g = work.gradient.v0.color.b =
                work.gradient.v1.color.r = work.gradient.v1.color.g = work.gradient.v1.color.b = 0x80;
            work.gradient.v2.color.r = work.gradient.v2.color.g = work.gradient.v2.color.b =
                work.gradient.v3.color.r = work.gradient.v3.color.g = work.gradient.v3.color.b = 0x20;
            shadeY = 0x30;
            shadeHeight = 0x40;
            break;
        case 1:
            work.gradient.v0.color.r = work.gradient.v0.color.g = work.gradient.v0.color.b =
                work.gradient.v1.color.r = work.gradient.v1.color.g = work.gradient.v1.color.b = 0x20;
            work.gradient.v2.color.r = work.gradient.v2.color.g = work.gradient.v2.color.b =
                work.gradient.v3.color.r = work.gradient.v3.color.g = work.gradient.v3.color.b = 0;
            shadeY += 0x40;
            shadeHeight = 0x70;
            break;
        case 2:
            work.gradient.v0.color.r = work.gradient.v0.color.g = work.gradient.v0.color.b =
                work.gradient.v1.color.r = work.gradient.v1.color.g = work.gradient.v1.color.b = 0;
            work.gradient.v2.color.r = work.gradient.v2.color.g = work.gradient.v2.color.b =
                work.gradient.v3.color.r = work.gradient.v3.color.g = work.gradient.v3.color.b = 0x20;
            shadeY += 0x70;
            shadeHeight = 0x70;
            break;
        case 3:
            work.gradient.v0.color.r = work.gradient.v0.color.g = work.gradient.v0.color.b =
                work.gradient.v1.color.r = work.gradient.v1.color.g = work.gradient.v1.color.b = 0x20;
            work.gradient.v2.color.r = work.gradient.v2.color.g = work.gradient.v2.color.b =
                work.gradient.v3.color.r = work.gradient.v3.color.g = work.gradient.v3.color.b = 0x80;
            shadeY += 0x70;
            shadeHeight = 0x40;
            break;
        }
        work.gradient.v0.color.a = work.gradient.v1.color.a = work.gradient.v2.color.a = work.gradient.v3.color.a = 0x80;
        work.gradient.v0.color.q = work.gradient.v1.color.q = work.gradient.v2.color.q = work.gradient.v3.color.q = 1.0f;
        work.gradient.v0.xyz.z = work.gradient.v1.xyz.z = work.gradient.v2.xyz.z = work.gradient.v3.xyz.z = 0xFFFFF8;
        work.gradient.v0.xyz.f = work.gradient.v1.xyz.f = work.gradient.v2.xyz.f = work.gradient.v3.xyz.f = 0;
        work.gradient.v2.xyz.x = work.gradient.v0.xyz.x = (x + 0x6C0) << 4;
        work.gradient.v1.xyz.y = work.gradient.v0.xyz.y = (shadeY + 0x720) << 4;
        work.gradient.v3.xyz.x = work.gradient.v1.xyz.x = work.gradient.v0.xyz.x + 0x680;
        work.gradient.v3.xyz.y = work.gradient.v2.xyz.y = work.gradient.v0.xyz.y + (shadeHeight << 4);
        ExAssignAlpha(&work.gradient.header[0], 0x42 | ((u64) 0x80 << 32));
        D_00351228 = ExSortPrim_Pipe(D_00351228, &work.gradient.header[0], 0, -1);
    }
}

#pragma optimization_level reset

typedef struct Timers_00284D30 {
    s32 enabled;
    u8 counters[5];
    u8 grid[3][3];
} Timers_00284D30;

extern u8 D_00351178;
extern u8 D_00351179;
extern u8 D_0035117A;
extern u16 D_0035117C;
extern s16 D_00351248;

#pragma optimization_level 0

s32 ShSlot_Draw_Pipe(s32 arg0) {
    extern Timers_00284D30 D_00351210;
    s32 i;
    s32 j;
    s32 speed;
    s32 brakingSpeed;
    s32 segment;

    for (i = 0; i < 3; i++) {
        switch (D_00351240[i].enabled) {
        case 0:
        case 4:
            break;
        case 1:
            if (D_00351240[i].velocity < 32) {
                D_00351240[i].velocity++;
            } else {
                D_00351240[i].enabled = 2;
            }
        case 2:
            speed = D_00351240[i].velocity;
            D_00351240[i].position += (s16)speed;
            if (D_00351240[i].position > D_00351248) {
                D_00351240[i].position -= D_00351248;
            } else if (D_00351240[i].position < 0) {
                D_00351240[i].position += D_00351248;
            }
            D_00351240[i].angle += (s16)speed;
            if (D_00351240[i].angle > 351) {
                D_00351240[i].angle -= 351;
            } else if (D_00351240[i].angle < 0) {
                D_00351240[i].angle += 351;
            }
            break;
        case 3:
            if (D_00351240[i].countdown < 6) {
                switch (D_00351240[i].countdown) {
                case 5:
                    segment = D_00351240[i].position / 112;
                    D_00351240[i].position = (s16)((segment + 1) * 112);
                    D_00351240[i].velocity = 16;
                    break;
                case 4:
                case 3:
                    D_00351240[i].velocity = -12;
                    break;
                case 2:
                case 1:
                    D_00351240[i].velocity = 4;
                    break;
                }
            }
            brakingSpeed = D_00351240[i].velocity;
            D_00351240[i].position += (s16)brakingSpeed;
            if (D_00351240[i].position > D_00351248) {
                D_00351240[i].position -= D_00351248;
            } else if (D_00351240[i].position < 0) {
                D_00351240[i].position += D_00351248;
            }
            D_00351240[i].angle += (s16)brakingSpeed;
            if (D_00351240[i].angle > 351) {
                D_00351240[i].angle -= 351;
            } else if (D_00351240[i].angle < 0) {
                D_00351240[i].angle += 351;
            }
            D_00351240[i].countdown--;
            if (!D_00351240[i].countdown) {
                D_00351240[i].velocity = 0;
                D_00351240[i].enabled = 4;
                ShSlot_CheckLine(i);
            }
            break;
        }
    }
    D_00351228 = arg0;
    if (D_00351228 != 0) {
        ShSlot_DrawParts(0);
        ShSlot_DrawEye();
        for (j = 0; j < 3; j++) {
            ShSlot_DrawReel(j);
        }
        if (D_00351210.enabled != 0) {
            ShSlot_FlashBox();
            ShSlot_DrawParts(2);
            for (i = 0; i < 5; i++) {
                if (D_00351210.counters[i] > 1) {
                    D_00351210.counters[i]--;
                }
            }
            for (j = 0; j < 3; j++) {
                for (i = 0; i < 3; i++) {
                    if (D_00351210.grid[j][i] > 1) {
                        D_00351210.grid[j][i]--;
                    }
                }
            }
        }
        ShSlot_DrawParts(1);
        if (D_00351240[0].state == 3) {
            switch (D_00351178) {
            case 1:
                ShSlot_HitCardRequest();
                if (D_0035117C != 0xFFFF) {
                    if (D_0035117A > 3) {
                        SzSound_PlaySE(0, 25);
                        SzDuel_OpenMsgPopup(3, 0, 0, D_0035117C);
                        D_00351178 = 2;
                        D_00351179 = 0;
                    } else {
                        SzSound_PlaySE(0, 7);
                        SzDuel_OpenMsgPopup(2, 0, 0, D_0035117C);
                        D_00351178 = 2;
                        D_00351179 = 0;
                    }
                } else {
                    SzDuel_CloseMsgPopup();
                    D_00351178 = 6;
                    D_00351179 = 8;
                }
                break;
            }
        }
        ShSlot_Flear(D_00351180, 3);
    }
    D_00351246++;
    return D_00351228;
}
#pragma optimization_level reset

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
extern u16 D_00351246;
extern s16 D_00351248;

#pragma optimization_level 0

void ShSlot_Init(s32 arg0) {
    s32 i;
    s32 j;
    s32 a;
    s32 b;
    u16 temp;
    Deck_00285880 *deck;
    s32 k;
    extern Flags_00280670 D_00351240[];
    extern s32 ShSlot_Start();

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
        ShSlot_Start();
    }
}

#pragma optimization_level reset

#pragma optimization_level 0

s32 ShSlot_Draw_Pipe(s32);                             /* extern */

void ShSlot_Draw(void) {
    RhBase_SetVifPacketArea(ShSlot_Draw_Pipe(RhBase_GetVifPacketArea()));
}

#pragma optimization_level reset

static inline Object_00280670 *object_00285F20(s32 index) {
    return &D_00351180[index];
}

static inline Flags_00280670 *row_00285F20(s32 index) {
    return &D_00351240[index];
}

#pragma optimization_level 0

void ShSlot_Act(void) {
    extern s32 SzDuel_CloseMsgPopup();
    extern s32 SzGame_Pop();
    extern s32 ShFx_initTimer();
    extern s32 SzSound_PlaySE();
    extern s32 ShSlot_Start();
    extern s32 ShSlot_IsFlashStop();
    extern s32 ShSlot_Init(s32);
    extern s32 SzPad_GetAnalogInfo();
    s32 i;
    s32 remainder1;
    s32 remainder2;
    s32 remainder3;

    if (D_00351244) {
        if (SzPad_Check(0, 0, 0x800) != 0) {
            SzDuel_CloseMsgPopup();
            ShSlot_Init(1);
        }
        if (SzPad_Check(0, 0, 0x100) != 0) {
            SzGame_Pop();
        }
    }
    switch (D_00351240[0].state) {
    case 0:
        if (SzPad_Check(0, 0, 0x4000) != 0 ||
            (SzPad_IsAnalog(0) != 0 && (SzPad_GetAnalogInfo(0, 3) & 0xFF) > 0xF0)) {
            SzSound_PlaySE(0, 0x20);
            ShSlot_Start();
        }
        break;
    case 1:
        if (D_00351240[0].enabled == 2 && SzPad_Check(0, 0, 0x80) != 0) {
            SzSound_PlaySE(0, 0x21);
            ShFx_initTimer(object_00285F20(0), 0x10, 0, 0xFF);
            object_00285F20(0)->width = 40.0f;
            object_00285F20(0)->height = 1.0f;
            row_00285F20(0)->enabled = 3;
            remainder1 = row_00285F20(0)->position % 112;
            row_00285F20(0)->countdown = (u8)((0x70 - remainder1) / row_00285F20(0)->velocity + 5);
            if (D_00351230->flags & 2) {
                row_00285F20(0)->countdown +=
                    (u8)((0x70 / row_00285F20(0)->velocity) * ((func_0019A5C8() >> 4) % 3));
            }
        }
        if (D_00351240[1].enabled == 2 && SzPad_Check(0, 0, 0x10) != 0) {
            SzSound_PlaySE(0, 0x21);
            ShFx_initTimer(object_00285F20(1), 0x10, 0, 0xFF);
            object_00285F20(1)->width = 40.0f;
            object_00285F20(1)->height = 1.0f;
            row_00285F20(1)->enabled = 3;
            remainder2 = row_00285F20(1)->position % 112;
            row_00285F20(1)->countdown = (u8)((0x70 - remainder2) / row_00285F20(1)->velocity + 5);
            if (D_00351230->flags & 2) {
                row_00285F20(1)->countdown +=
                    (u8)((0x70 / row_00285F20(1)->velocity) * ((func_0019A5C8() >> 4) % 3));
            }
        }
        if (D_00351240[2].enabled == 2 && SzPad_Check(0, 0, 0x20) != 0) {
            SzSound_PlaySE(0, 0x21);
            ShFx_initTimer(object_00285F20(2), 0x10, 0, 0xFF);
            object_00285F20(2)->width = 40.0f;
            object_00285F20(2)->height = 1.0f;
            row_00285F20(2)->enabled = 3;
            remainder3 = row_00285F20(2)->position % 112;
            row_00285F20(2)->countdown = (u8)((0x70 - remainder3) / row_00285F20(2)->velocity + 5);
            if (D_00351230->flags & 2) {
                row_00285F20(2)->countdown +=
                    (u8)((0x70 / row_00285F20(2)->velocity) * ((func_0019A5C8() >> 4) % 3));
            }
        }
        if (D_00351240[0].enabled == 4 && D_00351240[1].enabled == 4 && D_00351240[2].enabled == 4) {
            D_00351240[0].state = 2;
            SzSound_StopSE(0, 0x1E);
        }
        break;
    case 2:
        if (ShSlot_IsFlashStop() != 0) {
            if ((D_00351242 & 0x1F) == 0) {
                D_00351240[0].state = 3;
                D_00351178 = 0;
                D_00351179 = 0x10;
            } else {
                for (i = 0; i < 5; i++) {
                    if (D_00351242 & (1 << i)) {
                        switch (i) {
                        case 0:
                            D_00351210.state = 1;
                            D_00351214 = D_00351210.rows[0][1] = D_00351210.rows[1][1] = D_00351210.rows[2][1] = 0x10;
                            break;
                        case 1:
                            D_00351210.state = 1;
                            D_00351215 = D_00351210.rows[0][2] = D_00351210.rows[1][2] = D_00351210.rows[2][2] = 0x10;
                            break;
                        case 2:
                            D_00351210.state = 1;
                            D_00351216 = D_00351210.rows[0][0] = D_00351210.rows[1][0] = D_00351210.rows[2][0] = 0x10;
                            break;
                        case 3:
                            D_00351210.state = 1;
                            D_00351217 = D_00351210.rows[0][2] = D_00351210.rows[1][1] = D_00351210.rows[2][0] = 0x10;
                            break;
                        case 4:
                            D_00351210.state = 1;
                            D_00351218 = D_00351210.rows[0][0] = D_00351210.rows[1][1] = D_00351210.rows[2][2] = 0x10;
                            break;
                        }
                        D_00351242 &= (u8)~(1 << i);
                        i = 5;
                    }
                }
            }
        }
        break;
    case 3:
        switch (D_00351178) {
        case 0:
            if (D_00351179) {
                D_00351179--;
            } else {
                D_00351178 = 1;
                D_0035117A = 0;
                D_00351179 = 8;
            }
            break;
        case 1:
            break;
        case 2:
            if (SzPad_Check(0, 0, 0xF0) != 0) {
                D_00351178 = 1;
                D_00351179 = 8;
            }
            break;
        case 6:
            if (D_00351179) {
                D_00351179--;
            } else {
                D_00351240[0].state = 4;
            }
            break;
        }
        break;
    case 4:
        if (!D_00351244) {
            SzGame_Pop();
        }
        break;
    }
}

#pragma optimization_level reset

void ShSlot_Term(void) {

}

void __initialize_cpp_rts(void *arg0, void *arg1) {
    Callback_00286910 *current = arg0;
    Callback_00286910 *end = arg1;

    if (current < end) {
        do {
            (*current)();
            current++;
        } while (current < end);
    }
}

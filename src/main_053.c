#include "common.h"

f32 func_001A6C30(f32, f32);
void func_0020C630(void *, void *);
extern f32 D_00293040[4][4];

typedef struct Vec4_001FB500 {
    f32 x, y, z, w;
} Vec4_001FB500;

typedef struct Camera_001FB500 {
    Vec4_001FB500 param;
    f32 direction[4];
    f32 origin[4];
    f32 target[4];
} Camera_001FB500;

static inline s32 aim_001FB500(s32 index) {
    Camera_001FB500 *entry;

    if ((index < 0) || (index > 0)) {
        return 0;
    }
    entry = (Camera_001FB500 *)D_0031BEB0[index];
    if (entry == 0) {
        return 0;
    }
    entry->direction[0] = entry->target[0] - entry->origin[0];
    entry->direction[1] = entry->target[1] - entry->origin[1];
    entry->direction[2] = entry->target[2] - entry->origin[2];
    entry->direction[3] = 0.0f;
    func_0020D070(entry->direction);
    return 1;
}

s32 func_001FB500(s32 index, f32 *src) {
    Camera_001FB500 *entry;
    f32 matrix[4][4];
    f32 angles[4];

    if ((index < 0) || (index > 0)) {
        return 0;
    }
    entry = (Camera_001FB500 *)D_0031BEB0[index];
    if (entry == 0) {
        return 0;
    }
    if (src == NULL) {
        return 0;
    }
    entry->param = *(Vec4_001FB500 *)src;
    entry->param.y = func_001A6C30(6.2831855f + entry->param.y, 6.2831855f);
    if (func_001FAFB0(index, (s32)angles) != 0) {
        func_0020C630(matrix, angles);
    }
    func_0020CDD0(entry->direction, matrix, D_00293040);
    entry->target[0] = entry->origin[0] - entry->direction[0] * entry->param.x;
    entry->target[1] = entry->origin[1] - entry->direction[1] * entry->param.x;
    entry->target[2] = entry->origin[2] - entry->direction[2] * entry->param.x;
    entry->target[3] = 0.0f;
    aim_001FB500(index);
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FB6A0);

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FB940);

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FBE50);

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FC050);

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FC210);

s32 func_001FC6D0(s32 arg0, s32 arg1) {
    s32 entry;
    u16 flags;

    if (arg0 < 0 || arg0 > 0) {
        return 0;
    }
    entry = D_0031BEB0[arg0];
    if (entry == 0) {
        return 0;
    }
    if (arg1 < 0 || arg1 >= 10) {
        return 0;
    }
    flags = *(u16 *)((u8 *)entry + 0x8AC);
    if (flags & (1 << arg1)) {
        return 1;
    }
    return (flags & 0x200) ? 1 : 0;
}

s32 func_001FC760(s32 arg0, s32 arg1) {
    s32 temp_v1;
    u16 temp_a0;

    if (arg0 < 0 || arg0 > 0) {
        return 0;
    }
    temp_v1 = D_0031BEB0[arg0];
    if (temp_v1 == 0) {
        return 0;
    }
    if (arg1 < 0 || arg1 >= 0xA) {
        return 0;
    }
    temp_a0 = *(u16 *)((u8 *)temp_v1 + 0x8AE);
    if (temp_a0 & (1 << arg1)) {
        return 1;
    }
    return !(temp_a0 & 0x200) ? 0 : 1;
}

s32 func_001FC7F0(s32 arg0) {
    void *temp_v0;
    s32 result;

    if (arg0 < 0 || arg0 > 0) {
        result = -1;
    } else {
        temp_v0 = (void *)D_0031BEB0[arg0];
        if (temp_v0 == NULL) {
            result = -1;
        } else {
            result = *(s32 *)((u8 *)temp_v0 + 0x8B0);
        }
    }
    return result;
}

s32 func_001FC840(s32 arg0, s32 arg1) {
    void *temp_v0;

    if (arg0 < 0 || arg0 > 0) {
        return 0;
    }
    temp_v0 = (void *)D_0031BEB0[arg0];
    if (temp_v0 == NULL) {
        return 0;
    }
    *(s32 *)((u8 *)temp_v0 + 0x8B0) = arg1;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FC890);

void func_001FC950(void *arg0, void *arg1) {
    s32 *src = arg0;
    f32 *dst = arg1;

    dst[0] = (f32) src[0];
    dst[1] = (3.1415927f * (f32) src[1]) / 32768.0f;
    dst[2] = (3.1415927f * (f32) src[2]) / 32768.0f;
    dst[3] = (f32) src[3];
}

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FC9B0);

void func_001FCA70(void) {

    if (D_0031C048 != 0) {
        func_00217B50(D_0031C048);
        D_0031C048 = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FCAB0);

void func_001FCC20(void) {
    Entry_0031C050 *entry;
    s32 count;

    entry = D_0031C050;
    count = 2;
    while (count--) {
        entry->flag = 1;
        entry++;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FCC70);

s32 func_001FCD60(s32 arg0) {
    Entry_0031C050 *temp_a2;

    temp_a2 = &D_0031C050[arg0];
    temp_a2->flag = 1;
    return 1;
}

void func_001FCDA0(void) {
    s32 i;

    i = 0;
    do {
        func_001FCDE0(i);
        i += 1;
    } while (i < 2);
}

typedef struct {
    s8 paused : 1;
    s8 unused : 7;
} Flags_001FCDE0;

s32 func_001FCDE0(s32 arg0) {
    u8 color[4];
    Entry_0031C050 *entry;
    s32 next;
    u8 amount;

    if ((arg0 < 0) || (arg0 >= 2)) {
        return 0;
    }
    entry = &D_0031C050[arg0];
    if (entry->flag != 0) {
        return 0;
    }
    amount = entry->lo;
    if (!(*(u8 *)((u8 *)entry + 7) & 0x3F)) {
        amount = entry->hi - amount;
    }
    color[2] = entry->pad0[2];
    color[1] = entry->pad0[1];
    color[0] = entry->pad0[0];
    color[3] = (entry->pad0[3] * (amount & 0xFF)) / entry->hi;
    func_001FCF30(0, (s32)color, 0xFFFFFF);
    if (entry->lo >= entry->hi) {
        if (entry->pad7b != 0) {
            entry->flag = 1;
        }
    } else if (((Flags_001FCDE0 *)&entry->pad8[0])->paused == 0) {
        next = entry->lo + entry->pad0[4];
        if (entry->hi < next) {
            entry->lo = entry->hi;
        } else {
            entry->lo = next;
        }
    }
    return 1;
}

void func_001FCF30(s32 arg0, s32 arg1, s32 arg2) {
    func_00209D30(func_001FCF90(func_00209D20(), arg0, arg1, arg2));
}

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 reserved : 8;
} Vertex_001FCF90;

typedef struct {
    u16 count;
    u16 flags;
    u32 reserved;
    u64 registers;
} Header_001FCF90;

typedef struct {
    u64 tag[2];
    u8 color[4];
    f32 q;
    Vertex_001FCF90 vertices[2];
} Packet_001FCF90;

static inline void init_001FCF90(void *tag) {
    ((Header_001FCF90 *)tag)->flags = 6;
    ((Header_001FCF90 *)tag)->count = 3;
    ((Header_001FCF90 *)tag)->registers = 0x441;
    ((Header_001FCF90 *)tag)->reserved = 0;
}

s32 func_001FCF90(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    Packet_001FCF90 packet;

    init_001FCF90((Header_001FCF90 *)packet.tag);
    func_002086D0(&packet, func_00208D00(arg1));
    packet.color[0] = ((u8 *)arg2)[2];
    packet.color[1] = ((u8 *)arg2)[1];
    packet.color[2] = ((u8 *)arg2)[0];
    packet.color[3] = ((u8 *)arg2)[3];
    packet.q = 1.0f;
    packet.vertices[0].x = 0x6C00;
    packet.vertices[0].y = 0x7200;
    packet.vertices[0].z = (u32)arg3;
    packet.vertices[0].reserved = 0;
    packet.vertices[1].x = 0x9400;
    packet.vertices[1].y = 0x8E00;
    packet.vertices[1].z = (u32)arg3;
    packet.vertices[1].reserved = 0;
    return func_00207650(arg0, (s32)&packet, 0, 0);
}

s32 func_001FD0B0(s32 arg0) {
    Entry_0031C050 *entry;

    if (arg0 < 0 || arg0 >= 2) {
        return 0;
    }
    entry = &D_0031C050[arg0];
    if (entry->flag) {
        return 0;
    }
    entry->pad7b = -1;
    return 1;
}

typedef struct {
    s8 enabled : 1;
    s8 pad : 7;
} Flags_001FD130;

s32 func_001FD130(s32 arg0, s64 arg1) {
    Entry_0031C050 *temp_a2;

    if (arg0 < 0 || arg0 >= 2) {
        return 0;
    }
    temp_a2 = &D_0031C050[arg0];
    if (temp_a2->flag != 0) {
        return 0;
    }
    ((Flags_001FD130 *) temp_a2->pad8)->enabled = (s8) arg1;
    return 1;
}

s32 func_001FD1B0(s32 arg0) {
    Entry_0031C050 *e;

    if (arg0 < 0 || arg0 >= 2) {
        return -1;
    }
    e = &D_0031C050[arg0];
    if (e->flag != 0) {
        return -1;
    }
    return e->hi - e->lo;
}

static inline s32 calc_001FD220(s32 idx) {
    Entry_0031C050 *e;

    if (idx < 0 || idx >= 2) {
        return -1;
    }
    e = &D_0031C050[idx];
    if (e->flag) {
        return -1;
    }
    return e->hi - e->lo;
}

s32 func_001FD220(s32 arg0) {
    s32 i;
    s32 want = arg0 ? 1 : 0;

    for (i = 0; i < 2; i++) {
        if (calc_001FD220(i) >= want) {
            return 1;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FD2B0);

s32 func_001FD2D0(s32 arg0, s32 arg1) {
    s32 sp3C;

    func_00209D30(func_001FD320(func_00209D20(), arg0, arg1, &sp3C));
    return sp3C;
}

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FD320);

void func_001FD4B0(s32 arg0) {
    D_0031C2E4 = arg0;
}

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FD4C0);

void func_001FD610(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_00209D30(func_001FD680(func_00209D20(), arg0, arg1, arg2, arg3));
}

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FD680);

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FDB90);

typedef struct {
    u64 TBP0 : 14;
    u64 TBW : 6;
    u64 PSM : 6;
    u64 TW : 4;
    u64 TH : 4;
    u64 TCC : 1;
    u64 TFX : 2;
    u64 CBP : 14;
    u64 CPSM : 4;
    u64 CSM : 1;
    u64 CSA : 5;
    u64 CLD : 3;
} Tex0_001FDD70;

typedef struct {
    u64 LCM : 1;
    u64 : 1;
    u64 MXL : 3;
    u64 MMAG : 1;
    u64 MMIN : 3;
    u64 MTBA : 1;
    u64 : 9;
    u64 L : 2;
    u64 : 11;
    u64 K : 12;
    u64 : 20;
} Tex1_001FDD70;

typedef struct {
    s32 width;
    s32 height;
    s32 tw;
    s32 th;
    s32 cbp;
    s32 tbp;
    s32 cbpOffset;
} TexInfo_001FDD70;

void func_001FDD70(void *arg0, void *arg1) {
    extern TexInfo_001FDD70 D_0031C070;
    TexInfo_001FDD70 *texture = &D_0031C070;

    if (arg0 != NULL) {
        ((Tex0_001FDD70 *)arg0)->TBP0 = texture->tbp;
        ((Tex0_001FDD70 *)arg0)->TBW = texture->width >> 6;
        ((Tex0_001FDD70 *)arg0)->PSM = 20;
        ((Tex0_001FDD70 *)arg0)->TW = texture->tw;
        ((Tex0_001FDD70 *)arg0)->TH = texture->th;
        ((Tex0_001FDD70 *)arg0)->TCC = 1;
        ((Tex0_001FDD70 *)arg0)->TFX = 0;
        ((Tex0_001FDD70 *)arg0)->CBP = texture->cbp + texture->cbpOffset;
        ((Tex0_001FDD70 *)arg0)->CPSM = 0;
        ((Tex0_001FDD70 *)arg0)->CSM = 0;
        ((Tex0_001FDD70 *)arg0)->CSA = 0;
        ((Tex0_001FDD70 *)arg0)->CLD = 1;
    }
    if (arg1 != NULL) {
        ((Tex1_001FDD70 *)arg1)->LCM = 0;
        ((Tex1_001FDD70 *)arg1)->MXL = 0;
        ((Tex1_001FDD70 *)arg1)->MMAG = 0;
        ((Tex1_001FDD70 *)arg1)->MMIN = 0;
        ((Tex1_001FDD70 *)arg1)->MTBA = 0;
        ((Tex1_001FDD70 *)arg1)->L = 0;
        ((Tex1_001FDD70 *)arg1)->K = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FDFE0);

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FE290);

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FE660);

void func_001FE750(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_00209D30(func_001FE7D0(func_00209D20(), arg0, arg1, arg2, arg3, arg4));
}

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FE7D0);

void func_001FE880(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_00209D30(func_001FE8F0(func_00209D20(), arg0, arg1, arg2, arg3));
}

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FE8F0);

typedef struct Vec4_001FEA80 {
    f32 x, y, z, w;
} Vec4_001FEA80;

extern Vec4_001FEA80 D_002CFCD0;

void func_001FEA80(void *arg0) {
    *(Vec4_001FEA80 *)arg0 = D_002CFCD0;
}

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FEAB0);

typedef struct {
    u8 pad00[0x13];
    s8 low_001FEAF0 : 7;
    s8 flag_001FEAF0 : 1;
} Entry_001FEAF0;

typedef struct {
    u8 pad00[0xC];
    Entry_001FEAF0 entries[30];
} Table_001FEAF0;

extern Table_001FEAF0 D_0031C070;

void func_001FEAF0(s32 arg0) {
    Table_001FEAF0 *t = &D_0031C070;

    if (arg0 >= 0 && arg0 < 0x1E) {
        t->entries[arg0].flag_001FEAF0 = 0;
    }
}

typedef struct {
    s8 pad0[3];
    s8 unused : 7;
    s8 active : 1;
    s8 pad4[16];
} Entry_001FEB40;

extern Entry_001FEB40 D_0031C08C[30];

void func_001FEB40(void) {
    Entry_001FEB40 *entry;
    s32 i;

    entry = D_0031C08C;
    i = 0;
    do {
        i += 1;
        entry->active = 0;
        entry++;
    } while (i < 30);
}

typedef struct Flags_001FEB80 {
    s8 bit0 : 1;
    s8 bit1 : 1;
    s8 bits2_7 : 6;
} Flags_001FEB80;

typedef struct State_001FEB80 {
    u8 pad[0x6688];
    s32 field_6688;
    s16 field_668C;
    s16 field_668E;
    Flags_001FEB80 field_6690;
} State_001FEB80;

typedef struct Entry36_001FEB80 {
    s32 field0;
    u8 pad[0x20];
} Entry36_001FEB80;

typedef struct Entry8_001FEB80 {
    s32 field0;
    s32 field4;
} Entry8_001FEB80;

extern State_001FEB80 D_0031C2F0;
extern Entry36_001FEB80 D_00320370[];
extern Entry8_001FEB80 D_00322770[];

void func_001FEB80(void) {
    State_001FEB80 *state;
    Entry8_001FEB80 *small;
    Entry36_001FEB80 *large;
    s32 count;

    state = &D_0031C2F0;
    large = D_00320370;
    small = D_00322770;
    count = 0x100;
    func_0020B3C0((s8 *)&D_0031C2F0, 0, 0x66A0);
    while (count--) {
        large->field0 = -1;
        large++;
    }
    count = 0x40;
    while (count--) {
        small->field0 = -1;
        small++;
    }
    state->field_668C = 0;
    state->field_668E = 0;
    state->field_6688 = -1;
    state->field_6690.bit1 = 0;
}

void func_001FEC70(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s64 arg5) {
    func_001FECB0(arg0, 0, arg1, arg2, arg3, 0, -1, arg4, arg5);
}

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FECB0);

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FEDA0);

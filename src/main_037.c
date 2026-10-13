#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_037", func_001A6C30);

INCLUDE_ASM("asm/nonmatchings/main_037", func_001A6C48);

INCLUDE_ASM("asm/nonmatchings/main_037", func_001A6C60);


typedef struct Flags2C_001A6C80 {
    u8 low : 2;
    s8 mode : 2;
    u8 value : 2;
    u8 high : 2;
} Flags2C_001A6C80;

typedef struct Flags2D_001A6C80 {
    u8 first : 3;
    u8 second : 3;
    u8 high : 2;
} Flags2D_001A6C80;

typedef struct Flags2E_001A6C80 {
    u8 value : 3;
    u8 bit3 : 1;
    s8 bit4 : 1;
    s8 bit5 : 1;
    s8 bit6 : 1;
    s8 bit7 : 1;
} Flags2E_001A6C80;

void func_001A6C80(void) {
    s8 *data = (s8 *)&D_00317250;
    s32 i;
    s32 *p;

    func_0020B3C0((s8 *) &D_00317250, 0, 0x230);
    D_00317250 = 0;
    D_00317254 = 0;
    D_0031747A = 1;
    i = 0;
    p = (s32 *)data;
    do {
        p[0x138 / 4] = 0;
        p[0xA4 / 4] = 0;
        p[0x10 / 4] = 0;
        data[0x1CC + i] = 10;
        i++;
        p++;
    } while (i < 0x25);
    *(s32 *)(data + 0x14) = 2;
    *(s32 *)(data + 0xA8) = 0x38;
    *(s32 *)(data + 0x18) = 1;
    *(s32 *)(data + 0xAC) = 2;
    *(s32 *)(data + 0x1C) = 4;
    *(s32 *)(data + 0xB0) = 0x66;
    *(s32 *)(data + 0x144) = 0x64;
    *(s32 *)(data + 0x20) = 4;
    *(s32 *)(data + 0xB4) = 0x66;
    *(s32 *)(data + 0x148) = 0x64;
    *(s32 *)(data + 0x24) = 2;
    *(s32 *)(data + 0xB8) = 0xA;
    *(s32 *)(data + 0x28) = 1;
    *(s32 *)(data + 0xBC) = 2;
    *(s32 *)(data + 0x2C) = 3;
    *(s32 *)(data + 0xC0) = 0x2AB;
    *(s32 *)(data + 0x34) = 1;
    *(s32 *)(data + 0xC8) = 5;
    *(s32 *)(data + 0x38) = 1;
    *(s32 *)(data + 0xCC) = 3;
    *(s32 *)(data + 0x3C) = 2;
    *(s32 *)(data + 0xD0) = 0x64;
    *(s32 *)(data + 0x40) = 1;
    *(s32 *)(data + 0xD4) = 5;
    *(s32 *)(data + 0x54) = 4;
    *(s32 *)(data + 0xE8) = 0x2710;
    *(s32 *)(data + 0x5C) = 4;
    *(s32 *)(data + 0xF0) = 0x2710;
    *(s32 *)(data + 0x60) = 1;
    *(s32 *)(data + 0xF4) = 7;
    *(s32 *)(data + 0x64) = 1;
    *(s32 *)(data + 0xF8) = 2;
    *(s32 *)(data + 0x18C) = 1;
    *(s32 *)(data + 0x68) = 4;
    *(s32 *)(data + 0xFC) = 0x2710;
    *(s32 *)(data + 0x190) = 0x63;
    *(s32 *)(data + 0x6C) = 5;
    *(s32 *)(data + 0x100) = 0x186A0;
    *(s32 *)(data + 0x70) = 4;
    *(s32 *)(data + 0x104) = 0x10000;
    *(s8 *)(data + 0x1E4) = 0x10;
    *(s32 *)(data + 0x74) = 1;
    *(s32 *)(data + 0x108) = 2;
    *(s32 *)(data + 0x19C) = 1;
    *(s32 *)(data + 0x78) = 2;
    *(s32 *)(data + 0x10C) = 0x81;
    *(s32 *)(data + 0x1A0) = 0x80;
    *(s8 *)(data + 0x1E6) = 0x10;
    *(s32 *)(data + 0x7C) = 2;
    *(s32 *)(data + 0x110) = 0xD;
    *(s32 *)(data + 0x1A4) = 1;
    *(s32 *)(data + 0x80) = 1;
    *(s32 *)(data + 0x114) = 4;
    *(s32 *)(data + 0x1A8) = 3;
    *(s32 *)(data + 0x84) = 1;
    *(s32 *)(data + 0x118) = 4;
    *(s32 *)(data + 0x1AC) = 3;
    *(s32 *)(data + 0x88) = 1;
    *(s32 *)(data + 0x11C) = 2;
    *(s32 *)(data + 0x1B0) = 1;
    *(s32 *)(data + 0x8C) = 1;
    *(s32 *)(data + 0x120) = 2;
    *(s32 *)(data + 0x90) = 1;
    *(s32 *)(data + 0x124) = 2;
    *(s32 *)(data + 0x50) = 1;
    *(s32 *)(data + 0xE4) = 4;
    *(s32 *)(data + 0x94) = 2;
    *(s32 *)(data + 0x128) = 0x12;
    *(s8 *)(data + 0x21E) = -3;
    *(s8 *)(data + 0x21F) = -3;
    *(s8 *)(data + 0x220) = -3;
    *(s8 *)(data + 0x221) = 0;
    *(s8 *)(data + 0x1F1) = -3;
    *(s8 *)(data + 0x1F9) = 0;
    *(s8 *)(data + 0x222) = 0;
    *(s8 *)(data + 0x223) = 0;
    *(s8 *)(data + 0x22B) = *(s8 *)(data + 0x188);
    ((Flags2D_001A6C80 *)(data + 0x22D))->first = 0;
    *(s16 *)(data + 0x21C) = 0;
    ((Flags2D_001A6C80 *)(data + 0x22D))->second = 0;
    ((Flags2E_001A6C80 *)(data + 0x22E))->value = 0;
    ((Flags2E_001A6C80 *)(data + 0x22E))->bit3 = 0;
    ((Flags2E_001A6C80 *)(data + 0x22E))->bit5 = *(s8 *)(data + 0x18C);
    func_00214BB0(0, 0, *(s32 *)(data + 0x1B8));
    func_00214BB0(0, 1, *(s32 *)(data + 0x1B4));
    func_00214BB0(0, 2, *(s32 *)(data + 0x19C));
    ((Flags2E_001A6C80 *)(data + 0x22E))->bit6 = 1;
    ((Flags2E_001A6C80 *)(data + 0x22E))->bit7 = 0;
    ((Flags2C_001A6C80 *)(data + 0x22C))->value = 0;
    ((Flags2E_001A6C80 *)(data + 0x22E))->bit4 = 0;
    *(s32 *)(data + 0xC) = 0;
    *(s8 *)(data + 0x229) = 0;
    *(s8 *)(data + 0x228) = 0;
    ((Flags2C_001A6C80 *)(data + 0x22C))->mode = 1;
    *(s32 *)(data + 0x204) = 0;
    *(s32 *)(data + 0x208) = 0;
    *(s8 *)(data + 0x20E) = 0;
    *(s8 *)(data + 0x20D) = 0;
    *(s8 *)(data + 0x20C) = 0;
    *(u8 *)(data + 0x20F) = 0x80;
    *(s32 *)(data + 0x214) = 0;
    *(s32 *)(data + 0x218) = 0;
}

INCLUDE_ASM("asm/nonmatchings/main_037", func_001A6FF0);

INCLUDE_ASM("asm/nonmatchings/main_037", func_001A7380);

typedef struct {
    u8 padding[0x138];
    s32 entries[0x25];
} Table_001A82E0;

s32 func_001A82E0(s32 arg0) {
    Table_001A82E0 *table = (Table_001A82E0 *)&D_00317250;
    s32 result;

    if ((arg0 < 0) || (arg0 >= 0x25)) {
        result = -1;
    } else {
        result = table->entries[arg0];
    }
    return result;
}

typedef struct State_001A8320 {
    u8 padding[0x138];
    s32 values[0x25];
} State_001A8320;

s32 func_001A8320(s32 arg0, s32 arg1) {
    State_001A8320 *state = (State_001A8320 *)&D_00317250;

    if ((arg0 < 0) || (arg0 >= 0x25)) {
        return 0;
    }
    state->values[arg0] = arg1;
    return 1;
}

void func_001A8360(s32 arg0, s32 arg1, s32 arg2) {
    u8 *func_001FFF90(u8 *);
    void func_0019B648(void *, void *, ...);
    u8 buf[128];

    func_0019B648(buf, D_002BE809, func_001FFF90(D_002BE80F), D_0028FF10[arg0]);
    func_001A83E0(buf, arg1, arg2);
}

s32 func_001A83E0(u8 *arg0, s32 arg1, s32 arg2) {
    extern s32 func_00242470();
    extern s32 func_001F2920(s32);
    s32 flag;
    s32 i;
    s32 result;

    flag = func_00217530();
    while (func_001FF300() != 0) {
        func_001FF420();
    }
    if (flag != 0) {
        func_00109FC0();
        func_00109D70(1);
        func_002174D0();
    }
    for (i = 0; i < 10; i++) {
        func_001E7E70(i + 0x14, -1, func_001F2920(i + 0x14));
    }
    func_002099D0();
    func_002098B0(1);
    result = func_00242470(arg0, arg1, arg2);
    func_001854E0(0);
    func_002098B0(0);
    func_001A8520(10, 0, 0, 0, 0x400, 0x400);
    if (flag != 0) {
        func_00109D70(0);
        func_00217410();
    }
    return result;
}

typedef union {
    u32 words[4];
    u64 halves[2];
    __int128 quad;
} Packet_001A8520;

s32 func_00184E10(void *, s64, s64, s64, s64, s64);
s32 func_00184FF8(void *, s64, s64, s64, s64, s64, s32, s32, s64, s64, s64);
s32 func_00186120(s32);
void func_00186470(s32, void *);

void func_001A8520(s64 arg0, s32 arg1, s32 arg2, s64 arg3, s64 arg4, s64 arg5) {
    Packet_001A8520 packet[20];
    s32 channel;
    u8 *cursor;

    channel = func_00186120(2);
    cursor = (u8 *)packet;
    *(u32 *)(cursor + 0) = 0x10000010;
    *(u32 *)(cursor + 4) = 0;
    *(u32 *)(cursor + 8) = 0;
    *(u32 *)(cursor + 12) = 0;
    *(u64 *)(cursor + 16) = 0x1000000000000008ULL;
    *(u64 *)(cursor + 24) = 0xE;
    cursor += 32;
    cursor += func_00184E10(cursor, (s16)arg0, (s16)arg4, (s16)arg5, 0, 0) * 16;
    *(u64 *)(cursor + 0) = 0x1000000000008006ULL;
    *(u64 *)(cursor + 8) = 0xE;
    cursor += 16;
    cursor += func_00184FF8(cursor, 2, 0, 0, 0xFFF, 0xFFF, arg1, arg2, arg3, 0, 0) * 16;
    *(u32 *)(cursor + 0) = 0x70000000;
    *(u32 *)(cursor + 4) = 0;
    *(u32 *)(cursor + 8) = 0;
    *(u32 *)(cursor + 12) = 0;
    func_0017BB60(0);
    func_00185578(0, 0);
    func_00186470(channel, packet);
    func_00185578(0, 0);
}

s8 func_001A8690(void) {
    return D_0031747B;
}

typedef struct {
    u8 pad00[0xF4];
    u32 count;
    u8 padF8[0x133];
    s8 selected;
} State_001A86A0;

void func_001A86A0(s32 arg0) {
    State_001A86A0 *state = (State_001A86A0 *)&D_00317250;

    if ((arg0 >= 0) && ((u32)arg0 < state->count)) {
        state->selected = arg0;
    }
}

typedef struct Flags_001A86D0 {
    s8 reserved0 : 5;
    s8 enabled : 1;
    s8 flag6 : 1;
    s8 reserved1 : 1;
} Flags_001A86D0;

extern Flags_001A86D0 D_0031747E;

s32 func_001A86D0(void) {
    return D_0031747E.enabled != 0 ? 1 : 0;
}

s32 func_001A86F0(void) {
    D_00317250 += 1;
    return 1;
}

s32 func_001A8710(void) {
    return *(s32 *)0x10000800;
}

s32 func_001A8720(void) {
    return D_00317254;
}

s32 func_001A8730(void) {
    return ++D_00317254;
}

void func_001A8750(s32 arg0) {
    D_0031747A = (s8) arg0;
}

u8 func_001A8760(void) {
    return D_0031747A;
}

void func_001A8770(s64 arg0) {
    D_0031747E.flag6 = arg0;
}

s32 func_001A87A0(void) {
    return D_0031747E.flag6 != 0 ? 1 : 0;
}

typedef struct {
    s8 padding[0x1F9];
    s8 values[0x28];
    s8 index;
    u8 base;
} State_001A87C0;

typedef struct {
    s8 a;
    s8 b;
    s8 c;
} Tail_001A87C0;

void func_001AAAF0(s32, s32);
extern Tail_001A87C0 D_0031746F;

void func_001A87C0(s32 arg0, s32 arg1) {
    State_001A87C0 *state = (State_001A87C0 *)&D_00317250;

    func_001FCC70(0, 1, 1, 0, 60, 0);
    D_0031746F.a = -2;
    D_0031746F.b = arg0;
    D_0031746F.c = 0;
    if (arg1 >= 0) {
        *((s8 *)(state->index + (state->base + (s32)state)) + 0x1F9) = arg1;
    }
    if (arg1 < 2) {
        func_001AAAF0(-2, 1);
    }
}

void func_001AAAF0(s32, s32);
extern u8 D_00317472;

typedef struct State_001A8870 {
    u8 pad_000[0x1F9];
    s8 entries[0x26];
    s8 field_21F;
    s8 field_220;
    s8 field_221;
    u8 field_222;
} State_001A8870;

void func_001A8870(s32 arg0, s32 arg1) {
    State_001A8870 *state = (State_001A8870 *)&D_00317250;
    s8 *entry;

    if ((D_00317472 + 1) < 8) {
        func_001FCC70(0, 1, 1, 0, 60, 0);
        state->field_21F = -2;
        state->field_220 = arg0;
        state->field_221 = 1;
        entry = (s8 *)(state->field_222 + (u32)state);
        entry[state->field_221 + 0x1F9] = arg1;
        if (arg1 < 2) {
            func_001AAAF0(-2, 1);
        }
    }
}

typedef struct {
    u8 padding[0x1F0];
    s8 entries[0x2F];
    s8 state;
    s8 selected;
    s8 previous;
    u8 index;
} State_001A8920;

void func_001AAAF0(s32, s32);
extern u8 D_00317472;

void func_001A8920(void) {
    State_001A8920 *state = (State_001A8920 *)&D_00317250;

    if ((D_00317472 - 1) >= 0) {
        func_001FCC70(0, 1, 1, 0, 60, 0);
        state->state = -2;
        state->selected = state->entries[state->index];
        state->previous = -1;
        if (state->entries[state->index + 1] < 2) {
            func_001AAAF0(-2, 1);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/main_037", func_001A89C0);

void func_001A8BB0(void) {
    extern s32 func_001F1A80(s32, f32);
    s32 i;

    func_001E2FB0(0, 0, 1);
    func_001E2340();
    func_001F9F90(0, 0);
    func_001F9A80(0, 800.0f);
    func_001F9FE0(0, 0, 0);
    func_001FB6A0(0, 0, 1, 3.0434179f, 0.19634955f, 0.0f);

    for (i = 0; i < 10; i++) {
        func_001F9230(0, i, 0);
        func_001F9310(0, i, 0);
        func_001F9770(0, i, 0);
        func_001F9940(0, i, 0);
    }
    for (i = 0; i < 10; i++) {
        func_001F29E0(i + 20, 0);
        func_001F2AD0(i + 20, 0);
    }
    for (i = 0; i < 2; i++) {
        func_001F29E0(i + 30, 0);
        func_001F2AD0(i + 30, 0);
    }
    for (i = 0; i < 84; i++) {
        func_001F30B0(i, 0);
        func_001F25D0(i, NULL);
        func_001F24C0(i, NULL);
        func_001F29E0(i, 0);
        func_001F2AD0(i, 0);
        func_001F1830(i, 0);
        func_001F1A00(i, 1);
        func_001F1A80(i, 1.0f);
        func_001F26E0(i, 0, NULL);
        func_001F2860(i, 1, NULL);
        func_001F1EE0(i, NULL);
    }
    func_001F6CE0(0x80);
    func_001F6CF0(0x80);
    func_001F6D00(0x80);
}

INCLUDE_ASM("asm/nonmatchings/main_037", func_001A8DB0);

INCLUDE_ASM("asm/nonmatchings/main_037", func_001A9590);

typedef struct Flags_001A9800 {
    u8 unused:4;
    u8 state:2;
    u8 unused2:2;
} Flags_001A9800;

extern Flags_001A9800 D_0031747C;

void func_001A9800(void) {
    u8 *data = (u8 *) &D_00317250;
    s64 temp_v0;

    temp_v0 = func_001AAF60(1);
    if (D_0031747C.state < 3) {
        switch (data[0x228]) {
        default:
            return;
        case 0:
            switch (temp_v0) {
            case 1:
                func_001B81E0();
                func_001B83C0();
                break;
            case 11:
                func_002085A0(2);
                func_0021DAA0();
                func_00246490();
                break;
            }
            func_001AF7B0();
            break;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/main_037", func_001A98B0);

INCLUDE_ASM("asm/nonmatchings/main_037", func_001A9F50);

typedef struct {
    u8 unused0 : 4;
    u8 mode : 2;
    u8 unused6 : 2;
} Mode_001AA260;

typedef struct {
    s8 unused0 : 4;
    s8 pending : 1;
    s8 busy : 1;
    s8 unused6 : 2;
} Flags_001AA260;

typedef struct {
    s8 enabled : 1;
    s8 unused1 : 7;
} Toggle_001AA260;

typedef struct {
    u8 pad000[0xC];
    s32 field00C;
    u8 pad010[0x180];
    s32 field190;
    u8 pad194[0x5C];
    s8 entries[0x1C];
    u8 red;
    u8 green;
    u8 blue;
    u8 alpha;
    u8 pad210[4];
    s32 x;
    s32 y;
    u8 pad21C[3];
    s8 selection;
    s8 entry;
    s8 field221;
    u8 index;
    u8 pad223[5];
    u8 wait;
    u8 pad229[3];
    Mode_001AA260 mode;
    u8 pad22D;
    Flags_001AA260 flags;
    Toggle_001AA260 toggle;
} State_001AA260;

extern u8 D_00317472;

void func_001A7380(void);
void func_001AC700(void);
void func_001B8840(void);
void func_001CC620(void);
s32 func_001CEE60(void);
void func_001D95F0(void);
void func_001EAA60(s32);
void func_001EDA40(s32, s32);
void func_001F7790(s32);
void func_001FCAB0(void);
void func_002009E0(s32, s32);
void func_00203E20(void);
void func_00237730(void);
void func_00285F20(void);

void func_001AA260(void) {
    extern void func_001AAAF0();
    State_001AA260 *state;
    s64 event;
    s32 i;
    s32 position;
    s32 j0;
    s32 j5;
    s32 j12;
    s32 step;

    state = (State_001AA260 *)&D_00317250;
    event = func_001AAF60(0);
    switch (D_0031747C.state) {
    case 3:
        if (func_001FF300() != 0) {
            return;
        }
        if (state->field190 != 0) {
            func_001AAAF0(event, 1);
        }
        if (state->flags.pending != 0) {
            state->wait = 0x80;
        }
        state->mode.mode--;
        return;
    case 2:
        if (((D_0031747E.enabled != 0 ? 1 : 0) != 0) && (func_002179C0() != 0)) {
            return;
        }
        switch (event) {
        case 1:
            func_002009E0(4, 1);
            func_002009E0(1, 0);
            func_002009E0(2, 0);
            func_002009E0(3, 0);
            break;
        case 6:
        case 8:
            func_002009E0(0, 0);
            break;
        }
        state->mode.mode--;
        return;
    case 1:
        if (state->wait != 0) {
            return;
        }
        func_001FD130(1, 0);
        state->field00C = 0;
        break;
    }

    if (func_00217530() != 0) {
        for (i = 0; i < 2; i++) {
            position = func_001E5240(i);
            if (position < 0) {
                continue;
            }
            func_001EDA40(i + 2, func_001E1360(position >> 8, position & 0xFF));
        }
        func_001F3F20();
    }
    i = 0;
    do {
        func_001ED4A0(i);
        i++;
    } while (i < 0x54);
    func_001F3870();
    if (func_001FD220(1) != 0) {
        return;
    }
    switch (event) {
    case -3:
        break;
    case -2:
    case -1:
        func_001A7380();
        break;
    case 0:
        func_00203E20();
        if (func_002051F0() == 0) {
            j0 = 0;
            do {
                func_001EAA60(j0);
                j0++;
            } while (j0 < 0x54);
        }
        func_001F7790(0);
        break;
    case 1:
        do {
        } while (func_001CEE60() != 0);
        break;
    case 5:
        func_00203E20();
        if (func_002051F0() == 0) {
            j5 = 0;
            do {
                func_001EAA60(j5);
                j5++;
            } while (j5 < 0x54);
        }
        func_001F7790(0);
        break;
    case 6:
        func_001B8840();
        break;
    case 7:
        func_001C12B0();
        break;
    case 8:
        func_001C2540();
        break;
    case 9:
        func_001C6130();
        break;
    case 36:
        func_001AC560();
        break;
    case 10:
        func_001AC700();
        break;
    case 11:
        func_00237730();
        func_002464C0();
        break;
    case 12:
        func_00203E20();
        if (func_002051F0() == 0) {
            j12 = 0;
            do {
                func_001EAA60(j12);
                j12++;
            } while (j12 < 0x54);
        }
        func_001F7790(0);
        break;
    case 13:
        func_001CC620();
        break;
    case 18:
        func_001D95F0();
        break;
    case 19:
        func_001FCAB0();
        func_001F7790(0);
        break;
    case 14:
        func_002464C0();
        break;
    case 15:
        func_00285F20();
        break;
    case 17:
        step = 1;
        if (func_00203A40(0, 0, 0x10) != 0) {
            state->toggle.enabled = (s8)(state->toggle.enabled != 0 ? 0 : 1);
        }
        if (func_00203A40(0, 1, 0x20) != 0) {
            step = 2;
        }
        if (func_00203A40(0, 1, 0x80) != 0) {
            step = 2;
        }
        if (func_00203A40(0, 1, 0xF000) != 0) {
            if (func_00203A40(0, 1, 0x8000) != 0) {
                state->x -= step;
            }
            if (func_00203A40(0, 1, 0x2000) != 0) {
                state->x += step;
            }
            if (func_00203A40(0, 1, 0x1000) != 0) {
                state->y -= step;
            }
            if (func_00203A40(0, 1, 0x4000) != 0) {
                state->y += step;
            }
        }
        if (func_00203A40(1, 1, 0x1000) != 0) {
            if (func_00203A40(1, 2, 0x80) != 0) {
                if (state->alpha > 0) {
                    state->alpha--;
                }
            }
            if (func_00203A40(1, 2, 0x20) != 0) {
                if (state->alpha < 0xFF) {
                    state->alpha++;
                }
            }
        } else {
            if (func_00203A40(1, 2, 0x81) != 0) {
                if (state->blue > 0) {
                    state->blue--;
                }
            }
            if (func_00203A40(1, 2, 0x22) != 0) {
                if (state->blue < 0xFF) {
                    state->blue++;
                }
            }
            if (func_00203A40(1, 2, 0x41) != 0) {
                if (state->green > 0) {
                    state->green--;
                }
            }
            if (func_00203A40(1, 2, 0x12) != 0) {
                if (state->green < 0xFF) {
                    state->green++;
                }
            }
            if (func_00203A40(1, 2, 5) != 0) {
                if (state->red > 0) {
                    state->red--;
                }
            }
            if (func_00203A40(1, 2, 10) != 0) {
                if (state->red < 0xFF) {
                    state->red++;
                }
            }
        }
        if (func_00203A40(0, 0, 0x20) != 0) {
            state = (State_001AA260 *)&D_00317250;
            if ((D_00317472 - 1) >= 0) {
                func_001FCC70(0, 1, 1, 0, 0x3C, 0);
                state->selection = -2;
                state->entry = state->entries[state->index];
                state->field221 = -1;
                if (state->entries[state->index + 1] < 2) {
                    func_001AAAF0(-2, 1);
                }
            }
        }
        break;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_037", func_001AAAF0);

INCLUDE_ASM("asm/nonmatchings/main_037", func_001AAD50);

typedef struct {
    u8 pad[0x1F1];
    s8 values[0x2D];
    s8 negative;
    s8 zero;
    u8 pad220[2];
    u8 selected;
} State_001AAF60;

s64 func_001AAF60(s32 arg0) {
    s8 value;
    State_001AAF60 *state = (State_001AAF60 *)&D_00317250;

    if (arg0 > 0) {
        value = state->values[state->selected];
    } else if (arg0 < 0) {
        value = state->negative;
    } else {
        value = state->zero;
    }
    return value;
}

INCLUDE_ASM("asm/nonmatchings/main_037", func_001AAFA0);

INCLUDE_ASM("asm/nonmatchings/main_037", func_001AB1D0);

INCLUDE_ASM("asm/nonmatchings/main_037", func_001AC290);

void func_001AC510(void) {
    s32 i;

    i = 0;
    do {
        func_001F30B0(i, 0);
        i += 1;
    } while (i < 0x54);
    func_001AAFA0(6);
}

typedef struct Block_001AC560 {
    u8 entries[0x26];
    s8 mode;
    s8 selected;
    s8 previous;
    u8 index;
} Block_001AC560;

void func_001AAAF0(s32, s32);
s32 func_001AB1D0(void);
extern s32 D_003173B0;
extern Block_001AC560 D_00317449;

void func_001AC560(void) {
    if (func_001AB1D0() < 0) {
        D_003173B0 = 0;
        func_001FCC70(0, 1, 1, 0, 60, 0);
        D_00317449.mode = -2;
        D_00317449.selected = 10;
        D_00317449.previous = 0;
        D_00317449.entries[D_00317449.index + D_00317449.previous] = 0;
        func_001AAAF0(-2, 1);
    }
}

void func_001AC600(void) {

}

typedef struct State_001AC610 {
    s32 pad0[2];
    s32 counter;
    u8 padC[0x218];
    u8 red;
    u8 green;
    u8 blue;
    u8 alpha;
    u8 pad228[4];
    s8 mode : 2;
    s8 pad22C : 6;
    u8 pad22D[2];
    s8 pad22F : 1;
    s8 enabled : 1;
    s8 pad22FHigh : 6;
} State_001AC610;

extern s32 D_003173B0;

void func_001AC610(s32 arg0) {
    State_001AC610 *state = (State_001AC610 *)&D_00317250;
    s32 i;

    i = 0;
    do {
        func_001F30B0(i, 0);
        i += 1;
    } while (i < 0x54);
    i = 0;
    do {
        func_001F30B0(i + 0x22, 1);
        i += 1;
    } while (i < 0x28);
    if (arg0 < 2) {
        D_003173B0 = 2;
        state->red = 0;
        state->green = 0;
        state->blue = 0;
        state->alpha = 0x80;
        state->mode = 1;
        state->enabled = 1;
        state->counter = 0;
    }
}

void func_001AC6F0(void) {

}

INCLUDE_ASM("asm/nonmatchings/main_037", func_001AC700);

void func_001ACC50(void) {
    func_00209D30(func_001ACC80(func_00209D20()));
}

INCLUDE_ASM("asm/nonmatchings/main_037", func_001ACC80);

INCLUDE_ASM("asm/nonmatchings/main_037", func_001AD670);

void func_001AD960(void) {
    u8 *state = D_00317490;
    s32 x;
    s32 y;
    u8 *cell;
    s32 group;
    s32 index;
    u8 *entry;
    u8 *row;

    func_0020B3C0((s8 *)D_00317490, 0, 0xD70);
    func_001CDA10();
    func_001CDD40();
    y = 0;
    do {
        x = 0;
        do {
            cell = func_001DCD00(x, y);
            func_001DCC90(cell);
            cell[0x16] = (y + x) % 10;
            x++;
        } while (x < 7);
        y++;
    } while (y < 7);

    row = D_00318280;
    group = 0;
    do {
        index = 0;
        entry = row;
        do {
            func_001DCD70(entry, -1);
            index++;
            entry += 0x5C;
        } while (index < 11);
        group++;
        row += 0x3F4;
    } while (group < 3);

    state[0x33C] = 100;
    state[0x68C] = 100;
    func_001ADD00(0, 0, 0);
}

void func_001ADA80(s32 arg0) {
    extern s32 func_001AAF60();
    s32 mode;
    s32 i;

    mode = func_001AAF60(1);
    func_001F9770(0, 9, 1);
    i = 0;
    do {
        func_001F30B0(i, 0);
        i++;
    } while (i < 0x54);
    i = 0;
    do {
        func_001F30B0(i, 1);
        i++;
    } while (i < 5);
    i = 0;
    do {
        func_001F30B0(i + 5, 1);
        i++;
    } while (i < 2);
    i = 0;
    do {
        func_001F30B0(i + 0x14, 1);
        i++;
    } while (i < 0xA);
    i = 0;
    do {
        func_001F30B0(i + 0x1E, 1);
        i++;
    } while (i < 2);
    i = 0;
    do {
        func_001F30B0(i + 0x20, 1);
        i++;
    } while (i < 2);
    i = 0;
    do {
        func_001F30B0(i + 0x4A, 1);
        i++;
    } while (i < 0xA);
    if (mode == 1) {
        s32 j = 0;
        do {
            func_001F29E0(j + 0x14, 1);
            func_001F2AD0(j + 0x14, 0x20);
            j++;
        } while (j < 0xA);
        j = 0;
        do {
            func_001F29E0(j + 0x1E, 1);
            func_001F2AD0(j + 0x1E, 0x20);
            j++;
        } while (j < 2);
    }
    if (arg0 != 0) {
        s32 color = (s32) &D_00291000;
        s32 ambient = (s32) &D_0029100C;
        s32 matrix = (s32) &D_00291020;
        s32 range = (s32) &D_002910B0;
        s32 position = (s32) &D_002910B8;

        func_001F68D0((s32) position);
        func_001F6910((s32) position);
        func_001F69A0(0);
        func_001F69E0(0);
        if (((f32 *) range)[0] == ((f32 *) range)[1]) {
            func_001F6A70(0);
            func_001F6AB0(0);
        } else {
            func_001F6A70((s32) range);
            func_001F6AB0((s32) range);
        }
        func_001F6B40((s32) matrix);
        func_001F6B80((s32) matrix);
        func_001F6C10(0);
        func_001F6C50(0);
        func_001F6D40((s32) ambient);
        func_001F6D80((s32) color);
        func_001F6CE0(0x80);
        func_001F6CF0(0x80);
    }
}

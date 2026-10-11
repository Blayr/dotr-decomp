#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_037", func_001A6C30);

INCLUDE_ASM("asm/nonmatchings/main_037", func_001A6C48);

INCLUDE_ASM("asm/nonmatchings/main_037", func_001A6C60);

INCLUDE_ASM("asm/nonmatchings/main_037", func_001A6C80);

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

INCLUDE_ASM("asm/nonmatchings/main_037", func_001A8360);

INCLUDE_ASM("asm/nonmatchings/main_037", func_001A83E0);

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

INCLUDE_ASM("asm/nonmatchings/main_037", func_001A8690);

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
    s8 reserved1 : 2;
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

INCLUDE_ASM("asm/nonmatchings/main_037", func_001A8750);

INCLUDE_ASM("asm/nonmatchings/main_037", func_001A8760);

INCLUDE_ASM("asm/nonmatchings/main_037", func_001A8770);

INCLUDE_ASM("asm/nonmatchings/main_037", func_001A87A0);

INCLUDE_ASM("asm/nonmatchings/main_037", func_001A87C0);

INCLUDE_ASM("asm/nonmatchings/main_037", func_001A8870);

typedef struct {
    u8 padding[0x1F0];
    s8 entries[0x2F];
    s8 state;
    s8 selected;
    s8 previous;
    u8 index;
} State_001A8920;

void func_001AAAF0(s32, s32);
void func_001FCC70(s32, s32, s32, s32, s32, s32);
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

INCLUDE_ASM("asm/nonmatchings/main_037", func_001A8BB0);

INCLUDE_ASM("asm/nonmatchings/main_037", func_001A8DB0);

INCLUDE_ASM("asm/nonmatchings/main_037", func_001A9590);

INCLUDE_ASM("asm/nonmatchings/main_037", func_001A9800);

INCLUDE_ASM("asm/nonmatchings/main_037", func_001A98B0);

INCLUDE_ASM("asm/nonmatchings/main_037", func_001A9F50);

INCLUDE_ASM("asm/nonmatchings/main_037", func_001AA260);

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

INCLUDE_ASM("asm/nonmatchings/main_037", func_001AC560);

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

INCLUDE_ASM("asm/nonmatchings/main_037", func_001ADA80);

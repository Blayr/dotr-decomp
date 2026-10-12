#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_058", func_0020CB20);

INCLUDE_ASM("asm/nonmatchings/main_058", func_0020CB90);

void func_0020CBD0(s32 arg0) {
    f32 matrix[4][4];

    func_0020C750(matrix);
    func_0020BC00(arg0, matrix);
}

INCLUDE_ASM("asm/nonmatchings/main_058", func_0020CC10);

INCLUDE_ASM("asm/nonmatchings/main_058", func_0020CDD0);

INCLUDE_ASM("asm/nonmatchings/main_058", func_0020CF00);

void func_0020D070(f32 *arg0) {
    f32 length;

    length = func_001A6C60(arg0[0] * arg0[0] + arg0[1] * arg0[1] + arg0[2] * arg0[2]);
    arg0[0] /= length;
    arg0[1] /= length;
    arg0[2] /= length;
    arg0[3] = arg0[3];
}

f32 func_0020D0E0(f32 *arg0) {
    return func_001A6C60(arg0[0] * arg0[0] + arg0[1] * arg0[1] + arg0[2] * arg0[2]);
}

f32 func_0020D100(f32 *arg0, f32 *arg1) {
    f32 x = arg0[0] - arg1[0];
    f32 y = arg0[1] - arg1[1];
    f32 z = arg0[2] - arg1[2];

    return func_001A6C60(x * x + y * y + z * z);
}

void func_0020D140(f32 *arg0, f32 *arg1, f32 *arg2) {
    arg0[0] = arg1[1] * arg2[2] - arg1[2] * arg2[1];
    arg0[1] = arg1[2] * arg2[0] - arg1[0] * arg2[2];
    arg0[2] = arg1[0] * arg2[1] - arg1[1] * arg2[0];
    arg0[3] = arg1[3];
}

f32 func_0020D1A0(f32 *arg0, f32 *arg1) {
    return arg0[0] * arg1[0] + arg0[1] * arg1[1] + arg0[2] * arg1[2];
}

INCLUDE_ASM("asm/nonmatchings/main_058", func_0020D1D0);

INCLUDE_ASM("asm/nonmatchings/main_058", func_0020D240);

INCLUDE_ASM("asm/nonmatchings/main_058", func_0020D5E0);

INCLUDE_ASM("asm/nonmatchings/main_058", func_0020D8E0);

INCLUDE_ASM("asm/nonmatchings/main_058", func_0020D9F0);

INCLUDE_ASM("asm/nonmatchings/main_058", func_0020DA70);

INCLUDE_ASM("asm/nonmatchings/main_058", func_0020DB00);

INCLUDE_ASM("asm/nonmatchings/main_058", func_0020DB20);

INCLUDE_ASM("asm/nonmatchings/main_058", func_0020DB80);

INCLUDE_ASM("asm/nonmatchings/main_058", func_0020DBE0);

INCLUDE_ASM("asm/nonmatchings/main_058", func_0020DDB0);

s32 func_0020DEE0(void) {
    return 1;
}

typedef struct {
    __int128 data[9];
} Copy_0020DEF0;

extern u8 D_0032A360[];

s32 func_0020DEF0(void *arg0) {
    *(Copy_0020DEF0 *)arg0 =
        *(Copy_0020DEF0 *)(D_0032A360 + D_0032A240 * 0x1A0);
    return 1;
}

typedef struct State_0020DF40 {
    u8 pad000[0x150];
    f32 field150;
    f32 field154;
    u8 pad158[8];
    f32 field160;
    f32 field164;
    f32 field168;
    u8 pad16C[0x34];
} State_0020DF40;

s32 func_0020DF40(f32 fparg0, f32 fparg1, f32 fparg2, f32 fparg3, f32 fparg4) {
    extern State_0020DF40 D_0032A2A0[];
    State_0020DF40 *state;

    state = &D_0032A2A0[D_0032A240];
    state->field160 = fparg0;
    state->field164 = fparg1;
    state->field168 = fparg2;
    state->field150 = fparg3;
    state->field154 = fparg4;
    return 1;
}

typedef struct State_0020DF90 {
    u8 pad0[0x158];
    f32 field158;
    f32 field15C;
    u8 pad160[0x40];
} State_0020DF90;

s32 func_0020DF90(f32 fparg0, f32 fparg1) {
    extern State_0020DF90 D_0032A2A0[];
    State_0020DF90 *state;

    state = &D_0032A2A0[D_0032A240];
    state->field158 = fparg0;
    state->field15C = fparg1;
    return 1;
}

typedef struct {
    u8 pad_000[0x16C];
    f32 x;
    f32 y;
    u8 pad_174[0x2C];
} Entry_0020DFD0;

s32 func_0020DFD0(f32 fparg0, f32 fparg1) {
    extern Entry_0020DFD0 D_0032A2A0[];
    Entry_0020DFD0 *entry;

    entry = &D_0032A2A0[D_0032A240];
    entry->x = fparg0;
    entry->y = fparg1;
    return 1;
}

typedef struct {
    u8 pad0[0x150];
    f32 x;
    f32 y;
    u8 pad158[0x48];
} Entry_0020E010;

extern s32 D_0032A240;
extern Entry_0020E010 D_0032A2A0[];

s32 func_0020E010(f32 *arg0, f32 *arg1) {
    Entry_0020E010 *e = &D_0032A2A0[D_0032A240];

    *arg0 = e->x;
    *arg1 = e->y;
    return 1;
}

s32 func_0020E050(f32 *arg0) {
    Entry_0020E010 *e = &D_0032A2A0[D_0032A240];

    *arg0 = *(f32 *)&e->pad158[8];
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_058", func_0020E090);

INCLUDE_ASM("asm/nonmatchings/main_058", func_0020E0D0);

INCLUDE_ASM("asm/nonmatchings/main_058", func_0020E130);

INCLUDE_ASM("asm/nonmatchings/main_058", func_0020E1A0);

INCLUDE_ASM("asm/nonmatchings/main_058", func_0020E260);

INCLUDE_ASM("asm/nonmatchings/main_058", func_0020E360);

INCLUDE_ASM("asm/nonmatchings/main_058", func_0020E460);

s32 func_0020E4F0(void) {
    if (D_0032A240 <= 0) {
        return 0;
    }
    D_0032A240 -= 1;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_058", func_0020E520);

typedef struct {
    u8 padding[0x44];
    s32 ready;
} State_0020E970;

typedef struct {
    __int128 data[9];
} Buffer_0020E970;

extern State_0020E970 D_0032A250;
extern s32 D_0032A294;
extern u8 D_0032A360[];

s32 func_0020E970(void *arg0) {
    State_0020E970 *state = &D_0032A250;

    if (D_0032A294 == 0) {
        return 0;
    }
    if (D_0032A240 > 0) {
        D_0032A240 -= 1;
    }
    state->ready = 0;
    *(Buffer_0020E970 *)arg0 = *(Buffer_0020E970 *)D_0032A360;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_058", func_0020E9F0);

INCLUDE_ASM("asm/nonmatchings/main_058", func_0020EB40);

typedef struct {
    s32 words[16];
} Block_0020EBA0;

extern u8 D_0032A2E0[][0x1A0];

void func_0020EBA0(void *arg0) {
    *(Block_0020EBA0 *)arg0 = *(Block_0020EBA0 *)D_0032A2E0[D_0032A240];
}

typedef struct {
    s32 words[16];
} Block_0020EC00;

typedef struct {
    Block_0020EC00 block;
    u8 padding[0x160];
} Entry_0020EC00;

extern Entry_0020EC00 D_0032A320[];

void func_0020EC00(void *dst) {
    *(Block_0020EC00 *)dst = D_0032A320[D_0032A240].block;
}

INCLUDE_ASM("asm/nonmatchings/main_058", func_0020EC60);

INCLUDE_ASM("asm/nonmatchings/main_058", func_0020ED30);

INCLUDE_ASM("asm/nonmatchings/main_058", func_0020EDE0);

void func_0020F250(s32 arg0) {
    u8 *entry;
    s32 i;
    s32 count;

    *(s32 *)((u8 *)arg0 + 0xC) = arg0;
    count = *(s32 *)((u8 *)arg0 + 0x58);
    entry = (u8 *)arg0 + *(s32 *)((u8 *)arg0 + 0x10);
    for (i = 0; i < count; i += 1) {
        *(s32 *)(entry + 4) = arg0 + *(s32 *)(entry + 4);
        entry += 0x30;
    }
}

s32 func_0020F290(s32 arg0) {
    func_001875F8(D_0032A5E0, arg0);
    func_00187660(D_0032A5E0, 0);
    func_001877F8(D_0032A5E0, 0x11000000);
    func_00187778(D_0032A5E0, 2, 3);
    func_00187858(D_0032A5E0, 0);
    *(u64 *)&D_0032A600 = 0x8000 | ((u64)0x10000000 << 32);
    *((u64 *)&D_0032A600 + 1) = 0xE;
    func_001876B8(D_0032A5E0, D_0032A600);
    func_00187828(D_0032A5E0, 0x3F, 1);
    func_001876D0(D_0032A5E0);
    func_001878B0(D_0032A5E0);
    return func_00187608(D_0032A5E0);
}

s32 func_0020F370(void *arg0) {
    s32 *sections;
    s32 i;
    u32 *entries;
    u32 value;
    u32 *target;
    u8 *resolved;

    sections = (s32 *)((u8 *)arg0 + 0x10);
    entries = (u32 *)((u8 *)arg0 + *(s32 *)((u8 *)arg0 + 0x50));
    for (i = 0; entries[i] != 0xFFFFFFFF; i++) {
        value = entries[i];
        switch (value & 0xF0000000) {
        case 0x20000000:
            target = (u32 *)((u8 *)arg0 + sections[2] + (value & 0x0FFFFFFF));
            break;
        case 0x30000000:
            target = (u32 *)((u8 *)arg0 + sections[4] + (value & 0x0FFFFFFF));
            break;
        case 0x40000000:
            target = (u32 *)((u8 *)arg0 + sections[6] + (value & 0x0FFFFFFF));
            break;
        case 0x50000000:
            target = (u32 *)((u8 *)arg0 + sections[8] + (value & 0x0FFFFFFF));
            break;
        default:
            continue;
        }
        value = *target;
        switch (value & 0xF0000000) {
        case 0x20000000:
            resolved = (u8 *)arg0 + sections[2] + (value & 0x0FFFFFFF);
            break;
        case 0x30000000:
            resolved = (u8 *)arg0 + sections[4] + (value & 0x0FFFFFFF);
            break;
        case 0x40000000:
            resolved = (u8 *)arg0 + sections[6] + (value & 0x0FFFFFFF);
            break;
        case 0x50000000:
            resolved = (u8 *)arg0 + sections[8] + (value & 0x0FFFFFFF);
            break;
        default:
            continue;
        }
        *target = (u32)resolved;
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_058", func_0020F4E0);

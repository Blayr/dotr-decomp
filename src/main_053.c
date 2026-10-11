#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FB500);

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

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FCA70);

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

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FCDE0);

void func_001FCF30(s32 arg0, s32 arg1, s32 arg2) {
    func_00209D30(func_001FCF90(func_00209D20(), arg0, arg1, arg2));
}

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FCF90);

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

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FD4B0);

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FD4C0);

void func_001FD610(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_00209D30(func_001FD680(func_00209D20(), arg0, arg1, arg2, arg3));
}

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FD680);

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FDB90);

INCLUDE_ASM("asm/nonmatchings/main_053", func_001FDD70);

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

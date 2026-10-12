#include "common.h"

void func_001CDD40(void) {
    u8 *p;
    s32 i;

    p = D_0031A7C0;
    i = 0;
    do {
        func_001CDD90(p);
        i += 1;
        p += 0xA0;
    } while (i < 6);
}

typedef struct State_001CDD90 {
    s32 value;
    u8 padding[0x94];
    s16 field98;
    s16 field9A;
    u32 field9C : 26;
    u32 reserved : 6;
} State_001CDD90;

typedef struct Flags_001CDD90 {
    s8 reserved : 2;
    s8 bit2 : 1;
    s8 bit3 : 1;
    s8 bit4 : 1;
    s8 bit5 : 1;
    s8 bit6 : 1;
    s8 bit7 : 1;
} Flags_001CDD90;

s32 func_001CDD90(u8 *arg0) {
    State_001CDD90 *state = (State_001CDD90 *)arg0;
    Flags_001CDD90 *flags;

    if (arg0 == NULL) {
        return 0;
    }
    state->value = 0;
    state->field98 = 0;
    state->field9A = 0;
    state->field9C = 0xFF;
    flags = (Flags_001CDD90 *)(arg0 + 0x9F);
    flags->bit2 = 0;
    flags->bit3 = 0;
    flags->bit4 = 0;
    flags->bit5 = 0;
    flags->bit6 = 0;
    flags->bit7 = 0;
    return 1;
}

void *func_001CDE70(s32 arg0) {
    if (arg0 < 0 || arg0 >= 6) {
        return NULL;
    }

    return &D_0031A7C0[arg0 * 0xA0];
}

INCLUDE_ASM("asm/nonmatchings/main_042", func_001CDEB0);

void func_001CE400(void) {
    func_00209D30(func_001CE430(func_00209D20()));
}

INCLUDE_ASM("asm/nonmatchings/main_042", func_001CE430);

typedef struct Vec4_001CEA50 {
    f32 x, y, z, w;
} Vec4_001CEA50;

typedef struct Flags_001CEA50 {
    s8 unused : 4;
    s8 horizontal : 1;
    s8 enabled : 1;
    s8 colored : 1;
    s8 reserved : 1;
} Flags_001CEA50;

typedef struct Draw_001CEA50 {
    u8 pad00[0x10];
    Vec4_001CEA50 position;
    u8 bounds[0x10];
    Vec4_001CEA50 color;
    u8 pad40[0x41];
    Flags_001CEA50 flags;
    u8 pad82[0xE];
} Draw_001CEA50;

s32 func_001D9F00(void *, s32);
void func_001DA2B0(void *, s32, f32, f32);
extern Vec4_001CEA50 D_0031825C;
extern s32 D_00318270;

void func_001CEA50(void) {
    extern void func_001CD560();
    u8 matrix[0x60];
    Draw_001CEA50 draw;

    func_001CD560(&draw);
    draw.flags.enabled = 1;
    draw.flags.colored = 0;
    draw.flags.reserved = 0;
    func_001DCD70(matrix, func_001DE130(D_00318270));
    func_00205C40((s32) draw.bounds);
    draw.position = D_0031825C;
    func_001D99F0();
    draw.flags.horizontal = 1;
    func_001DA2B0(&draw, 0, -192.0f, 0.0f);
    func_001DA7A0((s32) matrix, (s32) &draw);
    func_001DBCF0((s32) &draw);
    draw.flags.horizontal = 0;
    func_001DA2B0(&draw, 0, 0.0f, -96.0f);
    func_001DA7A0((s32) matrix, (s32) &draw);
    func_001DBCF0((s32) &draw);
    draw.flags.horizontal = 1;
    func_00205CB0(&draw, 192.0f, 0.0f);
    func_001DA7A0((s32) (func_001D9F00(&draw, 1) ? matrix : NULL), (s32) &draw);
    func_001DBCF0((s32) &draw);
    draw.flags.horizontal = 0;
    func_00205CB0(&draw, 0.0f, 96.0f);
    func_001DA7A0((s32) (func_001D9F00(&draw, 1) ? matrix : NULL), (s32) &draw);
    func_001DBCF0((s32) &draw);
    if (func_00203A40(0, 1, 0x80) != 0) {
        draw.flags.colored = 1;
        draw.color.x = 0.46875f;
        draw.color.y = 0.489130437f;
        draw.color.z = 1.0f;
        draw.color.w = 0.0f;
        draw.flags.horizontal = 1;
        func_00205CB0(&draw, 0.0f, 96.0f);
        func_001DA7A0((s32) (func_001D9F00(&draw, 1) ? matrix : NULL), (s32) &draw);
        func_001DBCF0((s32) &draw);
    }
    func_001D9DD0();
}

typedef struct Record_001CECF0 {
    u8 padding[0x33C];
    u8 kind;
    u8 low;
    u8 high;
    u8 tail[0x11];
} Record_001CECF0;

extern s32 (*D_002BAEB0[])(u16, void *);
extern s8 D_0034F700;
extern s8 D_0034F708;

s32 func_001CECF0(s32 arg0, s32 arg1) {
    u8 *base = D_00317490;
    s32 ret = 0;
    Record_001CECF0 *record = (Record_001CECF0 *)(D_00317490 + arg0 * 0x350);
    void *selected;
    s32 result;

    switch (record->kind) {
    case 0x64:
        ret = func_00203A40(0, arg1, 0xFFFF) & 0xFFFF;
        break;
    case 0x65:
        ret = func_00203A40(1, arg1, 0xFFFF) & 0xFFFF;
        break;
    default:
        if (record->kind < 0x64) {
            selected = record;
            if (func_0027F830(arg0) != 0) {
                selected = base;
            }
            if (func_001FA6F0(-1, -1) == NULL) {
                result = D_002BAEB0[record->kind]((u16)((record->high << 8) | record->low), selected);
                if (result < 0) {
                    if (D_0034F700 != 0) {
                        if (result == -1) {
                            func_0023BB00(1);
                        } else {
                            D_0034F700 = 0;
                            D_0034F708 = 1;
                            func_001A8920();
                        }
                    } else {
                        func_001A8920();
                    }
                } else {
                    ret = result & 0xFFFF;
                }
            }
        }
        break;
    }
    return ret;
}

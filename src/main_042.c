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

INCLUDE_ASM("asm/nonmatchings/main_042", func_001CEA50);

typedef struct Record_001CECF0 {
    u8 padding[0x33C];
    u8 kind;
    u8 low;
    u8 high;
    u8 tail[0x11];
} Record_001CECF0;

void func_0023BB00(s32);
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

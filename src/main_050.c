#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F3790);

typedef struct Entry_001F3870 {
    u64 state : 3;
    u64 source : 3;
    u64 target : 10;
    u64 reserved : 48;
} Entry_001F3870;

void func_001F3870(void) {
    extern Entry_001F3870 D_0031BB50[];
    Entry_001F3870 *entry;
    s32 i;

    entry = D_0031BB50;
    for (i = 0; (s64)i < 32; i++, entry++) {
        if (entry->state == 2 && func_001F5240(entry->source, entry->target) == 0) {
            entry->state = 3;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F3910);

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F3CB0);

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F3E40);

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F3EA0);

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F3F20);

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F40D0);

void func_001F48F0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_001F4900(arg0, arg1, arg2, arg3, arg4, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F4900);

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F4CB0);

typedef struct Entry_001F4E50 {
    u8 pad0[2];
    u16 category : 3;
    u16 kind : 10;
    u16 reserved : 3;
    u8 pad4[0x14];
} Entry_001F4E50;

s32 func_001F4CB0(s32);
extern struct Entry_001F5240 D_0031BC50[];

s32 func_001F4E50(s32 arg0, s32 arg1) {
    Entry_001F4E50 *var_s0;
    s32 var_s1;
    s32 var_s2;

    var_s0 = (Entry_001F4E50 *)D_0031BC50;
    var_s1 = 0;
    var_s2 = 0;
    do {
        if ((arg0 < 0 || var_s0->category == arg0) &&
            (arg1 < 0 || var_s0->kind == arg1)) {
            var_s1 |= func_001F4CB0(var_s2);
        }
        var_s2 += 1;
        var_s0++;
    } while (var_s2 < 0x18);
    return var_s1;
}

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F4F10);

typedef struct Entry_001F4FD0 {
    u16 unk0;
    u16 category : 3;
    u16 group : 10;
    u16 unused : 3;
    u8 unk4[0x14];
} Entry_001F4FD0;

s32 func_001F4F10(s32, s32);
extern struct Entry_001F5240 D_0031BC50[];

s32 func_001F4FD0(s32 arg0, s32 arg1, s32 arg2) {
    Entry_001F4FD0 *var_s0;
    s32 var_s1;
    s32 var_s2;

    var_s0 = (Entry_001F4FD0 *)D_0031BC50;
    var_s1 = 0;
    var_s2 = 0;
    do {
        if (arg0 < 0 || var_s0->category == arg0) {
            if (arg1 < 0 || var_s0->group == arg1) {
                var_s1 |= func_001F4F10(var_s2, arg2);
            }
        }
        var_s2 += 1;
        var_s0++;
    } while (var_s2 < 0x18);
    return var_s1;
}

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F5090);

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F51D0);

typedef struct Entry_001F5240 {
    u8 state : 3;
    u8 : 5;
    u8 unk1;
    u16 kind : 3;
    u16 value : 10;
    u16 : 3;
    u8 padding[0x14];
} Entry_001F5240;

extern Entry_001F5240 D_0031BC50[];

s32 func_001F5240(s32 arg0, s32 arg1) {
    Entry_001F5240 *entry;
    s32 result;
    s32 i;
    s32 state;

    entry = D_0031BC50;
    result = 0;
    i = 0;
    do {
        if (arg0 < 0 || entry->kind == arg0) {
            if (arg1 < 0 || entry->value == arg1) {
                state = entry->state;
                if (state == 1) {
                    result |= 1;
                }
                if (state == 2) {
                    result |= 2;
                }
            }
        }
        i++;
        entry++;
    } while (i < 0x18);
    return result;
}

typedef struct {
    u8 unk00[0x10];
    s32 unk10;
    s32 unk14;
} Entry_001F52D0;

typedef struct {
    u8 unk00[0x100];
    Entry_001F52D0 entries[0x18];
} Data_001F52D0;

extern Data_001F52D0 D_0031BB50;

s32 func_001F52D0(s32 arg0) {
    Entry_001F52D0 *entry = &D_0031BB50.entries[arg0];
    s32 ret;

    if ((arg0 < 0) || (arg0 >= 0x18)) {
        ret = -1;
    } else {
        ret = entry->unk10;
    }
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F5320);

void func_001F5370(s32 arg0) {
    D_0031BE98 = arg0;
}

s32 func_001F5380(u8 arg0) {
    return D_0031BE98;
}

void func_001F5390(s32 arg0) {
    D_0031BE9C = arg0;
}

s32 func_001F53A0(u8 arg0) {
    return D_0031BE9C;
}

void func_001F53B0(s32 arg0, s32 arg1) {
    func_001F53C0(arg0, D_0031BE98, arg1);
}

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F53C0);

s32 func_001F54E0(s32 arg0) {
    extern s32 func_001E1360(s32, s32);
    s32 hi;
    s32 lo;

    hi = arg0 >> 8;
    lo = arg0 & 0xFF;
    if (hi < 0 || hi >= 3 || lo < 0 || lo >= 0xB) {
        return -1;
    }
    arg0 = func_001E1360(hi, lo);
    if (arg0 < 0) {
        return -1;
    }
    return func_001F2B30(arg0);
}

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F5560);

s32 func_001F5620(s32 arg0, u8 arg1, s32 arg2) {
    extern s32 func_001E1360(s32, s32);
    s32 hi = arg0 >> 8;
    s32 lo = arg0 & 0xFF;
    f32 *vec = (f32 *)arg2;

    vec[2] = 0.0f;
    vec[1] = 0.0f;
    vec[0] = 0.0f;
    vec[3] = 1.0f;
    if (hi < 0 || hi >= 3 || lo < 0 || lo >= 0xB) {
        return 0;
    }
    arg0 = func_001E1360(hi, lo);
    if (arg0 < 0) {
        return 0;
    }
    return func_001F2EC0(arg0, arg1, arg2);
}

INCLUDE_ASM("asm/nonmatchings/main_050", func_001F56D0);

void func_001F57B0(s32 arg0) {
    func_001F57C0(D_0031BE9C, arg0);
}

s32 func_001F57C0(s32 arg0, s32 arg1) {
    s32 func_001E1360(s32, s32);
    s32 func_001F2FF0(s32, s32);
    s32 row;
    s32 column;

    row = arg0 >> 8;
    column = arg0 & 0xFF;
    if (row < 0 || row >= 3 || column < 0 || column >= 0xB) {
        return 0;
    }
    arg0 = func_001E1360(row, column);
    if (arg0 < 0) {
        return 0;
    }
    return func_001F2FF0(arg0, arg1);
}

void func_001F5850(void) {
    func_001F5860(D_0031BE98);
}

f32 func_001F5860(s32 arg0) {
    extern s32 func_001E1360(s32, s32);
    s32 hi;
    s32 lo;

    hi = arg0 >> 8;
    lo = arg0 & 0xFF;
    if (hi < 0 || hi >= 3 || lo < 0 || lo >= 0xB) {
        return 0.0f;
    }
    arg0 = func_001E1360(hi, lo);
    if (arg0 < 0) {
        return 0.0f;
    }
    return func_001F0F40(arg0);
}

s32 func_001F58E0(s32 arg0) {
    extern s32 func_001E1360(s32, s32);
    extern s32 func_001F2920(s32);
    s32 hi;
    s32 lo;

    hi = arg0 >> 8;
    lo = arg0 & 0xFF;
    if (hi < 0 || hi >= 3 || lo < 0 || lo >= 0xB) {
        return -1;
    }
    arg0 = func_001E1360(hi, lo);
    if (arg0 < 0) {
        return -1;
    }
    return func_001DE260(func_001DE130(func_001F2920(arg0)));
}

s32 func_001F5970(s32 arg0, s32 arg1) {
    s32 temp_a1;
    s32 temp_v1;

    temp_v1 = arg0 >> 8;
    temp_a1 = arg0 & 0xFF;
    if ((temp_v1 < 0) || (temp_v1 >= 3) ||
        (temp_a1 < 0) || (temp_a1 >= 0xB)) {
        return 0;
    }
    return func_001E3850(temp_v1, temp_a1, arg1);
}

s32 func_001F59D0(s32 arg0, s32 arg1) {
    s32 column;
    s32 row;

    row = arg0 >> 8;
    column = arg0 & 0xFF;
    if (row < 0 || row >= 3 || column < 0 || column >= 11) {
        return 0;
    }
    return func_001E3900(row, column, arg1);
}

s32 func_001F5A30(s32 arg0, s32 arg1) {
    s32 row;
    s32 column;

    row = arg0 >> 8;
    column = arg0 & 0xFF;
    if (row < 0 || row >= 3 || column < 0 || column >= 11) {
        return 0;
    }
    return func_001E3990(row, column, arg1);
}

s32 func_001F5A90(s32 arg0, s32 arg1) {
    s32 column;
    s32 row;

    row = arg0 >> 8;
    column = arg0 & 0xFF;
    if (row < 0 || row >= 3 || column < 0 || column >= 11) {
        return 0;
    }
    return func_001E3A20(row, column, arg1);
}

s32 func_001F5AF0(s32 arg0) {
    s32 temp_v0;

    temp_v0 = func_001DF540(arg0 >> 8, arg0 & 0xFF);
    if (temp_v0 == 0) {
        return 0;
    }
    return (*(s32 *)((u8 *)temp_v0 + 4) != 0) ? 1 : 0;
}

s32 func_001F5B30(s32 arg0) {
    s32 *temp_v0;

    temp_v0 = (s32 *)func_001DF540(arg0 >> 8, arg0 & 0xFF);
    if (temp_v0 == 0) {
        return 0;
    }
    return temp_v0[1];
}

s32 func_001F5B70(s32 arg0, s32 arg1) {
    s32 temp_a1;
    s32 temp_v1;

    temp_v1 = arg0 >> 8;
    temp_a1 = arg0 & 0xFF;
    if (temp_v1 < 0 || temp_v1 >= 3 || temp_a1 < 0 || temp_a1 >= 0xB) {
        return 0;
    }
    return func_001E3AB0(temp_v1, temp_a1, arg1);
}

typedef struct Vec4_001F5BD0 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4_001F5BD0;


s32 func_001F5BD0(s32 arg0, void *arg1) {
    s32 index;
    s32 group;
    Vec4_001F5BD0 *out = arg1;

    group = arg0 >> 8;
    index = arg0 & 0xFF;
    out->z = 0.0f;
    out->y = 0.0f;
    out->x = 0.0f;
    out->w = 1.0f;
    if (group < 0 || group >= 3 || index < 0 || index >= 11) {
        return 0;
    }
    return func_001E3B50(group, index, out);
}

s32 func_001F5C40(s32 arg0, s32 arg1) {
    s32 column;
    s32 row;

    row = arg0 >> 8;
    column = arg0 & 0xFF;
    if ((row < 0) || (row >= 3) || (column < 0) || (column >= 11)) {
        return 0;
    }
    return func_001E3BF0(row, column, arg1);
}

s32 func_001F5CA0(s32 arg0, void *arg1) {
    s32 row = arg0 >> 8;
    s32 column = arg0 & 0xFF;
    s32 *out = arg1;

    out[3] = 0;
    out[2] = 0;
    out[1] = 0;
    out[0] = 0;
    if (row < 0 || row >= 3 || column < 0 || column >= 11) {
        return 0;
    }
    return func_001E3C90(row, column, arg1);
}

s32 func_001F5D10(s32 arg0, s32 arg1) {
    s32 temp_a1;
    s32 temp_v1;

    temp_v1 = arg0 >> 8;
    temp_a1 = arg0 & 0xFF;
    if (temp_v1 < 0 || temp_v1 >= 3 || temp_a1 < 0 || temp_a1 >= 0xB) {
        return 0;
    }
    return func_001E3D30(temp_v1, temp_a1, arg1);
}

typedef struct {
    f32 x, y, z, w;
} Vec4_001F5D70;


s32 func_001F5D70(s32 arg0, void *arg1) {
    Vec4_001F5D70 *out = (Vec4_001F5D70 *)arg1;
    s32 a = arg0 >> 8;
    s32 b = arg0 & 0xFF;

    out->z = 0.0f;
    out->y = 0.0f;
    out->x = 0.0f;
    out->w = 1.0f;
    if (a < 0 || a >= 3 || b < 0 || b >= 0xB) {
        return 0;
    }
    return func_001E3DD0(a, b, out);
}

s32 func_001F5DE0(s32 arg0, s32 arg1) {
    s32 row;
    s32 column;

    row = arg0 >> 8;
    column = arg0 & 0xFF;
    if (row < 0 || row >= 3 || column < 0 || column >= 11) {
        return 0;
    }
    return func_001E3E70(row, column, arg1);
}

s32 func_001F5E40(s32 arg0, u8 *arg1) {
    s32 index;
    s32 bank;

    bank = arg0 >> 8;
    index = arg0 & 0xFF;
    arg1[3] = 0x80;
    arg1[0] = 0x80;
    arg1[1] = 0x80;
    arg1[2] = 0x80;
    if (bank < 0 || bank >= 3 || index < 0 || index >= 11) {
        return 0;
    }
    return func_001E3F10(bank, index, arg1);
}

s32 func_001F5EB0(void) {
    return func_001F5EC0(D_0031BE98);
}

s32 func_001F5EC0(s32 arg0) {
    s32 temp_v0;

    temp_v0 = func_001DF540(arg0 >> 8, arg0 & 0xFF);
    if (temp_v0 != 0) {
        return func_001F1370(*((u8 *)temp_v0 + 0x46));
    }
    return 0;
}

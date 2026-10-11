#include "common.h"

typedef struct {
    u8 pad00[0x40];
    u8 x;
    u8 y;
    u8 alternateX;
    u8 alternateY;
    u8 pad44[0x13];
    s8 : 6;
    s8 alternate : 1;
    s8 : 1;
} Card_001F6F50;

s32 func_001DE2B0(s32, s32, s32, s32, s32, s32, s32);
s32 func_001E5240(s32);

s32 func_001F6F50(s32 arg0) {
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_a3;
    s32 temp_v0;
    Card_001F6F50 *card;
    u8 x;
    u8 y;

    temp_v0 = func_001E5240(1);
    card = (Card_001F6F50 *)func_001DF540(temp_v0 >> 8, temp_v0 & 0xFF);
    temp_a2 = (s32) D_0031BE98 >> 8;
    temp_a3 = D_0031BE98 & 0xFF;
    temp_a0 = (s32) D_0031BE9C >> 8;
    temp_a1 = D_0031BE9C & 0xFF;
    if (card == 0) {
        return -1;
    }
    if ((temp_a0 < 0) || (temp_a0 >= 3) || (temp_a1 < 0) || (temp_a1 >= 0xB) || (temp_a2 < 0) || (temp_a2 >= 3) || (temp_a3 < 0) || (temp_a3 >= 0xB)) {
        return -1;
    }
    x = card->alternate ? card->alternateX : card->x;
    y = card->alternate ? card->alternateY : card->y;
    return func_001DE2B0(temp_a0, temp_a1, temp_a2, temp_a3, x, y, arg0);
}

INCLUDE_ASM("asm/nonmatchings/main_052", func_001F7060);

void func_001F7070(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_001F70A0(D_0031BE9C, arg0, arg1, arg2, arg3, arg4);
}

INCLUDE_ASM("asm/nonmatchings/main_052", func_001F70A0);

void func_001F7170(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_001F71A0(D_0031BE9C, arg0, arg1, arg2, arg3, arg4);
}

INCLUDE_ASM("asm/nonmatchings/main_052", func_001F71A0);

void func_001F7260(s32 arg0) {
    func_001F7350(4, arg0);
    func_001F7350(5, arg0);
    func_001F7350(2, arg0);
    func_001F7350(3, arg0);
    func_001FA770(-1, -1, arg0);
}

INCLUDE_ASM("asm/nonmatchings/main_052", func_001F72C0);

INCLUDE_ASM("asm/nonmatchings/main_052", func_001F7350);

void func_001F73C0(void) {
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s1;
    s32 var_s1_2;
    s32 var_v0;
    s32 var_v0_2;

    var_s0 = 0;
    do {
        var_s1 = var_s0 + 0x14;
        temp_v0 = func_001F3690(var_s1);
        if ((temp_v0 >= 0) && (temp_v0 < 0xFF)) {
            var_v0 = temp_v0 + 1;
            var_v0 = var_v0 < 0xFF ? var_v0 : 0xFF;
            func_001F34A0(var_s1, var_v0 & 0xFF);
        }
        var_s0 += 1;
    } while (var_s0 < 0xA);
    var_s1_2 = 0;
    do {
        var_s0_2 = var_s1_2 + 0x1E;
        temp_v0_2 = func_001F3690(var_s0_2);
        if ((temp_v0_2 >= 0) && (temp_v0_2 < 0xFF)) {
            var_v0_2 = temp_v0_2 + 1;
            var_v0_2 = var_v0_2 < 0xFF ? var_v0_2 : 0xFF;
            func_001F34A0(var_s0_2, var_v0_2 & 0xFF);
        }
        var_s1_2 += 1;
    } while (var_s1_2 < 2);
}

s32 func_001F74B0(void) {
    return 1;
}

s32 func_001F74C0(s32 arg0) {
    s32 temp_v0;

    if (arg0 < 0 || arg0 > 0) {
        return 0;
    }
    temp_v0 = func_00217B40(0x8C0);
    if (temp_v0 == 0) {
        return 0;
    }
    D_0031BEB0[arg0] = temp_v0;
    func_0020B400((void *) temp_v0, 0, 0x230);
    func_001F7550(arg0);
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_052", func_001F7550);

INCLUDE_ASM("asm/nonmatchings/main_052", func_001F7720);

INCLUDE_ASM("asm/nonmatchings/main_052", func_001F7790);

typedef struct Vec4_001F8A30 {
    f32 x, y, z, w;
} Vec4_001F8A30;

typedef struct Object_001F8A30 {
    u8 pad00[0x10];
    Vec4_001F8A30 vector10;
    Vec4_001F8A30 vector20;
    u8 pad30[0x10];
    s32 flags40;
    f32 value44;
    f32 value48;
    f32 value4C;
    f32 value50;
    f32 value54;
    u8 pad58[0x7D0];
    f32 value828;
    f32 value82C;
    u8 pad830[0x48];
    f32 value878;
    f32 value87C;
    u8 pad880[0x24];
    f32 matrix8A4[16];
} Object_001F8A30;

typedef struct Render_001F8A30 {
    f32 matrix[16];
    Vec4_001F8A30 vector40;
    Vec4_001F8A30 vector50;
    u8 pad60[0x20];
    s32 flags80;
} Render_001F8A30;

void func_00206830(void);
void func_0020DF40(f32, f32, f32, f32, f32);
void func_0020DF90(f32, f32);
void func_0020DFD0(f32, f32);
void func_0020E0D0(void *, f32, f32, f32, f32);
void func_0020E260(void *);
s32 func_0020EC60(s32);

s32 func_001F8A30(s32 arg0, s32 arg1) {
    Render_001F8A30 render;
    Object_001F8A30 *object;

    if ((arg1 < 0) || (arg1 > 0)) {
        return arg0;
    }
    object = (Object_001F8A30 *)D_0031BEB0[arg1];
    if (object == 0) {
        return arg0;
    }
    func_0020DF40(object->value44, 640.0f, 448.0f, 320.0f, 224.0f);
    func_0020DF90(object->value48, object->value4C);
    func_0020DFD0(object->value50, object->value54);
    func_00206830();
    func_0020E0D0(object->matrix8A4, object->value828, object->value82C,
                 object->value878, object->value87C);
    render.vector40 = object->vector20;
    render.vector50 = object->vector10;
    render.flags80 = object->flags40;
    func_0020E260(&render);
    return func_0020EC60(arg0);
}

INCLUDE_ASM("asm/nonmatchings/main_052", func_001F8B50);

INCLUDE_ASM("asm/nonmatchings/main_052", func_001F8D30);

INCLUDE_ASM("asm/nonmatchings/main_052", func_001F8F80);

typedef struct {
    u8 pad[0x10];
    f32 direction[4];
    f32 origin[4];
    f32 target[4];
} Direction_001F90E0;

s32 func_001F90E0(s32 arg0) {
    Direction_001F90E0 *entry;

    if ((arg0 < 0) || (arg0 > 0)) {
        return 0;
    }
    entry = (Direction_001F90E0 *)D_0031BEB0[arg0];
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

typedef struct Color_001F9170 {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} Color_001F9170;

typedef struct Palette_001F9170 {
    u8 padding[0x880];
    Color_001F9170 colors[10];
} Palette_001F9170;

s32 func_001F9170(s32 arg0, s32 arg1, s32 arg2) {
    Palette_001F9170 *palette;

    if (arg0 < 0 || arg0 > 0) {
        return 0;
    }
    palette = (Palette_001F9170 *)D_0031BEB0[arg0];
    if (palette == 0) {
        return 0;
    }
    if (arg1 < 0 || arg1 >= 10) {
        return 0;
    }
    if (arg2 != 0) {
        palette->colors[arg1] = *(Color_001F9170 *)arg2;
    } else {
        palette->colors[arg1].r = 0xFF;
        palette->colors[arg1].g = 0xFF;
        palette->colors[arg1].b = 0xFF;
    }
    return 1;
}

typedef struct Bounds_001F9230 {
    f32 min;
    f32 max;
} Bounds_001F9230;

typedef struct State_001F9230 {
    u8 pad[0x7E0];
    Bounds_001F9230 bounds[10];
    u8 pad830[0x7C];
    u16 flags;
} State_001F9230;

s32 func_001F9230(s32 arg0, s32 arg1, s32 arg2) {
    State_001F9230 *state;

    if (arg0 < 0 || arg0 > 0) {
        return 0;
    }
    state = (State_001F9230 *)D_0031BEB0[arg0];
    if (state == 0) {
        return 0;
    }
    if (arg1 < 0 || arg1 >= 10) {
        return 0;
    }
    if (arg2 != 0) {
        if (arg2 != 1) {
            state->bounds[arg1] = *(Bounds_001F9230 *)arg2;
        }
        state->flags |= 1 << arg1;
    } else {
        state->bounds[arg1].min = 2000.0f;
        state->bounds[arg1].max = 4000.0f;
        state->flags &= ~(1 << arg1);
    }
    return 1;
}

typedef struct Pair_001F9310 {
    f32 x;
    f32 y;
} Pair_001F9310;

typedef struct Object_001F9310 {
    u8 pad0[0x830];
    Pair_001F9310 pairs[10];
    u8 pad1[0x2E];
    u16 flags;
} Object_001F9310;

s32 func_001F9310(s32 arg0, s32 arg1, s32 arg2) {
    Object_001F9310 *object;

    if (arg0 < 0 || arg0 > 0) {
        return 0;
    }
    object = (Object_001F9310 *)D_0031BEB0[arg0];
    if (object == 0) {
        return 0;
    }
    if (arg1 < 0 || arg1 >= 10) {
        return 0;
    }
    if (arg2 != 0) {
        if (arg2 != 1) {
            object->pairs[arg1] = *(Pair_001F9310 *)arg2;
        }
        object->flags |= 1 << arg1;
    } else {
        object->pairs[arg1].x = 2000.0f;
        object->pairs[arg1].y = 4000.0f;
        object->flags &= ~(1 << arg1);
    }
    return 1;
}

typedef struct Vec4_001F93F0 {
    f32 x, y, z, w;
} Vec4_001F93F0;

s32 func_001F93F0(s32 arg0, s32 arg1, s32 arg2, void *arg3) {
    u8 *base;
    s32 row;
    s32 offset;
    f32 value;
    Vec4_001F93F0 *dst;

    if (arg0 < 0 || arg0 > 0) {
        return 0;
    }
    base = (u8 *)D_0031BEB0[arg0];
    if (base == NULL) {
        return 0;
    }
    if (arg1 < 0 || arg1 >= 10) {
        return 0;
    }
    if (arg2 < 0 || arg2 >= 3) {
        return 0;
    }
    row = (s32)base + arg1 * 0x90 + 0x60;
    if (arg3 != NULL) {
        dst = (Vec4_001F93F0 *)(row + arg2 * 0x30);
        *dst = *(Vec4_001F93F0 *)arg3;
    } else {
        offset = arg2 * 0x30;
        if (arg2 > 0) {
            value = 0.0f;
        } else {
            value = 0.5f;
        }
        dst = (Vec4_001F93F0 *)(offset + row);
        dst->w = value;
        dst->z = value;
        dst->y = value;
    }
    return 1;
}

typedef struct Vec4_001F9500 {
    f32 x, y, z, w;
} Vec4_001F9500;

typedef struct Entry_001F9500 {
    u8 padding[0x20];
    Vec4_001F9500 value;
} Entry_001F9500;

s32 func_001F9500(s32 arg0, s32 arg1, s32 arg2, void *arg3) {
    u8 *base;
    Entry_001F9500 *entries;

    if (arg0 < 0 || arg0 > 0) {
        return 0;
    }
    base = (u8 *)D_0031BEB0[arg0];
    if (base == NULL) {
        return 0;
    }
    if (arg1 < 0 || arg1 >= 10) {
        return 0;
    }
    if (arg2 < 0 || arg2 >= 3) {
        return 0;
    }
    entries = (Entry_001F9500 *)(base + arg1 * 0x90 + 0x60);
    if (arg3 != NULL) {
        *(Vec4_001F9500 *)arg3 = entries[arg2].value;
    }
    return 1;
}

typedef struct {
    f32 x, y, z, w;
} Vec4_001F95E0;

typedef struct {
    u8 pad[0x10];
    Vec4_001F95E0 rotation;
    Vec4_001F95E0 result;
} Entry_001F95E0;

void func_0020C630(void *, void *);
extern f32 D_00293040[4][4];

s32 func_001F95E0(s32 arg0, s32 arg1, s32 arg2, void *arg3) {
    f32 matrix[4][4];
    Entry_001F95E0 *entry;
    u8 *base;
    Entry_001F95E0 *row;

    if ((arg0 < 0) || (arg0 > 0)) {
        return 0;
    }
    base = (u8 *)D_0031BEB0[arg0];
    if (base == NULL) {
        return 0;
    }
    if ((arg1 < 0) || (arg1 >= 10)) {
        return 0;
    }
    if ((arg2 < 0) || (arg2 >= 3)) {
        return 0;
    }
    row = (Entry_001F95E0 *)(base + arg1 * 0x90 + 0x60);
    if (arg3 != NULL) {
        row[arg2].rotation = *(Vec4_001F95E0 *)arg3;
    }
    entry = &row[arg2];
    func_0020C630(matrix, &entry->rotation);
    func_0020CDD0(&entry->result, matrix, D_00293040);
    return 1;
}

s32 func_001F96F0(s32 arg0, s32 arg1) {
    u8 *data;

    if (arg0 < 0 || arg0 > 0) {
        return 0;
    }
    data = (u8 *)D_0031BEB0[arg0];
    if (data == NULL) {
        return 0;
    }
    if (arg1 < 0 || arg1 >= 10) {
        return 0;
    }
    return (*(u16 *)(data + 0x8A8) & (1 << arg1)) ? 1 : 0;
}

typedef struct {
    __int128 data[9];
} Block_001F9770;

s32 func_001F9770(s32 arg0, s32 arg1, s32 arg2) {
    s32 offset;
    u8 *state;
    u8 *slot;

    if ((arg0 < 0) || (arg0 > 0)) {
        return 0;
    }
    state = (u8 *)D_0031BEB0[arg0];
    if (state == NULL) {
        return 0;
    }
    if ((arg1 < 0) || (arg1 >= 10)) {
        return 0;
    }
    if (arg2 != 0) {
        if (arg2 != 1) {
            offset = arg1 * 0x90;
            *(Block_001F9770 *)(offset + (s32)state + 0x60) = *(Block_001F9770 *)arg2;
            slot = state + offset;
            func_001F95E0(arg0, arg1, 0, slot + 0x70);
            func_001F95E0(arg0, arg1, 1, slot + 0xA0);
            func_001F95E0(arg0, arg1, 2, slot + 0xD0);
        }
        *(u16 *)(state + 0x8A8) |= 1 << arg1;
    } else {
        *(u16 *)(state + 0x8A8) &= ~(1 << arg1);
    }
    return 1;
}

s32 func_001F98C0(s32 arg0, s32 arg1) {
    s32 temp_v1;

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
    return (*(u16 *)((u8 *)temp_v1 + 0x8AA) & (1 << arg1)) ? 1 : 0;
}

INCLUDE_ASM("asm/nonmatchings/main_052", func_001F9940);

f32 func_001F9A20(s32 arg0) {
    s32 temp_v0;

    if ((arg0 < 0) || (arg0 > 0)) {
        return 0.0f;
    }
    temp_v0 = D_0031BEB0[arg0];
    if (temp_v0 == 0) {
        return 0.0f;
    }
    return *(f32 *)((u8 *)temp_v0 + 0x44);
}

INCLUDE_ASM("asm/nonmatchings/main_052", func_001F9A80);

s32 func_001F9AD0(s32 arg0) {
    s32 temp_v0;

    if (arg0 < 0 || arg0 > 0) {
        return 0;
    }
    temp_v0 = D_0031BEB0[arg0];
    if (temp_v0 == 0) {
        return 0;
    }
    return temp_v0 + 0x20;
}

INCLUDE_ASM("asm/nonmatchings/main_052", func_001F9B20);

s32 func_001F9D30(s32 arg0) {
    s32 data;

    if (arg0 < 0 || arg0 >= 1) {
        return 0;
    }
    data = D_0031BEB0[arg0];
    if (data == 0) {
        return 0;
    }
    return data + 0x30;
}

INCLUDE_ASM("asm/nonmatchings/main_052", func_001F9D80);

s32 func_001F9F90(s32 arg0, s32 arg1) {
    void *temp_v0;

    if (arg0 < 0 || arg0 > 0) {
        return 0;
    }
    temp_v0 = (void *)D_0031BEB0[arg0];
    if (temp_v0 == NULL) {
        return 0;
    }
    *(s32 *)((u8 *)temp_v0 + 0x40) = arg1;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_052", func_001F9FE0);

INCLUDE_ASM("asm/nonmatchings/main_052", func_001FA220);

typedef struct Entry_001FA6F0 {
    s8 active : 1;
    s8 : 7;
    s8 unk_01;
    s8 field_02;
    s8 field_03;
    u8 pad_04[0x2C];
} Entry_001FA6F0;

extern Entry_001FA6F0 D_0031BEC0[];

void *func_001FA6F0(s32 arg0, s32 arg1) {
    Entry_001FA6F0 *entry;
    s32 i;

    entry = D_0031BEC0;
    i = 0;
    do {
        if (entry->active && (arg0 < 0 || entry->field_02 == arg0) &&
            (arg1 < 0 || entry->field_03 == arg1)) {
            return entry;
        }
        i++;
        entry++;
    } while (i < 8);
    return NULL;
}

INCLUDE_ASM("asm/nonmatchings/main_052", func_001FA770);

INCLUDE_ASM("asm/nonmatchings/main_052", func_001FA810);

INCLUDE_ASM("asm/nonmatchings/main_052", func_001FA8A0);

s32 func_001FAD10(s32 arg0) {
    s32 temp_v0;

    if (arg0 < 0 || arg0 > 0) {
        return 0;
    }
    temp_v0 = D_0031BEB0[arg0];
    if (temp_v0 == 0) {
        return 0;
    }
    return temp_v0 + 0x10;
}

INCLUDE_ASM("asm/nonmatchings/main_052", func_001FAD60);

f32 *func_001FAF60(s32 arg0) {
    f32 *var_v0;

    if (arg0 < 0 || arg0 > 0) {
        return NULL;
    }
    var_v0 = (f32 *)D_0031BEB0[arg0];
    if (var_v0 == NULL) {
        var_v0 = NULL;
    }
    return var_v0;
}

INCLUDE_ASM("asm/nonmatchings/main_052", func_001FAFB0);

INCLUDE_ASM("asm/nonmatchings/main_052", func_001FB0B0);

INCLUDE_ASM("asm/nonmatchings/main_052", func_001FB1D0);

INCLUDE_ASM("asm/nonmatchings/main_052", func_001FB360);

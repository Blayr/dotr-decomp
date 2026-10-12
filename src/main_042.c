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

typedef struct Flags_001CDEB0 {
    s8 unused : 3;
    s8 position : 1;
    s8 rotation : 1;
    s8 rotation2 : 1;
    s8 scale : 1;
    s8 color : 1;
} Flags_001CDEB0;

typedef struct Output_001CDEB0 {
    f32 position[4];
    s32 rotation[4];
    s32 rotation2[4];
    f32 scale[4];
    u8 color[4];
} Output_001CDEB0;

typedef struct Blend_001CDEB0 {
    Output_001CDEB0 *output;
    u8 padding04[12];
    f32 position0[4];
    f32 position1[4];
    s32 rotation0[4];
    s32 rotation1[4];
    s32 rotation20[4];
    s32 rotation21[4];
    f32 scale0[4];
    f32 scale1[4];
    u8 color0[4];
    u8 color1[4];
    u16 duration;
    u16 progress;
    u8 padding9C[3];
    Flags_001CDEB0 flags;
} Blend_001CDEB0;

s32 func_001CDEB0(void *arg0) {
    extern s32 func_001A22C0(f32);
    Output_001CDEB0 *output;
    f32 blend;
    f32 inverse;
    Blend_001CDEB0 *src = arg0;

    output = src->output;
    if (output != NULL) {
        blend = (f32)src->progress / (f32)src->duration;
        inverse = 1.0f - blend;
        if (src->flags.position) {
            output->position[0] = src->position0[0] * inverse + src->position1[0] * blend;
            output->position[1] = src->position0[1] * inverse + src->position1[1] * blend;
            output->position[2] = src->position0[2] * inverse + src->position1[2] * blend;
            output->position[3] = src->position0[3] * inverse + src->position1[3] * blend;
        }
        if (src->flags.rotation) {
            output->rotation[0] = func_001A22C0((f32)src->rotation0[0] * inverse + (f32)src->rotation1[0] * blend) % 0x10000;
            output->rotation[1] = func_001A22C0((f32)src->rotation0[1] * inverse + (f32)src->rotation1[1] * blend) % 0x10000;
            output->rotation[2] = func_001A22C0((f32)src->rotation0[2] * inverse + (f32)src->rotation1[2] * blend) % 0x10000;
            output->rotation[3] = func_001A22C0((f32)src->rotation0[3] * inverse + (f32)src->rotation1[3] * blend) % 0x10000;
        }
        if (src->flags.rotation2) {
            output->rotation2[0] = func_001A22C0((f32)src->rotation20[0] * inverse + (f32)src->rotation21[0] * blend) % 0x10000;
            output->rotation2[1] = func_001A22C0((f32)src->rotation20[1] * inverse + (f32)src->rotation21[1] * blend) % 0x10000;
            output->rotation2[2] = func_001A22C0((f32)src->rotation20[2] * inverse + (f32)src->rotation21[2] * blend) % 0x10000;
            output->rotation2[3] = func_001A22C0((f32)src->rotation20[3] * inverse + (f32)src->rotation21[3] * blend) % 0x10000;
        }
        if (src->flags.scale) {
            output->scale[0] = src->scale0[0] * inverse + src->scale1[0] * blend;
            output->scale[1] = src->scale0[1] * inverse + src->scale1[1] * blend;
            output->scale[2] = src->scale0[2] * inverse + src->scale1[2] * blend;
            output->scale[3] = src->scale0[3] * inverse + src->scale1[3] * blend;
        }
        if (src->flags.color) {
            output->color[2] = func_001A22C0((f32)src->color0[2] * inverse + (f32)src->color1[2] * blend);
            output->color[1] = func_001A22C0((f32)src->color0[1] * inverse + (f32)src->color1[1] * blend);
            output->color[0] = func_001A22C0((f32)src->color0[0] * inverse + (f32)src->color1[0] * blend);
            output->color[3] = func_001A22C0((f32)src->color0[3] * inverse + (f32)src->color1[3] * blend);
        }
        return 1;
    }
    return 0;
}

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

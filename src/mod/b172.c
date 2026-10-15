#include "common.h"

typedef struct {
    f32 x, y, z, w;
} Vec_b005_01E00080;

typedef struct {
    u8 count;
    u8 pad01;
    u8 length;
    u8 mask;
    u8 mode;
    u8 pad05[0xB];
    u8 light[0x10];
    Vec_b005_01E00080 pos;
    u8 pad30[8];
    f32 value;
    u8 pad3C[4];
    Vec_b005_01E00080 vel;
    f32 base;
} Fx_b005_01E00080;

static void func_01E00080_b172(Fx_b005_01E00080 *o) {
    u8 phase;
    u8 mask;
    u8 rest;
    u8 count;
    f32 step;
    u8 length;
    s32 on;

    if (func_00101AF0(o) == 0) {
        return;
    }
    o->pos.x += o->vel.x;
    o->pos.y += o->vel.y;
    o->pos.z += o->vel.z;
    func_00101BA0(o, (s32)&o->pos);
    count = o->count;
    mask = o->mask;
    length = o->length;
    phase = count & mask;
    rest = length - count;
    if (mask == 0xFF) {
        step = o->base / length;
    } else {
        step = o->base / (mask + 1);
    }
    on = 1;
    switch (o->mode & 0xF) {
    case 1:
        o->value = step * phase;
        break;
    case 2:
        if (mask == 0xFF) {
            if (rest < length >> 1) {
                o->value = 2.0f * step * rest;
            } else {
                o->value = 2.0f * step * count;
            }
        } else {
            if (phase < mask >> 1) {
                o->value = 2.0f * step * (mask - phase);
            } else {
                o->value = 2.0f * step * phase;
            }
        }
        break;
    case 4:
        o->value = o->base;
        if (o->count & 1) {
            o->value *= 0.5f;
        }
        break;
    case 8:
        if (count & 1) {
            on = 0;
        }
    default:
        o->value = o->base;
        break;
    }
    if (on == 0 || o->count == 0) {
        func_001F6C10(0);
    } else {
        func_001F6C10((s32)o->light);
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b172", func_01E003A0_b172);

INCLUDE_ASM("asm/nonmatchings/mod/b172", func_01E012E0_b172);

INCLUDE_ASM("asm/nonmatchings/mod/b172", func_01E020F0_b172);

INCLUDE_ASM("asm/nonmatchings/mod/b172", func_01E02940_b172);

INCLUDE_ASM("asm/nonmatchings/mod/b172", func_01E02F30_b172);

INCLUDE_ASM("asm/nonmatchings/mod/b172", func_01E03670_b172);

INCLUDE_ASM("asm/nonmatchings/mod/b172", func_01E04010_b172);

INCLUDE_ASM("asm/nonmatchings/mod/b172", func_01E043A0_b172);

INCLUDE_ASM("asm/nonmatchings/mod/b172", func_01E04DF0_b172);

INCLUDE_ASM("asm/nonmatchings/mod/b172", func_01E05700_b172);

/* shape b172:01E061E0, 128 insns: b062:01E05A10's 30-piece ring, with the pieces past 0x8000 (0x8508) and the centre
   after the scales (0x8EE0); pieces turn on the x/z plane (y = 0) */

typedef struct {
    u8 n;
    u8 pad1;
    u8 step;
    u8 pad3;
    u8 flags;
    u8 pad5[0x33];
    f32 x, y, z;
} Piece_b172_01E061E0;

typedef struct {
    u8 m[0xC];
} Mtx_b172_01E061E0;

typedef struct {
    u8 pad0[0x8508];
    Piece_b172_01E061E0 pieces[30];
    Mtx_b172_01E061E0 mats[30];
    f32 scale[30];
    f32 cx, cy, cz;
} Scene_b172_01E061E0;

static void func_01E061E0_b172(Scene_b172_01E061E0 *s) {
    extern void func_00101A00(void *, void *);
    extern f32 func_001A6898(f32);
    extern f32 func_001A6A88(f32);
    extern void func_0020CDD0(void *, void *, void *);
    Vec4f v;
    Vec4f out;
    f32 mtx[16];
    f32 r;
    f32 a;
    s32 d;
    s32 i;

    for (i = 0; i < 0x1E; i++) {
        if (s->pieces[i].n != 0) {
            if (s->pieces[i].n < 4) {
                s->pieces[i].flags |= 8;
            }
            func_00101A00(&s->mats[i], mtx);
            d = s->pieces[i].step - s->pieces[i].n;
            r = (f32)(s->pieces[i].n - 4) * s->scale[i];
            if (r < 0.0f) {
                r = 0.0f;
            }
            a = (3.1415927f * (45.0f * i + 16.0f * d)) / 180.0f;
            v.x = r * func_001A6898(a);
            v.y = 0.0f;
            v.z = r * func_001A6A88(a);
            func_0020CDD0(&out, mtx, &v);
            s->pieces[i].x = s->cx + out.x;
            s->pieces[i].y = s->cy + out.y;
            s->pieces[i].z = s->cz + out.z;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b172", func_01E063E0_b172);

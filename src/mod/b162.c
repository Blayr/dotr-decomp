#include "common.h"

/* OVL_CFLAGS: -O2,p -sdatathreshold 0 -relax_pointers */

/* shape b010:01E00080, 226 insns, 89 copies: move an emitter (pos += vel) and set its level from the blend mode */

typedef struct Obj_b010_01E00080 {
    u8 b0;
    u8 b1;
    u8 b2;
    u8 b3;
    u8 b4;
    u8 pad5[0xB];
    u8 f10[0x10];
    Vec4f pos;
    u8 pad30[8];
    f32 level;
    u8 pad3C[4];
    Vec4f vel;
    f32 base;
} Obj_b010_01E00080;

#pragma optimization_level 2

static void func_01E00080_b162(Obj_b010_01E00080 *o) {
    extern s32 func_00101AF0();
    extern void func_00101BA0();
    extern void func_001F6C10();
    u8 d;
    u8 e;
    u8 a;
    s32 on;
    u8 n;
    f32 k;
    u8 m;

    if (func_00101AF0(o) == 0) {
        return;
    }
    o->pos.x += o->vel.x;
    o->pos.y += o->vel.y;
    o->pos.z += o->vel.z;
    func_00101BA0(o, &o->pos);
    a = o->b0;
    m = o->b3;
    d = a & m;
    n = o->b2;
    e = n - a;
    if (m == 0xFF) {
        k = o->base / n;
    } else {
        k = o->base / (m + 1);
    }
    on = 1;
    switch (o->b4 & 0xF) {
    case 1:
        o->level = k * d;
        break;
    case 2:
        if (m == 0xFF) {
            if (e < n >> 1) {
                k = 2.0f * k;
                o->level = k * e;
            } else {
                k = 2.0f * k;
                o->level = k * a;
            }
        } else {
            if (d < m >> 1) {
                k = 2.0f * k;
                o->level = k * (m - d);
            } else {
                k = 2.0f * k;
                o->level = k * d;
            }
        }
        break;
    case 4:
        o->level = o->base;
        if (o->b0 & 1) {
            o->level *= 0.5f;
        }
        break;
    case 8:
        if (a & 1) {
            on = 0;
        }
    default:
        o->level = o->base;
        break;
    }
    if (on == 0 || o->b0 == 0) {
        func_001F6C10(0);
    } else {
        func_001F6C10(o->f10);
    }
}
#pragma optimization_level reset

INCLUDE_ASM("asm/nonmatchings/mod/b162", func_01E00410_b162);

INCLUDE_ASM("asm/nonmatchings/mod/b162", func_01E011C0_b162);

INCLUDE_ASM("asm/nonmatchings/mod/b162", func_01E01BD0_b162);

INCLUDE_ASM("asm/nonmatchings/mod/b162", func_01E02750_b162);

INCLUDE_ASM("asm/nonmatchings/mod/b162", func_01E02CF0_b162);

/* OVL_CFLAGS: -O2,p */

/* shape b162:01E03F70, 94 insns: looks up the sound ids for a set: set 0 takes five (0x28 first, then 0x27, 0x30, 0x2F, 1),
   set 1 takes eight (0x35 first, then 0x34, 0x3A, 0x39, 0x3F, 0x3E, 0x44, 0x43) */

typedef struct {
    u8 pad0[4];
    s32 bank;
    u8 pad8[4];
    s32 id[8];
} Obj_b162_01E03F70;

#pragma optimization_level 2

static void func_01E03F70_b162(Obj_b162_01E03F70 *o, s32 set) {
    extern s32 func_001F5560(s32, s32, s32);

    switch (set) {
    case 0:
        o->id[0] = func_001F5560(o->bank, 0x28, 1);
        o->id[1] = func_001F5560(o->bank, 0x27, 0);
        o->id[2] = func_001F5560(o->bank, 0x30, 0);
        o->id[3] = func_001F5560(o->bank, 0x2F, 0);
        o->id[4] = func_001F5560(o->bank, 1, 0);
        break;
    case 1:
        o->id[0] = func_001F5560(o->bank, 0x35, 1);
        o->id[1] = func_001F5560(o->bank, 0x34, 0);
        o->id[2] = func_001F5560(o->bank, 0x3A, 0);
        o->id[3] = func_001F5560(o->bank, 0x39, 0);
        o->id[4] = func_001F5560(o->bank, 0x3F, 0);
        o->id[5] = func_001F5560(o->bank, 0x3E, 0);
        o->id[6] = func_001F5560(o->bank, 0x44, 0);
        o->id[7] = func_001F5560(o->bank, 0x43, 0);
        break;
    }
}
#pragma optimization_level reset

INCLUDE_ASM("asm/nonmatchings/mod/b162", func_01E040F0_b162);

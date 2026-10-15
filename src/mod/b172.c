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

/* shape b172:01E04010, 225 insns: b131:01E03B50's trail emitters (0x5C bytes each) without the drift: follow a bone,
   then spawn particles (0x44 bytes) pointing up along the path from the last three positions (a spline of
   e->segs points, or just the last segment when e->segs is 0 or 1). */

typedef struct {
    u8 r, g, b, a;
} Col_b172_01E04010;

typedef struct {
    u8 pad0[4];
    u8 flags;
    u8 f5;
    u8 pad6[2];
    u8 f8;
    u8 f9;
    u8 fA;
    u8 fB;
    u8 fC;
    u8 fD;
    u8 padE[2];
    s32 f10;
    f32 len;
    f32 f18;
    f32 f1C;
    f32 f20;
    Col_b172_01E04010 col;
    u8 f28[0x10];
    f32 x, y, z;
} Part_b172_01E04010;

typedef struct {
    u8 age;
    u8 pad1;
    u8 life;
    u8 pad3;
    u8 flags;
    u8 pad5[3];
    Part_b172_01E04010 *pool;
    s32 fC;
    u8 kind;
    u8 sub;
    u8 f12;
    u8 f13;
    u8 f14;
    u8 f15;
    u8 f16;
    u8 segs;
    f32 len;
    f32 f1C;
    f32 f20;
    f32 f24;
    Col_b172_01E04010 col;
    Vec4f pos;
    Vec4f prev;
    Vec4f prev2;
} Emit_b172_01E04010;

typedef struct {
    s32 n;
    f32 x[8];
    f32 y[8];
    f32 z[8];
    Vec4f pts[28];
    u8 pad[0xC];
} Spline_b172_01E04010;

static s32 func_01E04010_b172(Emit_b172_01E04010 *arg0, s32 arg1, s32 n) {
    extern void func_00101BA0();
    extern s32 func_00101C30();
    extern void func_00101AD0();
    extern void func_00101940();
    Emit_b172_01E04010 *e = arg0;
    Spline_b172_01E04010 spl;
    f32 dir[4];
    s32 i;
    s32 j;
    s32 k;
    s32 idx;

    for (i = 0; i < n; i++) {
        if (i != 0) {
            e++;
        }
        if (func_00101AF0(e) != 0 && e->age != e->life - 1) {
            func_00101BA0(e, &e->pos);
            if (e->segs <= 1) {
                spl.pts[0] = e->pos;
                spl.pts[1] = e->prev;
                k = 1;
            } else {
                spl.n = 3;
                spl.x[0] = e->pos.x;
                spl.y[0] = e->pos.y;
                spl.z[0] = e->pos.z;
                spl.x[1] = e->prev.x;
                spl.y[1] = e->prev.y;
                spl.z[1] = e->prev.z;
                spl.x[2] = e->prev2.x;
                spl.y[2] = e->prev2.y;
                spl.z[2] = e->prev2.z;
                func_00102550(&spl);
                k = e->segs;
            }
            for (j = 0; j < k; j++) {
                idx = func_00101C30(e->pool, 0x44, e->kind);
                if (idx >= 0) {
                    func_00101AD0(&e->pool[idx], e->sub, 0, 0xFF);
                    dir[0] = dir[2] = 0.0f;
                    dir[1] = 1.0f;
                    if (e->len) {
                        e->pool[idx].len = e->len;
                    }
                    e->pool[idx].f18 = e->f1C;
                    e->pool[idx].flags = e->flags;
                    e->pool[idx].f5 = 0;
                    e->pool[idx].f8 = e->f12;
                    e->pool[idx].f1C = e->f20;
                    e->pool[idx].f20 = e->f24;
                    e->pool[idx].f9 = func_0019A5C8() >> 4;
                    e->pool[idx].fA = e->f13;
                    e->pool[idx].fB = e->f14;
                    e->pool[idx].fC = e->f15;
                    e->pool[idx].fD = e->f16;
                    e->pool[idx].f10 = e->fC;
                    e->pool[idx].col = e->col;
                    e->pool[idx].x = spl.pts[j].x;
                    e->pool[idx].y = spl.pts[j].y;
                    e->pool[idx].z = spl.pts[j].z;
                    func_00101940(dir, e->pool[idx].f28);
                }
            }
            e->prev2 = e->prev;
            e->prev = e->pos;
        }
    }
    return 1;
}

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

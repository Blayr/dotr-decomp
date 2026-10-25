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

static void func_01E00080_b176(Obj_b010_01E00080 *o) {
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

INCLUDE_ASM("asm/nonmatchings/mod/b176", func_01E00410_b176);

/* OVL_CFLAGS: -O2,p -sdatathreshold 0 -relax_pointers */

/* shape b010:01E00DC0, 200 insns, 34 copies: spawns the emitter's particle ring: one particle per slot, evenly spaced from a
   random start angle, placed on the radius and moving outwards; the slot keeps the particle index (-1 if none) */

typedef struct {
    u8 pad0[3];
    s8 flag;
    f32 x, y, z;
    f32 vx, vy, vz;
    f32 ax;
    s32 ay;
    f32 az;
} Part_b010_01E00DC0;

typedef struct {
    u8 pad0[8];
    u8 *parts;
    s16 idx[8];
    u8 type;
    u8 count;
} Sys_b010_01E00DC0;

typedef struct {
    Sys_b010_01E00DC0 *sys;
    u8 kind;
    u8 mask;
    u8 pad6[2];
    f32 speed;
    f32 vy;
    f32 radius;
    f32 cx, cy, cz;
} Emit_b010_01E00DC0;

#pragma optimization_level 2

static void func_01E00DC0_b176(Emit_b010_01E00DC0 *e) {
    extern void func_00101B40(void *, u8, u8);
    Sys_b010_01E00DC0 *sys;
    f32 ang;
    f32 step;
    Part_b010_01E00DC0 *p;
    s32 i;
    s32 k;
    f32 r;
    f32 s;
    f32 c;

    sys = e->sys;
    ang = 180.0f + (f32)((func_0019A5C8() >> 4) % 36000 - 18000) / 100.0f;
    step = 360.0f / sys->count;
    for (i = 0; i < sys->count; i++) {
        k = func_00101C30(sys->parts, 0x28, sys->type);
        if (k >= 0) {
            sys->idx[i] = k;
            p = (Part_b010_01E00DC0 *)(sys->parts + k * 0x28);
            func_00101B40(p, e->kind, e->mask & (func_0019A5C8() >> 4));
            p->flag = ((func_0019A5C8() >> 4) & 3) * 16;
            ang += step;
            if (ang > 360.0f) {
                ang -= 360.0f;
            }
            r = 3.1415927f * ang / 180.0f;
            s = func_001A6A88(r);
            c = func_001A6898(r);
            p->x = e->cx + e->radius * c;
            p->z = e->cz + e->radius * s;
            p->y = e->cy;
            p->vx = e->speed * c;
            p->vz = e->speed * s;
            p->vy = e->vy;
            p->ax = -(p->vx / e->kind);
            p->az = -(p->vz / e->kind);
            p->ay = 0;
        } else {
            sys->idx[i] = -1;
        }
    }
}
#pragma optimization_level reset

/* OVL_CFLAGS: -O2,p -sdatathreshold 0 -relax_pointers */

/* shape b010:01E010E0, 304 insns, 34 copies: on a given frame, starts the effect emitters listed for it:
   each of the 8 frame tables starts a 4-particle burst at its bone, and the frame window lo..hi starts a
   2-particle emitter with randomly spread particles. */

typedef struct {
    u8 pad0[4];
    u8 type;
    u8 pad5[3];
    void *pool;
    s16 idx[8];
    u8 pool_kind;
    u8 count;
    u8 one;
    u8 kind;
    u8 four;
    u8 pad21;
    u8 r, g, b, a;
    u8 pad26[2];
    f32 x;
    f32 y;
    f32 speed;
    f32 depth;
} Emit_b010_01E010E0;

typedef struct {
    u8 pad0[3];
    u8 frame;
    f32 x, y, z;
    s32 w[6];
} Part_b010_01E010E0;

typedef struct {
    Emit_b010_01E010E0 *emits;
    Part_b010_01E010E0 *parts;
    s16 *frames[8];
    u8 bone[8];
    u8 emit_kind;
    u8 part_kind;
    u8 kind;
    u8 bone2;
    s16 lo;
    s16 hi;
    f32 x0;
    f32 x1;
    f32 y;
} Obj_b010_01E010E0;

typedef struct {
    Emit_b010_01E010E0 *e;
    u8 n;
    u8 m;
    f32 a, b, c;
    Vec4f pos;
} Burst_b010_01E010E0;

extern void b176_01E00DC0(Burst_b010_01E010E0 *);

#pragma optimization_level 2

static s32 func_01E010E0_b176(Obj_b010_01E010E0 *obj, u16 frame) {
    extern s32 func_001F53A0();
    extern s32 func_00101C30();
    extern s32 func_001F5620();
    extern void func_00101AD0();
    Vec4f pos;
    Burst_b010_01E010E0 burst;
    Emit_b010_01E010E0 *e;
    Part_b010_01E010E0 *pt;
    s32 i;
    s16 *list;
    s32 k;
    s32 j;

    for (i = 0; i < 8; i++) {
        list = obj->frames[i];
        if (list != NULL) {
            for (; *list > 0; list++) {
                if (*list == frame) {
                    if (func_001F5620(func_001F53A0(), obj->bone[i], &pos) == 0) {
                        break;
                    }
                    k = func_00101C30(obj->emits, 0x38, obj->emit_kind);
                    if (k < 0) {
                        return 0;
                    }
                    e = &obj->emits[k];
                    func_00101AD0(e, 1, 0, 0xFF);
                    e->type = 4;
                    e->pool = obj->parts;
                    e->pool_kind = obj->part_kind;
                    e->count = 4;
                    e->one = 1;
                    e->kind = obj->kind;
                    e->four = 4;
                    e->r = 0x90;
                    e->g = 0x90;
                    e->b = 0x90;
                    e->a = 0x30;
                    e->x = obj->x0;
                    e->y = obj->y;
                    e->speed = -0.015f;
                    e->depth = pos.y;
                    burst.e = e;
                    burst.n = 0x20;
                    burst.m = 3;
                    burst.a = 0.25f;
                    burst.b = 0.3f;
                    burst.c = 0.15f;
                    burst.pos = pos;
                    b176_01E00DC0(&burst);
                }
            }
        }
    }
    if (obj->lo != 0) {
        if ((s16)obj->lo <= frame && obj->hi >= frame) {
            if (func_001F5620(func_001F53A0(), obj->bone2, &pos) == 0) {
                return 0;
            }
            k = func_00101C30(obj->emits, 0x38, obj->emit_kind);
            if (k < 0) {
                return 0;
            }
            e = &obj->emits[k];
            func_00101AD0(e, 1, 0, 0xFF);
            e->type = 4;
            e->pool = obj->parts;
            e->pool_kind = obj->part_kind;
            e->count = 2;
            e->one = 1;
            e->kind = obj->kind;
            e->four = 4;
            e->r = 0x90;
            e->g = 0x90;
            e->b = 0x90;
            e->a = 0x30;
            e->x = obj->x1;
            e->y = obj->y;
            e->speed = -0.007f;
            e->depth = 0.0f;
            for (j = 0; j < e->count; j++) {
                k = func_00101C30(obj->parts, 0x28, obj->part_kind);
                if (k >= 0) {
                    e->idx[j] = k;
                    pt = &obj->parts[k];
                    func_00101B40(pt, 0x20, 0);
                    pt->frame = ((func_0019A5C8() >> 4) & 3) * 0x10;
                    pt->x = pos.x + (f32)((func_0019A5C8() >> 4) % 500 - 250) / 100.0f;
                    pt->z = pos.z + (f32)((func_0019A5C8() >> 4) % 500 - 250) / 100.0f;
                    pt->y = pos.y + (f32)((func_0019A5C8() >> 4) % 500 - 250) / 100.0f;
                    pt->w[5] = 0;
                    pt->w[4] = 0;
                    pt->w[3] = 0;
                    pt->w[2] = 0;
                    pt->w[1] = 0;
                    pt->w[0] = 0;
                } else {
                    e->idx[j] = -1;
                }
            }
        }
    }
    return 1;
}
#pragma optimization_level reset

INCLUDE_ASM("asm/nonmatchings/mod/b176", func_01E015A0_b176);

INCLUDE_ASM("asm/nonmatchings/mod/b176", func_01E02820_b176);

INCLUDE_ASM("asm/nonmatchings/mod/b176", func_01E03160_b176);

/* OVL_CFLAGS: -O2,p -sdatathreshold 0 -relax_pointers */
/* OVL_WARM: compile warm (its (u32) casts are jal fptoui, func_001A23B0) */

/* shape b133:01E01440, 325 insns: n burst emitters (0x60 bytes each): move and spin, then draw count radial lines
   from a random byte table: angle steps by 20 + table[idx], radius and height from the next two table bytes,
   length 1 + (mask & table), pushed out by the emitter's age; each line drawn twice */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b133_01E01440;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Xyz_b133_01E01440 xyz;
} Vtx_b133_01E01440;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Vtx_b133_01E01440 v[2];
    u8 tail[8];
} Pk_b133_01E01440;

typedef struct {
    u8 b, g, r, a;
} Col_b133_01E01440;

typedef struct {
    f32 x, y, z;
    u8 padC[4];
} V3_b133_01E01440;

typedef struct {
    u8 life;
    u8 pad1;
    u8 max;
    u8 pad3[5];
    u8 count;
    u8 idx;
    u8 mask;
    u8 padB;
    u8 *tab;
    f32 hscale;
    f32 rscale;
    Col_b133_01E01440 c1;
    Col_b133_01E01440 c0;
    V3_b133_01E01440 pos;
    V3_b133_01E01440 vel;
    s32 rot[4];
    s32 drot[4];
} Emit_b133_01E01440;

#pragma optimization_level 2

static s32 func_01E039D0_b176(void *arg0, s32 ot, s32 n) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_00101BA0(void *, void *);
    extern void func_0020BC00(void *, void *);
    f32 m2[16];
    f32 m[16];
    f32 p[8];
    Pk_b133_01E01440 pk __attribute__((aligned(8)));
    f32 dep;
    Emit_b133_01E01440 *e;
    s32 i;
    s32 j;
    s32 len;
    s32 k;
    f32 ang;
    f32 step;
    f32 c;
    f32 r;
    f32 a;
    f32 h;
    f32 s;
    f32 fl;
    f32 w;

    e = arg0;
    for (i = 0; i < n; i++) {
        if (i != 0) {
            e++;
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        e->pos.x += e->vel.x;
        e->pos.y += e->vel.y;
        e->pos.z += e->vel.z;
        e->rot[0] += e->drot[0];
        e->rot[1] += e->drot[1];
        e->rot[2] += e->drot[2];
        func_00101BA0(e, &e->pos);
        func_0020EB40(m);
        func_0020C940(m2, NULL, e->rot, &e->pos);
        func_0020BC00(m, m2);
        j = e->idx;
        step = 20.0f + e->tab[j];
        j = (u8)(j + 1);
        ang = 0.0f;
        len = e->max - e->life;
        ((Pk_b133_01E01440 *)(s32)&pk)->flags = 0x11;
        ((Pk_b133_01E01440 *)(s32)&pk)->size = 4;
        ((Pk_b133_01E01440 *)(s32)&pk)->regs = 0x4141;
        ((Pk_b133_01E01440 *)(s32)&pk)->pad4 = 0;
        pk.v[0].r = e->c0.r;
        pk.v[0].g = e->c0.g;
        pk.v[0].b = e->c0.b;
        pk.v[1].r = e->c1.r;
        pk.v[1].g = e->c1.g;
        pk.v[1].b = e->c1.b;
        pk.v[0].q = pk.v[1].q = 1.0f;
        if (e->life < 8) {
            pk.v[0].a = pk.v[1].a = (e->c1.a >> 3) * e->life;
        } else {
            pk.v[0].a = pk.v[1].a = e->c1.a;
        }
        func_002086D0(&pk, 0x48);
        ((Pk_b133_01E01440 *)(s32)&pk)->flags |= 0x400;
        for (k = 0; k < e->count; k++) {
            ang += step;
            if (!(ang <= 360.0f)) {
                ang -= 360.0f;
            }
            r = e->rscale * e->tab[(u8)j] / 255.0f;
            a = 3.1415927f * ang / 180.0f;
            c = r * func_001A6898(a);
            s = r * func_001A6A88(a);
            h = e->hscale * e->tab[(u8)(j + 1)] / 255.0f;
            fl = len;
            p[0] = c * fl;
            p[1] = h * fl;
            p[2] = s * fl;
            w = 1.0f + (e->mask & e->tab[(u8)(j + 2)]);
            j = (u8)(j + 3);
            p[4] = p[0] + c * w;
            p[5] = p[1] + h * w;
            p[6] = p[2] + s * w;
            if (func_00205440(p, m, &pk.v[0].xyz, &dep) != 0 && func_00205440(&p[4], m, &pk.v[1].xyz, &dep) != 0) {
                func_002075F0((s32)&pk, ot, (u32)dep);
                func_002075F0((s32)&pk, ot, (u32)dep);
            }
        }
    }
    return 1;
}
#pragma optimization_level reset

INCLUDE_ASM("asm/nonmatchings/mod/b176", func_01E03EF0_b176);

/* shape b176:01E049A0, 259 insns (b176_setBst): sets up the four blade sparks of blade `n` (1-based) for `mode`:
   0 keeps only their low nibble, 1 starts them (kind 0x9F, joints from the scene's joint table: odd blades 2/3,
   even blades 2/1; size 10/18, red 0x80/0x10/0x10), 2 resizes to 18/10 with alpha 0x80, 3 to 80/15 with alpha 0xC0;
   mode 3 on blades 1 and 3 also starts the blade's trail (0x48 bytes, kind 0x18) at the first spark's joint A,
   aimed at its joint B */

typedef struct {
    u8 b0;
    u8 pad1[3];
    u8 b4;
    u8 pad5[2];
    u8 b7;
    u8 b8;
    u8 b9;
    u8 bA;
    u8 ja;
    u8 jb;
    u8 padD[3];
    f32 f10;
    f32 size;
    u8 pad18[4];
    f32 f1C;
    f32 f20;
    u8 col[4];
    u8 col2[4];
    u8 pad2C[0x20];
} Spark_b176_01E049A0;

typedef struct {
    u8 b0[4];
    u8 b4;
    u8 b5;
    u8 pad6;
    u8 b7;
    u8 b8;
    u8 b9;
    u8 bA;
    u8 padB;
    f32 f0C;
    f32 f10;
    f32 f14;
    f32 f18;
    f32 f1C;
    u8 col[4];
    u8 col2[4];
    Vec4f pos;
    f32 dir[4];
    u8 pad48[0];
} Trail_b176_01E049A0;

typedef struct {
    u8 pad0[4];
    s32 model;
    u8 jt[(0x12F4 - 8) / 4][4];
    Trail_b176_01E049A0 tr[3];
    Spark_b176_01E049A0 sp[16];
} Scene_b176_01E049A0;

#pragma optimization_level 2

static void func_01E049A0_b176(Scene_b176_01E049A0 *g, s32 n, s32 mode) {
    extern void func_00101AD0(void *, s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern void func_00101940(void *, void *);
    Vec4f p;
    f32 d[4];
    s32 i;
    s32 k;

    for (i = 0; i < 4; i++) {
        k = i + (n - 1) * 4;
        switch (mode) {
        case 0:
            g->sp[k].b0 &= 0xF;
            break;
        case 1:
            func_00101AD0(&g->sp[k], 0x9F, 0, 0xF);
            g->sp[k].b0 = 0x9F - i * 4;
            g->sp[k].b4 = 2;
            g->sp[k].b7 = 3;
            g->sp[k].b8 = 1;
            g->sp[k].bA = 0x20;
            g->sp[k].b9 = 7;
            if (n & 1) {
                g->sp[k].ja = g->jt[n + 1][0];
                g->sp[k].jb = g->jt[n + 2][0];
            } else {
                g->sp[k].ja = g->jt[n + 1][0];
                g->sp[k].jb = g->jt[n][0];
            }
            g->sp[k].size = 18.0f;
            g->sp[k].f10 = 10.0f;
            g->sp[k].f1C = g->sp[k].size / 16.0f;
            g->sp[k].f20 = 1.05f;
            g->sp[k].col[1] = 0x10;
            g->sp[k].col[2] = 0x10;
            g->sp[k].col[0] = 0x80;
            g->sp[k].col[3] = 0;
            g->sp[k].col2[0] = 0x80;
            g->sp[k].col2[1] = 0x80;
            g->sp[k].col2[2] = 0x80;
            g->sp[k].col2[3] = 0x80;
            break;
        case 2:
            g->sp[k].size = 18.0f;
            g->sp[k].f10 = 10.0f;
            g->sp[k].col2[3] = 0x80;
            g->sp[k].f1C = g->sp[k].size / 16.0f;
            break;
        case 3:
            g->sp[k].size = 80.0f;
            g->sp[k].f10 = 15.0f;
            g->sp[k].col2[3] = 0xC0;
            g->sp[k].f1C = g->sp[k].size / 16.0f;
            break;
        }
    }
    if (mode == 3 && (n == 1 || n == 3)) {
        func_00101AD0(&g->tr[n - 1], 0x18, 0, 0xFF);
        g->tr[n - 1].b4 = 0;
        g->tr[n - 1].b5 = 0;
        g->tr[n - 1].b7 = 9;
        g->tr[n - 1].b8 = 0;
        g->tr[n - 1].bA = 0;
        g->tr[n - 1].b9 = 0;
        g->tr[n - 1].f0C = 4.0f;
        g->tr[n - 1].f10 = 0.5f;
        g->tr[n - 1].f14 = 0.9f;
        g->tr[n - 1].f18 = 0.0f;
        g->tr[n - 1].f1C = 0.1f;
        g->tr[n - 1].col[0] = 0x80;
        g->tr[n - 1].col[1] = 0x80;
        g->tr[n - 1].col[2] = 0x80;
        g->tr[n - 1].col[3] = 0xC0;
        g->tr[n - 1].col2[1] = 0x10;
        g->tr[n - 1].col2[2] = 0x10;
        g->tr[n - 1].col2[0] = 0x80;
        g->tr[n - 1].col2[3] = 0;
        func_001F5620(g->model, g->sp[(n - 1) * 4].ja, &p);
        g->tr[n - 1].pos = p;
        func_001F5620(g->model, g->sp[(n - 1) * 4].jb, &p);
        d[0] = g->tr[n - 1].pos.x - p.x;
        d[1] = g->tr[n - 1].pos.y - p.y;
        d[2] = g->tr[n - 1].pos.z - p.z;
        func_00101940(d, g->tr[n - 1].dir);
    }
}
#pragma optimization_level reset

INCLUDE_ASM("asm/nonmatchings/mod/b176", func_01E04DB0_b176);

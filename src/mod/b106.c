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

static void func_01E00080_b106(Obj_b010_01E00080 *o) {
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

INCLUDE_ASM("asm/nonmatchings/mod/b106", func_01E00410_b106);

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

static void func_01E00DC0_b106(Emit_b010_01E00DC0 *e) {
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

extern void b106_01E00DC0(Burst_b010_01E010E0 *);

#pragma optimization_level 2

static s32 func_01E010E0_b106(Obj_b010_01E010E0 *obj, u16 frame) {
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
                    b106_01E00DC0(&burst);
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

INCLUDE_ASM("asm/nonmatchings/mod/b106", func_01E015A0_b106);

INCLUDE_ASM("asm/nonmatchings/mod/b106", func_01E02350_b106);

INCLUDE_ASM("asm/nonmatchings/mod/b106", func_01E02EC0_b106);

INCLUDE_ASM("asm/nonmatchings/mod/b106", func_01E03730_b106);

/* OVL_CFLAGS: -O2,p -sdatathreshold 0 -relax_pointers */
/* OVL_WARM: compile warm (its (u32) cast is jal fptoui, func_001A23B0) */

/* shape b106:01E042B0, 461 insns: draws the module's flare entities (0x24 bytes each) as screen sprites: one
   packet set up on the first live entity, then per entity the point above its object (towards the camera,
   flipped by flags & 1) is projected and, when on screen, up to cnt quads per side are drawn stepping out by
   (dx, dy) * 16 from the screen centre. Sends the list if anything was live. */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b106_01E042B0;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b106_01E042B0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Uv_b106_01E042B0 uv;
    Xyz_b106_01E042B0 xyz;
} Vtx_b106_01E042B0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b106_01E042B0 v[4];
    u8 tail[8];
} Pkt_b106_01E042B0;

typedef struct {
    u8 life;
    u8 pad1;
    u8 span;
    u8 pad3;
    u8 flags;
    u8 pad5[3];
    u8 len;
    u8 blend;
    u8 dx;
    u8 dy;
    s32 obj;
    u8 pad10[3];
    u8 alpha;
    u8 pad14[0x10];
} Flare_b106_01E042B0;

#pragma optimization_level 2

static s32 func_01E042B0_b106(Flare_b106_01E042B0 *arg0, s32 ot __attribute__((aligned(8))), s32 n) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_001F7060(s32, s32, void *, void *);
    extern Vec4f *func_001F9AD0(s32);
    extern void func_001F53C0(s32, s32, void *);
    extern f32 func_001F5860(s32);
    extern void func_00101A00(void *, void *);
    extern void func_0020CDD0(void *, void *, void *);
    extern s32 func_00101770(void *);
    extern void func_00101C80(void *, u8 *);
    Flare_b106_01E042B0 *e = arg0;
    f32 mat[16];
    Vec4f pos;
    Vec4f d;
    Vec4f p;
    Vec4f cam;
    f32 m2[16];
    u8 td[0x20];
    struct {
        Pkt_b106_01E042B0 pk;
        s32 a[2];
        s32 b[2];
    } w;
    Xyz_b106_01E042B0 xy;
    f32 depth;
    u8 bl[4];
    s32 i;
    s32 list;
    s32 any;
    s32 j;
    s32 k;
    s32 cnt;
    s32 y;
    s32 x;

    list = func_00207F60();
    any = 0;
    for (i = 0; i < n; i++) {
        if (i != 0) {
            e++;
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        if (any == 0) {
            ((Pkt_b106_01E042B0 *)(s32)&w.pk)->count = 0x34;
            ((Pkt_b106_01E042B0 *)(s32)&w.pk)->tag = 0xC;
            ((Pkt_b106_01E042B0 *)(s32)&w.pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
            ((Pkt_b106_01E042B0 *)(s32)&w.pk)->pad = 0;
            w.pk.v[0].r = w.pk.v[1].r = w.pk.v[2].r = w.pk.v[3].r = w.pk.v[0].g = w.pk.v[1].g = w.pk.v[2].g = w.pk.v[3].g =
                w.pk.v[0].b = w.pk.v[1].b = w.pk.v[2].b = w.pk.v[3].b = w.pk.v[0].a = w.pk.v[1].a = w.pk.v[2].a =
                    w.pk.v[3].a = 0x80;
            w.pk.v[0].q = w.pk.v[1].q = w.pk.v[2].q = w.pk.v[3].q = 1.0f;
            w.pk.v[0].xyz.z = w.pk.v[1].xyz.z = w.pk.v[2].xyz.z = w.pk.v[3].xyz.z = 0xFFFFFF;
            w.pk.v[0].xyz.f = w.pk.v[1].xyz.f = w.pk.v[2].xyz.f = w.pk.v[3].xyz.f = 0;
            func_00208460();
            func_001F7060(e->obj, 0, w.a, w.b);
            func_00208460();
            any = 1;
            ((Pkt_b106_01E042B0 *)(s32)&w.pk)->count |= 0x800;
            ((Uv_b106_01E042B0 *)(s32)&w.pk.v[0].uv)->u = 0;
            ((Uv_b106_01E042B0 *)(s32)&w.pk.v[0].uv)->v = 0;
            ((Uv_b106_01E042B0 *)(s32)&w.pk.v[1].uv)->u = 0x2800;
            ((Uv_b106_01E042B0 *)(s32)&w.pk.v[1].uv)->v = 0;
            ((Uv_b106_01E042B0 *)(s32)&w.pk.v[2].uv)->u = 0;
            ((Uv_b106_01E042B0 *)(s32)&w.pk.v[2].uv)->v = 0x1C00;
            ((Uv_b106_01E042B0 *)(s32)&w.pk.v[3].uv)->u = 0x2800;
            ((Uv_b106_01E042B0 *)(s32)&w.pk.v[3].uv)->v = 0x1C00;
        }
        func_0020EB40(mat);
        cam = *func_001F9AD0(0);
        func_001F53C0(1, e->obj, &pos);
        d.x = cam.x - pos.x;
        d.y = cam.y - pos.y;
        d.z = cam.z - pos.z;
        func_00101A00(&d, m2);
        d.x = d.z = 0.0f;
        d.y = func_001F5860(e->obj);
        if (e->flags & 1) {
            d.y *= -1.0f;
        }
        func_0020CDD0(&p, m2, &d);
        p.x += pos.x;
        p.y += pos.y;
        p.z += pos.z;
        if (func_00205440(&p, mat, &xy, &depth) != 0 && func_00101770(&xy) != 0) {
            w.pk.v[0].xyz.z = w.pk.v[1].xyz.z = w.pk.v[2].xyz.z = w.pk.v[3].xyz.z = xy.z;
            w.pk.v[0].xyz.f = w.pk.v[1].xyz.f = w.pk.v[2].xyz.f = w.pk.v[3].xyz.f = 0;
            td[5] = e->blend;
            func_00101C80(td, bl);
            func_002086D0(&w.pk, (u64)bl[0] | ((u64)bl[1] << 2) | ((u64)bl[2] << 4) | ((u64)bl[3] << 6));
            w.pk.v[0].a = w.pk.v[1].a = w.pk.v[2].a = w.pk.v[3].a = e->alpha;
            cnt = e->len >> 1;
            if (e->span - e->life + 1 < cnt) {
                cnt = e->span - e->life + 1;
            }
            if (e->life < cnt) {
                cnt = e->life;
            }
            for (k = 0; k < 2; k++) {
                for (j = 0; j < cnt; j++) {
                    if (k) {
                        x = e->dx * (j + 1);
                        y = e->dy * (j + 1);
                    } else {
                        x = -e->dx * (j + 1);
                        y = -e->dy * (j + 1);
                    }
                    w.pk.v[0].xyz.x = w.pk.v[2].xyz.x = (x << 4) + 27648.0f;
                    w.pk.v[1].xyz.x = w.pk.v[3].xyz.x = 37888.0f + (x << 4);
                    w.pk.v[0].xyz.y = w.pk.v[1].xyz.y = (y << 4) + 29184.0f;
                    w.pk.v[2].xyz.y = w.pk.v[3].xyz.y = 36352.0f + (y << 4);
                    func_002075F0(&w.pk, 0, (u32)depth);
                }
            }
        }
    }
    if (any) {
        func_00207FD0(list, ot, 0);
    }
    return 1;
}
#pragma optimization_level reset

INCLUDE_ASM("asm/nonmatchings/mod/b106", func_01E049F0_b106);

INCLUDE_ASM("asm/nonmatchings/mod/b106", func_01E05580_b106);

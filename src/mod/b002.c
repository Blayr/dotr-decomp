#include "common.h"

/* OVL_CFLAGS: -O1,p -sdatathreshold 0 -relax_pointers */

/* shape b002:01E00080, 237 insns, 27 copies: b010:01E00080 (move an emitter, set its level from the blend mode) built at -O1,p: every field read again, nothing CSEd */

typedef struct Obj_b002_01E00080 {
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
} Obj_b002_01E00080;

#pragma optimization_level 1

static void func_01E00080_b002(Obj_b002_01E00080 *arg0) {
    extern s32 func_00101AF0();
    extern void func_00101BA0();
    extern void func_001F6C10();
    Obj_b002_01E00080 *o;
    u8 d;
    u8 e;
    s32 on;
    f32 k;

    o = arg0;
    if (func_00101AF0(o) == 0) {
        return;
    }
    o->pos.x += o->vel.x;
    o->pos.y += o->vel.y;
    o->pos.z += o->vel.z;
    func_00101BA0(o, &o->pos);
    d = o->b0 & o->b3;
    e = o->b2 - o->b0;
    if (o->b3 == 0xFF) {
        k = o->base / o->b2;
    } else {
        k = o->base / (o->b3 + 1);
    }
    on = 1;
    switch (o->b4 & 0xF) {
    case 1:
        o->level = k * d;
        break;
    case 2:
        if (o->b3 == 0xFF) {
            if (e < o->b2 >> 1) {
                o->level = 2.0f * k * e;
            } else {
                o->level = 2.0f * k * o->b0;
            }
        } else {
            if (d < o->b3 >> 1) {
                o->level = 2.0f * k * (o->b3 - d);
            } else {
                o->level = 2.0f * k * d;
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
        if (o->b0 & 1) {
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

INCLUDE_ASM("asm/nonmatchings/mod/b002", func_01E00440_b002);

/* OVL_CFLAGS: -O1,p -sdatathreshold 0 -relax_pointers */

typedef struct {
    u8 pad00[3];
    u8 frame;
    f32 x, y, z;
    f32 vx, vy, vz;
    f32 ax, ay, az;
} Node_b002_01E00E60;

typedef struct {
    u8 pad00[8];
    Node_b002_01E00E60 *pool;
    s16 ids[8];
    u8 kind;
    u8 count;
} Sys_b002_01E00E60;

typedef struct {
    Sys_b002_01E00E60 *sys;
    u8 life;
    u8 mask;
    u8 pad06[2];
    f32 speed;
    f32 rise;
    f32 radius;
    f32 cx, cy, cz;
} Burst_b002_01E00E60;

#pragma optimization_level 1

static void func_01E00E60_b002(Burst_b002_01E00E60 *arg) {
    extern void func_00101B40(void *, u8, u8);
    extern s32 func_00101C30(void *, s32, s32);
    extern f32 func_001A6898(f32);
    extern f32 func_001A6A88(f32);
    Burst_b002_01E00E60 *pr;
    Sys_b002_01E00E60 *s;
    Node_b002_01E00E60 *node;
    s32 i;
    s32 idx;
    f32 angle;
    f32 step;
    f32 c;
    f32 sn;

    pr = arg;
    s = pr->sys;
    angle = 180.0f + (f32)((func_0019A5C8() >> 4) % 36000 - 18000) / 100.0f;
    step = 360.0f / s->count;
    for (i = 0; i < s->count; i++) {
        idx = func_00101C30(s->pool, 0x28, s->kind);
        if (idx >= 0) {
            s->ids[i] = idx;
            node = &s->pool[idx];
            func_00101B40(node, pr->life, pr->mask & (func_0019A5C8() >> 4));
            node->frame = ((func_0019A5C8() >> 4) & 3) << 4;
            angle += step;
            if (!(angle <= 360.0f)) {
                angle -= 360.0f;
            }
            c = func_001A6A88(3.1415927f * angle / 180.0f);
            sn = func_001A6898(3.1415927f * angle / 180.0f);
            node->x = pr->cx + pr->radius * sn;
            node->z = pr->cz + pr->radius * c;
            node->y = pr->cy;
            node->vx = pr->speed * sn;
            node->vz = pr->speed * c;
            node->vy = pr->rise;
            node->ax = -(node->vx / pr->life);
            node->az = -(node->vz / pr->life);
            node->ay = 0.0f;
        } else {
            s->ids[i] = -1;
        }
    }
}
#pragma optimization_level reset

/* OVL_CFLAGS: -O1,p -sdatathreshold 0 -relax_pointers */

/* shape b002:01E011B0, 312 insns, 6 copies: effect spawner (per-frame joint lists -> b002:01E00E60 bursts, then a
   timed particle cloud). Calls b002_01E00E60 of the same module as a plain extern. Its Burst type here uses a Vec
   for the centre where ovl-matched/b002_01E00E60.c has three floats: same layout, unify the types when integrating. */

typedef struct {
    f32 x, y, z, w;
} Vec_b002_01E011B0;

typedef struct {
    u8 pad00[3];
    u8 frame;
    f32 x, y, z;
    f32 vx, vy, vz;
    f32 ax, ay, az;
} Part_b002_01E011B0;

typedef struct {
    u8 pad00[4];
    u8 b4;
    u8 pad05[3];
    Part_b002_01E011B0 *pool;
    s16 ids[8];
    u8 kind;
    u8 count;
    u8 b1E;
    u8 b1F;
    u8 b20;
    u8 pad21;
    u8 r, g, b, a;
    u8 pad26[2];
    f32 f28;
    f32 f2C;
    f32 f30;
    f32 f34;
} Node_b002_01E011B0;

typedef struct {
    Node_b002_01E011B0 *sys;
    u8 life;
    u8 mask;
    u8 pad06[2];
    f32 speed;
    f32 rise;
    f32 radius;
    Vec_b002_01E011B0 c;
} Burst_b002_01E011B0;

typedef struct {
    Node_b002_01E011B0 *nodes;
    Part_b002_01E011B0 *parts;
    s16 *lists[8];
    u8 joint[8];
    u8 kind;
    u8 pkind;
    u8 b32;
    u8 joint2;
    s16 start;
    s16 end;
    f32 f38;
    f32 f3C;
    f32 f40;
} Spawner_b002_01E011B0;

extern void b002_01E00E60(Burst_b002_01E011B0 *);

#pragma optimization_level 1

static s32 func_01E011B0_b002(Spawner_b002_01E011B0 *obj, u16 t) {
    extern s32 func_001F53A0(void);
    extern s32 func_001F5620(s32, s32, void *);
    extern s32 func_00101C30(void *, s32, s32);
    extern void func_00101AD0(void *, s32, s32, s32);
    extern void func_00101B40(void *, s32, s32);
    Spawner_b002_01E011B0 *o;
    Node_b002_01E011B0 *node;
    s16 *p;
    s32 k;
    Part_b002_01E011B0 *part;
    s32 idx;
    Vec_b002_01E011B0 pos;
    Burst_b002_01E011B0 burst;

    o = obj;
    for (k = 0; k < 8; k++) {
        if (o->lists[k] == 0) {
            continue;
        }
        for (p = o->lists[k]; *p > 0; p++) {
            if (*p != t) {
                continue;
            }
            if (func_001F5620(func_001F53A0(), o->joint[k], &pos) == 0) {
                break;
            }
            idx = func_00101C30(o->nodes, 0x38, o->kind);
            if (idx < 0) {
                return 0;
            }
            node = &o->nodes[idx];
            func_00101AD0(node, 1, 0, 0xFF);
            node->b4 = 4;
            node->pool = o->parts;
            node->kind = o->pkind;
            node->count = 4;
            node->b1E = 1;
            node->b1F = o->b32;
            node->b20 = 4;
            node->b = node->g = node->r = 0x90;
            node->a = 0x30;
            node->f28 = o->f38;
            node->f2C = o->f40;
            node->f30 = -0.015f;
            node->f34 = pos.y;
            burst.sys = node;
            burst.life = 0x20;
            burst.mask = 3;
            burst.speed = 0.25f;
            burst.rise = 0.3f;
            burst.radius = 0.15f;
            burst.c = pos;
            b002_01E00E60(&burst);
        }
    }
    if (o->start != 0 && o->start <= t && o->end >= t) {
        if (func_001F5620(func_001F53A0(), o->joint2, &pos) == 0) {
            return 0;
        }
        idx = func_00101C30(o->nodes, 0x38, o->kind);
        if (idx < 0) {
            return 0;
        }
        node = &o->nodes[idx];
        func_00101AD0(node, 1, 0, 0xFF);
        node->b4 = 4;
        node->pool = o->parts;
        node->kind = o->pkind;
        node->count = 2;
        node->b1E = 1;
        node->b1F = o->b32;
        node->b20 = 4;
        node->b = node->g = node->r = 0x90;
        node->a = 0x30;
        node->f28 = o->f3C;
        node->f2C = o->f40;
        node->f30 = -0.007f;
        node->f34 = 0.0f;
        for (k = 0; k < node->count; k++) {
            idx = func_00101C30(o->parts, 0x28, o->pkind);
            if (idx >= 0) {
                node->ids[k] = idx;
                part = &o->parts[idx];
                func_00101B40(part, 0x20, 0);
                part->frame = ((func_0019A5C8() >> 4) & 3) << 4;
                part->x = pos.x + (f32)((func_0019A5C8() >> 4) % 500 - 250) / 100.0f;
                part->z = pos.z + (f32)((func_0019A5C8() >> 4) % 500 - 250) / 100.0f;
                part->y = pos.y + (f32)((func_0019A5C8() >> 4) % 500 - 250) / 100.0f;
                part->vx = part->vy = part->vz = part->ax = part->ay = part->az = 0.0f;
            } else {
                node->ids[k] = -1;
            }
        }
    }
    return 1;
}
#pragma optimization_level reset

INCLUDE_ASM("asm/nonmatchings/mod/b002", func_01E01690_b002);

INCLUDE_ASM("asm/nonmatchings/mod/b002", func_01E02AD0_b002);

INCLUDE_ASM("asm/nonmatchings/mod/b002", func_01E037F0_b002);

INCLUDE_ASM("asm/nonmatchings/mod/b002", func_01E04520_b002);

INCLUDE_ASM("asm/nonmatchings/mod/b002", func_01E053E0_b002);

INCLUDE_ASM("asm/nonmatchings/mod/b002", func_01E05FE0_b002);

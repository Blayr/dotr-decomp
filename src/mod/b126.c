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

static void func_01E00080_b126(Obj_b002_01E00080 *arg0) {
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

INCLUDE_ASM("asm/nonmatchings/mod/b126", func_01E00440_b126);

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

static void func_01E00E60_b126(Burst_b002_01E00E60 *arg) {
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
   timed particle cloud). Calls b126_01E00E60 of the same module as a plain extern. Its Burst type here uses a Vec
   for the centre where ovl-matched/b126_01E00E60.c has three floats: same layout, unify the types when integrating. */

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

extern void b126_01E00E60(Burst_b002_01E011B0 *);

#pragma optimization_level 1

static s32 func_01E011B0_b126(Spawner_b002_01E011B0 *obj, u16 t) {
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
            b126_01E00E60(&burst);
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

/* OVL_CFLAGS: -O1,p -sdatathreshold 0 -relax_pointers */
/* OVL_WARM */

#define ABS_b011_01E04380(x) ((x) >= 0 ? (x) : -(x))

typedef struct {
    f32 x, y, z, w;
} Vec_b011_01E04380;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b011_01E04380;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    Xyz_b011_01E04380 p;
} Vtx_b011_01E04380;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b011_01E04380 v[4];
    u8 tail[0x20];
} Pkt_b011_01E04380;

typedef struct {
    s32 id;
    u8 kind;
    u8 page;
    u8 pad06[6];
    s32 u;
    u8 pad10[4];
    s32 v;
} Tex_b011_01E04380;

typedef struct {
    u8 step;
    u8 pad01;
    u8 total;
    u8 pad03;
    u8 flags;
    u8 pad05[3];
    u8 segments;
    u8 index;
    u8 texkind;
    u8 texpage;
    u8 texmode;
    u8 delay;
    u8 target;
    u8 pad0F;
    u8 *table;
    f32 size;
    f32 radius;
    f32 width;
    u8 b0, g0, r0, a0;
    u8 b1, g1, r1, a1;
    Vec_b011_01E04380 pos;
    Vec_b011_01E04380 vel;
    s32 rot[4];
    s32 spin[4];
} Ray_b011_01E04380;

extern Tex_b011_01E04380 D_01E05880_b126;

#pragma optimization_level 1

static s32 func_01E01690_b126(Ray_b011_01E04380 *obj, s32 target, s32 count) {
    extern s32 func_00202BF0(s32, s32);
    extern s32 func_00101AF0(void *);
    extern void func_001020B0(void *, s32, s32);
    extern void func_00101BA0(void *, void *);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_00101940(void *, void *);
    extern void func_0020EB40(void *);
    extern void func_0020C940(void *, s32, void *, void *);
    extern void func_0020BC00(void *, void *);
    extern void func_00101EE0(void *, void *, s32);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern s32 func_00101600(void *);
    extern f32 func_001018E0(f32, f32);
    extern f32 func_001A6898(f32);
    extern f32 func_001A6A88(f32);
    extern void func_002075F0(void *, s32, s32);
    Ray_b011_01E04380 *o;
    s32 i;
    s32 j;
    u8 idx;
    s32 span;
    s32 texture;
    f32 w;
    f32 zd;
    f32 y;
    f32 angle;
    f32 x;
    f32 r;
    f32 z;
    f32 step;
    f32 m2[16];
    f32 m1[16];
    Xyz_b011_01E04380 xy[2];
    Vec_b011_01E04380 pt;
    Vec_b011_01E04380 d;
    Vec_b011_01E04380 tmp;
    Tex_b011_01E04380 tex0;
    Tex_b011_01E04380 tex;
    Pkt_b011_01E04380 pkt __attribute__((aligned(8)));
    f32 dep[2];

    o = obj;
    tex0 = D_01E05880_b126;
    for (i = 0; i < count; i++) {
        if (i != 0) {
            o++;
        }
        if (func_00101AF0(o) == 0) {
            continue;
        }
        if (o->flags & 4) {
            texture = func_00202BF0(5, o->texkind);
            tex.page = o->texpage;
            func_001020B0(&tex, o->texmode, 0);
        } else {
            texture = func_00202BF0(tex0.id, tex0.kind);
            tex = tex0;
        }
        if (!(o->flags & 2)) {
            tex.u -= 0x10;
            tex.v -= 0x10;
        }
        idx = o->index;
        step = 17.0f;
        angle = 0.0f;
        if (o->step < o->delay) {
            span = o->total - o->delay;
        } else {
            span = o->total - o->step;
        }
        o->pos.x += o->vel.x;
        o->pos.y += o->vel.y;
        o->pos.z += o->vel.z;
        o->rot[0] += o->spin[0];
        o->rot[1] += o->spin[1];
        o->rot[2] += o->spin[2];
        func_00101BA0(o, &o->pos);
        if (o->flags & 8) {
            func_001F5620(func_001F53A0(), o->target, &tmp);
            d.x = tmp.x - o->pos.x;
            d.y = tmp.y - o->pos.y;
            d.z = tmp.z - o->pos.z;
            func_00101940(&d, o->rot);
        }
        func_0020EB40(m1);
        func_0020C940(m2, 0, o->rot, &o->pos);
        func_0020BC00(m1, m2);
        ((Pkt_b011_01E04380 *)(s32)&pkt)->count = 0x34;
        ((Pkt_b011_01E04380 *)(s32)&pkt)->tag = 0xC;
        ((Pkt_b011_01E04380 *)(s32)&pkt)->regs = 0x421421421421LL;
        ((Pkt_b011_01E04380 *)(s32)&pkt)->pad = 0;
        pkt.v[0].r = pkt.v[1].r = o->r0;
        pkt.v[2].r = pkt.v[3].r = o->r1;
        pkt.v[0].g = pkt.v[1].g = o->g0;
        pkt.v[2].g = pkt.v[3].g = o->g1;
        pkt.v[0].b = pkt.v[1].b = o->b0;
        pkt.v[2].b = pkt.v[3].b = o->b1;
        pkt.v[0].q = pkt.v[1].q = pkt.v[2].q = pkt.v[3].q = 1.0f;
        if (o->step <= 7 && !(o->flags & 0x40)) {
            pkt.v[0].a = pkt.v[1].a = pkt.v[2].a = (o->a0 >> 3) * o->step;
            pkt.v[3].a = (o->a1 >> 3) * o->step;
        } else {
            pkt.v[0].a = pkt.v[1].a = pkt.v[2].a = o->a0;
            pkt.v[3].a = o->a1;
        }
        func_00101EE0(&pkt, &tex, texture);
        pt.x = pt.y = pt.z = 0.0f;
        if (func_00205440(&pt, m1, &xy[1], &dep[1]) == 0 || func_00101600(&xy[1]) == 0) {
            continue;
        }
        for (j = 0; j < o->segments; j++) {
            if (o->flags & 1) {
                x = o->size * (o->table[idx] - o->table[idx + 1]) / 255.0f;
                y = o->size * (o->table[idx + 2] - o->table[idx + 3]) / 255.0f;
                z = o->size * (o->table[idx + 4] - o->table[idx + 5]) / 255.0f;
                idx += 6;
            } else {
                angle += step;
                if (!(angle <= 360.0f)) {
                    angle -= 360.0f;
                }
                r = o->radius * o->table[idx] / 255.0f;
                idx++;
                x = r * func_001A6898(3.1415927f * angle / 180.0f);
                z = r * func_001A6A88(3.1415927f * angle / 180.0f);
                y = o->size / 2.0f;
                y += y * (o->table[idx] / 255.0f);
                idx++;
            }
            pt.x = x * span;
            pt.y = y * span;
            pt.z = z * span;
            if (func_00205440(&pt, m1, &xy[0], &dep[0]) == 0 || func_00101600(&xy[0]) == 0) {
                continue;
            }
            w = func_001018E0(o->width, dep[0]);
            if (o->flags & 0x80) {
                pkt.v[0].p.z = pkt.v[1].p.z = pkt.v[2].p.z = pkt.v[3].p.z = 0xFFFFFE;
                zd = 0.0f;
            } else {
                if (dep[0] < dep[1]) {
                    zd = dep[0];
                } else {
                    zd = dep[1];
                }
                pkt.v[0].p.z = pkt.v[1].p.z = xy[0].z;
                pkt.v[2].p.z = pkt.v[3].p.z = xy[1].z;
            }
            pkt.v[0].p.f = pkt.v[1].p.f = pkt.v[2].p.f = pkt.v[3].p.f = 0;
            if (ABS_b011_01E04380(xy[1].x - xy[0].x) > ABS_b011_01E04380(xy[1].y - xy[0].y)) {
                pkt.v[0].p.y = xy[0].y;
                pkt.v[1].p.y = (u32)(xy[0].y - w);
                pkt.v[2].p.y = (u32)(xy[0].y + w);
                pkt.v[3].p.y = xy[1].y;
                if (xy[0].x < xy[1].x) {
                    pkt.v[0].p.x = (u32)(xy[0].x - w);
                } else {
                    pkt.v[0].p.x = (u32)(xy[0].x + w);
                }
                pkt.v[1].p.x = pkt.v[2].p.x = xy[0].x;
                pkt.v[3].p.x = xy[1].x;
            } else {
                pkt.v[0].p.x = xy[0].x;
                pkt.v[1].p.x = (u32)(xy[0].x - w);
                pkt.v[2].p.x = (u32)(xy[0].x + w);
                pkt.v[3].p.x = xy[1].x;
                if (xy[0].y < xy[1].y) {
                    pkt.v[0].p.y = (u32)(xy[0].y - w);
                } else {
                    pkt.v[0].p.y = (u32)(xy[0].y + w);
                }
                pkt.v[1].p.y = pkt.v[2].p.y = xy[0].y;
                pkt.v[3].p.y = xy[1].y;
            }
            func_002075F0(&pkt, target, (u32)zd);
        }
    }
    return 1;
}
#pragma optimization_level reset

INCLUDE_ASM("asm/nonmatchings/mod/b126", func_01E023C0_b126);

INCLUDE_ASM("asm/nonmatchings/mod/b126", func_01E030E0_b126);

/* OVL_CFLAGS: -O1,p -sdatathreshold 0 -relax_pointers */

/* shape b061:01E03440, 346 insns, 11 copies: b010:01E05740 rewritten for an -O1,p file (no mode/w temps, c = 32768.0f, one long 0xFF chain, local copy of the object pointer): full-screen fade quad (4 vertices); its alpha follows the emitter's counter */

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
} Hdr_b061_01E03440;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b061_01E03440;

typedef struct {
    Hdr_b061_01E03440 h;
    Vtx_b061_01E03440 v[4];
    u8 tail[8];
} Pkt_b061_01E03440;

typedef struct {
    u8 cur;
    u8 pad1;
    u8 max;
    u8 pad3;
    u8 flags;
} Obj_b061_01E03440;

#pragma optimization_level 1

static s32 func_01E03BB0_b126(Obj_b061_01E03440 *arg0, s32 tex) {
    Obj_b061_01E03440 *o = arg0;
    Pkt_b061_01E03440 p __attribute__((aligned(8)));
    u8 a;
    s32 d;
    f32 s;
    f32 c;

    if (func_00101AF0(o) == 0) {
        return 0;
    }
    ((Hdr_b061_01E03440 *)(s32)&p)->count = 0x14;
    ((Hdr_b061_01E03440 *)(s32)&p)->tag = 8;
    ((Hdr_b061_01E03440 *)(s32)&p)->regs = 0x41414141;
    ((Hdr_b061_01E03440 *)(s32)&p)->pad = 0;
    switch (o->flags & 7) {
    case 1:
        a = func_001A23B0(128.0f / o->max * o->cur);
        break;
    case 2:
        a = ((o->max - o->cur) << 7) / o->max;
        break;
    case 4:
    default:
        a = 0x80;
        break;
    }
    if (o->cur == 1 && (o->flags & 0x80)) {
        o->cur = o->max;
        if (o->flags & 1) {
            o->flags = 2;
        } else {
            o->flags = 1;
        }
    }
    if (o->flags & 8) {
        a >>= 1;
    }
    p.v[0].r = p.v[1].r = p.v[2].r = p.v[3].r = p.v[0].g = p.v[1].g = p.v[2].g = p.v[3].g =
        p.v[0].b = p.v[1].b = p.v[2].b = p.v[3].b = 0xFF;
    p.v[0].q = p.v[1].q = p.v[2].q = p.v[3].q = 1.0f;
    p.v[0].z = p.v[1].z = p.v[2].z = p.v[3].z = 0xFFFFFF;
    func_002086D0(&p, 0x48);
    if (o->flags & 0x10) {
        s = 7168.0f / (o->max >> 1);
        c = 32768.0f;
        d = o->max - o->cur;
        a = (0x80 / (o->max >> 1)) * (d >> 1);
        if ((o->max >> 1) < d) {
            p.v[0].a = p.v[1].a = a;
            d = o->max >> 1;
        } else {
            p.v[0].a = p.v[1].a = 0;
        }
        p.v[2].a = p.v[3].a = 0x80;
        p.v[0].x = p.v[2].x = 0x6C00;
        p.v[1].x = p.v[3].x = 0x9400;
        p.v[0].y = p.v[1].y = func_001A23B0(c - s * d);
        p.v[2].y = p.v[3].y = func_001A23B0(c);
        func_002075F0((s32)&p, tex, 0);
        p.v[2].a = p.v[3].a = p.v[1].a;
        p.v[1].a = p.v[0].a = 0x80;
        p.v[0].y = p.v[1].y = func_001A23B0(c);
        p.v[2].y = p.v[3].y = func_001A23B0(c + s * d);
        func_002075F0((s32)&p, tex, 0);
    } else {
        p.v[0].a = p.v[1].a = p.v[2].a = p.v[3].a = a;
        if (o->flags & 0x20) {
            p.v[2].a = p.v[3].a = 0;
        }
        if (o->flags & 0x40) {
            p.v[0].a = p.v[1].a = 0;
        }
        p.v[0].x = p.v[2].x = 0x6C00;
        p.v[1].x = p.v[3].x = 0x9400;
        p.v[0].y = p.v[1].y = 0x7200;
        p.v[2].y = p.v[3].y = 0x8E00;
        func_002075F0((s32)&p, tex, 0);
    }
    return 1;
}
#pragma optimization_level reset

INCLUDE_ASM("asm/nonmatchings/mod/b126", func_01E04120_b126);

INCLUDE_ASM("asm/nonmatchings/mod/b126", func_01E04FE0_b126);

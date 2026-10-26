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

/* OVL_CFLAGS: -O2,p -sdatathreshold 0 -relax_pointers */

/* shape b010:01E00410, 620 insns, 35 copies: the code of shape b011:01E00440 built at -O2 (n particle emitters (0x38
   bytes each), each with up to 8 particles (0x28 bytes, indexes into a shared table): moves each live particle
   (gravity, floor), sizes it by age, and draws it as a textured screen-space quad of radius func_001018E0(scale,
   depth), flipped by the particle's flags & 0x30) */

/* OVL_CFLAGS: -O1,p -sdatathreshold 0 -relax_pointers */
/* OVL_WARM: compile warm (its (u32) casts are jal fptoui, func_001A23B0) */

/* shape b011:01E00440, 647 insns: n particle emitters (0x38 bytes each), each with up to 8 particles (0x28 bytes,
   indexes into a shared table): moves each live particle (gravity, floor), sizes it by age, and draws it as a
   textured screen-space quad of radius func_001018E0(scale, depth), flipped by the particle's flags & 0x30 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b011_01E00440;

typedef struct {
    f32 s, t;
    Xyz_b011_01E00440 xyz;
} Vtx_b011_01E00440;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Vtx_b011_01E00440 v[4];
    u8 tail[0x20];
} Pkt_b011_01E00440;

typedef struct {
    s32 id;
    u8 sub;
    u8 b5;
    u8 pad6[2];
    s32 u, w, v, h;
} Tex_b011_01E00440;

typedef struct {
    f32 x, y, z;
} V3_b011_01E00440;

typedef struct {
    u8 life;
    u8 pad1;
    u8 max;
    u8 flags;
    V3_b011_01E00440 pos;
    V3_b011_01E00440 vel;
    V3_b011_01E00440 acc;
} Part_b011_01E00440;

typedef struct {
    u8 drawn;
    u8 pad1[3];
    u8 flags;
    u8 pad5[3];
    Part_b011_01E00440 *parts;
    s16 idx[8];
    u8 pad1C;
    u8 count;
    u8 sub;
    u8 texid;
    u8 size;
    u8 shift;
    u8 b, g, r, a;
    f32 scale;
    f32 dscale;
    f32 grav;
    f32 floor;
} Emit_b011_01E00440;

#pragma optimization_level 2

static s32 func_01E00410_b176(void *arg0, s32 ot, s32 n) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_001020B0(void *, s32, s32);
    extern void func_00101D20(void *, void *, void *);
    extern f32 func_001018E0(f32, f32);
    f32 mat[16];
    Vec4f pos;
    Tex_b011_01E00440 td;
    Pkt_b011_01E00440 pkt __attribute__((aligned(8)));
    Xyz_b011_01E00440 xyz;
    f32 dep;
    Emit_b011_01E00440 *e;
    s32 i;
    Part_b011_01E00440 *parts;
    Part_b011_01E00440 *p;
    s32 j;
    s32 tex;
    s32 d;
    s32 sz;
    f32 r;

    e = arg0;
    parts = e->parts;
    for (i = 0; i < n; i++) {
        if (i != 0) {
            e++;
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        if (e->flags & 4) {
            tex = func_00202BF0(5, e->texid);
        } else {
            tex = func_00202BF0(4, 2);
        }
        e->scale += e->dscale;
        for (j = 0; j < e->count; j++) {
            if (e->idx[j] == -1) {
                continue;
            }
            p = &parts[e->idx[j]];
            if (p->life < 2) {
                e->idx[j] = -1;
            } else {
                e->drawn = 1;
            }
            if (func_00101B50(p) == 0) {
                continue;
            }
            p->vel.x += p->acc.x;
            p->vel.y += p->acc.y + e->grav;
            p->vel.z += p->acc.z;
            p->pos.x += p->vel.x;
            p->pos.y += p->vel.y;
            p->pos.z += p->vel.z;
            if (p->pos.y < e->floor) {
                p->pos.y = e->floor;
            }
            pos.x = p->pos.x;
            pos.y = p->pos.y;
            pos.z = p->pos.z;
            func_0020EB40(mat);
            ((Pkt_b011_01E00440 *)(s32)&pkt)->count = 0x24;
            ((Pkt_b011_01E00440 *)(s32)&pkt)->tag = 9;
            ((Pkt_b011_01E00440 *)(s32)&pkt)->regs = ((u64)4 << 32) | 0x24242421;
            ((Pkt_b011_01E00440 *)(s32)&pkt)->pad = 0;
            pkt.r = e->r;
            pkt.g = e->g;
            pkt.b = e->b;
            pkt.q = 1.0f;
            d = p->max - p->life;
            sz = e->size;
            if (e->flags & 8) {
                sz = ((d >> e->shift) & 3) + 2;
                if (d < 3) {
                    sz = d;
                }
                if (p->life < 7) {
                    sz = 7 - (p->life >> e->shift);
                }
            }
            td.b5 = e->sub;
            func_001020B0(&td, sz, 0);
            func_00101D20(&pkt, &td, (void *)tex);
            if (p->life < 16) {
                pkt.a = (e->a >> 4) * p->life;
            } else {
                pkt.a = e->a;
            }
            if (func_00205440(&pos, mat, &xyz, &dep) == 0 || func_00101600(&xyz) == 0) {
                continue;
            }
            r = func_001018E0(e->scale, dep);
            pkt.v[0].xyz.z = pkt.v[1].xyz.z = pkt.v[2].xyz.z = pkt.v[3].xyz.z = xyz.z;
            switch (p->flags & 0x30) {
            case 0x10:
                pkt.v[0].xyz.x = pkt.v[1].xyz.x = (u32)(xyz.x - r);
                pkt.v[2].xyz.x = pkt.v[3].xyz.x = (u32)(xyz.x + r);
                pkt.v[1].xyz.y = pkt.v[3].xyz.y = (u32)(xyz.y - r);
                pkt.v[0].xyz.y = pkt.v[2].xyz.y = (u32)(xyz.y + r);
                break;
            case 0x20:
                pkt.v[1].xyz.x = pkt.v[3].xyz.x = (u32)(xyz.x - r);
                pkt.v[0].xyz.x = pkt.v[2].xyz.x = (u32)(xyz.x + r);
                pkt.v[2].xyz.y = pkt.v[3].xyz.y = (u32)(xyz.y - r);
                pkt.v[0].xyz.y = pkt.v[1].xyz.y = (u32)(xyz.y + r);
                break;
            case 0x30:
                pkt.v[2].xyz.x = pkt.v[3].xyz.x = (u32)(xyz.x - r);
                pkt.v[0].xyz.x = pkt.v[1].xyz.x = (u32)(xyz.x + r);
                pkt.v[0].xyz.y = pkt.v[2].xyz.y = (u32)(xyz.y - r);
                pkt.v[1].xyz.y = pkt.v[3].xyz.y = (u32)(xyz.y + r);
                break;
            default:
                pkt.v[0].xyz.x = pkt.v[2].xyz.x = (u32)(xyz.x - r);
                pkt.v[1].xyz.x = pkt.v[3].xyz.x = (u32)(xyz.x + r);
                pkt.v[0].xyz.y = pkt.v[1].xyz.y = (u32)(xyz.y - r);
                pkt.v[2].xyz.y = pkt.v[3].xyz.y = (u32)(xyz.y + r);
                break;
            }
            func_002075F0((s32)&pkt, ot, (u32)dep);
        }
    }
    return 1;
}
#pragma optimization_level reset

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

/* OVL_CFLAGS: -O2,p -sdatathreshold 0 -relax_pointers */

/* shape b032:01E02820, 538 insns, 5 copies: the code of shape b059:01E00440 built at -O2 (draws n ring/cone emitters
   (0x48 bytes each): a quarter ring of up to 9 segments between an inner radius at height y+dy and an outer one at y,
   mirrored into four quadrants as quads; texture page from a 4-entry module table by e->type, STQ from the page
   rectangle (types 1-3) or func_00101EE0) */

/* OVL_CFLAGS: -O1,p -sdatathreshold 0 -relax_pointers */
/* OVL_WARM: compile warm (its (u32) cast is jal fptoui, func_001A23B0) */

/* shape b059:01E00440, 626 insns, 8 copies: draws n ring/cone emitters (0x48 bytes each): a quarter ring of up to 9
   segments between an inner radius at height y+dy and an outer one at y, mirrored into four quadrants as quads;
   texture page from a 4-entry module table by e->type, STQ from the page rectangle (types 1-3) or func_00101EE0 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b059_01E00440;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    f32 s, t;
    Xyz_b059_01E00440 xyz;
} Vtx_b059_01E00440;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b059_01E00440 v[4];
    u8 tail[0x20];
} Pkt_b059_01E00440;

typedef struct {
    s32 id;
    u8 sub;
    u8 pad5[3];
    s32 u, w, v, h;
} Tex_b059_01E00440;

typedef struct {
    Tex_b059_01E00440 e[4];
} Tab_b059_01E00440;

typedef struct {
    u8 b, g, r, a;
} Col_b059_01E00440;

typedef struct {
    u8 life;
    u8 pad1[6];
    u8 seg;
    u8 type;
    u8 b9;
    u8 bA;
    u8 padB;
    f32 scale;
    f32 base;
    f32 dy;
    f32 y;
    f32 vy;
    Col_b059_01E00440 c0;
    Col_b059_01E00440 c1;
    Vec4f pos;
    Vec4f rot;
} Emit_b059_01E00440;

extern Tab_b059_01E00440 D_01E05AF0_b176;

#pragma optimization_level 2

static s32 func_01E03160_b176(void *arg0, s32 ot, s32 n) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_0020BC00(void *, void *);
    extern void func_00101BA0(void *, void *);
    f32 mat2[16];
    f32 mat[16];
    Vec4f a[10];
    Vec4f b[10];
    Vec4f c[4];
    f32 depth[4];
    Tab_b059_01E00440 tab;
    Tex_b059_01E00440 td;
    Pkt_b059_01E00440 pkt __attribute__((aligned(8)));
    u8 bl[4];
    Emit_b059_01E00440 *e;
    s32 i;
    s32 j;
    s32 k;
    s32 nseg;
    s32 tex;
    f32 sn;
    f32 step;
    f32 r1;
    f32 r2;
    f32 cs;

    e = arg0;
    tab = D_01E05AF0_b176;
    for (i = 0; i < n; i++) {
        if (i != 0) {
            e++;
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        tex = func_00202BF0(tab.e[e->type].id, tab.e[e->type].sub);
        e->y += e->vy;
        func_00101BA0(e, &e->pos);
        func_0020EB40(mat);
        func_0020C940(mat2, NULL, &e->rot, &e->pos);
        func_0020BC00(mat, mat2);
        if (e->seg > 9) {
            nseg = 9;
        } else {
            nseg = e->seg;
        }
        step = 90.0f / nseg;
        r1 = e->scale * (e->y + e->dy) / e->base;
        r2 = e->scale * e->y / e->base;
        for (j = 0; j < nseg + 1; j++) {
            sn = func_001A6A88(3.1415927f * (step * j) / 180.0f);
            cs = func_001A6898(3.1415927f * (step * j) / 180.0f);
            a[j].x = r1 * cs;
            a[j].z = r1 * sn;
            a[j].y = e->y + e->dy;
            b[j].x = r2 * cs;
            b[j].z = r2 * sn;
            b[j].y = e->y;
        }
        ((Pkt_b059_01E00440 *)(s32)&pkt)->count = 0x34;
        ((Pkt_b059_01E00440 *)(s32)&pkt)->tag = 0xC;
        ((Pkt_b059_01E00440 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Pkt_b059_01E00440 *)(s32)&pkt)->pad = 0;
        pkt.v[0].r = pkt.v[1].r = e->c0.r;
        pkt.v[2].r = pkt.v[3].r = e->c1.r;
        pkt.v[0].g = pkt.v[1].g = e->c0.g;
        pkt.v[2].g = pkt.v[3].g = e->c1.g;
        pkt.v[0].b = pkt.v[1].b = e->c0.b;
        pkt.v[2].b = pkt.v[3].b = e->c1.b;
        pkt.v[0].q = pkt.v[1].q = pkt.v[2].q = pkt.v[3].q = 1.0f;
        if (e->life < 8) {
            pkt.v[0].a = pkt.v[1].a = e->life * (e->c0.a >> 3);
            pkt.v[2].a = pkt.v[3].a = e->life * (e->c1.a >> 3);
        } else {
            pkt.v[0].a = pkt.v[1].a = e->c0.a;
            pkt.v[2].a = pkt.v[3].a = e->c1.a;
        }
        c[0].y = c[1].y = a[0].y;
        c[2].y = c[3].y = b[0].y;
        for (j = 0; j < nseg; j++) {
            for (k = 0; k < 4; k++) {
                switch (k) {
                case 0:
                    c[0].x = a[j].x;
                    c[1].x = a[j + 1].x;
                    c[2].x = b[j].x;
                    c[3].x = b[j + 1].x;
                    c[0].z = a[j].z;
                    c[1].z = a[j + 1].z;
                    c[2].z = b[j].z;
                    c[3].z = b[j + 1].z;
                    break;
                case 1:
                    c[0].x = -a[j].x;
                    c[1].x = -a[j + 1].x;
                    c[2].x = -b[j].x;
                    c[3].x = -b[j + 1].x;
                    break;
                case 2:
                    c[0].z = -a[j].z;
                    c[1].z = -a[j + 1].z;
                    c[2].z = -b[j].z;
                    c[3].z = -b[j + 1].z;
                    break;
                case 3:
                    c[0].x = a[j].x;
                    c[1].x = a[j + 1].x;
                    c[2].x = b[j].x;
                    c[3].x = b[j + 1].x;
                    break;
                }
                if (func_00205440(&c[0], mat, &pkt.v[0].xyz, &depth[0]) != 0 &&
                    func_00205440(&c[1], mat, &pkt.v[1].xyz, &depth[1]) != 0 &&
                    func_00205440(&c[2], mat, &pkt.v[2].xyz, &depth[2]) != 0 &&
                    func_00205440(&c[3], mat, &pkt.v[3].xyz, &depth[3]) != 0) {
                    pkt.v[0].xyz.f = pkt.v[1].xyz.f = pkt.v[2].xyz.f = pkt.v[3].xyz.f = 0;
                    td = tab.e[e->type];
                    switch (e->type) {
                    case 1:
                    case 2:
                    case 3:
                        func_00208CB0(&pkt, 0xB | ((u64)e->b9 << 4) | ((u64)td.u << 14) | ((u64)td.v << 24) |
                                                ((u64)(td.h - 1) << 34));
                        td.u = 0;
                        td.w = e->bA;
                        pkt.v[0].q = 1.0f / depth[0];
                        pkt.v[1].q = 1.0f / depth[1];
                        pkt.v[2].q = 1.0f / depth[2];
                        pkt.v[3].q = 1.0f / depth[3];
                        pkt.v[0].s = td.u / 256.0f / depth[0];
                        pkt.v[0].t = td.v / 256.0f / depth[0];
                        pkt.v[1].s = td.w / 256.0f / depth[1];
                        pkt.v[1].t = td.v / 256.0f / depth[1];
                        pkt.v[2].s = td.u / 256.0f / depth[2];
                        pkt.v[2].t = td.h / 256.0f / depth[2];
                        pkt.v[3].s = td.w / 256.0f / depth[3];
                        pkt.v[3].t = td.h / 256.0f / depth[3];
                        func_00101C80(&td, bl);
                        func_002086D0(&pkt, (u64)bl[0] | ((u64)bl[1] << 2) | ((u64)bl[2] << 4) | ((u64)bl[3] << 6));
                        func_00208700(&pkt, (void *)tex, 1);
                        break;
                    default:
                        func_00101EE0(&pkt, &td, (void *)tex);
                        break;
                    }
                    func_002075F0((s32)&pkt, ot, (u32)((depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f));
                }
            }
        }
    }
    return 1;
}
#pragma optimization_level reset

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

INCLUDE_ASM("asm/nonmatchings/mod/b176", func_01E049A0_b176);

INCLUDE_ASM("asm/nonmatchings/mod/b176", func_01E04DB0_b176);

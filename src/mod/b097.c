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

static void func_01E00080_b097(Obj_b002_01E00080 *arg0) {
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

INCLUDE_ASM("asm/nonmatchings/mod/b097", func_01E00440_b097);

INCLUDE_ASM("asm/nonmatchings/mod/b097", func_01E01880_b097);

INCLUDE_ASM("asm/nonmatchings/mod/b097", func_01E025A0_b097);

INCLUDE_ASM("asm/nonmatchings/mod/b097", func_01E03260_b097);

INCLUDE_ASM("asm/nonmatchings/mod/b097", func_01E03A40_b097);

/* OVL_CFLAGS: -O1,p -sdatathreshold 0 -relax_pointers */

/* shape b198:01E05C30, 260 insns, 4 copies: moves n trail emitters (0x7C bytes each) and drops trail particles into the
   emitter's pool: one at the head (flag 1) or four along a spline through the last three positions. */

typedef struct {
    s32 n;
    f32 x[8];
    f32 y[8];
    f32 z[8];
    Vec4f out[28];
} Spline_b097_01E04900;

typedef struct {
    u8 r, g, b, a;
} C4_b097_01E04900;

typedef struct {
    u8 pad00[4];
    u8 flags;
    u8 b5;
    u8 pad06[2];
    u8 b8;
    u8 b9;
    u8 bA;
    u8 bB;
    u8 bC;
    u8 bD;
    u8 pad0E[2];
    s32 w10;
    f32 f14;
    f32 f18;
    f32 f1C;
    f32 f20;
    C4_b097_01E04900 col;
    Vec4f pos;
    u8 pad38[0x10];
    u8 x48[0x10];
} Part_b097_01E04900;

typedef struct {
    u8 life;
    u8 pad1;
    u8 max;
    u8 pad3;
    u8 flags;
    u8 follow;
    u8 pad6[2];
    Part_b097_01E04900 *list;
    s32 w0C;
    u8 b10;
    u8 b11;
    u8 b12;
    u8 b13;
    u8 b14;
    u8 b15;
    u8 b16;
    u8 pad17;
    f32 f18;
    f32 f1C;
    f32 f20;
    f32 f24;
    C4_b097_01E04900 col;
    Vec4f pos;
    Vec4f prev;
    Vec4f prev2;
    Vec4f vel;
    Vec4f off;
    Vec4f drift;
} Trail_b097_01E04900;

#pragma optimization_level 1

static s32 func_01E04900_b097(void *arg0, s32 arg1, s32 n) {
    extern s32 func_00101AF0(void *);
    extern void func_00101BA0(void *, void *);
    extern void func_00102550(void *);
    extern s32 func_00101C30(void *, s32, s32);
    extern void func_00101AD0(void *, s32, s32, s32);
    extern void func_00101940(void *, void *);
    extern f32 func_0020D0E0(void *);
    extern void func_0020D070(void *);
    Spline_b097_01E04900 sp;
    Vec4f tmp;
    Trail_b097_01E04900 *e;
    s32 i;
    s32 k;
    s32 cnt;
    s32 idx;
    f32 f;

    e = arg0;
    for (i = 0; i < n; i++) {
        if (i != 0) {
            e = (Trail_b097_01E04900 *)((u8 *)e + 0x8C);
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        if (e->life == e->max - 1) {
            continue;
        }
        e->pos.x += e->vel.x;
        e->pos.y += e->vel.y;
        e->pos.z += e->vel.z;
        func_00101BA0(e, &e->pos);
        if (e->follow != 0) {
            e->pos.x += e->off.x;
            e->pos.y += e->off.y;
            e->pos.z += e->off.z;
        }
        if (e->flags & 1) {
            sp.out[0] = e->pos;
            sp.out[1] = e->prev;
            cnt = 1;
        } else {
            sp.n = 3;
            sp.x[0] = e->pos.x;
            sp.y[0] = e->pos.y;
            sp.z[0] = e->pos.z;
            sp.x[1] = e->prev.x;
            sp.y[1] = e->prev.y;
            sp.z[1] = e->prev.z;
            sp.x[2] = e->prev2.x;
            sp.y[2] = e->prev2.y;
            sp.z[2] = e->prev2.z;
            func_00102550(&sp);
            cnt = 4;
        }
        for (k = 0; k < cnt; k++) {
            idx = func_00101C30(e->list, 0x58, e->b10);
            if (idx >= 0) {
                func_00101AD0(&e->list[idx], e->b11, 0, 0xFF);
                tmp.x = sp.out[k + 1].x - sp.out[k].x;
                tmp.y = sp.out[k + 1].y - sp.out[k].y;
                tmp.z = sp.out[k + 1].z - sp.out[k].z;
                f = func_0020D0E0(&tmp);
                if (f < 0.3f) {
                    tmp.x += e->drift.x;
                    tmp.y += e->drift.y;
                    tmp.z += e->drift.z;
                } else if (f > 1.0f) {
                    func_0020D070(&tmp);
                }
                e->list[idx].f14 = func_0020D0E0(&tmp);
                if (e->f18) {
                    e->list[idx].f14 *= e->f18;
                }
                e->list[idx].f18 = e->f1C;
                e->list[idx].flags = 0;
                if (e->flags & 2) {
                    e->list[idx].flags |= 4;
                    e->list[idx].bC = e->b16;
                }
                if (e->flags & 4) {
                    e->list[idx].flags |= 8;
                }
                e->list[idx].b5 = 0;
                e->list[idx].b8 = e->b12;
                e->list[idx].f1C = e->f20;
                e->list[idx].f20 = e->f24;
                e->list[idx].b9 = func_0019A5C8() >> 4;
                e->list[idx].bA = e->b13;
                e->list[idx].bB = e->b14;
                e->list[idx].bD = e->b15;
                e->list[idx].w10 = e->w0C;
                e->list[idx].col = e->col;
                e->list[idx].pos = sp.out[k];
                func_00101940(&tmp, e->list[idx].x48);
            }
        }
        e->prev2 = e->prev;
        e->prev = e->pos;
    }
    return 1;
}
#pragma optimization_level reset

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

extern Tab_b059_01E00440 D_01E07240_b097;

#pragma optimization_level 1

static s32 func_01E04FE0_b097(void *arg0, s32 ot, s32 n) {
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
    tab = D_01E07240_b097;
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

/* OVL_CFLAGS: -O1,p -sdatathreshold 0 -relax_pointers */
/* OVL_WARM */

typedef struct {
    f32 x, y, z, w;
} Vec_b097_01E059B0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b097_01E059B0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Col_b097_01E059B0;

typedef struct {
    u64 st;
    Xyz_b097_01E059B0 p;
} Vtx_b097_01E059B0;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Col_b097_01E059B0 c;
    Vtx_b097_01E059B0 v[4];
    u8 tail[0x20];
} Pkt_b097_01E059B0;

typedef struct {
    s32 id;
    u8 kind;
    u8 page;
    u8 pad06[0x12];
} Tex_b097_01E059B0;

typedef struct {
    u8 life;
    u8 pad01;
    u8 total;
    u8 pad03;
    u8 flags;
    u8 pad05[3];
    u8 page;
    u8 texkind;
    u8 frame;
    u8 shift;
    u8 b, g, r, a;
    f32 width;
    f32 grow;
    f32 gravity;
    f32 floor;
    f32 x, y, z;
    f32 vx, vy, vz;
    f32 ax, ay, az;
} Fx_b097_01E059B0;

#pragma optimization_level 1

static s32 func_01E059B0_b097(Fx_b097_01E059B0 *obj, s32 target, s32 n) {
    extern s32 func_00101AF0(void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_0020EB40(void *);
    extern void func_001020B0(void *, s32, s32);
    extern void func_00101D20(void *, void *, s32);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern s32 func_00101600(void *);
    extern f32 func_001018E0(f32, f32);
    extern void func_002075F0(void *, s32, s32);
    f32 m[16];
    Vec_b097_01E059B0 a;
    Tex_b097_01E059B0 tex;
    Pkt_b097_01E059B0 pkt __attribute__((aligned(8)));
    Xyz_b097_01E059B0 xy;
    f32 d;
    Fx_b097_01E059B0 *e;
    s32 age;
    s32 i;
    s32 fr;
    f32 w;
    s32 texture;

    e = obj;
    for (i = 0; i < n; i++) {
        if (i != 0) {
            e = (Fx_b097_01E059B0 *)((u8 *)e + 0x44);
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        if (e->flags & 4) {
            texture = func_00202BF0(5, e->texkind);
        } else {
            texture = func_00202BF0(4, 2);
        }
        e->vx += e->ax;
        e->vy += e->ay + e->gravity;
        e->vz += e->az;
        e->x += e->vx;
        e->y += e->vy;
        e->z += e->vz;
        e->width += e->grow;
        if (e->y < e->floor) {
            e->y = e->floor;
        }
        a.x = e->x;
        a.y = e->y;
        a.z = e->z;
        func_0020EB40(m);
        ((Pkt_b097_01E059B0 *)(s32)&pkt)->count = 0x24;
        ((Pkt_b097_01E059B0 *)(s32)&pkt)->tag = 9;
        ((Pkt_b097_01E059B0 *)(s32)&pkt)->regs = ((u64)4 << 32) | 0x24242421;
        ((Pkt_b097_01E059B0 *)(s32)&pkt)->pad = 0;
        pkt.c.r = e->r;
        pkt.c.g = e->g;
        pkt.c.b = e->b;
        pkt.c.q = 1.0f;
        age = e->total - e->life;
        fr = e->frame;
        if (e->flags & 8) {
            fr = ((age >> e->shift) & 3) + 2;
            if (age < 3) {
                fr = age;
            }
            if (e->life < 7) {
                fr = 7 - (e->life >> e->shift);
            }
        }
        tex.page = e->page;
        func_001020B0(&tex, fr, 0);
        func_00101D20(&pkt, &tex, texture);
        if (e->life < 16) {
            pkt.c.a = (e->a >> 4) * e->life;
        } else {
            pkt.c.a = e->a;
        }
        if (func_00205440(&a, m, &xy, &d) == 0) {
            continue;
        }
        if (func_00101600(&xy) == 0) {
            continue;
        }
        w = func_001018E0(e->width, d);
        pkt.v[0].p.z = pkt.v[1].p.z = pkt.v[2].p.z = pkt.v[3].p.z = xy.z;
        switch (e->flags & 0x30) {
        case 0x10:
            pkt.v[0].p.x = pkt.v[1].p.x = (u32)((f32)(u32)xy.x - w);
            pkt.v[2].p.x = pkt.v[3].p.x = (u32)((f32)(u32)xy.x + w);
            pkt.v[1].p.y = pkt.v[3].p.y = (u32)((f32)(u32)xy.y - w);
            pkt.v[0].p.y = pkt.v[2].p.y = (u32)((f32)(u32)xy.y + w);
            break;
        case 0x20:
            pkt.v[1].p.x = pkt.v[3].p.x = (u32)((f32)(u32)xy.x - w);
            pkt.v[0].p.x = pkt.v[2].p.x = (u32)((f32)(u32)xy.x + w);
            pkt.v[2].p.y = pkt.v[3].p.y = (u32)((f32)(u32)xy.y - w);
            pkt.v[0].p.y = pkt.v[1].p.y = (u32)((f32)(u32)xy.y + w);
            break;
        case 0x30:
            pkt.v[2].p.x = pkt.v[3].p.x = (u32)((f32)(u32)xy.x - w);
            pkt.v[0].p.x = pkt.v[1].p.x = (u32)((f32)(u32)xy.x + w);
            pkt.v[0].p.y = pkt.v[2].p.y = (u32)((f32)(u32)xy.y - w);
            pkt.v[1].p.y = pkt.v[3].p.y = (u32)((f32)(u32)xy.y + w);
            break;
        default:
            pkt.v[0].p.x = pkt.v[2].p.x = (u32)((f32)(u32)xy.x - w);
            pkt.v[1].p.x = pkt.v[3].p.x = (u32)((f32)(u32)xy.x + w);
            pkt.v[0].p.y = pkt.v[1].p.y = (u32)((f32)(u32)xy.y - w);
            pkt.v[2].p.y = pkt.v[3].p.y = (u32)((f32)(u32)xy.y + w);
            break;
        }
        func_002075F0(&pkt, target, (u32)d);
    }
    return 1;
}
#pragma optimization_level reset

INCLUDE_ASM("asm/nonmatchings/mod/b097", func_01E06310_b097);

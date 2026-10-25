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

static void func_01E00080_b241(Obj_b002_01E00080 *arg0) {
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

INCLUDE_ASM("asm/nonmatchings/mod/b241", func_01E00440_b241);

/* OVL_WARM */

#define ABS(x) ((x) >= 0 ? (x) : -(x))

/* OVL_CFLAGS: -O1,p -sdatathreshold 0 -relax_pointers */

/* shape b059:01E00E10, 941 insns, 11 copies: b024:01E02120 at -O1 (angle inline, step = 17.0f local, ABS macro): update and draw ribbon emitters (0x58 bytes each); every segment
   is projected straight into the packet's vertex slots and widened on screen */

typedef struct Uvs_b059_01E00E10 {
    s32 kind;
    u8 tex;
    u8 b5;
    u16 pad6;
    s32 u0, v0, u1, v1;
} Uvs_b059_01E00E10;

typedef struct Rib_b059_01E00E10 {
    u8 age;
    u8 b1;
    u8 life;
    u8 b3;
    u8 flags;
    u8 b5[3];
    u8 count;
    u8 k;
    u8 idx;
    u8 frame;
    u8 b5c;
    u8 div;
    u8 padE[2];
    u8 *pts;
    f32 scale;
    f32 f18;
    f32 width;
    f32 grow;
    u8 r, g, b, a;
    f32 pos[3];
    u8 pad34[4];
    f32 vel[3];
    u8 pad44[4];
    f32 rot[4];
} Rib_b059_01E00E10;

typedef struct Xyz_b059_01E00E10 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b059_01E00E10;

typedef struct Pk_b059_01E00E10 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    u64 st;
    Xyz_b059_01E00E10 v[4];
    u64 pad60[3];
} Pk_b059_01E00E10;

static inline void b059_01E00E10_tag(Pk_b059_01E00E10 *p, s32 size, s32 flags, u64 regs) {
    p->flags = flags;
    p->size = size;
    p->regs = regs;
    p->pad4 = 0;
}

#pragma optimization_level 1
typedef struct W_tbl_func_01E01160_b241 {
    Uvs_b059_01E00E10 v[4];
} W_tbl_func_01E01160_b241;

static s32 func_01E01160_b241(Rib_b059_01E00E10 *arg0, s32 id __attribute__((aligned(8))), s32 n) {
    extern s32 func_00205440();
    extern void func_00101BA0();
    extern void func_001020B0();
    extern void func_00101D20();
    extern void func_0020C940();
    extern void func_0020BC00();
    s32 sel;
    f32 ang;
    s32 dx;
    f32 step;
    f32 b;
    Rib_b059_01E00E10 *p = arg0;
    s32 i;
    f32 h1;
    s32 dy;
    s32 tex;
    u8 k;
    f32 w;
    f32 d;
    f32 a;
    f32 h0;
    s32 life;
    s32 j;

    f32 m2[4][4];
    f32 m[4][4];
    Vec4f t[2];
    Vec4f v;
    extern W_tbl_func_01E01160_b241 D_01E053A0_b241;
    W_tbl_func_01E01160_b241 tbl_w = D_01E053A0_b241;
    Uvs_b059_01E00E10 uvs;
    Pk_b059_01E00E10 pk;
    f32 depth[2];

    for (i = 0; i < n; i++) {
        if (i != 0) {
            p++;
        }
        if (func_00101AF0(p) == 0) {
            continue;
        }
        if (p->flags & 4) {
            tex = func_00202BF0(5, p->idx);
        } else {
            tex = func_00202BF0(tbl_w.v[p->idx].kind, tbl_w.v[p->idx].tex);
        }
        p->pos[0] += p->vel[0];
        p->pos[1] += p->vel[1];
        p->pos[2] += p->vel[2];
        func_00101BA0(p, p->pos);
        func_0020EB40(m);
        func_0020C940(m2, 0, p->rot, p->pos);
        func_0020BC00(m, m2);
        k = p->k;
        step = 17.0f;
        ang = 0.0f;
        life = p->life - p->age;
        b059_01E00E10_tag((Pk_b059_01E00E10 *)(u32)&pk, 9, 0x24, ((u64)4 << 32) | 0x24242421);
        pk.r = p->b;
        pk.g = p->g;
        pk.b = p->r;
        pk.q = 1.0f;
        if (p->flags & 4) {
            sel = p->frame;
            if (p->flags & 8) {
                sel = life & 7;
                if (life < 3) {
                    sel = life;
                }
                if (p->age < 4) {
                    sel = 7 - p->age;
                }
            }
            uvs.b5 = p->b5c;
            func_001020B0(&uvs, sel, 0);
            func_00101D20(&pk, &uvs, tex);
        } else {
            func_00101D20(&pk, &tbl_w.v[p->idx], tex);
        }
        if (p->age < 8) {
            pk.a = (p->a >> 3) * p->age;
        } else {
            pk.a = p->a;
        }
        for (j = 0; j < p->count; j++) {
            if (p->flags & 1) {
                v.x = p->scale * (f32)(p->pts[k] - p->pts[k + 1]) / 255.0f;
                v.y = p->scale * (f32)(p->pts[k + 2] - p->pts[k + 3]) / 255.0f;
                v.z = p->scale * (f32)(p->pts[k + 4] - p->pts[k + 5]) / 255.0f;
                k += 6;
            } else {
                ang += step;
                if (!(ang <= 360.0f)) {
                    ang -= 360.0f;
                }
                a = (f32)p->pts[k++] / 255.0f;
                b = p->f18 * (f32)p->pts[k++] / 255.0f;
                v.x = a * b * func_001A6898(3.1415927f * ang / 180.0f);
                v.z = a * b * func_001A6A88(3.1415927f * ang / 180.0f);
                v.y = a * p->scale;
            }
            w = p->width + p->grow * (f32)life;
            if (p->div > 1) {
                d = p->scale / (f32)p->div;
                w = w / (1.0f + func_0020D0E0(&v.x) / d);
            }
            t[0].x = v.x * (f32)life;
            t[0].y = v.y * (f32)life;
            t[0].z = v.z * (f32)life;
            if (func_00205440(&t[0], m, &pk.v[0], &depth[0]) == 0) {
                continue;
            }
            if (func_00101600(&pk.v[0]) == 0) {
                continue;
            }
            h0 = func_001018E0(w, depth[0]);
            if (p->flags & 2) {
                t[1].x = t[0].x + 4.0f * v.x;
                t[1].y = t[0].y + 4.0f * v.y;
                t[1].z = t[0].z + 4.0f * v.z;
                if (func_00205440(&t[1], m, &pk.v[2], &depth[1]) == 0) {
                    continue;
                }
                if (func_00101600(&pk.v[2]) == 0) {
                    continue;
                }
                h1 = func_001018E0(w, depth[1]);
                dy = ABS(pk.v[2].y - pk.v[0].y);
                dx = ABS(pk.v[2].x - pk.v[0].x);
                if (dy < dx) {
                    pk.v[1].x = pk.v[0].x;
                    pk.v[3].x = pk.v[2].x;
                    pk.v[1].y = (u32)(pk.v[0].y + h0);
                    pk.v[0].y = (u32)(pk.v[0].y - h0);
                    pk.v[3].y = (u32)(pk.v[2].y + h1);
                    pk.v[2].y = (u32)(pk.v[2].y - h1);
                } else {
                    pk.v[1].y = pk.v[0].y;
                    pk.v[3].y = pk.v[2].y;
                    pk.v[1].x = (u32)(pk.v[0].x + h0);
                    pk.v[0].x = (u32)(pk.v[0].x - h0);
                    pk.v[3].x = (u32)(pk.v[2].x + h1);
                    pk.v[2].x = (u32)(pk.v[2].x - h1);
                }
                pk.v[1].z = pk.v[0].z;
                pk.v[3].z = pk.v[2].z;
            } else {
                pk.v[1].x = (u32)(pk.v[0].x + h0);
                pk.v[1].y = (u32)(pk.v[0].y - h0);
                pk.v[2].x = (u32)(pk.v[0].x - h0);
                pk.v[2].y = (u32)(pk.v[0].y + h0);
                pk.v[3].x = (u32)(pk.v[0].x + h0);
                pk.v[3].y = (u32)(pk.v[0].y + h0);
                pk.v[0].x = (u32)(pk.v[0].x - h0);
                pk.v[0].y = (u32)(pk.v[0].y - h0);
                pk.v[1].z = pk.v[2].z = pk.v[3].z = pk.v[0].z;
            }
            pk.v[0].fog = pk.v[1].fog = pk.v[2].fog = pk.v[3].fog = 1;
            func_002075F0((s32)&pk, id, (u32)(depth[0]));
        }
    }
    return 1;
}
#pragma optimization_level reset

INCLUDE_ASM("asm/nonmatchings/mod/b241", func_01E02020_b241);

/* shape b241:01E02BB0, 322 insns: ShFx_Amp3, b241:01E030C0's trail emitters (0x64 bytes) riding between two model
   joints (b13 and b14, lerp by f2C): one particle at the head when b18 < 2, else b18 along a spline through the last
   three positions; each particle's speed is the length to the next point (y raised 0.8 when shorter than f1C) */

typedef struct {
    s32 n;
    f32 x[8];
    f32 y[8];
    f32 z[8];
    Vec4f out[28];
} Spline_b241_01E02BB0;

typedef struct {
    u8 r, g, b, a;
} C4_b241_01E02BB0;

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
    u8 pad0D[3];
    s32 w10;
    f32 f14;
    f32 f18;
    f32 f1C;
    C4_b241_01E02BB0 col;
    u8 x24[0x10];
    f32 x;
    f32 y;
    f32 z;
} Part_b241_01E02BB0;

typedef struct {
    u8 life;
    u8 pad1;
    u8 max;
    u8 pad3;
    u8 flags;
    u8 b5;
    u8 joint;
    u8 pad7;
    Part_b241_01E02BB0 *list;
    s32 w0C;
    u8 b10;
    u8 b11;
    u8 b12;
    u8 j0;
    u8 j1;
    u8 b15;
    u8 b16;
    u8 b17;
    u8 cnt;
    u8 pad19[3];
    f32 minlen;
    f32 f20;
    f32 f24;
    f32 f28;
    f32 lerp;
    C4_b241_01E02BB0 col;
    Vec4f pos;
    Vec4f prev;
    Vec4f prev2;
} Amp_b241_01E02BB0;

#pragma optimization_level 1

static s32 func_01E02BB0_b241(void *arg0, s32 arg1, s32 n) {
    extern s32 func_00101AF0(void *);
    extern void func_00101BA0(void *, void *);
    extern void func_00102550(void *);
    extern s32 func_00101C30(void *, s32, s32);
    extern void func_00101AD0(void *, s32, s32, s32);
    extern void func_00101940(void *, void *);
    extern f32 func_0020D0E0(void *);
    Spline_b241_01E02BB0 sp;
    Vec4f d;
    Vec4f a;
    Vec4f b;
    Amp_b241_01E02BB0 *e;
    s32 i;
    s32 k;
    s32 cnt;
    s32 idx;

    e = arg0;
    for (i = 0; i < n; i++) {
        if (i != 0) {
            e = (Amp_b241_01E02BB0 *)((u8 *)e + 0x64);
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        if (e->life == e->max - 1) {
            continue;
        }
        e->b5 = 1;
        e->joint = e->j0;
        func_00101BA0(e, &a);
        e->joint = e->j1;
        func_00101BA0(e, &b);
        e->pos.x = b.x + e->lerp * (a.x - b.x);
        e->pos.y = b.y + e->lerp * (a.y - b.y);
        e->pos.z = b.z + e->lerp * (a.z - b.z);
        if (e->cnt < 2) {
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
            cnt = e->cnt;
        }
        for (k = 0; k < cnt; k++) {
            idx = func_00101C30(e->list, 0x40, e->b10);
            if (idx >= 0) {
                func_00101AD0(&e->list[idx], e->b11, 0, 0xFF);
                d.x = sp.out[k + 1].x - sp.out[k].x;
                d.y = sp.out[k + 1].y - sp.out[k].y;
                d.z = sp.out[k + 1].z - sp.out[k].z;
                if (func_0020D0E0(&d) < e->minlen) {
                    d.y += 0.8f;
                }
                e->list[idx].f14 = func_0020D0E0(&d);
                if (e->f20) {
                    e->list[idx].f14 *= e->f20;
                }
                e->list[idx].f18 = e->f24;
                e->list[idx].flags = 0;
                e->list[idx].b5 = 0;
                e->list[idx].b8 = e->b12;
                e->list[idx].f1C = e->f28;
                e->list[idx].b9 = func_0019A5C8() >> 4;
                e->list[idx].bA = e->b15;
                e->list[idx].bB = e->b16;
                e->list[idx].bC = e->b17;
                e->list[idx].w10 = e->w0C;
                e->list[idx].col = e->col;
                e->list[idx].x = sp.out[k].x;
                e->list[idx].y = sp.out[k].y;
                e->list[idx].z = sp.out[k].z;
                func_00101940(&d, e->list[idx].x24);
            }
        }
        e->prev2 = e->prev;
        e->prev = e->pos;
    }
    return 1;
}

#pragma optimization_level reset

/* shape b241:01E030C0, 304 insns: ShFx_Amp4, b198:01E05C30's trail emitters (0x70 bytes, 0x40-byte particles) with
   gravity (+0x28 into vel.y) and no follow: one particle at the head when b16 < 2, else b16 along a spline through the
   last three positions; each particle's speed is the length to the next point (or 0.8 up when flag 1), times f18 */

typedef struct {
    s32 n;
    f32 x[8];
    f32 y[8];
    f32 z[8];
    Vec4f out[28];
} Spline_b241_01E030C0;

typedef struct {
    u8 r, g, b, a;
} C4_b241_01E030C0;

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
    u8 pad0D[3];
    s32 w10;
    f32 f14;
    f32 f18;
    f32 f1C;
    C4_b241_01E030C0 col;
    u8 x24[0x10];
    f32 x;
    f32 y;
    f32 z;
} Part_b241_01E030C0;

typedef struct {
    u8 life;
    u8 pad1;
    u8 max;
    u8 pad3;
    u8 flags;
    u8 pad5[3];
    Part_b241_01E030C0 *list;
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
    f32 grav;
    C4_b241_01E030C0 col;
    Vec4f pos;
    Vec4f prev;
    Vec4f prev2;
    Vec4f vel;
} Amp_b241_01E030C0;

#pragma optimization_level 1

static s32 func_01E030C0_b241(void *arg0, s32 arg1, s32 n) {
    extern s32 func_00101AF0(void *);
    extern void func_00102550(void *);
    extern s32 func_00101C30(void *, s32, s32);
    extern void func_00101AD0(void *, s32, s32, s32);
    extern void func_00101940(void *, void *);
    extern f32 func_0020D0E0(void *);
    Spline_b241_01E030C0 sp;
    Vec4f d;
    Amp_b241_01E030C0 *e;
    s32 i;
    s32 k;
    s32 cnt;
    s32 idx;

    e = arg0;
    for (i = 0; i < n; i++) {
        if (i != 0) {
            e = (Amp_b241_01E030C0 *)((u8 *)e + 0x70);
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        if (e->life == e->max - 1) {
            continue;
        }
        e->vel.y += e->grav;
        e->pos.x += e->vel.x;
        e->pos.y += e->vel.y;
        e->pos.z += e->vel.z;
        if (e->b16 < 2) {
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
            cnt = e->b16;
        }
        for (k = 0; k < cnt; k++) {
            idx = func_00101C30(e->list, 0x40, e->b10);
            if (idx >= 0) {
                func_00101AD0(&e->list[idx], e->b11, 0, 0xFF);
                if (e->flags & 1) {
                    d.x = 0.0f;
                    d.y = 0.8f;
                    d.z = 0.0f;
                } else {
                    d.x = sp.out[k + 1].x - sp.out[k].x;
                    d.y = sp.out[k + 1].y - sp.out[k].y;
                    d.z = sp.out[k + 1].z - sp.out[k].z;
                }
                e->list[idx].f14 = func_0020D0E0(&d);
                if (e->f18) {
                    e->list[idx].f14 *= e->f18;
                }
                e->list[idx].f18 = e->f1C;
                e->list[idx].flags = 0;
                if (e->flags & 0x40) {
                    e->list[idx].flags = 0x40;
                }
                e->list[idx].b5 = 0;
                e->list[idx].b8 = e->b12;
                e->list[idx].f1C = e->f20;
                e->list[idx].b9 = func_0019A5C8() >> 4;
                e->list[idx].bA = e->b13;
                e->list[idx].bB = e->b14;
                e->list[idx].bC = e->b15;
                e->list[idx].w10 = e->w0C;
                e->list[idx].col = e->col;
                e->list[idx].x = sp.out[k].x;
                e->list[idx].y = sp.out[k].y;
                e->list[idx].z = sp.out[k].z;
                func_00101940(&d, e->list[idx].x24);
            }
        }
        e->prev2 = e->prev;
        e->prev = e->pos;
    }
    return 1;
}

#pragma optimization_level reset

INCLUDE_ASM("asm/nonmatchings/mod/b241", func_01E03580_b241);

INCLUDE_ASM("asm/nonmatchings/mod/b241", func_01E04030_b241);

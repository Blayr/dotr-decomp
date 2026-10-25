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

/* OVL_WARM */

/* OVL_CFLAGS: -O2,p -sdatathreshold 0 -relax_pointers */

/* shape b024:01E02120, 875 insns, 51 copies: update and draw ribbon emitters (0x58 bytes each); every segment
   is projected straight into the packet's vertex slots and widened on screen */

typedef struct Uvs_b024_01E02120 {
    s32 kind;
    u8 tex;
    u8 b5;
    u16 pad6;
    s32 u0, v0, u1, v1;
} Uvs_b024_01E02120;

typedef struct Rib_b024_01E02120 {
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
} Rib_b024_01E02120;

typedef struct Xyz_b024_01E02120 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b024_01E02120;

typedef struct Pk_b024_01E02120 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    u64 st;
    Xyz_b024_01E02120 v[4];
    u64 pad60[3];
} Pk_b024_01E02120;

static inline void b024_01E02120_tag(Pk_b024_01E02120 *p, s32 size, s32 flags, u64 regs) {
    p->flags = flags;
    p->size = size;
    p->regs = regs;
    p->pad4 = 0;
}

#pragma optimization_level 2
typedef struct W_tbl_func_01E00410_b162 {
    Uvs_b024_01E02120 v[4];
} W_tbl_func_01E00410_b162;

static s32 func_01E00410_b162(Rib_b024_01E02120 *arg0, s32 id __attribute__((aligned(8))), s32 n) {
    extern s32 func_00205440();
    extern void func_00101BA0();
    extern void func_001020B0();
    extern void func_00101D20();
    extern void func_0020C940();
    extern void func_0020BC00();
    s32 sel;
    f32 ang;
    s32 dx;
    f32 w;
    f32 b;
    Rib_b024_01E02120 *p = arg0;
    s32 i;
    f32 h1;
    s32 dy;
    u8 k;
    s32 tex;
    s32 life;
    f32 rad;
    f32 d;
    f32 a;
    f32 h0;
    s32 j;

    f32 m2[4][4];
    f32 m[4][4];
    Vec4f t[2];
    Vec4f v;
    extern W_tbl_func_01E00410_b162 D_01E05080_b162;
    W_tbl_func_01E00410_b162 tbl_w = D_01E05080_b162;
    Uvs_b024_01E02120 uvs;
    Pk_b024_01E02120 pk;
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
        ang = 0.0f;
        life = p->life - p->age;
        b024_01E02120_tag((Pk_b024_01E02120 *)(u32)&pk, 9, 0x24, ((u64)4 << 32) | 0x24242421);
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
                ang += 17.0f;
                if (!(ang <= 360.0f)) {
                    ang -= 360.0f;
                }
                a = (f32)p->pts[k++] / 255.0f;
                b = p->f18 * (f32)p->pts[k++] / 255.0f;
                rad = 3.1415927f * ang / 180.0f;
                v.x = a * b * func_001A6898(rad);
                v.z = a * b * func_001A6A88(rad);
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
                dy = pk.v[2].y - pk.v[0].y;
                dy = dy >= 0 ? dy : -dy;
                dx = pk.v[2].x - pk.v[0].x;
                dx = dx >= 0 ? dx : -dx;
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

INCLUDE_ASM("asm/nonmatchings/mod/b162", func_01E011C0_b162);

INCLUDE_ASM("asm/nonmatchings/mod/b162", func_01E01BD0_b162);

/* OVL_CFLAGS: -O2,p -sdatathreshold 0 -relax_pointers */
/* OVL_WARM: compile warm (its (u32) cast is jal fptoui, func_001A23B0) */

/* shape b104:01E02ED0, 359 insns: draws n streak emitters (0x50 bytes each): a sprite from the emitter's position
   to position + dir * (life - age), turned by its rotation, widened on screen sideways or up (flags & 3: 1 up,
   2 sideways, else by the streak's slope); alpha fades in over the first 8 ticks. */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b104_01E02ED0;

typedef struct {
    u64 uv;
    Xyz_b104_01E02ED0 xyz;
} Vtx_b104_01E02ED0;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Vtx_b104_01E02ED0 v[4];
    u8 tail[0x20];
} Pkt_b104_01E02ED0;

typedef struct {
    s32 kind;
    u8 tex;
    u8 b5;
    u16 pad6;
    s32 u0, v0, u1, v1;
} Uvs_b104_01E02ED0;

typedef struct {
    u8 age;
    u8 pad1;
    u8 life;
    u8 pad3;
    u8 flags;
    u8 pad5[3];
    f32 width;
    u8 b, g, r, a;
    Vec4f pos;
    Vec4f dir;
    Vec4f rot;
    u8 pad40[0x10];
} Streak_b104_01E02ED0;

#pragma optimization_level 2

static s32 func_01E02750_b162(Streak_b104_01E02ED0 *arg0, s32 ot, s32 n) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_00101BA0(void *, void *);
    extern void func_00101D20(void *, void *, s32);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020BC00(void *, void *);
    Streak_b104_01E02ED0 *e = arg0;
    s32 tex __attribute__((aligned(16)));
    s32 i;
    s32 h;
    s32 k;
    s32 dx;
    s32 dy;
    f32 l;
    f32 w;
    f32 w0;
    f32 w1;
    f32 m2[16];
    f32 m[16];
    Vec4f p[2];
    Xyz_b104_01E02ED0 xy[2];
    extern Uvs_b104_01E02ED0 D_01E05120_b162;
    Uvs_b104_01E02ED0 tbl = D_01E05120_b162;
    f32 dep[2] __attribute__((aligned(16)));
    Pkt_b104_01E02ED0 pkt __attribute__((aligned(8)));

    tex = func_00202BF0(tbl.kind, tbl.tex);
    for (i = 0; i < n; i++) {
        if (i != 0) {
            e++;
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        func_00101BA0(e, &e->pos);
        func_0020EB40(m);
        func_0020C940(m2, NULL, &e->rot, &e->pos);
        func_0020BC00(m, m2);
        ((Pkt_b104_01E02ED0 *)(s32)&pkt)->count = 0x24;
        ((Pkt_b104_01E02ED0 *)(s32)&pkt)->tag = 9;
        ((Pkt_b104_01E02ED0 *)(s32)&pkt)->regs = ((u64)4 << 32) | 0x24242421;
        ((Pkt_b104_01E02ED0 *)(s32)&pkt)->pad = 0;
        pkt.r = e->r;
        pkt.g = e->g;
        pkt.b = e->b;
        pkt.q = 1.0f;
        func_00101D20(&pkt, &tbl, tex);
        if (e->age < 8) {
            pkt.a = (e->a >> 3) * e->age;
        } else {
            pkt.a = e->a;
        }
        k = e->life - e->age;
        p[0].z = 0.0f;
        p[0].y = 0.0f;
        p[0].x = 0.0f;
        l = k;
        p[1].x = e->dir.x * l;
        p[1].y = e->dir.y * l;
        p[1].z = e->dir.z * l;
        if (func_00205440(&p[0], m, &xy[0], &dep[0]) == 0 || func_00101600(&xy[0]) == 0 ||
            func_00205440(&p[1], m, &xy[1], &dep[1]) == 0 || func_00101600(&xy[1]) == 0) {
            continue;
        }
        w = e->width;
        w0 = w / (dep[0] / 256.0f);
        w1 = w / (dep[1] / 256.0f);
        pkt.v[0].xyz.z = pkt.v[2].xyz.z = xy[1].z;
        pkt.v[1].xyz.z = pkt.v[3].xyz.z = xy[0].z;
        switch (e->flags & 3) {
        case 1:
            h = 0;
            break;
        case 2:
            h = 1;
            break;
        default:
            dy = xy[0].y - xy[1].y;
            dy = dy >= 0 ? dy : -dy;
            dx = xy[0].x - xy[1].x;
            dx = dx >= 0 ? dx : -dx;
            h = dy < dx;
            break;
        }
        if (h != 0) {
            pkt.v[0].xyz.y = (u32)((f32)(u32)xy[1].y - w1);
            pkt.v[1].xyz.y = (u32)((f32)(u32)xy[0].y - w0);
            pkt.v[2].xyz.y = xy[1].y;
            pkt.v[3].xyz.y = xy[0].y;
            pkt.v[0].xyz.x = pkt.v[2].xyz.x = xy[1].x;
            pkt.v[1].xyz.x = pkt.v[3].xyz.x = xy[0].x;
            func_002075F0(&pkt, ot, 0);
        } else {
            pkt.v[0].xyz.x = (u32)((f32)(u32)xy[1].x - w1);
            pkt.v[1].xyz.x = (u32)((f32)(u32)xy[0].x - w0);
            pkt.v[2].xyz.x = xy[1].x;
            pkt.v[3].xyz.x = xy[0].x;
            pkt.v[0].xyz.y = pkt.v[2].xyz.y = xy[1].y;
            pkt.v[1].xyz.y = pkt.v[3].xyz.y = xy[0].y;
            func_002075F0(&pkt, ot, 0);
        }
    }
    return 1;
}
#pragma optimization_level reset

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

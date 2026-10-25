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

static void func_01E00080_b033(Obj_b010_01E00080 *o) {
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
typedef struct W_tbl_func_01E00410_b033 {
    Uvs_b024_01E02120 v[4];
} W_tbl_func_01E00410_b033;

static s32 func_01E00410_b033(Rib_b024_01E02120 *arg0, s32 id __attribute__((aligned(8))), s32 n) {
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
    extern W_tbl_func_01E00410_b033 D_01E06600_b033;
    W_tbl_func_01E00410_b033 tbl_w = D_01E06600_b033;
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

INCLUDE_ASM("asm/nonmatchings/mod/b033", func_01E011C0_b033);

/* OVL_CFLAGS: -O2,p -sdatathreshold 0 -relax_pointers */

/* shape b033:01E01CD0, 203 insns (-O2,p): steps n emitters (0x38 bytes each): a live one moves by its velocity
   and, unless flags 0 & 3 say it is paused, takes a free particle (0x3C bytes) from its pool, copies its settings,
   colour and velocity into it, snaps to its anchor when 0x5 is set, and places it at a random spread (+-0x14/2
   hundredths) around itself (flag 2: the spread alone) */

typedef struct {
    f32 x, y, z;
} V3_b033_01E01CD0;

typedef struct {
    u8 r, g, b, a;
} Col_b033_01E01CD0;

typedef struct {
    u8 pad0[4];
    u8 b4;
    u8 b5;
    u8 pad6[2];
    u8 b8;
    u8 b9;
    u8 padA;
    u8 bB;
    u8 bC;
    u8 bD;
    u8 padE[2];
    f32 f10;
    Col_b033_01E01CD0 col;
    f32 a[3];
    f32 b[3];
    V3_b033_01E01CD0 vel;
} Part_b033_01E01CD0;

typedef struct {
    u8 b0;
    u8 pad1[2];
    u8 b3;
    u8 b4;
    u8 b5;
    u8 b6;
    u8 pad7;
    Part_b033_01E01CD0 *pool;
    u8 kind;
    u8 bD;
    u8 bE;
    u8 bF;
    u8 b10;
    u8 b11;
    u8 pad12[2];
    s32 spread;
    f32 f18;
    Col_b033_01E01CD0 col;
    V3_b033_01E01CD0 pos;
    V3_b033_01E01CD0 vel;
} Emit_b033_01E01CD0;

#pragma optimization_level 2

static s32 func_01E01CD0_b033(Emit_b033_01E01CD0 *arg0, s32 arg1, s32 n) {
    extern s32 func_00101AF0(void *);
    extern s32 func_00101C30(void *, s32, s32);
    extern void func_00101AD0(void *, u8, s32, s32);
    extern void func_00101BA0(void *, f32 *);
    f32 v[4];
    Emit_b033_01E01CD0 *e = arg0;
    Part_b033_01E01CD0 *pt;
    s32 i;
    s32 k;
    f32 dx;
    f32 dy;
    f32 dz;

    for (i = 0; i < n; i++) {
        if (i != 0) {
            e++;
        }
        if (func_00101AF0(e) != 0) {
            e->pos.x += e->vel.x;
            e->pos.y += e->vel.y;
            e->pos.z += e->vel.z;
            if (!(e->b0 & e->b3)) {
                k = func_00101C30(e->pool, 0x3C, e->kind);
                if (k >= 0) {
                    pt = &e->pool[k];
                    func_00101AD0(pt, e->b11, 0, 0xFF);
                    pt->b5 = e->b5;
                    pt->b4 = e->b4;
                    pt->b9 = e->b6;
                    pt->b8 = e->bD;
                    pt->bB = e->bE;
                    pt->bC = e->bF;
                    pt->bD = e->b10;
                    pt->f10 = e->f18;
                    pt->col = e->col;
                    pt->vel = e->vel;
                    if (e->b5 != 0) {
                        func_00101BA0(e, v);
                        e->pos.x = v[0];
                        e->pos.y = v[1];
                        e->pos.z = v[2];
                    }
                    dx = (f32)((func_0019A5C8() >> 4) % e->spread - (e->spread >> 1)) / 100.0f;
                    dy = (f32)((func_0019A5C8() >> 4) % e->spread - (e->spread >> 1)) / 100.0f;
                    dz = (f32)((func_0019A5C8() >> 4) % e->spread - (e->spread >> 1)) / 100.0f;
                    if (e->b4 & 2) {
                        pt->a[0] = dx;
                        pt->a[1] = dy;
                        pt->a[2] = dz;
                    } else {
                        pt->a[0] = e->pos.x + dx;
                        pt->a[1] = e->pos.y + dy;
                        pt->a[2] = e->pos.z + dz;
                        pt->b[0] = e->pos.x - dx;
                        pt->b[1] = e->pos.y - dy;
                        pt->b[2] = e->pos.z - dz;
                    }
                }
            }
        }
    }
    return 1;
}
#pragma optimization_level reset

INCLUDE_ASM("asm/nonmatchings/mod/b033", func_01E02000_b033);

INCLUDE_ASM("asm/nonmatchings/mod/b033", func_01E02B80_b033);

/* OVL_WARM */

/* OVL_CFLAGS: -O2,p -sdatathreshold 0 -relax_pointers */

/* shape b033:01E03590, 674 insns: update and draw a pool of jittering particles (0x3C bytes each): move, every
   (mask+1) ticks re-follow the owner and pick a new random offset, frame from the tick (fade-in frames while
   young), project, then one textured sprite whose corners (rounded) follow the flip bits */

typedef struct Part_b033_01E03590 {
    u8 age;
    u8 b1;
    u8 life;
    u8 mask;
    u8 flags;
    u8 follow;
    u8 b6[2];
    u8 tex;
    u8 b9;
    u8 bA;
    u8 bB;
    u8 r, g, b, a;
    f32 size;
    s32 range;
    f32 pos[3];
    f32 vel[3];
    f32 off[3];
} Part_b033_01E03590;

typedef struct Xyz_b033_01E03590 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b033_01E03590;

typedef struct Pk_b033_01E03590 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    u64 st;
    Xyz_b033_01E03590 v[4];
    u64 pad60[3];
} Pk_b033_01E03590;

typedef struct Buf_b033_01E03590 {
    u64 tag;
    Pk_b033_01E03590 pk;
} Buf_b033_01E03590;

typedef struct Uvs_b033_01E03590 {
    u8 b0[5];
    u8 b5;
    u8 pad6[0x12];
} Uvs_b033_01E03590;

typedef struct Scr_b033_01E03590 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Scr_b033_01E03590;

static inline void b033_01E03590_tag(Pk_b033_01E03590 *p, s32 size, s32 flags, u64 regs) {
    p->flags = flags;
    p->size = size;
    p->regs = regs;
    p->pad4 = 0;
}

#pragma optimization_level 2

static s32 func_01E03590_b033(Part_b033_01E03590 *arg0, s32 id, s32 n) {
    extern void func_001020B0();
    extern void func_00101D20();
    extern s32 func_00205440();
    extern void func_00101BA0();
    Part_b033_01E03590 *p = arg0;
    s32 i;
    s32 tex;
    s32 tick;
    s32 frame;
    s32 r;
    f32 half;
    u32 c;

    f32 m[4][4];
    Vec4f pos;
    Vec4f tmp;
    Uvs_b033_01E03590 uvs;
    Pk_b033_01E03590 pk __attribute__((aligned(8)));
    Scr_b033_01E03590 scr;
    f32 depth;

    for (i = 0; i < n; i++) {
        if (i != 0) {
            p++;
        }
        if (func_00101AF0(p) == 0) {
            continue;
        }
        tex = func_00202BF0(5, p->tex);
        p->pos[0] += p->vel[0];
        p->pos[1] += p->vel[1];
        p->pos[2] += p->vel[2];
        tick = p->mask & (p->life - p->age);
        if (tick == 0 || p->life - 1 == p->age) {
            if (p->follow != 0) {
                func_00101BA0(p, &tmp);
                p->pos[0] = tmp.x;
                p->pos[1] = tmp.y;
                p->pos[2] = tmp.z;
            }
            r = p->range;
            p->off[0] = ((func_0019A5C8() >> 4) % r - (r >> 1)) / 100.0f;
            r = p->range;
            p->off[1] = ((func_0019A5C8() >> 4) % r - (r >> 1)) / 100.0f;
            r = p->range;
            p->off[2] = ((func_0019A5C8() >> 4) % r - (r >> 1)) / 100.0f;
        }
        pos.x = p->pos[0] + p->off[0];
        pos.y = p->pos[1] + p->off[1];
        pos.z = p->pos[2] + p->off[2];
        func_0020EB40(m);
        ((Pk_b033_01E03590 *)(u32)&pk)->flags = 0x24;
        ((Pk_b033_01E03590 *)(u32)&pk)->size = 9;
        ((Pk_b033_01E03590 *)(u32)&pk)->regs = ((u64)4 << 32) | 0x24242421;
        ((Pk_b033_01E03590 *)(u32)&pk)->pad4 = 0;
        pk.r = p->b;
        pk.g = p->g;
        pk.b = p->r;
        pk.q = 1.0f;
        frame = tick & 7;
        if (p->age < 4) {
            frame = 7 - p->age;
        }
        if ((p->flags & 1) && frame == 0) {
            p->flags = (p->flags & 0xC7) | (((func_0019A5C8() >> 4) & 3) << 4);
        }
        uvs.b5 = p->bA;
        func_001020B0(&uvs, frame, 0);
        func_00101D20(&pk, &uvs, tex);
        pk.a = p->a;
        if (!(p->flags & 0x40) && p->age < 8) {
            pk.a = (p->a >> 3) * p->age;
        }
        if (func_00205440(&pos, m, &scr, &depth) == 0) {
            continue;
        }
        if (func_00101600(&scr) == 0) {
            continue;
        }
        half = func_001018E0(p->size, depth);
        if (p->flags & 0x80) {
            pk.v[0].z = pk.v[1].z = pk.v[2].z = pk.v[3].z = 0xFFFFFE;
        } else {
            pk.v[0].z = pk.v[1].z = pk.v[2].z = pk.v[3].z = scr.z;
        }
        switch (p->flags & 0x30) {
        case 0x10:
            c = scr.x;
            pk.v[0].x = pk.v[1].x = (u32)(c - half);
            pk.v[2].x = pk.v[3].x = (u32)(c + half);
            c = scr.y;
            pk.v[1].y = pk.v[3].y = (u32)(c - half);
            pk.v[0].y = pk.v[2].y = (u32)(c + half);
            break;
        case 0x20:
            c = scr.x;
            pk.v[1].x = pk.v[3].x = (u32)(c - half);
            pk.v[0].x = pk.v[2].x = (u32)(c + half);
            c = scr.y;
            pk.v[2].y = pk.v[3].y = (u32)(c - half);
            pk.v[0].y = pk.v[1].y = (u32)(c + half);
            break;
        case 0x30:
            c = scr.x;
            pk.v[2].x = pk.v[3].x = (u32)(c - half);
            pk.v[0].x = pk.v[1].x = (u32)(c + half);
            c = scr.y;
            pk.v[0].y = pk.v[2].y = (u32)(c - half);
            pk.v[1].y = pk.v[3].y = (u32)(c + half);
            break;
        default:
            c = scr.x;
            pk.v[0].x = pk.v[2].x = (u32)(c - half);
            pk.v[1].x = pk.v[3].x = (u32)(c + half);
            c = scr.y;
            pk.v[0].y = pk.v[1].y = (u32)(c - half);
            pk.v[2].y = pk.v[3].y = (u32)(c + half);
            break;
        }
        func_002075F0((s32)&pk, id, 0);
    }
    return 1;
}
#pragma optimization_level reset

INCLUDE_ASM("asm/nonmatchings/mod/b033", func_01E04020_b033);

/* shape b033:01E04F60 (b033_setVolt), 323 insns, 1 copy (-O2,p): with a flag set, four bolts are taken from the
   emitter pool (stopping when it runs out), each between two of the unit's five joints: bolt 0 from joint 0 to 1, bolt
   1 from joint 1 towards it with a random spread scaled by how far the gap is from the range, bolts 2 and 3 from joint
   2 to joints 3 and 4; then the five joints are picked again (joint 1 fixed, the rest random within the model) */

typedef struct {
    u8 b0[4];
    u8 b4;
    u8 b5;
    u8 b6[2];
    u8 kind;
    u8 b9[2];
    u8 bB;
    u8 bC;
    u8 bD;
    u8 bE[2];
    f32 size;
    u8 col[4];
    f32 pos[3];
    f32 tgt[3];
    f32 off[3];
} Emit_b033_01E04F60;

typedef struct {
    u8 pad0[8];
    s32 unit;
    s32 joint[5];
    u8 pad20[0x180];
    Emit_b033_01E04F60 pool[100];
    u8 pad[0x1C88 - 0x1A0 - 100 * 0x3C];
    f32 range;
} Volt_b033_01E04F60;

#pragma optimization_level 2

static void func_01E04F60_b033(Volt_b033_01E04F60 *g, s32 on) {
    extern s32 func_00101C30(void *, s32, s32);
    extern void func_00101AD0(void *, s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern f32 func_0020D0E0(void *);
    extern s32 func_001F54E0(s32);
    extern s32 func_001F5560(s32, s32, s32);
    Vec4f p[5];
    Vec4f d;
    f32 f;
    s32 i;
    s32 k;
    s32 j;

    while (on != 0) {
        for (i = 0; i < 4; i++) {
            k = func_00101C30(g->pool, 0x3C, 40);
            if (k < 0) {
                break;
            }
            for (j = 0; j < 5; j++) {
                func_001F5620(g->unit, g->joint[j], &p[j]);
            }
            func_00101AD0(&g->pool[k], 12, 0, 0xFF);
            g->pool[k].b5 = 0;
            g->pool[k].b4 = 0;
            g->pool[k].bB = 0;
            g->pool[k].bC = 0;
            g->pool[k].col[0] = 0x80;
            g->pool[k].col[1] = 0x80;
            g->pool[k].col[2] = 0x80;
            g->pool[k].col[3] = 0x80;
            g->pool[k].off[2] = 0.0f;
            g->pool[k].off[1] = 0.0f;
            g->pool[k].off[0] = 0.0f;
            switch (i) {
            case 0:
                g->pool[k].kind = 8;
                g->pool[k].size = 0.8f;
                g->pool[k].bD = 3;
                g->pool[k].pos[0] = p[0].x;
                g->pool[k].pos[1] = p[0].y;
                g->pool[k].pos[2] = p[0].z;
                g->pool[k].tgt[0] = p[1].x;
                g->pool[k].tgt[1] = p[1].y;
                g->pool[k].tgt[2] = p[1].z;
                break;
            case 1:
                g->pool[k].kind = 6;
                g->pool[k].size = 1.2f;
                g->pool[k].bD = 4;
                g->pool[k].pos[0] = p[1].x;
                g->pool[k].pos[1] = p[1].y;
                g->pool[k].pos[2] = p[1].z;
                d.x = p[1].x - p[0].x;
                d.y = p[1].y - p[0].y;
                d.z = p[1].z - p[0].z;
                f = 200.0f * (g->range - func_0020D0E0(&d) >= 0.0f ? g->range - func_0020D0E0(&d)
                                                                    : -(g->range - func_0020D0E0(&d)));
                g->pool[k].tgt[0] = p[1].x + ((func_0019A5C8() >> 4) % (s32)f - ((s32)f >> 1)) / 100.0f;
                g->pool[k].tgt[1] = p[1].y + ((func_0019A5C8() >> 4) % (s32)f - ((s32)f >> 1)) / 100.0f;
                g->pool[k].tgt[2] = p[1].z + ((func_0019A5C8() >> 4) % (s32)f - ((s32)f >> 1)) / 100.0f;
                break;
            case 2:
            case 3:
                g->pool[k].kind = 8;
                g->pool[k].size = 0.8f;
                g->pool[k].bD = 3;
                g->pool[k].pos[0] = p[2].x;
                g->pool[k].pos[1] = p[2].y;
                g->pool[k].pos[2] = p[2].z;
                g->pool[k].tgt[0] = p[i + 1].x;
                g->pool[k].tgt[1] = p[i + 1].y;
                g->pool[k].tgt[2] = p[i + 1].z;
                break;
            }
        }
        break;
    }
    k = func_001F54E0(g->unit);
    g->joint[0] = func_001F5560(g->unit, 1, 1);
    i = (func_0019A5C8() >> 4) % (k - 3) + 3;
    g->joint[1] = func_001F5560(g->unit, i, 0);
    i = (func_0019A5C8() >> 4) % (k - 5) + 3;
    g->joint[2] = func_001F5560(g->unit, i, 0);
    g->joint[3] = func_001F5560(g->unit, i - 2, 0);
    g->joint[4] = func_001F5560(g->unit, i + 2, 0);
}
#pragma optimization_level reset

INCLUDE_ASM("asm/nonmatchings/mod/b033", func_01E05470_b033);

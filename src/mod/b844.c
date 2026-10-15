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

static void func_01E00080_b844(Obj_b010_01E00080 *o) {
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
/* OVL_WARM */

/* shape b387:01E00410, 1018 insns, 3 copies: comet emitters (0x44 bytes each): the head position (optionally following the
   owner) is pushed into a ring of pool entries; the history is either used as is (flag 4 of b24) or run through
   the spline; a head sprite is drawn at the first point, then a ribbon of quads between consecutive projected
   points (stopping at the first point that fails to project), widths from the depth, alpha fading along the tail. */

typedef struct {
    s32 n;
    f32 x[8];
    f32 y[8];
    f32 z[8];
    Vec4f out[28];
} Spline_b387_01E00410;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b387_01E00410;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    Xyz_b387_01E00410 p;
} Vtx_b387_01E00410;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b387_01E00410 v[4];
    u8 tail[0x20];
} Pkt_b387_01E00410;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    struct {
        u64 tc;
        Xyz_b387_01E00410 p;
    } v[4];
    u8 tail[0x20];
} Spr_b387_01E00410;

typedef struct {
    u8 pad0[5];
    u8 page;
    u8 pad6[2];
    s32 u, w, v, h;
} Tex_b387_01E00410;

typedef struct {
    u8 life;
    u8 pad1[3];
    f32 x, y, z;
} Part_b387_01E00410;

typedef struct {
    u8 life;
    u8 pad1;
    u8 max;
    u8 mask;
    u8 flags;
    u8 follow;
    u8 pad6[2];
    Part_b387_01E00410 *parts;
    s16 slot[9];
    u8 count;
    u8 texid;
    u8 b20;
    u8 page;
    u8 frame;
    u8 frame2;
    u8 b24;
    u8 pad25[3];
    s32 type;
    f32 size;
    f32 width;
    u8 b, g, r, a;
    f32 pos[3];
} Comet_b387_01E00410;

#pragma optimization_level 2

static s32 func_01E00410_b844(void *arg0, s32 ot __attribute__((aligned(8))), s32 n) {
    extern s32 func_00101AF0(void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_0020EB40(void *);
    extern void func_00101BA0(void *, void *);
    extern s32 func_00101C30(void *, s32, s32);
    extern void func_00101B40(void *, u8, s32);
    extern s32 func_00102550(void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern s32 func_00101600(void *);
    extern f32 func_001018E0(f32, f32);
    extern void func_001020B0(void *, s32, s32);
    extern void func_00101D20(void *, void *, void *);
    extern void func_00101EE0(void *, void *, void *);
    extern void func_002075F0(void *, s32, s32);
    f32 mat[16];
    Spline_b387_01E00410 sp;
    Vec4f t;
    Xyz_b387_01E00410 q[2];
    Tex_b387_01E00410 td;
    Pkt_b387_01E00410 pkt;
    Spr_b387_01E00410 spr;
    f32 dz[2];
    Comet_b387_01E00410 *e;
    Part_b387_01E00410 *pool;
    s32 i;
    s32 k;
    s32 m;
    Part_b387_01E00410 *p;
    void *tex;
    s32 ok;
    s32 pok;
    s32 fr;
    s32 idx;
    s32 dd;
    f32 h;
    f32 pw;
    f32 d;
    f32 al;

    e = arg0;
    pool = e->parts;
    for (i = 0; i < n; i++) {
        if (i != 0) {
            e = (Comet_b387_01E00410 *)((u8 *)e + 0x44);
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        tex = (void *)func_00202BF0(5, e->texid);
        func_0020EB40(mat);
        if (e->follow != 0) {
            func_00101BA0(e, &t);
            e->pos[0] = t.x;
            e->pos[1] = t.y;
            e->pos[2] = t.z;
        }
        fr = e->mask & (e->max - e->life);
        if (e->life == 0) {
            for (k = 0; k < e->count; k++) {
                p = &pool[e->slot[k]];
                p->life = 0;
                e->slot[k] = -1;
            }
            continue;
        }
        for (k = e->count; k > 0; k--) {
            if (e->slot[k - 1] >= 0) {
                p = &pool[e->slot[k - 1]];
                p->life = e->life;
            }
            if (!(e->flags & 8)) {
                e->slot[k] = e->slot[k - 1];
            }
        }
        if (!(e->flags & 8)) {
            if (e->slot[e->count] >= 0) {
                p = &pool[e->slot[e->count]];
                p->life = 0;
                e->slot[e->count] = -1;
            }
            idx = func_00101C30(pool, 0x10, e->type);
            if (idx >= 0) {
                e->slot[0] = idx;
                p = &pool[e->slot[0]];
                func_00101B40(p, e->life, 0);
                p->x = e->pos[0];
                p->y = e->pos[1];
                p->z = e->pos[2];
            } else {
                e->slot[0] = -1;
            }
        }
        if (e->b24 & 4) {
            m = 0;
            for (k = 0; k < e->count; k++) {
                if (e->slot[k] >= 0) {
                    p = &pool[e->slot[k]];
                    sp.out[k].x = p->x;
                    sp.out[k].y = p->y;
                    sp.out[k].z = p->z;
                    m++;
                }
            }
        } else {
            sp.n = 0;
            for (k = 0; k < e->count; k++) {
                if (e->slot[k] >= 0) {
                    p = &pool[e->slot[k]];
                    sp.x[sp.n] = p->x;
                    sp.y[sp.n] = p->y;
                    sp.z[sp.n] = p->z;
                    sp.n++;
                }
            }
            if (func_00102550(&sp) == 0) {
                continue;
            }
            m = (sp.n - 1) * 4;
        }
        ok = func_00205440(&sp.out[0], mat, &q[1], &dz[1]);
        h = func_001018E0(e->size, dz[1]);
        if (ok != 0) {
            ok = func_00101600(&q[1]);
        }
        if (ok != 0 && !(e->flags & 1)) {
            ((Spr_b387_01E00410 *)(s32)&spr)->count = 0x24;
            ((Spr_b387_01E00410 *)(s32)&spr)->tag = 9;
            ((Spr_b387_01E00410 *)(s32)&spr)->regs = ((u64)4 << 32) | 0x24242421;
            ((Spr_b387_01E00410 *)(s32)&spr)->pad = 0;
            spr.r = e->r;
            spr.g = e->g;
            spr.b = e->b;
            spr.q = 1.0f;
            if (e->flags & 2) {
                dd = fr & 7;
                if (e->life < 7) {
                    dd = 7 - e->life;
                }
            } else {
                dd = e->frame;
            }
            td.page = e->page;
            func_001020B0(&td, dd, e->b20);
            func_00101D20(&spr, &td, tex);
            spr.a = e->a;
            if (!(e->flags & 0x40)) {
                if (e->life < 4) {
                    spr.a = (e->a >> 2) * e->life;
                }
            }
            if (e->flags & 0x80) {
                spr.v[0].p.z = spr.v[1].p.z = spr.v[2].p.z = spr.v[3].p.z = 0xFFFFFE;
                d = 0.0f;
            } else {
                spr.v[0].p.z = spr.v[1].p.z = spr.v[2].p.z = spr.v[3].p.z = q[1].z;
                d = dz[1];
            }
            spr.v[0].p.x = spr.v[2].p.x = q[1].x - h;
            spr.v[1].p.x = spr.v[3].p.x = q[1].x + h;
            spr.v[0].p.y = spr.v[1].p.y = q[1].y - h;
            spr.v[2].p.y = spr.v[3].p.y = q[1].y + h;
            func_002075F0(&spr, ot, (u32)d);
        }
        ((Pkt_b387_01E00410 *)(s32)&pkt)->count = 0x34;
        ((Pkt_b387_01E00410 *)(s32)&pkt)->tag = 0xC;
        ((Pkt_b387_01E00410 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Pkt_b387_01E00410 *)(s32)&pkt)->pad = 0;
        pkt.v[0].r = pkt.v[1].r = pkt.v[2].r = pkt.v[3].r = e->r;
        pkt.v[0].g = pkt.v[1].g = pkt.v[2].g = pkt.v[3].g = e->g;
        pkt.v[0].b = pkt.v[1].b = pkt.v[2].b = pkt.v[3].b = e->b;
        pkt.v[0].q = pkt.v[1].q = pkt.v[2].q = pkt.v[3].q = 1.0f;
        td.page = e->page;
        func_001020B0(&td, e->frame2, e->b20);
        if (e->flags & 4) {
            dd = (td.w - td.u) >> 1;
            td.u = td.u + dd - 1;
            td.w = td.w - dd + 1;
        }
        func_00101EE0(&pkt, &td, tex);
        h = func_001018E0(e->width, dz[1]);
        for (k = 1; k < m - 1; k++) {
            q[0] = q[1];
            dz[0] = dz[1];
            pw = h;
            pok = ok;
            ok = func_00205440(&sp.out[k], mat, &q[1], &dz[1]);
            if (ok != 0) {
                ok = func_00101600(&q[1]);
            }
            if (pok == 0 || ok == 0) {
                break;
            }
                h = func_001018E0(e->width, dz[1]);
                if (e->life < 4 && !(e->flags & 0x40)) {
                    al = (f32)e->life * e->a / 4.0f;
                } else {
                    al = e->a;
                }
                d = al / m;
                pkt.v[0].a = pkt.v[2].a = d * (m - k);
                pkt.v[1].a = pkt.v[3].a = d * (m - k - 1);
                if (k == 1 && (e->b24 & 2)) {
                    pkt.v[0].a = pkt.v[2].a = 0;
                }
                if (e->flags & 0x80) {
                    pkt.v[0].p.z = pkt.v[1].p.z = pkt.v[2].p.z = pkt.v[3].p.z = 0xFFFFFE;
                    d = 0.0f;
                } else {
                    pkt.v[0].p.z = pkt.v[2].p.z = q[0].z;
                    pkt.v[1].p.z = pkt.v[3].p.z = q[1].z;
                    if (dz[0] < dz[1]) {
                        d = dz[0];
                    } else {
                        d = dz[1];
                    }
                }
                pkt.v[0].p.y = q[0].y - pw;
                pkt.v[1].p.y = q[1].y - h;
                pkt.v[2].p.y = q[0].y + pw;
                pkt.v[3].p.y = q[1].y + h;
                pkt.v[0].p.x = pkt.v[2].p.x = q[0].x;
                pkt.v[1].p.x = pkt.v[3].p.x = q[1].x;
                func_002075F0(&pkt, ot, (u32)d);
                pkt.v[0].p.x = q[0].x - pw;
                pkt.v[1].p.x = q[1].x - h;
                pkt.v[2].p.x = q[0].x + pw;
                pkt.v[3].p.x = q[1].x + h;
                pkt.v[0].p.y = pkt.v[2].p.y = q[0].y;
                pkt.v[1].p.y = pkt.v[3].p.y = q[1].y;
                func_002075F0(&pkt, ot, (u32)d);
        }
    }
    return 1;
}
#pragma optimization_level reset

INCLUDE_ASM("asm/nonmatchings/mod/b844", func_01E01400_b844);

INCLUDE_ASM("asm/nonmatchings/mod/b844", func_01E01F80_b844);

INCLUDE_ASM("asm/nonmatchings/mod/b844", func_01E02B10_b844);

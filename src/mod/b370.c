#include "common.h"

typedef struct {
    f32 x, y, z, w;
} Vec_b005_01E00080;

typedef struct {
    u8 count;
    u8 pad01;
    u8 length;
    u8 mask;
    u8 mode;
    u8 pad05[0xB];
    u8 light[0x10];
    Vec_b005_01E00080 pos;
    u8 pad30[8];
    f32 value;
    u8 pad3C[4];
    Vec_b005_01E00080 vel;
    f32 base;
} Fx_b005_01E00080;

static void func_01E00080_b370(Fx_b005_01E00080 *o) {
    u8 phase;
    u8 mask;
    u8 rest;
    u8 count;
    f32 step;
    u8 length;
    s32 on;

    if (func_00101AF0(o) == 0) {
        return;
    }
    o->pos.x += o->vel.x;
    o->pos.y += o->vel.y;
    o->pos.z += o->vel.z;
    func_00101BA0(o, (s32)&o->pos);
    count = o->count;
    mask = o->mask;
    length = o->length;
    phase = count & mask;
    rest = length - count;
    if (mask == 0xFF) {
        step = o->base / length;
    } else {
        step = o->base / (mask + 1);
    }
    on = 1;
    switch (o->mode & 0xF) {
    case 1:
        o->value = step * phase;
        break;
    case 2:
        if (mask == 0xFF) {
            if (rest < length >> 1) {
                o->value = 2.0f * step * rest;
            } else {
                o->value = 2.0f * step * count;
            }
        } else {
            if (phase < mask >> 1) {
                o->value = 2.0f * step * (mask - phase);
            } else {
                o->value = 2.0f * step * phase;
            }
        }
        break;
    case 4:
        o->value = o->base;
        if (o->count & 1) {
            o->value *= 0.5f;
        }
        break;
    case 8:
        if (count & 1) {
            on = 0;
        }
    default:
        o->value = o->base;
        break;
    }
    if (on == 0 || o->count == 0) {
        func_001F6C10(0);
    } else {
        func_001F6C10((s32)o->light);
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b370", func_01E003A0_b370);

INCLUDE_ASM("asm/nonmatchings/mod/b370", func_01E011B0_b370);

/* OVL_WARM */

/* shape b029:01E02B80, 696 insns, 37 copies: update and draw ribbon emitters (0x68 bytes each, may turn toward a
   target object); each segment is projected and drawn as a quad from the emitter's origin, widened on screen */

typedef struct Uvs_b029_01E02B80 {
    s32 kind;
    u8 tex;
    u8 b5;
    u16 pad6;
    s32 u0, v0, u1, v1;
} Uvs_b029_01E02B80;

typedef struct Rib_b029_01E02B80 {
    u8 age;
    u8 b1;
    u8 life;
    u8 b3;
    u8 flags;
    u8 b5[3];
    u8 count;
    u8 k;
    u8 idx;
    u8 b5c;
    u8 frame;
    u8 hold;
    u8 target;
    u8 padF;
    u8 *pts;
    f32 scale;
    f32 f18;
    f32 width;
    u8 b0, g0, r0, a0;
    u8 b1c, g1, r1, a1;
    f32 pos[3];
    u8 pad34[4];
    f32 vel[3];
    u8 pad44[4];
    s32 rot[3];
    u8 pad54[4];
    s32 drot[3];
    u8 pad64[4];
} Rib_b029_01E02B80;

typedef struct Xyz_b029_01E02B80 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Xyz_b029_01E02B80;

typedef struct Vtx_b029_01E02B80 {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    Xyz_b029_01E02B80 xyz;
} Vtx_b029_01E02B80;

typedef struct Pk_b029_01E02B80 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Vtx_b029_01E02B80 v[4];
    u8 pad70[0x20];
} Pk_b029_01E02B80;

static inline void b029_01E02B80_tag(Pk_b029_01E02B80 *p, s32 size, s32 flags, u64 regs) {
    p->flags = flags;
    p->size = size;
    p->regs = regs;
    p->pad4 = 0;
}

static s32 func_01E01C00_b370(Rib_b029_01E02B80 *arg0, s32 id __attribute__((aligned(8))), s32 n) {
    extern s32 func_00205440();
    extern void func_00101BA0();
    extern void func_001020B0();
    extern void func_00101EE0();
    extern void func_0020C940();
    extern void func_0020BC00();
    extern void func_00101940();
    extern s32 func_001F53A0();
    extern void func_001F5620();
    Rib_b029_01E02B80 *p = arg0;
    s32 i __attribute__((aligned(16)));
    s32 life __attribute__((aligned(16)));
    s32 j __attribute__((aligned(16)));
    s32 tex;
    u8 k;
    s32 dx;
    s32 dy;
    f32 h;
    f32 ang;
    f32 zf;
    f32 x;
    f32 lf;
    f32 half;
    f32 y;
    f32 z;
    f32 b;
    f32 rad;

    f32 m2[4][4];
    f32 m[4][4];
    Xyz_b029_01E02B80 s[2];
    f32 v[4];
    Vec4f d;
    Vec4f tgt;
    extern Uvs_b029_01E02B80 D_01E075A0_b370;
    Uvs_b029_01E02B80 tbl = D_01E075A0_b370;
    Uvs_b029_01E02B80 uvs;
    Pk_b029_01E02B80 pk __attribute__((aligned(8)));
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
            uvs.b5 = p->b5c;
            func_001020B0(&uvs, p->frame, 0);
        } else {
            tex = func_00202BF0(tbl.kind, tbl.tex);
            uvs = tbl;
        }
        if (!(p->flags & 2)) {
            uvs.v0 -= 0x10;
            uvs.v1 -= 0x10;
        }
        ang = 0.0f;
        k = p->k;
        if (p->age < p->hold) {
            life = p->life - p->hold;
        } else {
            life = p->life - p->age;
        }
        p->pos[0] += p->vel[0];
        p->pos[1] += p->vel[1];
        p->pos[2] += p->vel[2];
        p->rot[0] += p->drot[0];
        p->rot[1] += p->drot[1];
        p->rot[2] += p->drot[2];
        func_00101BA0(p, p->pos);
        if (p->flags & 8) {
            func_001F5620(func_001F53A0(), p->target, &tgt);
            d.x = tgt.x - p->pos[0];
            d.y = tgt.y - p->pos[1];
            d.z = tgt.z - p->pos[2];
            func_00101940(&d, p->rot);
        }
        func_0020EB40(m);
        func_0020C940(m2, 0, p->rot, p->pos);
        func_0020BC00(m, m2);
        b029_01E02B80_tag((Pk_b029_01E02B80 *)(u32)&pk, 0xC, 0x34, ((u64)0x4214 << 32) | 0x21421421);
        pk.v[0].r = pk.v[1].r = p->r0;
        pk.v[2].r = pk.v[3].r = p->r1;
        pk.v[0].g = pk.v[1].g = p->g0;
        pk.v[2].g = pk.v[3].g = p->g1;
        pk.v[0].b = pk.v[1].b = p->b0;
        pk.v[2].b = pk.v[3].b = p->b1c;
        pk.v[0].q = pk.v[1].q = pk.v[2].q = pk.v[3].q = 1.0f;
        if (p->age < 8 && !(p->flags & 0x40)) {
            pk.v[0].a = pk.v[1].a = pk.v[2].a = (p->a0 >> 3) * p->age;
            pk.v[3].a = (p->a1 >> 3) * p->age;
        } else {
            pk.v[0].a = pk.v[1].a = pk.v[2].a = p->a0;
            pk.v[3].a = p->a1;
        }
        func_00101EE0(&pk, &uvs, tex);
        v[0] = v[1] = v[2] = 0.0f;
        if (func_00205440(v, m, &s[1], &depth[1]) == 0) {
            continue;
        }
        if (func_00101600(&s[1]) == 0) {
            continue;
        }
        for (j = 0; j < p->count; j++) {
            if (p->flags & 1) {
                x = p->scale * (f32)(p->pts[k] - p->pts[k + 1]) / 255.0f;
                y = p->scale * (f32)(p->pts[k + 2] - p->pts[k + 3]) / 255.0f;
                z = p->scale * (f32)(p->pts[k + 4] - p->pts[k + 5]) / 255.0f;
                k += 6;
            } else {
                ang += 17.0f;
                if (!(ang <= 360.0f)) {
                    ang -= 360.0f;
                }
                b = p->f18 * (f32)(u32)p->pts[k++] / 255.0f;
                rad = 3.1415927f * ang / 180.0f;
                x = b * func_001A6898(rad);
                z = b * func_001A6A88(rad);
                half = p->scale / 2.0f;
                y = half + half * ((f32)(u32)p->pts[k++] / 255.0f);
            }
            lf = (f32)life;
            v[0] = x * lf;
            v[1] = y * lf;
            v[2] = z * lf;
            if (func_00205440(v, m, &s[0], &depth[0]) == 0) {
                continue;
            }
            if (func_00101600(&s[0]) == 0) {
                continue;
            }
            h = func_001018E0(p->width, depth[0]);
            if (p->flags & 0x80) {
                zf = 0.0f;
                pk.v[0].xyz.z = pk.v[1].xyz.z = pk.v[2].xyz.z = pk.v[3].xyz.z = 0xFFFFFE;
            } else {
                if (depth[0] < depth[1]) {
                    zf = depth[0];
                } else {
                    zf = depth[1];
                }
                pk.v[0].xyz.z = pk.v[1].xyz.z = s[0].z;
                pk.v[2].xyz.z = pk.v[3].xyz.z = s[1].z;
            }
            pk.v[0].xyz.fog = pk.v[1].xyz.fog = pk.v[2].xyz.fog = pk.v[3].xyz.fog = 0;
            dy = s[1].y - s[0].y;
            dy = dy >= 0 ? dy : -dy;
            dx = s[1].x - s[0].x;
            dx = dx >= 0 ? dx : -dx;
            if (dy < dx) {
                pk.v[0].xyz.y = s[0].y;
                pk.v[1].xyz.y = s[0].y - h;
                pk.v[2].xyz.y = s[0].y + h;
                pk.v[3].xyz.y = s[1].y;
                if ((s32)s[0].x < (s32)s[1].x) {
                    pk.v[0].xyz.x = s[0].x - h;
                } else {
                    pk.v[0].xyz.x = s[0].x + h;
                }
                pk.v[1].xyz.x = pk.v[2].xyz.x = s[0].x;
                pk.v[3].xyz.x = s[1].x;
            } else {
                pk.v[0].xyz.x = s[0].x;
                pk.v[1].xyz.x = s[0].x - h;
                pk.v[2].xyz.x = s[0].x + h;
                pk.v[3].xyz.x = s[1].x;
                if ((s32)s[0].y < (s32)s[1].y) {
                    pk.v[0].xyz.y = s[0].y - h;
                } else {
                    pk.v[0].xyz.y = s[0].y + h;
                }
                pk.v[1].xyz.y = pk.v[2].xyz.y = s[0].y;
                pk.v[3].xyz.y = s[1].y;
            }
            func_002075F0((s32)&pk, id, (u32)zf);
        }
    }
    return 1;
}

/* OVL_WARM */

/* shape b070:01E03C10, 676 insns, 13 copies: draws n lightning bolts (0x40-byte emitters): func_00102A50 builds the zigzag
   points between two ends (from func_00101BA0 or the emitter's moving ends); each projected segment becomes
   (life & 3) + 1 quads, widened across the shorter screen axis; the corner order rotates with age */

typedef struct {
    f32 x, y, z;
} Vec3_b070_01E03C10;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b070_01E03C10;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    Xyz_b070_01E03C10 xyz;
} Vtx_b070_01E03C10;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b070_01E03C10 v[4];
    u8 tail[0x20];
} Pkt_b070_01E03C10;

typedef struct {
    s32 k0, k1;
    s32 u, w, v, h;
} Tex_b070_01E03C10;

typedef struct {
    s32 n;
    f32 jitter;
    Vec3_b070_01E03C10 a;
    Vec3_b070_01E03C10 b;
    Vec3_b070_01E03C10 *pts;
} Bolt_b070_01E03C10;

typedef struct {
    u8 life;
    u8 pad1;
    u8 max;
    u8 pad3;
    u8 flags;
    u8 mode;
    u8 sel;
    u8 pad7;
    u8 nseg;
    u8 sel0;
    u8 sel1;
    u8 texid;
    u8 texsel;
    u8 wdiv;
    u8 padE[2];
    f32 jitter;
    f32 grow;
    u8 b, g, r, a;
    Vec3_b070_01E03C10 p0;
    Vec3_b070_01E03C10 p1;
    Vec3_b070_01E03C10 vel;
} Emit_b070_01E03C10;

typedef struct W_tmpl_func_01E026E0_b370 {
    Tex_b070_01E03C10 v[2];
} W_tmpl_func_01E026E0_b370;

static s32 func_01E026E0_b370(void *arg0, s32 ot __attribute__((aligned(8))), s32 n) {
    extern void func_00101BA0(void *, void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_00102A50(void *);
    extern void func_00101EE0(void *, void *, void *);
    Emit_b070_01E03C10 *e = arg0;
    f32 mat[16];
    Bolt_b070_01E03C10 bolt;
    Vec3_b070_01E03C10 pts[17];
    Xyz_b070_01E03C10 s[3];
    Vec4f v;
    Vec3_b070_01E03C10 ab[2];
    extern W_tmpl_func_01E026E0_b370 D_01E075C0_b370;
    W_tmpl_func_01E026E0_b370 tmpl_w = D_01E075C0_b370;
    Pkt_b070_01E03C10 pkt __attribute__((aligned(8)));
    f32 depth[2];
    s32 i;
    void *tex;
    s32 j;
    s32 end;
    s32 k;
    s32 dx;
    s32 dy;
    f32 fdx;
    f32 fdy;
    f32 w;
    u32 c0;
    u32 c1;
    f32 z;

    for (i = 0; i < n; i++) {
        if (i != 0) {
            e++;
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        tex = (void *)func_00202BF0(5, e->texid);
        if (e->mode != 0) {
            e->sel = e->sel0;
            func_00101BA0(e, &v);
            ab[0].x = v.x;
            ab[0].y = v.y;
            ab[0].z = v.z;
            if (e->flags & 2) {
                ab[1].x = ab[0].x + e->p0.x;
                ab[1].y = ab[0].y + e->p0.y;
                ab[1].z = ab[0].z + e->p0.z;
            } else {
                e->sel = e->sel1;
                func_00101BA0(e, &v);
                ab[1].x = v.x;
                ab[1].y = v.y;
                ab[1].z = v.z;
            }
        } else {
            e->p0.x += e->vel.x;
            e->p0.y += e->vel.y;
            e->p0.z += e->vel.z;
            e->p1.x += e->vel.x;
            e->p1.y += e->vel.y;
            e->p1.z += e->vel.z;
            ab[0] = e->p0;
            ab[1] = e->p1;
        }
        func_0020EB40(mat);
        bolt.n = e->nseg;
        bolt.jitter = e->jitter;
        bolt.pts = pts;
        bolt.a = ab[0];
        bolt.b = ab[1];
        func_00102A50(&bolt);
        ((Pkt_b070_01E03C10 *)(s32)&pkt)->count = 0x34;
        ((Pkt_b070_01E03C10 *)(s32)&pkt)->tag = 0xC;
        ((Pkt_b070_01E03C10 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Pkt_b070_01E03C10 *)(s32)&pkt)->pad = 0;
        pkt.v[0].r = pkt.v[1].r = pkt.v[2].r = pkt.v[3].r = e->r;
        pkt.v[0].g = pkt.v[1].g = pkt.v[2].g = pkt.v[3].g = e->g;
        pkt.v[0].b = pkt.v[1].b = pkt.v[2].b = pkt.v[3].b = e->b;
        pkt.v[0].q = pkt.v[1].q = pkt.v[2].q = pkt.v[3].q = 1.0f;
        pkt.v[0].a = pkt.v[1].a = pkt.v[2].a = pkt.v[3].a = e->a;
        func_00101EE0(&pkt, &tmpl_w.v[e->texsel], tex);
        if (!(e->flags & 4) && e->life < bolt.n) {
            j = bolt.n - e->life;
        } else {
            j = 0;
        }
        if ((e->flags & 1) && e->max - e->life < bolt.n) {
            end = e->max - e->life;
        } else {
            end = bolt.n;
        }
        for (; j < end; j++) {
            if (func_00205440(&pts[j], mat, &s[0], &depth[0]) == 0 || func_00101600(&s[0]) == 0 ||
                func_00205440(&pts[j + 1], mat, &s[1], &depth[1]) == 0 || func_00101600(&s[1]) == 0) {
                continue;
            }
            dx = s[0].x - s[1].x;
            fdx = (dx >= 0) ? dx : -dx;
            dy = s[0].y - s[1].y;
            fdy = (dy >= 0) ? dy : -dy;
            w = func_001A6C60(fdx * fdx + fdy * fdy) / e->wdiv;
            for (k = 0; k < (e->life & 3) + 1; k++) {
                w += k * (w * e->grow);
                if (fdx > fdy) {
                    c0 = s[0].y;
                    pkt.v[0].xyz.y = c0 - w;
                    c1 = s[1].y;
                    pkt.v[1].xyz.y = c1 - w;
                    pkt.v[2].xyz.y = c0 + w;
                    pkt.v[3].xyz.y = c1 + w;
                    pkt.v[0].xyz.x = pkt.v[2].xyz.x = s[0].x;
                    pkt.v[1].xyz.x = pkt.v[3].xyz.x = s[1].x;
                } else {
                    c0 = s[0].x;
                    pkt.v[0].xyz.x = c0 - w;
                    c1 = s[1].x;
                    pkt.v[1].xyz.x = c1 - w;
                    pkt.v[2].xyz.x = c0 + w;
                    pkt.v[3].xyz.x = c1 + w;
                    pkt.v[0].xyz.y = pkt.v[2].xyz.y = s[0].y;
                    pkt.v[1].xyz.y = pkt.v[3].xyz.y = s[1].y;
                }
                if (e->flags & 0x80) {
                    pkt.v[0].xyz.z = pkt.v[1].xyz.z = pkt.v[2].xyz.z = pkt.v[3].xyz.z = 0xFFFFFE;
                    z = 0.0f;
                } else {
                    pkt.v[0].xyz.z = pkt.v[1].xyz.z = s[0].z;
                    pkt.v[2].xyz.z = pkt.v[3].xyz.z = s[1].z;
                    if (depth[0] < depth[1]) {
                        z = depth[0];
                    } else {
                        z = depth[1];
                    }
                }
                pkt.v[0].xyz.f = pkt.v[1].xyz.f = 0;
                pkt.v[2].xyz.f = pkt.v[3].xyz.f = 0;
                switch ((e->life + j) & 3) {
                case 1:
                    s[2] = pkt.v[0].xyz;
                    pkt.v[0].xyz = pkt.v[3].xyz;
                    pkt.v[3].xyz = s[2];
                    s[2] = pkt.v[1].xyz;
                    pkt.v[1].xyz = pkt.v[2].xyz;
                    pkt.v[2].xyz = s[2];
                    break;
                case 2:
                    s[2] = pkt.v[0].xyz;
                    pkt.v[0].xyz = pkt.v[1].xyz;
                    pkt.v[1].xyz = s[2];
                    s[2] = pkt.v[2].xyz;
                    pkt.v[2].xyz = pkt.v[3].xyz;
                    pkt.v[3].xyz = s[2];
                    break;
                case 3:
                    s[2] = pkt.v[0].xyz;
                    pkt.v[0].xyz = pkt.v[2].xyz;
                    pkt.v[2].xyz = s[2];
                    s[2] = pkt.v[1].xyz;
                    pkt.v[1].xyz = pkt.v[3].xyz;
                    pkt.v[3].xyz = s[2];
                    break;
                }
                func_002075F0((s32)&pkt, ot, (u32)z);
            }
        }
    }
    return 1;
}

/* shape b238:01E02360, 205 insns, 8 copies: b044:01E03490 (-O2,p) built at -O4,p: run a list of emitters (0x3C bytes each): a held emitter just moves;
   otherwise it takes a particle (0x40 bytes) from its pool, copies its colours/sizes/velocity into it and
   gives it a random offset (rand() % range - range / 2, in hundredths), either as is or as a +/- segment */

typedef struct Col_b238_01E02360 {
    u8 r, g, b, a;
} Col_b238_01E02360;

typedef struct Vec3_b238_01E02360 {
    f32 x, y, z;
} Vec3_b238_01E02360;

typedef struct Em_b238_01E02360 {
    u8 b0;
    u8 b1[2];
    u8 b3;
    u8 flags;
    u8 b5;
    u8 b6;
    u8 b7;
    u8 *pool;
    u8 count;
    u8 bD;
    u8 bE;
    u8 bF;
    u8 b10;
    u8 b11;
    u8 b12[2];
    s32 range;
    f32 f18;
    f32 f1C;
    Col_b238_01E02360 col;
    f32 pos[3];
    Vec3_b238_01E02360 vel;
} Em_b238_01E02360;

typedef struct Part_b238_01E02360 {
    u8 b0[4];
    u8 b4;
    u8 b5;
    u8 b6[2];
    u8 b8;
    u8 b9;
    u8 bA;
    u8 bB;
    u8 bC;
    u8 bD;
    u8 bE[2];
    f32 f10;
    f32 f14;
    Col_b238_01E02360 col;
    f32 a[3];
    f32 b[3];
    Vec3_b238_01E02360 vel;
} Part_b238_01E02360;

static s32 func_01E03170_b370(Em_b238_01E02360 *arg0, s32 arg1, s32 n) {
    extern s32 func_00101C30();
    extern void func_00101AD0(void *, u8, s32, s32);
    extern void func_00101BA0();
    extern s32 func_0019A5C8();
    Em_b238_01E02360 *e = arg0;
    Part_b238_01E02360 *q;
    s32 i;
    s32 k;
    f32 rx;
    f32 ry;
    f32 rz;
    Vec4f tmp;

    for (i = 0; i < n; i++) {
        if (i != 0) {
            e++;
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        if (e->b0 & e->b3) {
            e->pos[0] += e->vel.x;
            e->pos[1] += e->vel.y;
            e->pos[2] += e->vel.z;
            continue;
        }
        k = func_00101C30(e->pool, 0x40, e->count);
        if (k < 0) {
            continue;
        }
        q = (Part_b238_01E02360 *)(e->pool + k * 0x40);
        func_00101AD0(q, e->b11, 0, 0xFF);
        q->b5 = e->b5;
        q->b4 = e->flags;
        q->b9 = e->b6;
        q->b8 = e->bD;
        q->bB = e->bE;
        q->bC = e->bF;
        q->bD = e->b10;
        q->f10 = e->f18;
        q->f14 = e->f1C;
        q->col = e->col;
        q->vel = e->vel;
        if (e->b5) {
            func_00101BA0(e, &tmp);
            e->pos[0] = tmp.x;
            e->pos[1] = tmp.y;
            e->pos[2] = tmp.z;
        }
        rx = ((func_0019A5C8() >> 4) % e->range - (e->range >> 1)) / 100.0f;
        ry = ((func_0019A5C8() >> 4) % e->range - (e->range >> 1)) / 100.0f;
        rz = ((func_0019A5C8() >> 4) % e->range - (e->range >> 1)) / 100.0f;
        if (e->flags & 2) {
            q->a[0] = rx;
            q->a[1] = ry;
            q->a[2] = rz;
        } else {
            q->a[0] = e->pos[0] + rx;
            q->a[1] = e->pos[1] + ry;
            q->a[2] = e->pos[2] + rz;
            q->b[0] = e->pos[0] - rx;
            q->b[1] = e->pos[1] - ry;
            q->b[2] = e->pos[2] - rz;
        }
        if (e->b5 == 0) {
            e->pos[0] += e->vel.x;
            e->pos[1] += e->vel.y;
            e->pos[2] += e->vel.z;
        }
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/mod/b370", func_01E034B0_b370);

/* OVL_WARM: compile warm (DK_WARM=1, after a runtime-helper call as in the original many-files-per-run build).
   Its float -> int casts are MWCC runtime calls: fptosi = 0x001A22C0, fptoui = 0x001A23B0 (link names). */

/* shape b029:01E026A0, 310 insns, 35 copies: full-screen fade quad (4 vertices); its alpha follows the emitter's counter */

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
} Hdr_b029_01E026A0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b029_01E026A0;

typedef struct {
    Hdr_b029_01E026A0 h;
    Vtx_b029_01E026A0 v[4];
    u8 tail[8];
} Pkt_b029_01E026A0;

typedef struct {
    u8 cur;
    u8 pad1;
    u8 max;
    u8 pad3;
    u8 flags;
} Obj_b029_01E026A0;

static s32 func_01E04110_b370(Obj_b029_01E026A0 *o, s32 tex, s32 d, s32 h) {
    Pkt_b029_01E026A0 p __attribute__((aligned(8)));
    u8 a;
    u8 mode;
    u8 k;
    f32 w;
    f32 mid;
    f32 s;

    if (func_00101AF0(o) == 0) {
        return 0;
    }
    ((Hdr_b029_01E026A0 *)(s32)&p)->count = 0x14;
    ((Hdr_b029_01E026A0 *)(s32)&p)->tag = 8;
    ((Hdr_b029_01E026A0 *)(s32)&p)->regs = 0x41414141;
    ((Hdr_b029_01E026A0 *)(s32)&p)->pad = 0;
    mode = o->flags;
    switch (mode & 7) {
    case 1:
        a = 128.0f / o->max * o->cur;
        break;
    case 2:
        a = ((o->max - o->cur) << 7) / o->max;
        break;
    case 4:
    default:
        a = 0x80;
        break;
    }
    if (o->cur == 1 && (mode & 0x80)) {
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
    p.v[0].b = p.v[1].b = p.v[2].b = p.v[3].b = 0xFF;
    p.v[0].g = p.v[1].g = p.v[2].g = p.v[3].g = 0xFF;
    p.v[0].r = p.v[1].r = p.v[2].r = p.v[3].r = 0xFF;
    p.v[0].q = p.v[1].q = p.v[2].q = p.v[3].q = 1.0f;
    p.v[0].z = p.v[1].z = p.v[2].z = p.v[3].z = 0xFFFFFF;
    func_002086D0(&p, 0x48);
    if (o->flags & 0x10) {
        h = o->max >> 1;
        s = h;
        s = 7168.0f / s;
        d = o->max - o->cur;
        k = (0x80 / h) * (d >> 1);
        if (h < d) {
            p.v[0].a = p.v[1].a = k;
            d = o->max >> 1;
        } else {
            p.v[0].a = p.v[1].a = 0;
        }
        p.v[2].a = p.v[3].a = 0x80;
        p.v[0].x = p.v[2].x = 0x6C00;
        p.v[1].x = p.v[3].x = 0x9400;
        w = s * d;
        mid = 32768.0f;
        p.v[0].y = p.v[1].y = mid - w;
        p.v[2].y = p.v[3].y = mid;
        func_002075F0((s32)&p, tex, 0);
        p.v[2].a = p.v[3].a = p.v[1].a;
        p.v[1].a = p.v[0].a = 0x80;
        p.v[0].y = p.v[1].y = mid;
        p.v[2].y = p.v[3].y = mid + w;
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

INCLUDE_ASM("asm/nonmatchings/mod/b370", func_01E045F0_b370);

INCLUDE_ASM("asm/nonmatchings/mod/b370", func_01E04F00_b370);

INCLUDE_ASM("asm/nonmatchings/mod/b370", func_01E05940_b370);

INCLUDE_ASM("asm/nonmatchings/mod/b370", func_01E062B0_b370);

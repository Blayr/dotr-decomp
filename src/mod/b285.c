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

static void func_01E00080_b285(Fx_b005_01E00080 *o) {
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

INCLUDE_ASM("asm/nonmatchings/mod/b285", func_01E003A0_b285);

INCLUDE_ASM("asm/nonmatchings/mod/b285", func_01E014C0_b285);

INCLUDE_ASM("asm/nonmatchings/mod/b285", func_01E02120_b285);

/* OVL_WARM: compile warm (its (u32) casts are jal fptoui, func_001A23B0) */

/* shape b040:01E01340, 1016 insns: n beam emitters (0x38 bytes each): on first use the two ends come from
   func_00101BA0 (sel = i0, then i1); the beam a-b is drawn as 4 offset lines of half-width func_001018E0(size,
   depth) at each end, plus the extensions past a (ext0) and past b (ext1), far z with flags & 0x80; the
   extensions use a width the original never sets (r2) */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b040_01E01340;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Xyz_b040_01E01340 xyz;
} Vtx_b040_01E01340;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b040_01E01340 v[4];
    u8 tail[8];
} Pkt_b040_01E01340;

typedef struct {
    u8 b, g, r, a;
} Col_b040_01E01340;

typedef struct {
    f32 x, y, z;
} V3_b040_01E01340;

typedef struct {
    u8 life;
    u8 pad1[3];
    u8 flags;
    u8 inited;
    u8 sel;
    u8 pad7;
    u8 i0;
    u8 i1;
    u8 padA[2];
    f32 size;
    f32 ext0;
    f32 ext1;
    Col_b040_01E01340 c1;
    Col_b040_01E01340 c0;
    V3_b040_01E01340 a;
    V3_b040_01E01340 b;
} Emit_b040_01E01340;

static s32 func_01E02B70_b285(void *arg0, s32 ot, s32 n) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_00101BA0(void *, void *);
    extern f32 func_001018E0(f32, f32);
    s32 i;
    f32 mat[16];
    Vec4f pt[4];
    Vec4f tmp;
    Xyz_b040_01E01340 xy[4];
    f32 dep[4];
    Pkt_b040_01E01340 pkt __attribute__((aligned(8)));
    Emit_b040_01E01340 *e;
    f32 r0;
    f32 r1;
    f32 r2;

    e = arg0;
    for (i = 0; i < n; i++) {
        if (i != 0) {
            e++;
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        if (!(e->flags & 1)) {
            e->inited = 1;
            e->sel = e->i0;
            func_00101BA0(e, &tmp);
            e->a.x = tmp.x;
            e->a.y = tmp.y;
            e->a.z = tmp.z;
            e->sel = e->i1;
            func_00101BA0(e, &tmp);
            e->b.x = tmp.x;
            e->b.y = tmp.y;
            e->b.z = tmp.z;
        }
        pt[0].x = e->a.x;
        pt[0].y = e->a.y;
        pt[0].z = e->a.z;
        pt[1].x = e->b.x;
        pt[1].y = e->b.y;
        pt[1].z = e->b.z;
        pt[2].x = e->a.x + e->ext0 * (e->a.x - e->b.x);
        pt[2].y = e->a.y + e->ext0 * (e->a.y - e->b.y);
        pt[2].z = e->a.z + e->ext0 * (e->a.z - e->b.z);
        pt[3].x = e->b.x - e->ext1 * (e->a.x - e->b.x);
        pt[3].y = e->b.y - e->ext1 * (e->a.y - e->b.y);
        pt[3].z = e->b.z - e->ext1 * (e->a.z - e->b.z);
        func_0020EB40(mat);
        ((Pkt_b040_01E01340 *)(s32)&pkt)->count = 0x14;
        ((Pkt_b040_01E01340 *)(s32)&pkt)->tag = 8;
        ((Pkt_b040_01E01340 *)(s32)&pkt)->regs = 0x41414141;
        ((Pkt_b040_01E01340 *)(s32)&pkt)->pad = 0;
        pkt.v[2].r = pkt.v[3].r = e->c1.r;
        pkt.v[2].g = pkt.v[3].g = e->c1.g;
        pkt.v[2].b = pkt.v[3].b = e->c1.b;
        pkt.v[0].r = pkt.v[1].r = e->c0.r;
        pkt.v[0].g = pkt.v[1].g = e->c0.g;
        pkt.v[0].b = pkt.v[1].b = e->c0.b;
        pkt.v[0].q = pkt.v[1].q = pkt.v[2].q = pkt.v[3].q = 1.0f;
        func_002086D0(&pkt, 0x48);
        if ((e->flags & 2) && (e->life & 1)) {
            pkt.v[0].a = pkt.v[1].a = e->c0.a >> 1;
            pkt.v[2].a = pkt.v[3].a = e->c1.a >> 1;
        } else {
            pkt.v[0].a = pkt.v[1].a = e->c0.a;
            pkt.v[2].a = pkt.v[3].a = e->c1.a;
        }
        if (func_00205440(&pt[0], mat, &xy[0], &dep[0]) == 0 || func_00205440(&pt[1], mat, &xy[1], &dep[1]) == 0 ||
            (!(e->ext0 <= 0.0f) && func_00205440(&pt[2], mat, &xy[2], &dep[2]) == 0) ||
            (!(e->ext1 <= 0.0f) &&
             (func_00205440(&pt[3], mat, &xy[3], &dep[3]) == 0 || func_00101600(&xy[3]) == 0))) {
            continue;
        }
        r0 = func_001018E0(e->size, dep[0]);
        r1 = func_001018E0(e->size, dep[1]);
        if (e->flags & 0x80) {
            xy[0].z = xy[1].z = xy[2].z = 0xFFFFFE;
            dep[0] = dep[1] = dep[2] = 0.0f;
        }
        pkt.v[0].xyz.z = pkt.v[2].xyz.z = xy[0].z;
        pkt.v[1].xyz.z = pkt.v[3].xyz.z = xy[1].z;
        pkt.v[0].xyz.f = pkt.v[2].xyz.f = pkt.v[1].xyz.f = pkt.v[3].xyz.f = 1;
        pkt.v[2].xyz.y = xy[0].y;
        pkt.v[3].xyz.y = xy[1].y;
        pkt.v[0].xyz.y = (u32)(xy[0].y - r0);
        pkt.v[1].xyz.y = (u32)(xy[1].y - r1);
        pkt.v[0].xyz.x = pkt.v[2].xyz.x = xy[0].x;
        pkt.v[1].xyz.x = pkt.v[3].xyz.x = xy[1].x;
        func_002075F0((s32)&pkt, ot, (u32)dep[0]);
        pkt.v[0].xyz.y = (u32)(xy[0].y + r0);
        pkt.v[1].xyz.y = (u32)(xy[1].y + r1);
        func_002075F0((s32)&pkt, ot, (u32)dep[0]);
        pkt.v[0].xyz.x = (u32)(xy[0].x - r0);
        pkt.v[1].xyz.x = (u32)(xy[1].x - r1);
        pkt.v[2].xyz.x = xy[0].x;
        pkt.v[3].xyz.x = xy[1].x;
        pkt.v[0].xyz.y = pkt.v[2].xyz.y = xy[0].y;
        pkt.v[1].xyz.y = pkt.v[3].xyz.y = xy[1].y;
        func_002075F0((s32)&pkt, ot, (u32)dep[0]);
        pkt.v[0].xyz.x = (u32)(xy[0].x + r0);
        pkt.v[1].xyz.x = (u32)(xy[1].x + r1);
        func_002075F0((s32)&pkt, ot, (u32)dep[0]);
        pkt.v[3].a = 0;
        if (!(e->ext0 <= 0.0f)) {
            pkt.v[0].xyz.z = pkt.v[2].xyz.z = xy[0].z;
            pkt.v[1].xyz.z = pkt.v[3].xyz.z = xy[2].z;
            pkt.v[2].xyz.y = xy[0].y;
            pkt.v[3].xyz.y = xy[2].y;
            pkt.v[0].xyz.y = (u32)(xy[0].y - r0);
            pkt.v[1].xyz.y = (u32)(xy[2].y - r2);
            pkt.v[0].xyz.x = pkt.v[2].xyz.x = xy[0].x;
            pkt.v[1].xyz.x = pkt.v[3].xyz.x = xy[2].x;
            func_002075F0((s32)&pkt, ot, (u32)dep[0]);
            pkt.v[0].xyz.y = (u32)(xy[0].y + r0);
            pkt.v[1].xyz.y = (u32)(xy[2].y + r2);
            func_002075F0((s32)&pkt, ot, (u32)dep[0]);
            pkt.v[0].xyz.x = (u32)(xy[0].x - r0);
            pkt.v[1].xyz.x = (u32)(xy[2].x - r2);
            pkt.v[2].xyz.x = xy[0].x;
            pkt.v[3].xyz.x = xy[2].x;
            pkt.v[0].xyz.y = pkt.v[2].xyz.y = xy[0].y;
            pkt.v[1].xyz.y = pkt.v[3].xyz.y = xy[2].y;
            func_002075F0((s32)&pkt, ot, (u32)dep[0]);
            pkt.v[0].xyz.x = (u32)(xy[0].x + r0);
            pkt.v[1].xyz.x = (u32)(xy[2].x + r2);
            func_002075F0((s32)&pkt, ot, (u32)dep[0]);
        }
        if (!(e->ext1 <= 0.0f)) {
            pkt.v[0].xyz.z = pkt.v[2].xyz.z = xy[1].z;
            pkt.v[1].xyz.z = pkt.v[3].xyz.z = xy[3].z;
            pkt.v[2].xyz.y = xy[1].y;
            pkt.v[3].xyz.y = xy[3].y;
            pkt.v[0].xyz.y = (u32)(xy[1].y - r1);
            pkt.v[1].xyz.y = (u32)(xy[3].y - r2);
            pkt.v[0].xyz.x = pkt.v[2].xyz.x = xy[1].x;
            pkt.v[1].xyz.x = pkt.v[3].xyz.x = xy[3].x;
            func_002075F0((s32)&pkt, ot, (u32)dep[1]);
            pkt.v[0].xyz.y = (u32)(xy[1].y + r1);
            pkt.v[1].xyz.y = (u32)(xy[3].y + r2);
            func_002075F0((s32)&pkt, ot, (u32)dep[1]);
            pkt.v[0].xyz.x = (u32)(xy[1].x - r1);
            pkt.v[1].xyz.x = (u32)(xy[3].x - r2);
            pkt.v[2].xyz.x = xy[1].x;
            pkt.v[3].xyz.x = xy[3].x;
            pkt.v[0].xyz.y = pkt.v[2].xyz.y = xy[1].y;
            pkt.v[1].xyz.y = pkt.v[3].xyz.y = xy[3].y;
            func_002075F0((s32)&pkt, ot, (u32)dep[1]);
            pkt.v[0].xyz.x = (u32)(xy[1].x + r1);
            pkt.v[1].xyz.x = (u32)(xy[3].x + r2);
            func_002075F0((s32)&pkt, ot, (u32)dep[1]);
        }
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/mod/b285", func_01E03B50_b285);

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

static s32 func_01E049C0_b285(Rib_b029_01E02B80 *arg0, s32 id __attribute__((aligned(8))), s32 n) {
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
    extern Uvs_b029_01E02B80 D_01E06910_b285;
    Uvs_b029_01E02B80 tbl = D_01E06910_b285;
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

/* OVL_WARM: compile warm (its (u32) cast is jal fptoui, func_001A23B0) */

/* shape b131:01E05D00, 513 insns: b059:01E00440 / b032:01E02820 at -O4 with the texture table as a local initialiser: draws n ring/cone emitters (0x48 bytes each): a quarter ring of up to 9
   segments between an inner radius at height y+dy and an outer one at y, mirrored into four quadrants as quads;
   texture page from a 4-entry module table by e->type, STQ from the page rectangle (types 1-3) or func_00101EE0 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b131_01E05D00;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    f32 s, t;
    Xyz_b131_01E05D00 xyz;
} Vtx_b131_01E05D00;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b131_01E05D00 v[4];
    u8 tail[0x20];
} Pkt_b131_01E05D00;

typedef struct {
    s32 id;
    u8 sub;
    u8 pad5[3];
    s32 u, w, v, h;
} Tex_b131_01E05D00;

typedef struct {
    Tex_b131_01E05D00 e[4];
} Tab_b131_01E05D00;

typedef struct {
    u8 b, g, r, a;
} Col_b131_01E05D00;

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
    Col_b131_01E05D00 c0;
    Col_b131_01E05D00 c1;
    Vec4f pos;
    Vec4f rot;
} Emit_b131_01E05D00;

static s32 func_01E054A0_b285(void *arg0, s32 ot __attribute__((aligned(8))), s32 n) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_0020BC00(void *, void *);
    extern void func_00101BA0(void *, void *);
    f32 mat2[16];
    f32 mat[16];
    Vec4f ab[2][10];
    Vec4f c[4];
    f32 depth[4];
    extern Tab_b131_01E05D00 D_01E06930_b285;
    Tab_b131_01E05D00 tab = D_01E06930_b285;
    Tex_b131_01E05D00 td;
    Pkt_b131_01E05D00 pkt __attribute__((aligned(8)));
    u8 bl[4];
    Emit_b131_01E05D00 *e;
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
            ab[0][j].x = r1 * cs;
            ab[0][j].z = r1 * sn;
            ab[0][j].y = e->y + e->dy;
            ab[1][j].x = r2 * cs;
            ab[1][j].z = r2 * sn;
            ab[1][j].y = e->y;
        }
        ((Pkt_b131_01E05D00 *)(s32)&pkt)->count = 0x34;
        ((Pkt_b131_01E05D00 *)(s32)&pkt)->tag = 0xC;
        ((Pkt_b131_01E05D00 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Pkt_b131_01E05D00 *)(s32)&pkt)->pad = 0;
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
        c[0].y = c[1].y = ab[0][0].y;
        c[2].y = c[3].y = ab[1][0].y;
        for (j = 0; j < nseg; j++) {
            for (k = 0; k < 4; k++) {
                switch (k) {
                case 0:
                    c[0].x = ab[0][j].x;
                    c[1].x = ab[0][j + 1].x;
                    c[2].x = ab[1][j].x;
                    c[3].x = ab[1][j + 1].x;
                    c[0].z = ab[0][j].z;
                    c[1].z = ab[0][j + 1].z;
                    c[2].z = ab[1][j].z;
                    c[3].z = ab[1][j + 1].z;
                    break;
                case 1:
                    c[0].x = -ab[0][j].x;
                    c[1].x = -ab[0][j + 1].x;
                    c[2].x = -ab[1][j].x;
                    c[3].x = -ab[1][j + 1].x;
                    break;
                case 2:
                    c[0].z = -ab[0][j].z;
                    c[1].z = -ab[0][j + 1].z;
                    c[2].z = -ab[1][j].z;
                    c[3].z = -ab[1][j + 1].z;
                    break;
                case 3:
                    c[0].x = ab[0][j].x;
                    c[1].x = ab[0][j + 1].x;
                    c[2].x = ab[1][j].x;
                    c[3].x = ab[1][j + 1].x;
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

INCLUDE_ASM("asm/nonmatchings/mod/b285", func_01E05CB0_b285);

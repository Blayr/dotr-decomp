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

static void func_01E00080_b198(Obj_b010_01E00080 *o) {
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

/* shape b010:01E04D20, 646 insns, 49 copies: update and draw a pool of particles (0x44 bytes each): move,
   floor bounce, colour and frame, project, then one textured sprite whose corners follow the flip bits */

typedef struct Part_b010_01E04D20 {
    u8 age;
    u8 b1;
    u8 life;
    u8 b3;
    u8 flags;
    u8 follow;
    u8 b6[2];
    u8 tex;
    u8 frame;
    u8 anim;
    u8 bB;
    u8 r, g, b, a;
    f32 size;
    f32 grow;
    f32 grav;
    f32 floor;
    f32 pos[3];
    f32 vel[3];
    f32 acc[3];
} Part_b010_01E04D20;

typedef struct Xyz_b010_01E04D20 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b010_01E04D20;

typedef struct Pk_b010_01E04D20 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    u64 st;
    Xyz_b010_01E04D20 v[4];
    u64 pad60[3];
} Pk_b010_01E04D20;

typedef struct Buf_b010_01E04D20 {
    u64 tag;
    Pk_b010_01E04D20 pk;
} Buf_b010_01E04D20;

typedef struct Uvs_b010_01E04D20 {
    u8 b0[5];
    u8 b5;
    u8 pad6[0x12];
} Uvs_b010_01E04D20;

typedef struct Scr_b010_01E04D20 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Scr_b010_01E04D20;

static inline void b010_01E04D20_tag(Pk_b010_01E04D20 *p, s32 size, s32 flags, u64 regs) {
    p->flags = flags;
    p->size = size;
    p->regs = regs;
    p->pad4 = 0;
}

#pragma optimization_level 2

static s32 func_01E00410_b198(Part_b010_01E04D20 *arg0, s32 id, s32 n) {
    extern void func_001020B0();
    extern void func_00101D20();
    extern s32 func_00205440();
    extern void func_00101BA0();
    Part_b010_01E04D20 *p = arg0;
    s32 i;
    s32 tex;
    s32 life;
    s32 frame;
    f32 half;
    f32 zf;
    u16 c;

    f32 m[4][4];
    Vec4f pos;
    Vec4f tmp;
    Uvs_b010_01E04D20 uvs;
    Pk_b010_01E04D20 pk __attribute__((aligned(8)));
    Scr_b010_01E04D20 scr;
    f32 depth;

    for (i = 0; i < n; i++) {
        if (i != 0) {
            p++;
        }
        if (func_00101AF0(p) == 0) {
            continue;
        }
        tex = func_00202BF0(5, p->tex);
        p->vel[0] += p->acc[0];
        p->vel[1] += p->acc[1] + p->grav;
        p->vel[2] += p->acc[2];
        p->pos[0] += p->vel[0];
        p->pos[1] += p->vel[1];
        p->pos[2] += p->vel[2];
        p->size += p->grow;
        if (p->pos[1] < p->floor) {
            p->pos[1] = p->floor;
            if (p->flags & 2) {
                p->vel[1] = -(0.7f * p->vel[1]);
            }
        }
        if (p->follow != 0) {
            func_00101BA0(p, &tmp);
            p->pos[0] = tmp.x;
            p->pos[1] = tmp.y;
            p->pos[2] = tmp.z;
        }
        pos.x = p->pos[0];
        pos.y = p->pos[1];
        pos.z = p->pos[2];
        func_0020EB40(m);
        ((Pk_b010_01E04D20 *)(u32)&pk)->flags = 0x24;
        ((Pk_b010_01E04D20 *)(u32)&pk)->size = 9;
        ((Pk_b010_01E04D20 *)(u32)&pk)->regs = ((u64)4 << 32) | 0x24242421;
        ((Pk_b010_01E04D20 *)(u32)&pk)->pad4 = 0;
        pk.r = p->b;
        pk.g = p->g;
        pk.b = p->r;
        pk.q = 1.0f;
        life = p->life - p->age;
        frame = p->frame;
        if (p->flags & 1) {
            frame = (u8)func_001022D0(p->anim, life);
            if (p->flags & 4) {
                p->flags &= 0xCF;
                p->flags |= (u8)(((func_0019A5C8() >> 4) & 3) << 4);
            }
        }
        uvs.b5 = p->bB;
        func_001020B0(&uvs, frame, p->anim);
        func_00101D20(&pk, &uvs, tex);
        pk.a = p->a;
        if (!(p->flags & 0x40) && p->age < 0x10) {
            pk.a = (p->a >> 4) * p->age;
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
            zf = 0.0f;
        } else {
            pk.v[0].z = pk.v[1].z = pk.v[2].z = pk.v[3].z = scr.z;
            zf = depth;
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
        func_002075F0((s32)&pk, id, (u32)(zf));
    }
    return 1;
}
#pragma optimization_level reset

INCLUDE_ASM("asm/nonmatchings/mod/b198", func_01E00E30_b198);

INCLUDE_ASM("asm/nonmatchings/mod/b198", func_01E020B0_b198);

INCLUDE_ASM("asm/nonmatchings/mod/b198", func_01E02C30_b198);

/* OVL_CFLAGS: -O2,p -sdatathreshold 0 -relax_pointers */
/* OVL_WARM: compile warm (its (u32) cast is jal fptoui, func_001A23B0) */

/* shape b106:01E042B0, 461 insns: draws the module's flare entities (0x24 bytes each) as screen sprites: one
   packet set up on the first live entity, then per entity the point above its object (towards the camera,
   flipped by flags & 1) is projected and, when on screen, up to cnt quads per side are drawn stepping out by
   (dx, dy) * 16 from the screen centre. Sends the list if anything was live. */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b106_01E042B0;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b106_01E042B0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Uv_b106_01E042B0 uv;
    Xyz_b106_01E042B0 xyz;
} Vtx_b106_01E042B0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b106_01E042B0 v[4];
    u8 tail[8];
} Pkt_b106_01E042B0;

typedef struct {
    u8 life;
    u8 pad1;
    u8 span;
    u8 pad3;
    u8 flags;
    u8 pad5[3];
    u8 len;
    u8 blend;
    u8 dx;
    u8 dy;
    s32 obj;
    u8 pad10[3];
    u8 alpha;
    u8 pad14[0x10];
} Flare_b106_01E042B0;

#pragma optimization_level 2

static s32 func_01E037C0_b198(Flare_b106_01E042B0 *arg0, s32 ot __attribute__((aligned(8))), s32 n) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_001F7060(s32, s32, void *, void *);
    extern Vec4f *func_001F9AD0(s32);
    extern void func_001F53C0(s32, s32, void *);
    extern f32 func_001F5860(s32);
    extern void func_00101A00(void *, void *);
    extern void func_0020CDD0(void *, void *, void *);
    extern s32 func_00101770(void *);
    extern void func_00101C80(void *, u8 *);
    Flare_b106_01E042B0 *e = arg0;
    f32 mat[16];
    Vec4f pos;
    Vec4f d;
    Vec4f p;
    Vec4f cam;
    f32 m2[16];
    u8 td[0x20];
    struct {
        Pkt_b106_01E042B0 pk;
        s32 a[2];
        s32 b[2];
    } w;
    Xyz_b106_01E042B0 xy;
    f32 depth;
    u8 bl[4];
    s32 i;
    s32 list;
    s32 any;
    s32 j;
    s32 k;
    s32 cnt;
    s32 y;
    s32 x;

    list = func_00207F60();
    any = 0;
    for (i = 0; i < n; i++) {
        if (i != 0) {
            e++;
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        if (any == 0) {
            ((Pkt_b106_01E042B0 *)(s32)&w.pk)->count = 0x34;
            ((Pkt_b106_01E042B0 *)(s32)&w.pk)->tag = 0xC;
            ((Pkt_b106_01E042B0 *)(s32)&w.pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
            ((Pkt_b106_01E042B0 *)(s32)&w.pk)->pad = 0;
            w.pk.v[0].r = w.pk.v[1].r = w.pk.v[2].r = w.pk.v[3].r = w.pk.v[0].g = w.pk.v[1].g = w.pk.v[2].g = w.pk.v[3].g =
                w.pk.v[0].b = w.pk.v[1].b = w.pk.v[2].b = w.pk.v[3].b = w.pk.v[0].a = w.pk.v[1].a = w.pk.v[2].a =
                    w.pk.v[3].a = 0x80;
            w.pk.v[0].q = w.pk.v[1].q = w.pk.v[2].q = w.pk.v[3].q = 1.0f;
            w.pk.v[0].xyz.z = w.pk.v[1].xyz.z = w.pk.v[2].xyz.z = w.pk.v[3].xyz.z = 0xFFFFFF;
            w.pk.v[0].xyz.f = w.pk.v[1].xyz.f = w.pk.v[2].xyz.f = w.pk.v[3].xyz.f = 0;
            func_00208460();
            func_001F7060(e->obj, 0, w.a, w.b);
            func_00208460();
            any = 1;
            ((Pkt_b106_01E042B0 *)(s32)&w.pk)->count |= 0x800;
            ((Uv_b106_01E042B0 *)(s32)&w.pk.v[0].uv)->u = 0;
            ((Uv_b106_01E042B0 *)(s32)&w.pk.v[0].uv)->v = 0;
            ((Uv_b106_01E042B0 *)(s32)&w.pk.v[1].uv)->u = 0x2800;
            ((Uv_b106_01E042B0 *)(s32)&w.pk.v[1].uv)->v = 0;
            ((Uv_b106_01E042B0 *)(s32)&w.pk.v[2].uv)->u = 0;
            ((Uv_b106_01E042B0 *)(s32)&w.pk.v[2].uv)->v = 0x1C00;
            ((Uv_b106_01E042B0 *)(s32)&w.pk.v[3].uv)->u = 0x2800;
            ((Uv_b106_01E042B0 *)(s32)&w.pk.v[3].uv)->v = 0x1C00;
        }
        func_0020EB40(mat);
        cam = *func_001F9AD0(0);
        func_001F53C0(1, e->obj, &pos);
        d.x = cam.x - pos.x;
        d.y = cam.y - pos.y;
        d.z = cam.z - pos.z;
        func_00101A00(&d, m2);
        d.x = d.z = 0.0f;
        d.y = func_001F5860(e->obj);
        if (e->flags & 1) {
            d.y *= -1.0f;
        }
        func_0020CDD0(&p, m2, &d);
        p.x += pos.x;
        p.y += pos.y;
        p.z += pos.z;
        if (func_00205440(&p, mat, &xy, &depth) != 0 && func_00101770(&xy) != 0) {
            w.pk.v[0].xyz.z = w.pk.v[1].xyz.z = w.pk.v[2].xyz.z = w.pk.v[3].xyz.z = xy.z;
            w.pk.v[0].xyz.f = w.pk.v[1].xyz.f = w.pk.v[2].xyz.f = w.pk.v[3].xyz.f = 0;
            td[5] = e->blend;
            func_00101C80(td, bl);
            func_002086D0(&w.pk, (u64)bl[0] | ((u64)bl[1] << 2) | ((u64)bl[2] << 4) | ((u64)bl[3] << 6));
            w.pk.v[0].a = w.pk.v[1].a = w.pk.v[2].a = w.pk.v[3].a = e->alpha;
            cnt = e->len >> 1;
            if (e->span - e->life + 1 < cnt) {
                cnt = e->span - e->life + 1;
            }
            if (e->life < cnt) {
                cnt = e->life;
            }
            for (k = 0; k < 2; k++) {
                for (j = 0; j < cnt; j++) {
                    if (k) {
                        x = e->dx * (j + 1);
                        y = e->dy * (j + 1);
                    } else {
                        x = -e->dx * (j + 1);
                        y = -e->dy * (j + 1);
                    }
                    w.pk.v[0].xyz.x = w.pk.v[2].xyz.x = (x << 4) + 27648.0f;
                    w.pk.v[1].xyz.x = w.pk.v[3].xyz.x = 37888.0f + (x << 4);
                    w.pk.v[0].xyz.y = w.pk.v[1].xyz.y = (y << 4) + 29184.0f;
                    w.pk.v[2].xyz.y = w.pk.v[3].xyz.y = 36352.0f + (y << 4);
                    func_002075F0(&w.pk, 0, (u32)depth);
                }
            }
        }
    }
    if (any) {
        func_00207FD0(list, ot, 0);
    }
    return 1;
}
#pragma optimization_level reset

INCLUDE_ASM("asm/nonmatchings/mod/b198", func_01E03F00_b198);

/* OVL_CFLAGS: -O2,p -sdatathreshold 0 -relax_pointers */
/* OVL_WARM: compile warm (its (u32) cast is jal fptoui, func_001A23B0) */

/* shape b095:01E02120, 345 insns, 17 copies: draws n billboards (0x3C-byte emitters): a quad that shrinks with age
   and grows along y, turned by the emitter's rotation at its position, perspective STQ, texture frame from
   func_001020B0, blend from func_00101C80 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b095_01E02120;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    f32 s, t;
    Xyz_b095_01E02120 xyz;
} Vtx_b095_01E02120;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b095_01E02120 v[4];
    u8 tail[0x20];
} Pkt_b095_01E02120;

typedef struct {
    u8 pad0[5];
    u8 b5;
    u8 pad6[2];
    s32 u, w, v, h;
} Tex_b095_01E02120;

typedef struct {
    u8 life;
    u8 pad1;
    u8 max;
    u8 pad3;
    u8 flags;
    u8 pad5[3];
    u8 texid;
    u8 b9;
    u8 bA;
    u8 bB;
    u8 b, g, r, a;
    f32 r0;
    f32 w0;
    f32 dw;
    Vec4f rot;
    Vec4f pos;
} Emit_b095_01E02120;

#pragma optimization_level 2

static s32 func_01E04910_b198(void *arg0, s32 ot, s32 n) {
    extern void func_001020B0();
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_0020BC00(void *, void *);
    extern void func_00101BA0(void *, void *);
    f32 mat[16];
    f32 mat2[16];
    Vec4f c[4];
    f32 depth[4];
    Tex_b095_01E02120 td;
    Pkt_b095_01E02120 pkt __attribute__((aligned(8)));
    u8 bl[4];
    Emit_b095_01E02120 *e;
    s32 i;
    void *tex;
    s32 d;
    f32 r0;
    f32 h;
    f32 w;
    s32 life;
    f32 q1;
    f32 q2;
    f32 q3;
    f32 z;

    e = arg0;
    for (i = 0; i < n; i++) {
        if (i != 0) {
            e++;
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        tex = (void *)func_00202BF0(5, e->texid);
        d = e->max - e->life;
        r0 = e->r0;
        h = r0 - d * (r0 / e->max);
        w = e->w0 + e->dw * d;
        c[0].z = c[1].z = c[2].z = c[3].z = 0.0f;
        c[0].x = c[2].x = -h;
        c[1].x = c[3].x = h;
        c[0].y = c[1].y = -w;
        c[2].y = c[3].y = w;
        func_00101BA0(e, &e->pos);
        func_0020EB40(mat);
        func_0020C940(mat2, NULL, &e->rot, &e->pos);
        func_0020BC00(mat, mat2);
        ((Pkt_b095_01E02120 *)(s32)&pkt)->count = 0x34;
        ((Pkt_b095_01E02120 *)(s32)&pkt)->tag = 0xC;
        ((Pkt_b095_01E02120 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Pkt_b095_01E02120 *)(s32)&pkt)->pad = 0;
        pkt.v[0].r = pkt.v[1].r = pkt.v[2].r = pkt.v[3].r = e->r;
        pkt.v[0].g = pkt.v[1].g = pkt.v[2].g = pkt.v[3].g = e->g;
        pkt.v[0].b = pkt.v[1].b = pkt.v[2].b = pkt.v[3].b = e->b;
        life = e->life;
        if (!(e->flags & 0x40) && life < 8) {
            pkt.v[0].a = pkt.v[1].a = pkt.v[2].a = pkt.v[3].a = (e->a >> 3) * life;
        } else {
            pkt.v[0].a = pkt.v[1].a = pkt.v[2].a = pkt.v[3].a = e->a;
        }
        if (func_00205440(&c[0], mat, &pkt.v[0].xyz, &depth[0]) != 0 &&
            func_00205440(&c[1], mat, &pkt.v[1].xyz, &depth[1]) != 0 &&
            func_00205440(&c[2], mat, &pkt.v[2].xyz, &depth[2]) != 0 &&
            func_00205440(&c[3], mat, &pkt.v[3].xyz, &depth[3]) != 0) {
            td.b5 = e->bB;
            func_001020B0(&td, e->bA, e->b9);
            pkt.v[0].q = 1.0f / depth[0];
            q1 = 1.0f / depth[1];
            pkt.v[1].q = q1;
            q2 = 1.0f / depth[2];
            pkt.v[2].q = q2;
            q3 = 1.0f / depth[3];
            pkt.v[3].q = q3;
            pkt.v[0].s = 0.0f;
            pkt.v[0].t = 0.0f;
            pkt.v[1].s = q1;
            pkt.v[1].t = 0.0f;
            pkt.v[2].s = 0.0f;
            pkt.v[2].t = q2;
            pkt.v[3].s = q3;
            pkt.v[3].t = q3;
            func_00208CB0(&pkt, (u64)0xA | ((u64)td.u << 4) | ((u64)(td.w - 1) << 14) | ((u64)td.v << 24) |
                                    ((u64)(td.h - 1) << 34));
            func_00101C80(&td, bl);
            func_002086D0(&pkt, (u64)bl[0] | ((u64)bl[1] << 2) | ((u64)bl[2] << 4) | ((u64)bl[3] << 6));
            func_00208700(&pkt, tex, 1);
            if (e->flags & 0x80) {
                pkt.v[0].xyz.z = pkt.v[1].xyz.z = pkt.v[2].xyz.z = pkt.v[3].xyz.z = 0xFFFFFE;
                z = 0.0f;
            } else {
                z = (depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f;
            }
            func_002075F0((s32)&pkt, ot, (u32)z);
        }
    }
    return 1;
}
#pragma optimization_level reset

INCLUDE_ASM("asm/nonmatchings/mod/b198", func_01E04E80_b198);

/* OVL_CFLAGS: -O2,p -sdatathreshold 0 -relax_pointers */

/* shape b198:01E05C30, 260 insns, 4 copies: moves n trail emitters (0x7C bytes each) and drops trail particles into the
   emitter's pool: one at the head (flag 1) or four along a spline through the last three positions. */

typedef struct {
    s32 n;
    f32 x[8];
    f32 y[8];
    f32 z[8];
    Vec4f out[28];
} Spline_b198_01E05C30;

typedef struct {
    u8 r, g, b, a;
} C4_b198_01E05C30;

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
    C4_b198_01E05C30 col;
    Vec4f pos;
    u8 pad38[0x10];
    u8 x48[0x10];
} Part_b198_01E05C30;

typedef struct {
    u8 life;
    u8 pad1;
    u8 max;
    u8 pad3;
    u8 flags;
    u8 follow;
    u8 pad6[2];
    Part_b198_01E05C30 *list;
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
    C4_b198_01E05C30 col;
    Vec4f pos;
    Vec4f prev;
    Vec4f prev2;
    Vec4f vel;
    Vec4f off;
} Trail_b198_01E05C30;

#pragma optimization_level 2

static s32 func_01E05C30_b198(void *arg0, s32 arg1, s32 n) {
    extern s32 func_00101AF0(void *);
    extern void func_00101BA0(void *, void *);
    extern void func_00102550(void *);
    extern s32 func_00101C30(void *, s32, s32);
    extern void func_00101AD0(void *, s32, s32, s32);
    extern void func_00101940(void *, void *);
    Spline_b198_01E05C30 sp;
    Vec4f tmp;
    Trail_b198_01E05C30 *e;
    s32 i;
    s32 k;
    s32 cnt;
    s32 idx;

    e = arg0;
    for (i = 0; i < n; i++) {
        if (i != 0) {
            e = (Trail_b198_01E05C30 *)((u8 *)e + 0x7C);
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
                e->list[idx].f14 = e->f18;
                e->list[idx].f18 = e->f1C;
                e->list[idx].flags = 5;
                if (e->flags & 2) {
                    e->list[idx].flags |= 8;
                }
                e->list[idx].bC = e->b16;
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

INCLUDE_ASM("asm/nonmatchings/mod/b198", func_01E06040_b198);

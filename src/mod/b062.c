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

static void func_01E00080_b062(Fx_b005_01E00080 *o) {
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

INCLUDE_ASM("asm/nonmatchings/mod/b062", func_01E003A0_b062);

INCLUDE_ASM("asm/nonmatchings/mod/b062", func_01E00DF0_b062);

INCLUDE_ASM("asm/nonmatchings/mod/b062", func_01E01660_b062);

INCLUDE_ASM("asm/nonmatchings/mod/b062", func_01E020A0_b062);

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

static s32 func_01E02A10_b062(Obj_b029_01E026A0 *o, s32 tex, s32 d, s32 h) {
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

INCLUDE_ASM("asm/nonmatchings/mod/b062", func_01E02EF0_b062);

INCLUDE_ASM("asm/nonmatchings/mod/b062", func_01E039D0_b062);

INCLUDE_ASM("asm/nonmatchings/mod/b062", func_01E042E0_b062);

/* OVL_WARM */

/* shape b062:01E05220, 508 insns, 3 copies: moves n spark emitters (0x60 bytes each: position, velocity, turning angles,
   growing size and speed) and draws count square sprites per emitter, each pushed out from the emitter
   along a direction from its random table, scaled by the speed (optionally jittered); frame from age or
   fixed, alpha fading at the end. */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b062_01E05220;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    struct {
        u64 tc;
        Xyz_b062_01E05220 p;
    } v[4];
    u8 tail[0x20];
} Pkt_b062_01E05220;

typedef struct {
    u8 pad0[5];
    u8 page;
    u8 pad6[2];
    s32 u, w, v, h;
    u8 pad18[8];
} Tex_b062_01E05220;

typedef struct {
    u8 life;
    u8 pad1;
    u8 max;
    u8 pad3;
    u8 flags;
    u8 pad5[3];
    u8 count;
    u8 seed;
    u8 texid;
    u8 frame;
    u8 bC;
    u8 bD;
    u8 padE[2];
    u8 *tbl;
    f32 speed;
    f32 dspeed;
    f32 rise;
    f32 size;
    f32 dsize;
    u8 b, g, r, a;
    s32 rot[4];
    f32 pos[3];
    f32 vel[3];
    f32 rv[3];
} Spark_b062_01E05220;

static s32 func_01E05220_b062(void *arg0, s32 ot, s32 n) {
    extern s32 func_00101AF0(void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00101BA0(void *, void *);
    extern void func_0020EB40(void *);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020BC00(void *, void *);
    extern void func_001020B0(void *, s32, s32);
    extern void func_00101D20(void *, void *, void *);
    extern void func_00101A00(void *, void *);
    extern void func_0020CDD0(void *, void *, void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern s32 func_00101600(void *);
    extern f32 func_001018E0(f32, f32);
    extern void func_002075F0(void *, s32, s32);
    f32 mat2[16];
    f32 mat[16];
    f32 rm[16];
    Vec4f out;
    Vec4f p;
    Vec4f d;
    Tex_b062_01E05220 td;
    Pkt_b062_01E05220 pkt __attribute__((aligned(8)));
    f32 dep;
    Spark_b062_01E05220 *e;
    s32 i;
    void *tex;
    u8 seed;
    s32 fr;
    s32 j;
    f32 sp;
    f32 h;

    e = arg0;
    for (i = 0; i < n; i++) {
        if (i != 0) {
            e = (Spark_b062_01E05220 *)((u8 *)e + 0x60);
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        tex = (void *)func_00202BF0(5, e->texid);
        e->pos[0] += e->vel[0];
        e->pos[1] += e->vel[1];
        e->pos[2] += e->vel[2];
        e->rot[0] += e->rv[0];
        e->rot[1] += e->rv[1];
        e->rot[2] += e->rv[2];
        e->size += e->dsize;
        e->speed += e->dspeed;
        p.x = e->pos[0];
        p.y = e->pos[1];
        p.z = e->pos[2];
        func_00101BA0(e, &p);
        func_0020EB40(mat);
        func_0020C940(mat2, NULL, e->rot, &p);
        func_0020BC00(mat, mat2);
        seed = e->seed;
        fr = e->max - e->life;
        ((Pkt_b062_01E05220 *)(s32)&pkt)->count = 0x24;
        ((Pkt_b062_01E05220 *)(s32)&pkt)->tag = 9;
        ((Pkt_b062_01E05220 *)(s32)&pkt)->regs = ((u64)4 << 32) | 0x24242421;
        ((Pkt_b062_01E05220 *)(s32)&pkt)->pad = 0;
        pkt.r = e->r;
        pkt.g = e->g;
        pkt.b = e->b;
        pkt.q = 1.0f;
        fr = (e->flags & 1) ? fr & 7 : e->frame;
        td.page = e->bD;
        func_001020B0(&td, fr, e->bC);
        func_00101D20(&pkt, &td, tex);
        pkt.a = e->a;
        if (!(e->flags & 0x40) && e->life < 8) {
            pkt.a = (e->a >> 3) * e->life;
        }
        p.x = p.y = p.z = 0.0f;
        for (j = 0; j < e->count; j++) {
            if (e->flags & 8) {
                sp = e->speed;
            } else {
                sp = e->speed * (e->tbl[seed++] / 255.0f);
                if (e->flags & 4) {
                    sp = 0.5f * (sp + e->speed);
                }
            }
            if (e->flags & 2) {
                d.x = e->tbl[seed] - e->tbl[seed + 1];
                d.z = e->tbl[seed + 2] - e->tbl[seed + 3];
                d.y = 0.0f;
                p.x = sp;
                seed += 4;
            } else {
                d.x = e->tbl[seed] - e->tbl[seed + 1];
                d.z = e->tbl[seed + 2] - e->tbl[seed + 3];
                d.y = e->tbl[seed + 4] - e->tbl[seed + 5];
                p.y = sp;
                seed += 6;
            }
            func_00101A00(&d, rm);
            func_0020CDD0(&out, rm, &p);
            if (e->flags & 2) {
                out.y += (e->rise * e->tbl[seed++]) / 255.0f;
            }
            if (func_00205440(&out, mat, &pkt.v[0].p, &dep) == 0) {
                continue;
            }
            if (func_00101600(&pkt.v[0].p) == 0) {
                continue;
            }
            h = func_001018E0(e->size, dep);
            pkt.v[1].p.x = pkt.v[0].p.x + h;
            pkt.v[1].p.y = pkt.v[0].p.y - h;
            pkt.v[2].p.x = pkt.v[0].p.x - h;
            pkt.v[2].p.y = pkt.v[0].p.y + h;
            pkt.v[3].p.x = pkt.v[0].p.x + h;
            pkt.v[3].p.y = pkt.v[0].p.y + h;
            pkt.v[0].p.x = pkt.v[0].p.x - h;
            pkt.v[0].p.y = pkt.v[0].p.y - h;
            pkt.v[1].p.z = pkt.v[2].p.z = pkt.v[3].p.z = pkt.v[0].p.z;
            pkt.v[0].p.f = pkt.v[1].p.f = pkt.v[2].p.f = pkt.v[3].p.f = 1;
            func_002075F0(&pkt, ot, (u32)dep);
        }
    }
    return 1;
}

/* shape b062:01E05A10, 104 insns: places the 30 ring pieces: for each live piece (flagged when under 4) takes its matrix, a
   radius of (level - 4) times its scale (not below 0) and an angle of 45 per index plus 16 per step, and sets its position to
   the centre plus the turned offset */

typedef struct {
    u8 n;
    u8 pad1;
    u8 step;
    u8 pad3;
    u8 flags;
    u8 pad5[0x33];
    f32 x, y, z;
} Piece_b062_01E05A10;

typedef struct {
    u8 m[0xC];
} Mtx_b062_01E05A10;

typedef struct {
    u8 pad0[0x60];
    f32 cx, cy, cz;
    u8 pad6C[0x6064 - 0x6C];
    Piece_b062_01E05A10 pieces[30];
    u8 pad[0x775C - 0x6064 - 30 * 0x44];
    Mtx_b062_01E05A10 mats[30];
    f32 scale[30];
} Scene_b062_01E05A10;

static void func_01E05A10_b062(Scene_b062_01E05A10 *s) {
    extern void func_00101A00(void *, void *);
    extern f32 func_001A6898(f32);
    extern f32 func_001A6A88(f32);
    extern void func_0020CDD0(void *, void *, void *);
    Vec4f v;
    Vec4f out;
    f32 mtx[16];
    f32 r;
    f32 a;
    s32 d;
    s32 i;

    for (i = 0; i < 0x1E; i++) {
        if (s->pieces[i].n != 0) {
            if (s->pieces[i].n < 4) {
                s->pieces[i].flags |= 8;
            }
            func_00101A00(&s->mats[i], mtx);
            d = s->pieces[i].step - s->pieces[i].n;
            r = (f32)(s->pieces[i].n - 4) * s->scale[i];
            if (r < 0.0f) {
                r = 0.0f;
            }
            a = (3.1415927f * (45.0f * i + 16.0f * d)) / 180.0f;
            v.x = r * func_001A6898(a);
            v.z = 0.0f;
            v.y = r * func_001A6A88(a);
            func_0020CDD0(&out, mtx, &v);
            s->pieces[i].x = s->cx + out.x;
            s->pieces[i].y = s->cy + out.y;
            s->pieces[i].z = s->cz + out.z;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b062", func_01E05BB0_b062);

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

static void func_01E00080_b706(Fx_b005_01E00080 *o) {
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

static s32 func_01E003A0_b706(Obj_b029_01E026A0 *o, s32 tex, s32 d, s32 h) {
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

/* OVL_WARM */

/* shape b457:01E03790, 221 insns, 4 copies: draws a full-screen black fade quad: alpha by mode (1 fade out over the
   life, 2 fade in, else half-white 0x80), optional loop (restart life, flip mode), halved by flag 8; flags 0x20 /
   0x40 clear the alpha of the bottom / top edge. */

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b457_01E03790;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b457_01E03790 v[4];
    u8 tail[8];
} Pkt_b457_01E03790;

typedef struct {
    u8 life;
    u8 pad1;
    u8 max;
    u8 pad3;
    u8 flags;
} Fade_b457_01E03790;

static s32 func_01E00880_b706(Fade_b457_01E03790 *f, s32 ot) {
    extern s32 func_00101AF0(void *);
    extern void func_002075F0(void *, s32, s32);
    Pkt_b457_01E03790 pkt __attribute__((aligned(8)));
    u8 flags;
    u8 a;

    if (func_00101AF0(f) == 0) {
        return 0;
    }
    ((Pkt_b457_01E03790 *)(s32)&pkt)->count = 0x14;
    ((Pkt_b457_01E03790 *)(s32)&pkt)->tag = 8;
    ((Pkt_b457_01E03790 *)(s32)&pkt)->regs = 0x41414141;
    ((Pkt_b457_01E03790 *)(s32)&pkt)->pad = 0;
    flags = f->flags;
    switch (flags & 7) {
    case 1:
        a = 128.0f / f->max * f->life;
        break;
    case 2:
        a = ((f->max - f->life) << 7) / f->max;
        break;
    case 4:
    default:
        a = 0x80;
        break;
    }
    if (f->life == 1 && (flags & 0x80)) {
        f->life = f->max;
        if (f->flags & 1) {
            f->flags = 2;
        } else {
            f->flags = 1;
        }
    }
    if (f->flags & 8) {
        a >>= 1;
    }
    pkt.v[0].b = pkt.v[1].b = pkt.v[2].b = pkt.v[3].b = 0;
    pkt.v[0].g = pkt.v[1].g = pkt.v[2].g = pkt.v[3].g = 0;
    pkt.v[0].r = pkt.v[1].r = pkt.v[2].r = pkt.v[3].r = 0;
    pkt.v[0].q = pkt.v[1].q = pkt.v[2].q = pkt.v[3].q = 1.0f;
    pkt.v[0].z = pkt.v[1].z = pkt.v[2].z = pkt.v[3].z = 0xFFFFFF;
    func_002086D0(&pkt, 0x44);
    pkt.v[0].a = pkt.v[1].a = pkt.v[2].a = pkt.v[3].a = a;
    if (f->flags & 0x20) {
        pkt.v[2].a = pkt.v[3].a = 0;
    }
    if (f->flags & 0x40) {
        pkt.v[0].a = pkt.v[1].a = 0;
    }
    pkt.v[0].x = pkt.v[2].x = 0x6C00;
    pkt.v[1].x = pkt.v[3].x = 0x9400;
    pkt.v[0].y = pkt.v[1].y = 0x7200;
    pkt.v[2].y = pkt.v[3].y = 0x8E00;
    func_002075F0(&pkt, ot, 0);
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/mod/b706", func_01E00C00_b706);

/* OVL_WARM */

/* shape b457:01E026E0, 756 insns: draws n lightning strips (0x20-byte emitters) along each emitter's point list:
   texture either a fixed atlas cell with its own blend (flag 1) or the emitter's animated cell; every projected
   segment becomes 2 or (life & 3) + 1 quads widened across the shorter screen axis, ends faded when flag 0xF.1;
   the corner order rotates with the segment (flag 4) or with age. Sibling of b070:01E03C10. */

typedef struct {
    f32 x, y, z;
} Vec3_b457_01E026E0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b457_01E026E0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    Xyz_b457_01E026E0 xyz;
} Vtx_b457_01E026E0;

typedef struct {
    u64 u : 14;
    u64 pad0 : 2;
    u64 v : 14;
    u64 pad1 : 34;
} UV_b457_01E026E0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b457_01E026E0 v[4];
    u8 tail[0x20];
} Pkt_b457_01E026E0;

typedef struct {
    s32 k0, k1;
    s32 u, w, v, h;
} Tex_b457_01E026E0;

typedef struct {
    u8 b5[5];
    u8 b5x;
    u8 pad6[0x12];
} Uvs_b457_01E026E0;

typedef struct {
    u8 life;
    u8 pad1;
    u8 max;
    u8 pad3;
    u8 flags;
    u8 pad5[3];
    u8 n;
    u8 texid;
    u8 frame;
    u8 bB;
    u8 anim;
    u8 wdiv;
    u8 step;
    u8 flags2;
    u8 pad10[4];
    f32 grow;
    u8 b, g, r, a;
    Vec3_b457_01E026E0 *pts;
} Strip_b457_01E026E0;

extern Tex_b457_01E026E0 D_01E072B0_b706;

static s32 func_01E01690_b706(void *arg0, s32 ot __attribute__((aligned(8))), s32 n) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_00101EE0(void *, void *, void *);
    extern void func_001020B0();
    extern void func_00101C80(void *, void *);
    Strip_b457_01E026E0 *e = arg0;
    f32 mat[16];
    Xyz_b457_01E026E0 s[3];
    Vec4f v;
    Uvs_b457_01E026E0 uvs;
    Tex_b457_01E026E0 tmpl;
    Pkt_b457_01E026E0 pkt __attribute__((aligned(8)));
    f32 depth[2];
    u8 bl[4];
    Vec3_b457_01E026E0 *pts;
    s32 i;
    void *tex;
    s32 j;
    s32 start;
    s32 end;
    s32 cnt;
    s32 rot;
    s32 k;
    s32 dx;
    s32 dy;
    f32 fdx;
    f32 fdy;
    f32 w;
    u32 c0;
    u32 c1;
    f32 z;

    tmpl = D_01E072B0_b706;
    for (i = 0; i < n; i++) {
        if (i != 0) {
            e++;
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        func_0020EB40(mat);
        ((Pkt_b457_01E026E0 *)(s32)&pkt)->count = 0x34;
        ((Pkt_b457_01E026E0 *)(s32)&pkt)->tag = 0xC;
        ((Pkt_b457_01E026E0 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Pkt_b457_01E026E0 *)(s32)&pkt)->pad = 0;
        pkt.v[0].r = pkt.v[1].r = pkt.v[2].r = pkt.v[3].r = e->r;
        pkt.v[0].g = pkt.v[1].g = pkt.v[2].g = pkt.v[3].g = e->g;
        pkt.v[0].b = pkt.v[1].b = pkt.v[2].b = pkt.v[3].b = e->b;
        pkt.v[0].q = pkt.v[1].q = pkt.v[2].q = pkt.v[3].q = 1.0f;
        if (e->flags & 1) {
            tex = (void *)func_00202BF0(4, 0xF);
            ((Pkt_b457_01E026E0 *)(s32)&pkt)->count |= 0x800;
            ((UV_b457_01E026E0 *)(s32)&pkt.v[0].st)->u = tmpl.u * 16;
            ((UV_b457_01E026E0 *)(s32)&pkt.v[0].st)->v = tmpl.h * 16;
            ((UV_b457_01E026E0 *)(s32)&pkt.v[1].st)->u = tmpl.u * 16;
            ((UV_b457_01E026E0 *)(s32)&pkt.v[1].st)->v = tmpl.v * 16;
            ((UV_b457_01E026E0 *)(s32)&pkt.v[2].st)->u = tmpl.w * 16;
            ((UV_b457_01E026E0 *)(s32)&pkt.v[2].st)->v = tmpl.h * 16;
            ((UV_b457_01E026E0 *)(s32)&pkt.v[3].st)->u = tmpl.w * 16;
            ((UV_b457_01E026E0 *)(s32)&pkt.v[3].st)->v = tmpl.v * 16;
            func_00208CB0(&pkt, (u64)0xA | ((u64)tmpl.u << 4) | ((u64)tmpl.w << 14) | ((u64)tmpl.v << 24) |
                                    ((u64)(tmpl.h - 1) << 34));
            func_00208700(&pkt, tex, 1);
            func_00101C80(&tmpl, bl);
            func_002086D0(&pkt, (u64)bl[0] | ((u64)bl[1] << 2) | ((u64)bl[2] << 4) | ((u64)bl[3] << 6));
        } else {
            tex = (void *)func_00202BF0(5, e->texid);
            uvs.b5x = e->bB;
            func_001020B0(&uvs, e->frame, e->anim);
            func_00101EE0(&pkt, &uvs, tex);
        }
        if (!(e->flags & 2) && e->life < e->n) {
            start = e->n - e->life;
        } else {
            start = 0;
        }
        if (e->step > 0 && e->max - e->life < e->n / e->step) {
            end = e->step * (e->max - e->life);
        } else {
            end = e->n;
        }
        pts = e->pts;
        for (j = start; j < end; j++) {
            pkt.v[0].a = pkt.v[1].a = pkt.v[2].a = pkt.v[3].a = e->a;
            if (e->flags2 & 1) {
                if (j == start) {
                    pkt.v[0].a = pkt.v[1].a = 0;
                }
                if (j == end - 1) {
                    pkt.v[2].a = pkt.v[3].a = 0;
                }
            }
            v.x = pts[j].x;
            v.y = pts[j].y;
            v.z = pts[j].z;
            if (func_00205440(&v, mat, &s[0], &depth[0]) == 0 || func_00101600(&s[0]) == 0) {
                continue;
            }
            v.x = pts[j + 1].x;
            v.y = pts[j + 1].y;
            v.z = pts[j + 1].z;
            if (func_00205440(&v, mat, &s[1], &depth[1]) == 0 || func_00101600(&s[1]) == 0) {
                continue;
            }
            dx = s[0].x - s[1].x;
            fdx = (dx >= 0) ? dx : -dx;
            dy = s[0].y - s[1].y;
            fdy = (dy >= 0) ? dy : -dy;
            w = func_001A6C60(fdx * fdx + fdy * fdy) / e->wdiv;
            if (e->flags & 8) {
                cnt = 2;
            } else {
                cnt = (e->life & 3) + 1;
            }
            for (k = 0; k < cnt; k++) {
                rot = j & 3;
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
                switch ((e->flags & 4) ? rot : (e->life + j) & 3) {
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

/* OVL_CFLAGS: -O3,p -sdatathreshold 0 -relax_pointers */

/* shape b051:01E003A0, 660 insns, 39 copies: the code of shape b035:01E00410 built at -O3 (draws each emitter of a
   list as a glowing ring: a fan of segs*4 triangles from the centre colour out to the edge colour, and unless flag 1
   a textured band along the edge (two quads per slice); the radius grows each frame) */

/* OVL_CFLAGS: -O2,p -sdatathreshold 0 -relax_pointers */

/* shape b035:01E00410, 736 insns, 89 copies: draws each emitter of a list as a glowing ring: a fan of segs*4
   triangles from the centre colour out to the edge colour, and unless flag 1 a textured band along the edge (two
   quads per slice); the radius grows each frame */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b035_01E00410;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
} Hdr_b035_01E00410;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Xyz_b035_01E00410 xyz;
} Vtx1_b035_01E00410;

typedef struct {
    Hdr_b035_01E00410 h;
    Vtx1_b035_01E00410 v[3];
    u8 tail[8];
} Pkt1_b035_01E00410;

typedef struct {
    u64 st;
    Xyz_b035_01E00410 xyz;
} Vtx2_b035_01E00410;

typedef struct {
    Hdr_b035_01E00410 h;
    u8 r, g, b, a;
    f32 q;
    Vtx2_b035_01E00410 v[4];
    u8 tail[0x20];
} Pkt2_b035_01E00410;

typedef struct {
    f32 x, y, z, w;
} V4_b035_01E00410;

typedef struct {
    s32 id;
    u8 kind;
    u8 pad05[3];
    s32 w[4];
} Tex_b035_01E00410;

typedef struct {
    u8 cur;
    u8 pad1;
    u8 max;
    u8 pad3;
    u8 flags;
    u8 pad5[2];
    u8 segs;
    u8 b, g, r;
    u8 padB;
    u8 ib, ig, ir;
    u8 alpha;
    f32 radius;
    f32 grow;
    f32 width;
    V4_b035_01E00410 pos;
    V4_b035_01E00410 vel;
    V4_b035_01E00410 org;
} Obj_b035_01E00410;

#pragma optimization_level 3

static s32 func_01E02260_b706(Obj_b035_01E00410 *obj, s32 tex, s32 n) {
    extern Tex_b035_01E00410 D_01E072D0_b706;
    extern s32 func_00202BF0(s32, s32);
    extern s32 func_00101AF0(void *);
    extern void func_00101BA0(void *, void *);
    extern void func_0020EB40(void *);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020BC00(void *, void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern s32 func_00101600(void *);
    extern f32 func_001018E0(f32, f32);
    extern void func_002086D0(void *, u64);
    extern void func_00101D20(void *, void *, s32);
    extern f32 func_001A6898(f32);
    extern f32 func_001A6A88(f32);
    extern void func_002075F0(void *, s32, s32);
    Obj_b035_01E00410 *o; /* a copy of obj: needed for the match (register order) */
    s32 k;
    s32 h __attribute__((aligned(16))); /* aligned: its spill slot, needed for the match */
    f32 m0[16];
    f32 m1[16];
    V4_b035_01E00410 org;
    Tex_b035_01E00410 t;
    Xyz_b035_01E00410 scr;
    Pkt1_b035_01E00410 p1 __attribute__((aligned(8)));
    Pkt2_b035_01E00410 p2 __attribute__((aligned(8)));
    f32 depth;
    s32 i;
    s32 segs;
    f32 zf;
    f32 px;
    f32 py;
    f32 x;
    f32 y;
    f32 step;
    f32 r;
    f32 w;
    f32 v;
    f32 a;
    u8 d;

    o = obj;
    t = D_01E072D0_b706;
    h = func_00202BF0(t.id, t.kind);
    for (k = 0; k < n; k++) {
        if (k != 0) {
            o++;
        }
        if (func_00101AF0(o) == 0) {
            continue;
        }
        o->pos.x += o->vel.x;
        o->pos.y += o->vel.y;
        o->pos.z += o->vel.z;
        o->radius += o->grow;
        org = o->org;
        segs = o->segs;
        segs = segs > 9 ? 9 : segs; /* this form for the match */
        step = 90.0f / segs;
        func_00101BA0(o, &o->pos);
        func_0020EB40(m1);
        func_0020C940(m0, NULL, NULL, &o->pos);
        func_0020BC00(m1, m0);
        if (func_00205440(&org, m1, &scr, &depth) == 0 || func_00101600(&scr) == 0) {
            continue;
        }
        r = func_001018E0(o->radius, depth);
        w = func_001018E0(o->width, depth);
        if (o->flags & 0x80) {
            scr.z = 0xFFFFFE;
            zf = 0.0f;
        } else {
            zf = depth;
        }
        ((Hdr_b035_01E00410 *)(s32)&p1)->count = 0x13;
        ((Hdr_b035_01E00410 *)(s32)&p1)->tag = 6;
        ((Hdr_b035_01E00410 *)(s32)&p1)->regs = 0x414141;
        ((Hdr_b035_01E00410 *)(s32)&p1)->pad = 0;
        p1.v[0].r = o->ir;
        p1.v[1].r = p1.v[2].r = o->r;
        p1.v[0].g = o->ig;
        p1.v[1].g = p1.v[2].g = o->g;
        p1.v[0].b = o->ib;
        p1.v[1].b = p1.v[2].b = o->b;
        p1.v[0].q = p1.v[1].q = p1.v[2].q = 1.0f;
        if (o->flags & 8) {
            func_002086D0(&p1, 0x42);
        } else {
            func_002086D0(&p1, 0x48);
        }
        ((Hdr_b035_01E00410 *)(s32)&p2)->count = 0x24;
        ((Hdr_b035_01E00410 *)(s32)&p2)->tag = 9;
        ((Hdr_b035_01E00410 *)(s32)&p2)->regs = ((u64)4 << 32) | 0x24242421;
        ((Hdr_b035_01E00410 *)(s32)&p2)->pad = 0;
        p2.r = o->r;
        p2.g = o->g;
        p2.b = o->b;
        p2.q = 1.0f;
        func_00101D20(&p2, &t, h);
        p1.v[0].a = o->alpha;
        p2.a = o->alpha >> 1;
        p1.v[1].a = p1.v[2].a = 0;
        if (!(o->flags & 0x40)) {
            if (o->cur < 8) {
                p1.v[0].a = (o->alpha >> 3) * o->cur;
                p2.a = (o->alpha >> 4) * o->cur;
            } else {
                d = o->max - o->cur;
                if (d < 8) {
                    p1.v[0].a = (o->alpha >> 3) * d;
                    p2.a = (o->alpha >> 4) * d;
                }
            }
        }
        if (o->cur & 1) {
            if (o->flags & 2) {
                if (p1.v[0].a > 0x10) {
                    p1.v[0].a -= 0x10;
                }
            }
            if (o->flags & 4) {
                if (p1.v[0].a > 0) {
                    p1.v[0].a >>= 1;
                }
            }
        }
        x = r * func_001A6898(0.0f);
        y = r * func_001A6A88(0.0f);
        p2.v[0].xyz.z = p2.v[1].xyz.z = p2.v[2].xyz.z = p2.v[3].xyz.z = p1.v[0].xyz.z = p1.v[1].xyz.z =
            p1.v[2].xyz.z = scr.z;
        p2.v[0].xyz.f = p2.v[1].xyz.f = p2.v[2].xyz.f = p2.v[3].xyz.f = p1.v[0].xyz.f = p1.v[1].xyz.f =
            p1.v[2].xyz.f = 1;
        for (i = 1; i < segs * 4 + 1; i++) {
            px = x;
            py = y;
            a = 3.1415927f * (step * i) / 180.0f;
            x = r * func_001A6898(a);
            y = r * func_001A6A88(a);
            p1.v[0].xyz.x = scr.x;
            p1.v[0].xyz.y = scr.y;
            p1.v[1].xyz.x = scr.x + px;
            p1.v[1].xyz.y = scr.y + py;
            p1.v[2].xyz.x = scr.x + x;
            p1.v[2].xyz.y = scr.y + y;
            func_002075F0(&p1, tex, (u32)zf);
            if (o->flags & 1) {
                continue;
            }
            p2.v[0].xyz.x = p2.v[2].xyz.x = scr.x + px;
            p2.v[1].xyz.x = p2.v[3].xyz.x = scr.x + x;
            v = scr.y + py;
            p2.v[0].xyz.y = v - w;
            p2.v[2].xyz.y = w + v;
            v = scr.y + y;
            p2.v[1].xyz.y = v - w;
            p2.v[3].xyz.y = w + v;
            func_002075F0(&p2, tex, (u32)zf);
            p2.v[0].xyz.y = p2.v[2].xyz.y = scr.y + py;
            p2.v[1].xyz.y = p2.v[3].xyz.y = scr.y + y;
            px = scr.x + px; /* px reused as the temporary: needed for the match */
            p2.v[0].xyz.x = w + px;
            p2.v[2].xyz.x = px - w;
            px = scr.x + x;
            p2.v[1].xyz.x = w + px;
            p2.v[3].xyz.x = px - w;
            func_002075F0(&p2, tex, (u32)zf);
        }
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/mod/b706", func_01E02CB0_b706);

INCLUDE_ASM("asm/nonmatchings/mod/b706", func_01E03790_b706);

INCLUDE_ASM("asm/nonmatchings/mod/b706", func_01E040A0_b706);

/* shape b379:01E020F0, 95 insns: if the value lies in [lo, hi] draw a full-screen flat quad (0x6BF8,0x71F8 -
   0x93F8,0x8DF8) in the source colour at the source depth, into a fresh draw buffer and close it */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b379_01E020F0;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Xyz_b379_01E020F0 v[2];
    u64 tail;
} Flat_b379_01E020F0;

typedef struct {
    u16 lo;
    u16 hi;
    u8 pad4[4];
    f32 depth;
    u8 b, g, r, a;
} Src_b379_01E020F0;

static s32 func_01E04520_b706(Src_b379_01E020F0 *src, s32 arg1, s32 v) {
    extern s32 func_00207F60(void);
    extern u64 func_00208D00(s32);
    extern void func_00207FD0(s32, s32, s32);
    Flat_b379_01E020F0 flat __attribute__((aligned(8)));
    s32 buf;

    buf = func_00207F60();
    if ((u16)v >= src->lo && (u16)v <= src->hi) {
        ((Flat_b379_01E020F0 *)(s32)&flat)->flags = 6;
        ((Flat_b379_01E020F0 *)(s32)&flat)->size = 3;
        ((Flat_b379_01E020F0 *)(s32)&flat)->regs = 0x441;
        ((Flat_b379_01E020F0 *)(s32)&flat)->pad4 = 0;
        flat.r = src->r;
        flat.g = src->g;
        flat.b = src->b;
        flat.a = src->a;
        flat.q = 1.0f;
        flat.v[0].x = 0x6BF8;
        flat.v[0].y = 0x71F8;
        flat.v[0].z = 0xFFFFFF;
        flat.v[0].f = 0;
        flat.v[1].x = 0x93F8;
        flat.v[1].y = 0x8DF8;
        flat.v[1].z = 0xFFFFFE;
        flat.v[1].f = 0;
        func_002086D0(&flat, func_00208D00(3));
        func_002075F0((s32)&flat, 0, (u32)src->depth);
        func_00207FD0(buf, arg1, 0);
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/mod/b706", func_01E046A0_b706);

INCLUDE_ASM("asm/nonmatchings/mod/b706", func_01E050E0_b706);

INCLUDE_ASM("asm/nonmatchings/mod/b706", func_01E055E0_b706);

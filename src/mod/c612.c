#include "common.h"

/* shape b000:01E00100, 38 insns, 169 copies: one colour into the four vertices of a quad (q = 1.0) */

typedef struct Src_b000_01E00100 {
    u8 b, g, r, a;
} Src_b000_01E00100;

typedef struct Col_b000_01E00100 {
    u8 r, g, b, a;
    f32 q;
} Col_b000_01E00100;

typedef struct Vtx_b000_01E00100 {
    u8 pad[0x10];
    Col_b000_01E00100 c;
} Vtx_b000_01E00100;


/* static in its module (callers that include this file #define OVL_LOCAL static first) */

static void func_01E00080_c612(Vtx_b000_01E00100 *v, Src_b000_01E00100 *s) {
    v[0].c.r = s->r;
    v[0].c.g = s->g;
    v[0].c.b = s->b;
    v[0].c.a = s->a;
    v[0].c.q = 1.0f;
    v[1].c.r = s->r;
    v[1].c.g = s->g;
    v[1].c.b = s->b;
    v[1].c.a = s->a;
    v[1].c.q = 1.0f;
    v[2].c.r = s->r;
    v[2].c.g = s->g;
    v[2].c.b = s->b;
    v[2].c.a = s->a;
    v[2].c.q = 1.0f;
    v[3].c.r = s->r;
    v[3].c.g = s->g;
    v[3].c.b = s->b;
    v[3].c.a = s->a;
    v[3].c.q = 1.0f;
}

/* shape b001:01E00A30, 740 insns, 55 copies: draws an emitter's particles as textured quads. Each point moves
   with the velocity (or func_001036A0), turns around the emitter centre while the angle catches up, and gets a
   square of the emitter size, aspect-scaled, either rotated (flag 0x1E) or axis-aligned.
   Calls the module's colour helper (shape b000:01E00100), included above as a static function. */

typedef struct {
    u8 b, g, r, a;
} Src_b001_01E00A30;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b001_01E00A30;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b001_01E00A30 v[4];
    u8 tail[0x20];
} Pkt_b001_01E00A30;

typedef struct {
    f32 x, y, z, w;
} Vec_b001_01E00A30;

typedef struct {
    f32 x, y, z;
    s16 pad;
    s16 life;
} Pt_b001_01E00A30;

typedef struct {
    void *texture;
    s32 flags;
    Src_b001_01E00A30 color;
    f32 size;
    f32 cx, cy;
    u8 pad18[8];
    s16 u, v, w, h;
    f32 fw, fh;
    Pt_b001_01E00A30 pts[16];
    s16 count;
    s16 angle;
    s16 cur;
} Emit_b001_01E00A30;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_b001_01E00A30;

static s32 func_01E00120_c612(s32 obj, Cam_b001_01E00A30 *cam, Emit_b001_01E00A30 *e, Vec_b001_01E00A30 *vel) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 depth[4];
    Vec_b001_01E00A30 p;
    Pkt_b001_01E00A30 pkt;
    s32 i;
    f32 dx;
    f32 dy;
    f32 da;
    f32 r;
    f32 kx;
    f32 ky;

    ((Pkt_b001_01E00A30 *)(s32)&pkt)->count = 0x34;
    ((Pkt_b001_01E00A30 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_b001_01E00A30 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_b001_01E00A30 *)(s32)&pkt)->pad = 0;
    if (func_00104520(e->flags, 0xC) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x44);
    } else if (func_00104520(e->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(e->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    func_01E00080_c612((Vtx_b000_01E00100 *)&pkt, (Src_b000_01E00100 *)&e->color);
    for (i = 0; i < e->count; i++) {
        if (e->cur != e->angle) {
            if (func_00104520(e->flags, 0x1F) != 0) {
                da = e->angle - e->cur;
                dx = e->pts[i].x - e->cx;
                dy = e->pts[i].y - e->cy;
                if (func_00104520(e->flags, 7) != 0) {
                    func_001036A0(&e->pts[i].x, vel);
                    r = 0.017453292f * da;
                    e->pts[i].x = e->cx + (dx * func_0020B620(r) - dy * func_0020B730(r));
                    e->pts[i].y = e->cy + (dx * func_0020B730(r) + dy * func_0020B620(r));
                } else {
                    r = 0.017453292f * da;
                    e->pts[i].x = vel->x + (e->cx + (dx * func_0020B620(r) - dy * func_0020B730(r)));
                    e->pts[i].y = vel->y + (e->cy + (dx * func_0020B730(r) + dy * func_0020B620(r)));
                }
            } else if (func_00104520(e->flags, 7) != 0) {
                func_001036A0(&e->pts[i].x, vel);
            } else {
                e->pts[i].x += vel->x;
                e->pts[i].y += vel->y;
            }
            if (i == e->count - 1) {
                e->cur = e->angle;
            }
        } else if (func_00104520(e->flags, 7) != 0) {
            func_001036A0(&e->pts[i].x, vel);
        } else {
            e->pts[i].x += vel->x;
            e->pts[i].y += vel->y;
        }
        func_00105260(&pkt, e, i);
        if (func_00104520(e->flags, 0) != 0) {
            if (e->w > e->h) {
                kx = 1.0f;
                ky = (f32)e->h / (f32)e->w;
            } else if (e->w < e->h) {
                kx = (f32)e->w / (f32)e->h;
                ky = 1.0f;
            } else {
                ky = 1.0f;
                kx = 1.0f;
            }
        } else {
            if (e->fw > e->fh) {
                ky = e->fh / e->fw;
                kx = 1.0f;
            } else if (e->fw < e->fh) {
                kx = e->fh / e->fw;
                ky = 1.0f;
            } else {
                ky = 1.0f;
                kx = 1.0f;
            }
        }
        if (func_00104520(e->flags, 0x1E) != 0) {
            r = 0.017453292f * ((e->angle + 135) % 360);
            p.x = e->pts[i].x + kx * (e->size * func_0020B620(r));
            p.y = e->pts[i].y + ky * (e->size * func_0020B730(r));
            p.z = e->pts[i].z;
            if (func_00205440(&p, cam->view, &pkt.v[0].st + 1, &depth[0]) != 0) {
                e->flags |= 0x100000;
            }
            r = 0.017453292f * ((e->angle + 45) % 360);
            p.x = e->pts[i].x + kx * (e->size * func_0020B620(r));
            p.y = e->pts[i].y + ky * (e->size * func_0020B730(r));
            if (func_00205440(&p, cam->view, &pkt.v[1].st + 1, &depth[1]) != 0) {
                e->flags |= 0x200000;
            }
            r = 0.017453292f * ((e->angle + 225) % 360);
            p.x = e->pts[i].x + kx * (e->size * func_0020B620(r));
            p.y = e->pts[i].y + ky * (e->size * func_0020B730(r));
            if (func_00205440(&p, cam->view, &pkt.v[2].st + 1, &depth[2]) != 0) {
                e->flags |= 0x400000;
            }
            r = 0.017453292f * ((e->angle + 315) % 360);
            p.x = e->pts[i].x + kx * (e->size * func_0020B620(r));
            p.y = e->pts[i].y + ky * (e->size * func_0020B730(r));
            if (func_00205440(&p, cam->view, &pkt.v[3].st + 1, &depth[3]) != 0) {
                e->flags |= 0x800000;
            }
        } else {
            p.x = e->pts[i].x - e->size * kx;
            p.y = e->pts[i].y + e->size * ky;
            p.z = e->pts[i].z;
            if (func_00205440(&p, cam->view, &pkt.v[0].st + 1, &depth[0]) != 0) {
                e->flags |= 0x100000;
            }
            p.x = e->pts[i].x + e->size * kx;
            p.y = e->pts[i].y + e->size * ky;
            if (func_00205440(&p, cam->view, &pkt.v[1].st + 1, &depth[1]) != 0) {
                e->flags |= 0x200000;
            }
            p.x = e->pts[i].x - e->size * kx;
            p.y = e->pts[i].y - e->size * ky;
            if (func_00205440(&p, cam->view, &pkt.v[2].st + 1, &depth[2]) != 0) {
                e->flags |= 0x400000;
            }
            p.x = e->pts[i].x + e->size * kx;
            p.y = e->pts[i].y - e->size * ky;
            if (func_00205440(&p, cam->view, &pkt.v[3].st + 1, &depth[3]) != 0) {
                e->flags |= 0x800000;
            }
        }
        if (func_00104520(e->flags, 0x18) != 0) {
            func_00208700(&pkt, e->texture, 0);
        } else {
            if (func_00104520(e->flags, 0) != 0) {
                func_00208CB0(&pkt, (u64)0xA | ((u64)e->u << 4) | ((u64)(e->u + e->w - 1) << 14) |
                                        ((u64)e->v << 24) | ((u64)(e->v + e->h - 1) << 34));
            }
            func_00208700(&pkt, e->texture, 1);
        }
        if (e->pts[i].life >= 0 && func_00104520(e->flags, 0x14) != 0 && func_00104520(e->flags, 0x15) != 0 &&
            func_00104520(e->flags, 0x16) != 0 && func_00104520(e->flags, 0x17) != 0) {
            if (func_00104520(e->flags, 0x13) != 0) {
                pkt.v[0].z = pkt.v[1].z = pkt.v[2].z = pkt.v[3].z = 0xFFFFFF;
                func_002075F0(&pkt, obj, 0);
            } else {
                func_002075F0(&pkt, obj, func_001A23B0((depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f));
            }
        }
        e->flags &= 0xFF0FFFFF;
    }
    if (func_00104520(e->flags, 7) == 0) {
        e->cx += vel->x;
        e->cy += vel->y;
    }
    return 0;
}

/* shape b025:01E016F0, 509 insns, 17 copies: draws a cloud of sprite quads whose offsets follow a wave table: per point,
   amplitude from |tab[i]| / 10, x/y/z from tab[k], tab[k+1], tab[k+2] (or their absolute values, or 0, per
   flag bits), scaled by the frame count; depth-sorted unless flag 0x13 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b025_01E016F0;

typedef struct {
    u64 u : 14;
    u64 pad0 : 2;
    u64 v : 14;
    u64 pad1 : 34;
} UV_b025_01E016F0;

typedef struct {
    u64 uv;
    Xyz_b025_01E016F0 p;
} Vtx_b025_01E016F0;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Vtx_b025_01E016F0 v[4];
    u8 tail[0x20];
} Pk_b025_01E016F0;

typedef struct {
    void *texture;
    s32 flags;
    u8 b8, b9, bA, bB;
    s8 *tab;
    s16 u, v, w, h;
    u8 pad18[8];
    f32 size;
    f32 amp;
    s16 count;
    s16 frame;
    u8 phase;
} Wave_b025_01E016F0;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_b025_01E016F0;

static s32 func_01E00CB0_c612(s32 obj, Wave_b025_01E016F0 *w, Cam_b025_01E016F0 *cam) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00195070(s32);
    Vec4f pos;
    f32 depth[4];
    Pk_b025_01E016F0 pk __attribute__((aligned(8)));
    s32 i;
    s32 k;
    f32 amp;
    f32 x;
    f32 y;
    f32 z;

    if (w->frame > 0) {
        ((Pk_b025_01E016F0 *)(s32)&pk)->flags = 0x24;
        ((Pk_b025_01E016F0 *)(s32)&pk)->size = 9;
        ((Pk_b025_01E016F0 *)(s32)&pk)->regs = ((u64)4 << 32) | 0x24242421;
        ((Pk_b025_01E016F0 *)(s32)&pk)->pad4 = 0;
        if (func_00104520(w->flags, 0xC) != 0) {
            func_002086D0(&pk, ((u64)0x80 << 32) | 0x44);
        } else if (func_00104520(w->flags, 0xB) != 0) {
            func_002086D0(&pk, ((u64)0x80 << 32) | 0x88);
        } else if (func_00104520(w->flags, 0xA) != 0) {
            func_002086D0(&pk, ((u64)0x80 << 32) | 0x42);
        } else {
            func_002086D0(&pk, ((u64)0x80 << 32) | 0x48);
        }
        pk.r = w->bA;
        pk.g = w->b9;
        pk.b = w->b8;
        pk.a = w->bB;
        pk.q = 1.0f;
        ((Pk_b025_01E016F0 *)(s32)&pk)->flags |= 0x800;
        ((UV_b025_01E016F0 *)(s32)&pk.v[0].uv)->u = w->u * 16;
        ((UV_b025_01E016F0 *)(s32)&pk.v[0].uv)->v = w->v * 16;
        ((UV_b025_01E016F0 *)(s32)&pk.v[1].uv)->u = w->u * 16;
        ((UV_b025_01E016F0 *)(s32)&pk.v[1].uv)->v = (w->v + w->h - 1) * 16;
        ((UV_b025_01E016F0 *)(s32)&pk.v[2].uv)->u = (w->u + w->w - 1) * 16;
        ((UV_b025_01E016F0 *)(s32)&pk.v[2].uv)->v = w->v * 16;
        ((UV_b025_01E016F0 *)(s32)&pk.v[3].uv)->u = (w->u + w->w - 1) * 16;
        ((UV_b025_01E016F0 *)(s32)&pk.v[3].uv)->v = (w->v + w->h - 1) * 16;
        for (i = 0; i < w->count; i++) {
            k = (u8)(w->phase + i);
            amp = w->amp * (0.1f * func_00195070(w->tab[i]));
            if (w->flags & 0x08000000) {
                x = 0.0f;
            } else if (w->flags & 0x01000000) {
                x = w->frame * (amp * func_00195070(w->tab[(u8)k]));
            } else {
                x = w->frame * (amp * w->tab[(u8)k]);
            }
            if (w->flags & 0x10000000) {
                y = 0.0f;
            } else if (w->flags & 0x02000000) {
                y = w->frame * (amp * func_00195070(w->tab[(u8)(k + 1)]));
            } else {
                y = w->frame * (amp * w->tab[(u8)(k + 1)]);
            }
            if (w->flags & 0x20000000) {
                z = 0.0f;
            } else if (w->flags & 0x04000000) {
                z = w->frame * (amp * func_00195070(w->tab[(u8)(k + 2)]));
            } else {
                z = w->frame * (amp * w->tab[(u8)(k + 2)]);
            }
            pos.x = x - w->size;
            pos.y = y + w->size;
            pos.z = z;
            if (func_00205440(&pos, cam->view, &pk.v[0].p, &depth[0]) != 0) {
                w->flags |= 0x100000;
            }
            pos.x = x + w->size;
            pos.y = y + w->size;
            if (func_00205440(&pos, cam->view, &pk.v[1].p, &depth[1]) != 0) {
                w->flags |= 0x200000;
            }
            pos.x = x - w->size;
            pos.y = y - w->size;
            if (func_00205440(&pos, cam->view, &pk.v[2].p, &depth[2]) != 0) {
                w->flags |= 0x400000;
            }
            pos.x = x + w->size;
            pos.y = y - w->size;
            if (func_00205440(&pos, cam->view, &pk.v[3].p, &depth[3]) != 0) {
                w->flags |= 0x800000;
            }
            func_00208700(&pk, w->texture, 0);
            if (func_00104520(w->flags, 0x13) != 0) {
                pk.v[0].p.z = pk.v[1].p.z = pk.v[2].p.z = pk.v[3].p.z = 0xFFFFFF;
                func_002075F0(&pk, obj, 0);
            } else if (func_00104520(w->flags, 0x14) != 0 && func_00104520(w->flags, 0x15) != 0 &&
                       func_00104520(w->flags, 0x16) != 0 && func_00104520(w->flags, 0x17) != 0) {
                func_002075F0(&pk, obj, func_001A23B0((depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f));
            }
            w->flags &= 0xFF0FFFFF;
        }
    }
    w->frame++;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/c612", func_01E014B0_c612);

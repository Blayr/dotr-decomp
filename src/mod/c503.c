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

static void func_01E00080_c503(Vtx_b000_01E00100 *v, Src_b000_01E00100 *s) {
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

static s32 func_01E00120_c503(s32 obj, Cam_b001_01E00A30 *cam, Emit_b001_01E00A30 *e, Vec_b001_01E00A30 *vel) {
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
    func_01E00080_c503((Vtx_b000_01E00100 *)&pkt, (Src_b000_01E00100 *)&e->color);
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

/* shape c503:01E00CB0, 349 insns: the module's main: on start clears the 0x260 context, 90 ticks, the scene camera's
   channel/id, the light, 16 sparks around (0, 5, 0) and the board at the camera's point, then saves the scene's three
   camera vectors; each tick fades the scene in (or out once flag 31 is set), draws the board, shakes the camera by
   +-1 on even/odd ticks, and from tick 61 puts the camera back (ends 8 once faded out); 2 at tick 20, 8 at the end */

typedef struct {
    f32 x, y, z;
    s16 hAC;
    s16 hAE;
} Part_c503_01E00CB0;

typedef struct {
    Vec4f *eye;
    Vec4f *at;
    Vec4f *up;
    f32 *fov;
    u8 m[0x10];
    Vec4f eye0;
    Vec4f at0;
    Vec4f up0;
} Cam_c503_01E00CB0;

typedef struct {
    u8 pad000[0x20];
    u8 board[0x50];
    s32 light;
    s32 kind;
    u8 col[4];
    f32 f7C;
    f32 x, y, z;
    s32 w8C;
    u8 pad90[4];
    s16 h94;
    s16 h96;
    s16 h98;
    s16 h9A;
    s16 h9C;
    s16 h9E;
    Part_c503_01E00CB0 part[16];
    s16 n;
    u8 pad1A2[4];
    s16 h1A6;
    s16 h1A8;
    s16 step;
    s16 h1AC;
    s16 h1AE;
    s16 h1B0;
    u8 pad1B2[0xE];
    Cam_c503_01E00CB0 cam;
    u8 pad210[0x30];
    s32 timer;
    s32 t;
    s32 code;
    s32 flags;
    s32 ch;
    s32 id;
    s32 w258;
    s32 fade;
} Ctx_c503_01E00CB0;

static s32 func_01E00CB0_c503(s32 arg0, s32 code) {
    Ctx_c503_01E00CB0 *g = (Ctx_c503_01E00CB0 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern s32 func_001F5380(void);
    extern void func_00103890(void *);
    extern void func_00103260(s32 *, s32);
    extern void func_001E10F0(s32, s32, s32, void *);
    extern Vec4f *func_001F9AD0(s32);
    extern Vec4f *func_001F9D30(s32);
    extern Vec4f *func_001FAD10(s32);
    extern f32 *func_001FAF60(s32);
    extern void func_001FAFB0(s32, void *);
    extern void func_001039A0(void *);
    extern void func_001E23A0(s32, s32, s32);
    extern s32 func_00103500(s32 *, s32, s32);
    extern s32 func_00103350(s32 *, s32, s32);
    extern void func_001E2220(s32, s32, s32);
    extern void func_001F9D80(s32, Vec4f *);
    extern void func_001F9B20(s32, Vec4f *);
    extern void func_001FAD60(s32, Vec4f *);
    extern s32 func_00103470(void *, u32, s32);
    extern void c503_01E00120();
    Vec4f sc;
    s32 ot;
    s32 l;
    s32 i;

    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x260);
        g->timer = 90;
        g->t = 0;
        g->code = code;
        g->flags = 0;
        g->ch = func_001F5380() & 0xFF;
        g->id = func_001F5380() >> 8;
        g->w258 = 8;
        g->fade = 0;
        func_00103890(g);
        func_00103260(&l, 15);
        g->light = l;
        g->kind = 0x85;
        g->x = 0.0f;
        g->y = 5.0f;
        g->z = 0.0f;
        g->w8C = 0;
        g->h98 = 0xF0;
        g->h9A = 0;
        g->h94 = 0x10;
        g->h96 = 0x10;
        g->h9C = 0x100;
        g->h9E = 0x100;
        g->f7C = 10.0f;
        g->n = 16;
        g->step = 3;
        g->h1AC = 1;
        g->h1B0 = 8;
        g->h1A6 = 30;
        g->h1A8 = 20;
        g->col[2] = 0x70;
        g->col[1] = 0x60;
        g->col[0] = 0x40;
        g->col[3] = 0x40;
        for (i = 0; i < g->n; i++) {
            g->part[i].x = g->x + (func_0019A5C8() % 20 - 10);
            g->part[i].y = g->y + (func_0019A5C8() % 20 - 10);
            g->part[i].z = g->z + (func_0019A5C8() % 20 - 10);
            g->part[i].hAE = -g->step * i;
            g->part[i].hAC = 0;
            g->h1AE = g->h1B0 - 1;
        }
        func_001E10F0(g->ch, g->id, 0, g->board);
        if (&g->cam != NULL) {
            g->cam.eye = func_001F9AD0(0);
            g->cam.at = func_001F9D30(0);
            g->cam.up = func_001FAD10(0);
            g->cam.fov = func_001FAF60(0);
            func_001FAFB0(0, g->cam.m);
            g->cam.eye0 = *g->cam.eye;
            g->cam.at0 = *g->cam.at;
            g->cam.up0 = *g->cam.up;
        }
        return 0;
    }
    func_001039A0(g);
    func_001E23A0(g->ch, g->id, g->fade);
    if (func_00104520(g->flags, 0x1F) == 0) {
        if (func_00103500(&g->fade, -0x80, 4) == 0) {
            g->flags |= 0x80000000;
            func_001E2220(g->ch, g->id, g->w258);
        }
    } else if (func_00103350(&g->fade, 0, 4) == 0) {
        g->flags |= 0x40000000;
    }
    sc.z = 1.01f;
    sc.y = 1.01f;
    sc.x = 1.01f;
    c503_01E00120(ot, g, &g->light, &sc);
    if (g->t % 2 == 0) {
        g->cam.at->x = 1.0f + g->cam.at0.x;
        g->cam.at->y = 1.0f + g->cam.at0.y;
        g->cam.at->z = 1.0f + g->cam.at0.z;
        func_001F9D80(0, g->cam.at);
    } else {
        g->cam.at->x = g->cam.at0.x - 1.0f;
        g->cam.at->y = g->cam.at0.y - 1.0f;
        g->cam.at->z = g->cam.at0.z - 1.0f;
        func_001F9D80(0, g->cam.at);
    }
    if (g->t > 60) {
        g->cam.eye->x = g->cam.eye0.x;
        g->cam.eye->y = g->cam.eye0.y;
        g->cam.eye->z = g->cam.eye0.z;
        func_001F9B20(0, g->cam.eye);
        g->cam.at->x = g->cam.at0.x;
        g->cam.at->y = g->cam.at0.y;
        g->cam.at->z = g->cam.at0.z;
        func_001F9D80(0, g->cam.at);
        g->cam.up->x = g->cam.up0.x;
        g->cam.up->y = g->cam.up0.y;
        g->cam.up->z = g->cam.up0.z;
        func_001FAD60(0, g->cam.up);
        if (func_00103470(&g->col[3], 0, 2) == 0 && func_00104520(g->flags, 0x1E) != 0) {
            return 8;
        }
    }
    g->t++;
    g->timer--;
    if (g->t == 20) {
        return 2;
    }
    if (g->timer <= 0) {
        return 8;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/c503", func_01E01280_c503);

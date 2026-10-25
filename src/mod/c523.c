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

static void func_01E00080_c523(Vtx_b000_01E00100 *v, Src_b000_01E00100 *s) {
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

/* shape b037:01E00280, 86 insns, 2 copies: lays out count trail points at the emitter position, each jittered in x and y by
   up to the emitter's spread, delayed by a per-point step; their start frame comes from the model's animation
   unless flag 0 is set */

typedef struct {
    f32 x, y, z;
    s16 start;
    s16 delay;
} Pt_b037_01E00280;

typedef struct {
    u8 pad0[4];
    s32 flags;
    u8 pad8[8];
    f32 x, y, z;
    u8 pad1C[4];
    u8 anim[0x10];
    Pt_b037_01E00280 pt[16];
    s16 count;
    u8 pad132[4];
    s16 jx;
    s16 jy;
    s16 step;
    u8 pad13C[2];
    s16 end;
    s16 len;
} Trail_b037_01E00280;

static s32 func_01E00120_c523(Trail_b037_01E00280 *o) {
    extern s16 func_00105C40(void *);
    s32 i;
    s16 j;

    for (i = 0; i < o->count; i++) {
        o->pt[i].x = o->x;
        o->pt[i].y = o->y;
        j = o->jx;
        if (j != 0) {
            o->pt[i].x = o->x + (f32)(func_0019A5C8() % (j * 2) - j);
        }
        j = o->jy;
        if (j != 0) {
            o->pt[i].y = o->y + (f32)(func_0019A5C8() % (j * 2) - j);
        }
        o->pt[i].z = o->z;
        o->pt[i].delay = -o->step * i;
        if (func_00104520(o->flags, 0) != 0) {
            o->pt[i].start = 0;
            o->end = o->len - 1;
        } else {
            o->pt[i].start = func_00105C40(o->anim);
            o->end = o->pt[i].start + o->len - 1;
        }
    }
    return 0;
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

static s32 func_01E00280_c523(s32 obj, Cam_b001_01E00A30 *cam, Emit_b001_01E00A30 *e, Vec_b001_01E00A30 *vel) {
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
    func_01E00080_c523((Vtx_b000_01E00100 *)&pkt, (Src_b000_01E00100 *)&e->color);
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

/* shape c523:01E00E10, 319 insns: the c523 module's main step (c545:01E00CB0 family): with a code it clears the scene,
   sets up its coordinate, keeps the code and a 60-tick timer and three emitters: a white trail (texture 1, flags 3,
   size 18, 2 points 5 apart, set up by c523:01E00120), grey sparks (texture 15, flags 0x485, size 10, 16 points
   jittered around (0, 20)) and pink motes (texture 0, flags 0x87, size 0.5, 16 points around (0, 15)), reads the
   effect position; otherwise it draws the sparks and motes scaled 1.01 and the trail unscaled, fades in the trail for
   38 ticks then fades it and the motes; returns 2 on tick 40 and 8 when the timer ends */

typedef struct {
    u8 b, g, r, a;
} Src_c523_01E00E10;

typedef struct {
    f32 x, y, z;
    s16 hC;
    s16 hE;
} Pt_c523_01E00E10;

typedef struct {
    s32 texture;
    s32 flags;
    Src_c523_01E00E10 color;
    f32 size;
    f32 cx;
    f32 cy;
    f32 z0;
    s32 w1C;
    s16 rect[8];
    Pt_c523_01E00E10 pt[16];
    s16 count;
    u8 pad132[4];
    s16 h136;
    s16 h138;
    s16 step;
    s16 h13C;
    s16 h13E;
    s16 h140;
    u8 pad142[0xE];
} Emit_c523_01E00E10;

typedef struct {
    u8 pad0[0x20];
    struct {
        f32 f0;
        f32 scale;
        u8 pad8[0x48];
    } pos;
    Emit_c523_01E00E10 e0;
    Emit_c523_01E00E10 e1;
    Emit_c523_01E00E10 e2;
    s32 t;
    s32 timer;
    s32 code;
} Scene_c523_01E00E10;

static s32 func_01E00E10_c523(s32 arg0, s32 code) {
    Scene_c523_01E00E10 *g = (Scene_c523_01E00E10 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern void func_00103890(void *);
    extern void func_00103260(void *, s32);
    extern void func_001039A0(void *);
    extern void func_001F53B0(s32, void *);
    extern void func_00103470(void *, s32, s32);
    extern void func_001032C0(void *, s32, s32);
    Vec4f sc;
    s32 tex __attribute__((aligned(16)));
    s32 ot;
    s32 i;

    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x470);
        func_00103890(g);
        g->t = 0;
        g->timer = 60;
        g->code = code;
        func_00103260(&tex, 1);
        g->e0.texture = tex;
        g->e0.flags = 3;
        g->e0.cx = 0.0f;
        g->e0.cy = 0.0f;
        g->e0.z0 = 0.0f;
        g->e0.w1C = 0;
        g->e0.rect[4] = 0;
        g->e0.rect[5] = 0;
        g->e0.rect[2] = 0x18;
        g->e0.rect[3] = 0x20;
        g->e0.rect[6] = 0x80;
        g->e0.rect[7] = 0x40;
        g->e0.size = 18.0f;
        g->e0.count = 2;
        g->e0.step = 5;
        g->e0.h13C = 1;
        g->e0.h140 = 10;
        g->e0.h136 = 0;
        g->e0.h138 = 0;
        g->e0.color.r = 0x80;
        g->e0.color.g = 0x80;
        g->e0.color.b = 0x80;
        g->e0.color.a = 0;
        func_01E00120_c523((Trail_b037_01E00280 *)&g->e0);
        func_00103260(&tex, 0xF);
        g->e1.texture = tex;
        g->e1.flags = 0x485;
        g->e1.cx = 0.0f;
        g->e1.cy = 20.0f;
        g->e1.z0 = 0.0f;
        g->e1.w1C = 0;
        g->e1.rect[4] = 0xF0;
        g->e1.rect[5] = 0;
        g->e1.rect[2] = 0x10;
        g->e1.rect[3] = 0x10;
        g->e1.rect[6] = 0x100;
        g->e1.rect[7] = 0x100;
        g->e1.size = 10.0f;
        g->e1.count = 16;
        g->e1.step = 3;
        g->e1.h13C = 1;
        g->e1.h140 = 8;
        g->e1.h136 = 30;
        g->e1.h138 = 30;
        g->e1.color.r = 0x60;
        g->e1.color.g = 0x60;
        g->e1.color.b = 0x60;
        g->e1.color.a = 0x80;
        for (i = 0; i < g->e1.count; i++) {
            g->e1.pt[i].x = g->e1.cx + (func_0019A5C8() % 20 - 10);
            g->e1.pt[i].y = g->e1.cy + (func_0019A5C8() % 16 - 4);
            g->e1.pt[i].z = g->e1.z0;
            g->e1.pt[i].hE = -g->e1.step * i;
            g->e1.pt[i].hC = 0;
            g->e1.h13E = g->e1.h140 - 1;
        }
        func_00103260(&tex, 0);
        g->e2.texture = tex;
        g->e2.flags = 0x87;
        g->e2.cx = 0.0f;
        g->e2.cy = 15.0f;
        g->e2.z0 = 0.0f;
        g->e2.w1C = 0;
        g->e2.rect[4] = 0;
        g->e2.rect[5] = 0;
        g->e2.rect[2] = 0x20;
        g->e2.rect[3] = 0x20;
        g->e2.rect[6] = 0x80;
        g->e2.rect[7] = 0x40;
        g->e2.size = 0.5f;
        g->e2.count = 16;
        g->e2.step = 1;
        g->e2.h13C = 0;
        g->e2.h140 = 6;
        g->e2.h136 = 20;
        g->e2.h138 = 20;
        g->e2.color.r = 0x80;
        g->e2.color.g = 0x40;
        g->e2.color.b = 0x40;
        g->e2.color.a = 0x80;
        for (i = 0; i < g->e2.count; i++) {
            g->e2.pt[i].x = g->e2.cx + (func_0019A5C8() % 10 - 5);
            g->e2.pt[i].y = g->e2.cy + func_0019A5C8() % 5;
            g->e2.pt[i].z = g->e2.z0 + (func_0019A5C8() % 10 - 5);
            g->e2.pt[i].hE = -g->e2.step * i;
            g->e2.pt[i].hC = 0;
            g->e2.h13E = g->e2.h140 - 1;
        }
        func_001F53B0(0, &g->pos);
        return 0;
    }
    g->pos.scale = g->e0.size;
    func_001039A0(g);
    sc.x = sc.y = sc.z = 1.01f;
    func_01E00280_c523(ot, (Cam_b001_01E00A30 *)g, (Emit_b001_01E00A30 *)&g->e1, (Vec_b001_01E00A30 *)&sc);
    func_00103470(&g->e1.color.a, 0, 2);
    func_01E00280_c523(ot, (Cam_b001_01E00A30 *)g, (Emit_b001_01E00A30 *)&g->e2, (Vec_b001_01E00A30 *)&sc);
    sc.x = sc.y = sc.z = 0.0f;
    func_01E00280_c523(ot, (Cam_b001_01E00A30 *)g, (Emit_b001_01E00A30 *)&g->e0, (Vec_b001_01E00A30 *)&sc);
    if (g->t < 38) {
        func_001032C0(&g->e0.color.a, 0x80, 0x10);
    } else {
        func_00103470(&g->e0.color.a, 0, 8);
        func_00103470(&g->e2.color.a, 0, 4);
    }
    g->t++;
    g->timer--;
    if (g->t == 40) {
        return 2;
    }
    if (g->timer <= 0) {
        return 8;
    }
    return 0;
}

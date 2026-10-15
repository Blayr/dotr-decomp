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

static void func_01E00080_b101(Vtx_b000_01E00100 *v, Src_b000_01E00100 *s) {
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

/* OVL_WARM */

/* shape b015:01E00280, 412 insns, 10 copies: 64-strip wave/water sprite.
   func_00205D10 is declared here returning u64 (functions.h says s32): the 24-bit z store takes its result
   with no sign extension, which only a 64-bit return type gives (an SCE-style u_long). */

typedef struct {
    f32 x, y, z, w;
} Vec_b015_01E00280;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b015_01E00280;

typedef struct {
    u16 s : 14;
    u16 s_pad : 2;
    u16 t : 14;
    u16 t_pad : 2;
    u32 pad;
} Uv_b015_01E00280;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Uv_b015_01E00280 st;
    Xyz_b015_01E00280 p;
} Vtx_b015_01E00280;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b015_01E00280 v[4];
    u8 pad70[8];
    u64 t78;
    u64 t80;
    u8 pad88[8];
} Pkt_b015_01E00280;

typedef struct {
    u8 pad00[0x30];
    f32 m[16];
} Cam_b015_01E00280;

typedef struct {
    s32 flags;
    u8 b04[6];
    s16 model;
    s32 step;
    s32 phase;
    f32 amp;
} Wave_b015_01E00280;

extern void b101_01E00080(Pkt_b015_01E00280 *, void *);

static s32 func_01E00120_b101(Wave_b015_01E00280 *o, Vec_b015_01E00280 *pos) {
    extern s32 func_00207F60(void);
    extern void func_00103890(void *);
    extern void func_001038D0(void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_00208460(void);
    extern void func_001F7060(s32, s32, void *, void *);
    extern f32 func_001F5860(s32);
    extern u64 func_00205D10(void *, f32);
    extern f32 func_00205DF0(void *, f32);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00207500(void);
    extern void func_00207FD0(s32, s32, s32);
    u16 y;
    s32 x1;
    s32 x0;
    s32 d;
    s32 i;
    s32 h;
    Cam_b015_01E00280 cam;
    Pkt_b015_01E00280 pkt;
    Xyz_b015_01E00280 q;
    f32 dep;

    h = func_00207F60();
    func_00103890(&cam);
    func_001038D0(&cam);
    if (func_00205440(pos, cam.m, &q, &dep) == 0) {
        return -1;
    }
    ((Pkt_b015_01E00280 *)(s32)&pkt)->count = 0x34;
    ((Pkt_b015_01E00280 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_b015_01E00280 *)(s32)&pkt)->regs = 0x421421421421LL;
    ((Pkt_b015_01E00280 *)(s32)&pkt)->pad = 0;
    if (func_00104520(o->flags, 0xC) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x44);
    } else if (func_00104520(o->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(o->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    b101_01E00080(&pkt, o->b04);
    func_00208460();
    func_001F7060(o->model, 1, &pkt.t78, &pkt.t80);
    func_00208460();
    ((Pkt_b015_01E00280 *)(s32)&pkt)->count |= 0x800;
    for (i = 0; i < 64; i++) {
        y = i * 7 + 0x720;
        x0 = (s32)(o->amp * func_0020B550(o->phase + o->step * i));
        x1 = (s32)(o->amp * func_0020B550(o->phase + o->step * (i + 1)));
        pkt.v[0].p.x = ((x0 + 0x6C0) << 4) - 8;
        pkt.v[0].p.y = (y << 4) - 8;
        pkt.v[0].p.f = 0;
        pkt.v[1].p.x = ((x0 + 0x940) << 4) - 8;
        pkt.v[1].p.y = (y << 4) - 8;
        pkt.v[1].p.f = 0;
        pkt.v[2].p.x = ((x1 + 0x6C0) << 4) - 8;
        pkt.v[2].p.y = (((i + 1) * 7 + 0x720) << 4) - 8;
        pkt.v[2].p.f = 0;
        pkt.v[3].p.x = ((x1 + 0x940) << 4) - 8;
        pkt.v[3].p.y = (((i + 1) * 7 + 0x720) << 4) - 8;
        pkt.v[3].p.f = 0;
        ((Uv_b015_01E00280 *)(s32)&pkt.v[0].st)->s = 0;
        ((Uv_b015_01E00280 *)(s32)&pkt.v[0].st)->t = (i * 7) << 4;
        ((Uv_b015_01E00280 *)(s32)&pkt.v[1].st)->s = 0x2800;
        ((Uv_b015_01E00280 *)(s32)&pkt.v[1].st)->t = (i * 7) << 4;
        ((Uv_b015_01E00280 *)(s32)&pkt.v[2].st)->s = 0;
        ((Uv_b015_01E00280 *)(s32)&pkt.v[2].st)->t = ((i + 1) * 7) << 4;
        ((Uv_b015_01E00280 *)(s32)&pkt.v[3].st)->s = 0x2800;
        ((Uv_b015_01E00280 *)(s32)&pkt.v[3].st)->t = ((i + 1) * 7) << 4;
        if (func_00104520(o->flags, 0x13) != 0) {
            pkt.v[0].p.z = pkt.v[1].p.z = pkt.v[2].p.z = pkt.v[3].p.z = 0xFFFFFF;
            d = 0;
        } else if (func_00104520(o->flags, 0x12) != 0) {
            pkt.v[0].p.z = pkt.v[1].p.z = pkt.v[2].p.z = pkt.v[3].p.z = q.z;
            d = 0xFFFFFF;
        } else {
            pkt.v[0].p.z = pkt.v[1].p.z = pkt.v[2].p.z = pkt.v[3].p.z = func_00205D10(pos, -func_001F5860(o->model));
            d = (u32)func_00205DF0(pos, -func_001F5860(o->model));
        }
        func_002075F0(&pkt, 0, d);
    }
    o->phase += o->step;
    func_00207FD0(h, func_00207500(), d);
    return 0;
}

/* OVL_WARM: compile warm (DK_WARM=1, after a runtime-helper call as in the original many-files-per-run build).
   Its float -> int casts are MWCC runtime calls: fptosi = 0x001A22C0, fptoui = 0x001A23B0 (link names). */

/* shape b015:01E01620, 110 insns, 54 copies: scatter the particles on a random ring (flag 0x1D) or at a spawn point */

typedef struct {
    f32 x, y, z;
    u8 c;
    u8 d;
    s16 t;
} Part_b015_01E01620;

typedef struct {
    u8 pad00[4];
    s32 flags;
    u8 pad08[3];
    u8 c;
    Part_b015_01E01620 *parts;
    u8 pad10[0x18];
    f32 radius;
    s16 count;
} Obj_b015_01E01620;

static s32 func_01E00790_b101(Obj_b015_01E01620 *obj, s32 life, f32 y) {
    f32 v[4];
    s32 a;
    s32 n;
    s32 i;
    f32 r;

    n = (s32)(10.0f * obj->radius);
    for (i = 0; i < obj->count; i++) {
        if (func_00104520(obj->flags, 0x1D) != 0) {
            a = func_0019A5C8() % 0x10000;
            r = 0.1f * (f32)(func_0019A5C8() % n);
            obj->parts[i].y = y;
            obj->parts[i].z = r * func_0020B480(a);
            obj->parts[i].x = r * func_0020B550(a);
        } else {
            func_001043F0(v, y);
            obj->parts[i].x = v[0];
            obj->parts[i].y = v[1];
            obj->parts[i].z = v[2];
        }
        obj->parts[i].t = -(func_0019A5C8() % life);
        obj->parts[i].c = obj->c;
        obj->parts[i].d = 0;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b101", func_01E00950_b101);

/* shape b007:01E017F0, 355 insns, 16 copies: draws a sprite as two crossed quads: 8 corners (from a template, sized by
   two width/height pairs) rotated by the sprite's rotation, projected per quad, depth-sorted unless flag 0x13 */

typedef struct {
    u8 b, g, r, a;
} Src_b007_01E017F0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b007_01E017F0;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b007_01E017F0 v[4];
    u8 tail[0x20];
} Pkt_b007_01E017F0;

typedef struct {
    f32 x, y, z, w;
} Vec_b007_01E017F0;

typedef struct {
    Vec_b007_01E017F0 v[8];
} Quad8_b007_01E017F0;

typedef struct {
    void *texture;
    s32 flags;
    Src_b007_01E017F0 color;
    f32 w;
    f32 h;
    f32 w2;
    f32 h2;
    u8 pad1C[4];
    s16 u;
    s16 v;
    s16 tw;
    s16 th;
    u8 pad28[8];
    Vec_b007_01E017F0 rot;
} Spr_b007_01E017F0;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_b007_01E017F0;

static s32 func_01E016B0_b101(s32 obj, Spr_b007_01E017F0 *spr, Cam_b007_01E017F0 *cam) {
    extern Quad8_b007_01E017F0 D_01E03C00_b101;
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00104540(void *, void *, s32);
    Quad8_b007_01E017F0 in;
    Vec_b007_01E017F0 out[8];
    f32 m[16];
    f32 depth[4];
    Pkt_b007_01E017F0 pkt;
    s32 i;

    in = D_01E03C00_b101;
    in.v[0].x = -spr->w;
    in.v[0].y = spr->h;
    in.v[1].x = spr->w;
    in.v[1].y = spr->h;
    in.v[2].x = -spr->w;
    in.v[2].y = -spr->h;
    in.v[3].x = spr->w;
    in.v[3].y = -spr->h;
    in.v[4].x = -spr->h2;
    in.v[4].y = spr->w2;
    in.v[5].x = spr->h2;
    in.v[5].y = spr->w2;
    in.v[6].x = -spr->h2;
    in.v[6].y = -spr->w2;
    in.v[7].x = spr->h2;
    in.v[7].y = -spr->w2;
    func_0020C630(m, &spr->rot);
    for (i = 0; i < 8; i++) {
        func_0020CDD0(&out[i], m, &in.v[i]);
    }
    ((Pkt_b007_01E017F0 *)(s32)&pkt)->count = 0x34;
    ((Pkt_b007_01E017F0 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_b007_01E017F0 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_b007_01E017F0 *)(s32)&pkt)->pad = 0;
    if (func_00104520(spr->flags, 0xC) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x44);
    } else if (func_00104520(spr->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(spr->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    func_01E00080_b101((Vtx_b000_01E00100 *)&pkt, (Src_b000_01E00100 *)&spr->color);
    func_00104540(&pkt, &spr->u, 0);
    for (i = 0; i < 2; i++) {
        if (func_00205440(&out[i * 4], cam->view, &pkt.v[0].st + 1, &depth[0]) != 0) {
            spr->flags |= 0x100000;
        }
        if (func_00205440(&out[i * 4 + 1], cam->view, &pkt.v[1].st + 1, &depth[1]) != 0) {
            spr->flags |= 0x200000;
        }
        if (func_00205440(&out[i * 4 + 2], cam->view, &pkt.v[2].st + 1, &depth[2]) != 0) {
            spr->flags |= 0x400000;
        }
        if (func_00205440(&out[i * 4 + 3], cam->view, &pkt.v[3].st + 1, &depth[3]) != 0) {
            spr->flags |= 0x800000;
        }
        func_00208CB0(&pkt, (u64)0xA | ((u64)spr->u << 4) | ((u64)(spr->u + spr->tw - 1) << 14) |
                                ((u64)spr->v << 24) | ((u64)(spr->v + spr->th - 1) << 34));
        func_00208700(&pkt, spr->texture, 1);
        if (func_00104520(spr->flags, 0x14) != 0 && func_00104520(spr->flags, 0x15) != 0 &&
            func_00104520(spr->flags, 0x16) != 0 && func_00104520(spr->flags, 0x17) != 0) {
            if (func_00104520(spr->flags, 0x13) != 0) {
                pkt.v[0].z = pkt.v[1].z = pkt.v[2].z = pkt.v[3].z = 0xFFFFFF;
                func_002075F0(&pkt, obj, 0);
            } else {
                func_002075F0(&pkt, obj, func_001A23B0((depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f));
            }
        }
        spr->flags &= 0xFF0FFFFF;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b101", func_01E01C40_b101);

/* OVL_WARM */

/* shape b101:01E021A0, 492 insns: draws a beam between two points: the line is cut into n pieces (at most 32),
   all points projected; each visible piece up to the moving head is drawn as four quads (above, below, right,
   left of the line) as wide as func_001018E0(width, depth). Colour from the module helper b101:01E00080.
   Both spilled params are aligned(8): that puts their homes at 0xD8/0xD0 like the original. */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b101_01E021A0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 uv;
    Xyz_b101_01E021A0 xyz;
} Vtx_b101_01E021A0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b101_01E021A0 v[4];
    u8 tail[0x20];
} Pkt_b101_01E021A0;

typedef struct {
    s16 u, v, w, h;
} Rect_b101_01E021A0;

typedef struct {
    void *texture;
    s32 flags;
    u8 color[4];
    f32 width;
    Rect_b101_01E021A0 rect;
    u8 pad18[0x10];
    s16 n;
    u8 pad2A[2];
    s16 head;
} Beam_b101_01E021A0;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_b101_01E021A0;

static s32 func_01E021A0_b101(s32 ot __attribute__((aligned(8))), Beam_b101_01E021A0 *b, Cam_b101_01E021A0 *cam __attribute__((aligned(8))), Vec4f *p1, Vec4f *p2) {
    extern void b101_01E00080(void *, void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern s32 func_00101600(void *);
    extern s32 func_00104540(void *, void *, s32);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00208CB0(void *, u64);
    extern f32 func_001018E0(f32, f32);
    Vec4f pts[33];
    Xyz_b101_01E021A0 s[33];
    f32 depth[33];
    Pkt_b101_01E021A0 pkt;
    f32 t;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 w0;
    f32 w1;
    s32 vis;
    s32 i;
    s32 j;

    vis = 0;
    if (b->n > 32) {
        b->n = 32;
    }
    ((Pkt_b101_01E021A0 *)(s32)&pkt)->count = 0x34;
    ((Pkt_b101_01E021A0 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_b101_01E021A0 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_b101_01E021A0 *)(s32)&pkt)->pad = 0;
    func_00208CB0(&pkt, (u64)0xA | ((u64)b->rect.u << 4) | ((u64)(b->rect.u + b->rect.w - 1) << 14) |
                            ((u64)b->rect.v << 24) | ((u64)(b->rect.v + b->rect.h - 1) << 34));
    func_00208700(&pkt, b->texture, 1);
    func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    b101_01E00080(&pkt, b->color);
    dx = p2->x - p1->x;
    dy = p2->y - p1->y;
    dz = p2->z - p1->z;
    for (i = 0; i < b->n + 1; i++) {
        if (i == b->n) {
            pts[b->n] = *p2;
        } else {
            t = (f32)i / b->n;
            pts[i].x = p1->x + dx * t;
            pts[i].y = p1->y + dy * t;
            pts[i].z = p1->z + dz * t;
        }
        if (func_00205440(&pts[i], cam->view, &s[i], &depth[i]) != 0) {
            vis |= 1 << i;
        }
    }
    for (i = 0; i < b->n; i++) {
        if (i <= b->head) {
            func_00104540(&pkt, &b->rect, 0);
            if (func_00104520(vis, i) != 0 && func_00104520(vis, i + 1) != 0) {
                w0 = func_001018E0(b->width, depth[i]);
                w1 = func_001018E0(b->width, depth[i + 1]);
                for (j = 0; j < 4; j++) {
                    if (j < 2) {
                        pkt.v[0].xyz.x = pkt.v[2].xyz.x = s[i].x;
                        pkt.v[1].xyz.x = pkt.v[3].xyz.x = s[i + 1].x;
                        if (j == 0) {
                            pkt.v[0].xyz.y = w0 + s[i].y;
                            pkt.v[1].xyz.y = w1 + s[i + 1].y;
                            pkt.v[2].xyz.y = s[i].y;
                            pkt.v[3].xyz.y = s[i + 1].y;
                        }
                        if (j == 1) {
                            pkt.v[0].xyz.y = s[i].y - w0;
                            pkt.v[1].xyz.y = s[i + 1].y - w1;
                            pkt.v[2].xyz.y = s[i].y;
                            pkt.v[3].xyz.y = s[i + 1].y;
                        }
                    } else {
                        pkt.v[0].xyz.y = pkt.v[2].xyz.y = s[i].y;
                        pkt.v[1].xyz.y = pkt.v[3].xyz.y = s[i + 1].y;
                        if (j == 2) {
                            pkt.v[0].xyz.x = w0 + s[i].x;
                            pkt.v[1].xyz.x = w1 + s[i + 1].x;
                            pkt.v[2].xyz.x = s[i].x;
                            pkt.v[3].xyz.x = s[i + 1].x;
                        }
                        if (j == 3) {
                            pkt.v[0].xyz.x = s[i].x - w0;
                            pkt.v[1].xyz.x = s[i + 1].x - w1;
                            pkt.v[2].xyz.x = s[i].x;
                            pkt.v[3].xyz.x = s[i + 1].x;
                        }
                    }
                    if (func_00101600(&pkt.v[0].xyz) != 0) {
                        b->flags |= 0x100000;
                    }
                    if (func_00101600(&pkt.v[1].xyz) != 0) {
                        b->flags |= 0x200000;
                    }
                    if (func_00104520(b->flags, 0x14) != 0 && func_00104520(b->flags, 0x15) != 0) {
                        pkt.v[0].xyz.z = pkt.v[2].xyz.z = s[i].z;
                        pkt.v[1].xyz.z = pkt.v[3].xyz.z = s[i + 1].z;
                        func_002075F0(&pkt, ot, (u32)((depth[i] + depth[i + 1]) / 2.0f));
                    }
                    b->flags &= 0xFFCFFFFF;
                }
            }
        }
    }
    b->head++;
    if (b->head >= b->n) {
        if (func_00104520(b->flags, 0x1A) != 0) {
            b->head = b->n;
        } else {
            b->head = 0;
        }
    }
    return 0;
}

typedef struct {
    f32 x, y, z, w;
} Vec_b001_01E035A0;

typedef struct {
    s32 type;
    s32 id;
    u8 pad08[4];
    f32 height;
    u8 pad10[0x10];
    f32 inner;
    f32 a24;
    f32 a28;
    u8 pad2C[4];
    f32 outer;
    f32 b34;
    f32 b38;
    u8 pad3C[4];
    Vec_b001_01E035A0 in[30];
    Vec_b001_01E035A0 out[30];
} Ring_b001_01E035A0;

static s32 func_01E02950_b101(Ring_b001_01E035A0 *o, s32 type, f32 inner, f32 outer, f32 y, f32 height) {
    extern s32 func_001A22C0(f32);
    Vec_b001_01E035A0 *in;
    s32 i;
    f32 span;
    f32 top;
    f32 span2;
    f32 top2;
    f32 angle;
    s32 r;

    o->type = type;
    o->height = height;
    o->inner = inner;
    o->outer = outer;
    if (func_00104520(o->id, 0x1D) != 0) {
        o->a24 = 0.0f;
        top = y + height;
        o->a28 = y;
        o->b34 = 0.0f;
        span = 2.0f * height;
        o->b38 = top;
        for (i = 0; i < 30; i++) {
            angle = 0.20943952f * (i + 1);
            o->in[i].x = inner * func_0020B620(angle);
            o->in[i].y = inner * func_0020B730(angle);
            o->in[i].z = y;
            o->out[i].x = outer * func_0020B620(angle);
            o->out[i].y = outer * func_0020B730(angle);
            if (func_00104520(o->id, 0xF) != 0) {
                r = func_0019A5C8();
                o->out[i].z = top + ((r % func_001A22C0(span) - func_001A22C0(height)) >> 1);
            } else {
                o->out[i].z = top;
            }
        }
    } else {
        top2 = y + height;
        o->a24 = y;
        o->a28 = 0.0f;
        o->b34 = top2;
        span2 = 2.0f * height;
        o->b38 = 0.0f;
        for (i = 0; i < 30; i++) {
            angle = 0.20943952f * (i + 1);
            o->in[i].x = inner * func_0020B620(angle);
            o->in[i].z = inner * func_0020B730(angle);
            o->in[i].y = y;
            o->out[i].x = outer * func_0020B620(angle);
            o->out[i].z = outer * func_0020B730(angle);
            if (func_00104520(o->id, 0xF) != 0) {
                r = func_0019A5C8();
                o->out[i].y = top2 + ((r % func_001A22C0(span2) - func_001A22C0(height)) >> 1);
            } else {
                o->out[i].y = top2;
            }
        }
    }
    return 0;
}

/* shape b001:01E03860, 316 insns, 72 copies: draws the 30-segment ring built by b001:01E035A0.
   It calls the module's colour helper (shape b000:01E00100, here func_01E00080_b101) and needs that helper
   defined EARLIER in the same file as a static function: MWCC keeps &pkt in a0 across the call only then.
   The static copy below is that helper (identical code to ovl-matched/b000_01E00100.c). */

typedef struct {
    u8 b, g, r, a;
} Src_b001_01E03860;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b001_01E03860;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b001_01E03860 v[4];
    u8 tail[0x20];
} Pkt_b001_01E03860;

typedef struct {
    f32 x, y, z, w;
} Vec_b001_01E03860;

typedef struct {
    void *texture;
    s32 flags;
    Src_b001_01E03860 color;
    u8 pad0C[4];
    s16 u;
    s16 v;
    s16 w;
    s16 h;
    u8 pad18[8];
    Vec_b001_01E03860 p0;
    Vec_b001_01E03860 p1;
    Vec_b001_01E03860 in[30];
    Vec_b001_01E03860 out[30];
} Ring_b001_01E03860;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_b001_01E03860;



static inline void init_b001_01E03860(Pkt_b001_01E03860 *p) {
    p->count = 0x34;
    p->tag = 0xC;
    p->regs = ((u64)0x4214 << 32) | 0x21421421;
    p->pad = 0;
}

static s32 func_01E02C10_b101(s32 obj, Ring_b001_01E03860 *ring, Cam_b001_01E03860 *cam) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00104540(void *, void *, s32);
    f32 depth[4];
    Pkt_b001_01E03860 pkt;
    s32 i;
    Pkt_b001_01E03860 *hdr;

    ((Pkt_b001_01E03860 *)(s32)&pkt)->count = 0x34;
    ((Pkt_b001_01E03860 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_b001_01E03860 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_b001_01E03860 *)(s32)&pkt)->pad = 0;
    if (func_00104520(ring->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(ring->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    for (i = 0; i < 30; i++) {
        func_01E00080_b101(&pkt, &ring->color);
        func_00104540(&pkt, &ring->u, 2);
        if (i == 0) {
            if (func_00205440(&ring->p0, cam->view, &pkt.v[0].st + 1, &depth[0]) != 0) {
                ring->flags |= 0x100000;
            }
            if (func_00205440(&ring->p1, cam->view, &pkt.v[1].st + 1, &depth[1]) != 0) {
                ring->flags |= 0x200000;
            }
        } else {
            if (func_00205440(&ring->in[i - 1], cam->view, &pkt.v[0].st + 1, &depth[0]) != 0) {
                ring->flags |= 0x100000;
            }
            if (func_00205440(&ring->out[i - 1], cam->view, &pkt.v[1].st + 1, &depth[1]) != 0) {
                ring->flags |= 0x200000;
            }
        }
        if (i != 29) {
            if (func_00205440(&ring->in[i], cam->view, &pkt.v[2].st + 1, &depth[2]) != 0) {
                ring->flags |= 0x400000;
            }
            if (func_00205440(&ring->out[i], cam->view, &pkt.v[3].st + 1, &depth[3]) != 0) {
                ring->flags |= 0x800000;
            }
        } else {
            if (func_00205440(&ring->p0, cam->view, &pkt.v[2].st + 1, &depth[2]) != 0) {
                ring->flags |= 0x400000;
            }
            if (func_00205440(&ring->p1, cam->view, &pkt.v[3].st + 1, &depth[3]) != 0) {
                ring->flags |= 0x800000;
            }
        }
        func_00208CB0(&pkt, (u64)0xA | ((u64)ring->u << 4) | ((u64)(ring->u + ring->w - 1) << 14) |
                                ((u64)ring->v << 24) | ((u64)(ring->v + ring->h - 1) << 34));
        func_00208700(&pkt, ring->texture, 1);
        if (func_00104520(ring->flags, 0x14) != 0 && func_00104520(ring->flags, 0x15) != 0 &&
            func_00104520(ring->flags, 0x16) != 0 && func_00104520(ring->flags, 0x17) != 0) {
            if (func_00104520(ring->flags, 0x13) != 0) {
                pkt.v[0].z = pkt.v[1].z = pkt.v[2].z = pkt.v[3].z = 0xFFFFFF;
                func_002075F0(&pkt, obj, 0);
            } else {
                func_002075F0(&pkt, obj, func_001A23B0((depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f));
            }
        }
        ring->flags &= 0xFF0FFFFF;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b101", func_01E03100_b101);

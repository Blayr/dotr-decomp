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

static void func_01E00080_b143(Vtx_b000_01E00100 *v, Src_b000_01E00100 *s) {
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

/* shape b001:01E00900, 73 insns, 54 copies: one GS sprite (RGBAQ, ST, XYZ2, ST, XYZ2) sent with the current texture */

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
} Hdr_b001_01E00900;

typedef struct {
    Hdr_b001_01E00900 h;
    u8 r, g, b, a;
    f32 q;
    f32 s0, t0;
    u64 x0 : 16;
    u64 y0 : 16;
    u64 z0 : 24;
    u64 f0 : 8;
    f32 s1, t1;
    u64 x1 : 16;
    u64 y1 : 16;
    u64 z1 : 24;
    u64 f1 : 8;
    u8 tail[0x20];
} Pkt_b001_01E00900;

static s32 func_01E00120_b143(void) {
    Pkt_b001_01E00900 p __attribute__((aligned(8)));

    ((Hdr_b001_01E00900 *)(s32)&p)->count = 0x26;
    ((Hdr_b001_01E00900 *)(s32)&p)->tag = 5;
    ((Hdr_b001_01E00900 *)(s32)&p)->regs = 0x42421;
    ((Hdr_b001_01E00900 *)(s32)&p)->pad = 0;
    p.r = 0x80;
    p.g = 0x80;
    p.b = 0x80;
    p.a = 0x60;
    p.q = 1.0f;
    p.x0 = 0x6BF8;
    p.y0 = 0x71F8;
    p.z0 = 0xFFFFFF;
    p.f0 = 0;
    p.x1 = 0x93F8;
    p.y1 = 0x8DF8;
    p.z1 = 0xFFFFFF;
    p.f1 = 0;
    p.s0 = 0.0f;
    p.t0 = 0.0f;
    p.s1 = 0.625f;
    p.t1 = 0.875f;
    func_002086D0(&p, ((u64)0x80 << 32) | 0x44);
    func_002087A0(&p, 1);
    func_002075F0((s32)&p, (s32)func_00207500(), 0);
    return 0;
}

/* OVL_WARM */

/* shape b105:01E00120, 479 insns, 10 copies. Calls the module colour helper at 0x1E00080 (shape b000:01E00100)
   as a plain extern: nothing is kept in a scratch register across that call. */


typedef struct {
    u8 b, g, r, a;
} Src_b105_01E00120;

typedef struct {
    u16 s : 14;
    u16 s_pad : 2;
    u16 t : 14;
    u16 t_pad : 2;
} Uv_b105_01E00120;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    union {
        Uv_b105_01E00120 i;
        f32 f[2];
    } st;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b105_01E00120;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b105_01E00120 v[4];
    u8 tail[0x20];
} Pkt_b105_01E00120;

typedef struct {
    f32 x, y, z, w;
} Vec_b105_01E00120;

typedef struct {
    f32 x, y, z;
} Pt_b105_01E00120;

typedef struct {
    void *texture;
    s32 flags;
    Src_b105_01E00120 color;
    f32 r;
    f32 spin[4];
    union {
        struct {
            s16 u, v, w, h;
        } i;
        struct {
            f32 u, v, w, h;
        } f;
    } uv;
    Vec_b105_01E00120 rots[60];
    Pt_b105_01E00120 pts[60];
} Spark_b105_01E00120;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_b105_01E00120;

extern void b143_01E00080(Pkt_b105_01E00120 *p, Src_b105_01E00120 *s);

static s32 func_01E00250_b143(s32 obj, Spark_b105_01E00120 *sp, Cam_b105_01E00120 *cam, s32 mode) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_00103620(void *, void *);
    extern void func_001036A0(void *, s32);
    extern void func_0020C630(void *, void *);
    extern void func_0020CDD0(void *, void *, void *);
    f32 depth[4];
    f32 m[16];
    Vec_b105_01E00120 a;
    Vec_b105_01E00120 b;
    Pkt_b105_01E00120 pkt;
    s32 i;
    f32 rx;
    f32 ry;

    ((Pkt_b105_01E00120 *)(s32)&pkt)->count = 0x34;
    ((Pkt_b105_01E00120 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_b105_01E00120 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_b105_01E00120 *)(s32)&pkt)->pad = 0;
    if (func_00104520(sp->flags, 0xC) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x44);
    } else if (func_00104520(sp->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(sp->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    b143_01E00080(&pkt, &sp->color);
    if (func_00104520(sp->flags, 0) != 0) {
        ((Pkt_b105_01E00120 *)(s32)&pkt)->count |= 0x800;
        ((Uv_b105_01E00120 *)(s32)&pkt.v[0].st)->s = sp->uv.i.u << 4;
        ((Uv_b105_01E00120 *)(s32)&pkt.v[0].st)->t = sp->uv.i.v << 4;
        ((Uv_b105_01E00120 *)(s32)&pkt.v[1].st)->s = (sp->uv.i.u + sp->uv.i.w - 1) << 4;
        ((Uv_b105_01E00120 *)(s32)&pkt.v[1].st)->t = sp->uv.i.v << 4;
        ((Uv_b105_01E00120 *)(s32)&pkt.v[2].st)->s = sp->uv.i.u << 4;
        ((Uv_b105_01E00120 *)(s32)&pkt.v[2].st)->t = (sp->uv.i.v + sp->uv.i.h - 1) << 4;
        ((Uv_b105_01E00120 *)(s32)&pkt.v[3].st)->s = (sp->uv.i.u + sp->uv.i.w - 1) << 4;
        ((Uv_b105_01E00120 *)(s32)&pkt.v[3].st)->t = (sp->uv.i.v + sp->uv.i.h - 1) << 4;
    } else {
        pkt.v[0].st.f[0] = sp->uv.f.u;
        pkt.v[0].st.f[1] = sp->uv.f.v;
        pkt.v[1].st.f[0] = sp->uv.f.u + sp->uv.f.w;
        pkt.v[1].st.f[1] = sp->uv.f.v;
        pkt.v[2].st.f[0] = sp->uv.f.u;
        pkt.v[2].st.f[1] = sp->uv.f.v + sp->uv.f.h;
        pkt.v[3].st.f[0] = sp->uv.f.u + sp->uv.f.w;
        pkt.v[3].st.f[1] = sp->uv.f.v + sp->uv.f.h;
    }
    if (func_00104520(sp->flags, 0x1E) != 0) {
        func_0020C630(m, sp->spin);
        for (i = 0; i < 60; i++) {
            b.x = sp->pts[i].x;
            b.y = sp->pts[i].y;
            b.z = sp->pts[i].z;
            func_0020CDD0(&a, m, &b);
            sp->pts[i].x = a.x;
            sp->pts[i].y = a.y;
            sp->pts[i].z = a.z;
        }
    }
    if (sp->uv.i.w == sp->uv.i.h) {
        rx = ry = sp->r;
    } else if (sp->uv.i.h < sp->uv.i.w) {
        rx = sp->r;
        ry = rx * ((f32)sp->uv.i.h / sp->uv.i.w);
    } else {
        ry = sp->r;
        rx = ry * ((f32)sp->uv.i.w / sp->uv.i.h);
    }
    for (i = 0; i < 60; i++) {
        func_001036A0(&sp->pts[i], mode);
        func_0020C630(m, &sp->rots[i]);
        a.x = -rx;
        a.y = ry;
        a.z = 0.0f;
        func_0020CDD0(&b, m, &a);
        func_00103620(&b, &sp->pts[i]);
        if (func_00205440(&b, cam->view, &pkt.v[0].st + 1, &depth[0]) != 0) {
            sp->flags |= 0x100000;
        }
        a.x = rx;
        a.y = ry;
        a.z = 0.0f;
        func_0020CDD0(&b, m, &a);
        func_00103620(&b, &sp->pts[i]);
        if (func_00205440(&b, cam->view, &pkt.v[1].st + 1, &depth[1]) != 0) {
            sp->flags |= 0x200000;
        }
        a.x = -rx;
        a.y = -ry;
        a.z = 0.0f;
        func_0020CDD0(&b, m, &a);
        func_00103620(&b, &sp->pts[i]);
        if (func_00205440(&b, cam->view, &pkt.v[2].st + 1, &depth[2]) != 0) {
            sp->flags |= 0x400000;
        }
        a.x = rx;
        a.y = -ry;
        a.z = 0.0f;
        func_0020CDD0(&b, m, &a);
        func_00103620(&b, &sp->pts[i]);
        if (func_00205440(&b, cam->view, &pkt.v[3].st + 1, &depth[3]) != 0) {
            sp->flags |= 0x800000;
        }
        func_00208700(&pkt, sp->texture, 0);
        if (func_00104520(sp->flags, 0x14) != 0 && func_00104520(sp->flags, 0x15) != 0 &&
            func_00104520(sp->flags, 0x16) != 0 && func_00104520(sp->flags, 0x17) != 0) {
            if (func_00104520(sp->flags, 0x13) != 0) {
                pkt.v[0].z = pkt.v[1].z = pkt.v[2].z = pkt.v[3].z = 0xFFFFFF;
                func_002075F0(&pkt, obj, 0);
            } else {
                func_002075F0(&pkt, obj, (u32)((depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f));
            }
        }
        sp->flags &= 0xFF0FFFFF;
    }
    return 0;
}

/* OVL_WARM */

/* shape b039:01E01B70, 1004 insns, 6 copies: draws an emitter's particles as camera-facing squares (one strip packet),
   sized by distance (and age with flag 0x1B), bobbing along z; UV or ST frames animate per particle; flag 0x1C
   first turns all points by the emitter's rotation. Same emitter layout as shape b000:01E01140. */

typedef struct {
    u8 b, g, r, a;
} Src_b039_01E01B70;

typedef struct {
    u64 u : 14;
    u64 pad0 : 2;
    u64 v : 14;
    u64 pad1 : 34;
} UV_b039_01E01B70;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b039_01E01B70;

typedef union {
    UV_b039_01E01B70 uv;
    struct {
        f32 s, t;
    } st;
} Tc_b039_01E01B70;

typedef struct {
    Tc_b039_01E01B70 tc;
    Xyz_b039_01E01B70 xyz;
} Vtx_b039_01E01B70;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Vtx_b039_01E01B70 v[4];
    u8 tail[0x20];
} Pkt_b039_01E01B70;

typedef struct {
    f32 x, y, z;
    u8 a;
    u8 frame;
    s16 t;
} Pt_b039_01E01B70;

typedef struct {
    void *texture;
    s32 flags;
    Src_b039_01E01B70 color;
    f32 size;
    u8 pad10[0x10];
    Vec4f rot;
    union {
        struct {
            s16 u, v, w, h;
            s16 u0, v0, tw, th;
        } i;
        struct {
            f32 s, t, w, h;
        } f;
    } r;
    Pt_b039_01E01B70 *pts;
    Vec4f *rots;
    u8 pad48[4];
    f32 radius;
    f32 grow;
    f32 amp;
    s16 freq;
    s16 count;
    s16 nframes;
    s16 rate;
} Emit_b039_01E01B70;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_b039_01E01B70;

#define UV1(k) ((UV_b039_01E01B70 *)(s32)&pkt.v[k].tc)

static s32 func_01E009D0_b143(s32 obj, Emit_b039_01E01B70 *e, Cam_b039_01E01B70 *cam __attribute__((aligned(16)))) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 depth[4];
    f32 m[16];
    Vec4f off;
    Vec4f tmp;
    Pkt_b039_01E01B70 pkt __attribute__((aligned(8)));
    s32 i;
    f32 w;

    ((Pkt_b039_01E01B70 *)(s32)&pkt)->count = 0x24;
    ((Pkt_b039_01E01B70 *)(s32)&pkt)->tag = 9;
    ((Pkt_b039_01E01B70 *)(s32)&pkt)->regs = ((u64)4 << 32) | 0x24242421;
    ((Pkt_b039_01E01B70 *)(s32)&pkt)->pad = 0;
    if (e->rate == 0) {
        e->rate = 1;
    }
    if (func_00104520(e->flags, 0xC) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x44);
    } else if (func_00104520(e->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(e->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    pkt.r = e->color.r;
    pkt.g = e->color.g;
    pkt.b = e->color.b;
    *(u8 *)(s32)&pkt.a = e->color.a;
    pkt.q = 1.0f;
    if (func_00104520(e->flags, 3) != 0) {
        if (func_00104520(e->flags, 0) != 0) {
            ((Pkt_b039_01E01B70 *)(s32)&pkt)->count |= 0x800;
            UV1(0)->u = e->r.i.u * 16;
            UV1(0)->v = e->r.i.v * 16;
            UV1(1)->u = (e->r.i.u + e->r.i.w - 1) * 16;
            UV1(1)->v = e->r.i.v * 16;
            UV1(2)->u = e->r.i.u * 16;
            UV1(2)->v = (e->r.i.v + e->r.i.h - 1) * 16;
            UV1(3)->u = (e->r.i.u + e->r.i.w - 1) * 16;
            UV1(3)->v = (e->r.i.v + e->r.i.h - 1) * 16;
        } else {
            pkt.v[0].tc.st.s = e->r.f.s;
            pkt.v[0].tc.st.t = e->r.f.t;
            pkt.v[1].tc.st.s = e->r.f.s + e->r.f.w;
            pkt.v[1].tc.st.t = e->r.f.t;
            pkt.v[2].tc.st.s = e->r.f.s;
            pkt.v[2].tc.st.t = e->r.f.t + e->r.f.h;
            pkt.v[3].tc.st.s = e->r.f.s + e->r.f.w;
            pkt.v[3].tc.st.t = e->r.f.t + e->r.f.h;
        }
    }
    if (func_00104520(e->flags, 0x1C) != 0) {
        func_0020C630(m, &e->rot);
        for (i = 0; i < e->count; i++) {
            tmp.x = e->pts[i].x;
            tmp.y = e->pts[i].y;
            tmp.z = e->pts[i].z;
            func_0020CDD0(&off, m, &tmp);
            e->pts[i].x = off.x;
            e->pts[i].y = off.y;
            e->pts[i].z = off.z;
        }
    }
    for (i = 0; i < e->count; i++) {
        if (e->pts[i].a < e->color.a) {
            *(u8 *)(s32)&pkt.a = e->pts[i].a;
        } else {
            *(u8 *)(s32)&pkt.a = e->color.a;
        }
        if (func_00104520(e->flags, 3) == 0) {
            if (func_00104520(e->flags, 0) != 0) {
                if (func_00104520(e->flags, 1) != 0) {
                    e->r.i.u = e->r.i.u0 + e->r.i.w * (e->pts[i].frame % (e->r.i.tw / e->r.i.w));
                    e->r.i.v = e->r.i.v0 + e->r.i.h * (e->pts[i].frame / (e->r.i.tw / e->r.i.w));
                } else {
                    e->r.i.u = e->r.i.u0 + e->r.i.w * (e->pts[i].frame / (e->r.i.th / e->r.i.h));
                    e->r.i.v = e->r.i.v0 + e->r.i.h * (e->pts[i].frame % (e->r.i.th / e->r.i.h));
                }
                ((Pkt_b039_01E01B70 *)(s32)&pkt)->count |= 0x800;
                UV1(0)->u = e->r.i.u * 16;
                UV1(0)->v = e->r.i.v * 16;
                UV1(1)->u = (e->r.i.u + e->r.i.w - 1) * 16;
                UV1(1)->v = e->r.i.v * 16;
                UV1(2)->u = e->r.i.u * 16;
                UV1(2)->v = (e->r.i.v + e->r.i.h - 1) * 16;
                UV1(3)->u = (e->r.i.u + e->r.i.w - 1) * 16;
                UV1(3)->v = (e->r.i.v + e->r.i.h - 1) * 16;
            } else {
                if (func_00104520(e->flags, 1) != 0) {
                    e->r.f.s = e->r.f.w * (e->pts[i].frame % (s16)(s32)(1.0f / e->r.f.w));
                    e->r.f.t = e->r.f.h * (e->pts[i].frame / (s16)(s32)(1.0f / e->r.f.w));
                } else {
                    e->r.f.s = e->r.f.w * (e->pts[i].frame / (s16)(s32)(1.0f / e->r.f.h));
                    e->r.f.t = e->r.f.h * (e->pts[i].frame % (s16)(s32)(1.0f / e->r.f.h));
                }
                pkt.v[0].tc.st.s = e->r.f.s;
                pkt.v[0].tc.st.t = e->r.f.t;
                pkt.v[1].tc.st.s = e->r.f.s + e->r.f.w;
                pkt.v[1].tc.st.t = e->r.f.t;
                pkt.v[2].tc.st.s = e->r.f.s;
                pkt.v[2].tc.st.t = e->r.f.t + e->r.f.h;
                pkt.v[3].tc.st.s = e->r.f.s + e->r.f.w;
                pkt.v[3].tc.st.t = e->r.f.t + e->r.f.h;
            }
        }
        off.x = e->pts[i].x;
        off.y = e->pts[i].y;
        off.z = e->pts[i].z - e->amp * func_0020B550(e->freq * e->pts[i].t);
        if (func_00205440(&off, cam->view, &pkt.v[0].xyz, &depth[0]) != 0 && func_00101600(&pkt.v[0].xyz) != 0) {
            e->flags |= 0xF00000;
        }
        depth[1] = depth[2] = depth[3] = depth[0];
        w = 20.0f * func_001018E0(e->size, depth[0]);
        if (func_00104520(e->flags, 0x1B) != 0) {
            w += e->grow * e->pts[i].t;
        }
        pkt.v[1].xyz.x = pkt.v[0].xyz.x + w;
        pkt.v[1].xyz.y = pkt.v[0].xyz.y - w;
        pkt.v[2].xyz.x = pkt.v[0].xyz.x - w;
        pkt.v[2].xyz.y = pkt.v[0].xyz.y + w;
        pkt.v[3].xyz.x = pkt.v[0].xyz.x + w;
        pkt.v[3].xyz.y = pkt.v[0].xyz.y + w;
        pkt.v[0].xyz.x = pkt.v[0].xyz.x - w;
        pkt.v[0].xyz.y = pkt.v[0].xyz.y - w;
        pkt.v[1].xyz.z = pkt.v[2].xyz.z = pkt.v[3].xyz.z = pkt.v[0].xyz.z;
        if (func_00104520(e->flags, 0x18) != 0) {
            func_00208700(&pkt, e->texture, 0);
        } else {
            if (func_00104520(e->flags, 0) != 0) {
                func_00208CB0(&pkt, (u64)0xA | ((u64)e->r.i.u << 4) | ((u64)(e->r.i.u + e->r.i.w - 1) << 14) |
                                        ((u64)e->r.i.v << 24) | ((u64)(e->r.i.v + e->r.i.h - 1) << 34));
            }
            func_00208700(&pkt, e->texture, 1);
        }
        if (func_00104520(e->flags, 0x14) != 0 && func_00104520(e->flags, 0x15) != 0 &&
            func_00104520(e->flags, 0x16) != 0 && func_00104520(e->flags, 0x17) != 0) {
            if (func_00104520(e->flags, 0x13) != 0) {
                pkt.v[0].xyz.z = pkt.v[1].xyz.z = pkt.v[2].xyz.z = pkt.v[3].xyz.z = 0xFFFFFF;
                if (e->pts[i].t >= 0) {
                    func_002075F0(&pkt, obj, 0);
                }
            } else if (e->pts[i].t >= 0) {
                func_002075F0(&pkt, obj, (u32)((depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f));
            }
        }
        e->flags &= 0xFF0FFFFF;
        if (func_00104520(e->flags, 3) == 0) {
            e->pts[i].t++;
            if (e->pts[i].t % e->rate == 0) {
                e->pts[i].frame++;
                if (e->nframes == e->pts[i].frame) {
                    e->pts[i].frame = 0;
                }
            }
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

static s32 func_01E01980_b143(s32 obj, Cam_b001_01E00A30 *cam, Emit_b001_01E00A30 *e, Vec_b001_01E00A30 *vel) {
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
    func_01E00080_b143((Vtx_b000_01E00100 *)&pkt, (Src_b000_01E00100 *)&e->color);
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

INCLUDE_ASM("asm/nonmatchings/mod/b143", func_01E02510_b143);

INCLUDE_ASM("asm/nonmatchings/mod/b143", func_01E02B60_b143);

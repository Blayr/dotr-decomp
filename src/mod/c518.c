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

static void func_01E00080_c518(Vtx_b000_01E00100 *v, Src_b000_01E00100 *s) {
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

/* shape c500:01E003D0, 149 insns: set up a 6-corner billboard: copy the module's corner template, store the id and
   half the size, then stretch x or y so the shape keeps the source's aspect (s16 w/h when flag 0 is set and flag
   0x1F is not, f32 w/h otherwise), and write corner = template * size/2 * stretch */

typedef struct {
    Vec4f v[6];
} Six_c500_01E003D0;

typedef struct {
    u8 pad0[4];
    s16 w;
    s16 h;
    f32 fw;
    f32 fh;
    u8 pad10[0x28];
    s32 flags;
} Src_c500_01E003D0;

typedef struct {
    s32 id;
    u8 pad4[4];
    f32 scale;
    u8 padC[4];
    s32 f10;
    s32 f14;
    s32 f18;
    u8 pad1C[4];
    Vec4f v[6];
} Bb_c500_01E003D0;

extern Six_c500_01E003D0 D_01E03900_c518;

static s32 func_01E00120_c518(Src_c500_01E003D0 *o, Bb_c500_01E003D0 *out, s32 id, f32 size) {
    Six_c500_01E003D0 q;
    f32 sx;
    f32 sy;
    f32 half;
    s32 i;

    q = D_01E03900_c518;
    out->f10 = out->f14 = out->f18 = 0;
    out->scale = size / 2.0f;
    out->id = id;
    if (func_00104520(o->flags, 0) != 0 && func_00104520(o->flags, 0x1F) == 0) {
        if (o->w > o->h >> 1) {
            sx = 1.0f;
            sy = o->w / (o->h / 2.0f);
        } else if (o->w < o->h >> 1) {
            sx = o->w / (o->h / 2.0f);
            sy = 1.0f;
        } else {
            sy = 1.0f;
            sx = sy;
        }
    } else {
        half = o->fh / 2.0f;
        if (o->fw > half) {
            sy = o->fw / half;
            sx = 1.0f;
        } else if (o->fw < half) {
            sx = o->fw / half;
            sy = 1.0f;
        } else {
            sy = 1.0f;
            sx = sy;
        }
    }
    for (i = 0; i < 6; i++) {
        out->v[i].x = sx * (out->scale * q.v[i].x);
        out->v[i].y = sy * (out->scale * q.v[i].y);
        out->v[i].z = out->scale * q.v[i].z;
    }
    return 0;
}

/* shape c500:01E00630, 465 insns: draws two textured quads of a 6-point strip (like b001:01E03860's ring):
   quad i uses points 2i, 4, 2i+1, 5 offset by the strip position, rotated by the object's angle when flag 0x1E
   is set; colour from the module helper c500:01E00080. */

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_c500_01E00630;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_c500_01E00630 v[4];
    u8 tail[0x20];
} Pkt_c500_01E00630;

typedef struct {
    s16 u, v, w, h;
    u8 pad8[0x2C];
    u8 color[4];
    s32 flags;
    u8 pad3C[4];
    s32 angle;
} Obj_c500_01E00630;

typedef struct {
    void *texture;
    s32 flags;
    u8 pad8[8];
    Vec4f pos;
    Vec4f pts[6];
} Strip_c500_01E00630;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_c500_01E00630;

extern void c518_01E00080(void *, void *);

static s32 func_01E00380_c518(s32 ot, Obj_c500_01E00630 *o, Strip_c500_01E00630 *s, Cam_c500_01E00630 *cam) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00104540(void *, void *, s32);
    extern void func_00104DC0(void *, void *);
    extern void func_0020C750(void *, void *, s32);
    extern void func_0020CDD0(void *, void *, void *);
    f32 depth[4];
    Vec4f p;
    Vec4f rv;
    f32 m[16];
    Pkt_c500_01E00630 pkt;
    s32 i;

    ((Pkt_c500_01E00630 *)(s32)&pkt)->count = 0x34;
    ((Pkt_c500_01E00630 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_c500_01E00630 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_c500_01E00630 *)(s32)&pkt)->pad = 0;
    if (func_00104520(o->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(o->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    c518_01E00080(&pkt, o->color);
    for (i = 0; i < 2; i++) {
        if (func_00104520(o->flags, 0x1F) != 0) {
            func_00104540(&pkt, o, 5);
        } else {
            func_00104DC0(&pkt, o);
        }
        if (func_00104520(o->flags, 0x1E) != 0) {
            rv.x = rv.z = rv.w = 0.0f;
            rv.y = 1.0f;
            func_0020C750(m, &rv, o->angle % 0x10000);
            func_0020CDD0(&p, m, &s->pts[i * 2]);
            p.x += s->pos.x;
            p.y += s->pos.y;
            p.z += s->pos.z;
            if (func_00205440(&p, cam->view, &pkt.v[0].st + 1, &depth[0]) != 0) {
                s->flags |= 0x100000;
            }
            func_0020CDD0(&p, m, &s->pts[4]);
            p.x += s->pos.x;
            p.y += s->pos.y;
            p.z += s->pos.z;
            if (func_00205440(&p, cam->view, &pkt.v[1].st + 1, &depth[1]) != 0) {
                s->flags |= 0x200000;
            }
            func_0020CDD0(&p, m, &s->pts[i * 2 + 1]);
            p.x += s->pos.x;
            p.y += s->pos.y;
            p.z += s->pos.z;
            if (func_00205440(&p, cam->view, &pkt.v[2].st + 1, &depth[2]) != 0) {
                s->flags |= 0x400000;
            }
            func_0020CDD0(&p, m, &s->pts[5]);
            p.x += s->pos.x;
            p.y += s->pos.y;
            p.z += s->pos.z;
            if (func_00205440(&p, cam->view, &pkt.v[3].st + 1, &depth[3]) != 0) {
                s->flags |= 0x800000;
            }
        } else {
            p.x = s->pos.x + s->pts[i * 2].x;
            p.y = s->pos.y + s->pts[i * 2].y;
            p.z = s->pos.z;
            if (func_00205440(&p, cam->view, &pkt.v[0].st + 1, &depth[0]) != 0) {
                s->flags |= 0x100000;
            }
            p.x = s->pos.x + s->pts[4].x;
            p.y = s->pos.y + s->pts[4].y;
            if (func_00205440(&p, cam->view, &pkt.v[1].st + 1, &depth[1]) != 0) {
                s->flags |= 0x200000;
            }
            p.x = s->pos.x + s->pts[i * 2 + 1].x;
            p.y = s->pos.y + s->pts[i * 2 + 1].y;
            if (func_00205440(&p, cam->view, &pkt.v[2].st + 1, &depth[2]) != 0) {
                s->flags |= 0x400000;
            }
            p.x = s->pos.x + s->pts[5].x;
            p.y = s->pos.y + s->pts[5].y;
            if (func_00205440(&p, cam->view, &pkt.v[3].st + 1, &depth[3]) != 0) {
                s->flags |= 0x800000;
            }
        }
        if (func_00104520(o->flags, 0x18) != 0) {
            func_00208700(&pkt, s->texture, 0);
        } else {
            if (func_00104520(o->flags, 0) != 0) {
                func_00208CB0(&pkt, (u64)0xA | ((u64)o->u << 4) | ((u64)(o->u + o->w - 1) << 14) |
                                        ((u64)o->v << 24) | ((u64)(o->v + o->h - 1) << 34));
            }
            func_00208700(&pkt, s->texture, 1);
        }
        if (func_00104520(s->flags, 0x14) != 0 && func_00104520(s->flags, 0x15) != 0 &&
            func_00104520(s->flags, 0x16) != 0 && func_00104520(s->flags, 0x17) != 0) {
            if (func_00104520(o->flags, 0x13) != 0) {
                pkt.v[0].z = pkt.v[1].z = pkt.v[2].z = pkt.v[3].z = 0xFFFFFF;
                func_002075F0(&pkt, ot, 0);
            } else {
                func_002075F0(&pkt, ot, func_001A23B0((depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f));
            }
        }
        s->flags &= 0xFF0FFFFF;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/c518", func_01E00AD0_c518);

/* func_00205440 is called unprototyped here */

/* shape b013:01E004E0, 757 insns, 40 copies: project the 8-point effect outline set up by b013:01E001A0 as
   quads (8 small squares for type 3, else 4 quads round the centre), flag what landed on screen and draw */

typedef struct Model_b013_01E004E0 {
    s16 x, y, w, h;
    u8 pad8[0x2C];
    Src_b000_01E00100 col;
    s32 tex;
} Model_b013_01E004E0;

typedef struct Fx_b013_01E004E0 {
    s32 kind;
    s32 flags;
    s32 type;
    f32 scale;
    Vec4f c;
    Vec4f v[8];
} Fx_b013_01E004E0;

typedef struct Cam_b013_01E004E0 {
    u8 pad0[0x30];
    u8 view[0x10];
} Cam_b013_01E004E0;

typedef struct Xyz_b013_01E004E0 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Xyz_b013_01E004E0;

typedef struct Vtx_b013_01E004E0 {
    u8 rgbaq[8];
    u64 st;
    Xyz_b013_01E004E0 xyz;
} Vtx_b013_01E004E0;

typedef struct Pk_b013_01E004E0 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Vtx_b013_01E004E0 v[4];
    u8 pad70[0x20];
} Pk_b013_01E004E0;

static inline void b013_01E004E0_tag(Pk_b013_01E004E0 *p, s32 size, s32 flags, u64 regs) {
    p->flags = flags;
    p->size = size;
    p->regs = regs;
    p->pad4 = 0;
}

static s32 func_01E00E10_c518(s32 id, Model_b013_01E004E0 *m, Fx_b013_01E004E0 *o, Cam_b013_01E004E0 *cam) {
    extern s32 func_00205440();
    s32 i;
    f32 z[4];
    Vec4f pos;
    Pk_b013_01E004E0 pk;

    b013_01E004E0_tag((Pk_b013_01E004E0 *)(u32)&pk, 0xC, 0x34, ((u64)0x4214 << 32) | 0x21421421);
    if (func_00104520(m->tex, 0xB) != 0) {
        func_002086D0(&pk, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(m->tex, 0xA) != 0) {
        func_002086D0(&pk, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pk, ((u64)0x80 << 32) | 0x48);
    }
    func_01E00080_c518((Vtx_b000_01E00100 *)&pk, &m->col);
    func_00104DC0(&pk, m);
    if (o->type == 3) {
        for (i = 0; i < 8; i++) {
            pos.x = o->v[i].x - o->scale;
            pos.y = o->v[i].y + o->scale;
            pos.z = o->v[i].z;
            if (func_00205440(&pos, cam->view, &pk.v[0].xyz, &z[0]) != 0) {
                o->flags |= 0x100000;
            }
            pos.x = o->v[i].x + o->scale;
            pos.y = o->v[i].y + o->scale;
            if (func_00205440(&pos, cam->view, &pk.v[1].xyz, &z[1]) != 0) {
                o->flags |= 0x200000;
            }
            pos.x = o->v[i].x - o->scale;
            pos.y = o->v[i].y - o->scale;
            if (func_00205440(&pos, cam->view, &pk.v[2].xyz, &z[2]) != 0) {
                o->flags |= 0x400000;
            }
            pos.x = o->v[i].x + o->scale;
            pos.y = o->v[i].y - o->scale;
            if (func_00205440(&pos, cam->view, &pk.v[3].xyz, &z[3]) != 0) {
                o->flags |= 0x800000;
            }
            if (func_00104520(m->tex, 0x18) != 0) {
                func_00208700(&pk, (void *)o->kind, 0);
            } else {
                if (func_00104520(m->tex, 0) != 0) {
                    func_00208CB0(&pk, (u64)2 | ((u64)2 << 2) | ((u64)m->x << 4) | ((u64)(m->x + m->w - 1) << 14) |
                                           ((u64)m->y << 24) | ((u64)(m->y + m->h - 1) << 34));
                }
                func_00208700(&pk, (void *)o->kind, 1);
            }
            if (func_00104520(o->flags, 0x14) != 0 && func_00104520(o->flags, 0x15) != 0 &&
                func_00104520(o->flags, 0x16) != 0 && func_00104520(o->flags, 0x17) != 0) {
                if (func_00104520(m->tex, 0x13) != 0) {
                    pk.v[0].xyz.z = pk.v[1].xyz.z = pk.v[2].xyz.z = pk.v[3].xyz.z = 0xFFFFFF;
                    func_002075F0((s32)&pk, id, 0);
                } else {
                    func_002075F0((s32)&pk, id, (u32)((z[0] + z[1] + z[2] + z[3]) / 4.0f));
                }
                o->flags &= 0xFF0FFFFF;
            }
        }
    } else {
        for (i = 0; i < 4; i++) {
            if (o->type == 1 || o->type == 5) {
                pos.x = o->c.x + o->v[i + i + 1].x;
                pos.y = o->c.y + o->v[i + i + 1].y;
                pos.z = o->c.z + o->v[i + i + 1].z;
                if (func_00205440(&pos, cam->view, &pk.v[0].xyz, &z[0]) != 0) {
                    o->flags |= 0x100000;
                }
                if (i < 2) {
                    pos.x = o->c.x + o->v[2].x;
                    pos.y = o->c.y + o->v[2].y;
                    pos.z = o->c.z + o->v[2].z;
                    if (func_00205440(&pos, cam->view, &pk.v[1].xyz, &z[1]) != 0) {
                        o->flags |= 0x200000;
                    }
                } else {
                    pos.x = o->c.x + o->v[6].x;
                    pos.y = o->c.y + o->v[6].y;
                    pos.z = o->c.z + o->v[6].z;
                    if (func_00205440(&pos, cam->view, &pk.v[1].xyz, &z[1]) != 0) {
                        o->flags |= 0x200000;
                    }
                }
                if (i == 1 || i == 2) {
                    pos.x = o->c.x + o->v[4].x;
                    pos.y = o->c.y + o->v[4].y;
                    pos.z = o->c.z + o->v[4].z;
                    if (func_00205440(&pos, cam->view, &pk.v[2].xyz, &z[2]) != 0) {
                        o->flags |= 0x400000;
                    }
                } else {
                    pos.x = o->c.x + o->v[0].x;
                    pos.y = o->c.y + o->v[0].y;
                    pos.z = o->c.z + o->v[0].z;
                    if (func_00205440(&pos, cam->view, &pk.v[2].xyz, &z[2]) != 0) {
                        o->flags |= 0x400000;
                    }
                }
                if (func_00205440(&o->c, cam->view, &pk.v[3].xyz, &z[3]) != 0) {
                    o->flags |= 0x800000;
                }
            } else if (o->type == 2 || o->type == 6) {
                pos.x = o->c.x + o->v[i * 2 + 1].x;
                pos.y = o->c.y + o->v[i * 2 + 1].y;
                pos.z = o->c.z + o->v[i * 2 + 1].z;
                if (func_00205440(&pos, cam->view, &pk.v[0].xyz, &z[0]) != 0) {
                    o->flags |= 0x100000;
                }
                if (i != 3) {
                    pos.x = o->c.x + o->v[i * 2 + 2].x;
                    pos.y = o->c.y + o->v[i * 2 + 2].y;
                    pos.z = o->c.z + o->v[i * 2 + 2].z;
                    if (func_00205440(&pos, cam->view, &pk.v[1].xyz, &z[1]) != 0) {
                        o->flags |= 0x200000;
                    }
                } else {
                    pos.x = o->c.x + o->v[0].x;
                    pos.y = o->c.y + o->v[0].y;
                    pos.z = o->c.z + o->v[0].z;
                    if (func_00205440(&o->v[0], cam->view, &pk.v[1].xyz, &z[1]) != 0) {
                        o->flags |= 0x200000;
                    }
                }
                pos.x = o->c.x + o->v[i * 2].x;
                pos.y = o->c.y + o->v[i * 2].y;
                pos.z = o->c.z + o->v[i * 2].z;
                if (func_00205440(&o->v[i * 2], cam->view, &pk.v[2].xyz, &z[2]) != 0) {
                    o->flags |= 0x400000;
                }
                if (func_00205440(&o->c, cam->view, &pk.v[3].xyz, &z[3]) != 0) {
                    o->flags |= 0x800000;
                }
            }
            if (func_00104520(m->tex, 0x18) != 0) {
                func_00208700(&pk, (void *)o->kind, 0);
            } else {
                if (func_00104520(m->tex, 0) != 0) {
                    func_00208CB0(&pk, (u64)2 | ((u64)2 << 2) | ((u64)m->x << 4) | ((u64)(m->x + m->w - 1) << 14) |
                                           ((u64)m->y << 24) | ((u64)(m->y + m->h - 1) << 34));
                }
                func_00208700(&pk, (void *)o->kind, 1);
            }
            if (func_00104520(o->flags, 0x14) != 0 && func_00104520(o->flags, 0x15) != 0 &&
                func_00104520(o->flags, 0x16) != 0 && func_00104520(o->flags, 0x17) != 0) {
                if (func_00104520(m->tex, 0x13) != 0) {
                    pk.v[0].xyz.z = pk.v[1].xyz.z = pk.v[2].xyz.z = pk.v[3].xyz.z = 0xFFFFFF;
                    func_002075F0((s32)&pk, id, 0);
                } else {
                    func_002075F0((s32)&pk, id, (u32)((z[0] + z[1] + z[2] + z[3]) / 4.0f));
                }
            }
            o->flags &= 0xFF0FFFFF;
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

static s32 func_01E019F0_c518(Ring_b001_01E035A0 *o, s32 type, f32 inner, f32 outer, f32 y, f32 height) {
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
   It calls the module's colour helper (shape b000:01E00100, here func_01E00080_c518) and needs that helper
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

static s32 func_01E01CB0_c518(s32 obj, Ring_b001_01E03860 *ring, Cam_b001_01E03860 *cam) {
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
        func_01E00080_c518(&pkt, &ring->color);
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

INCLUDE_ASM("asm/nonmatchings/mod/c518", func_01E021A0_c518);

/* shape b000:01E03420, 387 insns, 68 copies: draws a textured sprite quad: n rotations of its 4 corner points,
   UV (texel) or ST coordinates from the sprite rect, depth-sorted unless flag 0x13/0x12.
   Calls the module's colour helper (shape b000:01E00100), included above as a static function. */

typedef struct {
    u8 b, g, r, a;
} Src_b000_01E03420;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    union {
        struct {
            f32 s, t;
        } st;
        struct {
            u64 u : 14;
            u64 pad0 : 2;
            u64 v : 14;
            u64 pad1 : 34;
        } uv;
    } tc;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b000_01E03420;

typedef struct {
    u64 u : 14;
    u64 pad0 : 2;
    u64 v : 14;
    u64 pad1 : 34;
} UV_b000_01E03420;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b000_01E03420 v[4];
    u8 tail[0x20];
} Pkt_b000_01E03420;

typedef struct {
    f32 x, y, z, w;
} Vec_b000_01E03420;

typedef struct {
    void *texture;
    s32 flags;
    Src_b000_01E03420 color;
    u8 pad0C[4];
    union {
        struct {
            s16 u, v, w, h;
        } i;
        struct {
            f32 s, t, w, h;
        } f;
    } rect;
    Vec_b000_01E03420 p[4];
    Vec_b000_01E03420 rot[1];
} Spr_b000_01E03420;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_b000_01E03420;

static s32 func_01E02300_c518(s32 obj, Spr_b000_01E03420 *spr, Cam_b000_01E03420 *cam) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    s32 n[1];
    Vec_b000_01E03420 out;
    f32 m[16];
    f32 depth[4];
    Pkt_b000_01E03420 pkt;
    s32 i;
    s32 t;

    t = func_00104520(spr->flags, 0x1F);
    n[0] = 0x10;
    n[0] = t ? n[0] : 0x40;
    ((Pkt_b000_01E03420 *)(s32)&pkt)->count = 0x34;
    ((Pkt_b000_01E03420 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_b000_01E03420 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_b000_01E03420 *)(s32)&pkt)->pad = 0;
    if (func_00104520(spr->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(spr->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    func_01E00080_c518((Vtx_b000_01E00100 *)&pkt, (Src_b000_01E00100 *)&spr->color);
    if (func_00104520(spr->flags, 0) != 0) {
        ((Pkt_b000_01E03420 *)(s32)&pkt)->count |= 0x800;
        ((UV_b000_01E03420 *)(s32)&pkt.v[0].tc)->u = spr->rect.i.u * 16;
        ((UV_b000_01E03420 *)(s32)&pkt.v[0].tc)->v = spr->rect.i.v * 16;
        ((UV_b000_01E03420 *)(s32)&pkt.v[1].tc)->u = (spr->rect.i.u + spr->rect.i.w - 1) * 16;
        ((UV_b000_01E03420 *)(s32)&pkt.v[1].tc)->v = spr->rect.i.v * 16;
        ((UV_b000_01E03420 *)(s32)&pkt.v[2].tc)->u = spr->rect.i.u * 16;
        ((UV_b000_01E03420 *)(s32)&pkt.v[2].tc)->v = (spr->rect.i.v + spr->rect.i.h - 1) * 16;
        ((UV_b000_01E03420 *)(s32)&pkt.v[3].tc)->u = (spr->rect.i.u + spr->rect.i.w - 1) * 16;
        ((UV_b000_01E03420 *)(s32)&pkt.v[3].tc)->v = (spr->rect.i.v + spr->rect.i.h - 1) * 16;
    } else {
        pkt.v[0].tc.st.s = spr->rect.f.s;
        pkt.v[0].tc.st.t = spr->rect.f.t;
        pkt.v[1].tc.st.s = spr->rect.f.s + spr->rect.f.w;
        pkt.v[1].tc.st.t = spr->rect.f.t;
        pkt.v[2].tc.st.s = spr->rect.f.s;
        pkt.v[2].tc.st.t = spr->rect.f.t + spr->rect.f.h;
        pkt.v[3].tc.st.s = spr->rect.f.s + spr->rect.f.w;
        pkt.v[3].tc.st.t = spr->rect.f.t + spr->rect.f.h;
    }
    for (i = 0; i < n[0]; i++) {
        func_0020C630(m, &spr->rot[i]);
        func_0020CDD0(&out, m, &spr->p[0]);
        if (func_00205440(&out, cam->view, &pkt.v[0].tc + 1, &depth[0]) != 0) {
            spr->flags |= 0x100000;
        }
        func_0020CDD0(&out, m, &spr->p[1]);
        if (func_00205440(&out, cam->view, &pkt.v[1].tc + 1, &depth[1]) != 0) {
            spr->flags |= 0x200000;
        }
        func_0020CDD0(&out, m, &spr->p[2]);
        if (func_00205440(&out, cam->view, &pkt.v[2].tc + 1, &depth[2]) != 0) {
            spr->flags |= 0x400000;
        }
        func_0020CDD0(&out, m, &spr->p[3]);
        if (func_00205440(&out, cam->view, &pkt.v[3].tc + 1, &depth[3]) != 0) {
            spr->flags |= 0x800000;
        }
        func_00208700(&pkt, spr->texture, 0);
        if (func_00104520(spr->flags, 0x14) != 0 && func_00104520(spr->flags, 0x15) != 0 &&
            func_00104520(spr->flags, 0x16) != 0 && func_00104520(spr->flags, 0x17) != 0) {
            if (func_00104520(spr->flags, 0x13) != 0) {
                pkt.v[0].z = pkt.v[1].z = pkt.v[2].z = pkt.v[3].z = 0xFFFFFF;
                func_002075F0(&pkt, obj, 0);
            } else if (func_00104520(spr->flags, 0x12) != 0) {
                func_002075F0(&pkt, obj, 0xFFFFFF);
            } else {
                func_002075F0(&pkt, obj, func_001A23B0((depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f));
            }
        }
        spr->flags &= 0xFF0FFFFF;
    }
    return 0;
}

/* shape c518:01E02910, 108 insns: lay out a 10 x 6 grid of points from the module's x and y tables, scaled by
   the given size (x mirrored when flip is set); each point gets a random variant 0..7 and a random value 0..4;
   func_0019A5B0 is called with the point's index first */

typedef struct {
    f32 x[10];
} Xs_c518_01E02910;

typedef struct {
    f32 y[6];
} Ys_c518_01E02910;

typedef struct {
    f32 x, y;
    u8 pad8[4];
    u8 b;
    u8 kind;
    s16 v;
} Pt_c518_01E02910;

typedef struct {
    u8 pad0[0xC];
    f32 scale;
    u8 pad10[0x10];
    Pt_c518_01E02910 p[60];
    u8 pad3E0[0xA];
    s16 f3EA;
} Grid_c518_01E02910;

extern Xs_c518_01E02910 D_01E03AA0_c518;
extern Ys_c518_01E02910 D_01E03AD0_c518;

static s32 func_01E02910_c518(Grid_c518_01E02910 *o, s32 flip, f32 scale) {
    extern void func_0019A5B0(s32);
    Xs_c518_01E02910 xs;
    Ys_c518_01E02910 ys;
    s32 k;
    s32 j;
    s32 i;

    xs = D_01E03AA0_c518;
    ys = D_01E03AD0_c518;
    o->scale = scale;
    o->f3EA = 0;
    for (i = 0; i < 60;) {
        for (j = 0; j < 6; j++) {
            for (k = 0; k < 10; k++) {
                func_0019A5B0(i);
                if (flip == 0) {
                    o->p[i].x = o->scale * xs.x[k];
                } else {
                    o->p[i].x = o->scale * xs.x[9 - k];
                }
                o->p[i].y = o->scale * ys.y[j];
                o->p[i].b = 0;
                o->p[i].kind = func_0019A5C8() % 8;
                o->p[i].v = func_0019A5C8() % 5;
                i++;
            }
        }
    }
    return 0;
}

/* shape c518:01E02AC0, 453 insns, 2 copies: draws up to 60 glyph cells as textured squares (each picks its tile from the
   atlas by its character, placed at its scaled position), visibility flagged on the object (bits 20..23); fades
   each shown cell in, then shows one more cell per frame up to 60 (the original passes the cell count, not the
   flags, to the flag test there). Colour by the module helper (shape b000:01E00100). */

typedef struct {
    u16 s : 14;
    u16 s_pad : 2;
    u16 t : 14;
    u16 t_pad : 2;
    u32 pad;
} Uv_c518_01E02AC0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Uv_c518_01E02AC0 st;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_c518_01E02AC0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_c518_01E02AC0 v[4];
    u8 tail[0x20];
} Pkt_c518_01E02AC0;

typedef struct {
    f32 x, y;
    u8 pad8[4];
    u8 a;
    u8 ch;
    u8 padE[2];
} Cell_c518_01E02AC0;

typedef struct {
    void *texture;
    s32 flags;
    u8 col[4];
    f32 size;
    s16 u, v, w, h;
    s16 u0, v0;
    s16 aw;
    u8 pad1E[2];
    Cell_c518_01E02AC0 cells[60];
    u8 pad3E0[0xA];
    s16 count;
} Text_c518_01E02AC0;

typedef struct {
    u8 pad0[0x30];
    f32 m[16];
} Cam_c518_01E02AC0;

static s32 func_01E02AC0_c518(s32 ot, Text_c518_01E02AC0 *o, Cam_c518_01E02AC0 *cam, f32 scale) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 d[4];
    Vec4f p;
    Pkt_c518_01E02AC0 pkt;
    s32 i;

    ((Pkt_c518_01E02AC0 *)(s32)&pkt)->count = 0x34;
    ((Pkt_c518_01E02AC0 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_c518_01E02AC0 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_c518_01E02AC0 *)(s32)&pkt)->pad = 0;
    func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    for (i = 0; i < 60; i++) {
        func_01E00080_c518((Vtx_b000_01E00100 *)&pkt, (Src_b000_01E00100 *)o->col);
        if (func_00104520(o->flags, 0x10) == 0) {
            pkt.v[0].a = pkt.v[1].a = pkt.v[2].a = pkt.v[3].a = o->cells[i].a;
        }
        o->u = o->u0 + o->w * (o->cells[i].ch % (o->aw / o->w));
        o->v = o->v0 + o->h * (o->cells[i].ch / (o->aw / o->w));
        ((Pkt_c518_01E02AC0 *)(s32)&pkt)->count |= 0x800;
        pkt.v[0].st.s = o->u * 16;
        ((Uv_c518_01E02AC0 *)(s32)&pkt.v[0].st)->t = o->v * 16;
        pkt.v[1].st.s = (o->u + o->w - 1) * 16;
        ((Uv_c518_01E02AC0 *)(s32)&pkt.v[1].st)->t = o->v * 16;
        pkt.v[2].st.s = o->u * 16;
        ((Uv_c518_01E02AC0 *)(s32)&pkt.v[2].st)->t = (o->v + o->h - 1) * 16;
        pkt.v[3].st.s = (o->u + o->w - 1) * 16;
        ((Uv_c518_01E02AC0 *)(s32)&pkt.v[3].st)->t = (o->v + o->h - 1) * 16;
        p.x = o->cells[i].x * scale;
        p.y = o->cells[i].y * scale;
        p.z = 10.0f;
        if (func_00205440(&p, cam->m, &pkt.v[0].st + 1, &d[0]) != 0) {
            o->flags |= 0x100000;
        }
        p.x = scale * (o->cells[i].x + o->size);
        p.y = o->cells[i].y * scale;
        if (func_00205440(&p, cam->m, &pkt.v[1].st + 1, &d[1]) != 0) {
            o->flags |= 0x200000;
        }
        p.x = o->cells[i].x * scale;
        p.y = scale * (o->cells[i].y - o->size);
        if (func_00205440(&p, cam->m, &pkt.v[2].st + 1, &d[2]) != 0) {
            o->flags |= 0x400000;
        }
        p.x = scale * (o->cells[i].x + o->size);
        p.y = scale * (o->cells[i].y - o->size);
        if (func_00205440(&p, cam->m, &pkt.v[3].st + 1, &d[3]) != 0) {
            o->flags |= 0x800000;
        }
        if (func_00104520(o->flags, 0x18) != 0) {
            func_00208700(&pkt, o->texture, 0);
        } else {
            func_00208CB0(&pkt, ((u64)o->v << 24) | (((u64)o->u << 4) | 0xA | ((u64)(o->u + o->w - 1) << 14)) |
                                    ((u64)(o->v + o->h - 1) << 34));
            func_00208700(&pkt, o->texture, 1);
        }
        if (func_00104520(o->flags, 0x14) != 0 && func_00104520(o->flags, 0x15) != 0 &&
            func_00104520(o->flags, 0x16) != 0 && func_00104520(o->flags, 0x17) != 0) {
            if (func_00104520(o->flags, 0x13) != 0) {
                pkt.v[0].z = pkt.v[1].z = pkt.v[2].z = pkt.v[3].z = 0xFFFFFF;
                func_002075F0(&pkt, ot, 0);
            } else {
                func_002075F0(&pkt, ot, (u32)((d[3] + (d[2] + (d[0] + d[1]))) / 4.0f));
            }
        }
        o->flags &= 0xFF0FFFFF;
    }
    for (i = 0; i < o->count; i++) {
        if (o->cells[i].a < 0x80) {
            o->cells[i].a += 0x20;
        } else {
            o->cells[i].a = 0x80;
        }
    }
    if (func_00104520(o->count, 0x10) == 0) {
        if (o->count < 60) {
            o->count++;
        } else {
            o->count = 60;
            o->flags |= 0x10000;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/c518", func_01E031E0_c518);

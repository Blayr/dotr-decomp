#include "common.h"

/* shape b000:01E00080, 31 insns, 12 copies: colour the two vertices of a line packet; mode 0 = colour on the
   first vertex (second black), else on the second (first black); alpha and q = 1.0 on both */

typedef struct Src_b000_01E00080 {
    u8 b, g, r, a;
} Src_b000_01E00080;

typedef struct Xyz_b000_01E00080 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b000_01E00080;

typedef struct Vtx_b000_01E00080 {
    u8 r, g, b, a;
    f32 q;
    Xyz_b000_01E00080 p;
} Vtx_b000_01E00080;

typedef struct Pk_b000_01E00080 {
    u8 head[0x10];
    Vtx_b000_01E00080 v[2];
} Pk_b000_01E00080;


/* static in its module (callers that include this file #define OVL_LOCAL static first) */

static void func_01E00080_c560(Pk_b000_01E00080 *p, Src_b000_01E00080 *s, s32 mode) {
    if (mode == 0) {
        p->v[0].r = s->r;
        p->v[0].g = s->g;
        p->v[0].b = s->b;
        p->v[1].r = 0;
        p->v[1].g = 0;
        p->v[1].b = 0;
    } else {
        p->v[0].r = 0;
        p->v[0].g = 0;
        p->v[0].b = 0;
        p->v[1].r = s->r;
        p->v[1].g = s->g;
        p->v[1].b = s->b;
    }
    p->v[0].a = s->a;
    p->v[0].q = 1.0f;
    p->v[1].a = s->a;
    p->v[1].q = 1.0f;
    p->v[0].p.f = 0;
    p->v[1].p.f = 0;
}

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

static void func_01E00100_c560(Vtx_b000_01E00100 *v, Src_b000_01E00100 *s) {
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

INCLUDE_ASM("asm/nonmatchings/mod/c560", func_01E001A0_c560);

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

static s32 func_01E004E0_c560(s32 id, Model_b013_01E004E0 *m, Fx_b013_01E004E0 *o, Cam_b013_01E004E0 *cam) {
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
    func_01E00100_c560((Vtx_b000_01E00100 *)&pk, &m->col);
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

/* shape b000:01E00400, 87 insns, 46 copies: one flat-coloured full-screen quad (GS sprite packet, far z). The tag
   is written through a pointer that went through u32 (a plain &pk gets folded into $sp offsets). */

typedef struct Xyz_b000_01E00400 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Xyz_b000_01E00400;

typedef struct Pk_b000_01E00400 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Xyz_b000_01E00400 v[4];
} Pk_b000_01E00400;

typedef struct Src_b000_01E00400 {
    u8 b, g, r, a;
} Src_b000_01E00400;

static inline void b000_01E00400_tag(Pk_b000_01E00400 *p, s32 size, s32 flags, u64 regs) {
    p->flags = flags;
    p->size = size;
    p->regs = regs;
    p->pad4 = 0;
}

static s32 func_01E010C0_c560(s32 arg0, Src_b000_01E00400 *c) {
    Pk_b000_01E00400 pk;

    b000_01E00400_tag((Pk_b000_01E00400 *)(u32)&pk, 5, 4, 0x44441);
    func_002086D0((Pk_b000_01E00400 *)(u32)&pk, ((u64)0x80 << 32) | 0x48);
    pk.r = c->r;
    pk.g = c->g;
    pk.b = c->b;
    pk.a = c->a;
    pk.q = 1.0f;
    pk.v[0].x = 0x6000;
    pk.v[0].y = 0x7000;
    pk.v[0].z = 0xFFFFFF;
    pk.v[0].fog = 0;
    pk.v[1].x = 0xA000;
    pk.v[1].y = 0x7000;
    pk.v[1].z = 0xFFFFFF;
    pk.v[1].fog = 0;
    pk.v[2].x = 0x6000;
    pk.v[2].y = 0x9000;
    pk.v[2].z = 0xFFFFFF;
    pk.v[2].fog = 0;
    pk.v[3].x = 0xA000;
    pk.v[3].y = 0x9000;
    pk.v[3].z = 0xFFFFFF;
    pk.v[3].fog = 0;
    func_002075F0((s32)&pk, arg0, 0);
    return 0;
}

/* shape b000:01E04EC0, 148 insns, 12 copies: seed n points with random positions: flag 0x1D set and v < 0:
   +-50 / +-50 / 0..50, flag set and v >= 0: +-240 / +-240 / 240..480, flag clear: tenths of +-240 / 0..240 */

typedef struct Pt_b000_01E04EC0 {
    f32 x, y, z, w;
} Pt_b000_01E04EC0;

typedef struct Obj_b000_01E04EC0 {
    s32 flags;
    u8 pad4[4];
    f32 f8;
    s32 count;
    Pt_b000_01E04EC0 pts[1];
} Obj_b000_01E04EC0;

static s32 func_01E01220_c560(Obj_b000_01E04EC0 *o, s32 n, f32 v) {
    extern f32 func_001A6970(f32);
    extern s32 func_0019A5C8();
    s32 i;

    o->f8 = func_001A6970(v);
    o->count = n;
    for (i = 0; i < o->count; i++) {
        if (func_00104520(o->flags, 0x1D) != 0) {
            if (v < 0.0f) {
                o->pts[i].x = func_0019A5C8() % 100 - 50;
                o->pts[i].y = func_0019A5C8() % 100 - 50;
                o->pts[i].z = func_0019A5C8() % 50;
            } else {
                o->pts[i].x = func_0019A5C8() % 480 - 240;
                o->pts[i].y = func_0019A5C8() % 480 - 240;
                o->pts[i].z = func_0019A5C8() % 240 + 240;
            }
        } else {
            o->pts[i].x = 0.1f * (func_0019A5C8() % 480 - 240);
            o->pts[i].z = 0.1f * (func_0019A5C8() % 480 - 240);
            o->pts[i].y = 0.1f * (func_0019A5C8() % 240);
        }
    }
    return 0;
}

/* shape b000:01E05110, 344 insns, 12 copies: draws falling streaks (rain/snow): each point is drawn as a line
   from it along its normalised direction, then moved; points that fall past the floor are reseeded (the two
   ranges of b000:01E04EC0); drawn twice with flag 0x1C. Calls the module's line colour helper (b000:01E00080),
   included above as a static function. */

typedef struct Pt_b000_01E05110 {
    f32 x, y, z, w;
} Pt_b000_01E05110;

typedef struct Obj_b000_01E05110 {
    s32 flags;
    Src_b000_01E00080 color;
    f32 len;
    s32 count;
    Pt_b000_01E05110 pts[1];
} Obj_b000_01E05110;

typedef struct Cam_b000_01E05110 {
    u8 pad[0x30];
    f32 view[1];
} Cam_b000_01E05110;

typedef struct LPk_b000_01E05110 {
    s16 size;
    s16 flags;
    s32 pad4;
    u64 regs;
    Vtx_b000_01E00080 v[2];
} LPk_b000_01E05110;

static s32 func_01E01470_c560(s32 obj, Obj_b000_01E05110 *o, Cam_b000_01E05110 *cam, f32 v) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_0020D070();
    extern s32 func_0019A5C8();
    Vec4f a;
    Vec4f b;
    LPk_b000_01E05110 pk;
    f32 depth[2];
    s32 i;

    ((LPk_b000_01E05110 *)(s32)&pk)->flags = 0x11;
    ((LPk_b000_01E05110 *)(s32)&pk)->size = 4;
    ((LPk_b000_01E05110 *)(s32)&pk)->regs = 0x4141;
    ((LPk_b000_01E05110 *)(s32)&pk)->pad4 = 0;
    func_002086D0(&pk, ((u64)0x80 << 32) | 0x48);
    for (i = 0; i < o->count; i++) {
        if (!(v < 0.0f)) {
            func_01E00080_c560((Pk_b000_01E00080 *)&pk, &o->color, 0);
        } else {
            func_01E00080_c560((Pk_b000_01E00080 *)&pk, &o->color, 1);
        }
        a.x = b.x = o->pts[i].x;
        a.y = b.y = o->pts[i].y;
        a.z = b.z = o->pts[i].z;
        if (func_00205440(&a, cam->view, &pk.v[0].p, &depth[0]) != 0) {
            o->flags |= 0x100000;
        }
        func_0020D070(&a);
        b.x += a.x * o->len;
        b.y += a.y * o->len;
        b.z += a.z * o->len;
        if (func_00205440(&b, cam->view, &pk.v[1].p, &depth[1]) != 0) {
            o->flags |= 0x200000;
        }
        o->pts[i].x -= a.x * v;
        o->pts[i].y -= a.y * v;
        o->pts[i].z -= a.z * v;
        if (func_00104520(o->flags, 0x1D) != 0) {
            if (!(o->pts[i].z < 300.0f)) {
                o->pts[i].x = 0.1f * (func_0019A5C8() % 480 - 240);
                o->pts[i].y = 0.1f * (func_0019A5C8() % 480 - 240);
                o->pts[i].z = 0.1f * (func_0019A5C8() % 240);
            }
        } else if (o->pts[i].y <= 0.0f) {
            o->pts[i].x = 0.1f * (func_0019A5C8() % 480 - 240);
            o->pts[i].z = 0.1f * (func_0019A5C8() % 480 - 240);
            o->pts[i].y = 0.1f * (func_0019A5C8() % 240);
        }
        if (func_00104520(o->flags, 0x14) != 0 && func_00104520(o->flags, 0x15) != 0) {
            if (func_00104520(o->flags, 0x13) != 0) {
                pk.v[0].p.z = pk.v[1].p.z = 0xFFFFFF;
                func_002075F0(&pk, obj, 0);
                if (func_00104520(o->flags, 0x1C) != 0) {
                    func_002075F0(&pk, obj, 0);
                }
            } else {
                func_002075F0(&pk, obj, func_001A23B0((depth[0] + depth[1]) / 2.0f));
                if (func_00104520(o->flags, 0x1C) != 0) {
                    func_002075F0(&pk, obj, func_001A23B0((depth[0] + depth[1]) / 2.0f));
                }
            }
        }
        o->flags &= 0xFF0FFFFF;
    }
    return 0;
}

/* shape c560:01E019D0, 158 insns: c560's quarter-wave table lookup (91 floats, 0..90 degrees): returns the sine of the
   angle (mode 0) or its cosine (mode != 0), the angle first wrapped into 0..359 */

static f32 func_01E019D0_c560(f32 *tab, s16 a, s32 mode) {
    s16 b;
    f32 r;

    if (mode == 0) {
        if (a >= 360) {
            a %= 360;
        }
        if (a < -359) {
            a %= 360;
        }
        if (a < 0) {
            a += 360;
        }
        if (a < 90) {
            tab += a;
            r = *tab;
        } else if (a < 180) {
            b = a - 90;
            tab += 90 - b;
            r = *tab;
        } else if (a < 270) {
            b = a - 180;
            tab += b;
            r = *tab;
            r *= -1.0f;
        } else {
            b = a - 270;
            tab += 90 - b;
            r = *tab;
            r *= -1.0f;
        }
    } else {
        if (a >= 360) {
            a %= 360;
        }
        if (a < -359) {
            a %= 360;
        }
        if (a < 0) {
            a += 360;
        }
        if (a < 90) {
            tab += 90 - a;
            r = *tab;
        } else if (a < 180) {
            b = a - 90;
            tab += b;
            r = *tab;
            r *= -1.0f;
        } else if (a < 270) {
            b = a - 180;
            tab += 90 - b;
            r = *tab;
            r *= -1.0f;
        } else {
            b = a - 270;
            tab += b;
            r = *tab;
        }
    }
    return r;
}

/* shape c560:01E01C50, 123 insns: c560 trail link in a 20-slot list (0x5C bytes at ctx+0x1FC): takes the first free slot (marks it slot+1), copies the context's colour twice, its size as shorts, height 13 above, both clamped to 50, chains after the context's last piece and becomes it; returns 1, or 0 when full */

/* OVL_WARM */

typedef struct {
    u8 r, g, b, a;
} Col_c560_01E01C50;

typedef struct Ent_c560_01E01C50 {
    u8 pad0[4];
    f32 f4;
    u8 pad8[0xC];
    f32 f14;
    u8 pad18[0x18];
    Col_c560_01E01C50 col0;
    Col_c560_01E01C50 col1;
    struct Ent_c560_01E01C50 *prev;
    struct Ent_c560_01E01C50 *next;
    u8 pad40[8];
    s16 f48;
    s16 f4A;
    s16 f4C;
    s16 f4E;
    s16 f50;
    s16 f52;
    s16 f54;
    u8 pad56[0x5C - 0x56];
} Ent_c560_01E01C50;

typedef struct {
    u8 pad0[0x34];
    Col_c560_01E01C50 col;
    u8 pad38[8];
    Ent_c560_01E01C50 *last;
    f32 f44;
    f32 f48;
    f32 f4C;
    u8 pad50[0x1E0 - 0x50];
    s16 f1E0;
    s16 f1E2;
    u8 pad1E4[2];
    s16 f1E6;
    u8 pad1E8[2];
    s16 f1EA;
    u8 pad1EC[0x1FC - 0x1EC];
    Ent_c560_01E01C50 ent[20];
} Ctx_c560_01E01C50;

static s32 func_01E01C50_c560(Ctx_c560_01E01C50 *g) {
    extern void func_00195108(void *, s32);
    s16 i;
    Ent_c560_01E01C50 *e = NULL;
    Ent_c560_01E01C50 *p;
    f32 h;
    f32 d;

    for (i = 0; i < 20; i++) {
        if (g->ent[i].f48 == 0) {
            e = &g->ent[i];
            func_00195108(e, 0x5C);
            g->ent[i].f48 = i + 1;
            i = 20;
        }
    }
    if (e != NULL) {
        d = 13.0f;
        e->col0 = g->col;
        e->col1 = g->col;
        e->f4A = (s16)g->f44;
        e->f4C = (s16)g->f48;
        e->f52 = g->f1E2;
        e->prev = g->last;
        e->f4E = g->f1EA;
        if (e->prev == NULL) {
            h = g->f4C;
            e->f4 = h;
            e->f14 = h + d;
        } else {
            h = g->f4C;
            e->f4 = h;
            e->f14 = h + d;
        }
        e->f50 = g->f1E0;
        if (50.0f < e->f4) {
            e->f4 = 50.0f;
        }
        if (50.0f < e->f14) {
            e->f14 = 50.0f;
        }
        e->prev = g->last;
        p = e->prev;
        if (p != NULL) {
            p->next = e;
        }
        e->f54 = g->f1E6;
        g->last = e;
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/c560", func_01E01E40_c560);

/* shape c560:01E02520, 128 insns: the c560 trail link's step (c560:01E01C50 links): sinks both heights by 4 (the top stops 13 above the bottom; at the ground the top drops onto the bottom, unlinks the next piece and clears f48), and while the top is under 50 hands its position to the context and spawns the next link; fades by 15 when n < 10, else alpha up by 6 to 0x50 */

/* OVL_WARM */

typedef struct {
    u8 r, g, b, a;
} Col_c560_01E02520;

typedef struct Ent_c560_01E02520 {
    u8 pad0[4];
    f32 f4;
    u8 pad8[0xC];
    f32 f14;
    u8 pad18[0x18];
    Col_c560_01E02520 col0;
    Col_c560_01E02520 col1;
    struct Ent_c560_01E02520 *prev;
    struct Ent_c560_01E02520 *next;
    u8 pad40[8];
    s16 f48;
    s16 f4A;
    s16 f4C;
    s16 f4E;
    s16 f50;
    s16 f52;
    s16 f54;
    u8 pad56[0x5C - 0x56];
} Ent_c560_01E02520;

typedef struct {
    u8 pad0[0x34];
    Col_c560_01E02520 col;
    u8 pad38[8];
    Ent_c560_01E02520 *last;
    f32 f44;
    f32 f48;
    f32 f4C;
    u8 pad50[0x1E0 - 0x50];
    s16 f1E0;
    s16 f1E2;
    u8 pad1E4[2];
    s16 f1E6;
    u8 pad1E8[2];
    s16 f1EA;
    u8 pad1EC[0x1FC - 0x1EC];
    Ent_c560_01E02520 ent[20];
} Ctx_c560_01E02520;

static s32 func_01E02520_c560(Ctx_c560_01E02520 *g, Ent_c560_01E02520 *e, s32 n) {
    extern s32 c560_01E01C50();
    e->f52 -= 7;
    e->f4A = (s16)e->f4;
    e->f4C = (s16)e->f14;
    if (e->f4 > 0.0f) {
        e->f4 -= 4.0f;
        if (e->f14 - e->f4 >= 13.0f) {
            e->f14 -= 4.0f;
        }
    } else {
        e->f14 -= 4.0f;
        if (e->f14 < e->f4) {
            e->f14 = e->f4;
            if (e->next != NULL) {
                e->next->prev = NULL;
            }
            e->f48 = 0;
        }
    }
    if (e->f54 > 0) {
        if (e->f14 < 50.0f) {
            g->last = e;
            g->f44 = e->f4A;
            g->f48 = e->f4C;
            g->col.a = 0;
            g->f1E6 = 1;
            g->f4C = e->f14;
            g->f1EA = 1;
            g->f1E2 = e->f52 + 12;
            g->f1E0 = e->f50;
            if (c560_01E01C50(g, func_01E02520_c560) != 0) {
                e->f54 = 0;
            }
        }
    }
    if (n < 10) {
        if (e->col0.a > 16) {
            e->col0.a -= 15;
        }
        if (e->col1.a > 16) {
            e->col1.a -= 15;
        }
    } else if (e->col0.a < 0x50) {
        e->col0.a += 6;
    }
    e->col1.a = 0;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/c560", func_01E02720_c560);
